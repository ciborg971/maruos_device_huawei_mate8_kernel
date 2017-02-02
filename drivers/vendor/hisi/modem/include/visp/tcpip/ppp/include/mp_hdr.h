/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                               mp_hdr.h
*
*  Project Code: VISPV100R007C03
*   Module Name: MP  
*  Date Created: 2009-02-28
*        Author: wuhailan
*   Description: VISP �������ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-02-28   zhangchi                Create
*******************************************************************************/
#ifndef _MP_HDR_H_
#define _MP_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

#define  MP_HEALTH_MAX_ITEM     20  

#ifndef MP_SUPPORT_MAX_BIND
#define MP_SUPPORT_MAX_BIND     128
#endif


/* �ӿ�UP/DOWNͳ����Ϣ */
typedef struct tagMP_HEALTH_STATISTIC
{
    ULONG ulMpIfIndex;
    ULONG ulLostFragments;          /* ���շ������ķ�Ƭ */
    ULONG ulReorderedPkts;          /* ���շ������鱨���� */
    ULONG ulUnassignedPkts;         /* ���շ���ȴ�����ķ�Ƭ�� */
    ULONG ulInterleavedPkts;        /* ���ͷ���LFI�ķ�Ƭ���� */
    
    ULONG ulWindowMatchPkts;        /* ƥ�����鴰�ڱ��ĸ��� */
    ULONG ulWindowInPkts;           /* �������鴰���б��ĸ��� */
    ULONG ulWindowBehindPkts;       /* ������鴰�ڱ��ĸ��� */
    ULONG ulWindowSurpassPkts;      /* �������鴰�ڱ��ĸ��� */
}MP_HEALTH_STATISTIC_S;

typedef struct tagMP_HDR_MPBIND
{
    ULONG ulFatherIfIndex;
    ULONG ulMpBindNum;                          /* ������·��, ������Ч������·�� */
    ULONG ulSubLinkNum;                         /* ���õ�����·�� */  
}MP_HDR_MPBIND_S;

typedef struct tagMP_HDR_MPSUBLINK
{
    ULONG ulFatherIfIndex;
    ULONG ulSubLinkIfIndex;
    ULONG ulSubLinkStatus;
}MP_HDR_MPSUBLINK_S;

extern VOID MP_Health_BatchCheckup();
extern ULONG MP_Health_StatisticCheckup();
extern ULONG MP_Health_MpInfoCheckup();
extern ULONG MP_LastWord_BatchCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);
extern ULONG MP_LastWord_StatisticCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);
    
#ifdef  __cplusplus 
}
#endif
#endif /* _MP_HDR_H_ */

