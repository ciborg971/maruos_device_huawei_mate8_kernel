/**
 * @file sre_hwi.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������Ӳ�ж�ģ��Ķ���ͷ�ļ��� \n
 */

 /**@defgroup SRE_interrupt �ж�
   *@ingroup SRE_kernel
 */
 /** @defgroup SRE_hwi Ӳ�ж�
  *@ingroup SRE_interrupt
 */

#ifndef _SRE_HWI_H
#define _SRE_HWI_H

#include "sre_base.h"
#include "sre_hook.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_hwi
 * ���õ�Ӳ�ж����ȼ��ĺ궨�塣
 *
 * SD6108��SD6181�����ȼ�Ϊ1-6��SD6182/SD6157�����ȼ�Ϊ1-5����ֵԽ�����ȼ�Խ�ߣ�Tensilicaƽ̨�����ȼ���Ӳ���̶���
 * ��Cortex-AX�����ȼ�Ϊ0-31��SD6183�����ȼ�Ϊ1-7��
 *
 *
 * N: Invalid Priority
 * Y: Valid Priority
 * NMI: Non-Maskable Interrupt
 */
 /*************************************************<SD6108/6181>*****<SD6182/SD6157>*****<SD6183>*****<Cortex-AX>***/
#define SRE_HWI_PRIORITY0             0    /*       N                 N                   Y            Y           */
#define SRE_HWI_PRIORITY1             1    /*       Y                 Y                   Y            Y           */
#define SRE_HWI_PRIORITY2             2    /*       Y                 Y                   Y            Y           */
#define SRE_HWI_PRIORITY3             3    /*       Y                 Y                   Y            Y           */
#define SRE_HWI_PRIORITY4             4    /*       Y                 Y                   Y            Y           */
#define SRE_HWI_PRIORITY5             5    /*       Y                 NMI                 Y            Y           */
#define SRE_HWI_PRIORITY6             6    /*       NMI               N                   Y            Y           */
#define SRE_HWI_PRIORITY7             7    /*       N                 N                   Y            Y           */
#define SRE_HWI_PRIORITY8             8    /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY9             9    /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY10            10   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY11            11   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY12            12   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY13            13   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY14            14   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY15            15   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY16            16   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY17            17   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY18            18   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY19            19   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY20            20   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY21            21   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY22            22   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY23            23   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY24            24   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY25            25   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY26            26   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY27            27   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY28            28   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY29            29   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY30            30   /*       N                 N                   N            Y           */
#define SRE_HWI_PRIORITY31            31   /*       N                 N                   N            Y           */

/**
 * Ӳ�ж�ģʽ�ĺ궨�塣
 */

/**
 * @ingroup SRE_hwi
 * �����Ӳ�жϡ�
 */
#define OS_HWI_MODE_COMBINE                                 0x8000

/**
 * @ingroup SRE_hwi
 * ������Ӳ�жϡ�
 */
#define OS_HWI_MODE_ENGROSS                                 0x4000

/**
 * @ingroup SRE_hwi
 * ȱʡӲ�ж�ģʽ��
 */
#define OS_HWI_MODE_DEFAULT                                 OS_HWI_MODE_ENGROSS

/**
 * @ingroup SRE_hwi
 * ��Ϊʹ�ܻ���������Ӳ�жϺ�������Σ���Tensilicaƽ̨��Ч��
 */
#define OS_HWI_ALL                                          0x7fff

/*
 * Ӳ�ж�ģ��Ĵ����붨�塣
 */

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺�жϺŷǷ���
 *
 * ֵ: 0x02001400
 *
 * ���������ȷ���жϺźϷ���Tensilica:[0,31]��Cortex-AXƽ̨Balong��Ʒ:[0,255]��Cortex-AXƽ̨ISP��Ʒ:[0,511]��SD6183:[34,51],[55,58],[64,103],[124,127]��
 */
#define OS_ERRNO_HWI_NUM_INVALID                            SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x00)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺���ȼ��Ƿ���
 *
 * ֵ: 0x02001401
 *
 * ���������ȷ�����ȼ��Ϸ���Tensilica:���ȼ����ԣ�Cortex-AX:[0,31]��SD6183:[1,7]��
 */
