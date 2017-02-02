

#include        "MM_Inc.h"
#include        "GmmMmInterface.h"
#include        "GmmExt.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"

#include "NasUtranCtrlInterface.h"
#include "NasMmEcall.h"

/* Added by n00355355 for �����ؽ�, 2015-9-24, begin */
#include "NasMmlLib.h"
/* Added by n00355355 for �����ؽ�, 2015-9-24, end */

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_MM_MSG_C

/*lint -save -e958 */

VOS_VOID MM_ReportN2MOtaMsg(VOS_UINT8 ucMsgType, NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "MM_ReportN2MOtaMsg:NORMAL: msg type is ", ucMsgType);

    switch(ucMsgType)
    {
        case MM_IE_MSG_TYPE_AUTH_REQ:                                           /* AUTHENTICATION REQUEST ��Ϣ              */
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_REQ;
            break;

        case MM_IE_MSG_TYPE_CM_SERV_REJ:                                        /* CM SERVICE REJECT ��Ϣ                   */
            usNasOtaMsyId = NAS_OTA_MSG_CM_SERV_REJECT;
            break;

        case MM_IE_MSG_TYPE_CM_SERV_ACP:                                        /* CM SERVICE ACCEPT ��Ϣ                   */
            usNasOtaMsyId = NAS_OTA_MSG_CM_SERV_ACCEPT;
            break;

        case MM_IE_MSG_TYPE_AUTH_REJ:                                           /* AUTHENTICATION REJECT ��Ϣ               */
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_REJECT;
            break;

        case MM_IE_MSG_TYPE_ABORT:                                              /* ABORT ��Ϣ                               */
            usNasOtaMsyId = NAS_OTA_MSG_ABORT;
            break;

        case MM_IE_MSG_TYPE_ID_REQ:                                             /* IDENTITY REQUEST ��Ϣ                    */
            usNasOtaMsyId = NAS_OTA_MSG_ID_REQ;
            break;

        case MM_IE_MSG_TYPE_MM_INFO:                                            /* MM INFORMATION ��Ϣ                      */
            usNasOtaMsyId = NAS_OTA_MSG_MM_INFO;
            break;

        case MM_IE_MSG_TYPE_MM_STA:                                             /* MM STATUS ��Ϣ                           */
            usNasOtaMsyId = NAS_OTA_MSG_MM_STA_N2M;
            break;

        case MM_IE_MSG_TYPE_TMSI_REALLOC_CMD:                                   /* TMSI REALLOCATION COMMAND ��Ϣ           */
            usNasOtaMsyId = NAS_OTA_MSG_TMSI_REALLOC_CMD;
            break;

        case MM_IE_MSG_TYPE_LU_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_LOCATION_UPDATE_ACCEPT;
            break;

        case MM_IE_MSG_TYPE_LU_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_LOCATION_UPDATE_REJECT;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "MM_ReportN2MOtaMsg:WARNING: invalid msg id");
            /*������MMģ��Ŀտ���Ϣ������trace����ʾ*/
            return;
    }

    NAS_SendAirMsgToOM(WUEPS_PID_MM, usNasOtaMsyId, NAS_OTA_DIRECTION_DOWN, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8*)pNasMsg);
}


VOS_UINT8 Mm_ComMsgAuthReqRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* ��ǰ�������Ϣ                           */
                            VOS_UINT16      usMsgSize                               /* ��Ϣ����,���ֽ�Ϊ��λ                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_AUTH_REQ;                               /* �¼�ID                                   */
    VOS_UINT16      usIndex;

    PS_MEM_SET( &g_MmMsgAuthReq, 0, sizeof(MM_MSG_AUTHENTICATION_REQ_STRU));   /* ����                                     */

    if (VOS_NULL_PTR == pucRcvMsg)
    {
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgAuthReqRcv:WARNING: MSG VOS_NULL_PTR!");
    }
    else if ( usMsgSize < 19 )
    {
        ucEventId = MM_EVENT_ID_STATUS_96;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgAuthReqRcv:WARNING: RCV MM AUTHENTICATION REQ MSG WITH ERROR SIZE!");
    }
    else if (MM_FALSE == MM_IeChkCksn( &pucRcvMsg[2] ))
    {                                                                           /* CKSNΪ����ֵ                             */
        ucEventId = MM_EVENT_ID_STATUS_95;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgAuthReqRcv:WARNING: CKSN ERROR!");
    }
    else
    {
        g_MmMsgAuthReq.MmIeCKSN.ucCksn
            = (VOS_UINT8)(pucRcvMsg[2] & MM_IE_CKSN_KEY_SEQUENCE_MASK);         /* �洢CKSN                                 */


        if ( MM_FALSE == MM_IeChkRand( &pucRcvMsg[3] ) )
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgAuthReqRcv:WARNING: RAND ERROR!");
            return MM_EVENT_ID_STATUS_95;
        }
        PS_MEM_CPY(
                    g_MmMsgAuthReq.MmIeRAND.aucRandValue,
                    pucRcvMsg+3,
                    MM_RAND_VALUE_LENGTH
                    );                                                          /* �洢RAND                                 */
        usIndex = 19;
        while ( usIndex < usMsgSize )
        {                                                                       /* ��Ϣ�ﺬ��AUTN                           */
            if ( ( 0x20 == pucRcvMsg[usIndex] ) && ( usMsgSize > 36 ) )
            {                                                                   /* AUTN��IEI��ȷ                            */
                usIndex++;
                if ( MM_FALSE == MM_IeChkAutn( &pucRcvMsg[usIndex] ) )
                {
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgAuthReqRcv:WARNING: AUTN ERROR!");
                    return MM_EVENT_ID_STATUS_95;
                }
                if ( MM_IE_AUTN_PRESENT == g_MmMsgAuthReq.ucAutnFlg)
                {
                    ;
                }
                else
                {
                    g_MmMsgAuthReq.ucAutnFlg = MM_IE_AUTN_PRESENT;
                    g_MmMsgAuthReq.MmIeAUTN.ucAutnLen = pucRcvMsg[usIndex];     /* ���AUTN�ĳ���                           */
                    PS_MEM_CPY(
                                g_MmMsgAuthReq.MmIeAUTN.aucAutn,
                                &pucRcvMsg[usIndex + 1],
                                pucRcvMsg[usIndex]
                                );                                              /* ���AUTN                                 */
                }
                usIndex = usIndex + pucRcvMsg[usIndex] + 1;
            }
            else
            {                                                                   /* AUTN��IEI����ȷ                          */
                usIndex = usMsgSize;
            }
        }
    }
    return ucEventId;                                                           /* �����¼�ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgCcMsgInteChk
  Function: ��CC��Ϣ���������Լ��
  Input:    RRMM_DATA_IND_STRU       *pMsg, RRMM_DATA_INDԭ��ָ��
  Output:
  NOTE:
  Return:   VOS_UINT8,�¼�ID,���MM_Def.h�й����¼��ĺ궨��
  History:
      1.  ��־��   2003.12.11  �°�����
      2. ��    ��   : 2006��11��21��
         ��    ��   : luojian   id:60022475
         �޸�����   : ȥ�������Լ���ж�,���ⵥ�ţ�A32D07459
*******************************************************************************/
VOS_UINT8 Mm_ComMsgCcMsgInteChk (
                              RRMM_DATA_IND_FOR_PCLINT_STRU       *pMsg         /* ��ǰ�������Ϣ                           */
                               )
{
    VOS_UINT8       ucEventId;                                                  /* �¼�ID                                   */
    VOS_UINT8       i;                                                          /* ѭ������                                 */
    VOS_UINT8       j;                                                          /* ѭ������                                 */
    VOS_UINT8       ucCnt = 0;                                                  /* MM���ӵĴ��ڸ���                         */
    /*lint -e701*/
    for ( i = MM_CONST_NUM_0; i < MM_CONST_NUM_2; i++ )
    {
        for ( j = MM_CONST_NUM_0; j < MM_CONST_NUM_7; j++ )
        {
            if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[i] & (0x01 << j) ) )
            {                                                                   /* ͳ��MM���ӵĸ���                         */
                ucCnt++;
            }
            if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                aucMMConnExtFlg[i] & (0x01 << j) ) )
            {                                                                   /* ͳ��MM���ӵĸ���                         */
                ucCnt++;
            }
            if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                aucMMConnExtFlg[i] & (0x01 << j) ) )
            {                                                                   /* ͳ��MM���ӵĸ���                         */
                ucCnt++;
            }
        }
    }
    /*lint +e701*/

    if ((MM_CONST_NUM_1 == ucCnt)
        &&(NO_MM_CONN_ESTING ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
        &&(MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg))
    {                                                                           /* ���MM����ֻ��һ�������ǽ�����           */
        ucEventId = MM_EVENT_ID_CC_MESSAGE;                                     /* ����¼�ID                               */
    }

    else
    {
        ucEventId = MM_EVENT_ID_CC_MESSAGE;                                     /* ����¼�ID                               */
    }
    return ucEventId;                                                           /* �����¼�ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgCmSvcAcceptRcv
  Function: ��CM SERVICE ACCEPT��Ϣ���������Լ��
  Input:    RRMM_DATA_IND_STRU       *pMsg, RRMM_DATA_INDԭ��ָ��
  Output:
  NOTE:
  Return:   VOS_UINT8,�¼�ID,���MM_Def.h�й����¼��ĺ궨��
  History:
      1.  ��־��    2003.12.11  �°�����
*******************************************************************************/
VOS_UINT8 Mm_ComMsgCmSvcAcceptRcv (
                                RRMM_DATA_IND_FOR_PCLINT_STRU       *pMsg       /* ��ǰ�������Ϣ                           */
                                  )
{
    VOS_UINT8       ucEventId;                                                  /* �¼�ID                                   */

    if ((MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0])
        &&(MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1])
        && (MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0])
        && (MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1])
        && (MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0])
        && (MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1])
        &&(NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
        &&(MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg))
    {
        ucEventId = MM_EVENT_ID_CM_SVC_ACCEPT;                                  /* ����¼�ID                               */
    }
    else
    {
        ucEventId = MM_EVENT_ID_CM_SVC_ACCEPT;                                  /* ����¼�ID                               */
    }

    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */

    return ucEventId;                                                           /* �����¼�ID                               */
}
VOS_UINT8 Mm_ComMsgAuthRjctRcv ()
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_AUTH_REJ;                               /* �¼�ID                                   */
	NAS_MML_PLMN_ID_STRU *         pstCurrCampPlmnId;
	NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo;
    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_TYPE_BUTT;

    pstCurrCampPlmnId = NAS_MML_GetCurrCampPlmnId();
    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_AUTH_REJ,
                              NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    if (pstAuthRejInfo->ucHplmnCsAuthRejCounter < pstAuthRejInfo->ucMaxAuthRejNo)
    {
        if ((VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId))
        && (VOS_TRUE == pstAuthRejInfo->ucIgnoreAuthRejFlg))
        {
            pstAuthRejInfo->ucHplmnCsAuthRejCounter++;
            return MM_EVENT_ID_INVALID;
        }
    }

    return ucEventId;                                                           /* �����¼�ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgCmSvcRjctRcv
  Function: �洢��ϢCM SERVICE REJECT
  Input:    VOS_UINT8    *pucRcvMsg, ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_UINT8,�¼�ID,���MM_Def.h�й����¼��ĺ궨��
  History:
      1.  ��־��   2003.12.10   �°�����
*******************************************************************************/
VOS_UINT8 Mm_ComMsgCmSvcRjctRcv (
                            VOS_UINT8      *pucRcvMsg,                          /* ��ǰ�������Ϣ                           */
                            VOS_UINT16      usMsgSize                           /* ��Ϣ����,���ֽ�Ϊ��λ                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_CM_SVC_REJ;                         /* �¼�ID                                   */

    if ( usMsgSize < 3 )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgCmSvcRjctRcv:WARNING: RCV MM CM SERVICE REJECT MSG WITH ERROR SIZE!");
        return MM_EVENT_ID_STATUS_96;
    }
    g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause = pucRcvMsg[2];                    /* �洢Reject cause                         */

    g_MmGlobalInfo.ucRejectCause = pucRcvMsg[2];

    /* Modified by n00355355 for User_Exp_Improve, 2015-8-19, begin */
    NAS_MM_ParseT3246IE(pucRcvMsg, usMsgSize, &(g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246));
    /* Modified by n00355355 for User_Exp_Improve, 2015-8-19, end */

    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */

    return ucEventId;                                                           /* �����¼�ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgAbortRcv
  Function: �洢��ϢABORT
  Input:    VOS_UINT8    *pucRcvMsg, ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_UINT8,�¼�ID,���MM_Def.h�й����¼��ĺ궨��
  History:
      1.  ��־��   2003.12.10   �°�����
*******************************************************************************/
VOS_UINT8 Mm_ComMsgAbortRcv (
                            VOS_UINT8      *pucRcvMsg,                          /* ��ǰ�������Ϣ                           */
                            VOS_UINT16      usMsgSize                           /* ��Ϣ����,���ֽ�Ϊ��λ                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_ABORT;                              /* �¼�ID                                   */

    if ( usMsgSize < 3 )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgAbortRcv:WARNING: RCV MM ABORT MSG WITH ERROR SIZE!");
        return MM_EVENT_ID_STATUS_96;
    }
    g_MmMsgAbort.MmIeRejCause.ucRejCause = pucRcvMsg[2];                        /* �洢Reject cause                         */

    g_MmGlobalInfo.ucRejectCause = pucRcvMsg[2];

    return ucEventId;                                                           /* �����¼�ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgIdReqRcv
  Function: �洢��Ϣ IDENTITY REQUEST
  Input:    VOS_UINT8    *pucRcvMsg, ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_UINT8,�¼�ID,���MM_Def.h�й����¼��ĺ궨��
  History:
      1.  ��־��   2003.12.10   �°�����

      2.��    ��   : 2006��2��20��
        ��    ��   : liuyang id:48197
        �޸�����   : ��IE������ϱ���ԭ��ֵ��95��Ϊ96,���ⵥ��:A32D01694
*******************************************************************************/
VOS_UINT8 Mm_ComMsgIdReqRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* ��ǰ�������Ϣ                           */
                            VOS_UINT16      usMsgSize                               /* ��Ϣ����,���ֽ�Ϊ��λ                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_IDENTITY_REQ;                           /* �¼�ID                                   */

    if ( usMsgSize < 3 )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgIdReqRcv:WARNING: RCV MM IDENTITY REQUEST MSG WITH ERROR SIZE!");
        return MM_EVENT_ID_STATUS_96;
    }

    if ( MM_FALSE == MM_IeChkIdType( &pucRcvMsg[2] ) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgIdReqRcv:WARNING: ID TYPE ERROR!");
        return MM_EVENT_ID_STATUS_96;
    }
    g_MmMsgIdReq.MmIeIdType.ucIDType
        = (VOS_UINT8)(pucRcvMsg[2] & MM_IE_ID_TYPE_IDTYPE_MASK);                    /* �洢Id type                              */
    return ucEventId;                                                           /* �����¼�ID                               */
}
VOS_UINT8 Mm_ComMsgMmInfoRcv (
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize
)
{
    VOS_UINT8                           ucEventId;
    VOS_UINT16                          usIndex;
    VOS_UINT8                           ucShortNetWorkNameExist;
    VOS_UINT8                           ucLongNetWorkNameExist;
    MM_DECODE_RESULT_ENUM_U32           ucRst;
    NAS_MML_OPERATOR_NAME_INFO_STRU     stOldOperatorName;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstCurrOperatorName = VOS_NULL_PTR;

    NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU                    stNvimOperatorName;

    ucShortNetWorkNameExist = VOS_FALSE;
    ucLongNetWorkNameExist  = VOS_FALSE;
    ucEventId               = MM_EVENT_ID_MM_INFO;
    ucRst                   = MM_DECODE_SUCCESS;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();
    PS_MEM_CPY(&stOldOperatorName, pstCurrOperatorName, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU));

    PS_MEM_SET(&g_MmMsgMmInfo, 0, sizeof(MM_MSG_MM_INFO_STRU));

    if ( usMsgSize < MM_MSG_HEADER_LEN )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "Mm_ComMsgMmInfoRcv:WARNING: RCV MM INFORMATION MSG WITH ERROR SIZE!");
        return MM_EVENT_ID_STATUS_96;
    }

    usIndex = MM_MSG_HEADER_LEN;
    while ( usIndex < usMsgSize )
    {
        switch (pucRcvMsg[usIndex])
        {
            case MM_IE_FULL_NAME_FOR_NETWORK:
                ucRst = NAS_MM_DecodeFullNameForNetworkIe(pucRcvMsg, usMsgSize,
                                                          &usIndex, &ucEventId,
                                                          &ucLongNetWorkNameExist);


                g_MmMsgMmInfo.ucFulNamFrNWFlg = VOS_TRUE;

                break;
            case MM_IE_SHORT_NAME_FOR_NETWORK:
                ucRst = NAS_MM_DecodeShortNameForNetworkIe(pucRcvMsg, usMsgSize,
                                                          &usIndex, &ucEventId,
                                                          &ucShortNetWorkNameExist);

                g_MmMsgMmInfo.ucShortNamFrNWFlg = VOS_TRUE;

                break;
            case MM_IE_LOCAL_TIME_ZONE:
                ucRst = NAS_MM_DecodeLocalTimeZoneIe(pucRcvMsg, usMsgSize,
                                             &usIndex, &ucEventId);
                break;
            case MM_IE_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE:
                ucRst = NAS_MM_DecodeUniversalTimeAndLocalTimeZoneIe(pucRcvMsg, usMsgSize,
                                                     &usIndex, &ucEventId);
                break;
            case MM_IE_LSA_IDENTITY:
                ucRst = NAS_MM_DecodeLocalizedServiceAreaIe(pucRcvMsg, usMsgSize,
                                                     &usIndex, &ucEventId);
                break;
            case MM_IE_NETWORK_DAYLIGHT_SAVING_TIME:
                ucRst = NAS_MM_DecodeNetworkDaylightSavingTimeIe(pucRcvMsg, usMsgSize,
                                                     &usIndex, &ucEventId);
                break;
            default:
                usIndex = usMsgSize;
                break;
        }

        /* �����Ϣ���������������֮ǰ��������ݲ�ͬ,��ҪдNV */
        if (0 != VOS_MemCmp(pstCurrOperatorName, &stOldOperatorName, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU)))
        {
            PS_MEM_CPY(&stNvimOperatorName, pstCurrOperatorName, sizeof(stNvimOperatorName));

            if (NV_OK != NV_Write(en_NV_Item_Network_Name_From_MM_Info,
                                  &stNvimOperatorName,
                                  sizeof(stNvimOperatorName)))
            {
                NAS_WARNING_LOG(WUEPS_PID_MM, "Mm_ComMsgMmInfoRcv:Write NV fail.");
            }
        }

        if(MM_DECODE_END == ucRst)
        {
            return ucEventId;
        }
    }

    return ucEventId;                                                           /* �����¼�ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgMmStatusRcv
  Function: �洢��ϢMM STATUS
  Input:    VOS_UINT8    *pucRcvMsg, ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_UINT8,�¼�ID,���MM_Def.h�й����¼��ĺ궨��
  History:
      1.  ��־��   2003.12.10   �°�����
*******************************************************************************/
VOS_UINT8 Mm_ComMsgMmStatusRcv (
                            VOS_UINT8      *pucRcvMsg,                          /* ��ǰ�������Ϣ                           */
                            VOS_UINT16      usMsgSize                           /* ��Ϣ����,���ֽ�Ϊ��λ                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_MM_STATUS;                          /* �¼�ID                                   */

    if ( usMsgSize < 3 )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgMmStatusRcv:WARNING: RCV MM STATUS MSG WITH ERROR SIZE!");
        return MM_EVENT_ID_STATUS_96;
    }

    g_MmGlobalInfo.ucRejectCause = pucRcvMsg[2];

    return ucEventId;                                                           /* �����¼�ID                               */
}



