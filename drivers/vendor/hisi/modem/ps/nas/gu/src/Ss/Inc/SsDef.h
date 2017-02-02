/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SsDef.h
  Description : �궨��
  History     :
      1.  ��־�� 2004.03.09   �°�����
*******************************************************************************/
#ifndef _SS_DEF_H_
#define _SS_DEF_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


/*******************************************************************************/
/**************************** �����궨�� ***************************************/
/*******************************************************************************/
#define  GET_MSG_TI(ti)             (((ti)>7)?  ((ti)-8):((ti)+8))

#define  Ss_MemSet(pBuf,Data,Len)   PS_NAS_MEM_SET(pBuf,Data,Len)                  /* �ڴ����ú���                             */
#define  Ss_MemCpy(pDst,pSrc,Len)   PS_NAS_MEM_CPY(pDst,pSrc,Len)                  /* �ڴ濽������                             */

#define SS_ASN_ENCODER(msg_id,p_msg_data,msg_data_size,p_enc_data_adr,p_data_size,p_pad_bits)   \
    per_encoder_ss(                                                                             \
                    msg_id,          /* �����ϢID�����ֵ��per_interface.h�ж��壩 */          \
                    p_msg_data,      /* �������ݵ�ַ�����������ݵ�ͷ��ַ��          */          \
                    msg_data_size,   /* �������ݳ��ȣ����������ݵĳ��ȣ�            */          \
                    p_enc_data_adr,  /* ������ݵ�ַ����������ݵ�ͷ��ַ��          */          \
                    p_data_size,     /* ������ݳ��ȣ���������ݵ�byte����          */          \
                    p_pad_bits )     /* padding��λ����bit����                      */
#define SS_ASN_ENC_SIZE_CALC(msg_id,p_msg_data,msg_data_size,p_enc_data_adr,p_data_size)        \
    per_enc_size_calculation_ss(                                                                \
                    msg_id,          /* �����ϢID�����ֵ��per_interface.h�ж��壩 */          \
                    p_msg_data,      /* �������ݵ�ַ�����������ݵ�ͷ��ַ��          */          \
                    msg_data_size,   /* �������ݳ��ȣ����������ݵĳ��ȣ�            */          \
                    p_enc_data_adr,  /* ������ݵ�ַ����������ݵ�ͷ��ַ��          */          \
                    p_data_size )    /* ������ݳ��ȣ���������ݵ�byte����          */
#define SS_ASN_DECODER(msg_id,p_msg_data,p_msg_data_size,p_dec_data_adr,data_size)              \
    per_decoder_ss(                                                                             \
                    msg_id,          /* �����ϢID�����ֵ��per_interface.h�ж��壩 */          \
                    p_msg_data,      /* ������ݵ�ַ����������ݵ�ͷ��ַ��          */          \
                    p_msg_data_size, /* ������ݳ��ȣ���������ݵ�byte����          */          \
                    p_dec_data_adr,  /* �������ݵ�ַ������ǰ���ݵ�ͷ��ַ��          */          \
                    data_size )      /* �������ݳ��ȣ�����ǰ����byte����            */
#define SS_ASN_DEC_SIZE_CALC(msg_id,p_msg_data,p_msg_data_size,p_dec_data_adr,data_size)        \
    per_dec_size_calculation_ss(                                                                \
                    msg_id,          /* �����ϢID�����ֵ��per_interface.h�ж��壩 */          \
                    p_msg_data,      /* ������ݵ�ַ����������ݵ�ͷ��ַ��          */          \
                    p_msg_data_size, /* ������ݳ��ȣ���������ݵ�byte����          */          \
                    p_dec_data_adr,  /* �������ݵ�ַ������ǰ���ݵ�ͷ��ַ��          */          \
                    data_size )      /* �������ݳ��ȣ�����ǰ����byte����            */
/*******************************************************************************/
/**************************** �����궨�� ***************************************/
/*******************************************************************************/

/*-----------------------------------------------------------------------------*/
/*----------------------------ʵ�����궨��-----------------------------------*/
/*-----------------------------------------------------------------------------*/

#define SS_MAX_ENTITY_NUM               15                                      /* SSʵ��������                           */
#define SS_M0_ENTITY_NUM                7                                       /* MOʵ��������                           */
#define SS_MT_ENTITY_NUM                7                                       /* MTʵ��������                           */
#define SS_NONE_TI                      16                                      /* û�ҵ�TI                                 */
#define SS_NONE_TAFID                   0                                       /* û�ҵ�TAF ID                             */
#define SS_NONE_CR                      0xff                                    /* û�ҵ�CR                                 */
#define SS_MO_CR_NUM                    0x7f                                    /* MO������ʹ�õ�CR��                       */
/*-----------------------------------------------------------------------------*/
/*----------------------------�տ���Ϣ����(24.080)-----------------------------*/
/*-----------------------------------------------------------------------------*/

