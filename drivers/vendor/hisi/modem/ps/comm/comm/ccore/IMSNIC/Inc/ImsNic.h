/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ImsNic.h
  �� �� ��   : ����
  ��    ��   : caikai
  ��������   : 2013��7��16��
  ����޸�   :
  ��������   : IMS���������ڲ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��30��
    ��    ��   : caikai
    �޸�����   : �����ļ�

******************************************************************************/


#ifndef __IMSNIC_H__
#define __IMSNIC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "ImsNicInterface.h"

#if( FEATURE_ON == FEATURE_IMS )
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "PsCommonDef.h"

#if (VOS_OS_VER == VOS_WIN32)
#include  "VxWorksStub.h"
#endif  /* VOS_OS_VER == VOS_WIN32 */


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define UEPS_PID_IMSNIC                    UEPS_PID_IPS_CCORE


#define IMS_NIC_RAB_ID_MAX_NUM             (11)                         /* RAB��������ֵ */

#define IMS_NIC_RAB_ID_OFFSET              (5)

#define IMS_NIC_RAB_ID_MIN                 (5)                          /* Rab Id����Сֵ */
#define IMS_NIC_RAB_ID_MAX                 (15)                         /* Rab Id�����ֵ */

#define IMS_NIC_RAB_ID_INVALID             (0xFF)

#define IMS_NIC_ETH_HDR_SIZE               (14)
#define IMS_NIC_ETHER_ADDR_LEN             (6)

#define IMS_NIC_IPV4_VERSION               (4)                          /* IPͷ����IP V4�汾�� */
#define IMS_NIC_IPV6_VERSION               (6)                          /* IPͷ����IP V6�汾�� */
#define IMS_NIC_IP_VERSION_POS             (4)                          /* IP���ݰ���Э��汾�ֶ�ƫ�� */
#define IMS_NIC_IP_VERSION_MASK            (0x0F)                       /* IP���ݰ���Э��汾�ֶ����� */

#define IMS_NIC_MIN_IPPKT_LEN              (20)                         /* ��СIP������ */
#define IMS_NIC_MAX_IPPKT_LEN              (1500)                       /* IMS���������޶����IP������ */

#define IMS_NIC_IPPKT_OFFSET               (4)                          /* IP�����ϲ㴫�µ������е�ƫ�� */

#define IMS_NIC_ETHERTYPE_IPV4             (0x0800)                     /* ��������ʽ����ʾIPv4������  */
#define IMS_NIC_ETHERTYPE_IPV6             (0x86DD)                     /* ��������ʽ����ʾIPv6������  */
#define IMS_NIC_ETHERTYPE_ARP              (0x0806)                     /* ��������ʽ����ʾARP������  */

#define IMS_NIC_CMD_LEN                    (200)

#define IMS_NIC_IP_ADDR_MAX_LENGTH         (16)                         /* IP��ַ����󳤶ȣ�ȡIPV6�ĳ��� */

#define IMS_NIC_UL_SEND_BUFF_SIZE          (1520)                       /* IMS�����������з��ͻ����С */

#define IMS_NIC_SPEED_100M                 (100000000)                  /* 100Mbs */

#define IMS_NIC_IPV6_ADDR_BIT_LEN          (128)
#define IMS_NIC_IPV6_ADDR_STR_LEN          (39)
#define IMS_NIC_IPV6_STR_RFC2373_TOKENS    (8)
#define IMS_NIC_IPV6_STR_DELIMITER         ':'                          /* RFC2373ʹ�õ�IPV6�ı���﷽ʽʹ�õķָ��� */

#define IMS_NIC_MODEM_ID_LEN               (2)                          /* ModemIdռ��2���ֽ�*/
#define IMS_NIC_MODEM_ID_OFFSET            (4)                          /* ��д��ά�ɲ�ʱʹ�ã������ֽڶ��� */

#define IMS_NIC_LOG_RECORD_MAX_NUM         (10)
#define IMS_NIC_LOG_PARAM_MAX_NUM          (4)

#define IMS_NIC_TYPE_HEX                   (16)
#define IMS_NIC_TYPE_DEC                   (10)

#define IMS_NIC_MTU_DEFAULT_VALUE          (1280)                       /* MTUĬ��ֵ */

#define IMS_NIC_ROUND_UP(x, n)             (((x)+(n)-1U) & ~((n)-1U))  /* ȡn�ı��� */

#define IMS_NIC_DEFAULT_ROUTE_GATEWAY      (0x01010101)                 /* ����IPV4��̬·��ʱ���õ���һ�� */
#define IMS_NIC_DEFAULT_IPV6_MASK_LEN      (128)                        /* IPV6Ĭ�ϵ����볤����128 */
#define IMS_NIC_MAC_STR_LEN                (15)                         /* MAC��ַ����xxxx-xxxx-xxxx */
#define IMS_NIC_ENABLE_HOST_MODE           (1)                          /* ʹ������ģʽ */
#define IMS_NIC_ENABLE_IPV6_FORWARDING     (1)                          /* ʹ��IPV6ת�� */
#define IMS_NIC_DISABLE_IPV6_FORWARDING    (0)                          /* ȥʹ��IPV6ת�� */

#define IMS_NIC_IFNAMSIZ                   (16)                         /*�����������Ƴ���*/

/* DNS������ȡ4����������ֹ�ṹ���С����4�������� */
#define IMS_NIC_DNS_NUM_ADAPTER            IMS_NIC_ROUND_UP(IMS_NIC_MAX_DNS_SERVER_NUM,4)

