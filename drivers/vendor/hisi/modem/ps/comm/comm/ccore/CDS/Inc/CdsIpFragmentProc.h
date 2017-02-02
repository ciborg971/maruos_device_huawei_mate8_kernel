

#ifndef __CDS_IPFRAGMENT_PROC_H__
#define __CDS_IPFRAGMENT_PROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "CdsDepend.h"
#include "CdsIpfCtrl.h"
#include "TcpIpTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define CDS_IPV4_FRAGMENT_BUFF_SIZE               (30)                  /**/
#define CDS_IPV6_FRAGMENT_BUFF_SIZE               (20)                  /**/
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
   5 STRUCT����
*****************************************************************************/


/*****************************************************************************
 �ṹ��    : CDS_IPV4_FRAGMENT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS IPV4�ֶ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8        ucEpsbID;
    VOS_UINT8        aucRev[1];

    VOS_UINT16       usIpIdentity;
    IPV4_ADDR_UN     unSrcAddr;
    IPV4_ADDR_UN     unDstAddr;
}CDS_IPV4_FRAGMENT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CDS_IPV4_FRAGMENT_BUFF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS IPV4��Ƭ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulIndex;
    CDS_IPV4_FRAGMENT_INFO_STRU        astSegBuff[CDS_IPV4_FRAGMENT_BUFF_SIZE];
}CDS_IPV4_FRAGMENT_BUFF_STRU;

/*****************************************************************************
 �ṹ��    : CDS_IPV6_FRAGMENT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS IPV6��Ƭ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8        ucEpsbID;
    VOS_UINT8        aucRev[3];
    IPV6_ADDR_UN     unSrcAddr;
    IPV6_ADDR_UN     unDstAddr;
    VOS_UINT32       ulIdentity;
}CDS_IPV6_FRAGMENT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : CDS_IPV6_FRAGMENT_BUFF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS IPV6��Ƭ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulIndex;
    CDS_IPV6_FRAGMENT_INFO_STRU        astSegBuff[CDS_IPV6_FRAGMENT_BUFF_SIZE];
}CDS_IPV6_FRAGMENT_BUFF_STRU;

/*****************************************************************************
 �ṹ��    : CDS_IP_FRAGMENT_STATS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS IP��Ƭͳ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulRxIpv4Frag;               /*����IPV4��Ƭ�ĸ���*/
    VOS_UINT32                  ulRxIpv4IpfSucc;            /*����IPV4 IPF���˳ɹ��ĸ���*/
    VOS_UINT32                  ulRxIpv4IpfFail;            /*����IPV4 IPF����ʧ�ܸ���*/
    VOS_UINT32                  ulRxIpv6Frag;               /*����IPV6��Ƭ����*/
    VOS_UINT32                  ulRxIpv6IpfSucc;            /*����IPV6 IPF���˳ɹ��ĸ���*/
    VOS_UINT32                  ulRxIpv6IpfFail;            /*����IPV6 IPF����ʧ�ܵĸ���*/
    VOS_UINT32                  ulLocalProcSucc;            /*���ձ��ش���ɹ��ĸ���*/
    VOS_UINT32                  ulLocalProcFail;            /*���ձ��ش���ʧ�ܵĸ���*/
}CDS_IP_FRAGMENT_STATS_STRU;

/*****************************************************************************
 �ṹ��    : CDS_IPV6_SEGMENT_BUFF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS IPV6��Ƭ����
*****************************************************************************/
typedef struct
{
    CDS_IPV4_FRAGMENT_BUFF_STRU        stIpV4Buff;
    CDS_IPV6_FRAGMENT_BUFF_STRU        stIpV6Buff;
    CDS_IP_FRAGMENT_STATS_STRU         stStats;
}CDS_IP_FRAGMENT_BUFF_STRU;


/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/
extern     CDS_IP_FRAGMENT_BUFF_STRU       g_stCdsIpFragBuff;

/*��ȡIPV4��Ƭ����BUFF*/
#define CDS_GET_IPV4_FRAGMENT_BUFF()            (&(g_stCdsIpFragBuff.stIpV4Buff))

/*��ȡIPV6��Ƭ����BUFF*/
#define CDS_GET_IPV6_FRAGMENT_BUFF()            (&(g_stCdsIpFragBuff.stIpV6Buff))

/*��ȡIP��Ƭ����ͳ����*/
#define CDS_GET_IP_FRAGMENT_STATS_STRU()        (&(g_stCdsIpFragBuff.stStats))


/*ͳ����Ϣ*/
#define CDS_IPFRAG_RX_IPV4_PKT(n)                (g_stCdsIpFragBuff.stStats.ulRxIpv4Frag += (n))
#define CDS_IPFRAG_RX_IPV4_IPF_SUCC(n)           (g_stCdsIpFragBuff.stStats.ulRxIpv4IpfSucc += (n))
#define CDS_IPFRAG_RX_IPV4_IPF_FAIL(n)           (g_stCdsIpFragBuff.stStats.ulRxIpv4IpfFail += (n))
#define CDS_IPFRAG_RX_IPV6_PKT(n)                (g_stCdsIpFragBuff.stStats.ulRxIpv6Frag    += (n))
#define CDS_IPFRAG_RX_IPV6_IPF_SUCC(n)           (g_stCdsIpFragBuff.stStats.ulRxIpv6IpfSucc += (n))
#define CDS_IPFRAG_RX_IPV6_IPF_FAIL(n)           (g_stCdsIpFragBuff.stStats.ulRxIpv6IpfFail += (n))
#define CDS_IPFRAG_LOCAL_PROC_SUCC(n)            (g_stCdsIpFragBuff.stStats.ulLocalProcSucc += (n))
#define CDS_IPFRAG_LOCAL_PROC_FAIL(n)            (g_stCdsIpFragBuff.stStats.ulLocalProcFail += (n))


/*****************************************************************************
  8 ��������
*****************************************************************************/



/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


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

#endif

