


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "CDS.h"
#include "QosFcCommon.h"
#include "QosFcStatus.h"
#include "QosFcRabStatus.h"
#include "QosFcChannelFlowCtrl.h"
#include "FcFlowCtrlMana.h"


/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_QOS_FC_STATUS_C
/*lint +e767*/

/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/
extern  FLOWCTRL_CDS_CONFIG_STRU        g_stFcCdsConfig;
VOS_VOID QosFc_FlowCtrlProc(VOS_UINT32 ulMemRemain, VOS_UINT32 *pRestoreCnt);
/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
QOS_FC_CONTROL_STRU g_stQosFcCtrl = {0};

/******************************************************************************
   5 ����ʵ��
******************************************************************************/

VOS_UINT32 QosFc_RestartCheckTmr(VOS_VOID)
{
    /*������*/
    if (VOS_NULL_PTR != g_stQosFcCtrl.hTimer)
    {
        (VOS_VOID)PS_STOP_REL_TIMER(&(g_stQosFcCtrl.hTimer));
    }

    if (VOS_OK != PS_START_REL_TIMER(&(g_stQosFcCtrl.hTimer),
                                    UEPS_PID_CDS,
                                    g_stQosFcCtrl.ulTimerLen,
                                    CDS_TMR_ID_FC_CHECK_TMR,
                                    0,
                                    VOS_RELTIMER_NOLOOP))
    {
        /*ERROR LOG*/
        CDS_ERROR_LOG(UEPS_PID_CDS,"QosFc_RestartCheckTmr : Fail to Start FC Tmr.");
        CDS_PRINT_ERROR(QosFc_RestartCheckTmr_ENUM,CDS_START_TIMER_ERROR);
        return PS_FAIL;
    }

    return PS_SUCC;
}


VOS_VOID QosFc_FlowCtrl(VOS_VOID)
{
    static VOS_UINT32 ulRestoreCnt = 0;
    VOS_UINT32 ulMemRemain;

    if(VOS_TRUE != g_stQosFcCtrl.bQosFcEnable)
    {
        /* ����û�򿪣���������״̬ */
        return;
    }

    ulMemRemain = TTF_GetUlIpFreeMemCnt();

    /* ���ٴ��� */
    if(g_stQosFcCtrl.ulRandomDiscardThres <= ulMemRemain)
    {
        if(QOS_FC_STATE_NORMAL == g_stQosFcCtrl.enFlowCtrl)
        {
            /* �����κ����ز��� */
            return;
        }
        else
        {
            /* ���ȼ�С��6�ĳ������Ȼָ��������� */
            if(PS_SUCC == QosFc_RestoreHighPriRab())
            {
                /* ��һ�����ش��� */
                (VOS_VOID)QosFc_RestartCheckTmr();
                return;
            }
        }
    }

    /*���ز���*/
    QosFc_FlowCtrlProc(ulMemRemain, &ulRestoreCnt);

    /* �˳�����״̬���������Լ�� */
    if(QOS_FC_STATE_FLOWCTRL == g_stQosFcCtrl.enFlowCtrl)
    {
        /* �������ؼ�鶨ʱ�� */
        (VOS_VOID)QosFc_RestartCheckTmr();
    }
    /* modify by jiqiang 2014.03.19 pclint begin */
    else
    {
    }
    /* modify by jiqiang 2014.03.19 pclint end */

    return;
}


