#include "normal_mode.h"
#include <mmc.h>
#include <fat.h>
#if defined(CONFIG_OF_LIBFDT)
#include <libfdt.h>
#include <fdt_support.h>
#endif

#define FACTORY_PART "prodnv"
#define CMDLINE_BUF_SIZE	(1024)

unsigned spl_data_buf[0x2000] __attribute__((align(4)))={0};
unsigned harsh_data_buf[8]__attribute__((align(4)))={0};
void *spl_data = spl_data_buf;
void *harsh_data = harsh_data_buf;
unsigned char raw_header[8192];
const int SP09_MAX_PHASE_BUFF_SIZE = sizeof(SP09_PHASE_CHECK_T);
unsigned int g_charger_mode = 0;


extern int charger_connected(void);

extern void* lcd_base;
#ifdef CONFIG_OF_LIBFDT
static char boot_cmd[64];
#endif

unsigned short calc_checksum(unsigned char *dat, unsigned long len)
{
        unsigned short num = 0;
        unsigned long chkSum = 0;
        while(len>1){
                num = (unsigned short)(*dat);
                dat++;
                num |= (((unsigned short)(*dat))<<8);
                dat++;
                chkSum += (unsigned long)num;
                len -= 2;
        }
        if(len){
                chkSum += *dat;
        }
        chkSum = (chkSum >> 16) + (chkSum & 0xffff);
        chkSum += (chkSum >> 16);
        return (~chkSum);
}

unsigned char _chkNVEcc(uint8_t* buf, uint32_t size,uint32_t checksum)
{
	uint16_t crc;

	crc = calc_checksum(buf,size);
	debugf("_chkNVEcc calcout 0x%lx, org 0x%llx\n",crc,checksum);
	return (crc == (uint16_t)checksum);
}
/*FDT_ADD_SIZE used to describe the size of the new bootargs items*/
/*include lcd id, lcd base, etc*/
#define FDT_ADD_SIZE (500)
static int start_linux()
{
	void (*theKernel)(int zero, int arch, u32 params);
	u32 exec_at = (u32)-1;
	u32 parm_at = (u32)-1;
	u32 machine_type;
	u8* fdt_blob;
	u32 fdt_size;
	boot_img_hdr *hdr=raw_header;
	int err;

	machine_type = machine_arch_type;         /* get machine type */
	theKernel = (void (*)(int, int, u32))KERNEL_ADR; /* set the kernel address */
#ifndef CONFIG_SC8830
	*(volatile u32*)0x84001000 = 'j';
	*(volatile u32*)0x84001000 = 'm';
	*(volatile u32*)0x84001000 = 'p';
#endif

#ifdef CONFIG_OF_LIBFDT
	fdt_blob = (u8*)DT_ADR;
	if (fdt_check_header(fdt_blob) != 0) {
		printk("image is not a fdt\n");
	}
	fdt_size=fdt_totalsize(fdt_blob);

	err = fdt_open_into(fdt_blob, fdt_blob, fdt_size + FDT_ADD_SIZE);
	if (err != 0) {
		printf ("libfdt fdt_open_into(): %s\n",
				fdt_strerror(err));
	}

	fdt_initrd_norsvmem(fdt_blob,RAMDISK_ADR,RAMDISK_ADR+hdr->ramdisk_size, 1);

	fdt_fixup_lcdid(fdt_blob);
	fdt_fixup_lcdbase(fdt_blob);
	fdt_fixup_calibration_parameter(fdt_blob);
	fdt_fixup_serialno(fdt_blob);
	fdt_fixup_adc_calibration_data(fdt_blob);
	fdt_fixup_dram_training(fdt_blob);
#ifndef CONFIG_EMMC_BOOT
	fdt_fixup_mtd(fdt_blob);
#endif
	debugf("start_linux boot_cmd: %s\n",boot_cmd);
	fdt_fixup_boot_mode(fdt_blob,boot_cmd);
	fdt_fixup_chosen_bootargs_board_private(fdt_blob, boot_cmd);
	// start modem CP
         modem_entry();
#ifdef CONFIG_EMMC_BOOT
	Emmc_DisSdClk();
#endif
	theKernel(0, machine_type, (unsigned long)fdt_blob);
#else
         // start modem CP
         modem_entry();
#ifdef CONFIG_EMMC_BOOT
         Emmc_DisSdClk();
#endif
	theKernel(0, machine_type, VLX_TAG_ADDR);    /* jump to kernel with register set */
#endif
	while(1);
	return 0;
}
void lcd_display_logo(int backlight_set,ulong bmp_img,size_t size)
{
#define mdelay(t)     ({unsigned long msec=(t); while (msec--) { udelay(1000);}})//LiWei add
#ifdef CONFIG_SPLASH_SCREEN
	extern int lcd_display_bitmap(ulong bmp_image, int x, int y);
	extern void lcd_display(void);
	extern void *lcd_base;
	extern void Dcache_CleanRegion(unsigned int addr, unsigned int length);
	extern void set_backlight(uint32_t value);
	if(backlight_set == BACKLIGHT_ON){
		lcd_display_bitmap((ulong)bmp_img, 0, 0);
#if defined(CONFIG_SC8810) || defined(CONFIG_SC8825) || defined(CONFIG_SC8830)
		Dcache_CleanRegion((unsigned int)(lcd_base), size<<1);//Size is to large.
#endif
		lcd_display();
#ifdef CONFIG_SC8830_LVDS
		mdelay(50);//LiWei add
#endif
		mdelay(50);
		set_backlight(255);
	}else{
		memset((unsigned int)lcd_base, 0, size);
#if defined(CONFIG_SC8810) || defined(CONFIG_SC8825) || defined(CONFIG_SC8830)
		Dcache_CleanRegion((unsigned int)(lcd_base), size<<1);//Size is to large.
#endif
		lcd_display();
	}
#endif
}

