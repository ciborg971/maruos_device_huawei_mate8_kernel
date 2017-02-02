/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : lcp_type.h
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2012��11��8��
  ����޸�   :
  ��������   : PPPģ��LCPЭ��ṹ�嶨��
  �����б�   :
*
*

  �޸���ʷ   :
  1.��    ��   : 2012��11��8��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef      _LCP_TYPE_H_
#define      _LCP_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */



typedef struct tagPppLcpInfo
{
    PPPINFO_S *pstPppInfo ;           /* PPP���ƿ�ָ�� */
    PPPFSM_S  stFsm;                  /* LCPЭ��״̬�� */
    PPP_LCP_OPTION_S stGotOptions;    /* �Ѿ�Э�̵����ҵ�ѡ�� */
    PPP_LCP_OPTION_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */
    PPP_LCP_OPTION_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_LCP_OPTION_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */

    
#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)
    UCHAR ucUsedFlag:1;               /* lcp���ƿ�ʹ�ñ�ǣ�0:δʹ�ã�1:��ռ��*/
    UCHAR bReqSendAck:1;              /* lcp״̬������open̬�յ��ն�requestֱ�ӻظ�ack��������Э�̱��,0:��δ�յ�request 1:�Ѿ��յ� */
    UCHAR bRevbit:6;
#else
    UCHAR bRevbit:6;
    UCHAR bReqSendAck:1;              /* lcp״̬������open̬�յ��ն�requestֱ�ӻظ�ack��������Э�̱��,0:��δ�յ�request 1:�Ѿ��յ� */
    UCHAR ucUsedFlag:1;               /* lcp���ƿ�ʹ�ñ�ǣ�0:δʹ�ã�1:��ռ��*/
#endif
    UCHAR ucPppLcpInfoRev[7];          /*�����ֶ�*/
} PPPLCPINFO_S ;

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _LCP_TYPE_H_ */





