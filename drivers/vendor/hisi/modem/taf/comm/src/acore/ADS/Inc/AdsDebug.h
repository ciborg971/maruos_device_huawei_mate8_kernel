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

#ifndef __ADSTEST_H__
#define __ADSTEST_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "AdsCtx.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "msp_diag.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define ADS_LATENCY_LOG(ModuleId, String)   \
            ADS_LATENCY_OM_LOG(__FILE__, __LINE__, ModuleId, LOG_LEVEL_ERROR, String)

/*����ͳ����Ϣ*/
#define  ADS_DBG_RECV_UL_PKT_NUM(i, n)              (g_stAdsStats.astAdsSpecStatsInfo[i].ulUlRecvPktNum += (n))
#define  ADS_DBG_UL_SAVE_BUFF_PKT_NUM(i, n)         (g_stAdsStats.astAdsSpecStatsInfo[i].ulUlSaveBuffPktNum += (n))
#define  ADS_DBG_UL_ENQUE_FAIL_NUM(i, n)            (g_stAdsStats.astAdsSpecStatsInfo[i].ulUlEnQueFail += (n))
#define  ADS_DBG_UL_CFG_FAIL_FREE_NUM(i, n)         (g_stAdsStats.astAdsSpecStatsInfo[i].ulUlCfgFailFreeNum += (n))
#define  ADS_DBG_UL_CURRT_BDCD_NUM(i, n)            (g_stAdsStats.astAdsSpecStatsInfo[i].ulUlCurrtBDCDNum += (n))

/*����ͳ����Ϣ*/
#define  ADS_DBG_RECV_DL_PKT_NUM(i, n)              (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRecvPktNum += (n))
#define  ADS_DBG_SEND_DL_PKT_NUM(i, n)              (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlSendPktNum += (n))
#define  ADS_DBG_DL_IPF_ERR_PKT_NUM(i, n)           (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlIPFErrNum += (n))
#define  ADS_DBG_DL_IPV6_BIG_PKT_NUM(i, n)          (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlIpv6BigPktum += (n))
#define  ADS_DBG_DL_RECV_NDCLIENT_PKT_NUM(i, n)     (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRecvNDClintPktum += (n))
#define  ADS_DBG_DL_RABID_ERR_PKT_NUM(i, n)         (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRabIdErrPktum += (n))
#define  ADS_DBG_DL_RECV_DHCPV4V6_PKT_NUM(i, n)     (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRecvDHCPV4V6Pktum += (n))
#define  ADS_DBG_DL_RECV_IPV6_LINK_LOCAL_ADRESS_PKT_NUM(i, n)  (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRecvIPV6LinkLocalAddressPktum += (n))
/* ֻ��V3R3��ʹ�� */
#define  ADS_DBG_DL_TRANS_FROM_IMMZC_ERR_NUM(n)     (g_stAdsStats.astAdsSpecStatsInfo[0].ulDlTransformImmZcErr += (n))
#define  ADS_DBG_DL_FREE_NUM(i, n)                  (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlFreeNum += (n))

#define  ADS_DBG_UL_CFG_IPF_HAVE_NO_BDCD(n)         (g_stAdsStats.stUlComStatsInfo.ulUlCfgIpfHaveNoBDCD += (n))
#define  ADS_DBG_UL_SEND_BUFF_PKT_NUM(n)            (g_stAdsStats.stUlComStatsInfo.ulUlSendBuffPktNum += (n))
#define  ADS_DBG_UL_SEND_PKT_FAIL_NUM(n)            (g_stAdsStats.stUlComStatsInfo.ulUlIpfSendPktFailNum += (n))
#define  ADS_DBG_UL_PROC_EVENT_NUM(n)               (g_stAdsStats.stUlComStatsInfo.ulUlProcEventNum += (n))

