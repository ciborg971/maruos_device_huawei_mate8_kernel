

#ifndef __LPSFSMSTATE_H__
#define __LPSFSMSTATE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"


#pragma pack(4)

/*****************************************************************************
  2 Macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : RRC_MS_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ״̬����״̬ö�ٶ���
*****************************************************************************/
enum ERRC_MS_ID_ENUM
{
    /* ERRC PID״̬����״̬ */
    RRC_ERRC_MS_IDLE = 0,

    /* RRCģ�����״̬ */
    RRC_RRC_MS_CONN_REQ,                                   /* �������ӽ����������״̬ */
    RRC_RRC_MS_CONN_SETUP,                                   /* �ȴ����ӽ�������ܾ�����״̬ */
    RRC_RRC_MS_UE_CAPA_ENQUIRY,                                   /* ���緢��UE������ѯ����״̬ */
    RRC_RRC_MS_CONN_REL,                                   /* �����ͷŹ��̵���״̬:nas����ģ�enodeb����ģ�release all�� */
    RRC_RRC_MS_POWER_OFF,                                   /* �ػ��������״̬ */
    RRC_RRC_MS_POWER_ON,                                   /* �����������״̬ */
    LRRC_LRRC_MS_SUSPEND_REQ,                            /* �յ�LNAS�����������״̬ */
    RRC_RRC_MS_PUCCH_SRS_REL_IND,                          /* CONNECTED̬��MAC�ϱ�PUCCH/SRS�ͷŵ���״̬ */
    LRRC_LRRC_MS_RL_FAIL,                                  /* ������·ʧ�ܵ���״̬ */
    RRC_RRC_MS_UE_INFO_REQ,                            /* UE INFORMATION REQ��״̬ */
    LRRC_LRRC_MS_GU2L_IRAT_MOBILITY,                    /* GU->L��ѡ/GU->L�ض���/G->L CCO��״̬ */
    LRRC_LRRC_MS_L2GU_IRAT_MOBILITY,                    /* L->GU��ѡ/L->GU�ض���/L->G CCO��״̬ */


    /* END of RRCģ�����״̬ */

    /* RBģ�����״̬ */
    LRRC_LRB_MS_GU2L_HO,                            /* GU->L�л�����״̬ */
    RRC_RB_MS_HO,                                   /* ��������Ϣ�д����ƶ��Թ���������Ϣʱ����״̬ */
    RRC_RB_MS_RBCFG,                                   /* ��������Ϣ�н�������������Դ������Ϣʱ����״̬ */
    RRC_RB_MS_RECFG,                                   /* ��������Ϣ�в������ƶ��Թ����������Դ������Ϣ����״̬ */
    /* END of RBģ�����״̬ */

    /* REESTģ�����״̬ */
    RRC_REEST_MS_CONN_REEST_REQ,                                   /* ����RRC CONNECTION REESTABLISHMENT REQUEST��״̬ */
    RRC_REEST_MS_CONN_REEST,                                   /* ����RRC CONNECTION REESTABLISHMENT��״̬ */

    /* END of REESTģ�����״̬ */

    /* CSELPCģ�����״̬ */
    RRC_CSELPC_MS_SPEC_PLMN_SEARCH,                                   /* ָ��PLMN��������״̬ */
    RRC_CSELPC_MS_ANY_CELL_SEARCH,                                   /* ANY CELL��������״̬ */
    RRC_CSELPC_MS_SUIT_CELL_SEARCH,                                   /* SUITABLE CELL��������״̬ */
    RRC_CSELPC_MS_PLMN_LIST_SEARCH,                                   /* PLMN LIST��������״̬ */
    RRC_CSELPC_MS_RRC_CELL_RESEL_STOP,                                   /* ����С����ѡֹͣ�������״̬ */
    RRC_CSELPC_MS_RRC_CELL_RESEL_START,                                   /* ����С����ѡ�����������״̬ */
    RRC_CSELPC_MS_REEST_CELL_RESEL_STOP,                                   /* ����С����ѡֹͣ�������״̬ */
    RRC_CSELPC_MS_REEST_CELL_RESEL_START,                                   /* ����С����ѡ�����������״̬ */
    RRC_CSELPC_MS_RRC_STATE_CHANGE,                                   /* RRC���͵�״̬��Ǩ�������״̬ */
    RRC_CSELPC_MS_REEST_STATE_CHANGE,                                   /* REEST���͵�״̬��Ǩ�������״̬ */
    RRC_CSELPC_MS_SYS_INFO_UPDATE_IDLE,                                   /* ����ϵͳ��Ϣ���µ���״̬ */
    RRC_CSELPC_MS_SYS_INFO_UPDATE_CONNECT,
    RRC_CSELPC_MS_HANDOVER_SYS_INFO_UPDATE,                                   /* �л���ɺ�֪ͨcselpc����ϵͳ��Ϣ���� */
    RRC_CSELPC_MS_CELL_RESEL_IND,                                   /* CSEL���͹�����ѡָʾ */
    RRC_CSELPC_MS_COVERAGE_AREA_LOST,                                   /* CSEL���͹�����ѡָʾ */
    RRC_CSELPC_MS_STOP_SYS_UPDATE_CONNECT,                                   /* CSELPCֹͣϵͳ��Ϣ���µ���״̬ */
    /* MBMS Begin */
    RRC_CSELPC_MS_MBMS_COMM_FLOW,                               /* MBMS�Ĺ������� */
     RRC_CSELPC_MS_MODE_NTF,                                 /*�յ�LMM���͵�NTF��Ϣ����״̬ */
    /* MBMS end */
    /* bgs begin */
    LRRC_LCSELPC_MS_BGS_CTRL,                                                   /* CSELPC�����ѿ��Ƶ���״̬ */
    /* bgs end */

