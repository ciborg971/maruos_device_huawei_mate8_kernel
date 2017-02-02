/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : media_mntn_kernel.c
  �� �� ��   : ����
  ��    ��   : ��ޱ
  ��������   : 2012��09��12��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��09��12��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ļ�
******************************************************************************/


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "MEDIA_MNTN"

#include <linux/init.h>
#include <linux/module.h>
#include <linux/memory.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/fcntl.h>
#include <linux/time.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

//#ifndef __CHECK_CODE_UT_STUB_
//#include <linux/media_mntn_kernel.h>
//#else
//#include "media_mntn_kernel.h"
//#endif

#include "media_mntn_kernel.h"
/* stubs */
#ifdef __CHECK_CODE_LINT_STUB_
#include "code_stub.h"
#endif

/*****************************************************************************
  2 �ڲ��궨��
*****************************************************************************/

#define FILE_NAME_MAX   256

#if 0
#define mntn_log(fmt, ...) {    \
    printk(KERN_ALERT "[" LOG_TAG "]" "func: %s, line: %d " fmt "\n", __func__, __LINE__, ##__VA_ARGS__);   \
}

#define mntn_assert(x)  \
    do {            \
        if (!(x))   \
            mntn_log("!!!!!ASSERT ERROR!!!!");    \
    } while (0)
#endif

/*****************************************************************************
  3 �ڲ�ȫ�ֱ���
*****************************************************************************/

om_api_func_t           g_om_api_func = {NULL, NULL};      /* OM API used by mntn */

om_rsp_func             g_om_rsp_func = NULL;      /* ����OMע��Ļص����� */

/* ��ά�ɲ���Ϣ���� */
mntn_trace_config_t     g_video_trace_cfg[MNTN_MODULE_ID_MAX];

/* �������Իص�������¼ */
mntn_exch_cb            g_mntn_exch_cb_funcs[MNTN_MODULE_ID_MAX] = {0};

/* ��ӡ���� */
unsigned int            g_mntn_print_level[MNTN_MODULE_ID_MAX + 1] = {0};

/* ��module_idת��Ϊ�ַ������ַ�������С��7��Ŀǰģ����DEC/ENC/VPP/CAMERA */
static char             g_mntn_module_name[][8] = {"dec", "enc", "vpp", "camera", "edc", "gpu", "hdmi", "mntn"};

static char *save_path = (char*) "/data";

/*****************************************************************************
  4 �ⲿ��������
*****************************************************************************/

/* �����ṩ���������Իص�������ע�ắ�� */

/* yjl  2012-10-25 macro */

//#define __CHECK_CODE_ST_STUB_
#ifdef __CHECK_CODE_ST_STUB_
int DRV_EXCH_CUST_FUNC_REG(mntn_exch_cb cb)
{
	return 0;
}
#else
extern int DRV_EXCH_CUST_FUNC_REG(mntn_exch_cb cb);
#endif
  /* __CHECK_CODE_ST_STUB_ */


/*****************************************************************************
  5 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : mntn_set_snap_flags
 ��������  : ����ͼ������ץȡ���־���ڲ��ӿ�
 �������  : NONE
 �������  : NONE
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��19��
    ��    ��   : �࿡��yKF77511
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_set_snap_flags(void)
{
    return;
}

/*****************************************************************************
 �� �� ��  : mntn_set_print_level
 ��������  : MNTN�ṩ��OM�Ľӿڣ�OM�����·���ά�ɲ����ã��ڲ��ӿ�
 �������  : module_id  - ģ��ID
             level      - 0~4�����μ�MNTN_LOG_LEVEL_OFF�Ⱥ궨��
 �������  : NONE
 �� �� ֵ  : int, �����������õ�level
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��19��
    ��    ��   : �࿡��yKF77511
    �޸�����   : �����ɺ���
*****************************************************************************/
int mntn_set_print_level(mntn_module_id_enum_u8 module_id, unsigned int level)
{
    int ret = MNTN_OK;

    mntn_logd(MNTN_MODULE_ID_MNTN, "enter. module id=%d, print level=%d.", module_id, level);
    if (module_id > MNTN_MODULE_ID_MAX) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "module_id %d overflow!", module_id);
        return MNTN_ERR;
    }

    if (level >= MNTN_LOG_LEVEL_MAX) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "level %d overflow!", level);
        return MNTN_ERR;
    }

    g_mntn_print_level[module_id] = level;

    return ret;
}

