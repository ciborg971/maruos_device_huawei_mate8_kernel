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

#ifndef __HI_MIPI_H__
#define __HI_MIPI_H__

/*
 * Project: hi
 * Module : mipi
 */

#ifndef HI_SET_GET_MIPI
#define HI_SET_GET_MIPI(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    mipi �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    MIPI_MIPI0_RD_DATA_LOW_SOFT_OFFSET            (0xD8) /* �Ĵ��� */
#define    MIPI_MIPI0_RD_DATA_HIGH_SOFT_OFFSET           (0xDC) /* �Ĵ��� */
#define    MIPI_RD_END_FLAG_MIPI0_SOFT_OFFSET            (0xE0) /* �Ĵ��� */
#define    MIPI_MIPI0_GRANT_DSP_OFFSET                   (0xE4) /* �Ĵ��� */
#define    MIPI_DSP_MIPI0_WDATA_LOW_OFFSET               (0xE8) /* �Ĵ��� */
#define    MIPI_DSP_MIPI0_WDATA_HIGH_OFFSET              (0xEC) /* �Ĵ��� */
#define    MIPI_DSP_MIPI0_EN_IMI_OFFSET                  (0xF0) /* �Ĵ��� */
#define    MIPI_DSP_MIPI0_CFG_IND_IMI_OFFSET             (0xF4) /* �Ĵ��� */
#define    MIPI_DSP_MIPI0_RD_CLR_OFFSET                  (0xF8) /* �Ĵ��� */

/********************************************************************************/
/*    mipi �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    mipi0_rd_data_low_soft     : 32; /* [31..0] �����ֱ�ӿ���MIPI0 master,������xbbp���ͻض�ָ��ʱ,�ض�ָ���ŵ�32bit. */
    } bits;
    unsigned int    u32;
}MIPI_MIPI0_RD_DATA_LOW_SOFT_T;    /* �Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    mipi0_rd_data_high_soft    : 32; /* [31..0] �����ֱ�ӿ���MIPI0 master,������xbbp���ͻض�ָ��ʱ,�ض�ָ���Ÿ�32bit. */
    } bits;
    unsigned int    u32;
}MIPI_MIPI0_RD_DATA_HIGH_SOFT_T;    /* �Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    rd_end_flag_mipi0_soft     : 1; /* [0..0] �����ֱ�ӿ���MIPI0 master,������xbbp���ͻض�ָ��ʱ,�ض�������Чָʾ */
        unsigned int    Reserved                   : 31; /* [31..1]  */
    } bits;
    unsigned int    u32;
}MIPI_RD_END_FLAG_MIPI0_SOFT_T;    /* �Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    mipi0_grant_dsp            : 1; /* [0..0] �����ֱ�ӿ���MIPI0 master1:������Է���CFG_IND����mipi00:����ȴ�mipi0��Ȩʹ�� */
        unsigned int    Reserved                   : 31; /* [31..1]  */
    } bits;
    unsigned int    u32;
}MIPI_MIPI0_GRANT_DSP_T;    /* �Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    dsp_mipi0_wdata_low        : 32; /* [31..0] �����ֱ�ӿ���MIPI0 master,������xbbp����дָ��ʱ,дָ���32bit */
    } bits;
    unsigned int    u32;
}MIPI_DSP_MIPI0_WDATA_LOW_T;    /* �Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    dsp_mipi0_wdata_high       : 32; /* [31..0] �����ֱ�ӿ���MIPI0 master,������xbbp����дָ��ʱ,дָ���32bit */
    } bits;
    unsigned int    u32;
}MIPI_DSP_MIPI0_WDATA_HIGH_T;    /* �Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    dsp_mipi0_en_imi           : 1; /* [0..0] �����ֱ�ӿ���MIPI0 master,���������ߴ�ָʾ,����xbbp��MIPI0�Ŀ��� */
        unsigned int    Reserved                   : 31; /* [31..1]  */
    } bits;
    unsigned int    u32;
}MIPI_DSP_MIPI0_EN_IMI_T;    /* �Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    dsp_mipi0_cfg_ind_imi      : 1; /* [0..0] �����ֱ�ӿ���MIPI0 master,���ߴ�dsp_mipi0_en��,��������������� */
        unsigned int    Reserved                   : 31; /* [31..1]  */
    } bits;
    unsigned int    u32;
}MIPI_DSP_MIPI0_CFG_IND_IMI_T;    /* �Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    dsp_mipi0_rd_clr           : 1; /* [0..0] �����ֱ�ӿ���MIPI0 master,ȡ�߻ض����ݺ�,���־λ���� */
        unsigned int    Reserved                   : 31; /* [31..1]  */
    } bits;
    unsigned int    u32;
}MIPI_DSP_MIPI0_RD_CLR_T;    /* �Ĵ��� */


