

#ifndef __DIAG_DEBUG_H__
#define __DIAG_DEBUG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "product_config.h"
#include  "mdrv.h"
#include  "vos.h"
#include  "msp_errno.h"
#include  "SCMProc.h"
#include  "msp_diag_comm.h"

#pragma pack(4)

typedef enum
{
   DIAG_DEBUG_API = 0,
   DIAG_DEBUG_API_AIR,
   DIAG_DEBUG_API_TRACE,
   DIAG_DEBUG_API_USERPLANE,
   DIAG_DEBUG_API_EVENT,
   DIAG_DEBUG_API_PRINT,
   DIAG_DEBUG_API_VOLTE,
   DIAG_DEBUG_API_TRANS,
   DIAG_DEBUG_API_DEFAULT
}DIAG_DEBUG_API_ENUM;


/* CBT ***********************************************************************/

#define DIAG_DEBUG_SDM_FUN(enType,ulRserved1,ulRserved2,ulRserved3)  \
            diag_CBT(enType,ulRserved1,ulRserved2,ulRserved3)

#define DIAG_PRINT_INFO
#ifdef DIAG_PRINT_INFO
#define diag_printf        (VOS_VOID)vos_printf
#else
#define diag_printf( fmt...)
#endif

typedef enum
{
    EN_DIAG_CBT_MSGMSP_CMD_ENTER,
    EN_DIAG_CBT_MSGMSP_TRANS_ENTER,
    EN_DIAG_CBT_MSGMSP_SYS_ENTER,
    EN_DIAG_CBT_MSGMSP_DFLT_ENTER,

    EN_DIAG_CBT_MSGMSP_TRANS_REQ,
    EN_DIAG_CBT_MSGMSP_TRANS_CNF,

    EN_DIAG_CBT_API_PRINTFV_OK,
    EN_DIAG_CBT_API_PRINTFV_ERR,

    EN_DIAG_CBT_API_EVENT_OK,
    EN_DIAG_CBT_API_EVENT_ERR,

    EN_DIAG_CBT_API_AIR_OK,
    EN_DIAG_CBT_API_AIR_ERR,

    EN_DIAG_CBT_API_TRACE_OK,
    EN_DIAG_CBT_API_TRACE_ERR,
    EN_DIAG_CBT_API_TRACE_FILTER,
    EN_DIAG_CBT_API_TRACE_MATCH,

    EN_DIAG_CBT_API_USER_OK,
    EN_DIAG_CBT_API_USER_ERR,

    EN_DIAG_CBT_API_PACKET_ERR_REQ,

    EN_DIAG_CBT_API_TRANS_OK,
    EN_DIAG_CBT_API_TRANS_ERR,

    EN_DIAG_CBT_API_VOLTE_ERR,
    EN_DIAG_CBT_API_VOLTE_OK,

    EN_DIAG_DEBUG_CODE_PACKET_START,
    EN_DIAG_DEBUG_CODE_PACKET_START_ERROR,

    EN_DIAG_DEBUG_GET_SRC_BUF_START,
    EN_DIAG_DEBUG_GET_SRC_BUF_START_ERROR,

    EN_SDM_DIAG_DOT,
    EN_SDM_DIAG_DOT_ERR,
    EN_SDM_DIAG_DOT_OK,

    EN_DIAG_DEBUG_MSG,
    EN_DIAG_DEBUG_MSG_ERR,
    EN_DIAG_DEBUG_CONN_CFG,
    EN_DIAG_DEBUG_DIS_CONN_CFG,
    EN_DIAG_DEBUG_LAYER_CFG,
    EN_DIAG_DEBUG_PRINT_CFG,
    EN_DIAG_DEBUG_EVENT_CFG,
    EN_DIAG_DEBUG_AIR_CFG,
	EN_DIAG_DEBUG_USEPLANE_CFG,

    EN_DIAG_DEBUG_AGENT_INIT,
    EN_DIAG_DEBUG_AGENT_INIT_ERROR,
    EN_DIAG_DEBUG_AGENT_DISPATCH_CMD,
    EN_DIAG_DEBUG_REG_RD,
    EN_DIAG_DEBUG_REG_WR,
    EN_DIAG_DEBUG_BBP_LOG,
    EN_DIAG_DEBUG_BBP_SAMPLE,
    EN_DIAG_DEBUG_LTE_DSP_CNF,
    EN_DIAG_DEBUG_TDS_DSP_CNF,

    EN_DIAG_DEBUG_BBP_AGENT_TIME_OUT_ENTRY,
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    /* DIAG APP SOCPͶƱ */
    EN_DIAG_APP_SOCP_VOTE,
    EN_DIAG_APP_SOCP_VOTE_ERR,
#endif
    /* DIAG AGENT��LDSP���佻�� */
    EN_DIAG_AGENT_LDSP_MB_MSG,
    EN_DIAG_DEBUG_INFO_MAX
} DIAG_CBT_ID_ENUM;

/*����������λʱMSP����Ĳ���ID��СֵΪ:0xB000000*/
#define DIAG_BASE_ERROR_NUMBER          (0xB0000000)

