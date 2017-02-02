
#ifndef __TTF_MEM_H_
#define __TTF_MEM_H_

/******************************************************************************
  1 ����ͷ�ļ�����
******************************************************************************/
#include "TtfMemoryMap.h"
#include "TTFLink.h"
#include "TTFMemInterface.h"
#include "TtfNvInterface.h"
#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/******************************************************************************
  2 �궨��
******************************************************************************/
#define TTF_NODE_MEM_DBG                FEATURE_OFF

/* TTF���ò����궨�� */
#define TTF_MEM_GET_HDR_RSV_LEN(pMem)           (VOS_UINT16)((pMem)->pData - (pMem)->pOrigData)

#define TTF_MEM_INIT(pMem, usMemType, usMemLen) \
{                                               \
    TTF_NodeInit(&pMem->stNode);                \
    (pMem)->pNext   = VOS_NULL_PTR;             \
    (pMem)->usType  = (usMemType);              \
    (pMem)->usLen   = (usMemLen);               \
    (pMem)->usUsed  = 0;                        \
    (pMem)->ucDataPriority = (VOS_UINT8)TTF_PS_DATA_PRIORITY_NORMAL;\
}

#if (FEATURE_ON == FEATURE_TTF_MEM_DEBUG)
#define TTF_MEM_STATE_INIT(pMem) \
    (pMem)->enMemStateFlag  = TTF_BLK_MEM_STATE_FREE;
#endif

#define TTF_MEM_SET(pMem, usMemType, usMemLen) \
{                                               \
    TTF_NodeInit(&pMem->stNode);                \
    (pMem)->pNext   = VOS_NULL_PTR;             \
    (pMem)->usType  = (usMemType);              \
    (pMem)->usLen   = (usMemLen);               \
    (pMem)->usUsed  = (usMemLen);               \
    (pMem)->ucDataPriority = (VOS_UINT8)TTF_PS_DATA_PRIORITY_NORMAL;\
}

#define TTF_MEM_RESET(pMem)                     \
{                                               \
    TTF_LINK_INIT_NODE(&pMem->stNode);          \
    (pMem)->pNext   = VOS_NULL_PTR;             \
    (pMem)->usLen  += TTF_MEM_GET_HDR_RSV_LEN((pMem)); \
    (pMem)->usUsed  = 0;                        \
    (pMem)->pData   = (pMem)->pOrigData;        \
    (pMem)->ucDataPriority = (VOS_UINT8)TTF_PS_DATA_PRIORITY_NORMAL;\
}

#define TTF_MEM_CLEAN(pMem)                     \
{                                               \
    TTF_LINK_INIT_NODE(&pMem->stNode);          \
    (pMem)->pNext       = VOS_NULL_PTR;         \
    (pMem)->usLen       = 0;                    \
    (pMem)->usUsed      = 0;                    \
    (pMem)->pOrigData   = VOS_NULL_PTR;         \
    (pMem)->pData       = (pMem)->pOrigData;    \
    (pMem)->ucDataPriority = (VOS_UINT8)TTF_PS_DATA_PRIORITY_NORMAL;\
}

/*�ܳ�����ָ��ָ��ͷ������������?
 */
#define TTF_MEM_REMOVE_FROM_HDR(pMem, usNum)    \
{                                               \
    (pMem)->pData  += (usNum);                  \
    (pMem)->usLen  -= (usNum);                  \
    (pMem)->usUsed -= (usNum);                  \
}

#define TTF_MEM_RESUME_TO_HDR(pMem, usNum)      \
{                                               \
    (pMem)->pData  -= (usNum);                  \
    (pMem)->usLen  += (usNum);                  \
    (pMem)->usUsed += (usNum);                  \
}

#define TTF_MEM_NEXT(pMem)                      ((pMem)->pNext)

#define TTF_MEM_SIZE                            sizeof(TTF_MEM_ST)


#if (FEATURE_ON == FEATURE_DC_MIMO)
#define TTF_BLK_MEM_ALERT_THLD                  (1)
#else
#define TTF_BLK_MEM_ALERT_THLD                  (300)
#endif


#define TTF_MALLOC_STATIC_WITH_FILE_LINE(ulPid,size,ulFileID, ulLine)    \
    V_MemAlloc(ulPid, STATIC_MEM_PT, (size), VOS_TRUE, ulFileID, ulLine)
#define TTF_MALLOC_WITH_FILE_LINE(ulPid,size,ulFileID, ulLine)    \
    V_MemAlloc(ulPid, DYNAMIC_MEM_PT, (size), VOS_TRUE, ulFileID, ulLine)


#define TTF_GET_LEN_INDEX(pstTtfMemPoolInfo, usLen) \
    ((pstTtfMemPoolInfo)->aucLenIndexTable[(usLen)])

#define TTF_MEM_NET_PAD                     (64)
#define TTF_MEM_WIFI_PAD                    (256)
#define TTF_MEM_MAC_HEAD_LEN                (14)

/* Ԥ����Linux skbuff��share�ռ䣬=sizeof(struct skb_shared_info)
Linux�汾�����ı�ʱ��Ҫ����check��ֵ */
#define TTF_MEM_SKBUFF_SHARE_INFO_SIZE      (264)

/* Gģ19�龲̬�ڴ� */
#ifdef __UT_CENTER__
#define TTF_NODE_MEM_G_STATIC_CNT           (0)
#else
#define TTF_NODE_MEM_G_STATIC_CNT           (19)
#endif

/* ����DSDS����RRMģ��ڵ��ڴ� */
#define RRM_NODE_MEM_CNT                    (100)

