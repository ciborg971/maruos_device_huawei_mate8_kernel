

#ifndef __MEDIA_MNTN_KERNEL_H__
#define __MEDIA_MNTN_KERNEL_H__


/******************************************************************************
  1 ����ͷ�ļ�����
******************************************************************************/

#include "media_mntn_kernel_om_interface.h"
//#include "../../../../../../include/med/media_mntn_kernel_om_interface.h"

/******************************************************************************
  2 �궨��
******************************************************************************/

/* �������� TAG */
#define EXCH_CB_NAME_SIZE       (28)

/* DRV_EXCH_CUST_FUNC_REG�ķ���ֵEXCH_OK��ʾ��ȷ������ֵ���Ǵ���ֵ */
#define EXCH_OK         (0)
#define EXCH_ERROR      (-1)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum mntn_bool_enum {
    MNTN_OK     = 0,
    MNTN_ERR    = 1
};

enum mntn_trace_msg_attrib_enum {
    MNTN_TRACE_MSG_NO = 0,
    MNTN_TRACE_MSG_YES,
    MNTN_TRACE_MSG_ATTRIB_MAX
};
typedef unsigned char   mntn_trace_msg_attrib_enum_u8;

/* module_id */
enum mntn_module_id_enum {
    /* VIDEO_FUNCTION_TYPE */
    MNTN_MODULE_ID_DEC  = 0,
    MNTN_MODULE_ID_ENC,
    MNTN_MODULE_ID_VPP,
    MNTN_MODULE_ID_CAMERA,

    /* DISP_FUNCTION_TYPE */
    MNTN_MODULE_ID_EDC,
    MNTN_MODULE_ID_GPU,
    MNTN_MODULE_ID_HDMI,

    /* MNTN */
    MNTN_MODULE_ID_MNTN,

    MNTN_MODULE_ID_MAX = MNTN_MODULE_ID_MNTN
};
typedef unsigned char   mntn_module_id_enum_u8;


/******************************************************************************
  4 ȫ�ֱ�������
******************************************************************************/

extern unsigned int            g_mntn_print_level[MNTN_MODULE_ID_MAX + 1];

/******************************************************************************
 * log
 ******************************************************************************/
