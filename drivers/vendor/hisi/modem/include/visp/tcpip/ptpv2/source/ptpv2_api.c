/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_api.c
*
*  Project Code:
*   Module Name: PTPV2 api
*  Date Created: 2014-03-03
*        Author: luoagwoei
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03    luoagwoei               Create
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"

#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/ptpv2/include/ptpv2_pkt.h"
#include "tcpip/ptpv2/include/ptpv2_func.h"
#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_basefun.h"

/*******************************************************************************
*    Func Name: TCPIP_PTP_Init
* Date Created: 2014-03-03
*       Author: luogaowei
*      Purpose: PTPV2��ʼ��
*  Description: PTPV2��ʼ����������ʱ�������ġ�������Ϣ���У�����PTP���񣬷���˿���Դ
*        Input: ulPtpClockType: PTPʱ�����ͣ�OC����BC
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-03   luogaowei               Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_Init(ULONG ulPtpClockType)
{
    ULONG ulRet = TCPIP_PTP_OK;

    ulRet = PTPV2_Global_Init(ulPtpClockType);
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27EA, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_Init ClockType = %u, return code = %#x.\r\n",
        ulPtpClockType, ulRet, 0, 0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_UnInit
* Date Created: 2014-03-03
*       Author: luogaowei
*      Purpose: PTPV2ȥ��ʼ��
*  Description: PTPV2ȥ��ʼ����д�¼���PTP�����񣬲��ȴ�������ж�����
*        Input: 
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-03   luogaowei               Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_UnInit()
{
    ULONG ulRet = TCPIP_PTP_OK;

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPV2û�г�ʼ��*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    g_pfETH_PTPV2_HOOK = NULL; /*ֹͣ���ձ���*/

    PTPV2_WarningRemoveProc();/*�澯�������*/

    /*֪ͨPTPV2�������Զ�����*/
    ulRet = VOS_Ev_Write(g_ulPtpV2TaskId, PTPV2_EVT_TASK_OVER_Q);
    if (TCPIP_PTP_OK != ulRet)
    {
        PTPV2_UnLock();
        goto EXIT_LABEL;
    }

    PTPV2_UnLock();

    /*����ͬ���ź������ȴ�PTPV2��������*/
    ulRet = TCPIP_CreateSm(NULL, 0, &g_ulSynsemId);
    if (TCPIP_PTP_OK == ulRet)
    {
        ulRet = TCPIP_SmP_Wait(g_ulSynsemId, 1000);/*�ȴ�1��*/
        if (TCPIP_PTP_OK != ulRet)
        {
            TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2A86, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN,
                   "TCPIP PTPv2 LOG: TCPIP_PTP_UnInit SmP wait error! return code = %#x.\r\n", 
                   ulRet, 0, 0, 0);

            ulRet = TCPIP_PTP_ERR_SMP_TIMEOUT;
        }

        (VOID)TCPIP_DeleteMutex(g_ulSynsemId);
    }

    g_ulSynsemId = 0;

