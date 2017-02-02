

#ifndef __PHYGRRINTERFACE_H__
#define __PHYGRRINTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C"{
    #endif
#endif /* __cplusplus */


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "EdgeInterface.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define GAS_INT_LEVEL_TN_MAX                            8
#define GAS_MAX_TIMESLOT_NUM                            8
#define GAS_GCOMM_MPHP_BA_MEAS_IND_REPORT_NCELL_MAX_NUM 32
#define MPHP_BA_MEAS_IND_REPORT_NCELL_MAX_NUM           32
#define GAS_MAX_HOPPING_FREQUENCY_NUM                   64
#define MPHP_MA_LIST_FREQ_MAX                           64
#define MPHP_INT_MA_CHANNEL_GROUP_MAX_NUM               4     /* �ú������GasGcom.h�е�GAS_GCOM_INT_MA_CHANNEL_GROUP_MAX_NUMһ�� */
#define MPHP_INT_CHANNEL_GROUP_MAX_NUM                  32    /* �ú������GasGcom.h�е�GAS_GCOM_INT_CHANNEL_GROUP_MAX_NUMһ�� */
#define GASGRR_PHY_PARAMS_INVALID_VALUE                 0xFF

/*���к�������Moiri��ʱ��ר��ʹ��, ��ΪMPH_ASSIGNMENT_REQ�д��ڷ���ָʾ*/
#define MPHP_ASSIGN_DIRECTION_UL                        0
#define MPHP_ASSIGN_DIRECTION_DL                        1


/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

/*�ӿ���ϢIDֵ����*/
/* GRR -> PHY �ӿ���ϢID */

