/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.
******************************************************************************/

#ifndef __EMMLPPINTERFACE_H__
#define __EMMLPPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "LPSCommon.h"
//#include    "NasLppAirMsg.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 macro
*****************************************************************************/

#define LPP_LMM_MSG_HDR  0
#define LMM_LPP_MSG_HDR  100


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

enum LMM_LPP_MSG_TYPE_ENUM
{
    /*��Ϣԭ��*/
    /*LPP���͸�LMM����Ϣԭ��*/
    ID_LPP_LMM_DATA_REQ                     = (LPP_LMM_MSG_HDR + 0x1),  /* _H2ASN_MsgChoice LPP_LMM_DATA_REQ_STRU*/
    ID_LPP_LMM_EST_REQ                      = (LPP_LMM_MSG_HDR + 0x2),  /* _H2ASN_MsgChoice LPP_lMM_EST_REQ_STRU*/

    /*LMM���͸�LPP����Ϣԭ��*/
    ID_LMM_LPP_DATA_CNF                     = (LMM_LPP_MSG_HDR + 0x1),  /* _H2ASN_MsgChoice LMM_LPP_DATA_CNF_STRU*/
    ID_LMM_LPP_EST_CNF                      = (LMM_LPP_MSG_HDR + 0x2),  /* _H2ASN_MsgChoice LMM_LPP_EST_CNF_STRU*/
    ID_LMM_LPP_START_IND                    = (LMM_LPP_MSG_HDR + 0x3),  /* _H2ASN_MsgChoice LMM_LPP_START_IND_STRU*/
    ID_LMM_LPP_STOP_IND                     = (LMM_LPP_MSG_HDR + 0x4),  /* _H2ASN_MsgChoice LMM_LPP_STOP_IND_STRU*/
    ID_LMM_LPP_CELL_CHANGE_IND              = (LMM_LPP_MSG_HDR + 0x5),  /* _H2ASN_MsgChoice LMM_LPP_CELL_CHANGE_IND*/
    ID_LMM_LPP_DATA_IND                     = (LMM_LPP_MSG_HDR + 0x6),  /* _H2ASN_MsgChoice LMM_LPP_DATA_IND_STRU*/
    ID_LMM_LPP_REL_IND                      = (LMM_LPP_MSG_HDR + 0x7),  /* _H2ASN_MsgChoice LMM_LPP_REL_IND_STRU*/

    ID_LMM_LPP_BUTT
};
typedef VOS_UINT32 LMM_LPP_MSG_TYPE_ENUM_UINT32;


enum LMM_LPP_SEND_RSLT_ENUM
{
    LMM_LPP_SEND_RSLT_SUCCESS                       = 0, /*���ͳɹ�*/
    LMM_LPP_SEND_RSLT_FAIL_PS_NOT_ATTACHED          = 1, /*PS��δע��*/
    LMM_LPP_SEND_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED    = 2, /*PS������ע��*/
    LMM_LPP_SEND_RSLT_FAIL_USIM_PS_INVALID          = 3, /*USIM����Ч*/
    LMM_LPP_SEND_RSLT_FAIL_ACCESS_BARRED            = 4, /*��BAR*/
    LMM_LPP_SEND_RSLT_FAIL_RRC_CONN_NOT_EXIST       = 5, /*����״̬�����ڣ�SS������EST REQ������*/
    LMM_LPP_SEND_RSLT_LOW_LAYER_FAIL                = 6, /*�ײ㷢��ʧ�ܣ�����1s���ٳ���*/
    LMM_LPP_SEND_RSLT_FAIL_3411_RUNNING             = 7, /*3411�����У����Թ�10s�ٳ���*/
    LMM_LPP_SEND_RSLT_FAIL_3402_RUNNING             = 8, /*3402������*/
    LMM_LPP_SEND_RSLT_OHTERS                        = 9, /*����ʧ��ԭ��ֵ*/

    LMM_LPP_SEND_RSLT_BUTT
};
typedef VOS_UINT32 LMM_LPP_SEND_RSLT_ENUM_UINT32;


enum LMM_LPP_EST_RESULT_ENUM
{
    LMM_LPP_EST_RESULT_SUCC                         = 0, /*�����ɹ�*/
    LMM_LPP_EST_RESULT_FAIL_PS_NOT_ATTACHED         = 1, /*PS��δע��*/
    LMM_LPP_EST_RESULT_FAIL_PS_ATTACH_NOT_ALLOWED   = 2, /*PS������ע��*/
    LMM_LPP_EST_RESULT_FAIL_USIM_PS_INVALID         = 3, /*USIM����Ч*/
    LMM_LPP_EST_RESULT_FAIL_ACCESS_BARRED           = 4, /*��BAR*/
    LMM_LPP_EST_RESULT_FAIL_STATE_CANNOT_SERVICE    = 5, /*��ǰ״̬�޷�����SERVICE*/
    LMM_LPP_EST_RESULT_FAIL_3411_RUNNING            = 6, /*3411�����У����Թ�10s�ٳ���*/
    LMM_LPP_EST_RESULT_FAIL_3402_RUNNING            = 8, /*3402������*/
    LMM_LPP_EST_RESULT_FAIL_SERVICE_FAIL            = 9, /*SERVICEʧ�ܣ�����2s���ٳ���*/
    LMM_LPP_EST_RESULT_FAIL_OTHERS                  = 10, /*����ʧ��ԭ��ֵ*/

