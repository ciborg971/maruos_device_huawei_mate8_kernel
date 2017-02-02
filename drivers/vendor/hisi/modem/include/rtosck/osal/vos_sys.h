/**
 * @file vos_sys.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������OSALϵͳ��������ͷ�ļ��� \n
 */

/**@defgroup vos_sys ϵͳ��������
 *@ingroup OSAL
*/

#ifndef __VOS_SYS_H__
#define __VOS_SYS_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup vos_sys
 * OSAL����ϵͳʱ��Ƚϣ���һ��ʱ��ȵڶ���ʱ��С��
 */
#define COMP_TIME_LT    1

/**
 * @ingroup vos_sys
 * OSAL����ϵͳʱ��Ƚϣ���һ��ʱ����ڶ���ʱ����ȡ�
 */
#define COMP_TIME_EQ    2

/**
 * @ingroup vos_sys
 * OSAL����ϵͳʱ��Ƚϣ���һ��ʱ��ȵڶ���ʱ���
 */
#define COMP_TIME_GT    3

/**
 * @ingroup vos_sys
 * OSAL�������ݽṹ���͡�
 */
typedef struct tagDateS
{
    VOS_UINT32 d_usDate: 8;     /**< �գ�ȡֵ1-31 */
    VOS_UINT32 d_usMonth: 8;    /**< �£�ȡֵ1-12 */
    VOS_UINT32 d_usYear: 16;    /**< �꣬��1970��ʼ */
} DATE_S;

/**
 * @ingroup vos_sys
 * OSALʱ�����ݽṹ���͡�
 */
typedef struct tagTimeS
{
    VOS_UINT32 t_usSecond: 8;   /**< �룬ȡֵ0-59 */
    VOS_UINT32 t_usMinute: 8;   /**< �֣�ȡֵ0-59 */
    VOS_UINT32 t_usHour:  16;   /**< ʱ��ȡֵ0-23 */
} TIME_S;

/**
 * @ingroup vos_sys
 * OSAL����ʱ�����ݽṹ���͡�
 */
typedef struct _tagDateTime
{
    DATE_S stDate;              /**< ���ڣ������� */
    TIME_S stTime;              /**< �¼���ʱ���� */
} DATE_TIME_S;

/**
 * @ingroup  vos_sys
 * @brief ���жϡ�
 *
 * @par ����:
 * �ر�ȫ�ֿ������жϡ������������뺯����ȫ�ֱ���ʱ��Ϊ�˷�ֹ���������д��Դ��������б���������ñ��ӿڡ�
 *
 * @attention �ڹ�ȫ���жϺ󣬽�ֹ���������ں˵��ȵ���ؽӿڣ���VOS_T_Delay�ӿڡ�
 *
 * @param plRetSpl [OUT] ����#VOS_INT32 *������ر�ȫ���ж�ǰ���ж�״ֵ̬��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000�����жϳɹ���
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_SplX
 */
extern VOS_UINT32 VOS_SplImp(VOS_INT32 *plRetSpl);

/**
 * @ingroup  vos_sys
 * @brief ���жϡ�
 *
 * @par ����:
 * �ָ�ԭ�ж�״̬�Ĵ������������Կ����뺯��������Ĳ���������ñ��ӿڡ�
 *
 * @attention
 *<ul>
 *<li>�ýӿڱ���͹ر�ȫ���жϻ����ǿ���ȫ���жϽӿڳɶ�ʹ�ã��Թ�ȫ���жϻ��߿�ȫ���жϲ����ķ���ֵΪ��Ρ�</li>
 *<li>�Ա�֤�жϿ��Իָ�����ȫ���жϻ��߿�ȫ���жϲ���ǰ��״̬��</li>
 *</ul>
 *
 * @param lSpl [IN] ����#VOS_INT32�����ж�VOS_SplImp��ȡ״̬��ȡֵ��ΧΪ32λ�з���������
 *
 * @retval #VOS_OK                              0x00000000�����жϳɹ���
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_SplImp
 */
extern VOS_UINT32 VOS_SplX(VOS_INT32 lSpl);

/**
 * @ingroup  vos_sys
 * @brief ��ȡ��ϵͳ��������ǰ���ۼ�����ʱ�䡣
 *
 * @par ����:
 * ��ȡ��ϵͳ��������ǰ��64λ����ʱ�䣬�����pulSecond��pulUSecond�С�
 *
 * @attention ��
 *
 * @param pulSecond [OUT] ����#VOS_UINT32 *���ۼ����е�������ȡֵ��ΧΪ�ǿա�
 * @param pulUSecond [OUT] ����#VOS_UINT32 *���ۼ����еĲ���һ���΢������ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��pulSecond��pulUSecondΪ�գ��û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ȡʱ��ɹ���
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_Now
 */
