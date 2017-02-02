/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              mp_api.h
*
*  Project Code: VISPV100R006C02
*   Module Name:   
*  Date Created: 2008-3-8
*        Author: yebo(62004)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-8  yebo(62004)         Create the first version.
*
*******************************************************************************/
#ifndef _MP_API_H_
#define _MP_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN                 47       /* ͬiifnet_inc.h */ 
#endif

#ifndef MP_SUPPORT_MAX_BIND
#define MP_SUPPORT_MAX_BIND                    128       /* ͬiifnet_inc.h */ 
#endif

#ifndef MC_PREFIXE_MAX_STR
#define MC_PREFIXE_MAX_STR                     8       /* ͬiifnet_inc.h */ 
#endif

/* Mp-Group�ӿڰ���Ϣ���ݽṹ */
typedef struct tagMpINFO
{
    /*��ͨ������*/
    ULONG ulFatherIfIndex;
    /*��ͨ������*/
    UCHAR ucFatherName[IF_MAX_INTERFACE_NAME_LEN + 1];
    /*����·��������*/
    ULONG ulSubLink[MP_SUPPORT_MAX_BIND];
    /*�ӽӿ���·��״̬*/
    UCHAR ucSubLinkStatus[MP_SUPPORT_MAX_BIND];
    /*���ð󶨵�����·��*/
    ULONG ulSubLinkNum; 
    /*ʵ�������ϵ�����·��*/
    ULONG ulMpBindNum;
}MPINFO_S;

/* MPͳ����Ϣ�ṹ */
typedef struct tagMPSTATISTIC_S
{
    ULONG ulInOctets;
    ULONG ulInGigaWords;
    ULONG ulOutOctets;
    ULONG ulOutGigaWords;
    ULONG ulInPackets;
    ULONG ulOutPackets;
    
    ULONG ulOutBadPkts;       /* ���Ͷ��������� */
    ULONG ulOutBadOctets;     /* ���Ͷ����ֽ��� */

    ULONG ulLostFragments;          /* ���շ������ķ�Ƭ */
    ULONG ulReorderedPkts;          /* ���շ������鱨���� */
    ULONG ulUnassignedPkts;         /* ���շ���ȴ�����ķ�Ƭ�� */
    ULONG ulInterleavedPkts;        /* ���ͷ���LFI�ķ�Ƭ���� */
    
    ULONG ulWindowMatchPkts;        /* ƥ�����鴰�ڱ��ĸ��� */
    ULONG ulWindowInPkts;           /* �������鴰���б��ĸ��� */
    ULONG ulWindowBehindPkts;       /* ������鴰�ڱ��ĸ��� */
    ULONG ulWindowSurpassPkts;      /* �������鴰�ڱ��ĸ��� */
    /* End of addition */

}MPSTATISTIC_S;

/* ǰ׺ʡ��ӳ��ṹ */
typedef struct tagMCPrefixE
{ 
    UCHAR aucPrefixE[MC_PREFIXE_MAX_STR];   /* ����ǰ׺ʡ���ֶΣ���󳤶�Ϊ8�ֽ�*/
    UCHAR ucIsUsedFlag;                     /* �Ƿ����øõȼ�ǰ׺ʡ�Ա�־ */
    UCHAR ucClass;                          /* ����Class�ȼ� */
    UCHAR ucPrefixELen;                     /* ǰ׺�ֶγ��� */      
    UCHAR ucReserve;                        /* ���� */
} MC_PREFIXE_S;

/*MC���ò������ݽṹ*/
typedef struct tagMC_CONFIG_STRUCT
{
    ULONG ulMc;           /*�Ƿ�ʹ��MC*/
    ULONG ulCode;         /*���ճ������кű�ʶ*/
    ULONG ulClassNum;     /*���ȼ���*/
    ULONG ulPrefixE;      /*�Ƿ�ʹ��ǰ׺ʡ��ѡ��Э��*/
}MC_CONFIG_S;
/* End of addition */

/* MP-QOS�����ķ��ؽ����ö�ٶ��� */
enum enumMpQosCode
{
    MP_QOS_PROCESS_OK = 0,
    MP_QOS_PROCESS_Fail,
    MP_QOS_NOT_PROCESS      /*QOSû�д�����*/
};

/*----------------------------------------------*
 * Error code definition
 *----------------------------------------------*/
