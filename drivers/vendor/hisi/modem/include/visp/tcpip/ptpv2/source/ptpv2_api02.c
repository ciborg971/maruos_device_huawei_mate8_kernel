/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_api02.c
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
*  2014-03-03    luoagwoei               Create  ���ļ�����ά��ӿ�
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/ptpv2/include/ptpv2_pkt.h"
#include "tcpip/ptpv2/include/ptpv2_func.h"
#include "tcpip/ptpv2/include/ptpv2_timer.h"
#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/public/tcpip_basefun.h"

/*******************************************************************************
*    Func Name: TCPIP_PTP_GetPktPortStat
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ȡ�˿ڵı���ͳ����Ϣ
*  Description: ��ȡ�˿ڵı���ͳ����Ϣ
*        Input: USHORT usPtpPortNo:ʱ�Ӷ˿ں�
*       Output: TCPIP_PTP_PKT_STAT_S *pStatPackets:���ڶ˿ڵı���ͳ����Ϣ
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: OC�¶˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_GetPktPortStat(USHORT usPortNo, TCPIP_PTP_PKT_STAT_S *pStatPackets)
{
    PTPV2_PORT_S *pstPortInfo = NULL;
    ULONG ulRet = 0;
    ULONG ulFreeLockFlag = PTPV2_NO;

    if (NULL == pStatPackets)
    {
        ulRet = TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }

    /*PTPv2û�г�ʼ��*/
    if (PTPV2_NO == PTPV2_GetInitFlag())
    {
        ulRet = TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;
    
    ulRet = PTPV2_CheckPortValidation(usPortNo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    ulRet = PTPV2_GetPortInfoByPort(usPortNo, &pstPortInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        goto EXIT_LABEL;
    }

    (VOID)TCPIP_Mem_Copy((VOID *)pStatPackets, sizeof(TCPIP_PTP_PKT_STAT_S),(VOID *)&(pstPortInfo->stPacketStat), sizeof(TCPIP_PTP_PKT_STAT_S));
    
EXIT_LABEL:
    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_GetPktStat
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ȡȫ�ֵı���ͳ����Ϣ
*  Description: ��ȡȫ�ֵı���ͳ����Ϣ
*        Input: 
*       Output: TCPIP_PTP_PKT_STAT_S *pStatPackets:ȫ�ֵı���ͳ����Ϣ
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_GetPktStat(TCPIP_PTP_PKT_STAT_S *pStatPackets)
{
    if (NULL == pStatPackets)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    /*PTPv2û�г�ʼ��*/
    if (PTPV2_NO == PTPV2_GetInitFlag())
    {
        return TCPIP_PTP_ERR_UNINIT;
    }

    PTPV2_Lock();

    (VOID)TCPIP_Mem_Copy((VOID *)pStatPackets, sizeof(TCPIP_PTP_PKT_STAT_S),(VOID *)&g_stGlobalPtpV2PktStat, sizeof(TCPIP_PTP_PKT_STAT_S));

    PTPV2_UnLock();

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_GetSysInfo
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: ��ȡPTP��ǰ��ȫ����Ϣ
*  Description: ��ȡPTP��ǰ��ȫ����Ϣ(�û�������Ϣ��ѡ�е�����ʱ��Դ��Ϣ)
*        Input: 
*       Output: TCPIP_PTP_SYSTEM_INFO_S *pstSysInfo:PTPȫ����Ϣ
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_GetSysInfo(TCPIP_PTP_SYSTEM_INFO_S *pstSysInfo)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;

    /*������Ч���ж�*/
    if (NULL == pstSysInfo)
    {
        ulRet = TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }

    /*PTPv2û�г�ʼ��*/
    if (PTPV2_NO == PTPV2_GetInitFlag())
    {
        ulRet = TCPIP_PTP_ERR_UNINIT;
        goto EXIT_LABEL;
    }

    PTPV2_Lock();
    ulFreeLockFlag = PTPV2_YES;
    if (NULL == g_pstPtpGlobalInfo || NULL == g_pstPortManageInfo)
    {
        ulRet =  TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
        goto EXIT_LABEL;
    }

    /*��ȡclock id*/
    (VOID)TCPIP_Mem_Copy((VOID*)pstSysInfo->szClockId,sizeof(TCPIP_PTP_CLOCK_ID_SZ), (VOID*)g_pstPtpGlobalInfo->szClockId, sizeof(TCPIP_PTP_CLOCK_ID_SZ));

    /*��ȡ�û�����ֵ*/
    (VOID)TCPIP_Mem_Copy((VOID*)&(pstSysInfo->stDefaultDS), sizeof(TCPIP_PTP_DEFAULT_DS_S),(VOID*)&(g_pstPtpGlobalInfo->stCfgDefaultDs), sizeof(TCPIP_PTP_DEFAULT_DS_S));

    /*��ȡ��ǰ���ٽӿ�������PTP*/
    pstSysInfo->stDefaultDS.ulNumberPorts = g_pstPortManageInfo->ulCrtPortCount;

    /*��ȡѡ�е�����ʱ��Դ��Ϣ����ParentDs��ȡ*/
    (VOID)TCPIP_Mem_Copy((VOID*)&(pstSysInfo->stParentMasterDS), sizeof(TCPIP_PTP_PARENT_DS_S),(VOID*)&(g_pstPtpGlobalInfo->stParentDs), sizeof(TCPIP_PTP_PARENT_DS_S));    


EXIT_LABEL:
    if (PTPV2_YES == ulFreeLockFlag)
    {
        PTPV2_UnLock();
    }

    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_GetPortInfo
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: ��ȡPTP�˿ڼ���Ϣ
*  Description: ��ȡPTP�˿ڼ���Ϣ
*        Input: USHORT usPtpPortNo:ʱ�Ӷ˿ں�
*       Output: TCPIP_PTP_PORT_INFO_S *pstPortPara:PTP�˿ڼ���Ϣ
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
ULONG TCPIP_PTP_GetPortInfo(USHORT usPtpPortNo, TCPIP_PTP_PORT_INFO_S *pstPortPara)
{
    ULONG ulRet = TCPIP_PTP_OK;
    ULONG ulFreeLockFlag = PTPV2_NO;
    PTPV2_PORT_S* pstPortInfo = NULL;

    if (NULL == pstPortPara)
    {
        ulRet = TCPIP_PTP_ERR_POINTER_NULL;
        goto EXIT_LABEL;
    }

    /*PTPv2û�г�ʼ��*/
    if (PTPV2_NO == PTPV2_GetInitFlag())
    {
        ulRet = TCPIP_PTP_ERR_UNINIT;
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

    pstPortPara->clogAnnounceInterval = pstPortInfo->pstSubPortInfo->stPortAnnInfo.clogAnnounceInterval;
    pstPortPara->ucPortState = pstPortInfo->pstSubPortInfo->ucPtpPortFsmState;
    pstPortPara->ucPortRole = pstPortInfo->pstSubPortInfo->ucPtpPortRole;
    pstPortPara->ucAnnRcvTimeoutNum = pstPortInfo->pstSubPortInfo->stPortAnnInfo.ucAnnRcvTimeoutNum;
    pstPortPara->ucCastMode = pstPortInfo->pstSubPortInfo->ucCastMode;
    pstPortPara->ucDomain = g_pstPtpGlobalInfo->stCfgDefaultDs.ucDomainNumber;
    pstPortPara->usPortNo = usPtpPortNo;
    pstPortPara->ulIfIndex = pstPortInfo->ulIfIndex;

EXIT_LABEL:
    if (ulFreeLockFlag == PTPV2_YES)
    {
        PTPV2_UnLock();
    }

    return ulRet;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowSysInfo
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ӡPTP��ǰ��ȫ����Ϣ
*  Description: ��ӡPTP��ǰ��ȫ����Ϣ
*        Input: 
*       Output: PTP��ǰ��ȫ����Ϣ
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowSysInfo()
{
    TCPIP_PTP_SYSTEM_INFO_S stSysInfo;
    CHAR  szOutputBuf[LEN_1024] = {0};
    INT32 i32Offset = 0;
    ULONG ulRet = 0;

    /*PTPv2û�г�ʼ��*/
    if (PTPV2_NO == PTPV2_GetInitFlag())
    {
        return;
    }

    (VOID)TCPIP_Mem_Set((VOID *)&stSysInfo, 0, sizeof(TCPIP_PTP_SYSTEM_INFO_S));

    ulRet = TCPIP_PTP_GetSysInfo(&stSysInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        TCPIP_InfoOutput("\r\nGet PTP System Info failed!\r\n");
        return;
    }

    i32Offset = TCPIP_SNPRINTF0(szOutputBuf, LEN_1024, P1("\r\n %s",
                "-----------------------PTP System Info-------------------------"));

    /*Clock ID*/
    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P9("\r\n %30s : %02x%02x%02x%02x%02x%02x%02x%02x",
                                    "Clock Identity",
                                    stSysInfo.szClockId[0],
                                    stSysInfo.szClockId[1],
                                    stSysInfo.szClockId[2],
                                    stSysInfo.szClockId[3],
                                    stSysInfo.szClockId[4],
                                    stSysInfo.szClockId[5],
                                    stSysInfo.szClockId[6],
                                    stSysInfo.szClockId[7]));
    TCPIP_InfoOutput(szOutputBuf);

    /*DefaultDS*/
    i32Offset = TCPIP_SNPRINTF0(szOutputBuf, LEN_1024, 
                                    P4("\r\n %30s : %u \r\n %30s : %u", 
                                    "NumberPorts", stSysInfo.stDefaultDS.ulNumberPorts,
                                    "TwoStepFlag", stSysInfo.stDefaultDS.bTwoStepFlag));
    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P6("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u",
                                    "ClockClass", stSysInfo.stDefaultDS.stCfgClockQa.ucClockClass,
                                    "ClockAccuracy", stSysInfo.stDefaultDS.stCfgClockQa.ucClockAccuracy,
                                    "OffsetScaledLogVariance", stSysInfo.stDefaultDS.stCfgClockQa.usOffsetScaledLogVariance));
    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P6("\r\n %30s : %u \r\n %30s : %u ", 
                                    "Priority1", stSysInfo.stDefaultDS.ucPriority1,
                                    "Priority2", stSysInfo.stDefaultDS.ucPriority2,
                                    "ClockFsmMode", stSysInfo.stDefaultDS.usClockFsmMode));
    TCPIP_InfoOutput(szOutputBuf);
    
    i32Offset = TCPIP_SNPRINTF0(szOutputBuf, LEN_1024, 
                                    P8("\r\n %30s : %d \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u", 
                                    "CurrentUtcOffset", stSysInfo.stDefaultDS.sCurrentUtcOffset,
                                    "CurrentUtcOffsetValid", stSysInfo.stDefaultDS.bCurrentUtcOffsetValid,
                                    "Leap59", stSysInfo.stDefaultDS.bLeap59,
                                    "Leap61", stSysInfo.stDefaultDS.bLeap61));
    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P4("\r\n %30s : %u \r\n %30s : %u", 
                                    "DomainNumber", stSysInfo.stDefaultDS.ucDomainNumber,
                                    "PriClassFlag", stSysInfo.stDefaultDS.ucPriClassFlag));
    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P8("\r\n %30s : %d \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u", 
                                    "ucClass0", stSysInfo.stDefaultDS.ucClass0,
                                    "ucClass1", stSysInfo.stDefaultDS.ucClass1,
                                    "ucClass2", stSysInfo.stDefaultDS.ucClass2,
                                    "ucClass3", stSysInfo.stDefaultDS.ucClass3));
    TCPIP_InfoOutput(szOutputBuf);

    /*ParentDS*/
    i32Offset = TCPIP_SNPRINTF0(szOutputBuf, LEN_1024, 
                                    P9("\r\n %30s : %02x%02x%02x%02x%02x%02x%02x%02x",
                                    "GrandMaster Clock Identity",
                                    stSysInfo.stParentMasterDS.szGrandMasterId[0],
                                    stSysInfo.stParentMasterDS.szGrandMasterId[1],
                                    stSysInfo.stParentMasterDS.szGrandMasterId[2],
                                    stSysInfo.stParentMasterDS.szGrandMasterId[3],
                                    stSysInfo.stParentMasterDS.szGrandMasterId[4],
                                    stSysInfo.stParentMasterDS.szGrandMasterId[5],
                                    stSysInfo.stParentMasterDS.szGrandMasterId[6],
                                    stSysInfo.stParentMasterDS.szGrandMasterId[7]));
    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P11("\r\n %30s : %02x%02x%02x%02x%02x%02x%02x%02x \r\n %30s : %u",
                                    "Parent Clock Identity",
                                    stSysInfo.stParentMasterDS.stParentPortId.szClockId[0],
                                    stSysInfo.stParentMasterDS.stParentPortId.szClockId[1],
                                    stSysInfo.stParentMasterDS.stParentPortId.szClockId[2],
                                    stSysInfo.stParentMasterDS.stParentPortId.szClockId[3],
                                    stSysInfo.stParentMasterDS.stParentPortId.szClockId[4],
                                    stSysInfo.stParentMasterDS.stParentPortId.szClockId[5],
                                    stSysInfo.stParentMasterDS.stParentPortId.szClockId[6],
                                    stSysInfo.stParentMasterDS.stParentPortId.szClockId[7],
                                    "Parent PortNumber",
                                    stSysInfo.stParentMasterDS.stParentPortId.usPortNumber));
    TCPIP_InfoOutput(szOutputBuf);
    
    i32Offset = TCPIP_SNPRINTF0(szOutputBuf, LEN_1024, 
                                    P6("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u",
                                    "Parent ClockClass", stSysInfo.stParentMasterDS.stParentClockQA.ucClockClass,
                                    "Parent ClockAccuracy", stSysInfo.stParentMasterDS.stParentClockQA.ucClockAccuracy,
                                    "Parent OffsetScaledLogVariance", stSysInfo.stParentMasterDS.stParentClockQA.usOffsetScaledLogVariance));
    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P4("\r\n %30s : %d \r\n %30s : %u", 
                                    "GrandmasterPriority1", stSysInfo.stParentMasterDS.ucGrandmasterPriority1,
                                    "GrandmasterPriority2", stSysInfo.stParentMasterDS.ucGrandmasterPriority2));
    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P8("\r\n %30s : %d \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u", 
                                    "Parent CurrentUtcOffset", stSysInfo.stParentMasterDS.sCurrentUtcOffset,
                                    "Parent CurrentUtcOffsetValid", stSysInfo.stParentMasterDS.bCurrentUtcOffsetValid,
                                    "Parent Leap59", stSysInfo.stParentMasterDS.bLeap59,
                                    "Parent Leap61", stSysInfo.stParentMasterDS.bLeap61));
    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P8("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u", 
                                    "TimeTraceable", stSysInfo.stParentMasterDS.bTimeTraceable,
                                    "FrequencyTraceable", stSysInfo.stParentMasterDS.bFrequencyTraceable,
                                    "TimeScale", stSysInfo.stParentMasterDS.bTimeScale,
                                    "PtpTimescale", stSysInfo.stParentMasterDS.bPtpTimescale));
    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P4("\r\n %30s : %u \r\n %30s : %d", 
                                    "TimeSource", stSysInfo.stParentMasterDS.ucTimeSource,
                                    "LogMAnnInterval", stSysInfo.stParentMasterDS.cLogMAnnInterval));
    TCPIP_InfoOutput(szOutputBuf);

    return;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowPortInfo
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ӡPTP�˿ڼ���Ϣ
*  Description: ��ӡPTP�˿ڼ���Ϣ
*        Input: USHORT usPtpPortNo:ʱ�Ӷ˿ں�
*       Output: PTP�Ķ˿ڼ���Ϣ
*       Return: 
*      Caution: OC�¶˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowPortInfo(USHORT usPortNo)
{
    TCPIP_PTP_PORT_INFO_S stPortInfo;
    CHAR  szOutputBuf[LEN_1024] = {0};
    INT32 i32Offset = 0;
    ULONG ulRet = 0;
    
    /*PTPv2û�г�ʼ��*/
    if (PTPV2_NO == PTPV2_GetInitFlag())
    {
        TCPIP_InfoOutput("\r\nPTP has not been initialized!\r\n");

        return;
    }

    (VOID)TCPIP_Mem_Set((VOID *)&stPortInfo, 0, sizeof(TCPIP_PTP_PORT_INFO_S));

    ulRet = TCPIP_PTP_GetPortInfo(usPortNo, &stPortInfo);
    if (TCPIP_PTP_OK != ulRet)
    {
        TCPIP_InfoOutput("\r\nGet PTP Port Info failed!\r\n");
        
        return;
    }

    i32Offset = TCPIP_SNPRINTF0(szOutputBuf, LEN_1024, P1("\r\n %s",
                "-----------------------PTP Port Info-------------------------"));

    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P8("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %d",
                                    "IfIndex", stPortInfo.ulIfIndex,
                                    "PortNo", stPortInfo.usPortNo,
                                    "PortState", stPortInfo.ucPortState,
                                    "logAnnounceInterval", stPortInfo.clogAnnounceInterval));
    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P8("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u",
                                    "AnnRcvTimeoutNum", stPortInfo.ucAnnRcvTimeoutNum,
                                    "CastMode", stPortInfo.ucCastMode,
                                    "Domain", stPortInfo.ucDomain,
                                    "PortRole", stPortInfo.ucPortRole));

    TCPIP_InfoOutput(szOutputBuf);

    return;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowSysPktStatics
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ӡPTPϵͳ������ͳ����Ϣ
*  Description: ��ӡPTPϵͳ������ͳ����Ϣ
*        Input: 
*       Output: PTP��ϵͳ������ͳ����Ϣ
*       Return: 
*      Caution: OC�¶˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowSysPktStatics()
{
    TCPIP_PTP_PKT_STAT_S stStatPackets = {0};
    ULONG ulRet = 0;
    INT32 i32Offset = 0;
    CHAR  szOutputBuf[LEN_1024] = {0};

    /*PTPv2û�г�ʼ��*/
    if (PTPV2_NO == PTPV2_GetInitFlag())
    {
        TCPIP_InfoOutput("\r\nPTP has not been initialized!\r\n");

        return;
    }

    ulRet = TCPIP_PTP_GetPktStat(&stStatPackets);
    if (TCPIP_PTP_OK != ulRet)
    {
        TCPIP_InfoOutput("\r\nCannot get PTP PortInfo!\r\n");

        return;
    }

    i32Offset = TCPIP_SNPRINTF0(szOutputBuf, LEN_1024, P1("\r\n %s",
                "-----------------------PTP System Statistic-------------------------"));

    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P8("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %d",
                                    "RcvAnnPackets", stStatPackets.ulRcvAnnPackets,
                                    "RcvErrorPackets", stStatPackets.ulRcvErrorPackets,
                                    "SndAnnPackets", stStatPackets.ulSndAnnPackets,
                                    "SndDropPackets", stStatPackets.ulSndDropPackets));

    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P10("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u",
                                    "RcvErrorTotalLenPackets", stStatPackets.ulRcvErrorTotalLenPackets,
                                    "RcvErrorDomainNoPackets", stStatPackets.ulRcvErrorDomainNoPackets,
                                    "RcvErrorPtpLenPackets", stStatPackets.ulRcvErrorPtpLenPackets,
                                    "RcvErrorAddrPackets", stStatPackets.ulRcvErrorAddrPackets,
                                    "RcvErrorClockIdPackets", stStatPackets.ulRcvErrorClockIdPackets));

    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P8("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u",
                                    "RcvErrorSeqIdPackets", stStatPackets.ulRcvErrorSeqIdPackets,
                                    "RcvErrorUnexpectedSeqIdPackets", stStatPackets.ulRcvErrorUnexpectedSeqIdPackets,
                                    "RcvErrorIfPackets", stStatPackets.ulRcvErrorIfPackets,
                                    "RcvErrorForeMasterPackets", stStatPackets.ulRcvErrorForeMasterPackets));

    (VOID)TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P4("\r\n %30s : %u \r\n %30s : %u",
                                    "SndBuildDropPackets", stStatPackets.ulSndBuildDropPackets,
                                    "SndGetIfDropPackets", stStatPackets.ulSndGetIfDropPackets));

    TCPIP_InfoOutput(szOutputBuf);

    return;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowPortPktStatics
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ӡPTP�˿ڼ�����ͳ����Ϣ
*  Description: ��ӡPTP�˿ڼ�����ͳ����Ϣ
*        Input: 
*       Output: PTP�Ķ˿ڼ�����ͳ����Ϣ
*       Return: 
*      Caution: OC�¶˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowPortPktStatics(USHORT usPortNo)
{
    TCPIP_PTP_PKT_STAT_S stStatPackets = {0};
    ULONG ulRet = 0;
    INT32 i32Offset = 0;
    CHAR  szOutputBuf[LEN_1024] = {0};

    /*PTPv2û�г�ʼ��*/
    if (PTPV2_NO == PTPV2_GetInitFlag())
    {
        TCPIP_InfoOutput("\r\nPTP has not been initialized!\r\n");

        return;
    }

    ulRet = TCPIP_PTP_GetPktPortStat(usPortNo, &stStatPackets);
    if (TCPIP_PTP_OK != ulRet)
    {
        TCPIP_InfoOutput("\r\nCannot get PTP PortInfo!\r\n");

        return;
    }

    i32Offset = TCPIP_SNPRINTF0(szOutputBuf, LEN_1024, P2("\r\n %s",
                "-----------------------PTP Port %u Statistic-------------------------", usPortNo));

    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P8("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %d",
                                    "RcvAnnPackets", stStatPackets.ulRcvAnnPackets,
                                    "RcvErrorPackets", stStatPackets.ulRcvErrorPackets,
                                    "SndAnnPackets", stStatPackets.ulSndAnnPackets,
                                    "SndDropPackets", stStatPackets.ulSndDropPackets));

    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P10("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u",
                                    "RcvErrorTotalLenPackets", stStatPackets.ulRcvErrorTotalLenPackets,
                                    "RcvErrorDomainNoPackets", stStatPackets.ulRcvErrorDomainNoPackets,
                                    "RcvErrorPtpLenPackets", stStatPackets.ulRcvErrorPtpLenPackets,
                                    "RcvErrorAddrPackets", stStatPackets.ulRcvErrorAddrPackets,
                                    "RcvErrorClockIdPackets", stStatPackets.ulRcvErrorClockIdPackets));

    i32Offset += TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P8("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u",
                                    "RcvErrorSeqIdPackets", stStatPackets.ulRcvErrorSeqIdPackets,
                                    "RcvErrorUnexpectedSeqIdPackets", stStatPackets.ulRcvErrorUnexpectedSeqIdPackets,
                                    "RcvErrorIfPackets", stStatPackets.ulRcvErrorIfPackets,
                                    "RcvErrorForeMasterPackets", stStatPackets.ulRcvErrorForeMasterPackets));

    (VOID)TCPIP_SNPRINTF(szOutputBuf + i32Offset, LEN_1024 - i32Offset, 
                                    P4("\r\n %30s : %u \r\n %30s : %u",
                                    "SndBuildDropPackets", stStatPackets.ulSndBuildDropPackets,
                                    "SndGetIfDropPackets", stStatPackets.ulSndGetIfDropPackets));

    TCPIP_InfoOutput(szOutputBuf);

    return;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_RegFuncWarningHook
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ע��澯����
*  Description: ע��澯����
*        Input: TCPIP_PTP_WARN_OUTPUT_FUNC pfWarnOutPut:�澯������
*       Output: 
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_RegFuncWarningHook(TCPIP_PTP_WARN_OUTPUT_FUNC pfWarnOutPut)
{
    g_pfPtpV2WarnOutput = pfWarnOutPut;
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F8, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                    "TCPIP PTPV2 LOG: TCPIP_PTP_RegFuncWarningHook, hook = %#x!\r\n",
                    (ULONG)pfWarnOutPut, 0, 0, 0);

    return;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_RegFuncCapturePacketHook