#define IMS_NIC_IS_RAB_VALID(rabId) \
        ((rabId >= IMS_NIC_RAB_ID_MIN) && (rabId <= IMS_NIC_RAB_ID_MAX))

/* ͳ�Ʋ��� */
#define IMS_NIC_STATS_INC(type, n, modem)  \
        (g_astImsNicEntity[modem].stImsNicStatsInfo.aulStats[type] += n)

#define IMS_INC_STATS_SHOW(type, modem) \
        vos_printf("%s      %d \n", #type, g_astImsNicEntity[modem].stImsNicStatsInfo.aulStats[type])

/* ��ȡIMS��������ʵ�� */
#define IMS_NIC_GET_ENTITY_STRU(modem)              (&g_astImsNicEntity[modem])

/* ��ȡ���������� */
#define IMS_NIC_GET_NIC_NAME                        (g_stImsNicManageTbl.ucImsNicName)

/* ��ȡĿ��MAC��ַ */
#define IMS_NIC_GET_DST_MAC_ADDR(modem) \
        (g_stImsNicManageTbl.astImsNicElementTbl[modem].stIpv4Ethhead.aucEtherDhost)

#define IMS_NIC_IPV4_DNS_CONFIG(ipAddr, pstDnsInfo, pstPdnInfo) \
        IMS_NIC_DnsConfig(ipAddr, IMS_NIC_IPV4_ADDR_LENGTH, pstDnsInfo, pstPdnInfo)

#define IMS_NIC_IPV6_DNS_CONFIG(ipAddr, pstDnsInfo, pstPdnInfo) \
        IMS_NIC_DnsConfig(ipAddr, IMS_NIC_IPV6_ADDR_LENGTH, pstDnsInfo, pstPdnInfo)

#define IMS_NIC_IPCOM_DNSS_CONFIG(indx, ipAddrStr) \
        IMS_NIC_MNTN_TRACE2(ID_IMS_NIC_MNTN_TRACE_DNS_CFG, ipAddrStr, sizeof(ipAddrStr), indx, (VOS_UINT32)ipcom_sysvar_set(g_pcDnsSSysVarName[indx], (VOS_CHAR *)ipAddrStr, IPCOM_SYSVAR_FLAG_OVERWRITE))

#define IMS_NIC_IPCOM_DNSS_DEL(indx) \
        IMS_NIC_MNTN_TRACE2(ID_IMS_NIC_MNTN_TRACE_DNS_DEL, "", sizeof(""), indx, (VOS_UINT32)ipcom_sysvar_set(g_pcDnsSSysVarName[indx], (VOS_CHAR *)"", IPCOM_SYSVAR_FLAG_OVERWRITE))

/* ��ȡIMS��������������Ϣ�� */
#define IMS_NIC_GET_ELEMENT_TABLE(modem)            (&(g_stImsNicManageTbl.astImsNicElementTbl[modem]))

/* ��ȡIMS���������豸�ṹ */
#define IMS_NIC_GET_DEV_STRU_PTR(modem)             (&g_astImsNicDev[modem])

#define IMS_NIC_GET_MTU                             (g_stImsNicCtx.ulMtu)               /* ��ȡIMS��������MTUֵ */
#define IMS_NIC_SET_MTU(n)                          (g_stImsNicCtx.ulMtu = (n))         /* ����IMS��������MTUֵ */

#define IMS_NIC_GET_SAVED_UL_DATA_FUNC(modem)       (g_stImsNicCtx.pTmpSendFunc[modem])
#define IMS_NIC_SAVE_UL_DATA_FUNC(modem, pFunc)     (g_stImsNicCtx.pTmpSendFunc[modem]  = (pFunc))

#define IMS_NIC_IP4_TO_STR(str, ipArray)  \
        VOS_sprintf((VOS_CHAR *)str, "%d.%d.%d.%d", ipArray[0], ipArray[1], ipArray[2], ipArray[3])

#define IMS_NIC_SET_CMD_END(cmd, indx) \
        PS_MEM_SET(&cmd[indx], 0, sizeof(cmd) - indx); \
        (cmd[indx] = '\0')

#define IMS_NIC_MNTN_TRACE_DATA_OFFSET_LEN           /*lint -e(545) -e(413)*/TTF_OFFSET_OF(IMS_NIC_MNTN_TRACE_MSG_STRU, aucData)

#define IMS_NIC_INFO_LOG(ModuleId, str)
#define IMS_NIC_INFO_LOG1(ModuleId, str, para1)
#define IMS_NIC_INFO_LOG2(ModuleId, str, para1, para2)
#define IMS_NIC_INFO_LOG3(ModuleId, str, para1, para2, para3)
#define IMS_NIC_INFO_LOG4(ModuleId, str, para1, para2, para3, para4)

#ifdef __UT_CENTER__
#define IMS_NIC_WARNING_LOG(ModuleId, str) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_WARNING, THIS_FILE_ID, __LINE__, 0, 0, 0, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_WARNING_LOG1(ModuleId, str, para1) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, 0, 0, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_WARNING_LOG2(ModuleId, str, para1, para2) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, (VOS_INT32)para2, 0, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_WARNING_LOG3(ModuleId, str, para1, para2, para3) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, (VOS_INT32)para2, (VOS_INT32)para3, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_WARNING_LOG4(ModuleId, str, para1, para2, para3, para4) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, (VOS_INT32)para2, (VOS_INT32)para3, (VOS_INT32)para4); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_ERROR_LOG(ModuleId, str) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_ERROR, THIS_FILE_ID, __LINE__, 0, 0, 0, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_ERROR_LOG1(ModuleId, str, para1) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, 0, 0, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_ERROR_LOG2(ModuleId, str, para1, para2) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, (VOS_INT32)para2, 0, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_ERROR_LOG3(ModuleId, str, para1, para2, para3) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, (VOS_INT32)para2, (VOS_INT32)para3, 0); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)

#define IMS_NIC_ERROR_LOG4(ModuleId, str, para1, para2, para3, para4) \
        IMS_NIC_MNTN_LogSave(&g_stImsNicCtx.stLogEnt, ModuleId, LOG_LEVEL_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)para1, (VOS_INT32)para2, (VOS_INT32)para3, (VOS_INT32)para4); \
        IMS_NIC_MNTN_LogOutput(&g_stImsNicCtx.stLogEnt, ModuleId)
