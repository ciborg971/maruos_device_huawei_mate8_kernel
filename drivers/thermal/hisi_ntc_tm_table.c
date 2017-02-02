/*
 * Copyright (c) 2011 Hisilicon Technologies Co., Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <linux/err.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/input.h>
#include <linux/time.h>
#include <linux/wakelock.h>
#include <linux/syscalls.h>
#include <linux/mutex.h>
#include <linux/io.h>
#include <linux/huawei/hisi_adc.h>
#include "hisi_peripheral_tm.h"

#define PRORATE_OF_INIT	1000 /*in order to resolve divisor less than zero*/
#define multiple		100
#define NCP_GENERAL1_NUM	34

enum ntc_tm_table_list {
	ncp_general1_flag = 0,
	austin_adc2temp_flag = 1,
	austin_pa_volt2temp_flag = 2,
	austin_soc_volt2temp_flag =3
};

#define ADC_RTMP_DEFAULT_VALUE	1200 /*base default value for ap temp*/

/*hi3630 IC 1 temperature from -40 to 125*/
static int hi3630_volt_to_temp_general1[NCP_GENERAL1_NUM][2] = {
	{2561, 125}, {2952, 120}, {3415, 115}, {3966, 110}, {4623, 105},
	{5410, 100}, {6357, 95}, {7500, 90}, {8887, 85}, {10580, 80},
	{12640, 75}, {15180, 70}, {18320, 65}, {22220, 60}, {27090, 55},
	{33190, 50}, {40900, 45}, {50680, 40}, {63180, 35}, {79230, 30},
	{100000, 25}, {127000, 20}, {162500, 15}, {209400, 10}, {271800, 5},
	{355600, 0}, {469100, -5}, {624100, -10}, {837800, -15}, {1135000, -20},
	{1554000, -25}, {2149000, -30}, {3005000, -35}, {4251000, -40},
};

/*DCXO: {volt(mv),temp(C)}*/
int austin_hkadc_volt_temp_table[][2] =
{
	{51,120},{59,115},{68,110},{79,105},{92,100},{107,95},
	{125,90},{146,85},{172,80},{201,75},{237,70},{278,65},
	{327,60},{383,55},{448,50},{522,45},{605,40},{696,35},
	{795,30},{900,25},{1007,20},{1114,15},{1218,10},{1316,5},
	{1405,0},{1484,-5},{1552,-10},{1608,-15},{1655,-20},{1692,-25},
	{1720,-30},{1742,-35}
};

