/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Profile.h
  �� �� ��   : ����
  ��    ��   : ̷ǿ
  ��������   : 2008��5��4��
  ����޸�   :
  ��������   : ���߶���ѡԴ�㷨ģ�鶨��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   :
    ��    ��   :
    �޸�����   :

******************************************************************************/
#ifndef _PTP_BMC_H_
#define _PTP_BMC_H_

/*addtional header files*/
#include "ptp/cbb/include/ptp_inc.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
*Func Name   : PTP_Shell_CompareClockQuality
*Description : ʱ�������ȽϺ���
*Input       : pstPtpPort      ʱ�Ӷ˿�ָ�� 
               pstForeMasterA  ��Ƚ�ʱ��������foreignmaster�ṹ��ָ��
               pstForeMasterB  ��Ƚ�ʱ��������foreignmaster�ṹ��ָ��
*Output      : N/A
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME               DESCRIPTION
*
*******************************************************************************/
ULONG PTP_Shell_CompareClockQuality(PTP_PORT_S *pstPtpPort,
                                    PTP_FOREIGN_MASTER_S *pstForeMasterA,
                                    PTP_FOREIGN_MASTER_S *pstForeMasterB);

/******************************************************************************
*Func Name   : PTP_Shell_IsForeMasterValid
*Description : ʱ����Ч���жϺ���
*Input       : pstForeMaster  ���ж�ʱ����Ч�Ե�foreignmaster�ṹ��ָ��               
*Output      : N/A
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����PTP_ERR_BMC_MASTER_INVALID
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME               DESCRIPTION
*
*******************************************************************************/
ULONG PTP_Shell_IsForeMasterValid(PTP_FOREIGN_MASTER_S *pstForeMaster);

/******************************************************************************
*Func Name   : PTP_Shell_BMC
*Description : ����ѡԴ����
*Input       : pstPtpPort      ʱ�Ӷ˿�ָ��                
*Output      : *pulRecommendState   ���ظ������ߵ��Ƽ�״̬
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME               DESCRIPTION
*
*******************************************************************************/
ULONG PTP_Shell_BMC(PTP_PORT_S *pstPtpPort, ULONG *pulRecommendState);

#ifdef __cplusplus
}
#endif
#endif /*_PTP_BMC_H_*/
