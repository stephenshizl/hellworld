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
test_t b[60];

void test_store (test_t *buf)
{
	unsigned int i = 0;

	buf[i].reg = ANA_REG_GLB_PWR_WR_PROT_VALUE;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_PWR_WR_PROT_VALUE);

	buf[i].reg = ANA_REG_GLB_LDO_DCDC_PD;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_LDO_DCDC_PD);

	buf[i].reg = ANA_REG_GLB_DCDC_SLP_CTRL0;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_DCDC_SLP_CTRL0);

	buf[i].reg = ANA_REG_GLB_PWR_SLP_CTRL0;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_PWR_SLP_CTRL0);

	buf[i].reg = ANA_REG_GLB_PWR_SLP_CTRL1;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_PWR_SLP_CTRL1);

	buf[i].reg = ANA_REG_GLB_PWR_SLP_CTRL2;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_PWR_SLP_CTRL2);

	buf[i].reg = ANA_REG_GLB_PWR_SLP_CTRL3;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_PWR_SLP_CTRL3);

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
/*
	buf[i].reg = ANA_REG_GLB_PWR_XTL_EN3;
	buf[i++].val = CHIP_REG_GET(ANA_REG_GLB_PWR_XTL_EN3);
*/
	buf[i].reg = REG_PMU_APB_CPLL_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_CPLL_REL_CFG);

	buf[i].reg = REG_PMU_APB_WIFIPLL1_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_WIFIPLL1_REL_CFG);

	buf[i].reg = REG_PMU_APB_WIFIPLL2_REL_CFG;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_WIFIPLL2_REL_CFG);

	buf[i].reg = REG_PMU_APB_CGM_AP_EN;
	buf[i++].val = CHIP_REG_GET(REG_PMU_APB_CGM_AP_EN);

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

	buf[i].reg = ANA_REG_GLB_SLP_WAIT_DCDCARM;
	buf[i++].val = ANA_REG_GET(ANA_REG_GLB_SLP_WAIT_DCDCARM);

	buf[i].reg = i;
	buf[i].val = 0x55AA55AA;
}
#endif

static struct ldo_lowpower_cfg *gp_ldo_cfg = NULL;
static struct pll_cfg *gp_pll_cfg = NULL;
static struct shutdown_cfg *gp_shutdown_cfg = NULL;

/*********************************************************************
**	Description :
**		This function used to get customize information. if not get, don't running.
**	Param :
**		None
**	Return :
**		none
**	Date					Author				Operation
**	2014/01/23			ypxie				optimization
*********************************************************************/
void customize_low_power_init_prepare(struct ldo_lowpower_cfg *ldo,
								struct pll_cfg *pll,
								struct shutdown_cfg *shutdown)
{
	gp_ldo_cfg = ldo;
	gp_pll_cfg = pll;
	gp_shutdown_cfg = shutdown;
}

static void lowpower_earlyinit(void)
{
	unsigned int reg_val;

	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD,
				BIT_DCDC_TOP_CLKF_EN|BIT_DCDC_TOP_OSC_EN);

	ANA_REG_SET(ANA_REG_GLB_PWR_SLP_CTRL0, BIT_SLP_IO_EN);
	ANA_REG_SET(ANA_REG_GLB_PWR_SLP_CTRL1, BIT_SLP_LDO_PD_EN);
	ANA_REG_SET(ANA_REG_GLB_PWR_XTL_EN0, BIT_LDO_XTL_EN);
	CHIP_REG_SET(REG_PMU_APB_CGM_AP_EN,0x1FFF81);

	reg_val = ANA_REG_GET(ANA_REG_GLB_DCDC_SLP_CTRL0);
	reg_val &= ~BITS_DCDC_CORE_CTL_DS_SW(7);
	reg_val |= BITS_DCDC_CORE_CTL_DS_SW(4);
	ANA_REG_SET(ANA_REG_GLB_DCDC_SLP_CTRL0,reg_val);

	ANA_REG_SET(ANA_REG_GLB_SLP_WAIT_DCDCARM,0x0908);
	/*plls wait, xtl0/1 wait, xtlbuf0/1 wait time*/

	if (ANA_GET_CHIP_ID() != 0x2711a000) {
		CHIP_REG_SET(REG_AON_CLK_FM_CFG,
			//BIT_CLK_FM_PAD_SEL |
			//BIT_CLK_FM_SEL |
			0 );

		CHIP_REG_SET(REG_AON_APB_GPS_26M_REF_SEL,
			//BIT_XTLBUF1_GPS_SEL |
			BIT_XTLBUF0_GPS_SEL |
			//BIT_GPS_26M_REF_SEL |
			0 );
	}
}