typedef enum
{
    /* GRR  --> L1 */
    ID_MPHP_UL_SETUP_REQ                    =   0x4701,         /* _H2ASN_MsgChoice  MPHP_UL_SETUP_REQ_ST */
    ID_MPHP_UL_RECONFIG_REQ                 =   0x4702,         /* _H2ASN_MsgChoice  MPHP_UL_RECONFIG_REQ_ST */
    ID_MPHP_UL_RELEASE_REQ                  =   0x4703,         /* _H2ASN_MsgChoice  MPHP_UL_RELEASE_REQ_ST */
    ID_MPHP_REPEAT_UL_FIXED_ALLOC_REQ       =   0x4704,         /* _H2ASN_MsgChoice  MPHP_REPEAT_UL_FIXED_ALLOC_REQ_ST */
    ID_MPHP_PDCH_RELEASE_REQ                =   0x4705,         /* _H2ASN_MsgChoice  MPHP_PDCH_RELEASE_REQ_ST */
    ID_MPHP_SINGLE_BLOCK_REQ                =   0x4706,         /* _H2ASN_MsgChoice  MPHP_SINGLE_BLOCK_REQ_ST */
    ID_MPHP_RA_REQ                          =   0x4707,         /* _H2ASN_MsgChoice  MPHP_RA_REQ_ST */
    ID_MPHP_RA_ABORT_REQ                    =   0x4708,         /* _H2ASN_MsgChoice  MPHP_RA_ABORT_REQ_ST */
    ID_MPHP_PAGING_MODE_REQ                 =   0x4709,         /* _H2ASN_MsgChoice  MPHP_PAGING_MODE_REQ_ST */
    ID_MPHP_MSGDATA_REQ                     =   0x470a,         /* _H2ASN_MsgChoice  MPHP_MSGDATA_REQ_ST */
    ID_MPHP_TIMING_ADVANCE_REQ              =   0x470b,         /* _H2ASN_MsgChoice  MPHP_TIMING_ADVANCE_REQ_ST */
    ID_MPHP_POWER_PARAM_UPDATE_REQ          =   0x470c,         /* _H2ASN_MsgChoice  MPHP_POWER_PARAM_UPDATE_REQ_ST */
    ID_MPHP_SUSPENSION_REQ                  =   0x470e,         /* _H2ASN_MsgChoice  MPHP_SUSPENSION_REQ_ST */
    ID_MPHP_RESUME_REQ                      =   0x470f,         /* _H2ASN_MsgChoice  MPHP_RESUME_REQ_ST */
    ID_MPHP_MULTI_BLOCK_REQ                 =   0x4710,         /* _H2ASN_MsgChoice  MPHP_MULTI_BLOCK_REQ_ST */
    ID_MPHP_DL_SETUP_REQ                    =   0x4711,         /* _H2ASN_MsgChoice  MPHP_DL_SETUP_REQ_ST */
    ID_MPHP_DL_RECONFIG_REQ                 =   0x4712,         /* _H2ASN_MsgChoice  MPHP_DL_RECONFIG_REQ_ST */
    ID_MPHP_DL_RELEASE_REQ                  =   0x4713,         /* _H2ASN_MsgChoice  MPHP_DL_RELEASE_REQ_ST */
    ID_MPHP_LIMIT_SEND_POWER_REQ            =   0x4715,         /* _H2ASN_MsgChoice  MPHP_LIMIT_SEND_POWER_REQ_ST */
    /* L1 ----> GRR */
    ID_MPHP_UL_SETUP_CNF                    =   0x7401,         /* _H2ASN_MsgChoice  MPHP_UL_SETUP_CNF_ST */
    ID_MPHP_UL_RECONFIG_CNF                 =   0x7402,         /* _H2ASN_MsgChoice  MPHP_UL_RECONFIG_CNF_ST */
    ID_MPHP_UL_RELEASE_CNF                  =   0x7403,         /* _H2ASN_MsgChoice  MPHP_UL_RELEASE_CNF_ST */
    ID_MPHP_REPEAT_UL_FIXED_ALLOC_CNF       =   0x7404,         /* _H2ASN_MsgChoice  MPHP_REPEAT_UL_FIXED_ALLOC_CNF_ST */
    ID_MPHP_PDCH_RELEASE_CNF                =   0x7405,         /* _H2ASN_MsgChoice  MPHP_PDCH_RELEASE_CNF_ST */
    ID_MPHP_SINGLE_BLOCK_CNF                =   0x7406,         /* _H2ASN_MsgChoice  MPHP_SINGLE_BLOCK_CNF_ST */
    ID_MPHP_RA_CNF                          =   0x7407,         /* _H2ASN_MsgChoice  MPHP_RA_CNF_ST */
    ID_MPHP_PAGING_MODE_CNF                 =   0x7409,         /* _H2ASN_MsgChoice  MPHP_PAGING_MODE_CNF_ST */
    ID_MPHP_MSGDATA_CNF                     =   0x740a,         /* _H2ASN_MsgChoice  MPHP_MSGDATA_CNF_ST */
    ID_MPHP_TIMING_ADVANCE_CNF              =   0x740b,         /* _H2ASN_MsgChoice  MPHP_TIMING_ADVANCE_CNF_ST */
    ID_MPHP_POWER_PARAM_UPDATE_CNF          =   0x740c,         /* _H2ASN_MsgChoice  MPHP_POWER_PARAM_UPDATE_CNF_ST */
    ID_MPHP_OUT_OF_MEM_IND                  =   0x740d,         /* _H2ASN_MsgChoice  MPHP_OUT_OF_MEM_IND_ST */
    ID_MPHP_SUSPENSION_CNF                  =   0x740e,         /* _H2ASN_MsgChoice  MPHP_SUSPENSION_CNF_ST */
    ID_MPHP_RESUME_CNF                      =   0x740f,         /* _H2ASN_MsgChoice  MPHP_RESUME_CNF_ST */
    ID_MPHP_MULTI_BLOCK_CNF                 =   0x7410,         /* _H2ASN_MsgChoice  MPHP_MULTI_BLOCK_CNF_ST */
    ID_MPHP_DL_SETUP_CNF                    =   0x7411,         /* _H2ASN_MsgChoice  MPHP_DL_SETUP_CNF_ST */
    ID_MPHP_DL_RECONFIG_CNF                 =   0x7412,         /* _H2ASN_MsgChoice  MPHP_DL_RECONFIG_CNF_ST */
    ID_MPHP_DL_RELEASE_CNF                  =   0x7413,         /* _H2ASN_MsgChoice  MPHP_DL_RELEASE_CNF_ST */
    ID_MPHP_LIMIT_SEND_POWER_CNF            =   0x7415,         /* _H2ASN_MsgChoice  MPHP_LIMIT_SEND_POWER_CNF_ST */
    ID_PHY_GRR_MSG_BUTT
}PHY_GRR_MSG_ID_ENUM;

typedef VOS_UINT16 PHY_GRR_MSG_ID_ENUM_UINT16;


/*******************************************************************************
* ��Ƶģʽ
*******************************************************************************/
typedef enum
{
    GAS_GRR_PHY_ASSIGN_NO_HOPPING           =   0,
    GAS_GRR_PHY_ASSIGN_HOPPING
}GAS_PHY_HOPPING_MODE_ENUM;

typedef VOS_UINT16 GAS_PHY_HOPPING_MODE_ENUM_UINT16;


/*******************************************************************************
* �ָ������ķ�ʽ
*******************************************************************************/
typedef enum
{
    MPHP_RESUME_IND_NORMAL                  =   0,
    MPHP_RESUME_IND_RELEASE
}GAS_PHY_RESUME_METHOD_ENUM;

typedef VOS_UINT16 GAS_PHY_RESUME_METHOD_ENUM_UINT16;


