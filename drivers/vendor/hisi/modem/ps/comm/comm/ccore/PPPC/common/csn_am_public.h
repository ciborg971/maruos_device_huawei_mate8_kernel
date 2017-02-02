/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : csn_am_public.h
  �� �� ��   : ����
  ��    ��   : luofang
  ��������   : 2013��4��18��
  ����޸�   :
  ��������   : CSNģ����ⲿ�ṩ��ͷ�ļ�
  �����б�   :
*
*

  �޸���ʷ   :
  1.��    ��   : 2013��4��18��
    ��    ��   : luofang
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef _CSN_AM_PUBLIC_H_H_H_
#define _CSN_AM_PUBLIC_H_H_H_


typedef struct tagA11_RRQ_PARSER_FOR_CSN
{
    A11_IMSI_S stIMSI;
    ULONG  ulPcfIp;
    ULONG  ulSpi;
    ULONG  ulIdHigh;          /* Identification: higher 4 bytes */    
    ULONG  ulIdLow;           /* Identification: lower 4 bytes */
    USHORT usLifetime;
    UCHAR  ucMsgType;
    UCHAR  ucReserved;
    USHORT usDstPortNum;
    USHORT usReserved;
}VOS_PACKED A11_PARSER_FOR_CSN_S;

typedef struct tagCSN_INTERFACE_INFO
{
    VOS_UINT32 ulCsnifIPAddr;         /*CSN�ӿ�IP��ַ*/
    VOS_UINT32 ulCsnifVpnId;           /*CSN�ӿ�VPN ID*/
    VOS_UINT32 ulCsnifSubIdx;         
    VOS_UINT32 ulCsnifIdx;             
}CSN_INTERFACE_INFO_S;  

#define CSN_IF_IPADDR                         (g_stCsnifInfo.ulCsnifIPAddr)
#define CSN_IF_VPNID                          (g_stCsnifInfo.ulCsnifVpnId)
#define CSN_IF_SUBIDX                         (g_stCsnifInfo.ulCsnifSubIdx)
#define CSN_IF_IDX                            (g_stCsnifInfo.ulCsnifIdx)

#define CSN_RPIF_IPADDR                       (g_stCSNRpifInfo.ulCsnifIPAddr)
#define CSN_RPIF_VPNID                        (g_stCSNRpifInfo.ulCsnifVpnId)
#define CSN_RPIF_SUBIDX                       (g_stCSNRpifInfo.ulCsnifSubIdx)
#define CSN_RPIF_IDX                          (g_stCSNRpifInfo.ulCsnifIdx)

#define CSN_DETC_MSG_BUF_LEN      4096      /* ̽����Ϣ�������󳤶� */

enum CSN_BACKUP_MSG_CODE
{
    CSN_MSGCODE_FCM_DETECEREPLY,    
    CSN_MSGCODE_VP_BACKUP,
    CSN_MSGCODE_FCM_BACKUP,   /* ����������Ϣ��λ��Ϊ����fcm��Ϣ������ת�����͵�̽��Ӧ����Ϣ�ͱ�����Ϣ */
    CSN_MSGCODE_BULT
};

extern ULONG g_ulCsnServiceReadyFlag;
extern VOS_UINT32 CSN_OmInitial(VOID);

#endif


