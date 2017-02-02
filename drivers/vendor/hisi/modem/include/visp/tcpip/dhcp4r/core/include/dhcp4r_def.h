/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4r_def.h
*
*  Project Code: VISPV1R6
*   Module Name: DHCP4R  
*  Date Created: 2007-7-11
*        Author: LY(57500)
*   Description: DHCP4Rģ��ĺ��ö�ٶ���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-7-11  LY(57500)     Create the first version.
*
*******************************************************************************/

#ifndef _DHCP4R_DEF_H_
#define _DHCP4R_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif

/* ʹ������ģʽ: 0 - �ӿ�ģʽ��1 - ȫ��ģʽ */
#define DHCP4R_ENABLE_INTERFACE     0
#define DHCP4R_ENABLE_GLOBAL        1
#define DHCP4R_ENABLE_AUTO           2

/* ʹ��ȥʹ��   */
#define DHCP4R_DISABLE              0
#define DHCP4R_ENABLE               1

/* 82ѡ����غ궨�� */
#define DHCP4R_OPTION_82            82
#define DHCP4R_82_SUB_MINLEN        1       /* ��ѡ����С����   */
#define DHCP4R_82_CIRCUIT_ID        0x1     /* ��ѡ��1 CODE     */
#define DHCP4R_82_REMOTE_ID         0x2     /* ��ѡ��2 CODE     */

/* �������ɵ�82ѡ�����󳤶�; ÿ����ѡ����1�ֽ�code��1�ֽ�Len,82ѡ��������Ҫ1�ֽ�code��1�ֽ�Len */
#define DHCP4R_82_TOTAL_LEN  (DHCP4R_82_SUB_NUM * (DHCP4R_82_SUB_MAXLEN + 2) + 2)

/* ����м��������� */
#define DHCP4R_HOPS_MAX             16
/* �м�ģʽ */
#define DHCP4R_FORWORD_CYCLE        0x0     /* �ֵ���ʽ */
#define DHCP4R_FORWORD_BROADCAST    0x1     /* �㲥��ʽ */

/* ����������Ϣ(���hops,�м̷�ʽ,TOS)��Ĭ��ֵ */
#define DHCP4R_HOPS_DEFAULT         16
#define DHCP4R_FORWORD_DEFAULT      DHCP4R_FORWORD_CYCLE
#define DHCP4R_TOS_DEFAULT          0

/* relay���ñ�־    */
#define DHCP4R_FLAG_ENABLE          0x01    /* ��ʹ��           */
#define DHCP4R_FLAG_SERVER          0x02    /* �������м̵�ַ   */
#define DHCP4R_FLAG_OPTION82        0x04    /* ������82ѡ��     */
#define DHCP4R_FLAG_OPT82MODE       0x08    /* ������82ѡ���ģʽ */
/* ����������ñ�� */
#define DHCP4R_SET_FLAG(SetFlag, FlagMask)      ((SetFlag) |= (FlagMask))
#define DHCP4R_CLEAR_FLAG(SetFlag, FlagMask)    ((SetFlag) &= ~(FlagMask))

/* relay���շ��ͱ��Ļ��������� */
#define DHCP4R_UDPBUF_MAXLEN        2048

/* debug���� */
#define DHCP4R_DEBUG_PAKCET         0x1     /* packet���Կ���   */
#define DHCP4R_DEBUG_ERROR          0x2     /* error���Կ���    */
#define DHCP4R_DEBUG_ALL            0x3     /* ǰ���߶���     */

/* DHCP4Rģ���¼�λ */
/* ������Ϣʹ��ͬһ��������Ϣ���к���ͬ�¼�����ͨ����ͬ����Ϣ����������  */
#define DHCP4R_EV_CNTRL             0x1     /* ����ģ��֪ͨDHCP4R�¼�   */

#define DHCP4R_MSG_IFDEL            0x1     /* ��̫ģ��ɾ���ӿ���Ϣ     */
#define DHCP4R_MSG_CRTSKT           0x2     /* ����relay socket��Ϣ     */
#define DHCP4R_MSG_VRFDEL           0x3     /* VRFɾ����Ϣ              */
#define DHCP4R_MSG_CLSSKT           0x4     /* ɾ��relay socket��Ϣ     */



/* �û����ýӿ��д���Ľӿ�����ֵ�ڵ�ǰ����ģʽ���Ƿ���Ч
 * �ӿ�����ģʽ(0),�ӿ��������� ��0
 * ȫ������ģʽ(1),�ӿ��������� Ϊ0
 * ��ֵΪ1��ʾ��������������ģʽ��ͻ
 */