#define  ADS_DBG_DL_RECV_IPF_BREAK_NUM(n)           (g_stAdsStats.stDlComStatsInfo.ulDlRecvIPFBreakNum += (n))
#define  ADS_DBG_DL_RECV_ADQ_EMPTY_BREAK_NUM(n)     (g_stAdsStats.stDlComStatsInfo.ulDlRecvAdqEmptyBreakNum += (n))
#define  ADS_DBG_DL_RECV_RD_ZERO_NUM(n)             (g_stAdsStats.stDlComStatsInfo.ulDlRecvRDZeroNum += (n))
#define  ADS_DBG_DL_RECV_RD_NUM(n)                  (g_stAdsStats.stDlComStatsInfo.ulDlRecvRDNum += (n))
#define  ADS_DBG_DL_PROC_EVENT_NUM(n)               (g_stAdsStats.stDlComStatsInfo.ulDlProcEventNum += (n))
#define  ADS_DBG_DL_PROC_RD_EVENT_NUM(n)            (g_stAdsStats.stDlComStatsInfo.ulDlRdEventNum += (n))
#define  ADS_DBG_DL_PROC_AD_EMPTY_EVENT_NUM(n)      (g_stAdsStats.stDlComStatsInfo.ulDlAdEmptyNum += (n))
#define  ADS_DBG_DL_PROC_ALL_EVENT_NUM(n)           (g_stAdsStats.stDlComStatsInfo.ulDlAllEvent += (n))
#define  ADS_DBG_DL_PROC_EMPTY_EVENT_NUM(n)         (g_stAdsStats.stDlComStatsInfo.ulDlEmptyEvent += (n))

/* ����Դ�ڴ��ͷ�ͳ�� */
#define ADS_DBG_UL_IPF_SAVE_SRCMEM_FAIL_NUM(n)      (g_stAdsStats.stUlComStatsInfo.ulUlIpfSaveSrcMemFail  += (n))
#define ADS_DBG_UL_IPF_SAVE_SRCMEM_SUCC_NUM(n)      (g_stAdsStats.stUlComStatsInfo.ulUlIpfSaveSrcMemSucc  += (n))
#define ADS_DBG_UL_IPF_FREE_SRCMEM_NUM(n)           (g_stAdsStats.stUlComStatsInfo.ulUlIpfFreeSrcMemNum   += (n))
#define ADS_DBG_UL_IPF_FREE_SRCMEM_ERROR(n)         (g_stAdsStats.stUlComStatsInfo.ulUlIpfFreeSrcMemErr   += (n))
#define ADS_DBG_UL_DROPPED_PACKET_NUM(n)            (g_stAdsStats.stUlComStatsInfo.ulUlDroppedPacketNum   += (n))

#define ADS_DBG_UL_LEVEL_ONE_CNT(n)                  (g_stAdsStats.stUlComStatsInfo.ulLevelOneCnt   += (n))
#define ADS_DBG_UL_LEVEL_TWO_CNT(n)                  (g_stAdsStats.stUlComStatsInfo.ulLevelTwoCnt   += (n))
#define ADS_DBG_UL_LEVEL_THREE_CNT(n)                (g_stAdsStats.stUlComStatsInfo.ulLevelThreeCnt += (n))
#define ADS_DBG_UL_LEVEL_FOUR_CNT(n)                 (g_stAdsStats.stUlComStatsInfo.ulLevelFourCnt  += (n))

/* ��������ϵͳ�ڴ�ͳ�� */
#define ADS_DBG_DL_ALLOC_SYS_MEM_FAIL_NUM(n)        (g_stAdsStats.stDlComStatsInfo.ulDlAllocSysMemFailNum   += (n))
#define ADS_DBG_DL_ALLOC_SYS_MEM_SUCC_NUM(n)        (g_stAdsStats.stDlComStatsInfo.ulDlAllocSysMemSuccNum   += (n))

