/**
* @file sre_mem.h
*
* Copyright(C), 2008-2008, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* �������ڴ�������ܶ���ͷ�ļ��� \n
*/


/** @defgroup SRE_mem �ڴ��������
 *@ingroup SRE_memory
*/

#ifndef _SRE_MEM_H
#define _SRE_MEM_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_mem
 * �ڴ�������������
 */
#define OS_SLICE_MAXTYPE             8

/**
 * @ingroup SRE_mem
 * ϵͳȱʡ���ڴ����������
 */
#define OS_MEM_DEFAULT_PTNUM         2

/**
 * @ingroup SRE_mem
 * ȱʡ˽��FSC�ڴ������
 */
#define OS_MEM_DEFAULT_FSC_PT        0

/**
 * @ingroup SRE_mem
 * OS֧�ֺ˼�ͨ�ŵ�ǰ���£�ȱʡ����̬FSC�ڴ������
 */
#define OS_MEM_DEFAULT_MCSTA_FSC_PT  1

/**
 * @ingroup SRE_mem
 * �����POOL�ڴ��ַ�����׼:16�ֽڶ��롣
 */
#define OS_MEM_ADDR_ALIGN            16

/**
 * @ingroup SRE_mem
 * �����FSC�ڴ��ַ�����׼:4�ֽڶ��롣
 */
#define OS_MEM_FSC_ADDR_ALIGN        4


/**
* @ingroup  SRE_mem
* @brief �ڴ�鱻�ȴ����Ӻ������Ͷ��塣
*
* @par ����:
* �������ڴ�鱻��ʱ��ͨ���ù���֪ͨ�û���
* @attention
* <ul>
* <li>����FSC�㷨�����ڴ��ͷ�ʱ������ڴ�ͷ����̤��⣨�����ظ��ͷŻ򱻲ȣ������û�����Ҫ�ͷŵĵ�ַ��Ϊ���Ӻ���������</li>
* <li>����POOL�㷨�����ڴ��ͷ�ʱ������ڴ�ͷ����̤��⣨�����ڱ��ȣ������û�����Ҫ�ͷŵĵ�ַ��Ϊ���Ӻ���������</li>
* <li>����POOL�㷨�����ڴ�����ʱ������ڴ�ͷ����̤��⣨�����ڱ��ȣ������ڴ����ʼ��ַ��Ϊ���Ӻ���������</li>
* </ul>
* @param  pUserAddr [IN] ����#VOID *���ڴ����ʼ��ַ���û�����Ҫ�ͷŵĵ�ַ��
*
* @retval �ޡ�
* @par ����:
* <ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R002C00
* @see �ޡ�
*/
typedef VOID (* MEM_DAMAGE_HOOK)(VOID * pUserAddr);

/**
 * @ingroup SRE_mem
 * �ڴ��㷨����,Ŀǰ��#MEM_ARITH_MCPOOL֧��Cache�ڴ�ռ䡣
 */
typedef enum
{
    MEM_ARITH_FSC,        /**< ˽��FSC�㷨*/
    MEM_ARITH_POOL,       /**< ˽��POOL��̬�㷨*/
    MEM_ARITH_MCDYNFSC,   /**< ����̬FSC�㷨*/
    MEM_ARITH_MCPOOL,     /**< ����POOL��̬�㷨*/
    MEM_ARITH_MCBLOCK,    /**< ����Block�ڴ��㷨�����㷨�������ֵ���֧��*/
    MEM_ARITH_BUTT        /**< �ڴ��㷨�Ƿ�  */
}OS_MEM_ARITH_E;

/**
 * @ingroup SRE_mem
 * �ڴ���뷽ʽ��
 */
typedef enum
{
    MEM_ADDR_ALIGN_004 = 2  , /**< 4�ֽڶ���*/
    MEM_ADDR_ALIGN_008 = 3  , /**< 8�ֽڶ���*/
    MEM_ADDR_ALIGN_016 = 4  , /**< 16�ֽڶ���*/
    MEM_ADDR_ALIGN_032 = 5  , /**< 32�ֽڶ���*/
    MEM_ADDR_ALIGN_064 = 6  , /**< 64�ֽڶ���*/
    MEM_ADDR_ALIGN_128 = 7  , /**< 128�ֽڶ���*/
    MEM_ADDR_ALIGN_256 = 8  , /**< 256�ֽڶ���*/
    MEM_ADDR_ALIGN_512 = 9  , /**< 512�ֽڶ���*/
    MEM_ADDR_ALIGN_1K  = 10 , /**< 1K�ֽڶ���*/
    MEM_ADDR_ALIGN_2K  = 11 , /**< 2K�ֽڶ���*/
    MEM_ADDR_ALIGN_4K  = 12 , /**< 4K�ֽڶ���*/
    MEM_ADDR_ALIGN_8K  = 13 , /**< 8K�ֽڶ���*/
    MEM_ADDR_ALIGN_16K = 14 , /**< 16K�ֽڶ���*/
    MEM_ADDR_BUTT             /**< �ֽڶ���Ƿ�*/
}OS_MEM_ALIGN_E;

/**
 * @ingroup SRE_mem
 * ��̬���������ӿڲ����ṹ�塣
 */
typedef struct tagCreatePtPara
{
    OS_MEM_ARITH_E  enArith;                           /**< �������㷨����                  */
    VOID           *pPtAddr;                           /**< ������ʼ��ַ                    */
    UINT32          uwPtSize;                          /**< ������С (��λ���ֽڣ�          */
    BOOL            bCachable;                         /**< ָ���ÿ������ڴ��Ƿ�Ϊ��cache   */
    UINT16          ausSliceSize[OS_SLICE_MAXTYPE];    /**< �������ڴ���С(��λ���ֽڣ� */
}MEM_CREATEPT_PARA;

/**
 * @ingroup SRE_mem
 * ��ȡָ�������ڴ���Ϣ�ӿڲ����ṹ�塣
 */
typedef struct tagMemStatInfo
{
    UINT32 uwFreeSize;                              /**< �����ڴ�Ĵ�С����λ���ֽڣ�  */
    UINT32 uwMaxBlockSize;                          /**< �����С����λ���ֽڣ�      */
    UINT32 uwPeakUsed;                              /**< �����ڴ�ʹ�÷�ֵ����λ���ֽڣ�*/
    UINT32 uwPtSize;                                /**< �ڴ�����ܴ�С                */
}OS_MEM_PT_STATE;

