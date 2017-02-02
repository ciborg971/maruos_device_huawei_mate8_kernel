/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsRcvAir.c
  Description  : ���տտ���Ϣ�Ĵ���
  Function List:
      1.  Ss_RcvRegister            �յ���������REGISTER��Ϣ�Ĵ���
      2.  Ss_RcvFacility            �յ���������FACILITY��Ϣ�Ĵ���
      3.  Ss_RcvRelCmpl             �յ���������RELEASE COMPLETE��Ϣ�Ĵ���
      4.  Ss_RcvUnknownAirMsg       �յ��������Ĳ���ʶ��Ŀտ���Ϣ�Ĵ���
  History:
      1.  ��־�� 2004.03.08   �°�����
      2.  ��  �� 2006.11.07   ���ⵥA32D07063
      3.  ��  �� 2006.12.26   ���ⵥA32D07990
      4.  ��  �� 2007.08.07   ���ⵥA32D12052
*******************************************************************************/

#include "SsInclude.h"
#include "Taf_Tafm_Local.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SS_RCVAIR_C

/*lint -save -e958 */


VOS_VOID Ss_RcvRegister(
                    VOS_VOID *pMsg,
                    VOS_UINT32 ulMsgLen,
                    VOS_UINT8 ucTi
                    )
{
    ST_SSP_MSG          stSsmsg;                                                    /* SS�������ɵ���Ϣ                         */

    switch( g_SsEntity[ucTi].ucState )
    {                                                                           /* ����ʵ��״̬�ֱ���д���                 */
    case SS_S_NULL:                                                             /* S0                                       */
        Ss_MemSet( &stSsmsg, 0, sizeof( ST_SSP_MSG ));    /* ����Ϣ�ռ�����                           */
        if( WUEPS_TRUE == Ss_Decode( pMsg, &(stSsmsg.SspmsgCore), ulMsgLen ))
        {                                                                       /* ����ɹ�                                 */
            stSsmsg.ucCr = g_SsEntity[ucTi].ucCr;                               /* ����CR                                   */
            if (stSsmsg.ucCr >= TAF_MT_MIN_CR)
            {
                stSsmsg.ucCr -= 120;                                            /*Cr��ΧΪ128-134ʱ����Ҫת����TI:8-14*/
            }

            NAS_SS_ChangeSsState(ucTi, SS_S_CONNECTED);

            SS_NORM_LOG("\n SS state: SS_S_NULL ==> SS_S_CONNECTED \r" );

            SSA_DealMsgFromSS(&stSsmsg);
        }
    break;

    case SS_S_CONNECT_PEND:                                                     /* S1                                       */
    case SS_S_CONNECTED:                                                        /* S2                                       */
        break;

    default:                                                                    /* ����״̬                                 */
        SS_WARN_LOG( "\n [Error]SsEntity State Error! \r" );
        break;
    }
}

/***********************************************************************
*  MODULE   : Ss_RcvFacility
*  FUNCTION : �յ���������FACILITY��Ϣ�Ĵ���
*  INPUT    : VOS_VOID      *pMsg       ���յ��տ���Ϣ��ָ��
*             VOS_UINT32     ulMsgLen    ��Ϣ�ĳ���
*             VOS_UINT8     ucTi        ��Ӧ��TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-08  �°�����
************************************************************************/

VOS_VOID Ss_RcvFacility(
                    VOS_VOID *pMsg,
                    VOS_UINT32 ulMsgLen,
                    VOS_UINT8 ucTi
                    )
{
    ST_SSP_MSG      stSsmsg;                                                        /* SS�������ɵ���Ϣ                         */


    switch( g_SsEntity[ucTi].ucState )
    {                                                                           /* ����ʵ��״̬�ֱ���д���                 */
    case SS_S_CONNECTED:                                                        /* S2                                       */
        Ss_MemSet( &stSsmsg, 0, sizeof( ST_SSP_MSG ));    /* ����Ϣ�ռ�����                           */
        if( WUEPS_TRUE == Ss_Decode( pMsg, &(stSsmsg.SspmsgCore), ulMsgLen ))
        {                                                                       /* ����ɹ�                                 */
            stSsmsg.ucCr = g_SsEntity[ucTi].ucCr;                               /* ����CR                                   */
            if (stSsmsg.ucCr >= TAF_MT_MIN_CR)
            {
                stSsmsg.ucCr -= 120;                                            /*Cr��ΧΪ128-134ʱ����Ҫת����TI:8-14*/
            }
            SSA_DealMsgFromSS(&stSsmsg);
        }
        break;

    default:                                                                    /* ����״̬                                 */
        SS_WARN_LOG( "\n [Error]SsEntity State Error! \r" );
        break;
    }
}



