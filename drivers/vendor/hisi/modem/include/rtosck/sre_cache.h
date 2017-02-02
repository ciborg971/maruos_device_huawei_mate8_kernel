/**
 * @file sre_cache.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������CACHEģ��Ķ���ͷ�ļ��� \n
 */
/** @defgroup sre_cache Cache
   *@ingroup SRE_kernel
*/

#ifndef _SRE_CACHE_H
#define _SRE_CACHE_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
* @ingroup sre_cache
* cache����Ϊָ��cache��
*/
#define OS_ICACHE_TYPE                                      1

/**
* @ingroup sre_cache
* cache����Ϊ����cache��
*/
#define OS_DCACHE_TYPE                                      2

/**
* @ingroup sre_cache
* cache��С�������ò��Ϸ���
*/
#define SRE_CACHE_SIZE_INVALID                              0x00000001

/**
* @ingroup sre_cache
*cache��ַ�����������ò��Ϸ� ��
*/
#define SRE_CACHE_ADDR_INVALID                              0x00000002

/**
* @ingroup sre_cache
*cache���Ͳ������ò��Ϸ� ��
*/
#define SRE_CACHE_TYPE_INVALID                              0x00000003

/**
* @ingroup sre_cache
* cache�����������㡣
*/
#define SRE_CACHE_NOAREA_LOCK                               0x00000006

/**
* @ingroup sre_cache
* cache TAG��ȡ�ӿ���ε�ַΪ�ա�
*/
#define SRE_CACHE_TAG_PTR_NULL                              0x00000007

/**
* @ingroup sre_cache
*cache������ַ��������
*/
#define SRE_CACHE_ADDR_LOCKED                               0x00000008

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)

typedef enum
{
    CACHE_UNIFY     = 0,                    /**< Unifyģʽ          */
    CACHE_SPLIT     = 1                     /**< Splitģʽ          */
} OS_CACHE_MODE_E;

typedef enum
{
    ONE_LINE_PF         = 0,                /**< 1��cacheline       */
    TWO_LINES_PF        = 1,                /**< 2��cacheline       */
    ILLEGAL_ONE_LINE_PF = 2,                /**< ��Ч               */
    THREE_LINES_PF      = 3,                /**< 3��cacheline       */
    INVALID_DCC_HWPF    = 4                 /**< ��Ч               */
} OS_DCC_HWPF_POLICY_E;

typedef enum
{
    ZERO_LINE_OFFSET    = 0,                /**< Ԥȡ0��cacheline   */
    QUATER_LINE_OFFSET  = 1,                /**< Ԥȡ1/4��cacheline */
    HALF_LINE_OFFSET    = 2,                /**< Ԥȡ1/2��cacheline */
    THREE_QUARTERS_LINE_OFFSET = 3,         /**< Ԥȡ3/4��cacheline */
    INVALID_PCC_HWPF = 4                    /**< ��Ч               */
} OS_PCC_HWPF_POLICY_E;

#endif

/**
* @ingroup sre_cache
* cache������: ʹ��cache�ӿڣ�����cache�����СΪ0�����߼�������Ԥȡ�ӿڲ�����ʵ�ʴ�С�������ɲ�����Χ���򷵻ظ�ֵ��
*
* ֵ: 0x02001101
*
* �������: ����������ռ��С��
*/
#define OS_ERRNO_CACHE_SIZE_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_SIZE_INVALID)

/**
 * @ingroup sre_cache
 * cache������: ʹ�ü��������Լ���ȡtag�ӿ�ʱ��������ַ������cache�ķ�Χ��
 *
 * ֵ: 0x02001102
 *
 * �������: ��鿴������ַ�ռ��Ƿ��cache��
 */
#define OS_ERRNO_CACHE_ADDR_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_ADDR_INVALID)

/**
 * @ingroup sre_cache
 * cache������: ����cache�ӽ�������ȡtag�ӿ��Լ�SD6183����Icacheģʽʱ�������cache���Ͳ���ȷ��Ŀǰֻ֧��ICACHE���мӽ�������������ֵ�������룬��ȡcache tag�ӿ�֧��ָ��cache������cache���ͣ�ֻ����PCC����DCC��SD6183����ICacheģʽʱֻ����Split����UNIFYģʽ��
 *
 * ֵ: 0x02001103
 *
 * �������: ��鿴�����cache�����Ƿ�֧�֡�
 */
#define OS_ERRNO_CACHE_TYPE_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_TYPE_INVALID)

/**
 * @ingroup sre_cache
 * cache������: cache���������У�����ĳһ������������㡣
 *
 * ֵ: 0x02001106
 *
 * �������: ���������ӿ���Ҫ���ʹ�ã������ռ䷶Χ���ޣ���鿴�Ƿ���ж�μ�����
 */
#define OS_ERRNO_CACHE_NOAREA_LOCK                          SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_NOAREA_LOCK)

/**
 * @ingroup sre_cache
 * cache������: cache tag��ȡ�ӿڣ������tag�ṹ��ָ��Ϊ�ա�
 *
 * ֵ: 0x02001107
 *
 * �������: ��������Ч�Ľṹ��ָ�롣
 */
#define OS_ERRNO_CACHE_TAG_PTR_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_TAG_PTR_NULL)

/**
 * @ingroup sre_cache
 * cache������: ����ָ��cache��Ч�ӿ�ʱ�����ڸ���Ч�ռ���ڼ����������Ч���ɹ���
 *
 * ֵ: 0x02001108
 *
 * �������: ��Чǰ����õ�ַ�Ƿ������
 */
