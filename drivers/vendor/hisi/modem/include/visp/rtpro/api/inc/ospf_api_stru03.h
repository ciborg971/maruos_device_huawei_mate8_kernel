/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_api_stru03.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: 
*   01 OSPF API �ṹ����(Query�ӿ�����)
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create                              
*******************************************************************************/
#ifndef _OSPF_API_STRU03_H
#define _OSPF_API_STRU03_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#if 31 /*31 Query�ӿڽṹ��*/
/*********************���ѯ��ض���***************************/

typedef struct tagOSPF_SHOWLSDB
{
    USHORT  usProcessId;
    UCHAR   ucLsaType;   
/*
#define OSPF_ROUTER_LSA           1
#define OSPF_NETWORK_LSA          2
#define OSPF_SUMMARY_LSA          3
#define OSPF_SUMMARY_ASBR_LSA     4
#define OSPF_ASEXTERNAL_LSA       5
#define OSPF_NSSA_LSA             7
#define OSPF_OPAQUE_LOCAL_LSA     9
#define OSPF_OPAQUE_AREA_LSA      10
#define OSPF_OPAQUE_AS_LSA        11*/
    UCHAR   ucPadding;
}OSPF_SHOWLSDB_S;


typedef struct tagOspf_Lsdb_in
{
    USHORT   usProcId;  /*OSPFʵ��ID*/    
    USHORT   usLsaType; /*LSA���� */
    ULONG    ulAreaId;  /*��ID */
    ULONG    ulLsaId;   /*LSA ID*/
    ULONG    ulAdvRtrId; /*route id*/ 
}OSPF_LSDB_IN_S; /*OSPF ��LSDB ��ѯ����*/

typedef struct tagOSPF_LSAHdr_OUT
{
    USHORT  usLsaAge;   /* �ϻ�ʱ�� */
    UCHAR   ucOptions;   /* ��ѡ�� */
    UCHAR   ucLsaType;   /* LSA ���� */
    ULONG   ulLinkId;   /* ��·ID */
    ULONG   ulAdvRtr;   /* ͨ��·����ID */
    LONG    ILSSeqNum;   /* ���к� */
    USHORT  usLSChksum; /* У��� */
    USHORT  usLength;   /* ����LSAͷ�����ڵ�LSA���� */
}OSPF_LSAHDR_OUT_S; /*LSA��ͷ����Ϣ*/

typedef struct tagOSPF_RtrTOS_OUT
{
    UCHAR   ucTOS;   /* TOS */
    UCHAR   ucVar;   /* unused value Zero */
    USHORT  usMetric;   /* Metric */
}OSPF_RTRTOS_OUT_S;

typedef struct tagOSPF_RtrPiece_OUT
{
    ULONG   ulLinkId;   /* Link ID */
    ULONG   ulLinkdata;   /* Link data */
    UCHAR   ucType;   /* Type */
    UCHAR   ucNumTOS;   /* number of  TOS */
    USHORT   usMetric;   /* Metric */
    OSPF_RTRTOS_OUT_S  stTOS[OSPF_LSA_MAX_TOS_COUNT];     /* Array to first node of List of TOS */
}OSPF_RTRPIECE_OUT_S; /*·����LSA �ڲ�����*/

typedef struct tagOSPF_RtrLSA_OUT
{
    UCHAR    ucVEBBit;   /* V , E and B bit */
    UCHAR    ucPad;
    USHORT   usLinkCount;   /* Link count */
    OSPF_RTRPIECE_OUT_S   stRtrPieces[OSPF_LSA_MAX_RTR_PIECE]; 
}OSPF_RTRLSA_OUT_S; /*·����LSA*/



typedef struct tagOSPF_NetLSA_Adv_OUT
{
    ULONG   ulNetMask;   /* Network Mask */
    ULONG   ulAttachedRtr[OSPF_LSA_MAX_NET_NBR];
}OSPF_NETLSA_OUT_S; /*����LSA*/


typedef struct tagOSPF_SummPiece_OUT
{
    UCHAR   ucTOS;   /* TOS */
    UCHAR   szTOSMetric[OSPF_ARRAY_SIZE_3];   /* TOS Metric */
}OSPF_SUMMPIECE_OUT_S; /*SUMMARY LSA �ڲ�����*/

