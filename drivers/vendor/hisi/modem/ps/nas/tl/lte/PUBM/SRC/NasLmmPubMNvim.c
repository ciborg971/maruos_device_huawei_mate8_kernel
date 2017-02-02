

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMInclude.h"
#include    "UsimPsInterface.h"
/* lihong00150010 ims begin */
#include    "SysNvId.h"
/* lihong00150010 ims begin */


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMNVIM_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMNVIM_C
/*lint +e767*/


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

VOS_UINT32                              g_aucNvimBuff[NAS_NVIM_MAX_BUFFER];

static NAS_LMM_NV_ACT_STRU               g_astNvDataMap[] =
{
    /*NVIM����*/
    {EN_NV_ID_UE_NET_CAPABILITY,      NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_IMSI,                   NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_EPS_LOC,                NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_SEC_CONTEXT,            NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_UE_CENTER,              NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    /* lihong00150010 ims begin */
    {en_NV_Item_UMTS_CODEC_TYPE,      NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {en_NV_Item_MED_CODEC_TYPE,       NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    /* lihong00150010 ims end */
    {EN_NV_ID_UE_VOICE_DOMAIN,        NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_NAS_RELEASE,            NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_CONFIG_NWCAUSE,         NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_DAM_CONFIG_PARA,        NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
    {EN_NV_ID_LNAS_COMM_CONFIG_PARA,  NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},

    {EN_NV_ID_LNAS_SWITCH_PARA,       NAS_LMM_DecodeOneNvItem,   NAS_LMM_EncodeOneNvItem},
};

VOS_UINT32 g_ulNvDataMapNum = sizeof(g_astNvDataMap)/sizeof(NAS_LMM_NV_ACT_STRU);

/* ����USIM��ȡ���ļ�ID */
VOS_UINT32 g_aulMmUsimEf[] = {  0x6F38, 0x6FAD, 0x6F7B, 0x6F31, 0x6F7E,
                                0x6F73, 0x6F07, 0x6F08, 0x6F09, 0x6FE4,
                                0x6F78};
VOS_UINT32 g_ulUsimSecuFileLen;

VOS_UINT8  g_aucUsimSecuContext[NAS_NVIM_SECU_CONTEXT_MAX_LEN] = {0}; /* �����ϴ�д���İ�ȫ���������� */

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : NAS_LMM_SndUsimReadFileReq()
 Description    : ��USIM���Ͷ�ȡ�ļ�����
 Input          : ulAppType         Ӧ������
                  ucRecordNum
                  ulOpId
                  stGetFilePath     �ļ�·��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
          1.zhaochen 00308719  2015-02-10   Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SndUsimReadFileReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    VOS_UINT8                       ucRecordNum,
    VOS_UINT8                       ulOpId,
    USIMM_FILEPATH_INFO_STRU       *pstGetFilePath
)
{
    USIMM_READFILE_REQ_STRU     *pstUsimReadFileReq;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstUsimReadFileReq = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(USIMM_READFILE_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstUsimReadFileReq)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_SndUsimReadFileReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndUsimReadFileReq_ENUM
,LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_LMM_MEM_SET( pstUsimReadFileReq, 0, sizeof(USIMM_READFILE_REQ_STRU));

    /*��д��Ϣͷ*/
    /*��Ϣ�ṹ���е�SendPara�����洢OpId*/
    NAS_EMM_USIM_MSG_HEAD(pstUsimReadFileReq, USIMM_READFILE_REQ, ulAppType, ulOpId);

    /*��д��Ϣ����*/
    pstUsimReadFileReq->ucRecordNum = ucRecordNum;
    pstUsimReadFileReq->bNeedReadCache = VOS_TRUE;
    NAS_LMM_MEM_CPY(&(pstUsimReadFileReq->stFilePath),
                 pstGetFilePath,
                 sizeof(USIMM_FILEPATH_INFO_STRU));

    /*������Ϣ���ͺ��� */
    NAS_LMM_SEND_MSG(pstUsimReadFileReq);

}

/*****************************************************************************
 Function Name  : NAS_LMM_SndUsimReadFileReq()
 Description    : ��USIM����д���ļ�����
 Input          : ulAppType         Ӧ������
                  ucRecordNum
                  ulOpId
                  stGetFilePath     �ļ�·��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
          1.zhaochen 00308719  2015-02-15   Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SndUsimWriteFileReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    VOS_UINT8                       ucRecordNum,
    VOS_UINT8                       ulOpId,
    USIMM_FILEPATH_INFO_STRU       *pstGetFilePath,
    VOS_UINT16                      usDataLen,
    VOS_UINT8                      *aucContent
)
{
    USIMM_UPDATEFILE_REQ_STRU     *pstUsimUpdateFileReq;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstUsimUpdateFileReq = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(USIMM_READFILE_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstUsimUpdateFileReq)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_SndUsimWriteFileReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndUsimWriteFileReq_ENUM
,LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_LMM_MEM_SET( pstUsimUpdateFileReq, 0, sizeof(USIMM_READFILE_REQ_STRU));

    /*��д��Ϣͷ*/
    /*��Ϣ�ṹ���е�SendPara�����洢OpId*/
    NAS_EMM_USIM_MSG_HEAD(pstUsimUpdateFileReq, USIMM_UPDATEFILE_REQ, ulAppType, ulOpId);

    /*��д��Ϣ����*/
    pstUsimUpdateFileReq->ucRecordNum = ucRecordNum;
    pstUsimUpdateFileReq->usDataLen = usDataLen;
    NAS_LMM_MEM_CPY(&(pstUsimUpdateFileReq->stFilePath),
                 pstGetFilePath,
                 sizeof(USIMM_FILEPATH_INFO_STRU));
    NAS_LMM_MEM_CPY(pstUsimUpdateFileReq->aucContent,
                 aucContent,
                 usDataLen);

    /*������Ϣ���ͺ��� */
    NAS_LMM_SEND_MSG(pstUsimUpdateFileReq);

}
/* 2015-03-15: ע�Ȿ���Ǵ��ļ�������޸� */

/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_LMM_NvimWrite
(
    NAS_LMM_ITEM_TYPE_ENUM_UINT32       ulNVItemType,
    VOS_VOID                           *pData,
    VOS_UINT16                          usDataLen
)
{
    VOS_UINT32                          ulRslt = NAS_LMM_NVIM_FAIL;
    NAS_NVIM_CTRL_TBL                   stNvCtrlTbl;
    VOS_UINT32                          i;
    NAS_LMM_NV_ACTION_FUN               pActFun = NAS_LMM_NULL_PTR;

    /*check input params*/
    if((NAS_NVIM_NULL_PTR == pData)
        ||(usDataLen == VOS_NULL)
        ||(ulNVItemType > EN_NV_ID_PS_END))
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimWrite:input para ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_NvimWrite_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_NVIM_FAIL;
    }

    /*Initalize NVIM ctrl tbl*/
    stNvCtrlTbl.pData       = pData;
    stNvCtrlTbl.pNvData     = g_aucNvimBuff;
    stNvCtrlTbl.usDataLen   = usDataLen;
    stNvCtrlTbl.usNvDataLen = 0;

    /* ��g_astNvDataMap�в��Ҷ�Ӧ��NV TYPE*/
    for(i = 0; i < g_ulNvDataMapNum; i++)
    {
        /* ��NV������ͬ,���ҵ���,���ص�ǰ��NV�����������˳�ѭ�� */
        if(ulNVItemType == g_astNvDataMap[i].ulEventType)
        {
            pActFun = g_astNvDataMap[i].pfEncodeActionFun;
            break;
        }
    }

    if (NAS_LMM_NULL_PTR == pActFun)
    {
        /* ����Ҳ�������������ʾ��ǰû�иô����� */
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimWrite:Action functin is ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_NvimWrite_ENUM
,LNAS_FUNCTION_LABEL1);

        return NAS_LMM_NVIM_FAIL;
    }

    ulRslt = (*pActFun) (&stNvCtrlTbl);

    if ( NAS_LMM_NVIM_WRITTEN_UNNEEDED == ulRslt)
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_NvimWrite: Don't need to write usim.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_NvimWrite_ENUM
,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_NVIM_WRITTEN_UNNEEDED;
    }

    if(ulRslt != NAS_LMM_NVIM_OK)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimWrite:Encode is ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_NvimWrite_ENUM
