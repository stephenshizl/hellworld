#include <asm/arch/sci_types.h>
#include <asm/arch/adi_hal_internal.h>
#include <asm/arch/chip_drv_common_io.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/low_power.h>

//#define LDO_SLP_DEBUG
#ifdef LDO_SLP_DEBUG
typedef struct slp_test {
	unsigned int						reg;
	unsigned int						val;
}test_t;
test_t b[60] = {0x0};

void test_store (test_t *buf)
{
	unsigned int i = 0, j = 0;
	buf[i].reg = ANA_REG_GLB_LDO_PD_CTRL;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_LDO_PD_CTRL);

	buf[i].reg = ANA_REG_GLB_LDO_SLP_CTRL0;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_LDO_SLP_CTRL0);

	buf[i].reg = ANA_REG_GLB_LDO_SLP_CTRL1;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_LDO_SLP_CTRL1);

	buf[i].reg = ANA_REG_GLB_LDO_SLP_CTRL2;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_LDO_SLP_CTRL2);

	buf[i].reg = ANA_REG_GLB_LDO_SLP_CTRL3;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_LDO_SLP_CTRL3);

	buf[i].reg = ANA_REG_GLB_PWR_XTL_EN0;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_PWR_XTL_EN0);

	buf[i].reg = ANA_REG_GLB_PWR_XTL_EN1;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_PWR_XTL_EN1);

	buf[i].reg = ANA_REG_GLB_PWR_XTL_EN2;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_PWR_XTL_EN2);

	buf[i].reg = ANA_REG_GLB_PWR_XTL_EN3;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_PWR_XTL_EN3);

	buf[i].reg = ANA_REG_GLB_PWR_XTL_EN4;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_PWR_XTL_EN4);

	buf[i].reg = ANA_REG_GLB_PWR_XTL_EN5;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_PWR_XTL_EN5);

	buf[i].reg = ANA_REG_GLB_LDO1828_XTL_CTL;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_LDO1828_XTL_CTL);

	buf[i].reg = ANA_REG_GLB_SLP_WAIT_DCDCARM;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_SLP_WAIT_DCDCARM);

	buf[i].reg = REG_PMU_APB_XTL0_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_XTL0_REL_CFG);

	buf[i].reg = REG_PMU_APB_XTL1_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_XTL1_REL_CFG);

	buf[i].reg = REG_PMU_APB_XTL2_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_XTL2_REL_CFG);

	buf[i].reg = REG_PMU_APB_XTLBUF0_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_XTLBUF0_REL_CFG);

	buf[i].reg = REG_PMU_APB_XTLBUF1_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_XTLBUF1_REL_CFG);

	buf[i].reg = REG_PMU_APB_MPLL_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_MPLL_REL_CFG);

	buf[i].reg = REG_PMU_APB_DPLL_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_DPLL_REL_CFG);

	buf[i].reg = REG_PMU_APB_TDPLL_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_TDPLL_REL_CFG);

	buf[i].reg = REG_PMU_APB_WPLL_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_WPLL_REL_CFG);

	buf[i].reg = REG_PMU_APB_CPLL_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_CPLL_REL_CFG);

	buf[i].reg = REG_PMU_APB_WIFIPLL1_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_WIFIPLL1_REL_CFG);

	buf[i].reg = REG_PMU_APB_WIFIPLL2_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_WIFIPLL2_REL_CFG);

