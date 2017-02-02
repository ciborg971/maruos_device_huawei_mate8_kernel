

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafMmaMsgPrioCompare.h"
#include  "TafFsm.h"
#include  "Taf_Tafm_Remote.h"
#include  "TafOamInterface.h"
#include  "TafLog.h"
#include  "TafMmaSndInternalMsg.h"
#include  "TafMmaSndApp.h"

#include  "MmaMsccInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_MSG_PRIO_COMPARE_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

TAF_MMA_MSG_COMPARE_STRU g_astMmaMsgPrioCompareWithPhoneModeTbl[] =
{
    /* phone mode�������յ�OM��ģʽ�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode),

    /* ģʽ��ѯ����Ҫ�Ƚ� */



    /* phone mode�������յ�ģʽ�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode),

    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode),

    /* phone mode�������յ�MMA���ڲ���״ָ̬ʾ����Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND),
                             TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithPhoneMode),


    /* phone mode�������յ�TAF��SYSCFG�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ),
                             TAF_MMA_CompareAtSyscfgReqPrioWithPhoneMode),

    /* phone mode�������յ�AT��list�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ),
                             TAF_MMA_CompareAtPlmnListReqPrioWithPhoneMode),
    /* phone mode�������յ�AT���û�ָ�������������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ),
                             TAF_MMA_CompareAtPlmnUserSelReqPrioWithPhoneMode),

    /* phone mode�������յ�AT��attach�������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ),
                             TAF_MMA_CompareAtAttachPrioWithPhoneMode),


    /* phone mode�������յ�AT��detach�������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ),
                             TAF_MMA_CompareAtDetachPrioWithPhoneMode),

    /* phone mode�������յ�AT���Զ���ѡ�������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ),
                             TAF_MMA_CompareAtPlmnReselPrioWithPhoneMode),
#if (FEATURE_ON == FEATURE_IMS)
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ),
                             TAF_MMA_CompareImsSwitchSetReqPrioWithPhoneMode),
#endif

};

#if (FEATURE_ON == FEATURE_IMS)

TAF_MMA_MSG_COMPARE_STRU g_astMmaMsgPrioCompareWithImsSwitchTbl[] =
{
    /* IMS SWITCH�������յ�OM��ģʽ�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithImsSwitch),

    /* IMS SWITCH�������յ�ģʽ�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithImsSwitch),

    /* IMS SWITCH�������յ�MMA���ڲ���״ָ̬ʾ����Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND),
                             TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithImsSwitch),

    /* IMS SWITCH�������յ�TAF��SYSCFG�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ),
                             TAF_MMA_CompareAtSyscfgReqPrioWithImsSwitch),

    /* IMS SWITCH�������յ�AT���û�ָ�������������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ),
                             TAF_MMA_CompareAtPlmnUserSelReqPrioWithImsSwitch),

    /* IMS SWITCH�������յ�AT��attach�������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ),
                             TAF_MMA_CompareAtAttachPrioWithImsSwitch),

    /* IMS SWITCH�������յ�AT��detach�������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ),
                             TAF_MMA_CompareAtDetachPrioWithImsSwitch),

    /* IMS SWITCH�������յ�AT���Զ���ѡ�������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ),
                             TAF_MMA_CompareAtPlmnReselPrioWithImsSwitch),

    /* IMS SWITCH�������յ�TAF��IMS���ػ��������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ),
                             TAF_MMA_CompareImsSwitchSetReqPrioWithImsSwitch),


    /* IMS SWITCH�������յ�MSCC��PLMN RESEL�ظ�����Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMA_PLMN_RESEL_CNF),
                             TAF_MMA_CompareMsccPlmnReselCnfPrioWithImsSwitch),

};
#endif


TAF_MMA_MSG_COMPARE_STRU g_astMmaMsgPrioCompareWithSysCfgTbl[] =
{
    /* ��SYS CFG�����У��յ�OAMģʽ�������� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg),

    /* ��SYS CFG�����У��յ�APP��ģʽ�������� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg),

    /* ��SYS CFG�����У��յ�CBT��ģʽ�������� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ),
                             TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg),

    /* ��SYS CFG������, �յ�MMA���ڲ���״ָ̬ʾ����Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND),
                             TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithSysCfg),

    /* Deleted by h00313353 for Iteration 13, 2015-4-27, begin */

    /* Deleted by h00313353 for Iteration 13, 2015-4-27, end */

    /* ��SYS CFG������, �յ�APP��SYSCFG�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ),
                             TAF_MMA_CompareSyscfgSetReqPrioWithSysCfg),

    /* ��SYS CFG�����У��յ�MMA�ڲ����͵�ϵͳ�������� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ),
                             TAF_MMA_CompareSyscfgSetReqPrioWithSysCfg),

    /* ��SYS CFG������, �յ�APP��ATTACH�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ),
                             TAF_MMA_CompareAttachReqPrioWithSysCfg),

    /* ��SYS CFG������, �յ�APP��DETACH�����������Ϣ���ȼ��Ƚ�, ����L-C������ */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ),
                             TAF_MMA_CompareDetachReqPrioWithSysCfg),

    /* ��SYS CFG������, �յ�APP��PLMN RESEL�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ),
                             TAF_MMA_ComparePlmnReselReqPrioWithSysCfg),

    /* ��SYS CFG������, �յ�APP��PLMN LIST�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ),
                             TAF_MMA_ComparePlmnListReqPrioWithSysCfg),

    /* ��SYS CFG������, �յ�APP��PLMN USER SEL�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ),
                             TAF_MMA_ComparePlmnUserSelReqPrioWithSysCfg),

    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_ABORT_REQ),
                             TAF_MMA_ComparePlmnAbortReqPrioWithSysCfg),

    #if (FEATURE_ON == FEATURE_IMS)
    /* ��SYS CFG������, �յ�APP��ims switch�����������Ϣ���ȼ��Ƚ� */
    TAF_MMA_COMPARE_TBL_ITEM(TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ),
                             TAF_MMA_CompareImsSwitchSetReqPrioWithSysCfg),
    #endif
};


