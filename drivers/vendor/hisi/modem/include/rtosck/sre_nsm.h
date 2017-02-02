/**
* @file SRE_nsm.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* �����������ռ�ģ�����ͷ�ļ��� \n
*/

/**
 * @defgroup SRE_nsm  �����ռ�
 * @ingroup SRE_kernel
 */

#ifndef _SRE_NSM_H
#define _SRE_NSM_H

#include "sre_base.h"
#include "sre_mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//֧�ֹ��ܺ�ü�,sre_buildef.h�ļ���֧�ֵĹ��ܺ�
#if (OS_OPTION_NSM == YES)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺��ηǷ�������ָ��ΪNULL��
 *
 * ֵ: 0x02001b01
 *
 * ���������ȷ��ָ��ǿա�
 */
#define OS_ERRNO_NSM_PTR_NULL                               SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x01)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺����������ռ��С�Ƿ���
 *
 * ֵ: 0x02001b02
 *
 * ��������������ռ����ô�СSD6183�費С��1K�ֽڣ�SD6157/82�費С��212�ֽڡ�
 */

#define OS_ERRNO_NSM_SPACE_SIZE_ILLEG                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x02)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���������ռ�����ռ������ռ��׵�ַδ�ֽڶ��롣
 *
 * ֵ: 0x02001b03
 *
 * ��������������ռ��׵�ַ��4K�ֽڶ���(SD6183)��4�ֽڶ���(SD6108/81/57/82)��
 */
#define OS_ERRNO_NSM_ADDR_NOT_ALIGN                         SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x03)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���������ռ��Сδ�ֽڶ��롣
 *
 * ֵ: 0x02001b04
 *
 * ��������������ռ��С��4K�ֽڶ���(SD6183)��4�ֽڶ���(SD6108/81/57/82)��
 */
#define OS_ERRNO_NSM_SIZE_NOT_ALIGN                         SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x04)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�����ռ�������
 *
 * ֵ: 0x02001b05
 *
 * �����������Ӽ�¼ʱ��ȷ�������ռ����㹻�Ŀռ�洢��
 */
#define OS_ERRNO_NSM_MEM_FULL                               SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x05)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�����ռ��м�¼��������
 *
 * ֵ: 0x02001b06
 *
 * ����������������ռ�����Ӽ�¼ʱ��ȷ����¼��Ψһ��
 */
#define OS_ERRNO_NSM_OBJ_RENAME                             SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x06)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺ɾ��������¼ʱ����Ӧ��¼�����ڡ�
 *
 * ֵ: 0x02001b07
 *
 * ���������ɾ��������¼ʱ����ȷ����Ӧ��¼���ڡ�
 */
#define OS_ERRNO_NSM_DEL_NOT_FIND                           SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x07)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�����ռ��ж�Ӧ��¼�����ڡ�
 *
 * ֵ: 0x02001b08
 *
 * ���������ȷ���ÿռ�������Ӧ��¼��
 */
#define OS_ERRNO_NSM_FIND_FAILURE                           SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x08)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺ʵ���������ռ�ID�Ƿ���
 *
 * ֵ: 0x02001b0a
 *
 * ���������ȷ�ϸÿռ�ID�Ƿ���ȷ��
 */
#define OS_ERRNO_LOCAL_NSM_ID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x0a)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�����ռ��������ʧ�ܡ�
 *
 * ֵ: 0x02001b0b
 *
 * ���������ȷ�������ռ��ڴ��Ƿ��㹻��
 */
#define OS_ERRNO_NSM_OBJ_ALLOC_FAILED                 SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x0b)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺Space IDָ������
 *
 * ֵ: 0x02001b0c
 *
 * ���������Space ID�������ռ䴴��ʱȡֵ��Χ(0,0xffff],�����ֶ��󴴽�ʱȡֵ��Χ[0,0xffff]��
 */
#define OS_ERRNO_NSM_SPACE_ID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x0c)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���뷽ʽָ������
 *
 * ֵ: 0x02001b0d
 *
 * ����������ο�ö������NS_MEM_ALIGN_E��0�����ֿռ�ȡֵ��Χ[NS_ADDR_ALIGN_004, NS_ADDR_ALIGN_128],��0�����ֿռ�ȡֵ��Χ[NS_ADDR_ALIGN_4K, NS_ADDR_ALIGN_16M]��
 */
