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
 
 #ifdef  __cplusplus
 #if  __cplusplus
    extern "C" {
 #endif
#endif

/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "product_config.h"
#if( FEATURE_ON == FEATURE_CSD )

#include "vos.h"
#include "Dicc.h"
#if (VOS_WIN32 != VOS_OS_VER)
    #if (OSA_CPU_CCPU == VOS_OSA_CPU)
    #elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    #include <linux/spinlock.h>
    #endif
#else
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define     THIS_FILE_ID PS_FILE_ID_DICC_C
/*lint +e(767)*/

#if (VOS_WIN32 != VOS_OS_VER)
    #if (OSA_CPU_CCPU == VOS_OSA_CPU)
    #define    DICC_LOCAL_CPU_ID   (DICC_CPU_ID_CCPU)
    #define    LOCAL_UEPS_PID_DICC (UEPS_PID_DICC_C)
    #elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    #define    DICC_LOCAL_CPU_ID (DICC_CPU_ID_ACPU)
    #define    LOCAL_UEPS_PID_DICC (UEPS_PID_DICC_A)
    #endif
#else
    #define     LOCAL_UEPS_PID_DICC (UEPS_PID_DICC_A)    /* WIN32�ϰ���A��������PID, ���ڿ���ʵת����û��ִ�� */
#endif

#ifdef __UT_CENTER__
    #define DICC_TTF_PHY_TO_VIRT(var) (g_aucDiccBuff)
    #define DICC_DRV_PHY_TO_VIRT(var) (&g_ulMagicNum)
#else
    #define  DICC_TTF_PHY_TO_VIRT(var)  (TTF_PHY_TO_VIRT(var))
    #define  DICC_DRV_PHY_TO_VIRT(var)  (DRV_AXI_PHY_TO_VIRT(var))
#endif

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/


/******************************************************************************
   3 ˽�ж���
******************************************************************************/
/* DICCģ���ڲ���DFx���ܿ���, 1 - ��, 0 - �ر� */
#define DICC_DFX_SWITCH    (1)

/* ����ʹ�õĺ� */
#define DICC_BBIT          (0)
#define DICC_RELEASE       (1)

/* ���Դ�ӡ */
#define DEBUG_PRINT(...)\
        {\
            if ( PS_TRUE == g_ulDiccDebugPrint )\
            {\
                vos_printf(__VA_ARGS__);\
            }\
        }

#define DICC_LOG(Level, String)\
    {\
        (TTF_LOG(LOCAL_UEPS_PID_DICC, DIAG_MODE_COMM, (Level), (String)));\
        /*lint --e{506, 774}*/\
        if (DICC_BBIT == g_ucDiccStability)\
        {\
            if (((Level) == PS_PRINT_WARNING) || ((Level) == PS_PRINT_ERROR))\
            {\
                Print((String));\
            }\
        }\
    }
#define DICC_LOG1(Level, String, Para1)\
    {\
        (TTF_LOG1(LOCAL_UEPS_PID_DICC, DIAG_MODE_COMM, (Level), (String), (Para1)));\
        /*lint --e{506, 774}*/\
        if (DICC_BBIT == g_ucDiccStability)\
        {\
            if (((Level) == PS_PRINT_WARNING) || ((Level) == PS_PRINT_ERROR))\
            {\
                Print1((String), (Para1));\
            }\
        }\
    }
#define DICC_LOG2(Level, String, Para1, Para2)\
    {\
        (TTF_LOG2(LOCAL_UEPS_PID_DICC, DIAG_MODE_COMM, (Level), (String), (Para1), (Para2)));\
        /*lint --e{506, 774}*/\
        if (DICC_BBIT == g_ucDiccStability)\
        {\
            if (((Level) == PS_PRINT_WARNING) || ((Level) == PS_PRINT_ERROR))\
            {\
                Print2((String), (Para1), (Para2));\
            }\
        }\
    }
#define DICC_LOG3(Level, String, Para1, Para2, Para3)\
    {\
        (TTF_LOG3(LOCAL_UEPS_PID_DICC, DIAG_MODE_COMM, (Level), (String), (Para1), (Para2), (Para3)));\
        /*lint --e{506, 774}*/\
        if (DICC_BBIT == g_ucDiccStability)\
        {\
            if (((Level) == PS_PRINT_WARNING) || ((Level) == PS_PRINT_ERROR))\
            {\
                Print3((String), (Para1), (Para2), (Para3));\
            }\
        }\
    }
#define DICC_LOG4(Level, String, Para1, Para2, Para3, Para4)\
    {\
        (TTF_LOG4(LOCAL_UEPS_PID_DICC, DIAG_MODE_COMM, (Level), (String), (Para1), (Para2), (Para3), (Para4)));\
        /*lint --e{506, 774}*/\
        if (DICC_BBIT == g_ucDiccStability)\
        {\
            if (((Level) == PS_PRINT_WARNING) || ((Level) == PS_PRINT_ERROR))\
            {\
                Print4((String), (Para1), (Para2), (Para3), (Para4));\
            }\
        }\
    }


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
/*
DICCͨ����¼��
���þ�̬���÷�ʽ, �ȹ����, ���ܷ�ֹͨ������ʹ��
 */
volatile DICC_CHAN_ROLE_STRU g_astChanRole[] =
{
    {
        /* enLocalCpuId */
        DICC_CPU_ID_CCPU,

        /* aenSender */
        {
            DICC_CHAN_ID_2,           /* for service 0 */
            DICC_CHAN_ID_1            /* for service 1 */
        },

        /* aenRecver */
        {
            DICC_CHAN_ID_0,           /* for service 0 */
            DICC_CHAN_ID_3            /* for service 1 */
        },

        /* aenRole */
        {
            DICC_CHAN_ROLE_RECVER,    /* for channel 0 */
            DICC_CHAN_ROLE_SENDER,    /* for channel 1 */
            DICC_CHAN_ROLE_SENDER,    /* for channel 2 */
            DICC_CHAN_ROLE_RECVER     /* for channel 3 */
        },

        /* aucReserve */
        {
            0x00,
            0x00
        },

        /* ucSemCreated */
        0,

        /* ulDiccLocalMutexSem */
        VOS_NULL,

        /* pastDICCMgmt */
        VOS_NULL_PTR,

        /* PID */
        UEPS_PID_DICC_C
    },
    {
        /* enLocalCpuId */
        DICC_CPU_ID_ACPU,

        /* aenSender */
        {
            DICC_CHAN_ID_0,           /* for service 0 */
            DICC_CHAN_ID_3            /* for service 1 */
        },

        /* aenRecver */
        {
            DICC_CHAN_ID_2,           /* for service 0 */
            DICC_CHAN_ID_1            /* for service 1 */
        },

        /* aenRole */
        {
            DICC_CHAN_ROLE_SENDER,    /* for channel 0 */
            DICC_CHAN_ROLE_RECVER,    /* for channel 1 */
            DICC_CHAN_ROLE_RECVER,    /* for channel 2 */
            DICC_CHAN_ROLE_SENDER     /* for channel 3 */
        },

        /* aucReserve */
        {
            0x00,
            0x00
        },

        /* ucSemCreated */
        0,

        /* ulDiccLocalMutexSem */
        VOS_NULL,

        /* pastDICCMgmt */
        VOS_NULL_PTR,

        /* PID */
        UEPS_PID_DICC_A
    }
};

/* ���ڴ�ӡ����, ����ΪPS_TRUEʱ, ���򴮿ڴ�ӡ */
VOS_UINT32 g_ulDiccDebugPrint                            = PS_FALSE;
VOS_UINT8  g_ucDiccPrintDataMaxLen                       = DICC_DEBUG_PRINT_MAX_LEN;
DICC_TRACE_INFO_STRU g_stDiccTraceInfo[DICC_CPU_ID_BUTT] = {{0,0,{0,0},0,0,0},{0,0,{0,0},0,0,0}};
VOS_UINT8  g_ucDiccStability                             = DICC_BBIT;

/* DICC��ʼ������������ */
VOS_UINT32      g_ulDiccMultiCoreFlag                    = DICC_MUTEX_SEM_NOT_CREATE;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
spinlock_t      g_stDiccSpinLock;
#endif

#ifdef __UT_CENTER__
VOS_UINT8 g_aucDiccBuff[DICC_QUEUE_MEM_SIZE] = {0};
VOS_UINT32 g_ulMagicNum;
#endif


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/*lint -save -e958 */

VOS_VOID DICC_PrintDebugData(VOS_VOID *pData, VOS_UINT32 ulDataLen)
{
    VOS_UINT8       *ptr;
    VOS_UINT32       ulLoop;
    VOS_UINT32       ulLoopLen;

    ptr       = (VOS_UINT8 *)pData;
    if (VOS_NULL_PTR == ptr)
    {
        return;
    }

    if (PS_TRUE != g_ulDiccDebugPrint)
    {
        return;
    }

    ulLoopLen = ulDataLen;
    if (ulDataLen > g_ucDiccPrintDataMaxLen)
    {
        vos_printf("Debug_DataPrint Data too long = %d ", ulDataLen );
        ulLoopLen = g_ucDiccPrintDataMaxLen;
    }

    for (ulLoop = 0; ulLoop < ulLoopLen; ++ulLoop)
    {
        vos_printf("0x%x ", ptr[ulLoop]);
    }

    vos_printf("\n");
}


VOS_VOID DICC_SetDebugPrintState(VOS_UINT32 ulPrintState, VOS_UINT8 ucPrintDataMaxLen)
{
    g_ulDiccDebugPrint      = (PS_TRUE != ulPrintState) ? PS_FALSE : PS_TRUE;
    g_ucDiccPrintDataMaxLen = (DICC_DEBUG_PRINT_MAX_LEN < ucPrintDataMaxLen) ? DICC_DEBUG_PRINT_MAX_LEN : ucPrintDataMaxLen;

    return;
}/* Debug_PrintStateSet */

/*****************************************************************************
 �� �� ��  : DICC_TraceInfo
 ��������  : ���VC��TRACE��¼����, ��¼�³���ִ��·��, ֧���ֶ���ӡ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��17��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID DICC_TraceInfo()
{
    DICC_TRACE_INFO_STRU     *pstDiccTraceInfo;
    DICC_CPU_ID_ENUM_UINT8    enCpuId;

#if (VOS_WIN32 != VOS_OS_VER)
 #if (OSA_CPU_CCPU == VOS_OSA_CPU)
    enCpuId = DICC_CPU_ID_CCPU;
 #elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    enCpuId = DICC_CPU_ID_ACPU;
 #endif
#else
    enCpuId = DICC_CPU_ID_ACPU;
#endif

    pstDiccTraceInfo = &g_stDiccTraceInfo[enCpuId];

    vos_printf("enCpuId=%d\n",  pstDiccTraceInfo->enCpuId);
    vos_printf("enFuncId=%d\n", pstDiccTraceInfo->enFuncId);
    vos_printf("ulPid=%d\n",    pstDiccTraceInfo->ulPid);
    vos_printf("ulLine=%d\n",   pstDiccTraceInfo->ulLine);
    vos_printf("enResult=%d\n", pstDiccTraceInfo->enResult);
}    /* DICC_TraceInfo */

VOS_VOID DICC_DealWithFatalError(DICC_SOFT_REBOOT_INFO_STRU *pstRebootInfo)
{
    VOS_UINT32    ulTaskID;

    if (DICC_BBIT == g_ucDiccStability)
    {
        ulTaskID = VOS_GetCurrentTaskID();

        if ( VOS_OK != VOS_SuspendTask( ulTaskID ) )
        {
            DICC_LOG(PS_PRINT_ERROR, "# SUSPED PPP task error.\r\n");
        }
    }

    if (DICC_RELEASE == g_ucDiccStability)
    {
        if (VOS_NULL_PTR != pstRebootInfo)
        {
            /* ����OM API���е��帴λ */
            VOS_ProtectionReboot((VOS_INT)pstRebootInfo->ulModule,
                (VOS_INT)(pstRebootInfo->ulFile), (VOS_INT)(pstRebootInfo->ulLine),
                (VOS_CHAR *)(pstRebootInfo->pucData),
                sizeof(pstRebootInfo->ulDataLen) );
        }
    }
}

/*****************************************************************************
 �� �� ��  : DICC_SndEvent
 ��������  : �ϱ�DICC�¼�
 �������  : ulPid - ����PID
             enEventId - �¼�ID
             pEventData - �¼���Ϣ����
             ulDataLen - �¼���Ϣ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��22��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  DICC_SndEvent(DICC_MNTN_EVENT_ID_ENUM_UINT16 enEventId,
                        VOS_VOID   *pEventData,
                        VOS_UINT32  ulDataLen,
                        DICC_CPU_ID_ENUM_UINT8  enCpuId)
{
    DIAG_EVENT_IND_STRU                 stEvent;

    stEvent.ulEventId   = enEventId;
    stEvent.ulPid       = LOCAL_UEPS_PID_DICC;
    stEvent.ulModule    = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(LOCAL_UEPS_PID_DICC), DIAG_MODE_COMM);
    stEvent.ulLength    = ulDataLen;
    stEvent.pData       = pEventData;

    /*����OM���¼��ϱ��ӿ�*/
#if (VOS_WIN32 != VOS_OS_VER)
    if (VOS_OK != DIAG_EventReport((DIAG_EVENT_IND_STRU *)&pEventData))
    {
        DICC_LOG(PS_PRINT_ERROR, "[LOCAL CPU_ID: DICC_SndEvent] DIAG_EventReport fail");
    }
#else
    /* �ƻ���PC���ϲ���A��, ����ǰOAM��û�а�DIAG_EventReport��WIN32��ʵ�ֺ�,
       �������¼�, ��ʱ��DIAG_EventReport�ϱ� */
    if (DICC_CPU_ID_CCPU == enCpuId)
    {
        if (VOS_OK != DIAG_EventReport((DIAG_EVENT_IND_STRU *)&pEventData))
        {
            DICC_LOG(PS_PRINT_ERROR, "[LOCAL CPU_ID: DICC_SndEvent] DIAG_EventReport fail");
        }
    }

    if (DICC_CPU_ID_ACPU == enCpuId)
    {
        if (VOS_OK != DIAG_EventReport((DIAG_EVENT_IND_STRU *)&pEventData))
        {
            DICC_LOG(PS_PRINT_ERROR, "[LOCAL CPU_ID: DICC_SndEvent] DIAG_EventReport fail");
        }
    }
#endif

    return ;
}    /* DICC_SndEvent */

VOS_UINT8* DICC_GetCtrlChnAddr(VOS_UINT8 ucChnId, DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT8                               *pucCtrlChnAddr = VOS_NULL_PTR;
    VOS_UINT8                               *pucStartAddr = VOS_NULL_PTR;

    pucStartAddr   = (VOS_UINT8*)(g_astChanRole[enCpuId].pastDICCMgmt);
    pucCtrlChnAddr = pucStartAddr + sizeof(DICC_CTRL_STRU) + (ucChnId * sizeof(DICC_CHAN_CTRL_STRU));

    return pucCtrlChnAddr;
}/* DICC_GetCtrlChnAddr */