#define OS_ERRNO_HWI_PRI_ERROR                              SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x01)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺Ӳ�ж��ѱ���������Ӧ�ж��������ѱ������ж�ռ�á�
 *
 * ֵ: 0x02001402
 *
 * ��������������жϺ�
 */
#define OS_ERRNO_HWI_ALREADY_CREATED                        SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x02)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺Ӳ�жϴ�����Ϊ�ա�
 *
 * ֵ: 0x02001403
 *
 * �������������ǿյ���Ч������
 */
#define OS_ERRNO_HWI_PROC_FUNC_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x03)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺δ������Ӳ�жϱ���Ӧ��
 *
 * ֵ: 0x03001404
 *
 * ����������ȴ���Ӳ�жϣ�Ȼ��ʹ�ܲ��������ж�ʹ��õ���Ӧ
 */
#define OS_ERRNO_HWI_UNCREATED                              SRE_ERRNO_OS_FATAL(OS_MID_HWI, 0x04)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺ɾ��TICK�жϡ�
 *
 * ֵ: 0x02001405
 *
 * ���������������ɾ��tick�ж�
 */
#define OS_ERRNO_HWI_DELETE_TICK_INT                        SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x05)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺����Ӳ�ж�����ʱ������������֮ǰ����ֵ��һ��
 *
 * ֵ: 0x02001406
 *
 * ���������ȷ�ϵ�ǰ��������ֵ��֮ǰ�Ƿ�һ�¡����ȷ���޸����ԣ�����ɾ����Ӳ�жϡ�
 */
#define OS_ERRNO_HWI_ATTR_CONFLICTED                        SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x06)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺������жϴ���ʧ�ܣ�Ϊ������жϽڵ�����ϵͳĬ��˽��FSC�ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02001408
 *
 * �������: ����ϵͳĬ��˽��FSC������С
 */
#define OS_ERRNO_HWI_MEMORY_ALLOC_FAILED                    SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x08)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺������жϺ���ע��ʧ�ܣ���������ж��Ѵ�������ͬ���жϴ�������
 *
 * ֵ: 0x02001409
 *
 * �������: �����жϴ�����
 */
#define OS_ERRNO_HWI_COMBINEHOOK_ALREADY_CREATED            SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x09)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺�������жϺ��������Ƕ����ͣ�Ҳ��������ͣ�����SD6183ƽ̨���õ��ж�ģʽ�Ȳ��Ǳ�����Ҳ���ǵ�ƽ�͡�
 *
 * ֵ: 0x0200140a
 *
 * �������: Ӳ�ж�ģʽֻ������Ϊ�����ͻ�����ͣ�����SD6183ƽ̨���õ��ж�ģʽ�����Ǳ����ͻ��ߵ�ƽ��
 */
#define OS_ERRNO_HWI_MODE_ERROR                             SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x0a)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺ɾ��δ���������Ѿ���ɾ����Ӳ�жϡ�
 *
 * ֵ: 0x0200140b
 *
 * �������: ɾ���Ѵ�������δ��ɾ����Ӳ�ж�
 */
#define OS_ERRNO_HWI_DELETED                                SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x0b)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺δ����Ӳ�ж�ģʽ���á�
 *
 * ֵ: 0x0200140c
 *
 * �������: �����жϴ�������ǰ����Ҫ�ȵ����ж�ģʽ���ú���������ģʽ��������
 */
#define OS_ERRNO_HWI_MODE_UNSET                             SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x0c)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺Ӳ�жϴ����ӿ���δ���������Ч�ĺ˺š�
 *
 * ֵ: 0x0200140d
 *
 * �������: ���뱾�˺˺�
 */
#define OS_ERRNO_HWI_CORE_ID_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x0d)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺Ӳ�ж�������ɴ�����
 *
 * ֵ: 0x0200140e
 *
 * �������: SD6182��CPU,DSP,HAC CC�ˣ�SD6157��CPU,DSP�˼�SD6181/SD6108��CPU��ֻ��7�ſ������������SD6181/SD6108��DSP��7����11�ſ������������SD6183ƽ̨124~127�ſ����������
 */