int austin_pa_volt_temp_table[][2] =
{
 {44,125}, {46,124}, {47,123}, {48,122}, {50,121}, {51,120},
 {53,119}, {54,118}, {56,117}, {57,116}, {59,115}, {61,114}, {62,113}, {64,112},
 {66,111}, {68,110}, {70,109}, {72,108}, {74,107}, {77,106}, {79,105}, {81,104},
 {84,103}, {86,102}, {89,101}, {92,100}, {95,99}, {98,98}, {101,97}, {104,96},
 {107,95}, {110,94}, {114,93}, {118,92}, {121,91}, {125,90}, {129,89}, {133,88},
 {137,87}, {142,86}, {146,85}, {151,84}, {156,83}, {161,82}, {166,81}, {172,80},
 {177,79}, {183,78}, {189,77}, {195,76}, {201,75}, {208,74}, {215,73}, {222,72},
 {229,71}, {237,70}, {245,69}, {253,68}, {261,67}, {269,66}, {278,65}, {287,64},
 {297,63}, {306,62}, {316,61}, {327,60}, {337,59}, {348,58}, {360,57}, {371,56},
 {383,55}, {395,54}, {408,53}, {421,52}, {434,51}, {448,50}, {462,49}, {477,48},
 {491,47}, {506,46}, {522,45}, {538,44}, {554,43}, {571,42}, {588,41}, {605,40},
 {623,39}, {641,38}, {659,37}, {677,36}, {696,35}, {716,34}, {735,33}, {755,32},
 {775,31}, {795,30}, {816,29}, {836,28}, {857,27}, {878,26}, {900,25}, {921,24},
 {942,23}, {964,22}, {985,21}, {1007,20}, {1028,19}, {1050,18}, {1071,17}, {1093,16},
 {1114,15}, {1135,14}, {1156,13}, {1177,12}, {1197,11}, {1218,10}, {1238,9}, {1258,8},
 {1277,7}, {1296,6}, {1315,5}, {1334,4}, {1352,3}, {1370,2}, {1387,1}, {1404,0},
 {1421,-1}, {1437,-2}, {1453,-3}, {1468,-4}, {1483,-5}, {1498,-6}, {1512,-7}, {1525,-8},
 {1538,-9}, {1551,-10}, {1563,-11}, {1575,-12}, {1586,-13}, {1597,-14}, {1608,-15}, {1618,-16},
 {1627,-17}, {1636,-18}, {1645,-19}, {1654,-20}, {1662,-21}, {1670,-22}, {1677,-23}, {1684,-24},
 {1691,-25}, {1697,-26}, {1703,-27}, {1709,-28}, {1714,-29}, {1719,-30}, {1724,-31}, {1729,-32},
 {1733,-33}, {1738,-34}, {1742,-35}, {1745,-36}, {1749,-37}, {1752,-38}, {1755,-39}, {1758,-40},
};

int austin_soc_volt_temp_table[][2] =
{
 {44,125}, {46,124}, {47,123}, {48,122}, {50,121}, {51,120},
 {53,119}, {54,118}, {56,117}, {57,116}, {59,115}, {61,114}, {62,113}, {64,112},
 {66,111}, {68,110}, {70,109}, {72,108}, {74,107}, {77,106}, {79,105}, {81,104},
 {84,103}, {86,102}, {89,101}, {92,100}, {95,99}, {98,98}, {101,97}, {104,96},
 {107,95}, {110,94}, {114,93}, {118,92}, {121,91}, {125,90}, {129,89}, {133,88},
 {137,87}, {142,86}, {146,85}, {151,84}, {156,83}, {161,82}, {166,81}, {172,80},
 {177,79}, {183,78}, {189,77}, {195,76}, {201,75}, {208,74}, {215,73}, {222,72},
 {229,71}, {237,70}, {245,69}, {253,68}, {261,67}, {269,66}, {278,65}, {287,64},
 {297,63}, {306,62}, {316,61}, {327,60}, {337,59}, {348,58}, {360,57}, {371,56},
 {383,55}, {395,54}, {408,53}, {421,52}, {434,51}, {448,50}, {462,49}, {477,48},
 {491,47}, {506,46}, {522,45}, {538,44}, {554,43}, {571,42}, {588,41}, {605,40},
 {623,39}, {641,38}, {659,37}, {677,36}, {696,35}, {716,34}, {735,33}, {755,32},
 {775,31}, {795,30}, {816,29}, {836,28}, {857,27}, {878,26}, {900,25}, {921,24},
 {942,23}, {964,22}, {985,21}, {1007,20}, {1028,19}, {1050,18}, {1071,17}, {1093,16},
 {1114,15}, {1135,14}, {1156,13}, {1177,12}, {1197,11}, {1218,10}, {1238,9}, {1258,8},
 {1277,7}, {1296,6}, {1315,5}, {1334,4}, {1352,3}, {1370,2}, {1387,1}, {1404,0},
 {1421,-1}, {1437,-2}, {1453,-3}, {1468,-4}, {1483,-5}, {1498,-6}, {1512,-7}, {1525,-8},
 {1538,-9}, {1551,-10}, {1563,-11}, {1575,-12}, {1586,-13}, {1597,-14}, {1608,-15}, {1618,-16},
 {1627,-17}, {1636,-18}, {1645,-19}, {1654,-20}, {1662,-21}, {1670,-22}, {1677,-23}, {1684,-24},
 {1691,-25}, {1697,-26}, {1703,-27}, {1709,-28}, {1714,-29}, {1719,-30}, {1724,-31}, {1729,-32},
 {1733,-33}, {1738,-34}, {1742,-35}, {1745,-36}, {1749,-37}, {1752,-38}, {1755,-39}, {1758,-40},
};

