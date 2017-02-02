/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsEntityMng.c
  Description  : SSʵ�����
  Function List:
      1.  Ss_EntityBuildTi      ѡ��TI
      2.  Ss_EntityBuildCr      ѡ��CR
      3.  Ss_EntityCreat        ����ʵ��
      4.  Ss_EntityClear        �ͷ�ʵ��
      5.  Ss_EntitySelectTi     ����CR��TAF IDѡ�����Ӧ��TI
      6.  Ss_AribMalloc         Ϊ����ARIB�ṹ�ṩ�ڴ�ռ�
      7.  Ss_AribFree           �ͷŵ�����ARIB�ṹ������������ڴ�
  History:
      1.  ��־�� 2004.03.08   �°�����
      2.  ��  �� 2006.11.07   ���ⵥA32D07063
*******************************************************************************/

#include "SsInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SS_ENTITYMNG_C

/*lint -save -e958 */

VOS_VOID  NAS_SS_LogSsStateInfo(
    VOS_UINT8                           ucState
)
{
    NAS_SS_LOG_STATE_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_SS_LOG_STATE_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_SS,
                                         sizeof(NAS_SS_LOG_STATE_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_SS, "NAS_SS_LogCcStateInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_SS_LOG_STATE_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_SS;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_SS;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_SS_LOG_STATE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = SSOM_LOG_STATE_INFO_IND;
    pstMsg->ucSsState                   = ucState;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_SS, pstMsg);

    return;
}


/***********************************************************************
*  MODULE   : Ss_EntityBuildTi
*  FUNCTION : ΪMO�����е�SSʵ��ѡ��һ���µ�TI
*  INPUT    : VOS_UINT8             ucCr        ��Ϣ�е�CR
*             VOS_UINT8             ucTafId     ��Ϣ�е�TAF ID
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT8             ucTi    ��ѡ���TI
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-08  �°�����
************************************************************************/

VOS_UINT8 Ss_EntityBuildTi(
                            VOS_UINT8 ucCr
                       )
{
    VOS_UINT8   i;

    for( i = 8 ; i < SS_MAX_ENTITY_NUM ; i++ )
    {                                                                           /* ѭ����������TI                           */
        if(( ucCr == g_SsEntity[i].ucCr )
            && ( SS_S_NULL != g_SsEntity[i].ucState ))
        {                                                                       /* �ж�ָ��TI�Ƿ��Ѵ���                     */
            return SS_NONE_TI;                                                  /* ����û�ҵ�TI                             */
        }
    }

    for( i = 8 ; i < SS_MAX_ENTITY_NUM ; i++ )
    {                                                                           /* ѭ����������TI                           */
        if( SS_S_NULL == g_SsEntity[i].ucState )
        {                                                                       /* �ж��Ƿ���ڿ��е�TI                     */
            return i;                                                           /* ���ش�TI                                 */
        }
    }
    return SS_NONE_TI;                                                          /* ����û�ҵ�TI                             */
}

/***********************************************************************
*  MODULE   : Ss_EntityBuildCr
*  FUNCTION : ΪMT�����е�SSʵ��ѡ��һ���µ�CR
*  INPUT    : VOS_UINT8     ucTi        ָ��ʵ���TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT8     ucCr        ��ѡ���CR
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-08  �°�����
************************************************************************/

