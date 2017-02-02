/**
 * @file sre_coresleep.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * �������͹���ģ��Ķ���ͷ�ļ��� \n
 */

 /**@defgroup SRE_coresleep �͹��Ĺ���
   *@ingroup SRE_inspect
 */

#ifndef _SRE_CORESLEEP_H
#define _SRE_CORESLEEP_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_coresleep
 * �͹��Ĵ����룺���ú˵ĵ͹���ģʽ�Ƿ���
 *
 * ֵ: 0x02003a01
 *
 * �������: �˵ĵ͹��ķ�ʽֻ��ΪLOW_POWER_MODE_OFF��LOW_POWER_MODE_CORE_SLEEP��
 */
#define OS_ERRNO_POWER_MODE_INVALID                   SRE_ERRNO_OS_ERROR(OS_MID_CORESLEEP,0x01)

/**@ingroup SRE_coresleep
 * �͹��Ľṹ�嶨��
 */
typedef enum
{
    LOW_POWER_MODE_OFF,                 /**< �رյ͹���״̬     */
    LOW_POWER_MODE_CORE_SLEEP,          /**< �͹���״̬         */
    LOW_POWER_MODE_BUTT                 /**< �Ƿ�״̬           */
}OS_POWER_MODE_E;

/**
 * @ingroup  SRE_coresleep
 * @brief �͹��ķ�ʽ���á�
 *
 * @par ����:
 * ����enPowerMode���ú˵͹������з�ʽ��
 *
 * @attention
 * <ul>
 * <li>֧��Tensilica��SD6183ƽ̨��</li>
 * </ul>
 *
 * @param  enPowerMode   [IN] ����#OS_POWER_MODE_E�����ú˵͹��ķ�ʽ�����OS_POWER_MODE_E��
 *
 * @retval #OS_ERRNO_POWER_MODE_INVALID               0x02003a01�����õ͹��ķ�ʽ����ֻ������ΪLOW_POWER_MODE_OFF��LOW_POWER_MODE_CORE_SLEEP��
 * @retval #SRE_OK                                    0x00000000�����õ͹��ķ�ʽ�ɹ���
 * @par ����:
 * <ul><li>sre_coresleep.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see
 **/
extern UINT32 SRE_PowerModeSet(OS_POWER_MODE_E enPowerMode);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_CORESLEEP_H */


