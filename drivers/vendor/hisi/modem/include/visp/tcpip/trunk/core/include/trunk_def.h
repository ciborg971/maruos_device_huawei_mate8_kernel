/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_def.h
*
*  Project Code: VISP V100R006
*   Module Name: Trunk  
*  Date Created: 2006-11-27
*        Author: sunmo(44939)
*   Description: Trunkģ��ĺ��ö�ٶ���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2006-11-27  sunmo(44939)     Create the first version.
*
*******************************************************************************/

#ifndef _TRUNK_DEF_H_
#define _TRUNK_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif

/* Trunk�ӿ������Ŀ */
#define TRUNK_MAX_NUM           g_ulTrunkMaxIfNums
#define TRUNK_MIN_NUM           32

/* Trunk ID��Сֵ */
#define TRUNK_MIN_ID            0
/* Trunk ID���ֵ */
#define TRUNK_MAX_ID            (g_ulTrunkMaxIfNums - 1)

/* Trunk���������� */
#define TRUNK_COM_NUM           9


#define TRUNK_TIME              100

#define TRUNK_TIME_MULT 10

/* Trunk link loop back timer */
#define TRUNK_LB_TIME           3000

/* 10M������ (��KΪ��λ--- �޸�ԭ��:����10GE�����޷���ʶ) */
#define TRUNK_SPEED_10M     (10*1024)

/* 100M������ (��KΪ��λ--- �޸�ԭ��:����10GE�����޷���ʶ) */
#define TRUNK_SPEED_100M    (100*1024)

/* 1000M������ (��KΪ��λ--- �޸�ԭ��:����10GE�����޷���ʶ) */
#define TRUNK_SPEED_1000M   (1000*1024)
#define TRUNK_SPEED_MAX_GE  (1024*1024)

/* 10GE������ (��KΪ��λ--- �޸�ԭ��:����10GE�����޷���ʶ) */
#define TRUNK_SPEED_10GE   (10*1000*1024)
#define TRUNK_SPEED_MAX_10GE  (10*1024*1024)

/* 40GE������ (��KΪ��λ--- �޸�ԭ��:����10GE�����޷���ʶ) */
#define TRUNK_SPEED_40GE   (40*1000*1024)
#define TRUNK_SPEED_MAX_40GE  (40*1024*1024)

#define TRUNK_SPEED_MAC_MULTI   5  /*GET_SPEEDKEY_BY_BAUD�����keyֵ/0x100 */

/* �Ƿ�Trunk ID */
#define TRUNK_INVALID_ID        0xFFFFFFFF

/* physical��ַ���� */
#define TRUNK_MACADDR_LEN       6

#define TRUNK_MAX_NEG_TIME 600         /* �����״�Э�̲�������澯���ʱ��,��λΪs */
#define TRUNK_NEGWARNING_TIMEINIT  (ULONG)~0x0  /* 0xFFFFFFFF */
#define TRUNK_NEGWARNING_TIMEDONE  (ULONG)~0x1  /* 0xFFFFFFFE */

/* ��state���в����ĺ� */
#define LACP_EXPIRED           0x0
#define LACP_STATE_ACTIVITY    0x01
#define LACP_STATE_TIMEOUT     0x02
#define LACP_STATE_AGG         0x04
#define LACP_STATE_SYNC        0x08
#define LACP_STATE_COLLECT     0x10
#define LACP_STATE_DISTRIB     0x20
#define LACP_STATE_DEFAULT     0x40
#define LACP_STATE_EXPIRED     0x80

#define LACP_SET_STATE_ACTIVITY(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_ACTIVITY;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_ACTIVITY);\
    }\
}
#define LACP_GET_STATE_ACTIVITY(ucState) (ucState & LACP_STATE_ACTIVITY)

#define LACP_SET_STATE_TIMEOUT(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_TIMEOUT;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_TIMEOUT);\
    }\
}
#define LACP_GET_STATE_TIMEOUT(ucState) ((ucState & LACP_STATE_TIMEOUT) >> 1)

#define LACP_SET_STATE_AGG(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_AGG;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_AGG);\
    }\
}
#define LACP_GET_STATE_AGG(ucState) ((ucState & LACP_STATE_AGG) >> 2)

#define LACP_SET_STATE_SYNC(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_SYNC;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_SYNC);\
    }\
}
#define LACP_GET_STATE_SYNC(ucState) ((ucState & LACP_STATE_SYNC) >> 3)

#define LACP_SET_STATE_COLLECT(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_COLLECT;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_COLLECT);\
    }\
}
#define LACP_GET_STATE_COLLECT(ucState) ((ucState & LACP_STATE_COLLECT) >> 4)

#define LACP_SET_STATE_DISTRIB(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_DISTRIB;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_DISTRIB);\
    }\
}
#define LACP_GET_STATE_DISTRIB(ucState) ((ucState & LACP_STATE_DISTRIB) >> 5)

#define LACP_SET_STATE_DEFAULT(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_DEFAULT;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_DEFAULT);\
    }\
}
#define LACP_GET_STATE_DEFAULT(ucState) ((ucState & LACP_STATE_DEFAULT) >> 6)

#define LACP_SET_STATE_EXPIRED(ucState, ulValue) \
{\
    ULONG ulTemp = ulValue;\
    if(ulTemp > 0)\
    {\
        ucState |= LACP_STATE_EXPIRED;\
    }\
    else\
    {\
        ucState &= (~LACP_STATE_EXPIRED);\
    }\
}
#define LACP_GET_STATE_EXPIRED(ucState) ((ucState & LACP_STATE_EXPIRED) >> 7)