#define OS_ERRNO_HWI_NUM_NOT_SOFT_TRIGGERD                  SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x0e)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺ɾ��SD6182/SD6157/SD6183 MSGM�е�HPQ�жϡ�
 *
 * ֵ: 0x0200140f
 *
 * ���������SD6182/SD6157/SD6183 MSGM�е�HPQ�ж�ΪOS�ڲ�ʹ�ã�����ɾ����
 */
#define OS_ERRNO_HWI_DELETE_MSGM_HPQ_INT                    SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x0f)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺Cortex-AXӲ���ϱ������жϣ��ϱ����жϺŴ���0x1FF��
 *
 * ֵ: 0x02001410
 *
 * ����������ޡ�
 */
#define OS_ERRNO_HWI_HW_REPORT_HWINO_INVALID                SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x10)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ����룺���Ϊ��
 *
 * ֵ: 0x02001411
 *
 * ����������ޡ�
 */
#define OS_ERRNO_HWI_PARAM_NULL                             SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x11)

/**
 * @ingroup SRE_hwi
 * Ӳ�жϺŵ����Ͷ��塣
 */
typedef UINT32                                              HWI_HANDLE_T;

/**
 * @ingroup SRE_hwi
 * Ӳ�ж����ȼ������Ͷ��塣
 */
typedef UINT16                                              HWI_PRIOR_T;

/**
 * @ingroup SRE_hwi
 * Ӳ�ж�ģʽ������Ϣ�����Ͷ��塣
 */
typedef UINT16                                              HWI_MODE_T;

/**
 * @ingroup SRE_hwi
 * Ӳ�жϴ������Ĳ������Ͷ��塣
 */
typedef UINT32                                              HWI_ARG_T;

/**
* @ingroup  SRE_hwi
* @brief Ӳ�жϴ����������Ͷ��塣
*
* @par ����:
* ͨ��Ӳ�жϴ����������Ͷ���Ӳ�жϴ���������Ӳ�жϴ���ʱ���ø��жϴ�������
*
* @attention �ޡ�
*
* @param  uwParam1 [IN] ����#HWI_ARG_T��Ӳ�жϴ������Ĳ�����
*
* @retval �ޡ�
* @par ����:
* <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
* @see �ޡ�
*/
typedef VOID (* HWI_PROC_FUNC)(HWI_ARG_T);


/**
* @ingroup  SRE_hwi
* @brief Ӳ�жϵ��ô��������Ӻ������Ͷ��塣
*
* @par ����:
* �û�ͨ��Ӳ�жϵ��ù��Ӵ��������Ͷ���Ӳ�жϵ��ô��������ӣ���Ӳ�жϵ��ô�����ʱ�����øù��ӡ�
* @attention �ޡ�
*
* @param  uwHwiNum [IN] ����#UINT32��Ӳ�жϺš�
*
* @retval �ޡ�
* @par ����:
* <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R002C00
* @see SRE_HwiEntryHookAdd | SRE_HwiEntryHookDel | SRE_HookAdd | SRE_HookDel
*/
typedef VOID (* HWI_ENTRY_HOOK)(UINT32 uwHwiNum);

/**
* @ingroup  SRE_hwi
* @brief Ӳ�ж��˳����������Ӻ������Ͷ��塣
*
* @par ����:
* �û�ͨ��Ӳ�ж��˳����Ӵ��������Ͷ���Ӳ�ж��˳����������ӣ���Ӳ�ж��˳�������ʱ�����øù��ӡ�
* @attention �ޡ�
*
* @param  uwHwiNum [IN] ����#UINT32��Ӳ�жϺš�
*
* @retval �ޡ�
* @par ����:
* <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R002C00
* @see SRE_HwiExitHookAdd | SRE_HwiExitHookDel | SRE_HookAdd | SRE_HookDel
*/
typedef VOID (* HWI_EXIT_HOOK)(UINT32 uwHwiNum);

