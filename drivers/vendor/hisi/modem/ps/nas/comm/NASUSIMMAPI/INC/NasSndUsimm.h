/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasSndUsimm.h
  �� �� ��   : ����
  ��    ��   : h00313353
  ��������   : 2015��01��26��
  ����޸�   :
  ��������   : ��NAS USIM API���õ���USIMM������Ϣ�Ľӿ��ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��01��26��
    ��    ��   : h00313353
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _NAS_SNDUSIMM_H_
#define _NAS_SNDUSIMM_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "siapppb.h"
#include "siappstk.h"
#include "UsimPsInterface.h"
#include "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_SI_STK_ENVELOPEDOWN_ENCODE (1)
#define MAX_FILE_LENGTH (65535)
#define MIN_FILE_LENGTH (1)
#define BITS_OF_ONE_BYTE (8)
#define RECEIVERID_NOT_FOUND (0xFFFFF)
#define NAS_USIMM_UPDATEFILE_STRU_ARRAY_LENGTH (3)
#define NAS_SI_PB_ECALLQRY_REQ_STRU_ARRAY_LENGTH (3)
#define MAX_VALUE_OF_ONE_BYTE (255)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_USIMM_SVLTE_TYPE_ENUM_UINT8
 �ṹ˵��  : svlte�Ƿ�֧�ֱ�ʶ
  1.��    ��   : 2015��01��27��
    ��    ��   : h00313353
    �޸�����   : Create
*****************************************************************************/
enum NAS_USIMM_SVLTE_TYPE_ENUM
{
    NAS_USIMM_SVLTE_TYPE_NOT_SUPPORT    = 0x00,
    NAS_USIMM_SVLTE_TYPE_SUPPORT        = 0x01,

    NAS_USIMM_SVLTE_TYPE_BUTT
};

typedef VOS_UINT8 NAS_USIMM_SVLTE_TYPE_ENUM_UINT8;

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
  7 �ṹ�嶨��
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : NAS_USIMM_UPDATEFILE_INFO_STRU
 �ṹ˵��  : �����ļ�

 1.��    ��   : 2015��02��03��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* Ӧ������ */
    VOS_UINT16                  usEfId;         /* �ļ�ID */
    VOS_UINT8                   ucRecordNum;    /* �ļ���¼�ţ��������ļ���0 */
    VOS_UINT8                   ucRsv;          /* ���� */
    VOS_UINT32                  ulEfLen;        /* �������ݳ��� */
    VOS_UINT8                  *pucEfContent;   /* ������������ */
}NAS_USIMM_UPDATEFILE_DATA_STRU;

/*****************************************************************************
 �ṹ��    : NAS_USIMM_GETFILE_INFO_STRU
 �ṹ˵��  : ��ȡ�ļ�

 1.��    ��   : 2015��02��03��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* Ӧ������ */
    VOS_UINT16                  usEfId;         /* �ļ�ID */
    VOS_UINT8                   ucRecordNum;    /* �ļ���¼�ţ��������ļ���0 */
    VOS_UINT8                   ucRsv;          /* ���� */
}NAS_USIMM_GETFILE_DATA_STRU;

/*****************************************************************************
 �ṹ��    : NAS_USIMM_AUTH_DATA_STRU
 �ṹ˵��  : ��Ȩ����

 1.��    ��   : 2015��02��03��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
typedef struct
{
    USIMM_AUTH_TYPE_ENUM_UINT32         enAuthType;
    USIMM_AUTH_DATA_UNION               unAuthPara;
}NAS_USIMM_AUTH_DATA_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 NAS_SNDUSIMM_IsSvlteSupported(
    VOS_VOID
);

VOS_VOID NAS_SNDUSIMM_ReadSvlteSupportFlagNvim(
    VOS_VOID
);

NAS_USIMM_SVLTE_TYPE_ENUM_UINT8 NAS_SNDUSIMM_GetSvlteSupportFlag(
    VOS_VOID
);

VOS_VOID NAS_SNDUSIMM_SetSvlteSupportFlag(
    NAS_USIMM_SVLTE_TYPE_ENUM_UINT8     enSvlteSupportFlag
);

VOS_UINT32 NAS_SndUsimmUpdateFileReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    NAS_USIMM_UPDATEFILE_DATA_STRU     *pstSetFileInfo
);

VOS_UINT32 NAS_SndUsimmReadFileReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    NAS_USIMM_GETFILE_DATA_STRU        *pstGetFileInfo
);

VOS_UINT32 NAS_SndUsimmAuthReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    NAS_USIMM_AUTH_DATA_STRU           *pstAuth,
    VOS_UINT8                           ucOpId
);

VOS_UINT32 NAS_SndUsimmPinReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT8                           ucCmdType,
    VOS_UINT8                           ucPINType,
    VOS_UINT8                          *pucOldPIN,
    VOS_UINT8                          *pucNewPIN
);

VOS_UINT32 NAS_SndUsimmFdnNumCheckReq(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulContextIndex,
    VOS_UINT32                          ulSendPara,
    SI_PB_FDN_NUM_STRU                 *pstFdnInfo
);

VOS_UINT32 NAS_SndUsimmQueryFileReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEFid
);

VOS_UINT32 NAS_SndUsimmDeactiveCardReq(
    VOS_UINT32                          ulSenderPid
);

VOS_UINT32 NAS_SndUsimmEcallNumberQry(
    VOS_UINT32                          ulPid,
    SI_PB_STORAGE_ENUM_UINT32           enStorage,
    VOS_UINT8                           ucListLen,
    VOS_UINT8                          *pucList
);

VOS_UINT32 NAS_SndUsimmEnvelopeDownloadReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    SI_STK_ENVELOPE_STRU               *pstENStru
);

VOS_UINT32 NAS_SndUsimmRestrictedAccessReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    USIMM_RACCESS_REQ_STRU             *pstData
);

VOS_UINT32 NAS_SndUsimmRefreshReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_STK_COMMAND_DETAILS_STRU     *pstCMDDetail,
    USIMM_RESET_INFO_STRU              *pstRstInfo
);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* END OF _NAS_SNDUSIMM_H_ */