#else
#define IMS_NIC_WARNING_LOG(ModuleId, str)  \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_WARNING), (ModuleId), __FILE__, __LINE__, "%s \r\n", str)
#define IMS_NIC_WARNING_LOG1(ModuleId, str, para1)  \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_WARNING), (ModuleId), __FILE__, __LINE__, "%s, %d \r\n", str, para1)
#define IMS_NIC_WARNING_LOG2(ModuleId, str, para1, para2)   \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_WARNING), (ModuleId), __FILE__, __LINE__, "%s, %d, %d \r\n", str, para1, para2)
#define IMS_NIC_WARNING_LOG3(ModuleId, str, para1, para2, para3)    \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_WARNING), (ModuleId), __FILE__, __LINE__, "%s, %d, %d, %d \r\n", str, para1, para2, para3)
#define IMS_NIC_WARNING_LOG4(ModuleId, str, para1, para2, para3, para4) \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_WARNING), (ModuleId), __FILE__, __LINE__, "%s, %d, %d, %d, %d \r\n", str, para1, para2, para3, para4)

#define IMS_NIC_ERROR_LOG(ModuleId, str)    \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_ERROR), (ModuleId), __FILE__, __LINE__, "%s \r\n", str)
#define IMS_NIC_ERROR_LOG1(ModuleId, str, para1)    \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_ERROR), (ModuleId), __FILE__, __LINE__, "%s, %d \r\n", str, para1)
#define IMS_NIC_ERROR_LOG2(ModuleId, str, para1, para2) \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_ERROR), (ModuleId), __FILE__, __LINE__, "%s, %d, %d \r\n", str, para1, para2)
#define IMS_NIC_ERROR_LOG3(ModuleId, str, para1, para2, para3)  \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_ERROR), (ModuleId), __FILE__, __LINE__, "%s, %d, %d, %d \r\n", str, para1, para2, para3)
#define IMS_NIC_ERROR_LOG4(ModuleId, str, para1, para2, para3, para4)   \
        DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, PS_PRINT_ERROR), (ModuleId), __FILE__, __LINE__, "%s, %d, %d, %d, %d \r\n", str, para1, para2, para3, para4)
#endif

/* IMS����������ʼ���ڼ�Ĵ����ӡ��ֱ�Ӵ�ӡ������ */
#define IMS_NIC_INIT_LOG_PRINT(ModuleId, String)                              vos_printf(" %s, %d, %s \r\n ", __FILE__, __LINE__,String)
#define IMS_NIC_INIT_LOG_PRINT1(ModuleId, String,Para1)                       vos_printf(" %s, %d, %s, %d \r\n ",  __FILE__, __LINE__, String, Para1)
#define IMS_NIC_INIT_LOG_PRINT2(ModuleId, String,Para1,Para2)                 vos_printf(" %s, %d, %s, %d, %d \r\n ",  __FILE__, __LINE__, String, Para1, Para2)
#define IMS_NIC_INIT_LOG_PRINT3(ModuleId, String,Para1,Para2,Para3)           vos_printf(" %s, %d, %s, %d, %d, %d \r\n ",  __FILE__, __LINE__, String, Para1, Para2, Para3)
#define IMS_NIC_INIT_LOG_PRINT4(ModuleId, String,Para1,Para2,Para3,Para4)     vos_printf(" %s, %d, %s, %d, %d, %d, %d \r\n ",  __FILE__, __LINE__, String, Para1, Para2, Para3, Para4)


#define IMS_NIC_MNTN_TRACE(msgId, pData, ulLen)   \
        IMS_NIC_MntnTrace(msgId, (VOS_UINT8 *)pData, ulLen, 0, 0)

#define IMS_NIC_MNTN_TRACE1(msgId, pData, ulLen, ulPara1)   \
        IMS_NIC_MntnTrace(msgId, (VOS_UINT8 *)pData, ulLen, ulPara1, 0)

#define IMS_NIC_MNTN_TRACE2(msgId, pData, ulLen, ulPara1, ulPara2)   \
        IMS_NIC_MntnTrace(msgId, (VOS_UINT8 *)pData, ulLen, ulPara1, ulPara2)

#define IMS_NIC_MNTN_TRACE_NO_DATA(msgId, ulPara1, ulPara2)   \
        IMS_NIC_MntnTrace(msgId, VOS_NULL_PTR, 0, ulPara1, ulPara2)

