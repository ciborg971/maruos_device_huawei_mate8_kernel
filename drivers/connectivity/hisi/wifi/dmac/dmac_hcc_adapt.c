


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "mac_resource.h"
#include "dmac_hcc_adapt.h"
#include "dmac_vap.h"
#include "mac_device.h"
#include "oal_hcc_slave_if.h"
#include "oal_profiling.h"

#include "oal_hcc_slave_if.h"
#include "cali_data.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_HCC_ADAPT_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#define DMAC_HCC_EXTEND_TOTAL_SIZE      (MAX_MAC_HEAD_LEN + OAL_MAX_CB_LEN + (oal_int32)OAL_SIZEOF(struct frw_hcc_extend_hdr))
oal_uint32  g_hcc_sched_event_pkts[FRW_EVENT_TYPE_BUTT]={0};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*debug*/
oal_void dmac_event_pkts_dump(oal_void)
{
    oal_int32 i = 0;
    for(i = 0; i < FRW_EVENT_TYPE_BUTT;i++)
    {
        OAL_IO_PRINT("event:%d,pkts:%d\r\n",i,g_hcc_sched_event_pkts[i]);
    }
}

OAL_STATIC OAL_INLINE struct frw_hcc_extend_hdr* dmac_get_hcc_tx_extend_hdr_addr(oal_netbuf_stru  *pst_netbuf)
{
    struct frw_hcc_extend_hdr* pst_hdr =
                    (struct frw_hcc_extend_hdr*)hcc_get_extend_addr(pst_netbuf,DMAC_HCC_EXTEND_TOTAL_SIZE);
    OAL_BUG_ON(NULL == pst_hdr);
    return pst_hdr;
}

OAL_STATIC OAL_INLINE struct frw_hcc_extend_hdr* dmac_get_hcc_rx_extend_hdr_addr(oal_netbuf_stru  *pst_netbuf)
{
    struct frw_hcc_extend_hdr* pst_hdr =
                    (struct frw_hcc_extend_hdr*)hcc_get_extend_payload_addr(pst_netbuf);
    OAL_BUG_ON(NULL == pst_hdr);
    return pst_hdr;
}

OAL_STATIC OAL_INLINE oal_int32 dmac_hcc_adapt_extend_hdr_init(frw_event_mem_stru *pst_hcc_event_mem,oal_netbuf_stru *pst_netbuf)
{
    struct frw_hcc_extend_hdr* pst_hdr;
    frw_event_hdr_stru   *pst_event_hdr = frw_get_event_hdr(pst_hcc_event_mem);

    pst_hdr = dmac_get_hcc_tx_extend_hdr_addr(pst_netbuf);
    pst_hdr->en_nest_type = pst_event_hdr->en_type;
    pst_hdr->uc_nest_sub_type = pst_event_hdr->uc_sub_type;
    pst_hdr->device_id = pst_event_hdr->uc_device_id;
    pst_hdr->chip_id = pst_event_hdr->uc_chip_id;
    pst_hdr->vap_id = pst_event_hdr->uc_vap_id;
    return OAL_SUCC;
}

oal_void dmac_adapt_tx_param_and_netbuf_hdr_init(frw_event_mem_stru   *pst_event_mem,
                                                   struct hcc_transfer_param* pst_param,
                                                   oal_netbuf_stru  * pst_netbuf)
{
    OAL_BUG_ON(NULL == pst_netbuf);

    dmac_hcc_adapt_extend_hdr_init(pst_event_mem,pst_netbuf);

    hcc_hdr_param_init(pst_param,HCC_ACTION_TYPE_WIFI,0,DMAC_HCC_EXTEND_TOTAL_SIZE);
}
/*lint -e801*/
oal_uint32 dmac_hcc_tx_event_convert_to_netbuf(frw_event_mem_stru   *pst_event_mem,
                                               oal_netbuf_stru      *pst_event_netbuf,
                                               oal_uint32            payload_size)
{
    oal_uint32 ret = OAL_SUCC;
    oal_uint8                      *pst_event_payload;
    oal_netbuf_stru                *pst_netbuf = NULL;
    oal_netbuf_stru                *pst_netbuf_tx;
    struct hcc_transfer_param param;

    /* 参数合法性检查 */
    if (OAL_PTR_NULL == pst_event_mem)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_payload = frw_get_event_payload(pst_event_mem);

    /*If Null, we should alloc netbuf and copy from event to netbuf*/
    if(NULL == pst_event_netbuf)
    {
        frw_event_hdr_stru   *pst_event_hdr = frw_get_event_hdr(pst_event_mem);
        pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, (oal_uint16)payload_size, OAL_TRUE);
        if (OAL_PTR_NULL == pst_netbuf)
        {
            ret = OAL_ERR_CODE_ALLOC_MEM_FAIL;
            OAM_WARNING_LOG3(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac2hmac event to netbuf alloc[%d] failed,main:%d,sub:%d}",
					 payload_size,pst_event_hdr->en_type,pst_event_hdr->uc_sub_type);
            goto failed_alloc_netbuf;
        }

        OAL_MEMZERO(oal_netbuf_cb(pst_netbuf), OAL_TX_CB_LEN);
        oal_memcopy((oal_uint8 *)(OAL_NETBUF_DATA(pst_netbuf)),
                    (oal_uint8 *)pst_event_payload,
                    payload_size);

    }

    if(NULL != pst_event_netbuf)
        pst_netbuf_tx       = pst_event_netbuf;
    else
        pst_netbuf_tx       = pst_netbuf;
#if 1
    dmac_adapt_tx_param_and_netbuf_hdr_init(pst_event_mem,&param,pst_netbuf_tx);
#else
    hcc_hdr_param_init(&param,HCC_ACTION_TYPE_WIFI,0,0);
#endif

    hcc_slave_tx(pst_netbuf_tx, (oal_uint16)payload_size,&param);

    return OAL_SUCC;

failed_alloc_netbuf:
    return ret;
}

