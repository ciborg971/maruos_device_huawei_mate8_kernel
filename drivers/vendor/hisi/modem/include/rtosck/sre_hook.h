/**
 * @file sre_hook.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * �������ں˹���ͷ�ļ��� \n
 */

 /**
 *@defgroup  SRE_hook  ���ӹ���
 *@ingroup SRE_kernel
*/

#ifndef _SRE_HOOK_H
#define _SRE_HOOK_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_hook
 * HOOK�����룺HOOK���ʹ���
 *
 * ֵ: 0x02001600
 *
 * ���������ȷ�����빳���Ƿ�Ϊ��Ч��OS_HOOK_TYPE_E���͡�
 */
#define OS_ERRNO_HOOK_TYPE_INVALID   SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x00)

/**
 * @ingroup SRE_hook
 * HOOK�����룺�ڴ治�㡣
 *
 * ֵ: 0x02001601
 *
 * �������������ȱʡ������С��
 */
#define OS_ERRNO_HOOK_NO_MEMORY     SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x01)

/**
 * @ingroup SRE_hook
 * HOOK�����룺HOOKָ��ա�
 *
 * ֵ: 0x02001602
 *
 * ��������������εĹ��ӣ�NULLָ�벻���������ӻ�ɾ����
 */
#define OS_ERRNO_HOOK_PTR_NULL      SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x02)

/**
 * @ingroup SRE_hook
 * HOOK�����룺HOOK�Ѵ��ڡ�
 *
 * ֵ: 0x02001603
 *
 * ���������ȷ�ϸù���֮ǰ�Ƿ��Ѿ��ɹ�ע�ᣬ�����ٴ�ע��ʧ�ܡ�
 */
#define OS_ERRNO_HOOK_EXISTED       SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x03)

/**
 * @ingroup SRE_hook
 * HOOK�����룺HOOK������
 *
 * ֵ: 0x02001604
 *
 * ��������������͹����Ѿ�ע�����������������ã���ɾ��һ���ֹ��ӡ�
 */
#define OS_ERRNO_HOOK_FULL          SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x04)

/**
 * @ingroup SRE_hook
 * HOOK�����룺HOOK�����ڡ�
 *
 * ֵ: 0x02001605
 *
 * ���������ȷ�ϸù���֮ǰ�Ƿ��Ѿ��ɹ�ע�ᡣ
 */
#define OS_ERRNO_HOOK_NOT_EXISTED   SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x05)

/**
 * @ingroup SRE_hook
 * HOOK�����룺HOOK���ø���Ϊ0��
 *
 * ֵ: 0x02001606
 *
 * ��������������͹��Ӹ�������Ϊ0����ӻ���ɾ��ĳ���͹���ǰ����Ҫ�ȶ������������ȷ���á�
 */
#define OS_ERRNO_HOOK_NOT_CFG       SRE_ERRNO_OS_ERROR(OS_MID_HOOK, 0x06)


/**
 * @ingroup SRE_hook
 * �û���ʹ�ù�������ö�١�
 */
typedef enum
{
    OS_HOOK_HWI_ENTRY = 0,       /**< Ӳ�жϽ��빳��  */
    OS_HOOK_HWI_EXIT,            /**< Ӳ�ж��˳�����  */

    OS_HOOK_SWI_ENTRY,           /**< ���жϽ��빳��  */
    OS_HOOK_SWI_EXIT,            /**< ���ж��˳�����  */

    OS_HOOK_TSK_CREATE,          /**< ���񴴽�����    */
    OS_HOOK_TSK_DELETE,          /**< ����ɾ������    */
    OS_HOOK_TSK_SWITCH,          /**< �����л�����    */

    OS_HOOK_IDLE_PERIOD,         /**< IDLE����        */
    OS_HOOK_LAST_WORDS,          /**< �������Թ���    */

    OS_HOOK_TYPE_NUM             /**< ��������        */
}OS_HOOK_TYPE_E;


/**
 * @ingroup SRE_hook
 * ����ģ��������Ϣ�Ľṹ�嶨�塣
 */
typedef struct tagOSHookModInfo
{
    UINT8 aucMaxNum[OS_HOOK_TYPE_NUM];
}HOOK_MOD_INFO_S;


/**
*@ingroup SRE_hook
*
*@brief ����ں˹��ӡ�
*
*@par ����:
* ���ָ�����͵��ں˹��ӣ��ں�����Ӧ�Ĵ������й��ӻص���
*@attention ��ӹ�����Ŀ���ܴ��ڶ�Ӧ���;�̬����(OS_HOOK_XXX_NUM)�����ֵ�����û�о�̬�����Ĭ��֧��1����
*
*@param enHookType [IN] ����#OS_HOOK_TYPE_E����ӹ������͡�
*@param pfnHook [IN] ����#OS_VOID_FUNC����ӹ���ָ�롣
*
*@retval #OS_ERRNO_HOOK_TYPE_INVALID   0x02001600������������Ч��
*@retval #OS_ERRNO_HOOK_PTR_NULL       0x02001602������ָ��Ϊ�ա�
*@retval #OS_ERRNO_HOOK_EXISTED        0x02001603�������Ѿ����ڡ�
*@retval #OS_ERRNO_HOOK_FULL           0x02001604������������
*@retval #OS_ERRNO_HOOK_NOT_CFG        0x02001606�����Ӹ�������Ϊ0��
*@retval #SRE_OK                       0x00000000����ӹ��ӳɹ���
*@par ����:
*<li>sre_hook.h���ýӿ��������ڵ�ͷ�ļ���</li>
*@since RTOSck V100R002C00
*@see SRE_HookDel
*/
extern UINT32 SRE_HookAdd(OS_HOOK_TYPE_E enHookType, OS_VOID_FUNC pfnHook);


/**
*@ingroup SRE_hook
*
*@brief ɾ���ں˹��ӡ�
*
*@par ����:
* ɾ��ָ�����͵��ں˹��ӡ�
*@attention
*
*@param enHookType [IN] ����#OS_HOOK_TYPE_E����ɾ���������͡�
*@param pfnHook [IN] ����#OS_VOID_FUNC����ɾ������ָ�롣
*
*@retval #OS_ERRNO_HOOK_TYPE_INVALID   0x02001600������������Ч��
*@retval #OS_ERRNO_HOOK_PTR_NULL       0x02001602������ָ��Ϊ�ա�
*@retval #OS_ERRNO_HOOK_NOT_EXISTED    0x02001605�����Ӳ����ڡ�
*@retval #OS_ERRNO_HOOK_NOT_CFG        0x02001606�����Ӹ�������Ϊ0��
*@retval #SRE_OK                       0x00000000��ɾ�����ӳɹ���
*@par ����:
*<li>sre_hook.h���ýӿ��������ڵ�ͷ�ļ���</li>
*@since RTOSck V100R002C00
*@see SRE_HookAdd
*/
extern UINT32 SRE_HookDel(OS_HOOK_TYPE_E enHookType, OS_VOID_FUNC pfnHook);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HOOK_H */

/*
 * History: \n
 * 2013-3-22, Create this file. \n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

