
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifndef __XMAILBOX_H__
#define __XMAILBOX_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include <product_config.h>
#include <mdrv.h>
#include <bsp_external_stub.h>
#include "xmailbox_types.h"


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/


/* ��������
PS initial (0) --> DSP start (2) --> DSP end (0xa5a5a5a5)
*/

#if 0
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
#endif

/* �쳣����ʱ���ڿռ����ƣ�����10����Ϣ */
#define MBX_ERROR_MNTN_NUM                  10

/* ��ά�ɲ��¼��Ϣ������ */
#define MAILBOX_MNTN_NUMBER                 100

#define MAILBOX_ADDR_OFFSET                 (0)

#define MAILBOX_WAKEUP_TIMEOUT              10    /* 100ms */

/* 32Kʱ�ӵ���ֵ:1ms */
#define MAILBOX_SLICE_THRESHOLD             32

/* �쳣����ʱ���������е�ǰ512�ֽ�Ԥ����PS��DSP */
#define MBX_ERROR_RESERVE_SIZE              512

#define MBX_SYSTEM_ERROR_SIZE               0x1000


#define BSP_CPHY_SHAKEHAND_CMP            (0xa5a5a5a5)

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
} xMAILBOX_CHANNEL_TABLE_STRU;

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
} xMAILBOX_RINGBUFF_STRU;


typedef struct __MAILBOX_MSG_HAED_STRU
{
    u16         usMsgSize;      /* ���ֽ�Ϊ��λ */
    u16         usDstMod;
    u8*         pPayload;
}xMAILBOX_MSG_HAED_STRU;


typedef struct
{
    BSP_BOOL                bMbxInit;               /* �����Ƿ��ʼ�� */
    unsigned int            mem_init;               /* �����ַ�Ƿ��ʼ���� 0 δ��ʼ�� */

    osl_sem_id              semDspMutex;
    osl_sem_id              semDspWakeup;
    BSP_BOOL                bDspWakeFlag;           /* ֻ������������ʱ���ã�����͹���ģ���λ��ѳ��� */

    BSP_xMBX_NOTIFY_FUNC     pfnSpNotifyProc;        /* ר�������ж��ϱ�����ص����� */

    BSP_xMBX_GET_STATUS_FUNC pfnGetDspStatusProc;    /* ��ȡDSP˯��״̬�ص����� */
    BSP_xMBX_DSP_AWAKE_FUNC  pfnDspForceAwakeProc;   /* ǿ�ƻ���DSP�ص����� */
    BSP_xMBX_GET_STATUS_FUNC pfnGetSpMsgProc;        /* ��ȡר�������Ƿ�����DSP˯�߻ص����� */
    BSP_xMBX_RCM_CALLBACK_FUNC pfnRcmNotifyProc;     /*��ȡ֪ͨRCM�Ļص�����*/

    BSP_BOOL                bIsSubFrameInt;         /* PS�����Ƿ�����֡�жϷ�ʽ */

    u32                     ulMsgLen;               /* PS�����е�һ����Ϣ����,0��ʾΪ�� */
    u32                     ulOmMsgLen;             /* OM�����е�һ����Ϣ����,0��ʾΪ�� */


    u32                     *pulAxiAddr;            /* PS����������ź��� */
    s32                     lAxiCnt;                /* ��¼AXI memory���õĴ�����������̲߳������� */
} xMAILBOX_MAINCTRL_STRU;


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


    u32     ulOmComOmRdNum;     /* OM����OM��ȡ���� */
    u32     ulOmComOmRdOKNum;   /* OM����OM��ȡ�ɹ����� */


    u32     ulPsComPsNotifyNum; /* PS����PS�ص����� */
    u32     ulPsComMspNotifyNum;/* PS����MSP�ص����� */
    u32     ulPsComRcmNotifyNum;/* PS����RCM�ص�����*/
    u32     ulPsComRttAgentNotifyNum;/* PS����RTT AGENT�ص����� */
} xMAILBOX_MNTN_NUMBER_STRU;

