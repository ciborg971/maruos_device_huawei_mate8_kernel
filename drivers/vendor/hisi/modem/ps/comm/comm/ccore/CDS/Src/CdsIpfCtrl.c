


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CDS.h"
#include "CdsIpfCtrl.h"
#include "CdsDebug.h"
#include "CdsUlProc.h"
#include "CdsDlProc.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_CDS_IPF_CTRL_C
/*lint +e767*/

/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/

CDS_IPF_CTRL_ENTITY_STRU    g_stCdsIpfCtrlEntity = {0};

/******************************************************************************
   5 ����ʵ��
******************************************************************************/



VOS_UINT32 CDS_GetTtfMemCnt(TTF_MEM_ST *pstTtfMem)
{
    VOS_UINT32    ulCnt;
    TTF_MEM_ST   *pstNext;

    if (VOS_NULL_PTR == pstTtfMem)
    {
        return 0;
    }

    pstNext = pstTtfMem;
    ulCnt = 0;

    while (VOS_NULL_PTR != pstNext)
    {
        ulCnt ++;
        pstNext = pstNext->pNext;
    }

    return ulCnt;
}



TTF_MEM_ST* CDS_AllocTtfMem(VOS_UINT32 ulLen)
{
    TTF_MEM_ST   *pstTtf;

    if ((0 == ulLen) || (CDS_DL_SDU_MAX_LEN < ulLen))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_AllocTtfMem : Input Length Err.",ulLen);
        CDS_PRINT_ERROR1(CDS_AllocTtfMem_ENUM,CDS_PRINT_PARA_INPUT_ERR,ulLen);
        return VOS_NULL_PTR;
    }

    /*�����ڴ棬ָ����Ҫ��λ*/
    pstTtf = TTF_MemBlkAlloc(UEPS_PID_CDS,
                             TTF_MEM_POOL_ID_UL_IP_DATA,
                             (VOS_UINT16)(ulLen + CDS_UL_RESV_LEN_FOR_PDU_HDR));

    if (VOS_NULL_PTR == pstTtf)
    {
        return VOS_NULL_PTR;
    }

    /*����ָ��ƫ��*/
    pstTtf->pData  = pstTtf->pData + CDS_UL_RESV_LEN_FOR_PDU_HDR;
    pstTtf->usUsed = (VOS_UINT16)ulLen;
    pstTtf->ucReserve = 0;

    return pstTtf;
}


VOS_INT32 CDS_UlIpfIntCB(VOS_VOID)
{
    CDS_DBG_RECV_UL_IPF_INT(1);
    CDS_SendEventToCds(CDS_EVENT_UL_IPF_INT);
    return 0;
}



