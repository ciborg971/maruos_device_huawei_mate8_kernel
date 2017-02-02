

#ifndef _PHY_GRM_INTERFACE_H_
#define _PHY_GRM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "EdgeInterface.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*====================*/ /* ��ϢID���� */
enum GRM_PHY_MSG_ID_ENUM
{
    /* GRM��PHY֮���ԭ�� */
    ID_PHP_UL_START_TIME_IND                = 0x7506,   /*_H2ASN_MSGChoice PHP_START_TIME_IND*/
    ID_PHP_DL_START_TIME_IND                = 0x7501,   /*_H2ASN_MSGChoice PHP_START_TIME_IND*/
    ID_PHP_PACKET_SEND_IND                  = 0x7503,   /*_H2ASN_MSGChoice PHP_PACKET_SEND_IND*/
    ID_PHP_PACKET_DATA_REQ                  = 0x5701,   /*_H2ASN_MSGChoice PHP_PACKET_DATA_REQ*/
    ID_PHP_PACKET_DATA_IND                  = 0x7502,   /*_H2ASN_MSGChoice PHP_PACKET_DATA_IND*/
    ID_PHP_RRBP_FN_REQ                      = 0x5703,   /*_H2ASN_MSGChoice PHP_RRBP_FN_REQ*/
    ID_PHY_RRBP_FN_IND                      = 0x7507,   /*_H2ASN_MSGChoice PHY_RRBP_FN_IND*/
    ID_PHP_RRBP_MSG_REQ                     = 0x5702,   /*_H2ASN_MSGChoice PHP_RRBP_MSG_REQ*/
    ID_PHP_RRBP_MSG_CNF                     = 0x7505,   /*_H2ASN_MSGChoice PHP_RRBP_MSG_CNF*/
    ID_PHP_EGPRS_SRB_REQ                    = 0x5706,   /*EGPRS Srb����ģʽʱ������㷢�ͻ�������*/
    ID_PHP_EGPRS_SRB_CNF                    = 0x7508,   /*EGPRS Srb����ģʽʱ�������Ի��������ȷ��*/
    ID_PHP_HARQ_INFO_IND                    = 0x5707,   /*PHP_HARQ_INFO_IND_MSG ֪ͨ������������ݿ��״̬���Ա��䴦��HARQ����*/
    ID_PHP_RRBP_MSG_BUTT
};

typedef VOS_UINT16 GRM_PHY_MSG_ID_ENUM_UINT16;


/*====================*/ /* �������� */
#define GRM_BLKDATA_MAX_SIZE                40          /* GRMÿ�����ݿ���32����Ϊ��λ�ĸ��� */
#define GRM_UL_BSN_CNF_MAX_NUM              8           /* һ�����ȷ��RLC���ݿ��ӦBSN�ĸ��� */

/*�����������λ��Ϣ����BSN����rrbp���ͳɹ�*/
#define GRM_BSN_FOR_RRBP                    0x88FF

/*�����������λ��Ϣ����BSN�������п��ƿ鷢�ͳɹ�*/
#define GRM_BSN_FOR_UL_CTRL                 0x66FF

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/*================*/ /* ��׷�ʽö�� */
enum PHY_EGPRS_PS_ENUM
{
    PHY_EGPRS_PS_1                          = 0,
    PHY_EGPRS_PS_2                          = 1,
    PHY_EGPRS_PS_3                          = 2,
    PHY_EGPRS_PS_BUTT
};

typedef VOS_UINT16 PHY_EGPRS_PS_ENUM_UINT16;

/* ע�⣬������������Э��ջʹ�ã�����㲻��ʹ��UINT8���� */
typedef VOS_UINT8  PHY_EGPRS_PS_ENUM_UINT8;