,LNAS_FUNCTION_LABEL3);

        return NAS_LMM_NVIM_FAIL;
    }

    /*���������NV��д��Ϣ*/
    /*lint -e718*/
    /*lint -e516*/
    /*lint -e732*/
    ulRslt = LPs_NvimItem_Write(ulNVItemType, stNvCtrlTbl.pNvData, stNvCtrlTbl.usNvDataLen);
    /*lint +e732*/
    /*lint +e516*/
    /*lint +e718*/
    return ulRslt;

}


NAS_LMM_USIM_NV_RESULT  NAS_LMM_NvimRead
(
    NAS_LMM_ITEM_TYPE_ENUM_UINT32       ulNVItemType,
    VOS_VOID                           *pData,
    const VOS_UINT16                   *pusDataLen )
{
    VOS_UINT32                          ulRslt  = NAS_LMM_NVIM_FAIL;
    NAS_LMM_NV_ACTION_FUN               pActFun = NAS_LMM_NULL_PTR;
    NAS_NVIM_CTRL_TBL                   stNvCtrlTbl;
    VOS_UINT32                          i;

    /*check input params*/
    if((NAS_NVIM_NULL_PTR == pData)
        ||(NAS_NVIM_NULL_PTR == pusDataLen)
        ||(ulNVItemType > EN_NV_ID_PS_END))
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimRead :Input Para is error");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_NvimRead_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_NVIM_FAIL;
    }

    NAS_LMM_MEM_SET(g_aucNvimBuff, 0, sizeof(g_aucNvimBuff));

    /*Initalize NVIM ctrl tbl*/
    stNvCtrlTbl.pData        = pData;
    stNvCtrlTbl.pNvData      = g_aucNvimBuff;
    stNvCtrlTbl.usDataLen    = *pusDataLen;
    stNvCtrlTbl.usNvDataLen  = *pusDataLen;

    /* ��NV�ж�ȡ��Ϣ */
    /*lint -e718*/
    /*lint -e516*/
    /*lint -e732*/
    ulRslt = LPs_NvimItem_Read(ulNVItemType, stNvCtrlTbl.pNvData, stNvCtrlTbl.usNvDataLen);
    /*lint +e732*/
    /*lint +e516*/
    /*lint +e718*/
    if(ulRslt != EN_NV_OK)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimRead:PS_NVIM_Read is fail");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_NvimRead_ENUM
