/******************************************************************************
  �� �� ��   : PsQnode.h
  �� �� ��   : ����
  ��    ��   : liukai
  ��������   : 2013��9��16��
  ����޸�   :
  ��������   : PsQnode���ܵ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��9��16��
    ��    ��   : liukai
    �޸�����   : �����ļ�
******************************************************************************/

#ifndef __PS_QNODE_H__
#define __PS_QNODE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 ����ͷ�ļ�����
******************************************************************************/
#include "PsCommonDef.h"
#include "TTFLink.h"
#include "TTFMem.h"


/******************************************************************************
  2 �궨��
******************************************************************************/
/* ʹ�����Զ�������δ�С, ��λ: B */
#define  MAX_PARA_OCTET_NUM     (32)

/*
��ǰ����1xÿ20ms���8�����ݣ�RLP���͵صȴ�ʱ����560ms�����Գ�������Ϊ8*560ms/20ms=224�顣
����1500B��IP��������256B��Ϊ8�Σ���ô����һ��IP�����㣬��Ҫ224*8=1792�顣
����������԰�ehs�Ľ��Ҳ���ϵ�����ṹ�У���ô�Ϳ��Ը���ehs���ĸ������ڴ档
*/
#define  MAX_PS_QNODE_NUM      (1792)

/* ����PSQnode����(MAX_PS_QNODE_NUM)��bit, ռ�ö��ٸ�4byte */
#define  MAX_PS_QNODE_4BYTE_ALIGN_NUM   ((((MAX_PS_QNODE_NUM) + 0x1f) & (~0x1f)) / 32)

/* �������Խ���ħ���� */
#define  PS_QNODE_MAGICNUM     (0x1D2D)


/******************************************************************************
  3 ö�ٶ���
******************************************************************************/
/* PsQnode���Կ��� */
enum PS_QNODE_TRACE_PRINT_SWITCH_ENUM
{
    PS_QNODE_TRACE_PRINT_OFF     = 0,
    PS_QNODE_TRACE_PRINT_ON      = 1,
    PS_QNODE_TRACE_PRINT_BUTT
};

typedef VOS_UINT8 PS_QNODE_TRACE_PRINT_SWITCH_ENUM_UINT8;

/* PsQnode����״̬ */
enum PS_QNODE_STATE_ENUM
{
    PS_QNODE_FREE_STATE     = 0,
    PS_QNODE_USED_STATE     = 1,
    PS_QNODE_STATE_BUTT
};

typedef VOS_UINT8 PS_QNODE_STATE_ENUM_UINT8;

/* TtfNode��Դ�ڴ����� */
enum PS_QNODE_MEM_SOURCE_TYPE_ENUM
{
    PS_QNODE_MEM_SOURCE_CONSECMEM_TYPE     = 0,
    PS_QNODE_MEM_SOURCE_TTFMEM_TYPE        = 1,
    PS_QNODE_MEM_SOURCE_TYPE_BUTT
};

typedef VOS_UINT8 PS_QNODE_MEM_SOURCE_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : PS_QNODE_EVENT_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : PsQnode�¼��ϱ�ID
*****************************************************************************/
enum PS_QNODE_EVENT_ID_ENUM
{
    ID_PS_QNODE_FOUND_TAMPERED             = 0x0316,   /* _H2ASN_MsgChoice PS_QNODE_TAMPERED_EVENT_STRU */
    ID_PS_QNODE_TYPE_BUTT
};
typedef VOS_UINT16 PS_QNODE_EVENT_ID_ENUM_UINT16;




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

/*****************************************************************************
 �ṹ��    : PS_QNODE_STATISTICS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Qnodeͳ�ƽṹ
*****************************************************************************/
typedef struct
{
    volatile VOS_UINT32                      ulAllocTotalCnt;
    volatile VOS_UINT32                      ulAllocFailCnt;         /* ����Qnodeʧ�ܴ��� */
    volatile VOS_UINT32                      ulFreeTotalCnt;
    volatile VOS_UINT32                      ulFreeNullPtrCnt;       /* �ͷſ�ָ����� */
    volatile VOS_UINT32                      ulFreePtrBeforeCnt;     /* �ظ��ͷŴ��� */
    volatile VOS_UINT32                      ulMagicTamperedCnt;     /* ħ���ֱ��۸Ĵ��� */
    volatile VOS_UINT32                      ulFreeInvalidPrtCnt;    /* �ͷ�Ұָ�� */
}PS_QNODE_STATISTICS_STRU;

