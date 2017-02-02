

#ifndef __NASLMMPUBMFSM_H__
#define __NASLMMPUBMFSM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "vos.h"
#include    "NasLmmPubMIntraMsg.h"
#include    "AppMmInterface.h"
#include    "NasCommBuffer.h"
#include    "MmcLmmInterface.h"
#include    "NasMmlCtx.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define NAS_LMM_MAX_STACK_DEPTH          8
#define NAS_LMM_STACK_BASE               0
#define NAS_LMM_QUEUE_CLEAR_POSITION     0
#define NAS_LMM_TIMER_NUM                50                  /* �ݶ�50�� */

#define NAS_LMM_MOVEMENT_1_BITS          1
#define NAS_LMM_MOVEMENT_2_BITS          2
#define NAS_LMM_MOVEMENT_3_BITS          3
#define NAS_LMM_MOVEMENT_4_BITS          4
#define NAS_LMM_MOVEMENT_8_BITS          8
#define NAS_LMM_MOVEMENT_16_BITS         16
#define NAS_LMM_MOVEMENT_24_BITS         24



#define NAS_LMM_SEA_TABLE_ERR_LOC        0xFFFF

#define NAS_LMM_STACK_EMPTY              0
#define NAS_LMM_MSG_BUF_EMPTY            0

#define NAS_LMM_MSG_BUF_HEAD_INIT        0
#define NAS_LMM_MSG_BUF_TAIL_INIT        0

#define NAS_LMM_INTRA_MSG_HEAD_INIT      0
#define NAS_LMM_INTRA_MSG_TAIL_INIT      0

#define NAS_LMM_VOS_HEADER_LEN           20

#define NAS_LMM_REJ_CAUSE_IS_12          1
#define NAS_LMM_REJ_CAUSE_NOT_12         0

#define NAS_LMM_MMC_SER_REG_STAT_OPEN_FLAG    1
#define NAS_LMM_MMC_SER_REG_STAT_CLOSE_FLAG   0


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/* ��ȡMM��������ĵĵ�ַ */
#define NAS_LMM_GetMmMainCtxAddr()                   (&g_stMmMainContext)

/* ��ȡMM���״̬�������ַ */
#define NAS_LMM_GetMmFsmAddr()                       (&((NAS_LMM_GetMmMainCtxAddr())->stNasMmFsm))

/* ��ȡĳ����״̬����ǰ״̬�ĵ�ַ */
#define NAS_LMM_GetCurFsmAddr(enParalFsmId)          (&((NAS_LMM_GetMmFsmAddr())->astCurFsm[enParalFsmId]))
/*#define NAS_LMM_GetMmcCurFsmAddr()                   (&((NAS_LMM_GetMmFsmAddr())->astCurFsm[NAS_LMM_PARALLEL_FSM_MMC]))*/
#define NAS_LMM_GetEmmCurFsmAddr()                   (&((NAS_LMM_GetMmFsmAddr())->astCurFsm[NAS_LMM_PARALLEL_FSM_EMM]))
#define NAS_LMM_GetSecuFsmAddr()                     (&((NAS_LMM_GetMmFsmAddr())->astCurFsm[NAS_LMM_PARALLEL_FSM_SECU]))

/* ��ȡĳ����״̬����ǰ״̬����״̬ */
#define NAS_LMM_GetCurFsmMS(enParalFsmId)            ((NAS_LMM_GetCurFsmAddr(enParalFsmId))->enMainState)
/*#define NAS_LMM_GetMmcCurFsmMS()                     ((NAS_LMM_GetMmcCurFsmAddr())->enMainState)*/
#define NAS_LMM_GetEmmCurFsmMS()                     ((NAS_LMM_GetEmmCurFsmAddr())->enMainState)

/* ��ǰ��ȫ������״̬*/
#define NAS_LMM_GetSecuCurFsmCS()                    ((NAS_LMM_GetSecuFsmAddr())->enMainState)

/* ��ȡĳ����״̬����ǰ״̬����״̬ */
#define NAS_LMM_GetCurFsmSS(enParalFsmId)            ((NAS_LMM_GetCurFsmAddr(enParalFsmId))->enSubState)
#define NAS_LMM_GetMmcCurFsmSS()                     ((NAS_LMM_GetMmcCurFsmAddr())->enSubState)
#define NAS_LMM_GetEmmCurFsmSS()                     ((NAS_LMM_GetEmmCurFsmAddr())->enSubState)

/* �°�ȫ������״̬*/
#define NAS_LMM_GetSecuCurFsmNS()                    ((NAS_LMM_GetSecuFsmAddr())->enSubState)

/* ���ð�ȫ������״̬*/
#define NAS_LMM_SetSecuCurFsmCS(CurSta)              (((NAS_LMM_GetSecuFsmAddr())->enMainState) = (CurSta))
#define NAS_LMM_SetSecuCurFsmNS(NewSta)              (((NAS_LMM_GetSecuFsmAddr())->enSubState) = (NewSta))


/* ��ȡĳ����״̬����ǰ״̬�Ķ�ʱ�� */
#define NAS_LMM_GetMmcCurTimer()                     ((NAS_LMM_GetMmcCurFsmAddr())->enStaTId)
#define NAS_LMM_GetEmmCurTimer()                     ((NAS_LMM_GetEmmCurFsmAddr())->enStaTId)


/* ��ȡĳ����״̬����״̬��ջ�ĵ�ַ */
#define NAS_LMM_GetFsmStackAddr(enParalFsmId)        (&((NAS_LMM_GetMmFsmAddr())->astFsmStack[enParalFsmId]))
/*#define NAS_LMM_GetMmcFsmStackAddr()                 (&((NAS_LMM_GetMmFsmAddr())->astFsmStack[NAS_LMM_PARALLEL_FSM_MMC]))*/
#define NAS_LMM_GetEmmFsmStackAddr()                 (&((NAS_LMM_GetMmFsmAddr())->astFsmStack[NAS_LMM_PARALLEL_FSM_EMM]))

/* ��ȡĳ����״̬��������������еĵ�ַ */
#define NAS_LMM_GetFsmBufQueueAddr(enParalFsmId)     (&((NAS_LMM_GetMmFsmAddr())->astFsmMsgBuffer[enParalFsmId]))
/*#define NAS_LMM_GetMmcFsmBufQueueAddr()              (&((NAS_LMM_GetMmFsmAddr())->astFsmMsgBuffer[NAS_LMM_PARALLEL_FSM_MMC]))*/
#define NAS_LMM_GetEmmFsmBufQueueAddr()              (&((NAS_LMM_GetMmFsmAddr())->astFsmMsgBuffer[NAS_LMM_PARALLEL_FSM_EMM]))

/* ��ȡĳ����״̬���Ļ�����еĸ����ȼ���������Ϣ�ĸ����ĵ�ַ */
#define NAS_LMM_GetFsmBufQueueHighCnt(enParalFsmId)  ((NAS_LMM_GetFsmBufQueueAddr(enParalFsmId))->ucHighPrioCnt)
#define NAS_LMM_GetMmcFsmBufQueueHighCnt()           ((NAS_LMM_GetMmcFsmBufQueueAddr())->ucHighPrioCnt)
#define NAS_LMM_GetEmmFsmBufQueueHighCnt()           ((NAS_LMM_GetEmmFsmBufQueueAddr())->ucHighPrioCnt)
/*PC REPLAY MODIFY BY LEILI BEGIN*/
#define NAS_LMM_GetEmmFsmBufQueueMidCnt()           ((NAS_LMM_GetEmmFsmBufQueueAddr())->ucMidPrioCnt)
#define NAS_LMM_GetEmmFsmBufQueueLowCnt()           ((NAS_LMM_GetEmmFsmBufQueueAddr())->ucLowPrioCnt)

