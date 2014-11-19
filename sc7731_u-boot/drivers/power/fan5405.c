
#include <asm/arch/sci_types.h>
#include <asm/arch/os_api.h>
#include <asm/arch/chip_drvapi.h>
#include <asm/arch/chip_plf_export.h>
#include <asm/arch/sprd_reg_global.h>
#include <asm/arch/sprd_reg_base.h>
#include "sp8830_i2c.h"


/******************************************************************************
* Register addresses
******************************************************************************/
#define FAN5405_REG_CONTROL0	              0
#define FAN5405_REG_CONTROL1	              1
#define FAN5405_REG_OREG	              2
#define FAN5405_REG_IC_INFO                   3
#define FAN5405_REG_IBAT	              4
#define FAN5405_REG_SP_CHARGER                5
#define FAN5405_REG_SAFETY                    6
#define FAN5405_REG_MONITOR                  16

/******************************************************************************
* Register bits
******************************************************************************/
/* FAN5405_REG_CONTROL0 (0x00) */
#define FAN5405_FAULT                   (0x07)
#define FAN5405_FAULT_SHIFT                  0
#define FAN5405_BOOST              (0x01 << 3)
#define FAN5405_BOOST_SHIFT                  3
#define FAN5405_STAT               (0x3 <<  4)
#define FAN5405_STAT_SHIFT                   4
#define FAN5405_EN_STAT            (0x01 << 6)
#define FAN5405_EN_STAT_SHIFT                6
#define FAN5405_TMR_RST_OTG        (0x01 << 7)  // writing a 1 resets the t32s timer, writing a 0 has no effect
#define FAN5405_TMR_RST_OTG_SHIFT            7

/* FAN5405_REG_CONTROL1 (0x01) */
#define FAN5405_OPA_MODE                (0x01)
#define FAN5405_OPA_MODE_SHIFT               0
#define FAN5405_HZ_MODE            (0x01 << 1)
#define FAN5405_HZ_MODE_SHIFT                1
#define FAN5405_CE_N               (0x01 << 2)
#define FAN5405_CE_N_SHIFT                   2
#define FAN5405_TE                 (0x01 << 3)
#define FAN5405_TE_SHIFT                     3
#define FAN5405_VLOWV              (0x03 << 4)
#define FAN5405_VLOWV_SHIFT                  4
#define FAN5405_IINLIM             (0x03 << 6)
#define FAN5405_IINLIM_SHIFT                 6

/* FAN5405_REG_OREG (0x02) */
#define FAN5405_OTG_EN                  (0x01)
#define FAN5405_OTG_EN_SHIFT                 0
#define FAN5405_OTG_PL             (0x01 << 1)
#define FAN5405_OTG_PL_SHIFT                 1
#define FAN5405_OREG               (0x3f << 2)
#define FAN5405_OREG_SHIFT                   2

/* FAN5405_REG_IC_INFO (0x03) */
#define FAN5405_REV                     (0x03)
#define FAN5405_REV_SHIFT                    0
#define FAN5405_PN                 (0x07 << 2)
#define FAN5405_PN_SHIFT                     2
#define FAN5405_VENDOR_CODE        (0x07 << 5)
#define FAN5405_VENDOR_CODE_SHIFT            5

/* FAN5405_REG_IBAT (0x04) */
#define FAN5405_ITERM                   (0x07)
#define FAN5405_ITERM_SHIFT                  0
#define FAN5405_IOCHARGE           (0x07 << 4)
#define FAN5405_IOCHARGE_SHIFT               4
#define FAN5405_RESET              (0x01 << 7)
#define FAN5405_RESET_SHIFT                  7

/* FAN5405_REG_SP_CHARGER (0x05) */
#define FAN5405_VSP                     (0x07)
#define FAN5405_VSP_SHIFT                    0
#define FAN5405_EN_LEVEL           (0x01 << 3)
#define FAN5405_EN_LEVEL_SHIFT               3
#define FAN5405_SP                 (0x01 << 4)
#define FAN5405_SP_SHIFT                     4
#define FAN5405_IO_LEVEL           (0x01 << 5)
#define FAN5405_IO_LEVEL_SHIFT               5
#define FAN5405_DIS_VREG           (0x01 << 6)
#define FAN5405_DIS_VREG_SHIFT               6

/* FAN5405_REG_SAFETY (0x06) */
#define FAN5405_VSAFE                   (0x0f)
#define FAN5405_VSAFE_SHIFT                  0
#define FAN5405_ISAFE              (0x07 << 4)
#define FAN5405_ISAFE_SHIFT                  4

