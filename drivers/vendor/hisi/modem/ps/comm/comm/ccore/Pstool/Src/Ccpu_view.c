

/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "cpu_view_interface.h"
#include "mdrv.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(760)*/
#define    THIS_FILE_ID        PS_FILE_ID_CPU_VIEW_C

/******************************************************************************
   2 ��������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
CPU_VIEW_CTRL_STRU     *g_pstCpuViewCtrl;
VOS_UINT32              g_ulCpuViewInitFlag     = CPU_VIEW_NO;
VOS_UINT32              g_ulCpuViewStartFlag    = CPU_VIEW_NO;
VOS_UINT32              g_ulPointWatch          = CPU_VIEW_NO;
VOS_UINT32              g_ulTaskWatch           = CPU_VIEW_NO;
VOS_UINT32              g_ulFuncWatch           = CPU_VIEW_NO;


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/*lint -save -e958 */
/*lint -save -e534 */

VOS_UINT32 CpuView_GetTaskName(VOS_VOID)
{
    VOS_UINT32                  ulloop;
    CPU_TASK_NAME_STRU         *pTaskName;
    int                         lTaskNumber;
    int                         alVxWorks_TID_list[CPU_VIEW_MAX_TASK_NUMBER];
    char                       *pcTaskName;

    lTaskNumber = OS_GetTaskIdList( alVxWorks_TID_list, CPU_VIEW_MAX_TASK_NUMBER );
    if (( 0 >= lTaskNumber ) || (CPU_VIEW_MAX_TASK_NUMBER < lTaskNumber))
    {
        CPU_VIEW_LOG_PRINT1("CpuView_GetTaskName fail.TaskNumber outof range:%d\r\n", lTaskNumber);
        return VOS_ERR;
    }

    memset((void *)g_astCpuTaskName, 0, sizeof(CPU_TASK_NAME_STRU) * CPU_VIEW_MAX_TASK_NUMBER);

    for ( ulloop = 0; ulloop < (VOS_UINT32)lTaskNumber; ulloop++ )
    {
        pTaskName       = &g_astCpuTaskName[ulloop];
        pTaskName->pTcb = (CPUVIEW_TCB *)alVxWorks_TID_list[ulloop];
        pcTaskName      = OS_GetTaskName((VOS_UINT32)alVxWorks_TID_list[ulloop]);

        if (VOS_NULL_PTR != pcTaskName)
        {
            strncpy(pTaskName->aucTaskName, pcTaskName, CPU_VIEW_TASK_NAME_LEN);
        }
    }

    g_ulTaskNumber  = (VOS_UINT32)lTaskNumber;

    return VOS_OK;
} /* CpuView_GetTaskName */

VOS_UINT32 CpuView_IsOverturn(VOS_VOID)
{
    if (g_ulCpuViewTraceCnt == g_ulCpuViewCnt)
    {
        g_ulCpuViewOC = CPU_VIEW_RECORD_OVERTURN_YES;

        if (CPU_VIEW_RECORD_MODE_CYCLE_NO == g_ulCpuViewMode)
        {
            return CPU_VIEW_YES;
        }
        else
        {
            g_ulCpuViewCnt = 0;
        }
    }

    return CPU_VIEW_NO;
} /* CpuView_IsOverturn */