/* ----------------VxWorks ϵͳ������װ--------------------------- */
#if (VOS_OS_VER == VOS_WIN32)
#define IMS_NIC_MALLOC(size)                    VOS_MemAlloc(UEPS_PID_IMSNIC, STATIC_MEM_PT, size)
#define IMS_NIC_FREE(pAddr)                     VOS_MemFree(UEPS_PID_IMSNIC, pAddr)
#elif (VOS_OS_VER == VOS_RTOSCK)
/* TODO: */
#define IMS_NIC_MALLOC(size)                    malloc(size)
#define IMS_NIC_FREE(pAddr)                     free(pAddr)

#else
#define IMS_NIC_MALLOC(size)                    malloc(size)
#define IMS_NIC_FREE(pAddr)                     free(pAddr)

#endif

#define IMS_NIC_TCPIP_ADD_DNS_OP                (0)                          /* ���ָ��DNS���������� */
#define IMS_NIC_TCPIP_DEL_DNS_OP                (1)                          /* ɾ��ָ��DNS���������� */
#define IMS_NIC_TCPIP_DEL_ALL_DNS_OP            (2)                          /* ɾ������DNS���������� */
#define IMS_NIC_TCPIP_DNS_CONFIG_IPV4_FLAG      (0)                          /* IPV4��ַ����DNS��� */
#define IMS_NIC_TCPIP_DNS_CONFIG_IPV6_FLAG      (1)                          /* IPV6��ַ����DNS��� */
#define IMS_NIC_TCPIP_DEFAULT_SUBNET_MASK       (0xffffffff)                 /* Ĭ�ϵ������ַ��255.255.255.255 */
#define IMS_NIC_TCPIP_DEFAULT_ROUTE_PRIORITY    (1)                          /* ·�����ʱ�����ȼ����Ϸ���Χ��1~255 */
#define IMS_NIC_TCPIP_GLOBAL_ADDR_FLAG          (0)                          /* ȫ�ֵ�ַ��־ */
#define IMS_NIC_TCPIP_MAX_IMS_NIC_DATA_LEN      (2048)                       /* ���洢���ݳ��� */

#define IMS_NIC_TCPIP_HEADER_RESERVE_LEN        (64)                         /* ���б�������VISPЭ��ջ����MBUFʱԤ���ı���ͷ���� */
#define IMS_NIC_TCPIP_INPUT_LEN                 (200)

#define IMS_NIC_IPV6_ADDR_ELEM_0                (0)                          /* IPV6��ַUINT32��ʽ��0��Ԫ�� */
#define IMS_NIC_IPV6_ADDR_ELEM_1                (1)                          /* IPV6��ַUINT32��ʽ��1��Ԫ�� */
#define IMS_NIC_IPV6_ADDR_ELEM_2                (2)                          /* IPV6��ַUINT32��ʽ��2��Ԫ�� */
#define IMS_NIC_IPV6_ADDR_ELEM_3                (3)                          /* IPV6��ַUINT32��ʽ��3��Ԫ�� */

#define IMS_NIC_TCPIP_INPUT_LOG(str, fn, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s Return:%u \n", #fn, ulRet)

#define IMS_NIC_TCPIP_INPUT_LOG1(str, fn, ulPara1, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%u Return:%u \n", #fn, ulPara1, ulRet)

#define IMS_NIC_TCPIP_INPUT_LOG2(str, fn, ulPara1, ulPara2, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%u para2:%u Return:%u \n", #fn, ulPara1, ulPara2, ulRet)

#define IMS_NIC_TCPIP_INPUT_STR_LOG2(str, fn, ulPara1, szStringPara2, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%u para2:%s Return:%u \n", #fn, ulPara1, szStringPara2, ulRet)

#define IMS_NIC_TCPIP_INPUT_STR2_LOG2(str, fn, szStringPara1, szStringPara2, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%s para2:%s Return:%u \n", #fn, szStringPara1, szStringPara2, ulRet)

#define IMS_NIC_TCPIP_INPUT_LOG3(str, fn, ulPara1, ulPara2, ulPara3, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%u para2:%u para3:%u Return:%u \n", #fn, ulPara1, ulPara2, ulPara3, ulRet)

#define IMS_NIC_TCPIP_INPUT_STR_LOG3(str, fn, ulPara1, ulPara2, szStringPara3, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%u para2:%u para3:%s Return:%u \n", #fn, ulPara1, ulPara2, szStringPara3, ulRet)

#define IMS_NIC_TCPIP_INPUT_LOG4(str, fn, ulPara1, ulPara2, ulPara3, ulPara4, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%u para2:%u para3:%u para4:%u Return:%u \n", #fn, ulPara1, ulPara2, ulPara3, ulPara4, ulRet)

