

#ifndef __MAILBOX_H__
#define __MAILBOX_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include <product_config.h>
#include <mdrv.h>
#include <bsp_external_stub.h>
#include "mailbox_types.h"
#include <mdrv_mailbox.h>


#pragma pack(4)


#define FEATURE_MAILBOX_CDMA_NOT_USE FEATURE_OFF
/*****************************************************************************
  2 �궨��
*****************************************************************************/


/* ��������
PS initial (0) --> DSP start (2) --> DSP end (0xa5a5a5a5)
*/

/* DSP���ֵ�ַ */
#define BSP_DSP_INIT_RESULT_ADDR        LPHY_MAILBOX_LOAD_MEMORY_ADDR

/* ���ù���ģʽ(������˫����RTT��ȫϵͳ��) */
#define BSP_DSP_WORKING_MODE_ADDR       LPHY_MAILBOX_LPHY_WORKING_MODE_ADDR


/* ���ֳɹ���־ */
#define BSP_TL_SHAKEHAND_CMP            (0xa5a5a5a5)


/* PS�������������ʼ��ַ��size */
#define MAILBOX_PS_DOWN_ADDR                LPHY_MAILBOX_LHPA_DOWN_BASE_ADDR
#define MAILBOX_PS_UP_ADDR                  LPHY_MAILBOX_LHPA_UP_BASE_ADDR

#define MAILBOX_PS_DOWN_SIZE                LPHY_MAILBOX_LHPA_DOWN_SIZE
#define MAILBOX_PS_UP_SIZE                  LPHY_MAILBOX_LHPA_UP_SIZE


/* OM�����������ʼ��ַ��size */
#define MAILBOX_OM_DOWN_ADDR                LPHY_MAILBOX_OM_DOWN_BASE_ADDR

#define MAILBOX_OM_DOWN_SIZE                LPHY_MAILBOX_OM_DOWN_SIZE


/* ר���������������ʼ��ַ */
#define MAILBOX_SP_UP_ADDR                  LPHY_MAILBOX_LMAC_UP_BASE_ADDR
#define MAILBOX_SP_DOWN_ADDR                LPHY_MAILBOX_LMAC_DOWN_BASE_ADDR

/* �쳣����ʱ���ڿռ����ƣ�����10����Ϣ */
#define MBX_ERROR_MNTN_NUM                  10

/* ��ά�ɲ��¼��Ϣ������ */
#define MAILBOX_MNTN_NUMBER                 100

#define MAILBOX_ADDR_OFFSET                 MASTER_TCM_ADDR_OFFSET

#define MAILBOX_WAKEUP_TIMEOUT              10    /* 100ms */

/* 32Kʱ�ӵ���ֵ:1ms */
#define MAILBOX_SLICE_THRESHOLD             32

/* �쳣����ʱ���������е�ǰ512�ֽ�Ԥ����PS��DSP */
#define MBX_ERROR_RESERVE_SIZE              512

#define MBX_SYSTEM_ERROR_SIZE               0x1000



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum __MBX_ADDRESSEE_ID_ENUM__
{
    MBX_ADDRESSER_LTE_PHY_RL = 0,
    MBX_ADDRESSER_LTE_PHY_OM,
    MBX_ADDRESSER_LTE_PHY_BT,
    MBX_ADDRESSER_LTE_PHY_CT,
    MBX_ADDRESSER_LTE_PHY_COEX,
    MBX_ADDRESSER_LTE_PHY_HS_DIAG,
    MBX_ADDRESSER_LTE_PHY_RCM,

    MBX_ADDRESSER_TDS_PHY_RL = 16,
    MBX_ADDRESSER_TDS_PHY_OM,
    MBX_ADDRESSER_TDS_PHY_BT,
    MBX_ADDRESSER_TDS_PHY_CT,
    MBX_ADDRESSER_TDS_PHY_HS_DIAG,
    MBX_ADDRESSER_TDS_PHY_RCM,

    MBX_ADDRESSER_XSYS_PHY_RL = 32,
    MBX_ADDRESSER_XSYS_PHY_OM,
    MBX_ADDRESSER_XSYS_PHY_BT,
    MBX_ADDRESSER_XSYS_PHY_CT,
    MBX_ADDRESSER_XSYS_PHY_HS_DIAG,

    MBX_ADDRESSER_RTT_SYS_CTRL = 48,
    MBX_ADDRESSER_RTT_AGENT,
    MBX_ADDRESSER_RTT_CBT,
    MBX_ADDRESSER_RTT_HIFI_AGENT,

    MBX_ADDRESSEE_BUTT
};