/* ��ȡĳ����״̬���Ļ�����еĸ����ȼ����еĵ�ַ */
#define NAS_LMM_GetFsmBufQueueHighAddr(enParalFsmId) (&((NAS_LMM_GetFsmBufQueueAddr(enParalFsmId))->astHighPrioBuffer))
#define NAS_LMM_GetMmcFsmBufQueueHighAddr()          (&((NAS_LMM_GetMmcFsmBufQueueAddr())->astHighPrioBuffer))
#define NAS_LMM_GetEmmFsmBufQueueHighAddr()          ((NAS_LMM_GetEmmFsmBufQueueAddr())->astHighPrioBufQue)
#define NAS_LMM_GetEmmFsmBufQueueMidAddr()           ((NAS_LMM_GetEmmFsmBufQueueAddr())->astMidPrioBufQue)
#define NAS_LMM_GetEmmFsmBufQueueLowAddr()           ((NAS_LMM_GetEmmFsmBufQueueAddr())->astLowPrioBufQue)

/*PC REPLAY MODIFY BY LEILI END*/

/* ��ȡMM����״̬�ĵ�ַ */
#define NAS_LMM_GetMmAuxFsmAddr()                    (&((NAS_LMM_GetMmMainCtxAddr())->stNasMmAuxFsm))

/* MM����״̬��RRC����״̬�ĺ궨�� */
#define NAS_EMM_GetConnState()                      (NAS_LMM_GetMmAuxFsmAddr()->ucRrcConnState)
/* ����ת�����״̬����ͳ��Ser Other Fail���� */
/* mod by yanglei 00307272 for KEY_INFO_REPORT3,2015-08-18,begin */
/* �ж�����״̬�ı����ϱ���Ϣ*/
#define NAS_EMM_SetConnState(ConnState)    \
            {                              \
                NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_SetConnState", ConnState, NAS_EMM_GetConnState()); \
                if(ConnState != NAS_EMM_GetConnState())                                             \
                {                                                                                   \
                    NAS_LMM_SndOmConnstateInfo(ConnState);                                          \
                }                                                                                   \
                NAS_LMM_GetMmAuxFsmAddr()->ucRrcConnState = ConnState;                            \
                NAS_LMM_UpdateSerOtherFailCounter();   \
            }
/* mod by yanglei 00307272 for KEY_INFO_REPORT3,2015-08-18,end */

#define NAS_EMM_UPDATE_STAE                         (NAS_LMM_GetMmAuxFsmAddr()->ucEmmUpStat)
#define NAS_EMM_GetCurLteState()                    (NAS_LMM_GetMmAuxFsmAddr()->ulCurLteState)
#define NAS_LMM_GetNasAppRegState()                 (NAS_LMM_GetMmAuxFsmAddr()->enNasAppRegState)
#define NAS_LMM_SetNasAppRegState(RegState)         (NAS_LMM_GetMmAuxFsmAddr()->enNasAppRegState = RegState)
/* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */


/* ��ȡMM���ڲ���Ϣ���еĵ�ַ */
#define NAS_LMM_GetMmIntrMsgQueueAddr()              (&((NAS_LMM_GetMmMainCtxAddr())->stMmIntraMsgQueue))


/* ��ȡMM��ĳ��״̬��ʱ���ĵ�ַ */
#define NAS_LMM_GetMmTimerStaCtrlAddrByIdx(ucIdx)    (&((NAS_LMM_GetMmMainCtxAddr())->astMmTimerSta[ucIdx]))
#define NAS_LMM_GetMmTimerPtlCtrlAddrByIdx(ucIdx)    (&((NAS_LMM_GetMmMainCtxAddr())->astMmTimerPtl[ucIdx]))

/* ��ȡMM��״̬��ʱ������ĵ�ַ */
#define NAS_LMM_GetStateTimerListAddr()              ((NAS_LMM_GetMmMainCtxAddr())->astMmTimerSta)

/* ��ȡMM��ĳ��״̬��ʱ���ĵ�ַ */
#define NAS_LMM_GET_STATE_TI_INDEX(usIndex)          ((NAS_LMM_GetStateTimerListAddr())[usIndex])

/* ����״̬��ʱ��ID��ȡ���Ӧ�Ķ�ʱ�����ƿ��ַ */
#define NAS_LMM_GetStateTimerAddr(enStateTimerId)    ((enStateTimerId < NAS_LMM_STATE_TI_BUTT)? (&(NAS_LMM_GET_STATE_TI_INDEX(enStateTimerId))) : VOS_NULL_PTR)

/* ��ȡMM��Э�鶨ʱ������ĵ�ַ */
#define NAS_LMM_GetPtlTimerListAddr()                ((NAS_LMM_GetMmMainCtxAddr())->astMmTimerPtl)

/* ��ȡMM��ĳ��Э�鶨ʱ���ĵ�ַ */
#define NAS_LMM_GET_PTL_TI_INDEX(usIndex)            ((NAS_LMM_GetPtlTimerListAddr())[usIndex])

/* ����Э�鶨ʱ��ID��ȡ���Ӧ�Ķ�ʱ�����ƿ��ַ */
#define NAS_LMM_GetPtlTimerAddr(enPtlTimerId)        ((enPtlTimerId < NAS_LMM_PTL_TI_BUTT)? (&(NAS_LMM_GET_PTL_TI_INDEX(enPtlTimerId))) : VOS_NULL_PTR)

/* ����USIM���е���Ϣ�����HPLMN��������
    '00':   No higher priority PLMN search attempts;
    '01':   n minutes;
    '02':   2n minutes;
    ...
    'YZ':   (16Y+Z)n minutes (maximum value)

    6:      n minutes
    1 m = 60 s
    1 s = 1000ms
*/
#define NAS_LMM_GET_MS_FROM_USIM(ucNumberOfUnit)     (ucNumberOfUnit * 6 * 60 * 1000)
#define NAS_LMM_CALC_MS_FROM_USIM(ucMinute)           (((ucMinute / 6) / 60) / 1000)

/* ��ȡEMM��һЩ��Ϣ */
#define NAS_EMM_CUR_MAIN_STAT                       (NAS_LMM_GetEmmCurFsmMS())
#define NAS_EMM_CUR_SUB_STAT                        (NAS_LMM_GetEmmCurFsmSS())
#define NAS_EMM_CUR_STATE_PROTECT_TIMER             (NAS_LMM_GetEmmCurFsmAddr()->enStaTId)

/* ����EMM������ȫ�ֱ������� */
#define NAS_EMM_MAIN_CONTEXT_SET_AUX_UPDATE_STAE(ucEmmUpStat)\
            (NAS_EMM_UPDATE_STAE = ucEmmUpStat)

#define NAS_LMM_ACT_TBL_ITEM(ucSrcPid, ulEventType, pActFun)\
        {\
            (ulEventType),\
            (pActFun)\
        }
/*EMM����ͨ��Ϣ*/
#define NAS_EMM_ACT_TBL_ITEM(ucSrcPid, ulMsgId, pActFun)\
            NAS_LMM_ACT_TBL_ITEM(ucSrcPid, NAS_LMM_GET_BT_MD_ET(ulMsgId), pActFun)

/*EMM��CN��Ϣ*/
#define NAS_EMM_ACT_CN_TBL_ITEM(ucSrcPid, ulCnMsgType, pActFun)\
            NAS_LMM_ACT_TBL_ITEM(ucSrcPid, NAS_LMM_GET_RRC_MM_DATA_IND_CN_ET(ulCnMsgType), pActFun)

/*EMM�Ķ�ʱ����Ϣ*/
#define NAS_EMM_ACT_TI_TBL_ITEM(ucSrcPid, ulMsgId, pActFun)\
            NAS_LMM_ACT_TBL_ITEM(ucSrcPid, NAS_LMM_TIMER_EXP_MSG_ET(ulMsgId), pActFun)


/*MMC����ͨ��Ϣ*/
#define NAS_EMMC_ACT_TBL_ITEM(ucSrcPid, ulMsgId, pActFun)\
            NAS_LMM_ACT_TBL_ITEM(ucSrcPid, NAS_LMM_GET_BT_MD_ET(ulMsgId), pActFun)

/*MMC��CN��Ϣ*/
#define NAS_EMMC_ACT_CN_TBL_ITEM(ucSrcPid, ulCnMsgType, pActFun)\
            NAS_LMM_ACT_TBL_ITEM(ucSrcPid, NAS_LMM_GET_RRC_MM_DATA_IND_CN_ET(ulCnMsgType), pActFun)

/*MMC�Ķ�ʱ����Ϣ*/
#define NAS_EMMC_ACT_TI_TBL_ITEM(ucSrcPid, ulMsgId, pActFun)\
            NAS_LMM_ACT_TBL_ITEM(ucSrcPid, NAS_LMM_TIMER_EXP_MSG_ET(ulMsgId), pActFun)



/* �������״̬,: 0x��_0x�� */
#define NAS_LMM_PUB_COMP_EMMSTATE(usMainStat, usSubStat)\
        ((((VOS_UINT32)(usMainStat)) << NAS_LMM_MOVEMENT_16_BITS) | (usSubStat))
/*leili modify for isr begin*/
#define NAS_LMM_PUB_COMP_BEARERSTATE(ucMmlStat, ucESMStat)\
            (((ucMmlStat) << NAS_LMM_MOVEMENT_8_BITS) | (ucESMStat))

/*leili modify for isr end*/
#define NAS_LMM_STA_TBL_ITEM(usMainState, usSubState, astActTbl)\
        {\
            NAS_LMM_PUB_COMP_EMMSTATE(usMainState, usSubState),\
            ((sizeof(astActTbl))/sizeof(NAS_LMM_ACT_STRU)),\
            (astActTbl)\
        }
#define NAS_EMMC_STA_TBL_ITEM(usMainState, usSubState, astActTbl) \
        NAS_LMM_STA_TBL_ITEM(usMainState, usSubState, astActTbl)

#define NAS_EMM_STA_TBL_ITEM(usMainState, usSubState, astActTbl) \
            NAS_LMM_STA_TBL_ITEM(usMainState, usSubState, astActTbl)


#define NAS_LMM_TIMER_EXP_EVT_SKELETON   \
            (0x00000000UL | (VOS_PID_TIMER << NAS_LMM_MOVEMENT_16_BITS))

/* TIMER EXP MSG =>  EVENT TYPE * */
#define NAS_LMM_TIMER_EXP_MSG_ET(usNasMmTi)\
            (NAS_LMM_TIMER_EXP_EVT_SKELETON | usNasMmTi)



#define NAS_LMM_GetMsgSenderPid(pMsg)                  (((NAS_LMM_MSG_HEADER_STRU*)pMsg)->ulSenderPid)
#define NAS_LMM_GetMsgLength(pMsg)                     (((NAS_LMM_MSG_HEADER_STRU*)pMsg)->ulLength)
#define NAS_LMM_GetMsgId(pMsg)                         (((NAS_LMM_MSG_HEADER_STRU*)pMsg)->ulMsgId)
/*#define NAS_LMM_GetTimerName(pMsg)                     (((REL_TIMER_MSG *)pMsg)->ulName)*/
#define NAS_LMM_GetTimerName(pMsg)                     NAS_LMM_TIMER_EXP_MSG_ET((((REL_TIMER_MSG *)pMsg)->ulName))




#define NAS_LMM_GetNameFromMsg(ulMsgId, pMsg)\
{\
    if(VOS_PID_TIMER == NAS_LMM_GetMsgSenderPid(pMsg))\
    {\
        ulMsgId = NAS_LMM_GetTimerName(pMsg);\
    }\
    else\
    {\
        ulMsgId = NAS_LMM_GetMsgId(pMsg);\
    }\
}


#define NAS_EMM_CHK_STAT_INVALID(EMM_MS,EMM_SS)\
        (\
            NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS,EMM_SS) != \
            NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT, NAS_EMM_CUR_SUB_STAT)\
        )