#define IMS_NIC_TCPIP_INPUT_STR_LOG4(str, fn, szStringPara1, szStringPara2, ulPara3, ulPara4, ulRet) \
        VOS_sprintf((VOS_CHAR *)str, "%s para1:%s para2:%s para3:%u para4:%u Return:%u \n", #fn, szStringPara1, szStringPara2, ulPara3, ulPara4, ulRet)

/* ת����LogMsg�������������Բ�����ʹ�� */
#define IMS_NIC_ERROR_LOG_MSG(ModuleId, fmt)                                  LogPrint(fmt)
#define IMS_NIC_ERROR_LOG_MSG1(ModuleId, fmt,Para1)                           LogPrint1((fmt), (Para1))
#define IMS_NIC_ERROR_LOG_MSG2(ModuleId, fmt,Para1,Para2)                     LogPrint2((fmt), (Para1), (Para2))
#define IMS_NIC_ERROR_LOG_MSG3(ModuleId, fmt,Para1,Para2,Para3)               LogPrint3((fmt), (Para1), (Para2), (Para3))
#define IMS_NIC_ERROR_LOG_MSG4(ModuleId, fmt,Para1,Para2,Para3,Para4)         LogPrint4((fmt), (Para1), (Para2), (Para3), (Para4))

#define IMS_NIC_IP6_ADDR_XOR_ADDRESSES(m_pstIP6Addr1, m_pstIP6Addr2, m_stIP6AddrRes)\
{\
    m_stIP6AddrRes.s6_addr32[0] = m_pstIP6Addr1->s6_addr32[0]\
                                                ^ m_pstIP6Addr2->s6_addr32[0];\
    m_stIP6AddrRes.s6_addr32[1] = m_pstIP6Addr1->s6_addr32[1]\
                                                ^ m_pstIP6Addr2->s6_addr32[1];\
    m_stIP6AddrRes.s6_addr32[2] = m_pstIP6Addr1->s6_addr32[2]\
                                                ^ m_pstIP6Addr2->s6_addr32[2];\
    m_stIP6AddrRes.s6_addr32[3] = m_pstIP6Addr1->s6_addr32[3]\
                                               ^ m_pstIP6Addr2->s6_addr32[3];\
}

#define IMS_NIC_IN6_IS_MULTICAST(a)   ((a)->s6_addr[0] == 0xff)

#define IMS_NIC_IN6_IS_LINKLOCAL(a)   \
        (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))

#define IMS_NIC_IN6_IS_UNSPECIFIED(a)   \
        (((a)->s6_addr32[0] == 0) && ((a)->s6_addr32[1] == 0) && \
          ((a)->s6_addr32[2] == 0) && ((a)->s6_addr32[3] == 0))

#define IMS_NIC_MAP_MAC_INTERFACEID(enaddr , interfaceid) \
{ \
   (interfaceid)[0] = (enaddr)[0] | (VOS_UINT8)0x02; \
   (interfaceid)[1] = (enaddr)[1];  \
   (interfaceid)[2] = (enaddr)[2];  \
   (interfaceid)[3] = (VOS_UINT8)  0xff; \
   (interfaceid)[4] = (VOS_UINT8)  0xfe; \
   (interfaceid)[5] = (enaddr)[3]; \
   (interfaceid)[6] = (enaddr)[4]; \
   (interfaceid)[7] = (enaddr)[5]; \
}

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum IMS_NIC_MODEM_ID_ENUM
{
    IMS_NIC_MODEM_ID_0 = 0,

    IMS_NIC_MODEM_ID_BUTT       /* ���ǵ�Ŀǰ��������ҪIMS����������ʱ����BUTTֵΪ1*/
};

typedef VOS_UINT16 IMS_NIC_MODEM_ID_ENUM_UINT16;

/* IMS��������ͳ��ö�� */
enum IMS_NIC_STATS_INFO_ENUM
{
    IMS_NIC_STATS_DL_RCV_IPV4_PKT = 0,                                  /* IMS���������յ�����IPV4���ݵĸ��� */
    IMS_NIC_STATS_DL_RCV_IPV6_PKT,                                      /* IMS���������յ�����IPV6���ݵĸ��� */
    IMS_NIC_STATS_DL_SEND_PKT,                                          /* IMS�������������������ݵĸ��� */
    IMS_NIC_STATS_DL_RCV_BYTES,                                         /* �����յ����ݰ�byte�� */
    IMS_NIC_STATS_DL_RCV_ERR_PKT,                                       /* �յ��������ݰ��ĸ���(��ipv4��ipv6��) */
    IMS_NIC_STATS_DL_INPUT_NULL_PTR,                                    /* ��������Ϊ�յĴ��� */
    IMS_NIC_STATS_DL_RCV_DATA_LEN_ERR,                                  /* IMS���������յ��������ݳ��ȴ���ĸ��� */

    IMS_NIC_STATS_UL_RCV_IPV4_PKT,                                      /* IMS���������յ�����IPV4���ݵĸ��� */
    IMS_NIC_STATS_UL_RCV_IPV6_PKT,                                      /* IMS���������յ�����IPV6���ݵĸ��� */
    IMS_NIC_STATS_UL_SEND_PKT,                                          /* IMS�����������з��͸�CDS���ݵĸ��� */
    IMS_NIC_STATS_UL_SEND_BYTES,                                        /* ���з��͵����ݰ�byte�� */
    IMS_NIC_STATS_UL_RCV_ERR_PKT,                                       /* �յ��������ݰ��ĸ���(��ipv4��ipv6��) */
    IMS_NIC_STATS_UL_RCV_ARP_PKT,                                       /* �յ�ARP���ĸ��� */
    IMS_NIC_STATS_UL_INPUT_NULL_PTR,                                    /* ��������Ϊ�յĴ��� */
    IMS_NIC_STATS_UL_RCV_DATA_LEN_ERR,                                  /* IMS���������յ��������ݳ��ȴ���ĸ��� */
    IMS_NIC_STATS_UL_CB_FUN_NOT_REG,                                    /* IMS���������������ݷ��ͺ���û��ע����� */
    IMS_NIC_STATS_UL_CALL_CB_FUN_FAIL,                                  /* ����CDSע��Ļص�����ʧ�ܴ��� */
    IMS_NIC_STATS_UL_PKT_MEM_SEG,                                       /* ���ݰ��ڴ�ֶ� */