/*****************************************************************************
 �� �� ��  : mntn_print_trace_cfg
 ��������  : ��ӡ��ά�ɲ����õ����ڣ��ڲ��ӿ�
 �������  : module_id  - ģ��ID
 �������  :
 �� �� ֵ  : NONE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��18��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_print_trace_cfg(mntn_module_id_enum_u8 module_id)
{
    mntn_trace_config_t *trace_config = NULL;

    if (module_id >= MNTN_MODULE_ID_MAX) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "module id %d error!", module_id);
        return;
    }

    trace_config = &g_video_trace_cfg[module_id];

    mntn_logd(MNTN_MODULE_ID_MNTN, "-----module %s Ȩ�ޱ�: ---------", g_mntn_module_name[module_id]);
    mntn_logd(MNTN_MODULE_ID_MNTN, "event config: %#x", trace_config->event_cfg.config);
    mntn_logd(MNTN_MODULE_ID_MNTN, "reg config: %#x", trace_config->reg_cfg.config);
    mntn_logd(MNTN_MODULE_ID_MNTN, "frame info config: %#x", trace_config->frame_info_cfg.config);
    mntn_logd(MNTN_MODULE_ID_MNTN, "context config: %#x", trace_config->context_cfg.config);

    return;
}

/*****************************************************************************
 �� �� ��  : mntn_save_trace_cfg
 ��������  : �����ά�ɲ����õ����أ��ڲ��ӿ�, �����������
 �������  : module_id  - ģ��ID
             trace_req  - OM��MNTN�Ŀ�ά�ɲ���������
 �������  : NONE
 �� �� ֵ  : MNTN_OK - ����ɹ���MNTN_ERR - ����ʧ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��15��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
int mntn_save_trace_cfg(mntn_module_id_enum_u8 module_id, mntn_trace_req_t *trace_req)
{
    mntn_config_data_t     *config_data     = NULL;
    unsigned short          req_length      = 0;
    mntn_trace_config_t    *trace_config    = NULL;

    mntn_logd(MNTN_MODULE_ID_MNTN, "enter.");

    req_length = (trace_req->length + offsetof(mntn_trace_req_t, prim_id))
                - (sizeof(mntn_trace_req_t) - sizeof(trace_req->data));
    if (req_length != sizeof(mntn_config_data_t)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "recieve SDT config req error!");
        return MNTN_ERR;
    }

    trace_config = &g_video_trace_cfg[module_id];
    config_data = (mntn_config_data_t*)trace_req->data;

    trace_config->event_cfg.config
        = (1 == config_data->event) ? MNTN_TRACE_MSG_YES : MNTN_TRACE_MSG_NO;
    trace_config->reg_cfg.config
        = (1 == config_data->reg) ? MNTN_TRACE_MSG_YES : MNTN_TRACE_MSG_NO;
    trace_config->frame_info_cfg.config
        = (1 == config_data->frame_info) ? MNTN_TRACE_MSG_YES : MNTN_TRACE_MSG_NO;
    trace_config->context_cfg.config
        = (1 == config_data->context) ? MNTN_TRACE_MSG_YES : MNTN_TRACE_MSG_NO;

    mntn_print_trace_cfg(module_id);

    if (MNTN_OK != mntn_set_print_level(module_id, config_data->print_level)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "mntn_set_print_level error!");
        return MNTN_ERR;
    }

    return MNTN_OK;
}

/*****************************************************************************
 �� �� ��  : mntn_om_send_cfg_cnf
 ��������  : MNTN�ڲ��ӿڣ����ڷ��Ϳ�ά�ɲ����õ�ȷ����Ϣ
 �������  : func_type   - FUNC TYPE
             prim_id     - MNTN��OM��CNF��ϢID
             result      - ���ý��
 �������  : NONE
 �� �� ֵ  : NONE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��10��09��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
int mntn_om_send_cfg_cnf(unsigned char func_type, unsigned short prim_id, mntn_module_id_enum_u8 module_id, unsigned int result)
{
    mntn_trace_cnf_t      *trace_rsp     = NULL;
    unsigned short         rsp_length    = 0x0;
    int                    ret = 0;

    mntn_logd(MNTN_MODULE_ID_MNTN, "enter, g_om_api_func.om_add_sn_time=%lx, g_om_rsp_func=%lx.", (unsigned long)g_om_api_func.om_add_sn_time, (unsigned long)g_om_rsp_func);

    if (NULL == g_om_api_func.om_add_sn_time) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "g_mntn_config.om_api_func.om_add_sn_time is null!");
        return MNTN_ERR;
    }

    /* Ϊ����ȷ����Ϣ�����ڴ� */
    rsp_length = sizeof(mntn_trace_cnf_t);
    if (NULL == (trace_rsp = (mntn_trace_cnf_t *)kmalloc(rsp_length, GFP_KERNEL))) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "mntn_om_send_cfg_cnf kmalloc failed!");
        return MNTN_ERR;
    }

    /* ��дȷ����Ϣ������ */
    trace_rsp->func_type = func_type;
    trace_rsp->cpu_id    = VIDEO_CPU_ID;
    trace_rsp->length    = rsp_length - 4;
    trace_rsp->prim_id   = prim_id;
    trace_rsp->module_id = module_id;
    trace_rsp->result    = result;
    (*(g_om_api_func.om_add_sn_time))(&(trace_rsp->sn), &(trace_rsp->timestamp));

    /* ����ȷ����Ϣ */
    //if (MNTN_OK != (*g_om_rsp_func)((om_rsp_packet *)trace_rsp, rsp_length)) {
    ret = g_om_rsp_func((om_rsp_packet *)trace_rsp, rsp_length);
    if (MNTN_OK != ret) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "send rsp error!");
        kfree(trace_rsp);
        return MNTN_ERR;
    }

    kfree(trace_rsp);

    mntn_logd(MNTN_MODULE_ID_MNTN, "exit. g_om_rsp_func return: %d.", ret);
    return MNTN_OK;
}