VOS_VOID Ss_RcvRelCmpl(
                   VOS_VOID *pMsg,
                   VOS_UINT32 ulMsgLen,
                   VOS_UINT8 ucTi
                   )
{
    ST_SSP_MSG      stSsmsg;                                                         /* SS�������ɵ���Ϣ                         */


    switch( g_SsEntity[ucTi].ucState )
    {                                                                           /* ����ʵ��״̬�ֱ���д���                 */
    case SS_S_CONNECTED:                                                        /* S2                                       */
        Ss_MemSet( &stSsmsg, 0, sizeof( ST_SSP_MSG ));    /* ����Ϣ�ռ�����                           */
        if( WUEPS_TRUE == Ss_Decode( pMsg, &(stSsmsg.SspmsgCore), ulMsgLen ))
        {                                                                       /* ����ɹ�                                 */
            stSsmsg.ucCr = g_SsEntity[ucTi].ucCr;                               /* ����CR                                   */
            if (stSsmsg.ucCr >= TAF_MT_MIN_CR)
            {
                stSsmsg.ucCr -= 120;                                            /*Cr��ΧΪ128-134ʱ����Ҫת����TI:8-14*/
            }
            Ss_SndMmssRelReq( ucTi );                                           /* ��MM����MMSS_REL_REQԭ��ͷ�MM����     */

            Ss_EntityClear( ucTi );
            SSA_DealMsgFromSS(&stSsmsg);
        }
        break;
    default:                                                                    /* ����״̬                                 */
        SS_WARN_LOG( "\n [Error]SsEntity State Error! \r" );
        break;
    }
}

/***********************************************************************
*  MODULE   : Ss_RcvUnknownAirMsg
*  FUNCTION : �յ��������Ĳ���ʶ��Ŀտ���Ϣ�Ĵ���
*  INPUT    : VOS_UINT8     ucTi        ��Ӧ��TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-08  �°�����
************************************************************************/

VOS_VOID Ss_RcvUnknownAirMsg(
                         VOS_UINT8 ucTi
                         )
{
    ST_SSP_MSG      stSsMsg;

    Ss_MemSet( &stSsMsg, 0, sizeof( ST_SSP_MSG ));    /* ����Ϣ�ռ�����                           */

    if( SS_S_NULL != g_SsEntity[ucTi].ucState )
    {
        stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;                                       /* ����CR                                   */
        if (stSsMsg.ucCr >= TAF_MT_MIN_CR)
        {
            stSsMsg.ucCr -= 120;                                            /*Cr��ΧΪ128-134ʱ����Ҫת����TI:8-14*/
        }
        stSsMsg.SspmsgCore.ucChoice = D_SMC_END_IND;                                /* ������Ϣѡ��                             */
        Ss_MemSet( &(stSsMsg.SspmsgCore.u.EndInd), 0, sizeof( ST_END_IND ));       /* ����Ϣ�ռ�����                           */
        SSA_DealMsgFromSS(&stSsMsg);
    }

    Ss_SndRelCmpl( VOS_NULL_PTR, ucTi, SS_CAUSE_MSG_TYPE_ERR_OR_NOT_IMPLEMENT );        /* ����DR(RELEASE COMPLETE #97)             */
    Ss_SndMmssRelReq( ucTi );                                                   /* ��MM����MMSS_REL_REQԭ��ͷ�MM����     */
    Ss_EntityClear( ucTi );                                                     /* �ͷŶ�Ӧ��SSʵ��                         */
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

