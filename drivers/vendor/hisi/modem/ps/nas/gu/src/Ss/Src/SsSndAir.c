/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsSndAir.c
  Description  : ���Ϳտ���Ϣ�Ĵ���
  Function List:
      1.  Ss_SaveRegister           ���ڻ���REGISTER��Ϣ
      2.  Ss_SndRegister            ����REGISTER��Ϣ
      3.  Ss_SndFacility            ����FACILITY��Ϣ
      4.  Ss_SndRelCmpl             ����RELEASE COMPLETE��Ϣ
  History:
      1.  ��־�� 2004.03.09   �°�����
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
#define    THIS_FILE_ID        PS_FILE_ID_SS_SNDAIR_C

/*lint -save -e958 */

/***********************************************************************
*  MODULE   : Ss_SaveRegister
*  FUNCTION : ���ڻ���REGISTER��Ϣ
*  INPUT    : VOS_VOID      *pSspMsg        ��ǰ�������Ϣ
*             VOS_UINT8     ucTi            ��Ӧ��Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_VOID Ss_SaveRegister(
                     VOS_VOID *pstSsMsg,
                     VOS_UINT8 ucTi
                     )
{
    VOS_UINT32   ulEncLen;                                                           /* ��������Ϣ����                         */
    VOS_VOID    *pucEncDest;                                                        /* ָ�����������                         */

    SS_NORM_LOG1("Ss_SaveRegister entered. ucTi:", ucTi);

    pucEncDest = PS_SS_MEM_ALLOC( VOS_MEMPOOL_INDEX_NAS,
        SS_MAX_MSG_LEN, WUEPS_MEM_NO_WAIT );                                    /* ����SS����ռ�                           */
    if ( VOS_NULL_PTR == pucEncDest )
    {
        return;
    }
    ulEncLen = Ss_Encode( pstSsMsg, pucEncDest, SS_MSG_REGISTER, ucTi );            /* SS����                                   */
    g_SsSaveMsg[ucTi-8].ulMsgLen = ulEncLen;                                    /* ������Ϣ����                             */
    g_SsSaveMsg[ucTi-8].pucMsg = (VOS_UINT8 *)pucEncDest;                                    /* ������Ϣ                                 */
}

/***********************************************************************
*  MODULE   : Ss_DeleteRegister
*  FUNCTION : �����ͷ�SaveREGISTERʱ������ڴ�
*  INPUT    : VOS_UINT8     ucTi            ��Ӧ��Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
 1.��    ��   : 2015��9��19��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���
************************************************************************/

VOS_VOID Ss_DeleteRegister(
                     VOS_UINT8 ucTi
                     )
{
    SS_NORM_LOG1("Ss_DeleteRegister entered. ucTi:", ucTi);

    g_SsSaveMsg[ucTi-8].ulMsgLen = 0;                                           /* ������Ϣ������0                          */

    if (VOS_NULL_PTR != g_SsSaveMsg[ucTi-8].pucMsg)
    {
        PS_SS_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, g_SsSaveMsg[ucTi-8].pucMsg );    /* �ͷŻ����REGISTER��Ϣ                   */
        g_SsSaveMsg[ucTi-8].pucMsg = VOS_NULL_PTR;
    }
}

/***********************************************************************
*  MODULE   : Ss_SndRegister
*  FUNCTION : ����REGISTER��Ϣ
*  INPUT    : VOS_UINT8     ucTi            ��Ӧ��Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_VOID Ss_SndRegister(
                    VOS_UINT8 ucTi
                    )
{
    VOS_UINT32   ulEncLen;                                                           /* ��������Ϣ����                         */
    VOS_VOID    *pucEncDest;                                                        /* ָ�����������                         */

    ulEncLen = g_SsSaveMsg[ucTi-8].ulMsgLen;
    pucEncDest = g_SsSaveMsg[ucTi-8].pucMsg;                                    /* ��ȡ�����REGISTER��Ϣ                   */

    Ss_SndMmssDataReq( ucTi, (VOS_UINT8 *)pucEncDest, ulEncLen );                            /* ����MMSS_DATA_REQ                        */
    g_SsSaveMsg[ucTi-8].ulMsgLen = 0;                                           /* ������Ϣ������0                          */
    PS_SS_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, pucEncDest );                             /* �ͷŻ����REGISTER��Ϣ                   */
}

