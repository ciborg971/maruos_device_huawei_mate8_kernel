

#if 0
#include "vos.h"
#include "SleepInit.h"
#include "sleepsleep.h"
#include "mdrv.h"
#include "OamSpecTaskDef.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if 0

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SLEEP_INIT_C


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

/*****************************************************************************
  2 ������������
*****************************************************************************/
extern VOS_VOID SLEEP_Init(VOS_VOID);
extern VOS_VOID SLEEP_SelfTask(VOS_VOID);


DRX_STATE_SLICE_STRU        *g_pstDrxStateSlice         = VOS_NULL_PTR;
LOWPOWER_STATE_STRU         *g_pstLowPowerState         = VOS_NULL_PTR;
HIFI_STATE_STRU             *g_pstHifiStateSlice        = VOS_NULL_PTR;
SLAVE_LOW_POWER_STATE_STRU  *g_pstSlaveLowPowerState    = VOS_NULL_PTR;

/*****************************************************************************
 �� �� ��  : WuepsSleepPidInit
 ��������  : SLEEP PID ��ʼ������
 �������  : enum VOS_INIT_PHASE_DEFINE ip
 �������  : ��
 �� �� ֵ  : VOS_UINT32 PID ��ʼ�����
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID Sleep_InitGlobal(VOS_VOID)
{
    VOS_UINT32 ulRecordAddr = VOS_NULL_PTR;

    SLEEP_Init();

    ulRecordAddr = DRV_EXCH_MEM_MALLOC(VOS_DUMP_MEM_TOTAL_SIZE);

    if (VOS_NULL_PTR != ulRecordAddr)
    {
        g_pstDrxStateSlice      = (DRX_STATE_SLICE_STRU*)ulRecordAddr;

        ulRecordAddr += ((PWC_COMM_MODE_GSM + 1)*sizeof(DRX_STATE_SLICE_STRU));

        g_pstLowPowerState      = (LOWPOWER_STATE_STRU*)ulRecordAddr;

        ulRecordAddr += sizeof(LOWPOWER_STATE_STRU);

        g_pstHifiStateSlice     = (HIFI_STATE_STRU*)ulRecordAddr;

        ulRecordAddr += sizeof(HIFI_STATE_STRU);

        g_pstSlaveLowPowerState = (SLAVE_LOW_POWER_STATE_STRU*)ulRecordAddr;
    }
    else
    {
        g_pstDrxStateSlice = (DRX_STATE_SLICE_STRU*)VOS_MemAlloc(WUEPS_PID_OM, STATIC_MEM_PT,
                ((PWC_COMM_MODE_GSM + 1)*sizeof(DRX_STATE_SLICE_STRU)));

        if (VOS_NULL_PTR == g_pstDrxStateSlice)
        {
            /*lint -e534*/
            LogPrint("Sleep_InitGlobal:VOS_MemAlloc DRX_STATE_SLICE_STRU Fail!\n");
            /*lint +e534*/
            return;
        }

        g_pstLowPowerState = (LOWPOWER_STATE_STRU*)VOS_MemAlloc(WUEPS_PID_OM, STATIC_MEM_PT,
                sizeof(LOWPOWER_STATE_STRU));

        if (VOS_NULL_PTR == g_pstLowPowerState)
        {
            /*lint -e534*/
            LogPrint("Sleep_InitGlobal:VOS_MemAlloc LOWPOWER_STATE_STRU Fail!\n");
            /*lint +e534*/
            return;
        }

        g_pstHifiStateSlice = (HIFI_STATE_STRU*)VOS_MemAlloc(WUEPS_PID_OM, STATIC_MEM_PT,
                sizeof(HIFI_STATE_STRU));

        if (VOS_NULL_PTR == g_pstHifiStateSlice)
        {
            /*lint -e534*/
            LogPrint("Sleep_InitGlobal:VOS_MemAlloc HIFI_STATE_STRU Fail!\n");
            /*lint +e534*/
            return;
        }

        g_pstSlaveLowPowerState = (SLAVE_LOW_POWER_STATE_STRU*)VOS_MemAlloc(WUEPS_PID_OM, STATIC_MEM_PT,
                sizeof(SLAVE_LOW_POWER_STATE_STRU));

        if (VOS_NULL_PTR == g_pstSlaveLowPowerState)
        {
            /*lint -e534*/
            LogPrint("Sleep_InitGlobal:VOS_MemAlloc SLAVE_LOW_POWER_STATE_STRU Fail!\n");
            /*lint +e534*/
            return;
        }
    }

    /*lint -e534*/
    VOS_MemSet(g_pstDrxStateSlice, 0, ((PWC_COMM_MODE_GSM + 1)*sizeof(DRX_STATE_SLICE_STRU)));
    VOS_MemSet(g_pstLowPowerState, 0, sizeof(LOWPOWER_STATE_STRU));
    VOS_MemSet(g_pstHifiStateSlice, 0, sizeof(HIFI_STATE_STRU));
    VOS_MemSet(g_pstSlaveLowPowerState, 0, sizeof(SLAVE_LOW_POWER_STATE_STRU));
    /*lint +e534*/

    return;
}

/*****************************************************************************
 �� �� ��  : WuepsSleepFidInit
 ��������  : SLEEP ģ�� FID �ĳ�ʼ������
 �������  : enum VOS_INIT_PHASE_DEFINE ip
 �������  : ��
 �� �� ֵ  : VOS_UINT32 FID ��ʼ�����
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32  Sleep_TaskInit(VOS_VOID)
{
    Sleep_InitGlobal();

    if (VOS_NULL_BYTE == VOS_RegisterSelfTaskPrio(WUEPS_FID_OM,
                                               (VOS_TASK_ENTRY_TYPE)SLEEP_SelfTask,
                                               SLEEP_SELFTASK_PRI, WSLEEP_TASK_STACK_SIZE ))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
