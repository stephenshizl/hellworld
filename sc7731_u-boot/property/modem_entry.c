#include "normal_mode.h"

extern void boot_cp0(void);
extern void boot_cp1(void);
extern void boot_cp2(void);

void modem_entry(void)
{
#if modem_cp0_enable
	boot_cp0();
#endif

#if modem_cp1_enable
	boot_cp1();
#endif

#if modem_cp2_enable
	boot_cp2();
#endif

}