/*******************************************************************************
* ������Ϣ�����ȼ�, 0Ϊ��ߣ�1��֮
*******************************************************************************/
typedef enum
{
    PHY_CTRL_BLK_PRIO_HL                    =   0,
    PHY_CTRL_BLK_PRIO_LL
}GAS_PHY_CTRL_BLK_PRIO_ENUM;

typedef VOS_UINT16 GAS_PHY_CTRL_BLK_PRIO_ENUM_UINT16;

/*******************************************************************************
* ������ڴ�ָʾ
*******************************************************************************/
typedef enum
{
    GAS_PHY_ENOUGH_MEM                      =   0,
    GAS_PHY_OUT_OF_MEM
}GAS_PHY_MEM_IND_ENUM;

typedef VOS_UINT16 GAS_PHY_MEM_IND_ENUM_UINT16;

/*******************************************************************************
* EGPRSʱ���ռ�õ��ڴ��ֽ�����
*******************************************************************************/
typedef enum
{
    MPHP_NO_MULTI_BLOCK                     =   0,
    MPHP_MULTI_BLOCK_ONE                    =   12,
    MPHP_MULTI_BLOCK_TWO                    =   24
}MPHP_MULTI_BLOCK_LEN_ENUM;

typedef VOS_UINT16 MPHP_MULTI_BLOCK_LEN_ENUM_UINT16;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
#pragma pack(1)

/*===================================================================*/
typedef struct
{
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_MsgChoice_Export      PHY_GRR_MSG_ID_ENUM_UINT16*/
    VOS_UINT8                               aucMsgBlock[4];
    /******************************************************************************************************
        _H2ASN_MsgChoice_When_Comment          PHY_GRR_MSG_ID_ENUM_UINT16
    ******************************************************************************************************/

}PHY_GRR_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    PHY_GRR_MSG_DATA                        stMsgData;
}PhyGrrInterface_MSG;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*******************************************************************************
* MPHP_FREQUENCY_PARAMETERS_ST�ṹ
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usTsc;
    GAS_PHY_HOPPING_MODE_ENUM_UINT16        usHoppingMode;                              /* �Ƿ���Ƶ     */
    VOS_UINT16                              usArfcn;                                    /* ����Ƶ��Ƶ�� */
    VOS_UINT16                              usHsn;                                      /* ��Ƶ���к�   */
    VOS_UINT16                              usMaio;                                     /* ��ƵMAIO     */
    VOS_UINT16                              usFreqNum;                                  /* ��ƵƵ����Ŀ */
    VOS_UINT16                              ausFnList[GAS_MAX_HOPPING_FREQUENCY_NUM];   /* ��ƵƵ���б� */
}MPHP_FREQUENCY_PARAMETERS_ST;

/*******************************************************************************
* MPHP_DL_RESOURCE_ALLOCATION_ST�ṹ
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usDownlinkTFI;                      /* ����TBF��ʶ, [0,31] */
    VOS_UINT16                              usDownlinkTNBitmap;                 /* ����ָ��ʱ϶λͼ,Bit7,..bit0��ʾʱ϶0..7, 0=δָ��, 1=ָ�� */
}MPHP_DL_RESOURCE_ALLOCATION_ST;

/*******************************************************************************
* MPHP_DYNAMIC_ALLOCATION_ST�ṹ
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usUsfGranularity;                   /* USF����  0=1 block, 1=4 block */
    VOS_UINT16                              usRsv;                              /* ���ֽڶ��� */
    VOS_UINT16                              ausUsf[GAS_MAX_TIMESLOT_NUM];       /* USF��,[0,7],��ʱ϶��0..7��������255Ϊ��Чֵ */
}MPHP_DYNAMIC_ALLOCATION_ST;

/*******************************************************************************
* MPHP_FIXED_ALLOCATION_ST�ṹ
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usDownlinkCtrlTn;                       /* ���п����ŵ�����ʱ϶ ,[0,7] */
    VOS_UINT16                              usAllocBitmapLen;                       /* �̶�ָ���λͼ���� ,[0,127] */
    VOS_UINT16                              ausAllocBitmap[GAS_MAX_TIMESLOT_NUM];   /* �̶�ָ���λͼ ,�����StartTime��blockΪ���� */
}MPHP_FIXED_ALLOCATION_ST;


