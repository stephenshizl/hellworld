/*
 * This file is produced by tools!!
 *
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

#include <asm/io.h>
#include <asm/arch/pinmap.h>

static pinmap_t  ctrl[] = {
{REG_PIN_CTRL0,(3<<16)|0},
{REG_PIN_CTRL1,0},
{REG_PIN_CTRL2,(5<<20)|0},
{REG_PIN_CTRL3,0},
};

void pinctrl_init(void)
{
    int i;
    for (i = 0; i < sizeof(ctrl)/sizeof(ctrl[0]); i++) {
        __raw_writel(ctrl[i].val, CTL_PIN_BASE + ctrl[i].reg);
    }
}
