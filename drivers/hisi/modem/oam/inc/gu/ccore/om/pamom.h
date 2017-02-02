/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��      : pamom.h
  �� �� ��      : ����
  ��    ��      : H00300778
  ��������      : 2015��6��24��
  ����޸�      :
  ��������      : ��h�ļ�������pamom.c��ͷ�ļ�
  �����б�      :
  �޸���ʷ      :
  1.��    ��    : 2015��6��24��
    ��    ��    : H00300778
    �޸�����    : �����ļ�

******************************************************************************/


#ifndef __PAMOM_H__
#define __PAMOM_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "mdrv.h"

/*****************************************************************************
  2 �궨��
******************************************************************************/
/* DSP CS-ERRLOG PrimId */
#define OM_RECORD_DSP_ERRORLOG         0x5100

#define OM_DSP_DCXO_UPDATE_NV_DATA     0x5101

/* DSP CS-ERRLOG MAX LENGTH */
#define OM_ERRORLOG_DSP_LEN_MAX        (1024)

#define OM_ICC_CHANNEL_PRIORITY        (0)

#define OM_ICC_HANDSHAKE_TIME_MAX      (200000)

#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
#define OSA_ICC_BUFFER_SIZE                                     (128*1024)
#else
#define OSA_ICC_BUFFER_SIZE                                     (64*1024)
#endif  /* ( FEATURE_MULTI_MODEM == FEATURE_ON ) */

/*******************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum OM_ICC_CHANNEL_ENUM
{
    OM_OM_ICC_CHANNEL           = 0,    /*��ǰͨ�����ڴ���OM����*/
    OM_OSA_MSG_ICC_CHANNEL,             /*��ǰͨ�����ڴ���OSA����Ϣ����*/
    OM_ICC_CHANNEL_BUTT
};
typedef VOS_UINT32 OM_ICC_CHANNEL_ENUM_UINT32;

/*****************************************************************************
  4 STRUCT����
*****************************************************************************/
typedef struct
{
   VOS_UINT8                       *pucBuf;
   VOS_UINT32                       ulLen;
   VOS_UINT8                        aucRsv[4];
}OM_RECORD_BUF_STRU;

typedef struct
{
   VOS_UINT16                       usSendPid;
   VOS_UINT16                       usRcvPid;
   VOS_UINT32                       ulMsgName;
   VOS_UINT32                       ulSliceStart;
   VOS_UINT32                       ulSliceEnd;
}OM_RECORD_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16 usPrimId;
    VOS_UINT16 usResv;
    VOS_UINT32 ulTotalLength;
    VOS_UINT32 ulErrNo;
    VOS_UINT8  aucData[4];
}DSP_ERROR_LOG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16 usPrimId;
    VOS_UINT16 usCount;
    VOS_UINT8  aucNVData[4];
}DSP_WRITE_NV_STRU;

typedef struct
{
    VOS_UINT16 usNvId;
    VOS_UINT16 usNvLen;
    VOS_UINT8  aucNVData[4];
}DSP_WRITE_NV_CONTEXT_STRU;

/*����ICCͨ��UDI��������Ƭ�ṹ*/
typedef struct
{
    VOS_UINT32                      enICCId;        /*������ĵ�ǰͨ����*/
    ICC_CHAN_ATTR_S                *pstICCAttr;     /*��ǰͨ������*/
}OM_ICC_UDI_CTRL_STRU;


typedef struct
{
    VOS_MSG_HEADER
}OM_FILTER_MSG_HEAD_STRU;

/*****************************************************************************
  5 �ӿڶ���
*****************************************************************************/

extern VOS_UINT32 Om_BbpDumpEdmaInit(VOS_VOID);

extern VOS_VOID Om_BbpDbgSelfTask(unsigned long ulPara1, unsigned long ulPara2,
                  unsigned long ulPara3, unsigned long ulPara4);

extern VOS_VOID PsRegTransferTaskEntry(VOS_VOID);

extern VOS_UINT32 OM_BbpMasterInit(VOS_VOID);

extern VOS_UINT V_ICC_OSAMsg_CB(VOS_UINT ulChannelID,VOS_INT lLen);

extern VOS_VOID Om_QueryDumpMsgProc(MsgBlock* pMsg);

extern VOS_VOID OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber);

extern VOS_VOID OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber, VOS_UINT32 ulSendPid, VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgName);

extern VOS_VOID OM_RecordMemInit(VOS_VOID);

extern VOS_UINT32 OM_GetLogPath(VOS_CHAR *pucBuf, VOS_CHAR *pucOldPath, VOS_CHAR *pucUnitaryPath);

extern VOS_UINT V_ICC_OSAHifiMsg_CB(VOS_UINT ulChannelID,VOS_INT lLen);

#if ((OSA_CPU_ACPU == VOS_OSA_CPU)||(VOS_WIN32 == VOS_OS_VER))
extern VOS_UINT32 OM_GetSlice(VOS_VOID);
#else
static inline __attribute__((always_inline)) VOS_UINT32 OM_GetSlice(VOS_VOID)
{
    /* Add for L Only version */
    if (PROTOCOL_TYPE_LTE_ONLY == VOS_GetProtocolType())
    {
        return VOS_GetTick();
    }

    return mdrv_timer_get_normal_timestamp();
}
#endif

#if (VOS_WIN32 == VOS_OS_VER)
#define PS_LOG(ModulePID, SubMod, Level, String)\
        vos_printf("\r\n%s",   String)

#define PS_LOG1(ModulePID, SubMod, Level, String, Para1)\
        vos_printf("\r\n%s,para1=%d", String, Para1)

#define PS_LOG2(ModulePID, SubMod, Level, String, Para1, Para2)\
        vos_printf("\r\n%s,para1=%d,para2=%d", String, Para1, Para2)

#define PS_LOG3(ModulePID, SubMod, Level, String, Para1, Para2, Para3)\
        vos_printf("\r\n%s,para1=%d,para2=%d,para3=%d", String, Para1, Para3)

#define PS_LOG4(ModulePID, SubMod, Level, String, Para1, Para2, Para3, Para4)\
        vos_printf("\r\n%s,para1=%d,para2=%d,para3=%d,para4=%d", String, Para1, Para3, Para4)

#else
#define PS_LOG(ModulePID, SubMod, Level, String)

#define PS_LOG1(ModulePID, SubMod, Level, String, Para1)

#define PS_LOG2(ModulePID, SubMod, Level, String, Para1, Para2)

#define PS_LOG3(ModulePID, SubMod, Level, String, Para1, Para2, Para3)

#define PS_LOG4(ModulePID, SubMod, Level, String, Para1, Para2, Para3, Para4)

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __PAMOM_H__ */