VOS_VOID CDS_InitDlIpfFilter(VOS_VOID)
{
    IPF_FILTER_CONFIG_S    *pstFilter;

    /*Mem Set */
    PS_MEM_SET(g_stCdsIpfCtrlEntity.stFilterCfgStru.astDlFilter,
               0,
               sizeof(IPF_FILTER_CONFIG_S) * CDS_IPF_MAX_DL_FILTER_NUM);

    /* ����DHCPv4 Filter����, IPV4-UDP-Dest Port 68 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_DHCP4);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_DHCP4;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V4);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,17);
    CDS_DL_IPF_FILTER_SET_PORT_HI(pstFilter,68);
    CDS_DL_IPF_FILTER_SET_PORT_LOW(pstFilter,68);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_DHCPV4);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);


    /* ����DHCPv6 Filter����, UDPĿ�Ķ˿�546 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_DHCP6);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_DHCP6;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,17);
    CDS_DL_IPF_FILTER_SET_PORT_HI(pstFilter,546);
    CDS_DL_IPF_FILTER_SET_PORT_LOW(pstFilter,546);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_DHCPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*����ICMP Router Solicitation Filter����, Э���58��Type 133�� code 0 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_RS);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_RS;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,58);
    CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,133);
    CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_ICMPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);


    /*����ICMP Router Advertisement Filter����, Э���58��Type 134�� code 0 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_RA);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_RA;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,58);
    CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,134);
    CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_ICMPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*����ICMP Neighbor Solicitation Filter����, Э���58��Type 135�� code 0 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_NS);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_NS;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,58);
    CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,135);
    CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_ICMPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*����ICMP Neighbor Advertisement Filter����, Э���58��Type 136�� code 0 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_NA);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_NA;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,58);
    CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,136);
    CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_ICMPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*����ICMP REDIRECT Filter����, Э���58��Type 137�� code 0 */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_REDIRECT);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_REDIRECT;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,58);
    CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,137);
    CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_ICMPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*����NDIS ICMP ECHO REQUEST����, Э���58��Type 128�� code 0��Ŀ�ĵ�ַΪFE80��ͷ */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_LL_PING6);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_LL_PING6;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_PROTOCOL(pstFilter,58);
    CDS_DL_IPF_FILTER_SET_ICMP_TYPE(pstFilter,128);
    CDS_DL_IPF_FILTER_SET_ICMP_CODE(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_DST_LL_ADDR_FE80(pstFilter);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,0);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_ICMPV6);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*����NDIS Ŀ�ĵ�ַFE80��ͷ���� */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_LL_FE80);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_LL_FE80;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_DST_LL_ADDR_FE80(pstFilter);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,1);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_LL_FE80);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    /*����NDIS Ŀ�ĵ�ַFF��ͷ���� */
    pstFilter = CDS_GET_DL_IPF_FILTER_PTR(CDS_IPF_DL_FITLER_ID_LL_FF);
    pstFilter->u32FilterID = CDS_IPF_DL_FITLER_ID_LL_FF;
    CDS_DL_IP_FILTER_SET_IP_TYPE(pstFilter,IPF_IPTYPE_V6);
    CDS_DL_IPF_FILTER_SET_DST_LL_ADDR_FF(pstFilter);
    CDS_DL_IPF_FILTER_SET_PRIORITY(pstFilter,1);
    CDS_DL_IPF_FILTER_SET_BEARER_ID(pstFilter,CDS_ADS_DL_IPF_BEARER_ID_LL_FF);
    CDS_DL_IPF_FILTER_ENABLE_FILTER(pstFilter);

    g_stCdsIpfCtrlEntity.stFilterCfgStru.ulDownLinkUsedNum = 10;

    return;
}
VOS_UINT32 CDS_StartAdqEmptyProctectTmr(VOS_VOID)
{

    /*������*/
    if (VOS_NULL_PTR != CDS_GET_ADQ_EMPTY_TMR_PTR())
    {
        return PS_SUCC;
    }

    if (VOS_OK != PS_START_REL_TIMER(&(CDS_GET_ADQ_EMPTY_TMR_PTR()),
                                    UEPS_PID_CDS,
                                    CDS_IPF_AD_EMPTY_PROTECT_TMR_LEN,
                                    CDS_TMR_ID_ADQ_EMPTY_PROCTECT,
                                    0,
                                    VOS_RELTIMER_NOLOOP))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_StartAdqEmptyProctectTmr : Start Timer Fail ");
        CDS_PRINT_ERROR(CDS_StartAdqEmptyProctectTmr_ENUM,CDS_PRINT_START_TIMER_FAIL);
        return PS_FAIL;
    }

    CDS_DBG_UL_ADQ_START_EMPTY_TMR_NUM(1);

    return PS_SUCC;
}
VOS_VOID CDS_StopAdqEmptyProctectTmr(VOS_VOID)
{
    /*��ֹͣ*/
    if (VOS_NULL_PTR == CDS_GET_ADQ_EMPTY_TMR_PTR())
    {
        return ;
    }

    if (VOS_OK != PS_STOP_REL_TIMER(&(CDS_GET_ADQ_EMPTY_TMR_PTR())))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_StopAdqEmptyProctectTmr : Stop Timer Fail ");
        CDS_PRINT_ERROR(CDS_StopAdqEmptyProctectTmr_ENUM,CDS_PRINT_STOP_TIMER_FAIL);
        return ;
    }

    CDS_DBG_UL_ADQ_STOP_EMPTY_TMR_NUM(1);

    return ;
}
VOS_VOID CDS_AdqEmptyProctectTimeOutProc(VOS_VOID)
{

    CDS_DBG_UL_ADQ_EMPTY_TMR_TIMEOUT_NUM(1);

    /*ֹͣ��ʱ��*/
    CDS_StopAdqEmptyProctectTmr();

    /*�����ڴ�*/
    CDS_AllocMemForAdq();
    return ;
}


