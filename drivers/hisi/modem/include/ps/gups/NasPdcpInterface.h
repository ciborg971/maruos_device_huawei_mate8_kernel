/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasPdcpInterface.h
  �� �� ��   : ����
  ��    ��   : ������
  ��������   : 2006��11��30��
  ����޸�   :
  ��������   : NasPdcpInterface.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2006��11��30��
    ��    ��   : ������
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __NASPDCPINTERFACE_H__
#define __NASPDCPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "WUeSpec.h"
#include "TtfDrvInterface.h"                                                           /* _H2ASN_Skip */
#include "NasTtf_typedef.h"

/* _H2ASN_Include PsTypeDef.h */

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define PS_NSAPI_NUM  16


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* ԭ���ʶ */
enum NAS_PDCP_MSG_TYPE_ENUM
{
    ID_RABM_PDCP_DATA_REQ           =   0x0013,             /* _H2ASN_MsgChoice RABM_PDCP_DATA_REQ_STRU */
    ID_PDCP_RABM_DATA_IND           =   0x0014,             /* _H2ASN_MsgChoice */ /* Ŀǰ��������ֱ����API�������͸���Ϣ */

    ID_RABM_PDCP_DATA_RESUME_IND    =   0x0015,             /* _H2ASN_MsgChoice RABM_PDCP_DATA_RESUME_IND_STRU*/
    ID_PDCP_RABM_DATA_RESUME_RSP    =   0x0016,             /* _H2ASN_MsgChoice PDCP_RABM_DATA_RESUME_RSP_STRU*/

    ID_RABM_PDCP_SAVE_DATA_IND      =   0x0017,             /* _H2ASN_MsgChoice RABM_PDCP_SAVE_DATA_IND_STRU*/
    ID_PDCP_RABM_SAVE_DATA_RSP      =   0x0018,             /* _H2ASN_MsgChoice PDCP_RABM_SAVE_DATA_RSP_STRU */

    ID_RABM_PDCP_TC_DATA_REQ        =   0x0019,             /* _H2ASN_MsgChoice RABM_PDCP_TC_DATA_REQ_STRU */
    ID_PDCP_RABM_TC_DATA_IND        =   0x001A,             /* _H2ASN_MsgChoice PDCP_RABM_TC_DATA_IND_STRU */

    ID_PDCP_RABM_TC_DATA_IND_NOTIFY =   0x001C,             /* _H2ASN_MsgChoice PDCP_RABM_TC_DATA_IND_NOTIFY_STRU */

    ID_RABM_PDCP_TRACE_DATA_REQ     =   0x8013,             /* _H2ASN_MsgChoice RABM_PDCP_TRACE_DATA_REQ_STRU */
    ID_PDCP_RABM_TRACE_DATA_IND     =   0x8014,             /* _H2ASN_MsgChoice PDCP_RABM_TRACE_DATA_IND_STRU */

    ID_RABM_PDCP_TRACE_TC_DATA_REQ  =   0x8019,             /* _H2ASN_MsgChoice RABM_PDCP_TRACE_DATA_REQ_STRU */
    ID_PDCP_RABM_TRACE_TC_DATA_IND  =   0x801A,             /* _H2ASN_MsgChoice PDCP_RABM_TRACE_DATA_IND_STRU */

    ID_NAS_PDCP_MSG_TYPE_BUTT
} ;
typedef VOS_UINT16 NAS_PDCP_MSG_TYPE_ENUM_UINT16;

enum RABMPDCPITF_RSLT_ENUM
{
    RABMPDCPITF_SUCC                         = 0,
    RABMPDCPITF_FAIL                         ,
    RABMPDCPITF_RSLT_BUTT
};
typedef VOS_UINT32   RABMPDCPITF_RSLT_ENUM_UINT32;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/******************************************************************************
*     RABM_PDCP_DATA_REQ_STRU ԭ�ﶨ��
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* [5,32],��־PDCPʵ�� */
    VOS_UINT8                           aucReserve[1];      /* 4�ֽڶ��룬����*/
    VOS_UINT32                          ulDataBitLen;
    TTF_MEM_ST                         *pstDataMem;         /* PDCP SDU��ַ */  /* _H2ASN_Replace VOS_UINT32 *pstDataMem */
}RABM_PDCP_DATA_REQ_STRU;



/******************************************************************************
*     PDCP_RABM_DATA_IND_STRU ԭ�ﶨ�壬��Ϊʹ�ú����ӿڣ�
                              �ýṹֻ��RABMʹ�ã�PDCP��ʹ��
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* [5,32] ��ʶ���RB ID��Ӧ��PDCPʵ��*/
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬����*/
    VOS_UINT32                          ulDataLen;
    TTF_MEM_ST                         *pstDataMem;        /* PDCP SDU��ַ */  /* _H2ASN_Replace VOS_UINT32 *pstDataMem */
} PDCP_RABM_DATA_IND_STRU;

/******************************************************************************
*     RABM_PDCP_TC_DATA_REQ_STRU ԭ�ﶨ��
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* [5,32],��־PDCPʵ�� */
    VOS_UINT8                           aucReserve[1];      /* 4�ֽڶ��룬����*/
    VOS_UINT32                          ulDataBitLen;       /* ��λ:bit����AM,UM,TM������Чֵ*/
    TTF_MEM_ST                         *pstDataMem;         /* PDCP SDU��ַ */  /* _H2ASN_Replace VOS_UINT32 *pstDataMem */
}RABM_PDCP_TC_DATA_REQ_STRU;