/****************************************************
  Function:       int change_volt_to_temp()
  Description: volt to temp
  Input:
  Output:         NA
  Return:         get temperature
  Others:          NA
*****************************************************/
static int change_volt_to_temp(int iResistance, int index_min, int index_max, int table_list)
{
	int prorate = 0;
	int resistance_max = 0;
	int resistance_min = 0;
	int temper_top = 0;
	int temper_bottom = 0;
	int itemper = 0;

	switch (table_list) {
	case ncp_general1_flag:
		resistance_min = hi3630_volt_to_temp_general1[index_min][0];
		resistance_max = hi3630_volt_to_temp_general1[index_max][0];
		temper_bottom = hi3630_volt_to_temp_general1[index_min][1];
		temper_top = hi3630_volt_to_temp_general1[index_max][1];
		break;
	case austin_adc2temp_flag:
		resistance_min = austin_hkadc_volt_temp_table[index_min][0];
		resistance_max = austin_hkadc_volt_temp_table[index_max][0];
		temper_bottom = austin_hkadc_volt_temp_table[index_min][1];
		temper_top = austin_hkadc_volt_temp_table[index_max][1];
		break;
	case austin_pa_volt2temp_flag:
		resistance_min = austin_pa_volt_temp_table[index_min][0];
		resistance_max = austin_pa_volt_temp_table[index_max][0];
		temper_bottom = austin_pa_volt_temp_table[index_min][1];
		temper_top = austin_pa_volt_temp_table[index_max][1];
		break;
	case austin_soc_volt2temp_flag:
		resistance_min = austin_soc_volt_temp_table[index_min][0];
		resistance_max = austin_soc_volt_temp_table[index_max][0];
		temper_bottom = austin_soc_volt_temp_table[index_min][1];
		temper_top = austin_soc_volt_temp_table[index_max][1];
		break;
	default:
		pr_err("ADC channel is not exist!\n\r");
		break;
	}
	if ((resistance_max - resistance_min) == 0) {
		return 25;
	}
	prorate =  ((resistance_max - iResistance) * PRORATE_OF_INIT) / (resistance_max - resistance_min);
	itemper = ((temper_bottom - temper_top) * prorate) / PRORATE_OF_INIT + temper_top;
	return itemper;
}