//	buf[i].reg = REG_PMU_APB_CGM_AP_EN;
//	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_CGM_AP_EN);

	buf[i].reg = REG_PMU_APB_PD_CA7_TOP_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_PD_CA7_TOP_CFG);

	buf[i].reg = REG_PMU_APB_PD_CA7_C0_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_PD_CA7_C0_CFG);

	buf[i].reg = REG_PMU_APB_PD_CA7_C1_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_PD_CA7_C1_CFG);

	buf[i].reg = REG_PMU_APB_PD_CA7_C2_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_PD_CA7_C2_CFG);

	buf[i].reg = REG_PMU_APB_PD_CA7_C3_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_PD_CA7_C3_CFG);

	buf[i].reg = REG_PMU_APB_PD_AP_SYS_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_PD_AP_SYS_CFG);

	buf[i].reg = REG_PMU_APB_PD_MM_TOP_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_PD_MM_TOP_CFG);

	buf[i].reg = REG_PMU_APB_PD_GPU_TOP_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_PD_GPU_TOP_CFG);

	buf[i].reg = REG_PMU_APB_PD_PUB_SYS_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_PD_PUB_SYS_CFG);

	buf[i].reg = REG_PMU_APB_XTL_WAIT_CNT;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_XTL_WAIT_CNT);

	buf[i].reg = REG_PMU_APB_XTLBUF_WAIT_CNT;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_XTLBUF_WAIT_CNT);

	buf[i].reg = REG_PMU_APB_PLL_WAIT_CNT1;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_PLL_WAIT_CNT1);

	buf[i].reg = REG_PMU_APB_PLL_WAIT_CNT2;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_PLL_WAIT_CNT2);


	buf[i].reg = i;
	buf[i].val = 0x55AA55AA;

	for(j = 0; j < i; j++) {
		printf("addr:0x%.8x, val:0x%.8x\n",buf[j].reg,buf[j].val);
	}
}
#endif

static struct ldo_lowpower_cfg *gp_ldo_cfg = NULL;
static struct pll_cfg *gp_pll_cfg = NULL;
static struct shutdown_cfg *gp_shutdown_cfg = NULL;

void customize_low_power_init_prepare(struct ldo_lowpower_cfg *ldo,
								struct pll_cfg *pll,
								struct shutdown_cfg *shutdown)
{
	gp_ldo_cfg = ldo;
	gp_pll_cfg = pll;
	gp_shutdown_cfg = shutdown;
}

static void switch_protect(unsigned int rf_id)
{
   unsigned int pll_reg;
/* before switch reference crystal, it must be sure that no module is using TDPLL */
    pll_reg = CHIP_REG_GET(REG_AP_CLK_AP_AHB_CFG);
    pll_reg &= ~AP_AHB_CLK_SEL_MASK;
    CHIP_REG_SET(REG_AP_CLK_AP_AHB_CFG,pll_reg);

    pll_reg = CHIP_REG_GET(REG_AON_CLK_PUB_AHB_CFG);
    pll_reg &= ~PUB_AHB_CLK_SEL_MASK;
    CHIP_REG_SET(REG_AON_CLK_PUB_AHB_CFG,pll_reg);

    pll_reg = CHIP_REG_GET(REG_AP_CLK_AP_APB_CFG);
    pll_reg &= ~AP_APB_CLK_SEL_MASK;
    CHIP_REG_SET(REG_AP_CLK_AP_APB_CFG,pll_reg);

    pll_reg = CHIP_REG_GET(REG_AON_CLK_AON_APB_CFG);
    pll_reg &= ~PUB_APB_CLK_SEL_MASK;
    CHIP_REG_SET(REG_AON_CLK_AON_APB_CFG,pll_reg);

    pll_reg = CHIP_REG_GET(REG_AON_APB_PLL_SOFT_CNT_DONE);
    pll_reg &= ~(BIT_TDPLL_SOFT_CNT_DONE);
    CHIP_REG_SET(REG_AON_APB_PLL_SOFT_CNT_DONE,pll_reg);
    udelay(1);

/* switch TDPLL reference crystal */
    if (rf_id == 0)
    {
        pll_reg = CHIP_REG_GET(REG_PMU_APB_TDPLL_REL_CFG);
        pll_reg &= ~(0x1 << 4);
        CHIP_REG_SET(REG_PMU_APB_TDPLL_REL_CFG,pll_reg);

        pll_reg = CHIP_REG_GET(REG_PMU_APB_XTL0_REL_CFG);
        pll_reg |= BIT_XTL1_AP_SEL;
        CHIP_REG_SET(REG_PMU_APB_XTL0_REL_CFG,pll_reg);

        pll_reg = CHIP_REG_GET(REG_PMU_APB_XTLBUF0_REL_CFG);
        pll_reg |= BIT_XTLBUF1_AP_SEL;
        CHIP_REG_SET(REG_PMU_APB_XTLBUF0_REL_CFG,pll_reg);
    }
    else if(rf_id == 1)
    {

        pll_reg = CHIP_REG_GET(REG_PMU_APB_TDPLL_REL_CFG);
        pll_reg |= (0x1 << 4);
        CHIP_REG_SET(REG_PMU_APB_TDPLL_REL_CFG,pll_reg);

        pll_reg = CHIP_REG_GET(REG_PMU_APB_XTL1_REL_CFG);
        pll_reg |= BIT_XTL1_AP_SEL;
        CHIP_REG_SET(REG_PMU_APB_XTL1_REL_CFG,pll_reg);

        pll_reg = CHIP_REG_GET(REG_PMU_APB_XTLBUF1_REL_CFG);
        pll_reg |= BIT_XTLBUF1_AP_SEL;
        CHIP_REG_SET(REG_PMU_APB_XTLBUF1_REL_CFG,pll_reg);


    }

    pll_reg = CHIP_REG_GET(REG_AON_APB_PLL_SOFT_CNT_DONE);
    pll_reg |= (BIT_TDPLL_SOFT_CNT_DONE);
    CHIP_REG_SET(REG_AON_APB_PLL_SOFT_CNT_DONE,pll_reg);

    udelay(120);

/* after switch, up ahb clock to 128M, APB to 64M */
    pll_reg = CHIP_REG_GET(REG_AP_CLK_AP_AHB_CFG);
    pll_reg |= 0x3;
    CHIP_REG_SET(REG_AP_CLK_AP_AHB_CFG,pll_reg);

    pll_reg = CHIP_REG_GET(REG_AON_CLK_PUB_AHB_CFG);
    pll_reg |= 0x3;
    CHIP_REG_SET(REG_AON_CLK_PUB_AHB_CFG,pll_reg);

    pll_reg = CHIP_REG_GET(REG_AP_CLK_AP_APB_CFG);
    pll_reg |= 0x1;
    CHIP_REG_SET(REG_AP_CLK_AP_APB_CFG,pll_reg);

    pll_reg = CHIP_REG_GET(REG_AON_CLK_AON_APB_CFG);
    pll_reg |= 0x3;
    CHIP_REG_SET(REG_AON_CLK_AON_APB_CFG,pll_reg);
    printf("switch_protect end\n");
}

