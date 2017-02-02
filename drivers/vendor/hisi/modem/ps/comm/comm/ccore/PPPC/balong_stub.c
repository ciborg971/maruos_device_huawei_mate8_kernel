/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "v_lib.h"
#include "v_typdef.h"
#include "vrpcfg.h"

#include "PsCommonDef.h"

#include "vrpcfg.h"
#include "balong_stub.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
ULONG g_ulA11RpifIp = 0;
ULONG g_ucSelfScId = 0xffffffff;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

ULONG L2TP_SeparateUserName(CHAR *szUserName, CHAR *szDomain, CHAR *szUserAbbr)
{
    return 0;
}

VOID A11_PPP_TermTag(ULONG ulPdpIndex, UCHAR ucFlag)
{
    return;
}

ULONG DVM_GetSelfCpuId(VOID)
{
    return 0;
}

ULONG SDB_GetRpContextByIndex(ULONG ulIndex, VOID **ppucContext)
{
    ULONG ulRet = VOS_OK;

    return SDB_SUCCESS;
}


VOID HSGW_EmsTraceByRpIndex(ULONG ulRpIndex, ULONG ulModule, ULONG ulCode)
{
    return;
}

VOID HSGW_EmsTraceByPdnIndex(ULONG ulPdnIndex, ULONG ulModule, ULONG ulCode)
{
    return;
}

VOS_UINT32 A11_GetCompStatNum(SC_COMPRESS_STATE_S * pstCompStatInfo)
{
    return VOS_OK;
}

VOS_VOID A11_OM_HSGWPerfStatisticPCFUnit(ULONG ulStatisticType, ULONG ulPcfIp, ULONG ulOperType, ULONG ulValue)
{
    return;
}

VOS_VOID A11_OM_PerfStatisticPCFUnit(ULONG ulStatisticType, ULONG ulPcfIp)
{
    return;
}

ULONG USM_NotifyPhaseResultFunc(ULONG ulRpIndex, ULONG ulMsgtype,
                                            VOS_VOID *pResultInfo)
{
    return VOS_OK;
}

ULONG A11_VirtualDomainMapping(USHORT usVirtualDomainIndex,
                               A11_IMSI_S stIMSI,
                               USHORT *pusRealDomainIndex)
{
    return VOS_OK;
}

ULONG A11_GetVirtualDomainStatusByIndex(USHORT usAPNIndex)
{
    return VOS_OK;
}

ULONG SDB_GetPdnContextByIndex(ULONG ulIndex, VOID **ppucContext)
{
    return VOS_OK;
}

ULONG A11_A10GlobalIndexToA10ScIndex(ULONG ulA10GlobalIndex)
{
    return VOS_OK;
}

ULONG A11_PPPC_SendUsrInfor(ULONG                 ulRpIndex,
                            A11_PPPC_USR_INFOR_S* pstUsrInfor,
                            ULONG                 ulFlag)
{
    return VOS_OK;
}

ULONG ALM_GetAlmSlotCpuID()
{
    return 0;
}

VOID  A11_4BitsToString( UCHAR *strSrc, UCHAR DstArr[], UCHAR ucMaxNum )
{
    return;
}

VOS_BOOL Trc_IsTraceTaskEnabled(VOS_UINT8 ucTrcType)
{
    return VOS_FALSE;
}

ULONG USM_NotifyReleaseUserFunc(ULONG ulRpIndex, ULONG ulReleaseCode, UCHAR* pucMsg)
{
    return VOS_OK;
}

ULONG Diam_AUTHHostRemoveByAAACBIndex(USHORT usDynAAAIndex, ULONG ulRpIndex)
{
    return VOS_OK;
}

ULONG PPPC_CRYPT_random (UCHAR*  pBuf, ULONG ulLen)
{
    return VOS_OK;
}

VOS_UINT32 AlarmToFamEx(VOS_UINT32  ucSlotNo,               /* 2???o? */
                        VOS_UINT32 udwMid,                 /* 2úéú???ˉ?￡?éPID*/
                        VOS_UINT32 udwAlarmICID,           /* ???ˉ???-ID */
                        VOS_UINT8  ucAlarmType,            /* ???ˉààDí */
                        VOS_UINT8  ucParaNum,             /* ???ˉ2?êy??êy */
                        VOS_UINT8  ucValueLen[],          /* ???ˉ2?êy3¤?èáD±í */
                        VOID      *pVarValue[])            /* ???ˉ2?êyáD±í */
{
    return 0;
}

VOID Snmp_Perf( MEAOBJINDEX_STRU stMeaObj, ULONG ulMeaType, ULONG ulOpType )
{
    return;
}

ULONG SPM_RegisterByte(  ULONG  ulSoftparaNum,     pfSPM_ByteCallBack pfCallback)
{
    return VOS_OK;
}

VOS_UINT32 PSM_Inf_GetSGIndexBySGID(VOS_UINT64 SGID)
{
    return VOS_OK;
}

ULONG CRM_GetSelfGroupId(VOID)
{
    return 1;
}

ULONG PDN_PppVsncpSucc( ULONG ulRpIndex, UCHAR ucPdnId )
{
    return 0;
}

VOID PDN_FsmStopTimer(ULONG ulTimerType, ULONG ulTimerId)
{
    return;
}

ULONG USM_GetApnIndexByApnName(UCHAR *pucApnName, USHORT *pusApnIndex)
{
    return 0;
}

ULONG PDN_VsncpNotifyGetPCO(PDN_CONTEXT_S *pstPdnContext, PDN_PPP_VSNCP_REQ_S *pstVsncpReq)
{
    return 0;
}

