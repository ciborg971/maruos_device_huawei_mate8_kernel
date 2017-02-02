#ifndef __TAF_TAFM_LOCAL_H__
#define __TAF_TAFM_LOCAL_H__

/*============================================================================*/

/******************************************************************************/
/* Copyright (c) ,1988-2001,Huawei Tech. Co.,Ltd                              */
/* File name     :TafDef.h                                                    */
/* Author        :zzy                                                         */
/* Description   :TAFM����ģ���ڲ����ݽṹ����ͷ�ļ�                          */
/* Others        :                                                            */
/* Function List :                                                            */
/* History       :                                                            */
/*               :2005-04-13 ����                                             */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*========================================================*/

/*��Ϣ���ٿ���*/
#define    TAF_TRACE_OFF   0    /*�رո���*/
#define    TAF_TRACE_ON    1    /*�򿪸���*/

/*��Ϣ���ٷ���*/
#define    TAF_MSG_RECV    0    /*TAF���յ���Ϣ*/
#define    TAF_MSG_SEND    1    /*TAF���͵���Ϣ*/

/*TAF�ܱ�ģ��ӿ�����*/
#define    TAF_APP      0
#define    TAF_AT       1
#define    TAF_CC       2
#define    TAF_SM       3
#define    TAF_MMC      4
#define    TAF_SMS      5
#define    TAF_RRC      6
#define    TAF_AMR      7

#define  TAF_INVALID_TAB_INDEX         0

/*ATʹ�õ�����IDֵ��TAF��ֵ������AT����APP*/
#define  TAF_AT_CALL_ID                0
#define  TAF_AT_OP_ID                  0
#define  TAF_AT_SMI                    0

/*SPEECH TI:0-6, 8-14*/
/*APS TI:0-6, 8-14*/
/*SMA TI:0-6*/
/*STATUS TI:0-1*/
#define  TAF_MAX_CCA_TI       14
#define  TAF_MAX_SMA_TI       6
#define  TAF_MAX_STATUS_TI    1


/*CC/SS/SMģ��MTʱ��СCrֵ*/
#define  TAF_MT_MIN_CR            128

#define  TAF_MAX_RABM_DATA_LEN    4096

#define  TAF_SELF_TASK_STACK_SIZE    (5120)


/*TAF�ڲ���Ϣ��ͷ�ṹ*/
typedef struct
{
    VOS_UINT8    ucMsgType;
    VOS_UINT8    ucSubMsgType;
    VOS_UINT8    ucClientId2;   /*���ֽ�ClientId���ֽ�*/
    VOS_UINT8    ucCilentId1;   /*���ֽ�ClientId���ֽ�*/
    VOS_UINT8    ucId;          /*CallId,OpId,Smi*/
    VOS_UINT8    ucIeMask2;     /*IE���������λ�����ֽ�IeMask������ֽ�*/
    VOS_UINT8    ucIeMask1;     /*IE���������λ�����ֽ�IeMask������ֽ�*/
}TAF_INNER_MSG_HEADER_STRU;

#define TAF_INNER_MSG_HEADER    \
        VOS_UINT8    ucMsgType;     \
        VOS_UINT8    ucSubMsgType;  \
        VOS_UINT8    ucClientId1;   \
        VOS_UINT8    ucCilentId2;   \
        VOS_UINT8    ucId;          \
        VOS_UINT8    ucIeMask2;     \
        VOS_UINT8    ucIeMask1;


/*SME��ַ����*/
typedef enum
{
    TAF_SME_ADDR_UNKNOWN,
    TAF_SME_ADDR_INTERNATIONAL,
    TAF_SME_ADDR_NATIONAL,
    TAF_SME_ADDR_NETWORK_SPEC,
    TAF_SME_ADDR_SUBSCRIBER,
    TAF_SME_ADDR_ALPHA,
    TAF_SME_ADDR_ABBREVIATED
}TAF_SME_ADDR_TYPE_ENUM;


#define TAF_USIM_READ    0   /*TAF��ȡUSIM�Ĳ���*/
#define TAF_USIM_MODIFY  1   /*TAF�޸�USIM�Ĳ���*/
#define TAF_SMSP_EFID    0x6F42  /*EFsmsp��ID*/

/*========================================================*/
#ifdef __cplusplus
}
#endif
/******************************************************************************/

/*============================================================================*/
#endif          /* __TAF_LOCAL_DEF_H__ */

