


/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "R_ITF_FlowCtrl.h"
#include "NVIM_Interface.h"
#include "TTFMem.h"
#include "FcIntraMsg.h"
#include "PsCommonDef.h"
#include "Fc.h"
#include "TTFComm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/******************************************************************************
   2 �ⲿ������������
******************************************************************************/
extern VOS_UINT32 IPSCH_FeatureSwitchIsOn(VOS_VOID);

/******************************************************************************
   3 ˽�ж���
******************************************************************************/
/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID                    PS_FILE_ID_R_ITF_FLOW_CTRL_C


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
/* R�ӿ�����ʵ�嶨�� */
R_ITF_FLOW_CTRL_STRU                    g_stRItfFlowCtrl;
VOS_UINT32                              g_ulRItfFlowCtrlProTime = 0;
R_ITF_FLOW_CTRL_CONFIG_STRU             g_stRItfFlowCtrlConfig;
VOS_UINT32                              g_ulLteFlowCtrl  =   VOS_FALSE;

VOS_UINT32      g_ulRItfFlowCtrlCnt = 0;
VOS_UINT32      g_ulRItfFlowCtrlDiscardNum = 20;

#define         RITF_FLOWCTRL_WRED_THRESHOLD        (g_ulRItfFlowCtrlDiscardNum)


/******************************************************************************
   6 ����ʵ��
******************************************************************************/
/*lint -save -e958 */

VOS_VOID R_ITF_MntnFlowCtrlEvent
(
    R_ITF_FLOW_CTRL_TYPE_ENUM_UINT32 ulFlowCtrlType,
    VOS_UINT32                       ulNewLev,
    R_ITF_FLOW_CTRL_CMD_ENUM_UINT32  ulFlowCtrlCmd,
    VOS_UINT32                       ulResult
)
{
    R_ITF_FLOW_CTRL_MNTN_INFO_STRU                stMntnInfo;


    stMntnInfo.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stMntnInfo.ulSenderPid     = WUEPS_PID_RLC;
    stMntnInfo.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stMntnInfo.ulReceiverPid   = WUEPS_PID_RLC;
    stMntnInfo.ulLength        = sizeof(R_ITF_FLOW_CTRL_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    stMntnInfo.enFlowCtrlType  = ulFlowCtrlType;
    stMntnInfo.ulNewLevel      = ulNewLev;
    stMntnInfo.enFlowCtrlCmd   = ulFlowCtrlCmd;
    stMntnInfo.ulResult        = ulResult;

    (VOS_VOID)DIAG_TraceReport(&stMntnInfo);

    return;
}


VOS_VOID R_ITF_TtfMemAllocEvent(VOS_UINT32 ulMemUsedCnt, VOS_UINT32 ulMemUsedSize)
{
    (VOS_VOID)R_ITF_SetFlowCtrl(R_ITF_FLOW_CTRL_TYPE_MEM_CNT, ulMemUsedCnt);
    (VOS_VOID)R_ITF_SetFlowCtrl(R_ITF_FLOW_CTRL_TYPE_MEM_SIZE, ulMemUsedSize);
} /* R_ITF_TtfMemAllocEvent */

VOS_VOID R_ITF_TtfMemFreeEvent(VOS_UINT32 ulMemUsedCnt, VOS_UINT32 ulMemUsedSize)
{
    (VOS_VOID)R_ITF_ClearFlowCtrl(R_ITF_FLOW_CTRL_TYPE_MEM_CNT, ulMemUsedCnt);
    (VOS_VOID)R_ITF_ClearFlowCtrl(R_ITF_FLOW_CTRL_TYPE_MEM_SIZE, ulMemUsedSize);
} /* R_ITF_TtfMemFreeEvent */


/*****************************************************************************
 �� �� ��  : R_ITF_StartFlowCtrl
 ��������  : ��������
 �������  : usMsgId - ��ϢID
 �������  : ��
 �� �� ֵ  : �����ɹ����, VOS_OK - �ɹ�, ���� - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 R_ITF_StartFlowCtrl(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    FC_SET_FLOWCTRL_IND_STRU           *pstFcSetInd;


    pstFcSetInd = (FC_SET_FLOWCTRL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_FLOWCTRL_C, sizeof(FC_SET_FLOWCTRL_IND_STRU));

    /* ������Ϣʧ�� */
    if (VOS_NULL_PTR == pstFcSetInd)
    {
        /* �澯��ӡ */
        (VOS_VOID)LogPrint("R_ITF_StartFlowCtrl, ERROR, alloc msg fail\r\n");
        return VOS_ERR;
    }

    /* ��д��Ϣ���� */
    pstFcSetInd->usMsgName          = ID_FC_SET_FLOWCTRL_IND;
    pstFcSetInd->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstFcSetInd->ulReceiverPid      = UEPS_PID_FLOWCTRL_A;
    pstFcSetInd->enRateMode         = enRateMode;

    /* ����Ϣ */
    PS_SEND_MSG(UEPS_PID_FLOWCTRL_C, pstFcSetInd);

    return VOS_OK;
}    /* R_ITF_StartFlowCtrl */