#define OS_ERRNO_CACHE_ADDR_LOCKED                          SRE_ERRNO_OS_ERROR(OS_MID_CACHE, SRE_CACHE_ADDR_LOCKED)

/**
 * @ingroup sre_cache
 * cache������: �˺Ŵ���HiDSPֻ��Ϊ0-33��
 *
 * ֵ: 0x02001109
 *
 * �������: ��������ȷ�ĺ˺š�
 */
#define OS_ERRNO_CACHE_CORE_ID_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x09)

/**
 * @ingroup sre_cache
 * cache������: PCCӲ��Ԥȡ���Դ���
 *
 * ֵ: 0x0200110a
 *
 * �������: ���޸�PCCӲ��Ԥȡ���ԡ�
 */
#define OS_ERRNO_CACHE_PCC_HWPF_POLICY_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0a)

/**
 * @ingroup sre_cache
 * cache������: ��ȡָ����ַ��cache tag��Ϣʱ�������CACHE Tag�ṹ��ָ��Ϊ�ա�
 *
 * ֵ: 0x0200110c
 *
 * �������: ���������Ч�Ľṹ��ָ�롣
 */
#define OS_ERRNO_CACHE_INFO_PTR_NULL                        SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0c)

/**
 * @ingroup sre_cache
 * cache������: DCCӲ��Ԥȡ���Դ���
 *
 * ֵ: 0x0200110d
 *
 * �������: ���޸�DCCӲ��Ԥȡ���ԡ�
 */
#define OS_ERRNO_CACHE_DCC_HWPF_POLICY_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0d)

/**
 * @ingroup sre_cache
 * CACHE������: PCC ���������㡣
 *
 * ֵ: 0x0200110e
 *
 * ������� :4��ɼ�����ַ�����Ѿ�ʹ���꣬��������ܼ���������
 */
#define OS_ERRNO_CACHE_PCC_LOCK_BLOCK_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0e)

/**
 * @ingroup sre_cache
 * ��Ϣ�����룺cache�������ĵ�ַ��Χ�����˷�ת��
 *
 * ֵ: 0x0200110f
 *
 * �������: �뱣֤������������ַ��Ӧ�������ַ����������û�з�����ת��
 *
 */
#define OS_ERRNO_CACHE_REGION_REVERSE                       SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x0f)

/**
 * @ingroup sre_cache
 * ��Ϣ�����룺cache�������ĵ�ַ��Χ�Ѿ�������
 *
 * ֵ: 0x02001110
 *
 * �������: ȷ�ϵ�ǰ�������ĵ�ַ��Χ�Ƿ��ѱ���������
 *
 */
#define OS_ERRNO_CACHE_REGION_ALREARY_LOCK                  SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x10)

/**
 * @ingroup sre_cache
 * ��Ϣ�����룺�첽��ʽ����cache���͵���Ϣ����Ϊ�ա�
 *
 * ֵ: 0x02001111
 *
 * �������: �뱣֤�������Ϣ���ݲ�Ϊ�ա�
 *
 */
#define OS_ERRNO_CACHE_ASYNC_MSG_NULL                       SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x11)

/**
 * @ingroup sre_cache
 * ��Ϣ�����룺����������Ӧ�ĵ�ַ����δ������
 *
 * ֵ: 0x02001112
 *
 * �������: ���鴫�������ַ��Χ�Ƿ���ȷ��
 *
 */
#define OS_ERRNO_CACHE_PCC_LOCK_REGION_UNLOCK               SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x12)

/**
 * @ingroup sre_cache
 * ��Ϣ�����룺L2 Cache���ƻ���ַΪ0��
 *
 * ֵ: 0x02001113
 *
 * �������: L2 Cache���ƻ���ַ����Ϊ0��
 *
 */
#define OS_ERRNO_L2_CACHE_CTRL_BASE_ADDR_ZERO               SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x13)

/**
 * @ingroup sre_cache
 * ��Ϣ�����룺����L2 Cache�͹���Suspend��Resume��������ʱ��L2 Cacheδ��ʼ����
 *
 * ֵ: 0x02001114
 *
 * �������: ����L2 Cache�͹���Suspend��Resume��������ǰ����Ҫ��Cache���г�ʼ����
 *
 */
#define OS_ERRNO_L2_CACHE_NOT_INIT                          SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x14)

/**
 * @ingroup sre_cache
 * ��Ϣ�����룺�ظ����߸���ע���Ѿ�ע���L2 Cache�Ż����ӡ�
 *
 * ֵ: 0x02001115
 *
 * �������: ע��L2 Cache�Ż�����ʱ��ȡ��ǰֻ��ע��һ�Ρ�
 *
 */
#define OS_ERRNO_L2_CACHE_HOOK_EXIST                        SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x15)

/**
 * @ingroup sre_cache
 * ��Ϣ�����룺�ظ�Suspend L2 Cache��
 *
 * ֵ: 0x02001116
 *
 * �������: Suspend L2 Cache�󣬱���Resume L2 Cache�������ٴ�Suspend L2 Cache��
 *
 */
#define OS_ERRNO_L2_CACHE_ALREADY_SUSPENDED                 SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x16)

/**
 * @ingroup sre_cache
 * ��Ϣ�����룺δSuspend L2 CacheǰResume L2 Cache��
 *
 * ֵ: 0x02001117
 *
 * �������: ������Suspend L2 Cache�󣬲���Resume L2 Cache��
 *
 */
#define OS_ERRNO_L2_CACHE_NOT_SUSPENDED                     SRE_ERRNO_OS_ERROR(OS_MID_CACHE, 0x17)

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC))

/**
 * @ingroup sre_cache
 * CACHE Tag �ṹ����Ϣ��
 */