/*******************************************************************************
* MPHP_MEASUREMENT_MAPPING_ST�ṹ
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              ulMeasStartTime;                    /* ָʾ��һ���������ڵ���ʼʱ�� */
    VOS_UINT16                              usMeasInterval;                     /* ָʾǰ�������������ڵļ��[0, 32 ],��λΪ block */
    VOS_UINT16                              usMeasBitMap;                       /* ����ӳ���λͼ,Bit0,..bit7��ʾʱ϶0..7��0=���ڽ������ݣ�1=���ڲ��� */
}MPHP_MEASUREMENT_MAPPING_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_UL_SETUP_REQ
 ��������  :  ��������TBF�Ľ������������������ã�����PHY����֪�������ĸ�Ƶ����Щʱ϶���շ������ݡ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usMeasEnable;                       /* TBF�ڼ��Ƿ���Ҫ���Ų���,0=disbale,1=enable */
    VOS_UINT16                              usTimingAdvanceValue;               /* TA, [0,63],255=TA������ */
    VOS_UINT16                              usTimingAdvanceIndex;               /* PTCCH����, [0,15],255=������ */
    VOS_UINT16                              usTimingAdvanceTS;                  /* PTCCHʱ϶,[0,7],255=������ */
    VOS_UINT16                              usAlpha;                            /* �����������з��书��*/
    VOS_UINT16                              ausGammaTn[GAS_MAX_TIMESLOT_NUM];   /* ���ڼ������з��书��,[0,31]*/
    VOS_UINT16                              usBepPeriod2;                       /* ���ڼ���BEP,[0,15]����ЧֵΪ0xFFFF */
    VOS_UINT16                              usBLOCKS_OR_BLOCK_PERIODS;          /* �̶�����bitmapʹ�õ�ָʾ,0 bitmapΪ����,1 bitmapΪ�������� */
    VOS_UINT16                              usP0;                               /* ���й��ز���,[0,15] ,255=������ */
    VOS_UINT16                              usPwrCtlMode;                       /* ���й���ģʽ,0=mode A,1=mode B */
    VOS_UINT16                              usPrMode;                           /* PR ģʽ,0=PR Mode A,1=PR mode B */
    VOS_UINT16                              usRsv;                              /* ���ֽڶ��� */
    VOS_UINT32                              ulTBFStartTime;
    VOS_UINT16                              usUplinkTFI;                        /* ����TBF��ʶ    [0,31] */
    VOS_UINT16                              usUplinkTNBitmap;                   /* ����ָ��ʱ϶λͼ Bit7,..bit0��ʾʱ϶0..7, 0=δָ��, 1=ָ�� */
    VOS_UINT16                              usTbfMode;                          /* �������ֵ�ǰTBF����GPRS����EGPRS TBF,0��ʾGPRS TBF,1��ʾEGPRS TBF*/
    GMAC_MODE_ENUM_UINT16                   enAllocationChoice;                 /* ����ָ�䷽ʽ,�̶�����,��̬�����̬����;*//* _H2ASN_IeChoice_Export GMAC_MODE_ENUM_UINT16 */

    union                                                          /* _H2ASN_Skip */
    {                                                              /* _H2ASN_Skip */
        MPHP_FIXED_ALLOCATION_ST            stFixedAllocation;     /* _H2ASN_Skip */
        MPHP_DYNAMIC_ALLOCATION_ST          stDynamicAllocation;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        GMAC_MODE_ENUM_UINT16
        ******************************************************************************************************/
    }u;                                                 /* _H2ASN_Skip */

    MPHP_FREQUENCY_PARAMETERS_ST            stFreqParams;

}MPHP_UL_SETUP_REQ_ST;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usNeedLimitSendPower;               /*1:SIM�����ڸ�λ����Ҫ�������������27db;0:�������ƹ���*/
}MPHP_LIMIT_SEND_POWER_REQ_ST;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usNeedLimitSendPower;               /*1:SIM�����ڸ�λ����Ҫ�������������27db;0:�������ƹ���*/
}MPHP_LIMIT_SEND_POWER_CNF_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_UL_SETUP_CNF
 ��������  :  ����ϢMPHP_UL_SETUP_REQ��Ӧ����Ϣ��
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* ԭ������ */
    EDGE_CNF_RESULT_ENUM_UINT16             enSucessInd;
}MPHP_UL_SETUP_CNF_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_DL_SETUP_REQ
 ��������  :  ��������TBF�Ľ������Խ�����������ã�����PHY����֪�������ĸ�Ƶ����Щʱ϶���շ������ݡ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usMeasEnable;                       /* TBF�ڼ��Ƿ���Ҫ���Ų���,0=disbale,1=enable */
    VOS_UINT16                              usTbfMode;                          /* �������ֵ�ǰTBF����GPRS����EGPRS TBF,0��ʾGPRS TBF,1��ʾEGPRS TBF*/
    VOS_UINT16                              usMeasmentMapPresent;               /* usMeasmentMapPresent�ǹ̶�ģʽ��ʹ�õĲ�����Ŀǰ���Ժ󶼲���ʹ�ã�
                                                                                   ��������������·�RLCģʽ��0��ʾAMģʽ��1��ʾUMģʽ */
    VOS_UINT16                              usTimingAdvanceValue;               /* TA, [0,63],255=TA������ */
    VOS_UINT16                              usTimingAdvanceIndex;               /* PTCCH����, [0,15],255=������ */
    VOS_UINT16                              usTimingAdvanceTS;                  /* PTCCHʱ϶,[0,7],255=������ */
    VOS_UINT16                              usAlpha;                            /* �����������з��书��*/
    VOS_UINT16                              ausGammaTn[GAS_MAX_TIMESLOT_NUM];   /* ���ڼ������з��书��,[0,31]*/
    VOS_UINT16                              usBepPeriod2;                       /* ���ڼ���BEP */
    VOS_UINT16                              usP0;                               /* ���й��ز���,[0,15] ,255=������ */
    VOS_UINT16                              usPwrCtlMode;                       /* ���й���ģʽ,0=mode A,1=mode B */
    VOS_UINT16                              usPrMode;                           /* PR ģʽ,0=PR Mode A,1=PR mode B */
    VOS_UINT16                              usControlAck;                       /* ControlAck����ȡֵ 0��1:
                                                                                   1.EVT_MPHP_DL_SETUP_REQ������ ControlAck;
                                                                                   2.EVT_MPHP_DL_RECONFIG_REQ, 1:�ͷź��ٽ����µ�����TBF, 0:����������TBF*/
    VOS_UINT16                              usLinkQualMeasMode;                 /* 0��ʾ�Ȳ������Ų�����Ҳ����BEP����
                                                                                   1��ʾֻ�����Ų���������BEP����
                                                                                   2��ʾֻ���ѷ���ʱ϶��BEP���������Ų���
                                                                                   3��ʾ����BEP�������ֱ����Ų��� */
    MPHP_FREQUENCY_PARAMETERS_ST            stFreqParams;
    VOS_UINT32                              ulTBFStartTime;
    MPHP_DL_RESOURCE_ALLOCATION_ST          stDlResourceAlloc;
    MPHP_MEASUREMENT_MAPPING_ST             stMeasMapping;
}MPHP_DL_SETUP_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_DL_RECONFIG_REQ
 ��������  :  �Է����ŵ����������ã���������ù�����ֻ�и�����������仯��ô��������Ҳ��Ҫ��������㡣
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_DL_SETUP_REQ_ST    MPHP_DL_RECONFIG_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_DL_SETUP_CNF
 ��������  :  ����ϢMPHP_DL_SETUP_REQ��Ӧ����Ϣ��
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_UL_SETUP_CNF_ST    MPHP_DL_SETUP_CNF_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_UL_RECONFIG_REQ
 ��������  :  �Է����ŵ����������ã���������ù�����ֻ�и�����������仯��ô��������Ҳ��Ҫ��������㡣
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_UL_SETUP_REQ_ST    MPHP_UL_RECONFIG_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_UL_RECONFIG_CNF
 ��������  :  �����ŵ�������ȷ����Ϣ��
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_UL_SETUP_CNF_ST    MPHP_UL_RECONFIG_CNF_ST;

