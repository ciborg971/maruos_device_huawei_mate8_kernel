/**
 * @file sre_coprocessor.h
 *
 * Copyright(C), 2010-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������ʸ���Ĵ���ģ��Ķ���ͷ�ļ��� \n
 */
 /**@defgroup SRE_coprocessor ʸ���Ĵ���
   *@ingroup SRE_kernel
 */


#include "sre_base.h"
#ifndef _SRE_COPROCESSOR_H
#define _SRE_COPROCESSOR_H


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if  (OS_OPTION_COPROCESSOR == YES)

/**
 * @ingroup SRE_coprocessor
 * coprocessor_a��coprocessor_b�����ı�������Ĵ�С��
 *
 */

#if (OS_HARDWARE_PLATFORM == OS_DSP170)

#define OS_CP_CONTEXT_A_SIZE                                0x18C
#define OS_CP_CONTEXT_B_SIZE                                0x18C

#elif (OS_HARDWARE_PLATFORM == OS_DSP220)

#define OS_CP_CONTEXT_A_SIZE                                0xD8
#define OS_CP_CONTEXT_B_SIZE                                0xD8

#elif ((OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))

#define OS_CP_CONTEXT_A_SIZE                                0x44
#define OS_CP_CONTEXT_B_SIZE                                0x44

#elif (OS_HARDWARE_PLATFORM == OS_HIDSP)

#define OS_CP_CONTEXT_A_SIZE                                0x88
#define OS_CP_CONTEXT_B_SIZE                                0x88

#endif

#endif // (OS_OPTION_COPROCESSOR == YES)

/**
 *@ingroup SRE_coprocessor
 *@brief Ϊָ�����ڴ�ռ�����ָ��ֵ��
 *
 *@par ����:
 *ͨ��ʸ����������ָ���׵�ַ�ͳ��ȵ��ڴ�ռ�����Ϊ�̶�ֵ�����ܵ�ͬ��memset��
 *@attention
 * <ul>
 * <li>�ò���������SD6108/SD6181ƽ̨��DSP�ˣ�SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>��SD6183ƽ̨�����û�ʹ��ʸ����ֵ����ǰ����#SRE_TaskCpEntry��#SRE_SwiCpEntry��ʹ��ʸ����ֵ�����󣬵���#SRE_TaskCpExit��#SRE_SwiCpExit, �����ʸ���������ܡ�</li>
 * <li>����uwValueֻ�е�8bit��Ч����λ�ᱻ���ԡ�</li>
 * <li>��SD6183ƽ̨����������ж��н���ʸ����ֵ����ǰһ��Ҫ����ʸ����������</li>
 * <li>��SD6183ƽ̨Ӳ�ж��в�֧��ʸ������</li>
 * </ul>
 *@param pDst         [IN]  ����#VOID *���ڴ�ռ��׵�ַ��
 *@param uwValue      [IN]   ����#UINT32�������õ�ָ��ֵ����8BIT��Ч��
 *@param uwSize       [IN]   ����#UINT32���ڴ�ռ�ĳ��ȡ�
 *
 *@retval #VOID *    �ڴ�ռ��׵�ַ��
 *@par ����:
 *sre_coprocessor.h���ýӿ��������ڵ�ͷ�ļ���
 *@since UniDSP V200R003C05
 *@see SRE_SwiCpEntry|SRE_TaskCpEntry
*/
extern VOID * SRE_VecMemSet(VOID *pDst, UINT32 uwValue, UINT32 uwSize);


/**
 *@ingroup SRE_coprocessor
 *@brief ��һ��ָ�����ȵ��ڴ��Դ��ַ������Ŀ�ĵ�ַ��
 *
 *@par ����:
 * ͨ��ʸ����������pSrc��ʼ��СΪuwSize���ڴ�����ݿ�����pDst��ʼ���ڴ�ռ䡣
 *@attention
 * <ul>
 * <li>�ò���������SD6108/SD6181ƽ̨��DSP�ˣ�SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>�����û�ʹ��ʸ����������ǰ����#SRE_TaskCpEntry��#SRE_SwiCpEntry��ʹ��ʸ�����������󣬵���#SRE_TaskCpExit��#SRE_SwiCpExit, �����ʸ���������ܡ�</li>
 * <li>����ǰ����Ҫ��֤����֮�䲻�������¹�ϵpSrc < pDst < (pSrc + uwSize)</li>
 * <li>����������ж��н���ʸ����������ǰһ��Ҫ����ʸ����������</li>
 * <li>Ӳ�ж��в�֧��ʸ������</li>
 * </ul>
 *@param pDst         [IN] ����#VOID *����������Ŀ���ڴ��׵�ַ��
 *@param pSrc         [IN]  ����#VOID *���追����Դ�ڴ��׵�ַ��
 *@param uwSize       [IN]  ����#UINT32�����п����ĳ��ȡ�
 *
 *@retval #VOID*    ��������Ŀ���ڴ��׵�ַ��
 *@par ����:
 *sre_coprocessor.h���ýӿ��������ڵ�ͷ�ļ���
 *@since UniDSP V200R003C05
 *@see SRE_SwiCpEntry|SRE_TaskCpEntry
*/
extern VOID * SRE_VecMemCpy(VOID *pDst, VOID *pSrc, UINT32 uwSize);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_COPROCESSOR_H */