#define TTF_NODE_MEM_POOL_SIZE              (52)
#define TTF_NODE_MEM_W_CNT                  (4352)
#if (FEATURE_OFF == FEATURE_MULTI_MODEM)
#define TTF_NODE_MEM_POOL_CNT               (TTF_NODE_MEM_G_STATIC_CNT + TTF_NODE_MEM_W_CNT)
#else
#define TTF_NODE_MEM_DSDA_G_STATIC_CNT      (1202)
/* ˫���£�����һ��Gģ����Class 33���㣺����RLC�������640������RLC����512��
  ����SDU�ڵ���Ҫ512*74*2/1500=50�飬������640+512+50=1202�飨ռ���ڴ�Լ60KB����*/
#define TTF_NODE_MEM_POOL_CNT               (TTF_NODE_MEM_G_STATIC_CNT + TTF_NODE_MEM_W_CNT + TTF_NODE_MEM_DSDA_G_STATIC_CNT)
#endif

#define TTF_NODE_MEM_POOL_BASE_ADDR         (g_stNodeMemSpace)

#define RRM_NODE_MEM_POOL_BASE_ADDR         (g_astRrmNodeMemSpace)

/* C-CPU�ڴ�����룬��Ӧλ���� */
#define TTF_MEM_MASK_POOL(ucPoolId)         (((VOS_UINT32)1) << (ucPoolId))

/* C-CPU����IP�������ڴ����Ҫ��ADQԤ���ڴ棬����ȡ����IPF_ULAD0_DESC_SIZE + IPF_ULAD1_DESC_SIZE */
#define TTF_MEM_UL_IP_DATA_POOL_RSV_CNT     (IPF_ULAD0_DESC_SIZE + IPF_ULAD1_DESC_SIZE)

/* �ڴ�����ʧ�ܸ�λ��ӡ���� */
#define TTF_MEM_DEBUG_NUM                   (60)


#define TTF_MEM_RCOV_THRES                  (0x1F)
#define TTF_MEM_RCOV_TIMER_LEN              (10 * 60 * 1000 * 33)   /* Ĭ��10����, ��λslice */

#define TTF_MEM_RCOV_DEF_POOL_MSK           (TTF_MEM_MASK_POOL(TTF_MEM_POOL_ID_DL_SHARE) | TTF_MEM_MASK_POOL(TTF_MEM_POOL_ID_DL_PDU))

#define TTF_MEM_RST_RCOV_ENT()              PS_MEM_SET(&g_stTtfMemRcovEnt, 0, sizeof(TTF_MEM_RCOV_ENTITY_STRU))

#define TTF_MEM_SET_RCOV_ENT_POOL_MSK(poolMsk) \
    (g_stTtfMemRcovEnt.ucRcovPoolMsk = (poolMsk))

#define TTF_MEM_CHK_NEED_RCOV_POOL(poolMsk) \
    (poolMsk == (poolMsk & g_stTtfMemRcovEnt.ucRcovPoolMsk))


#define TTF_MEM_SET_RCOV_ENT_THRES(ulPoolId, ulThres) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulRcovThres = (ulThres))

#define TTF_MEM_GET_RCOV_ENT_THRES(ulPoolId) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulRcovThres)

#define TTF_MEM_SET_RCOV_ENT_TIMER_LEN(ulPoolId, ulTmLen) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulRcovTimerLen = (ulTmLen))

#define TTF_MEM_GET_RCOV_ENT_TIMER_LEN(ulPoolId) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulRcovTimerLen)

#define TTF_MEM_SET_RCOV_ENT_STATE(ulPoolId, state) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulState = (state))

#define TTF_MEM_GET_RCOV_ENT_STATE(ulPoolId) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulState)

#define TTF_MEM_SET_RCOV_ENT_TIMESTAMP(ulPoolId, ulTs) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulEnterRcovTs = (ulTs))

#define TTF_MEM_GET_RCOV_ENT_TIMESTAMP(ulPoolId) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulEnterRcovTs)

#define TTF_MEM_SET_RCOV_ENT_FAIL_CNT(ulPoolId, ulFailCnt) \
    (g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulAllocFailCnt = (ulFailCnt))

#define TTF_MEM_RCOV_ENTER_WAIT_RCOV_STATE(ulPoolId) \
{ \
    TTF_MEM_SET_RCOV_ENT_TIMESTAMP(ulPoolId, mdrv_timer_get_normal_timestamp()); \
    TTF_MEM_SET_RCOV_ENT_STATE(ulPoolId, TTF_MEM_STATE_WAIT_RCOV); \
}

#define TTF_MEM_RCOV_EXIT_WAIT_RCOV_STATE(ulPoolId) \
{ \
    TTF_MEM_SET_RCOV_ENT_STATE(ulPoolId, TTF_MEM_STATE_NORMAL); \
    TTF_MEM_SET_RCOV_ENT_TIMESTAMP(ulPoolId, 0); \
}


#define TTF_MEM_RCOV_TIMER_EXPIRED(a, b) \
    (((VOS_INT32)a - (VOS_INT32)b) >= 0)


#define TTF_MEM_RCOV_ALLOC_SUCC(ulPoolId) \
{ \
    if (TTF_MEM_STATE_NORMAL != g_stTtfMemRcovEnt.astPoolInfo[ulPoolId].ulState) \
    {\
        TTF_MEM_RCOV_EXIT_WAIT_RCOV_STATE(ulPoolId);\
    }\
}

#define TTF_MEM_RCOV_ALLOC_FAIL(ulPoolId, ulFailCnt, ulPid, usFileId, usLine) \
    TTF_MemRcovAllocFail(ulPoolId, ulFailCnt, ulPid, usFileId, usLine)