static void lowpower_earlyinit(void)
{
//	ANA_REG_SET(REG_PMU_APB_PD_CP0_SYS_CFG, BIT_CP0_FORCE_DEEP_SLEEP);
//	ANA_REG_SET(REG_PMU_APB_PD_CP1_SYS_CFG, BIT_CP1_FORCE_DEEP_SLEEP);
//	ANA_REG_SET(REG_PMU_APB_PD_CP2_SYS_CFG, BIT_CP2_FORCE_DEEP_SLEEP);

	ANA_REG_SET(ANA_REG_GLB_LDO_SLP_CTRL0, BIT_SLP_IO_EN);
	ANA_REG_SET(ANA_REG_GLB_LDO_SLP_CTRL1, BIT_SLP_LDO_PD_EN);
	ANA_REG_SET(ANA_REG_GLB_PWR_XTL_EN0, BIT_LDO_XTL_EN);

	ANA_REG_SET(ANA_REG_GLB_SLP_WAIT_DCDCARM,0x0908);
//	ANA_REG_SET(REG_PMU_APB_CGM_AP_EN,0x1fff81 );

//	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD_RTCSET, 0xffff);
//	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD_RTCCLR, 0xffff);

//	switch_protect(1);
//	ANA_REG_SET(REG_PMU_APB_WPLL_REL_CFG,BIT_WPLL_REF_SEL);
//	ANA_REG_SET(REG_PMU_APB_TDPLL_REL_CFG,BIT_TDPLL_REF_SEL);
	/*plls wait, xtl0/1 wait, xtlbuf0/1 wait time*/
}

static unsigned long ffs(unsigned int x)
{
	unsigned long i = 0;
	if(x == 0)
		i = 32;
	else {
		while((x & (1<<i)) == 0) {
			i ++;
		}
		i++;
	}
	return i;
}

static unsigned long __ffs(unsigned int x)
{
	return ffs(x) -1;
}

