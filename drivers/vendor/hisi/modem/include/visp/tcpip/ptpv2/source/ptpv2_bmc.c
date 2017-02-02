/*-------------------------------------------------------------------------------
*
*                              ptpv2_bmc.c
*
*  Project Code:
*   Module Name: PTPV2 bmc
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"
#include "tcpip/ptpv2/include/ptpv2_func.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"
#include "tcpip/ptpv2/include/ptpv2_timer.h"
#include "tcpip/ptpv2/include/ptpv2_bmc.h"
#include "tcpip/public/tcpip_basefun.h"
#include "tcpip/etharp/include/etharp_api.h"

/*D0,Erbest,Ebest�Ƚ�*/
#define DSA_COMPAR_TYPE_NO_NEED           0   
#define DSA_COMPAR_TYPE_DO_WITH_ERBEST    1
#define DSA_COMPAR_TYPE_DO_WITH_EBEST     2
#define DSA_COMPAR_TYPE_EBEST_WITH_ERBEST 3

/*
ѡԴ:
*/

ULONG PTPV2_CompareClockClass(PTPV2_FOREIGN_MASTER_S* pstForeMasterA,
                              PTPV2_FOREIGN_MASTER_S* pstForeMasterB,
                              PTPV2_FOREIGN_MASTER_S** pstSelectMaster)
{
    UCHAR ucClockClassA = 0;
    UCHAR ucClockClassB = 0;
    /*   A B ������ѡ���У� ֱ�ӱȽ����ߴ�С
         A �ڣ�B ���ڣ�ֱ��ѡA
         A ���ڣ�B �ڣ�ֱ��ѡB
         A ��B �����ڣ�ֱ�ӱȽ����ߴ�С
         �ܽ�Ϊ������֧��
    */
    ucClockClassA = pstForeMasterA->stGrandmasterClockQuality.ucClockClass;
    ucClockClassB = pstForeMasterB->stGrandmasterClockQuality.ucClockClass;

    /*��������ѡԴ*/
    if (PTPV2_YES == g_pstPtpGlobalInfo->stCfgDefaultDs.ucPriClassFlag)
    {
        if (PTPV2_IS_PRI_CLOCK_SOURCE(ucClockClassA)
            && !PTPV2_IS_PRI_CLOCK_SOURCE(ucClockClassB))
        {
            *pstSelectMaster = pstForeMasterA;
            return TCPIP_PTP_OK;
        }
        else if (!PTPV2_IS_PRI_CLOCK_SOURCE(ucClockClassA)
                 && PTPV2_IS_PRI_CLOCK_SOURCE(ucClockClassB))
        {
            *pstSelectMaster = pstForeMasterB;
            return TCPIP_PTP_OK;
        }
        else if (PTPV2_IS_PRI_CLOCK_SOURCE(ucClockClassA)
                 && PTPV2_IS_PRI_CLOCK_SOURCE(ucClockClassB))
        {
            /*������Master��class������ѡԴ�У�������ѡԴ��˳���Ⱥ����ѡԴ*/
            if (ucClockClassA != ucClockClassB)
            {
                if(g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass0 == ucClockClassA)        
                {
                    *pstSelectMaster = pstForeMasterA;
                    return TCPIP_PTP_OK;
                }
                else if(g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass0 == ucClockClassB)
                {
                    *pstSelectMaster = pstForeMasterB;
                    return TCPIP_PTP_OK;
                }
                else if (g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass1 == ucClockClassA)
                {
                    *pstSelectMaster = pstForeMasterA;
                    return TCPIP_PTP_OK;
                }
                else if (g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass1 == ucClockClassB)
                {
                    *pstSelectMaster = pstForeMasterB;
                    return TCPIP_PTP_OK;
                }
                else if (g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass2 == ucClockClassA)
                {
                    *pstSelectMaster = pstForeMasterA;
                    return TCPIP_PTP_OK;
                }
                else if (g_pstPtpGlobalInfo->stCfgDefaultDs.ucClass2 == ucClockClassB)
                {
                    *pstSelectMaster = pstForeMasterB;
                    return TCPIP_PTP_OK;
                }
            }
        }
    }

    /*pstForeMasterAʱ�ӵȼ� < pstForeMasterBʱ�ӵȼ�*/
    if (ucClockClassA < ucClockClassB)
    {
        *pstSelectMaster = pstForeMasterA;
        return TCPIP_PTP_OK;
    }
    else if (ucClockClassA > ucClockClassB)
    {
        /*pstForeMasterAʱ�ӵȼ� > pstForeMasterBʱ�ӵȼ�*/
        *pstSelectMaster = pstForeMasterB;
        return TCPIP_PTP_OK;
    }

    return TCPIP_PTP_ERR;/*class��ͬ���޷�ѡ����Ҫ��һ��ѡԴ����*/
}

