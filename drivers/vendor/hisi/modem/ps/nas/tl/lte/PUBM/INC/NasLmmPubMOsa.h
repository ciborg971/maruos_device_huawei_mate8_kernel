

#ifndef __NASLMMPUBMOSA_H__
#define __NASLMMPUBMOSA_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "vos.h"
#include    "PsLogdef.h"

#include    "PsCommonDef.h"

#include    "OmCommon.h"
#include    "NasLmmPubMPrint.h"
#include   "UsimPsInterface.h"
#include   "NasFileId.h"

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
*****************************************************************************/

/*#define NAS_LMM_ASSERT_ABORT     1    ���� : �˺꿪�ؽ����ڷ����������ʱ����PC���� */




/*========================= OSA���װ =========================BEGIN */
#define NAS_EMM_TIMER_PARA_NULL             0

#define NAS_EMM_LENGTH_OF_PRINT_LINE_BUF    256

#define NAS_LMM_NULL_PTR                     VOS_NULL_PTR


#define NAS_LOG_LEVEL_OFF               LOG_LEVEL_OFF        /* �رմ�ӡ     */
#define NAS_LOG_LEVEL_ERROR             LOG_LEVEL_ERROR      /* Error����    */
#define NAS_LOG_LEVEL_WARNING           LOG_LEVEL_WARNING    /* Warning����  */
#define NAS_LOG_LEVEL_NORMAL            LOG_LEVEL_NORMAL     /* Normal����   */
#define NAS_LOG_LEVEL_INFO              LOG_LEVEL_INFO       /* Info����     */

#ifdef  PS_ITT_PC_TEST

#define NAS_LMM_LOG_INFO(SubModId,String)            vos_printf(" %s\r\n",String)
#define NAS_LMM_LOG_NORM(SubModId,String)            vos_printf(" %s\r\n",String)
#define NAS_LMM_LOG_WARN(SubModId,String)            vos_printf(" %s\r\n",String)
#define NAS_LMM_LOG_ERR(SubModId,String)             vos_printf(" %s\r\n",String)

#define NAS_LMM_LOG1_INFO(SubModId,String, Para1)    vos_printf(" %s %d\r\n",String,Para1)

#define NAS_LMM_LOG1_NORM(SubModId,String, Para1)    vos_printf(" %s %d\r\n",String,Para1)
#define NAS_LMM_LOG1_WARN(SubModId,String, Para1)    vos_printf(" %s %d\r\n",String,Para1)
#define NAS_LMM_LOG1_ERR(SubModId,String,  Para1)    vos_printf(" %s %d\r\n",String,Para1)

#define NAS_LMM_LOG2_INFO(SubModId,String, Para1, Para2)    vos_printf(" %s %d,%d\r\n",String,Para1,Para2)
#define NAS_LMM_LOG2_NORM(SubModId,String, Para1, Para2)    vos_printf(" %s %d,%d\r\n",String,Para1,Para2)
#define NAS_LMM_LOG2_WARN(SubModId,String, Para1, Para2)    vos_printf(" %s %d,%d\r\n",String,Para1,Para2)
#define NAS_LMM_LOG2_ERR(SubModId,String,  Para1, Para2)    vos_printf(" %s %d,%d\r\n",String,Para1,Para2)

#define NAS_LMM_LOG3_INFO(SubModId,String, Para1, Para2, Para3)    vos_printf(" %s %d,%d,%d\r\n",String,Para1,Para2,Para3)
#define NAS_LMM_LOG3_NORM(SubModId,String, Para1, Para2, Para3)    vos_printf(" %s %d,%d,%d\r\n",String,Para1,Para2,Para3)
#define NAS_LMM_LOG3_WARN(SubModId,String, Para1, Para2, Para3)    vos_printf(" %s %d,%d,%d\r\n",String,Para1,Para2,Para3)
#define NAS_LMM_LOG3_ERR(SubModId,String,  Para1, Para2, Para3)    vos_printf(" %s %d,%d,%d\r\n",String,Para1,Para2,Para3)

#else  /*For PS_ITT_PC_TEST*/

#define NAS_LMM_LOG_INFO(SubModId, String)            LPS_LOG(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_INFO, String)
#define NAS_LMM_LOG_NORM(SubModId, String)            LPS_LOG(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_NORMAL, String)
#define NAS_LMM_LOG_WARN(SubModId, String) \
    {\
        LPS_LOG(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_WARNING, String);\
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR); \
    }
#define NAS_LMM_LOG_ERR(SubModId, String) \
    {\
        LPS_LOG(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_ERROR, String); \
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR); \
    }

