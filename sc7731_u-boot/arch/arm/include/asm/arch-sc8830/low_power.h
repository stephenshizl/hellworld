#ifndef __LOWPOWER_H__
#define __LOWPOWER_H__

#if defined(CONFIG_SPX15)
#include "chip_x15/__low_power.h"
#elif defined(CONFIG_SPX30G)
#include "chip_x30g/__low_power.h"
#endif

#endif
