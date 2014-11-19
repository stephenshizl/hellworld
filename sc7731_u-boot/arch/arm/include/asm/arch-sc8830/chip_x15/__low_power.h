#ifndef __LOW_POWER_H__
#define __LOW_POWER_H__

/*ldo name*/
#define DCDC_BG						(1 << 0)
#define LDO_VDD18					(1 << 1)
#define LDO_VDD28					(1 << 2)
#define LDO_VDD25					(1 << 3)
#define LDO_CON						(1 << 4)
#define LDO_DCXO						(1 << 5)
#define LDO_EMMCIO					(1 << 6)
#define LDO_EMMCCORE				(1 << 7)
#define LDO_RF0						(1 << 8)
#define DCDC_CORE					(1 << 9)
#define DCDC_ARM					(1 << 10)
#define DCDC_MEM					(1 << 11)
#define DCDC_GEN						(1 << 12)
#define LDO_SD						(1 << 13)
#define LDO_SIM0						(1 << 14)
#define LDO_SIM1						(1 << 15)
#define LDO_SIM2						(1 << 16)
#define LDO_CAMA					(1 << 17)
#define LDO_CAMD					(1 << 18)
#define LDO_CAMIO					(1 << 19)
#define LDO_CAMMOT					(1 << 20)
#define LDO_USB						(1 << 21)
#define LDO_CLSG						(1 << 22)
#define DCDC_WPA					(1 << 23)
#define LDO_LPREF					(1 << 24)
#define LDO_XO						(1 << 25)
#define RESERVED_NUM				(-1)

#define NO_USED						(-2)/*for all no use*/
#define LP_DIS						(1)
#define LP_EN							(2)

#define BIT3(_X_)						((BIT(3)-1)<<(3*_X_))
#define BIT8(_X_)						((BIT(8)-1)<<(8*_X_))


//PLL
#define PLL_MPLL						(1 << 0)
#define PLL_DPLL						(1 << 1)
#define PLL_TDPLL						(1 << 2)
#define PLL_WPLL						(1 << 3)
#define PLL_CPLL						(1 << 4)
#define PLL_WIFIPLL1					(1 << 5)
#define PLL_WIFIPLL2					(1 << 6)
#define PLL_XTL0						(1 << 7)
#define PLL_XTL1						(1 << 8)
#define PLL_XTL2						(1 << 9)
#define PLL_XTLBUF0					(1 << 10)
#define PLL_XTLBUF1					(1 << 11)


#define PD_CA7_TOP					(1 << 0)
#define PD_CA7_C0					(1 << 1)
#define PD_CA7_C1					(1 << 2)
#define PD_CA7_C2					(1 << 3)
#define PD_CA7_C3					(1 << 4)
#define PD_AP_SYS					(1 << 5)
#define PD_MM_TOP					(1 << 6)
#define PD_GPU_TOP 					(1 << 7)
#define PD_PUB_SYS					(1 << 8)

/**
	some ldos can only controled by ap. for example(shark):
	ldo_cam/ldo_emmc/ldo_clsg/ldo_usb/ldo_sd

	All ldos lowpower mode and powerdown mode can triggered by ap(chip_sleep)
	signals.
*/
struct ldo_reg_bit {
	unsigned int						ldo_id;

	unsigned int						ldo_pd_reg;
	unsigned int						ldo_pd_reg_bitmsk;

	unsigned int						slp_pd_reg;
	unsigned int						slp_pd_reg_bitmsk;

	unsigned int						slp_lp_reg;
	unsigned int						slp_lp_reg_bitmsk;

	unsigned int						xtl_reg;
	unsigned int						xtl_reg_bitmsk;

	unsigned int						ext_xtl_reg;
	unsigned int						ext_xtl_reg_bitmsk;
};

