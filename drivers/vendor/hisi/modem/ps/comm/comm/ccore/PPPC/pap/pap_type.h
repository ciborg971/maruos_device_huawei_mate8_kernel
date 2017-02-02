/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pap_type.h
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2012��11��8��
  ����޸�   :
  ��������   : PPPģ��PAP�ṹ�嶨��
  �����б�   :
*
*

  �޸���ʷ   :
  1.��    ��   : 2012��11��8��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#if( VRP_MODULE_LINK_PPP_PAP == VRP_YES )

#ifndef      _PAPC_TYPE_H_
#define      _PAPC_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/* PAP ���ƿ����ݽṹ����*/
typedef struct tagPppPapInfo
{
    PPPINFO_S *pstPppInfo;/* PPP ���ƿ�ָ��*/
    VOID* pstAAAAuthReqMsg;
    RELTMR_T ulServerTimeoutID;         /* Server ��ʱ��ʱ�� ID */
    RELTMR_T ulClientTimeoutID;	/* Client ��ʱ��ʱ�� ID*/

    ULONG ulWaitReqTimeout;/* �ȴ��Զ���֤��ʱʱ�� */
    ULONG ulWaitLnsAuthTimeOut;
    ULONG ulSendReqTimeout;/* ��֤����ʱ�ش�ʱ�� */
    ULONG ulMaxTransmits;/* ��֤��������ʹ��� */
    ULONG ulWaitAuthRspTimeout;             /* �ȴ�AAA��Ȩ��Ӧ��ʱʱ�� */
    ULONG ulAuthMaxTransmits;/* ��֤��������ʹ��� */

    USHORT usAuthClientFailureTimes;	/* ������֤ʧ�ܴ���*/
    USHORT usAuthServerFailureTimes;	/* Զ����֤ʧ�ܴ���*/
    UCHAR ucClientState;/* Client ״̬ */
    UCHAR ucServerState;/* Server ״̬ */
    UCHAR ucId;	/* ��ǰ������֤�������ID*/
    UCHAR ucAuthTransmits;	/* ������֤����Ĵ��� */




    UCHAR ucTransmits;	/* ������֤����Ĵ���*/
    UCHAR ucPeerId;/* ��ǰ�Զ���֤�����ID */
    UCHAR ucUsed;  /*pap���ƿ�ʹ�ñ�ǣ�1ʹ�ã�0δʹ��*/
    UCHAR szPapUsrName[PPP_MAXUSERNAMELEN + 2];/*�û���*/
    UCHAR szPapUsrPwd[PPP_MAXUSERPWDLEN + 2];/*�û�����*/
    UCHAR ucPppPapInfoRev;        /*�����ֶ�*/

}PPPPAPINFO_S;


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PAP_TYPE_H_ */

#endif  /* #if( VRP_MODULE_LINK_PPP_PAP == VRP_YES ) */

#endif	/* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */


