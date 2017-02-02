


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmBackOffAlgMain.h"
#include    "NasEmmPubUGlobal.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMBACKOFFALGMAIN_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMBACKOFFALGMAIN_C
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


NAS_BACKOFF_ALGORITHM_ENTITY_STRU  g_stBackOffEntity;


/*****************************************************************************
  3 Function
*****************************************************************************/


VOS_VOID NAS_BACKOFF_OperateInit
(
    NAS_BACKOFF_INIT_INFO_STRU            *pstInitPara
)
{
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara;

    NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateInit Enter");
    TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateInit_ENUM, LNAS_ENTRY);

    pstOpPara = (NAS_BACKOFF_OPERATE_PARA_STRU*)pstInitPara;

    (VOS_VOID)NAS_BACKOFF_MainTaskEntry(NAS_BACKOFF_NETRAT_LTE, NAS_BACKOFF_OPERATE_TYPE_INIT, pstOpPara);

    return;
}


VOS_UINT32 NAS_BACKOFF_OperateJudgment
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_JUDGMENT_PARA_STRU    *pstJudgmentPara
)
{
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara;

    NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateJudgment Enter");
    TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateJudgment_ENUM, LNAS_ENTRY);

    pstOpPara = (NAS_BACKOFF_OPERATE_PARA_STRU*)pstJudgmentPara;

    /* ������DAM����������NV����Ҳû�򿪣���ʹ��Back-off�㷨 */
    if((NAS_ESM_YES != NAS_EMM_IsDamConfitionSatisfied())
        &&(NAS_BACKOFF_ALG_VALID != g_stBackOffEntity.ucBackOffAlgFlag))
    {
        NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateJudgment Backoff close");
        TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateJudgment_ENUM, ESM_BACKOFF_CLOSE);
        return NAS_BACKOFF_SUCC;
    }

    /* �����USIM����ʱ�������У�˵����δ���꣬��ʹ��Back-off�㷨 */
    if(PS_FALSE != NAS_ESM_IsWaitBackOffUsimCnfTimerRunning())
    {
        NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateJudgment wait Usim Cnf");
        TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateJudgment_ENUM, ESM_WAIT_USIM_CNF);
        return NAS_BACKOFF_SUCC;
    }

    /* ����DAM������NV���ش� */
    return NAS_BACKOFF_MainTaskEntry(enNetRat, NAS_BACKOFF_OPERATE_TYPE_JUDGMENT, pstOpPara);
}
VOS_VOID NAS_BACKOFF_OperateMaintain
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
)
{
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara;

    NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateMaintain Enter");
    TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateMaintain_ENUM, LNAS_ENTRY);

    pstOpPara = (NAS_BACKOFF_OPERATE_PARA_STRU*)pstMaintainPara;

    /* ������DAM����������NV����Ҳû�򿪣���ʹ��Back-off�㷨 */
    if((NAS_ESM_YES != NAS_EMM_IsDamConfitionSatisfied())
        &&(NAS_BACKOFF_ALG_VALID != g_stBackOffEntity.ucBackOffAlgFlag))
    {
        NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateMaintain Backoff close");
        TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateMaintain_ENUM, ESM_BACKOFF_CLOSE);
        return;
    }

    /* �����USIM����ʱ�������У�˵����δ���꣬��ʹ��Back-off�㷨 */
    if(PS_FALSE != NAS_ESM_IsWaitBackOffUsimCnfTimerRunning())
    {
        NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateMaintain wait Usim Cnf");
        TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateMaintain_ENUM, ESM_WAIT_USIM_CNF);
        return;
    }

    /* ����DAM������NV���ش� */
    (VOS_VOID)NAS_BACKOFF_MainTaskEntry(enNetRat, NAS_BACKOFF_OPERATE_TYPE_MAINTAIN, pstOpPara);

    return;
}
VOS_VOID NAS_BACKOFF_OperateReset
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32        enNetRat,
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  *penResetCause
)
{
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara;

    NAS_BACKOFF_INFO_LOG("NAS_BACKOFF_OperateReset Enter");
    TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_OperateReset_ENUM, LNAS_ENTRY);

    pstOpPara = (NAS_BACKOFF_OPERATE_PARA_STRU*)penResetCause;

    (VOS_VOID)NAS_BACKOFF_MainTaskEntry(enNetRat, NAS_BACKOFF_OPERATE_TYPE_RESET, pstOpPara);

    return;
}


VOS_UINT8* NAS_BACKOFF_GetAlgFlagAddr(VOS_VOID)
{
    return &g_stBackOffEntity.ucBackOffAlgFlag;
}


NAS_BACKOFF_APN_ENTITY_STRU* NAS_BACKOFF_GetApnEntityAddr
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32  enNetRat,
    VOS_UINT32                      ulIndex
)
{
    return &g_stBackOffEntity.stNetRatEntity[enNetRat].stApnEntity[ulIndex];
}


NAS_BACKOFF_COMM_PARA_STRU* NAS_BACKOFF_GetCommParaAddr(VOS_VOID)
{
    return &g_stBackOffEntity.stCommPara;
}


NAS_CONFIG_PDP_PERM_CAUSE_STRU* NAS_BACKOFF_GetPdpPermCauseListAddr(VOS_VOID)
{
    return &g_stBackOffEntity.stPdpPermCause;
}


NAS_CONFIG_PDP_TEMP_CAUSE_STRU* NAS_BACKOFF_GetPdpTempCauseListAddr(VOS_VOID)
{
    return &g_stBackOffEntity.stPdpTempCause;
}


VOS_VOID NAS_BACKOFF_SetBackOffState
(
    NAS_BACKOFF_STATE_ENUM_UINT8     enDestState,
    NAS_BACKOFF_APN_ENTITY_STRU     *pstApnEntity
)
{
    pstApnEntity->enState = enDestState;
    return ;
}