/* ���APP��Ϣͷ */
#define NAS_LMM_COMP_APP_MSG_HEADER(pMsg, ulMsgLengthNoHeader) \
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
            (pMsg)->ulSenderPid         = PS_PID_MM; \
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
            (pMsg)->ulReceiverPid       = PS_PID_APP; \
            (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
            (pMsg)->usOriginalId        = UE_MODULE_MM_ID;\
            (pMsg)->usTerminalId        = UE_APP_SUBSYS_ID;\
        }

/* ���APP��Ϣͷ */
#if(VOS_WIN32 == VOS_OS_VER)
#define NAS_LMM_COMP_APP_DT_MSG_HEADER(pMsg, ulMsgLengthNoHeader) \
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
            (pMsg)->ulSenderPid         = PS_PID_MM; \
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
            (pMsg)->ulReceiverPid       = PS_PID_APP; \
            (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
            (pMsg)->usOriginalId        = UE_MODULE_MM_ID;\
            (pMsg)->usTerminalId        = UE_APP_SUBSYS_ID;\
        }

#else
#define NAS_LMM_COMP_APP_DT_MSG_HEADER(pMsg, ulMsgLengthNoHeader) \
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
            (pMsg)->ulSenderPid         = PS_PID_MM; \
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
            (pMsg)->ulReceiverPid       = L3_MSP_PID_DT_IND; \
            (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
            (pMsg)->usOriginalId        = UE_MODULE_MM_ID;\
            (pMsg)->usTerminalId        = UE_APP_SUBSYS_ID;\
        }
#endif
/* ����MMCҪ����XXX����Ϣ����, ������VOSͷ(�ⲿ��Ϣ) */
#define NAS_LMM_MSG_LENGTH_NO_HEADER(MM_XXX_MSG_STRU) \
                    (sizeof(MM_XXX_MSG_STRU) - NAS_LMM_VOS_HEADER_LEN)

#define NAS_Emm_Get_Mmc_Srv_Reg_Flag()              g_ulMmcSerRegFlag

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : NAS_LMM_PARALLEL_FSM_ENUM_UINT16
 �ṹ˵��  : MM�㲢��״̬����ʶ
*****************************************************************************/
enum NAS_LMM_PARALLEL_FSM_ENUM
{
    NAS_LMM_PARALLEL_FSM_EMM             = 0x0000,
    /*NAS_LMM_PARALLEL_FSM_MMC                     ,*/
    NAS_LMM_PARALLEL_FSM_SECU                    ,
    NAS_LMM_PARALLEL_FSM_BUTT
};
typedef VOS_UINT16 NAS_LMM_PARALLEL_FSM_ENUM_UINT16;


/*****************************************************************************
 ö����    : NAS_LMM_SERIES_FSM_ID_ENUM
 ö��˵��  : MM���ģ�鲢��״̬���Ĵ���״̬��IDö�ٶ���,
             UE 1.0 ֻ��EMMģ���Լ��Ĵ���״̬��
             UE 1.0 ��û���õ���ö��
*****************************************************************************/
enum NAS_LMM_SERIES_FSM_ID_ENUM
{
    NAS_LMM_SERIES_FSM_BEGIN             = 0x0000,

    /* EMM ״̬���ĸ�����FSM ID */
    NAS_LMM_SERIES_FSM_EMM_IDLE                  ,
    NAS_LMM_SERIES_FSM_EMM                       ,

    /* MMC ״̬���ĸ�����FSM ID */


    NAS_LMM_SERIES_FSM_BUTT
};
typedef VOS_UINT16 NAS_LMM_SERIES_FSM_ID_ENUM_UINT16;



/*****************************************************************************
 �ṹ��    : NAS_LMM_MAIN_STATE_ENUM
 �ṹ˵��  : MM�����в���״̬������״̬��ö�ٶ���
*****************************************************************************/
enum    NAS_LMM_MAIN_STATE_ENUM
{
    /*=================== EMM����״̬ ===================*/
    EMM_MS_NULL                         = 0x0000,
    EMM_MS_DEREG                                ,
    EMM_MS_REG_INIT                             ,           /*ATTACH������״̬*/
    EMM_MS_REG                                  ,
    EMM_MS_TAU_INIT                             ,           /*TAU������״̬*/
    EMM_MS_SER_INIT                             ,           /*SERVICE������״̬*/
    EMM_MS_DEREG_INIT                           ,           /*DETACH������״̬*/

    EMM_MS_AUTH_INIT                            ,           /*AUTH����*/