/*******************************************************************************
* MPHP_UL_RELEASE_REQ�ṹ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16 usRsv;
} MPHP_UL_RELEASE_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_UL_RELEASE_CNF
 ��������  :  ����TBF�ͷŵ�ȷ��ԭ��յ�MPHP_UL_RELEASE_REQ�������ʹ�ø�ԭ����Э��ջ�ظ�ȷ�ϡ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_UL_SETUP_CNF_ST    MPHP_UL_RELEASE_CNF_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_DL_RELEASE_REQ
 ��������  :  Э��ջ֪ͨ�����������������TBF���䡣
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_UL_RELEASE_REQ_ST  MPHP_DL_RELEASE_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_DL_RELEASE_CNF
 ��������  :  ����TBF�ͷŵ�ȷ��ԭ��յ�MPHP_DL_RELEASE_REQ�������ʹ�ø�ԭ����Э��ջ�ظ�ȷ�ϡ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_UL_SETUP_CNF_ST    MPHP_DL_RELEASE_CNF_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_DL_RECONFIG_CNF
 ��������  :  ��MPHP_DL_RECONFIG_REQ�Ļظ���
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_UL_SETUP_CNF_ST    MPHP_DL_RECONFIG_CNF_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_REPEAT_UL_FIXED_ALLOC_REQ
 ��������  :  �̶�����ṹ,����ԭ�ж��塣
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /* _H2ASN_Skip */ /* ԭ������ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usOperation;
    VOS_UINT16                              usTsOveride;
    VOS_UINT16                              usReserved;
    VOS_UINT32                              ulTBFStartTime;
} MPHP_REPEAT_UL_FIXED_ALLOC_REQ_ST;

/*******************************************************************************
* MPHP_REPEAT_UL_FIXED_ALLOC_CNF_ST
*******************************************************************************/
/*****************************************************************************
 ��Ϣ����  :  MPHP_REPEAT_UL_FIXED_ALLOC_CNF
 ��������  :  MPHP_REPEAT_UL_FIXED_ALLOC_REQ�Ļظ���
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_UL_SETUP_CNF_ST    MPHP_REPEAT_UL_FIXED_ALLOC_CNF_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_PDCH_RELEASE_REQ
 ��������  :  PDCH�ͷ�ԭ�Э��ջʹ�ø�ԭ���ͷ������PDCH��
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /* _H2ASN_Skip */ /* ԭ������ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usRemainTn;             /* BIT0��Ӧʱ϶0,BIT7��Ӧʱ϶7,��ӦbitΪ1��ʾ������Ӧʱ϶ */
} MPHP_PDCH_RELEASE_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_PDCH_RELEASE_CNF
 ��������  :  MPHP_PDCH_RELEASE_REQȷ��ԭ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_UL_SETUP_CNF_ST    MPHP_PDCH_RELEASE_CNF_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_SINGLE_BLOCK_REQ
 ��������  :  Э��ջͨ����ԭ��֪ͨ���������������ݿ�ķ��͡�
              ���׶ν���ʱ��Packet Resource Request�ķ��ͣ�����㷢����������Ҫ
              ����ԭ��ָʾ���ж��Ƿ���Ҫ��������PACCH�������Ҫ��������PACCH�ŵ���
              ��ô�������Ҫ����ͬ���ŵ��ϼ���PACCH���
              ��Ӧ������Packet Polling Request������Packet Control Acknowledge�ķ��͡�
              �����ڿ���̬ʱ������෢�Ͳ������档
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usAlpha;                /* �����������з��书��*/
    VOS_UINT16                              usGammaTn;              /* �����������з��书��*/
    VOS_UINT16                              usTimingAdvanceValue;   /* TA, [0,63],255=TA������ */
    VOS_UINT16                              usDlReceive;            /* ����ָʾ���鷢�ͺ��Ƿ���Ҫ��������PACCH,0����Ҫ��1��Ҫ*/
    VOS_UINT16                              usChannelCodingType;    /* �ŵ���������,0:8-bit,1:11-bit,2:23Byte */
    MPHP_FREQUENCY_PARAMETERS_ST            stFreqParams;
    VOS_UINT32                              ulFrameNumber;          /* ���͵�֡�� */
    VOS_UINT16                              usTimeSlot;             /* ����ʱ϶�� */
    VOS_UINT16                              usDataLenth;            /* ���͵����ݳ��ȣ���λbyte */
    VOS_UINT16                              ausData[12];            /* ���͵����� */

}MPHP_SINGLE_BLOCK_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_SINGLE_BLOCK_CNF
 ��������  :  ��MPHP_SINGLE_BLOCK_REQ�Ļظ���
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_UL_SETUP_CNF_ST    MPHP_SINGLE_BLOCK_CNF_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_MULTI_BLOCK_REQ
 ��������  :  Э��ջͨ����ԭ��֪ͨ���������������ݿ�ķ��͡�
              �������׶ν���ʱ��Packet Resource Request��ADDITIONAL MS RADIO
              ACCESS CAPABILITIES ����packet uplink dummy control block/Packet
              Measurement Report������Ϣ���ķ��ͣ�����㷢����������Ҫ����ԭ��
              ָʾ���ж��Ƿ���Ҫ��������PACCH�������Ҫ��������PACCH�ŵ�����ô
              �������Ҫ����ͬ���ŵ��ϼ���PACCH���
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usAlpha;                /* �����������з��书��*/
    VOS_UINT16                              usGammaTn;              /* �����������з��书��*/
    VOS_UINT16                              usTimingAdvanceValue;   /* TA, [0,63],255=TA������ */
    VOS_UINT16                              usDlReceive;            /* ����ָʾ���鷢�ͺ��Ƿ���Ҫ��������PACCH,0����Ҫ��1��Ҫ*/
    VOS_UINT16                              usChannelCodingType;    /* �ŵ���������,0:8-bit,1:11-bit,2:23Byte */
    MPHP_FREQUENCY_PARAMETERS_ST            stFreqParams;
    VOS_UINT32                              ulFrameNumber;          /* ���͵�֡�� */
    VOS_UINT16                              usTimeSlot;             /* ����ʱ϶�� */
    MPHP_MULTI_BLOCK_LEN_ENUM_UINT16        enDataLenth;            /* ���͵����ݳ��ȣ���λbyte */
    VOS_UINT16                              ausData[24];

}MPHP_MULTI_BLOCK_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_MULTI_BLOCK_CNF
 ��������  :  ��MPHP_MULTI_BLOCK_REQ�Ļظ���
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_UL_SETUP_CNF_ST    MPHP_MULTI_BLOCK_CNF_ST;


