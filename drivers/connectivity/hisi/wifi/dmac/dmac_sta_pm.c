


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "dmac_sta_pm.h"
#include "dmac_psm_sta.h"
#include "dmac_ext_if.h"
#include "mac_resource.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_psm_ap.h"
#include "pm_extern.h"
#include "dmac_p2p.h"
#include "dmac_config.h"

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif
#include "dmac_pm_sta.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_STA_PM_C

OAL_STATIC oal_void sta_power_state_active_entry(oal_void *p_ctx);
OAL_STATIC oal_void sta_power_state_active_exit(oal_void *p_ctx);
OAL_STATIC oal_uint32 sta_power_state_active_event(oal_void  *p_ctx, oal_uint16  us_event,
                                    oal_uint16 us_event_data_len,  oal_void  *p_event_data);
OAL_STATIC oal_void sta_power_state_doze_entry(oal_void *p_ctx);

OAL_STATIC oal_void sta_power_state_doze_exit(oal_void *p_ctx);

OAL_STATIC oal_uint32 sta_power_state_doze_event(oal_void  *p_ctx, oal_uint16  us_event,
                                    oal_uint16 us_event_data_len,  oal_void  *p_event_data);

OAL_STATIC oal_void sta_power_state_awake_entry(oal_void *p_ctx);

OAL_STATIC oal_void sta_power_state_awake_exit(oal_void *p_ctx);

OAL_STATIC oal_uint32 sta_power_state_awake_event(oal_void  *p_ctx, oal_uint16  us_event,
                                    oal_uint16 us_event_data_len,  oal_void  *p_event_data);

oal_void dmac_pm_sta_state_trans(mac_sta_pm_handler_stru* pst_handler,oal_uint8 uc_state, oal_uint16 us_event);
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
oal_uint32                 g_lightsleep_fe_awake_cnt = 0; //ǳ˯�ָ�ǰ�˼���
oal_uint32                 g_deepsleep_fe_awake_cnt  = 0; //��˯�ָ�ǰ�˼���

/* ȫ��״̬�������� */
mac_fsm_state_info  g_sta_power_fsm_info[] = {

    {
        STA_PWR_SAVE_STATE_ACTIVE,
        "ACTIVE",
        sta_power_state_active_entry,
        sta_power_state_active_exit,
        sta_power_state_active_event,
    },

    {
        STA_PWR_SAVE_STATE_DOZE,
        "DOZE",
        sta_power_state_doze_entry,
        sta_power_state_doze_exit,
        sta_power_state_doze_event,
    },
    {
        STA_PWR_SAVE_STATE_AWAKE,
        "AWAKE",
        sta_power_state_awake_entry,
        sta_power_state_awake_exit,
        sta_power_state_awake_event,
    },
};
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if 0
/*****************************************************************************
 �� �� ��  : dmac_pm_sta_vote
 ��������  : ��ƽ̨ͶƱ�����
 �������  : p_fsm:״̬��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��13��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_pm_sta_vote(dmac_vap_stru  *pst_dmac_vap, oal_uint8 uc_vote)
{
    mac_device_stru    *pst_device;

    pst_device      = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);

    if (uc_vote >=  WLAN_STS_NUM)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_vote::uc_vote:[%d]\r\n.}", uc_vote);
    }
    /* DBACû�п���������²���Ͷ˯��Ʊ */
    else if ((WLAN_DEEPSLEEP == uc_vote) || (WLAN_LIGHTSLEEP == uc_vote))
    {
        if(OAL_FALSE == mac_is_dbac_running(pst_device))
        {
            /* ��¼˯��ʱvap id */
            pst_device->uc_mac_vap_id = pst_dmac_vap->st_vap_base_info.uc_vap_id;

            /* ��˯ǳ˯�ŵ��ô˽ӿ� */
            PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, uc_vote);
        }
    }
    else
    {
        PM_WLAN_SwitchToState(pst_dmac_vap->pst_hal_vap->uc_service_id, uc_vote);
    }
}
#endif
/*****************************************************************************
 �� �� ��  : dmac_pm_enable_front_end
 ��������  : �͹��Ļ���ǰ�˲���
 �������  : p_ctx:״̬�������ģ��Խ���״̬����˵Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��14��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_pm_enable_front_end(mac_device_stru *pst_mac_device)
{
    oal_uint32                  ulTimeOut;

    if ((WLAN_LIGHT_SLEEP == g_us_PmWifiSleepRfPwrOn) || (WLAN_DEEP_SLEEP == g_us_PmWifiSleepRfPwrOn))
    {
        /* wlan iq switch */
        rRF_WB_CTL_ABB_WB_IQ_EXCHANGE_REG = 0x4;
        rRF_WB_CTL_ABB_WB_DAT_PHASE_REG = 0x2;

        /* wlan open rfldo2 */
        PM_WLAN_OpenRfldo2();

        /* wlan rfldo2 open check */
        ulTimeOut = PM_WLAN_TIMEOUT_INIT;
        while(ERR == PM_WLAN_CheckRfldo2())
        {
           ulTimeOut--;
           if(0 == ulTimeOut)
           {
               PM_WLAN_PRINT("Fail to open rfldo2"NEWLINE);
               break;
           }
        }

        /* ��˯�ָ�ǰ�� */
        if (WLAN_DEEP_SLEEP == g_us_PmWifiSleepRfPwrOn)
        {
            /* wlan rf awake */
            dmac_psm_rf_awake(OAL_TRUE);
            g_deepsleep_fe_awake_cnt++;
        }
        /* ǳ˯�ָ�ǰ�� */
        else
        {
            dmac_psm_rf_awake(OAL_FALSE);
            g_lightsleep_fe_awake_cnt++;
        }

        /* wlan open paldo */
        PM_WLAN_OpenPaldo();
        oal_udelay(120);
        PM_WLAN_PaldoWorkMode();

        /* ʹ��pa */
        hal_enable_machw_phy_and_pa(pst_mac_device->pst_device_stru);

        /* �ָ�Ӳ������ */
        hal_set_machw_tx_resume(pst_mac_device->pst_device_stru);

        g_us_PmWifiSleepRfPwrOn = WLAN_NOT_SLEEP;

    }
}

