

#ifndef _RABM_STRU_INTERFACE_H_
#define _RABM_STRU_INTERFACE_H_

#include "NasTtf_typedef.h"
#include "TTFLink.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#pragma pack(4)
#define RABM_PS_MAX_ENT_NUM         11
#define RABM_CS_MAX_ENT_NUM         14
#define RABM_MAX_RB_NUM_PER_RAB     3
#define RABM_MAX_RB_ID              32

#define RABM_MAX_SAVE_MSG_NUM   1

#define RABM_MAX_TAF_NUM        1

#define RABM_RABM_REEST_PROT_TIMER_LEN    30000                                 /* rab�ؽ�����timerʱ��                     */

#define NAS_RABM_MAX_QOS_LEN            (16)

/*PDCP->RABM���ݶ���һ�����������Ľ�����*/
#define RABM_PDCP_ONCE_DEAL_MAX_CNT     100

#define RABM_TC_NO_START                (0)                 /* û������TC                           */
#define RABM_TC_LOOP_OPEN               (1)                 /* TC���������Ի�û�йر�               */
#define RABM_TC_LOOP_CLOSE              (2)                 /* TC���������Ի��رգ���ʼ����TC����   */

typedef struct{
    VOS_UINT8     ucRabId;                                                          /* ��RAB��Ӧ��RAB ID                        */
    VOS_UINT8     ucRbNum;                                                          /* ��RAB����RB����                          */
    VOS_UINT8     aucRbId[RABM_MAX_RB_NUM_PER_RAB];                                 /* RB ID�б�                                */
    VOS_UINT8     aucRbTxMode[RABM_MAX_RB_NUM_PER_RAB];                             /* RB ����ģʽ(��aucRbId�±�һ��)*/
}RABM_RAB_INFO_STRU;
typedef struct{
    VOS_UINT32                          ulQosLength;                            /* Qos�����ݴ�С */
    VOS_UINT8                           aucQosValue[NAS_RABM_MAX_QOS_LEN];        /* Qos�����׵�ַ */
} RABM_QOS_STRU;

typedef struct datalink{
    VOS_VOID       *pData;                                                          /* �����׵�ַ                               */
    struct datalink   *pNxt;                                                    /* ��һ�����ݽڵ��ַ                       */
}RABM_DATA_LINK_STRU;

typedef struct datasave{
    VOS_UINT8    ucNum;                                                             /* ��Ϣ����                                 */
    RABM_DATA_LINK_STRU   Data;                                                 /* �洢����Ϣ����                           */
}RABM_DATA_SAVE_STRU;


typedef struct
{
    VOS_UINT8                           ucState;            /* ��ʵ���״̬                             */
    VOS_UINT8                           ucPppFlg;           /* �Ƿ�֧��PPP��0��֧�֣�1:��֧��           */
    VOS_UINT8                           ucReEstFlg;         /* �Ƿ�Ϊ�ؽ�RAB�ı�־                      */
    VOS_UINT8                           ucStpFlg;           /* ��־�Ƿ��Ѿ�֪ͨtafֹͣ���ݴ��䣬
                                                             * RABM_TRUE:�Ѿ�֪ͨ,RABM_FALSE:û��֪ͨ   */
    HTIMER                              hRabPendingTmrHdl;  /* RAB�ؽ�������ʱ��                        */
    RABM_RAB_INFO_STRU                  RabInfo;            /* ��ʵ���Ӧ��RAB��Ϣ                      */
    RABM_QOS_STRU                       QoS;                /* ��ʵ���Ӧ��QoS                          */
    RABM_DATA_SAVE_STRU                 DlDataSave;         /* ��������������׵�ַ                     */
    RABM_DATA_SAVE_STRU                 UlDataSave;         /* ��������������׵�ַ                     */
}RABM_ENTITY_PS_STRU;


typedef struct
{
    VOS_UINT8   ucState;                                                            /* ��ʵ���״̬                             */
    VOS_UINT8   ucSi;                                                               /* ʵ���Ӧ��si                             */
    RABM_RAB_INFO_STRU   RabInfo;                                               /* ��ʵ���Ӧ��RAB��Ϣ                      */
}RABM_ENTITY_CS_STRU;

typedef struct
{
    VOS_UINT8   ucRbNum;                                                            /* ����AMR���������RB����                  */
    VOS_UINT8   aucDataLen[3];                                                      /* ���ݵ�bit����                            */
    VOS_UINT8   aucLenOffset[3];                                                    /* CLASS i��������padding����               */
    VOS_UINT8   *apucData[3];                                                       /* �����׵�ַ                               */
} RABM_AMR_DATA_STRU;

typedef struct{
    VOS_UINT8           ucTcStartSta;
    VOS_UINT8           ucLbCnt;
    struct{
        VOS_UINT8           ucEstFlg;                                               /* ��־��rb�Ƿ��Ѿ�����,RABM_TRUE:����,
                                                                                 * RABM_FALSE:û�н���                      */
        VOS_UINT8           ucRabId;
        VOS_UINT8           ucRbId;
        VOS_UINT8           ucDomain;
        VOS_UINT32          ulRlcSduSize;                                           /* ��RB���������RLC SDU�Ĵ�С              */
        VOS_BOOL            bRlcSduSizeValid;
    }aRbInf[TC_LB_MAX_RBNUM];

    VOS_BOOL                bFlowCtrlFlg;
    VOS_UINT8               ucTestLoopMode;
}RABM_TC_INF_STRU;


