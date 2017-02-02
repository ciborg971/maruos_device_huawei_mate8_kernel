

#ifndef _NASEMMGUTI_H
#define _NASEMMGUTI_H


/*****************************************************************************
  1 ����ͷ�ļ�����
****************************************************************************/
#include    "NasEmmGIMComm.h"
#include    "NasEmmPubUCnMsgDecode.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
****************************************************************************/
/*Ӧ�ð��������ֶ�*/
#define EMM_COUNT_CN_GUTI_CMP_LEN \
        (\
            NAS_MSG_STRU_MSG_SIZE_LEN   +   \
            NAS_GUTI_COMP_NAS_MSG_LEN       \
        )

#define VOS_UINT32_FFS VOS_UINT32


/*��װGUTIģ���LOG��ӡ��*/
#define LOG_SUBMOD_ID_NAS_LMM_GUTI               1
#define NAS_EMM_GUTI_ERROR_LOG(String)          NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_GUTI, String)
#define NAS_EMM_GUTI_WARNING_LOG(String)        NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_GUTI, String)
#define NAS_EMM_GUTI_NORMAL_LOG(String)         NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_GUTI, String)
#define NAS_EMM_GUTI_INFO_LOG(String)           NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_GUTI, String)
#define NAS_EMM_GUTI_NORAML_LOG1(String, Para1) NAS_LMM_LOG1_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_GUTI, String, Para1)

#define NAS_EMM_GUTI_NORAML_LOG2(String, Para1, Para2) NAS_LMM_LOG2_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_GUTI, String, Para1, Para2)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*���෢�Ŀտ���ϢGUTI_REALLOCATION_COMMAND�Ľṹ*/


/*****************************************************************************
  6 UNION
*****************************************************************************/

/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*����NVIM�ӿں���*/
extern VOS_VOID       NAS_EMM_GutiWrite(VOS_UINT32 g_ulGuti);
extern VOS_VOID       NAS_EMM_TaiListWrite(VOS_VOID);
extern VOS_VOID    NAS_EMM_CompCnGutiCmp(LRRC_LNAS_MSG_STRU  *pNasMsg);
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32    NAS_EMM_GutiMrrcDataReq(VOS_VOID);

/*****************************************************************************
  9 OTHERS
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