VOS_UINT32 NAS_BACKOFF_MainTaskEntry
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32             enNetRat,
    NAS_BACKOFF_OPERATE_TYPE_ENUM_UINT32       enOpType,
    NAS_BACKOFF_OPERATE_PARA_STRU             *pstOpPara
)
{
    VOS_UINT32                          ulRslt  = NAS_BACKOFF_FAIL;
    VOS_UINT8                           ulIndex = 0;

    /* �������Ϳ�ά�ɲ���Ϣ�����HIDS��������ʼ�����ж���ά���͸�λ */
    NAS_BACKOFF_SndOmLogOperateInfo(enNetRat, enOpType, pstOpPara);

    switch(enOpType)
    {
        case NAS_BACKOFF_OPERATE_TYPE_INIT:

            /* ��ά�ɲ⣬�����ʼ��֮ǰ�㷨����������HIDS */
            NAS_BACKOFF_SndOmLogCommInfo();

            NAS_BACKOFF_Init(&pstOpPara->u.stInitPara);

            /* ��ά�ɲ⣬�����ʼ��֮���㷨����������HIDS */
            NAS_BACKOFF_SndOmLogCommInfo();
            ulRslt = NAS_BACKOFF_SUCC;
            break;

        case NAS_BACKOFF_OPERATE_TYPE_JUDGMENT:

            /* ��ά�ɲ⣬����ж�֮ǰ�㷨����������APNʵ���б�HIDS */
            NAS_BACKOFF_SndOmLogCommInfo();
            NAS_BACKOFF_SndOmLogApnEntityList(enNetRat);
            ulRslt = NAS_BACKOFF_Judgment(enNetRat, &pstOpPara->u.stJudgmentPara);
            break;

        case NAS_BACKOFF_OPERATE_TYPE_MAINTAIN:

            /* ��ά�ɲ⣬���ά��֮ǰ�㷨����������APNʵ���б�HIDS */
            NAS_BACKOFF_SndOmLogCommInfo();
            NAS_BACKOFF_SndOmLogApnEntityList(enNetRat);

            NAS_BACKOFF_Maintain(enNetRat, &pstOpPara->u.stMaintainPara);

            /* ��ά�ɲ⣬���ά��֮��APNʵ���б�HIDS */
            NAS_BACKOFF_SndOmLogApnEntityList(enNetRat);
            ulRslt = NAS_BACKOFF_SUCC;
            break;

        case NAS_BACKOFF_OPERATE_TYPE_RESET:

            NAS_BACKOFF_Reset(enNetRat, &pstOpPara->u.enResetCause);

            /* ��ά�ɲ⣬�����λ֮�󹫹����������н��뼼�����㷨ʵ��״̬��HIDS */
            NAS_BACKOFF_SndOmLogCommInfo();
            for(ulIndex = 0; ulIndex < NAS_BACKOFF_NETRAT_ENUM_BUTT; ulIndex++)
            {
                NAS_BACKOFF_SndOmLogApnEntityList(ulIndex);
            }
            ulRslt = NAS_BACKOFF_SUCC;
            break;

        default:

            NAS_ESM_INFO_LOG("NAS_BACKOFF_MainTaskEntry:Operate type ERR!");
            TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_MainTaskEntry_ENUM, LNAS_PARAM_INVALID);
            ulRslt = NAS_BACKOFF_FAIL;
    }

    return ulRslt;

}
VOS_VOID NAS_BACKOFF_Init
(
    NAS_BACKOFF_INIT_INFO_STRU  *pstInitInfo
)
{
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU   stNvDamPara;
    VOS_UINT8                             *pstBackOffAlgFlag = NAS_BACKOFF_NULL_PTR;
    NAS_BACKOFF_COMM_PARA_STRU            *pstCommPara       = NAS_BACKOFF_NULL_PTR;

    NAS_ESM_MEM_SET(&stNvDamPara, 0, sizeof(LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU));

    NAS_ESM_MEM_SET(&g_stBackOffEntity, 0, sizeof(NAS_BACKOFF_ALGORITHM_ENTITY_STRU));

    pstBackOffAlgFlag = NAS_BACKOFF_GetAlgFlagAddr();
    pstCommPara       = NAS_BACKOFF_GetCommParaAddr();

    if(NAS_BACKOFF_NVIM_SUCC != NAS_BACKOFF_ReadNvDamBackOffPara(&stNvDamPara))
    {
        /* ��NVʧ�ܣ�����NV�ж�ȡ��������ȫΪ0��������ʼ����Ĭ��ֵ����ʱֻ��DAM��Чʱ����ʹ���㷨 */
        NAS_ESM_MEM_SET(&stNvDamPara, 0, sizeof(LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU));
    }

    /* ���NV������HIDS�����ڿ�ά�ɲ� */
    NAS_BACKOFF_SndOmLogNvPara(&stNvDamPara);

    NAS_BACKOFF_InitPdpRejCauseList(&stNvDamPara);

    NAS_BACKOFF_InitCommParaFx(&stNvDamPara, pstInitInfo);

    NAS_BACKOFF_InitCommParaFb(pstCommPara);

    /* ��ʼ���ͷ���ʱ�������� */
    NAS_BACKOFF_InitCommParaTimerPara(pstCommPara);

    /* Back-off�㷨��NV��δ�� */
    if(NAS_BACKOFF_BIT_NO_SILT == stNvDamPara.bitOpBackOffAlg)
    {
        *pstBackOffAlgFlag = NAS_BACKOFF_ALG_INVALID;
    }
    else
    {
        /* �㷨�� */
        *pstBackOffAlgFlag = NAS_BACKOFF_ALG_VALID;
    }

    return;

}
VOS_UINT32 NAS_BACKOFF_Judgment
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_JUDGMENT_PARA_STRU    *pstJudgmentPara
)
{
    NAS_BACKOFF_QUERY_RESULT_STRU  stQueryResult;

    NAS_ESM_MEM_SET(&stQueryResult, 0 , sizeof(NAS_BACKOFF_QUERY_RESULT_STRU));

    /* ���ҷ���APN��Ӧ��ʵ�岻���ڣ������� */
    if(NAS_BACKOFF_SUCC != NAS_BACKOFF_QueryInfo(enNetRat, pstJudgmentPara, &stQueryResult))
    {
        return NAS_BACKOFF_SUCC;
    }

    /* ʵ����ڵ��㷨����δ����̬�������� */
    if(NAS_BACKOFF_STATE_INACTIVE == stQueryResult.enState)
    {
        return NAS_BACKOFF_SUCC;
    }

    /* ʵ������㷨���ڼ���̬���ͷ���ʱ��δ���У������� */
    if(NAS_BACKOFF_FOBID_TIMER_STATE_STOP == stQueryResult.enTimeStatus)
    {
        return NAS_BACKOFF_SUCC;
    }

    return NAS_BACKOFF_FAIL;

}
VOS_VOID NAS_BACKOFF_Maintain
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
)
{
    /* PDP�������Ƿ� */
    if(NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM_BUTT <= pstMaintainPara->enPdpResult)
    {
        return;
    }

    if(NAS_BACKOFF_PDP_ACTIVE_RESULT_SUCC == pstMaintainPara->enPdpResult)
    {
        NAS_BACKOFF_PdpActiveSuccProc(enNetRat, pstMaintainPara);
        return;
    }

    /* ʧ��ԭ��ֵ����Ҫά��ֱ�ӷ��أ���Ҫά��ִ��PDPʧ�ܵ���Ӧ��������ʱ����ЧCN REJԭ��ֵʱ��ά�� */
    if((NAS_BACKOFF_PDP_ACTIVE_RESULT_TIMER_EXP == pstMaintainPara->enPdpResult)
        ||((NAS_BACKOFF_PDP_ACTIVE_RESULT_CN_REJ == pstMaintainPara->enPdpResult)
            &&(NAS_BACKOFF_PDP_REJ_TYPE_OTHER != NAS_BACKOFF_GetPdpCnRejType(pstMaintainPara->ucCnCause))))
    {
        NAS_BACKOFF_PdpActiveFailProc(enNetRat, pstMaintainPara);
    }

    return;
}