int is_factorymode()
{
  char factorymode_falg[8]={0};
  int ret = 0;

	if ( do_fs_file_read(FACTORY_PART,"/factorymode.file",factorymode_falg,8))
		return 0;
	debugf("Checking factorymode :  factorymode_falg = %s \n", factorymode_falg);
	if(!strcmp(factorymode_falg, "1"))
		ret = 1;
	else
		ret = 0;
	debugf("Checking factorymode :  ret = %d \n", ret);
	return ret;
}

char* get_product_sn(void)
{
	SP09_PHASE_CHECK_T phase_check;
         char serial_number_to_transfer[SP09_MAX_SN_LEN];
	memset(serial_number_to_transfer, 0x0, SP09_MAX_SN_LEN);

	if(do_raw_data_read(PRODUCTINFO_FILE_PATITION, 
					sizeof(phase_check),
					0,
					(char *)&phase_check)){
		debugf("%s: read miscdata error.\n", __func__);
		return NULL;
	}

	if(phase_check.Magic == SP09_SPPH_MAGIC_NUMBER){
		memcpy(serial_number_to_transfer, phase_check.SN1, SP09_MAX_SN_LEN);
		return serial_number_to_transfer;
	}

	return NULL;
}

#ifdef CONFIG_OF_LIBFDT
static char * set_boot_mode(char *cmdline)
{
	char * boot_mode_p = NULL;

	memset(boot_cmd,0,64);
	boot_mode_p = strstr(cmdline,"androidboot");
	if(boot_mode_p){
		if(strlen(boot_mode_p) > 64){
			debugf("boot mode too long\n");
			return NULL;
		}
		strcpy(boot_cmd,boot_mode_p);
	}
	debugf("CONFIG_OF_LIBFDT cmdline %s boot_cmd %s\n",cmdline,boot_cmd);
	return boot_cmd;
}

#else

#ifndef CONFIG_FPGA
int cmdline_fixup_lcd(char *buf, int str_len)
{
    extern uint32_t load_lcd_id_to_kernel();
    uint32_t lcd_id;
    int offset;

    offset = str_len;
    lcd_id = load_lcd_id_to_kernel();
    //add lcd id
    if(lcd_id) {
        offset += sprintf(buf+offset, " lcd_id=ID");
        offset += sprintf(buf+offset, "%x",lcd_id);
    }
    if(lcd_base != NULL){
        //add lcd frame buffer base, length should be lcd w*h*2(RGB565)
        offset += sprintf(buf+offset, " lcd_base=");
        offset += sprintf(buf+offset, "%x",lcd_base);
    }
    
    return offset;
}
#endif

#ifdef USB_PHY_TUNE_VALUE
int cmdline_fixup_usb_phy_tune(char *buf, int str_len)
{
    /*transfer this value to kernel usb_hw.c*/
    int offset = str_len;
    
    offset += sprintf(buf+offset, " usb_phy_tune=");
    offset += sprintf(buf+offset, "%x", USB_PHY_TUNE_VALUE);
    //buf[offset] = '\0';
    
    return offset;
}
#endif
int cmdline_fixup_factorymode(char *buf, int str_len)
{
    int offset = str_len;
    
    if (1 == is_factorymode()) {
        offset += sprintf(buf+offset, " factory=1");
    }

    return offset;
}