extern VOS_UINT32 VOS_Tm_BootInSec(VOS_UINT32 *pulSecond, VOS_UINT32 *pulUSecond);

/**
 * @ingroup  vos_sys
 * @brief ��ȡ��ϵͳ��������ǰ���ۼ�����ʱ�䡣
 *
 * @par ����:
 * ��ȡ��ϵͳ��������ǰ��64λ���Ժ������������pulRetTimeInMillSecHigh��pulRetTimeInMillSecLow�С�
 *
 * @attention ��
 *
 * @param pulRetTimeInMillSecHigh [OUT] ����#VOS_UINT32 *���ۼ�����ʱ���ú����ʾ�ĸ�λ��ȡֵ��ΧΪ�ǿա�
 * @param pulRetTimeInMillSecLow [OUT] ����#VOS_UINT32 *���ۼ�����ʱ���ú����ʾ�ĵ�λ��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��pulRetTimeInMillSecHigh��pulRetTimeInMillSecLowΪ�գ��û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ȡʱ��ɹ���
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_BootInSec
 */
extern VOS_UINT32 VOS_Tm_Now(VOS_UINT32 *pulRetTimeInMillSecHigh, VOS_UINT32 *pulRetTimeInMillSecLow);

/**
 * @ingroup  vos_sys
 * @brief ��ȡϵͳ��ǰ��cputick����
 *
 * @par ����:
 * ͨ����ȡϵͳ��ʱ���Ĵ������õ�ϵͳ��ǰ��cputick����
 *
 * @attention ��
 *
 * @param pLow [OUT] ����#VOS_UINT32 *��ϵͳcputick�ĵ�32λ��ȡֵ��ΧΪ�ǿա�
 * @param pHigh [OUT] ����#VOS_UINT32 *��ϵͳcputick�ĸ�32λ��ȡֵ��ΧΪ�ǿա�
 *
 * @retval ��
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_TickGet
 */
extern VOS_VOID VOS_GetCpuTick(VOS_UINT32 *pLow, VOS_UINT32 *pHigh);

/**
 * @ingroup  vos_sys
 * @brief ��ȡϵͳ��ǰ��Tick����
 *
 * @par ����:
 * ��ȡϵͳ��ǰ��Tick����
 *
 * @attention ��
 *
 * @param puiHigh [OUT] ����#VOS_UINT32 *��ϵͳTick�ĸ�32λ��ȡֵ��ΧΪ�ǿա�
 * @param puiLow [OUT] ����#VOS_UINT32 *��ϵͳTick�ĵ�32λ��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��puiHigh��puiLowΪ�գ��û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ȡTick���ɹ���
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_GetCpuTick
 */
extern VOS_UINT32 VOS_TickGet(VOS_UINT32 *puiHigh, VOS_UINT32 *puiLow);

/**
 * @ingroup  vos_sys
 * @brief ��ȡcpuTick��Tickת���Ļ�ֵ��
 *
 * @par ����:
 * ͨ��ȫ�ֱ�������ȡcpuTick��Tickת���Ļ�ֵ������ȡ���ٸ�cpuTick�൱��һ��Tick��
 *
 * @attention ��
 *
 * @param puiCpuTickBase [OUT] ����#VOS_UINT32 *�����cpuTick��ֵ��ָ�롣cpuTick��ֵ��λΪcpuTick/Tick��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��puiCpuTickBaseΪ�գ��û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ȡcpuTick��Tickת���Ļ�ֵ�ɹ���
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_UINT32 VOS_GetCpuTickBase(VOS_UINT32 *puiCpuTickBase);

/**
 * @ingroup  vos_sys
 * @brief ����������������ΪTick����
 *
 * @par ����:
 * ����������������ΪTick����ͨ������Ϊÿ����������Tick����ȫ�ֱ������Ѹ�������������ΪTick����
 *
 * @attention ��
 *
 * @param ulSecs [IN] ����#VOS_UINT32����Ҫת��ΪTick����������ȡֵ��ΧΪ��������0xFFFFFFFF/ÿ����������Tick������
 *
 * @retval #VOS_NULL_DWORD                      0xFFFFFFFF�����������
 * @retval #������                              ת�����Tick����
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_UINT32 VOS_TmSecToTick(VOS_UINT32 ulSecs);

/**
 * @ingroup  vos_sys
 * @brief ��ȡ��ǰϵͳʱ��(��ʽΪLocalTime)��
 *
 * @par ����:
 * ��ȡ��ǰϵͳʱ��(��ʽΪLocalTime)���������롣
 *
 * @attention
 * <ul><li>�ýӿڻ�ȡ��ʱ��ֻ�ܾ�ȷ���룬�����������ķ���ֵ��Ϊ�㡣</li></ul>
 *
 * @param pRetDate [OUT] ����#DATE_S *����ȡ�����ڡ�ȡֵ��ΧΪ�ǿա�
 * @param pRetTime [OUT] ����#TIME_S *����ȡ��ʱ�䡣ȡֵ��ΧΪ�ǿա�
 * @param pulMillSec [OUT] ����#VOS_UINT32 *����ȡ�ĺ��룬�ò����ķ���ֵ��Ϊ�㡣ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��pRetDate��pRetTime��pulMillSecΪ�գ��û���Ҫ����Լ������������
 * @retval #VOS_ERROR                           0xFFFFFFFF������ִ��ʧ�ܡ�
 * @retval #VOS_OK                              0x00000000����ȡʱ��ɹ���
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_Now
 */