VOS_UINT8* DICC_GetTtfRingQStChnAddr(VOS_UINT8 ucChnId, DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    DICC_CHAN_CTRL_STRU                    *pstDiccChnCtrl = VOS_NULL_PTR;
    VOS_UINT8                              *pucSpace = VOS_NULL_PTR;

    /* ��ʼ��Ϊ�˼��ڴ��׵�ַ */
    pucSpace = (VOS_UINT8 *)(g_astChanRole[enCpuId].pastDICCMgmt);
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* ����ͨ����TTFRINGQSTƫ���� */
    pucSpace = pucSpace + pstDiccChnCtrl->ulTtfRingQStAddrOffSet;

    return pucSpace;
}/* DICC_GetTtfRingQStChnAddr */

VOS_UINT8* DICC_GetQueueNodeChnAddr(VOS_UINT8 ucChnId,
               DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    DICC_CHAN_CTRL_STRU                    *pstDiccChnCtrl = VOS_NULL_PTR;
    VOS_UINT8                              *pucSpace = VOS_NULL_PTR;

    /* ��ʼ��Ϊ�˼��ڴ��׵�ַ */
    pucSpace = (VOS_UINT8 *)(g_astChanRole[enCpuId].pastDICCMgmt);
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* ����ͨ����TTFRINGQSTƫ���� */
    pucSpace = pucSpace + pstDiccChnCtrl->ulQueueNodeAddrOffSet;

    return pucSpace;
}/* DICC_GetQueueNodeChnAddr */

/*****************************************************************************
�� �� ��  : DICC_GetChannelNodeCnt
��������  : ����ȡͨ�������ݿ����Ĳ���
�������  : ulPid - ���ô˽ӿڵ�PID
            ucChanId - ͨ��ID
            enGetChnNodeCntType - ָʾ��ȡͨ�����Ѿ���ŵ����ݸ���,
                                  ����ͨ���п��Լ�����ŵĸ���
�������  : ��
�� �� ֵ  : �����ɹ����, DICC_OK - �ɹ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��8��11��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_CheckCpuId(DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    if (DICC_CPU_ID_BUTT <= enCpuId)
    {
        return DICC_ERR_CPU_ID_NOT_MATCH;
    }

#if (VOS_WIN32 != VOS_OS_VER)
 #if (OSA_CPU_CCPU == VOS_OSA_CPU)
    if (DICC_CPU_ID_CCPU != enCpuId)
    {
        return DICC_ERR_CPU_ID_NOT_MATCH;
    }
 #elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    if (DICC_CPU_ID_ACPU != enCpuId)
    {
        return DICC_ERR_CPU_ID_NOT_MATCH;
    }
 #endif
#endif

    return DICC_OK;
}

/*****************************************************************************
�� �� ��  : DICC_RecordIsrOp
��������  : ��¼�û��жϲ���
�������  : pstIsrRecord - �û������жϵļ�¼��Ϣ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��13��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DICC_RecordIsrOp(DICC_RECORD_ISR_STRU *pstIsrRecord,
                          DICC_CPU_ID_ENUM_UINT8       enCpuId)
{
    DICC_DFX_STRU        *pstDFx;
    VOS_UINT8             ucChanId;

    pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);

    if (PS_TRUE == pstIsrRecord->enOpResult)    /* ��ȷ�����ж�, ��¼�¹켣���� */
    {
        /* ��ͨ����ɳ�ʼ����, ���ǽ��ն���DiableIsr, EnableIsr */
        ucChanId = g_astChanRole[enCpuId].aenRecver[pstIsrRecord->enServiceType];

        if (DICC_SERVICE_ISR_ENABLE == pstIsrRecord->enIsrOp)
        {
            pstDFx->astChanStatus[ucChanId].stIsrOp.ulEnableOpPid  = pstIsrRecord->ulPid;
            pstDFx->astChanStatus[ucChanId].stIsrOp.ulEnableOpTime = mdrv_timer_get_normal_timestamp();
            pstDFx->astChanStatus[ucChanId].stIsrOp.ulEnableCnt++;
        }
        else
        {
            pstDFx->astChanStatus[ucChanId].stIsrOp.ulDisableOpPid  = pstIsrRecord->ulPid;
            pstDFx->astChanStatus[ucChanId].stIsrOp.ulDisableOpTime = mdrv_timer_get_normal_timestamp();
            pstDFx->astChanStatus[ucChanId].stIsrOp.ulDisableCnt++;
        }
    }
    else    /* ��DiableIsr, EnableIsr��������ʱ, ��¼��Debug��, ֻ��¼�����һ�ε����� */
    {
        if (DICC_SERVICE_ISR_ENABLE == pstIsrRecord->enIsrOp)
        {
            pstDFx->stIsrDbg.ulInvalidEnableOpPid   = pstIsrRecord->ulPid;
            pstDFx->stIsrDbg.ulInvalidEnableOpTime  = mdrv_timer_get_normal_timestamp();
        }
        else
        {
            pstDFx->stIsrDbg.ulInvalidDisableOpPid  = pstIsrRecord->ulPid;
            pstDFx->stIsrDbg.ulInvalidDisableOpTime = mdrv_timer_get_normal_timestamp();
        }
    }
}    /* DICC_RecordIsrOp */

/*****************************************************************************
�� �� ��  : DICC_EnableIsr
��������  : �ϱ��û�������Ϣ
�������  : ʹ�ܺ˼�ͨ���ж�API
�������  : ulPid - ����PID
            enServiceType - �����
�� �� ֵ  : �����ɹ����, DICC_OK - �ɹ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��8��13��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_EnableIsr(VOS_UINT32                   ulPid,
                          DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
                          DICC_CPU_ID_ENUM_UINT8       enCpuId)
{
#if (1 == DICC_DFX_SWITCH)
    DICC_RECORD_ISR_STRU    stIsrRecord;
#endif
    VOS_UINT32              ulRet;
    /*lint --e{550, 830} */
    PS_BOOL_ENUM_UINT8      enOpResult;    /* PS_FALSE - ������ж� */
    VOS_INT32               lIntRet;    /* �жϲ�������ֵ */
    IPC_INT_LEV_E           lIntLvl;

    if ((DICC_SERVICE_TYPE_0 != enServiceType)
        && (DICC_SERVICE_TYPE_1 != enServiceType))
    {
        enOpResult = PS_FALSE;    /* �޴˷������, ����������ж� */
        ulRet      = DICC_ERR_SERVCE_UNDEFINED;
    }
    else
    {
        enOpResult = PS_TRUE;    /* ��ȷ�ķ������, ������������ж� */
        ulRet      = DICC_OK;

        if (DICC_SERVICE_TYPE_0 == enServiceType)
        {
            lIntLvl = DICC_SERVICE_0_INT_LEVEL;
        }
        else
        {
            lIntLvl = DICC_SERVICE_1_INT_LEVEL;
        }

        /* ʹ��service֪ͨ�ж� */
#ifndef WTTF_PS_FUSION_PC_ST
        lIntRet = mdrv_ipc_int_enable(lIntLvl);
#else
        lIntRet = VHW_IPC_IntEnable(ulPid,lIntLvl);
#endif
        if (BSP_OK != lIntRet)
        {
            ulRet      = DICC_ERR_OP_ISR_FAIL;
        }
    }

#if (1 == DICC_DFX_SWITCH)
    SET_ISR_RECORD(&stIsrRecord, ulPid, enServiceType, DICC_SERVICE_ISR_ENABLE, enOpResult);
    DICC_RecordIsrOp(&stIsrRecord, enCpuId);    /* ��¼�û�������ж� */
#endif

    return ulRet;
}    /* DICC_EnableIsr */

/*****************************************************************************
�� �� ��  : DICC_DisableIsr
��������  : ȥʹ�ܺ˼�ͨ���ж�API
            ���жϷ��������ִ��, �����������Բ���
�������  : ulPid - ����PID
            enServiceType - �����
�������  : ��
�� �� ֵ  : �����ɹ����, DICC_OK - �ɹ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��7��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_DisableIsr(VOS_UINT32 ulPid, DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
               DICC_CPU_ID_ENUM_UINT8       enCpuId)
{
#if (1 == DICC_DFX_SWITCH)
    DICC_RECORD_ISR_STRU    stIsrRecord;
#endif
    VOS_UINT32              ulRet;
    /*lint --e{550, 830} */
    PS_BOOL_ENUM_UINT8      enOpResult;    /* PS_FALSE - ������ж� */
    VOS_INT32               lIntRet;    /* �жϲ�������ֵ */
    IPC_INT_LEV_E           lIntLvl;

    if ((DICC_SERVICE_TYPE_0 != enServiceType)
        && (DICC_SERVICE_TYPE_1 != enServiceType))
    {
        enOpResult = PS_FALSE;    /* �޴˷������, ����������ж� */
        ulRet      = DICC_ERR_SERVCE_UNDEFINED;
    }
    else
    {
        enOpResult = PS_TRUE;    /* ��ȷ�ķ������, ������������ж� */
        ulRet      = DICC_OK;

        if (DICC_SERVICE_TYPE_0 == enServiceType)
        {
            lIntLvl = DICC_SERVICE_0_INT_LEVEL;
        }
        else
        {
            lIntLvl = DICC_SERVICE_1_INT_LEVEL;
        }

        /* ȥʹ��service֪ͨ�ж� */
#ifndef WTTF_PS_FUSION_PC_ST
        lIntRet = mdrv_ipc_int_disable(lIntLvl);
#else
        lIntRet = VHW_IPC_IntDisable(ulPid,lIntLvl);
#endif

        if (BSP_OK != lIntRet)
        {
            ulRet      = DICC_ERR_OP_ISR_FAIL;
        }
    }

#if (1 == DICC_DFX_SWITCH)
    SET_ISR_RECORD(&stIsrRecord, ulPid, enServiceType, DICC_SERVICE_ISR_DISABLE, enOpResult);
    DICC_RecordIsrOp(&stIsrRecord, enCpuId);    /* ��¼�û�������ж� */
#endif

    return ulRet;
}    /* DICC_DisableIsr */


VOS_UINT32 DICC_CheckIsExistEnoughMem(DICC_BLK_CHN_INFO_STRU *penSndChnInfo,
               DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT32 ulAllocMemSize;

    if ((0 == penSndChnInfo->usChnBlkNum)
        || (DICC_PER_QUEUE_MAX_NODE_NUM < penSndChnInfo->usChnBlkNum))
    {
        DICC_LOG1(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_CheckIsExistEnoughMem] check <usChnBlkNum> fail",
            penSndChnInfo->usChnBlkNum);

        return DICC_ERR_CHAN_BLK_NUM;
    }

    if (DICC_INFO_BLOCK_MAX_LEN < penSndChnInfo->usChnBlkSize)
    {
        DICC_LOG1(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_CheckIsExistEnoughMem] check <usChnBlkSize> fail",
            penSndChnInfo->usChnBlkSize);

        return DICC_ERR_CHAN_BLK_SIZE;
    }

    ulAllocMemSize = (penSndChnInfo->usChnBlkNum) * (penSndChnInfo->usChnBlkSize + sizeof(VOS_VOID *));

    if ((g_astChanRole[enCpuId].pastDICCMgmt->ulCurrSize + ulAllocMemSize) > DICC_MEMORY_TOTAL_SIZE)
    {
        DICC_LOG(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_CheckIsExistEnoughMem] check total memory size fail");

        /* ȷ����blk_size��blk_num����ȷ��, �Ͳ�������ڴ治��, �ʲ����ظ��ϱ�SDT */
        return DICC_ERR_MEM_SIZE;
    }

    return DICC_OK;
}/* DICC_CheckIsExistEnoughMem */


VOS_UINT32 DICC_CheckChnInitStatus(DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
               DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    volatile DICC_CHAN_CTRL_STRU       *pstDiccChnCtrl;

    ucChnId = g_astChanRole[enCpuId].aenSender[enServiceType];
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* ��������������ռpstDiccChnCtrl->ucValidFlag�����⣬��Ҫ�����񻥳��� */

    if (DICC_CHAN_STATUS_INITIALED == pstDiccChnCtrl->enValidFlag)    /* ����ͨ���ѳ�ʼ�� */
    {
        VOS_TaskUnlock();
        DICC_LOG1(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_CheckChnInitStatus] <pstDiccChnCtrl->enValidFlag>",
            pstDiccChnCtrl->enValidFlag);
        return DICC_ERR_EXISTED_CHAN_ID;
    }


    return DICC_OK;
}/* DICC_CheckChnInitStatus */

VOS_UINT32  DICC_RING_Q_InitAndNodeAddrSet(VOS_UINT32 ulPid,
                DICC_CHAN_CTRL_STRU *pstDiccChnCtrl,
                DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT16                          usNodeLoop = 0;

    /* ָ���ͨ����ring_queue��ָ��(ring_queue��ppNode) */
    VOS_VOID                           *pstTtfRingQStAddr = VOS_NULL_PTR;

    /* ͨ����ring_queue��ָ������Ļ�ַ */
    DICC_QUEUE_NODE_STRU               *pstQueueNodeBaseAddr = VOS_NULL_PTR;

    /* �ڼ���ÿ���˼����ݵ��׵�ַʱʹ�õ�����ʱָ�� */
    VOS_UINT8                          *pucBaseQueueNodeAddr = VOS_NULL_PTR;

    /* ÿ���˼����ݵ��׵�ַ */
    VOS_UINT8                          *pucQueuePerNodeAddr = VOS_NULL_PTR;
    DICC_QUEUE_NODE_STRU               *pstPerNodeAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulChnNodeSize;

    ulChnNodeSize        = sizeof(DICC_QUEUE_NODE_STRU);
    pstTtfRingQStAddr = (VOS_VOID *)DICC_GetTtfRingQStChnAddr(pstDiccChnCtrl->ucChanId, enCpuId);
    pstQueueNodeBaseAddr = (DICC_QUEUE_NODE_STRU *)DICC_GetQueueNodeChnAddr(pstDiccChnCtrl->ucChanId, enCpuId);
    ulRslt = TTF_RING_Q_InitAndNodeAddrSet(ulPid,
                                           &(pstDiccChnCtrl->stRingBuffer),
                                           (VOS_VOID **)pstTtfRingQStAddr,
                                           (VOS_VOID *)pstQueueNodeBaseAddr,
                                           ulChnNodeSize,
                                           (VOS_UINT32)pstDiccChnCtrl->usChnBlkNum);
    if (PS_FAIL == ulRslt)
    {
        DICC_LOG(PS_PRINT_WARNING,
            "[LOCAL CPU_ID: DICC_RING_Q_InitAndNodeAddrSet] TTF_RING_Q_InitAndNodeAddrSet fail");
        return DICC_ERR_RING_QUEUE_FAIL;
    }

    pucBaseQueueNodeAddr = (VOS_UINT8 *)pstQueueNodeBaseAddr;
    for (usNodeLoop = 0; usNodeLoop < pstDiccChnCtrl->usChnBlkNum; usNodeLoop++)
    {
        pucQueuePerNodeAddr = (pucBaseQueueNodeAddr + (ulChnNodeSize * usNodeLoop));

        /* �˼乲����ĵ�ַ */
        pstPerNodeAddr = (DICC_QUEUE_NODE_STRU *)pucQueuePerNodeAddr;

        /* �˼䴫�ݽ���ڴ����� */
        VOS_MemSet(pstPerNodeAddr->aucPriData, 0x0, sizeof(pstPerNodeAddr->aucPriData));

        pstPerNodeAddr->usIndex = usNodeLoop;
        pstPerNodeAddr->usMagicNum = DICC_MAGIC_NUM_VALUE;
    }

    return DICC_OK;
} /* DICC_RING_Q_InitAndNodeAddrSet */

