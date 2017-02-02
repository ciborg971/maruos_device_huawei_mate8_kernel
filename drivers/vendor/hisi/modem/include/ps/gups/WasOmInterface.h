/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : WasOmInterface.h
  �� �� ��   : ����
  ��    ��   : WAS_SMC_GetLastestDomain
  ��������   : 2010��5��5��
  ����޸�   :
  ��������   : WasMntnMsg.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��5��5��
    ��    ��   : WAS_SMC_GetLastestDomain
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __WASOMINTERFACE_H__
#define __WASOMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ��ӡ��¼������ */
#define WAS_PRINT_MSG_MAX_NUM           10


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : WAS_MNTN_RPT_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  :����С����Ϣ������
*****************************************************************************/
enum WAS_MNTN_OM_OUT_OF_SERVICE_ENUM
{
    WAS_MNTN_OM_IN_SERVICE              = 0,
    WAS_MNTN_OM_OUT_SERVICE                ,
    WAS_MNTN_OM_SERVICE_BUTT
};
typedef VOS_UINT8 WAS_MNTN_OM_OUT_OF_SERVICE_ENUM_UINT8;

/*****************************************************************************
 ö����    : WAS_MNTN_RPT_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  :����С����Ϣ������
*****************************************************************************/
enum WAS_MNTN_RPT_TYPE_ENUM
{
    WAS_MNTN_RPT_ONLYONE              = 0,
    WAS_MNTN_RPT_FOR_CHANGE              ,
    WAS_MNTN_RPT_PERIOD                  ,
    WAS_MNTN_RPT_TYPE_BUTT
};
typedef VOS_UINT8 WAS_MNTN_RPT_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����    : WAS_MNTN_RPT_CMD_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  :��ʼ��ѯ����ֹͣ��ѯ����
*****************************************************************************/
enum WAS_MNTN_RPT_CMD_ENUM
{
    WAS_MNTN_RPT_STOP                 = 0,
    WAS_MNTN_RPT_START
};
typedef VOS_UINT8 WAS_MNTN_RPT_CMD_ENUM_UINT8;

/*****************************************************************************
 ö����    : WAS_PRINT_LEVEL_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ��ӡ����
*****************************************************************************/
enum WAS_PRINT_LEVEL_ENUM
{
    WAS_PRINT_LEVEL_NO_PRINT        = 0 ,
    WAS_PRINT_LEVEL_ERROR               ,
    WAS_PRINT_LEVEL_WARNING             ,
    WAS_PRINT_LEVEL_NORMAL              ,
    WAS_PRINT_LEVEL_INFO                ,
    WAS_PRINT_LEVEL_BUTT

};
typedef VOS_UINT16 WAS_PRINT_LEVEL_ENUM_UINT16;

/*****************************************************************************
 ö����    : WAS_OM_MSG_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :WAS_MNTN_INTRA_TRANS_SUBMSG_ENUM_UINT16
 ö��˵��  : OM->WAS֮���͸����Ϣ,͸����ϢWASģ��ID��8λ��ʾWAS���B0�̶���
            ��8���ʾ��ϢID
*****************************************************************************/
enum WAS_OM_MSG_TYPE_ENUM
{

    /*��ӡ���Ƽ���*/
    ID_OM_WAS_PRINT_LEVEL_CTRL_REQ                  = 0xB000,
    ID_WAS_OM_PRINT_LEVEL_CTRL_CNF                  = 0xB001,

    /* ��Ƶ͸������  */
    ID_OM_WAS_FREQ_LOCK_REQ                         = 0xB002,                   /*OM_WAS_FREQ_LOCK_REQ_STRU*/
    ID_WAS_OM_FREQ_LOCK_CNF                         = 0xB003,

    /* ����͸������  */
    ID_OM_WAS_ENCRYPT_REQ                           = 0xB004 ,
    ID_WAS_OM_ENCRYPT_CNF                           = 0xB005 ,

    /* ͷѹ��͸������  */
    ID_OM_WAS_COMPRESS_REQ                          = 0xB006 ,
    ID_WAS_OM_COMPRESS_CNF                          = 0xB007  ,

    /* ���ʿ���͸������  */
    ID_OM_WAS_POWERCTRL_REQ                         = 0xB008 ,
    ID_WAS_OM_POWERCTRL_CNF                         = 0xB009 ,


    /* ��С���ͼ���������͸������  */
    ID_OM_WAS_ACT_OR_SERV_CELL_INFO_REQ             = 0xB010 ,          /*_H2ASN_MsgChoice OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU*/
    ID_WAS_OM_ACT_OR_SERV_CELL_INFO_CNF             = 0xB011 ,          /*_H2ASN_MsgChoice WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU*/
    ID_WAS_OM_ACT_OR_SERV_CELL_INFO_IND             = 0xB012 ,          /*_H2ASN_MsgChoice WAS_OM_ACT_OR_SERV_CELL_INFO_IND_STRU*/

