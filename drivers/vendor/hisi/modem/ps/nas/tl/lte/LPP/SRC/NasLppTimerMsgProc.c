

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "PsCommonDef.h"
#include    "NasLppTimerMsgProc.h"
#include    "NasLppPublic.h"
#include    "NasLppEmmMsgProc.h"
#include    "NasLppLrrcMsgProc.h"
#include    "NasLppOm.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
#define    THIS_FILE_ID            PS_FILE_ID_NASLPPTIMERMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPTIMERMSGPROC_C




#if (FEATURE_LPP == FEATURE_ON)


/*****************************************************************************
  3 Function
*****************************************************************************/
extern VOS_VOID  NAS_LPP_ConnFailHandle(VOS_VOID);
extern VOS_VOID  NAS_LPP_SndUpLppAbortMsg
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx,
    LPP_COMMON_IES_ABORT_ENUM_UINT8     enAbortCause,
    VOS_BOOL                            enNeedAck,
    VOS_BOOL                            bEndTransaction
);
/*****************************************************************************
 Function Name   : NAS_LPP_TimerInit
 Description     : ��ʱ���ĳ�ʼ��
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-7-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_TimerInit( VOS_VOID )
{

    NAS_LPP_TimerReg(TI_NAS_LPP_UPLINK_MSG_RETRANS  , NAS_LPP_RcvUpMsgRetransTimer,      TI_NAS_LPP_UPLINK_MSG_RETRANS_TIMER_LEN    );
    NAS_LPP_TimerReg(TI_NAS_LPP_WAIT_CN_ASSIST_DATA , NAS_LPP_RcvWaitCnAssistDataTimer,  TI_NAS_LPP_WAIT_CN_ASSIST_DATA_TIMER_LEN    );
    NAS_LPP_TimerReg(TI_NAS_LPP_WAIT_LRRC_MEAS_CNF  , NAS_LPP_RcvWaitLrrcMeasCnfTimer,   TI_NAS_LPP_WAIT_LRRC_MEAS_CNF_TIMER_LEN    );
    NAS_LPP_TimerReg(TI_NAS_LPP_WAIT_GNSS_CAP_CNF   , NAS_LPP_RcvWaitGnssCapCnfTimer,    TI_NAS_LPP_WAIT_GNSS_CAP_TIMER_LEN   );
    NAS_LPP_TimerReg(TI_NAS_LPP_WAIT_INTRA_DATE_CNF , NAS_LPP_RcvIntraDataCnfTimerExpire,NAS_LPP_GetLppIntraDataCnfTimerLen()  );
    NAS_LPP_TimerReg(TI_NAS_LPP_WAIT_EST_CNF        , NAS_LPP_RcvWaitEstCnfTimer,        TI_NAS_LPP_WAIT_EST_CNF_TIMER_LEN  );
    NAS_LPP_TimerReg(TI_NAS_LPP_WAIT_RE_EST         , NAS_LPP_RcvWaitReEstTimer,         0  );

    NAS_LPP_TimerReg(TI_NAS_LPP_RESPONSE_TIMER      , NAS_LPP_RcvWaitResponseTimer,      0  );
    NAS_LPP_TimerReg(TI_NAS_LPP_PERIODICAL_REPORT   , NAS_LPP_RcvWaitPeriodicalTimer,    0  );
    NAS_LPP_TimerReg(TI_NAS_LPP_REPORT_DURATION     , NAS_LPP_RcvWaitReportDurationTimer,0  );
    NAS_LPP_TimerReg(TI_NAS_LPP_LOCATION_INVALID    , NAS_LPP_RcvLocationInvalidTimer,   0  );
}

/*****************************************************************************
 Function Name   : NAS_LPP_TimerMsgDistr
 Description     :
 Input           :ucSessionTransIndx�÷�:  aucTransElementIdx[ucSessionTransIndx]
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvUpMsgRetransTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,VOS_VOID *pRcvMsg)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU * pstSessionElement;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx = 0;
    NAS_LPP_TRANS_ID_STRU                    stTransId;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvUpMsgRetransTimer");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvUpMsgRetransTimer_ENUM, LNAS_LPP_Func_Enter);

    if ( (ucSessionIndx >= NAS_LPP_MAX_SESSION_COUNT)||(ucSessionTransIndx >= NAS_LPP_MAX_TRANS_COUNT) )
    {
        NAS_LPP_ERR_LOG2("ACK timter expire,wrong ucSessionIndx ,ucSessionTransIndx",ucSessionIndx ,ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvUpMsgRetransTimer_ENUM, LNAS_LPP_ValueOverflow );
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvUpMsgRetransTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvUpMsgRetransTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);
        return;
    }

    pstSessionElement = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvUpMsgRetransTimer: don't find transaction entity");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvUpMsgRetransTimer_ENUM,LNAS_LPP_GetTransElementByIndexFail );
        return;
    }

    /*������������ﵽ�����ĴΣ�����transaction*/
    if ( pstTransEntity->ucRetranNum >= NAS_LPP_MAX_RETRANS_COUNT )
    {
        /* ����һ���Ƚϴ�Ĵ���ֹͣ��Ӧ��session */
        NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndx);
    }
    else
    {
        /*�����´��ش�*/
        pstTransEntity->ucRetranNum++;

        /*����ȴ�intra data conf��״̬*/
        NAS_LPP_ChangeTransFsmState(ucSessionIndx,ucSessionTransIndx,pstTransEntity->enLppMainState,LPP_SS_WAIT_INTRA_DATA_CNF);

        /*������Ϣ*/
        stTransId = pstTransEntity->stTransId;
        NAS_LPP_ResendUplinkMsg(pstSessionElement->ulSessionId,&stTransId);
    }

}
/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitCnAssistDataTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitCnAssistDataTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,VOS_VOID *pRcvMsg)
{
    NAS_LPP_LOC_TECH_MAP_STRU          *pstTechMap;
    NAS_LPP_CONFIG_PARA_STRU           *pstCfgPara;
    NAS_LPP_LOC_TECH_RUNING_STRU        stPosSearchRslt = {0};
    VOS_UINT8 ucTransIndx;

    pstCfgPara = NAS_LPP_GetCfgPara();
    ucTransIndx = NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    if (PS_NULL_UINT8 == ucTransIndx )
    {
        NAS_LPP_ERR_LOG2("wait cn assist data timer wrong index", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitCnAssistDataTimer_ENUM, LNAS_LPP_GetTransIdIndexFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitCnAssistDataTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitCnAssistDataTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);
        return;
    }

    /*����assist data ��transaction*/
    NAS_LPP_ReleaseTransEntity(ucSessionIndx, ucSessionTransIndx);
    NAS_LPP_SndUpLppAbortMsg(ucSessionIndx,ucSessionTransIndx,ucTransIndx,LPP_COMMON_IES_ABORT_TARGET_DEVCIE_ABORT,VOS_FALSE,VOS_TRUE);

    /* �����transaction��assist�������޸�otdoa�ĸ������ݣ�*/
    if (NAS_LPP_SLCT == pstCfgPara->bitOtdoaAssisChng)
    {
        /* �ҵ�otdoa��transaction*/
        pstTechMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
        if ( NAS_LPP_NULL_PTR != pstTechMap)
        {
            NAS_LPP_SearchRunningPosTechByTransIndx(pstTechMap->ucTransIndx,&stPosSearchRslt);

            /*���otdoa��transaction����ecid/gnss�����ܣ� */
            if (stPosSearchRslt.ucNum > 1)
            {
                /*  ���otdoa�Ĳ����Ѿ�������LRRC��ҪֹͣLRRC��otdoa���� */
                NAS_LPP_ReleasePosTechMeas(pstTechMap->ucSessionIndx, pstTechMap->ucSessionTranIndx,NAS_LPP_POSITION_TECH_OTDOA);
            }
            else /*���otdoa��transactionû����������(ecid/gnss)�����ܣ� */
            {
                /*������transaction*/
                NAS_LPP_ReleaseTransEntity(pstTechMap->ucSessionIndx, pstTechMap->ucSessionTranIndx);
            }
        }

        pstCfgPara->bitOtdoaAssisChng = NAS_LPP_NO_SLCT;
    }

#if 0
    /* �����transaction��assist�������޸�gnss�ĸ������� */
    if ()
    {
        /* �ҵ�gnss��transaction */


        /* ���gnss��transaction����ecid/otdoa������ */
        if ()
        {
            /*  ���gnss�Ĳ����Ѿ�������gps��Ҫֹͣgps��gnss���� */
            if  ()
            {

            }
        }
        else
        {
            /*������transaction*/
        }
    }
#endif

    /*����otdoa ��transaction*/
    pstTechMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
    if (NAS_LPP_NULL_PTR != pstTechMap)
    {
        NAS_LPP_ReleaseTransEntity(pstTechMap->ucSessionIndx, pstTechMap->ucSessionTranIndx);
    }
    else
    {
    }

}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvLocationInvalidTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvLocationInvalidTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,VOS_VOID *pRcvMsg)
{

}
/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitLrrcMeasCnfTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitLrrcMeasCnfTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,VOS_VOID *pRcvMsg)
{
    NAS_LPP_LOC_TECH_RUNING_STRU stPosSearchRslt = {0};
    PS_BOOL_ENUM_UINT8 enGnssPosExist = PS_FALSE;
    VOS_UINT32 ulLoop;

    NAS_LPP_ERR_LOG2("LPP rcv LRRC meas cnf time expire!", ucSessionIndx, ucSessionTransIndx);

    TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitLrrcMeasCnfTimer_ENUM, LNAS_LPP_Func_Enter);
    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitLrrcMeasCnfTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitLrrcMeasCnfTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);

    NAS_LPP_SearchRunningPosTechByIndx2(ucSessionIndx,ucSessionTransIndx,&stPosSearchRslt);

    for ( ulLoop = 0 ; ulLoop < stPosSearchRslt.ucNum; ulLoop++ )
    {
        if ( NAS_LPP_POSITION_TECH_GNSS == stPosSearchRslt.astLocTechMap[ulLoop].enPositionTech)
        {
            enGnssPosExist = PS_TRUE;
            break;
        }
    }

    /*�����transaction����gps�ģ����ͷ�transaction*/
    if (PS_FALSE == enGnssPosExist)
    {
        NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndx);
    }
    else
    {
        NAS_LPP_ERR_LOG("GNSS exist and not release trans");

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitLrrcMeasCnfTimer_ENUM, LNAS_LPP_GnssExistAndNotRelTrans);
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitEstCnfTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitEstCnfTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx,VOS_VOID *pRcvMsg )
{
    if(NAS_LPP_GetTransLppMsgCnt() < NAS_LPP_GetLppTransAttepCnt())
    {
        /*��������û�дﵽ��󣬷�����*/
        NAS_LPP_LppLmmEstReq();

        /*����������ʱ��*/
        NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                          NAS_LPP_TIMER_INVAILD_PARA,
                          TI_NAS_LPP_WAIT_EST_CNF);

        /*���������1*/
        NAS_LPP_TransLppMsgAddCnt();
    }
    else
    {
        /*���������ﵽ��������֪ͨSession�ͷ����е���Դ*/
        NAS_LPP_ConnFailHandle();
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitReEstTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitReEstTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx,VOS_VOID *pRcvMsg )
{
    NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitReEstTimer!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvWaitReEstTimer_ENUM, LNAS_LPP_Func_Enter);

    if(NAS_LPP_GetTransLppMsgCnt() < NAS_LPP_GetLppTransAttepCnt())
    {
        /*��������û�дﵽ��󣬷�����*/
        NAS_LPP_LppLmmEstReq();

        /*����������ʱ��*/
        NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                          NAS_LPP_TIMER_INVAILD_PARA,
                          TI_NAS_LPP_WAIT_RE_EST);

        /*���������1*/
        NAS_LPP_TransLppMsgAddCnt();
    }
    else
    {
        /*���������ﵽ��������֪ͨSession�ͷ����е���Դ*/
        NAS_LPP_ConnFailHandle();
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitResponseTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitResponseTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,VOS_VOID *pRcvMsg)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx           = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitResponseTimer!!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_Func_Enter);

    pstSessionEntity = NAS_LPP_GetSessionEntity(ucSessionIndx);
    if(NAS_LPP_NULL_PTR == pstSessionEntity)
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_RcvWaitResponseTimer: don't find SessionEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_GetSessionEntityFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);
        return;
    }
    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    if(PS_NULL_UINT8 == ucTransIndx)
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_RcvWaitResponseTimer: don't find TransEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_GetTransIdIndexFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitResponseTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);
        return;
    }

    /*end transactionΪtrue*/
    NAS_LPP_SetEndTransFlg(ucSessionIndx,ucSessionTransIndx,PS_TRUE);

    /*�ϱ�λ����Ϣ*/
    NAS_LPP_SndProvideLocInfoAndChngState(ucSessionIndx,
                                          ucSessionTransIndx,
                                          ucTransIndx);

    /*���ﲻ�ܽ�����transaction��Ҫ��provide location info�������*/
}


