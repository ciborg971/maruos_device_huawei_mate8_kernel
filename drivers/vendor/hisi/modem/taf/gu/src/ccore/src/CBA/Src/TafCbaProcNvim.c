

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaProcNvim.h"
#include  "NVIM_Interface.h"
#include  "TafCbaComFunc.h"
#include  "MnComm.h"
#include  "TafLog.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_NVIM_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_VOID TAF_CBA_ReadNvUserAcceptMsgIdList(
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmiRangeList
)
{
    VOS_UINT32                          ulInx;
    VOS_UINT32                          ulCbmiRangNum;
    TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU  *pstCbmiNvRangeList = VOS_NULL_PTR;

    /* �����ڴ����ڶ�ȡNV �е�CBS���� */
    pstCbmiNvRangeList = (TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, 
                                    sizeof(TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU));

    if (VOS_NULL_PTR == pstCbmiNvRangeList)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ReadNvUserAcceptMsgIdList: ALLOC MEM FAILED!");
        return;
    }

    /*  ��ȡNV en_NV_Item_CBS_MID_Range_List_New */
    if (NV_OK != NV_Read(en_NV_Item_CBS_MID_Range_List_New,
                         pstCbmiNvRangeList,
                         sizeof(TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU)))
    {
        pstCbmiNvRangeList->ulCbmirNum = 0;

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_GetNvimAcceptModeCbmiRangeList: To read CBS MidRangeList in NVIM failed!");

        PS_MEM_FREE(WUEPS_PID_TAF, pstCbmiNvRangeList);

        return;
    }

    /* �˴�����һ������,��ֹ���� */
    if ( pstCbmiNvRangeList->ulCbmirNum > TAF_CBA_MAX_CBMID_RANGE_NUM )
    {
        pstCbmiNvRangeList->ulCbmirNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    /* 
       ת��NV�е�CBS����Ϊ�ڴ��еĽṹ�������˵� REJECT ģʽ��  CBMI RANGE��
       Ŀǰֻ֧��ACCEPT ģʽ�� CBMI RANGE, 
    */
    ulCbmiRangNum = 0;

    for ( ulInx = 0; ulInx < pstCbmiNvRangeList->ulCbmirNum; ulInx++ )
    {
        if ( TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT == pstCbmiNvRangeList->astCbmiRangeInfo[ulInx].ulRcvMode )
        {
            pstCbmiRangeList->astCbmiRangeInfo[ulCbmiRangNum].enRcvMode   = pstCbmiNvRangeList->astCbmiRangeInfo[ulInx].ulRcvMode;
            pstCbmiRangeList->astCbmiRangeInfo[ulCbmiRangNum].usMsgIdFrom = pstCbmiNvRangeList->astCbmiRangeInfo[ulInx].usMsgIdFrom;
            pstCbmiRangeList->astCbmiRangeInfo[ulCbmiRangNum].usMsgIdTo   = pstCbmiNvRangeList->astCbmiRangeInfo[ulInx].usMsgIdTo;
            PS_MEM_CPY(pstCbmiRangeList->astCbmiRangeInfo[ulCbmiRangNum].ucLabel,
                     pstCbmiNvRangeList->astCbmiRangeInfo[ulInx].ucLabel,TAF_CBA_NVIM_MAX_LABEL_NUM);
            ulCbmiRangNum++;
        }
    }
    
    pstCbmiRangeList->usCbmirNum = (VOS_UINT16)ulCbmiRangNum;

    /* NV��CBS���������Ѿ�ת��Ϊ�ڴ������ýṹ���Ƿ�Ϊ��ȡNV������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstCbmiNvRangeList);

    return;
}
VOS_VOID TAF_CBA_AppendNvUserAcceptMsgIdList(VOS_VOID)
{
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmiNvRangeList = VOS_NULL_PTR;

    pstCbmiNvRangeList = (TAF_CBA_CBMI_RANGE_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));

    if (VOS_NULL_PTR == pstCbmiNvRangeList)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_AppendNvUserAcceptMsgIdList: ALLOC MEM FAILED!");
        return;
    }

    PS_MEM_SET(pstCbmiNvRangeList, 0x00, sizeof(TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU));

    TAF_CBA_ReadNvUserAcceptMsgIdList(pstCbmiNvRangeList);

    /* ������ */
    TAF_CBA_SortCbmiRangeList(pstCbmiNvRangeList);

    /* �����ڴ��б� */
    (VOS_VOID)TAF_CBA_AddCbMiRangeListToActiveList(pstCbmiNvRangeList);

    PS_MEM_FREE(WUEPS_PID_TAF, pstCbmiNvRangeList);

    return;
}