,LNAS_FAIL);
        return NAS_LMM_NVIM_FAIL;
    }

    /* ��g_astNvDataMap�в��Ҷ�Ӧ��NV TYPE, ����NV*/
    for(i = 0; i < g_ulNvDataMapNum; i++)
    {
        /* ��NV������ͬ,���ҵ���,���ص�ǰ��NV�����������˳�ѭ�� */
        if(ulNVItemType == g_astNvDataMap[i].ulEventType)
        {
           pActFun = g_astNvDataMap[i].pfDecodeActionFun;
           break;
        }
    }

    if (NAS_LMM_NULL_PTR != pActFun)
    {
        ulRslt = (*pActFun) (&stNvCtrlTbl);
        if(NAS_LMM_NVIM_OK == ulRslt)
        {
            return NAS_LMM_NVIM_OK;
        }
        else
        {
            return NAS_LMM_NVIM_FAIL;
        }
    }
    else /* ����Ҳ�������������ʾ��ǰû�иô����� */
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimRead:Action functin is ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_NvimRead_ENUM
,LNAS_ERROR);
        return NAS_LMM_NVIM_FAIL;
    }

}



VOS_VOID NAS_LMM_UsimFileWrite
(
    USIMM_DEF_FILEID_ENUM_UINT32        ulUsimFileId,
    VOS_VOID                           *pData,
    VOS_UINT16                          usDataLen
)
{
    VOS_UINT32                          ulRslt      = NAS_LMM_NVIM_FAIL;
    NAS_NVIM_CTRL_TBL                   stNvCtrlTbl;

    /*ucRecordNumĬ��Ϊ1��NASĿǰ�漰���ļ��������ļ�����ֻ��һ����¼*/
    VOS_UINT8                           ucRecordNum = 0x01;
    VOS_CHAR                           *cPathStr;
    VOS_UINT8                          *paucContent;
    USIMM_FILEPATH_INFO_STRU            stSetFilePath;

    /*check input params*/
    if((NAS_NVIM_NULL_PTR == pData)||(usDataLen == VOS_NULL))
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_UsimFileWrite:input para ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UsimFileWrite_ENUM
,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET(&stSetFilePath, 0, sizeof(USIMM_FILEPATH_INFO_STRU));

    /*Initalize NVIM ctrl tbl*/
    stNvCtrlTbl.pData       = pData;
    stNvCtrlTbl.pNvData     = g_aucNvimBuff;

    /* �ڲ����ݳ��Ȳ�ʹ�ã�дUSIMʹ�õ�ʵ�ʳ�����Encode��õ���usNvDataLen */
    stNvCtrlTbl.usDataLen   = usDataLen;
    stNvCtrlTbl.usNvDataLen = 0;

    NAS_LMM_NVIM_LOG1_INFO("NAS_LMM_UsimFileWrite: UsimFileId = ", ulUsimFileId);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_UsimFileWrite_ENUM
,LNAS_FUNCTION_LABEL1,ulUsimFileId);

    switch(ulUsimFileId)
    {
        case USIMM_USIM_EFEPSLOCI_ID :

            ulRslt = NAS_LMM_EncodeSimPsLoc(&stNvCtrlTbl);
            break;
        case USIMM_USIM_EFEPSNSC_ID  :

            ulRslt = NAS_LMM_EncodeSimSecContext(&stNvCtrlTbl);
            break;
        default:
            NAS_LMM_NVIM_LOG1_ERR("NAS_LMM_UsimFileWrite: UsimFileId err ID = ", ulUsimFileId);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_UsimFileWrite_ENUM
,LNAS_FUNCTION_LABEL2,ulUsimFileId);
            return;
    }

    if (NAS_LMM_NVIM_WRITTEN_UNNEEDED == ulRslt)
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_UsimFileWrite: code Don't need to write usim.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_UsimFileWrite_ENUM
,LNAS_FUNCTION_LABEL3);
        return;
    }

    if(ulRslt != NAS_LMM_NVIM_OK)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_UsimFileWrite:Encode is ERR");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UsimFileWrite_ENUM