    /* W�����������͸������*/
    ID_OM_WAS_W_NCELL_INFO_REQ                      = 0xB013 ,          /*_H2ASN_MsgChoice OM_WAS_W_NCELL_INFO_REQ_STRU*/
    ID_WAS_OM_W_NCELL_INFO_CNF                      = 0xB014,           /*_H2ASN_MsgChoice WAS_OM_W_NCELL_INFO_CNF_STRU*/
    ID_WAS_OM_W_NCELL_INFO_IND                      = 0xB015 ,          /*_H2ASN_MsgChoice WAS_OM_W_NCELL_INFO_IND_STRU*/

    /* G �����������͸������*/
    ID_OM_WAS_G_NCELL_INFO_REQ                      = 0xB016 ,          /*_H2ASN_MsgChoice OM_WAS_G_NCELL_INFO_REQ_STRU*/
    ID_WAS_OM_G_NCELL_INFO_CNF                      = 0xB017 ,          /*_H2ASN_MsgChoice WAS_OM_G_NCELL_INFO_CNF_STRU*/
    ID_WAS_OM_G_NCELL_INFO_IND                      = 0xB018 ,          /*_H2ASN_MsgChoice WAS_OM_G_NCELL_INFO_IND_STRU*/

    /*��ѯWCDMAС���仯����*/
    ID_OM_WAS_W_CELL_CHG_INFO_REQ                   = 0xB019 ,          /*_H2ASN_MsgChoice OM_WAS_W_CELL_CHG_INFO_REQ_STRU*/
    ID_WAS_OM_W_CELL_CHG_INFO_CNF                   = 0xB01A ,          /*_H2ASN_MsgChoice WAS_OM_W_CELL_CHG_INFO_CNF_STRU*/
    ID_WAS_OM_W_CELL_CHG_INFO_IND                   = 0xB01B ,          /*_H2ASN_MsgChoice WAS_OM_W_CELL_CHG_INFO_IND_STRU*/


    /*��ѯUE״̬*/
    ID_OM_WAS_UE_STATE_REQ                          = 0xB01C ,          /*_H2ASN_MsgChoice OM_WAS_UE_STATE_REQ_STRU*/
    ID_OM_WAS_UE_STATE_CNF                          = 0xB01D ,          /*_H2ASN_MsgChoice WAS_OM_UE_STATE_CNF_STRU*/
    ID_WAS_OM_UE_STATE_IND                          = 0xB01E ,          /*_H2ASN_MsgChoice WAS_OM_UE_STATE_IND_STRU*/


    /*�տ���Ϣ����*/
    ID_OM_WAS_OTA_REQ                               = 0XB020,                   /*OM_WAS_OTA_REQ_STRU*/
    ID_WAS_OM_OTA_CNF                               = 0XB021,                   /*WAS_OM_OTA_CNF_STRU*/
    ID_WAS_OM_OTA_IND                               = 0XB022,


    ID_WAS_OM_WCDMA_WORK_MODE_REQ                   = 0XB027,                   /*OM_WAS_UE_WORK_MODE_REQ_STRU*/
    ID_OM_WAS_WCDMA_WORK_MODE_CNF                   = 0XB028,                   /*OM_WAS_UE_WORK_MODE_CNF_STRU*/

    ID_WAS_FREQ_LOCK_IND                            = 0xB035,
    ID_WAS_FIXED_DATA_RECUR                         = 0xeeee,
    ID_WAS_ALL_DATA_IND                             = 0xB037,
    ID_OM_WAS_CONNECTED_IND                         = 0xaaaa,
    ID_WAS_OM_CONNECTED_CNF                         = 0xaaab,

    /* ��ӡ������Ϣ */
    ID_WAS_PRINT_MSG                                = 0xB040,                   /*_H2ASN_MsgChoice WAS_PRINT_MSG_STRU */

    ID_WAS_AFC_INFO_IND                             = 0xB050,
    ID_WAS_JAM_DETECT_INFO_IND                      = 0xB051,                   /*_H2ASN_MsgChoice WAS_JAM_DETECT_INFO_STRU */
    /* LTE��֧�ֵ�Ƶ���б� */
    ID_WAS_LTE_UNSUPPORT_FREQ                       = 0xB052,                   /*_H2ASN_MsgChoice WAS_UNSUPPORT_EUTRA_ARFCN_LIST_STRU */