/*****************************************************************************
 �� �� ��  : mntn_proc_disp_cfg_req
 ��������  : MNTN�ڲ��ӿڣ����ڴ�����ʾģ��Ŀ�ά�ɲ�����
 �������  : trace_req  - ��ά�ɲ�����
 �������  : NONE
 �� �� ֵ  : NONE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��10��10��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_proc_disp_cfg_req(mntn_trace_req_t *trace_req)
{
    unsigned int           result        = MNTN_OK;
    unsigned short         cnf_prim_id   = 0;
    mntn_module_id_enum_u8 cnf_module_id = 0;

    mntn_logd(MNTN_MODULE_ID_MNTN, "enter, prim_id=0x%d.", trace_req->prim_id);
    switch (trace_req->prim_id) {
        /* ����EDC��Ϣ�ϱ����� */
        case ID_EDC_CFG_REQ:
            mntn_logd(MNTN_MODULE_ID_MNTN, "ID_EDC_CFG_REQ case.");
            result = mntn_save_trace_cfg(MNTN_MODULE_ID_EDC, trace_req);
            cnf_prim_id = ID_EDC_CFG_CNF;
            cnf_module_id = MNTN_MODULE_ID_EDC;
            break;
        case ID_GPU_CFG_REQ:
            mntn_logd(MNTN_MODULE_ID_MNTN, "ID_GPU_CFG_REQ case.");
            result = mntn_save_trace_cfg(MNTN_MODULE_ID_GPU, trace_req);
            cnf_prim_id = ID_GPU_CFG_CNF;
            cnf_module_id = MNTN_MODULE_ID_GPU;
            break;
        case ID_HDMI_CFG_REQ:
            mntn_logd(MNTN_MODULE_ID_MNTN, "ID_HDMI_CFG_REQ case.");
            result = mntn_save_trace_cfg(MNTN_MODULE_ID_HDMI, trace_req);
            cnf_prim_id = ID_HDMI_CFG_CNF;
            cnf_module_id = MNTN_MODULE_ID_HDMI;
            break;
        default:
            mntn_loge(MNTN_MODULE_ID_MNTN, "prim_id=0x%x error !", trace_req->prim_id);
            return;
    }

    /*��OM����CNF��Ϣ*/
    if (MNTN_OK != mntn_om_send_cfg_cnf(trace_req->func_type, cnf_prim_id, cnf_module_id, result))
    {
        mntn_loge(MNTN_MODULE_ID_MNTN, "send cfg rsp error!");
    }

    mntn_logd(MNTN_MODULE_ID_MNTN, "exit.");
    return;
}

/*****************************************************************************
 �� �� ��  : mntn_proc_video_cfg_req
 ��������  : MNTN�ڲ��ӿڣ����ڴ���CAMERA&��Ƶ�����ģ��Ŀ�ά�ɲ�����
 �������  : trace_req  - ��ά�ɲ�����
 �������  : NONE
 �� �� ֵ  : NONE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��10��10��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_proc_video_cfg_req(mntn_trace_req_t *trace_req)
{
    unsigned int           result        = MNTN_OK;
    unsigned short         cnf_prim_id   = 0;
    mntn_module_id_enum_u8 cnf_module_id = 0;

    mntn_logd(MNTN_MODULE_ID_MNTN, "enter, prim_id=0x%d.", trace_req->prim_id);
    switch (trace_req->prim_id) {
        /* ����ץȡͼ������ */
        case ID_FRAME_DATA_CFG_REQ:
            mntn_logd(MNTN_MODULE_ID_MNTN, "ID_FRAME_DATA_CFG_REQ case.");
            /*TODO*/
            mntn_set_snap_flags();
            cnf_prim_id = ID_FRAME_DATA_CFG_CNF;
            cnf_module_id = MNTN_MODULE_ID_MNTN;
            break;
        /* ���ý�����Ϣ�ϱ����� */
        case ID_DEC_CFG_REQ:
            mntn_logd(MNTN_MODULE_ID_MNTN, "ID_DEC_CFG_REQ case.");
            result = mntn_save_trace_cfg(MNTN_MODULE_ID_DEC, trace_req);
            cnf_prim_id = ID_DEC_CFG_CNF;
            cnf_module_id = MNTN_MODULE_ID_DEC;
            break;
        /* ���ñ�����Ϣ�ϱ����� */
        case ID_ENC_CFG_REQ:
            mntn_logd(MNTN_MODULE_ID_MNTN, "ID_ENC_CFG_REQ case.");
            result = mntn_save_trace_cfg(MNTN_MODULE_ID_ENC, trace_req);
            cnf_prim_id = ID_ENC_CFG_CNF;
            cnf_module_id = MNTN_MODULE_ID_ENC;
            break;
        /* ����VPP��Ϣ�ϱ����� */
        case ID_VPP_CFG_REQ:
            mntn_logd(MNTN_MODULE_ID_MNTN, "ID_VPP_CFG_REQ case.");
            result = mntn_save_trace_cfg(MNTN_MODULE_ID_VPP, trace_req);
            cnf_prim_id = ID_VPP_CFG_CNF;
            cnf_module_id = MNTN_MODULE_ID_VPP;
            break;
        /* ����CAMERA��Ϣ�ϱ����� */
        case ID_CAMERA_CFG_REQ:
            mntn_logd(MNTN_MODULE_ID_MNTN, "ID_CAMERA_CFG_REQ case.");
            result = mntn_save_trace_cfg(MNTN_MODULE_ID_CAMERA, trace_req);
            cnf_prim_id = ID_CAMERA_CFG_CNF;
            cnf_module_id = MNTN_MODULE_ID_CAMERA;
            break;
        default:
            mntn_loge(MNTN_MODULE_ID_MNTN, "prim_id=0x%x error !", trace_req->prim_id);
            return;
    }

    /*��OM����CNF��Ϣ*/
    if (MNTN_OK != mntn_om_send_cfg_cnf(trace_req->func_type, cnf_prim_id, cnf_module_id, result))
    {
        mntn_loge(MNTN_MODULE_ID_MNTN, "send cfg rsp error!");
    }

    mntn_logd(MNTN_MODULE_ID_MNTN, "exit.");
    return;
}