    EMM_MS_SUSPEND                              ,           /*�������*/
    EMM_MS_RESUME                               ,           /*��ҹ���*/

    /*=================== MMC����״̬ ===================*/
    MMC_MS_NULL                                 ,           /* ��λ��Ŀ�״̬                   */
    MMC_MS_TRYING_PLMN                          ,           /* ��λ�����list��Ч����£���PLMN�͵ȴ�ע����*/
    MMC_MS_TRYING_PLMN_LIST                     ,           /* List��Ч����£������͵ȴ�ע����״̬        */
    MMC_MS_ON_PLMN                              ,           /* ָ��PLMN��ע��ɹ�״̬           */
    MMC_MS_NOT_ON_PLMN                          ,           /* �ȴ��û�ָ��PLMN��ֻ�����ֶ�ģʽ */
    MMC_MS_WAIT_FOR_PLMN                        ,           /* �ȴ�PLMN                         */
    MMC_MS_NO_IMSI                              ,           /* NO SIM״̬                       */


    /*=================== SECU ��CUR ״̬ ===================*/
    EMM_CUR_SECU_NOT_EXIST,   /*17*/
    EMM_CUR_SECU_EXIST_NOT_ACTIVE, /*18*/
    EMM_CUR_SECU_EXIST_ACTIVE, /*19*/



    NAS_LMM_MAIN_STATE_BUTT
};
typedef VOS_UINT16 NAS_LMM_MAIN_STATE_ENUM_UINT16;
typedef NAS_LMM_MAIN_STATE_ENUM_UINT16   NAS_EMM_MAIN_STATE_ENUM_UINT16;
typedef NAS_LMM_MAIN_STATE_ENUM_UINT16   NAS_EMMC_MAIN_STATE_ENUM_UINT16;


/*****************************************************************************
 �ṹ��    : NAS_LMM_SUB_STATE_ENUM
 �ṹ˵��  : MM�����в���״̬������״̬��ö�ٶ���
*****************************************************************************/
enum    NAS_LMM_SUB_STATE_ENUM
{

    /*=================== EMM����״̬ ===================*/

    /*========== NULL�µ���״̬ ===============*/
    EMM_SS_NULL_WAIT_APP_START_REQ      = 0x0000,           /*��״̬��ֻ����APP_START_REQ��Ϣ*/
    /*EMM_SS_WAIT_NULL_READING_SRV_TABLE          ,*/
    EMM_SS_NULL_WAIT_READING_USIM               ,
    /*EMM_SS_NULL_WAITING_USIM_READY              ,*/
    EMM_SS_NULL_WAIT_MMC_START_CNF              ,
    EMM_SS_NULL_WAIT_RRC_START_CNF              ,
    EMM_SS_NULL_WAIT_SWITCH_OFF                 ,
    EMM_SS_NULL_WAIT_MMC_STOP_CNF               ,
    EMM_SS_NULL_WAIT_RRC_STOP_CNF               ,


    /*========== DEREG�µ���״̬ ==============*/
    EMM_SS_DEREG_NORMAL_SERVICE                 ,   /*0x0009*/
    EMM_SS_DEREG_LIMITED_SERVICE                ,
    EMM_SS_DEREG_ATTEMPTING_TO_ATTACH           ,
    EMM_SS_DEREG_PLMN_SEARCH                    ,
    EMM_SS_DEREG_NO_IMSI                        ,
    EMM_SS_DEREG_ATTACH_NEEDED                  ,
    EMM_SS_DEREG_NO_CELL_AVAILABLE              ,

    /*========== ATTACH_INIT����״̬ ==========*/
    EMM_SS_ATTACH_WAIT_ESM_PDN_RSP              ,  /*0x0011*/
    EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF            ,
    EMM_SS_ATTACH_WAIT_MRRC_REL_CNF             ,
    EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF           ,
    EMM_SS_ATTACH_WAIT_RRC_DATA_CNF             ,


    /*========== REG�µ���״̬ ================*/
    EMM_SS_REG_NORMAL_SERVICE                   ,   /*0x0017*/
    EMM_SS_REG_ATTEMPTING_TO_UPDATE             ,
    EMM_SS_REG_LIMITED_SERVICE                  ,
    EMM_SS_REG_PLMN_SEARCH                      ,
    EMM_SS_REG_WAIT_ACCESS_GRANT_IND            ,
    EMM_SS_REG_NO_CELL_AVAILABLE                ,
    EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM          ,
    EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF   ,


    /*========== TAU_INIT����״̬  ============*/
    EMM_SS_TAU_WAIT_CN_TAU_CNF                  ,   /*0x0021*/

    /*========== SER_INIT����״̬ =============*/
    EMM_SS_SER_WAIT_CN_SER_CNF                  ,   /*0x0024*/

    /*========== DETACH_INIT����״̬ ==========*/
    EMM_SS_DETACH_WAIT_CN_DETACH_CNF            ,
    EMM_SS_DETACH_WAIT_MRRC_REL_CNF             ,


    /*========== EMM_MS_RRC_CONN_INIT����״̬ =*/
    EMM_SS_RRC_CONN_WAIT_EST_CNF                ,
    EMM_SS_RRC_CONN_WAIT_REL_CNF                ,


    /*========== AUTH�����е���״̬ ===========*/
    EMM_SS_AUTH_WAIT_CN_AUTH,

    /*========== SUSPEND�����е���״̬ ========*/
    EMM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND,
    EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND,
    EMM_SS_SUSPEND_WAIT_END,
    EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND,
    EMM_SS_SUSPEND_SYSCFGORI_WAIT_OTHER_SUSPEND,

    /*========== RESUME�����е���״̬ ========*/
    EMM_SS_RESUME_RRCRSM_WAIT_OTHER_RESUME,
    EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND,
    EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND,

    /*========== GUTI     ����������״̬  =====*/
    /*========== IDEN     ����������״̬  =====*/
    /*========== SECURITY ����������״̬  =====*/

    /*=================== SECU��NEW״̬ ===================*/
    EMM_NEW_SECU_NOT_EXIST,/*56*/
    EMM_NEW_SECU_EXIST,


    MM_SS_BUTT
};
typedef VOS_UINT16  NAS_LMM_SUB_STATE_ENUM_UINT16;
typedef NAS_LMM_SUB_STATE_ENUM_UINT16    NAS_EMM_SUB_STATE_ENUM_UINT16;
typedef NAS_LMM_SUB_STATE_ENUM_UINT16    NAS_EMMC_SUB_STATE_ENUM_UINT16;


/*****************************************************************************
 ö����    : NAS_LMM_STATE_TI_ENUM
 ö��˵��  : MM�����в���״̬����״̬������ʱ������
             BOUNDARY_START����ʶ��ģ�鶨ʱ���ڶ�ʱ�����е���ʼ�±�;
             BOUNDARY_END����ʶ��ģ�鶨ʱ���ڶ�ʱ�����еĽ����±�;
             ����ģ��Ķ�ʱ��������Ҫ�����ڸ�����Ӧ��������.
*****************************************************************************/
enum NAS_LMM_STATE_TI_ENUM
{
    /*=================== EMM�Ķ�ʱ�� ===================*/

    /*========== ������ʱ�� ===================*/
    TI_NAS_EMM_STATE_NO_TIMER           = 0x0000,           /* �ȶ�״̬���޶�ʱ�� */
    TI_NAS_EMM_STATE_T3440                      ,
    TI_NAS_EMM_STATE_DEL_FORB_TA_PROID          ,            /* ɾ����ֹ��TA */
    /*========== PUBģ�鶨ʱ�� ===================*/
    TI_NAS_LMM_TIMER_WAIT_USIM_CNF               ,
    TI_NAS_LMM_TIMER_WAIT_USIM_READY_START       ,

    /*========== MRRC ģ�鶨ʱ�� ==============*/
    TI_NAS_EMM_STATE_MRRC_BOUNDARY_START        ,           /* MRRC ��ʱ����ʼ�߽� */
    TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF           ,
    TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF            ,

