

#ifndef __TAFAPSCTX_H__
#define __TAFAPSCTX_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafFsm.h"
#include "TafApsTimerMgmt.h"
#include "TafApsDsFlowStats.h"
#include "AtMnInterface.h"
#include "SmEsmInterface.h"
#include "MmcApsInterface.h"
#include "Taf_Aps.h"
#include "TafApsApi.h"

#include "NasNvInterface.h"

#include "mdrv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_APS_MAX_MSG_BUFFER_LEN                      (1500)                  /* �������󳤶� */
#define TAF_APS_MAX_MSG_QUEUE_NUM                       (22)                    /* ��󻺴�ĸ��� */

#define TAF_APS_RAB_ID_OFFSET                           (5)                     /* ��ǰ������Ķ�����5��15�������һ��5��ƫ���� */

#define TAF_APS_RAB_ID_MIN                              (5)                     /* RAB ID��ȡֵ��Χ����С��5 */
#define TAF_APS_RAB_ID_MAX                              (15)                    /* RAB ID��ȡֵ��Χ�������15 */

/* ���RAB���ظ��� */
#define TAF_APS_MAX_RAB_NUM                             (15)                    /* RAB ID��ȡֵ��Χ�������15 */


#define TAF_APS_MAX_CMD_BUFFER_QUEUE_SIZE               (11)                    /* �ȴ���Ϣ����Ķ��г��ȣ�Ŀǰ�ٶ�Ϊ10�� */

#define TAF_APS_INVALID_PDPID                           (0xFF)                  /* ��Ч��PDP ID */
#define TAF_APS_INVALID_CID                             (0xFF)                  /* ��Ч��CID */
#define TAF_APS_INVALID_CLIENTID                        (0xFFFE)                /* ��Ч��CLIENT ID */
#define TAF_APS_INVALID_OPID                            (0xFF)                  /* ��Ч��OPID ID */

#define TAF_APS_MAX_MSG_QUEUE_SIZE                      (11)                    /* �ڲ���Ϣ�������ĳ��ȣ�
                                                                                   ��ǰ״̬���ڲ�������Ӧ�����ʮ��PDPʵ�壬Ŀǰʹ�õĳ�����12 */
#define TAF_APS_INVALID_INTERNAL_MSG_ID                 (0xFFFF)                /* ��ϢID����Чֵ */

#define TAF_APS_32BIT_DATA_LEN                          (32)                    /* 32λ���ݵ�bit���� */
#define TAF_APS_DEFAULT_CID                             (0)                     /* Ĭ�ϳ�����ʹ�õ�CID��CID0 */
#define TAF_APS_OCTET_MOVE_THREE_BITS                   (0x03)                  /* ��һ���ֽ��ƶ�3λ */

#define TAF_APS_1_KBYTE_1024_BYTE                       (1024)

/* PDP�����10��֮�ڣ��������û������෢��PDP�������� */
#define TAF_APS_PDP_ACT_LIMIT_NO_DELAY_COUNT_THRESHOLD   (10)

/* PDP�����11-19��֮�ڣ�����10s��������������ʱ�� */
#define TAF_APS_PDP_ACT_LIMIT_STEP_DELAY_COUNT_THRESHOLD (19)
#define TAF_APS_PDP_ACT_LIMIT_STEP_TIME                  (10)

/* PDP�����19��(����19��)���ϣ�����90sʱ��������ʱ�� */
#define TAF_APS_PDP_ACT_LIMIT_AVERAGE_DELAY_TIME         (90)

/* PDP��ͣ���ʱ��ʱ�����������ֵ */
#define TAF_APS_PDP_ACT_LIMIT_RANDOM_TIME_THRESHOLD      (45)

/* ��ʧ�ܴ�����10��������ʱ��PDP��ͣ���ʱ��ʹ�����ʱ�� */
#define TAF_APS_PDP_ACT_LIMIT_RANDOM_TIME_FAILCOUNT      (10)

/* TI_TAF_APS_LIMIT_PDP_ACT��ʱ�������κ�PDP ID������Զ���һ����Чֵ */
#define TAF_APS_PDP_ACT_LIMIT_PDP_ID                    (0xFF)

#define TAF_APS_DSFLOW_AT_REPORT_PERIOD                 (2)

/* Modified by y00314741 for CDMA Iteration 11, 2015-3-30, begin */
#define TAF_APS_HRPD_DEFAULT_SR_ID                       (1)

#define TAF_APS_CDMA_EPDSZID_LIST_MAX_LEN                   ( 15 )
#define TAF_APS_CDMA_EPDSZID_DEFAULT_MAX_LEN                ( 4 )
#define TAF_APS_CDMA_EPDSZID_DEFAULT_MIN_LEN                ( 1 )

#define TAF_APS_CDMA_EPDSZID_INVAILD_SID                    (0xFFFF)
#define TAF_APS_CDMA_EPDSZID_INVAILD_NID                    (0)
#define TAF_APS_CDMA_EPDSZID_INVAILD_PZID                   (0xFF)

#define TAF_APS_CDMA_EPDSZID_INVAILD_SEQ_NUM                (0xFF)

#define TAF_APS_CDATA_EPDSZID_HAT_DEFAULT_LEN               ( 30  )             /* UNIT:S */
#define TAF_APS_CDATA_EPDSZID_HT_DEFAULT_LEN                ( 60  )             /* UNIT:S */