VOS_VOID CDS_FreeIpfDlSrcMem(VOS_VOID)
{
    LUP_QUEUE_STRU                   *pstDlFreeQue ;
    VOS_UINT32                           ulIdleCD;
    VOS_UINT32                        ulIdleBD;
    VOS_UINT32                        ulBusyBD;
    VOS_UINT32                        ulCanFree;
    VOS_UINT32                        ulQueCnt;
    VOS_UINT32                        ulCnt;
    TTF_MEM_ST                       *pstSrcTtf;

    pstDlFreeQue = CDS_IPF_DL_SRCMEM_FREE_QUE();
    CDS_ASSERT(VOS_NULL_PTR != pstDlFreeQue);

    ulQueCnt = LUP_QueCnt(pstDlFreeQue);
    if (0 == ulQueCnt)
    {
        return;
    }

    /*get busy bd num*/
    ulIdleBD = LDRV_IPF_GET_DLBD_NUM(&ulIdleCD);
    ulBusyBD = IPF_DLBD_DESC_SIZE - ulIdleBD;
    if (ulQueCnt >= ulBusyBD)
    {
        ulCanFree = ulQueCnt - ulBusyBD;
    }
    else
    {
        CDS_ERROR_LOG3(UEPS_PID_CDS, "CDS_FreeIpfDlSrcMem:Buff Num Less IPF Busy BD Num.quecnt,busybd,idlebd",ulQueCnt,ulBusyBD,ulIdleBD);
        CDS_PRINT_ERROR2(CDS_FreeIpfDlSrcMem_ENUM,CDS_PRINT_PARA_ERR,ulQueCnt,ulBusyBD);
        CDS_PRINT_ERROR1(CDS_FreeIpfDlSrcMem_ENUM,CDS_PRINT_PARA_ERR,ulIdleBD);
        PS_PRINTF("CDS_FreeIpfDlSrcMem : src free que less than busy bd. quecnt=%d,busybd=%d,idlebd=%d.\n",ulQueCnt,ulBusyBD,ulIdleBD);
        CDS_DBG_DL_IPF_FREE_SRCMEM_ERROR(1);
        return;
    }

    /*free src mem*/
    for (ulCnt = 0; ulCnt < ulCanFree; ulCnt ++)
    {
        if (PS_SUCC != LUP_DeQue(pstDlFreeQue,(VOS_VOID **)&pstSrcTtf))
        {
            return;
        }

        TTF_MemFree(UEPS_PID_CDS,pstSrcTtf);
        CDS_DBG_DL_IPF_FREE_SRCMEM_NUM(1);
    }

    return;
}


VOS_INT32 CDS_UlAdqEmptyIntCB(IPF_ADQ_EMPTY_E  eAdqEmpty )
{
    CDS_DBG_UL_RX_ADQ_EMPTY_INT(1);

    /*���¼�����ͳ��*/
    if (IPF_EMPTY_ADQ0 == eAdqEmpty)
    {
        CDS_DBG_UL_ADQ_AD0_EMPTY_INT_NUM(1);
    }
    else if (IPF_EMPTY_ADQ1 == eAdqEmpty)
    {
        CDS_DBG_UL_ADQ_AD1_EMPTY_INT_NUM(1);
    }
    else
    {
        CDS_DBG_UL_ADQ_AD0_EMPTY_INT_NUM(1);
        CDS_DBG_UL_ADQ_AD1_EMPTY_INT_NUM(1);
    }

    /*����CDS����*/
    CDS_SendEventToCds(CDS_EVENT_UL_ADQ_EMPTY);
    return 0;
}



