/*******************************************************************************
  Copyright   : 2005-2010, Huawei Tech. Co., Ltd.
  File name   : SNInterface.h
  Version     : V200R001
  Date        : 2005-06-16
  Description : ��ͷ�ļ�������SNDCPģ�����ӿ�
  History     :
  1. Date:2005-06-16
     Author: w29695
     Modification:Create
  2.��    ��   : 2006��08��09��
    ��    ��   : ����Ƽj60010247
    �޸�����   : ���ⵥA32D03479����PC����ʵ��ʱ��#pragma pack(0)��#pragma pack()�ӱ��뿪��
*******************************************************************************/
#ifndef __SN_INTERFACE_H__
#define __SN_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#include "vos.h"
#include "TTFCause.h"
#include "TTFMem.h"

/*******************************************************************************
�궨��
*******************************************************************************/
#define ID_SN_XID_REQ                   0x0101
#define ID_SN_XID_RSP                   0x0102
#define ID_SN_XID_IND                   0x0103
#define ID_SN_XID_CNF                   0x0104

#define ID_SN_DATA_REQ                  0x0110
#define ID_SN_DATA_IND                  0x0111  /*ĿǰNAS�ܹ��Ż����ݲ�ʹ�ø���Ϣ����*/
#define ID_SN_UNITDATA_REQ              0x0112
#define ID_SN_UNITDATA_IND              0x0113  /*ĿǰNAS�ܹ��Ż����ݲ�ʹ�ø���Ϣ����*/

#define ID_SM_ACT_IND                   0x0121
#define ID_SM_ACT_RSP                   0x0122
#define ID_SM_DEACT_IND                 0x0123
#define ID_SM_DEACT_RSP                 0x0124
#define ID_SM_MODIFY_IND                0x0125
#define ID_SM_MODIFY_RSP                0x0126
#define ID_SN_RABM_SEQUENCE_IND         0x0127
#define ID_SN_RABM_SEQUENCE_RSP         0x0128

#define ID_SM_STATUS_REQ                0x0130

#define ID_RABM_SNDCP_SAVE_DATA_IND     0x0140
#define ID_RABM_SNDCP_SAVE_DATA_RSP     0x0141
#define ID_RABM_SNDCP_RESUME_DATA_IND   0x0142
#define ID_RABM_SNDCP_RESUME_DATA_RSP   0x0143

#define ID_SN_RESUME_ABM_IND            0x0144 /* GTTFģ���ڲ�ʹ�õ���Ϣ*/

/*******************************************************************************
�ṹ����
*******************************************************************************/
#pragma pack(4)

/* SN_DATA_REQ_STΪNAS�û���ܹ��Ż�ǰ�ĺ�����ʹ�õĽṹ���ڼܹ��Ż����PS��
����ʹ�ã������ڸú�����GCF����ʱ�����һ��AT����(AT^TRIG)��ʹ�ã����Ծɱ���*/
typedef struct
{
    /*0         Escape mechanism for future extensions.
    1           Point-to-Multipoint Multicast (PTM-M) information for Multimedia Broadcast/Multicast Service (MBMS).
    2-4         Reserved for future use.
    5-15        Dynamically allocated NSAPI value (see subclause 6.1).*/
    VOS_UINT8       ucNsapi;
#define SN_DATA_REQ_MASK_PDU            0x80
    VOS_UINT8       ucMask;                     /*b0000000  bΪ0:��pdu number, 1:��*/
    VOS_UINT16      usRsv;                      /*���ֽڲ���*/
    VOS_UINT16      usPduNum;                   /*N PDU number - acknowledged mode:    0-255    N PDU number - unacknowledged mode:    0-4095*/
    VOS_UINT16      usDataLen;                  /*NDPU�����ݳ���*/
    void           *pPdu;
}SN_DATA_REQ_ST;

typedef struct
{
    VOS_UINT8       ucNsapi;
    VOS_UINT8       ucRsv;                      /*���ֽڲ���*/
    VOS_UINT16      usDataLen;
    void           *pPdu;
}SN_UNITDATA_REQ_ST;


