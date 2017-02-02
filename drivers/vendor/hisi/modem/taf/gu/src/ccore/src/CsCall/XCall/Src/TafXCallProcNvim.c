/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallProcNvim.c
  �� �� ��   : ����
  ��    ��   : h00313353
  ��������   : 2015��07��07��
  ����޸�   :
  ��������   : ����Nvim���ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2015��07��07��
    ��    ��   : h00313353
    �޸�����   : �����ļ�

******************************************************************************/


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/

#include "TafXCallCtx.h"
#include "NVIM_Interface.h"
#include "TafXCallProcNvim.h"
#include "TafLog.h"
#include "TafXCallMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_TAF_X_CALL_PROC_NVIM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
   2 ��������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_XCALL_ReadEmcCallRedialPeriod
 ��������  : ��ȡ�������ز���ʱ��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��6��
    ��    ��   : h00313353
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID  TAF_XCALL_ReadEmcCallRedialPeriod(VOS_VOID)
{
    TAF_XCALL_CONFIG_STRU                                  *pstXcallConfig = VOS_NULL_PTR;
    TAF_XCALL_NVIM_1X_EMC_CALL_REDIAL_PERIOD_STRU           stEmcCallRedialPeriod;

    pstXcallConfig      = TAF_XCALL_GetConfigInfo();

    PS_MEM_SET(&stEmcCallRedialPeriod, 0x0, sizeof(stEmcCallRedialPeriod));

    if (NV_OK != NV_Read(en_Nv_Item_EMC_REDIAL_PERIOD,
                         &stEmcCallRedialPeriod, sizeof(stEmcCallRedialPeriod)))
    {
        pstXcallConfig->ulEmcRedialPeriod   = TAF_XCALL_EMC_CALL_REDIAL_PERIOD_DEFAULT * 1000;

        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_ReadEmcCallRedialPeriod():WARNING: en_Nv_Item_EMC_REDIAL_PERIOD Error");;
        return;
    }

    pstXcallConfig->ulEmcRedialPeriod = stEmcCallRedialPeriod.ulEmcCallRedialPeriod * 1000;

    TAF_XCALL_MNTN_LogEmcCallRedialPeriod();

    return;
}


VOS_VOID TAF_XCALL_Read1xVoiceSoCfgNvim()
{
    TAF_XCALL_SO_TYPE_ENUM_UINT16      *penSoType = VOS_NULL_PTR;
    TAF_NVIM_1X_VOICE_SO_CFG            st1xVoiceSoCfg;

    penSoType = &(TAF_XCALL_GetConfigInfo()->enSoInitType);

    PS_MEM_SET(&st1xVoiceSoCfg, 0x0, sizeof(st1xVoiceSoCfg));

    if (NV_OK != NV_Read(en_Nv_Item_1X_VOICE_SO_CFG,
                         &st1xVoiceSoCfg, sizeof(st1xVoiceSoCfg)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_Read1xVoiceSoCfgNvim:Read Nvim Failed");

       *penSoType = TAF_XCALL_SO_3_EVRC;
        return;
    }

    if ((TAF_XCALL_SO_3_EVRC    != st1xVoiceSoCfg.usSo)
     && (TAF_XCALL_SO_68_EVRC_B != st1xVoiceSoCfg.usSo))
    {
        *penSoType = TAF_XCALL_SO_3_EVRC;
        
    }
    else
    {
        *penSoType = st1xVoiceSoCfg.usSo;
    }
   
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ReadStartAndStopContDtmfIntervalLen
 ��������  : ��ȡ ����Stop Cont DTMF Req��Start Cont DTMF Reqʱ������ʱ��ʱ������λΪ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��18��
    ��    ��   : l00324781
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_XCALL_ReadStartAndStopContDtmfIntervalLen(VOS_VOID)
{
    TAF_XCALL_CONFIG_STRU                                  *pstXcallConfig = VOS_NULL_PTR;
    TAF_XCALL_NVIM_START_AND_STOP_CONT_DTMF_INTERVAL_STRU   stStartAndStopContDtmfInterVal;

    pstXcallConfig      = TAF_XCALL_GetConfigInfo();

    PS_MEM_SET(&stStartAndStopContDtmfInterVal, 0x0, sizeof(stStartAndStopContDtmfInterVal));

    if (NV_OK != NV_Read(en_NV_Item_START_AND_STOP_CONT_DTMF_INTERVAL,
                         &stStartAndStopContDtmfInterVal, sizeof(stStartAndStopContDtmfInterVal)))
    {
        /* ��ȡʧ�ܣ�ʹ����Сʱ����Ϊ360ms */
        pstXcallConfig->ulStartAndStopContDtmfIntervalLen = TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MIN;

        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_ReadStartAndStopContDtmfIntervalLen():WARNING: en_NV_Item_START_AND_STOP_CONT_DTMF_INTERVAL Error");
        return;
    }

    /* NV���ü�� */
    if (TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MIN > stStartAndStopContDtmfInterVal.ulStartAndStopContDtmfIntervalLen)
    {
        pstXcallConfig->ulStartAndStopContDtmfIntervalLen = TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MIN;
    }
    else if (TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MAX < stStartAndStopContDtmfInterVal.ulStartAndStopContDtmfIntervalLen)
    {
        pstXcallConfig->ulStartAndStopContDtmfIntervalLen = TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MAX;
    }
    else
    {
        pstXcallConfig->ulStartAndStopContDtmfIntervalLen = stStartAndStopContDtmfInterVal.ulStartAndStopContDtmfIntervalLen;
    }

    /* ��ά�ɲ⣬���� */
    TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval();

    return;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