#define OS_ERRNO_NSM_MEM_ALIGN_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x0d)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺0�����ֿռ�����ָ������
 *
 * ֵ: 0x02001b0e
 *
 * ���������ȷ��ȡֵ��Χ��[0 , 0xf0000000)��
 */
#define OS_ERRNO_GLOBLE_NAME_ID_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x0e)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�����ռ������ַע��ӿڽ������˵��á�
 *
 * ֵ: 0x02001b0f
 *
 * ����������������˵��á�
 */
#define OS_ERRNO_NSM_MCPU_ALLOW                             SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x0f)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺��������ռ������ַ�θ���Ϊ0��
 *
 * ֵ: 0x02001b10
 *
 * ������������������ַ�θ�������Ϊ0��
 */
#define OS_ERRNO_NSM_VIR_MEM_NUM_ZERO                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x10)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�����ռ������ַ�������ַ�γ���Ϊ0��
 *
 * ֵ: 0x02001b11
 *
 * ������������������ַ�������ַ�γ��Ȳ���Ϊ0��
 */
#define OS_ERRNO_NSM_MEM_SEG_SIZE_ZERO                      SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x11)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���������ռ��ַ�򳤶�δ�ֽڶ��롣
 *
 * ֵ: 0x02001b12
 *
 * ���������ȷ�����������ռ��ַ�򳤶�����4K�ֽڶ��롣
 */
#define OS_ERRNO_NSM_ADDR_LEN_NOT_ALIGN                     SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x12)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���������ռ��ַ�ռ䷭ת��
 *
 * ֵ: 0x02001b13
 *
 * ���������ȷ�����������ռ��ַ�ռ䲻��ת��
 */
#define OS_ERRNO_NSM_ADDR_REGION_WRONG                      SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x13)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���������ռ������ַ�ռ��ص���
 *
 * ֵ: 0x02001b14
 *
 * ���������ȷ�����������ռ������ַ�ռ䲻�ص���
 */
#define OS_ERRNO_NSM_ADDR_REGION_OVERLAP                    SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x14)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�����ռ������ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02001b15
 *
 * ���������ȷ��0�������ռ��ڴ��Ƿ��㹻��
 */
#define OS_ERRNO_NSM_MEM_ALLOC_FAILED                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x15)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�����ռ����Ͳ����Ƿ���
 *
 * ֵ: 0x02001b16
 *
 * ���������0��ʾʵ���������ռ䣬1��ʾʵ���������ռ䣬����ֵ�Ƿ���
 */
#define OS_ERRNO_NSM_TYPE_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x16)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�ظ����������ռ������ƥ�䡣
 *
 * ֵ: 0x02001b17
 *
 * ���������ȷ���ظ����������ռ�ʱ���һ�¡�
 */
#define OS_ERRNO_NSM_SPACE_CREATE_REPEAT                    SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x17)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�����ַδע�ᡣ
 *
 * ֵ: 0x02001b18
 *
 * ���������ȷ�����������ռ�ǰ,��ע�������ַ��
 */
#define OS_ERRNO_NSM_VIR_MEM_NOT_REG                        SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x18)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�Ҳ����ɷ�������ַ�ռ䡣
 *
 * ֵ: 0x02001b19
 *
 * ���������ȷ�����ַ�ռ乻�á�
 */
#define OS_ERRNO_NSM_VIR_MEM_NOT_ENOUGH                     SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x19)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�������ֶ���ʱ��СΪ0
 *
 * ֵ: 0x02001b1a
 *
 * ���������ȷ���������ֶ���ʱ��С��Ϊ0��
 */
#define OS_ERRNO_NSM_OBJ_SIZE_ZERO                          SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x1a)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�������ֶ���ʱMMU�������ò���ȷ
 *
 * ֵ: 0x02001b1b
 *
 * ���������ȷ���������ֶ���ʱMMU����������ȷ��
 */
#define OS_ERRNO_NSM_OBJ_ATTR_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x1b)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���ֿռ�δ����
 *
 * ֵ: 0x02001b1c
 *
 * ���������ȷ���Ѿ��������ֿռ䡣
 */
