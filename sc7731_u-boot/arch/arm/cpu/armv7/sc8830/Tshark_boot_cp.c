#include <normal_mode.h>

#define msleep(cnt) udelay(cnt*1000)
static u32 state;

void boot_cp0(void)
{
	u32 m_data[3] = {0xe59f0000, 0xe12fff10, MODEM_ADR};
	memcpy(CP0_CODE_COPY_ADR, m_data, sizeof(m_data));	  /* copy cp0 source code */

	*((volatile u32*)COOPERATE_PMU_CTRL0_ADDR) &= ~BIT_25;  /* open cp0 pmu controller*/
	msleep(50);
	*((volatile u32*)COOPERATE_PMU_CTRL0_ADDR) &= ~BIT_28;
	msleep(50);

	*((volatile u32*)COOPERATE_PROCESSOR_RESET_ADDR)|= CORE_CP0;	/* reset cp0 */
	*((volatile u32*)COOPERATE_PROCESSOR_RESET_ADDR) &= ~CORE_CP0; /* clear cp0 force shutdown */

	while(1)
	{
		state = *((volatile u32*)COOPERATE_PROCESSOR_RESET_ADDR);

		if(!(state & CORE_CP0))
			break;
	}


}

void boot_cp1(void);

void boot_cp2(void)
{
	u32 wcndata[3] = {0xe59f0000, 0xe12fff10,  WCNMODEM_ADR};
	memcpy(CP2_CODE_COPY_ADR, wcndata, sizeof(wcndata));	/* copy cp2 source code */

	*((volatile u32*)COOPERATE_PMU_CTRL2_ADDR) &= ~BIT_25;	/* open cp2 pmu controller*/
	msleep(50);
	*((volatile u32*)COOPERATE_PMU_CTRL2_ADDR) &= ~BIT_28;
	msleep(50);

	*((volatile u32*)COOPERATE_PROCESSOR_RESET_ADDR)|= CORE_CP2;	/* reset cp2 */
	*((volatile u32*)COOPERATE_PROCESSOR_RESET_ADDR) &= ~CORE_CP2; /* clear cp2 force shutdown */
	while(1)
	{
		state = *((volatile u32*)COOPERATE_PROCESSOR_RESET_ADDR);

		if(!(state & CORE_CP2))
		break;
	}

}

