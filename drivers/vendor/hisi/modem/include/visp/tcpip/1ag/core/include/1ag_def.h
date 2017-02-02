/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_def.h
*
*  Project Code: VISPV100R007
*   Module Name: 1AG  
*  Date Created: 2008-3-3
*        Author: yebo(62007)
*   Description: 1AGģ��궨��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-3  yebo(62007)         Create the first version.
*
*******************************************************************************/
#ifndef _1AG_DEF_H
#define _1AG_DEF_H

#ifdef  __cplusplus
    extern "C"{
#endif

/* 1AGЭ������*/
#define OAM_1AG_ETHERTYPE 0x8902

/*VLAN ���� 0x8100*/
#define OAM_1AG_VLANTYPE 0x8100
#define DOT1Q_TAG_SIZE   4

/* ���ձ��Ľ���ʱ���ڱ�ʶ������û�д�VLANͷ */
#define OAM_1AG_NOVLAN_FLAG  0xFFFF

/* ��VLAN����̫ͷ���� */
#define OAM_1AG_ETHHEAD_LEN sizeof(OAM1AG_ETHERHDR_S)

/* ����VLAN����̫ͷ���� */
#define OAM_1AG_NOVLAN_ETHHEAD_LEN sizeof(OAM1AG_NOVLAN_ETHERHDR_S)

/* ����VLANͷ��SNAP����ת��Ϊ��̫����ʱSNAPͷ��ƫ���� */
#define OAM_1AG_CUTSNAP_NOVLAN_OFFSET 12
/* ��VLANͷ��SNAP����ת��Ϊ��̫����ʱSNAPͷ��ƫ���� */
#define OAM_1AG_CUTSNAP_OFFSET 16
/* SNAP����ת��Ϊ��̫����ʱӦȥ����SNAPͷ���� */
#define OAM_1AG_CUTSNAP_LENGTH 8

/* �յ�һ������VLAN��LB��LT����ʱ,��ӿڴ��ڶ������VLAN��MEP��Ϣʱ,�ص�֪ͨ��Ϣ�������� */
#define OAM_1AG_MAX_NOVLANINFONUM  8


/*MD + MA������ֳ���*/
#define OAM_1AG_MAX_MDMANAME_LEN 44
/*CCM����MD��MA��Ϣ����*/
#define OAM_1AG_MAX_MDMAINFO_LEN 48

/* ���MD���� */
#define OAM_1AG_MAX_MDLEVEL 7

/*���MD��*/
#define OAM_1AG_MAX_MDNUM 8
/*���MA��*/
#define OAM_1AG_MAX_MANUM 3000
/*���MEP��*/
#define OAM_1AG_MAX_MEPNUM 3000
/*���RMEP��*/
#define OAM_1AG_MAX_RMEPNUM 3000
/*MEPID��Сֵ*/
#define OAM_1AG_MIN_MEPID 1
/*mepid���ֵ*/
#define OAM_1AG_MAX_MEPID 8191

/* ��С��VLAN ID */
#define OAM_1AG_MIN_VLANID 1
/* ����VLAN ID */
#define OAM_1AG_MAX_VLANID 4094

/* ������С���ȼ� */
#define OAM_1AG_MIN_PRIORITY 0
/* ����������ȼ� */
#define OAM_1AG_MAX_PRIORITY 7
/* ����MA��VLAN���ȼ���ʼֵ, 1AG Pingʹ��Э��ջĬ�Ϲ�����дVLAN���ȼ��ı�־ */
#define OAM_1AG_INIT_PRIORITY  0xFF


/*LBR������󻺴�ڵ���*/
#define OAM_1AG_MAX_LBRNODE 128
/*���LBR�������ʱ����*/
#define OAM_1AG_CLRQUE_INTERVAL 60000
/*LBR�ڵ㳬ʱʱ��*/
#define OAM_1AG_LBR_MAXTIMEOUT 60000
/*�����ͨPING�û���*/
#define OAM_1AG_MAX_LBUSER 16
/*Ĭ��LB���ķ��ʹ���*/
#define OAM_1AG_LBM_DEFAULT_COUNT 5
/*Ĭ��LB���ĳ���*/
#define OAM_1AG_LB_DEFAULT_LEN 128
/*���LB���ĳ���*/
#define OAM_1AG_LBM_MAX_LEN 1500
/*��С���ĳ���*/
#define OAM_1AG_LBM_MIN_LEN 95

/*����MEP����CCM��ʱʱ��*/
#define OAM_1AG_MEPTIME  20
/*����RMEP��ⳬʱʱ��*/
#define OAM_1AG_RMEPTIME 50
/*����LTR��ⳬʱʱ��*/
#define OAM_1AG_LTRTIMER  1000

/*����AIS��ⳬʱʱ��*/
#define OAM_1AG_AISTIMER  500

/*Ĭ�ϳ�ʱʱ��*/
#define OAM_1AG_LB_DEFAULT_TIMEOUT 2
/*��С��ʱʱ��*/
#define OAM_1AG_LB_MIN_TIMEOUT 1
/*���ʱʱ��*/
#define OAM_1AG_LB_MAX_TIMEOUT 65535
/*LB���Է��ͱ��������ʱ��*/
#define OAM_1AG_LB_MAX_INTERVAL 60
/*�û��Զ��������С�û�����������*/
#define OAM_1AG_LB_MIN_USERBUFFLEN 40
/*�û��Զ����������û�����������*/
#define OAM_1AG_LB_MAX_USERBUFFLEN 1460
/* ��ͨƫ�� */
#define   OAM_1AG_VRPLB_FIRSTTLVOFFSET  10
/* ��׼ƫ�� */
#define   OAM_1AG_STDLB_FIRSTTLVOFFSET      4
/* ��ͨlb����tlv���ͺͲݰ�7����tlv������ͬ */
#define OAM_1AG_LB_DATATYPE    4
#define OAM_1AG_LB_STDDATALEN    8
#define OAM_1AG_LB_VRPDATALEN   sizeof(OAM_1AG_VRPDATATLV_VALUE_S)

/* ��СLB���ĳ��� ,��̫ͷ+LB�����8���ֶ�+end tlv*/
#define  OAM_1AG_LB_MIN_LEN    (OAM_1AG_ETHHEAD_LEN+8+1)
/* LBM������DATA TLV�����ֶμ�֮ǰ��1AG���ĳ���(��������̫ͷ) */
#define  OAM_1AG_FIXED_LBM_LEN  11

/*����ͬʱ�����LT������*/
#define OAM_1AG_MAX_LTMSEND 16
/* LT����С��ʱ���� */
#define OAM_1AG_MIN_LT_TIMEOUT 1
/* LT�����ʱ���� */
#define OAM_1AG_MAX_LT_TIMEOUT 60

/* ��װLTM��LTRʱ����first tlv offset�ֶε�ֵ��Ŀ��������ͨ��ʵ��һ��,ͬʱ��Υ����׼Э��,
    ��˹����LTM���Ŀ���ͬʱ��������ģʽ,�������ı���������� */
#define OAM_1AG_LT_FIRST_TLV_OFFSET 28
/* ��׼LTM���ĵ�first tlv offset ֵ */
#define OAM_1AG_LTM_DRAFT7_FIRST_TLV_OFFSET 25
/* 1AG-CFM-2007��׼LTM���ĵ�first tlv offset ֵ */
#define OAM_1AG_LTM_STD_FIRST_TLV_OFFSET 17
/* ��׼LTR���ĵ�first tlv offset ֵ */
#define OAM_1AG_LTR_DRAFT7_FIRST_TLV_OFFSET 22
/* 1AG-CFM-2007��׼LTR���ĵ�first tlv offset ֵ */
#define OAM_1AG_LTR_STD_FIRST_TLV_OFFSET 6

/* ����Ϊ1AG����ͷ��FirstTlvOffset�ֶεĳ���,������1�ֽڵ�FirstTlvOffset�ֶ� */
#define OAM_1AG_LTR_STD_COMMON_OFFSET 3
#define OAM_1AG_LTM_STD_COMMON_OFFSET 3


/* TLV����,����type.length.value���� */
#define OAM_1AG_LTM_EGRESS_TLV_LEN  sizeof(OAM_1AG_LTM_EGRESS_TLV_S)
/* END TLV���� */
#define OAM_1AG_END_TLV_LEN       1


/* LTR �е� TLV Ҫ�õ��ĺ� */
#define REPLY_INGRESS_TLV_LENGTH 13
#define REPLY_EGRESS_TLV_LENGTH 13
#define INGRESS_PORT_ID_LENGTH 4
#define INGRESS_PORT_ID_SUBTYPE 5
#define EGRESS_PORT_ID_LENGTH 4
#define EGRESS_PORT_ID_SUBTYPE 5
#define REPLY_Y1731INGRESS_TLV_LENGTH 7
#define REPLY_Y1731EGRESS_TLV_LENGTH 7



/* �豸�ĳ��˿���Ϣ���� */
#define OAM_1AG_EGRESSID_SIZE 8

/* �豸����/���˿�ID���� */
#define OAM_1AG_PORTID_SIZE 4

/*��ʾRMEP�Ƿ��·���NP*/
#define OAM_1AG_NODOWNLOADNP 0   /* ��ʾ��RMEPδ�·���NP */
#define OAM_1AG_DOWNLOADNP   1   /* ��ʾ��RMEP�·���NP */


/* ��ʾ�յ���CCM�����Ƿ����VLAN tag */
#define OAM_1AG_NOTVLAN_CCM   0   /* ��VLAN CCM���� */
#define OAM_1AG_VLAN_CCM      1   /* VLAN CCM����  */

/* ��ɾ��MDʱ,��ɾ��MD�µ�����MA,MEP��RMEP,ÿ��ɾ�������ͱ�����Ϣ�ǲ���Ҫ��,�����ʱ����������Ϣ;��������ɾ��
MA,MEP,RMEP������뷢�ͱ�����Ϣ */
/* ɾ��MA,MEP,RMEPʱ�Ƿ��ͱ�����Ϣ */
#define OAM_1AG_BACKUP 1        /* ���ͱ�����Ϣ */
#define OAM_1AG_NOBACKUP 0      /* �����ͱ�����Ϣ */

/*CCM�����ֶ�ƫ����*/
#define OAM_1AG_MDTYPE_OFFSET   0
#define OAM_1AG_MDLENGTH_OFFSET 1
#define OAM_1AG_MDNAME_OFFSET   2
#define OAM_1AG_MALENGTH_OFFSET 3
#define OAM_1AG_MANAME_OFFSET   4

#define OAM_Y1731_MEGID_TYPE_ICC      32
#define OAM_Y1731_MEGID_LEN_ICC       13

#define OAM_Y1731_MEGTYPE_OFFSET 1
#define OAM_Y1731_MEGLENGTH_OFFSET   2
#define OAM_Y1731_MEGID_OFFSET 3


/*��׼CCM����ƫ����*/
#define OAM_1AG_CCM_STDOFFSET    70
/*��׼CCM������䳤��*/
#define OAM_1AG_CCM_STDPAD_LEN   16
/*������ͨCCM����ƫ����*/
#define OAM_1AG_CCM_VRPOFFSET    54

/* ��ʱ���±����� */
#define OAM_1AG_100MSLISTINDEX 0
#define OAM_1AG_1SLISTINDEX    1
#define OAM_1AG_10SLISTINDEX   2

/* AIS ��ʱ���±����� */
#define OAM_Y1731_AIS_1SLISTINDEX 0
#define OAM_Y1731_AIS_1MINLISTINDEX    1

/* Interface Status��� */
#define OAM_1AG_INTERFACE_UP    1
#define OAM_1AG_INTERFACE_DOWN  2

/* ���Ͳ���Interface Tlv��CCM */
#define OAM_1AG_NOTLVFLAG 0
/* ���ʹ�Interface Tlv��CCM */
#define OAM_1AG_TLVFLAG   1
/* Added by hanna55555, Y1731-CCM, 2010/5/5 */
/* ���Ͳ����κ�Tlv��CCM */
#define OAM_1AG_NOTLVFLAG_Y1731 2
/*End of Added by hanna55555, 2010/5/5 */

/*SID����*/
#define SID_OAM_1AG_MD   1
#define SID_OAM_1AG_MA   2
#define SID_OAM_1AG_MEP  3
#define SID_OAM_1AG_RMEP 4
#define SID_OAM_1AG_DISP_MEP 5

/*1AG���ܲ��Կ�ʼ*/
#define OAM_1AG_CAPTEST_BEGIN 1
/*1AG���ܲ��Խ���*/
#define OAM_1AG_CAPTEST_END   2
/*VLAN ID��Hashֵ*/
#define OAM_1AG_VLANHASHVALUE 128


#define OAM_1AG_SET_VERSION_USER_INPUT 0
#define OAM_1AG_SET_VERSION_TRUNK_PORT 1

#define OAM_1AG_NOT_HANDLE      0xFFF /* 1ag ������δ������Ҫ����ģ��������� */

typedef enum enOAM_1AG_PKT_DEBUG
{
    OAM_1AG_PKTIN = 1, /*���յ��ı���*/
    OAM_1AG_PKTOUT,    /*���͵ı���*/
    OAM_1AG_FORWARD,   /*ת���ı���*/
    OAM_1AG_MAX_END
}OAM_1AG_PKT_DEBUG_E;

/*���ݱ�׼ģʽ*/
#define OAM_1AG_COMPATIBLE_STD    0
/*������ͨģʽ*/
#define OAM_1AG_COMPATIBLE_VRP    1

/*OAM 1ag���Կ���,��Ӧλ0-�ر�,1-����*/
#define OAM_1AG_DEBUGCCON   1
#define OAM_1AG_DEBUGLBON   2
#define OAM_1AG_DEBUGLTON   4
#define OAM_1AG_DEBUGAISON   8
/*�ж�CC�Ƿ���*/
#define OAM_1AG_DEBUGCCISON(ulDebugSwitch) ((ulDebugSwitch) & OAM_1AG_DEBUGCCON)

/*�ж�LB�Ƿ���*/
#define OAM_1AG_DEBUGLBISON(ulDebugSwitch) ((ulDebugSwitch) & OAM_1AG_DEBUGLBON)

/*�ж�LT�Ƿ���*/
#define OAM_1AG_DEBUGLTISON(ulDebugSwitch) ((ulDebugSwitch) & OAM_1AG_DEBUGLTON)

/*�ж�AIS�Ƿ���*/
#define OAM_1AG_DEBUGAISISON(ulDebugSwitch) ((ulDebugSwitch) & OAM_1AG_DEBUGAISON)

/* �����װCCM���ģ�ulValue��������װLTM���ģ�ulValue���+8 */
#define OAM_1AG_DEST_ADDRESS(pdestmac, ucValue) \
{\
    (pdestmac[0]) = 0x01;\
    (pdestmac[1]) = 0x80;\
    (pdestmac[2]) = 0xC2;\
    (pdestmac[3]) = 0x00;\
    (pdestmac[4]) = 0x00;\
    (pdestmac[5]) = 0x30 | (ucValue);\
}

/* ���ݰ汾�ż������� */
#define OAM_1AG_DESTMASK_ADDRESS(pdestmac_mask, ucversion) \
{\
    (pdestmac_mask[0]) = 0xff;\
    (pdestmac_mask[1]) = 0xff;\
    (pdestmac_mask[2]) = 0xff;\
    if (ucversion) /* draft8 */\
    {\
        (pdestmac_mask[3]) = 0xff;\
        (pdestmac_mask[4]) = 0xff;\
        (pdestmac_mask[5]) = 0xf0;\
    }\
    else /* draft7 */\
    {\
        (pdestmac_mask[3]) = 0x00;\
        (pdestmac_mask[4]) = 0x00;\
        (pdestmac_mask[5]) = 0x00;\
    }\
}

/* �����Ƿ���VLANͷ��־��ȡ��̫ͷ�ĳ��� */
#define OAM_1AG_GET_ETHHEADER_LEN(ucVlanFlag, ulEthHeaderLen)\
{\
    if (OAM_1AG_SEND_WITH_VLAN == ucVlanFlag)\
    {\
        ulEthHeaderLen = OAM_1AG_ETHHEAD_LEN;\
    }\
    else\
    {\
        ulEthHeaderLen = OAM_1AG_NOVLAN_ETHHEAD_LEN;\
    }\
}

/* �����Ƿ���VLANͷ��־��ȡ��̫ͷ�ĳ��� */
#define OAM_1AG_GET_ETHHEADER_LEN_WITH_VLANID(ucVlanId, ulEthHeaderLen)\
{\
    if (OAM_1AG_NOVLAN_FLAG == ucVlanId)\
    {\
        ulEthHeaderLen = OAM_1AG_NOVLAN_ETHHEAD_LEN;\
    }\
    else\
    {\
        ulEthHeaderLen = OAM_1AG_ETHHEAD_LEN;\
    }\
}


/* ����õ�ַ�Ȳ���ȫ0��ַ,Ҳ����ȫF��ַ,Ҳ���Ƕಥ��ַ(��һ�ֽڵ����λΪ1��ʾ�Ƕಥ��ַ),��õ�ַ���ǵ�����ַ */
/* physical��ַ��һ�ֽڵ����λΪ0���Ҹ�physical��ַ����ȫ0��ַ�����physical��ַ���ǵ�����ַ */
#define ISUNICASTMAC(aucMac)\
            ( (0 == (aucMac[0] & 1))\
              && ((0 != aucMac[0]) || (0 != aucMac[1]) || (0 != aucMac[2])\
                 || (0 != aucMac[3]) || (0 != aucMac[4])|| (0 !=  aucMac[5]) )\
            )

/* ���ڼ���hashֵ */
#define OAM_1AG_HASH_CODE 16777619

#define GET_MDINFO_PTR(ulMdIndex)       ((OAM_1AG_MD_S*)g_pstMdChainTable[ulMdIndex].pstMdInfo)
#define GET_MAINFO_PTR(ulMaIndex)       ((OAM_1AG_MA_S*)g_pstMaChainTable[ulMaIndex].pstMaInfo)
#define GET_MEPINFO_PTR(ulMepIndex)     ((OAM_1AG_MEP_S*)g_pstMepChainTable[ulMepIndex].pstMepInfo)
#define GET_RMEPINFO_PTR(ulRmepIndex)   ((OAM_1AG_RMEP_S*)g_pstRmepChainTable[ulRmepIndex].pstRmepInfo)

/* ������ȥ��ʱ�䣬������ʱ�䷴ת���� */
#define OAM_1AG_INVALID_ULONG 0xFFFFFFFF
#define ELAPSETIME(begintime, endtime, elapsetime)\
{\
    if (begintime > endtime) \
    {\
        elapsetime = endtime + (OAM_1AG_INVALID_ULONG - begintime) + 1;\
    }\
    else\
    {\
        elapsetime = endtime - begintime;\
    }\
}

/*����NP����ĺ�*/
#define OAM1AG_PPI_Update(ulIfIndex,ulOprType,pEoam1agMsg)\
{\
    if ((OAM_1AG_FULLNP == g_stOam1agModInfo.ulNpModel) || (OAM_1AG_HALFNP == g_stOam1agModInfo.ulNpModel))\
    {\
        if (g_pfTCPIP_PPI_1AG_Update)\
        {\
            ULONG ulResult = OAM1AG_OK;\
            /*��¼ʱ���*/\
            MAKE_NP_STARTDOT(PPI_TYPE_OAM1AG, ulOprType);\
            ulResult = g_pfTCPIP_PPI_1AG_Update(ulIfIndex,ulOprType,pEoam1agMsg);\
            /*��¼ʱ���*/\
            MAKE_NP_ENDDOT(PPI_TYPE_OAM1AG);\
            TCPIP_PPI_1AG_LogMsg(ulResult,ulIfIndex,ulOprType,(VOID*)pEoam1agMsg);\
        }\
    }\
}

/*���ӻ�ȡMEP��ϢNP����ĺ�*/
#define OAM1AG_PPI_GetMep(ulIfIndex,ulOprType,pEoam1agMsg,ulResult)\
{\
    if (g_pfTCPIP_PPI_1AG_Update)\
    {\
        /*��¼ʱ���*/\
        MAKE_NP_STARTDOT(PPI_TYPE_OAM1AG, ulOprType);\
        ulResult = g_pfTCPIP_PPI_1AG_Update(ulIfIndex,ulOprType,pEoam1agMsg);\
        /*��¼ʱ���*/\
        MAKE_NP_ENDDOT(PPI_TYPE_OAM1AG);\
        TCPIP_PPI_1AG_LogMsg(ulResult,ulIfIndex,ulOprType,(VOID*)pEoam1agMsg);\
    }\
}

/*��װ1AGȫ��NP�·���Ϣ*/
#define PPI_1AG_COPYGLBINFO(pstPpi1agGlbInfo)\
{\
    (pstPpi1agGlbInfo)->usPktType = g_usOam1agPktType;\
    (pstPpi1agGlbInfo)->ucPktPriority = g_ucOam1agPktPri;\
    (pstPpi1agGlbInfo)->ulCompatibleSwitch = g_ulCompatibleSwitch;\
}

/*��װ1AG MA�·���Ϣ*/
#define PPI_1AG_COPYMAINFO(pstPpi1agMaInfo,pstMaInfo)\
{\
    OAM_1AG_MD_S *pstMdInfoTemp = NULL;\
    \
    pstMdInfoTemp = (OAM_1AG_MD_S *)((g_pstMdChainTable[(pstMaInfo)->ulMdIndex]).pstMdInfo);\
    /*�ڵ��ú�ǰ�Ѿ���֤��pstMdInfoTemp�ǿ�*/\
    (VOID)TCPIP_Mem_Copy((VOID*)(pstPpi1agMaInfo)->szMdName,OAM_1AG_MAX_MDNAME_LEN+1,(VOID*)pstMdInfoTemp->szMDName, OAM_1AG_MAX_MDNAME_LEN + 1);\
    (VOID)TCPIP_Mem_Copy((VOID*)(pstPpi1agMaInfo)->szMaName,OAM_1AG_MAX_MANAME_LEN+1,(VOID*)(pstMaInfo)->szMaName, OAM_1AG_MAX_MANAME_LEN + 1);\
    (pstPpi1agMaInfo)->ucCcmInterval = (pstMaInfo)->ucCcmInterval;\
    (pstPpi1agMaInfo)->ucCompatibleType = (pstMaInfo)->ucCompatibleFlag;\
    (pstPpi1agMaInfo)->usVlanId = (pstMaInfo)->usVlanId;\
    (pstPpi1agMaInfo)->ucMaPri  = (OAM_1AG_INIT_PRIORITY == (pstMaInfo)->ucMaVlanPri)?g_ucOam1agPktPri:(pstMaInfo)->ucMaVlanPri;\
    (pstPpi1agMaInfo)->ucRdiFlag = (pstMaInfo)->ucRdiFlag;\
    (pstPpi1agMaInfo)->ucMaNameType = (pstMaInfo)->ucMaNameType;\
}

/*��װ1AG CCM�·���Ϣ*/
#define PPI_1AG_COPYCCMINFO(pstPpiCcmInfo,pstMepInfo)\
{\
    OAM_1AG_MA_S *pstTempMaInfo = NULL;\
    OAM_1AG_MD_S *pstMdInfo = NULL;\
    /*�ڵ��ú�ǰ�Ѿ���֤��pstMdInfo��pstMaInfo�ǿ�*/\
    pstTempMaInfo = (OAM_1AG_MA_S *)((g_pstMaChainTable[(pstMepInfo)->ulMaIndex]).pstMaInfo);\
    pstMdInfo = (OAM_1AG_MD_S *)((g_pstMdChainTable[pstTempMaInfo->ulMdIndex]).pstMdInfo);\
    (VOID)TCPIP_Mem_Copy((pstPpiCcmInfo)->szMdName,OAM_1AG_MAX_MDNAME_LEN+1,pstMdInfo->szMDName, OAM_1AG_MAX_MDNAME_LEN + 1);\
    (VOID)TCPIP_Mem_Copy((pstPpiCcmInfo)->szMaName,OAM_1AG_MAX_MANAME_LEN+1,pstTempMaInfo->szMaName, OAM_1AG_MAX_MANAME_LEN + 1);\
    (pstPpiCcmInfo)->usMepId = (pstMepInfo)->usMepId;\
    (pstPpiCcmInfo)->usVId = pstTempMaInfo->usVlanId;\
    (pstPpiCcmInfo)->ucMdLevel = pstMdInfo->ucMdLevel;\
    (pstPpiCcmInfo)->ucCcmInterval = pstTempMaInfo->ucCcmInterval;\
    (pstPpiCcmInfo)->ucRdiFlag = pstTempMaInfo->ucRdiFlag;\
    (pstPpiCcmInfo)->ucMaPri = (OAM_1AG_INIT_PRIORITY == (pstTempMaInfo)->ucMaVlanPri)?g_ucOam1agPktPri:(pstTempMaInfo)->ucMaVlanPri;\
    (pstPpiCcmInfo)->ucCompatibleType = pstTempMaInfo->ucCompatibleFlag;\
    (pstPpiCcmInfo)->uc1agVersion = (pstMepInfo)->uc1agVersion;\
    (pstPpiCcmInfo)->ucVlanFlag = (pstMepInfo)->ucVlanFlag;\
    (pstPpiCcmInfo)->ucCcSendEnable = (pstMepInfo)->ucCcSendEnable;\
    (pstPpiCcmInfo)->ulIfIndex = (pstMepInfo)->ulIfIndex;\
    (pstPpiCcmInfo)->usLossDetectTimer = (pstMepInfo)->usLossDetectTimer;\
}

/*��װY1731 PM�·���Ϣ*/
#define PPI_Y1731_COPYPMINFO(pstPpiPMInfo,pstMepInfo)\
{\
    OAM_1AG_MA_S *pstTempMaInfo = NULL;\
    OAM_1AG_MD_S *pstMdInfo = NULL;\
    /*�ڵ��ú�ǰ�Ѿ���֤��pstMdInfo��pstMaInfo�ǿ�*/\
    pstTempMaInfo = (OAM_1AG_MA_S *)((g_pstMaChainTable[(pstMepInfo)->ulMaIndex]).pstMaInfo);\
    pstMdInfo = (OAM_1AG_MD_S *)((g_pstMdChainTable[pstTempMaInfo->ulMdIndex]).pstMdInfo);\
    (VOID)TCPIP_Mem_Copy((pstPpiPMInfo)->szMdName,OAM_1AG_MAX_MDNAME_LEN+1,pstMdInfo->szMDName, OAM_1AG_MAX_MDNAME_LEN + 1);\
    (VOID)TCPIP_Mem_Copy((pstPpiPMInfo)->szMaName,OAM_1AG_MAX_MANAME_LEN+1,pstTempMaInfo->szMaName, OAM_1AG_MAX_MANAME_LEN + 1);\
    (pstPpiPMInfo)->usMepId = (pstMepInfo)->usMepId;\
}

/* ��װRMEP�·���Ϣ */
#define PPI_1AG_COPYRMEPINFO(pstPpiRmepInfo, pstRmepInfo)\
{\
    OAM_1AG_MD_S *pstMd = NULL;\
    OAM_1AG_MA_S *pstMa = NULL;\
    /*�ڵ��ú�ǰ�Ѿ���֤��pstMdInfo��pstMaInfo�ǿ�*/\
    pstMa = (OAM_1AG_MA_S *)((g_pstMaChainTable[(pstRmepInfo)->ulMaIndex]).pstMaInfo);\
    pstMd = (OAM_1AG_MD_S *)((g_pstMdChainTable[pstMa->ulMdIndex]).pstMdInfo);\
    (pstPpiRmepInfo)->ulIfIndex = (pstRmepInfo)->ulIfIndex;\
    (pstPpiRmepInfo)->usVlanId = GET_MAINFO_PTR((pstRmepInfo)->ulMaIndex)->usVlanId;\
    (pstPpiRmepInfo)->usRmepId = (pstRmepInfo)->usRmepId;\
    (pstPpiRmepInfo)->ucInterval = (pstRmepInfo)->ucCcmInterval;\
    (pstPpiRmepInfo)->ucMdLevelFlag = (pstRmepInfo)->ucMdLevelFlag;\
    (VOID)TCPIP_Mem_Copy((pstPpiRmepInfo)->aucMacAddr,MACADDRLEN,(pstRmepInfo)->aucMacAddress,OAM_1AG_MACADDR_LEN);\
    (VOID)TCPIP_Mem_Copy((pstPpiRmepInfo)->aucMdName,OAM_1AG_MAX_MDNAME_LEN+1,pstMd->szMDName, OAM_1AG_MAX_MDNAME_LEN + 1);\
    (VOID)TCPIP_Mem_Copy((pstPpiRmepInfo)->aucMaName,OAM_1AG_MAX_MANAME_LEN + 1,pstMa->szMaName, OAM_1AG_MAX_MANAME_LEN + 1);\
    (pstPpiRmepInfo)->ucRdiFlag = (pstRmepInfo)->ucRdiFlag;\
    (pstPpiRmepInfo)->ucRemoteIfFlag = (pstRmepInfo)->ucRemoteIfFlag;\
    (pstPpiRmepInfo)->ucVlanFlag = (pstRmepInfo)->ucVlanFlag;\
    (pstPpiRmepInfo)->ucRMepStatic = (pstRmepInfo)->ucRMepStatic;\
    (pstPpiRmepInfo)->ucMdLevel = (pstRmepInfo)->ucMdLevel;\
}

#define INFO_MAX_LEN  800

#define LB_OUTPUT(szBuf,ulID)                \
if (g_pfOAM1AGOutputInfo)               \
{                                       \
    (VOID)g_pfOAM1AGOutputInfo((UCHAR *)szBuf,ulID);   \
}

#define LT_OUTPUT(szBuf,ulID)                \
if (g_pfOAM1AGOutputInfo)               \
{                                       \
    (VOID)g_pfOAM1AGOutputInfo((UCHAR *)szBuf,ulID);   \
}


#define OAM_1AG_INFOOUTPUTCOUNT_EACHTIME    (8)

/* ���ڼ��㶯̬CCM���ϻ�ʱ�� */
#define OAM_1AG_1TIMERSOLD(x)    ((x) * 1200)
#define OAM_1AG_10TIMERSOLD(x)   ((x) * 120)
#define OAM_1AG_100TIMERSOLD(x)  ((x) * 12)


#define OAM_1AG_RMEP_NOTIFY     1  /*1AG �����·����*/
#define OAM_1AG_RMEP_CC_DETECT  2  /*1AG  RMEP CC̽����*/

#ifdef  __cplusplus
}
#endif

#endif