VOS_UINT32 CDS_IpfInit(VOS_VOID )
{
    IPF_COMMON_PARA_S stCommPara;
    IPF_CHL_CTRL_S    stChlCtrl;
    struct mdrv_ipf_ops stIpfOps;

    /*��ʼ��ipfע��ṹ��*/
    stIpfOps.adq_empty_cb = VOS_NULL;
    stIpfOps.rx_complete_cb = VOS_NULL;

    /*��ʼ��ʱIP���˵Ĳ�������*/
    stCommPara.bEspSpiDisable  = PS_FALSE;              /* ESP SPI����ƥ������ź� */
    stCommPara.bAhSpiDisable   = PS_FALSE;              /* AH SPI����ƥ������ź� */
    stCommPara.bEspAhSel       = PS_TRUE;               /* 0ѡESP��1ѡAH */
    stCommPara.bIpv6NextHdSel  = PS_TRUE;
    stCommPara.eMaxBurst       = IPF_BURST_16;          /* BURST��󳤶� */
    stCommPara.bSpWrrModeSel   = PS_FALSE;
    stCommPara.bSpPriSel       = PS_FALSE;              /* SP���ȼ�ѡ�� */
    stCommPara.bFltAddrReverse = PS_FALSE;              /* �������е�ַ�Ĵ�����С������˳�� 0��ʾ��� */
    stCommPara.bFilterSeq      = PS_FALSE;              /* ����������˳��ָʾ */

    /*������������������*/
    stCommPara.bAdReport       = PS_FALSE;              /* AD�ϱ�ѡ��PS_FALSE:�ϱ��ṹ��ָ�룬 PS_TRUE:�ϱ�����ָ�� */
    stCommPara.bMultiModeEn    = PS_TRUE;               /* ��ͨ����̬ģʽ��PS_TRUEΪʹ�� */
    stCommPara.bMultiFilterChainEn = PS_TRUE;           /* ��ͨ�����������PS_TRUEΪʹ��*/

    if (IPF_SUCCESS != LDRV_IPF_INIT(&stCommPara))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_INIT Fail!\n");
        return PS_FAIL;
    }

    /*����ͨ������ģʽ: �����Ұ��ƣ�֧����ʽ����*/
    stChlCtrl.u32WrrValue      = 16*1024;
    stChlCtrl.bDataChain       = PS_FALSE;
    stChlCtrl.bEndian          = PS_FALSE;
    stChlCtrl.eIpfMode         = IPF_MODE_FILTERANDTRANS;
    if (IPF_SUCCESS != LDRV_IPF_CONFIG_ULCHAN(&stChlCtrl))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_CONFIG_ULCHAN Fail!\n");
        return PS_FAIL;
    }

    /*����ͨ������ģʽ: �����Ұ��ƣ�֧����ʽ����*/
    stChlCtrl.u32WrrValue      = 16*1024;
    stChlCtrl.bDataChain       = PS_TRUE;
    stChlCtrl.bEndian          = PS_FALSE;
    stChlCtrl.eIpfMode         = IPF_MODE_FILTERANDTRANS;
    if (IPF_SUCCESS != LDRV_IPF_CONFIG_DLCHAN(&stChlCtrl))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_CONFIG_DLCHAN Fail!\n");
        return PS_FAIL;
    }

    /*ע������RD����жϺ�ADQ���жϻص�����*/
    stIpfOps.rx_complete_cb = CDS_UlIpfIntCB;
    stIpfOps.adq_empty_cb = CDS_UlAdqEmptyIntCB;

    if (IPF_SUCCESS != LDRV_IPF_REG_OPS(&stIpfOps))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_REG_OPS Fail!\n");
        return PS_FAIL;
    }

    /*����RD����жϳ�ʱʱ��*/
    if (IPF_SUCCESS != LDRV_IPF_CONFIG_TIMEOUT(CDS_IPF_BD_CMP_INT_TIMEOUT))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_CONFIG_TIMEOUT Fail!\n");
        return PS_FAIL;
    }

    /*����AD������ֵ*/
    if (IPF_SUCCESS != LDRV_IPF_CONFIG_ADTHRED(CDS_IPF_AD_LEN_THRESHOLD,CDS_IPF_AD_LEN_THRESHOLD))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_CONFIG_ADTHRED Fail!\n");
        return PS_FAIL;
    }

    /*�������н��ն���*/
    if (PS_SUCC != LUP_CreateQue(UEPS_PID_CDS, &(CDS_GET_IPF_DL_SDU_QUE()),CDS_IPF_DL_SDU_QUE_SIZE))
    {
        PS_PRINTF("CDS_IpfInit : Create DL Sdu Que Fail.\n");
        return PS_FAIL;
    }

    /*����Դ�ڴ��ͷŶ���*/
    if (PS_SUCC != LUP_CreateQue(UEPS_PID_CDS, &(CDS_IPF_DL_SRCMEM_FREE_QUE()),CDS_IPF_DL_SRCMEM_FREE_QUE_SIZE))
    {
        PS_PRINTF("CDS_IpfInit : Create IPF DL Src Mem Free  Que Fail. \n");
        return PS_FAIL;
    }

    /*ʹ������IP����*/
    /*lint -e730 -e506 -e944*/
    if(IPF_SUCCESS != LDRV_IPF_ENABLE_CHAN(IPF_CHANNEL_UP, VOS_TRUE))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_ENABLE_CHAN UL Fail!\n");
        return PS_FAIL;
    }

    /*ʹ������IP����*/
    if(IPF_SUCCESS != LDRV_IPF_ENABLE_CHAN(IPF_CHANNEL_DOWN, VOS_TRUE))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_ENABLE_CHAN DL Fail!\n");
        return PS_FAIL;
    }

    /*ע��TTF_MEM_SETƫ��*/
    if (IPF_SUCCESS != LDRV_IPF_SET_DBUF_PARA(TTF_OFFSET_OF(TTF_MEM_ST, pData),
            TTF_OFFSET_OF(TTF_MEM_ST, usUsed), TTF_OFFSET_OF(TTF_MEM_ST, pNext)))
    {
        PS_PRINTF("CDS_IpfInit : LDRV_IPF_SET_DBUF_PARA Fail!\n");
        return PS_FAIL;
    }
    /*lint +e730 +e506 +e944*/

    /*��ʼ������IPF������*/
    CDS_InitDlIpfFilter();

    /*����ADQ�ڴ�*/
    CDS_AllocMemForAdq();

    (VOS_VOID)CDS_DisableDlIPFFilter(MODEM_ID_0);
    (VOS_VOID)CDS_DisableDlIPFFilter(MODEM_ID_1);
    (VOS_VOID)CDS_DisableDlIPFFilter(MODEM_ID_2);

    return PS_SUCC;
}
VOS_UINT32 CDS_ChangeDlIpfFilterType(VOS_UINT16  usModemId)
{
    VOS_UINT32              ulCnt;
    IPF_FILTER_CONFIG_S    *pstFilter;

    if (usModemId >= CDS_MAX_MODEM_NUM)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "CDS_ChangeDlIpfFilterType : Modem ID Error.", usModemId);
        CDS_PRINT_ERROR1(CDS_ChangeDlIpfFilterType_ENUM,CDS_PRINT_MODEM_ID_ERR,usModemId);
        return PS_FAIL;
    }

    for (ulCnt = 1; ulCnt < CDS_GET_DL_IPF_FILTER_NUM(); ulCnt ++)
    {
        pstFilter = CDS_GET_DL_IPF_FILTER_PTR(ulCnt);

        CDS_DL_IPF_CLR_EX_FILTER_FLG(pstFilter->u32FilterID);

        /*Modem1����Ϊ��չ������*/
        if (MODEM_ID_0 < usModemId)
        {
            CDS_DL_IPF_SET_EX_FILTER_FLG(pstFilter->u32FilterID);
        }
    }

    return PS_SUCC;
}
VOS_UINT32 CDS_EnableDlIPFFilter(VOS_UINT16  usModemId)
{
    IPF_FILTER_CHAIN_TYPE_E  enFCType;

    /*����ModemId���ֹ������׵�ַ*/
    if (MODEM_ID_0 == usModemId)
    {
        enFCType = IPF_MODEM0_DLFC;
    }
    else if (MODEM_ID_1 == usModemId)
    {
        enFCType = IPF_MODEM1_DLFC;
    }
    else if (MODEM_ID_2 == usModemId)
    {
        enFCType = IPF_MODEM2_DLFC;
    }
    else
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS, "CDS_EnableDlIPFFilter : Input Para Error. ModemId,MaxModemNum:", usModemId,CDS_MAX_MODEM_NUM);
        CDS_PRINT_ERROR2(CDS_EnableDlIPFFilter_ENUM,CDS_PRINT_MODEM_ID_ERR, usModemId,CDS_MAX_MODEM_NUM);
        return PS_FAIL;
    }

    /*�ı�����IPF������������*/
    if (PS_SUCC != CDS_ChangeDlIpfFilterType(usModemId))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS, "CDS_EnableDlIPFFilter : Change DL Filter Type Fail.");
        CDS_PRINT_ERROR(CDS_EnableDlIPFFilter_ENUM,LL2_FUNCTION_RETURN_ERROR);
        return PS_FAIL;
    }

    /*�������úõĹ��������ø�����IPF*/
    if (IPF_SUCCESS != LDRV_IPF_SET_FILTER(enFCType,
                                         CDS_GET_DL_IPF_FILTER_ARRAY(),
                                         CDS_GET_DL_IPF_FILTER_NUM()))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "CDS_EnableDlIPFFilter : Enable Dl IPF Filter Fail.Filter Num:", CDS_GET_DL_IPF_FILTER_NUM());
        CDS_PRINT_ERROR1(CDS_EnableDlIPFFilter_ENUM,CDS_PRINT_DRV_RETURN_ERR,CDS_GET_DL_IPF_FILTER_NUM());
        return PS_FAIL;
    }
    else
    {
        CDS_INFO_LOG(UEPS_PID_CDS, "CDS_EnableDlIPFFilter : Enable Dl IPF Filter Success.");
        CDS_PRINT_INFO(CDS_EnableDlIPFFilter_ENUM,CDS_PRINT_IPF_FILTER_INFO);
        return PS_SUCC;
    }
}
VOS_UINT32 CDS_DisableDlIPFFilter(MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT32               ulFilterNum = 0;
    IPF_FILTER_CHAIN_TYPE_E  enFCType;

    /*����ModemId���ֹ������׵�ַ*/
    if (MODEM_ID_0 == enModemId)
    {
        enFCType = IPF_MODEM0_DLFC;
    }
    else if (MODEM_ID_1 == enModemId)
    {
        enFCType = IPF_MODEM1_DLFC;
    }
    else if (MODEM_ID_2 == enModemId)
    {
        enFCType = IPF_MODEM2_DLFC;
    }
    else
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "CDS_DisableDlIPFFilter : Modem ID Error.", enModemId);
        CDS_PRINT_ERROR1(CDS_DisableDlIPFFilter_ENUM,CDS_PRINT_MODEM_ID_ERR,enModemId);
        return PS_FAIL;
    }

    /*ȡ������������*/
    if (IPF_SUCCESS != LDRV_IPF_SET_FILTER(enFCType,
                                         CDS_GET_DL_IPF_FILTER_ARRAY(),
                                         ulFilterNum))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS, "CDS_DisableDlIPFFilter : Disable Dl IPF Filter Fail.Filter Num:", CDS_GET_DL_IPF_FILTER_NUM());
        CDS_PRINT_ERROR1(CDS_DisableDlIPFFilter_ENUM,CDS_PRINT_DRV_RETURN_ERR,CDS_GET_DL_IPF_FILTER_NUM());
        return PS_FAIL;
    }
    else
    {
        /*CDS_INFO_LOG(UEPS_PID_CDS, "CDS_DisableDlIPFFilter : Disable Dl IPF Filter Success.");*/
        return PS_SUCC;
    }
}
VOS_VOID CDS_SaveIpfDlSrcMem(const IPF_CONFIG_DLPARAM_S *pstIpfDlBdBuff, VOS_UINT32 ulSaveNum)
{
    LUP_QUEUE_STRU                   *pstDlFreeQue;
    VOS_UINT32                        ulCnt;
    TTF_MEM_ST                       *pstSrcMem;

    CDS_ASSERT(VOS_NULL_PTR != pstIpfDlBdBuff);

    if (ulSaveNum > IPF_DLBD_DESC_SIZE)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_SaveIpfDlMemInfo:Input Bd Num Error.",ulSaveNum);
        CDS_PRINT_ERROR1(CDS_SaveIpfDlSrcMem_ENUM,CDS_PRINT_PARA_INPUT_ERR,ulSaveNum);
        return ;
    }

    pstDlFreeQue = CDS_IPF_DL_SRCMEM_FREE_QUE();
    CDS_ASSERT(VOS_NULL_PTR != pstDlFreeQue);

    for (ulCnt = 0; ulCnt < ulSaveNum; ulCnt ++)
    {
        pstSrcMem = (TTF_MEM_ST*)pstIpfDlBdBuff[ulCnt].u32Data;
        if (PS_SUCC != LUP_EnQue(pstDlFreeQue,pstSrcMem))
        {
            CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_SaveIpfDlMemInfo: Src Mem Leak.",ulCnt,ulSaveNum);
            CDS_PRINT_ERROR2(CDS_SaveIpfDlSrcMem_ENUM,CDS_PRINT_ENQUE_FAIL,ulCnt,ulSaveNum);
            PS_PRINTF("CDS_SaveIpfDlMemInfo: Buffer Full!! cnt=%d,ulSaveNum=%d\n",ulCnt,ulSaveNum);
            TTF_MemFree(UEPS_PID_CDS,pstSrcMem);
            CDS_DBG_DL_IPF_SAVE_SRCMEM_FAIL_NUM(1);
            continue;
        }

        CDS_DBG_DL_IPF_SAVE_SRCMEM_SUCC_NUM(1);
    }

    return ;
}