/* ����ADͳ��  */
#define ADS_DBG_DL_GET_AD_FAIL_NUM(n)               (g_stAdsStats.stDlComStatsInfo.ulDlGetAdFailNum         += (n))
#define ADS_DBG_DL_CONFIG_AD_SUCC_NUM(i, n)         (g_stAdsStats.stDlComStatsInfo.aulDlConfigAdSuccNum[i]  += (n))
#define ADS_DBG_DL_CONFIG_AD_FAIL_NUM(i, n)         (g_stAdsStats.stDlComStatsInfo.aulDlConfigAdFailNum[i]  += (n))
#define ADS_DBG_DL_GET_ADQ_EMPTY_NUM(i, n)          (g_stAdsStats.stDlComStatsInfo.aulDlGetAdqEmptyNum[i]   += (n))
#define ADS_DBG_DL_ALLOC_AD_FAIL_NUM(i, n)          (g_stAdsStats.stDlComStatsInfo.aulDlAllocAdFailNum[i]   += (n))
#define ADS_DBG_DL_ALLOC_AD_SUCC_NUM(i, n)          (g_stAdsStats.stDlComStatsInfo.aulDlAllocAdSuccNum[i]   += (n))

#define  ADS_DBG_DL_RD_TI_PROTECT_EXPIRED_NUM(n)    (g_stAdsStats.stDlComStatsInfo.ulDlRdTiProtectExpiredNum += (n))
#define  ADS_DBG_DL_RD_PROTECT_EVENT_NUM(n)         (g_stAdsStats.stDlComStatsInfo.ulDlRdProctectEventNum += (n))
#define  ADS_DBG_DL_FC_ACTIVATE_NUM(n)              (g_stAdsStats.stDlComStatsInfo.ulDlFcTmrExpiredCnt += (n))
#define  ADS_DBG_DL_FC_TMR_EXP_NUM(n)               (g_stAdsStats.stDlComStatsInfo.ulDlFcActivateCnt += (n))

#define ADS_DBG_DL_ADQ_START_EMPTY_TMR_NUM(n)       (g_stAdsStats.stDlComStatsInfo.ulDlAdqStartEmptyTmrNum += (n))
#define ADS_DBG_DL_ADQ_EMPTY_TMR_TIMEOUT_NUM(n)     (g_stAdsStats.stDlComStatsInfo.ulDlAdqEmptyTmrTimeoutNum += (n))

