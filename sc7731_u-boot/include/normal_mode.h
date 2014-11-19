#ifndef NORMAL_MODE_H
#define NORMAL_MODE_H

#include <config.h>
#include <common.h>
#include <linux/types.h>
#include <asm/arch/bits.h>
#include <linux/string.h>
#include <android_bootimg.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/ubi.h>
#include <linux/crc32b.h>
#include <linux/mtd/nand.h>
#include <nand.h>
#include <android_boot.h>
#include <environment.h>
#include <jffs2/jffs2.h>
#include <boot_mode.h>
#include <malloc.h>
#include <asm/arch/secure_boot.h>
#include <ubi_uboot.h>
#ifdef CONFIG_MTD_PARTITIONS
#include <linux/mtd/partitions.h>
#endif

extern unsigned spl_data_buf[0x2000] __attribute__((align(4)));
extern unsigned harsh_data_buf[8]__attribute__((align(4)));
extern void *spl_data;
extern void *harsh_data;
extern unsigned char raw_header[8192];
#define DEBUG 1

#ifdef DEBUG
#define debugf(fmt, args...) do { printf("%s(): ", __func__); printf(fmt, ##args); } while (0)
#else
#define debugf(fmt, args...)
#endif


#define SPL_PART "spl"
#define LOGO_PART "logo"
#define SIMLOCK_SIZE   1024
#define PRODUCTINFO_FILE_PATITION  "miscdata"


#if defined (CONFIG_SP8835EB) ||defined(CONFIG_SP8830EB)||defined(CONFIG_SP8830EC)||defined(CONFIG_SP8830GEA)||defined(CONFIG_SC9620OPENPHONE)  //for TD CP1
#define SIMLOCK_ADR      (0x891FE800+0x4)   //0x4 just for data header
#elif defined (CONFIG_SP7735EC) || defined(CONFIG_SP7730EC)  //for W CP0
#define SIMLOCK_ADR      (0x920FE800+0x4)   //0x4(32bit) just for data header
#endif

#define KERNEL_ADR      0x80008000
#define VLX_TAG_ADDR    0x82000100
#define DT_ADR          0x85400000
#define RAMDISK_ADR     0x85500000

#if defined (CONFIG_SPX30G)
#define COOPERATE_PROCESSOR_RESET_ADDR    0x402b00b0
#define COOPERATE_PMU_CTRL0_ADDR         0x402b0044
#define COOPERATE_PMU_CTRL2_ADDR         0x402b0068
#define CORE_CP0                          BIT_0
#define CORE_CP2                          BIT_2
#endif

/////////////////////////////////////////////////////////
/* log_switch function */
#if 0
GSM_Download_Param include the following :

system_param_version  short
fcch_det_struct		12 * short
freq_est_struct		6 * short
freq_track_algo_struct	4 * short
AGC_algo_cal_struct		12 * short
time_track_algo_struct	4 * short
rx_equalizer_struct		3 * short
rx_deinterlever_struct	1 * short
power_scan_struct		----------------->  power_scan_saturation_thresh		1 * short
                                               power_exp_lev					3 * short
                                               power_underflow_thresh			3 * short
tone_para_struct		1 * short
action_tables_struct		0x120 * short
audio_filter_coef		----------------->  HPF_coef					36 * short
                                               LPF_coef					15 * short
dsp_uart_struct		1 * short
deep_sleep_struct		5 * short
log_switch_struct		-----------------> DSP_log_switch                             1 * short
#endif

struct power_scan_saturation_thresh_tag {
	unsigned short	power_scan_saturation_thresh;
};

struct power_exp_lev_tag {
	unsigned short	power_exp_lev[3];
};

struct power_underflow_thresh_tag {
	unsigned short	power_underflow_thresh[3];
};

struct HPF_coef_tag {
	unsigned short	HPF_coef[36];
};

struct LPF_coef_tag {
	unsigned short	LPF_coef[15];
};

struct power_scan_struct_tag {
	struct power_scan_saturation_thresh_tag power_scan_saturation_thresh;
	struct power_exp_lev_tag power_exp_lev;
	struct power_underflow_thresh_tag power_underflow_thresh;
};