/*****************************************************************************
 �� �� ��  : dmac_pm_process_deassociate
 ��������  : ����ȥ�����¼��Ľӿ�
 �������  : p_ctx:״̬�������ģ��Խ���״̬����˵Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_pm_process_deassociate(mac_sta_pm_handler_stru* pst_sta_pm_handler)
{
    dmac_vap_stru               *pst_dmac_vap;
    mac_cfg_ps_open_stru         st_ps_open;

    pst_dmac_vap = (dmac_vap_stru *)(pst_sta_pm_handler->p_mac_fsm->p_oshandler);

    if(STA_GET_PM_STATE(pst_sta_pm_handler) != STA_PWR_SAVE_STATE_ACTIVE)
    {
        dmac_pm_sta_state_trans(pst_sta_pm_handler, STA_PWR_SAVE_STATE_ACTIVE, STA_PWR_EVENT_DEASSOCIATE);/* ����״̬ */
    }
    /*ȥ��������Ҫ�ر�Э��͹��ķ�������´����¹���ʱ�����ȡdhcpǰ����͹���ģʽ--��˯��null֡ */
    st_ps_open.uc_sta_pm_open = MAC_STA_OFF_PM;

    dmac_set_sta_pm_open(&(pst_dmac_vap->st_vap_base_info), OAL_SIZEOF(mac_cfg_ps_open_stru), (oal_uint8 *)&st_ps_open);

    /* ����ȥ����ɾ����ʱ�� */
    if(OAL_TRUE == pst_sta_pm_handler->st_inactive_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_sta_pm_handler->st_inactive_timer));
    }

    /* ȥ������service id ȥע�� */
    hal_pm_wlan_servid_unregister(pst_dmac_vap->pst_hal_vap);
}


oal_void dmac_process_send_null_succ_event(mac_sta_pm_handler_stru  *pst_pm_handler, mac_ieee80211_frame_stru  *pst_mac_hdr)
{
    dmac_vap_stru               *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)(pst_pm_handler->p_mac_fsm->p_oshandler);

    if (OAL_PTR_NULL == pst_mac_hdr)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_ps_process_send_null_succ_event::pst_mac_hdr NULL.}");
        return;
    }
    /* ��beacon��awake״̬�л���active״̬����null֡�ɹ� */
    if (STA_PWR_SAVE_STATE_ACTIVE == pst_mac_hdr->st_frame_control.bit_power_mgmt)
    {
        /* fast_ps�Ż��ٴν���active״̬ */
        if (OAL_TRUE == pst_pm_handler->st_null_wait.en_active_null_wait)
        {
            pst_pm_handler->st_null_wait.en_active_null_wait  = OAL_FALSE;

            /* active null֡���ɹ�����activity ��ʱ�� */
            dmac_psm_start_activity_timer(pst_dmac_vap,pst_pm_handler);

            /* No need to track this flag in ACTIVE state */
            pst_pm_handler->en_more_data_expected = OAL_FALSE;

            if (STA_PWR_SAVE_STATE_ACTIVE != STA_GET_PM_STATE(pst_pm_handler))
            {
                dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_ACTIVE, STA_PWR_EVENT_SEND_NULL_SUCCESS);

                /* ˯�ߵ����ѵĴ���ͳ�� */
                pst_pm_handler->aul_pmDebugCount[PM_MSG_WAKE_TO_ACTIVE]++;
            }
        }
    }
    /* ��ʱ��������,��ʱ�л���doze״̬ */
    else
    {
        if(OAL_TRUE == (pst_pm_handler->st_null_wait.en_doze_null_wait))
        {
            pst_pm_handler->st_null_wait.en_doze_null_wait  = OAL_FALSE;
            pst_pm_handler->en_ps_deep_sleep                = OAL_TRUE;     /* �л���ǳ˯ */

            OAM_INFO_LOG0(0, OAM_SF_PWR, "{dmac_ps_process_send_null_succ_event::en_doze_null_wait oal_true}");

            if (STA_PWR_SAVE_STATE_DOZE == STA_GET_PM_STATE(pst_pm_handler))
            {
                /* ���ѵ�˯�ߵĴ���ͳ�� */
                pst_pm_handler->aul_pmDebugCount[PM_MSG_WAKE_TO_DOZE]++;
            }
            else if (STA_PWR_SAVE_STATE_ACTIVE == STA_GET_PM_STATE(pst_pm_handler))
            {
                /* ���ѵ�˯�ߵĴ���ͳ�� */
                pst_pm_handler->aul_pmDebugCount[PM_MSG_ACTIVE_TO_DOZE]++;
            }

            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_DOZE, STA_PWR_EVENT_SEND_NULL_SUCCESS);
        }
    }

}
OAL_STATIC oal_void sta_power_state_active_entry(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 �� �� ��  : sta_power_state_active_exit
 ��������  : active״̬��exit�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void sta_power_state_active_exit(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_work_event
 ��������  : active״̬��event�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
             us_event:�������¼�
             us_event_data_len:�¼���Я�������ݳ���
             p_event_data:�¼���Я�����¼���Ӧ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 sta_power_state_active_event(oal_void   *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    oal_uint32                       ul_ret;
    mac_ieee80211_frame_stru        *pst_mac_hdr;
    dmac_vap_stru                   *pst_dmac_vap = OAL_PTR_NULL;
    mac_device_stru                 *pst_mac_device;

    mac_sta_pm_handler_stru*  pst_pm_handler = (mac_sta_pm_handler_stru*)p_ctx;
    if(OAL_PTR_NULL == pst_pm_handler)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_active_event::pst_pm_handler null}");
        return OAL_FAIL;
    }

    pst_dmac_vap = (dmac_vap_stru *)(pst_pm_handler->p_mac_fsm->p_oshandler);
    if(OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_active_event::pst_dmac_vap null}");
        return OAL_FAIL;
    }
    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_active_event::pst_mac_device null}");
        return OAL_FAIL;
    }

    switch(us_event)
    {
        case STA_PWR_EVENT_TIMEOUT:
            //OAM_INFO_LOG0(0, OAM_SF_PWR, "{sta_power_state_active_event::dmac_send_null_frame_to_ap doze}");
            ul_ret = dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_DOZE, OAL_FALSE);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_power_state_active_event:dmac_send_null_frame_to_ap:[%d]}", ul_ret);
            }
        break;

        /* active ״̬��null֡���ͳɹ����½������ģʽ */
        case STA_PWR_EVENT_SEND_NULL_SUCCESS:
        	pst_mac_hdr = (mac_ieee80211_frame_stru *)(p_event_data);
            dmac_process_send_null_succ_event(pst_pm_handler, pst_mac_hdr);
        break;

        /* active ������keepalive��ʱ�� */
        case STA_PWR_EVENT_KEEPALIVE:
            /* ��ʱ����keepalive */
            pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_keepalive   =  OAL_TRUE;

            if (OAL_TRUE != pst_pm_handler->st_inactive_timer.en_is_registerd)
            {
                /* �����³�ʱʱ��ͷǽ����µĳ�ʱʱ�䲻һ����������ʱ�� */
                FRW_TIMER_CREATE_TIMER(&(pst_pm_handler->st_inactive_timer),
                                    dmac_psm_alarm_callback,
                                    pst_pm_handler->ul_activity_timeout ,
                                    pst_dmac_vap,
                                    OAL_FALSE,
                                    OAM_MODULE_ID_DMAC,
                                    pst_mac_device->ul_core_id);
            }
			/* staut �����Ϻ���up״̬����ƽ̨ע�� */
            hal_pm_wlan_servid_register(pst_dmac_vap->pst_hal_vap, &ul_ret);
            if (OAL_SUCC != ul_ret)
            {
              OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                                     "{sta_power_state_active_event:hal_pm_wlan_servid_register hal vap:[%d]fail",pst_dmac_vap->pst_hal_vap->uc_vap_id);

            }

        break;

        /* p2p ��ʱӦRESTART active->doze�Ķ�ʱ�� */
        case STA_PWR_EVENT_P2P_SLEEP:
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_TRUE);

            if ((WLAN_MIB_PWR_MGMT_MODE_PWRSAVE == mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info))) &&
              (OAL_TRUE == dmac_is_sta_fast_ps_enabled(pst_pm_handler)))
            {
                dmac_psm_start_activity_timer(pst_dmac_vap,pst_pm_handler);
            }
        break;

        case STA_PWR_EVENT_P2P_AWAKE:
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
        break;

		case STA_PWR_EVENT_PNO_SCHED_SCAN_COMP:
		    pst_pm_handler->en_ps_deep_sleep = OAL_TRUE;

			/* PNO����˯�����ٵ� todo */
            //dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_DOZE, us_event);
		break;

        case STA_PWR_EVENT_DEASSOCIATE:
            dmac_pm_process_deassociate(pst_pm_handler);
        break;

        case STA_PWR_EVENT_TX_MGMT:
            dmac_pm_enable_front_end(pst_mac_device);
            pst_pm_handler->aul_pmDebugCount[PM_MSG_TX_MGMT]++;
        break;
        default:
        break;
    }
    return OAL_SUCC;
}