VOS_VOID Mm_ComSaveLai(
                   VOS_UINT8            *pucLai,                                    /* ��Ϣ�е�LAI��ŵ�ַ                      */
                   MM_LAI_STRU      *pLai                                       /* LAIȫ�����ĵ�ַ                          */
                   )
{
    pLai->PlmnId.ulMcc = pucLai[1] & MM_IE_LU_ID_MCC_DIGIT_3_MASK;              /* �洢LAI�е� MCC digit 3                  */
    pLai->PlmnId.ulMcc = (pLai->PlmnId.ulMcc << 8) | (pucLai[0] >> 4);          /* �洢LAI�е� MCC digit 2                  */
    pLai->PlmnId.ulMcc = (pLai->PlmnId.ulMcc << 8)
                         | (pucLai[0] & MM_IE_LU_ID_MCC_DIGIT_1_MASK);          /* �洢LAI�е� MCC digit 1                  */

    pLai->PlmnId.ulMnc = pucLai[1] >> 4;                                        /* �洢LAI�е� MNC digit 3                  */
    pLai->PlmnId.ulMnc = (pLai->PlmnId.ulMnc << 8) | (pucLai[2] >> 4);          /* �洢LAI�е� MNC digit 2                  */
    pLai->PlmnId.ulMnc = (pLai->PlmnId.ulMnc << 8)
                         | (pucLai[2] & MM_IE_LU_ID_MNC_DIGIT_1_MASK);          /* �洢LAI�е� MNC digit 1                  */
    pLai->ulLac = pucLai[3];
    pLai->ulLac = (pLai->ulLac << 8) | pucLai[4];

    if ( 0 == ( pLai->ulLac & 0x0000ffff ) )
    {
        pLai->ulLac = MM_INVALID_LAI;
    }

}


VOS_UINT8 Mm_ComMsgTmsiReallocCmdRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* ��ǰ�������Ϣ                           */
                            VOS_UINT16      usMsgSize                               /* ��Ϣ����,���ֽ�Ϊ��λ                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_TMSI_REALLOC_CMD;                       /* �¼�ID                                   */
    VOS_UINT8       i;                                                              /* ѭ������                                 */

    if ( usMsgSize < 9 )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgTmsiReallocCmdRcv:WARNING: RCV TMSI REALLOCATION COMMAND MSG WITH ERROR SIZE!");
        return MM_EVENT_ID_STATUS_96;
    }
    PS_MEM_SET(&g_MmMsgTmsiReallocCmd,0,sizeof(MM_MSG_TMSI_REALLOC_CMD_STRU)); /* ����                                     */

    if ( MM_FALSE == MM_IeChkLai( &pucRcvMsg[2] ) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgTmsiReallocCmdRcv:WARNING: LAI ERROR!");
    }
    Mm_ComSaveLai (pucRcvMsg + 2, &g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai);        /* �洢��Ϣ�е�LAI                          */

    if ( ( 0xF4 != pucRcvMsg[8] ) && ( 0x01 != (pucRcvMsg[8] & 0x0F) )
                                && ( 0x09 != (pucRcvMsg[8] & 0x0F) ) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgTmsiReallocCmdRcv:WARNING: MOBILE ID TYPE ERROR!");
        return MM_EVENT_ID_STATUS_95;
    }
    if ( MM_FALSE == MM_IeChkMblId( &pucRcvMsg[7] ) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgTmsiReallocCmdRcv:WARNING: MOBILE ID ERROR!");
        return MM_EVENT_ID_STATUS_95;
    }
    switch ( pucRcvMsg[8] & MM_IE_MI_ID_TYPE_MASK )
    {                                                                           /* �ж�MOBILE ID������                      */
    case MM_IE_MI_ID_TYPE_IMSI:                                                 /* IMSI                                     */
        g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.ucMsIdFlg
            = MM_MS_ID_IMSI_PRESENT;                                            /* ��Mobile ID���ڱ�־                      */
        break;
    case MM_IE_MI_ID_TYPE_TMSI:                                                 /* TMSI                                     */
        g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.ucMsIdFlg
            = MM_MS_ID_TMSI_PRESENT;                                            /* ��Mobile ID���ڱ�־                      */
        for ( i = MM_CONST_NUM_0; i < MM_CONST_NUM_4; i++ )
        {
            g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.aucTmsi[i]
                = pucRcvMsg[9+i];                                               /* ���TMSI                                 */
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgTmsiReallocCmdRcv:WARNING: MOBILE IDENTITY TYPE Abnormal");
        break;
    }
    return ucEventId;                                                           /* �����¼�ID                               */
}
VOS_UINT32  MM_ComCheckNoOtherMmConnection()
{
    if ( (MM_CONST_NUM_0 ==  g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0])
      && (MM_CONST_NUM_0 ==  g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1])
      && (MM_CONST_NUM_0 ==  g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0])
      && (MM_CONST_NUM_0 ==  g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]))
    {
        return MM_TRUE;
    }
    else
    {
        return MM_FALSE;
    }
}


VOS_UINT32 MM_ComCmpLai(
    MM_LAI_STRU                         stLai1,
    MM_LAI_STRU                         stLai2
)
{
    if ((stLai1.ulLac        != stLai2.ulLac)
     || (stLai1.PlmnId.ulMnc != stLai2.PlmnId.ulMnc)
     || (stLai1.PlmnId.ulMcc != stLai2.PlmnId.ulMcc))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}



VOS_UINT32 MM_ComCheckLauIntegrityProtection(VOS_UINT8 *pucMsgContent, VOS_UINT16  usMsgLen)
{
    MM_LAI_STRU                         stLuLai;
    VOS_UINT8                           aucLuTmsi[MM_TMSI_LENGTH];
    VOS_UINT8                           ucTmsiAvail;
    VOS_UINT8                           ucImsiAvail;
    VOS_UINT16                          usIeCount;
    VOS_UINT32                          ulIntegrityCheckResult;
    MM_LAI_STRU                         stCurLai;

    PS_MEM_SET(&stCurLai, 0x0 ,sizeof(stCurLai));
    NAS_MM_ConvertMmlLaiFormatToMMFormat((NAS_MML_GetCurrCampLai()), &stCurLai);

    /* �����Ա����Ѿ����� */
    if (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.MmShare.ucCsIntegrityProtect)
    {
        ulIntegrityCheckResult = MM_TRUE;
    }
    /* �����Ա���û������ */
    else
    {
        ulIntegrityCheckResult = MM_FALSE;

        /* 24.008 4.1.1.1  LOCATION UPDATING ACCEPT (at periodic location update with no change
        of location area or temporary identity) */
        if (MM_IE_LUT_PERIODIC_UPDATING != g_MmGlobalInfo.LuInfo.ucLuType)
        {
            return MM_FALSE;
        }

        /* ��ȡLAU ACCEPT��ϢLAI���� */
        Mm_ComSaveLai( &pucMsgContent[2], &stLuLai );

        ucTmsiAvail = MM_FALSE;
        ucImsiAvail = MM_FALSE;
        PS_MEM_SET(aucLuTmsi, 0x00, MM_TMSI_LENGTH);

        /* ��ȡLAU ACCEPT��ϢTMSI���� */
        for (usIeCount=7; usIeCount < usMsgLen; usIeCount++ )
        {
            if (MM_IEI_MOBILE_ID == pucMsgContent[usIeCount])
            {
                if ( MM_IE_MI_ID_TYPE_TMSI == (pucMsgContent[usIeCount+2] & 0x07) )
                {
                    ucTmsiAvail = MM_TRUE;
                    PS_MEM_CPY(aucLuTmsi, &pucMsgContent[usIeCount+3], MM_TMSI_LENGTH);
                }
                else if ( MM_IE_MI_ID_TYPE_IMSI == (pucMsgContent[usIeCount+2] & 0x07) )
                {
                    ucImsiAvail = MM_TRUE;
                }
                else
                {
                }
                break;
            }
        }

        /* LAIû�з����ı� */
        if (VOS_TRUE == MM_ComCmpLai(stLuLai,stCurLai))
        {
            /* û�з���TMSI */
            if (MM_FALSE == ucTmsiAvail)
            {
                if (!( (MM_TRUE == ucImsiAvail)
                      &&( MM_MS_ID_TMSI_PRESENT == ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
                                                   & MM_MS_ID_TMSI_PRESENT ) ))
                   )
                {
                    ulIntegrityCheckResult = MM_TRUE;
                }
            }
            /* �����TMSI����ǰ��ͬ */
            else if ( 0 == VOS_MemCmp(aucLuTmsi,NAS_MML_GetUeIdTmsi(),MM_TMSI_LENGTH) )
            {
                ulIntegrityCheckResult = MM_TRUE;
            }
            else
            {
            }
        }
    }
    return ulIntegrityCheckResult;
}
VOS_UINT32 MM_ComCheckIntegrityProtection(VOS_UINT8 *pucMsgContent, VOS_UINT16  usMsgLen)
{
    VOS_UINT8                           ucPD;
    VOS_UINT8                           ucMsgType;
    VOS_UINT32                          ulIntegrityCheckResult;

    /* ���ٽ���ģʽ���ڲ���ģʽ�������������Լ�� */
    if ( VOS_TRUE == NAS_MML_IsQuickStartFlg())
    {
        return MM_TRUE;
    }

    /* �����Լ���������UMTS���� */
    if (NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        return MM_TRUE;
    }


    /* ��TDDģʽʱ��������ò���Ҫ����SMC���ã��򷵻������Ա���ͨ�� */
    if (VOS_FALSE == NAS_UTRANCTRL_IsUtranCsSmcNeeded())
    {
        return MM_TRUE;
    }

    ucPD = pucMsgContent[0] & 0x0f;

    /* �����Ա����Ѿ����� */
    if (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.MmShare.ucCsIntegrityProtect)
    {
        ulIntegrityCheckResult = MM_TRUE;
    }
    /* �����Ա���û������ */
    else
    {
        ulIntegrityCheckResult = MM_FALSE;

        /*
        24.008 4.1.1.1 Except the messages listed below, no layer 3 signalling
        messages shall be processed by the receiving MM and GMM entities or
        forwarded to the CM entities, unless the security mode control procedure
        is activated for that domain. */
        if (MM_IE_PD_MM_MSG == ucPD)
        {
            ucMsgType = pucMsgContent[1] & 0x3f;
            switch (ucMsgType)
            {
                case MM_IE_MSG_TYPE_AUTH_REQ:
                case MM_IE_MSG_TYPE_AUTH_REJ:
                case MM_IE_MSG_TYPE_ID_REQ:
                case MM_IE_MSG_TYPE_LU_REJECT:
                case MM_IE_MSG_TYPE_CM_SERV_REJ:
                case MM_IE_MSG_TYPE_ABORT:
                    ulIntegrityCheckResult = MM_TRUE;
                    break;
                case MM_IE_MSG_TYPE_LU_ACCEPT:
                    ulIntegrityCheckResult = MM_ComCheckLauIntegrityProtection(pucMsgContent,usMsgLen);
                    break;

                case MM_IE_MSG_TYPE_CM_SERV_ACP:
                    if ( (MM_TRUE == MM_ComCheckNoOtherMmConnection())
                      && (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucState)
                      && (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType) )
                    {
                        ulIntegrityCheckResult = MM_TRUE;
                    }
                    break;
                default:
                    break;
            }
        }
        else if(MM_IE_PD_CALL_CONTROL == ucPD)
        {
            /* ����̬û������MM���ӣ���ǰΪ��������״̬ */
            if ((MM_TRUE == MM_ComCheckNoOtherMmConnection())
             && (MM_CONNECTION_ACTIVE == g_MmGlobalInfo.ucState)
             && (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType) )
            {
                ulIntegrityCheckResult = MM_TRUE;
            }
        }
        else if (MM_IE_PD_TEST == ucPD)
        {
            ulIntegrityCheckResult = MM_TRUE;
        }
        else
        {
        }
    }
    return ulIntegrityCheckResult;
}



VOS_BOOL NAS_MM_IsIdleState()
{
    VOS_BOOL                            bIdle;

    bIdle = VOS_FALSE;

    switch (g_MmGlobalInfo.ucState)
    {
        case MM_IDLE_NO_CELL_AVAILABLE:
        case MM_IDLE_PLMN_SEARCH:
        case MM_IDLE_NORMAL_SERVICE:
        case MM_IDLE_LIMITED_SERVICE:
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
        case MM_IDLE_NO_IMSI:
        case LOCATION_UPDATING_PENDING:
        /* ����������ecall inactive״̬��Ҳ��һ��IDLE̬ */
        case MM_IDLE_ECALL_INACTIVE:
            bIdle = VOS_TRUE;
            break;

        default:

            break;
    }


    return bIdle;
}
VOS_VOID NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(
    VOS_UINT32                          ulCurFobidnFlg
)
{
    if (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS == (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS & ulCurFobidnFlg))
    {
        if (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);

            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_SndMmcForbidenRslt();
    }

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN);

    g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

    /* ��FORBIDEN��ͳһ���� */
    g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

    Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_NULL);

    Mm_DealWithBuffMsg();

    return;
}




VOS_VOID NAS_MM_ResetRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_ResetHplmnCsRejCauseChangedCounter();
    NAS_MML_ResetVplmnCsRejCauseChangedCounter();
}




VOS_VOID NAS_MM_HandleHplmnRejCauseChange(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                          *pucRcvMsg
)
{
    VOS_UINT8                           ucAdaptCause = 0;

    ucAdaptCause = NAS_MML_GetHplmnChangeNWCause(enChangeRejType, pucRcvMsg[2]);
    if (ucAdaptCause == pucRcvMsg[2])
    {
        /* δ���ҵ��滻��ԭ��ֵ�����滻��ԭ��ֵ���� */
        return;
    }

    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == ucAdaptCause)
    {
        if (VOS_TRUE != NAS_MML_GetHplmnCsRejChangeTo17Flg())
        {
            /* ����滻��ԭ��ֵΪ#17�����滻�������Ѿ��ﵽ���ޣ������滻 */
            return;
        }

        /* ������+1 */
        NAS_MML_IncHplmnCsRejCauseChangedCounter();
    }

    /* ����滻���ԭ��ֵ��#17�����滻���ԭ��ֵΪ#17���滻����δ�ﵽ���ޣ����滻 */
    pucRcvMsg[2] = ucAdaptCause;
}


VOS_VOID NAS_MM_HandleVplmnRejCauseChange(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                          *pucRcvMsg
)
{
    VOS_UINT8                           ucAdaptCause = 0;

    ucAdaptCause = NAS_MML_GetVplmnChangeNWCause(enChangeRejType, pucRcvMsg[2]);
    if (ucAdaptCause == pucRcvMsg[2])
    {
        /* δ���ҵ��滻��ԭ��ֵ�����滻��ԭ��ֵ���� */
        return;
    }
    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == ucAdaptCause)
    {
        if (VOS_TRUE != NAS_MML_GetVplmnCsRejChangeTo17Flg())
        {
            /* ����滻��ԭ��ֵΪ#17�����滻�������Ѿ��ﵽ���ޣ������滻 */
            return;
        }

        /* ������+1 */
        NAS_MML_IncVplmnCsRejCauseChangedCounter();
    }

    /* ����滻���ԭ��ֵ��#17�����滻���ԭ��ֵΪ#17���滻����δ�ﵽ���ޣ����滻 */
    pucRcvMsg[2] = ucAdaptCause;
}


VOS_VOID NAS_MM_ChangeRegRejCauseAvoidInvalidSim (
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize
)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId    = VOS_NULL_PTR;
    VOS_UINT32                          bIsRegisteredInHplmn = VOS_FALSE;

    /* ���Ӳ��Կ����������Կ�ʱ���޸ģ�ֱ�ӷ��� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ChangeRegRejCauseAvoidInvalidSim: The sim is Test card");
        return;
    }

    if (3 > usMsgSize)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ChangeRegRejCauseAvoidInvalidSim:WARNING: RCV MM LU REJECT MSG WITH ERROR SIZE!");
        return;
    }
    NAS_MML_SetOriginalRejectCause(pucRcvMsg[2]);

    /* ȡ�õ�ǰפ����PLMN���� */
    pstCurrCampPlmnId    = NAS_MML_GetCurrCampPlmnId();
    bIsRegisteredInHplmn = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    if (VOS_TRUE == bIsRegisteredInHplmn)
    {
        /* HPLMN */
        NAS_MM_HandleHplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_CS_REG, pucRcvMsg);
    }
    else
    {
        /* VPLMN */
        NAS_MM_HandleVplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_CS_REG, pucRcvMsg);

    }
}


VOS_VOID NAS_MM_ChangeMmAbortCauseAvoidInvalidSim (
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize
)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId    = VOS_NULL_PTR;
    VOS_UINT32                          bIsRegisteredInHplmn = VOS_FALSE;

    /* ���Ӳ��Կ����������Կ�ʱ���޸ģ�ֱ�ӷ��� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ChangeMmAbortCauseAvoidInvalidSim: The sim is Test card");
        return;
    }

    if (3 > usMsgSize)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ChangeMmAbortCauseAvoidInvalidSim:WARNING: RCV MM ABORT MSG WITH ERROR SIZE!");
        return;
    }
    NAS_MML_SetOriginalRejectCause(pucRcvMsg[2]);
    /* ȡ�õ�ǰפ����PLMN���� */
    pstCurrCampPlmnId    = NAS_MML_GetCurrCampPlmnId();
    bIsRegisteredInHplmn = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    if (VOS_TRUE == bIsRegisteredInHplmn)
    {
        /* HPLMN */
        NAS_MM_HandleHplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_MM_ABORT, pucRcvMsg);
    }
    else
    {
        /* VPLMN */
        NAS_MM_HandleVplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_MM_ABORT, pucRcvMsg);
    }
}


VOS_VOID NAS_MM_ChangeCmSerRejCauseAvoidInvalidSim (
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize
)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId    = VOS_NULL_PTR;
    VOS_UINT32                          bIsRegisteredInHplmn = VOS_FALSE;

    /* ���Ӳ��Կ����������Կ�ʱ���޸ģ�ֱ�ӷ��� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ChangeCmSerRejCauseAvoidInvalidSim: The sim is Test card");
        return;
    }

    if (3 > usMsgSize)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ChangeCmSerRejCauseAvoidInvalidSim:WARNING: RCV CM SERVICE REJECT MSG WITH ERROR SIZE!");
        return;
    }
    NAS_MML_SetOriginalRejectCause(pucRcvMsg[2]);
    /* ȡ�õ�ǰפ����PLMN���� */
    pstCurrCampPlmnId    = NAS_MML_GetCurrCampPlmnId();
    bIsRegisteredInHplmn = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    if (VOS_TRUE == bIsRegisteredInHplmn)
    {
        /* HPLMN */
        NAS_MM_HandleHplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_CM_SER_REJ, pucRcvMsg);
    }
    else
    {
        /* VPLMN */
        NAS_MM_HandleVplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_CM_SER_REJ, pucRcvMsg);
    }
}