#define ADS_DBG_SET_SEM_INIT_FLAG(flag)              (g_stAdsStats.stResetStatsinfo.ulSemInitFlg = (flag))
#define ADS_UL_DBG_SAVE_BINARY_SEM_ID(sem_id)        (g_stAdsStats.stResetStatsinfo.hULBinarySemId = (sem_id))
#define ADS_DL_DBG_SAVE_BINARY_SEM_ID(sem_id)        (g_stAdsStats.stResetStatsinfo.hDLBinarySemId = (sem_id))
#define ADS_UL_DBG_CREATE_BINARY_SEM_FAIL_NUM(n)     (g_stAdsStats.stResetStatsinfo.ulULCreateBinarySemFailNum += (n))
#define ADS_DL_DBG_CREATE_BINARY_SEM_FAIL_NUM(n)     (g_stAdsStats.stResetStatsinfo.ulDLCreateBinarySemFailNum += (n))
#define ADS_UL_DBG_LOCK_BINARY_SEM_FAIL_NUM(n)       (g_stAdsStats.stResetStatsinfo.ulULLockBinarySemFailNum += (n))
#define ADS_DL_DBG_LOCK_BINARY_SEM_FAIL_NUM(n)       (g_stAdsStats.stResetStatsinfo.ulDLLockBinarySemFailNum += (n))
#define ADS_UL_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(rslt)  (g_stAdsStats.stResetStatsinfo.ulULLastBinarySemErrRslt = (rslt))
#define ADS_DL_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(rslt)  (g_stAdsStats.stResetStatsinfo.ulDLLastBinarySemErrRslt = (rslt))
#define ADS_UL_DBG_SAVE_CCPU_RESET_SUCCESS_NUM(n)    (g_stAdsStats.stResetStatsinfo.ulULResetSucessNum += (n))
#define ADS_DL_DBG_SAVE_CCPU_RESET_SUCCESS_NUM(n)    (g_stAdsStats.stResetStatsinfo.ulDLResetSucessNum += (n))

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : ADS_FLOW_DEBUG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ADS�����ϱ�Debug����
*****************************************************************************/
enum ADS_FLOW_DEBUG_ENUM
{
    ADS_FLOW_DEBUG_OFF                  = 0,
    ADS_FLOW_DEBUG_DL_ON                = 1,
    ADS_FLOW_DEBUG_UL_ON                = 2,
    ADS_FLOW_DEBUG_ALL_ON               = 3,
    ADS_FLOW_DEBUG_BUTT
};

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef struct
{
    /*ADS����ͳ����Ϣ*/
    VOS_UINT32              ulUlRecvPktNum;                                     /*ADS�յ��������ݵĸ���*/
    VOS_UINT32              ulUlSaveBuffPktNum;                                 /*ADS���л��������*/
    VOS_UINT32              ulUlEnQueFail;                                      /*ADS�������ʧ�ܴ���*/
    VOS_UINT32              ulUlCfgFailFreeNum;                                 /*��������BDʧ�ܺ��ͷ�SDU����*/
    VOS_UINT32              ulUlCurrtBDCDNum;                                   /*��ǰ������BD/CD����*/

    /*����RDͳ����Ϣ*/
    VOS_UINT32              ulDlRecvPktNum;                                     /*ADS�յ��������ݵĸ���*/
    VOS_UINT32              ulDlSendPktNum;                                     /*ADS������APP���ݵĸ���*/
    VOS_UINT32              ulDlIPFErrNum;                                      /*IPF���˴��������*/
    VOS_UINT32              ulDlIpv6BigPktum;                                   /*��ȡ������MTU��IPV6������*/
    VOS_UINT32              ulDlRabIdErrPktum;                                  /*RAB ID��������ݰ��ĸ���*/
    VOS_UINT32              ulDlRecvNDClintPktum;                               /*��Ҫת����NDClient���ݰ��ĸ���*/
    VOS_UINT32              ulDlRecvDHCPV4V6Pktum;                              /*��Ҫת����NDClient���ݰ��ĸ���*/
    VOS_UINT32              ulDlRecvIPV6LinkLocalAddressPktum;                  /*��Ҫת����NDClient���ݰ��ĸ���*/

    VOS_UINT32              ulDlTransformImmZcErr;                              /*��Ҫת����NDClient���ݰ��ĸ���*/
    VOS_UINT32              ulDlFreeNum;                                        /*ADS�����ͷ�C���ڴ�Ĵ���*/

    /* ����ͳ����Ϣ */
    VOS_UINT32              ulDLFlowInfo;                                       /*ADS��������Byte����*/
    VOS_UINT32              ulDLStartSlice;                                     /*ADS��������ͳ�ƿ�ʼʱ��*/
    VOS_UINT32              ulDLEndSlice;                                       /*ADS��������ͳ�ƽ���ʱ��*/

    VOS_UINT32              ulULFlowInfo;                                       /*ADS��������Byte����*/
    VOS_UINT32              ulULStartSlice;                                     /*ADS��������ͳ�ƿ�ʼʱ��*/
    VOS_UINT32              ulULEndSlice;                                       /*ADS��������ͳ�ƽ���ʱ��*/
}ADS_SPEC_STATS_INFO_STRU;


typedef struct
{
    VOS_UINT32              ulUlCfgIpfHaveNoBDCD;                               /*��������IPFû�л��BD/CD����*/
    VOS_UINT32              ulUlSendBuffPktNum;                                 /*ADS�������л��������*/
    VOS_UINT32              ulUlIpfSendPktFailNum;                              /*����IPF����ʧ�ܵĴ���*/
    VOS_UINT32              ulUlProcEventNum;                                   /*ADS���������¼�����*/
    VOS_UINT32              ulUlIpfSaveSrcMemFail;                              /* ����IPFԴ�ڴ���в��㵼���ڴ�*/
    VOS_UINT32              ulUlIpfSaveSrcMemSucc;                              /* ���б���Դ�ڴ���� */
    VOS_UINT32              ulUlIpfFreeSrcMemNum;                               /* �����ͷ�Դ�ڴ���� */
    VOS_UINT32              ulUlIpfFreeSrcMemErr;                               /* �����ͷ��ڴ���� */
    VOS_UINT32              ulUlDroppedPacketNum;                               /* ���г����������� */

    VOS_UINT32              ulLevelOneCnt;
    VOS_UINT32              ulLevelTwoCnt;
    VOS_UINT32              ulLevelThreeCnt;
    VOS_UINT32              ulLevelFourCnt;

    /* ����ͳ����Ϣ */
    VOS_UINT32              ulULFlowDebugFlag;                                  /*��������Debug����*/
    VOS_UINT32              ulULFlowRptThreshold;                               /*���������ϱ�����*/
}ADS_UL_COM_STATS_INFO_STRU;