VOS_VOID NAS_BACKOFF_Reset
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32        enNetRat,
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  *penResetCause
)
{
    VOS_UINT32                           ulIndex           = 0;
    VOS_UINT32                           ulNetRat          = 0;
    NAS_BACKOFF_COMM_PARA_STRU          *pstCommPara       = NAS_BACKOFF_NULL_PTR;
    VOS_UINT8                           *pstBackOffAlgFlag = NAS_BACKOFF_NULL_PTR;
    NAS_CONFIG_PDP_PERM_CAUSE_STRU       *pstPdpPermCauseList = NAS_BACKOFF_NULL_PTR;
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU       *pstPdpTempCauseList = NAS_BACKOFF_NULL_PTR;

    /* ��λԭ����� */
    if(NAS_BACKOFF_RESET_CAUSE_ENUM_BUTT <= *penResetCause)
    {
        return;
    }

    /* PLMN�ı䣬��յ�ǰ���뼼���µ�����APNʵ�� */
    if(NAS_BACKOFF_RESET_CAUSE_PLMN_CHANGE == *penResetCause)
    {
        for(ulIndex = 0; ulIndex < NAS_BACKOFF_APN_ENTITY_MAX_NUM; ulIndex++)
        {
            NAS_BACKOFF_ClearApnEntity(enNetRat, ulIndex);
        }
    }
    else
    {
        /* �ػ� */
        pstBackOffAlgFlag   = NAS_BACKOFF_GetAlgFlagAddr();
        pstCommPara         = NAS_BACKOFF_GetCommParaAddr();
        pstPdpPermCauseList = NAS_BACKOFF_GetPdpPermCauseListAddr();
        pstPdpTempCauseList = NAS_BACKOFF_GetPdpTempCauseListAddr();

        /* �ر��㷨 */
        *pstBackOffAlgFlag  = NAS_BACKOFF_ALG_INVALID;

        /* ����㷨�������� */
        NAS_ESM_MEM_SET(pstCommPara, 0, sizeof(NAS_BACKOFF_COMM_PARA_STRU));

        /* ��վܾ�ԭ��ֵ�б� */
        NAS_ESM_MEM_SET(pstPdpPermCauseList, 0, sizeof(NAS_CONFIG_PDP_PERM_CAUSE_STRU));
        NAS_ESM_MEM_SET(pstPdpTempCauseList, 0, sizeof(NAS_CONFIG_PDP_TEMP_CAUSE_STRU));

        /* �����ǵ�ǰ���뼼����ѭ��������н��뼼��������APNʵ�� */
        for(ulNetRat = NAS_BACKOFF_NETRAT_LTE; ulNetRat < NAS_BACKOFF_NETRAT_ENUM_BUTT; ulNetRat++)
        {
            for(ulIndex = 0; ulIndex < NAS_BACKOFF_APN_ENTITY_MAX_NUM; ulIndex++)
            {
                NAS_BACKOFF_ClearApnEntity(ulNetRat, ulIndex);
            }
        }
    }

    return;

}
VOS_UINT32 NAS_BACKOFF_QueryInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    APP_ESM_APN_INFO_STRU              *pstApn,
    NAS_BACKOFF_QUERY_RESULT_STRU      *pstQueryResult
)
{
    VOS_UINT32                          ulIndex      = 0;
    NAS_BACKOFF_APN_ENTITY_STRU        *pstApnEntity = NAS_BACKOFF_NULL_PTR;

    for(ulIndex = 0; ulIndex < NAS_BACKOFF_APN_ENTITY_MAX_NUM; ulIndex++)
    {
        pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulIndex);

        /* ��ǰAPNʵ����Ч��APN������ͬ���Ƚ�APNֵ */
        if((NAS_BACKOFF_APN_ENTITY_FLAG_VALID == pstApnEntity->enValidFlag)
            &&(pstApnEntity->stApnInfo.ucApnLen == pstApn->ucApnLen))
        {
            /* APNֵ��ͬ���ҵ� */
            if(NAS_ESM_SUCCESS == NAS_ESM_MEM_CMP(pstApn, &pstApnEntity->stApnInfo, pstApn->ucApnLen))
            {
                break;
            }
        }
    }

    /* �ҵ� */
    if(ulIndex < NAS_BACKOFF_APN_ENTITY_MAX_NUM)
    {
        /* ���ò�ѯ���: �������㷨״̬���ͷ���ʱ��״̬ */
        pstQueryResult->ulIndex      = ulIndex;
        pstQueryResult->enState      = pstApnEntity->enState;
        pstQueryResult->enTimeStatus = NAS_BACKOFF_GetForbidTimerState(pstApnEntity);

        return NAS_BACKOFF_SUCC;
    }

    /* δ�ҵ� */
    return NAS_BACKOFF_FAIL;

}
VOS_VOID NAS_BACKOFF_PdpActiveSuccProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
)
{
    NAS_BACKOFF_QUERY_RESULT_STRU   stQueryResult;

    NAS_ESM_MEM_SET(&stQueryResult, 0 , sizeof(NAS_BACKOFF_QUERY_RESULT_STRU));

    /* ��ѯ��ǰAPN���ʵ���Ƿ���� */
    if(NAS_BACKOFF_SUCC == NAS_BACKOFF_QueryInfo(enNetRat, &pstMaintainPara->stApnInfo, &stQueryResult))
    {
        /* �����������Ӧ��APNʵ�� */
        NAS_BACKOFF_ClearApnEntity(enNetRat, stQueryResult.ulIndex);
    }

    return;

}


VOS_VOID NAS_BACKOFF_PdpActiveFailProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
)
{
    NAS_BACKOFF_APN_ENTITY_STRU        *pstApnEntity = NAS_BACKOFF_NULL_PTR;
    VOS_UINT32                          ulAllocIndex = 0;
    NAS_BACKOFF_QUERY_RESULT_STRU       stQueryResult;

    NAS_ESM_MEM_SET(&stQueryResult, 0 , sizeof(NAS_BACKOFF_QUERY_RESULT_STRU));

    /* ���ҷ���APN��Ӧ��ʵ����� */
    if(NAS_BACKOFF_SUCC == NAS_BACKOFF_QueryInfo(enNetRat, &pstMaintainPara->stApnInfo, &stQueryResult))
    {
        /* �ҵ�APNʵ�壬���ݵ�ǰʵ����㷨״̬������Ӧ���� */
        pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, stQueryResult.ulIndex);

        if(NAS_BACKOFF_STATE_INACTIVE == pstApnEntity->enState)
        {
            NAS_BACKOFF_InactiveProc(enNetRat, stQueryResult.ulIndex, \
                        pstMaintainPara->enPdpResult, pstMaintainPara->ucCnCause);
        }
        else
        {
            NAS_BACKOFF_ActiveProc(enNetRat, stQueryResult.ulIndex, \
                        pstMaintainPara->enPdpResult, pstMaintainPara->ucCnCause);
        }

        return;
    }

    /* APNʵ�岻���ڣ�����һ��ʵ�� */
    if(NAS_BACKOFF_SUCC != NAS_BACKOFF_AllocApnEntity(enNetRat, &ulAllocIndex))
    {
        /* ʵ������������ʧ��ֱ�ӷ��� */
        return;
    }

    pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulAllocIndex);

    /* ����APNʵ�屻���� */
    pstApnEntity->enValidFlag        = NAS_BACKOFF_APN_ENTITY_FLAG_VALID;

    /* ����APN */
    pstApnEntity->stApnInfo.ucApnLen = pstMaintainPara->stApnInfo.ucApnLen;
    NAS_ESM_MEM_CPY(pstApnEntity->stApnInfo.aucApnName,
                     pstMaintainPara->stApnInfo.aucApnName,
                     pstMaintainPara->stApnInfo.ucApnLen);

    /* ����INACTIVE̬ */
    NAS_BACKOFF_SetBackOffState(NAS_BACKOFF_STATE_INACTIVE, pstApnEntity);

    /* ִ��INACTIVE̬�Ĵ��� */
    NAS_BACKOFF_InactiveProc(enNetRat, ulAllocIndex, \
                pstMaintainPara->enPdpResult, pstMaintainPara->ucCnCause);

    return;

}


