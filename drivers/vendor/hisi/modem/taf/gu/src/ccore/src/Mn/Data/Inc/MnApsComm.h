
#ifndef _MN_APS_COMM_H_
#define _MN_APS_COMM_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* ��ȡָ��PDPID��PDPʵ���ַ */
#define TAF_APS_GetPdpEntInfoAddr(ucPdpId)      (&g_PdpEntity[ucPdpId])

/* ��ȡָ��PDPID��PDPʵ���Ӧ��NSAPI */
#define TAF_APS_GetPdpEntNsapi(ucPdpId)         (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->ucNsapi)

/* ��ȡָ��PDPID��PDPʵ���Ӧ��cliet info��ַ */
#define TAF_APS_GetPdpEntClientInfoAddr(ucPdpId)  (&(TAF_APS_GetPdpEntInfoAddr(ucPdpId)->stClientInfo))

/* ��ȡָ��PDPID��PDPʵ���Ӧ��CID */
#define TAF_APS_GetPdpEntCurrCid(ucPdpId)       (TAF_APS_GetPdpEntClientInfoAddr(ucPdpId)->ucCid)

/* ��ȡָ��PDPID��PDPʵ���Ӧ��APN��Ч��־ */
#define TAF_APS_GetPdpEntApnFlag(ucPdpId)       (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->PdpApnFlag)

/* ��ȡָ��PDPID��PDPʵ���Ӧ��APN��ַ */
#define TAF_APS_GetPdpEntApnInfoAddr(ucPdpId)   (&(TAF_APS_GetPdpEntInfoAddr(ucPdpId)->PdpApn))

/* ��ȡָ��PDPID��PDPʵ���Ӧ��APN���� */
#define TAF_APS_GetPdpEntApnLen(ucPdpId)        (TAF_APS_GetPdpEntApnInfoAddr(ucPdpId)->ucLength)

/* ��ȡָ��PDPID��PDPʵ���Ӧ��APN���� */
#define TAF_APS_GetPdpEntApnValue(ucPdpId)      (TAF_APS_GetPdpEntApnInfoAddr(ucPdpId)->aucValue)

/* ��ȡָ��PDPID��PDPʵ���Ӧ��PDP ADDRESS */
#define TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId) (&(TAF_APS_GetPdpEntInfoAddr(ucPdpId)->PdpAddr))

/* ��ȡָ��PDPID��PDPʵ���Ӧ��PDP TYPE */
#define TAF_APS_GetPdpEntPdpAddrType(ucPdpId)   (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->ucPdpTypeNum)

/* ��ȡָ��PDPID��PDPʵ���Ӧ��PDP ACT TYPE */
#define TAF_APS_GetPdpEntActType(ucPdpId)       (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->ActType)

/* ��ȡָ��PDPID��PDPʵ���Ӧ��GPRS PARA */
#define TAF_APS_GetPdpEntGprsParaAddr(ucPdpId)  (&(TAF_APS_GetPdpEntInfoAddr(ucPdpId)->GprsPara))

/* ��ȡָ��PDPID��PDPʵ���Ӧ��SNDCP�����ʶ */
#define TAF_APS_GetPdpEntSndcpActFlg(ucPdpId)   (TAF_APS_GetPdpEntProcTrackAddr(ucPdpId)->ucSNDCPActOrNot)

/* ��ȡָ��PDPID��PDPʵ���Ӧ��PROC TRACK */
#define TAF_APS_GetPdpEntProcTrackAddr(ucPdpId) (&(TAF_APS_GetPdpEntInfoAddr(ucPdpId)->PdpProcTrack))

/* ��ȡָ��PDPID��PDPʵ���Ӧ��IPV6 DNS */
#define TAF_APS_GetPdpEntPdpIpV6DnsInfoAddr(ucPdpId) (&(TAF_APS_GetPdpEntInfoAddr(ucPdpId)->stPdpIpV6Dns))

/* ��ȡָ��PDPID��PDPʵ���Ӧ��LINKEDNSAPI */
#define TAF_APS_GetPdpEntLinkedNsapi(ucPdpId)   (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->ucLinkedNsapi)

/* ��ȡָ��PDPID��PDPʵ���Ӧ��UsedFlg */
#define TAF_APS_GetPdpEntUsedFlg(ucPdpId)       (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->ulUsedFlg)

/* ��ȡָ��CID��CID TAB��Ӧ��IMSר�г��ر�ʾ */
#define TAF_APS_GetPdpEntImCnSigFlag(ucPdpId)   (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->enImCnSignalFlg)