#define TAF_APS_MAX_SLICE_VALUE                             (0xFFFFFFFF)

/**
 * Traffic channel is suspended.
 */
#define TAF_APS_CDMA_TC_SUSPENDED                           ( 1 )
/**
 * Traffic channel is resumed.
 */
#define TAF_APS_CDMA_TC_RESUMED                             ( 0 )

#define TAF_APS_CDMA_INVALID_SR_ID                          ( 0 )

#define TAF_APS_CDMA_INVALID_PDN_ID                         ( 0xFF )


#define TAF_APS_NSAPI_INVALID_VALUE                         ( 0 )

#define TAF_APS_GET_MULTI_DFS_SUPPORT_FLG()                 (g_stTafApsCtx.stSwitchDdrRateInfo.ulMultiDfsFlg)

#define TAF_APS_GET_MULTI_DFS_PROFILE_NUM(dfsType)          (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[dfsType].ulProfileNum)
#define TAF_APS_GET_MULTI_DFS_PROFILE_DL_RATE(dfsType, i)   (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[dfsType].astProfile[i].ulDlRate)
#define TAF_APS_GET_MULTI_DFS_PROFILE_UL_RATE(dfsType, i)   (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[dfsType].astProfile[i].ulUlRate)
#define TAF_APS_GET_MULTI_DFS_PROFILE_DDR_BAND(dfsType, i)  (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[dfsType].astProfile[i].ulDdrBand)

#define TAF_APS_GET_DFS_PROFILE_NUM()                       (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[0].ulProfileNum)
#define TAF_APS_GET_DFS_PROFILE_DL_RATE(i)                  (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[0].astProfile[i].ulDlRate)
#define TAF_APS_GET_DFS_PROFILE_UL_RATE(i)                  (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[0].astProfile[i].ulUlRate)
#define TAF_APS_GET_DFS_PROFILE_DDR_BAND(i)                 (g_stTafApsCtx.stSwitchDdrRateInfo.astDfsConfig[0].astProfile[i].ulDdrBand)

#define TAF_APS_DFS_REQUEST_SUCC_CNT(i)                     (g_stTafApsCtx.stSwitchDdrRateInfo.stDfsDebugInfo.ulRequestSucCnt  += i)
#define TAF_APS_DFS_REQUEST_FAIL_CNT(i)                     (g_stTafApsCtx.stSwitchDdrRateInfo.stDfsDebugInfo.ulRequestFailCnt  += i)
#define TAF_APS_DFS_UPDATE_SUCC_CNT(i)                      (g_stTafApsCtx.stSwitchDdrRateInfo.stDfsDebugInfo.ulUpdateSucCnt  += i)
#define TAF_APS_DFS_UPDATE_FAIL_CNT(i)                      (g_stTafApsCtx.stSwitchDdrRateInfo.stDfsDebugInfo.ulUpdateFailCnt += i)

#define TAF_APS_GET_DSFLOW_RELEASE_DFS()                    (g_stTafApsCtx.stSwitchDdrRateInfo.ulMinBand)
#define TAF_APS_GET_DSFLOW_MIN_DDR_BAND()                   (g_stTafApsCtx.stSwitchDdrRateInfo.ulMinBand)
#define TAF_APS_GET_DSFLOW_MAX_DDR_BAND()                   (g_stTafApsCtx.stSwitchDdrRateInfo.ulMaxBand)


#define TAF_APS_GET_RAT_TYPE_IN_SUSPEND()                   (g_stTafApsCtx.enCurrSuspendRatType)
#define TAF_APS_SET_RAT_TYPE_IN_SUSPEND(ratType)            (g_stTafApsCtx.enCurrSuspendRatType = (ratType))

#define TAF_APS_SET_CDATA_SUSPEND_STATUS(ucStatus)          (g_stTafApsCtx.stCdataCtx.ucSuspendStatus = (ucStatus))
#define TAF_APS_GET_CDATA_SUSPEND_STATUS()                  (g_stTafApsCtx.stCdataCtx.ucSuspendStatus)


#define TAF_APS_SET_CDATA_MTU(value)                        (g_stTafApsCtx.stCdataCtx.usMtu = (value))
#define TAF_APS_GET_CDATA_MTU()                             (g_stTafApsCtx.stCdataCtx.usMtu)
#define TAF_APS_MIN(x, y)\
        (((x)<(y))?(x):(y))

