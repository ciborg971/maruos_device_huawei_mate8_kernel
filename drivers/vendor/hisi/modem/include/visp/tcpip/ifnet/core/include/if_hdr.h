

#ifndef _IF_HDR_H_
#define _IF_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN 47       /* ���ӿ������� */
#endif

/* IFNET�ӿ���챨�����ݽṹ */

/* �ӿ�״̬ */
typedef struct tagIF_HEALTH_IFSTATUS
{
    UCHAR   szIfName[IF_MAX_INTERFACE_NAME_LEN+1] ;
    ULONG   ulIfIndex ;
    ULONG   ulPhyStatus;       
    ULONG   ulShutdown;       
}IF_HEALTH_IFSTATUS_S ;

/* �ӿ�UP/DOWNͳ����Ϣ */
typedef struct tagIF_HEALTH_IFSTATISTIC
{
    ULONG   ulIfIndex ;
    ULONG   ulPhyUpCount;      /* �ӿڱ仯������UP���� */
    ULONG   ulPhyDownCount;    /* �ӿڱ仯������Down���� */
    ULONG   ulLineUpCount;     /* �ӿڱ仯��Э��UP���� */
    ULONG   ulLineDownCount;   /* �ӿڱ仯��Э��Down���� */
}IF_HEALTH_IFSTATISTIC_S ;


/* IFNET�ӿ������������ݽṹ */
typedef struct tagIF_LASTWORD_IFSTATUS
{
    ULONG   ulIfIndex ;
    UCHAR   ucPhyStatus;       
    UCHAR   ucShutdown;  
    UCHAR   ucResevred[2];
}IF_LASTWORD_IFSTATUS_S ;

/*ÿ�α���Ľӿڸ��� */
#define  IFNET_HEALTH_MAXIF_ITEM     20  

/*IFNET��챨�泤��*/
#define  IFNET_HEALTH_HEAD_LEN        (sizeof(HDR_MSG_HEAD_S))

extern VOID IF_Health_BatchCheckup();
extern ULONG IF_Health_IfStatusCheckup();
extern ULONG IF_Health_IfStatisticCheckup();
extern ULONG IF_LastWord_BatchCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);

#ifdef  __cplusplus
}
#endif
#endif

