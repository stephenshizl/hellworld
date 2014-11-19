#ifndef __PLL_H__
#define __PLL_H__

struct pll_cfg fixed_pll_cfg[] = {
	{ PLL_MPLL,		AP_SYS,								LP_EN,		7,		0 },
	{ PLL_DPLL,		AP_SYS|CP0_SYS|CP2_SYS,				LP_EN,		7,		0 },
	{ PLL_TDPLL,		AP_SYS|CP0_SYS|CP1_SYS|CP2_SYS,	LP_EN,		7,		0 },
	{ PLL_WPLL,		CP0_SYS|REF_SYS,					LP_DIS,		7,		0 },
	{ PLL_CPLL,		CP2_SYS,							LP_DIS,		7,		0 },
	{ PLL_WIFIPLL1,	CP2_SYS,							LP_DIS,		7,		0 },
	{ PLL_WIFIPLL2,	CP2_SYS,							NO_USED,	7,		0 },
	{ PLL_XTL0,		AP_SYS|CP0_SYS|CP2_SYS,				NO_USED,	57,		0 },
	{ PLL_XTL1,		CP0_SYS,							NO_USED,	57,		0 },
	{ PLL_XTL2,		CP2_SYS,							NO_USED,	NO_USED,1 },
	{ PLL_XTLBUF0,	AP_SYS|CP0_SYS|CP2_SYS,				NO_USED,	7,		0 },
	{ PLL_XTLBUF1,	CP0_SYS,							NO_USED,	7,		0 },
	{ RESERVED_NUM, 0, 0, 0, 0 }
};

struct pll_cfg fixed_pll_cfg_0x2711a000[] = {
	{ PLL_MPLL,		AP_SYS,								LP_EN,		7,		0 },
	{ PLL_DPLL,		AP_SYS|CP0_SYS|CP2_SYS,				LP_EN,		7,		0 },
	{ PLL_TDPLL,		AP_SYS|CP0_SYS|CP1_SYS|CP2_SYS,	LP_EN,		7,		0 },
	{ PLL_WPLL,		CP0_SYS,							LP_DIS,		7,		0 },
	{ PLL_CPLL,		CP2_SYS,							LP_DIS,		7,		0 },
	{ PLL_WIFIPLL1,	CP2_SYS,							LP_DIS,		7,		0 },
	{ PLL_WIFIPLL2,	CP2_SYS,							NO_USED,	7,		0 },
	{ PLL_XTL0,		AP_SYS|CP0_SYS|CP2_SYS,				NO_USED,	57,		0 },
	{ PLL_XTL1,		CP0_SYS,							NO_USED,	57,		0 },
	{ PLL_XTL2,		CP2_SYS,							NO_USED,	NO_USED,1 },
	{ PLL_XTLBUF0,	AP_SYS|CP0_SYS|CP2_SYS,				NO_USED,	7,		0 },
	{ PLL_XTLBUF1,	AP_SYS|CP0_SYS,						NO_USED,	7,		0 },
	{ RESERVED_NUM, 0, 0, 0, 0 }
};


#endif