/********************************************************************************/
/*    mipi ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET_MIPI(mipi_mipi0_rd_data_low_soft_mipi0_rd_data_low_soft,mipi0_rd_data_low_soft,MIPI_MIPI0_RD_DATA_LOW_SOFT_T,MIPI_BASE_ADDR, MIPI_MIPI0_RD_DATA_LOW_SOFT_OFFSET)
HI_SET_GET_MIPI(mipi_mipi0_rd_data_high_soft_mipi0_rd_data_high_soft,mipi0_rd_data_high_soft,MIPI_MIPI0_RD_DATA_HIGH_SOFT_T,MIPI_BASE_ADDR, MIPI_MIPI0_RD_DATA_HIGH_SOFT_OFFSET)
HI_SET_GET_MIPI(mipi_rd_end_flag_mipi0_soft_rd_end_flag_mipi0_soft,rd_end_flag_mipi0_soft,MIPI_RD_END_FLAG_MIPI0_SOFT_T,MIPI_BASE_ADDR, MIPI_RD_END_FLAG_MIPI0_SOFT_OFFSET)
HI_SET_GET_MIPI(mipi_rd_end_flag_mipi0_soft_reserved,Reserved,MIPI_RD_END_FLAG_MIPI0_SOFT_T,MIPI_BASE_ADDR, MIPI_RD_END_FLAG_MIPI0_SOFT_OFFSET)
HI_SET_GET_MIPI(mipi_mipi0_grant_dsp_mipi0_grant_dsp,mipi0_grant_dsp,MIPI_MIPI0_GRANT_DSP_T,MIPI_BASE_ADDR, MIPI_MIPI0_GRANT_DSP_OFFSET)
HI_SET_GET_MIPI(mipi_mipi0_grant_dsp_reserved,Reserved,MIPI_MIPI0_GRANT_DSP_T,MIPI_BASE_ADDR, MIPI_MIPI0_GRANT_DSP_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_wdata_low_dsp_mipi0_wdata_low,dsp_mipi0_wdata_low,MIPI_DSP_MIPI0_WDATA_LOW_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_WDATA_LOW_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_wdata_high_dsp_mipi0_wdata_high,dsp_mipi0_wdata_high,MIPI_DSP_MIPI0_WDATA_HIGH_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_WDATA_HIGH_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_en_imi_dsp_mipi0_en_imi,dsp_mipi0_en_imi,MIPI_DSP_MIPI0_EN_IMI_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_EN_IMI_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_en_imi_reserved,Reserved,MIPI_DSP_MIPI0_EN_IMI_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_EN_IMI_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_cfg_ind_imi_dsp_mipi0_cfg_ind_imi,dsp_mipi0_cfg_ind_imi,MIPI_DSP_MIPI0_CFG_IND_IMI_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_CFG_IND_IMI_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_cfg_ind_imi_reserved,Reserved,MIPI_DSP_MIPI0_CFG_IND_IMI_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_CFG_IND_IMI_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_rd_clr_dsp_mipi0_rd_clr,dsp_mipi0_rd_clr,MIPI_DSP_MIPI0_RD_CLR_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_RD_CLR_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_rd_clr_reserved,Reserved,MIPI_DSP_MIPI0_RD_CLR_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_RD_CLR_OFFSET)

#endif // __HI_MIPI_H__

