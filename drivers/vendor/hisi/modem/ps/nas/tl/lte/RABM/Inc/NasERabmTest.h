/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasERabmTest.h
  Description     : NasERabmTest.c header file
  History         :
     1.lihong00150010       2009-9-17     Draft Enact
     2.
******************************************************************************/

#ifndef __NASRABMTEST_H__
#define __NASRABMTEST_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LPSCommon.h"
#include "NasERabmPublic.h"
#include "NasERabmIpFilter.h"

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
#define NAS_ERABM_GetUlDataTransInfoAddr()                   (&g_stERabmUlDataTransInfo)

#define NAS_ERABM_GetDlDataTransInfoAddr()                   (&g_stERabmDlDataTransInfo)

/* ���������յ������ݰ��� */
#define NAS_ERABM_AddUlReceivePackageNum()                   ((NAS_ERABM_GetUlDataTransInfoAddr())->ulRecePackageNum++)

/* �������з��������ݰ��� */
#define NAS_ERABM_AddUlSendPackageNum()                      ((NAS_ERABM_GetUlDataTransInfoAddr())->ulSendPackageNum++)

/* ��������IDLE̬�����ݰ��� */
#define NAS_ERABM_AddUlIdlePackageNum()                      ((NAS_ERABM_GetUlDataTransInfoAddr())->ulIdlePackageNum++)

/* ��������SUSPEND̬�����ݰ��� */
#define NAS_ERABM_AddUlSuspendPackageNum()                   ((NAS_ERABM_GetUlDataTransInfoAddr())->ulSuspendPackageNum++)

/* �������ж��������ݰ��� */
#define NAS_ERABM_AddUlDiscardPackageNum()                   ((NAS_ERABM_GetUlDataTransInfoAddr())->ulDiscPackageNum++)

/* ��������δ�ҵ����������ݰ��� */
#define NAS_ERABM_AddUlUnfoundBearerPackageNum()             ((NAS_ERABM_GetUlDataTransInfoAddr())->ulUnfoundBearerPackageNum++)

/* ��������DHCPV4 SERVER�����ݰ��� */
#define NAS_ERABM_AddUlDhcpv4ServerPackageNum()              ((NAS_ERABM_GetUlDataTransInfoAddr())->ulDhcpv4ServerPacketNum++)

/* �������е�һ����Ƭ������ */
#define NAS_ERABM_AddUlFirstSegmentPackageNum()              ((NAS_ERABM_GetUlDataTransInfoAddr())->ulFirstSegmentPacketNum++)

/* �������з�Ƭ������ */
#define NAS_ERABM_AddUlSegmentPackageNum()                   ((NAS_ERABM_GetUlDataTransInfoAddr())->ulSegmentPacketNum++)

/* ��������δ�ҵ��˿ںŰ����� */
#define NAS_ERABM_AddUlUnfoundPortPackageNum()               ((NAS_ERABM_GetUlDataTransInfoAddr())->ulUnfoundPortPacketNum++)

/* ��ȡ���ص�������Ϣ */
#define NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId)       (&((NAS_ERABM_GetUlDataTransInfoAddr())->astBearerDataTransInfo[ulEpsbId-NAS_ERABM_MIN_EPSB_ID]))

/* ���ӳ��ط������ݰ����� */
#define NAS_ERABM_AddBearerSendPackageNum(ulEpsbId)          ((NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId))->ulSendPackageNum++)

/* ���ӳ��ض������ݰ����� */
#define NAS_ERABM_AddBearerDiscardPackageNum(ulEpsbId)       ((NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId))->ulDiscardPackageNum++)

/* ���ӳ���IDLE̬���ݰ����� */
#define NAS_ERABM_AddBearerIdlePackageNum(ulEpsbId)          ((NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId))->ulIdlePackageNum++)

/* ���ӳ���Suspend̬���ݰ����� */
#define NAS_ERABM_AddBearerSuspendPackageNum(ulEpsbId)          ((NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId))->ulSuspendPackageNum++)

/* ���ӳ��ع���DRB�����ڴ��� */
#define NAS_ERABM_AddBearerNoDrbTimes(ulEpsbId)              ((NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId))->ulEpsbNoDrbTimes++)

/* ��������ع���DRB�����ڶ����������ݰ����� */
#define NAS_ERABM_AddBearerNoDrbDiscardPackageNum(ulEpsbId)  ((NAS_ERABM_GetBearerDataTransInfoAddr(ulEpsbId))->ulEpsbNoDrbDiscPackageNum++)