enum TTF_MEM_RCOV_STATE_ENUM
{
    TTF_MEM_STATE_NORMAL = 0,
    TTF_MEM_STATE_ALLOC_FAIL,
    TTF_MEM_STATE_WAIT_RCOV,
    TTF_MEM_STATE_BUTT
};

typedef struct
{
    VOS_UINT32  ulState;
    VOS_UINT32  ulRcovThres;
    VOS_UINT32  ulRcovTimerLen;
    VOS_UINT32  ulEnterRcovTs;                  /* ����ȴ��ָ�״̬��ʱ�� */
}TTF_MEM_RCOV_POOL_INFO_STRU;

typedef struct
{
    VOS_UINT8     ucRcovPoolMsk;             /* ��Ҫ�������ڴ������ */
    VOS_UINT8     aucRsv[3];
    TTF_MEM_RCOV_POOL_INFO_STRU astPoolInfo[TTF_MEM_POOL_ID_BUTT];
}TTF_MEM_RCOV_ENTITY_STRU;


/******************************************************************************
  3 ö�ٶ���
******************************************************************************/


/******************************************************************************
  4 ȫ�ֱ�������
******************************************************************************/

/******************************************************************************
  5 ��Ϣͷ����
******************************************************************************/


/******************************************************************************
  6 ��Ϣ����
******************************************************************************/


/******************************************************************************
  7 STRUCT����
******************************************************************************/
#pragma pack(4)


/*====================================*/        /* TTF�ڴ������ */
enum TTF_MEM_TYPE_ENUM
{
    TTF_MEM_TYPE_MIN    = 0,
    TTF_MEM_TYPE_DYN    = 0,                /* ��̬�����ڴ� */
    TTF_MEM_TYPE_BLK,                       /* ר���ڴ�����ݿ� */
    TTF_MEM_TYPE_EXT,                       /* �ⲿ�ڴ�����ݿ� */

    TTF_MEM_TYPE_BUTT
};
typedef VOS_UINT16 TTF_MEM_TYPE_ENUM_UINT16;

#define EVENT_BLK_MEM_USED_INFO_CNT_PER_MSG         (1000)
/*****************************************************************************
 ö����    : TTF_OM_EVENT_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �¼��ϱ�ID
*****************************************************************************/
enum TTF_OM_EVENT_ID_ENUM
{
    TTF_EVENT_BLK_MEM_USED_INFO             = 0X0101,   /* _H2ASN_MsgChoice TTF_OM_EVENT_BLK_MEM_USED_INFO_STRU */
    TTF_EVENT_BUTT
};
typedef VOS_UINT16 TTF_OM_EVENT_ID_ENUM_UINT16;
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /* _H2ASN_Skip */
    VOS_UINT16                              usMsgName;      /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                               aucRsv[2];
} TTF_MEM_LEAK_INFO_IND_MSG;


enum BLK_MEM_USED_INFO_TRIG_TYPE_ENUM
{
    TRIG_TYPE_ALERT                      = 0x0,
    TRIG_TYPE_ALLOC_FAIL,
    TRIG_TYPE_LEAK,
    TRIG_TYPE_NORMAL,
    TRIG_TYPE_BUTT
};
typedef VOS_INT8 BLK_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : TTF_OM_EVENT_USED_BLK_MEM_INFO_STRU
 Э����  :
 ASN.1���� :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulAllocTick;        /* CPU tick when alloc or free */
    VOS_UINT16                                  usAllocFileId;      /* File ID when alloc or free */
    VOS_UINT16                                  usAllocLineNum;     /* File Line when alloc or free */
    VOS_UINT32                                  ulTraceTick;        /* CPU tick when traced */
    VOS_UINT16                                  usTraceFileId;      /* File ID when traced */
    VOS_UINT16                                  usTraceLineNum;     /* File Line when traced */
    VOS_UINT8                                   aucMemData[4];
}BLK_MEM_TRACE_INFO_STRU;

typedef struct
{
    VOS_UINT16                                  usEventId;
    VOS_UINT16                                  usReserved;
    VOS_UINT32                                  ulModuleId;

    VOS_UINT8                                   ucPoolId;
    VOS_UINT8                                   ucRes[3];
    BLK_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8      enTrigType;
    VOS_UINT8                                   ucNo;
    VOS_UINT16                                  usRptCnt;
    VOS_UINT32                                  ulTotalUsedCnt;
    BLK_MEM_TRACE_INFO_STRU                     astBlkMemTraceInfo[1];
}TTF_OM_EVENT_BLK_MEM_USED_INFO_STRU;

typedef struct
{
    VOS_UINT32                                  ulAllocTick;        /* CPU tick when alloc */
    VOS_UINT16                                  usAllocFileId;      /* File ID when alloc */
    VOS_UINT16                                  usAllocLineNum;     /* File Line when alloc */
    VOS_UINT32                                  ulTraceTick;        /* CPU tick when traced */
    VOS_UINT16                                  usTraceFileId;      /* File ID when traced */
    VOS_UINT16                                  usTraceLineNum;     /* File Line when traced */
}TTF_BLK_MEM_DEBUG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TTF_MEM_CLUSTER_STRU
 Э����  :
 ASN.1���� :
*****************************************************************************/
typedef struct
{
    /*��������TTF_MEM_ST�ֽڸ���*/
    VOS_UINT16                          usTotalCnt;
    VOS_UINT16                          usFreeCnt;

    /*�����ڴ�����ݳ���*/
    VOS_UINT16                          usLen;

    VOS_UINT8                           aucRsv[2];

    /*��¼TTF_MEM_ST�����ڴ��������ջ��Ԫ�أ�������ΪTTF_MEM_STָ�� */
    TTF_MEM_ST                        **apstFreeStack;
}TTF_MEM_CLUSTER_STRU;

