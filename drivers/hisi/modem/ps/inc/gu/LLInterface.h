
#ifndef _LL_INTERFACE_H_
#define _LL_INTERFACE_H_

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/******************************************************************************
  1 ����ͷ�ļ�����
******************************************************************************/
#include "PsTypeDef.h"

/******************************************************************************
 2 �궨��
******************************************************************************/
/* ��ϢID */
#define ID_LL_GMM_ASSIGN_REQ        0x0001
#define ID_LL_GMM_TRIGGER_REQ       0x0002
#define ID_LL_GMM_SUSPEND_REQ       0x0003
#define ID_LL_GMM_RESUME_REQ        0x0004
#define ID_LL_GMM_STATUS_IND        0x0005
#define ID_LL_GMM_ABORT_REQ         0x0006

#define ID_LL_UNITDATA_REQ          0x0015
#define ID_LL_UNITDATA_IND          0x0016
#define ID_LL_UNITDATA_CNF          0x0017

#define ID_LL_DATA_INFORM           0x0020

#define LL_INVALID_TLLI             0xFFFFFFFF

/* �������ȼ����� */
/*
Priority (2 bit field)
This information field indicates the requested Radio Priority. This field is coded as shown in the following table. The
8 bit format has a default Radio Priority of 4.bit
bit
2 1
0 0 Radio Priority 1 (Highest priority)
0 1 Radio Priority 2
1 0 Radio Priority 3
1 1 Radio Priority 4 (Lower priority)
*/
#define LL_RADIO_PRI_1              0
#define LL_RADIO_PRI_2              1
#define LL_RADIO_PRI_3              2
#define LL_RADIO_PRI_4              3

/* SAPIȡֵ���� */
#define LL_SAPI_GMM                 1   /* SAPI1 for GMM */
#define LL_SAPI_SMS                 7   /* SAPI7 for SMS */

/* ���ڱ�ʾָ��������幦�ܵ�����
   b000 0000 : 1��ʾָ��TLLI ;0��ʾ��ָ��TLLI
   0b00 0000 : 1��ʾָ������㷨KC ; 0��ʾ��ָ������㷨KC */
#define LL_ASSIGN_REQ_MASK_TLLI     0x80
#define LL_ASSIGN_REQ_MASK_CiphAlg  0x40

/*
Type of ciphering algorithm
bits
3   2   1
0   0   0       ciphering not used
0   0   1       GPRS Encryption Algorithm GEA/1
0   1   0       GPRS Encryption Algorithm GEA/2
0   1   1       GPRS Encryption Algorithm GEA/3
1   0   0       GPRS Encryption Algorithm GEA/4
1   0   1       GPRS Encryption Algorithm GEA/5
1   1   0       GPRS Encryption Algorithm GEA/6
1   1   1       GPRS Encryption Algorithm GEA/7
*/
#define LL_GEA0     0       /* ciphering not used */
#define LL_GEA1     1
#define LL_GEA2     2
#define LL_GEA3     3
#define LL_GEA4     4
#define LL_GEA5     5
#define LL_GEA6     6
#define LL_GEA7     7


#define LL_GMM_TRIG_CAUSE_PAG_RSP               0   /* Ѱ����Ӧ */
#define LL_GMM_TRIG_CAUSE_CELUPD_NO_CELL_NOTIFY 1   /* С�����µ�SGSNδָʾCell Notification*/
#define LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY    2   /* С��������SGSNָʾCell Notification */


#define LL_GMM_STA_CAUSE_UNSOLICITED_UA_RSP       1     /* unsolicited UA response */
#define LL_GMM_STA_CAUSE_UNSOLICITED_DM_RSP       2     /* unsolicited DM response */
#define LL_GMM_STA_CAUSE_RETRANS_SABM_N200        3     /* SABM�����ط�N200�� */
#define LL_GMM_STA_CAUSE_RETRANS_DISC_N200        4     /* DISC�����ط�N200�� */
#define LL_GMM_STA_CAUSE_RETRANS_XID_CMD_N200     5     /* XID�����ظ�N200�� */
#define LL_GMM_STA_CAUSE_INQUIRY_PEER_BUSY_N200   6     /* ��ѯ�Է��Ƿ���æ״̬����N200�� */
#define LL_GMM_STA_CAUSE_LLC_INIT_RE_EST          7     /* LLC����ABM�ؽ� */
#define LL_GMM_STA_CAUSE_PEER_INIT_RE_EST         8     /* �Զ˷���ABM�ؽ� */
#define LL_GMM_STA_CAUSE_FRAME_REJ_CONDITION      9     /* ��⵽֡�ܾ����� */
#define LL_GMM_STA_CAUSE_RECV_FRMR_RSP            10    /* ���յ�FRMR��Ӧ */
#define LL_GMM_STA_CAUSE_GMM_ASSIGN_FAIL          11    /* TLLIָ��ʧ�� */
#define LL_GMM_STA_CAUSE_GMM_TRIGGER_FAIL         12    /* LLC֡���ʹ�������ʧ�� */
#define LL_GMM_STA_CAUSE_GMM_SUSPEND_FAIL         13    /* LLC����ʧ�� */
#define LL_GMM_STA_CAUSE_GMM_RESUME_FAIL          14    /* LLC�ָ�ʧ�� */