/**
 * @ingroup SRE_mem
 * �����ڴ�ʹ�������ѯ�ṹ�塣
 * ���ݲ�ѯ�����ڴ�ʹ�����������Ϣ��
 */
typedef struct tagMemPtUsage
{
    UINT32  uwThreadSize;     /**<����������ж���ͨ��uniMemAlloc MIDΪ0���뵽�ڴ��С�������ڴ�����ͷ�ȡ�  */
    UINT32  uwHwiSize;        /**<����Ӳ�ж��ڱ��ڴ������ռ�õ��ڴ��ܴ�С��                         */
    UINT32  uwSysSize;        /**<����OS������Դ������ջ��Դ������OS�ӿ�������ڴ桢��ʼ���׶ε��á�*/
} OS_MEM_PT_USAGE_S;

/**
 * @ingroup SRE_mem
 * 0�ŷ���������Ϣ�Ľṹ�嶨�塣
 *
 * ����0�ŷ�������������Ϣ��
 */
typedef struct tagPTMemInfo
{
    UINT32 uwStartAddr;                /**< 0�ŷ�����ʼ��ַ    */
    UINT32 uwSize;                     /**< 0�ŷ�����С        */
} OS_MEM_PT0_INFO_S;

/**
 * @ingroup SRE_mem
 * ������������ж��ڴ�ʹ�������ѯ�ṹ�塣
 * ���ݲ�ѯ������������ж��ڴ�ʹ�����������Ϣ��
 */
typedef struct tagMemTask
{
    UINT16 usID;           /**<��������ж�ID                                                           */
    UINT16 usSize;         /**<����������ж���ͨ��SRE_MemAlloc��SRE_MemAllocAlign MIDΪ0���뵽�ڴ��С�������ڴ�����ͷ�� */
} OS_MEM_TASK_S;

/**
 * @ingroup SRE_mem
 * �ڴ�����룺���������ķ�����С̫С��
 *
 * ֵ: 0x02000101
 *
 * ���������������С�Ĵ�
 */
#define OS_ERRNO_MEM_PTCREATE_SIZE_TOOSMALL                 SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x01)

 /**
  * @ingroup SRE_mem
  * ��������룺��ȡ0�ŷ���������Ϣʱ��0�ŷ������õĴ�СС��10K�ֽ�(��ʼ���׶�SRE_Printf�����СΪ4K��Ӳ�жϿ��ƿ��СΪ6K)��
  *
  * ֵ: 0x02000102
  *
  * �������: ����Cortex-AXƽ̨��0�ŷ������ô�С������ڵ���10K�ֽڡ�
  */
#define OS_ERRNO_MEM_PT0_SIZE_TOO_SMALL                     SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x02)

 /**
 * @ingroup SRE_mem
 * �ڴ�����룺�ͷŵĵ�ַΪ�ա�
 *
 * ֵ: 0x02000103
 *
 * ��������������ͷŵ��ڴ���ַ�Ƿ���ȷ��
 */
#define OS_ERRNO_MEM_FREE_ADDR_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x03)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺�ͷ��ڴ����ڵķ�����Ч(����δ����������Ŵ��ڷ�����)��
 *
 * ֵ: 0x02000104
 *
 * �����������������ŵ���Ч�ԡ�
 */
#define OS_ERRNO_MEM_FREE_PTNO_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x04)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺���õ����ɴ����ڴ����������(����ܳ���253)��
 *
 * ֵ: 0x02000105
 *
 * �������: ���������(����ܳ���253)�����
 */
#define OS_ERRNO_MEM_PTNUMBER_OVERMANY                      SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x05)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺�ڴ�����ʱ����Ĵ�С̫��(����Ϊ��ֵ)��
 *
 * ֵ: 0x02000106
 *
 * �������: ���������С�����СҪ������ڴ��С��
 */
#define OS_ERRNO_MEM_ALLOC_SIZETOOLARGE                     SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x06)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺�ڴ����õ��ڴ�����Ͷ���0��
 *
 * ֵ: 0x02000107
 *
 * �������: �����ڴ���������ã�ȷ���ڴ�����Ͳ�ȫΪ0��
 */
#define OS_ERRNO_MEM_ALLSLICE_ZERO                          SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x07)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺�ڴ����õ��ڴ�����Ͳ��ǰ�������˳�����õġ�
 *
 * ֵ: 0x02000108
 *
 * �������: ��ȷ���ڴ�����Ͱ��յ�����˳�����á�
 */
#define OS_ERRNO_MEM_MEMSLICE_NOT_INORDER                   SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x08)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺���������������(������Ӧ����1��С����������������+2��������Ϣ�ṹ��ͷ�����ʼ��ַ��Ϊ�ա�
 * �������㷨��ȷ�ԡ�������С��Ϊ0)��
 *
 * ֵ: 0x02000109
 *
 * �������: �����������Ƿ�Ϸ���
 */
#define OS_ERRNO_MEM_PTCREATE_PARAMETER_INVALID             SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x09)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺�����Ѿ�������
 *
 * ֵ: 0x0200010a
 *
 * �������: ��ȷ������δ������
 */
#define OS_ERRNO_MEM_PT_ALREADY_CREATED                     SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x0a)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺��̬�����ڴ����ʱ���������ص���
 *
 * ֵ: 0x0200010b
 *
 * �������: ��ͬ����֮������ص���
 */
#define OS_ERRNO_MEM_PT_OVERLAP                             SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x0b)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺�ڴ��㷨û�д�����
 *
 * ֵ: 0x0200010c
 *
 * �������: �����Ӧ�����Ƿ�򿪡�
 */
#define OS_ERRNO_MEM_ALGORITHM_UNINSTALLED                  SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x0c)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺��ѯ�ڴ�����Ļ�����Ϣʱ���ڴ����δ���������߷����ŷǷ���
 *
 * ֵ: 0x0200010d
 *
 * �������: �������ŵ���Ч�ԡ�
 */
#define OS_ERRNO_MEM_NO_USE                                 SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x0d)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺���û�ȡ������ʹ������ӿ�ʱ���ýӿڲ������ڿ�ָ�롣
 *
 * ֵ: 0x0200010e
 *
 * �������: ��ȷ���ӿڲ�����Ϊ��ָ�롣
 */
#define OS_ERRNO_MEM_INPUT_INVAILD                          SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x0e)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺FSC�ڴ��㷨��֧�ֿ�Cache�ռ䡣
 *
 * ֵ: 0x0200010f
 *
 * �������: ���ò���Cache�ռ䣬�����POOL�㷨��
 */