/* FAN5405_REG_MONITOR (0x10) */
#define FAN5405_CV                      (0x01)
#define FAN5405_CV_SHIFT                     0
#define FAN5405_VBUS_VALID         (0x01 << 1)
#define FAN5405_VBUS_VALID_SHIFT             1
#define FAN5405_IBUS               (0x01 << 2)
#define FAN5405_IBUS_SHIFT                   2
#define FAN5405_ICHG               (0x01 << 3)
#define FAN5405_ICHG_SHIFT                   3
#define FAN5405_T_120              (0x01 << 4)
#define FAN5405_T_120_SHIFT                  4
#define FAN5405_LINCHG             (0x01 << 5)
#define FAN5405_LINCHG_SHIFT                 5
#define FAN5405_VBAT_CMP           (0x01 << 6)
#define FAN5405_VBAT_CMP_SHIFT               6
#define FAN5405_ITERM_CMP          (0x01 << 7)
#define FAN5405_ITERM_CMP_SHIFT              7

/******************************************************************************
* bit definitions
******************************************************************************/
/********** FAN5405_REG_CONTROL0 (0x00) **********/
// EN_STAT [6]
#define ENSTAT 1
#define DISSTAT 0
// TMR_RST [7]
#define RESET32S 1

/********** FAN5405_REG_CONTROL1 (0x01) **********/
// OPA_MODE [0]
#define CHARGEMODE 0
#define BOOSTMODE 1
//HZ_MODE [1]
#define NOTHIGHIMP 0
#define HIGHIMP 1
// CE/ [2]
#define ENCHARGER 0
#define DISCHARGER 1
// TE [3]
#define DISTE 0
#define ENTE 1
// VLOWV [5:4]
#define VLOWV3P4 0
#define VLOWV3P5 1
#define VLOWV3P6 2
#define VLOWV3P7 3
// IINLIM [7:6]
#define IINLIM100 0
#define IINLIM500 1
#define IINLIM800 2
#define NOLIMIT 3

/********** FAN5405_REG_OREG (0x02) **********/
// OTG_EN [0]
#define DISOTG 0
#define ENOTG 1
// OTG_PL [1]
#define OTGACTIVELOW 0
#define OTGACTIVEHIGH 1
// OREG [7:2]
#define VOREG4P2 35  // refer to table 3

/********** FAN5405_REG_IC_INFO (0x03) **********/

/********** FAN5405_REG_IBAT (0x04) **********/
// ITERM [2:0] - 68mOhm
#define ITERM49 0
#define ITERM97 1
#define ITERM146 2
#define ITERM194 3
#define ITERM243 4
#define ITERM291 5
#define ITERM340 6
#define ITERM388 7
// IOCHARGE [6:4] - 68mOhm
#define IOCHARGE550 0
#define IOCHARGE650 1
#define IOCHARGE750 2
#define IOCHARGE850 3
#define IOCHARGE1050 4
#define IOCHARGE1150 5
#define IOCHARGE1350 6
#define IOCHARGE1450 7

/********** FAN5405_REG_SP_CHARGER (0x05) **********/
// VSP [2:0]
#define VSP4P213 0
#define VSP4P293 1
#define VSP4P373 2
#define VSP4P453 3
#define VSP4P533 4
#define VSP4P613 5
#define VSP4P693 6
#define VSP4P773 7
// IO_LEVEL [5]
#define ENIOLEVEL 0
#define DISIOLEVEL 1
// DIS_VREG [6]
#define VREGON 0
#define VREGOFF 1

/********** FAN5405_REG_SAFETY (0x06) **********/
// VSAFE [3:0]
#define VSAFE4P20 0
#define VSAFE4P22 1
#define VSAFE4P24 2
#define VSAFE4P26 3
#define VSAFE4P28 4
#define VSAFE4P30 5
#define VSAFE4P32 6
#define VSAFE4P34 7
#define VSAFE4P36 8
#define VSAFE4P38 9
#define VSAFE4P40 10
#define VSAFE4P42 11
#define VSAFE4P44 12
// ISAFE [6:4] - 68mOhm
#define ISAFE550 0
#define ISAFE650 1
#define ISAFE750 2
#define ISAFE850 3
#define ISAFE1050 4
#define ISAFE1150 5
#define ISAFE1350 6
#define ISAFE1450 7


#define mdelay(t)	({unsigned long msec=(t); while (msec--) { udelay(1000);}})
//#define msleep(ms) udelay(ms*1000)

typedef unsigned char BYTE;

static int fan5405_ReadReg(int reg);