/*****************************************************************************
�� �� ��  : DICC_SenderChnInit
��������  : ͨ�����Ͷ˳�ʼ��
�������  : ucChnId - ͨ��ID
            penChnInfo - ͨ��������Ϣ(����˼���Ϣ�����ʹ�С��)
�������  : ��
�� �� ֵ  : �����ɹ����, DICC_OK - �ɹ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��8��12��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_SenderChnInit(VOS_UINT32 ulPid, DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                              DICC_BLK_CHN_INFO_STRU        *penChnInfo,
                              DICC_CHAN_LOCAL_SEM_PAPA_STRU *pstLocalSemPara,
                              DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU       *pstDiccChnCtrl;
    VOS_UINT32                          ulSize;
    VOS_UINT32                          ulReturn;


    /* ��ʼ������ͬһ����Ҫ����, ���ⲿ������ȷ�� */

    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* ͨ���� */
    pstDiccChnCtrl->ucChanId               = ucChnId;
    pstDiccChnCtrl->usChnBlkNum            = penChnInfo->usChnBlkNum;
    pstDiccChnCtrl->ucPriDataLen           = (VOS_UINT8)(penChnInfo->usChnBlkSize);
    pstDiccChnCtrl->ulTtfRingQStAddrOffSet = g_astChanRole[enCpuId].pastDICCMgmt->ulCurrSize;

    /* pstDiccChnCtrl->ulQueueNodeAddrOffSet����ͨ��TFFRINGQST�Ĵ�С */
    pstDiccChnCtrl->ulQueueNodeAddrOffSet = pstDiccChnCtrl->ulTtfRingQStAddrOffSet
        + (penChnInfo->usChnBlkNum * sizeof(VOS_VOID *));

    /* ͨ��������ܳ��� */
    ulSize = (penChnInfo->usChnBlkNum) * (sizeof(DICC_QUEUE_NODE_STRU) + sizeof(VOS_VOID *));

    /* ��ʼ��ͨ���Ļ��λ��沢�ҹ����˼乲�����ַ��ͨ���������� */
    ulReturn = DICC_RING_Q_InitAndNodeAddrSet(ulPid, (DICC_CHAN_CTRL_STRU *)pstDiccChnCtrl, enCpuId);

    if (DICC_OK != ulReturn)
    {
        DICC_LOG(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_SenderChnInit] DICC_RING_Q_InitAndNodeAddrSet fail");

        return DICC_ERR_RING_QUEUE_FAIL;
    }

    /* ��������, ע���������Ĵ����ı���, ��ͨ���˺����ĵ�����tasklockʵ�ֵ� */
    DICC_SPIN_LOCK();

    /* ͨ��״̬��ʼ�� */
    pstDiccChnCtrl->ucStateMask &= ~DICC_CHAN_SENDER_OPEN_MASK;
    pstDiccChnCtrl->enValidFlag = DICC_CHAN_STATUS_INITIALED;

    /* ���º˼�ͨ�����ƽṹ */
    g_astChanRole[enCpuId].pastDICCMgmt->ulCurrSize += (ulSize);

    /* �������� */
    DICC_SPIN_UNLOCK();

    return DICC_OK;
}    /* DICC_SenderChanInit */

/*****************************************************************************
�� �� ��  : DICC_ChnIsrInit
��������  : DICC�û�ͨ����ʼ��������麯��
�������  : enServiceType - ��������
            pfuncRecvIsr - �жϷ������
�������  : ��
�� �� ֵ  : �����ɹ����, DICC_OK - �ɹ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��8��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_ChnIsrInit(VOS_UINT32 ulPid, VOS_UINT32 ulIntLevel,
                           VOIDFUNCPTR pfuncRecvIsr, DICC_INT_OP_STRU *pstIntOp)
{
    VOS_INT32  lIntRet;


    /* �ҽ��ж� */
#ifndef WTTF_PS_FUSION_PC_ST
    lIntRet = mdrv_ipc_int_connect(((IPC_INT_LEV_E)ulIntLevel), ((VOIDFUNCPTR)pfuncRecvIsr), VOS_NULL);
#else
    lIntRet = VHW_IPC_IntConnect(ulPid,((IPC_INT_LEV_E)ulIntLevel), ((VOIDFUNCPTR)pfuncRecvIsr), VOS_NULL);
#endif
    /* �ڴ˽��жϲ�����¼���� */
    pstIntOp->ulIntLevel = ulIntLevel;
    pstIntOp->lResult = lIntRet;

    if (lIntRet != VOS_OK)
    {
        DICC_LOG1(PS_PRINT_ERROR,
            "[LOCAL CPU_ID: DICC_ChnIsrInit] connect <ulIntLevel> ISR fail",
            (VOS_INT32)ulIntLevel);
        return DICC_ERR_ISR_CONNECT_FAIL;
    }

    /* ʹ��֪ͨ�ж� */
    mdrv_ipc_int_enable((IPC_INT_LEV_E)ulIntLevel);

    return DICC_OK;
}    /* DICC_ChnIsrInit */

/*****************************************************************************
�� �� ��  : DICC_RecverChnInit
��������  : ͨ�����ն˳�ʼ��
�������  : ulPid - ����PID
            enServiceType - ��������
            pfuncRecvIsr - �жϷ������
�������  : ��
�� �� ֵ  : �����ɹ����, DICC_OK - �ɹ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��8��12��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_RecverChnInit(VOS_UINT32                        ulPid,
                              DICC_SERVICE_TYPE_ENUM_UINT8      enServiceType,
                              VOIDFUNCPTR                       pfuncRecvIsr,
                              DICC_INT_OP_STRU                 *pstIntOp,
                              DICC_CHAN_LOCAL_SEM_PAPA_STRU    *pstLocalSemPara,
                              DICC_CPU_ID_ENUM_UINT8            enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU       *pstDiccChnCtrl  = VOS_NULL_PTR;
    DICC_CHAN_ID_ENUM_UINT8             ucChnId         = g_astChanRole[enCpuId].aenRecver[enServiceType];
    VOS_UINT32                          ulReturn;
    VOS_UINT32                          ulIntLevel;

    /* ��ʼ������ͬһ����Ҫ����, Ŀǰ�����ⲿ������ȷ�� */

    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* ͨ���� */
    pstDiccChnCtrl->ucChanId = ucChnId;

    /* ��������, ע���������Ĵ����ı���, ��ͨ���˺����ĵ�����tasklockʵ�ֵ� */
    DICC_SPIN_LOCK();

    /* ͨ��״̬��ʼ�� */
    pstDiccChnCtrl->ucStateMask &= ~DICC_CHAN_RECVER_OPEN_MASK;

    /* �������� */
    DICC_SPIN_UNLOCK();

    if (DICC_SERVICE_TYPE_0 == enServiceType)
    {
        ulIntLevel = DICC_SERVICE_0_INT_LEVEL;
    }
    else
    {
        ulIntLevel = DICC_SERVICE_1_INT_LEVEL;
    }

    ulReturn = DICC_ChnIsrInit(ulPid, ulIntLevel, pfuncRecvIsr, pstIntOp);

    return ulReturn;
}    /* DICC_RecverChanInit */

/*****************************************************************************
�� �� ��  : DICC_ChkChnInit
��������  : DICC�û�ͨ����ʼ��������麯��
�������  : enServiceType - ��������
            pstInitChanInfo - ͨ���Ļ�����Ϣ
�������  : ��
�� �� ֵ  : �����ɹ����, DICC_OK - �ɹ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��7��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_ChkChnServiceInfo(DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
                           DICC_INIT_CHN_INFO_STRU     *pstInitChanInfo,
                           DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT32 ulRet;

    if (DICC_SERVICE_TYPE_BUTT <= enServiceType)
    {
        DICC_LOG1(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_ChkChnInit] undefined <enServiceType>",
            enServiceType);
        return DICC_ERR_SERVCE_UNDEFINED;
    }

    if (DICC_CHAN_ROLE_SENDER == pstInitChanInfo->enUserRole)
    {
        /* ���ͨ���Ƿ��Ѿ���ʼ�� */
        ulRet = DICC_CheckChnInitStatus(enServiceType, enCpuId);
        if (DICC_OK != ulRet)
        {
            return ulRet;
        }

        /* ���˼��Ƿ����㹻�Ŀռ�����ʼ��ͨ�� */
        ulRet = DICC_CheckIsExistEnoughMem(&(pstInitChanInfo->u.stSndInitInfo.stSndChnInfo), enCpuId);
        if (DICC_OK != ulRet)
        {
            return ulRet;
        }
    }
    else if (DICC_CHAN_ROLE_RECVER == pstInitChanInfo->enUserRole)
    {
        if (VOS_NULL_PTR == pstInitChanInfo->u.stRcvInitInfo.pfuncRecvIsr)    /* �жϷ������Ϊ�� */
        {
            DICC_LOG2(PS_PRINT_WARNING,
                "[LOCAL CPU_ID: DICC_ChkChnInit] pfuncRecvIsr is NULL, <enServiceType> <enUserRole>",
                enServiceType, pstInitChanInfo->enUserRole);
            return DICC_ERR_RECV_ISR_NULL;
        }
    }
    else
    {
        DICC_LOG1(PS_PRINT_WARNING, "[LOCAL CPU_ID: DICC_ChkChnInit] undefined enUserRole, <enUserRole>",
            pstInitChanInfo->enUserRole);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    return DICC_OK;
}   /* DICC_ChkChnInit */

/*****************************************************************************
�� �� ��  : DICC_Sync
��������  : DICC˫�˹����ڴ��ʼ��ͬ��
�������  : ��
�������  : ��
�� �� ֵ  : �����ɹ����, DICC_OK - �ɹ�, ���� - ʧ��
���ú���  :
��������  :
˵    ��  : ��ʼ������ͬһ����Ҫ����
            ��ֹ�ظ�����Ӳ���ź���, ���ж�, ֱ��������������,
            ����һ������ṹû����ɳ�ʼ��, �������ȼ���������, �ж�ucSemCreatedΪ1,
            �뿪�˺���, ʵ���ϴ�ʱ��û�����sync�ĳ�ʼ��

�޸���ʷ      :
 1.��    ��   : 2011��10��20��
   ��    ��   : wangrong
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_Sync(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum, VOS_UINT32 ulPid,
               DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    volatile VOS_UINT32                *pulDiccMagicAddr;
    DICC_CHAN_SYNC_PARA_STRU            stSyncPara;
    volatile VOS_UINT8                 *pucStartAddr;
    DICC_SOFT_REBOOT_INFO_STRU          stRebootInfo     = {0};


    VOS_MemSet((VOID *)&stSyncPara, 0x00, sizeof(DICC_CHAN_SYNC_PARA_STRU));

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

#if (VOS_WIN32 != VOS_OS_VER)
    if (DICC_CPU_ID_CCPU == enCpuId)
    {
        pulDiccMagicAddr = (VOS_UINT32 *)(DICC_MEM_INIT_MAGIC_NUM_ADDR);

        pucStartAddr = (VOS_UINT8 *)DICC_TTF_PHY_TO_VIRT(DICC_MEM_START_PHY_ADDR);
    }
    else
    {
        /* ע��DICC_MEM_INIT_MAGIC_NUM_ADDR���ڵ�������ַ��, ��Ҫ����Linux IO_ADDRESS���е�ַת�� */
        pulDiccMagicAddr = (VOS_UINT32 *)DICC_DRV_PHY_TO_VIRT(DICC_MEM_INIT_MAGIC_NUM_ADDR);

        pucStartAddr = (VOS_UINT8 *)DICC_TTF_PHY_TO_VIRT(DICC_MEM_START_PHY_ADDR);
    }
#else
    pulDiccMagicAddr = (VOS_UINT32 *)DICC_DRV_PHY_TO_VIRT(DICC_MEM_INIT_MAGIC_NUM_ADDR);
    pucStartAddr = (VOS_UINT8 *)DICC_TTF_PHY_TO_VIRT(DICC_MEM_START_PHY_ADDR);
#endif

    if (1 == g_astChanRole[enCpuId].ucSemCreated)    /* ��CPU�Ѵ���Ӳ���ź��� */
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

        return DICC_OK;    /* ��ֹ�ظ����� */
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

    /* ������������ͬ��DICC�ڴ������Ӳ���ź��� */
    mdrv_ipc_sem_creat(IPC_SEM_DICC);

    g_astChanRole[enCpuId].ucSemCreated = 1;    /* �Ѿ�����Ӳ���ź��� */

    /* ��ȡӲ���ź���, ���ļĴ���������ͨ���ⲿ��������tasklock������ */
    stSyncPara.stHwSemPara.ulSingnalNum = IPC_SEM_DICC;
    stSyncPara.stHwSemPara.lTimeout     = 0;
    stSyncPara.stHwSemPara.lResult      = mdrv_ipc_sem_take(IPC_SEM_DICC, 0);
    if (BSP_OK != stSyncPara.stHwSemPara.lResult)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_ERR_USE_HW_SEMPHORE_FAIL);

        SET_DICC_SOFT_REBOOT_INFO((&stRebootInfo), TTF_SOFT_REBOOT_MODULE_ID_DICC_MEM_CLEAN_SYNC_FAIL,
            ulFileId, ulLineNum, (&stSyncPara), sizeof(stSyncPara));
        DICC_DealWithFatalError(&stRebootInfo);

        DICC_LOG2(PS_PRINT_ERROR, "[<LOCAL CPU_ID>: DICC_Sync] <SignalNum> <timeout>",
            IPC_SEM_DICC, 0);

        return DICC_ERR_USE_HW_SEMPHORE_FAIL;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

    /* take���ź�������Ҫ���ħ���֣����û�����ã�����Խ����ڴ���0 */
    if (0 == (*pulDiccMagicAddr))
    {
        DICC_LOG1(PS_PRINT_INFO, "[<LOCAL CPU_ID>: DICC_Sync] <DICC MAGIC NUM> ",
            (VOS_INT32)(*pulDiccMagicAddr));

        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

        VOS_MemSet((VOID *)pucStartAddr, 0x00, DICC_QUEUE_MEM_SIZE);

        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

        *pulDiccMagicAddr = DICC_MEM_INIT_MAGIC_NUM;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

    stSyncPara.ulDiccMagic = (*pulDiccMagicAddr);

    /* ��ֹ����MAGIC-NUM��AXI�ڴ��ϵ�û��������������߱��۸� */
    if (DICC_MEM_INIT_MAGIC_NUM != stSyncPara.ulDiccMagic)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_ERR_MAGIC_MEM_TEMPERED);

        SET_DICC_SOFT_REBOOT_INFO((&stRebootInfo), TTF_SOFT_REBOOT_MODULE_ID_DICC_MEM_CLEAN_SYNC_FAIL,
            ulFileId, ulLineNum, (&stSyncPara), sizeof(stSyncPara));
        DICC_DealWithFatalError(&stRebootInfo);

        DICC_LOG1(PS_PRINT_ERROR, "[<LOCAL CPU_ID>: DICC_Sync] <ulDiccMagic> tempered",
            (VOS_INT)stSyncPara.ulDiccMagic);

        /* �ͷ�Ӳ���ź��� */
        mdrv_ipc_sem_give(IPC_SEM_DICC);

        return DICC_ERR_MAGIC_MEM_TEMPERED;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_TRACE_OK);

    /* ��ʼ��ͨ������ṹ��ȫ�ֱ����׵�ַ */
    g_astChanRole[enCpuId].pastDICCMgmt = (DICC_CTRL_STRU *)pucStartAddr;
    DEBUG_PRINT("DICC_MemInit Succ! virtual: 0x%0x\n", (int)(g_astChanRole[enCpuId].pastDICCMgmt));

    /* ��ʼ��ͨ�����ƽṹ�ı���, ����һ�˽�DICC�����ڴ��С��¼��ȥ
       ��һ�˿�����˸��¹�CurrSize, �����Ѿ���ĳЩͨ��init��, ��ʱ���˲�ִ�е�����,
       �����Ҫ�ж��Ƿ�Ϊ0, ��û�м�¼�� */
    if (0 == g_astChanRole[enCpuId].pastDICCMgmt->ulCurrSize)
    {
        g_astChanRole[enCpuId].pastDICCMgmt->ulCurrSize = sizeof(DICC_CTRL_STRU) + (DICC_MAX_CHAN_NUM * sizeof(DICC_CHAN_CTRL_STRU));
    }

