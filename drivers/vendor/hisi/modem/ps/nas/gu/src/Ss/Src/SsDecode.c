/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsDecode.c
  Description  : SS����
  Function List:
      1.  Ss_DecodeField         ��ָ��IE���н���
      2.  Ss_DecodeRegister      REGISTER��Ϣ����
      3.  Ss_DecodeFacility      FACILITY��Ϣ����
      4.  Ss_DecodeRelCmpl       RELEASE COMPLETE��Ϣ����
      5.  Ss_Decode              SS����������
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
#define    THIS_FILE_ID        PS_FILE_ID_SS_DECODE_C


/*lint -save -e958 */
/***********************************************************************
*  MODULE   : Ss_DecodeField
*  FUNCTION : ��ָ��IE���н���
*  INPUT    : VOS_UINT8           *pucField;  ָ��IE����ǰ���ݵĵ�ַ
*             ST_SSP_IES_FACILITY *pOct;      ָ��IE��������ݵص�ַ
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_VOID Ss_DecodeField(
                    VOS_UINT8 *pucField,                                            /* ָ��IE����ǰ���ݵĵ�ַ                   */
                    ST_SSP_IES_FACILITY *pOct                                       /* ָ��IE��������ݵĵ�ַ                   */
                    )
{
    VOS_UINT8   ucFieldLen;                                                         /* ����ָ��IE�ĳ���                         */
    ucFieldLen = *pucField;                                                     /* ��ȡ��IE�ĳ���                           */
    pOct->ulCnt = ucFieldLen;                                                   /* �������ݳ���                             */
    Ss_MemCpy( pOct->Facility, pucField + 1, ucFieldLen );                          /* ��������                                 */
}

/***********************************************************************
*  MODULE   : Ss_DecodeRegister
*  FUNCTION : REGISTER��Ϣ����
*  INPUT    : VOS_VOID *pSrc;               ����ǰ���ݵĵ�ַ
*             ST_BEGIN_IND *pMsg;       ��������ݵĵ�ַ
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/
VOS_VOID Ss_DecodeRegister(
                        VOS_UINT8 *pSrc,                                            /* ����ǰ���ݵĵ�ַ                         */
                        ST_BEGIN_IND *pMsg                                      /* ��������ݵĵ�ַ                         */
                        )
{
    Ss_DecodeField( pSrc + 1, &( pMsg->Facility ));                             /* ����IE���뺯��                           */
    return;                                                          /* ���ؽ���ɹ���ʧ�ܱ�־                   */
}

/***********************************************************************
*  MODULE   : Ss_DecodeFacility
*  FUNCTION : FACILITY��Ϣ����
*  INPUT    : VOS_VOID *pSrc;                       ����ǰ���ݵĵ�ַ
*             ST_SSP_MSGS_FACILITY_IND *pMsg;   ��������ݵĵ�ַ
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/
VOS_VOID Ss_DecodeFacility(
                        VOS_UINT8 *pSrc,                                            /* ����ǰ���ݵĵ�ַ                         */
                        ST_SSP_MSGS_FACILITY_IND *pMsg                          /* ��������ݵĵ�ַ                         */
                        )
{
    Ss_DecodeField( pSrc, &( pMsg->Facility ));                                 /* ����IE���뺯��                           */

    return;                                                          /* ���ؽ���ɹ���ʧ�ܱ�־                   */
}

