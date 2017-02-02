

#ifndef __NASCOMMPUBLIC_H__
#define __NASCOMMPUBLIC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "OmCommon.h"
#include  "PsLogdef.h"
#include  "PsCommonDef.h"


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
#define NAS_COMM_NULL                   (0)

/* �ڴ濽���궨�� */
#define NAS_COMM_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulBufferLen) \
    {\
        if(NAS_COMM_NULL == PS_MEM_CPY_ALL_CHECK((pucDestBuffer),(pucSrcBuffer),(ulBufferLen)))\
        {\
            NAS_COMM_LOG_ERR("NAS_COMM_MEM_CPY  ERR!!");\
        }\
    }

#define NAS_COMM_MEM_SET(pucBuffer, ucData, ulBufferLen) \
    {\
        if(VOS_NULL_PTR == PS_MEM_SET_ALL_CHECK( (pucBuffer), (ucData), (ulBufferLen)))\
        {\
            NAS_COMM_LOG_ERR("NAS_COMM_MEM_SET  ERR!!");\
        }\
    }

#define NAS_COMM_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
            PS_MEM_CMP((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))

#define NAS_COMM_ALLOC_MSG(ulLen) \
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_MM) , (ulLen))

/* ������Ϣ */
#define NAS_COMM_SND_MSG(pMsg)\
            if(VOS_OK != PS_SND_MSG_ALL_CHECK((PS_PID_MM) , (pMsg)))\
                {NAS_COMM_LOG_ERR("NAS_COMM_SND_MSG:Msg Snd Err!");}

/*�ڴ��ͷ�*/
#define NAS_COMM_MEM_FREE(pAddr)\
    {\
        if(VOS_OK != PS_MEM_FREE_ALL_CHECK((PS_PID_MM), (pAddr)))\
        {\
            NAS_COMM_LOG_ERR("NAS_COMM_MEM_FREE  ERR!!");\
        }\
    }

/*�ڴ涯̬����*/
#define NAS_COMM_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC_All_CHECK((PS_PID_MM) , (ulSize))

#define NAS_COMM_LOG_LEVEL_OFF               LOG_LEVEL_OFF        /* �رմ�ӡ     */
#define NAS_COMM_LOG_LEVEL_ERROR             LOG_LEVEL_ERROR      /* Error����    */
#define NAS_COMM_LOG_LEVEL_WARNING           LOG_LEVEL_WARNING    /* Warning����  */
#define NAS_COMM_LOG_LEVEL_NORMAL            LOG_LEVEL_NORMAL     /* Normal����   */
#define NAS_COMM_LOG_LEVEL_INFO              LOG_LEVEL_INFO       /* Info����     */

#ifdef  PS_ITT_PC_TEST
#define NAS_COMM_LOG_INFO(String)            vos_printf(" %s\r\n",String)
#define NAS_COMM_LOG_NORM(String)            vos_printf(" %s\r\n",String)
#define NAS_COMM_LOG_WARN(String)            vos_printf(" %s\r\n",String)
#define NAS_COMM_LOG_ERR(String)             vos_printf(" %s\r\n",String)

#define NAS_COMM_LOG1_INFO(String, Para1)    vos_printf(" %s %d\r\n",String,Para1)
#define NAS_COMM_LOG1_NORM(String, Para1)    vos_printf(" %s %d\r\n",String,Para1)
#define NAS_COMM_LOG1_WARN(String, Para1)    vos_printf(" %s %d\r\n",String,Para1)
#define NAS_COMM_LOG1_ERR(String,  Para1)    vos_printf(" %s %d\r\n",String,Para1)

#define NAS_COMM_LOG2_INFO(String, Para1, Para2)    vos_printf(" %s %d,%d\r\n",String,Para1,Para2)
#define NAS_COMM_LOG2_NORM(String, Para1, Para2)    vos_printf(" %s %d,%d\r\n",String,Para1,Para2)
#define NAS_COMM_LOG2_WARN(String, Para1, Para2)    vos_printf(" %s %d,%d\r\n",String,Para1,Para2)
#define NAS_COMM_LOG2_ERR(String,  Para1, Para2)    vos_printf(" %s %d,%d\r\n",String,Para1,Para2)

#define NAS_COMM_LOG3_INFO(String, Para1, Para2, Para3)    vos_printf(" %s %d,%d,%d\r\n",String,Para1,Para2,Para3)
#define NAS_COMM_LOG3_NORM(String, Para1, Para2, Para3)    vos_printf(" %s %d,%d,%d\r\n",String,Para1,Para2,Para3)
#define NAS_COMM_LOG3_WARN(String, Para1, Para2, Para3)    vos_printf(" %s %d,%d,%d\r\n",String,Para1,Para2,Para3)
#define NAS_COMM_LOG3_ERR(String,  Para1, Para2, Para3)    vos_printf(" %s %d,%d,%d\r\n",String,Para1,Para2,Para3)

#else  /*For PS_ITT_PC_TEST*/

#define NAS_COMM_LOG_INFO(String)            LPS_LOG(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_INFO, String)
#define NAS_COMM_LOG_NORM(String)            LPS_LOG(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_NORMAL, String)
#define NAS_COMM_LOG_WARN(String)            LPS_LOG(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_WARNING, String)
#define NAS_COMM_LOG_ERR( String)             LPS_LOG(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_ERROR, String)

#define NAS_COMM_LOG1_INFO(String, Para1)    LPS_LOG1(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_INFO, String, (long)Para1)
#define NAS_COMM_LOG1_NORM(String, Para1)    LPS_LOG1(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_NORMAL, String, (long)Para1)
#define NAS_COMM_LOG1_WARN(String, Para1)    LPS_LOG1(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_WARNING, String, (long)Para1)
#define NAS_COMM_LOG1_ERR(String,  Para1)    LPS_LOG1(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_ERROR, String, (long)Para1)

#define NAS_COMM_LOG2_INFO(String, Para1, Para2)    LPS_LOG2(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define NAS_COMM_LOG2_NORM(String, Para1, Para2)    LPS_LOG2(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#define NAS_COMM_LOG2_WARN(String, Para1, Para2)    LPS_LOG2(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_WARNING, String, (long)Para1, (long)Para2)
#define NAS_COMM_LOG2_ERR(String,  Para1, Para2)    LPS_LOG2(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_ERROR,   String, (long)Para1, (long)Para2)

#define NAS_COMM_LOG3_INFO(String, Para1, Para2, Para3)    LPS_LOG3(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_INFO, String, (long)Para1, (long)Para2, (long)Para3)
#define NAS_COMM_LOG3_NORM(String, Para1, Para2, Para3)    LPS_LOG3(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2, (long)Para3)
#define NAS_COMM_LOG3_WARN(String, Para1, Para2, Para3)    LPS_LOG3(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_WARNING, String, (long)Para1, (long)Para2, (long)Para3)
#define NAS_COMM_LOG3_ERR(String,  Para1, Para2, Para3)    LPS_LOG3(UE_MODULE_MM_ID, VOS_NULL, NAS_COMM_LOG_LEVEL_ERROR,   String, (long)Para1, (long)Para2, (long)Para3)

#endif

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/


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

#endif /* end of NasCommPrint.h */