#define OS_ERRNO_NSM_SPACE_NOT_CREATE                       SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x1c)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺��ʵ���ڵĺ˴��������ʵ�������ֿռ�
 *
 * ֵ: 0x02001b1d
 *
 * ���������ȷ����ʵ���ĺ˴��������ʵ�������ֿռ䡣
 */
#define OS_ERRNO_NSM_SPACE_NOT_MATCH                        SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x1d)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�ظ��ͷ����ַ
 *
 * ֵ: 0x02001b1e
 *
 * ���������ȷ�����ظ��ͷ����ַ��
 */
#define OS_ERRNO_NSM_VIR_MEM_FREE_REPEAT                    SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x1e)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺����ͬһ�����ֶ���ʱ����С����뷽ʽ����ͬ
 *
 * ֵ: 0x02001b1f
 *
 * �������������ͬһ�����ֶ���ʱ��ȷ����С�Ͷ��뷽ʽ��ͬ��
 */
#define OS_ERRNO_NSM_OBJ_SIZE_OR_ALIGN_NOT_MATCH            SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x1f)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�ͷ������ַʱ�����ַδ�ҵ�
 *
 * ֵ: 0x02001b20
 *
 * ���������ȷ���ͷ������ַ���ڡ�
 */
#define OS_ERRNO_NSM_VIR_MEM_FREE_NOT_FIND                  SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x20)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺ͬһ���˴���ͬһ�����ֶ���ʱ�����Բ���ͬ
 *
 * ֵ: 0x02001b21
 *
 * ���������ȷ��ͬһ���˴���ͬһ�����ֶ���ʱ��������ͬ��
 */
#define OS_ERRNO_NSM_OBJ_ATTR_NOT_MATCH                     SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x21)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���ֿռ䴴��ʱ��������ֿռ������ַӳ��������ַΪ0
 *
 * ֵ: 0x02001b22
 *
 * ���������ȷ����������ֿռ������ַӳ��������ַ��Ϊ0��
 */
#define OS_ERRNO_NSM_CREATE_PHY_ADDR_ZERO                   SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x22)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺�ظ�ע�������ַ
 *
 * ֵ: 0x02001b23
 *
 * ���������ȷ����Ҫ�ظ�ע�������ַ��
 */
#define OS_ERRNO_NSM_VIR_ADDR_CFG_REPEAT                    SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x23)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺��ʵ��δ����������£��Ӻ˴������ֶ���
 *
 * ֵ: 0x02001b24
 *
 * �������:������ʵ�����ٸ��Ӻ�����MMU��
 */
#define OS_ERRNO_NSM_SLAVE_INST_UNCREATE                    SRE_ERRNO_OS_ERROR(OS_MID_NSM, 0x24)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺������OS_NSM_SPACE_PADDR���õ������ַ����ȷ
 *
 * ֵ: 0x02001b25
 *
 * �������:ȷ��������OS_NSM_SPACE_PADDR���õ������ַ�������ַ�Ƕ�Ӧ�ġ�
 */
#define OS_ERRNO_NSM_PADDR_CFG_WRONG                        SRE_ERRNO_OS_ERROR(OS_MID_NSM, 0x25)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���ֿռ䴴��ʱ����������ַδӳ��
 *
 * ֵ: 0x02001b26
 *
 * �������:ȷ�����ֿռ䴴��ʱ����������ַ�Ѿ�ӳ�����
 */
#define OS_ERRNO_NSM_CREATE_VA2PA_ERROR                     SRE_ERRNO_OS_ERROR(OS_MID_NSM, 0x26)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���ֿռ䴴��ʱ��������ַӳ��������ַΪPL2��GLOBAL��ַ
 *
 * ֵ: 0x02001b27
 *
 * �������:ȷ�����ֿռ䴴��ʱ��������ַӳ��������ַ��ΪPL2��GLOBAL��ַ��
 */
#define OS_ERRNO_NSM_CREATE_PA_ILLEGAL                      SRE_ERRNO_OS_ERROR(OS_MID_NSM, 0x27)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺һ�������ʹ������һ������˵������ռ�PL2��Local�ڴ�
 *
 * ֵ: 0x02001b28
 *
 * �������:ȷ�������ռ�PL2��Local�ڴ�ֻ��һ�����������Ӳ�߳�ʹ�ã�������ʹ�ñ���
 */