#if defined( CONFIG_AP_ADC_CALIBRATION)||defined(CONFIG_SC8830)|| (defined(CONFIG_SC8825) && (!(BOOT_NATIVE_LINUX)))
int cmdline_fixup_adc_data(char *buf, int str_len)
{
    extern int read_adc_calibration_data(char *buffer,int size);
    extern void CHG_SetADCCalTbl (unsigned int *adc_data);
    int offset = str_len;
    unsigned int *adc_data;
    
    adc_data = malloc(64);
    if(adc_data){
        memset(adc_data,0,64);
        if(0 <  read_adc_calibration_data(adc_data,48)){
            if(((adc_data[2]&0xffff) < 4500 )&&((adc_data[2]&0xffff) > 3000)&&
            ((adc_data[3]&0xffff) < 4500 )&&((adc_data[3]&0xffff) > 3000)){
                offset += sprintf(buf+offset, " adc_cal=%d,%d",adc_data[2],adc_data[3]);
            }
            if((0x00000002 == adc_data[10])&&(0x00000002 == adc_data[11])){
                offset += sprintf(buf+offset, " fgu_cal=%d,%d,%d",adc_data[4],adc_data[5],adc_data[6]);
            }
#if (defined(CONFIG_SC8825) && (!(BOOT_NATIVE_LINUX)))
            CHG_SetADCCalTbl(adc_data);
            DCDC_Cal_ArmCore();
#endif
        }
        free(adc_data);
    }

    return offset;    
}
#endif

int cmdline_fixup_harsh_data(char *buf, int str_len)
{
    int offset = str_len;
    
    if(0 != read_spldata()){
    	debugf("read_spldata failed\n");
    	free(buf);
    	return 0;
    }
    if(harsh_data == NULL){
    	debugf("harsh_data malloc failed\n");
    	free(buf);
    	return 0;
    }
    debugf("spl_data adr 0x%x harsh_data adr 0x%x\n", spl_data, harsh_data);
    if(cal_md5(spl_data, CONFIG_SPL_LOAD_LEN, harsh_data)){
    	offset += sprintf(buf+offset, " securemd5=%08x%08x%08x%08x", *(uint32_t*)harsh_data, *(uint32_t*)(harsh_data+4),\
    		*(uint32_t*)(harsh_data+8), *(uint32_t*)(harsh_data+12));
    }
    return offset;
}

int cmdline_fixup_serialno(char *buf, int str_len)
{
    int offset;
    char *sn = get_product_sn();

    offset = str_len;
    offset += sprintf(buf+offset, " androidboot.serialno=%s", sn?sn:"0123456789ABCDEF");

    return offset;
}

#if defined(CONFIG_SC8830)
int cmdline_fixup_fgu(char *buf, int str_len)
{
    extern unsigned int fgu_cur;
    extern unsigned int fgu_vol;
    int offset;

    offset = str_len;
    offset += sprintf(buf+offset, " fgu_init=%d,%d",fgu_vol,fgu_cur);
    
    return offset;
}
#endif

int cmdline_fixup_apct_param(char *buf, int str_len)
{
    extern long long lcd_init_time;
    extern long long load_image_time;
    int offset;

    offset = str_len;
    offset += sprintf(buf+offset, " lcd_init=%lld",lcd_init_time);
    offset += sprintf(buf+offset, " load_image=%lld",load_image_time);
    offset += sprintf(buf+offset, " pl_t=%lld",get_ticks());

    return offset;
}
#endif

