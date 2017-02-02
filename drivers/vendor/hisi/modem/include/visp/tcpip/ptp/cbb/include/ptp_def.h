/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_def.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP
*  Date Created: 2008-06-02
*        Author: Yaochengliang
*   Description: PTP���Ժ궨��ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME               DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-06-02    Yaochengliang        Create
*
*******************************************************************************/

#ifndef _PTP_DEF_H_
#define _PTP_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*����PTPģ��MID/SID*/
#define PTP_MID  MID_COMP_PTP

#define SID_PTP_UNICAST_SLAVE_S       1  /*��ŵ���SLAVE�����б�*/
#define SID_PTP_CLOCK_S               2  /*���PTPʱ��ʵ��*/
#define SID_PTP_LOGIC_TIMER_S         3  /*���PTP�߼���ʱ��ʵ��*/
#define SID_PTP_DEFAULT_SOCKET_PACKET 4  /*���Socket���Ļ���*/
#define SID_PTP_MAC_VLAN              5  /*���ڴ��VLAN�����Ϣ*/
#define SID_PTP_UNICAST_SLAVE_TABLE   6  /*���ڴ��slave table �ṹ��*/
#define SID_PTP_PORT_ADDR_VRF         7  /* ���ڴ��PTP_PORT_ADDR_VRF_S�ṹ�� */
#define SID_PTP_VRF_SOCKET            8  /* ���ڴ��PTP_PORT_ADDR_VRF_S�ṹ�� */

/*Mod end */

/* PTP�汾�� */
#define PTP_VERSION                     2

/* Keep alive �������ʱ���� */
#define PTP_LIVE_EXPIRES_NUMBER         3

/* Keep alive ���ĵķ��ͼ�� 64S */
#define PTP_LIVE_INTERVAL               6

/*Added by wangchengyang62830 for VISPV1R8C01, 2009/6/8 */
#define PTP_LIVE_MAX_INTERVAL           10
/* End of Added by wangchengyang62830, 2009/6/8 */

#define PTP_LIVE_MSG_LEN                34

/* �����ı��ĳ��ȹ������txt TLV�� */
#define PTP_TXT_SUPPORT_LEN             256

/* ���嵥��master�б����ù��,ÿ��ֻ����ֵ���������ֵ */
/* Modified by Anish K Kurian & Wangchengyang72338 & 62830, for new profile, 2010/9/24 */
#define PTP_UNICAST_MASTR_CFG_LEN       5
/* End of Added by Anish K Kurian & Wangchengyang72338 & 62830, 2010/9/24 */

/*���嵥��foreign Master�б��ȹ��*/
#define PTP_FOREIGN_MASTR_LEN           2

/*���嵥��slave�б��ȹ��*/
#define PTP_UNICAST_SLAVE_LEN           10240


#define PTP_TRUE  1
#define PTP_FALSE 0


/*TCIP.SafeModify.Delete, Modify by guojianjun178934, 2014/5/21*/

/*����PTP�˿ڵ�ַ�ĸ�����*/
#define PTP_PORT_ADDR_NUM               2

/*����foreignMasterDS,BMC���*/
#define FOREIGN_MASTER_TIME_WINDOW      4

/*����������ȼ��궨��*/
#define PTP_MAX_TASK_PRI                255

/* ���ֻ�Ӧ��Ϣ���� */
#define PTP_HANDSHAKE_RESP_LEN          12

/* ����������Ϣ���� */
#define PTP_HANDSHAKE_REQ_LEN           4

/* PTP header���� */
#define PTP_HEADER_LEN                  34

/* PTP udp/ipv4��ַ���� */
#define PTP_ADDRLEN_UDP_IPV4            4

/* PTP udp/ipv4��ַ���� */
#define PTP_ADDRLEN_UDP_IPV6            16
/*��չTLV*/
#define PTP_TLV_SYNC_LEN                10


/* ptp����Э��tlv ���� */
#define PTP_TLV_HEADER_LEN              44

/*��������*/
#define PTP_ONE_SIANGLING_TLV_PKTLEN    128
/*End of Modified by wangchengyang62830, 2011/4/21 */

/* ��ͨTLV���� */
#define PTP_GENERAL_TLV_LEN             6

/* ��չTLV���� */
#define PTP_EXTEND_TLV_LEN              14

/* announce log interval�����Сֵ�궨�� */
#define PTP_MAX_ANNOUNCE_LOGINTERVAL       4

#define PTP_MIN_ANNOUNCE_LOGINTERVAL      (-3)

/* sync log interval�����Сֵ�궨�� */
#define PTP_MAX_SYNC_LOGINTERVAL       4

#define PTP_MIN_SYNC_LOGINTERVAL      (-7)

/* delay/pdelay Req interval�����Сֵ�궨�� */
#define PTP_MAX_MINDELAY_REQ_LOGINTERVAL       4

#define PTP_MIN_MINDELAY_REQ_LOGINTERVAL      (-7)

/*Mod End*/

/*Added by Anish K Kurian & Wangchengyang72338 & 62830, for new profile, 2010/9/26 */
#define PTP_MAX_NEW_PROFILE_CLASS 110
#define PTP_MIN_NEW_PROFILE_CLASS 80
/* End of Added by Anish K Kurian & Wangchengyang72338 & 62830, 2010/9/26 */

/* announce��С���ճ�ʱ���� */
#define PTP_MIN_RECEIPT_TIMEOUT        2

/* ��ǰ�汾��PTP�˿ڹ̶��ź� */
#define PTP_PORT_NO_ZERO                0

/*Added by xujun-wangchengyang57575-62830 for VISPV1R8C01, 2009/3/19 */
#define VLANTYPE_DOT1Q   0x8100         /* VLAN 802.1q��ʽ*/
#define DOT1Q_TAG_SIZE   4
#define PTP_IEEE8023_ETHTYPE 0x88f7     /*1588 OVER MAC ��̫����*/
#define PTP_EVT_IEEE8023MSG_Q 0x00020000         /*MAC����д�뵽PTP����ʹ�ø���Ϣ*/
#define PTP_IEEE8023MSGT 0x00001000     /*MAC����д�뵽PTP����MSG[0]ʹ�øñ�ʶ*/
#define PTP_ADDRLEN_IEEE8023 6          /* PTP MAC ��ַ���� */
/* End of Added by xujun-wangchengyang57575-62830, 2009/3/19 */

/* ����dscpĬ��ֵ�� */
#define PTP_DEFAULT_DSCP     0x38


/*PTP IPV6 MSG*/
#define PTP_IPV6MSGT 0x00002000     /*IPV6����д�뵽PTP����MSG[0]ʹ�øñ�ʶ*/

#define PTP_EVT_IPV6MSG_Q 0x00040000         /*IPV6����д�뵽PTP����ʹ�ø���Ϣ*/

#define PTP_KEEP_ALIVE_MODE_OLD  0
#define PTP_KEEP_ALIVE_MODE_NEW  1

/*Add by dutianyi 14-7-14 ֧����G8275.1��׼���մ�����*/
#define PTP_G82751_MODE_DISABLE 0
#define PTP_G82751_MODE_ENABLE 1
/*End of adding*/

#define PTP_MIN_DURATION_FIELD 60
#define PTP_MAX_DURATION_FIELD 1000
#define PTP_DEFAULT_DURATION_FIELD 300

/*Ann ���ķ��Ͷ�ʱ������*/
#define PTP_ANN_SEND_TIMER_BASE 125
/*Add End*/

/*��ѡԴ����*/
#define PTP_CLOCK_CLASS_6      6
#define PTP_CLOCK_CLASS_7      7
#define PTP_CLOCK_CLASS_13    13
#define PTP_CLOCK_CLASS_14    14

/*�Ƿ�Ϊ��ѡԴ*/
#define PTP_IS_PRI_CLOCK_SOURCE(clkclass)\
    ((g_pstPtpClock->ucClass0 == clkclass)\
    || (g_pstPtpClock->ucClass1 == clkclass)\
    || (g_pstPtpClock->ucClass2 == clkclass)\
    || (g_pstPtpClock->ucClass3 == clkclass))\
/*Add End*/

#define IP_ADDR_VALID( stAddr )\
    (((PTP_PROTOCAL_UDP_IPV4 == (stAddr).usNetworkProtocol)&&(PTP_ADDRLEN_UDP_IPV4 == (stAddr).usAddressLength))\
   ||((PTP_PROTOCAL_UDP_IPV6 == (stAddr).usNetworkProtocol)&&( PTP_ADDRLEN_UDP_IPV6 == (stAddr).usAddressLength)))
/*Add End*/

#define PTP_IS_MASTER()                                                \
    (PTP_CLOCK_FSM_MODE_MASTER_ONLY == g_pstPtpClock->ucClockFsmMode) 

#define PTP_IS_SLAVE()                                                 \
    (PTP_CLOCK_FSM_MODE_SLAVE_ONLY == g_pstPtpClock->ucClockFsmMode) 

#define PTP_IS_UNICAST()                                    \
    (PTP_CLOCK_UNICAST_MODE == g_pstPtpClock->ucCastMode) 

#define PTP_IS_MULTICAST()                                    \
    (PTP_CLOCK_MULTICAST_MODE == g_pstPtpClock->ucCastMode) 

#define PTP_IS_OVERMAC()                                    \
    (PTP_CLOCK_IEEE8023_MODE == g_pstPtpClock->ucCastMode) 

#define PTP_IS_NEW_MODE()                                   \
    (PTP_KEEP_ALIVE_MODE_NEW == g_ucKeepAliveMode)

#define PTP_IS_OLD_MODE()                                   \
    (PTP_KEEP_ALIVE_MODE_OLD == g_ucKeepAliveMode)


/*Modified by xujun-wangchengyang57575-62830 for VISPV1R8C01, 2009/4/14 */
/*TCIP.SafeModify.Delete, Modify by guojianjun178934, 2014/5/21*/
#define ADDR_VALID( stAddr )\
    (((PTP_PROTOCAL_UDP_IPV4 == (stAddr).usNetworkProtocol)&&(PTP_ADDRLEN_UDP_IPV4 == (stAddr).usAddressLength))\
      || ((PTP_PROTOCAL_IEEE_802 == (stAddr).usNetworkProtocol)&&(PTP_ADDRLEN_IEEE8023 == (stAddr).usAddressLength))\
      || (( PTP_PROTOCAL_UDP_IPV6 == (stAddr).usNetworkProtocol)&&( PTP_ADDRLEN_UDP_IPV6 == (stAddr).usAddressLength)))
/*End of Modified by xujun-wangchengyang57575-62830, 2009/4/14 */

#define PTP_IS_IPV4_ADDR(pstAddr)                              \
    ((PTP_PROTOCAL_UDP_IPV4 == (pstAddr)->usNetworkProtocol)   \
    && (PTP_ADDRLEN_UDP_IPV4 == (pstAddr)->usAddressLength))   

#define PTP_IS_IPV6_ADDR(pstAddr)                              \
    ((PTP_PROTOCAL_UDP_IPV6 == (pstAddr)->usNetworkProtocol)   \
    && (PTP_ADDRLEN_UDP_IPV6 == (pstAddr)->usAddressLength))   

#define PTP_IS_MAC_ADDR(pstAddr)                               \
    ((PTP_PROTOCAL_IEEE_802 == (pstAddr)->usNetworkProtocol)   \
    && (PTP_ADDRLEN_IEEE8023 == (pstAddr)->usAddressLength))   


/*slave״̬�½�����������������һ�����͵�ַ*/
#define PTP6_ADDR_VALID(stPortAddr)\
    (!((PTP_CLOCK_FSM_MODE_SLAVE_ONLY == g_pstPtpClock->ucClockFsmMode)\
    && ((PTP6_CheckIfIPV6Enable() && (PTP_PROTOCAL_UDP_IPV6 != (stPortAddr).usNetworkProtocol))\
        || (!PTP6_CheckIfIPV6Enable() && (PTP_PROTOCAL_UDP_IPV4 != (stPortAddr).usNetworkProtocol)))))

/*����CLOCK ID������жϺ꣬ulResultΪ0����ȣ�����ֵΪ����*/
#define PTP_IS_CLOCK_ID_EQUAL(szDescClockId,szSrcClockId,ulResult) \
{\
    (VOID)VOS_Mem_Cmp((VOID*)szDescClockId, (VOID*)szSrcClockId, PTP_CLOCK_ID_LEN, (LONG*)&ulResult); \
}

/*����PORT_ADDR������жϺ꣬ulResultΪ0����ȣ�����ֵΪ����*/
/* Modified by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/3/30 */
#define PTP_IS_PORT_ADDR_EQUAL(pstDescPortAddr, pstSrcPortAddr, lResult) \
{\
    (VOID)PTP_Addr_Cmp(pstDescPortAddr, pstSrcPortAddr, (LONG*)&lResult);\
}
/*End of Modified by wangchengyang-xujun62830-57575, 2009/3/30 */

/* ����ת��logֵ��������������ĺ� */
#define PTP_CAL_LOG_TO_MILL(cLogValue,ulMillValue)\
{\
    ULONG ulLogValueAbs = 0;\
    (ulMillValue) = 1;     \
    ulLogValueAbs = (cLogValue) >= 0 ? (cLogValue) : -(cLogValue);\
    (ulMillValue) = (ulMillValue) << ulLogValueAbs;\
    (ulMillValue) = (cLogValue) >= 0 ? (1000 * (ulMillValue)):(1000 / (ulMillValue));\
}

#define PTP_GRANT_ACQUIRED(ulMasterIp, bGrantR, ulMsgType)  \
{\
    if (NULL != g_pfPtpGrantAcquired)\
    {\
        (VOID)g_pfPtpGrantAcquired(ulMasterIp, &bGrantR, ulMsgType);\
    }\
    else\
    {\
        bGrantR = BOOL_TRUE;\
    }\
}

/* Modified by weishanfengwKF61331, ��Ʒ��Ȩ�Ƿ�ܾ�����, 2011/11/26   ���ⵥ��:S.PTP.ANNCHOOK.01  */
#define PTP_GRANT_ACQUIRED_BY_ID(pstPortId, bGrantR, ulPtpMsgType, ulAnnInterval, cSlaveFlag)\
{\
    if (NULL != g_pfPtpGrantAcquiredById)\
    {\
        PTP_GRANT_PARA_S stMsgPara;\
        (VOID)TCPIP_Mem_Set((CHAR *)&stMsgPara, 0, sizeof(PTP_GRANT_PARA_S));\
        (VOID)TCPIP_Mem_Copy(&(stMsgPara.stPortId),sizeof(PTP_PORT_ID_S),(pstPortId),sizeof(PTP_PORT_ID_S));\
        stMsgPara.ulMsgType= (ULONG)(ulPtpMsgType);\
        stMsgPara.cAnnInterval = (ulAnnInterval);\
        stMsgPara.cSlaveFlag = (cSlaveFlag);\
        (VOID)g_pfPtpGrantAcquiredById(&stMsgPara, &(bGrantR));\
    }\
/*End of Modified by weishanfengwKF61331, 2011/11/26   ���ⵥ��:S.PTP.ANNCHOOK.01 */\
    else\
    {\
        (bGrantR) = BOOL_TRUE;\
    }\
}

/*��ӡ�����*/
#define PTP_DEBUGINFO_OUTPUT(ulDebugType,szBuffer)\
{\
    if (ulDebugType & g_ulPtpGlobalDbgSwitch)\
    {\
        PTP_DBG_OUTPUT(szBuffer);\
    }\
}

/* ɾ�����б� */
#define PTP_DEL_RUNMASTERTAB(pstUniMaster)\
{\
    PTP_ClearUnicastMasterRunInfo(pstUniMaster);\
}

/* ɾ���ܱ� */
#define PTP_DEL_TOTALMASTERTAB(pstUniMaster)\
{\
    PTP_ClearUnicastMasterCfgInfo(pstUniMaster);\
}

/* ����Delay_Resp/Pdelay_Respʱ����ֵ */
#define PTP_SET_PPI_DELAYRESP_INTERVAL(ucDelayMechanism,cLogMinDelayReqInterval,cLogMinPdelayReqInterval,cLogInterMessagePeriod)\
{\
    if (PTP_DELAY_MACHENISM_E2E == ucDelayMechanism)\
    {\
        cLogMinDelayReqInterval = cLogInterMessagePeriod;\
        cLogMinPdelayReqInterval = 0;\
    }\
    else\
    {\
        cLogMinDelayReqInterval = 0;\
        cLogMinPdelayReqInterval= cLogInterMessagePeriod;\
    }\
}

/* if x not equs NULL return ERR_CODE, make sure x is null */
#define  PTP_CHECK_NUL(X, ERR_CODE)       \
{                                          \
    if (NULL != (X))                       \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

/* if x equs NULL return ERR_CODE, make sure x is not null */
#define  PTP_CHECK_NNU(X, ERR_CODE)       \
{                                          \
    if (NULL == (X))                       \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define  PTP_CHECK_NEQ(X, Y, ERR_CODE)     \
{                                          \
    if ((X) == (Y))                        \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define  PTP_CHECK_EQU(X, Y, ERR_CODE)     \
{                                          \
    if ((X) != (Y))                        \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define PTP_CHECK_TRUE(VALUE, ERR_CODE)    \
{                                          \
    if (!(VALUE))                          \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define PTP_CHECK_FALSE(VALUE, ERR_CODE)   \
{                                          \
    if (VALUE)                             \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define PTP_CHECK_GT(X, Y, ERR_CODE)       \
{                                          \
    if ((X) <= (Y))                        \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define PTP_CHECK_LT(X, Y, ERR_CODE)       \
{                                          \
    if ((X) >= (Y))                        \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define PTP_CHECK_GE(X, Y, ERR_CODE)       \
{                                          \
    if ((X) < (Y))                         \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}

#define PTP_CHECK_LE(X, Y, ERR_CODE)       \
{                                          \
    if ((X) > (Y))                         \
    {                                      \
        return (ERR_CODE);                 \
    }                                      \
}



/*���������*/
#define PTP_DBG_OUTPUT(pszMsg)  do\
                                {\
                                    if (NULL != g_pfDbgOutput)\
                                    {\
                                        g_pfDbgOutput(pszMsg);\
                                    }\
                                }while (FALSE)

#define PTP_WARN_OUTPUT(ulWarnId, pWarnParam)    do\
                                {\
                                    PTP_WarningOut(ulWarnId,pWarnParam);\
                                }while (FALSE)


/* ������תΪ������ */
#define PTP6_ADDRESS_HTON(x) \
{\
    (x)[0] = VOS_HTONL((x)[0]);\
    (x)[1] = VOS_HTONL((x)[1]);\
    (x)[2] = VOS_HTONL((x)[2]);\
    (x)[3] = VOS_HTONL((x)[3]);\
}

/* ������ תΪ������*/
#define PTP6_ADDRESS_NTOH(x) \
{\
    (x)[0] = VOS_NTOHL((x)[0]);\
    (x)[1] = VOS_NTOHL((x)[1]);\
    (x)[2] = VOS_NTOHL((x)[2]);\
    (x)[3] = VOS_NTOHL((x)[3]);\
}

/*IPv6��ַ��ֵ*/
#define IPV6_ADDR_COPY(dst, src)\
{\
    dst[0] = src[0];\
    dst[1] = src[1];\
    dst[2] = src[2];\
    dst[3] = src[3];\
}

#define PTP_REQUEST_UNICAST_TRANSMISSION_TLV_LEN            6
#define PTP_GRANT_UNICAST_TRANSMISSION_TLV_LEN              8
#define PTP_ACK_CANCEL_UNICAST_TRANSMISSION_TLV_LEN         2
#define PTP_CANCEL_UNICAST_TRANSMISSION_TLV_LEN             2
#define PTP_ORGANIZATION_EXTENSION_TLV_LEN                  14

#define PTP_TLVLEN_CHECK(type, len)\
    (((PTP_REQUEST_UNICAST_TRANSMISSION == type) && (PTP_REQUEST_UNICAST_TRANSMISSION_TLV_LEN == len))\
    || ((PTP_GRANT_UNICAST_TRANSMISSION == type) && (PTP_GRANT_UNICAST_TRANSMISSION_TLV_LEN == len))\
    || ((PTP_CANCEL_UNICAST_TRANSMISSION == type) && (PTP_CANCEL_UNICAST_TRANSMISSION_TLV_LEN == len))\
    || ((PTP_ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION == type) && (PTP_ACK_CANCEL_UNICAST_TRANSMISSION_TLV_LEN == len))\
    || ((PTP_ORGANIZATION_EXTENSION == type) && (PTP_ORGANIZATION_EXTENSION_TLV_LEN == len)))
/* End of Added by Anish K Kurian & Wangchengyang72338 & 62830, 2010/10/22 */

#define PTP_IS_MULTI_TLV_WITH_DELAY(ptp_port_num)\
    ((PTP_KEEP_ALIVE_MODE_NEW == g_ucKeepAliveMode)\
    && (PTP_DELAY_MACHENISM_E2E == g_pstPtpClock->stPtpPort[ptp_port_num].ucDelayMechanism))

/* End of Added by Anish K Kurian & Wangchengyang72338 & 62830, 2010/10/25 */

#define PTP_NEWPROFILE_DEFAULT_CLASS      255
#define PTP_NEWPROFILE_DEFAULT_DOMAIN     4
#define PTP_NEWPROFILE_DEFAULT_QUERYMAX   3
/* End of Modified by Anish K Kurian & Wangchengyang72338 & 62830, 2010/10/27 */

#define PTP_YES    1
#define PTP_NO     0
/*End of Added by wangchengyang62830, 2011/1/6 */
/*�����ʱ����ʱʱ��ulOutTime + ulTimeLowʱ��С��0xFFFFFFFF,
 *�ͱ���ulEndTimeHigh���䣬ֱ����ulEndTimeLow�ϼ���ulOutTime����*/

/*�����ʱ����ʱ���� + ulTimeLowʱ�����0xFFFFFFFF,
 *ulEndTimeHigh��Ҫ��1����ulEndTimeLow�ϼ������� */
#define PTP_SET_OUTTIME(interval ,timenowhigh ,timenowlow ,dsthigh ,dstlow)\
{\
    ULONG ultime = 0;\
    ultime = 0xFFFFFFFF - timenowlow;\
    if (ultime >= interval)\
    {\
        dstlow  = timenowlow + interval;\
        dsthigh = timenowhigh;\
    }\
    else \
    {\
        dsthigh = timenowhigh + 1;\
        dstlow  = interval + ultime;\
    }\
}
/* End of Added by wangchengyang62830, 2011/3/8*/

#define PTP_CANCEL_QUERY_DEFAULT    3

#define PTP_TIMER_COUNT_MAX         10240
#define PTP_TIMER_COUNT_MIN         500
/* End of Added by wangchengyang62830, 2011/3/18   */

/* Modified by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/3/30 */
/* ��ַ�Ƚ�ʧ�ܻ��߲���ȵ�ʱ�����ֵ */

#define PTP_ADDRCMP_ERR         (-1)

/*End of Modified by wangchengyang-xujun62830-57575, 2009/3/30 */


#define PTP_DEL_TIMER(ulTimerId)\
{\
    if (ulTimerId)\
    {\
        (VOID)PTP_DeleteLogicTimer(ulTimerId);\
        ulTimerId = 0;\
    }\
}

#define  PTP_NP_PPI_ADD_FLAG  0x01
#define  PTP_NP_PPI_SET_FLAG  0x02

#define PTP_IPV6_END_EXTEND_SIZE   2 /*ptp ipv6����ĩβ��չ2�ֽ�*/

#define  PTP_MASTER_CANCEL_OR_ACK_OR_REFUSE(flag)   \
    ((PTP_STATE_UNICAST_NEGO_CANCEL == flag)         \
    || (PTP_STATE_UNICAST_NEGO_ACK == flag)         \
    || (PTP_STATE_UNICAST_NEGO_REFUSE == flag))

#define  PTP_MASTER_ACK_OR_REFUSE(flag)   \
    ((PTP_STATE_UNICAST_NEGO_ACK == flag)         \
    || (PTP_STATE_UNICAST_NEGO_REFUSE == flag))

/*Added by guo00178934, two-wayģʽ���Ƿ�����sync��delay�����ͬ, 2012/1/5   ���ⵥ��:20120105_2 */
#define PTP_TWOWAY_SEQID_CHECK_DIFF 1 /*two way Ӧ�� sync ��delay���в�����ͬ Ĭ��ֵ���������Ĭ�Ϻ�TP5000 �ԽӲ��ɹ�*/ 
#define PTP_TWOWAY_SEQID_CHECK_SAME 2 /*two way Ӧ�� sync ��delay���б�����ͬ*/ 
#define PTP_TWOWAY_SEQID_CHECK_ALL  (PTP_TWOWAY_SEQID_CHECK_DIFF|PTP_TWOWAY_SEQID_CHECK_SAME) /*��������������� */
/* End of Added by guo00178934, 2012/1/5   ���ⵥ��:20120105_2 */

/*Added by guo00178934, Duration��Э��ʱ���û�����, 2012/1/7   ���ⵥ��:20120107_1 */
#define PTP_DURATION_TIMEOUT_PERCENT_MIN  50
#define PTP_DURATION_TIMEOUT_PERCENT_MAX  99

/*����Duration��Э�̵�ʱ��*/
#define PTP_DURATION_TIMEOUT_PERIOD(ulDuration, ulPrecent) \
  ((ulDuration) * 1000 * (ulPrecent) / 100)
/* End of Added by guo00178934, 2012/1/7   ���ⵥ��:20120107_1 */

/*Added by guo00178934, ��������Master�澯��Ϣ, 2012/1/13   ���ⵥ��:20120112_1 */
#define PTP_CPY_WARNING_INFO(pstWarnParam, pstUniMaster, pstPtpPort)  \
{\
    if(((pstUniMaster) != NULL) && \
      ((pstPtpPort) != NULL)) \
    {\
        if (PTP_FALSE == PTP6_CheckIfIPV6Enable())\
        {\
            VOS_CopyVar((pstWarnParam)->stLocalPortAddr, (pstPtpPort)->stLocalPortAddr[0]); \
        }\
        else\
        {\
            VOS_CopyVar((pstWarnParam)->stLocalPortAddr, (pstPtpPort)->stLocalPortAddr6[0]);  \
        }\
        VOS_CopyVar((pstWarnParam)->stDstPortAddr, (pstUniMaster)->stPortAddr); \
        (pstWarnParam)->ulVrfIndex = (pstUniMaster)->ulVrfIndex;  \
        (pstWarnParam)->usPtpPortNum = (pstPtpPort)->stPortId.usPortNumber; \
    }\
}
/* End of Added by guo00178934, 2012/1/13   ���ⵥ��:20120112_1 */

/*Added by limin00188004, 1588 PTP֧�ֶ�TLV�����Э����·����ɾ��, 2012/9/21   ���ⵥ��:S.PTP.02.01 */
#define PTP_MASTER_DURATION_SWITCH() (PTP_YES == g_ulPtpMasterDurationSwitch)
/* End of Added by limin00188004, 2012/9/21   ���ⵥ��:S.PTP.02.01 */

/* Added by dutianyi00217007, 2014-1-18, expanding PTP port address */
#define PTP_UNI_SLAVE_TBL_HASH_SIZE 64
#define PTP_UNI_SLAVE_TBL_HASH(pstPortAddr) \
    ((UINT8)((pstPortAddr->unAddr.ulIpv4 >> 24) \
                      ^ (pstPortAddr->unAddr.ulIpv4 >> 16) \
                      ^ (pstPortAddr->unAddr.ulIpv4 >> 8) \
                      ^ (pstPortAddr->unAddr.ulIpv4)) % PTP_UNI_SLAVE_TBL_HASH_SIZE)
/* End of adding by dutianyi00217007, 2014-1-18 */

#ifdef __cplusplus
}
#endif


#endif

