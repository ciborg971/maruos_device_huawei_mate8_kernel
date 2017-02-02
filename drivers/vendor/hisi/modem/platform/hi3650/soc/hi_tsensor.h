/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __HI_TSENSOR_H__
#define __HI_TSENSOR_H__

/*
 * Project: hi
 * Module : tsensor
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    tsensor �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_TEMP_EN_OFFSET                                 (0x0) /* Tsensor�¶ȼ��ʹ�ܼĴ��� */
#define    HI_TEMP_DIS_TIME_OFFSET                           (0x4) /* Tsensor�¶ȼ��ȥʹ�ܵȴ�ʱ��Ĵ��� */
#define    HI_TRIM0_OFFSET                                   (0x8) /* Tsensor�¶�У׼�Ĵ���1 */
#define    HI_TRIM1_OFFSET                                   (0xC) /* Tsensor�¶�У׼�Ĵ���2 */
#define    HI_TEMP_TH_OFFSET                                 (0x10) /* Tsensor�¶ȱ������޼Ĵ��� */
#define    HI_TEMP_B_TH_OFFSET                               (0x14) /* Tsensor�¶Ȼ��ͼĴ��� */
#define    HI_TEMP_CONFIG_OFFSET                             (0x18) /* Tsensorģʽ���üĴ��� */
#define    HI_TEMP_RAWINT_OFFSET                             (0x1C) /* Tsensorԭʼ�жϼĴ��� */
#define    HI_TEMP_MSKINT_OFFSET                             (0x20) /* Tsensor�����жϼĴ��� */
#define    HI_TEMP_STATINT_OFFSET                            (0x24) /* Tsensor�ж�״̬�Ĵ��� */
#define    HI_TEMP_OFFSET                                    (0x28) /* Tsensor�¶ȼ�����Ĵ��� */
#define    HI_TEMP_TRIM_MODE_OFFSET                          (0x2C) /* Tsensor�¶�У��ģʽ */

/********************************************************************************/
/*    tsensor �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    temp_en                    : 1; /* [0..0] Tsensor�¶Ȳ���ʹ�ܼĴ�����0����ʹ��1��ʹ�� */
        unsigned int    reserved                   : 31; /* [31..1] ����λ */
    } bits;
    unsigned int    u32;
}HI_TEMP_EN_T;    /* Tsensor�¶ȼ��ʹ�ܼĴ��� */

typedef union
{
    struct
    {
        unsigned int    temp_dis_time              : 8; /* [7..0] �ȴ�ʱ��ΪN��1Mhz���ڡ�N��ʾ������ֵ���Խ�����Ҫ������5us������Ĭ��ֵ��Ϊ6�� */
        unsigned int    reserved                   : 24; /* [31..8] ����λ */
    } bits;
    unsigned int    u32;
}HI_TEMP_DIS_TIME_T;    /* Tsensor�¶ȼ��ȥʹ�ܵȴ�ʱ��Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    local_sensor_trim          : 8; /* [7..0] ATE remote sensor4�¶�У׼�����Ϣ�����λ��ʾ���ţ�1�������¶ȼ�ȥУ׼���0�������¶ȼ���У׼��� */
        unsigned int    remote_sensor1_trim        : 8; /* [15..8] ATE remote sensor5�¶�У׼�����Ϣ�����λ��ʾ���ţ�1�������¶ȼ�ȥУ׼���0�������¶ȼ���У׼��� */
        unsigned int    remote_sensor2_trim        : 8; /* [23..16] ATE remote sensor6�¶�У׼�����Ϣ�����λ��ʾ���ţ�1�������¶ȼ�ȥУ׼���0�������¶ȼ���У׼��� */
        unsigned int    remote_sensor3_trim        : 8; /* [31..24] ATE remote sensor7�¶�У׼�����Ϣ�����λ��ʾ���ţ�1�������¶ȼ�ȥУ׼���0�������¶ȼ���У׼��� */
    } bits;
    unsigned int    u32;
}HI_TRIM0_T;    /* Tsensor�¶�У׼�Ĵ���1 */

typedef union
{
    struct
    {
        unsigned int    remote_sensor4_trim        : 8; /* [7..0] ATE local sensor�¶�У׼�����Ϣ�����λ��ʾ���ţ�1�������¶ȼ�ȥУ׼���0�������¶ȼ���У׼��� */
        unsigned int    remote_sensor5_trim        : 8; /* [15..8] ATE remote sensor1�¶�У׼�����Ϣ�����λ��ʾ���ţ�1�������¶ȼ�ȥУ׼���0�������¶ȼ���У׼��� */
        unsigned int    remote_sensor6_trim        : 8; /* [23..16] ATE remote sensor2�¶�У׼�����Ϣ�����λ��ʾ���ţ�1�������¶ȼ�ȥУ׼���0�������¶ȼ���У׼��� */
        unsigned int    remote_sensor7_trim        : 8; /* [31..24] ATE remote sensor3�¶�У׼�����Ϣ�����λ��ʾ���ţ�1�������¶ȼ�ȥУ׼���0�������¶ȼ���У׼��� */
    } bits;
    unsigned int    u32;
}HI_TRIM1_T;    /* Tsensor�¶�У׼�Ĵ���2 */

