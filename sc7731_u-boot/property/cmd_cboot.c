#include <config.h>
#include <common.h>
#include <command.h>
#include <linux/types.h>
#include <linux/keypad.h>
#include <linux/key_code.h>
#include <boot_mode.h>
#include <android_bootimg.h>
#include <asm/arch/gpio.h>

#define COMMAND_MAX 128

#define DEBUG
#ifdef DEBUG
#define DBG(fmt...) printf(fmt)
#else
#define DBG(fmt...) 
#endif

extern int power_button_pressed(void);
extern int charger_connected(void);
extern int alarm_triggered(void);
extern int cali_file_check(void);
extern int get_mode_from_gpio();
unsigned check_reboot_mode(void);
extern void CHG_LateInit(void);
extern void CHG_LowBatChg(void);


int boot_pwr_check(void)
{
    static int total_cnt = 0;
    if(!power_button_pressed())
      total_cnt ++;
    return total_cnt;
}
#define mdelay(_ms) udelay(_ms*1000)

extern CBOOT_FUNC s_boot_func_array[CHECK_BOOTMODE_FUN_NUM] ;

static unsigned _reboot_mode_check(void)
{
    static unsigned rst_mode = 0, check_times=0;
    if(!check_times)
    {
        rst_mode = check_reboot_mode();
        check_times++;
    }
    DBG("_reboot_mode_check rst_mode=0x%x\n",rst_mode);
    return rst_mode;
}


// 0 get mode from calibration detect
boot_mode_enum_type get_mode_from_calibration (void){
    if(cali_file_check() && !boot_pwr_check() && calibration_detect(2)){
        //never come to here
        return CMD_CALIBRATION_MODE;
    }else{
        return CMD_NONE;
    }
}

#ifndef CONFIG_MACH_CORI
#if !defined(CONFIG_KANAS_W) && !defined(CONFIG_KANAS_TD)
boot_mode_enum_type get_mode_from_bat_low (void){
	while(is_bat_low()) {
		if(charger_connected()) {
			DBG("cboot:low battery,charging...\n");
			mdelay(200);
			CHG_LowBatChg();
		}else{
			DBG("cboot:low battery and shutdown\n");
			return CMD_POWER_DOWN_DEVICE;
		}
	}
	if(charger_connected()){
		CHG_LateInit();
	}
	return CMD_NONE;
}
#endif
#endif

#ifdef CONFIG_SPRD_SYSDUMP
boot_mode_enum_type write_sysdump_before_boot_extend (void){
    unsigned rst_mode = _reboot_mode_check();
    write_sysdump_before_boot(rst_mode);
    return CMD_NONE;
}
#endif

// 1 get mode from file
boot_mode_enum_type get_mode_from_file_extend (void){
    switch(get_mode_from_file()){
        case RECOVERY_MODE:
            DBG("cboot:get mode from file:recovery\n");
            return CMD_RECOVERY_MODE;
        default: 
        return CMD_NONE;
    }
    return CMD_NONE;
}

// 2 get mode from watch dog
boot_mode_enum_type get_mode_from_watchdog (void){
    unsigned rst_mode = _reboot_mode_check();
    switch(rst_mode){
        case RECOVERY_MODE:
            return CMD_RECOVERY_MODE;
        case FASTBOOT_MODE:
            return  CMD_FASTBOOT_MODE;
        case NORMAL_MODE:
            return CMD_NORMAL_MODE;
        case WATCHDOG_REBOOT:
            return CMD_WATCHDOG_REBOOT;
        case UNKNOW_REBOOT_MODE:
            return CMD_UNKNOW_REBOOT_MODE;
        case PANIC_REBOOT:
            return CMD_PANIC_REBOOT;
        case AUTODLOADER_REBOOT:
            return CMD_AUTODLOADER_REBOOT;
        case SPECIAL_MODE:
            return CMD_SPECIAL_MODE;
        case EXT_RSTN_REBOOT_MODE:
            return CMD_NORMAL_MODE;
	case IQ_REBOOT_MODE:
            return CMD_IQ_REBOOT_MODE;
        case ALARM_MODE:
        if(alarm_flag_check()){
            int flag =alarm_flag_check();
            DBG("get_mode_from_watchdog flag=%d\n", flag);
            if(flag == 1){
                return CMD_ALARM_MODE;
            }
            else if(flag == 2){
                return CMD_NORMAL_MODE;
            }
        }
        default:
            return CMD_NONE;
    }
}