typedef struct
{
    u32     ulModId;            /* д�������� */
    u32     ulMsgId;            /* ��ϢID */
    u32     ulSlice;            /* ʱ�� */
} xMAILBOX_MNTN_MSGINFO_STRU;

/* дԭ��ʱ������ʱ�����Ϣ  */
typedef struct
{
    u32     ulFullNum;          /* �������Ĵ��� */

    u32     ulPtr;              /* ѭ��ָ��,����ѭ���洢 */
    xMAILBOX_MNTN_MSGINFO_STRU   astFullInfo[MAILBOX_MNTN_NUMBER];
} xMAILBOX_MNTN_MAILFULL_STRU;

/* �쳣��Ϣ  */
typedef struct
{
    u8      ucComPsType;        /* PS�������յ��ķ�PSԭ�CT/BT���͵���Ϣ */
    u32     ulMulCtBtMsg;       /* PS�����������յ�����CT/BT���͵���Ϣ����¼msgid */

    u32     ulLongestReq;       /* �������ʱ�� */

    u32     ulNInitSlic;        /* ���һ��δ��ʼ��ʱ�����ʱ���,��¼�ڴ汻�� */
} xMAILBOX_MNTN_ABNORMAL_STRU;


/* ���10��ԭ��������Ϣ��¼ */
typedef struct
{
    u32     ulModId;            /* д�������� */
    u32     ulMsgId;            /* ��ϢID */
    u32     ulRWPtr;            /* ��дָ�룬��16λ��ָ�룬��16λдָ�� */
    u32     ulSliceStart;       /* ���������ʱ�� */
    u32     ulSliceEnd;         /* д�������ʱ�� */
} xMAILBOX_MNTN_REQ_STRU;

typedef struct
{
    u32     ulPtr;              /* ѭ��ָ��,����ѭ���洢 */
    xMAILBOX_MNTN_REQ_STRU astReq[MAILBOX_MNTN_NUMBER];
} xMAILBOX_MNTN_REQINFO_STRU;


/* ��ȡ�����10��ԭ����Ϣ��¼ */
typedef struct
{
    u32     ulMsgId;            /* ��ϢID */
    u32     ulRWptr;            /* ��дָ�룬��16λ��ָ�룬��16λдָ�� */
    u32     ulSlice;            /* ��ȡʱ�� */
} xMAILBOX_MNTN_CNF_STRU;

typedef struct
{
    u32     ulPsPtr;            /* ѭ��ָ��,����ѭ���洢 */
    xMAILBOX_MNTN_CNF_STRU astPsCnf[MAILBOX_MNTN_NUMBER];

     u32     ulOmPtr;            /* ѭ��ָ��,����ѭ���洢 */
    xMAILBOX_MNTN_CNF_STRU astOmCnf[MAILBOX_MNTN_NUMBER];

    u32     ulRcmPtr;           /*ѭ��ָ�룬����ѭ���洢*/
    xMAILBOX_MNTN_CNF_STRU astRcmCnf[MAILBOX_MNTN_NUMBER];
    u32     ulCbtPtr;            /* ѭ��ָ��,����ѭ���洢 */
    xMAILBOX_MNTN_CNF_STRU astCbtCnf[MAILBOX_MNTN_NUMBER];
    u32     ulRttAgentPtr;       /* ѭ��ָ��,����ѭ���洢 */
    xMAILBOX_MNTN_CNF_STRU astRttAgentCnf[MAILBOX_MNTN_NUMBER];
} xMAILBOX_MNTN_CNFINFO_STRU;


typedef struct
{
    u32     ulPtr;              /* ѭ��ָ��,����ѭ���洢 */
    u32     ulSlice[MAILBOX_MNTN_NUMBER];   /* slice ��¼ */
} xMAILBOX_MNTN_INTSLICE_STRU;