    RRC_CSELPC_MS_MBMS_CONN_TO_IDLE,                              /* ����MBMSҵ�񣬿տ���������REL���̣�UEΪ�˱�֤MBMS�����ԣ�����ֱ��פ�� */
    /* END of CSELPCģ�����״̬ */

    /* SMC ģ�����״̬ */
    RRC_SMC_MS_ACTIVE,                                                          /* �յ�eNB�İ�ȫģʽ�������� */
    RRC_SMC_MS_CONN,                                                            /* �յ�RB����REEST������Ҫ����������L2 */
    RRC_SMC_MS_CNT_CHK,
    /* END of SMC ģ�����״̬ */

    /* ITFģ�����״̬ */
    RRC_ITF_MS_WAIT_CNF,

    /* END OF ITFģ�����״̬ */

    /* bgs begin */
    /* CSELBGģ�����״̬ */
    LRRC_LCSELBG_MS_IDLE,
    LRRC_LCSELBG_MS_RUN_BGS,
    LRRC_LCSELBG_MS_SUSPEND_BGS,
    LRRC_LCSELBG_MS_RESUME_BGS,
    LRRC_LCSELBG_MS_STOP_BGS,
    /* END of CSELBGģ�����״̬ */
    /* bgs end */

    /* CSELģ�����״̬ */
    RRC_CSEL_MS_IDLE,
    RRC_CSEL_MS_CELL_SEARCH,    /* С��������״̬ */
    RRC_CSEL_MS_PLMN_LIST_SEARCH,    /* PLMN List������״̬ */
    RRC_CSEL_MS_PLMN_LIST_SEARCH_STOP,    /* ֹͣPLMN List������״̬ */
    RRC_CSEL_MS_RUN_RESEL                   ,    /* ���ڽ���С����ѡ */
    RRC_CSEL_MS_STOP_RESEL                  ,    /* ����ֹͣС����ѡ */
    RRC_CSEL_MS_DONE_RESEL                  ,    /* С����ѡ�Ѿ�ӵ�н��,���ڽ��� */

    LRRC_LCSEL_MS_IRAT_MEAS_IN_IDLE,      /* L��ģʱ���ò���״̬ */
    /* END of CSELģ�����״̬ */

    /* CMMģ�����״̬ */
    RRC_CMM_MS_IDLE,
    RRC_CMM_MS_MEAS_CTRL,
    LRRC_LCMM_MS_IRAT_MEAS_IN_CONN,
    LRRC_LCMM_MS_BSIC_VERIFY,         /* ����̬BSIC��֤��״̬ */
     LRRC_LCMM_MS_MODE_NTF,                                 /*�յ�LMM���͵�NTF��Ϣ����״̬ */
    /* END of CMMģ�����״̬ */

    /* SIBģ�����״̬ */
    RRC_SIB_MS_IDLE,
    RRC_SIB_MS_GET_SEARCH_INFO,   /* PLMN�����µ���״̬ */
    RRC_SIB_MS_GET_NEW_SI,   /* ��ȡ�µ�ϵͳ��Ϣ����״̬ */
    RRC_SIB_MS_UPDATE_SI,   /* ����ϵͳ��Ϣ����״̬ */
    RRC_SIB_MS_CSEL_STOP,   /* CSELֹ֪ͨͣ����״̬ */
    RRC_SIB_MS_CSELPC_STOP,   /* CSELPCֹ֪ͨͣ����״̬ */
    /* END of SIBģ�����״̬ */

    /* begin: add mbms for feature v700r500 */
    RRC_RRC_MS_MBMS_CONN_TO_IDLE,                              /* ����MBMSҵ�񣬿տ���������REL���̣�UEΪ�˱�֤MBMS�����ԣ�����ֱ��פ�� */
    RRC_CSELPC_MS_MBMS_ENABLE_WITH_MCCH_FLOW,                     /*��IDLE̬������̬��û�и���ϵͳ��Ϣ��MBMS���SI��Чʱ��ʹ�ø�����*/
    RRC_CSELPC_MS_MBMS_DISABLE_FLOW,                              /* ȥʹ��MBMS����״̬�� */
    RRC_CSELPC_MS_MBMS_SERVICE_STATE_SET_FLOW,                    /*����״̬�������̣������ȥ��������ʹ��*/
    RRC_CSELPC_MS_MBMS_NOTIFY_IND_FLOW,                           /* �����յ�LPHY��NOTIFY IND�������� */
    /* end: add mbms for feature v700r500 */