#define OS_ERRNO_NSM_OBJ_CREATE_PL2_OWNER_ERROR             SRE_ERRNO_OS_ERROR(OS_MID_NSM, 0x28)

/**
 * @ingroup SRE_nsm
 * �����ռ�����룺���������ռ������ַӳ��������ַΪDDR�ռ䣬��ַ�򳤶�δ1M����
 *
 * ֵ: 0x02001b29
 *
 * ���������ȷ�����������ռ������ַӳ��������ַΪDDR�ռ�ʱ����ַ�ͳ�����Ҫ1M���롣
 */
#define OS_ERRNO_NSM_ADDR_OR_LEN_NOT_DDR_ALIGN              SRE_ERRNO_OS_ERROR(OS_MID_NSM,0x29)

/**
 * @ingroup SRE_nsm
 *
 * �����ռ�ע��ṹ�嶨�塣
 */
#if(OS_HIDSP == OS_HARDWARE_PLATFORM)
typedef struct tagNsmModInfo
{
    UINT32 uwVA;                 /**< �����ռ�������ʼ��ַ                          */
    UINT32 uwPA;                 /**< �����ռ�������ʼ��ַ                          */
    UINT32 uwSize;               /**< �����ռ��ڴ�ռ��С                          */
}NSM_MOD_INFO_S;
#else
typedef struct tagNsmModInfo
{
    VOID  *pStart;               /**< �����ռ���ʼ��ַ                              */
    UINT32 uwSize;               /**< �����ռ��ڴ�ռ��С                          */
}NSM_MOD_INFO_S;
#endif
/**
 * @ingroup SRE_nsm
 * �����ռ������ַע�ṹ�嶨�塣
 */
typedef struct tagNsVirMemCfg
{
    UINT32 uwAddr;               /**< �����ռ������ڴ��ַ����4K�ֽڶ���            */
    UINT32 uwLen;                /**< �����ռ������ڴ��С����4K�ֽڶ���            */
}SRE_NS_VIR_MEM_CFG;

/**
 * @ingroup SRE_nsm
 * �����ռ䴴���ṹ�嶨�塣
 */
typedef struct tagNameSpacePara
{
    UINT32 uwNsType;             /**< 0��ʾʵ����NS��1��ʾʵ����NS                        */
    UINT32 uwRes;                /**< ��������дΪ0                                       */
    VOID  *pVirAddr;             /**< ���ֿռ������ַ������4K����                        */
    UINT32 uwNsSize;             /**< ���ֿռ��С������4K����                            */
}NAME_SPACE_PARA;

/**
 * @ingroup SRE_nsm
 * �����ռ���󴴽����뷽ʽö�ٶ��塣
 */
typedef enum
{
    NS_ADDR_ALIGN_004  = 2,      /**< 4�ֽڶ���    */
    NS_ADDR_ALIGN_008  = 3,      /**< 8�ֽڶ���    */
    NS_ADDR_ALIGN_016  = 4,      /**< 16�ֽڶ���   */
    NS_ADDR_ALIGN_032  = 5,      /**< 32�ֽڶ���   */
    NS_ADDR_ALIGN_064  = 6,      /**< 64�ֽڶ���   */
    NS_ADDR_ALIGN_128  = 7,      /**< 128�ֽڶ���  */
    NS_ADDR_ALIGN_4K   = 8,      /**< 4K�ֽڶ���   */
    NS_ADDR_ALIGN_8K   = 9,      /**< 8K�ֽڶ���   */
    NS_ADDR_ALIGN_16K  = 10,     /**< 16K�ֽڶ���  */
    NS_ADDR_ALIGN_64K  = 11,     /**< 64K�ֽڶ���  */
    NS_ADDR_ALIGN_256K = 12,     /**< 256K�ֽڶ��� */
    NS_ADDR_ALIGN_512K = 13,     /**< 512K�ֽڶ��� */
    NS_ADDR_ALIGN_1M   = 14,     /**< 1M�ֽڶ���   */
    NS_ADDR_ALIGN_4M   = 15,     /**< 4M�ֽڶ���   */
    NS_ADDR_ALIGN_16M  = 16,     /**< 256M�ֽڶ��� */
}NS_MEM_ALIGN_E;

