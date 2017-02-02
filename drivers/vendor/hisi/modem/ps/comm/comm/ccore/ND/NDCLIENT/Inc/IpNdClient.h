

#ifndef __IPNDCLIENT_H__
#define __IPNDCLIENT_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "IpComm.h"
#include  "IpIpmGlobal.h"


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
  2 �궨��
*****************************************************************************/
#define NDCLIENT_TASK_PID     UEPS_PID_NDCLIENT      /*PID*/
#define NDCLIENT_TASK_FID     UEPS_FID_NDCLIENT      /*FID*/

/*��NDCLIENTʹ�õ��ڴ�ؽ������䣬�ֱ�����V9R1��V3R3*/
#if (FEATURE_OFF == FEATURE_SKB_EXP)
#define IP_NDCLIENT_MEM_POOL_ID             (TTF_MEM_POOL_ID_UL_IP_DATA)
#else
#define IP_NDCLIENT_MEM_POOL_ID             (TTF_MEM_POOL_ID_DL_SHARE)
#endif

#define IP_MAX_NDCLIENT_ENTITY_NUM      (11)

#define IP_NDCLIENT_GET_ADDR_INFO_INDEX(exEpsbId)       (IP_NdClient_GetEntityIndex(exEpsbId))

#define IP_NDCLIENT_Entity_IncRevPackageNum(ulEpsbId) \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulRevPackageNum++; \
                g_stNdClientStatInfo.ulRevPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncRevRaPackageNum(ulEpsbId)   \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulRevRaPackageNum++; \
                g_stNdClientStatInfo.ulRevRaPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncRevEchoReqPackageNum(ulEpsbId)   \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulRevEchoReqPackageNum++; \
                g_stNdClientStatInfo.ulRevEchoReqPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncRevTooBigPackageNum(ulEpsbId)   \
                        {\
                            g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulRevTooBigPackageNum++; \
                            g_stNdClientStatInfo.ulRevTooBigPackageNum++; \
                        }

#define IP_NDCLIENT_Entity_IncSendPackageNum(ulEpsbId)   \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulSendPackageNum++; \
                g_stNdClientStatInfo.ulSendPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncSendRsPackageNum(ulEpsbId)   \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulSendRsPackageNum++; \
                g_stNdClientStatInfo.ulSendRsPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncSendEchoReplyPackageNum(ulEpsbId)   \
                        {\
                            g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulSendEchoReplyPackageNum++; \
                            g_stNdClientStatInfo.ulSendEchoReplyPackageNum++; \
                        }

#define IP_NDCLIENT_Entity_IncSendICMPV6TooBigPackageNum(ulEpsbId)   \
                        {\
                            g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulSendICMPV6TooBigPackageNum++; \
                            g_stNdClientStatInfo.ulSendICMPV6TooBigPackageNum++; \
                        }

#define IP_NDCLIENT_Entity_IncDiscPackageNum(ulEpsbId)    \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulDiscPackageNum++; \
                g_stNdClientStatInfo.ulDiscPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncRevNotForMePackageNum(ulEpsbId)  \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulRevNotForMePackageNum++; \
                g_stNdClientStatInfo.ulRevNotForMePackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncRevInvalidPackageNum(ulEpsbId)   \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulRevInvalidPackageNum++; \
                g_stNdClientStatInfo.ulRevInvalidPackageNum++; \
            }

#define IP_NDCLIENT_Entity_IncTimerNum(ulEpsbId)      \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulTimerNum++; \
                g_stNdClientStatInfo.ulTimerNum++; \
            }

#define IP_NDCLIENT_Entity_IncTimeoutNum(ulEpsbId)      \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulTimeoutNum++; \
                g_stNdClientStatInfo.ulTimeoutNum++; \
            }

#define IP_NDCLIENT_Entity_IncMemAllocNum(ulEpsbId)    \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulMemAllocNum++; \
                g_stNdClientStatInfo.ulMemAllocNum++; \
            }

#define IP_NDCLIENT_Entity_IncMemFreeNum(ulEpsbId)     \
            {\
                g_stNdClientEntity[IP_NDCLIENT_GET_ADDR_INFO_INDEX(ulEpsbId)].stStats.ulMemFreeNum++; \
                g_stNdClientStatInfo.ulMemFreeNum++; \
            }