/* ��������\�ǻָ���Trunk��,δ��ѡ�ж˿ڵĶ˿ں����λ��1. ѡ���߼�ʱ,Ӧ�ò��������λ��ȡֵ */
#define LACP_GET_PORTNUM(usPortNum) (usPortNum & 0X7FFF)


/* ÿ�뷢�͵�LACP���ĵ������Ŀ*/
#define LACP_PDU_MAXSEND_PERSECOND  3

#define LACP_FAST_PERIODIC_TIME     1   /* ���ö̳�ʱ����������Է���ʱ�䳤�ȣ��룩 */
#define LACP_SLOW_PERIODIC_TIME     30  /* ���ó���ʱ����������Է���ʱ�䳤�ȣ��룩 */

#define LACP_SHORT_TIMEOUT_TIME     3   /* ���������̳�ʱ����Ľ��ճ�ʱʱ�䳤�ȣ��룩*/
#define LACP_LONG_TIMEOUT_TIME      90  /* ������������ʱ����Ľ��ճ�ʱʱ�䳤�ȣ��룩*/

/* ����ΪLACPDU�������õ�����صĺ궨�� */
#define LACP_SUBTYPE                1  /* ����Э����LACP��Э��� */
#define LACP_VERSION                1  /* Э��汾�� */
#define LACP_ACTOR_TYPE             1  /* ָʾΪActor���� */
#define LACP_ACTOR_INFO_LEN         20 /* Actor��Ϣ�ĳ��� */
#define LACP_PARTNER_TYPE           2  /* ָʾΪPartner������ */
#define LACP_PARTNER_INFO_LEN       20 /* partner��Ϣ�ĳ��� */
#define LACP_COLLECTOR_TYPE         3  /* ָʾΪcollector���� */
#define LACP_COLLECTOR_LEN          16 /* collector��Ϣ�ĳ��� */
#define LACP_MAX_COLLECTOR_DELAY    0  /* ����ռ��ӳ� */

/* �������������־ */
#define PKT_INPUT   0
#define PKT_OUTPUT  1

/* ѡ���߼�������Ч�±� */
#define LACP_SL_INVALID_PORTID  0xFFFFFFFF

/* ȱʡ���ȼ� */
#define LACP_DEFAULT_PRI 0xFFFF

/* trunk���Ա�˿��Ͻ�������bfd�Ự����Чģʽ */
#define BFD_TRUNKMODE_TRUNK     0x0 /* trunk�ϵĵ����Ự��Ч */
#define BFD_TRUNKMODE_PORT      0x1 /* ��Ա�˿��ϵĵ����Ự��Ч */

#ifndef MACADDRLEN
#define MACADDRLEN       6       /*physical��ַ����*/
#endif

/* 1:1ģʽ�����˿��� */
#define TRUNK_ONETOONE_MAX_PORT  2

#define GET_SPEEDKEY_BY_BAUD(Baud, Key)\
do\
{\
    switch(Baud)\
    {\
        case TRUNK_SPEED_10M:\
        case (10*1000):\
            (Key) = 0x100;\
            break;\
        case TRUNK_SPEED_100M:\
        case (100*1000):\
            (Key) = 0x200;\
            break;\
        case TRUNK_SPEED_1000M:\
        case (1000*1000):\
        case TRUNK_SPEED_MAX_GE:\
            (Key) = 0x300;\
            break;\
        /* 10GE */\
        case TRUNK_SPEED_10GE:\
        case (10*1000*1000):\
        case TRUNK_SPEED_MAX_10GE:\
            (Key) = 0x400;\
            break;\
        /* 40GE */\
        case TRUNK_SPEED_40GE:\
        case (40*1000*1000):\
        case TRUNK_SPEED_MAX_40GE:\
            (Key) = 0x500;\
            break;\
        default:\
            (Key) = 0;\
            break;\
    }\
}while(0)\

/* ����LACP down��ԭ���¼ */
enum emumTRUNK_LACP_DOWN_DOT
{
    TRUNK_DOWN_NORMAL               = 0,
    TRUNK_DOWN_PORTDOWN             = 1, /* �ײ��ϱ�����down */
    TRUNK_DOWN_PORTSPEED            = 2, /* �˿����ʷ����仯 */
    TRUNK_DOWN_PORTDUPLEX           = 3, /* �˿�˫��ģʽ�����仯 */
    TURNK_DOWN_PORTREMOVE           = 4, /* �˿��Ƴ�TRUNK�� */
    TRUNK_DOWN_RXTIMEOUT            = 5, /* ���ն�ʱ����ʱ */
    TRUNK_DOWN_PARTNER_UNSEL        = 6, /* �յ��Զ�û��ѡ�б�� */ 
    TRUNK_DOWN_PARTNER_PARA_CHANGE  = 7, /* �յ��Զ˲����仯 */
    TRUNK_DOWN_ACTOR_PARA_CHANGE    = 8, /* �յ��Զ˱��汾�˲����仯 */
    TRUNK_DOWN_END        = 0xFF,
};

enum enumTRUNK_NSR_LINK_STATE
{
    TRUNK_NSR_LINK_CONFIG_RESUME_FAIL = 1,                  /* ����ת��������ݴ����µĻָ�ʧ�� */
    TRUNK_NSR_LINK_RESUME_FINISH,                       /**/
    TRUNK_NSR_LINK_STATE_MAX
};

#define TRUNK_DROP_NOLACP_OFF    0
#define TRUNK_DROP_NOLACP_ON     1
        
#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRUNK_DEF_H_ */