/*ע��:
����޸Ĵ����룬��ͬ���޸�mp_sh_err.c�ļ��е�
CHAR *Inf_MP_Err_En[]������Ϣ*/
enum enumMpErrorCode
{
    MP_OK = 0,
    MP_ERR,        
    MP_ERR_RESOURCE_UNAVAILABLE,      /* 2  ��Դ����ʧ�� */
    MP_ERR_NULL_IFNET,                /* 3  IFNETָ��ΪNULL */
    MP_ERR_EXCEED_USER_NUM,           /* 4  �������������û����� */
    MP_ERR_ZERO_USER_NUM,             /* 5  �����û������ѽ�Ϊ0 */
    MP_ERR_NONE_USER_NAME,            /* 6  �޴��û��� */
    MP_ERR_NONE_PPP_INFO,             /* 7  û��PPP���ƿ�ָ�� */
    MP_ERR_NOT_FATHER,                /* 8  ��Ӧͨ���Ǹ�ͨ�� */
    MP_ERR_MP_HEADER,                 /* 9  MP֡ͷ���� */
    MP_ERR_PACKET_LEN,                /* 10 ���ĳ��ȴ��� */
    MP_ERR_ASSEMBLE_FAIL,             /* 11 ������װʧ�� */
    MP_ERR_EXCEED_MULTILINK,          /* 12 MP-group����·�����������÷�Χ */
    MP_ERR_COM_NOT_AVAILABLE,         /* 13 ��������� */

    MP_ERR_VA_NOT_EXIST,              /* 14 VA������ */
    MP_ERR_VT_NUM,                    /* 15 VT�ų�����Χ */
    MP_ERR_NOT_PPP_LINE,              /* 16 ��PPP��· */
    MP_ERR_NOT_MPGROUP_INTF,          /* 17 ��MP-group�ӿ� */
    MP_ERR_NOT_VT_INTF,               /* 18 ��VT�ӿ� */
    MP_ERR_NOT_VT_NOT_MPGROUP_INTF,   /* 19 ��VT�ӿ�Ҳ��MP-group�ӿ� */
    MP_ERR_MPGROUP_CANNT_BIND,        /* 20 Mp-group�ӿڲ��ܰ󶨵�VT��Mp-group */
    MP_ERR_VA_CANNT_BIND_TO_MPGROUP,  /* 21 VA�ӿڲ��ܰ󶨵�Mp-group */
    MP_ERR_BIND_MODE,                 /* 22 ��ģʽֵ������Χ */
    MP_ERR_MAX_BIND_NUM,              /* 23 ���������������÷�Χ */
    MP_ERR_MIN_FRAG_LEN,              /* 24 ��С��Ƭ����ֵ���������÷�Χ */
    MP_ERR_FRAGMENT_DELAY,            /* 25 ��Ƭ��ʱֵ���������÷�Χ */
    MP_ERR_MPGROUP_NAME,              /* 26 Mp-group����ʽ���� */
    MP_ERR_USER_NAME_NULL,            /* 27 �û���Ϊ�� */
    MP_GET_DATA_END,                  /* 28 ��ȡ�����ѵ�ĩβ */

    MP_ERR_INPUT_PARAMETER,           /* 29 ��������Ƿ� */
    MP_ERR_GETCONFIGINFO,             /* 30 ��ȡPPP���ƿ�ʧ�� */
    MP_ERR_EXCEED_MHF_CLASS,          /* 31 MHFѡ���class�ȼ����������÷�Χ */
    MP_ERR_MHF_CODE,                  /* 32 MHFѡ���codeֵ�Ƿ� */
    MP_ERR_PREFIX_ELISION_LENGTH,     /* 33 ǰ׺�ֶγ��ȳ��������÷�Χ */
    MP_ERR_LENGTH_PREFIX_ELISION,     /* 34 ���õĳ����������ֶγ��Ȳ���� */
    MP_ERR_PREFIX_ELISION_FIELD,      /* 35 ǰ׺�ֶηǷ� */
    MP_ERR_PREFIX_ELISION_NUM,        /* 36 ���õ�ǰ׺ʡ��ӳ�����ĿΪ0 */
    MP_ERR_CMD_SWITCH_ERROR,          /* 37 ��������ÿ���ֵ�Ƿ� */
    /* End of addition */