enum MSP_SYSTEMERROR_MODID_ENUM
{
    DIAG_ERROR_MODID_BASE       = (0xB0000000),
    DIAG_CALLED_IN_IRQ          = DIAG_ERROR_MODID_BASE,
    DIAG_ERROR_MODID_OVERFLOW,
    DIAG_ERROR_MODID_BUTT       = (0xB0000010)
};

typedef struct
{
    VOS_UINT32 ulCalledNum;  /* ���ô���������Ϣ����,���߱����ú����Ƿ񱻵���*/
    VOS_UINT32 ulRserved1;
    VOS_UINT32 ulRserved2;
    VOS_UINT32 ulRserved3;
    VOS_UINT32 ulRtcTime;
} DIAG_CBT_INFO_TBL_STRU;

typedef struct
{
    VOS_CHAR                pucApiName[8];
    DIAG_CBT_ID_ENUM        ulOk;
    DIAG_CBT_ID_ENUM        ulErr;
    VOS_UINT32              ulSlice;
    VOS_UINT32              ulOkNum;
    VOS_UINT32              ulErrNum;
}DIAG_DEBUG_API_INFO_STRU;

extern VOS_VOID diag_CBT(DIAG_CBT_ID_ENUM ulType, VOS_UINT32 ulRserved1,
                        VOS_UINT32 ulRserved2, VOS_UINT32 ulRserved3);


/* LNR ***********************************************************************/

#define DIAG_LNR_NUMBER             (100)

typedef enum
{
    EN_DIAG_LNR_CMDID = 0,  /* ���N�����յ���������� */

    EN_DIAG_LNR_LOG_LOST,   /* ���N��log��ʧ�ļ�¼ */

    EN_DIAG_LNR_PS_TRANS,   /* ���N��PS͸������ļ�¼ */

    EN_DIAG_LNR_CCORE_MSG,  /* ���N��C�˴�A���յ�����ϢID�ļ�¼ */

    EN_DIAG_LNR_MESSAGE_RPT,/* ���N��ͨ��messageģ��report�ϱ���cmdid�ļ�¼ */

    EN_DIAG_LNR_TRANS_IND,  /* ���N��͸���ϱ��ļ�¼ */

    EN_DIAG_LNR_INFO_MAX
} DIAG_LNR_ID_ENUM;

typedef struct
{
    VOS_UINT32 ulCur;
    VOS_UINT32 ulRserved1[DIAG_LNR_NUMBER];
    VOS_UINT32 ulRserved2[DIAG_LNR_NUMBER];
} DIAG_LNR_INFO_TBL_STRU;


extern VOS_VOID diag_LNR(DIAG_LNR_ID_ENUM ulType, VOS_UINT32 ulRserved1, VOS_UINT32 ulRserved2);


/* DFR (Data Flow Record������¼��)*******************************************/

#define     DIAG_DFR_NAME_MAX       (8)
#define     DIAG_DFR_BUFFER_MAX     (8*1024)
#define     DIAG_DFR_MAGIC_NUM      (0x44494147)    /* DIAG */

#define     DIAG_DFR_START_NUM      (0xabcd4321)

#define DFR_ALIGN_WITH_4BYTE(len)      (((len) + 3)&(~3))

typedef struct
{
    VOS_UINT32  ulMagicNum;                 /* ħ���� */
    VOS_SEM     semid;                      /* �洢�ռ���ʵĻ����ź��� */
    VOS_CHAR    name[DIAG_DFR_NAME_MAX];    /* �洢���������� */
    VOS_UINT32  ulCur;                      /* �洢�ռ�ĵ�ǰ��ַ */
    VOS_UINT32  ulLen;                      /* �洢�ռ���ܳ��� */
    VOS_UINT8   *pData;                     /* �洢�ռ���׵�ַ */
} DIAG_DFR_INFO_STRU;


typedef struct
{
    VOS_UINT32      ulStart;
    VOS_UINT32      ulTime;
}DIAG_DFR_HEADER_STRU;

/* throughput ��������Ϣ*******************************************/

#define     DIAG_THRPUT_DEBUG_NUM       (100)       /* ����100���� */

#define     DIAG_THRPUT_DEBUG_LEN       (5*32768)   /* ÿ��ͳ�����������ټ��5������ */

typedef enum
{
    EN_DIAG_THRPUT_DATA_CHN_ENC = 0,    /* ����ͨ����������� */
#if (VOS_OS_VER == VOS_LINUX)
    EN_DIAG_THRPUT_DATA_CHN_PHY,        /* ����ͨ��д������ͨ�� */

    EN_DIAG_THRPUT_DATA_CHN_CB,         /* ��������ͨ���ص� */
#endif
    EN_DIAG_THRPUT_MAX
} DIAG_THRPUT_ID_ENUM;


typedef struct
{
    VOS_UINT32      ulSlice;            /* ��ǰʱ���ʱ��� */
    VOS_UINT32      ulThroughput;       /* ������(Bytes/s) */
}DIAG_THRPUT_NODE_STRU;

