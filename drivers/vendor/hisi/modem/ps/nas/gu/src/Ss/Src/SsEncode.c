/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsEncode.c
  Description  : SS����
  Function List:
      1.  Ss_EncodeField               ��ָ��IE���б���
      2.  Ss_EncodeRegister            REGISTER��Ϣ����
      3.  Ss_EncodeFacility            FACILITY��Ϣ����
      4.  Ss_EncodeRelCmpl             RELEASE COMPLETE��Ϣ����
      5.  Ss_Encode                    SS����������
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
#define    THIS_FILE_ID        PS_FILE_ID_SS_ENCODE_C

/*lint -save -e958 */

/***********************************************************************
*  MODULE   : Ss_EncodeField
*  FUNCTION : ��ָ��IE���б���
*  INPUT    : VOS_UINT8 *pDestTmp;          ��������ݵĵ�ַ
*             VOS_UINT8 ucIEI;              ��IE��Ӧ��IEI
*             VOS_UINT32 ulFieldLen;         ��IE�ı��볤��
*             VOS_UINT8 *pSrcTmp;           ����ǰ���ݵĵ�ַ
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT32 ulCodeLen;          �����ĳ���
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_UINT32 Ss_EncodeField(
                     VOS_UINT8 *pDestTmp,                                           /* ��������ݵĵ�ַ                         */
                     VOS_UINT8 ucIEI,                                               /* ��IE��Ӧ��IEI                            */
                     VOS_UINT32 ulFieldLen,                                          /* ��IE�ı��볤��                           */
                     VOS_UINT8 *pSrcTmp                                             /* ����ǰ���ݵĵ�ַ                         */
                     )
{
    VOS_UINT8  ucFldLenTmp;                                                         /* ����IE�ĳ��ȼ�¼                         */

    ucFldLenTmp = 0;                                                            /* ��ʼ��IE�ĳ��ȼ�¼                       */

    if( SS_IEINONE != ucIEI )
    {                                                                           /* �ж�IE�������Ƿ����                     */
        *( pDestTmp + ucFldLenTmp ) = ucIEI;                                    /* ����ָ��IE���ڱ�־                       */
        ucFldLenTmp++;                                                          /* ����IE�ĳ��ȼ�¼                         */
    }
    *( pDestTmp + ucFldLenTmp ) = ( VOS_UINT8 )ulFieldLen;                          /* ���ô�IE����                             */
    ucFldLenTmp++;                                                              /* ����IE�ĳ��ȼ�¼                         */
    Ss_MemCpy( pDestTmp + ucFldLenTmp, pSrcTmp, ulFieldLen );                   /* ���ƴ�IE������                           */

    return( ulFieldLen + ucFldLenTmp );                                         /* ���ر����ĳ���                         */
}

/***********************************************************************
*  MODULE   : Ss_EncodeRegister
*  FUNCTION : REGISTER��Ϣ����
*  INPUT    : ST_BEGIN_REQ *pSrc;       ����ǰ���ݵĵ�ַ
*             VOS_UINT8 *pDest;             ��������ݵĵ�ַ
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT32 ulCodeLen;          �����ĳ���
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_UINT32 Ss_EncodeRegister(
                        ST_BEGIN_REQ *pSrc,                                     /* ����ǰ���ݵĵ�ַ                         */
                        VOS_UINT8 *pDest                                            /* ��������ݵĵ�ַ                         */
                        )
{
    VOS_UINT32   ulCodeLen;                                                          /* ��������ĳ���                         */
    VOS_UINT8   *pSrcTmp;                                                           /* ����ָ��IE�ı���ǰ���ݵĵ�ַ             */
    VOS_UINT32   ulFieldLen;                                                         /* ����ָ��IE�ı��볤��                     */

    ulCodeLen = 0;                                                              /* ��ʼ�������ĳ���                       */
    ulFieldLen = 0;                                                             /* ��ʼ��ָ��IE�ı��볤��                   */

    ulFieldLen = pSrc->Facility.ulCnt;                                          /* ����IE Facility�ı��볤��                */
    pSrcTmp = pSrc->Facility.Facility;                                          /* ���ø�IE�ı���ǰ���ݵĵ�ַ               */
    ulCodeLen += Ss_EncodeField( pDest + ulCodeLen,
        SS_IEIFACILITY, ulFieldLen, pSrcTmp );                                  /* ����IE���뺯��                           */

    if( 1 == pSrc->OP_Sspversion )
    {                                                                           /* �ж�IE SS version�Ƿ����                */
        ulFieldLen = pSrc->Sspversion.ulCnt;                                    /* ���ø�IE�ı��볤��                       */
        pSrcTmp = pSrc->Sspversion.Sspversion;                                  /* ���ø�IE�ı���ǰ���ݵĵ�ַ               */
        ulCodeLen += Ss_EncodeField( pDest + ulCodeLen,
            SS_IEISSPVERSION, ulFieldLen, pSrcTmp );                            /* ����IE���뺯��                           */
    }
    return ulCodeLen;                                                           /* ���ر����ĳ���                         */
}