VOS_UINT8 Mm_ComMsgChkProc(
                        RRMM_DATA_IND_FOR_PCLINT_STRU       *pMsg               /* ��ǰ�������Ϣ                           */
                        )
{
    VOS_UINT8                          *pucRcvMsg = pMsg->RcvNasMsg.aucNasMsg;                             /* �����Ϣָ��                             */
    VOS_UINT16                          usMsgSize = (VOS_UINT16)pMsg->RcvNasMsg.ulNasMsgSize;                  /* �����Ϣ��Size                           */
    VOS_UINT8                           ucEventId;                                                         /* �¼�ID                                   */
    MM_MSG_MM_STATUS_STRU               Msg;

    if ( usMsgSize < 2 )
    {
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgChkProc:WARNING: RCV MSG TOO SHORT!");
    }

    /* �����Ա������ */
    if (MM_FALSE == MM_ComCheckIntegrityProtection(pucRcvMsg, usMsgSize))
    {
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgChkProc:WARNING:  Integrity Check Fail!");
    }
    else
    {
        /*�յ�NAS����Ϣ����ȫ�ֱ���ΪTRUE*/
        g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_TRUE;

        switch ( pucRcvMsg[0] & 0x0f )
        {                                                                           /* �ж�PD                                   */
        case MM_IE_PD_CALL_CONTROL:                                                 /* CC����Ϣ                                 */
            ucEventId = Mm_ComMsgCcMsgInteChk(pMsg);
            break;
        case MM_IE_PD_SMS_MSG:                                                      /* SMS����Ϣ                                */
            ucEventId = MM_EVENT_ID_SMS_MESSAGE;
            break;
        case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                          /* SS����Ϣ                                 */
        case MM_IE_PD_LOCATION_SRVC:                                                /* LCS����Ϣ                                */
            ucEventId = MM_EVENT_ID_SS_MESSAGE;
            break;
        case MM_IE_PD_TEST:                                                         /* TC����Ϣ                                 */
            ucEventId = MM_EVENT_ID_TC_MESSAGE;
            break;
        case MM_IE_PD_MM_MSG:                                                       /* MM����Ϣ                                 */
            if ( 0 != ( pucRcvMsg[0] & 0xf0 ) )
            {
                ucEventId = MM_EVENT_ID_INVALID;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgChkProc:WARNING: RCV MM MSG SKIP INDICATOR ERROR!");
                break;
            }

            MM_ReportN2MOtaMsg(pucRcvMsg[1] & 0x3f, (NAS_MSG_STRU *)(&(pMsg->RcvNasMsg)));


            switch ( pucRcvMsg[1] & 0x3f )
            {                                                                       /* �ж�MM��Ϣ������                         */
            case MM_IE_MSG_TYPE_AUTH_REQ:                                           /* AUTHENTICATION REQUEST ��Ϣ              */
                ucEventId = Mm_ComMsgAuthReqRcv ( pucRcvMsg, usMsgSize );           /* �洢��Ϣ������¼�ID                     */
                break;
            case MM_IE_MSG_TYPE_CM_SERV_REJ:                                        /* CM SERVICE REJECT ��Ϣ                   */
                NAS_MM_ChangeCmSerRejCauseAvoidInvalidSim (pucRcvMsg, usMsgSize);

                ucEventId = Mm_ComMsgCmSvcRjctRcv ( pucRcvMsg, usMsgSize );         /* �洢��Ϣ������¼�ID                     */
                g_T3211Flag = 0;
                break;
            case MM_IE_MSG_TYPE_CM_SERV_ACP:                                        /* CM SERVICE ACCEPT ��Ϣ                   */
                ucEventId = Mm_ComMsgCmSvcAcceptRcv(pMsg);                          /* ����¼�ID                               */
                g_T3211Flag = 0;
                break;
            case MM_IE_MSG_TYPE_AUTH_REJ:                                           /* AUTHENTICATION REJECT ��Ϣ               */
                ucEventId = Mm_ComMsgAuthRjctRcv();                                 /* ����¼�ID                               */
                break;
            case MM_IE_MSG_TYPE_ABORT:                                              /* ABORT ��Ϣ                               */
                NAS_MM_ChangeMmAbortCauseAvoidInvalidSim (pucRcvMsg, usMsgSize);
                ucEventId = Mm_ComMsgAbortRcv ( pucRcvMsg, usMsgSize );             /* �洢��Ϣ������¼�ID                     */
                break;
            case MM_IE_MSG_TYPE_ID_REQ:                                             /* IDENTITY REQUEST ��Ϣ                    */
                ucEventId = Mm_ComMsgIdReqRcv ( pucRcvMsg, usMsgSize );             /* �洢��Ϣ������¼�ID                     */
                break;
            case MM_IE_MSG_TYPE_MM_INFO:                                            /* MM INFORMATION ��Ϣ                      */
                ucEventId = Mm_ComMsgMmInfoRcv ( pucRcvMsg, usMsgSize );        /* �洢��Ϣ������¼�ID */
                break;
            case MM_IE_MSG_TYPE_MM_STA:                                             /* MM STATUS ��Ϣ                           */
                ucEventId = Mm_ComMsgMmStatusRcv ( pucRcvMsg, usMsgSize );      /* �洢��Ϣ������¼�ID                     */
                break;
            case MM_IE_MSG_TYPE_TMSI_REALLOC_CMD:                                   /* TMSI REALLOCATION COMMAND ��Ϣ           */
                ucEventId =
                            Mm_ComMsgTmsiReallocCmdRcv ( pucRcvMsg, usMsgSize );    /* �洢��Ϣ������¼�ID   */
                break;
            case MM_IE_MSG_TYPE_LU_ACCEPT:
                ucEventId = Mm_ComMsgLuAccptRcv( pucRcvMsg, usMsgSize  );
                break;
            case MM_IE_MSG_TYPE_LU_REJECT:
                NAS_MM_ChangeRegRejCauseAvoidInvalidSim( pucRcvMsg, usMsgSize );
                ucEventId = Mm_ComMsgLuRejctRcv( pucRcvMsg, usMsgSize  );
                break;
            case MM_IE_MSG_TYPE_CM_SERV_PROMPT:
                ucEventId = Mm_ComMsgSvcPromptRcv( pucRcvMsg, usMsgSize );
                break;
            default:
                ucEventId = MM_EVENT_ID_INVALID;                                    /* ��Ч���¼�ID                             */

                Msg.MmIeRjctCause.ucRejCause =
                                NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE;
                Mm_ComMsgMmStatusSnd(&Msg);

                break;
            }
            break;
        default:
            ucEventId = MM_EVENT_ID_INVALID;                                        /* ��Ч���¼�ID                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgChkProc:WARNING: RCV NAS MSG PD UNKNOW!");
            break;
        }
    }

    return ucEventId;                                                           /* �����¼�ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgAuthRspSnd
  Function: ��䲢���� AUTHENTICATION RESPONSE ��Ϣ
  Input:    MM_MSG_AUTHENTICATION_RSP_STRU *pMsg,Ҫ���͵���Ϣ��ָ��
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��   2003.12.10   �°�����
*******************************************************************************/
VOS_VOID Mm_ComMsgAuthRspSnd(
                          MM_MSG_AUTHENTICATION_RSP_STRU    *pMsg               /* Ҫ���͵���Ϣ��ָ��                       */
                         )
{
    VOS_UINT8               i;                                                  /* ѭ������                                 */
    VOS_UINT16              usMsgSize = 20;                                     /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* ������Ϣָ��                             */

    if ( MM_IE_AUTN_EXT_PRESENT == pMsg->ucAutnRspParaExtFlg )
    {                                                                           /* AUTN Extention ����                      */
        usMsgSize = (VOS_UINT16)(8 + pMsg->MmIeAuthRspParaExt.ucLength);
    }
    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgAuthRspSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* ����                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* ����PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_AUTH_RES;                                 /* ����Message type                         */
        for ( i = MM_CONST_NUM_0; i < MM_CONST_NUM_4; i++ )
        {
            pucSndMsg[2+i] = pMsg->MmIeAuthRspPara.aucSgnfcntRES[i];            /* ����AUTN                                 */
        }
        if ( MM_IE_AUTN_EXT_PRESENT == pMsg->ucAutnRspParaExtFlg )
        {                                                                       /* AUTN Extention ����                      */
            pucSndMsg[6] = 0x21;                                                /* ����AUTN Extention��IEI                  */
            pucSndMsg[7] = pMsg->MmIeAuthRspParaExt.ucLength;                   /* ����Length of AUTN Extention             */
            for(i = MM_CONST_NUM_0; i < pMsg->MmIeAuthRspParaExt.ucLength; i++)
            {
                pucSndMsg[8+i] = pMsg->MmIeAuthRspParaExt.aucRES[i];            /* ����AUTN Extention������                 */
            }
            usMsgSize = (VOS_UINT16)(8 + pMsg->MmIeAuthRspParaExt.ucLength);    /* ������Ϣʵ�ʳ���                         */
        }
        else
        {                                                                       /* AUTN Extention ������                    */
            usMsgSize = 6;                                                      /* ������Ϣʵ�ʳ���                         */
        }

        #ifdef GSM_GCF_RS_SIM_STUB
        pucSndMsg[2] = 0x11;
        pucSndMsg[3] = 0x10;
        pucSndMsg[4] = 0x13;
        pucSndMsg[5] = 0x12;
        usMsgSize    = 6;
        #endif
        Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);

        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgAuthFailSnd
  Function: ��䲢���� AUTHENTICATION FAILURE ��Ϣ
  Input:    MM_MSG_AUTHENTICATION_FAIL_STRU *pMsg,Ҫ���͵���Ϣ��ָ��
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��   2003.12.10   �°�����
*******************************************************************************/
VOS_VOID Mm_ComMsgAuthFailSnd(
                          MM_MSG_AUTHENTICATION_FAIL_STRU    *pMsg              /* Ҫ���͵���Ϣ��ָ��                       */
                            )
{
    VOS_UINT8               i;                                                      /* ѭ������                                 */
    VOS_UINT16              usMsgSize = 19;                                         /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                                       /* ������Ϣָ��                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgAuthFailSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* ����                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* ����PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_AUTH_FAIL;                                /* ����Message type                         */
        pucSndMsg[2] = pMsg->MmIeRejCause.ucRejCause;                           /* ����Reject Cause                         */

        if ( NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE == pMsg->MmIeRejCause.ucRejCause )
        {                                                                       /* �ܾ�ԭ��Ϊ Synch failure                 */
            pucSndMsg[3] = 0x22;                                                /* ����Authentication Failure parameter��IE
                                                                                 * I                                        */
            pucSndMsg[4] = pMsg->MmIeAuthFailPara.ucLength;                     /* ����Length of Authentication Failurepara
                                                                                 * meter contents                           */
            for (i = MM_CONST_NUM_0; i < pMsg->MmIeAuthFailPara.ucLength; i++)
            {
                pucSndMsg[5+i] = pMsg->MmIeAuthFailPara.aucAuthFailPara[i];     /* ����Authentication Failure parameter     */
            }
        }
        else
        {                                                                       /* �ܾ�ԭ��Ϊ MAC failure                   */
            usMsgSize = 3;                                                      /* ������Ϣʵ�ʳ���                         */
        }

        Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);

        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
    }
    return;                                                                     /* ����                                     */
}
VOS_UINT8 Mm_ComMsgSetMobileId(
                            VOS_UINT8                  *pucSndMsg,              /* ��Ϣ���׵�ַ                             */
                            VOS_UINT16                 *pusMsgSize,             /* ��ϢĿǰ�ĳ���                           */
                            MM_MOBILE_ID_STRU          *pMobileId               /* Դ����ָ��                               */
                            )
{
    VOS_UINT8                           i;                                                  /* ѭ������                                 */
    VOS_UINT16                          usIndex = *pusMsgSize;                              /* λ������                                 */
    VOS_UINT8                          *pTmpImsi;

    /* TMSI��Ч���ҵ�ǰפ������������TMSI������Ϊ��ͬ������ЧPLMN�� */
    if (MM_MS_ID_TMSI_PRESENT == (pMobileId->ucMsIdFlg & MM_MS_ID_TMSI_PRESENT))
    {

        pucSndMsg[usIndex] = 0x05;                                              /* ����Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = 0xf0 | MM_IE_MI_ID_TYPE_TMSI;                    /* ����Type of identity ����ż��־λ        */
        for ( i = MM_CONST_NUM_0; i < MM_CONST_NUM_4; i++ )
        {
            pucSndMsg[usIndex+2+i]
                = (VOS_UINT8)(pMobileId->aucTmsi[i]);                           /* ����TMSI������                           */
        }
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* ������Ϣʵ�ʳ���                         */
    }
    else if ( MM_MS_ID_IMSI_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMSI_PRESENT) )
    {

        pTmpImsi = NAS_MML_GetSimImsi();
        PS_MEM_CPY(&pucSndMsg[usIndex],
                   pTmpImsi,
                   pTmpImsi[0]+1);

        *pusMsgSize = (VOS_UINT16)(usIndex + pTmpImsi[0] + 1);           /* ������Ϣʵ�ʳ���                         */
    }
    else if ( MM_MS_ID_IMEI_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMEI_PRESENT) )
    {
        pucSndMsg[usIndex] = 0x08;                                              /* ����Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = (VOS_UINT8)(pMobileId->aucImei[0] & 0xf0);       /* ����pucSndMsg[usIndex+1]�ĸ���λΪdigit1 */
        pucSndMsg[usIndex+1] |= MM_IE_MI_ID_TYPE_IMEI | 0x08;                   /* ����pucSndMsg[usIndex+1]��4λΪ��ż��־
                                                                                 * λ��Typeof identity                      */
        for ( i = MM_CONST_NUM_1; i < pucSndMsg[usIndex]; i++ )
        {
            pucSndMsg[usIndex+1+i] = pMobileId->aucImei[i];                     /* ����IMEIʣ���digits                     */
        }
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* ������Ϣʵ�ʳ���                         */
    }
    else if ( MM_MS_ID_IMEISV_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMEISV_PRESENT) )
    {
        pucSndMsg[usIndex] = 0x09;                                              /* ����Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = (VOS_UINT8)(pMobileId->aucImeisv[0] & 0xf0);     /* ����pucSndMsg[usIndex+1]����λΪdigit 1  */
        pucSndMsg[usIndex+1] |= MM_IE_MI_ID_TYPE_IMEISV;                        /* ����pucSndMsg[usIndex+1]��4λΪ��ż��־
                                                                                   λ��Typeof identity                      */
        for ( i = MM_CONST_NUM_1; i < pucSndMsg[usIndex]; i++ )
        {
            pucSndMsg[usIndex+1+i] = pMobileId->aucImeisv[i];                   /* ����IMEISVʣ���digits                   */
        }
        pucSndMsg[usIndex+pucSndMsg[usIndex]] |= 0xf0;                          /* ������Ϣ���һ���ֽڵĸ���λΪ"1111"     */
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* ������Ϣʵ�ʳ���                         */
    }
    else
    {
        pucSndMsg[usIndex] = 0x01;                                              /* ����Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = 0xf0;                                            /* ����pucSndMsg[usIndex+1]��4λΪ��ż��־
                                                                                   λ��Typeof identity, ����λΪ"1111"      */
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* ������Ϣʵ�ʳ���                         */
    }

    return MM_TRUE;                                                             /* ����                                     */
}



VOS_UINT8 NAS_MM_SetPagingRspMobileId(
    VOS_UINT8                          *pucSndMsg,
    VOS_UINT16                         *pusMsgSize,
    MM_MOBILE_ID_STRU                  *pMobileId
)
{
    VOS_UINT8                           i;                                                  /* ѭ������                                 */
    VOS_UINT16                          usIndex = *pusMsgSize;                             /* λ������                                 */
    VOS_UINT8                          *pTmpImsi;

    /* TMSI��Ч���ҵ�ǰפ������������TMSI�����粢��Ҫ��Ϊ��ͬ������ЧPLMN�� */
    if (((MM_TMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
      || (MM_STMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId))
     && (MM_MS_ID_TMSI_PRESENT == (pMobileId->ucMsIdFlg & MM_MS_ID_TMSI_PRESENT)))
    {
        pucSndMsg[usIndex] = 0x05;                                              /* ����Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = 0xf0 | MM_IE_MI_ID_TYPE_TMSI;                    /* ����Type of identity ����ż��־λ        */
        for ( i = MM_CONST_NUM_0; i < MM_CONST_NUM_4; i++ )
        {
            pucSndMsg[usIndex+2+i]
                = (VOS_UINT8)(pMobileId->aucTmsi[i]);                           /* ����TMSI������                           */
        }
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* ������Ϣʵ�ʳ���                         */
    }
    else if ( MM_MS_ID_IMSI_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMSI_PRESENT) )
    {

        pTmpImsi = NAS_MML_GetSimImsi();
        PS_MEM_CPY(&pucSndMsg[usIndex],
                   pTmpImsi,
                   pTmpImsi[0]+1);

        *pusMsgSize = (VOS_UINT16)(usIndex + pTmpImsi[0] + 1);           /* ������Ϣʵ�ʳ���                         */
    }
    else if ( MM_MS_ID_IMEI_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMEI_PRESENT) )
    {
        pucSndMsg[usIndex] = 0x08;                                              /* ����Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = (VOS_UINT8)(pMobileId->aucImei[0] & 0xf0);       /* ����pucSndMsg[usIndex+1]�ĸ���λΪdigit1 */
        pucSndMsg[usIndex+1] |= MM_IE_MI_ID_TYPE_IMEI | 0x08;                   /* ����pucSndMsg[usIndex+1]��4λΪ��ż��־
                                                                                 * λ��Typeof identity                      */
        for ( i = MM_CONST_NUM_1; i < pucSndMsg[usIndex]; i++ )
        {
            pucSndMsg[usIndex+1+i] = pMobileId->aucImei[i];                     /* ����IMEIʣ���digits                     */
        }
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* ������Ϣʵ�ʳ���                         */
    }
    else if ( MM_MS_ID_IMEISV_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMEISV_PRESENT) )
    {
        pucSndMsg[usIndex] = 0x09;                                              /* ����Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = (VOS_UINT8)(pMobileId->aucImeisv[0] & 0xf0);     /* ����pucSndMsg[usIndex+1]����λΪdigit 1  */
        pucSndMsg[usIndex+1] |= MM_IE_MI_ID_TYPE_IMEISV;                        /* ����pucSndMsg[usIndex+1]��4λΪ��ż��־
                                                                                   λ��Typeof identity                      */
        for ( i = MM_CONST_NUM_1; i < pucSndMsg[usIndex]; i++ )
        {
            pucSndMsg[usIndex+1+i] = pMobileId->aucImeisv[i];                   /* ����IMEISVʣ���digits                   */
        }
        pucSndMsg[usIndex+pucSndMsg[usIndex]] |= 0xf0;                          /* ������Ϣ���һ���ֽڵĸ���λΪ"1111"     */
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* ������Ϣʵ�ʳ���                         */
    }
    else
    {
        pucSndMsg[usIndex] = 0x01;                                              /* ����Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = 0xf0;                                            /* ����pucSndMsg[usIndex+1]��4λΪ��ż��־
                                                                                   λ��Typeof identity, ����λΪ"1111"      */
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* ������Ϣʵ�ʳ���                         */
    }

    return MM_TRUE;                                                             /* ����                                     */
}



