#ifndef __LDO_H__
#define __LDO_H__

struct ldo_lowpower_cfg fixed_ldo_cfg[] = {
		{ LDO_VDD18,               NO_REG,                  SLP_NO_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ LDO_VDD28,               NO_REG,                  SLP_NO_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ LDO_VDD25,               NO_REG,                  SLP_PD_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ LDO_RF0,                 NO_REG,                  SLP_PD_MODE,             BY_XTL0|BY_XTL1,                        DEFAULT,                                0 },
		{ LDO_RF1,                 NO_REG,                  SLP_PD_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ LDO_RF2,                 NO_REG,                  SLP_PD_MODE,             BY_XTL2,                                DEFAULT,                                0 },
		{ LDO_EMMCIO,              NO_REG,                  SLP_PD_MODE,             NO_REG,                                 NO_REG,                                 0 },
		{ LDO_EMMCCORE,            NO_REG,                  SLP_PD_MODE,             NO_REG,                                 NO_REG,                                 0 },
		{ DCDC_ARM,                NO_REG,                  SLP_PD_MODE,             NO_REG,                                 NO_REG,                                 1 },
		{ DCDC_WRF,                NO_REG,                  SLP_PD_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ DCDC_WPA,                ON,                      SLP_PD_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ DCDC_GEN,                NO_REG,                  SLP_NO_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ DCDC_OTP,                NO_REG,                  SLP_PD_MODE,             NO_REG,                                 NO_REG,                                 0 },
		{ LDO_AVDD18,              NO_REG,                  SLP_PD_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ LDO_SD,                  ON,                      SLP_PD_MODE,             NO_REG,                                 NO_REG,                                 0 },
		{ LDO_SIM0,                ON,                      SLP_NO_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ LDO_SIM1,                ON,                      SLP_NO_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ LDO_SIM2,                ON,                      SLP_PD_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ LDO_CAMA,                ON,                      SLP_PD_MODE,             NO_REG,                                 NO_REG,                                 0 },
		{ LDO_CAMD,                ON,                      SLP_PD_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ LDO_CAMIO,               ON,                      SLP_PD_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ LDO_CAMMOT,              ON,                      SLP_PD_MODE,             NO_REG,                                 NO_REG,                                 0 },
		{ LDO_USB,                 ON,                      SLP_PD_MODE,             NO_REG,                                 NO_REG,                                 0 },
		{ LDO_CLSG,                ON,                      SLP_PD_MODE,             NO_REG,                                 NO_REG,                                 0 },
		{ LDO_LPREF,               ON,                      SLP_PD_MODE,             NO_REG,                                 NO_REG,                                 1 },
		{ DCDC_CORE,               NO_REG,                  SLP_NO_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ DCDC_MEM,                NO_REG,                  SLP_NO_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ DCDC_BG,                 NO_REG,                  SLP_NO_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ BG,                      NO_REG,                  SLP_NO_MODE,             DEFAULT,                                DEFAULT,                                0 },
		{ RESERVED_NUM, 0, 0, 0, 0, 0 }
};

#endif