/* ��ȡָ��PDPID��PDPʵ���Ӧ��PDP Addr��Ч��־ */
#define TAF_APS_GetPdpEntPdpAddrFlag(ucPdpId)   (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->PdpAddrFlag)

/* ��ȡָ��PDPID��PDPʵ���Ӧ��IP��ַ */
#define TAF_APS_GetPdpEntPdpIpAddr(ucPdpId)     (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->aucIpAddr)

/* ��ȡָ��PDPID��PDPʵ���Ӧ�Ľ������ر�ʶ */
#define TAF_APS_GetPdpEntEmcFlg(ucPdpId)        (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->enEmergencyFlg)

/* ��ȡָ��PDPID��PDPʵ���Ӧ��CAUSE */
#define TAF_APS_GetPdpEntPdpCause(ucPdpId)     (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->enCause)

/* ��ȡָ��CID�������ĵ�ַ */
#define TAF_APS_GetTafCidInfoAddr(ucCid)        (&g_TafCidTab[ucCid])

/* ��ȡָ��CID�������Ķ����ʶ */
#define TAF_APS_GetTafCidInfoUsedFlg(ucCid)     (TAF_APS_GetTafCidInfoAddr(ucCid)->ucUsed)

/* ��ȡָ��CID��Primary PDP��ʶ */
#define TAF_APS_GetTafCidInfoPrimPdpFlg(ucCid)  (TAF_APS_GetTafCidInfoAddr(ucCid)->ucPriCidFlag)

/* ��ȡָ��CID��Primary CID */
#define TAF_APS_GetTafCidInfoPrimCid(ucCid)     (TAF_APS_GetTafCidInfoAddr(ucCid)->ucPriCid)

/* ��ȡָ��CID��CID TAB��ַ */
#define TAF_APS_GetTafCidInfoCidTabAddr(ucCid)  (&(TAF_APS_GetTafCidInfoAddr(ucCid)->CidTab))

/* ��ȡָ��CID��CID TAB��Ӧ��PDP���� */
#define TAF_APS_GetTafCidInfoPdpAddr(ucCid)     (&(TAF_APS_GetTafCidInfoCidTabAddr(ucCid)->stPdpAddr))

/* ��ȡָ��CID��CID TAB��Ӧ��PDP���� */
#define TAF_APS_GetTafCidInfoPdpType(ucCid)     (TAF_APS_GetTafCidInfoPdpAddr(ucCid)->enPdpType)

/* ��ȡָ��CID��CID TAB��Ӧ��IPv4��ַ */
#define TAF_APS_GetTafCidInfoPdpIpv4Addr(ucCid) (&(TAF_APS_GetTafCidInfoPdpAddr(ucCid)->aucIpv4Addr[0]))

/* ��ȡָ��CID��CID TAB��Ӧ��APN */
#define TAF_APS_GetTafCidInfoApn(ucCid)         (&(TAF_APS_GetTafCidInfoCidTabAddr(ucCid)->stApn))

/* ��ȡָ��CID��CID TAB��Ӧ��APN���� */
#define TAF_APS_GetTafCidInfoApnLen(ucCid)      (TAF_APS_GetTafCidInfoApn(ucCid)->ucLength)

/* ��ȡָ��CID��CID TAB��Ӧ��APN�ַ��� */
#define TAF_APS_GetTafCidInfoApnData(ucCid)     (TAF_APS_GetTafCidInfoApn(ucCid)->aucValue)

/* ��ȡָ��CID��CID TAB��Ӧ�Ľ������ر�ʶ */
#define TAF_APS_GetTafCidInfoEmcFlg(ucCid)      (TAF_APS_GetTafCidInfoCidTabAddr(ucCid)->enEmergencyInd)

/* ���PDP IP��ַ�����Ƿ�����IPv4 */
#define TAF_APS_CheckPdpAddrTypeIpv4(ucPdpId)     \
        ( (APS_ADDR_DYNAMIC_IPV4 == (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->ucPdpTypeNum))  \
         || (APS_ADDR_STATIC_IPV4 == (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->ucPdpTypeNum)) \
         || (MN_APS_ADDR_IPV4V6 == (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->ucPdpTypeNum)) )

/* ���PDP IP��ַ�����Ƿ�����IPv6 */
#define TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)     \
        ( (MN_APS_ADDR_IPV6 == (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->ucPdpTypeNum))       \
         || (MN_APS_ADDR_IPV4V6 == (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->ucPdpTypeNum)) )  \

/* ���PDP�Ƿ�ΪPrimary PDP */
#define TAF_APS_CheckPrimaryPdp(ucPdpId)        (APS_PDP_ACT_PRI == (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->ActType))


/*****************************************************************************
  3 ö�ٶ���
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

#endif