oal_uint8  dmac_is_sta_allow_to_sleep(mac_device_stru *pst_device, dmac_vap_stru *pst_dmac_vap, mac_sta_pm_handler_stru* pst_sta_pm_handler)
{
    oal_uint8          uc_vap_idx;
    mac_vap_stru      *pst_vap;
    wlan_bw_cap_enum_uint8      en_bwcap_vap;        /* ��ǰVAP����������� */
    wlan_bw_cap_enum_uint8      en_vap_bwcap_vap;     /* һ��VAP����������� */

    /* ����ɨ�費˯�� */
    if (MAC_SCAN_STATE_RUNNING == pst_device->en_curr_scan_state)
    {
        pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_SCAN_DIS_ALLOW_SLEEP]++;
        return OAL_FALSE;
    }
    /* DBAC running ��˯�� */
    if(OAL_TRUE == mac_is_dbac_running(pst_device))
    {
        pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_DBAC_DIS_ALLOW_SLEEP]++;
        return OAL_FALSE;
    }

    /* beacon�����ղ���DMAC_BEACON_TIMEOUT_MAX_NUM�β�˯�� */
    if (pst_dmac_vap->bit_beacon_timeout_times > DMAC_BEACON_TIMEOUT_MAX_NUM)
    {
        pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_BCNTIMOUT_DIS_ALLOW_SLEEP]++;
        return OAL_FALSE;
    }

    if(pst_device->uc_vap_num < 2)
    {
        return OAL_TRUE;
    }

    /* �����ɹ�״̬�²Ž����Ƿ�20/40M���ж� */
    if(OAL_SUCC != mac_device_is_p2p_connected(pst_device))
    {
        return OAL_TRUE;
    }

    /* ��ȡVAP�������� */
    mac_vap_get_bandwidth_cap(&pst_dmac_vap->st_vap_base_info, &en_bwcap_vap);

    /* ����device������vap */
    for (uc_vap_idx = 0; uc_vap_idx <pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_PWR,
                             "{dmac_p2p_one_channel_diff_band::pst_vap null,vap_id=%d.}", pst_device->auc_vap_id[uc_vap_idx]);

            continue;
        }

        /* ���ﲻ�ܼӴ�ӡ,���ǼӼ��� */
        if(IS_P2P_GO(pst_vap))
        {
            continue;
        }

        /* �����ɹ�״̬�²Ž����Ƿ�20/40M���ж� */
        if(IS_STA(pst_vap) && (MAC_VAP_STATE_UP != pst_vap->en_vap_state))
        {
            continue;
        }

        /* ��ȡÿ��VAP�������� */
        mac_vap_get_bandwidth_cap(pst_vap, &en_vap_bwcap_vap);

        if((IS_P2P_CL(pst_vap) || (IS_STA(pst_vap) && (MAC_VAP_STATE_UP == pst_vap->en_vap_state))) && (en_vap_bwcap_vap != en_bwcap_vap))
        {
            pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_FREQ_DIS_ALLOW_SLEEP]++;
            return OAL_FALSE;
        }
    }
    return OAL_TRUE;

}