struct audio_filter_coef_tag {
	struct HPF_coef_tag HPF_coef;
	struct LPF_coef_tag LPF_coef;
};

struct DSP_log_switch_tag {
	unsigned short DSP_log_switch_value;
};

struct log_switch_struct_tag {
	struct DSP_log_switch_tag DSP_log_switch;
};

struct GSM_Download_Param_Tag {
	unsigned short system_param_version;
	unsigned short fcch_det_struct[12];
	unsigned short freq_est_struct[6];
	unsigned short freq_track_algo_struct[4];
	unsigned short AGC_algo_cal_struct[12];
	unsigned short time_track_algo_struct[4];
	unsigned short rx_equalizer_struct[3];
	unsigned short rx_deinterlever_struct;
	struct power_scan_struct_tag power_scan_struct;
	unsigned short tone_para_struct;
	unsigned short action_tables_struct[0x120];
	struct audio_filter_coef_tag audio_filter_coef;
	unsigned short dsp_uart_struct;
	unsigned short deep_sleep_struct[5];
	struct log_switch_struct_tag log_switch_struct;
};
/////////////////////////////////////////////////////////

#define MAX_SN_LEN 			(24)
#define SP09_MAX_SN_LEN			MAX_SN_LEN
#define SP09_MAX_STATION_NUM		(15)
#define SP09_MAX_STATION_NAME_LEN	(10)
#define SP09_SPPH_MAGIC_NUMBER          (0X53503039)    // "SP09"
#define SP09_MAX_LAST_DESCRIPTION_LEN   (32)

typedef struct _tagSP09_PHASE_CHECK
{
	unsigned long 	Magic;                	// "SP09"
	char    	SN1[SP09_MAX_SN_LEN]; 	// SN , SN_LEN=24
	char    	SN2[SP09_MAX_SN_LEN];    // add for Mobile
	int     	StationNum;                 	// the test station number of the testing
	char    	StationName[SP09_MAX_STATION_NUM][SP09_MAX_STATION_NAME_LEN];
	unsigned char 	Reserved[13];               	//
	unsigned char 	SignFlag;
	char    	szLastFailDescription[SP09_MAX_LAST_DESCRIPTION_LEN];
	unsigned short  iTestSign;				// Bit0~Bit14 ---> station0~station 14
	                 		  			  //if tested. 0: tested, 1: not tested
	unsigned short  iItem;    // part1: Bit0~ Bit_14 indicate test Station,1 : Pass,

}SP09_PHASE_CHECK_T, *LPSP09_PHASE_CHECK_T;

typedef enum{
	IMG_RAW,
	IMG_UBIFS,
	IMG_YAFFS,
	IMG_MAX
}img_fs_type;

typedef struct vol_image_required
{
	char* vol;  //volume name
	char* bak_vol;  //if no backup vol, set NULL
	unsigned long size;  //partition size to be read
	unsigned long mem_addr;  //target memory addr
	img_fs_type fs_type;
}vol_image_required_t;

typedef struct boot_image_required
{
	wchar_t* partition;  //partition name record on disk
	wchar_t* bak_partition;  //if no backup partition, set NULL
	unsigned long size;  //partition size to be read
	unsigned long mem_addr;  //target memory addr
}boot_image_required_t;

extern const int SP09_MAX_PHASE_BUFF_SIZE;

#define NV_HEAD_MAGIC	(0x00004e56)
#define NV_VERSION		(101)
#define NV_HEAD_LEN	(512)
typedef struct  _NV_HEADER {
     uint32_t magic;
     uint32_t len;
     uint32_t checksum;
     uint32_t version;
}nv_header_t;

void set_vibrator(int on);
void vibrator_hw_init(void);
void MMU_InvalideICACHEALL(void);
int read_spldata();
void lcd_display_logo(int backlight_set,ulong bmp_image,size_t size);
int creat_cmdline(char * cmdline,boot_img_hdr *hdr);
void vlx_entry();

#endif /* NORMAL_MODE_H */