/* ����L3�����ж��Ƿ�ΪGMM����,������ֽ�Ϊ0x08��ΪGMM���ݣ����Ϊ0x0A��ΪSM���� */
#define LL_GMM_DATA                               0x8
#define LL_SM_DATA                                0xA

/******************************************************************************
  3 �ṹ����
******************************************************************************/

/******************************************************************************
  4 ö�ٶ���
******************************************************************************/

enum LL_GMM_CIPH_FLG_ENUM
{
    LL_GMM_CIPH_STOP            = 0,    /*0: ֹͣ */
    LL_GMM_CIPH_START           = 1,    /*1: ���� */
    LL_GMM_CIPH_FLG_BUTT        = 2
};
typedef VOS_UINT8 LL_GMM_CIPH_FLG_ENUM_UINT8;

enum LL_GMM_CLEAR_DATA_TYPE_ENUM
{
    LL_GMM_CLEAR_DATA_TYPE_GMM          = 0x01,    /* GMM���� */
    LL_GMM_CLEAR_DATA_TYPE_SM           = 0x02,    /* SM���� */
    LL_GMM_CLEAR_DATA_TYPE_CELL_UPDT    = 0x04,    /* CELL_UPDATE���� */
    LL_GMM_CLEAR_DATA_TYPE_PAGE_RSP     = 0x08,    /* PAGE_RSP���� */
    LL_GMM_CLEAR_DATA_TYPE_USER         = 0x10,    /* �û������� */
    LL_GMM_CLEAR_DATA_TYPE_SMS          = 0x20,    /* ����Ϣ���� */
    LL_GMM_CLEAR_DATA_TPYE_BUTT
};
typedef VOS_UINT8 LL_GMM_CLEAR_DATA_TYPE_ENUM_UINT8;

#define LL_GMM_CLEAR_DATA_TYPE_TRIG              ( (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_CELL_UPDT \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_PAGE_RSP )

#define LL_GMM_CLEAR_DATA_TYPE_NO_SM_SIGNALLING  ( (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_GMM \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_TRIG )

#define LL_GMM_CLEAR_DATA_TYPE_SIGNALLING        ( (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_GMM \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_SM \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_TRIG )

#define LL_GMM_CLEAR_DATA_TYPE_ALL               ( (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_GMM \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_SM \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_TRIG \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_USER \
                                                 | (VOS_UINT8)LL_GMM_CLEAR_DATA_TYPE_SMS )

/* GMM֪ͨLL�ָ����ݵ����� */
enum LL_GMM_RESUME_TYPE_ENUM
{
    LL_GMM_RESUME_TYPE_ALL              = 0,
    LL_GMM_RESUME_TYPE_SIGNAL           = 1,
    LL_GMM_RESUME_TYPE_BUTT
};
typedef VOS_UINT32    LL_GMM_RESUME_TYPE_ENUM_UINT32;


/******************************************************************************
  5 ȫ�ֱ�������
******************************************************************************/


/******************************************************************************
  6 ��Ϣͷ����
******************************************************************************/


/******************************************************************************
  7 ��Ϣ����
******************************************************************************/


/******************************************************************************
  8 �ṹ����
******************************************************************************/
#pragma pack(4)

