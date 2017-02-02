

#ifndef _TRUNK_HDR_H_
#define _TRUNK_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* ��챨��TRUNK��Ϣ */
typedef struct tagTRUNK_HEALTH_INFO
{
    TRUNK_INFO_S stTkInfo;
}TRUNK_HEALTH_INFO_S;

/* ��챨��trunk ��Ա�˿���Ϣ */
typedef struct tagLACP_HEALTH_INFO
{
    ULONG ulTkId;                        /* �˿�����trunk��id*/
    ULONG ulPortIndex;                  /* �˿�����          */
    LACP_FSM_INFO_S   stLacpFsmInfo;    /* ��Ա�˿�״̬����Ϣ */
    LACP_NEGO_INFO_S  stLacpNegoInfo;   /* ��Ա�˿�Э����Ϣ */
    PORT_STAT_INFO_S  stPortStat;       /* ��Ա�˿ڱ���ͳ����Ϣ */
}LACP_HEALTH_INFO_S;


/* trunk�������԰���Ϣ */
typedef struct tagTRUNK_LASTWORD_BINDINFO
{
    ULONG  ulIfIndex;                           /* Trunk�ӿ����� */
    ULONG  ulEnableLacp;                            /* �Ƿ�ʹ��LACP */
    ULONG  ulPortIfIndex[TRUNK_PORT_MAX_NUM];       /* ��Ա�˿ڽӿ��������� */
    ULONG  ulUpPortIfIndex[TRUNK_PORT_MAX_NUM];     /* UP�ĳ�Ա�˿ڽӿ��������� */
}TRUNK_LASTWORD_BINDINFO_S;


#ifdef  __cplusplus
}
#endif
#endif


