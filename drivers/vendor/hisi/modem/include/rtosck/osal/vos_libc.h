/**
 * @file vos_libc.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������OSAL��C����ͷ�ļ��� \n
 */

/**@defgroup vos_libc libc
 *@ingroup OSAL
*/

#ifndef __VOS_LIBC_H__
#define __VOS_LIBC_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include <stdarg.h>
#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#ifndef VOS_NTOHL

#define VOS_NTOHL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#endif //VOS_NTOHL

#define VOS_DBGASSERT(lExpression)

/**
 * @ingroup vos_libc
 * �ж��ַ��Ƿ�Ϊ��д��ĸ��
 */
#define VOS_isupper(c)  (((c) >= 'A' && (c) <= 'Z') ?  1 : 0)

/**
 * @ingroup vos_libc
 * �ж��ַ��Ƿ�ΪСд��ĸ��
 */
#define VOS_islower(c)  (((c) >= 'a' && (c) <= 'z') ?  1 : 0)

/**
 * @ingroup vos_libc
 * �ж��ַ��Ƿ�Ϊ��ĸ��
 */
#define VOS_isalpha(c)  (VOS_isupper(c) || VOS_islower(c))

/**
 * @ingroup vos_libc
 * �ж��ַ��Ƿ�Ϊ���֡�
 */
#define VOS_isdigit(c)  (((c) >= '0' && (c) <= '9') ?  1 : 0)

/**
 * @ingroup vos_libc
 * ��Դ��ַSrc���ڴ����ݿ�����Ŀ���ڴ��ַDest��
 */
#define VOS_CopyVar(Dest, Src) \
{\
    (VOID)VOS_Mem_Copy((VOID *)&(Dest), (VOID *)&(Src), sizeof(Dest)); \
}

/**
 * @ingroup vos_libc
 * OSAL Libc�����룺��ʽ���Ŀ����ַ���Ϊ�ա�
 *
 * ֵ: 0x00000050
 *
 * �������: ��������Ч�ĸ�ʽ���Ŀ����ַ�����
 */
#define VOS_ERR_NULL_FORMAT_STR                 0x00000050

/**
 * @ingroup  vos_libc
 * @brief �ӻ������а�ָ����ʽ�����ַ���
 *
 * @par ����:
 * ��pscIBuf��������ݣ�����pfmt�ĸ�ʽ������д�뵽��ѡ�����
 *
 * @attention
 * <ul>
 * <li>�ָ����ǿո�</li>
 * <li>�û���֤��ʽ�����ַ����пɷֽ���Ӵ��ĸ�ʽ���ʽ�������ַ����еĸ�ʽƥ�䡣</li>
 * <li>�û���֤��Ÿ�ʽ�����ݵĿɱ�����ռ��㹻��</li>
 * <li>���pscIBuf�����ĸ�������Ҫ���٣���ôֻ�ܽ���pscIBuf�а������ַ���</li>
 * <li>֧��x��d��s��u���ָ�ʽ�����͡�</li>
 * </ul>
 *
 * @param pscIBuf [IN] ����#VOS_CHAR *����ʽ�����ַ�����ȡֵ��ΧΪ�ǿա�
 * @param pfmt [IN] ����#VOS_CHAR *����ʽ�������ַ�����ȡֵ��ΧΪ�ǿա�
 * @param ... [OUT] ��ѡ������
 *
 * @retval #-1                                  pscIBuf��pfmtΪ�ա�
 * @retval #�Ǹ���                              �Ӹ�ʽ���Ļ����ж�����ֵ�ĸ�����
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_INT32 VOS_sscanf(const VOS_CHAR *pscIBuf, const VOS_CHAR *pfmt, ...);

/**
 * @ingroup  vos_libc
 * @brief �Ƚ������ڴ������ַ���
 *
 * @par ����:
 * �����Ƚ�pDestPtr��pSrcPtr��ָ���ڴ�����ǰulCmpLen���ַ����ַ�����С�ıȽ�����ASCII����ϵ�˳������������˳����Ϊ�ַ���ֵ�����ȽϵĲ�ֵ������plRetResult�С�
 *
 * @attention ��
 *
 * @param pDestPtr [IN] ����#const VOS_VOID *��Ҫ�Ƚϵ��ڴ��ַ��ȡֵ��ΧΪ�ǿա�
 * @param pSrcPtr [IN] ����#const VOS_VOID *��Ҫ�Ƚϵ��ڴ��ַ��ȡֵ��ΧΪ�ǿա�
 * @param uvCmpLen [IN] ����#VOS_SIZE_T���Ƚϵ��ַ�����ȡֵ��ΧΪ��������
 * @param plRetResult [OUT] ����#VOS_INT32 *���洢�ȽϵĽ�������˵��: ����0˵��pDestPtr����pSrcPtr������0˵��pDestPtr����pSrcPtr��С��0˵��pDestPtrС��pSrcPtr��
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF��pDestPtr��pSrcPtr��plRetResult��һ��Ϊ�ջ�uvCmpLenΪ0��
 * @retval #VOS_OK                              0x00000000���Ƚϳɹ���
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_UINT32 VOS_Mem_Cmp(const VOS_VOID *pDestPtr, const VOS_VOID *pSrcPtr, VOS_SIZE_T uvCmpLen, VOS_INT32 *plRetResult);

/**
 * @ingroup  vos_libc
 * @brief ��ָ�����ڴ��������ض���ֵ��䡣
 *
 * @par ����:
 * �Ὣ����pBufPtr��ָ���ڴ�����ǰulSetLen���ֽ��Բ���uChar���롣
 *
 * @attention ��
 *
 * @param pBufPtr [IN/OUT] ����#VOS_CHAR *��Ҫ�����ڴ��ַ��ȡֵ��ΧΪ�ǿա�
 * @param uChar [IN] ����#VOS_CHAR��Ҫ������ڴ�ֵ��ȡֵ��ΧΪ�ǿա�
 * @param uvSetLen [IN] ����#VOS_SIZE_T��Ҫ�����ַ�����ȡֵ��ΧΪ��������
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF��pBufPtrΪ�ջ�uvSetLenΪ0��
 * @retval #VOS_OK                              0x00000000���ڴ����óɹ���
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_MemSet
 */