#if (1 == DICC_DFX_SWITCH)
    g_astChanRole[enCpuId].pastDICCMgmt->stDFx.enDFxEnabled = PS_TRUE;
#else
    g_astChanRole[enCpuId].pastDICCMgmt->stDFx.enDFxEnabled = PS_FALSE;
#endif

    /* �ͷ�Ӳ���ź��� */
    mdrv_ipc_sem_give(IPC_SEM_DICC);

    return DICC_OK;
}

/*****************************************************************************
�� �� ��  : DICC_SingleChnInit
��������  : DICC�û���ͨ����ʼ��API(���շ�������ʼ��һ��ͨ��)
�������  : ulPid - ���ô˽ӿڵ�PID
            enServiceType - ��������
            pstInitChanInfo - Ҫ��ʼ����ͨ���ľ������
�������  : ��
�� �� ֵ  : �����ɹ����, DICC_OK - �ɹ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��11��28��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_SingleChnInitAction(VOS_UINT32             ulFileId,
                              VOS_UINT32                   ulLineNum,
                              VOS_UINT32                   ulPid,
                              DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
                              DICC_INIT_CHN_INFO_STRU     *pstInitChanInfo,
                              DICC_CPU_ID_ENUM_UINT8       enCpuId)
{
    VOS_UINT32                          ulRet;
    DICC_CHAN_SINGLE_INIT_CONTENT_STRU  stInitChanInfo     = {0};
    DICC_SOFT_REBOOT_INFO_STRU          stRebootInfo       = {0};

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* ע���ڴ�֮ǰ, �޷�ȷ��enCpuId�Ƿ�����, ֱ���������±���ܻ��������, �ʲ��ܵ���TRACE */
    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, DICC_TRACE_OK);

    if (VOS_NULL_PTR == pstInitChanInfo)
    {
        DICC_LOG(PS_PRINT_WARNING,
            "[LOCAL CPU_ID: DICC_ChkChnInit] pstSndInitChanInfo is NULL");

        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, DICC_ERR_INFO_PTR_NULL);
        return DICC_ERR_INFO_PTR_NULL;
    }

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    /* �����ȼ�������ռʱ�����ܻ�����ظ���ʼ��g_stDiccSpinLock����� */
    if( DICC_MUTEX_SEM_NOT_CREATE == g_ulDiccMultiCoreFlag )
    {
        spin_lock_init(&g_stDiccSpinLock);
    }

    spin_lock(&g_stDiccSpinLock);
#else
    VOS_TaskLock();
#endif

    if( DICC_MUTEX_SEM_NOT_CREATE == g_ulDiccMultiCoreFlag )
    {
        /* �������ػ����ź���(��һ������ֻ����4�ֽ�, DICC Local Mutex, ��дΪDLM) */
        ulRet = VOS_SmMCreate("DLM", VOS_SEMA4_FIFO,
                (VOS_SEM *)(&(g_astChanRole[enCpuId].ulDiccLocalMutexSem)));

        if (VOS_OK != ulRet)
        {
            SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
                ID_DICC_TRACE_FUNC_MARK_SYNC, __LINE__, DICC_ERR_LOCAL_SEMPHORE_FAIL);

            DICC_DealWithFatalError(&stRebootInfo);

            DICC_LOG(PS_PRINT_ERROR, "[<LOCAL CPU_ID>: DICC_SingleChnInitAction] Create g_ulDiccLocalMutexSem fail ");

            return DICC_ERR_LOCAL_SEMPHORE_FAIL;
        }

        g_ulDiccMultiCoreFlag   = DICC_MUTEX_SEM_CREATED;
    }

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    spin_unlock(&g_stDiccSpinLock);
#else
    VOS_TaskUnlock();
#endif

    ulRet = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != ulRet)
    {
        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_SingleChnInitAction] take ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)(ulRet));

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    /* ����DICC���ƽṹ�ڴ��������ͬ�� */
    ulRet = DICC_Sync(ulFileId, ulLineNum, ulPid, enCpuId);
    if (DICC_OK != ulRet)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, ulRet);

        VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

        return ulRet;
    }

    /* �ڴ˽��û�������¼���� */
    stInitChanInfo.enServiceType = enServiceType;
    VOS_MemCpy(&(stInitChanInfo.stInitPara),
               pstInitChanInfo, sizeof(stInitChanInfo.stInitPara));

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, DICC_TRACE_OK);

    ulRet = DICC_ChkChnServiceInfo(enServiceType, pstInitChanInfo, enCpuId);
    if (DICC_OK != ulRet)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, ulRet);

        SET_DICC_SOFT_REBOOT_INFO((&stRebootInfo), TTF_SOFT_REBOOT_MODULE_ID_DICC_CHAN_INIT_FAIL,
            ulFileId, ulLineNum, (&stInitChanInfo), sizeof(stInitChanInfo));
        DICC_DealWithFatalError(&stRebootInfo);

        VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

        return ulRet;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, DICC_TRACE_OK);

    if (DICC_CHAN_ROLE_SENDER == pstInitChanInfo->enUserRole)
    {
        ulRet = DICC_SenderChnInit(ulPid, g_astChanRole[enCpuId].aenSender[enServiceType],
                                   &(pstInitChanInfo->u.stSndInitInfo.stSndChnInfo),
                                   &(stInitChanInfo.stLocalSemPara), enCpuId);
        if (DICC_OK != ulRet)
        {
            SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
                ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, ulRet);

            SET_DICC_SOFT_REBOOT_INFO((&stRebootInfo), TTF_SOFT_REBOOT_MODULE_ID_DICC_CHAN_INIT_FAIL,
                ulFileId, ulLineNum, (&stInitChanInfo), sizeof(stInitChanInfo));
            DICC_DealWithFatalError(&stRebootInfo);

            VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

            return ulRet;
        }
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, DICC_TRACE_OK);

    if (DICC_CHAN_ROLE_RECVER == pstInitChanInfo->enUserRole)
    {
/*lint -e64*/
        ulRet = DICC_RecverChnInit(ulPid, enServiceType,
                                   (VOIDFUNCPTR)(pstInitChanInfo->u.stRcvInitInfo.pfuncRecvIsr),
                                   &(stInitChanInfo.stIntOp),
                                   &(stInitChanInfo.stLocalSemPara), enCpuId);
/*lint +e64*/
        if (DICC_OK != ulRet)
        {
            SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
                ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, ulRet);

            SET_DICC_SOFT_REBOOT_INFO((&stRebootInfo), TTF_SOFT_REBOOT_MODULE_ID_DICC_CHAN_INIT_FAIL,
                ulFileId, ulLineNum, (&stInitChanInfo), sizeof(stInitChanInfo));
            DICC_DealWithFatalError(&stRebootInfo);

            VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

            return ulRet;
        }
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT, __LINE__, DICC_TRACE_OK);

    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    return DICC_OK;
}    /* DICC_SingleChnInit */

/*****************************************************************************
�� �� ��  : DICC_OpenChannelByRole
��������  : ���ս�ɫ�򿪺˼�ͨ��ͨ��
�������  : ucChanId - ͨ��ID
            enUserRole - �ڵ�ǰCPU�ϱ�����ͨ���ϰ��ݵĽ�ɫ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��8��11��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_OpenChannelByRole(DICC_CHAN_ID_ENUM_UINT8      ucChnId,
                                DICC_CHAN_ROLE_ENUM_UINT8      enUserRole,
                                VOS_UINT32                     ulPid,
                                DICC_CHAN_LOCAL_SEM_PAPA_STRU *pstLocalSemPara,
                                DICC_CPU_ID_ENUM_UINT8         enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU   *pstDiccChnCtrl = VOS_NULL_PTR;
    VOS_UINT8                       ucStateMask    = DICC_CHAN_BOTH_CLOSE_MASK;

    if (DICC_CHAN_ROLE_SENDER == enUserRole)
    {
        ucStateMask = DICC_CHAN_SENDER_OPEN_MASK;
    }

    if (DICC_CHAN_ROLE_RECVER == enUserRole)
    {
        ucStateMask = DICC_CHAN_RECVER_OPEN_MASK;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_TRACE_OK);

    /* ������ռ������, �ɱ��ػ����ź��������������� */
    pstLocalSemPara->ulResult = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != pstLocalSemPara->ulResult)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_ERR_LOCAL_SEMPHORE_FAIL);

        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_OpenChannelByRole] take g_ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)(pstLocalSemPara->ulResult));

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_TRACE_OK);

    /* �������� */
    DICC_SPIN_LOCK();

    /* ����ͨ���Ų��ҵ��˼����ݹ�����ƽṹ */
    pstDiccChnCtrl               = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);
    pstDiccChnCtrl->ucStateMask |= ucStateMask;

    /* �������� */
    DICC_SPIN_UNLOCK();

    /* �ͷ��ź��� */
    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_TRACE_OK);

    DEBUG_PRINT("DICC_OpenChannelByRole chan-id = %d, pstDiccChnCtrl->ucStateMask = %d\n",
                ucChnId, pstDiccChnCtrl->ucStateMask);

    return DICC_OK;
}    /* DICC_SenderOpenChannel */

/*****************************************************************************
�� �� ��  : DICC_CheckChanOpPara
��������  : ���ͨ�������Ļ�������
�������  : ucChanId - ͨ��ID
�������  : ��
�� �� ֵ  : ���Ϸ����, DICC_OK - �Ϸ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��15��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_CheckChanOpPara(DICC_CHAN_ID_ENUM_UINT8 ucChnId,
               DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    if (VOS_NULL_PTR == g_astChanRole[enCpuId].pastDICCMgmt)
    {
        DICC_LOG(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckChanOpPara] get g_pastDICCMgmt NULL ");
        return DICC_ERR_CHAN_NOT_READY;
    }

    if (DICC_CHAN_ID_BUTT <= ucChnId)
    {
        DICC_LOG1(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckChanOpPara] undefined <ucChnId> ",
            ucChnId);
        return DICC_ERR_INVALID_CHAN_ID;
    }

    /* �����pstDiccChnCtrl->ucValidFlag, ��ֹ�ⲿʹ�����쳣ʱ, ������ */

    return DICC_OK;
}    /* DICC_CheckChanOpPara */

/*****************************************************************************
�� �� ��  : DICC_CheckOpenPara
��������  : ���ͨ�������Ĳ���
�������  : ucChanId - ͨ��ID
            enUserRole - �ڵ�ǰCPU�ϱ�����ͨ���ϰ��ݵĽ�ɫ
�������  : ��
�� �� ֵ  : ���Ϸ����, DICC_OK - �Ϸ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��15��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_CheckOpenPara(DICC_CHAN_ID_ENUM_UINT8   ucChnId,
                              DICC_CHAN_ROLE_ENUM_UINT8 enUserRole,
                              VOS_UINT32                ulPid,
                              DICC_CPU_ID_ENUM_UINT8    enCpuId)
{
    DICC_CHAN_ID_ENUM_UINT8      *penRole     = VOS_NULL_PTR;
    volatile DICC_CHAN_CTRL_STRU *pstDiccChnCtrl;
    VOS_UINT8                     ucStateMask = DICC_CHAN_BOTH_CLOSE_MASK;
    VOS_UINT32                    ulRet;

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if (DICC_CHAN_ROLE_SENDER == enUserRole)
    {
        penRole = (DICC_CHAN_ID_ENUM_UINT8 *)g_astChanRole[enCpuId].aenSender;
        ucStateMask |= DICC_CHAN_SENDER_OPEN_MASK;
    }
    else if (DICC_CHAN_ROLE_RECVER == enUserRole)
    {
        penRole = (DICC_CHAN_ID_ENUM_UINT8 *)g_astChanRole[enCpuId].aenRecver;
        ucStateMask |= DICC_CHAN_RECVER_OPEN_MASK;
    }
    else
    {
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    if ((ucChnId != penRole[DICC_SERVICE_TYPE_0]) && (ucChnId != penRole[DICC_SERVICE_TYPE_1]))
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckOpenPara] <ucChnId> <enUserRole> not match ",
            ucChnId, enUserRole);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    DEBUG_PRINT("DICC_OpenChannel enUserRole=%d, ucChnId=%d, penRole[DICC_SERVICE_TYPE_0]=%d, penRole[DICC_SERVICE_TYPE_1]=%d\n",
                enUserRole, ucChnId, penRole[DICC_SERVICE_TYPE_0], penRole[DICC_SERVICE_TYPE_1]);

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_TRACE_OK);

    /* ����ͨ���Ų��ҵ��˼����ݹ�����ƽṹ  */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* �жϱ����Ƿ��Ѿ��� */
    if (ucStateMask == (ucStateMask & pstDiccChnCtrl->ucStateMask))
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_ERR_CHAN_ALREADY_OPENED);

        DICC_LOG1(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckOpenPara] <ucChnId> already opened ",
            ucChnId);
        return DICC_ERR_CHAN_ALREADY_OPENED;
    }

    return DICC_OK;
}    /* DICC_CheckOpenPara */

/*****************************************************************************
�� �� ��  : DICC_OpenChannel
��������  : �򿪺˼�ͨ��ͨ��API
�������  : ulPid - ���ô˽ӿڵ�PID
            ucChanId - ͨ��ID
            enUserRole - �ڵ�ǰCPU�ϱ�����ͨ���ϰ��ݵĽ�ɫ
�������  : ��
�� �� ֵ  : �����ɹ����, VOS_OK - �ɹ�, VOS_ERR - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��8��11��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_OpenChannel(VOS_UINT32 ulPid, DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                            DICC_CHAN_ROLE_ENUM_UINT8 enUserRole,
                            DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT32                          ulRet;
    DICC_CHAN_OPEN_PAPA_STRU            stOpenPara = {0};


    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* ע���ڴ�֮ǰ, �޷�ȷ��enCpuId�Ƿ�����, ֱ���������±���ܻ��������, �ʲ��ܵ���TRACE */
    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_TRACE_OK);

    ulRet = DICC_CheckOpenPara(ucChnId, enUserRole, ulPid, enCpuId);

    /* ������� */
    stOpenPara.ucChnId    = ucChnId;
    stOpenPara.enUserRole = enUserRole;

    if (DICC_OK != ulRet)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, ulRet);

        return ulRet;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, DICC_TRACE_OK);

    ulRet = DICC_OpenChannelByRole(ucChnId, enUserRole, ulPid,
                &(stOpenPara.stLocalSemPara), enCpuId);

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_OPEN, __LINE__, ulRet);

    return ulRet;
}    /* DICC_SenderOpenChannel */