    LRRC_LCMM_MS_LPP_OTDOA_MEAS_FLOW,
    LRRC_LRRC_MS_LPP_OTDOA_MEAS_FLOW,

    /* ״̬��Ԥ��״̬����Ҫ���ڲ���״̬������Ϣ�Ĵ��� */
    RRC_MS_PRE_PROCESS,

    RRC_MS_ID_BUTT
};
typedef VOS_UINT16 RRC_MS_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RRC_SS_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ״̬����״̬ö�ٶ���
*****************************************************************************/
enum RRC_SS_ID_ENUM
{
    /* ERRC PID״̬����״̬ */
    RRC_ERRC_SS_IDLE = 0,

    /* RRCģ�����״̬ */
    RRC_RRC_SS_WAIT_ITFL2_CFG_CNF,                            /* ���ò�2���ȴ�ITFL2��Ӧ����״̬ */
    RRC_RRC_SS_WAIT_ITFL2_REL_CNF,                            /* �ͷŲ�2���ȴ�ITFL2��Ӧ����״̬ */
    RRC_RRC_SS_WAIT_ITFPHY_CFG_CNF,                            /* ��������㣬�ȴ�ITFPHY��Ӧ����״̬ */
    RRC_RRC_SS_WAIT_ITFPHY_REL_CNF,                            /* �ͷ������㣬�ȴ�ITFPHY��Ӧ����״̬ */
    RRC_RRC_SS_WAIT_CSELPC_STATE_CHANGE_CNF,                            /* ֪ͨCSELPC��Э��״̬ԾǨ���ȴ�CSELPC��Ӧ����״̬ */
    RRC_RRC_SS_WAIT_CMM_STATE_CHANGE_CNF,                            /* ֪ͨCMM��Э��״̬ԾǨ���ȴ�CMM��Ӧ����״̬ */
    RRC_RRC_SS_WAIT_AM_DATA_CNF,                            /* ����AM���ݸ�PDCP���ȴ�PDCP��Ӧ����״̬ */
    RRC_RRC_SS_WAIT_CONN_SETUP,                            /* �ȴ��տ�CONN SETUP��Ϣ����״̬ */
    RRC_RRC_SS_WAIT_MAC_RA_CNF,                            /* ��MAC���������������󣬵ȴ����������Ӧ����״̬ */
    RRC_RRC_SS_WAIT_CSELPC_STOP_RESEL_CNF,                            /* ��CSELPC����ֹͣ��ѡ�󣬵ȴ���ѡֹͣ��Ӧ����״̬ */
    LRRC_LRRC_SS_WAIT_ITFL2_RESET_L2_CNF,                   /* �ȴ�ITFL2��λMAC��STOP PDCP��REEST RLC����״̬ */
    LRRC_LRRC_SS_WAIT_GRR_UE_CAP_INFO_CNF,                   /* �ȴ�GRR UE������Ӧ����״̬ */
    LRRC_LRRC_SS_WAIT_WRRC_UE_CAP_INFO_CNF,                   /* �ȴ�WRRC UE������Ӧ����״̬ */
    LRRC_LRRC_SS_WAIT_SET_WORK_MODE_CNF,                    /* �ȴ��������ģ����״̬ */
    LRRC_LRRC_SS_WAIT_CSELPC_CELL_SEARCH_CNF,                    /* �ȴ�CSELPCС��������Ӧ����״̬ */
    LRRC_LRRC_SS_WAIT_LMM_RESUME_RSP,                    /* �ȴ�LNAS�����Ӧ����״̬ */
    LRRC_LRRC_SS_WAIT_LMM_SUSPEND_RSP,                    /* �ȴ�LNAS������Ӧ����״̬ */
    LRRC_LRRC_SS_WAIT_GURRC_CNF,                      /* �ȴ�GURRC�ض���/��ѡ/CCO/�л���Ӧ����״̬ */
    LRRC_LRRC_SS_WAIT_WRRC_LOAD_DSP_CNF,                /* �ȴ�WRRC����WDSP��Ӧ����״̬ */
    LRRC_LRRC_SS_WAIT_GURRC_STOP_CNF,            /* �ȴ�GURRCֹͣ�ض���/��ѡ/CCO/�л���Ӧ����״̬ */
    LRRC_LRRC_SS_WAIT_GURRC_REL_ALL_CNF,            /* �ȴ�GURRC REL ALL��Ӧ����״̬ */
    LRRC_LRRC_SS_WAIT_GURRC_CELL_SRCH_CNF,          /* �ȴ�GURRC С��������Ӧ����״̬ */
    LRRC_LRRC_SS_WAIT_GURRC_CELL_SRCH_STOP_CNF,     /* �ȴ�GURRC ֹͣС��������Ӧ����״̬ */
    /* TDS begin */
    LRRC_LRRC_SS_WAIT_TRRC_REL_ALL_CNF,            /* �ȴ�TRRC REL ALL��Ӧ����״̬ */
    /* TDS end */
    /* END of RRCģ�����״̬ */