VOS_UINT32 R_ITF_FlowCtrlNotify(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    FC_FLOWCTRL_NOTIFY_STRU            *pstFcNotify;

    pstFcNotify = (FC_FLOWCTRL_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
        UEPS_PID_FLOWCTRL_C, sizeof(FC_FLOWCTRL_NOTIFY_STRU));

    /* ������Ϣʧ�� */
    if (VOS_NULL_PTR == pstFcNotify)
    {
        /* �澯��ӡ */
        (VOS_VOID)LogPrint("R_ITF_FlowCtrlNotify, ERROR, alloc msg fail\r\n");
        return VOS_ERR;
    }

    /* ��д��Ϣ���� */
    pstFcNotify->usMsgName              = ID_FC_C_FLOWCTRL_NOTIFY;
    pstFcNotify->enRateMode             = enRateMode;
    pstFcNotify->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstFcNotify->ulReceiverPid          = UEPS_PID_FLOWCTRL_C;


    /* ����Ϣ */
    PS_SEND_MSG(UEPS_PID_FLOWCTRL_C, pstFcNotify);

    return VOS_OK;

}


VOS_VOID R_ITF_UpdateFlowCtrlCnt(VOS_VOID)
{
    g_ulRItfFlowCtrlCnt++;
    return;
}


VOS_UINT32 R_Itf_FlowctrlGetStatCnt(VOS_UINT32 *pulFcStatCnt)
{
    *pulFcStatCnt = g_ulRItfFlowCtrlCnt;
    return VOS_OK;
}


VOS_UINT32 R_Itf_FlowctrlSetStatCnt(VOS_UINT32 pulFcStatCnt)
{
    g_ulRItfFlowCtrlCnt = pulFcStatCnt;
    return VOS_OK;
}



VOS_UINT32 R_ITF_FlowCtrlCntIsOverFlow(VOS_VOID)
{
    VOS_INT32               lLockKey;

    if (RITF_FLOWCTRL_WRED_THRESHOLD < g_ulRItfFlowCtrlCnt)
    {
        /* ���������ٽ��� */
        lLockKey            = VOS_SplIMP();

        g_ulRItfFlowCtrlCnt = 0;

        VOS_Splx(lLockKey);
        return VOS_YES;
    }

    return VOS_NO;
}

/*****************************************************************************
 �� �� ��  : R_ITF_StopFlowCtrl
 ��������  : ֹͣ����
 �������  : usMsgId - ��ϢID
 �������  : ��
 �� �� ֵ  : �����ɹ����, VOS_OK - �ɹ�, ���� - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 R_ITF_StopFlowCtrl(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    FC_STOP_FLOWCTRL_IND_STRU          *pstFcStopInd;

    pstFcStopInd = (FC_STOP_FLOWCTRL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
        UEPS_PID_FLOWCTRL_C, sizeof(FC_STOP_FLOWCTRL_IND_STRU));

    /* ������Ϣʧ�� */
    if (VOS_NULL_PTR == pstFcStopInd)
    {
        /* �澯��ӡ */
        (VOS_VOID)LogPrint("R_ITF_StopFlowCtrl, ERROR, alloc msg fail\r\n");
        return VOS_ERR;
    }

    /* ��д��Ϣ���� */
    pstFcStopInd->usMsgName         = ID_FC_STOP_FLOWCTRL_IND;

    pstFcStopInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFcStopInd->ulReceiverPid     = UEPS_PID_FLOWCTRL_A;
    pstFcStopInd->enRateMode        = enRateMode;


    /* ����Ϣ */
    PS_SEND_MSG(UEPS_PID_FLOWCTRL_C, pstFcStopInd);

    return VOS_OK;
}   /* FC_StopFlowCtrl */

