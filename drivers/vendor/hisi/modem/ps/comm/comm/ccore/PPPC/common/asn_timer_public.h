/******************************************************************************

                  ��Ȩ���� (C), 2012-2020, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : asn_timer_public.h
  �� �� ��   : ����
  ��         ��   :  zhaichao
  ��������   : 2012��9��27��
  ����޸�   :
  ��������   : ҵ��ʱ��ģ���ṩ��AM��ϵͳ�Ĺ���ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��27��
    ��    ��   : zhaichao
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __ASN_TIMER_PUBLIC_H__
#define __ASN_TIMER_PUBLIC_H__



/*--------------------- ��ʱ�����Ͷ��� -----------------------------------*
  ��ʱ�����͵ĺ궨������ͼ��ʾ:
  -------------------------------------------------
  |  ��ʱ��   |  ��ʱ��   |      ��ʱ��           |
  |   ��ʽ    | ��������  |      ������           |
  -------------------------------------------------
  ����,��ʱ�����Ͷ�Ӧ��ʱ������ʱ��Ϣ�ṹ�еĶ�ʱ�������ֶ�.
*/

#define ASN_TIMER_DEF_TYPE(Style, TimerMid, Sub) ((((Style)&0xFF)<<24)  |(((TimerMid) &0xFF)<<16) | ((Sub)&0xFFFF))
#define ASN_TIEMR_GET_MID(TimerType) (((TimerType)>>16)&0xFF)

/* ʹ�ö�ʱ����ģ��ID������ģ������ڴ˴�����mid�Ķ��� */
typedef enum
{
    ASN_COMMON_TIMER_MODULE_START,
    ASN_COMMON_TIMER_MODULE_A11,                         /* a11ģ�鶨ʱ��ʹ�õ�MID */ 
    ASN_COMMON_TIMER_MODULE_IPV6,                       /* IPV6ģ�鶨ʱ��ʹ�õ�MID */ 
    ASN_COMMON_TIMER_MODULE_PDN,                       /* PDNģ�鶨ʱ��ʹ�õ�MID */ 
    ASN_COMMON_TIMER_MODULE_USM,                       /* USMģ�鶨ʱ��ʹ�õ�MID */ 
    ASN_COMMON_TIMER_MODULE_FA,                          /* FAģ�鶨ʱ��ʹ�õ�MID */ 
    ASN_COMMON_TIMER_MODULE_PMIPV6,                      /* PMIPV6ģ�鶨ʱ��ʹ�õ�MID */
    ASN_COMMON_TIMER_MODULE_RESV,                        /*RESVģ�鶨ʱ��ʹ�õ�MID */
    ASN_COMMON_TIMER_MODULE_END
}ASN_COMM_TIMER_MID_E;

/*��ʱ����ʽ����*/
typedef enum
{
    ASN_CP_COMMON_TIMER_STYLE   = 0x01,             /* ��ʶ��ͨ����̬��ʱ��*/ 
    ASN_CP_LOOP_TIMER_STYLE,                                      /* ��ʶѭ����ʱ�� */

    ASN_CP_TIMER_STYLE_BUTT
}ASN_COMM_TIMER_STYLE_E;


/*������ʱ������������������ݽṹ��ʽ,��ҵ�����д*/
typedef struct
{   
    VOS_UINT32 ulTimerType;             /* ��ʱ������ */
    VOS_UINT32 ulTimerLength;        /*��ʱ����ʱʱ��(��λ:��)*/
    VOS_UINT32 ulParam1;      
    VOS_UINT32 ulParam2;                 /*�û�����2*/
} ASN_STARTTIMER_PARAM_S;

/*��ʱ�����������������ͳ�ʱ��Ϣ�Ľṹ*/
typedef struct
{   
    VOS_UINT32  ulTimerType; /*��ʱ������, ��д��ʱ�����Ͷ���ĺ�,�μ����ĵ�*/
    VOS_UINT32  ulTimerID;   /*��ʱ��ID*/
    VOS_UINT32  ulParam1;    /*�û�����*/
    VOS_UINT32  ulParam2;    /*�û�����*/
} ASN_TIMER_MSG_S;

/*********************�����ṩ�Ľ�ں���**********************/
ULONG ASN_TimerInitRegister(ULONG ulTimerMid, VOS_UINT64 ullCsi, ULONG ulMsgType);
extern VOS_UINT32 ASN_CPGetTimerNodePosition(VOS_UINT32  ulTimerID, VOS_UINT32  *pulNodePosition);

extern VOS_UINT32 ASN_CPGetTimerSpareTime(VOS_UINT32  ulTimerID, VOS_UINT32  *pulGetSpareTime);
extern VOS_UINT32 ASN_CPStartTimer(ASN_STARTTIMER_PARAM_S* pstStartTimerParam, VOS_UINT32* pulTimerID);
extern VOS_UINT32 ASN_CPStopTimer(VOS_UINT32 ulTimerType, VOS_UINT32 ulTmrIndex);

#endif /* __ASN_TIMER_PUBLIC_H__ */