VOS_VOID NAS_BACKOFF_InactiveProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32           enNetRat,
    VOS_UINT32                               ulIndex,
    NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8      enPdpResult,
    VOS_UINT8                                ucCnCause
)
{
    NAS_BACKOFF_PDP_REJ_TYPE_ENUM8      enPdpRejType = NAS_BACKOFF_PDP_REJ_TYPE_ENUM_BUTT;
    NAS_BACKOFF_COMM_PARA_STRU         *pstCommPara  = NAS_BACKOFF_NULL_PTR;
    NAS_BACKOFF_APN_ENTITY_STRU        *pstApnEntity = NAS_BACKOFF_NULL_PTR;

    pstCommPara  = NAS_BACKOFF_GetCommParaAddr();
    pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulIndex);

    /* ���ʧ��ԭ��Ϊ��ʱ����FnIgnore���м�1��Ȼ���ж��Ƿ��������ACTIVE̬ */
    if(NAS_BACKOFF_PDP_ACTIVE_RESULT_TIMER_EXP == enPdpResult)
    {
        pstApnEntity->stInactiveInfo.ulFnIgnore++;

        /* �����ﵽFbIgnore��ֱ�ӽ���ACTIVE̬�������ͷ���ʱ�� */
        if(pstApnEntity->stInactiveInfo.ulFnIgnore >= pstCommPara->ucFbIgnore)
        {
            /* ����״̬ΪACTIVE��ִ��ACTIVE���� */
            NAS_BACKOFF_SetBackOffState(NAS_BACKOFF_STATE_ACTIVE, pstApnEntity);
            NAS_BACKOFF_ActiveProc(enNetRat, ulIndex,\
                        NAS_BACKOFF_PDP_ACTIVE_RESULT_TIMER_EXP, NAS_BACKOFF_PDP_CAUSE_NULL);
        }

        return;
    }

    enPdpRejType = NAS_BACKOFF_GetPdpCnRejType(ucCnCause);

    /* ������PERM REJ����TEMP REJ�Լ������д���OTHER REJ�����ߵ�����ɵ����߱�֤ */
    if(NAS_BACKOFF_PDP_REJ_TYPE_PERM_REJ == enPdpRejType)
    {
        pstApnEntity->stInactiveInfo.ulFnPerm++;
    }
    else
    {
        pstApnEntity->stInactiveInfo.ulFnTemp++;
    }

    /* �����������ﵽFbPerm��FbTemp��ֱ�ӽ���ACTIVE̬�������ͷ���ʱ�� */
    if((pstApnEntity->stInactiveInfo.ulFnPerm >= pstCommPara->ucFbPerm)
        ||(pstApnEntity->stInactiveInfo.ulFnTemp >= pstCommPara->ucFbTemp))
    {
        /* ����״̬ΪACTIVE��ִ��ACTIVE���� */
        NAS_BACKOFF_SetBackOffState(NAS_BACKOFF_STATE_ACTIVE, pstApnEntity);
        NAS_BACKOFF_ActiveProc(enNetRat, ulIndex,\
                    NAS_BACKOFF_PDP_ACTIVE_RESULT_CN_REJ, ucCnCause);
    }

    return;

}


VOS_VOID NAS_BACKOFF_ActiveProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32           enNetRat,
    VOS_UINT32                               ulIndex,
    NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8      enPdpResult,
    VOS_UINT8                                ucCnCause
)
{
    /* ���ʧ��ԭ��Ϊ��ʱ������Ignore�ͷ���ʱ�� */
    if(NAS_BACKOFF_PDP_ACTIVE_RESULT_TIMER_EXP == enPdpResult)
    {
        NAS_BACKOFF_ForbidTimerStart(enNetRat, ulIndex, TI_NAS_ESM_BACKOFF_IGNORE_FORBID);
        return;
    }

    /* CN�ܾ���һ����PERM REJ��TEMP REJ��������Ӧ��ʱ��������REJ�������˺������ɵ����߱�֤ */
    if(NAS_BACKOFF_PDP_ACTIVE_RESULT_CN_REJ == enPdpResult)
    {
        if(NAS_BACKOFF_PDP_REJ_TYPE_PERM_REJ == NAS_BACKOFF_GetPdpCnRejType(ucCnCause))
        {
            NAS_BACKOFF_ForbidTimerStart(enNetRat, ulIndex, TI_NAS_ESM_BACKOFF_PERM_REJ_FORBID);
        }
        else
        {
            NAS_BACKOFF_ForbidTimerStart(enNetRat, ulIndex, TI_NAS_ESM_BACKOFF_TEMP_REJ_FORBID);
        }
    }

    return;

}