extern VOS_UINT32 VOS_Tm_Get(DATE_S *pRetDate, TIME_S *pRetTime, VOS_UINT32 *pulMillSec);

/**
 * @ingroup  vos_sys
 * @brief ��ȡ��1970��1��1��0ʱ0��0������ǰʱ�������������
 *
 * @par ����:
 * ��ȡ��1970��1��1��0ʱ0��0������ǰʱ��������������������pulRetTimeInMillSecHigh��pulRetTimeInMillSecLow�С�
 *
 * @attention ��
 *
 * @param pulSecHigh [OUT] ����#VOS_UINT32 *�����������ĸ�λ��ȡֵ��ΧΪ�ǿա�
 * @param pulSecLow [OUT] ����#VOS_UINT32 *�����������ĵ�λ��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��pulRetTimeInMillSecHigh��pulRetTimeInMillSecLowΪ�գ��û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ȡ�����ɹ���
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_Now | VOS_Tm_Get | VOS_Tm_NowInSec
 */
extern VOS_UINT32 VOS_Tm_Since1970(VOS_UINT32 *pulSecHigh, VOS_UINT32 *pulSecLow);

/**
 * @ingroup  vos_sys
 * @brief ��ȡ��1970��1��1��0ʱ0��0�뵽��ǰ��������
 *
 * @par ����:
 * ��ȡ��1970��1��1��0ʱ0��0�뵽��ǰʱ���32λ���������������pulRetTimeInSec�С�
 *
 * @attention ��
 *
 * @param pulRetTimeInSec [OUT] ����#VOS_UINT32 *����1970��1��1��0ʱ0��0�뵽��ǰ��������ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��pulRetTimeInSecΪ�գ��û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ȡʱ��ɹ���
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_Now | VOS_Tm_Get | VOS_Tm_Since1970
 */
extern VOS_UINT32 VOS_Tm_NowInSec(VOS_UINT32 *pulRetTimeInSec);

/**
 * @ingroup  vos_sys
 * @brief ��ȡ��ǰʱ��(��ʽLocalTime)��
 *
 * @par ����:
 * ��ȡ��ǰʱ��(��ʽLocalTime)��ʱ����Ϣѹ���洢�������С�
 * ������ʱ����������Ϣ��ʾ����: ��������Ϣ�洢��һ��32λ�����У���ʽΪ Y/M/D (��Ӧλ�� 31-16/15-8/7-0) ʱ������Ϣ�洢��һ��32λ�����У���ʽΪ h/m/s (��Ӧλ�� 31-16/15-8/7-0) ������һ��32λ����ʾ��ֵ��Ϊ�㡣
 *
 * @attention
 * <ul><li>�ýӿڻ�ȡ��ʱ��ֻ�ܾ�ȷ���룬�����������ķ���ֵ��Ϊ�㡣</li></ul>
 *
 * @param pulRetDate [OUT] ����#VOS_UINT32 *����ǰʱ�����������Ϣ��ȡֵ��ΧΪ�ǿա�
 * @param pulRetTime [OUT] ����#VOS_UINT32 *����ǰʱ���ʱ������Ϣ��ȡֵ��ΧΪ�ǿա�
 * @param pulRetMillSec [OUT] ����#VOS_UINT32 *����ǰʱ��ĺ�����Ϣ���ò����ķ���ֵ��Ϊ�㡣ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��pulRetDate��pulRetTime��pulRetMillSecΪ�ա�
 * @retval #VOS_ERROR                           0xFFFFFFFF������ִ��ʧ�ܡ�
 * @retval #VOS_OK                              0x00000000����ȡʱ��ɹ���
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_Now
 */