/* pll */
static void pll_xtl_with_sys_config(struct pll_cfg *cfg, struct pll_reg_bit *pll_reg)
{
	/*enable all xtl for simply config.  xtlbuf0 is for ap, xtlbuf1 is for tdpll, choose!*/
	unsigned int i = 0, j;
	unsigned int sel_mode = 0, sel_tmp = 0;

	if ((!cfg) || (cfg[0].pll_id == RESERVED_NUM) || (pll_reg == NULL)) {
		return;
	}

	/*collecting the current system mode, like TD only ..etc.*/
	while (cfg[i].pll_id != RESERVED_NUM) {
		j = 0;
		while (pll_reg[j].pll_id != RESERVED_NUM) {
			if (cfg[i].pll_id == pll_reg[j].pll_id) {
				break;
			}
			++j;
		}

		sel_mode = 0;
		/* set select by ap,cp0,cp1,cp2 */
		if (pll_reg[j].pll_sys_reg != -1) {
			if(cfg[i].sys != DEFAULT) {
				if (cfg[i].sys & AP_SYS) {
					sel_mode |= BIT(0);
				}
				if (cfg[i].sys & CP0_SYS) {
					sel_mode |= BIT(1);
				}
				if (cfg[i].sys & CP1_SYS) {
					sel_mode |= BIT(2);
				}
				if (cfg[i].sys & CP2_SYS) {
					sel_mode |= BIT(3);
				}

				sel_tmp = CHIP_REG_GET(pll_reg[j].pll_sys_reg);
				sel_tmp &= ~pll_reg[j].pll_sys_reg_bitmsk;
				sel_tmp |= (sel_mode << __ffs(pll_reg[j].pll_sys_reg_bitmsk)
							& pll_reg[j].pll_sys_reg_bitmsk);

				CHIP_REG_SET(pll_reg[j].pll_sys_reg, sel_tmp);
			}
		}

		if (pll_reg[j].pll_wait_reg != -1) {
			if (cfg[i].wait != DEFAULT) {
				sel_mode = cfg[i].wait << __ffs(pll_reg[j].pll_wait_reg_bitmsk);
				sel_mode &= pll_reg[j].pll_wait_reg_bitmsk;

				sel_tmp = CHIP_REG_GET(pll_reg[j].pll_wait_reg);
				sel_tmp &= ~pll_reg[j].pll_wait_reg_bitmsk;
				sel_tmp |= sel_mode;

				CHIP_REG_SET(pll_reg[j].pll_wait_reg, sel_tmp);
			}
		}

		++i;
	}
}

static void pd_shutdown_config(struct shutdown_cfg *cfg,
						struct pd_reg_bit *pd_reg)
{
	/*enable all xtl for simply config.  xtlbuf0 is for ap, xtlbuf1 is for tdpll, choose!*/
	unsigned int i = 0, j;
	unsigned int reg_value = 0;

	if ((!cfg) || (cfg[0].pd_shutdown_id == RESERVED_NUM) || (pd_reg == NULL)) {
		return;
	}