VOS_VOID CDS_ConfigDlIPF(VOS_VOID)
{
    VOS_UINT32              ulIdleBD;
    VOS_UINT32              ulIdleCD;
    VOS_UINT32              ulCnt;
    VOS_UINT32              ulCfgCD;
    TTF_MEM_ST             *pstSrcMem;
    IPF_CONFIG_DLPARAM_S   *pstDlCfgPara;
    int                     intLockLevel;
    VOS_UINT16              usModemId;

    /*��������IPF�ͷ�Դ�ڴ�*/
    CDS_FreeIpfDlSrcMem();

    /*������п���BD/CD����*/
    ulIdleBD = (VOS_UINT32)LDRV_IPF_GET_DLBD_NUM(&ulIdleCD);
    if (0 == ulIdleBD)
    {
        /*û�п���BD*/
        CDS_DBG_DL_IPF_CFG_HAVE_NO_BD(1);
        return;
    }

    if (ulIdleBD > IPF_DLBD_DESC_SIZE)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_GUConfigDlIPF : DL Idle BD Num Error.",ulIdleBD);
        CDS_PRINT_ERROR1(CDS_ConfigDlIPF_ENUM,CDS_PRINT_IDLE_BD_NUM_ERR,ulIdleBD);
        return;
    }

    if (0 == ulIdleCD)
    {
        /*û�п���CD*/
        CDS_DBG_DL_IPF_CFG_HAVE_NO_CD(1);
        return;
    }

    ulCfgCD = 0;
    for (ulCnt = 0; ulCnt < ulIdleBD; ulCnt ++)
    {
        /**/
        pstDlCfgPara = &(g_stCdsIpfCtrlEntity.astDlIpfCfgPara[ulCnt]);
        if (PS_SUCC != LUP_PeekQueHead(CDS_GET_IPF_DL_SDU_QUE(),(VOS_VOID **)&pstSrcMem))
        {
            break;
        }

        /*Get BD*/
        ulCfgCD += CDS_GetTtfMemCnt(pstSrcMem);
        if (ulCfgCD > ulIdleCD)
        {
            CDS_DBG_DL_IPF_CFG_CD_NOT_ENOUGH(1);
            break;
        }

        /*��ʵ����*/
        intLockLevel = VOS_SplIMP();
        if (PS_SUCC != LUP_DeQue(CDS_GET_IPF_DL_SDU_QUE(),(VOS_VOID **)&pstSrcMem))
        {
            /*�쳣������Ӧ�ò���*/
            VOS_Splx(intLockLevel);
            break;
        }
        VOS_Splx(intLockLevel);

        pstDlCfgPara->u32Data       = (VOS_UINT32)(pstSrcMem);
        pstDlCfgPara->u16Len        = CDS_DL_GET_PKT_LEN_FROM_TTF(pstSrcMem);
        pstDlCfgPara->u16UsrField1  = CDS_DL_GET_MODEMID_RABID_FROM_TTF(pstSrcMem);

        usModemId = CDS_DL_GET_MODEMID_FROM_TTF(pstSrcMem);

        if (MODEM_ID_0 == usModemId)
        {
            CDS_DL_BD_SET_ATTR_WITH_FC_HDR(pstDlCfgPara->u16Attribute,IPF_MODEM0_DLFC);
        }
        else if (MODEM_ID_1 == usModemId)
        {
            CDS_DL_BD_SET_ATTR_WITH_FC_HDR(pstDlCfgPara->u16Attribute,IPF_MODEM1_DLFC);
        }
        else
        {
            CDS_DL_BD_SET_ATTR_WITH_FC_HDR(pstDlCfgPara->u16Attribute,IPF_MODEM2_DLFC);
        }

    }

    /*�������й��˰���Ϊ0��ֱ�ӷ���*/
    if (0 == ulCnt)
    {
        return;
    }

    /*���һ��BD�����жϱ�־*/
    pstDlCfgPara = &(g_stCdsIpfCtrlEntity.astDlIpfCfgPara[ulCnt - 1]);
    CDS_DL_BD_SET_ATTR_INT_FLG(pstDlCfgPara->u16Attribute);

    /*��������IPF����*/
    if (IPF_SUCCESS != LDRV_IPF_CONFIG_DLBD(ulCnt,g_stCdsIpfCtrlEntity.astDlIpfCfgPara))
    {
        /*����ʧ�ܺ�Դ�ڴ��ͷ�*/
        ulIdleBD = ulCnt;
        for (ulCnt = 0; ulCnt < ulIdleBD; ulCnt ++)
        {
            pstDlCfgPara = &(g_stCdsIpfCtrlEntity.astDlIpfCfgPara[ulCnt]);
            pstSrcMem = (TTF_MEM_ST*)(pstDlCfgPara->u32Data);
            TTF_MemFree(UEPS_PID_CDS,pstSrcMem);
        }

        CDS_DBG_DL_IPF_CFG_BD_FAIL_NUM(ulIdleBD);
        return;
    }

    /*����Src Mem*/
    CDS_SaveIpfDlSrcMem(g_stCdsIpfCtrlEntity.astDlIpfCfgPara,ulCnt);

    CDS_DBG_DL_IPF_CFG_BD_SUCC_NUM(ulCnt);

    return;
}
VOS_UINT32 CDS_ConfigUlAdq(VOS_UINT32 ulAdType, VOS_UINT32 ulCanCfgAdNum)
{
    VOS_UINT32           ulCnt;
    VOS_UINT32           ulAdLen;
    TTF_MEM_ST          *pstDstMem;
    IPF_AD_DESC_S       *pstAdDesc;
    VOS_UINT32           ulTmp;

    /*����ж�*/
    if ((0 == ulCanCfgAdNum) || (CDS_IPF_ULAD_DESC_SIZE < ulCanCfgAdNum))
    {
        return 0;
    }

    if (ulAdType >= IPF_AD_MAX)
    {
        return 0;
    }

    /*���������ڴ泤��*/
    if (IPF_AD_0 == ulAdType)
    {
        ulAdLen = CDS_IPF_AD_0_PKT_LEN;
    }
    else
    {
        ulAdLen = CDS_IPF_AD_1_PKT_LEN;
    }

    /*ѭ�������ڴ棬����AD������*/
    for (ulCnt = 0; ulCnt < ulCanCfgAdNum; ulCnt ++)
    {
        pstDstMem = CDS_AllocTtfMem(ulAdLen);
        if (VOS_NULL_PTR == pstDstMem)
        {
            break;
        }

        /*����AD DESC*/
        CDS_DBG_UL_ADQ_ALLOC_MEM_NUM(1);
        pstAdDesc = &(g_stCdsIpfCtrlEntity.astUlAdBuff[ulCnt]);
        pstAdDesc->u32OutPtr0 = (VOS_UINT32)(pstDstMem->pData);
        pstAdDesc->u32OutPtr1 = (VOS_UINT32)pstDstMem;
    }

    if (0 == ulCnt)
    {
        return 0;
    }

    /*����AD*/
    if (IPF_SUCCESS != LDRV_IPF_CONFIG_ULAD((IPF_AD_TYPE_E)ulAdType,ulCnt,g_stCdsIpfCtrlEntity.astUlAdBuff))
    {
        /*����ʧ�ܣ��ͷ��ڴ�*/
        ulTmp = ulCnt;
        for (ulCnt = 0; ulCnt < ulTmp; ulCnt ++)
        {
            pstAdDesc = &(g_stCdsIpfCtrlEntity.astUlAdBuff[ulCnt]);
            pstDstMem = (TTF_MEM_ST*)(pstAdDesc->u32OutPtr1);
            TTF_MemFree(UEPS_PID_CDS,pstDstMem);
            CDS_DBG_UL_ADQ_FREE_MEM_NUM(1);
        }

        CDS_DBG_UL_ADQ_CFG_ADQ_FAIL_NUM(1);
        return 0;
    }

    CDS_DBG_UL_ADQ_CFG_AD_NUM(ulCnt);
    CDS_DBG_UL_ADQ_CFG_ADQ_SUCC_NUM(1);

    return ulCnt;
}


