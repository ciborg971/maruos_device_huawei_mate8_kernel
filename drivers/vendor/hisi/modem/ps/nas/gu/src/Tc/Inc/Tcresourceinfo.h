

#ifndef TC_RESOURCE_INFO_H_
#define TC_RESOURCE_INFO_H_


#include "Tcinclude.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#pragma pack(4)
#define TC_CN_DOMAIN_CS                             0x00                        /* CS�������              0                */
#define TC_CN_DOMAIN_PS                             0x01                        /* PS�������              1                */
#define TC_RABM_MAX_RB_PER_RAB                      0x08                        /* ÿ��RAB�����RB����     8                */
#define TC_LB_MAX_RBNUM                             0x10                        /* LOOP BACKʵ��������� 16               */
#define TC_RB_TEST_ACTIVE                           0x01                        /* ����RB����              1                */
#define TC_RB_TEST_DEACTIVE                         0x00                        /* ȥ����RB����            0                */
#define TC_RABM_MAX_RAB_SETUP                       0x10                        /* CN DomainRAB�������� 16                */
#define TC_LOOP_OPEN                                0x00                        /* ֹͣ�ػ�����            0                */
#define TC_LOOP_CLOSE                               0x01                        /* ��ʼ���лػ�����        1                */
#define TC_MODE_1                                   0x00                        /* LOOP MODE 1                              */
#define TC_MODE_2                                   0x01                        /* LOOP MODE 2                              */

/***********************************
    Define TC Status Value
************************************/
#define TC_NORMAL_MODE                              0x00                        /* TC��ͨ��״̬����ʱRB����û�м���         */
#define TC_OPEN_TEST_LOOP                           0x01                        /* TC�Ŀ���״̬����ʱRB�����Ѿ�����ػ���
                                                                                 * �Ի�û�н��У���ʱ����WCDMA����ģʽ��    */
#define TC_CLOSE_TEST_LOOP                          0x02                        /* TC�ıջ�״̬����ʱRB�����Ѿ�����ػ���
                                                                                 * �����ڽ��У���ʱ����WCDMA����ģʽ��    */
#define TC_GSM_CLOSE_TCH_LOOP                       0x03                        /* TC�ıջ�״̬����ʱ����GSM����ģʽ��*/

#define TC_GPRS_CLOSE_TCH_LOOP                      0x04                        /*GPRS�µ�TC�ջ�״̬*/

#define TC_EGPRS_CLOSE_TCH_LOOP                     0x05                        /*EGPRS�µ�TC�ջ�״̬*/

#define TC_ABNORMAL_STATE                           0x0F                        /* TC״̬�쳣 */

/***********************************
    Define TC-SS Message Value
************************************/
#define TC_CLOSE_UE_TEST_LOOP                       0x40
#define TC_CLOSE_UE_TEST_LOOP_CMP                   0x41
#define TC_OPEN_UE_TEST_LOOP                        0x42
#define TC_OPEN_UE_TEST_LOOP_CMP                    0x43
#define TC_ACT_RB_TEST_MODE                         0x44
#define TC_ACT_RB_TEST_MODE_CMP                     0x45
#define TC_DEACT_RB_TEST_MODE                       0x46
#define TC_DEACT_RB_TEST_MODE_CMP                   0x47

#define TC_RESET_UE_POS_STORED_INFO                 0x48

#define TC_MSG_INVALID                              0x80


#define TC_CLOSE_TCH_LOOP_CMD                       0x00
#define TC_CLOSE_TCH_LOOP_ACK                       0x01
#define TC_OPEN_LOOP_CMD                            0x06
#define TC_CLOSE_MULTI_SLOT_LOOP_CMD                0x20
#define TC_CLOSE_MULTI_SLOT_LOOP_ACK                0x21
#define TC_OPEN_MULTI_SLOT_LOOP_CMD                 0x22
#define TC_OPEN_MULTI_SLOT_LOOP_ACK                 0x23
#define TC_ACT_EMMI_CMD                             0x0C
#define TC_ACT_EMMI_ACK                             0x0D
#define TC_DEACT_EMMI                               0x10
#define TC_TEST_INTERFACE                           0x14
#define TC_GPRS_TEST_MODE_CMD                       0x24
#define TC_EGPRS_START_RADIO_BLOCK_LOOPBACK_CMD     0x25