/**
 * @ingroup  SRE_hwi
 * @brief ����Ӳ�ж����Խӿڡ�
 *
 * @par ����:
 * �ڴ���Ӳ�ж�ǰ������Ҫ���ú�Ӳ�жϵ����ȼ���ģʽ�����������ͣ�#OS_HWI_MODE_ENGROSS��������ͣ�#OS_HWI_MODE_COMBINE����������ģʽ��
 *
 * @attention
 * <ul>
 * <li>Tensilica�µ�SD6181, SD6108, SD6182, SD6157оƬ������Ӳ�жϺ�Ϊ0-31��OS�Ѿ�ռ�õĲ��ܱ�ʹ��(����SD6182ƽ̨��1���ж����ڴ����жϣ�9���ж�����WriteError��28���ж�����MSGM������Tickģ�飬6���ж�����Tick;����SD6183ƽ̨��48��50���ж�����CACHE��51���ж�����MMU��64���ж����ڴ����жϣ�72��73���ж�����Ӳ���ź���)��</li>
 * <li>����Tensilicaƽ̨��Ӳ�ж����ȼ���Ӳ���̶������ȼ����ò���#usHwiPrio��Ч��</li>
 * <li>Cortex-AXƽ̨��Balong��Ʒ����Ӳ�жϺ�Ϊ0-255,ISP��Ʒ����Ӳ�жϺ�Ϊ0-511�����ȼ���Ϊ0-31��</li>
 * <li>SD6183ƽ̨�¿���Ӳ�жϺ�Ϊ34-51,55-58,64-103,124-127�����ȼ�1-7������Խ�����ȼ�Խ�ߡ�</li>
 * </ul>
 *
 * @param  uwHwiNum  [IN] ����#HWI_HANDLE_T��Ӳ�жϺš�
 * @param  usHwiPrio [IN] ����#HWI_PRIOR_T��Ӳ�ж����ȼ���
 * @param  usMode    [IN] ����#HWI_MODE_T�����õ��ж�ģʽ��Ϊ������(#OS_HWI_MODE_ENGROSS)���������(#OS_HWI_MODE_COMBINE)��
 *
 * @retval #OS_ERRNO_HWI_NUM_INVALID                     0x02001400���жϺŷǷ���
 * @retval #OS_ERRNO_HWI_PRI_ERROR                       0x02001401�����ȼ��Ƿ���
 * @retval #OS_ERRNO_HWI_MODE_ERROR                      0x0200140a���������жϺ��������Ƕ����ͣ�Ҳ��������͡�
 * @retval #OS_ERRNO_HWI_ATTR_CONFLICTED                 0x02001406�������ظ����ó�ͻ��
 * @retval #SRE_OK                                       0x00000000��Ӳ�жϴ����ɹ���
 * @par ����:
 * <ul><li>SRE_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwiCreate
 **/
extern UINT32 SRE_HwiSetAttr(HWI_HANDLE_T uwHwiNum,
                             HWI_PRIOR_T usHwiPrio,
                             HWI_MODE_T usMode);

/**
 * @ingroup  SRE_hwi
 * @brief ����Ӳ�жϺ�����
 *
 * @par ����:
 * ע��Ӳ�жϵĴ�������
 *
 * @attention
 * <ul>
 * <li>�ڵ��øú���֮ǰ������ȷ���Ѿ��������ж����ԡ�</li>
 * <li>Tensilicaƽ̨�µ�SD6181, SD6108, SD6182, SD6157оƬ������Ӳ�жϺ�Ϊ0-31��</li>
 * <li>Cortex-AXƽ̨��Balong��Ʒ����Ӳ�жϺ�Ϊ0-255,ISP��Ʒ����Ӳ�жϺ�Ϊ0-511�����ȼ���Ϊ0-31��</li>
 * <li>SD6183ƽ̨�¿���Ӳ�жϺ�Ϊ34-51,55-58,64-103,124-127,���ȼ�1-7��</li>
 * <li>Ӳ�жϴ����ɹ��󣬲���ʹ����Ӧ�������жϣ���Ҫ��ʽ����#SRE_HwiEnable����ʹ�ܡ�</li>
 * </ul>
 *
 * @param  uwHwiNum   [IN] ����#HWI_HANDLE_T��Ӳ�жϺš�
 * @param  pfnHandler [IN] ����#HWI_PROC_FUNC��Ӳ�жϴ���ʱ�Ĵ�������
 * @param  uwArg      [IN] ����#HWI_ARG_T������Ӳ�жϴ�����ʱ���ݵĲ�����
 *
 * @retval #OS_ERRNO_HWI_NUM_INVALID                     0x02001400���жϺŷǷ���
 * @retval #OS_ERRNO_HWI_PROC_FUNC_NULL                  0x02001403��Ӳ�жϴ�����Ϊ�ա�
 * @retval #OS_ERRNO_HWI_MODE_UNSET                      0x0200140c��δ����Ӳ�ж�ģʽ���á�
 * @retval #OS_ERRNO_HWI_MEMORY_ALLOC_FAILED             0x02001408��������жϽڵ�����˽�о�̬�ڴ�ʧ��
 * @retval #OS_ERRNO_HWI_COMBINEHOOK_ALREADY_CREATED     0x02001409��������ж��Ѵ�������ͬ���жϴ�������
 * @retval #OS_ERRNO_HWI_ALREADY_CREATED                 0x02001402��Ӳ�ж��ѱ���������Ӧ�ж��������ѱ������ж�ռ�á�
 * @retval #SRE_OK                                       0x00000000��Ӳ�жϴ����ɹ���
 * @par ����:
 * <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwiDelete
 **/
