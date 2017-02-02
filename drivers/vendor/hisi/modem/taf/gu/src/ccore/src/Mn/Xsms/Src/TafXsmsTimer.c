/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsTimer.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��11��03��
  ��������   : 1X SMS(Short Message Service)�Ķ�ʱ������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafXsmsTimer.h"
#include  "TafXsmsCtx.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_TIMER_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
HTIMER                                  g_astXsmsTimer[TI_TAF_XSMS_TIMER_BUTT] = {VOS_NULL_PTR};
/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_XSMS_StartTimer
 ��������  : ��XSMSģ��ʹ�õĶ�ʱ��
 �������  : ulTimerId:��ʱ��ID
             ulTimerLen: ��ʱ��ʱ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_StartTimer(VOS_UINT32 ulTimerId, VOS_UINT32 ulTimerLen)
{
    if (TI_TAF_XSMS_TIMER_BUTT <= ulTimerId)
    {
        return;
    }

    TAF_XSMS_NORMAL_LOG1("TAF_XSMS_StartTimer: start timer id is", ulTimerId);
    TAF_XSMS_NORMAL_LOG1("TAF_XSMS_StartTimer: start timer len is", ulTimerLen);

    VOS_StartRelTimer(&g_astXsmsTimer[ulTimerId], UEPS_PID_XSMS, ulTimerLen, ulTimerId, 0, VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_5);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_StopTimer
 ��������  : ֹͣXSMSģ��ʹ�õĶ�ʱ��
 �������  : ulTimerId:��ʱ��ID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_StopTimer(VOS_UINT32 ulTimerId)
{
    if (TI_TAF_XSMS_TIMER_BUTT <= ulTimerId)
    {
        return;
    }

    if (VOS_NULL_PTR == g_astXsmsTimer[ulTimerId])
    {
        return;
    }

    TAF_XSMS_NORMAL_LOG1("TAF_XSMS_StartTimer: stop timer id is", ulTimerId);

    VOS_StopRelTimer(&g_astXsmsTimer[ulTimerId]);

    return;
}




#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