/*****************************************************************************
 �ṹ��    : PS_QNODE_MGMT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PsQnode����ṹ
*****************************************************************************/
typedef struct
{
    volatile VOS_UINT16                     usNodeIdx;     /* ���ʹ��ָʾ */
    PS_QNODE_TRACE_PRINT_SWITCH_ENUM_UINT8  enIsTracePrintOn;
    VOS_UINT8                               aucReserve[1];
    PS_QNODE_STATISTICS_STRU                stStat;
    volatile VOS_UINT32                     aulQuickMap[MAX_PS_QNODE_4BYTE_ALIGN_NUM];
}PS_QNODE_MGMT_STRU;

/*****************************************************************************
 �ṹ��    : PS_QNODE_DEBUG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PsQnode���Լ�¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulAllocTick;        /* CPU tick when alloc or free */
    VOS_UINT16                      usAllocFileId;      /* File ID when alloc or free */
    VOS_UINT16                      usAllocLineNum;     /* File Line when alloc or free */
    VOS_UINT16                      usTraceFileId;      /* File ID when traced */
    VOS_UINT16                      usTraceLineNum;     /* File Line when traced */
    VOS_UINT32                      ulTraceTick;        /* CPU tick when traced */
}PS_QNODE_DEBUG_STRU;

/*****************************************************************************
 �ṹ��    : PS_QNODE_CONSECUTIVE_MEM_DSCP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ⲿ�����ڴ����ݴ�ŵĽṹ
*****************************************************************************/
typedef struct _CONSECUTIVE_MEM_STRU
{
    VOS_UINT8                      *pucStartMem;    /* �����ڴ���ʼ��ַ */
    /*
    MSB           LSB
     7 6 5 4 3 2 1 0
    +-+-+-+-+-+-+-+-
    |              |
    +-+-+-+-+-+-+-+-
    e.g, ucOffset = 2, ��ʾ��MSB��ʼƫ��2bit, ��bit 5��ʼ
    */
    VOS_UINT8                        ucOffset;       /* ����ʼ�ֽ��д�MSB��ƫ��offset bit */
    VOS_UINT8                        aucReserve[1];
    VOS_UINT16                       usBitLen;       /* ���ݳ��� */
    struct _CONSECUTIVE_MEM_STRU    *pstNext;
}PS_QNODE_CONSECUTIVE_MEM_DSCP_STRU;

/*****************************************************************************
 �ṹ��    : PS_QNODE_TTF_MEM_DSCP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ⲿTTF_MEM�ڴ����ݴ�ŵĽṹ
*****************************************************************************/
typedef struct _TTF_MEM_DSCP_STRU
{
    TTF_MEM_ST                     *pstMem;       /* TTF_MEM��ʽ���ڴ� */
    /*
    MSB           LSB
     7 6 5 4 3 2 1 0
    +-+-+-+-+-+-+-+-
    |              |
    +-+-+-+-+-+-+-+-
    e.g, ucOffset = 2, ��ʾ��MSB��ʼƫ��2bit, ��bit 5��ʼ
    */
    VOS_UINT8                       ucOffset;       /* ����ʼ�ֽ��д�MSB��ƫ��offset bit */
    VOS_UINT8                       aucReserve[1];
    VOS_UINT16                      usBitLen;       /* ���ݳ��� */
    struct _TTF_MEM_DSCP_STRU      *pstNext;
}PS_QNODE_TTF_MEM_DSCP_STRU;

