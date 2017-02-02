/*
 * The codes for io debugging, and could checkout unexpected
 * status of all io/clk/pmu before system into SUSPEND.
 *
 * Copyright (C) 2013-2014 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */
#ifndef	__HISI_LPREGS_H
#define	__HISI_LPREGS_H

struct pmuregs {
	unsigned int ucoffset;
	unsigned int cval;
	unsigned int old_val;
	unsigned int cmask;
};

#define PERI_EN_CLOSE	(1 << 0)
#define PERI_EN_ECO		(1 << 1)
#define LPM3_DIS		(1 << 2)
#define AP_DIS			(1 << 3)
#define CLK_EN_CLOSE	(1 << 4)
#define NULL_OWNER		(1 << 5)
#define SOFT_ECO		(1 << 6)
struct pmu_idx {
	char *name;
	char *module;
	unsigned int status;
	char *status_name;
};

#define PMU_NAME(a, b, c, d) { .name = a, .module = b, .status = c, .status_name = d}

/* note: hisi_pmu_idx[k] must be matched with pmuregs_lookups[k],
 * otherwise the array may be out of range.
 */
struct pmu_idx hisi_pmu_idx[] = {
	PMU_NAME("BUCK1_LDO0_2",	"<SYS CORE/PLL>",						PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BUCK2_LDO1",		"<main sim card for hi6362(modem)>",	AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK3_LDO2",		"<1.8V IO>",							PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BUCK3_LDO3",		"<hi6362 avdd2(modem)>",				AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK3_LDO4",		"<LCD&TP 1.8V I/O>",					AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK3_LDO5",		"<1.8V LDO: PHY/DSI DPHY/CSI DPHY/Tsensor 1.8V/VDDHV/HKADC/EMMC 5.0 PHY>", PERI_EN_CLOSE, "PERI_EN_ECO"),
	PMU_NAME("BUCK3_LDO7",		"<AVDDH_ABB/AVDD1P8_PLL>", 				PERI_EN_CLOSE,	"PERI_EN_CLOSE"),
	PMU_NAME("BUCK3_LDO8",		"<SOC PLL 1.8V/Codec Hi6402 1.8V/CLASS D 1.8V>", SOFT_ECO, "SOFT_ECO"),
	PMU_NAME("BOOST_LDO9",		"<vdd of sd io>", 						AP_DIS,			"AP_DIS"),
	PMU_NAME("BOOST_LDO10",		"<3.2V LDO:USB PHY>", 					PERI_EN_CLOSE,	"PERI_EN_CLOSE"),/* AP soft eco*/
	PMU_NAME("BOOST_LDO11",		"<SIM0>", 								PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BOOST_LDO12",		"<SIM1>", 								PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BOOST_LDO13",		"<TCXO0+CLK_Buffer/camera analog>",		AP_DIS,			"AP_DIS"),
	PMU_NAME("BOOST_LDO14",		"<TCXO1+CLK_Buffer/TRF TUNER/SWITCH VCC 2.8V>",	AP_DIS, "AP_DIS"),
	PMU_NAME("BOOST_LDO15",		"<eMMC Flash>", 						AP_DIS,			"AP_DIS"),
	PMU_NAME("BOOST_LDO16",		"<SD>", 								AP_DIS,			"AP_DIS"),
	PMU_NAME("BOOST_LDO17",		"<LCD &TP AVDD 2.8V>", 					AP_DIS,			"AP_DIS"),
	PMU_NAME("BOOST_LDO19",		"<M_Camera Analog 2.8V>", 				AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK2_LDO20",		"<M_Camera Core 1.0V/1.2V/1.3V>", 		AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK3_LDO21",		"<BISR Fuse>", 							AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK2_LDO22",		"<hi36362 avdd1(modem)>", 				AP_DIS,			"AP_DIS"),
	PMU_NAME("BOOST_LDO23",		"<HKADC+Aux DAC>", 						PERI_EN_CLOSE,	"PERI_EN_CLOSE"),
	PMU_NAME("BOOST_LDO24",		"<X_Sensor AVDD & IRDA>", 				AP_DIS,			"AP_DIS"),
	PMU_NAME("VSYS_LDO25",		"<Camera AFVDD Motor>", 				AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK3_LDO26",		"<DCXO_XO>", 							PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BOOST_LDO27",		"<pmu clk buffer/Hi6362 AVDD3>", 		CLK_EN_CLOSE,	"CLK_EN_CLOSE"),
	PMU_NAME("BUCK3_LDO28",		"<PA STAR 1.8V dig/RF TUNER/SWITCH VIO 1.8V>",	AP_DIS,	"AP_DIS"),
	PMU_NAME("BUCK2_LDO29",		"<hi6402 1.2V dig>", 					PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BUCK1_LDO30",		"<emmc phy 0.8V Core/USB PHY Core>", 	PERI_EN_CLOSE,	"PERI_EN_CLOSE"),
	PMU_NAME("VSYS_LDO31",		"<vibrator>", 							AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK2_LDO32",		"<s_camera core>", 						AP_DIS,			"AP_DIS"),
	PMU_NAME("BUCK0",			"<PERI/PHY/LPDDR3 (CORE)/CSI DSI PHY/Tsensor 0.8V dig/VDD08_ABB modem/ABB 0.8V(DVDD)>", PERI_EN_CLOSE, "PERI_EN_CLOSE"),
	PMU_NAME("BUCK1",			"<1.2V Power plane: DDRPHY CKE; DDRPHY IO/LPDDR3 VDD2, VDDQ and VDDCA/LPDDR4 VDD2 VDDQ/CA>", PERI_EN_ECO, "PERI_EN_ECO"),
	PMU_NAME("BUCK2",			"<1.45V Power plane>", 					PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BUCK3",			"<2.15V Power plane>", 					PERI_EN_ECO,	"PERI_EN_ECO"),
	PMU_NAME("BUCK4",			"<NULL>",								AP_DIS,			"AP_DIS"),
};

#define PMU_LOW(x, y, z) { .ucoffset = (x), .cval = (y), .cmask = (z), .old_val = 0,}
static struct pmuregs pmuregs_lookups[] = {
	PMU_LOW(0x5A , 0x02, 0x02),/*LDO0_2 */
	PMU_LOW(0x5C , 0x02, 0x02),/*LDO1*/
	PMU_LOW(0x5E , 0x02, 0x02),/*LDO2*/
	PMU_LOW(0x60 , 0x02, 0x02),/*LDO3*/
	PMU_LOW(0x62 , 0x02, 0x02),/*LDO4*/
	PMU_LOW(0x64 , 0x02, 0x02),/*LDO5*/
	PMU_LOW(0x66 , 0x02, 0x02),/*LDO7*/
	PMU_LOW(0x68 , 0x02, 0x02),/*LDO8*/
	PMU_LOW(0x6A , 0x02, 0x02),/*LDO9*/
	PMU_LOW(0x6C , 0x02, 0x02),/*LDO10*/
	PMU_LOW(0x6E , 0x02, 0x02),/*LDO11*/
	PMU_LOW(0x70 , 0x02, 0x02),/*LDO12*/
	PMU_LOW(0x72 , 0x02, 0x02),/*LDO13*/
	PMU_LOW(0x74 , 0x02, 0x02),/*LDO14*/
	PMU_LOW(0x76 , 0x02, 0x02),/*LDO15*/
	PMU_LOW(0x78 , 0x02, 0x02),/*LDO16*/
	PMU_LOW(0x7A , 0x02, 0x02),/*LDO17*/
	PMU_LOW(0x7C , 0x02, 0x02),/*LDO19*/
	PMU_LOW(0x7E , 0x02, 0x02),/*LDO20*/
	PMU_LOW(0x80 , 0x02, 0x02),/*LDO21*/
	PMU_LOW(0x82 , 0x02, 0x02),/*LDO22*/
	PMU_LOW(0x84 , 0x02, 0x02),/*LDO23*/
	PMU_LOW(0x86 , 0x02, 0x02),/*LDO24*/
	PMU_LOW(0x88 , 0x02, 0x02),/*LDO25*/
	PMU_LOW(0x8A , 0x02, 0x02),/*LDO26*/
	PMU_LOW(0x8C , 0x02, 0x02),/*LDO27*/
	PMU_LOW(0x8E , 0x02, 0x02),/*LDO28*/
	PMU_LOW(0x90 , 0x02, 0x02),/*LDO29*/
	PMU_LOW(0x92 , 0x02, 0x02),/*LDO30*/
	PMU_LOW(0x94 , 0x02, 0x02),/*LDO31*/
	PMU_LOW(0x96 , 0x02, 0x02),/*LDO32*/

	PMU_LOW(0x98 , 0x02, 0x02),/*BUCK0*/
	PMU_LOW(0x9A , 0x02, 0x02),/*BUCK1*/
	PMU_LOW(0x9C , 0x02, 0x02),/*BUCK2*/
	PMU_LOW(0x9E , 0x02, 0x02),/*BUCK3*/
	PMU_LOW(0xA0 , 0x02, 0x02),/*BUCK4*/

};
#endif