// 3 get mode from alarm register
boot_mode_enum_type  get_mode_from_alarm_register(void){
    //boot_pwr_check();
    if(alarm_triggered() && alarm_flag_check()){
        int flag =alarm_flag_check();
        DBG("get_mode_from_alarm_register flag=%d\n", flag);
        if(flag == 1){
            return CMD_ALARM_MODE;
        }
        else if(flag == 2){
            return CMD_NORMAL_MODE;
        }
    }else{
        return CMD_NONE;
    }
}

// 4 get mode from charger
boot_mode_enum_type  get_mode_from_charger(void){
    if(charger_connected()){
        DBG("get mode from charger\n");
        return CMD_CHARGE_MODE;
    }else{
        return CMD_NONE;
    }
}
    
// 5 get mode from keypad
boot_mode_enum_type  get_mode_from_keypad(void){
    uint32_t key_mode = 0;
    uint32_t key_code = 0;
    volatile int i;
    if(boot_pwr_check() >= get_pwr_key_cnt()){
        mdelay(50);
        for(i=0; i<10;i++){
            key_code = board_key_scan();
            if(key_code != KEY_RESERVED)
                break;
        }
        key_mode = check_key_boot(key_code);
        DBG("cboot:get mode from keypad:0x%x\n",key_code);
        switch(key_mode){
            case BOOT_FASTBOOT:
                return  CMD_FASTBOOT_MODE;
            case BOOT_RECOVERY:
                return CMD_RECOVERY_MODE;
            case BOOT_CALIBRATE:
                return CMD_ENGTEST_MODE;
            default:
                return CMD_NORMAL_MODE;
        }
    }else{
        return CMD_NONE;
    }
}

// 6 get mode from gpio
boot_mode_enum_type  get_mode_from_gpio_extend(void){
    if (get_mode_from_gpio()) {
        DBG("pbint2 triggered, do normal mode\n");
        return CMD_NORMAL_MODE;
    }else{
        return CMD_NONE;
    }
}

int do_cboot(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    volatile int i;
    boot_mode_enum_type bootmode = CMD_NONE;
    CBOOT_MODE_ENTRY boot_mode_array[20] ={0};

    if(argc > 2)
        goto usage;

#ifdef CONFIG_AUTOBOOT
    normal_mode();
#endif
    for (i=0;  i<CHECK_BOOTMODE_FUN_NUM; i++){
        if (0 != s_boot_func_array[i]){
            DBG("cboot: i=%d\n", i);
            bootmode = s_boot_func_array[i]();
            if(CMD_NONE == bootmode){
                boot_pwr_check();
                continue;
            }else{
                break;
            }
        }
// get mode from argument
        else if(2 == argc){
            DBG("cboot:get mode from argument:%s\n",argv[1]);
            if(!strcmp(argv[1],"normal")){
                bootmode = CMD_NORMAL_MODE;
                break;
            }
            if(!strcmp(argv[1],"recovery")){
                bootmode = CMD_RECOVERY_MODE;
                break;
            }
            if(!strcmp(argv[1],"fastboot")){
                bootmode = CMD_FASTBOOT_MODE;
                break;
            }
            if(!strcmp(argv[1],"charge")){
                bootmode = CMD_CHARGE_MODE;
                break;
            }
        }else{
            bootmode = CMD_POWER_DOWN_DEVICE;
            break;
        }
    }
    DBG("do_cboot:boot mode is %d\n",bootmode);

    cmd_mode_regist(boot_mode_array);
    if((bootmode > CMD_POWER_DOWN_DEVICE) && (0 != boot_mode_array[bootmode])){
        DBG("do_cboot: enter boot mode\n");
        boot_mode_array[bootmode]();
    }else{
        DBG("do_cboot: power down device\n");
        power_down_devices();
        while(1);
    }

    usage:
        cmd_usage(cmdtp);
        return 1;
}

U_BOOT_CMD(
            cboot, CONFIG_SYS_MAXARGS, 1, do_cboot,
            "choose boot mode",
            "mode: \nrecovery, fastboot, dloader, charge, normal, vlx, caliberation.\n"
            "cboot could enter a mode specified by the mode descriptor.\n"
            "it also could enter a proper mode automatically depending on "
            "the environment\n"
          );