oal_uint32 dmac_hcc_tx_netbuf_convert_to_netbuf(frw_event_mem_stru *pst_event_mem,
                                                             oal_netbuf_stru   *pst_event_netbuf,
                                                              oal_uint32 payload_size)
{
    oal_uint32 ret;
    if(NULL != pst_event_netbuf)
    {
        ret = dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem,pst_event_netbuf,payload_size);
    }
    else
    {
        /*assert?*/
        ret = OAL_ERR_CODE_PTR_NULL;
    }

    return ret;
}


frw_event_mem_stru * dmac_hcc_rx_netbuf_convert_to_event(frw_event_mem_stru *pst_hcc_event_mem, oal_uint32 revert_size)
{
    frw_event_hdr_stru             *pst_hcc_event_hdr;
    hcc_event_stru                 *pst_hcc_event_payload;
    oal_netbuf_stru                *pst_hcc_netbuf;
    frw_event_type_enum_uint8       en_type;
    oal_uint8                       uc_sub_type;
    oal_uint8                       uc_chip_id;
    oal_uint8                       uc_device_id;
    oal_uint8                       uc_vap_id;
    frw_event_mem_stru             *pst_event_mem;              /* 业务事件相关信息 */

	if(NULL == pst_hcc_event_mem)
	{
			return NULL;
	}

    /* 提取HCC事件信息 */
    pst_hcc_event_hdr       = frw_get_event_hdr(pst_hcc_event_mem);
    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    pst_hcc_netbuf          = pst_hcc_event_payload->pst_netbuf;
    en_type                 = pst_hcc_event_hdr->en_type;
    uc_sub_type             = pst_hcc_event_hdr->uc_sub_type;
    uc_chip_id              = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id            = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id               = pst_hcc_event_hdr->uc_vap_id;

    /* 申请业务事件 */
    pst_event_mem = FRW_EVENT_ALLOC((oal_uint16)revert_size);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        /* 释放hcc事件中申请的netbuf内存 */
        OAL_MEM_NETBUF_FREE(pst_hcc_netbuf);
        return OAL_PTR_NULL;
    }

    /* 填业务事件头*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       en_type,
                       uc_sub_type,
                       (oal_uint16)revert_size,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       uc_chip_id,
                       uc_device_id,
                       uc_vap_id);
    if(revert_size)
        oal_memcopy((oal_uint8 *)frw_get_event_payload(pst_event_mem),
                (oal_uint8 *)OAL_NETBUF_HCC_PAYLOAD(pst_hcc_netbuf), revert_size);

    /* 释放hcc事件中申请的netbuf内存 */
    OAL_MEM_NETBUF_FREE(pst_hcc_netbuf);

    /* 2015.08.12 START 用于同步事件打印，确认接收是否丢事件 */
    if(HMAC_TO_DMAC_SYN_CFG == uc_sub_type)
    {
        hmac_to_dmac_cfg_msg_stru  *pst_syn_msg = (hmac_to_dmac_cfg_msg_stru *)frw_get_event_payload(pst_event_mem);
        OAM_WARNING_LOG3(uc_vap_id, OAM_SF_ANY, "{dmac_hcc_rx_netbuf_convert_to_event::device recv event from host:type[%d],subtype[%d],cfgid[%d]}",
                       en_type, uc_sub_type, pst_syn_msg->en_syn_id);
    }
    /* 2015.08.12 END*/

    return pst_event_mem;
}
/*lint +e801*/


oal_uint32 dmac_proc_common_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,OAL_SIZEOF(oal_uint16));
}

/*****************************************************************************
 函 数 名  : dmac_proc_event_del_ba_tx_adapt
 功能描述  : DMAC_TO_HMAC_DEL_BA事件发送适配(dmac发送delba)
 输入参数  : pst_event_mem: 事件内存指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月28日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_proc_event_del_ba_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                    OAL_SIZEOF(dmac_to_hmac_ctx_event_stru));
}
/*****************************************************************************
 函 数 名  : dmac_alg_syn_info_adapt
 功能描述  : DMAC_TO_HMAC_ALG_INFO_SYN事件发送适配(dmac通知hmac协议模式改变)
 输入参数  : pst_event_mem: 事件内存指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : j0019683
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_syn_info_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                    OAL_SIZEOF(dmac_to_hmac_syn_info_event_stru));
}


/*lint -e413*/
oal_uint32 dmac_proc_event_config_syn_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                  *pst_event;
    dmac_to_hmac_cfg_msg_stru       *pst_syn_cfg_payload;
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_syn_cfg_payload    = (dmac_to_hmac_cfg_msg_stru *)pst_event->auc_event_data;
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                                        pst_syn_cfg_payload->us_len + (oal_uint32)OAL_OFFSET_OF(hmac_to_dmac_cfg_msg_stru,auc_msg_body));
}
/*lint +e413*/