,LNAS_FUNCTION_LABEL4);
        return;
    }

    /*��FileIDת��Ϊ�ļ�·��*/
    if (VOS_OK != USIMM_ChangeDefFileToPath(ulUsimFileId, &cPathStr))
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_NvimRead: ChangeDefFileToPath err.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UsimFileWrite_ENUM
,LNAS_FUNCTION_LABEL5);
        return;
    }
    stSetFilePath.ulPathLen = strlen(cPathStr);
    NAS_LMM_MEM_CPY(stSetFilePath.acPath, cPathStr, stSetFilePath.ulPathLen);

    paucContent = stNvCtrlTbl.pNvData;

    NAS_LMM_NVIM_LOG1_INFO("NAS_LMM_UsimFileWrite: usNvDataLen = ", stNvCtrlTbl.usNvDataLen);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_UsimFileWrite_ENUM
                                ,LNAS_FUNCTION_LABEL6,stNvCtrlTbl.usNvDataLen);

    NAS_LMM_SndUsimWriteFileReq(USIMM_GUTL_APP, ucRecordNum, 0, &stSetFilePath, stNvCtrlTbl.usNvDataLen, paucContent);

    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(), (VOS_UINT8*)stNvCtrlTbl.pNvData, stNvCtrlTbl.usNvDataLen);

    return;

}
VOS_VOID NAS_LMM_UsimFileRead
(
    USIMM_DEF_FILEID_ENUM_UINT32        ulUsimFileId
)
{
    USIMM_FILEPATH_INFO_STRU            stGetFilePath;
    VOS_CHAR                           *cPathStr;

    /*ucRecordNumĬ��Ϊ1��NASĿǰ�漰���ļ��������ļ�����ֻ��һ����¼*/
    VOS_UINT8                           ucRecordNum = 0x01;

    NAS_LMM_MEM_SET(&stGetFilePath, 0, sizeof(USIMM_FILEPATH_INFO_STRU));

    NAS_LMM_NVIM_LOG1_INFO("NAS_LMM_UsimFileRead: UsimFileId = ", ulUsimFileId);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_UsimFileRead_ENUM
,LNAS_FUNCTION_LABEL1,ulUsimFileId);

    switch(ulUsimFileId)
    {
        case USIMM_USIM_EFAD_ID      :
        case USIMM_USIM_EFACC_ID     :
        case USIMM_USIM_EFEPSLOCI_ID :
        case USIMM_USIM_EFEPSNSC_ID  :
            break;
        default:
            NAS_LMM_NVIM_LOG1_ERR("NAS_LMM_UsimFileRead: UsimFileId err ID = ", ulUsimFileId);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_UsimFileRead_ENUM
,LNAS_FUNCTION_LABEL2,ulUsimFileId);
            return;
    }

    /*��FileIDת��Ϊ�ļ�·��*/
    if (VOS_OK != USIMM_ChangeDefFileToPath(ulUsimFileId, &cPathStr))
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_UsimFileRead: ChangeDefFileToPath err.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UsimFileRead_ENUM
,LNAS_FUNCTION_LABEL3);
        return;
    }

    stGetFilePath.ulPathLen = strlen(cPathStr);
    NAS_LMM_MEM_CPY(stGetFilePath.acPath, cPathStr, stGetFilePath.ulPathLen);

    /*���Ͷ�USIM�ļ�����Ϣ*/
    NAS_LMM_SndUsimReadFileReq(USIMM_GUTL_APP, ucRecordNum, 0, &stGetFilePath);

    NAS_EMM_GET_SEND_COUNTER()++;

    return;
}
VOS_UINT32  NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf( MsgBlock  * pMsg)
{
    USIMM_READFILE_CNF_STRU          *pstUsimCnf = NAS_LMM_NULL_PTR;
    VOS_UINT32                          ulRst;

    NAS_LMM_PUBM_LOG2_INFO("NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf: g_ulSendMsgCounter = ,NAS_EMM_GET_USIM_FILE_TYPE=",
                                        NAS_EMM_GET_SEND_COUNTER(),
                                        NAS_EMM_GET_USIM_FILE_TYPE());
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf_ENUM
,LNAS_FUNCTION_LABEL1,
                                        NAS_EMM_GET_SEND_COUNTER(),
                                        NAS_EMM_GET_USIM_FILE_TYPE());

    /* ״̬ƥ����,����ƥ��,�˳� */
    if (NAS_EMM_PLMN_CHK_STAT_INVALID(EMM_MS_NULL, EMM_SS_NULL_WAIT_READING_USIM))
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf: STATE ERR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf_ENUM
,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_DISCARD;
    }

    /*�յ������*//*��ȫ�ֱ������б������Է����ָ���*/
    if (NAS_NVIM_SEND_COUNTER_NONE == NAS_EMM_GET_SEND_COUNTER())
    {
        NAS_LMM_EMM_PLMN_LOG_WARN("NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf: Receive USIM cnf when Counter is 0!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf_ENUM
,LNAS_FUNCTION_LABEL3);
        return NAS_LMM_MSG_DISCARD;
    }
    else
    {
        NAS_EMM_GET_SEND_COUNTER() --;
    }

    pstUsimCnf = (USIMM_READFILE_CNF_STRU*)pMsg;


    NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf:===>",pstUsimCnf->stCmdResult.ulResult);
    TLPS_PRINT2LAYER_WARNING1(NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf_ENUM
,LNAS_FUNCTION_LABEL4,pstUsimCnf->stCmdResult.ulResult);

    /*����ʧ��*/
    if (VOS_OK != pstUsimCnf->stCmdResult.ulResult)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf: Read file err !");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf_ENUM