    ID_WAS_CSS_BAND_INFO_IND                        = 0xB053,
    ID_WAS_FFT_PLMN_BAND_INFO_IND                   = 0xB054,

    ID_WAS_OM_CELL_INDI_OFFSET_MODIFY_INFO_IND      = 0xB055,

    ID_WAS_AM_SRB_SEND_STATE_INFO_IND               = 0xB056,

    /* LTE�����������͸������*/
    ID_OM_WAS_L_NCELL_INFO_REQ                      = 0xB060 ,          /*_H2ASN_MsgChoice OM_WAS_L_NCELL_INFO_REQ_STRU*/
    ID_WAS_OM_L_NCELL_INFO_CNF                      = 0xB061 ,          /*_H2ASN_MsgChoice WAS_OM_L_NCELL_INFO_CNF_STRU*/
    ID_WAS_OM_L_NCELL_INFO_IND                      = 0xB062 ,          /*_H2ASN_MsgChoice WAS_OM_L_NCELL_INFO_IND_STRU*/

    /* SECOND CELL�����������͸������*/
    ID_OM_WAS_SECOND_CELL_INFO_REQ                  = 0xB063 ,          /*_H2ASN_MsgChoice OM_WAS_SECOND_CELL_INFO_REQ_STRU*/
    ID_WAS_OM_SECOND_CELL_INFO_CNF                  = 0xB064 ,          /*_H2ASN_MsgChoice WAS_OM_SECOND_CELL_INFO_CNF_STRU*/
    ID_WAS_OM_SECOND_CELL_INFO_IND                  = 0xB065 ,          /*_H2ASN_MsgChoice WAS_OM_SECOND_CELL_INFO_IND_STRU*/

    /* ��ʱ���¼��ϱ����� */
    ID_OM_WAS_TIMER_EVENT_REQ                       = 0xB066 ,          /*_H2ASN_MsgChoice OM_WAS_TIMER_EVENT_REQ_STRU*/
    ID_WAS_OM_TIMER_EVENT_CNF                       = 0xB067 ,          /*_H2ASN_MsgChoice WAS_OM_TIMER_EVENT_CNF_STRU*/

    WAS_OM_MSG_TYPE_ENUM_BUTT
};
typedef VOS_UINT16 WAS_OM_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : WAS_OM_STATE_IND_ENUM_UINT8
 Э����  :
 ASN.1���� : WAS_OM_STATE_IND_ENUM_UINT8
 ö��˵��  : WAS->OM֮��RRC״ָ̬ʾ(R8Э������)
*****************************************************************************/
enum WAS_OM_STATE_IND_ENUM
{
    WAS_OM_STATE_CELL_DCH                   = 0,
    WAS_OM_STATE_CELL_FACH                  = 1,
    WAS_OM_STATE_CELL_PCH                   = 2,
    WAS_OM_STATE_URA_PCH                    = 3,
    WAS_OM_STATE_IDLE                       = 4,
    WAS_OM_STATE_E_CELL_FACH                = 5,
    WAS_OM_STATE_E_CELL_PCH_WITHOUT_HRNTI   = 6,
    WAS_OM_STATE_E_URA_PCH                  = 7,
    WAS_OM_STATE_E_CELL_PCH_WITH_HRNTI      = 8,
    WAS_OM_STATE_BUTT

};
typedef VOS_UINT8 WAS_OM_STATE_IND_ENUM_UINT8;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*======================= ����Ϊ�����͸������Ľṹ ======================*/

/*****************************************************************************
 �ṹ��    : DIAG_WAS_MSG_COMM_HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32                      ulMsgId;

    VOS_UINT16                      usOriginalId;
    VOS_UINT16                      usTerminalId;
    VOS_UINT32                      ulTimeStamp;
    VOS_UINT32                      ulSN;
} DIAG_WAS_MSG_COMM_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : OM_WAS_OTA_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �տ���Ϣ��������
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    VOS_UINT32                          ulOnOff;                                /* 0 - ֹͣ�ϱ�����WAS�տ���Ϣ; 1 - �����ϱ�����WAS�տ���Ϣ */
}OM_WAS_OTA_REQ_STRU;