/****************************************************************************
  Function:       int get_ap_ntc_temperature(int iResistance)
  Description:    dichotomy
  Input:          NA
  Output:         NA
  Return:         return temperature
  Others:         NA
*****************************************************************************/
static int get_ntc_temperature(int iResistance, int channel, int **volt_to_temperature, int table_list)
{
	int iLow = 0;
	int iUpper = 0 ;
	int temperature = 0;
	int iMid = 0;
	int *temp_idex = (int *)volt_to_temperature;

	if (ncp_general1_flag == table_list) {
		iUpper = sizeof(hi3630_volt_to_temp_general1) / sizeof(hi3630_volt_to_temp_general1[0][0]) / 2;
	}
	else if (austin_adc2temp_flag == table_list) {
		iUpper = sizeof(austin_hkadc_volt_temp_table) / sizeof(austin_hkadc_volt_temp_table[0][0]) / 2;
	}
	else if (austin_pa_volt2temp_flag == table_list) {
		iUpper = sizeof(austin_pa_volt_temp_table) / sizeof(austin_pa_volt_temp_table[0][0]) / 2;
	}
	else if (austin_soc_volt2temp_flag == table_list) {
		iUpper = sizeof(austin_soc_volt_temp_table) / sizeof(austin_soc_volt_temp_table[0][0]) / 2;
	}


	if (iResistance < *(temp_idex + 2 * 0 + 0)) {
		temperature = *(temp_idex + 2 * 0 + 1);
		return temperature;
	} else if (iResistance > *(temp_idex + 2 * (iUpper - 1) + 0)) {
		temperature = *(temp_idex + 2 * (iUpper - 1) + 1);
		return temperature;
	}

	while (iLow <= iUpper) {
		iMid = (iLow + iUpper) / 2;
		if (*(temp_idex + 2 * iMid + 0) > iResistance) {
			if (*(temp_idex + 2 * (iMid - 1) + 0) < iResistance) {
				temperature = change_volt_to_temp(iResistance,
						(iMid - 1), iMid, table_list);
				return temperature;
			}
			iUpper = iMid - 1;
		} else if (*(temp_idex + 2 * iMid + 0) < iResistance) {
			if (*(temp_idex + 2 * (iMid + 1) + 0) > iResistance) {
				temperature = change_volt_to_temp(iResistance,
					iMid, (iMid + 1), table_list);
			return temperature;
			}
			iLow = iMid + 1;
		} else {
			temperature = *(temp_idex + 2 * iMid + 1);
			break;
		}
	}
	return temperature;
}

/****************************************************************************
  Function:       int getcalctemperature(int BatteryTemperature)
  Description:    get temperature value
  Calls:          NA
  Data Accessed:  NA
  Data Updated:   NA
  Input:          NA
  Output:         NA
  Return:         vol to temp
  Others:         NA
*****************************************************************************/


int hisi_peripheral_get_temp(struct periph_tsens_tm_device_sensor *chip, unsigned long *temp)
{
	int tempdata = 0;
	int adc_value = 0;
	int Resistance1 = 0;
	*temp = tempdata;

	if (chip->ntc_name == NULL) {
		pr_err("ntc_name is NULL\n\r");
		return -EINVAL;
	}

	adc_value = hisi_adc_get_value(chip->chanel);
	if (adc_value <= 0) {
		pr_err("AP get ADC value is fail,adc_value[%d]!\n\r", adc_value);
		adc_value = ADC_RTMP_DEFAULT_VALUE;/*if read error, return default value*/
	}

	if (strcmp(chip->ntc_name, "hi3630_volt_to_temp_general1") == 0) {
		Resistance1 = (100 * 1000  * adc_value) / (25 * multiple - adc_value);
		pr_debug("+++++Resistance1=%d+++++\n\r", Resistance1);
		tempdata = get_ntc_temperature(Resistance1, chip->chanel, (int **)hi3630_volt_to_temp_general1, ncp_general1_flag);
	}
	 else if (strcmp(chip->ntc_name, "austin_hkadc_adc_temp_table") == 0) {
		tempdata = get_ntc_temperature(adc_value, chip->chanel, (int **)austin_hkadc_volt_temp_table, austin_adc2temp_flag);
	}
	 else if (strcmp(chip->ntc_name, "austin_hkadc_pa_temp_table") == 0) {
		tempdata = get_ntc_temperature(adc_value, chip->chanel, (int **)austin_pa_volt_temp_table, austin_pa_volt2temp_flag);
	}
	else if (strcmp(chip->ntc_name, "austin_hkadc_soc_temp_table") == 0) {
		tempdata = get_ntc_temperature(adc_value, chip->chanel, (int **)austin_soc_volt_temp_table, austin_soc_volt2temp_flag);
	}

	else {
		pr_err("[%s]input ntc name was not found!\n",chip->ntc_name);
	}

	*temp = (unsigned long)tempdata;
	pr_debug("+++++++++++temp=%ld++++++++++\n\r", *temp);
	return 0;
}
