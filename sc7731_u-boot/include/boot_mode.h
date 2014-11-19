#ifndef _BOOT_MODE_H_
#define _BOOT_MODE_H_
#include <asm/arch/sci_types.h>
#define CHECK_BOOTMODE_FUN_NUM 20

typedef enum{
    CMD_NONE=0,
    CMD_POWER_DOWN_DEVICE,
    CMD_NORMAL_MODE,
    CMD_RECOVERY_MODE,
    CMD_FASTBOOT_MODE,
    CMD_ALARM_MODE,
    CMD_CHARGE_MODE,
    CMD_ENGTEST_MODE,
    CMD_WATCHDOG_REBOOT ,
    CMD_SPECIAL_MODE,
    CMD_UNKNOW_REBOOT_MODE,
    CMD_PANIC_REBOOT,
    CMD_CALIBRATION_MODE,
    CMD_AUTODLOADER_REBOOT,
    CMD_EXT_RSTN_REBOOT_MODE,
    CMD_IQ_REBOOT_MODE,
}boot_mode_enum_type;

typedef boot_mode_enum_type (*CBOOT_FUNC) (void);
typedef void (*CBOOT_MODE_ENTRY) (void);

#define MODE_REGIST(index, fun) \
    do{\
            array[index]  = fun;\
        }while(0)

boot_mode_enum_type get_mode_from_calibration (void);
#ifndef CONFIG_MACH_CORI
#if !defined(CONFIG_KANAS_W) && !defined(CONFIG_KANAS_TD)
 boot_mode_enum_type get_mode_from_bat_low (void);
#endif
#endif
#ifdef CONFIG_SPRD_SYSDUMP
 boot_mode_enum_type write_sysdump_before_boot_extend (void);
#endif
 boot_mode_enum_type get_mode_from_file_extend (void);
 boot_mode_enum_type get_mode_from_watchdog (void);
 boot_mode_enum_type  get_mode_from_alarm_register(void);
 boot_mode_enum_type  get_mode_from_charger(void);
 boot_mode_enum_type  get_mode_from_keypad(void);
 boot_mode_enum_type  get_mode_from_gpio_extend(void);

int get_mode_from_file(void);
void normal_mode(void);
void recovery_mode(void);
void charge_mode(void);
void fastboot_mode(void);
void alarm_mode(void);
BOOLEAN calibration_detect(int key);
void engtest_mode(void);
void watchdog_mode(void);
void unknow_reboot_mode(void);
void special_mode(void);
void panic_reboot_mode(void);
#ifdef CONFIG_AUTODLOADER
void autodloader_mode(void);
#else
#define autodloader_mode() do {} while (0)
#endif
void iq_mode(void);
int is_bat_low(void);
int alarm_flag_check(void);
int cali_file_check(void);
int read_adc_calibration_data(char *buffer,int size);
#define RECOVERY_MODE   0x77665502
#define FASTBOOT_MODE   0x77665500
#define NORMAL_MODE   0x77665503
#define ALARM_MODE   0x77665504
#define SLEEP_MODE   0x77665505
#define WATCHDOG_REBOOT 0x77665506
#define SPECIAL_MODE 0x77665507
#define UNKNOW_REBOOT_MODE 0x77665508
#define PANIC_REBOOT 0x77665509
#define CALIBRATION_MODE 0x7766550a
#define AUTODLOADER_REBOOT 0x77665510
#define EXT_RSTN_REBOOT_MODE 0x77665511
#define IQ_REBOOT_MODE 0x77665512

#define BOOT_FASTBOOT FASTBOOT_MODE
#define BOOT_RECOVERY RECOVERY_MODE
#define BOOT_CALIBRATE CALIBRATION_MODE
#define BOOT_DLOADER 0xf5

#define BACKLIGHT_ON 1
#define BACKLIGHT_OFF 0

extern unsigned int check_key_boot(unsigned char key);
extern void vlx_nand_boot(char * kernel_pname, char * cmdline, int backlight_set);
#endif
