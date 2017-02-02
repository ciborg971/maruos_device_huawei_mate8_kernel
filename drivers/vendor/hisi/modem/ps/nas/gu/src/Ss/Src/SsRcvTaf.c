/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsRcvTaf.c
  Description  : ����TAF��Ϣ�Ĵ���
  Function List:
      1.  Ss_CheckTafId                  �ж�TAF ID�Ƿ���ACMPָ����TAF ID
      2.  Ss_RcvMnssBeginReq             SS�յ�MNSS_BEGIN_REQ�Ĵ���
      3.  Ss_RcvMnssFacilityReq          SS�յ�MNSS_FACILITY_REQ�Ĵ���
      4.  Ss_RcvMnssEndReq               SS�յ�MNSS_END_REQ�Ĵ���
      5.  Ss_RcvTafMsg                   �ַ�TAF��Ϣ
  History:
      1.  ��־�� 2004.03.08   �°�����
      2.  ��  �� 2006.11.07   ���ⵥA32D07063
      3.  ��  �� 2006.11.23   ���ⵥA32D07452
*******************************************************************************/

#include "SsInclude.h"
#include "SsExt.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SS_RCVTAF_C




VOS_VOID Ss_RcvMnssBeginReq(
    ST_SSP_MSG                         *pSspMsg
)
{
    VOS_UINT8   ucTi;                                                               /* ����TI                                   */
    VOS_UINT8   ucCr;                                                               /* ����CR                                   */

   ucCr = pSspMsg->ucCr;                                                       /* ��ȡCR                                   */
    if( ucCr <= SS_MO_CR_NUM )
    {
        if( SS_NONE_TI != ( ucTi = Ss_EntityBuildTi( ucCr )))
        {                                                                       /* ѡ�����TI                               */
            Ss_EntityCreat( ucTi, ucCr );                              /* ����SSʵ��                               */
            Ss_SaveRegister( pSspMsg, ucTi );                                   /* ����REGISTER��Ϣ                         */

            /* DSDS��Ҫ����Դ�����ٷ�est req�������� */
            NAS_SS_ChangeSsState(ucTi, SS_S_CONNECT_PEND);

            Ss_SndMmssEstReq( ucTi, pSspMsg->ucRedialFlg);                                           /* ����MMSS_EST_REQԭ��                     */

            SS_NORM_LOG("\n SS state: SS_S_NULL ==> SS_S_CONNECT_PEND \r" );
        }
    }
}

/***********************************************************************
*  MODULE   : Ss_RcvMnssFacilityReq
*  FUNCTION : SS�յ�MNSS_FACILITY_REQ�Ĵ���
*  INPUT    : ST_SSP_MSG        *pSspMsg    ��ǰ�������Ϣ
*             VOS_UINT8             ucTafId     ��Ϣ�е�TAF ID
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-08  �°�����
************************************************************************/

VOS_VOID Ss_RcvMnssFacilityReq( ST_SSP_MSG *pSspMsg )
{
    VOS_UINT8   ucTi;                                                               /* ����TI                                   */

    if( SS_NONE_TI != ( ucTi = Ss_EntitySelectTi( pSspMsg->ucCr )))
    {                                                                           /* ����CR��TAF ID��TI                       */
        Ss_SndFacility( pSspMsg, ucTi );                                        /* ����DR(FACILITY)ԭ��                     */
    }
}
VOS_VOID Ss_RcvMnssEndReq( ST_SSP_MSG *pSspMsg )
{
    VOS_UINT8   i;
    VOS_UINT8   ucTi = SS_NONE_TI;                                                            /* ����TI                                   */

    for( i = 0 ; i < SS_MAX_ENTITY_NUM ; i++ )
    {
        if( pSspMsg->ucCr == g_SsEntity[i].ucCr )
        {
            ucTi = i;
            break;
        }
    }

    if( SS_NONE_TI != ucTi)
    {
        if (SS_S_CONNECTED == g_SsEntity[ucTi].ucState)
        {
            Ss_SndRelCmpl( pSspMsg, ucTi, 0 );                                  /* ����DR(RELCMPL)ԭ��                      */
        }

        if ( ( VOS_TRUE == pSspMsg->SspmsgCore.u.EndReq.OP_SspTaCause )
          && ( EN_STC_NORMAL == pSspMsg->SspmsgCore.u.EndReq.enSspTaCause )
          && (SS_S_CONNECT_PEND == g_SsEntity[ucTi].ucState))
        {
            Ss_SndMmssAbortReq(ucTi);
        }
        else
        {
            Ss_SndMmssRelReq( ucTi );                                               /* �ͷŶ�Ӧ��MM����                         */
        }
        Ss_EntityClear( ucTi );                                                 /* �ͷŶ�Ӧ��Ssʵ��                         */
    }
}
VOS_VOID Ss_RcvMnssSsStatusNty(
    ST_SSP_MSG                         *pSspMsg
)
{
    Ss_SndMmssSsStatusNty(pSspMsg->SspmsgCore.u.stSsStatusNty.enSsStatus);
    return;
}

/***********************************************************************
*  MODULE   : Ss_RcvTafMsg
*  FUNCTION : �ַ�TAF��Ϣ
*  INPUT    : VOS_VOID      *pMsg   ��ǰ�������Ϣ
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-08  �°�����
************************************************************************/

VOS_VOID Ss_RcvSsaMsg(
    VOS_VOID                           *pMsg
)
{
    ST_SSP_MSG                      *pstSsMsg;                                   /* CCP��Ϣ�ṹ                              */

    pstSsMsg = (ST_SSP_MSG*)pMsg;                               /* ��ȡASN�����SSP��Ϣ                     */

    switch( pstSsMsg->SspmsgCore.ucChoice )
        {                                                                       /* ������Ϣ���ַ�                           */
        case MNSS_BEGIN_REQ:                                                    /* MNSS_BEGIN_REQ                           */
            Ss_RcvMnssBeginReq( pstSsMsg);                             /* ���� MNSS_BEGIN_REQ ��Ϣ����             */
            break;
        case MNSS_FACILITY_REQ:                                                 /* MNSS_FACILITY_REQ                        */
            Ss_RcvMnssFacilityReq( pstSsMsg );                          /* ���� MNSS_FACILITY_REQ ��Ϣ����          */
            break;
        case MNSS_END_REQ:                                                      /* MNSS_END_REQ                             */
            Ss_RcvMnssEndReq( pstSsMsg );                               /* ���� MNSS_END_REQ ��Ϣ����               */
            break;

        case MNSS_SS_STATUS_NTY:                                                      /* MNSS_SS_STATUS_NTY                             */
            Ss_RcvMnssSsStatusNty( pstSsMsg );                               /* ���� MNSS_SS_STATUS_NTY ��Ϣ����               */
            break;

        default:                                                                /* ����TAF��Ϣ                              */
            SS_WARN_LOG( "\n [Error]APP->SS MsgType Error!\r" );
            break;
        }

}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

