/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  reset.h    reset module interface declare
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */
#ifndef __MACH_RESET_H__
#define __MACH_RESET_H__

#include <linux/notifier.h>
#include <linux/semaphore.h>
#include "drv_global.h"
#include "drv_reset.h"
#include "drv_udi.h"
#include "drv_icc.h"
#include "hifidrvinterface.h"
/*****************************************************************************
 �궨��
*****************************************************************************/
#define RESET_CPU_CCORE_STATUS_OFF            0x00000001
#define RESET_CPU_MCU_STATUS_OFF            0x00000002
#define RESET_CPU_HIFI_STATUS_OFF            0x00000004
/*CCORE OR hifi ������λ�ܿغ�*/
#define BSP_C_HIFI_RESET_ALONE_FEATURE
#undef RESET_PRINK_TO_FILE

/*�ú����ڿ��Ʋ��Դ���*/
#define BSP_C_HIFI_RESET_ALONE_TESET_VALID
#define BSP_RESET_MAILBOX_MSG_PROTECT           0x5a5a5a5a

/*CCORE OR hifi ������λ,CCORE������Ҫ��ȫУ��*/
#undef BSP_C_HIFI_RESET_ALONE_SEC_FEATURE

#define BSP_RESET_OK                    0
#define BSP_RESET_ERROR                 (-1)

#define DRV_RESET_MODULE_NAME_LEN       9/*exclude '\0'*/
/*reference to copy from bootloader, fastboot, starts*/
#define EFI_NAMELEN     36

/*һ����Ϣ����󳤶�*/
#define     BSP_RESET_LOG_INFO_ITEM_LEN     100
/*����log��Ϣ���ļ�*/
#define     BSP_RESET_LOG_FILE      "log/record/reset_sub.txt"

/*����ص��������ȼ�*/
#define     BSP_DRV_CBFUN_PRIOLEVEL         5
/*****************************************************************************
���ݽṹ����
*****************************************************************************/
/*Record information of callback functions*/
typedef struct
{
    char		name[DRV_RESET_MODULE_NAME_LEN + 1];
    int				priolevel;
    pdrv_reset_cbfun	cbfun;
    int         userdata;
} sreset_mgr_callbackfunc;

/*Link list unit of managing all callback functions*/
typedef struct _sreset_mgr_LLI
{
    sreset_mgr_callbackfunc cbfuninfo;
    struct _sreset_mgr_LLI	*pnext;
} sreset_mgr_LLI;


typedef struct _sreset_mailbox_msg_ccore
{
    int     iproctec;
    int     idata;
    int     ireserved;
} sreset_mailbox_msg_mcu;
/*Э����ɵ�����λ���ܵ����ݶ���*/
typedef struct
{
    sreset_mailbox_msg_mcu              smailboxmsg_mcu;
    AP_HIFI_CCPU_RESET_REQ_STRU               smailboxmsg_hifi;
    int               iccore_reset;
    int               ivalue_reg1;      /*����Ĵ���ԭʼֵ���������ָ�*/
    int               ivalue_reg2;      /*����Ĵ���ԭʼֵ���������ָ�*/
    unsigned int               icpustatus;           /*ÿһλ������ʾһ��cpu״̬�����ҵ���:ccpu,mcu,hifi,0:��ʾ����������1:��ʾ�Ѿ���λ*/
	UDI_HANDLE        ccorereset_IccFd;
	ICC_CHAN_ATTR_S   attr;
	UDI_OPEN_PARAM    ccorereset_IccParam;
    struct semaphore     sem_wait_ccorereset;
    struct semaphore     sem_wait_ccorereset_ok;
    struct semaphore     sem_wait_hifireset;
    struct semaphore     sem_wait_hifi_msg;
    struct semaphore     sem_wait_mcu_msg;
} sreset_mgr_assistant;

/*****************************************************************************
ö������
*****************************************************************************/
/*��λ�����漰��ģ��*/
typedef enum
{
    BSP_RESET_MODULE_CCORE,
    BSP_RESET_MODULE_HIFI,
    BSP_RESET_MODULE_MCU,
    BSP_RESET_MODULE_ACORE,
    BSP_RESET_MODULE_INVALID
} ereset_module;

/*��λ�����漰��ģ��*/
typedef enum
{
    BSP_RESET_MCU_MSG_CCORE_TORESET,
    BSP_RESET_MCU_MSG_CCORE_AFTER_RESET,
    BSP_RESET_MCU_MSG_HIFI_TORESET,
    BSP_RESET_MCU_MSG_HIFI_AFTER_RESET,
    BSP_RESET_MCU_MSG_INVALID
} ereset_msg_with_mcu;