/*****************************************************************************
 �� �� ��  : mntn_om_rcv_cfg_req
 ��������  : MNTN�ṩ��OM�Ľӿڣ�OM�����·���ά�ɲ�����
 �������  : req_packet  - ��ά�ɲ�����
             rsq_func    - OM��MNTN�Ľӿڣ�����MNTN�ϱ���ά�ɲ���Ϣ��
                           ע: ����ACPU�����ֵ����ͳһһ�������ӿ�
 �������  : NONE
 �� �� ֵ  : NONE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��12��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_om_rcv_cfg_req(om_req_packet *req_packet, om_rsp_func rsq_func)
{
    mntn_trace_req_t      *trace_req     = NULL;

    mntn_logd(MNTN_MODULE_ID_MNTN, "enter.");

    if ((NULL == req_packet) ||(NULL == rsq_func)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "mntn_om_rcv_cfg_req para error!");
        return;
    }

    if ((DISP_FUNCTION_TYPE != req_packet->func_type)
        && (VIDEO_FUNCTION_TYPE != req_packet->func_type)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, " Function type %d error!", req_packet->func_type);
        return;
    }

    g_om_rsp_func = rsq_func;

    mntn_logd(MNTN_MODULE_ID_MNTN, "g_om_rsp_func=%lx, rsq_func=%lx.", (unsigned long)g_om_rsp_func, (unsigned long)rsq_func);
    mntn_logd(MNTN_MODULE_ID_MNTN, "om_req_packet func_type=%d, om_req_packet cpu_id=%d, om_req_packet length=%d.", (int)req_packet->func_type, (int)req_packet->cpu_id, req_packet->length);

    trace_req = (mntn_trace_req_t *)req_packet;

    if (DISP_FUNCTION_TYPE == trace_req->func_type) {
        mntn_proc_disp_cfg_req(trace_req);
    }
    else {
        mntn_proc_video_cfg_req(trace_req);
    }

    return;
}/* mntn_om_rcv_cfg_req */