/******************************************************************************
*Func Name   : PTPV2_BMC_DSCA_Part1
*Description : ʱ�������ȽϺ���
*Input       :
*              pstDSMaster  ��Ƚ�ʱ��������foreignmaster/DataSet�ṹ��ָ��
*              pstForeMasterB  ��Ƚ�ʱ��������foreignmaster�ṹ��ָ��
*              bFlags          true������Master�Ƚ�,false��master�� DS�Ƚ�
*Output      : ppstSelectMaster: ���ȼ��ߵı���ʱ��Դ
*              BOOL_T* pbBetter: ѡԴ����Ƿ�ΪԴ����
*              BOOL_T* pbTopoBetter: ѡԴ����Ƿ�Ϊ���˸���
*Return      : �ɹ�����TCPIP_PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME               DESCRIPTION
*  ѡԴ�����޸�Ϊ��
* 1������ԭ��:���ȼ�1 ��class�ȼ������� ���ȶ��� �����ȼ�2 ��CLK ID
* 2�����û���Clockclassʶ����ʱ:
*     1)����ClockclassΪ6��7��13��14ʱ��VISP�ж���Ϊ�ο�Դ����ѡ��
*        ��������1588��·��Clockclass��ѡ˳��Ϊ��6>13>7>14. ����1588��·��
*     2)�����ֻ��һ��ClockClassΪ��6��7��13��14������һ��Ϊ6��7��
*        13��14����VISPѡ��6��7��13��14�Ĳο�Դ��
*     3)���������1588��·�У�ClockClass��Ϊ��6��7��13��14����VISP����ѡԴʧ�ܣ�
* 3�����û�û�д�Clockclassʶ����ʱ������Class�ȼ���С���Ƚϣ�ԽСԽ�ţ�
*
*******************************************************************************/
ULONG PTPV2_BMC_DSCA_Part1(ULONG ulCompareType, 
                                PTPV2_FOREIGN_MASTER_S* pstForeMasterA,
                                PTPV2_FOREIGN_MASTER_S* pstForeMasterB,
                                PTPV2_FOREIGN_MASTER_S** ppstSelectMaster,
                                BOOL_T* pbBetter, BOOL_T* pbTopoBetter)
{
    LONG lRetResult = -1;
    ULONG ulRet = TCPIP_PTP_OK;

    if (NULL == pstForeMasterA || NULL == pstForeMasterB || NULL == ppstSelectMaster)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;    
    }
    
    /*Step0:�Ƚ�ʱ��ID GM Id �Ƿ���ͬ,��ִ���㷨�ĵڶ�����*/
    /*CLOCK ID�Ƚ�*/
    (VOID)VOS_Mem_Cmp((VOID*)pstForeMasterA->szGrandMasterId,
                      (VOID*)pstForeMasterB->szGrandMasterId,
                      TCPIP_PTP_CLOCK_ID_LEN, &lRetResult);
    if (0 == lRetResult)
    {
        ulRet = PTPV2_BMC_DSCA_Part2(ulCompareType, pstForeMasterA, pstForeMasterB, ppstSelectMaster, pbBetter, pbTopoBetter);
        if (TCPIP_PTP_OK != ulRet)/*�������ô�����ѡ���һ��*/
        {
            *ppstSelectMaster = pstForeMasterA;
            goto EXIT_LABEL;
        }
        return ulRet;        
    }
    
    /*Step1:�Ƚ����ȼ�1*/
    /*pstForeMasterAʱ�ӿɽ���master�б��е����ȼ� 1<
     pstForeMasterBʱ�ӿɽ���master�б��е����ȼ�1*/
    if (pstForeMasterA->ucGrandmasterPriority1
        < pstForeMasterB->ucGrandmasterPriority1)
    {
        *ppstSelectMaster = pstForeMasterA;
        goto EXIT_LABEL;
    }
    else if (pstForeMasterA->ucGrandmasterPriority1
             > pstForeMasterB->ucGrandmasterPriority1)
    {
        /*pstForeMasterAʱ�ӿɽ���master�б��е����ȼ� >
         pstForeMasterBʱ�ӿɽ���master�б��е����ȼ�*/
        *ppstSelectMaster = pstForeMasterB;
        goto EXIT_LABEL;
    }

    /*Step2:�Ƚ�ʱ�ӵȼ�*/
    /*���MasterA��MasterB�Ƿ�Ϊ��ѡԴ�ȼ�*/
    lRetResult = PTPV2_CompareClockClass(pstForeMasterA, pstForeMasterB, ppstSelectMaster);
    if (TCPIP_PTP_OK == lRetResult)
    {
        goto EXIT_LABEL;
    }

    /*Step3:�Ƚ�ʱ�Ӿ���*/
    /*pstForeMasterAʱ�Ӿ��� < pstForeMasterBʱ�Ӿ���*/
    if (pstForeMasterA->stGrandmasterClockQuality.ucClockAccuracy
        < pstForeMasterB->stGrandmasterClockQuality.ucClockAccuracy)
    {
        *ppstSelectMaster = pstForeMasterA;
        goto EXIT_LABEL;
    }
    else if (pstForeMasterA->stGrandmasterClockQuality.ucClockAccuracy
             > pstForeMasterB->stGrandmasterClockQuality.ucClockAccuracy)
    {
        /*pstForeMasterAʱ�Ӿ���  > pstForeMasterBʱ�Ӿ���*/
        *ppstSelectMaster = pstForeMasterB;
        goto EXIT_LABEL;
    }

    /*Step4:�Ƚ�ʱ���ȶ���*/
    /*pstForeMasterAʱ���ȶ��� < pstForeMasterBʱ���ȶ���*/
    if (pstForeMasterA->stGrandmasterClockQuality.usOffsetScaledLogVariance
        < pstForeMasterB->stGrandmasterClockQuality.usOffsetScaledLogVariance)
    {
        *ppstSelectMaster = pstForeMasterA;
        goto EXIT_LABEL;
    }
    else if (pstForeMasterA->stGrandmasterClockQuality.usOffsetScaledLogVariance
             > pstForeMasterB->stGrandmasterClockQuality.usOffsetScaledLogVariance)
    {
        /*pstForeMasterAʱ���ȶ��� > pstForeMasterBʱ���ȶ���*/
        *ppstSelectMaster = pstForeMasterB;
        goto EXIT_LABEL;
    }

    /*Step5:�Ƚ�ʱ�����ȼ�2*/
    /*pstForeMasterAʱ���ڿɽ���master�б��е����ȼ�2<
     pstForeMasterBʱ�ӿɽ���master�б��е����ȼ�2*/
    if (pstForeMasterA->ucGrandmasterPriority2
        < pstForeMasterB->ucGrandmasterPriority2)
    {
        *ppstSelectMaster = pstForeMasterA;
        goto EXIT_LABEL;
    }
    else if (pstForeMasterA->ucGrandmasterPriority2
             > pstForeMasterB->ucGrandmasterPriority2)
    {
        /*pstForeMasterAʱ�ӿɽ���master�б��е����ȼ� >
         pstForeMasterBʱ�ӿɽ���master�б��е����ȼ�*/
        *ppstSelectMaster = pstForeMasterB;
        goto EXIT_LABEL;
    }

    /*Step6:�Ƚ�ʱ��ID*/
    /*CLOCK ID�Ƚ�*/
    (VOID)VOS_Mem_Cmp((VOID*)pstForeMasterA->szGrandMasterId,
                      (VOID*)pstForeMasterB->szGrandMasterId,
                      TCPIP_PTP_CLOCK_ID_LEN, &lRetResult);
    if (lRetResult > 0)
    {
        *ppstSelectMaster = pstForeMasterB;
        goto EXIT_LABEL;
    }
    else if (lRetResult < 0)
    {
        *ppstSelectMaster = pstForeMasterA;
        goto EXIT_LABEL;
    }   

    /*ע:����clock id��ͬ�������µıȽϣ������ܷ���,announce���Ľ�����������*/
    *ppstSelectMaster = pstForeMasterA;

EXIT_LABEL:
    *pbBetter = BOOL_TRUE;
    return TCPIP_PTP_OK;
}
ULONG PTPV2_1588_BMC(DLL_S *pstDll, PTPV2_FOREIGN_MASTER_S** pstSelectMaster, BOOL_T bEbest)
{

    PTPV2_FOREIGN_MASTER_S* pstIter = NULL;
    PTPV2_FOREIGN_MASTER_S* pstIterForeMaster = NULL;
    PTPV2_FOREIGN_MASTER_S* pstBmcParent = NULL;
    PTPV2_FOREIGN_MASTER_S* pstTemp = NULL;

    ULONG ulRet = TCPIP_PTP_OK;
    BOOL_T bBetter = BOOL_FALSE;
    BOOL_T bTopoBetter = BOOL_FALSE;

    if (NULL == pstSelectMaster || NULL == pstDll)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    DLL_Scan(pstDll, pstIter, PTPV2_FOREIGN_MASTER_S *)
    {
        /*ָ������ָ���ṹ����ʼλ��,Ebest��Ӧglobal����,Erbest��Ӧ��port����*/
        pstIterForeMaster = bEbest ? (PTPV2_FOREIGN_MASTER_S *)((CHAR *)pstIter - ((CHAR *)&pstIter->stGlobalDllNode - (CHAR *)pstIter))
                                    : (PTPV2_FOREIGN_MASTER_S *)((CHAR *)pstIter - ((CHAR *)&pstIter->stPortDllNode - (CHAR *)pstIter));

        if ((NULL == pstIterForeMaster) || (PTPV2_IS_FOREMASTER_GOT_PTSF(pstIterForeMaster)) 
             || (pstIterForeMaster->ulRecvAnnCount < 2))
        {
            continue;
        }

        if (NULL == pstBmcParent)
        {

            pstBmcParent = pstIterForeMaster;
            continue;
        }

        pstTemp = pstBmcParent;
        
        (VOID)PTPV2_BMC_DSCA_Part1(DSA_COMPAR_TYPE_NO_NEED, pstTemp, pstIterForeMaster, &pstBmcParent, &bBetter, &bTopoBetter);
       
    }

    *pstSelectMaster = pstBmcParent;
    return ulRet;
}

ULONG PTPV2_AddForeignMaster(PTPV2_PORT_S* pstPtpPort, TCPIP_PTP_ADDRINFO_S* pstAddrInfo,
                             PTPV2_FOREIGN_MASTER_S** ppstForeMaster)
{
    PTPV2_FOREIGN_MASTER_S* pstAddForeign = NULL;
    ULONG ulStructLen = sizeof(PTPV2_FOREIGN_MASTER_S);
    ULONG ulRet = TCPIP_PTP_ERR;

    if (NULL == pstAddrInfo || NULL == ppstForeMaster)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    pstAddForeign = (PTPV2_FOREIGN_MASTER_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_FOREIGN_MASTER, ulStructLen);
    if (NULL == pstAddForeign)
    {
        ulRet = TCPIP_PTP_ERR_MALLOC_FAIL;
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27FA, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN,
                         "TCPIP PTPV2 LOG: PTPV2_AddForeignMaster malloc pstAddForeign failed.\r\n",
                         0, 0, 0, 0);
        goto EXIT_LABEL;
    }

    (VOID)TCPIP_Mem_Set((CHAR*)pstAddForeign, 0, ulStructLen);

    /*fill */
    (VOID)TCPIP_Mem_Copy((VOID*) & (pstAddForeign->stForeignMasterPortAddr), sizeof(TCPIP_PTP_PORT_ADDR_S),
                                            (VOID*) & (pstAddrInfo->stSrcPortAddr), sizeof(TCPIP_PTP_PORT_ADDR_S));

    DLL_Add(&g_GlobalForeignMasterList, (DLL_NODE_S*)&(pstAddForeign->stGlobalDllNode));
    DLL_Add(&(pstPtpPort->dllForeignMasterHead), (DLL_NODE_S*)&(pstAddForeign->stPortDllNode));
    pstAddForeign->pstPortInfo = pstPtpPort;
    pstAddForeign->ulRcvIfIndex = pstAddrInfo->ulIfIndex;/*��д��ӿ�����*/
    pstAddForeign->ulRecvAnnCount++; /*�յ���һ��ann����ʱ����foremaster*/

    *ppstForeMaster = pstAddForeign;
    ulRet = TCPIP_PTP_OK;