#if 0
VOS_UINT32 R_ITF_ExcFlowCtrl
(
    R_ITF_FLOW_CTRL_CMD_ENUM_UINT32  ulFlowCtrlCmd,
    VOS_UINT32                       ulFlowCtrlType,
    VOS_UINT32                      *pulNeedTrace
)
{
    VOS_UINT32      ulResult = VOS_OK;

    if ( R_ITF_FLOW_CTRL_START == ulFlowCtrlCmd )
    {
        /* PS�ںϺ�, ����ֻ����ڴ�, �����������ȫ��ͳһ��FC�Ŀ���� */
        if ((R_ITF_FLOW_CTRL_TYPE_MEM_CNT == ulFlowCtrlType)
            || (R_ITF_FLOW_CTRL_TYPE_MEM_SIZE == ulFlowCtrlType))
        {
            ulResult        = R_ITF_StartFlowCtrl();    /* �������غ��� */
            *pulNeedTrace   = PS_TRUE;
        }
    }
    else if ( R_ITF_FLOW_CTRL_STOP == ulFlowCtrlCmd )
    {
        /* PS�ںϺ�, ����ֻ����ڴ�, �����������ȫ��ͳһ��FC�Ŀ���� */
        if ((R_ITF_FLOW_CTRL_TYPE_MEM_CNT == ulFlowCtrlType)
            || (R_ITF_FLOW_CTRL_TYPE_MEM_SIZE == ulFlowCtrlType))
        {
            ulResult        = R_ITF_StopFlowCtrl();    /* �������ؽ������ */
            *pulNeedTrace   = PS_TRUE;
        }
    }
    else
    {
        (VOS_VOID)LogPrint1("R_ITF_ExcFlowCtrl, WARNING, Unknow flow control command %u\r\n",
                  (VOS_INT32)ulFlowCtrlCmd);

        return VOS_ERR;
    }

    return ulResult;
}
#endif


VOS_UINT32 R_ITF_SetFlowCtrl
(
    VOS_UINT32                                  ulFlowCtrlType,
    VOS_UINT32                                  ulNewLev
)
{
    R_ITF_FLOW_LEV_STRU                 *pFlowLev;
    VOS_INT32                           lLockKey;
    VOS_UINT32                          ulOldMask;
    VOS_UINT32                          ulCurrTick;
    VOS_UINT32                          ulNeedExec;              /* �Ƿ���Ҫ�������ػ��߽�����ز��� */
    VOS_UINT32                          ulResult;                /* ����ִ�н�� */


    if (R_ITF_FLOW_CTRL_TYPE_BUTT <= ulFlowCtrlType)
    {
        return VOS_ERR;
    }

    /* ���������ٽ��� */
    lLockKey            = VOS_SplIMP();

    ulNeedExec          = PS_FALSE;
    ulResult            = VOS_OK;
    pFlowLev            = &g_stRItfFlowCtrl.astFlowCtrl[ulFlowCtrlType];
    ulCurrTick          = VOS_GetTick();

    if (pFlowLev->ulMaxLev < ulNewLev)
    {
        pFlowLev->ulMaxLev = ulNewLev;
    }

    /* ����ʵ���ﱣ��ĵ�ǰֵ��Ҫ�����Ᵽ�� */
    pFlowLev->ulCurrLev = ulNewLev;
    ulOldMask           = g_stRItfFlowCtrl.ulCtrlMask;

    /* ���ڽ�����״̬ʱ������ֵ, �������� */
    if (ulNewLev >= pFlowLev->ulWarningLev)
    {
        if (0 == ulOldMask)
        {
            ulNeedExec  = PS_TRUE;

            g_stRItfFlowCtrl.ulLastOptTick  = ulCurrTick;
            g_stRItfFlowCtrl.ulCtrlMask    |=  pFlowLev->ulMask;

            g_stRItfFlowCtrl.ulCtrlFlag     = R_ITF_FLOW_CTRL_START;
        }
    }

    /* �뿪�����ٽ��� */
    VOS_Splx(lLockKey);

    if (PS_TRUE == ulNeedExec)
    {
        /* �������غ��� */
        ulResult        = R_ITF_FlowCtrlNotify(g_stRItfFlowCtrl.enRateMode);

        R_ITF_UpdateFlowCtrlCnt();

        if (VOS_OK == ulResult)
        {
            /* �������ػ��߽�����ز�����ͬʱ, ���пɲ��ά */
            R_ITF_MntnFlowCtrlEvent(ulFlowCtrlType, ulNewLev, R_ITF_FLOW_CTRL_START, ulResult);
        }
    }

    return ulResult;
} /* R_ITF_SetFlowCtrl */

