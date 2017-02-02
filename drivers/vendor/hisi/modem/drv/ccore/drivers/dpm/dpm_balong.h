#ifndef __DPM_BALONG_H__
#define __DPM_BALONG_H__
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <osl_list.h>
#include <osl_types.h>
#include <osl_spinlock.h>

#ifndef OK
#define OK 0
#endif
#ifndef ERROR
#define ERROR (-1)
#endif

struct dpm_control
{
    struct list_head dpm_list;                      /*��¼��dpmģ��ע�����ģ��                 */
    struct list_head dpm_prepared_list;             /*��¼�Ѿ�prepare��resume_late����ģ��                   */
    struct list_head dpm_sus_early_list;            /*��¼�Ѿ�suspend early��resumeģ�� */
    struct list_head dpm_suspend_list;              /*��¼�Ѿ�suspend��resume early��ģ��                 */
    struct list_head dpm_late_early_list;           /*��¼�Ѿ�suspend lateģ�� */
    spinlock_t    dpm_list_mtx;                     /*������ʻ����ź���������������һ�������ź���*/
    u32  dpm_count[DPM_CALLBACK_NUM];               /*0:pre failed,1:early,2:suspend failed,3:late failed,4:total suspend,5:total resume*/
    s32  (*current_callback)(struct dpm_device *dev);
    char *device_name;                              /*��¼ģ������*/
    s32  flag;
};
#endif
