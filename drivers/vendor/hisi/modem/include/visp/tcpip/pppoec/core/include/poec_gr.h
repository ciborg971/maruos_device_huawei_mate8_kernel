
#ifndef _POEC_GR_H_
#define _POEC_GR_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/* PPPOE�ı���״̬ */
enum enumPOEC_GR_STATE
{
    POEC_GR_STATE_NORMAL,       /* 0 ����״̬ */
    POEC_GR_STATE_SMOOTHING,    /* 1 ���ڽ���ƽ������, ƽ��������Ϻ�ֱ�ӽ��� 0 ����״̬ */
    POEC_GR_STATE_RESTORED,     /* 2 �Ѿ���ɻָ�����, �ȴ�ƽ������ */
    POEC_GR_STATE_RESTORING,    /* 3 ���ڽ��лָ����� */
    POEC_GR_STATE_KEEPALIVE,    /* 4 ����״̬, �ȴ��ָ����� */
};

typedef enum tagPOEC_DEBUG_TYPE
{
    POEC_GR_DEBUG_DIALERIF_NULL,    /* */
    POEC_GR_DEBUG_ETHIF_STATE,      /* */
    POEC_GR_DEBUG_MODE,             /* */
    POEC_GR_DEBUG_NEGO_CFG,         /* */
    POEC_GR_DEBUG_NEGO_GOT,         /* */
    POEC_GR_DEBUG_GETINFO,          /* */
    POEC_GR_DEBUG_MAC_INVALID,      /* */
    POEC_GR_DEBUG_MAC_DIFF,         /* */
    POEC_GR_DEBUG_CB_NULL,          /* */
    POEC_GR_DEBUG_SESSION_EXIST,    /* */
    POEC_GR_DEBUG_CREATE_VA_FAIL,   /* */
    POEC_GR_DEBUG_ENCAP_VA_FAIL,    /* */
    POEC_GR_DEBUG_NO_PPPINFO,       /* */
    POEC_GR_DEBUG_PPP_NORMAL,       /* */
}POEC_DEBUG_TYPE_E;

extern VOID PPP_GR_DealMsg(UINTPTR aulMsg[4]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _POEC_GR_H_ */

