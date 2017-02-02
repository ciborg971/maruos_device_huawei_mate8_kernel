

#ifndef _MP_TYPE_H_
#define _MP_TYPE_H_

#ifdef  __cplusplus
extern "C"{
#endif


/* �ն�������Ϣ�ṹ */
typedef struct tagMP_DISCR_INFO
{
    CHAR  ucUserName[MP_USERNAME_LEN + 2];  /* �û���; "+ 2:��Ž�β����4�ֽڶ���" */
    UCHAR ucDiscrLen;                       /* �ն����������� */
    UCHAR ucDiscrClass;                     /* �ն����������� */
    UCHAR ucDiscrAddr[MP_DISCRIMINATOR_MAX_LENGTH]; /* �ն������� */
    ULONG ulBindType;                       /* MP�������� */
} MP_DISCR_INFO_S;

/* ָ����VT�Ľӿ�������Ϣ�ṹ */
typedef struct tagMP_IFINDEX
{
    DLL_NODE_S  stDLLNode;  /* ˫����ڵ� */
    ULONG       ulIfIndex;
}MP_IFINDEX_S;

/* MP����·����ṹ */
typedef struct tagMP_SUBLINKS
{
    DLL_NODE_S  stDLLNode;  /* ˫����ڵ� */
    ULONG       ulIfIndex;
    CHAR        ucIfName[IF_MAX_INTERFACE_NAME_LEN + 1]; /* ԭ48�ú궨���滻 */
}MP_SUBLINKS_S;

/* ���黺�����ڵ�ṹ */
typedef struct tagMP_FRAGMENT
{
    MBUF_S  *pstMbuf;       /* ���ζ�ӦMBUFָ�� */
    ULONG   ulSeqNumber;    /* �������к� */
    UCHAR   ucBEFlag;       /* (B)eginning��(E)nding���ر�־ */
    UCHAR   ucPadding[3]; 
} MP_FRAGMENT_S;

/* MP��ͨ�����ƿ������ṹ */
typedef struct tagMP_SON_INDEX
{
    struct tagMP_SON_INDEX *pstNext;    /* ��һ��ͨ�����ƿ�ָ�� */
    struct tagMP_SON_INDEX *pstPrev;    /* ��һ��ͨ�����ƿ�ָ�� */
    ULONG ulFatherChannelIfIndex;       /* ��ͨ��IFNET���� */
    ULONG ulSonChannelIfIndex;          /* ��ͨ��IFNET���� */
    ULONG ulChannelBandWith;            /* ��ͨ������ */
} MP_SON_INDEX_S;

/* ����HUAWEI-MP-MIB���ʵ�MP��Ϣ�ṹ; "+ 4:��Ž�β����4�ֽڶ���" */
typedef struct tagMPMULTILINKINFO
{
    /* ������; �����Mp-group�ӿڣ�ͳһΪ"Multilink" */
    UCHAR ucHwMpBundleName[MP_USERNAME_LEN + 4];
    ULONG ulHwMpBundledSlot;        /* ��ͨ�����ڵĲۺ� */
    ULONG ulHwMpBundledMemberCnt;   /* ��VT:�ǰ󶨳ɹ�����ͨ���ĸ��� */
                                    /* ��Mp-group:���а󶨹�ϵ����ͨ������ */
    
    /*�����ĸ�����Ϊ��ѯ��ͨ����Ϣ������*/
    ULONG ulHwMpMemberlinkSeqNumber;/* ��ͨ����һ��MP�е���ţ���1��ʼ��� */
    ULONG ulHwMpMemberlinkIfIndex;  /* ��ͨ���ӿ�����; ����󶨵���ͨ��Ϊ����·
                                       ֻ���ڽӿڰ�ȡ�ýӿ�����������Ҫ������� */
    UCHAR ucHwMpMemberlinkDescr[MAX_INTERFACE_DESCRIPTION_LEN + 4]; /*�ӽӿ�����*/
    ULONG ulHwMpMemberlinkMpStatus; /* ��ͨ���󶨳ɹ����ı�־; 0:û�а󶨣�1:�ɹ���*/
    
    ULONG ulBindType;               /* �󶨷�ʽ; �����Mp-group�ӿڰ󶨣���Ϊ0 */
    UCHAR ucHwMpMultilinkDescr[MAX_INTERFACE_DESCRIPTION_LEN + 4];  /* ���ӿ����� */
    ULONG ulHwMpLostFragments;      /* ���շ������ķ�Ƭ */
    ULONG ulHwMpReorderedPkts;      /* ���շ������鱨���� */
    ULONG ulHwMpUnassignedPkts;     /* ���շ���ȴ�����ķ�Ƭ�� */
    ULONG ulHwMpInterleavedPkts;    /* ���ͷ���LFI�ķ�Ƭ���� */
    ULONG ulHwMpRcvdSequence;       /* �������к� */
    ULONG ulHwMpSentSequence;       /* �������к� */
    
}MP_MULTILINK_INFO_S;

/* MP��ͨ�����ƿ�ṹ */
/* ����/����/�������к���������飬�����黺������ʼָ����������飬
 * ���ӱ��˺ͶԶ��Ƿ����MC���ģ�class�ȼ����ֶ�  */
typedef struct tagMP_FATHER
{
    ULONG ulOutSeqNumber[MC_MAX_LSCLASS];   /* ��ǰ�������к� */
    ULONG ulInSeqNumber[MC_MAX_LSCLASS];    /* ��ǰ�������к� */
    ULONG ulVTIfIndex;          /* ��ģ��IFNET���� */
    ULONG ulFatherIndexAddr;    /* ��ͨ��������ַ */
    ULONG ulFragmentBufLen;     /* �����黺�������� */
    ULONG ulLostFragments;      /* �����Ķ��� */
    ULONG ulReordered;          /* ����ı����� */
    ULONG ulUnassigned;         /* �ȴ�����Ķ��� */

    ULONG ulInterleaved;        /* ��·��ֶβ���ı����� */

    ULONG ulFibIndex;           /* ����VLINKʱ���ڽӱ����� */
    MP_FRAGMENT_S *pstMpFrags[MC_MAX_LSCLASS];  /* �����黺������ʼָ�� */

    ULONG ulSeqReordered[MC_MAX_LSCLASS];       /* �����鱨����� */

    MP_SON_INDEX_S *pstCurrentSonChannel;   /* ��ǰ���Է��ͱ��ĵ���ͨ�� */
    MP_SON_INDEX_S *pstFirstSonChannel;     /* ����MP��show������ͷһ����ͨ�� */
    USHORT usMaxMpBindNum;      /* ������·�� */
    USHORT usMpBindNum;         /* �Ѱ󶨵���·�� */

    USHORT usMinFragLen;        /* MP��ʼ�ֶε���С���� */
    UCHAR  bPppReorderWindow;   /* MP�����Ƿ�ʹ�����鹦�ܣ�0:��ʹ�ã�1:ʹ�� */
    UCHAR  bPppInterleave;      /* LFIʹ������� */
    USHORT usMaxFragLFI;        /* LFI����Ƭ����ֵ */
    UCHAR bSheRcvShortHdr ;     /* �Զ˽��ն̵�ַ */
    UCHAR bWeRcvShortHdr ;      /* ���˽��ն̵�ַ */

    UCHAR bSheMultiClass;       /* �Զ˽���MC����*/
    UCHAR ucSheClassNum;        /* �Զ�֧�ֽ��յ�mc�ȼ���*/
    UCHAR bWeMultiClass;        /* ���˽���MC����*/
    UCHAR ucWeClassNum;         /* ����֧�ֽ��յ�mc�ȼ���*/

    USHORT usUpSublinkLowLimit; /* mp�ӿڳ�Ա�˿�UP���ﵽ��ֵ���������Э�� */ 
    UCHAR ucPadding[2];

    ULONG ulWindowMatch;        /* ƥ�����鴰�ڵı��ĸ��� */
    ULONG ulWindowIn;           /* �������鴰���ڱ��ĸ��� */
    ULONG ulWindowBehind;       /* ������鴰�ڵı��ĸ��� */
    ULONG ulWindowSurpass;      /* �������鴰�ڵı��ĸ��� */
    /* End of addition */
} MP_FATHER_S;

/* MP��ͨ����������ṹ */
typedef struct tagMP_FATHER_INDEX
{
    DLL_NODE_S stDLLNode;           /* ˫����ڵ� */
    DLL_S *pstFatherIndexList;      /* ˫����ͷ�ڵ�ָ�� */
    ULONG ulFatherChannelIfIndex;   /* ��ͨ��IFNET���� */
    ULONG ulWaitBindTimerId;        /* �ȴ�����Ӧ��ʱ�� */
    MP_DISCR_INFO_S stDiscrInfo;    /* �ն�������Ϣ */
    ULONG ulBindType;               /* �󶨷�ʽ */
} MP_FATHER_INDEX_S;



/* MPģ����Ϣ�ṹ����SHELLע��ʱ���� */
 typedef struct tagMP_ModInfo
{
    ULONG ulMID_MP;
    ULONG ulQUE_PPP_ASY;
    ULONG ulQUE_PPP_NEGO;
    ULONG ulQUE_PPP_MP;
    ULONG ulQUE_PPP_STAC;
    ULONG ulQUE_IP_INPUT;
    ULONG ulQUE_MPLS_INPUT;
    ULONG ulQUE_ISIS_INPUT;
    ULONG ulQUE_IPX_INPUT;
    ULONG ulQUE_PPPMUX_INPUT;
    ULONG ulQUE_IPV6_INPUT; /* Added by tuyan45114, VISPV1R8C01 for mp-link support ipv6, 2009/3/18 */
    ULONG ulWaitList;
}MP_MOD_INFO_S;

/* MP SHELL��COREע��Ļص��������� */
typedef struct tagMP_SHELL_CALLBACK
{
    VOID(*pfDebugOutString)(CHAR *szString, ULONG ulBufLenth);
    
    ULONG(*pfMPQOS_MpGroupQueInit)(ULONG ulIfIndex, BOOL_T bLfiConfigFlag, 
                                   UCHAR ucMC, UCHAR ucClassNum);
    ULONG(*pfMPQOS_CloneTemplateQue)(ULONG ulFatherIndex, ULONG ulTemplateIfIndex, 
                                     UCHAR ucMC,UCHAR ucClassNum);
    VOID(*pfMPQOS_DelFatherFromQos)(ULONG ulFatherIndex);
    VOID(*pfMPQOS_QosChange)( ULONG ulFatherIndex, ULONG *pulLfiConfigFlag);
    ULONG(*pfMPQOS_QM_TransmitDone)(ULONG ulIfIndex, UINTPTR ulPointerToDcb, MBUF_S *pstMBuf);
    ULONG(*pfQOS_QM_TransmitDone)(ULONG ulIfIndex, UINTPTR ulPointerToDcb, MBUF_S *pstMBuf);
    BOOL_T(*pfQOS_IfCanSendPkt)(ULONG ulIfIndex);
    ULONG(*pfMPQOS_QM_Transmit)(ULONG ulIfIndex, MBUF_S *pstMBuf, USHORT usProtocol);

    ULONG(*pfDDR_GetFatherIfIndex)(IFNET_S*pstSonIf);
    ULONG(*pfDDR_IoCtl)(IFNET_S*pstIfnet,ULONG ulCommand, CHAR *pszPara);
    VOID(*pfDDR_ResetIdleTimeout)(IFNET_S *pstIf);
    
    ULONG(*pfPPP_BAK_RealTime_Send)(VOID *pstInfo, ULONG ulParaType, ULONG ulOpType);
    
    ULONG(*pfMP_EnDropQue)(MBUF_S *pMBuf);
    ULONG(*pfMP_EnQueue)(MBUF_S *pMBuf);
}MP_SHELL_CALLBACK_S;

/* disp mp(show)��������ݽṹ���� */
/* ����/�������к����������*/
typedef struct tagMpDispInfo
{
    ULONG ulFatherIfIndex;      /* ��ͨ������ */
    
    /* ��ͨ�����֣�������Ҫ��Ϊ�˽�����ذ��ϲ��ܸ���VA������ȡVA���ֵ����� */
    UCHAR ucFatherName[IF_MAX_INTERFACE_NAME_LEN + 1];
    ULONG ulSubLink[MP_SUPPORT_MAX_BIND];       /* ����·�������� */
    UCHAR ucSubLinkStatus[MP_SUPPORT_MAX_BIND]; /* �ӽӿ���·��״̬����MP-groupģʽ����Ч */

    /* ��MP-groupģʽ�£�ulSubLinkNum�����õ�����·��������ulSubLink���������; 
       ��VTģʽ�£�ulSubLinkNum�������涨���ulMpBindNum */
    ULONG ulSubLinkNum;         /* ����·�� */    
    ULONG ulFatherSlot;         /* ��ͨ�����ڲۺ� */
    ULONG ulMpBindNum;          /* ������·��, ������Ч������·�� */

    /* ����4����Ϣ��VTģʽ����Ч��MP-group���벻Ҫʹ�ã� */
    UCHAR ucUserName[MP_USERNAME_LEN + 2];      /* �û���; "+ 2:��Ž�β����4�ֽڶ���" */
    UCHAR ucDiscrLen;                           /* �ն����������� */
    UCHAR ucDiscrClass;                         /* �ն����������� */
    UCHAR ucDiscrAddr[MP_DISCRIMINATOR_MAX_LENGTH]; /* �ն������� */

    ULONG ulBindType;           /* ������ */

    ULONG ulLostFragments;      /* ���շ������ķ�Ƭ�� */
    ULONG ulReorderedPkts;      /* ���շ�������ı����� */
    ULONG ulUnassignedPkts;     /* ���շ���ȴ�����ķ�Ƭ�� */
    ULONG ulInterleavedPkts;    /* ���ͷ���LFI�ķ�Ƭ���� */
    ULONG ulInSeqNum[MC_MAX_LSCLASS];           /* �뱨�����к� */
    ULONG ulOutSeqNum[MC_MAX_LSCLASS];          /* ���������к� */

    ULONG ulWindowMatchPkts;        /* ƥ�����鴰�ڱ��ĸ��� */
    ULONG ulWindowInPkts;           /* �������鴰���б��ĸ��� */
    ULONG ulWindowBehindPkts;       /* ������鴰�ڱ��ĸ��� */
    ULONG ulWindowSurpassPkts;      /* �������鴰�ڱ��ĸ��� */
    /* End of addition */
}MP_DISP_INFO_S;

typedef struct tagMpSubIndexInfo
{
    ULONG ulSubLink[MP_SUPPORT_MAX_BIND]; /* �ӽӿ���·�Ľӿ�����*/
    ULONG ulSubLinkNum;                   /* ����·�������� */
}MP_SUB_INDEX_S;

/* MP GROUP��ͨ���ӿ�ָ�������ṹ */
typedef struct tag_Mtl_link
{
    UINTPTR ulIfPointer;
    struct tag_Mtl_link * pNext;
}MTL_LINK_S;

/* MP GROUP�ײ�ʹ�õĿ��ƿ�ṹ */
typedef struct tag_Mtl_Message
{
    COMMON_MSG;
    MTL_LINK_S st_mul_link;
}MLT_MESSAGE_S;


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _MP_TYPE_H_ */
