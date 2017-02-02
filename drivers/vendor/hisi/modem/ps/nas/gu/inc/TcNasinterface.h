

#ifndef TC_NAS_INTERFACE_H_
#define TC_NAS_INTERFACE_H_

#include "NasMmlCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)
/***********************************
    Define TC-INTRA Primitive
************************************/
/* TC -> NAS */
#define TCRABM_TEST_LOOP_REQ                      0x00000001
#define TCMM_TEST_REQ                             0x00000002
#define TCGMM_TEST_REQ                            0x00000003
#define TCRABM_TEST_REQ                           0x00000004
#define TCCC_TEST_REQ                             0x00000005
#define TCSM_TEST_REQ                             0x00000006
#define TCSMS_TEST_REQ                            0x00000007
#define TCSS_TEST_REQ                             0x00000008
#define TCMM_DATA_REQ                             0x00000009
#define TCGMM_DATA_REQ                            0x0000000A

/* NAS -> TC */
#define TCRABM_TEST_LOOP_CNF                      0x0000000B
#define TCRABM_TEST_CNF                           0x0000000C
#define TCRABM_RAB_IND                            0x0000000D
#define TCMM_DATA_IND                             0x0000000E
#define TCGMM_DATA_IND                            0x0000000F

#define TCMM_RR_REL_IND                           0x00000010
#define TCGMM_RR_REL_IND                          0x00000011
#define TCGMM_HANDOVER_IND                        0x00000012


/* TC -> MTA */
#define TCMTA_RESET_UE_POS_STORED_INFO_IND        0x00000020

/***********************************
    NAS-TC �ӿ���ʹ�õĺ궨��
************************************/
#define TC_NAS_MAX_SIZE_TC_MSG                       0x10                       /* TC��Ϣ����󳤶�    16�ֽ�               */
#define TC_CN_DOMAIN_CS                              0x00                       /* CS�������    0                          */
#define TC_CN_DOMAIN_PS                              0x01                       /* PS�������    1                          */
#define TC_LB_MAX_RBNUM                              0x10                       /* LOOP BACKʵ���������    16            */
#define TC_RB_TEST_ACTIVE                            0x01                       /* ����RB����    1                          */
#define TC_RB_TEST_DEACTIVE                          0x00                       /* ȥ����RB����    0                        */
#define TC_RABM_MAX_RAB_SETUP                        0x10                       /* CN Domain��RAB��������    16           */
#define TC_LOOP_OPEN                                 0x00                       /* ֹͣ�ػ�����    0                        */
#define TC_LOOP_CLOSE                                0x01                       /* ��ʼ���лػ�����    1                    */
#define TC_MODE_1                                    0x00                       /* LOOP MODE 1                              */
#define TC_MODE_2                                    0x01                       /* LOOP MODE 2                              */
#define TC_RAB_SETUP                     (VOS_UINT32)0x00                       /* �����µ�RAB                              */
#define TC_RAB_RELEASE                   (VOS_UINT32)0x01                       /* �ͷ��Ѿ�������RAB                        */
#define TC_CMPMSG_SIZE                   (VOS_UINT32)0x02                       /* TC����mm��gmm����Ϣ���ȣ�2���ֽ�         */

/******************************************************************************
*       TCRABM_TEST_LOOP_REQ
******************************************************************************/
typedef struct
{
    VOS_UINT32                 ulRBID;                                               /* LB ʵ���RBID                            */
    VOS_UINT32                 ulUpRlcSduSize;                                       /* LBʵ�����Ϣ                             */
}LB_INFO_STRU;

typedef struct tcrabm_test_loop_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32             ulMode;                                              /* ��ʼ���߽����ı�־                       */
    VOS_UINT32             ulRBNum;                                             /* LB ʵ�����                              */
    LB_INFO_STRU           aLBIdList[TC_LB_MAX_RBNUM];                          /* LBʵ�����Ϣ                             */

    VOS_UINT8              ucTestLoopMode;                                      /* ģʽһ��ģʽ�� */
} TCRABM_TEST_LOOP_REQ_STRU;

/******************************************************************************
*       TCRABM_TEST_LOOP_CNF
******************************************************************************/
typedef struct tcrabm_test_loop_cnf_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
} TCRABM_TEST_LOOP_CNF_STRU;

/******************************************************************************
*       TCMM_TEST_REQ
******************************************************************************/
typedef struct tcmm_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulMode;                                              /* �������ȥ����ı�־                     */
} TCMM_TEST_REQ_STRU;

/******************************************************************************
*       TCGMM_TEST_REQ
******************************************************************************/
typedef struct tcgmm_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulMode;                                              /* �������ȥ����ı�־                     */
} TCGMM_TEST_REQ_STRU;