typedef struct
{
    VOS_UINT32              ulSlice;            /* ���һ��ͳ�Ƶ�ʱ��� */
    VOS_UINT32              ulBytes;            /* ��ǰ���ۼƵ��ֽ��� */
    VOS_UINT32              ulMax;              /* �����ʷ�ֵ */
    VOS_UINT32              ulPtr;              /* ��ǰָ�� */
    DIAG_THRPUT_NODE_STRU   stNode[DIAG_THRPUT_DEBUG_NUM];
}DIAG_THRPUT_INFO_STRU;


/* DIAG_TRACE *******************************************/

#define DIAG_DEBUG_TRACE_DELAY          (1*32768)
#define DIAG_DEBUG_TXT_LOG_DELAY        (10*32768)
#define DIAG_DEBUG_TXT_LOG_LENGTH       256
typedef struct
{
    VOS_UINT32      ulModuleId;
    VOS_UINT32      ulLevel;
    VOS_UINT32      ulSn;
    VOS_CHAR        pucData[DIAG_DEBUG_TXT_LOG_LENGTH];
}DIAG_DEBUG_INFO_STRU;

typedef struct
{
    DIAG_FRAME_INFO_STRU                pstFrameInfo;
    DIAG_DEBUG_INFO_STRU                pstInfo;
}DIAG_DEBUG_FRAME_STRU;

/* A����C�˷��͵�debug��Ϣ *******************************************/

#define DIAG_DEBUG_DFR_BIT          0x00000001      /* �������� */
#define DIAG_DEBUG_NIL_BIT          0x00000002      /* ����log���ϱ��Ķ�λ��Ϣ */

typedef struct
{
    VOS_UINT32    ulSenderCpuId;
    VOS_UINT32    ulSenderPid;
    VOS_UINT32    ulReceiverCpuid;
    VOS_UINT32    ulReceiverPid;
    VOS_UINT32    ulLength;
    VOS_UINT32    ulMsgId;
    
    /* bit0 : DFR */
    /* bit1 : no ind log */
    VOS_UINT32      ulFlag;
} DIAG_A_DEBUG_C_REQ_STRU;


/* ���⺯���ӿ� *******************************************/

extern VOS_UINT32 diag_CreateDFR(VOS_CHAR *name, VOS_UINT32 ulLen, DIAG_DFR_INFO_STRU *pDfr);
extern VOS_VOID diag_SaveDFR(DIAG_DFR_INFO_STRU *pDfr, VOS_UINT8 *pData, VOS_UINT32 ulLen);
extern VOS_VOID diag_GetDFR(DIAG_DFR_INFO_STRU *pDfr);
extern DIAG_CBT_INFO_TBL_STRU* diag_DebugGetInfo(VOS_VOID);
extern VOS_VOID DIAG_ShowLNR(DIAG_LNR_ID_ENUM ulType, VOS_UINT32 n);
extern VOS_VOID DIAG_ShowLogCfg(VOS_UINT32 ulModuleId);
extern VOS_VOID DIAG_ShowEventCfg(VOS_UINT32 ulpid);
extern VOS_VOID DIAG_ShowAirCfg(VOS_VOID);
extern VOS_VOID DIAG_ShowLayerCfg(VOS_UINT32 ulModuleId, VOS_UINT32 ulSrcDst);
extern VOS_VOID DIAG_ShowUsrCfg(VOS_VOID);
extern VOS_VOID DIAG_ShowLost(VOS_VOID);
extern VOS_VOID DIAG_ShowTrans(VOS_UINT32 n);
extern VOS_VOID DIAG_Api_Statistic_Ind(DIAG_DEBUG_API_ENUM ulApi,DIAG_CBT_ID_ENUM ulOk,DIAG_CBT_ID_ENUM ulErr);
extern VOS_VOID DIAG_Show_Api_Statistic(VOS_VOID);
extern VOS_VOID DIAG_TRACE(VOS_CHAR* fmt,...);
extern VOS_VOID DIAG_ShowPsTransCmd(VOS_UINT32 n);
extern VOS_UINT32 diag_DebugMsgProc(MsgBlock* pMsgBlock);
extern VOS_VOID DIAG_DebugDFR(VOS_VOID);
extern VOS_VOID diag_ThroughputSave(DIAG_THRPUT_ID_ENUM enChn, VOS_UINT32 bytes);
extern VOS_VOID DIAG_ShowThroughput(VOS_UINT32 ulIndex);
extern VOS_VOID DIAG_DebugEventReport(VOS_UINT32 ulpid);
extern VOS_VOID DIAG_DebugLayerReport(VOS_VOID);
extern VOS_VOID DIAG_DebugLogReport(VOS_UINT32 ulpid, VOS_UINT32 level);
extern VOS_VOID DIAG_DebugTransReport(VOS_UINT32 ulpid);
extern VOS_VOID DIAG_DebugLayerCfg(VOS_UINT32 ulModuleId, VOS_UINT8 ucFlag);

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