#if(OS_HIDSP == OS_HARDWARE_PLATFORM)

/**************************** Cache����(���º�ֻ��ѡ��һ��) *********************/
/**
 * @ingroup SRE_nsm
 * ���ֶ���MMU�ڴ�cache����-non-cache��
 */
#define OS_NS_OBJ_STATE_NONCACHE                                  0x1

/**
 * @ingroup SRE_nsm
 * ���ֶ���MMU�ڴ�cache����-cache��
 */
#define OS_NS_OBJ_STATE_CACHE                                     0x3

/**************************** Share����(���º�ֻ��ѡ��һ��) *********************/
/**
 * @ingroup SRE_nsm
 * ���ֶ���MMU�ڴ湲������-non-share��
 */
#define OS_NS_OBJ_STATE_NONSHARED                                 0x0

/**
 * @ingroup SRE_nsm
 * ���ֶ���MMU�ڴ湲������-share��
 */
#define OS_NS_OBJ_STATE_SHARED                                    0x1

/**
 * @ingroup SRE_nsm
 * ���ֶ���MMU�ڴ�������װ�ֻ꣬���������������OS_NS_OBJ_STATE_NONCACHE&OS_NS_OBJ_STATE_NONSHARED; OS_NS_OBJ_STATE_NONCACHE&OS_NS_OBJ_STATE_SHARED; OS_NS_OBJ_STATE_CACHE&OS_NS_OBJ_STATE_NONSHARED��
 */
#define OS_NS_OBJ_MMU_ATTR(CacheAttr, Share) OS_MMU_ATTR(CacheAttr, OS_MMU_STATE_SPEC, Share, OS_MMU_STATE_READ_WRITE)

/**
 * @ingroup  SRE_nsm
 * @brief  ע�������ռ������ַ��Ϣ��
 *
 * @par ����:
 * ͨ�����������ռ������ַ�θ���uwNum�������ַ��ʼ��ַ�ͳ���pstVirMemCfg��ע�������ַ��Ϣ��
 *
 * @attention
 * <ul>
 * <li>��SD6183ƽ̨��֧�ָù��ܡ�</li>
 * <li>���������˵���һ�Ρ�</li>
 * </ul>
 *
 * @param  uwNum         [IN]  ����#UINT32  �������ַ�θ�����ȡֵ��ΧΪ(0, 0xffffffff]��
 * @param  pstVirMemCfg  [IN]  ����#SRE_NS_VIR_MEM_CFG *  �������ռ������ַ��Ϣ�������ص���
 *
 * @retval #OS_ERRNO_NSM_MCPU_ALLOW                 0x02001b0f�������ռ������ַע��ӿڽ������˵��á�
 * @retval #OS_ERRNO_NSM_VIR_MEM_NUM_ZERO           0x02001b10����������ռ������ַ�θ���Ϊ0��
 * @retval #OS_ERRNO_NSM_PTR_NULL                   0x02001b01����ηǷ�������ָ��ΪNULL��
 * @retval #OS_ERRNO_NSM_MEM_SEG_SIZE_ZERO          0x02001b11�������ռ������ַ�������ַ�γ���Ϊ0��
 * @retval #OS_ERRNO_NSM_ADDR_LEN_NOT_ALIGN         0x02001b12�����������ռ��ַ�򳤶�δ�ֽڶ��롣
 * @retval #OS_ERRNO_NSM_ADDR_REGION_WRONG          0x02001b13�����������ռ��ַ�ռ䷭ת��
 * @retval #OS_ERRNO_NSM_ADDR_REGION_OVERLAP        0x02001b14�����������ռ������ַ�ռ��ص���
 * @retval #OS_ERRNO_NSM_MEM_ALLOC_FAILED           0x02001b15�������ռ������ڴ�ʧ�ܡ�
 * @retval #OS_ERRNO_NSM_VIR_ADDR_CFG_REPEAT        0x02001b23���ظ�ע�������ַ��
 * @retval #SRE_OK                                  0x00000000�������ռ������ַ��Ϣע��ɹ���
 * @par ����:
 * <ul><li>sre_nsm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see
 */