/*****************************************************************************
 �ṹ��    : WAS_OM_OTA_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �տ���Ϣ���ٻظ�
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    VOS_UINT32                          ulErrCode;                              /* ������Ϣ������:0���տ���Ϣ�������óɹ�; 1���տ���Ϣ��������ʧ�� */
}WAS_OM_OTA_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WAS_MNTN_SUB_MODE_PRINT_LEVEL_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ģ���ӡ�������
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    VOS_UINT32                          enMidId;                                    /* ģ��ID:WAS_MID_ENUM_UINT32,���ܰ���WasGlobal.h,�ʴ˴���ʹ�ø�ö�ٽ��ж���   */
    WAS_PRINT_LEVEL_ENUM_UINT16         enPrintLevel;                               /* ��ӡ���� */
    VOS_UINT8                           aucReserved[2];

}OM_WAS_PRINT_LEVEL_CTRL_REQ_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_PRINT_LEVEL_CTRL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WAS_OM_OTA_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ٵĿտ���Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usOtaMsgID;         /*�տ���Ϣ��ID��*/
    VOS_UINT8                           ucUpDown;           /*�տ���Ϣ�ķ���*/
    VOS_UINT8                           ucReserved;         /*�߼��ŵ�����*/
    VOS_UINT32                          ulLengthASN;        /*�տ���Ϣ���ݵĳ���*/
    VOS_UINT8                           aucData[4];         /*���ٵĿտ���Ϣ����*/

}WAS_OM_OTA_IND_STRU;

/*****************************************************************************
 �ṹ��    : OM_WAS_FREQ_LOCK_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-��Ƶ
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    VOS_UINT16                          usLockedFreq;                           /* Ҫ������Ƶ�ʣ�0xffff��ʾ������,����ֵ��ʾҪ������Ƶ�� */
    VOS_UINT8                           aucReserved1[2];

} OM_WAS_FREQ_LOCK_REQ_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_FREQ_LOCK_CNF_STRU;

/*****************************************************************************
 �ṹ��    : OM_WAS_POWER_CTRL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-���ʿ���
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    PS_BOOL_ENUM_UINT8                  enPowerCtrlFlag;                        /* �Ƿ��������ر�ʶ��PS_FALSE(0)�����������أ� PS_TRUE(1)���������� */
    VOS_UINT8                           aucReserved1[3];

} OM_WAS_POWER_CTRL_REQ_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_POWER_CTRL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : OM_WAS_ENCRYPT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-����
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    PS_BOOL_ENUM_UINT8                  enEncryptFlag;                          /* �Ƿ��������ܱ�ʶ��PS_FALSE(0)�����������ܣ� PS_TRUE(1)���������� */
    VOS_UINT8                           aucReserved1[3];

} OM_WAS_ENCRYPT_REQ_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_ENCRYPT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : OM_WAS_COMPRESS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-ͷѹ��RFC2507
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    PS_BOOL_ENUM_UINT8                  enCompressFlag;                         /* �Ƿ�����ͷѹ����ʶ��PS_FALSE(0)��������ͷѹ���� PS_TRUE(1)������ͷѹ�� */
    VOS_UINT8                           aucReserved1[3];

} OM_WAS_COMPRESS_REQ_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_COMPRESS_CNF_STRU;

/*********************************����ͬWCDMA�����ϱ��й�***************************/

/*****************************************************************************
 �ṹ��    : OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-��С����������Req��Ϣ
*****************************************************************************/

typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    WAS_MNTN_RPT_CMD_ENUM_UINT8         enCommand;                              /*��ʼ��ֹͣ�ϱ�*/
    WAS_MNTN_RPT_TYPE_ENUM_UINT8        enReportType;                           /*һ���ϱ��������ϱ����߱仯�ϱ�*/
    VOS_UINT16                          usReportPerio;                          /*��������ϱ��������ڳ���*/
} OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU;


/*****************************************************************************
 �ṹ��    : WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-��С����������Cnf��Ϣ
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    PS_RSLT_CODE_ENUM_UINT32            enRslt;                                 /* ���ز�ѯ�ṹ�ɹ���ʧ�� */
    VOS_UINT8                           aucReserved[3];
    WAS_MNTN_RPT_TYPE_ENUM_UINT8        enReportType;                           /*һ���ϱ��������ϱ����߱仯�ϱ�*/
}WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-WCDMA С��������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usCellFreq;

    VOS_UINT16                         usCellPSC;

    VOS_INT16                          sCpichRscp;

    VOS_INT16                          sCpichEcN0;

    VOS_UINT16                         usCellIndex;

    VOS_INT16                          sCellRssi;                               /* �������ϱ���ǰ��С����RSSIֵ */

    PS_BOOL_ENUM_UINT8                 enHsdpaFlg;                              /* �Ƿ��ѽ�DPA�ŵ� */

    PS_BOOL_ENUM_UINT8                 enHsupaFlg;                              /* �Ƿ��ѽ�UPA�ŵ� */

    VOS_INT16                          sRValue;                                 /* ������Rֵ*/

    VOS_INT16                          sHValue;                                 /* ������Hֵ*/

    PS_BOOL_ENUM_UINT8                 enTreselFlg;                             /* �Ƿ�������Treselection��ʱ�� */

    PS_BOOL_ENUM_UINT8                 enTevaluateFlg;                          /* �Ƿ�������Tevaluate��ʱ�� */

    PS_BOOL_ENUM_UINT8                 enTnFlg;                                 /* �Ƿ�������Tn��ʱ�� */

    PS_BOOL_ENUM_UINT8                 enDetectCellFlg;                         /* �Ƿ���DETECTС���ı�� */

    PS_BOOL_ENUM_UINT8                 enBlackCellFlg;                          /* ��ǰ�����Ƿ񱻼����������������ѡ�������� */
    VOS_UINT8                          ucSscDisableMeas;                        /* SSC Disable��Ƶ\GSM���� */
}WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU;