	/*collecting the current system mode, like TD only ..etc.*/
	while (cfg[i].pd_shutdown_id != RESERVED_NUM) {
		j = 0;
		while (pd_reg[j].pd_shutdown_id != RESERVED_NUM) {
			if (cfg[i].pd_shutdown_id == pd_reg[j].pd_shutdown_id) {
				break;
			}
			++j;
		}

		if (pd_reg[j].pd_shutdown_id == RESERVED_NUM) {
			continue;
		}

		if (pd_reg[j].pd_reg != -1) {
			if(cfg[i].iso_on_delay != DEFAULT) {
				reg_value = cfg[i].iso_on_delay << __ffs(pd_reg[j].iso_on_delay_bitmsk);
				CHIP_REG_AND(pd_reg[j].pd_reg, ~pd_reg[j].iso_on_delay_bitmsk);
				CHIP_REG_OR(pd_reg[j].pd_reg, reg_value);
			}

			if(cfg[i].pwr_on_seq_delay != DEFAULT) {//pwr_on_seq_delay
				reg_value = cfg[i].pwr_on_seq_delay
							<< __ffs(pd_reg[j].pwr_on_seq_delay_bitmsk);
				CHIP_REG_AND(pd_reg[j].pd_reg, ~pd_reg[j].pwr_on_seq_delay_bitmsk);
				CHIP_REG_OR(pd_reg[j].pd_reg, reg_value);
			}

			if(cfg[i].pwr_on_delay != DEFAULT) {//pwr_on_delay
				reg_value = cfg[i].pwr_on_delay << __ffs(pd_reg[j].pwr_on_delay_bitmsk);
				CHIP_REG_AND(pd_reg[j].pd_reg, ~pd_reg[j].pwr_on_delay_bitmsk);
				CHIP_REG_OR(pd_reg[j].pd_reg,reg_value);
			}

			if(cfg[i].auto_shutdown != DEFAULT) {
				if(cfg[i].auto_shutdown == ENABLE) {//auto_shutdown
					CHIP_REG_OR(pd_reg[j].pd_reg, pd_reg[j].auto_shutdown_bitmsk);
				}
				else if(cfg[i].auto_shutdown == DISABLE) {
					CHIP_REG_AND(pd_reg[j].pd_reg, ~pd_reg[j].auto_shutdown_bitmsk);
				}
			}

			if(cfg[i].force_shutdown != DEFAULT) {
				if(cfg[i].force_shutdown == ENABLE) {//force_shutdown
					CHIP_REG_OR(pd_reg[j].pd_reg, pd_reg[j].force_shutdown_bitmsk);
				}
				else if(cfg[i].force_shutdown == DISABLE) {
					CHIP_REG_AND(pd_reg[j].pd_reg, ~pd_reg[j].force_shutdown_bitmsk);
				}
			}

			if(cfg[i].debug_shutdown != DEFAULT) {
				if(cfg[i].debug_shutdown == ENABLE) {//debug_shutdown
					CHIP_REG_OR(pd_reg[j].pd_reg, pd_reg[j].debug_shutdown_bitmsk);
				}
				else if(cfg[i].debug_shutdown == DISABLE) {
					CHIP_REG_AND(pd_reg[j].pd_reg, ~(pd_reg[j].debug_shutdown_bitmsk));
				}
			}
		}
		++i;
	}
}

static void ddie_pll_lowpower_init(void)
{
	/*default all:xtl0/1/2 to ap, default all:xtlbuf0/1 to ap +*/
	pll_xtl_with_sys_config(gp_pll_cfg, pll_reg_tb);
	pd_shutdown_config(gp_shutdown_cfg, shutdown_tb);
}

/* ldo */

static  void ldo_set_sts(struct ldo_lowpower_cfg *cfg, struct ldo_reg_bit *reg)
{
	if (reg->ldo_pd_reg != -1) {
		if (cfg->ldo_pd == ON) {
			ANA_REG_OR(reg->ldo_pd_reg, reg->ldo_pd_reg_bitmsk);
		} else if (cfg->ldo_pd == OFF) {
			ANA_REG_BIC(reg->ldo_pd_reg, reg->ldo_pd_reg_bitmsk);
		}
	}
}

static  void ldo_set_sts_sleep(struct ldo_lowpower_cfg *cfg, struct ldo_reg_bit *reg)
{
	if (cfg->status_in_sleep == SLP_PD_MODE) {
		if (reg->slp_pd_reg != -1) {
			ANA_REG_OR(reg->slp_pd_reg, reg->slp_pd_reg_bitmsk);
		}
		if (reg->slp_lp_reg != -1) {
			ANA_REG_BIC(reg->slp_lp_reg, reg->slp_lp_reg_bitmsk);
		}
	} else if (cfg->status_in_sleep == SLP_LP_MODE) {
		if (reg->slp_pd_reg != -1) {
			ANA_REG_BIC(reg->slp_pd_reg, reg->slp_pd_reg_bitmsk);
		}
		if (reg->slp_lp_reg != -1) {
			ANA_REG_OR(reg->slp_lp_reg, reg->slp_lp_reg_bitmsk);
		}
	} else if (cfg->status_in_sleep == SLP_NO_MODE) {
		if (reg->slp_pd_reg != -1) {
			ANA_REG_BIC(reg->slp_pd_reg, reg->slp_pd_reg_bitmsk);
		}
		if (reg->slp_lp_reg != -1) {
			ANA_REG_BIC(reg->slp_lp_reg, reg->slp_lp_reg_bitmsk);
		}
	} else {
//		printf("error for this callback ldo_set_sts_sleep\n");
	}
}