/* ���������յ������ݰ��� */
#define NAS_ERABM_AddDlReceivePackageNum()                   ((NAS_ERABM_GetDlDataTransInfoAddr())->ulRecePackageNum++)

/* �������з��������ݰ��� */
#define NAS_ERABM_AddDlSendPackageNum()                      ((NAS_ERABM_GetDlDataTransInfoAddr())->ulSendPackageNum++)

/* �������ж��������ݰ��� */
#define NAS_ERABM_AddDlDiscardPackageNum()                   ((NAS_ERABM_GetDlDataTransInfoAddr())->ulDiscPackageNum++)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/* ����������Ϣ */
typedef struct
{
    VOS_UINT32                          ulSendPackageNum;           /* �������ݰ��� */
    VOS_UINT32                          ulDiscardPackageNum;        /* �������ݰ��� */
    VOS_UINT32                          ulIdlePackageNum;           /* IDLE̬���ݰ��� */
    VOS_UINT32                          ulSuspendPackageNum;        /* Suspend̬���ݰ��� */
    VOS_UINT32                          ulEpsbNoDrbTimes;           /* ���ֳ��ش���DRB�����ڵĴ��� */
    VOS_UINT32                          ulEpsbNoDrbDiscPackageNum;  /* ����ع�����DRB�����ڶ����������ݰ���*/
}NAS_ERABM_BERER_DATA_TRANS_INFO_STRU;

/* �������ݴ�����Ϣ�ṹ�� */
typedef struct
{
    VOS_UINT32                          ulRecePackageNum;          /* �յ����ݰ����� */
    VOS_UINT32                          ulSendPackageNum;          /* �������ݰ����� */
    VOS_UINT32                          ulDiscPackageNum;          /* �������ݰ����� */
    VOS_UINT32                          ulSuspendPackageNum;       /* DRB����SUSPEND̬ʱ�յ����ݰ���*/
    VOS_UINT32                          ulIdlePackageNum;          /* DRB����IDLE̬ʱ�յ����ݰ��� */
    VOS_UINT32                          ulDhcpv4ServerPacketNum;   /* DHCPV4 SERVER������ */
    VOS_UINT32                          ulFirstSegmentPacketNum;   /* ��һ����Ƭ������ */
    VOS_UINT32                          ulSegmentPacketNum;        /* ��Ƭ������ */
    VOS_UINT32                          ulUnfoundPortPacketNum;    /* δ�ҵ��˿ںŰ����� */
    VOS_UINT32                          ulUnfoundBearerPackageNum; /* δ�ҵ����ص����ݰ��� */
    NAS_ERABM_BERER_DATA_TRANS_INFO_STRU astBearerDataTransInfo[NAS_ERABM_MAX_EPSB_NUM];  /* ���ص�������Ϣ */
}NAS_ERABM_UL_DATA_TRANS_INFO_STRU;

/* �������ݴ�����Ϣ�ṹ�� */
typedef struct
{
    VOS_UINT32                          ulRecePackageNum;          /* �յ����ݰ����� */
    VOS_UINT32                          ulSendPackageNum;          /* �������ݰ����� */
    VOS_UINT32                          ulDiscPackageNum;          /* �������ݰ����� */
}NAS_ERABM_DL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_ERABM_UL_DATA_TRANS_INFO_STRU    g_stERabmUlDataTransInfo;
extern NAS_ERABM_DL_DATA_TRANS_INFO_STRU    g_stERabmDlDataTransInfo;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/
extern VOS_VOID  NAS_ERABM_CmdHelp( VOS_VOID );
extern VOS_VOID  NAS_ERABM_DebugInit(VOS_VOID);
extern VOS_VOID  NAS_ERABM_ShowEpsBearerDataTransInfo( VOS_UINT32 ulEspbId );
extern VOS_VOID  NAS_ERABM_ShowActiveEpsBearerDataTransInfo( VOS_VOID );
extern VOS_VOID  NAS_ERABM_ShowUlDataTransInfo( VOS_VOID);
extern VOS_VOID  NAS_ERABM_ShowDlDataTransInfo( VOS_VOID );
extern VOS_VOID  NAS_ERABM_ShowEpsbTftInfo( VOS_UINT32 ulEspbId );



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

#endif /* end of NasERabmTest.h */