#define OS_ERRNO_MEM_PTCREATE_FSC_ARITH_UNCACHABLE          SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x0f)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺�����Ų��Ϸ��������ŷ�Χ[OS_MEM_DEFAULT_PTNUM, OS_MEM_MAX_PT_NUM + OS_MEM_DEFAULT_PTNUM - 1],OS_MEM_MAX_PT_NUM���û����õķ�������OS_MEM_DEFAULT_PTNUMϵͳȱʡ�ķ�������
 *
 * ֵ: 0x02000110
 *
 * ���������������η����š�
 */
#define OS_ERRNO_MEM_PTNO_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x10)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺������ڴ���СΪ0��
 *
 * ֵ: 0x02000111
 *
 * ������������������ڴ��С����Ч�ԡ�
 */
#define OS_ERRNO_MEM_ALLOC_SIZE_ZERO                        SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x11)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺�����ķ���û�д�����
 *
 * ֵ: 0x02000112
 *
 * �������������÷����Ƿ��Ѿ�������
 */
#define OS_ERRNO_MEM_PT_NOT_CREATED                         SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x12)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺���뷽ʽ���Ϸ���
 *
 * ֵ: 0x02000113
 *
 * ���������������ζ��뷽ʽ��
 */
#define OS_ERRNO_MEM_ALLOC_ALIGNPOW_INVALID                 SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x13)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺�����㷨�Ƿ���OS֧�ֵķ����㷨:MEM_ARITH_FSC��MEM_ARITH_POOL��MEM_ARITH_MCDYNFSC��MEM_ARITH_MCPOOL��
 *
 * ֵ: 0x02000114
 *
 * �����������������㷨������
 */
#define OS_ERRNO_MEM_PT_ARITH_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x14)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺��ѯ�ڴ�ʹ�����ʱ���������Ч������ΪNULL��
 *
 * ֵ: 0x02000115
 *
 * �������: ��ѯ�ڴ�ʹ�����ʱ���豣֤�������Ч�����Ϸ���
 */
#define OS_ERRNO_MEMINFO_CHECK_ALL_ADDR_NULL                SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x15)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺��ѯ�����ڴ�ʹ�����ʱ�������������Ч��������һ��ΪNULL��
 *
 * ֵ: 0x02000116
 *
 * �������: ��ѯ�����ڴ�ʹ�����ʱ���豣֤�����������Ч�����Ϸ���
 */
#define OS_ERRNO_MEMINFO_TSK_SINGLE_ADDR_NULL               SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x16)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺��ѯ�ڴ�ʹ�����ʱ������Ĳ�ѯ�����������0��
 *
 * ֵ: 0x02000117
 *
 * �������: ��ʹ���ڴ�ʹ�������ѯ����ʱ���豣֤����Ĳ�ѯ���������������Χ�ڡ�
 */
#define OS_ERRNO_MEMINFO_CHECK_TASKNUM_INVALID              SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x17)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺�̼߳��ڴ�ʹ�ò�ѯ���ܲ�֧�֡�
 *
 * ֵ: 0x02000118
 *
 * �������:��STM32F407оƬ֧�ָù��ܣ�����ƽ̨ʹ�ñ��˴����롣
 */
#define OS_ERRNO_MEM_NOT_SUPPORT                            SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x18)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺�����㷨��֧�֡�
 *
 * ֵ: 0x02000119
 *
 * �������:�ù���ֻ֧��˽��FSC�㷨��
 */
#define OS_ERRNO_MEM_PT_ARITH_NOT_SUPPORT                   SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x19)

/**
 * @ingroup SRE_mem
 * OSȱʡ˽��FSC�ڴ�����룺��˽��FSC�����������ڴ�ʱ���Ҳ��������ڴ棬����ʧ�ܡ�
 *
 * ֵ: 0x02000210
 *
 * �������: ����˽��FSC�ڴ������С��
 */
#define OS_ERRNO_FSCMEM_ALLOC_NO_MEMORY                     SRE_ERRNO_OS_ERROR(OS_MID_FSCMEM, 0x10)

/**
 * @ingroup SRE_mem
 * ��̬�ڴ�����룺��̬�ڴ��ͷ�ʱҪ�ͷŵ��ڴ���ͷ���ƻ��������ͷš�
 *
 * ֵ: 0x0200011a
 *
 * �������: ��֤���ڴ�д����ʱ����Ҫ����дԽ�硣
 *
 */
#define OS_ERRNO_MEM_FREE_SH_DAMAGED                        SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x1a)

/**
 * @ingroup SRE_mem
 * ��̬�ڴ�����룺��̬(POOL)�ڴ�����ʱ������ڴ�鱻�ƻ���
 *
 * ֵ: 0x02000512
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_MEM_DYNALLOC_SH_DAMAGED                    SRE_ERRNO_OS_ERROR(OS_MID_POOLMEM, 0x12)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺˽��POOL�ڴ��ͷ�ʱ�ڴ���Ѿ����ͷ�(�����ڴ�û�б������)��
 *
 * ֵ: 0x02000514
 *
 * �������: ����ͷŵ��ڴ��Ƿ������룬�����Ƿ��Ѿ����ͷš�
 */
#define OS_ERRNO_MEM_FREE_POOL_MEM_ALREADY_FREE             SRE_ERRNO_OS_ERROR(OS_MID_POOLMEM, 0x14)

/**
 * @ingroup SRE_mem
 * ��̬�ڴ�����룺��̬POOL�ڴ�����ʱ�ڴ�ռ䲻����
 *
 * ֵ: 0x02000515
 *
 * �������: ���������С�����СҪ������ڴ��С��
 */
#define OS_ERRNO_MEM_DYN_ALLOC_MEM_SHORTAGE                 SRE_ERRNO_OS_ERROR(OS_MID_POOLMEM, 0x15)

/**
 * @ingroup SRE_mem
 * ��̬�ڴ�����룺�ڴ��㷨���ͷǷ���OS��֧�ָ��ڴ��㷨��
 *
 * ֵ: 0x0200011b
 *
 * �������: �鿴������㷨�Ƿ���ȷ��
 */
#define OS_ERRNO_MEM_ARITH_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x1b)

/**
 * @ingroup SRE_mem
 * �����ڴ�����룺����̬POOL�ڴ�����ʱ�ڴ�ռ䲻����
 *
 * ֵ: 0x02000417
 *
 * �������: ���������С�����СҪ������ڴ��С��
 */