    MP_ERR_PREFIX_ELISION_NOT_EXIST,  /* 38 ǰ׺ʡ�Թ��򲻴��� */
    /* End of addition */
    MP_ERR_INVALID_OPERATION,         /* 39 �Ƿ�����:�����ڸ�ͨ���������ã���ѯ�Ȳ��� */
    MP_ERR_HA_IS_SMOOTHING,           /* 40 HA����ƽ��������ֶ��������� */

    MP_ERR_MPGROUP_NAME_TOOSHORT,     /* 41 �������ֹ��� */
    MP_ERR_MPGROUP_NAME_NOTMATCH,     /* 42 ������"Mp_Group"��ƥ��*/
    MP_ERR_MPGROUP_NAME_NOIF,         /* 43 �Ҳ������ֶ�Ӧ�Ľӿ� */
    MP_ERR_ENABLE,                    /* 44 MPʹ�ܴ��� */
    MP_ERR_ADDTOGROUP,                /* 45 ����MP_GROUP���� */
    MP_ERR_PREFIX_ELISION_NOT_INUSE,  /* 46 Prefixû��ʹ�� */
    MP_ERR_EXCEED_MHF_CLASS_LONG,     /* 47 CODE Ϊ2ʱ������Χ */
    MP_ERR_VT_BIND_TO_ETH,            /* 48 VT�ӿ��Ѿ��󶨵���̫�ӿ���(ʹ��pppoe server����) */
    MP_ERR_VT_EXCEED_MULTILINK,       /* 49 MP-group����·�����������÷�Χ(VT�ӿ�) */
    MP_ERR_VT_NONE_PPP_INFO,          /* 50 û��PPP���ƿ�ָ��(VT�ӿ�) */
    MP_ERR_LOWLIMIT_OVER_MAXBIND,     /* 51 ���õ�������ֵ����mp�������� */
    MP_ERR_COM_NULL,                  /* 52 ���Ϊ�� */

    MP_ERR_NOT_BOUND,                 /* 53 PPP�ӿ���δ�󶨵�MP�� */
    MP_ERR_ANALYSE,                   /* 54 �����ӿ���ʧ�� */
    MP_ERR_INPUT_NULL_POINTER,        /* 55 �����ָ�� */
    MP_ERR_CFGINFO_NOEXIST,           /* 56 �ӿ��϶�Ӧ��������Ϣ������ */
    MP_ERR_PORT_IS_VIRTUAL = 57,      /* 57 ָ���ӿ�Ϊ��ӿ� */

    MP_ERR_LOWLIMIT_OVER_DEFAULTBIND, /* 58 ���õ�������ֵ����Ĭ�������� */
    MP_ERR_CODE_MAX                   /* 59 MP���������ֵ */
};
/*ע��:
����޸Ĵ����룬��ͬ���޸�mp_sh_err.c�ļ��е�
CHAR *Inf_MP_Err_En[]������Ϣ*/


/*���平�Ӻ���*/
typedef ULONG(*MPQOSQueInit_HOOK_FUNC)(ULONG ulIfIndex, BOOL_T bLfiConfigFlag, 
                               UCHAR ucMC, UCHAR ucClassNum);
typedef ULONG(*MPQOSCloneTemplateQue_HOOK_FUNC)(ULONG ulFatherIndex, ULONG ulTemplateIfIndex, 
                                 UCHAR ucMC,UCHAR ucClassNum);
typedef VOID(*MPQOSDelFatherFromQos_HOOK_FUNC)(ULONG ulFatherIndex);
typedef VOID(*MPQOSChange_HOOK_FUNC)( ULONG ulFatherIndex, ULONG *pulLfiConfigFlag);
typedef ULONG(*MPQOSTransmitDone_HOOK_FUNC)(ULONG ulIfIndex, UINTPTR ulPointerToDcb, MBUF_S *pstMBuf);
typedef ULONG(*QOSTransmitDone_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulPointerToDcb, MBUF_S *pstMBuf);
typedef  BOOL_T(*MPQOSIfCanSendPkt_HOOK_FUNC)(ULONG ulIfIndex);
typedef ULONG(*QOSTransmit_HOOK_FUNC)(ULONG ulIfIndex, MBUF_S *pstMBuf, USHORT usProtocol);





