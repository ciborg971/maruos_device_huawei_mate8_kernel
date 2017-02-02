/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : msp_Debug.h
  Description     : msp_Debug.h header file
  History         :
     1.C64416       2014-11-18     Draft Enact
     2.
******************************************************************************/
#ifndef __MSP_DEBUG_H__
#define __MSP_DEBUG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "product_config.h"
#include  "vos.h"

#pragma pack(4)


#define DIAG_DEBUG_START        (0xaaaa5555)
#define DIAG_DEBUG_END          (0x5555aaaa)

/* debug版本 V1.00 */
#define DIAG_DEBUG_VERSION      (0x00010000)

/* debug提示信息的长度 */
#define DIAG_DEBUG_INFO_LEN     (32)

/* 两次数据采集的时间间隔 */
#define DIAG_DEBUG_DEALAY       (5000)

/* 复杂的数据结构，存储信息前先存储信息长度，高8位是0xa5，低24位是数据长度 */
#define DIAG_DEBUG_SIZE_FLAG    (0xa5000000)


/* PTR ***********************************************************************/
#if((VOS_OS_VER == VOS_LINUX) || (VOS_OS_VER == VOS_WIN32))

/*
初步估计每个诊断命令由10-20个点能覆盖整个处理流程，
1000个点能缓存50-100个诊断命令的处理流程
*/
#define DIAG_PTR_NUMBER             (1000)

typedef enum
{
    EN_DIAG_PTR_BEGIN = 0,
    EN_DIAG_PTR_PPM_READDATA,
    EN_DIAG_PTR_CPM_COMRCV,
    EN_DIAG_PTR_SCM_SOFTDECODE,
    EN_DIAG_PTR_SCM_SELFTASK,
    EN_DIAG_PTR_SCM_RCVDATA,
    EN_DIAG_PTR_SCM_RCVDATA_SUCCESS,
    EN_DIAG_PTR_SCM_DISPATCH,
    EN_DIAG_PTR_MSP_SERVICE_1,
    EN_DIAG_PTR_MSP_SERVICE_2,
    EN_DIAG_PTR_SERVICE_IN,
    EN_DIAG_PTR_SERVICE_1,
    EN_DIAG_PTR_MESSAGE_IN,
    EN_DIAG_PTR_MESSAGE_PROC,
    EN_DIAG_PTR_MSGMSP_IN,
    EN_DIAG_PTR_MSGMSP_TRANS,
    EN_DIAG_PTR_MSGMSP_PS_IN,
    EN_DIAG_PTR_MSGMSP_PS_OUT,
    EN_DIAG_PTR_MSGMSP_CONN_IN,
    EN_DIAG_PTR_MSGMSP_DISCONN_IN,
    EN_DIAG_PTR_MESSAGE_REPORT,
    EN_DIAG_PTR_SERVICE_PACKETDATA,
    EN_DIAG_PTR_SEND_CODER_SRC,
    EN_DIAG_PTR_SCM_CODER_SRC,
    EN_DIAG_PTR_SCM_CODER_DST_CB,
    EN_DIAG_PTR_SCM_SENDTOUDI,
    EN_DIAG_PTR_CPM_COMSEND,
    EN_DIAG_PTR_PPM_PORTSEND,

    /* 失败流程的点 */
    EN_DIAG_PTR_ERR_BEGIN = 0x100,
    EN_DIAG_PTR_PPM_ERR1,
    EN_DIAG_PTR_PPM_ERR2,
    EN_DIAG_PTR_CPM_ERR1,
    EN_DIAG_PTR_CPM_ERR2,
    EN_DIAG_PTR_CPM_ERR3,
    EN_DIAG_PTR_SCM_ERR1,
    EN_DIAG_PTR_SCM_ERR2,
    EN_DIAG_PTR_SCM_ERR3,
    EN_DIAG_PTR_MSP_SERVICE_ERR1,
    EN_DIAG_PTR_MSP_SERVICE_ERR2,
    EN_DIAG_PTR_MSP_SERVICE_ERR3,
    EN_DIAG_PTR_DIAG_SERVICE_ERR1,
    EN_DIAG_PTR_DIAG_SERVICE_ERR2,
    EN_DIAG_PTR_DIAG_SERVICE_ERR3,
    EN_DIAG_PTR_DIAG_BUFFER_ERR1,
    EN_DIAG_PTR_DIAG_BUFFER_ERR2,
    EN_DIAG_PTR_MAX
} DIAG_PTR_ID_ENUM;

typedef struct
{
    DIAG_PTR_ID_ENUM    enStep;
    VOS_UINT32          ulTime;
} DIAG_PTR_ELEMENT_STRU;

typedef struct
{
    VOS_UINT32              ulCur;
    DIAG_PTR_ELEMENT_STRU   stPtr[DIAG_PTR_NUMBER];
} DIAG_PTR_INFO_STRU;

extern VOS_VOID diag_PTR(DIAG_PTR_ID_ENUM enType);

extern VOS_VOID DIAG_DebugCommon(VOS_VOID);

#endif

extern VOS_UINT32 DIAG_DebugFileHeader(void *pFile);
extern VOS_VOID DIAG_DebugFileTail(void *pFile, VOS_CHAR *FilePath);
extern VOS_VOID DIAG_DebugNoIndLog(VOS_VOID);
extern VOS_VOID diag_numberinfo(void *pFile);


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

#endif /* end of diag_Debug.h */