VOS_UINT32 R_ITF_ClearFlowCtrl(VOS_UINT32 ulFlowCtrlType, VOS_UINT32 ulNewLev)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;
    VOS_UINT32              ulCurrTick;
    VOS_UINT32              ulNeedExec;              /* �Ƿ���Ҫ�������ػ��߽�����ز��� */
    VOS_UINT32              ulResult;                /* ����ִ�н�� */
    VOS_UINT32              ulUpdatedMask;


    if (R_ITF_FLOW_CTRL_TYPE_BUTT <= ulFlowCtrlType)
    {
        return VOS_ERR;
    }

    /* ���������ٽ��� */
    lLockKey            = VOS_SplIMP();

    ulNeedExec          = PS_FALSE;
    ulResult            = VOS_OK;
    pFlowLev            = &g_stRItfFlowCtrl.astFlowCtrl[ulFlowCtrlType];
    ulCurrTick          = VOS_GetTick();

    /* ����ʵ���ﱣ��ĵ�ǰֵ��Ҫ�����Ᵽ�� */
    pFlowLev->ulCurrLev = ulNewLev;

    /* ��û����Ϊ�������͵�������, ���������� */
    if (0 == (g_stRItfFlowCtrl.ulCtrlMask & pFlowLev->ulMask))
    {
        VOS_Splx(lLockKey);
        return VOS_OK;
    }

    if (ulNewLev < pFlowLev->ulNormalLev)
    {
        if ((ulCurrTick - g_stRItfFlowCtrl.ulLastOptTick) >= g_ulRItfFlowCtrlProTime)
        {
            ulUpdatedMask = g_stRItfFlowCtrl.ulCtrlMask &  (~(pFlowLev->ulMask));

            /*�����������������������£�ִ�н�����ز���*/
            if ( 0 == ulUpdatedMask )
            {
                ulNeedExec      = PS_TRUE;

                g_stRItfFlowCtrl.ulLastOptTick = ulCurrTick;
                g_stRItfFlowCtrl.ulCtrlMask   &=  ~(pFlowLev->ulMask);

                g_stRItfFlowCtrl.ulCtrlFlag    = R_ITF_FLOW_CTRL_STOP;
            }
        }
    }

    /* �뿪�����ٽ��� */
    VOS_Splx(lLockKey);

    if (PS_TRUE == ulNeedExec)
    {
        /* �������ؽ������ */
        ulResult        = R_ITF_FlowCtrlNotify(g_stRItfFlowCtrl.enRateMode);

        if (VOS_OK == ulResult)
        {
            /*�����¼���ά�ɲ�*/
            R_ITF_MntnFlowCtrlEvent(ulFlowCtrlType, ulNewLev, R_ITF_FLOW_CTRL_STOP, ulResult);
        }
    }

    return ulResult;
} /* R_ITF_ClearFlowCtrl */



