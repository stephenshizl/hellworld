#ifndef __LOW_POWER_H__
#define __LOW_POWER_H__

/*global definition*/
#define RESERVED_NUM					(-1)
#define DEFAULT						(-2)/*for all no use*/
#define NO_REG						(-3)
#define DISABLE						(1)
#define ENABLE						(2)

#define ON						(1)
#define OFF						(2)

#define BIT3(_X_)					((BIT(3)-1)<<(3*_X_))
#define BIT8(_X_)					((BIT(8)-1)<<(8*_X_))



/*ldo port*/
#define LDO_VDD18					(0)
#define LDO_VDD28					(1)
#define LDO_VDD25					(2)
#define LDO_RF0						(3)
#define LDO_RF1						(4)
#define LDO_RF2						(5)
#define LDO_EMMCIO					(6)
#define LDO_EMMCCORE				        (7)
#define DCDC_ARM					(8)
#define DCDC_WRF					(9)
#define DCDC_WPA					(10)
#define DCDC_GEN					(11)
#define DCDC_OTP					(12)
#define LDO_AVDD18                                      (13)
#define LDO_SD						(14)
#define LDO_SIM0					(15)
#define LDO_SIM1					(16)
#define LDO_SIM2					(17)
#define LDO_CAMA					(18)
#define LDO_CAMD					(19)
#define LDO_CAMIO					(20)
#define LDO_CAMMOT					(21)
#define LDO_USB						(22)
#define LDO_CLSG					(23)
#define LDO_LPREF					(24)
#define DCDC_CORE					(25)
#define DCDC_MEM					(26)
#define DCDC_BG						(27)
#define BG						(28)


/*pll port*/
#define PLL_MPLL					(0)
#define PLL_DPLL					(1)
#define PLL_TDPLL					(2)
#define PLL_WPLL					(3)
#define PLL_CPLL					(4)
#define PLL_WIFIPLL1					(5)
#define PLL_WIFIPLL2					(6)
#define XTL0					(7)
#define XTL1					(8)
#define XTL2					(9)
#define XTLBUF0					(10)
#define XTLBUF1					(11)