    /* RBģ�����״̬ */
    LRRC_LRB_SS_WAIT_SET_WORK_MODE_CNF,                    /* �ȴ��������ģ����״̬ */
    RRC_RB_SS_WAIT_RABM_STATUS_RSP_SUSPEND,                            /* ��RABM����ֹͣ���ݴ�������󣬵ȴ�RABM��Ӧ */
    RRC_RB_SS_WAIT_ITFL2_STOP_PDCP_CNF,                            /* ��L2����ֹͣPDCP�󣬵ȴ�ITFL2��Ӧ */
    RRC_RB_SS_WAIT_ITFL2_CFG_RLC_AND_MAC_CNF,                            /* ��L2�����ؽ�RLC����λMAC������MAC������RACH��Ϣ�󣬵ȴ�ITFL2��Ӧ */
    RRC_RB_SS_WAIT_ITFPHY_HO_CNF,                            /* ��PHY�����л���ʼ�󣬵ȴ�PHY��Ӧ */
    LRRC_LRB_SS_WAIT_GURRC_REL_ALL_CNF,            /* �ȴ�GURRC REL ALL��Ӧ����״̬ */
    RRC_RB_SS_WAIT_ITFPHY_CFG_CNF,                            /* ����PHY�󣬵ȴ���Ӧ */
    /* v7r2 ca begin */
    RRC_RB_SS_WAIT_ITFPHY_SCELL_SETUP_CNF,                            /* ����PHY�󣬵ȴ���Ӧ */
    RRC_RB_SS_WAIT_ITFPHY_SCELL_REL_CNF,                            /* ����PHY�󣬵ȴ���Ӧ */
    /* v7r2 ca end */
    RRC_RB_SS_WAIT_ITFL2_CFG_CNF,                            /* ����L2�󣬵ȴ���Ӧ */
    RRC_RB_SS_WAIT_ITFL2_CFG_PDCP_AND_RLC_CNF,                            /* ��PDCP��RLC��������RBʵ������󣬵ȴ�PDCP��RLC��Ӧ */
    /* v7r2 ca begin */
    RRC_RB_SS_WAIT_ITFL2_SCELL_SETUP_CNF,                       /* ����L2 scell SETUP�󣬵ȴ���Ӧ */
    RRC_RB_SS_WAIT_ITFL2_SCELL_REL_CNF,                         /* ����L2 scell rel�󣬵ȴ���Ӧ */
    /* v7r2 ca end */
    LRRC_LRB_SS_WAIT_MM_SECU_PARA_RSP,                    /* �ȴ�LNAS��ȫ��������״̬ */
    RRC_RB_SS_WAIT_SMC_SECU_CFG_CNF,                            /* ��SMC���Ͱ�ȫ������������󣬵ȴ�SMC��Ӧ */
    RRC_RB_SS_WAIT_PDCP_AM_DATA_CNF,                            /* ��PDCP����RRC CONNECTION RECONFIGURATION CMPL�󣬵ȴ�PDCP��Ӧ */
    LRRC_LRB_SS_WAIT_MM_RESUME_RSP,                    /* �ȴ�LNAS��ҵ���״̬ */
    RRC_RB_SS_WAIT_PDCP_CONTINUE_CNF,                            /* ��PDCP�����������ݴ�������󣬵ȴ�PDCP��Ӧ */
    RRC_RB_SS_WAIT_RABM_STATUS_RSP_RESUME,                            /* ��RABM���ͽ����������󣬵ȴ�RABM��Ӧ */
    RRC_RB_SS_WAIT_CMM_HO_CMPL_CNF,                            /* ��CMM�����л���ɺ󣬵ȴ�CMM��Ӧ */
    RRC_RB_SS_WAIT_PHY_SYNC_CNF,                                /* ��PHY�����ϱ�ͬ�����󣬵ȴ���Ӧ */
    RRC_RB_SS_WAIT_CMM_MEAS_CTRL_CNF,                            /* ��CMM���Ͳ�������ʱ���ȴ�CMM��Ӧ*/
    RRC_RB_SS_WAIT_ITF_REL_NEW_RB_CNF,                            /* ������ʧ�ܺ���Ҫ���½���RBɾ�� */
    /* END of RBģ�����״̬ */