/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitPeriodicalTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitPeriodicalTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx,VOS_VOID *pRcvMsg )
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity = NAS_LPP_NULL_PTR;
    NAS_LPP_COMM_CONFIG_INFO_STRU           *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx           = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitPeriodicalTimer!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_Func_Enter);

    pstSessionEntity = NAS_LPP_GetSessionEntity(ucSessionIndx);
    if(NAS_LPP_NULL_PTR == pstSessionEntity)
    {
        NAS_LPP_ERR_LOG2(": don't find SessionEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_GetSessionEntityFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_SessionTransIndex, ucSessionTransIndx);
        return;
    }
    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_RcvWaitPeriodicalTimer: don't find TransEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_GetTransElementByIndexFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_SessionTransIndex, ucSessionTransIndx);
        return;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1(": period don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_GetCommCfgInfoElementByIndexFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_CommCfgIndex,pstTransElementEntity->ucCommCfgIndex);
        return;
    }

    if ( NAS_LPP_REPORT_LOCATION_TYPE_PERIOD != pstLppCommCfgInfo->stReportCriteria.enType)
    {
        NAS_LPP_ERR_LOG1(": period don't match comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_ReportCriteriaMatchFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_CommCfgIndex,pstTransElementEntity->ucCommCfgIndex);
        return;
    }

    /*�ϱ�������1*/
    pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ucReportingAmount++;

    /*�ж��ϱ��Ĵ����Ƿ�ﵽ���һ��: ��������һ�ε�LPP�����ϱ���end transactionΪtrue����������transaction*/
    if ( (PS_FALSE == NAS_LPP_IsReportInfinity(pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ucReportAmount))
       &&( pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ucReportingAmount >=
            pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ucReportAmount)  )
    {
        NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitPeriodicalTimer: Up Max Report Count!");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_PeriodReportUpToMaxNum);

        /*end transactionΪtrue*/
        NAS_LPP_SetEndTransFlg(ucSessionIndx,ucSessionTransIndx,PS_TRUE);

        /*�ϱ�λ����Ϣ*/
        NAS_LPP_SndProvideLocInfoAndChngState(ucSessionIndx,
                                                  ucSessionTransIndx,
                                                  ucTransIndx);

        /*���ﲻ�ܽ�����transaction��Ҫ��provide location info�������*/
    }
    else
    {
        NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitPeriodicalTimer: Don't Up Max Report Count!");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvWaitPeriodicalTimer_ENUM, LNAS_LPP_PeriodReportNotUpToMaxNum);

        /*�������������ϱ���ʱ��*/
        NAS_LPP_TimerStart(ucSessionIndx,ucSessionTransIndx,TI_NAS_LPP_PERIODICAL_REPORT);

        /*�ϱ�λ����Ϣ*/
        NAS_LPP_SndProvideLocInfoAndChngState(ucSessionIndx,
                                                  ucSessionTransIndx,
                                                  ucTransIndx);
    }

}
/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitReportDurationTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitReportDurationTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,VOS_VOID *pRcvMsg)
{
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx           = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvWaitReportDurationTimer!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_Func_Enter);

    pstSessionEntity = NAS_LPP_GetSessionEntity(ucSessionIndx);
    if(NAS_LPP_NULL_PTR == pstSessionEntity)
    {
        NAS_LPP_ERR_LOG2("DurationTimer: don't find SessionEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_GetSessionEntityFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);
        return;
    }
    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    if(PS_NULL_UINT8 == ucTransIndx)
    {
        NAS_LPP_ERR_LOG2("DurationTimer: don't find TransEntity!", ucSessionIndx, ucSessionTransIndx);

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_GetTransIdIndexFail);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_SessionIndex,ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvWaitReportDurationTimer_ENUM, LNAS_LPP_SessionTransIndex,ucSessionTransIndx);
        return;
    }

    /*������session*/
    /*NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndx);*/

    /*end transactionΪtrue*/
    NAS_LPP_SetEndTransFlg(ucSessionIndx,ucSessionTransIndx,PS_TRUE);

    /*�ϱ�λ����Ϣ*/
    NAS_LPP_SndProvideLocInfoAndChngState(ucSessionIndx,
                                          ucSessionTransIndx,
                                          ucTransIndx);
}
/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitGnssCapCnfTimer
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvWaitGnssCapCnfTimer( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx,VOS_VOID *pRcvMsg )
{

}

