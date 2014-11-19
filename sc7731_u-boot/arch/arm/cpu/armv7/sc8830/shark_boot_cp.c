#include <normal_mode.h>
static u32 state;

/*void boot_cp0(void)
{
	u32 cp0data[3] = {0xe59f0000, 0xe12fff10, WMODEM_ADR};
	memcpy(CP0_CODE_COPY_ADR, cp0data, sizeof(cp0data));	   // copy cp0 source code
	*((volatile u32*)CP_SOFT_RST_ADR) |=  BIT_0;	   // reset cp0 
	*((volatile u32*)PD_CP0_SYS_CFG_ADR) &= ~BIT_25;	   //clear cp0 force shutdown

	while(1)
	{
		state = *((volatile u32*)PWR_STATUS1_DBG_ADR);
		if (!(state & (0xf<<28)))
			break;
	}
	*((volatile u32*)PD_CP0_SYS_CFG_ADR) &= ~BIT_31;	   // clear cp0 force deep sleep
}*/

/*both CP0 and CP1 are not booted here for shark 9620,
currently delete CP0 part to avoid compile error ,in 9620
, currently WMODEM_ADR is not defined*/


void boot_cp1(void)
{
	u32 cp1data[3] = {0xe59f0000, 0xe12fff10, TDMODEM_ADR};
	memcpy(CP1_CODE_COPY_ADR, cp1data, sizeof(cp1data));      /* copy cp1 source code */
	*((volatile u32*)CP_SOFT_RST_ADR) |=  BIT_1;       /* reset cp1 */
	*((volatile u32*)PD_CP1_SYS_CFG_ADR) &= ~BIT_25;       /* clear cp1 force shutdown */

	while(1)
	{
		state = *((volatile u32*)PWR_STATUS2_DBG_ADR);
		if (!(state & (0xf<<16)))
			break;
	}

	*((volatile u32*)PD_CP1_SYS_CFG_ADR) &= ~BIT_28;       /* clear cp1 force deep sleep */
}

void boot_cp2(void)
{
	u32 cp2data[3] = {0xe59f0000, 0xe12fff10, WCNMODEM_ADR};
	memcpy(CP2_CODE_COPY_ADR, cp2data, sizeof(cp2data));	   /* copy cp2 source code */
	*((volatile u32*)CP_SOFT_RST_ADR) |=  BIT_2;	   /* reset cp2 */
	*((volatile u32*)PD_CP2_ARM9_CFG_ADR) &= ~BIT_25;	   /* clear cp2 force shutdown */

	while(1)
	{
		state = *((volatile u32*)PWR_STATUS3_DBG_ADR);
		if (!(state & (0xf<<16)))
		break;
	}

	*((volatile u32*)PD_CP2_SYS_CFG_ADR) &= ~(BIT_28 | BIT_25);	   /*system force shutdown deep_sleep*/
	*((volatile u32*)CP_SOFT_RST_ADR) &= ~(BIT_0 | BIT_1 | BIT_2);	   /* clear reset cp0 cp1 cp2 */
}
