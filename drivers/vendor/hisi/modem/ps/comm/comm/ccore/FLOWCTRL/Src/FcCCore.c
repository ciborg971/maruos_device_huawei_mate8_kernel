



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "Fc.h"
#include "FcInterface.h"
#include "FcIntraMsg.h"
#include "PsCommonDef.h"
#include "PsLib.h"
#include "OmApi.h"
#include "R_ITF_FlowCtrl.h"
#include "FcMacInterface.h"
#include "RabmInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e534*/
#define    THIS_FILE_ID        PS_FILE_ID_CCORE_FLOW_CTRL_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
VOS_UINT32                              g_ulFcUlRateCpu = FC_HSUPA_RATE_MAX_KBPS;
VOS_UINT32                              g_ulFcUlRateTmp = FC_HSUPA_RATE_MAX_KBPS;

FC_CPU_CTRL_STRU                        g_stFcCpuCCtrl;

FC_TRACE_CPULOAD_STRU                   g_stFcTraceCpuLoad  =
{
    FC_CCPU_TRACE_CPULOAD_TIMELEN,
    0,
    VOS_NULL_PTR
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : FC_UL_GetRate
 ��������  : ����HSUPA���з�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��5��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FC_UL_GetRate( VOS_VOID )
{
    /* �������з����������� = MIN(CPU���ʣ��±�����) */
    return PS_MIN(g_ulFcUlRateCpu*1024, g_ulFcUlRateTmp*1024);
}


/*****************************************************************************
 �� �� ��  : FC_UL_UpRateLimit
 ��������  : ��ǿHSUPA���з����������ƣ����ͷ�������
 �������  : ulSndRate    --  �������ʰٷֱ�
             ulPolicyMask --  ���ز�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��5��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FC_UL_UpRateLimit( VOS_UINT32 ulUlRate, VOS_UINT32 ulPolicyId )
{
    VOS_UINT32                          ulRateLimit;


    /* ǰ16λ��¼��ǰ��λ�����ذٷֱȣ����������� */
    ulRateLimit = ulUlRate >> 16;

    if ( FC_POLICY_MASK_CPU_C == FC_POLICY_MASK(ulPolicyId))
    {
        g_ulFcUlRateCpu = ulRateLimit;
    }
    else if ( FC_POLICY_MASK_TMP == FC_POLICY_MASK(ulPolicyId))
    {
        g_ulFcUlRateTmp = ulRateLimit;
    }
    else
    {
        FC_LOG1(PS_PRINT_WARNING,
                "FC_UL_UpRateLimit, ERROR, Invalid ulPolicyId %d\n",
                (VOS_INT32)ulPolicyId);
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : FC_UL_DownRateLimit
 ��������  : ����HSUPA���з����������ƣ���߷�������
 �������  : ulSndRate    --  �������ʰٷֱ�
             ulPolicyMask --  ���ز�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��5��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FC_UL_DownRateLimit( VOS_UINT32 ulUlRate, VOS_UINT32 ulPolicyId )
{
    VOS_UINT32                          ulRateLimit;


    /* ��16λ��¼��һ�������ȼ���λ�����ذٷֱȣ����ڽ����� */
    ulRateLimit = ulUlRate & FC_DOWN_RATE_LIMIT_MASK;

    if ( FC_POLICY_MASK_CPU_C == FC_POLICY_MASK(ulPolicyId))
    {
        g_ulFcUlRateCpu = ulRateLimit;
    }
    else if ( FC_POLICY_MASK_TMP == FC_POLICY_MASK(ulPolicyId))
    {
        g_ulFcUlRateTmp = ulRateLimit;
    }
    else
    {
        FC_LOG1(PS_PRINT_WARNING,
                "FC_UL_DownRateLimit, ERROR, Invalid ulPolicyId %d\n",
                (VOS_INT32)ulPolicyId);
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : FC_UL_InitFcPoints
 ��������  : ����HSUPA���з�������
 �������  : ucPolicyId --  ����ID
             pstUlFcCfg --  ������������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��5��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FC_UL_InitFcPoints
(
    FC_POLICY_ID_ENUM_UINT8             enPolicyId,
    FC_CFG_UM_UL_RATE_STRU             *pstUlFcCfg
)
{
    FC_REG_POINT_STRU                   stFcRegPoint;
    VOS_UINT32                          ulRateLoop;
    VOS_UINT16                          usCurrRate;
    VOS_UINT16                          usPrevRate = FC_HSUPA_RATE_MAX_KBPS;
    FC_ID_ENUM_UINT8                    enFcId;
    FC_PRI_ENUM_UINT8                   enPri = FC_PRI_LOWEST;

    if (FC_POLICY_ID_CPU_C == enPolicyId)
    {
        enFcId = FC_ID_UL_RATE_1_FOR_CPU;
    }
    else if (FC_POLICY_ID_TMP == enPolicyId)
    {
        enFcId = FC_ID_UL_RATE_1_FOR_TMP;
    }
    /* Ŀǰ��ֻ���CCPU��TMP�ṩ�˰���λ�����ʹ��ܣ�������������ʹ�� */
    else
    {
        FC_LOG1(PS_PRINT_WARNING,
                "FC_UL_InitFcPoints, ERROR, wrong ulPolicyId %d\n",
                (VOS_INT32)enPolicyId);

        return VOS_ERR;
    }

    /* NV����CCPU��TMP�ĵ�λԤ�������11�����������ȼ����ΪFC_PRI_9������ʹ�õ�λʱֻ��ǰ9����Ч */
    for ( ulRateLoop = 0 ; ulRateLoop < pstUlFcCfg->ucRateCnt ; ulRateLoop++ )
    {
        usCurrRate = pstUlFcCfg->ausRate[ulRateLoop];

        stFcRegPoint.enPolicyId = enPolicyId;
        stFcRegPoint.enFcPri    = enPri;
        stFcRegPoint.enFcId     = enFcId;
        stFcRegPoint.enModemId  = MODEM_ID_0;

        /* ������ʱ������������Ϊ��һ�� */
        stFcRegPoint.ulParam1   = (((VOS_UINT32)usCurrRate) << 16) | (((VOS_UINT32)usPrevRate) & FC_DOWN_RATE_LIMIT_MASK);
        stFcRegPoint.ulParam2   = enPolicyId;
        stFcRegPoint.pSetFunc   = (FC_SET_FUNC)FC_UL_UpRateLimit;
        stFcRegPoint.pClrFunc   = (FC_CLR_FUNC)FC_UL_DownRateLimit;
        stFcRegPoint.pRstFunc   = VOS_NULL_PTR;

        FC_POINT_Reg(&stFcRegPoint);

        enFcId++;

        if ( FC_PRI_HIGHEST == enPri )
        {
            break;
        }

        enPri++;
        usPrevRate = usCurrRate;

    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : FC_CPUC_UpJudge
 ��������  : ���˹���CPU���ش���ӿ�
 �������  : ulCpuIdleValue  --  ��ǰCPU������0~100
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��5��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FC_CPUC_UpJudge
(
    VOS_UINT32       ulCpuLoad,
    FC_CFG_CPU_STRU *pstFcCfgCpu,
    FC_POLICY_STRU  *pstFcPolicy
)
{
    if ( ulCpuLoad < pstFcCfgCpu->ulCpuOverLoadVal )
    {
        g_stFcCpuCCtrl.ulSmoothTimerLen =0;
        return VOS_FALSE;
    }

    if (pstFcPolicy->enHighestPri <= pstFcPolicy->enDonePri)
    {
        return VOS_FALSE;
    }

    if ( FC_PRI_NULL != pstFcPolicy->enDonePri )
    {
        return VOS_TRUE;
    }


    /*================================*//* ����һ��������ʱ����ƽ������  */
    g_stFcCpuCCtrl.ulSmoothTimerLen++;

    if (g_stFcCpuCCtrl.ulSmoothTimerLen < pstFcCfgCpu->ulSmoothTimerLen)
    {
        return VOS_FALSE;
    }

    g_stFcCpuCCtrl.ulSmoothTimerLen  = 0;

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : FC_CPUC_DownJudge
 ��������  : ���˹���CPU���ش���ӿ�
 �������  : ulCpuIdleValue  --  ��ǰCPU������0~100
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��5��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FC_CPUC_DownJudge
(
    VOS_UINT32       ulCpuLoad,
    FC_CFG_CPU_STRU *pstFcCfgCpu,
    FC_POLICY_STRU  *pstFcPolicy
)
{

    if ( (ulCpuLoad < pstFcCfgCpu->ulCpuUnderLoadVal)
         && (FC_PRI_NULL < pstFcPolicy->enDonePri) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32  FC_CPUC_UpProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pFcPolicy;


    /*================================*//* ��ȡCPU���ز���ʵ�壬������ͨ�����ز��� */
    pFcPolicy   = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CPU_C_MODEM_0);
    FC_POLICY_Up(pFcPolicy);

    return VOS_OK;
}
VOS_UINT32  FC_CPUC_DownProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pPolicy;


    /*================================*//* ��ȡCPU���ز���ʵ�壬������ͨ�����ز��� */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CPU_C_MODEM_0);
    FC_POLICY_Down(pPolicy);

    return VOS_OK;
}
VOS_VOID FC_FcNotifyProcess(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    /* ���ݵ�ǰ��������״̬��ͣ���� */
    if (R_ITF_FLOW_CTRL_START == g_stRItfFlowCtrl.ulCtrlFlag)
    {
        R_ITF_StartFlowCtrl(enRateMode);
    }
    else
    {
        R_ITF_StopFlowCtrl(enRateMode);
    }
}
VOS_UINT32  FC_CPUC_Init( VOS_VOID )
{
    VOS_UINT32                          ulResult;


    ulResult = FC_UL_InitFcPoints(FC_POLICY_ID_CPU_C, &(g_stFcCfg.stFcCfgUmUlRateForCpu));

    if ( VOS_OK != ulResult )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_Init, ERROR, Fail to init FC Points for CPU!\n");
        return VOS_ERR;
    }

    VOS_MemSet(&g_stFcCpuCCtrl, 0, sizeof(g_stFcCpuCCtrl));

    ulResult = VOS_StartRelTimer(&g_stFcTraceCpuLoad.pstTraceCpuLoadTHandle, UEPS_PID_FLOWCTRL_C,
                                  g_stFcTraceCpuLoad.ulTraceCpuLoadTimerLen,
                                  TIMER_FC_CCPU_TRACE_CPULOAD, 0,
                                  VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
    if (VOS_OK != ulResult)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_Init, ERROR, Fail to Start Timer!\n");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : FC_CPU_Process
 ��������  : C������ģ���ṩ��CPU���ش���ӿڣ��ú���Ŀǰ���ж��е��ã������������Բ���
 �������  : ulCpuLoad  --  ��ǰCPUռ����0~100
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��5��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FC_CPU_Process( VOS_UINT32 ulCpuLoad )
{
    FC_CFG_CPU_STRU                    *pstFcCfgCpu;
    FC_POLICY_STRU                     *pstFcPolicy;
    VOS_UINT32                          ulStartCtrl;


    /*====================================*//* ʹ�ܼ�� */
    if ( FC_POLICY_MASK_CPU_C != (FC_POLICY_MASK_CPU_C & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* CPU����δʹ�ܣ����ж��б����ã���ʹ��LogPrint */
        (VOS_VOID)LogPrint1("FC_CPU_Process, INFO, CPU FlowCtrl is disabled %d.\r\n", (VOS_INT32)g_stFcCfg.ulFcEnbaleMask );
        return 0;
    }

    /*================================*//* ������� */
    if ( 100 < ulCpuLoad )
    {
        /* �����Ƿ������ж��б����ã���ʹ��LogPrint */
        (VOS_VOID)LogPrint1("FC_CPU_Process, WARNING, Invalid Cpu Load %d.\r\n", (VOS_INT32)ulCpuLoad);
        return 0;
    }

    /* ��¼CPU�������ݵ�ȫ�ֱ����� */
    g_stFcTraceCpuLoad.ulCpuLoadRecord   = ulCpuLoad;

    pstFcPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CPU_C_MODEM_0);
    pstFcCfgCpu = &(g_stFcCfg.stFcCfgCpuC);

    /*================================*//* �Ƿ�Ҫ����CPU���� */
    ulStartCtrl = FC_CPUC_UpJudge(ulCpuLoad, pstFcCfgCpu, pstFcPolicy);
    if (VOS_TRUE == ulStartCtrl)
    {
        FC_SndCpuMsg(ID_FC_CPU_C_OVERLOAD_IND, ulCpuLoad, 0, 0);

        /* ����ģʽ�£������������� */
        NAS_RABM_SetTcFlowCtrl();

        return 0;
    }

    /*================================*//* ����CPU�������о� */
    ulStartCtrl = FC_CPUC_DownJudge(ulCpuLoad, pstFcCfgCpu, pstFcPolicy);
    if ( VOS_TRUE ==  ulStartCtrl )
    {
        FC_SndCpuMsg(ID_FC_CPU_C_UNDERLOAD_IND, ulCpuLoad, 0, 0);

        /* ����ģʽ�£�ֹͣ�������� */
        NAS_RABM_ClearTcFlowCtrl();

        return 0;
    }

    if ( ulCpuLoad <= pstFcCfgCpu->ulCpuOverLoadVal )
    {
        /* ����ģʽ�£�ֹͣ�������� */
        NAS_RABM_ClearTcFlowCtrl();
    }

    return 0;
}



VOS_UINT32  FC_TEMPERATURE_UpProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pstFcPolicy;


    /*================================*//* ��ȡCPU���ز���ʵ�壬������ͨ�����ز��� */
    pstFcPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_TMP_MODEM_0);
    FC_POLICY_Up(pstFcPolicy);

    return VOS_OK;
}
VOS_UINT32  FC_TEMPERATURE_DownProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pPolicy;


    /*================================*//* ��ȡCPU���ز���ʵ�壬������ͨ�����ز��� */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_TMP_MODEM_0);
    FC_POLICY_Down(pPolicy);

    return VOS_OK;
}
VOS_UINT32  FC_TEMPERATURE_RecoverProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pPolicy;


    /*================================*//* ��ȡCPU���ز���ʵ�壬������ͨ�����ز��� */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_TMP_MODEM_0);
    FC_POLICY_DownToTargetPri(pPolicy, FC_PRI_NULL);

    return VOS_OK;
}
VOS_UINT32 FC_TEMPERATURE_SndCtrlMsg
(
    FC_MSG_TYPE_ENUM_UINT16 usMsgName
)
{
    VOS_UINT32                          ulResult;
    FC_TEMPERATURE_IND_STRU            *pstMsg;


    pstMsg = (FC_TEMPERATURE_IND_STRU *)VOS_AllocMsg(UEPS_PID_FLOWCTRL, \
                                        sizeof(FC_TEMPERATURE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_SndIntraTemperatureMsg, Alloc Msg Fail\n");
        return VOS_ERR;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL;
    pstMsg->usMsgName       = usMsgName;

    ulResult = VOS_SendMsg(UEPS_PID_FLOWCTRL, pstMsg);

    if (VOS_OK != ulResult)
    {
        FC_LOG(PS_PRINT_ERROR,"FC_SndIntraTemperatureMsg, Send Msg Fail\n");
        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_UINT32  FC_TEMPERATURE_Init( VOS_VOID )
{
    VOS_UINT32                          ulResult;


    /* �����±����ص�ʵ�� */
    ulResult = FC_UL_InitFcPoints(FC_POLICY_ID_TMP, &(g_stFcCfg.stFcCfgUmUlRateForTmp));

    return ulResult;
}


/*****************************************************************************
 �� �� ��  : FC_DownUlGradeProcess
 ��������  : OM�¿�ģ���⵽�¶ȹ�����Ҫ����ʱ������ע��Ĺ��½��ٴ���API�����ټ����ġ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : OM_DATA_DOWMGRADE_CONTINUE --  ���Լ�����
             OM_DATA_DOWNGRADE_FINISH   --  ���ܼ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��5��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32 FC_DownUlGradeProcess(VOS_VOID)
{
    FC_POLICY_STRU                     *pstFcPolicy;

    if ( FC_POLICY_MASK_TMP != (FC_POLICY_MASK_TMP & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* �¿�δʹ�� */
        FC_LOG1(PS_PRINT_INFO, "FC_DownUlGradeProcess, INFO, TMP FlowCtrl is disabled %d\n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return SPY_DATA_DOWNGRADE_FINISH;
    }

    pstFcPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_TMP_MODEM_0);

    if ( pstFcPolicy->enHighestPri <= pstFcPolicy->enDonePri )
    {
        /* �Ѿ��ﵽ������߼����޷�����ִ������ */
        return SPY_DATA_DOWNGRADE_FINISH;
    }

    (VOS_VOID)FC_TEMPERATURE_SndCtrlMsg(ID_FC_TEMPERATURE_OVERLOAD_IND);

    return SPY_DATA_DOWNGRADE_CONTINUE;
}


/*****************************************************************************
 �� �� ��  : FC_UpUlGradeProcess
 ��������  : OM�¿�ģ���⵽�¶Ȼָ���������ʱ������ע������ٴ���API
 �������  : ��
 �������  : ��
 �� �� ֵ  : OM_DATA_DOWMGRADE_CONTINUE --  ���Լ�����
             OM_DATA_DOWNGRADE_FINISH   --  ���ܼ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��5��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
SPY_DATA_UPGRADE_RESULT_ENUM_UINT32 FC_UpUlGradeProcess(VOS_VOID)
{
    FC_POLICY_STRU                     *pstFcPolicy;

    if ( FC_POLICY_MASK_TMP != (FC_POLICY_MASK_TMP & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* �¿�δʹ�� */
        FC_LOG1(PS_PRINT_INFO, "FC_UpUlGradeProcess, INFO, TMP FlowCtrl is disabled %d\n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return SPY_DATA_UPGRADE_FINISH;
    }

    pstFcPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_TMP_MODEM_0);

    if ( FC_PRI_NULL == pstFcPolicy->enDonePri )
    {
        /* �Ѿ��ﵽ������ͼ����޷����������� */
        return SPY_DATA_UPGRADE_FINISH;
    }

    (VOS_VOID)FC_TEMPERATURE_SndCtrlMsg(ID_FC_TEMPERATURE_UNDERLOAD_IND);

    return SPY_DATA_UPGRADE_CONTINUE;
}