VOS_VOID CpuView_TaskSwitchHook(CPUVIEW_TCB *pOldTcb, CPUVIEW_TCB *pNewTcb)
{
    VOS_INT32           lLockValue;
    VOS_UINT32          ulCurrentSlice;

    if (CPU_VIEW_NO == g_ulTaskWatch)
    {
        return;
    }

    lLockValue      = VOS_SplIMP();

    if (CPU_VIEW_YES == CpuView_IsOverturn())
    {
        VOS_Splx(lLockValue);
        return;
    }

    /* get current time */
    ulCurrentSlice = mdrv_timer_get_hrt_timestamp();

    g_pstCpuView[g_ulCpuViewCnt].ulId       = (VOS_UINT32)pOldTcb;
    g_pstCpuView[g_ulCpuViewCnt].ucType     = CPU_VIEW_TYPE_TASK;
    g_pstCpuView[g_ulCpuViewCnt].ucLev      = CPU_VIEW_LEV_EXIT;
    g_pstCpuView[g_ulCpuViewCnt].ulSlice    = ulCurrentSlice;
    g_pstCpuView[g_ulCpuViewCnt].ulTick     = CPU_VIEW_GET_TICK();
    g_pstCpuView[g_ulCpuViewCnt].ulPC       = (VOS_UINT32)CPU_VIEW_GET_TASK_PC(pOldTcb);
    g_pstCpuView[g_ulCpuViewCnt].ulPara1    = 0;
    g_ulCpuViewCnt++;

    if (CPU_VIEW_YES == CpuView_IsOverturn())
    {
        VOS_Splx(lLockValue);
        return;
    }

    g_pstCpuView[g_ulCpuViewCnt].ulId       = (VOS_UINT32)pNewTcb;
    g_pstCpuView[g_ulCpuViewCnt].ucType     = CPU_VIEW_TYPE_TASK;
    g_pstCpuView[g_ulCpuViewCnt].ucLev      = CPU_VIEW_LEV_ENTRY;
    g_pstCpuView[g_ulCpuViewCnt].ulSlice    = ulCurrentSlice;
    g_pstCpuView[g_ulCpuViewCnt].ulTick     = CPU_VIEW_GET_TICK();
    g_pstCpuView[g_ulCpuViewCnt].ulPC       = (VOS_UINT32)CPU_VIEW_GET_TASK_PC(pNewTcb);
    g_pstCpuView[g_ulCpuViewCnt].ulPara1    = 0;
    g_ulCpuViewCnt++;

    VOS_Splx(lLockValue);

    return;
} /* CpuView_TaskSwitchHook */


VOS_VOID CpuView_IntLevChgInHook(VOS_UINT32 ulNewLev)
{
    VOS_INT32           lLockValue;
    VOS_UINT32          ulCurrentSlice;

    if (CPU_VIEW_NO == g_ulTaskWatch)
    {
        return;
    }

    lLockValue = VOS_SplIMP();

    if (CPU_VIEW_YES == CpuView_IsOverturn())
    {
        VOS_Splx(lLockValue);
        return;
    }

    /* get current time */
    ulCurrentSlice = mdrv_timer_get_hrt_timestamp();

    g_pstCpuView[g_ulCpuViewCnt].ulId           = ulNewLev;
    g_pstCpuView[g_ulCpuViewCnt].ucType         = CPU_VIEW_TYPE_INT;
    g_pstCpuView[g_ulCpuViewCnt].ucLev          = CPU_VIEW_LEV_ENTRY;
    g_pstCpuView[g_ulCpuViewCnt].ulSlice        = ulCurrentSlice;
    g_pstCpuView[g_ulCpuViewCnt].ulTick         = CPU_VIEW_GET_TICK();
    g_pstCpuView[g_ulCpuViewCnt].ulPC           = 0xFFFFFFFF;
    g_pstCpuView[g_ulCpuViewCnt].ulPara1        = 0;
    g_ulCpuViewCnt++;

    VOS_Splx(lLockValue);

    return;
} /* CpuView_IntLevChgInHook */


VOS_VOID CpuView_IntLevChgOutHook(VOS_UINT32 ulOldLev)
{
    VOS_INT32           lLockValue;
    VOS_UINT32          ulCurrentSlice;

    if (CPU_VIEW_NO == g_ulTaskWatch)
    {
        return;
    }

    lLockValue = VOS_SplIMP();

    if (CPU_VIEW_YES == CpuView_IsOverturn())
    {
        VOS_Splx(lLockValue);
        return;
    }

    /* get current time */
    ulCurrentSlice = mdrv_timer_get_hrt_timestamp();

    g_pstCpuView[g_ulCpuViewCnt].ulId           = ulOldLev;
    g_pstCpuView[g_ulCpuViewCnt].ucType         = CPU_VIEW_TYPE_INT;
    g_pstCpuView[g_ulCpuViewCnt].ucLev          = CPU_VIEW_LEV_EXIT;
    g_pstCpuView[g_ulCpuViewCnt].ulSlice        = ulCurrentSlice;
    g_pstCpuView[g_ulCpuViewCnt].ulTick         = CPU_VIEW_GET_TICK();
    g_pstCpuView[g_ulCpuViewCnt].ulPC           = 0xFFFFFFFF;
    g_pstCpuView[g_ulCpuViewCnt].ulPara1        = 0;
    g_ulCpuViewCnt++;

    VOS_Splx(lLockValue);

    return;
} /* CpuView_IntLevChgOutHook */