,LNAS_FUNCTION_LABEL5);


        if( NAS_NVIM_SEND_COUNTER_NONE == NAS_EMM_GET_SEND_COUNTER() )
        {/*��ѡ���һ���ļ���ȡʧ�ܣ����ж�NV��ת״̬�Ķ���*/

            NAS_LMM_DoAfterReadOptFileOver();
        }

        return NAS_LMM_MSG_HANDLED;
    }

    /* ���ļ����д��� */
    ulRst = NAS_LMM_ProcessHardUsimCnf(pstUsimCnf);
    if(NAS_LMM_NVIM_OK != ulRst)
    {
        NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf : Decode USIM MSG err: ",
                                ulRst);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_MsNullSsNullReadingUsimMsgUsimCnf_ENUM
,LNAS_FUNCTION_LABEL6,ulRst);
    }

    if( NAS_NVIM_SEND_COUNTER_NONE == NAS_EMM_GET_SEND_COUNTER())
    {   /* ����ض����ѡ�ļ� */

        NAS_LMM_DoAfterReadOptFileOver();
    }

    /* û�ж��꣬������ȴ�������Ӧ��Ϣ */

    return NAS_LMM_MSG_HANDLED;
}
VOS_VOID  NAS_LMM_DoAfterReadOptFileOver( VOS_VOID )
{
    NAS_LMM_FSM_STATE_STRU               EmmState;
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeMode;

    NAS_LMM_UEID_STRU                    *pstUeId;


    /* ֹͣTI_NAS_LMM_TIMER_WAIT_USIM_CNF */
    NAS_LMM_StopStateTimer(TI_NAS_LMM_TIMER_WAIT_USIM_CNF);
    /*�����ȡ����GUTI��Ч���ǰ�ȫ��������Ч����ɾ�����غ�NV�е�������*/
    pstUeId                             = NAS_LMM_GetEmmInfoUeidAddr();

    if((NAS_EMM_BIT_NO_SLCT == pstUeId->bitOpGuti)
        &&(EMM_CUR_SECU_NOT_EXIST!= NAS_LMM_GetSecuCurFsmCS()))
    {
        NAS_EMM_ClearCurSecuCntxt();
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);
    }

    /* Read NV Files*/
    NAS_LMM_ProcessNvData();

    /* ״̬ת�ɶ���ѡ�ļ�״̬ */
    /* V7�������ֱض���ѡ */
    /*NAS_EMM_GET_USIM_FILE_TYPE() = NAS_LMM_USIM_MANDATORY_FILE;*/
    /*PC REPLAY MODIFY BY LEILI END*/
    ulLteUeMode = NAS_LMM_ComputeLteUeMode( NAS_EMM_GetMsMode(),
                                          NAS_LMM_GetEmmInfoUeCenter());
    NAS_LMM_SetEmmInfoUeOperationMode(ulLteUeMode);
    /*PC REPLAY MODIFY BY LEILI END*/
    /* ����TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER */
    NAS_LMM_StartStateTimer(TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER);

    /* ת״̬ */
    EmmState.enFsmId             = NAS_LMM_PARALLEL_FSM_EMM;
    EmmState.enMainState         = EMM_MS_NULL;
    EmmState.enSubState          = EMM_SS_NULL_WAIT_MMC_START_CNF;
    EmmState.enStaTId            = TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER;
    NAS_LMM_StaTransProc(EmmState);

    /* ��MMC����MMC_EMM_START_REQ(��������)��Ϣ */
    (VOS_VOID)NAS_EMM_PLMN_SendMmcStartReq(EMMC_EMM_START_REQ_CAUSE_NORMAL_START);

    return;
}
VOS_VOID  NAS_LMM_ProcessNvData( VOS_VOID )
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_ProcessNvData is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ProcessNvData_ENUM
,LNAS_ENTRY);

    /*��ʼ��EMMȫ�ֱ���ReadNV*/
    NAS_EMM_ReadEmmNvim();

    return;
}