EXIT_LABEL:

    return ulRet;
}

ULONG PTPV2_GetForeignMasterByAddr(TCPIP_PTP_PORT_ADDR_S* pstAddrInfo,
                                   PTPV2_FOREIGN_MASTER_S** ppstForeMaster)
{
    PTPV2_FOREIGN_MASTER_S* pstIter = NULL;
    PTPV2_FOREIGN_MASTER_S* pstIterForeMaster = NULL;
    LONG lCmp = -1L;
    ULONG ulRet = TCPIP_PTP_ERR;

    if (NULL == pstAddrInfo || NULL == ppstForeMaster)
    {
        return TCPIP_PTP_ERR_POINTER_NULL;
    }

    DLL_Scan(&g_GlobalForeignMasterList, pstIter, PTPV2_FOREIGN_MASTER_S *)
    {
        /*ָ������ָ���ṹ����ʼλ��*/
        pstIterForeMaster = (PTPV2_FOREIGN_MASTER_S *)((CHAR *)pstIter - ((CHAR *)&pstIter->stGlobalDllNode - (CHAR *)pstIter));

        /*ԭ�жϴ�������*/
        if ((TCPIP_PTP_PROTOCAL_IEEE_802 == pstAddrInfo->usNetworkProtocol) && 
                (PTPV2_MACADDRLEN == pstAddrInfo->usAddressLength))
        {
            (VOID)VOS_Mem_Cmp((VOID *)pstAddrInfo->unAddr.ucMacAddr, 
                              (VOID *)pstIterForeMaster->stForeignMasterPortAddr.unAddr.ucMacAddr,
                               PTPV2_MACADDRLEN, &lCmp);
            if (0 == lCmp)
            {
                *ppstForeMaster = pstIterForeMaster;
                ulRet = TCPIP_PTP_OK;
                break;
            }
        }
    }

    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPV2_DelForeignMaster
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description:  ɾ������master
*        Input: PTPV2_FOREIGN_MASTER_S* pstDelForeMaster:
*       Output:
*       Return:
*      Caution:
*              ����ʱ��:1�� announce���ճ�ʱ��Ӧ��ɾ������master
*                       2�� ɾ���˿�
*                       3�� ж��PTPģ��
*             ɾ������master: a. ɾ����ʱ�� b. ��ȫ��������ɾ�� c.�Ӷ˿�������ɾ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_DelForeignMaster(PTPV2_FOREIGN_MASTER_S* pstDelForeMaster)
{
    PTPV2_PORT_S* pstPortInfo = NULL;

    VOS_DBGASSERT(NULL != pstDelForeMaster);

    pstPortInfo = pstDelForeMaster->pstPortInfo;

    VOS_DBGASSERT(NULL != pstPortInfo);

    /*Foremaster Debug��Ϣ*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_FOREMASTER)
    {
        TCPIP_InfoOutput("\r\ndel foremaster:");

        PTPV2_ForeMasterPrint(pstDelForeMaster);
    }

    if (g_pstBmcEbest == pstDelForeMaster)/*��ǰɾ����==ѡ�е�ʱ��Դ*/
    {
        (VOID)PTPV2_BMC_PPI_SlaveRole(pstDelForeMaster, TCPIP_PTP_PPI_DEL, TCPIP_PTP_PARA_CHANGE_FIELD_NONE);
        g_pstBmcEbest = NULL;        
    }

    /*ɾ������ʱ��Դ: ���ն�ʱ�� &  ��ȫ������ɾ�� & �Ӷ˿�������ɾ��*/
    (VOID)PTPV2_DeleteLogicTimer(pstDelForeMaster->ulAnnRcvTimerId);
    DLL_Delete(&g_GlobalForeignMasterList, (DLL_NODE_S*)&pstDelForeMaster->stGlobalDllNode);
    DLL_Delete(&(pstPortInfo->dllForeignMasterHead), (DLL_NODE_S*)&pstDelForeMaster->stPortDllNode);
    (VOID)TCPIP_Free(pstDelForeMaster);
    return TCPIP_PTP_OK;
}

ULONG PTPV2_DelForeignMaster_ByAddrr(TCPIP_PTP_PORT_ADDR_S* pstAddrInfo)
{
    PTPV2_FOREIGN_MASTER_S* pstIter = NULL;
    PTPV2_FOREIGN_MASTER_S* pstIterForeMaster = NULL;
    LONG lCmp = -1;
    ULONG ulRet = TCPIP_PTP_ERR;
    PTPV2_PORT_S* pstPortInfo = NULL;

    DLL_Scan(&g_GlobalForeignMasterList, pstIter, PTPV2_FOREIGN_MASTER_S *)
    {
        /*ָ������ָ���ṹ����ʼλ��*/
        pstIterForeMaster = (PTPV2_FOREIGN_MASTER_S *)((CHAR *)pstIter - ((CHAR *)&pstIter->stGlobalDllNode - (CHAR *)pstIter));

        (VOID)VOS_Mem_Cmp(pstAddrInfo, &(pstIterForeMaster->stForeignMasterPortAddr), sizeof(TCPIP_PTP_PORT_ADDR_S), &lCmp);
        if (0 == lCmp)
        {
            pstPortInfo = pstIterForeMaster->pstPortInfo;

            /*Foremaster Debug��Ϣ*/
            if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_FOREMASTER)
            {
                TCPIP_InfoOutput("\r\ndel foremaster:");

                PTPV2_ForeMasterPrint(pstIterForeMaster);
            }

            DLL_Delete(&g_GlobalForeignMasterList, (DLL_NODE_S*)&pstIterForeMaster->stGlobalDllNode);
            DLL_Delete(&(pstPortInfo->dllForeignMasterHead), (DLL_NODE_S*)&pstIterForeMaster->stPortDllNode);
            (VOID)TCPIP_Free(pstIterForeMaster);

            ulRet = TCPIP_PTP_OK;
            break;
        }
    }

    return ulRet;
}

ULONG PTPV2_Update_ForeignMasterPara(PTPV2_PORT_S* pstPtpPort, PTPV2_FOREIGN_MASTER_S* pstForeMaster,
                                     PTPV2_ANNOUNCE_MSG_S* pstAnnMsg, TCPIP_PTP_ADDRINFO_S* pstAddrInfo)
{
    pstForeMaster->cLogMAnnInterval = pstAnnMsg->stMsgHeader.cLogMessageInterval;
    /*ANN���ճ�ʱ��������*/
    pstForeMaster->ulAnnRcvTimerCount = 0;
    VOS_CopyVar(pstForeMaster->stGrandmasterClockQuality, pstAnnMsg->stGrandmasterClockQuality);
    pstForeMaster->stGrandmasterClockQuality.usOffsetScaledLogVariance = 
        VOS_NTOHS(pstAnnMsg->stGrandmasterClockQuality.usOffsetScaledLogVariance);
    pstForeMaster->ucGrandmasterPriority1 = pstAnnMsg->ucGrandmasterPriority1;
    pstForeMaster->ucGrandmasterPriority2 = pstAnnMsg->ucGrandmasterPriority2;
    pstForeMaster->ucFlagField[0] = pstAnnMsg->stMsgHeader.ucflagField[0];
    pstForeMaster->ucFlagField[1] = pstAnnMsg->stMsgHeader.ucflagField[1];
    pstForeMaster->ucTimeSource = pstAnnMsg->ucTimeSource;
    pstForeMaster->usStepsRemoved = VOS_NTOHS(pstAnnMsg->usStepsRemoved);

    (VOID)TCPIP_Mem_Copy((VOID*)(pstForeMaster->szGrandMasterId), TCPIP_PTP_CLOCK_ID_LEN,(VOID*)(pstAnnMsg->stGrandmasterIdentity), TCPIP_PTP_CLOCK_ID_LEN);
    (VOID)TCPIP_Mem_Copy((VOID*)(&(pstForeMaster->stForeignMasterPortAddr)), sizeof(TCPIP_PTP_PORT_ADDR_S),(VOID*)(&(pstAddrInfo->stSrcPortAddr)),
                       sizeof(TCPIP_PTP_PORT_ADDR_S));
    (VOID)TCPIP_Mem_Copy((VOID*)(&(pstForeMaster->szForeignMasterPortId)),sizeof(TCPIP_PTP_PORT_ID_S), (VOID*)(&(pstAnnMsg->stMsgHeader.stSourcePortIdentity)),
                       sizeof(TCPIP_PTP_PORT_ID_S));
    pstForeMaster->szForeignMasterPortId.usPortNumber = VOS_NTOHS(pstAnnMsg->stMsgHeader.stSourcePortIdentity.usPortNumber);

    pstForeMaster->sCurrentUtcOffset = VOS_NTOHS(pstAnnMsg->sCurrentUtcOffset);

    /*����announce���ĵ����к�*/
    pstForeMaster->usRcvAnnSequenceId = VOS_NTOHS(pstAnnMsg->stMsgHeader.usSequenceId);

    return TCPIP_PTP_OK;
}