extern UINT32 SRE_HwiCreate(HWI_HANDLE_T  uwHwiNum,
                            HWI_PROC_FUNC pfnHandler,
                            HWI_ARG_T     uwArg);

/**
 * @ingroup  SRE_hwi
 * @brief ɾ��Ӳ�жϺ�����
 *
 * @par ����:
 * ������ӦӲ�жϻ��¼���ȡ��Ӳ�жϴ�������ע�ᡣ
 *
 * @attention
 * <ul>
 * <li>Tensilica�µ�SD6181, SD6108, SD6182, SD6157оƬ������Ӳ�жϺ�Ϊ0-31��</li>
 * <li>����ɾ��OSռ�õ��жϺš�</li>
 * <li>Cortex-AXƽ̨��Balong��Ʒ����Ӳ�жϺ�Ϊ0-255,ISP��Ʒ����Ӳ�жϺ�Ϊ0-511��</li>
 * <li>SD6183�¿���Ӳ�жϺ�Ϊ34-51,55-58,64-103,124-127��</li>
 * </ul>
 *
 * @param  uwHwiNum [IN] ����#HWI_HANDLE_T��Ӳ�жϺš�
 *
 * @retval #OS_ERRNO_HWI_NUM_INVALID            0x02001400���жϺŷǷ���
 * @retval #OS_ERRNO_HWI_DELETE_TICK_INT        0x02001405��ɾ��TICK�жϡ�
 * @retval #OS_ERRNO_HWI_DELETE_MSGM_HPQ_INT    0x0200140f��ɾ��SD6182/SD6157/SD6183 MSGM�е�HPQ�жϡ�
 * @retval #OS_ERRNO_HWI_DELETED                0x0200140b��ɾ��δ������Ӳ�жϡ�
 * @retval #SRE_OK                              0x00000000��Ӳ�ж�ɾ���ɹ���
 * @par ����:
 * <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwiCreate
 */
extern UINT32 SRE_HwiDelete(HWI_HANDLE_T uwHwiNum);

/**
* @ingroup  SRE_hwi
* @brief ��ԭָ���жϺŵ��ж�ʹ�ܼĴ�����ֵ��
*
* @par ����:
* ��֮ǰ����#SRE_HwiDisable��#SRE_HwiEnable�ķ���ֵ�����������ж�ʹ�ܼĴ�����
*
* @attention
* <ul>
* <li>�ú�����Ҫ��#SRE_HwiDisable��#SRE_HwiEnable���ʹ�á�</li>
* <li>����Tensilica������Ӳ�жϺ�Ϊ0-31��</li>
* <li>Cortex-AXƽ̨��Balong��Ʒ����Ӳ�жϺ�Ϊ0-255,ISP��Ʒ����Ӳ�жϺ�Ϊ0-511��</li>
* <li>����SD6183������Ӳ�жϺ�Ϊ34-51,55-58,64-103,124-127��</li>
* <li>Tensilica���й���:�����ΪOS_HWI_ALLʱ���ɻ�ԭ����Ӳ�жϡ�</li>
* </ul>
*
* @param  uwHwiNum  [IN] ����#HWI_HANDLE_T��Ӳ�жϺš�
* @param  uvHwiSave [IN] ����#UINTPTR���ж�ʹ�ܼĴ����ı���ֵ��
*
* @retval ��
* @par ����:
* <ul><li>SRE_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
* @see SRE_HwiEnable | SRE_HwiDisable
*/
extern VOID SRE_HwiRestore(HWI_HANDLE_T  uwHwiNum, UINTPTR  uvHwiSave);

/**
* @ingroup  SRE_hwi
* @brief ����ָ���˺��ڵ�Ӳ�жϡ�
*
* @par ����:
* ����ָ���˺��ڵ�����ɴ�����Ӳ�ж�
*
* @attention
* <ul>
* <li>���Tensilica��SD6183ƽ̨��Ч��</li>
* <li>���Cortex-AX����֧�ָýӿڡ�</li>
* </ul>
*
* @param  uwDstCore [IN] ����#UINT32�� Ŀ��˺š� Ŀǰֻ֧��ָ��Ϊ���ˡ�
* @param  uwHwiNum  [IN] ����#HWI_HANDLE_T��Ӳ�жϺţ�ֻ֧������ɴ������жϺţ�SD6182ƽ̨Ϊ7��11���жϣ�SD6183ƽ̨Ϊ124��125��126��127���жϣ���
*
* @retval #OS_ERRNO_HWI_NUM_INVALID                0x02001400���жϺŷǷ���
* @retval #OS_ERRNO_HWI_CORE_ID_INVALID            0x0200140d��������Ч�ĺ˺š�
* @retval #OS_ERRNO_HWI_NUM_NOT_SOFT_TRIGGERD      0x0200140e��������Ч���жϺţ�������ɴ�����
* @retval #SRE_OK                                  0x00000000��Ӳ�ж�����λ����ɹ���
* @par ����:
* <ul><li>SRE_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
*/
extern UINT32 SRE_HwiTrigger (UINT32 uwDstCore , HWI_HANDLE_T uwHwiNum);

/**
 * @ingroup  SRE_hwi
 * @brief ����ж�����λ��
 *
 * @par ����:
 * ������е��ж�����λ����������ǰ�Ѵ����жϵĵ���Ӧ��
 *
 * @attention
 * <ul>
 * <li>���Tensilica��SD6183ƽ̨��������е��ж�����λ(����NMI�ж���Ч)��</li>
 * <li>���Cortex-AX����֧�ָýӿڡ�</li>
 * </ul>
 *
 * @param  �ޡ�
 *
 * @retval �ޡ�
 * @par ����:
 * <ul><li>SRE_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwiClearPendingBit
 */
extern VOID SRE_ClearAllPending(VOID);

/**
 * @ingroup  SRE_hwi
 * @brief ���Ӳ�жϵ�Pendingλ��
 *
 * @par ����:
 * ��ʽ���Ӳ�жϻ��¼�������λ����Ϊ�е�Ӳ����Ӧ�жϺ󲻻��Զ���Pendingλ��
 *
 * @attention
 * <ul>
 * <li>����Tensilica���˲���Ϊ�ж�������0-31��</li>
 * <li>���Cortex-AX����֧�ָýӿڡ�</li>
 * <li>���SD6183ƽ̨���˲���Ϊ�ж�������34-51,55-58,64-103,124-127������˽ӿڶ�NMI�ж���Ч��</li>
 * </ul>
 *
 * @param  uwHwiNum [IN] ����#HWI_HANDLE_T��Ӳ�жϺš�
 *
 * @retval #OS_ERRNO_HWI_NUM_INVALID            0x02001400���жϺŷǷ���
 * @retval #SRE_OK                              0x00000000��Ӳ�ж�����λ����ɹ���
 * @par ����:
 * <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_HwiCreate
 */
extern UINT32 SRE_HwiClearPendingBit(HWI_HANDLE_T uwHwiNum);