void cmdline_set_cp_cmdline(char *buf, int str_len)
{
    char *nv_info;
#ifdef CONFIG_SUPPORT_TD
    nv_info = (char*)(((volatile u32*)CALIBRATION_FLAG));
    sprintf(nv_info, buf);
    nv_info[str_len] = '\0';
    debugf("nv_info:[%08x]%s \n", nv_info, nv_info);
#endif
#ifdef CONFIG_SUPPORT_W
    nv_info = (char*)((volatile u32*)CALIBRATION_FLAG_WCDMA);
    sprintf(nv_info, buf);
    nv_info[str_len] = '\0';
    debugf("nv_info:[%08x]%s \n", nv_info, nv_info);
#endif
}
int creat_cmdline(char * cmdline,boot_img_hdr *hdr)
{
    char *buf;
    int offset = 0;
    int ret = 0;

    if(cmdline == NULL){
        return -1;
    }
    buf = malloc(CMDLINE_BUF_SIZE);
    memset(buf, 0, CMDLINE_BUF_SIZE);

#ifdef CONFIG_OF_LIBFDT
    if(set_boot_mode(cmdline)){
		if(cmdline && cmdline[0]){
			offset += sprintf(buf, " %s", cmdline);
		}
#ifdef CONFIG_AP_VERSION
		offset += sprintf(buf+offset, " apv=\"%s\"", CONFIG_AP_VERSION);
#endif
		cmdline_set_cp_cmdline(cmdline, offset);
		if (buf != NULL) {
			free(buf);
		}
        return 0;
    }else{
		if (buf != NULL) {
			free(buf);
		}
        return -1;
    }
#else

    if(hdr){
        offset += sprintf(buf, "initrd=0x%x,0x%x", RAMDISK_ADR, hdr->ramdisk_size);
    }
/* preset loop_per_jiffy */
#ifdef CONFIG_LOOP_PER_JIFFY
    offset += sprintf(buf+offset, " lpj=%d", CONFIG_LOOP_PER_JIFFY);
#endif
#ifdef CONFIG_AP_VERSION
    offset += sprintf(buf+offset, " apv=\"%s\"", CONFIG_AP_VERSION);
#endif
    if(cmdline && cmdline[0]){
        offset += sprintf(buf+offset, " %s", cmdline);
    }
#ifndef CONFIG_FPGA 
    offset = cmdline_fixup_lcd(buf, offset);
#endif
#ifdef USB_PHY_TUNE_VALUE
    offset = cmdline_fixup_usb_phy_tune(buf, offset);
#endif
    offset = cmdline_fixup_factorymode(buf, offset);
    offset += sprintf(buf+offset, " no_console_suspend");
#ifdef CONFIG_RAM_CONSOLE 
/* Fill ram log base address and size to cmdline.
It will be used when assigning reserve memory in kernel and dump ram log*/
    offset += sprintf(buf+offset, " boot_ram_log=%#010x,%#x", CONFIG_RAM_CONSOLE_START, CONFIG_RAM_CONSOLE_SIZE);
#endif
    offset = cmdline_fixup_serialno(buf, offset);
    ret =  cmdline_fixup_harsh_data(buf, offset);
    if (ret){
        offset = ret;
    }else{
        return -1;
    }
#if defined(CONFIG_AP_ADC_CALIBRATION)||defined(CONFIG_SC8830)|| (defined(CONFIG_SC8825) && (!(BOOT_NATIVE_LINUX)))
    offset = cmdline_fixup_adc_data(buf, offset);
#if defined(CONFIG_SC8830)
    offset = cmdline_fixup_fgu(buf, offset);
#endif
    offset = cmdline_fixup_apct_param(buf, offset);
#endif
    cmdline_set_cp_cmdline(buf, offset);

    debugf("cmdline_len = %d \n pass cmdline: %s \n",strlen(buf), buf);
    creat_atags(VLX_TAG_ADDR, buf, NULL, 0);

    if (buf != NULL) {
        free(buf);
    }
    return 0;
#endif
}
void vlx_entry()
{
	/*down the device if charger disconnect during calibration detect.*/
	if ( g_charger_mode && !charger_connected() ){
		g_charger_mode = 0;
		power_down_devices();
		while(1);
	}

#if !(defined CONFIG_SC8810 || defined CONFIG_TIGER || defined CONFIG_SC8830)
	MMU_InvalideICACHEALL();
#endif

#if (defined CONFIG_SC8810) || (defined CONFIG_SC8825) || (defined CONFIG_SC8830)
	MMU_DisableIDCM();
#endif

#ifdef REBOOT_FUNCTION_INUBOOT
	reboot_func();
#endif

#if BOOT_NATIVE_LINUX
	start_linux();
#else
	void (*entry)(void) = (void*) VMJALUNA_ADR;
	entry();
#endif
}
void normal_mode(void)
{
#if defined (CONFIG_SC8810) || defined (CONFIG_SC8825) || defined (CONFIG_SC8830)
    //MMU_Init(CONFIG_MMU_TABLE_ADDR);
	vibrator_hw_init();
#endif
    set_vibrator(1);

#ifndef UART_CONSOLE_SUPPORT
#ifdef CONFIG_SC7710G2
	extern int  serial1_SwitchToModem(void);
	serial1_SwitchToModem();
#endif
#endif

#if BOOT_NATIVE_LINUX
    vlx_nand_boot(BOOT_PART, CONFIG_BOOTARGS, BACKLIGHT_ON);
#else
    vlx_nand_boot(BOOT_PART, NULL, BACKLIGHT_ON);
#endif

}
void special_mode(void)
{
    debugf("special_mode\n");
#if BOOT_NATIVE_LINUX
    vlx_nand_boot(BOOT_PART, CONFIG_BOOTARGS " androidboot.mode=special", BACKLIGHT_OFF);
#else
    vlx_nand_boot(BOOT_PART, "androidboot.mode=special", BACKLIGHT_OFF);
#endif

}
void iq_mode(void)
{
    debugf("iq_mode\n");
#if BOOT_NATIVE_LINUX
    vlx_nand_boot(BOOT_PART, CONFIG_BOOTARGS " androidboot.mode=iq", BACKLIGHT_OFF);
#else
    vlx_nand_boot(BOOT_PART, " androidboot.mode=iq", BACKLIGHT_OFF);
#endif

}

