/******************************************************************************
        @(#)Copyright(C)2008,Hisilicon Co. LTD.
 ******************************************************************************
    File name   : NasEmmGuti.c
    Description : ���ļ�������GUTIģ��Ĵ�������
    History     :
      1.  zangyalan 57968  2008-09-09  Draft Enact
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmGuti.h"
#include "NasEmmAttDetInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMGUTI_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMGUTI_C
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


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_EMM_GutiInit
 Discription    : GUTIģ���ʼ������
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968 2008-10-16  Draft Enact
      2.  hanlufeng 41410 2009-05-12  ��ʼ�����ٸ�ȱʡֵ��
*****************************************************************************/
VOS_VOID NAS_EMM_GutiInit(VOS_VOID)
{
    /*GUTIĿǰû����Ҫ��ʼ������Ϣ,��ʱΪ��*/
    return;
}
VOS_VOID  NAS_EMM_FreeGutiDyn( VOS_VOID )
{
    /*GUTI��ʱΪ��*/
    return;
}



/*****************************************************************************
 Function Name  : Nas_Emm_TaiListSet
 Discription    : ����TAI�б�
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-09  Draft Enact
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMM_TaiListSet(const NAS_EMM_TA_LIST_STRU *pstTaiList)
{

    /*���TaiList�Ϸ���      */
    if ( NAS_EMM_NULL_PTR == pstTaiList)
    {
        NAS_EMM_GUTI_ERROR_LOG("NAS_EMM_TaiListSet:Input TaiList is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TaiListSet_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_FAIL;
    }

    /*�Ѿ�TaiList��0*/
    NAS_LMM_MEM_SET(&NAS_EMM_TAI_LIST, 0, sizeof(NAS_EMM_TA_LIST_STRU));

    /* ����TaiList��ȫ�ֱ��� */
    NAS_LMM_MEM_CPY(&NAS_EMM_TAI_LIST, pstTaiList, sizeof(NAS_EMM_TA_LIST_STRU));
    g_stEmmInfo.stNetInfo.bitOpTaiList = NAS_EMM_BIT_SLCT;

    /* �Ѹ��µ�ȫ�ֱ���TAI Listд��NVIM */
    /*NAS_LMM_WriteNvTaList();*/

    return NAS_LMM_SUCC;
}

/*****************************************************************************
 Function Name  : Nas_Emm_CompCnGutiCmp
 Discription    : ����GUTI REALLOCATION COMPLETE��CN��Ϣ
 Input          : ��Ϣ
 Output         : pNasMsg
 Return         : None
 History:
      1.  zangyalan  2008-09-18  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_EMM_CompCnGutiCmp(LRRC_LNAS_MSG_STRU  *pNasMsg)
{

    /* ���CN��Ϣ�����ֶ�,�� NasMsg����*/
    pNasMsg->ulNasMsgSize = NAS_GUTI_COMP_NAS_MSG_LEN;

    /* ��ս����CN��Ϣ�Ŀռ� */
    NAS_LMM_MEM_SET(pNasMsg->aucNasMsg, 0, pNasMsg->ulNasMsgSize);

    /* ��� Protocol Discriminator */
    pNasMsg->aucNasMsg[0]  = EMM_CN_MSG_PD_EMM;

    /*��� Security header type*/
    pNasMsg->aucNasMsg[0] |= NAS_EMM_CN_MSG_SE_EMM;

    /* ��� Guti reallocation complete message identity   */
    pNasMsg->aucNasMsg[1]  = NAS_EMM_CN_MT_GUTI_CMP;

    return;
}