#define NAS_LMM_LOG1_INFO(SubModId, String, Para1)    LPS_LOG1(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_INFO, String, (long)Para1)
#define NAS_LMM_LOG1_NORM(SubModId, String, Para1)    LPS_LOG1(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_NORMAL, String, (long)Para1)
#define NAS_LMM_LOG1_WARN(SubModId, String, Para1) \
    {\
        LPS_LOG1(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_WARNING, String, (long)Para1);\
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, (VOS_UINT16)Para1, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR); \
    }
#define NAS_LMM_LOG1_ERR(SubModId, String,  Para1) \
    {\
        LPS_LOG1(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_ERROR, String, (long)Para1);\
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, (VOS_UINT16)Para1, VOS_NULL_PTR, VOS_NULL_PTR, VOS_NULL_PTR); \
    }

#define NAS_LMM_LOG2_INFO(SubModId, String, Para1, Para2)    LPS_LOG2(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define NAS_LMM_LOG2_NORM(SubModId, String, Para1, Para2)    LPS_LOG2(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#define NAS_LMM_LOG2_WARN(SubModId, String, Para1, Para2) \
    {\
        LPS_LOG2(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_WARNING, String, (long)Para1, (long)Para2); \
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, (VOS_UINT16)Para1, (VOS_UINT16)Para2, VOS_NULL_PTR, VOS_NULL_PTR); \
    }
#define NAS_LMM_LOG2_ERR(SubModId, String,  Para1, Para2) \
    { \
        LPS_LOG2(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_ERROR,   String, (long)Para1, (long)Para2); \
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, (VOS_UINT16)Para1, (VOS_UINT16)Para2, VOS_NULL_PTR, VOS_NULL_PTR); \
    }

#define NAS_LMM_LOG3_INFO(SubModId, String, Para1, Para2, Para3)    LPS_LOG3(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_INFO, String, (long)Para1, (long)Para2, (long)Para3)
#define NAS_LMM_LOG3_NORM(SubModId, String, Para1, Para2, Para3)    LPS_LOG3(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2, (long)Para3)
#define NAS_LMM_LOG3_WARN(SubModId, String, Para1, Para2, Para3) \
    {\
        LPS_LOG3(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_WARNING, String, (long)Para1, (long)Para2, (long)Para3);\
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, (VOS_UINT16)Para1, (VOS_UINT16)Para2, (VOS_UINT16)Para3, VOS_NULL_PTR);\
    }
#define NAS_LMM_LOG3_ERR(SubModId, String,  Para1, Para2, Para3) \
    { \
        LPS_LOG3(UE_MODULE_MM_ID, SubModId, NAS_LOG_LEVEL_ERROR,   String, (long)Para1, (long)Para2, (long)Para3); \
        NAS_LMM_SndDebugInfoInd(THIS_NAS_FILE_ID, __LINE__, (VOS_UINT16)Para1, (VOS_UINT16)Para2, (VOS_UINT16)Para3, VOS_NULL_PTR); \
    }

#endif


/*=============================== ����ΪPUBM ר�� ============================*/

#define NAS_LMM_PUBM_LOG_INFO(String)                     NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_PUBM, String)
#define NAS_LMM_PUBM_LOG_NORM(String)                     NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_PUBM, String)
#define NAS_LMM_PUBM_LOG_WARN(String)                     NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_PUBM, String)
#define NAS_LMM_PUBM_LOG_ERR(String)                      NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_PUBM, String)

#define NAS_LMM_PUBM_LOG1_INFO(String, Para1)             NAS_LMM_LOG1_INFO(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1)
#define NAS_LMM_PUBM_LOG1_NORM(String, Para1)             NAS_LMM_LOG1_NORM(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1)
#define NAS_LMM_PUBM_LOG1_WARN(String, Para1)             NAS_LMM_LOG1_WARN(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1)
#define NAS_LMM_PUBM_LOG1_ERR(String,  Para1)             NAS_LMM_LOG1_ERR(LOG_SUBMOD_ID_NAS_LMM_PUBM, String,  Para1)

#define NAS_LMM_PUBM_LOG2_INFO(String, Para1, Para2)      NAS_LMM_LOG2_INFO(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2)
#define NAS_LMM_PUBM_LOG2_NORM(String, Para1, Para2)      NAS_LMM_LOG2_NORM(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2)
#define NAS_LMM_PUBM_LOG2_WARN(String, Para1, Para2)      NAS_LMM_LOG2_WARN(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2)
#define NAS_LMM_PUBM_LOG2_ERR(String,  Para1, Para2)      NAS_LMM_LOG2_ERR(LOG_SUBMOD_ID_NAS_LMM_PUBM, String,  Para1, Para2)

