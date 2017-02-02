/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ccp_type.h
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2012��11��8��
  ����޸�   :
  ��������   :    PPPģ�鶨��CCPЭ��ṹ��
  �����б�   :
*
*

  �޸���ʷ   :
  1.��    ��   : 2012��11��8��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/

#ifdef		__cplusplus
extern		"C"{
#endif

#ifndef _CCP_TYPE_H_
#define _CCP_TYPE_H__
/********************************************************************/

/********************************************************************/
typedef struct tagPppCcpInfo
{
    PPPINFO_S *pstPppInfo ;            /* PPP���ƿ�ָ�� */
    PPP_CCP_options_S stGotOptions;    /* �Ѿ�Э�̵����ҵ�ѡ�� */
    PPP_CCP_options_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */
    PPP_CCP_options_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_CCP_options_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */
    PPPFSM_S  stFsm;                   /* CCPЭ��״̬�� */
    RELTMR_T     ulCcpTimeoutID;          /* CCPЭ�̳�ʱ��ʱ�� */

    ULONG     ulTimeOutTime;           /* CCPЭ�̳�ʱʱ�� */  /* Added by heyajun kf1199 at 2004-08-05 V800R001C01B010 for BYHD03171 */
    UCHAR  ucPppCompType;           /* 1��MPPC��2��LZS0��3��LZS1*/
    UCHAR  ucUsed;               /*ccp���ƿ�ռ�ñ��*/
    UCHAR  ucPppCcpInfoRev[2];     /*�����ֶ�*/


} PPP_CCP_INFO_S ;
/********************************************************************/

#endif /*_CCP_TYPE_H_*/

#ifdef		__cplusplus
}
#endif