typedef enum
{
    ID_MPHP_PACKET_OTHER_MSG                = 0x0000,
    
    ID_MPHP_PACKET_CELL_CHANGE_FAILURE      = 0x0100,
    ID_MPHP_PACKET_MOBILE_TBF_STATUS        = 0x0106,
    ID_MPHP_PACKET_PSI_STATUS               = 0x0107,
    ID_MPHP_PACKET_CELL_CHANGE_NOTIFICATION = 0x010C,
    ID_MPHP_PACKET_SI_STATUS                = 0x010D
}PHY_GRR_AIR_MSG_TYPE_ENUM;

typedef VOS_UINT16 PHY_GRR_AIR_MSG_TYPE_ENUM_UINT16;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    GAS_PHY_CTRL_BLK_PRIO_ENUM_UINT16       usPrio;             /* ������Ϣ�����ȼ� */
    PHY_GRR_AIR_MSG_TYPE_ENUM_UINT16        usAirMsgType;       /* �տ���Ϣ���� */
    VOS_UINT16                              usReserved;
    VOS_UINT16                              ausData[12];
}MPHP_MSGDATA_REQ_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    PHY_GRR_AIR_MSG_TYPE_ENUM_UINT16        usAirMsgType;       /* �տ���Ϣ���� */
}MPHP_MSGDATA_CNF_ST;