/*================*/ /* ������ö�� */
enum PHY_ERR_CODE_ENUM
{
    PHY_ERR_CODE_ALL_OK                     = 0,    /*0: û�д���*/
    PHY_ERR_CODE_HDR_OK_DATA1_ERR           = 1,    /*1: ͷ����ȷ�����ݿ�һ����*/
    PHY_ERR_CODE_HDR_OK_DATA2_ERR           = 2,    /*2��ͷ����ȷ�����ݿ������*/
    PHY_ERR_CODE_HDR_OK_DATA_ALL_ERR        = 3,    /*3��ͷ����ȷ�����ݿ�ȫ������*/
    PHY_ERR_CODE_ALL_ERR                    = 4     /*4��ͷ��������ȫ������*/
};
typedef VOS_UINT16 PHY_ERR_CODE_ENUM_UINT16;

/*================*/ /* ��������ö�� */
enum PHY_DECODE_DATA_TYPE_ENUM
{
    PHY_DECODE_DATA_TYPE_NORMAL             = 0,    /*0: �������룻*/
    PHY_DECODE_DATA_TYPE_HARQ               = 1,    /*1: HARQ���룻*/
    PHY_DECODE_DATA_TYPE_BUTT               = 2
};
typedef VOS_UINT16 PHY_DECODE_DATA_TYPE_ENUM_UINT16;

enum EDGE_HARQ_DATA_STATUS
{
    EDGE_HARQ_DATA_STATUS_FULL_RXED         = 0,    /* ��ӦBSN�����ݿ�, ȫ��������ȷ */
    EDGE_HARQ_DATA_STATUS_NOT_RXED          = 1,    /* ��ӦBSN�����ݿ�, û��������ȷ */
    EDGE_HARQ_DATA_STATUS_BUTT
};
typedef VOS_UINT16 EDGE_HARQ_DATA_STATUS_UINT16;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
#pragma pack(4)

typedef struct
{
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;            /*_H2ASN_MsgChoice_Export      GRM_PHY_MSG_ID_ENUM_UINT16*/
    VOS_UINT16                              usMsgBlock;
    /******************************************************************************************************
        _H2ASN_MsgChoice_When_Comment          GRM_PHY_MSG_ID_ENUM_UINT16
    ******************************************************************************************************/
}GRM_PHY_MSG_DATA;
/*_H2ASN_Length UINT32*/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_DATA                        stMsgData;
}PhyGrmInterface_MSG;

/*================*/ /* PHP_START_TIME_IND��Ϣ�ṹ */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;            /*_H2ASN_Skip*/
    VOS_UINT16                              usRsv;
    VOS_UINT32                              ulFN;               /* Starting time֡�ţ�GRM���ݴ�֡�ž����Ǽ�������tbf,
                                                                   ��������tbf��������������tbfͬʱ����*/
}PHP_START_TIME_IND;

/*================*/ /* ���ݿ�ṹ */
typedef struct
{
    VOS_UINT16                              usBsn1;                             /* EGPRS��ָBSN1,GPRS��ָBSN */
    VOS_UINT16                              usBsn2;                             /* EGPRS��ʹ��MCS7-MCS9ʱ��Ч */
    EDGE_CODE_SCHEME_ENUM_UINT16            enCodeScheme;                       /* ���ƺͱ��뷽ʽ */
    PHY_EGPRS_PS_ENUM_UINT16                enPS1;                              /* EGPRS����Ч����һ����׷�ʽ */
    PHY_EGPRS_PS_ENUM_UINT16                enPS2;                              /* EGPRS����Ч���ڶ�����׷�ʽ��ֻ��MCS7-MCS9ʹ�� */
    VOS_UINT16                              usStatusRpt;                        /* ���ݿ鷢������Ҫ��GRR���͵�״̬���� */
    VOS_UINT32                              aulBlkData[GRM_BLKDATA_MAX_SIZE];   /* GRPS��EGPRS RLC/MAC�� */
}BLK_ENCODE_DATA_ST;

