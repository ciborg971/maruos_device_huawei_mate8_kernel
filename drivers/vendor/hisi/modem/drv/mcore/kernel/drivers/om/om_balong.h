

#ifndef _OM_BALONG_H
#define _OM_BALONG_H

#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************
  ͷ�ļ�����
**************************************************************************/
#include "osl_common.h"
#include "bsp_om.h"

/* return error code */
#define BSP_ERR_LOG_BASE                (int)(0x80000000 | (BSP_DEF_ERR(BSP_MODU_LOG, 0)))
#define BSP_ERR_LOG_INVALID_MODULE      (BSP_ERR_LOG_BASE + 0x1)
#define BSP_ERR_LOG_INVALID_LEVEL       (BSP_ERR_LOG_BASE + 0x2)
#define BSP_ERR_LOG_INVALID_PARAM       (BSP_ERR_LOG_BASE + 0x3)
#define BSP_ERR_LOG_NO_BUF              (BSP_ERR_LOG_BASE + 0x4)
#define BSP_ERR_LOG_SOCP_ERR            (BSP_ERR_LOG_BASE + 0x5)

/* print buffer length */
#define BSP_PRINT_BUF_LEN  	(128)
#define BSP_PRINT_DATA_LEN  (64)
#define BSP_OM_TIMESTAMP_LEN   	(2)

/* ind max length */
#define BSP_IND_DATA_MAX_LEN (128)

/* connect state */
#define  BSP_LOG_SEND_TO_SHELL 	(0)
#define  BSP_LOG_SEND_TO_HSO    (1)
#define  BSP_LOG_SEND_TO_FILE   (2)

#define  BSP_LOG_HSO_PAD   		(1)

#define  BSP_HISI_HEAD          (0x48495349)

#define  BSP_PRINT_STR_ID       (0)

#ifdef K3V3_LPM3_HAS_MODEM_FEATURE

#define M3_SYSCTRL_TOTAL_LENGTH             (4096)
#define CRG_SRSTSTAT1_AP_BASE_ADDR	        (HI_LP_PERI_CRG_REG_ADDR + 0x98)

#define CRG_STAT_MODEM_RST_MASK             ((s32)(1 << 28))

#endif


/* packet struct */
typedef struct
{
    u32                hso_connect_flag;
    union
    {
        u32 uin_nv_cfg;
        struct
        {
            u32 log_switch     : 2;  /* 00:��ӡ�����ڣ�01:��ӡ��HSO��10:��ӡ���ļ���11:Ԥ�� */
            u32 reserved1      : 30;
        } nv_cfg;
    } om_cfg;
    u32                 print_sn;
    u32                 trace_cnt;
} bsp_om_global_s;

typedef struct
{
    u32 hisiHead;
	u32 length;
} bsp_hisi_head_s;


typedef struct
{
    /*���������ֽڵ����ͳ��Service ID */
    u8      service_id;
    u8      s_service_id;
    u8      service_session_id;
    u8      msg_type;
    u32     msg_trans_id;
    u32     time_stamp[BSP_OM_TIMESTAMP_LEN];
} bsp_socp_head_s;

typedef struct
{
    u32     om_id;        /* �ṹ��ID*/
    u32     data_size;    /* �����ucData�ĳ���*/
    u8      data[0];      /* �������*/
} bsp_om_head_s;

typedef struct
{
    u32     mod_id;     /* ��ӡ��Ϣ���ڵ�ģ��ID*/
    u32     level;      /* �������*/
    u32     log_sn;     /* IND���*/
    char    text[0];    /* ���д�ӡ�ı����ݣ����ܰ����ļ����к�,��'\0'��β */
} bsp_trace_txt_s;

typedef struct
{
    bsp_hisi_head_s  	hisi_head_str;
	bsp_socp_head_s  	socp_head_str;
	bsp_om_head_s    	om_head_str;
	char                data[0];
} bsp_om_gbl_s;


/* print  level */
typedef struct
{
    u32 print_level;
} bsp_log_swt_cfg_s;


typedef void (*om_xputc)(void *rb, unsigned n, void *cookie);

/*****************************************************************************
  2 ��������
*****************************************************************************/
#ifdef ENABLE_BUILD_OM
void om_switch_set(u32 ulSwitch);
void om_log_init(void);
#else
static void inline om_switch_set(u32 ulSwitch)
{
    return;
}
static void inline om_log_init(void)
{
    return;
}
#endif
u32 om_get_hso_connect_flag(void);

#ifdef K3V3_LPM3_HAS_MODEM_FEATURE
void om_m3_dump_save();
#endif

#ifdef __cplusplus
}
#endif

#endif

