/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : wal_linux_ioctl.h
  �� �� ��   : ����
  ��    ��   : zhangheng
  ��������   : 2012��12��10��
  ����޸�   :
  ��������   : wal_linux_ioctl.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��12��10��
    ��    ��   : zhangheng
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __WAL_LINUX_IOCTL_H__
#define __WAL_LINUX_IOCTL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "wlan_types.h"
#include "wlan_spec.h"
#include "mac_vap.h"
#include "hmac_ext_if.h"
#include "wal_ext_if.h"
#include "wal_config.h"
#include "dmac_alg_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_IOCTL_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define WAL_HIPRIV_CMD_MAX_LEN       (WLAN_MEM_LOCAL_SIZE2 - 4)     /* ˽�����������ַ�����󳤶ȣ���Ӧ�����ڴ��һ����С */

#define WAL_HIPRIV_CMD_NAME_MAX_LEN  80                             /* �ַ�����ÿ�����ʵ���󳤶�(ԭ20) */

#define WAL_HIPRIV_PROC_ENTRY_NAME   "hipriv"

#define WAL_SIOCDEVPRIVATE              0x89F0  /* SIOCDEVPRIVATE */

#define WAL_HIPRIV_HT_MCS_MIN           0
#define WAL_HIPRIV_HT_MCS_MAX           32
#define WAL_HIPRIV_VHT_MCS_MIN          0
#define WAL_HIPRIV_VHT_MCS_MAX          9
#define WAL_HIPRIV_NSS_MIN              1
#define WAL_HIPRIV_NSS_MAX              4
#define WAL_HIPRIV_CH_NUM               4

#define WAL_HIPRIV_BOOL_NIM             0
#define WAL_HIPRIV_BOOL_MAX             1
#define WAL_HIPRIV_FREQ_SKEW_ARG_NUM    8

#define WAL_HIPRIV_MS_TO_S                   1000   /* ms��s֮�䱶���� */
#define WAL_HIPRIV_KEEPALIVE_INTERVAL_MIN    5000   /* ��Ĭ���ϻ�����������ʱ�������� */
#define WAL_HIPRIV_KEEPALIVE_INTERVAL_MAX    0xffff /* timer���ʱ����������(oal_uin16) */


/* IOCTL˽����������궨�� */
#define WAL_IOCTL_PRIV_SETPARAM          (OAL_SIOCIWFIRSTPRIV + 0)
#define WAL_IOCTL_PRIV_GETPARAM          (OAL_SIOCIWFIRSTPRIV + 1)
#define WAL_IOCTL_PRIV_SET_WMM_PARAM     (OAL_SIOCIWFIRSTPRIV + 3)
#define WAL_IOCTL_PRIV_GET_WMM_PARAM     (OAL_SIOCIWFIRSTPRIV + 5)
#define WAL_IOCTL_PRIV_SET_COUNTRY       (OAL_SIOCIWFIRSTPRIV + 8)
#define WAL_IOCTL_PRIV_GET_COUNTRY       (OAL_SIOCIWFIRSTPRIV + 9)

#define WAL_IOCTL_PRIV_GET_MODE     (OAL_SIOCIWFIRSTPRIV + 17)      /* ��ȡģʽ */
#define WAL_IOCTL_PRIV_SET_MODE     (OAL_SIOCIWFIRSTPRIV + 18)      /* ����ģʽ ����Э�� Ƶ�� ���� */

#define WAL_IOCTL_PRIV_AP_GET_STA_LIST               (OAL_SIOCIWFIRSTPRIV + 21)
#define WAL_IOCTL_PRIV_AP_MAC_FLTR	                 (OAL_SIOCIWFIRSTPRIV + 22)
/* netd��������������ΪGET��ʽ�·���get��ʽ������������set��ż�� */
#define WAL_IOCTL_PRIV_SET_AP_CFG                    (OAL_SIOCIWFIRSTPRIV + 23)
#define WAL_IOCTL_PRIV_AP_STA_DISASSOC		         (OAL_SIOCIWFIRSTPRIV + 24)
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
/*atcmdsrv˽������궨��*/
#define WAL_ATCMDSRV_IOCTL_DBB_LEN               12
#define WAL_ATCMDSRV_IOCTL_VERIFY_CODE           1102
#define WAL_ATCMDSRV_IOCTL_MODE_NUM              11
#define WAL_ATCMDSRV_IOCTL_DATARATE_NUM          12
#define WAL_ATCMDSRB_IOCTL_AL_TX_LEN             2000
#define WAL_ATCMDSRB_DBB_NUM_TIME                (5 * OAL_TIME_HZ)
#define WAL_ATCMDSRB_CHECK_FEM_PA                (5 * OAL_TIME_HZ)
#define WAL_ATCMDSRV_GET_HEX_CHAR(tmp) (((tmp) > 9)? ((tmp-10) + 'A') : ((tmp) + '0'))

