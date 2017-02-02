/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasRlcInterface.h
  �� �� ��   : ����
  ��    ��   : ������
  ��������   : 2006��12��21��
  ����޸�   :
  ��������   : NasRlcInterface.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2006��12��21��
    ��    ��   : ������
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __NASRLCINTERFACE_H__
#define __NASRLCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"               /* _H2ASN_Skip */
#include "TtfDrvInterface.h"        /* _H2ASN_Skip */
#include "NasTtf_typedef.h"     /* _H2ASN_Include PsTypeDef.h */

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* ԭ���ʶ */
enum NAS_RLC_MSG_TYPE_ENUM
{
    ID_RLC_RABM_CS_DATA_IND  =  0x0001, /* _H2ASN_MsgChoice RLC_RABM_CS_DATA_IND_STRU */

    ID_RABM_RLC_AM_DATA_REQ  =  0x0000, /* _H2ASN_MsgChoice RABM_RLC_AM_DATA_REQ_STRU */
    ID_RABM_RLC_UM_DATA_REQ  =  0x0002, /* _H2ASN_MsgChoice RABM_RLC_UM_DATA_REQ_STRU */
    ID_RABM_RLC_TM_DATA_REQ  =  0x0004, /* _H2ASN_MsgChoice RABM_RLC_TM_DATA_REQ_STRU */
    ID_TC_RLC_TEST_IND       =  0x0006, /* _H2ASN_MsgChoice TC_RLC_TEST_IND_STRU */

    ID_NAS_RLC_MSG_TYPE_BUTT
};
typedef VOS_UINT16 NAS_RLC_MSG_TYPE_ENUM_UINT16;


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
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* message name */ /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* �����ϲ�PDUʹ�õ�RB��, Vaule: [5, 32] */
    VOS_UINT8                           aucReserve[3];      /* ���ֽڶ��룬���� */
    VOS_UINT16                          usDataBitLen;       /* �ϲ�PDU���ݳ���, ��λ: Bit */
    TTF_MEM_ST                         *pstDataMem;         /* RLC SDU */ /* _H2ASN_Replace VOS_UINT32 *ppstDataMem */
} RABM_RLC_AM_DATA_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* message name */ /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* �����ϲ�PDUʹ�õ�RB��, Value: 5-32 */
    VOS_UINT8                           aucReserve[3];      /* ���ֽڶ��룬���� */
    VOS_UINT16                          usDataBitLen;       /* �ϲ�PDU���ݳ���, ��λ: Bit */
    TTF_MEM_ST                         *pstDataMem;         /* RLC SDU */ /* _H2ASN_Replace VOS_UINT32 *ppstDataMem */
} RABM_RLC_UM_DATA_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* message name */ /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* �����ϲ�PDUʹ�õ�RB��, Value: 0, 5-32 */
    VOS_UINT8                           aucReserve[3];      /* ���ֽڶ��룬���� */
    VOS_UINT16                          usDataBitLen;       /* �ϲ�PDU���ݳ���, ��λ: Bit */
    TTF_MEM_ST                         *pstDataMem;         /* RLC SDU */ /* _H2ASN_Replace VOS_UINT32 *ppstDataMem */
} RABM_RLC_TM_DATA_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /* message name */ /* _H2ASN_Skip */
    VOS_UINT8                           ucRbId;             /* RB��ʶ, Value: 5-32 */
    VOS_UINT8                           aucReserve1[1];      /* ���ֽڶ��룬���� */
    DL_DATA_CRC_INFO_STRU               stCrcInfo;
    VOS_UINT16                          usDataBitLen;       /* ���ݵĳ���, ��λ: Bit */
    VOS_UINT8                           aucReserve2[2];      /* ���ֽڶ��룬���� */
    VOS_UINT8                           *pucData;           /* �����׵�ַ */
} RLC_RABM_CS_DATA_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /*��Ϣͷ*/ /* _H2ASN_Skip */
    NAS_RLC_MSG_TYPE_ENUM_UINT16        enMsgName;          /*��Ϣ����*/ /* _H2ASN_Skip */
    TEST_LOOP_TYPE_ENUM_UINT8           enTcMode;           /*���Ի���ģʽ���ͣ�ֻҪ��enTcAct=TEST_MODE_ACTIVE��ʱ��������*/
    VOS_UINT8                           aucReserve[1];      /* ���ֽڶ��룬���� */
} TC_RLC_TEST_IND_STRU;

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
    NAS_RLC_MSG_TYPE_ENUM_UINT16        enMsgID;    /*_H2ASN_MsgChoice_Export NAS_RLC_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_RLC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}NAS_RLC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_RLC_MSG_DATA                    stMsgData;
}NasRlcInterface_MSG;

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 WTTF_RLC_GetRbSuitableUlPduSize(VOS_UINT8  ucRbId   ,VOS_UINT32 ulPduSize,
                                      VOS_UINT8  ucCrcSize,VOS_UINT32 *pulUlPduSize);


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

#endif /* end of NasRlcInterface.h */