extern VOS_UINT32 VOS_Mem_Set(VOS_CHAR *pBufPtr, VOS_CHAR uChar, VOS_SIZE_T uvSetLen);

/**
 * @ingroup  vos_libc
 * @brief ��ָ�����ڴ��������ض���ֵ��䡣
 *
 * @par ����:
 * �Ὣ����pBufPtr��ָ���ڴ�����ǰulSetLen���ֽ��Բ���uChar���롣
 *
 * @attention ��
 *
 * @param pBufPtr [IN/OUT] ����#VOS_CHAR *��Ҫ�����ڴ��ַ��ȡֵ��ΧΪ�ǿա�
 * @param uChar [IN] ����#VOS_CHAR��Ҫ������ڴ�ֵ��ȡֵ��ΧΪ�ǿա�
 * @param uvSetLen [IN] ����#VOS_SIZE_T��Ҫ�����ַ�����ȡֵ��ΧΪ��������
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF��pBufPtrΪ�ջ�uvSetLenΪ0��
 * @retval #VOS_OK                              0x00000000���ڴ����óɹ���
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_Mem_Set
 */
extern VOS_UINT32 VOS_MemSet(VOS_VOID *pBufPtr, VOS_CHAR uChar, VOS_SIZE_T uvSetLen);

/**
 * @ingroup  vos_libc
 * @brief �Ƚ������ַ�����ǰn���ַ���
 *
 * @par ����:
 * �û����뱣֤�����������Ч�ԣ����pscStr1��pscStr2Ϊ��ָ�룬��ýӿڷ���0����ʱ���ַ������ʱ�ķ���ֵ��ͬ��
 *
 * @attention ��
 *
 * @param pscStr1 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���1��ȡֵ��ΧΪ�ǿա�
 * @param pscStr2 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���2��ȡֵ��ΧΪ�ǿա�
 * @param ulLen [IN] ����#VOS_UINT32��Ҫ�Ƚϵ��ַ�����ȡֵ��ΧΪ��������
 *
 * @retval #0                                   pscStr1����pscStr2��pscStr1��pscStr2����һ��Ϊ��ָ���ulLenΪ0��
 * @retval #����0                               pscStr1����pscStr2��
 * @retval #С��0                               pscStr1С��pscStr2��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_strncmp
 */
extern VOS_INT32 VOS_StrNCmp(const VOS_CHAR *pscStr1, const VOS_CHAR *pscStr2, VOS_UINT32 ulLen);

/**
 * @ingroup  vos_libc
 * @brief �Ƚ��ַ���������������ĸ�Ĵ�Сд��
 *
 * @par ����:
 * �û����뱣֤�����������Ч�ԣ����pscStr1��pscStr2Ϊ��ָ�룬��ýӿڷ���0����ʱ���ַ������ʱ�ķ���ֵ��ͬ��
 *
 * @attention
 * <ul><li>�û����뱣֤���������Ϊ��ָ�룬����ýӿڷ���0����ʱ���ַ������ʱ�ķ���ֵ��ͬ���޷����ݷ���ֵ�жϺ����Ƿ�ִ�гɹ���</li></ul>
 *
 * @param pscStr1 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���1��ȡֵ��ΧΪ�ǿա�
 * @param pscStr2 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���2��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #0                                   pscStr1����pscStr2��pscStr1��pscStr2����һ��Ϊ��ָ�롣
 * @retval #����0                               pscStr1����pscStr2��
 * @retval #С��0                               pscStr1С��pscStr2��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_stricmp
 */
extern VOS_INTPTR VOS_StrICmp(VOS_CHAR *pscStr1, VOS_CHAR *pscStr2);

/**
 * @ingroup  vos_libc
 * @brief ���ַ���ת��Ϊ�޷���������
 *
 * @par ����:
 * ���ַ���pcStrת��Ϊ�޷����������洢��pnVal�С�
 *
 * @attention ��
 *
 * @param pcStr [IN] ����#const VOS_CHAR *��Ҫת����ԭ�ַ�����ȡֵ��ΧΪ�ǿա�
 * @param pnVal [OUT] ����#VOS_UINT32 *�����ڴ洢ת�����������ȡֵ��ΧΪ�ǿա�
 *
 * @retval #-1                                  ���pcStr��pnValΪ�ա�
 * @retval #VOS_OK                              0x00000000��ת���ɹ���
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_atol
 */
extern VOS_INT32 VOS_atoul(const VOS_CHAR *pcStr, VOS_UINT32 *pnVal);