/*****************************************************************************
 Function Name  : Nas_Emm_MrrcDataReq
 Discription    : ����MRRC_DATA_REQ����������Ϣ����mrrcģ��ת��
 Input          : GUTI
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-09  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_GutiMrrcDataReq(VOS_VOID)
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pstMrrcDataReqMsg = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulLen;


    /*����ռ�,�ڲ���Ϣ��Ӧ�÷���ռ�,��Ӧ��ȡ��ַ��ʽ*/
    /*��ȡ�ڲ���Ϣ��ַ*/
    pstMrrcDataReqMsg =(NAS_EMM_MRRC_DATA_REQ_STRU *) NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    if(NAS_EMM_NULL_PTR == pstMrrcDataReqMsg)
    {
        return NAS_EMM_ERR;
    }

     /* ���CN��Ϣ    */
    NAS_EMM_CompCnGutiCmp( &(pstMrrcDataReqMsg->stNasMsg));

    ulLen  = NAS_EMM_CountMrrcDataReqLen(pstMrrcDataReqMsg->stNasMsg.ulNasMsgSize);

    /*���VOS��Ϣͷ,NAS_EMM_MRRC_DATA_REQ_STRU */
    NAS_EMM_INTRA_MSG_HEADER(pstMrrcDataReqMsg, ulLen);

    /*�����ϢID    */
    pstMrrcDataReqMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    pstMrrcDataReqMsg->enDataCnf        = LRRC_LMM_DATA_CNF_NEED;

    /*�����Ϣ����*/
    pstMrrcDataReqMsg->enEstCaue        = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
     pstMrrcDataReqMsg->enCallType      = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pstMrrcDataReqMsg->enEmmMsgType     = NAS_EMM_MSG_GUTI_CMP;

    /*�տ���Ϣ�ϱ�GUTI REALLOCATION COMPLETE*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_GUTI_CMP,  (NAS_MSG_STRU*)&(pstMrrcDataReqMsg->stNasMsg));

    /*�ؼ��¼��ϱ�GUTI REALLOCATION COMPLETE*/
    NAS_LMM_SendOmtKeyEvent(         EMM_OMT_KE_GUTI_CMP);

    /*�����ڲ���ϢMRRC_DATA_REQ*/
    NAS_EMM_SndUplinkNasMsg(            pstMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pstMrrcDataReqMsg);

    return NAS_EMM_OK;
}
VOS_UINT32 NAS_EMM_AnyStateMsgGtReCmd(VOS_UINT32  ulMsgId,
                                      VOS_VOID  *pMsgStru)
{
    NAS_EMM_GUTI_REALLOCATION_CMD_STRU *pstGutiCmdMsg = NAS_EMM_NULL_PTR;
    NAS_EMM_GUTI_STRU                  *pstGuti;
    VOS_UINT32                          ulRst;

    (VOS_VOID)ulMsgId;

    /*������Ϣ����ȡ���෢����GUTI*/
    pstGutiCmdMsg = (NAS_EMM_GUTI_REALLOCATION_CMD_STRU *)pMsgStru;
    pstGuti       = (NAS_EMM_GUTI_STRU *) &pstGutiCmdMsg->stGuti;

    /*����ȫ�ֱ���GUTI*/
    NAS_LMM_MEM_CPY(                NAS_LMM_GetEmmInfoUeidGutiAddr(),
                                        pstGuti,
                                        sizeof(NAS_LMM_GUTI_STRU));
    NAS_LMM_GetEmmInfoUeidAddr()->bitOpGuti = NAS_EMM_BIT_SLCT;
    /*���������Tai List,�洢����Tai List */
    if(VOS_TRUE == pstGutiCmdMsg->ucBitOpTaiList)
    {
        if(NAS_LMM_SUCC == NAS_EMM_TaiListSet(&pstGutiCmdMsg->stTaiList))
        {
            NAS_EMM_GUTI_NORMAL_LOG("NAS_EMM_AnyStateMsgGtReCmd: TaiList update is success!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_AnyStateMsgGtReCmd_ENUM,LNAS_SUCC);

            /*�����µ�TAI List��ͬʱ����ForbTA for Roaming��ForbTA for RPOS*/
            NAS_EMMC_UpdateForbTaList();
        }
        else
        {
            NAS_EMM_GUTI_ERROR_LOG("NAS_EMM_AnyStateMsgGtReCmd: TaiList update is fail!");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_AnyStateMsgGtReCmd_ENUM,LNAS_FAIL);
        }
    }

    /* �ж�û�зŵ�����NAS_LMM_WritePsLoc�������������ڽ���ע�ᱻ�ܻ��߳���
       �����ﵽ5��ʱ����Ҫɾ������ ��Э��ֻ�涨�ǽ���ע��ɹ���Ų�д������
       NV�� */
    if ((NAS_LMM_REG_STATUS_EMC_REGING != NAS_LMM_GetEmmInfoRegStatus())
        && (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus()))
    {
        /*����PS LOC��Ϣ*/ /*�洢����guti��last Ta,update state */
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }

    /*�����ڲ���ϢMRRC_DATA_REQ,Я��GUTI REALLOCAITON CMPL*/
    ulRst = NAS_EMM_GutiMrrcDataReq();
    if(NAS_EMM_OK != ulRst)
    {
        NAS_EMM_GUTI_ERROR_LOG("NAS_EMM_AnyStateMsgGtReCmd: NAS_EMM_GutiMrrcDataReq err!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AnyStateMsgGtReCmd_ENUM,LNAS_ERROR);
    }

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e961*/
/*lint +e960*/


VOS_UINT32  NAS_EMM_CheckSimGutiValid( const VOS_UINT8 *pucSimRecord,
                                                  const VOS_UINT32 ulIndex,
                                                  const VOS_UINT32 ulLen )
{
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_LMM_CheckWhetherAllBytesAreFF( pucSimRecord, ulIndex, ulLen );

    if ( VOS_FALSE == ulRslt)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}


/****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of NasEmmGuti.c */