/**
* @ingroup  SRE_hwi
* @brief ����ָ����Ӳ�жϡ�
*
* @par ����:
* ��ֹ����Ӧָ��Ӳ�жϵ�����
*
* @attention
* <ul>
* <li>����Tensilica���˲���Ϊ�ж�������0-31��</li>
* <li>����Cortex-AX��Balong��Ʒ����Ӳ�ж�������Ϊ0-255,ISP��Ʒ����Ӳ�ж�������Ϊ0-511��</li>
* <li>����SD6183���˲���Ϊ�ж�������34-51,55-58,64-103,124-127������˽ӿڶ�NMI�ж���Ч��</li>
* <li>Tensilica���й���:�����ΪOS_HWI_ALLʱ������������Ӳ�жϡ�</li>
* </ul>
*
* @param  uwHwiNum [IN] ����#HWI_HANDLE_T�����ݲ�ͬ��оƬ��Ӳ�жϺŻ��ж������ţ���ע�����
*
* @retval #OS_ERRNO_HWI_NUM_INVALID           0x02001400���жϺŷǷ���(���Cortex-AX��SD6183)
* @retval #0                                  ����ǰ���жϽ�ֹ״ֵ̬��(���Cortex-AX��SD6183)
* @retval #1                                  ����ǰ���ж�ʹ��״ֵ̬��(���Cortex-AX��SD6183)
* @retval #����ֵ                             ����ǰ���ж�ʹ�ܼĴ�����ֵ��(���Tensilica)
* @par ����:
* <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
* @see SRE_HwiEnable
*/
extern UINTPTR SRE_HwiDisable(HWI_HANDLE_T uwHwiNum);



/**
* @ingroup  SRE_hwi
* @brief ��ѯ�ж�״̬��
*
* @par ����:
* ��ѯ�ж�״̬��
*
* @attention
* <ul>
* <li>ֻ֧��6183��</li>
* <li>�������ǵ�ǰ�жϵ��ж�״̬��</li>
* </ul>
*
* @param  uwHwiNum [IN] ����#HWI_HANDLE_T�����ݲ�ͬ��оƬ��Ӳ�жϺŻ��ж������ţ���ע������
* @param  puwHwiPendingReg [OUT] ����#UINT32*����Ӧ���ж�״̬1:���жϣ�0���ж�
*
* @retval #OS_ERRNO_HWI_NUM_INVALID           0x02001400���жϺŷǷ���(���SD6183)
* @retval #OS_ERRNO_HWI_PARAM_NULL            0x02001411����ηǷ���
* @retval #SRE_OK                             0x00000000����ѯ�ɹ���
* @par ����:
* <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R003C00
* @see
*/
extern  UINT32 SRE_HwiPendingQuery(HWI_HANDLE_T uwHwiNum, UINT32 *puwHwiPendingReg);

/**
* @ingroup  SRE_hwi
* @brief ʹ��ָ����Ӳ�жϡ�
*
* @par ����:
* �������Ӧָ��Ӳ�жϵ�����
*
* @attention
* <ul>
* <li>����Tensilica���˲���Ϊ�ж�������0-31��</li>
* <li>����Cortex-AX��Balong��Ʒ����Ӳ�ж�������Ϊ0-255,ISP��Ʒ����Ӳ�ж�������Ϊ0-511��</li>
* <li>����SD6183���˲���Ϊ�ж�������34-51,55-58,64-103,124-127������˽ӿڶ�NMI�ж���Ч��</li>
* <li>Tensilica���й���:�����ΪOS_HWI_ALLʱ����ʹ������Ӳ�жϡ�</li>
* <li>���ڲ�ͬоƬ���˷���ֵ����������������죬����ϸ�ڼ����淵��ֵ˵��</li>
* </ul>
*
* @param  uwHwiNum [IN] ����#HWI_HANDLE_T�����ݲ�ͬ��оƬ��Ӳ�жϺŻ��ж������ţ���ע�����
*
* @retval #OS_ERRNO_HWI_NUM_INVALID           0x02001400���жϺŷǷ�(���Cortex-AX��SD6183)��
* @retval #0                                  ����ǰ���жϽ�ֹ״ֵ̬(���Cortex-AX��SD6183)��
* @retval #1                                  ����ǰ���ж�ʹ��״ֵ̬(���Cortex-AX��SD6183)��
* @retval #����ֵ                             ����ǰ���ж�ʹ�ܼĴ�����ֵ(���Tensilica)��
* @par ����:
* <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
* @see SRE_HwiDisable
*/
extern UINTPTR SRE_HwiEnable(HWI_HANDLE_T uwHwiNum);