/*===========================================================================*/
/*GMM��LLME�Ľӿ�ԭ�ﶨ��*/
/*===========================================================================*/
typedef struct
{
    /*TLLI all 1's��ʾ��Чֵ*/
    VOS_UINT32  ulTlliOld;
    VOS_UINT32  ulTlliNew;

    /* ���ڱ�ʾָ��������幦�ܵ�����
       b000 0000 : ��b����1ʱ��ʾָ��TLLI ;0��ʾ��ָ��TLLI
       0b00 0000 : ��b����1ʱ��ʾָ������㷨KC ; 0��ʾ��ָ������㷨KC
#define LL_ASSIGN_REQ_MASK_TLLI     0x80
#define LL_ASSIGN_REQ_MASK_CiphAlg  0x40 */
    VOS_UINT8   ucMask;

    /*64 bits Kc parameter received from GMM*/
    VOS_UINT8   aucKc[8];

    /* 128 bits RAND parameter received from GMM */
    VOS_UINT8   ucRand[16];
/*
Type of ciphering algorithm
bits
3   2   1
0   0   0       ciphering not used
0   0   1       GPRS Encryption Algorithm GEA/1
0   1   0       GPRS Encryption Algorithm GEA/2
0   1   1       GPRS Encryption Algorithm GEA/3
1   0   0       GPRS Encryption Algorithm GEA/4
1   0   1       GPRS Encryption Algorithm GEA/5
1   1   0       GPRS Encryption Algorithm GEA/6
1   1   1       GPRS Encryption Algorithm GEA/7

#define LL_GEA0     0       ciphering not used
#define LL_GEA1     1
#define LL_GEA2     2
#define LL_GEA3     3
#define LL_GEA4     4
#define LL_GEA5     5
#define LL_GEA6     6
#define LL_GEA7     7 */
    VOS_UINT8                           ucCiphAlg;      /* �����㷨��Ŀǰ֧��GEA1��GEA2��GEA3 */

    LL_GMM_CIPH_FLG_ENUM_UINT8          enCiphStartFlg; /* �����Ƿ�������־ */

    VOS_UINT8                           ucRsv;          /* ���ֽڲ��� */
} LL_GMM_ASSIGN_REQ_ST;

typedef struct
{
    VOS_UINT32  ulTlli;
/*
#define LL_GMM_TRIG_CAUSE_PAG_RSP               0   Ѱ����Ӧ
#define LL_GMM_TRIG_CAUSE_CELUPD_NO_CELL_NOTIFY 1   С�����µ�SGSNδָʾCell Notification
#define LL_GMM_TRIG_CAUSE_CELUPD_CELL_NOTIFY    2   С��������SGSNָʾCell Notification */
    VOS_UINT8   ucCause;                            /* GMM������ԭ�� */

    VOS_UINT8   ucRsv;                              /*���ֽڲ���*/
    VOS_UINT16  usRsv;                              /*���ֽڲ���*/
} LL_GMM_TRIGGER_REQ_ST;

typedef struct
{
    VOS_UINT32 ulTlli;
/*
#define LL_GMM_STA_CAUSE_UNSOLICITED_UA_RSP       1     unsolicited UA response
#define LL_GMM_STA_CAUSE_UNSOLICITED_DM_RSP       2     unsolicited DM response
#define LL_GMM_STA_CAUSE_RETRANS_SABM_N200        3     SABM�����ط�N200��
#define LL_GMM_STA_CAUSE_RETRANS_DISC_N200        4     DISC�����ط�N200��
#define LL_GMM_STA_CAUSE_RETRANS_XID_CMD_N200     5     XID�����ظ�N200��
#define LL_GMM_STA_CAUSE_INQUIRY_PEER_BUSY_N200   6     ��ѯ�Է��Ƿ���æ״̬����N200��
#define LL_GMM_STA_CAUSE_LLC_INIT_RE_EST          7     LLC����ABM�ؽ�
#define LL_GMM_STA_CAUSE_PEER_INIT_RE_EST         8     �Զ˷���ABM�ؽ�
#define LL_GMM_STA_CAUSE_FRAME_REJ_CONDITION      9     ��⵽֡�ܾ�����
#define LL_GMM_STA_CAUSE_RECV_FRMR_RSP            10    ���յ�FRMR��Ӧ
#define LL_GMM_STA_CAUSE_GMM_ASSIGN_FAIL          11    TLLIָ��ʧ��
#define LL_GMM_STA_CAUSE_GMM_TRIGGER_FAIL         12    LLC֡���ʹ�������ʧ��
#define LL_GMM_STA_CAUSE_GMM_SUSPEND_FAIL         13    LLC����ʧ��
#define LL_GMM_STA_CAUSE_GMM_RESUME_FAIL          14    LLC�ָ�ʧ�� */

    VOS_UINT16  usCause;                                /* ����״ָ̬ʾ��ԭ�� */

    VOS_UINT16  usRsv;                                  /*���ֽڲ���*/
} LL_GMM_STATUS_IND_ST;


/*===========================================================================*/
/*LLE��GMM/SMS/��ȷ�����ݴ���ӿ�ԭ�ﶨ��*/
/*===========================================================================*/
typedef struct
{
    VOS_UINT32              ulTlli;         /* ĿǰLLC����ʹ��NAS�����д���TLLI*/
    VOS_UINT8               ucRadioPri;     /* �������ȼ��� */
    VOS_UINT8               ucCiphInd;      /* �Ƿ���ܵ�ָʾ��0:������ 1:����*/
    PS_BOOL_ENUM_UINT8      enNeedCnf;
    VOS_UINT8               ucRsv;
    VOS_UINT16              usMui;          /* LLC��MM����ʹ�õ�SDU�ı�� */
    VOS_UINT16              usPduLen;       /* ���ݳ��� */
    VOS_UINT8               aucPdu[4];      /* GMM��SMS������*/
} LL_NAS_UNITDATA_REQ_ST;

typedef struct
{
    VOS_UINT32  ulTlli;
    VOS_UINT8   ucCiphInd;  /* �Ƿ���ܵ�ָʾ��0:������ 1:����*/
    VOS_UINT8   ucRsv;      /* ���ֽڲ���*/
    VOS_UINT16  usPduLen;
    VOS_UINT8   aucPdu[4];
} LL_NAS_UNITDATA_IND_ST;

/*===========================================================================*/
/*LLC--GMM/SMS��Ϣ����*/
/*===========================================================================*/

typedef struct
{
    VOS_MSG_HEADER

    /*��Ϣ����*/
    VOS_UINT16 usMsgType;

    /*�ӽ��̣�������SAPI*/
    VOS_UINT16 usTransId;

    /*��Ϣ��ṹ*/
    LL_GMM_ASSIGN_REQ_ST  stLlGmmAssReq;
} LL_GMM_ASSIGN_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER

    /*��Ϣ����*/
    VOS_UINT16 usMsgType;

    /*�ӽ��̣�������SAPI*/
    VOS_UINT16 usTransId;

    /*��Ϣ��ṹ*/
    LL_GMM_TRIGGER_REQ_ST stLlGmmTrigReq;
} LL_GMM_TRIGGER_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER

    /*��Ϣ����*/
    VOS_UINT16  usMsgType;

    /*�ӽ��̣�������SAPI*/
    VOS_UINT16  usTransId;

    /* ������ */
    VOS_UINT8   aucReserve[4];
} LL_GMM_SUSPEND_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER

    /*��Ϣ����*/
    VOS_UINT16 usMsgType;

    /*�ӽ��̣�������SAPI*/
    VOS_UINT16 usTransId;

    /* �ָ����ݴ�������:�������ݣ��û����� */
    LL_GMM_RESUME_TYPE_ENUM_UINT32  ulResumeType;
} LL_GMM_RESUME_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER                /* _H2ASN_Skip */
    VOS_UINT32  ulMsgName;        /* message name *//* _H2ASN_Skip */
    LL_GMM_STATUS_IND_ST    stLlGmmStatusInd;
} LL_GMM_STATUS_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER

    /*��Ϣ����*/
    VOS_UINT16 usMsgType;

    /*�ӽ��̣�������SAPI*/
    VOS_UINT16 usTransId;

    /*��Ϣ��ṹ*/
    LL_NAS_UNITDATA_REQ_ST  stUnitDataReq;
} LL_NAS_UNITDATA_REQ_MSG;

typedef struct
{
    VOS_MSG_HEADER

    /*��Ϣ����*/
    VOS_UINT32 ulMsgName;

    /*��Ϣ��ṹ*/
    VOS_UINT16              usMui;          /* LLC��MM����ʹ�õ�SDU�ı�� */

    VOS_UINT8               aucRsv[2];
} LL_NAS_UNITDATA_CNF_MSG;

typedef struct
{
    VOS_MSG_HEADER                /* _H2ASN_Skip */
    VOS_UINT32  ulMsgName;        /* message name *//* _H2ASN_Skip */
    LL_NAS_UNITDATA_IND_ST  stUnitDataInd;
} LL_NAS_UNITDATA_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER
    /*��Ϣ����*/
    VOS_UINT16 usMsgType;

    /*�ӽ��̣�������SAPI*/
    VOS_UINT16 usTransId;

    /*��Ϣ��ṹ*/
    LL_NAS_UNITDATA_IND_ST  stUnitDataInd;
} LL_SMS_UNITDATA_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER                /* _H2ASN_Skip */
    VOS_UINT32  ulMsgName;        /* message name *//* _H2ASN_Skip */
} LL_DATA_INFORM_MSG;

typedef struct
{
    VOS_MSG_HEADER

    /*��Ϣ����*/
    VOS_UINT16                          usMsgType;

    LL_GMM_CLEAR_DATA_TYPE_ENUM_UINT8   enClearDataType;

    /*�ӽ��̣�������SAPI*/
    VOS_UINT8                           ucRsv;
} LL_GMM_ABORT_REQ_MSG;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/******************************************************************************
  8 UNION����
******************************************************************************/


/******************************************************************************
  9 OTHERS����
******************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /*LLInterface.h*/