VOS_UINT32  NAS_LMM_ProcessHardUsimCnf(USIMM_READFILE_CNF_STRU* pstUsimFileCnf)
{
    VOS_UINT32                          ulRslt      = NAS_LMM_NVIM_FAIL;
    NAS_NVIM_CTRL_TBL                   stNvCtrlTbl;
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileID = 0;

    /*Initalize NVIM ctrl tbl*/
    stNvCtrlTbl.pNvData     = pstUsimFileCnf->aucEf;
    stNvCtrlTbl.usNvDataLen = pstUsimFileCnf->usEfLen;

    /* ����USIM�ṩ�Ľӿڣ����ļ�·��ת��ΪFileID */
    if(VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pstUsimFileCnf->stFilePath.ulPathLen,
                                        pstUsimFileCnf->stFilePath.acPath, &enDefFileID))
    {
        /* ���ת��ʧ�ܣ���ʾû�ж�Ӧ��FileID */
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_ProcessHardUsimCnf: USIMM_ChangePathToDefFileID err");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ProcessHardUsimCnf_ENUM
,LNAS_FUNCTION_LABEL1);
        return VOS_ERR;
    }

    NAS_LMM_PUBM_LOG2_INFO("NAS_LMM_ProcessHardUsimCnf:pstUsimCnf->usEfId=,pstUsimCnf->ucEfLen",
                                        enDefFileID,
                                        pstUsimFileCnf->usEfLen);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_ProcessHardUsimCnf_ENUM