#if (VOS_WIN32 != VOS_OS_VER)


VOS_VOID __cyg_profile_func_enter(VOS_VOID *this_fn, VOS_VOID *call_site)
{
    VOS_INT32       lLockValue;
    VOS_UINT32      ulCurrentSlice;

    if (CPU_VIEW_NO == g_ulFuncWatch)
    {
        return;
    }

    lLockValue = VOS_SplIMP();

    if (CPU_VIEW_YES == CpuView_IsOverturn())
    {
        VOS_Splx(lLockValue);
        return;
    }

    /* get current time */
    ulCurrentSlice = mdrv_timer_get_hrt_timestamp();

    g_pstCpuView[g_ulCpuViewCnt].ulId       = (VOS_UINT32)this_fn;
    g_pstCpuView[g_ulCpuViewCnt].ucType     = CPU_VIEW_TYPE_FUNC;
    g_pstCpuView[g_ulCpuViewCnt].ucLev      = CPU_VIEW_LEV_ENTRY;
    g_pstCpuView[g_ulCpuViewCnt].ulSlice    = ulCurrentSlice;
    g_pstCpuView[g_ulCpuViewCnt].ulTick     = CPU_VIEW_GET_TICK();
    g_pstCpuView[g_ulCpuViewCnt].ulPC       = (VOS_UINT32)call_site;
    g_pstCpuView[g_ulCpuViewCnt].ulPara1    = 0;
    g_ulCpuViewCnt++;

    VOS_Splx(lLockValue);

    return;
} /* __cyg_profile_func_enter */



VOS_VOID __cyg_profile_func_exit(VOS_VOID *this_fn, VOS_VOID *call_site)
{
    VOS_INT32       lLockValue;
    VOS_UINT32      ulCurrentSlice;

    if (CPU_VIEW_NO == g_ulFuncWatch)
    {
        return;
    }

    lLockValue = VOS_SplIMP();

    if (CPU_VIEW_YES == CpuView_IsOverturn())
    {
        VOS_Splx(lLockValue);
        return;
    }

    /* get current time */
    ulCurrentSlice = mdrv_timer_get_hrt_timestamp();

    g_pstCpuView[g_ulCpuViewCnt].ulId       = (VOS_UINT32)this_fn;
    g_pstCpuView[g_ulCpuViewCnt].ucType     = CPU_VIEW_TYPE_FUNC;
    g_pstCpuView[g_ulCpuViewCnt].ucLev      = CPU_VIEW_LEV_EXIT;
    g_pstCpuView[g_ulCpuViewCnt].ulSlice    = ulCurrentSlice;
    g_pstCpuView[g_ulCpuViewCnt].ulTick     = CPU_VIEW_GET_TICK();
    g_pstCpuView[g_ulCpuViewCnt].ulPC       = (VOS_UINT32)call_site;
    g_pstCpuView[g_ulCpuViewCnt].ulPara1    = 0;
    g_ulCpuViewCnt++;

    VOS_Splx(lLockValue);

    return;
} /* __cyg_profile_func_exit */
#endif


VOS_VOID CpuView_SetPoint(VOS_UINT32 ulId, VOS_UINT8 ucLev, VOS_UINT32 ulPara0, VOS_UINT32 ulPara1)
{
    VOS_INT32   lLockValue;
    VOS_UINT32  ulCurrentSlice;

    if (CPU_VIEW_NO == g_ulPointWatch)
    {
        return;
    }

    lLockValue = VOS_SplIMP();

    if (CPU_VIEW_YES == CpuView_IsOverturn())
    {
        VOS_Splx(lLockValue);
        return;
    }

    /* get current time */
    ulCurrentSlice = mdrv_timer_get_hrt_timestamp();

    g_pstCpuView[g_ulCpuViewCnt].ulId       = ulId;
    g_pstCpuView[g_ulCpuViewCnt].ucType     = CPU_VIEW_TYPE_POINT;
    g_pstCpuView[g_ulCpuViewCnt].ucLev      = ucLev;
    g_pstCpuView[g_ulCpuViewCnt].ulSlice    = ulCurrentSlice;
    g_pstCpuView[g_ulCpuViewCnt].ulTick     = CPU_VIEW_GET_TICK();
    g_pstCpuView[g_ulCpuViewCnt].ulPC       = ulPara0;
    g_pstCpuView[g_ulCpuViewCnt].ulPara1    = ulPara1;
    g_ulCpuViewCnt++;

    VOS_Splx(lLockValue);

    return;
} /* CpuView_SetPoint */