static struct ldo_reg_bit ldo_reg_tb[] = {
	/* chip_id */		/* ldo_pd_reg */						/*slp_pd_reg*/						/*slp_lp_reg*/						/*xtl_reg*/								/*ext_xtl_reg*/
	{ DCDC_BG, 		ANA_REG_GLB_LDO_DCDC_PD, BIT(0),		-1, -1,								ANA_REG_GLB_PWR_SLP_CTRL3, BIT(15),	ANA_REG_GLB_PWR_XTL_EN3, BIT(0)|BIT(1),	ANA_REG_GLB_PWR_XTL_EN3, BIT(0)|BIT(1)	},
	{ LDO_VDD18,		ANA_REG_GLB_LDO_DCDC_PD, BIT(1), 	ANA_REG_GLB_PWR_SLP_CTRL0, BIT(0),	ANA_REG_GLB_PWR_SLP_CTRL2, BIT(0),	ANA_REG_GLB_PWR_XTL_EN0, BIT(4)|BIT(5),	ANA_REG_GLB_PWR_XTL_EN0, BIT(6)|BIT(7)	},
	{ LDO_VDD28,		ANA_REG_GLB_LDO_DCDC_PD, BIT(2), 	ANA_REG_GLB_PWR_SLP_CTRL0, BIT(1),	ANA_REG_GLB_PWR_SLP_CTRL2, BIT(1),	ANA_REG_GLB_PWR_XTL_EN0, BIT(0)|BIT(1),	ANA_REG_GLB_PWR_XTL_EN0, BIT(2)|BIT(3)	},
	{ LDO_VDD25,		ANA_REG_GLB_LDO_DCDC_PD, BIT(3), 	ANA_REG_GLB_PWR_SLP_CTRL0, BIT(2),	ANA_REG_GLB_PWR_SLP_CTRL2, BIT(2),	ANA_REG_GLB_PWR_XTL_EN1, BIT(4)|BIT(5),	ANA_REG_GLB_PWR_XTL_EN1, BIT(6)|BIT(7)	},
	{ LDO_CON,		ANA_REG_GLB_LDO_DCDC_PD, BIT(4), 	ANA_REG_GLB_PWR_SLP_CTRL0, BIT(3),	ANA_REG_GLB_PWR_SLP_CTRL2, BIT(3),	ANA_REG_GLB_PWR_XTL_EN1, BIT(0)|BIT(1),	ANA_REG_GLB_PWR_XTL_EN1, BIT(2)|BIT(3)	},
	{ LDO_DCXO,		ANA_REG_GLB_LDO_DCDC_PD, BIT(5), 	ANA_REG_GLB_PWR_SLP_CTRL0, BIT(4),	ANA_REG_GLB_PWR_SLP_CTRL2, BIT(4),	ANA_REG_GLB_PWR_XTL_EN0, BIT(8)|BIT(9),	ANA_REG_GLB_PWR_XTL_EN1, BIT(10)|BIT(11)	},
	{ LDO_EMMCIO,	ANA_REG_GLB_LDO_DCDC_PD, BIT(6), 	ANA_REG_GLB_PWR_SLP_CTRL0, BIT(5),	ANA_REG_GLB_PWR_SLP_CTRL2, BIT(5),	-1, -1,									-1, -1									},
	{ LDO_EMMCCORE,	ANA_REG_GLB_LDO_DCDC_PD, BIT(7), 	ANA_REG_GLB_PWR_SLP_CTRL0, BIT(6),	ANA_REG_GLB_PWR_SLP_CTRL2, BIT(6),	-1, -1,									-1, -1									},
	{ LDO_RF0,		ANA_REG_GLB_LDO_DCDC_PD, BIT(8), 	ANA_REG_GLB_PWR_SLP_CTRL0, BIT(7),	ANA_REG_GLB_PWR_SLP_CTRL2, BIT(7),	ANA_REG_GLB_PWR_XTL_EN1, BIT(8)|BIT(9),	ANA_REG_GLB_PWR_XTL_EN1, BIT(10)|BIT(11)	},
	{ DCDC_CORE,	ANA_REG_GLB_LDO_DCDC_PD, BIT(9), 	-1, -1,								ANA_REG_GLB_PWR_SLP_CTRL2, BIT(12),	ANA_REG_GLB_PWR_XTL_EN4, BIT(0)|BIT(1),	ANA_REG_GLB_PWR_XTL_EN4, BIT(2)|BIT(3)	},
	{ DCDC_ARM,		ANA_REG_GLB_LDO_DCDC_PD, BIT(10), 	ANA_REG_GLB_PWR_SLP_CTRL0, BIT(8),	ANA_REG_GLB_PWR_SLP_CTRL2, BIT(10),	-1, -1,									-1, -1									},
	{ DCDC_MEM,		ANA_REG_GLB_LDO_DCDC_PD, BIT(11), 	-1, -1,								ANA_REG_GLB_PWR_SLP_CTRL2, BIT(11),	ANA_REG_GLB_PWR_XTL_EN4, BIT(8)|BIT(9),	ANA_REG_GLB_PWR_XTL_EN4, BIT(10)|BIT(11)	},
	{ DCDC_GEN, 		ANA_REG_GLB_LDO_DCDC_PD, BIT(12),	ANA_REG_GLB_PWR_SLP_CTRL0, BIT(10),	ANA_REG_GLB_PWR_SLP_CTRL2, BIT(9),	ANA_REG_GLB_PWR_XTL_EN4, BIT(4)|BIT(5),	ANA_REG_GLB_PWR_XTL_EN4, BIT(6)|BIT(7)	},
	{ LDO_SD,		ANA_REG_GLB_LDO_PD_CTRL, BIT(0),	 	ANA_REG_GLB_PWR_SLP_CTRL1, BIT(0),	ANA_REG_GLB_PWR_SLP_CTRL3, BIT(0),	-1, -1,									-1, -1									},
	{ LDO_SIM0,		ANA_REG_GLB_LDO_PD_CTRL, BIT(1),	 	ANA_REG_GLB_PWR_SLP_CTRL1, BIT(1),	ANA_REG_GLB_PWR_SLP_CTRL3, BIT(1),	ANA_REG_GLB_PWR_XTL_EN2, BIT(0)|BIT(2),	ANA_REG_GLB_PWR_XTL_EN2, BIT(2)|BIT(3)	},
	{ LDO_SIM1,		ANA_REG_GLB_LDO_PD_CTRL, BIT(2),	 	ANA_REG_GLB_PWR_SLP_CTRL1, BIT(2),	ANA_REG_GLB_PWR_SLP_CTRL3, BIT(2),	ANA_REG_GLB_PWR_XTL_EN2, BIT(4)|BIT(5),	ANA_REG_GLB_PWR_XTL_EN2, BIT(6)|BIT(7)	},
	{ LDO_SIM2,		ANA_REG_GLB_LDO_PD_CTRL, BIT(3),	 	ANA_REG_GLB_PWR_SLP_CTRL1, BIT(3),	ANA_REG_GLB_PWR_SLP_CTRL3, BIT(3),	ANA_REG_GLB_PWR_XTL_EN2, BIT(8)|BIT(9),	ANA_REG_GLB_PWR_XTL_EN2, BIT(10)|BIT(11)	},
	{ LDO_CAMA,		ANA_REG_GLB_LDO_PD_CTRL, BIT(4),	 	ANA_REG_GLB_PWR_SLP_CTRL1, BIT(4),	ANA_REG_GLB_PWR_SLP_CTRL3, BIT(4),	-1, -1,									-1, -1									},
	{ LDO_CAMD,		ANA_REG_GLB_LDO_PD_CTRL, BIT(5),	 	ANA_REG_GLB_PWR_SLP_CTRL1, BIT(5),	ANA_REG_GLB_PWR_SLP_CTRL3, BIT(5),	-1, -1,									-1, -1									},
	{ LDO_CAMIO,		ANA_REG_GLB_LDO_PD_CTRL, BIT(6),	 	ANA_REG_GLB_PWR_SLP_CTRL1, BIT(6),	ANA_REG_GLB_PWR_SLP_CTRL3, BIT(6),	-1, -1,									-1, -1									},
	{ LDO_CAMMOT,	ANA_REG_GLB_LDO_PD_CTRL, BIT(7),	 	ANA_REG_GLB_PWR_SLP_CTRL1, BIT(7),	ANA_REG_GLB_PWR_SLP_CTRL3, BIT(7),	-1, -1,									-1, -1									},
	{ LDO_USB,		ANA_REG_GLB_LDO_PD_CTRL, BIT(8),	 	ANA_REG_GLB_PWR_SLP_CTRL1, BIT(8),	ANA_REG_GLB_PWR_SLP_CTRL3, BIT(8),	-1, -1,									-1, -1									},
	{ LDO_CLSG,		ANA_REG_GLB_LDO_PD_CTRL, BIT(9),	 	ANA_REG_GLB_PWR_SLP_CTRL1, BIT(9),	ANA_REG_GLB_PWR_SLP_CTRL3, BIT(9),	-1, -1,									-1, -1									},
	{ DCDC_WPA,		ANA_REG_GLB_LDO_PD_CTRL, BIT(10), 	ANA_REG_GLB_PWR_SLP_CTRL0, BIT(9),	ANA_REG_GLB_PWR_SLP_CTRL2, BIT(8),	ANA_REG_GLB_PWR_XTL_EN4, BIT(12)|BIT(13),	ANA_REG_GLB_PWR_XTL_EN4, BIT(14)|BIT(15)	},
	{ LDO_LPREF,		ANA_REG_GLB_LDO_PD_CTRL, BIT(11), 	ANA_REG_GLB_PWR_SLP_CTRL1, BIT(10),	-1, -1,								-1, -1,									-1, -1									},
	{ LDO_XO,		-1, -1,								-1, -1,								-1, -1,								ANA_REG_GLB_PWR_XTL_EN3, BIT(4)|BIT(5),	ANA_REG_GLB_PWR_XTL_EN3, BIT(6)|BIT(7)	},