typedef struct tagCacheCb
{
    UINT32  uwCacheTag; /**< cache tag��������Ϣ                        */
    BOOL    bDirty;     /**< dcache�е������Ƿ��޸ģ�����Dache��Ч    */
    BOOL    bLock;      /**< cache�е������Ƿ񱻼���������SD6182��SD6157ƽ̨��Ч */
    BOOL    bValid;     /**< cache�е������Ƿ���Ч                      */
} CACHE_LINE_INFO_S;

#elif (OS_HARDWARE_PLATFORM == OS_HIDSP)

/**
 * @ingroup sre_cache
 * CACHE Tag �ṹ����Ϣ��
 */
typedef struct tagCacheCb
{
    UINT32 uwCacheTag;  /**< cache tag��������Ϣ                        */
    UINT32 uwCacheData; /**< cache data��������Ϣ                       */
} CACHE_LINE_INFO_S;

#endif

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

typedef VOID  (* CACHE_INIT_HOOK)(VOID);
typedef VOID  (* CACHE_SUSPEND_HOOK)(VOID);
typedef VOID  (* CACHE_RESUME_HOOK)(VOID);

#endif
#if (OS_OPTION_DCACHE == NO)

/**
 * @ingroup sre_cache
 * ������Cache�����ݻ�д���ڴ档
 */
#define  SRE_DCacheFlush(pAddr, uwSize, bWait)          SRE_OK

/**
 * @ingroup sre_cache
 * ������Cache�е�������Ч��
 */
#define  SRE_DCacheInv(pAddr, uwSize, bWait)            SRE_OK

/**
 * @ingroup sre_cache
 * ������Cache������ݻ�д���ڴ沢��Ч������cache��
 */
#define  SRE_DCacheFlushInv(pAddr, uwSize, bWait)       SRE_OK

/**
 * @ingroup sre_cache
 * �ȴ�DCache������ɡ�
 */
#define  SRE_DCacheWait(VOID)

#else

/**
 * @ingroup  sre_cache
 * @brief ��д����DCACHE
 *
 * @par ����:
 * ˢ������DCACHE, �������������ݻ�д���ڴ�
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182��SD6157��CORTEX_AXƽ̨��SD6181/SD6108 CPU�ˡ�SD6183֧��ˢ������DCACHE����</li>
 * <li>����Cortex-A9ƽ̨����L2 Cache���ܴ�ʱ���ڹ��ж������½��иò��������ж�ʱ�䳤��������Dcache��С�����ȡ�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheFlushAll(VOID);

/**
 * @ingroup  sre_cache
 * @brief ������Cache������ݻ�д���ڴ档
 *
 * @par ����:
 * ��ָ����ַ���������Cache���ݻ�д���ڴ��С�
 *
 * @attention
 * <ul>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>ֻ��SD6182��SD6157��SD6108��SD6181��CPU�ˡ�SD6183��Cortex-AX֧�ָù��ܡ�</li>
 * <li>����Cortex-A9ƽ̨����L2 Cache���ܴ�ʱ������Ĳ���#bWait����ΪTRUE</li>
 * <li>����Cortex-A9ƽ̨����L2 Cache���ܴ�ʱ���ڹ��ж������½��иò��������ж�ʱ�䳤����Dcache��д�ڴ��С�����ȡ�</li>
 * <li>����SD6183ƽ̨���û�����������ַ�ռ��Ӧ�������ַ�ռ����������û�з�ת</li>
 * </ul>
 *
 * @param  pAddr    [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize   [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait    [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239��SD6183ƽ̨��������ַδӳ�䡣
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheFlush(VOID *pAddr, UINT32 uwSize, BOOL bWait);

/**
 * @ingroup  sre_cache
 * @brief ����Cache��д����Ч��
 *
 * @par ����:
 * ��ָ����ַ���������Cache���ݻ�д���ڴ沢��Ч����
 *
 * @attention
 * <ul>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>ֻ��SD6182��SD6157��SD6108��SD6181��CPU�ˡ�SD6183��Cortex-AX֧�ָù��ܡ�</li>
 * <li>����Cortex-A9ƽ̨����L2 Cache���ܴ�ʱ������Ĳ���#bWait����ΪTRUE</li>
 * <li>����Cortex-A9ƽ̨����L2 Cache���ܴ�ʱ���ڹ��ж������½��иò��������ж�ʱ�䳤����Dcache��д����Ч�ڴ��С�����ȡ�</li>
 * <li>����SD6183ƽ̨���û�����������ַ�ռ��Ӧ�������ַ�ռ����������û�з�ת</li>
 * </ul>
 *
 * @param  pAddr   [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize  [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait   [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239��SD6183ƽ̨��������ַδӳ�䡣
 * @retval #SRE_OK                        0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_ICacheInv
 */
extern UINT32 SRE_DCacheFlushInv(VOID *pAddr, UINT32 uwSize, BOOL bWait);