/*****************************************************************************
 �� �� ��  : dmac_power_state_process_doze
 ��������  : active״̬��entry�ӿ�
 �������  : p_ctx:״̬�������ģ��Խ���״̬����˵Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_power_state_process_doze(mac_sta_pm_handler_stru* pst_sta_pm_handler, oal_uint8 uc_ps_mode)
{

    mac_device_stru             *pst_device;
    dmac_vap_stru               *pst_dmac_vap;

    pst_dmac_vap    = (dmac_vap_stru *)(pst_sta_pm_handler->p_mac_fsm->p_oshandler);

    pst_device      = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);

    pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_PROCESS_DOZE_CNT]++;

    if ((pst_sta_pm_handler->en_hw_ps_enable) && (OAL_TRUE == dmac_is_sta_allow_to_sleep(pst_device,pst_dmac_vap, pst_sta_pm_handler)))
    {
        pst_device->uc_mac_vap_id = pst_dmac_vap->st_vap_base_info.uc_vap_id;

        if (OAL_TRUE == (oal_uint8)IS_P2P_PS_ENABLED(pst_dmac_vap))
        {
            uc_ps_mode = STA_PS_LIGHT_SLEEP;
            pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_PSM_P2P_PS]++;
        }

        if (STA_PS_DEEP_SLEEP == uc_ps_mode)
        {
            #ifdef PM_WLAN_FPGA_DEBUG
                /*˯������ʱ��۲��P12,����*/
                //WRITEW(0x50002174,READW(0x50002174)|((1<<2)));
            #endif
            pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_DEEP_DOZE_CNT]++;
	        /* ����ƽ̨�ӿ��л���deepsleep ״̬ */
			PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_DEEPSLEEP_PROCESS);
	    }
	    else
	    {
            pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_LIGHT_DOZE_CNT]++;
			PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_LIGHTSLEEP_PROCESS);
	    }
	}

#ifdef PM_WLAN_FPGA_DEBUG
    /*˯������ʱ��۲��P12,����*/
    //WRITEW(0x50002174,READW(0x50002174)&(~(1<<2)));
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : sta_power_state_doze_entry
 ��������  : active״̬��entry�ӿ�
 �������  : p_ctx:״̬�������ģ��Խ���״̬����˵Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void sta_power_state_doze_entry(oal_void *p_ctx)
{
    oal_uint8                   uc_ps_mode;
    mac_sta_pm_handler_stru*    pst_sta_pm_handler = (mac_sta_pm_handler_stru*)p_ctx;

    if(OAL_PTR_NULL == pst_sta_pm_handler)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_doze_entry::pst_pm_handler null}");
        return;
    }

    /* ȷ������˯����ǳ˯ */
    uc_ps_mode = (OAL_TRUE == pst_sta_pm_handler->en_ps_deep_sleep) ? STA_PS_DEEP_SLEEP : STA_PS_LIGHT_SLEEP;

    /* �����л���֡���͵�host,todo */

    /* ����doze״̬�µ���˯��ǳ˯������ƽ̨�Ľӿ� */
    dmac_power_state_process_doze(pst_sta_pm_handler, uc_ps_mode);

    /* Increment the number of STA sleeps */
    //DMAC_STA_PSM_STATS_INCR(pst_sta_pm_handler->st_psm_stat_info.ul_sta_doze_times);
    return;
}