	{ RESERVED_NUM, -1, -1,								-1, -1,								-1, -1,								-1, -1,									-1, -1,			 						}
};


struct pll_reg_bit {
	unsigned int						pll_id;

	unsigned int						pll_sys_reg;
	unsigned int						pll_sys_reg_bitmsk;

	unsigned int						cgm_ap_reg;
	unsigned int						cgm_ap_reg_bitmsk;

	/*unsigned int cgm_ap_auto_reg;		*/
	/*unsigned int cgm_ap_auto_reg_bitmsk;	*/

	unsigned int						pll_wait_reg;
	unsigned int						pll_wait_reg_bitmsk;
};

static struct pll_reg_bit pll_reg_tb[] = {
	{ PLL_MPLL,		REG_PMU_APB_MPLL_REL_CFG,		BIT3(0)|BIT(3),	REG_PMU_APB_CGM_AP_EN, BIT(6),	REG_PMU_APB_PLL_WAIT_CNT1,	BIT8(0)		},
	{ PLL_DPLL,		REG_PMU_APB_DPLL_REL_CFG,		BIT3(0)|BIT(3),	REG_PMU_APB_CGM_AP_EN, BIT(1),	REG_PMU_APB_PLL_WAIT_CNT1,	BIT8(1)		},
	{ PLL_TDPLL,		REG_PMU_APB_TDPLL_REL_CFG,		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_CGM_AP_EN, BIT(3),	REG_PMU_APB_PLL_WAIT_CNT1,	BIT8(2)		},
	{ PLL_WPLL,		REG_PMU_APB_WPLL_REL_CFG,		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_CGM_AP_EN, BIT(5),	REG_PMU_APB_PLL_WAIT_CNT1,	BIT8(3)		},
	{ PLL_CPLL,		REG_PMU_APB_CPLL_REL_CFG, 		BIT3(0)|BIT(3),	REG_PMU_APB_CGM_AP_EN, BIT(2),	REG_PMU_APB_PLL_WAIT_CNT2,	BIT8(0)		},
	{ PLL_WIFIPLL1,	REG_PMU_APB_WIFIPLL1_REL_CFG, 	BIT3(0)|BIT(3),	REG_PMU_APB_CGM_AP_EN, BIT(4),	REG_PMU_APB_PLL_WAIT_CNT2,	BIT8(1)		},
	{ PLL_WIFIPLL2,	REG_PMU_APB_WIFIPLL2_REL_CFG, 	BIT3(0)|BIT(3),	-1, -1,							REG_PMU_APB_PLL_WAIT_CNT2,	BIT8(2)		},
	{ PLL_XTL0,		REG_PMU_APB_XTL0_REL_CFG, 		BIT3(0)|BIT(3),	-1, -1,							REG_PMU_APB_XTL_WAIT_CNT,	BIT8(0)		},
	{ PLL_XTL1,		REG_PMU_APB_XTL1_REL_CFG, 		BIT3(0)|BIT(3),	-1, -1,							REG_PMU_APB_XTL_WAIT_CNT,	BIT8(1)		},
	{ PLL_XTL2,		REG_PMU_APB_XTL2_REL_CFG, 		BIT3(0)|BIT(3),	-1, -1,							-1, -1 									},
	{ PLL_XTLBUF0,	REG_PMU_APB_XTLBUF0_REL_CFG, 	BIT3(0)|BIT(3),	-1, -1,							REG_PMU_APB_XTLBUF_WAIT_CNT,BIT8(0)	},
	{ PLL_XTLBUF1,	REG_PMU_APB_XTLBUF1_REL_CFG, 	BIT3(0)|BIT(3),	-1, -1,							REG_PMU_APB_XTLBUF_WAIT_CNT,BIT8(1)	},
	{ RESERVED_NUM,	-1, -1,  -1, -1,  -1, -1 }
};