#ifdef _PRE_WLAN_CHIP_TEST_ALG
/*****************************************************************************
 函 数 名  : dmac_alg_test_result_tx_adapt
 功能描述  : 算法芯片测试结果上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月8日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_ct_result_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                  *pst_event;
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL, pst_event->auc_event_data[0] + 1);

}
#endif

oal_uint32 dmac_proc_init_event_process_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                  *pst_event;
    dmac_tx_event_stru              *pst_ctx_event;
    pst_event   = (frw_event_stru *)pst_event_mem->puc_data;
    pst_ctx_event = (dmac_tx_event_stru *)pst_event->auc_event_data;

    //OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_proc_init_event_process_tx_adapt.}");
    return  dmac_hcc_tx_netbuf_convert_to_netbuf(pst_event_mem,pst_ctx_event->pst_netbuf,
                                       pst_ctx_event->us_frame_len);
}



oal_uint32 dmac_proc_wlan_drx_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_hdr_stru              *pst_event_hdr;
    oal_uint32                       ul_payload_len;

    dmac_wlan_drx_event_stru        *pst_wlan_rx;

    oal_netbuf_stru                 *pst_tmp_netbuf = NULL;
    oal_netbuf_stru                 *pst_curr_netbuf;

    oal_uint16                       us_loop;
    oal_uint16                       us_netbuf_num;

    mac_rx_ctl_stru                 *pst_rx_cb;

    OAL_STATIC oal_uint8             uc_mac_header_len = MAX_MAC_HEAD_LEN;
    OAL_STATIC oal_uint8             uc_mac_header[MAX_MAC_HEAD_LEN];

    pst_event_hdr           = frw_get_event_hdr(pst_event_mem);

    pst_wlan_rx             = (dmac_wlan_drx_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_curr_netbuf         = pst_wlan_rx->pst_netbuf;
    us_netbuf_num           = pst_wlan_rx->us_netbuf_num;

    for (us_loop = 0; us_loop < us_netbuf_num; us_loop++)
    {
        struct hcc_transfer_param param;
        if(NULL == pst_curr_netbuf)
        {
            /*netbuf list num < list head's num?*/
            OAM_ERROR_LOG3(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac had post %d netbufs,but list num is:%d,miss %d}",
                                                                us_loop, us_netbuf_num, us_netbuf_num - us_loop);
            break;
        }

        /* for amsdu adapt */
        pst_rx_cb = (mac_rx_ctl_stru *)oal_netbuf_cb(pst_curr_netbuf);
        if(OAL_TRUE == pst_rx_cb->bit_amsdu_enable)
        {
            if ((pst_rx_cb->bit_buff_nums > 1) && (OAL_TRUE == pst_rx_cb->bit_is_first_buffer))
            {
                uc_mac_header_len = pst_rx_cb->bit_mac_header_len;
                oal_memcopy(uc_mac_header, oal_netbuf_header(pst_curr_netbuf), uc_mac_header_len);
            }
            if (OAL_FALSE == pst_rx_cb->bit_is_first_buffer)
            {
                pst_rx_cb->bit_mac_header_len = uc_mac_header_len;
                pst_rx_cb->uc_mac_vap_id = pst_event_hdr->uc_vap_id;
                oal_memcopy(oal_netbuf_header(pst_curr_netbuf), uc_mac_header, uc_mac_header_len);
            }
            pst_rx_cb->us_frame_len = 0;
            //ul_payload_len = WLAN_LARGE_NETBUF_SIZE; //因为没有单buffer长度(描述符里是总长度) SDIO发送最大长度
            pst_rx_cb->bit_buff_nums = 1;//host netbuf不成链 单buffer处理
        }

        if (pst_rx_cb->us_frame_len)
        {
            ul_payload_len = pst_rx_cb->us_frame_len - pst_rx_cb->bit_mac_header_len;//接收描述符中的payload len
            if(ul_payload_len > WLAN_LARGE_NETBUF_SIZE)
            {
                OAM_ERROR_LOG3(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac invalid len:%d,frame:%d,mac hdr:%d}",
                                                                ul_payload_len,
                                                                pst_rx_cb->us_frame_len,
                                                                pst_rx_cb->bit_mac_header_len);
                ul_payload_len = WLAN_LARGE_NETBUF_SIZE;
            }
        }
        else
        {
            ul_payload_len = WLAN_LARGE_NETBUF_SIZE;
        }

        pst_tmp_netbuf = pst_curr_netbuf;

		/* 指向netbuf链表的下一个netbuf */
        pst_curr_netbuf = pst_curr_netbuf->next;

        dmac_adapt_tx_param_and_netbuf_hdr_init(pst_event_mem,&param,pst_tmp_netbuf);
    	hcc_slave_tx(pst_tmp_netbuf, (oal_uint16)ul_payload_len, &param);
    }

    if(us_loop != us_netbuf_num)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac wlan drx mem leak,still reamin %d netbufs}",
                                                        us_netbuf_num - us_loop);
    }

    return OAL_SUCC;

}
oal_uint32 dmac_proc_tkip_mic_fail_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem,NULL, OAL_SIZEOF(dmac_to_hmac_mic_event_stru));
}



oal_uint32 dmac_proc_tbtt_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_proc_common_tx_adapt(pst_event_mem);
}

oal_uint32 dmac_dfs_radar_detect_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_proc_common_tx_adapt(pst_event_mem);
}




oal_uint32 dmac_proc_crx_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                  *pst_event;
    dmac_wlan_crx_event_stru              *pst_ctx_event;
    mac_rx_ctl_stru    *pst_rx_cb;

    pst_event   = (frw_event_stru *)pst_event_mem->puc_data;
    pst_ctx_event = (dmac_wlan_crx_event_stru *)pst_event->auc_event_data;

	if(NULL == pst_ctx_event->pst_netbuf)
	{
		OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_proc_crx_event_tx_adapt::netbuf = OAL_PTR_NULL!}");
		return OAL_ERR_CODE_PTR_NULL;
	}

    pst_rx_cb = (mac_rx_ctl_stru *)oal_netbuf_cb(pst_ctx_event->pst_netbuf);
    return dmac_hcc_tx_netbuf_convert_to_netbuf(pst_event_mem,pst_ctx_event->pst_netbuf,
                                       pst_rx_cb->us_frame_len);
}



oal_uint32 dmac_scan_report_scanned_bss_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    oal_uint16 payload_len;
    frw_event_stru                 *pst_event;                /* 用于提取业务事件的信息 */
    dmac_tx_event_stru             *pst_ctx_event;
	if(NULL == pst_event_mem)
	{
		return OAL_ERR_CODE_PTR_NULL;
	}
    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_ctx_event = (dmac_tx_event_stru *)pst_event->auc_event_data;

    payload_len = (pst_ctx_event->us_frame_len > MAC_80211_FRAME_LEN)?
                    (pst_ctx_event->us_frame_len - MAC_80211_FRAME_LEN)
                    :MAC_80211_FRAME_LEN;

    return dmac_hcc_tx_netbuf_convert_to_netbuf(pst_event_mem,pst_ctx_event->pst_netbuf,
                                         payload_len);
}

#ifdef _PRE_WLAN_RF_110X_CALI_DPD