typedef union
{
    struct
    {
        unsigned int    temp_0th                   : 8; /* [7..0] Tsensor�¶ȱ�������0 */
        unsigned int    temp_1th                   : 8; /* [15..8] Tsensor�¶ȱ�������1 */
        unsigned int    temp_2th                   : 8; /* [23..16] Tsensor�¶ȱ�������2 */
        unsigned int    temp_3th                   : 8; /* [31..24] Tsensor�¶ȱ�������3 */
    } bits;
    unsigned int    u32;
}HI_TEMP_TH_T;    /* Tsensor�¶ȱ������޼Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    temp_b_th                  : 5; /* [4..0] Tsensor�¶Ȼ������� */
        unsigned int    reserved                   : 27; /* [31..5] ����λ */
    } bits;
    unsigned int    u32;
}HI_TEMP_B_TH_T;    /* Tsensor�¶Ȼ��ͼĴ��� */

typedef union
{
    struct
    {
        unsigned int    ct_sel                     : 2; /* [1..0] ��������1M��׼ʱ�������Tsensor HKADCת��ʱ��ѡ��00-----0.768ms��01-----6.144ms��10-----49.152ms��11-----393.216ms�� */
        unsigned int    test                       : 3; /* [4..2] Tsensorͨ��ģʽѡ��000����ѡ��LOCAL SENSOR���¶�ֵ001����ѡ��REMOTE SENSOR1���¶�ֵ010����ѡ��REMOTE SENSOR2���¶�ֵ011����ѡ��REMOTE SENSOR3���¶�ֵ100����ѡ��REMOTE SENSOR4���¶�ֵ101����ѡ��REMOTE SENSOR5���¶�ֵ110����ѡ��REMOTE SENSOR6���¶�ֵ111����ѡ��REMOTE SENSOR7���¶�ֵ */
        unsigned int    sample_mode                : 2; /* [6..5] Tsensorͬһͨ���¶Ȳ���ģʽѡ��00������β������һ��ֵ01������β���ȡ���ֵ10������β���ȡ��ֵ11������β���ȡ��Сֵ */
        unsigned int    sample_num                 : 3; /* [9..7] Tsensorͬһͨ����������ѡ��ֻ֧��2��N�η���1��2��4��8~128 */
        unsigned int    reserved                   : 22; /* [31..10] ����λ */
    } bits;
    unsigned int    u32;
}HI_TEMP_CONFIG_T;    /* Tsensorģʽ���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    temp_rawint                : 1; /* [0..0] Tsensorԭʼ�жϣ�д1�壺1�����ж�0�����ж� */
        unsigned int    reserved                   : 31; /* [31..1] ����λ */
    } bits;
    unsigned int    u32;
}HI_TEMP_RAWINT_T;    /* Tsensorԭʼ�жϼĴ��� */

typedef union
{
    struct
    {
        unsigned int    temp_maskint               : 1; /* [0..0] Tsensor�����ж�ʹ�ܣ�1�������ж�0�������� */
        unsigned int    reserved                   : 31; /* [31..1] ����λ */
    } bits;
    unsigned int    u32;
}HI_TEMP_MSKINT_T;    /* Tsensor�����жϼĴ��� */

typedef union
{
    struct
    {
        unsigned int    temp_statint               : 1; /* [0..0] Tsensor�ж�״̬��1�����ж�0�����ж� */
        unsigned int    reserved                   : 31; /* [31..1] ����λ */
    } bits;
    unsigned int    u32;
}HI_TEMP_STATINT_T;    /* Tsensor�ж�״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    temp                       : 8;
        unsigned int    reserved                   : 24; /* [31..8] �¶ȼ�����Ĵ��� */
    } bits;
    unsigned int    u32;
}HI_TEMP_T;    /* Tsensor�¶ȼ�����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    temp_trim_mode             : 1; /* [0..0] Tsensor�¶ȼ���ģʽ��0�����У��1��������ֱ���ö������¶���У�� */
        unsigned int    reserved                   : 31; /* [31..1] ����λ */
    } bits;
    unsigned int    u32;
}HI_TEMP_TRIM_MODE_T;    /* Tsensor�¶�У��ģʽ */