/**
 * @ingroup  sre_cache
 * @brief ����Cache��Ч��
 *
 * @par ����:
 * ��ָ����ַ���������Cache������Ч����
 *
 * @attention
 * <ul>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>ֻ��SD6182��SD6157��SD6108��SD6181��CPU�ˡ�SD6183��Cortex-AX֧�ָù��ܡ�</li>
 * <li>����SD6183ƽ̨���û�����������ַ�ռ��Ӧ�������ַ�ռ����������û�з�ת</li>
 * </ul>
 *
 * @param  pAddr   [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize  [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait   [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239��SD6183ƽ̨��������ַδӳ�䡣
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_ICacheInv | SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheInv(VOID *pAddr, UINT32 uwSize, BOOL bWait);

#if ( (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC) || (OS_HARDWARE_PLATFORM == OS_HIDSP))

/**
 * @ingroup  sre_cache
 * @brief Ԥȡ����CACHE
 *
 * @par ����:
 * ����ַΪpVirtAddr����СΪuwSize���ڴ�����Ԥȡ������cache�У��ɸ��ݲ���bWaitѡ���Ƿ�ȴ���
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182��SD6157��SD6183ƽ̨֧��ԤȡDCACHE����</li>
 * <li>�û�����ĵ�ַ�ռ���cache line������ܳ���dcache��С</li>
 * </ul>
 *
 * @param  pVirtAddr  [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize     [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait      [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #SRE_OK                        0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_DCachePrefetch(VOID * pVirtAddr, UINT32 uwSize, BOOL bWait);

/**
 * @ingroup  sre_cache
 * @brief ����ָ��cache
 *
 * @par ����:
 * ������ΪuwCacheType����ַΪpVirtAddr����СΪuwSize��ָ��cache���м���������
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182��SD6157��SD6183ƽ̨֧�ּ���ָ��CACHE����</li>
 * <li>��֧������cache����</li>
 * <li>����SD6182ƽ̨��cache�����׵�ַ�ʹ�Сcache line����ʱ��ÿ��4-WAY�����ܼ���3-WAY�������������СΪcache��С���ķ�֮��</li>
 * <li>����SD6182ƽ̨��cache��С������λΪһ��cache line�����ǵ���β��ַ������������ܻ��˷ѵ�����cache line�������ɼ�����С����Ϊ�ķ�֮����cache��С��ȥ����cache line</li>
 * <li>����SD6183ƽ̨������ָ��4����ַ��Χ������������cache�ռ����ȫ��������ĳһSetȫ�������󣬸�Set��Ӧ�������ݲ����ٽ�cache��</li>
 * <li>����SD6183ƽ̨���û�����������ַ�ռ��Ӧ�������ַ�ռ����������û�з�ת</li>
 * </ul>
 *
 * @param  uwCacheType  [IN] ����#UINT32��cache���ͣ�OS_ICACHE_TYPE��ʾָ��cache,Ŀǰֻ֧��ָ��cache��
 * @param  pVirtAddr    [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize       [IN] ����#UINT32���ڴ��Ĵ�С��
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #OS_ERRNO_CACHE_ADDR_INVALID   0x02001102������cache�ռ䷶Χ������
 * @retval #OS_ERRNO_CACHE_NOAREA_LOCK    0x02001106�������������㡣
 * @retval #OS_ERRNO_CACHE_TYPE_INVALID   0x02001103���������Ͳ���ȷ��Ŀǰֻ֧��ICACHE��
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239��SD6183ƽ̨��������ַδӳ�䡣
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_CacheUnLock
 */
extern UINT32 SRE_CacheLock(UINT32 uwCacheType, VOID *pVirtAddr,UINT32 uwSize);

/**
 * @ingroup  sre_cache
 * @brief ����ָ��cache
 *
 * @par ����:
 * ������ΪuwCacheType����ַΪpVirtAddr����СΪuwSize��ָ��cache���н���������
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182��SD6157��SD6183ƽ̨֧�ֽ���ָ��CACHE����</li>
 * <li>��֧������cache����</li>
 * <li>����SD6182��SD6157ƽ̨��������ӿڱ���һ�£���������СΪ�ķ�֮����cache��С��ȥ��β��ַcache line������������</li>
 * <li>����SD6183ƽ̨���û�����������ַ�ռ��Ӧ�������ַ�ռ����������û�з�ת</li>
 * </ul>
 *
 * @param  uwCacheType  [IN] ����#UINT32��cache���ͣ�OS_ICACHE_TYPE��ʾָ��cache,Ŀǰֻ֧��ָ��cache��
 * @param  pVirtAddr    [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize       [IN] ����#UINT32���ڴ��Ĵ�С��
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #OS_ERRNO_CACHE_ADDR_INVALID   0x02001102������cache�ռ䷶Χ������
 * @retval #OS_ERRNO_CACHE_TYPE_INVALID   0x02001103���������Ͳ���ȷ��Ŀǰֻ֧��ICACHE��
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239��SD6183ƽ̨��������ַδӳ�䡣
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_CacheLock
 */
extern UINT32 SRE_CacheUnLock(UINT32 uwCacheType, VOID *pVirtAddr,UINT32 uwSize);
#endif

/**
 * @ingroup  sre_cache
 * @brief �ȴ�����Cache������ɡ�
 *
 * @par ����:
 * �ȴ�DCache������ɡ�
 *
 * @attention
 * <ul>
 * <li>Cortex-AXƽ̨��֧�ִ˹��ܡ�</li>
 * <li>����Բ��ȴ��ķ�ʽʹ������cache�Ľӿڣ�����ʹ������ӿڱ�֤��ȫ�ԡ�</li>
 * </ul>
 *
 *@param ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC))
#ifndef _TOOL_WIN32
OS_SEC_ALW_INLINE INLINE VOID SRE_DCacheWait(VOID)
{
    OS_EMBED_ASM("memw");
}
#else
OS_SEC_ALW_INLINE INLINE VOID SRE_DCacheWait(VOID)
{
    ;
}

#endif
#elif (OS_HARDWARE_PLATFORM == OS_HIDSP)
extern VOID SRE_DCacheWait(VOID);
#endif

#endif /* (OS_OPTION_DCACHE == NO) */

#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC) || (OS_HARDWARE_PLATFORM == OS_HIDSP))