/**
 * @ingroup  SRE_hwi
 * @brief ���Ӳ�жϽ��빳��
 *
 * @par ����:
 * ���Ӳ�жϽ��빳�ӡ��ù��Ӻ����ڽ���Ӳ�ж�ISRǰ�����á�
 *
 * @attention
 * <ul>
 * <li>��ͬ���Ӻ�����ִ�е��Ⱥ�˳�򣬲�Ӧ������������ϵ��</li>
 * <li>��Ӧ�ڹ��Ӻ�������ÿ��������̵߳��Ȼ�������OS�ӿڡ�</li>
 * <li>���֧�ֹ������農̬����</li>
 * </ul>
 *
 * @param  pfnHook [IN] ����#HWI_ENTRY_HOOK���жϽ��빳�Ӻ�����
 *
 * @par ����:
 * <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwiEntryHookDel | SRE_HookAdd | SRE_HwiExitHookAdd
 */
#define SRE_HwiEntryHookAdd(pfnHook) SRE_HookAdd(OS_HOOK_HWI_ENTRY, (OS_VOID_FUNC)(HWI_ENTRY_HOOK)pfnHook)

/**
 * @ingroup  SRE_hwi
 * @brief ɾ��Ӳ�жϽ��빳��
 *
 * @par ����:
 * ɾ��Ӳ�жϽ��빳�ӡ��ù��Ӻ�����ֹͣ�ڽ���Ӳ�ж�ISRǰ�ĵ��á�
 *
 * @attention
 * <ul>
 * <li>��ͬ���Ӻ�����ִ�е��Ⱥ�˳�򣬲�Ӧ������������ϵ��</li>
 * <li>��Ӧ�ڹ��Ӻ�������ÿ��������̵߳��Ȼ�������OS�ӿڡ�</li>
 * <li>���֧�ֹ������農̬����</li>
 * </ul>
 *
 * @param  pfnHook [IN] ����#HWI_ENTRY_HOOK���жϽ��빳�Ӻ�����
 *
 * @par ����:
 * <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwiEntryHookAdd | SRE_HookDel
 */
#define SRE_HwiEntryHookDel(pfnHook) SRE_HookDel(OS_HOOK_HWI_ENTRY, (OS_VOID_FUNC)(HWI_ENTRY_HOOK)pfnHook)

/**
 * @ingroup  SRE_hwi
 * @brief ���Ӳ�ж��˳�����
 *
 * @par ����:
 * ���Ӳ�ж��˳����ӡ��ù��Ӻ������˳�Ӳ�ж�ISR�󱻵��á�
 *
 * @attention
 * <ul>
 * <li>��ͬ���Ӻ�����ִ�е��Ⱥ�˳�򣬲�Ӧ������������ϵ��</li>
 * <li>��Ӧ�ڹ��Ӻ�������ÿ��������̵߳��Ȼ�������OS�ӿڡ�</li>
 * <li>���֧�ֹ������農̬����</li>
 * </ul>
 *
 * @param  pfnHook [IN] ����#HWI_EXIT_HOOK���ж��˳����Ӻ�����
 *
 * @par ����:
 * <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwiExitHookDel | SRE_HookAdd | SRE_HwiEntryHookAdd
 */
#define SRE_HwiExitHookAdd(pfnHook) SRE_HookAdd(OS_HOOK_HWI_EXIT, (OS_VOID_FUNC)(HWI_EXIT_HOOK)pfnHook)

/**
 * @ingroup  SRE_hwi
 * @brief ɾ��Ӳ�ж��˳�����
 *
 * @par ����:
 * ɾ��Ӳ�ж��˳����ӡ��ù��Ӻ�����ֹͣ���˳�Ӳ�ж�ISR��ĵ��á�
 *
 * @attention
 * <ul>
 * <li>��ͬ���Ӻ�����ִ�е��Ⱥ�˳�򣬲�Ӧ������������ϵ��</li>
 * <li>��Ӧ�ڹ��Ӻ�������ÿ��������̵߳��Ȼ�������OS�ӿڡ�</li>
 * <li>���֧�ֹ������農̬����</li>
 * </ul>
 *
 * @param  pfnHook [IN] ����#HWI_EXIT_HOOK���ж��˳����Ӻ�����
 *
 * @par ����:
 * <ul><li>sre_hwi.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_HwiExitHookAdd | SRE_HookDel
 */
#define SRE_HwiExitHookDel(pfnHook) SRE_HookDel(OS_HOOK_HWI_EXIT, (OS_VOID_FUNC)(HWI_EXIT_HOOK)pfnHook)


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HWI_H */