VOS_UINT8 Mm_ComMsgSetMobileIdForEmc(
                            VOS_UINT8                  *pucSndMsg,              /* ��Ϣ���׵�ַ                             */
                            VOS_UINT16                 *pusMsgSize,             /* ��ϢĿǰ�ĳ���                           */
                            MM_MOBILE_ID_STRU          *pMobileId               /* Դ����ָ��                               */
                            )
{
    VOS_UINT8               i;                                                  /* ѭ������                                 */
    VOS_UINT16              usIndex = *pusMsgSize;                              /* λ������                                 */
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    VOS_UINT8              *pucIMSI;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
      && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
      && (MM_MS_ID_TMSI_PRESENT == (pMobileId->ucMsIdFlg & MM_MS_ID_TMSI_PRESENT)))
    {
        pucSndMsg[usIndex] = 0x05;                                              /* ����Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = 0xf0 | MM_IE_MI_ID_TYPE_TMSI;                    /* ����Type of identity ����ż��־λ        */

        for ( i = MM_CONST_NUM_0; i < MM_CONST_NUM_4; i++ )
        {
            pucSndMsg[usIndex+2+i]
                = (VOS_UINT8)(pMobileId->aucTmsi[i]);                           /* ����TMSI������                           */
        }

        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* ������Ϣʵ�ʳ���                         */
    }

    else if (MM_MS_ID_IMSI_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMSI_PRESENT))
    {

        pucIMSI = NAS_MML_GetSimImsi();

        pucSndMsg[usIndex] = pucIMSI[0];


        PS_MEM_CPY(&pucSndMsg[usIndex+1],
               pucIMSI + 1,
               pucIMSI[0]);

        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* ������Ϣʵ�ʳ���                         */
    }

    else if (MM_MS_ID_IMEI_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMEI_PRESENT))
    {
        pucSndMsg[usIndex] = 0x08;                                              /* ����Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = (VOS_UINT8)(pMobileId->aucImei[0] & 0xf0);       /* ����pucSndMsg[usIndex+1]�ĸ���λΪdigit1 */
        pucSndMsg[usIndex+1] |= MM_IE_MI_ID_TYPE_IMEI | 0x08;                   /* ����pucSndMsg[usIndex+1]��4λΪ��ż��־
                                                                                 * λ��Typeof identity                      */
        for ( i = MM_CONST_NUM_1; i < pucSndMsg[usIndex]; i++ )
        {
            pucSndMsg[usIndex+1+i] = pMobileId->aucImei[i];                     /* ����IMEIʣ���digits                     */
        }

        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* ������Ϣʵ�ʳ���                         */
    }

    else
    {
        pucSndMsg[usIndex] = 0x01;                                              /* ����Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = MM_IE_MI_ID_TYPE_NO_ID | 0x08;                   /* ����pucSndMsg[usIndex+1]��4λΪ��ż��־
                                                                                   λ��Typeof identity, ����λΪ"1111"      */
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* ������Ϣʵ�ʳ���                         */
    }

    return MM_TRUE;
}
VOS_VOID Mm_ComMsgCmSvcReqSnd(
                          MM_MSG_CM_SVC_REQ_STRU    *pMsg                       /* Ҫ���͵���Ϣ��ָ��                       */
                            )
{
    VOS_UINT16              usMsgSize = 19;                                     /* ��Ϣ����,���ֽ�Ϊ��λ                    */

    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* ������Ϣָ��                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgCmSvcReqSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                 /* ����                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* ����PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_CM_SERV_REQ;                              /* ����Message type                         */

        pucSndMsg[2] = (VOS_UINT8)(pMsg->MmIeCmSvcType.ucCMSvcType & 0x0f);         /* ����CM service type                      */
        pucSndMsg[2] = (VOS_UINT8)(pucSndMsg[2] | (pMsg->MmIeCKSN.ucCksn << 4));    /* ����CKSN                                 */

        MM_Fill_IE_ClassMark2(&pucSndMsg[3]);

        usMsgSize = 7;                                                          /* ������Ϣʵ�ʳ���                         */
        if ( MM_TRUE == Mm_ComMsgSetMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID))
        {
            if ( MM_TRUE == pMsg->ucPrioLeveFlg )
            {                                                                   /* �������Priority                         */
                pucSndMsg[usMsgSize] = (VOS_UINT8)(0x80
                    | (pMsg->MmIePrio.ucPrioLeve & MM_IE_PRIO_LEVE_MASK));      /* ����Priority��IEI�;�������              */
                usMsgSize++;                                                    /* ������Ϣʵ�ʳ���                         */
            }

#if (FEATURE_ON == FEATURE_LTE)
            NAS_MM_SetCsfbAdditionalUpdateParameters(VOS_FALSE, NAS_MM_IsNeedSetCsmoFlg(), &usMsgSize, pucSndMsg);
#endif

            Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);

        }
        else
        {
            /*WUEPS_ASSERT(0);
 */
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                    /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
        Mm_TimerStop(MM_TIMER_T3211);
    }
    return;                                                                     /* ����                                     */
}


VOS_UINT8* Mm_ComMsgCmSvcReqOfRrEstReq(
                                    MM_MSG_CM_SVC_REQ_STRU    *pMsg,            /* Ҫ���͵���Ϣ��ָ��                       */
                                    VOS_UINT16                *pusMsgSize       /* ��Ϣ�ĳ���ָ��                           */
                                    )
{
    VOS_UINT16              usMsgSize = 19;                                     /* ��Ϣ����,���ֽ�Ϊ��λ                    */

    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* ������Ϣָ��                             */

    *pusMsgSize = 0;                                                            /* ��Ϣ���ȳ�ʼ��Ϊ0                        */

    pucSndMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    if ( VOS_NULL_PTR != pucSndMsg )
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* ����                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* ����PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_CM_SERV_REQ;                              /* ����Message type                         */

        pucSndMsg[2] = (VOS_UINT8)(pMsg->MmIeCmSvcType.ucCMSvcType & 0x0f);     /* ����CM service type                      */
        pucSndMsg[2] = (VOS_UINT8)(pucSndMsg[2] | (pMsg->MmIeCKSN.ucCksn << 4));/* ����CKSN                                 */

        MM_Fill_IE_ClassMark2(&pucSndMsg[3]);

        usMsgSize = 7;                                                          /* ������Ϣʵ�ʳ���                         */

        if (MM_IE_CM_SVC_TYPE_EMG_CALL_EST == pMsg->MmIeCmSvcType.ucCMSvcType)
        {
            if (MM_TRUE == Mm_ComMsgSetMobileIdForEmc(pucSndMsg, &usMsgSize,
                                                    &pMsg->MmIeMobileId.MobileID))
            {
                if (MM_TRUE == pMsg->ucPrioLeveFlg)
                {                                                               /* �������Priority                         */
                    pucSndMsg[usMsgSize] = (VOS_UINT8)(0x80
                        | (pMsg->MmIePrio.ucPrioLeve & MM_IE_PRIO_LEVE_MASK));  /* ����Priority��IEI�;�������              */
                    usMsgSize++;                                                /* ������Ϣʵ�ʳ���                         */
                }
                *pusMsgSize = usMsgSize;                                        /* ������Ϣ�ĳ���,���������ʹ��            */
            }
            else
            {
                MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                  /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
                pucSndMsg = VOS_NULL_PTR;                                       /* ָ�븳��                                 */
                *pusMsgSize = 0;                                                /* ��Ϣ������Ϊ0                            */
            }
        }
        else
        {
            if (MM_TRUE == Mm_ComMsgSetMobileId(pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID))
            {
                if (MM_TRUE == pMsg->ucPrioLeveFlg)
                {                                                               /* �������Priority                         */
                    pucSndMsg[usMsgSize] = (VOS_UINT8)(0x80
                        | (pMsg->MmIePrio.ucPrioLeve & MM_IE_PRIO_LEVE_MASK));  /* ����Priority��IEI�;�������              */
                    usMsgSize++;                                                /* ������Ϣʵ�ʳ���                         */
                }
                *pusMsgSize = usMsgSize;                                        /* ������Ϣ�ĳ���,���������ʹ��            */
            }
            else
            {
                MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                  /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
                pucSndMsg = VOS_NULL_PTR;                                       /* ָ�븳��                                 */
                *pusMsgSize = 0;                                                /* ��Ϣ������Ϊ0                            */
            }
        }

        if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
        {
            Mm_TimerStop(MM_TIMER_T3211);
        }

#if (FEATURE_ON == FEATURE_LTE)
        NAS_MM_SetCsfbAdditionalUpdateParameters(VOS_FALSE, NAS_MM_IsNeedSetCsmoFlg(), pusMsgSize, pucSndMsg);
#endif

    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgCmSvcReqOfRrEstReq:ERROR: MALLOC ERROR!");
    }
    return pucSndMsg;                                                           /* ����                                     */
}
VOS_VOID Mm_ComMsgCmReEstReqSnd(
                            MM_MSG_RE_EST_REQ_STRU    *pMsg                     /* Ҫ���͵���Ϣ��ָ��                       */
                            )
{
    VOS_UINT16              usMsgSize = 23;                                     /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* ������Ϣָ��                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgCmReEstReqSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* ����                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* ����PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_REEST_REQ;                                /* ����Message type                         */

        pucSndMsg[2]
            = (VOS_UINT8)(pMsg->MmIeCKSN.ucCksn & MM_IE_CKSN_KEY_SEQUENCE_MASK);/* ����CKSN                                 */

        MM_Fill_IE_ClassMark2(&pucSndMsg[3]);

        usMsgSize = 7;                                                          /* ������Ϣʵ�ʳ���                         */
        if ( MM_TRUE == Mm_ComMsgSetMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID))
        {
            if (MM_MS_ID_TMSI_PRESENT
                == ( MM_MS_ID_TMSI_PRESENT &
                pMsg->MmIeMobileId.MobileID.ucMsIdFlg ) )
            {                                                                   /* ���Mobile IdΪTMSI,����Ҫ����LAI        */
                pucSndMsg[usMsgSize] = 0x13;                                    /* ����LAI��IEI                             */
                pucSndMsg[usMsgSize+1]
                    = (VOS_UINT8)((pMsg->MmIeLai.IeLai.PlmnId.ulMcc >> 4)
                                | pMsg->MmIeLai.IeLai.PlmnId.ulMcc );           /* ����MCC digit 2,digit 1                  */
                pucSndMsg[usMsgSize+2]
                    = (VOS_UINT8)((pMsg->MmIeLai.IeLai.PlmnId.ulMcc >> 16)
                                | (pMsg->MmIeLai.IeLai.PlmnId.ulMnc >> 12));    /* ����MNC digit 3, MCC digit 3             */
                pucSndMsg[usMsgSize+3]
                    = (VOS_UINT8)((pMsg->MmIeLai.IeLai.PlmnId.ulMnc >> 4)
                                | pMsg->MmIeLai.IeLai.PlmnId.ulMnc );           /* ����MNC digit 2,digit 1                  */

                pucSndMsg[usMsgSize+4] = (VOS_UINT8)(pMsg->MmIeLai.IeLai.ulLac>>8);      /* ����LAC��8λ                             */
                pucSndMsg[usMsgSize+5] = (VOS_UINT8)pMsg->MmIeLai.IeLai.ulLac; /* ����LAC��8λ                             */

                usMsgSize += 6;                                                 /* ������Ϣʵ�ʳ���                         */

            }
            if (MMCC_EMERGENCY_CALL == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType)
            {
                Mm_SndRrEstReq( RRC_EST_CAUSE_EMERGENCY_CALL_RE_ESTABLISH, MM_FALSE,
                    usMsgSize, pucSndMsg );                                         /* ������Ϣ                                 */
            }
            else
            {
                Mm_SndRrEstReq( RRC_EST_CAUSE_CALL_RE_ESTABLISH, MM_FALSE,
                    usMsgSize, pucSndMsg );                                         /* ������Ϣ                                 */
            }
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgCmReEstReqSnd:WARNING: MSG SET MOBILE ID ERROR!");
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgIdRspSnd
  Function: ��䲢���� IDENTITY RESPONSE ��Ϣ
  Input:    MM_MSG_ID_RSP_STRU *pMsg,Ҫ���͵���Ϣ��ָ��
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��   2003.12.11   �°�����
*******************************************************************************/
VOS_VOID Mm_ComMsgIdRspSnd(
                          MM_MSG_ID_RSP_STRU    *pMsg                           /* Ҫ���͵���Ϣ��ָ��                       */
                            )
{
    VOS_UINT16              usMsgSize = 12;                                     /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* ������Ϣָ��                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgIdRspSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* ����                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* ����PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_ID_RES;                                   /* ����Message type                         */

        usMsgSize = 2;                                                          /* ������Ϣʵ�ʳ���                         */
        if ( MM_TRUE == Mm_ComMsgSetMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID))
        {
            Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgIdRspSnd:WARNING: MSG SET MOBILE ID ERROR!");
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgMmStatusSnd
  Function: ��䲢���� MM STATUS ��Ϣ
  Input:    MM_MSG_MM_STATUS_STRU *pMsg,Ҫ���͵���Ϣ��ָ��
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��   2003.12.11   �°�����
*******************************************************************************/
VOS_VOID Mm_ComMsgMmStatusSnd(
                          MM_MSG_MM_STATUS_STRU    *pMsg                        /* Ҫ���͵���Ϣ��ָ��                       */
                            )
{
    VOS_UINT16              usMsgSize = 3;                                      /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* ������Ϣָ��                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgMmStatusSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* ����                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* ����PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_MM_STA;                                   /* ����Message type                         */
        pucSndMsg[2] = pMsg->MmIeRjctCause.ucRejCause;                          /* ����Reject Cause                         */

        Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);

        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgTmsiRelocCpltSnd
  Function: ��䲢���� TMSI REALLOCATION COMPLETE ��Ϣ
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��   2003.12.11   �°�����
*******************************************************************************/
VOS_VOID Mm_ComMsgTmsiRelocCpltSnd( )
{
    VOS_UINT16              usMsgSize = 2;                                      /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* ������Ϣָ��                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgTmsiRelocCpltSnd:ERROR: MALLOC ERROR!");
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* ����                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* ����PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_TMSI_REALLOC_CPL;                         /* ����Message type                         */

        Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);

        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
    }
    return;                                                                     /* ����                                     */
}


VOS_VOID Mm_ComMsgPagingRspSnd(
                            MM_MSG_PAGING_RSP_STRU    *pMsg                     /* Ҫ���͵���Ϣ��ָ��                       */
                            )
{
    VOS_UINT16              usMsgSize = 17;                                     /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* ������Ϣָ��                             */
    VOS_UINT8               ucEstCause  = 0;                                    /* RRC������ԭ��                            */
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbService ;

    enCsfbService = NAS_MML_GetCsfbServiceStatus();

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgPagingRspSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* ����                                     */

        pucSndMsg[0] = MM_IE_PD_RRM_MSG;                                        /* ����PD, Skip Indicator                   */

        pucSndMsg[1] = MM_IE_MSG_TYPE_PAGING_RSP;                               /* ����Message type                         */

        pucSndMsg[2]
            = (VOS_UINT8)(pMsg->MmIeCksn.ucCksn & MM_IE_CKSN_KEY_SEQUENCE_MASK);    /* ����CKSN                                 */

        MM_Fill_IE_ClassMark2(&pucSndMsg[3]);
        usMsgSize = 7;                                                          /* ������Ϣʵ�ʳ���                         */
        switch ( g_MmGlobalInfo.ucPagingCause )
            {                                                                   /* RRMM_PAGING_IND��RRMM_EST_REQ��causeת�� */
            case RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL:
                if ( (VOS_TRUE == NAS_MML_GetRelCauseCsfbHighPrioFlg())
                    && (NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == enCsfbService) )
                {
                    ucEstCause = RRC_EST_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL;
                }
                else
                {
                    ucEstCause = RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL;
                }
                break;
            case RRC_PAGE_CAUSE_TERMINAT_STREAM_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_STREAM_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_INTERACT_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_INTERACT_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_BACKGROUND_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_BACKGROUND_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_CAUSE_UNKNOWN:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_CAUSE_UNKNOWN;
                break;
            default:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_CAUSE_UNKNOWN;
                break;
            }

        if ( MM_TRUE == NAS_MM_SetPagingRspMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID) )
        {
            Mm_SndRrEstReq( ucEstCause, MM_TRUE,
                usMsgSize, pucSndMsg );                                         /* ������Ϣ                                 */
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgPagingRspSnd:WARNING: MSG SET MOBILE ID ERROR!");
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgCmSvcAbortSnd
  Function: ��䲢���� CM SERVICE ABORT ��Ϣ
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��   2003.12.11   �°�����
*******************************************************************************/
VOS_VOID Mm_ComMsgCmSvcAbortSnd( )
{
    VOS_UINT16              usMsgSize = 2;                                      /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                          /* ������Ϣָ��                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgCmSvcAbortSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* ����                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* ����PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_CM_SERV_ABO;                              /* ����Message type                         */

        Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);

        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
    }
    return;                                                                     /* ����                                     */
}


VOS_VOID Mm_ComMsgImsiDetachIniSndOfEstReq(
                                       MM_MSG_IMSI_DETACH_IND_STRU    *pMsg     /* Ҫ���͵���Ϣ��ָ��                       */
                                       )
{
    VOS_UINT16              usMsgSize = 13;                                     /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* ������Ϣָ��                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgImsiDetachIniSndOfEstReq:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* ����                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* ����PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_IMSI_DETACH_INDICATION;                   /* ����Message type                         */

        /* ����Mobile station classmark1             */
        MM_Fill_IE_ClassMark1(&pucSndMsg[2]);

        usMsgSize = 3;                                                          /* ������Ϣʵ�ʳ���                         */

        if ( MM_TRUE == Mm_ComMsgSetMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID) )
        {
            Mm_SndRrEstReq( RRC_EST_CAUSE_DETACH, MM_FALSE,
                usMsgSize, pucSndMsg );                                         /* ������Ϣ                                 */
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgImsiDetachIniSndOfEstReq:WARNING: MSG SET MOBILE ID ERROR!");
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
    }
    return;                                                                     /* ����                                     */
}


VOS_VOID Mm_ComMsgImsiDetachIniSndOfDataReq(
                                       MM_MSG_IMSI_DETACH_IND_STRU    *pMsg     /* Ҫ���͵���Ϣ��ָ��                       */
                                       )
{
    VOS_UINT16              usMsgSize = 13;                                     /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* ������Ϣָ��                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgImsiDetachIniSndOfDataReq:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* ����                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* ����PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_IMSI_DETACH_INDICATION;                   /* ����Message type                         */

        /* ����Mobile station classmark1             */
        MM_Fill_IE_ClassMark1(&pucSndMsg[2]);

        usMsgSize = 3;                                                          /* ������Ϣʵ�ʳ���                         */

        if ( MM_TRUE == Mm_ComMsgSetMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID) )
        {
            Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg,
                RRC_NAS_MSG_PRIORTY_HIGH );                                     /* ������Ϣ                                 */
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgImsiDetachIniSndOfDataReq:WARNING: MSG SET MOBILE ID ERROR!");
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
    }
    return;                                                                     /* ����                                     */
}

/*lint -e438 -e830*/

VOS_UINT16  NAS_MM_GetLocationUpdateRequestMsgIELength( VOS_VOID )
{
    VOS_UINT16                          usMsgLen;

    usMsgLen = 0;

    /* Mobility management protocol discriminator IE����1/2�ֽڣ�Skip Indicator IE����1/2�ֽ� */
    usMsgLen += 1;

    /* Location Updating Request message type IE����1�ֽ� */
    usMsgLen += 1;

    /* Location updating type IE ����1/2�ֽڣ�Ciphering key sequence number IE����1/2�ֽ� */
    usMsgLen += 1;

    /*Location area identification IE����5�ֽ� */
    usMsgLen += 5;

    /* Mobile station classmark IE����1�ֽ� */
    usMsgLen += 1;

    /* Mobile identity IE����2-9�ֽ� */
    usMsgLen += 9;

    /* Mobile station classmark for UMTS IE����5�ֽ� */
    usMsgLen += 5;

    /* Additional update parameters IE����1�ֽ� */
    usMsgLen += 1;

    /* Device properties IE����1�ֽ� */
    usMsgLen += 1;

    /* MS network feature support  IE����1�ֽ� */
    usMsgLen += 1;

    return usMsgLen;
}