/*****************************************************************************
 �ṹ��    : WAS_OM_ACT_OR_SERV_CELL_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-��С����������Ind��Ϣ

            WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usReserved;

    VOS_UINT8                               aucReserved[3];
    WAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;
    VOS_UINT16                              usMeasQuantity;

     /* ���usCellNumΪN��N > 0������ʾ������ж��С����
        ��ʱaucActOrServeCellInfo�д���N��С��
        WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU����Ϣ,�˴�
        ռ��4���ֽڵ�λ��*/
    VOS_UINT16                              usCellNum;      /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNCellNum */

    VOS_UINT8                               aucActOrServeCellInfo[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU MINIDX:1 MAXIDX:6 EXPORTNAME:usH2ASNCellNum
    ******************************************************************************************************/
}WAS_OM_ACT_OR_SERV_CELL_INFO_IND_STRU;


/*****************************************************************************
 �ṹ��    : OM_WAS_W_NCELL_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-W�����ϱ�Req��Ϣ
*****************************************************************************/
typedef OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU OM_WAS_W_NCELL_INFO_REQ_STRU;


/*****************************************************************************
 �ṹ��    : WAS_OM_W_NCELL_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-W��������Cnf��Ϣ
*****************************************************************************/
typedef WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU WAS_OM_W_NCELL_INFO_CNF_STRU;


/*****************************************************************************
 �ṹ��    : WAS_OM_W_NCELL_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-W��������Ind��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usReserved;

    VOS_UINT8                               aucReserved[3];
    WAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;
    VOS_UINT16                              usMeasQuantity;

    /* ���usCellNumΪN��N > 0������ʾ�������ж��С����
       ��ʱaucWcdmaNeighberCellInfo�д���N��С��
       WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU����Ϣ,�˴�
       ռ��4���ֽڵ�λ��*/

    VOS_UINT16                              usCellNum;  /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNCellNum */

    VOS_UINT8                               aucWcdmaNeighberCellInfo[4];

    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU MINIDX:1 MAXIDX:8 EXPORTNAME:usH2ASNCellNum
    ******************************************************************************************************/

} WAS_OM_W_NCELL_INFO_IND_STRU;


/*****************************************************************************
 �ṹ��    : OM_WAS_G_NCELL_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-G�����ϱ�Req��Ϣ
*****************************************************************************/
typedef OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU OM_WAS_G_NCELL_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : OM_WAS_L_NCELL_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����ϢLTE�����ϱ�Req��Ϣ
*****************************************************************************/
typedef OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU OM_WAS_L_NCELL_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : OM_WAS_SECOND_CELL_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����ϢSecond cell info�����ϱ�Req��Ϣ
*****************************************************************************/
typedef OM_WAS_ACT_OR_SERV_CELL_INFO_REQ_STRU OM_WAS_SECOND_CELL_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WAS_OM_W_NCELL_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-W��������Cnf��Ϣ
*****************************************************************************/
typedef WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU WAS_OM_G_NCELL_INFO_CNF_STRU;


/*****************************************************************************
 �ṹ��    : WAS_OM_L_NCELL_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-W��������Cnf��Ϣ
*****************************************************************************/
typedef WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU WAS_OM_L_NCELL_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WAS_OM_SECOND_CELL_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-Second Cell��������Cnf��Ϣ
*****************************************************************************/
typedef WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU WAS_OM_SECOND_CELL_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WAS_MNTN_REPORT_GSM_CELL_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-G�������
*****************************************************************************/
typedef struct
{
    VOS_INT16                            sCarrierRSSI;

    VOS_UINT16                           usBcchArfch;

    VOS_UINT16                           usFreqBandInd;

    VOS_UINT16                           usNCC;

    VOS_UINT16                           usBCC;

    VOS_INT16                            sRValue;                                 /* ������Rֵ*/

    VOS_INT16                            sHValue;                                 /* ������Hֵ*/

    PS_BOOL_ENUM_UINT8                   enTreselFlg;                             /* �Ƿ�������Treselection��ʱ�� */

    PS_BOOL_ENUM_UINT8                   enTevaluateFlg;                          /* �Ƿ�������Tevaluate��ʱ�� */

    PS_BOOL_ENUM_UINT8                   enTnFlg;                                 /* �Ƿ�������Tn��ʱ�� */

    VOS_UINT8                            aucReserved[3];
}WAS_MNTN_REPORT_GSM_CELL_RSLT_STRU;