#define mntn_loge(module_id, fmt, ...) {    \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_ERR)) { \
        printk(KERN_ALERT "[" LOG_TAG "]" "ERR func: %s, line: %d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__);  \
    }   \
}

#define mntn_logw(module_id, fmt, ...) {    \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_WARNING)) { \
        printk(KERN_ALERT "[" LOG_TAG "]" "WARRING func: %s, line: %d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__);  \
    }   \
}

#define mntn_logi(module_id, fmt, ...) { \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_INFO)) {\
        printk(KERN_ALERT "[" LOG_TAG "]" "INFO func: %s, line: %d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__); \
    }   \
}

#define mntn_logd(module_id, fmt, ...) { \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_DEBUG)) {\
        printk(KERN_ALERT "[" LOG_TAG "]" "DEBUG func: %s, line: %d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__);\
    }   \
}

/******************************************************************************
 * log with timestamp
 ******************************************************************************/
#define mntn_loge_time(module_id, fmt, ...) {   \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_ERR)) { \
        struct timeval tv;      \
        do_gettimeofday(&tv);   \
        printk(KERN_ALERT "[" LOG_TAG "]" " ERR **** TIME: (%ld.%6ld) **** func: %s, line: %d, " fmt "\n", tv.tv_sec, tv.tv_usec, __func__, __LINE__, ##__VA_ARGS__);   \
    }   \
}

#define mntn_logw_time(module_id, fmt, ...) {   \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_WARNING)) { \
        struct timeval tv;      \
        do_gettimeofday(&tv);   \
        printk(KERN_ALERT "[" LOG_TAG "]" " WARRING **** TIME: (%ld.%6ld) **** func: %s, line: %d, " fmt "\n", tv.tv_sec, tv.tv_usec, __func__, __LINE__, ##__VA_ARGS__);   \
    }   \
}

#define mntn_logi_time(module_id, fmt, ...) { \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_INFO)) {    \
        struct timeval tv;      \
        do_gettimeofday(&tv);   \
        printk(KERN_ALERT "[" LOG_TAG "]" " INFO **** TIME: (%ld.%6ld) **** func: %s, line: %d, " fmt "\n", tv.tv_sec, tv.tv_usec, __func__, __LINE__, ##__VA_ARGS__);  \
    }   \
}

#define mntn_logd_time(module_id, fmt, ...) { \
    if (((unsigned int)module_id <= MNTN_MODULE_ID_MAX) && (g_mntn_print_level[module_id] >= MNTN_LOG_LEVEL_DEBUG)) {   \
        struct timeval tv;      \
        do_gettimeofday(&tv);   \
        printk(KERN_ALERT "[" LOG_TAG "]" " DEBUG **** TIME: (%ld.%6ld) **** func: %s, line: %d, " fmt "\n", tv.tv_sec, tv.tv_usec, __func__, __LINE__, ##__VA_ARGS__); \
    }   \
}

/******************************************************************************
  5 ��Ϣͷ����
******************************************************************************/


/******************************************************************************
  6 ��Ϣ����
******************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/******************************************************************************
�ṹ��    : om_api_func_t
�ṹ˵��  : ��ά�ɲ�ģ����Ҫ�õ���OM��API��������
*******************************************************************************/
typedef struct {
    om_reg_request_func om_reg_request;   /* OM API: OM_AcpuRegisterReqProc */
    om_add_sn_time_func om_add_sn_time;   /* OM API: OM_AddSNTime*/
}om_api_func_t;

/******************************************************************************
�ṹ��    : mntn_config_data
�ṹ˵��  : OM����mntnģ��ľ����������ݣ���Ӧmntn_trace_req_t�е�data��
*******************************************************************************/
typedef struct {
    unsigned char   event;              /* �¼����� */
    unsigned char   reg;                /* �Ĵ������� */
    unsigned char   frame_info;         /* ֡��Ϣ���� */
    unsigned char   context;            /* ���������� */
    unsigned char   print_level;        /* ��ӡ���� */
    unsigned char   rsv_0;              /* reserve���� */
    unsigned char   rsv_1;              /* reserve���� */
    unsigned char   rsv_2;              /* reserve���� */
}mntn_config_data_t;

/******************************************************************************
�ṹ��    : mntn_trace_req_t
�ṹ˵��  : OM����mntnģ���������Ϣ����ӦMNTN_PRIM_ID_xxx_CFG_REQ��Ϣ
*******************************************************************************/
typedef struct {
    unsigned char   func_type;          /* IT2's module ID */
    unsigned char   cpu_id;             /* filled with 1 (ACPU) */
    unsigned short  length;             /* msg length after 'length' domain */
    unsigned short  prim_id;            /* message ID */
    unsigned short  rsv_0;              /* reserved */
    unsigned char   data[4];            /* message content, ��OM�˶ԣ���Ҫ8�ֽڣ���Ӧ�ṹ����mntn_config_data */
}mntn_trace_req_t;

/******************************************************************************
�ṹ��    : mntn_trace_cnf_t
�ṹ˵��  : mntnģ�鷢��OM������ȷ����Ϣ����ӦMNTN_PRIM_ID_xxx_CFG_CNF��Ϣ
*******************************************************************************/
typedef struct {
    unsigned char   func_type;          /* IT2's module ID */
    unsigned char   cpu_id;             /* filled with 1 (ACPU) */
    unsigned short  length;             /* msg length after 'length' domain */
    unsigned int    sn;                 /* msg number of ACPU */
    unsigned int    timestamp;          /* timestamp got from board */
    unsigned short  prim_id;            /* message ID */
    unsigned short  module_id;          /* reserved --> module_id */
    unsigned int    result;             /* message content */
}mntn_trace_cnf_t;

/******************************************************************************
�ṹ��    : mntn_trace_ind_t
�ṹ˵��  : mntnģ����Ϣ�ϱ������͵�OM����ӦMNTN_PRIM_ID_xxx_xxx_IND��Ϣ
*******************************************************************************/
typedef struct {
    unsigned char   func_type;          /* IT2's module ID */
    unsigned char   cpu_id;             /* filled with 1 (ACPU) */
    unsigned short  length;             /* msg length after 'length' domain */
    unsigned int    sn;                 /* msg number of ACPU */
    unsigned int    timestamp;          /* timestamp got from board */
    unsigned short  prim_id;            /* message ID */
    unsigned short  module_id;          /* reserved --> module id */
    unsigned char   data[4];            /* message content */
}mntn_trace_ind_t;

/******************************************************************************
�ṹ��    : mntn_trace_simple_config_t
�ṹ˵��  : ĳһ����Ϣ������(�Ƿ��ϱ���Ϣ��OM)
*******************************************************************************/
typedef struct {
    mntn_trace_msg_attrib_enum_u8       config;
    unsigned char                       rsv[3];              /* reserved */
}mntn_trace_simple_config_t;

/******************************************************************************
�ṹ��    : mntn_trace_config_t
�ṹ˵��  : ĳһ����ģ���и�����Ϣ�����ã���VDEC��VENC��VPP��CAMERA��
*******************************************************************************/
typedef struct
{
    mntn_trace_simple_config_t event_cfg;      /* �Ƿ��ϱ��¼� */
    mntn_trace_simple_config_t reg_cfg;        /* �Ƿ��ϱ��Ĵ��� */
    mntn_trace_simple_config_t frame_info_cfg; /* �Ƿ��ϱ�֡��Ϣ */
    mntn_trace_simple_config_t context_cfg;    /* �Ƿ��ϱ���������Ϣ */
}mntn_trace_config_t;

/******************************************************************************
�ṹ��    : mntn_reg_cfg_t
�ṹ˵��  : ��ȡ��Щ�Ĵ���������
*******************************************************************************/
typedef struct {
    unsigned int     module_id;
    unsigned long    addr_base;
    unsigned long    addr_offset;
} mntn_reg_cfg_t;

/******************************************************************************
�ṹ��    : mntn_simple_reg_data_t
�ṹ˵��  : �����Ĵ��������ݽṹ
*******************************************************************************/
typedef struct {
    unsigned long    addr;
    unsigned int     data;
} mntn_reg_data_t;

/******************************************************************************
�ṹ��    : mntn_reg_data_t
�ṹ˵��  : �ϱ��Ĵ��������ݽṹ���˽ṹ��������漰ASN1����
*******************************************************************************/
typedef struct {
    unsigned int        data_len;
    void               *reg_data;/* ��Ӧ�ṹ����mntn_reg_data_t */
} mntn_reg_info_t;

/******************************************************************************
�ṹ��    : mntn_exch_cust_buf_t
�ṹ˵��  : �������Իص��������������
*******************************************************************************/
typedef struct {
    char            name[EXCH_CB_NAME_SIZE];    /* ģ���־���Զ�����ַ��� */
    unsigned char  *data;                       /* �����������ݴ�ŵ�buffer��ģ���Լ����� */
    unsigned int    data_len;                   /* buffer�ĳ��ȣ�С��8K */
} mntn_exch_cust_buf_t;

/******************************************************************************
�ṹ��    : mntn_exch_cb
�ṹ˵��  : �������Իص���������
*******************************************************************************/
// 2012-11-24
typedef int (*mntn_exch_cb) (mntn_exch_cust_buf_t *);


/******************************************************************************
  8 UNION����
******************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : mntn_send_event_msg
 ��������  : MNTN�ϱ��¼���Ϣ�Ľӿڷ�װ
 �������  : ulModuleId    - ģ��ID��Ŀǰ����DEC/ENC/VPP/CAMERA����Ӧö��mntn_module_id_t
             buffer        - ���������ݴ�ŵ�buffer
             length        - buffer�ĳ��ȣ�С��4K
 �������  : NONE
 �� �� ֵ  : void
*****************************************************************************/
void mntn_send_event_msg(unsigned short prim_id, mntn_module_id_enum_u8 module_id,
    unsigned char *buffer, unsigned short length);

/*****************************************************************************
 �� �� ��  : mntn_send_reg_msg
 ��������  : MNTN�ϱ��Ĵ�����Ϣ�Ľӿڷ�װ
 �������  : ulModuleId    - ģ��ID��Ŀǰ����DEC/ENC/VPP/CAMERA����Ӧö��mntn_module_id_t
             buffer        - ���������ݴ�ŵ�buffer
             length        - buffer�ĳ��ȣ�С��4K
 �������  : NONE
 �� �� ֵ  : void
*****************************************************************************/
void mntn_send_reg_msg(unsigned short prim_id, mntn_module_id_enum_u8 module_id,
    unsigned char *buffer, unsigned short length);

/*****************************************************************************
 �� �� ��  : mntn_send_frame_info_msg
 ��������  : MNTN�ϱ�֡��Ϣ��Ϣ�Ľӿڷ�װ
 �������  : ulModuleId    - ģ��ID��Ŀǰ����DEC/ENC/VPP/CAMERA����Ӧö��mntn_module_id_t
             buffer        - ���������ݴ�ŵ�buffer
             length        - buffer�ĳ��ȣ�С��4K
 �������  : NONE
 �� �� ֵ  : void
*****************************************************************************/
void mntn_send_frame_info_msg(unsigned short prim_id, mntn_module_id_enum_u8 module_id,
    unsigned char *buffer, unsigned short length);

/*****************************************************************************
 �� �� ��  : mntn_send_context_msg
 ��������  : MNTN�ϱ���������Ϣ��Ϣ�Ľӿڷ�װ
 �������  : ulModuleId    - ģ��ID��Ŀǰ����DEC/ENC/VPP/CAMERA����Ӧö��mntn_module_id_t
             buffer        - ���������ݴ�ŵ�buffer
             length        - buffer�ĳ��ȣ�С��4K
 �������  : NONE
 �� �� ֵ  : void
*****************************************************************************/
void mntn_send_context_msg(unsigned short prim_id, mntn_module_id_enum_u8 module_id,
    unsigned char *buffer, unsigned short length);

/*****************************************************************************
 �� �� ��  : mntn_save_reg_data
 ��������  : ����Ĵ������ݵ�BUFFER
 �������  : module_id - ģ��ID
             buffer    - �Ĵ�����ŵ�buffer����Ӧ�ṹ����
             length    - buffer����
 �������  : NONE
 �� �� ֵ  : void
*****************************************************************************/
void mntn_save_reg_data(mntn_module_id_enum_u8 module_id, const void *buffer, const int length);

/*****************************************************************************
 �� �� ��  : mntn_save_frame_data
 ��������  : ����ͼ�����ݵ�FILE
 �������  : module_id     - ģ��ID��Ŀǰ����DEC/ENC/VPP/CAMERA����Ӧö��mntn_module_id_t
             buffer        - ���������ݴ�ŵ�buffer
             length        - buffer�ĳ��ȣ�С��4K
 �������  : NONE
 �� �� ֵ  : void
*****************************************************************************/
void mntn_save_frame_data(mntn_module_id_enum_u8 module_id, const void *buffer, const int length);

/*****************************************************************************
 �� �� ��  : mntn_exch_cb_register
 ��������  : ��������, MNTN�ṩ��������Ľӿڣ�����ģ��ͨ��register�������Լ���
             �ص�����ע���MNTNģ���С�
             �ص�����ʹ�õ�buffer����С��8K, �������ں�̬
 �������  : module_id    - ģ��ID
             func         - ����ģ��Ļص�����
 �������  : NONE
 �� �� ֵ  : int��MNTN_OKע��ɹ�, MNTN_ERRע��ʧ��
*****************************************************************************/
int mntn_exch_cb_register(mntn_module_id_enum_u8 module_id, mntn_exch_cb func);

/*****************************************************************************
 �� �� ��  : mntn_set_print_level
 ��������  : MNTN�ṩ��OM�Ľӿڣ�OM�����·���ά�ɲ����ã��ڲ��ӿ�
 �������  : module_id  - ģ��ID
             level      - 0~4�����μ�MNTN_LOG_LEVEL_OFF�Ⱥ궨��
 �������  : NONE
 �� �� ֵ  : int, �����������õ�level
*****************************************************************************/
int mntn_set_print_level(mntn_module_id_enum_u8 module_id, unsigned int level);

#endif /* __MEDIA_MNTN_KERNEL_H__ */

