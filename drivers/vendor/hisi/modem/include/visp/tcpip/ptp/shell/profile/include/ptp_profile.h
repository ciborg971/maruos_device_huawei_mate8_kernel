/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Profile.h
  �� �� ��   : ����
  ��    ��   : ̷ǿ
  ��������   : 2008��5��4��
  ����޸�   :
  ��������   : PTP ģ��ӿڶ����ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��6��4��
    ��    ��   :  ̷ǿ
    �޸�����   :    PTP_Shell_Profile�����Ķ���
                                ULONG ulProfileType,  (ԭö�����Ͳ�����ΪULONG ����),
                                ���Ӳ���ULONG ulFsmMode(״̬��ģʽ)

******************************************************************************/
#ifndef _PTP_PROF_H_
#define _PTP_PROF_H_

/*addtional header files*/
#include "ptp/cbb/include/ptp_inc.h"
#ifdef __cplusplus
extern "C" {
#endif

/*����ģ������ö��*/
typedef  enum  tagPTP_PROFILE_TYPE_E
{
    ETE_UC_F = 1,       /*�˵��˵�����Ƶ��ͬ��*/
    ETE_MC_F,      /*�˵��˶ಥ��Ƶ��ͬ��*/
    ETE_UC_T,      /*�˵��˵�����ʱ��ͬ��*/
    ETE_MC_T,      /*�˵��˶ಥ��ʱ��ͬ��*/
    PTP_MC_F,      /*�㵽��ಥ��Ƶ��ͬ��*/
    PTP_MC_T       /*�㵽��ಥ��ʱ��ͬ��*/
}PTP_PROFILE_TYPE_E;

/*�˵��˵�����Ƶ��ͬ��*/
ULONG PTP_Profile_ETE_UC_F(USHORT usPortNumber, ULONG ulFsmMode);

/*�˵��˶ಥ��Ƶ��ͬ��*/
ULONG PTP_Profile_ETE_MC_F(USHORT usPortNumber, ULONG ulFsmMode);

/*�˵��˵�����ʱ��ͬ��*/
ULONG PTP_Profile_ETE_UC_T(USHORT usPortNumber, ULONG ulFsmMode);

/*�˵��˶ಥ��ʱ��ͬ��*/
ULONG PTP_Profile_ETE_MC_T(USHORT usPortNumber, ULONG ulFsmMode);

/*�㵽��ಥ��Ƶ��ͬ��*/
ULONG PTP_Profile_PTP_MC_F(USHORT usPortNumber, ULONG ulFsmMode);

/*�㵽��ಥ��ʱ��ͬ��*/
ULONG PTP_Profile_PTP_MC_T(USHORT usPortNumber, ULONG ulFsmMode);

ULONG PTP_Profile_Type(USHORT usPortNumber, ULONG ulFsmMode, ULONG ulProfileType);

#ifdef __cplusplus
}
#endif
#endif /*_PTP_PROF_H_*/