/*****************************************************************************
 �ṹ��    : WAS_MNTN_REPORT_LTE_CELL_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����ϢL��Ƶ����С�����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usCellId;
    VOS_INT16                                               sRsrp;              /* RSRP����ֵ,ȡֵ��Χ[-141*8,-44*8]����λ:0.125dBm */
    VOS_INT16                                               sRsrq;              /* RSRQ����ֵ ,ȡֵ��Χ[-20*8��-3*8]����λ:0.125dB */
    VOS_INT16                                               sRssi;              /* RSSI����ֵ ,ȡֵ��Χ[-110*8,-20*8],  ��λ:0.125dBm*/
    PS_BOOL_ENUM_UINT8                                      enTreselFlg;        /* �Ƿ�������Treselection��ʱ�� */
    VOS_INT8                                                cArfcnPri;         /* Ƶ�����ȼ���Ϣ,��ЧֵΪ-1, */
}WAS_MNTN_REPORT_LTE_CELL_RSLT_STRU;

/*****************************************************************************
 �ṹ��    : WAS_OM_L_NCELL_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����ϢLTE��������Ind,���֧��8��LTEƵ���ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usReserved;

    VOS_UINT8                               aucReserved[1];
    WAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;

    /***************************************************************************
     ���usCellNumΪN��N > 0������ʱaucLTENeighberFreqInfo�д���N��С��
     WAS_MNTN_REPORT_LTE_CELL_RSLT_STRU����Ϣ,�˴�ռ��4���ֽڵ�λ��
    ***************************************************************************/

    VOS_UINT16                              usCellNum;      /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNCellNum */

    VOS_UINT8                               aucLTENeighberCellInfo[4];

    /***************************************************************************
     _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:WAS_MNTN_REPORT_LTE_CELL_RSLT_STRU MINIDX:1 MAXIDX:256 EXPORTNAME:usH2ASNCellNum
    ***************************************************************************/

} WAS_OM_L_NCELL_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : WAS_OM_SECOND_CELL_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����ϢSecond Cell��������Ind,���֧��6+32��Second Cell�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usReserved;

    VOS_UINT8                               aucReserved[3];
    WAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;
    VOS_UINT16                              usMeasQuantity;

     /* ���usCellNumΪN��N > 0������ʾSecond Cell���ж��С����
        ��ʱaucSecondCellInfo�д���N��С��
        WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU����Ϣ,�˴�
        ռ��4���ֽڵ�λ��*/
    VOS_UINT8                               ucServCellNum;  /* ��С������ */
    VOS_UINT8                               ucNeighCellNum; /* �������� */
    VOS_UINT8                               aucReserved2[2];

    VOS_UINT16                              usCellNum;      /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNCellNum */
    VOS_UINT8                               aucSecondCellInfo[4];
    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:WAS_MNTN_REPORT_WCDMA_CELL_RSLT_STRU MINIDX:1 MAXIDX:38 EXPORTNAME:usH2ASNCellNum
    ******************************************************************************************************/
}WAS_OM_SECOND_CELL_INFO_IND_STRU;


/*****************************************************************************
 �ṹ��    : WAS_OM_G_NCELL_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ͸����Ϣ-G��������Ind,���֧��G 6�������ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usReserved;

    VOS_UINT8                               aucReserved[1];
    WAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;

    /* ���usCellNumΪN��N > 0����
        ��ʱaucGsmNeighberCellInfo�д���N��С��
        WAS_MNTN_REPORT_GSM_CELL_RSLT_STRU����Ϣ,�˴�
        ռ��4���ֽڵ�λ��*/

    VOS_UINT16                              usCellNum;      /* _H2ASN_IE_DYNAMIC_ARRAY_EXPORT STRUTYPE:VOS_UINT16 EXPORTNAME:usH2ASNCellNum */

    VOS_UINT8                               aucGsmNeighberCellInfo[4];

    /******************************************************************************************************
        _H2ASN_IE_DYNAMIC_ARRAY_COMMENT STRUTYPE:WAS_MNTN_REPORT_GSM_CELL_RSLT_STRU MINIDX:1 MAXIDX:32 EXPORTNAME:usH2ASNCellNum
    ******************************************************************************************************/
} WAS_OM_G_NCELL_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : OM_WAS_W_CELL_CHG_INFO_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :С���仯��Ϣ��ѯ
*****************************************************************************/

typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    WAS_MNTN_RPT_CMD_ENUM_UINT8         enCommand;                              /*ֹͣ��ʼ�ϱ�*/
    WAS_MNTN_RPT_TYPE_ENUM_UINT8        enReportType;                           /*�ϱ����ͣ�����ֻ����һ���ϱ����߱仯�ϱ�*/
    VOS_UINT8                           aucReserve1[2];

}OM_WAS_W_CELL_CHG_INFO_REQ_STRU;

typedef WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU WAS_OM_W_CELL_CHG_INFO_CNF_STRU;

/*****************************************************************************
 ö����    : WAS_CALL_ACCS_IND_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum WAS_CALL_ACCS_IND_ENUM
{
    WAS_CALL_ACCS_UNLIMITED             = 0,
    WAS_CALL_ACCS_EMERGENCY             = 1,
    WAS_CALL_ACCS_BUTT
};
typedef VOS_UINT8 WAS_CALL_ACCS_IND_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : WAS_OM_W_CELL_CHG_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :RNC ID/CELL ID/URA ID RNC���/С�����/ע�������
Cell Beared С����ֹ����ָʾ
Cell Reserved С������ʹ��ָʾ
UE Camped to a cell UEפ����С��ָʾ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usReserved;

    WAS_MNTN_RPT_TYPE_ENUM_UINT8            enReportType;
    VOS_UINT8                               aucReserve1[1];

    VOS_UINT16                              usDlFreq;                           /* С������Ƶ�� ,��λ200KHZ*/
    VOS_UINT16                              usUlFreq;                           /* С������Ƶ�� ,��λ200KHZ*/

    PS_BOOL_ENUM_UINT8                      enCellBarredFlg;                    /* PS_TRUE,��ʾС����������PS_FALSE��ʾС��δ������ */
    PS_BOOL_ENUM_UINT8                      enCellReservFlag;                   /* PS_TRUE��ʾС����reserved*/
    PS_BOOL_ENUM_UINT8                      enCellCampedFlag;                   /* PS_TRUE��ʾפ������С��*/
    VOS_UINT8                               aucReserve2[1];

    VOS_UINT16                              usRncId;                            /* usRncId */ /*10������ʾ*/
    VOS_UINT16                              usUeUraId;                          /*10������ʾ*/
    VOS_UINT16                              usCellId;                           /*10������ʾ*/

    WAS_CALL_ACCS_IND_ENUM_UINT8            enCallAccs;                         /* 0:��ʾ���Խ����������;1:��ʾ���ܽ��н������� */
    VOS_UINT8                               aucReserve3[1];

    VOS_UINT16                              usPrimaryScramCode;                 /*usCellId��Ӧ��С������*/

    VOS_UINT16                              usScndDlFreq;                       /* ���ز�����Ƶ�� ,��λ200KHZ*/
    VOS_UINT8                               aucReserve4[2];
}WAS_OM_W_CELL_CHG_INFO_IND_STRU;

/*****************************************************************************
 ö����    : WAS_OM_UE_WORK_MODE_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : W����ģʽ
*****************************************************************************/
enum WAS_OM_UE_WORK_MODE_TYPE_ENUM
{
    WAS_OM_UE_WORK_MODE_TYPE_WCDMA,
    WAS_OM_UE_WORK_MODE_TYPE_HSDPA,
    WAS_OM_UE_WORK_MODE_TYPE_HSUPA,
    WAS_OM_UE_WORK_MODE_TYPE_DEACTIVE,
    WAS_OM_UE_WORK_MODE_TYPE_BUTT
};

typedef VOS_UINT8   WAS_OM_UE_WORK_MODE_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : OM_WAS_UE_WORK_MODE_REQ_STRU
 Э����  :
 ASN.1���� : W��UE����ģʽ��ѯ��R99/R5/R6
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;
}OM_WAS_UE_WORK_MODE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : OM_WAS_UE_WORK_MODE_REQ_STRU
 Э����  :
 ASN.1���� : W��UE����ģʽ��ѯ��R99/R5/R6
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU             stMsgCommHead;

    WAS_OM_UE_WORK_MODE_TYPE_ENUM_UINT8     enWasWorkMode;
    VOS_UINT8                               aucReserve1[3];
}WAS_OM_UE_WORK_MODE_CNF_STRU;