/*******************************************************************************
*    Func Name: PTPV2_BMCPreProcess
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description:  BMC ѡԴ��Ԥ����
*        Input: PTPV2_PORT_S* pstPortInfo:
*               PTPV2_ANNOUNCE_MSG_S* pstAnnMsg:
*               TCPIP_PTP_ADDRINFO_S* pstAddrInfo:
*       Output:
*       Return:
*      Caution:
1����ѯforegin master�Ƿ���ڣ���������²���(������һ��master�Ӷ������ڽ���
   port id����仯�������ģ�ֱ����ʱɾ��foreign matser
2��������,�򴴽�һ���µ�foreign master
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_BMCPreProcess(PTPV2_PORT_S* pstPortInfo, PTPV2_ANNOUNCE_MSG_S* pstAnnMsg, TCPIP_PTP_ADDRINFO_S* pstAddrInfo)
{
    PTPV2_FOREIGN_MASTER_S* pstFind = NULL;
    PTPV2_FOREIGN_MASTER_S* pstAddForeign = NULL;
    ULONG ulRet = TCPIP_PTP_ERR;
    ULONG ulMaxCfgMasterNum = 0;
    ULONG ulCurrentMasterNum = 0;
    ULONG ulPeriod = 0;
    LONG lRet = 0;

    if (NULL == pstPortInfo || NULL == pstPortInfo->pstSubPortInfo
        || NULL == pstAnnMsg || NULL == pstAddrInfo)
    {
        return TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
    }

    /*����port id ���� foreign master�Ƿ��Ѿ�����*/
    ulRet = PTPV2_GetForeignMasterByPortId(&(pstAnnMsg->stMsgHeader), &pstFind);
    if (TCPIP_PTP_OK == ulRet)
    {
        /*��֧��ͬһ��matser�ı��Ĵӱ��˶������ڽ���*/
        if (pstAddrInfo->ulIfIndex != pstFind->ulRcvIfIndex)
        {
            /*��֧����������*/
            /*����ͳ��*/
            g_stGlobalPtpV2PktStat.ulRcvErrorIfPackets ++;

            return TCPIP_PTP_ERR_INVALID_RCVINDEX;
        }

        /*clock id��port no�仯���������ģ�ֱ�����ճ�ʱ��ɾ������Դ*/
        (VOID)VOS_Mem_Cmp((void*)(&(pstFind->szForeignMasterPortId)),
                          (void*)(pstAnnMsg->stMsgHeader.stSourcePortIdentity.szClockId), sizeof(TCPIP_PTP_CLOCK_ID_SZ), &lRet);
        if (0 != lRet)
        {
            return TCPIP_PTP_ERR_PORTID;
        }

        /*������ת����Ϊ2(����Ӱ�����ѡԴ),��������1*/
        if (0xFFFFFFFF == pstFind->ulRecvAnnCount)
        {
            pstFind->ulRecvAnnCount = 2;
        }
        else
        {
            pstFind->ulRecvAnnCount++;
        }

        /*���� master�ĵ�ַ��ʱ�Ӳ���*/
        (VOID)PTPV2_Update_ForeignMasterPara(pstPortInfo, pstFind, pstAnnMsg, pstAddrInfo);
        return ulRet;
    }

    (VOID)PTPV2_GetGlobalInfo(PTPV2_CMD_MASTER_NUM_LIMIT, &ulMaxCfgMasterNum);
    (VOID)PTPV2_GetGlobalInfo(PTPV2_CMD_CURRENT_MASTER_NUMS, &ulCurrentMasterNum);

    if (ulCurrentMasterNum >= ulMaxCfgMasterNum)/*�ﵽ�������ֵ*/
    {
        /*���������滻�����Ǹ�ʱ��Դ*/
        return TCPIP_PTP_ERR_MASTER_UP_MAX;
    }

    /*û���ҵ�������*/
    ulRet = PTPV2_AddForeignMaster(pstPortInfo, pstAddrInfo, &pstAddForeign);
    if (TCPIP_PTP_OK != ulRet)
    {
        return ulRet;
    }

    /*����*/
    (VOID)PTPV2_Update_ForeignMasterPara(pstPortInfo, pstAddForeign, pstAnnMsg, pstAddrInfo);/*����master����*/

    /*�������ն�ʱ��*/
    PTPV2_CAL_LOG_TO_MILL(pstAddForeign->cLogMAnnInterval, ulPeriod);
    if (0 == ulPeriod)
    {
        ulPeriod = 2000;
    }

    ulRet = PTPV2_CreateLogicTimer(ulPeriod, PTPV2_AnnRcvTimerOut, pstAddForeign, &pstAddForeign->ulAnnRcvTimerId);
    if (TCPIP_PTP_OK != ulRet)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_27FB, TCPIP_LOG_LEVEL_WARNING, LOG_TYPE_RUN,
                         "TCPIP PTP LOG:Create Accept Master Detect Timer Failed, Period:%u\r\n", ulPeriod, 0, 0, 0);
    }

    /*Foremaster Debug��Ϣ*/
    if (g_ulPtpV2GlobalDbgSwitch & TCPIP_PTP_DEBUG_FOREMASTER)
    {
        TCPIP_InfoOutput("\r\nadd foremaster:");

        PTPV2_ForeMasterPrint(pstAddForeign);
    }

    return ulRet;
}