typedef struct tagOSPF_SummLSA_Adv_OUT
{
    ULONG   ulNetMask;   /* Network Mask */
    ULONG   ulMetric;   /* Metric -First 8 bits are zero */
    OSPF_SUMMPIECE_OUT_S   stSummPiece[OSPF_LSA_MAX_SUM_PIECE];   
}OSPF_SUMMLSA_OUT_S; /*SUMMARY LSA �ṹ*/


typedef struct tagOSPF_ASEPiece_OUT
{
    UCHAR   ucE_TOS;   /* E bit in first Netpiece indicates type of metric  in others Backward Compatibility & TOS*/
    UCHAR   szTOSMetric[OSPF_ARRAY_SIZE_3];   /* Metric & TOS Metric */
    ULONG   ulFwdAddr;   /* Forwarding Address */
    ULONG   ulExtRtTag;   /* External Route Tag */
}OSPF_ASEPIECE_OUT_S;


typedef struct tagOSPF_ASELSA_Adv_OUT
{
    ULONG   ulNetMask;   /* Network Mask */
    OSPF_ASEPIECE_OUT_S   stASEPiece[OSPF_LSA_MAX_ASE_PIECE];   /* Array to first node of list of ASE/NSSA LSA */
}OSPF_ASELSA_OUT_S; /*ASE LSA����*/

typedef struct tagOSPF_OpqLsa_Adv_OUT
{
    UCHAR   szOpqData[OSPF_LSA_MAX_OPQ_DATA];   /*Unparsed Data to be used by external modules*/
    UCHAR   ucPadding[2]; /*B015-L*/
}OSPF_OPQLSA_OUT_S; /*OPQ��չ����*/


typedef struct tagOSPF_SHOW_LSADATA
{
    OSPF_LSAHDR_OUT_S   stLsaHdr;   /* LSA header */
    union   tagOSPF_LSA_BODY_OUT
    {
        OSPF_RTRLSA_OUT_S   stRtrLSA;   /* Router LSA */
        OSPF_NETLSA_OUT_S   stNetLSA;   /* Network LSA */
        OSPF_SUMMLSA_OUT_S   stSummLSA;   /* Summary LSA */
        OSPF_ASELSA_OUT_S   stAseLSA;   /* External LSA */
        OSPF_OPQLSA_OUT_S   stOpqLSA;   /* Opaque LSA */
    }unLSAOut;
}OSPF_SHOW_LSADATA_S;  /*���е�LSA���нṹ*/


typedef struct tagOSPF_SHOWLSDB_OUT
{
    ULONG   ulRouterId;
    ULONG   ulAreaId;   /* for type-5 LSA, this field is invalid */
    USHORT  usProcId;
    USHORT  usRes;
    OSPF_SHOW_LSADATA_S stLSAData;
    /*UCHAR   *pucLSA;*/   /* defined in ospf\include\ospf_lsa.h */
}OSPF_SHOWLSDB_OUT_S;

typedef struct tagOSPF_VLSDB_KEY
{
    /*��ID ���ھ�ID���ڲ�ѯIF CB ,LS id��route id ���ڲ�ѯVLSDB CB*/
    UCHAR ucAreaId[4]; /*��ID*/
    UCHAR ucNeighbor[4]; /*�ھ�*/
    UCHAR ucLsId[4];  /*��·ID */
    UCHAR ucRouterId[4]; /*route id*/
    ULONG ulProcId;
}OSPF_VLSDB_KEY_S; /*����·LSDB ��ѯ�ؼ���*/

/*OSPF �շ�����ע�ṳ�Ӻ�������*/


/*OSPF ���Ĺ��Ӵ�����:OSPFʵ���š������׵�ַ�����ݳ���*/
typedef ULONG (*OSPF_PACKET_HOOK_FUNC)(USHORT usProcId, ULONG ulIfIndex, CHAR *pcPacket, ULONG ulLen);

/*PRU�������ھ�״̬�仯֪ͨ�ṹ��*/
/*�˽ṹ����޸ı����޸� I3_NBR_STATE_NOTIFY_S*/
typedef struct tagOSPF_NBR_STATE_NOTIFY
{
    ULONG ulVrfIndex;          /*VRF����*/
    ULONG ulProcID;            /*����ID*/
    ULONG ulRouterID;          /*Router ID*/
    ULONG ulAreaID;            /*����ID*/   
    ULONG ulLocalIfIndex;      /*���ھӶ�Ӧ�ı��ؽӿ�����*/ 
    ULONG ulNbrAddr;           /*�ھӵ�ַroute id*/
    ULONG ulNbrReachable;      /*�ھ��Ƿ�ɴ��ʶ
                                                      0:�ھӲ��ɴ�
                                                      1:�ھӲ��ɴ�*/
    ULONG ulPeerAddress;       /*�ھӶ�Ӧ�ӿڵĵ�ַ*/
    ULONG ulReason;            /*״̬�仯��ԭ��ֵ,��ʱ�������� */
}OSPF_NBR_STATE_NOTIFY_S;  /*�ھ�״̬֪ͨ�ṹ��*/
/*PRU�������ھ�״̬�仯֪ͨ�ӿ�*/
typedef ULONG (*OSPF_NBR_STATE_NOTIFY_FUNC)(OSPF_NBR_STATE_NOTIFY_S *pstNotify);