/* �տ���Ϣ���� */
#define  SS_MSG_REGISTER                0x3b                                    /* REGISTER                                 */
#define  SS_MSG_FACILITY                0x3a                                    /* FACILITY                                 */
#define  SS_MSG_RELCMPL                 0x2a                                    /* RELEASE COMPLETE                         */

/*-----------------------------------------------------------------------------*/
/*----------------------------�տ���Ϣ��ʹ�õ�IEI(24.080)----------------------*/
/*-----------------------------------------------------------------------------*/
#define  SS_IEINONE                     0x00                                    /* ��IEI                                    */
#define  SS_IEICAUSE                    0x08                                    /* Cause ���IEI                            */
#define  SS_IEIFACILITY                 0x1C                                    /* Facility ���IEI                         */
#define  SS_IEISSPVERSION               0x7F                                    /* SS version ���IEI                       */
/*-----------------------------------------------------------------------------*/
/*----------------------------TAF-SS�ӿ�ԭ������-------------------------------*/
/*-----------------------------------------------------------------------------*/
#define  MNSS_BEGIN_REQ                 D_SMC_BEGIN_REQ                         /* MNSS_BEGIN_REQ                           */
#define  MNSS_FACILITY_REQ              D_SMC_FACILITY_REQ                      /* MNSS_FACILITY_REQ                        */
#define  MNSS_END_REQ                   D_SMC_END_REQ                           /* MNSS_END_REQ                             */
#define  MNSS_BEGIN_IND                 D_SMC_BEGIN_IND                         /* MNSS_BEGIN_IND                           */
#define  MNSS_FACILITY_IND              D_SMC_FACILITY_IND                      /* MNSS_FACILITY_IND                        */
#define  MNSS_END_IND                   D_SMC_END_IND                           /* MNSS_END_IND                             */
#define  MNSS_SS_STATUS_NTY             SSA_SS_STATUS_NTY                       /* MNSS_SS_STATUS_NTY                       */

/*-----------------------------------------------------------------------------*/
/*----------------------------�쳣��������-------------------------------------*/
/*-----------------------------------------------------------------------------*/
#define  SS_ERROR_MSG                   0x00                                    /* �տ���Ϣ��                               */
#define  SS_ERROR_STATE                 0x01                                    /* ״̬��                                   */
#define  SS_ERROR_TAFID                 0x02                                    /* TAF ID��                                 */
#define  SS_ERROR_ENCODE                0x03                                    /* �����                                   */
#define  SS_ERROR_DECODE                0x04                                    /* �����                                   */

/*-----------------------------------------------------------------------------*/
/*----------------------------TIMER����----------------------------------------*/
/*-----------------------------------------------------------------------------*/
#define  SS_T551                        0xF0                                    /* T551                                     */
#define  SS_T551_LEN                    180                                     /* T551ʱ��(��)                             */
#define  SS_MAX_MSG_LEN                 256                                     /* SS��Ϣ��󳤶�                           */

/*-----------------------------------------------------------------------------*/
/*----------------------------Cause Value--------------------------------------*/
/*-----------------------------------------------------------------------------*/
#define  SS_CAUSE_NORMAL_CALL_CLEARING              0x10                        /* Normal Call Clearing */
#define  SS_CAUSE_NORMAL_UNSPECIFIED                0x9f
#define  SS_CAUSE_INVALID_TI_VALUE                  0xd1                          /* invalid transaction identifier value             */
#define  SS_CAUSE_MSG_TYPE_ERR_OR_NOT_IMPLEMENT     0xe1                          /* message type non-existent or not implemented     */
#define  SS_CAUSE_MSG_NOT_COMPATIBLE_STATUS         0xe2                          /* message type not compatible with protocol state  */
#define  SS_CAUSE_RECOVERY_TIMER_EXPIRY             0xe6                         /* Recovery on timer expiry                         */
#define  SS_CAUSE_INVALID_MANDATORY_IE              0xe0

#define  LCS_MM_IE_PD_LOCATION_SRVC                 (12)                        /* Location services                        */
#define  LCS_IEICAUSE                               (0x10)                      /* Cause ���IEI                            */
#define  LCS_MSG_REGISTER                           (0x32)                      /* REGISTER                                 */
#define  LCS_MSG_RELCMPL                            (0x21)                      /* RELEASE COMPLETE                         */
#define  LCS_CAUSE_CODING_STANDARD_GSM              (0xE0)
#define  LCS_CAUSE_FACILITY_NOT_IMPLEMENTED         (0xC5)                      /* Requested facility not implemented       */

#define NAS_SS_MSG_SND_TO_SIDE_THAT_ORIGINATES_THE_TI (0x08)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