/**
 * @ingroup  vos_libc
 * @brief ��ָ�����ڴ�������0ֵ��䡣
 *
 * @par ����:
 * ������pBufPtr��ָ���ڴ�����ǰulSetLen���ֽ���0ֵ���롣
 *
 * @attention ��
 *
 * @param pBufPtr [IN/OUT] ����#VOS_CHAR *���������ڴ�����ĵ�ַ��ȡֵ��ΧΪ�ǿա�
 * @param uvSetLen [IN] ����#VOS_SIZE_T��ָ���ڴ�����Ĵ�С������0ʱ�������ڴ����κ���䡣ȡֵ��ΧΪ�Ǹ�����
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF��pBufPtrΪ�ա�
 * @retval #VOS_OK                              0x00000000���ڴ����óɹ���
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_UINT32 VOS_Mem_Zero(VOS_CHAR *pBufPtr, VOS_SIZE_T uvSetLen);

/**
 * @ingroup  vos_libc
 * @brief ��һ���ڴ������ֵ����������һ���ڴ������С�
 *
 * @par ����:
 * ��ԴpSrcPtr��ָ���ڴ��ַ����ʼλ�ÿ�ʼ����uvCopyLen���ֽڵ�Ŀ��pDestPtr��ָ���ڴ��ַ����ʼλ���С�
 *
 * @attention ��
 *
 * @param pDestPtr [IN/OUT] ����#VOS_VOID *��Ŀ���ڴ档ȡֵ��ΧΪ�ǿա�
 * @param pSrcPtr [IN] ����#const VOS_VOID *����Դ�ڴ档ȡֵ��ΧΪ�ǿա�
 * @param uvCopyLen [IN] ����#VOS_SIZE_T���������ֽ�����ȡֵ��ΧΪ��������
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF��pBufPtr��pSrcPtr����һ��Ϊ�ջ�uvCopyLenΪ0��
 * @retval #VOS_OK                              0x00000000�������ɹ���
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_UINT32 VOS_Mem_Copy(VOS_VOID *pDestPtr, const VOS_VOID *pSrcPtr, VOS_SIZE_T uvCopyLen);

/**
 * @ingroup  vos_libc
 * @brief �����ַ��������һ�����ֵ�ָ���ַ���
 *
 * @par ����:
 * �����ҳ�����pscStr�ַ��������һ�����ֵĲ���scChar��ַ��Ȼ�󽫸��ַ����ֵĵ�ַ���ء����δ�ҵ�������VOS_NULL_PTR��
 *
 * @attention ��
 *
 * @param pscStr [IN] ����#VOS_CHAR *���������ַ�����ȡֵ��ΧΪ�ǿա�
 * @param scChar [IN] ����#VOS_CHAR��Ҫ���ҵ��ַ���ȡֵ��ΧΪ�����ַ���
 *
 * @retval #VOS_NULL_PTR                        0x00000000��pscStrΪ�ջ�δ�ҵ�ָ���ַ���
 * @retval #����ֵ                              ���ַ����ڵ�ַ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_CHAR * VOS_StrRChr(VOS_CHAR *pscStr, VOS_CHAR scChar);

/**
 * @ingroup  vos_libc
 * @brief ��ָ�����ڴ��������ָ���ַ���
 *
 * @par ����:
 * ��ͷ��ʼ����pvBuf��ָ���ڴ�����ǰsiSize���ֽڣ�ֱ�����ֵ�һ��ֵΪucChar���ֽڣ��򷵻�ָ����ֽڵ�ָ�롣
 *
 * @attention ��
 *
 * @param pvBuf [IN] ����#const VOS_VOID *���������ַ����ĵ�ַ��ȡֵ��ΧΪ�ǿա�
 * @param ucChar [IN] ����#VOS_CHAR�����������ַ���ȡֵ��ΧΪ�����ַ���
 * @param siSize [IN] ����#VOS_INT32���������ڴ�Ĵ�С��ȡֵ��ΧΪ��������
 *
 * @retval #VOS_NULL_PTR                        0x00000000��pvBufΪ�ջ�siSizeΪ0��δ������ָ���ַ���
 * @retval #����ֵ                              �������ַ��ĵ�ַ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_VOID * VOS_MemChr(const VOS_VOID *pvBuf, VOS_CHAR ucChar, VOS_INT32 siSize);

/**
 * @ingroup  vos_libc
 * @brief ���ַ���ת��Ϊ�޷���������
 *
 * @par ����:
 * ������szStr�ַ���ת��Ϊ�޷���������
 *
 * @attention ��
 *
 * @param szStr [IN] ����#const VOS_CHAR *����ת���ַ����ĵ�ַ��ȡֵ��ΧΪ�ǿա�
 * @param puiVal [OUT] ����#VOS_UINT32 *��ת�����޷��������ĵ�ַ��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��szStr��puiValΪ�ա�
 * @retval #VOS_OK                              0x00000000��ת���ɹ���
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_INT32 VOS_StrToUint32(const VOS_CHAR *szStr, VOS_UINT32 *puiVal);

/**
 * @ingroup  vos_libc
 * @brief �����ַ����е�һ�����ֵ�ָ���ַ���
 *
 * @par ����:
 * �ڲ���pcChar�ַ����в��ҵ�һ�γ��ֲ���scChar�ַ��ĵ�ַ��Ȼ�󽫸��ַ����ֵĵ�ַ���ء�
 *
 * @attention ��
 *
 * @param pcChar [IN] ����#const VOS_CHAR *��Դ�ַ�����ȡֵ��ΧΪ�ǿա�
 * @param scChar [IN] ����#VOS_CHAR��Ҫ���ҵ��ַ���ȡֵ��ΧΪ�����ַ���
 *
 * @retval #VOS_NULL_PTR                        0x00000000��pcCharΪ�ջ�δ���ҵ�ָ���ַ���
 * @retval #����ֵ                              ����scChar���ֵĵ�ַ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_CHAR * VOS_strchr(const VOS_CHAR *pcChar, VOS_CHAR scChar);

/**
 * @ingroup  vos_libc
 * @brief �����ַ���֮��Ŀ�����
 *
 * @par ����:
 * ������pcsrc�ַ�������������pcdest��ָ�ĵ�ַ��
 *
 * @attention
 * <ul><li>�������pcdest��ָ���ڴ�ռ��pcsrc��С�����ܻ���ɻ�������Ĵ��������</li></ul>
 *
 * @param pcdest [IN/OUT] ����#VOS_CHAR *��Ŀ���ַ�����ȡֵ��ΧΪ�ǿա�
 * @param pcsrc  [IN] ����#const VOS_CHAR *��Դ�ַ�����ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_NULL_PTR                        0x00000000��pcdest��pcsrcΪ�ա�
 * @retval #����ֵ                              Ŀ���ַ�������ʼ��ַ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_StrCpy
 */