/**
 * @ingroup  sre_cache
 * @brief ��Ч����ָ��Cache
 *
 * @par ����:
 * ������ָ��Cache��Ч��
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182,SD6157,SD6181,SD6108,SD6183ƽ̨֧����Ч����ָ��Cache���ܡ�</li>
 * <li>SD6182��SD6157ƽָ̨��Cache�����������ýӿ��н������ܡ�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_ICacheInv
 */
extern VOID SRE_ICacheInvAll(VOID);

/**
 * @ingroup  sre_cache
 * @brief ��ȡָ����ַ��cache tag��Ϣ
 *
 * @par ����:
 * ������ΪuwCacheType����ַΪpVirtAddr��cache Tag��Ϣ��ȡ���洢��pstCacheInfo�ṹ���С�
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182/SD6157/SD6181/SD6108/SD6183ƽ̨֧�ֻ�ȡcache tag��Ϣ����</li>
 * <li>SD6181/SD6108ƽ̨DSP�˲�֧�ֻ�ȡdcache tag��Ϣ����</li>
 * <li>�����ȡ��ָ����ַ��Cache Tag��ϢΪ0��˵���õ�ַ����Cache��</li>
 * </ul>
 *
 * @param  uwCacheType  [IN]  ����#UINT32��OS_ICACHE_TYPE��ʾָ��cache��OS_DCACHE_TYPE��ʾ����cache��
 * @param  pVirtAddr    [IN]  ����#VOID *���ڴ�����ʼ��ַ������SD6182/SD6157ƽ̨����Cache��ַ��ΧΪ[0x08000000, 0x60000000)������SD6181/SD08ƽ̨����Cache��ַ��ΧΪ[0x10000000, 0x60000000)
 * @param  pstCacheInfo [OUT] ����#CACHE_LINE_INFO_S *����ȡ��tag��Ϣ�ṹ�塣
 *
 * @retval #OS_ERRNO_CACHE_TYPE_INVALID   0x02001103��cache�������벻����
 * @retval #OS_ERRNO_CACHE_TAG_PTR_NULL   0x02001107������Ĵ��Tag��Ϣ��ָ��ΪNULL��
 * @retval #OS_ERRNO_CACHE_ADDR_INVALID   0x02001102������ĵ�ַ���Ϸ���
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239��SD6183ƽ̨��������ַδӳ�䡣
 * @retval #SRE_OK                        0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_CacheLineInfoGet(UINT32 uwCacheType, VOID *pVirtAddr, CACHE_LINE_INFO_S *pstCacheInfo);

#endif

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)
/**
 * @ingroup  sre_cache
 * @brief ����PCCģʽ
 *
 * @par ����:
 * PCC ģʽ����: UNIFY/SPLIT
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6183ƽ̨֧������ICacheģʽ</li>
 * </ul>
 *
 * @param  uwCoreID      [IN] ����#UINT32��ָ���ĺ˺š�
 * @param  enMode        [IN] ����#OS_CACHE_MODE��SPLIT/UNIFYģʽ��
 *
 * @retval #OS_ERRNO_CACHE_CORE_ID_INVALID   0x02001109��ָ���ĺ˺ŷǷ���
 * @retval #OS_ERRNO_CACHE_TYPE_INVALID      0x02001103��ָ����cache���ͷǷ���
 * @retval #SRE_OK                           0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern UINT32 SRE_ICacheModeSet(UINT32 uwCoreID, OS_CACHE_MODE_E enMode);

/**
 * @ingroup  sre_cache
 * @brief ����PCCӲ��Ԥȡ
 *
 * @par ����:
 * PCC ��Ӳ��Ԥȡ��ʹ��ȥʹ�ܣ��Լ�Ԥȡ�Ĳ�������
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6183ƽ̨֧������ICacheӲ��Ԥȡ����</li>
 * </ul>
 *
 * @param  uwCoreID      [IN] ����#UINT32��ָ���ĺ˺š�
 * @param  bEnable       [IN] ����#BOOL��1:ʹ�ܣ�0:ȥʹ�ܡ�
 * @param  enHwPfPolicy  [IN] ����#OS_PCC_HWPF_POLICY_E��4�ֲ��ԡ�
 *
 * @retval #OS_ERRNO_CACHE_PCC_HWPF_POLICY_INVALID 0x0200110a��ָ����Ӳ��Ԥȡ���ԷǷ���
 * @retval #OS_ERRNO_CACHE_CORE_ID_INVALID         0x02001109��ָ���ĺ˺ŷǷ���
 * @retval #SRE_OK                                 0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_DCacheHwPfCfg
 */
extern UINT32 SRE_ICacheHwPfCfg(UINT32 uwCoreID, BOOL bEnable, OS_PCC_HWPF_POLICY_E enHwPfPolicy);

/**
 * @ingroup  sre_cache
 * @brief ����DCCӲ��Ԥȡ
 *
 * @par ����:
 * DCC ��Ӳ��Ԥȡ��ʹ��ȥʹ�ܣ��Լ�Ԥȡ�Ĳ�������
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6183ƽ̨֧������DCacheӲ��Ԥȡ����</li>
 * </ul>
 *
 * @param  uwCoreID      [IN] ����#UINT32��ָ���ĺ˺š�
 * @param  bEnable       [IN] ����#BOOL��1:ʹ�ܣ�0:ȥʹ�ܡ�
 * @param  enHwPfPolicy  [IN] ����#OS_DCC_HWPF_POLICY_E��3�ֲ��ԡ�
 *
 * @retval #OS_ERRNO_CACHE_PCC_HWPF_POLICY_INVALID 0x0200110a��ָ����Ӳ��Ԥȡ���ԷǷ���
 * @retval #OS_ERRNO_CACHE_CORE_ID_INVALID         0x02001109��ָ���ĺ˺ŷǷ���
 * @retval #SRE_OK                                 0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_ICacheHwPfCfg
 */