#define IP_NDCLIENT_IncRevPackageNum()          g_stNdClientStatInfo.ulRevPackageNum++;
#define IP_NDCLIENT_IncRevRaPackageNum()        g_stNdClientStatInfo.ulRevRaPackageNum++;
#define IP_NDCLIENT_IncRevEchoReqPackageNum()   g_stNdClientStatInfo.ulRevEchoReqPackageNum++;
#define IP_NDCLIENT_IncRevTooBigPackageNum()    g_stNdClientStatInfo.ulRevTooBigPackageNum
#define IP_NDCLIENT_IncSendPackageNum()         g_stNdClientStatInfo.ulSendPackageNum++;
#define IP_NDCLIENT_IncSendRsPackageNum()       g_stNdClientStatInfo.ulSendRsPackageNum++;
#define IP_NDCLIENT_IncSendEchoReplyPackageNum() g_stNdClientStatInfo.ulSendEchoReplyPackageNum++;
#define IP_NDCLIENT_IncSendICMPV6TooBigPackageNum() g_stNdClientStatInfo.ulSendICMPV6TooBigPackageNum++;
#define IP_NDCLIENT_IncDiscPackageNum()         g_stNdClientStatInfo.ulDiscPackageNum++;
#define IP_NDCLIENT_IncRevNotForMePackageNum()  g_stNdClientStatInfo.ulRevNotForMePackageNum++;
#define IP_NDCLIENT_IncRevInvalidPackageNum()   g_stNdClientStatInfo.ulRevInvalidPackageNum++;
#define IP_NDCLIENT_IncTimerNum()               g_stNdClientStatInfo.ulTimerNum++;
#define IP_NDCLIENT_IncTimeoutNum()             g_stNdClientStatInfo.ulTimeoutNum++;
#define IP_NDCLIENT_IncMemAllocNum()            g_stNdClientStatInfo.ulMemAllocNum++;
#define IP_NDCLIENT_IncMemFreeNum()             g_stNdClientStatInfo.ulMemFreeNum++;

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : NDCLIENT_TIMER_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : NDCLIENT��ʱ��ö��
*****************************************************************************/
enum NDCLIENT_TIMER_ENUM
{
    /* ND CLIENT��ʱ�� */
    IP_NDCLIENT_TIMER_RS               = 0,

    IP_NDCLIENT_TIMER_BUTT
};
typedef VOS_UINT32 NDCLIENT_TIMER_ENUM_UINT32;

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


/* ͳ������ */
typedef struct
{
    VOS_UINT32                          ulRevPackageNum;            /* �յ����ݰ����� */
    VOS_UINT32                          ulRevRaPackageNum;          /* �յ�RA���� */
    VOS_UINT32                          ulRevEchoReqPackageNum;     /* �յ�ECHO REQUEST����*/
    VOS_UINT32                          ulRevTooBigPackageNum;      /* �յ�����������*/
    VOS_UINT32                          ulSendPackageNum;           /* �������ݰ����� */
    VOS_UINT32                          ulSendRsPackageNum;         /* ����RS���� */
    VOS_UINT32                          ulSendEchoReplyPackageNum;  /* ����ECHO REPLY���� */
    VOS_UINT32                          ulSendICMPV6TooBigPackageNum; /* ���ͳ�������Ӧ���� */
    VOS_UINT32                          ulDiscPackageNum;           /* �������ݰ����� */
    VOS_UINT32                          ulRevNotForMePackageNum;    /* �յ����ܴ�������ݰ����� */
    VOS_UINT32                          ulRevInvalidPackageNum;     /* �յ�Checksum Error���ݰ����� */

    VOS_UINT32                          ulTimerNum;                 /* Timer����ͳ�� */
    VOS_UINT32                          ulTimeoutNum;               /* Timer��ʱͳ�� */

    VOS_UINT32                          ulMemAllocNum;              /* �ڴ����ͳ�� */
    VOS_UINT32                          ulMemFreeNum;               /* �ڴ��ͷ�ͳ�� */

}IP_NDCLIENT_STATISTIC_INFO_STRU;

/* NDCLIENTʵ�� */
typedef struct
{
    VOS_UINT8                           ucEpsbId;       /*DSDA�޸ĺ󣬸�2bit����ModemId����6bit����EPSID*/
    VOS_UINT8                           ucflag;
    VOS_UINT8                           aucReserve1[2];
    IP_ICMPV6_TYPE_ENUM_UINT32          enMsgType;

    VOS_UINT8                           aucInterfaceId[ND_IPV6_IF_LEN];
    VOS_UINT8                           aucRouterIpAddr[IP_IPV6_ADDR_LEN];
    IP_TIMER_STRU                       stTimerInfo;
    IP_SND_MSG_STRU                     stIpSndNwMsg;
    VOS_UINT16                          usRouterLifeTime;
    VOS_UINT8                           aucReserve2[2];
    VOS_UINT32                          ulReachableTimer;
    VOS_UINT32                          ulReTransTime;
    VOS_UINT32                          ulMtu;
    IP_NDCLIENT_STATISTIC_INFO_STRU     stStats;
}IP_NDCLIENT_ENTITY_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID IP_NdClient_Init(VOS_VOID);
extern VOS_UINT32  IP_NdClient_GetEntityIndex(VOS_UINT8 ucExEpsId);







#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of IpNdClient.h */