    /* REESTģ�����״̬ */
    RRC_REEST_SS_WAIT_NAS_SUSPEND_RABM_RSP,                            /* �ȴ�����NAS��Ӧ(ֹͣ���ݴ���) */
    RRC_REEST_SS_WAIT_CMM_STATE_CHANGE_CNF,                            /* ��CMM����״̬�ı�����󣬵ȴ�CMM��Ӧ */
    RRC_REEST_SS_WAIT_ITFL2_STOP_PDCP_CNF,                            /* ��L2����ֹͣPDCP��������󣬵ȴ�L2��Ӧ */
    RRC_REEST_SS_WAIT_ITFL2_REEST_AND_RESET_L2_CNF,                            /* ��L2�����ؽ�RLC�͸�λMAC��������󣬵ȴ�L2��Ӧ */
    RRC_REEST_SS_WAIT_ITFPHY_RELALL_CNF,                            /* ������㷢����������󣬵ȴ�PHY��Ӧ */
    LRRC_LREEST_SS_WAIT_GURRC_REL_ALL_CNF,                  /* �ȴ�GURRC REL ALL��Ӧ����״̬ */
    /* TDS begin */
    LRRC_LREEST_SS_WAIT_TRRC_REL_ALL_CNF,                  /* �ȴ�TRRC REL ALL��Ӧ����״̬ */
    /* TDS end */
    RRC_REEST_SS_WAIT_CSELPC_STATE_CHANGE_CNF,                            /* ��CSELPC����״̬����󣬵ȴ�CSELPC��Ӧ */
    RRC_REEST_SS_WAIT_ITFL2_CONFIG_CNF,                            /* ��L2������������󣬵ȴ�L2��Ӧ */
    RRC_REEST_SS_WAIT_SMC_SECU_CONFIG_CNF,                            /* ��SMC������������󣬵ȴ�SMC��Ӧ */
    RRC_REEST_SS_WAIT_ITFPHY_CONFIG_CNF,                            /* ������㷢����������󣬵ȴ�PHY��Ӧ */
    RRC_REEST_SS_WAIT_MAC_RA_CNF,                            /* ��MAC���������������󣬵ȴ�MAC��Ӧ */
    RRC_REEST_SS_WAIT_CONNECTION_REESTABLISHMENT,                            /* �ȴ��տ���Ϣ */
    RRC_REEST_SS_WAIT_PDCP_AM_DATA_CNF,                            /* ����AM Data Req���ȴ�PDCP��Ӧ */
    RRC_REEST_SS_WAIT_DSDS_RADIO_RESOURCE_CNF,
    /* END of REESTģ�����״̬ */