,LNAS_FUNCTION_LABEL2,
                                        enDefFileID,
                                        pstUsimFileCnf->usEfLen);
    switch(enDefFileID)
    {
        case USIMM_USIM_EFIMSI_ID    :

            ulRslt = NAS_LMM_DecodeSimImsi(&stNvCtrlTbl);
            break;
        case USIMM_USIM_EFAD_ID      :

            ulRslt = NAS_LMM_DecodeSimMncLen(&stNvCtrlTbl);
            break;
        case USIMM_USIM_EFACC_ID     :

            ulRslt = NAS_LMM_DecodeNvACC(&stNvCtrlTbl);
            break;
        case USIMM_USIM_EFEPSLOCI_ID :

            ulRslt = NAS_LMM_DecodeSimPsLoc(&stNvCtrlTbl);
            break;
        case USIMM_USIM_EFEPSNSC_ID  :

            ulRslt = NAS_LMM_DecodeSimSecContext(&stNvCtrlTbl);
            break;
        default:

            NAS_LMM_NVIM_LOG1_ERR("NAS_LMM_ProcessHardUsimCnf: UsimFileId err ID = ", enDefFileID);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_ProcessHardUsimCnf_ENUM
,LNAS_FUNCTION_LABEL3,enDefFileID);
            return NAS_LMM_NVIM_FAIL;
    }

    if(NAS_LMM_NVIM_OK != ulRslt)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_ProcessHardUsimCnf: UsimFileId decode err.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_ProcessHardUsimCnf_ENUM
