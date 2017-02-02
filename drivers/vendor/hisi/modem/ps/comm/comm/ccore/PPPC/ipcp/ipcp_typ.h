/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ipcp_typ.h
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2012��11��8��
  ����޸�   :
  ��������   : PPPģ��IPCPЭ�鶨��ṹ��
  �����б�   :
*
*

  �޸���ʷ   :
  1.��    ��   : 2012��11��8��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/


#ifndef      _IPCP_TYPE_H_
#define      _IPCP_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */


typedef struct tagPppIpcpInfo
{
	PPPINFO_S *pstPppInfo ;           /* PPP���ƿ�ָ�� */
    UCHAR * pucIpv4cpMsg;             /* IPCP���ƿ��б���Э�̻�����Ϣ */    
	PPPFSM_S  stFsm;                  /* IPCPЭ��״̬�� */
	PPP_IPCP_OPTION_S stGotOptions;    /* �Ѿ�Э�̵����ҵ�ѡ�� */
	PPP_IPCP_OPTION_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */
	PPP_IPCP_OPTION_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
	PPP_IPCP_OPTION_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */
    ULONG ulIpv4cpLen;
    UCHAR ucUsedFlag;                  /*IPCP���ƿ�ʹ�ñ��*/
    UCHAR ucPppIpcpInfoRev[3];                  /*�����ֶ�*/
} PPPIPCPINFO_S ;

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _IPCP_TYPE_H_ */