#define OS_ERRNO_MEM_SHARE_ALLOC_MEM_SHORTAGE               SRE_ERRNO_OS_ERROR(OS_MID_MCPOOLMEM, 0x17)

/**
 * @ingroup SRE_mem
 * �����ڴ�����룺����̬POOL�ڴ�����ʱ������ڴ�鱻�ƻ���
 *
 * ֵ: 0x02000418
 *
 * �������: ��֤��ַ���ڴ��ַ����֤�û�д��������Խ�硣
 */
#define OS_ERRNO_MEM_SHAREALLOC_SH_DAMAGED                  SRE_ERRNO_OS_ERROR(OS_MID_MCPOOLMEM, 0x18)

/**
 * @ingroup SRE_mem
 * �����ڴ�����룺����̬POOL�ڴ��ͷ�ʱ�ڴ���Ѿ����ͷ�(�����ڴ�û�б������)��
 *
 * ֵ: 0x02000419
 *
 * �������: ��֤�ͷŵ��ڴ�����Ѿ�������ġ�
 */
#define OS_ERRNO_MEM_FREE_SHARE_MEM_ALREADY_FREE            SRE_ERRNO_OS_ERROR(OS_MID_MCPOOLMEM, 0x19)

/**
 * @ingroup SRE_mem
 *
 * �ڴ�����룺��ͬ�˴�����ͬ��ŵĹ������ʱ��������ͬ��
 *
 * ֵ: 0x0200011c
 *
 * �������: �������ţ������㷨��������ʼ��ַ��������С�����������ͼ���С��һ���ԡ�
 */
#define OS_ERRNO_MEM_SHARE_PARA_INCONSISTENT                SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x1c)

/**
 * @ingroup SRE_mem
 * �����ڴ�����룺����̬FSC�ڴ�����ĳߴ���ͬBLOCK��������ڴ�ߴ粻ƥ�䡣
 *
 * ֵ: 0x02000e1c
 *
 * �������: ��ȷ������ĳߴ���ͬBLOCK��������ڴ�ߴ�ƥ�䡣
 */
#define OS_ERRNO_MEM_MCSTA_FSCMEM_UNMATCHED                 SRE_ERRNO_OS_ERROR(OS_MID_STAFSCMEM, 0x1c)

/**
 * @ingroup SRE_mem
 * �����ڴ�����룺�ӹ���̬FSC�����������ڴ�ʱ���Ҳ��������ڴ棬����ʧ�ܡ�
 *
 * ֵ: 0x02000e1d
 *
 * �������: ������̬FSC�ڴ������С��
 */
#define OS_ERRNO_MCSTA_FSCMEM_ALLOC_NO_MEMORY               SRE_ERRNO_OS_ERROR(OS_MID_STAFSCMEM, 0x1d)

/**
 * @ingroup SRE_mem
 * �����ڴ�����룺����̬FSC���ڴ治���ͷš�
 *
 * ֵ: 0x02000e1e
 *
 * �������: ����̬FSC�㷨��֧���ڴ��ͷŲ����������Ƿ��ͷ��˴�����ڴ�顣
 */
#define OS_ERRNO_MCSTA_FSCMEM_FREE_ISFORBIDEN               SRE_ERRNO_OS_ERROR(OS_MID_STAFSCMEM, 0x1e)

/**
 * @ingroup SRE_mem
 * �����ڴ�����룺��ͬimage�ж���OSȱʡʹ�õ�1�ŷ������ò�һ�¡�
 *
 * ֵ: 0x02000e20
 *
 * �������: ��ȷ������image�ж���OSȱʡʹ�õ�1�ŷ������õ���ʼ��ַһ�¡�������Сһ�¡�
 */
#define OS_ERRNO_MCSTA_FSCMEM_PT_PARA_INCONSISTENT          SRE_ERRNO_OS_ERROR(OS_MID_STAFSCMEM, 0x20)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺���ýӿ�#SRE_MemFree/#SRE_MemCacheFree�ͷŲ���cache�ڴ棬����ýӿ�#SRE_MemUncacheFree�ͷſ�cache�ڴ档
 *
 * ֵ: 0x02000121
 *
 * �������: ����ýӿ�#SRE_MemFree/#SRE_MemCacheFree�ͷſ�cache�ڴ棬����ýӿ�#SRE_MemUncacheFree�ͷŲ���cache�ڴ档
 */
#define OS_ERRNO_MEM_ATTR_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x21)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺���ýӿ�#SRE_MemUncacheFree�ͷŷ�OS_MEM_DEFAULT_FSC_PT�����е��ڴ档
 *
 * ֵ: 0x02000122
 *
 * �������: ����ýӿ�#SRE_MemFree/#SRE_MemCacheFree�ͷ��ڴ档
 */
#define OS_ERRNO_MEM_FREE_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x22)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺mmuģ��û�г�ʼ����
 *
 * ֵ: 0x02000123
 *
 * �������: ����mmuģ����������Ƿ���ȷ��
 */
#define OS_ERRNO_MEM_MMU_NOT_INIT                           SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x23)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺����ɾ��ϵͳȱʡ���ڴ������
 *
 * ֵ: 0x02000124
 *
 * �������: ����������Ƿ�Ϊϵͳȱʡ�ķ�����
 */
#define OS_ERRNO_MEM_DELETE_DEFAULT_PT                      SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x24)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺����ɾ�������ڴ��㷨������
 *
 * ֵ: 0x02000125
 *
 * �������: ��ȷ����ɾ���ķ���Ϊ˽���ڴ��㷨������
 */
#define OS_ERRNO_MEM_DELETE_SHARE_PT                        SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x25)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺������ʼ��ַ̫��
 *
 * ֵ: 0x02000126
 *
 * �������: ���С������ʼ��ַ��
 */
#define OS_ERRNO_MEM_PTCREATE_ADDR_TOOLARGE                 SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x26)

/**
 * @ingroup SRE_mem
 * �ڴ�����룺��֧�ִ��������㷨�ڴ������
 *
 * ֵ: 0x02000127
 *
 * �������: ����˽���ڴ��㷨����������
 */
#define OS_ERRNO_MEM_PTCREATE_ARITH_NONSUPPORT              SRE_ERRNO_OS_ERROR(OS_MID_MEM, 0x27)

