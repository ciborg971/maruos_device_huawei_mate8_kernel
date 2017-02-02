/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4r_ha.h
*
*  Project Code: VISPV1R6
*   Module Name: DHCP4R  
*  Date Created: 2007-7-12
*        Author: LY(57500)
*   Description: DHCP4R HA ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-7-12  LY(57500)     Create the first version.
*
*******************************************************************************/

#ifndef _DHCP4R_HA_H_
#define _DHCP4R_HA_H_

#ifdef __cplusplus
extern "C"{
#endif

/* �������ͣ������ڹ���HA�ṹͷ��ucOperation�ֶ� */
#define DHCP4R_HA_BATCH     0x1
#define DHCP4R_HA_REALTIME  0x2

/* ������Ϣ���� ��������DHCP4Rģ�鱸����Ϣͷ��usMsgType�ֶ�   */
/* ע: ������Ϣ����ʱҪͬ������ g_aulDhcp4rRtPackLen����� g_aszDhcp4rRtBakDbgInfo���� */
enum enDhcp4rRtBak
{
    DHCP4R_HA_COMMON_CFG = 1,   /* 1, ����������Ϣʵʱ����     */
    DHCP4R_HA_RELAYENABLE,      /* 2, ʹ��ȥʹ��RELAYʵʱ����  */
    DHCP4R_HA_CFGSERVER,        /* 3, �����м̵�ַʵʱ����     */
    DHCP4R_HA_CFG82,            /* 4, ����82��ѡ��ʵʱ����     */

    DHCP4R_HA_VRFCOMCFG,        /* 5, VRF����������Ϣʵʱ����  */
    DHCP4R_HA_VRFRELAYENABLE,   /* 6, VRFʹ��/ȥʹ��RELAYʵʱ���� */
    DHCP4R_HA_VRFCFGSERVER,     /* 7, VRF����server��ַʵʱ���� */
    DHCP4R_HA_VRFCFG82,         /* 8, VRF����82ѡ��ʵʱ����    */
    DHCP4R_HA_VRFCFG82MODE,        /* 9,����82ѡ���ģʽʵʱ���� */
};

/* DHCP4Rģ�鱸����Ϣͷ */
typedef struct tagDHCP4RHeadBak
{
    USHORT usMsgType;   /* DHCP4R������Ϣ����   */
    USHORT usMsgLen;    /* DHCP4R������Ϣ����,����������Ϣͷ����    */
}DHCP4R_HEAD_BAK_S;

/* DHCP4Rģ�鹫��������������Ϣ�ṹ */
typedef struct tagDHCP4RCommonCfgBak
{
    ULONG ulMaxHops;    /* �м����� */
    ULONG ulFwdMode;    /* �м̷�ʽ */
    UCHAR ucRelayTos;   /* RELAYTOS */
    UCHAR ucPad[3];
}DHCP4R_COMMON_CFG_BAK_S;

/* ʹ��ȥʹ��ʵʱ���� */
typedef struct tagDHCP4RRelayEnableBak
{
    ULONG ulIfIndex;
    ULONG ulSetYes;
}DHCP4R_RELAY_ENABLE_BAK_S;

/* �����м̵�ַʵʱ���� */
typedef struct tagDHCP4RCfgServerBak
{
    ULONG ulOperate;
    ULONG ulIfIndex;
    ULONG ulServerIP;
}DHCP4R_CFG_SERVER_BAK_S;

/* ����82��ѡ��ʵʱ����, 40�ֽ� */
typedef struct tagDHCP4RCfgOption82Bak
{
    ULONG ulOperate;
    ULONG ulIfIndex;
    ULONG ulSubCode;
    ULONG ulSubLen;
    UCHAR aucSubVar[DHCP4R_82_SUB_MAXLEN];
}DHCP4R_CFG_OPTION82_BAK_S;

/* ֧��VRF��ʹ��ȥʹ��ʵʱ���� */
typedef struct tagDHCP4RVrfRelayBak
{
    ULONG ulVrfIndex;
    ULONG ulIfIndex;
    ULONG ulSetYes;
}DHCP4R_VRF_RELAY_BAK_S;

/* ֧��VRF�������м̵�ַʵʱ���� */
typedef struct tagDHCP4RVrfCfgServerBak
{
    ULONG ulVrfIndex;
    ULONG ulOperate;
    ULONG ulIfIndex;
    ULONG ulServerIP;
}DHCP4R_VRF_CFG_SERVER_BAK_S;

/* ֧��VRF������82��ѡ��ʵʱ���� */
typedef struct tagDHCP4RVrfCfgOption82Bak
{
    ULONG ulVrfIndex;
    ULONG ulOperate;
    ULONG ulIfIndex;
    ULONG ulSubCode;
    ULONG ulSubLen;
    UCHAR aucSubVar[DHCP4R_82_SUB_MAXLEN];
}DHCP4R_VRF_CFG_OPTION82_BAK_S;

/* ����VRF����ʵʱ���� */
typedef struct tagDHCP4RVrfComBak
{
    ULONG ulVrfIndex;
    ULONG ulDHCP4RFwdMode;          /* ��ʵ���м̷�ʽ */
    ULONG ulDHCP4RMaxHops;          /* ��ʵ�� ���RELAY���� */
    UCHAR ucDHCP4RTos;              /* ��ʵ��TOSֵ */
    UCHAR ucpad[3];
}DHCP4R_VRF_COM_BAK_S;

/* ����82ѡ���ģʽʵʱ����*/
typedef struct tagDHCP4RVrfCfgOpt82ModeBak
{
    ULONG ulVrfIndex;
    ULONG ulIfIndex;
    ULONG ulOpt82Mode;
}DHCP4R_VRF_CFG_OPT82MODE_BAK_S;


/* DHCP4R HA����HA������ͷ */
#define SET_HA_HEAD(pucData, ucHAMid, ucBakOperation, ulBakMsgLen)\
{\
    HAMSGHEADER_S* pstHaHdr = (HAMSGHEADER_S *)(pucData);\
    pstHaHdr->usMsgLen = (USHORT)ulBakMsgLen;\
    pstHaHdr->ucModID = (UCHAR)ucHAMid;\
    pstHaHdr->ucOperation = (UCHAR)ucBakOperation;\
}

/* ����DCHP4R HA�ڲ�ģ�鱨�� */
#define SET_DHCP4R_HA_HEAD(pstDhcp4rHeadBak, ulBakType, ulBakLen)\
{\
    (pstDhcp4rHeadBak)->usMsgType = (USHORT)(ulBakType);\
    (pstDhcp4rHeadBak)->usMsgLen  = (USHORT)(ulBakLen);\
}

/* HA������Ϣ����� */
#define DHCP4R_DBG_OUTPUT(szInfo) TCPIP_DebugOutput(szInfo)

/* HA ͷ���� + DHCP4R HA ͷ���� */
#define DHCP4R_HA_HDR_LEN  (sizeof(HAMSGHEADER_S) + sizeof(DHCP4R_HEAD_BAK_S))

#define DHCP4R_HA_DBG_INFO_LEN     512

/* ��82��ѡ��ֵ��8�ֽ�һ���ӡ���ַ��������� */
#define DHCP4R_DBG_82SUB(aucSubVar, ulSubLen, i32Len, szDebugStr, i32DebugStrLen) \
{\
    ULONG j;\
    VOS_DBGASSERT(((ulSubLen) <= DHCP4R_82_SUB_MAXLEN) && ((ulSubLen) > 0));\
    for (j = 0; j < (ulSubLen); j++)\
    {\
        if (0 == (j % 8))\
        {\
            i32Len += TCPIP_SNPRINTF(szDebugStr + i32Len, i32DebugStrLen - i32Len, P0(" "));\
        }\
        if (((aucSubVar)[j] < 127) && ((aucSubVar)[j] > 32)) /* �ɴ�ӡ�ַ���Χ */\
        {\
            i32Len += TCPIP_SNPRINTF(szDebugStr + i32Len, i32DebugStrLen - i32Len, P1("%c", (aucSubVar)[j]));\
        }\
        else\
        {\
            break; /* ��ʾ82ѡ��ʱ����������ɴ�ӡ�ַ��򲻶Ժ����ַ�������ʾ */\
        }\
    }\
}

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _DHCP4R_HA_H_ */