enum MBX_SYSTEM_ERROR_ID_ENUM
{
    MBX_ERROR_WR_FULL = 0,      /* ����������                   */
    MBX_ERROR_DSP_IPC,          /* ������������DSP IPC֪ͨARM   */
    MBX_ERROR_PS_TIMEOUT,       /* PS��DSP��Ϣ��ʱ              */
    MBX_ERROR_UP_WR,            /* ��������дָ���쳣           */
    MBX_ERROR_DL_MOD,           /* ���������ָ��MOD�쳣        */

    MBX_ERROR_BUTT
};


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

typedef struct
{
    u32                     ulMbxChn;           /* ����ͨ�� */
    u32                     ulModule;           /* ģ��ID */
    u32                     ulDlAddr;           /* ���������ַ */
    u32                     ulUlAddr;           /* ���������ַ */
    BSP_MBX_NOTIFY_FUNC     pFnCallBack;        /* �ص����� */
    IPC_INT_LEV_E           ulIntNum;           /*ARM -> DSP�жϺ�*/
} MAILBOX_CHANNEL_TABLE_STRU;

extern MAILBOX_CHANNEL_TABLE_STRU g_astMbxChnTbl[EN_MAILBOX_SERVICE_BUTT];


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*lint --e{43}*/ /*PCLINT: aulMsgBuf 43 is inevitable*/
typedef struct
{
    u8*         pucRbufAddr;    /* ����buffer����ʼ��ַ(DSP��)��ARM����Ҫ-0x0f000000 */
    u32         ulRbufSize;     /* Ring Buffer ���ܳ��ȣ��ֽ�Ϊ��λ */
    u32         ulRbufRdPtr;    /* Ring Buffer ���ÿռ���׵�ַ,��ָ�� */
    u32         ulRbufWrPtr;    /* Ring Buffer ���пռ���׵�ַ,дָ�� */
    u32         aulMsgBuf[0];
} MAILBOX_RINGBUFF_STRU;


typedef struct __MAILBOX_MSG_HAED_STRU
{
    u16         usMsgSize;      /* ���ֽ�Ϊ��λ */
    u16         usDstMod;
    u8*         pPayload;
}MAILBOX_MSG_HAED_STRU;


typedef struct
{
    BSP_BOOL                bMbxInit;               /* �����Ƿ��ʼ�� */

    osl_sem_id              semDspMutex;
    osl_sem_id              semDspWakeup;
    BSP_BOOL                bDspWakeFlag;           /* ֻ������������ʱ���ã�����͹���ģ���λ��ѳ��� */

    BSP_MBX_NOTIFY_FUNC     pfnSpNotifyProc;        /* ר�������ж��ϱ�����ص����� */

    BSP_MBX_GET_STATUS_FUNC pfnGetDspStatusProc;    /* ��ȡDSP˯��״̬�ص����� */
    BSP_MBX_DSP_AWAKE_FUNC  pfnDspForceAwakeProc;   /* ǿ�ƻ���DSP�ص����� */
    BSP_MBX_GET_STATUS_FUNC pfnGetSpMsgProc;        /* ��ȡר�������Ƿ�����DSP˯�߻ص����� */
    BSP_MBX_RCM_CALLBACK_FUNC pfnRcmNotifyProc;     /*��ȡ֪ͨRCM�Ļص�����*/

    BSP_BOOL                bIsSubFrameInt;         /* PS�����Ƿ�����֡�жϷ�ʽ */

    u32                     ulMsgLen;               /* PS�����е�һ����Ϣ����,0��ʾΪ�� */
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    u32                 ulOmMsgLen;                 /* OM�����е�һ����Ϣ����,0��ʾΪ�� */
#endif

    u32                     *pulAxiAddr;            /* PS����������ź��� */
    s32                     lAxiCnt;                /* ��¼AXI memory���õĴ�����������̲߳������� */
} MAILBOX_MAINCTRL_STRU;