VOS_VOID TAF_CBA_ReadCbsServiceParamNvim(VOS_VOID)
{
    TAF_CBA_CBS_SERVICE_PARM_STRU       stSrvPara;


    stSrvPara.ucCbStatus = TAF_CBA_CBSTATUS_DISABLE;



    /* Ĭ��ʹ���ظ����� */
    stSrvPara.ucDupDetectCfg = TAF_CBA_DUP_DETECT_CFG_ALL_ENABLE;


    /* Ĭ�ϲ��ϱ���ҳ��ֻ��APP�ϱ���Ч�ֽ� */
    stSrvPara.ucRptAppFullPageFlg = VOS_FALSE;

    /* ��ȡNV en_NV_Item_CBS_Service_Para */
    if (NV_OK != NV_Read(en_NV_Item_CBS_Service_Para,
                         &stSrvPara,
                         sizeof(TAF_CBA_CBS_SERVICE_PARM_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ReadCbsServiceParamNvim: To read CBS service parameter in NVIM failed!");
        stSrvPara.ucCbStatus = TAF_CBA_CBSTATUS_DISABLE;
    }

    TAF_CBA_SetCbsStatus(stSrvPara.ucCbStatus);

    if ( stSrvPara.ucDupDetectCfg < TAF_CBA_DUP_DETECT_CFG_BUTT )
    {
        TAF_CBA_SetDupDetectCfg(stSrvPara.ucDupDetectCfg);
    }
    else
    {
        TAF_CBA_SetDupDetectCfg(TAF_CBA_DUP_DETECT_CFG_ALL_ENABLE);
    }



    TAF_CBA_SetRptAppFullPageFlg(stSrvPara.ucRptAppFullPageFlg);

}

#if (FEATURE_ETWS == FEATURE_ON)
VOS_VOID TAF_CBA_ReadEtwsServieCfgNvim(VOS_VOID)
{
    TAF_CBA_NVIM_ETWS_CFG_STRU          stNewNvinEtwsInfo;
    TAF_CBA_MS_CFG_ETWS_INFO_STRU       stMsEtwsInfo;
    VOS_UINT32                          ulIndex;

    /* ��ʼ���ֲ����� */
    PS_MEM_SET(&stNewNvinEtwsInfo, 0x00, sizeof(TAF_CBA_NVIM_ETWS_CFG_STRU));


    PS_MEM_SET(&stMsEtwsInfo,      0x00, sizeof(stMsEtwsInfo));

    /* ��ȡNV en_NV_Item_ETWS_Service_Cfg_Para */
    if (NV_OK != NV_Read(en_NV_Item_ETWS_Service_Cfg_Para,
                         &(stNewNvinEtwsInfo),
                         sizeof(TAF_CBA_NVIM_ETWS_CFG_STRU)))
    {
        stNewNvinEtwsInfo.ucEtwsEnableFlg = VOS_FALSE;
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ReadEtwsServieCfgNvim: To read EtwsInfo in NVIM failed!");
    }

    /* ��NV�е�EtwsCfg������MsCfgEtwsInfo */
    stMsEtwsInfo.ucEtwsEnableFlg                                     =
            stNewNvinEtwsInfo.ucEtwsEnableFlg;

    stMsEtwsInfo.stDupDetectCfg.ucEnhDupDetectFlg                    =
            stNewNvinEtwsInfo.stDupDetcCfg.ucEnhDupDetcFlg;

    stMsEtwsInfo.stDupDetectCfg.ulNormalTimeLen                      =
            (VOS_UINT32)(stNewNvinEtwsInfo.stDupDetcCfg.usNormalTimeLen * TAF_CBA_MINUTE_TO_SECOND);

    stMsEtwsInfo.stDupDetectCfg.stDupDetectTimeLen.ulSpecMccTimeLen  =
            (VOS_UINT32)(stNewNvinEtwsInfo.stDupDetcCfg.usSpecMccTimeLen * TAF_CBA_MINUTE_TO_SECOND);

    stMsEtwsInfo.stDupDetectCfg.stDupDetectTimeLen.ulOtherMccTimeLen =
            (VOS_UINT32)(stNewNvinEtwsInfo.stDupDetcCfg.usOtherMccTimeLen * TAF_CBA_MINUTE_TO_SECOND);

    stMsEtwsInfo.ulTempEnableCbsTimeLen                              =
            (VOS_UINT32)(stNewNvinEtwsInfo.usTempEnableCbsTimeLen * TAF_CBA_MINUTE_TO_SECOND);

    for ( ulIndex = 0; ulIndex < TAF_CBA_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM; ulIndex++ )
    {
        stMsEtwsInfo.stDupDetectCfg.stDupDetectTimeLen.aulSpecMcc[ulIndex] =
                stNewNvinEtwsInfo.stDupDetcCfg.aulSpecMcc[ulIndex];
    }

    for ( ulIndex = 0; ulIndex < TAF_CBA_NVIM_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM; ulIndex++ )
    {
        stMsEtwsInfo.astSpecEtwsMsgIdList[ulIndex].usMsgIdFrom =
               stNewNvinEtwsInfo.astSpecEtwsMsgIdList[ulIndex].usMsgIdFrom;

        stMsEtwsInfo.astSpecEtwsMsgIdList[ulIndex].usMsgIdTo   =
                stNewNvinEtwsInfo.astSpecEtwsMsgIdList[ulIndex].usMsgIdTo;
    }

    /* ��range list����, ��֤ usMsgIdFrom С�ڵ��� usMsgIdTo */
    TAF_CBA_SortEtwsRangList( &(stMsEtwsInfo.astSpecEtwsMsgIdList[0]),
                              TAF_CBA_NVIM_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM );

    /* ��NV�ж�ȡ��ֵ���浽ȫ�ֱ����� */
    TAF_CBA_SetMsCfgEtwsInfo(&stMsEtwsInfo);

}
#endif
VOS_VOID TAF_CBA_WriteCbmiRangeListNvim(VOS_VOID)
{
    TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU  *pstNvimCbmiRangeList;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstMemCbmiRangeList;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulCbmiInx;

    pstMemCbmiRangeList  = TAF_CBA_GetCbMiRangeList();

    pstNvimCbmiRangeList = (TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU));
    if (VOS_NULL_PTR == pstNvimCbmiRangeList)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_WriteCbmiRangeListNvim: ALLOC MEM FAILED!");
        return;
    }

    /* �ڴ��ʼ�� */
    PS_MEM_SET(pstNvimCbmiRangeList, 0x00, sizeof(TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU));

    pstNvimCbmiRangeList->ulCbmirNum = pstMemCbmiRangeList->usCbmirNum;

    for ( ulCbmiInx = 0; ulCbmiInx < TAF_CBA_MAX_CBMID_RANGE_NUM; ulCbmiInx++ )
    {
        pstNvimCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].ulRcvMode   = pstMemCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].enRcvMode;
        pstNvimCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].usMsgIdFrom = pstMemCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].usMsgIdFrom;
        pstNvimCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].usMsgIdTo   = pstMemCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].usMsgIdTo;
        PS_MEM_CPY(pstNvimCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].ucLabel,
                   pstMemCbmiRangeList->astCbmiRangeInfo[ulCbmiInx].ucLabel,TAF_CBA_NVIM_MAX_LABEL_NUM);
    }

    /* дNV en_NV_Item_CBS_MID_Range_List_New */
    ulRet = NV_Write(en_NV_Item_CBS_MID_Range_List_New,
                     pstNvimCbmiRangeList,
                     sizeof(TAF_CBA_NVIM_CBMI_RANGE_LIST_STRU));

    if (NV_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_WriteCbmiRangeListNvim:Fail to write CBS cbmir in NVIM!");
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstNvimCbmiRangeList);
}

#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