extern VOS_CHAR * VOS_strcpy(VOS_CHAR *pcdest, const VOS_CHAR *pcsrc);

/**
 * @ingroup  vos_libc
 * @brief �����ַ���֮��Ŀ�����
 *
 * @par ����:
 * ������pcsrc�ַ�������������pcdst��ָ�ĵ�ַ��
 *
 * @attention
 * <ul><li>�������pcdst��ָ���ڴ�ռ��pcsrc��С�����ܻ���ɻ�������Ĵ��������</li></ul>
 *
 * @param pcdst [IN/OUT] ����#VOS_CHAR *��Ŀ���ַ�����ȡֵ��ΧΪ�ǿա�
 * @param pcsrc [IN] ����#const VOS_CHAR *��Դ�ַ�����ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_NULL_PTR                        0x00000000��pcdst��pcsrcΪ�ա�
 * @retval #����ֵ                              Ŀ���ַ�������ʼ��ַ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_strcpy
 */
extern VOS_CHAR * VOS_StrCpy(VOS_CHAR *pcdst, const VOS_CHAR *pcsrc);

/**
 * @ingroup  vos_libc
 * @brief ��һ���ַ�����ǰn���ַ���������һ���ַ����С�
 *
 * @par ����:
 * ������pcsrc�ַ���ǰn���ַ�����������pcdest��ָ�ĵ�ַ��
 *
 * @attention
 * <ul><li>���ú�����ע���жϷ��صĵ�ַ�Ƿ�Ϊ�գ�������ܻ���ʿ�ָ�롣</li></ul>
 *
 * @param pcdest [IN/OUT] ����#VOS_CHAR *��Ŀ���ַ�����ȡֵ��ΧΪ�ǿա�
 * @param pcsrc  [IN] ����#const VOS_CHAR *��Դ�ַ�����ȡֵ��ΧΪ�ǿա�
 * @param n [IN] ����#VOS_UINT32�������ַ�����ȡֵ��ΧΪ��������
 *
 * @retval #����ֵ                              Ŀ���ַ�������ʼ��ַ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_CHAR * VOS_strncpy(VOS_CHAR *pcdest, const VOS_CHAR *pcsrc, VOS_UINT32 n);

/**
 * @ingroup  vos_libc
 * @brief ��ָ���ַ�����ӵ���һ�ַ�����β����
 *
 * @par ����:
 * ��pcsrc��ָ�ַ�����ӵ�pcdest��β��(����pcdest��β���Ľ�����)����ӽ�������pcsrc��pcdest��ָ�ڴ����򲻿����ص���pcdest�������㹻�Ŀռ�������pcsrc���ַ���������ָ��pcdest��ָ�롣
 *
 * @attention ��
 *
 * @param pcdest [IN/OUT] ����#VOS_CHAR *��Ŀ���ַ�����ȡֵ��ΧΪ�ǿա�
 * @param pcsrc [IN] ����#const VOS_CHAR *��Դ�ַ�����ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_NULL_PTR                        0x00000000��pcdst��pcsrcΪ�ա�
 * @retval #����ֵ                              ��Ӻ���ַ�����ַ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_CHAR * VOS_strcat(VOS_CHAR *pcdest, const VOS_CHAR *pcsrc);

/**
 * @ingroup  vos_libc
 * @brief ��һ���ַ�����ǰn���ַ���ӵ���һ���ַ���β��
 *
 * @par ����:
 * �Ѳ���pscSrc��ָ�ַ�����ǰuvCount���ַ���ӵ�����pscDest�ַ�����β��(���ǲ���pscDest�ַ���������)����ӽ�������pscSrc��pscDest��ָ�ڴ����򲻿����ص���pscDest�������㹻�Ŀռ�������pscSrc���ַ���������ָ��pscDest��ָ�롣
 *
 * @attention ��
 *
 * @param pscDest [IN/OUT] ����#VOS_CHAR *��Ŀ���ַ�����ȡֵ��ΧΪ�ǿա�
 * @param pscSrc [IN] ����#VOS_CHAR *��Դ�ַ�����ȡֵ��ΧΪ�ǿա�
 * @param uvCount [IN] ����#VOS_SIZE_T���ַ�������ȡֵ��ΧΪ��������
 *
 * @retval #VOS_NULL_PTR                        0x00000000��pcdst��pcsrcΪ�ջ�uvCountΪ0��
 * @retval #����ֵ                              ��Ӻ���ַ�����ַ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_CHAR * VOS_StrNCat(VOS_CHAR *pscDest, VOS_CHAR *pscSrc, VOS_SIZE_T uvCount);

/**
 * @ingroup  vos_libc
 * @brief ��ȡ�����ַ����ĳ��ȡ�
 *
 * @par ����:
 * ��ȡ�����ַ���pcstr�ĳ��ȣ���������������
 *
 * @attention ��
 *
 * @param pcstr [IN] ����#const VOS_CHAR *��Ҫ��ȡ���ȵ��ַ�����ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_NULL��                          0x00000000��pcstrΪ�ա�
 * @retval #������                              �ַ������ȡ�
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_UINT32 VOS_strlen(const VOS_CHAR *pcstr);

/**
 * @ingroup  vos_libc
 * @brief ���ַ���������ָ���ַ�����
 *
 * @par ����:
 * ���ַ���pscStr1�������ַ���pscStr2���������ַ���pscStr2��һ�γ��ֵĵ�ַ��
 *
 * @attention ��
 *
 * @param pscStr1 [IN] ����#VOS_CHAR *��Դ�ַ�����ȡֵ��ΧΪ�ǿա�
 * @param pscStr2 [IN] ����#VOS_CHAR *��Ҫ�������ַ�����ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_NULL_PTR��                      0x00000000��pscStr1��pscStr2Ϊ�ա�
 * @retval #����ֵ                              ��һ�γɹ����ҵ��ַ���pscStr2�ĵ�ַ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_CHAR * VOS_StrStr(VOS_CHAR *pscStr1, VOS_CHAR *pscStr2);

/**
 * @ingroup  vos_libc
 * @brief �Ƚ������ַ�����
 *
 * @par ����:
 * �û����뱣֤�����������Ч�ԣ����pscStr1��pscStr2Ϊ��ָ�룬��ýӿڷ���0����ʱ���ַ������ʱ�ķ���ֵ��ͬ��
 *
 * @attention ��
 *
 * @param pscStr1 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���1��ȡֵ��ΧΪ�ǿա�
 * @param pscStr2 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���2��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #0                                   pscStr1����pscStr2��pscStr1��pscStr2����һ��Ϊ�ա�
 * @retval #����0                               pscStr1����pscStr2��
 * @retval #С��0                               pscStr1С��pscStr2��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_INT32 VOS_strcmp(const VOS_CHAR *pscStr1, const VOS_CHAR *pscStr2);

/**
 * @ingroup  vos_libc
 * @brief �Ƚ������ַ�����ǰn���ַ���
 *
 * @par ����:
 * �û����뱣֤�����������Ч�ԣ����pscStr1��pscStr2Ϊ��ָ�룬��ýӿڷ���0����ʱ���ַ������ʱ�ķ���ֵ��ͬ��
 *
 * @attention ��
 *
 * @param pscStr1 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���1��ȡֵ��ΧΪ�ǿա�
 * @param pscStr2 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���2��ȡֵ��ΧΪ�ǿա�
 * @param ulLen [IN] ����#VOS_UINT32�����Ƚϵ��ַ�����ȡֵ��ΧΪ��������
 *
 * @retval #0                                   pscStr1����pscStr2��pscStr1��pscStr2����һ��Ϊ�ջ�ulLenΪ0��
 * @retval #����0                               pscStr1����pscStr2��
 * @retval #С��0                               pscStr1С��pscStr2��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_StrNCmp
 */