oal_uint32 dmac_dpd_data_cali_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                 *pst_event;
    dmac_tx_event_stru             *pst_ctx_event;

    if(NULL == pst_event_mem)
    {
       OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_cali_tx_adapt::pst_event_mem null.}");

       return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "dmac_dpd_data_cali_tx_adapt\n\r");

    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_ctx_event = (dmac_tx_event_stru *)pst_event->auc_event_data;

    return dmac_hcc_tx_netbuf_convert_to_netbuf(pst_event_mem,pst_ctx_event->pst_netbuf,
                                         pst_ctx_event->us_frame_len);
}

#endif
oal_uint32  dmac_proc_mgmt_rx_delba_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                                        OAL_SIZEOF(dmac_ctx_action_event_stru));
}


oal_uint32  dmac_rx_send_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                                               OAL_SIZEOF(dmac_diasoc_deauth_event));
}



oal_uint32  dmac_hcc_test_event_rxsub_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    hcc_event_stru                  *pst_test_event_payload;
    pst_test_event_payload = (hcc_event_stru  *)frw_get_event_payload(pst_event_mem);
    return dmac_hcc_tx_netbuf_convert_to_netbuf(
                            pst_event_mem,
                            pst_test_event_payload->pst_netbuf,
                            pst_test_event_payload->ul_buf_len);
}

/*****************************************************************************
 函 数 名  : dmac_switch_to_new_chan_complete_tx_adapt
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : s00304087
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_switch_to_new_chan_complete_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                     OAL_SIZEOF(dmac_set_chan_stru));
}

/*****************************************************************************
 函 数 名  : dmac_dbac_status_notify_tx_adapt
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月8日
    作    者   : l00311403
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_dbac_status_notify_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                     OAL_SIZEOF(oal_bool_enum_uint8));
}


oal_uint32 dmac_scan_proc_scan_comp_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                                               OAL_SIZEOF(mac_scan_rsp_stru));
}

#ifdef _PRE_WLAN_FEATURE_FLOWCTL

oal_uint32  dmac_alg_flowctl_backp_tx_adapt(frw_event_mem_stru * pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                    OAL_SIZEOF(mac_ioctl_queue_backp_stru));
}

#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST

oal_uint32 dmac_scan_proc_obss_scan_comp_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL,
                                               OAL_SIZEOF(dmac_obss_te_a_b_stru));
}
#endif


oal_uint32 dmac_proc_chan_result_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    dmac_crx_chan_result_stru    *pst_event_payload;
    oal_netbuf_stru              *pst_scan_comp_netbuf;

    struct hcc_transfer_param param;

    /* 参数合法性检查 */
    if (OAL_PTR_NULL == pst_event_mem)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 提取信道统计测量结果上报业务事件的结构体信息 */
    pst_event_payload = (dmac_crx_chan_result_stru *)frw_get_event_payload(pst_event_mem);;

    /* 申请netbuf，存放扫描事件结构体中携带的扫描参数信息 */
    pst_scan_comp_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MGMT_NETBUF_SIZE, OAL_TRUE);
    if (OAL_PTR_NULL == pst_scan_comp_netbuf)
    {
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* 将扫描参数的结构体信息拷贝到netbuff数据区 */
    OAL_MEMZERO(oal_netbuf_cb(pst_scan_comp_netbuf), OAL_TX_CB_LEN);
    oal_memcopy((oal_uint8 *)(OAL_NETBUF_DATA(pst_scan_comp_netbuf)),
                (oal_uint8 *)pst_event_payload,
                OAL_SIZEOF(dmac_crx_chan_result_stru));

    dmac_adapt_tx_param_and_netbuf_hdr_init(pst_event_mem,&param,pst_scan_comp_netbuf);
    hcc_slave_tx(pst_scan_comp_netbuf, OAL_SIZEOF(dmac_crx_chan_result_stru),&param);

    return OAL_SUCC;
}


frw_event_mem_stru* dmac_tx_process_data_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    hcc_event_stru                  *pst_hcc_event_payload;
    frw_event_hdr_stru              *pst_hcc_event_hdr;

    oal_uint8                        uc_chip_id;
    oal_uint8                        uc_device_id;
    oal_uint8                        uc_vap_id;

    frw_event_mem_stru              *pst_event_mem;
    dmac_tx_event_stru              *pst_dmac_tx_event_payload;
    mac_tx_ctl_stru                 *pst_tx_ctl;

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_ADAPT_START);

     /*step1 取HCC事件头*/
    pst_hcc_event_hdr       = frw_get_event_hdr(pst_hcc_event_mem);

    uc_chip_id              = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id            = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id               = pst_hcc_event_hdr->uc_vap_id;

    /*step2 取HCC事件信息*/
    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);

    /*step3 申请业务事件*/
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
       OAL_MEM_NETBUF_FREE(pst_hcc_event_payload->pst_netbuf);
       return OAL_PTR_NULL;
    }

    /*step4 填业务事件头*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                   pst_hcc_event_hdr->en_type,
                   pst_hcc_event_hdr->uc_sub_type,
                   OAL_SIZEOF(dmac_tx_event_stru),
                   FRW_EVENT_PIPELINE_STAGE_1,
                   uc_chip_id,
                   uc_device_id,
                   uc_vap_id);

    /*step5 填业务事件信息*/
    pst_dmac_tx_event_payload               = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_dmac_tx_event_payload->pst_netbuf   = pst_hcc_event_payload->pst_netbuf;
    pst_dmac_tx_event_payload->us_frame_len = (oal_uint16) pst_hcc_event_payload->ul_buf_len;

    /* pad不为0时才进行数据搬移 */
    if (OAL_UNLIKELY(0 != ((struct hcc_header *)OAL_NETBUF_HCCHDR(pst_dmac_tx_event_payload->pst_netbuf))->pad_payload))
    {
        oal_memmove((oal_uint8 *)OAL_NETBUF_DATA(pst_dmac_tx_event_payload->pst_netbuf),
                    (oal_uint8 *)OAL_NETBUF_HCC_PAYLOAD(pst_dmac_tx_event_payload->pst_netbuf),
                    pst_dmac_tx_event_payload->us_frame_len);
    }

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_dmac_tx_event_payload->pst_netbuf);
    MAC_GET_CB_MPDU_LEN(pst_tx_ctl) = pst_dmac_tx_event_payload->us_frame_len;

    pst_dmac_tx_event_payload->us_frame_len += MAC_80211_FRAME_LEN;

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_ADAPT_END);

    return pst_event_mem;

}



