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


#ifndef __DRV_TELE_MNTN_H__
#define __DRV_TELE_MNTN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/


/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*

˵��:

extern int DRV_TELE_MNTN_WRITE_LOG(
            TELE_MNTN_TYPE_ID type_id,
            unsigned int len,
            void *data);

def type_id ��  ���len���� data�������� �Ķ�Ӧ��ϵ:

    TELE_MNTN_DEF_STR ��Ӧ��data�������� �� ���len����:
            U8 tmp[64]
            len = 64 Bytes

    TELE_MNTN_DEF_U8 ��Ӧ��data�������� �� ���len����:
            struct
            {
                U8 tmp0;
                U8 tmp1;
                U8 tmp2;
                U8 tmp3;
                U8 tmp4;
                U8 tmp5;
                U8 tmp6;
                U8 tmp7;
            }
            len = 8 Bytes

    TELE_MNTN_DEF_U16 ��Ӧ��data�������� �� ���len����:
            struct
            {
                U16 tmp0;
                U16 tmp1;
                U16 tmp2;
                U16 tmp3;
                U16 tmp4;
                U16 tmp5;
                U16 tmp6;
                U16 tmp7;
            }
            len = 16 Bytes

    TELE_MNTN_DEF_U32 ��Ӧ��data�������� �� ���len����:
            struct
            {
                U32 tmp0;
                U32 tmp1;
                U32 tmp2;
                U32 tmp3;
                U32 tmp4;
                U32 tmp5;
                U32 tmp6;
                U32 tmp7;
            }
            len = 32 Bytes

    TELE_MNTN_DEF_U64 ��Ӧ��data�������� �� ���len����:
            struct
            {
                U64 tmp0;
                U64 tmp1;
                U64 tmp2;
                U64 tmp3;
            }
            len = 32 Bytes

*/
typedef enum
{
    TELE_MNTN_TYPE_RESERVED = -1,
    /*������;������*/
    TELE_MNTN_NVME_WAKEUP_ACPU = 0,
    TELE_MNTN_NVME_LOGCAT,

    /*Ĭ��type_id ��Ӧ�̶������ݽ������ͺ�Ĭ�ϵ�������󳤶ȣ�
    ������Ĭ�ϵ����ݽ������ͽ�������ģ����ظ�ʹ��*/
    TELE_MNTN_DEF_STR = 5,    /*��˵��*/
    TELE_MNTN_DEF_U8,         /*��˵��*/
    TELE_MNTN_DEF_U16,        /*��˵��*/
    TELE_MNTN_DEF_U32,        /*��˵��*/
    TELE_MNTN_DEF_U64,        /*��˵��*/

    /*��ģ���Զ���type_id ��Ӧ�����ݽ������ͺ����ݳ����ɸ�ģ���Լ�����Ľṹ�������
    ���û�нṹ�嶨�壬������������ʽ����*/
    TELE_MNTN_SLEEPWAKE_CCPU = 15,
    TELE_MNTN_NOTSLEEPREASON_CCPU,
    TELE_MNTN_SLEEPWAKE_MCU,
    TELE_MNTN_NOTSLEEPREASON_MCU,
    TELE_MNTN_PUPD_CCPU,
    TELE_MNTN_WFIFAIL_CCPU,  /*20*/
    TELE_MNTN_PUPD_ACPU,
    TELE_MNTN_WFIFAIL_ACPU,
    TELE_MNTN_PUPD_HIFI,
    TELE_MNTN_WFIFAIL_HIFI,
    TELE_MNTN_CPUIDLE,  /*25*/
    TELE_MNTN_VOTE_CCPU,
    TELE_MNTN_VOTE_MCU,
    TELE_MNTN_ICC_WAKE_ACPU,
    TELE_MNTN_ICC_WAKE_CCPU,
    TELE_MNTN_IPC_MCU,  /*30*/
    TELE_MNTN_DFS_DDR,
    TELE_MNTN_PLI_DDR,
    TELE_MNTN_MAXFREQ_REQ_DDR,
    TELE_MNTN_MINFREQ_REQ_DDR,
    TELE_MNTN_QOS_DDR_MCU,  /*35*/
    TELE_MNTN_QOS_DDR_CCPU,
    TELE_MNTN_QOS_DDR_ACPU,
    TELE_MNTN_DFS_CCPU,
    TELE_MNTN_PLI_CCPU,
    TELE_MNTN_QOS_CCPU,  /*40*/
    TELE_MNTN_DFS_ACPU,
    TELE_MNTN_DRX,
    TELE_MNTN_PLI_ACPU,
    TELE_MNTN_SR_ACPU,

    TELE_MNTN_OSA = 50,

    TELE_MNTN_REG_DUMP = 63,
    TELE_MNTN_TYPE_BUTT
}TELE_MNTN_TYPE_ID;
/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of drv_tele_mntn.h */