/***********************************************************************
*  MODULE   : Ss_EncodeFacility
*  FUNCTION : FACILITY��Ϣ����
*  INPUT    : ST_SSP_MSGS_FACILITY_REQ *pSrc;   ����ǰ���ݵĵ�ַ
*             VOS_UINT8 *pDest;                     ��������ݵĵ�ַ
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT32 ulCodeLen;          �����ĳ���
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_UINT32 Ss_EncodeFacility(
                        ST_SSP_MSGS_FACILITY_REQ *pSrc,                         /* ����ǰ���ݵĵ�ַ                         */
                        VOS_UINT8 *pDest                                            /* ��������ݵĵ�ַ                         */
                        )
{
    VOS_UINT32   ulCodeLen;                                                          /* ��������ĳ���                         */
    VOS_UINT8   *pSrcTmp;                                                           /* ����ָ��IE�ı���ǰ���ݵĵ�ַ             */
    VOS_UINT32   ulFieldLen;                                                         /* ����ָ��IE�ı��볤��                     */

    ulCodeLen = 0;                                                              /* ��ʼ�������ĳ���                       */
    ulFieldLen = 0;                                                             /* ��ʼ��ָ��IE�ı��볤��                   */

    ulFieldLen = pSrc->Facility.ulCnt;                                          /* ����IE Facility�ı��볤��                */
    pSrcTmp = pSrc->Facility.Facility;                                             /* ���ø�IE�ı���ǰ���ݵĵ�ַ               */
    ulCodeLen += Ss_EncodeField( pDest + ulCodeLen,
        SS_IEINONE, ulFieldLen, pSrcTmp );                                      /* ����IE���뺯��                           */

    return ulCodeLen;                                                           /* ���ر����ĳ���                         */
}

/***********************************************************************
*  MODULE   : Ss_EncodeRelCmpl
*  FUNCTION : RELEASE COMPLETE��Ϣ����
*  INPUT    : ST_END_REQ *pSrc;         ����ǰ���ݵĵ�ַ
*             VOS_UINT8 *pDest;             ��������ݵĵ�ַ
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT32 ulCodeLen;          �����ĳ���
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_UINT32 Ss_EncodeRelCmpl(
                       ST_END_REQ *pSrc,                                        /* ����ǰ���ݵĵ�ַ                         */
                       VOS_UINT8 *pDest                                             /* ��������ݵĵ�ַ                         */
                       )
{
    VOS_UINT32   ulCodeLen;                                                          /* ��������ĳ���                         */
    VOS_UINT8   *pSrcTmp;                                                           /* ����ָ��IE�ı���ǰ���ݵĵ�ַ             */
    VOS_UINT32   ulFieldLen;                                                         /* ����ָ��IE�ı��볤��                     */

    ulCodeLen = 0;                                                              /* ��ʼ�������ĳ���                       */
    ulFieldLen = 0;                                                             /* ��ʼ��ָ��IE�ı��볤��                   */

    if( 1 == pSrc->OP_Cause )
    {                                                                           /* �ж�IE Cause�Ƿ����                     */
        ulFieldLen = pSrc->Cause.ulCnt;                                         /* ���ø�IE�ı��볤��                       */
        pSrcTmp = pSrc->Cause.Cause;                                            /* ���ø�IE�ı���ǰ���ݵĵ�ַ               */
        ulCodeLen += Ss_EncodeField( pDest + ulCodeLen,
            SS_IEICAUSE, ulFieldLen, pSrcTmp );                                 /* ����IE���뺯��                           */
    }
    if( 1 == pSrc->OP_Facility )
    {                                                                           /* �ж�IE Facility�Ƿ����                  */
        ulFieldLen = pSrc->Facility.ulCnt;                                      /* ���ø�IE�ı��볤��                       */
        pSrcTmp = pSrc->Facility.Facility;                                      /* ���ø�IE�ı���ǰ���ݵĵ�ַ               */
        ulCodeLen += Ss_EncodeField( pDest + ulCodeLen,
            SS_IEIFACILITY, ulFieldLen, pSrcTmp );                              /* ����IE���뺯��                           */
    }
    return ulCodeLen;                                                           /* ���ر����ĳ���                         */
}