frw_event_mem_stru* dmac_user_add_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_ctx_add_user_stru));
}



frw_event_mem_stru* dmac_user_del_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_ctx_add_user_stru));
}



frw_event_mem_stru* dmac_event_config_syn_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    frw_event_stru                  *pst_hcc_event;
    hcc_event_stru                  *pst_hcc_event_payload;
    pst_hcc_event           = (frw_event_stru *)pst_hcc_event_mem->puc_data;
    pst_hcc_event_payload   = (hcc_event_stru *)pst_hcc_event->auc_event_data;
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,pst_hcc_event_payload->ul_buf_len);
}




frw_event_mem_stru* dmac_mgmt_tx_event_process_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    return dmac_tx_process_data_event_rx_adapt(pst_hcc_event_mem);
}


frw_event_mem_stru* dmac_tx_process_action_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    return dmac_tx_process_data_event_rx_adapt(pst_hcc_event_mem);
}



frw_event_mem_stru* dmac_mgmt_wmm_update_edca_machw_sta_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_ctx_sta_asoc_set_edca_reg_stru));
}


frw_event_mem_stru* dmac_scan_proc_scan_req_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    frw_event_hdr_stru         *pst_hcc_event_hdr;
    hcc_event_stru             *pst_hcc_event_payload;
    oal_netbuf_stru            *pst_scan_req_netbuf;
    frw_event_type_enum_uint8   en_type;
    oal_uint8                   uc_sub_type;
    oal_uint8                   uc_chip_id;
    oal_uint8                   uc_device_id;
    oal_uint8                   uc_vap_id;
    frw_event_mem_stru         *pst_event_mem;              /* 业务事件相关信息 */
    mac_scan_req_stru          *pst_h2d_scan_req_params;    /* 扫描请求参数 */

    /* 参数合法性检查 */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hcc_event_mem))
    {
        return OAL_PTR_NULL;
    }

    //OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_scan_proc_scan_req_event_rx_adapt:: scan req, enter into rx adapt.}");

    /* 提取HCC事件信息 */
    pst_hcc_event_payload = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);
    pst_scan_req_netbuf   = pst_hcc_event_payload->pst_netbuf;
    pst_hcc_event_hdr     = frw_get_event_hdr(pst_hcc_event_mem);
    en_type               = pst_hcc_event_hdr->en_type;
    uc_sub_type           = pst_hcc_event_hdr->uc_sub_type;
    uc_chip_id            = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id          = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id             = pst_hcc_event_hdr->uc_vap_id;

    /* 申请业务事件 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_scan_req_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
       OAL_MEM_NETBUF_FREE(pst_scan_req_netbuf);
       return OAL_PTR_NULL;
    }

    /* 填业务事件头*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       en_type,
                       uc_sub_type,
                       OAL_SIZEOF(mac_scan_req_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       uc_chip_id,
                       uc_device_id,
                       uc_vap_id);

    /* 将扫描参数内容拷贝到事件内存data区域 */
    pst_h2d_scan_req_params = (mac_scan_req_stru *)frw_get_event_payload(pst_event_mem);
    oal_memcopy(pst_h2d_scan_req_params, OAL_NETBUF_HCC_PAYLOAD(pst_scan_req_netbuf), OAL_SIZEOF(mac_scan_req_stru));

    /* 释放hcc事件申请的netbuf内存 */
    OAL_MEM_NETBUF_FREE(pst_scan_req_netbuf);

    /*输出业务事件给后面实际函数调用*/
    return pst_event_mem;
}

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
frw_event_mem_stru*   dmac_dpd_data_processed_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
   frw_event_hdr_stru         *pst_hcc_event_hdr;
   oal_netbuf_stru            *pst_dpd_data_netbuf;
   frw_event_mem_stru         *pst_event_mem;
   dmac_tx_event_stru         *pst_dmac_tx_event;


   if (OAL_PTR_NULL == pst_hcc_event_mem)
   {
       //OAM_INFO_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_event_rx_adapt:: pst_hcc_event_mem null.}");
       return OAL_PTR_NULL;
   }

   OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_event_rx_adapt:: dpd enter into rx adapt.}");

   pst_dpd_data_netbuf   = ((hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem))->pst_netbuf;
   pst_hcc_event_hdr     = frw_get_event_hdr(pst_hcc_event_mem);

   pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
   if (OAL_PTR_NULL == pst_event_mem)
   {
      OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_event_rx_adapt:: pst_event_mem null.}");
      OAL_MEM_NETBUF_FREE(pst_dpd_data_netbuf);
      return OAL_PTR_NULL;
   }

   FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       pst_hcc_event_hdr->en_type,
                       pst_hcc_event_hdr->uc_sub_type,
                       OAL_SIZEOF(dpd_cali_data_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hcc_event_hdr->uc_chip_id,
                       pst_hcc_event_hdr->uc_device_id,
                       pst_hcc_event_hdr->uc_vap_id);


   pst_dmac_tx_event = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);
   pst_dmac_tx_event->pst_netbuf = pst_dpd_data_netbuf;
   pst_dmac_tx_event->us_frame_len = OAL_SIZEOF(dpd_cali_data_stru);

   return pst_event_mem;
}
#endif

