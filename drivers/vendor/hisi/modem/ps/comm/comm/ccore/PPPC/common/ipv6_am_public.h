/******************************************************************************

                  ��Ȩ���� (C), 2012-2020, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ipv6_am_public.h
  �� �� ��   : ����
  ��         ��   :  zhaichao
  ��������   : 2012��10��10��
  ����޸�   :
  ��������   : IPV6���ģ���ṩ��AM��ϵͳ�Ĺ���ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��10��
    ��    ��   : zhaichao
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _IPV6_AM_PUBLIC_H
#define _IPV6_AM_PUBLIC_H

/**************�궨��***************/
#define IPV6_V6_USER       1   
#define IPV6_V4V6_USER     2 

#define IPV6_ADD   0
#define IPV6_SUB   1

#define IPV6_IPV6CP_ATTEMPT  1   
#define IPV6_IPV6CP_SUCC     2 
/**************��������***************/

/*IPV6 FIXED HEADER */
typedef struct tagIpv6hdr {
#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)
    ULONG        traffic_class_1:4,
                 version:4,
                 flow_lbl_1:4,
                 traffic_class_2:4,
                 flow_lbl_2:16;
#else
    ULONG        version:4,
                 traffic_class:8,
                 flow_lbl:20;
#endif    

    USHORT       payload_len;
    UCHAR        nexthdr;
    UCHAR        hop_limit;

    in6_addr    saddr;
    in6_addr    daddr;
}VOS_PACKED IPV6HDR_S;


VOS_VOID IPV6_PerfActUserStatistic(ULONG ulPerfType,ULONG ulOper,ULONG ulDomainIndex);
VOS_UINT16 IPV6_CalcCheckSum(VOS_UINT8 *ptr, in6_addr *pSrcAddr, in6_addr *pDesAddr, const VOS_UINT8 *msg, 
                                       VOS_UINT32 ulLen, VOS_UINT8 ucPro);
VOS_UINT16 IPV6_CalcCheckSumExten(in6_addr *pSrcAddr, in6_addr *pDesAddr, const VOS_UINT8 *msg, 
                                                    VOS_UINT32 ulLen, VOS_UINT8 ucPro);
VOS_UINT32  IPV6_StopTimer(VOS_UINT32 ulTimerId);
extern VOS_UINT32 Ipv6_A11NotifySendRa(VOS_UINT32 ulPdnIndex);

#endif
