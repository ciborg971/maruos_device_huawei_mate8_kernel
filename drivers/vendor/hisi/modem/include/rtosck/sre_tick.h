/**
 * @file sre_tick.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������Tick�жϵĶ���ͷ�ļ��� \n
 */

 /** @defgroup SRE_tick Tick�ж�
 *@ingroup SRE_interrupt
 */

#ifndef _SRE_TICK_H
#define _SRE_TICK_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_tick
 * Tick�ж�ģ��������Ϣ�Ľṹ�嶨�塣
 *
 * ����Tick�ж�ģ�����������Ϣ��
 */
typedef struct tagTickModInfo
{
    UINT32 uwTickPerSecond;                                 /**< ÿ�������TICK�ж���       */
} TICK_MOD_INFO_S;

/**
 * @ingroup SRE_tick
 * Tick�жϴ����룺tick������Ӳ����ʱ��������Դʱ��Դ���㣬���벻����
 *
 * ֵ: 0x02000b02
 *
 * �������:ȷ�����㹻�Ķ�ʱ��������Դ
 */
#define OS_ERRNO_TICK_NO_HWTIMER                            SRE_ERRNO_OS_ERROR(OS_MID_TICK, 0x02)

/**
 * @ingroup SRE_tick
 * Tick�жϴ����룺Cortex-AXƽ̨�ڵ���Tick����ֵʱ������Ĳ���ֵ�ܴ�СΪ��ֵ�Ҿ���ֵ����������Tick����ֵ��
 *
 * ֵ: 0x02000b03
 *
 * �������:ȷ������Tick����ֵʱ������Ĳ���ֵ�ܴ�СΪ��ֵʱ�����ľ���ֵ���ܴ���������Tick����ֵ
 */
#define OS_ERRNO_TICK_ADJUST_VALUE_INVALID                  SRE_ERRNO_OS_ERROR(OS_MID_TICK, 0x03)

/**
 * @ingroup SRE_tick
 * Tick�жϴ����룺Cortex-MX tick�����ڴ���
 *
 * ֵ: 0x02000b04
 *
 * �������:ȷ�Ͼ���ת�����tick����(����cycle/tick)�Ƿ�����(0,0x00FFFFFF]�ڡ�
 */
#define OS_ERRNO_TICK_PERIOD                                SRE_ERRNO_OS_ERROR(OS_MID_TICK, 0x04)

/**
 * @ingroup SRE_tick
 * Tick�жϴ����룺ÿ���Tick�жϼ������ò��Ϸ���
 *
 * ֵ: 0x02000b05
 *
 * �������:ȷ�����õ�ÿ��Tick�жϼ���С��ϵͳʱ���������Ҳ�����0��
 */
#define OS_ERRNO_TICK_PER_SECOND_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_TICK, 0x05)

/**
 * @ingroup  SRE_tick
 * @brief Tick�жϴ�������
 *
 * @par ����:
 * Tick�жϴ�������
 *
 * @attention
 * <ul>
 * <li>��ǰ��Cortex-AXƽ̨��Ч��</li>
 * <li>ֻ����Tick�ж�Դ���û��ṩ������Tick�жϴ����е�����Ч�����ڷ�tick�жϴ������е��ã���������tickʱ�Ӳ�׼ȷ</li>
 * <li>Tickģ��ü�����δ�򿪣����ô˽ӿ���Ч��</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval �ޡ�
 * @par ����:
 * <ul><li>sre_tick.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern VOID SRE_TickISR(VOID);

/**
 * @ingroup  SRE_tick
 * @brief ��ȡÿ���Ӷ�Ӧ��Tick����
 *
 * @par ����:
 * ��ȡÿ����ʱ���ڴ�����Tick�жϴ�����
 *
 * @attention ��
 *
 * @param  ��
 *
 * @retval #[0,0xFFFFFFFF]  ÿ���Ӷ�Ӧ��Tick����
 * @par ����:
 * <ul><li>sre_tick.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since UniDSP V100R001C01
 * @see SRE_TickCountGet
 */
extern UINT32 SRE_TickPerSecondGet(VOID);

/**
 * @ingroup  SRE_tick
 * @brief ����Tick����ֵ��
 *
 * @par ����:
 * ����Tick����ֵ��
 *
 * @attention
 * �ù��ܽӿڽ���ͳ��ʹ�ã�ֻӰ��SRE_TickCountGet����ֵ��������������Ϊ���ƣ�����Ӱ��Task Delay�������ʱ�����ź���/��Ϣ/ʱ����ʱ�ȴ�����
 *
 * @param  swTick [IN] ����#INT32��Tick��������ֵ��ȡֵ��Χ[-2^31,2^31 - 1]��
 *
 * @retval #OS_ERRNO_TICK_ADJUST_VALUE_INVALID  0x02000b03    Tick�����ܲ���ֵΪ���������Ҿ���ֵ����ʵ�ʵ�Tick����ֵ��
 * @retval #SRE_OK                              0x00000000    ����Tick����ֵ�ɹ���
 * @par ����:
 * <ul><li>sre_tick.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_TickCountGet
 */
extern UINT32 SRE_TickCountAdjust(INT32 swTick);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_TICK_H */