VOS_UINT32  NAS_BACKOFF_ReadNvDamBackOffPara
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU  *pstNvDamPara
)
{
    VOS_UINT32                          ulDataLen = 0;
    VOS_UINT32                          ulRslt    = NAS_BACKOFF_NVIM_FAIL;

    /* ��NV */
    ulDataLen = sizeof(LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU);
    ulRslt = LPs_NvimItem_Read(EN_NV_ID_BACKOFF_ALG_CONFIG,
                              (VOS_VOID *)pstNvDamPara,
                              ulDataLen);

    if(NAS_BACKOFF_NVIM_SUCC == ulRslt)
    {
        return NAS_BACKOFF_NVIM_SUCC;
    }

    NAS_ESM_INFO_LOG("NAS_BACKOFF_ReadNvDamBackOffPara: read NV Fail.");
    TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_ReadNvDamBackOffPara_ENUM, LNAS_FAIL);
    return NAS_BACKOFF_NVIM_FAIL;

}
VOS_VOID  NAS_BACKOFF_InitPdpRejCauseList
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU    *pstNvDamPara
)
{
    NAS_CONFIG_PDP_PERM_CAUSE_STRU       *pstPdpPermCauseList = NAS_BACKOFF_NULL_PTR;
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU       *pstPdpTempCauseList = NAS_BACKOFF_NULL_PTR;

    pstPdpPermCauseList = NAS_BACKOFF_GetPdpPermCauseListAddr();
    pstPdpTempCauseList = NAS_BACKOFF_GetPdpTempCauseListAddr();

    pstPdpPermCauseList->ucCauseNum = pstNvDamPara->stPdpPermCause.ucCauseNum;
    pstPdpTempCauseList->ucCauseNum = pstNvDamPara->stPdpTempCause.ucCauseNum;

    /* �������ԭ��ֵ����ʼ�������ԭ��ֵ��ĿΪ0�����ʼ����Ĭ��ֵ */
    if(0 != pstPdpPermCauseList->ucCauseNum)
    {
        NAS_ESM_MEM_CPY(pstPdpPermCauseList->aucCause,
                         pstNvDamPara->stPdpPermCause.aucCause,
                         pstPdpPermCauseList->ucCauseNum*sizeof(VOS_UINT8));
    }
    else
    {
        /* ���þܾ�ԭ��ֵ, Ĭ��ֵ7�� #8#27#28#29#30#32#33 */
        pstPdpPermCauseList->ucCauseNum  = NAS_BACKOFF_PDP_PERM_CAUSE_DEFAULT_NUM;
        pstPdpPermCauseList->aucCause[0] = 0X08;
        pstPdpPermCauseList->aucCause[1] = 0X1B;
        pstPdpPermCauseList->aucCause[2] = 0X1C;
        pstPdpPermCauseList->aucCause[3] = 0X1D;
        pstPdpPermCauseList->aucCause[4] = 0X1E;
        pstPdpPermCauseList->aucCause[5] = 0X20;
        pstPdpPermCauseList->aucCause[6] = 0X21;
    }

    if(0 != pstPdpTempCauseList->ucCauseNum)
    {
        NAS_ESM_MEM_CPY(pstPdpTempCauseList->aucCause,
                         pstNvDamPara->stPdpTempCause.aucCause,
                         pstPdpTempCauseList->ucCauseNum*sizeof(VOS_UINT8));
    }
    else
    {
        /* ��ʱ�ܾ�ԭ��ֵ��Ĭ��ֵ8�� #25#26#31#34#35#38#102#111 */
        pstPdpTempCauseList->ucCauseNum  = NAS_BACKOFF_PDP_TEMP_CAUSE_DEFAULT_NUM;
        pstPdpTempCauseList->aucCause[0] = 0X19;
        pstPdpTempCauseList->aucCause[1] = 0X1A;
        pstPdpTempCauseList->aucCause[2] = 0X1F;
        pstPdpTempCauseList->aucCause[3] = 0X22;
        pstPdpTempCauseList->aucCause[4] = 0X23;
        pstPdpTempCauseList->aucCause[5] = 0X26;
        pstPdpTempCauseList->aucCause[6] = 0X66;
        pstPdpTempCauseList->aucCause[7] = 0X6F;
    }

    return;

}
VOS_VOID  NAS_BACKOFF_InitCommParaFx
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU  *pstNvDamPara,
    NAS_BACKOFF_INIT_INFO_STRU            *pstInitInfo
)
{
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara       = NAS_BACKOFF_NULL_PTR;

    pstCommPara       = NAS_BACKOFF_GetCommParaAddr();

    /* ���в�����Ч */
    if(NAS_BACKOFF_BIT_SILT == pstInitInfo->bitOpSimFxFlag)
    {
        pstCommPara->ucFxIgnore = pstInitInfo->ucSimFxIgnore;
        pstCommPara->ucFxPerm   = pstInitInfo->ucSimFxPerm;
        pstCommPara->ucFxTemp   = pstInitInfo->ucSimFxTemp;
    }
    else if(NAS_BACKOFF_BIT_SILT == pstNvDamPara->bitOpBackOffFx)
    {
        /* ���в�����Ч�����ʧ�ܣ�NV�в�����Ч��ʹ��NV�в��� */
        pstCommPara->ucFxIgnore = pstNvDamPara->stBackOffFx.ucFxIgnore;
        pstCommPara->ucFxPerm   = pstNvDamPara->stBackOffFx.ucFxPerm;
        pstCommPara->ucFxTemp   = pstNvDamPara->stBackOffFx.ucFxTemp;
    }
    else
    {
        /* ���ֲ�������Ч������Ĭ��ֵ */
        pstCommPara->ucFxIgnore = NAS_ESM_BACKOFF_IGNORE_FX_DEFAULT_VALUE;
        pstCommPara->ucFxPerm   = NAS_ESM_BACKOFF_PERM_FX_DEFAULT_VALUE;
        pstCommPara->ucFxTemp   = NAS_ESM_BACKOFF_TEMP_FX_DEFAULT_VALUE;
    }

    /* ����������� */
    NAS_BACKOFF_CheckFx(pstCommPara);

    return;

}


VOS_VOID  NAS_BACKOFF_InitCommParaFb
(
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara
)
{
    pstCommPara->ucFbIgnore = NAS_BACKOFF_SelectFb(pstCommPara->ucFxIgnore);
    pstCommPara->ucFbPerm   = NAS_BACKOFF_SelectFb(pstCommPara->ucFxPerm);
    pstCommPara->ucFbTemp   = NAS_BACKOFF_SelectFb(pstCommPara->ucFxTemp);
    return;
}


VOS_VOID NAS_BACKOFF_InitCommParaTimerPara
(
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara
)
{
    /* ����Ignore�����Ķ�ʱ�������� */
    NAS_BACKOFF_CalcTimerLenMinAndMax(pstCommPara->ucFxIgnore,
                     pstCommPara->ucFbIgnore, &pstCommPara->stFxIgnoreTimerInfo);

    /* ����Perm�����Ķ�ʱ�������� */
    NAS_BACKOFF_CalcTimerLenMinAndMax(pstCommPara->ucFxPerm,
                     pstCommPara->ucFbPerm, &pstCommPara->stFxPermTimerInfo);

    /* ����Temp�����Ķ�ʱ�������� */
    NAS_BACKOFF_CalcTimerLenMinAndMax(pstCommPara->ucFxTemp,
                     pstCommPara->ucFbTemp, &pstCommPara->stFxTempTimerInfo);

    return;
}
VOS_VOID NAS_BACKOFF_CheckFx
(
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara
)
{
    /* ����Back-off�㷨��������FxС��4�������޷�ʵ��ÿ15����
    ���ٿɷ���1�ε���������ֵ�쳣������ΪĬ��ֵ */
    if(NAS_BACKOFF_FX_MIN_VALUE > pstCommPara->ucFxIgnore)
    {
        pstCommPara->ucFxIgnore = NAS_ESM_BACKOFF_IGNORE_FX_DEFAULT_VALUE;
    }

    if(NAS_BACKOFF_FX_MIN_VALUE > pstCommPara->ucFxPerm)
    {
        pstCommPara->ucFxPerm = NAS_ESM_BACKOFF_PERM_FX_DEFAULT_VALUE;
    }

    if(NAS_BACKOFF_FX_MIN_VALUE > pstCommPara->ucFxTemp)
    {
        pstCommPara->ucFxTemp = NAS_ESM_BACKOFF_TEMP_FX_DEFAULT_VALUE;
    }

    return;
}