struct pd_reg_bit {
	unsigned int						pd_shutdown_id;
	unsigned int						pd_reg;
	unsigned int						iso_on_delay_bitmsk;
	unsigned int						pwr_on_seq_delay_bitmsk;
	unsigned int						pwr_on_delay_bitmsk;
	unsigned int						auto_shutdown_bitmsk;
	unsigned int						force_shutdown_bitmsk;
	unsigned int						debug_shutdown_bitmsk;
};

static struct pd_reg_bit shutdown_tb[] = {
	{ PD_CA7_TOP,		REG_PMU_APB_PD_CA7_TOP_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	BIT(28) },
	{ PD_CA7_C0,			REG_PMU_APB_PD_CA7_C0_CFG,		BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	BIT(28) },
	{ PD_CA7_C1,			REG_PMU_APB_PD_CA7_C1_CFG,		BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	BIT(28) },
	{ PD_CA7_C2,			REG_PMU_APB_PD_CA7_C2_CFG,		BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	BIT(28) },
	{ PD_CA7_C3,			REG_PMU_APB_PD_CA7_C3_CFG,		BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	BIT(28) },
	{ PD_AP_SYS,			REG_PMU_APB_PD_AP_SYS_CFG,		BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_MM_TOP,		REG_PMU_APB_PD_MM_TOP_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_GPU_TOP,		REG_PMU_APB_PD_GPU_TOP_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_PUB_SYS,		REG_PMU_APB_PD_PUB_SYS_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ RESERVED_NUM,		-1, 						-1,  		-1, 		-1,  		-1, 		-1, 		-1 }

};

