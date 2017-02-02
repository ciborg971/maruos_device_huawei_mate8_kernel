

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/

/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

#ifndef __DRX_OM_DEF_H__
#define __DRX_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



typedef enum
{
     LPHY_DEBUG_DRX        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_DEBUG, 0x1),

}LPHY_DEBUG_DRX_ENUM;

typedef enum
{
     LPHY_ERR_DRX        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_ERROR, 0x1),

}LPHY_ERR_DRX_ENUM;



typedef struct
{
    UINT32 ulAllResetCnt;
    UINT32 ulInitPowUpCnt;
    UINT32 ulLpcResetCnt;
    UINT32 ulTaskLoopCnt[16];
    UINT32 ulWakeResumeFunc;
    //UINT32 ulWakeTimer;
    //UINT32 ulSlwwpTimer;
    //UINT32 ulMeasResult;

    UINT32 ulTaskInfo;
    UINT32 ulDrxCurStatus;
    UINT32 epc[4];
    UINT32 eps[4];
	UINT32 ulExcLoc;
	UINT16 usExcID;
    UINT16 usSysFrame;
    UINT16 usSubFrame;
    UINT16 usMeasCalcCnt;
    UINT16 usWakeCnt;
    UINT16 usSleepCnt;
    UINT16 usCdrxSleepCnt;
    UINT16 usCdrxWakeCnt;
    //UINT16 usWakeValid;
    UINT16 usSlaveWakeUpCnt;
    UINT16 usSlaveSleepCnt;
    UINT16 usCdrxOnlyRfSleepCnt;
    UINT16 usCdrxOnlyRfWakeCnt;
    UINT16 usRsvd[6];
}DRX_DEBUG_STRU;

/* BEGIN: Added by xueqiuyan, 2012/9/18   PN:CMCC_DT*/
typedef enum
{
    LPHY_DT_DRX_STATUS_INFO_REQ        =  OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_REQ, 0x1),
    LPHY_DT_DRX_STATUS_INFO_REQ_DT        =  OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_DT, 0x1),
    LPHY_REQ_DRX_PRINT_INFO            =  OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_REQ, 0x2)

}LPHY_DT_DRX_REQ_ENUM;

typedef enum
{
     LPHY_DT_DRX_STATUS_INFO_IND        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_SG, 0x1),
     LPHY_DT_DRX_STATUS_INFO_IND_DT        = OM_CMD_ID(LPHY_DRX_MID, OM_TYPE_DT, 0x1001)

}LPHY_DT_DRX_IND_ENUM;


typedef enum
{
    DRX_TIMER_INACTIVE = 0,
    DRX_TIMER_ACTIVE
}DRX_TIMER_STATUS_ENUM;

typedef UINT16 DRX_TIMER_STATUS_ENUM_UINT16;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16          usRsv;
} LPHY_DT_DRX_STATUS_INFO_REQ_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enHighPrintEn;
    OM_REQ_ENABLE_ENUM_UINT16   enLowPrintEn;
    OM_REQ_ENABLE_ENUM_UINT16   enMidPrintEn;
    UINT16                      usRsv;
} LPHY_REQ_DRX_PRINT_INFO_REQ_STRU;


typedef struct
{
    DRX_TIMER_STATUS_ENUM_UINT16  aenDlRttTimer[15];
    DRX_TIMER_STATUS_ENUM_UINT16  aenDlRetranTimer[15];
} DRX_DL_HARQ_TIMER_INFO_STRU;

typedef struct __LPHY_DT_DRX_STATUS_INFO_IND_STRU__
{
    UINT16  usSFN;
    UINT16  usSubFn;
    UINT16  usDrxCycleType;
    UINT16  usActiveState;
    DRX_TIMER_STATUS_ENUM_UINT16  enOndurationTimerState;
    DRX_TIMER_STATUS_ENUM_UINT16  enInactivityTimer;
    DRX_TIMER_STATUS_ENUM_UINT16  enShortTimer;
    UINT16                        usRsv;
    DRX_DL_HARQ_TIMER_INFO_STRU   astDlHarqTimer[2];

} LPHY_DT_DRX_STATUS_INFO_IND_STRU;

typedef struct __LPHY_DT_DRX_STATUS_INFO_IND_STRU_DT__
{
    UINT16  usSFN;
    UINT16  usSubFn;

    UINT16  usDrxCycleType;
    DRX_TIMER_STATUS_ENUM_UINT16  enOndurationTimerState;

    DRX_TIMER_STATUS_ENUM_UINT16  enInactivityTimer;
    UINT16                        usRsv;


} LPHY_DT_DRX_STATUS_INFO_IND_STRU_DT;




/* END:   Added by xueqiuyan, 2012/9/18 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DRX_OM_DEF_H__ */

