



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmIpMsgProc.h"
#include    "NasEsmPublic.h"
#include    "NasEsmNwMsgDecode.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMIPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMIPMSGPROC_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif




/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmIpPdpReleaseInd
 Description    : ��IPģ�鷢��ID_ESM_IP_PDP_RELEASE_IND��Ϣ
 Input          : ulEpsbId-------------------���غ�
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong00150010      2010-12-01  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ESM_SndEsmIpPdpReleaseInd
(
    VOS_UINT8                           ucEpsbId
)
{
    ESM_IP_PDP_RELEASE_IND_STRU        *pstPdpReleaseInd    = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstPdpReleaseInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_IP_PDP_RELEASE_IND_STRU));

    if ( VOS_NULL_PTR == pstPdpReleaseInd )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmIpPdpReleaseInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmIpPdpReleaseInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET(    NAS_ESM_GET_MSG_ENTITY(pstPdpReleaseInd),
                        NAS_ESM_NULL,
                        NAS_ESM_GET_MSG_LENGTH(pstPdpReleaseInd));

    /* ��д��Ϣ���� */
    pstPdpReleaseInd->ucEpsbId      = ucEpsbId;

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_IP_MSG_HEAD(pstPdpReleaseInd, ID_ESM_IP_PDP_RELEASE_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstPdpReleaseInd);
}


/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmIpRelInd
 Description    : ��IPģ�鷢��ID_ESM_IP_REL_IND��Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong00150010      2010-12-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmIpRelInd( VOS_VOID )
{
    ESM_IP_REL_IND_STRU                *pstRelInd           = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstRelInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_IP_REL_IND_STRU));

    if ( VOS_NULL_PTR == pstRelInd )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmIpRelInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmIpRelInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET(    NAS_ESM_GET_MSG_ENTITY(pstRelInd),
                        NAS_ESM_NULL,
                        NAS_ESM_GET_MSG_LENGTH(pstRelInd));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_IP_MSG_HEAD(pstRelInd, ID_ESM_IP_REL_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstRelInd);
}


/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmIpNwParaIndMsg
 Description    : ��IPģ�鷢��ID_ESM_IP_NW_PARA_IND��Ϣ
 Input          : ulEpsbId-------------------���غ�
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong00150010      2010-12-11  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmIpNwParaIndMsg
(
    VOS_UINT8                           ucEpsbId
)
{
    ESM_IP_NW_PARA_IND_STRU            *pstNwParaInd        = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;


    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucEpsbId);

    /* �ж�IP��ַ�Ƿ���Ч */
    if (NAS_ESM_IS_IPV4_ADDR_INVALID(pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV4Addr))
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmIpNwParaIndMsg:Ipv4 is invaild!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmIpNwParaIndMsg_ENUM, 1);
        return ;
    }

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstNwParaInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_IP_NW_PARA_IND_STRU));

    if ( VOS_NULL_PTR == pstNwParaInd )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmIpNwParaIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmIpNwParaIndMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET(    NAS_ESM_GET_MSG_ENTITY(pstNwParaInd),
                        NAS_ESM_NULL,
                        NAS_ESM_GET_MSG_LENGTH(pstNwParaInd));

    /* ��д��Ϣ���� */
    pstNwParaInd->ucEpsbId              = ucEpsbId;

    pstNwParaInd->bitOpIpAddr           = NAS_ESM_OP_TRUE;
    pstNwParaInd->stIpAddr.ucIpType     = NAS_ESM_PDN_IPV4;
    NAS_ESM_MEM_CPY(    pstNwParaInd->stIpAddr.aucIpV4Addr,
                        pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV4Addr,
                        NAS_ESM_IP_ADDR_LEN_IPV4);

    pstNwParaInd->bitOpSubnetMask       = NAS_ESM_OP_TRUE;
    pstNwParaInd->stSubnetMask.ucIpType = NAS_ESM_PDN_IPV4;
    NAS_ESM_MEM_CPY(    pstNwParaInd->stSubnetMask.aucIpV4Addr,
                        pstEpsbCntxtInfo->stSubnetMask.aucIpV4Addr,
                        NAS_ESM_IP_ADDR_LEN_IPV4);

    pstNwParaInd->bitOpGateWay          = NAS_ESM_OP_TRUE;
    pstNwParaInd->stGateWay.ucIpType    = NAS_ESM_PDN_IPV4;
    NAS_ESM_MEM_CPY(    pstNwParaInd->stGateWay.aucIpV4Addr,
                        pstEpsbCntxtInfo->stGateWayAddrInfo.aucIpV4Addr,
                        NAS_ESM_IP_ADDR_LEN_IPV4);

    if (NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpPco)
    {
        pstNwParaInd->stDnsServer.ucDnsSerNum = pstEpsbCntxtInfo->stPcoInfo.ucIpv4DnsSerNum;
        NAS_ESM_MEM_CPY(    pstNwParaInd->stDnsServer.astDnsServer,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4DnsServer,
                            (NAS_ESM_MAX_DNS_SERVER_NUM * sizeof(NAS_ESM_IPV4_ADDR_STRU)));
    }

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_IP_MSG_HEAD(pstNwParaInd, ID_ESM_IP_NW_PARA_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstNwParaInd);
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


/* end of NasEsmIpMsgProc.c */
