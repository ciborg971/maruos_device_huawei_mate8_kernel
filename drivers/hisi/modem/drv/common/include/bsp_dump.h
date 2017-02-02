/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __BSP_DUMP_H__
#define __BSP_DUMP_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "osl_common.h"
#if defined(__KERNEL__) || defined(__VXWORKS__) || defined(__OS_RTOSCK__)
#include "mdrv_om.h"
#else
#include "mdrv_om_common.h"
#endif
#include "drv_comm.h"
#include "bsp_om.h"
#ifdef __OS_RTOSCK__
#include "sre_task.h"
#include "sre_exc.h"
#endif


#include "bsp_om_enum.h"

/*****************************************************************************
  1 �궨��
*****************************************************************************/
#define  DUMP_TASK_SWT_THRESHOLD_SIZE       16*1024
#define  DUMP_INT_LOCK_THRESHOLD_SIZE       4*1024
/* dump�����ں��޸� begin */
#ifdef __KERNEL__
#define EXC_VEC_RESET		0x00	/* reset */
#define EXC_VEC_UNDEF		0x04	/* undefined instruction */
#define EXC_VEC_SWI		    0x08	/* software interrupt */
#define EXC_VEC_PREFETCH	0x0c	/* prefetch abort */
#define EXC_VEC_DATA		0x10	/* data abort */
#define EXC_VEC_IRQ         0x18    /* interrupt */
#define EXC_VEC_FIQ         0x1C    /* fast interrupt */
#endif
/* dump�����ں��޸� end */

/*****************************************************************************
  2 ö�ٶ���
*****************************************************************************/
typedef DUMP_SAVE_MOD_ENUM          dump_save_modid_t;

typedef enum{
    DUMP_SYSVIEW_TASKSWITCH       = 0,
    DUMP_SYSVIEW_INTSWITCH,
    DUMP_SYSVIEW_INTLOCK,
    DUMP_SYSVIEW_BUTT
}dump_sysview_t;

typedef enum
{
    DUMP_MBB    = 0,
    DUMP_PHONE,
    DUMP_PRODUCT_BUTT
}dump_product_type_t;

#define NVID_DUMP   (NV_ID_DRV_DUMP)


/* ö��ֵ��dump_file_cfg_s���뱣��ƥ�� */
typedef enum
{
    MODEM_DUMP      = 0,
    MODME_SRAM,
    MODEM_SHARE,
    MODEM_DDR,
    LPHY_TCM,
    LPM3_TCM,
    AP_ETB,
    MODME_ETB,
    DUMP_FILE_BUTT
}dump_file_index_e;

/* dump�ļ���㣬ioctl������ */
#define DUMP_CMD_SET_COUNT      0x1f000000  /* ������󱣴���� */
#define DUMP_CMD_SET_FILE       0x1f000001  /* ���ñ����ļ��б� */
#define DUMP_CMD_FLUSH          0x1f000002  /* �������ã�д��NV */

typedef enum
{
    DUMP_SAVE_FILE_NORMAL = 0x0,
    DUMP_SAVE_FILE_NEED   = 0xAABB,
    DUMP_SAVE_FILE_END    = 0xCCDD
}dump_save_flag_t;

typedef enum
{
    DUMP_START_POWER_ON = 0,
    DUMP_START_REBOOT   = 0x5A5A1111,
    DUMP_START_EXCH     = 0x5A5A2222,
    DUMP_START_CRASH    = 0x5A5A3333
}dump_start_flag_e;

typedef enum _dump_reboot_cpu_e
{
    DUMP_CPU_APP     = 0x01000000,
    DUMP_CPU_COMM    = 0x02000000,
    DUMP_CPU_BBE     = 0x03000000,
    DUMP_CPU_LPM3    = 0x04000000,
    DUMP_CPU_IOM3    = 0x05000000,
    DUMP_CPU_HIFI    = 0x06000000,
    DUMP_CPU_TEEOS   = 0x07000000
}dump_reboot_cpu_t;

typedef enum _dump_reboot_reason_e
{
    DUMP_REASON_NORMAL      = 0x0,
    DUMP_REASON_ARM         = 0x1,
    DUMP_REASON_STACKFLOW   = 0x2,
    DUMP_REASON_WDT         = 0x3,
    DUMP_REASON_PMU         = 0x4,
    DUMP_REASON_REBOOT      = 0x5,
    DUMP_REASON_UNDEF       = 0xff
}dump_reboot_reason_t;