static I2C_DEV i2c_fan5405_bridge = {
	.id = 3,
	.freq = 100*1000,
	.bus = 2,
	.slave_addr = 0xd4,
	.reg_addr_num = 1,
	.check_ack = 1,
	.no_stop = 0,
};


static int reset_flag = 0;      // use when assert reset


static const BYTE fan5405_def_reg[17] = {
    0x40,    // #0x00(CONTROL0)
    0x30,    // #0x01(CONTROL1)
    0x0a,    // #0x02(OREG)
    0x84,    // #0x03(IC_INFO)
    0x09,    // #0x04(IBAT) default is 0x89 but writing 1 to IBAT[7] resets charge parameters, except the safety reg, so
    0x24,    // #0x05(SP_CHARGER)
    0x40,    // #0x06(SAFETY)
    0x00,    // #0x07 - unused
    0x00,    // #0x08 - unused
    0x00,    // #0x09 - unused
    0x00,    // #0x0a - unused
    0x00,    // #0x0b - unused
    0x00,    // #0x0c - unused
    0x00,    // #0x0d - unused
    0x00,    // #0x0e - unused
    0x00,    // #0x0f - unused
    0x00,    // #0x10(MONITOR)
};

static BYTE fan5405_curr_reg[17];

static int fan54015_init_flag = 0;
static int count = 0;

static int32 handle = 0;


void sprd_ext_charger_disable(int disable)
{
	sprd_gpio_request(NULL,219);
	sprd_gpio_direction_output(NULL, 219, disable);

	mdelay(20);
	sprd_gpio_set(NULL, 219, disable);
}

extern int sprd_charger_is_adapter(void);
enum sprd_adapter_type {
	ADP_TYPE_UNKNOW = 0,	//unknow adapter type
	ADP_TYPE_CDP = 1,	//Charging Downstream Port,USB&standard charger
	ADP_TYPE_DCP = 2,	//Dedicated Charging Port, standard charger
	ADP_TYPE_SDP = 4,	//Standard Downstream Port,USB and nonstandard charge
};

void sprd_ext_charger_init(void)
{
	int i = 0;
	enum sprd_adapter_type adp_type = sprd_charger_is_adapter();
	if(fan54015_init_flag == 0){
		fan5405_Initialization();
		if(adp_type == ADP_TYPE_CDP || adp_type == ADP_TYPE_DCP){
			printf("charge start with AC\n");
			fan5405_TA_StartCharging();
			}
		else{
			printf("charge start with USB\n");
			fan5405_USB_StartCharging();
			}
		fan54015_init_flag = 1;
		}

	count ++;
	if(count == 10){
		count = 0;
		fan5405_Reset32sTimer();
		}
	for( i; i<7; i++){
		printf("read uboot ext ic i2c reg[%d] = 0x%x\n", i ,fan5405_ReadReg(i));
	}

	return;
}


uint16_t sprd_fan54015_i2c_init(void)
{
	handle = I2C_HAL_Open(&i2c_fan5405_bridge);
	return 1;
}

uint16_t sprd_fan54015_i2c_uninit(void)
{
	I2C_HAL_Close(handle);
	return 1;
}


void sprd_ext_charger_uninit(void)
{
	sprd_fan54015_i2c_uninit();
}


//pengwei added for i2c read error
static int read_err_flag = 0;
static int write_error_count = 0;
static int read_err_count = 0;


static int fan5405_WriteReg(int reg, int val)
{
    int ret;
	printf("####uboot low power fan54015 write reg = %d val = %d ,handle =%d\n",reg,val,handle);

	ret = I2C_HAL_Write(handle, &reg, &val, 1);
	if (ret < 0)
		write_error_count ++;
		printf("%s: error = %d ,write error time is %d\n", __func__, ret ,write_error_count);

	if((reset_flag == 1) ||
		((reg == FAN5405_REG_IBAT) && (val & FAN5405_RESET)))
	{
	    memcpy(fan5405_curr_reg,fan5405_def_reg,6);  // resets charge paremeters, except the safety register(#6)
	    reset_flag = 0;
	}
	else
	{
	    fan5405_curr_reg[reg] = val;
	}

    return ret;
}

static void fan5405_SetValue(BYTE reg, BYTE reg_bit,BYTE reg_shift, BYTE val)
	{
		BYTE tmp;
		tmp = fan5405_curr_reg[reg] & (~reg_bit);
		printf("test value of i2c fan5405_curr_reg[%d] = 0x%x , temp = %d\n",reg,fan5405_curr_reg[reg],tmp);
		tmp |= (val << reg_shift);
		printf("continue test tmp =0x%x\n",tmp);
		if(reg_bit == FAN5405_RESET)
		{
			reset_flag = 1;
		}
		fan5405_WriteReg(reg,tmp);
	}