extern UINT32 SRE_DCacheHwPfCfg(UINT32 uwCoreID, BOOL bEnable,  OS_DCC_HWPF_POLICY_E enHwPfPolicy);

/**
 * @ingroup  sre_cache
 * @brief �첽��ʽ������Cache������ݻ�д���ڴ沢������Ϣ��
 *
 * @par ����:
 * ��ָ����ַ���������Cache���ݻ�д���ڴ��У����������ʱ��Ŀ���ַ������Ϣ֪ͨ��
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6183ƽ̨֧���첽��ʽ��д����cache��ֻ����MSGM�ĵ�ַ�ռ䷢����Ϣ</li>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>��uwSizeΪ0xffffffffʱ���൱�ڻ�дȫ��������cache</li>
 * <li>ͨ��MSGM��SRE_QportAddrGet�ӿڿ��Եõ�Ŀ���ָ�����еĵ�ַ�����sre_msgm.h</li>
 * <li>����SD6183ƽ̨���û�����������ַ�ռ��Ӧ�������ַ�ռ����������û�з�ת</li>
 * </ul>
 *
 * @param  pAddr     [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize    [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait     [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 * @param  uwDstAddr [IN] ����#UINT32��Ŀ��MSGM���е��׵�ַ��
 * @param  auwData   [IN] ����#UINT32*�������͵���Ϣ�����׵�ַ����Ϣ���ݳ�����Ϊ16�ֽڡ�
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239��SD6183ƽ̨��������ַδӳ�䡣
 * @retval #OS_ERRNO_CACHE_ASYNC_MSG_NULL 0x02001111�����͵���Ϣ����Ϊ�ա�
 * @retval #SRE_OK                        0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_DCacheFlush
 */
extern UINT32 SRE_DCacheFlushAsync(VOID *pAddr, UINT32 uwSize, BOOL bWait, UINT32 uwDstAddr, UINT32 *auwData);

/**
 * @ingroup sre_cache
 * @brief �첽��ʽ����Cache��Ч��������Ϣ��
 *
 * @par ����:
 * �첽��ʽ��ָ����ַ���������Cache������Ч,���������ʱ��Ŀ���ַ������Ϣ֪ͨ��
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6183ƽ̨֧���첽��ʽ��Ч����cache��ֻ����MSGM�ĵ�ַ�ռ䷢����Ϣ</li>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>��uwSizeΪ0xffffffffʱ���൱����Чȫ��������cache</li>
 * <li>ͨ��MSGM�Ľӿڿ��Եõ�Ŀ���ָ�����еĵ�ַ�����sre_msgm.h</li>
 * <li>����SD6183ƽ̨���û�����������ַ�ռ��Ӧ�������ַ�ռ����������û�з�ת</li>
 * </ul>
 *
 * @param  pAddr     [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize    [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait     [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 * @param  uwDstAddr [IN] ����#UINT32��Ŀ��MSGM���е��׵�ַ��
 * @param  auwData   [IN] ����#UINT32�������͵���Ϣ���ݡ�

 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239��SD6183ƽ̨��������ַδӳ�䡣
 * @retval #OS_ERRNO_CACHE_ASYNC_MSG_NULL 0x02001111�����͵���Ϣ����Ϊ�ա�
 * @retval #SRE_OK                        0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_DCacheInv
 */
extern UINT32 SRE_DCacheInvAsync(VOID *pAddr, UINT32 uwSize, BOOL bWait, UINT32 uwDstAddr, UINT32 *auwData);

/**
 * @ingroup  sre_cache
 * @brief �첽��ʽ������Cache��д����Ч������Ϣ��
 *
 * @par ����:
 * �첽��ʽ��ָ����ַ���������Cache���ݻ�д���ڴ沢��Ч,���������ʱ��Ŀ���ַ������Ϣ֪ͨ��
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6183ƽ̨֧���첽��ʽ��д����Ч����cache��ֻ����MSGM�ĵ�ַ�ռ䷢����Ϣ</li>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>��uwSizeΪ0xffffffffʱ���൱�ڻ�д��Чȫ��������cache��</li>
 * <li>ͨ��MSGM�Ľӿڿ��Եõ�Ŀ���ָ�����еĵ�ַ�����sre_msgm.h</li>
 * <li>����SD6183ƽ̨���û�����������ַ�ռ��Ӧ�������ַ�ռ����������û�з�ת</li>
 * </ul>
 *
 * @param  pAddr     [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize    [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait     [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 * @param  uwDstAddr [IN] ����#UINT32��Ŀ��MSGM���е��׵�ַ��
 * @param  auwData   [IN] ����#UINT32 *�������͵���Ϣ���ݡ�
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239��SD6183ƽ̨��������ַδӳ�䡣
 * @retval #OS_ERRNO_CACHE_ASYNC_MSG_NULL 0x02001111�����͵���Ϣ����Ϊ�ա�
 * @retval #SRE_OK                        0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_DCacheFlushInv
 */
extern UINT32 SRE_DCacheFlushInvAsync(VOID *pAddr, UINT32 uwSize, BOOL bWait, UINT32 uwDstAddr, UINT32 *auwData);