/*******************************************************************************
*    Func Name: PTPV2_BMCProcess
* Date Created: 2014-03-24
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: PTPV2_FOREIGN_MASTER_S** pstSelectMaster:
*       Output:
*       Return:
*      Caution:
*       ѡԴʱ��:1 �յ�announce����  2 announce���ճ�ʱ  3 ɾ���˿�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-24   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_BMCProcess(PTPV2_FOREIGN_MASTER_S** ppstSelectMaster)
{
    ULONG ulBmcPolicy = 0;
    ULONG ulRet = TCPIP_PTP_ERR;
    ulRet = PTPV2_GetGlobalInfo(PTPV2_CMD_BMC_POLICY, &ulBmcPolicy);
    if (TCPIP_PTP_OK != ulRet)
    {
        return ulRet;
    }

    switch (ulBmcPolicy)
    {
        case TCPIP_PTP_BMC_POLICY_1588:
            (VOID)PTPV2_1588_BMC(&g_GlobalForeignMasterList, ppstSelectMaster, BOOL_TRUE);
            break;
        default:
            break;
    }

    return ulRet;

}


ULONG PTPV2_BMCNotify(PTPV2_FOREIGN_MASTER_S* pstSelectMaster)
{
    ULONG ulChangeField = TCPIP_PTP_PARA_CHANGE_FIELD_NONE;

    if (PTPV2_NO == PTPV2_HaveParent())
    {
        /*1.1 ��ǰû��ʱ��Դ  & ����Ҳû��ѡ�У���ʲô��������
          1.2 ��ǰû��ʱ��Դ  & ����ѡ���ˣ���ADD
        */
        if (NULL != pstSelectMaster)
        {
            g_pstBmcEbest = pstSelectMaster;

            /* ��ѡ��Դ����Ϣ�洢��ParentDs */
            PTPV2_UpdateParentDS(g_pstBmcEbest, NULL);

            /*Ebest���,��Ҫ���¾�������,���߶˿ڵ�״̬�ͽ�ɫ,��֤������·���Ϣ��ȷ*/
            (VOID)PTPV2_BMC_SDAProcess();

            /*֪ͨ����passive�˿ڵ�״̬*/
            PTPV2_BMC_PPI_PassiveRoleForAll();

            /*֪ͨslave�˿ڵ�״̬*/
            (VOID)PTPV2_BMC_PPI_SlaveRole(g_pstBmcEbest, TCPIP_PTP_PPI_ADD, TCPIP_PTP_PARA_CHANGE_FIELD_NONE);

            /*��һ��ѡ��ʱ��Դ�������ñ�ǣ��˱�ǽ�����һ��*/
            if (PTPV2_NO == g_ucPtpGotTimeSourceFlag)
            {
                g_ucPtpGotTimeSourceFlag = PTPV2_YES;
            }

            /*�澯�������*/
            PTPV2_WarningRemoveProc();
        }
    }
    else /*��ǰ�Ѿ���ʱ��Դ*/
    {
        /*2.1 ��ǰ��ʱ��Դ & ����û��ѡ�� ����ɾ����һ�ε�ʱ��Դ
          2.2 ��ǰ��ʱ��Դ & ����ѡ�� ==  ��ǰ��,������
          2.3 ��ǰ��ʱ��Դ & ����ѡ�� != ��ǰ�ģ���DEL ����ADD
        */
        if (NULL == pstSelectMaster)
        {
            (VOID)PTPV2_BMC_PPI_SlaveRole(g_pstBmcEbest, TCPIP_PTP_PPI_DEL, TCPIP_PTP_PARA_CHANGE_FIELD_NONE);
            g_pstBmcEbest = NULL;

            /*Ebest��ʧ,����Դ���,������BMC����,�����ɫ��״̬���ܲ�׼*/
            (VOID)PTPV2_BMC_SDAProcess();
            
            /*֪ͨ����passive�˿ڵ�״̬*/
            PTPV2_BMC_PPI_PassiveRoleForAll();
            
            /*�����澯��ʱ��*/
            (VOID)PTPV2_CreateWarningTimer();
        }
        else if (g_pstBmcEbest != pstSelectMaster)
        {
            (VOID)PTPV2_BMC_PPI_SlaveRole(g_pstBmcEbest, TCPIP_PTP_PPI_DEL, TCPIP_PTP_PARA_CHANGE_FIELD_NONE);

            g_pstBmcEbest = pstSelectMaster;

            /* ��ѡ��Դ����Ϣ�洢��ParentDs */
            PTPV2_UpdateParentDS(g_pstBmcEbest, NULL);

            /*��Դ,��Ҫ���¾�������,���߶˿ڵ�״̬�ͽ�ɫ,��֤������·���Ϣ��ȷ*/
            (VOID)PTPV2_BMC_SDAProcess();

             /*֪ͨ����passive�˿ڵ�״̬*/
            PTPV2_BMC_PPI_PassiveRoleForAll();

            (VOID)PTPV2_BMC_PPI_SlaveRole(g_pstBmcEbest, TCPIP_PTP_PPI_ADD, TCPIP_PTP_PARA_CHANGE_FIELD_NONE);

            /*�澯�������*/
            PTPV2_WarningRemoveProc();
        }
        /*��ѡ�е�Դ��ԭ�е�Դ��ͬ*/
        else
        {
            /*����ѡ��Դ����Ϣ������ParentDs */
            PTPV2_UpdateParentDS(g_pstBmcEbest, &ulChangeField);

            /*Դ��Ϣ���,�˿ڵ�״̬�ͽ�ɫ����Ҫ��,���߾�������*/
            (VOID)PTPV2_BMC_SDAProcess();

             /*֪ͨ����passive�˿ڵ�״̬*/
            PTPV2_BMC_PPI_PassiveRoleForAll();

            /*Դ���������˱仯*/
            if (TCPIP_PTP_PARA_CHANGE_FIELD_NONE != ulChangeField)
            {
                 (VOID)PTPV2_BMC_PPI_SlaveRole(g_pstBmcEbest, TCPIP_PTP_PPI_UPDATE, ulChangeField);
            }
        }
    }

    return TCPIP_PTP_OK;
}

/******************************************************************************
*Func Name   : PTPV2_ForeMasterPrint
*Description : ForeMaster��Ϣ��ӡ�ӿ�
*Input       : PTPV2_FOREIGN_MASTER_S *pstForeMaster
*Output      : 
*Return      : 
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-05-14           dutianyi       Create
*  2014-11-07           heyijun        Add PtsfSync to display
*******************************************************************************/
VOID PTPV2_ForeMasterPrint(PTPV2_FOREIGN_MASTER_S *pstForeMaster)
{
    CHAR szBuf[LEN_512] = {0};      /* ����������512���ֽڣ���ű�����Ϣ */
    INT32 i32Offset = 0;

    if (NULL == pstForeMaster)
    {
        return;
    }

    (VOID)TCPIP_SNPRINTF0(szBuf, LEN_512, 
                             P8("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u",
                             "PortNo", pstForeMaster->pstPortInfo->pstSubPortInfo->usPortNo,
                             "ForeMasterPortNo", pstForeMaster->szForeignMasterPortId.usPortNumber,
                             "GrandmasterPriority1", pstForeMaster->ucGrandmasterPriority1,
                             "GrandmasterPriority2", pstForeMaster->ucGrandmasterPriority2));

    TCPIP_InfoOutput(szBuf);

    (VOID)TCPIP_SNPRINTF0(szBuf, LEN_512, 
                            P9("\r\n %30s : %02x%02x%02x%02x%02x%02x%02x%02x",
                            "Foreign Master Clock Id",
                            pstForeMaster->szForeignMasterPortId.szClockId[0],
                            pstForeMaster->szForeignMasterPortId.szClockId[1],
                            pstForeMaster->szForeignMasterPortId.szClockId[2],
                            pstForeMaster->szForeignMasterPortId.szClockId[3],
                            pstForeMaster->szForeignMasterPortId.szClockId[4],
                            pstForeMaster->szForeignMasterPortId.szClockId[5],
                            pstForeMaster->szForeignMasterPortId.szClockId[6],
                            pstForeMaster->szForeignMasterPortId.szClockId[7]));

    TCPIP_InfoOutput(szBuf);

    i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512, 
                             P8("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %d",
                             "FlagField0", pstForeMaster->ucFlagField[0],
                             "FlagField1", pstForeMaster->ucFlagField[1],
                             "TimeSource", pstForeMaster->ucTimeSource,
                             "LogMAnnInterval", pstForeMaster->cLogMAnnInterval));

    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, 
                             P8("\r\n %30s : %d \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u",
                             "CurrentUtcOffset", pstForeMaster->sCurrentUtcOffset,
                             "ClockAccuracy", pstForeMaster->stGrandmasterClockQuality.ucClockAccuracy,
                             "ClockClass", pstForeMaster->stGrandmasterClockQuality.ucClockClass,
                             "OffsetScaledLogVariance", pstForeMaster->stGrandmasterClockQuality.usOffsetScaledLogVariance));

    TCPIP_InfoOutput(szBuf);

    i32Offset = TCPIP_SNPRINTF0(szBuf, LEN_512, 
                            P9("\r\n %30s : %02x%02x%02x%02x%02x%02x%02x%02x",
                            "Grand Master Clock Id",
                            pstForeMaster->szGrandMasterId[0],
                            pstForeMaster->szGrandMasterId[1],
                            pstForeMaster->szGrandMasterId[2],
                            pstForeMaster->szGrandMasterId[3],
                            pstForeMaster->szGrandMasterId[4],
                            pstForeMaster->szGrandMasterId[5],
                            pstForeMaster->szGrandMasterId[6],
                            pstForeMaster->szGrandMasterId[7]));

    (VOID)TCPIP_SNPRINTF(szBuf + i32Offset, LEN_512 - i32Offset, 
                             P14("\r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n %30s : %u \r\n",
                             "RcvIfIndex", pstForeMaster->ulRcvIfIndex,
                             "AnnRcvTimerId", pstForeMaster->ulAnnRcvTimerId,
                             "AnnRcvTimerCount", pstForeMaster->ulAnnRcvTimerCount,
                             "RcvAnnSequenceId", pstForeMaster->usRcvAnnSequenceId,
                             "StepsRemoved", pstForeMaster->usStepsRemoved,
                             "PtsfSync", pstForeMaster->ulPtsfSync,
                             "RecvAnnCount",pstForeMaster->ulRecvAnnCount));

    TCPIP_InfoOutput(szBuf);

    return;
}
VOID PTPV2_BMC_SDAProcess(VOID)
{
    ULONG ulIter = 0;
    PTPV2_PORT_S *pstPtpPortInfo = NULL;
    PTPV2_FOREIGN_MASTER_S *pstErbest = NULL;
    UCHAR ucSelectPortFsmState = 0;
    UCHAR ucPortRole = 0;
    
    /*1.�������е�PTP �˿�
      2.���ÿ���˿�r����ѡ��Erbest
      3.Ȼ�����<D0,Erbest,Ebest>ѡ��ÿ���˿ڵ�״̬��ɫ
    */
    for(ulIter = PTPV2_MIN_PORTNO ; ulIter < PTPV2_MAX_PORTNO + 1; ulIter ++)
    {
        pstPtpPortInfo = (PTPV2_PORT_S *)(g_pstPortManageInfo->ulPortInfoHandle[ulIter]);

        /*PTP�˿���Ϣ�������򷵻�ʧ��*/
        if (NULL == pstPtpPortInfo || NULL == pstPtpPortInfo->pstSubPortInfo
            || (PTPV2_NO == pstPtpPortInfo->pstSubPortInfo->ucWorkState))
        {
            continue;
        }

        (VOID)PTPV2_1588_BMC(&(pstPtpPortInfo->dllForeignMasterHead), &pstErbest, BOOL_FALSE);/*ѡ��Erbest*/
        /*ѡ���˿�r��״̬*/
        ucSelectPortFsmState = PTPV2_BMC_SDAForPort(pstPtpPortInfo, g_pstVirtualD0, pstErbest, g_pstBmcEbest);

        /*���±��˿ڵ�״̬����Ϣ*/
        PTPV2_Set_FsmState(pstPtpPortInfo->pstSubPortInfo,ucSelectPortFsmState);

        /*���ö˿ڵĽ�ɫ��Ϣ*/
        ucPortRole = PTPV2_GetPortRoleByFsmState(ucSelectPortFsmState);
        PTPV2_Set_PortRole(pstPtpPortInfo->pstSubPortInfo, ucPortRole);        
    }

}
VOID PTPV2_UpdateVirtualD0()
{    
     if (NULL == g_pstVirtualD0)
     {
         return;
     }
    
    (VOID)TCPIP_Mem_Copy((VOID*)(g_pstVirtualD0->szGrandMasterId), sizeof(TCPIP_PTP_CLOCK_ID_SZ),
                         (VOID*)(g_pstPtpGlobalInfo->szClockId), sizeof(TCPIP_PTP_CLOCK_ID_SZ));

    (VOID)TCPIP_Mem_Copy((VOID*)&(g_pstVirtualD0->szForeignMasterPortId), sizeof(TCPIP_PTP_PORT_ID_S),
                         (VOID*)(g_pstPtpGlobalInfo->szClockId),sizeof(TCPIP_PTP_CLOCK_ID_SZ));

    g_pstVirtualD0->sCurrentUtcOffset = g_pstPtpGlobalInfo->stCfgDefaultDs.sCurrentUtcOffset;
    
    return;
}