/*****************************************************************************
�� �� ��  : DICC_CloseChannel
��������  : �رպ˼�ͨ��ͨ��API
�������  : ulPid - ���ô˽ӿڵ�PID
            ucChanId - ͨ��ID
�������  : ��
�� �� ֵ  : �����ɹ����, VOS_OK - �ɹ�, VOS_ERR - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��8��11��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_CloseChannel(VOS_UINT32 ulPid, DICC_CHAN_ID_ENUM_UINT8 ucChnId,
               DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU       *pstDiccChnCtrl = VOS_NULL_PTR;
    DICC_CHAN_ROLE_ENUM_UINT8           enUserRole = DICC_CHAN_ROLE_BUTT;
    VOS_UINT32                          ulRet;
    DICC_CHAN_CLOSE_PAPA_STRU           stClosePara = {0};
    VOS_UINT32                          ulCnt;
    DICC_CHAN_CLOSE_FLUSH_EVENT_STRU    stEvent;
    PS_BOOL_ENUM_UINT8                  enFlushData = PS_FALSE;

    /* ������� */
    stClosePara.ucChnId = ucChnId;

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* ע���ڴ�֮ǰ, �޷�ȷ��enCpuId�Ƿ�����, ֱ���������±���ܻ��������, �ʲ��ܵ���TRACE */
    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_TRACE_OK);

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);

    if (DICC_OK != ulRet)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, ulRet);

        return ulRet;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_TRACE_OK);

    /* ����ͨ���Ų��ҵ��˼����ݹ�����ƽṹ */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);
    enUserRole = g_astChanRole[enCpuId].aenRole[ucChnId];

    /* ������ռ������, �ɱ��ػ����ź��������������� */
    stClosePara.stLocalSemPara.ulResult = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != stClosePara.stLocalSemPara.ulResult)
    {
        SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
            ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_ERR_LOCAL_SEMPHORE_FAIL);

        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_CloseChannel] take g_ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)(stClosePara.stLocalSemPara.ulResult));

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_TRACE_OK);

    /* �������� */
    DICC_SPIN_LOCK();

    if (DICC_CHAN_ROLE_SENDER == enUserRole)
    {
        /* ���ñ���Ϊ�ر�״̬ */
        pstDiccChnCtrl->ucStateMask &= ~DICC_CHAN_SENDER_OPEN_MASK;
    }

    if (DICC_CHAN_ROLE_RECVER == enUserRole)
    {
        if (DICC_CHAN_SENDER_OPEN_MASK == (DICC_CHAN_SENDER_OPEN_MASK & pstDiccChnCtrl->ucStateMask))
        {
            /* �������� */
            DICC_SPIN_UNLOCK();

            /* �ͷ��ź��� */
            VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

            SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
                ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_ERR_CLOSE_BEFORE_SENDER_CLOSED);

            DICC_LOG2(PS_PRINT_WARNING,
                "[<LOCAL CPU_ID>: DICC_CloseChannel] receiver close channel before sender ",
            enCpuId, (VOS_INT32)(stClosePara.stLocalSemPara.ulResult));

            return DICC_ERR_CLOSE_BEFORE_SENDER_CLOSED;
        }

        /* ���ñ���Ϊ�ر�״̬ */
        pstDiccChnCtrl->ucStateMask &= ~DICC_CHAN_RECVER_OPEN_MASK;
    }

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_TRACE_OK);

    ulCnt = 0;
    /* ͨ��״̬Ϊ���˹ر� */
    if (DICC_CHAN_BOTH_CLOSE_MASK == pstDiccChnCtrl->ucStateMask)
    {
        ulCnt = DICC_GetChannelCurrDataCnt(ulPid, ucChnId, enCpuId);
        if ((0 < ulCnt) && (DICC_INVALID_VALUE != ulCnt))
        {
            enFlushData = PS_TRUE;
        }
        /* ����βָ����� */
        TTF_RING_Q_Flush(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
    }

    /* �������� */
    DICC_SPIN_UNLOCK();

    /* �ͷ��ź��� */
    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    SET_DICC_TRACE_INFO_RECORD(&g_stDiccTraceInfo[enCpuId], enCpuId, ulPid,
        ID_DICC_TRACE_FUNC_MARK_CLOSE, __LINE__, DICC_TRACE_OK);

    if (PS_TRUE == enFlushData)
    {
        stEvent.ulOpPid    = ulPid;
        stEvent.ucFlushCnt = (VOS_UINT8)ulCnt;
        stEvent.ucChnId    = ucChnId;
        DICC_SndEvent(ID_DICC_MNTN_CLOSE_FLUSH_EVENT, &stEvent, sizeof(stEvent), enCpuId);
    }

    DEBUG_PRINT("DICC_CloseChannel MASK State : %d", pstDiccChnCtrl->ucStateMask );

    return DICC_OK;
}    /* DICC_CloseChannel */

/*****************************************************************************
�� �� ��  : DICC_CheckTrigPara
��������  : ��鴥���˼��жϲ����Ĳ���
�������  : ucChanId - ͨ��ID
�������  : ��
�� �� ֵ  : ���Ϸ����, DICC_OK - �Ϸ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��15��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_CheckTrigPara(DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                              DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT32 ulRet;

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if ((ucChnId != g_astChanRole[enCpuId].aenSender[DICC_SERVICE_TYPE_0])
        && (ucChnId != g_astChanRole[enCpuId].aenSender[DICC_SERVICE_TYPE_1]))
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckTrigPara] <ucChnId> <enUserRole> not match ",
            ucChnId, DICC_CHAN_ROLE_SENDER);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    return DICC_OK;
}    /* DICC_CheckTrigPara */

/*****************************************************************************
�� �� ��  : DICC_TriggerChanDataTx
��������  : �����˼�ͨ���ж�API
            �����˼�ͨ���ж�, ��֪��Զ˽��մ��ݵ���Ϣ
�������  : ulPid  - ���ô˽ӿڵ�PID
            ucChanId - ͨ��ID
�������  : ��
�� �� ֵ  : �����ɹ����, VOS_OK - �ɹ�, VOS_ERR - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��15��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_TriggerChanDataTx(VOS_UINT32 ulPid,
               DICC_CHAN_ID_ENUM_UINT8 ucChnId, DICC_CPU_ID_ENUM_UINT8 enCurrCpuId)
{
    VOS_UINT32                     ulDiccIsrIntLev;
    VOS_INT32                      lIsrRet;    /* �жϲ�������ֵ */
#if (1 == DICC_DFX_SWITCH)
    DICC_DFX_STRU                 *pstDFx;
#endif
    VOS_UINT32                     ulRet;
    IPC_INT_CORE_E                 enDstCore;

    ulRet = DICC_CheckCpuId(enCurrCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DICC_CheckTrigPara(ucChnId, enCurrCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* ����ͨ��ID��ȡ�˼�ͨ���жϺ� */
    if (ucChnId == g_astChanRole[enCurrCpuId].aenSender[DICC_SERVICE_TYPE_0])
    {
        ulDiccIsrIntLev = DICC_SERVICE_0_INT_LEVEL;
    }
    else
    {
        ulDiccIsrIntLev = DICC_SERVICE_1_INT_LEVEL;
    }

#if (1 == DICC_DFX_SWITCH)
    /* �����жϴ���++ */
    pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCurrCpuId].pastDICCMgmt);
    (pstDFx->astChanStatus[ucChnId].stStatistics.ulTrigIsrCnt)++;
    pstDFx->astChanStatus[ucChnId].stStatistics.ulTrigIsrPid = ulPid;
    pstDFx->astChanStatus[ucChnId].stStatistics.ulLastTrigIsrTime = mdrv_timer_get_normal_timestamp();
#endif

#ifndef WTTF_PS_FUSION_PC_ST
    /* �����˼����ݴ����ж�֪ͨ�Է�CPU */
    if (DICC_CPU_ID_CCPU == enCurrCpuId)
    {
        enDstCore = IPC_CORE_APPARM;
        lIsrRet = mdrv_ipc_int_send(enDstCore, (IPC_INT_LEV_E)ulDiccIsrIntLev);
    }
    else
    {
        enDstCore = IPC_CORE_COMARM;
        lIsrRet = mdrv_ipc_int_send(enDstCore, (IPC_INT_LEV_E)ulDiccIsrIntLev);
    }
#else
    if (DICC_CPU_ID_CCPU == enCurrCpuId)
    {
        enDstCore = IPC_CORE_APPARM;
        lIsrRet = VHW_IPC_IntSend(enDstCore, (IPC_INT_LEV_E)ulDiccIsrIntLev);
    }
    else
    {
        enDstCore = IPC_CORE_COMARM;
        lIsrRet = VHW_IPC_IntSend(enDstCore, (IPC_INT_LEV_E)ulDiccIsrIntLev);
    }
#endif

    if (lIsrRet != VOS_OK)
    {
        DICC_LOG3(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_TriggerChanDataTx] <ucChnId> <enDstCore> <ulDiccIsrIntLev> trigger Isr fail ",
            ucChnId, enDstCore, (VOS_INT32)ulDiccIsrIntLev);

        return DICC_ERR_TRIG_ISR_FAIL;
    }

    return DICC_OK;
}    /* DICC_TriggerChanDataTx */

/*****************************************************************************
�� �� ��  : DICC_TimeDiff
��������  : ��������ʱ�̵�ʱ���
�������  : ulTimeStart  - ��ʼʱ��
            ulTimeEnd - ����ʱ��
�������  : ��
�� �� ֵ  : ʱ���
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��14��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_TimeDiff(VOS_UINT32 ulTimeStart, VOS_UINT32 ulTimeEnd)
{
    VOS_UINT32 ulTimeDiff;

    if (ulTimeEnd < ulTimeStart)
    {
        ulTimeDiff = ulTimeStart - ulTimeEnd;
    }
    else
    {
        /* ��ʱ��������Ϊ������: 0xFFFFFFFF��ulTimeEnd֮��, ulTimeStart��0֮��
           ǰ��Ϊ(PS_NULL_UINT32 - ulTimeEnd + 1) ��1��ԭ��:slice=PS_NULL_UINT32����Ҳ��Ҫ����,
           ����Ϊ(ulCurrTime - 0 ) slice=0�Ѿ��������� */
        ulTimeDiff = (PS_NULL_UINT32 - ulTimeEnd + 1) + ( ulTimeStart - 0);
    }

    return ulTimeDiff;
}    /* DICC_TimeDiff */
#if 0
/*****************************************************************************
�� �� ��  : DICC_ChanStayInFullState
��������  : ��������������
�������  : ulPid - ���ô˽ӿڵ�PID
            pstDiccChnCtrl - ͨ���Ŀ������ݽṹ��ʼ��ַ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��14��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DICC_ChanStayInFullState(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum,
                                  VOS_UINT32 ulPid,
                                  volatile DICC_CHAN_CTRL_STRU *pstDiccChnCtrl,
                                  DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT8                    ucTraceBlkCnt;
    VOS_UINT32                   ulTraceBlkLoop;
    DICC_QUEUE_NODE_STRU        *pstQueueNode;
    DICC_DFX_STRU               *pstDFx;
    DICC_TRACE_QUEUE_STRU       *pstTraceQueue;
    DICC_TRACE_QUEUE_DATA_STRU  *pstQueueData;
    DICC_CHAN_EXECPTION_STRU    *pstDiccExcp;

    pstDiccExcp = VOS_MemAlloc(ulPid, (STATIC_MEM_PT), sizeof(DICC_CHAN_EXECPTION_STRU));

    if (VOS_NULL_PTR != pstDiccExcp)
    {
        pstTraceQueue = &(pstDiccExcp->stTraceQueue);
        pstTraceQueue->ucChanId = pstDiccChnCtrl->ucChanId;
        ucTraceBlkCnt = (VOS_UINT8)TTF_MIN(pstDiccChnCtrl->usChnBlkNum, DICC_MAX_TRACE_QUEUE_DATA_CNT);
        pstTraceQueue->ucDataCnt = ucTraceBlkCnt;

        /* ��ͨ������ǰ���10�������Ѽ����� */
        for (ulTraceBlkLoop = 0; ulTraceBlkLoop < ucTraceBlkCnt; ulTraceBlkLoop++)
        {
            pstQueueNode = (DICC_QUEUE_NODE_STRU*)TTF_RING_Q_Out(ulPid,
                                                                 (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
            pstQueueData = &(pstTraceQueue->astQueueData[ulTraceBlkLoop]);
            pstQueueData->ulInsertTime = pstQueueNode->ulInsertTime;
            pstQueueData->ucPriDataLen = pstQueueNode->ucPriDataLen;
            VOS_MemCpy(pstQueueData->aucPriData, pstQueueNode->aucPriData, pstQueueNode->ucPriDataLen);
        }

        /* �������ͨ����״̬��Ϣ���� */
        pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);
        VOS_MemCpy(&(pstDiccExcp->stIsrDbg), &(pstDFx->stIsrDbg), sizeof(pstDiccExcp->stIsrDbg));
        VOS_MemCpy(&(pstDiccExcp->stChanStatus), &(pstDFx->astChanStatus[pstTraceQueue->ucChanId]),
                   sizeof(pstDiccExcp->stChanStatus));

        /* ����OM API���е��帴λ */
        VOS_ProtectionReboot(TTF_SOFT_REBOOT_MODULE_ID_DICC_CHAN_ALWAYS_FULL,
            (VOS_INT)ulFileId, (VOS_INT)ulLineNum, (VOS_CHAR *)(pstDiccExcp),
            sizeof(DICC_CHAN_EXECPTION_STRU) );

        VOS_MemFree(ulPid, pstDiccExcp);
    }

    return;
}    /* DICC_ChanStayInFullState */
#endif
/*****************************************************************************
�� �� ��  : DICC_CheckInsertPara
��������  : ���������ݲ����Ĳ���
�������  : ucChanId - ͨ��ID
            pstDscpBlk - �˼䴫�������ֶ�
�������  : ��
�� �� ֵ  : ���Ϸ����, DICC_OK - �Ϸ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��15��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_CheckInsertPara(DICC_CHAN_ID_ENUM_UINT8    ucChnId,
                                DICC_INSERT_DSCP_BLK_STRU *pstDscpBlk,
                                DICC_CPU_ID_ENUM_UINT8     enCpuId)
{
    VOS_UINT32                           ulRet;
    volatile DICC_CHAN_CTRL_STRU        *pstDiccChnCtrl = VOS_NULL_PTR;

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if ((ucChnId != g_astChanRole[enCpuId].aenSender[DICC_SERVICE_TYPE_0])
        && (ucChnId != g_astChanRole[enCpuId].aenSender[DICC_SERVICE_TYPE_1]))
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> <enRole> not match ",
            enCpuId, ucChnId, DICC_CHAN_ROLE_SENDER);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    if (VOS_NULL_PTR == pstDscpBlk)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> pstDscpBlk is NULL ",
            enCpuId, ucChnId);
        return DICC_ERR_INSERT_DESP_BLK_PTR_NULL;
    }

    if (VOS_NULL_PTR == pstDscpBlk->pucUserData)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> pstDscpBlk->pucUserData is NULL ",
            enCpuId, ucChnId);
        return DICC_ERR_INSERT_DESP_BLK_DATA_NULL;
    }

    /* ����ͨ���Ų��ҵ��˼����ݹ�����ƽṹ */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    if (pstDiccChnCtrl->ucPriDataLen < (VOS_UINT16)(pstDscpBlk->ucDataLen))
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> <pstDscpBlk->ucDataLen> size error ",
            enCpuId, ucChnId, (pstDscpBlk->ucDataLen));
        return DICC_ERR_DLV_DATA_BLK_SIZE;
    }

    /* ���ﲻ��Ҫ����, ��ͬһ�˶���, ֻҪ�������˶���, ���ܲ���;
       ��һ����mask���޷���sender��û�йر�ǰ, recver���޷��ر� */
    if (DICC_CHAN_BOTH_OPEN_MASK != pstDiccChnCtrl->ucStateMask)
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> is not all open, <mask> ",
            enCpuId, ucChnId, (pstDiccChnCtrl->ucStateMask));
        return DICC_ERR_CHAN_NOT_OPEN_IN_BOTH_SIDES;
    }

    return DICC_OK;
}