/***********************************************************************
*  MODULE   : Ss_SndFacility
*  FUNCTION : ����FACILITY��Ϣ
*  INPUT    : VOS_VOID      *pSspMsg        ��ǰ�������Ϣ
*             VOS_UINT8     ucTi            Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_VOID Ss_SndFacility(
                    VOS_VOID *pSspMsg,
                    VOS_UINT8 ucTi
                    )
{
    VOS_UINT32   ulEncLen;                                                           /* ��������Ϣ����                         */
    VOS_VOID    *pucEncDest;                                                        /* ָ�����������                         */
    VOS_UINT8   *pucSsMsg;

    pucEncDest = PS_SS_MEM_ALLOC( VOS_MEMPOOL_INDEX_NAS,
        SS_MAX_MSG_LEN, WUEPS_MEM_NO_WAIT );                                    /* ����SS����ռ�                           */
    if ( VOS_NULL_PTR == pucEncDest )
    {
        return;
    }
    ulEncLen = Ss_Encode( pSspMsg, pucEncDest, SS_MSG_FACILITY, ucTi );         /* SS����                                   */
    pucSsMsg = (VOS_UINT8 *)pucEncDest;
    Ss_SndMmssDataReq( ucTi, pucSsMsg, ulEncLen );                            /* ����MMSS_DATA_REQ                        */
    PS_SS_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, pucEncDest );                             /* �ͷŸ���Ϣ                               */
}


VOS_VOID Ss_SndRelCmpl(
                   VOS_VOID *pSspMsg,
                   VOS_UINT8 ucTi,
                   VOS_UINT8 ucCause
                   )
{
    VOS_UINT32   ulEncLen;                                                           /* ��������Ϣ����                         */
    VOS_VOID    *pucEncDest;                                                        /* ָ�����������                         */
    VOS_UINT8   *pucSsMsg;
    ST_SSP_MSG    stSsMsg;

    PS_MEM_SET(&stSsMsg, 0, sizeof(stSsMsg));

    if( VOS_NULL_PTR == pSspMsg )
    {                                                                           /* ��Ҫ�Լ�����һ��RELEASE COMPLETE��Ϣ     */
        stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;
        stSsMsg.SspmsgCore.ucChoice = D_SMC_END_REQ;

        stSsMsg.SspmsgCore.u.EndReq.OP_Cause = 1;                                                  /* ���ô���Cause��                          */

        /* ����Cause���ݳ���                        */
        stSsMsg.SspmsgCore.u.EndReq.Cause.ulCnt = 2;                                             /* ����Cause���ݳ���                        */

        stSsMsg.SspmsgCore.u.EndReq.Cause.Cause[0] = 0xe0;                                 /* ��дcoding standard                      */
        stSsMsg.SspmsgCore.u.EndReq.Cause.Cause[1] = ucCause;                              /* ����Cause����                            */

        pucEncDest = PS_SS_MEM_ALLOC( VOS_MEMPOOL_INDEX_NAS,
            SS_MAX_MSG_LEN, WUEPS_MEM_NO_WAIT );                                /* ����SS����ռ�                           */
        if ( VOS_NULL_PTR == pucEncDest)
        {
            return;
        }

        PS_MEM_SET(pucEncDest, 0, SS_MAX_MSG_LEN);

        ulEncLen = Ss_Encode( &stSsMsg, pucEncDest, SS_MSG_RELCMPL, ucTi );         /* SS����                                   */
        pucSsMsg = (VOS_UINT8 *)pucEncDest;

        Ss_SndMmssDataReq( ucTi, pucSsMsg, ulEncLen );                        /* ����MMSS_DATA_REQ                        */
        PS_SS_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, pucEncDest );                         /* �ͷŸ���Ϣ                               */

    }
    else
    {
        pucEncDest = PS_SS_MEM_ALLOC( VOS_MEMPOOL_INDEX_NAS,
            SS_MAX_MSG_LEN, WUEPS_MEM_NO_WAIT );                                /* ����SS����ռ�                           */
        if ( VOS_NULL_PTR == pucEncDest)
        {
            return;
        }

        PS_MEM_SET(pucEncDest, 0, SS_MAX_MSG_LEN);

        ulEncLen = Ss_Encode( pSspMsg, pucEncDest, SS_MSG_RELCMPL, ucTi );      /* SS����                                   */
        pucSsMsg = (VOS_UINT8 *)pucEncDest;
        Ss_SndMmssDataReq( ucTi, pucSsMsg, ulEncLen );                        /* ����MMSS_DATA_REQ                        */
        PS_SS_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, pucEncDest );                         /* �ͷŸ���Ϣ                               */
    }
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