/* ldo_id, cfg_to_xtl, cfg_to_ext_xtl,power_sts_in_sleep; */
static void ldo_set_xtl(struct ldo_lowpower_cfg *cfg, struct ldo_reg_bit *reg)
{
	unsigned int v = 0, tmp = 0;
	unsigned int shft = 0;

	if (reg->xtl_reg != -1) {
		shft = __ffs(reg->xtl_reg_bitmsk);

		if (cfg->select_by_xtl & BY_XTL0)
			v |= BIT(0);
		if (cfg->select_by_xtl & BY_XTL1)
			v |= BIT(1);
		if (cfg->select_by_xtl & BY_XTL2)
			v |= BIT(2);
		v = v << shft;
		v &= reg->xtl_reg_bitmsk;

		tmp = ANA_REG_GET(reg->xtl_reg);
		tmp &= ~reg->xtl_reg_bitmsk;
		tmp |= v;

		ANA_REG_SET(reg->xtl_reg, tmp);
	}
}

static  void ldo_set_exxtl(struct ldo_lowpower_cfg *cfg, struct ldo_reg_bit *reg)
{
	unsigned int v = 0, tmp = 0;
	unsigned int shft = 0;

	if (reg->ext_xtl_reg != -1) {
		shft = __ffs(reg->ext_xtl_reg_bitmsk);

		if (cfg->select_by_ext_xtl & BY_EXT_XTL0)
			v |= BIT(0);
		if (cfg->select_by_ext_xtl & BY_EXT_XTL1)
			v |= BIT(1);
		if (cfg->select_by_ext_xtl & BY_EXT_XTL2)
			v |= BIT(2);

		v = v << shft;
		v &= reg->ext_xtl_reg_bitmsk;

		tmp = ANA_REG_GET(reg->ext_xtl_reg);
		tmp &= ~reg->ext_xtl_reg_bitmsk;
		tmp |= v;

		ANA_REG_SET(reg->ext_xtl_reg, tmp);
	}
}

static void adie_ldo_lowpower_init()
{
	struct ldo_lowpower_cfg *ldo_cfg = gp_ldo_cfg;
	struct ldo_reg_bit *ldo_reg = ldo_reg_tb;
	unsigned int i = 0, j = 0;

	if ((!ldo_cfg) || (ldo_reg == NULL))
		return;

	while (ldo_cfg[i].ldo_id != RESERVED_NUM) {
		j = 0;
		while (ldo_reg[j].ldo_id != RESERVED_NUM) {
			if (ldo_cfg[i].ldo_id == ldo_reg[j].ldo_id) {
				break;
			}
			++j;
		}

		if (ldo_reg[j].ldo_id == RESERVED_NUM) {
			continue;
		}

		if (ldo_cfg[i].ldo_pd != DEFAULT) {
			ldo_set_sts(&ldo_cfg[i], &ldo_reg[j]);
		}
		if (ldo_cfg[i].status_in_sleep != DEFAULT) {
			ldo_set_sts_sleep(&ldo_cfg[i], &ldo_reg[j]);
		}
		if (ldo_cfg[i].select_by_xtl!= DEFAULT) {
			ldo_set_xtl(&ldo_cfg[i], &ldo_reg[j]);
		}
		if (ldo_cfg[i].select_by_ext_xtl != DEFAULT) {
			ldo_set_exxtl(&ldo_cfg[i], &ldo_reg[j]);
		}
		++i;
	}
}

void low_power_init(void)
{
	/*
	Every ldo LP/PD depend on AP, we can make ap select xtl_buf_en0, xtl_buf_en1,
	xtl_buf_en2 and cp0 select xtl_buf_en0, cp1 select xtl-buf_en1, cp2 select xtl_buf_en2, so
	ldo_x can flexiblly config to xtl0/cp0, xtl1/cp1, xtl2/cp2. But now, we can make this process
	to simple. make xtl_buf_en0 == xtl_buf_en1 == xtl_buf_en2
	if cp(X) is exist, slecet all xtl_Buf_en0/1/2.
	*/
	lowpower_earlyinit();
	ddie_pll_lowpower_init();
	adie_ldo_lowpower_init();

	/* used test register */
#ifdef LDO_SLP_DEBUG
	test_store(&b);
#endif
}