    IMS_NIC_STATS_CFG_DNS_SERVER_FULL,
    IMS_NIC_STATS_CFG_INPUT_NULL_PTR,                                   /* ����ָ��Ϊ�� */
    IMS_NIC_STATS_CFG_ADD_MODEM_ID_ERR,                                 /* ����ʱ�����modem id������ */
    IMS_NIC_STATS_CFG_DEL_MODEM_ID_ERR,                                 /* ɾ�����ô����ModemId���� */
    IMS_NIC_STATS_CFG_ADD_RAB_ID_ERR,                                   /* �������������RABID���� */
    IMS_NIC_STATS_CFG_DEL_RAB_ID_ERR,                                   /* ɾ�������RABID���� */
    IMS_NIC_STATS_GET_CLUSTER_FAIL,                                     /* ��ȡClusterʧ�ܴ��� */
    IMS_NIC_STATS_GET_CLBLK_FAIL,                                       /* ��ȡclBlkʧ�� */
    IMS_NIC_STATS_GET_MBLK_FAIL,
    IMS_NIC_STATS_MBLK_COPY_ERR,                                        /* ����Mblk�ڴ�ʧ�� */
    IMS_NIC_STATS_NOT_INITED_ERR,                                       /* ��������û�г�ʼ�� */
    IMS_NIC_STATS_SYS_CALL_FAIL,                                        /* ϵͳ����ʧ�� */
    IMS_NIC_STATS_FIND_DEV_FAIL,                                        /* �����豸ʧ�� */
    IMS_NIC_STATS_NO_CFGED_PDN,
    IMS_NIC_STATS_CFG_ADD_NO_PDN,
    IMS_NIC_STATS_CFG_DEL_NO_PDN,
    IMS_NIC_STATS_MODEM_ID_ERR_OTHER,
    IMS_NIC_STATS_MODEM_ID_ERR_IN_REG_CB,
    IMS_NIC_STATS_MODE_ID_ERR_IN_DL_PROC,
    IMS_NIC_STATS_MODE_ID_ERR_IN_UL_PROC,
    IMS_NIC_STATS_MTU_INVALID,
    IMS_NIC_STATS_INVALID_IPV6_PREFIX_LEN,
    IMS_NIC_STATS_MTU_CONFIG_FAIL,                                      /* ����MTUʧ�� */
    IMS_NIC_STATS_PORT_CONFIG_INVALID,                                  /* ���ö˿ڲ����Ƿ� */
    IMS_NIC_STATS_NETIF_RESET_FAIL,                                     /* �����ͷ�ʧ�� */
    IMS_NIC_STATS_DEL_IPV4_ADDR_FAIL,                                   /* ɾ��IPV4��ַʧ�� */
    IMS_NIC_STATS_DEL_IPV6_ADDR_FAIL,                                   /* ɾ��IPV6��ַʧ�� */
    IMS_NIC_STATS_GET_IF_NAME_BY_INDEX_FAIL,                            /* ͨ���ӿ�������ȡ�ӿ���ʧ�� */
    IMS_NIC_STATS_ADD_IPV4_ADDR_FAIL,                                   /* ����IPV4��ַʧ�� */
    IMS_NIC_STATS_ADD_IPV6_ADDR_FAIL,                                   /* ����IPV6��ַʧ�� */
    IMS_NIC_STATS_CONFIG_IPV4_ROUTE_FAIL,                               /* ����IPV4·��ʧ�� */
    IMS_NIC_STATS_CONFIG_IPV6_ROUTE_FAIL,                               /* ����IPV6·��ʧ�� */
    IMS_NIC_STATS_COPY_DATA_FROM_MBUF_FAIL,                             /* ��MBUF��������ʧ�� */
    IMS_NIC_STATS_RESUME_IF_FAIL,                                       /* �ӿڻָ�ʧ�� */
    IMS_NIC_STATS_SET_STATIC_ARP_FAIL,                                  /* ���þ�̬ARPʧ�� */
    IMS_NIC_STATS_SET_STATIC_ND_FAIL,                                   /* ���þ�̬ND����ʧ�� */
    IMS_NIC_STATS_ENABLE_HOST_FAIL,                                     /* ʹ������ģʽʧ�� */
    IMS_NIC_STATS_ISLUP_SUCC,                                           /* ����up�ɹ� */
    IMS_NIC_STATS_ISLUP_FAIL,                                           /* ����upʧ�� */
    IMS_NIC_STATS_MATCH_IPV6_ADDR_SUCC,                                 /* ��ȡIPV6��ַ�ɹ� */
    IMS_NIC_STATS_MATCH_IPV6_ADDR_FAIL,                                 /* ��ȡIPV6��ַʧ�� */
    IMS_NIC_STATS_LOCAL_IPV6_ADDR_SUCC,                                 /* ��ȡLocal��ַ�ɹ� */
    IMS_NIC_STATS_LOCAL_IPV6_ADDR_FAIL,                                 /* ��ȡLocal��ַʧ�� */
    IMS_NIC_STATS_HAVE_IPV6_ADDR_SUCC,                                  /* �Ƿ��е�ַ�ɹ� */
    IMS_NIC_STATS_HAVE_IPV6_ADDR_FAIL,                                  /* �Ƿ��е�ַʧ�� */

