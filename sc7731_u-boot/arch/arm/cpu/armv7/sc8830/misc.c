#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sci_types.h>
#include <asm/arch/adi_hal_internal.h>
/*
	REG_AON_APB_BOND_OPT0  ==> romcode set
	REG_AON_APB_BOND_OPT1  ==> set it later

	!!! notice: these two registers can be set only one time!!!

	B1[0] : B0[0]
	0     : 0     Jtag enable
	0     : 1     Jtag disable
	1     : 0     Jtag enable
	1     : 1     Jtag enable
*/

/*************************************************
* 1 : enable jtag success                        *
* 0 : enable jtag fail                           *
*************************************************/
int sprd_jtag_enable()
{
	if (*((volatile unsigned int *)(REG_AON_APB_BOND_OPT0)) & 1)
	{
		*((volatile unsigned int *)(REG_AON_APB_BOND_OPT1)) = 1;
		if (!((*(volatile unsigned int *)(REG_AON_APB_BOND_OPT1)) & 1))
			return 0;
	}
	return 1;
}

/*************************************************
* 1 : disable jtag success                       *
* 0 : disable jtag fail                          *
*************************************************/
int sprd_jtag_disable()
{
	if (!(*((volatile unsigned int *)(REG_AON_APB_BOND_OPT0)) & 1))
	{
		return 0;
	}
	else
	{
		*((volatile unsigned int *)(REG_AON_APB_BOND_OPT1)) = 0;
		if (*((volatile unsigned int *)(REG_AON_APB_BOND_OPT1)) & 1)
			return 0;
		else
			return 1;
	}
}

static void ap_slp_cp_dbg_cfg()
{
	*((volatile unsigned int *)(REG_AP_AHB_MCU_PAUSE)) |= BIT_MCU_SLEEP_FOLLOW_CA7_EN; //when ap sleep, cp can continue debug
}

static void ap_cpll_rel_cfg()
{
	*((volatile unsigned int *)(REG_PMU_APB_CPLL_REL_CFG)) |= BIT_CPLL_AP_SEL;
}

static void bb_bg_auto_en()
{
	*((volatile unsigned int *)(REG_AON_APB_RES_REG0)) |= 1<<8;
}


static void ap_close_wpll_en()
{
       *((volatile unsigned int *)(REG_PMU_APB_CGM_AP_EN)) &= ~BIT_CGM_WPLL_AP_EN;
}

static void ap_close_cpll_en()
{
       *((volatile unsigned int *)(REG_PMU_APB_CGM_AP_EN)) &= ~BIT_CGM_CPLL_AP_EN;
}

static void ap_close_wifipll_en()
{
       *((volatile unsigned int *)(REG_PMU_APB_CGM_AP_EN)) &= ~BIT_CGM_WIFIPLL1_AP_EN;
}


static void bb_ldo_auto_en()
{
	*((volatile unsigned int *)(REG_AON_APB_RES_REG0)) |= 1<<9;
} 

#ifndef CONFIG_PBINT_7S_RESET_V1
/* this is default 7s reset function
   like shark project.
*/
#define CONFIG_PBINT_7S_RESET_V0
#endif

#ifdef CONFIG_PBINT_7S_RESET_V1

#define PBINT_7S_HW_FLAG (BIT(7))
#define PBINT_7S_SW_FLAG (BIT(12))

#define CONFIG_7S_RESET_SW_FLAG
#ifdef CONFIG_7S_RESET_SW_FLAG
static u32 pbint_7s_flag = 0;
#endif
int is_7s_reset(void)
{
#ifdef CONFIG_7S_RESET_SW_FLAG
	return pbint_7s_flag & PBINT_7S_SW_FLAG;
#else
	return sci_adi_read(ANA_REG_GLB_POR_SRC_FLAG) & PBINT_7S_SW_FLAG;
#endif
}

int is_7s_reset_for_systemdump(void)
{
	int val;
	/* FIXME flag? */
	int mask = PBINT_7S_SW_FLAG | PBINT_7S_HW_FLAG;
	/* some chip just care software flag */
	int chip_id = ANA_GET_CHIP_ID();
	if (((chip_id >> 16) & 0xFFFF) == 0x2711) {
		if ((chip_id & 0xFFFF) <= 0xA100) {
			mask = PBINT_7S_SW_FLAG;
		}
	}
#ifdef CONFIG_7S_RESET_SW_FLAG
	val = pbint_7s_flag & mask;
#else
	val = sci_adi_read(ANA_REG_GLB_POR_SRC_FLAG) & mask;
#endif
	return (val == mask);
}

