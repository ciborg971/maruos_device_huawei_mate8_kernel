/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_pub_ha.h
*
*  Project Code: VISPV100R007
*   Module Name: PUBLIC HA  
*  Date Created: 2008-04-09
*        Author: zhoutong(43740)
*   Description: ����ģ��HA�궨���뺯������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-09   zhoutong(43740)         Create
*
*******************************************************************************/
#ifndef _TCPIP_PUB_HA_H_
#define _TCPIP_PUB_HA_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/* ����ģ��HA�����в�����Ķ��� */
typedef enum tagPUBLIC_HAHEAD_TYPE
{
    PUBLIC_INFORMATION_BAK = 1,           /* ����ģ��������ݵ�ʵʱ���� */
    PUBLIC_SOCKSCHEDULE_BAK,              /* ����Sock�¼������ĵ��ȴ��� */
    PUBLIC_PINGALLOWLIST_BAK = 0x81,      /* ping allow list��ʵʱ���ݣ���ҪԤ��һЩֵ��VISPV1R6ʹ�ã��ʴ�0x81��ʼ */
    PUBLIC_OPTIM_BAK,                     /* �����Ż���ʵʱ���� */

    PUBLIC_BATCH_BAK = 0xff   /* ����ģ�����������������ݣ�����ģ��������������ʱ���ڴ��ֶ�֮ǰ��������� */
}PUBLIC_HAHEAD_TYPE_E;

/* ����ģ��HA������TLV���͵Ķ��� */
typedef enum tagPUBLIC_HATLV_TYPE
{
    PUBLIC_HA_PINGALLOWLIST_ADD       = 0x0001, /* ���ӵ�ַ��ping allow list */
    PUBLIC_HA_PINGALLOWLIST_DELSINGLE = 0x0002, /* ��ping allow list��ɾ��һ����ַ */
    PUBLIC_HA_PINGALLOWLIST_DELALL    = 0x0003, /* ɾ��ping allow list�е����е�ַ */
    PUBLIC_HA_OPTIM_TYPE              = 0x0004, /* �����Ż���ģ�鱸������ */
    PUBLIC_HA_SOCKSCHEDULE            = 0x0005, /* ����Sock�¼������ĵ��ȴ��� */
}PUBLIC_HATLV_TYPE_E;

/* �������ֱ�����Ϣ */
typedef struct tagPUBLIC_HEAD_BAK
{
    ULONG  ulLinkMaxPkt;         
    ULONG  ulPingForbidFlag;
}PUBLIC_HEAD_BAK_S;

typedef struct tagHA_PINGALLOWLIST_ADDR
{
    ULONG ulIPAddr;             /*��ַ*/
    ULONG ulSubnetMask;         /*��������*/
}HA_PINGALLOWLIST_ADDR_S;

/* ���������������Ż����ֱ�����Ϣ(TLV) */
typedef struct tagPUBLIC_OPTIM_BAK
{
    ULONG  ulOptimEnable;
    ULONG  ulOptimEntrySum;
}PUBLIC_OPTIM_BAK_S;

/* ����������Sock Schedule���ֱ�����Ϣ(TLV) */
typedef struct tagPUBLIC_SOCKSCHEDULE_BAK
{
    ULONG  ulSwitch;
    ULONG  ulTimes;
    ULONG  ulDelayTime;
}PUBLIC_SOCKSCHEDULE_BAK_S;


/* PUBLIC HA����HA������ͷ */
#define SET_PUBLIC_HA_HEAD(pucData, ucHAMid, ucBakOperation, usBakMsgLen)\
{\
    HAMSGHEADER_S* pstHaHdr = (HAMSGHEADER_S *)(pucData);\
    pstHaHdr->ucModID = (UCHAR)(ucHAMid);\
    pstHaHdr->ucOperation = (UCHAR)(ucBakOperation);\
    pstHaHdr->usMsgLen = (USHORT)(usBakMsgLen);\
}

extern ULONG g_ulPUBLICBakDbg; 
extern ULONG g_ulPUBVerboseDebug;

extern ULONG PUBLIC_HA_PingAllosList_Input(UCHAR *pucBuf);
extern ULONG PUBLIC_HA_PingAllowList_Backup(ULONG ulOperation, ULONG ulIPAddr, ULONG ulSubnetMask);
extern ULONG PUBLIC_HA_OptimInput(UCHAR *pucBuf);
extern ULONG PUBLIC_HA_BatchBackup(VOID);
extern ULONG PUBLIC_HA_Backup(UCHAR ucOperation);
extern ULONG PUBLIC_HA_Input(UCHAR *pucInBuf, USHORT usDataLen);
extern ULONG PUBLIC_HA_Smooth(VOID);
extern ULONG PUBLIC_HA_Clean(VOID);
extern VOID  PUBLIC_HA_DebugOutPut(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _TCPIP_PUB_HA_H_ */