/* Modified by y00314741 for CDMA Iteration 11, 2015-4-8, end */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum TAF_APS_FSM_ID_ENUM
{
    /* TAF APS MAIN ״̬������ǰ������̬ */
    TAF_APS_FSM_MAIN                                    = 0X00,

    /* TAF APS MS ACTIVATING״̬������ǰ��UE���𼤻���������� */
    TAF_APS_FSM_MS_ACTIVATING                           = 0X01,

    /* TAF APS NW ACTIVATING״̬������ǰ��NW���𼤻���������� */
    TAF_APS_FSM_NW_ACTIVATING                           = 0X02,

    /* TAF APS MS DEACTIVATING״̬������ǰ��UE����ȥ������������� */
    TAF_APS_FSM_MS_DEACTIVATING                         = 0X03,

    /* TAF APS MS MODIFYING״̬������ǰ��UE����MODIFY���������� */
    TAF_APS_FSM_MS_MODIFYING                            = 0X04,

    /* TAF APS CDATA ESTING״̬������ǰ��CDMAģʽ�·������ݷ������ӽ��������� */
    TAF_APS_FSM_CDATA_ESTING                            = 0X05,

    /* TAF APS CDATA DISCING״̬������ǰ��CDMAģʽ�����ݷ������ӹҶϹ����� */
    TAF_APS_FSM_CDATA_DISCING                           = 0X06,

    /* Added by y00314741 for CDMA Iteration 11, 2015-4-7, begin */
    /* TAF APS CDATA HANDOFF״̬������ǰ��CDMAģʽ�����ݷ��������л������� */
    TAF_APS_FSM_CDATA_HANDOFF                           = 0X07,
    /* Added by y00314741 for CDMA Iteration 11, 2015-4-7, end */

    TAF_APS_FSM_BUTT

};
typedef VOS_UINT32 TAF_APS_FSM_ID_ENUM_UINT32;


enum TAF_APS_DFS_TYPE_ENUM
{
    TAF_APS_DFS_TYPE_BASE               = 0x00,                                 /*��ǰδ���κ�������פ��*/
    TAF_APS_DFS_TYPE_GSM                = 0x01,                                 /* GSM��DFS */
    TAF_APS_DFS_TYPE_WCDMA              = 0x02,                                 /* WCDMA��DFS */
    TAF_APS_DFS_TYPE_LTE                = 0x03,                                 /* LTE��DFS */
    TAF_APS_DFS_TYPE_TD_WCDMA           = 0x04,                                 /* TD-WCDMA��DFS */
    TAF_APS_DFS_TYPE_CDMA               = 0x05,                                 /* CDMA��DFS */
    TAF_APS_DFS_TYPE_BUTT                                                       /* ��Ч�Ľ��뼼�� */
};
typedef VOS_UINT32 TAF_APS_DFS_TYPE_ENUM_UINT32;



/** ****************************************************************************
 * Name        : TAF_APS_CDATA_QOS_MODE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_APS_CDATA_QOS_MODE_ENUM
{
    TAF_APS_CDATA_QOS_MODE_ONE          = 0x00,/* _H2ASN_MsgChoice TAF_APS_CDATA_1X_QOS_ASSURED_PARA_STRU */
    TAF_APS_CDATA_QOS_MODE_TWO          = 0x01,/* _H2ASN_MsgChoice TAF_APS_CDATA_1X_QOS_NON_ASSURED_PARA_STRU */
    TAF_APS_CDATA_QOS_MODE_BUTT         = 0x02
};
typedef VOS_UINT8 TAF_APS_CDATA_QOS_MODE_ENUM_UINT8;



/** ****************************************************************************
 * Name        : TAF_APS_CDATA_EPDSZID_CHG_REORIG_TYPE_ENUM_UINT8
 * Description :
 *******************************************************************************/
enum TAF_APS_CDATA_EPDSZID_CHG_REORIG_SCENE_ENUM
{
    TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG                         = 0x00,     /* Don't start re-orig */
    TAF_APS_CDATA_EPDSZID_CHG_REORIG_ENTER_DORMANT              = 0x01,     /* Start re-Orig before gone to dormant */
    TAF_APS_CDATA_EPDSZID_CHG_REORIG_AFTER_TC_RELEASE           = 0x02,     /* after Traffic channel release, Start re-Orig */
    TAF_APS_CDATA_EPDSZID_CHG_REORIG_AFTER_DORMANT_TI_EXPIRED   = 0x03,     /* Dormant Ti expired, Start re-orig */

    TAF_APS_CDATA_EPDSZID_CHG_REORIG_BUTT
};
typedef VOS_UINT8 TAF_APS_CDATA_EPDSZID_CHG_REORIG_SCENE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM_UINT8
 * Description :
 *******************************************************************************/
enum TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM
{
    TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID,
    TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID_SID,
    TAF_APS_EPDSZID_SUPPORT_TYPE_PDSZID_SID_NID,

    TAF_APS_EPDSZID_TYPE_BUTT
};
typedef VOS_UINT8 TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM_UINT8;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern VOS_UINT32                              g_ulApsTestStub;


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/** ****************************************************************************
 * Name        : TAF_APS_CDATA_EPDSZID_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usSid;        /* System Identifier */
    VOS_UINT16                          usNid;        /* Network Identifier */
    VOS_UINT8                           ucPzid;       /* Packet Zone Identifier */
    VOS_UINT8                           ucReserved[3];
    VOS_UINT32                          ulBeginSlice; /* Record Begin SliceTimer */
}TAF_APS_CDATA_EPDSZID_STRU;