PTPV2_FOREIGN_MASTER_S *PTPV2_CreateVirtualD0()
{    
    PTPV2_FOREIGN_MASTER_S *pstVirtualD0 = NULL;
    pstVirtualD0 =  (PTPV2_FOREIGN_MASTER_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_FOREIGN_MASTER, sizeof(PTPV2_FOREIGN_MASTER_S));
    if (NULL == pstVirtualD0)
    { 
       goto EXIT_LABEL;
    }

    (VOID)TCPIP_Mem_Set((CHAR *)pstVirtualD0, 0, sizeof(PTPV2_FOREIGN_MASTER_S));
    pstVirtualD0->pstPortInfo = (PTPV2_PORT_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_PORTINFO, sizeof(PTPV2_PORT_S));
    if (NULL == pstVirtualD0->pstPortInfo)
    {
        (VOID)TCPIP_Free(pstVirtualD0);
        pstVirtualD0 = NULL;
        goto EXIT_LABEL;
    }

    (VOID)TCPIP_Mem_Set((CHAR *)pstVirtualD0->pstPortInfo, 0, sizeof(PTPV2_PORT_S));
    pstVirtualD0->pstPortInfo->pstSubPortInfo = (PTPV2_PORT_SUB_INFO_S*)TCPIP_Malloc(PTPV2_MID | SID_PTP_SUBPORTINFO, sizeof(PTPV2_PORT_SUB_INFO_S));
    if (NULL == pstVirtualD0->pstPortInfo->pstSubPortInfo)
    {
        (VOID)TCPIP_Free(pstVirtualD0->pstPortInfo);
        (VOID)TCPIP_Free(pstVirtualD0);
        pstVirtualD0 = NULL;
        goto EXIT_LABEL;
    }
    
    (VOID)TCPIP_Mem_Set((CHAR *)pstVirtualD0->pstPortInfo->pstSubPortInfo, 0, sizeof(PTPV2_PORT_SUB_INFO_S));    
        
    pstVirtualD0->ucGrandmasterPriority1 = 0x80;    
    pstVirtualD0->ucGrandmasterPriority2 = 0x80;    
    pstVirtualD0->usStepsRemoved = 0;
    pstVirtualD0->pstPortInfo->pstSubPortInfo->usPortNo = 0;

    /*D0��ʱ�������̶�,Ϊ���ֵ*/
    pstVirtualD0->stGrandmasterClockQuality.ucClockClass = 0xF8;
    pstVirtualD0->stGrandmasterClockQuality.ucClockAccuracy = 0xFE;
    pstVirtualD0->stGrandmasterClockQuality.usOffsetScaledLogVariance = 0xFFFF;

EXIT_LABEL:
    if (NULL == pstVirtualD0)
    {
        TCPIP_LOG_FIXLEN(RUN_LOG_VISP_02CA, TCPIP_LOG_LEVEL_CRITICAL, LOG_TYPE_RUN,
             "TCPIP PTPV2 LOG: PTPV2_CreateVirtualD0 malloc failed.\r\n", 0, 0, 0, 0);
    }

    return pstVirtualD0;
}
VOID PTPV2_FreeVirtualD0()
{
    if (NULL == g_pstVirtualD0)
    {
        return;
    }

    (VOID)TCPIP_Free(g_pstVirtualD0->pstPortInfo->pstSubPortInfo);
    (VOID)TCPIP_Free(g_pstVirtualD0->pstPortInfo);
    (VOID)TCPIP_Free(g_pstVirtualD0);
    g_pstVirtualD0 = NULL;

    return ;
}