EXIT_LABEL:
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27EB, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_UnInit , return code = %#x.\r\n",
         ulRet, 0, 0, 0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_AddPort
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: �������õ�PTP�˿�
*  Description: �������õ�PTP�˿�
*        Input: ULONG ulIfIndex: �ӿ�����
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr: ��ӵ�PTP��ַ��Ŀǰ��ʹ�ã����ڽ�����չ
*       Output: USHORT* pusPtpPortNo:���ص�PTP�˿ں�
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 1.Ŀǰ��֧��Overmac�����ڽӿ����ò���Ҫָ��physical��ַ
*               2.OC�£����صĶ˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_AddPort(ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr,
                        USHORT* pusPtpPortNo)
{
    ULONG ulRet = TCPIP_PTP_OK;
    PTPV2_PORT_S*  pstPortTemp = NULL;
    PTPV2_PORT_S*  pstAdd = NULL;
    ULONG ulFreeLockFlag = PTPV2_NO;
    USHORT usPortNo = 0;

    if (NULL == pusPtpPortNo)
    {
        ulRet =  TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }

    /*PTPV2û�г�ʼ��*/
    if (PTPV2_NO == PTPV2_GetInitFlag())
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;

    /*��֧�ֵĽӿ�����*/
    ulRet =  PTPV2_CheckIfIndex(ulIfIndex);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*�Ƿ��Ѿ������*/
    ulRet = PTPV2_CheckPortNoUpToMax();
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*���ж����Ƿ���ڣ������������*/
    ulRet = PTPV2_GetPortInfoByIntf(ulIfIndex, pstPtpAddr, &pstPortTemp);
    if (TCPIP_PTP_OK == ulRet)
    {
        if (NULL == pstPortTemp || NULL == pstPortTemp->pstSubPortInfo)
        {
            ulRet = TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        }
        else
        {
            *pusPtpPortNo = pstPortTemp->pstSubPortInfo->usPortNo;
            usPortNo = *pusPtpPortNo;
        }

        goto EXIT_LABEL;
    }

    /*����µ����ڵ�*/
    ulRet = PTPV2_AddPortInfo(ulIfIndex, pstPtpAddr, &pstAdd);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*PTP �˿ںŲ�����ʼ��*/
    (VOID)PTPV2_InitPortInfo(pstAdd);

    *pusPtpPortNo = pstAdd->pstSubPortInfo->usPortNo;
    usPortNo = *pusPtpPortNo;
EXIT_LABEL:
    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27EC, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_AddPort ulIfIndex = %u, usPortNo = %u, return code = %#x.\r\n",
        ulIfIndex, usPortNo, ulRet,  0);

    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_DelPort