static inline int pbint_7s_rst_disable(uint32 disable)
{
	if (disable) {
		sci_adi_set(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_RST_DISABLE);
	} else {
		sci_adi_clr(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_RST_DISABLE);
	}
	return 0;
}

#if defined CONFIG_PBINT_7S_RST_2KEY_MODE_SUPPORT
#define PBINT_7S_RST_2KEY_MODE 1
#define PBINT_7S_RST_NORMAL_MODE 0
static inline int pbint_7s_rst_set_2keymode(uint32 mode)
{
	if (mode) {
		sci_adi_set(ANA_REG_GLB_SWRST_CTRL, BIT_KEY2_7S_RST_EN);
	} else {
		sci_adi_clr(ANA_REG_GLB_SWRST_CTRL, BIT_KEY2_7S_RST_EN);
	}
	return 0;
}
#endif

#define PBINT_7S_RST_HW_MODE 1
#define PBINT_7S_RST_SW_MODE 0
static inline int pbint_7s_rst_set_sw(uint32 mode)
{
	if (mode) {
		sci_adi_set(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_RST_MODE);
	} else {
		sci_adi_clr(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_RST_MODE);
	}
	return 0;
}

#define PBINT_7S_RST_SW_LONG_MODE 0
#define PBINT_7S_RST_SW_SHORT_MODE 1
static inline int pbint_7s_rst_set_swmode(uint32 mode)
{
	if (mode) {
		sci_adi_set(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_RST_SWMODE);
	} else {
		sci_adi_clr(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_RST_SWMODE);
	}
	return 0;
}

static inline int pbint_7s_rst_set_threshold(uint32 th)
{
	int mask = BITS_PBINT_7S_RST_THRESHOLD(-1);
	int shift = ffs(mask) - 1;
	sci_adi_write(ANA_REG_GLB_POR_7S_CTRL, (th << shift) & mask, mask);
	return 0;
}

int pbint_7s_rst_cfg(uint32 en, uint32 sw_rst, uint32 short_rst)
{
#ifdef CONFIG_7S_RESET_SW_FLAG
	pbint_7s_flag = sci_adi_read(ANA_REG_GLB_POR_SRC_FLAG);
	sci_adi_set(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_FLAG_CLR);
	udelay(10);
	sci_adi_clr(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_FLAG_CLR);
#endif
	/* ignore sw_rst, please refer to config.h */
	if (en) {
#if defined CONFIG_PBINT_7S_RST_THRESHOLD
		pbint_7s_rst_set_threshold(CONFIG_PBINT_7S_RST_THRESHOLD);
#endif
		if (sw_rst) {
			pbint_7s_rst_set_sw(PBINT_7S_RST_SW_MODE);
		} else {
			pbint_7s_rst_set_sw(PBINT_7S_RST_HW_MODE);
		}
		if (short_rst) {
			pbint_7s_rst_set_swmode(PBINT_7S_RST_SW_SHORT_MODE);
		} else {
			pbint_7s_rst_set_swmode(PBINT_7S_RST_SW_LONG_MODE);
		}
#if defined CONFIG_PBINT_7S_RST_2KEY_MODE_SUPPORT
#if defined CONFIG_PBINT_7S_RST_2KEY_MODE_ENABLE
		pbint_7s_rst_set_2keymode(PBINT_7S_RST_2KEY_MODE);
#elif defined CONFIG_PBINT_7S_RST_2KEY_MODE_DISABLE
		pbint_7s_rst_set_2keymode(PBINT_7S_RST_NORMAL_MODE);
#endif
#endif
	}
	return pbint_7s_rst_disable(!en);
}
#elif defined CONFIG_PBINT_7S_RESET_V0

#define PBINT_7S_HW_FLAG (BIT(7))
#define PBINT_7S_SW_FLAG (BIT(12))

#define CONFIG_7S_RESET_SW_FLAG
#ifdef CONFIG_7S_RESET_SW_FLAG
static u32 pbint_7s_flag = 0;
#endif
int is_7s_reset(void)
{
#ifdef CONFIG_7S_RESET_SW_FLAG
	return pbint_7s_flag & PBINT_7S_SW_FLAG;
#else
	return sci_adi_read(ANA_REG_GLB_POR_SRC_FLAG) & PBINT_7S_SW_FLAG;
#endif
}

int is_7s_reset_for_systemdump(void)
{
	int val;
	int mask = PBINT_7S_SW_FLAG;
#ifdef CONFIG_7S_RESET_SW_FLAG
	val = pbint_7s_flag & mask;
#else
	val = sci_adi_read(ANA_REG_GLB_POR_SRC_FLAG) & mask;
#endif
	return (val == mask);
}