/*******************************************************************************
 * Name        : TAF_APS_CDATA_EPDSZID_CTX_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucEpdszidHysEnableFlg;      /* Enable:VOS_TRUE(default) Disable:VOS_FALSE */
    VOS_UINT8                                               ucEpdszidHai;               /* default: VOS_FALSE */
    TAF_APS_CDATA_EPDSZID_CHG_REORIG_SCENE_ENUM_UINT8       enReOrigScene;              /* default: 0 */
    VOS_UINT8                                               ucEpdszidMaxListLen;        /* List len allowed by BS: default: 0 */
    VOS_UINT8                                               ucEpdszidCurrListLen;
    TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM_UINT8                 enEpdszidType;              /*Pzid, Pzid-sid-nid, Pzid-sid */
    VOS_UINT8                                               ucHatTimerLen;
    VOS_UINT8                                               ucHtTimerLen;
    TAF_APS_CDATA_EPDSZID_STRU                              stCurrEpdszid;
    TAF_APS_CDATA_EPDSZID_STRU                              astEpdszidList[TAF_APS_CDMA_EPDSZID_LIST_MAX_LEN];
}TAF_APS_CDATA_EPDSZID_CTX_STRU;

/*******************************************************************************
 * Name        : TAF_APS_CDATA_HRPD_EPDSZID_CTX_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usSid;        /* System Identifier */
    VOS_UINT16                          usNid;        /* Network Identifier */
    VOS_UINT8                           ucPzid;       /* Packet Zone Identifier */
    VOS_UINT8                           ucReserved[3];
}TAF_APS_CDATA_HRPD_EPDSZID_CTX_STRU;

/** ****************************************************************************
 * Name        : TAF_APS_CDATA_CTX_STRU
 *
 * Description : New add, Belong to TAF_APS_CONTEXT_STRU.
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSocmDormTiVal; /* Default value: 0 */
    VOS_UINT32                          ulUserCfgDormTival;

    /* Added by y00314741 for CDMA Iteration 11, 2015-4-2, begin */
    TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32  enCdataDialMode;
    /* Added by y00314741 for CDMA Iteration 11, 2015-4-2, end */

    VOS_UINT8                           ucSuspendStatus;
    VOS_UINT8                           aucReserved[1];
    VOS_UINT8                           uc1XPktDtInactivityTmrLen;    /* 1X Packet Data Inactivity Timer Len  */

    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-2, begin */
    VOS_UINT8                           ucEvdoPktDtInactivityTmrLen;  /* EVDO Packet Data Inactivity Timer Len  */
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-2, end */

    VOS_UINT16                          usMtu;
    TAF_APS_CDATA_SO_TYPE_ENUM_UINT16   enSoInitType;

    TAF_APS_RAT_TYPE_ENUM_UINT32        enLastOirgOnRatType;

    TAF_APS_CDATA_HRPD_EPDSZID_CTX_STRU stHrpdEpdszidInfo;

    TAF_APS_CDATA_EPDSZID_CTX_STRU      stEpdszidCtx;
}TAF_APS_CDATA_CTX_STRU;

typedef SM_ESM_EPS_BEARER_INFO_IND_STRU TAF_APS_EPS_BEARER_INFO_IND_STRU;
typedef struct
{
    VOS_UINT8                           ucRabActiveFlag;                        /*��ʶ��RAB�Ƿ񼤻�*/
    VOS_UINT8                           aucReserve[3];                          /*����λ*/

    VOS_UINT32                          ulStartLinkTime;                        /*��ǰ���ӿ�ʼʱ��*/
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;                      /*��ǰ����������Ϣ�������һ��PDP���ӵ�������Ϣ */
    TAF_DSFLOW_INFO_STRU                stTotalFlowInfo;                        /*�ۻ�������Ϣ����RAB��ʷ���������ۼӵ�������Ϣ */

}TAF_APS_DSFLOW_STATS_STRU;
typedef struct
{
    VOS_UINT32                          ulRequestSucCnt;
    VOS_UINT32                          ulRequestFailCnt;
    VOS_UINT32                          ulUpdateSucCnt;                         /* ͶƱ�ɹ����� */
    VOS_UINT32                          ulUpdateFailCnt;                        /* ͶƱʧ�ܴ��� */
}TAF_APS_DFS_DEBUG_INFO_STRU;


typedef struct
{
    VOS_INT32                           iDfsReqId;                              /* DDR��ƵͶƱ����ID */
    VOS_UINT32                          ulReqValue;                             /* DDR��ƵͶƱ����ֵ */
    VOS_UINT32                          ulSetMaxFlag;                           /* �������Ƶ�ʵı�ʶ */

    VOS_UINT32                          ulMultiDfsFlg;
    TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU  astDfsConfig[TAF_NVIM_DIFF_DFS_NUM];
    TAF_APS_DFS_DEBUG_INFO_STRU         stDfsDebugInfo;

    VOS_UINT32                          ulMinBand;                              /* ��СDDRƵ�� */
    VOS_UINT32                          ulMaxBand;                              /* ���DDRƵ�� */
}TAF_APS_SWITCH_DDR_RATE_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucDsFlowSave2NvFlg;                     /* ��ʶ�Ƿ���Ҫ������ʷ������Ϣ��NV�� */
    VOS_UINT8                           ucDsFlowSavePeriod;                     /* ����дNV������ */

    VOS_UINT8                           ucDsFlowOMReportFlg;                    /* ��ʶ�Ƿ����OM�����ϱ� */
    VOS_UINT8                           ucDsFlowATRptPeriod;                    /* AT�˿������ϱ������ڵ�λs */
    VOS_UINT8                           ucDsFlowOMRptPeriod;                    /* OM�����ϱ������ڵ�λs */
    VOS_UINT8                           ucDsFlowATRptTmrExpCnt;                 /* AT�˿������ϱ�ʱ�������ڿ����ϱ����� */
    VOS_UINT8                           ucDsFlowOMRptTmrExpCnt;                 /* OM�����ϱ�ʱ�������ڿ����ϱ����� */
    VOS_UINT8                           aucReserved[1];


    VOS_UINT32                          ulFluxThresRptFlg;                      /* AP�����ϱ�������� */
    VOS_UINT32                          ulFluxThresKByte;                       /* AP�����ϱ�����, ��λKByte */
    VOS_UINT32                          ulFluxThresHigh;                        /* AP�����ϱ����޸��ĸ��ֽ�, ��λByte */
    VOS_UINT32                          ulFluxThresLow;                         /* AP�����ϱ����޵��ĸ��ֽ�, ��λByte */
    VOS_UINT32                          ulTotalFluxHigh;                        /* AP�����ۼ��ϱ����ĸ��ֽ�, ��λByte */
    VOS_UINT32                          ulTotalFluxLow;                         /* AP�����ۼ��ϱ����ĸ��ֽ�, ��λByte */

    TAF_APS_DSFLOW_STATS_STRU           astApsDsFlowStats[TAF_APS_MAX_RAB_NUM]; /* ������RABIDΪ��λ���������� */

}TAF_APS_DSFLOW_STATS_CTX_STRU;