/*****************************************************************************
 �ṹ��    : TTF_MEM_POOL_STRU
 Э����  :
 ASN.1���� :
*****************************************************************************/
typedef VOS_VOID (*TTF_MEM_EVENT_CALLBACK)(VOS_UINT32 ulMemUsedCnt, VOS_UINT32 ulMemUsedSize);
typedef VOS_VOID (*TTF_MEM_EXT_FREE_CALLBACK)(VOS_VOID *pucAddr);

typedef struct
{
    /* ��ʶ���ڴ���Ƿ�ʹ�� */
    VOS_UINT16                          usUsedFlag;

    /* ���ڴ����ʹ�õ�����û��ֽ� */
    VOS_UINT16                          usMaxByteLen;

    /* ָ�򳤶��������ָ�� */
    VOS_UINT8                           aucLenIndexTable[TTF_MEM_BLK_MAX_BYTE_LEN];

    /* ���ڴ��һ���ж��ټ�*/
    VOS_UINT8                           ucClusterCnt;

    VOS_UINT8                           aucsv2[3];

    /* ָ�����������ָ�� */
    TTF_MEM_CLUSTER_STRU                astClusterTable[TTF_MEM_MAX_CLUSTER_NUM];


    VOS_UINT16                          usTtfMemTotalCnt;       /* ���ڴ��һ���ж���TTF_MEM_ST */
    VOS_UINT16                          usTtfMemUsedCnt;        /* ʹ���˶���TTF_MEM_ST */
    VOS_UINT32                          ulTtfMemTotalByteSize;  /* һ���ж����ֽ� */
    VOS_UINT32                          ulTtfMemUsedByteSize;   /* ��ʹ���ڴ��ܴ�С�����ֽ�Ϊ��λ */

    VOS_UINT16                          usTtfMemExcThresholdCnt;   /* �����ڴ�ʧ�ܳ������޴��� */
    VOS_UINT16                          usTtfMemAllocFailCnt;      /* ���һ�ι����������ڴ�ʧ�ܴ��� */
    VOS_UINT16                          usTtfMemConAllocFailCnt;   /* ���������ڴ�ʧ�ܴ��������ڸ�λ */
    VOS_UINT8                           aucRsv[2];

    TTF_MEM_ST                         *pstTtfMemStStartAddr;   /* ָ��TtfMemST�׵�ַ��ָ�� */

    TTF_MEM_EVENT_CALLBACK              pMemAllocEvent;
    TTF_MEM_EVENT_CALLBACK              pMemFreeEvent;
    TTF_MEM_EXT_FREE_CALLBACK           pMemExtFreeFunc;        /* ָ���ⲿע����ͷź���*/
}TTF_MEM_POOL_STRU;

/* TTF MEMÿ����������Ϣ*/
typedef struct
{
    VOS_UINT16                          usSize;    /* �������Ĵ�С */
    VOS_UINT16                          usCnt;     /* �������� */
}TTF_MEM_CLUSTER_CFG_INFO_STRU;

/* TTF MEMÿ���ڴ�صļ�����Ϣ*/
typedef struct
{
    /* ���� ID */
    VOS_UINT8                           ucPoolID;

    /* ���ڴ���ж��ټ� */
    VOS_UINT8                           ucClusterCnt;

    VOS_UINT8                           aucResv[2];

    /* ÿ���ľ�����Ϣ */
    TTF_MEM_CLUSTER_CFG_INFO_STRU      *pstClusterCfgInfo;
}TTF_MEM_POOL_CFG_INFO_STRU;



/* ����ʹ�ò��� */
typedef struct TTF_MEM_FLOW_CTRL_INFO
{
    VOS_UINT16                          usUsedMemCnt;
    VOS_UINT16                          usRsv;
    VOS_UINT32                          ulTotalUsedByteCnt;
}TTF_MEM_FLOW_CTRL_INFO_STRU;



enum TTF_INVALID_MEM_TYPE_ENUM
{
    TTF_INVALID_MEM_TYPE_BLKTYPE = 1,               /* �ڴ����� */
    TTF_INVALID_MEM_TYPE_POOLID,                    /* �ڴ��ID�Ƿ�  */
    TTF_INVALID_MEM_TYPE_CTRLADDR,                  /* �ڴ��ַ�Ƿ� */
    TTF_INVALID_MEM_TYPE_STUTAS,                    /* �ڴ�״̬���� */

    TTF_INVALID_MEM_TYPE_BUTT
};
typedef unsigned char TTF_INVALID_MEM_TYPE_ENUM_UINT8;

#if(TTF_NODE_MEM_DBG == FEATURE_ON)
enum TTF_NODE_MEM_STATE_ENUM
{
    TTF_NODE_MEM_USED = 0,
    TTF_NODE_MEM_IDLE,
    TTF_NODE_MEM_BUTT
};

typedef VOS_UINT8 TTF_NODE_MEM_STATE_ENUM_UINT8;
#endif

enum TTF_NODE_MEM_POOL_STATE_ENUM
{
    TTF_NODE_MEM_POOL_STATE_IDLE = 0,
    TTF_NODE_MEM_POOL_STATE_ACTIVE,
    TTF_NODE_MEM_POOL_STATE_BUTT
};

typedef VOS_UINT8 TTF_NODE_MEM_POOL_STATE_ENUM_UINT8;