/***********************************
    ����RRC�����Ƿ���ڵĺ궨��
************************************/
#define    TC_RRC_CONN_STATUS_PRESENT    0x00                                   /* RRC Connection����                       */
#define    TC_RRC_CONN_STATUS_ABSENT     0x01                                   /* RRC Connection������                     */

/***********************************
    Define TC Globle Struct
************************************/
/* RAB_INFORMATION_STRU�Ѿ������ڽӿ��ļ��� */
typedef struct
{
    VOS_UINT8                 ucRBID;                                               /* LB ʵ���RBID                            */
    VOS_UINT16                usUpRlcSduSize;                                       /* LBʵ�����Ϣ                             */
} TC_LB_INFO_STRU;

typedef struct
{
    VOS_UINT32                  ulRabId;                                             /* RAB ID                                   */
    VOS_UINT32                  ulCnDomainId;                                        /* ��RAB����CN Domain                       */
    VOS_UINT32                  ulRbCnt;
    VOS_UINT32                  aulRbId[RRC_NAS_MAX_RB_PER_RAB];
}TC_RAB_INFORMATION_STRU;

    typedef struct
{
    VOS_UINT32                               ulRabCnt;                               /* ��ǰ����RAB������                        */
    TC_RAB_INFORMATION_STRU                  aRabInfo[TC_RABM_MAX_RAB_SETUP];        /* RABʵ����Ϣ                              */
}TC_RAB_INFO_STRU;

/* ģʽ��Ϣ */
typedef struct
{
    VOS_UINT8                               ucTcMode;                               /* mode1,mode2                              */
    VOS_UINT8                               ucLbNum;                                /* MODE1ʱ��Ч,��Ϣ�а���LB ��Ϣʱ��ʵ�����*/
    TC_LB_INFO_STRU                         aLBList[TC_LB_MAX_RBNUM];               /* LBʵ�����Ϣ                             */
}TC_MODE_INFO_STRU;

/* ȫ�ֿ�����Ϣ */
typedef struct
{
    TC_RAB_INFO_STRU                     TcRabInfo;                             /* RABʵ����Ϣ */
    TC_MODE_INFO_STRU                    TcModeInfo;                            /* ģʽ��Ϣ */
    VOS_UINT8                            ucTcState;                             /* TC������״̬ */
    VOS_UINT8                            ucMsgType;                             /* TC���յ�����Ϣ���� */
    VOS_UINT8                            ucCnDomain;                            /* TC���ĸ������Ͻ��յ���Ϣ */
    VOS_UINT8                            ucRrcConnStatus;                       /* RRC�����Ƿ���� */
    VOS_UINT8                            ucSndWphyCloseLoopNtfLable;            /* �Ƿ��Ѿ���������·��ջ�֪ͨ */
    VOS_UINT16                           usTchLoopType;                         /* TCH ���Ի������� */
}TC_GLOBAL_CTRL_STRU;


/*************************************************************************
                ���� TC �� L1 ֮�����Ϣԭ�Ｐ��Ϣ�ṹ��
**************************************************************************/
/************************************************
    TC ---> L1 : TC_CLOSE_TCH_LOOP_REQ_STRU
*************************************************/
/*ԭ��ID*/
#define     TC_CLOSE_TCH_LOOP_REQ          0xE701
/*TCH����ģʽ*/
#define     TC_TCH_LOOP_TYPE_A             0x0
#define     TC_TCH_LOOP_TYPE_B             0x1
#define     TC_TCH_LOOP_TYPE_C             0x2
#define     TC_TCH_LOOP_TYPE_D             0x3
#define     TC_TCH_LOOP_TYPE_E             0x4
#define     TC_TCH_LOOP_TYPE_F             0x5
#define     TC_TCH_LOOP_TYPE_G             0x6
#define     TC_TCH_LOOP_TYPE_H             0x7
#define     TC_TCH_LOOP_TYPE_I             0x8
#define     TC_TCH_LOOP_TYPE_ABNORMAL      0xFFFF
/*�ŵ�ģʽ*/
#define     TC_TCH_LOOP_ALLCHAN            0x0
#define     TC_TCH_LOOP_SUBCHAN            0x1

typedef struct
{
    VOS_UINT16      usMsgID;
    VOS_UINT16      usTchLoopType;          /*TCH����ģʽ*/
    VOS_UINT16      usSubChan;              /*�ŵ�ģʽ*/
    VOS_UINT16      usReserve;
}TC_CLOSE_TCH_LOOP_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    TC_CLOSE_TCH_LOOP_REQ_STRU          TcCloseTchLoopReq;
}TC_CLOSE_TCH_LOOP_REQ_MSG;