typedef struct
{
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId;
    VOS_UINT32                         *pulMsgInfo;
    VOS_UINT32                          ulMsgInfoLen;
    VOS_UINT32                          ulPara;
}TAF_APS_CMD_BUFFER_STRU;


typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucEntryMsgBuffer[TAF_APS_MAX_MSG_BUFFER_LEN];
} TAF_APS_ENTRY_MSG_STRU;


typedef struct
{
    TAF_APS_ENTRY_MSG_STRU              stMsgEntry;                             /* ����ľ������� */
}TAF_APS_CACHE_MSG_INFO_STRU;
typedef struct
{
    VOS_UINT32                          ucCurrIndex;                            /* ��¼��ǰ�������index */
    VOS_UINT8                           ucCacheMsgNum;                          /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    TAF_APS_CACHE_MSG_INFO_STRU         astMsgQueue[TAF_APS_MAX_MSG_QUEUE_NUM]; /* APS����Ϣ�������飬�洢���Ǵ�ͨ����Ϣͷ����Ϣ */
}TAF_APS_MSG_QUEUE_STRU;
typedef struct
{
    /* TAF APS��Ϣ����*/
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType;
    VOS_UINT8                           ucPdpid;
    VOS_UINT8                           ucReserved;
} TAF_APS_PS_CALL_ANSWER_MSG_STRU;
typedef struct
{
    TAF_APS_PS_CALL_ANSWER_MSG_STRU     stAnswerMsg;

} TAF_APS_FSM_NW_ACTIVATING_CTX_STRU;


typedef union
{
    TAF_APS_FSM_NW_ACTIVATING_CTX_STRU  stNwActivatingCtx;

}TAF_APS_FSM_EXTRA_CTX_UNION;


typedef struct
{
    /* ״̬������ָ��,ָ��ΪNULL��ʾ��ǰ״̬����Ч  */
    TAF_FSM_DESC_STRU                  *pstFsmDesc;

    /* ��ǰ״̬����ʶ */
    TAF_APS_FSM_ID_ENUM_UINT32          enFsmId;

    /* ��ǰ״̬ */
    VOS_UINT32                          ulState;                            /*  */

    /* ��״̬�������ϢMSGID������  */
    TAF_APS_ENTRY_MSG_STRU              stEntryMsg;

    /* ״̬������ */
    TAF_APS_FSM_EXTRA_CTX_UNION         unFsmCtx;
}TAF_APS_SUB_FSM_CTX_STRU;


typedef struct
{
    /* ״̬������ָ��,ָ��ΪNULL��ʾ��ǰ״̬����Ч  */
    TAF_FSM_DESC_STRU                  *pstFsmDesc;

    /* ��ǰ״̬����ʶ */
    TAF_APS_FSM_ID_ENUM_UINT32          enFsmId;

    /* ��ǰ״̬ */
    VOS_UINT32                          ulState;                            /*  */
}TAF_APS_MAIN_FSM_CTX_STRU;


typedef struct
{
    TAF_APS_MAIN_FSM_CTX_STRU           stMainFsm;                              /* ��״̬�� */
    TAF_APS_SUB_FSM_CTX_STRU            stSubFsm;                               /* ��״̬�� */

    /**************************************************************************
                        TAF APS ��ǰ������״̬��PS��Ŀ�״̬������״̬��ʵ���������ά��
    **************************************************************************/
    VOS_UINT8                           ucPdpId;                                /* ��ǰ״̬������Ӧ��PDP ID */
    VOS_UINT8                           aucReserve[3];
}TAF_APS_PDP_ENTITY_FSM_CTX_STRU;

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, end */

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* ��ϢID */
    VOS_UINT8                           aucReserve[2];

    VOS_UINT8                           aucBuf[TAF_APS_MAX_MSG_BUFFER_LEN];     /* ��Ϣ���� */
}TAF_APS_INTERNAL_MSG_BUF_STRU;


