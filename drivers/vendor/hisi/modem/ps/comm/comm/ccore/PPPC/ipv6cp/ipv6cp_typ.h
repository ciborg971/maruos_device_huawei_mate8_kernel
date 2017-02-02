/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ipv6cp_typ.h
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2012��11��8��
  ����޸�   :
  ��������   : PPPģ��IpV6CPЭ��ṹ�嶨��
  �����б�   :
*
*
#ifndef      _IPV6CP_TYPE_H_
  �޸���ʷ   :
  1.��    ��   : 2012��11��8��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef      _IPV6CP_TYPE_H_
#define      _IPV6CP_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/*˵�� Ŀǰ�ýṹ����ͬv4����һ�£���ΪĿǰ��ɾ������ʹ�õ���ͬһ��*/
typedef struct tagPppIpV6cpInfo
{
    PPPINFO_S *pstPppInfo ;               /* PPP���ƿ�ָ�� */
    UCHAR * pucIpv6cpMsg;
    PPPFSM_S  stFsm;                     /* IPv6CPЭ��״̬�� */
    PPP_IPV6CP_OPTION_S stGotOptions;    /* �Ѿ�Э�̵����ҵ�ѡ�� */
    PPP_IPV6CP_OPTION_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */
    PPP_IPV6CP_OPTION_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_IPV6CP_OPTION_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */
    ULONG ulIpv6cpLen;
    UCHAR ucUsedFlag;                    /*IPv6CP���ƿ�ʹ�ñ��,1ռ�ã�0��δռ��*/
    UCHAR ucIpv6cpInfoRev[3];            /*�����ֶ�*/
} PPPIPV6CPINFO_S ;

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _IPCP_TYPE_H_ */






