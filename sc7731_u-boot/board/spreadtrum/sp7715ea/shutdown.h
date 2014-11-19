#ifndef __SHUTDOWN_H__
#define __SHUTDOWN_H__

struct shutdown_cfg fixed_shutdown_cfg[] = {
	{ PD_CA7_TOP,	4,	2,	8,	LP_EN,	LP_DIS,	LP_DIS,	0 },
	{ PD_CA7_C0,		2,	6,	8,	LP_EN,	LP_DIS,	LP_DIS,	0 },
	{ PD_CA7_C1,		2,	4,	8,	LP_DIS,	LP_EN,	LP_DIS,	0 },
	{ PD_CA7_C2,		2,	4,	8,	LP_DIS,	LP_EN,	LP_DIS,	0 },
	{ PD_CA7_C3,		2,	4,	8,	LP_DIS,	LP_EN,	LP_DIS,	1 },
	{ PD_AP_SYS,		6,	0,	8,	LP_EN,	LP_DIS,	NO_USED,0 },
	{ PD_MM_TOP,	4,	0,	8,	LP_DIS,	LP_EN,	NO_USED,0 },
	{ PD_GPU_TOP,	4,	0,	8,	LP_DIS,	LP_EN,	NO_USED,0 },
	{ PD_PUB_SYS,	6,	0,	8,	LP_EN,	LP_DIS,	NO_USED,0 },
	{RESERVED_NUM,	0, 0, 0, 0, 0, 0, 0 }
};

#endif