VOS_VOID CDS_AllocMemForAdq(VOS_VOID)
{
    VOS_UINT32             ulAd0CanCfgNum    = 0;
    VOS_UINT32             ulAd1CanCfgNum    = 0;
    VOS_UINT32          ulAd0CfgNum       = CDS_IPF_ULAD_DESC_SIZE;
    VOS_UINT32          ulAd1CfgNum       = CDS_IPF_ULAD_DESC_SIZE;


    /*���AD0/AD1 ������AD����*/
    if (IPF_SUCCESS != LDRV_IPF_GET_ULAD_NUM(&ulAd0CanCfgNum,&ulAd1CanCfgNum))
    {
        return;
    }

    /*����AD0*/
    if (0 != ulAd0CanCfgNum)
    {
        ulAd0CfgNum = CDS_ConfigUlAdq(IPF_AD_0,ulAd0CanCfgNum);
        CDS_DBG_UL_ADQ_CFG_AD0_NUM(ulAd0CfgNum);
    }

    /*����AD1*/
    if (0 != ulAd1CanCfgNum)
    {
        ulAd1CfgNum = CDS_ConfigUlAdq(IPF_AD_1,ulAd1CanCfgNum);
        CDS_DBG_UL_ADQ_CFG_AD1_NUM(ulAd1CfgNum);
    }

    /*ֻҪ��һ������û���������ڴ棬������������ʱ��*/
    if (((CDS_IPF_ULAD_START_TMR_THRESHOLD < ulAd0CanCfgNum) && (0 == ulAd0CfgNum))
       || ((CDS_IPF_ULAD_START_TMR_THRESHOLD < ulAd1CanCfgNum) && (0 == ulAd1CfgNum)))
    {
        /*����������ʱ��*/
        if (PS_SUCC != CDS_StartAdqEmptyProctectTmr())
        {
            CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_AllocMemForAdq : Start Protect Timer Fail.");
            CDS_PRINT_ERROR(CDS_AllocMemForAdq_ENUM,CDS_PRINT_START_TIMER_FAIL);
            return;
        }
    }

    return;
}
TTF_MEM_ST* CDS_RdTransferTtfMem(const IPF_RD_DESC_S *pstRdDesc)
{
    TTF_MEM_ST     *pstIpPkt;

    /*��Outָ��ת��ΪTTFָ��*/
    pstIpPkt = (TTF_MEM_ST*)(pstRdDesc->u32OutPtr);
    if (VOS_NULL_PTR == pstIpPkt)
    {
        return VOS_NULL_PTR;
    }

    /*������������*/
    pstIpPkt->usUsed = pstRdDesc->u16PktLen;

    /*����FilterResult(2Byte)/ModemId(1Byte)/RabId(1Bytes)*/
    CDS_UL_SAVE_RD_INFO_TO_TTF(pstIpPkt,pstRdDesc);
    return pstIpPkt;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

