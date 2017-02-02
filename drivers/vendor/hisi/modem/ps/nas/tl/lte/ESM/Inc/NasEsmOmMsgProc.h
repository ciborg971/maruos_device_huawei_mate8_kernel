/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEsmOmMsgProc.h
  Description     : NasEsmOmMsgProc.c header file
  History         :
     1.sunbing       2008-12-30     Draft Enact
     2.
******************************************************************************/

#ifndef __NASESMOMMSGPROC_H__
#define __NASESMOMMSGPROC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "OmCommon.h"
#include    "LnasFtmInterface.h"
#include    "LnasErrlogInterface.h"


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
#define NAS_ESM_LEN_VOS_MSG_HEADER          20
#define NAS_ESM_GetFtmInfoManageAddr()      (&(g_astEsmFtmInfoManage))
#define NAS_ESM_GetEsmInfoAddr()            (&(g_astEsmInfo))
#define NAS_ESM_GetFtmInfoActionFlag()      (NAS_ESM_GetFtmInfoManageAddr()->ulFtmActionFlag)
#define NAS_ESM_GetFtmInfoMsgSN()           (NAS_ESM_GetFtmInfoManageAddr()->ulMsgSN)
#define NAS_ESM_GetFtmInfoEsmCause()        (NAS_ESM_GetFtmInfoManageAddr()->ucEsmCause)
#define NAS_ESM_SetFtmOmManageFtmActionFlag(Flag)  (NAS_ESM_GetFtmInfoActionFlag() = Flag)

#define NAS_ESM_GetErrlogManageAddr()       (&(g_astEsmErrlogInfoManage))
#define NAS_ESM_GetErrlogActionFlag()       (NAS_ESM_GetErrlogManageAddr()->ulActionFlag)
#define NAS_ESM_SetErrlogActionFlag(Flag)   (NAS_ESM_GetErrlogActionFlag() = Flag)
#define NAS_ESM_GetErrlogMsgSN()            (NAS_ESM_GetErrlogManageAddr()->ulMsgSN)
#define NAS_ESM_GetErrlogAlmLevel()         (NAS_ESM_GetErrlogManageAddr()->usALMLevel)
#define NAS_ESM_SetErrlogAlmLevel(usLevel)  (NAS_ESM_GetErrlogAlmLevel() = usLevel)
#define NAS_ESM_GetErrlogAlmType()          (NAS_ESM_GetErrlogManageAddr()->usALMType)
#define NAS_ESM_GetErrlogAlmLowSlice()      (NAS_ESM_GetErrlogManageAddr()->ulAlmLowSlice)
#define NAS_ESM_GetErrlogAlmHighSlice()     (NAS_ESM_GetErrlogManageAddr()->ulAlmHighSlice)
#define NAS_ESM_GetErrlogAmount()           (NAS_ESM_GetErrlogManageAddr()->ulErrLogAmount)
#define NAS_ESM_GetErrlogNextNullPos()      (NAS_ESM_GetErrlogManageAddr()->ulNextNullPos)
#define NAS_ESM_GetErrlogInfo(ulIndex)      (NAS_ESM_GetErrlogManageAddr()->stEsmErrInfoDetail[ulIndex])
#define NAS_ESM_ERRLOG_MAX_NUM  (4)

#define NAS_ESM_COMP_OM_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_ESM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = MSP_PID_DIAG_APP_AGENT;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_ESM_TP_CMD_TYPE_ENUM
 ö��˵��  : ��������ȡֵ
*****************************************************************************/
enum    NAS_ESM_TP_CMD_TYPE_ENUM
{
    NAS_ESM_TP_CMD_TYPE_TEST            = 0x00,

    NAS_ESM_TP_CMD_TYPE_BUTT
};
typedef VOS_UINT8   NAS_ESM_TP_CMD_TYPE_ENUM_UINT8 ;

/*****************************************************************************
 ö����    : NAS_ESM_AIR_MSG_DIR_ENUM
 ö��˵��  : ��������ȡֵ
*****************************************************************************/
enum    NAS_ESM_AIR_MSG_DIR_ENUM
{
    NAS_ESM_AIR_MSG_DIR_ENUM_UP         = 0x00,
    NAS_ESM_AIR_MSG_DIR_ENUM_DOWN             ,