extern UINT32 SRE_NSVirMemCfg(UINT32 uwNum, SRE_NS_VIR_MEM_CFG *pstVirMemCfg);

/**
 * @ingroup  SRE_nsm
 * @brief  ���������ռ䡣
 *
 * @par ����:
 * ͨ�����������ռ䴴������pstPara�������ռ�uwSpaceId�����������ռ䡣
 *
 * @attention
 * <ul>
 * <li>��SD6183ƽ̨��֧�ָù��ܡ�</li>
 * <li>ֻ��Ҫһ���˴���һ�Σ�������ɺ�ʵ���������˶�����ֱ�Ӵ��������롣</li>
 * <li>��������0�����ֿռ䡣</li>
 * <li>��֧��PL2��Global��ַ��</li>
 * </ul>
 *
 * @param  pstPara       [IN]  ����#NAME_SPACE_PARA *  �������ռ������Ϣ��
 * @param  uwSpaceId     [IN]  ����#UINT32  �������ռ�ID��ȡֵ��Χ(0,0xffff]��
 *
 * @retval #OS_ERRNO_NSM_PTR_NULL                   0x02001b01����ηǷ�������ָ��ΪNULL��
 * @retval #OS_ERRNO_NSM_SPACE_ID_INVALID           0x02001b0c��Space IDָ������
 * @retval #OS_ERRNO_NSM_TYPE_INVALID               0x02001b16�������ռ����Ͳ����Ƿ���
 * @retval #OS_ERRNO_NSM_MEM_SEG_SIZE_ZERO          0x02001b11�������ռ������ַ�������ַ�γ���Ϊ0��
 * @retval #OS_ERRNO_NSM_ADDR_LEN_NOT_ALIGN         0x02001b12�����������ռ��ַ�򳤶�δ�ֽڶ��롣
 * @retval #OS_ERRNO_NSM_ADDR_REGION_WRONG          0x02001b13�����������ռ��ַ�ռ䷭ת��
 * @retval #OS_ERRNO_NSM_FIND_FAILURE               0x02001b08�������ռ��ж�Ӧ��¼�����ڡ�
 * @retval #OS_ERRNO_NSM_SPACE_CREATE_REPEAT        0x02001b17���ظ����������ռ������ƥ�䡣
 * @retval #OS_ERRNO_NSM_VIR_MEM_NOT_REG            0x02001b18�������ַδע�ᡣ
 * @retval #OS_ERRNO_NSM_MEM_ALLOC_FAILED           0x02001b15�������ռ������ڴ�ʧ�ܡ�
 * @retval #OS_ERRNO_NSM_VIR_MEM_NOT_ENOUGH         0x02001b19���Ҳ����ɷ�������ַ�ռ䡣
 * @retval #OS_ERRNO_NSM_CREATE_PHY_ADDR_ZERO       0x02001b22�����ֿռ䴴��ʱ��������ֿռ������ַӳ��������ַΪ0��
 * @retval #OS_ERRNO_NSM_CREATE_VA2PA_ERROR         0x02001b26�����ֿռ䴴��ʱ����������ַδӳ�䡣
 * @retval #OS_ERRNO_NSM_CREATE_PA_ILLEGAL          0x02001b27�����ֿռ䴴��ʱ��������ַӳ��������ַΪPL2��GLOBAL��ַ��
 * @retval #OS_ERRNO_NSM_ADDR_OR_LEN_NOT_DDR_ALIGN  0x02001b29�����������ռ������ַӳ��������ַΪDDR�ռ䣬��ַ�򳤶�δ1M���롣
 * @retval #SRE_OK                                  0x00000000�������ռ䴴���ɹ���
 * @par ����:
 * <ul><li>sre_nsm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see
 */
extern UINT32 SRE_NSCreate(NAME_SPACE_PARA *pstPara, UINT32 uwSpaceId);