extern VOS_INT32 VOS_strncmp(const VOS_CHAR *pscStr1, const VOS_CHAR *pscStr2, VOS_UINT32 ulLen);

/**
 * @ingroup  vos_libc
 * @brief ��Сд��ĸת���ɵȼ۵Ĵ�д��ĸ��
 *
 * @par ����:
 * �Ѹ�����Сд��ĸcCharת���ɵȼ۵Ĵ�д��ĸ��
 *
 * @attention
 * <ul><li>�����������ĸ����['a', 'z']��ȡֵ��Χ�ڣ��򲻽���ת����ԭֵ���ء�</li></ul>
 *
 * @param cChar [IN] ����#VOS_CHAR����Ҫת������ĸ��ȡֵ��ΧΪ�����ַ���
 *
 * @retval #�����ַ�                            ת�������ĸ����ԭֵ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_tolower
 */
extern VOS_CHAR VOS_toupper(VOS_CHAR cChar);

/**
 * @ingroup  vos_libc
 * @brief �Ѵ�д��ĸת���ɵȼ۵�Сд��ĸ��
 *
 * @par ����:
 * �Ѹ����Ĵ�д��ĸcCharת���ɵȼ۵�Сд��ĸ��
 *
 * @attention
 * <ul><li>�����������ĸ����['A', 'Z']��ȡֵ��Χ�ڣ��򲻽���ת����ԭֵ���ء�</li></ul>
 *
 * @param cChar [IN] ����#VOS_CHAR����Ҫת������ĸ��ȡֵ��ΧΪ�����ַ���
 *
 * @retval #�����ַ�                            ת�������ĸ����ԭֵ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_toupper
 */
extern VOS_CHAR VOS_tolower(VOS_CHAR cChar);

/**
 * @ingroup  vos_libc
 * @brief �Ƚ��ַ���������������ĸ�Ĵ�Сд��
 *
 * @par ����:
 * �û����뱣֤�����������Ч�ԣ����pscStr1��pscStr2Ϊ��ָ�룬��ýӿڷ���0����ʱ���ַ������ʱ�ķ���ֵ��ͬ��
 *
 * @attention
 * <ul><li>�û����뱣֤���������Ϊ��ָ�룬����ýӿڷ���0����ʱ���ַ������ʱ�ķ���ֵ��ͬ���޷����ݷ���ֵ�жϺ����Ƿ�ִ�гɹ���</li></ul>
 *
 * @param pscStr1 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���1��ȡֵ��ΧΪ�ǿա�
 * @param pscStr2 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���2��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #0                                   pscStr1����pscStr2��pscStr1��pscStr2����һ��Ϊ�ա�
 * @retval #����0                               pscStr1����pscStr2��
 * @retval #С��0                               pscStr1С��pscStr2��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_StrICmp
 */
extern VOS_INT32 VOS_stricmp(const VOS_CHAR *pscStr1, const VOS_CHAR *pscStr2);

