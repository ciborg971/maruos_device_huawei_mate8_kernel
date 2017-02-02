/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_TYPE.H 
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/03/28
 *        Author: luohanjun
 *   Description: 
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/03/28      luohanjun       Create File
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *  2006-05-10   luyao(60000758)    Ϊ֧��ARM CPU�ֽڶ������ԣ��޸Ľṹ��
 *
 ************************************************************************/

#ifndef _TCPIP_IF_TYPE_H_
#define _TCPIP_IF_TYPE_H_

#ifdef  __cplusplus
extern "C"{
#endif


typedef struct Vector
{
    ULONG    ulUsedMax;            /* ���õ����Ԫ��  */
    ULONG    ulAllocedMax;         /* �ѷ�������Ԫ��*/
    VOID **  Pindex;               /* ��ַ����          */
} VECTOR_S;
typedef  VECTOR_S * PVECTOR_S;



/* �����ĸ��ṹҪ�����ֶ���ͬ��������֪ͨ���������� */
typedef struct tagIF_MSG_FUNLINK_S  
{
    IF_MSG_NOTIFYFN   if_pfNotifyFn ;  /* ֪ͨ���� */ 
    ULONG   if_ulPriority;   /* ���ȼ� */   
    struct tagIF_MSG_FUNLINK_S* if_pNext;
}IF_MSG_FUNLINK_S ;

typedef struct tagIF_LMSG_FUNLINK_S  
{
    IF_LMSG_NOTIFYFN   if_pfNotifyFn ;  /* ֪ͨ���� */ 
    ULONG   if_ulPriority;   /* ���ȼ� */   
    struct tagIF_LMSG_FUNLINK_S* if_pNext;
}IF_LMSG_FUNLINK_S ;

typedef struct tagIF_PTR_FUNLINK_S  
{
    IF_PTR_NOTIFYFN   if_pfNotifyFn ;  /* ֪ͨ���� */ 
    ULONG   if_ulPriority;   /* ���ȼ� */   
    struct tagIF_PTR_FUNLINK_S* if_pNext;
}IF_PTR_FUNLINK_S ;

/*���������ڵ�ṹ������ע�ᡢע�����ϸ�֪ͨ����*/
typedef struct tagIF_FUNLINK_S  
{
    void*   if_pfNotifyFn ;  /* ֪ͨ���� */ 
    ULONG   if_ulPriority;   /* ���ȼ� */   
    struct tagIF_FUNLINK_S* if_pNext;
}IF_FUNLINK_S ;
/*end for A82D20427*/


/*��ʱ���ṹ*/
typedef struct tagX_Timer
{
    ULONG ulStartFlag;  /*������ʱ����־ VRP_YES /VRP_NO*/
    ULONG ulTimerPeriod;/*ֵΪ��ʱ�����ڳ���������Ϊ��λ*/
}IF_TIMER_S;
 

#define CLI_CMD_TEMPLET_IF_ETHERNET         "ethernet"
#define CLI_CMD_TEMPLET_IF_SERIAL           "serial"
#define CLI_CMD_TEMPLET_IF_NULL             "null"
#define CLI_CMD_TEMPLET_IF_LOOPBACK         "loopback"

#define CLI_CMD_TEMPLET_IF_DIALER          "dialer"
#define CLI_CMD_TEMPLET_VIRTUAL_TEMPLATE   "virtual-template"
#define CLI_CMD_TEMPLET_IF_ATM             "atm"
#define CLI_CMD_TEMPLET_MULTILINK          "mp-group"

#define CLI_NO_CMD_TEMPLET                 "NoCMDTemplet"     /* ��ʶû������ģ�� */

#define CLI_CMD_TEMPLET_IF_VI             "vi"

#define CLI_CMD_TEMPLET_IF_UI             "ui"

#define CLI_CMD_TEMPLET_IF_VLANIF          "vlanif"

#define CLI_CMD_TEMPLET_IF_TUNNEL         "tunnel"

#ifdef  __cplusplus
}
#endif

#endif

