

#ifndef __TAFMTACOMM_H__
#define __TAFMTACOMM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

/* Added by wx270776 for OM�ں�, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (VOS_WIN32 == VOS_OS_VER)
#define   MTA_WARNING_LOG(string)                vos_printf("%s \r\n", string)
#define   MTA_WARNING1_LOG(string, para1)        vos_printf("%s %d.\r\n", string, para1)
#define   MTA_WARNING2_LOG(string, para1, para2) vos_printf("%s %d, %d.\r\n", string, para1, para2)

#define   MTA_ERROR_LOG(string)                  vos_printf("%s \r\n", string)
#define   MTA_ERROR1_LOG(string, para1)          vos_printf("%s %d.\r\n", string, para1)
#define   MTA_ERROR2_LOG(string, para1, para2)   vos_printf("%s %d, %d.\r\n", string, para1, para2)
#else
#define   MTA_WARNING_LOG(string)                TAF_LOG(UEPS_PID_MTA, 0, PS_LOG_LEVEL_WARNING,  string)
#define   MTA_WARNING1_LOG(string, para1)        TAF_LOG1(UEPS_PID_MTA, 0, PS_LOG_LEVEL_WARNING,  string, (VOS_INT32)para1)
#define   MTA_WARNING2_LOG(string, para1, para2) TAF_LOG2(UEPS_PID_MTA, 0, PS_LOG_LEVEL_WARNING,  string, (VOS_INT32)para1, (VOS_INT32)para2)

#define   MTA_ERROR_LOG(string)                  TAF_LOG(UEPS_PID_MTA, 0, PS_LOG_LEVEL_ERROR,  string)
#define   MTA_ERROR1_LOG(string, para1)          TAF_LOG1(UEPS_PID_MTA, 0, PS_LOG_LEVEL_ERROR,  string, (VOS_INT32)para1)
#define   MTA_ERROR2_LOG(string, para1, para2)   TAF_LOG2(UEPS_PID_MTA, 0, PS_LOG_LEVEL_ERROR,  string, (VOS_INT32)para1, (VOS_INT32)para2)
#endif

/* Added by w00316404 for eMBMS project, 2015-5-22, begin */
/*�����Ϣͷ*/
#define   MTA_FILL_MSG_HEADER(pSendMsg, RecvPid)    \
        (pSendMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID; \
        (pSendMsg)->ulSenderPid     = UEPS_PID_MTA; \
        (pSendMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID; \
        (pSendMsg)->ulReceiverPid   = RecvPid;
/* Added by w00316404 for eMBMS project, 2015-5-22, end */

/* ��װOSA������Ϣ�ӿ� */
#define TAF_MTA_ALLOC_MSG_WITH_HDR(ulMsgLen)\
            PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MTA, (ulMsgLen))

/* ��װOSA��Ϣͷ */
#define TAF_MTA_CFG_MSG_HDR(pstMsg, ulRecvPid, ulMsgId)\
           { \
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderPid     = UEPS_PID_MTA;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverPid   = (ulRecvPid);\
            ((MSG_HEADER_STRU *)(pstMsg))->ulMsgName       = (ulMsgId); \
           }

/* ��װOSA��Ϣͷ(MTA�ڲ���Ϣ) */
#define TAF_MTA_CFG_INTRA_MSG_HDR(pstMsg, ulMsgId)\
            TAF_MTA_CFG_MSG_HDR(pstMsg, UEPS_PID_MTA, ulMsgId)

/* ��ȡOSA��Ϣ���� */
#define TAF_MTA_GET_MSG_ENTITY(pstMsg)\
            ((VOS_VOID *)&(((MSG_HEADER_STRU *)(pstMsg))->ulMsgName))

/* ��ȡOSA��Ϣ���� */
#define TAF_MTA_GET_MSG_LENGTH(pstMsg)\
            (((MSG_HEADER_STRU *)(pstMsg))->ulLength)

/* ��װOSA��Ϣ��ʼ����Ϣ���ݽӿ� */
#define TAF_MTA_CLR_MSG_ENTITY(pstMsg)\
            PS_MEM_SET(TAF_MTA_GET_MSG_ENTITY(pstMsg), 0x0, TAF_MTA_GET_MSG_LENGTH(pstMsg))

/* ��װOSA������Ϣ�ӿ� */
#define TAF_MTA_SEND_MSG(pstMsg)\
            PS_SEND_MSG(UEPS_PID_MTA, pstMsg)

/* �ַ���ת��Ϊ��ֵʱ�����õĺ� */
#define   MTA_UNSIGNED_LONG_FORMER_NINE_DIGIT    (429496729)      /* VOS_UINT32�������ֵ4294967295��ǰ9λ*/
#define   MTA_UNSIGNED_SHORT_FORMER_FOUR_DIGIT   (6553)           /* VOS_UINT16�������ֵ65535��ǰ4λ*/
#define   MTA_UNSIGNED_CHAR_FORMER_TWO_DIGIT     (25)             /* VOS_UINT8�������ֵ255��ǰ2λ*/
#define   MTA_SIGNED_LONG_FORMER_NINE_DIGIT      (214748364)      /* VOS_INT32�������ֵ2147483647��ǰ9λ*/

#define   MTA_UNSIGNED_LONG_LAST_DIGIT           '5'              /* VOS_UINT32�������ֵ4294967295�����1λ*/
#define   MTA_UNSIGNED_SHORT_LAST_DIGIT          '5'              /* VOS_UINT16�������ֵ65535�����1λ*/
#define   MTA_UNSIGNED_CHAR_LAST_DIGIT           '5'              /* VOS_UINT8�������ֵ255�����1λ*/
#define   MTA_SIGNED_LONG_POSITIVE_LAST_DIGIT    '7'              /* VOS_INT32�����������ֵ2147483647�����1λ*/
#define   MTA_SIGNED_LONG_NEGATIVE_LAST_DIGIT    '8'              /* VOS_INT32���͸�����Сֵ-2147483648�����1λ*/

#define   MTA_POSITIVE                           (1)              /* ���� */
#define   MTA_NEGATIVE                           (-1)             /* ���� */
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
  8 UNION����
*****************************************************************************/
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 TAF_MTA_Ac2ul(
    VOS_CHAR                           *pcStr,
    VOS_UINT32                          usLen,
    VOS_UINT32                         *pulRtn);
extern VOS_UINT32 TAF_MTA_Ac2us(
    VOS_CHAR                           *pcStr,
    VOS_UINT32                          ulLen,
    VOS_UINT16                         *pusRtn);
extern VOS_UINT32 TAF_MTA_Ac2uc(
    VOS_CHAR                           *pcStr,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucRtn);
extern VOS_UINT32 TAF_MTA_Ac2sl(
    VOS_CHAR                           *pcStr,
    VOS_UINT32                          usLen,
    VOS_INT32                          *plRtn);

extern VOS_UINT32 TAF_MTA_AcNums2DecNums(
    VOS_UINT8                          *pucAsciiNum,
    VOS_UINT8                          *pucDecNum,
    VOS_UINT32                          ulLen
);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