/*shutdown port*/
#define PD_CA7_TOP					(0)
#define PD_CA7_C0					(1)
#define PD_CA7_C1					(2)
#define PD_CA7_C2					(3)
#define PD_CA7_C3					(4)
#define PD_AP_SYS					(5)
#define PD_MM_TOP					(6)
#define PD_GPU_TOP 					(7)
#define PD_CP0_ARM9_0                                   (8)
#define PD_CP0_ARM9_1                                   (9)
#define PD_CP0_ARM9_2                                   (10)
#define PD_CP0_HU3GE                                    (11)
#define PD_CP0_GSM					(12)
#define PD_CP0_TD					(13)
#define PD_CP0_CEVA					(14)
#define PD_CP0_SYS					(15)
#define PD_CP1_ARM9					(16)
#define PD_CP1_GSM					(17)
#define PD_CP1_L1RAM					(18)
#define PD_CP1_SYS					(19)
#define PD_CP2_ARM9					(20)
#define PD_CP2_WIFI					(21)
#define PD_CP2_SYS					(22)
#define PD_PUB_SYS					(23)

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
	/* chip_id */		/* ldo_pd_reg */				/*slp_pd_reg*/				/*slp_lp_reg*/				/*xtl_reg*/						/*ext_xtl_reg*/
	{ LDO_VDD18,		-1, -1, 					ANA_REG_GLB_LDO_SLP_CTRL0, BIT(0),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(11),	ANA_REG_GLB_LDO1828_XTL_CTL, BIT3(2),			ANA_REG_GLB_LDO1828_XTL_CTL, BIT3(3),	},
	{ LDO_VDD28,		-1, -1, 					ANA_REG_GLB_LDO_SLP_CTRL0, BIT(1),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(12),	ANA_REG_GLB_LDO1828_XTL_CTL, BIT3(0),			ANA_REG_GLB_LDO1828_XTL_CTL, BIT3(1),	},
	{ LDO_VDD25,		-1, -1, 					ANA_REG_GLB_LDO_SLP_CTRL0, BIT(2),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(13),	ANA_REG_GLB_PWR_XTL_EN1, BIT3(2),			ANA_REG_GLB_PWR_XTL_EN1, BIT3(3)	},
	{ LDO_RF0,		-1, -1, 					ANA_REG_GLB_LDO_SLP_CTRL0, BIT(3),	ANA_REG_GLB_LDO_SLP_CTRL2, BIT(0), 	ANA_REG_GLB_PWR_XTL_EN0, BIT3(0),			ANA_REG_GLB_PWR_XTL_EN0, BIT3(1)	},
	{ LDO_RF1,		-1, -1, 	 				ANA_REG_GLB_LDO_SLP_CTRL0, BIT(4),	ANA_REG_GLB_LDO_SLP_CTRL2, BIT(1), 	ANA_REG_GLB_PWR_XTL_EN0, BIT3(2),			ANA_REG_GLB_PWR_XTL_EN0, BIT3(3)	},
	{ LDO_RF2,		-1, -1, 	 				ANA_REG_GLB_LDO_SLP_CTRL0, BIT(5),	ANA_REG_GLB_LDO_SLP_CTRL2, BIT(2), 	ANA_REG_GLB_PWR_XTL_EN1, BIT3(0),			ANA_REG_GLB_PWR_XTL_EN1, BIT3(1)	},
	{ LDO_EMMCIO,		-1, -1, 	 				ANA_REG_GLB_LDO_SLP_CTRL0, BIT(6),	ANA_REG_GLB_LDO_SLP_CTRL2, BIT(3), 	-1, -1,							-1, -1					},
	{ LDO_EMMCCORE,		-1, -1, 	 				ANA_REG_GLB_LDO_SLP_CTRL0, BIT(7),	ANA_REG_GLB_LDO_SLP_CTRL2, BIT(4), 	-1, -1,							-1, -1					},
	{ DCDC_ARM,		-1, -1, 	 				ANA_REG_GLB_LDO_SLP_CTRL0, BIT(9),	ANA_REG_GLB_LDO_SLP_CTRL2, BIT(9), 	-1, -1,							-1, -1					},
	{ DCDC_WRF,		-1, -1, 					ANA_REG_GLB_LDO_SLP_CTRL0, BIT(10),	ANA_REG_GLB_LDO_SLP_CTRL2, BIT(5), 	ANA_REG_GLB_PWR_XTL_EN4, BIT3(4),			ANA_REG_GLB_PWR_XTL_EN5, BIT3(4)	},
	{ DCDC_WPA,		ANA_REG_GLB_LDO_PD_CTRL, BIT(11), 		ANA_REG_GLB_LDO_SLP_CTRL0, BIT(11),	ANA_REG_GLB_LDO_SLP_CTRL2, BIT(6), 	ANA_REG_GLB_PWR_XTL_EN4, BIT3(3),			ANA_REG_GLB_PWR_XTL_EN5, BIT3(3)	},
	{ DCDC_GEN, 		-1, -1,						ANA_REG_GLB_LDO_SLP_CTRL0, BIT(12),	ANA_REG_GLB_LDO_SLP_CTRL2, BIT(8), 	ANA_REG_GLB_PWR_XTL_EN4, BIT3(1),			ANA_REG_GLB_PWR_XTL_EN5, BIT3(1)	},
	{ DCDC_OTP, 		-1, -1,						ANA_REG_GLB_LDO_SLP_CTRL0, BIT(13),	-1, -1,				   	-1, -1,							-1, -1					},
	{ LDO_AVDD18,		ANA_REG_GLB_LDO_PD_CTRL, BIT(0),		ANA_REG_GLB_LDO_SLP_CTRL1, BIT(0),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(0), 	ANA_REG_GLB_PWR_XTL_EN2, BIT3(2),			ANA_REG_GLB_PWR_XTL_EN2, BIT3(3)	},
	{ LDO_SD,		ANA_REG_GLB_LDO_PD_CTRL, BIT(1),		ANA_REG_GLB_LDO_SLP_CTRL1, BIT(1),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(1), 	-1, -1,							-1, -1					},
	{ LDO_SIM0,		ANA_REG_GLB_LDO_PD_CTRL, BIT(2), 		ANA_REG_GLB_LDO_SLP_CTRL1, BIT(2),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(2), 	ANA_REG_GLB_MP_PWR_CTRL0, BIT(4)|BIT(5)|BIT(6),		ANA_REG_GLB_MP_PWR_CTRL0, BIT(7)|BIT(8)|BIT(9)	},
	{ LDO_SIM1,		ANA_REG_GLB_LDO_PD_CTRL, BIT(3),		ANA_REG_GLB_LDO_SLP_CTRL1, BIT(3),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(3), 	ANA_REG_GLB_MP_PWR_CTRL0, BIT(10)|BIT(11)|BIT(12),	ANA_REG_GLB_MP_PWR_CTRL0, BIT(13)|BIT(14)|BIT(15)},
	{ LDO_SIM2,		ANA_REG_GLB_LDO_PD_CTRL, BIT(4), 		ANA_REG_GLB_LDO_SLP_CTRL1, BIT(4),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(4), 	ANA_REG_GLB_PWR_XTL_EN2, BIT3(0),			ANA_REG_GLB_PWR_XTL_EN2, BIT3(1)	},
	{ LDO_CAMA,		ANA_REG_GLB_LDO_PD_CTRL, BIT(5), 		ANA_REG_GLB_LDO_SLP_CTRL1, BIT(5),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(5), 	-1, -1,							-1, -1					},
	{ LDO_CAMD,		ANA_REG_GLB_LDO_PD_CTRL, BIT(6), 		ANA_REG_GLB_LDO_SLP_CTRL1, BIT(6),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(6), 	ANA_REG_GLB_CA_CTRL0,BIT3(0),				ANA_REG_GLB_CA_CTRL0,BIT3(1)		},
	{ LDO_CAMIO,		ANA_REG_GLB_LDO_PD_CTRL, BIT(7), 		ANA_REG_GLB_LDO_SLP_CTRL1, BIT(7),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(7), 	ANA_REG_GLB_CA_CTRL0,BIT3(2),				ANA_REG_GLB_CA_CTRL0,BIT3(2)		},
	{ LDO_CAMMOT,		ANA_REG_GLB_LDO_PD_CTRL, BIT(8), 		ANA_REG_GLB_LDO_SLP_CTRL1, BIT(8),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(8), 	-1, -1,							-1, -1					},
	{ LDO_USB,		ANA_REG_GLB_LDO_PD_CTRL, BIT(9), 		ANA_REG_GLB_LDO_SLP_CTRL1, BIT(9),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(9), 	-1, -1,							-1, -1					},
	{ LDO_CLSG,		ANA_REG_GLB_LDO_PD_CTRL, BIT(10), 		ANA_REG_GLB_LDO_SLP_CTRL1, BIT(10),	ANA_REG_GLB_LDO_SLP_CTRL3, BIT(10),	-1, -1,							-1, -1					},
	{ LDO_LPREF,		ANA_REG_GLB_LDO_PD_CTRL, BIT(12), 		ANA_REG_GLB_LDO_SLP_CTRL1, BIT(11),	-1, -1,				   	-1, -1,							-1, -1					},
	{ DCDC_CORE,		-1, -1, 					-1, -1,					ANA_REG_GLB_LDO_SLP_CTRL2, BIT(11),	ANA_REG_GLB_PWR_XTL_EN4, BIT3(0),			ANA_REG_GLB_PWR_XTL_EN5, BIT3(0)	},
	{ DCDC_MEM,		-1, -1,  					-1, -1,					ANA_REG_GLB_LDO_SLP_CTRL2, BIT(10),	ANA_REG_GLB_PWR_XTL_EN4, BIT3(2),			ANA_REG_GLB_PWR_XTL_EN5, BIT3(2)	},
	{ DCDC_BG, 		-1, -1, 					-1, -1,					ANA_REG_GLB_LDO_SLP_CTRL2, BIT(15),	ANA_REG_GLB_PWR_XTL_EN3, BIT3(2),			ANA_REG_GLB_PWR_XTL_EN3, BIT3(3)	},
	{ BG,			-1, -1, 					-1, -1,					ANA_REG_GLB_LDO_SLP_CTRL3, BIT(15),	ANA_REG_GLB_PWR_XTL_EN3, BIT3(0),			ANA_REG_GLB_PWR_XTL_EN3, BIT3(1)	},
	{ RESERVED_NUM, -1, -1,	-1, -1,	-1, -1,	-1, -1,	-1, -1,	}
};