frw_event_mem_stru*   dmac_cali_hmac2dmac_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
   frw_event_hdr_stru         *pst_hcc_event_hdr;
   oal_netbuf_stru            *pst_dpd_data_netbuf;
   frw_event_mem_stru         *pst_event_mem;
   dmac_tx_event_stru         *pst_dmac_tx_event;


   if (OAL_PTR_NULL == pst_hcc_event_mem)
   {
       //OAM_INFO_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_event_rx_adapt:: pst_hcc_event_mem null.}");
       return OAL_PTR_NULL;
   }
   //OAL_IO_PRINT("dmac_cali_hmac2dmac_rx_adapt: start\r\n");
   //OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_event_rx_adapt:: dpd enter into rx adapt.}");

   pst_dpd_data_netbuf   = ((hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem))->pst_netbuf;
   pst_hcc_event_hdr     = frw_get_event_hdr(pst_hcc_event_mem);

   pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
   if (OAL_PTR_NULL == pst_event_mem)
   {
      OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_event_rx_adapt:: pst_event_mem null.}");
      OAL_MEM_NETBUF_FREE(pst_dpd_data_netbuf);
      return OAL_PTR_NULL;
   }

   FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       pst_hcc_event_hdr->en_type,
                       pst_hcc_event_hdr->uc_sub_type,
                       OAL_WIFI_CALI_DATA_LEN,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hcc_event_hdr->uc_chip_id,
                       pst_hcc_event_hdr->uc_device_id,
                       pst_hcc_event_hdr->uc_vap_id);


   pst_dmac_tx_event = (dmac_tx_event_stru *)frw_get_event_payload(pst_event_mem);
   pst_dmac_tx_event->pst_netbuf = pst_dpd_data_netbuf;
   pst_dmac_tx_event->us_frame_len = OAL_WIFI_CALI_DATA_LEN;

   return pst_event_mem;
}
frw_event_mem_stru* dmac_scan_proc_sched_scan_req_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    frw_event_hdr_stru         *pst_hcc_event_hdr;
    hcc_event_stru             *pst_hcc_event_payload;
    frw_event_mem_stru         *pst_event_mem;              /* 业务事件相关信息 */
    oal_netbuf_stru            *pst_pno_scan_req_netbuf;
    mac_device_stru            *pst_mac_device;
    frw_event_type_enum_uint8   en_type;
    oal_uint8                   uc_sub_type;
    oal_uint8                   uc_chip_id;
    oal_uint8                   uc_device_id;
    oal_uint8                   uc_vap_id;

    /* 提取HCC事件信息 */
    pst_hcc_event_payload = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);
    pst_pno_scan_req_netbuf   = pst_hcc_event_payload->pst_netbuf;
    pst_hcc_event_hdr     = frw_get_event_hdr(pst_hcc_event_mem);
    en_type               = pst_hcc_event_hdr->en_type;
    uc_sub_type           = pst_hcc_event_hdr->uc_sub_type;
    uc_chip_id            = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id          = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id             = pst_hcc_event_hdr->uc_vap_id;

    /* 获取mac device */
    pst_mac_device = mac_res_get_dev(uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_scan_proc_sched_scan_req_event_rx_adapt::pst_mac_device is null.}");
        OAL_MEM_NETBUF_FREE(pst_pno_scan_req_netbuf);
        return OAL_PTR_NULL;
    }

    /* 申请业务事件 */
    pst_event_mem = FRW_EVENT_ALLOC(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_scan_proc_sched_scan_req_event_rx_adapt::alloc event mem failed.}");
        OAL_MEM_NETBUF_FREE(pst_pno_scan_req_netbuf);
        return OAL_PTR_NULL;
    }

    /* 填业务事件头*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       en_type,
                       uc_sub_type,
                       0,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       uc_chip_id,
                       uc_device_id,
                       uc_vap_id);

    /* 申请用于管理PNO调度扫描的内存，动态申请，节省内存 */
    pst_mac_device->pst_pno_sched_scan_mgmt = (mac_pno_sched_scan_mgmt_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_pno_sched_scan_mgmt_stru), OAL_FALSE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device->pst_pno_sched_scan_mgmt))
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_scan_proc_sched_scan_req_event_rx_adapt::alloc pno sched scan mem failed.}");
        OAL_MEM_NETBUF_FREE(pst_pno_scan_req_netbuf);
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_PTR_NULL;
    }

    /* 将PNO调度扫描请求参数直接拷贝到device结构体下，避免netbuf传来传去 */
    oal_memcopy(&(pst_mac_device->pst_pno_sched_scan_mgmt->st_pno_sched_scan_params),
                OAL_NETBUF_HCC_PAYLOAD(pst_pno_scan_req_netbuf), OAL_SIZEOF(mac_pno_scan_stru));

#if 0
    /* 打印PNO调度扫描参数 */
    OAM_WARNING_LOG2(0, OAM_SF_SCAN,
                     "{dmac_scan_proc_sched_scan_req_event_rx_adapt::PNO sched scan params is ssid_count[%d], rssi_thold[%d].}",
                     pst_mac_device->pst_pno_sched_scan_mgmt->st_pno_sched_scan_params.l_ssid_count,
                     pst_mac_device->pst_pno_sched_scan_mgmt->st_pno_sched_scan_params.l_rssi_thold);
    OAM_WARNING_LOG2(0, OAM_SF_SCAN,
                     "{dmac_scan_proc_sched_scan_req_event_rx_adapt::interval[%d], repeat_times[%d].}",
                     pst_mac_device->pst_pno_sched_scan_mgmt->st_pno_sched_scan_params.ul_pno_scan_interval,
                     pst_mac_device->pst_pno_sched_scan_mgmt->st_pno_sched_scan_params.uc_pno_scan_repeat);
#endif

    /* 释放hcc事件申请的netbuf内存 */
    OAL_MEM_NETBUF_FREE(pst_pno_scan_req_netbuf);

    /*输出业务事件给后面实际函数调用*/
    return pst_event_mem;
}


frw_event_mem_stru* dmac_asoc_set_reg_event_process_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_ctx_asoc_set_reg_stru));
}



frw_event_mem_stru* dmac_join_set_dtim_reg_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_ctx_set_dtim_tsf_reg_stru));
}


