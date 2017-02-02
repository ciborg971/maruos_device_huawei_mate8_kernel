/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasERabmTest.c
  Description     :
  History         :
     1.lihong00150010   2009-09-17  Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmTest.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMTEST_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMTIMERMSGPROC_C
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
NAS_ERABM_UL_DATA_TRANS_INFO_STRU    g_stERabmUlDataTransInfo;
NAS_ERABM_DL_DATA_TRANS_INFO_STRU    g_stERabmDlDataTransInfo;



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ERABM_DebugInit
 Description     : ���ͳ����Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-09-17  Draft Enact

*****************************************************************************/
/*lint -e960*/
VOS_VOID NAS_ERABM_DebugInit(VOS_VOID)
{
    NAS_ERABM_MEM_SET(  &g_stERabmUlDataTransInfo,
                        0,
                        sizeof(NAS_ERABM_UL_DATA_TRANS_INFO_STRU));
}
VOS_VOID  NAS_ERABM_CmdHelp( VOS_VOID )
{
    (VOS_VOID)vos_printf("\r\n");
    (VOS_VOID)vos_printf("********************** NAS RABM ��������б� *********************\r\n");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_DebugInit","���RABMͳ��ͳ����Ϣ");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_ShowEpsBearerDataTransInfo(ulEpsbId)","��ʾĳ����������Ϣ");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_ShowActiveEpsBearerDataTransInfo","��ʾ���м������������Ϣ");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_ShowEpsbTftInfo(ulEpsbId)","��ʾĳ����TFT��Ϣ");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_ShowUlDataTransInfo","��ʾ����������Ϣ");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_ShowDlDataTransInfo","��ʾ����������Ϣ");
    (VOS_VOID)vos_printf("%-30s : %s\r\n","NAS_ERABM_ShowUlFilterInfo(ulFilterId)","��ʾ���й�������Ϣ");
    (VOS_VOID)vos_printf("*******************************************************************\r\n");
    (VOS_VOID)vos_printf("\r\n");

    return;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_ShowEpsBearerDataTransInfo
 Description     : ��ʾ������Ϣ
 Input           : VOS_UINT32
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-9-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_ShowEpsBearerDataTransInfo( VOS_UINT32 ulEspbId )
{
    NAS_ERABM_BERER_DATA_TRANS_INFO_STRU    *pstEpsBearerDataTransInfo   = VOS_NULL_PTR;
    NAS_ERABM_EPSB_STATE_ENUM_UINT8          enEpsBearerState            = NAS_ERABM_GetEpsbStateInfo(ulEspbId);
    NAS_ERABM_RB_STATE_ENUM_UINT8            enRbState                   = NAS_ERABM_GetRbStateInfo(ulEspbId);

    if ((ulEspbId < NAS_ERABM_MIN_EPSB_ID) || (ulEspbId > NAS_ERABM_MAX_EPSB_ID))
    {
        (VOS_VOID)vos_printf("NAS_ERABM_ShowEpsBearerDataTransInfo:����������غŵķ�Χ:5-15\r\n");
        return ;
    }

    pstEpsBearerDataTransInfo = NAS_ERABM_GetBearerDataTransInfoAddr(ulEspbId);

    (VOS_VOID)vos_printf("****************EPS����%d��Ӧ�������Ϣ����****************\r\n",ulEspbId);

    if (NAS_ERABM_EPSB_ACTIVE == enEpsBearerState)
    {
        (VOS_VOID)vos_printf("����״̬:%s\r\n","����");
    }
    else
    {
        (VOS_VOID)vos_printf("����״̬:%s\r\n","δ����");
    }

    (VOS_VOID)vos_printf("����RB��:%d\r\n",NAS_ERABM_GetEpsbRbIdInfo(ulEspbId));

    if (NAS_ERABM_RB_CONNECTED == enRbState)
    {
        (VOS_VOID)vos_printf("����RB״̬:%s\r\n","����̬");
    }
    else if (NAS_ERABM_RB_SUSPENDED == enRbState)
    {
        (VOS_VOID)vos_printf("����RB״̬:%s\r\n","��̬ͣ");
    }
    else
    {
        (VOS_VOID)vos_printf("����RB״̬:%s\r\n","������̬");
    }

    (VOS_VOID)vos_printf("����QCI:%d\r\n",NAS_ERABM_GetEpsbQCI(ulEspbId));
    (VOS_VOID)vos_printf("�������ݰ�����:%d\r\n",pstEpsBearerDataTransInfo->ulSendPackageNum);
    (VOS_VOID)vos_printf("�������ݰ�����:%d\r\n",pstEpsBearerDataTransInfo->ulDiscardPackageNum);
    (VOS_VOID)vos_printf("����DRB IDLE̬�����ݰ�����:%d\r\n",pstEpsBearerDataTransInfo->ulIdlePackageNum);
    (VOS_VOID)vos_printf("����DRB SUSPEND̬�����ݰ�����:%d\r\n",pstEpsBearerDataTransInfo->ulSuspendPackageNum);
    (VOS_VOID)vos_printf("���ع���DRB�����ڴ���:%d\r\n",pstEpsBearerDataTransInfo->ulEpsbNoDrbTimes);
    (VOS_VOID)vos_printf("����ع���DRB�����ڶ����������ݰ�����:%d\r\n",pstEpsBearerDataTransInfo->ulEpsbNoDrbDiscPackageNum);
}

