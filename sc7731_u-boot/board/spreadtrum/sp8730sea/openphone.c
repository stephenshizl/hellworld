#include <common.h>
#include <asm/io.h>
#include <asm/arch/ldo.h>
#include <asm/arch/sprd_reg_ahb.h>
#include <asm/arch/regs_ahb.h>
#include <asm/arch/common.h>
#include <asm/arch/adi_hal_internal.h>
#include <asm/u-boot.h>
#include <part.h>
#include <sdhci.h>
#include <asm/arch/mfp.h>
#include <linux/gpio.h>
#include <asm/arch/gpio.h>
#include <asm/arch/pinmap.h>
DECLARE_GLOBAL_DATA_PTR;

extern void sprd_gpio_init(void);
extern void ADI_init (void);
extern int LDO_Init(void);
extern void ADC_Init(void);
extern int sound_init(void);

#ifdef CONFIG_GENERIC_MMC
int mv_sdh_init(u32 regbase, u32 max_clk, u32 min_clk, u32 quirks);
int mmc_sdcard_init();

int board_mmc_init(bd_t *bd)
{
	mmc_sdcard_init();

	mv_sdh_init(CONFIG_SYS_SD_BASE, SDIO_BASE_CLK_192M,
			SDIO_CLK_250K, 0);

	return 0;
}
#endif

extern struct eic_gpio_resource sprd_gpio_resource[];
extern int sprd_gpio_direction_output(struct gpio_chip *chip, unsigned offset, int value);
extern int sprd_gpio_request(struct gpio_chip *chip, unsigned offset);

#define EXT_VDDUSB_EN_GPIO	152

int set_ext_vddusb_en(int is_enable)
{
	sprd_gpio_request(NULL, EXT_VDDUSB_EN_GPIO);
	if (is_enable) {
		sprd_gpio_direction_output(NULL, EXT_VDDUSB_EN_GPIO, 1);
	} else {
		sprd_gpio_direction_output(NULL, EXT_VDDUSB_EN_GPIO, 0);
	}

	return 0;
}

int board_init()
{
	gd->bd->bi_arch_number = MACH_TYPE_OPENPHONE;
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;
	ADI_init();
	misc_init();
	LDO_Init();
	ADC_Init();
	pin_init();
	sprd_eic_init();
	sprd_gpio_init();
	sound_init();
	init_ldo_sleep_gr();
	//TDPllRefConfig(1);

	// disable external vddusb
	set_ext_vddusb_en(0);

	return 0;
}

int dram_init(void)
{
	gd->ram_size = get_ram_size((volatile void *)PHYS_SDRAM_1,
			PHYS_SDRAM_1_SIZE);
	return 0;
}