TAF_MMA_FSM_MSG_COMPARE_STRU g_astMmaMsgCompareTbl[] =
{
     /* phone mode ״̬���ȽϺ�����*/
    TAF_MMA_FSM_COMPARE_TBL_ITEM(TAF_MMA_FSM_PHONE_MODE,
                                 g_astMmaMsgPrioCompareWithPhoneModeTbl),

#if (FEATURE_ON == FEATURE_IMS)
    /* IMS SWITCH״̬���ȽϺ�����*/
    TAF_MMA_FSM_COMPARE_TBL_ITEM(TAF_MMA_FSM_IMS_SWITCH,
                                 g_astMmaMsgPrioCompareWithImsSwitchTbl),
#endif
     TAF_MMA_FSM_COMPARE_TBL_ITEM(TAF_MMA_FSM_SYS_CFG,
                                  g_astMmaMsgPrioCompareWithSysCfgTbl),
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_UINT32 TAF_MMA_ComparePhoneModeSetReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}



VOS_UINT32 TAF_MMA_CompareAtSyscfgReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}



VOS_UINT32 TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtPlmnListReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtPlmnUserSelReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtAttachPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}



VOS_UINT32 TAF_MMA_CompareAtDetachPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtPlmnReselPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_UINT32 TAF_MMA_CompareImsSwitchSetReqPrioWithPhoneMode(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_ComparePhoneModeSetReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtSyscfgReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtPlmnListReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtPlmnUserSelReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtAttachPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtDetachPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareAtPlmnReselPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 TAF_MMA_CompareImsSwitchSetReqPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}



VOS_UINT32 TAF_MMA_CompareMsccPlmnReselCnfPrioWithImsSwitch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}

#endif

TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32               enPrioRslt;

    /* ��ȡSYS CFG��ǰ״̬�������Ϣ */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    switch (pstEntryMsg->ulEventType)
    {
        /* �����ǰSYS CFG״̬������Ϊattach/detach�������յ�phone mode���ã��ɴ�ϵ�ǰ���� */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ):
            *penAbortType = TAF_MMA_ABORT_FSM_IMMEDIATELY;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT;
            break;

        /* �����ǰSYS CFG״̬������Ϊsystem cofigure setting�������յ�phone mode���ã�����phone mode */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ):
        case TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ):
            *penAbortType = TAF_MMA_ABORT_BUTT;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
            break;

        default:
            /* �����ϲ�Ӧ�÷�������ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ComparePhoneModeSetReqPrioWithSysCfg: abnormal message!");

            *penAbortType = TAF_MMA_ABORT_FSM_IMMEDIATELY;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT;
            break;
    }

    return enPrioRslt;
}


VOS_UINT32 TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32               enPrioRslt;

    /* ��ȡSYS CFG��ǰ״̬�������Ϣ */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    switch (pstEntryMsg->ulEventType)
    {
        /* �����ǰSYS CFG״̬������Ϊattach/detach�������յ�usim״̬�ı䣬�ɴ�ϵ�ǰ���� */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ):
            *penAbortType = TAF_MMA_ABORT_FSM_IMMEDIATELY;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT;
            break;

        /* �����ǰSYS CFG״̬������Ϊsystem cofigure setting�������յ�usim״̬�ı䣬����usim��״̬�仯ָʾ */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ):
        case TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ):
            *penAbortType = TAF_MMA_ABORT_BUTT;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
            break;

        default:
            /* �����ϲ�Ӧ�÷�������ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_CompareMmaInterUsimStatusChangeIndPrioWithSysCfg: abnormal message!");

            *penAbortType = TAF_MMA_ABORT_FSM_IMMEDIATELY;
            enPrioRslt    = TAF_MMA_MSG_COMPARE_PRIO_RSLT_ABORT;
            break;
    }

    return enPrioRslt;
}

/* Deleted by h00313353 for Iteration 13, 2015-4-27, begin */

/* Deleted by h00313353 for Iteration 13, 2015-4-27, end */


VOS_UINT32 TAF_MMA_CompareSyscfgSetReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ��ǰSYS CFG�����У��ܾ���ǰϵͳ�������� */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}
VOS_UINT32 TAF_MMA_CompareAttachReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ���浱ǰ���� */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;

}
VOS_UINT32 TAF_MMA_CompareDetachReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ���浱ǰ���� */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
}
VOS_UINT32 TAF_MMA_ComparePlmnReselReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ��ȡSYS CFG��ǰ״̬�������Ϣ */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ) == pstEntryMsg->ulEventType)
    {
        /* �����ǰSYS CFG״̬�����ڲ�ϵͳ�������󴥷��ģ����浱ǰ���� */
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* �����ܾ���ǰ������ */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}
VOS_UINT32 TAF_MMA_ComparePlmnListReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ��ȡSYS CFG��ǰ״̬�������Ϣ */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ) == pstEntryMsg->ulEventType)
    {
        /* �����ǰSYS CFG״̬�����ڲ�ϵͳ�������󴥷��ģ����浱ǰ���� */
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* �����ܾ���ǰ������ */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}
VOS_UINT32 TAF_MMA_ComparePlmnUserSelReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ��ȡSYS CFG��ǰ״̬�������Ϣ */
    pstEntryMsg  = TAF_MMA_GetCurrFsmMsgAddr();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_SYS_CFG_SET_REQ) == pstEntryMsg->ulEventType)
    {
        /* �����ǰSYS CFG״̬�����ڲ�ϵͳ�������󴥷��ģ����浱ǰ���� */
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* �����ܾ���ǰ������ */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_REJECT;
}
VOS_UINT32 TAF_MMA_ComparePlmnAbortReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstEntryMsgAddr = VOS_NULL_PTR;
    VOS_UINT16                          i;
    VOS_UINT32                          ulPlmnListEvent;
    TAF_MMA_PLMN_LIST_ABORT_REQ_STRU   *pstPlmnListAbortMsg = VOS_NULL_PTR;

    pstPlmnListAbortMsg = (TAF_MMA_PLMN_LIST_ABORT_REQ_STRU *)pstMsg;

    ulPlmnListEvent = TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ);

    pstEntryMsgAddr = TAF_MMA_GetCachMsgBufferAddr();

    for (i = 0; i < pstEntryMsgAddr->ucCacheMsgNum; i++)
    {
        if (ulPlmnListEvent == pstEntryMsgAddr->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            pstEntryMsgAddr->ucCacheMsgNum--;

            /* ���PLMN LIST REQ�¼�, move�����к���Ļ�����Ϣ */
            PS_MEM_MOVE(&(pstEntryMsgAddr->astMsgQueue[i].stMsgEntry),
                        &(pstEntryMsgAddr->astMsgQueue[i+1].stMsgEntry),
                        sizeof(TAF_MMA_ENTRY_MSG_STRU) * (pstEntryMsgAddr->ucCacheMsgNum - i));

            /* ��Ϣ���������һ����Ϣ�����0 */
            PS_MEM_SET(&(pstEntryMsgAddr->astMsgQueue[pstEntryMsgAddr->ucCacheMsgNum].stMsgEntry),
                       0,
                       sizeof(TAF_MMA_ENTRY_MSG_STRU));

            break;
        }
    }

    /* �ϱ�AT��ǰ״̬�¼� */
    TAF_MMA_SndPlmnListAbortCnf(&(pstPlmnListAbortMsg->stCtrl), TAF_ERR_NO_ERROR);

    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* �Ѵ�����ϣ����Ը���Ϣ */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