/*****************************************************************************
 �� �� ��  : sta_power_state_active_exit
 ��������  : active״̬��exit�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void sta_power_state_doze_exit(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_work_event
 ��������  : active״̬��event�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
             us_event:�������¼�
             us_event_data_len:�¼���Я�������ݳ���
             p_event_data:�¼���Я�����¼���Ӧ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 sta_power_state_doze_event(oal_void   *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    oal_uint32                  ul_ret;
    mac_sta_pm_handler_stru*    pst_pm_handler = (mac_sta_pm_handler_stru*)p_ctx;
    dmac_vap_stru              *pst_dmac_vap;

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_doze_event::pst_pm_handler null}");
        return OAL_FAIL;
    }

    pst_dmac_vap = (dmac_vap_stru *)(pst_pm_handler->p_mac_fsm->p_oshandler);
    if(OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_doze_event::pst_dmac_vap null}");
        return OAL_FAIL;
    }

    switch(us_event)
    {
        /* null֡���ͳɹ���ʱȴ����doze״̬���쳣���� */
        case STA_PWR_EVENT_SEND_NULL_SUCCESS:
        case STA_PWR_EVENT_TX_DATA:
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_AWAKE, us_event);
            pst_pm_handler->aul_pmDebugCount[PM_MSG_HOST_AWAKE]++;
        break;

        /* DOZE״̬�µ�TBTT�¼� */
        case STA_PWR_EVENT_TBTT:
            /* TBTT�¼��л���awake״̬ */
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_AWAKE, us_event);
        break;

        /* �쳣����,fast ps ģʽ�£��е�doze��tbtt�жϻ�δ��������devie���ֶ����� */
        case STA_PWR_EVENT_FORCE_AWAKE:
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_AWAKE, us_event);
        break;

        case STA_PWR_EVENT_P2P_SLEEP:
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_TRUE);
        break;

        case STA_PWR_EVENT_P2P_AWAKE:
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
        break;

        /*�ǽ���ģʽ�£�����doze״̬���쳣���� */
        case STA_PWR_EVENT_NO_POWERSAVE:
            if (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state)
            {
                ul_ret = dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_ACTIVE, OAL_FALSE);
                if (OAL_SUCC != ul_ret)
                {
                    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_power_state_awake_event:dmac_send_null_frame_to_ap:[%d]}", ul_ret);
                }
            }
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_AWAKE, us_event);/* �Ȼ��� */
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_ACTIVE, us_event);/* ����״̬ */
        break;
        case STA_PWR_EVENT_DEASSOCIATE:
            dmac_pm_process_deassociate(pst_pm_handler);
        break;

        case STA_PWR_EVENT_TX_MGMT:
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_AWAKE, us_event);
            pst_pm_handler->aul_pmDebugCount[PM_MSG_TX_MGMT]++;
        break;
        default:
        break;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : sta_power_state_active_entry
 ��������  : awake״̬��entry�ӿ�
 �������  : p_ctx:״̬�������ģ��Խ���״̬����˵Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void sta_power_state_awake_entry(oal_void *p_ctx)
{
    mac_sta_pm_handler_stru*    pst_sta_pm_handler = (mac_sta_pm_handler_stru*)p_ctx;
    dmac_vap_stru               *pst_dmac_vap;
    mac_device_stru             *pst_mac_device;

    if(OAL_PTR_NULL == pst_sta_pm_handler)
    {
        return;
    }

        /* ��Ҫ�ٴ�ȷ��start������ */
#if 0
        g_no_tbtt_link_loss_count = 0;
        g_flowCtrlCnt = 0;
        DFX_FlowCtrlStartTimer();
        if (g_us_PmWifiDeepSleepRfPwrOn)
        {
            /* ��˯�߻��Ѻ��ṩ���������λ���Ľӿں��� */
            psm_start_bcn_check_timer();

            //PM_WifiDebug_Patch(0xF);
            RF_Awake();
            g_us_PmWifiDeepSleepRfPwrOn = 0;
            //PM_WifiDebug_Patch(0);
        }

        /* Power up the PHY */
        power_up_phy();

        /* Enable MAC H/w and PHY */
        enable_machw_phy_and_pa();

        /* Check if STA can transmit now  */
        if((can_sta_transmit_now_prot() == BFALSE) ||
           (is_csw_in_prog() == BFALSE))
        {
            set_ps_state(STA_AWAKE);
            return;
        }

        WIFI_INFO_LOG0(WLOG_ID_PS,"[INFO][PS] {awake}\r\n");

        /* Resume MAC H/w transmission after enabling it */
        set_machw_tx_resume();
#endif
    pst_dmac_vap    = (dmac_vap_stru *)(pst_sta_pm_handler->p_mac_fsm->p_oshandler);

    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_awake_entry::pst_mac_device null}");
        return;
    }

    if (OAL_TRUE == pst_sta_pm_handler->en_hw_ps_enable)
    {
        //PM_WLAN_PRINT("PSM awake entry vote wakeup"NEWLINE);
        #ifdef HI1102_FPGA
            /*˯������ʱ��۲��P12*/
            //WRITEW(0x50002174,READW(0x50002174)|((1<<2)));
        #endif
        dmac_pm_enable_front_end(pst_mac_device);

    	PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_WORK_PROCESS);
        //frw_timer_restart();

	}
}
/*****************************************************************************
 �� �� ��  : sta_power_state_active_exit
 ��������  : active״̬��exit�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void sta_power_state_awake_exit(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_work_event
 ��������  : active״̬��event�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
             us_event:�������¼�
             us_event_data_len:�¼���Я�������ݳ���
             p_event_data:�¼���Я�����¼���Ӧ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 sta_power_state_awake_event(oal_void   *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    oal_uint32                           ul_ret;
    mac_ieee80211_frame_stru            *pst_mac_hdr;
    dmac_vap_stru                       *pst_dmac_vap;

    mac_sta_pm_handler_stru*    pst_pm_handler = (mac_sta_pm_handler_stru*)p_ctx;
    if(OAL_PTR_NULL == pst_pm_handler)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_awake_event::pst_pm_handler null}");
        return OAL_FAIL;
    }

    pst_dmac_vap = (dmac_vap_stru *)(pst_pm_handler->p_mac_fsm->p_oshandler);
    if(OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_awake_event::pst_dmac_vap null}");
        return OAL_FAIL;
    }


    switch(us_event)
    {
        case STA_PWR_EVENT_RX_UCAST:
            ul_ret = dmac_send_pspoll_to_ap(pst_dmac_vap);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_power_state_awake_event::dmac_send_pspoll_to_ap fail [%d].}", ul_ret);
            }

        break;

        /* TIM is set */
        case STA_PWR_EVENT_TIM:
            if (OAL_TRUE == pst_pm_handler->en_more_data_expected)
            {
                ul_ret = dmac_send_pspoll_to_ap(pst_dmac_vap);
                if (OAL_SUCC != ul_ret)
                {
                    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_power_state_awake_event::dmac_send_pspoll_to_ap fail [%d].}", ul_ret);
                }
            }
        break;

        /* DTIM set, stay in AWAKE mode to recieve all broadcast frames */
        case STA_PWR_EVENT_DTIM:
            pst_pm_handler->en_more_data_expected = OAL_TRUE;
            pst_pm_handler->aul_pmDebugCount[PM_MSG_DTIM_AWAKE]++;
        break;

        /* AWAKE״̬�½���null֡���ͳɹ��Ĵ��� */
        case STA_PWR_EVENT_SEND_NULL_SUCCESS:
            pst_mac_hdr = (mac_ieee80211_frame_stru *)(p_event_data);
            dmac_process_send_null_succ_event(pst_pm_handler, pst_mac_hdr);
        break;

       /* ˯���¼� */
       case STA_PWR_EVENT_BEACON_TIMEOUT:
       case STA_PWR_EVENT_NORMAL_SLEEP:
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_DOZE, us_event);
       break;

        /* Awake ״̬���յ����һ���鲥/�㲥 */
        case STA_PWR_EVENT_LAST_MCAST:
            pst_pm_handler->en_more_data_expected   = OAL_FALSE;
            pst_pm_handler->en_ps_deep_sleep        = OAL_TRUE;
            pst_pm_handler->aul_pmDebugCount[PM_MSG_LAST_DTIM_SLEEP]++;
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_DOZE, us_event);
        break;

        /* ��ʱ���������¼� pspollģʽ��,����Ҫ��ʱ��doze,ֱ�ӿ�beacon tim Ԫ�� */
        case STA_PWR_EVENT_TIMEOUT:
            pst_pm_handler->en_ps_deep_sleep        = OAL_TRUE;   /* �л���ǳ˯״̬ */
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_DOZE, us_event);
        break;

        case STA_PWR_EVENT_P2P_SLEEP:
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_TRUE);
        break;

        case STA_PWR_EVENT_P2P_AWAKE:
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
        break;

        /* �ǽ���ģʽ�¼� */
         case STA_PWR_EVENT_NO_POWERSAVE:
            if (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state)
            {
                OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_pm sta_power_state_awake_event::dmac_send_null_frame_to_ap active}");
                ul_ret = dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_ACTIVE, OAL_FALSE);
                if (OAL_SUCC != ul_ret)
                {
                    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_power_state_awake_event:dmac_send_null_frame_to_ap:[%d]}", ul_ret);
                }
            }

            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_ACTIVE, us_event);/* ��״̬ */
        break;
        case STA_PWR_EVENT_DEASSOCIATE:
            dmac_pm_process_deassociate(pst_pm_handler);
        break;
        default:
        break;
    }
    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_pm_sta_doze_state_trans
 ��������  : PM����״̬����״̬�л���doze״̬
 �������  : pst_handler:pm handlerָ��
             uc_state:�л�״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_pm_sta_doze_state_trans(mac_sta_pm_handler_stru* pst_handler, oal_uint16 us_event)
{
    mac_fsm_stru    *pst_fsm = pst_handler->p_mac_fsm;
    dmac_vap_stru    *pst_dmac_vap;
    oal_uint8         uc_doze_trans_flag;

    pst_dmac_vap = (dmac_vap_stru *)(pst_fsm->p_oshandler);
    uc_doze_trans_flag = (pst_handler->en_beacon_frame_wait) | (pst_handler->st_null_wait.en_doze_null_wait << 1) | (pst_handler->en_more_data_expected << 2)
                | (pst_handler->st_null_wait.en_active_null_wait << 3) | (pst_handler->en_send_active_null_frame_to_ap << 4);

    if (us_event != STA_PWR_EVENT_BEACON_TIMEOUT)
    {
        if ((OAL_FALSE == uc_doze_trans_flag) && (OAL_TRUE == dmac_can_sta_doze_prot(pst_dmac_vap)))
        {

            pst_handler->uc_doze_event = (oal_uint8)us_event;
            pst_handler->uc_state_fail_doze_trans_cnt = 0;                      //ʧ��ͳ������
            mac_fsm_trans_to_state(pst_fsm, STA_PWR_SAVE_STATE_DOZE);
        }
        else if (OAL_FALSE != uc_doze_trans_flag)
        {
            pst_handler->uc_state_fail_doze_trans_cnt++;

            /* �쳣,���ǵ�doze null ֡���ɹ�����������ж�,�м�ap��֪�����˶���,staut�޷�˯��ȥ,�����Ѿ�������doze��null֡,�˴���Ҫ��һ��active��null֡*/
            if ((STA_PWR_EVENT_SEND_NULL_SUCCESS == us_event) && (OAL_TRUE == dmac_is_any_legacy_ac_present(pst_dmac_vap)))
            {
                if(OAL_SUCC != dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_ACTIVE, OAL_FALSE))
                {
                    OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "sta_pm dmac_pm_sta_doze_state_trans send active null data fail");
                }

            }

            if (DMAC_STATE_DOZE_TRANS_FAIL_NUM == pst_handler->uc_state_fail_doze_trans_cnt)
            {
                pst_handler->uc_state_fail_doze_trans_cnt = 0;
                OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "sta_pm now event:[%d],but sta_doze_state_change trans flag:[%d]",us_event,uc_doze_trans_flag);
            }
        }
    }
    else
    {
        pst_handler->en_beacon_frame_wait = OAL_FALSE;
        pst_handler->st_null_wait.en_doze_null_wait = OAL_FALSE;
        pst_handler->en_more_data_expected = OAL_FALSE;
        pst_handler->st_null_wait.en_active_null_wait = OAL_FALSE;
        pst_handler->en_send_active_null_frame_to_ap  = OAL_FALSE;

        pst_handler->uc_doze_event = (oal_uint8)us_event;

        mac_fsm_trans_to_state(pst_fsm, STA_PWR_SAVE_STATE_DOZE);
    }
}
/*****************************************************************************
 �� �� ��  : dmac_pm_state_trans
 ��������  : PM����״̬����״̬�л��ӿ�
 �������  : pst_handler:pm handlerָ��
             uc_state:�л�״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_pm_sta_state_trans(mac_sta_pm_handler_stru* pst_handler,oal_uint8 uc_state, oal_uint16 us_event)
{
    mac_fsm_stru    *pst_fsm = pst_handler->p_mac_fsm;
    dmac_vap_stru   *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru*)(pst_fsm->p_oshandler);

    if(uc_state >= STA_PWR_SAVE_STATE_BUTT)
    {
        /* OAM��־�в���ʹ��%s*/
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "dmac_pm_sta_state_trans:invalid state %d",uc_state);
        return;
    }

    /* 1102������״̬ʱ��¼���¼������� */
    switch (uc_state)
    {
        case STA_PWR_SAVE_STATE_ACTIVE:
            pst_handler->uc_active_event = (oal_uint8)us_event;
            if (STA_PWR_SAVE_STATE_ACTIVE != STA_GET_PM_STATE(pst_handler))
            {
                mac_fsm_trans_to_state(pst_fsm, uc_state);
            }
            else
            {
                OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_pm dmac event:[%d]trans state to active in[%d]state}", us_event, STA_GET_PM_STATE(pst_handler));
            }
        break;

        case STA_PWR_SAVE_STATE_AWAKE:
            pst_handler->uc_awake_event = (oal_uint8)us_event;
            if (STA_PWR_SAVE_STATE_AWAKE != STA_GET_PM_STATE(pst_handler))
            {
                mac_fsm_trans_to_state(pst_fsm, uc_state);
            }
            else
            {
                OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_pm dmac event:[%d]trans state to awake in awake}", us_event);
            }
        break;

        /* �����������������л���doze״̬,��������staû������˯��ȥ,״̬ȴ�Ѿ��г�doze,tbtt�ظ����� */
        case STA_PWR_SAVE_STATE_DOZE:
        if (STA_PWR_SAVE_STATE_DOZE != STA_GET_PM_STATE(pst_handler))
        {
            dmac_pm_sta_doze_state_trans(pst_handler, us_event);
        }
        else
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_pm dmac event:[%d]trans state to doze in doze}", us_event);
        }
        break;

        default:
        break;
    }
    return;

}
/*****************************************************************************
 �� �� ��  : dmac_sta_pm_post_event
 ��������  : ����״̬�����¼�����ӿ�,����״̬����״̬�л����¼�������������frw���¼��ַ�����������pm���ڲ��¼�
 �������  : pst_event_mem: frw���¼��ṹָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��17��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_pm_sta_post_event(oal_void* pst_oshandler, oal_uint16 us_type, oal_uint16 us_datalen, oal_uint8* pst_data)
{
    mac_sta_pm_handler_stru     *pst_handler;
    mac_fsm_stru                *pst_fsm;
    oal_uint32                  ul_ret;
    oal_uint8                   uc_pm_state;
    oal_uint8                   uc_event = 0;
    dmac_vap_stru*              pst_dmac_vap = (dmac_vap_stru*)pst_oshandler;

    OAL_REFERENCE(uc_event);

    if(pst_dmac_vap == OAL_PTR_NULL)
    {
        OAM_WARNING_LOG1(0, OAM_SF_PWR, "{dmac_pm_sta_post_event::pst_dmac_vap null.event:[%d]}", us_type);
        return OAL_FAIL;
    }

    pst_handler = (mac_sta_pm_handler_stru *)pst_dmac_vap->pst_pm_handler;
    if(pst_handler == OAL_PTR_NULL)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_post_event::pst_pm_handler null.event:[%d]}", us_type);
        return OAL_FAIL;
    }

    pst_fsm = pst_handler->p_mac_fsm;
    uc_pm_state = STA_GET_PM_STATE(pst_handler);

    /* �ϴ��л���xx״̬���¼� */
    switch (uc_pm_state)
    {
        case STA_PWR_SAVE_STATE_DOZE:
            uc_event = pst_handler->uc_doze_event;
        break;

        case STA_PWR_SAVE_STATE_AWAKE:
            uc_event = pst_handler->uc_awake_event;
        break;

        case STA_PWR_SAVE_STATE_ACTIVE:
            uc_event = pst_handler->uc_active_event;
        break;

        default:
        break;

    }

    /* �������ڵ�״̬�׳����¼�����ʵ����״̬��һ�µĴ���ά���ӡ */
    switch(us_type)
    {
        case STA_PWR_EVENT_TX_DATA:
        case STA_PWR_EVENT_TBTT:
        case STA_PWR_EVENT_FORCE_AWAKE:
            if (STA_PWR_SAVE_STATE_DOZE != uc_pm_state)
            {
                OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_pm dmac_pm_sta_post_event::now event:[%d],but event:[%d]change state to[%d]not doze}",us_type, uc_event, uc_pm_state);
            }
        break;

        case STA_PWR_EVENT_RX_UCAST:
        case STA_PWR_EVENT_LAST_MCAST:
        case STA_PWR_EVENT_TIM:
        case STA_PWR_EVENT_DTIM:
        case STA_PWR_EVENT_NORMAL_SLEEP:
            if (STA_PWR_SAVE_STATE_AWAKE != uc_pm_state)
            {
                OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_pm dmac_pm_sta_post_event::now event:[%d], but event:[%d]change state to[%d]not awake}",us_type, uc_event, uc_pm_state);
            }
        break;

        /* ��ʱ��Ӧ����doze״̬ */
        case STA_PWR_EVENT_SEND_NULL_SUCCESS:
            if (STA_PWR_SAVE_STATE_DOZE == uc_pm_state)
            {
                //OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_post_event::now event:[%d], but event:[%d]change state to[%d]is doze}",us_type, uc_event, uc_pm_state);
                //OAL_IO_PRINT("dmac_pm_sta_post_event::now event:[%d], but event:[%d]change state to[%d]is doze.\r\n", us_type, uc_event, uc_pm_state);
            }
        break;
