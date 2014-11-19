#include <config.h>
#include <asm/io.h>
#include <asm/arch/chip_drv_config_extern.h>
#include <asm/arch/bits.h>
#include <linux/types.h>
#include <asm/arch/regs_adi.h>
#include <asm/arch/adi_hal_internal.h>
#include <asm/arch/sprd_reg.h>

#define ANA_VIBRATOR_CTRL0_U      (ANA_REGS_GLB_BASE + 0xf8)

#define CUR_DRV_CAL_SEL_U	(0x0 << 12)
#define SLP_LDOVIBR_PD_EN_U	(0x1 << 9)
#define LDO_VIBR_PD_U	(0x1 << 8)
#define LDO_VIBR_V_U	(0xB4)

void set_vibrator(int on)
{
	if (on){
		ANA_REG_AND(ANA_VIBRATOR_CTRL0_U, ~LDO_VIBR_PD_U);
		ANA_REG_AND(ANA_VIBRATOR_CTRL0_U, ~SLP_LDOVIBR_PD_EN_U);
		}
	else{
			ANA_REG_MSK_OR(ANA_VIBRATOR_CTRL0_U, LDO_VIBR_PD_U, LDO_VIBR_PD_U);
			ANA_REG_MSK_OR(ANA_VIBRATOR_CTRL0_U, SLP_LDOVIBR_PD_EN_U, SLP_LDOVIBR_PD_EN_U);
		}
}

void vibrator_hw_init(void)
{
	ANA_REG_OR(ANA_REG_GLB_RTC_CLK_EN, BIT_RTC_VIBR_EN);
	ANA_REG_MSK_OR(ANA_VIBRATOR_CTRL0_U,CUR_DRV_CAL_SEL_U,CUR_DRV_CAL_SEL_U);
	ANA_REG_MSK_OR(ANA_VIBRATOR_CTRL0_U,LDO_VIBR_V_U,LDO_VIBR_V_U);
}