/*****************************************************************************
 �� �� ��  : mntn_om_close_trace
 ��������  : MNTN�ṩ��OM��API����������OM���������Ϣ�ϱ�������
 �������  : NONE
 �������  : NONE
 �� �� ֵ  : NONE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��12��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_om_close_trace(void)
{
    mntn_logd(MNTN_MODULE_ID_MNTN, "enter.");

    memset(&g_video_trace_cfg, 0x00, sizeof(g_video_trace_cfg));
    g_om_rsp_func = NULL;
}

/*****************************************************************************
 �� �� ��  : mntn_proc_reg
 ��������  : MNTN�ṩ��OM��API������OMͨ���˽ӿ��·�ע����Ϣ������SN��ȡ����
 �������  : func_id    - ����ID����Ӧom_api_func_id_eö������
             func_name  - ����������OM�ṩ
 �������  : NONE
 �� �� ֵ  : NONE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��12��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_proc_reg(om_api_func_id_e func_id, om_api_func func_name)
{
    unsigned int ret_reg = MNTN_OK;

    mntn_logd(MNTN_MODULE_ID_MNTN, "enter.");

    if (NULL == func_name) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "pFunc is error!");
        return;
    }

    switch(func_id) {
        case MNTN_OM_FUNC_ID_REGISTER_REQ:
            g_om_api_func.om_reg_request = (om_reg_request_func)func_name;

            /* video om callback register */
            ret_reg = (*(g_om_api_func.om_reg_request))(VIDEO_FUNCTION_TYPE, mntn_om_rcv_cfg_req);
            if (MNTN_OK != ret_reg) {
                mntn_loge(MNTN_MODULE_ID_MNTN, "VIDEO om_reg_request fail!");
            }
            mntn_logd(MNTN_MODULE_ID_MNTN, "VIDEO REQ return %d, g_om_rsp_func=%lx.", ret_reg, (unsigned long)g_om_rsp_func);

            /* display om callback register */
            ret_reg = (*(g_om_api_func.om_reg_request))(DISP_FUNCTION_TYPE, mntn_om_rcv_cfg_req);
            if (MNTN_OK != ret_reg) {
                mntn_loge(MNTN_MODULE_ID_MNTN, "DISP om_reg_request fail!");
            }
            mntn_logd(MNTN_MODULE_ID_MNTN, "DISP REQ return %d, g_om_rsp_func=%lx.", ret_reg, (unsigned long)g_om_rsp_func);

            break;
        case MNTN_OM_FUNC_ID_ADD_SN_TIME:
            g_om_api_func.om_add_sn_time = (om_add_sn_time_func)func_name;
            mntn_logd(MNTN_MODULE_ID_MNTN, "SN_TIME return g_om_api_func.om_add_sn_time=%lx.", (unsigned long)g_om_api_func.om_add_sn_time);
            break;
        default:
            mntn_loge(MNTN_MODULE_ID_MNTN, "func_id is error!");
            break;
    }

    mntn_logd(MNTN_MODULE_ID_MNTN, "exit.");
    return;
}

/*****************************************************************************
 �� �� ��  : mntn_check_msg_param
 ��������  : MNTN�ϱ���Ϣ����μ��
 �������  : ulModuleId    - ģ��ID��Ŀǰ����DEC/ENC/VPP/CAMERA����Ӧö��mntn_module_id_t
             buffer        - ���������ݴ�ŵ�buffer
             length        - buffer�ĳ��ȣ�С��4K
 �������  : NONE
 �� �� ֵ  : int
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��10��08��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
int mntn_check_msg_param(mntn_module_id_enum_u8 module_id, unsigned char *buffer, unsigned short length)
{
    /* 2012-10-25  FIXBUG: buffer == NULL && length == 0 */
    if ((NULL == buffer) || (0 == length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "buffer info error!");
        return MNTN_ERR;
    }

    if (module_id >= MNTN_MODULE_ID_MAX) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "module id %x error!", module_id);
        return MNTN_ERR;
    }

    return MNTN_OK;
}

/*****************************************************************************
 �� �� ��  : mntn_send_msg
 ��������  : MNTN������Ϣ��OM���ڲ��ӿ�, �����������
 �������  : prim_id       - ��ϢID����Ӧmntn_prim_id_eö������
             buffer        - ���������ݴ�ŵ�buffer
             length        - buffer�ĳ��ȣ����4K
 �������  : NONE
 �� �� ֵ  : int
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��20��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
int mntn_send_msg(unsigned char func_type, unsigned short prim_id, mntn_module_id_enum_u8 module_id, unsigned char *buffer, unsigned short length)
{
    mntn_trace_ind_t   *trace_rsp  = NULL;
    unsigned short      rsp_length = 0x0;
    unsigned short      rsp_header_length = 0x0;

    /* �����Ϣ�ϱ��ص���������Ч�� */
    if(NULL == g_om_rsp_func) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "pointer of om_rsp_func is NULL!");
        return MNTN_ERR;
    }

    /* ���ʱ���ص���������Ч�� */
    if(NULL == g_om_api_func.om_add_sn_time) {
         mntn_loge(MNTN_MODULE_ID_MNTN, "pointer of om_add_sn_time is NULL!");
         return MNTN_ERR;
    }

    /* Ϊ������Ϣ�����ڴ� */
    rsp_header_length = sizeof(mntn_trace_ind_t) - 4;   /* 4��ʾmntn_trace_ind_t�ṹ����data��ĳ��� */
    rsp_length = rsp_header_length + length;
    rsp_length = (rsp_length > MNTN_MSG_MAX_LENGTH) ? MNTN_MSG_MAX_LENGTH : rsp_length;
    trace_rsp = (mntn_trace_ind_t *)kmalloc(rsp_length, GFP_KERNEL);
    if (NULL == trace_rsp) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "mntn_send_msg kmalloc fail!");
        return MNTN_ERR;
    }

    /* ��д��Ϣ���� */
    trace_rsp->func_type  = func_type;
    trace_rsp->cpu_id     = VIDEO_CPU_ID;
    trace_rsp->length     = rsp_length - offsetof(mntn_trace_ind_t, sn);/* length��ʾlength��֮������г��� */
    trace_rsp->prim_id    = prim_id;
    trace_rsp->module_id  = module_id;

    mntn_logd(MNTN_MODULE_ID_MNTN, "func_type=%d, prim_id=%x.", func_type, prim_id);

    (*(g_om_api_func.om_add_sn_time))(&(trace_rsp->sn), &(trace_rsp->timestamp));
    memcpy((void *)trace_rsp->data, buffer, rsp_length - rsp_header_length);

    /* ������Ϣ */
    if (MNTN_OK != (*(g_om_rsp_func))((om_rsp_packet *)trace_rsp, rsp_length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "mntn_send_msg error!");
        kfree(trace_rsp);
        return MNTN_ERR;
    }

    /* �ͷ��ڴ� */
    kfree(trace_rsp);

    return MNTN_OK;
}