/**
 *@ingroup SRE_mem
 *@brief ��RTOSck�Ѵ�����ָ�����������ڴ档
 *
 *@par ����:
 *<li>�ڷ�����ΪucPtNo�ķ����У������СΪuwSize���ڴ档</li>
 *@attention
 *<ul>
 *<li>�����ڴ�ʱ�ķ����ţ�����ʵ�ʴ����ķ�������ʹ�á�</li>
 *<li>���ú�����ע���жϷ��صĵ�ַ�Ƿ�Ϊ���Ա���������ʿ�ָ�롣</li>
 *<li>����FSC�ڴ��㷨�����뵽���ڴ��׵�ַ�ǰ�4�ֽڶ���ģ�����POOL�ڴ��㷨�����뵽���ڴ��׵�ַ�ǰ�16�ֽڶ���ġ�</li>
 *<li>����ڴ�����ʧ�ܣ�����ֵΪNULL��������ʧ�ܵ�ԭ�򽫼�¼�ڴ�����ռ��С�</li>
 *</ul>
 *
 *@param uwMid        [IN] ����#UINT32�������ģ��š�
 *@param ucPtNo       [IN] ����#UINT8�� �����ţ���Χ[0,#OS_MEM_MAX_PT_NUM+2)��
 *@param uwSize       [IN] ����#UINT32������Ĵ�С��
 *
 *@retval #NULL  0������ʧ�ܡ�
 *@retval #!NULL �ڴ��׵�ֵַ��
 *@par ����:
 *<ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R001C00
 *@see SRE_MemFree
 */
extern VOID * SRE_MemAlloc(UINT32 uwMid, UINT8 ucPtNo, UINT32 uwSize);

/**
 *@ingroup SRE_mem
 *@brief ��RTOSck�Ѵ�����ָ����������ָ����С��ָ�����뷽ʽ���ڴ�顣
 *
 *@par ����:
 *<ul>
 *<li>�ڷ�����ΪucPtNo�ķ����У������СΪuwSize���ڴ棬���뷽ʽΪenAlignPow��</li>
 *</ul>
 *@attention
 *<ul>
 *<li>�����ڴ����ʱ�ķ����ţ�����ʵ�ʴ����ķ�������ʹ�á�</li>
 *<li>���ú�����ע���жϷ��صĵ�ַ�Ƿ�Ϊ���Ա���������ʿ�ָ�롣</li>
 *<li>enAlignPow�Ƕ��뷽ʽ������POOL�㷨�����ֻ֧��16�ֽڶ��뷽ʽ��</li>
 *<li>����ڴ�����ʧ�ܣ�����ֵΪNULL��������ʧ�ܵ�ԭ�򽫼�¼�ڴ�����ռ��С�</li>
 *</ul>
 *
 *@param uwMid        [IN] ����#UINT32�������ģ��š�
 *@param ucPtNo       [IN] ����#UINT8�� �����ţ���Χ[0,#OS_MEM_MAX_PT_NUM+2)��
 *@param uwSize       [IN] ����#UINT32������Ĵ�С��
 *@param enAlignPow   [IN] ����#OS_MEM_ALIGN_E����̬���롣
 *
 *@retval NULL  0������ʧ�ܡ�
 *@retval !NULL���ڴ��׵�ֵַ��
 *@par ����:
 *<ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R001C00
 *@see SRE_MemFree
 */
extern VOID * SRE_MemAllocAlign(UINT32 uwMid, UINT8 ucPtNo, UINT32 uwSize, OS_MEM_ALIGN_E enAlignPow);

/**
 *@ingroup SRE_mem
 *@brief �ͷ�������ڴ档
 *
 *@par ����:
 *�ýӿڸ����ڴ��ĵ�ַpAddr���ҵ����ڴ���������ڴ�������ٸ��ݷ����ź��û�ʹ�õĵ�ַpAddr�ͷŸ��ڴ档
 *@attention
 *<ul>
 *<li>�������ֵ����#SRE_OK�����ڴ治�ᱻ�ͷš�</li>
 *<li>���ƻ����ڴ治�ܱ��ͷš�</li>
 *</ul>
 *
 *@param uwMid       [IN] ����#UINT32��Ҫ�ͷŵ�ģ��š�
 *@param pAddr       [IN] ����#VOID *���ͷŵĵ�ַ��
 *
 *@retval #OS_ERRNO_MEM_FREE_PTNO_INVALID           0x02000104���ͷ��ڴ����ڵķ�����Ч(����δ����������Ŵ��ڷ�����)��
 *@retval #OS_ERRNO_MEM_FREE_SH_DAMAGED             0x0200011a���ڴ��ͷ�ʱҪ�ͷŵ��ڴ���ͷ���ƻ��������ͷš�
 *@retval #OS_ERRNO_MEM_FREE_POOL_MEM_ALREADY_FREE  0x02000514��˽��POOL�ڴ��ͷ�ʱ�ڴ���Ѿ����ͷ�(�����ڴ�û�б������)��
 *@retval #OS_ERRNO_MEM_FREE_SHARE_MEM_ALREADY_FREE 0x02000419������̬POOL�ڴ��ͷ�ʱ�ڴ���Ѿ����ͷ�(�����ڴ�û�б������)��
 *@retval #OS_ERRNO_MCSTA_FSCMEM_FREE_ISFORBIDEN    0x02000e1e������̬FSC���ڴ治���ͷš�
 *@retval #OS_ERRNO_MEM_ATTR_INVALID                0x02000121�����ýӿ�#SRE_MemFree/#SRE_MemCacheFree�ͷŲ���cache�ڴ棬���ýӿ�#SRE_MemUncacheFree�ͷſ�cache�ڴ档
 *@retval #OS_ERRNO_MEM_FREE_ADDR_INVALID           0x02000103���ͷŵ�ַΪ�ա�
 *@retval #SRE_OK                                   0x00000000���ڴ��ͷųɹ���
 *@par ����:
 *<ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R001C00
 *@see SRE_MemAlloc | SRE_MemAllocAlign
 */
extern UINT32 SRE_MemFree(UINT32 uwMid, VOID * pAddr);