    /*========== ATTACH ģ�鶨ʱ�� ============*/
    TI_NAS_EMM_STATE_REG_BOUNDARY_START         ,           /* REG ��ʱ����ʼ�߽� */
    TI_NAS_EMM_T3410                            ,
   /*TI_NAS_EMM_T3402                          ,*/
    TI_NAS_EMM_WAIT_ESM_PDN_RSP                 ,           /*�ȴ�ESM��PDN��Ӧ*/
    TI_NAS_EMM_WAIT_ESM_BEARER_CNF              ,           /*�ȴ�ESM�ĳ�����Ӧ*/
    TI_NAS_EMM_WAIT_RRC_DATA_CNF                ,           /*�ȴ�RRCֱ����Ϣ����ȷ��*/

    /*========== DETACH ģ�鶨ʱ�� ============*/
    TI_NAS_EMM_STATE_DEREG_BOUNDARY_START       ,           /* DEREG ��ʱ����ʼ�߽� */
    TI_NAS_EMM_T3421                            ,

    /*========== TAU ģ�鶨ʱ�� ===============*/
    TI_NAS_EMM_STATE_TAU_BOUNDARY_START         ,           /* TAU ��ʱ����ʼ�߽� */
    TI_NAS_EMM_STATE_TAU_T3430                  ,

    /*========== SERVICE ģ�鶨ʱ�� ===========*/
    TI_NAS_EMM_STATE_SERVICE_BOUNDARY_START     ,           /* SERVICE ��ʱ����ʼ�߽� */
    TI_NAS_EMM_STATE_SERVICE_T3417              ,
    TI_NAS_EMM_STATE_SERVICE_T3417_EXT          ,
    TI_NAS_EMM_STATE_SERVICE_T3442              ,

    /*========== PLMN ģ�鶨ʱ�� ==============*/
    TI_NAS_EMM_STATE_PLMN_BOUNDARY_START        ,           /* PLMN ��ʱ����ʼ�߽� */
    TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER         ,
    TI_NAS_EMM_WAIT_RRC_START_CNF_TIMER         ,
    TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER          ,
    TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER          ,

    /*========== AUTH ģ�鶨ʱ�� ==============*/
    TI_NAS_EMM_STATE_AUTH_BOUNDARY_START        ,           /* AUTH ��ʱ����ʼ�߽� */
    TI_NAS_EMM_T3418                            ,
    TI_NAS_EMM_T3420                            ,

    /*========== SUSPEND��ʱ�� ================*/
    TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER   ,
    TI_NAS_EMM_WAIT_SUSPEND_END_TIMER           ,
    TI_NAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER   ,
    TI_NAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER   ,


    /*========== RESEUME��ʱ�� ================*/
    TI_NAS_EMM_RRCRSM_WAIT_OTHER_RESUME_RSP_TIMER     ,
    TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER         ,
    TI_NAS_EMM_SYSCFGRSM_WAIT_OTHER_RESUME_RSP_TIMER,

    /*========== SYSCFG�Ķ�ʱ�� ============================*/
    TI_NAS_EMM_STATE_WAIT_SYSCFG_CNF_TIMER,

    TI_NAS_EMM_STATE_TI_BUTT                    ,

    /*========== MMC�Ķ�ʱ�� ============================*/
    /*========== PLMN_SRCH�Ķ�ʱ�� ============================*/
    TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER,

    TI_NAS_EMMC_STATE_TI_BUTT                    ,

    /*========== END ====================================*/
    NAS_LMM_STATE_TI_BUTT
};
typedef VOS_UINT16 NAS_LMM_STATE_TI_ENUM_UINT16;
typedef NAS_LMM_STATE_TI_ENUM_UINT16     NAS_EMM_STATE_TI_ENUM_UINT16;
typedef NAS_LMM_STATE_TI_ENUM_UINT16     NAS_EMMC_STATE_TI_ENUM_UINT16;


/*****************************************************************************
 ö����    : NAS_LMM_PTL_TI_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : Э�鶨ʱ���͹��ܶ�ʱ�� ����
             BOUNDARY_START����ʶ��ģ�鶨ʱ���ڶ�ʱ�����е���ʼ�±�;
             BOUNDARY_END����ʶ��ģ�鶨ʱ���ڶ�ʱ�����еĽ����±�;
             ����ģ��Ķ�ʱ��������Ҫ�����ڸ�����Ӧ��������.
*****************************************************************************/
enum NAS_LMM_PTL_TI_ENUM
{
    /*=================== EMM�Ķ�ʱ�� ===================*/

    /*========== ������ʱ�� ===================*/
    TI_NAS_LMM_PTL_TI_PUB_BOUNDARY_START = NAS_LMM_STATE_TI_BUTT,


    /*========== ATTACH ģ�鶨ʱ�� ============*/
    /*========== DETACH ģ�鶨ʱ�� ============*/
    /*========== TAU ģ�鶨ʱ�� ===============*/
    TI_NAS_EMM_PTL_T3411                        ,
    TI_NAS_EMM_PTL_T3412                        ,
    TI_NAS_EMM_PTL_T3402                        ,
    TI_NAS_EMM_PTL_T3423                        ,

    /*========== AUTH ģ�鶨ʱ�� ===============*/
    TI_NAS_EMM_PTL_T3416                        ,

    /*========== �ػ���ʱ�� ===================*/
    TI_NAS_EMM_PTL_SWITCH_OFF_TIMER             ,

    /*========== attach��ʱ��ʱ�� =============*/
    TI_NAS_EMM_PTL_REATTACH_DELAY               ,

    /*========== CSFB��ʱ��ʱ�� ===============*/
    TI_NAS_EMM_PTL_CSFB_DELAY               ,

    TI_NAS_EMM_PTL_T3346                        ,
    TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER            ,       /* ���������ͷ���ʱ�� */
    TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER      ,       /* ���������ϻ���ʱ�� */
    TI_NAS_EMM_PTL_TI_BUTT                      ,

    /*========== MMC�Ķ�ʱ�� ==================*/
    NAS_LMM_PTL_TI_BUTT
};
typedef VOS_UINT16 NAS_LMM_PTL_TI_ENUM_UINT16;

/*****************************************************************************
 ö����    : NAS_LMM_TIMER_RUN_STATE_ENUM
 ö��˵��  : MM���״̬������ʱ�������б�ʶ
             Timer�������(����ЩTimer������)
*****************************************************************************/
enum NAS_LMM_TIMER_RUN_STATE_ENUM
{
    NAS_LMM_TIMER_RS_NOT_RUNNING         = 0,                /*NO RUNNING*/
    NAS_LMM_TIMER_RS_RUNNING                ,                /*RUNNING*/

    NAS_LMM_TIMER_RS_BUTT
};
typedef VOS_UINT8 NAS_LMM_TIMER_RUN_STATE_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_LMM_TIMER_RUN_STATE_ENUM
 ö��˵��  : MM���״̬������ʱ�������б�ʶ
             Timer������(����ЩTimer������)
*****************************************************************************/
enum NAS_LMM_TIMER_SUS_STATE_ENUM
{
    NAS_LMM_TIMER_SS_NOT_SUSPENDING      = 0,                /*NO SUSPEND*/
    NAS_LMM_TIMER_SS_SUSPENDING             ,                /*SUSPEND*/

    NAS_LMM_TIMER_SS_BUTT
};
typedef VOS_UINT8 NAS_LMM_TIMER_SUS_STATE_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_LMM_TIMER_RUN_STATE_ENUM
 ö��˵��  : MM���״̬������ʱ�������б�ʶ
             Timerʱ�����±��(����ЩTimerʱ��������)
             ���տ���Ϣ�и��¶�ʱ��ʱ��ʱ, NAS_EMM_TIMER_VALUE_STATE_ENUM ����1,
             ��ʱ������ʱ�ж�;
             �类��λ�������OS API����ʱ��������NAS_EMM_TIMER_VALUE_STATE_ENUM
             ���㣬Ȼ��������;