VOS_VOID QosFc_FlowCtrlProc(VOS_UINT32 ulMemRemain, VOS_UINT32 *pRestoreCnt)
{
    /* ���ز��� */
    if (g_stQosFcCtrl.ulWarningThres > ulMemRemain)
    {
        (VOS_VOID)QosFc_DiscardAllDataFlow();
        g_stQosFcCtrl.enFlowCtrl = QOS_FC_STATE_FLOWCTRL;
        *pRestoreCnt = 0;
    }
    else if (g_stQosFcCtrl.ulDiscardThres > ulMemRemain)
    {
        (VOS_VOID)QosFc_DiscardDataFlow();
        g_stQosFcCtrl.enFlowCtrl = QOS_FC_STATE_FLOWCTRL;
        *pRestoreCnt = 0;
    }
    else if (g_stQosFcCtrl.ulRandomDiscardThres > ulMemRemain)
    {
        (VOS_VOID)QosFc_RandomDiscardDataFlow();
        g_stQosFcCtrl.enFlowCtrl = QOS_FC_STATE_FLOWCTRL;
        *pRestoreCnt = 0;
    }
    else if (g_stQosFcCtrl.ulRestoreThres < ulMemRemain)
    {
        if (QOS_FC_STATE_FLOWCTRL == g_stQosFcCtrl.enFlowCtrl)
        {
            (*pRestoreCnt)++;

            if (QOS_FC_SLOW_UP <= (*pRestoreCnt))
            {
                /*  ���ָ� */
                *pRestoreCnt = 0;
                if (PS_SUCC != QosFc_RestoreDataFlow())
                {
                    /* һ�����ع��̽��� */
                    g_stQosFcCtrl.enFlowCtrl = QOS_FC_STATE_NORMAL;
                }
            }
        }
    }
    /* modify by jiqiang 2014.03.19 pclint begin */
    else
    {
    }
    /* modify by jiqiang 2014.03.19 pclint end */
    return;
}
VOS_VOID QosFcCtrlInit(VOS_VOID)
{
    /* ����NV�����ƽṹ */
    if(0 == (QOS_FC_ENABLED_MASK & g_stFcCdsConfig.ulFcEnableMask))
    {
        g_stQosFcCtrl.bQosFcEnable = VOS_FALSE;
    }
    else
    {
        g_stQosFcCtrl.bQosFcEnable = VOS_TRUE;
    }

    if(0 == (QOS_FC_HIGHEST_FC_ENABLED_MASK & g_stFcCdsConfig.ulFcEnableMask))
    {
        g_stQosFcCtrl.bHighFcEnable = VOS_FALSE;
    }
    else
    {
        g_stQosFcCtrl.bHighFcEnable = VOS_TRUE;
    }

    if(0 == (QOS_FC_HIGHEST_NOTDISCARD_ENABLED_MASK & g_stFcCdsConfig.ulFcEnableMask))
    {
        g_stQosFcCtrl.bHighDiscardEnable = VOS_TRUE;
    }
    else
    {
        g_stQosFcCtrl.bHighDiscardEnable = VOS_FALSE;
    }

    g_stQosFcCtrl.hTimer = VOS_NULL_PTR;
    g_stQosFcCtrl.enFlowCtrl = QOS_FC_STATE_NORMAL;

    g_stQosFcCtrl.ulPktCntLimit = g_stFcCdsConfig.stQosFcConfig.ulPktCntLimit;
    g_stQosFcCtrl.ulTimerLen = g_stFcCdsConfig.stQosFcConfig.ulTimerLen;

    g_stQosFcCtrl.ulRandomDiscardRate = g_stFcCdsConfig.stQosFcConfig.ulRandomDiscardRate;
    g_stQosFcCtrl.ulDiscardRate = g_stFcCdsConfig.stQosFcConfig.ulDiscardRate;

    g_stQosFcCtrl.ulWarningThres = g_stFcCdsConfig.stQosFcConfig.ulWarningThres;
    g_stQosFcCtrl.ulDiscardThres = g_stFcCdsConfig.stQosFcConfig.ulDiscardThres;
    g_stQosFcCtrl.ulRandomDiscardThres = g_stFcCdsConfig.stQosFcConfig.ulRandomDiscardThres;
    g_stQosFcCtrl.ulRestoreThres = g_stFcCdsConfig.stQosFcConfig.ulRestoreThres;

    return;

}
VOS_VOID QosFc_Init(VOS_VOID)
{
    QosFcCtrlInit();    /* ��ʱ���ظ�ֵ������Ҫ��NV��ȡ */
    QosFcRabInit();
    QosFcChannelInit();

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



