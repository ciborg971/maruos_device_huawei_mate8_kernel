/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              VISP_IR_ACL.h
*
*  Project Code: VISPV1R6C02
*   Module Name:   
*  Date Created: 2007-07-31
*        Author: luogaowei61496
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-31   luogaowei61496          Create
*
*******************************************************************************/

#ifndef _VISP_IR_ACL_H_
#define _VISP_IR_ACL_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* ��Ź����еĵ�ַ������ */
typedef struct tagIR_ACL_Range32 
{
    ULONG ulAddr;    
    ULONG ulMask;    
} IR_ACL_RANGE32_S;

#ifndef _ACL_ITEM
#define _ACL_ITEM
/* ACL������,�ṩ��IPSECģ����� */
typedef struct tagACL_Item
{
    IR_ACL_RANGE32_S   stSIP;  /* Դ��ַ */
    IR_ACL_RANGE32_S   stDIP;  /* Ŀ�ĵ�ַ */
    UCHAR           ucPID;  /* Э��� */
    UCHAR           ucPadding[3];
    USHORT          usSP;   /* Դ�˿ں� */
    USHORT          usDP;   /* Ŀ�Ķ˿ں� */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG           ulVrfIndex; /* ָ��VRF�����ƥ��������VrfIndex����Ϊ0xFFFFFFFFL,���û��ʹ��VRF����д0 */
    /* End: VISP1.7C03 VRF wangchengyang,2009-01-20 */

    USHORT          usSPEnd; /*Source port End. Port Range will be considered only when this field is non-zero. */        
    USHORT          usDPEnd; /* Dest port End.Port Range will be considered only when this field is non-zero. */        
} ACL_Item, * PACL_Item;
#endif

#ifndef _ACLCONFIG_S
#define _ACLCONFIG_S
/* ACL config information */
typedef struct tagAclConfig
{
    ULONG ulAclNumMin;          /* ��С��������� */
    ULONG ulAclNumMax;          /* ����������� */
    ULONG ulAclBasMinExt;       /* ��С������������� */
    ULONG ulAclBasMaxExt;       /* ��������������� */
    ULONG ulAclAdvMinExt;       /* ��С��չ��������� */
    ULONG ulAclAdvMaxExt;       /* �����չ��������� */
    ULONG ulIpAddrAny;          /* ��ַͨ��� */
    ULONG ulAclDeny;            /* acl denyȡֵ */
    ULONG ulAclPermit;          /* acl permitȡֵ */
    ULONG ulAclNotfound;        /* acl notfoundȡֵ */
} ACLCONFIG_S, *PACLCONFIG_S;
#endif

#pragma    pack( 1 )
typedef struct  tagAclETHERHDR
{
    UCHAR                   ucHdrDstMacAddr[6];     /*Ŀ��physical��ַ*/ 
    UCHAR                   ucHdrSrcMacAddr[6];     /*Դphysical��ַ  */
    USHORT                  usHdrType;              /*Э������   */
}ACL_ETHARP_ETHERHDR_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* ��Ч�������� */
#define ACL_INVALID_SUBNO       0xffffffff

/*
    when delete all rule of given group, ulRuleId is 0;
    when delete one group, ulRuleId is 0;
    when delete all group, ulGroupId and ulRuleId is 0.
 */
#ifndef _PF_ACLREFRESHCALLBACK
#define _PF_ACLREFRESHCALLBACK
typedef VOID (*PF_ACLREFRESHCALLBACK)(ULONG ulGroupId, ULONG ulRuleId, ULONG ulEventType);
#endif

#define ACL_UPDATE_GROUP_DELETE         1
#define ACL_UPDATE_RULE_DELETE          2
#define ACL_UPDATE_RULE_MODIFY          3
#define ACL_UPDATE_RULE_ADD             4
#define ACL_UPDATE_GROUP_DELETE_ALL     5

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif    /* end of _VISP_IR_ACL_H_ */
