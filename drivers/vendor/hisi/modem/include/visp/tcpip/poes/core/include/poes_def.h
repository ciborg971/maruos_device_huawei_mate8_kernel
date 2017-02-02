/*******************************************************************************
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poes_def.h
*
* Project Code: VISPV100R006C02
*  Module Name: POES
* Date Created: 2007-07-18
*       Author: lijing(52889)
*  Description: POESģ��ĺ궨���ö�����Ͷ���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-18   lijing(52889)           Create
*
*******************************************************************************/

#ifndef  _POES_DEF_H_
#define  _POES_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif
/* ����ΪPOESģ��ĺ궨�� */

#define POES_MAC_BCAST_ADDR "\xff\xff\xff\xff\xff\xff"  /* ethernet broadcast address */

#define POES_COM_NUM 1                 /* Poes���������� */ 


#define POES_SES_NODE_ARRAY_INCR 100    /* Session�ڵ�����ÿ�ε�������Ĵ�С */

#define POES_SESID_NULL 0xFFFF          /* �Ƿ�session id */

#define POES_MAX_SES_LIMIT 65534            /* Session�����Ƶ��������� */
#define POES_DEFAULT_ALL_SES_LIMIT 1000     /* ȫ��Session�����Ƶ�ȱʡֵ */
#define POES_DEFAULT_OURMAC_SES_LIMIT 1000  /* ����MAC Session������ȱʡֵ */
#define POES_DEFAULT_HISMAC_SES_LIMIT 100   /* �Զ�MAC Session������ȱʡֵ */

#define POES_PKT_IN 0   /* �뱨�ı�־ */
#define POES_PKT_OUT 1  /* �����ı�־ */
#define POES_SW_OFF 0   /* ���عر� */
#define POES_SW_ON 1    /* ���ش� */

#define POES_PRINT_PACKET_LEN 128   /* ���ݱ��Ĵ�ӡ���� */

#define POES_TIME 1000  /* POES��ʱ��ʱ��,���� */
#define POES_CLEAN_SESSION_TIME 15  /*PADI״̬Session���ʱ��15��*/
#define POES_GET_QUE_PKT_NUM 40  /* 1�δ�POES���Ķ���ȡ���ĸ��� */

/*POES Version & Type, ĿǰΪ0x11*/
#define POES_VERSION_1_TYPE_1  0x11

/* POES �ĸ���codes */
#define POES_CODE_SESS 0x00 /* PPPoE session */
#define POES_CODE_PADI 0x09 /* PPPoE Active Discovery Initiation */
#define POES_CODE_PADO 0x07 /* PPPoE Active Discovery Offer */
#define POES_CODE_PADR 0x19 /* PPPoE Active Discovery Request */
#define POES_CODE_PADS 0x65 /* PPPoE Active Discovery Session-confirmation */
#define POES_CODE_PADT 0xa7 /* PPPoE Active Discovery Terminate */

/* POES �ĸ���tag type */
#define POES_TAG_END_OF_LIST           0x0000
#define POES_TAG_SERVICE_NAME          0x0101
#define POES_TAG_AC_NAME               0x0102
#define POES_TAG_HOST_UNIQ             0x0103
#define POES_TAG_AC_COOKIE             0x0104
#define POES_TAG_VENDOR_SPECIFIC       0x0105
#define POES_TAG_RELAY_SESSION_ID      0x0110
#define POES_TAG_SERVICE_NAME_ERROR    0x0201
#define POES_TAG_AC_SYSTEM_ERROR       0x0202
#define POES_TAG_GENERIC_ERROR         0x0203

/* POES ��س��Ⱥ�*/
#define POES_MIN_ETHERNET_PAYLOAD 6     /*PPPOE ��С����*/
#define POES_MAX_ETHERNET_PAYLOAD 1500 
#define POES_ETHER_HEADER_LEN     14   /*��̫ͷ�ĳ���*/
#define POES_TAG_AND_LENGTH       4    /*TAG�����С����*/

#define POES_HEADER_LEN 20  /*PPPoE ͷ��Ϣ��������̫��֡ͷ*/
#define POES_PPP_HEAD 2     /*PPP��ACFC�ֶ����ֽ�*/

/*ETH�ײ� + PPPOE�ײ�����С����20*/
#define POES_MIN_ETHERNET_LEN \
    (POES_ETHER_HEADER_LEN + POES_MIN_ETHERNET_PAYLOAD)

/*ETH�ײ� + PPPOE�ײ�����󳤶�14 + 1500 = 1514*/
#define POES_MAX_ETHERNET_LEN \
    (POES_ETHER_HEADER_LEN + POES_MAX_ETHERNET_PAYLOAD)

/*TAG�����󾻺ɳ���1500- 6 = 1494*/
#define POES_MAX_TAG_PAYLOAD_LEN \
    (POES_MAX_ETHERNET_PAYLOAD - POES_MIN_ETHERNET_PAYLOAD)

/*TAG�����󳤶�1500- 6 - 4 = 1490*/
#define POES_MAX_TAG_LENGTH \
    (POES_MAX_ETHERNET_PAYLOAD - POES_MIN_ETHERNET_PAYLOAD - POES_TAG_AND_LENGTH)




/*PPPoE Server��ʹ�õ�һЩ�����*/
/* ���ַ�ָ��cp���һ��char��c��cpָ���1 */
#define POES_GET_CHAR(c, cp) { \
    (c) = *( (UCHAR *)(cp) ); \
    (cp) += 1 ; \
}

/* ���ַ�cд���ַ�ָ��cp����cpָ���1 */
#define POES_PUT_CHAR(c, cp) { \
    *( (UCHAR *)(cp) ) = (c) ; \
    (cp) += 1 ; \
}

/* ���ַ�ָ��cp���һ��ushortֵ��s��cpָ���2 */
#define POES_GET_SHORT(s, cp) { \
    VOS_CopyVar((s), *((USHORT *)(cp))); \
    (cp) += 2 ; \
}

/* ��ushort����s��ֵд���ַ�ָ��cp����cpָ���2 */
#define POES_PUT_SHORT(s, cp) { \
    VOS_CopyVar(*((USHORT*)(cp)), (s)) ; \
    (cp) += 2 ; \
}

/* ���ַ�ָ��cp���һ��ulongֵ��s��cpָ���4 */
#define POES_GET_LONG(l, cp) { \
    VOS_CopyVar((l) , *((ULONG *)(cp))); \
    (cp) += 4 ; \
}

/* ��ulong����l��ֵд���ַ�ָ��cp����cpָ���4 */
#define POES_PUT_LONG(l, cp) { \
    VOS_CopyVar(*((ULONG*)(cp)),(l)) ; \
    (cp) += 4 ; \
}

/* ����ΪPOESģ���ö�����Ͷ��� */
/* Session״̬ */
enum enumPoesSesState
{
    POES_RCVD_PADI = 0, /* PADI״̬ */
    POES_PPP_SESSION    /* �Ự״̬ */
};




#ifdef __cplusplus
}
#endif

#endif 