/*ldo chip definition*/
//typedef void (*ldo_status_in_sleep)(struct ldo_lowpower_cfg *ldo_lowpower_cfg);
#define SLP_LP_MODE					(1 << 0)	/* low power in ap sleep mode */
#define SLP_PD_MODE					(1 << 1)	/* power down in  ap sleep mode */
#define SLP_NO_MODE					(1 << 2)	/* all no used in  ap sleep mode */

#define BY_XTL0						(1 << 0)
//#define BY_XTL1						(1 << 1)
#define BY_XTL2						(1 << 2)
#define BY_XTL_ALL					(BY_XTL0 | BY_XTL2)

#define BY_EXT_XTL0					(1 << 0)
#define BY_EXT_XTL1					(1 << 1)
//#define BY_EXT_XTL2					(1 << 2)
#define BY_EXT_XTL_ALL				(BY_EXT_XTL0 | BY_EXT_XTL1)

struct ldo_lowpower_cfg {
	unsigned int						ldo_id;

	unsigned int						ldo_pd;
	unsigned int						status_in_sleep;
	unsigned int						select_by_xtl;
	unsigned int						select_by_ext_xtl;

	unsigned int 						priority;
};

#define AP_SYS						(1 << 0)
#define CP0_SYS						(1 << 1)
#define CP1_SYS						(1 << 2)
#define CP2_SYS						(1 << 3)
#define REF_SYS						(1 << 4)

struct pll_cfg {
	unsigned int						pll_id;

	unsigned int						sys;/*pls config acoording the real exist subsystem*/

	unsigned int						cgm_ap_en;
	unsigned int						wait;
	unsigned int 						priority;
};

struct shutdown_cfg {
	unsigned int 						pd_shutdown_id;
	unsigned int		 				iso_on_delay;
	unsigned int 						pwr_on_seq_delay;
	unsigned int 						pwr_on_delay;
//#define AUTO_SHUTDOWN_DISEN 1
//#define AUTO_SHUTDOWN_EN 2
	unsigned int 						auto_shutdown;
//#define FORCE_SHUTDOWN_DISEN 1
//#define FORCE_SHUTDOWN_EN 2
	unsigned int 						force_shutdown;
//#define DEBUG_SHUTDOWN_DISEN 1
//#define DEBUG_SHUTDOWN_EN 2
	unsigned int 						debug_shutdown;
	unsigned int						priority;
};

struct lowpower {
	struct ldo_reg_bit					*ldo_reg;
	struct pll_reg_bit					*pll_reg;
	struct pd_reg_bit					*pd_reg;
	//ldo
	struct ldo_lowpower_cfg			*ldo_cfg;
	//pll and sys
	struct pll_cfg						*pll_sys_cfg;
	//pd_shutdown
	struct shutdown_cfg				*pd_shutdown_cfg;
};

void customize_low_power_init_prepare(struct ldo_lowpower_cfg *ldo,
								struct pll_cfg *pll,
								struct shutdown_cfg *shutdown);
void low_power_init(void);

#endif