* Date Created: 2014-03-15
*       Author: luogaowei
*      Purpose: ע�ᱨ�Ĳ�����
*  Description: ע�ᱨ�Ĳ�����
*        Input: TCPIP_PTP_WARN_OUTPUT_FUNC pfWarnOutPut:���Ĳ�����
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei               Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_RegFuncCapturePacketHook(TCPIP_PTP_CAPTURE_PACKET_FUNC pfPtpCapturePacket)
{
    g_pfPtpV2CapturePktFunc = pfPtpCapturePacket;

    /* ��¼��־ */
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_281A, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                     "TCPIP PTPV2 LOG: Regist Capture Packet function,hook = %#x!\r\n",
                    (ULONG)pfPtpCapturePacket, 0, 0, 0);
    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetDbgSwitch
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ����Debug����
*  Description: ����Debug����
*        Input: ULONG ulDbgFlag:
*                   TCPIP_PTP_DEBUG_FOREMASTER  = 0x01,   PTP ForeMaster����
*                   TCPIP_PTP_DEBUG_INPUT  = 0X02,        ���յ�PTP���ĵ���
*                   TCPIP_PTP_DEBUG_OUTPUT = 0X04,        ���͵�PTP���ĵ���
*                   TCPIP_PTP_DEBUG_TIMER  = 0X08,        PTP��ʱ���ĵ���
*                   TCPIP_PTP_DEBUG_WARN   = 0X10         PTP�澯�ĵ���
*       Output: 
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetDbgSwitch (ULONG ulDbgFlag)
{
    ULONG ulRet = TCPIP_PTP_OK;

    /* debug���غϷ��Լ��,ֻ�õ���λ,�����������Ƿ� */
    if (0 != (ulDbgFlag >> 6))
    {
        ulRet = TCPIP_PTP_ERR_INVALID_PARA;
        goto ExitLabel;
    }

    /* ��ֵ��־λ */
    g_ulPtpV2GlobalDbgSwitch = ulDbgFlag;

ExitLabel:
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_2F79, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
            "TCPIP PTPV2 LOG: Set Dbg Switch Finished, ulDbgFlag = %d, return %u.\r\n",
            (ULONG)ulDbgFlag, (ULONG)ulRet, 0, 0);
    return ulRet;

}