    LMM_LPP_EST_RESULT_BUTT
};
typedef VOS_UINT32 LMM_LPP_EST_RESULT_ENUM_UINT32;



enum LMM_LPP_REL_CAUSE_ENUM
{
    LMM_LPP_REL_CAUSE_CONN_FAIL                  = 0,  /* RR Connection Failure*/
    LMM_LPP_REL_CAUSE_LOAD_BALANCE_REQ           = 1,  /* Rrc Con Release ���е�ԭ��ΪloadBalancingTAUrequired */
    LMM_LPP_REL_CAUSE_OTHER_REASON               = 2,  /* Rrc Con Release ���е�ԭ����loadBalancingTAUrequired����������·ʧ���ͷ�ԭ��*/
    LMM_LPP_REL_CAUSE_NAS_DATA_ABSENT            = 3,  /* NAS Data Request: Connection Absent*/
    LMM_LPP_REL_CAUSE_RRC_ABNORMAL               = 4,  /* RRC��ײ�ϵͳ�쳣�ͷ�ԭ��*/
    LMM_LPP_REL_CAUSE_GU2L_HO_ERR                = 5,  /* GU��L�л�ʧ�� */
    LMM_LPP_REL_CAUSE_L2GU_REDIRECT              = 6,  /* ��ϵͳ�ض��� */
    LMM_LPP_REL_CAUSE_CSFB_HIGH_PRIOR            = 7,  /* Rrc Con Release ���е�ԭ�� cs-FallbackHighPriority */
    LMM_LPP_REL_CAUSE_NO_RF                      = 8,  /* DSDS���Դ򿪿��ܻᵼ��NORF */

    LMM_LPP_REL_CAUSE_BUTT
};
typedef VOS_UINT32 LMM_LPP_REL_CAUSE_ENUM_UINT32;


/*****************************************************************************
 5. STRUCT
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    VOS_UINT32                              ulMsgId;            /*_H2ASN_Skip*/    /*msg ID*/

    LMM_LPP_REL_CAUSE_ENUM_UINT32           enRelCause;         /* �����ͷ�ԭ�� */
}LMM_LPP_REL_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/    /*msg ID*/

    VOS_UINT32                          ulOpId;             /*ά��LMM, LPP��Ϣ�����ļ���*/
} LPP_lMM_EST_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulOpId;             /*ά��LMM, LPP��Ϣ�����ļ���*/
    LMM_LPP_EST_RESULT_ENUM_UINT32      ulEstRst;           /*�������*/
} LMM_LPP_EST_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/  /* ��Ϣͷ */

    VOS_UINT32                          ulCellId;           /* ����С��ID�����仯��ʱ����֪ͨLPP*/
    VOS_UINT32                          ulEarfcn;
    VOS_UINT16                          usPhyCellId;
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           aucRsv[3];
}LMM_LPP_CELL_CHANGE_IND;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/  /* ��Ϣͷ */

    VOS_UINT32                          ulRsv;              /*����LPP�Ŀ�����ʼ���������������Ϣ��LPP�յ�����Ϣ��ʱ���ʼ�����ȫ�����ݼ���*/
}LMM_LPP_START_IND_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/  /* ��Ϣͷ */

    VOS_UINT32                          ulRsv;              /*�ػ���Ҫ��������Ϣ��ֻҪ������ȫ�����ݽṹ����*/
}LMM_LPP_STOP_IND_STRU;
typedef struct
{
    VOS_UINT32                         ulLppMsgSize;
    VOS_UINT8                          aucLppMsg[4];       /* ��Ϣ��ǰ�ĸ��ֽ�����             */
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}LPP_LMM_MSG_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/ /* ��Ϣͷ */

    VOS_UINT32                          ulOpId;             /*ά��LMM, LPP��Ϣ�����ļ���*/
    VOS_UINT32                          ulSessionId;        /*�ỰID���������generic��Ϣ��Ҫʹ��*/
    LPP_LMM_MSG_STRU                    stLppMsg;           /*LPP��Ϣʵ������*/
}LPP_LMM_DATA_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/ /* ��Ϣͷ */

    VOS_UINT32                          ulSessionId;        /*LPP��Ϣ�ĻỰID*/
    LPP_LMM_MSG_STRU                    stLppMsg;           /*LPP��Ϣʵ������*/
}LMM_LPP_DATA_IND_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                                  ulOpId;             /*ά��LMM, LPP��Ϣ�����ļ���*/
    LMM_LPP_SEND_RSLT_ENUM_UINT32               enDataCnfRst;       /*Lpp Data cnf���*/
}LMM_LPP_DATA_CNF_STRU;

typedef struct
{
    LMM_LPP_MSG_TYPE_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export LMM_LPP_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LMM_LPP_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LMM_LPP_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    LMM_LPP_MSG_DATA                     stMsgData;
}LmmLppInterface_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of EmmLppInterface.h */