VOS_VOID CpuView_OpenPointWatch(VOS_VOID)
{
    VOS_INT32         lLockValue;

    if (CPU_VIEW_NO == g_ulCpuViewInitFlag)
    {
        CPU_VIEW_LOG_PRINT("CpuView_OpenPointWatch, CpuView is not initialized!\r\n");
        return;
    }

    if (CPU_VIEW_YES == g_ulPointWatch)
    {
        CPU_VIEW_LOG_PRINT("CpuView_OpenPointWatch, WatchPoint is already opened!\r\n");
        return;
    }

    lLockValue = VOS_SplIMP();
    g_ulPointWatch  = CPU_VIEW_YES;
    VOS_Splx(lLockValue);

    CPU_VIEW_LOG_PRINT("WatchPoint open successfully!\r\n");

    return;
} /* CpuView_OpenPointWatch */

VOS_VOID CpuView_OpenTaskWatch(VOS_VOID)
{
    VOS_INT32         lLockValue;

    if (CPU_VIEW_NO == g_ulCpuViewInitFlag)
    {
        CPU_VIEW_LOG_PRINT("CpuView_OpenTaskWatch, CpuView is not initialized!\r\n");
        return;
    }

    if (CPU_VIEW_YES == g_ulTaskWatch)
    {
        CPU_VIEW_LOG_PRINT("WatchTask is already opened!\r\n");
        return;
    }

    (VOS_VOID)CpuView_GetTaskName();

    lLockValue = VOS_SplIMP();

    if ( VOS_OK != CPU_VIEW_ADD_TASK_SWITCH_HOOK( (FUNCPTR)CpuView_TaskSwitchHook ) )
    {
        VOS_Splx(lLockValue);
        CPU_VIEW_LOG_PRINT("CpuView_OpenTaskWatch CPU_VIEW_ADD_TASK_SWITCH_HOOK fail!\r\n");
        return;
    }

    mdrv_int_register_enterhook((FUNCPTR_1)CpuView_IntLevChgInHook);
    mdrv_int_register_exithook((FUNCPTR_1)CpuView_IntLevChgOutHook);

    g_ulTaskWatch   = CPU_VIEW_YES;
    VOS_Splx(lLockValue);

    CPU_VIEW_LOG_PRINT("WatchTask open successfully!\r\n");

    return;
} /* CpuView_OpenTaskWatch */

VOS_VOID CpuView_OpenFuncWatch(VOS_VOID)
{
    VOS_INT32         lLockValue;

    if (CPU_VIEW_NO == g_ulCpuViewInitFlag)
    {
        CPU_VIEW_LOG_PRINT("CpuView_OpenFuncWatch, CpuView is not initialized!\r\n");
        return;
    }

    if (CPU_VIEW_YES == g_ulFuncWatch)
    {
        CPU_VIEW_LOG_PRINT("CpuView_OpenFuncWatch is already opened!\r\n");
        return;
    }

    lLockValue = VOS_SplIMP();
    g_ulFuncWatch   = CPU_VIEW_YES;
    VOS_Splx(lLockValue);

    CPU_VIEW_LOG_PRINT("FuncWatch open successfully!\r\n");

    return;
} /* CpuView_OpenFuncWatch */

VOS_VOID CpuView_ClosePointWatch(VOS_VOID)
{
    g_ulPointWatch  = CPU_VIEW_NO;

    return;
} /* CpuView_ClosePointWatch */

VOS_VOID CpuView_CloseTaskWatch(VOS_VOID)
{
    VOS_INT32     lLockValue;

    if (CPU_VIEW_NO == g_ulTaskWatch)
    {
        return;
    }

    lLockValue       = VOS_SplIMP();

    g_ulTaskWatch   = CPU_VIEW_NO;

    /* �ر��ж��л����� */
    mdrv_int_unregister_enterhook();
    mdrv_int_unregister_exithook();

    /* �ر������л����� */
    if ( VOS_OK != CPU_VIEW_DEL_TASK_SWITCH_HOOK( (FUNCPTR)CpuView_TaskSwitchHook ) )
    {
        VOS_Splx(lLockValue);
        CPU_VIEW_LOG_PRINT("CpuView_CloseTaskWatch CPU_VIEW_DEL_TASK_SWITCH_HOOK fail!\r\n");
        return;
    }

    VOS_Splx(lLockValue);

    return;
} /* CpuView_CloseTaskWatch */