    NAS_ESM_AIR_MSG_DIR_BUTT
};
typedef VOS_UINT8   NAS_ESM_AIR_MSG_DIR_ENUM_UINT8 ;

enum    NAS_ESM_FTM_ACTION_FLAG_ENUM
{
    NAS_ESM_FTM_ACTION_FLAG_CLOSE = 0,
    NAS_ESM_FTM_ACTION_FLAG_OPEN = 1,
    NAS_ESM_FTM_ACTION_FLAG_BUTT
};
typedef VOS_UINT32  NAS_ESM_FTM_ACTION_FLAG_ENUM_UINT32;

enum NAS_ESM_ERRLOG_LEVEL_ENUM
{
    NAS_ESM_ERRLOG_LEVEL_CRITICAL   = 1,/*�������*/
    NAS_ESM_ERRLOG_LEVEL_MAJOR      = 2,/*������Ҫ*/
    NAS_ESM_ERRLOG_LEVEL_MINOR      = 3,/*�����Ҫ*/
    NAS_ESM_ERRLOG_LEVEL_WARING     = 4,/*������ʾ��*/
    NAS_ESM_ERRLOG_LEVEL_BUTT
};
typedef VOS_UINT16  NAS_ESM_ERRLOG_LEVEL_ENUM_UINT16;

/* ERROR LOG����&��������*/
enum NAS_ESM_ERRLOG_TYPE_ENUM
{
    NAS_ESM_ERRLOG_TYPE_COMMUNICATION       = 0x00, /* ͨ��     */
    NAS_ESM_ERRLOG_TYPE_SERVING_QUALITY     = 0x01, /* ҵ������ */
    NAS_ESM_ERRLOG_TYPE_PROCESS_ERROR       = 0x02, /* ������� */
    NAS_ESM_ERRLOG_TYPE_EQUIPMENT_TROUBLE   = 0x03, /* �豸���� */
    NAS_ESM_ERRLOG_TYPE_ENVIRONMENT_TROUBLE = 0x04, /* �������� */
};
typedef VOS_UINT16 NAS_ESM_ERRLOG_TYPE_ENUM_UINT16;


enum NAS_ESM_ERRLOG_ACTION_FLAG_ENUM
{
    NAS_ESM_ERRLOG_ACTION_FLAG_CLOSE  = 0,
    NAS_ESM_ERRLOG_ACTION_FLAG_OPEN   = 1,
    NAS_ESM_ERRLOG_ACTION_FLAG_BUTT
};
typedef VOS_UINT32  NAS_ESM_ERRLOG_ACTION_FLAG_ENUM_UINT32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : NAS_ESM_TRANSPARENT_CMD_REQ_STRU
 �ṹ˵��  : OMT->ESM��͸�������·��ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;        /*ԭ������*/
    APP_MSG_HEADER

    NAS_ESM_TP_CMD_TYPE_ENUM_UINT8      enEsmTpCmdType;
    VOS_UINT8                           aucRsv[3];
}NAS_ESM_TRANSPARENT_CMD_REQ_STRU;


/* xiongxianghui00253310 modify for ftmerrlog begin */
typedef struct
{
    /* ȡֵ�ͺ���� 24301 9.9.4.4 */
    VOS_UINT8                           ucEsmCause;
    VOS_UINT8                           aucRsv[3];
}ESM_DATABASE_INFO_STRU;

typedef struct
{
    /* �򿪻��߹رչ���ģʽ�ϱ����� 0:close 1:open*/
    VOS_UINT32                          ulFtmActionFlag;
    /* ESM��OM���͵�ÿ������ģʽ��Ϣ���д˱�ţ��ϵ�Ϊ0��Ȼ�����μ� 1 */
    VOS_UINT32                          ulMsgSN;
    /* ESM����ģʽ����ṹ��ʱ�洢CnCause�������뱾�����ݿ���бȶ� */
    VOS_UINT8                           ucEsmCause;
    VOS_UINT8                           aucRsv[3];

}ESM_FTM_INFO_MANAGE_STRU;