VOS_VOID Mm_ComMsgLuReqSndOfEstReq(
                               MM_MSG_LU_REQ_STRU    *pMsg                      /* Ҫ���͵���Ϣ��ָ��                       */
                               )
{
    VOS_UINT16              usMsgSize;                                     /* ��Ϣ����,���ֽ�Ϊ��λ                    */

    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* ������Ϣָ��                             */
    VOS_UINT16              usIdx = 0;
    VOS_UINT8               i;


    usMsgSize = NAS_MM_GetLocationUpdateRequestMsgIELength();

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* ���뷢�͵���Ϣ���õ�����ڴ�ռ�         */
    /*lint -e961*/
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgLuReqSndOfEstReq:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* ����                                     */
        pucSndMsg[usIdx] =  MM_IE_PD_MM_MSG;                                    /* ����PD                                   */
        pucSndMsg[usIdx++] &= 0x0f;                                             /* Skip Indicator                           */
        pucSndMsg[usIdx++] = MM_IE_MSG_TYPE_LU_REQUEST;                         /* ����Message type                         */

        pucSndMsg[usIdx] =
            (VOS_UINT8)(pMsg->MmIeLuType.ucLUT & MM_IE_LU_TYPE_LUT_MASK);       /* ����Location updating type               */
        pucSndMsg[usIdx] = (VOS_UINT8)(pucSndMsg[usIdx] |
                    (pMsg->MmIeLuType.ucFOR & MM_IE_LU_TYPE_FOR_MASK));         /* ����The Follow-On Request                */
        pucSndMsg[usIdx] =
            (VOS_UINT8)(pucSndMsg[usIdx] | (pMsg->MmIeCksn.ucCksn << 4));       /* ����CKSN                                 */
        usIdx++;

        pucSndMsg[usIdx]   |=
            (VOS_UINT8)(0x0000000f & pMsg->MmIeLAI.IeLai.PlmnId.ulMcc);
        pucSndMsg[usIdx++] |=
            (VOS_UINT8)((0x00000f00 & pMsg->MmIeLAI.IeLai.PlmnId.ulMcc) >> 4);
        pucSndMsg[usIdx]   |=
            (VOS_UINT8)((0x000f0000 & pMsg->MmIeLAI.IeLai.PlmnId.ulMcc) >> 16);
        pucSndMsg[usIdx++] |=
            (VOS_UINT8)((0x000f0000 & pMsg->MmIeLAI.IeLai.PlmnId.ulMnc) >> 12);
        pucSndMsg[usIdx]   |=
            (VOS_UINT8)(0x0000000f & pMsg->MmIeLAI.IeLai.PlmnId.ulMnc );
        pucSndMsg[usIdx++] |=
            (VOS_UINT8)((0x00000f00 & pMsg->MmIeLAI.IeLai.PlmnId.ulMnc) >> 4 );
        pucSndMsg[usIdx++] =
            (VOS_UINT8)( (0x0000ff00 & pMsg->MmIeLAI.IeLai.ulLac) >> 8 );
        pucSndMsg[usIdx++] =
            (VOS_UINT8)( 0x000000ff & pMsg->MmIeLAI.IeLai.ulLac );

        /* ����Mobile station classmark1             */
        MM_Fill_IE_ClassMark1(&pucSndMsg[usIdx++]);

        usMsgSize = usIdx;                                                      /* ������Ϣʵ�ʳ���                         */

        if ( MM_TRUE == Mm_ComMsgSetMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID) )
        {
            if ( (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType() )
              && (MM_TRUE == pMsg->ucMsClsMskFrUMTSFlg) )
            {
                usIdx = usMsgSize;
                usMsgSize = usMsgSize + 5;
                pucSndMsg[usIdx++] = 0x33;
                pucSndMsg[usIdx++] = pMsg->MmIeMsClsMskFrUMTS.aucClassmark2[0];
                for( i = 0; i < pMsg->MmIeMsClsMskFrUMTS.aucClassmark2[0]; i++ )
                {
                    pucSndMsg[usIdx++] =
                        pMsg->MmIeMsClsMskFrUMTS.aucClassmark2[i + 1];
                }
            }

#if (FEATURE_ON == FEATURE_LTE)
            if (VOS_TRUE == NAS_MM_IsNeedSetCsmoFlg())
            {
                NAS_MM_SetCsfbAdditionalUpdateParameters(VOS_FALSE,
                                                         VOS_TRUE,
                                                         &usMsgSize, pucSndMsg);
            }
            else if (VOS_TRUE == NAS_MM_IsNeedSetCsmtFlg())
            {
                NAS_MM_SetCsfbAdditionalUpdateParameters(VOS_TRUE,
                                                         VOS_FALSE,
                                                         &usMsgSize, pucSndMsg);
            }
            else
            {
            }
#endif

            if (VOS_TRUE == NAS_MM_IsNeedSetMsNetworkFeatureSupportIELauReq())
            {
                NAS_MM_SetMsNetworkFeatureSupportIE(&usMsgSize, pucSndMsg);
            }


            Mm_SndRrEstReq( RRC_EST_CAUSE_REGISTRATION, MM_FALSE,
                                                usMsgSize, pucSndMsg );
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuReqSndOfEstReq:WARNING: MSG SET MOBILE ID ERROR!");
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* �ͷ�Ϊ������Ϣ������ڴ�ռ�             */
    }

    /*lint +e961*/
    return;                                                                     /* ����                                     */
}

/*lint +e438 +e830*/


MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeMobileId(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize,
    VOS_UINT8           *pucMobileIdFlg,
    VOS_UINT8           *pucEventId)
{
    VOS_UINT16          usIndex;

    usIndex         = *pusIndex;

    /* ��Ϣ�а���IE���ͣ������������͵ĳ��� */
    usIndex++;

    /* �ж���Ϣ���Ƿ���������ֽ���Ϣ */
    if ( usMsgSize < (usIndex + 1) )
    {
        return MM_DECODE_END;
    }
    if (( 0 == pucRcvMsg[usIndex] ) || ( 9 < pucRcvMsg[usIndex] ))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: MOBILE IDENTITY LENGTH Abnormal");
        *pucEventId = MM_EVENT_ID_STATUS_95;
        return MM_DECODE_END;
    }

    /* �ж�IE���Ƿ����mobile identity��������Ϣ */
    if ( usMsgSize < (usIndex + pucRcvMsg[usIndex] + 1 ))
    {
        /* ������������Ϣʱ���ж�IE���Ƿ����mobile identity��type of identity��Ϣ��
           �˴����ж���Ϊ��GCF���� 26.7.3.2���������IMSI��Ϣ����Ҫɾ��ԭ����TMSI */
        if (usMsgSize >= (usIndex + 2))
        {
            if (1 == (pucRcvMsg[usIndex + 1] & MM_IE_MI_ID_TYPE_MASK))
            {
                g_MmMsgLuAccpt.ucMobileIDFlg            = MM_TRUE;
                g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                        = MM_MS_ID_IMSI_PRESENT;
            }
        }
        return MM_DECODE_END;
    }
    if ( MM_FALSE == (*pucMobileIdFlg) )
    {
        *pucMobileIdFlg = MM_TRUE;

        g_MmMsgLuAccpt.ucMobileIDFlg            = MM_TRUE;
        if ( MM_IE_MI_ID_TYPE_IMSI == (pucRcvMsg[usIndex + 1] & 0x07) )
        {
            g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                                   = MM_MS_ID_IMSI_PRESENT;
        }
        else if ( MM_IE_MI_ID_TYPE_TMSI == (pucRcvMsg[usIndex + 1] & 0x07) )
        {
            g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                                       = MM_MS_ID_TMSI_PRESENT;
            PS_MEM_CPY(
                    g_MmMsgLuAccpt.MmIeMobileId.MobileID.aucTmsi,
                    &pucRcvMsg[usIndex + 2],
                    4);
        }
        else
        {
        }
        usIndex = usIndex + pucRcvMsg[usIndex] + 1;
    }
    else
    {
        usIndex = usIndex + pucRcvMsg[usIndex] + 1;
    }

    *pusIndex = usIndex;

    return MM_DECODE_SUCCESS;
}

/*lint -e438 -e830*/

MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeEplmn(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize,
    VOS_UINT8           *pucEventId)
{
    VOS_UINT16          usIndex;
    VOS_UINT16          usEPLmnLen;
    VOS_UINT8           ucPlmnNum;
    VOS_UINT8           i;

    usIndex         = *pusIndex;

    if ( usMsgSize < (usIndex + 2) )
    {
        return MM_DECODE_END;
    }

    if ( pucRcvMsg[usIndex + 1] < 3 )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: RCV MM LU ACCEPT MSG WITH PLMN LIST SIZE ERROR!");
        return MM_DECODE_END;
    }

    if ( usMsgSize < (usIndex + pucRcvMsg[usIndex + 1] + 2) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: RCV MM LU ACCEPT MSG WITH PLMN LIST SIZE ERROR!");
        return MM_DECODE_END;
    }

    *pusIndex = *pusIndex + pucRcvMsg[usIndex + 1] + 2;

    if ( MM_FALSE == g_MmMsgLuAccpt.ucPlmnListFlg )
    {
        g_MmMsgLuAccpt.ucPlmnListFlg = MM_TRUE;
        usIndex++;
        usEPLmnLen = pucRcvMsg[usIndex];

        ucPlmnNum = pucRcvMsg[usIndex] / 3;
        if (ucPlmnNum > NAS_MAX_EQUPLMN_NUM)
        {
            ucPlmnNum = NAS_MAX_EQUPLMN_NUM;
        }

        g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = ucPlmnNum;
        usIndex++;
        for ( i = 0; i < ucPlmnNum; i++ )
        {
            g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMcc
                = pucRcvMsg[usIndex + 1] &
                 MM_IE_LU_ID_MCC_DIGIT_3_MASK;                      /* �洢LAI�е� MCC digit 3                  */
            g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMcc
                = (g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMcc << 8)
                | (pucRcvMsg[usIndex] >> 4);                        /* �洢LAI�е� MCC digit 2                  */
            g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMcc
                = (g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMcc << 8)
                                 | (pucRcvMsg[usIndex] &
                                 MM_IE_LU_ID_MCC_DIGIT_1_MASK);     /* �洢LAI�е� MCC digit 1                  */

            g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMnc
                = pucRcvMsg[usIndex + 1] >> 4;                      /* �洢LAI�е� MNC digit 3                  */
            g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMnc
                = (g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMnc << 8)
                | (pucRcvMsg[usIndex + 2] >> 4);                    /* �洢LAI�е� MNC digit 2                  */
            g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMnc
                = (g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMnc << 8)
                                 | (pucRcvMsg[usIndex + 2] &
                                 MM_IE_LU_ID_MNC_DIGIT_1_MASK);
            usIndex = usIndex + 3;
        }
        if (usEPLmnLen < (NAS_MAX_EQUPLMN_NUM*3))
        {
            usIndex = usIndex + (usEPLmnLen%3);
        }
        else
        {
        }
    }



    return MM_DECODE_SUCCESS;
}
/*lint +e438 +e830*/

MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeOtherOptionalIE(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize,
    VOS_UINT8           *pucEventId)
{
    VOS_UINT16          usIndex;

    usIndex         = *pusIndex;

    if (0x0 == (pucRcvMsg[usIndex] & 0xF0))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: Unexpected IE type.");
        *pucEventId = MM_EVENT_ID_STATUS_96;
        return MM_DECODE_END;
    }

    else if (0x13 == pucRcvMsg[usIndex])
    {/* not code as comprehension required IEI but as LAI IEI in other MM protocal */
        if (usMsgSize < (usIndex + 1))
        {
            return MM_DECODE_END;
        }
        usIndex = usIndex + pucRcvMsg[usIndex+1] + 2;
    }
    else
    {/* not code as comprehension required IEI */
        usIndex = usIndex + 1;
    }

    *pusIndex = usIndex;

    return MM_DECODE_SUCCESS;
}


MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeFollowOn(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize)
{
    VOS_UINT16          usIndex;

    usIndex         = *pusIndex;

    if ( MM_FALSE == g_MmMsgLuAccpt.ucFollowOFlg )
    {
        g_MmMsgLuAccpt.ucFollowOFlg = MM_TRUE;
    }
    usIndex++;

    *pusIndex = usIndex;

    return MM_DECODE_SUCCESS;
}


MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeCTS(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize)
{
    VOS_UINT16          usIndex;

    usIndex         = *pusIndex;

    if ( MM_FALSE == g_MmMsgLuAccpt.ucCtsPermisFlg )
    {
        g_MmMsgLuAccpt.ucCtsPermisFlg = MM_TRUE;
    }
    usIndex++;

    *pusIndex = usIndex;

    return MM_DECODE_SUCCESS;
}


VOS_UINT8 Mm_ComMsgLuAccptRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* ��ǰ�������Ϣ                           */
                            VOS_UINT16      usMsgSize                               /* ��Ϣ����,���ֽ�Ϊ��λ                    */
                            )
{
    VOS_UINT8       ucEventId;                              /* �¼�ID                                   */
    VOS_UINT16      usIndex;
    VOS_UINT8       ucMobileIdFlg;
    VOS_UINT32      ulResult;

    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo = NAS_MM_GetAllocT3212ValueLaiInfo();

    /* ����t3212ʱ������Ϊbroadcast�����lau accept��Я�����µ�t3212ʱ���ٸ���*/
    NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_BROADCAST);

    usIndex         = 2;
    ucEventId       = MM_EVENT_ID_LU_ACCEPT;
    ucMobileIdFlg   = MM_FALSE;

    PS_MEM_SET( &g_MmMsgLuAccpt, 0, sizeof(MM_MSG_LU_ACCPT_STRU));             /* ����                                     */

    if (VOS_NULL_PTR == pucRcvMsg)
    {
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: RCV VOS_NULL_PTR MM LU ACCEPT MSG!");
        return ucEventId;
    }

    if (usMsgSize < 7)
    {
        ucEventId = MM_EVENT_ID_STATUS_96;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: RCV MM LU ACCEPT MSG WITH ERROR SIZE!");
        return ucEventId;
    }


    /* lau�ɹ����CSMT��־ */
    NAS_MM_SetCsfbMtLauFlg(VOS_FALSE);


    /* �յ�Accept��Ϣʱ��Ҫ���ü����� */
    NAS_MM_ResetRejCauseChangedCounter();
    if ( MM_FALSE == MM_IeChkLai( &pucRcvMsg[usIndex] ) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: RCV MM LU ACCEPT MSG WITH LAI ERROR!");
        g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac = MM_INVALID_LAI;                /* plmn�Ƿ�*/
    }
    else
    {
        Mm_ComSaveLai( &pucRcvMsg[usIndex], &g_MmMsgLuAccpt.MmIeLAI.IeLai );
    }

    usIndex = usIndex + 5;

    g_MmMsgLuAccpt.ucFollowOFlg             = MM_FALSE;
    g_MmMsgLuAccpt.ucCtsPermisFlg           = MM_FALSE;
    g_MmMsgLuAccpt.ucMobileIDFlg            = MM_FALSE;
    g_MmMsgLuAccpt.ucPlmnListFlg            = MM_FALSE;
    g_MmMsgLuAccpt.ucEmcFlg                 = MM_FALSE;
    Mm_TimerStop(MM_TIMER_T3218);                                           /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                     /* ɾ��RAND��RES                            */

    while ( usIndex < usMsgSize )
    {
        if ( 0x17 == pucRcvMsg[usIndex] )
        {                                                                   /* ����mobile identity */
            ulResult = NAS_MM_DecodeMobileId(&usIndex, pucRcvMsg, usMsgSize,
                            &ucMobileIdFlg, &ucEventId);
        }
        else if ( 0xa1 == pucRcvMsg[usIndex] )
        {                                                                   /* ����follow on */
            ulResult = NAS_MM_DecodeFollowOn(&usIndex, pucRcvMsg, usMsgSize);
        }
        else if ( 0xa2 == pucRcvMsg[usIndex] )
        {                                                                   /* ����CTS */
            ulResult = NAS_MM_DecodeCTS(&usIndex, pucRcvMsg, usMsgSize);
        }
        else if ( 0x4a == pucRcvMsg[usIndex] )
        {                                                                   /* ����EPLMN */
            ulResult = NAS_MM_DecodeEplmn(&usIndex, pucRcvMsg,
                            usMsgSize, &ucEventId);
        }
        else if (0x34 == pucRcvMsg[usIndex])
        {                                                                   /* Emergency Number List                    */

            (VOS_VOID)NAS_MML_DecodeEmergencyNumList(&usIndex, pucRcvMsg, usMsgSize);

            g_MmMsgLuAccpt.ucEmcFlg = MM_TRUE;

            ulResult = MM_DECODE_SUCCESS;
        }
        else if (0x35 == pucRcvMsg[usIndex])
        {
            if (PS_PTL_VER_R11 <= NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS))
            {
                NAS_MM_UpdateT3212Value_RcvLauAccept(pucRcvMsg[usIndex + 2]);

                pstAllocT3212ValueLaiInfo->stPlmnId.ulMcc   = g_MmMsgLuAccpt.MmIeLAI.IeLai.PlmnId.ulMcc;
                pstAllocT3212ValueLaiInfo->stPlmnId.ulMnc   = g_MmMsgLuAccpt.MmIeLAI.IeLai.PlmnId.ulMnc;
                pstAllocT3212ValueLaiInfo->aucLac[0]        = (g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac >> NAS_MML_OCTET_MOVE_EIGHT_BITS) & (NAS_MML_BYTE_MASK);
                pstAllocT3212ValueLaiInfo->aucLac[1]        = (g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac) & (NAS_MML_BYTE_MASK);
                pstAllocT3212ValueLaiInfo->enCampPlmnNetRat = NAS_MML_GetCurrNetRatType();

                NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_NONE_BROADCAST);
            }

            usIndex = usIndex + 3;

            ulResult = MM_DECODE_SUCCESS;
        }
        else
        {                                                                   /* ����������ѡ��IE */
            ulResult = NAS_MM_DecodeOtherOptionalIE(&usIndex, pucRcvMsg,
                            usMsgSize, &ucEventId);
        }

        if (MM_DECODE_END == ulResult)
        {
            break;
        }
    }
    return ucEventId;                                                           /* �����¼�ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgLuRejctRcv
  Function: �洢��ϢLU ACCEPT
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
            VOS_UINT16    usMsgSize, ��Ϣ����,���ֽ�Ϊ��λ
  Output:
  NOTE:
  Return:   VOS_UINT8,�¼�ID,���MM_Def.h�й����¼��ĺ궨��
  History:
      1.  ��־��    2004.03.25   �°�����
      2. ��    ��   : 2007��05��11��
         ��    ��   : luojian id:60022475
         �޸�����   : ���ⵥ��:A32D10713
*******************************************************************************/
VOS_UINT8 Mm_ComMsgLuRejctRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* ��ǰ�������Ϣ                           */
                            VOS_UINT16      usMsgSize                               /* ��Ϣ����,���ֽ�Ϊ��λ                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_LU_REJECT;                              /* �¼�ID                                   */

    PS_MEM_SET( &g_MmMsgLuRjct, 0, sizeof(MM_MSG_LU_RJCT_STRU));               /* ����                                     */

    if (VOS_NULL_PTR == pucRcvMsg)
    {
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuRejctRcv:WARNING: RCV VOS_NULL_PTR MM LU REJECT MSG!");
    }
    else if (usMsgSize < 3)
    {
        ucEventId = MM_EVENT_ID_STATUS_96;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuRejctRcv:WARNING: RCV MM LU REJECT MSG WITH ERROR SIZE!");
    }
    else
    {
        g_MmMsgLuRjct.MmIeRejCause.ucRejCause = pucRcvMsg[2];
    }

    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;

    return ucEventId;                                                           /* �����¼�ID                               */
}