VOS_VOID TAF_MMA_ProcessComparePrioRsltAbort(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ENTRY_MSG_STRU              stEntryMsg;

    PS_MEM_SET(&stEntryMsg, 0, sizeof(TAF_MMA_ENTRY_MSG_STRU));

    /* ����л��棬����������е���Ϣ */
    while (VOS_TRUE ==TAF_MMA_GetNextCachedMsg(&stEntryMsg))
    {
        TAF_MMA_RejectAppRequest(stEntryMsg.ulEventType, (struct MsgCB *)stEntryMsg.aucEntryMsgBuffer);
    }

    /* ���浱ǰ���û����� */
    (VOS_VOID)TAF_MMA_SaveCacheMsgInMsgQueue(ulEventType, (VOS_VOID *) pstMsg);
}


VOS_VOID TAF_MMA_ProcessComparePrioRsltReject(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_RejectAppRequest(ulEventType, pstMsg);
}


VOS_VOID TAF_MMA_RejectAppRequest(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstRcvMsg          = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara = VOS_NULL_PTR;

    pstRcvMsg = (MSG_HEADER_STRU *)pstMsg;

    switch (ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ):
            /* ����attach confirm�ظ��ӿں��� */
            TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                 TAF_MMA_APP_OPER_RESULT_FAILURE,
                                 TAF_ERR_PHONE_MSG_UNMATCH);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ):
            /* ����detach confirm�ظ��ӿں��� */
            TAF_MMA_SndDetachCnf(&(((TAF_MMA_DETACH_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                 TAF_MMA_APP_OPER_RESULT_FAILURE,
                                 TAF_ERR_PHONE_MSG_UNMATCH);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ):
            /* ����SYS CFG SET�ظ��ӿں��� */
            TAF_MMA_SndSysCfgSetCnf(&(((TAF_MMA_SYS_CFG_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                    TAF_ERR_ERROR);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ):
            TAF_MMA_SndPlmnAutoReselCnf(&(((TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                        TAF_ERR_PHONE_MSG_UNMATCH);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ):
            {
                pstPlmnListCnfPara = (TAF_MMA_PLMN_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                                                                     sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));
                if (VOS_NULL_PTR != pstPlmnListCnfPara)
                {
                    PS_MEM_SET(pstPlmnListCnfPara, 0x0, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

                    pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
                    pstPlmnListCnfPara->enPhoneError = TAF_ERR_PHONE_MSG_UNMATCH;

                    TAF_MMA_SndPlmnListCnf(&(((TAF_MMA_PLMN_LIST_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                           pstPlmnListCnfPara);

                    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);
                }
            }
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ):
            TAF_MMA_SndPlmnSpecialSelCnf(&(((TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                         TAF_ERR_PHONE_MSG_UNMATCH);
            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ):
             TAF_MMA_SndPhoneModeSetCnf(&(((TAF_MMA_PHONE_MODE_SET_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                        ((TAF_MMA_PHONE_MODE_SET_REQ_STRU *)(pstRcvMsg))->stPhoneModePara.PhMode,
                                        TAF_MMA_APP_OPER_RESULT_FAILURE,
                                        TAF_ERR_PHONE_MSG_UNMATCH);
            break;

#if (FEATURE_IMS == FEATURE_ON)
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ):
             /* ���ϲ�ظ�ʧ�� */
            TAF_MMA_SndImsSwitchSetCnf(&(((TAF_MMA_IMS_SWITCH_SET_REQ_STRU *)(pstRcvMsg))->stCtrl),
                                         TAF_MMA_APP_OPER_RESULT_FAILURE,
                                         TAF_ERR_UNSPECIFIED_ERROR);
             break;
#endif

        default:
            /* unknown message, ignore it */
            break;
    }
}

TAF_MMA_MSG_COMPARE_FUNC  TAF_MMA_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId
)
{
    TAF_MMA_FSM_MSG_COMPARE_STRU       *pstFsmCompareTbl = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astMmaMsgCompareTbl)/sizeof(TAF_MMA_FSM_MSG_COMPARE_STRU);

    for ( i = 0 ; i < ulTblSize ; i++ )
    {
        if ( enFsmId == g_astMmaMsgCompareTbl[i].enFsmId)
        {
            pstFsmCompareTbl = &g_astMmaMsgCompareTbl[i];
            break;
        }
    }

    /* δ���ҵ���״̬���ıȽϺ�����,ֱ�ӷ��ؿ�ָ�� */
    if ( VOS_NULL_PTR == pstFsmCompareTbl )
    {
        return VOS_NULL_PTR;
    }

    for ( i = 0 ; i < pstFsmCompareTbl->ulSize; i++ )
    {
        /* ���Ҳ�ͬ�¼��ıȽϺ��� */
        if ( pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType == ulEventType)
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
    }

    /* δ�ҵ�������ֱ�ӷ��ؿ�ָ�� */
    return VOS_NULL_PTR;
}
TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 TAF_MMA_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    TAF_MMA_MSG_COMPARE_FUNC                    pfCompareFunc;
    TAF_MMA_FSM_ID_ENUM_UINT32                  enCurrFsmId;
    TAF_MMA_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32   enRslt;

    /*  ��ȡ��ǰ״̬����ID */
    enCurrFsmId         = TAF_MMA_GetCurrFsmId();

    if (TAF_MMA_FSM_BUTT <= enCurrFsmId)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "ERROR:FsmId Error");
    }

    /*  ��ȡ�ȽϺ��� TAF_MMA_FindMsgPrioCompareFun() */
    pfCompareFunc       = TAF_MMA_FindMsgPrioCompareFun(ulEventType, pstMsg, enCurrFsmId);

    /* δ�ҵ�������,��Ĭ����Ϣ���� */
    if ( VOS_NULL_PTR == pfCompareFunc )
    {
        *penAbortType = TAF_MMA_ABORT_BUTT;
        return TAF_MMA_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* ���ñȽϺ���,�������ȼ��ʹ������ */
    enRslt = pfCompareFunc(ulEventType, pstMsg, penAbortType);

    return enRslt;

}


VOS_UINT32 TAF_MMA_CompareImsSwitchSetReqPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_MMA_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = TAF_MMA_ABORT_BUTT;

    /* ���浱ǰ���� */
    return TAF_MMA_MSG_COMPARE_PRIO_RSLT_STORE;

}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