VOS_VOID R_ITF_SetLFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;

    /* PS�ںϺ�, Lģ��C����������A���Ͽ���, �����C���Ͻ����޸�Ϊ�����, �������������� */

    /* ���������ٽ��� */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 600;
    pFlowLev->ulWarningLev  = 1200;
    pFlowLev->ulMaxLev      = 0;

    if ( VOS_FALSE == g_ulLteFlowCtrl )
    {
        pFlowLev->ulWarningLev  = 0xffffffff;
        pFlowLev->ulNormalLev   = 0xffffffff;
    }

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 900000;
    pFlowLev->ulWarningLev  = 1800000;
    pFlowLev->ulMaxLev      = 0;

    g_stRItfFlowCtrl.enRateMode = VOS_RATMODE_LTE;

    if ( VOS_FALSE == g_ulLteFlowCtrl )
    {
        pFlowLev->ulWarningLev  = 0xffffffff;
        pFlowLev->ulNormalLev   = 0xffffffff;
    }

    /* �뿪�����ٽ��� */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* ��Lģ��, �ڴ���A�˼��, ���C���ϲ���Ҫ�ڴ��⹳�� */
    (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_DATA, VOS_NULL_PTR, VOS_NULL_PTR);

    return;
}



/******************************************************************************
 Prototype      : R_ITF_SetWFlowLev
 Description    : ҵ���л�ΪWģʱ��������������
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2009-02-27
    Author      : ����48156
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_SetWFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;


    /* PS�ںϺ�, Wģ��C����������A���Ͽ���, �����C���Ͻ����޸�Ϊ�����, �������������� */
    /* ���������ٽ��� */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 0xffffffff;/*1000*/
    pFlowLev->ulWarningLev  = 0xffffffff;/*2000*/
    pFlowLev->ulMaxLev      = 0;

    /* PS�ںϺ�, Wģ����ʹ��A���ڴ�, ��˽���������Ϊ�����, �����ڴ������� */
    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 0xffffffff;/*1200000*/
    pFlowLev->ulWarningLev  = 0xffffffff;/*2000000*/
    pFlowLev->ulMaxLev      = 0;

    g_stRItfFlowCtrl.enRateMode = VOS_RATMODE_WCDMA;

    /* �뿪�����ٽ��� */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* ��Wģ��, �ڴ���A�˼��, ���C���ϲ���Ҫ�ڴ��⹳�� */
    (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_DATA, VOS_NULL_PTR, VOS_NULL_PTR);

    return;
}