/**
 *@ingroup SRE_mem
 *@brief ��̬����������
 *
 *@par ����:
 *����һ����������ΪpstPara��������ΪucPtNo���ڴ������
 *@attention
 *<ul>
 *<li>�����ڴ����ʱ�ķ����ţ�ȡֵ��Χ��[2,#OS_MEM_MAX_PT_NUM+2)��</li>
 *<li>�û������������ļ�(sre_config.h)������ϵͳ֧�ֵ���������#OS_MEM_MAX_PT_NUM������Ϊ253��</li>
 *<li>����˽��FSC�㷨�������㷨������ͨ���ڴ�ü����ؾ����Ƿ񴴽��� </li>
 *<li>os��֧�ֺ˼�ͨ�ŵ�ǰ���£���ռ��2������(������ϵͳ֧�ֵ�����������)�������Ŵ�0��1��0��Ϊϵͳʹ�õ�˽��FSC������
      1��Ϊϵͳʹ�õĹ���̬FSC����������osռ��һ��������Ϊ0��˽��FSC������</li>
 *<li>���ű�ģ��򿪵�����£�SD6108/81/82��Cortex-MXƽ̨��ռ��һ���ڴ������</li>
 *<li>�����ڴ�ʱ���û����õ��ڴ��ַ�������ڴ��Ƿ��cache��</li>
 *<li>����Block�ڴ��㷨��֧�֡�</li>
 *</ul>
 *
 *@param pstPara  [IN] ����#MEM_CREATEPT_PARA *����������������Ϣ��
 *@param ucPtNo   [IN] ����#UINT8�� �����š�
 *
 *@retval #OS_ERRNO_MEM_PTCREATE_PARAMETER_INVALID   0x02000109�����������������
 *@retval #OS_ERRNO_MEM_PT_ALREADY_CREATED           0x0200010a�������Ѿ�������
 *@retval #OS_ERRNO_MEM_PT_OVERLAP                   0x0200010b����̬�����ڴ����ʱ���������ص���
 *@retval #OS_ERRNO_MEM_SHARE_PARA_INCONSISTENT      0x0200011c����������������ò�ͳһ����ͬ�˴�����ͬ��ŵĹ������ʱ����Ӧ��ͬ��
 *@retval #OS_ERRNO_MEM_ALGORITHM_UNINSTALLED        0x0200010c���ڴ��㷨û�д�����
 *@retval #OS_ERRNO_MEM_PTCREATE_SIZE_TOOSMALL       0x02000101�����������ķ�����С̫С��
 *@retval #OS_ERRNO_FSCMEM_ALLOC_NO_MEMORY           0x02000210����������ʱ����ȱʡ˽��FSC�ڴ����������������ƿ�ʧ�ܡ�
 *@retval #OS_ERRNO_MCSTA_FSCMEM_ALLOC_NO_MEMORY     0x02000e1d����������ʱ����ȱʡ����̬FSC�ڴ����������������ƿ�ʧ�ܡ�
 *@retval #OS_ERRNO_MEM_PTCREATE_ADDR_TOOLARGE       0x02000126��������ʼ��ַ̫��
 *@retval #OS_ERRNO_MEM_PTCREATE_ARITH_NONSUPPORT    0x02000127����˺�OS_MULTI_COREδ�򿪣���֧�ִ��������㷨�ڴ������
 *@retval #SRE_OK                                    0x00000000�����������ɹ���
 *@par ����:
 *<ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R001C01
 *@see SRE_MemFree | SRE_MemAlloc
 */
extern  UINT32 SRE_MemPtCreate(MEM_CREATEPT_PARA * pstPara, UINT8 ucPtNo);

/**
 *@ingroup SRE_mem
 *@brief ��̬ɾ��������
 *
 *@par ����:
 *ɾ��������ΪucPtNo���ڴ������
 *@attention
 *<ul>
 *<li>��֧��ɾ��˽���ڴ��㷨(����˽��FSC�㷨��˽��POOL�㷨)��������֧��ɾ�������ڴ��㷨������ </li>
 *<li>����ɾ��ϵͳȱʡ�ķ�����</li>
 *<li>����ɾ��δ�����ķ�����</li>
 *<li>���ýӿڻ�ǿ��ɾ��������������Ӧ���ڴ�ȫ�����㡣</li>
 *</ul>
 *
 *@param ucPtNo   [IN] ����#UINT8�� ��ɾ�������ķ����ţ�ȡֵ��Χ��[2,#OS_MEM_MAX_PT_NUM + 2)��
 *
 *@retval #OS_ERRNO_MEM_PTNO_INVALID                0x02000110�������ŷǷ���
 *@retval #OS_ERRNO_MEM_DELETE_DEFAULT_PT           0x02000124��ɾ��ϵͳȱʡ�ķ�����
 *@retval #OS_ERRNO_MEM_PT_NOT_CREATED              0x02000112������δ������
 *@retval #OS_ERRNO_MEM_DELETE_SHARE_PT             0x02000125��ɾ�������ڴ��㷨������
 *@retval #OS_ERRNO_MEM_FREE_PTNO_INVALID           0x02000104���ͷ��ڴ����ڵķ�����Ч(����δ����������Ŵ��ڷ�����)��
 *@retval #OS_ERRNO_MEM_FREE_SH_DAMAGED             0x0200011a���ڴ��ͷ�ʱҪ�ͷŵ��ڴ���ͷ���ƻ��������ͷš�
 *@retval #OS_ERRNO_MEM_FREE_ADDR_INVALID           0x02000103���ͷŵ�ַΪ�ա�
 *@retval #SRE_OK                                   0x00000000������ɾ���ɹ���
 *@par ����:
 *<ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_MemPtCreate
 */
extern  UINT32 SRE_MemPtDelete(UINT8 ucPtNo);

/**
 *@ingroup SRE_mem
 *@brief ��ȡָ���ڴ�������ڴ�ռ���ʡ�
 *
 *@par ����:
 *��ȡ������ΪucPtNo���ڴ������ռ���ʡ�
 *@attention
 *<ul>
 *<li>����POOL�㷨����ʹ�õ��ڴ�ռ��������֮���ͷŵ��ڴ�ռ䣬�����ڴ�����֮�󣬼�ʹ�ͷţ����ڴ�������Ѿ���ָ�������������ɷ��䡣</li>
 *<li>����FSC�㷨����ʹ�õ��ڴ�ռ䲻��������֮���ͷŵ��ڴ�ռ䣬�ͷŵĿռ�������±����䡣</li>
 *<li>�����Ų�����ʱ�÷������ڴ�ռ����Ϊ0��</li>
 *</ul>
 *
 *@param ucPtNo            [IN] ����#UINT8�� �����ţ���Χ[0,#OS_MEM_MAX_PT_NUM+2)��
 *
 *@retval �ڴ����ռ����   �����ɹ����������ڴ�ռ����ȡֵ��ΧΪ[0,10000]��
 *@retval 0                �÷������ڴ�ռ����Ϊ0���߸÷��������ڡ�
 *@par ����:
 *<ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R001C01
 *@see SRE_MemPtCreate
 */