/*================*/ /* PHP_PACKET_DATA_REQ��Ϣ�ṹ */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    VOS_UINT16                              usBlkNum;                           /* ���͵����ݿ���   */
    BLK_ENCODE_DATA_ST                      astBlkData[EDGE_UL_TS_MAX_NUM];
}PHP_PACKET_DATA_REQ;

/*================*/ /* BLK_DECODE_DATA_ST�ṹ */
typedef struct
{
    VOS_UINT16                              usTN;                               /* �������ݵ�ʱ϶�� */
    EDGE_CODE_SCHEME_ENUM_UINT16            enCodeScheme;                       /* ���ƺͱ��뷽ʽ */
    PHY_ERR_CODE_ENUM_UINT16                enErrCode;                          /* 0: û�д���1:ͷ����ȷ�����ݿ�һ����2��ͷ����ȷ�����ݿ������3��ͷ����ȷ�����ݿ�ȫ������4��ͷ��������ȫ������Ŀ����Ϊ�˻�ȡ���ܵ�RRBPָʾ */
    PHY_DECODE_DATA_TYPE_ENUM_UINT16        enDecodeDataType;                   /* ��������ö��,ö��ֵ�����ڵ�8λ,��ʾ��������;��8λ��ʾTFI�Ƿ�ƥ��.1:���Լ�������,0:�����Լ������� */
    VOS_UINT32                              aulBlkData[GRM_BLKDATA_MAX_SIZE];   /* GRPS��EGPRS RLC/MAC��*/
}BLK_DECODE_DATA_ST;

/*================*/ /* PHP_RRBP_FN_REQ��Ϣ�ṹ */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    EDGE_YES_OR_NO_ENUM_UINT16              enRptMeas;                          /* �Ƿ���Ҫ�ϱ��������� */
    VOS_UINT32                              ulFN;                               /* ����RRBP��Ϣ�Ŀ����ڵ���֡֡�� */
}PHP_RRBP_FN_REQ;

/*================*/ /* PHY_RRBP_FN_IND��Ϣ�ṹ */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    VOS_UINT16                              usRsv;
    VOS_UINT32                              ulFN;                               /* ����RRBP��֡�� */
}PHY_RRBP_FN_IND;


/*================*/ /* PHP_EGPRS_SRB_REQ��Ϣ�ṹ */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgId;
    VOS_UINT16                              usSrbPara;
}PHP_EGPRS_SRB_REQ;

/*================*/ /* PHP_EGPRS_SRB_CNF��Ϣ�ṹ */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgId;
    VOS_UINT16                              usRsv;
}PHP_EGPRS_SRB_CNF;

/*================*/ /* PHP_PACKET_SEND_IND_MSG��Ϣ�ṹ */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    EDGE_YES_OR_NO_ENUM_UINT16              enPrefetchPresent;                  /* Prefetch���Ƿ���Ч��EDGE_YES:��Ч��EDGE_NO:��Ч */
    VOS_UINT16                              usPrefetchNum;                      /* Ԥȡ�Ŀ��� */
    EDGE_YES_OR_NO_ENUM_UINT16              enCnfPresent;                       /* cnf���Ƿ���Ч��EDGE_YES:��Ч��EDGE_NO:��Ч */
    VOS_UINT32                              ulFN;                               /* ���ݿ鷢���������߿��FN1������2֡��֡�Ű���FN0��FN1��FN2��FN3��ţ�,������һ���FN1 */
    VOS_UINT16                              usCtrlBlkSentNum;                   /* ��һ���������У� ��8λ: ����RRBP��Ϣ����Ŀ; ��8λ: �ж���USF���ڷ��Ϳ�����Ϣ */
    VOS_UINT16                              usDataBlkSentNum;                   /* ��һ���������У��ж��ٸ�USF���ڷ������ݿ� */
    VOS_UINT16                              usStatusRpt;                        /* �������Ҫ���ص�״̬���� */
    VOS_UINT16                              usCnfBsnNum;                        /* ��һ���������У������˶��ٸ�RLC PDU�����ж��ٸ�BSN */
    VOS_UINT16                              ausCnfBsn[GRM_UL_BSN_CNF_MAX_NUM];  /* ��������ЩRLC���BSN�� */
}PHP_PACKET_SEND_IND_MSG;