/**
 * @ingroup  vos_libc
 * @brief �Ƚ������ַ�����ǰn���ַ����������ִ�Сд��
 *
 * @par ����:
 * �����Ƚϲ���pscStr1��pscStr2�ַ�����ǰulLen���ַ����������ִ�Сд��
 *
 * @attention
 * <ul><li>�û����뱣֤�����������Ч�ԣ����pscStr1��pscStr2Ϊ��ָ�룬��ýӿڷ���0����ʱ���ַ������ʱ�ķ���ֵ��ͬ��</li></ul>
 *
 * @param pscStr1 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���1��ȡֵ��ΧΪ�ǿա�
 * @param pscStr2 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���2��ȡֵ��ΧΪ�ǿա�
 * @param ulLen [IN] ����#VOS_UINT32�����Ƚϵ��ַ�����ȡֵ��ΧΪ��������
 *
 * @retval #0                                   pscStr1����pscStr2��pscStr1��pscStr2����һ��Ϊ�ջ�ulLenΪ0��
 * @retval #����0                               pscStr1����pscStr2��
 * @retval #С��0                               pscStr1С��pscStr2��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_INT32 VOS_strnicmp(const VOS_CHAR *pscStr1, const VOS_CHAR *pscStr2, VOS_UINT32 ulLen);

/**
 * @ingroup  vos_libc
 * @brief ����ʽ������д�뵽�ַ����С�
 *
 * @par ����:
 * ����ʽ������д�뵽�ַ����С�
 *
 * @attention
 * <ul>
 * <li>�û���֤��ʽ���Ļ���ռ��㹻��</li>
 * <li>�û���֤��ʽ�������ַ����еĸ�ʽ������ɱ��������ƥ�䡣</li>
 * <li>֧��d��x��s��u��p���ָ�ʽ�����͡�</li>
 * </ul>
 *
 * @param pscStr [OUT] ����#VOS_CHAR *����ʽ���Ļ��档ȡֵ��ΧΪ�ǿա�
 * @param pscFormat [IN] ����#const VOS_CHAR *����ʽ�������ַ�����ȡֵ��ΧΪ�ǿա�
 * @param argument [IN] ����#va_list��ָ��ɱ�����б��ָ�롣ȡֵ��ΧΪ�ǿա�
 *
 * @retval #-1                                  pscStr��pscFormatΪ�ա�
 * @retval #�Ǹ���                              ����д����ַ��ĸ�����
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_INT32 VOS_vsprintf(VOS_CHAR *pscStr, const VOS_CHAR *pscFormat, va_list argument);

/**
 * @ingroup  vos_libc
 * @brief ����ʽ������д�뵽�ַ����С�
 *
 * @par ����:
 * ����ʽ������д�뵽�ַ����С�
 *
 * @attention
 * <ul>
 * <li>�û���֤��ʽ���Ļ���ռ��㹻��</li>
 * <li>�û���֤��ʽ�������ַ����еĸ�ʽ������ɱ��������ƥ�䡣</li>
 * <li>֧��d��x��s��u��p���ָ�ʽ�����͡�</li>
 * </ul>
 *
 * @param pscStr [OUT] ����#VOS_CHAR *����ʽ���Ļ��档ȡֵ��ΧΪ�ǿա�
 * @param pscFmt [IN] ����#const VOS_CHAR *����ʽ�������ַ�����ȡֵ��ΧΪ�ǿա�
 * @param ... [IN] ��ѡ������
 *
 * @retval #-1                                  pscStr��pscFmtΪ�ա�
 * @retval #�Ǹ���                              ����д����ַ��ĸ�����
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_INT32 VOS_sprintf(VOS_CHAR * pscStr, const VOS_CHAR *pscFmt, ...);

/**
 * @ingroup  vos_libc
 * @brief ���ݿɱ�����б�ָ�룬����ʽ������д�뵽�ַ����С�
 *
 * @par ����:
 * ���ݸ�ʽ�������ݣ�д��̶��������ַ����ַ����С�
 *
 * @attention
 * <ul>
 * <li>�û���֤��ʽ���Ļ���ռ��㹻��</li>
 * <li>�û���֤��ʽ�������ַ����еĸ�ʽ������ɱ��������ƥ�䡣</li>
 * <li>�ַ�����������������Ҳ����˵��APIֻ��������д��uiMaxStrLen-1���ַ���Ȼ����ӽ�������</li>
 * <li>֧��d��x��s��u���ָ�ʽ�����͡�</li>
 * </ul>
 *
 * @param pscStr [OUT] ����#VOS_CHAR *����ʽ���Ļ��档ȡֵ��ΧΪ�ǿա�
 * @param uiMaxStrLen [IN] ��������VOS_UINT32����ʾ��ʽ���ַ�������󳤶ȡ�ȡֵ��ΧΪ��������
 * @param pscFormat [IN] ����#const VOS_CHAR *����ʽ�������ַ�����ȡֵ��ΧΪ�ǿա�
 * @param arguments [IN] ����#va_list��ָ��ɱ�����б��ָ�롣ȡֵ��ΧΪ�ǿա�
 *
 * @retval #-1                                  pscStr��pscFormatΪ�ջ�uiMaxStrLenΪ0���ʽ������ַ�������uiMaxStrLen��
 * @retval #�Ǹ���                              ����д����ַ��ĸ�����
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_INT32 VOS_nvsprintf(VOS_CHAR *pscStr, VOS_UINT32 uiMaxStrLen, const VOS_CHAR *pscFormat, va_list arguments);

/**
 * @ingroup  vos_libc
 * @brief ����ʽ������д�뵽�ַ����С�
 *
 * @par ����:
 * ���ݸ�ʽ�������ݣ�д��̶��������ַ����ַ����С�
 *
 * @attention
 * <ul>
 * <li>�û���֤��ʽ���Ļ���ռ��㹻��</li>
 * <li>�û���֤��ʽ�������ַ����еĸ�ʽ������ɱ��������ƥ�䡣</li>
 * <li>�ַ�����������������Ҳ����˵��APIֻ��������д��uiMaxStrLen-1���ַ���Ȼ����ӽ�������</li>
 * <li>֧��d��x��s��u���ָ�ʽ�����͡�</li>
 * </ul>
 *
 * @param pscStr [OUT] ����#VOS_CHAR *����ʽ���Ļ��档ȡֵ��ΧΪ�ǿա�
 * @param uiMaxStrLen [IN] ��������VOS_UINT32����ʾ��ʽ���ַ�������󳤶ȡ�ȡֵ��ΧΪ��������
 * @param pscFmt [IN] ����#const VOS_CHAR *����ʽ�������ַ�����ȡֵ��ΧΪ�ǿա�
 * @param ... [IN] ��ѡ������
 *
 * @retval #-1                                  pscStr��pscFmtΪ�ջ�uiMaxStrLenΪ0���ʽ������ַ�������uiMaxStrLen��
 * @retval #�Ǹ���                              ����д����ַ��ĸ�����
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_INT32 VOS_nsprintf(VOS_CHAR *pscStr, VOS_UINT32 uiMaxStrLen, const VOS_CHAR *pscFmt, ...);

#if (OS_OPTION_IO_INTF == YES)
/**
 * @ingroup  vos_libc
 * @brief ����ʽ���ַ���������ڡ�
 *
 * @par ����:
 * ����ʽ���ַ���������ڡ�
 *
 * @attention
 * <ul>
 * <li>��֧���ж��д�ӡ��</li>
 * <li>�û���֤��ʽ�������ַ����еĸ�ʽ������ɱ��������ƥ�䡣</li>
 * <li>�û���֤��ʽ������ַ���������512����������������</li>
 * <li>֧��c��d��i��x��s��%���ָ�ʽ�����͡�</li>
 * <li>���ӿ�������Ҫ536�ֽڵ�ջ�ռ䣬�û���֤�����ô˽ӿڵ�����ջ�ռ��㹻��</li>
 * </ul>
 *
 * @param pscFormat [IN] ����#VOS_CHAR *����ʽ���Ŀ����ַ�����ȡֵ��ΧΪ�ǿա�
 * @param ... [IN] ��ѡ������
 *
 * @retval #-1                                  pscFormatΪ�ա���Ӵ�ӡǰ׺ʧ�ܡ���ʽ������ַ�������512�����ַ����ʧ�ܡ�
 * @retval #VOS_OK                              0x00000000���ַ�����ɹ���
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_INT32 vos_printf(VOS_CHAR *pscFormat, ...);

/**
 * @ingroup  vos_libc
 * @brief ��������Ϣ�ַ�����ӡ����Ļ��
 *
 * @par ����:
 * ��������Ϣ�ַ�����ӡ����Ļ��
 *
 * @attention
 * <ul><li>�û���֤��ʽ������ַ���������512����������������</li></ul>
 *
 * @param s [IN] ����#const VOS_CHAR *��������Ϣ�ַ�����
 *
 * @retval ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_VOID perror(const VOS_CHAR *s);
#endif

/**
 * @ingroup  vos_libc
 * @brief ���ַ���ת��Ϊ�з���������
 *
 * @par ����:
 * ���ַ���pcStrת��Ϊ�з����������洢��pnVal�С�
 *
 * @attention ��
 *
 * @param pcStr [IN] ����#const VOS_CHAR *��Ҫת����ԭ�ַ�����ȡֵ��ΧΪ�ǿա�
 * @param pnVal [OUT] ����#VOS_INT32 *�����ڴ洢ת�����������ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF��pcStr��pnValΪ�ա�
 * @retval #VOS_OK                              0x00000000��ת���ɹ���
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_atoul
 */