/*****************************************************************************
 Function Name   : NAS_ERABM_ShowActiveEpsBearerDataTransInfo
 Description     : ��ʾ���м�����ص�������Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-9-18  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_ShowActiveEpsBearerDataTransInfo( VOS_VOID )
{
    VOS_UINT32                 ulEpsbId;
    VOS_UINT32                 ulActiveNum = NAS_ERABM_NULL;

    for ( ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++ )
    {
        if ( NAS_ERABM_EPSB_INACTIVE == NAS_ERABM_GetEpsbStateInfo(ulEpsbId))
        {
            continue;
        }
        else
        {
            ulActiveNum++;

            /* ��ʾ����������Ϣ */
            NAS_ERABM_ShowEpsBearerDataTransInfo(ulEpsbId);
        }
    }

    if ( NAS_ERABM_NULL == ulActiveNum )
    {
        (VOS_VOID)vos_printf("%-30s\r\n","��ǰ�����ڼ����EPS����");
    }
}
VOS_VOID  NAS_ERABM_ShowEpsbTftInfo( VOS_UINT32 ulEspbId )
{
    ESM_ERABM_TFT_PF_STRU           *pstEpsbTft = VOS_NULL_PTR;
    VOS_UINT32                      ulEpsbTftNum = NAS_ERABM_NULL;
    VOS_UINT32                      ulLoop = NAS_ERABM_NULL;

    if ((ulEspbId < NAS_ERABM_MIN_EPSB_ID) || (ulEspbId > NAS_ERABM_MAX_EPSB_ID))
    {
        (VOS_VOID)vos_printf("NAS_ERABM_ShowEpsbTftInfo:����������غŵķ�Χ:5-15\r\n");
        return ;
    }

    ulEpsbTftNum = NAS_ERABM_GetEpsbTftPfNum(ulEspbId);

    if ( NAS_ERABM_NULL == ulEpsbTftNum )
    {
        (VOS_VOID)vos_printf("EPS����%d������TFT��Ϣ\r\n",ulEspbId);
        return;
    }
    else
    {
        (VOS_VOID)vos_printf("EPS����%d����%d��PF\r\n",ulEspbId,ulEpsbTftNum);
    }

    for ( ulLoop = 0 ; ulLoop < ulEpsbTftNum; ulLoop++ )
    {
        pstEpsbTft = NAS_ERABM_GetEpsbTftAddr(ulEspbId, ulLoop);
        (VOS_VOID)vos_printf("********RABMģ��ͳ�Ƶ�EPS����%d�ĵ�%d��PF��TFT��Ϣ********\r\n",ulEspbId,(ulLoop + 1));

        if ( NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpRmtIpv4AddrAndMask )
        {
            (VOS_VOID)vos_printf("%-30s : %d.%d.%d.%d\r\n","TFT��Ŀ��IPv4", pstEpsbTft->aucRmtIpv4Address[0],
                                      pstEpsbTft->aucRmtIpv4Address[1],
                                      pstEpsbTft->aucRmtIpv4Address[2],
                                      pstEpsbTft->aucRmtIpv4Address[3]);

            (VOS_VOID)vos_printf("%-30s : %d.%d.%d.%d\r\n","TFT������", pstEpsbTft->aucRmtIpv4Mask[0],
                                      pstEpsbTft->aucRmtIpv4Mask[1],
                                      pstEpsbTft->aucRmtIpv4Mask[2],
                                      pstEpsbTft->aucRmtIpv4Mask[3]);
        }

        if ( NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpRmtIpv6AddrAndMask )
        {
            (VOS_VOID)vos_printf("%-30s : %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n","TFT��Ŀ��IPv6",
                                      pstEpsbTft->aucRmtIpv6Address[0],
                                      pstEpsbTft->aucRmtIpv6Address[1],
                                      pstEpsbTft->aucRmtIpv6Address[2],
                                      pstEpsbTft->aucRmtIpv6Address[3],
                                      pstEpsbTft->aucRmtIpv6Address[4],
                                      pstEpsbTft->aucRmtIpv6Address[5],
                                      pstEpsbTft->aucRmtIpv6Address[6],
                                      pstEpsbTft->aucRmtIpv6Address[7],
                                      pstEpsbTft->aucRmtIpv6Address[8],
                                      pstEpsbTft->aucRmtIpv6Address[9],
                                      pstEpsbTft->aucRmtIpv6Address[10],
                                      pstEpsbTft->aucRmtIpv6Address[11],
                                      pstEpsbTft->aucRmtIpv6Address[12],
                                      pstEpsbTft->aucRmtIpv6Address[13],
                                      pstEpsbTft->aucRmtIpv6Address[14],
                                      pstEpsbTft->aucRmtIpv6Address[15]);

            (VOS_VOID)vos_printf("%-30s : %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n","TFT������",
                                      pstEpsbTft->aucRmtIpv6Mask[0],
                                      pstEpsbTft->aucRmtIpv6Mask[1],
                                      pstEpsbTft->aucRmtIpv6Mask[2],
                                      pstEpsbTft->aucRmtIpv6Mask[3],
                                      pstEpsbTft->aucRmtIpv6Mask[4],
                                      pstEpsbTft->aucRmtIpv6Mask[5],
                                      pstEpsbTft->aucRmtIpv6Mask[6],
                                      pstEpsbTft->aucRmtIpv6Mask[7],
                                      pstEpsbTft->aucRmtIpv6Mask[8],
                                      pstEpsbTft->aucRmtIpv6Mask[9],
                                      pstEpsbTft->aucRmtIpv6Mask[10],
                                      pstEpsbTft->aucRmtIpv6Mask[11],
                                      pstEpsbTft->aucRmtIpv6Mask[12],
                                      pstEpsbTft->aucRmtIpv6Mask[13],
                                      pstEpsbTft->aucRmtIpv6Mask[14],
                                      pstEpsbTft->aucRmtIpv6Mask[15]);
        }

        if ( NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpLocalPortRange )
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT�Ľ��˶˿���Сֵ", pstEpsbTft->usLcPortLowLimit);
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT�Ľ��˶˿����ֵ", pstEpsbTft->usLcPortHighLimit);
        }

        if ( NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpRemotePortRange)
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT��Զ�˶˿���Сֵ", pstEpsbTft->usRmtPortLowLimit);
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT��Զ�˶˿����ֵ", pstEpsbTft->usRmtPortHighLimit);
        }

        if (NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpProtocolId)
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT��Э��汾��", pstEpsbTft->ucProtocolId);
        }

        if ( NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpSingleLocalPort)
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT�Ľ��˶˿ں�", pstEpsbTft->usSingleLcPort);
        }

        if ( NAS_ERABM_OP_TRUE == pstEpsbTft->bitOpSingleRemotePort)
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT��Զ�˶˿ں�", pstEpsbTft->usSingleRmtPort);
        }

        (VOS_VOID)vos_printf("%-30s : %d\r\n","TFT�����ȼ�", pstEpsbTft->ucPrecedence);

    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_ShowUlDataTransInfo
 Description     : ��ʾ����������Ϣ
 Input           : VOS_UINT32
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-9-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_ShowUlDataTransInfo( VOS_VOID )
{
    NAS_ERABM_UL_DATA_TRANS_INFO_STRU *pstUlDataTransInfo = VOS_NULL_PTR;

    pstUlDataTransInfo = NAS_ERABM_GetUlDataTransInfoAddr();

    (VOS_VOID)vos_printf("****************************����������Ϣ****************************\r\n");
    (VOS_VOID)vos_printf("�����յ������ݰ���:%d\r\n",pstUlDataTransInfo->ulRecePackageNum);
    (VOS_VOID)vos_printf("���з��������ݰ���:%d\r\n",pstUlDataTransInfo->ulSendPackageNum);
    (VOS_VOID)vos_printf("���ж��������ݰ���:%d\r\n",pstUlDataTransInfo->ulDiscPackageNum);
    (VOS_VOID)vos_printf("����DRB��IDLE̬�������ݰ���:%d\r\n",pstUlDataTransInfo->ulIdlePackageNum);
    (VOS_VOID)vos_printf("����DRB��SUSPEND̬�������ݰ���:%d\r\n",pstUlDataTransInfo->ulSuspendPackageNum);
    (VOS_VOID)vos_printf("����δ�ҵ����������ݰ�����:%d\r\n",pstUlDataTransInfo->ulUnfoundBearerPackageNum);
    (VOS_VOID)vos_printf("����DHCPV4 SERVER�����ݰ�����:%d\r\n",pstUlDataTransInfo->ulDhcpv4ServerPacketNum);
    (VOS_VOID)vos_printf("���е�һ����Ƭ������:%d\r\n",pstUlDataTransInfo->ulFirstSegmentPacketNum);
    (VOS_VOID)vos_printf("���з�Ƭ������:%d\r\n",pstUlDataTransInfo->ulSegmentPacketNum);
    (VOS_VOID)vos_printf("����δ�ҵ��˿ںŰ�����:%d\r\n",pstUlDataTransInfo->ulUnfoundPortPacketNum);

    /* ��ʾ���м������������Ϣ */
    NAS_ERABM_ShowActiveEpsBearerDataTransInfo();
}

