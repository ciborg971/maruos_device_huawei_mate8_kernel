
 
#ifdef __cplusplus
extern "C" {
#endif


#ifndef _AM4_ADDR_H_
#define _AM4_ADDR_H_


#ifndef MIN
#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#endif


/* ��Ҫ�������ذ���ӿڰ�֪ͨʱ����Ϊ��־�е�һλ֪ͨ��
 * �¼����������ַ��־�ظ�������Ϊ���õ�ַ��ipif_ulAddrFlag��
 */
#define IP_ADD       0x0100   /* ��ӵ�ַ */
#define IP_DEL       0x0200   /* ɾ����ַ */
#define IP_CHA       0x0400   /* �ı��ַ */
#define IP_OTH       0x0800   /* ��֪ͨ��·�� */
#define IP_INVALID   0x1000   /* ��PPP�������ģ���ⲻ�Ϸ� */

/* ���ӵ�ַʱ�Ĳ�����־ */
#define LINKTAIL      1     /* ����β���� */
#define CHECKCONFLICT 2     /* ����ͻ */
#define INVALID       4     /* ��ַ��Ч�Լ�� */
#define PPP           8     /* PPP negotiated */
#define IP_DELSEC     512   /* ɾ���ӵ�ַ,֪ͨEthɾ��ARP���� */

/* ֪ͨ��ַ��������ʱʹ�õı�־λ,������Щ��־λ�������ⲿ������֪ͨ */
#define BEFORE_DEL    0x0010
#define AFTER_DEL     0x0020
#define BEFORE_ADD    0x0040
#define AFTER_ADD     0x0080
#define IP_PRIMARY    0x0100
#define IP_SECONDARY  0x0200


/* VRF's address tree check operation flag */
#define IP_PPP_FLAG   0x01

#define ARP_PROXY_SAMESUBNET   2 

#define NO_INCLUDE    0x02
#define ANY_INCLUDE   0x04
#define IP_BORROW_FLAG   0x08 /* �ñ�Ǳ�ʾ������õ�ַ���г�ͻ��� */

#define DHCP4C_CFG_FLAG   0x100  /*���DHCP4C���Ի�ȡ��ͬ�����εĵ�ַ*/

typedef struct tagIPInsertPos
{
    IP_radix_node *pstNode;
    USHORT usOpCode;
    USHORT usDiffBitLen;
} IPInsertPos;


typedef struct tagIPCMDMSG
{
    ULONG   ipif_ulIndexIf;     /* �ӿ����� */
    ULONG   ipif_ulFlags;       /* �ӿڱ�־λ���㲥���ԡ�NBMA����IFF_BROADCAST��IFF_NBMA*/
    ULONG   ipif_ulAddrFlag;    /* �ӿڵ�ַ�����ԣ���ַЭ�̡����õ�ַ�����Լ��ĵ�ַ��IFF_NEGOTIATE,*/
    ULONG   ipif_ulBorrowIfIndex;
    CHAR    ipif_szIfName[ IF_MAX_INTERFACE_NAME_LEN+1];   /*  �ӿ���  */
    ULONG   ulNum;
    ULONG   ulMultiNum;
    
    ULONG       ulIcmpRedirect; 
    ULONG       ulIcmpHostUnreach;

    IPIFADDR_S  ipif_stIpIfAddrList[MAXADDR_ON_ONEIF]; /* �ӿڵĵ�����ַ����˫������ */
    IPMULTI_S   ipif_stIPIfMultiList[1];    /*�ӿڵĶಥ��ַ��:  ѭ������*/
}IP_IPCMDMSG_S;



/* �������ӿڵĵ�ַ */
#define V_LIST_EMPTY(ptr)   ((ptr)->ia_v_pNext == (ptr))
#define V_LIST_FIRST(ptr)   ((ptr)->ia_v_pNext)
#define V_LIST_NEXT(ptr)    ((ptr)->ia_v_pNext)
#define V_LIST_LAST(ptr)    ((ptr)->ia_v_pPrev)
#define V_LIST_SCAN(pHead, pNode) \
    for ((pNode) = V_LIST_FIRST((pHead)); (pNode) != (pHead); (pNode) = V_LIST_NEXT((pNode)))

/* ����ȫ�ֵĵ�ַ */
#define H_LIST_EMPTY(ptr)   ((ptr)->ia_h_pNext == (ptr))
#define H_LIST_FIRST(ptr)   ((ptr)->ia_h_pNext)
#define H_LIST_NEXT(ptr)    ((ptr)->ia_h_pNext)
#define H_LIST_LAST(ptr)    ((ptr)->ia_h_pPrev)
#define H_LIST_SCAN(pHead, pNode) \
    for ((pNode) = H_LIST_FIRST((pHead)); (pNode) != (pHead); (pNode) = H_LIST_NEXT((pNode)))


/*
 * changed for permitting address overlap 2002-10-30 by mayun & yuyong
 * now use radix tree
 */
extern ULONG IP_InsertTree(IPIFNET_S *pstIpIf, IPIFADDR_S *pstAddr);  
extern ULONG IP_DeleteTree(IPIFADDR_S *pstAddr);
extern ULONG IP_CheckOverlap(IPIFNET_S *pstIpIf, ULONG ulIpAddr, ULONG ulMask, ULONG ulFlag);

IPMULTI_S *IPIF_AddMulti(INADDR_S *pstIn, IPIFNET_S *pstIpIf);
LONG IPIF_DelMulti( INADDR_S *pstInAddr, IPIFNET_S *pstIpIf );
ULONG IP_GetNumOfLend( IPIFNET_S *pstCurIf );
ULONG IP_Del_AllOfIfIpAddr( IPIFNET_S *pstIpIf, UCHAR ucVrrpFlag );
ULONG IP_DelAll(IPIFNET_S *pstIpIf);
VOID IP_NotifyWithAddrChange(ULONG ulIfIndex, ULONG ulIpAddrFlag,  ULONG ulActionTime );
IPIFADDR_S * IP_FindAddrWithMask( ULONG ulIpAddr, ULONG ulIpMask ,IPIFNET_S *pstIpIf );
ULONG IP_Del_Addr( ULONG ulIpAddr, ULONG  ulIpMask, IFNET_S *pstIfNet );
IPIFADDR_S * IP_Find_SameIpAddr( ULONG ulIpAddr, IPIFNET_S *pstIpIf );
ULONG IP_Get_First_IpAddr(IPIFNET_S *pstIpIf, ULONG *pulFirstAddr, ULONG *pulFirstMask);
/*Begin BC3D01271 liangjicheng 2009-03-17*/
ULONG IP_Get_Second_IpAddr( IPIFNET_S *pstIpIf, ULONG *pulSecondAddr, ULONG *pulSecondMask );
/*End BC3D01271 liangjicheng 2009-03-17*/
ULONG IP_Add_Addr(ULONG ulIpAddr, ULONG ulIpMask, ULONG ulIpDstAddr, IFNET_S *pstIfNet, ULONG ulAddrFlag);
ULONG IP_Del_AllOfIfIpMultiAddr( IPIFNET_S *pstIpIf );

ULONG IP_AM4_AddBorrowOtherAddr(IPIFNET_S* pstMyIpIf, IPIFNET_S*pstLendIpIf);
ULONG IP_AM4_RemoveBorrowOtherAddr(IPIFNET_S* pstMyIpIf);

VOID DealWithOthersBorrowMyIPaddr(IPIFNET_S *pstCurIf, ULONG ulCmd, UCHAR ucNofityFlag);
ULONG IP_ConflictIpAddressSpecial(ULONG ulIfIndex, ULONG ulAddr, ULONG ulMask);
ULONG IP_ConflictIpAddressSpecial_PT(ULONG ulIfIndex, ULONG ulAddr, ULONG ulMask);

ULONG IP_NotifyRmAddrChange(PIPIFNET_S pstIpIf, ULONG ulIpAddr, ULONG ulIpMask, ULONG ulMainIpAddr, ULONG ulAction);
VOID DealWithOthersBorrowMyIPaddr_PT(IPIFNET_S *pstCurIf, ULONG ulCmd);
IPIFADDR_S *IP_GetBestIpAddrByVrf(SOCKADDRIN_S *pstSockInAddr, ULONG ulVrfIndex);
IPIFADDR_S *IP_GetBestIpIfForDontroute(SOCKADDRIN_S *pstSockInAddr, ULONG ulVrfIndex);
ULONG IP_SetIpConflictFlag(IFNET_S* pIf, ULONG ulIpAddr);
ULONG IP_ClearIpConflictFlag(IFNET_S* pIf, ULONG ulIpAddr);
BOOL_T IP_AM4_SupportSameSubAddr();

#endif  /* end of _AM4_ADDR_H_ */ 

#ifdef __cplusplus
}
#endif/* end of __cplusplus */