    IMS_NIC_STATS_BUTT,
};
typedef VOS_UINT32 IMS_NIC_STATS_INFO_ENUM_UINT32;

enum IMS_NIC_DNS_STATE_ENUM
{
    IMS_NIC_DNS_CFGED                           = 0,
    IMS_NIC_DNS_NOT_CFGED,
    IMS_NIC_DNS_STATE_BUTT
};
typedef VOS_UINT32 IMS_NIC_DNS_STATE_ENUM_UINT32;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : IMS_NIC_SINGLE_PDN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ĳ��������IMS��������PDN��Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv4PdnInfo            : 1;                        /* ���Ϊ1�����aucIpV4Addr��Ч */
    VOS_UINT32                          bitOpIpv6PdnInfo            : 1;                        /* ���Ϊ1�����aucIpV6Addr��Ч */
    VOS_UINT32                          bitOpIpv4DnsPrimCfged       : 1;                     /* IMS NIC�ڲ���д����¼aucDnsPrimAddr�Ƿ����óɹ� */
    VOS_UINT32                          bitOpIpv4DnsSecCfged        : 1;                     /* IMS NIC�ڲ���д����¼aucDnsSecAddr�Ƿ����óɹ� */
    VOS_UINT32                          bitOpIpv6DnsPrimCfged       : 1;                     /* IMS NIC�ڲ���д����¼aucDnsPrimAddr�Ƿ����óɹ� */
    VOS_UINT32                          bitOpIpv6DnsSecCfged        : 1;                     /* IMS NIC�ڲ���д����¼aucDnsSecAddr�Ƿ����óɹ� */

    VOS_UINT32                          bitOpSpare                  : 26;

    VOS_UINT8                           aucDnsFlag[IMS_NIC_DNS_NUM_ADAPTER];         /* ���Ϊ1�����������DNS������,�ֱ��Ӧ�����ڶ��������͵���DNS������ */

    IMS_NIC_IPV4_PDN_INFO_STRU          stIpv4PdnInfo;
    IMS_NIC_IPV6_PDN_INFO_STRU          stIpv6PdnInfo;
}IMS_NIC_SINGLE_PDN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMS_NIC_SINGLE_DNS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����DNS������Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT8                            cDnsRef;                                   /* DNS�����������ü��� */
    VOS_UINT8                           ucIpAddrLen;                                /* �洢��DNS������IP��ַ���� */
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucDnsAddr[IMS_NIC_IP_ADDR_MAX_LENGTH];     /* DNS��������ַ */
}IMS_NIC_SINGLE_DNS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMS_NIC_DNS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DNS������Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDnsServerCnt;                                     /* ��ǰ����DNS�������ĸ��� */
    VOS_UINT8                           aucReserved[3];
    IMS_NIC_SINGLE_DNS_INFO_STRU        astImsNicDnsInfo[IMS_NIC_MAX_DNS_SERVER_NUM];       /* DNS������Ϣ���ֱ��Ӧ������һ���ڶ�������DNS������ */
}IMS_NIC_DNS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMS_NIC_PDN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���г�����IMS��������PDN��Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT                             iPdnCfgCnt;
    IMS_NIC_DNS_INFO_STRU               stImsNicDnsInfo;                                /* ��ǰDNS������������Ϣ */
    IMS_NIC_SINGLE_PDN_INFO_STRU        astImsNicPdnInfo[IMS_NIC_RAB_ID_MAX_NUM];       /* ��Rab��PDN������Ϣ */
}IMS_NIC_PDN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMS_NIC_DEV_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ڿ����豸�������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_INT                   unit;                                             /* �豸��unit�� */                                      /* ���ڻ�ȡ���绺�� */
    VOS_UINT8                 aucSendBuf[IMS_NIC_UL_SEND_BUFF_SIZE];            /* ���з��ͻ���,1520�ֽ�*/
} IMS_NIC_DEV_STRU;

/*****************************************************************************
 �ṹ��    : IMS_NIC_ETH_HEADER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��̫��ͷ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                 aucEtherDhost[IMS_NIC_ETHER_ADDR_LEN];            /* Ŀ����̫����ַ */
    VOS_UINT8                 aucEtherShost[IMS_NIC_ETHER_ADDR_LEN];            /* Դ��̫����ַ */
    VOS_UINT16                usEtherType;                                      /* ������ */
}IMS_NIC_ETH_HEADER_STRU;

/*****************************************************************************
 �ṹ��    : IMS_NIC_ELEMENT_TAB_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMS����������Ϣ
*****************************************************************************/
typedef struct
{
    IMS_NIC_ETH_HEADER_STRU             stIpv4Ethhead;                          /* IPV4��̫��ͷ */
    IMS_NIC_ETH_HEADER_STRU             stIpv6Ethhead;                          /* IPV6��̫��ͷ */
}IMS_NIC_ELEMENT_TAB_STRU;