/******************************************************************************
 Prototype      : R_ITF_SetGFlowLev
 Description    : ҵ���л�ΪGģʱ��������������
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2009-02-27
    Author      : ����48156
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_SetGFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;


    /* ���������ٽ��� */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 600;
    pFlowLev->ulWarningLev  = 600;
    pFlowLev->ulMaxLev      = 0;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 30000;
    pFlowLev->ulWarningLev  = 30000;
    pFlowLev->ulMaxLev      = 0;

    g_stRItfFlowCtrl.enRateMode = VOS_RATMODE_GSM;

    /* �뿪�����ٽ��� */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* V9R1��ʹ������NV����GPRS����ʹ��λ���ж��Ƿ�ע�ṳ�Ӻ��� */
    if ( (FC_POLICY_MASK(FC_POLICY_ID_GPRS) == FC_POLICY_GetEnableMask(FC_POLICY_ID_GPRS) ))
    {
        /* ��Gģ��, A���ڴ���Ҫ������C��TTF_MEM��, ���C������Ҫ�ڴ��⹳�� */
        (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_DATA, R_ITF_TtfMemAllocEvent, R_ITF_TtfMemFreeEvent);
    }
    else
    {
        /* V9R1��ʹ�ú����жϣ������V9R1,��ע�ṳ�Ӻ��� */
        (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_DATA, VOS_NULL_PTR, VOS_NULL_PTR);
    }

    return;
}
VOS_VOID R_ITF_Set1XFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;

    /* ���������ٽ��� */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 300;
    pFlowLev->ulWarningLev  = 600;
    pFlowLev->ulMaxLev      = 0;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 121200;
    pFlowLev->ulWarningLev  = 900000;
    pFlowLev->ulMaxLev      = 0;

    g_stRItfFlowCtrl.enRateMode = VOS_RATMODE_1X;

    /* �뿪�����ٽ��� */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* V9R1��ʹ������NV����GPRS����ʹ��λ���ж��Ƿ�ע�ṳ�Ӻ��� */
    if ( (FC_POLICY_MASK(FC_POLICY_ID_CDMA) == FC_POLICY_GetEnableMask(FC_POLICY_ID_CDMA) ))
    {
        /* ��Xģ��, A���ڴ���Ҫ������C��TTF_MEM��, ���C������Ҫ�ڴ��⹳�� */
        (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_IP_DATA, R_ITF_TtfMemAllocEvent, R_ITF_TtfMemFreeEvent);
    }
    else
    {
        /* V9R1��ʹ�ú����жϣ������V9R1,��ע�ṳ�Ӻ��� */
        (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_IP_DATA, VOS_NULL_PTR, VOS_NULL_PTR);
    }

    return;
}
VOS_VOID R_ITF_SetHrpdFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;


    /* ���������ٽ��� */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 200;
    pFlowLev->ulWarningLev  = 500;
    pFlowLev->ulMaxLev      = 0;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 312000;
    pFlowLev->ulWarningLev  = 780000;
    pFlowLev->ulMaxLev      = 0;

    g_stRItfFlowCtrl.enRateMode = VOS_RATMODE_HRPD;

    /* �뿪�����ٽ��� */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* V9R1��ʹ������NV����GPRS����ʹ��λ���ж��Ƿ�ע�ṳ�Ӻ��� */
    if ( (FC_POLICY_MASK(FC_POLICY_ID_CDMA) == FC_POLICY_GetEnableMask(FC_POLICY_ID_CDMA) ))
    {
        /* ��Xģ��, A���ڴ���Ҫ������C��TTF_MEM��, ���C������Ҫ�ڴ��⹳�� */
        (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_IP_DATA, R_ITF_TtfMemAllocEvent, R_ITF_TtfMemFreeEvent);
    }
    else
    {
        /* V9R1��ʹ�ú����жϣ������V9R1,��ע�ṳ�Ӻ��� */
        (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_IP_DATA, VOS_NULL_PTR, VOS_NULL_PTR);
    }

    return;
}
VOS_VOID R_ITF_SetFlowLev
(
    VOS_RATMODE_ENUM_UINT32             enRateMode
)
{
    switch (enRateMode)
    {
        case VOS_RATMODE_GSM:

            R_ITF_SetGFlowLev(VOS_RATMODE_GSM);

            break;

        case VOS_RATMODE_WCDMA:

            R_ITF_SetWFlowLev(VOS_RATMODE_WCDMA);

            break;

        case VOS_RATMODE_LTE:

            R_ITF_SetLFlowLev(VOS_RATMODE_LTE);

            break;

        case VOS_RATMODE_1X:

            R_ITF_Set1XFlowLev(VOS_RATMODE_1X);

            break;

        case VOS_RATMODE_HRPD:

            R_ITF_SetHrpdFlowLev(VOS_RATMODE_HRPD);

            break;

        default:

            (VOS_VOID)LogPrint1("R_ITF_SetFlowLev, Invalid rate mode\r\n", (VOS_INT32)enRateMode);

            break;
    }

    return;
}/* R_ITF_SetFlowLev */