enum TTF_NODE_MEM_TYPE_ENUM
{
    TTF_NODE_MEM_TYPE_NORMAL    = 0,
    TTF_NODE_MEM_TYPE_RRM       = 1,
    TTF_NODE_MEM_TYPE_BUTT
};

typedef VOS_UINT8 TTF_NODE_MEM_TYPE_ENUM_UINT8;


/*****************************************************************************
 �ṹ��    : TTF_MEM_FREE_NULL_PTR_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TTF MEM FREE�յ���ָ����Ϣ
*****************************************************************************/
typedef struct TTF_MEM_FREE_NULL_PTR_INFO
{
    VOS_UINT32          ulTtfMemFreeNullPtrCnt;     /* TtfMemFree �յ���ָ����� */
    VOS_UINT16          usTtfMemFreeFileId;         /* TtfMemFree �յ���ָ������ļ�ID�����������һ���յ���ָ���ļ�ID��Ϣ */
    VOS_UINT16          usTtfMemFreeLineNum;        /* TtfMemFree �յ���ָ������ļ�ID�����������һ���յ���ָ���к���Ϣ */
}TTF_MEM_FREE_NULL_PTR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TTF_MEM_FREE_INVALIED_MEM_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TTF MEM FREE �յ��ķǷ�TTF MEM �ڴ���Ϣ
*****************************************************************************/
typedef struct TTF_MEM_FREE_INVALIED_MEM_INFO
{
    VOS_UINT32                          ulInvalidTtfMemCnt;         /* TTF MEM FREE �յ��ķǷ��ڴ���� */
    VOS_UINT32                          ulInvalidTtfMemAddr;        /* TTF MEM FREE ���һ���յ��ķǷ�TTF MEM �ڴ��ַ */
    VOS_UINT16                          usTtfMemFreeFileId;         /* TTF MEM FREE ���һ���յ��ķǷ�TTF MEM �ڴ��ļ�ID��Ϣ */
    VOS_UINT16                          usTtfMemFreeLineNum;        /* TTF MEM FREE ���һ���յ��ķǷ�TTF MEM �ڴ��к���Ϣ */
    TTF_INVALID_MEM_TYPE_ENUM_UINT8     ucInvalidTtfMemType;        /* TTF MEM FREE ���һ���յ��ķǷ�TTF MEM �ڴ� */
    VOS_UINT8                           aucResve[1];                /* ���ֽڶ��� */
    VOS_UINT16                          usInvalidTtfMemValue;       /* �Ƿ��ڴ�ֵ */
}TTF_MEM_FREE_INVALIED_MEM_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TTF_MEM_FREE_MNTN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����TTF �ڴ��ͷſ�ά�ɲ���Ϣ
*****************************************************************************/
typedef struct TTF_MEM_FREE_MNTN_INFO
{
    TTF_MEM_FREE_INVALIED_MEM_INFO_STRU astTtfMemFreeInvalidMemInfo;    /* TTF MEM FREE �յ��ķǷ�TTF MEM �ڴ���Ϣ */
    TTF_MEM_FREE_NULL_PTR_INFO_STRU     astTtfMemFreeNullPtrInfo;       /* TTF MEM FREE �յ�һ��ָ��Ϊ�յ���Ϣ */
    TTF_MEM_FREE_NULL_PTR_INFO_STRU     astTtfMemFreeNullPPtrInfo;      /* TTF MEM FREE �յ�����ָ��Ϊ�յ���Ϣ */
    VOS_UINT32                          ulTtfMemExtFreeFailCnt;         /* TTF MEM �ͷ��ⲿ�ڴ�ʧ�ܴ��� */
}TTF_MEM_FREE_MNTN_INFO_STRU;

typedef struct
{
#if(TTF_NODE_MEM_DBG == FEATURE_ON)
    VOS_UINT16  usPid;
    VOS_UINT16  usFileId;
    VOS_UINT16  usLineNo;
    VOS_UINT8   ucState;
    VOS_UINT8   ucRsv;
#endif
    VOS_UINT8   aucData[TTF_NODE_MEM_POOL_SIZE];
}TTF_NODE_MEM_NODE_STRU;

typedef struct
{
    VOS_UINT8                               ucState;
    VOS_UINT8                               aucRsv[3];
    volatile VOS_UINT16                     usFreeCnt;
    VOS_UINT16                              usTotalCnt;
    VOS_UINT32                              ulTotalSize;
    VOS_VOID                               *pBaseAddr;
    volatile TTF_NODE_MEM_NODE_STRU       **pFreeNode;
}TTF_NODE_MEM_POOL_STRU;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


/******************************************************************************
  8 UNION����
******************************************************************************/


/******************************************************************************
  9 OTHERS����
******************************************************************************/
extern TTF_MEM_POOL_STRU    g_astTtfMemPool[TTF_MEM_POOL_ID_BUTT];
#define TTF_MEM_BLK_IS_ALERT(ulPoolId)    \
                ((g_astTtfMemPool[ulPoolId].usTtfMemTotalCnt - g_astTtfMemPool[ulPoolId].usTtfMemUsedCnt) < TTF_BLK_MEM_ALERT_THLD)

extern VOS_UINT32  TTF_MemBlkIsAlert(VOS_UINT32 ulPoolId);
extern VOS_UINT32  TTF_MemBlkInit(VOS_UINT32 ulPid);
extern VOS_UINT32  TTF_MemGet(VOS_UINT32 ulPid, TTF_MEM_ST *pMemSrc, VOS_UINT16 usOffset,
           VOS_UINT8 *pDest, VOS_UINT16 usLen);
extern VOS_UINT32  TTF_MemBlkGetHeadData( VOS_UINT32 ulPid, VOS_UINT32 ulPoolId, TTF_MEM_ST *pMemSrc,
           VOS_UINT8 *pDest, VOS_UINT16 usLen);