#define DHCP4R_MODE_NO_MATCH(mode, ifIndex)  (((!(mode))&&(!(ifIndex))) || ((mode)&&(ifIndex)))

/* �����ڽ��DHCP����ʱ���ָ������Ƿ�Խ�磬ÿ�ζ�ȡ����ǰ��Ҫ���� */
#define  DHCP4R_MSG_BOUNDCHECK(pucOptRead, pucStart, length) \
    (((UINTPTR)(pucOptRead) > (UINTPTR)(pucStart) + (length)) ? (VOS_ERR) : (VOS_OK))

/* ����dhcp���������� */
enum enDHCPTxRx
{
    DHCP_FROM_CLIENT = 1,   /* 1 ��client���� */
    DHCP_TO_CLIENT,         /* 2 ��client���� */
    DHCP_FROM_SERVER,       /* 3 ��server���� */
    DHCP_TO_SERVER,         /* 4 ��server���� */
    DHCP_TO_RELAY,         /* 5 ����Relay */
};

/* �ж��Ƿ�Ƿ�dhcp��Ϣ���� */
#define DHCP_IS_BADTYPE(msgType) (((msgType) < DHCP4C_DHCPDISCOVER) || ((msgType) > DHCP4C_DHCPINFORM))

/* ����Ƿ�dhcp��Ϣ���ͺ� */
#define DHCP_BAD_MSG    0

/* ���屨��ͳ������,Ϊ����DHCPC�����������ﶨ���16��ʼ */
enum enDHCPERRPKTTYPE
{
    /* ����ulRxServerPkt����ͳ������0x10 */
    DHCP4R_RXS_MSG = 0x10,
    /* ����ulTxServerPkt����ͳ������0x11 */
    DHCP4R_TXS_MSG,
    /* ����ulRxClientPkt����ͳ������0x12 */
    DHCP4R_RXC_MSG,
    /* ����ulTxClientUnicast����ͳ������0x13 */
    DHCP4R_TXCU_MSG,
    /* ����ulTxClientBroadcast����ͳ������0x14 */
    DHCP4R_TXCB_MSG,
    /* ����ulTxClientPkt����ͳ������0x15 */
    DHCP4R_TXC_MSG,
    /* ����ulBorrowDropPkt����ͳ������0x16 */
    DHCP4R_BD_MSG,
    /* ����ulAdd82TooLongPkt����ͳ������0x17 */
    DHCP4R_ATL_MSG,
    /* �������Relay����ͳ������0x18 */
    DHCP4R_TXR_MSG,
};

/* �����ֽ���, DHCP OPTION��ʼ���ĸ��ֽ�Ϊħ����, ����У�� */
#define DHCP4R_MAGICCOOKIE  0x63825363  

/* DHCP4Rģ��ʹ�õ�SIDͳһ�ڴ˶��� */

#define SID_COMP_DHCP4R_DLL_S      1  /* DLL_S */
#define SID_COMP_DHCP4R_CFG_S      2  /* DHCP4R_CFG_NODE_S */
#define SID_COMP_DHCP4R_DBG_S      3  /* DHCP4R_DEBUG_NODE_S */
    
/* end of SID */

/* ���幫��VRF������ΪIP_L3VPN_VRF_INDEX_PUBLIC*/
#define DHCP4R_VRF_INDEX_PUBLIC IP_L3VPN_VRF_INDEX_PUBLIC
/* ��������VRF������ΪIP_L3VPN_VRF_RESERVE_DCN*/
#define DHCP4R_VRF_INDEX_RESERVE_DCN IP_L3VPN_VRF_RESERVE_DCN

/* �������VRF������ΪIP_L3VPN_VRF_INDEX_MAX_DEFAULT*/
#define DHCP4R_VRF_INDEX_MIN           1
#define DHCP4R_VRF_INDEX_MAX_DEFAULT   1
#define DHCP4R_VRF_INDEX_MAX g_ulDhcp4rMaxVrfIndex
#define DHCP4R_VRF_POOL_SIZE (g_ulDhcp4rMaxVrfIndex + 1)


#define DHCP4R_VRF_INVALIDVRF(ulVrfIndex) ((ulVrfIndex) > DHCP4R_VRF_INDEX_MAX)

#define DHCP4R_PACKET_PRO_COUNT 40
#define DHCP4R_PACKET_MAX_PRO_COUNT 100
#define DHCP4R_DELAY_TIME 40
#define DHCP4R_MAX_DELAY_TIME 100

#ifdef __cplusplus
}
#endif      /* end of _cplusplus        */

#endif      /* end of _DHCP4R_DEF_H_    */