VOS_UINT8 Ss_EntityBuildCr( VOS_UINT8 ucTi )
{
    if( SS_S_NULL == g_SsEntity[ucTi].ucState )
    {                                                                           /* �ж�ָ��TI�Ƿ��Ѵ���                     */
        return ((VOS_UINT8)( ucTi + 128 ));                                         /* ����û�ҵ�TI                             */
    }
    return SS_NONE_CR;                                                          /* ����û�ҵ�CR                             */
}
VOS_UINT8 NAS_SS_IsOnlyMtSs(
    VOS_UINT8                           ucTi
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucNum;

    ucNum = 0;

    /* TI�Ƿ�������VOS_FALSE */
    if (ucTi >= SS_MT_ENTITY_NUM)
    {
        return VOS_FALSE;
    }

    for (ucIndex = 0; ucIndex < SS_MT_ENTITY_NUM; ucIndex++)
    {
        if (SS_S_NULL != g_SsEntity[ucIndex].ucState)
        {
            ucNum++;
        }
    }

    if (1 == ucNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT8 NAS_SS_IsOnlyMoSs(
    VOS_UINT8                           ucTi
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucNum;

    ucNum = 0;

    /* TI�Ƿ�����VOS_FALSE */
    if ((ucTi < 8)
     || (ucTi >= SS_MAX_ENTITY_NUM))
    {
        return VOS_FALSE;
    }

    for (ucIndex = 8; ucIndex < SS_MAX_ENTITY_NUM; ucIndex++)
    {
        if (SS_S_NULL != g_SsEntity[ucIndex].ucState)
        {
            ucNum++;
        }
    }

    if (1 == ucNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_SS_NotifySessionAccordingSsStateChg(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucNewState
)
{
    if ((SS_S_NULL == g_SsEntity[ucTi].ucState)
     && (SS_S_NULL != ucNewState))
    {
        g_SsEntity[ucTi].ucState = ucNewState;

        /* ��һ������ssҵ��֪ͨmm��Դ���� */
        if (0 == (ucTi & NAS_SS_MSG_SND_TO_SIDE_THAT_ORIGINATES_THE_TI))
        {
            if (VOS_TRUE == NAS_SS_IsOnlyMtSs(ucTi))
            {
                NAS_SS_SndMmBeginSessionNotify(MMSS_SESSION_TYPE_MT_SS);
                return;
            }
        }

        /* ��һ����ssҵ�񣬸�mm������Դ */
        if (VOS_TRUE == NAS_SS_IsOnlyMoSs(ucTi))
        {
            NAS_SS_SndMmBeginSessionNotify(MMSS_SESSION_TYPE_MO_SS);
        }

        return;
    }

    if ((SS_S_NULL == ucNewState)
     && (SS_S_NULL != g_SsEntity[ucTi].ucState))
    {
        /* ��������һ·����ss������֪ͨmm ��Դ�ͷ� */
        if (0 == (ucTi & NAS_SS_MSG_SND_TO_SIDE_THAT_ORIGINATES_THE_TI))
        {
            if (VOS_TRUE == NAS_SS_IsOnlyMtSs(ucTi))
            {
                NAS_SS_SndMmEndSessionNotify(MMSS_SESSION_TYPE_MT_SS);
            }

            g_SsEntity[ucTi].ucState = ucNewState;
            return;
        }

        /* ��������һ·����ss������֪ͨmm�ͷ���Դ */
        if (VOS_TRUE == NAS_SS_IsOnlyMoSs(ucTi))
        {
            NAS_SS_SndMmEndSessionNotify(MMSS_SESSION_TYPE_MO_SS);
        }

        g_SsEntity[ucTi].ucState = ucNewState;
        return;
    }

    return;
}
#endif


VOS_VOID NAS_SS_ChangeSsState(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucNewState
)
{
    NAS_SS_LogSsStateInfo(g_SsEntity[ucTi].ucState);

#if (FEATURE_ON == FEATURE_DSDS)
    NAS_SS_NotifySessionAccordingSsStateChg(ucTi, ucNewState);
 #endif

    g_SsEntity[ucTi].ucState = ucNewState;

    NAS_SS_LogSsStateInfo(g_SsEntity[ucTi].ucState);
    return;
}


/***********************************************************************
*  MODULE   : Ss_EntityCreat
*  FUNCTION : ����ʵ��
*  INPUT    : VOS_UINT8     ucTi        ָ��ʵ���TI
*             VOS_UINT8     ucCr        ָ��ʵ���Ӧ��CR
*             VOS_UINT8     ucTafId     ָ��ʵ���Ӧ��TAF ID
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-08  �°�����
************************************************************************/

VOS_VOID Ss_EntityCreat(
                    VOS_UINT8 ucTi,
                    VOS_UINT8 ucCr
                    )
{
    SS_NORM_LOG( "\n Create SS entity()\r");
    g_SsEntity[ucTi].ucCr = ucCr;                                               /* ����CR                                   */
}


VOS_VOID Ss_EntityClear(
                    VOS_UINT8 ucTi
                    )
{
    NAS_SS_ChangeSsState(ucTi, SS_S_NULL);

    SS_NORM_LOG( "\n SS state = SS_S_NULL() \r" );
    SS_NORM_LOG( "\n Destroy SS entity()\r" );
    g_SsEntity[ucTi].ucCr = SS_NONE_CR;                                         /* ���CR                                   */
}


/***********************************************************************
*  MODULE   : Ss_EntitySelectTi
*  FUNCTION : ����CR��TAF IDѡ�����Ӧ��TI
*  INPUT    : VOS_UINT8     ucCr        ָ��ʵ���Ӧ��CR
*             VOS_UINT8     ucTafId     ָ��ʵ���Ӧ��TAF ID
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT8     ucTi;
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-08  �°�����
*     2.
************************************************************************/

VOS_UINT8 Ss_EntitySelectTi(
                            VOS_UINT8 ucCr
                        )
{
    VOS_UINT8   i;                                                                  /* ����ѭ��                                 */
    VOS_UINT8   ucTi;                                                               /* �������ڷ��ص�TI                         */

    ucTi = SS_NONE_TI;                                                          /* ��ʼ��TI                                 */

    if( ucCr <= SS_MO_CR_NUM )
    {                                                                           /* MO����                                   */
        for( i = 8 ; i < SS_MAX_ENTITY_NUM ; i++ )
        {                                                                       /* ����MO���̵�����SSʵ��                   */
            if( ucCr == g_SsEntity[i].ucCr )
            {                                                                   /* �ҵ���ָ����CR��TAF ID                   */
                if( SS_S_CONNECTED == g_SsEntity[i].ucState )
                {                                                               /* ��Ӧ��SSʵ���״̬ΪSS_S_CONNECTED       */
                    ucTi = i;                                                   /* ���ظ�TI                                 */
                }
                else
                {                                                               /* ʵ��״̬����                             */
                    SS_WARN_LOG("\n [Error]SsEntity State Error! \r" );
                }
                break;                                                          /* ����ѭ��                                 */
            }
        }
    }
    else
    {                                                                           /* MT����                                   */
        for( i = 0 ; i < SS_MT_ENTITY_NUM ; i++ )
        {                                                                       /* ����MT���̵�����SSʵ��                   */
            if( ucCr == g_SsEntity[i].ucCr )
            {                                                                   /* �ҵ���ָ����CR                           */
                if( SS_S_CONNECTED == g_SsEntity[i].ucState )
                {                                                               /* ��Ӧ��SSʵ���״̬ΪSS_S_CONNECTED       */
                        ucTi = i;                                               /* ���ظ�TI                                 */
                    }
                else
                {                                                               /* ʵ��״̬����                             */
                    SS_WARN_LOG("\n [Error]SsEntity State Error! \r" );
                }
                break;                                                          /* ����ѭ��                                 */
            }
        }
    }
    return ucTi;                                                                /* �����ҵ���TI                             */
}

VOS_UINT8 Ss_GetSsTi(VOS_UINT8  ucCr)
{
    VOS_UINT8  i;
    VOS_UINT8  ucTi = SS_NONE_TI;

    /* ���緢��USSDҵ��Ҫ���û�ȷ�ϣ��û���ȷ������ʱ����ʱCr��Χ��8-14,ת����128-134 */
    if ((ucCr > (TAF_MIDDLE_SSA_TI))
     && (ucCr <= TAF_MAX_SSA_TI))
    {
        ucCr += 120;
    }

    for( i = 0 ; i < SS_MAX_ENTITY_NUM ; i++ )
    {
        if( ucCr == g_SsEntity[i].ucCr )
        {
            ucTi = i;
            break;
        }
    }

    return ucTi;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

