/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_l3vpn.h
*
* Project Code: VISPV100R005
*  Module Name: AM4  
* Date Created: 2006-01-04
*       Author: Li LiXiang
*  Description: ������AM4����VRF��صĺ���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                ���ݱ�̹淶�����ļ����й淶������ 
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _AM4_L3VPN_H_
#define _AM4_L3VPN_H_


/*VISP�ڲ�0��ʾ����������PTN��Ʒ1��ʾ������DCNʹ��VISP FIB,��ʹ��VISP ����FIB*/
#define IP_L3VPN_VRF_INDEX_PUBLIC               0
/*OSP�ӿ���DCN �ӿڣ�����DCNʹ��VISP FIB,����,DCN��Socket����ʵ����Ϊ0xABCDABCD*/
#define IP_L3VPN_VRF_RESERVE_DCN              0xABCDABCD
#define IP_L3VPN_VRF_INDEX_MIN                  1
#define IP_L3VPN_VRF_DEFAULT_POOL_SIZE                  1


#define IP_L3VPN_VRF_EVENT_CREATE               1
#define IP_L3VPN_VRF_EVENT_DELETE               2
#define IP_L3VPN_VRF_EVENT_INTFCHANGE           4

/* #define IP_L3VPN_VRF_RESERVE_DCN              0xABCDABCD */

typedef struct tagIP_L3VPN_IFCHANGE
{
    USHORT usOldVrfId;
    USHORT usNewVrfId;
    ULONG  ulIfIndex;
}IP_L3VPN_IFCHANGE_S;


#endif  /* end of _AM4_L3VPN_H_ */ 

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