/*****************************************************************************
* MPHP_SUSPENSION_REQ�ṹ
*******************************************************************************/
typedef MPHP_UL_RELEASE_REQ_ST  MPHP_SUSPENSION_REQ_ST;

/*******************************************************************************
* MPHP_SUSPENSION_CNF�ṹ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usReserved;
} MPHP_SUSPENSION_CNF_ST;

/*******************************************************************************
* MPHP_RESUME_REQ�ṹ
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    GAS_PHY_RESUME_METHOD_ENUM_UINT16       usResumeInd;        /* 0: �ָ�������֮ǰ״̬,1: �뿪����, �ͷ����ݴ����ŵ�*/
} MPHP_RESUME_REQ_ST;

/*******************************************************************************
* MPHP_RESUME_CNF�ṹ
*******************************************************************************/
typedef MPHP_UL_SETUP_CNF_ST    MPHP_RESUME_CNF_ST;

/*******************************************************************************
 ��Ϣ����  :  MPHP_RA_REQ
 ��������  :  Э��ջͨ����ԭ��֪ͨ�������PRACH�����������
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usABType;           /* �������ݳ���,0Ϊ8bit��1Ϊ11bit */
    VOS_UINT16                              usTsc;              /* 8PSK��TSC1;GMSK��TSC0 */
    VOS_UINT16                              usRachData;         /* ������������,8bit���ݻ�11bit���� */
    VOS_UINT16                              usSkipFrames;       /* ����PRACHǰ��Ҫ�ȴ���֡����,���ֵ 217+50,�μ�44060 Table 12.14.2 */
    VOS_UINT16                              usRsv;              /* Ϊ���ֽڶ������ӵı����� */
}MPHP_RA_REQ_ST;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usAcsBurstType;     /* ��������,8bit��11bit */
    VOS_UINT32                              ulFn;               /* ֡�� */
    VOS_UINT16                              usRachData;         /* ������������,8bit���ݻ�11bit���� */
    VOS_UINT16                              SuccessInd;         /* �ɹ���־,0Ϊ�ɹ�, 1Ϊʧ�� */
}MPHP_RA_CNF_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_RA_ABORT_REQ
 ��������  :  Э��ջͨ����ԭ��֪ͨ��������PRACH������̣��������Ҫ��������PAGCH��
              ��ôЭ��ջʹ�ò���MonitorPagch��ָʾ��������PAGCH.
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*******************************************************************************/
typedef enum
{
    PHY_MONI_PAGCH_FLG_NEEDLESS             =   0,
    PHY_MONI_PAGCH_FLG_NEED                 =   1
}PHY_MONI_PAGCH_FLG_ENUM;
typedef VOS_UINT16 PHY_MONI_PAGCH_FLG_ENUM_UINT16;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              enMonitorPagch;     /* ָʾPHY�Ƿ����PAGCH,0��ʾ���ټ�����1��ʾ�������� */
}MPHP_RA_ABORT_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_TIMING_ADVANCE_REQ
 ��������  :  Э��ջͨ����ԭ��֪ͨ�������¶�ʱ������
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usTimingAdvanceValue;   /* TA, [0,63],255=TA������ */
    VOS_UINT16                              usTimingAdvanceIndex;   /* PTCCH����, [0,15],255=������ */
    VOS_UINT16                              usTimingAdvanceTS;      /* PTCCHʱ϶,[0,7],255=������ */
}MPHP_TIMING_ADVANCE_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_TIMING_ADVANCE_CNF
 ��������  :  MPHP_TIMING_ADVANCE_REQ��ȷ��ԭ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef MPHP_UL_SETUP_CNF_ST    MPHP_TIMING_ADVANCE_CNF_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_POWER_PARAM_UPDATE_REQ
 ��������  :  Э��ջͨ����ԭ��֪ͨ�������¹��ز�����
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usAlpha;                            /* �����������з��书��*/
    VOS_UINT16                              ausGammaTn[GAS_MAX_TIMESLOT_NUM];   /* ���ڼ������з��书��,[0,31]*/
    VOS_UINT16                              usKTAvgT;                           /* ���鴫��ģʽ�¹��ʿ����м����ź�ǿ���˲����ڲ��� */
    VOS_UINT16                              usKTAvgW;                           /* ���鴫��ģʽ�¹��ʿ����м����ź�ǿ���˲����ڲ��� */
    VOS_UINT16                              usKTAvgI;                           /* ���ʿ����м������ǿ���˲�������                 */
    VOS_UINT16                              usPcMeasCh;                         /* �������ŵ�                                       */
    VOS_UINT16                              usPb;                               /* Pbcch���������BCCH�ز��Ĺ��ʼ�Сֵ              */
    VOS_UINT16                              usReserved;
} MPHP_POWER_PARAM_UPDATE_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_POWER_PARAM_UPDATE_CNF
 ��������  :  MPHP_POWER_PARAM_UPDATE_REQ��ȷ��ԭ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usCause;
} MPHP_POWER_PARAM_UPDATE_CNF_ST;