#ifdef CONFIG_GENERIC_MMC
#define MODEM_MEMORY_NAME "modem_memory.log"
#define MODEM_MEMORY_SIZE  (22 * 1024 * 1024)
#ifdef CONFIG_SC8810
#define MODEM_MEMORY_ADDR 0
#elif defined (CONFIG_SC8825) || defined (CONFIG_TIGER) || defined(CONFIG_SC8830)
#define MODEM_MEMORY_ADDR 0x80000000
#endif
#endif
void watchdog_mode(void)
{
	debugf("watchdog_mode\n");
#if BOOT_NATIVE_LINUX
	vlx_nand_boot(BOOT_PART, CONFIG_BOOTARGS " androidboot.mode=wdgreboot", BACKLIGHT_OFF);
#else
	vlx_nand_boot(BOOT_PART, "androidboot.mode=wdgreboot", BACKLIGHT_OFF);
#endif
}

void unknow_reboot_mode(void)
{
	debugf("unknow_reboot_mode\n");
#if BOOT_NATIVE_LINUX
	vlx_nand_boot(BOOT_PART, CONFIG_BOOTARGS " androidboot.mode=unknowreboot", BACKLIGHT_OFF);
#else
	vlx_nand_boot(BOOT_PART, "androidboot.mode=unknowreboot", BACKLIGHT_OFF);
#endif
}
void panic_reboot_mode(void)
{
	debugf("%s\n", __func__);
#if BOOT_NATIVE_LINUX
	vlx_nand_boot(BOOT_PART, CONFIG_BOOTARGS " androidboot.mode=panic", BACKLIGHT_OFF);
#else
	vlx_nand_boot(BOOT_PART, "androidboot.mode=panic", BACKLIGHT_OFF);
#endif
}

#if BOOT_NATIVE_LINUX_MODEM

void sipc_addr_reset()
{
#ifdef CONFIG_SC8825
	memset((void *)SIPC_APCP_START_ADDR, 0x0, SIPC_APCP_RESET_ADDR_SIZE);
#elif defined (CONFIG_SC8830)
#if defined(CONFIG_SUPPORT_TD) || defined(CONFIG_SC9620OPENPHONE) || defined(CONFIG_SC9620FPGA)
	memset((void *)SIPC_TD_APCP_START_ADDR, 0x0, SIPC_APCP_RESET_ADDR_SIZE);

#elif defined(CONFIG_SUPPORT_W)

	memset((void *)SIPC_WCDMA_APCP_START_ADDR, 0x0, SIPC_APCP_RESET_ADDR_SIZE);
#else
#ifndef CONFIG_NOT_BOOT_TD_MODEM
	memset((void *)SIPC_TD_APCP_START_ADDR, 0x0, SIPC_APCP_RESET_ADDR_SIZE);
#endif
#ifndef CONFIG_NOT_BOOT_W_MODEM
	memset((void *)SIPC_WCDMA_APCP_START_ADDR, 0x0, SIPC_APCP_RESET_ADDR_SIZE);
#endif
#endif
#ifdef CONFIG_SP8830WCN
	memset((void *)SIPC_WCN_APCP_START_ADDR, 0x0, SIPC_APCP_RESET_ADDR_SIZE);
#endif
#endif
}

#endif