/***********************************************************************
*  MODULE   : Ss_DecodeRelCmpl
*  FUNCTION : RELEASE COMPLETE��Ϣ����
*  INPUT    : VOS_VOID *pSrc;              ����ǰ���ݵĵ�ַ
*             ST_END_IND *pMsg;        ��������ݵĵ�ַ
*             VOS_UINT32 ulMsgDataLen;      ��Ϣ��IE���ܳ���
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT8 ucResult;          ����ɹ���־
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_UINT8 Ss_DecodeRelCmpl(
                        VOS_UINT8 *pSrc,                                            /* ����ǰ���ݵĵ�ַ                         */
                        ST_END_IND *pMsg,                                       /* ��������ݵĵ�ַ                         */
                        VOS_UINT32 ulMsgDataLen                                      /* ��Ϣ��IE���ܳ���                         */
                        )
{
    VOS_UINT8   ucIEI;                                                              /* ����ָ��IE��Ӧ��IEI                      */
    VOS_UINT32   ulLenOffset;                                                        /* ����������Ϣ��IE�Ķ�λ�ĳ���ƫ��         */
    VOS_UINT8   *pucField;                                                          /* ����ָ��ָ��IE��ָ��                     */
    VOS_UINT8   ucResult;                                                           /* �������ɹ���־                         */

    ucIEI = 0;                                                                  /* ��ʼ��ָ��IE��Ӧ��IEI                    */
    ulLenOffset = 0;                                                            /* ��ʼ������ƫ��                           */
    pucField = VOS_NULL_PTR;                                                            /* ��ʼ��ָ��IE��ָ��                       */
    ucResult = WUEPS_TRUE;                                                      /* ��ʼ������ɹ���־                       */

    for( ; ulLenOffset < ulMsgDataLen ; )
    {                                                                           /* ѭ���жϸ�IE�Ƿ����                     */
        pucField = pSrc + ulLenOffset + 1;                                      /* ��ȡָ��IE                               */
        ucIEI = *( pSrc + ulLenOffset );                                        /* ��ȡָ��IEI                              */
        switch( ucIEI )
        {                                                                       /* ��IE�����ͷַ�                           */
        case SS_IEIFACILITY:                                                    /* IE: FACILITY                             */
            pMsg->OP_Facility = 1;                                              /* ���ø�IE���ڱ�־                         */
                Ss_DecodeField( pucField, (ST_SSP_IES_FACILITY*)(&(pMsg->Facility)));                        /* ����IE���뺯��                           */
            break;                                                              /* ������֧                                 */
        case SS_IEICAUSE:                                                       /* IE: CAUSE                                */
            pMsg->OP_Cause = 1;                                                 /* ���ø�IE���ڱ�־                         */
                Ss_DecodeField( pucField, (ST_SSP_IES_FACILITY*)(&(pMsg->Cause)));                           /* ����IE���뺯��                           */
            break;                                                              /* ������֧                                 */
        default:                                                                /* ����IE                                   */
            ucResult = WUEPS_FALSE;                                             /* ���ý���ʧ�ܱ�־                         */
            break;                                                              /* ������֧                                 */
        }

        if( WUEPS_FALSE == ucResult )
        {                                                                       /* �жϽ����Ƿ�ʧ��                         */
            break;                                                              /* ����ѭ��                                 */
        }
        ulLenOffset += *pucField + 2;                                           /* ���³���ƫ��                             */
    }
    return ucResult;                                                            /* ���ؽ���ɹ���ʧ�ܱ�־                   */
}

/***********************************************************************
*  MODULE   : Ss_Decode
*  FUNCTION : SS����������
*  INPUT    : VOS_VOID *pSrc;           ����ǰ���ݵĵ�ַ
*             VOS_VOID *pDest;          ��������ݵĵ�ַ
*             VOS_UINT32 ulMsgLen;       ��Ϣ����
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT8 ucResult;       ����ɹ���־
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_UINT8 Ss_Decode(
                VOS_VOID *pSrc,                                                     /* ����ǰ���ݵĵ�ַ                         */
                VOS_VOID *pDest,                                                    /* ��������ݵĵ�ַ                         */
                VOS_UINT32 ulMsgLen                                                  /* ��Ϣ����                                 */
                )
{
    VOS_UINT8   ucMsgType;                                                          /* ������Ϣ����                             */
    VOS_UINT8   ucResult;                                                           /* �������ɹ���־                         */

    ucResult = WUEPS_TRUE;                                                      /* ��ʼ������ɹ���־                       */

    ucMsgType = (( VOS_UINT8 *)pSrc)[1];                                            /* ��ȡ��Ϣ����                             */
    switch( ucMsgType )
    {                                                                           /* ����Ϣ���ͷַ�                           */
    case SS_MSG_REGISTER:
            (( ST_SSP_MSG_CORE *)pDest )->ucChoice = D_SMC_BEGIN_IND;           /* ������Ϣ����                             */
            Ss_DecodeRegister(( VOS_UINT8 *)pSrc + 2,
                              (ST_BEGIN_IND *)(&((( ST_SSP_MSG_CORE *)pDest )->u.BeginInd)));             /* ����REGISTER��Ϣ���뺯��                 */
        break;                                                                  /* ������֧                                 */
    case SS_MSG_FACILITY:
            Ss_DecodeFacility(( VOS_UINT8 *)pSrc + 2,
                              (ST_SSP_MSGS_FACILITY_IND *)(&((( ST_SSP_MSG_CORE *)pDest )->u.BeginInd)));            /* ����FACILITY��Ϣ���뺯��                 */
            (( ST_SSP_MSG_CORE *)pDest )->ucChoice = D_SMC_FACILITY_IND;        /* ������Ϣ����                             */
        break;                                                                  /* ������֧                                 */
    case SS_MSG_RELCMPL:
        ucResult = Ss_DecodeRelCmpl(( VOS_UINT8 *)pSrc + 2,
                                        (ST_END_IND *)(&((( ST_SSP_MSG_CORE *)pDest )->u.BeginInd)),
                                        ulMsgLen - 2 );                                 /* ����REL CMPL��Ϣ���뺯��                 */
        if( WUEPS_TRUE == ucResult )
        {                                                                       /* �жϽ����Ƿ�ɹ�                         */
            (( ST_SSP_MSG_CORE *)pDest )->ucChoice = D_SMC_END_IND;             /* ������Ϣ����                             */
        }
        break;                                                                  /* ������֧                                 */
    default:
        ucResult = WUEPS_FALSE;                                                 /* ���ý���ʧ�ܱ�־                         */
        break;                                                                  /* ������֧                                 */
    }

    return ucResult;                                                            /* ���ؽ���ɹ���ʧ�ܱ�־                   */
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