ULONG PDN_VsncpNotifyReconnect(PDN_CONTEXT_S *pstPdnContext, PDN_PPP_VSNCP_REQ_S *pstVsncpReq)
{
    return 0;
}

ULONG PDN_PppStartEhrpdPdn(ULONG ulRpIndex, PDN_PPP_VSNCP_REQ_S *pstVsncpReq)
{
    return 0;
}

ULONG USM_GetApnCfgByApnIndex(USHORT usApnIndex, HSGW_APN_INFO_S **ppstHsgwApn)
{
    return 0;
}

VOS_BOOL USM_IsDefaultApn(ULONG ulRpIndex, USHORT usApnIndex)
{
   return 0;
}

VOS_UINT32 IPV6_StopTimer(VOS_UINT32 ulTimerId)
{
    return 0;
}


ULONG INST_GetSelfInstanceId()
{
    return 0;
}

ULONG Diam_AUTHGetDynAAAInfoByIndex(USHORT usDynAAAIndex, UCHAR *pucHost, UCHAR *pucRealm, USHORT *pusDynPeerId)
{
    return 0;
}

ULONG PDN_GetPdnType( ULONG ulPdnIndex, ULONG *pulPdnType)
{
    return 0;
}

ULONG PDN_JudgeSubPDNStateActive(ULONG ulRpIndex, ULONG ulSubPdnType)
{
    return 0;
}

ULONG  RDA_GetApnDNSCfg(USHORT usApnIndex, APNDNS_S *pstApn)
{
    return 0;
}

ULONG Diam_AUTHBackupRebuildDynAAACB(USHORT usNewPeerId, USHORT usDynPeerId,
                                     UCHAR *pucAAAHost, UCHAR *pucAAARealm)
{
    return 0;
}

USHORT GetDomainIndexByName( UCHAR*   szDomainName)
{
    return 0;
}

VOS_UINT32 Ipv6_A11NotifySendRa(VOS_UINT32 ulPdnIndex)
{
    return 0;
}

VOS_UINT32 PGP_RTDistributeSend(VOS_UINT64 ul64SrcCSI,VOS_UINT64 ul64DstCSI, VOS_VOID* pMsg, VOS_UINT32 ulLen, VOS_UINT32 ulMode, VOS_UINT32 ulMsgType)
{
    //free(pMsg);
    pMsg = NULL;

    return 0;
}

VOS_UINT32 PSM_Inf_GetCmpSameTIndexInSGByCSI(VOS_UINT64 CSI)
{
    return 0;
}

VOS_UINT64 PSM_Inf_GetSelfSGID()
{
    return 1;
}

VOS_UINT32 PSM_Inf_GetCmpIndexInOSByCSI(VOS_UINT64 CSI)
{
    return 0;
}

VOS_UINT64 PSM_Inf_GetSelfCSI(VOS_UINT32 CompType)
{
    return 0;
}

VOS_UINT32 *PGP_ShrMemAllocByName(VOS_CHAR* name, UCHAR ShareMemType, ULONG ullInfo, ULONG uiSize)
{
    return VOS_OK;
}


VOS_UINT64 PSM_Inf_GetCSIByOSIDCmpTypeAndInstIdInOS(IN VOS_UINT32 uiChasisNo,IN VOS_UINT32 uiSlot,IN VOS_UINT32 OSID,
 IN VOS_UINT32 CmpType, IN VOS_UINT32 InstIdInOS)
{
    return 0;
}

ULONG CRM_GetSelfGroupBoardType( CRM_SPU_BOARD_TYPE_ENUM* pMode)
{
    *pMode = CRM_BOARD_TYPE_SPUE;
    return VOS_OK;
}

ULONG DBG_LogRecordReg(CHAR szSystemName[DBG_LOG_SYSTEM_NAME_LEN],
    CHAR szModuleName[DBG_LOG_MODULE_NAME_LEN], CHAR szSubmoduleName[DBG_LOG_SUB_MODULE_NAME_LEN],
    ULONG *ulDBGLogRegID)
{
    return VOS_OK;

}

ULONG PTM_CommandsRegister ( LPCommand_Group_S pCommand_Group, CHAR *cpCommand, CHAR *cpHelp , UINT64 ul64Csi)
{
    return 0;
}

VOID PGP_RTDistributeFreeMsg(VOID *pMsg)
{
    return;
}

VOID* PGP_RTDistributeAllocMsg(VOS_UINT64 selfCSI,ULONG ulMsgLen)
{
    return VOS_NULL;
}

VOS_UINT32 VOS_Que_Read( VOS_UINT32 ulQueID, VOS_UINT32 ulRetMsg[4],
                VOS_UINT32 ulFlags, VOS_UINT32 ulTimeOutInMillSec )
{
    return 0;
}


VOS_UINT32 VOS_Ev_Write( VOS_UINT32 ulTaskID, VOS_UINT32 ulEvents )
{
    return VOS_OK;
}

VOS_UINT32 VOS_MCReadQue(VOS_VOID* pstQueId,VOS_VOID** ppMsg,VOS_UINT32 *pulMsgLen,
                         VOS_UINT32 ulFlag,VOS_UINT32 ulMillsec)
{
    return 0;
}

VOS_UINT32 PTM_CreateQueue(PTM_QUEUE_INFO_S *pstQueInfo, VOS_UINT32* pulQueID)
{
    VOS_UINT32 ulRet = VOS_OK;

    return ulRet;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