/*================*/ /* PHP_PACKET_DATA_IND_MSG��Ϣ�ṹ */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    VOS_UINT16                              usBlkNum;                           /* �ϱ������ݿ��� */
    VOS_UINT32                              ulFN;                               /* �������ݵ���֡֡�� */
    BLK_DECODE_DATA_ST                      astBlkData[EDGE_DL_TS_MAX_NUM];
}PHP_PACKET_DATA_IND_MSG;

/*================*/ /* PHP_RRBP_MSG_REQ_MSG��Ϣ�ṹ */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    VOS_UINT16                              usTN;                               /* ����ʱ϶�� */
    VOS_UINT32                              ulFN;                               /* ���Ϳ����ڵ���֡֡�� */
    PHY_BURST_TPYE_ENUM_UINT16              enBurstType;                        /* RRBP��Ϣ���ʽ���� */
    GRR_RRBP_CNF_ENUM_UINT16                enRrbpCnf;                          /* �������PHP_RRBP_MSG_CNF��Ϣ�н���ֵ���ظ�GRM��GRM�����ж��Ƿ���Ҫ��GRR�ظ� */
    EDGE_YES_OR_NO_ENUM_UINT16              enMeasRpted;                        /* ��RRBP��Ϣ���Ƿ����˲������档EDGE_YES:�����ˣ�EDGE_NO:û�з��� */
    EDGE_YES_OR_NO_ENUM_UINT16              enCtrlRrbpMsgFlag;                  /* �Ƿ�Ϊ���ƿ�RRBP��Ϣ��־��EDGE_YES:�ǣ�EDGE_NO:�� */
    VOS_UINT16                              ausData[12];                        /* �����Ϊ23�ֽ� */
}PHP_RRBP_MSG_REQ_MSG;

/*================*/ /* PHP_RRBP_MSG_CNF_MSG��Ϣ�ṹ */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    GRR_RRBP_CNF_ENUM_UINT16                enRrbpID;                           /* RRBP��Ϣ�ظ����ͣ���ʾ�Ƿ���Ҫ��
                                                                                   GRR�ظ�����ֵ����PHP_RRBP_MSG_REQ�д��������� */
    EDGE_CNF_RESULT_ENUM_UINT16             enErrInd;                           /* EDGE_CNF_RESULT_FAIL����ʾ�ɹ���EDGE_CNF_RESULT_FAIL��ʾʧ�ܣ�*/
    VOS_UINT16                              usRsv;
    VOS_UINT32                              ulFN;                               /* ����RRBP��֡�ţ��Ա�֪������һ��
                                                                                   RRBP����ȥ�ˣ�������� */
}PHP_RRBP_MSG_CNF_MSG;

/*================*/ /* PHP_HARQ_INFO_IND_MSG ��Ϣ�ṹ */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    VOS_UINT16                              usBsn;
    EDGE_HARQ_DATA_STATUS_UINT16            enDataStatus;                       /* ���ݿ������� */
    VOS_UINT16                              usRsv;
}PHP_HARQ_INFO_IND_MSG;

/****************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
#ifdef FEATURE_DSP2ARM
extern VOS_UINT32 GPHY_GetGprsDataBufWriteIdxAddr(VOS_VOID);
extern VOS_UINT32 GPHY_GetGprsDataBufReadIdxAddr(VOS_VOID);
extern VOS_UINT32 GPHY_GetGprsDataBufMutexAddr(VOS_VOID);
extern VOS_UINT32 GPHY_GetGprsDataBufAddr(VOS_VOID);
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of PhyGrmInterface.h*/