void pbint_7s_rst_cfg(uint32 en_rst, uint32 sw_rst, uint32 short_rst)
{
	uint16 reg_data = ANA_REG_GET(ANA_REG_GLB_POR_7S_CTRL);

#ifdef CONFIG_7S_RESET_SW_FLAG
	pbint_7s_flag = sci_adi_read(ANA_REG_GLB_POR_SRC_FLAG);
	sci_adi_set(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_FLAG_CLR);
	udelay(10);
	sci_adi_clr(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_FLAG_CLR);
#endif

	if (!en_rst)
	{
		reg_data |=  BIT_PBINT_7S_RST_DISABLE;
	}
	else
	{
		reg_data &= ~BIT_PBINT_7S_RST_DISABLE;
		/* software reset */
		if (sw_rst)
		{
			reg_data |=  BIT_PBINT_7S_RST_MODE_RTCSET;
			reg_data &= ~BIT_PBINT_7S_RST_MODE_RTCCLR;
		}
		else
		{
			reg_data &= ~BIT_PBINT_7S_RST_MODE_RTCSET;
			reg_data |=  BIT_PBINT_7S_RST_MODE_RTCCLR;
		}
		/* 7s short reset */
		if (short_rst)
		{
			reg_data |=  BIT_PBINT_7S_RST_SWMODE_RTCSET;
			reg_data &= ~BIT_PBINT_7S_RST_SWMODE_RTCCLR;
		}
		else
		{
			reg_data &= ~BIT_PBINT_7S_RST_SWMODE_RTCSET;
			reg_data |=  BIT_PBINT_7S_RST_SWMODE_RTCCLR;
		}
	}
	ANA_REG_SET(ANA_REG_GLB_POR_7S_CTRL, reg_data);
	printf("ANA_REG_GLB_POR_7S_CTRL:%04X\r\n", ANA_REG_GET(ANA_REG_GLB_POR_7S_CTRL));
}
#endif

#if defined (CONFIG_OF_LIBFDT) && !defined (CONFIG_SPX30G)
void scx35_pmu_reconfig(void)
{
	/* FIXME:
	 * turn on gpu/mm domain for clock device initcall, and then turn off asap.
	 */
	__raw_writel(__raw_readl(REG_PMU_APB_PD_MM_TOP_CFG)
		     & ~(BIT_PD_MM_TOP_FORCE_SHUTDOWN),
		     REG_PMU_APB_PD_MM_TOP_CFG);

	__raw_writel(__raw_readl(REG_PMU_APB_PD_GPU_TOP_CFG)
		     & ~(BIT_PD_GPU_TOP_FORCE_SHUTDOWN),
		     REG_PMU_APB_PD_GPU_TOP_CFG);

	__raw_writel(__raw_readl(REG_AON_APB_APB_EB0) | BIT_MM_EB |
		     BIT_GPU_EB, REG_AON_APB_APB_EB0);

	__raw_writel(__raw_readl(REG_MM_AHB_AHB_EB) | BIT_MM_CKG_EB,
		     REG_MM_AHB_AHB_EB);

	__raw_writel(__raw_readl(REG_MM_AHB_GEN_CKG_CFG)
		     | BIT_MM_MTX_AXI_CKG_EN | BIT_MM_AXI_CKG_EN,
		     REG_MM_AHB_GEN_CKG_CFG);

	__raw_writel(__raw_readl(REG_MM_CLK_MM_AHB_CFG) | 0x3,
		     REG_MM_CLK_MM_AHB_CFG);

}

#else
void scx35_pmu_reconfig(void) {}
#endif
inline int is_hw_smpl_enable(void)
{
#if defined CONFIG_ADIE_SC2723S || defined CONFIG_ADIE_SC2723
	return !!(sci_adi_read(ANA_REG_GLB_SMPL_CTRL1) & BIT_SMPL_EN);
#endif
	return 0;
}

#if !defined CONFIG_SPX15 && !defined CONFIG_SPX30G
int is_smpl_bootup(void)
{
	if(sci_adi_read(ANA_REG_GLB_CHIP_ID_LOW) == 0xCA00) {
		return sci_adi_read(ANA_REG_GLB_CA_CTRL2) & BIT_IS_SMPL_ON;
	}
	else {
		return 0;
	}
}
#define SMPL_MODE_ENABLE_SET	(0x1935)
static int smpl_config(void)
{
	u32 val;
	if(sci_adi_read(ANA_REG_GLB_CHIP_ID_LOW) == 0xCA00) {
		val = BITS_SMPL_ENABLE(SMPL_MODE_ENABLE_SET);
		return sci_adi_write_fast(ANA_REG_GLB_CA_CTRL1, val, 1);
	}
}
#else
#ifdef CONFIG_SMPL_MODE
#define CONFIG_SMPL_SW_FLAG
#ifdef CONFIG_SMPL_SW_FLAG
static u32 smpl_flag = 0;
#endif
int is_smpl_bootup(void)
{
#ifdef CONFIG_SMPL_SW_FLAG
	return smpl_flag & BIT_IS_SMPL_ON_SW_FLAG;
#else
	return sci_adi_read(ANA_REG_GLB_BA_CTRL1) & BIT_IS_SMPL_ON;
#endif
}