struct pll_reg_bit {
	unsigned int						pll_id;
	unsigned int						pll_sys_reg;
	unsigned int						pll_sys_reg_bitmsk;
	unsigned int						pll_wait_reg;
	unsigned int						pll_wait_reg_bitmsk;
};
static struct pll_reg_bit pll_reg_tb[] = {
	{ PLL_MPLL,		REG_PMU_APB_MPLL_REL_CFG,		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_PLL_WAIT_CNT1,	BIT8(0)	},
	{ PLL_DPLL,		REG_PMU_APB_DPLL_REL_CFG,		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_PLL_WAIT_CNT1,	BIT8(1)	},
	{ PLL_TDPLL,		REG_PMU_APB_TDPLL_REL_CFG,		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_PLL_WAIT_CNT1,	BIT8(2)	},
	{ PLL_WPLL,		REG_PMU_APB_WPLL_REL_CFG,		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_PLL_WAIT_CNT1,	BIT8(3)	},
	{ PLL_CPLL,		REG_PMU_APB_CPLL_REL_CFG, 		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_PLL_WAIT_CNT2,	BIT8(0)	},
	{ PLL_WIFIPLL1,		REG_PMU_APB_WIFIPLL1_REL_CFG, 		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_PLL_WAIT_CNT2,	BIT8(1)	},
	{ PLL_WIFIPLL2,		REG_PMU_APB_WIFIPLL2_REL_CFG, 		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_PLL_WAIT_CNT2,	BIT8(2)	},
	{ XTL0,		REG_PMU_APB_XTL0_REL_CFG, 		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_XTL_WAIT_CNT,	BIT8(0)	},
	{ XTL1,		REG_PMU_APB_XTL1_REL_CFG, 		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_XTL_WAIT_CNT,	BIT8(1)	},
	{ XTL2,		REG_PMU_APB_XTL2_REL_CFG, 		BIT3(0)|BIT(3)|BIT(4),	-1, -1 					},
	{ XTLBUF0,		REG_PMU_APB_XTLBUF0_REL_CFG, 		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_XTLBUF_WAIT_CNT,	BIT8(0)	},
	{ XTLBUF1,		REG_PMU_APB_XTLBUF1_REL_CFG, 		BIT3(0)|BIT(3)|BIT(4),	REG_PMU_APB_XTLBUF_WAIT_CNT,	BIT8(1)	},
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
	{ PD_CA7_C0,		REG_PMU_APB_PD_CA7_C0_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	BIT(28) },
	{ PD_CA7_C1,		REG_PMU_APB_PD_CA7_C1_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	BIT(28) },
	{ PD_CA7_C2,		REG_PMU_APB_PD_CA7_C2_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	BIT(28) },
	{ PD_CA7_C3,		REG_PMU_APB_PD_CA7_C3_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	BIT(28) },
	{ PD_AP_SYS,		REG_PMU_APB_PD_AP_SYS_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_MM_TOP,		REG_PMU_APB_PD_MM_TOP_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_GPU_TOP,		REG_PMU_APB_PD_GPU_TOP_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP0_ARM9_0,   	REG_PMU_APB_PD_CP0_ARM9_0_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP0_ARM9_1,   	REG_PMU_APB_PD_CP0_ARM9_1_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP0_ARM9_2,   	REG_PMU_APB_PD_CP0_ARM9_2_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP0_HU3GE,    	REG_PMU_APB_PD_CP0_HU3GE_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP0_GSM,		REG_PMU_APB_PD_CP0_GSM_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP0_TD,		REG_PMU_APB_PD_CP0_TD_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP0_CEVA,		REG_PMU_APB_PD_CP0_CEVA_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP0_SYS,		REG_PMU_APB_PD_CP0_SYS_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	-1,		BIT(25),	-1 },
	{ PD_CP1_ARM9,		REG_PMU_APB_PD_CP1_ARM9_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP1_GSM,		REG_PMU_APB_PD_CP1_GSM_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP1_L1RAM,		REG_PMU_APB_PD_CP1_L1RAM_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP1_SYS,		REG_PMU_APB_PD_CP1_SYS_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	-1,		BIT(25),	-1 },
	{ PD_CP2_ARM9,		REG_PMU_APB_PD_CP2_ARM9_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP2_WIFI,		REG_PMU_APB_PD_CP2_WIFI_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ PD_CP2_SYS,		REG_PMU_APB_PD_CP2_SYS_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	-1,		BIT(25),	-1 },
	{ PD_PUB_SYS,		REG_PMU_APB_PD_PUB_SYS_CFG,	BIT8(0), 	BIT8(1), 	BIT8(2),	BIT(24),	BIT(25),	-1 },
	{ RESERVED_NUM,	-1,-1,-1,-1,-1,-1,-1 }

};