static int fan5405_ReadReg(int reg)
{
    int ret;
	uint8_t value = 0xFF;
	ret = I2C_HAL_Read(handle, &reg, &value, 1);
	printf("######fan5405_readreg reg = %d value =%d ret =%d read_err_count = %d\n",reg,value,ret,read_err_count);
	if (ret < 0)
		{
		read_err_flag = 1;
		read_err_count ++;
		}


    return value;
}


static BYTE fan5405_GetValue(BYTE reg, BYTE reg_bit, BYTE reg_shift)
{
	BYTE tmp,ret;

	tmp = (BYTE)fan5405_ReadReg(reg);
	ret = (tmp & reg_bit) >> reg_shift;

	return ret;
}


void fan5405_USB_StartCharging(void)
{
	printf("uboot fan54015 enter USB charging fan5405\n");
    fan5405_SetValue(FAN5405_REG_IBAT, FAN5405_IOCHARGE,FAN5405_IOCHARGE_SHIFT, IOCHARGE550);  //550mA
    fan5405_SetValue(FAN5405_REG_IBAT, FAN5405_ITERM, FAN5405_ITERM_SHIFT,ITERM194);  //194mA
    fan5405_SetValue(FAN5405_REG_CONTROL1, FAN5405_IINLIM,FAN5405_IINLIM_SHIFT, IINLIM500);  // limit 500mA (default)
    fan5405_SetValue(FAN5405_REG_CONTROL1, FAN5405_TE,FAN5405_TE_SHIFT, ENTE);
    fan5405_SetValue(FAN5405_REG_CONTROL1, FAN5405_CE_N,FAN5405_CE_N_SHIFT, ENCHARGER);
}


void fan5405_TA_StartCharging(void)
{
	printf("uboot fan54015 enter TA charging fan5405\n");
    fan5405_SetValue(FAN5405_REG_IBAT, FAN5405_IOCHARGE,FAN5405_IOCHARGE_SHIFT, IOCHARGE1450);  //1050mA
    fan5405_SetValue(FAN5405_REG_IBAT, FAN5405_ITERM,FAN5405_ITERM_SHIFT, ITERM97);  //97ma
    fan5405_SetValue(FAN5405_REG_CONTROL1, FAN5405_IINLIM, FAN5405_IINLIM_SHIFT,NOLIMIT);  // no limit
    fan5405_SetValue(FAN5405_REG_CONTROL1, FAN5405_TE,FAN5405_TE_SHIFT, ENTE);
    fan5405_SetValue(FAN5405_REG_CONTROL1, FAN5405_CE_N,FAN5405_CE_N_SHIFT, ENCHARGER);
}



void fan5405_Initialization(void)
{
    memcpy(fan5405_curr_reg,fan5405_def_reg,sizeof(fan5405_curr_reg));
	printf("fan5405init\n");
	sprd_fan54015_i2c_init();
//reg 6
	fan5405_SetValue(FAN5405_REG_SAFETY, FAN5405_VSAFE,FAN5405_VSAFE_SHIFT, VSAFE4P20);  // VSAFE = 4.20V
	fan5405_SetValue(FAN5405_REG_SAFETY, FAN5405_ISAFE, FAN5405_ISAFE_SHIFT, ISAFE1450);  // ISAFE = 1050mA (68mOhm)
//reg 1
	fan5405_SetValue(FAN5405_REG_CONTROL1, FAN5405_VLOWV, FAN5405_VLOWV_SHIFT,VLOWV3P4);  // VLOWV = 3.4V
	fan5405_SetValue(FAN5405_REG_CONTROL1, FAN5405_IINLIM, FAN5405_IINLIM_SHIFT,IINLIM500);  // INLIM = 500mA
//reg 2
	fan5405_SetValue(FAN5405_REG_OREG, FAN5405_OREG,FAN5405_OREG_SHIFT, VOREG4P2);  //OREG = 4.20V
//reg 5
	fan5405_SetValue(FAN5405_REG_SP_CHARGER, FAN5405_IO_LEVEL,FAN5405_IO_LEVEL_SHIFT, ENIOLEVEL);  //IO_LEVEL is 0. Output current is controlled by IOCHARGE bits.

}

void fan5405_Reset32sTimer(void)
{
	printf("fan 5405 reset rimer\n");
    fan5405_SetValue(FAN5405_REG_CONTROL0, FAN5405_TMR_RST_OTG,FAN5405_TMR_RST_OTG_SHIFT, RESET32S);
}