typedef struct
{
    VOS_UINT32              ulDlRecvIPFBreakNum;                                /*�����յ�IPF�¼��ĸ���*/
    VOS_UINT32              ulDlRecvRDNum;                                      /*���л�ȡRD�Ĵ���*/
    VOS_UINT32              ulDlRecvRDZeroNum;                                  /*���л�ȡRDΪ0�Ĵ���*/
    VOS_UINT32              ulDlProcEventNum;                                   /*ADS���������¼�����*/
    VOS_UINT32              ulDlRdEventNum;
    VOS_UINT32              ulDlAdEmptyNum;
    VOS_UINT32              ulDlOtherEvent;
    VOS_UINT32              ulDlAllEvent;
    VOS_UINT32              ulDlEmptyEvent;
    VOS_UINT32              ulDlAllocSysMemSuccNum;                             /* ADS��������ϵͳ�ڴ�ɹ����� */
    VOS_UINT32              ulDlAllocSysMemFailNum;                             /* ADS��������ϵͳ�ڴ�ʧ�ܴ��� */
    VOS_UINT32              ulDlGetAdFailNum;                                   /* ADS���л�ȡADʧ�ܴ��� */
    VOS_UINT32              aulDlConfigAdSuccNum[IPF_AD_MAX];                   /* ADS��������AD�ɹ����� */
    VOS_UINT32              aulDlConfigAdFailNum[IPF_AD_MAX];                   /* ADS��������ADʧ�ܴ��� */
    VOS_UINT32              ulDlRecvAdqEmptyBreakNum;                           /* ADS���п��жϴ��� */
    VOS_UINT32              ulDlProcAdqEmptyEventNum;                           /* ADS���п��ж��¼����� */
    VOS_UINT32              aulDlGetAdqEmptyNum[IPF_EMPTY_MAX];                 /* ADS����ADQΪ�յĴ��� */
    VOS_UINT32              aulDlAllocAdSuccNum[IPF_AD_MAX];                    /* ADS��������AD�ɹ��Ĵ��� */
    VOS_UINT32              aulDlAllocAdFailNum[IPF_AD_MAX];                    /* ADS��������ADʧ�ܵĴ��� */
    VOS_UINT32              ulDlRdTiProtectExpiredNum;                          /*ADS��������RD������ʱ����ʱ����*/
    VOS_UINT32              ulDlRdProctectEventNum;                             /*ADS��������RD�����¼�����*/
    VOS_UINT32              ulDlFcTmrExpiredCnt;
    VOS_UINT32              ulDlFcActivateCnt;
    /* ����ͳ����Ϣ */
    VOS_UINT32              ulDLFlowDebugFlag;                                  /*��������Debug����*/
    VOS_UINT32              ulDLFlowRptThreshold;                               /*���������ϱ�����*/

    VOS_UINT32              ulDlAdqStartEmptyTmrNum;
    VOS_UINT32              ulDlAdqEmptyTmrTimeoutNum;
}ADS_DL_COM_STATS_INFO_STRU;
typedef struct
{
    VOS_SEM                 hULBinarySemId;                                     /* ���ж������ź���ID */
    VOS_SEM                 hDLBinarySemId;                                     /* ���ж������ź���ID */
    VOS_UINT32              ulSemInitFlg;                                       /* ��ʼ����ʶ, VOS_TRUE: �ɹ�; VOS_FALSE: ʧ�� */
    VOS_UINT32              ulULCreateBinarySemFailNum;                         /* �������ж������ź���ʧ�ܴ��� */
    VOS_UINT32              ulDLCreateBinarySemFailNum;                         /* �������ж������ź���ʧ�ܴ��� */
    VOS_UINT32              ulULLockBinarySemFailNum;                           /* �����ж������ź���ʧ�ܴ��� */
    VOS_UINT32              ulDLLockBinarySemFailNum;                           /* �����ж������ź���ʧ�ܴ��� */
    VOS_UINT32              ulULLastBinarySemErrRslt;                           /* ���һ���������������ź���ʧ�ܽ�� */
    VOS_UINT32              ulDLLastBinarySemErrRslt;                           /* ���һ���������������ź���ʧ�ܽ�� */
    VOS_UINT32              ulULResetSucessNum;                                 /* C�˸�λ���гɹ��Ĵ��� */
    VOS_UINT32              ulDLResetSucessNum;                                 /* C�˸�λ���гɹ��Ĵ��� */
}ADS_RESET_STATS_INFO_STRU;
typedef struct
{
    ADS_SPEC_STATS_INFO_STRU        astAdsSpecStatsInfo[ADS_INSTANCE_MAX_NUM];  /* ÿ��ʵ��ר�е�ͳ����Ϣ */
    ADS_UL_COM_STATS_INFO_STRU      stUlComStatsInfo;
    ADS_DL_COM_STATS_INFO_STRU      stDlComStatsInfo;
    ADS_RESET_STATS_INFO_STRU       stResetStatsinfo;

}ADS_STATS_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulAdType;
    VOS_UINT32                          ulAdNum;
    VOS_UINT32                          ulBeginTi;
    VOS_UINT32                          ulMiddleTi;
    VOS_UINT32                          ulEndTi;
}ADS_DL_DEBUG_AD_TIMER_STRU;

