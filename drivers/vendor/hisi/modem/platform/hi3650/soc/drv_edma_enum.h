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

/*��ͷ�ļ�רΪTLdsp��Hifi�ṩ������ģ��Ӧ����drv_edma.h*/
#ifndef __DRV_EDMA_ENUM_H__
#define __DRV_EDMA_ENUM_H__

#define EDMA_CHANNEL_START  0
#define EDMA_CH16_NUM       16
#ifdef HI_EDMA_CH4_REGBASE_ADDR_VIRT
#define EDMA_CH4_NUM        0
#define EDMA_CHANNEL_END    (EDMA_CHANNEL_START+EDMA_CH16_NUM+EDMA_CH4_NUM)
#else
#define EDMA_CHANNEL_END    (EDMA_CHANNEL_START+EDMA_CH16_NUM)
#endif


#define	EDMA_CH16_0	    0
#define	EDMA_CH16_1	    1
#define	EDMA_CH16_2	    2
#define	EDMA_CH16_3	    3
#define	EDMA_CH16_4	    4
#define	EDMA_CH16_5	    5
#define	EDMA_CH16_6	    6
#define	EDMA_CH16_7	    7
#define	EDMA_CH16_8	    8
#define	EDMA_CH16_9	    9
#define	EDMA_CH16_10	10
#define	EDMA_CH16_11	11
#define	EDMA_CH16_12	12
#define	EDMA_CH16_13	13
#define	EDMA_CH16_14	14
#define	EDMA_CH16_15	15
#ifdef HI_EDMA_CH4_REGBASE_ADDR_VIRT
#define	EDMA_CH4_0	    16
#define	EDMA_CH4_1	    17
#define	EDMA_CH4_2	    18
#define	EDMA_CH4_3	    19
#define	EDMA_CH_END	    20
#else
#define	EDMA_CH4_0	    (0x1000)
#define	EDMA_CH4_1	    (0x1000)
#define	EDMA_CH4_2	    (0x1000)
#define	EDMA_CH4_3	    (0x1000)
#define	EDMA_CH_END	    16
#endif

#define	EDMA_CH_LDSP_API_USED_0 EDMA_CH16_0
#define	EDMA_CH_LDSP_API_USED_1 EDMA_CH16_1
#define	EDMA_CH_LDSP_LCS_SDR    EDMA_CH16_2
#define	EDMA_CH_LDSP_CSU_SDR    EDMA_CH16_3
#define	EDMA_CH_LDSP_EMU_SDR    EDMA_CH16_4
#define	EDMA_CH_LDSP_NV_LOADING EDMA_CH16_5
/****arm��ldsp����****�͹��ı��ݻָ�  m2m */
#define	EDMA_CH_LOAD_LDSP_TCM  EDMA_CH_LDSP_API_USED_0
#define	EDMA_CH_LOAD_TDSP_TCM  EDMA_CH_LDSP_API_USED_1
/****gudsp��ldsp����****GU CQI���� �� LDSP LCS */
#define	EDMA_CH_GUDSP_MEMORY_3  EDMA_CH_LDSP_LCS_SDR

/*EDMA_CH_GUDSP_MEMORY_9  ==  BBP_GRIF_PHY��
GUDSPʵ��BBP����������У׼ ����GU BBP DEBUG��������
����ͨ����Ϊ M2M */
#define	EDMA_CH_GUDSP_MEMORY_9  EDMA_CH16_6
#define	EDMA_CH_GUDSP_MEMORY_7  EDMA_CH16_7
/****gudsp��gudsp����****GU DSP������ GU AHB���� */
#define	EDMA_CH_GUDSP_MEMORY_8  EDMA_CH_GUDSP_MEMORY_7


#define	EDMA_CH_GUDSP_MEMORY_1  EDMA_CH16_8
#define	EDMA_CH_GUDSP_MEMORY_2  EDMA_CH16_9
#define	EDMA_CH_GUDSP_MEMORY_4  EDMA_CH16_10
#define	EDMA_CH_GUDSP_MEMORY_6  EDMA_CH16_11

#define	EDMA_CH_GUDSP_MEMORY_10  EDMA_CH16_15

/* SIM��0 ���պͷ��� / SIM��1 ���պͷ��� */
#define	EDMA_CH_DRV_SIM_0       EDMA_CH16_12
#define	EDMA_CH_DRV_SIM_1       EDMA_CH16_13
/* ��������axi_monitor�Ĳɼ����� */
#define	EDMA_CH_DRV_AXIMON      EDMA_CH16_14

/*===================================================*/
/* HIFI SIO �շ� */
#define	EDMA_CH_HIFI_SIO_TX     (-1)/*EDMA_CH16_8*/
#define	EDMA_CH_HIFI_SIO_RX     (-1)/*EDMA_CH16_9*/
/*���ٴ��ڷ���/����ʹ��	����������������*/
#define	EDMA_CH_HSUART_TX       (-1)/*EDMA_CH16_12*/
#define	EDMA_CH_HSUART_RX       (-1)/*EDMA_CH16_13*/
/* SPI1���ͣ�ˢLCD�� */
#define	EDMA_CH_DRV_LCD         (-1)/*EDMA_CH16_14*/

/* austin X ģ ʹ�� TL DSP��ͨ��
	memmap ����ַ 0xE0204000 */
	/* ����ͨ��2 ��TL��GU���õ� */
#define EDMA_CH_LOAD_CDSP_TCM	EDMA_CH16_0
#define EDMA_CH_CPHY_1			EDMA_CH_LOAD_CDSP_TCM
#define EDMA_CH_CPHY_2			EDMA_CH16_1
#define EDMA_CH_CPHY_3			EDMA_CH16_3
#define EDMA_CH_CPHY_4			EDMA_CH16_4
#define EDMA_CH_CPHY_5			EDMA_CH16_5


#endif