/********************************************************************************/
/*    tsensor ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_temp_en_temp_en,temp_en,HI_TEMP_EN_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_EN_OFFSET)
HI_SET_GET(hi_temp_en_reserved,reserved,HI_TEMP_EN_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_EN_OFFSET)
HI_SET_GET(hi_temp_dis_time_temp_dis_time,temp_dis_time,HI_TEMP_DIS_TIME_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_DIS_TIME_OFFSET)
HI_SET_GET(hi_temp_dis_time_reserved,reserved,HI_TEMP_DIS_TIME_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_DIS_TIME_OFFSET)
HI_SET_GET(hi_trim0_local_sensor_trim,local_sensor_trim,HI_TRIM0_T,HI_TSENSOR_BASE_ADDR, HI_TRIM0_OFFSET)
HI_SET_GET(hi_trim0_remote_sensor1_trim,remote_sensor1_trim,HI_TRIM0_T,HI_TSENSOR_BASE_ADDR, HI_TRIM0_OFFSET)
HI_SET_GET(hi_trim0_remote_sensor2_trim,remote_sensor2_trim,HI_TRIM0_T,HI_TSENSOR_BASE_ADDR, HI_TRIM0_OFFSET)
HI_SET_GET(hi_trim0_remote_sensor3_trim,remote_sensor3_trim,HI_TRIM0_T,HI_TSENSOR_BASE_ADDR, HI_TRIM0_OFFSET)
HI_SET_GET(hi_trim1_remote_sensor4_trim,remote_sensor4_trim,HI_TRIM1_T,HI_TSENSOR_BASE_ADDR, HI_TRIM1_OFFSET)
HI_SET_GET(hi_trim1_remote_sensor5_trim,remote_sensor5_trim,HI_TRIM1_T,HI_TSENSOR_BASE_ADDR, HI_TRIM1_OFFSET)
HI_SET_GET(hi_trim1_remote_sensor6_trim,remote_sensor6_trim,HI_TRIM1_T,HI_TSENSOR_BASE_ADDR, HI_TRIM1_OFFSET)
HI_SET_GET(hi_trim1_remote_sensor7_trim,remote_sensor7_trim,HI_TRIM1_T,HI_TSENSOR_BASE_ADDR, HI_TRIM1_OFFSET)
HI_SET_GET(hi_temp_th_temp_0th,temp_0th,HI_TEMP_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TH_OFFSET)
HI_SET_GET(hi_temp_th_temp_1th,temp_1th,HI_TEMP_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TH_OFFSET)
HI_SET_GET(hi_temp_th_temp_2th,temp_2th,HI_TEMP_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TH_OFFSET)
HI_SET_GET(hi_temp_th_temp_3th,temp_3th,HI_TEMP_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TH_OFFSET)
HI_SET_GET(hi_temp_b_th_temp_b_th,temp_b_th,HI_TEMP_B_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_B_TH_OFFSET)
HI_SET_GET(hi_temp_b_th_reserved,reserved,HI_TEMP_B_TH_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_B_TH_OFFSET)
HI_SET_GET(hi_temp_config_ct_sel,ct_sel,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_config_test,test,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_config_sample_mode,sample_mode,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_config_sample_num,sample_num,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_config_reserved,reserved,HI_TEMP_CONFIG_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_CONFIG_OFFSET)
HI_SET_GET(hi_temp_rawint_temp_rawint,temp_rawint,HI_TEMP_RAWINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_RAWINT_OFFSET)
HI_SET_GET(hi_temp_rawint_reserved,reserved,HI_TEMP_RAWINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_RAWINT_OFFSET)
HI_SET_GET(hi_temp_mskint_temp_maskint,temp_maskint,HI_TEMP_MSKINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_MSKINT_OFFSET)
HI_SET_GET(hi_temp_mskint_reserved,reserved,HI_TEMP_MSKINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_MSKINT_OFFSET)
HI_SET_GET(hi_temp_statint_temp_statint,temp_statint,HI_TEMP_STATINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_STATINT_OFFSET)
HI_SET_GET(hi_temp_statint_reserved,reserved,HI_TEMP_STATINT_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_STATINT_OFFSET)
HI_SET_GET(hi_temp_temp,temp,HI_TEMP_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_OFFSET)
HI_SET_GET(hi_temp_reserved,reserved,HI_TEMP_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_OFFSET)
HI_SET_GET(hi_temp_trim_mode_temp_trim_mode,temp_trim_mode,HI_TEMP_TRIM_MODE_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TRIM_MODE_OFFSET)
HI_SET_GET(hi_temp_trim_mode_reserved,reserved,HI_TEMP_TRIM_MODE_T,HI_TSENSOR_BASE_ADDR, HI_TEMP_TRIM_MODE_OFFSET)

#endif // __HI_TSENSOR_H__