/*****************************************************************************
�� �� ��  : DICC_InsertChannelDataAction
��������  : �������ݵ���Ϣ����ת�Ƶ��˼�API
            ���������ṹ��enAutoTrigTx��Ϊ0ʱ, ���ᴥ��������Ϊ,
            ��ʱ��Ҫ�ɷ��Ͷ�����������DICC_TriggerChanDataTx����;
            ֻ����ͨ���򿪺�, ��Ϣ�Ż��������ݵ��Զ�
            ���Ͷ˺ͽ��ն�����һ��δ��, ��˼�ת�ƴ����ݵ���Ϣ���ݲ���ʧ��
�������  : ucChanId - ͨ��ID
            pstDscpBlk - �˼䴫�������ֶ�
�������  : ��
�� �� ֵ  : �����ɹ����, VOS_OK - �ɹ�, VOS_ERR - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��8��11��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_InsertChannelDataAction(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum,
                                        VOS_UINT32 ulPid, DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                                        DICC_INSERT_DSCP_BLK_STRU *pstDscpBlk,
                                        DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU        *pstDiccChnCtrl = VOS_NULL_PTR;
    volatile DICC_QUEUE_NODE_STRU       *pstQueueNode = VOS_NULL_PTR;
    VOS_UINT32                           ulIsQFull;
    VOS_UINT32                           ulCurrTime;
#if 0
    VOS_UINT32                           ulFirstInsertTime;
    VOS_UINT32                           ulTimeDiff;
#endif
    DICC_DFX_STRU                       *pstDFx;
    VOS_UINT32                           ulRet;
    DICC_CHAN_INSERT_PAPA_STRU           stInsertPara = {0};
    VOS_UINT32                           ulTemp;
    DICC_CHAN_QUEUE_FULL_EVENT_STRU      stQueueFullEvent;


    DEBUG_PRINT("DICC_InsertChannelData entered ChnId: %d.\n", ucChnId);

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DICC_CheckInsertPara(ucChnId, pstDscpBlk, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* �ɹ�ʱ��¼�û����� */
    stInsertPara.ucChnId = ucChnId;
    stInsertPara.enChanInitFlag = PS_TRUE;
    stInsertPara.ucChanStateMask = DICC_CHAN_BOTH_OPEN_MASK;
    VOS_MemCpy(&(stInsertPara.stDscpBlk), pstDscpBlk, sizeof((stInsertPara.stDscpBlk)));

    /* �ɱ��ػ����ź�����ʵ�ֱ��˸�API������ */
    stInsertPara.stLocalSemPara.ulResult = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != stInsertPara.stLocalSemPara.ulResult)
    {
        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_InsertChannelDataAction] take ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)(stInsertPara.stLocalSemPara.ulResult));

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    ulCurrTime = mdrv_timer_get_normal_timestamp();    /* ��ȡ��ǰʱ�� */

    /* ����ͨ���Ų��ҵ��˼����ݹ�����ƽṹ */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);
    ulIsQFull = TTF_RING_Q_IsFull(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));

    if (PS_TRUE != ulIsQFull)    /* ���в��� */
    {
        /* ��ȡ�˼䴫�ݽ�� */
        pstQueueNode = (DICC_QUEUE_NODE_STRU*)TTF_RING_Q_Rear(ulPid,
            (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
        if (VOS_NULL_PTR == pstQueueNode)
        {
            /* �ͷ��ź��� */
            VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

            DICC_LOG(PS_PRINT_WARNING,
                "[<LOCAL CPU_ID>: DICC_InsertChannelDataAction] Get the node fail ");
            return DICC_ERR_GET_NODE_FAIL;
        }

        /* ���ݴ���ʱ�� */
        pstQueueNode->ulInsertTime = ulCurrTime;

        /* ���������ֶ�����, ����ulConsecutiveQueueFullCnt���� */
        pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);
        pstDFx->astChanStatus[ucChnId].stStatistics.ulConsecutiveQueueFullCnt = 0;

        /* ��������˼䴫�ݽ�� */
        VOS_MemCpy((VOS_UINT8 *)pstQueueNode->aucPriData, pstDscpBlk->pucUserData, pstDscpBlk->ucDataLen);
        pstQueueNode->ucPriDataLen = pstDscpBlk->ucDataLen;

#if (1 == DICC_DFX_SWITCH)
        /* �������++ */
        (pstDFx->astChanStatus[ucChnId].stStatistics.ulInsertCnt)++;
        pstDFx->astChanStatus[ucChnId].stStatistics.ulInsertPid      = ulPid;
        pstDFx->astChanStatus[ucChnId].stStatistics.ulLastInsertTime = ulCurrTime;
#endif

        DICC_PrintDebugData((VOS_VOID *)(pstQueueNode->aucPriData), pstQueueNode->ucPriDataLen);

        /* ��˼������Ϣ���� */
        TTF_RING_Q_In(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));

        if (PS_TRUE == pstDscpBlk->enAutoTrigTx)
        {
            DICC_TriggerChanDataTx(ulPid, ucChnId, enCpuId);
        }
    }
    else
    {
        pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);
        (pstDFx->astChanStatus[ucChnId].stStatistics.ulConsecutiveQueueFullCnt)++;
        (pstDFx->astChanStatus[ucChnId].stStatistics.ulQueueFullCnt)++;
        ulTemp = pstDFx->astChanStatus[ucChnId].stStatistics.ulConsecutiveQueueFullCnt % DICC_CHAN_QUEUE_FULL_REPORT_TIMES;
        if (0 == ulTemp)
        {
            /* �����¼� */
            stQueueFullEvent.ulOpPid        = ulPid;
            stQueueFullEvent.ucChnId        = ucChnId;
            stQueueFullEvent.ulQueueFullCnt = pstDFx->astChanStatus[ucChnId].stStatistics.ulQueueFullCnt;

            DICC_SndEvent(ID_DICC_MNTN_QUEUE_FULL_EVENT, &stQueueFullEvent, sizeof(stQueueFullEvent), enCpuId);

            /* �ϱ���Ϣ��, ��ulConsecutiveQueueFullCnt���� */
            pstDFx->astChanStatus[ucChnId].stStatistics.ulConsecutiveQueueFullCnt = 0;
        }

/* ��Ϊ�Ե��������λ, ����ֻ��exec.bin�м�¼������λ�ĺ��ϵ�CPU�켣�Լ�ջ����Ϣ,
   ������һ����, û�м�ʱ��¼��Ϣ, �����λ��, ���޷�֪������״��, �����ڶ�λ,
   ����ʼ�����������Ϊ�ϱ��¼������ִ˳��� */
#if 0
        pstQueueNode = (DICC_QUEUE_NODE_STRU*)TTF_RING_Q_Front(ulPid,
            (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));

        /* ȡ���׽���ʱ�� */
        ulFirstInsertTime = pstQueueNode->ulInsertTime;

        ulTimeDiff = DICC_TimeDiff(ulFirstInsertTime, ulCurrTime);
        if (DICC_CHAN_QUEUE_FULL_TIME <= ulTimeDiff)    /* ���׽�����ʱ�����Ѿ�����1s */
        {
            /* ��ͨ������ǰ���10�������Ѽ�����, ����OM API���е��帴λ */
            DICC_ChanStayInFullState(ulFileId, ulLineNum, ulPid, pstDiccChnCtrl, enCpuId);
        }
#endif

        /* �ͷ��ź��� */
        VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

        return DICC_ERR_CHAN_FULL;
    }

    /* �ͷ��ź��� */
    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    return DICC_OK;
}    /* DICC_InsertChannelData */

/*****************************************************************************
�� �� ��  : DICC_CheckRemovePara
��������  : ���ȡ�����ݲ����Ĳ���
�������  : ucChanId - ͨ��ID
            pucUsrData - �Ӻ˼�ȡ�������ݿ�������, �ⲿʹ���߱�ָ֤��ǿ�
�������  : ��
�� �� ֵ  : ���Ϸ����, DICC_OK - �Ϸ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��15��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_CheckRemovePara(DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                                VOS_UINT8              *pucUsrData,
                                DICC_CPU_ID_ENUM_UINT8  enCpuId)
{
    VOS_UINT32 ulRet;

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if ((ucChnId != g_astChanRole[enCpuId].aenRecver[DICC_SERVICE_TYPE_0])
        && (ucChnId != g_astChanRole[enCpuId].aenRecver[DICC_SERVICE_TYPE_1]))
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckRemovePara] <ucChnId> <enUserRole> not match ",
            enCpuId, ucChnId, DICC_CHAN_ROLE_RECVER);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    if (VOS_NULL_PTR == pucUsrData)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckRemovePara] <ucChnId> pucUsrData is NULL ",
            enCpuId, ucChnId);
        return DICC_ERR_REMOVE_DATA_PTR_NULL;
    }

    return DICC_OK;
}

/*****************************************************************************
�� �� ��  : DICC_RemoveChannelData
��������  : �����ݵ���Ϣ�Ӻ˼价�ι�������ȡ��API
�������  : ulPid - ���ô˽ӿڵ�PID
            ucChanId - ͨ��ID
            pucUsrData - �Ӻ˼�ȡ�������ݿ�������, �ⲿʹ���߱�ָ֤��ǿ�
�������  : ��
�� �� ֵ  : �����ɹ����, DICC_OK - �ɹ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��8��11��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_RemoveChannelData(VOS_UINT32              ulPid,
                                  DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                                  VOS_UINT8              *pucUsrData,
                                  DICC_CPU_ID_ENUM_UINT8  enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU             *pstDiccChnCtrl = VOS_NULL_PTR;
    volatile DICC_QUEUE_NODE_STRU            *pstQueueNode   = VOS_NULL_PTR;
#if (1 == DICC_DFX_SWITCH)
    DICC_DFX_STRU                            *pstDFx;
#endif
    VOS_UINT32                                ulRet;
    DICC_CHAN_MAGIC_NUM_CHANGED_EVENT_STRU    stMagicEvent;
    DICC_CHAN_REMOVE_PAPA_STRU                stRemovePara = {0};

    DEBUG_PRINT("DICC_RemoveChannelData entered! \n");

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DICC_CheckRemovePara(ucChnId, pucUsrData, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* ����ͨ���Ų��ҵ��˼����ݹ�����ƽṹ */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* �ɹ����¼�û��������� */
    stRemovePara.ucChnId          = ucChnId;
    stRemovePara.enChanInitFlag   = PS_TRUE;
    stRemovePara.ucChanStateMask  = pstDiccChnCtrl->ucStateMask;
    stRemovePara.ucFlushData      = 0;
    stRemovePara.pucToSaveUsrData = pucUsrData;

    /* �ɱ��ػ����ź�����ʵ�ֱ��˸�API������ */
    stRemovePara.stLocalSemPara.ulResult = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != stRemovePara.stLocalSemPara.ulResult)
    {
        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_InsertChannelDataAction] take ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)(stRemovePara.stLocalSemPara.ulResult));

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    /* ���ն�û�йر�, ����Լ���ȡ�� */
    if (DICC_CHAN_RECVER_OPEN_MASK == (DICC_CHAN_RECVER_OPEN_MASK & pstDiccChnCtrl->ucStateMask))
    {
        if (0 != TTF_RING_Q_GetCnt(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer))))
        {
            /* ��ȡ��һ���˼䴫�ݽ�� */
            pstQueueNode = (DICC_QUEUE_NODE_STRU*)TTF_RING_Q_Out(ulPid,
                (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));

            if (VOS_NULL_PTR == pstQueueNode)
            {
                /* �ͷ��ź��� */
                VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

                DICC_LOG(PS_PRINT_WARNING,
                    "[<LOCAL CPU_ID>: DICC_RemoveChannelData] Get the node fail ");
                return DICC_ERR_GET_NODE_FAIL;
            }

#if (1 == DICC_DFX_SWITCH)
            /* ȡ������++ */
            pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);
            (pstDFx->astChanStatus[ucChnId].stStatistics.ulRemoveCnt)++;
            pstDFx->astChanStatus[ucChnId].stStatistics.ulRemovePid = ulPid;
            pstDFx->astChanStatus[ucChnId].stStatistics.ulLastRemoveTime = mdrv_timer_get_normal_timestamp();
#endif

            DEBUG_PRINT("pstQueueNode:0x%x pstQueueNode->aucPriData:0x%x\n",
                        (unsigned int)pstQueueNode, (unsigned int)pstQueueNode->aucPriData);

            if (DICC_MAGIC_NUM_VALUE != pstQueueNode->usMagicNum)
            {
                /* �ͷ��ź��� */
                VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

                /* �����¼� */
                stMagicEvent.ulOpPid    = ulPid;
                stMagicEvent.ucChnId    = ucChnId;
                PS_MEM_CPY(&(stMagicEvent.stQueueNode), (VOS_UINT8*)pstQueueNode, sizeof(stMagicEvent.stQueueNode));

                DICC_SndEvent(ID_DICC_MNTN_MAGIC_NUM_CHANGED_EVENT, &stMagicEvent, sizeof(stMagicEvent), enCpuId);

                DICC_LOG2(PS_PRINT_ERROR,
                    "[<LOCAL CPU_ID>: DICC_RemoveChannelData] <ucChnId> find magic num tampered",
                    enCpuId, ucChnId);
                return DICC_ERR_MAGIC_NUM_CHANGED;
            }

            VOS_MemCpy(pucUsrData, (VOS_UINT8 *)pstQueueNode->aucPriData, pstQueueNode->ucPriDataLen);

            DEBUG_PRINT("DICC_RemoveChannelData pstQueueNode->ucPriDataLen = %d:\n", pstQueueNode->ucPriDataLen);
            DEBUG_PRINT("DICC_RemoveChannelData print remove data start:\n");
            DICC_PrintDebugData(pucUsrData, pstQueueNode->ucPriDataLen);

            /* ���ǵ�������Ϣ������ָ��֮��, Ϊ�˰�ȫ, ���������Ϣ */
            VOS_MemSet((VOS_VOID *)pstQueueNode->aucPriData, 0x0, sizeof(pstQueueNode->aucPriData));
        }
    }

    /* �ͷ��ź��� */
    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    return DICC_OK;
}    /* DICC_RemoveChannelData */