extern UINT32 SRE_MemUsageGet(UINT8 ucPtNo);

/**
 *@ingroup SRE_mem
 *@brief ��ѯ�ڴ��ΪucPtNo���ڴ�����Ļ�����Ϣ������Ϣ���ظ�pstMemPtState��ָ��Ľṹ�塣
 *
 *@par ����:
 *��������ţ���ѯ�÷������ܴ�С����ʷʹ�÷�ֵ��ʣ���ڴ�Ĵ�С��
 *@attention
 *<ul>
 *<li>֧��POOL�㷨��FSC�㷨��</li>
 *<li>�ڴ�����ܴ�С��ָ�û�����ķ�����С��÷������ƿ�Ĵ�С���ܺ͡�</li>
 *<li>��ʷʹ�÷�ֵ��ָ������ʷʹ�������ڴ�ռ�Ĵ�С��
 ����POOL�㷨��˵�������ڴ�����֮�󣬼�ʹ�ͷţ����ڴ�������Ѿ���ָ�������������ɷ��䡣���Զ���POOL�㷨����ʹ�ڴ�����֮���ͷţ����ռ�Ҳ������ʹ�õģ�
 ����FSC�㷨���������ֱ��ͷŵ��ڴ�������·��䣬����δ��ʹ�á�</li>
 *</ul>
 *
 *@param ucPtNo         [IN] ����#UINT8�� �����ţ���Χ[0,#OS_MEM_MAX_PT_NUM+2)��
 *@param pstMemPtState  [OUT]����#OS_MEM_PT_STATE *�������ڴ������ʹ��״̬��Ϣ��
 *
 *@retval #OS_ERRNO_MEM_INPUT_INVAILD   0x0200010e���ṹ��Ϊ�ա�
 *@retval #OS_ERRNO_MEM_NO_USE          0x0200010d������δ����������ŷǷ���
 *@retval #OS_ERRNO_MEM_ARITH_INVALID   0x0200011b���ڴ��㷨���ͷǷ���OS��֧�ָ��ڴ��㷨��
 *@retval #SRE_OK                       0x00000000�������ɹ���
 *@par ����:
 *<ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R001C01
 *@see SRE_MemPtCreate
 */
extern UINT32 SRE_MemPtStateGet(UINT8 ucPtNo, OS_MEM_PT_STATE *pstMemPtState);

#if (OS_OPTION_MEM_UNCACHE_ALLOC == YES)
/**
 *@ingroup SRE_mem
 *@brief ��RTOSck�Ѵ����ķ���OS_MEM_DEFAULT_FSC_PT����ָ����С��Ĭ�Ͽ�cache�ڴ�顣
 *
 *@par ����:
 *<ul>
 *<li>�ڷ�����ΪOS_MEM_DEFAULT_FSC_PT�ķ����У������СΪuwSize���ڴ棬���뷽ʽΪenAlignPow��</li>
 *</ul>
 *@attention
 *<ul>
 *<li>�˽ӿ�ֻ������Cortex_AXƽ̨Balong��Ʒ��</li>
 *<li>����ڴ�����ʧ�ܣ�����ֵΪNULL��������ʧ�ܵ�ԭ�򽫼�¼�ڴ�����ռ��С�</li>
 *</ul>
 *
 *@param uwSize       [IN] ����#UINT32������Ĵ�С��
 *@param enAlignPow   [IN] ����#OS_MEM_ALIGN_E����̬���룬��Чȡֵ��ΧΪ#OS_MEM_ALIGN_E��
 *
 *@retval #NULL  0������ʧ�ܡ�
 *@retval #!NULL �ڴ��׵�ֵַ��
 *@par ����:
 *<ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_MemCacheFree
 */
#define SRE_MemCacheAlloc(uwSize, enAlignPow)  SRE_MemAllocAlign(0, OS_MEM_DEFAULT_FSC_PT, uwSize, enAlignPow)

/**
 *@ingroup SRE_mem
 *@brief �ͷ�������ڴ档
 *
 *@par ����:
 *�ýӿڸ����ڴ��ĵ�ַpAddr���ҵ����ڴ���������ڴ�������ٸ��ݷ����ź��û�ʹ�õĵ�ַpAddr�ͷŸ��ڴ档
 *@attention
 *<ul>
 *<li>�������ֵ����#SRE_OK�����ڴ治�ᱻ�ͷš�</li>
 *<li>���ƻ����ڴ治�ܱ��ͷš�</li>
 *<li>�˽ӿ�ֻ������Cortex_AXƽ̨Balong��Ʒ��</li>
 *</ul>
 *
 *@param pAddr       [IN] ����#VOID *���ͷŵĵ�ַ��
 *
 *@retval #OS_ERRNO_MEM_FREE_PTNO_INVALID           0x02000104���ͷ��ڴ����ڵķ�����Ч(����δ����������Ŵ��ڷ�����)��
 *@retval #OS_ERRNO_MEM_FREE_SH_DAMAGED             0x0200011a���ڴ��ͷ�ʱҪ�ͷŵ��ڴ���ͷ���ƻ��������ͷš�
 *@retval #OS_ERRNO_MEM_FREE_POOL_MEM_ALREADY_FREE  0x02000514��˽��POOL�ڴ��ͷ�ʱ�ڴ���Ѿ����ͷ�(�����ڴ�û�б������)��
 *@retval #OS_ERRNO_MEM_FREE_SHARE_MEM_ALREADY_FREE 0x02000419������̬POOL�ڴ��ͷ�ʱ�ڴ���Ѿ����ͷ�(�����ڴ�û�б������)��
 *@retval #OS_ERRNO_MCSTA_FSCMEM_FREE_ISFORBIDEN    0x02000e1e������̬FSC���ڴ治���ͷš�
 *@retval #OS_ERRNO_MEM_ATTR_INVALID                0x02000121�����ýӿ�#SRE_MemFree/#SRE_MemCacheFree�ͷŲ���cache�ڴ棬���ýӿ�#SRE_MemUncacheFree�ͷſ�cache�ڴ档
 *@retval #OS_ERRNO_MEM_FREE_ADDR_INVALID           0x02000103���ͷŵ�ַΪ�ա�
 *@retval #SRE_OK                                   0x00000000���ڴ��ͷųɹ���
 *@par ����:
 *<ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_MemCacheAlloc
 */