/*****************************************************************************
 �ṹ��    : OM_WAS_UE_STATE_REQ_STRU
 Э����  :
 ASN.1���� :W��UE״̬��ѯ
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    WAS_MNTN_RPT_CMD_ENUM_UINT8         enCommand;                              /*ֹͣ��ʼ�ϱ�*/
    WAS_MNTN_RPT_TYPE_ENUM_UINT8        enReportType;                           /*�ϱ�������,����ֻ����1���ϱ����߱仯�ϱ�*/
    VOS_UINT8                           aucReserve1[2];
}OM_WAS_UE_STATE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : WAS_OM_UE_STATE_CNF_STRU
 Э����  :
 ASN.1���� :
*****************************************************************************/
typedef WAS_OM_ACT_OR_SERV_CELL_INFO_CNF_STRU WAS_OM_UE_STATE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WAS_OM_UE_STATE_IND_STRU
 Э����  :
 ASN.1���� :��̬�ϱ�RRC״̬
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReserved;

    WAS_OM_STATE_IND_ENUM_UINT8         enRrcStateInd;
    PS_BOOL_ENUM_UINT8                  enReadyForCommEdch;
    VOS_UINT8                           aucReserve1[2];
}WAS_OM_UE_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : OM_WAS_TIMER_EVENT_REQ_STRU
 Э����  :
 ASN.1���� : ��ʱ���¼��ϱ�����
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;

    VOS_UINT32                          ulTimerEventBitmap;     /* ÿһ��bitλ��Ӧһ����ʱ���¼�
                                                                   0 - �ö�ʱ���¼�����Ҫ�ϱ�
                                                                   1 - �ö�ʱ���¼���Ҫ�ϱ� */

}OM_WAS_TIMER_EVENT_REQ_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_TIMER_EVENT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WAS_PRINT_MSG_STRU
 Э����  :
 ASN.1���� : WAS��ӡ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTick;
    VOS_UINT32                          enLevel;
    PS_FILE_ID_DEFINE_ENUM_UINT32       enFile;
    VOS_UINT32                          ulLine;
    VOS_INT32                           alPara[4];
}WAS_PRINT_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : WAS_PRINT_MSG_STRU
 Э����  :
 ASN.1���� : WAS��ӡ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReserved;

    VOS_UINT32                          ulCnt;
    WAS_PRINT_RECORD_STRU               astData[WAS_PRINT_MSG_MAX_NUM];
}WAS_PRINT_MSG_STRU;

/*****************************************************************************
 �ṹ��    : OM_WAS_CONNECTED_IND_STRU
 Э����  :
 ASN.1���� : ��������IND
*****************************************************************************/
typedef struct
{
    DIAG_WAS_MSG_COMM_HEAD_STRU         stMsgCommHead;
}OM_WAS_CONNECTED_IND_STRU;

typedef WAS_OM_OTA_CNF_STRU WAS_OM_CONNECTED_CNF_STRU;

/*****************************************************************************
 �ṹ��    : WAS_OM_CELL_INDI_OFFSET_MODIFY_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С��ƫ�ö����޸���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_INT8                            cCellIndiOffsetBeforeModify;            /* �޸�ǰ��С��ƫ�ã�����0.5db���ȸ�OM�ϱ� */
    VOS_INT8                            cCellIndiOffsetAfterModify;             /* �޸ĺ��С��ƫ�ã�����0.5db���ȸ�OM�ϱ� */
    VOS_UINT8                           aucReserved[2];
} WAS_OM_CELL_INDI_OFFSET_MODIFY_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : WAS_OM_AM_SRB_SEND_STATE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��2��ǰĳ������RB�ϵķ���״̬��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulSduThreshold;
    VOS_UINT32                          ulSduTotalLen;
} WAS_OM_AM_SRB_SEND_STATE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : WAS_OM_TRANS_IND_STRU
 Э����  :
 ASN.1���� : ͸����Ϣ�ϱ������ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usPrimId;
    VOS_UINT16  usReserved;
    VOS_UINT8   aucData[4];
}WAS_OM_TRANS_IND_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern WAS_MNTN_OM_OUT_OF_SERVICE_ENUM_UINT8  WAS_MNTN_GetOmOutOfService(VOS_VOID);

extern VOS_UINT8   WAS_MNTN_FilterMsg(MsgBlock *msg);

extern VOS_VOID WAS_MAIN_ReportAbnormalMsgQueue2OM( VOS_UINT32 *pulAbnormalMsgAddr,
                    VOS_UINT32 *pulMsgQueueLength );



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of WasOmInterface.h */