/*****************************************************************************
 Function Name   : NAS_LPP_RcvWaitIntraDataCnfTimerExpire
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvIntraDataCnfTimerExpire( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,VOS_VOID *pRcvMsg)
{
    NAS_LPP_ERR_LOG2("LPP rcv intra data time expire!", ucSessionIndx, ucSessionTransIndx);
    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvIntraDataCnfTimerExpire_ENUM, LNAS_LPP_SessionIndex, ucSessionIndx);
    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvIntraDataCnfTimerExpire_ENUM, LNAS_LPP_SessionTransIndex, ucSessionTransIndx);

    /* ����һ���Ƚϴ�Ĵ���ֹͣ���е�session */
    NAS_LPP_ReleaseAllSession();
}

/*****************************************************************************
 Function Name   : NAS_LPP_ParsIndxFromTimePara
 Description     : �Ӷ�ʱ����parameter�����ֽ��session index��transaction
                   index
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ParsIndxFromTimePara( VOS_UINT32 ulPara,VOS_UINT8 *pucSessionIndx,VOS_UINT8 *pucSessionTransIndx)
{
    VOS_UINT32 ulTmp;

    ulTmp = ulPara & 0xFF;

    *pucSessionIndx  = (VOS_UINT8)ulTmp;

    ulTmp = (ulPara>>16)&0xFF;
    *pucSessionTransIndx = (VOS_UINT8)ulTmp;
}


/*****************************************************************************
 Function Name  : NAS_LPP_TimerMsgDistr()
 Description    : LPPģ��TIMER��Ϣ�ַ�����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
 1. xiaojun 2015-7-7 �¿���
*****************************************************************************/
VOS_VOID NAS_LPP_TimerMsgDistr(VOS_VOID *pRcvMsg )
{
    NAS_LPP_TIMER_PARA_ENUM_UINT8      enTimerType = TI_NAS_LPP_TIMER_PARA_BUTT;
    NAS_LPP_TIMER_PROC_FUNC pfTimerFun = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucSessionIndx, ucSessionTransIndx;
    VOS_UINT32 ulPara;

    NAS_LPP_NORM_LOG("NAS_LPP_TimerMsgDistr is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_TimerMsgDistr_ENUM, LNAS_LPP_Func_Enter);

    enTimerType = (NAS_LPP_TIMER_PARA_ENUM_UINT8)PS_GET_REL_TIMER_NAME(pRcvMsg);
    ulPara = PS_GET_REL_TIMER_PARA(pRcvMsg);

    NAS_LPP_ParsIndxFromTimePara(ulPara, &ucSessionIndx, &ucSessionTransIndx );

    NAS_LPP_OmTimerExpireInd(ucSessionIndx,ucSessionTransIndx,enTimerType);

    pfTimerFun = NAS_LPP_GetTimerProcFun(enTimerType);
    if ( NAS_LPP_NULL_PTR != pfTimerFun )
    {
        pfTimerFun(ucSessionIndx, ucSessionTransIndx, pRcvMsg);
    }
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