*****************************************************************************/
enum NAS_LMM_TIMER_VALUE_STATE_ENUM
{
    NAS_LMM_TIMER_VS_NOT_NEED_TO_UPDATE  = 0,                /* NO NEED TO UPDATE */
    NAS_LMM_TIMER_VS_NEED_TO_UPDATE         ,                /* NEED TO UPDATE */

    NAS_LMM_TIMER_VS_BUTT
};
typedef VOS_UINT8 NAS_LMM_TIMER_VALUE_STATE_ENUM_UINT8;



enum    NAS_EMM_UPDATE_STATE_ENUM
{
    EMM_US_UPDATED_EU1                  = 0x00,             /* UPDATED */
    EMM_US_NOT_UPDATED_EU2              = 0x01,             /* NOT UPDATED */
    EMM_US_ROAMING_NOT_ALLOWED_EU3      = 0x02,             /* ROAMING NOT ALLOWED */

    EMM_US_BUTT
};
typedef VOS_UINT8  NAS_EMM_UPDATE_STATE_ENUM_UINT8;


enum    NAS_EMM_RRC_CONN_STATE_ENUM
{
    NAS_EMM_CONN_IDLE                   = 0x00,
    NAS_EMM_CONN_ESTING                 = 0x01,
    NAS_EMM_CONN_SIG                    = 0x02,
    NAS_EMM_CONN_DATA                   = 0x03,
    NAS_EMM_CONN_RELEASING              = 0X04,  /* �ͷŹ����У�LMM�ڲ�ʹ�õ�RRC����״̬������MMC��˵��ͬIDLE */
    NAS_EMM_CONN_WAIT_SYS_INFO          = 0X05,  /* ��ʾ�յ���RRC_IND����RRC_CNF֮�󣬵ȴ�RRCϵͳ��Ϣ�Ĺ���*/

    NAS_EMM_CONN_BUTT
};
typedef VOS_UINT8  NAS_EMM_RRC_CONN_STATE_ENUM_UINT8;


enum    NAS_EMM_USIM_STATE_ENUM
{
    EMM_USIM_STATE_VALID                = 0x00,
    EMM_USIM_STATE_INVALID              = 0x01,

    EMM_USIM_STATE_BUTT
};
typedef VOS_UINT8  NAS_EMM_USIM_STATE_ENUM_UINT8;


enum NAS_APP_REG_STAT_ENUM
{
    NAS_APP_RS_NOT_REG_AND_NOT_SRCH_OPERATOR    = APP_REG_STAT_NOT_REG_AND_NOT_SRCH_OPERATOR,
    NAS_APP_RS_REG_HPLMN                        = APP_REG_STAT_REG_HPLMN ,
    NAS_APP_RS_NOT_REG_AND_SRCH_OPERATOR        = APP_REG_STAT_NOT_REG_AND_SRCH_OPERATOR,
    NAS_APP_RS_REG_DENIED                       = APP_REG_STAT_REG_DENIED,
    NAS_APP_RS_UNKNOWN                          = APP_REG_STAT_UNKNOWN,
    NAS_APP_RS_REG_ROAMING                      = APP_REG_STAT_REG_ROAMING,
    NAS_APP_RS_BUTT
};
typedef VOS_UINT32  NAS_APP_REG_STAT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_EMM_REG_CHANGE_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LMM�ϱ���register status
*****************************************************************************/
enum NAS_EMM_REG_CHANGE_TYPE_ENUM
{
    NAS_EMM_REG_CHANGE_TYPE_REG_STATE    = 0,
    NAS_EMM_REG_CHANGE_TYPE_LOCATION_INFO,
    NAS_EMM_REG_CHANGE_TYPE_BUTT
};
typedef VOS_UINT32 NAS_EMM_REG_CHANGE_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ����:  NAS_LMM_CUR_LTE_STATE_ENUM_UINT32
 Э����:  NO CELL״̬�£���LTE����״̬������LTE����ʱ������ NO CELL̬
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
enum    NAS_LMM_CUR_LTE_STATE_ENUM
{
    NAS_LMM_CUR_LTE_SUSPEND          = 0x00,
    NAS_LMM_CUR_LTE_ACTIVE           = 0x01,

    NAS_LMM_CUR_LTE_BUTT
};
typedef VOS_UINT32  NAS_LMM_CUR_LTE_STATE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_LMM_TIMER_RUN_STATE_ENUM
 ö��˵��  : MM��Timer���ͱ�ʶ
*****************************************************************************/

enum NAS_LMM_TIMER_TYPE_ENUM
{
    NAS_LMM_STATE_TIMER                  ,             /* ״̬��ʱ�� */
    NAS_LMM_PTL_TIMER                    ,                   /* Э�鶨ʱ�� */

    NAS_LMM_TIMER_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LMM_TIMER_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : NAS_LMM_RAT_TYPE_ENUM_UINT8
 �ṹ˵��  :
*****************************************************************************/
enum NAS_LMM_RAT_TYPE_ENUM
{
    NAS_LMM_RAT_TYPE_GSM = 0,                           /* GSM���뼼�� */
    NAS_LMM_RAT_TYPE_WCDMA,                             /* WCDMA���뼼�� */
    NAS_LMM_RAT_TYPE_LTE,                               /* LTE���뼼�� */
    NAS_LMM_RAT_TYPE_CDMA1X,                            /* 1x���뼼��*/
    NAS_LMM_RAT_TYPE_HRPD,                              /* HRPD���뼼��*/
    NAS_LMM_RAT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LMM_RAT_TYPE_ENUM_UINT8;


/*****************************************************************************
 �ṹ��    : NAS_LMM_RAT_PRIO_ENUM_UINT8
 �ṹ˵��  :
*****************************************************************************/
enum NAS_LMM_RAT_PRIO_ENUM
{
    NAS_LMM_RAT_PRIO_NULL                = 0,               /* �ý��뼼��������    */
    NAS_LMM_RAT_PRIO_LOW                 = 1,               /* ���ȼ��ϵ�   */
    NAS_LMM_RAT_PRIO_MIDDLE              = 2,               /* ���ȼ��м�   */
    NAS_LMM_RAT_PRIO_HIGH                = 3,               /* ���ȼ��ϸ�   */
    NAS_LMM_RAT_PRIO_BUTT
};
typedef VOS_UINT8  NAS_LMM_RAT_PRIO_ENUM_UINT8;
/*leili modify for isr begin*/
enum NAS_EMM_BEARER_STATE_ENUM
{
    NAS_EMM_BEARER_STATE_INACTIVE = 0,                                       /* ������ȥ����״̬ */
    NAS_EMM_BEARER_STATE_ACTIVE,                                             /* �����ļ���״̬ */
    NAS_EMM_BEARER_STATE_BUTT
};
typedef VOS_UINT8 NAS_EMM_BEARER_STATE_ENUM_UINT8;
/*leili modify for isr end*/
/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : NAS_LMM_BUFF_MSG_STRU
 �ṹ˵��  : NAS MM������Ϣ���нṹ�����������������װ������Ϣ��
             ulEvtType   : ������Ϣ������
             pBuffMsg    : ������Ϣ�ĵ�ַ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulEvtType;                             /* ������Ϣ��Ӧ���¼� PID + MSGTYPE */
    VOS_VOID                            *pBuffMsg;                              /* ������Ϣָ�� */
}NAS_LMM_BUFF_MSG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_FSM_MSG_BUF_STRU
 �ṹ˵��  : ��������Ϣ�ṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHighPrioCnt;      /* �����ȼ���Ϣ���� */
    VOS_UINT8                           ucMidPrioCnt;       /* �����ȼ���Ϣ���� */
    VOS_UINT8                           ucLowPrioCnt;       /* �����ȼ���Ϣ���� */
    VOS_UINT8                           ucRsrv;             /* �ֽڶ��룬���� */

    NAS_LMM_BUFF_MSG_STRU                astHighPrioBufQue[NAS_EMM_BUF_MSG_MAX_NUM];
    NAS_LMM_BUFF_MSG_STRU                astMidPrioBufQue[NAS_EMM_BUF_MSG_MAX_NUM];
    NAS_LMM_BUFF_MSG_STRU                astLowPrioBufQue[NAS_EMM_BUF_MSG_MAX_NUM];
}NAS_LMM_FSM_MSG_BUF_STRU;