/************************************************
    L1 ---> TC : TC_CLOSE_TCH_LOOP_CNF_STRU
*************************************************/
/*ԭ��ID*/
#define     TC_CLOSE_TCH_LOOP_CNF           0x7E01
/*�ɹ����ı�־*/
#define     TC_CLOSE_TCH_LOOP_FAIL          0
#define     TC_CLOSE_TCH_LOOP_SUCCESS       1

typedef struct
{
    VOS_UINT16      usMsgID;
    VOS_UINT16      usCloseFlag;
}TC_CLOSE_TCH_LOOP_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER
    TC_CLOSE_TCH_LOOP_CNF_STRU          TcCloseTchLoopCnf;
}TC_CLOSE_TCH_LOOP_CNF_MSG;


/************************************************
    TC ---> L1 : TC_OPEN_TCH_LOOP_REQ_STRU
*************************************************/
/*ԭ��ID*/
#define     TC_OPEN_TCH_LOOP_REQ            0xE702

typedef struct
{
    VOS_UINT16      usMsgID;
    VOS_UINT16      usAckInfo;
}TC_OPEN_TCH_LOOP_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    TC_OPEN_TCH_LOOP_REQ_STRU           TcOpenTchLoopReq;
}TC_OPEN_TCH_LOOP_REQ_MSG;


/************************************************
    L1 ---> TC : TC_OPEN_TCH_LOOP_CNF_STRU
*************************************************/
/*ԭ��ID*/
#define     TC_OPEN_TCH_LOOP_CNF            0x7E02
/*�ɹ����ı�־*/
#define     TC_OPEN_TCH_LOOP_FAIL           0
#define     TC_OPEN_TCH_LOOP_SUCCESS        1

typedef struct
{
    VOS_UINT16      usMsgID;
    VOS_UINT16      usAckInfo;
    VOS_UINT16      usOpenFlag;
    VOS_UINT16      usReserve;
}TC_OPEN_TCH_LOOP_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER
    TC_OPEN_TCH_LOOP_CNF_STRU           TcOpenTchLoopCnf;
}TC_OPEN_TCH_LOOP_CNF_MSG;


/************************************************
    TC ---> L1 : TC_TEST_INTERFACE_REQ_STRU
*************************************************/
/*ԭ��ID*/
#define     TC_TEST_INTERFACE_REQ           0xE703
/*�����豸*/
#define     TC_TEST_DEVICE_0                0
#define     TC_TEST_DEVICE_1                1
#define     TC_TEST_DEVICE_2                2
#define     TC_TEST_DEVICE_3                4
#define     TC_TEST_DEVICE_ABNORMAL         0xFFFF

typedef struct
{
    VOS_UINT16      usMsgID;
    VOS_UINT16      usTestDevice;
}TC_TEST_INTERFACE_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    TC_TEST_INTERFACE_REQ_STRU          TcTestInterfaceReq;
}TC_TEST_INTERFACE_REQ_MSG;


/************************************************
    L1 ---> TC : TC_TEST_INTERFACE_CNF_STRU
*************************************************/
/*ԭ��ID*/
#define     TC_TEST_INTERFACE_CNF           0x7E03
/*�ɹ����ı�־*/
#define     TC_TEST_INTERFACE_FAIL          0
#define     TC_TEST_INTERFACE_SUCCESS       1

typedef struct
{
    VOS_UINT16      usMsgID;
    VOS_UINT16      usFlag;
}TC_TEST_INTERFACE_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER
    TC_TEST_INTERFACE_CNF_STRU          TcTestInterfaceCnf;
}TC_TEST_INTERFACE_CNF_MSG;


/************************************************
    TC ---> L1 : TC_TEST_MODE_W_TO_G_IND_STRU
*************************************************/
/*ԭ��ID*/
#define     TC_TEST_MODE_W_TO_G_IND           0xE704

typedef struct
{
    VOS_UINT16      usMsgID;
    VOS_UINT8       aucReserve[2];
}TC_TEST_MODE_W_TO_G_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    TC_TEST_MODE_W_TO_G_IND_STRU         TcTestModeWToGInd;
}TC_TEST_MODE_W_TO_G_IND_MSG;




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

#endif  /* TC_RESOURCE_INFO_H_ */

