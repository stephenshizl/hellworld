#ifndef __PLL_H__
#define __PLL_H__

struct pll_cfg fixed_pll_cfg[] = {
		{ PLL_MPLL,                AP_SYS,                                 7,                       0 },
		{ PLL_DPLL,                AP_SYS|CP0_SYS|CP2_SYS,                 7,                       0 },
		{ PLL_TDPLL,               AP_SYS|CP0_SYS|CP2_SYS,                 7,                       0 },
		{ PLL_WPLL,                CP0_SYS,                                7,                       0 },
		{ PLL_CPLL,                CP2_SYS,                                7,                       0 },
		{ PLL_WIFIPLL1,            CP2_SYS,                                7,                       0 },
		{ PLL_WIFIPLL2,            CP2_SYS,                                7,                       0 },
		{ XTL0,                    AP_SYS|CP2_SYS,                         57,                      0 },
		{ XTL1,                    CP0_SYS,                                57,                      0 },
		{ XTL2,                    CP2_SYS,                                NO_REG,                  1 },
		{ XTLBUF0,                 AP_SYS|CP2_SYS,                         7,                       0 },
		{ XTLBUF1,                 CP0_SYS,                                7,                       0 },
		{ RESERVED_NUM, 0, 0, 0 }
};

#endif