,LNAS_FUNCTION_LABEL4);
    }

    return ulRslt;

}
NAS_LMM_USIM_READ_RST_ENUM_UINT32  NAS_LMM_ReadUsimFileImsi(VOS_VOID)
{
    VOS_UINT32                          ulRst;
    USIMM_READFILE_CNF_STRU            *pstUsimCnfMsg;
    VOS_CHAR                           *pcPathStr;

    pstUsimCnfMsg = (USIMM_READFILE_CNF_STRU *)(g_aucNvimBuff);

    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /* 6F07    MMC_READ_IMSI_FILE_ID ��USIM���ṩ�Ľӿں��� */
    ulRst = NAS_EMM_GetCardIMSI((VOS_UINT8 *)(pstUsimCnfMsg->aucEf));
    /*PC REPLAY MODIFY BY LEILI END*/
    if(USIMM_API_SUCCESS != ulRst)
    {
        NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_LMM_ReadMmcUsimFile : read IMSI err: ",
                                  ulRst);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_ReadUsimFileImsi_ENUM
,LNAS_FUNCTION_LABEL1,ulRst);
        return  NAS_LMM_USIM_READ_HARD_IMSI_ERR;
    }
    else
    {
        /* ��ӡ��USIM������ԭʼ���� */
        NAS_LMM_PUBM_LOG_NORM("\n");
        NAS_LMM_PUBM_LOG_NORM("====== USIMM_GetCardIMSI: IMSI:  ======");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadUsimFileImsi_ENUM
,LNAS_FUNCTION_LABEL2);
        NAS_COMM_PrintArray(             NAS_COMM_GET_MM_PRINT_BUF(),
                                         pstUsimCnfMsg->aucEf,
                                         NAS_LMM_NVIM_IMSI_FILE_LEN);
        NAS_LMM_PUBM_LOG_NORM("\n");

        /*zhaochen 00308719 begin for USIM Interface*/
        /*��FileIDת��Ϊ�ļ�·��*/
        if (VOS_OK != USIMM_ChangeDefFileToPath(USIMM_USIM_EFIMSI_ID, &pcPathStr))
        {
            NAS_LMM_NVIM_LOG_ERR("NAS_LMM_ReadMmcUsimFile: ChangeDefFileToPath err.");
            TLPS_PRINT2LAYER_ERROR(NAS_LMM_ReadUsimFileImsi_ENUM
,LNAS_FUNCTION_LABEL3);
            return NAS_LMM_USIM_READ_HARD_IMSI_ERR;
        }

        pstUsimCnfMsg->stFilePath.ulPathLen = strlen(pcPathStr);
        NAS_LMM_MEM_CPY(pstUsimCnfMsg->stFilePath.acPath, pcPathStr, pstUsimCnfMsg->stFilePath.ulPathLen);
        /*zhaochen 00308719 end for USIM Interface*/

        /* ׼��һ�� NAS_LMM_ProcessHardUsimCnf ����ڲ��� */
        pstUsimCnfMsg->usEfLen     = NAS_LMM_NVIM_IMSI_FILE_LEN;
        pstUsimCnfMsg->ucRecordNum = 0;
        pstUsimCnfMsg->ucTotalNum  = 0;

        /* ���� */
        ulRst = NAS_LMM_ProcessHardUsimCnf(pstUsimCnfMsg);
        if(NAS_LMM_NVIM_OK != ulRst)
        {
            NAS_LMM_EMM_PLMN_LOG1_ERR("NAS_LMM_ReadMmcUsimFile : Decode IMSI err: ", ulRst);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_ReadUsimFileImsi_ENUM
,LNAS_FUNCTION_LABEL4,ulRst);
            return  NAS_LMM_USIM_READ_HARD_IMSI_ERR;
        }
    }

    return  NAS_LMM_USIM_READ_SUCC;
}
VOS_VOID  NAS_LMM_ReadLteUsimFile(VOS_VOID)
{
    /*6F78 */
    NAS_EMM_ReadAccClassMask();

    /*6FE3 ��ȫ�����ĺ� PS_LOC*/
    NAS_LMM_ReadUsimEmmInfoFile();
    /*6FAD MNC����*/
    NAS_LMM_ReadSimMncLen();
    return;
}

/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif


