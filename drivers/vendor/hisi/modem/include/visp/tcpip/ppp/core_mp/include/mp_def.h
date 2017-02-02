/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                                mp_def.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2000-03-27
 *        Author: HouZhipeng
 *   Description: MPģ��ĺ궨������
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000-03-27      HouZhipeng      Create
 *  2005-09-15      YaoChengliang   Modified for VISP
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *  2006-05-12      languanghua     ֧��ARM CPU ���ֽڶ���
 *************************************************************************/

#ifndef _MP_DEF_H_
#define _MP_DEF_H_

#ifdef  __cplusplus
extern "C"{
#endif


/* ϵͳ֧�ֵ�MPĬ�ϰ���16, ��С����1��������128 */
#define MP_DEFAULT_MAX_BIND         16
#define MP_SUPPORT_MIN_BIND         1
#define MP_SUPPORT_MAX_BIND         128


/* MBUF͸������Ϣ���� */
#define MP_INPUT_PACKET             0
#define MP_TR_MP_PACKET             1
#define MP_TR_IP_PACKET             2


/* ��Ϣ���Ͷ���---��С��Ƭ����������Ϣ; ���ͼ�ʱ��Ч��Ϣ����ͨ�� */
#define MP_MSG_FRAGMENT_LEN         1

/* ���ֶ��� */
#define MP_MAX_FRAGMENT_NUM         16
/* MP��С��Ƭ���ȵ�ȱʡֵ500����Сֵ128�����ֵ1500 */
#define MP_MIN_FRAGMENT_LEN         500 
#define MP_MIN_FRAGMENT_LEN_MIN     128
#define MP_MIN_FRAGMENT_LEN_MAX     1500

/* ÿ����ͨ����Ӧ�Ķ����黺�������� */
#define MP_FRAGMENTNUM_PER_CHANNEL  16
/* �������黺�������� */
#define MP_MAX_FRAGMENT_BUF_LEN     512


/* LFIʹ��/ȥʹ�ܺ궨�� */
#define MP_LFI_ENABLE                   1
#define MP_LFI_DISABLE                  0

/* LFI��Ƭʱ��:ȱʡֵ10���룬��Сֵ1���룬���ֵ1000���� */
#define MP_LFI_DEFAULT_FRAGMENT_DELAY   10
#define MP_LFI_MIN_FRAGMENT_DELAY       1
#define MP_LFI_MAX_FRAGMENT_DELAY       1000

/* LFI������ЧҪ�����·����С����ֵ: 12000Kbps = 12Mbps */
#define MP_LFI_BANDWIDTH_THRESHOLD      12000

/* LFI����Ƭ���ȵ���Сֵ80�����ֵ1500 */
#define MP_LFI_MIN_FRAGMENT_LENGTH      80
#define MP_LFI_MAX_FRAGMENT_LENGTH      1500


/* MP���鴰��ʹ��/ȥʹ�ܺ궨�� */
#define MP_REORDER_WINDOW_ENABLE        1
#define MP_REORDER_WINDOW_DISABLE       0

/* �ն�������ʹ��/ȥʹ�ܺ궨�� */
#define MP_DISCRIMINATOR_ENABLE         1
#define MP_DISCRIMINATOR_DISABLE        0
/* �ն���������󳤶�ֵ */
#define MP_DISCRIMINATOR_MAX_LENGTH     20


/* MP����ͷ���ֶ�ֵ�궨�� */
#define MP_UCHAR_M      0x00
#define MP_UCHAR_E      0x40
#define MP_UCHAR_B      0x80
#define MP_UCHAR_BE     0xC0

/* MP�������IP���ķ�Ƭ����Լ���Ƭƫ�����ĺ궨�� */
#define MP_IP_DF        0x4000  /* dont fragment flag */
#define MP_IP_MF        0x2000  /* more fragments flag */
#define MP_IP_OFFMASK   0x1fff  /* mask for fragmenting bits */

/* MP����ͷ�����Ⱥ궨�� */

#define MP_MIN_LEN      1       /* ��СMP���ĳ��� */
#define MP_SHDRLEN      2       /* �����к�MPͷ���� */
#define MP_LHDRLEN      4       /* �����к�MPͷ���� */
#define MP_PPP_HDRLEN   4       /* PPP����ͷ���� */

#define MP_REORDERWIN_TIMES_MIN   1
#define MP_REORDERWIN_TIMES_DEF   2
#define MP_REORDERWIN_TIMES_MAX   4
/* End of addition */

#define MP_MASK_BIT0    0x0001
#define MP_MASK_BIT16   0x0100

/* MP���������Ϣ�����±��ö�ٶ��� */
enum
{
    /*���ķ���*/
    MP_IN = 0,              /* 0 IN */
    MP_OUT,                 /* 1 OUT */
    /*MP�¼�*/
    MP_DEL_FATHER_CHANNEL,  /* 2 Deleted a mp bundle */
    MP_ADD_FATHER_CHANNEL,  /* 3 Created a mp bundle */
    MP_DEL_SON_CHANNEL,     /* 4 Removed a mp link */
    MP_ADD_SON_CHANNEL      /* 5 Appended a mp link */
};


#define MP_GET_CHAR(c, cp) { \
    (c) = *( (UCHAR *)(cp) ); \
    (cp) += 1 ; \
}

#define MP_PUT_CHAR(c, cp) { \
    *( (UCHAR *)(cp) ) = (c) ; \
    (cp) += 1 ; \
}

#define MP_GET_SHORT(s, cp) { \
    VOS_CopyVar((s), *((USHORT *)(cp))); \
    (cp) += 2 ; \
}

#define MP_PUT_SHORT(s, cp) { \
    VOS_CopyVar(*((USHORT*)(cp)),(s)) ; \
    (cp) += 2 ; \
}

#define MP_GET_LONG(l, cp) { \
    VOS_CopyVar((l) , *((ULONG *)(cp))); \
    (cp) += 4 ; \
}

#define MP_PUT_LONG(l, cp) { \
    VOS_CopyVar(*((ULONG*)(cp)),(l)) ; \
    (cp) += 4 ; \
}

#define MP_PPP_MAKEHEADER(p, t) \
{ \
    USHORT usPro = t; \
    MP_PUT_CHAR(0xff, p); \
    MP_PUT_CHAR(0x03, p); \
    usPro = VOS_HTONS(usPro); \
    MP_PUT_SHORT(usPro, p); \
}

#define MP_MAKEHEADER( pstMpInfo, pucData, ucFlag, ucClass )\
{ \
    if( 1 == pstMpInfo->bSheRcvShortHdr )\
    {\
        USHORT usHeader;\
        ucFlag = (ucFlag | (ucClass << 4));\
        usHeader = (USHORT)(((USHORT)ucFlag << 8) | pstMpInfo->ulOutSeqNumber[ucClass]);\
#define MP_COUNTFRAGNUM( ulFragNum, ulBeginPos, ulEndPos, ulFragmentBufLen ) \
{\
    if( ulEndPos >= ulBeginPos )\
    {\
        ulFragNum = ulEndPos - ulBeginPos + 1;\
    }\
    else\
    {\
        ulFragNum = ulFragmentBufLen - (ulBeginPos - ulEndPos -1);\
    }\
}

#define MP_SON_CHECKOPTION(pstFatherLcpOption, pstSonLcpOption, ulCheckFailCode, ulWarningId)\
do\
{\
    /* �Ƚ�PFC */\
    if ((pstFatherLcpOption)->neg_pcompression != (pstSonLcpOption)->neg_pcompression)\
    {\
        ulCheckFailCode = PPP_MP_CFG_DIFF;\
        ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
        break;\
    }\
    /* �Ƚ�ACFC */\
    if ((pstFatherLcpOption)->neg_accompression != (pstSonLcpOption)->neg_accompression)\
    {\
        ulCheckFailCode = PPP_MP_CFG_DIFF;\
        ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
        break;\
    }\
    /* �Ƚ�MHF */\
    if (((pstFatherLcpOption)->ucMhfCode != (pstSonLcpOption)->ucMhfCode)\
        || ((pstFatherLcpOption)->ucMhfClass != (pstSonLcpOption)->ucMhfClass))\
    {\
        ulCheckFailCode = PPP_MP_CFG_DIFF;\
        ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
        break;\
    }\
    /* �Ƚ�SSNHF */\
    if ((pstFatherLcpOption)->neg_ssnhf != (pstSonLcpOption)->neg_ssnhf)\
    {\
        ulCheckFailCode = PPP_MP_CFG_DIFF;\
        ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
        break;\
    }\
    /* �Ƚ�mrru/mru */\
    if (((pstFatherLcpOption)->mrru != (pstSonLcpOption)->mrru)\
        || ((pstFatherLcpOption)->mru != (pstSonLcpOption)->mru))\
    {\
        ulCheckFailCode = PPP_MP_CFG_DIFF;\
        ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
        break;\
    }\
    /* ǰ׺ʡ�Ա�Ƚ�:1,Э��������һ�²�������� */\
    if ((pstFatherLcpOption)->neg_prefixE ^ (pstSonLcpOption)->neg_prefixE)\
    {\
        ulCheckFailCode = PPP_MP_CFG_DIFF;\
        ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
        break;\
    }\
    /* ǰ׺ʡ�Ա�Ƚ�:2,����ͨ������ǰ׺ʡ�Ա��ǲ�һ����������� */\
    if ((pstFatherLcpOption)->neg_prefixE  && (pstSonLcpOption)->neg_prefixE)\
    {\
        LONG lCmpRet = 0;\
        if ((NULL == (pstFatherLcpOption)->pstPrefixE) || (NULL == (pstSonLcpOption)->pstPrefixE)) \
        {\
            ulCheckFailCode = PPP_MP_CFG_DIFF;\
            ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
            break;\
        }\
        (VOID)VOS_Mem_Cmp((VOID*)((pstFatherLcpOption)->pstPrefixE), (VOID*)((pstSonLcpOption)->pstPrefixE),\
                           sizeof(MC_PREFIXE_S)*MC_PREFIXE_MAX_NUM, &lCmpRet);\
        if (lCmpRet)\
        { \
            ulCheckFailCode = PPP_MP_CFG_DIFF;\
            ulWarningId = WARNING_MP_CFG_NOCONSISTENT;\
            break;\
        }\
    }\
    ulCheckFailCode = 0; /* check ok */ \
}while(0)

/* MP����·״̬�ĺ궨�� */
#define MP_IF_STATUS_PROT_DOWN  0x1       /*����·�����DOWN*/
#define MP_IF_STATUS_LOW_DOWN   0x2       /*����·�����UP��Э���DOWN*/
#define MP_IF_STATUS_PROT_UP    0x3       /*����·Э���UP�������󶨵���ͨ��δ��Ч*/
#define MP_IF_STATUS_BIND_UP    0x4       /*����·Э���UP�Ұ󶨵���ͨ������Ч*/
#define MP_IF_STATUS_INVALID    0xFF

/* MP��ͨ��������ͨ�����ĺ궨�� */
#define MP_EXISTSON             0x1
#define MP_NOT_EXISTSON         0x0

/* MP MIB��Ϣ��ȡ�ĺ궨�� */
#define MP_MIB_MULTILINKTABLE_INFO  1   /*��ȡ��ͨ����Ϣ��*/
#define MP_MIB_MEMBERLINKTABLE_INFO 2   /*��ȡ��ͨ����Ϣ��*/

/* MP NCPЭ��UP�Ժ�ͨ��IFNET֪ͨPPPoE Client����DDR��Ӧ�ӿ�UP�ĺ궨�� */
#define MP_PPP_NEG_UP               1
#define MP_PPP_NEG_DOWN             0

/* NE5000��Ʒע���Ǻ궨�� */
#define MP_PRODUCT_NE5000_REG       0x01

/* MP WAITLIST��Ӧ����ĺ궨�� */
#define MP_WAITLIST_GET_USERINFO    0x01

/* MP SID�궨�� */
#define MP_SID_MP                   0x01
#define MP_SID_CACHE                0x02

/* ��Ч��MPͨ���� */
#define MP_INVALID_CHAN_NUM         0xFFFFFFFF

/* MP SHELLע���ģ����Ϣ�궨�� */
#define MP_MID_MP               g_stMPModInfo.ulMID_MP
#define MP_QUE_IP_INPUT         g_stMPModInfo.ulQUE_IP_INPUT
/* Added by hanna55555, VISPV1R8C01 for mp-link support ipv6, 2009/3/18 */
#define MP_QUE_IP6_INPUT        g_stMPModInfo.ulQUE_IPV6_INPUT 
/*End of Added by hanna55555, 2009/3/18 */

#define MP_QUE_IPX_INPUT        g_stMPModInfo.ulQUE_IPX_INPUT
#define MP_QUE_ISIS_INPUT       g_stMPModInfo.ulQUE_ISIS_INPUT
#define MP_QUE_MPLS_INPUT       g_stMPModInfo.ulQUE_MPLS_INPUT
#define MP_QUE_PPP_ASY          g_stMPModInfo.ulQUE_PPP_ASY
#define MP_QUE_PPP_MP           g_stMPModInfo.ulQUE_PPP_MP
#define MP_QUE_PPP_NEGO         g_stMPModInfo.ulQUE_PPP_NEGO
#define MP_QUE_PPP_STAC         g_stMPModInfo.ulQUE_PPP_STAC
#define MP_QUE_PPPMUX_INPUT     g_stMPModInfo.ulQUE_PPPMUX_INPUT
/* End of addition */
#define MP_WAITLIST_MAIN_TYPE   g_stMPModInfo.ulWaitList 

/* MP SHELLע���API�ӿں����궨�� */
#define MP_GetDialerFatherIfIndex   g_stMPShellApi.pfDDR_GetFatherIfIndex
#define MP_DialerIoCtl              g_stMPShellApi.pfDDR_IoCtl
#define MP_ResetDialerIdleTimeout   g_stMPShellApi.pfDDR_ResetIdleTimeout
#define MP_DebugOutString           g_stMPShellApi.pfDebugOutString
#define MP_CloneTemplateQue         g_stMPShellApi.pfMPQOS_CloneTemplateQue
#define MP_DelFatherFromQos         g_stMPShellApi.pfMPQOS_DelFatherFromQos
#define MP_MpGroupQueInit           g_stMPShellApi.pfMPQOS_MpGroupQueInit
#define MP_QosChange                g_stMPShellApi.pfMPQOS_QosChange
#define MP_EnDropQue                g_stMPShellApi.pfMP_EnDropQue
#define MP_EnQueue                  g_stMPShellApi.pfMP_EnQueue
#define MP_PPP_BAK_RealTime_Send    g_stMPShellApi.pfPPP_BAK_RealTime_Send
#define MP_QOS_IfCanSendPkt         g_stMPShellApi.pfQOS_IfCanSendPkt
#define MP_MPQOS_Transmit           g_stMPShellApi.pfMPQOS_QM_Transmit

#define MP_MPQOSTransmitDone        g_stMPShellApi.pfMPQOS_QM_TransmitDone
#define MP_QOSTransmitDone          g_stMPShellApi.pfQOS_QM_TransmitDone


extern DLL_S * MP_GetMpgroupList();


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _MP_DEF_H_ */