VOS_VOID R_ITF_InitFlowCtrl(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    R_ITF_FLOW_CTRL_CONFIG_STRU        *pstRItfFlowCtrlConfig;
    R_ITF_FLOW_LEV_STRU                *pFlowLev;

    pstRItfFlowCtrlConfig               = &g_stRItfFlowCtrlConfig;

    /*Read the NV Config Value*/
    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_RITF_FLOW_CTRL_Config, pstRItfFlowCtrlConfig, sizeof(R_ITF_FLOW_CTRL_CONFIG_STRU));

    /*Read NV Content is Failed , Configed the Vaule By Default Value*/
    if ( NV_OK != ulResult )
    {
        pstRItfFlowCtrlConfig->ulRateDismatchUsbEnable  = 1;
        pstRItfFlowCtrlConfig->ulRateDismatchWifiEnable = 0;
    }
    else
    {
        if ( 1 < pstRItfFlowCtrlConfig->ulRateDismatchUsbEnable )
        {
            pstRItfFlowCtrlConfig->ulRateDismatchUsbEnable  = 1;
        }

        if ( 1 < pstRItfFlowCtrlConfig->ulRateDismatchWifiEnable )
        {
            pstRItfFlowCtrlConfig->ulRateDismatchWifiEnable = 0;
        }
    }

    g_stRItfFlowCtrl.ulCtrlMask     = 0;
    g_stRItfFlowCtrl.ulLastOptTick  = 0;
    g_stRItfFlowCtrl.ulCtrlFlag     = R_ITF_FLOW_CTRL_STOP;;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulMask        = R_ITF_FLOW_CTRL_MASK_MEM_CNT;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulMask        = R_ITF_FLOW_CTRL_MASK_MEM_SIZE;

    R_ITF_SetWFlowLev(VOS_RATMODE_WCDMA);


} /* R_ITF_InitFlowCtrl */


/******************************************************************************
 Prototype      : R_ITF_RateDismatchUsbEnable
 Description    :
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2011-03-11
    Author      : hefeng
    Modification: Created function
******************************************************************************/
VOS_UINT32 R_ITF_RateDismatchUsbEnable(VOS_VOID)
{
    return g_stRItfFlowCtrlConfig.ulRateDismatchUsbEnable;
}


/******************************************************************************
 Prototype      : R_ITF_RateDismatchWifiEnable
 Description    :
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2011-03-11
    Author      : hefeng
    Modification: Created function
******************************************************************************/
VOS_UINT32 R_ITF_RateDismatchWifiEnable(VOS_VOID)
{
    return g_stRItfFlowCtrlConfig.ulRateDismatchWifiEnable;
}



VOS_VOID R_ITF_ResetMaxLev(VOS_VOID)
{
    VOS_UINT32  ulLoop;


    for (ulLoop = 0; ulLoop < R_ITF_FLOW_CTRL_TYPE_BUTT; ulLoop++)
    {
        g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulMaxLev   = 0;
    }
} /* R_ITF_ResetMaxLev */

VOS_VOID R_ITF_ResetFlowCtrl(VOS_VOID)
{
    VOS_UINT32  ulLoop;
    R_ITF_FLOW_LEV_STRU    *pFlowLev;


    for ( ulLoop = 0; ulLoop <= R_ITF_FLOW_CTRL_TYPE_MEM_SIZE; ++ulLoop )
    {
        pFlowLev = &g_stRItfFlowCtrl.astFlowCtrl[ulLoop];

        if ( pFlowLev->ulCurrLev >= pFlowLev->ulWarningLev )
        {
            (VOS_VOID)R_ITF_SetFlowCtrl(ulLoop, pFlowLev->ulCurrLev);
        }
        else
        {
            (VOS_VOID)R_ITF_ClearFlowCtrl(ulLoop, pFlowLev->ulCurrLev);
        }
    }

    return;

}

/* ��ʱ���Դ��룬�����ɼ�R�ӿ����صķ�ֵ������ֱ��ʹ���� vos_printf */

VOS_VOID R_ITF_Print(VOS_VOID)
{
    VOS_UINT32  ulLoop;


    (VOS_VOID)vos_printf("\r\n");

    for (ulLoop = 0; ulLoop < R_ITF_FLOW_CTRL_TYPE_BUTT; ulLoop++)
    {
        (VOS_VOID)vos_printf("Type:%u, MaxLev=%u, CurrLev=%u, ulWarningLev=%u, ulNormalLev=%u\r\n",
            ulLoop,
            g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulMaxLev,
            g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulCurrLev,
            g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulWarningLev,
            g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulNormalLev );
    }
} /* R_ITF_Print */
/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