extern VOS_UINT32 VOS_SYS_GetCurrentTime(VOS_UINT32 *pulRetDate, VOS_UINT32 *pulRetTime, VOS_UINT32 *pulRetMillSec);

/**
 * @ingroup  vos_sys
 * @brief ��ȡ��ϵͳ��������ǰ���ۼ�����ʱ�䡣
 *
 * @par ����:
 * ��ȡ��ϵͳ��������ǰ��64λ���Ժ������������pulMillSecHigh��pulMillSecLow�С�
 *
 * @attention ��
 *
 * @param pulMillSecHigh [OUT] ����#VOS_UINT32 *���ۼ�����ʱ���ú����ʾ�ĸ�λ��ȡֵ��ΧΪ�ǿա�
 * @param pulMillSecLow [OUT] ����#VOS_UINT32 *���ۼ�����ʱ���ú����ʾ�ĵ�λ��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��pulMillSecHigh��pulMillSecLowΪ�գ��û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ȡʱ��ɹ���
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Tm_Now
 */
extern VOS_UINT32 VOS_TmNow(VOS_UINT32 *pulMillSecHigh, VOS_UINT32 *pulMillSecLow);

/**
 * @ingroup  vos_sys
 * @brief �Ƚ������Ϸ���ϵͳʱ�䣬���رȽϵĽ����
 *
 * @par ����:
 * �Ƚ������Ϸ���ϵͳʱ�䣬���رȽϵĽ������ʱ��pFirstС��ʱ��pSecondʱ������1����ʱ��pFirst����ʱ��pSecondʱ������2����ʱ��pFirst����ʱ��pSecondʱ������3����������ֵΪ�����롣
 *
 * @attention ��
 *
 * @param pFirst [IN] ����#DATE_TIME_S *����һ��ϵͳʱ�䡣ȡֵ��ΧΪ�ǿա�
 * @param pSecond [IN] ����#DATE_TIME_S *���ڶ���ϵͳʱ�䡣ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��pFirst��pSecondΪ�գ��û���Ҫ����Լ������������
 * @retval #VOS_ERROR                           0xFFFFFFFF������ִ��ʧ�ܡ�
 * @retval #COMP_TIME_LT                        0x00000001��ʱ��pFirstС��ʱ��pSecond��
 * @retval #COMP_TIME_EQ                        0x00000002��ʱ��pFirst����ʱ��pSecond��
 * @retval #COMP_TIME_GT                        0x00000003��ʱ��pFirst����ʱ��pSecond��
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_DateTime_DeltaSec
 */
extern VOS_UINT32 VOS_DateTime_Cmp(DATE_TIME_S *pFirst, DATE_TIME_S *pSecond);

/**
 * @ingroup  vos_sys
 * @brief �Ƚ������Ϸ���ϵͳʱ�䣬���رȽϵĽ����
 *
 * @par ����:
 * �Ƚ������Ϸ���ϵͳʱ�䣬��������pFirst������pSecond�����������ʱ��pFirstС�ڵ���ʱ��pSecondʱ���Ƚ�ʧ�ܣ�����0xFFFFFFFF����ʱ��pFirst����ʱ��pSecondʱ�����سɹ���pDeltaSec�б���pFirst��pSecond���������
 *
 * @attention ��
 *
 * @param pFirst [IN] ����#DATE_TIME_S *����һ��ϵͳʱ�䡣ȡֵ��ΧΪ�ǿա�
 * @param pSecond [IN] ����#DATE_TIME_S *���ڶ���ϵͳʱ�䡣ȡֵ��ΧΪ�ǿա�
 * @param pDeltaSec [OUT] ����#VOS_UINT32 *���Ƚϳɹ�ʱ��������pFirst������pSecond���������ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��pFirst��pSecond��pDeltaSecΪ�գ��û���Ҫ����Լ������������
 * @retval #VOS_ERROR                           0xFFFFFFFF������pFirstС�ڵ�������pSecond��
 * @retval #VOS_OK                              0x00000000��ʱ��Ƚϳɹ���
 * @par ����:
 * <ul><li>vos_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_DateTime_Cmp
 */
extern VOS_UINT32 VOS_DateTime_DeltaSec(DATE_TIME_S *pFirst, DATE_TIME_S *pSecond, VOS_UINT32 *pDeltaSec);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_SYS_H__