typedef struct
{
    VOS_UINT8               ucRbId;             /* [5,32] ��ʶ���RB ID��Ӧ��PDCPʵ��*/
    VOS_UINT8               aucReserve[3];      /* 4�ֽڶ��룬����*/
    VOS_UINT32              ulDataLen;          /* ���ݵĳ���,��λ:�ֽ� */
    VOS_UINT8              *pucData;            /* �����׵�ַ */
}PDCP_RABM_DATA_BUF_STRU;


/******************************************************************************
*     PDCP_RABM_TC_DATA_STRU ԭ�ﶨ�壬����PS�򻷻ع����������ݽӿ�
      �ӿڹ�������: RABM��PDCP�������л�������ʱ����Ҫ�����л������ݵ�
                    �㿽���ڴ�ת��Ϊ�����ڴ�
******************************************************************************/
typedef struct
{
    VOS_UINT8               ucRbId;             /* [5,32] ��ʶ���RB ID��Ӧ��PDCPʵ��*/
    VOS_UINT8               aucReserve[3];      /* 4�ֽڶ��룬����*/
    DL_DATA_CRC_INFO_STRU   stCrcInfo;          /* CRC��Ϣ��������PS�򻷻�ģʽ�� */
    VOS_UINT32              ulDataBitLen;       /* ���ݵĳ���,��λ:Bit */
    TTF_MEM_ST             *pstDataMem;
}PDCP_RABM_TC_DATA_STRU;


/******************************************************************************
*     PDCP_RABM_TC_DATA_Q_STAT_STRU ԭ�ﶨ�壬����PS�򻷻ع����������ݵ�ͳ����Ϣ
******************************************************************************/
typedef struct
{
    VOS_UINT32                  ulDlTotalCnt;       /*�������ݰ��ܸ���*/
    VOS_UINT32                  ulQMaxCnt;          /*PDCPһ�εݽ���RABM�����ݿ��������ֵ*/
    VOS_UINT32                  ulMaxCntOnce;       /*RABMһ�δ������ݿ��������ֵ*/
}PDCP_RABM_TC_DATA_Q_STAT_STRU;

/******************************************************************************
*     PDCP_RABM_TC_DATA_Q_CFG_STRU ԭ�ﶨ�壬����PS�򻷻ع����������ݵ�������Ϣ
******************************************************************************/
typedef struct
{
    VOS_UINT32                  ulOnceDealMaxCnt;  /*RABM���ݶ���һ�����������Ľ�����*/
}PDCP_RABM_TC_DATA_Q_CFG_STRU;

/******************************************************************************
*     PDCP_RABM_TC_DATA_Q_STRU ԭ�ﶨ�壬����PS�򻷻ع����������ݶ���
******************************************************************************/
typedef struct
{
    TTF_LINK_ST                    stDataQ;
    PDCP_RABM_TC_DATA_Q_STAT_STRU  stStat;      /*PDCP->RABM���ݶ��е�ͳ����Ϣ*/
    PDCP_RABM_TC_DATA_Q_CFG_STRU   stCfg;       /*PDCP->RABM���ݶ��е�������Ϣ*/
}PDCP_RABM_TC_DATA_Q_STRU;

/******************************************************************************
*     PDCP_RABM_TC_DATA_IND_NOTIFY_STRU ԭ�ﶨ�壬����PS�򻷻ع����������ݽӿ�
******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ��Ϣͷ */        /* _H2ASN_Skip */
    NAS_PDCP_MSG_TYPE_ENUM_UINT16       enMsgName;          /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[2];      /* 4�ֽڶ��룬����*/
} PDCP_RABM_TC_DATA_IND_NOTIFY_STRU;



extern RABM_ENTITY_PS_STRU    g_aRabmPsEnt[RABM_PS_MAX_ENT_NUM];                /* PS��RABMʵ���ȫ����                     */
extern RABM_ENTITY_CS_STRU    g_aRabmCsEnt[RABM_CS_MAX_ENT_NUM];                /* CS��RABMʵ���ȫ����                     */


extern VOS_UINT8        g_aucSiMapEnt[256];                                         /* SI��RABMʵ���ӳ���ϵ                   */
extern VOS_UINT8        g_ucReestTimerFlg;                                          /* RABM_TRUE:�ؽ�TIMER��Ч��RABM_FALSE:��Ч */
extern HTIMER     g_ulRabReestTimerId;                                        /* rab�ؽ�����timer                         */

extern RABM_RRC_IMPORTED_FUNC_LIST_STRU  g_RabmRrcImportFunc;

extern RABM_TC_INF_STRU       g_RabmTcInf;

extern PDCP_RABM_TC_DATA_Q_STRU g_stPdcpRabmTcDataQ;

extern VOS_UINT32                       g_ulNasRabmRabPendingTmrLen;



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