/*******************************************************************************
  Module:   Mm_ComMsgSvcPromptRcv
  Function: �洢��ϢLU ACCEPT
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_UINT8,�¼�ID,���MM_Def.h�й����¼��ĺ궨��
  History:
      1.  ��־��      2004.04.14   �°�����
*******************************************************************************/
VOS_UINT8 Mm_ComMsgSvcPromptRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* ��ǰ�������Ϣ                           */
                            VOS_UINT16      usMsgSize                               /* ��Ϣ����,���ֽ�Ϊ��λ                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_CM_SVC_PROMPT;                          /* �¼�ID                                   */

    if (VOS_NULL_PTR == pucRcvMsg)
    {
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgSvcPromptRcv:WARNING: RCV VOS_NULL_PTR MM CM SVC PROMPT MSG!");
        return ucEventId;
    }
    else if (usMsgSize < 3)
    {
        ucEventId = MM_EVENT_ID_STATUS_96;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgSvcPromptRcv:WARNING: RCV MM CM SVC PROMPT MSG WITH ERROR SIZE!");
        return ucEventId;
    }
    else
    {

    }

    if ( MM_FALSE == MM_IeChkPdAndSapi( &pucRcvMsg[2] ) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgSvcPromptRcv:WARNING: RCV MM CM SVC PROMPT MSG WITH PD AND SAPI ERROR!");
        return MM_EVENT_ID_STATUS_95;
    }

    if ( MM_IE_PD_CALL_CONTROL != ( pucRcvMsg[2] & 0x0f ) )
    {                                                                           /* PD���Ϸ�                                 */
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgSvcPromptRcv:WARNING: RCV MM CM SVC PROMPT MSG WITH PD ERROR!");
    }

    return ucEventId;                                                           /* �����¼�ID                               */
}
/*******************************************************************************
  Module:   MM_IeChkLai
  Function: ���IE LAI����ȷ��
  Input:    VOS_UINT8      *pucRcvIe  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  ��־��    2005.01.12   �°�����
*******************************************************************************/
VOS_UINT8 MM_IeChkLai (
                   VOS_UINT8      *pucRcvIe                                         /* ��ǰ�������Ϣ                           */
                   )
{
    VOS_UINT8   ucIndex = 0;

    if( ( pucRcvIe[ucIndex] & 0x0F ) > 9 )
    {
        return MM_FALSE;
    }
    if( ( ( pucRcvIe[ucIndex] >> 4 ) & 0x0F ) > 9 )
    {
        return MM_FALSE;
    }
    if( ( pucRcvIe[ucIndex + 1] & 0x0F ) > 9 )
    {
        return MM_FALSE;
    }
    if( ( ( ( pucRcvIe[ucIndex + 1] >> 4 ) & 0x0F ) > 9 ) &&
        ( ( ( pucRcvIe[ucIndex + 1] >> 4 ) & 0x0F ) != 0x0F ) )
    {
        return MM_FALSE;
    }
    if( ( pucRcvIe[ucIndex + 2] & 0x0F ) > 9 )
    {
        return MM_FALSE;
    }
    if( ( ( pucRcvIe[ucIndex + 2] >> 4 ) & 0x0F ) > 9 )
    {
        return MM_FALSE;
    }
    return MM_TRUE;
}
VOS_UINT8 MM_IeChkMblId (
                   VOS_UINT8      *pucRcvIe                                         /* ��ǰ�������Ϣ                           */
                   )
{
    VOS_UINT8   ucIndex = 0;
    VOS_UINT8   ucLength = 0;

    if( ( pucRcvIe[ucIndex + 1] & MM_IE_MI_ID_TYPE_MASK ) > 4 )
    {
        return MM_FALSE;
    }
    if ( ( MM_IE_MI_ID_TYPE_IMSI == ( pucRcvIe[ucIndex + 1] & \
     MM_IE_MI_ID_TYPE_MASK ) ) ||
       ( MM_IE_MI_ID_TYPE_IMEI == ( pucRcvIe[ucIndex + 1] &\
        MM_IE_MI_ID_TYPE_MASK ) ) ||
       ( MM_IE_MI_ID_TYPE_IMEISV == ( pucRcvIe[ucIndex + 1] & \
        MM_IE_MI_ID_TYPE_MASK ) ) )
    {
        if ( 0 == (pucRcvIe[ucIndex + 1] & 0x08) )
        {
            ucLength = pucRcvIe[ucIndex];
            if ((pucRcvIe[ucLength] & MM_IE_MI_ID_DIGIT_1_MASK ) != 0xF0)
            {
                return MM_FALSE;
            }
        }
    }
    else
    {
        if( ( pucRcvIe[ucIndex + 1] & MM_IE_MI_ID_DIGIT_1_MASK ) != 0xF0 )
        {
            return MM_FALSE;
        }
    }

    return MM_TRUE;
}
/*******************************************************************************
  Module:   MM_IeChkPlmnLst
  Function: ���IE PLMN LIST����ȷ��
  Input:    VOS_UINT8      *pucRcvIe  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  ��־��    2005.01.13   �°�����
*******************************************************************************/
VOS_UINT8 MM_IeChkPlmnLst (
                   VOS_UINT8      *pucRcvIe                                         /* ��ǰ�������Ϣ                           */
                   )
{
    VOS_UINT8   ucIndex = 0;
    VOS_UINT8   ucPlmnNum;

    if ( 0 != ( pucRcvIe[ucIndex] % 3 ) )
    {
        return MM_FALSE;
    }
    else
    {
        ucPlmnNum = pucRcvIe[ucIndex] / 3;
        if (ucPlmnNum > 15)
        {
            return MM_FALSE;
        }
    }

    return MM_TRUE;
}

/*******************************************************************************
  Module:   MM_IeChkCksn
  Function: ���IE CKSN����ȷ��
  Input:    VOS_UINT8      *pucRcvIe  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  ��־��    2005.01.13   �°�����
*******************************************************************************/
VOS_UINT8 MM_IeChkCksn (
                   VOS_UINT8      *pucRcvIe                                         /* ��ǰ�������Ϣ                           */
                   )
{
    return MM_TRUE;
}


/*******************************************************************************
  Module:   MM_IeChkSprHalfOctet
  Function: ���IE Spare Half Octet����ȷ��
  Input:    VOS_UINT8      *pucRcvIe  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  ��־��    2005.01.13   �°�����
*******************************************************************************/
VOS_UINT8 MM_IeChkSprHalfOctet (
                   VOS_UINT8      *pucRcvIe                                         /* ��ǰ�������Ϣ                           */
                   )
{
    if ( 0 != ( pucRcvIe[0] & 0xF0 ) )
    {
        return MM_FALSE;
    }

    return MM_TRUE;
}

/*******************************************************************************
  Module:   MM_IeChkRand
  Function: ���IE RAND����ȷ��
  Input:    VOS_UINT8      *pucRcvIe  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  ��־��    2005.01.13   �°�����
*******************************************************************************/
VOS_UINT8 MM_IeChkRand (
                   VOS_UINT8      *pucRcvIe                                         /* ��ǰ�������Ϣ                           */
                   )
{
    return MM_TRUE;
}

/*******************************************************************************
  Module:   MM_IeChkAutn
  Function: ���IE AUTN����ȷ��
  Input:    VOS_UINT8      *pucRcvIe  ��ǰ�������Ϣ
            VOS_UINT8      ucflg       �Ƿ�Ϊ��ѡ��
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  ��־��    2005.01.13   �°�����
*******************************************************************************/
VOS_UINT8 MM_IeChkAutn (
                   VOS_UINT8      *pucRcvIe                                         /* ��ǰ�������Ϣ                           */
                   )
{
    VOS_UINT8       ucIndex = 0;

    if ( 16 != pucRcvIe[ucIndex] )
    {
        return MM_FALSE;
    }
    return MM_TRUE;
}

/*******************************************************************************
  Module:   MM_IeChkIdType
  Function: ���IE ID TYPE����ȷ��
  Input:    VOS_UINT8      *pucRcvIe  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  ��־��    2005.01.13   �°�����
*******************************************************************************/
VOS_UINT8 MM_IeChkIdType (
                   VOS_UINT8      *pucRcvIe                                         /* ��ǰ�������Ϣ                           */
                   )
{
    if( ( 1 != ( pucRcvIe[0] & MM_IE_ID_TYPE_IDTYPE_MASK) )&&
        ( 2 != ( pucRcvIe[0] & MM_IE_ID_TYPE_IDTYPE_MASK) )&&
        ( 3 != ( pucRcvIe[0] & MM_IE_ID_TYPE_IDTYPE_MASK) )&&
        ( 4 != ( pucRcvIe[0] & MM_IE_ID_TYPE_IDTYPE_MASK ) ) )
    {
        return MM_FALSE;
    }
    return MM_TRUE;
}