/*****************************************************************************
 Function Name   : NAS_ERABM_ShowDlDataTransInfo
 Description     : ��ʾ����������Ϣ
 Input           : VOS_UINT32
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-9-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_ShowDlDataTransInfo( VOS_VOID )
{
    NAS_ERABM_DL_DATA_TRANS_INFO_STRU *pstDlDataTransInfo = VOS_NULL_PTR;

    pstDlDataTransInfo = NAS_ERABM_GetDlDataTransInfoAddr();

    (VOS_VOID)vos_printf("****************************����������Ϣ****************************\r\n");
    (VOS_VOID)vos_printf("�����յ������ݰ���:%d\r\n",pstDlDataTransInfo->ulRecePackageNum);
    (VOS_VOID)vos_printf("���з��������ݰ���:%d\r\n",pstDlDataTransInfo->ulSendPackageNum);
    (VOS_VOID)vos_printf("���ж��������ݰ���:%d\r\n",pstDlDataTransInfo->ulDiscPackageNum);
}


VOS_VOID  NAS_ERABM_ShowUlFilterInfo(VOS_UINT32 ulFilterId)
{
    IPF_FILTER_CONFIG_S *pstFilterInfo = VOS_NULL_PTR;
    VOS_INT32  ulRslt = IPF_ERROR;

    pstFilterInfo = NAS_ERABM_MEM_ALLOC(sizeof(IPF_FILTER_CONFIG_S));

    if (VOS_NULL_PTR == pstFilterInfo)
    {
        (VOS_VOID)vos_printf(" ��ȡ��������Ϣʧ��\r\n");
        return;
    }
    /*lint -e64*/
    ulRslt = LDRV_IPF_GET_FILTER(IPF_MODEM0_ULFC, ulFilterId, pstFilterInfo);
    /*lint +e64*/

    if (IPF_SUCCESS == ulRslt)
    {
        (VOS_VOID)vos_printf("****************************���й�������Ϣ****************************\r\n");

        (VOS_VOID)vos_printf("%-30s : %d\r\n","��������ID", pstFilterInfo->u32FilterID);

        (VOS_VOID)vos_printf("%-30s : %d\r\n","��������EPSB����ID", pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltBid);

        (VOS_VOID)vos_printf("%-30s : %d\r\n","��������ʹ��״̬", pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltEn);

        if (NAS_ERABM_IPF_IPTYPE_IPV4 == pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltType)
        {
            (VOS_VOID)vos_printf("%-30s : %d.%d.%d.%d\r\n","��������Ŀ��IPv4", pstFilterInfo->stMatchInfo.u8DstAddr[0],
                                          pstFilterInfo->stMatchInfo.u8DstAddr[1],
                                          pstFilterInfo->stMatchInfo.u8DstAddr[2],
                                          pstFilterInfo->stMatchInfo.u8DstAddr[3]);

            (VOS_VOID)vos_printf("%-30s : %d.%d.%d.%d\r\n","������������", pstFilterInfo->stMatchInfo.u8DstMsk[0],
                                          pstFilterInfo->stMatchInfo.u8DstMsk[1],
                                          pstFilterInfo->stMatchInfo.u8DstMsk[2],
                                          pstFilterInfo->stMatchInfo.u8DstMsk[3]);

            (VOS_VOID)vos_printf("%-30s : %d.%d.%d.%d\r\n","��������ԴIPv4", pstFilterInfo->stMatchInfo.u8SrcAddr[0],
                                          pstFilterInfo->stMatchInfo.u8SrcAddr[1],
                                          pstFilterInfo->stMatchInfo.u8SrcAddr[2],
                                          pstFilterInfo->stMatchInfo.u8SrcAddr[3]);
            /*lint -e40*/
            (VOS_VOID)vos_printf("%-30s : %d\r\n","IPV4������local address��Դ������ֵ,�ӵ�λ����λ0�ĸ���Ϊ", pstFilterInfo->stMatchInfo.u32LocalAddressMsk);
            /*lint +e40*/
        }
        else
        {
            (VOS_VOID)vos_printf("%-30s : %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n","��������Ŀ��IPv6",
                                  pstFilterInfo->stMatchInfo.u8DstAddr[0],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[1],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[2],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[3],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[4],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[5],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[6],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[7],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[8],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[9],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[10],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[11],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[12],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[13],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[14],
                                  pstFilterInfo->stMatchInfo.u8DstAddr[15]);

            (VOS_VOID)vos_printf("%-30s : %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n","������������",
                                  pstFilterInfo->stMatchInfo.u8DstMsk[0],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[1],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[2],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[3],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[4],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[5],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[6],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[7],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[8],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[9],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[10],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[11],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[12],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[13],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[14],
                                  pstFilterInfo->stMatchInfo.u8DstMsk[15]);
            (VOS_VOID)vos_printf("%-30s : %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n","��������ԴIPv6",
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[0],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[1],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[2],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[3],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[4],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[5],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[6],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[7],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[8],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[9],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[10],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[11],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[12],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[13],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[14],
                                  pstFilterInfo->stMatchInfo.u8SrcAddr[15]);
            /*lint -e40*/
            (VOS_VOID)vos_printf("%-30s : %d\r\n","������local address��Դ������ֵ,�ӵ�λ����λ0�ĸ���Ϊ", pstFilterInfo->stMatchInfo.u32LocalAddressMsk);
            /*lint +e40*/

        }
        (VOS_VOID)vos_printf("%-30s : %d\r\n","��������Э��汾��", pstFilterInfo->stMatchInfo.unNextHeader.u32Protocol);

        if (NAS_ERABM_OP_TRUE == pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltLPortEn)
        {
           (VOS_VOID)vos_printf("%-30s : %d\r\n","�������Ľ��˶˿���Сֵ", pstFilterInfo->stMatchInfo.unSrcPort.Bits.u16SrcPortLo);
           (VOS_VOID)vos_printf("%-30s : %d\r\n","�������Ľ��˶˿����ֵ", pstFilterInfo->stMatchInfo.unSrcPort.Bits.u16SrcPortHi);
        }

        if (NAS_ERABM_OP_TRUE == pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltRPortEn)
        {
           (VOS_VOID)vos_printf("%-30s : %d\r\n","��������Զ�˶˿���Сֵ", pstFilterInfo->stMatchInfo.unDstPort.Bits.u16DstPortLo);
           (VOS_VOID)vos_printf("%-30s : %d\r\n","��������Զ�˶˿����ֵ", pstFilterInfo->stMatchInfo.unDstPort.Bits.u16DstPortHi);
        }

        if(NAS_ERABM_OP_TRUE == pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltTosEn)
        {
            /*lint -e40*/
            /*lint -e10*/
            (VOS_VOID)vos_printf("%-30s : %d\r\n","��������ServiceType:",pstFilterInfo->stMatchInfo.unTrafficClass.Bits.u8TrafficClass);
            (VOS_VOID)vos_printf("%-30s : %d\r\n","��������ServiceType:",pstFilterInfo->stMatchInfo.unTrafficClass.Bits.u8TrafficClassMask);
            /*lint +e10*/
            /*lint +e40*/
        }

        if(NAS_ERABM_OP_TRUE == pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltSpiEn)
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","��������FilterSpi:",pstFilterInfo->stMatchInfo.u32FltSpi);
        }

        if(NAS_ERABM_OP_TRUE == pstFilterInfo->stMatchInfo.unFltRuleCtrl.Bits.FltFlEn)
        {
            (VOS_VOID)vos_printf("%-30s : %d\r\n","��������FlowLable:",pstFilterInfo->stMatchInfo.u32FlowLable);
        }

        (VOS_VOID)vos_printf("%-30s : %d\r\n","�����������ȼ�", pstFilterInfo->stMatchInfo.unFltChain.Bits.u16FltPri);


    }
    else
    {
        (VOS_VOID)vos_printf(" ��ȡ��������Ϣʧ�ܣ�������Ϊ:%d\r\n", ulRslt);
    }

    NAS_ERABM_MEM_FREE(pstFilterInfo);
}
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif






