/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 */

#include <common.h>
#include <lcd.h>
#include <asm/arch/sprd_lcd.h>
#include <asm/arch/dispc_reg.h>

#include "sprdfb.h"

extern struct panel_if_ctrl sprdfb_mcu_ctrl;
extern struct panel_if_ctrl sprdfb_rgb_ctrl;
extern struct panel_if_ctrl sprdfb_mipi_ctrl;

extern struct panel_spec lcd_nt35510_mipi_spec;
extern struct panel_spec lcd_nt35516_mipi_spec;
extern struct panel_spec lcd_nt35516_mcu_spec;
extern struct panel_spec lcd_nt35516_rgb_spi_spec;
extern struct panel_spec lcd_otm8018b_mipi_spec;
extern struct panel_spec lcd_hx8363_mcu_spec;
extern struct panel_spec lcd_panel_hx8363_rgb_spi_spec;
extern struct panel_spec lcd_panel_hx8363_rgb_spi_spec_viva;
extern struct panel_spec lcd_s6d0139_spec;
extern struct panel_spec lcd_otm1283a_mipi_spec;
extern struct panel_spec lcd_ssd2075_mipi_spec;
extern struct panel_spec lcd_panel_st7789v;
extern struct panel_spec lcd_panel_sc7798_rgb_spi;
extern struct panel_spec lcd_hx8369b_mipi_spec;
extern struct panel_spec lcd_nt35502_mipi_spec;
extern struct panel_spec lcd_panel_ili9341;
extern struct panel_spec lcd_panel_ili9486;
extern struct panel_spec lcd_panel_ili9486_rgb_spi;
extern struct panel_spec lcd_ili9486s1_mipi_spec;
extern struct panel_spec lcd_nt51017_mipi_lvds_spec;
extern struct panel_spec lcd_t8861_mipi_spec;
extern struct panel_spec lcd_hx8379a_mipi_spec;
extern struct panel_spec lcd_hx8389c_mipi_spec;


void sprdfb_panel_remove(struct sprdfb_device *dev);

static ushort colormap[256];

static struct panel_cfg panel_cfg[] = {
#ifdef CONFIG_FB_LCD_NT35510_MIPI
	{
		.lcd_id = 0x10,
		.panel = &lcd_nt35510_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_NT35516_MIPI
	{
		.lcd_id = 0x16,
		.panel = &lcd_nt35516_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_NT35516_MCU
	{
		.lcd_id = 0x16,
		.panel = &lcd_nt35516_mcu_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_NT35516_RGB_SPI
	{
		.lcd_id = 0x16,
		.panel = &lcd_nt35516_rgb_spi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_OTM8018B_MIPI
	{
		.lcd_id = 0x18,
		.panel = &lcd_otm8018b_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_HX8363_MCU
	{
		.lcd_id = 0x18,
		.panel = &lcd_hx8363_mcu_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_VIVA_RGB_SPI
	{
		.lcd_id = 0x63,
		.panel = &lcd_panel_hx8363_rgb_spi_spec_viva,
	},
#endif

#ifdef CONFIG_FB_LCD_HX8363_RGB_SPI
	{
		.lcd_id = 0x84,
		.panel = &lcd_panel_hx8363_rgb_spi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_S6D0139
	{
		.lcd_id = 0x139,
		.panel = &lcd_s6d0139_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_OTM1283A_MIPI
	{
		.lcd_id = 0x1283,
		.panel = &lcd_otm1283a_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_SSD2075_MIPI
	{
		.lcd_id = 0x2075,
		.panel = &lcd_ssd2075_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_ST7789V_MCU
	{
		.lcd_id = 0x7789,
		.panel = &lcd_panel_st7789v,
	},
#endif

#ifdef CONFIG_FB_LCD_SC7798_RGB_SPI
	{
		.lcd_id = 0x7798,
		.panel = &lcd_panel_sc7798_rgb_spi,
	},
#endif

#ifdef CONFIG_FB_LCD_HX8369B_MIPI
	{
		.lcd_id = 0x8369,
		.panel = &lcd_hx8369b_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_NT35502_MIPI
	{
		.lcd_id = 0x8370,
		.panel = &lcd_nt35502_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_ILI9341
	{
		.lcd_id = 0x9341,
		.panel = &lcd_panel_ili9341,
	},
#endif

#ifdef CONFIG_FB_LCD_ILI9486
	{
		.lcd_id = 0x9486,
		.panel = &lcd_panel_ili9486,
	},
#endif

#ifdef CONFIG_FB_LCD_ILI9486_RGB_SPI
	{
		.lcd_id = 0x9486,
		.panel = &lcd_panel_ili9486_rgb_spi,
	},
#endif

#ifdef CONFIG_FB_LCD_ILI9486S1_MIPI
	{
		.lcd_id = 0x8370,
		.panel = &lcd_ili9486s1_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_NT51017_LVDS
	{
		.lcd_id = 0xC749,
		.panel = &lcd_nt51017_mipi_lvds_spec,
	},
#endif
#ifdef CONFIG_FB_LCD_T8861_MIPI
	{
		.lcd_id = 0x04,
		.panel = &lcd_t8861_mipi_spec,
	},
#endif
#ifdef CONFIG_FB_LCD_HX8379A_MIPI
	{
		.lcd_id = 0x8379,
		.panel = &lcd_hx8379a_mipi_spec,
	},
#endif
#ifdef CONFIG_FB_LCD_HX8389C_MIPI
{
	.lcd_id = 0x8389,
	.panel = &lcd_hx8389c_mipi_spec,
},
#endif
};

#ifdef CONFIG_LCD_FWVGA
vidinfo_t panel_info = {
	.vl_col = 480,
	.vl_bpix = 4,
	.vl_row = 854,
	.cmap = colormap,
};
#endif

#ifdef CONFIG_LCD_WVGA
vidinfo_t panel_info = {
	.vl_col = 480,
	.vl_bpix = 4,
	.vl_row = 800,
	.cmap = colormap,
};
#endif

#ifdef CONFIG_LCD_HVGA
vidinfo_t panel_info = {
	.vl_col = 320,
	.vl_bpix = 4,
	.vl_row = 480,
	.cmap = colormap,
};
#endif

#ifdef CONFIG_LCD_QVGA
vidinfo_t panel_info = {
	.vl_col = 240,
	.vl_bpix = 4,
	.vl_row = 320,
	.cmap = colormap,
};
#endif

#ifdef CONFIG_LCD_QHD
vidinfo_t panel_info = {
	.vl_col = 540,
	.vl_bpix = 4,
	.vl_row = 960,
	.cmap = colormap,
};
#endif

#ifdef CONFIG_LCD_720P  //thomaszhang@20130412
vidinfo_t panel_info = {
	.vl_col = 720,
	.vl_bpix = 4,
	.vl_row = 1280,
	.cmap = colormap,
};
#endif

#ifdef CONFIG_LCD_HD  //LiWei
vidinfo_t panel_info = {
	.vl_col = 768,
	.vl_bpix = 4,
	.vl_row = 1024,
	.cmap = colormap,
};
#endif

static int32_t panel_reset_dispc(struct panel_spec *self)
{
	dispc_write(1, DISPC_RSTN);
	mdelay(20);
	dispc_write(0, DISPC_RSTN);
	mdelay(20);
	dispc_write(1, DISPC_RSTN);
	/* wait 10ms util the lcd is stable */
	mdelay(120);
	return 0;
}

static void panel_reset(struct sprdfb_device *dev)
{
	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	//clk/data lane enter LP
	if(NULL != dev->if_ctrl->panel_if_before_panel_reset){
		dev->if_ctrl->panel_if_before_panel_reset(dev);
		mdelay(5);
	}

	//reset panel
	panel_reset_dispc(dev->panel);
}

static int panel_mount(struct sprdfb_device *dev, struct panel_spec *panel)
{
	uint16_t rval = 1;

	printf("sprdfb: [%s], type = %d\n",__FUNCTION__, panel->type);

	switch(panel->type){
	case SPRDFB_PANEL_TYPE_MCU:
		dev->if_ctrl = &sprdfb_mcu_ctrl;
		break;
	case SPRDFB_PANEL_TYPE_RGB:
		dev->if_ctrl = &sprdfb_rgb_ctrl;
		break;
#if ((!defined(CONFIG_SC7710G2)) && (!defined(CONFIG_SPX15)))
	case SPRDFB_PANEL_TYPE_MIPI:
		dev->if_ctrl = &sprdfb_mipi_ctrl;
		break;
#endif
	default:
		printf("sprdfb: [%s]: erro panel type.(%d)",__FUNCTION__, panel->type);
		dev->if_ctrl = NULL;
		rval = 0 ;
		break;
	};

	if(NULL == dev->if_ctrl){
		return -1;
	}

	if(dev->if_ctrl->panel_if_check){
		rval = dev->if_ctrl->panel_if_check(panel);
	}

	if(0 == rval){
		printf("sprdfb: [%s] check panel fail!\n", __FUNCTION__);
		dev->if_ctrl = NULL;
		return -1;
	}

	dev->panel = panel;

	if(NULL == dev->panel->ops->panel_reset){
		dev->panel->ops->panel_reset = panel_reset_dispc;
	}

	dev->if_ctrl->panel_if_mount(dev);

	return 0;
}


int panel_init(struct sprdfb_device *dev)
{
	if((NULL == dev) || (NULL == dev->panel)){
		printf("sprdfb: [%s]: Invalid param\n", __FUNCTION__);
		return -1;
	}

	FB_PRINT("sprdfb: [%s], type = %d\n",__FUNCTION__, dev->panel->type);

	if(NULL != dev->if_ctrl->panel_if_init){
		dev->if_ctrl->panel_if_init(dev);
	}
	return 0;
}

int panel_ready(struct sprdfb_device *dev)
{
	if((NULL == dev) || (NULL == dev->panel)){
		printf("sprdfb: [%s]: Invalid param\n", __FUNCTION__);
		return -1;
	}

	FB_PRINT("sprdfb: [%s],  type = %d\n",__FUNCTION__, dev->panel->type);

	if(NULL != dev->if_ctrl->panel_if_ready){
		dev->if_ctrl->panel_if_ready(dev);
	}

	return 0;
}


static struct panel_spec *adapt_panel_from_readid(struct sprdfb_device *dev)
{
	int id, i, ret, b_panel_reset=0;

	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	for(i = 0;i<(sizeof(panel_cfg))/(sizeof(panel_cfg[0]));i++) {
		printf("sprdfb: [%s]: try panel 0x%x\n", __FUNCTION__, panel_cfg[i].lcd_id);
		ret = panel_mount(dev, panel_cfg[i].panel);
		if(ret < 0){
			printf("sprdfb: panel_mount failed!\n");
			continue;
		}
		dev->ctrl->update_clk(dev);
		panel_init(dev);
		if(b_panel_reset==0)
		{
			panel_reset(dev);
			b_panel_reset=1;
		}
		id = dev->panel->ops->panel_readid(dev->panel);
		if(id == panel_cfg[i].lcd_id) {
			printf("sprdfb: [%s]: LCD Panel 0x%x is attached!\n", __FUNCTION__, panel_cfg[i].lcd_id);

			dev->panel->ops->panel_init(dev->panel);		//zxdebug modify for LCD adaptor 
			
			save_lcd_id_to_kernel(id);
			panel_ready(dev);
			return panel_cfg[i].panel;
		} else {							//zxdbg for LCD adaptor
			printf("sprdfb: [%s]: LCD Panel 0x%x attached fail!go next\n", __FUNCTION__, panel_cfg[i].lcd_id);
			sprdfb_panel_remove(dev);				//zxdebug modify for LCD adaptor 
		}
	}
	
	printf("sprdfb:  [%s]: final failed to attach LCD Panel!\n", __FUNCTION__);
	return NULL;
}

uint16_t sprdfb_panel_probe(struct sprdfb_device *dev)
{
	struct panel_spec *panel;

	if(NULL == dev){
		printf("sprdfb: [%s]: Invalid param\n", __FUNCTION__);
		return -1;
	}

	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	/* can not be here in normal; we should get correct device id from uboot */
	panel = adapt_panel_from_readid(dev);

	if (panel) {
		FB_PRINT("sprdfb: [%s] got panel\n", __FUNCTION__);
		return 0;
	}

	printf("sprdfb: [%s] can not got panel\n", __FUNCTION__);

	return -1;
}

void sprdfb_panel_invalidate_rect(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom)
{
	FB_PRINT("sprdfb: [%s]\n, (%d, %d, %d,%d)",__FUNCTION__, left, top, right, bottom);

	if(NULL != self->ops->panel_invalidate_rect){
		self->ops->panel_invalidate_rect(self, left, top, right, bottom);
	}
}

void sprdfb_panel_invalidate(struct panel_spec *self)
{
	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	if(NULL != self->ops->panel_invalidate){
		self->ops->panel_invalidate(self);
	}
}

void sprdfb_panel_before_refresh(struct sprdfb_device *dev)
{
	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	if(NULL != dev->if_ctrl->panel_if_before_refresh)
		dev->if_ctrl->panel_if_before_refresh(dev);
}

void sprdfb_panel_after_refresh(struct sprdfb_device *dev)
{
	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	if(NULL != dev->if_ctrl->panel_if_after_refresh)
		dev->if_ctrl->panel_if_after_refresh(dev);
}

void sprdfb_panel_remove(struct sprdfb_device *dev)
{
	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	if((NULL != dev->if_ctrl) && (NULL != dev->if_ctrl->panel_if_uninit)){
		dev->if_ctrl->panel_if_uninit(dev);
	}
	dev->panel = NULL;
}