VOS_VOID CpuView_CloseFuncWatch(VOS_VOID)
{
    g_ulFuncWatch   = CPU_VIEW_NO;

    return;
} /* CpuView_CloseFuncWatch */

VOS_VOID CpuView_Init(VOS_UINT32 ulRecordMode, VOS_UINT32 ulRecordCnt)
{
    /* ulRecordMode ��¼CpuView���ڴ�ģʽ��
       0:��̬ģʽ;
       1:��̬ģʽ���ݲ�֧�֡�
    */
    VOS_UINT32  ulCpuViewTraceCnt;
#if 0
    VOS_UINT32  ulCpuViewStaticBufferLenth;
#endif

    if (CPU_VIEW_YES == g_ulCpuViewInitFlag)
    {
        CPU_VIEW_LOG_PRINT("CpuView is already initialized!\r\n");
        return;
    }

    if (0 == ulRecordCnt)
    {
        ulCpuViewTraceCnt   = CPU_VIEW_RECORD_DEFAULT_NUM;
    }
    else if (CPU_VIEW_RECORD_MAX_NUM < ulRecordCnt)
    {
        ulCpuViewTraceCnt   = CPU_VIEW_RECORD_MAX_NUM;
    }
    else
    {
        ulCpuViewTraceCnt   = ulRecordCnt;
    }

    if (CPU_VIEW_MEMORY_MODE_DYNAMIC == ulRecordMode)
    {
        g_pstCpuViewCtrl    = (CPU_VIEW_CTRL_STRU *)VOS_CacheMemAlloc(sizeof(CPU_VIEW_CTRL_STRU) + (sizeof(CPU_VIEW_STRU) * ulCpuViewTraceCnt));
        if (VOS_NULL == g_pstCpuViewCtrl)
        {
            g_ulCpuViewInitFlag = CPU_VIEW_NO;
            CPU_VIEW_LOG_PRINT("CpuView initialize failed!\r\n");

            return;
        }

        memset((void *)g_pstCpuViewCtrl, 0, sizeof(CPU_VIEW_CTRL_STRU));
        g_pstCpuViewCtrl->ulCpuViewTraceCnt = ulCpuViewTraceCnt;
        g_pstCpuViewCtrl->pstCpuView        = (CPU_VIEW_STRU *)(g_pstCpuViewCtrl + 1);
    }
    /* �ݲ�֧�־�̬�ڴ淽ʽ */
#if 0
    else if (CPU_VIEW_MEMORY_MODE_STATIC == ulRecordMode)
    {
        /*lint -e527 -e774*/
        ulCpuViewStaticBufferLenth = CPU_VIEW_STATIC_MEM_ADDRESS_END - CPU_VIEW_STATIC_MEM_ADDRESS_START;
        if (sizeof(CPU_VIEW_CTRL_STRU) > ulCpuViewStaticBufferLenth)
        {
            CPU_VIEW_LOG_PRINT("CpuView_Init fail, no enough static buffer!\r\n");
            return;
        }
        /*lint +e527 +e774*/

        g_pstCpuViewCtrl    = (CPU_VIEW_CTRL_STRU *)CPU_VIEW_STATIC_MEM_ADDRESS_START;

        memset((void *)g_pstCpuViewCtrl, 0, sizeof(CPU_VIEW_CTRL_STRU));

        g_pstCpuViewCtrl->ulCpuViewTraceCnt = (ulCpuViewStaticBufferLenth - sizeof(CPU_VIEW_CTRL_STRU))/(sizeof(CPU_VIEW_STRU));
        g_pstCpuViewCtrl->pstCpuView        = (CPU_VIEW_STRU *)(g_pstCpuViewCtrl + 1);
    }
#endif
    else
    {
        /* Ŀǰ��֧�ֶ�̬�ڴ�����ģʽ��ֱ�ӷ��� */
        CPU_VIEW_LOG_PRINT("CpuView_Init Fail!Only Dynamic malloc is available!\r\n");
        return;
    }

    CPU_VIEW_LOG_PRINT("CpuView initialize successfully!\r\n");

    g_ulCpuViewInitFlag = CPU_VIEW_YES;

    return;
} /* CpuView_Init */

