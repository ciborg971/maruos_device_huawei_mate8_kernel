/* Copyright (c) 2008-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*/

#include "hisi_fb.h"

#define DTS_COMP_LG_ER69007 "hisilicon,mipi_lg_eR69007"

static struct hisi_fb_panel_data g_panel_data;
static int g_lcd_fpga_flag = 0;

#define LCD_POWER_STATUS_CHECK  (0)


/*******************************************************************************
** Power ON Sequence(sleep mode to Normal mode) begin
*/
//Manufacture,Command,Access,Protect=0h,(Protect,Open)
static char panel_on_cmd1 [] ={0xB0,0x04};
//Interface setting
static char panel_on_cmd2 [] ={0xB3,0x00,0x80,0x00};
//DSI,PHY,operating,freq.,740Mbps~1Gbps(related,tHS-PREPARE,tHS-PREPARE+tHS-ZERO)
static char panel_on_cmd3 [] ={0xB6,0x3B,0xD3,0x00};
//display set 1 
#if 1  //5.7
static char panel_on_cmd4 [] ={
0xC1,0x80,0x08,0x11,0x1F,0x7C,0xF1,0xC7,0x27,0xBF,0x98,0xB3,0xFE,
0xFF,0xF7,0xFE,0xFF,0xD7,0x31,0xF4,0xCF,0x2F,0x7F,0xFC,0xEF,0x03,
0x24,0x69,0x18,0xAA,0x40,0x01,0x42,0x02,0x08,0x00,0x01,0x00,0x01,0x00};
#else //5.5
static char panel_on_cmd4 [] ={
0xC1,0x80,0x08,0x11,0x1F,0xFC,0xF2,0xC9,0x1F,0x5F,0x98,0xB3,0xFE,0xFF,0xF7,
0xFE,0xFF,0xD7,0x31,0xF1,0xCB,0x3F,0x3F,0xFD,0xEF,0x03,0x24,0x69,0x18,
0xAA,0x40,0x01,0x42,0x02,0x08,0x00,0x01,0x00,0x01,0x00,};
#endif
//display set 2
static char panel_on_cmd5 [] ={0xC2,0x01,0xFA,0x00,0x04,0x64,0x08,0x00,0x60,0x00,0x38,0x70,0x00,0x00,0x00};
//display set 3
static char panel_on_cmd6 [] ={0xC3,0x07,0x01,0x08,0x01,0x00,0x00,0x00,0x00};
//Source Timing Setting &Sout Equalize Setting
static char panel_on_cmd7 [] ={0xC4,0x70,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x02,0x01,0x00,0x01,0x01,0x00,0x00,0x00};
//LTPS Timing Setting
static char panel_on_cmd8 [] ={0xC6,0x3C,0x00,0x3C,0x02,0x37,0x01,0x0E,0x01,0x02,0x01,0x02,0x03,0x0F,0x04,0x3C,0x46};
//gamma
static char panel_on_cmd9 [] ={0xC7,0x00,0x16,0x22,0x2c,0x3b,0x48,0x51,0x5d,0x40,0x47,0x53,0x61,0x6a,0x71,0x78,0x00,0x16,0x22,0x2c,0x3b,0x48,0x51,0x5d,0x40,0x47,0x53,0x61,0x6a,0x71,0x78};
static char panel_on_cmd10[] ={0xC8,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0xFC,0x00};
static char panel_on_cmd11[] ={0xC9,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0xFC,0x00};
//Panel,Pin,Control(SOUT,,MOUT)
static char panel_on_cmd12[] ={0xCB,0xAA,0x1E,0xE3,0x55,0xF1,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//Split 4P(8P)/Overlap/LongH
static char panel_on_cmd13[] ={0xCC,0x07};
//V-Blank Control
static char panel_on_cmd14[] ={0xCD,0x3A,0x86,0x3A,0x86,0x8D,0x8D,0x04,0x04,0x00,0x00};
//VGH,Limiter,Mode,On  power setting
static char panel_on_cmd15[] ={0xD0,0x2A,0x01,0x91,0x6A,0xDC,0x59,0x59,0x00,0x00,0x00,0x19,0x99,0x0C,0x00,0x00,0x00};
//power setting for internal
static char panel_on_cmd16[] ={0xD3,0x1B,0x3B,0xBB,0x77,0x77,0x77,0xBB,0xB3,0x33,0x00,0x80,0xA7,0xAF,0x5B,0x5B,0x33,0x33,0x33,0xC0,0x00,0xF2,0x0F,0x7D,0x7C,0xFF,0x0F,0x99,0x00,0x33,0x00,0xFF,0xFF};
//Driving Option and Touch Setting
static char panel_on_cmd17[] ={0xD4,0x57,0x33,0x07,0x00,0xF4};
//VCOM1=-0.418V,,VCOM2=1.639V
static char panel_on_cmd18[] ={0xD5,0x66,0x00,0x00,0x01,0x3D,0x01,0x3D,0x00,0x38,0x00,0x38};
//Sequencer Timing Control for Pon
static char panel_on_cmd19[] ={
0xD7,0x04,0xFF,0x23,0x15,0x75,0xA4,0xC3,0x1F,0xC3,0x1F,0xD9,0x07,0x1C,0x1F,0x30,0x8E,
0x87,0xC7,0xE3,0xF1,0xCC,0xF0,0x1F,0xF0,0x0D,0x70,0x00,0x2A,0x00,0x7E,0x1D,0x07,0x00};
//Compression,method
static char panel_on_cmd20[] ={0xEB,0x00,0x83};
//NVM,Load,Unusing T_SLPOUT=0h,:,NVM,load,OFF,after,exit_sleep_mode
static char panel_on_cmd21[] ={0xD6,0x01};
//MCAP=3h:Lock Manufacture Command Protect
static char panel_on_cmd22[] ={0xB0,0x03};

static char lcd_rotation[] = {
	0x36,0x80,
};

static char te_enable[] = {
	0x35,
	0x01,
};
static char bl_enable[] = {
	0x53,
	0x24,
};

static char exit_sleep[] = {
	0x11,
};

static char display_on[] = {
	0x29,
};
/*
** Power ON Sequence(sleep mode to Normal mode) end
*******************************************************************************/

/*******************************************************************************
** Power OFF Sequence(Normal to power off) begin
*/
static char display_off[] = {
	0x28,
};

static char enter_sleep[] = {
	0x10,
};
/*
** Power OFF Sequence(Normal to power off) end
*******************************************************************************/
static struct dsi_cmd_desc lcd_display_init_cmd[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,sizeof(te_enable), te_enable},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,sizeof(lcd_rotation), lcd_rotation},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd1 ),panel_on_cmd1},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd2 ),panel_on_cmd2},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd3 ),panel_on_cmd3},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd4 ),panel_on_cmd4},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd5 ),panel_on_cmd5},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd6 ),panel_on_cmd6},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd7 ),panel_on_cmd7},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd8 ),panel_on_cmd8},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd9 ),panel_on_cmd9},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd10),panel_on_cmd10},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd11),panel_on_cmd11},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd12),panel_on_cmd12},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd13),panel_on_cmd13},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd14),panel_on_cmd14},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd15),panel_on_cmd15},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd16),panel_on_cmd16},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd17),panel_on_cmd17},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd18),panel_on_cmd18},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd19),panel_on_cmd19},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd20),panel_on_cmd20},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd21),panel_on_cmd21},
	{DTYPE_GEN_LWRITE, 0,100, WAIT_TYPE_US,sizeof(panel_on_cmd22),panel_on_cmd22},
};