#define SRE_MemCacheFree(pAddr)                SRE_MemFree(0, (VOID *)pAddr)

/**
 *@ingroup SRE_mem
 *@brief ��RTOSck�Ѵ����ķ���OS_MEM_DEFAULT_FSC_PT����ָ����С��Ĭ�ϲ���cache�ڴ�顣
 *
 *@par ����:
 *<ul>
 *<li>�ڷ�����ΪOS_MEM_DEFAULT_FSC_PT�ķ����У������СΪuwSize���ڴ棬���뷽ʽΪenAlignPow��</li>
 *</ul>
 *@attention
 *<ul>
 *<li>�˽ӿ�ֻ������Cortex_AXƽ̨Balong��Ʒ��</li>
 *<li>�ڴ���뷽ʽ����������4k�ֽڶ��롣</li>
 *<li>����ڴ�����ʧ�ܣ�����ֵΪNULL��������ʧ�ܵ�ԭ�򽫼�¼�ڴ�����ռ��С�</li>
 *</ul>
 *
 *@param uwSize       [IN] ����#UINT32������Ĵ�С��
 *@param enAlignPow   [IN] ����#OS_MEM_ALIGN_E����̬���룬��Чȡֵ��ΧΪ#OS_MEM_ALIGN_E��
 *
 *@retval #NULL  0������ʧ�ܡ�
 *@retval #!NULL �ڴ��׵�ֵַ��
 *@par ����:
 *<ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_MemUncacheFree
 */
extern VOID *SRE_MemUncacheAlloc(UINT32 uwSize, OS_MEM_ALIGN_E enAlignPow);

/**
 *@ingroup SRE_mem
 *@brief �ͷ�������ڴ档
 *
 *@par ����:
 *�ýӿڸ����ڴ��ĵ�ַpAddr���ҵ����ڴ���������ڴ�������ٸ��ݷ����ź��û�ʹ�õĵ�ַpAddr�ͷŸ��ڴ档
 *@attention
 *<ul>
 *<li>�������ֵ����#SRE_OK�����ڴ治�ᱻ�ͷš�</li>
 *<li>���ƻ����ڴ治�ܱ��ͷš�</li>
 *<li>�˽ӿ�ֻ������Cortex_AXƽ̨Balong��Ʒ��</li>
 *</ul>
 *
 *@param pAddr       [IN] ����#VOID *���ͷŵĵ�ַ��
 *
 *@retval #OS_ERRNO_MEM_FREE_PTNO_INVALID            0x02000104���ͷ��ڴ����ڵķ�����Ч(����δ����������Ŵ��ڷ�����)��
 *@retval #OS_ERRNO_MEM_FREE_INVALID                 0x02000122�����ýӿ�#SRE_MemUncacheFree�ͷŷ�OS_MEM_DEFAULT_FSC_PT�����е��ڴ档
 *@retval #OS_ERRNO_MEM_FREE_SH_DAMAGED              0x0200011a���ڴ��ͷ�ʱҪ�ͷŵ��ڴ���ͷ���ƻ��������ͷš�
 *@retval #OS_ERRNO_MEM_FREE_POOL_MEM_ALREADY_FREE   0x02000514��˽��POOL�ڴ��ͷ�ʱ�ڴ���Ѿ����ͷ�(�����ڴ�û�б������)��
 *@retval #OS_ERRNO_MEM_FREE_SHARE_MEM_ALREADY_FREE  0x02000419������̬POOL�ڴ��ͷ�ʱ�ڴ���Ѿ����ͷ�(�����ڴ�û�б������)��
 *@retval #OS_ERRNO_MCSTA_FSCMEM_FREE_ISFORBIDEN     0x02000e1e������̬FSC���ڴ治���ͷš�
 *@retval #OS_ERRNO_MEM_ATTR_INVALID                 0x02000121�����ýӿ�#SRE_MemFree/#SRE_MemCacheFree�ͷŲ���cache�ڴ棬���ýӿ�#SRE_MemUncacheFree�ͷſ�cache�ڴ档
 *@retval #OS_ERRNO_MEM_FREE_ADDR_INVALID            0x02000103���ͷŵ�ַΪ�ա�
 *@retval #OS_ERRNO_MEM_MMU_NOT_INIT                 0x02000123��mmuģ��û�г�ʼ����
 *@retval #OS_ERRNO_MMU_DEOPTIMIZE_FAIL              0x02001211��ҳ����ʱ�ڴ治�㡣
 *@retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED              0x02001210�����������ַδӳ�����
 *@retval #SRE_OK                                    0x00000000���ڴ��ͷųɹ���
 *@par ����:
 *<ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R002C00
 *@see SRE_MemUncacheAlloc
 */
extern UINT32 SRE_MemUncacheFree(VOID *pAddr);
#endif

/**
 *@ingroup SRE_mem
 *@brief ע����ڴ洦���Ӻ�����
 *
 *@par ����:
 *�����û����õĻص�����pfnHook��ע����ڴ洦���Ӻ�����
 *@attention
 *<ul>
 *<li>�������ظ��򸲸�ע�ṳ�ӡ�pfnHookΪNULLʱ����ʾɾ���ù��ӡ�</li>
 *<li>֧�����ڴ�����롢�ͷŹ��̶��ڴ��ͷ����̤���м�⡣����fsc�㷨���������ڴ���ظ��ͷź��ڴ��ͷ����̤�����ֳ�������ִ�лص�����������pool�㷨�������ڴ���ظ��ͷź��ڴ��ͷ����̤���ֳ������ڴ��ͷ����̤��ִ�лص����������ڴ���ظ��ͷŽ����ش����롣</li>
 *</ul>
 *
 *@param pfnHook       [IN] ����#MEM_DAMAGE_HOOK���ڴ��̤�ص�������
 *
 *@retval #OS_ERRNO_HOOK_TYPE_INVALID              0x02001600��HOOK���ʹ���
 *@retval #OS_ERRNO_HOOK_FULL                      0x02001604��HOOK���������ø���Ϊ0��
 *@retval #SRE_OK                                  0x00000000������ע��ɹ���
 *@par ����:
 *<ul><li>sre_mem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 *@since RTOSck V100R002C00
 *@see �ޡ�
 */
extern UINT32 SRE_MemDamageHookReg(MEM_DAMAGE_HOOK pfnHook);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_MEM_H */