typedef struct
{
    /* TAF APS�ڲ���Ϣ���� */
    TAF_APS_INTERNAL_MSG_BUF_STRU       astApsMsgQueue[TAF_APS_MAX_MSG_QUEUE_SIZE];

    /* ������Ϣ��ʱ����buff,����ֲ�����ʱֱ��ʹ�øÿռ�,Ϊ�˱��ⷢ���ڲ���Ϣʱ
    ռ�ýϴ��ջ�ռ� */
    TAF_APS_INTERNAL_MSG_BUF_STRU       stSendMsgBuf;

    /*�ڲ���Ϣ������е�����βָ��*/
    VOS_UINT8                           ucTail;

    /*�ڲ���Ϣ������е�����ͷָ��*/
    VOS_UINT8                           ucHeader;

    VOS_UINT16                          usReserved;
} TAF_APS_INTERNAL_MSG_QUEUE_STRU;


typedef struct
{
    VOS_UINT8                           ucPdpActLimitFlg;                       /* ����NV��򿪹رձ�־ */
    VOS_UINT8                           ucPdpActFailCount;                      /* ��¼PDP����ʧ�ܴ��� */
    VOS_UINT8                           aucReserved[2];                         /* ���� ���ֽڶ��� */
}TAF_APS_PDP_ACT_LIMIT_INFO_STRU;

/*****************************************************************************
 �ṹ����  : TAF_APS_PDN_TEARDOWN_POLICY_STRU
 �ṹ˵��  : PDN���ӶϿ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucAllowDefPdnTeardownFlg;
    VOS_UINT8                               aucReserved[3];
} TAF_APS_PDN_TEARDOWN_POLICY_STRU;


typedef struct
{
    /**************************************************************************
                        �洢Lģ��Ĭ�ϳ���
    **************************************************************************/
    TAF_APS_CDATA_CTX_STRU                  stCdataCtx;                         /* ���CDMA����ҵ��ά����Dormant Timer�Լ�EPDSZID��Ϣ */

    /**************************************************************************
                        TAF APS״̬��״̬
    **************************************************************************/
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU         astPdpEntityFsmCtx[TAF_APS_MAX_PDPID];   /* ��ǰ���11��PDP�����ģ������11��������״̬�� */
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU        *pstCurrPdpEntityFsmCtx;                    /* ��ǰ��ʹ�õ�ʵ��״̬�� */

    TAF_APS_TIMER_CTX_STRU                  astApsTimerCtx[TAF_APS_MAX_TIMER_NUM];  /* APS��ǰ�������еĶ�ʱ����Դ */
    TAF_APS_DSFLOW_STATS_CTX_STRU           stApsDsFlowCtx;                         /* APS����ͳ�������� */

    /**************************************************************************
                        TAF APS������Ϣ����
    **************************************************************************/
    TAF_APS_MSG_QUEUE_STRU                  stBufferEntryMsgQueue;              /* APS�Ļ�����Ϣ���� */

    /**************************************************************************
                        TAF APS�����������
    **************************************************************************/
    TAF_APS_CMD_BUFFER_STRU                 astCmdBufferQueue[TAF_APS_MAX_CMD_BUFFER_QUEUE_SIZE]; /* �ȴ�L4A���ò�ѯ����Ķ��� */

    /**************************************************************************
                        APS �ڲ���Ϣ�������
    **************************************************************************/
    TAF_APS_INTERNAL_MSG_QUEUE_STRU         stInternalMsgQueue;                     /* MM�Ӳ���ڲ���Ϣ���� */

    TAF_APS_PDP_ACT_LIMIT_INFO_STRU         stPdpActLimitInfo;

    TAF_APS_SWITCH_DDR_RATE_INFO_STRU       stSwitchDdrRateInfo;                    /* DDRͶƱ��Ϣ */

    VOS_UINT32                              aulCallRemainTmrLen[TAF_MAX_CID + 1];   /* ��¼����ʣ��ʱ���������ϱ����� */

    TAF_APS_RAT_TYPE_ENUM_UINT32            enCurrSuspendRatType;                      /* ��¼��������й���ʱ�Ľ��뼼��ģʽ */

    TAF_APS_RAT_TYPE_ENUM_UINT32            enCurrRatType;                          /* ��¼��ǰ�Ľ��뼼��ģʽ */
    VOS_UINT32                              ulPsSimRegStatus;                       /* PS��SIM��״̬��Ϣ,VOS_TRUE:����Ч,VOS_FALSE:����Ч */
    TAF_APS_RAT_TYPE_ENUM_UINT32            enDataServiceMode;                      /* ��¼��ǰ���ݷ���ģʽ */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                              ulExist1XService;                       /* ��¼�Ƿ����1X�����ݷ��� */
    VOS_UINT32                              ulFinishClSearch;                       /* CLģʽ�¼�¼�Ƿ����DO��LTE������ */
#endif

#if (FEATURE_ON == FEATURE_LTE)
    TAF_APS_PDN_TEARDOWN_POLICY_STRU        stPdnTeardownPolicy;
#endif

}TAF_APS_CONTEXT_STRU;

extern TAF_APS_CONTEXT_STRU             g_stTafApsCtx;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

TAF_APS_PDP_ENTITY_FSM_CTX_STRU* TAF_APS_GetPdpEntityFsm(
    VOS_UINT32                          ulMainFsmState,
    TAF_APS_FSM_ID_ENUM_UINT32          enSubFsmId,
    VOS_UINT32                          ulSubFsmState
);