typedef struct
{
   NAS_OM_ACT_PDP_INFO_STRU            stActPdpInfo;
}APP_ESM_DT_STRU;

/* add by yanglei 00307272 for KEY_INFO_REPORT3,2015-08-18,begin */
/*****************************************************************************
 �ṹ��    : NAS_ESM_OM_LOG_REG_CID_INFO_STRU
 �ṹ˵��  : ESM��OM����Ŀ�ά�ɲ��ע��ʱѡ���CID
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                               stMsgHeader;        /*_H2ASN_Skip*/

    VOS_UINT32                                    ulRegCid;
} NAS_ESM_OM_LOG_REG_CID_INFO_STRU;
/* add by yanglei 00307272 for KEY_INFO_REPORT3,2015-08-18,end */

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32                  g_NasEsmOmInfoIndFlag;

/* xiongxianghui00253310 modify for ftmerrlog begin */
extern ESM_FTM_INFO_MANAGE_STRU             g_astEsmFtmInfoManage;
extern ESM_DATABASE_INFO_STRU               g_astEsmInfo;
/* xiongxianghui00253310 modify for ftmerrlog end   */

extern VOS_UINT32   g_ulRptPdpStatus;
extern VOS_UINT32   g_ulNasEsmOmMsgHookFlag;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/* xiongxianghui00253310 modify for ftmerrlog begin */
extern VOS_VOID     NAS_ESM_OmInfoIndProc(VOS_VOID);
extern VOS_VOID     NAS_ESM_FtmInfoInit(VOS_VOID);
extern VOS_UINT32   NAS_ESM_RevOmFtmCtrlMsg(MsgBlock   *pMsgStru);
extern VOS_UINT32   NAS_ESM_CompareEsmDatabaseInfo(VOS_VOID);
extern VOS_VOID     NAS_ESM_UpdateEsmDatabaseInfo(VOS_VOID);
extern VOS_VOID     NAS_ESM_SendOmFtmMsg(VOS_VOID);

/* del by yanglei 00307272 for OM_DIAG_PHASE2 2015-07-17 begin */
//extern VOS_VOID NAS_ESM_OmMsgDistrForAcpuPidOm( VOS_VOID *pRcvMsg );
/* del by yanglei 00307272 for OM_DIAG_PHASE2 2015-07-17 end */



/* xiongxianghui00253310 modify for ftmerrlog end   */


/*****************************************************************************
  9 OTHERS
*****************************************************************************/

extern VOS_VOID NAS_ESM_SndAirMsgReportInd
(
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulLength,
    NAS_ESM_AIR_MSG_DIR_ENUM_UINT8      enMsgDir,
    OM_PS_AIR_MSG_ENUM_UINT8            enMsgId
);
extern VOS_VOID NAS_ESM_SndEsmOmTpCmdCnfMsg(const VOS_UINT8 *pucData,
                                                               VOS_UINT32 ulLength);
extern VOS_VOID NAS_ESM_SndKeyEventReportInd(OM_PS_KEY_EVENT_ENUM_UINT8 enKeyEvent);
extern VOS_VOID NAS_ESM_TransparentMsgProc( VOS_VOID* pRcvMsg );
extern VOS_VOID NAS_ESM_OmMsgDistr
(
    VOS_VOID                           *pRcvMsg
);
extern VOS_VOID NAS_ESM_OmInfoIndMsgProc(VOS_VOID *pRcvMsg);
extern VOS_UINT32 LTE_MsgHook(VOS_VOID * pMsg);
/*niuxiufan DT end */

extern VOS_VOID NAS_ESM_ReportActPdpInfo( VOS_VOID);

/* add by yanglei  00307272 for KEY_INFO_REPORT3, 2015-08-19, begin */
extern VOS_VOID NAS_ESM_SndOmRegCidInfo(VOS_UINT32  ulRegCid);
/* add by yanglei  00307272 for KEY_INFO_REPORT3, 2015-08-19, end */








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

#endif /* end of NasEsmOmMsgProc.h */