/*****************************************************************************
 �� �� ��  : FC_RecoverUlGradeProcess
 ��������  : �ָ��������ʣ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��18��
    ��    ��   : FC_RecoverUlGradeProcess
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  FC_RecoverUlGradeProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pstFcPolicy;


    if ( FC_POLICY_MASK_TMP != (FC_POLICY_MASK_TMP & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* �¿�δʹ�� */
        FC_LOG1(PS_PRINT_INFO, "FC_RecoverUlGradeProcess, INFO, TMP FlowCtrl is disabled %d\n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return;
    }

    pstFcPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_TMP_MODEM_0);

    if ( FC_PRI_NULL == pstFcPolicy->enDonePri )
    {
        /* �Ѿ��ָ��������ٴ��� */
        return;
    }

    (VOS_VOID)FC_TEMPERATURE_SndCtrlMsg(ID_FC_TEMPERATURE_RECOVER_IND);

    return;
}



VOS_UINT32  FC_CCORE_RcvIntraMsg( MsgBlock * pMsg )
{
    switch( FC_GET_MSG_NAME16(pMsg) )
    {
        case ID_FC_REG_POINT_IND:
            FC_POINT_Reg( &(((FC_REG_POINT_IND_STRU *)pMsg)->stFcPoint) );
            break;

        case ID_FC_DEREG_POINT_IND:
            FC_POINT_DeReg( ((FC_DEREG_POINT_IND_STRU *)pMsg)->enFcId,
                            ((FC_DEREG_POINT_IND_STRU *)pMsg)->enModemId );
            break;

        case ID_FC_CHANGE_POINT_IND:
            /* add by wangrong */
            FC_POINT_Change( ((FC_CHANGE_POINT_IND_STRU *)pMsg)->enFcId,
                             ((FC_CHANGE_POINT_IND_STRU *)pMsg)->enPolicyId,
                             ((FC_CHANGE_POINT_IND_STRU *)pMsg)->enPri,
                             ((FC_CHANGE_POINT_IND_STRU *)pMsg)->enModemId);
            /* add by wangrong */
            break;

        case ID_FC_TEMPERATURE_OVERLOAD_IND:
            FC_TEMPERATURE_UpProcess();
            break;

        case ID_FC_TEMPERATURE_UNDERLOAD_IND:
            FC_TEMPERATURE_DownProcess();
            break;

        case ID_FC_TEMPERATURE_RECOVER_IND:
            FC_TEMPERATURE_RecoverProcess();
            break;

        case ID_FC_CPU_C_OVERLOAD_IND:
            FC_CPUC_UpProcess();
            break;

        case ID_FC_CPU_C_UNDERLOAD_IND:
            FC_CPUC_DownProcess();
            break;

        case ID_FC_C_FLOWCTRL_NOTIFY:
            FC_FcNotifyProcess(((FC_FLOWCTRL_NOTIFY_STRU *)pMsg)->enRateMode);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : FC_CCORE_RcvTimerExpireMsg
 ��������  : ���ն�ʱ����Ϣ�ķַ�����
 �������  : REL_TIMER_MSG *pTimerMsg
 �������  : ��
 �� �� ֵ  : ��
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��21��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID FC_CCORE_RcvTimerExpireMsg(REL_TIMER_MSG *pTimerMsg)
{
    VOS_UINT32                          ulResult;


    switch (pTimerMsg->ulName)
    {
        case TIMER_FC_CCPU_TRACE_CPULOAD:
            /*====================================*//* �����ά�ɲ� */
            FC_MNTN_TraceCpuLoad(ID_FC_MNTN_CPU_C_CPULOAD, g_stFcTraceCpuLoad.ulCpuLoadRecord);

            /* ������ʱ�� */
            ulResult = VOS_StartRelTimer(&g_stFcTraceCpuLoad.pstTraceCpuLoadTHandle, UEPS_PID_FLOWCTRL_C,
                                          g_stFcTraceCpuLoad.ulTraceCpuLoadTimerLen,
                                          TIMER_FC_CCPU_TRACE_CPULOAD, 0,
                                          VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
            if (VOS_OK != ulResult)
            {
                FC_LOG2(PS_PRINT_ERROR, "FC_Init, ERROR, Fail to Start Timer! ulResult = %d, ulTraceCpuLoadTimerLen = %d\n", (VOS_INT32)ulResult, (VOS_INT32)g_stFcTraceCpuLoad.ulTraceCpuLoadTimerLen);
                return;
            }

            break;

        default:
            break;
    }

    return;
}


VOS_UINT32  FC_CCORE_MsgProc( MsgBlock * pMsg )
{
    switch (pMsg->ulSenderPid)
    {
        case UEPS_PID_FLOWCTRL_C:
            FC_CCORE_RcvIntraMsg(pMsg);
            break;

        case VOS_PID_TIMER:
            FC_CCORE_RcvTimerExpireMsg( (REL_TIMER_MSG *)pMsg );
            break;

        default:
            break;
    }

    return VOS_OK;
} /* FC_MsgProc */

VOS_UINT32  FC_CCORE_Init( VOS_VOID )
{
    VOS_UINT32                          ulResult;


    ulResult = FC_CommInit();

    if ( VOS_OK != ulResult )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_Init, ERROR, FC_CommInit return error!\n");
        return VOS_ERR;
    }

    ulResult    = FC_CPUC_Init();
    if ( VOS_OK != ulResult )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_Init, ERROR, FC_CPUC_Init error!\n");
        return VOS_ERR;
    }

    ulResult    = FC_TEMPERATURE_Init();
    if ( VOS_OK != ulResult )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_Init, ERROR, FC_TEMPERATURE_Init error!\n");
        return VOS_ERR;
    }

    /* �ҽ� UL_DATA_POOL �ڴ�صļ�⺯�� */
    R_ITF_InitFlowCtrl();

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : FC_FidInit
 ��������  : ����FID��ʼ������
 �������  : enum VOS_INIT_PHASE_DEFINE enPhase
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��14��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 FC_CCORE_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    VOS_UINT32  ulResult = VOS_ERR;

    switch (enPhase)
    {
        case   VOS_IP_LOAD_CONFIG:

            ulResult = VOS_RegisterPIDInfo(UEPS_PID_FLOWCTRL,
                                           (Init_Fun_Type)VOS_NULL_PTR,
                                           (Msg_Fun_Type)FC_CCORE_MsgProc);
            if (VOS_OK != ulResult)
            {
                FC_LOG(PS_PRINT_ERROR, "FC_FidInit, VOS_RegisterPIDInfo Fail\n");
                return VOS_ERR;
            }

            ulResult = VOS_RegisterTaskPrio(UEPS_FID_FLOWCTRL, TTF_FLOW_CTRL_TASK_PRIO);

            if (VOS_OK != ulResult)
            {
                FC_LOG(PS_PRINT_ERROR, "FC_FidInit, OS_RegisterTaskPrio Fail\n");
                return VOS_ERR;
            }

            ulResult = FC_CCORE_Init();

            if (VOS_OK != ulResult)
            {
                FC_LOG(PS_PRINT_ERROR, "FC_FidInit, Call FC_Init return error!\n");
                return VOS_ERR;
            }

            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
            break;
        default:
            break;
    }

    return VOS_OK;
}
/*lint -restore */
/*lint +e534*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

