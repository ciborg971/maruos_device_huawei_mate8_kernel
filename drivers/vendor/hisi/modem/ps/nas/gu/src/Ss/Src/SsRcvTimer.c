/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsRcvTimer.c
  Description  : ����Timer�����Ϣ�Ĵ���
  Function List:
      1.  Ss_T551Expiry         T551�����Ĵ���
      2.  Ss_RcvTimerOut        ����TIMER����ķַ������ú�����CC���ã�
  History:
      1.  ��־�� 2004.03.09   �°�����
      2.  ��    ��   : 2006��10��8��
          ��    ��   : luojian id:60022475
          �޸�����   : ���ⵥ��:A32D06583���޸�Ss_RcvTimerOut����
      3.  ��  �� 2006.11.07   ���ⵥA32D07063
*******************************************************************************/


#include "SsInclude.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*=>A32D07063*/
#if 0
/***********************************************************************
*  MODULE   : Ss_T551Expiry
*  FUNCTION : T551�����Ĵ���
*  INPUT    : VOS_UINT8     ucTi        ��Ӧ��Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_VOID Ss_T551Expiry(
                   VOS_UINT8 ucTi
                   )
{
    ST_SSP_MSG                      stSsMsg;

    SS_WARN_LOG( "\n SS TimerExpiry: T551\r" );
    if( SS_S_CONNECTED == g_SsEntity[ucTi].ucState )
    {                                                                           /* �ж��Ƿ��������                         */

        stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;                                   /* ����CR                                   */
        stSsMsg.SspmsgCore.ucChoice = D_SMC_END_IND;                            /* ������Ϣѡ��                             */
        Ss_MemSet( &(stSsMsg.SspmsgCore.u.EndInd), 0, sizeof( ST_END_IND ));    /* ����Ϣ�ռ�����                           */
        SSA_DealMsgFromSS(&stSsMsg);

        Ss_SndRelCmpl( VOS_NULL_PTR, ucTi, SS_CAUSE_RECOVERY_TIMER_EXPIRY );            /* ����DR(RELEASE COMPLETE #102)            */
        Ss_SndMmssRelReq( ucTi );                                               /* ��MM����MMSS_REL_REQԭ��ͷ�MM����     */
        Ss_EntityClear( ucTi );                                                 /* �ͷŶ�Ӧ��SSʵ��                         */
    }
}
#endif
/*<=A32D07063*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SS_RCVTIMER_C




VOS_VOID Ss_RcvTimerOut(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucTimerId
)
{
    VOS_UINT8                           ucSsTi;


    if (TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER == ucTimerId)
    {
        ucSsTi = Ss_GetSsTi(ucTi);

        Ss_SndMmssAbortReq(ucSsTi);
    }


    TAF_SSA_RcvTimerExpired(ucTimerId, ucTi);




    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