extern VOS_UINT32  TTF_MemGetHeadData( VOS_UINT32 ulPid, TTF_MEM_ST *pMemSrc,
           VOS_UINT8 *pDest, VOS_UINT16 usLen);
extern VOS_UINT32  TTF_MemGetTailData( VOS_UINT32 ulPid, TTF_MEM_ST *pMemSrc,
           VOS_UINT8 *pDest, VOS_UINT16 usLen);
extern VOS_UINT32  TTF_MemLink(VOS_UINT32 ulPid, TTF_MEM_ST **ppMemHead, TTF_MEM_ST *pMemTail);
extern VOS_UINT32  TTF_MemSet(VOS_UINT32 ulPid, TTF_MEM_ST *pMemDest, VOS_UINT16 usOffset,
           VOS_UINT8 *pSrc, VOS_UINT16 usLen);
extern VOS_UINT32  TTF_MemStick(VOS_UINT32 ulPid, TTF_MEM_ST *pMemHead, TTF_MEM_ST *pMemTail);
extern VOS_UINT32  TTF_MemIsCritical(VOS_VOID);
extern VOS_UINT32 TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_ENUM_UINT32 enPoolId,
            TTF_MEM_EVENT_CALLBACK pMemAllocEvent, TTF_MEM_EVENT_CALLBACK  pMemFreeEvent);
extern TTF_MEM_ST *TTF_MemSingleFree_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum, VOS_UINT32 ulPid, TTF_MEM_ST *pMem);
extern TTF_MEM_ST *TTF_MemBlkCopyAllocFromMem_Debug
(
    VOS_UINT16      usFileID,
    VOS_UINT16      usLineNum,
    VOS_UINT32      ulPid,
    VOS_UINT32      ulPoolId,
    TTF_MEM_ST     *pMemSrc,
    VOS_UINT16      usOffset,
    VOS_UINT16      usLen
);

extern VOS_UINT32 TTF_MemBlkCutHeadData_Debug(VOS_UINT16 usFileID,
    VOS_UINT16 usLineNum, VOS_UINT32 ulPid, TTF_MEM_ST **ppMemSrc,
    VOS_UINT8 *pDest, VOS_UINT16 usLen);
extern VOS_UINT16 TTF_MemBlkCutTailData_Debug(VOS_UINT16 usFileID,
    VOS_UINT16 usLineNum, VOS_UINT32 ulPid, TTF_MEM_ST **ppMemSrc,
    VOS_UINT8 *pDest, VOS_UINT16 usLen);
extern VOS_UINT32 TTF_MemBlkAddHeadData_Debug(VOS_UINT16 usFileID,
    VOS_UINT16 usLineNum, VOS_UINT32 ulPid, VOS_UINT32 ulPoolId,
    TTF_MEM_ST * * ppMemDest, VOS_UINT8 * pSrcData, VOS_UINT16 usAddLen);
extern VOS_UINT32 TTF_MemBlkAddTailData_Debug(VOS_UINT16 usFileID,
    VOS_UINT16 usLineNum, VOS_UINT32 ulPid, VOS_UINT32 ulPoolId,
    TTF_MEM_ST * * ppMemDest, VOS_UINT8 * pSrcData, VOS_UINT16 usAddLen);
extern TTF_MEM_ST *TTF_MemBlkRef_Debug(VOS_UINT16 usFileID,
    VOS_UINT16 usLineNum, VOS_UINT32 ulPid, VOS_UINT32 ulPoolID,
    TTF_MEM_ST *pMemRef, VOS_UINT16  usOffset, VOS_UINT16  usLen);
extern TTF_MEM_ST *TTF_MemBlkAllocWithUsed_Debug(VOS_UINT16 usFileID,
    VOS_UINT16 usLineNum, VOS_UINT32 ulPid, VOS_UINT32 ulPoolId, VOS_UINT16 usLen);
extern VOS_UINT16 TTF_MemBlkCutTailDataWithLastMem_Debug
(
    VOS_UINT16 usFileID,VOS_UINT16 usLineNum, VOS_UINT32 ulPid,
    TTF_MEM_ST **ppMemSrc, TTF_MEM_ST **ppLastMem, VOS_UINT8 *pDest,
    VOS_UINT16 usLen
);
extern VOS_UINT32 TTF_MemBlkAddTailDataWithLastMem_Debug
(
    VOS_UINT16 usFileID,VOS_UINT16 usLineNum, VOS_UINT32 ulPid,
    VOS_UINT32 ulPoodId,TTF_MEM_ST **ppMemDest, TTF_MEM_ST *pLastMem,
    VOS_UINT8  *pSrcData, VOS_UINT16  usAddLen
);

extern TTF_MEM_ST *TTF_MemBlkAllocPlus_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum,
    VOS_UINT32 ulPid, VOS_UINT32 ulPoolId, VOS_UINT16 usLen);

extern TTF_MEM_ST *TTF_MemBlkCopyAlloc_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum,
    VOS_UINT32 ulPid, VOS_UINT32 ulPoolId, VOS_UINT8 *pData, VOS_UINT16 usLen);

extern TTF_MEM_ST *TTF_MemBlkCopyAllocPacket_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum,
    VOS_UINT32 ulPid, VOS_UINT32 ulPoolId, VOS_UINT8 *pData, VOS_UINT16 usLen);

extern TTF_MEM_ST *TTF_MemBlkSingleFree_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNum, TTF_MEM_ST *pstTtfMem);