#define SMPL_MODE_ENABLE_SET	(0x1935)
static int smpl_config(void)
{
	u32 val = BITS_SMPL_ENABLE(SMPL_MODE_ENABLE_SET);
#ifdef CONFIG_SMPL_THRESHOLD
	val |= BITS_SMPL_THRESHOLD(CONFIG_SMPL_THRESHOLD);
#endif
#ifdef CONFIG_SMPL_SW_FLAG
	smpl_flag = sci_adi_read(ANA_REG_GLB_BA_CTRL1);
	sci_adi_set(ANA_REG_GLB_BA_CTRL1, BIT_IS_SMPL_ON_SW_CLR);
#endif
	return sci_adi_write_fast(ANA_REG_GLB_BA_CTRL0, val, 1);
}
#else
inline int is_smpl_bootup(void)
{
	return 0;
}

inline static int smpl_config(void)
{
	return 0;
}
#endif
#endif
static void vbat_crash_vol_set(void)
{
#if !defined CONFIG_SPX15 && !defined CONFIG_SPX30G
	u32 val;
	if(sci_adi_read(ANA_REG_GLB_CHIP_ID_LOW) == 0xCA00) {
		val = sci_adi_read(ANA_REG_GLB_CA_CTRL3);
		val &= ~(3 << 14);
		val |= (1 << 14);
		sci_adi_write(ANA_REG_GLB_CA_CTRL3, val, 0xffff);
	}
#endif
}
void misc_init()
{
	scx35_pmu_reconfig();
	ap_slp_cp_dbg_cfg();
	ap_cpll_rel_cfg();
#ifndef  CONFIG_SPX15
	ap_close_wpll_en();
	ap_close_cpll_en();
	ap_close_wifipll_en();
#endif
#ifndef  CONFIG_SPX30G
	bb_bg_auto_en();
	bb_ldo_auto_en();
#endif
#ifndef CONFIG_PBINT_7S_RESET_DISABLE
#if defined CONFIG_PBINT_7S_RESET_V1
#if defined CONFIG_PBINT_7S_RST_SW_SHORT
	pbint_7s_rst_cfg(1, 1, 1);
#elif defined CONFIG_PBINT_7S_RST_SW_LONG
	pbint_7s_rst_cfg(1, 1, 0);
#elif defined CONFIG_PBINT_7S_RST_HW_LONG
	pbint_7s_rst_cfg(1, 0, 0);
#else
	pbint_7s_rst_cfg(1, 0, 1);
#endif
#elif defined CONFIG_PBINT_7S_RESET_V0
#if defined CONFIG_PBINT_7S_RST_HW_SHORT
	pbint_7s_rst_cfg(1, 1, 1);
#elif defined CONFIG_PBINT_7S_RST_HW_LONG
	pbint_7s_rst_cfg(1, 1, 0);
#elif defined CONFIG_PBINT_7S_RST_SW_SHORT
	pbint_7s_rst_cfg(1, 0, 1);
#else
	pbint_7s_rst_cfg(1, 0, 0);
#endif
#endif
#endif
	smpl_config();
	vbat_crash_vol_set();

#ifdef CONFIG_SPX30G
/*csi0_phy_powerdow & csi1_phy_powerdow*/
	__raw_bits_or((BIT_CSI1_PHY_PD | BIT_CSI0_PHY_PD), REG_AON_APB_PWR_CTRL);
/*dsi_phy_powerdow*/
	__raw_bits_or(BIT_DSI_PHY_PD, REG_AON_APB_PWR_CTRL);
#endif
}

typedef struct mem_cs_info
{
	uint32 cs_number;
	uint32 cs0_size;//bytes
	uint32 cs1_size;//bytes
}mem_cs_info_t;
PUBLIC int get_dram_cs_number(void)
{
	mem_cs_info_t *cs_info_ptr = 0x1C00;
	return cs_info_ptr->cs_number;
}
PUBLIC int get_dram_cs0_size(void)
{
	mem_cs_info_t *cs_info_ptr = 0x1C00;
	return cs_info_ptr->cs0_size;
}