VOS_UINT8 DICC_IsCurrChnOpen(DICC_CHAN_ID_ENUM_UINT8 ucChnId,
              DICC_CPU_ID_ENUM_UINT8           enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU *pstDiccChnCtrl = VOS_NULL_PTR;
    DICC_CHAN_ROLE_ENUM_UINT8     enUserRole = DICC_CHAN_ROLE_BUTT;

    /* ����ͨ���Ų��ҵ��˼����ݹ�����ƽṹ */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    enUserRole = g_astChanRole[enCpuId].aenRole[ucChnId];
    if (DICC_CHAN_ROLE_SENDER == enUserRole)
    {
        if (DICC_CHAN_SENDER_OPEN_MASK == (DICC_CHAN_SENDER_OPEN_MASK & pstDiccChnCtrl->ucStateMask))
        {
            return PS_TRUE;
        }
        else
        {
            return PS_FALSE;
        }
    }
    else if (DICC_CHAN_ROLE_RECVER == enUserRole)
    {
        if (DICC_CHAN_RECVER_OPEN_MASK == (DICC_CHAN_RECVER_OPEN_MASK & pstDiccChnCtrl->ucStateMask))
        {
            return PS_TRUE;
        }
        else
        {
            return PS_FALSE;
        }
    }
    else
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_IsCurrChnOpen] undefined <enUserRole>",
            enCpuId, enUserRole);
        return PS_FALSE;
    }
}
VOS_UINT32 DICC_CheckGetNodeCntPara(DICC_CHAN_ID_ENUM_UINT8          ucChnId,
                                    DICC_GET_CHN_NODE_CNT_ENUM_UINT8 enGetChnNodeCntType,
                                    DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    VOS_UINT32 ulRet;

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if (DICC_GET_CHN_NODE_CNT_BUTT <= enGetChnNodeCntType)
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckGetNodeCntPara] <ucChnId> undefined <enGetChnNodeCntType>",
            enCpuId, ucChnId, enGetChnNodeCntType);
        return DICC_ERR_GET_CNT_TYPE_UNDEFINED;
    }

    return DICC_OK;
}

/*****************************************************************************
�� �� ��  : DICC_GetChannelNodeCnt
��������  : ����ȡͨ�������ݿ����Ĳ���
�������  : ulPid - ���ô˽ӿڵ�PID
            ucChanId - ͨ��ID
            enGetChnNodeCntType - ָʾ��ȡͨ�����Ѿ���ŵ����ݸ���,
                                  ����ͨ���п��Լ�����ŵĸ���
�������  : ��
�� �� ֵ  : �����ɹ����, DICC_OK - �ɹ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��8��11��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_GetChannelNodeCnt(VOS_UINT32                       ulPid,
                                  DICC_CHAN_ID_ENUM_UINT8          ucChnId,
                                  DICC_GET_CHN_NODE_CNT_ENUM_UINT8 enGetChnNodeCntType,
                                  DICC_CPU_ID_ENUM_UINT8           enCpuId)
{
    VOS_UINT32                    ulCurrCnt      = DICC_INVALID_VALUE;
    VOS_UINT32                    ulTmpCnt       = 0;
    volatile DICC_CHAN_CTRL_STRU *pstDiccChnCtrl = VOS_NULL_PTR;
    VOS_UINT32                    ulRet;

    ulRet = DICC_CheckGetNodeCntPara(ucChnId, enGetChnNodeCntType, enCpuId);
    if (DICC_OK != ulRet)
    {
        return DICC_INVALID_VALUE;
    }

    if (PS_TRUE == DICC_IsCurrChnOpen(ucChnId, enCpuId))
    {
        /* ����ͨ���Ų��ҵ��˼����ݹ�����ƽṹ */
        pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

        /* ��ȡͨ���е�ǰ��ŵ���Ϣ���� */
        ulTmpCnt = TTF_RING_Q_GetCnt(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
        if (DICC_GET_CHN_CURR_DATA_CNT == enGetChnNodeCntType)
        {
            ulCurrCnt = ulTmpCnt;
        }
        else
        {
            ulCurrCnt = pstDiccChnCtrl->usChnBlkNum - ulTmpCnt - 1;
        }
    }

    return ulCurrCnt;
}    /* DICC_GetChannelNodeCnt */

#if (VOS_WIN32 != VOS_OS_VER)
/*****************************************************************************
�� �� ��  : DICC_Info
��������  : DICCͨ������ṹ���
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
˵    ��  : �����Ͽɲ��ά����, ֱ��ʹ��vos_printf�򴮿ڴ�ӡ

�޸���ʷ      :
 1.��    ��   : 2011��12��27��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DICC_Info()
{
    volatile DICC_CHAN_CTRL_STRU *pstDiccChnCtrl = VOS_NULL_PTR;
    VOS_UINT8                     ucChanLoop;
    DICC_CPU_ID_ENUM_UINT8        enCpuId;
    volatile DICC_CTRL_STRU      *pastDICCMgmt   = VOS_NULL_PTR;

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    enCpuId = DICC_CPU_ID_CCPU;
#elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    enCpuId = DICC_CPU_ID_ACPU;
#endif

    pastDICCMgmt = g_astChanRole[enCpuId].pastDICCMgmt;

    if (VOS_NULL_PTR == pastDICCMgmt)
    {
        vos_printf("get g_pastDICCMgmt NULL\n");
        return ;
    }
    else
    {
        vos_printf("==============DFx Info============\n");
        vos_printf("CurrSlice:                  0x%x\n", mdrv_timer_get_normal_timestamp());
        vos_printf("ulCurrSize:                 %u\n", pastDICCMgmt->ulCurrSize);
        vos_printf("enDFxEnabled:               %u\n", pastDICCMgmt->stDFx.enDFxEnabled);
        vos_printf("==================================\n");
    }

    for (ucChanLoop = 0; ucChanLoop < DICC_MAX_CHAN_NUM; ucChanLoop++)
    {
        /* ����ͨ���Ų��ҵ��˼����ݹ�����ƽṹ */
        pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChanLoop, enCpuId);
        if (VOS_NULL_PTR != pstDiccChnCtrl)
        {
            vos_printf("===========Chan Ctrl Info=========\n");
            vos_printf("ucChanId:                   %u\n", pstDiccChnCtrl->ucChanId);
            vos_printf("ucStateMask:                0x%x\n", pstDiccChnCtrl->ucStateMask);
            vos_printf("enValidFlag:                %u\n", pstDiccChnCtrl->enValidFlag);
            vos_printf("ucPriDataLen:               %u\n", pstDiccChnCtrl->ucPriDataLen);
            vos_printf("usChnBlkNum:                %u\n", pstDiccChnCtrl->usChnBlkNum);
            vos_printf("ulTtfRingQStAddrOffSet:     %u\n", pstDiccChnCtrl->ulTtfRingQStAddrOffSet);
            vos_printf("ulQueueNodeAddrOffSet:      %u\n", pstDiccChnCtrl->ulQueueNodeAddrOffSet);
            vos_printf("==================================\n");
        }
        else
        {
            vos_printf("get chan addr fail\n");
            vos_printf("==================================\n");
        }
    }

    vos_printf("==============ISR Dbg=============\n");
    vos_printf("ulInvalidDisableOpPid:      %u\n", pastDICCMgmt->stDFx.stIsrDbg.ulInvalidDisableOpPid);
    vos_printf("ulInvalidDisableOpTime:     0x%x\n", pastDICCMgmt->stDFx.stIsrDbg.ulInvalidDisableOpTime);
    vos_printf("ulInvalidEnableOpPid:       %u\n", pastDICCMgmt->stDFx.stIsrDbg.ulInvalidEnableOpPid);
    vos_printf("ulInvalidEnableOpTime:      0x%x\n", pastDICCMgmt->stDFx.stIsrDbg.ulInvalidEnableOpTime);
    vos_printf("==================================\n");

    return;
}

/*****************************************************************************
�� �� ��  : DICC_Chan_Info
��������  : DICCͨ����״���
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
˵    ��  : �����Ͽɲ��ά����, ֱ��ʹ��vos_printf�򴮿ڴ�ӡ

�޸���ʷ      :
 1.��    ��   : 2011��12��27��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DICC_Chan_Info(VOS_INT32 lChanId)
{
    DICC_CPU_ID_ENUM_UINT8                 enCpuId;
    volatile DICC_CTRL_STRU               *pastDICCMgmt   = VOS_NULL_PTR;
    volatile DICC_CHAN_STATISTICS_STRU    *pstStatistics  = VOS_NULL_PTR;
    volatile DICC_ISR_OP_STRU             *pstIsrOp       = VOS_NULL_PTR;
    VOS_UINT8                              ucChanId;

    if ((lChanId >= DICC_CHAN_ID_BUTT) || (lChanId < 0))
    {
        vos_printf("invalid ucChanId\n");
        return ;
    }
    else
    {
        ucChanId = (VOS_UINT8)lChanId;
    }

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    enCpuId = DICC_CPU_ID_CCPU;
#elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    enCpuId = DICC_CPU_ID_ACPU;
#endif

    pastDICCMgmt = g_astChanRole[enCpuId].pastDICCMgmt;

    if (VOS_NULL_PTR == pastDICCMgmt)
    {
        vos_printf("get g_pastDICCMgmt NULL\n");
        return ;
    }

    if (PS_FALSE == pastDICCMgmt->stDFx.enDFxEnabled)
    {
        vos_printf("enDFxEnabled is disable\n");
        return;    /* δͳ��, ���� */
    }

    pstStatistics = &(pastDICCMgmt->stDFx.astChanStatus[ucChanId].stStatistics);
    pstIsrOp      = &(pastDICCMgmt->stDFx.astChanStatus[ucChanId].stIsrOp);

    vos_printf("==========Chan Statistics Info=========\n");
    vos_printf("CurrSlice:                  0x%x\n", mdrv_timer_get_normal_timestamp());
    vos_printf("ulInsertPid:                %u\n", pstStatistics->ulInsertPid);
    vos_printf("ulInsertCnt:                %u\n", pstStatistics->ulInsertCnt);
    vos_printf("ulQueueFullCnt:             %u\n", pstStatistics->ulQueueFullCnt);
    vos_printf("ulConsecutiveQueueFullCnt:  %u\n", pstStatistics->ulConsecutiveQueueFullCnt);
    vos_printf("ulLastInsertTime:           0x%x\n", pstStatistics->ulLastInsertTime);
    vos_printf("ulRemovePid:                %u\n", pstStatistics->ulRemovePid);
    vos_printf("ulRemoveCnt:                %u\n", pstStatistics->ulRemoveCnt);
    vos_printf("ulLastRemoveTime:           0x%x\n", pstStatistics->ulLastRemoveTime);
    vos_printf("ulTrigIsrPid:               %u\n", pstStatistics->ulTrigIsrPid);
    vos_printf("ulTrigIsrCnt:               %u\n", pstStatistics->ulTrigIsrCnt);
    vos_printf("ulLastTrigIsrTime:          0x%x\n", pstStatistics->ulLastTrigIsrTime);
    vos_printf("ulDisableIptOpPid:          %u\n", pstIsrOp->ulDisableOpPid);
    vos_printf("ulDisableIptOpTime:         0x%x\n", pstIsrOp->ulDisableOpTime);
    vos_printf("ulDisableIptCnt:            %u\n", pstIsrOp->ulDisableCnt);
    vos_printf("ulEnableIptOpPid:           %u\n", pstIsrOp->ulEnableOpPid);
    vos_printf("ulEnableIptOpTime:          0x%x\n", pstIsrOp->ulEnableOpTime);
    vos_printf("ulEnableIptCnt:             %u\n", pstIsrOp->ulEnableCnt);
}

/*****************************************************************************
�� �� ��  : DICC_Help
��������  : �����Ͽɲ��ά����
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��27��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID DICC_Help()
{
    vos_printf("===============================================\n");
    vos_printf("DICC_Info\n");
    vos_printf("DICC_Chan_Info  ����:ͨ��ID[0-3]\n");
    vos_printf("ͨ��0:����CSDҵ�����ݴ���ͨ��, ���ݷ���:A->C\n");
    vos_printf("ͨ��1:�ͷ������û�ҵ�����ݴ���ͨ��, ���ݷ���:C->A\n");
    vos_printf("ͨ��2:����CSDҵ�����ݴ���ͨ��, ���ݷ���:C->A\n");
    vos_printf("ͨ��3:�ͷ������û�ҵ�����ݴ���ͨ��, ���ݷ���:A->C\n");
    vos_printf("===============================================\n");
}  /* DICC_Help */
#endif    /* end of #if (VOS_WIN32 != VOS_OS_VER) */

/*****************************************************************************
�� �� ��  : DICC_CheckBatRemovePara
��������  : ���ȡ�����ݲ����Ĳ���
�������  : ucChanId - ͨ��ID
            pucUsrData - �Ӻ˼�ȡ�������ݿ�������, �ⲿʹ���߱�ָ֤��ǿ�
�������  : ��
�� �� ֵ  : ���Ϸ����, DICC_OK - �Ϸ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��15��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_CheckBatRemovePara(DICC_CHAN_ID_ENUM_UINT8  ucChnId,
                                VOS_UINT16                  usNeedRemoveCnt,
                                VOS_UINT16                 *pusActiveRemoveCnt,
                                DICC_CPU_ID_ENUM_UINT8      enCpuId)
{
    VOS_UINT32 ulRet;

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if ((ucChnId != g_astChanRole[enCpuId].aenRecver[DICC_SERVICE_TYPE_0])
        && (ucChnId != g_astChanRole[enCpuId].aenRecver[DICC_SERVICE_TYPE_1]))
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckRemovePara] <ucChnId> <enUserRole> not match ",
            enCpuId, ucChnId, DICC_CHAN_ROLE_RECVER);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    if (usNeedRemoveCnt > DICC_BAT_OP_CNT)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckRemovePara] <ucChnId> ulNeedRemoveCnt is invalid ",
            enCpuId, ucChnId);
        return DICC_ERR_REMOVE_DATA_CNT;
    }

/*
    if (VOS_NULL_PTR == apucUsrData)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckRemovePara] <ucChnId> apucUsrData is NULL ",
            enCpuId, ucChnId);
        return DICC_ERR_REMOVE_DATA_PTR_NULL;
    }
*/

    if (VOS_NULL_PTR == pusActiveRemoveCnt)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckRemovePara] <ucChnId> pusActiveRemoveCnt is NULL ",
            enCpuId, ucChnId);
        return DICC_ERR_REMOVE_DATA_PTR_NULL;
    }

    return DICC_OK;
}