/*****************************************************************************
 �ṹ��    : IMS_NIC_STATS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMS��������ͳ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32              aulStats[IMS_NIC_STATS_BUTT];
}IMS_NIC_STATS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMS_NIC_ENTITY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMS��������ʵ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulImsNicInitFlag;                       /* IMS����������ʼ����� */
    VOS_UINT32                          ulIfIndex;                              /* �ӿ����� */
    IMS_NIC_SEND_UL_DATA_FUNC           pUlDataSendFunc;                        /* IMS���������������ݷ��ͺ��� */
    IMS_NIC_PDN_INFO_STRU               stImsNicPdnInfo;                        /* IMS��������PDN������Ϣ */
    IMS_NIC_STATS_INFO_STRU             stImsNicStatsInfo;                      /* IMS��������ͳ����Ϣ */
    VOS_UINT8                           aucIpV6LinkLocalAddr[IMS_NIC_IPV6_ADDR_LENGTH]; /* IPv6��·���ص�ַ */
}IMS_NIC_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : IMS_NIC_MANAGE_TBL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMS������������ṹ
*****************************************************************************/
typedef struct
{
    VOS_CHAR                            ucImsNicName[IMS_NIC_IFNAMSIZ];                 /* �������� */
    IMS_NIC_ELEMENT_TAB_STRU            astImsNicElementTbl[IMS_NIC_MODEM_ID_BUTT];     /* IMS��������������Ϣ�� */
}IMS_NIC_MANAGE_TBL_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16 usMsgId;
    VOS_UINT8  aucRsv[2];
    VOS_UINT32 ulPara1;
    VOS_UINT32 ulPara2;
    VOS_UINT8  aucData[4];
}IMS_NIC_MNTN_TRACE_MSG_STRU;

typedef struct
{
    VOS_UINT32                          ulTick;
    VOS_UINT32                          enLevel;
    PS_FILE_ID_DEFINE_ENUM_UINT32       enFile;
    VOS_UINT32                          ulLine;
    VOS_INT32                           alPara[IMS_NIC_LOG_PARAM_MAX_NUM];
}IMS_NIC_LOG_RECORD_STRU;

typedef struct
{
    VOS_UINT32                          ulCnt;                  /* ʵ�ʻ���Ĵ�ӡ��¼��Ŀ */
    IMS_NIC_LOG_RECORD_STRU             astData[IMS_NIC_LOG_RECORD_MAX_NUM];
}IMS_NIC_LOG_ENT_STRU;

typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    VOS_UINT16                          usMsgType;      /* _H2ASN_Skip */
    VOS_UINT16                          usTransId;
    IMS_NIC_LOG_ENT_STRU                stLogMsgCont;   /* LOG_MSG���� */
}IMS_NIC_TRACE_LOG_MSG_STRU;


/*****************************************************************************
 �ṹ��    : IMS_NIC_CTX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMS��������������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMtu;                                  /* MTUֵ,Ĭ��1280���ⲿģ�����ͨ���ӿ��޸� */
    VOS_SEM                             ulInitLogMutexSem;
    VOS_SEM                             ulSaveLogMutexSem;
    IMS_NIC_SEND_UL_DATA_FUNC           pTmpSendFunc[IMS_NIC_MODEM_ID_BUTT];    /* ��¼CDSע�����лص����� */
    IMS_NIC_LOG_ENT_STRU                stLogEnt;
}IMS_NIC_CTX_STRU;

typedef  struct  tagImsNicIp6InterfaceId
{
    union
    {
        VOS_UINT8       u6_InterfaceId8[8];
        VOS_UINT16      u6_InterfaceId16[4];
        VOS_UINT32      u6_InterfaceId32[2];
    } u6_InterfaceId;
}IMS_NIC_INTERFACEID_S;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern IMS_NIC_ENTITY_STRU                      g_astImsNicEntity[IMS_NIC_MODEM_ID_BUTT];        /* IMS��������ʵ����Ϣ */
extern const IMS_NIC_MANAGE_TBL_STRU            g_stImsNicManageTbl;
extern IMS_NIC_CTX_STRU                         g_stImsNicCtx;
extern IMS_NIC_DEV_STRU                         g_astImsNicDev[IMS_NIC_MODEM_ID_BUTT];

/*****************************************************************************
  10 ��������
*****************************************************************************/
#if ((VOS_OS_VER == VOS_RTOSCK) || ((VOS_OS_VER == VOS_WIN32) && (VOS_PC_TEST == VOS_RTOSCK)))

#else
extern IP_PUBLIC int    ipcom_run_cmd(char *cmd_str);

#endif

VOS_UINT32 IMS_NIC_SetSocketPort
(
    VOS_UINT16                          usMinPort,
    VOS_UINT16                          usMaxPort,
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID    IMS_NIC_SetDefaultRoute(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID IMS_NIC_ResetAll(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID IMS_NIC_DnsConfigtoIpStack
(
    VOS_UINT8                           ucIpAddrLen,
    VOS_UINT8                           ucDnsIndx,
    VOS_UINT8                          *pucIpAddr
);

VOS_VOID IMS_NIC_DnsDeltoIpStack
(
    VOS_UINT32                          ulIndx,
    VOS_UINT8                           ucRabId,
    IMS_NIC_DNS_INFO_STRU              *pstDnsInfo
);

VOS_VOID   IMS_NIC_PdnInfoDelIpv4(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID   IMS_NIC_PdnInfoDelIpv6(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID   IMS_NIC_ConfigIpv4Addr
(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                          *pucIpAddr
);

VOS_VOID   IMS_NIC_ConfigIpv6Addr
(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT32                          ulBitPrefixLen
);

VOS_UINT32 IMS_NIC_Delete (MODEM_ID_ENUM_UINT16 enModemId);

VOS_UINT32 IMS_NIC_Init (MODEM_ID_ENUM_UINT16 enModemId);

#endif  /*FEATURE_ON == FEATURE_IMS*/

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of ImsNicInterface.h */