/*******************************************************************************
*    Func Name: TCPIP_AddMcPrefix
*  Description: ���MCǰ׺
*        Input: ULONG ulIfIndex: �ӿ�����
*               UCHAR ucClass: ����MC�ȼ�    
*               UCHAR ucLen: ��Ҫʡ�Ե�ǰ׺�ĳ���
*               UCHAR *pszPreInfo: ��Ҫʡ�Ե�ǰ׺�ֶ�
*       Output: 
*       Return: VOS_OK      ���óɹ�                                         
*               ����        ����ʧ��   
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_AddMcPrefix (ULONG ulIfIndex, UCHAR ucClass, UCHAR ucLen, UCHAR *pszPreInfo );
/*******************************************************************************
*    Func Name: TCPIP_AddToMpGroup
*  Description: ���ӿ�ֱ�Ӱ󶨵�MP-group
*        Input: ULONG ulIfIndex: �ӿ�����
*               ULONG ulMpNo: MP-Group��
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_AddToMpGroup(ULONG ulIfIndex, ULONG ulMpNo);
/*******************************************************************************
*    Func Name: TCPIP_ClrMpStatics
*  Description: ���ͳ����Ϣ
*        Input: ULONG ulIfIndex: �ӿ�����
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_ClrMpStatics(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_DelFromMpGroup
*  Description: ȥʹ��MP�Ľӿڡ�
*        Input: ULONG ulIfIndex: �ӿ�����
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DelFromMpGroup(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_DelMcPrefix
*  Description: ɾ��һ��ָ����MC�ȼ����Ӧǰ׺ʡ�Ե�ӳ��  
*        Input: ULONG ulIfIndex: �ӿ�����
*               UCHAR ucClass: ��Ҫ����ĵȼ�
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DelMcPrefix ( ULONG ulIfIndex, UCHAR ucClass );
/*******************************************************************************
*    Func Name: TCPIP_EncapPPP
*  Description: ��װPPP����
*        Input: ULONG ulIfIndex: �ӿ�����
*               MBUF_S *pstMbuf: ����װ����
*               USHORT usProtocol: ��װЭ���
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_EncapPPP (ULONG ulIfIndex, MBUF_S *pstMbuf, USHORT usProtocol);
/*******************************************************************************
*    Func Name: TCPIP_FragmentMP
*  Description: mp���ķ�Ƭ����
*        Input: ULONG ulIfIndex:�ӿ����� 
*               MBUF_S *pstMBuf: ������Ϣ
*               USHORT usProtocol: Э���
*               UCHAR ucClass: MP�ȼ�
*       Output: 0--�ɹ� 
*             : ����ʧ��
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_FragmentMP(ULONG ulIfIndex,  MBUF_S *pstMBuf, USHORT usProtocol, UCHAR ucClass);
/*******************************************************************************
*    Func Name: TCPIP_GetMcConfig
*  Description: ��ȡMC������Ϣ
*        Input: ULONG ulIfIndex: �ӿ�����
*       Output: MC_CONFIG_S* pstMcCfg: MC������Ϣ
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMcConfig(ULONG ulIfIndex,MC_CONFIG_S* pstMcCfg);
/*******************************************************************************
*    Func Name: TCPIP_GetMpInfo
*  Description: ��ȡMP��Ϣ
*        Input: ULONG ulIfIndex:�ӿ����� 
*       Output: MPINFO_S * pstMpInfo: MP��Ϣ���ƿ�
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMpInfo(ULONG ulIfIndex, MPINFO_S * pstMpInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetMpReorderWindowTimes
*  Description: ��ȡMP���鴰�ڵ���ϵ����
*        Input: 
*       Output: ULONG *pulValue: ���ֵ
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMpReorderWindowTimes(ULONG *pulValue);
/*******************************************************************************
*    Func Name: TCPIP_GetMpStatics
*  Description: ��ȡMPͳ����Ϣ
*        Input: ULONG ulIfIndex: �ӿ�����
*               MPSTATISTIC_S * pstStat: ͳ����Ϣ
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMpStatics(ULONG ulIfIndex, MPSTATISTIC_S * pstStat);
/*******************************************************************************
*    Func Name: TCPIP_GetMpUpSublinkLowLimit
*  Description: ��ȡMP��������ֵ��
*        Input: ULONG ulIfIndex: �ӿ�������
*               ULONG *pulValue: Ҫ��ȡ��������ֵָ��
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMpUpSublinkLowLimit (ULONG ulIfIndex, ULONG *pulValue );
/*******************************************************************************
*    Func Name: TCPIP_GetPrefixEInfo
*  Description: ��ȡǰ׺������Ϣ
*        Input: ULONG ulIfIndex: �ӿ�����
*       Output: MC_PREFIXE_S *pstClsPrefix: ǰ׺������Ϣ
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetPrefixEInfo(ULONG ulIfIndex, MC_PREFIXE_S *pstClsPrefix);
/*******************************************************************************
*    Func Name: TCPIP_MPQOS_SonTransmit
*  Description: MPQOSѡ������·���߸���ָ��������·���ͱ��Ľӿ�
*        Input: ULONG ulIfIndex: �ӿ�����
*               ULONG ulPointerToDcb: �ײ���ƿ�ָ�룬�����ָ��Ϊ�գ��ӿ�ָ��ָ��ͨ���ӿڣ�
*                                     ���򣬽ӿ�ָ��ָ��ָ������ͨ���ӿ�
*               MBUF_S * pstMBuf: MBUFָ��
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_MPQOS_SonTransmit(ULONG ulIfIndex, ULONG ulPointerToDcb, MBUF_S * pstMBuf);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncMPQOSChangeHook
*  Description: MP����·��ɾʱ֪ͨMPQOSע��ӿڡ�
*        Input: MPQOSChange_HOOK_FUNC pfHookFunc: ע�ắ��ָ�롣
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncMPQOSChangeHook(MPQOSChange_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncMPQOSCloneTemplateQueHook
*  Description: VT��QOS��Ϣ��VA�ϵĸ���ע��ӿڡ�
*        Input: MPQOSCloneTemplateQue_HOOK_FUNC pfHookFunc: ע�ắ��ָ�롣
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncMPQOSCloneTemplateQueHook(MPQOSCloneTemplateQue_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncMPQOSDelFatherFromQosHook
*  Description: ɾ����ͨ��ʱ��֪ͨQOSע��ӿڡ�
*        Input: MPQOSDelFatherFromQos_HOOK_FUNC pfHookFunc: ע�ắ��ָ�롣
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncMPQOSDelFatherFromQosHook(MPQOSDelFatherFromQos_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncMPQOSIfCanSendPktHook
*  Description: ���ʹ����MPQOS���ж���ͨ���Ƿ�����ܷ��ͱ��ġ�
*        Input: MPQOSIfCanSendPkt_HOOK_FUNC pfHookFunc: ע�ắ��ָ�롣
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncMPQOSIfCanSendPktHook(MPQOSIfCanSendPkt_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncMPQOSQueInitHook
*  Description: MPQOS���г�ʼ������ע��ӿڡ�
*        Input: MPQOSQueInit_HOOK_FUNC pfHookFunc: ע�ắ��ָ�롣
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncMPQOSQueInitHook(MPQOSQueInit_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncMPQOSTransmitDoneHook
*  Description: �ײ��ϱ�MPQOSģ�������֪ͨ���ͱ���ע��ӿڡ�
*        Input: MPQOSTransmitDone_HOOK_FUNC pfHookFunc: ע�ắ��ָ�롣
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncMPQOSTransmitDoneHook(MPQOSTransmitDone_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncQOSTransmitDoneHook
*  Description: �ײ��ϱ�IFNETģ�������֪ͨ���ͱ���ע��ӿڡ�
*        Input: QOSTransmitDone_HOOK_FUNC pfHookFunc: ע�ắ��ָ�롣
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncQOSTransmitDoneHook(QOSTransmitDone_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncQOSTransmitHook
*  Description: ע���IFNETģ������б��ķ��ͺ���ע��ӿڡ�
*        Input: QOSTransmit_HOOK_FUNC pfHookFunc: ע�ắ��ָ�롣
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncQOSTransmitHook(QOSTransmit_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_SetMc
*  Description: ��ָ���ӿ�����ʹ��/ȥʹ��MC���ܡ�
*        Input: ULONG ulIfIndex: �ӿ�������
*               ULONG ulSetYes: ʹ��/ȥʹ�ܱ��(0 ȥʹ�ܣ�1 ʹ��)����������Ƿ���
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMc (ULONG ulIfIndex, ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_SetMcMhf
*  Description: ����MHF(Multilink Header Format ����·ͷ��ʽ)ѡ��Ĳ�����code����/�����кţ���class��MC���ĵȼ�������
*        Input: ULONG ulIfIndex: �ӿ�������
*               UCHAR ucCode: �������кű�ǣ�2 ������ͷ��ʽ��6 ������ͷ��ʽ����
*               UCHAR ucClass: MC�ȼ�����
*               UCHAR ucReset: ����Ĭ��ֵ��ʶ   0:������, 1: ����, ����: �Ƿ���
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMcMhf ( ULONG ulIfIndex, UCHAR ucCode, UCHAR ucClass, UCHAR ucReset );
/*******************************************************************************
*    Func Name: TCPIP_SetMcPrefixENeg
*  Description: ʹ��/ȥʹ��Prefix-Elisionѡ��Э�̡�
*        Input: ULONG ulIfIndex: �ӿ�������
*               ULONG ulSetYes:  ʹ��/ȥʹ�ܱ��(0 ȥʹ�ܣ�1 ʹ��)
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMcPrefixENeg(ULONG ulIfIndex , ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_SetMcSsnhfNeg
*  Description: ʹ��/ȥʹ��Э��SSNHFѡ�
*        Input: ULONG ulIfIndex: �ӿ�������
*               ULONG ulSetYes: ʹ�ܱ�־��1 ʹ�ܣ�0 ȥʹ�ܣ���������Ƿ�
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMcSsnhfNeg ( ULONG ulIfIndex, ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_SetMpDiscriminatorNeg
*  Description: ʹ��MP�ն�������Э��ѡ��ӿڡ�
*        Input: ULONG ulIfIndex: �ӿ�����
*               ULONG ulSetYes: ʹ�ܱ�־��1 ʹ�ܣ�0 ȥʹ�ܣ������������
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpDiscriminatorNeg(ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetMpEndpointDiscriminator
*  Description: ����MP�ն������������ɷ�ʽ��
*        Input: ULONG ulIfIndex: �ӿ�������
*               ULONG ulDiscriminator: ���õ��ն�������,����û����õ�ulDiscriminatorΪ0,���ͬ��ʹ��Ĭ��ֵ,
*                                       ��VISPĬ������(MP��ͨ����)
*               ULONG ulReset: 1,����    0�ָ�Ĭ������(MP��ͨ����)
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpEndpointDiscriminator(ULONG ulIfIndex, ULONG ulDiscriminator, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetMpFragment
*  Description: ����MP��С��Ƭ���ȣ��ù��ܶ�VT/MP-Group�ӿڶ���Ч��
*        Input: ULONG ulIfIndex: �ӿ�������
*               ULONG ulMinFragLen: ��С��Ƭ����ֵ��128��1500�ֽڡ�
*               ULONG ulReset: ���ñ�־��0 ���ã�1 �ָ�����������Ƿ�
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpFragment( ULONG ulIfIndex, ULONG ulMinFragLen, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetMpFragmentDelay
*  Description: ����MP����Ƭʱ�ӡ�
*        Input: ULONG ulIfIndex: �ӿ�������
*               ULONG ulDelay: ʱ��ֵ��1��1000���롣
*               ULONG ulReset: ���ñ�־��0 ���ã�1 �ָ��������������
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpFragmentDelay(ULONG ulIfIndex,ULONG ulDelay, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetMpInterleave
*  Description: ʹ��MP LFI���ܡ�
*        Input: ULONG ulIfIndex: �ӿ�������
*               ULONG ulSetYes: ʹ�ܱ�־��1 ʹ�ܣ�0 ȥʹ�ܣ���������Ƿ���
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpInterleave(ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetMpMaxBind
*  Description: ����MP���������������MP-Group�ӿ���Ч��
*        Input: ULONG ulIfIndex: �ӿ�������
*               ULONG ulMaxBindNum: ������ֵ��1��128��
*               ULONG ulReset: ���ñ�־��0 ���ã�1 �ָ��������������
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpMaxBind(ULONG ulIfIndex, ULONG ulMaxBindNum, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetMpReorderWindow
*  Description: ʹ��/ȥʹ��MP���鴰�ڹ��ܡ�
*        Input: ULONG ulIfIndex: �ӿ�������
*               ULONG ulSetYes: ʹ�ܱ�־��1 ʹ�ܣ�0 ȥʹ�ܣ���������Ƿ�
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpReorderWindow(ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetMpReorderWindowTimes
*  Description: ����MP���鴰�ڵ���ϵ����
*        Input: ULONG ulTimes: ����ϵ��
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpReorderWindowTimes(ULONG ulTimes);
/*******************************************************************************
*    Func Name: TCPIP_SetMpUpSublinkLowLimit
*  Description: ����MP��������ֵ��
*        Input: ULONG ulIfIndex: �ӿ�������
*               ULONG ulValue: ���õ�������ֵ
*       Output: 
*       Return: 0--�ɹ� 
*             : ����ʧ�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetMpUpSublinkLowLimit (ULONG ulIfIndex, ULONG ulValue );
/*******************************************************************************
*    Func Name: TCPIP_ShowMcConfig
*  Description: ��ʾMC������Ϣ
*        Input: CHAR *pszIfName: ����ӿ���
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern VOID  TCPIP_ShowMcConfig(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowMpConfig
*  Description: ��ʾMP�ӿ�������Ϣ
*        Input: CHAR *pszIfName: �ӿ���
*               ULONG ulUsed: 0-���ÿ��ƿ�,1-ʹ�ÿ��ƿ�
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern VOID  TCPIP_ShowMpConfig (CHAR *pszIfName,ULONG ulUsed);
/*******************************************************************************
*    Func Name: TCPIP_ShowMpInfo
*  Description: ��ʾMP��Ϣ,ÿ��ʾ5�νӿ�,�Զ��ͷ�CPU 10ms
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern VOID  TCPIP_ShowMpInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowMpStatistic
*  Description: ��ʾMPͳ����Ϣ
*        Input: CHAR *pName: �ӿ���
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern VOID  TCPIP_ShowMpStatistic(CHAR *pName);

extern VOID  TCPIP_ShowPrefixEInfo(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_MpIsEnableLFI
*  Description: �ж�MP�ӿ��Ƿ�ʹ����LFI
*        Input: ULONG ulIfIndex:MP�ӿ�����
*       Output: ULONG *pulIsEnable:�����Ƿ�ʹ����LFI�ı�־:1-ʹ��;0-δʹ��
*       Return: �ɹ�: MP_OK;����: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-06-18   XiongChangSheng36317    Create
*
*******************************************************************************/
extern ULONG TCPIP_MpIsEnableLFI(ULONG ulIfIndex, ULONG *pulIsEnable);
/*******************************************************************************
*    Func Name: TCPIP_GetMpFatherIfIndex
*  Description: ͨ����ͨ���ӿ�������ȡMP��ͨ���ӿ�����
*        Input: ULONG ulSonIfIndex: ��ͨ���ӿ�����
*       Output: ULONG *pulFatherIfIndex:���淵�صĸ�ͨ���ӿ�����
*       Return: �ɹ�: MP_OK; ����: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-06-18   XiongChangSheng36317    Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMpFatherIfIndex(ULONG ulSonIfIndex, ULONG *pulFatherIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetMpChanNumFromPpp
* Date Created: 2008-11-4
*       Author: wujie(61195)
*  Description: ���������PPP��ͨ���Ų��Ҷ�Ӧ��MP��ͨ����
*        Input: ULONG ulPppChanNum: PPP��ͨ����
*       Output: ULONG *pulMpChanNum: ��Ӧ��MP��ͨ����
*       Return: MP_ERR_COM_NOT_AVAILABLE
*               MP_ERR_RESOURCE_UNAVAILABLE
*               MP_ERR_INPUT_PARAMETER
*               MP_ERR_INPUT_NULL_POINTER
*               MP_ERR_NULL_IFNET
*               MP_ERR_NOT_BOUND
*               MP_ERR_ANALYSE
*               MP_OK
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-11-4   wujie(61195)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMpChanNumFromPpp(ULONG ulPppChanNum, ULONG *pulMpChanNum);


ULONG TCPIP_SetMpDiscReq(ULONG ulIfIndex, ULONG ulSetYes);


ULONG TCPIP_GetMpDiscReq(ULONG ulIfIndex, ULONG *pulSetYes);


ULONG TCPIP_GetMpFatherIfIndexFromCfg(ULONG ulSonIfIndex, ULONG *pulFatherIfIndex);


VOID TCPIP_ShowMpInfoByIf(CHAR* pszIfName);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _MP_API_H_ */