typedef enum 
{
    RESET_TYPE_FAILGET_MSG_FROM_MCU,  /*����c�˸�λ��û���յ�MCU��Ϣ*/
    RESET_TYPE_FAILGET_MSG_FROM_HIFI, /*����c�˸�λ��û���յ�hifi��Ϣ*/        
    RESET_TYPE_MSG_FROM_MCU_WRONG,      /*����c�˸�λ��mcu�ظ�����Ϣ����ȷ*/
    RESET_TYPE_MSG_FROM_HIFI_WRONG, /*����c�˸�λ��hifi�ظ�����Ϣ����ȷ*/
    RESET_TYPE_CRESET_RUNCB_STEP1_FAIL,   /*����c�˸�λ������ǰ���лص���������*/
    RESET_TYPE_CRESET_RUNCB_STEP2_FAIL,   /*����c�˸�λ�����غ����лص���������*/
    RESET_TYPE_CRESET_LOAD_BIN_FAIL,   /*����c�˸�λ�����س���*/
    RESET_TYPE_HIFIRESET_RUNCB_STEP1_FAIL,   /*����HIFI�˸�λ������ǰ���лص���������*/
    RESET_TYPE_HIFIRESET_RUNCB_STEP2_FAIL,   /*����HIFI�˸�λ�����غ����лص���������*/
    RESET_TYPE_HIFIRESET_LOAD_BIN_FAIL,     /*����HIFI�˸�λ�����س���*/
    RESET_TYPE_CRESET_CRUN_NO_OK,           /*c�˵�����λ���������ɹ�*/

    /*add new above,please!!*/
    RESET_TYPE_FOR_TEST,        /*���ڲ���*/
    RESET_TYPE_MAX,
} ereset_type;
/*****************************************************************************
��������
*****************************************************************************/
extern int ccorereset_loadcbin(void);
extern int ccorereset_loadbbebin(void);
extern int hifireset_loadhifibin(void);
extern void mailbox_recfun_mcu(void  *UserHandle,void *MailHandle,unsigned int MailLen);
extern void mailbox_recfun_hifi(void  *UserHandle,void *MailHandle,unsigned long MailLen);
extern sreset_mgr_LLI * reset_do_regcbfunc(sreset_mgr_LLI *plink, const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
extern int ccorereset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
extern int hifireset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
extern int ccorereset_task(void *arg);
extern int hifireset_task(void *arg);
extern int reset_sub_mgr_init (void);
extern int ccorereset_runcbfun (DRV_RESET_CALLCBFUN_MOMENT eparam);
extern int hifireset_runcbfun (DRV_RESET_CALLCBFUN_MOMENT eparam);
extern sreset_mgr_LLI * reset_link_insert(sreset_mgr_LLI *plink, sreset_mgr_LLI *punit);
extern int ccorereset_tonotify(DRV_RESET_CALLCBFUN_MOMENT eparam, ereset_module emodule);
extern int hifireset_tonotify(DRV_RESET_CALLCBFUN_MOMENT eparam, ereset_module emodule);
extern int ccorereset_setCresetFlag(void);
extern int ccorereset_doreset(void);
extern int ccorereset_dostart(void);
extern unsigned int ccorereset_icc_cok_notify(unsigned int chenalId,signed int u32size);
extern int drv_ccorereset_cbfun(DRV_RESET_CALLCBFUN_MOMENT eparam, int userdata);
extern int reset_icc_open(void);
extern int  set_for_cshell(DRV_RESET_CALLCBFUN_MOMENT eparam);
extern int  close_all_filehandle(DRV_RESET_CALLCBFUN_MOMENT eparam);
extern void  do_reset_system(int ireset_type);
extern int reset_no_ok_savelog(char *pname, int iresult, DRV_RESET_CALLCBFUN_MOMENT eparam, ereset_module emodule);
extern int reset_for_savelog(char *pstr);
extern void reset_ccore_up_semaphone(void);
extern void reset_hifi_up_semaphone(void);
extern void finish_reset_sub(void);
extern void reset_clean_wdt_int(ereset_module emodule);

/*register the notifier to the notify events below*/
int mcu_panic_regsister_notifier(struct notifier_block *n);
int modem_panic_regsister_notifier(struct notifier_block *n);
int modem_freeze_regsister_notifier(struct notifier_block *n);
int modem_reboot_regsister_notifier(struct notifier_block *n);
int hifi_freeze_regsister_notifier(struct notifier_block *n);
int android_freeze_regsister_notifier(struct notifier_block *n);
int mcu_freeze_regsister_notifier(struct notifier_block *n);
int android_reboot_regsister_notifier(struct notifier_block *n);
int wdg_rstlog_save_regsister_notifier(struct notifier_block *n);
int acpuwdg_historylog_write_regsister_notifier(struct notifier_block *n);
int mculocalwdg_historylog_write_regsister_notifier(struct notifier_block *n);
int mcuglbwdg_historylog_write_regsister_notifier(struct notifier_block *n);
int mcu_puzzle_regsister_notifier(struct notifier_block *n);

/*unregister the notifier from the notify events below*/
int mcu_panic_unregsister_notifier(struct notifier_block *n);
int modem_panic_unregsister_notifier(struct notifier_block *n);
int modem_reboot_unregsister_notifier(struct notifier_block *n);
int modem_freeze_unregsister_notifier(struct notifier_block *n);
int hifi_freeze_unregsister_notifier(struct notifier_block *n);
int android_freeze_unregsister_notifier(struct notifier_block *n);
int mcu_freeze_unregsister_notifier(struct notifier_block *n);
int android_reboot_unregsister_notifier(struct notifier_block *n);
int wdg_rstlog_save_unregsister_notifier(struct notifier_block *n);
int acpuwdg_historylog_write_unregsister_notifier(struct notifier_block *n);
int mculocalwdg_historylog_write_unregsister_notifier(struct notifier_block *n);
int mcuglbwdg_historylog_write_unregsister_notifier(struct notifier_block *n);
int mcu_puzzle_unregsister_notifier(struct notifier_block *n);
void save_mcu_log_info(void);
#endif