/*ldo chip definition*/
//typedef void (*ldo_status_in_sleep)(struct ldo_lowpower_cfg *ldo_lowpower_cfg);
#define SLP_LP_MODE					(1 << 0)	/* low power in ap sleep mode */
#define SLP_PD_MODE					(1 << 1)	/* power down in  ap sleep mode */
#define SLP_NO_MODE					(1 << 2)

#define BY_XTL0						(1 << 0)
#define BY_XTL1						(1 << 1)
#define BY_XTL2						(1 << 2)
#define BY_XTL_ALL					(BY_XTL0 | BY_XTL1 | BY_XTL2)

#define BY_EXT_XTL0					(1 << 0)
#define BY_EXT_XTL1					(1 << 1)
#define BY_EXT_XTL2					(1 << 2)
#define BY_EXT_XTL_ALL					(BY_EXT_XTL0 | BY_EXT_XTL1 | BY_EXT_XTL2)

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
#define ALL_SYS						(AP_SYS | CP0_SYS | CP1_SYS | CP2_SYS)

struct pll_cfg {
	unsigned int						pll_id;
	unsigned int						sys;/*pls config acoording the real exist subsystem*/
	unsigned int						wait;
	unsigned int 						priority;
};

struct shutdown_cfg {
	unsigned int 						pd_shutdown_id;
	unsigned int		 				iso_on_delay;
	unsigned int 						pwr_on_seq_delay;
	unsigned int 						pwr_on_delay;
	unsigned int 						auto_shutdown;
	unsigned int 						force_shutdown;
	unsigned int 						debug_shutdown;
	unsigned int						priority;
};

void customize_low_power_init_prepare(struct ldo_lowpower_cfg *ldo,
								struct pll_cfg *pll,
								struct shutdown_cfg *shutdown);
void low_power_init(void);

#endif