typedef struct
{
    u32 init_flag;           /*0xA0 */
    u32 start_flag;
    u32 save_flag;
    u32 ext_save_flag;

    u32 inInterrupt;           /*0xA0 */
    u32 taskSwitchStart;           /*0xA0 */
    u32 IntSwitchStart;           /*0xA0 */

    dump_save_flag_t save_file_flag;           /*0xA0 */
    u32 start_wait_flag;           /*0xA0 */
}dump_core_internal_t;

typedef struct
{
    dump_core_internal_t app_internal;
    dump_core_internal_t comm_internal;
    dump_core_internal_t m3_internal;
	u32 hso_connect_flag;  /* HIDS connect status --by yangzhi */
}dump_global_internal_t;

typedef struct
{
    dump_global_internal_t  internal_info;
}dump_global_info_t;

#define DUMP_LOAD_MAGIC     0xDDDD1234
typedef struct _dump_load_info_s
{
    u32 magic_num;      /* dump������Ϣ����ʶ�����ڼ���֮ǰ�汾 */
    u32 ap_ddr;         /* AP DDR���ص�ַ */
    u32 ap_share;       /* AP�����ڴ���ص�ַ */
    u32 ap_dump;        /* AP��ά�ɲ��ڴ���ص�ַ */
    u32 ap_sram;        /* AP SRAM���ص�ַ */
    u32 ap_dts;         /* AP DTS���ص�ַ */
    u32 mdm_ddr;        /* MODEM DDR���ص�ַ */
    u32 mdm_share;      /* MODEM�����ڴ���ص�ַ */
    u32 mdm_dump;       /* MODEM��ά�ɲ��ڴ���ص�ַ */
    u32 mdm_sram;       /* MODEM SRAM���ص�ַ */
    u32 mdm_dts;        /* MODEM DTS���ص�ַ */
    u32 lpm3_tcm0;      /* LPM3 TCM0���ص�ַ */
    u32 lpm3_tcm1;      /* LPM3 TCM1���ص�ַ */
}dump_load_info_t;
#ifdef __OS_RTOSCK__

/*RTOSck������ṹ��*/
typedef struct tagListObject
{
    struct tagListObject *pstPrev;
    struct tagListObject *pstNext;
} LIST_OBJECT_S;

typedef struct tagMsgQHead
{
    UINT32 uwMsgNum;
    LIST_OBJECT_S stMsgList;
} MSG_QHead_S;

typedef struct tagPublicTskCB
{
    VOID               *pStackPointer;              // ��ǰ�����SP
    TSK_STATUS_T        usTaskStatus;               // ����״̬
    TSK_PRIOR_T         usPriority;                 // ������������ȼ�
    UINT32              uwStackSizes;                // ����ջ��С
    UINT32              uwTopOfStack;               // ����ջ��
    TSK_HANDLE_T        uwTaskPID;                  // ����PID
    TSK_ENTRY_FUNC      pfnTaskEntry;               // ������ں���
    VOID               *pTaskSem;                   // ����Pend���ź���ָ��
    INT32               swFsemCount;                // �����ź�������
    UINT32              auwArgs[4];                 // ����Ĳ���
#if (OS_HAVE_COPROCESSOR1 == YES)                   // ֻ��Tensilicaƽ̨���иù���
    VOID               *pCpSaveAreaA;               // ʸ���Ĵ��������ַA
    VOID               *pCpSaveAreaB;               // ʸ���Ĵ��������ַB
#endif
    TSK_PRIOR_T         usOrigPriority;             // �����ԭʼ���ȼ�
    UINT16              usStackCfgFlg;              // ����ջ���ñ��
    UINT16              usQNum;                     // ��Ϣ������
    UINT16              usRecvQID;                  // ����������Ϣ��QID
    UINT32              uwPrivateData;              // ˽������
    MSG_QHead_S        *pstMsgQ;                    // ָ����Ϣ��������
    LIST_OBJECT_S       stPendList;                 // �ź�������ָ��
    LIST_OBJECT_S       stTimerList;                // ������ʱ����ָ��
    LIST_OBJECT_S       stSemBList;                 // ���л����ź�������
    UINT64              ullExpirationTick;          // ����ָ���ʱ���(��λTick)
    UINT32              uwEvent;                    // �����¼�
    UINT32              uwEventMask;                // �����¼�����
    UINT32              uwLastErr;                  // �����¼�����һ��������
    UINT32              uwReserved;                 // ����һ��PAD����֤TCB 8�ֽڶ���
} TSK_CB_S;
#endif
typedef bool (*exc_hook)(void * param);

