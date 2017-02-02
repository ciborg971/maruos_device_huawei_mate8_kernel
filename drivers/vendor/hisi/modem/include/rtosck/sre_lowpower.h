/**
 * @file sre_lowpower.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * �������͹������ģ��Ķ���ͷ�ļ��� \n
 */

 /**@defgroup SRE_lowpower Ӳ��֧��
   *@ingroup SRE_kernel
 */

#ifndef _SRE_LOWPOWER_H
#define _SRE_LOWPOWER_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_lowpower
 *  Ӳ�������Ϣ�����룺�͹��ı�����߻ָ���������Ͳ���ȷ��
 *
 * ֵ: 0x02004001
 *
 * �������: ��ȷ����������ͺϷ���
 */
#define OS_ERRNO_LOWPOWER_TYPE_INVALID                SRE_ERRNO_OS_ERROR(OS_MID_LOWPOWER, 0x01)

/**
 * @ingroup SRE_lowpower
 *  Ӳ�������Ϣ�����룺�͹���suspend����Resume GICʱ��GICδ��ʼ����
 *
 * ֵ: 0x02004002
 *
 * �������: �͹���suspend����Resume GICʱ���뱣֤GIC�Ѿ���ʼ����
 */
#define OS_ERRNO_LOWPOWER_GIC_NOT_INIT                SRE_ERRNO_OS_ERROR(OS_MID_LOWPOWER, 0x02)

/**
 * @ingroup SRE_lowpower
 *  Ӳ�������Ϣ�����룺�͹���Suspend GICʱ��ϵͳ�Ѿ�Suspend��
 *
 * ֵ: 0x02004003
 *
 * �������: �͹���Suspend GICʱ���뱣֤ϵͳδSuspend��
 */
#define OS_ERRNO_LOWPOWER_GIC_ALREADY_SUSPENDED       SRE_ERRNO_OS_ERROR(OS_MID_LOWPOWER, 0x03)

/**
 * @ingroup SRE_lowpower
 *  Ӳ�������Ϣ�����룺�͹���Resume GICʱ��ϵͳδsuspend��
 *
 * ֵ: 0x02004004
 *
 * �������: �͹���Resume GICʱ���뱣֤ϵͳ�Ѿ�suspend��
 */
#define OS_ERRNO_LOWPOWER_GIC_NOT_SUSPENDED           SRE_ERRNO_OS_ERROR(OS_MID_LOWPOWER, 0x04)

/**
 * @ingroup SRE_lowpower
 *  Ӳ�������Ϣ�����룺�͹���Suspend GICʱ������δ������жϡ�
 *
 * ֵ: 0x02004005
 *
 * �������: �͹���Suspend GICʱ���뱣֤ϵͳ�����ж��Ѿ�������
 */
#define OS_ERRNO_LOWPOWER_GIC_PENDING_INTERRUPT       SRE_ERRNO_OS_ERROR(OS_MID_LOWPOWER, 0x05)


/**
 * @ingroup SRE_lowpower
 * �͹���suspend��resumeģ���š�
 */
typedef  enum
{
    LOW_POWER_TYPE_L2CACHE = 0,     /**< L2 Cacheģ��ID */
    LOW_POWER_TYPE_GIC,             /**< GICģ��ID      */
    LOW_POWER_TYPE_BUIT
}OS_LOW_POWER_TYPE_S;


#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup  SRE_lowpower
 * @brief �͹��ġ�
 *
 * @par ����:
 * ����enLPType�����ͣ����е͹���Suspend���Ա��������Ϣ��
 *
 * @attention
 * <ul>
 * <li>��Cortex-A9ƽ̨֧�ִ˹��ܡ�</li>
 * <li>��Ҫ�ڽ���͹���ǰ���ô˽ӿڡ�</li>
 * </ul>
 *
 * @param  enLowPowerType   [IN] ����#OS_LOW_POWER_TYPE_S���͹���suspend��resumeģ�����͡�
 *
 * @retval #OS_ERRNO_LOWPOWER_TYPE_INVALID            0x02004001������ĵ͹���suspendģ�����Ͳ��Ϸ���
 * @retval #OS_ERRNO_LOWPOWER_GIC_NOT_INIT            0x02004002���͹���Suspend GICʱ��GICδ��ʼ����
 * @retval #OS_ERRNO_LOWPOWER_GIC_ALREADY_SUSPENDED   0x02004003���͹���Suspend GICʱ��GIC�Ѿ���Suspended��
 * @retval #OS_ERRNO_LOWPOWER_GIC_PENDING_INTERRUPT   0x02004005���͹���Suspend GICʱ��ϵͳ����δ������жϡ�
 * @retval #OS_ERRNO_L2_CACHE_NOT_INIT                0x02001114��������L2 Cache��ʼ������ô˽ӿڡ�
 * @retval #OS_ERRNO_L2_CACHE_ALREADY_SUSPENDED       0x02001116��L2 Cache�Ѿ���Suspend��
 * @retval #SRE_OK                                    0x00000000���͹���Suspend�ɹ���
 * @par ����:
 * <ul><li>sre_lowpower.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see
 **/
extern UINT32 SRE_LowPowerSuspend(OS_LOW_POWER_TYPE_S enLowPowerType);

/**
 * @ingroup  SRE_lowpower
 * @brief �͹��ġ�
 *
 * @par ����:
 * ����enLPType�����ͣ����е͹���Resume���Իָ������Ϣ��
 *
 * @attention
 * <ul>
 * <li>��Cortex-A9ƽ̨֧�ִ˹��ܡ�</li>
 * <li>��Ҫ�ڻ��ѵ͹��ĺ���ô˽ӿڡ�</li>
 * </ul>
 *
 * @param  enLowPowerType   [IN] ����#OS_LOW_POWER_TYPE_S���͹���suspend��resumeģ�����͡�
 *
 * @retval #OS_ERRNO_LOWPOWER_TYPE_INVALID            0x02004001������ĵ͹���Resumeģ�����Ͳ��Ϸ���
 * @retval #OS_ERRNO_LOWPOWER_GIC_NOT_INIT            0x02004002���͹���Resume GICʱ��GICδ��ʼ����
 * @retval #OS_ERRNO_LOWPOWER_GIC_NOT_SUSPENDED       0x02004004���͹���Resume GICʱ��GICδSuspended��
 * @retval #OS_ERRNO_L2_CACHE_NOT_INIT                0x02001114��������L2 Cache��ʼ������ô˽ӿڡ�
 * @retval #OS_ERRNO_L2_CACHE_NOT_SUSPENDED           0x02001117��L2 CacheδSuspend��
 * @retval #SRE_OK                                    0x00000000���͹���Suspend�ɹ���
 * @par ����:
 * <ul><li>sre_lowpower.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see
 **/
extern UINT32 SRE_LowPowerResume(OS_LOW_POWER_TYPE_S enLowPowerType);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HW_H */