typedef struct
{
#define SN_XID_PARA_P_CMPR              0x80
#define SN_XID_PARA_D_CMPR              0x40

#define SN_1144_ALGRTH                  0
#define SN_2507_ALGRTH                  1
#define SN_ROHC_ALGRTH                  2

#define SN_V42_ALGRTH                   0
#define SN_V44_ALGRTH                   1

    VOS_UINT8       ucMask;                     /*0��ʾû�У�1��ʾ��    bit7��ʾЭ��ѹ������    bit6��ʾ����ѹ������*/
    VOS_UINT8       ucPCmprAlgrth;              /*RFC 1144  0    RFC 2507    1    ROHC        2*/
    VOS_UINT8       ucDCmprAlgrth;              /*V.42 bis  0      V.44      1*/
    VOS_UINT8       ucRsv;                      /*���ֽڲ���*/
}SN_XID_REQ_ST;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgType;
    VOS_UINT16      usPId;                      /*��ucNsapi;��Χ�������SN_DATA_REQ_ST�е�˵��    ���ֶ�����Ϣ�����ӽ��̱�ʾ*/
    SN_XID_REQ_ST   stXid;
}SN_XID_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgType;
    VOS_UINT16      usPId;                      /*��ucNsapi;��Χ�������SN_DATA_REQ_ST�е�˵��    ���ֶ�����Ϣ�����ӽ��̱�ʾ*/
    SN_XID_REQ_ST   stXid;
}SN_XID_RSP_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgType;
    VOS_UINT16      usPId;                      /*��ucNsapi;��Χ�������SN_DATA_REQ_ST�е�˵��    ���ֶ�����Ϣ�����ӽ��̱�ʾ*/
    SN_XID_REQ_ST   stXid;
}SN_XID_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgType;
    VOS_UINT16      usPId;                      /*��ucNsapi;��Χ�������SN_DATA_REQ_ST�е�˵��    ���ֶ�����Ϣ�����ӽ��̱�ʾ*/
    SN_XID_REQ_ST   stXid;
}SN_XID_CNF_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16  usMsgType;                          /*��Ϣ����*/
    VOS_UINT16  usPId;                              /*NSAPI �ӽ��̱�ʶ,���ڶ�λ�ӽ���*/
    VOS_UINT16  usPduLen;
    VOS_UINT16  usRsv;
    TTF_MEM_ST *pMemPt;                             /*������ڴ�ָ��*/
}SN_UNITDATA_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16  usMsgType;
    VOS_UINT16  usPId;                              /*NSAPI �ӽ��̱�ʶ,���ڶ�λ�ӽ���*/
    VOS_UINT8   ucMask;
    VOS_UINT8   ucRsv;
    VOS_UINT16  usPduNum;
    VOS_UINT16  usPduLen;
    VOS_UINT16  usRsv;
    TTF_MEM_ST *pMemPt;                             /*������ڴ�ָ��*/
}SN_DATA_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgType;      /*��Ϣ����*/
    VOS_UINT16      usTransId;      
} SN_RESUME_ABM_IND_MSG;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/*******************************************************************************
�����ṩ�ĺ�������
*******************************************************************************/
VOS_UINT32 SN_DataReq       (SN_DATA_REQ_ST     *pData);    /*ȷ�����ݴ�������ӿ��������ֵ��ΪVOS_OK�����ʾû�з��ͳɹ�*/
VOS_UINT32 SN_UnitDataReq   (SN_UNITDATA_REQ_ST *pData);    /*��ȷ�����ݴ�������ӿ��������ֵ��ΪVOS_OK�����ʾû�з��ͳɹ�*/
VOS_VOID SN_RabmClear2G3Share(VOS_VOID);                            /*2G��3G�л������쳣ʱ��RABM���SNDCP��PDCP֮���NPDU����ȫ�ֱ���*/
VOS_VOID SN_RabmClear3G2Share(VOS_VOID);                            /*3G��2G�л������쳣ʱ��RABM���SNDCP��PDCP֮���NPDU����ȫ�ֱ���*/




/******************************************************************************/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