/*****************************************************************************
 �ṹ��    : NAS_EMM_FSM_STATE_STRU
 �ṹ˵��  : ״̬��״̬�����ṹ
*****************************************************************************/
typedef struct
{
    NAS_LMM_PARALLEL_FSM_ENUM_UINT16     enFsmId;            /* ״̬����ʶ */
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;        /* ��״̬ */
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSubState;         /* ��״̬ */
    NAS_LMM_STATE_TI_ENUM_UINT16         enStaTId;           /* ״̬��ʱ��ID,������ǰ״̬�Ķ�ʱ�� */

}NAS_LMM_FSM_STATE_STRU;
typedef NAS_LMM_FSM_STATE_STRU           NAS_EMM_FSM_STATE_STRU;
typedef NAS_LMM_FSM_STATE_STRU           NAS_EMMC_FSM_STATE_STRU;

/*****************************************************************************
 �ṹ��    : NAS_EMM_FSM_STATE_STACK_STRU
 �ṹ˵��  : ״̬��ջ�����ṹ
             ����ѹ��ջ�ĵ�K��״̬������ astFsmStack[K-1]��λ�ã�
             ucStackDepth Ϊ��ǰѹջ��״̬������
             ջ��Ϊ��,����astFsmStack[ucStackDepth]Ϊ�գ�����һ����ջ�����λ�ã�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT8                           ucStackDepth;                           /* ��ǰѹջ��״̬���� */
    NAS_EMM_FSM_STATE_STRU              astFsmStack[NAS_LMM_MAX_STACK_DEPTH];    /* ״̬��ջ����� */
}NAS_LMM_FSM_STATE_STACK_STRU;
typedef NAS_LMM_FSM_STATE_STACK_STRU     NAS_EMM_FSM_STATE_STACK_STRU;
typedef NAS_LMM_FSM_STATE_STACK_STRU     NAS_EMMC_FSM_STATE_STACK_STRU;




/*****************************************************************************
 �ṹ��    : NAS_LMM_COMM_ACTION_FUN
 �ṹ˵��  : MM���������������Ͷ��壬Ŀǰ���ڳ�ʼ������
*****************************************************************************/
typedef VOS_UINT32  ( * NAS_LMM_COMM_ACTION_FUN )( MsgBlock  *  /* ��Ϣָ�� */);

typedef VOS_UINT32  ( * NAS_EMMC_COMM_ACTION_FUN )( MsgBlock  *  /* ��Ϣָ�� */);

/*****************************************************************************
 �ṹ��    : NAS_LMM_COMM_ACT_STRU
 �ṹ˵��  : MM������ṹ��Ŀǰ���ڳ�ʼ������
*****************************************************************************/
typedef VOS_UINT32  MM_MSG_TYPE_ENUM_UINT32;

typedef struct
{
    MM_MSG_TYPE_ENUM_UINT32             ulMsgId;     /* ��ϢID */
    VOS_UINT32                          ulSenderPid;
    NAS_LMM_COMM_ACTION_FUN              pfFun;     /* ��Ϣ������ */
}NAS_LMM_COMM_ACT_STRU;

typedef struct
{
    MM_MSG_TYPE_ENUM_UINT32              ulMsgId;     /* ��ϢID */
    VOS_UINT32                           ulSenderPid;
    NAS_LMM_COMM_ACTION_FUN              pfFun;       /* ��Ϣ������ */
}NAS_EMMC_COMM_ACT_STRU;



/*****************************************************************************
 �ṹ��    : NAS_LMM_FSM_STRU
 �ṹ˵��  : ��Ÿ���״̬��
*****************************************************************************/
typedef struct
{
    NAS_LMM_FSM_STATE_STRU               astCurFsm[NAS_LMM_PARALLEL_FSM_BUTT];   /* ״̬��*/
    NAS_LMM_FSM_STATE_STACK_STRU         astFsmStack[NAS_LMM_PARALLEL_FSM_BUTT]; /* ״̬����״̬��ջ������   */
    NAS_LMM_FSM_MSG_BUF_STRU             astFsmMsgBuffer[NAS_LMM_PARALLEL_FSM_BUTT];/* ��״̬���������Ϣ������ */
} NAS_LMM_FSM_STRU;



/* �����쳣����ԭ�� */
typedef VOS_UINT32 ( * NAS_LMM_EXCEP_FUN )
(
    VOS_UINT32, /* EVENT ID,����PID��MSG ID */
    VOS_VOID *  /* ��Ϣָ�� */
);

/* ���������������Ͷ��� */
typedef VOS_UINT32 ( * NAS_LMM_ACTION_FUN )
(
    VOS_UINT32, /* ��ϢID   */
    VOS_VOID *  /* ��Ϣָ�� */
);


/* ������ṹ */
typedef struct
{
    VOS_UINT32                          ulEventType;        /* �¼����� */
    NAS_LMM_ACTION_FUN                   pfActionFun;        /* �������� */
}NAS_LMM_ACT_STRU;
typedef NAS_LMM_ACT_STRU                 NAS_EMM_ACT_STRU;
typedef NAS_LMM_ACT_STRU                 NAS_EMMC_ACT_STRU;


/* ״̬ת�Ʊ�ṹ */
typedef struct
{
    VOS_UINT32                          ulState;            /* ״̬                                */
    VOS_UINT32                          ulSize;             /* ������Ĵ�С�ֽ�������ACT�ṹ�Ĵ�С */
    NAS_LMM_ACT_STRU                    *pActTable;          /* ������Ļ���ַ                      */
}NAS_LMM_STA_STRU;
typedef NAS_LMM_STA_STRU                 NAS_EMM_STA_STRU;
typedef NAS_LMM_STA_STRU                 NAS_EMMC_STA_STRU;


/* ����״̬���������ṹ */
typedef struct
{
    NAS_LMM_STA_STRU*                    pStaTable;          /* ״̬ת�Ʊ�Ļ���ַ     */
    VOS_UINT32                          ulSize;             /* ״̬ת�Ʊ�Ĵ�С       */
    VOS_UINT32                          aulMmParaFsmId;     /* ��������״̬����ID       */
    NAS_LMM_EXCEP_FUN                    pfExceptHandle;     /* ���ڴ����쳣�Ļص����� */
}NAS_LMM_FSM_DESC_STRU;

/* ��Ϣͷ���� */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
}NAS_LMM_MSG_HEADER_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LMM_AUXILIARY_FSM_STRU
 �ṹ˵��  : EMM�ĸ���״̬��
*****************************************************************************/
typedef struct
{
    NAS_EMM_UPDATE_STATE_ENUM_UINT8     ucEmmUpStat;    /* EMM UPDATE STATE */
    NAS_EMM_RRC_CONN_STATE_ENUM_UINT8   ucRrcConnState; /* ��ǰRRC�����Ƿ���� */
    VOS_UINT8                           aucRsv[2];
    NAS_APP_REG_STAT_ENUM_UINT32        enNasAppRegState;
/* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
    NAS_LMM_CUR_LTE_STATE_ENUM_UINT32   ulCurLteState;
/* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */

}NAS_LMM_AUXILIARY_FSM_STRU;



