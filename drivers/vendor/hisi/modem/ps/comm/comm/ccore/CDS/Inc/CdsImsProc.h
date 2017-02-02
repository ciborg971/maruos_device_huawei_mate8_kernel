

#ifndef __CDS_IMS_PROC_H__
#define __CDS_IMS_PROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "CdsSoftFilter.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CDS_IMS_MIN_SPEECH_FRM   84


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*����*/
#define CDS_TRACE_PKT_TO_PC_MASK            (0x01)
#define CDS_TRACE_PKT_TO_OM_MASK            (0x02)

#define CDS_IMS_DL_FRAGMENT_BUFF_SIZE       (50)            /*CDS IMS ���з�Ƭ������*/

/*****************************************************************************
   5 STRUCT����
*****************************************************************************/


/*****************************************************************************
 �ṹ��    : CDS_IMS_SDU_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMS SDU�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRabId;            /* RAB IDֵ */
    VOS_UINT8                           ucDrbId;            /* DRB ID*/
    VOS_UINT8                           aucRev[2];          /* ����λ */
    VOS_UINT32                          ulSduLen;           /* ���ݳ��� */
    TTF_MEM_ST                         *pstSdu;             /* ����������ָ�� */
}CDS_IMS_SDU_STRU;


/*****************************************************************************
 �ṹ��    : CDS_IMS_DL_FRAGMENT_BUFF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMS ���з�Ƭ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulIndex;
    CDS_IP_DATA_INFO_STRU              astIpPktInfo[CDS_IMS_DL_FRAGMENT_BUFF_SIZE];
}CDS_IMS_DL_FRAGMENT_BUFF_STRU;

extern CDS_IMS_DL_FRAGMENT_BUFF_STRU    g_stCdsImsDlFragInfoBuff;

#define CDS_IMS_GET_DL_FRAGMENT_BUFF()  (&g_stCdsImsDlFragInfoBuff)

/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  8 ��������
*****************************************************************************/
extern VOS_UINT32 CDS_IsImsBearer(VOS_UINT8 ucRabId,const CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID   CDS_DlProcImsData(CDS_IMS_SDU_STRU *pstSdu, const CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID   CDS_IMSA_MsgProc(MsgBlock  *pstMsg);
extern VOS_VOID   CDS_UlProcImsData(MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_UINT8 CDS_JudgIpPktType(VOS_UINT8 ucRabId, const CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST *pstIpPkt);


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