VOS_UINT8 NAS_BACKOFF_SelectFb(VOS_UINT8 ucFx)
{
    /* Fxֵ���ڲ�ͬ���䣬ѡ��ͬ��Fb */
    if(NAS_BACKOFF_FX_MIN_VALUE == ucFx)
    {
        return 0;
    }

    if((5 <= ucFx)&&(6 >= ucFx))
    {
        return 1;
    }

    if((7 <= ucFx)&&(10 >= ucFx))
    {
        return 2;
    }

    if((11 <= ucFx)&&(15 >= ucFx))
    {
        return 4;
    }

    if((16 <= ucFx)&&(20 >= ucFx))
    {
        return 6;
    }

    if((21 <= ucFx)&&(29 >= ucFx))
    {
        return 8;
    }

    /* ���ڵ���30ʱ��ѡ��3��֮һ��ΪFb */
    if(30 <= ucFx)
    {
        return ucFx/3;/* [false alarm]:���뱣֤�˷��ŵ���ȷ�� */
    }
    return 0;

}
VOS_VOID NAS_BACKOFF_CalcTimerLenMinAndMax
(
    VOS_UINT8                           ucFx,
    VOS_UINT8                           ucFb,
    NAS_BACKOFF_TIMER_INFO_STRU        *pstTimerInfo
)
{
    VOS_UINT32                          ulFa;
    VOS_UINT32                          ulFm;

    /* ACTIVE̬1Сʱ�ڿ�����෢��Ĵ���Fa */
    ulFa = ucFx - ucFb;

    /* Tmin = min{15min , 60min/Fa}���粻�������������1ms�����Ժ��� */
    pstTimerInfo->ulTminLen = \
        (NAS_BACKOFF_1HOUR_VALUE / ulFa) < NAS_BACKOFF_FORBID_TIMER_MAX_VALUE ? \
                       (NAS_BACKOFF_1HOUR_VALUE / ulFa) : NAS_BACKOFF_FORBID_TIMER_MAX_VALUE;

    /* ÿ15���ӿɷ���������� Fm = max{0.05*Fx , 1} */
    ulFm = (ucFx / 20) > 1 ? (ucFx / 20) : 1;

    /* Tmax = 15min/Fm���粻�������������1ms�����Ժ���*/
    pstTimerInfo->ulTmaxLen = (NAS_BACKOFF_FORBID_TIMER_MAX_VALUE / ulFm);

    return;
}



VOS_UINT32 NAS_BACKOFF_AllocApnEntity
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulIndex      = 0;
    NAS_BACKOFF_APN_ENTITY_STRU        *pstApnEntity = NAS_BACKOFF_NULL_PTR;

    for(ulIndex = 0; ulIndex < NAS_BACKOFF_APN_ENTITY_MAX_NUM; ulIndex++)
    {
        pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulIndex);

        if(NAS_BACKOFF_APN_ENTITY_FLAG_VALID != pstApnEntity->enValidFlag)
        {
            /* �ҵ�δ���õ�APNʵ�壬������ݣ����������� */
            NAS_ESM_MEM_SET(pstApnEntity, 0 , sizeof(NAS_BACKOFF_APN_ENTITY_STRU));
            *pulIndex = ulIndex;
            return NAS_BACKOFF_SUCC;
        }
    }

    return NAS_BACKOFF_FAIL;

}
VOS_UINT8 NAS_BACKOFF_GetPdpCnRejType(VOS_UINT8  ucCnCause)
{
    VOS_UINT32                          ulIndex = 0;
    NAS_CONFIG_PDP_PERM_CAUSE_STRU     *pstPdpPermCauseList = NAS_BACKOFF_NULL_PTR;
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU     *pstPdpTempCauseList = NAS_BACKOFF_NULL_PTR;

    pstPdpPermCauseList = NAS_BACKOFF_GetPdpPermCauseListAddr();
    pstPdpTempCauseList = NAS_BACKOFF_GetPdpTempCauseListAddr();

    /* �����Ƿ���Permԭ��ֵ�б��� */
    for(ulIndex = 0; ulIndex < pstPdpPermCauseList->ucCauseNum; ulIndex++)
    {
        if(ucCnCause == pstPdpPermCauseList->aucCause[ulIndex])
        {
            return NAS_BACKOFF_PDP_REJ_TYPE_PERM_REJ;
        }
    }

    /* �����Ƿ���Tempԭ��ֵ�б��� */
    for(ulIndex = 0; ulIndex < pstPdpTempCauseList->ucCauseNum; ulIndex++)
    {
        if(ucCnCause == pstPdpTempCauseList->aucCause[ulIndex])
        {
            return NAS_BACKOFF_PDP_REJ_TYPE_TEMP_REJ;
        }
    }

    /* ȫ��δ�ҵ���������ԭ��ֵ */
    return NAS_BACKOFF_PDP_REJ_TYPE_OTHER;

}
VOS_VOID NAS_BACKOFF_ClearApnEntity
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                          ulIndex
)
{
    NAS_BACKOFF_APN_ENTITY_STRU    *pstApnEntity = NAS_BACKOFF_NULL_PTR;
    NAS_BACKOFF_TIMER_STRU         *pstTimer     = NAS_BACKOFF_NULL_PTR;

    pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulIndex);

    pstTimer = &pstApnEntity->stActiveInfo.stBackoffTimer;

    /* ɾ�������APN */
    NAS_ESM_MEM_SET(&pstApnEntity->stApnInfo, 0, sizeof(APP_ESM_APN_INFO_STRU));

    /* ʵ������Ϊ��Ч */
    pstApnEntity->enValidFlag = NAS_BACKOFF_APN_ENTITY_FLAG_INVALID;

    /* ��ǰAPNʵ���Ӧ���㷨״̬����Ϊδ���� */
    NAS_BACKOFF_SetBackOffState(NAS_BACKOFF_STATE_INACTIVE, pstApnEntity);

    /* ���δ����̬�����Ϣ */
    NAS_ESM_MEM_SET(&pstApnEntity->stInactiveInfo, 0, sizeof(NAS_BACKOFF_INACTIVE_INFO_STRU));

    /* ֹͣ�ͷ���ʱ�� */
    NAS_BACKOFF_ForbidTimerStop(enNetRat, ulIndex, pstTimer->enPara);

    return;
}
VOS_UINT32 NAS_BACKOFF_TimerLenRandom
(
    NAS_BACKOFF_TIMER_INFO_STRU       *pstTimerInfo
)
{
    VOS_UINT32                          ulTimerRandSize = 0;
    VOS_UINT32                          ulTimerLen      = 0;

    /* �����������Ķ�ʱ��ʱ��ƫ������Χ */
    ulTimerRandSize = pstTimerInfo->ulTmaxLen - pstTimerInfo->ulTminLen;

    /* ���һ��ƫ���������϶�ʱ����Сֵ��Ϊ��ʱ��ʱ�� */
    ulTimerLen = VOS_Rand(ulTimerRandSize) + pstTimerInfo->ulTminLen;

    return ulTimerLen;
}