/*******************************************************************************
*    Func Name: TCPIP_PTP_RegFuncPpiHook
* Date Created: 2014-03-15
*       Author: luogaowei
*      Purpose: ע��PPI�·�������
*  Description: ע��PPI�·�������
*        Input: TCPIP_PTP_PPI_HOOK_FUNC pfPtpPpiHook:PPI�·�������
*       Output: 
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_RegFuncPpiHook(TCPIP_PTP_PPI_HOOK_FUNC pfPtpPpiHook)
{
    g_pfPtpV2PpiHookFunc = pfPtpPpiHook;
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27F9, TCPIP_LOG_LEVEL_INFO, LOG_TYPE_CFG,
                    "TCPIP PTPV2 LOG: TCPIP_PTP_RegFuncPpiHook, hook = %#x!\r\n",
                    (ULONG)pfPtpPpiHook, 0, 0, 0);

    return;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowTimerInfo
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ӡPTP��ǰ���еĶ�ʱ����Ϣ
*  Description: ��ӡPTP��ǰ���еĶ�ʱ����Ϣ
*        Input: 
*       Output: PTP��ǰ���еĶ�ʱ����Ϣ
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowTimerInfo()
{
    PTPV2_LOGIC_TIMER_S *pstLogicTimer = NULL;
    CHAR szBuf[LEN_512] = {0};
    INT32 i32Offset = 0;
    ULONG ulIndex = 0;

    /* �ȴ�ӡ��ʾ��Ϣ */
    i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512, P0("\r\n----------timer info begin----------"));

    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, 
                         P2("\r\n %30s : %u",
                         "Total timer number", g_PtpV2TimerList.u4_Count));


    TCPIP_InfoOutput(szBuf);

    /*��������*/
    DLL_Scan(&g_PtpV2TimerList, pstLogicTimer, PTPV2_LOGIC_TIMER_S*)
    {
        ulIndex ++;
        
        /* �ȴ�ӡ��ʾ��Ϣ */
        (VOID)TCPIP_SNPRINTF0(szBuf, LEN_512, P1("\r\ntimer%u info:", ulIndex));
        
        TCPIP_InfoOutput(szBuf);

        PTPV2_TimerPrint(pstLogicTimer);
    }

    (VOID)TCPIP_SNPRINTF0(szBuf, LEN_512, P0("\r\n----------timer info end---------------"));

    TCPIP_InfoOutput(szBuf);

    return;
}

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowForeMasterInfo
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ӡPTP��ǰ���е�ForeMaster��Ϣ
*  Description: ��ӡPTP��ǰ���е�ForeMaster��Ϣ
*        Input: 
*       Output: PTP��ǰ��ǰ���е�ForeMaster��Ϣ
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowForeMasterInfo()
{
    PTPV2_FOREIGN_MASTER_S *pstForeMaster = NULL;
    PTPV2_FOREIGN_MASTER_S *pstIter = NULL;
    CHAR szBuf[LEN_512] = {0};
    INT32 i32Offset = 0;
    ULONG ulIndex = 0;

    /* �ȴ�ӡ��ʾ��Ϣ */
    i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512, P0("\r\n----------foremaster info begin----------"));

    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, 
                         P2("\r\n %30s : %u",
                         "Total foremaster number", g_GlobalForeignMasterList.u4_Count));


    TCPIP_InfoOutput(szBuf);

    DLL_Scan(&g_GlobalForeignMasterList, pstIter, PTPV2_FOREIGN_MASTER_S *)
    {
        ulIndex++;

        /* �ȴ�ӡ��ʾ��Ϣ */
        (VOID)TCPIP_SNPRINTF0(szBuf, LEN_512, P1("\r\nforemaster%u info:", ulIndex));
        
        TCPIP_InfoOutput(szBuf);

        pstForeMaster = (PTPV2_FOREIGN_MASTER_S *)((CHAR *)pstIter - ((CHAR *)&pstIter->stGlobalDllNode - (CHAR *)pstIter));

        PTPV2_ForeMasterPrint(pstForeMaster);
    }

    (VOID)TCPIP_SNPRINTF0(szBuf, LEN_512, P0("\r\n----------foremaster info end---------------"));

    TCPIP_InfoOutput(szBuf);

    return;
}