/**
 * @ingroup  SRE_nsm
 * @brief �������ֶ���
 *
 * @par ����:
 * ͨ������ռ��uwSpaceID��������uwNameId�������С�������ڴ�Ķ��뷽ʽ��MMU���ԣ��������뵽���ڴ��ַ��
 *
 * @attention
 * <ul>
 * <li>��SD6183ƽ̨��֧�ָù��ܡ�</li>
 * <li>0�����ֿռ䣬uwNameIdȡֵ��ΧΪ[0,0xf0000000)��enAlignȡֵ��Χ[NS_ADDR_ALIGN_004, NS_ADDR_ALIGN_128]��</li>
 * <li>��0�����ֿռ䣬enAlignȡֵ��Χ[NS_ADDR_ALIGN_4K, NS_ADDR_ALIGN_16M]��</li>
 * <li>���ֶ����������ò�������cache&share�����򱨴�</li>
 * <li>��0�����ֿռ��������uwAttr�����Ч��</li>
 * </ul>
 *
 * @param  uwSpaceID     [IN]  ����#UINT32  �������ռ�ID��ȡֵ��Χ[0,0xffff]��
 * @param  uwNameId      [IN]  ����#UINT32  �����������������
 * @param  uwSize        [IN]  ����#UINT32  �����������С��
 * @param  enAlign       [IN]  ����#NS_MEM_ALIGN_E �����뷽ʽ��
 * @param  uwAttr        [IN]  ����#UINT32  �����ֶ���MMU���ԣ���ЧbitλΪ(bit7-0)���������òο�OS_NS_OBJ_MMU_ATTR��
 * @param  puwAddr       [OUT] ����#UINT32 *������������������ڴ�ռ��ַ��
 *
 * @retval #OS_ERRNO_NSM_SPACE_ID_INVALID            0x02001b0c��Space IDָ������
 * @retval #OS_ERRNO_NSM_OBJ_SIZE_ZERO               0x02001b1a���������ֶ���ʱ��СΪ0��
 * @retval #OS_ERRNO_NSM_MEM_ALIGN_INVALID           0x02001b0d�����뷽ʽָ������
 * @retval #OS_ERRNO_NSM_PTR_NULL                    0x02001b01����ηǷ�������ָ��ΪNULL��
 * @retval #OS_ERRNO_NSM_OBJ_ATTR_INVALID            0x02001b1b���������ֶ���ʱMMU�������ò���ȷ��
 * @retval #OS_ERRNO_NSM_SPACE_NOT_CREATE            0x02001b1c�����ֿռ�δ������
 * @retval #OS_ERRNO_NSM_SPACE_NOT_MATCH             0x02001b1d����ʵ���ڵĺ˴��������ʵ�������ֿռ䡣
 * @retval #OS_ERRNO_NSM_FIND_FAILURE                0x02001b08�������ռ��ж�Ӧ��¼�����ڡ�
 * @retval #OS_ERRNO_NSM_OBJ_ALLOC_FAILED            0x02001b0b�������ռ��������ʧ�ܡ�
 * @retval #OS_ERRNO_GLOBLE_NAME_ID_INVALID          0x02001b0e��0�����ֿռ�����ָ������
 * @retval #OS_ERRNO_NSM_MEM_ALLOC_FAILED            0x02001b15�������ռ������ڴ�ʧ�ܡ�
 * @retval #OS_ERRNO_NSM_OBJ_SIZE_OR_ALIGN_NOT_MATCH 0x02001b1f������ͬһ�����ֶ���ʱ����С����뷽ʽ����ͬ��
 * @retval #OS_ERRNO_NSM_OBJ_ATTR_NOT_MATCH          0x02001b21��ͬһ���˴���ͬһ�����ֶ���ʱ�����Բ���ͬ��
 * @retval #OS_ERRNO_NSM_SLAVE_INST_UNCREATE         0x02001b24����ʵ��δ����������£��Ӻ˴������ֶ���
 * @retval #OS_ERRNO_NSM_OBJ_CREATE_PL2_OWNER_ERROR  0x02001b28��һ�������ʹ������һ������˵������ռ�PL2��Local�ڴ档
 * @retval #SRE_OK                                   0x00000000���������󴴽��ɹ���
 * @par ����:
 * <ul><li>sre_nsm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see
 */
extern UINT32 SRE_NSObjCreate(UINT32 uwSpaceID, UINT32 uwNameId, UINT32 uwSize, NS_MEM_ALIGN_E enAlign, UINT32 uwAttr, UINT32 *puwAddr);