    /* CSELPCģ�����״̬ */
    RRC_CSELPC_SS_WAIT_PHY_REL_ALL_CNF,                         /* �ȴ�PHY REL ALL��Ӧ����״̬ */
    RRC_CSELPC_SS_WAIT_PCH_RELEASE_CNF,
    RRC_CSELPC_SS_WAIT_CSEL_SPEC_PLMN_SEARCH_CNF,                            /* �ȴ�ָ��PLMN��������Ӧ����״̬ */
    RRC_CSELPC_SS_WAIT_CONFIG_PCH,                            /* �ȴ����������pch����״̬ */
    RRC_CSELPC_SS_WAIT_CONFIG_PHY_CNF,                            /* �ȴ�������������Ӧ����״̬ */
    RRC_CSELPC_SS_WAIT_PHY_CAMP_CNF,                            /* �ȴ������פ����Ӧ����״̬ */
    RRC_CSELPC_SS_WAIT_CONFIG_L2_CNF,
    RRC_CSELPC_SS_WAIT_CSEL_ANY_CELL_SEARCH_CNF,                            /* �ȴ�CSELģ��ANY CELL�����������״̬ */
    RRC_CSELPC_SS_WAIT_CSEL_SUIT_CELL_SEARCH_CNF,                            /* �ȴ�CSELģ��SUITABLE CELL�����������״̬ */
    RRC_CSELPC_SS_WAIT_CSEL_PLMN_LIST_SEARCH_CNF,                            /* �ȴ�CSELģ��PLMN LIST�����������״̬ */
    RRC_CSELPC_SS_WAIT_CSEL_STOP_PLMN_LIST_CNF,                            /* �ȴ�CSELģ��ֹͣPLMN LIST������Ӧ����״̬ */
    RRC_CSELPC_SS_WAIT_CSEL_CELL_SEARCH_CNF,                            /* �ȴ�CSELģ��ָ��cell��Ϣ������Ӧ����״̬ */
    RRC_CSELPC_SS_WAIT_CELL_RESEL_STOP,                            /* ����RRC��REESTС����ѡֹͣ�������״̬ */
    RRC_CSELPC_SS_WAIT_CELL_RESEL_STOP_CNF,                            /* �ȴ�CSELģ��ֹͣС����ѡ��Ӧ����״̬ */
    RRC_CSELPC_SS_WAIT_CELL_RESEL_START,                            /* ����RRC��REESTС����ѡ��ʼ����״̬ */
    RRC_CSELPC_SS_WAIT_CELL_RESEL_START_CNF,                            /* �ȴ�CSELģ������С����ѡ��Ӧ����״̬ */
    RRC_CSELPC_SS_WAIT_SIB_SYS_REL_CNF,                            /* �ȴ�sibɾ������״̬ */
    RRC_CSELPC_SS_WAIT_SIB_SYS_INFO_UPDATE_CNF,                            /* �ȴ�SIBģ��ϵͳ��Ϣ���µ���״̬ */
    RRC_CSELPC_SS_WAIT_CSEL_SYS_INFO_CNF,                            /* ֪ͨCSELϵͳ��Ϣ���£��ȴ�CSELģ����Ӧ����״̬ */
    RRC_CSELPC_SS_WAIT_CMM_SYS_INFO_CNF,                            /* ֪ͨCMMϵͳ��Ϣ���£��ȴ�CMMģ����Ӧ����״̬ */
    RRC_CSELPC_SS_WAIT_STATE_CHANGE,                            /* ͸��RRC��REEST��״̬���֪ͨʱ���ȴ�״̬���֪ͨ����״̬ */
    RRC_CSELPC_SS_WAIT_STATE_CHANGE_CNF,                            /* �ȴ�CSEL״̬�����Ӧ����״̬ */
    LRRC_LCSELPC_SS_WAIT_SET_WORK_MODE_CNF,                    /* �ȴ��������ģ����״̬ */
    LRRC_LCSELPC_SS_WAIT_CMM_RELALL_CNF,                           /*�ȴ�CMM�ظ�NTF״̬���ͷ�PHY��ϵͳ����֮����ӦCSELPC����״̬*/
    /* MBMS Begin */
    LRRC_LCSELPC_SS_WAIT_MBMS_FLOW_CMPLETE,
    LRRC_LCSELPC_SS_WAIT_MBMS_MCCH_CFG_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_MCCH_MSG_IND,
    LRRC_LCSELPC_SS_WAIT_MBMS_MCCH_RECFG_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_L2_CFG_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_PHY_CFG_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_L2_REL_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_PHY_REL_CNF,
    /* MBMS end */
    /* bgs begin */
    LRRC_LCSELPC_SS_WAIT_BGS_SUSPEND_CNF,                                         /* �ȴ������ѹ�����Ӧ����״̬ */
    LRRC_LCSELPC_SS_WAIT_BGS_RESUME_CNF,                                          /* �ȴ������ѻָ���Ӧ����״̬ */
    LRRC_LCSELPC_SS_WAIT_BGS_STOP_CNF,                                            /* �ȴ�������ֹͣ��Ӧ����״̬ */
    /* bgs end */
    /* begin: add mbms for feature v700r500 */
    LRRC_CSELPC_SS_WAIT_CONN_TO_IDLE_REQ,            /* �ȴ�phy ֱ��פ����Ӧ����״̬ */
    /* end: add mbms for feature v700r500 */

    /* END of CSELPCģ�����״̬ */
    /* SMCģ�����״̬ */
    RRC_SMC_SS_WAIT_PDCP_SECU_CONFIG_CNF,                                       /* �ȴ�����PDCP��ȫ��Կ����״̬ */
    RRC_SMC_SS_WAIT_PDCP_DATA_CNF,                                              /* ��ȫģʽ����ɹ�����cmpl����״̬ */
    RRC_SMC_SS_WAIT_PDCP_FAIL_ACT_SECU_CNF,                                     /* ��ȫģʽ����ʧ������PDCP��ȫ����״̬ */
    RRC_SMC_SS_WAIT_PDCP_CNT_CHK_CNF,
    /* END of SMCģ�����״̬ */

    /* ITFģ�����״̬ */

    /* RRC_ITFL2_SS_WAIT_CFG_CNF                      ,
     RRC_ITFPHY_SS_WAIT_CFG_CNF                     ,*/
    RRC_ITF_SS_WAIT_CFG_CNF,

    /* END of ITFģ�����״̬ */

    /* bgs begin */
    /* CSELBGģ�����״̬ */
    LRRC_LCSELBG_SS_IDLE,
    LRRC_LCSELBG_SS_WAIT_LPHY_BGS_CNF,
    LRRC_LCSELBG_SS_WAIT_GURRC_BGS_CNF,
    LRRC_LCSELBG_SS_WAIT_CELLSEARCHING_IND,
    LRRC_LCSELBG_SS_WAIT_GET_SYSINFO_CNF,
    LRRC_LCSELBG_SS_WAIT_REL_SYSINFO_CNF,

    LRRC_LCSELBG_SS_WAIT_LPHY_SUSPEND_BGS_CNF,
    LRRC_LCSELBG_SS_WAIT_LPHY_RESUME_BGS_CNF,
    /* END of CSELBGģ�����״̬ */
    /* bgs end */