extern VOS_INT32 VOS_atol(const VOS_CHAR *pcStr, VOS_INT32 *pnVal);

/**
 * @ingroup  vos_libc
 * @brief ���ڴ���ָ�����ȵ����ݸ��Ƶ�Ŀ���ڴ洦��
 *
 * @par ����:
 * ����pvSrc��ָ���ڴ�����ǰuvCount���ֽڵ�pvDest��ָ�ĵ�ַ�ϡ�
 *
 * @attention ��
 *
 * @param pvDest [IN/OUT] ����#VOS_VOID *��Ŀ���ڴ档ȡֵ��ΧΪ�ǿա�
 * @param pvSrc [IN] ����#const VOS_VOID *����Դ�ڴ档ȡֵ��ΧΪ�ǿա�
 * @param uvCount [IN] ����#VOS_SIZE_T���������ֽ�����ȡֵ��ΧΪ��������
 *
 * @retval #VOS_NULL_PTR                        0xFFFFFFFF��pvDest��pSrcPtr����һ��Ϊ�ջ�uvCountΪ0��
 * @retval #����ֵ                              Ŀ���ڴ�ĵ�ַ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_VOID * VOS_MemCpy(VOS_VOID *pvDest, const VOS_VOID *pvSrc, VOS_SIZE_T uvCount);

/**
 * @ingroup  vos_libc
 * @brief ���ַ����е�����Сд��ĸת���ɵȼ۵Ĵ�д��ĸ��
 *
 * @par ����:
 * �Ѹ����ַ���pcChar�е�����Сд��ĸת���ɵȼ۵Ĵ�д��ĸ��
 *
 * @attention
 * <ul><li>�����������ĸ����['a', 'z']��ȡֵ��Χ�ڣ��򲻽���ת����</li></ul>
 *
 * @param pcChar [IN] ����#VOS_CHAR *����Ҫת�����ַ�����ȡֵ��ΧΪ�ǿա�
 *
 * @retval ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_lowercase
 */
