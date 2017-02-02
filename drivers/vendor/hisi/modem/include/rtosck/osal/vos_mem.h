/**
 * @file vos_mem.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������OSAL�ڴ�ͷ�ļ��� \n
 */
/**@defgroup OSAL OSAL */
/**@defgroup vos_mem �ڴ�
 *@ingroup OSAL
*/

#ifndef __VOS_MEM_H__
#define __VOS_MEM_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup  vos_mem
 * @brief ����ָ����С���ڴ�ռ䡣
 *
 * @par ����:
 * ����ָ����С���ڴ�ռ䡣
 *
 * @attention ��
 *
 * @param  ulInfo [IN] ����#VOS_UINT32��������PID���ò������ԣ�ȡֵ��ΧΪ����ֵ��
 * @param  uvSize [IN] ����#VOS_SIZE_T�������ڴ�Ĵ�С��ȡֵ��ΧΪ��������
 *
 * @retval #VOS_NULL_PTR                        0x00000000�������ڴ�ʧ�ܣ����ܵ�ԭ��ΪuvSizeΪ0�����ڴ治�㡣
 * @retval #����ֵ                              ������ڴ���׵�ַ��
 * @par ����:
 * <ul><li>vos_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Free | VOS_MemReAlloc | VOS_Mem_Calloc
 */
extern VOS_VOID * VOS_Malloc(VOS_UINT32 ulInfo, VOS_SIZE_T uvSize);

/**
 * @ingroup  vos_mem
 * @brief �ͷ��ڴ�ռ䡣
 *
 * @par ����:
 * �ͷŸ����ĵ�ַ�ռ�pBuf��
 *
 * @attention ��
 *
 * @param  pBuf [IN] ����#VOS_VOID *����Ҫ�ͷŵ��ڴ��׵�ַ��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016���ͷŵ�ַpBufΪ�ա�
 * @retval #VOS_ERROR                           0xFFFFFFFF���ͷ��ڴ�ʧ�ܣ����ܵ�ԭ��Ϊ�ڴ���ͷ���ƻ������ڴ�����ͷš�
 * @retval #VOS_OK                              0x00000000���ͷ��ڴ�ɹ���
 * @par ����:
 * <ul><li>vos_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Malloc
 */
extern VOS_UINT32 VOS_Free(VOS_VOID *pBuf);

/**
 * @ingroup  vos_mem
 * @brief ��ȡָ����ַ�����ü�����
 *
 * @par ����:
 * ��ȡָ����ַpBuf�����ü�����
 *
 * @attention ��
 *
 * @param  pBuf [IN] ����#VOS_VOID *����Ҫ��ȡ���õļ������ڴ��׵�ַ��ȡֵ��ΧΪ�ǿա�
 * @param  pulRetRef [OUT] ����#VOS_UINT32 *�����ڴ洢��ȡ�������ü�����ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��pBuf��pulRetRefΪ�ա�
 * @retval #VOS_OK                              0x00000000����ȡָ����ַ�����ü����ɹ���
 * @par ����:
 * <ul><li>vos_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern VOS_UINT32 VOS_Mem_GetRef(VOS_VOID *pBuf, VOS_UINT32 *pulRetRef);

/**
 * @ingroup  vos_mem
 * @brief ����ָ����ַ�����ü�����
 *
 * @par ����:
 * ����ָ����ַpBuf�����ü�����
 *
 * @attention ��
 *
 * @param  pBuf [IN] ����#VOS_VOID *����Ҫ�������õļ������ڴ��׵�ַ��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��pBufΪ�ա�
 * @retval #VOS_OK                              0x00000000������ָ����ַpBuf�����ü����ɹ���
 * @par ����:
 * <ul><li>vos_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern VOS_UINT32 VOS_Mem_IncRef(VOS_VOID *pBuf);

/**
 * @ingroup  vos_mem
 * @brief ����ָ����С���ڴ�ռ䣬�����ڴ�ռ����ݽ������㡣
 *
 * @par ����:
 * ����uvSize�ֽڵ��ڴ棬�����ڴ�ռ����ݽ������㡣
 *
 * @attention ��
 *
 * @param  ulInfo [IN] ����#VOS_UINT32���ò������ԣ�ȡֵ��ΧΪ����ֵ��
 * @param  chTaskName[4] [IN] ����#VOS_CHAR���ò������ԣ�����VOS_NULL_PTR���ɡ�
 * @param  uvSize [IN] ����#VOS_SIZE_T�������ڴ�Ĵ�С��ȡֵ��ΧΪ��������
 *
 * @retval #VOS_NULL_PTR                        0x00000000�������ڴ�ʧ�ܣ����ܵ�ԭ��ΪuvSizeΪ0�����ڴ治�㡣
 * @retval #����ֵ                              ������ڴ���׵�ַ��
 * @par ����:
 * <ul><li>vos_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Malloc | VOS_MemReAlloc
 */
extern VOS_VOID * VOS_Mem_Calloc(VOS_UINT32 ulInfo, VOS_CHAR chTaskName[4], VOS_SIZE_T uvSize);

/**
 * @ingroup  vos_mem
 * @brief ���������ڴ��Ĵ�С��
 *
 * @par ����:
 * ���е��ڴ�鲻��ʹ��ʱ����������һ���СΪulNewSize���ڴ棬���ڴ�����ɹ��󣬻Ὣԭ�ڴ��(��ַΪpOldMemPtr)�е����ݿ��������ڴ�飬��ԭ�ڴ����Ϣ���ֲ��������£��õ���չ����󿽱�����Ϊ���ڴ��Ĵ�СulNewSize�����ͷ�ԭ�ڴ�顣
 *
 * @attention
 * <ul>
 * <li>��������ԭ�ڴ��ַΪVOS_NULL_PTR����ô��������൱�� VOS_MemAlloc��������һ�����ڴ�顣</li>
 * <li>��������ԭ�ڴ��ַ��Ϊ�գ�����������ڴ���СΪ0����ô��������൱�� VOS_MemFree�����ͷ�ԭ�ڴ档</li>
 * <li>������ڴ�����ʧ�ܣ�ԭ�ڴ�鲻�ᱻ�ͷš�</li>
 * <li>���ԭ���ڴ��Ĵ�СС���µĴ�С����ֻ����ԭ���ڴ��С�����ݣ��������´�С�����ݡ�</li>
 * </ul>
 *
 * @param  ulPid [IN] ����#VOS_UINT32���ò������ԣ�ȡֵ��ΧΪ����ֵ��
 * @param  ucPtNo [IN] ����#VOS_UINT8���ò������ԣ�ȡֵ��ΧΪ����ֵ��
 * @param  pOldMemPtr [IN] ����#VOS_VOID *��ԭ���ڴ��ĵ�ַ��ȡֵ��ΧΪ�ǿա�
 * @param  uwNewSize [IN] ����#VOS_UINT32���µ��ڴ���С��ȡֵ��ΧΪ��������
 *
 * @retval #VOS_NULL_PTR                        0x00000000�������ڴ�ʧ�ܣ����ܵ�ԭ��ΪuvSizeΪ0�����ڴ治�㡣
 * @retval #����ֵ                              ���·�����ڴ���׵�ַ��
 * @par ����:
 * <ul><li>vos_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Malloc | VOS_Mem_Calloc
 */
extern VOID * VOS_MemReAlloc(VOS_UINT32 ulPid, VOS_UINT8 ucPtNo, VOS_VOID *pOldMemPtr, VOS_UINT32 uwNewSize);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_MEM_H__