/*****************************************************************************
 �ṹ��    : NAS_LMM_TIMER_CTRL_STRU
 �ṹ˵��  : NAS_LMM ��ʱ���ṹ

             ���еĲ������յ���TIMER�ĳ�ʱ��Ϣ�еĲ����Ķ�Ӧ:
             �μ�:  REL_TIMER_MSG

��ʱ��ֹͣʱ: NAS_LMM_TIMER_RUN_STATE_ENUM_UINT8����0,
              NAS_LMM_TIMER_SUS_STATE_ENUM_UINT8����0;

��ʱ������ʱ: NAS_LMM_TIMER_RUN_STATE_ENUM_UINT8����1,
              NAS_LMM_TIMER_SUS_STATE_ENUM_UINT8����0;

��ʱ����ͣʱ: NAS_LMM_TIMER_RUN_STATE_ENUM_UINT8����1,
              NAS_LMM_TIMER_SUS_STATE_ENUM_UINT8����1,

���տ���Ϣ�и��¶�ʱ��ʱ��ʱ, usTimerValMask����λ, ��ʱ������ʱ�ж�;
�类��λ�������OS API����ʱ��������usTimerSusMask���㣬Ȼ��������;
*****************************************************************************/
typedef struct
{

    HTIMER                              psthTimer;          /* Timer��� */
    VOS_UINT32                          ulName;             /* �� NAS_LMM_STATE_TI_ENUM_UINT16*/
    VOS_UINT32                          ulParam;            /* ��ģ���Լ�������д��Ҳ���Բ��� */
    VOS_UINT32                          ulTimerLen;         /* Timerʱ��(UNIT: ms) */
    VOS_UINT32                          ulTimerRemainLen;   /* Timer��ͣ״̬�µ�ʣ��ʱ��(UNIT: ms),ֻ�е�
                                                               ucTimerSs == NAS_LMM_TIMER_SS_SUSPENDING ʱ��Ч*/
    VOS_UINT8                           ucMaxNum;           /* ��ʱ����ʱ������(N) */
    VOS_UINT8                           ucExpedNum;         /* �ѳ�ʱ���� */
    VOS_UINT8                           ucMode;             /* timer work mode
                                                               VOS_RELTIMER_LOOP   -- start periodically
                                                               VOS_RELTIMER_NOLOOP -- start once time */
    NAS_LMM_TIMER_TYPE_ENUM_UINT8        ucTimerType;        /* NAS_LMM_STATE_TIMER����NAS_LMM_PTL_TIMER */
    NAS_LMM_TIMER_RUN_STATE_ENUM_UINT8   ucTimerRs;
    NAS_LMM_TIMER_SUS_STATE_ENUM_UINT8   ucTimerSs;
    NAS_LMM_TIMER_VALUE_STATE_ENUM_UINT8 ucTimerVs;          /* UE 1.0 �ݲ�ʹ�� */

    VOS_UINT8                           ucRsv;

}NAS_LMM_TIMER_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LMM_MAIN_CONTEXT_STRU
 �ṹ˵��  : MM ģ������������
*****************************************************************************/
typedef struct
{
    /**************************************************************************
                        NAS_LMM ״̬��״̬����״̬ջ
    **************************************************************************/
    NAS_LMM_FSM_STRU                     stNasMmFsm;

    /**************************************************************************
                        NAS_LMM ����״̬
    **************************************************************************/
    NAS_LMM_AUXILIARY_FSM_STRU           stNasMmAuxFsm;

    /**************************************************************************
                        NAS_LMM ״̬��ʱ�����Ʊ�
    **************************************************************************/
    NAS_LMM_TIMER_CTRL_STRU              astMmTimerSta[NAS_LMM_STATE_TI_BUTT];

    /**************************************************************************
                        NAS_LMM Э�鶨ʱ�����Ʊ�
    **************************************************************************/
    NAS_LMM_TIMER_CTRL_STRU              astMmTimerPtl[NAS_LMM_PTL_TI_BUTT];



    /**************************************************************************
                        �ڲ���Ϣ���д洢��
    **************************************************************************/
    NAS_LMM_INTRA_MSG_QUEUE_STRU         stMmIntraMsgQueue;

}NAS_LMM_MAIN_CONTEXT_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern  NAS_LMM_MAIN_CONTEXT_STRU        g_stMmMainContext;
extern  NAS_LMM_FSM_DESC_STRU            g_astNasMmFsmDesc[NAS_LMM_PARALLEL_FSM_BUTT];
extern  VOS_UINT32                       g_ulMmcSerRegFlag;
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32   NAS_LMM_FsmRegisterFsm(     NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParaFsmId,
                                               VOS_UINT32                      ulSize,
                                               NAS_LMM_STA_STRU                *pStaTable,
                                               NAS_LMM_EXCEP_FUN                pfExceptHandle );

extern VOS_UINT32   NAS_LMM_FsmProcessEvent(    NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId,
                                               VOS_UINT32                      ulEventType,
                                               VOS_UINT32                      ulMsgID,
                                               VOS_UINT8                      *pRcvMsg );
extern NAS_LMM_ACTION_FUN   NAS_LMM_FsmFindAct(  const NAS_LMM_FSM_DESC_STRU   *pFsmDesc,
                                               VOS_UINT32              ulState,
                                               VOS_UINT32              ulEventType);

extern VOS_VOID    NAS_LMM_FsmGetEvtTab(        const NAS_LMM_FSM_DESC_STRU   *pFsmDesc,
                                               VOS_UINT32             *pulStaTblLoc);


extern VOS_VOID    NAS_LMM_FsmGetEvtStatFun(    const NAS_LMM_FSM_DESC_STRU   *pFsmDesc,
                                               VOS_UINT32              ulFsmStaTblLoc,
                                               VOS_UINT32              ulEventType,
                                               VOS_UINT32             *pulEmmActTblLoc);

extern VOS_VOID     NAS_LMM_FsmTranState(       NAS_LMM_FSM_STATE_STRU  stDestState);
extern VOS_UINT32   NAS_LMM_MsgProcessInFsm(    NAS_LMM_PARALLEL_FSM_ENUM_UINT16  enParalFsmId,
                                               MsgBlock                        *pMsg,
                                               VOS_UINT32                       ulMsgId,
                                               VOS_UINT32                       ulEventType );
extern  VOS_UINT32  NAS_LMM_ClearOnePtlTimer(   NAS_LMM_PTL_TI_ENUM_UINT16    usTi);
extern  VOS_UINT32  NAS_LMM_ClearOneStaTimer(   NAS_LMM_STATE_TI_ENUM_UINT16  usTi);
extern  NAS_LMM_COMM_ACTION_FUN  NAS_LMM_CommFindFun(
                                                const NAS_LMM_COMM_ACT_STRU   *pastMap,
                                                VOS_UINT32              ulMapNum,
                                                VOS_UINT32              ulMsgId,
                                                VOS_UINT32              ulSenderPid);

extern  NAS_EMMC_COMM_ACTION_FUN  NAS_EMMC_CommFindFun(
                                        const NAS_EMMC_COMM_ACT_STRU   *pastMap,
                                        VOS_UINT32              ulMapNum,
                                        VOS_UINT32              ulMsgId,
                                        VOS_UINT32              ulSenderPid);
extern  VOS_VOID  NAS_LMM_AppStateChange( NAS_EMM_FSM_STATE_STRU  stEmmDestState);
extern  VOS_VOID  NAS_LMM_StateMap(const NAS_EMM_FSM_STATE_STRU *pstEmmDestState,
                            NAS_APP_REG_STAT_ENUM_UINT32   *pulNasAppDstState);
extern VOS_VOID  NAS_LMM_RegStatOsa(const NAS_APP_REG_STAT_ENUM_UINT32   *pulNasAppDstState,
                               APP_REG_STAT_ENUM_UINT32       *pulAppRegStat);
extern VOS_VOID  NAS_LMM_StaTransProc( NAS_LMM_FSM_STATE_STRU  stDestState );
/* lihong00150010 emergency tau&service begin */
extern VOS_VOID  NAS_LMM_EnterDeregStateModify
(
    NAS_LMM_FSM_STATE_STRU              *pstDestState
);
/* lihong00150010 emergency tau&service end */
extern VOS_VOID  NAS_LMM_ActionBeforeTransToDestSta( NAS_LMM_FSM_STATE_STRU  stDestState );
extern VOS_UINT32  NAS_LMM_GetServiceDomain(NAS_LMM_MAIN_STATE_ENUM_UINT16  enMainState);
/* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
extern VOS_VOID NAS_LMM_SndOmLogStateChange(NAS_LMM_FSM_STATE_STRU *pstCurState, NAS_LMM_FSM_STATE_STRU *pstDestState);
/* ����ת�����״̬����ͳ��Ser Other Fail���� */
extern VOS_VOID NAS_LMM_UpdateSerOtherFailCounter(VOS_VOID);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmPubMFsm.h*/