#endif

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
#define WAL_IOCTL_PRIV_GET_BLACKLIST        (OAL_SIOCIWFIRSTPRIV + 27)
#define WAL_IOCTL_PRIV_SET_ISOLATION        (OAL_SIOCIWFIRSTPRIV + 28)
#endif
#define WAL_IOCTL_PRIV_SUBCMD_MAX_LEN          20
typedef oal_uint32  (*wal_hipriv_cmd_func)(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

typedef enum
{
    WAL_DSCR_PARAM_FREQ_BANDWIDTH_MODE = 0,      /* Ƶ��ģʽ */
    WAL_DSCR_PARAM_PA_GAIN_LEVEL,      /* pa����ȼ� */
    WAL_DSCR_PARAM_MICRO_TX_POWER_GAIN_LEVEL,
    WAL_DSCR_PARAM_SMART_ANTENNA_ENABLE,
    WAL_DSCR_PARAM_TXRTS_ANTENNA,
    WAL_DSCR_PARAM_RXCTRL_ANTENNA,
    WAL_DSCR_PARAM_CHANNAL_CODE,
    WAL_DSCR_PARAM_DATA_RATE0,
    WAL_DSCR_PARAM_DATA_RATE1,
    WAL_DSCR_PARAM_DATA_RATE2,
    WAL_DSCR_PARAM_DATA_RATE3,
    WAL_DSCR_PARAM_POWER,
    WAL_DSCR_PARAM_SHORTGI,
    WAL_DSCR_PARAM_PREAMBLE_MODE,
    WAL_DSCR_PARAM_RTSCTS,
    WAL_DSCR_PARAM_LSIGTXOP,
    WAL_DSCR_PARAM_SMOOTH,
    WAL_DSCR_PARAM_SOUNDING,
    WAL_DSCR_PARAM_TXBF,
    WAL_DSCR_PARAM_STBC,
    WAL_DSCR_PARAM_GET_ESS,
    WAL_DSCR_PARAM_DYN_BW,
    WAL_DSCR_PARAM_DYN_BW_EXIST,
    WAL_DSCR_PARAM_CH_BW_EXIST,

    WAL_DSCR_PARAM_BUTT
}wal_dscr_param_enum;
typedef oal_uint8 wal_dscr_param_enum_uint8;
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
/*atcmdsrvö������*/
enum WAL_ATCMDSRV_IOCTL_CMD
{
    WAL_ATCMDSRV_IOCTL_CMD_WI_FREQ_SET=0,              /*  */
    WAL_ATCMDSRV_IOCTL_CMD_WI_POWER_SET,               /*  */
    WAL_ATCMDSRV_IOCTL_CMD_MODE_SET,                   /*  */
    WAL_ATCMDSRV_IOCTL_CMD_DATARATE_SET,
    WAL_ATCMDSRV_IOCTL_CMD_BAND_SET,
    WAL_ATCMDSRV_IOCTL_CMD_ALWAYS_TX_SET,
    WAL_ATCMDSRV_IOCTL_CMD_DBB_GET,
    WAL_ATCMDSRV_IOCTL_CMD_FEM_PA_STATUS_GET,

    HWIFI_IOCTL_CMD_TEST_BUTT


};
#endif

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern oal_iw_handler_def_stru g_st_iw_handler_def;
extern oal_net_device_ops_stru g_st_wal_net_dev_ops;

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/* ˽��������ڽṹ���� */
typedef struct
{
    oal_int8           *pc_cmd_name;    /* �����ַ��� */
    wal_hipriv_cmd_func p_func;         /* �����Ӧ������ */
}wal_hipriv_cmd_entry_stru;

/* Э��ģʽ���ַ���ӳ�� */
typedef struct
{
    oal_int8                           *pc_name;        /* ģʽ���ַ��� */
    wlan_protocol_enum_uint8            en_mode;        /* Э��ģʽ */
    wlan_channel_band_enum_uint8        en_band;        /* Ƶ�� */
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;   /* ���� */
    oal_uint8                           auc_resv[1];
}wal_ioctl_mode_map_stru;

/* �㷨�������ýṹ�� */
typedef struct
{
    oal_int8                           *pc_name;        /* ���������ַ��� */
    mac_alg_cfg_enum_uint8              en_alg_cfg;     /* ���������Ӧ��ö��ֵ */
    oal_uint8                           auc_resv[3];    /* �ֽڶ��� */
}wal_ioctl_alg_cfg_stru;

/* 1102 ʹ��wpa_supplicant �·����� */
typedef struct wal_android_wifi_priv_cmd {
    oal_int32    l_total_len;
    oal_int32    l_used_len;
    oal_uint8   *puc_buf;
}wal_android_wifi_priv_cmd_stru;
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
/* 1102 ʹ��atcmdsrv �·����� */
typedef struct wal_atcmdsrv_wifi_priv_cmd {
    /* У��λ,ȡֵ1102,������ƽ̨������ */
    oal_int32 l_verify;
    oal_int32   ul_cmd;                                          /* ����� */
    union
    {
    oal_int32 l_freq;
    oal_int32 l_pow;
    oal_int32 l_mode;
    oal_int32 l_datarate;
    oal_int32 l_bandwidth;
    oal_int32 l_awalys_tx;
    oal_int32 l_fem_pa_status;
    oal_int8  auc_dbb[WAL_ATCMDSRV_IOCTL_DBB_LEN];

    }pri_data;

}wal_atcmdsrv_wifi_priv_cmd_stru;
#endif

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_uint32  wal_hipriv_create_proc(oal_void *p_proc_arg);
extern oal_int32   wal_netdev_stop(oal_net_device_stru *pst_net_dev);
extern oal_int32   wal_netdev_open(oal_net_device_stru *pst_net_dev);
extern oal_uint32  wal_hipriv_del_vap(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32  wal_hipriv_remove_proc(oal_void);
extern oal_uint32  wal_alloc_cfg_event(oal_net_device_stru *pst_net_dev,frw_event_mem_stru **ppst_event_mem,
                 hmac_vap_cfg_priv_stru **ppst_cfg_priv, wal_msg_stru  **ppst_cfg_msg, oal_uint16 us_len);
extern oal_int32   wal_send_cfg_event(
                                   oal_net_device_stru      *pst_net_dev,
                                   wal_msg_type_enum_uint8   en_msg_type,
                                   oal_uint16                us_len,
                                   oal_uint8                *puc_param,
                                   oal_bool_enum_uint8       en_need_rsp,
                                   wal_msg_stru            **ppst_rsp_msg);

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST)
extern oal_int32 wal_start_vap(oal_net_device_stru *pst_net_dev);
extern oal_int32  wal_stop_vap(oal_net_device_stru *pst_net_dev);
extern oal_int32 wal_init_wlan_vap(oal_net_device_stru *pst_net_dev);
extern oal_int32 wal_deinit_wlan_vap(oal_net_device_stru *pst_net_dev);
extern oal_int32 wal_init_wlan_netdev(oal_wiphy_stru *pst_wiphy, char *dev_name);
#endif

#ifdef _PRE_WLAN_FEATURE_11D
extern oal_uint32  wal_regdomain_update_sta(oal_uint8 uc_vap_id);
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_int32  wal_set_random_mac_to_mib(oal_net_device_stru *pst_net_dev);
#endif

wlan_p2p_mode_enum_uint8 wal_wireless_iftype_to_mac_p2p_mode(enum nl80211_iftype en_iftype);

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
extern oal_uint32 wal_hipriv_arp_offload_enable(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
oal_uint32 wal_hipriv_show_arpoffload_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
extern oal_uint32 wal_hipriv_roam_enable(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32 wal_hipriv_roam_band(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32 wal_hipriv_roam_org(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32 wal_hipriv_roam_start(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
extern oal_uint32 wal_hipriv_roam_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param);
#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of wal_linux_ioctl.h */