static void wr_prot_dis(void)
{
	unsigned int reg_val = 0;

	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE,
				BITS_PWR_WR_PROT_VALUE(0x6e7f));

	do{
		reg_val = (ANA_REG_GET(ANA_REG_GLB_PWR_WR_PROT_VALUE)
				& BIT_PWR_WR_PROT);
	}while(reg_val == 0);
}

static void wr_prot_en(void)
{
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE, BITS_PWR_WR_PROT_VALUE(0));
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

		/* set xtl ref */
		if (pll_reg[j].cgm_ap_reg != -1) {
			if (cfg[i].cgm_ap_en != NO_USED) {
				if (cfg[i].cgm_ap_en == LP_EN) {
					CHIP_REG_OR(pll_reg[j].cgm_ap_reg, pll_reg[j].cgm_ap_reg_bitmsk);
				}
				else if (cfg[i].cgm_ap_en == LP_DIS){
					CHIP_REG_AND(pll_reg[j].cgm_ap_reg, ~(pll_reg[j].cgm_ap_reg_bitmsk));
				}
			}
		}

		sel_mode = 0;
		/* set select by ap,cp0,cp1,cp2 */
		if (pll_reg[j].pll_sys_reg != -1) {
			if(cfg[i].sys != NO_USED) {
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

				if (cfg[i].sys & REF_SYS) {
					sel_mode |= BIT(4);
				}

				sel_tmp = CHIP_REG_GET(pll_reg[j].pll_sys_reg);
				sel_tmp &= ~pll_reg[j].pll_sys_reg_bitmsk;
				sel_tmp |= (sel_mode << __ffs(pll_reg[j].pll_sys_reg_bitmsk)
							& pll_reg[j].pll_sys_reg_bitmsk);

				CHIP_REG_SET(pll_reg[j].pll_sys_reg, sel_tmp);
			}
		}

		if (pll_reg[j].pll_wait_reg != -1) {
			if (cfg[i].wait != NO_USED) {
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
			if(cfg[i].iso_on_delay != NO_USED) {
				reg_value = cfg[i].iso_on_delay << __ffs(pd_reg[j].iso_on_delay_bitmsk);
				CHIP_REG_AND(pd_reg[j].pd_reg, ~pd_reg[j].iso_on_delay_bitmsk);
				CHIP_REG_OR(pd_reg[j].pd_reg, reg_value);
			}

			if(cfg[i].pwr_on_seq_delay != NO_USED) {//pwr_on_seq_delay
				reg_value = cfg[i].pwr_on_seq_delay
							<< __ffs(pd_reg[j].pwr_on_seq_delay_bitmsk);
				CHIP_REG_AND(pd_reg[j].pd_reg, ~pd_reg[j].pwr_on_seq_delay_bitmsk);
				CHIP_REG_OR(pd_reg[j].pd_reg, reg_value);
			}

			if(cfg[i].pwr_on_delay != NO_USED) {//pwr_on_delay
				reg_value = cfg[i].pwr_on_delay << __ffs(pd_reg[j].pwr_on_delay_bitmsk);
				CHIP_REG_AND(pd_reg[j].pd_reg, ~pd_reg[j].pwr_on_delay_bitmsk);
				CHIP_REG_OR(pd_reg[j].pd_reg,reg_value);
			}

			if(cfg[i].auto_shutdown != NO_USED) {
				if(cfg[i].auto_shutdown == LP_EN) {//auto_shutdown
					CHIP_REG_OR(pd_reg[j].pd_reg, pd_reg[j].auto_shutdown_bitmsk);
				}
				else if(cfg[i].auto_shutdown == LP_DIS) {
					CHIP_REG_AND(pd_reg[j].pd_reg, ~pd_reg[j].auto_shutdown_bitmsk);
				}
			}

			if(cfg[i].force_shutdown != NO_USED) {
				if(cfg[i].force_shutdown == LP_EN) {//force_shutdown
					CHIP_REG_OR(pd_reg[j].pd_reg, pd_reg[j].force_shutdown_bitmsk);
				}
				else if(cfg[i].force_shutdown == LP_DIS) {
					CHIP_REG_AND(pd_reg[j].pd_reg, ~pd_reg[j].force_shutdown_bitmsk);
				}
			}

			if(cfg[i].debug_shutdown != NO_USED) {
				if(cfg[i].debug_shutdown == LP_EN) {//debug_shutdown
					CHIP_REG_OR(pd_reg[j].pd_reg, pd_reg[j].debug_shutdown_bitmsk);
				}
				else if(cfg[i].debug_shutdown == LP_DIS) {
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
		if (cfg->ldo_pd == LP_DIS) {
			ANA_REG_OR(reg->ldo_pd_reg, reg->ldo_pd_reg_bitmsk);
		} else if (cfg->ldo_pd == LP_EN) {
			ANA_REG_BIC(reg->ldo_pd_reg, reg->ldo_pd_reg_bitmsk);
		}
	}
}

static  void ldo_set_sts_sleep(struct ldo_lowpower_cfg *cfg, struct ldo_reg_bit *reg)
{
	if (cfg->status_in_sleep == SLP_PD_MODE) {
		if (reg->ldo_pd_reg != -1) {
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
		/* no xtl1 in 7715 */
		/*if (cfg->select_by_xtl & BY_XTL1)
			v |= BIT(1);*/
		if (cfg->select_by_xtl & BY_XTL2)
			v |= BIT(1);
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
		/* no xtl1 in 7715 */
		/*if (cfg->select_by_ext_xtl & BY_EXT_XTL2)
			v |= BIT(2);*/

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

		if (ldo_cfg[i].ldo_pd != NO_USED) {
			ldo_set_sts(&ldo_cfg[i], &ldo_reg[j]);
		}
		if (ldo_cfg[i].status_in_sleep != NO_USED) {
			ldo_set_sts_sleep(&ldo_cfg[i], &ldo_reg[j]);
		}
		if (ldo_cfg[i].select_by_xtl!= NO_USED) {
			ldo_set_xtl(&ldo_cfg[i], &ldo_reg[j]);
		}
		if (ldo_cfg[i].select_by_ext_xtl != NO_USED) {
			ldo_set_exxtl(&ldo_cfg[i], &ldo_reg[j]);
		}
		++i;
	}
}

/*********************************************************************
**	Description :
**		This function used to init low power. Before running this function, must be running
**		customize_low_power_init_prepare().
**	Param :
**		None
**	Return :
**		none
**	Date					Author				Operation
**	2014/01/23			ypxie				optimization
*********************************************************************/
void low_power_init(void)
{
	/*
	Every ldo LP/PD depend on AP, we can make ap select xtl_buf_en0, xtl_buf_en1,
	xtl_buf_en2 and cp0 select xtl_buf_en0, cp1 select xtl-buf_en1, cp2 select xtl_buf_en2, so
	ldo_x can flexiblly config to xtl0/cp0, xtl1/cp1, xtl2/cp2. But now, we can make this process
	to simple. make xtl_buf_en0 == xtl_buf_en1 == xtl_buf_en2
	if cp(X) is exist, slecet all xtl_Buf_en0/1/2.
	*/
	wr_prot_dis();
	lowpower_earlyinit();
	ddie_pll_lowpower_init();
	adie_ldo_lowpower_init();
	wr_prot_en();

	/* used test register */
	//test_store(&b);
}