#define CCORE               "CP"
#define ACORE               "AP"
#define UNKNOW_CORE         "UNKNOW"
#define UNKNOW              "UNKNOW"
#define DATA_ABORT          "abort"
#define WDT                 "wdg"
#define NOARMAL             "syserr"
#define UNDEFFINE           "undefine"
#define DUMP_MODULE_NAME_LEN (12)
typedef struct
{
    u32 task_id;            /*����id*/
    u8  task_name[12];      /*������*/
}dump_task_info_s;

typedef struct module_info
{
    u32     moudle_sum;               /*�������*/
    struct
    {
    	u32 module;	                  /*�������*/
        char module_name[DUMP_MODULE_NAME_LEN];         /*�����������*/
    }module_info[1];
}module_info_t;

typedef struct modid_info
{
    u32     moudid_sum;             /*��Χ����*/
    struct
    {
    	u32  modid_start;		    /*���������λmodid��ʼֵ*/
    	u32  modid_end;		        /*���������λmodid����ֵ*/
    	char module[DUMP_MODULE_NAME_LEN];	        /*�������*/
    }modid_info[1];
}modid_info_t;

typedef struct task_table
{
    u32 task_sum;                /*��������*/
    struct
    {
    	char  task_name[16]; 	/*������*/
    	char  module[DUMP_MODULE_NAME_LEN]; 		/*�������*/
    }task_info[1];
}task_table_t;

typedef struct interupt_table
{
    u32 intrupt_sum;            /*�ж�����*/
    struct
    {
    	u32 interrpt_id; 		/*�жϺ�*/
    	char  module[DUMP_MODULE_NAME_LEN]; 		/*�������*/
    }interupt_info[1];
}interupt_table_t;

typedef struct
{
    u32 except_core;
    u32 except_reason;
    u32 voice;
    u32 modId;
    u32 reboot_context;
    u32 reboot_task;
    u32 reboot_int;
}dump_except_info_t;

typedef struct
{
    u8  brieftype[16];       /*module+voice*/
    u8  module_name[12];      /*���������*/
    u8  voice[4];            /*�Ƿ����������쳣, yes,no*/
    u8  task_name[16];       /*��λ������,���Ϊ�ж���Ϊ�жϺ�,�������Ϊ������Ϊ������*/
    u32 reboot_int;          /*��λ�жϺ�*/
    u32 modid;               /*��λmodid,system_error�ĵ�һ�����*/
    u8  reboot_core[8];      /*ȡֵAP CP*/
    u8  reboot_reson[16];    /*ȡֵNormal/DataAbort/Wdt*/
}dump_reset_log_t;
#define DUMP_REBOOT_INT "Interrupt_No"
#define DUMP_REBOOT_TASK "task_name"
/*CP������Ϣ������Ϣ�ṹ���г�Աƫ��*/
#define DUMP_CP_MODID_OFFSET        (0x1C)
#define DUMP_CP_TASK_NAME_OFFSET    (0x8)

/*AP������Ϣ������Ϣ�ṹ���г�Աƫ��*/
#define DUMP_AP_MODID_OFFSET        ((unsigned long)&(((dump_base_info_t*)0)->modId))
#define DUMP_AP_TASK_NAME_OFFSET    ((unsigned long)(((dump_base_info_t*)0)->taskName))
/*****************************************************************************
  3 ��������
*****************************************************************************/
#ifdef ENABLE_BUILD_OM