* Date Created: 2014-03-21
*       Author: luogaowei & dutianyi
*      Purpose: ɾ��ָ����PTP�˿�
*  Description: ɾ��ָ����PTP�˿�
*        Input: USHORT usPtpPortNo:PTP�˿ں�
*               ULONG ulIfIndex:�ӿ�����
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr:PTP��ַ
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 1. BCֻ��Ҫָ���Ķ˿ںż��ɣ�����������������ֵ����
*               2. OC���ڹ�����Ƕ˿ں�1����Ҫָ���ӿ�����(����Ҳ������Ҫָ����ַ)
*               3. pstPtpAddr��Ϊδ����չԤ������OC�£�ͬһ���ӿڲ�ͬ�ĵ�ַ��������PTPӦ��
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-21   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_DelPort(USHORT usPtpPortNo, ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPV2û�г�ʼ��*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;

    ulRet = PTPV2_CheckPortValidation(usPtpPortNo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    if (PTPV2_CLOCK_TYPE_OC == PTPV2_GetClockType())
    {
        ulRet = PTPV2_DelOCPortInfoEntry(usPtpPortNo, ulIfIndex, pstPtpAddr);
    }
    else
    {
        ulRet = PTPV2_DelBCPortInfoEntry(usPtpPortNo);
    }

EXIT_LABEL:
    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27ED, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_DelPort  usPtpPortNo = %u, return code = %#x.\r\n",
         usPtpPortNo, ulRet,  0, 0);

    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_Start
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: ����PTP�Ĺ���
*  Description: ����PTP�Ĺ��ܣ�����ָ���˿ڵķ��Ͷ�ʱ��
*        Input: USHORT usPtpPortNo: ������PTP�˿ں�
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr: ��ַ��ϢĿǰ��ʹ�ã�������չ
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 1.����pstPtpAddr��ʱ��ʹ�ã����ڽ�����չ֧�ֲ�3��������
*               2.OC�½���һ���˿ڣ�������ö˿����е�����ڶ��ᷢ�ͱ���
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_Start(USHORT usPtpPortNo, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;
    PTPV2_PORT_S* pstPortInfo = NULL;

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2û�г�ʼ��*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    if (NULL == pstPtpAddr)
    {
        ulRet =  TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }


    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;

    /* �˿ں��Ƿ���֧�ֵķ�Χ�� */
    ulRet = PTPV2_CheckPortValidation(usPtpPortNo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /* �ж϶˿��Ƿ���Ч */
    ulRet = PTPV2_GetPortInfoByPort(usPtpPortNo, &pstPortInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /* �ж϶˿��Ƿ��Ѿ����� */
    if (PTPV2_YES == pstPortInfo->pstSubPortInfo->ucWorkState)
    {
        goto EXIT_LABEL;
    }

    /*�Ѿ�����������*/
    (VOID)pstPortInfo->pfPtpStartFunc(pstPortInfo, pstPtpAddr);/*����PTP*/

EXIT_LABEL:

    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27EE, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_Start  usPtpPortNo = %u , return code = %#x.\r\n",
        usPtpPortNo, ulRet, 0, 0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetClockIdentity
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: ����PTPʱ��ID
*  Description: ����PTPʱ��ID
*        Input: TCPIP_PTP_CLOCK_ID_SZ szClockID:PTPʱ��ID
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: ������Ч���ɲ�Ʒ��֤
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetClockIdentity(TCPIP_PTP_CLOCK_ID_SZ szClockID)
{
    CHAR  szClockInfo[LEN_64] = {0};
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;
    
    if (NULL == szClockID)
    {
        ulRet =  TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2û�г�ʼ��*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    (VOID)TCPIP_SNPRINTF0(szClockInfo, LEN_64, P8("%02x%02x%02x%02x%02x%02x%02x%02x\r\n",
                       szClockID[0],
                       szClockID[1],
                       szClockID[2],
                       szClockID[3],
                       szClockID[4],
                       szClockID[5],
                       szClockID[6],
                       szClockID[7]));
    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;
    if (NULL == g_pstPtpGlobalInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    (VOID)TCPIP_Mem_Copy((VOID*)g_pstPtpGlobalInfo->szClockId, sizeof(TCPIP_PTP_CLOCK_ID_SZ),(VOID*)szClockID, sizeof(TCPIP_PTP_CLOCK_ID_SZ));
    PTPV2_UpdateVirtualD0();
    
EXIT_LABEL:
    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27EF, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetClockIdentity  return code = %#x.\r\n",
        ulRet, 0, 0, 0);

    TCPIP_LOG_VARLEN(RUN_LOG_VISP_33D3, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                     "TCPIP PTPV2 LOG: TCPIP_PTP_SetClockIdentity  szClockID = %s \r\n",
                     szClockInfo);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetClockQuality
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: ����ʱ��Դ����
*  Description: ����ʱ��Դ����
*        Input: TCPIP_PTP_CLOCK_QA_S *pstPtpCfgClockQuality:ʱ��Դ����
*                 pstPtpCfgClockQuality->ucClockClass:ʱ�����Ĭ��0
*                 pstPtpCfgClockQuality->ucClockAccuracy: ʱ�Ӿ��ȣ�Ĭ��0����Χ0x20-0x32
*                 pstPtpCfgClockQuality->usOffsetScaledLogVariance:ʱ���ȶ��ȣ�Ĭ��0
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: ʱ�ӵȼ�/ʱ���ȶ��ȵ���Ч���ɲ�Ʒ��֤
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetClockQuality(TCPIP_PTP_CLOCK_QA_S *pstPtpCfgClockQuality)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;
    TCPIP_PTP_CLOCK_QA_S  stClockForLog = {0};

    if (NULL == pstPtpCfgClockQuality)/*������Ч���ж�*/
    {
        ulRet =  TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }

    /*����ʱ�侫���ж���Ч�ԣ������ɲ�Ʒ����*/
    if ((TCPIP_PTP_CLOCK_ACCURACY_25NS > pstPtpCfgClockQuality->ucClockAccuracy) || (TCPIP_PTP_CLOCK_ACCURACY_M10S < pstPtpCfgClockQuality->ucClockAccuracy))
    {
        ulRet = TCPIP_PTP_ERR_CLOCK_ACCURACY;
        goto EXIT_LABEL;
    }

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2û�г�ʼ��*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;
    if (NULL == g_pstPtpGlobalInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    (VOID)TCPIP_Mem_Copy((VOID*)&stClockForLog, sizeof(TCPIP_PTP_CLOCK_QA_S),(VOID*)pstPtpCfgClockQuality, sizeof(TCPIP_PTP_CLOCK_QA_S));
    (VOID)TCPIP_Mem_Copy((VOID*)&g_pstPtpGlobalInfo->stCfgDefaultDs.stCfgClockQa,sizeof(TCPIP_PTP_CLOCK_QA_S),
        (VOID*)pstPtpCfgClockQuality, sizeof(TCPIP_PTP_CLOCK_QA_S));

EXIT_LABEL:
    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F0, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPV2 LOG: TCPIP_PTP_SetClockQuality, ucClockClass = %u, ucClockAccuracy = %u, \
        usOffsetScaledLogVariance = %u ,return code =%u.\r\n",
        (ULONG)(stClockForLog.ucClockClass),
        (ULONG)(stClockForLog.ucClockAccuracy),
        (ULONG)(stClockForLog.usOffsetScaledLogVariance),
        (ULONG)ulRet);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetUtcProperties
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi
*      Purpose: OC matser������UTC
*  Description: OC matser������UTC
*        Input: SHORT sCurrentUtcOffset:UTCƫ����
*               BOOL_T bLeap61:Leap61
*               BOOL_T bLeap59:Leap59
*               BOOL_T bCurrentUtcOffsetValid:UTCƫ������Ч��
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 1.Leap61��Leap59����ͬʱΪ��
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetUtcProperties(SHORT sCurrentUtcOffset, BOOL_T bLeap61, BOOL_T bLeap59, 
                                    BOOL_T bCurrentUtcOffsetValid)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;

    /* leap61,leap59������ͬʱΪ�� */
    if (((BOOL_TRUE == bLeap61) && (BOOL_TRUE == bLeap59))
        || (BOOL_TRUE != bCurrentUtcOffsetValid && BOOL_FALSE != bCurrentUtcOffsetValid))
    {
        ulRet = TCPIP_PTP_ERR_INVALID_PARA;
        goto EXIT_LABEL;
    }

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2û�г�ʼ��*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;
    if (NULL == g_pstPtpGlobalInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    /* ��ֵ��ǰutcʱ��ƫ�� */
    g_pstPtpGlobalInfo->stCfgDefaultDs.sCurrentUtcOffset = sCurrentUtcOffset;

    /* ��ֵ��ǰUTC������һ�����Ƿ�61������� */
    g_pstPtpGlobalInfo->stCfgDefaultDs.bLeap61 = bLeap61;

    /* ��ֵ��ǰUTC������һ�����Ƿ�59������� */
    g_pstPtpGlobalInfo->stCfgDefaultDs.bLeap59 = bLeap59;

    /*  ��ֵ��ǰʱ��ƫ��������Ч */
    g_pstPtpGlobalInfo->stCfgDefaultDs.bCurrentUtcOffsetValid = bCurrentUtcOffsetValid;

    PTPV2_UpdateVirtualD0();

EXIT_LABEL:

    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F1, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetUtcProperties  sCurrentUtcOffset = %d , bLeap61 = %u, bLeap59 = %u,"
        " bCurrentUtcOffsetValid = %u.\r\n",
        sCurrentUtcOffset, bLeap61, bLeap59, bCurrentUtcOffsetValid);
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F2, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetUtcProperties  return code = %#x.\r\n",
        ulRet, 0, 0 ,0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetPriClassGroup
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: ����PTP��ѡԴ
*  Description: ����PTP��ѡԴ��ѡ������ѡԴһ�µ�Դ����PPI�·�ʱ��Я����ѡԴ���
*        Input: UCHAR ucClass0
*               UCHAR ucClass1
*               UCHAR ucClass2
*               UCHAR ucClass3
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: ������Ч���ɲ�Ʒ��֤
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetPriClassGroup(UCHAR ucClass0, UCHAR ucClass1, UCHAR ucClass2, UCHAR ucClass3)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2û�г�ʼ��*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;
    if (NULL == g_pstPtpGlobalInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass0 = ucClass0;
    g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass1 = ucClass1;
    g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass2 = ucClass2;
    g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass3 = ucClass3;
    g_pstPtpGlobalInfo->stCfgDefaultDs.ucPriClassFlag = PTPV2_YES;/*�����������ѡԴ*/

EXIT_LABEL:
    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F3, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPV2 LOG: TCPIP_PTP_SetPriClassGroup, ucClass0 = %u, ucClass1 = %u, \
        ucClass2 = %u, ucClass3 = %u.\r\n",
        ucClass0, ucClass1, ucClass2, ucClass3);

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F4, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPV2 LOG: TCPIP_PTP_SetPriClassGroup, return code = %#x.\r\n",
        ulRet, 0, 0, 0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetDomain
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: ����ʱ���豸�������
*  Description: ����ʱ���豸���������PTPͨ�Ž���ͬһ�����ʱ�Ӽ����
*        Input: UCHAR ucDomainNumber:ʱ���豸��
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: ������Ч���ɲ�Ʒ��֤
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetDomain(UCHAR ucDomainNumber)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2û�г�ʼ��*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;

    if (NULL == g_pstPtpGlobalInfo)/*ָ��Ϊ�գ���ʾ�����쳣*/
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    g_pstPtpGlobalInfo->stCfgDefaultDs.ucDomainNumber = ucDomainNumber;

EXIT_LABEL:
    if (ulFreeLockFlag == PTPV2_YES)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F7, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetDomain  ucDomainNumber = %u , return code = %#x.\r\n",
        ucDomainNumber, ulRet, 0, 0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetAnnInterval
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: ���ö˿ڵ�Ann������Ϣ���(ָ����ʽ)
*  Description: ���ö˿ڵ�Ann������Ϣ���(ָ����ʽ)
*        Input: USHORT usPtpPortNo:ʱ�Ӷ˿ں�
*               CHAR cLogAnnInterval:ʱ�Ӷ˿�LogAnnounceIntervalֵ, Ĭ��1����Χ0--4
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: OC�¶˿ں�ֻ��Ϊ1��ʱ�����ɲ�Ʒ��֤��Ч��
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetAnnInterval(USHORT usPtpPortNo, CHAR cLogAnnInterval)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;
    PTPV2_PORT_S* pstPortInfo = NULL;

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2û�г�ʼ��*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;

    /* �˿ں��Ƿ���֧�ֵķ�Χ�� */
    ulRet = PTPV2_CheckPortValidation(usPtpPortNo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /* �ж϶˿��Ƿ���Ч */
    ulRet = PTPV2_GetPortInfoByPort(usPtpPortNo, &pstPortInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    if (NULL == pstPortInfo || NULL == pstPortInfo->pstSubPortInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    /*����ANNOUNCE��Ϣ���ͼ��*/
    pstPortInfo->pstSubPortInfo->stPortAnnInfo.clogAnnounceInterval = cLogAnnInterval;

EXIT_LABEL:
    if (ulFreeLockFlag == PTPV2_YES)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F5, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetAnnInterval  usPtpPortNo = %u ,cLogAnnInterval = %d, return code = %#x.\r\n",
        usPtpPortNo, cLogAnnInterval, ulRet,  0);
    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetAnnRcvTimeoutNum
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: ����announce���Ľ��ճ�ʱ������
*  Description: ����announce���Ľ��ճ�ʱ�������������ô������ɾ���˿��϶�Ӧ��ForeignMaster
*        Input: USHORT usPtpPortNo:PTP�˿ں�
*               UCHAR ucReceiptTimeout:���ճ�ʱ�����������ճ�ʱ������Ĭ��ֵΪ3����Χ2-10
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: OC�¶˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetAnnRcvTimeoutNum(USHORT usPtpPortNo, UCHAR ucAnnRcvTimeoutNum)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;
    PTPV2_PORT_S* pstPortInfo = NULL;

    /*��ʱ��ΧΪ2-255*/
    if (TCPPI_PTP_MIN_ANN_RCV_TIMEOUT > ucAnnRcvTimeoutNum)
    {
        ulRet = TCPIP_PTP_ERR_INVALID_PARA;
        goto EXIT_LABEL;
    }

    if (PTPV2_NO == PTPV2_GetInitFlag())/*PTPv2û�г�ʼ��*/
    {
        ulRet =  TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;

    /* �˿ں��Ƿ���֧�ֵķ�Χ�� */
    ulRet = PTPV2_CheckPortValidation(usPtpPortNo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /* �ж϶˿��Ƿ���Ч */
    ulRet = PTPV2_GetPortInfoByPort(usPtpPortNo, &pstPortInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    /*������Ч�Լ��*/
    if (NULL == pstPortInfo || NULL == pstPortInfo->pstSubPortInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    /*����ANNOUNCE ���մ���*/
    pstPortInfo->pstSubPortInfo->stPortAnnInfo.ucAnnRcvTimeoutNum = ucAnnRcvTimeoutNum;

EXIT_LABEL:
    if (ulFreeLockFlag == PTPV2_YES)
    {
        PTPV2_UnLock();
    }

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F6, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetAnnRcvTimeoutNum  usPtpPortNo = %u ,ucAnnRcvTimeoutNum = %d, return code = %#x.\r\n",
        usPtpPortNo, ucAnnRcvTimeoutNum, ulRet,  0);
    return ulRet;
}


ULONG TCPIP_PTP_SetPtsf(ULONG ulVrfIndex, TCPIP_PTP_PORT_ADDR_S* pstForeignMasterAddr, ULONG ulPtsfType,ULONG ulPTSFValue)
{
    ULONG ulRet = TCPIP_PTP_OK;
    PTPV2_FOREIGN_MASTER_S *pstForeignMaster = NULL;
    CHAR  szMacAddr[LEN_32] = {0};
    
    if (NULL == pstForeignMasterAddr)
    {
        ulRet = TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulRet = PTPV2_GetForeignMasterByAddr(pstForeignMasterAddr, &pstForeignMaster);
    if (TCPIP_PTP_OK != ulRet)
    {
        PTPV2_UnLock();
        goto EXIT_LABEL;
    }

    switch ( ulPtsfType ) 
    {
        case TCPIP_PTP_PTSF_SYNC:
        {
            pstForeignMaster->ulPtsfSync = ulPTSFValue;
            break;
        }
        
        default:
        {
            ulRet = TCPIP_PTP_ERR_INVALID_PARA;
            break;
        }
    }
    
    PTPV2_UnLock();

    /*��¼��־*/
    if ((TCPIP_PTP_PROTOCAL_IEEE_802 == pstForeignMasterAddr->usNetworkProtocol) && 
        (PTPV2_MACADDRLEN == pstForeignMasterAddr->usAddressLength))
    {
        (VOID)TCPIP_SNPRINTF0(szMacAddr, LEN_32, P6("%02x%02x.%02x%02x.%02x%02x",
                pstForeignMasterAddr->unAddr.ucMacAddr[0],pstForeignMasterAddr->unAddr.ucMacAddr[1],
                pstForeignMasterAddr->unAddr.ucMacAddr[2],pstForeignMasterAddr->unAddr.ucMacAddr[3],
                pstForeignMasterAddr->unAddr.ucMacAddr[4],pstForeignMasterAddr->unAddr.ucMacAddr[5]));
        TCPIP_LOG_VARLEN(RUN_LOG_VISP_0002, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
            "TCPIP PTPv2 LOG: TCPIP_PTP_SetPtsf for OverMac Master Addr: %s\r\n",szMacAddr);
    }
    
EXIT_LABEL:

    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_0001, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
        "TCPIP PTPv2 LOG: TCPIP_PTP_SetPtsf ulVrfIndex = %d ,ulPtsfType = %d, ulPTSFValue = %d, return code = %#x.\r\n",
        ulVrfIndex, ulPtsfType, ulPTSFValue, ulRet);
    return ulRet;

/*    TCPIP_LOG_VARLEN(RUN_LOG_VISP_0001, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                     "TCPIP PTPV2 LOG: TCPIP_PTP_SetClockIdentity  szClockID = %s \r\n",
                     szClockInfo);
*/                     

}

#ifdef __cplusplus
}
#endif