ULONG TCPIP_PTP_GetForeignMasterInfo(ULONG ulVrfIndex,
    TCPIP_PTP_PORT_ADDR_S   *pstInForeignMasterPortAddr,
    TCPIP_PTP_FOREIGN_MASTER_S *pstOutForeignMasterInfo)
{
    PTPV2_FOREIGN_MASTER_S *pstForeignMaster = NULL;
    ULONG ulRet = TCPIP_PTP_OK;

    /*��ʱ����*/
    (VOID)ulVrfIndex;

    if ((NULL == pstInForeignMasterPortAddr) || (NULL == pstOutForeignMasterInfo))
    {
        return TCPIP_PTP_ERR_POINTER_NULL;    
    }

    PTPV2_Lock();

    ulRet = PTPV2_GetForeignMasterByAddr(pstInForeignMasterPortAddr, &pstForeignMaster);
    if (ulRet != TCPIP_PTP_OK)
    {
        PTPV2_UnLock();
        return ulRet;
    }

    (VOID)TCPIP_Mem_Copy((VOID *)&(pstOutForeignMasterInfo->szForeignMasterPortId), sizeof(TCPIP_PTP_PORT_ID_S), 
                        (VOID *)&(pstForeignMaster->szForeignMasterPortId), sizeof(TCPIP_PTP_PORT_ID_S));
    pstOutForeignMasterInfo->ulRcvIfIndex       = pstForeignMaster->ulRcvIfIndex;
    pstOutForeignMasterInfo->ulPtsfValue        = pstForeignMaster->ulPtsfSync;
    pstOutForeignMasterInfo->ulAnnRcvTimeoutNum = pstForeignMaster->ulAnnRcvTimerCount;    

    PTPV2_UnLock();
    return TCPIP_PTP_OK;    
}

#ifdef __cplusplus
}
#endif