/******************************************************************************
*     PDCP_RABM_TC_DATA_IND_STRU ԭ�ﶨ�壬����PS�򻷻ع����������ݽӿ�
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* [5,32] ��ʶ���RB ID��Ӧ��PDCPʵ��*/
    VOS_UINT8                           aucReserve1[1];     /* 4�ֽڶ��룬����*/
    DL_DATA_CRC_INFO_STRU               stCrcInfo;          /* Crc��Ϣ��ֻ��PS�򻷻�ģʽ��ʹ��,PS�򻷻�ģʽһ�����ĸ�����  */
    VOS_UINT32                          ulDataBitLen;       /* ���ݵĳ��ȣ���λ: Bit����Ϊ���أ��п������ݳ��ȷ������ֽ� */
    TTF_MEM_ST                         *pstDataMem;        /* PDCP SDU��ַ */  /* _H2ASN_Replace VOS_UINT32 *pstDataMem */
} PDCP_RABM_TC_DATA_IND_STRU;

/******************************************************************************
*     PDCP_RABM_TC_DATA_Q_NODE_STRU ԭ�ﶨ�壬����PS�򻷻ع����������ݽ��
******************************************************************************/
typedef struct
{
    TTF_NODE_ST                         stQNode;
    VOS_UINT8                           ucRbId;             /* [5,32] ��ʶ���RB ID��Ӧ��PDCPʵ��*/
    VOS_UINT8                           aucReserve[3];      /* 4�ֽڶ��룬����*/
    DL_DATA_CRC_INFO_STRU               stCrcInfo;          /* Crc��Ϣ��ֻ��PS�򻷻�ģʽ��ʹ��,PS�򻷻�ģʽһ�����ĸ�����  */
    VOS_UINT32                          ulDataBitLen;       /* ���ݵĳ��ȣ���λ: Bit����Ϊ���أ��п������ݳ��ȷ������ֽ� */
    TTF_MEM_ST                         *pstDataMem;         /* PDCP SDU��ַ */  /* _H2ASN_Replace VOS_UINT32 *pstDataMem */
} PDCP_RABM_TC_DATA_Q_NODE_STRU;

/******************************************************************************
*     PDCP_RABM_DATA_BUF_STRU
******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           ucRcvNPduNum;       /*RCV NPDU NUM*/
    VOS_UINT8                           aucReserve[2];
} PDCP_NUM_INFO;

typedef struct
{
    PS_BOOL_ENUM_UINT8                  enValidInd;         /* PS_FALSE:��ǰNSAPI��Ч   PS_TRUE:��ǰNSAPI��Ч */
    VOS_UINT8                           ucRbId;             /* ��RAB����Ӧ��RbId */
    VOS_UINT8                           aucReserve[2];      /* 4�ֽڶ��룬���� */
}PDCP_NSAPI_MAP_RB_INFO;

/******************************************************************************
*     RABM_PDCP_DATA_RESUME_IND ԭ�ﶨ��
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    PDCP_NSAPI_MAP_RB_INFO              astNsapiMapRb[PS_NSAPI_NUM];  /*��������ֵΪNSAPI*/
    VOS_UINT8                           aucReserve[2];      /* 4�ֽڶ��룬���� */
}RABM_PDCP_DATA_RESUME_IND_STRU;

/******************************************************************************
*     PDCP_RABM_DATA_RESUME_RSP ԭ�ﶨ��
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[2];      /* 4�ֽڶ��룬���� */
    RABMPDCPITF_RSLT_ENUM_UINT32        enResult;
}PDCP_RABM_DATA_RESUME_RSP_STRU;

/******************************************************************************
*     RABM_PDCP_SAVE_DATA_IND ԭ�ﶨ��
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[2];      /* 4�ֽڶ��룬���� */
}RABM_PDCP_SAVE_DATA_IND_STRU;

/******************************************************************************
*     PDCP_RABM_SAVE_DATA_RSP ԭ�ﶨ��
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           ucRbCnt;            /* RB ���� */
    VOS_UINT8                           aucReserve[1];
    PDCP_NUM_INFO                       astPdcpNumInfo[PS_WUE_MAX_PS_RB_NUM]; /* PDCP ������Ϣ�ṹ�� */
} PDCP_RABM_SAVE_DATA_RSP_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgID;    /*_H2ASN_MsgChoice_Export NAS_PDCP_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_PDCP_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}NAS_PDCP_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_PDCP_MSG_DATA                   stMsgData;
}NasPdcpInterface_MSG;



/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_UINT32 RABM_EnqueueTcData(PDCP_RABM_TC_DATA_Q_NODE_STRU *pstNode);
VOS_UINT32 WTTF_PDCP_RcvRabmData(VOS_UINT8 ucRbId, TTF_MEM_ST *pstData, VOS_UINT32 ulDataBitLen);
VOS_VOID  WTTF_PDCP_TrigRlcUlProc(VOS_VOID);




#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasPdcpInterface.h */