/*****************************************************************************
 �� �� ��  : mntn_send_event_msg
 ��������  : MNTN�ϱ��¼���Ϣ�Ľӿڷ�װ
 �������  : prim_id       - ��ϢID����Ӧmntn_xxx_prim_id_eö������
             ulModuleId    - ģ��ID��Ŀǰ����DEC/ENC/VPP/CAMERA����Ӧö��mntn_module_id_t
             buffer        - ���������ݴ�ŵ�buffer
             length        - buffer�ĳ��ȣ�С��4K
 �������  : NONE
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��12��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_send_event_msg(unsigned short prim_id, mntn_module_id_enum_u8 module_id,
    unsigned char *buffer, unsigned short length)
{
    unsigned char       func_type;

    /* ������ */
    if (MNTN_OK != mntn_check_msg_param(module_id, buffer, length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "send event msg param error!");
        return;
    }

    /* ����modul id�ж��Ƿ��ܹ��ϱ���Ϣ */
    if (MNTN_TRACE_MSG_YES != g_video_trace_cfg[module_id].event_cfg.config) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "module %d not allow to send event!", module_id);
        return;
    }

    /* �ж�func_type����ģ��ID��Ŀǰ��MNTN_MODULE_ID_EDCΪ�ֽ��ߣ�
       ���DISPģ����Ҫ��MNTN_MODULE_ID_EDC֮ǰ����ģ��ID���˴���Ҫ��Ӧ���� */
    func_type = (module_id < MNTN_MODULE_ID_EDC) ? VIDEO_FUNCTION_TYPE : DISP_FUNCTION_TYPE;

    /* ������Ϣ */
    if (MNTN_OK != mntn_send_msg(func_type, prim_id, module_id, buffer, length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "mntn_send_event_msg error!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : mntn_send_reg_msg
 ��������  : MNTN�ϱ��Ĵ�����Ϣ�Ľӿڷ�װ
 �������  : prim_id       - ��ϢID����Ӧmntn_xxx_prim_id_eö������
             ulModuleId    - ģ��ID��Ŀǰ����DEC/ENC/VPP/CAMERA����Ӧö��mntn_module_id_t
             buffer        - ���������ݴ�ŵ�buffer
             length        - buffer�ĳ��ȣ�С��4K
 �������  : NONE
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��12��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_send_reg_msg(unsigned short prim_id, mntn_module_id_enum_u8 module_id,
    unsigned char *buffer, unsigned short length)
{
    unsigned char       func_type;

    /* ������ */
    if (MNTN_OK != mntn_check_msg_param(module_id, buffer, length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "send reg msg param error!");
        return;
    }

    /* ����modul id�ж��Ƿ��ܹ��ϱ���Ϣ */
    if (MNTN_TRACE_MSG_YES != g_video_trace_cfg[module_id].reg_cfg.config) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "module %d not allow to send reg msg!", module_id);
        return;
    }

    /* �ж�func_type����ģ��ID��Ŀǰ��MNTN_MODULE_ID_EDCΪ�ֽ��ߣ�
       ���DISPģ����Ҫ��MNTN_MODULE_ID_EDC֮ǰ����ģ��ID���˴���Ҫ��Ӧ���� */
    func_type = (module_id < MNTN_MODULE_ID_EDC) ? VIDEO_FUNCTION_TYPE : DISP_FUNCTION_TYPE;

    /* ������Ϣ */
    if (MNTN_OK != mntn_send_msg(func_type, prim_id, module_id, buffer, length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "mntn_send_reg_msg error!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : mntn_send_frame_info_msg
 ��������  : MNTN�ϱ�֡��Ϣ��Ϣ�Ľӿڷ�װ
 �������  : prim_id       - ��ϢID����Ӧmntn_xxx_prim_id_eö������
             ulModuleId    - ģ��ID��Ŀǰ����DEC/ENC/VPP/CAMERA����Ӧö��mntn_module_id_t
             buffer        - ���������ݴ�ŵ�buffer
             length        - buffer�ĳ��ȣ�С��4K
 �������  : NONE
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��12��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_send_frame_info_msg(unsigned short prim_id, mntn_module_id_enum_u8 module_id,
    unsigned char *buffer, unsigned short length)
{
    unsigned char       func_type;

    /* ������ */
    if (MNTN_OK != mntn_check_msg_param(module_id, buffer, length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "send frame info msg param error!");
        return;
    }

    /* ����modul id�ж��Ƿ��ܹ��ϱ���Ϣ */
    if (MNTN_TRACE_MSG_YES != g_video_trace_cfg[module_id].frame_info_cfg.config) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "module %d not allow to send frame info msg!", module_id);
        return;
    }

    /* �ж�func_type����ģ��ID��Ŀǰ��MNTN_MODULE_ID_EDCΪ�ֽ��ߣ�
       ���DISPģ����Ҫ��MNTN_MODULE_ID_EDC֮ǰ����ģ��ID���˴���Ҫ��Ӧ���� */
    func_type = (module_id < MNTN_MODULE_ID_EDC) ? VIDEO_FUNCTION_TYPE : DISP_FUNCTION_TYPE;

    /* Ϊ������Ϣ�����ڴ� */
    if (MNTN_OK != mntn_send_msg(func_type, prim_id, module_id, buffer, length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "mntn_send_frame_info_msg error!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : mntn_send_context_msg
 ��������  : MNTN�ϱ���������Ϣ��Ϣ�Ľӿڷ�װ
 �������  : prim_id       - ��ϢID����Ӧmntn_xxx_prim_id_eö������
             ulModuleId    - ģ��ID��Ŀǰ����DEC/ENC/VPP/CAMERA����Ӧö��mntn_module_id_t
             buffer        - ���������ݴ�ŵ�buffer
             length        - buffer�ĳ��ȣ�С��4K
 �������  : NONE
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��12��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_send_context_msg(unsigned short prim_id, mntn_module_id_enum_u8 module_id,
    unsigned char *buffer, unsigned short length)
{
    unsigned char       func_type;

    /* ������ */
    if (MNTN_OK != mntn_check_msg_param(module_id, buffer, length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "send context msg param error!");
        return;
    }

    /* ����modul id�ж��Ƿ��ܹ��ϱ���Ϣ */
    if (MNTN_TRACE_MSG_YES != g_video_trace_cfg[module_id].context_cfg.config) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "module %d not allow to send context msg!", module_id);
        return;
    }

    /* �ж�func_type����ģ��ID��Ŀǰ��MNTN_MODULE_ID_EDCΪ�ֽ��ߣ�
       ���DISPģ����Ҫ��MNTN_MODULE_ID_EDC֮ǰ����ģ��ID���˴���Ҫ��Ӧ���� */
    func_type = (module_id < MNTN_MODULE_ID_EDC) ? VIDEO_FUNCTION_TYPE : DISP_FUNCTION_TYPE;

    /* Ϊ������Ϣ�����ڴ� */
    if (MNTN_OK != mntn_send_msg(func_type, prim_id, module_id, buffer, length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "mntn_send_context_msg error!");
    }

    return;
}



/*****************************************************************************
 �� �� ��  : mntn_exch_cb_register
 ��������  : MNTN�ṩ��IT2�Ľӿڣ�����IT2������ģ����������Իص�����ע�ᵽMNTN��
             �ص�����ʹ�õ�buffer����С��8K, �������ں�̬
 �������  : module_id    - ģ��ID
             func         - ����ģ��Ļص�����
 �������  : NONE
 �� �� ֵ  : int��MNTN_OKע��ɹ�, MNTN_ERRע��ʧ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��12��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
int mntn_exch_cb_register(mntn_module_id_enum_u8 module_id, mntn_exch_cb func)
{
    int     result = 0;
    mntn_logd(MNTN_MODULE_ID_MNTN, "enter.");

    if (module_id >= MNTN_MODULE_ID_MAX) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "module id %d error!", module_id);
        return MNTN_ERR;
    }

    /* 2012-10-25  avoid to register exch more than once */
    if (NULL == g_mntn_exch_cb_funcs[module_id]) {

        /* 2012-10-25  register exch directly */
//        result = DRV_EXCH_CUST_FUNC_REG(func);
        /* STUB FOR DEBUG*/
        result = 0;
        /* STUB END */
        mntn_logd(MNTN_MODULE_ID_MNTN, "func address=%lx, DRV_EXCH_CUST_FUNC_REG return %d.", (unsigned long)func, result);

        if (EXCH_OK == result) {
            g_mntn_exch_cb_funcs[module_id] = func;
            mntn_logd(MNTN_MODULE_ID_MNTN, "register exch func ok ! g_mntn_exch_cb_funcs[%d]=0x%lx.", module_id, (unsigned long)g_mntn_exch_cb_funcs[module_id]);
        } else {
            /* NOT save the func if register false */
            mntn_loge(MNTN_MODULE_ID_MNTN, "register exch func error! %d.", result);
            return MNTN_ERR;
        }
    }
    return MNTN_OK;
}

/*****************************************************************************
 �� �� ��  : mntn_save_data_to_file
 ��������  : �������ݵ�FILE���ڲ��ӿڣ�����������飬��������Ҫ��֤�����Ч
 �������  : module_id     - ģ��ID��Ŀǰ����DEC/ENC/VPP/CAMERA����Ӧö��mntn_module_id_t
             buffer        - ���ݴ�ŵ�buffer
             length        - buffer�ĳ���
 �������  : NONE
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��12��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
int mntn_save_data_to_file(char *name, const void *buffer, const int length)
{
    ssize_t         ret = 0;
    struct file    *fp  = NULL;
    mm_segment_t    fs;
    loff_t          pos = 0;
    int             result = MNTN_OK;

    mntn_logd(MNTN_MODULE_ID_MNTN, "before filp_open %s", name);
    fp = (struct file *) filp_open(name, O_RDWR | O_CREAT, 0644);   /* 0644���˽��ƣ���ʾȨ�� */   /* lint need convert to (struct file *) explicitly */
    if (IS_ERR(fp)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "filp_open %s error, fp = %d !", name, (int)fp);
        return MNTN_ERR;
    }

    fs = get_fs();
    set_fs(KERNEL_DS);
    ret = vfs_write(fp, buffer, length, &pos);        /* arg. no. 4: lint need covert to int type explicitly, BUT, maybe it will be ERROR ! */
    if (ret != length) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "write file: %s error [write: %d, size; %d]", name, (int)ret, length);
        result = MNTN_ERR;
    }

    filp_close(fp, NULL);
    set_fs(fs);

    return result;
}