/*****************************************************************************
 �ṹ��    : PS_QNODE_MEM_SOURCE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ڴ��йҽӵ�����Դ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulChoice;   /* choice�������Լ�����չ */

    #define      PS_QNODE_MEM_SOURCE_CONSECMEM_CHOSEN       0    /* ���������ڴ��ṩ���� */
    #define      PS_QNODE_MEM_SOURCE_TTFMEM_CHOSEN          1    /* ����TTF_MEM�ṩ���� */

    union
    {
        PS_QNODE_CONSECUTIVE_MEM_DSCP_STRU      stSrcConsecMem;
        PS_QNODE_TTF_MEM_DSCP_STRU              stSrcTtfMem;
    }u;
}PS_QNODE_MEM_SOURCE_STRU;

/*****************************************************************************
 �ṹ��    : PS_QNODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PsQnode�ṹ
*****************************************************************************/
typedef  struct
{
    TTF_NODE_ST                         stNode;                         /* ���ڶ��йҽ� */
    PS_QNODE_MEM_SOURCE_STRU            stMemSrc;
    volatile VOS_UINT16                 usMagic;                        /* ����MemSrc, ���ڼ���Ƿ��������Խ�� */
    volatile VOS_UINT16                 usIndex;                        /* ���������, Ψһ */
    volatile PS_QNODE_STATE_ENUM_UINT8  enState;
    VOS_UINT8                           aucReserve1[3];
    PS_QNODE_DEBUG_STRU                 stDbg;
    VOS_UINT8                           aucPara[MAX_PARA_OCTET_NUM];    /* �ⲿʹ���ߴ���Զ������������ */
}PS_QNODE_STRU;

/*****************************************************************************
 �ṹ��    : PS_QNODE_TAMPERED_EVENT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ϱ�Qnode���۸��¼�
*****************************************************************************/
typedef struct
{
    VOS_UINT16      usEventId;
    VOS_UINT16      usReserved;
    VOS_UINT32      ulModuleId;

    VOS_UINT16      usFileId;
    VOS_UINT16      usLineId;
    VOS_UINT32      ulPid;
    VOS_UINT32      ulTick;
    PS_QNODE_STRU   stQnode;    /* ���۸ĵ�Qnode */
}PS_QNODE_TAMPERED_EVENT_STRU;



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


/******************************************************************************
  8 UNION����
******************************************************************************/


/******************************************************************************
  4 ȫ�ֱ�������
******************************************************************************/
extern PS_QNODE_STRU    g_astQnode[MAX_PS_QNODE_NUM];


/******************************************************************************
  9 OTHERS����
******************************************************************************/
PS_QNODE_STRU* PS_Qnode_GetNode
                            (VOS_UINT16 usFileId,
                            VOS_UINT16 usLineId,
                            VOS_UINT32 ulPid);

PS_RSLT_CODE_ENUM_UINT32 PS_Qnode_FreeNode
                              (VOS_UINT16       usFileId,
                               VOS_UINT16      usLineId,
                               VOS_UINT32      ulOpPid,
                               PS_QNODE_STRU  *pstQnode);

PS_RSLT_CODE_ENUM_UINT32 PS_Qnode_FillMemInfo
                    (VOS_UINT16   usFileId,
                    VOS_UINT16                     usLineId,
                    VOS_UINT32                     ulPid,
                    PS_QNODE_STRU                 *pstQnode,
                    PS_QNODE_MEM_SOURCE_STRU      *pstMemSrc,
                    VOS_UINT8                      ucParaOctetCnt,
                    VOS_UINT8                      aucPara[]);

#define PS_GET_QNODE(ulPid) \
    PS_Qnode_GetNode(THIS_FILE_ID, __LINE__, (ulPid))

#define PS_FREE_QNODE(ulPid, pstQnode) \
    PS_Qnode_FreeNode(THIS_FILE_ID, __LINE__, (ulPid), (pstQnode))

#define PS_FILL_QNODE(ulPid, pstQnode, pstMemSrc, ucParaOctetCnt, aucPara) \
    PS_Qnode_FillMemInfo(THIS_FILE_ID, __LINE__, (ulPid), (pstQnode), \
        (pstMemSrc), (ucParaOctetCnt), (aucPara))

extern VOS_VOID PS_Qnode_Init(VOS_VOID);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* PsQnode.h */


