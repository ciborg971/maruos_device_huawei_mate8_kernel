/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              VISP_IR_AC6L.h
*
*  Project Code: VISPV1R8C03
*   Module Name:   
*  Date Created: 2010-01-27
*        Author: luogaowei61496
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2010-01-27   luogaowei61496          Create
*
*******************************************************************************/

#ifndef _VISP_IR_ACL6_H_
#define _VISP_IR_ACL6_H_

#ifdef  __cplusplus
extern "C"{
#endif


#ifndef ACL6_IPV6_ADDR_LEN
#define ACL6_IPV6_ADDR_LEN   16
#endif

#ifndef _IR_ACL6_IP6ADDR_S
#define _IR_ACL6_IP6ADDR_S
typedef struct tagIR_Acl6Ip6Addr 
{
    UCHAR ucAddr[ACL6_IPV6_ADDR_LEN];    /*IPv6��ַ��Ϣ��������*/
    ULONG ulMaskLen;     /*IPv6��ַ���볤��*/
} IR_ACL6_IP6ADDR_S;
#endif

#ifndef _ACL6_ITEM
#define _ACL6_ITEM
typedef struct tagACL6_Item
{
    IR_ACL6_IP6ADDR_S stSrcIp;/* Դ��ַ */
    IR_ACL6_IP6ADDR_S stDstIp;/* Ŀ�ĵ�ַ */
    UCHAR           ucPID;  /* Э��� */
    UCHAR           ucPadding[3];
    USHORT          usSP;   /* Դ�˿ںţ������� */
    USHORT          usEndSP;/* Դ�˿ںŽ���ֵ�������� */
    USHORT          usDP;   /* Ŀ�Ķ˿ںţ������� */
    USHORT          usEndDP;/* Ŀ�Ķ˿ںŽ���ֵ�������� */
    ULONG           ulVrfIndex; /* ָ��VRF�����ƥ��������VrfIndex����Ϊ0xFFFFFFFFL,���û��ʹ��VRF����д0 */
} ACL6_Item, * PACL6_Item;

#endif

#ifndef _ACL6CONFIG_S
#define _ACL6CONFIG_S
typedef struct tagAcl6Config
{
    ULONG ulAclNumMin;          /* ��С��������� */
    ULONG ulAclNumMax;          /* ����������� */
    ULONG ulAclBasMinExt;       /* ��С������������� */
    ULONG ulAclBasMaxExt;       /* ��������������� */
    ULONG ulAclAdvMinExt;       /* ��С��չ��������� */
    ULONG ulAclAdvMaxExt;       /* �����չ��������� */
    ULONG ulIpAddrAny[LEN_4];          /* ��ַͨ��� */
    ULONG ulAclDeny;            /* acl denyȡֵ */
    ULONG ulAclPermit;          /* acl permitȡֵ */
    ULONG ulAclNotfound;        /* acl notfoundȡֵ */
} ACL6CONFIG_S, *PACL6CONFIG_S;
#endif


#ifndef _PF_ACL6_REFRESHCALLBACK
#define _PF_ACL6_REFRESHCALLBACK
/*zero means process all node*/
typedef VOID (*PF_ACL6_REFRESHCALLBACK)(ULONG ulGroupId, ULONG ulRuleId, ULONG ulEventType);
#endif

#define ACL6_UPDATE_GROUP_DELETE         1
#define ACL6_UPDATE_RULE_DELETE          2
#define ACL6_UPDATE_RULE_MODIFY          3
#define ACL6_UPDATE_RULE_ADD             4
#define ACL6_UPDATE_GROUP_DELETE_ALL     5

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif    /* end of _VISP_IR_ACL_H_ */

