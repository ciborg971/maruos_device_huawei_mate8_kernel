
#ifndef _IPHC_API_H_
#define _IPHC_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

enum eIPHC_ERR_CODE
{
    IPHC_OK = 0,
    IPHC_ERR,
    IPHC_ERR_COM_NULL,        /* ���Ϊ�� */
    IPHC_ERR_NULL_POINTER,    /* ����ָ��Ϊ�� */
    IPHC_ERR_IFNET_NOEXIST,   /* ��ȡIFNETʧ�� */
    IPHC_ERR_PPPCB_NOEXIST,   /* PPP���ƿ鲻���� */
    IPHC_ERR_CONTEXT_NOEXIST, /* IPHC CONTEXT������ */
    IPHC_ERR_NOTPPPTYPE       /* ��PPP�ӿ� */ 
};

/*******************************************************************************
*    Func Name: TCPIP_DebugIPHCAll
*  Description: ��IPHC������е��Կ��ء�
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
LONG TCPIP_DebugIPHCAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_NoDebugIPHCAll
*  Description: �ر�IPHC������е��Կ��ء�
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
LONG TCPIP_NoDebugIPHCAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_SetIPHCNonTcpDebug
*  Description: ���÷�TCPѹ�����͵��Կ���
*        Input: ULONG ulSetYes: 1-������0-�ر�
*       Output: O--�ɹ�
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
extern ULONG TCPIP_SetIPHCNonTcpDebug(ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetIPHCTcpDebug
*  Description: ����TCPѹ�����͵��Կ���
*        Input: ULONG ulSetYes: 1-������0-�ر�
*       Output: 
*       Return: O--�ɹ�
*             : ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetIPHCTcpDebug(ULONG ulSetYes);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _IPHC_API_H_ */