UCHAR PTPV2_BMC_SDAForPort(PTPV2_PORT_S* pstPortInfo,
                                          PTPV2_FOREIGN_MASTER_S *pstVirutalD0,
                                          PTPV2_FOREIGN_MASTER_S *pstErbest, 
                                          PTPV2_FOREIGN_MASTER_S *pstEbest)
{

    /*״̬�����㷨˵��:
    <Do,Erbest,Ebest>��Ϊ����������ѡ��˿�r�Ľ�ɫ

    1.DO��class��1-127


    */
    BOOL_T bBetter = BOOL_FALSE;
    BOOL_T bTopoBetter = BOOL_FALSE;
    PTPV2_FOREIGN_MASTER_S *pstBmcResult = NULL;
    
    /*pstErbest/pstEbest����ΪNULL
      pstPortInfo/pstVirutalD0 ������ΪNULL 
    */
    if (NULL == pstPortInfo || NULL == pstVirutalD0)
    {
        return PTPV2_PORT_FSM_LISTENING;
    }   

    /*�˿�Ϊlistening &&  no master*/
    if ((PTPV2_PORT_FSM_LISTENING == pstPortInfo->pstSubPortInfo->ucPtpPortFsmState)
        &&(0 == pstPortInfo->dllForeignMasterHead.u4_Count))
    {
        return PTPV2_PORT_FSM_LISTENING;
    }    
    
    if ((pstVirutalD0->stGrandmasterClockQuality.ucClockClass >= 1)
        &&(pstVirutalD0->stGrandmasterClockQuality.ucClockClass <= 127))
    {
        (VOID)PTPV2_BMC_DSCA_Part1(DSA_COMPAR_TYPE_DO_WITH_ERBEST, pstVirutalD0, pstErbest, &pstBmcResult, &bBetter, &bTopoBetter);
        if (NULL == pstErbest || pstBmcResult == pstVirutalD0)/*ѡ������ D0����*/
        {
            return PTPV2_PORT_FSM_MASTER;
        }
        
        return PTPV2_PORT_FSM_PASSIVE;
    }

    /*D0 class ����1-127֮�䣬��..... D0  Ebest*/
    pstBmcResult = NULL;
    bBetter = BOOL_FALSE;
    bTopoBetter = BOOL_FALSE;
    (VOID)PTPV2_BMC_DSCA_Part1(DSA_COMPAR_TYPE_DO_WITH_EBEST, pstVirutalD0, pstEbest, &pstBmcResult, &bBetter, &bTopoBetter);
    if (NULL == pstEbest || pstBmcResult == pstVirutalD0)
    {
        return PTPV2_PORT_FSM_MASTER;
    }

    if (pstErbest == pstEbest)
    {
        return PTPV2_PORT_FSM_SLAVE;
    }

    /*�Ƚ�Ebest��Erbest,set to passive state only if Ebest better by topology.
     *Ebest must is not null, Erbest maybe is null ,if Erbest is null, this port as master state
    */
    pstBmcResult = NULL;
    bBetter = BOOL_FALSE;
    bTopoBetter = BOOL_FALSE;
    (VOID)PTPV2_BMC_DSCA_Part1(DSA_COMPAR_TYPE_EBEST_WITH_ERBEST, pstEbest, pstErbest, &pstBmcResult, &bBetter, &bTopoBetter);
    /*���˸��ţ��ҷ�������Ebest������passive*/
    if ((BOOL_TRUE == bTopoBetter) && (pstBmcResult == pstEbest))
    {
        return PTPV2_PORT_FSM_PASSIVE;
    }

    return PTPV2_PORT_FSM_MASTER;
}
ULONG PTPV2_BMC_DSCA_Part2(ULONG ulCompareType, 
                                PTPV2_FOREIGN_MASTER_S* pstForeMasterA,
                                PTPV2_FOREIGN_MASTER_S* pstForeMasterB,
                                PTPV2_FOREIGN_MASTER_S** ppstSelectMaster,
                                BOOL_T* pbBetter, BOOL_T* pbTopoBetter)
{
    LONG                   lRet = 0;
    TCPIP_PTP_PORT_ID_S    stReceiverIdA;
    TCPIP_PTP_PORT_ID_S    stReceiverIdB;

    if (NULL == pstForeMasterA || NULL == pstForeMasterB || NULL == ppstSelectMaster)        
    {
        return TCPIP_PTP_ERR_POINTER_NULL;    
    }

    (VOID)TCPIP_Mem_Set((VOID*)&stReceiverIdA, 0, sizeof(TCPIP_PTP_PORT_ID_S));
    (VOID)TCPIP_Mem_Set((VOID*)&stReceiverIdB, 0, sizeof(TCPIP_PTP_PORT_ID_S));

    /*Step8:�Ƚ�stepsRemoved,A��B�Ĳ�����1,DataSet��stepsRemovedΪ0,����ΪԴ����*/
    if (pstForeMasterA->usStepsRemoved + 1 < pstForeMasterB->usStepsRemoved)
    {
        *ppstSelectMaster = pstForeMasterA;
        *pbBetter = BOOL_TRUE;
        return TCPIP_PTP_OK;
    }
    else if (pstForeMasterA->usStepsRemoved > pstForeMasterB->usStepsRemoved + 1)
    {       
        *ppstSelectMaster = pstForeMasterB;
        *pbBetter = BOOL_TRUE;
        return TCPIP_PTP_OK;
    }

    /*Step9:�Ƚ�stepsRemoved,A��B�Ĳ��С�ڵ���1,��ȷ��A/B��receiver*/
    switch (ulCompareType)
    {
        case DSA_COMPAR_TYPE_DO_WITH_ERBEST:
        case DSA_COMPAR_TYPE_DO_WITH_EBEST:
            /*D0��receiverȡ����clockid,portnum=0*/
            (VOID)TCPIP_Mem_Copy((VOID*)&stReceiverIdA,sizeof(TCPIP_PTP_PORT_ID_S),
                                 (VOID*)(g_pstPtpGlobalInfo->szClockId),sizeof(TCPIP_PTP_CLOCK_ID_SZ));
            stReceiverIdA.usPortNumber = 0;
            
            /*Erbest/Ebest��receiver������Ebest*/
            (VOID)TCPIP_Mem_Copy((VOID*)&stReceiverIdB,sizeof(TCPIP_PTP_PORT_ID_S),
                                 (VOID*)&(g_pstBmcEbest->szForeignMasterPortId),sizeof(TCPIP_PTP_PORT_ID_S));
            break;
        case DSA_COMPAR_TYPE_EBEST_WITH_ERBEST:
            /*Erbest/Ebest��receiver������Ebest*/
            (VOID)TCPIP_Mem_Copy((VOID*)&stReceiverIdA,sizeof(TCPIP_PTP_PORT_ID_S),
                                 (VOID*)&(g_pstBmcEbest->szForeignMasterPortId),sizeof(TCPIP_PTP_PORT_ID_S));
            (VOID)TCPIP_Mem_Copy((VOID*)&stReceiverIdB,sizeof(TCPIP_PTP_PORT_ID_S),
                                 (VOID*)&(g_pstBmcEbest->szForeignMasterPortId),sizeof(TCPIP_PTP_PORT_ID_S));
            break;
         default:
            /*Ĭ��������clockid,portnum = 0*/
            (VOID)TCPIP_Mem_Copy((VOID*)&stReceiverIdA,sizeof(TCPIP_PTP_PORT_ID_S),
                                 (VOID*)(g_pstPtpGlobalInfo->szClockId),sizeof(TCPIP_PTP_CLOCK_ID_SZ));
            (VOID)TCPIP_Mem_Copy((VOID*)&stReceiverIdB,sizeof(TCPIP_PTP_PORT_ID_S),
                                 (VOID*)(g_pstPtpGlobalInfo->szClockId),sizeof(TCPIP_PTP_CLOCK_ID_SZ));
            break;         
        
    }

   if (pstForeMasterA->usStepsRemoved < pstForeMasterB->usStepsRemoved)
    {
          
        (VOID)VOS_Mem_Cmp((void *)&stReceiverIdB, (void *)&(pstForeMasterB->szForeignMasterPortId),sizeof(TCPIP_PTP_PORT_ID_S), &lRet); 
        if (lRet < 0)/*stReceiverIdB < SenderB*/
        {
            *ppstSelectMaster = pstForeMasterA;
            *pbBetter = BOOL_TRUE;
            return TCPIP_PTP_OK;
        }
        else if (lRet > 0) /*stReceiverIdB > SenderB*/
        {
            *ppstSelectMaster = pstForeMasterA;
            *pbTopoBetter = BOOL_TRUE;
            return TCPIP_PTP_OK;
        }
        return TCPIP_PTP_ERR_BMC_ERRNO1;
    }
    else if (pstForeMasterA->usStepsRemoved > pstForeMasterB->usStepsRemoved)
    {
        (VOID)VOS_Mem_Cmp((void *)&stReceiverIdA, (void *)&(pstForeMasterA->szForeignMasterPortId),sizeof(TCPIP_PTP_PORT_ID_S), &lRet); 
        if (lRet < 0)  /*stReceiverIdA < senderA*/
        {
            *ppstSelectMaster = pstForeMasterB;
            *pbBetter = BOOL_TRUE;
            return TCPIP_PTP_OK;
        }
        else if (lRet > 0) /*stReceiverIdA > senderA*/
        {
            *ppstSelectMaster = pstForeMasterB;
            *pbTopoBetter = BOOL_TRUE;
            return TCPIP_PTP_OK;
        }
        return TCPIP_PTP_ERR_BMC_ERRNO1;
    }

    /*Step10:�Ƚ�portId*/
    (VOID)VOS_Mem_Cmp((void *)&(pstForeMasterA->szForeignMasterPortId), (void *)&(pstForeMasterB->szForeignMasterPortId),sizeof(TCPIP_PTP_PORT_ID_S), &lRet);
    if (lRet < 0)
    {
        *ppstSelectMaster = pstForeMasterA;
        *pbTopoBetter = BOOL_TRUE;
        return TCPIP_PTP_OK;
    }
    else if (lRet > 0)
    {       
        *ppstSelectMaster = pstForeMasterB;
        *pbTopoBetter = BOOL_TRUE;
        return TCPIP_PTP_OK;
    }

    /*Step11:�Ƚ�A��B����Ӧ��PTP�˿ںţ��ڵ�ǰʵ����ʼ����ͬ*/
    if (stReceiverIdA.usPortNumber > stReceiverIdB.usPortNumber)
    {
        *ppstSelectMaster = pstForeMasterB;
        *pbTopoBetter = BOOL_TRUE;
        return TCPIP_PTP_OK;
    }
    else if (stReceiverIdA.usPortNumber < stReceiverIdB.usPortNumber)
    {
        *ppstSelectMaster = pstForeMasterA;
        *pbTopoBetter = BOOL_TRUE;
        return TCPIP_PTP_OK;
    }

    return TCPIP_PTP_ERR_BMC_ERRNO2;
}