#endif

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup  sre_cache
 * @brief Cache��ʼ��
 *
 * @par ����:
 * ��L1/L2����Cache��ʼ������ʹ��L1/L2 Cache���ܡ�
 *
 * @attention
 * <ul>
 * <li>��Cortex-A9ƽ̨֧�ִ˹��ܣ�����ֻ�е��û���Ҫʹ��L2 Cache����ʱ������Ҫ���ô˽ӿڡ�</li>
 * <li>�˽ӿڱ���Ҫ��#SRE_HardBootInit�е��á�</li>
 * </ul>
 *
 * @param  uwL2CtrBase   [IN] ����#UINT32��L2 Cache���ƻ���ַ����Ҫ���ó�ʵ�ʵ�L2 Cache���ƻ���ַ��
 *
 * @retval #OS_ERRNO_L2_CACHE_CTRL_BASE_ADDR_ZERO  0x02001113�������L2 Cache���ƻ���ַΪ0��
 * @retval #SRE_OK                                 0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_CacheInitHookReg
 */
extern UINT32 SRE_CacheInit(UINT32 uwL2CtrBase);

/**
 * @ingroup  sre_cache
 * @brief L2 Cache Suspend����
 *
 * @par ����:
 * ����͹���ǰ��L2 Cache Suspend������
 *
 * @attention
 * <ul>
 * <li>��Cortex-A9ƽ̨֧�ִ˹��ܣ�����ֻ�е��û�ʹ��L2 Cache����ʱ������Ҫ���ô˽ӿڡ�</li>
 * <li>��Ҫ�ڽ���͹���ǰ���ô˽ӿڡ�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval #OS_ERRNO_L2_CACHE_NOT_INIT             0x02001114��������L2 Cache��ʼ������ô˽ӿڡ�
 * @retval #OS_ERRNO_L2_CACHE_ALREADY_SUSPENDED    0x02001116��L2 Cache�Ѿ���Suspend��
 * @retval #SRE_OK                                 0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_CacheResume
 */
extern UINT32 SRE_CacheSuspend(VOID);

/**
 * @ingroup  sre_cache
 * @brief L2 Cache Resume����
 *
 * @par ����:
 * ����͹���ǰ��L2 Cache Resume������
 *
 * @attention
 * <ul>
 * <li>��Cortex-A9ƽ̨֧�ִ˹��ܣ�����ֻ�е��û�ʹ��L2 Cache����ʱ������Ҫ���ô˽ӿڡ�</li>
 * <li>��Ҫ�ڻ��ѵ͹��ĺ���ô˽ӿڡ�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval #OS_ERRNO_L2_CACHE_NOT_INIT             0x02001114��������L2 Cache��ʼ������ô˽ӿڡ�
 * @retval #OS_ERRNO_L2_CACHE_NOT_SUSPENDED        0x02001117��L2 CacheδSuspend��
 * @retval #SRE_OK                                 0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_CacheSuspend
 */
extern UINT32 SRE_CacheResume(VOID);

/**
 * @ingroup  sre_cache
 * @brief L2 Cache ��ʼ���׶��Ż����Ӻ���ע��
 *
 * @par ����:
 * L2 Cache ��ʼ���׶��Ż����Ӻ���ע�ᡣ
 *
 * @attention
 * <ul>
 * <li>��Cortex-A9ƽ̨֧�ִ˹��ܣ�����ֻ�е��û�ʹ��L2 Cache����ʱ������Ҫ���ô˽ӿڡ�</li>
 * <li>����Ҫ��Cache��ʼ��ǰ���ô˽ӿڡ�</li>
 * <li>ͨ���ýӿ�ע��Ĺ����ڳ�ʼ���׶�L2 Cacheȥʹ��״̬�µ��á�</li>
 * <li>�ù��Ӳ������ظ����߸���ע�ᣬ����ע��ʧ�ܣ�������NULLʱ����ʾȥ�����Ż����Ӻ�����</li>
 * </ul>
 *
 * @param  pfnCacheInitHook   [IN] ����#CACHE_INIT_HOOK��L2 Cache��ʼ���׶��Ż����Ӻ�����
 *
 * @retval #OS_ERRNO_L2_CACHE_HOOK_EXIST           0x02001115��ע�ṳ���Ѿ�����
 * @retval #SRE_OK                                 0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_CacheInit
 */
extern UINT32 SRE_CacheInitHookReg(CACHE_INIT_HOOK pfnCacheInitHook);

/**
 * @ingroup  sre_cache
 * @brief L2 Cache Suspend�׶��Ż����Ӻ���ע��
 *
 * @par ����:
 * L2 Cache Suspend�׶��Ż����Ӻ���ע�ᡣ
 *
 * @attention
 * <ul>
 * <li>��Cortex-A9ƽ̨֧�ִ˹��ܣ�����ֻ�е��û�ʹ��L2 Cache����ʱ������Ҫ���ô˽ӿڡ�</li>
 * <li>����Ҫ��L2 Cache Suspendǰ���ô˽ӿڡ�</li>
 * <li>ͨ���ýӿ�ע��Ĺ�����Suspend�׶�L2 Cacheʹ��״̬�µ��á�</li>
 * <li>�ù��Ӳ������ظ����߸���ע�ᣬ����ע��ʧ�ܣ�������NULLʱ����ʾȥ�����Ż����Ӻ�����</li>
 * </ul>
 *
 * @param  pfnCacheSuspendHook   [IN] ����#CACHE_SUSPEND_HOOK��L2 Cache Suspend�׶��Ż����Ӻ�����
 *
 * @retval #OS_ERRNO_L2_CACHE_HOOK_EXIST           0x02001115��ע�ṳ���Ѿ�����
 * @retval #SRE_OK                                 0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_CacheResumeHookReg
 */
