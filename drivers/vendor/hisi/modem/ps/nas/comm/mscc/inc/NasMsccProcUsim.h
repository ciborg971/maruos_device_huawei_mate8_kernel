


#ifndef __NAS_MSCC_PROC_USIM_H__
#define __NAS_MSCC_PROC_USIM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "UsimPsInterface.h"
#include "NasMsccMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
#ifdef DMT
extern NAS_MSCC_CARD_READ_STUB_TYPE_ENUM_UINT8 genCardReadStubTypeForDmt;
#endif

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID NAS_MSCC_ReadUsimmFile(
    USIMM_CARDAPP_ENUM_UINT32                               enCardApp,
    USIMM_DEF_FILEID_ENUM_UINT32                            usFileId

);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID NAS_MSCC_ReadAndParseMlplMsplNvim(VOS_VOID);

VOS_VOID  NAS_MSCC_RcvUsimmReadMlplFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
);

VOS_VOID  NAS_MSCC_RcvUsimmReadMsplFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
);

VOS_VOID  NAS_MSCC_RcvUsimmReadFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg,
    USIMM_DEF_FILEID_ENUM_UINT32                            enEfId
);

VOS_VOID NAS_MSCC_ParseDefaultMlplMspl(VOS_VOID);

#ifdef DMT
VOS_VOID NAS_MSCC_SendCardReadTimerExpireMsgForDmt(VOS_VOID);
#endif

#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of NasMsccProcUsim.h */