/* ����ģ��Ŀ�ά�ɲ���Ϣ */

/* ԭ����������Ϣ  */
typedef struct
{
    u32     ulComPsIntNum;      /* PS�����жϴ��� */
    u32     ulSpIntNum;         /* ר�������жϴ��� */

    u32     ulPsComReqNum;      /* PS����������� */
    u32     ulPsComPsReqNum;    /* PS����PSд������� */
    u32     ulPsComMspReqNum;   /* PS����MSPд������� */
    u32     ulPsComRcmReqNum;   /* PS����RCMд�������*/
    u32     ulPsComRttAgentReqNum; /* PS����RttAgentд������� */
    u32     ulOmComReqNum;      /* OM����д������� */

    u32     ulPsComPsRdNum;     /* PS����PS��ȡ���� */
    u32     ulPsComPsRdOKNum;   /* PS����PS��ȡ�ɹ����� */
    u32     ulPsComRcmRdNum;    /* PS����RCM��ȡ����*/
    u32     ulPsComRcmRdOKNum;  /* PS����RCM��ȡ����*/
    u32     ulPsComMspRdNum;    /* PS����MSP��ȡ���� */
    u32     ulPsComMspRdOKNum;  /* PS����MSP��ȡ�ɹ����� */
    u32     ulPsComRttAgentRdNum;/* PS����RTT AGENT��ȡ���� */
    u32     ulPsComRttAgentRdOKNum;/* PS����RTT AGENT��ȡ�ɹ����� */

#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    u32     ulOmComOmRdNum;     /* OM����OM��ȡ���� */
    u32     ulOmComOmRdOKNum;   /* OM����OM��ȡ�ɹ����� */
#endif

    u32     ulPsComPsNotifyNum; /* PS����PS�ص����� */
    u32     ulPsComMspNotifyNum;/* PS����MSP�ص����� */
    u32     ulPsComRcmNotifyNum;/* PS����RCM�ص�����*/
    u32     ulPsComRttAgentNotifyNum;/* PS����RTT AGENT�ص����� */
} MAILBOX_MNTN_NUMBER_STRU;

typedef struct
{
    u32     ulModId;            /* д�������� */
    u32     ulMsgId;            /* ��ϢID */
    u32     ulSlice;            /* ʱ�� */
} MAILBOX_MNTN_MSGINFO_STRU;

/* дԭ��ʱ������ʱ�����Ϣ  */
typedef struct
{
    u32     ulFullNum;          /* �������Ĵ��� */

    u32     ulPtr;              /* ѭ��ָ��,����ѭ���洢 */
    MAILBOX_MNTN_MSGINFO_STRU   astFullInfo[MAILBOX_MNTN_NUMBER];
} MAILBOX_MNTN_MAILFULL_STRU;

/* �쳣��Ϣ  */
typedef struct
{
    u8      ucComPsType;        /* PS�������յ��ķ�PSԭ�CT/BT���͵���Ϣ */
    u32     ulMulCtBtMsg;       /* PS�����������յ�����CT/BT���͵���Ϣ����¼msgid */

    u32     ulLongestReq;       /* �������ʱ�� */

    u32     ulNInitSlic;        /* ���һ��δ��ʼ��ʱ�����ʱ���,��¼�ڴ汻�� */
} MAILBOX_MNTN_ABNORMAL_STRU;


/* ���10��ԭ��������Ϣ��¼ */
typedef struct
{
    u32     ulModId;            /* д�������� */
    u32     ulMsgId;            /* ��ϢID */
    u32     ulRWPtr;            /* ��дָ�룬��16λ��ָ�룬��16λдָ�� */
    u32     ulSliceStart;       /* ���������ʱ�� */
    u32     ulSliceEnd;         /* д�������ʱ�� */
} MAILBOX_MNTN_REQ_STRU;