extern UINT32 SRE_CacheSuspendHookReg(CACHE_SUSPEND_HOOK pfnCacheSuspendHook);

/**
 * @ingroup  sre_cache
 * @brief L2 Cache Resume�׶��Ż����Ӻ���ע��
 *
 * @par ����:
 * L2 Cache Resume�׶��Ż����Ӻ���ע�ᡣ
 *
 * @attention
 * <ul>
 * <li>��Cortex-A9ƽ̨֧�ִ˹��ܣ�����ֻ�е��û�ʹ��L2 Cache����ʱ������Ҫ���ô˽ӿڡ�</li>
 * <li>����Ҫ��L2 Cache Resumeǰ���ô˽ӿڡ�</li>
 * <li>ͨ���ýӿ�ע��Ĺ�����Resume�׶�L2 Cacheȥʹ��״̬�µ��á�</li>
 * <li>�ù��Ӳ������ظ����߸���ע�ᣬ����ע��ʧ�ܣ�������NULLʱ����ʾȥ�����Ż����Ӻ�����</li>
 * </ul>
 *
 * @param  pfnCacheResumeHook   [IN] ����#CACHE_RESUME_HOOK��L2 Cache Resume�׶��Ż����Ӻ�����
 *
 * @retval #OS_ERRNO_L2_CACHE_HOOK_EXIST           0x02001115��ע�ṳ���Ѿ�����
 * @retval #SRE_OK                                 0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_CacheSuspendHookReg
 */
extern UINT32 SRE_CacheResumeHookReg(CACHE_RESUME_HOOK pfnCacheResumeHook);

/**
 * @ingroup  sre_cache
 * @brief L2 Cacheͬ��
 *
 * @par ����:
 * L2 Cacheͬ�����ܡ�
 *
 * @attention
 * <ul>
 * <li>��Cortex-A9ƽ̨֧�ִ˹��ܣ�����ֻ�е��û�ʹ��L2 Cache����ʱ������Ҫ���ô˽ӿڡ�</li>
 * </ul>
 *
 * @param  NONE
 *
 * @retval NONE
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_CacheInit
 */
extern VOID SRE_L2CacheWait(VOID);

#endif



/**
 * @ingroup  sre_cache
 * @brief ��Чָ��Cache
 *
 * @par ����:
 * ��ָ����ַ�����ָ��Cache��Ϊ��Ч��
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182,SD6157,SD6181,SD6108,Cortex-AX,SD6183ƽ̨֧����Чָ��ܡ�</li>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>Ϊ��ָ֤��cache�����İ�ȫ�ԣ�Icache���������Եȴ���ʽ������bWait������Ч��</li>
 * <li>����Cortex-A9ƽ̨����L2 Cache���ܴ�ʱ������Ĳ���#bWait����ΪTRUE</li>
 * <li>����Cortex-A9ƽ̨����L2 Cache���ܴ�ʱ���ڹ��ж������½��иò��������ж�ʱ�䳤����Icache��Ч�ڴ��С�����ȡ�</li>
 * <li>����SD6183ƽ̨���û�����������ַ�ռ��Ӧ�������ַ�ռ����������û�з�ת</li>
 * </ul>
 *
 * @param  pAddr   [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize  [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait   [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 *
 * @retval #OS_ERRNO_CACHE_ADDR_LOCKED    0x02001108����SD6182��SD6157ƽ̨��������Ч��ַ�Ƿ��Ѿ�������
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239��SD6183ƽ̨��������ַδӳ�䡣
 * @retval #SRE_OK                        0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv
 */
extern UINT32 SRE_ICacheInv(VOID *pAddr, UINT32 uwSize, BOOL bWait);

/**
 * @ingroup  sre_cache
 * @brief ����ָ�����Cache
 *
 * @par ����:
 * ��ָ����ַ�����д����Ч����Cache��Ȼ������Чָ��cache��
 *
 * @attention
 * <ul>
 * <li>ֻ��SD6182,SD6157,SD6181,SD6108,Cortex-AX,SD6183ƽ̨֧�ָ���ָ�����Cache���ܡ�</li>
 * <li>Cache��������С��λΪCache line����ˣ�������ΧΪָ����ַ�������������Cache line��</li>
 * <li>��DCACHE����£��˽ӿڵ�ͬSRE_ICacheInv��</li>
 * <li>����Cortex-A9ƽ̨����L2 Cache���ܴ�ʱ������Ĳ���#bWait����ΪTRUE</li>
 * <li>����Cortex-A9ƽ̨����L2 Cache���ܴ�ʱ���ڹ��ж������½��иò��������ж�ʱ�䳤����Icache��Ч�ڴ��С�����ȡ�</li>
 * <li>����SD6183ƽ̨���û�����������ַ�ռ��Ӧ�������ַ�ռ����������û�з�ת</li>
 * </ul>
 *
 * @param  pAddr   [IN] ����#VOID *���ڴ�����ʼ��ַ��
 * @param  uwSize  [IN] ����#UINT32���ڴ��Ĵ�С��
 * @param  bWait   [IN] ����#BOOL��TRUEΪ��Cache������ɺ�ŷ��أ�FALSEΪִ�в���ָ����������ء�
 *
 * @retval #OS_ERRNO_CACHE_SIZE_INVALID   0x02001101������cache�����С���Ϸ���
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR      0x02001239��SD6183ƽ̨��������ַδӳ�䡣
 * @retval #SRE_OK                        0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_cache.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DCacheFlushInv | SRE_ICacheInv
 */
extern UINT32 SRE_CacheUpdate(VOID *pAddr, UINT32 uwSize, BOOL bWait);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_CACHE_H */