    /* CSELģ�����״̬ */
    RRC_CSEL_SS_IDLE,
    RRC_CSEL_SS_WAIT_CELL_SEARCHING_IND,/* ��PHY����С����������󣬵ȴ�PHY��Ӧ */
    RRC_CSEL_SS_WAIT_GET_SYSINFO_CNF,/* ��SIB����ϵͳ��Ϣ��������󣬵ȴ�SIB��Ӧ */
    RRC_CSEL_SS_WAIT_STOP_CELL_SEARCHING_CNF,/* ��PHY����ֹͣС����������󣬵ȴ�PHY��Ӧ */
    RRC_CSEL_SS_WAIT_REL_SYSINFO_CNF,/* ��SIB����ϵͳ��Ϣ��������󣬵ȴ�SIB��Ӧ */
    RRC_CSEL_SS_MEAS_SETUP                          ,    /* �������ò��� */
    RRC_CSEL_SS_MEAS_RELEASE                        ,    /* �����ͷŲ��� */
    RRC_CSEL_SS_SIB_ACQUIRE                         ,    /* ������ȡ���� SIB */
    RRC_CSEL_SS_SIB_CANCEL                          ,    /* ������Ϊֹͣ��ѡ��ȡ������ SIB */
    RRC_CSEL_SS_RESEL_RSP                           ,    /* ���ڵȴ���ѡָʾ��Ӧ�� */
    LRRC_LCSEL_SS_GU_MEAS_SETUP                     ,    /* ��������GUģ�������� */
    LRRC_LCSEL_SS_GU_MEAS_RELEASE                   ,    /* ��������GUģ�������� */
    LRRC_LCSEL_SS_WAIT_LPHY_MEAS_CNF                ,    /* L��ģʱ������������ */
    LRRC_LCSEL_SS_WAIT_WRRC_BSIC_VERITY_CNF         ,    /* �ȴ�WRRC BSIC��֤����״̬ */
    LRRC_LCSEL_SS_WAIT_LPHY_BSIC_VERITY_CNF         ,    /* �ȴ�LPHY BSIC��֤����״̬ */
    /* TDS begin */
    LRRC_LCSEL_SS_UTRA_TDD_MEAS_SETUP               ,    /* ��������UTRA_TDDģ�������� */
    LRRC_LCSEL_SS_UTRA_TDD_MEAS_RELEASE             ,    /* ��������UTRA_TDDģ�ͷŲ��� */
    /* TDS end */
    /* bgs begin */
    LRRC_LCSEL_SS_WAIT_BGS_SUSPEND_CNF,               /* �ȴ�LCSELPC �����ѹ������״̬ */
    LRRC_LCSEL_SS_WAIT_BGS_RESUME_CNF,                /* �ȴ�LCSELPC �����ѻָ�����״̬ */
    /* bgs end */

    /*DSDS begin: 2014-07-23*/
    RRC_CSEL_SS_WAIT_LPHY_BGS_START_CNF,              /* �ȴ�PHY�ظ������ѿ�ʼ��Ӧ����״̬*/
    /*DSDS begin: 2014-07-23*/
    RRC_CSEL_SS_WAIT_LPHY_FREQ_RSSI_SORT_CNF,         /*�ȴ������Ƶ������Ľ��*/

    RRC_CSEL_SS_WAIT_LPHY_BGS_RESEL_PREWORK_CNF,      /*BGS��ѡ׼���������ȴ������ظ�ȷ��*/

    RRC_CSEL_SS_WAIT_LPHY_BGS_STOP_CNF,               /*BGS��ѡSTOP�����Ѻ�ȴ��ظ�ȷ��*/

    RRC_CSEL_SS_SIB_ACQUIRE_BGSRESEL,                 /*BGS��ѡ�ȴ�ϵͳ��Ϣ��ȷ��״̬*/

    /* END of CSELģ�����״̬ */