#if 0
        /* ��ʱӦ����active״̬ ������ӵ͹����лط�ʡ��ģʽ,��ʱ��״̬�Ͳ���ACTIVE */
        case STA_PWR_EVENT_NO_POWERSAVE:
            if (STA_PWR_SAVE_STATE_ACTIVE != uc_pm_state)
            {
                //OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_post_event::now event:[%d], but event:[%d]change state to[%d]not active}",us_type, uc_event, uc_pm_state);
                OAL_IO_PRINT("dmac_pm_sta_post_event::now event:[%d], but event:[%d]change state to[%d]not active", us_type, uc_event, uc_pm_state);
            }
        break;

        case STA_PWR_EVENT_TIMEOUT:
            if (STA_PWR_SAVE_STATE_DOZE == uc_pm_state)
            {
                //OAM_ERROR_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_post_event::now event:[%d],but event:[%d]change state to[%d]is doze}",us_type, uc_event, uc_pm_state);
                //OAL_IO_PRINT("dmac_pm_sta_post_event::now event:[%d],but event:[%d]change state to[%d]is doze",us_type, uc_event, uc_pm_state);
            }
        break;
#endif

        default:
        break;

    }
    ul_ret = mac_fsm_event_dispatch(pst_fsm, us_type, us_datalen, pst_data);

    return ul_ret;

}
/*****************************************************************************
 �� �� ��  : dmac_pm_sta_attach
 ��������  : sta pm ������ʼ��
 �������  : p_fsm:״̬��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��4��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_sta_initialize_psm_globals(mac_sta_pm_handler_stru *p_handler)
{
        p_handler->en_beacon_frame_wait             = OAL_FALSE;
        p_handler->st_null_wait.en_active_null_wait = OAL_FALSE;
        p_handler->st_null_wait.en_doze_null_wait   = OAL_FALSE;
        p_handler->en_more_data_expected            = OAL_FALSE;
        p_handler->en_ps_deep_sleep                 = OAL_FALSE;
        p_handler->en_send_null_delay               = OAL_FALSE;
        p_handler->ul_tx_rx_activity_cnt            = 0;
        p_handler->en_send_active_null_frame_to_ap  = OAL_FALSE;
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
        p_handler->uc_uaspd_sp_status               = DMAC_SP_NOT_IN_PROGRESS;
        p_handler->uc_eosp_timeout_cnt              = 0;
#endif
        p_handler->ul_activity_timeout              = MIN_ACTIVITY_TIME_OUT;
        p_handler->ul_ps_keepalive_cnt              = 0;
        p_handler->ul_ps_keepalive_max_num          = WLAN_PS_KEEPALIVE_MAX_NUM;
        p_handler->uc_timer_fail_doze_trans_cnt           = 0;
        p_handler->uc_state_fail_doze_trans_cnt           = 0;

}

/*****************************************************************************
 �� �� ��  : dmac_pm_sta_attach
 ��������  : sta����VAP����pm handler
 �������  : p_fsm:״̬��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
mac_sta_pm_handler_stru * dmac_pm_sta_attach(oal_void* pst_oshandler)
{
    mac_sta_pm_handler_stru *p_handler  = OAL_PTR_NULL;
    dmac_vap_stru           *p_dmac_vap = (dmac_vap_stru*)pst_oshandler;
    oal_uint8                auc_fsm_name[6] = {0};

    if(OAL_PTR_NULL != p_dmac_vap->pst_pm_handler)
    {
        return p_dmac_vap->pst_pm_handler;
    }

    p_handler = (mac_sta_pm_handler_stru*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_sta_pm_handler_stru), OAL_TRUE);
    if(OAL_PTR_NULL == p_handler)
    {
        OAM_ERROR_LOG0(p_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{hmac_ap_pm_attach:malloc memory for pm handler fail!");
        return OAL_PTR_NULL;
    }

    OAL_MEMZERO(p_handler, OAL_SIZEOF(mac_sta_pm_handler_stru));

    p_handler->en_beacon_frame_wait             = OAL_FALSE;
    p_handler->st_null_wait.en_active_null_wait = OAL_FALSE;
    p_handler->st_null_wait.en_doze_null_wait   = OAL_FALSE;
    p_handler->en_more_data_expected            = OAL_FALSE;
    p_handler->uc_vap_ps_mode                   = NO_POWERSAVE;
    p_handler->en_receive_dtim                  = OAL_FALSE;
    p_handler->en_ps_deep_sleep                 = OAL_FALSE;
    p_handler->en_send_null_delay               = OAL_FALSE;
    p_handler->ul_tx_rx_activity_cnt            = 0;
    p_handler->en_send_active_null_frame_to_ap  = OAL_FALSE;
    p_handler->en_hw_ps_enable                  = OAL_FALSE;    /* �Ƿ����Э��ջ�͹���,����������� */
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    p_handler->uc_uaspd_sp_status               = DMAC_SP_NOT_IN_PROGRESS;
    p_handler->uc_eosp_timeout_cnt              = 0;