/*******************************************************************************
* MPHP_ARFCN_CHANNEL_GROUP�ṹ:���õ�ǰ����
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usArfcn;
    VOS_UINT16                              usTimeSlotAllocation;
}MPHP_ARFCN_CHANNEL_GROUP_ST;

/*******************************************************************************
* MPHP_MA_CHANNEL_GROUP�ṹ:���õ�ǰ����
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usHSN;
    VOS_UINT16                              usMAIO;
    VOS_UINT16                              usMaNum;                            /* Ƶ���б��е�Ƶ����� */
    VOS_UINT16                              ausMaList[MPHP_MA_LIST_FREQ_MAX];
    VOS_UINT16                              usTimeSlotAllocation;
}MPHP_MA_CHANNEL_GROUP_ST;

/*******************************************************************************
* MPHP_INT_MEAS_CHANNEL_LIST�ṹ:���õ�ǰ����
*******************************************************************************/
typedef struct
{
   VOS_UINT16                               usArfcnChannelGroupNumber;
   MPHP_ARFCN_CHANNEL_GROUP_ST              astArfcnChannelGroupList[MPHP_INT_CHANNEL_GROUP_MAX_NUM];
   VOS_UINT16                               usMaChannelGroupNumber;
   MPHP_MA_CHANNEL_GROUP_ST                 astMaChannelGroupList[MPHP_INT_MA_CHANNEL_GROUP_MAX_NUM];
}MPHP_INT_MEAS_CHANNEL_LIST_ST;


/*******************************************************************************
* MPHP_QUALITY_MEAS_REQ_ST�ṹ: ���õ�ǰ����
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    MPHP_INT_MEAS_CHANNEL_LIST_ST           stIntMeasChannelList;   /*�����INT_MEAS_CHANNEL_LISTʱ�ĸ��Ų����ŵ���*/
    VOS_UINT16                              Reserved;
} MPHP_QUALITY_MEAS_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_OUT_OF_MEM_IND
 ��������  :  ��ԭ�������ڣ�EGPRS������̬����ȷ��ָʾ��������������ݵ��ڴ�ռ�
              ���㣨�ڴ治�㽫���������ٶ��½�����
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    GAS_PHY_MEM_IND_ENUM_UINT16             usState;                /* 1��ʾIR�ڴ治�㣬0��ʾ�˳��ڴ治��״̬ */
}MPHP_OUT_OF_MEM_IND_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_PAGING_MODE_REQ
 ��������  :  ����Ѱ��ģʽ����ԭ�Э��ջʹ�ø�ԭ��������Ѱ��ģʽ�������á�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usPagingMode;           /* 0:Normal;1:Extended;2:ReOrganization;3:Same as before; */
}MPHP_PAGING_MODE_REQ_ST;

/*****************************************************************************
 ��Ϣ����  :  MPHP_PAGING_MODE_CNF
 ��������  :  ����С��PBCCH�ͷ�ȷ��ԭ�
 �޸���ʷ  :
  1.��    ��    : 2007��10��06��
    ��    ��    : fangjian(48555)
    �޸�����    : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                              usSuccessInd;
}MPHP_PAGING_MODE_CNF_ST;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/******************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 ��������
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif /* __cplusplus */


#endif /* __PHY_GRR_INTERFACE_H__ */