/*****************************************************************************
 �� �� ��  : mntn_save_frame_data
 ��������  : ����ͼ�����ݵ�FILE
 �������  : module_id     - ģ��ID��Ŀǰ����DEC/ENC/VPP/CAMERA����Ӧö��mntn_module_id_t
             buffer        - ͼ�����ݴ�ŵ�buffer
             length        - buffer�ĳ���
 �������  : NONE
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��12��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_save_frame_data(mntn_module_id_enum_u8 module_id, const void *buffer, const int length)
{
    char            name[FILE_NAME_MAX] = {0};
    struct timeval  tv;

    /* ������ */
    if ((NULL == buffer) || (0 == length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "buffer info error!");
        return;
    }

    /* ������ */
    if (module_id >= MNTN_MODULE_ID_MAX) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "module id %d error!", module_id);
        return;
    }

    do_gettimeofday(&tv);
    snprintf(name, FILE_NAME_MAX, "%s/mntn_krn_img_%s_%ld_%06ld.dump",
        save_path, g_mntn_module_name[module_id], tv.tv_sec, tv.tv_usec);

    if (MNTN_OK != mntn_save_data_to_file(name, buffer, length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "filp_open %s error!", name);
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : mntn_save_reg_data
 ��������  : ����Ĵ������ݵ�FILE
 �������  : module_id - ģ��ID
             buffer    - �Ĵ�����ŵ�buffer����Ӧ�ṹ����mntn_reg_info_t
             length    - buffer�ĳ���
 �������  : NONE
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��19��
    ��    ��   : ��ޱ62576
    �޸�����   : �����ɺ���
*****************************************************************************/
void mntn_save_reg_data(mntn_module_id_enum_u8 module_id, const void *buffer, const int length)
{
    char            name[FILE_NAME_MAX] = {0};
    struct timeval  tv;

    /* ������ */
    if ((NULL == buffer) || (0 == length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "buffer info error!");
        return;
    }

    /* ������ */
    if (module_id >= MNTN_MODULE_ID_MAX) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "module id %d error!", module_id);
        return;
    }

    do_gettimeofday(&tv);
    snprintf(name, FILE_NAME_MAX, "%s/mntn_krn_reg_%s_%ld_%06ld.dump",
        save_path, g_mntn_module_name[module_id], tv.tv_sec, tv.tv_usec);

    if (MNTN_OK != mntn_save_data_to_file(name, buffer, length)) {
        mntn_loge(MNTN_MODULE_ID_MNTN, "filp_open %s error!", name);
        return;
    }

    return;
}

EXPORT_SYMBOL(g_mntn_print_level);
EXPORT_SYMBOL(mntn_set_print_level);
EXPORT_SYMBOL(mntn_om_rcv_cfg_req);
EXPORT_SYMBOL(mntn_om_close_trace);
EXPORT_SYMBOL(mntn_proc_reg);
EXPORT_SYMBOL(mntn_send_event_msg);
EXPORT_SYMBOL(mntn_send_reg_msg);
EXPORT_SYMBOL(mntn_send_frame_info_msg);
EXPORT_SYMBOL(mntn_send_context_msg);
EXPORT_SYMBOL(mntn_exch_cb_register);
EXPORT_SYMBOL(mntn_save_frame_data);
EXPORT_SYMBOL(mntn_save_reg_data);



