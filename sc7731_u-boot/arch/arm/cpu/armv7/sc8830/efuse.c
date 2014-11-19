/*
 * Copyright (C) 2014 Spreadtrum Communications Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/* IMPORTANT:
 * The electrical fuse is a type of non-volatile memory fabricated
 * in standard CMOS logic process. This electrical fuse macro is widely
 * used in chip ID, memory redundancy, security code, configuration setting,
 * and feature selection, etc.
 *
 * This efuse controller is designed for 32*32 bits electrical fuses,
 * support TSMC HPM 28nm product of "TEF28HPM32X32HD18_PHRM".
 *
 * and we default use double-bit, 512bits efuse are visiable for software.
 *
 * efuse driver ONLY support module ip version since from r3p0
 * which had integrated into scx30g and scx35l etc.
 *
 * TODO:
 * 1. do something when block had been locked with bit31 if need
 * 1. check and clear blk prog/err flag if need
 * 1. wait *300ms* for read/prog ready time-out
 * 1. only mutexlock and hwspinlock for efuse access sync with cp
 * 1. be care not do use efuse API in interrupt function
 * 1. no need soft reset after efuse read/prog and power on/off
 * 1. efuse block width should less than 8bits
 * 1. efuse block count should not bigger than 32! or not should expland the cached otp arrary
 * 1. support efuse DT info (version, blocks, ...) later
 * 1. there is no handle for efuse module removed
 */

#include <common.h>
#include <linux/types.h>
#include <linux/err.h>
#include <asm/io.h>
//#include <asm/arch/hardware.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sci.h>
#include <asm/arch/__regs_efuse.h>

#define pr_debug(args...)  printf(args)
#define pr_info() printf

#define WARN_ON(a)
u32 SCI_GetTickCount(void);
#define jiffies (SCI_GetTickCount()) /* return msec count */
#define msecs_to_jiffies(a) (a)
#define time_after(a,b)	((int)(b) - (int)(a) < 0)
#define cpu_relax()

static void msleep(u32 ms)
{
	u32 timeout = jiffies + ms;
	while(!time_after(jiffies, timeout)) {
		;
	}
}

#define REGS_EFUSE_BASE                 SPRD_UIDEFUSE_PHYS

#define EFUSE_BLOCK_MAX                 ( 16 )
#define EFUSE_BLOCK_WIDTH               ( 32 )	/* bit counts */

void efuse_lookat(void)
{
	volatile u32 *reg = (volatile u32 *)REGS_EFUSE_BASE;
	int cnt = 16;
	while(cnt--) {
		printf("[%p] = %08x\n", reg, *reg);
		reg++;
	}
	printf("\n");
}

static void efuse_lock(void)
{
}

static void efuse_unlock(void)
{
}

static void efuse_reset(void)
{
	/* should enable module before soft reset efuse */
	WARN_ON(!sci_glb_read(REG_AON_APB_APB_EB0, BIT_EFUSE_EB));
	sci_glb_set(REG_AON_APB_APB_RST0, BIT_EFUSE_SOFT_RST);
	udelay(5);
	sci_glb_clr(REG_AON_APB_APB_RST0, BIT_EFUSE_SOFT_RST);
}

/* FIXME: Set EFS_VDD_ON will open 0.9v static power supply for efuse memory,
 * before any operation towards to efuse memory this bit have to set to 1.
 * Once this bit is cleared, the efuse will go to power down mode.
 *
 * each time when EFS_VDD_ON changes, software should wait at least 1ms to let
 * VDD become stable.
 *
 * For VDDQ(1.8v) power, to prevent the overshot of VDDQ, a extra power switch
 * connected to ground are controlled by "EFS_VDDQ_K2_ON"
 */
void __efuse_power_on(void)
{
	u32 cfg0;
	sci_glb_set(REG_AON_APB_APB_EB0, BIT_EFUSE_EB);
	efuse_reset();
	cfg0 = __raw_readl((void *)REG_EFUSE_CFG0);
	cfg0 &= ~BIT_EFS_VDDQ_K1_ON;
	cfg0 |= BIT_EFS_VDD_ON | BIT_EFS_VDDQ_K2_ON;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	msleep(1);
}

void __efuse_power_off(void)
{
	u32 cfg0 = __raw_readl((void *)REG_EFUSE_CFG0);
	if (cfg0 & BIT_EFS_VDDQ_K1_ON) {
		cfg0 &= ~BIT_EFS_VDDQ_K1_ON;
		__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
		msleep(1);
	}

	cfg0 |= BIT_EFS_VDDQ_K2_ON;
	cfg0 &= ~BIT_EFS_VDD_ON;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	msleep(1);

	sci_glb_clr(REG_AON_APB_APB_EB0, BIT_EFUSE_EB);
}

static __inline int __efuse_wait_clear(u32 bits)
{
	int ret = 0;
	unsigned long timeout;

	pr_debug("wait %x\n", __raw_readl((void *)REG_EFUSE_STATUS));

	/* wait for maximum of 300 msec */
	timeout = jiffies + msecs_to_jiffies(300);
	while (__raw_readl((void *)REG_EFUSE_STATUS) & bits) {
		if (time_after(jiffies, timeout)) {
			WARN_ON(1);
			ret = -ETIMEDOUT;
			break;
		}
		cpu_relax();
	}
	return ret;
}

static u32 __efuse_read(int blk)
{
	u32 val = 0;

	/* enable efuse module clk and power before */

	__raw_writel(BITS_READ_WRITE_INDEX(blk),
		     (void *)REG_EFUSE_READ_WRITE_INDEX);
	__raw_writel(BIT_RD_START, (void *)REG_EFUSE_MODE_CTRL);

	if (IS_ERR_VALUE(__efuse_wait_clear(BIT_READ_BUSY)))
		goto out;

	val = __raw_readl((void *)REG_EFUSE_DATA_RD);

out:
	return val;
}

static u32 efuse_read(int blk_index)
{
	u32 val;
	pr_debug("efuse read %d\n", blk_index);
	efuse_lock();

	__efuse_power_on();
	val = __efuse_read(blk_index);
	__efuse_power_off();

	efuse_unlock();
	return val;
}

u32 __ddie_efuse_read(int blk_index)
{
	return efuse_read(blk_index);
}
//EXPORT_SYMBOL_GPL(__ddie_efuse_read);

void __ddie_efuse_block_dump(void)
{
	int idx;
	printf("ddie efuse base %08x\n", REGS_EFUSE_BASE);
	printf("ddie efuse blocks dump:\n");
	for (idx = 0; idx < EFUSE_BLOCK_MAX; idx++) {
		printf("[%02d] %08x\n", idx, __ddie_efuse_read(idx));
	}
}