extern VOS_VOID TTF_MemFreeData(VOS_UINT32 ulPid, TTF_MEM_ST *pItem);

extern VOS_UINT16 TTF_MemGetLen(VOS_UINT32 ulPid, TTF_MEM_ST *pMem);

extern VOS_UINT32 TTF_MemRegExtFreeCallBack
                    (
                        TTF_MEM_EXT_FREE_CALLBACK           pMemExtFreeFunc
                    );

extern VOS_VOID TTF_MemFreeShowMntnInfo( VOS_VOID );

extern VOS_UINT_PTR TTF_GetHdlcMemSection(VOS_VOID);

extern VOS_UINT_PTR TTF_GetCipherMemSection(VOS_VOID);

extern VOS_VOID TTF_NodeMemPoolInit(VOS_VOID);
extern VOS_UINT8 *TTF_NodeMemAlloc_Debug(TTF_NODE_MEM_TYPE_ENUM_UINT8 enTtfNodeMemType,VOS_UINT32  ulPid, VOS_UINT16  usLen, VOS_UINT16  usFileId, VOS_UINT16  usLineNo);
extern VOS_VOID   TTF_NodeMemFree_Debug(TTF_NODE_MEM_TYPE_ENUM_UINT8 enTtfNodeMemType, VOS_UINT32 ulPid, VOS_UINT8 * pMem, VOS_UINT16 usFileId, VOS_UINT16 usLineNo);
extern VOS_UINT32 TTF_NodeMemLeakCheck(VOS_VOID);

extern VOS_UINT32 TTF_MemInsertNext(VOS_UINT32 ulPid, TTF_MEM_ST *pMemCurr, TTF_MEM_ST *pMemNext);

extern TTF_MEM_FREE_MNTN_INFO_STRU             g_stTtfMemFreeMntnEntity;

#define TTF_MemBlkAllocPlus(ulPid, ulPoolId, usLen) \
    TTF_MemBlkAllocPlus_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, usLen)


#define TTF_MemSingleFree(ulPid, pMem) \
    TTF_MemSingleFree_Debug(THIS_FILE_ID, __LINE__, ulPid, pMem)

#define TTF_MemBlkCopyAlloc(ulPid, ulPoolId, pData,usLen) \
    TTF_MemBlkCopyAlloc_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, pData, usLen)

#define TTF_MemBlkCopyAllocPacket(ulPid, ulPoolId, pData,usLen) \
    TTF_MemBlkCopyAllocPacket_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, pData, usLen)

#define TTF_MemBlkCopyAllocFromMem(ulPid, ulPoolId, pMemSrc, usOffset, usLen) \
    TTF_MemBlkCopyAllocFromMem_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, pMemSrc, usOffset, usLen)

#define TTF_MemBlkCutHeadData(ulPid, ppMemSrc, pDest, usLen) \
    TTF_MemBlkCutHeadData_Debug(THIS_FILE_ID, __LINE__, ulPid, ppMemSrc, pDest, usLen)

#define TTF_MemBlkCutTailData(ulPid, ppMemSrc, pDest, usLen) \
    TTF_MemBlkCutTailData_Debug(THIS_FILE_ID, __LINE__, ulPid, ppMemSrc, pDest, usLen)

#define TTF_MemBlkCutTailDataWithLastMem(ulPid, ppMemSrc, ppLastMem, pDest, usLen) \
    TTF_MemBlkCutTailDataWithLastMem_Debug(THIS_FILE_ID, __LINE__, ulPid, ppMemSrc, ppLastMem, pDest, usLen)

#define TTF_MemBlkAddHeadData(ulPid, ulPoolId, ppMemDest, pSrcData, usAddLen) \
    TTF_MemBlkAddHeadData_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, ppMemDest, pSrcData, usAddLen)

#define TTF_MemBlkAddTailData(ulPid, ulPoolId, ppMemDest, pSrcData, usAddLen) \
    TTF_MemBlkAddTailData_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, ppMemDest, pSrcData, usAddLen)

#define TTF_MemBLkAddTailDataWithLastMem(ulPid, ulPoolId, ppMemDest, pLastMem, pSrcData, usAddLen)\
    TTF_MemBlkAddTailDataWithLastMem_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, ppMemDest, pLastMem, pSrcData, usAddLen)

#define TTF_MemBlkRef(ulPid, ulPoolId, pMemRef, usOffset, usLen) \
    TTF_MemBlkRef_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, pMemRef, usOffset, usLen)

#define TTF_MemBlkAllocWithUsed(ulPid, ulPoolId, usLen) \
    TTF_MemBlkAllocWithUsed_Debug(THIS_FILE_ID, __LINE__, ulPid, ulPoolId, usLen)


#define TTF_NODE_MEM_ALLOC(ulPid, size)     \
    TTF_NodeMemAlloc_Debug(TTF_NODE_MEM_TYPE_NORMAL, ulPid, size, THIS_FILE_ID, __LINE__)

#define TTF_NODE_MEM_FREE(ulPid, pMem)     \
    TTF_NodeMemFree_Debug(TTF_NODE_MEM_TYPE_NORMAL, ulPid, (VOS_UINT8 *)pMem, THIS_FILE_ID, __LINE__)

#define TTF_NODE_MEM_ALLOC_WITH_FILE_LINE(ulPid, size, ulFileID, ulLine)\
    TTF_NodeMemAlloc_Debug(TTF_NODE_MEM_TYPE_NORMAL, ulPid, size, ulFileID, ulLine)

/* RRMģ��NODE�ڴ����� */
#define RRM_NODE_MEM_ALLOC(ulPid, size)     \
    TTF_NodeMemAlloc_Debug(TTF_NODE_MEM_TYPE_RRM, ulPid, size, THIS_FILE_ID, __LINE__)