#endif
    p_handler->ul_activity_timeout              = MIN_ACTIVITY_TIME_OUT;
    p_handler->ul_ps_keepalive_cnt              = 0;
    p_handler->ul_ps_keepalive_max_num          = WLAN_PS_KEEPALIVE_MAX_NUM;
    p_handler->uc_timer_fail_doze_trans_cnt           = 0;
    p_handler->uc_state_fail_doze_trans_cnt           = 0;

    /* ׼��һ��Ψһ��fsmname */
    auc_fsm_name[0] = (oal_uint8)(p_dmac_vap->st_vap_base_info.ul_core_id);
    auc_fsm_name[1] = p_dmac_vap->st_vap_base_info.uc_chip_id;
    auc_fsm_name[2] = p_dmac_vap->st_vap_base_info.uc_device_id;
    auc_fsm_name[3] = p_dmac_vap->st_vap_base_info.uc_vap_id;
    auc_fsm_name[4] = p_dmac_vap->st_vap_base_info.en_vap_mode;
    auc_fsm_name[5] = 0;

    p_handler->p_mac_fsm = mac_fsm_create((oal_void*)p_dmac_vap,
                                          auc_fsm_name,
                                          p_handler,
                                          STA_PWR_SAVE_STATE_ACTIVE,
                                          g_sta_power_fsm_info,
                                          OAL_SIZEOF(g_sta_power_fsm_info)/OAL_SIZEOF(mac_fsm_state_info)
                                          );
    p_dmac_vap->pst_pm_handler = p_handler;

    return p_dmac_vap->pst_pm_handler;
}