VOS_VOID CpuView_Close(VOS_VOID)
{
    if (CPU_VIEW_NO == g_ulCpuViewInitFlag)
    {
        return;
    }

    if (CPU_VIEW_YES == g_ulCpuViewStartFlag)
    {
        CpuView_End();
    }

    (VOS_VOID)VOS_CacheMemFree(g_pstCpuViewCtrl);
    g_pstCpuViewCtrl = VOS_NULL;

    g_ulCpuViewInitFlag = CPU_VIEW_NO;

    return;
} /* CpuView_Close  */

VOS_VOID CpuView_Start(VOS_UINT32 ulMode)
{
    VOS_INT32         lLockValue;

    if (CPU_VIEW_NO == g_ulCpuViewInitFlag)
    {
        /* ����Ĭ��ֵ��ʼ�� */
        CpuView_Init(CPU_VIEW_MEMORY_MODE_DYNAMIC, 0);
    }

    if (CPU_VIEW_YES == g_ulCpuViewStartFlag)
    {
        CPU_VIEW_LOG_PRINT("CpuView is already started!\r\n");
        return;
    }

    g_ulCpuViewMode = ulMode;

    CpuView_OpenPointWatch();
    CpuView_OpenTaskWatch();
    CpuView_OpenFuncWatch();

    lLockValue = VOS_SplIMP();
    g_ulCpuViewCnt          = 0;
    g_ulCpuViewOC           = CPU_VIEW_RECORD_OVERTURN_NO;
    g_ulCpuViewStartFlag    = CPU_VIEW_YES;
    VOS_Splx(lLockValue);

    CPU_VIEW_LOG_PRINT("CpuView Start......\r\n");

    return;
} /* CpuView_Start */



VOS_VOID CpuView_End(VOS_VOID)
{
    if (CPU_VIEW_NO == g_ulCpuViewStartFlag)
    {
        CPU_VIEW_LOG_PRINT("CpuView is not started!\r\n");
        return;
    }

    CpuView_ClosePointWatch();
    CpuView_CloseTaskWatch();
    CpuView_CloseFuncWatch();

    g_ulCpuViewStartFlag = CPU_VIEW_NO;

    return;
} /* CpuView_End */

VOS_VOID CpuView_Restart(VOS_VOID)
{
    VOS_INT32       lLockValue;

    if (CPU_VIEW_NO == g_ulCpuViewStartFlag)
    {
        CPU_VIEW_LOG_PRINT("CpuView is not started,please start first!\r\n");
        return;
    }

    lLockValue = VOS_SplIMP();

    g_ulPointWatch      = CPU_VIEW_YES;
    g_ulTaskWatch       = CPU_VIEW_YES;
    g_ulFuncWatch       = CPU_VIEW_YES;

    g_ulCpuViewOC       = CPU_VIEW_RECORD_OVERTURN_NO;
    g_ulCpuViewCnt      = 0;

    VOS_Splx(lLockValue);

    return;
} /* CpuView_Restart */