typedef struct
{
    u32     ulSrc;              /* ��ȡ��id */
    u32     ulSlice;            /* ��ȡ�ķ���ʱ�� */
} xMAILBOX_MNTN_READ_STRU;

typedef struct
{
    u32     ulPsPtr;            /* ѭ��ָ��,����ѭ���洢 */
    xMAILBOX_MNTN_READ_STRU astRead[MAILBOX_MNTN_NUMBER];

    u32     ulOmPtr;            /* ѭ��ָ��,����ѭ���洢 */
    xMAILBOX_MNTN_READ_STRU astOmRead[MAILBOX_MNTN_NUMBER];

} xMAILBOX_MNTN_READINFO_STRU;


typedef struct
{
    u32     ulSlice1;            /* ����ǿ�ƻ��ѵ�ʱ�� */
    u32     ulSlice2;            /* ǿ�ƻ��ѻظ���ʱ�� */
    u32     ulSlice3;            /* ���Ѵ����ʱ�� */
} xMAILBOX_MNTN_WAKEUP_STRU;

typedef struct
{
    u32     ulPtr;
    xMAILBOX_MNTN_WAKEUP_STRU astwakeup[MAILBOX_MNTN_NUMBER];   /* ǿ�ƻ���ʱ�� */
} xMAILBOX_MNTN_SLEEP_STRU;

typedef struct
{
    MAILBOX_CALLBACK_TYPE       cbType;                     /*�ص�����*/
    BSP_BOOL                    ulWakeup;                   /* �Ƿ������份�� */
    u32                         ulSliceStart;
    u32                         ulSliceEnd;
} xMAILBOX_MNTN_CB_STRU;

typedef struct
{
    u32 ulPtr;
    xMAILBOX_MNTN_CB_STRU    astCbInfo[MAILBOX_MNTN_NUMBER];
} xMAILBOX_MNTN_SLEEPCB_STRU;

typedef struct
{
    BSP_BOOL                        bdbg;
    xMAILBOX_MNTN_ABNORMAL_STRU      stAbnormal;         /* �����쳣 */
    xMAILBOX_MNTN_NUMBER_STRU        stNumber;           /* ԭ����������Ϣ */
    xMAILBOX_MNTN_MAILFULL_STRU      stMailFull;         /* ��������Ϣ */
    xMAILBOX_MNTN_REQINFO_STRU       stReqInfo;          /* ���N��ԭ��������Ϣ��¼ */
    xMAILBOX_MNTN_CNFINFO_STRU       stCnfInfo;          /* ��ȡ���N��ԭ����Ϣ��¼ */
    xMAILBOX_MNTN_INTSLICE_STRU      stIntInfo;          /* ���N�������жϵ�ʱ�� */
    xMAILBOX_MNTN_INTSLICE_STRU      stCallback;         /* �ص�Э��ջ��ʱ�� */
    xMAILBOX_MNTN_INTSLICE_STRU      stRcmCallback;      /* �ص�RCM��ʱ��*/
    xMAILBOX_MNTN_INTSLICE_STRU      stDirectInfo;       /* ֱ��д����*/
    xMAILBOX_MNTN_INTSLICE_STRU      stRttAgentCallback; /* �ص�RTT AGENT��ʱ�� */
    xMAILBOX_MNTN_READINFO_STRU      stReadInfo;         /* �����ȡ�����ʱ�� */
    xMAILBOX_MNTN_SLEEP_STRU         stSleepInfo;        /* ��͹���ģ�鷢��ǿ�ƻ��ѵ���Ϣ */
    xMAILBOX_MNTN_SLEEPCB_STRU       stSleepCbInfo;      /* �͹���ģ���������ӿڴ�����Ϣ */
} xMAILBOX_MNTN_STRU;