/* RRMģ��NODE�ڴ��ͷ� */
#define RRM_NODE_MEM_FREE(ulPid, pMem)     \
    TTF_NodeMemFree_Debug(TTF_NODE_MEM_TYPE_RRM, ulPid, (VOS_UINT8 *)pMem, THIS_FILE_ID, __LINE__)

/* RRMģ��NODE�ڴ����� */
#define RRM_NODE_MEM_ALLOC_WITH_FILE_LINE(ulPid, size, ulFileID, ulLine)\
    TTF_NodeMemAlloc_Debug(TTF_NODE_MEM_TYPE_RRM, ulPid, size, ulFileID, ulLine)

#if (FEATURE_ON == FEATURE_TTF_MEM_DEBUG)
#define TTF_MEM_DBG(pMem, usFileID, usLineNum) \
{ \
    if (TTF_BLK_MEM_DEBUG_SWITCH_ON) \
    { \
        if (VOS_NULL_PTR != pMem->pstDbgInfo) \
        { \
            pMem->pstDbgInfo->enMemStateFlag    = TTF_BLK_MEM_STATE_ALLOC; \
            pMem->pstDbgInfo->usAllocFileId     = usFileID; \
            pMem->pstDbgInfo->usAllocLineNum    = usLineNum; \
            pMem->pstDbgInfo->ulAllocTick       = mdrv_timer_get_normal_timestamp(); \
            pMem->pstDbgInfo->usTraceFileId     = usFileID; \
            pMem->pstDbgInfo->usTraceLineNum    = usLineNum; \
        } \
        else \
        { \
            TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_ERROR, "Blk Mem debug info is null! \n"); \
        } \
    }\
}

#define TTF_BLK_MEM_DEBUG_SWITCH_ON \
    (1 == g_ulTtfBlkMemCheck)

#define TTF_MEM_TRACE(pMem) \
    TTF_MemSetBlkFlag(pMem, THIS_FILE_ID, __LINE__)

#define TTF_MEM_RCOV_MEM(ulPoolId, ulPid, usFileId, usLine) \
    TTF_MemRcovMem(ulPoolId, ulPid, usFileId, usLine)

extern VOS_UINT32   g_ulTtfBlkMemCheck;
extern VOS_VOID     TTF_ShowUsedBlkMemInfo(VOS_VOID);
extern VOS_VOID     TTF_MemSetBlkFlag(TTF_MEM_ST *pstMem, VOS_UINT16 usFileID, VOS_UINT16 usLineNum);

#else

#define TTF_MEM_TRACE(pMem)
#define TTF_MEM_DBG(pMem, usFileID, usLineNum)
#define TTF_MEM_RCOV_MEM(ulPoolId, ulPid, usFileId, usLine) \
     mdrv_om_system_error(TTF_MEM_ALLOC_FAIL_SYSTEM_ERROR, usFileId, usLine, VOS_NULL_PTR, 0)

#endif


#if (FEATURE_PTM == FEATURE_ON)

#if (FEATURE_ON == FEATURE_TTF_MEM_DEBUG)
#define TTF_ERR_LOG_RCD_DBG(pstMemAllocInfo, pstMem, usMemRptCnt) \
{ \
    if ((VOS_NULL_PTR != pstMem->pstDbgInfo) && (TTF_BLK_MEM_STATE_FREE != pstMem->pstDbgInfo->enMemStateFlag)) \
    { \
        pstMemAllocInfo->usAllocFileId  = pstMem->pstDbgInfo->usAllocFileId; \
        pstMemAllocInfo->usAllocLine    = pstMem->pstDbgInfo->usAllocLineNum; \
        pstMemAllocInfo->usTraceFileId  = pstMem->pstDbgInfo->usTraceFileId; \
        pstMemAllocInfo->usTraceLine    = pstMem->pstDbgInfo->usTraceLineNum; \
        usMemRptCnt++;\
    } \
}
#else
#define TTF_ERR_LOG_RCD_DBG(pstMemAllocInfo, pstMem, usMemRptCnt) \
{ \
    PS_MEM_SET(pstMemAllocInfo, 0, sizeof(TTF_MNTN_ERR_LOG_MEM_ALLOC_INFO_STRU));\
    usMemRptCnt++; \
}
#endif
extern VOS_VOID TTF_MNTN_ErrlogTtfMemAllocFail(VOS_UINT32 ulPid, VOS_UINT8 ucPoolId, VOS_UINT16 usFileId, VOS_UINT16 usLine, VOS_UINT32 ulAllocFailCnt);

#endif


#if((FEATURE_LTE == FEATURE_OFF) && (FEATURE_WIFI == FEATURE_ON))
#define TTF_MEM_RSV_PAD_LEN(usDataLen, usLen) \
{\
    usDataLen   = DRV_WifiCalDataLen(usLen + TTF_MEM_MAC_HEADER_RSV_LEN); \
    usLen       = ( TTF_MEM_SKB_HEAD_PAD_LEN + usDataLen+ TTF_MEM_SKB_TAIL_PAD_LEN); \
}
#else
#define TTF_MEM_RSV_PAD_LEN(usDataLen, usLen) \
{ \
    usLen      += TTF_MEM_MAC_HEADER_RSV_LEN; \
    usDataLen   = (VOS_UINT16)TTF_GET_32BYTE_ALIGN_VALUE(usLen); \
    usLen       = ( TTF_MEM_SKB_HEAD_PAD_LEN + usDataLen+ TTF_MEM_SKB_TAIL_PAD_LEN); \
}
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* TTFMem.h */

