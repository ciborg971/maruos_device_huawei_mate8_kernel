typedef struct tagBFD_NEGOFAIL_S
{
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szIfName[BFD_MAX_INTF_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr[4]; 
    ULONG ulPeerAddr[4]; 
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1]; 
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    ULONG ulProtocol;      /* IPv6/IPv4��ʶ:0-IPv4,1-IPv6 */
}BFD_NEGOFAIL_S;

/* Bfd6 ȫ��socket�ṹ */
typedef struct tagBFD6_SOCK_INFO_S
{
    LONG lMutiRcv;    /* �������� */
    LONG lOneRcv;     /* �������� */
    LONG lSnd;        /* ���ķ��� */
}BFD6_SOCK_INFO_S;

/* �ر�socket */
#define BFD6_CLOSE_SOCKET(lSocktId)\
{\
    if (-1 != lSocktId)\
    {\
        (VOID)close(lSocktId);\
        lSocktId = -1;\
    }\
}


ULONG BFD6_GetVrfIndexByName(CHAR *pszVrfName,ULONG *pulVrfIndex);

ULONG BFD6_GetVrfNameByIndex(CHAR *pszVrfName,ULONG ulVrfIndex);

CHAR * BFD6_Inet_ntop6(const CHAR *pSrcAddr,CHAR *pszDstAddr, ULONG ulAddrLen);

ULONG BFD6_Shell_Init();

ULONG BFD6_Shell_Send (UCHAR* pIpPacket, BFD_PKTINFO_S * pstSndPktInfo);
ULONG BFD6_Shell_Init_Socket();
VOID BFD6_Shell_Close_GlobalSocket();

extern ULONG g_ulBfd6EnableFlag;
/* wangjiaqi modify for ipv6 bfd 20131125 begin */
/*******************************************************************************
*    Func Name: BFD6_GetRtmInstByIndex
* Date Created: 2013-11-25
*       Author: Wangchengyang
*  Description: ͨ��VRF ID��ȡ·�ɹ���ʵ����
*        Input: ulVrfIndex :VRF ID
*       Output: pulInst:ʵ����
*       Return: 
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_GetRtmInstByIndex(ULONG ulVrfIndex,ULONG *pulInst);

/*******************************************************************************
*    Func Name: BFD6_GetVrfIndexByIfIndex
* Date Created: 2013-11-25
*       Author: wangjiaqi
*  Description: ͨ���ӿ�������ȡ��VRF6 ����
*        Input: ulIfIndex  :�ӿ�����
*       Output: pulVrfIndex:VRF ����
*       Return: 
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_GetVrfIndexByIfIndex(ULONG ulIfIndex,ULONG *pulVrfIndex);
/* wangjiaqi modify for ipv6 bfd end */

/*******************************************************************************
*    Func Name: BFD6_Shell_CreateCheck
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: �趨һ��BFD6�Ự�Ļ�������
*               ����Ҫ��������Ч�ԣ�
*        Input: pstSession            ����ɾ���ĻỰ��Ϣ(��ԭ�ṹ���岻ͬ,��������Ѿ�����ַתΪ������)
*               ULONG ulOutIfIndex    �����ỰʱΪ���ӿ�����������ʱֵΪ0��
*               ULONG ulVrfIndex      VRF����
*
*       Output:
*       Return: �ɹ�����      BFD_OK
*               ʧ�ܷ���      ������
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8        wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
struct tagBFD6_SESSION_ADD_DEL_S;
ULONG BFD6_Shell_CreateCheck(struct tagBFD6_SESSION_ADD_DEL_S *pstSession, ULONG ulOutIfIndex,ULONG ulVrfIndex);

ULONG BFD6_CheckVRFValid(ULONG ulIfIndex, ULONG ulVRFIndex);