#define NAS_LMM_PUBM_LOG3_INFO(String, Para1, Para2, Para3)    NAS_LMM_LOG3_INFO(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2, Para3)
#define NAS_LMM_PUBM_LOG3_NORM(String, Para1, Para2, Para3)    NAS_LMM_LOG3_NORM(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2, Para3)
#define NAS_LMM_PUBM_LOG3_WARN(String, Para1, Para2, Para3)    NAS_LMM_LOG3_WARN(LOG_SUBMOD_ID_NAS_LMM_PUBM, String, Para1, Para2, Para3)
#define NAS_LMM_PUBM_LOG3_ERR(String,  Para1, Para2, Para3)    NAS_LMM_LOG3_ERR(LOG_SUBMOD_ID_NAS_LMM_PUBM, String,  Para1, Para2, Para3)




/* MM���ڴ濽���궨�� */
#define NAS_LMM_MEM_CPY(pDestBuffer,pSrcBuffer,Count) \
    {\
        if(NAS_EMM_NULL_PTR == PS_MEM_CPY_ALL_CHECK((pDestBuffer),(pSrcBuffer),(Count)))\
        {\
            NAS_LMM_PUBM_LOG_ERR("NAS_LMM_MEM_CPY  ERR!!");\
        }\
    }

/* MM���ڴ���λ�궨�� */
#define NAS_LMM_MEM_SET(pBuffer,ucData,Count) \
    {\
        if(NAS_EMM_NULL_PTR == PS_MEM_SET_ALL_CHECK( (pBuffer), (ucData), (Count)))\
        {\
            NAS_LMM_PUBM_LOG_ERR("NAS_LMM_MEM_SET  ERR!!");\
        }\
    }

/* MM��DOPRA��Ϣ����궨�� */
#define NAS_LMM_ALLOC_MSG(ulLen)\
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_MM),(ulLen))

/* MM���ڴ��ͷź궨�� */
#define NAS_LMM_FREE_MSG(pData)\
            PS_FREE_MSG_ALL_CHECK((PS_PID_MM),(pData))

/* MM���ڴ����궨�� */
#define NAS_LMM_MEM_ALLOC(ulSize) \
            PS_MEM_ALLOC_All_CHECK((PS_PID_MM), (ulSize))

/* MM���ڴ����궨�� */
#define NAS_LMM_MEM_FREE(pAddr) \
            {\
                if(NAS_EMM_OK != PS_MEM_FREE_ALL_CHECK((PS_PID_MM), (pAddr)))\
                {\
                    NAS_LMM_PUBM_LOG_ERR("NAS_LMM_MEM_FREE  ERR!!");\
                }\
            }

#define NAS_LMM_SEND_MSG(pMsg) \
        {\
            NAS_LMM_PUBM_PrintSendMsg((const PS_MSG_HEADER_STRU *)pMsg,NAS_COMM_GET_MM_PRINT_BUF());\
            if(NAS_EMM_OK != PS_SND_MSG_ALL_CHECK((PS_PID_MM), (pMsg)))\
            {\
                NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SEND_MSG  ERR!!");\
            }\
        }


#define NAS_EMM_SEND_INTRA_MSG(pIntraMsg)\
        {\
            NAS_LMM_PUBM_PrintSendMsg((const PS_MSG_HEADER_STRU *)pIntraMsg,\
                                      NAS_COMM_GET_MM_PRINT_BUF());\
            if(NAS_EMM_OK !=  NAS_LMM_SendIntraMsg((pIntraMsg)))\
            {\
                NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SEND_INTRA_MSG  ERR!!");\
            }\
        }

#define NAS_LMM_SEND_URGENT_MSG(pMsg) \
        {\
            NAS_LMM_PUBM_PrintSendMsg((const PS_MSG_HEADER_STRU *)pMsg,NAS_COMM_GET_MM_PRINT_BUF());\
            if(NAS_EMM_OK != PS_SND_URGENT_MSG((PS_PID_MM), (pMsg)))\
            {\
                NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SEND_URGENT_MSG  ERR!!");\
            }\
        }

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*typedef struct MsgCB                    NAS_EMM_MSG_STRU;
 */

/*****************************************************************************
 �ṹ��    : NasMmIntraMsgCB
 �ṹ˵��  : NAS_LMM�ڲ���Ϣ�ṹ,ͬVOS����ʱ����Ľṹ MsgCB
*****************************************************************************/
struct NasMmMsgCB
{
    VOS_MSG_HEADER
    VOS_UINT8 aucValue[4];
};

typedef struct NasMmMsgCB               NasMmMsgBlock;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/



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

#endif /* end of NasLmmPubMOsa.h*/