typedef struct
{
    u32     ulPtr;              /* ѭ��ָ��,����ѭ���洢 */
    MAILBOX_MNTN_REQ_STRU astReq[MAILBOX_MNTN_NUMBER];
} MAILBOX_MNTN_REQINFO_STRU;


/* ��ȡ�����10��ԭ����Ϣ��¼ */
typedef struct
{
    u32     ulMsgId;            /* ��ϢID */
    u32     ulRWptr;            /* ��дָ�룬��16λ��ָ�룬��16λдָ�� */
    u32     ulSlice;            /* ��ȡʱ�� */
} MAILBOX_MNTN_CNF_STRU;

typedef struct
{
    u32     ulPsPtr;            /* ѭ��ָ��,����ѭ���洢 */
    MAILBOX_MNTN_CNF_STRU astPsCnf[MAILBOX_MNTN_NUMBER];
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
     u32     ulOmPtr;            /* ѭ��ָ��,����ѭ���洢 */
    MAILBOX_MNTN_CNF_STRU astOmCnf[MAILBOX_MNTN_NUMBER];
#endif
    u32     ulRcmPtr;           /*ѭ��ָ�룬����ѭ���洢*/
    MAILBOX_MNTN_CNF_STRU astRcmCnf[MAILBOX_MNTN_NUMBER];
    u32     ulCbtPtr;            /* ѭ��ָ��,����ѭ���洢 */
    MAILBOX_MNTN_CNF_STRU astCbtCnf[MAILBOX_MNTN_NUMBER];
    u32     ulRttAgentPtr;       /* ѭ��ָ��,����ѭ���洢 */
    MAILBOX_MNTN_CNF_STRU astRttAgentCnf[MAILBOX_MNTN_NUMBER];
} MAILBOX_MNTN_CNFINFO_STRU;


typedef struct
{
    u32     ulPtr;              /* ѭ��ָ��,����ѭ���洢 */
    u32     ulSlice[MAILBOX_MNTN_NUMBER];   /* slice ��¼ */
} MAILBOX_MNTN_INTSLICE_STRU;


typedef struct
{
    u32     ulSrc;              /* ��ȡ��id */
    u32     ulSlice;            /* ��ȡ�ķ���ʱ�� */
} MAILBOX_MNTN_READ_STRU;

typedef struct
{
    u32     ulPsPtr;            /* ѭ��ָ��,����ѭ���洢 */
    MAILBOX_MNTN_READ_STRU astRead[MAILBOX_MNTN_NUMBER];
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    u32     ulOmPtr;            /* ѭ��ָ��,����ѭ���洢 */
    MAILBOX_MNTN_READ_STRU astOmRead[MAILBOX_MNTN_NUMBER];
#endif


} MAILBOX_MNTN_READINFO_STRU;


typedef struct
{
    u32     ulSlice1;            /* ����ǿ�ƻ��ѵ�ʱ�� */
    u32     ulSlice2;            /* ǿ�ƻ��ѻظ���ʱ�� */
    u32     ulSlice3;            /* ���Ѵ����ʱ�� */
} MAILBOX_MNTN_WAKEUP_STRU;

typedef struct
{
    u32     ulPtr;
    MAILBOX_MNTN_WAKEUP_STRU astwakeup[MAILBOX_MNTN_NUMBER];   /* ǿ�ƻ���ʱ�� */
} MAILBOX_MNTN_SLEEP_STRU;

typedef struct
{
    MAILBOX_CALLBACK_TYPE       cbType;                     /*�ص�����*/
    BSP_BOOL                    ulWakeup;                   /* �Ƿ������份�� */
    u32                         ulSliceStart;
    u32                         ulSliceEnd;
}MAILBOX_MNTN_CB_STRU;

typedef struct
{
    u32 ulPtr;
    MAILBOX_MNTN_CB_STRU    astCbInfo[MAILBOX_MNTN_NUMBER];
}MAILBOX_MNTN_SLEEPCB_STRU;