/* Begin BC3D03438 liangjicheng 2010-08-10*/
typedef struct tagOSPF_NBR_EVNET_NOTIFY
{
    ULONG ulVrfIndex;         /*VRF����*/
    ULONG ulProcID;            /*����ID*/ 
    ULONG ulNbrRouterID;   /*�ھӵ�ַroute id*/
    ULONG ulNbrIntAddr;     /*�ھӶ�Ӧ�ӿڵĵ�ַ*/
    ULONG ulReason;            /*״̬�仯��ԭ��ֵ ����μ�ԭ��ֵ˵��*/
    ULONG ulPrevState;        /*ǰһ״̬ ����μ�״ֵ̬˵��*/
    ULONG ulNewState;         /*��״̬ ����μ�״ֵ̬˵��*/
    ULONG ulLocalRouterID;   /*�Լ���route id*/
    ULONG ulAreaID;            /*����ID*/
    ULONG ulIfIndex ;           /*�ӿ�����*/
    ULONG ulIfAddr ;           /*�ӿڵ�ַ*/
}OSPF_NBR_EVENT_NOTIFY_S;  /*�ھ�״̬֪ͨ�ṹ��*/
typedef ULONG (*OSPF_NBR_EVENT_NOTIFY_FUNC)(OSPF_NBR_EVENT_NOTIFY_S *pstNotify);
/* End   BC3D03438 */

typedef struct tagOSPF_IF_EVENT_NOTIFY
{
  ULONG ulProcID; /*OSPF����ID*/
  ULONG ulAreaID; /*�ӿ������*/

  ULONG ulIfIndex;  /*���ؽӿ�����*/
  ULONG ulLocalRouterID;  /*����router id*/
  ULONG ulIfAddr; /*����ӿ�IP*/

  ULONG ulReason; /*�����¼�*/
  ULONG ulPrevState;  /*�ӿ�״̬��ת��ǰ��״̬*/
  ULONG ulNewState; /*�ӿ�״̬��ת����״̬*/	
}OSPF_IF_EVENT_NOTIFY_S;
typedef ULONG (*OSPF_IF_EVENT_NOTIFY_FUNC)(OSPF_IF_EVENT_NOTIFY_S *pstNotify);

#endif
typedef struct tagOSPF_DR_INFO
{
   ULONG ulDrRouteId;   /*DR Router id*/
   ULONG ulBDrRouteId;  /*BDR Router id*/
   UCHAR ucIfType;      /*OSPF�ӿ����� �ֱ���㲥��NBMA��P2P��P2MP����*/
   UCHAR ucRes[LEN_8-1];/*Ԥ��7�ֽڿռ�*/
}OSPF_DR_INFO_S;/*DR BDR��Ϣ�ṹ*/

typedef struct tagOSPF_SYS_COUNT_S
{
  ULONG ulTotalNbrs;         /* ��ϵͳ�����ھӸ��� */
  ULONG ulTotalLSAs;         /* ��ϵͳ����LSA���� */
  ULONG ulDetailLSAs[10];    /* ��ϵͳ����LSA����(�±��ӦLSA����:
                               1��2��3��4��5��7��Ч) */
}OSPF_SYS_COUNT_S;

/*OSPF�澯����*/
typedef enum tagOSPF_WARNING_TYPE
{
    OSPF_WARNING_NETWORK_LSA_CLASH = 1,   /*Network LSA��ͻ�澯*/
    OSPF_WARNING_ROUTE_CALC_OVER_LIMIT = 2,   /*·�ɼ��㳬����������*/
    OSPF_WARNING_MAX = 100
} OSPF_WARNING_TYPE_E;

typedef ULONG (*OSPF_WARNING_HOOK_FUNC)(ULONG ulWarningType, VOID *pWarningInfo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif 