extern VOS_VOID VOS_uppercase(VOS_CHAR *pcChar);

/**
 * @ingroup  vos_libc
 * @brief ���ַ����е����д�д��ĸת���ɵȼ۵�Сд��ĸ��
 *
 * @par ����:
 * �Ѹ����ַ���pcChar�е����д�д��ĸת���ɵȼ۵�Сд��ĸ��
 *
 * @attention
 * <ul><li>�����������ĸ����['A', 'Z']��ȡֵ��Χ�ڣ��򲻽���ת����</li></ul>
 *
 * @param pcChar [IN] ����#VOS_CHAR *����Ҫת�����ַ�����ȡֵ��ΧΪ�ǿա�
 *
 * @retval ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_uppercase
 */
extern VOS_VOID VOS_lowercase(VOS_CHAR *pcChar);

/**
 * @ingroup  vos_libc
 * @brief ��ȡ�����ַ����ĳ��ȡ�
 *
 * @par ����:
 * ��ȡ�����ַ���pcstr�ĳ��ȣ���������������
 *
 * @attention ��
 *
 * @param pscStr [IN] ����#VOS_CHAR *��Ҫ��ȡ���ȵ��ַ�����ȡֵ��ΧΪ�ǿա�
 *
 * @retval #0��                                 0x00000000��pscStrΪ�ա�
 * @retval #������                              �ַ������ȡ�
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_SIZE_T VOS_StrLen(VOS_CHAR *pscStr);

/**
 * @ingroup  vos_libc
 * @brief �Ƚ������ַ�����
 *
 * @par ����:
 * �û����뱣֤�����������Ч�ԣ����pscStr1��pscStr2Ϊ��ָ�룬��ýӿڷ���0����ʱ���ַ������ʱ�ķ���ֵ��ͬ��
 *
 * @attention ��
 *
 * @param pscStr1 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���1��ȡֵ��ΧΪ�ǿա�
 * @param pscStr2 [IN] ����#const VOS_CHAR *�����Ƚϵ��ַ���2��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #0                                   pscStr1����pscStr2��pscStr1��pscStr2����һ��Ϊ�ա�
 * @retval #����0                               pscStr1������pscStr2��
 * @retval #С��0                               pscStr1��С��pscStr2��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_INT32 VOS_StrCmp(const VOS_CHAR *pscStr1, const VOS_CHAR *pscStr2);

/**
 * @ingroup  vos_libc
 * @brief ���ַ������ո����ָ������зָ
 *
 * @par ����:
 * ���ַ���*ppcstringp����pcdelim�и�������һ�ַ����зָ���ָ��*ppcstringpָ��ָ�֮�����һ�ַ�������ʼ��ַ��
 *
 * @attention
 * <ul><li>�ӿ��ڲ�δ���������Ч���жϣ���Ҫ�û���֤�����������Ч�ԡ�</li></ul>
 *
 * @param ppcstringp [IN] ����#VOS_CHAR **�������зָ���ַ�����ȡֵ��ΧΪ�ǿգ���*ppcstringpΪ�ǿա�
 * @param pcdelim [IN] ����#const VOS_CHAR *�������ķָ����ַ�����ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_NULL_PTR                        0x00000000��ppcstringp��*ppcstringp��pcdelimΪ�ա�
 * @retval #����ֵ                              ����*ppcstringp�ַ�������ʼ��ַ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_CHAR * VOS_strsep(register VOS_CHAR **ppcstringp, register const VOS_CHAR *pcdelim);

/**
 * @ingroup  vos_libc
 * @brief ���ַ�����ʽ("***.***.***.***")��IP��ַת��Ϊ������ʽ��IP��ַ��
 *
 * @par ����:
 * ��������ַ�����ʽ��IP��ַpscStr��ת��Ϊ������ʽ��ת������洢��pulIpAddrָ��ĵ�ַ��
 *
 * @attention ��
 *
 * @param pscStr [IN] ����#VOS_CHAR *����Ҫת��Ϊ�������͵��ַ�����ʽ��IP��ַ��ȡֵ��ΧΪ�ǿա�
 * @param pulIpAddr [OUT] ����#VOS_UINT32 *���洢ת�����������ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF��pscStr��pulIpAddr����һ��Ϊ�ջ�����ַ�����ʽ��IP��ַ���Ϸ���
 * @retval #VOS_OK                              0x00000000��ת���ɹ���
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_INT32 VOS_StrToIpAddr(VOS_CHAR *pscStr, VOS_UINT32 *pulIpAddr);

/**
 * @ingroup  vos_libc
 * @brief ��������ʽ��IP��ַת��Ϊ�ַ�����ʽ("***.***.***.***")��IP��ַ��
 *
 * @par ����:
 * �������������ʽ��IP��ַulAddr��ת��Ϊ�ַ�����ʽ��ת������洢��pscStrָ��ĵ�ַ��
 *
 * @attention ��
 *
 * @param ulAddr [IN] ����#VOS_UINT32����Ҫת��Ϊ�ַ���������IP��ַ��ȡֵ��ΧΪ����ֵ��
 * @param pscStr [OUT] ����#VOS_CHAR *�����ڴ洢ת������ַ�����ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_NULL_PTR                        0x00000000��pscStrΪ�ա�
 * @retval #����ֵ                              ת������ַ����ĵ�ַ��
 * @par ����:
 * <ul><li>vos_libc.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  ��
 */
extern VOS_CHAR * VOS_IpAddrToStr(VOS_UINT32 ulAddr, VOS_CHAR *pscStr);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_LIBC_H__