typedef struct
{
    BSP_BOOL                        bdbg;
    MAILBOX_MNTN_ABNORMAL_STRU      stAbnormal;         /* �����쳣 */
    MAILBOX_MNTN_NUMBER_STRU        stNumber;           /* ԭ����������Ϣ */
    MAILBOX_MNTN_MAILFULL_STRU      stMailFull;         /* ��������Ϣ */
    MAILBOX_MNTN_REQINFO_STRU       stReqInfo;          /* ���N��ԭ��������Ϣ��¼ */
    MAILBOX_MNTN_CNFINFO_STRU       stCnfInfo;          /* ��ȡ���N��ԭ����Ϣ��¼ */
    MAILBOX_MNTN_INTSLICE_STRU      stIntInfo;          /* ���N�������жϵ�ʱ�� */
    MAILBOX_MNTN_INTSLICE_STRU      stCallback;         /* �ص�Э��ջ��ʱ�� */
    MAILBOX_MNTN_INTSLICE_STRU      stRcmCallback;      /* �ص�RCM��ʱ��*/
    MAILBOX_MNTN_INTSLICE_STRU      stDirectInfo;       /* ֱ��д����*/
    MAILBOX_MNTN_INTSLICE_STRU      stRttAgentCallback; /* �ص�RTT AGENT��ʱ�� */
    MAILBOX_MNTN_READINFO_STRU      stReadInfo;         /* �����ȡ�����ʱ�� */
    MAILBOX_MNTN_SLEEP_STRU         stSleepInfo;        /* ��͹���ģ�鷢��ǿ�ƻ��ѵ���Ϣ */
    MAILBOX_MNTN_SLEEPCB_STRU       stSleepCbInfo;      /* �͹���ģ���������ӿڴ�����Ϣ */
} MAILBOX_MNTN_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
#define Mbx_Printf(fmt,...) \
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MBX,"[BBE16 MailBox]:<%s> "fmt,__FUNCTION__,##__VA_ARGS__)
extern MAILBOX_MNTN_STRU       g_stMbxMntn;
extern MAILBOX_MAINCTRL_STRU   g_stMbxCtrl;

#define Mbx_Trace(pdata,ulLen)                                                              \
    if(g_stMbxMntn.bdbg == TRUE)                                                            \
    {\
        u32 i;\
        Mbx_Printf("<%s> datalen : 0x%x,slice :0x%x\n",__func__,ulLen,bsp_get_slice_value());     \
        for(i=0;i<ulLen;i++)\
        {\
            Mbx_Printf("%02x ",*((char*)pdata+i));\
        }\
        Mbx_Printf("\n");\
    };


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern void Mbx_ComPsIntProc(void);

extern void Mbx_ForbidDspSleep(void);

extern void Mbx_AllowDspSleep(void);

extern s32 Mbx_RbuffWrite(MAILBOX_RINGBUFF_STRU* pHead, MAILBOX_MSG_HAED_STRU* pstMsg);

extern u32 Mbx_NewMsgReadOut(MAILBOX_MSG_HAED_STRU* pMsg,MAILBOX_RINGBUFF_STRU* pMbxHandle);

extern void Mbx_SpIntProc(void);

extern void Mbx_ComPsPreProc(void);

extern void Mbx_BbeIpcProc(void);

extern void Mbx_WrFullProc(MAILBOX_RINGBUFF_STRU* pstAddr, u32 usSize, u32 ulRd, u32 ulWr);

extern void Mbx_SystemError(u32 errcode, u32 ulPara1, u32 ulPara2, u32 ulPara3);

extern void Mbx_DumpSave(u8* pData, u32 ulSize);

extern u32 mbx_IsChnModMatch(u32 ulChn, u32 ulMod);

extern void Mbx_MntnWriteEnd(MAILBOX_RINGBUFF_STRU* pHead, MAILBOX_MSG_HAED_STRU* pstMsg, u32 ulTempPPTR);

extern void Mbx_MntnReadEnd(void* pData, enum __MBX_ADDRESSEE_ID_ENUM__ enMbxType, u32 pRd, u32 pWr);

extern u32 mbx_GetChn(u32 ulMod);

extern u32 BSP_MailBox_IsDspSleep(void);

#pragma pack(0)




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* end of mailbox.h */

