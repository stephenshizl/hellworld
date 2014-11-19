/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/adi.h>
#include "asm/arch/efuse_drv.h"

#ifndef REG32
#define REG32(x)							(*((volatile uint32 *)(x)))
#endif

#if defined(CONFIG_SPX15)
static int idx = 0;
#define EFUSE_CONTROLLER_NUM	2

#undef SPRD_UIDEFUSE_PHYS
#define SPRD_UIDEFUSE_PHYS		(0x40240000 + idx * 0x100)
#endif


#define EFUSE_REGISTER_DUMP
static void efuse_dump(void)
{
#if defined(EFUSE_REGISTER_DUMP)
	printf("----------------- efuse dump start --------------------------------\n");

	printf("Efuse base addr = 0x%08x\n", SPRD_UIDEFUSE_PHYS);
	printf("REG_EFUSE_DATA_RD = 0x%08x\n", REG32(EFUSE_DATA_RD));
	printf("REG_EFUSE_DATA_WR = 0x%08x\n", REG32(EFUSE_DATA_WR));
	printf("REG_EFUSE_BLOCK_INDEX = 0x%08x\n", REG32(EFUSE_BLOCK_INDEX));
	printf("REG_EFUSE_MODE_CTRL = 0x%08x\n", REG32(EFUSE_MODE_CTRL));
	printf("REG_EFUSE_PGM_PARA = 0x%08x\n", REG32(EFUSE_PGM_PARA));
	printf("REG_EFUSE_STATUS = 0x%08x\n", REG32(EFUSE_STATUS));
	printf("REG_EFUSE_BLK_FLAGS = 0x%08x\n", REG32(EUSE_MEM_BLOCK_FLAGS));
	printf("REG_EFUSE_BLK_CLR = 0x%08x\n", REG32(EUSE_MEM_BLOCK_FLAGS_CLR));
	printf("REG_EFUSE_MAGIC_NUMBER = 0x%08x\n", REG32(EFUSE_MAGIC_NUMBER));

	printf("REG_AON_APB_APB_EB0 = 0x%08x\n", REG32(REG_AON_APB_APB_EB0));
	printf("REG_AON_APB_PWR_CTRL = 0x%08x\n", REG32(REG_AON_APB_PWR_CTRL));

	printf("----------------- efuse dump end --------------------------------\n");
#endif
}

static inline void efuse_udelay(unsigned long usec)
{
	unsigned long i;
	for (i = 0; i < (usec << 1); i++);
}

//static void __iomem *ctl_efuse_base = 0;
void sci_efuse_poweron(void)
{
	uint32 i = 0;
	/* enable efuse clock */
	REG32(REG_AON_APB_APB_EB0)  |= BIT_EFUSE_EB;

	// efuse reset
	REG32(REG_AON_APB_APB_RST0) |=  BIT_EFUSE_SOFT_RST;
	for(i = 0; i < 100; i++);
	REG32(REG_AON_APB_APB_RST0) &= ~BIT_EFUSE_SOFT_RST;

	/* power on effuse */
	REG32(EFUSE_PGM_PARA) |= BIT_EFS_VDD_ON;
	REG32(EFUSE_PGM_PARA) |= BIT_CLK_EFS_EN;
}

void sci_efuse_poweroff(void)
{
	REG32(EFUSE_PGM_PARA) &= ~BIT_CLK_EFS_EN;
	REG32(EFUSE_PGM_PARA) &= ~BIT_EFS_VDD_ON;
	REG32(REG_AON_APB_APB_EB0)  &= ~BIT_EFUSE_EB;
}

int sci_efuse_read(unsigned blk)
{
	int busy = 0;
	uint32 reg_val = 0;

#if defined(CONFIG_SPX15)
	idx = blk / 8;
	blk %= 8;

	if(idx >= EFUSE_CONTROLLER_NUM) {
		printf("%s()->Line:%d; efuse idx: %d exceed maximum!\n", __func__, __LINE__, idx);
		return 0;
	}
#endif

	sci_efuse_poweron();

	if (blk > (MASK_READ_INDEX >> SHIFT_READ_INDEX))
	{
		return 0;
	}

	REG32(EFUSE_BLOCK_INDEX) = BITS_READ_INDEX(blk);
	REG32(EFUSE_MODE_CTRL) |= BIT_RD_START;

	efuse_dump();

	do
	{
		busy = REG32(EFUSE_STATUS) & BIT_READ_BUSY;
	} while (busy);

	reg_val = REG32(EFUSE_DATA_RD);

	sci_efuse_poweroff();

#if defined(CONFIG_SPX15)
	printf("%s()->Line:%d; efuse idx=%d; blk=%d; data=0x%08x;\n", __func__, __LINE__, idx, blk, reg_val);
#else
	printf("%s()->Line:%d; efuse blk=%d; data=0x%08x;\n", __func__, __LINE__, blk, reg_val);
#endif

	return reg_val;
}