static struct dsi_cmd_desc lcd_display_on_cmd[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,sizeof(bl_enable), bl_enable},
	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS, sizeof(exit_sleep), exit_sleep},
	{DTYPE_DCS_WRITE, 0, 60, WAIT_TYPE_MS, sizeof(display_on), display_on},
};

static struct dsi_cmd_desc lcd_display_off_cmd[] = {
	{DTYPE_DCS_WRITE, 0, 50, WAIT_TYPE_MS, sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_MS, sizeof(enter_sleep), enter_sleep},
};

/*******************************************************************************
** LCD VCC
*/
#define VCC_LCDIO_NAME      "lcdio-vcc"
#define VCC_LCDANALOG_NAME  "lcdanalog-vcc"

static struct regulator *vcc_lcdio;
static struct regulator *vcc_lcdanalog;

static struct vcc_desc lcd_vcc_init_cmds[] = {
	/* vcc get */
	{DTYPE_VCC_GET, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_GET, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 0},

	/* vcc set voltage */
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 3100000, 3100000, WAIT_TYPE_MS, 0},
	/* io set voltage */
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCDIO_NAME, &vcc_lcdio, 1800000, 1800000, WAIT_TYPE_MS, 0},
};

static struct vcc_desc lcd_vcc_finit_cmds[] = {
	/* vcc put */
	{DTYPE_VCC_PUT, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_PUT, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 0},
};