/*****************************************************************************
 �� �� ��  : dmac_pm_sta_deattach
 ��������  : sta����VAP����pm handler
 �������  : p_fsm:״̬��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_pm_sta_detach(oal_void* pst_oshandler)
{
    mac_sta_pm_handler_stru *pst_handler = OAL_PTR_NULL;
    dmac_vap_stru           *pst_dmac_vap = (dmac_vap_stru*)pst_oshandler;

    pst_handler = (mac_sta_pm_handler_stru *)pst_dmac_vap->pst_pm_handler;
    if(OAL_PTR_NULL == pst_handler)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_detach::pst_handler null.}");
        return;
    }

    /* ����active״̬�л���active״̬ */
    if (STA_GET_PM_STATE(pst_handler) != STA_PWR_SAVE_STATE_ACTIVE)
    {
        dmac_pm_sta_state_trans(pst_handler, STA_PWR_SAVE_STATE_AWAKE, STA_PWR_EVENT_DETATCH);
        dmac_pm_sta_state_trans(pst_handler, STA_PWR_SAVE_STATE_ACTIVE, STA_PWR_EVENT_DETATCH);
    }

    if (OAL_TRUE == pst_handler->st_inactive_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_handler->st_inactive_timer));
    }

    if(OAL_PTR_NULL != pst_handler->p_mac_fsm)
    {
        mac_fsm_destroy(pst_handler->p_mac_fsm);
    }

    OAL_MEM_FREE(pst_handler,OAL_TRUE);

    pst_dmac_vap->pst_pm_handler = OAL_PTR_NULL;

    return;

}

#endif /* _PRE_WLAN_FEATURE_STA_PM */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