void system_error (u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length);
s32  bsp_dump_init(void);
void bsp_dump_init_phase2(void);
dump_handle bsp_dump_register_hook(char * name, dump_hook func);
s32  bsp_dump_unregister_hook(dump_handle handle);
u8*  bsp_dump_register_field(u32 mod_id, char * name, void * virt_addr, void * phy_addr, u32 length, u16 version);
u8*  bsp_dump_get_field_addr(u32 field_id);
u8 * bsp_dump_get_field_phy_addr(u32 field_id);
void bsp_dump_set_hso_conn_flag(u32 flag);
s32  bsp_dump_register_sysview_hook(dump_sysview_t mod_id, dump_hook func);
void bsp_dump_trace_stop(void);
void bsp_dump_init_task_name(void);
void bsp_om_save_reboot_log(const char * func_name, const void* caller);
/* dump�����ں��޸� begin */
void dump_set_exc_vec(u32 vec);
void dump_int_enter(u32 dir, u32 irq_num);
void dump_int_exit(u32 dir, u32 irq_num);
int  dump_stack_trace_print(unsigned long where);
/* dump�����ں��޸� end */
s32  dump_exc_register(exc_hook func);
void bsp_ccore_wdt_register_hook(void);
u32 bsp_dump_parse_apr_dts_info(void);
void bsp_dump_parse_reset_info( dump_reset_log_t* dump_reset_info, dump_except_info_t dump_except_info);
void bsp_dump_get_reset_module(dump_except_info_t dump_except_info, u8* task_name,u8 *module);
void bsp_dump_get_reset_task(dump_except_info_t dump_except_info,  u8 *task_name, u32 *reboot_int);
void bsp_dump_get_reset_context(u32 *reboot_context, u32 reboot_core);
void bsp_dump_get_reset_voice(u32 voice, u8 * reboot_voice);
void bsp_dump_get_reset_reason(u32 reason, u8 * reboot_reason);
void bsp_dump_get_reset_modid(u32 reason, u32 reboot_modid, u32 * modId);
void bsp_dump_get_reset_ccore(u32 core, char *reboot_core);
s32 bsp_dump_mark_voice(u32 flag);
dump_product_type_t dump_get_product_type(void);
#ifdef __OS_RTOSCK__

BOOL dump_exc_hook_earlier(EXC_INFO_S *pstExcInfo);
#endif


#else

static void inline system_error (u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length)
{
    return ;
}
static s32 inline bsp_dump_init(void)
{
    return 0;
}

static dump_handle inline bsp_dump_register_hook(char * name, dump_hook func)
{
    return 0;
}

static s32 inline bsp_dump_unregister_hook(dump_handle handle)
{
    return 0;
}

static inline u8 * bsp_dump_register_field(u32 mod_id, char * name, void * virt_addr, void * phy_addr, u32 length, u16 version)
{
    return BSP_NULL;
}

static inline u8 * bsp_dump_get_field_addr(u32 field_id)
{
	return 0;
}

static inline u8 * bsp_dump_get_field_phy_addr(u32 field_id)
{
    return 0;
}

static s32 inline bsp_dump_register_sysview_hook(dump_sysview_t mod_id, dump_hook func)
{
    return 0;
}


static void inline bsp_dump_trace_stop(void)
{
    return;
}

static void inline bsp_dump_init_task_name(void)
{
    return;
}

static void inline bsp_om_save_reboot_log(const char * func_name,  const void* caller)
{
    return;
}


/* dump�����ں��޸� begin */
static void inline dump_set_exc_vec(u32 vec)
{
    return;
}

static void inline dump_int_enter(u32 dir, u32 irq_num)
{
    return;
}

static void inline dump_int_exit(u32 dir, u32 irq_num)
{
    return;
}

static int inline dump_stack_trace_print(unsigned long where)
{
    return -1;
}
/* dump�����ں��޸� end */

static s32 inline dump_exc_register(exc_hook func)
{
    return 0;
}
static void inline bsp_ccore_wdt_register_hook(void)
{
    return;
}

static void bsp_dump_init_phase2(void)
{
    return;
}


#endif

#ifdef __OS_RTOSCK__
BOOL bsp_rtosck_exc_hook(EXC_INFO_S *pstExcInfo);
#endif

/*****************************************************************************
  4 ����������
*****************************************************************************/
#define BSP_ERR_DUMP_BASE               (int)(0x80000000 | (BSP_DEF_ERR(BSP_MODU_DUMP, 0)))
#define BSP_ERR_DUMP_INIT_FAILED        (BSP_ERR_DUMP_BASE + 0x1)
#define BSP_ERR_DUMP_INVALID_MODULE     (BSP_ERR_DUMP_BASE + 0x1)
#define BSP_ERR_DUMP_INVALID_FILE       (BSP_ERR_DUMP_BASE + 0x2)
#define BSP_ERR_DUMP_INVALID_PARAM      (BSP_ERR_DUMP_BASE + 0x3)
#define BSP_ERR_DUMP_NO_BUF             (BSP_ERR_DUMP_BASE + 0x4)
#define BSP_ERR_DUMP_SOCP_ERR           (BSP_ERR_DUMP_BASE + 0x5)


#ifdef __cplusplus
}
#endif


#endif