VOS_VOID  TAF_APS_InitDsFlowCtx(
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsTimerCtx
);

TAF_APS_DSFLOW_STATS_CTX_STRU*  TAF_APS_GetDsFlowCtxAddr( VOS_VOID );

TAF_APS_TIMER_CTX_STRU*  TAF_APS_GetTimerCtxAddr( VOS_VOID );




TAF_APS_MSG_QUEUE_STRU* TAF_APS_GetCachMsgBufferAddr(VOS_VOID);


VOS_UINT8  TAF_APS_GetCacheNum( VOS_VOID );

VOS_VOID  TAF_APS_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_UINT32  TAF_APS_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_VOID  TAF_APS_ClearCacheMsg(
    VOS_UINT32                          ulEventType
);

VOS_UINT32  TAF_APS_GetNextCachedMsg(
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg
);

VOS_VOID  TAF_APS_SetCurrPdpEntityMainFsmState(
    VOS_UINT32                          ulState
);


VOS_VOID  TAF_APS_SetCurrPdpEntitySubFsmState(
    VOS_UINT32                          ulState
);


VOS_VOID  TAF_APS_DelWaitInfoInL4aMsgRsltQueue(
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType
);

VOS_UINT32  TAF_APS_SetPdpIdMainFsmState(
    VOS_UINT8                          ucPdpId,
    VOS_UINT32                         ulState
);

VOS_UINT32  TAF_APS_GetPdpIdMainFsmState(
    VOS_UINT8                          ucPdpId
);

VOS_UINT32  TAF_APS_CheckPdpServiceActivated(
    VOS_UINT8                          ucPdpId
);

VOS_UINT32  TAF_APS_SetPdpIdSubFsmState(
    VOS_UINT8                          ucPdpId,
    VOS_UINT32                         ulState
);

VOS_UINT32  TAF_APS_GetPdpIdSubFsmState(
    VOS_UINT8                          ucPdpId
);

VOS_VOID  TAF_APS_SaveWaitInfoInWaitL4aMsgRsltQueue(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT16                          usClientId,
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType,
    VOS_UINT8                           ucOpId
);

TAF_APS_PDP_ENTITY_FSM_CTX_STRU* TAF_APS_GetCurrPdpEntityFsmAddr(VOS_VOID);


VOS_VOID  TAF_APS_InitCmdBufferQueue(
    TAF_APS_CMD_BUFFER_STRU            *pstCmdBufferQueue
);

TAF_APS_CMD_BUFFER_STRU  *TAF_APS_GetCmdBufferQueueAddr( VOS_VOID );

VOS_VOID  TAF_APS_DelItemInCmdBufferQueue(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
);

VOS_VOID  TAF_APS_SaveItemInCmdBufferQueue(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                         *pulMsgInfo,
    VOS_UINT32                          ulMsgInfoLen,
    VOS_UINT32                          ulPara
);

TAF_APS_CMD_BUFFER_STRU  *TAF_APS_GetItemFromCmdBufferQueue(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
);