/*****************************************************************************
�� �� ��  : DICC_BatRemoveChannelData
��������  : �����ݵ���Ϣ�Ӻ˼价�ι�������ȡ��API
�������  : ulPid - ���ô˽ӿڵ�PID
            ucChanId - ͨ��ID
            pucUsrData - �Ӻ˼�ȡ�������ݿ�������, �ⲿʹ���߱�ָ֤��ǿ�
�������  : ��
�� �� ֵ  : �����ɹ����, DICC_OK - �ɹ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��8��11��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_BatRemoveChannelData(VOS_UINT32            ulPid,
                                  DICC_CHAN_ID_ENUM_UINT8  ucChnId,
                                  VOS_UINT8                aucUsrData[],
                                  VOS_UINT16               usNeedRemoveCnt,
                                  VOS_UINT16              *pusActiveRemoveCnt,
                                  DICC_CPU_ID_ENUM_UINT8   enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU             *pstDiccChnCtrl = VOS_NULL_PTR;
    volatile DICC_QUEUE_NODE_STRU            *pstQueueNode   = VOS_NULL_PTR;
#if (1 == DICC_DFX_SWITCH)
    DICC_DFX_STRU                            *pstDFx;
#endif
    VOS_UINT32                                ulRet;
    DICC_CHAN_MAGIC_NUM_CHANGED_EVENT_STRU    stMagicEvent;
    VOS_UINT32                                ulActiveNeedCnt;
    VOS_UINT32                                ulResult;
    VOS_UINT32                                ulRingQCnt;
#if 0
    VOS_VOID                                 *astQueueNode[DICC_BAT_OP_CNT];
#endif
    VOS_UINT32                                ulCurrTime;
    VOS_UINT32                                ulCopyLen;

    DEBUG_PRINT("DICC_RemoveChannelData entered! \n");

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DICC_CheckBatRemovePara(ucChnId, usNeedRemoveCnt,
                pusActiveRemoveCnt, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* ����ͨ���Ų��ҵ��˼����ݹ�����ƽṹ */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    /* �ɱ��ػ����ź�����ʵ�ֱ��˸�API������ */
    ulResult = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != ulResult)
    {
        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_InsertChannelDataAction] take ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)ulResult);

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    /* ���ն�û�йر�, ����Լ���ȡ�� */
    if (DICC_CHAN_RECVER_OPEN_MASK == (DICC_CHAN_RECVER_OPEN_MASK & pstDiccChnCtrl->ucStateMask))
    {
        ulRingQCnt      = TTF_RING_Q_GetCnt(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
        ulActiveNeedCnt = PS_MIN(ulRingQCnt, usNeedRemoveCnt);    /* Ӧ���û��ṩ�ĸ�����׼ȷ */
        *pusActiveRemoveCnt = 0;
        ulCopyLen       = 0;
        ulCurrTime      = mdrv_timer_get_normal_timestamp();

        while (0 != ulActiveNeedCnt)
        {
            /* ��ȡ��һ���˼䴫�ݽ�� */
            pstQueueNode = (DICC_QUEUE_NODE_STRU*)TTF_RING_Q_Out(ulPid,
                (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));

            if (VOS_NULL_PTR == pstQueueNode)
            {
                /* �ͷ��ź��� */
                VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

                DICC_LOG(PS_PRINT_WARNING,
                    "[<LOCAL CPU_ID>: DICC_RemoveChannelData] Get the node fail ");
                return DICC_ERR_GET_NODE_FAIL;
            }

#if (1 == DICC_DFX_SWITCH)
            /* ȡ������++ */
            pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);
            (pstDFx->astChanStatus[ucChnId].stStatistics.ulRemoveCnt)++;
            pstDFx->astChanStatus[ucChnId].stStatistics.ulRemovePid = ulPid;
            pstDFx->astChanStatus[ucChnId].stStatistics.ulLastRemoveTime = ulCurrTime;
#endif

            DEBUG_PRINT("pstQueueNode:0x%x pstQueueNode->aucPriData:0x%x\n",
                        (unsigned int)pstQueueNode, (unsigned int)pstQueueNode->aucPriData);

            if (DICC_MAGIC_NUM_VALUE != pstQueueNode->usMagicNum)
            {
                /* �ͷ��ź��� */
                VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

                /* �����¼� */
                stMagicEvent.ulOpPid    = ulPid;
                stMagicEvent.ucChnId    = ucChnId;
                PS_MEM_CPY(&(stMagicEvent.stQueueNode), (VOS_UINT8*)pstQueueNode, sizeof(stMagicEvent.stQueueNode));

                DICC_SndEvent(ID_DICC_MNTN_MAGIC_NUM_CHANGED_EVENT, &stMagicEvent, sizeof(stMagicEvent), enCpuId);

                DICC_LOG2(PS_PRINT_ERROR,
                    "[<LOCAL CPU_ID>: DICC_RemoveChannelData] <ucChnId> find magic num tampered",
                    enCpuId, ucChnId);
                return DICC_ERR_MAGIC_NUM_CHANGED;
            }

            VOS_MemCpy(&aucUsrData[ulCopyLen], (VOS_UINT8 *)pstQueueNode->aucPriData, pstQueueNode->ucPriDataLen);
            ulCopyLen += pstQueueNode->ucPriDataLen;

            /* ���ǵ�������Ϣ������ָ��֮��, Ϊ�˰�ȫ, ���������Ϣ */
            VOS_MemSet((VOS_VOID *)pstQueueNode->aucPriData, 0x0, sizeof(pstQueueNode->aucPriData));

            /* ���ͨ���������ݺ�����Ӽ��� */
            (*pusActiveRemoveCnt)++;

            ulActiveNeedCnt--;
        }
    }

    /* �ͷ��ź��� */
    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    return DICC_OK;
}    /* DICC_RemoveChannelData */

VOS_UINT8 g_ucCheckBatInsert = 1;
/*****************************************************************************
�� �� ��  : DICC_CheckBatInsertPara
��������  : ���������ݲ����Ĳ���
�������  : ucChanId - ͨ��ID
            pstDscpBlk - �˼䴫�������ֶ�
�������  : ��
�� �� ֵ  : ���Ϸ����, DICC_OK - �Ϸ�, ���� - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��12��15��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_CheckBatInsertPara(VOS_UINT32 ulPid,
                                DICC_CHAN_ID_ENUM_UINT8    ucChnId,
                                DICC_BAT_INSERT_DSCP_BLK_STRU    *pstBatDscpBlk,
                                DICC_CPU_ID_ENUM_UINT8     enCpuId)
{
    VOS_UINT32                           ulRet;
    volatile DICC_CHAN_CTRL_STRU        *pstDiccChnCtrl = VOS_NULL_PTR;
    VOS_UINT32                           ulLoop;
    VOS_UINT32                           ulCurrCnt;

    ulRet = DICC_CheckChanOpPara(ucChnId, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    if ((ucChnId != g_astChanRole[enCpuId].aenSender[DICC_SERVICE_TYPE_0])
        && (ucChnId != g_astChanRole[enCpuId].aenSender[DICC_SERVICE_TYPE_1]))
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> <enRole> not match ",
            enCpuId, ucChnId, DICC_CHAN_ROLE_SENDER);
        return DICC_ERR_CHAN_ID_NOT_MATCH_ROLE;
    }

    if (VOS_NULL_PTR == pstBatDscpBlk)
    {
        DICC_LOG2(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> pstDscpBlk is NULL ",
            enCpuId, ucChnId);
        return DICC_ERR_INSERT_DESP_BLK_PTR_NULL;
    }

    if (pstBatDscpBlk->ucInsertCnt > DICC_BAT_OP_CNT)
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> <ucInsertCnt> is invalid ",
            enCpuId, ucChnId, pstBatDscpBlk->ucInsertCnt);
        return DICC_ERR_INSERT_DESP_BLK_DATA_CNT;
    }

    /* ����ͨ���Ų��ҵ��˼����ݹ�����ƽṹ */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);

    if (1 == g_ucCheckBatInsert)
    {
        for (ulLoop = 0; ulLoop < (VOS_UINT32)(pstBatDscpBlk->ucInsertCnt); ulLoop ++)
        {
            if (VOS_NULL_PTR == pstBatDscpBlk->apucUserData[ulLoop])
            {
                DICC_LOG2(PS_PRINT_WARNING,
                    "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> pstDscpBlk->pucUserData is NULL ",
                    enCpuId, ucChnId);
                return DICC_ERR_INSERT_DESP_BLK_DATA_NULL;
            }

            if (pstDiccChnCtrl->ucPriDataLen < (VOS_UINT16)(pstBatDscpBlk->aucDataLen[ulLoop]))
            {
                DICC_LOG3(PS_PRINT_WARNING,
                    "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> <ucDataLen> size error ",
                    enCpuId, ucChnId, (pstBatDscpBlk->aucDataLen[ulLoop]));
                return DICC_ERR_DLV_DATA_BLK_SIZE;
            }
        }
    }

    /* ���ﲻ��Ҫ����, ��ͬһ�˶���, ֻҪ�������˶���, ���ܲ���;
       ��һ����mask���޷���sender��û�йر�ǰ, recver���޷��ر� */
    if (DICC_CHAN_BOTH_OPEN_MASK != pstDiccChnCtrl->ucStateMask)
    {
        DICC_LOG3(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> is not all open, <mask> ",
            enCpuId, ucChnId, (pstDiccChnCtrl->ucStateMask));
        return DICC_ERR_CHAN_NOT_OPEN_IN_BOTH_SIDES;
    }

    /* ��ȡͨ���е�ǰ��ŵ���Ϣ���� */
    ulCurrCnt = TTF_RING_Q_GetCnt(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
    if ((pstBatDscpBlk->ucInsertCnt + ulCurrCnt) >= pstDiccChnCtrl->usChnBlkNum)
    {
        DICC_LOG4(PS_PRINT_WARNING,
            "[<LOCAL CPU_ID>: DICC_CheckInsertPara] <ucChnId> cannot <insert>, <currcnt> ",
            enCpuId, ucChnId, (pstBatDscpBlk->ucInsertCnt), (VOS_INT)ulCurrCnt);
        return DICC_ERR_INSERT_DESP_BLK_DATA_CNT;
    }

    return DICC_OK;
}

/*****************************************************************************
�� �� ��  : DICC_BatInsertChannelDataAction
��������  : �������ݵ���Ϣ����ת�Ƶ��˼�API
            ���������ṹ��enAutoTrigTx��Ϊ0ʱ, ���ᴥ��������Ϊ,
            ��ʱ��Ҫ�ɷ��Ͷ�����������DICC_TriggerChanDataTx����;
            ֻ����ͨ���򿪺�, ��Ϣ�Ż��������ݵ��Զ�
            ���Ͷ˺ͽ��ն�����һ��δ��, ��˼�ת�ƴ����ݵ���Ϣ���ݲ���ʧ��
�������  : ucChanId - ͨ��ID
            pstDscpBlk - �˼䴫�������ֶ�
�������  : ��
�� �� ֵ  : �����ɹ����, VOS_OK - �ɹ�, VOS_ERR - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2011��8��11��
   ��    ��   : liukai
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 DICC_BatInsertChannelDataAction(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum,
                                        VOS_UINT32 ulPid, DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                                        DICC_BAT_INSERT_DSCP_BLK_STRU    *pstBatDscpBlk,
                                        DICC_CPU_ID_ENUM_UINT8 enCpuId)
{
    volatile DICC_CHAN_CTRL_STRU        *pstDiccChnCtrl = VOS_NULL_PTR;
    volatile DICC_QUEUE_NODE_STRU       *pstQueueNode = VOS_NULL_PTR;
    VOS_UINT32                           ulCurrTime;
    DICC_DFX_STRU                       *pstDFx;
    VOS_UINT32                           ulRet;
    VOS_UINT32                           ulResult;
    VOS_UINT32                           ulActiveInsertCnt;


    DEBUG_PRINT("DICC_InsertChannelData entered ChnId: %d.\n", ucChnId);

    ulRet = DICC_CheckCpuId(enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DICC_CheckBatInsertPara(ulPid, ucChnId, pstBatDscpBlk, enCpuId);
    if (DICC_OK != ulRet)
    {
        return ulRet;
    }

    /* �ɱ��ػ����ź�����ʵ�ֱ��˸�API������ */
    ulResult = VOS_SmP(g_astChanRole[enCpuId].ulDiccLocalMutexSem, 0);
    if (VOS_OK != ulResult)
    {
        DICC_LOG1(PS_PRINT_ERROR,
            "[<LOCAL CPU_ID>: DICC_InsertChannelDataAction] take ulDiccLocalMutexSem fail, <ulSemRslt>",
            (VOS_INT32)ulResult);

        return DICC_ERR_LOCAL_SEMPHORE_FAIL;
    }

    /* ����ͨ���Ų��ҵ��˼����ݹ�����ƽṹ */
    pstDiccChnCtrl = (DICC_CHAN_CTRL_STRU *)DICC_GetCtrlChnAddr(ucChnId, enCpuId);
    ulActiveInsertCnt = 0;
    ulCurrTime = mdrv_timer_get_normal_timestamp();    /* ��ȡ��ǰʱ�� */

    while (ulActiveInsertCnt < pstBatDscpBlk->ucInsertCnt)
    {
        /* ��ȡ�˼䴫�ݽ�� */
        pstQueueNode = (DICC_QUEUE_NODE_STRU*)TTF_RING_Q_Rear(ulPid,
            (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
        if (VOS_NULL_PTR == pstQueueNode)
        {
            /* �ͷ��ź��� */
            VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

            DICC_LOG(PS_PRINT_WARNING,
                "[<LOCAL CPU_ID>: DICC_InsertChannelDataAction] Get the node fail ");
            return DICC_ERR_GET_NODE_FAIL;
        }

        /* ���ݴ���ʱ�� */
        pstQueueNode->ulInsertTime = ulCurrTime;

        /* ���������ֶ�����, ����ulConsecutiveQueueFullCnt���� */
        pstDFx = DICC_GET_CHAN_DFX(g_astChanRole[enCpuId].pastDICCMgmt);
        pstDFx->astChanStatus[ucChnId].stStatistics.ulConsecutiveQueueFullCnt = 0;

        /* ��������˼䴫�ݽ�� */
        VOS_MemCpy((VOS_UINT8 *)pstQueueNode->aucPriData,
                   pstBatDscpBlk->apucUserData[ulActiveInsertCnt],
                   pstBatDscpBlk->aucDataLen[ulActiveInsertCnt]);
        pstQueueNode->ucPriDataLen = pstBatDscpBlk->aucDataLen[ulActiveInsertCnt];

#if (1 == DICC_DFX_SWITCH)
        /* �������++ */
        (pstDFx->astChanStatus[ucChnId].stStatistics.ulInsertCnt)++;
        pstDFx->astChanStatus[ucChnId].stStatistics.ulInsertPid      = ulPid;
        pstDFx->astChanStatus[ucChnId].stStatistics.ulLastInsertTime = ulCurrTime;
#endif

        ulActiveInsertCnt ++;

        /* ��˼������Ϣ���� */
        TTF_RING_Q_In(ulPid, (TTF_RING_Q_ST *)(&(pstDiccChnCtrl->stRingBuffer)));
    }

    if (PS_TRUE == pstBatDscpBlk->enAutoTrigTx)
    {
        DICC_TriggerChanDataTx(ulPid, ucChnId, enCpuId);
    }

    /* �ͷ��ź��� */
    VOS_SmV(g_astChanRole[enCpuId].ulDiccLocalMutexSem);

    return DICC_OK;
}    /* DICC_InsertChannelData */
/*lint -restore */

#endif  /*FEATURE_ON == FEATURE_CSD*/

#ifdef  __cplusplus
 #if  __cplusplus
}
 #endif
#endif