#else
/**
 * @ingroup  SRE_nsm
 * @brief ��ѯ���������¼��
 *
 * @par ����:
 * ͨ������ռ��uwSpaceID��������uwNameId���������ռ��в��Ҷ�Ӧ�ļ�¼����ͨ��ppAddr��puwSizeָ�뷵�����ַ�ʹ�С��
 *
 * @attention
 * <ul>
 * <li>����SD6108/SD6181/SD6182/SD6157ƽ̨��֧�ָù��ܡ�</li>
 * </ul>
 *
 * @param  uwSpaceID     [IN]  ����#UINT32  �������ռ�ţ���Ϊ��Ч���������Ժ���չʹ�á�
 * @param  uwNameId      [IN]  ����#UINT32  �����������������
 * @param  ppAddr        [OUT] ����#VOID ** ���������������׵�ַ��
 * @param  puwSize       [OUT] ����#UINT32 *������������������ڴ�ռ��С��
 *
 * @retval #OS_ERRNO_NSM_FIND_FAILURE           0x02001b08�������ռ��ж�Ӧ��¼�����ڡ�
 * @retval #OS_ERRNO_NSM_PTR_NULL               0x02001b01����ηǷ�������ָ��ΪNULL��
 * @retval #SRE_OK                              0x00000000����¼���ҳɹ���
 * @par ����:
 * <ul><li>sre_nsm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_NSReg | SRE_NSUnReg
 */
extern UINT32 SRE_NSFind (UINT32 uwSpaceID,  UINT32 uwNameId, VOID **ppAddr, UINT32 *puwSize);

/**
 * @ingroup  SRE_nsm
 * @brief ������������¼��
 *
 * @par ����:
 * ͨ�����������uwNameId�����������׵�ַpAddr�����������СuwSize���������ռ�uwSpaceID�����һ����¼��
 *
 * @attention
 * <ul>
 * <li>����SD6108/SD6181/SD6182/SD6157ƽ̨��֧�ָù��ܡ�</li>
 * </ul>
 *
 * @param  uwSpaceID     [IN]  ����#UINT32  �������ռ�ţ���Ϊ��Ч���������Ժ���չʹ�á�
 * @param  uwNameId      [IN]  ����#UINT32  �����������������
 * @param  pAddr         [IN]  ����#VOID *  �����������׵�ַ��
 * @param  uwSize        [IN]  ����#UINT32  ��������������ڴ�ռ��С��
 *
 * @retval #OS_ERRNO_NSM_MEM_FULL               0x02001b05�������ռ�������
 * @retval #OS_ERRNO_NSM_PTR_NULL               0x02001b01����ηǷ�������ָ��ΪNULL��
 * @retval #OS_ERRNO_NSM_OBJ_RENAME             0x02001b06�������ռ��м�¼��������
 * @retval #SRE_OK                              0x00000000����¼��ӳɹ���
 * @par ����:
 * <ul><li>sre_nsm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_NSUnReg
 */
extern UINT32 SRE_NSReg (UINT32 uwSpaceID, UINT32 uwNameId, VOID *pAddr, UINT32 uwSize);

/**
 * @ingroup  SRE_nsm
 * @brief ɾ�����������¼��
 *
 * @par ����:
 * ͨ�����������uwNameId���������ռ�uwSpaceID��ɾ����Ӧ�ļ�¼��
 *
 * @attention
 * <ul>
 * <li>����SD6108/SD6181/SD6182/SD6157ƽ̨��֧�ָù��ܡ�</li>
 * </ul>
 *
 * @param  uwSpaceID     [IN]  ����#UINT32  �������ռ�ţ���Ϊ��Ч���������Ժ���չʹ�á�
 * @param  uwNameId      [IN]  ����#UINT32  �����������������
 *
 * @retval #OS_ERRNO_NSM_DEL_NOT_FIND           0x02001b07��ɾ��������¼ʱ����Ӧ��¼�����ڡ�
 * @retval #SRE_OK                              0x00000000����¼ɾ���ɹ���
 * @par ����:
 * <ul><li>sre_nsm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_NSReg
 */

extern UINT32 SRE_NSUnReg (UINT32 uwSpaceID, UINT32 uwNameId);
#endif
#endif // #if (OS_OPTION_NSM == YES)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_NSM_H */