typedef struct {
    unsigned int ulCphyMbxHpaUpAddr;             /* CPHY<->CCORE, HPA�������л���ַ  */
    unsigned int ulCphyMbxHpaDownAddr;           /* CPHY<->CCORE, HPA�������л���ַ  */
    unsigned int ulCphyMbxOmDownAddr;            /* CPHY<->CCORE, OM�������л���ַ   */
    unsigned int ulCphyMbxLoadMemAddr;           /* CPHY<->CCORE, ���ص�ַ           */
    unsigned int ulCphyMbxWorkModeAddr;          /* CPHY<->CCORE, ����ģʽ��ַ       */
    void*        pCphyMntnInfoAddr;
    void*        pCphyWakeupAddr;
} xMAILBOX_ADDR_SHARE_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
#define xMbx_Printf(fmt,...) \
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_XMBX,"[CBBE16 MailBox]:<%s> "fmt,__FUNCTION__,##__VA_ARGS__)

#define xMbx_invalid_type(type) ((type < EN_MAILBOX_SERVICE_BUTT) || (type >= EN_MAILBOX_SERVICE_TOTAL_BUTT))
#define xMbx_invalid_module(mod) ((mod < MBX_ADDRESSER_XSYS_PHY_RL) || (mod > MBX_ADDRESSER_XSYS_PHY_HS_DIAG))

extern xMAILBOX_MNTN_STRU               g_stxMbxMntn;
extern xMAILBOX_MAINCTRL_STRU           g_stxMbxCtrl;
extern xMAILBOX_CHANNEL_TABLE_STRU      g_astxMbxChnTbl[EN_MAILBOX_SERVICE_TOTAL_BUTT - EN_MAILBOX_SERVICE_BUTT];
extern xMAILBOX_ADDR_SHARE_STRU         g_stxMbxShareAddr;

#define xMbx_Trace(pdata,ulLen)                                                              \
    if(g_stxMbxMntn.bdbg == TRUE)                                                            \
    {\
        u32 i;\
        xMbx_Printf("<%s> datalen : 0x%x,slice :0x%x\n",__func__,ulLen,bsp_get_slice_value());     \
        for(i=0;i<ulLen;i++)\
        {\
            xMbx_Printf("%02x ",*((char*)pdata+i));\
        }\
        xMbx_Printf("\n");\
    };

#define xMbx_get_tbl(index)    &g_astxMbxChnTbl[index - EN_MAILBOX_SERVICE_BUTT]

/*****************************************************************************
  10 ��������
*****************************************************************************/

extern void xMbx_ComPsIntProc(void);


extern s32  xMbx_RbuffWrite(xMAILBOX_RINGBUFF_STRU* pHead, xMAILBOX_MSG_HAED_STRU* pstMsg);

extern u32  xMbx_NewMsgReadOut(xMAILBOX_MSG_HAED_STRU* pMsg,xMAILBOX_RINGBUFF_STRU* pMbxHandle);

extern void xMbx_SpIntProc(void);

extern void xMbx_BbeIpcProc(void);

extern void xMbx_WrFullProc(xMAILBOX_RINGBUFF_STRU* pstAddr, u32 usSize, u32 ulRd, u32 ulWr);

extern void xMbx_SystemError(u32 errcode, u32 ulPara1, u32 ulPara2, u32 ulPara3);

extern void xMbx_DumpSave(u8* pData, u32 ulSize);

extern u32  xmbx_IsChnModMatch(u32 ulChn, u32 ulMod);

extern void xMbx_MntnWriteEnd(xMAILBOX_RINGBUFF_STRU* pHead, xMAILBOX_MSG_HAED_STRU* pstMsg, u32 ulTempPPTR);

extern void xMbx_MntnReadEnd(void* pData, enum __MBX_ADDRESSEE_ID_ENUM__ enMbxType, u32 pRd, u32 pWr);

extern u32  xmbx_GetChn(u32 ulMod);

extern u32  BSP_xMailBox_IsDspSleep(void);

#pragma pack(0)




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* end of mailbox.h */