    /* CMMģ�����״̬ */
    RRC_CMM_SS_IDLE,
    RRC_CMM_SS_WAIT_SETUP_INTRA_FREQ_CNF,
    RRC_CMM_SS_WAIT_REL_INTRA_FREQ_CNF,
    RRC_CMM_SS_WAIT_SETUP_INTER_FREQ_CNF,
    RRC_CMM_SS_WAIT_REL_INTER_FREQ_CNF,
    RRC_CMM_SS_WAIT_CFG_MEAS_GAP_CNF,
    LRRC_LCMM_SS_WAIT_LPHY_MEAS_CNF,                     /* L��ģʱ������������ */
    LRRC_LCMM_SS_WAIT_WRRC_BSIC_VERITY_CNF,           /* �ȴ�WRRC BSIC��֤����״̬ */
    LRRC_LCMM_SS_WAIT_LPHY_BSIC_VERITY_CNF,          /* �ȴ�LPHY BSIC��֤����״̬ */
    LRRC_LCMM_SS_WAIT_GURRC_MEAS_SETUP_CNF,              /* L��ģʱ���ý���GUģ���� */
    LRRC_LCMM_SS_WAIT_GURRC_MEAS_REL_CNF,                /* L��ģʱ�����ͷ�GUģ���� */
    LRRC_LCMM_SS_WAIT_LPHY_GURRC_MEAS_SETUP_CNF,         /* L��ģʱ����LPHY����GUģ���� */
    LRRC_LCMM_SS_WAIT_LPHY_GURRC_MEAS_REL_CNF,           /* L��ģʱ����LPHY�ͷ�GUģ���� */
    /* TDS begin */
    LRRC_LCMM_SS_WAIT_UTRA_TDD_MEAS_SETUP_CNF,              /* L��ģʱ���ý���UTRA_TDDģ���� */
    LRRC_LCMM_SS_WAIT_UTRA_TDD_MEAS_REL_CNF,                /* L��ģʱ�����ͷ�UTRA_TDDģ���� */
    /* TDS end */
    /* anr begin */
    LRRC_LCMM_SS_WAIT_LPHY_ANR_START_CNF,
    LRRC_LCMM_SS_WAIT_LPHY_ANR_STOP_CNF,
    LRRC_LCMM_SS_WAIT_GURRC_ANR_START_CNF,
    LRRC_LCMM_SS_WAIT_GURRC_ANR_STOP_CNF,
    /* anr end */

    /* v7r2 ca begin */
    LRRC_LCMM_SS_WAIT_GU_MEAS_CNF,
    LRRC_LCMM_SS_WAIT_PHY_MEAS_CNF,
    /* v7r2 ca end */

    /* END of CMMģ�����״̬ */

    /* SIBģ�����״̬ */
    RRC_SIB_SS_IDLE,
    RRC_SIB_SS_WAIT_PBCH_SETUP_CNF,
    RRC_SIB_SS_WAIT_MIB_IND,
    RRC_SIB_SS_WAIT_PBCH_REL_CNF,
    RRC_SIB_SS_WAIT_RL_SETUP_CNF,
    RRC_SIB_SS_WAIT_SIB1_IND,
    RRC_SIB_SS_WAIT_SI_CFG_CNF,
    RRC_SIB_SS_WAIT_SIB_IND,
    RRC_SIB_SS_WAIT_RL_REL_CNF,
    RRC_SIB_SS_CSEL_WAIT_SETUP_CNF,
    RRC_SIB_SS_CSEL_WAIT_REL_CNF,
    /* END of SIBģ�����״̬ */

    /* begin: 2014-03- 20 CL MULT add */
    LRRC_LRRC_SS_WAIT_CDMA_CNF,                      /* �ȴ�CDMA�ض���/��ѡ��Ӧ����״̬ */
    LRRC_LRRC_SS_WAIT_CDMA_STOP_CNF,                 /* �ȴ�CDMA�ض���/��ѡֹͣ��Ӧ����״̬ */
    /* end: 2014-03- 20 CL MULT add */

    LRRC_DSDS_SS_WAIT_RRM_RADIO_RESOURCE_CNF,       /* �ȴ�dsds��RRM��Դ������Ӧ����״̬ */

    /* add for Balong CL begin */
    LRRC_LCSEL_SS_CDMA_HRPD_MEAS_SETUP               ,    /* ��������CDMA_HRPDģ�������� */
    LRRC_LCSEL_SS_CDMA_HRPD_MEAS_RELEASE             ,    /* ��������CDMA_HRPDģ�ͷŲ��� */
    LRRC_LRRC_SS_WAIT_CAS_REL_ALL_CNF                ,    /* �ȴ�CAS REL ALL CNF����״̬ */
    LRRC_LCMM_SS_WAIT_HRPD_MEAS_CNF,
    /* add for Balong CL end */

    LRRC_LRRC_SS_WAIT_CONN_TO_IDLE_CNF,            /* �ȴ�phy ֱ��פ����Ӧ����״̬ */
    LRRC_LCSELPC_SS_WAIT_MBMS_PHY_ENABLE_CNF,                 /*�ȴ�PHY MBMSʹ��ȷ����Ϣ*/
    LRRC_LCSELPC_SS_WAIT_MBMS_PHY_DISABLE_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_NOTIFY_CFG_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_PMCH_CFG_CNF,
    LRRC_LCSELPC_SS_WAIT_MBMS_PMCH_ACTIVE_CNF,

    LRRC_LCMM_SS_WAIT_LPHY_OTDOA_CNF,
    LRRC_LRRC_SS_WAIT_LCMM_OTDOA_CNF,

    /* ״̬��Ԥ��״̬����Ҫ���ڲ���״̬������Ϣ�Ĵ��� */
    RRC_SS_PRE_PROCESS,

    RRC_SS_ID_BUTT
};
typedef VOS_UINT16 RRC_SS_ID_ENUM_UINT16;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/


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

#endif /* end of LPsFsmState.h */