/******************************************************************************
*       TCCC_TEST_REQ
******************************************************************************/
typedef struct tccc_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulMode;                                              /* �������ȥ����ı�־                     */
} TCCC_TEST_REQ_STRU;

/******************************************************************************
*       TCSM_TEST_REQ
******************************************************************************/
typedef struct tcsm_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulMode;                                              /* �������ȥ����ı�־                     */
} TCSM_TEST_REQ_STRU;

/******************************************************************************
*       TCSMS_TEST_REQ
******************************************************************************/
typedef struct tcsms_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulMode;                                              /* �������ȥ����ı�־                     */
} TCSMS_TEST_REQ_STRU;

/******************************************************************************
*       TCSS_TEST_REQ
******************************************************************************/
typedef struct tcss_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulMode;                                              /* �������ȥ����ı�־                     */
} TCSS_TEST_REQ_STRU;

/******************************************************************************
*       TCRABM_TEST_REQ
******************************************************************************/
typedef struct tcrabm_test_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulMode;                                              /* �������ȥ����ı�־                     */
} TCRABM_TEST_REQ_STRU;

/******************************************************************************
*       TCRABM_TEST_CNF
******************************************************************************/
typedef struct
{
    VOS_UINT32                  ulRabId;                                             /* RAB ID                                   */
    VOS_UINT32                  ulCnDomainId;                                        /* ��RAB����CN Domain                       */
    VOS_UINT32                  ulRbId;                                              /* ��RAB����RB ID                           */
} RAB_INFORMATION_STRU;

typedef struct tcrabm_test_cnf_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulRabCnt;                                            /* ��ǰ�Ѿ�������RAB����                    */
    RAB_INFORMATION_STRU   aRabInfo[TC_RABM_MAX_RAB_SETUP];                     /* RABʵ�����Ϣ                            */
} TCRABM_TEST_CNF_STRU;

/******************************************************************************
*       TCRABM_RAB_IND
******************************************************************************/
typedef struct tcrabm_rab_ind_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulRabChangeType;                                     /* RAB�Ĳ�������                            */
    RAB_INFORMATION_STRU   RabInfo;                                             /* RABʵ�����Ϣ                            */
} TCRABM_RAB_IND_STRU;

/******************************************************************************
*       TCMM_DATA_IND
******************************************************************************/
typedef struct tc_msg_stru{
    VOS_UINT32                   ulTcMsgSize;                                        /* [1,TC_NAS_MAX_SIZE_TC_MSG]               */
    VOS_UINT8                   aucTcMsg[4];                                        /* ��Ϣ��ǰ�ĸ��ֽ�����                     */
}TC_MSG_STRU;

typedef struct tcmm_data_ind_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    TC_MSG_STRU            RcvTcMsg;                                            /* ��Ϣ����                                 */
}TCMM_DATA_IND_STRU;

/******************************************************************************
*       TCMM_DATA_REQ
******************************************************************************/
typedef struct tcmm_data_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    TC_MSG_STRU            SendTcMsg;                                           /* ������Ҫ���͵�TC��Ϣ                     */
}TCMM_DATA_REQ_STRU;

/******************************************************************************
*       TCGMM_DATA_IND
******************************************************************************/
typedef struct tcgmm_data_ind_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    TC_MSG_STRU            RcvTcMsg;                                            /* ��Ϣ����                                 */
}TCGMM_DATA_IND_STRU;

/******************************************************************************
*       TCGMM_DATA_REQ
******************************************************************************/
typedef struct tcgmm_data_req_stru{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    TC_MSG_STRU            SendTcMsg;                                           /* ������Ҫ���͵�TC��Ϣ                     */
}TCGMM_DATA_REQ_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ    */
}TCMM_RR_REL_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ    */
}TCGMM_RR_REL_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ           */

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRat;                               /* ��ǰפ���Ľ��뼼��  */
    VOS_UINT8                           aucReserve[3];                          /* ���� */
}TCGMM_HANDOVER_IND_STRU;
enum TC_UE_POS_TECH_ENUM
{
    TC_UE_POS_TECH_AGPS   = 0 ,
    TC_UE_POS_TECH_AGNSS      ,
    TC_UE_POS_TECH_BUTT
};
typedef VOS_UINT8 TC_UE_POS_TECH_ENUM_UINT8;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ           */

    TC_UE_POS_TECH_ENUM_UINT8           enUePosTech;                            /* UE Positioning Technology  */
    VOS_UINT8                           aucReserve[3];                          /* ���� */
}TCMTA_RESET_UE_POS_STORED_INFO_STRU;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif  /* TC_NAS_INTERFACE_H_ */