frw_event_mem_stru* dmac_mgmt_conn_result_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem, OAL_SIZEOF(oal_uint32));
}


frw_event_mem_stru* dmac_join_set_reg_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_ctx_join_req_set_reg_stru));
}


frw_event_mem_stru* dmac_set_rx_filter_value_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,OAL_SIZEOF(oal_uint32));
}

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
/*****************************************************************************
 函 数 名  : dmac_psm_opmode_notify_process_rx_adapt
 功能描述  : 通过SDIO从hmac到dmac下发帧过滤信息
             dmac接收侧，需要将hcc事件内容具体转换为具体业务事件
 输入参数  : frw_event_mem_stru *pst_hcc_event_mem，原先的hcc事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月13日
    作    者   : l00311403
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru* dmac_psm_opmode_notify_process_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem, OAL_SIZEOF(oal_uint16));
}
#endif


frw_event_mem_stru* dmac_user_add_notify_alg_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem, OAL_SIZEOF(dmac_ctx_add_user_stru));
}


frw_event_mem_stru* dmac_hcc_test_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    frw_event_hdr_stru             *pst_hcc_event_hdr;
    hcc_event_stru                 *pst_hcc_event_payload;
    oal_netbuf_stru                *pst_hcc_netbuf;
    frw_event_type_enum_uint8       en_type;
    oal_uint8                       uc_sub_type;
    oal_uint8                       uc_chip_id;
    oal_uint8                       uc_device_id;
    oal_uint8                       uc_vap_id;
    frw_event_mem_stru             *pst_event_mem;              /* 业务事件相关信息 */

	if(NULL == pst_hcc_event_mem)
	{
			return NULL;
	}

    /* 提取HCC事件信息 */
    pst_hcc_event_hdr       = frw_get_event_hdr(pst_hcc_event_mem);
    pst_hcc_event_payload   = (hcc_event_stru *)frw_get_event_payload(pst_hcc_event_mem);
    pst_hcc_netbuf          = pst_hcc_event_payload->pst_netbuf;
    en_type                 = pst_hcc_event_hdr->en_type;
    uc_sub_type             = pst_hcc_event_hdr->uc_sub_type;
    uc_chip_id              = pst_hcc_event_hdr->uc_chip_id;
    uc_device_id            = pst_hcc_event_hdr->uc_device_id;
    uc_vap_id               = pst_hcc_event_hdr->uc_vap_id;

    /* 申请业务事件 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hcc_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        /* 释放hcc事件中申请的netbuf内存 */
        OAL_MEM_NETBUF_FREE(pst_hcc_netbuf);
        return OAL_PTR_NULL;
    }

    /* 填业务事件头*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
                       en_type,
                       uc_sub_type,
                       (oal_uint16)OAL_SIZEOF(hcc_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       uc_chip_id,
                       uc_device_id,
                       uc_vap_id);

    /*copy the event payload*/
    oal_memcopy((oal_void*)frw_get_event_payload(pst_event_mem),
                (oal_void*)frw_get_event_payload(pst_hcc_event_mem),
                OAL_SIZEOF(hcc_event_stru));

    return pst_event_mem;
}

frw_event_mem_stru* dmac_commom_process_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,0);
}

frw_event_mem_stru* dmac_init_event_process_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_commom_process_rx_adapt(pst_hcc_event_mem);
}


frw_event_mem_stru* dmac_rx_process_sync_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_ctx_action_event_stru));
}

/*****************************************************************************
 函 数 名  : dmac_chan_select_channel_mac_rx_adapt
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : s00304087
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru *dmac_chan_select_channel_mac_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_set_chan_stru));
}

/*****************************************************************************
 函 数 名  : dmac_chan_select_channel_mac_rx_adapt
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : s00304087
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru *dmac_chan_initiate_switch_to_new_channel_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,OAL_SIZEOF(dmac_set_ch_switch_info_stru));
}

/*****************************************************************************
 函 数 名  : dmac_chan_restart_network_after_switch_rx_adapt
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : s00304087
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru *dmac_chan_restart_network_after_switch_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_commom_process_rx_adapt(pst_hcc_event_mem);
}

/*****************************************************************************
 函 数 名  : dmac_chan_disable_machw_rx_adapt
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : s00304087
    修改内容   : 新生成函数

*****************************************************************************/
frw_event_mem_stru *dmac_chan_disable_machw_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_commom_process_rx_adapt(pst_hcc_event_mem);
}

frw_event_mem_stru* dmac_init_event_create_cfg_vap_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_commom_process_rx_adapt(pst_hcc_event_mem);
}
frw_event_mem_stru* dmac_psm_reset_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem,OAL_SIZEOF(oal_uint16));
}

