

/*
 * �뽫�����ģ��껻�ɸ�ͷ�ļ�����ģ���ģ��ꡣ
 * ���磬������·��Э��ģ��PPP��ͷ�ļ�ppp_var.h��Ӧ�ø�Ϊ��
 *
 *    #if( VRP_MODULE_LINK_PPP == VRP_YES )
 *
 * ���øú��Ŀ����Ϊ��ͨ���ֹ������ڱ���ʱ�ü�VRP�������ÿ���ļ�������
 * ���е���Щģ��궼��VRP3.0�����ù���Ա������ͷ�ļ�vrpcfg.h�ж��塣
 */

#ifndef _IF_CFG_H_
#define _IF_CFG_H_
/*
 * �ú�Ķ��巽ʽΪ��"_" + "ȫ����д���ļ���" + "_" + "H" + "_"
 * ���磬������·��Э��ģ��PPP��ͷ�ļ�ppp_var.h��Ӧ�ö���Ϊ��
 *
 *#ifndef _PPP_VAR_H_
 *#define _PPP_VAR_H_
 *
 * ����ú��Ŀ����ȥ���ظ�����һ��ͷ�ļ��Ŀ�����
 */

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct tagIFGetVAInfo        /* For Get VA Info. */
{
    ULONG  ulLanguage;
    ULONG  ulVTNo;
    ULONG  ulVANo;
    CHAR   szUserName[40];
    ULONG ulCfgVTNo;
    ULONG ulCfgVANo;
    ULONG ulCfgIp;
    ULONG  ulInfoSize;
}IF_GetVAInfo_S;

/************************************************************************************
���нӿ����Ƽ�顢����������Ĺ��Ӻ���                                              *
                                                                                    *
��������:  ���ò�ѯ������                                                           *
             �����ݲ���ulFuncת����Ӧ�Ľӿ����͡���š����Ƶļ���������           *
��������ֵ:  ��ת��ļ����������ķ���ֵ(�μ�IF_CheckIfType��IF_HelpIfType�Ⱥ���)  *
*************************************************************************************/
ULONG IF_HookForQuery(ULONG ulFunc, CHAR * szType , CHAR * szInput , ULONG pHelpVec) ;
/************************************************************************************/

ULONG IF_GetConfigMTU(IFNET_S* pIf);
ULONG IF_GetMTU(IFNET_S* pIf);
VOID IF_GetDefaultEthMac(UCHAR *szMac);

ULONG IF_VT_FindVA( IF_GetVAInfo_S *pVAInfo); 

ULONG IF_SetMTU(IFNET_S* , ULONG ulMTU ) ;
ULONG IF_SetVTMTU(IFNET_S* pIf, ULONG ulMTU);
ULONG IF_SetDescript(IFNET_S* pIf, CHAR * pDescript);
ULONG IF_SetKeepAliveValue( IFNET_S* pIf, ULONG ulValue );
ULONG IF_SetBandWidthValue(ULONG ulSlot, IFNET_S* pIf, ULONG ulValue);

VOID IF_SelectMtu(IFNET_S * , ULONG * , ULONG * ) ;

/*added by fujibin for simple name D18451*/
ULONG IF_GetSimpleName( CHAR *szIfName, CHAR *szSimpleName );


ULONG IF_GetIPSecSaEntryHead(ULONG ulIfIndex, VOID **ppstHeadTemp);
ULONG IF_SetIPSecSaEntryHead(ULONG  ulIfIndex, ULONG ulTdbEntryHead);
ULONG IF_GetPortType(IFNET_S * pIf, ULONG *pulPortType );
ULONG IF_GetPhyType(IFNET_S * pIf, ULONG *pulPhyType );
BOOL_T IF_IsValidIfIndex(ULONG ulIfIndex);
CHAR *IF_GetIfNamebyIndex(ULONG ulIfIndex);
ULONG IF_GetPortTypeByIndex(ULONG ulIfIndex);
ULONG IF_GetMTUByIndex(ULONG ulIfIndex);

#if (TCPIP_MODULE_MINI == VRP_YES)

ULONG IF_Addr_IsInvalidIP4Address(ULONG ulV4Addr);
ULONG IF_IsInvalidIP6Address(IN6ADDR_S  *pstIn6Addr,ULONG ulJudgeFlg);
ULONG IF_CheckAddrWithLocal(IN6ADDR_S  *pstIn6Addr,ULONG ulIfIndex);
ULONG IF_GetMatchIfIndex(ULONG *pulIndex);
ULONG IF_SelectSourceAddr(IN6ADDR_S *pstIp6DestAddr,IN6ADDR_S *pstSrcAddr, ULONG ulIfIndex);
ULONG IF_HaveAddrCheck(ULONG ulIfIndex,ULONG ulFlag);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _IF_CFG_H_ */