/*******************************************************************************
  Module:   MM_IeChkPdAndSapi
  Function: ��IE"PD and SAPI"���
  Input:    VOS_UINT8 *pIePdAndSapi,  �����IE�׵�ַ
  Output:
  NOTE:
  Return:   VOS_UINT8,�����,MM_TRUE/MM_FALSE,�ɹ�/ʧ��
  History:
      1.  ��־��    2005.01.13   �°�����
*******************************************************************************/
VOS_UINT8 MM_IeChkPdAndSapi( VOS_UINT8 *pIePdAndSapi )
{
    VOS_UINT8 ucRet = MM_TRUE;
    VOS_UINT8 ucIndex = 0;
    VOS_UINT8 ucPd,ucSapi;

    ucSapi = ( pIePdAndSapi[ucIndex] & 0x30 ) >> 4;
    ucPd   = ( pIePdAndSapi[ucIndex] & 0x0f );
    if ( (0x00 != ucSapi) && (0x03 != ucSapi) )
    {
        ucRet = MM_FALSE;
    }
    else
    {
        ;
    }
    if ( MM_TRUE == ucRet )
    {
        if (  (0x07 == ucPd)
           || (0x0d == ucPd)
           || (0x0e == ucPd)
           || (0x0f == ucPd)
           )
        {
            ucRet = MM_FALSE;
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
    return ucRet;
}


VOS_UINT8 MM_IeChkDayLightSavTim( VOS_UINT8* pIeDayLightSvTim )
{
    VOS_UINT8 ucRet = MM_TRUE;
    VOS_UINT8 ucIndex = 0;

    if ( 1 == pIeDayLightSvTim[ucIndex] )
    {
        ucIndex ++;
        if( (0x00 != pIeDayLightSvTim[ucIndex])
            && (0x01 != pIeDayLightSvTim[ucIndex])
            && (0x02 != pIeDayLightSvTim[ucIndex])
            )
        {
            ucRet = MM_FALSE;
        }
        else
        {
            g_MmMsgMmInfo.ucNWDyLitSavTmFlg = VOS_TRUE;
            g_MmMsgMmInfo.MmIeNWDyLitSavTm.ucValue = pIeDayLightSvTim[ucIndex];
        }
    }
    else
    {
        ucRet = MM_FALSE;
    }

    return ucRet;
}

/*******************************************************************************
  Module:   MM_IeChkLsaIdtfr
  Function: ��IE"LSA Identifier"���
  Input:    VOS_UINT8 *pIeLsaIdTfr,  �����IE�׵�ַ
  Output:
  NOTE:
  Return:   VOS_UINT8,�����,VOS_TRUE/VOS_FALSE,�ɹ�/ʧ��
  History:
      1.  ��־��    2005.01.13   �°�����
*******************************************************************************/
VOS_UINT8 MM_IeChkLsaIdtfr( VOS_UINT8* pIeLsaIdTfr )
{
    VOS_UINT8 ucRet = VOS_TRUE;
    VOS_UINT8 ucIndex = 0;

    if ( pIeLsaIdTfr[ucIndex] <= 3 )
    {
        ;
    }
    else
    {
        ucRet = VOS_FALSE;
    }
    return ucRet;
}


VOS_UINT8 MM_IeChkTimAndTimZone( VOS_UINT8 * pIeTimAndTimZone )
{
    VOS_INT8    cTimeZone;
    VOS_UINT8   ucDigit;

    /*��ʽת��: �����·��ĸ�ʽΪBCD�룬���ֽ�Ϊ��λ�������ֽ�Ϊʮλ��, ��: 0x51 => 15 */
    /* ��һ���ֽ�Ϊ Year */
    g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucYear = ((pIeTimAndTimZone[0] & 0x0f) * 10)
                                                     +((pIeTimAndTimZone[0] & 0xf0) >> 4);
    if ( g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucYear > 99)
    {
        return VOS_FALSE;
    }

    /* �ڶ����ֽ�Ϊ Month */
    g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucMonth = ((pIeTimAndTimZone[1] & 0x0f) * 10)
                                                     +((pIeTimAndTimZone[1] & 0xf0) >> 4);
    if (  ( g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucMonth > 12 )
        ||( 0 == g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucMonth ) )
    {
        return VOS_FALSE;
    }

    /* �������ֽ�Ϊ Day */
    g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucDay = ((pIeTimAndTimZone[2] & 0x0f) * 10)
                                                     +((pIeTimAndTimZone[2] & 0xf0) >> 4);
    if ( ( g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucDay > 31)
      || ( 0 == g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucDay ) )
    {
        return VOS_FALSE;
    }

    /* ���ĸ��ֽ�Ϊ Hour */
    g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucHour = ((pIeTimAndTimZone[3] & 0x0f) * 10)
                                                     +((pIeTimAndTimZone[3] & 0xf0) >> 4);
    if ( g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucHour >= 24)
    {
        return VOS_FALSE;
    }

    /* ������ֽ�Ϊ Minute */
    g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucMinute = ((pIeTimAndTimZone[4] & 0x0f) * 10)
                                                     +((pIeTimAndTimZone[4] & 0xf0) >> 4);
    if ( g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucMinute >= 60)
    {
        return VOS_FALSE;
    }

    /* �������ֽ�Ϊ Second */
    g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucSecond = ((pIeTimAndTimZone[5] & 0x0f) * 10)
                                                     +((pIeTimAndTimZone[5] & 0xf0) >> 4);
    if ( g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucSecond >= 60)
    {
        return VOS_FALSE;
    }

    /* ���߸��ֽ�Ϊ TimeZone */
    ucDigit = (pIeTimAndTimZone[6] & 0xF0) >> 4;
    if ( ucDigit > 9 )
    {
        return VOS_FALSE;
    }
    cTimeZone = (VOS_INT8)(((pIeTimAndTimZone[6] & 0x07) * 10) + ucDigit);

    /* �ж�ʱ��������ֵ */
    if (pIeTimAndTimZone[6] & 0x08)
    {
        g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.cTimeZone = - cTimeZone;
    }
    else
    {
        g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.cTimeZone = cTimeZone;
    }

    g_MmMsgMmInfo.ucUnvrslTmAndLocalTmZoneFlg = VOS_TRUE;

    return VOS_TRUE;
}
VOS_UINT8 MM_IeChkTimZone( VOS_UINT8* pIeTimZone )
{
    VOS_INT8    cTimeZone;
    VOS_UINT8   ucDigit;

    ucDigit = ((*pIeTimZone) & 0xF0) >> 4;
    if ( ucDigit > 9 )
    {
        /* TimeZone ֵ�Ƿ� */
        return VOS_FALSE;
    }

    cTimeZone = (VOS_INT8)((((*pIeTimZone) & 0x07) * 10) + ucDigit);

    /* ����Time Zone */
    g_MmMsgMmInfo.ucLocalTmZoneFlg = VOS_TRUE;

    /* �ж�ʱ��������ֵ */
    if ((*pIeTimZone) & 0x08)
    {
        g_MmMsgMmInfo.MmIeLocalTmZone.cTimeZone = - cTimeZone;
    }
    else
    {
        g_MmMsgMmInfo.MmIeLocalTmZone.cTimeZone = cTimeZone;
    }

    return VOS_TRUE;
}


VOS_UINT8 MM_IeChkNtwkNam( VOS_UINT8* pIeNtWkNam )
{
    VOS_UINT8 ucRet = VOS_TRUE;
    VOS_UINT8 ucIndex = 0;
    VOS_UINT8 ucIeLen,ucOctetN,ucCodScheme;

    /*lint -e961*/
    ucIeLen     = pIeNtWkNam[ucIndex++];
    /*lint +e961*/
    ucOctetN    = pIeNtWkNam[ucIeLen];
    ucCodScheme = ( 0x70 & pIeNtWkNam[ucIndex] ) >> 4;

    if ( ( (0 == ucCodScheme) || (1 == ucCodScheme) )
        && (0 != (0x80 & pIeNtWkNam[ucIndex])) )
    {
        switch( ( 0x07 & pIeNtWkNam[ucIndex] ) )
        {
        case 0:
            break;
        case 1:
            if ( 0 != ( 0x80 & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        case 2:
            if ( 0 != ( 0xc0 & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        case 3:
            if ( 0 != ( 0xe0 & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        case 4:
            if ( 0 != ( 0xf0 & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        case 5:
            if ( 0 != ( 0xf8 & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        case 6:
            if ( 0 != ( 0xfc & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        case 7:
            if ( 0 != ( 0xfe & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        default:
            break;
        }
    }
    else
    {
        ucRet = VOS_FALSE;
    }

    return ucRet;
}

VOS_UINT32 NAS_MM_CheckSigConnStatusAffectAttach(
    MMCMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    if(((MM_COM_SRVST_NORMAL_SERVICE == Gmm_ComServiceSts())
      && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState ))
    && (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType)
    && ((GMM_SPECIFIC_ON == g_MmSubLyrShare.GmmShare.ucPsSpecificFlg)
     || (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg)))
    {
        return VOS_TRUE;
    }


    if (( MMC_MM_ATTACH_TYPE_IMSI == pstAttachReq->enAttachType )
     && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState)
     && (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg))
    {
        return VOS_TRUE;
    }

    /* CS��ǰ��ר�й�����,ֱ�ӷ���ע���� */
    if ((( MMC_MM_ATTACH_TYPE_IMSI == pstAttachReq->enAttachType )
     || (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType))
     && (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg))
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MM_CheckSimStatusBeforeAttachAction(
    MMCMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    NAS_MML_SIM_STATUS_STRU            *pstUsimStatus = VOS_NULL_PTR;

    pstUsimStatus = NAS_MML_GetSimStatus();

    /* USIM CS����Ч��ֱ�ӻظ�ATTACH CNF */
    if ( ( MMC_MM_ATTACH_TYPE_GPRS  != pstAttachReq->enAttachType )
      && ( VOS_TRUE            != pstUsimStatus->ucSimCsRegStatus ) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_CheckSimStatusAffectAttach:WARNING: CS USIM is invalid.");
        NAS_MM_SndMmcAttachCnf();
        return VOS_TRUE;
    }

    /* USIM PS����Ч��MMC_GMM_ATTACH_TYPE_GPRS_IMSI����ת��ΪMMC_MM_ATTACH_TYPE_IMSI */
    if ( ( MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
      && ( VOS_TRUE                != pstUsimStatus->ucSimPsRegStatus ) )
    {
        pstAttachReq->enAttachType = MMC_MM_ATTACH_TYPE_IMSI;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MM_ConflictWithDetach(VOS_UINT32 ulAttachType)
{
    /* ��ǰMM��detach��־λΪVOS_TRUE��ATTACH������MMC_MM_ATTACH_TYPE_IMSI
       ����MMC_MM_ATTACH_TYPE_GPRSIMSI ,����VOS_TRUE */
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo = VOS_NULL_PTR;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* ֮ǰ������DETACH���� */
    if ( MM_WAIT_NULL_DETACH == g_MmGlobalInfo.stDetachInfo.enDetachType)
    {
        return VOS_FALSE;
    }

    /* A+Iģʽ */
    if ( ( NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode() )
      && ( NAS_MML_NET_MODE_I    == pstCampInfo->enNetworkMode ) )
    {
        /* ����ģʽI��,��DETACH����,ֱ�ӻظ�CNF */
        if ( MMC_MM_ATTACH_TYPE_IMSI == (ulAttachType
                                        & MMC_MM_ATTACH_TYPE_IMSI))
        {
            NAS_MM_SndMmcAttachCnf();
        }
        return VOS_TRUE;
    }
    else
    {
        if ( ( (MMC_MM_ATTACH_TYPE_IMSI == ulAttachType )
             && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType
                                     & GMM_WAIT_CS_DETACH ) ) )
          || ( MMC_MM_ATTACH_TYPE_GPRS_IMSI == ulAttachType ) )
        {
            /* CS ATTACH ��DETACH��ͻ,ֱ�ӻظ�CNF */
            NAS_MM_SndMmcAttachCnf();
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

VOS_UINT32 NAS_MM_IsAttachRepeated(
    VOS_UINT32                          ulAttachType,
    VOS_UINT32                          ulOpID)
{
    /* ֮ǰ����CS ATTACH �յ�CS ATTACH������OPID��ֱ�ӷ��� */
    if (  MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                              & MM_WAIT_CS_ATTACH))
    {
        g_MmGlobalInfo.stAttachInfo.ulOpid = ulOpID;
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT8 NAS_MM_RcvMmcAttachReq_PreProc(
    VOS_VOID                           *pstRcvMsg
)
{
    MMCMM_ATTACH_REQ_STRU              *pstAttachReq;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstAttachReq    = (MMCMM_ATTACH_REQ_STRU*)pstRcvMsg;
    pstCampInfo     = NAS_MML_GetCurrCampPlmnInfo();

    /* �ж��Ƿ���Ҫ�������Ϣ����Ч��Ϣ����������MM_EVENT_ID_INVALID */
    if ((MMC_MM_ATTACH_TYPE_IMSI     != pstAttachReq->enAttachType)
     && (MMC_MM_ATTACH_TYPE_GPRS_IMSI!= pstAttachReq->enAttachType))
    {

        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_MM_RcvMmcAttachReq_PreProc:ATTACH TYPE INVALID");
        return MM_EVENT_ID_INVALID;
    }

    /* PS�ǽ����ֹ�����,��Ҫ���LIKEB��ǣ������ظ�����LAU */
    if (MM_TRUE == g_MmGlobalInfo.ucSysInfoFlg)
    {
        if ( ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
            || (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType) )
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod) )
        {
            /* FobidnFlag ��MMC �Ѿ������жϣ����ﲻ��Ҫ���ж� */
            if ( (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
              && (MM_UNSUPPORT_GPRS != g_MmGlobalInfo.usRac) )
            {
                if((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
                || (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType))
                {
                    g_MmGlobalInfo.ucLikeB = MM_FALSE;
                }
            }
        }
    }


    g_MmGlobalInfo.stAttachInfo.ulOpid = pstAttachReq->ulOpid;

    if (VOS_TRUE == NAS_MM_CheckSigConnStatusAffectAttach(pstAttachReq))
    {
        NAS_MM_SndMmcAttachCnf();
        return MM_EVENT_ID_INVALID;
    }

    /* CS����Ч���ظ�ATTACH_CNF������MM_EVENT_ID_INVALID */
    if (VOS_TRUE == NAS_MM_CheckSimStatusBeforeAttachAction(pstAttachReq))
    {
        return MM_EVENT_ID_INVALID;
    }

    /* ����Ƿ��֮ǰ��DETACH�г�ͻ */
    if (VOS_TRUE == NAS_MM_ConflictWithDetach(pstAttachReq->enAttachType))
    {
        return MM_EVENT_ID_INVALID;
    }

    /* ����Ƿ��֮ǰ��ATTACH�г�ͻ */
    if (VOS_TRUE == NAS_MM_IsAttachRepeated(pstAttachReq->enAttachType, pstAttachReq->ulOpid))
    {
        return MM_EVENT_ID_INVALID;
    }

    /* ����ģʽII�¸���ATTACH���� */
    if ((NAS_MML_NET_MODE_II            == pstCampInfo->enNetworkMode)
     && (MMC_MM_ATTACH_TYPE_GPRS_IMSI   == pstAttachReq->enAttachType))
    {
        pstAttachReq->enAttachType = MMC_MM_ATTACH_TYPE_IMSI;
    }

    /* �����ǰucCsAttachState��״̬�Ѿ����ţ���ظ�ATTACH_CNF��
       ����MM_EVENT_ID_INVALID */
    if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
    {
        NAS_MM_SndMmcAttachCnf();
        return MM_EVENT_ID_INVALID;
    }

    /* ���õȴ�ATTACH�����־λ������MM_EVENT_ID_ATTACH_REQ */
    g_MmGlobalInfo.stAttachInfo.enAttachType    = pstAttachReq->enAttachType;

    /* ��ΪCsAttachAllowFlg ΪVOS_TRUE */
    NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);

    return MM_EVENT_ID_ATTACH_REQ;
}


VOS_VOID NAS_MM_RcvAttachReq_InterRatChange(
    VOS_VOID                          *pMsg
)
{
    /* ֱ�ӻظ�MMCMM_ATTACH_CNF */
    NAS_MM_SndMmcAttachCnf();

    /* ����ȴ�ATTACH�����־λ */
    g_MmGlobalInfo.stAttachInfo.enAttachType    = MM_WAIT_NULL_ATTACH;

    /* ��ΪCsAttachAllowFlg ΪVOS_TRUE */
    NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
}

VOS_UINT32 NAS_MM_ProcCsDetach(
    MMCMM_DETACH_REQ_STRU              *pstDetachReq
)
{
    VOS_UINT32                          ulState;

    /* ��ȡMM��״̬ */
    ulState = Mm_GetState();



    g_MmGlobalInfo.stDetachInfo.ulOpid = pstDetachReq->ulOpid;


    NAS_MM_InitLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo());

    /* CS���е�ǰҵ�����,syscfg���������detach�����������棬ֱ�ӻظ�detach cnf����ǰ����״̬ */
    if ( VOS_TRUE == NAS_MML_GetCsServiceExistFlg() )
    {
        if ((MMC_MM_DETACH_REASON_RAT_OR_BAND_DETACH == pstDetachReq->enDetachReason)
         || (MMC_MM_DETACH_REASON_SRV_DOMAIN_DETACH  == pstDetachReq->enDetachReason))
        {
            NAS_MM_SndMmcDetachCnf(g_MmGlobalInfo.ucMmServiceState);
            return VOS_TRUE;
        }
    }

    if ( MM_WAIT_CS_ATTACH  == (g_MmGlobalInfo.stAttachInfo.enAttachType & MM_WAIT_CS_ATTACH) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcCsDetach:NORMAL: CS ATTACH is Running.");
        NAS_MM_SndMmcAttachCnf();

        g_MmGlobalInfo.stAttachInfo.enAttachType &= ~MM_WAIT_CS_ATTACH;
    }

#if (FEATURE_ON == FEATURE_ECALL)
    /* ecall onlyģʽ��CS�Ѿ�attach�ϵ�����²��������CS��detach,��Ϊ��Ҫ���лغ� */
    if ((NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
     && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState))
    {
        NAS_MM_SndMmcDetachCnf(g_MmGlobalInfo.ucMmServiceState);

        return VOS_TRUE;
    }
#endif

    /* ������ģʽI��,����ע�����LAU�����У�����CS���detach;
       ����ģʽI��,  ����ע���������ע������л���LAU�����У�����CS���detach  */
    if ( (MM_STATUS_ATTACHED                       == g_MmSubLyrShare.MmShare.ucCsAttachState)
      || (LOCATION_UPDATING_PENDING                == ulState)
      || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == ulState)
      || (LOCATION_UPDATING_INITIATED              == ulState))
    {
        g_MmGlobalInfo.stDetachInfo.enDetachType |= MM_WAIT_CS_DETACH;
    }
    else
    {
        g_MmGlobalInfo.stDetachInfo.enDetachType |= MM_WAIT_CS_DETACH;

        NAS_MM_LocalDetach();


        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MM_ProcCsPsDetach(
    MMCMM_DETACH_REQ_STRU              *pstDetachReq
)
{
    VOS_UINT32                          ulState;

    /* ��ȡMM��״̬ */
    ulState = Mm_GetState();


    g_MmGlobalInfo.stDetachInfo.ulOpid = pstDetachReq->ulOpid;


    NAS_MM_InitLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo());


    /* ��ǰ����CS��ATTACH��־������ֱ�ӻظ�ATTACH CNF��� */
    if ( MM_WAIT_CS_ATTACH  == (g_MmGlobalInfo.stAttachInfo.enAttachType & MM_WAIT_CS_ATTACH) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcCsPsDetach:NORMAL: CS ATTACH is Running.");

        NAS_MM_SndMmcAttachCnf();

        g_MmGlobalInfo.stAttachInfo.enAttachType &= ~MM_WAIT_CS_ATTACH;
    }

    /* ���ATTACH�ȴ���־ */
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    /* CS����ATTACHED״̬������־λ,����������ע�������, ����ֱ�ӻظ�DETACH CNF*/
    if ( (MM_STATUS_ATTACHED                       == g_MmSubLyrShare.MmShare.ucCsAttachState)
      || (LOCATION_UPDATING_PENDING                == ulState)
      || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == ulState)
      || (LOCATION_UPDATING_INITIATED              == ulState))
    {
        g_MmGlobalInfo.stDetachInfo.enDetachType    = MM_WAIT_CS_PS_DETACH;

        return VOS_FALSE;
    }
    else
    {
        g_MmGlobalInfo.stDetachInfo.enDetachType |= MM_WAIT_CS_PS_DETACH;

        NAS_MM_LocalDetach();
        return VOS_TRUE;
    }
}



VOS_UINT8  NAS_MM_RcvMmcDetachReq_PreProc(
    VOS_VOID                           *pstRcvMsg
)
{
    MMCMM_DETACH_REQ_STRU              *pstDetachReq;

    pstDetachReq = (MMCMM_DETACH_REQ_STRU*)pstRcvMsg;

    switch (pstDetachReq->enDetachType)
    {
        case MMC_MM_PS_DETACH:
            return MM_EVENT_ID_INVALID;
        case MMC_MM_CS_DETACH:
            if (VOS_TRUE == NAS_MM_ProcCsDetach(pstDetachReq))
            {
                return MM_EVENT_ID_INVALID;
            }
            break;
        case MMC_MM_PS_CS_DETACH:
            if (VOS_TRUE == NAS_MM_ProcCsPsDetach(pstDetachReq))
            {
                return MM_EVENT_ID_INVALID;
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, LOG_LEVEL_WARNING,"DETACH TYPE INVALID");
            return MM_EVENT_ID_INVALID;
    }

    /* ����CS�򱣻���ʱ��  */
    NAS_MM_StartDetachProtectingTimer(pstDetachReq);

    return MM_EVENT_ID_DETACH_REQ;
}





VOS_VOID NAS_MM_RcvMmcLauReq(
    VOS_VOID                           *pstRcvMsg
)
{
    MMCMM_LAU_REQ_STRU                 *pstLauReq       = VOS_NULL_PTR;
    VOS_UINT8                           ucPsRestrictionFlg;

    pstLauReq               = (MMCMM_LAU_REQ_STRU*)pstRcvMsg;
    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    /* NMO1��,MM����Ҫ����ע�� */
    if ((VOS_TRUE       == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I  == g_MmGlobalInfo.ucNewNtMod)
     && (MM_FALSE       == g_MmGlobalInfo.ucLikeB)
     && (VOS_FALSE      == ucPsRestrictionFlg))
    {
        return;
    }

    /* ����Ƿ��ڵ�ǰ�����ϱ���#17(MMC���ж�),��ʧ�ܴﵽ������ */
    if ( g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4 )
    {
        return;
    }

    if ( (MM_IDLE_ATTEMPTING_TO_UPDATE == Mm_GetState())
      && (MMC_MM_LAU_REQ_REASON_SOR == pstLauReq->enLauReqReason) )
    {
        /* ֱ�ӽ���lau */
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
        Mm_ComLuOnly();
    }

    return;
}



VOS_UINT8 NAS_MM_RcvMmcRatChangeInd(
    VOS_VOID                           *pstRcvMsg
)
{
    MMCMM_RAT_CHANGE_IND_STRU          *pstRatChangeInd = VOS_NULL_PTR;

    pstRatChangeInd = (MMCMM_RAT_CHANGE_IND_STRU *)pstRcvMsg;

    /*ˢ��Ŀ��RAT*/
    g_MmGlobalInfo.stSuspendShare.enDestSuspendRat = pstRatChangeInd->enNetRatType;

    return MM_EVENT_ID_INVALID;

}


/* Added by n00355355 for �����ؽ�, 2015-9-17, end */
/*****************************************************************************
 �� �� ��  : NAS_MM_RcvRrMmGetTransactionReq
 ��������  : �յ������ѯ��ǰҵ��״̬��־�ĺ�������
 �������  : ulEventType:��Ϣ����
              pstMsg:RRMM_TRANSACTION_INFO_ENQ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ������ɣ�����Ҫ��״̬�����д���
              VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��9��17��
    ��    ��   : n00355355
    �޸�����   : �½�
*****************************************************************************/
VOS_VOID NAS_MM_RcvRrMmGetTransactionReq(
    RRMM_TRANSACTION_INFO_ENQ_STRU      *pMsgHeader
)
{
    /* MM��CC����MMCC_GET_CALL_INFO_REQ */
    NAS_MM_SetTransactionEnqSenderPid(pMsgHeader->MsgHeader.ulSenderPid);

    NAS_Mm_SndCcGetCallInfoReq();

    return;
}
/* Added by n00355355 for �����ؽ�, 2015-9-17, end */



#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID NAS_MM_RcvMmcSrvccInfoNtf(
    VOS_VOID                           *pstRcvMsg
)
{
    /* ��¼SRVCC��ǵ�MMȫ�ֱ����� */
    NAS_MM_SetSrvccFlg(VOS_TRUE);

    if (VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
    {
        /* ֪ͨCCģ��SRVCC���̿�ʼ */
        NAS_MM_SndCcSrvccStatusInd(NAS_MMCC_SRVCC_STATUS_START);
    }

    return;
}



VOS_VOID NAS_MM_RcvCcSrvccCallInfoNtf(
    MMCC_SRVCC_CALL_INFO_NOTIFY_STRU   *pstCcMsg
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucTI;

#if 0
    /* ���MM����INTER_RAT_CHANGE״̬���յ�,��Ϊʱ���������,��������Ϣ */
    if (MM_INTER_RAT_CHANGE != g_MmGlobalInfo.ucState)
    {
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,"NAS_MM_RcvCcSrvccCallInfoNtf Unexpected msg!");

        return;
    }
#endif

    /* �߽��飬��������Խ�� */
    if (pstCcMsg->ucTiNum > NAS_MM_MAX_CC_CONNECTION_NUM)
    {
        pstCcMsg->ucTiNum = NAS_MM_MAX_CC_CONNECTION_NUM;
    }

    NAS_MM_SetRcvSrvccCallInfoFlg(VOS_TRUE);

    /* ����Э��涨��SRVCC�ɹ���GU��,������MT CALL */
    for (i = 0; i < pstCcMsg->ucTiNum ; i++)
    {
        ucTI = pstCcMsg->aucTransactionId[i];

        /*lint -e701*/
        if (MM_CONST_NUM_7 > ucTI)
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] |=
                        (VOS_UINT8 )( 0x01 << ucTI );
        }
        else if ((MM_CONST_NUM_7 < ucTI)
              && (MM_CONST_NUM_15 > ucTI))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] |=
                        (VOS_UINT8 )( 0x01 << (ucTI - 8) );
        }
        else
        {
        }

        /*lint +e701*/
    }

    return;
}
#endif


VOS_VOID NAS_MM_RcvSysInfoAccessBar_ProcBufferedCsService(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                               ucCsRestrictPagingFlg;
    VOS_UINT8                                               ucRestrictNormalService;
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8                    enServiceStatus;
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;

    ucCsRestrictPagingFlg = VOS_FALSE;
#endif

    /* access barʱ���������ֱ�ӷ��� */
    /* �жϽ������У����ܹ���RcvXXEstReq.ulCallType�жϣ�ǰ��������CCҵ��*/
    if (MM_CS_SERV_EMERGENCY_CALL_EXIST == Mm_ComJudgeCsServExist())
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState; /* ��¼�յ���������ʱ��״̬                 */

        NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    ucCsRestrictPagingFlg = NAS_MML_GetCsRestrictPagingFlg();
    enServiceStatus       = NAS_MM_GetLauUptNeededCsSrvStatus();
    enCsfbServiceStatus   = NAS_MML_GetCsfbServiceStatus();

    if ((NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == enCsfbServiceStatus)
     && (VOS_FALSE == ucCsRestrictPagingFlg)
     && ((MM_COM_SRVST_NORMAL_SERVICE == enServiceStatus)
      || (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)))
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();

        Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

        /* ��GU�£��ظ�paging response */
        NAS_MM_ResponseLmmPagingInd_CSFB();

        /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
        NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
        return;
    }

    ucRestrictNormalService = NAS_MML_GetCsRestrictNormalServiceFlg();

    if ((MM_COM_SRVST_NORMAL_SERVICE == enServiceStatus)
     && (VOS_FALSE == ucRestrictNormalService))
    {
        if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST == enCsfbServiceStatus)
        {
            /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
            NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

            g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();

            Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

            NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
        }
        else if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == enCsfbServiceStatus)
        {
            /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
            NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

            g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB(); /* ��¼�յ���������ʱ��״̬                 */

            Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

            NAS_MM_PerformBufferedSsService();
        }
        else
        {
        }
    }
#endif

    return;
}


#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_MM_ConvertMmccSessionTypeToRrcFormat(
    MMCC_SESSION_TYPE_ENUM_UINT8        enMmccSessionType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *penRrcSessionType
)
{
    switch(enMmccSessionType)
    {
        case MMCC_SESSION_TYPE_MO_NORMAL_CALL:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL;
            break;

        case MMCC_SESSION_TYPE_MO_EMERGENCY_CALL:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL;
            break;

        case MMCC_SESSION_TYPE_MT_NORMAL_CALL:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MT_NORMAL_CALL;
            break;

        default:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }

    return;
}


VOS_VOID NAS_MM_ConvertMmssSessionTypeToRrcFormat(
    MMSS_SESSION_TYPE_ENUM_UINT8        enMmssSessionType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *penRrcSessionType
)
{
    switch(enMmssSessionType)
    {
        case MMSS_SESSION_TYPE_MO_SS:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_SS;
            break;

        case MMSS_SESSION_TYPE_MT_SS:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MT_SS;
            break;

        default:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }

    return;
}


VOS_VOID NAS_MM_ConvertMmsmsSessionTypeToRrcFormat(
    MMSMS_SESSION_TYPE_ENUM_UINT8       enMmsmsSessionType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *penRrcSessionType
)
{
    switch (enMmsmsSessionType)
    {
        case MMSMS_SESSION_TYPE_MO_SMS:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_SMS;
            break;

        case MMSMS_SESSION_TYPE_MT_SMS:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MT_SMS;
            break;

        default:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }

    return;
}


VOS_VOID NAS_MM_RcvMmccBeginSessionNotify(
    MMCC_BEGIN_SESSION_NOTIFY_STRU     *pstRcvMsg
)
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;

    if ( MMCC_SESSION_TYPE_BUTT != pstRcvMsg->enSessionType )
    {
        NAS_MM_ConvertMmccSessionTypeToRrcFormat(pstRcvMsg->enSessionType, &enRrcSessionType);

        NAS_MM_SndBeginSessionNotify(enRrcSessionType);
    }

    return;
}


VOS_VOID NAS_MM_RcvMmccEndSessionNotify(
    MMCC_END_SESSION_NOTIFY_STRU     *pstRcvMsg
)
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;

    if ( MMCC_SESSION_TYPE_BUTT != pstRcvMsg->enSessionType )
    {
        NAS_MM_ConvertMmccSessionTypeToRrcFormat(pstRcvMsg->enSessionType, &enRrcSessionType);

        NAS_MM_SndEndSessionNotify(enRrcSessionType);
    }

    return;
}




VOS_VOID NAS_MM_RcvMmssBeginSessionNotify(
    MMSS_BEGIN_SESSION_NOTIFY_STRU     *pstRcvMsg
)
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;

    if ( MMSS_SESSION_TYPE_BUTT != pstRcvMsg->enSessionType )
    {
        NAS_MM_ConvertMmssSessionTypeToRrcFormat(pstRcvMsg->enSessionType, &enRrcSessionType);

        NAS_MM_SndBeginSessionNotify(enRrcSessionType);
    }

    return;
}


VOS_VOID NAS_MM_RcvMmssEndSessionNotify(
    MMSS_END_SESSION_NOTIFY_STRU     *pstRcvMsg
)
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;

    if ( MMSS_SESSION_TYPE_BUTT != pstRcvMsg->enSessionType )
    {
        NAS_MM_ConvertMmssSessionTypeToRrcFormat(pstRcvMsg->enSessionType, &enRrcSessionType);

        NAS_MM_SndEndSessionNotify(enRrcSessionType);
    }

    return;
}



VOS_VOID NAS_MM_RcvMmsmsBeginSessionNotify(
    MMSMS_BEGIN_SESSION_NOTIFY_STRU    *pstRcvMsg
)
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;

    if ( MMSMS_SESSION_TYPE_BUTT != pstRcvMsg->enSessionType )
    {
        NAS_MM_ConvertMmsmsSessionTypeToRrcFormat(pstRcvMsg->enSessionType, &enRrcSessionType);

        NAS_MM_SndBeginSessionNotify(enRrcSessionType);
    }

    return;
}


VOS_VOID NAS_MM_RcvMmsmsEndSessionNotify(
    MMSMS_END_SESSION_NOTIFY_STRU     *pstRcvMsg
)
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;

    if ( MMSMS_SESSION_TYPE_BUTT != pstRcvMsg->enSessionType )
    {
        NAS_MM_ConvertMmsmsSessionTypeToRrcFormat(pstRcvMsg->enSessionType, &enRrcSessionType);

        NAS_MM_SndEndSessionNotify(enRrcSessionType);
    }

    return;
}






#endif


VOS_UINT8 NAS_MM_CheckCallStatusNtyValid(
    MMCC_CALL_STATUS_NTF_STRU          *pstCallStatusNty
)
{
    /* CALLģ��Ŀǰֻ��֪ͨsucc��fail������ȡֵ����Ҫ���� */
    if ((MNCC_CALL_STATUS_SETUP_SUCC != pstCallStatusNty->enCallStatus)
     && (MNCC_CALL_STATUS_SETUP_FAIL != pstCallStatusNty->enCallStatus))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT8 NAS_MM_CheckSsStatusNtyValid(
    MMSS_STATUS_NTY_STRU               *pstSsStatusNty
)
{
    /* SSģ��Ŀǰֻ��֪ͨsucc��fail������ȡֵ����Ҫ���� */
    if ((SSA_SS_STATUS_SETUP_SUCC   != pstSsStatusNty->enSsStatus)
     && (SSA_SS_STATUS_SETUP_FAIL   != pstSsStatusNty->enSsStatus))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_VOID NAS_MM_RcvMmccCallStatusNty(
    MMCC_CALL_STATUS_NTF_STRU          *pstCallStatusNty
)
{
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enCallStatus;
    RRMM_TRANSACTION_STATUS_ENUM_UINT8  enTransStatus;

    enCallStatus    = NAS_MML_GetMoCallStatus();
    enTransStatus   = RRMM_TRANSACTION_FAIL;

    /* CALLģ��Ŀǰֻ��֪ͨsucc��fail������ȡֵ����Ҫ���� */
    if (VOS_FALSE == NAS_MM_CheckCallStatusNtyValid(pstCallStatusNty))
    {
        return;
    }

    /* ���н�����־Ϊstartʱ֪ͨ����������ͷ�֮��FR�����Ϊfail��succ��ǰ���Ѿ�֪ͨ���ˣ�����Ҫ��֪ͨ */
    if (VOS_TRUE == NAS_MML_GetMoCallSetupFlg())
    {
        NAS_MM_ConvertCallStatusToTransactionStatus(pstCallStatusNty->enCallStatus, &enTransStatus);
        NAS_MM_SndTransactionStatusNotify(enTransStatus);
    }

    /* ���MMC��������ʱ�Ҷϵ绰��֪ͨMMCֹͣ��GU�����´�LTE��ʼ����;���MMC����ON PLMN�������ȼ����뼼��BG�Ѷ�ʱ�� */
    if ( ((NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START  == enCallStatus)
       || (NAS_MML_CSFB_MO_EMC_CALL_SETUP_START     == enCallStatus))
      && (MNCC_CALL_STATUS_SETUP_FAIL               == pstCallStatusNty->enCallStatus) )
    {
        NAS_MM_SndMmcPlmnSearchInd(MM_MMC_PLMN_SEARCH_TYPE_CSFB_END);
    }

    /* ���º��н�����־ */
    NAS_MM_UpdateCallStatus_RcvCallStatusNty(pstCallStatusNty->enCallStatus);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_RcvMmccGetCallInfoCnf
 ��������  : MM�յ�MMCC_GET_CALL_INFO_CNF�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��17��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_RcvMmccGetCallInfoCnf(
    MMCC_GET_CALL_INFO_CNF_STRU        *pstMsg
)
{
    VOS_UINT32                          ucIndex;
    VOS_UINT8                           ucIsCallActive;
    RRC_NAS_CS_TRANSACTION_ENUM_UINT8   enCsTransactionStatus;
    VOS_UINT32                          ulRcvPid;

    ucIsCallActive  = VOS_FALSE;

    for (ucIndex = 0; ucIndex < NAS_CC_MAX_ENTITY_NUM; ucIndex++)
    {
        if (NAS_CC_CALL_STATE_U10 == pstMsg->astCallInfo[ucIndex].enCallState)
        {
            ucIsCallActive = VOS_TRUE;
            break;
        }
    }

    NAS_MML_GetMmlCsTransactionStatus(&enCsTransactionStatus);

    ulRcvPid = NAS_MM_GetTransactionEnqSenderPid();

    NAS_MM_SndAsCsTransactionStatus(enCsTransactionStatus, ulRcvPid, ucIsCallActive);

    return;
}



VOS_VOID NAS_MM_RcvMmssStatusNty(
    MMSS_STATUS_NTY_STRU               *pstSsStatusNty
)
{
    RRMM_TRANSACTION_STATUS_ENUM_UINT8  enTransStatus;
    NAS_MML_MO_SS_STATUS_ENUM_UINT8     enOldSsMoStatus;

    enOldSsMoStatus = NAS_MML_GetMoSsStatus();
    enTransStatus   = RRMM_TRANSACTION_FAIL;

    /* SSģ��Ŀǰֻ��֪ͨsucc��fail������ȡֵ����Ҫ���� */
    if (VOS_FALSE == NAS_MM_CheckSsStatusNtyValid(pstSsStatusNty))
    {
        return;
    }

    /* ��ҵ������־ʱ��֪ͨAS�������ͷ�ʱ����FR */
    if (VOS_TRUE == NAS_MML_GetMoSsSetupFlg())
    {
        NAS_MM_ConvertSsStatusToTransactionStatus(pstSsStatusNty->enSsStatus, &enTransStatus);
        NAS_MM_SndTransactionStatusNotify(enTransStatus);
    }

    /* ���MMC��������ʱҵ�������֪ͨMMCֹͣ��GU�����´�LTE��ʼ����;���MMC����ON PLMN�������ȼ����뼼��BG�Ѷ�ʱ�� */
    if ((NAS_MML_CSFB_MO_SS_SETUP_START == enOldSsMoStatus)
     && (SSA_SS_STATUS_SETUP_FAIL       == pstSsStatusNty->enSsStatus))
    {
        NAS_MM_SndMmcPlmnSearchInd(MM_MMC_PLMN_SEARCH_TYPE_CSFB_END);
    }

    /* ���±�־ */
    NAS_MM_UpdateSsStatus_RcvSsStatusNty(pstSsStatusNty->enSsStatus);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ParseT3246IE
 ��������  : ����CM SERVICE REJ��Ϣ�е�T3246
 �������  : VOS_UINT8                          *pucRcvMsg
             VOS_UINT16                          usMsgSize
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ParseT3246IE(
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT8                          *pucIsT3246Exist
)
{
    VOS_UINT8                           ucIndex;

    /* Э���½�:
        3GPP 24008 9.2.6 CM service reject

        IEI     Information element             Type/Reference         Presence    Format     Length
                Mobility management         Protocol discriminator        M          V         1/2
                protocol discriminator      10.2

                Skip Indicator              Skip Indicator                M          V         1/2
                                            10.3.1

                CM Service Reject           Message type                  M          V          1
                message type                10.4

                Reject cause                Reject cause                  M          V          1
                                            10.5.3.6

        36      T3246 value                 MM timer                      O         TLV         3
                                            10.5.3.16


        3GPP 24008 10.5.3.16 MM Timer

        MM Timer IEI:               octet 1
        Length of MM Timer contents:octet 2
        MM Timer value:             octet 3

        Timer value (octet 3)

        Bits 5 to 1 represent the binary coded timer value.

        Bits 6 to 8 defines the timer value unit for the MM timer as follows:
        Bits
        8 7 6
        0 0 0  value is incremented in multiples of 2 seconds
        0 0 1  value is incremented in multiples of 1 minute
        0 1 0  value is incremented in multiples of decihours
        1 1 1  value indicates that the timer is deactivated.

        Other values shall be interpreted as multiples of 1 minute in this version of the protocol.

        The value indicated is contructed by multiplying the value in bits 5 to 1 with the timer value unit in bits 8 to 6,
        unless the timer value unit indicates the timer being deactivated.
    */

    /* ����С�ڵ���3����ʾû��Я��T3246 IE�� */
    if ( usMsgSize <= MM_CM_SRV_REJ_MIN_LEN )
    {
        *pucIsT3246Exist    = VOS_FALSE;

        return;
    }

    /* ����С��6��T3246 IE���쳣 */
    if ( usMsgSize < MM_CM_SRV_REJ_MAX_LEN )
    {
        *pucIsT3246Exist    = VOS_FALSE;

        return;
    }

    ucIndex = MM_CM_SRV_REJ_MIN_LEN;

    /* MM Timer IEI���� */
    if (MM_IE_MM_TIMER != pucRcvMsg[ucIndex])
    {
        *pucIsT3246Exist    = VOS_FALSE;

        return;
    }


    ucIndex++;

    /* Length of MM Timer contentsΪ0 */
    if (0 == pucRcvMsg[ucIndex])
    {
        *pucIsT3246Exist    = VOS_FALSE;

        return;
    }

    ucIndex++;

    /* bits 8 to 6:111 value indicates that the timer is deactivated  */
    if (0xE0 == (pucRcvMsg[ucIndex] & 0xE0))
    {
        *pucIsT3246Exist    = VOS_FALSE;

        return;
    }

    /* bits 5 to 1: 00000 timer value=0 */
    if (0 == (pucRcvMsg[ucIndex] & 0x1F) )
    {
        *pucIsT3246Exist    = VOS_FALSE;

        return;

    }

    *pucIsT3246Exist    = VOS_TRUE;

    return;

}




VOS_UINT8 NAS_MM_RcvCspagingInd_PreProc(
    VOS_VOID                           *pstRcvMsg
)
{
/* Added by zwx247453 for CHR optimize, 2015-03-13 begin */
#if (FEATURE_ON == FEATURE_PTM)
    NAS_MM_ParseErrLogCsPagingInfo(pstRcvMsg);
#endif
/* Added by zwx247453 for CHR optimize, 2015-03-13 end */

    switch (g_MmGlobalInfo.ucState)
    {
        case MM_IDLE_PLMN_SEARCH:
        case MM_IDLE_NORMAL_SERVICE:
        case MM_IDLE_LIMITED_SERVICE:
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
        case LOCATION_UPDATING_PENDING:

            return MM_EVENT_ID_PAGING_IND;

        default:
#if (FEATURE_ON == FEATURE_PTM)
            /* �ж�Ϊ��IDLE״̬����¼�쳣 */
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_STATE_ERR);
#endif
            return MM_EVENT_ID_PAGING_IND;
    }
}


VOS_UINT32 NAS_MM_GetLauRequestInfo(
    NAS_MSG_STRU                           *pstLauReqMsg,
    NAS_LAU_TYPE_ENUM_UINT8                *penLauType,
    VOS_UINT8                              *pucFollowOnFlg,
    NAS_ADDITION_UPDATE_PARA_ENUM_UINT8    *penAdditionUpdatePara
)
{
    VOS_UINT8                          *pucMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulMsgSize;
    VOS_UINT32                          ulPointer;

    /* ������� */
    if ( (VOS_NULL_PTR == pstLauReqMsg)
      || (VOS_NULL_PTR == penLauType)
      || (VOS_NULL_PTR == pucFollowOnFlg)
      || (VOS_NULL_PTR == penAdditionUpdatePara) )
    {
        return VOS_ERR;
    }

    /* ��ʼ�� */
    ulPointer   = (VOS_UINT32)pstLauReqMsg->aucNasMsg;
    pucMsg      = (VOS_UINT8 *)ulPointer;
    ulIndex     = 0;
    ulMsgSize   = pstLauReqMsg->ulNasMsgSize;

    /* LAU����Ϣ������СΪ11  */
    if (ulMsgSize < 11)
    {
        return VOS_ERR;
    }

    /* ���� Mobility �� Skip Indicator */
    ulIndex     = ulIndex + 1;

    /* �ж��Ƿ���LAU��Ϣ */
    if(MM_IE_MSG_TYPE_LU_REQUEST != (pucMsg[ulIndex] & 0x3F))
    {
        return VOS_ERR;
    }
    /* ����msg type  ���� */
    ulIndex     = ulIndex + 1;

    /* ����LAU type �� Follow */
    *penLauType  = pucMsg[ulIndex] & 0x03;

    /* ����Follow */
    if ((pucMsg[ulIndex] & 0x8) > 0)
    {
        *pucFollowOnFlg = VOS_TRUE;
    }
    else
    {
        *pucFollowOnFlg = VOS_FALSE;
    }

    /* ֱ������Mobile identity */
    ulIndex     = ulIndex + 7;

    /* ����Mobile identity ���� */
    if (( 0 == pucMsg[ulIndex] ) || ( 8 <  pucMsg[ulIndex] ))
    {
        return VOS_ERR;
    }
    else
    {
        ulIndex = ulIndex + pucMsg[ulIndex];
    }

    /* ȥ��Mobilt identity length */
    ulIndex = ulIndex + 1;

    *penAdditionUpdatePara = NAS_ADDITION_UPDATE_PARA_NONE;

    while (ulIndex < ulMsgSize)
    {
        if (0x33 == pucMsg[ulIndex])
        {
            ulIndex = ulIndex + 5;
        }
        else if (0xC0 == (pucMsg[ulIndex] & 0xF0 ))
        {
            switch (pucMsg[ulIndex] & 0x3)
            {
                case 1:
                    *penAdditionUpdatePara = NAS_ADDITION_UPDATE_PARA_MT;
                    break;

                case 2:
                    *penAdditionUpdatePara = NAS_ADDITION_UPDATE_PARA_MO;
                    break;

                case 3:
                    *penAdditionUpdatePara = NAS_ADDITION_UPDATE_PARA_MO_MT;
                    break;

                default:
                    *penAdditionUpdatePara = NAS_ADDITION_UPDATE_PARA_NONE;
                    break;
            }
            break;
        }
        else if (0xD0 == (pucMsg[ulIndex] & 0xF0 ))
        {
            ulIndex = ulIndex + 1;
        }
        else if (0xE0 == (pucMsg[ulIndex] & 0xF0 ))
        {
            ulIndex = ulIndex + 1;
        }
        else
        {
            ulIndex = ulIndex + 1;
        }
    }

    return VOS_OK;
}

/* Added by h00313353 for SMS Filter Prj, 2015-9-17, begin */
/*****************************************************************************
 �� �� ��  : NAS_MM_GetL3ReqMsgPd
 ��������  : �ṩ��������ȡReq��Ϣ�е�PD��Ϣ
 �������  : pstSendMsg: Data Req��Ϣ���� RRMM_DATA_REQ_STRU�ṹ
 �������  : ucPd: Data Req��Ϣ��������PDֵ

 �� �� ֵ  : VOS_OK: ��ȡ�ɹ�
             VOS_ERR:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��17��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MM_GetL3ReqMsgPd(
    RRMM_DATA_REQ_STRU                     *pstSendMsg,
    VOS_UINT8                              *pucPd
)
{
    if ((VOS_NULL_PTR == pstSendMsg)
     || (VOS_NULL_PTR == pucPd))
    {
        return VOS_ERR;
    }

    if (RRMM_DATA_REQ   != pstSendMsg->MsgHeader.ulMsgName)
    {
        return VOS_ERR;
    }

    /* SenderPid��� */
    if ((WUEPS_PID_MM   != pstSendMsg->MsgHeader.ulSenderPid)
     && (WUEPS_PID_GMM  != pstSendMsg->MsgHeader.ulSenderPid))
    {
        return VOS_ERR;
    }

    /* ReceiverPid��� */
    if ((WUEPS_PID_WRR  != pstSendMsg->MsgHeader.ulReceiverPid)
     && (UEPS_PID_GAS   != pstSendMsg->MsgHeader.ulReceiverPid))
    {
        return VOS_ERR;
    }

    *pucPd = (pstSendMsg->SendNasMsg.aucNasMsg[0] & 0x0F);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_GetL3RcvMsgPd
 ��������  : �ṩ��������ȡInd��Ϣ�е�PD��Ϣ
 �������  : pstSendMsg: Data Ind��Ϣ���� RRMM_DATA_IND_STRU�ṹ
 �������  : ucPd: Data Ind��Ϣ��������PDֵ

 �� �� ֵ  : VOS_OK: ��ȡ�ɹ�
             VOS_ERR:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��17��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MM_GetL3RcvMsgPd(
    RRMM_DATA_IND_STRU                     *pstRcvMsg,
    VOS_UINT8                              *pucPd
)
{
    if ((VOS_NULL_PTR == pstRcvMsg)
     || (VOS_NULL_PTR == pucPd))
    {
        return VOS_ERR;
    }

    if (RRMM_DATA_IND   != pstRcvMsg->MsgHeader.ulMsgName)
    {
        return VOS_ERR;
    }

    /* SenderPid��� */
    if ((WUEPS_PID_WRR  != pstRcvMsg->MsgHeader.ulSenderPid)
     && (UEPS_PID_GAS   != pstRcvMsg->MsgHeader.ulSenderPid))
    {
        return VOS_ERR;
    }

    /* ReceiverPid��� */
    if ((WUEPS_PID_MM   != pstRcvMsg->MsgHeader.ulReceiverPid)
     && (WUEPS_PID_GMM  != pstRcvMsg->MsgHeader.ulReceiverPid))
    {
        return VOS_ERR;
    }

    *pucPd = (pstRcvMsg->RcvNasMsg.aucNasMsg[0] & 0x0F);

    return VOS_OK;
}
/* Added by h00313353 for SMS Filter Prj, 2015-9-17, end */


/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

