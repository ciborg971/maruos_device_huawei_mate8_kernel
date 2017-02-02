

#ifndef __CDS_DLPROC_H__
#define __CDS_DLPROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "CdsDepend.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*�洢RABID��SDU LEN��TTF��������*/
/*lint -emacro({717}, CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF)*/
/*lint -emacro({701}, CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF)*/
#define CDS_DL_SAVE_LEN_MODEMID_RABID_TO_TTF(pstIpPkt,usLen,usModemId,ucRabId) \
                    do\
                    {\
                        (pstIpPkt)->ulForCds[0] = 0;\
                        (pstIpPkt)->ulForCds[0] = ((usModemId) << 8) | ucRabId;\
                        (pstIpPkt)->ulForCds[0] = ((usLen) << 16) | ((pstIpPkt)->ulForCds[0]);\
                    }while(0)

/*��TTF�������л�ȡModemId/RABID*/
#define CDS_DL_GET_MODEMID_RABID_FROM_TTF(pstTtfMem)\
                    (VOS_UINT16)((pstTtfMem)->ulForCds[0] & 0x0000FFFF)

/*��TTF��������ȡSdu Len*/
#define CDS_DL_GET_PKT_LEN_FROM_TTF(pstTtfMem)      \
                    (VOS_UINT16)(((pstTtfMem)->ulForCds[0]) >> 16)

/*��TTF��������ȡModemId*/
#define CDS_DL_GET_MODEMID_FROM_TTF(pstTtfMem)      \
                    (VOS_UINT8)(((pstTtfMem)->ulForCds[0] & 0x0000FF00) >> 8)

/*��TTF��������ȡRABID*/
#define CDS_DL_GET_RABID_FROM_TTF(pstTtfMem)        \
                    (VOS_UINT8)((pstTtfMem)->ulForCds[0] & 0x000000FF)


/*����CDS���н���SDU����󳤶�*/
#define CDS_DL_SDU_MAX_LEN               (1536)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
   5 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : CDS_CDMA_TRANS_DATA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS CDMA�������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulSduLen;
    TTF_MEM_ST                         *pstSdu;
}CDS_CDMA_TRANS_DATA_STRU;



/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  8 ��������
*****************************************************************************/
extern VOS_VOID   CDS_LTE_RecvDbgData(TTF_MEM_ST *pstIpPkt);
extern VOS_UINT32 CDS_GUGetDefaultRabId(VOS_UINT8 ucRabId, VOS_UINT8 *pucDeftRabId, MODEM_ID_ENUM_UINT16 enModemId);
VOS_UINT32 I1_NAS_RABM_GetDefaultRabId(VOS_UINT8 ucRabId, VOS_UINT8 *pucDeftRabId);
VOS_UINT32 I2_NAS_RABM_GetDefaultRabId(VOS_UINT8 ucRabId, VOS_UINT8 *pucDeftRabId);

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