/***********************************************************************
*  MODULE   : Ss_Encode
*  FUNCTION : SS����������
*  INPUT    : VOS_VOID *pSrc;           ����ǰ���ݵĵ�ַ
*             VOS_VOID *pDest;          ��������ݵĵ�ַ
*             VOS_UINT8 ucMsgType;      ��Ϣ����
*             VOS_UINT8 ucTi;           �տ���Ϣ�е�Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT32 ulCodeLen;      �����ĳ���
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
************************************************************************/

VOS_UINT32 Ss_Encode(
                VOS_VOID *pSrc,                                                     /* ����ǰ���ݵĵ�ַ                         */
                VOS_VOID *pDest,                                                    /* ��������ݵĵ�ַ                         */
                VOS_UINT8 ucMsgType,                                                /* ��Ϣ����                                 */
                VOS_UINT8 ucTi                                                      /* �տ���Ϣ�е�Ti                           */
                )
{
    VOS_UINT32   ulCodeLen;                                                     /* ��������ĳ���                         */
    ST_SSP_MSG  *pstSsMsg;                                                      /* ����ָʾ�������õĽṹ                   */
    VOS_UINT8    ucMsgTi;

    ulCodeLen = 0;                                                              /* ��ʼ�������ĳ���                       */

    pstSsMsg = ( ST_SSP_MSG *)pSrc;                                             /* ��ȡ�������õĽṹ                       */

    ucMsgTi = GET_MSG_TI(ucTi);

    *(( VOS_UINT8 *)pDest + ulCodeLen ) =
        ( VOS_UINT8 )( NAS_PD_SS | ( ucMsgTi << 4 ));     /* ����PD��TI�ֽ�                           */

    ulCodeLen++;                                                                /* ���±����ĳ���                         */

    switch( ucMsgType )
    {                                                                           /* ����Ϣ���ͷַ�                           */
    case SS_MSG_REGISTER:                                                       /* IE: REGISTER                             */
        *(( VOS_UINT8 *)pDest + ulCodeLen ) = SS_MSG_REGISTER;                      /* ������Ϣ����                             */
        ulCodeLen++;                                                            /* ���±����ĳ���                         */
            ulCodeLen += Ss_EncodeRegister( &(pstSsMsg->SspmsgCore.u.BeginReq),
            ( VOS_UINT8 *)pDest +ulCodeLen );                                       /* ����REGISTER��Ϣ���뺯��                 */
        break;                                                                  /* ������֧                                 */
    case SS_MSG_FACILITY:                                                       /* IE: FACILITY                             */
        *(( VOS_UINT8 *)pDest + ulCodeLen ) = SS_MSG_FACILITY;                      /* ������Ϣ����                             */
        ulCodeLen++;                                                            /* ���±����ĳ���                         */
            ulCodeLen += Ss_EncodeFacility( &(pstSsMsg->SspmsgCore.u.FacilityReq),
            ( VOS_UINT8 *)pDest +ulCodeLen );                                       /* ����FACILITY��Ϣ���뺯��                 */
        break;                                                                  /* ������֧                                 */
    case SS_MSG_RELCMPL:                                                        /* IE: RELCMPL                              */
        *(( VOS_UINT8 *)pDest + ulCodeLen ) = SS_MSG_RELCMPL;                       /* ������Ϣ����                             */
        ulCodeLen++;                                                            /* ���±����ĳ���                         */
            ulCodeLen += Ss_EncodeRelCmpl( &(pstSsMsg->SspmsgCore.u.EndReq),
            ( VOS_UINT8 *)pDest +ulCodeLen );                                       /* ����REL CMPL��Ϣ���뺯��                 */
        break;                                                                  /* ������֧                                 */
    default:                                                                    /* ����IE                                   */
        SS_WARN_LOG( "\n [Error]Ss_Encode MsgType Error! \r" );
        break;                                                                  /* ������֧                                 */
    }
    return ulCodeLen;                                                           /* ���ر����ĳ���                         */
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