static struct vcc_desc lcd_vcc_enable_cmds[] = {
	/* vcc enable */
	{DTYPE_VCC_ENABLE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 3},
	{DTYPE_VCC_ENABLE, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 3},
};

static struct vcc_desc lcd_vcc_disable_cmds[] = {
	/* vcc disable */
	{DTYPE_VCC_DISABLE, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 3},
	{DTYPE_VCC_DISABLE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 3},
};


/*******************************************************************************
** LCD IOMUX
*/
static struct pinctrl_data pctrl;

static struct pinctrl_cmd_desc lcd_pinctrl_init_cmds[] = {
	{DTYPE_PINCTRL_GET, &pctrl, 0},
	{DTYPE_PINCTRL_STATE_GET, &pctrl, DTYPE_PINCTRL_STATE_DEFAULT},
	{DTYPE_PINCTRL_STATE_GET, &pctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc lcd_pinctrl_normal_cmds[] = {
	{DTYPE_PINCTRL_SET, &pctrl, DTYPE_PINCTRL_STATE_DEFAULT},
};

static struct pinctrl_cmd_desc lcd_pinctrl_lowpower_cmds[] = {
	{DTYPE_PINCTRL_SET, &pctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc sharp_lcd_pinctrl_finit_cmds[] = {
	{DTYPE_PINCTRL_PUT, &pctrl, 0},
};


/*******************************************************************************
** LCD GPIO
*/
#define GPIO_LCD_VCC3V1_NAME    "gpio_lcd_vcc3v1"
#define GPIO_LCD_VCC1V8_NAME    "gpio_lcd_vcc1v8"
//#define GPIO_LCD_BL_ENABLE_NAME "gpio_lcd_bl_enable"
#define GPIO_LCD_RESET_NAME "gpio_lcd_reset"
#define GPIO_LCD_P5V5_ENABLE_NAME   "gpio_lcd_p5v5_enable"
#define GPIO_LCD_N5V5_ENABLE_NAME "gpio_lcd_n5v5_enable"


static uint32_t gpio_lcd_reset;
static uint32_t gpio_lcd_p5v5_enable;
static uint32_t gpio_lcd_n5v5_enable;

static struct gpio_desc asic_lcd_gpio_request_cmds[] = {
    /* AVDD_5.8V */
    {DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
        GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
    /* AVEE_-5.8V */
    {DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
        GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
    /* reset */
    {DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
        GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
    /* backlight enable */
    //{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
   //     GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
};

static struct gpio_desc asic_lcd_gpio_normal_cmds[] = {
    /* AVDD_5.5V */
    {DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
        GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 1},
    /* AVEE_-5.5V */
    {DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 20,
        GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 1},
    /* reset */
    {DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
        GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
    {DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
        GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
    {DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
        GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
    /* backlight enable */
   // {DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 20,
     //   GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 1},
};

static struct gpio_desc asic_lcd_gpio_free_cmds[] = {
    /* backlight enable */
   // {DTYPE_GPIO_FREE, WAIT_TYPE_US, 50,
    //    GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
    /* AVEE_-5.5V */
    {DTYPE_GPIO_FREE, WAIT_TYPE_US, 50,
        GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
    /* AVDD_5.5V */
    {DTYPE_GPIO_FREE, WAIT_TYPE_US, 50,
        GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
    /* reset */
    {DTYPE_GPIO_FREE, WAIT_TYPE_US, 50,
        GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
};

static struct gpio_desc asic_lcd_gpio_lowpower_cmds[] = {
    /* backlight enable */
   // {DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
    //    GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
    /* AVEE_-5.5V */
    {DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
        GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
    /* AVDD_5.5V*/
    {DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
        GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
    /* reset */
    {DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
        GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},

    /* backlight enable input */
    //{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
     //   GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
    /* AVEE_-5.8V input */
    {DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 5,
        GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
    /* AVDD_5.8V input */
    {DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 5,
        GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
    /* reset input */
    {DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
        GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
};

/*******************************************************************************
**
*/
static int mipi_lg_panel_set_fastboot(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

		// lcd pinctrl normal
		pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
		ARRAY_SIZE(lcd_pinctrl_normal_cmds));

		// lcd gpio request
		gpio_cmds_tx(asic_lcd_gpio_request_cmds, \
		ARRAY_SIZE(asic_lcd_gpio_request_cmds));


	// backlight on
	hisi_lcd_backlight_on(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_lg_panel_on(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *mipi_dsi0_base = NULL;
#if LCD_POWER_STATUS_CHECK
	uint32_t status = 0;
	uint32_t try_times = 0;
#endif

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);

	pinfo = &(hisifd->panel_info);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {

			// lcd vcc enable
			vcc_cmds_tx(pdev, lcd_vcc_enable_cmds,
			ARRAY_SIZE(lcd_vcc_enable_cmds));

		pinfo->lcd_init_step = LCD_INIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_LP_SEND_SEQUENCE) {
			// lcd pinctrl normal
			pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
			ARRAY_SIZE(lcd_pinctrl_normal_cmds));

			// lcd gpio request
			gpio_cmds_tx(asic_lcd_gpio_request_cmds, \
			ARRAY_SIZE(asic_lcd_gpio_request_cmds));

			// lcd gpio normal
			gpio_cmds_tx(asic_lcd_gpio_normal_cmds, \
			ARRAY_SIZE(asic_lcd_gpio_normal_cmds));


		// lcd display on sequence
		mipi_dsi_cmds_tx(lcd_display_init_cmd, \
			ARRAY_SIZE(lcd_display_init_cmd), mipi_dsi0_base);
#if 0
		if (is_mipi_cmd_panel(hisifd)) {
			mipi_dsi_cmds_tx(lcd_display_command_cmd, \
				ARRAY_SIZE(lcd_display_command_cmd), mipi_dsi0_base);
		} else {
			mipi_dsi_cmds_tx(lcd_display_video_cmd, \
				ARRAY_SIZE(lcd_display_video_cmd), mipi_dsi0_base);
		}

		if (pinfo->ifbc_type == IFBC_TYPE_VESA3X_DUAL) {
			mipi_dsi_cmds_tx(lcd_ifbc_vesa3x_en_cmd, \
				ARRAY_SIZE(lcd_ifbc_vesa3x_en_cmd), mipi_dsi0_base);
		} else {
			mipi_dsi_cmds_tx(lcd_ifbc_vesa3x_dis_cmd, \
				ARRAY_SIZE(lcd_ifbc_vesa3x_dis_cmd), mipi_dsi0_base);
		}
#endif
		mipi_dsi_cmds_tx(lcd_display_on_cmd, \
			ARRAY_SIZE(lcd_display_on_cmd), mipi_dsi0_base);

	#if LCD_POWER_STATUS_CHECK
		//check lcd power status
		outp32(mipi_dsi0_base + MIPIDSI_GEN_HDR_OFFSET, 0x0A06);
		status = inp32(mipi_dsi0_base + MIPIDSI_CMD_PKT_STATUS_OFFSET);
		while (status & 0x10) {
			udelay(50);
			if (++try_times > 100) {
				try_times = 0;
				HISI_FB_ERR("Read lcd power status timeout!\n");
				break;
			}

			status = inp32(mipi_dsi0_base + MIPIDSI_CMD_PKT_STATUS_OFFSET);
		}

		status = inp32(mipi_dsi0_base + MIPIDSI_GEN_PLD_DATA_OFFSET);
		HISI_FB_INFO("LCD Power State = 0x%x.\n", status);
	#endif

		pinfo->lcd_init_step = LCD_INIT_MIPI_HS_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_HS_SEND_SEQUENCE) {
		;
	} else {
		HISI_FB_ERR("failed to init lcd!\n");
	}

	// backlight on
	hisi_lcd_backlight_on(pdev);

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_lg_panel_off(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	// backlight off
	hisi_lcd_backlight_off(pdev);

	udelay(10);

	// lcd display off sequence
	mipi_dsi_cmds_tx(lcd_display_off_cmd, \
	ARRAY_SIZE(lcd_display_off_cmd), mipi_dsi0_base);

		// lcd gpio lowpower
		gpio_cmds_tx(asic_lcd_gpio_lowpower_cmds, \
		    ARRAY_SIZE(asic_lcd_gpio_lowpower_cmds));

		// lcd gpio free
		gpio_cmds_tx(asic_lcd_gpio_free_cmds, \
		    ARRAY_SIZE(asic_lcd_gpio_free_cmds));

		// lcd pinctrl lowpower
		pinctrl_cmds_tx(pdev, lcd_pinctrl_lowpower_cmds,
		    ARRAY_SIZE(lcd_pinctrl_lowpower_cmds));

		// lcd vcc disable
		vcc_cmds_tx(pdev, lcd_vcc_disable_cmds,
		    ARRAY_SIZE(lcd_vcc_disable_cmds));

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_lg_panel_remove(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);

	if (!hisifd) {
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

		// lcd vcc finit
		vcc_cmds_tx(pdev, lcd_vcc_finit_cmds,
		ARRAY_SIZE(lcd_vcc_finit_cmds));

		// lcd pinctrl finit
		pinctrl_cmds_tx(pdev, sharp_lcd_pinctrl_finit_cmds,
		ARRAY_SIZE(sharp_lcd_pinctrl_finit_cmds));

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_lg_panel_set_backlight(struct platform_device *pdev, uint32_t bl_level)
{
	int ret = 0;
	char __iomem *mipi_dsi0_base = NULL;
	struct hisi_fb_data_type *hisifd = NULL;

	char bl_level_adjust[2] = {
		0x51,
		0x00,
	};

	struct dsi_cmd_desc lcd_bl_level_adjust[] = {
		{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(bl_level_adjust), bl_level_adjust},
	};

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	//HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	HISI_FB_DEBUG("fb%d, bl_level=%d.\n", hisifd->index, bl_level);

	if (hisifd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		ret = hisi_pwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_BLPWM) {
		ret = hisi_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_SH_BLPWM) {
		ret = hisi_sh_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_MIPI) {
		mipi_dsi0_base = hisifd->mipi_dsi0_base;

		//bl_level_adjust[1] = bl_level * 255 / hisifd->panel_info.bl_max;
		bl_level_adjust[1] = bl_level;
		mipi_dsi_cmds_tx(lcd_bl_level_adjust, \
		ARRAY_SIZE(lcd_bl_level_adjust), mipi_dsi0_base);
	} else {
		HISI_FB_ERR("fb%d, not support this bl_set_type(%d)!\n",
		hisifd->index, hisifd->panel_info.bl_set_type);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static char lcd_disp_x[] = {
	0x2A,
	0x00, 0x00,0x04,0x37
};

static char lcd_disp_y[] = {
	0x2B,
	0x00, 0x00,0x07,0x7F
};

static struct dsi_cmd_desc set_display_address[] = {
	{DTYPE_DCS_LWRITE, 0, 5, WAIT_TYPE_US,
		sizeof(lcd_disp_x), lcd_disp_x},
	{DTYPE_DCS_LWRITE, 0, 5, WAIT_TYPE_US,
		sizeof(lcd_disp_y), lcd_disp_y},
};

static int mipi_lg_panel_set_display_region(struct platform_device *pdev,
	struct dss_rect *dirty)
{
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(pdev == NULL || dirty == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	pinfo = &(hisifd->panel_info);

	if ((dirty->x != 0) || (dirty->w != pinfo->xres) ||
		((dirty->y % 32) != 0) || ((dirty->h % 32) != 0) ||
		(dirty->x >= pinfo->xres) || (dirty->w > pinfo->xres) || ((dirty->x + dirty->w) > pinfo->xres) ||
		(dirty->y >= pinfo->yres) || (dirty->h > pinfo->yres) || ((dirty->y + dirty->h) > pinfo->yres)) {
		HISI_FB_ERR("dirty_region(%d,%d, %d,%d) not support!\n",
		dirty->x, dirty->y, dirty->w, dirty->h);

		BUG_ON(1);
	}

	lcd_disp_x[1] = (dirty->x >> 8) & 0xff;
	lcd_disp_x[2] = dirty->x & 0xff;
	lcd_disp_x[3] = ((dirty->x + dirty->w - 1) >> 8) & 0xff;
	lcd_disp_x[4] = (dirty->x + dirty->w - 1) & 0xff;
	lcd_disp_y[1] = (dirty->y >> 8) & 0xff;
	lcd_disp_y[2] = dirty->y & 0xff;
	lcd_disp_y[3] = ((dirty->y + dirty->h - 1) >> 8) & 0xff;
	lcd_disp_y[4] = (dirty->y + dirty->h - 1) & 0xff;

	mipi_dsi_cmds_tx(set_display_address, \
	ARRAY_SIZE(set_display_address), mipi_dsi0_base);

	return 0;
}


/*******************************************************************************
**
*/
static struct hisi_panel_info g_panel_info = {0};
static struct hisi_fb_panel_data g_panel_data = {
	.panel_info = &g_panel_info,
	.set_fastboot = mipi_lg_panel_set_fastboot,
	.on = mipi_lg_panel_on,
	.off = mipi_lg_panel_off,
	.remove = mipi_lg_panel_remove,
	.set_backlight = mipi_lg_panel_set_backlight,
	.set_display_region = mipi_lg_panel_set_display_region,
};


/*******************************************************************************
**
*/
static int mipi_lg_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_panel_info *pinfo = NULL;
	struct device_node *np = NULL;
	uint32_t bl_type = 0;
	uint32_t lcd_display_type = 0;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_LG_ER69007);
		if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_LG_ER69007);
		goto err_return;
	}
	g_lcd_fpga_flag = 0;

	ret = of_property_read_u32(np, LCD_DISPLAY_TYPE_NAME, &lcd_display_type);
	if (ret) {
		HISI_FB_ERR("get lcd_display_type failed!\n");
		lcd_display_type = PANEL_MIPI_CMD;
	}
	HISI_FB_INFO("lcd_display_type=%u!\n", lcd_display_type);

	ret = of_property_read_u32(np, LCD_BL_TYPE_NAME, &bl_type);
	if (ret) {
		HISI_FB_ERR("get lcd_bl_type failed!\n");
		bl_type = BL_SET_BY_MIPI;
	}
	HISI_FB_INFO("bl_type=0x%x.", bl_type);

	if (hisi_fb_device_probe_defer(lcd_display_type, bl_type)) {
		goto err_probe_defer;
	}

	HISI_FB_DEBUG("+.\n");

	HISI_FB_INFO("%s\n", DTS_COMP_LG_ER69007);

		//gpio_1_1
		gpio_lcd_n5v5_enable = of_get_named_gpio(np, "gpios", 0);
		//gpio_1_2
		//gpio_lcd_bl_enable = of_get_named_gpio(np, "gpios", 1);
		// gpio_1_7
		gpio_lcd_p5v5_enable = of_get_named_gpio(np, "gpios", 1);
		//gpio_2_4
		gpio_lcd_reset = of_get_named_gpio(np, "gpios", 2);

	HISI_FB_INFO("enn=%d,enp=%d,rst=%d",gpio_lcd_n5v5_enable,gpio_lcd_p5v5_enable,gpio_lcd_reset);
	pdev->id = 1;
	// init lcd panel info
	pinfo = g_panel_data.panel_info;
	memset(pinfo, 0, sizeof(struct hisi_panel_info));
	pinfo->xres = 1440;
	pinfo->yres = 2560;
	pinfo->width = 75;
	pinfo->height = 133;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = LCD_RGB888;
	pinfo->bgr_fmt = LCD_RGB;
	pinfo->bl_set_type = bl_type;

	if (pinfo->bl_set_type == BL_SET_BY_BLPWM)
		pinfo->blpwm_input_ena = 0;

//#ifdef CONFIG_BACKLIGHT_10000
#if 0
	pinfo->bl_min = 157;
	pinfo->bl_max = 9960;
	pinfo->blpwm_precision_type = BLPWM_PRECISION_10000_TYPE;
#else
	pinfo->bl_min = 4;
	pinfo->bl_max = 255;
	pinfo->bl_default = 102;
#endif

	pinfo->type = lcd_display_type;

	pinfo->frc_enable = 0;
	pinfo->esd_enable = 0;

	//sbl
	pinfo->sbl_support = 0;
	pinfo->smart_bl.strength_limit = 0xff;
	pinfo->smart_bl.calibration_a = 0;
	pinfo->smart_bl.calibration_b = 0;
	pinfo->smart_bl.calibration_c = 0;
	pinfo->smart_bl.calibration_d = 0;
	pinfo->smart_bl.t_filter_control = 0;
	pinfo->smart_bl.backlight_min = 0;
	pinfo->smart_bl.backlight_max = 0;
	pinfo->smart_bl.backlight_scale = 0xffff;
	pinfo->smart_bl.ambient_light_min = 0;
	pinfo->smart_bl.filter_a = 0;
	pinfo->smart_bl.filter_b = 0;
		//ldi
		if (is_mipi_cmd_panel_ext(pinfo)) {
			//65.7fps
			pinfo->ldi.h_back_porch = 96;
			pinfo->ldi.h_front_porch = 108;
			pinfo->ldi.h_pulse_width = 48;
			pinfo->ldi.v_back_porch = 12;
			pinfo->ldi.v_front_porch = 14;
			pinfo->ldi.v_pulse_width = 4;

			pinfo->pxl_clk_rate = 288 * 1000000;
		} else {
			// 37.5fps;
			pinfo->ldi.h_back_porch = 156;
			pinfo->ldi.h_front_porch = 180;
			pinfo->ldi.h_pulse_width = 48;
			pinfo->ldi.v_back_porch = 26;
			pinfo->ldi.v_front_porch = 26;
			pinfo->ldi.v_pulse_width = 18;

			pinfo->pxl_clk_rate = 180 * 1000000;
		}

		//mipi
		pinfo->mipi.dsi_bit_clk = 480;
		pinfo->mipi.dsi_bit_clk_val1 = 471;
		pinfo->mipi.dsi_bit_clk_val2 = 480;
		pinfo->mipi.dsi_bit_clk_val3 = 490;
		pinfo->mipi.dsi_bit_clk_val4 = 500;
		//pinfo->mipi.dsi_bit_clk_val5 = ;
		pinfo->dsi_bit_clk_upt_support = 0;
		pinfo->mipi.dsi_bit_clk_upt = pinfo->mipi.dsi_bit_clk;

		pinfo->mipi.non_continue_en = 0;
	//mipi
	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.max_tx_esc_clk = 10 * 1000000;
	pinfo->mipi.burst_mode = 0;

	pinfo->pxl_clk_rate_div = 1;

	//is command_mode or video_mode
	if (is_mipi_cmd_panel_ext(pinfo)) {
		pinfo->vsync_ctrl_type = 0; //VSYNC_CTRL_ISR_OFF | VSYNC_CTRL_MIPI_ULPS | VSYNC_CTRL_CLK_OFF;
		pinfo->dirty_region_updt_support = 0;
		pinfo->dirty_region_info.left_align = -1;
		pinfo->dirty_region_info.right_align = -1;
		pinfo->dirty_region_info.top_align = 32;
		pinfo->dirty_region_info.bottom_align = 32;
		pinfo->dirty_region_info.w_align = -1;
		pinfo->dirty_region_info.h_align = -1;
		pinfo->dirty_region_info.w_min = pinfo->xres;
		pinfo->dirty_region_info.h_min = -1;
		pinfo->dirty_region_info.top_start = -1;
		pinfo->dirty_region_info.bottom_start = -1;
	} else {
		pinfo->mipi.burst_mode = DSI_BURST_SYNC_PULSES_1;
		pinfo->vsync_ctrl_type = 0;
		pinfo->dirty_region_updt_support = 0;
	}

	//is dual_mipi or single_mipi
	if (is_dual_mipi_panel_ext(pinfo))  {
		pinfo->ifbc_type = IFBC_TYPE_NONE;
		pinfo->pxl_clk_rate_div = 2;
	} else {
		pinfo->ifbc_type = IFBC_TYPE_RSP3X;
		pinfo->ifbc_cmp_dat_rev0 = 0;
		pinfo->ifbc_cmp_dat_rev1 = 0;
		pinfo->ifbc_auto_sel = 1;

		pinfo->pxl_clk_rate_div *= 3;
	}

	if (pinfo->pxl_clk_rate_div > 1) {
		pinfo->ldi.h_back_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_front_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_pulse_width /= pinfo->pxl_clk_rate_div;
	}

		// lcd vcc init
		ret = vcc_cmds_tx(pdev, lcd_vcc_init_cmds,
			ARRAY_SIZE(lcd_vcc_init_cmds));
		if (ret != 0) {
			HISI_FB_ERR("LCD vcc init failed!\n");
			goto err_return;
		}

		// lcd pinctrl init
		ret = pinctrl_cmds_tx(pdev, lcd_pinctrl_init_cmds,
			ARRAY_SIZE(lcd_pinctrl_init_cmds));
		if (ret != 0) {
			HISI_FB_ERR("Init pinctrl failed, defer\n");
			goto err_return;
		}

		// lcd vcc enable
		if (is_fastboot_display_enable()) {
			vcc_cmds_tx(pdev, lcd_vcc_enable_cmds,
			ARRAY_SIZE(lcd_vcc_enable_cmds));
		}

	// alloc panel device data
	ret = platform_device_add_data(pdev, &g_panel_data,
		sizeof(struct hisi_fb_panel_data));
	if (ret) {
		HISI_FB_ERR("platform_device_add_data failed!\n");
		goto err_device_put;
	}

	hisi_fb_add_device(pdev);

	HISI_FB_DEBUG("-.\n");

	return 0;

err_device_put:
	platform_device_put(pdev);
err_return:
	return ret;
err_probe_defer:
	return -EPROBE_DEFER;

	return ret;
}

static const struct of_device_id hisi_panel_match_table[] = {
	{
		.compatible = DTS_COMP_LG_ER69007,
		.data = NULL,
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_panel_match_table);

static struct platform_driver this_driver = {
	.probe = mipi_lg_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_lg_eR69007",
		.of_match_table = of_match_ptr(hisi_panel_match_table),
	},
};

static int __init mipi_lg_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(mipi_lg_panel_init);