VOS_UINT32 NAS_BACKOFF_ForbidTimerLenCalc
(
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    VOS_UINT32                      ulTimerLen  = 0;
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara = NAS_BACKOFF_NULL_PTR;

    pstCommPara = NAS_BACKOFF_GetCommParaAddr();

    switch(enTimerType)
    {
        case TI_NAS_ESM_BACKOFF_IGNORE_FORBID:

            ulTimerLen = NAS_BACKOFF_TimerLenRandom(&pstCommPara->stFxIgnoreTimerInfo);
            break;

        case TI_NAS_ESM_BACKOFF_PERM_REJ_FORBID:

            ulTimerLen = NAS_BACKOFF_TimerLenRandom(&pstCommPara->stFxPermTimerInfo);
            break;

        case TI_NAS_ESM_BACKOFF_TEMP_REJ_FORBID:

            ulTimerLen = NAS_BACKOFF_TimerLenRandom(&pstCommPara->stFxTempTimerInfo);
            break;

        default:
            break;
    }

    return ulTimerLen;

}


VOS_VOID NAS_BACKOFF_ForbidTimerStart
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    VOS_UINT32                      ulTimerLen   = NAS_BACKOFF_NULL;
    NAS_BACKOFF_TIMER_STRU         *pstTimerInfo = NAS_BACKOFF_NULL_PTR;
    VOS_UINT32                      ulTimerName  = 0;
    NAS_BACKOFF_APN_ENTITY_STRU    *pstApnEntity = NAS_BACKOFF_NULL_PTR;

    /* �ҵ�APNʵ�� */
    pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulIndex);

    /*����APNʵ��,��ȡ������Ķ�ʱ��*/
    pstTimerInfo = &pstApnEntity->stActiveInfo.stBackoffTimer;

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_BACKOff_ForbidTimerStart:WARN: stop rel timer error!");
            TLPS_PRINT2LAYER_WARNING1(NAS_BACKOFF_ForbidTimerStart_ENUM, ESM_CALL_API_FAIL, 1);
            return;
        }
    }

    /*���ݶ�ʱ����ͬ���ͣ��ͷ���ʱ�����Ȳ�ͬ*/
    ulTimerLen = NAS_BACKOFF_ForbidTimerLenCalc(enTimerType);
    if (ulTimerLen == NAS_BACKOFF_NULL)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_BACKOff_ForbidTimerStart:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_ForbidTimerStart_ENUM, 1);
        return;
    }

    /* �������ʱ����NAME�����ж�����뼼������˽�����ֵ����ƫ�ƴ���
    ��: ����GU��APNʵ�壬��Ӧ�Ķ�ʱ��ulIndex������ƫ����NAS_BACKOFF_APN_ENTITY_MAX_NUM */
    ulTimerName = (NAS_BACKOFF_APN_ENTITY_MAX_NUM * enNetRat) + ulIndex;

    /* �趨��ʱ��NAME��PARA */
    if (VOS_OK != PS_START_REL_TIMER(&(pstTimerInfo->hTimer),PS_PID_ESM,\
                                ulTimerLen,ulTimerName, (VOS_UINT32)enTimerType, VOS_RELTIMER_NOLOOP))
    {
          /*��ӡ�쳣��Ϣ*/
          NAS_ESM_WARN_LOG("NAS_BACKOff_ForbidTimerStart:WARN: start timer error!");
          TLPS_PRINT2LAYER_WARNING1(NAS_BACKOFF_ForbidTimerStart_ENUM, ESM_CALL_API_FAIL, 2);
          return;
    }

    /*���¶�ʱ��������Ϣ�Ͷ�ʱ�����*/
    pstTimerInfo->enPara = enTimerType;

    /*������ǰ�Ķ�ʱ����Ϣ */
    NAS_ESM_SndOmEsmTimerStatus(NAS_ESM_TIMER_RUNNING, enTimerType, ulTimerLen);

    /* ��ӡ��ʱ��������Ϣ */
    NAS_ESM_PrintTimeStartInfo(ulIndex, enTimerType);

    return;
}
VOS_VOID NAS_BACKOFF_ForbidTimerStop
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    NAS_BACKOFF_TIMER_STRU             *pstTimerInfo     = NAS_BACKOFF_NULL_PTR;
    NAS_BACKOFF_APN_ENTITY_STRU        *pstApnEntity     = NAS_BACKOFF_NULL_PTR;
    VOS_UINT32                          ulTimerRemainLen = 0;

    /* �ҵ�APNʵ�� */
    pstApnEntity = NAS_BACKOFF_GetApnEntityAddr(enNetRat, ulIndex);

    /*����APNʵ��,��ȡ������Ķ�ʱ��*/
    pstTimerInfo = &pstApnEntity->stActiveInfo.stBackoffTimer;

    /*��ʱ�����ڴ�״̬����رգ����򣬺���*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /* ��ȡ��ǰ��ʱ����ʣ��ʱ�� */
        if (VOS_OK != VOS_GetRelTmRemainTime(&pstTimerInfo->hTimer, &ulTimerRemainLen))
        {
            ulTimerRemainLen = 0;
        }

        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&pstTimerInfo->hTimer))
        {
            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_BACKOFF_ForbidTimerStop:WARN: stop rel timer error!");
            TLPS_PRINT2LAYER_WARNING(NAS_BACKOFF_ForbidTimerStop_ENUM, ESM_CALL_API_FAIL);
            return;
        }

        /*������ǰ�Ķ�ʱ����Ϣ */
        NAS_ESM_SndOmEsmTimerStatus(NAS_ESM_TIMER_STOPED, enTimerType, ulTimerRemainLen);

        /* ��ӡ��ʱ���ر���Ϣ */
        NAS_ESM_PrintTimeStopInfo(ulIndex, enTimerType);
    }

    return;
}


VOS_UINT8 NAS_BACKOFF_GetForbidTimerState
(
    NAS_BACKOFF_APN_ENTITY_STRU    *pstApnEntity
)
{
    if((NAS_BACKOFF_STATE_ACTIVE == pstApnEntity->enState)
        &&(VOS_NULL_PTR != pstApnEntity->stActiveInfo.stBackoffTimer.hTimer))
    {
        return NAS_BACKOFF_FOBID_TIMER_STATE_RUNNING;
    }
    else
    {
        return NAS_BACKOFF_FOBID_TIMER_STATE_STOP;
    }
}