VOS_VOID TAF_APS_SetCurrPdpEntityFsmAddr(
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_SaveCurrSubFsmEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID  TAF_APS_InitMainFsmCtx(
    TAF_APS_MAIN_FSM_CTX_STRU                *pstCurrFsmCtx
);

VOS_VOID  TAF_APS_InitSubFsmCtx(
    TAF_APS_SUB_FSM_CTX_STRU                *pstCurrFsmCtx
);

VOS_VOID  TAF_APS_InitInternalBuffer(
    TAF_APS_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
);

VOS_VOID TAF_APS_QuitCurrSubFsm( VOS_VOID );

VOS_VOID TAF_APS_InitSubFsm(
    TAF_APS_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
);
VOS_VOID  TAF_APS_SetCurrFsmEntityPdpId(
    VOS_UINT8                           ucPdpId
);

VOS_UINT8  TAF_APS_GetCurrFsmEntityPdpId(VOS_VOID);

VOS_VOID  TAF_APS_SetCurrPdpEntitySimRegStatus(
    VOS_UINT32                          ulPsSimRegStatus
);

VOS_UINT32  TAF_APS_GetCurrPdpEntitySimRegStatus( VOS_VOID );

VOS_VOID  TAF_APS_SetCurrPdpEntityRatType(
    TAF_APS_RAT_TYPE_ENUM_UINT32                enRatType
);

TAF_APS_RAT_TYPE_ENUM_UINT32  TAF_APS_GetCurrPdpEntityRatType( VOS_VOID );



/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, end */

VOS_VOID  TAF_APS_SetCurrPdpEntityDataServiceMode(
    TAF_APS_RAT_TYPE_ENUM_UINT32                enRatType
);

TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_GetCurrPdpEntityDataServiceMode(VOS_VOID);

TAF_APS_ENTRY_MSG_STRU* TAF_APS_GetCurrSubFsmMsgAddr(VOS_VOID);

TAF_APS_INTERNAL_MSG_BUF_STRU* TAF_APS_GetNextInternalMsg( VOS_VOID );
VOS_UINT32  TAF_APS_SndInternalMsg(
    VOS_VOID                           *pSndMsg
);
TAF_APS_INTERNAL_MSG_BUF_STRU *TAF_APS_GetIntMsgSendBuf(
    VOS_UINT32                          ulLen
);
VOS_VOID  TAF_APS_InitInternalMsgQueue(
    TAF_APS_INTERNAL_MSG_QUEUE_STRU     *pstInternalMsgQueue                   /* MM�Ӳ���ڲ���Ϣ���� */
);
TAF_APS_CONTEXT_STRU*  TAF_APS_GetApsCtxAddr( VOS_VOID );

VOS_VOID  TAF_APS_SaveCachePsCallAnswerMsg(
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType,
    VOS_UINT8                           ucPdpid
);



TAF_APS_PDP_ACT_LIMIT_INFO_STRU* TAF_APS_GetPdpActLimitInfoAddr(VOS_VOID);
VOS_VOID TAF_APS_InitPdpActLimitInfo(VOS_VOID);



VOS_VOID TAF_APS_InitSwitchDdrInfo(VOS_VOID);
TAF_APS_SWITCH_DDR_RATE_INFO_STRU*  TAF_APS_GetSwitchDdrRateInfoAddr(VOS_VOID);

VOS_VOID TAF_APS_InitCallRemainTmrLen(VOS_VOID);
VOS_VOID TAF_APS_SetCallRemainTmrLen(
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulTmrLen
);
VOS_UINT32 TAF_APS_GetCallRemainTmrLen(VOS_UINT8 ucCid);

VOS_VOID  TAF_APS_SetApsDmtTestStub(
    VOS_UINT32                          ulEnable
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_InitPdnTeardownPolicy(VOS_VOID);
TAF_APS_PDN_TEARDOWN_POLICY_STRU* TAF_APS_GetPdnTeardownPolicy(VOS_VOID);
VOS_UINT8 TAF_APS_GetAllowDefPdnTeardownFlg(VOS_VOID);
VOS_VOID TAF_APS_SetAllowDefPdnTeardownFlg(VOS_UINT8 ucAllowFlg);
#endif


TAF_PDP_AUTH_STRU*  TAF_APS_GetAuthParaByPdpId(
    VOS_UINT8                           ucPdpId
);
/* Deleted by y00314741 for CDMA Iteration 15, 2015-5-22, begin */

TAF_APS_CID_IMS_CFG_TBL_STRU* TAF_APS_GetCidImsCfgTable(VOS_VOID);

/* Deleted by y00314741 for CDMA Iteration 15, 2015-5-22, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_APS_IsEnterCdataEsting(VOS_VOID);
VOS_UINT32 TAF_APS_IsEnterCdataDiscing(VOS_VOID);

VOS_UINT32 TAF_APS_GetSocmDormantTiLen(VOS_VOID);

VOS_VOID TAF_APS_SetSocmDormantTiLen(
    VOS_UINT32                          ulDormantTiLen
);
VOS_VOID TAF_APS_InitCdataCtx( VOS_VOID );


VOS_VOID TAF_APS_Set1xPktDataInactivityTimerLen(
    VOS_UINT8                           ucTimeLen
);

VOS_UINT8 TAF_APS_Get1xPktDataInactivityTimerLen(VOS_VOID);

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-2, begin */
VOS_VOID TAF_APS_SetEvdoPktDataInactivityTimerLen(
    VOS_UINT8                           ucTimeLen
);

VOS_UINT8 TAF_APS_GetEvdoPktDataInactivityTimerLen(VOS_VOID);
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-2, end */

#endif


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_APS_SetFsmCtxCdataDialMode(
    TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32  enDialMode
);

TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32 TAF_APS_GetFsmCtxCdataDialMode( VOS_VOID );




VOS_VOID  TAF_APS_Set1XPsServiceStatus(
    VOS_UINT32                          ulExist
);

VOS_UINT32  TAF_APS_Get1XPsServiceStatus(VOS_VOID);

VOS_VOID TAF_APS_FillEhsmSdfParaApnInfo(
    APS_EHSM_SDF_PARA_INFO_STRU         *pstSdfParaInfo,
    TAF_PDP_TABLE_STRU                  *pstTafCidInfo
);

VOS_VOID TAF_APS_FillEhsmSdfParaAuthInfo(
    APS_EHSM_SDF_PARA_INFO_STRU        *pstSdfParaInfo,
    VOS_UINT8                           ucCid
);

VOS_UINT32  TAF_APS_GetFinishClSearch(VOS_VOID);

VOS_VOID  TAF_APS_SetFinishClSearch(
    VOS_UINT32                          ulFinished
);
VOS_VOID TAF_APS_SetFsmCtxCdataLastDialOnRatType(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enLastOirgOnRatType
);

TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_GetFsmCtxCdataLastDialOnRatType(VOS_VOID);


VOS_UINT32 TAF_APS_GetUserCfgDormTiVal(VOS_VOID);

VOS_VOID TAF_APS_SetUserCfgDormTiVal(
    VOS_UINT32                          ulUserCfgDormTival
);

VOS_VOID TAF_APS_SetFsmCtxCdataSoInitType(
    TAF_APS_CDATA_SO_TYPE_ENUM_UINT16   enSoInitType
);

TAF_APS_CDATA_SO_TYPE_ENUM_UINT16 TAF_APS_GetFsmCtxCdataSoInitType (VOS_VOID);


#endif

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

#endif /* end of TafApsCtx.h */