typedef struct
{
    VOS_UINT32                          ulBeginTi;
    VOS_UINT32                          ulEndTi;
}ADS_DL_DEBUG_RD_TIMER_STRU;

typedef struct
{
    VOS_UINT32                          ulBeginTi;
    VOS_UINT32                          ulEndTi;
}ADS_DL_DEBUG_TASK_TIMER_STRU;


typedef struct
{
    ADS_LOG_HEAD_STRU                   stLogHeader;
    ADS_STATS_INFO_STRU                 stAdsStats;                             /* ADS��ͳ����Ϣ */
}ADS_LOG_RPT_STATS_INFO_STRU;

/*****************************************************************************
  8 ȫ�ֱ�������
*****************************************************************************/

extern ADS_STATS_INFO_STRU                     g_stAdsStats;
extern VOS_UINT32                              g_ulAdsPrintUlDataFlg;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_VOID ADS_LATENCY_OM_LOG(const VOS_CHAR  *pcFileName,  VOS_UINT32  ulLineNum,
                                   VOS_UINT32      ulModuleId,   VOS_UINT32 ulLevel,
                                   const VOS_CHAR  *pcString);

extern VOS_VOID ADS_MNTN_TraceRcvUlData(VOS_VOID);
extern VOS_VOID ADS_MNTN_TraceSndUlData(VOS_VOID);
extern VOS_VOID ADS_MNTN_TraceRcvDlData(VOS_VOID);

VOS_VOID ADS_ResetDebugInfo(VOS_VOID);

extern VOS_VOID ADS_DLFlowAdd(VOS_UINT8  ucIndex, VOS_UINT32  ulSduLen);
extern VOS_VOID ADS_ULFlowAdd(VOS_UINT8  ucIndex, VOS_UINT32  ulSduLen);
VOS_VOID ADS_SetFlowDebugFlag(VOS_UINT32  ulFlowDebugFlag);
VOS_VOID ADS_SetFlowDLRptThreshold(VOS_UINT32  ulFlowDLRptThreshold);
VOS_VOID ADS_SetFlowULRptThreshold(VOS_UINT32  ulFlowULRptThreshold);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AdsTest.h */