/*****************************************************************************
 函 数 名  : dmac_proc_disasoc_misc_event_tx_adapt
 功能描述  : dmac适配hcc事件，dmac上报每次去关联事件发送适配接口
 输入参数  : frw_event_mem_stru *pst_event_mem，原先的业务事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月19日
    作    者   : l00311403
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_proc_disasoc_misc_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL, OAL_SIZEOF(dmac_disasoc_misc_stru));
}

#ifdef _PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
 函 数 名  : dmac_proc_roam_trigger_event_tx_adapt
 功能描述  : dmac适配hcc事件，dmac上报每次去关联事件发送适配接口
 输入参数  : frw_event_mem_stru *pst_event_mem，原先的业务事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月19日
    作    者   : l00311403
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_proc_roam_trigger_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    return dmac_hcc_tx_event_convert_to_netbuf(pst_event_mem, NULL, OAL_SIZEOF(oal_int8));
}
#endif //_PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
 函 数 名  : dmac_proc_disasoc_misc_event_tx_adapt
 功能描述  : dmac适配hcc事件，dmac上报每次去关联事件发送适配接口
 输入参数  : frw_event_mem_stru *pst_event_mem，原先的业务事件类型
 输出参数  : 无
 返 回 值  : OAL_SUCC， 发送前适配成功
             其他，     失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月19日
    作    者   : l00311403
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_cali2hmac_misc_event_tx_adapt(frw_event_mem_stru *pst_event_mem)
{
    oal_netbuf_stru                 *pst_tmp_netbuf = NULL;
    oal_netbuf_stru                 *pst_curr_netbuf;

    oal_uint16                       us_loop;
    oal_uint16                       us_netbuf_num;
    oal_uint16                       us_remained_netbuf_num;
    hal_cali_hal2hmac_event_stru   *pst_cali_tx_event;      /* wlan rx事件 */

    pst_cali_tx_event             = (hal_cali_hal2hmac_event_stru *)frw_get_event_payload(pst_event_mem);
    pst_curr_netbuf         = pst_cali_tx_event->pst_netbuf;
    us_netbuf_num           = pst_cali_tx_event->us_netbuf_num;
    us_remained_netbuf_num  = us_netbuf_num;
    //OAL_IO_PRINT("dmac_cali2hmac_misc_event_tx_adapt start\r\n");

    for (us_loop = 0; (us_loop < us_netbuf_num) && (us_remained_netbuf_num > 0); us_loop++)
    {
        struct hcc_transfer_param param;
        if(NULL == pst_curr_netbuf)
        {
            /*netbuf list num < list head's num?*/
            OAL_IO_PRINT("[ERROR]had post %d netbufs,but list num is:%d,miss %d\r\n",
                                    us_loop,us_netbuf_num,us_netbuf_num - us_loop);
            break;
        }

        pst_tmp_netbuf = pst_curr_netbuf;

		/* 指向netbuf链表的下一个netbuf */
        pst_curr_netbuf = pst_curr_netbuf->next;
        us_remained_netbuf_num--;
        //OAL_IO_PRINT("dmac_cali2hmac_misc_event_tx_adapt loop:%d\r\n",us_loop);
        dmac_adapt_tx_param_and_netbuf_hdr_init(pst_event_mem,&param,pst_tmp_netbuf);

        hcc_slave_tx(pst_tmp_netbuf, (oal_uint16)WLAN_LARGE_NETBUF_SIZE, &param);
    }

    if(0 != us_remained_netbuf_num)
    {
        OAL_IO_PRINT("[WARN]wlan drx mem leak,still reamin %d netbufs\r\n",us_remained_netbuf_num);
    }

    return OAL_SUCC;

}

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
frw_event_mem_stru* dmac_edca_opt_stat_event_rx_adapt(frw_event_mem_stru *pst_hcc_event_mem)
{
    return dmac_hcc_rx_netbuf_convert_to_event(pst_hcc_event_mem, OAL_SIZEOF(oal_uint8) * 16);
}

#endif

oal_int32 dmac_rx_extend_hdr_vaild_check(struct frw_hcc_extend_hdr* pst_extend_hdr)
{
    if(OAL_UNLIKELY(pst_extend_hdr->en_nest_type >= FRW_EVENT_TYPE_BUTT))
    {
        return OAL_FALSE;
    }
#if 0
    if(OAL_UNLIKELY(pst_extend_hdr->vap_id > WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        return OAL_FALSE;
    }
#endif
    return OAL_TRUE;
}

oal_int32 dmac_rx_wifi_post_action_function(oal_uint8 stype,
                                             hcc_netbuf_stru* pst_hcc_netbuf, oal_uint8 *pst_context)
{
    oal_int32 ret;
    frw_event_mem_stru  *pst_event_mem = (frw_event_mem_stru *)pst_context;

    OAL_BUG_ON(NULL == pst_event_mem);

    ret = (oal_int32)frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);
    return ret;
}

oal_int32 dmac_rx_wifi_pre_action_function(oal_uint8 stype, hcc_netbuf_stru* pst_hcc_netbuf,
                                                  oal_uint8  **pre_do_context)
{
    /*预先申请事件内存，如果事件内存申请失败，netbuf继续停留在HCC队列中，
      防止frw event 竞争在HCC上丢包*/
    frw_event_mem_stru    *pst_event_mem;
    hcc_event_stru        *pst_hcc_event_payload;
    struct frw_hcc_extend_hdr* pst_hdr;

	pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hcc_event_stru));
    if (NULL == pst_event_mem)
    {
        /*alloc failed,keep the netbuf in the rx queue!*/
        return -OAL_ENOMEM;
    }

    pst_hdr = dmac_get_hcc_rx_extend_hdr_addr(pst_hcc_netbuf->pst_netbuf);
    pst_hcc_event_payload = (hcc_event_stru *)frw_get_event_payload(pst_event_mem);

    //OAL_IO_PRINT("pst_hdr->en_nest_type:%u,pst_hdr->uc_nest_sub_type:%u\r\n",pst_hdr->en_nest_type,pst_hdr->uc_nest_sub_type);
    /*填写事件头*/
    FRW_EVENT_HDR_INIT(frw_get_event_hdr(pst_event_mem),
    				  pst_hdr->en_nest_type,
                      pst_hdr->uc_nest_sub_type,
                      OAL_SIZEOF(hcc_event_stru),
                      FRW_EVENT_PIPELINE_STAGE_1,
                      pst_hdr->chip_id,
                      pst_hdr->device_id,
                      pst_hdr->vap_id);

    g_hcc_sched_event_pkts[pst_hdr->en_nest_type]++;

    pst_hcc_event_payload->pst_netbuf = pst_hcc_netbuf->pst_netbuf;
    pst_hcc_event_payload->ul_buf_len = (oal_uint32)pst_hcc_netbuf->len;

    *pre_do_context = (oal_uint8*)pst_event_mem;
    return OAL_SUCC;
}

oal_int32 dmac_hcc_adapt_init(oal_void)
{
    OAL_MEMZERO(g_hcc_sched_event_pkts, OAL_SIZEOF(g_hcc_sched_event_pkts));
    return hcc_rx_register(hcc_get_default_handler(), HCC_ACTION_TYPE_WIFI,
                        dmac_rx_wifi_post_action_function, dmac_rx_wifi_pre_action_function);
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