VOS_VOID CpuView_Dump(VOS_UINT32 ulDumpMode)
{
    FILE                               *fp;
    VOS_CHAR                            acDumpFileName[500];
    static VOS_UINT8                    s_ucDumpFileNO = 0;
    VOS_INT                             iRet;
    VOS_INT32                           lLockValue;

    /* cpu_Viewδ��ʼ��������Ĭ��ֵ���г�ʼ�� */
    if (CPU_VIEW_NO == g_ulCpuViewInitFlag)
    {
        /* ����Ĭ��ֵ��ʼ�� */
        CpuView_Init(CPU_VIEW_MEMORY_MODE_DYNAMIC, 0);

        /* ��ѭ��ģʽ */
        CpuView_Start(CPU_VIEW_RECORD_MODE_CYCLE_NO);

        /* �ȴ�10s */
        CPU_VIEW_TASK_DELAY(1000);
    }

    /* cpu_Viewδ��ʼ������Ĭ��ֵ��ʼ */
    if (CPU_VIEW_NO == g_ulCpuViewStartFlag)
    {
        /* ��ѭ��ģʽ */
        CpuView_Start(CPU_VIEW_RECORD_MODE_CYCLE_NO);

        /* �ȴ�10s */
        CPU_VIEW_TASK_DELAY(1000);
    }

    if ( (VOS_NULL == g_pstCpuView)
        || ((0 == g_ulCpuViewCnt) && (CPU_VIEW_RECORD_OVERTURN_NO == g_ulCpuViewOC)) )
    {
        CPU_VIEW_LOG_PRINT("CpuView_DumpTrace, No Trace need dump!\r\n");
        return;
    }

    CpuView_End();

    CPU_VIEW_LOG_PRINT("CpuView Dump Begin ............\r\n");

    lLockValue = VOS_SplIMP();

    if (CPU_VIEW_DUMP_GEN_MODE_FLASH == ulDumpMode)    /* �����FLASH */
    {
#if (FEATURE_ON == FEATURE_MULTI_FS_PARTITION) /* SFT board*/
        sprintf(acDumpFileName, "/data/hisi_logs/cp_log/coredump/CpuView%d.dump", s_ucDumpFileNO);
#else
        /*lint -e586*/
        sprintf(acDumpFileName, "/yaffs0/CpuView%d.dump", s_ucDumpFileNO);
        /*lint +e586*/
#endif

        fp  = mdrv_file_open(acDumpFileName, "wb");
    }
    /* �ݲ�֧����������� */
#if 0
    else if (CPU_VIEW_DUMP_GEN_MODE_NETCARD == ulDumpMode)   /* ��������� */
    {
        CPU_VIEW_LOG_PRINT("Dump to Host!\r\n");
        fp  = DRV_FILE_OPEN("host:CpuView.dump", "wb");
    }
#endif
    else
    {
        VOS_Splx(lLockValue);
        CPU_VIEW_LOG_PRINT("Not support Dump file mode,Please check again!\r\n");

        return;
    }

    if (VOS_NULL == fp)
    {
        VOS_Splx(lLockValue);
        CPU_VIEW_LOG_PRINT("Open File Fail!\r\n");

        return;
    }

    iRet = mdrv_file_write(g_pstCpuViewCtrl, sizeof(CPU_VIEW_CTRL_STRU), 1, fp);
    if (-1 ==  iRet)
    {
        mdrv_file_close(fp);
        VOS_Splx(lLockValue);
        CPU_VIEW_LOG_PRINT("Write Control Info Fail!\r\n");

        return;
    }

    iRet = mdrv_file_write(g_pstCpuView, sizeof(CPU_VIEW_STRU), g_ulCpuViewTraceCnt, fp);
    if (-1 ==  iRet)
    {
        mdrv_file_close(fp);
        VOS_Splx(lLockValue);
        CPU_VIEW_LOG_PRINT("Write Cpu View Fail!\r\n");

        return;
    }

    mdrv_file_close(fp);

    VOS_Splx(lLockValue);

    CPU_VIEW_LOG_PRINT("CpuView Dump End ............\r\n");
    CPU_VIEW_LOG_PRINT1("Dump File Name:%s......\r\n", (VOS_INT)acDumpFileName);

    s_ucDumpFileNO++;

    return;
} /* CpuView_Dump */


VOS_VOID CpuView_InfoPrint(VOS_VOID)
{
    if ((CPU_VIEW_NO == g_ulCpuViewInitFlag) || (VOS_NULL == g_pstCpuViewCtrl))
    {
        CPU_VIEW_LOG_PRINT("CpuView is not initialized!\r\n");
        return;
    }

    CPU_VIEW_LOG_PRINT1("CpuViewCtrl Base Addr:0x%x\r\n", (VOS_INT)g_pstCpuViewCtrl);
    CPU_VIEW_LOG_PRINT1("CpuView Base Addr:0x%x\r\n", (VOS_INT)g_pstCpuViewCtrl->pstCpuView);

    CPU_VIEW_LOG_PRINT1("CpuView Mode:%d\r\n", (VOS_INT)g_pstCpuViewCtrl->ulCpuViewMode);
    CPU_VIEW_LOG_PRINT1("CpuView TraceCnt:%d\r\n", (VOS_INT)g_pstCpuViewCtrl->ulCpuViewTraceCnt);
    CPU_VIEW_LOG_PRINT1("CpuView Cnt:%d\r\n", (VOS_INT)g_pstCpuViewCtrl->ulCpuViewCnt);
    CPU_VIEW_LOG_PRINT1("CpuView OC:%d\r\n", (VOS_INT)g_pstCpuViewCtrl->ulCpuViewOC);
    CPU_VIEW_LOG_PRINT1("CpuView TaskNumber:%d\r\n", (VOS_INT)g_pstCpuViewCtrl->ulTaskNumber);

    return;
}
/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