#ifdef EFUSE_DEBUG
#define EFUSE_MAGIC_VAL				0x8810
int sci_efuse_program(unsigned blk, int data)
{
	int busy = 0;

#if defined(CONFIG_SPX15)
	idx = blk / 8;
	blk %= 8;

	if(idx >= EFUSE_CONTROLLER_NUM) {
		printf("%s()->Line:%d; efuse idx: %d exceed maximum!\n", __func__, __LINE__, idx);
		return 0;
	}
#endif

	if (blk > (MASK_PGM_INDEX >> SHIFT_PGM_INDEX))
	{
		return 0;
	}

	REG32(EFUSE_BLOCK_INDEX) = BITS_PGM_INDEX(blk);
	REG32(EFUSE_DATA_WR) = data;
	REG32(EFUSE_MODE_CTRL) |= BIT_PG_START;

	do
	{
		busy = REG32(EFUSE_STATUS) & BIT_PGM_BUSY;
	} while(busy);

	return 1;
}

/* low level */
int sci_efuse_raw_write(unsigned blk, int data, u32 magic)
{
	int retVal;

	REG32(REG_AON_APB_PWR_CTRL) |= BIT_EFUSE0_PWR_ON;
	REG32(REG_AON_APB_PWR_CTRL) |= BIT_EFUSE1_PWR_ON;

	REG32(EFUSE_PGM_PARA) |= BIT_PGM_EN;
	REG32(EFUSE_MAGIC_NUMBER) = BITS_MAGIC_NUMBER(magic);

	delay(10000);

	retVal = sci_efuse_program(blk, data);
	REG32(EFUSE_PGM_PARA) &= ~BIT_PGM_EN;

	return retVal;
}
#else
int sci_efuse_program(unsigned blk, int data)
{
	return 0;
}

int sci_efuse_raw_write(unsigned blk, int data, u32 magic)
{
	return 0;
}
#endif

#define CAL_DATA_BLK					7
#define BASE_ADC_P0						711			/* 3.6V */
#define BASE_ADC_P1						830			/* 4.2V */
#define VOL_P0							3600
#define VOL_P1							4200
#define ADC_DATA_OFFSET					128
/* they were stored in afuse of shark*/
int sci_efuse_calibration_get(unsigned int * p_cal_data)
{
	int timeout;
	unsigned int data;
	unsigned short adc_temp;
#if defined(CONFIG_SPX15)
	data = sci_efuse_read(CAL_DATA_BLK);
#elif !(defined(CONFIG_ADIE_SC2723) || defined(CONFIG_ADIE_SC2723S))
	/* wait for maximum of 100 msec */
	sci_adi_raw_write(ANA_REG_GLB_AFUSE_CTRL, BIT_AFUSE_READ_REQ);
	efuse_udelay(1);
	timeout = 1000;
	while(BIT_AFUSE_READ_REQ & sci_adi_read(ANA_REG_GLB_AFUSE_CTRL)) {
		if(timeout <= 0){
			break;
		}
		efuse_udelay(500);
		timeout--;
	}

	if (timeout <= 0)
	{
		return 0;
	}

	data = sci_adi_read(ANA_REG_GLB_AFUSE_OUT0);
	data |= (sci_adi_read(ANA_REG_GLB_AFUSE_OUT1)) << 16;
#endif

	if (data == 0)
	{
		return 0;
	}

	printf("afuse: data = 0x%x\n\r",data);
	/* adc 3.6V  */
	adc_temp = ((data & 0xFF00) >> 8) + BASE_ADC_P0 - ADC_DATA_OFFSET;
	p_cal_data[1] = (VOL_P0) | ((adc_temp << 2) << 16);

	/* adc 4.2V */
	adc_temp = (data & 0xFF) + BASE_ADC_P1 - ADC_DATA_OFFSET;
	p_cal_data[0] = (VOL_P1)|((adc_temp << 2) << 16);
	return 1;
}