VOS_VOID  NAS_BACKOFF_SndOmLogInitInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
)
{
    NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogInitInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogInitInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET(pstMsg, 0, sizeof(NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = NAS_ESM_OM_LOG_BACKOFF_INIT;
    NAS_ESM_MEM_CPY(&pstMsg->stInitInfo,
                     &pstOpPara->u.stInitPara,
                     sizeof(NAS_BACKOFF_INIT_INFO_STRU));
    pstMsg->enNetRat  = enNetRat;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
}

VOS_VOID  NAS_BACKOFF_SndOmLogJudgmentInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
)
{
    NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogJudgmentInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogJudgmentInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET(pstMsg, 0, sizeof(NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = NAS_ESM_OM_LOG_BACKOFF_JUDGMENT;
    NAS_ESM_MEM_CPY(&pstMsg->stJudgmentPara,
                     &pstOpPara->u.stJudgmentPara,
                     sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU));
    pstMsg->enNetRat  = enNetRat;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
}

VOS_VOID  NAS_BACKOFF_SndOmLogMaintainInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
)
{
    NAS_BACKOFF_Maintain_OPERATE_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_Maintain_OPERATE_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_Maintain_OPERATE_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogMaintainInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogMaintainInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET(pstMsg, 0, sizeof(NAS_BACKOFF_Maintain_OPERATE_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_Maintain_OPERATE_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = NAS_ESM_OM_LOG_BACKOFF_MAINTAIN;
    NAS_ESM_MEM_CPY(&pstMsg->stMaintainPara,
                             &pstOpPara->u.stMaintainPara,
                             sizeof(NAS_BACKOFF_MAINTAIN_PARA_STRU));
    pstMsg->enNetRat  = enNetRat;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
}

VOS_VOID  NAS_BACKOFF_SndOmLogResetInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
)
{
    NAS_BACKOFF_RESET_OPERATE_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_RESET_OPERATE_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_RESET_OPERATE_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogResetInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogResetInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET(pstMsg, 0, sizeof(NAS_BACKOFF_RESET_OPERATE_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_RESET_OPERATE_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = NAS_ESM_OM_LOG_BACKOFF_RESET;
    NAS_ESM_MEM_CPY(&pstMsg->enResetCause,
                             &pstOpPara->u.enResetCause,
                             sizeof(NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32));
    pstMsg->enNetRat  = enNetRat;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
}


VOS_VOID  NAS_BACKOFF_SndOmLogOperateInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_TYPE_ENUM_UINT32   enOpType,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
)
{


    /* ���ݲ�ͬ�Ĳ�����䲻ͬ����ϢID����Ϣ�� */
    switch(enOpType)
    {
        case NAS_BACKOFF_OPERATE_TYPE_INIT:

            NAS_BACKOFF_SndOmLogInitInfo(enNetRat,pstOpPara);
            break;

        case NAS_BACKOFF_OPERATE_TYPE_JUDGMENT:

            NAS_BACKOFF_SndOmLogJudgmentInfo(enNetRat,pstOpPara);
            break;

        case NAS_BACKOFF_OPERATE_TYPE_MAINTAIN:

            NAS_BACKOFF_SndOmLogMaintainInfo(enNetRat,pstOpPara);
            break;

        case NAS_BACKOFF_OPERATE_TYPE_RESET:

            NAS_BACKOFF_SndOmLogResetInfo(enNetRat,pstOpPara);
            break;

        default:

            NAS_ESM_INFO_LOG("NAS_BACKOFF_SndOmLogOperatePara:Operate type ERR!");
            TLPS_PRINT2LAYER_INFO(NAS_BACKOFF_SndOmLogResetInfo_ENUM, LNAS_PARAM_INVALID);
            break;
    }
    return;
}
VOS_VOID  NAS_BACKOFF_SndOmLogNvPara
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU         *pstNvDamPara
)
{
    NAS_BACKOFF_LOG_NV_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_LOG_NV_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_LOG_NV_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogNvPara: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogNvPara_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET(pstMsg, 0, sizeof(NAS_BACKOFF_LOG_NV_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_LOG_NV_INFO_STRU) - 20;

    pstMsg->stMsgHeader.ulMsgName       = NAS_ESM_OM_LOG_BACKOFF_NV_PARA;

    NAS_ESM_MEM_CPY(&pstMsg->stBackOffFx,    &pstNvDamPara->stBackOffFx,    sizeof(NAS_CONFIG_BACKOFF_FX_PARA_STRU));
    NAS_ESM_MEM_CPY(&pstMsg->stPdpPermCause, &pstNvDamPara->stPdpPermCause, sizeof(NAS_CONFIG_PDP_PERM_CAUSE_STRU));
    NAS_ESM_MEM_CPY(&pstMsg->stPdpTempCause, &pstNvDamPara->stPdpTempCause, sizeof(NAS_CONFIG_PDP_TEMP_CAUSE_STRU));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
    return;
}


VOS_VOID  NAS_BACKOFF_SndOmLogCommInfo(VOS_VOID)
{
    NAS_BACKOFF_LOG_COMM_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_LOG_COMM_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_LOG_COMM_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogCommInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogCommInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET(pstMsg, 0, sizeof(NAS_BACKOFF_LOG_COMM_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_LOG_COMM_INFO_STRU) - 20;

    pstMsg->stMsgHeader.ulMsgName       = NAS_ESM_OM_LOG_BACKOFF_COMM_INFO;

    NAS_ESM_MEM_CPY(&pstMsg->stCommPara,     &g_stBackOffEntity.stCommPara, sizeof(NAS_BACKOFF_COMM_PARA_STRU));
    NAS_ESM_MEM_CPY(&pstMsg->stPdpPermCause, &g_stBackOffEntity.stPdpPermCause, sizeof(NAS_CONFIG_PDP_PERM_CAUSE_STRU));
    NAS_ESM_MEM_CPY(&pstMsg->stPdpTempCause, &g_stBackOffEntity.stPdpTempCause, sizeof(NAS_CONFIG_PDP_TEMP_CAUSE_STRU));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
    return;

}


VOS_VOID  NAS_BACKOFF_SndOmLogApnEntityList(NAS_BACKOFF_NETRAT_ENUM_UINT32 enNetRat)
{
    NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_BACKOFF_SndOmLogApnEntityList: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_BACKOFF_SndOmLogApnEntityList_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET(pstMsg, 0, sizeof(NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU) - 20;

    pstMsg->stMsgHeader.ulMsgName       = NAS_ESM_OM_LOG_BACKOFF_APN_ENTITY_LIST;

    pstMsg->enNetRat                    = enNetRat;

    NAS_ESM_MEM_CPY(&pstMsg->stNetRatEntity,
                      &g_stBackOffEntity.stNetRatEntity[enNetRat],
                        sizeof(NAS_BACKOFF_NETRAT_ENTITY_STRU));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
    return;

}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