ULONG PTPV2_BMC_PPI_SlaveRole(PTPV2_FOREIGN_MASTER_S* pstSelectMaster,  ULONG ulCmd, ULONG ulChangeField)
{
    TCPIP_PTP_SLAVE_PPI_S  stPpiData;
    PTPV2_PORT_S* pstPortInfo = NULL;
    ULONG ulPtpV2ClockType = 0;
    ULONG ulRet = TCPIP_PTP_OK;

    if (NULL == g_pfPtpV2PpiHookFunc)
    {
        return TCPIP_PTP_ERR_HOOK_UNREG;
    }

    /*�·�ɾ�� �������澯��ʱ��*/
    if ((TCPIP_PTP_PPI_DEL == ulCmd))
    {
        /*�����澯��ʱ��*/
        (VOID)PTPV2_CreateWarningTimer();
    }
    
    ulPtpV2ClockType = PTPV2_GetClockType();

    VOS_DBGASSERT(PTPV2_CLOCK_TYPE_BC == ulPtpV2ClockType);

    if (PTPV2_CLOCK_TYPE_OC == ulPtpV2ClockType)
    {
        return TCPIP_PTP_ERR_NOT_SUPPORT_IN_OC;
    }

    pstPortInfo = pstSelectMaster->pstPortInfo;
    if (NULL == pstPortInfo || NULL == pstPortInfo->pstSubPortInfo)
    {
        return TCPIP_PTP_ERR_SYSTEM_EXCEPTION;
    }

    /*ѡ��ԴEbest,��Ӧ�˿�ΪSlave��ɫ���·�Slave,����¼�·����*/
    if(TCPIP_PTP_PPI_ADD == ulCmd)
    {
        if (TCPIP_PTP_PORT_ROLE_SLAVE != pstPortInfo->pstSubPortInfo->ucPtpPortRole)
        {
            return TCPIP_PTP_ERR;
        }
        pstPortInfo->pstSubPortInfo->ucPpiRoleFlag |= PTPV2_PPI_SLAVE_FLAG;
    }
    else if(TCPIP_PTP_PPI_DEL == ulCmd)
    {   /*ɾ��ԴEbest,��Ӧ�˿����·���Slave,���·�ɾ��Slave,����������ѡԴ,������״̬�ͽ�ɫ*/
        PTPV2_Set_FsmState(pstPortInfo->pstSubPortInfo, PTPV2_PORT_FSM_LISTENING);
        PTPV2_Set_PortRole(pstPortInfo->pstSubPortInfo, TCPIP_PTP_PORT_ROLE_MASTER);
        if (0 == (PTPV2_PPI_SLAVE_FLAG & pstPortInfo->pstSubPortInfo->ucPpiRoleFlag))
        {
            return TCPIP_PTP_ERR;
        }
        pstPortInfo->pstSubPortInfo->ucPpiRoleFlag &= ~PTPV2_PPI_SLAVE_FLAG;
    }

    (VOID)TCPIP_Mem_Set((CHAR*)&stPpiData, 0, sizeof(TCPIP_PTP_SLAVE_PPI_S));

    /*�����·�����Ʒ����Ϣ*/
    stPpiData.ulIfIndex =  pstSelectMaster->ulRcvIfIndex;
    (VOID)TCPIP_Mem_Copy((VOID*)&(stPpiData.stLocalAddr),sizeof(TCPIP_PTP_PORT_ADDR_S),
            (VOID*)&(pstPortInfo->stPtpPortAddr), sizeof(TCPIP_PTP_PORT_ADDR_S));
    stPpiData.usLocalPortNo = pstPortInfo->pstSubPortInfo->usPortNo;
    stPpiData.bTwoStep = g_pstPtpGlobalInfo->stCfgDefaultDs.bTwoStepFlag;
    (VOID)TCPIP_Mem_Copy((VOID*)&(stPpiData.stParentDS), sizeof(TCPIP_PTP_PARENT_DS_S),
            (VOID*)&(g_pstPtpGlobalInfo->stParentDs), sizeof(TCPIP_PTP_PARENT_DS_S));

    /*�����仯��־*/
    stPpiData.ulChangeField = ulChangeField;

    ulRet = g_pfPtpV2PpiHookFunc(TCPIP_PTP_PORT_ROLE_SLAVE , ulCmd, &stPpiData);
    (VOID)PTPV2_PPI_LogMsg(ulRet, pstPortInfo->pstSubPortInfo->usPortNo, ulCmd, &stPpiData);

    return ulRet;
}


VOID PTPV2_PPI_PassiveRole(ULONG ulCmd, PTPV2_PORT_S* pstPortInfo)
{
    ULONG ulRet = 0;
    ULONG ulCanPPI = VRP_NO;
    UCHAR ucLocalMac[PTPV2_MACADDRLEN] = {0};
    TCPIP_PTP_PASSIVE_PPI_S stPpiPassiveData;

    if (NULL == g_pfPtpV2PpiHookFunc)
    {
        return;
    }

    (VOID)TCPIP_Mem_Set((VOID*)&stPpiPassiveData, 0, sizeof(TCPIP_PTP_PASSIVE_PPI_S));
    (VOID)TCPIP_GetEtharpMac(pstPortInfo->ulIfIndex, ucLocalMac);
    
    (VOID)TCPIP_Mem_Copy((VOID*)stPpiPassiveData.stLocalAddr.unAddr.ucMacAddr, 8,(VOID*)ucLocalMac, PTPV2_MACADDRLEN);
    stPpiPassiveData.ulIfIndex = pstPortInfo->ulIfIndex;
    stPpiPassiveData.usLocalPortNo = pstPortInfo->pstSubPortInfo->usPortNo;

    /*Add passive:1.start port*/
    if (TCPIP_PTP_PPI_ADD == ulCmd)
    {   
        ulCanPPI = PTPV2_YES;
        pstPortInfo->pstSubPortInfo->ucPpiRoleFlag |= PTPV2_PPI_PASSIVE_FLAG;
    }
    else if (TCPIP_PTP_PPI_DEL == ulCmd)
    {   /*Del passive:1.del port*/
        ulCanPPI = PTPV2_YES;
        pstPortInfo->pstSubPortInfo->ucPpiRoleFlag &= ~PTPV2_PPI_PASSIVE_FLAG;
    }
    

    if (VRP_YES == ulCanPPI)
    {
        ulRet = g_pfPtpV2PpiHookFunc(TCPIP_PTP_PORT_ROLE_PASSIVE, ulCmd, (VOID *)&stPpiPassiveData);
        PTPV2_PPI_LogMsg(ulRet, pstPortInfo->pstSubPortInfo->usPortNo, ulCmd, &stPpiPassiveData);
    }

    return;
}


VOID PTPV2_BMC_PPI_PassiveRoleForAll()
{
    ULONG ulIter = 0;
    PTPV2_PORT_S *pstPortInfo = NULL;

    for(ulIter = PTPV2_MIN_PORTNO ; ulIter < PTPV2_MAX_PORTNO + 1; ulIter ++)
    {
        pstPortInfo = (PTPV2_PORT_S *)(g_pstPortManageInfo->ulPortInfoHandle[ulIter]);

        if (NULL == pstPortInfo)
        {
            continue;
        }
        if (TCPIP_PTP_PORT_ROLE_SLAVE == pstPortInfo->pstSubPortInfo->ucPtpPortRole)
        {
            /*1.passive->slave : ppi del passive
             *2.master->slave  : do nothing
             *3.slave->slave   : do nothing
            */
            if (PTPV2_PPI_PASSIVE_FLAG & pstPortInfo->pstSubPortInfo->ucPpiRoleFlag)
            {
               PTPV2_PPI_PassiveRole(TCPIP_PTP_PPI_DEL, pstPortInfo);
            }
        }
        else if (TCPIP_PTP_PORT_ROLE_MASTER== pstPortInfo->pstSubPortInfo->ucPtpPortRole)
        {
            /*1.passive->master: ppi del passive
             *2.slave->master  : do nothing
             *3.master->master : do noting
            */
            if (PTPV2_PPI_PASSIVE_FLAG & pstPortInfo->pstSubPortInfo->ucPpiRoleFlag)
            {
                PTPV2_PPI_PassiveRole(TCPIP_PTP_PPI_DEL, pstPortInfo);
            }
        }
        else if (TCPIP_PTP_PORT_ROLE_PASSIVE == pstPortInfo->pstSubPortInfo->ucPtpPortRole)
        {
            /*1.slave->passive  : ppi add passive
             *2.master->passive : ppi add passive
             *3.passive->passive: do nothing
            */
            if (0 == (PTPV2_PPI_PASSIVE_FLAG & pstPortInfo->pstSubPortInfo->ucPpiRoleFlag))
            {
                PTPV2_PPI_PassiveRole(TCPIP_PTP_PPI_ADD, pstPortInfo);
            }
        }
    }
    
    return;
}

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */
