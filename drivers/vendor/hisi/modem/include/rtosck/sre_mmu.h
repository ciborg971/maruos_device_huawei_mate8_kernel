/**
 * @file sre_mmu.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������mmuģ��Ķ���ͷ�ļ��� \n
 */
 /**@defgroup SRE_mmu MMU
  *@ingroup SRE_kernel
 */

#ifndef _SRE_MMU_H
#define _SRE_MMU_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define MMU_VA_T VOID*
#define MMU_PA_T VOID*

/**
 * @ingroup SRE_mmu
 * �����룺�����ַ�������ַ�򳤶ȷ�page���롣
 *
 * ֵ: 0x02001201
 *
 * �������: �����������ַ�������ַ�������Ƿ�page(�����ӳ����Ҫ8k, ���ݶ�ӳ����Ҫ4k)���롣
 */
#define OS_ERRNO_MMU_NOT_PAGE_ALIGNED                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1)

/**
 * @ingroup SRE_mmu
 * �����룺�ҵ������ַ��Ӧ�������ַΪ0����������MMU�ε������ַ�򳤶�Ϊ0��
 *
 * ֵ: 0x02001202
 *
 * �������: ����MMU�����õ������ַ�򳤶��Ƿ�Ϊ0��
 */
#define OS_ERRNO_MMU_SECTION_CFG_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x2)

/**
 * @ingroup SRE_mmu
 * �����룺δ���뵽һ��ҳ���ڴ档
 *
 * ֵ: 0x02001203
 *
 * �������: �����㹻����ڴ������
 */
#define OS_ERRNO_MMU_NO_LEVEL1_MEMORY                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3)

/**
 * @ingroup SRE_mmu
 * �����룺ӳ�������ַ�ռ��Ѿ�ӳ����߲����Ѿ�ӳ�䡣
 *
 * ֵ: 0x02001204
 *
 * �������: �����ӳ��������ַ�ռ��Ƿ��Ѿ�ӳ��򲿷��Ѿ�ӳ�䡣
 */
#define OS_ERRNO_MMU_ADDR_MAPPED                                 SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4)

/**
 * @ingroup SRE_mmu
 * �����룺δ���뵽����ҳ���ڴ档
 *
 * ֵ: 0x02001205
 *
 * �������: �����㹻����ڴ������
 */
#define OS_ERRNO_MMU_NO_LEVEL2_MEMORY                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x5)

/**
 * @ingroup SRE_mmu
 * �����룺δ���뵽ҳ��ӳ����Ϣ�ڴ档
 *
 * ֵ: 0x02001206
 *
 * �������: �����㹻����ڴ������
 */
#define OS_ERRNO_MMU_NO_MAP_INFO_MEMORY                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x6)

/**
 * @ingroup SRE_mmu
 * �����룺MMUģ���ʼ���ڴ�ӳ����Ϣ�ظ���
 *
 * ֵ: 0x02001207
 *
 * �������: ���MMU��ʼ���ڴ�ӳ����Ϣ�Ƿ��ظ���
 */
#define OS_ERRNO_MMU_INIT_ADDR_OVERLAPPED                        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x7)

/**
 * @ingroup SRE_mmu
 * �����룺(ȥ)ӳ���ڴ��ַ���������
 *
 * ֵ: 0x02001209
 *
 * �������: ����(ȥ)ӳ���ַ�ͳ��������Ƿ����
 */
#define OS_ERRNO_MMU_ADDR_OVERFLOW                               SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x09)

/**
 * @ingroup SRE_mmu
 * �����룺�����ַδӳ�䡣
 *
 * ֵ: 0x02001210
 *
 * �������: ��������ַ�Ƿ�ӳ���MMU��ʼ����ַ�Ƿ�����ڴ�������е�ַ��
 */
#define OS_ERRNO_MMU_ADDR_NOT_MAPPED                             SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x10)

/**
 * @ingroup SRE_mmu
 * �����룺ҳ����ʱ�ڴ�ռ䲻�㡣
 *
 * ֵ: 0x02001211
 *
 * �������: ���ÿռ��㹻��0�ŷ�����
 */
#define OS_ERRNO_MMU_DEOPTIMIZE_FAIL                             SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x11)

/**
 * @ingroup SRE_mmu
 * �����룺���Ȳ���ϲ�Ϊ��ҳ��
 *
 * ֵ: 0x02001212
 *
 * �������: �����������ַ�ͳ����Ƿ���ȷ��
 */
#define OS_ERRNO_MMU_OPTIMIZE_NO_NEED                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x12)

/**
 * @ingroup SRE_mmu
 * �����룺0�ŷ���ӳ��������ַ�������ַ��һ�¡�
 *
 * ֵ: 0x02001214
 *
 * �������: ����ʼ��ʱ�ڴ������ַ�����ַ�������ַ�Ƿ�һ�¡�
 */
#define OS_ERRNO_MMU_MEM_PT_NOT_FLAT                             SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x14)

/**
 * @ingroup SRE_mmu
 * �����룺��ʼ��ӳ����Ϣδ��������0�ŷ�����Ϣ��
 *
 * ֵ: 0x02001215
 *
 * �������: ����ʼ��ʱ�ڴ������ַ�Ƿ��������ӳ����Ϣ�С�
 */
#define OS_ERRNO_MMU_MEM_PT_NOT_INCLUDE                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x15)

/**
 * @ingroup SRE_mmu
 * �����룺��ʼ��ӳ����Ϣ0�ŷ����ڴ����Բ�һ�¡�
 *
 * ֵ: 0x02001216
 *
 * �������: ����ʼ��ʱ�ڴ���������Ƿ�һ�¡�
 */
#define OS_ERRNO_MMU_MEM_PT_STATE_DIFFERENT                      SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x16)

/**
 * @ingroup SRE_mmu
 * �����룺ATTRIBUTE�������
 *
 * ֵ: 0x02001217
 *
 * �������: ���ATTRIBUTE�����Ƿ�Ϊ���Ժ��һ�֡�
 */
#define OS_ERRNO_MMU_ATTRIBUTE_ERR                               SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x17)

/**
 * @ingroup SRE_mmu
 * �����룺ACCESS�������
 *
 * ֵ: 0x02001218
 *
 * �������: ���д�����Ƿ���϶����ԣ�����ִ�������Ƿ���϶����ԡ�
 */
#define OS_ERRNO_MMU_ACCESS_ERR                                  SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x18)

/**
 * @ingroup SRE_mmu
 * �����룺��ʼ��ӳ����Ϣ0�ŷ�������δ���óɿ�cache��
 *
 * ֵ: 0x02001219
 *
 * �������: ����ʼ��ʱ�ڴ������ַ�����Ƿ����wbwa��wbnwa��
 */
#define OS_ERRNO_MMU_MEM_PT_STATE_ERR                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x19)

/**
 * @ingroup SRE_mmu
 * �����룺��ʼ��ӳ����Ϣδ���û�ӳ��������ʼ��ַ��Ԫ�ظ������ó�0��
 *
 * ֵ: 0x0200121a
 *
 * �������: ���config��������MMU��ʼ��ӳ����Ϣ�Ƿ����ã����ӳ��������ʼ��ַ��Ԫ�ظ����Ƿ�����Ϊ0��
 */
#define OS_ERRNO_MMU_INIT_INFO_NOT_CONFIG                        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1a)

/**
 * @ingroup SRE_mmu
 * �����룺��δ���
 *
 * ֵ: 0x0200121b
 *
 * �������: �����Ρ�
 */
#define OS_ERRNO_MMU_PARAM_INVALID                               SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1b)

/**
 * @ingroup SRE_mmu
 * �����룺MMUģʽ���ô���
 *
 * ֵ: 0x0200121c
 *
 * �������: MMUģʽ����ֻ����BYPASS,MMU����ģʽ��
 */
#define OS_ERRNO_MMU_MODE_INVALID                                SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1c)

/**
 * @ingroup SRE_mmu
 * �����룺TLB ���ݲ�ѯʱindex����
 *
 * ֵ: 0x0200121d
 *
 * �������: TLB��ѯʱindex��Ч��Χ��0~31��
 */
#define OS_ERRNO_MMU_TLB_INDEX_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1d)

/**
 * @ingroup SRE_mmu
 * �����룺TLB ���ʹ���
 *
 * ֵ: 0x0200121e
 *
 * �������: TLB ���ʹ���ֻ����ITLB,DTLB���֡�
 */
#define OS_ERRNO_MMU_TLB_TYPE_INVALID                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1e)

/**
 * @ingroup SRE_mmu
 * �����룺TLB ��Ч���ԷǷ���
 *
 * ֵ: 0x0200121f
 *
 * �������: TLB ��Ч���ԷǷ���ֻ����PAGE_INV,LINE_INV,ALL_INV���֡�
 */
#define OS_ERRNO_MMU_TLB_INV_POLICY_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x1f)

/**
 * @ingroup SRE_mmu
 * �����룺TLB way number�Ƿ���
 *
 * ֵ: 0x02001220
 *
 * �������: WAY numberֻ����0~7��
 */
#define OS_ERRNO_MMU_WAY_NUMBER_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x20)

/**
 * @ingroup SRE_mmu
 * �����룺��ȡ�Ķ�Ӧindex��L1TLB������Ч��
 *
 * ֵ: 0x02001221
 *
 * �������: ȷ����index������ȷ�Լ���Ӧ��TLB����δ����Ч�����滻��
 */
#define OS_ERRNO_MMU_TLB_DATA_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x21)

/**
 * @ingroup SRE_mmu
 * �����룺Page Size�Ƿ���
 *
 * ֵ: 0x02001222
 *
 * �������: �޸�Page Size��
 */
#define OS_ERRNO_MMU_PAGE_SIZE_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x22)

/**
 * @ingroup SRE_mmu
 * �����룺SYSTEM MODE�Ƿ���
 *
 * ֵ: 0x02001223
 *
 * �������: ֻ��ΪSUPER_MODE����USER_MODE��
 */
#define OS_ERRNO_MMU_SYS_MODE_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x23)

/**
 * @ingroup SRE_mmu
 * �����룺���õ��ڴ����ԷǷ���
 *
 * ֵ: 0x02001224
 *
 * �������: ʹ��OS�ṩ�����Ժ������ڴ�����ԣ����Ժ������Ϣ�鿴SRE_MmuAssign��SRE_MmuMcAssign�ӿ�˵����
 */
#define OS_ERRNO_MMU_PAGEMAP_STATE_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x24)

/**
 * @ingroup SRE_mmu
 * �����룺MMUģʽ�£�ʵ��ַת���ַʧ�ܡ�
 *
 * ֵ: 0x02001227
 *
 * �������: MMUģʽ�£�ʵ��ַδ����ӳ�䡣
 */
#define OS_ERRNO_MMU_PA2VA_ERROR                                SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x27)

/**
 * @ingroup SRE_mmu
 * �����룺��ַת���ӿڣ���������ַ�������ַ��4�ֽڶ��롣
 *
 * ֵ: 0x02001228
 *
 * �������: �����������ַ�������ַ�Ƿ�4�ֽڶ��롣
 */
#define OS_ERRNO_MMU_NOT_WORD_ALIGNED                           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x28)

/**
 * @ingroup SRE_mmu
 * �����룺����ҳ���ڴ治����
 *
 * ֵ: 0x02001229
 *
 * �������: �������ҳ��ռ�
 */
#define OS_ERRNO_MMU_SIZE_ERROR                                 SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x29)

/**
 * @ingroup SRE_mmu
 * �����룺L2TLB setindex number�Ƿ���
 *
 * ֵ: 0x02001230
 *
 * �������: setindexֻ����0~127��
 */
#define OS_ERRNO_MMU_SET_NUMBER_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x30)

/**
 * @ingroup SRE_mmu
 * �����룺��ַӳ��ʱ������L1TLB�в��ֻ���ȫ�����ַ�Ѿ����á�
 *
 * ֵ: 0x02001231
 *
 * �������: �ȵ���SRE_MmuUnAssign�����Ѿ����õ�ҳ����������ȡ��ӳ���������ӳ�䣬����ӳ��������δӳ��ĵ�ַ��
 */
#define OS_ERRNO_MMU_VADDR_L1TLB_OVERLAP                        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x31)

/**
 * @ingroup SRE_mmu
 * �����룺��ַӳ��ʱ������L2TLB�в��ֻ���ȫ�����ַ�Ѿ����á�
 *
 * ֵ: 0x02001232
 *
 * �������: �ȵ���SRE_MmuUnAssign�����Ѿ����õ�ҳ����������ȡ��ӳ���������ӳ�䣬����ӳ��������δӳ��ĵ�ַ��
 */
#define OS_ERRNO_MMU_VADDR_L2TLB_OVERLAP                        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x32)


/**
 * @ingroup SRE_mmu
 * �����룺����ҳ�����ַδ��0x4000�ֽ�(16K)��С���롣
 *
 * ֵ: 0x02001233
 *
 * �������: �������ҳ�����ַ�Ƿ�0x4000�ֽڴ�С���롣
 */
#define OS_ERRNO_MMU_PAGE_TBL_ADDR_NOT_ALIGN                    SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x33)

/**
 * @ingroup SRE_mmu
 * �����룺����ҳ����δ��0x400�ֽ�(1k)��С���롣
 *
 * ֵ: 0x02001234
 *
 * �������: �������ҳ�����Ƿ�0x400�ֽڴ�С���롣
 */
#define OS_ERRNO_MMU_PAGE_TBL_LEN_NOT_ALIGN                     SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x34)

/**
 * @ingroup SRE_mmu
 * �����룺�����ҳ���ַ�򳤶ȷǷ���
 *
 * ֵ: 0x02001235
 *
 * �������: ��ȷ�������ҳ���������ȷ��(����ҳ���ַ����Ϊ0��ҳ���Ȳ���Ϊ0��
   ��OS����MMUҳ��ӳ��MAP�Ľ�������֤ҳ����ڵ���0x4000��16K��;
   �����ù���(��SDK) ����MMUҳ��ӳ��MAP�Ľ�������ҳ���С���ñ��뱣֤��������жε�ӳ��,��������ҳ���ȡ�
 */
#define OS_ERRNO_MMU_PAGE_TBL_CFG_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x35)

/**
 * @ingroup SRE_mmu
 * �����룺 L2 TLB����˳�����
 *
 * ֵ: 0x02001236
 *
 * �������: L2 TLB�Ĵ�������������8�����͵�ҳ���С����8�����ͽ�����һ�Ρ�
 */
#define OS_ERRNO_MMU_L2TLB_ORDER_ERR                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x36)

/**
 * @ingroup SRE_mmu
 * �����룺�˺Ŵ���
 *
 * ֵ: 0x02001237
 *
 * �������: �˺Ų��ܴ���33��
 */
#define OS_ERRNO_MMU_COREID_ERR                                 SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x37)


/**
 * @ingroup SRE_mmu
 * �����룺MMUģʽ�£����ַתʵ��ַʧ�ܡ�
 *
 * ֵ: 0x02001239
 *
 * �������: MMUģʽ�£����ַδ����ӳ�䡣
 */
#define OS_ERRNO_MMU_VA2PA_ERROR                                SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x39)

/**
 * @ingroup SRE_mmu
 * �����룺MMU��Ч��ʱ��ContextID����
 *
 * ֵ: 0x0200123a
 *
 * �������: ��鵱ǰ�����ContextID�Ƿ���Ч��
 */
#define OS_ERRNO_MMU_TLB_INV_CONTEXT_ID_INVALID                 SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3a)

/**
 * @ingroup SRE_mmu
 * �����룺MMUҳ��ȥӳ��(��������)ʱ������Ĳ���δ�������õ�ҳ���С���롣
 *
 * ֵ: 0x0200123b
 *
 * �������: �Ȱ�Ҫ��ַ��Χ����SRE_MmuPageSpaceGet���ҳ������ĵ�ַ��Χ��
 */
#define OS_ERRNO_MMU_PAGE_NOT_ALIGNED                           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3b)

/**
 * @ingroup SRE_mmu
 * �����룺��ȡMMU�ڴ�����ʱ�����ָ�����Ϊ�ա�
 *
 * ֵ: 0x0200123c
 *
 * �������: ȷ���洢�ڴ��������ֵ��ָ�벻��Ϊ�ա�
 */
#define OS_ERRNO_MMU_ATTR_OUTPUT_POINT_NULL                     SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3c)

/**
 * @ingroup SRE_mmu
 * �����룺��ȡMMU�ڴ�����ʱ������ָ�����ڴ��������ͷǷ���
 *
 * ֵ: 0x0200123d
 *
 * �������: ��ȷ���������������ֵΪ[OS_MMU_PERMISSION, OS_MMU_CACHE]
 */
#define OS_ERRNO_MMU_ATTR_TYPE_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3d)

/**
 * @ingroup SRE_mmu
 * �����룺ʵ���ַת���ռ䲻��
 *
 * ֵ: 0x0200123f
 *
 * �������: ����OS_MMU_PHYTOVIR_SIZE���ã�ȷ���ڴ�ռ乻�á�
 */
#define OS_ERRNO_MMU_PA_VA_MEM_ALLOC_FAIL                       SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x3f)

/**
 * @ingroup SRE_mmu
 * �����룺ʵ���ַת��ȥӳ��ʧ��
 *
 * ֵ: 0x02001240
 *
 * �������: ȷ���Ƿ��Ѿ������ʵ��ַӳ�䡣
 */
#define OS_ERRNO_MMU_PA_VA_REMOVE_FAIL                          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x40)

/**
 * @ingroup SRE_mmu
 * �����룺ʵ���ַת���ռ估��Сδ����
 *
 * ֵ: 0x02001241
 *
 * �������: ���OS_MMU_PHYTOVIR_ADDR��OS_MMU_PHYTOVIR_SIZE�����Ƿ�8�ֽڶ��롣
 */
#define OS_ERRNO_MMU_PA_VA_UN_ALIGN                             SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x41)

/**
 * @ingroup SRE_mmu
 * �����룺ʵ���ַת���ռ�δ���ã�����ʹ��SRE_MmuPA2VA
 *
 * ֵ: 0x02001242
 *
 * �������: ���OS_MMU_PHYTOVIR_SIZE�����Ƿ�����Ϊ0��
 */
#define OS_ERRNO_MMU_PA_VA_UNCONFIG                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x42)

/**
 * @ingroup SRE_mmu
 * �����룺mmuģ���������ֿռ�ʧ��
 *
 * ֵ: 0x02001243
 *
 * �������: ����ʵ�������ֿռ��С��
 */
#define OS_ERRNO_MMU_NAME_ALLOC_FAILED                            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x43)

/**
 * @ingroup SRE_mmu
 * �����룺����ָ���˵�MMUʱ��δ���MMU��Ϣ���г�ʼ��
 *
 * ֵ: 0x02001244
 *
 * �������: ����δ����OS��ʼ�����̣��͸�ָ����������Ϣ�ڴ档
 */
#define OS_ERRNO_MMU_MSG_UNINIT                               SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x44)

/**
 * @ingroup SRE_mmu
 * �����룺����ָ���˵�MMUʱ����ָ���˷�����Ϣʧ��
 *
 * ֵ: 0x02001245
 *
 * �������: ������δ���ȣ���ôԭ�����δ���ָ����MMU��Ϣ���г�ʼ������Ҫ�ȵ���SRE_MemCfg�ӿ����ã����벢��ʼ��ָ����MMU��Ϣ���С�
 */
#define OS_ERRNO_MMU_MSG_SEND_FAIL                                SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x45)

/**
 * @ingroup SRE_MNG
 * SRE MNG�����룺ʵ��ID�������ֵ
 *
 * ֵ: 0x02001246
 *
 * �������:ʵ��ID���Ϸ�
 */
#define OS_ERRNO_MMU_INST_ID_TOO_MAX           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x46)

/**
 * @ingroup SRE_MNG
 * SRE MNG�����룺Ӳ���߳�ID�������ֵ
 *
 * ֵ: 0x02001247
 *
 * �������:Ӳ���߳�ID���Ϸ�
 */
#define OS_ERRNO_MMU_CORE_ID_TOO_MAX           SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x47)

/**
 * @ingroup SRE_MNG
 * SRE MNG�����룺ʵ��δ׼����
 *
 * ֵ: 0x02001248
 *
 * �������:ʵ�������������Դ���ú󣬲��ܵ���
 */
#define OS_ERRNO_MMU_INST_NOT_READY            SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x48)

/**
 * @ingroup SRE_MNG
 * SRE MNG�����룺coreID����
 *
 * ֵ: 0x02001249
 *
 * �������:�û���coreID����ʵ����bitMap��
 */
#define OS_ERRNO_MMU_COREID_NOT_EXIST          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x49)

/**
 * @ingroup SRE_MNG
 * SRE MNG�����룺��ʵ��δ����������£����Ӻ�����MMU
 *
 * ֵ: 0x0200124a
 *
 * �������:������ʵ�����ٸ��Ӻ�����MMU
 */
#define OS_ERRNO_MMU_SLAVE_INST_UNCREATE       SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4a)

/**
 * @ingroup SRE_MNG
 * SRE MNG�����룺���˳�ʼ��MMU��Ϣ����ʱ�������ڴ�ʧ��
 *
 * ֵ: 0x0200124b
 *
 * �������:ȷ�������ռ��Ƿ��Ѿ�����
 */
#define OS_ERRNO_MMU_MSG_ALLOC_FAILED          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4b)

/**
 * @ingroup SRE_MNG
 * SRE MNG�����룺ʹ�÷��Ż��ӿ�ӳ��MMUʱ���������Խ��ͬ���ڴ�����
 *
 * ֵ: 0x0200124c
 *
 * �������:ʹ�÷��Ż��ӿ�ӳ��MMUʱ���������Խ��ͬ���ڴ�����
 */
#define OS_ERROR_MEM_REGION_OVERLAY          SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4c)


/**
 * @ingroup SRE_MNG
 * SRE MNG�����룺ʹ�÷��Ż��ӿ�ӳ��MMUʱ�����뷽ʽ����ȷ
 *
 * ֵ: 0x0200124d
 *
 * �������:ʹ�÷��Ż��ӿ�ӳ��MMUʱ��DDR��Ҫ����1M���룬�������ڴ�Ҫ����4K(���ݶ�)��8K(�����)����
 */
#define OS_ERRNO_MMU_NOT_CORRECT_ALIGNED     SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4d)

/**
 * @ingroup SRE_MNG
 * SRE MNG�����룺MMU��Ϣ����ʱ��������Ϣ�ڵ�ʧ��
 *
 * ֵ: 0x0200124e
 *
 * �������:��
 */
#define OS_ERRNO_MMU_MSG_NODE_ALLOC_FAILED        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4e)

/**
 * @ingroup SRE_MNG
 * SRE MNG�����룺MMU�޸�����ʱ�������޸ļĴ����ռ�����
 *
 * ֵ: 0x0200124f
 *
 * �������:��
 */
#define OS_ERRNO_MMU_REG_REGION_PROTECT        SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x4f)

/**
 * @ingroup SRE_MNG
 * SRE MNG�����룺MMU�޸�����ʱ�ڴ�ΰ������ܱ����ļĴ����ռ�
 *
 * ֵ: 0x02001250
 *
 * �������:��
 */
#define OS_ERRNO_MMU_SETATTR_PROTECT_REGION_COVERRED       SRE_ERRNO_OS_ERROR(OS_MID_MMU, 0x50)

/**
 * @ingroup  SRE_mmu
 * @brief ���ַתʵ��ַ��
 *
 * @par ����:
 * ���ַתʵ��ַ��
 *
 * @attention
 * <ul>
 * <li>AXƽ̨�����Ϊδӳ���ַ���᷵�ش����룬��ѯ���������ַΪ�����ַ����</li>
 * <li>AXƽֻ̨����MMUģ���ʼ����ɺ���á�</li>
 * <li>�ò�������SD6183��Cortex-AXƽ̨��֧�֡�</li>
 * </ul>
 *
 * @param  pVAddr  [IN] ����#MMU_VA_T�������ַ��
 * @param  ppPAddr  [OUT] ����#MMU_PA_T��ת����������ַ��
 *
 * @retval #OS_ERRNO_MMU_PARAM_INVALID       0x0200121b�����Ϊ�ա�
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED     0x02001210����ַδӳ�䡣
 * @retval #SRE_OK                           0x00000000��ת���ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see
 */
extern UINT32 SRE_MmuVA2PA(MMU_VA_T pVAddr, MMU_PA_T *ppPAddr);

/**
 * @ingroup  SRE_mmu
 * @brief ʵ��ַת���ַ��
 *
 * @par ����:
 * ʵ��ַת���ַ��
 *
 * @attention
 * <ul>
 * <li>AXƽֻ̨����MMUģ���ʼ����ɺ�MMUģʽ�µ��á�</li>
 * <li>AXƽ̨�����Ϊδӳ���ַ���᷵�ش����룬��ѯ���������ַΪ�����ַ����</li>
 * <li>�ò�������SD6183��Cortex-AXƽ̨��֧�֡�</li>
 * </ul>
 *
 * @param  pPAddr  [IN] ����#MMU_PA_T�������ַ��
 * @param  ppVAddr [OUT] ����#MMU_VA_T��ת����������ַ��
 *
 * @retval #OS_ERRNO_MMU_PARAM_INVALID       0x0200121b�����Ϊ�ա�
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED     0x02001210��AXƽ̨ʵ��ַδӳ�䡣
 * @retval #OS_ERRNO_MMU_PA_VA_UNCONFIG      0x02001242��ʵ���ַ�ռ�δ���á�
 * @retval #OS_ERRNO_MMU_PA2VA_ERROR         0x02001227��SD6183ƽ̨MMUģʽ��ʵ��ַδӳ�䡣
 * @retval #SRE_OK                           0x00000000��ת���ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see
 */
extern UINT32 SRE_MmuPA2VA(MMU_PA_T pPAddr, MMU_VA_T *ppVAddr);

/**
 * @ingroup  SRE_mmu
 * @brief ӳ�������ַ�������ַ��
 *
 * @par ����:
 * ���ݴ������pVStart��pPStart��uwLen�������⡢�����ַӳ�䣬������uwAttr�����ڴ����ԡ�
 *
 * @attention
 * <ul>
 * <li>uwLenΪ0ʱ�����е�ַӳ�䣬ֱ�ӷ��سɹ���</li>
 * <li>AXƽֻ̨����MMUģ���ʼ����ɺ���á�</li>
 * <li>AXƽ̨����κͷ����OSʹ�õ��ڴ���ӳ�䷽ʽ���������ַ�������ַһ�¡�</li>
 * <li>AXƽ̨��ַӳ��ʱ����uwVirtAddr��ʼ��page�������ӳ�䡣ĳһҳӳ�䲻�ɹ�ʱ���Ѿ�ӳ��ɹ��ĵ�ַ����ӳ���ϵ��</li>
 * <li>SD6183ƽ̨��ַӳ��ʱ������ӳ��ɴ�ҳ��</li>
 * <li>SD6183ƽ̨MMUȥӳ�估ӳ����ڴ�����cacheһ�������û���֤��</li>
 * <li>SD6183ƽ̨MMU���õ���ʵ��ַ�����ȶ����밴��4K���룬����ǿ�ִ�еĴ���Σ����밴��8K����</li>
 * </ul>
 *
 * @param  pVStart       [IN] ����#MMU_VA_T��ӳ�������ַ��ʼ��ַ��
 * @param  pPStart       [IN] ����#MMU_PA_T��ӳ�������ַ��ʼ��ַ��
 * @param  uwLen         [IN] ����#UINT32��ӳ����ڴ��С��
 * @param  uwAttr        [IN] ����#UINT32���ڴ����ԣ�SD6183ƽ̨uwAttr��ЧbitλΪ(bit7-0)��bit2-0:read,write,execute; bit3:shareable; bit4:speculative; bit7-5:cache attributes;
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201��������������ַ�������ַ�򳤶ȷ�page���롣
 * @retval #OS_ERRNO_MMU_NO_LEVEL1_MEMORY       0x02001203��δ���뵽һ��ҳ���ڴ档
 * @retval #OS_ERRNO_MMU_ADDR_MAPPED            0x02001204�����������ַ�Ѿ�ӳ�����
 * @retval #OS_ERRNO_MMU_NO_LEVEL2_MEMORY       0x02001205��δ���뵽����ҳ���ڴ档
 * @retval #OS_ERRNO_MMU_NO_MAP_INFO_MEMORY     0x02001206��δ���뵽ҳ��ӳ����Ϣ�ڴ档
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209����ַ�����
 * @retval #OS_ERRNO_MEM_FREE_SH_DAMAGED        0x02000311���ڴ��ͷ�ʱҪ�ͷŵ��ڴ���ͷ���ƻ��������ͷš�
 * @retval #OS_ERRNO_MMU_ATTRIBUTE_ERR          0x02001217�����uwState��ATTRIBUTE�������ò���ȷ��
 * @retval #OS_ERRNO_MMU_ACCESS_ERR             0x02001218�����uwState��ACCESS�������ò���ȷ��
 * @retval #OS_ERRNO_MMU_PA_VA_MEM_ALLOC_FAIL   0x0200123f���µ�ʵ��ӳ��ڵ������ڴ�ʧ�ܡ�
 * @retval #OS_ERRNO_MMU_MSG_NODE_ALLOC_FAILED  0x0200124e��MMU��Ϣ����ʱ��������Ϣ�ڵ�ʧ�ܡ�
 * @retval #SRE_OK                              0x00000000�����⡢�����ַӳ��ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see NA
 */
extern UINT32 SRE_MmuAssign(MMU_VA_T pVStart, MMU_PA_T pPStart,
                                  UINT32 uwLen, UINT32 uwAttr);


#if(OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-�ɶ���
 */
#define OS_MMU_STATE_READ                                      0x1

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-��д��
 *
 * �����Ժ�����ʱ��Ҫ����OS_MMU_STATE_READ����
 */
#define OS_MMU_STATE_WRITE                                     0x2

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-��ִ�С�
 *
 * �����Ժ�����ʱ��Ҫ����OS_MMU_STATE_READ����
 */
#define OS_MMU_STATE_EXE                                       0x4

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-strong ordered��
 */
#define OS_MMU_STATE_STRONGLY_ORDERED                          0x8

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-shared device��
 */
#define OS_MMU_STATE_SHARED_DEVICE                             0x10

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-device��
 */
#define OS_MMU_STATE_DEVICE                                    0x20

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-����cache��
 */
#define OS_MMU_STATE_CACHE_OFF                                 0x40

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-cache wbwa��
 */
#define OS_MMU_STATE_CACHE_WBWA                                0x80

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-cache wbnwa��
 */
#define OS_MMU_STATE_CACHE_WBNWA                               0x100

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-cache wtnwa��
 */
#define OS_MMU_STATE_CACHE_WTNWA                               0x200

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�����-shareable��
 */
#define OS_MMU_STATE_SHARE                                     0x400

/**
 * @ingroup SRE_mmu
 * MMU�ڴ���������-ACCESS��
 */
#define OS_MMU_STATEMASK_ACCESS                                (OS_MMU_STATE_READ | OS_MMU_STATE_WRITE | OS_MMU_STATE_EXE)

/**
 * @ingroup SRE_mmu
 * MMU�ڴ���������-Normal��
 */
#define OS_MMU_STATEMASK_NORMAL                                (OS_MMU_STATE_CACHE_OFF | OS_MMU_STATE_CACHE_WBWA | OS_MMU_STATE_CACHE_WBNWA | OS_MMU_STATE_CACHE_WTNWA)

/**
 * @ingroup SRE_mmu
 * MMU�ڴ���������-ATTRIBUTES��
 */
#define OS_MMU_STATEMASK_ATTRIBUTES                            (OS_MMU_STATEMASK_NORMAL | OS_MMU_STATE_STRONGLY_ORDERED | OS_MMU_STATE_SHARED_DEVICE | OS_MMU_STATE_DEVICE)

/**
 * @ingroup SRE_mmu
 * MMU�ڴ���������-SHARE��
 */
#define OS_MMU_STATEMASK_SHARE                                 OS_MMU_STATE_SHARE

/**
 * @ingroup SRE_mmu
 * mmu�û�������Ϣ�Ľṹ�嶨�塣
 *
 * mmu�û�������Ϣ��
 */
typedef struct tagVirtPhysMem
{
    UINT32 uwVirtualAddr;                                   /**< �����ַ */
    UINT32 uwPhysicalAddr;                                  /**< �����ַ */
    UINT32 uwLen;                                           /**< ����     */
    UINT32 uwInitialStateMask;                              /**< ״̬���� */
    UINT32 uwInitialState;                                  /**< ״̬     */
} VIRT_PHYS_MEM_S;

/**
 * @ingroup SRE_mmu
 * MMUģ��������Ϣ�Ľṹ�嶨�塣
 *
 * ����MMUģ�����������Ϣ��
 */
typedef struct tagMmuModInfo
{
    UINT32 uwMmuInitAddr;                                   /**< MMU��ʼ���ṹ�������׵�ַ       */
    UINT32 uwMmuInitNum ;                                   /**< MMU��ʼ���ṹ������Ԫ�ظ���     */
} MMU_MOD_INFO_S;
/**
 * @ingroup  SRE_mmu
 * @brief �ڴ��������á�
 *
 * @par ����:
 * ���������ַuwVirtAddr������uwLen���ڴ�����ΪuwState��
 *
 * @attention
 * <ul>
 * <li>�ò�������Cortex-AXƽ̨��֧�֡�</li>
 * <li>ֻ����MMUģ���ʼ����ɺ���á�</li>
 * <li>����������0�ŷ����ڴ����ԡ�</li>
 * <li>uwLenΪ0ʱ�������ڴ��������á�</li>
 * <li>�ڴ���������ʱ����uwVirtAddr��ʼ��section��page����������á�ĳһҳ�ڴ��������ò��ɹ�ʱ���Ѿ����óɹ��ı����������ԡ�</li>
 * </ul>
 *
 * @param  uwVirtAddr  [IN] ����#UINT32�������ַ��ʼ��ַ��
 * @param  uwLen       [IN] ����#UINT32�������ڴ����Գ��ȡ�
 * @param  uwStateMask [IN] ����#UINT32���ڴ��������룬����ƽ̨�����ã���ǰΪ��Ч�������ɺ��ԡ�
 * @param  uwState     [IN] ����#UINT32���ڴ����ԡ�
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201��������������ַ�������ַ�򳤶ȷ�page���롣
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED        0x02001210�����������ַδӳ�����
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209����ַ�����
 * @retval #OS_ERRNO_MMU_DEOPTIMIZE_FAIL        0x02001211��ҳ����ʱ�ڴ治�㡣
 * @retval #OS_ERRNO_MMU_ATTRIBUTE_ERR          0x02001217�����uwState��ATTRIBUTE�������ò���ȷ��
 * @retval #OS_ERRNO_MMU_ACCESS_ERR             0x02001218�����uwState��ACCESS�������ò���ȷ��
 * @retval #SRE_OK                              0x00000000���ڴ��������óɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_MmuStateSet(UINT32 uwVirtAddr, UINT32 uwLen, UINT32 uwStateMask, UINT32 uwState);

/**
 * @ingroup  SRE_mmu
 * @brief ʹ��MMU��
 *
 * @par ����:
 * ʹ��MMU��
 *
 * @attention
 * <ul>
 * <li>�ò�������Cortex-AXƽ̨��֧�֡�</li>
 * <li>ֻ����MMUģ���ʼ����ɺ���á�</li>
 * <li>�����ڵ͹���ʱʹ�ô˽ӿڡ�</li>
 * </ul>
 *
 * @param ��
 *
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED        0x02001210�������ַδӳ�䡣
 * @retval #SRE_OK                              0x00000000��MMUʹ�ܳɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MmuDisable
 */
extern UINT32 SRE_MmuEnable(VOID);

/**
 * @ingroup  SRE_mmu
 * @brief ����MMU��
 *
 * @par ����:
 * ����MMU��
 *
 * @attention
 * <ul>
 * <li>�ò�������Cortex-AXƽ̨��֧�֡�</li>
 * <li>ֻ����MMUģ���ʼ����ɺ���á�</li>
 * <li>�����ڵ͹���ʱʹ�ô˽ӿڡ�</li>
 * </ul>
 *
 * @param ��
 *
 * @retval #SRE_OK                              0x00000000��MMU���ܳɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MmuEnable
 */
extern UINT32 SRE_MmuDisable(VOID);

/**
 * @ingroup  SRE_mmu
 * @brief ҳ��ϲ���
 *
 * @par ����:
 * �ϲ�uwVirtAddr��ʼ������ΪuwLen���ڴ�ռ�ҳ��
 *
 * @attention
 * <ul>
 * <li>�ò�������Cortex-AXƽ̨��֧�֡�</li>
 * <li>ֻ����MMUģ���ʼ����ɺ���á�</li>
 * <li>�ýӿڱ�����ε�ַ�ռ䣬�������ַ�������ڴ�����һ�µ��ڴ���кϲ���</li>
 * </ul>
 *
 * @param  uwVirtAddr  [IN] ����#UINT32���ϲ���ʼ��ַ��
 * @param  uwLen       [IN] ����#UINT32���ϲ����ȡ�
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201����ʼ��ַ�򳤶ȷ�page���롣
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209����ַ�����
 * @retval #OS_ERRNO_MMU_OPTIMIZE_NO_NEED       0x02001212�����Ȳ���ϲ�Ϊ��ҳ��
 * @retval #SRE_OK                              0x00000000���ϲ��ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see NA
 */
extern UINT32 SRE_MmuOptimize(UINT32 uwVirtAddr, UINT32 uwLen);


/************************************************HIDSP interface*************************************************/
#elif(OS_HARDWARE_PLATFORM == OS_HIDSP)
/************************* Permission ����(���º�ֻ��ѡ��һ��) *********************/
/**
 * @ingroup SRE_mmu
 * MMU�ڴ�permission����-�ɶ���
 */
#define OS_MMU_STATE_READ                                      0x4

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�permission����-��д��
 */
#define OS_MMU_STATE_WRITE                                     0x2

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�permission����-��ִ�С�
 */
#define OS_MMU_STATE_EXE                                       0x1

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�permission����-���ɶ�������д������ִ�С�
 */
#define OS_MMU_STATE_NO_WRITE_READ_EXE                         0x0

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�permission����-�ɶ���ִ�С�
 */
#define OS_MMU_STATE_READ_EXE                                  (OS_MMU_STATE_READ | OS_MMU_STATE_EXE)

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�permission����-�ɶ���д��
 */
#define OS_MMU_STATE_READ_WRITE                                (OS_MMU_STATE_READ | OS_MMU_STATE_WRITE)

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�permission����-��д��ִ�С�
 */
#define OS_MMU_STATE_WRITE_EXE                                  (OS_MMU_STATE_WRITE | OS_MMU_STATE_EXE)

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�permission����-�ɶ���дִ�С�
 */
#define OS_MMU_STATE_READ_WRITE_EXE                            (OS_MMU_STATE_READ | OS_MMU_STATE_WRITE | OS_MMU_STATE_EXE)


/**************************** Share����(���º�ֻ��ѡ��һ��) *********************/
/**
 * @ingroup SRE_mmu
 * MMU�ڴ湲������-�ɹ���
 */
#define OS_MMU_STATE_SHARED                                    0x1

/**
 * @ingroup SRE_mmu
 * MMU�ڴ湲������-���ɹ���
 */
#define OS_MMU_STATE_NOT_SHARED                                0x0

/*************************** Speculative ���� (���º�ֻ��ѡ��һ��)***************/
/**
 * @ingroup SRE_mmu
 * MMU�ڴ�Ͷ������-��Ͷ����
 */
#define OS_MMU_STATE_SPEC                                      0x1

/**
 * @ingroup SRE_mmu
 * MMU�ڴ湲������-����Ͷ����
 */
#define OS_MMU_STATE_NOT_SPEC                                  0x0


/***************************** Cache   ���� (���º�ֻ��ѡ��һ��)**************/
/**
 * @ingroup SRE_mmu
 * MMU�ڴ�cache����-����cache����buffer��
 */
#define OS_MMU_STATE_NONCACHE_NONBUFFER                        0x0

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�cache����-����cache��buffer��
 */
#define OS_MMU_STATE_NONCACHE_BUFFERABLE                       0x1

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�cache����-DTLB: writeback,no allocate��
 */
#define OS_MMU_STATE_WRITEBACK_NOALLOC                         0x3

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�cache����-DTLB: writeback, writeallocate��
 */
#define OS_MMU_STATE_WRITEBACK_ALLOC                           0x7

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�cache����-DTLB:writethrough��
 */
#define OS_MMU_STATE_WRITETHROUGH                              0x2

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�cache����-ITLB:Cacheable, Read Allocate for write through cache��
 */
#define OS_MMU_STATE_READ_ALLOC_FOR_WRITETHROUGH               0x2

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�cache����-ITLB: cacheable, read allocate��
 */
#define OS_MMU_STATE_READ_ALLOC                                0x3

/**
 * @ingroup SRE_mmu
 * MMU�ڴ�������װ��(��8bit)��
 */
#define OS_MMU_ATTR(CacheAttr, Speculative, Share, permission) (((CacheAttr) << 5) | ((Speculative) << 4) | ((Share) << 3) | (permission))

/**
 * @ingroup SRE_mmu
 * TLB��Ч����ʱָ������Ч��ʽ:ҳ��Ч��context��Ч����ЧALL.
 *
 * TLB��Ч��ʽ��
 */
typedef enum
{
    NON_INV     = 0,              /**< none opreation     */
    PAGE_INV    = 1,              /**< page invalidate    */
    CONTEXT_INV = 2,              /**< context invalidate */
    ALL_INV     = 3,              /**< all invalidate     */
    RESERVED    = 4
}OS_TLB_INV_POLICY;

/**
 * @ingroup SRE_mmu
 * TLB����������:ITLB��DTLB.
 *
 * TLB���͡�
 */
typedef enum
{
    ITLB,            /**< ITLB*/
    DTLB             /**< DTLB*/
}OS_TLB_TYPE;

/**
 * @ingroup SRE_mmu
 * MMU�������ڴ���������.
 *
 * TLB���͡�
 */
typedef enum
{
    OS_MMU_PERMISSION,       /**<Permission: W(��д), R(�ɶ�), E(��ִ��)��������*/
    OS_MMU_SHARED,           /**<Shared: �ڴ湲����������*/
    OS_MMU_SPEC,             /**<Destructive: �ڴ�Ͷ����������*/
    OS_MMU_CACHE,            /**<Cache: �ڴ�cache��������*/
    OS_MMU_BUTT              /**<��ЧMMU�ڴ���������*/
}OS_MMU_ATTR_TYPE;

/**
 * @ingroup SRE_mmu
 * MMUģ��������Ϣ�Ľṹ�嶨�塣
 *
 * ����MMUģ�����������Ϣ��
 */
typedef struct tagMmuModInfo
{
    UINT32 uwMmuPhyToVirAddr;                                   /**< MMU��ʼ���ṹ�������׵�ַ   */
    UINT32 uwMmuPhyToVirSize ;                                  /**< MMU��ʼ���ṹ�������С     */
} MMU_MOD_INFO_S;



/**
 * @ingroup  SRE_mmu
 * @brief ���չ̶���Сӳ�������ַ�������ַ��
 *
 * @par ����:
 * ���ݴ������pVStart��pPStart��uwLen�������⡢�����ַӳ�䣬������uwAttr�����ڴ����ԡ�
 *
 * @attention
 * <ul>
 * <li>uwLenΪ0ʱ�����е�ַӳ�䣬ֱ�ӷ��سɹ���</li>
 * <li>SD6183ƽ̨��ַӳ��ʱ������ӳ��ɴ�ҳ��</li>
 * <li>SD6183ƽ̨MMUȥӳ�估ӳ����ڴ�����cacheһ�������û���֤��</li>
 * <li>SD6183ƽ̨MMU���õ���ʵ��ַ�������DDR�ռ䣬��Ҫ����1M���룬��������8K���룬���ݶ�4K����</li>
 * </ul>
 *
 * @param  pVStart       [IN] ����#MMU_VA_T��ӳ�������ַ��ʼ��ַ��
 * @param  pPStart       [IN] ����#MMU_PA_T��ӳ�������ַ��ʼ��ַ��
 * @param  uwLen         [IN] ����#UINT32��ӳ����ڴ��С��
 * @param  uwAttr        [IN] ����#UINT32���ڴ����ԣ�SD6183ƽ̨uwAttr��ЧbitλΪ(bit7-0)��bit2-0:read,write,execute; bit3:shareable; bit4:speculative; bit7-5:cache attributes;
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201��������������ַ�������ַ�򳤶ȷ�page���롣
 * @retval #OS_ERRNO_MMU_NO_LEVEL1_MEMORY       0x02001203��δ���뵽һ��ҳ���ڴ档
 * @retval #OS_ERRNO_MMU_ADDR_MAPPED            0x02001204�����������ַ�Ѿ�ӳ�����
 * @retval #OS_ERRNO_MMU_NO_LEVEL2_MEMORY       0x02001205��δ���뵽����ҳ���ڴ档
 * @retval #OS_ERRNO_MMU_NO_MAP_INFO_MEMORY     0x02001206��δ���뵽ҳ��ӳ����Ϣ�ڴ档
 * @retval #OS_ERRNO_MEM_FREE_SH_DAMAGED        0x02000311���ڴ��ͷ�ʱҪ�ͷŵ��ڴ���ͷ���ƻ��������ͷš�
 * @retval #OS_ERRNO_MMU_ATTRIBUTE_ERR          0x02001217�����uwState��ATTRIBUTE�������ò���ȷ��
 * @retval #OS_ERRNO_MMU_ACCESS_ERR             0x02001218�����uwState��ACCESS�������ò���ȷ��
 * @retval #OS_ERRNO_MMU_PA_VA_MEM_ALLOC_FAIL   0x0200123f���µ�ʵ��ӳ��ڵ������ڴ�ʧ�ܡ�
 * @retval #OS_ERRNO_MMU_PAGEMAP_STATE_INVALID  0x02001224�����õ��ڴ����ԷǷ���
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209��ӳ���ڴ��ַ���������
 * @retval #OS_ERRNO_MMU_MSG_NODE_ALLOC_FAILED  0x0200124e��MMU��Ϣ����ʱ��������Ϣ�ڵ�ʧ�ܡ�
 * @retval #OS_ERRNO_MMU_NOT_CORRECT_ALIGNED    0x0200124d��ʹ�÷��Ż��ӿ�ӳ��MMUʱ�����뷽ʽ����ȷ��
 * @retval #SRE_OK                              0x00000000�����⡢�����ַӳ��ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see NA
 */
extern  UINT32 SRE_MmuAssignNoOpt(MMU_VA_T pVStart, MMU_PA_T pPStart,
                                  UINT32 uwLen, UINT32 uwAttr);

/**
 * @ingroup  SRE_mmu
 * @brief �õ�ҳ����������ַ�ռ䡣
 *
 * @par ����:
 * ���ݴ������pVStart��uwLen�������ҳ����������ַ�ͳ��ȡ�
 *
 * @attention
 * <ul>
 * <li>uwLenΪ0ʱ�ݴ��������û��������ʼ��ַppVStartOut�ʹ�СpuwLenOut��</li>
 * </ul>
 *
 * @param  pVStart       [IN] ����#MMU_VA_T��ȥӳ�������ַ��ʼ��ַ��
 * @param  uwLen         [IN] ����#UINT32��ȥӳ����ڴ��С��
 * @param  ppVStartOut   [OUT] ����#MMU_VA_T*������ҳ������ȥӳ�������ַ��ʼ��ַ��
 * @param  puwLenOut     [OUT] ����#UINT32*������ҳ������ȥӳ����ڴ��С��
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201��������������ַ�������ַ�򳤶ȷ�page���롣
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209��(ȥ)ӳ���ڴ��ַ���������
 * @retval #SRE_OK                              0x00000000�����⡢�����ַӳ��ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuUnMap
 */
extern UINT32 SRE_MmuPageSpaceGet(MMU_VA_T pVStart, UINT32 uwLen, MMU_VA_T * ppVStartOut, UINT32 * puwLenOut);

/**
 * @ingroup  SRE_mmu
 * @brief ȥӳ���Ѿ����úõ������ַ��
 *
 * @par ����:
 * ���ݴ������pVStart��uwLen����MMU����ҳ���ȥӳ�䡣
 *
 * @attention
 * <ul>
 * <li>uwLenΪ0ʱ������ҳ����������ݴ������</li>
 * <li>pVStart��uwLen������SRE_MmuAlignSpace�����ĵ�ַ��</li>
 * <li>MMUȥӳ�估ӳ����ڴ�����cacheһ�������û���֤��</li>
 * <li>�ò�������SD6183ƽ̨��֧�֡�</li>
 * </ul>
 *
 * @param  pVStart       [IN] ����#MMU_VA_T��ӳ�������ַ��ʼ��ַ��
 * @param  uwLen         [IN] ����#UINT32��ӳ����ڴ��С��
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED       0x02001201��������������ַ�������ַ�򳤶ȷ�page���롣
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209��(ȥ)ӳ���ڴ��ַ���������
 * @retval #OS_ERRNO_MMU_PAGE_NOT_ALIGNED       0x0200123b��MMUҳ��ȥӳ��ʱ������Ĳ���δ�������õ�ҳ���С���롣
 * @retval #OS_ERRNO_MMU_MSG_NODE_ALLOC_FAILED  0x0200124e��MMU��Ϣ����ʱ��������Ϣ�ڵ�ʧ�ܡ�
 * @retval #SRE_OK                              0x00000000�����⡢�����ַӳ��ɹ���

 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuAlignSpace
 */
extern UINT32 SRE_MmuUnAssign(MMU_VA_T pVStart, UINT32 uwLen);

/**
 * @ingroup  SRE_mmu
 * @brief ��ЧTLB��
 *
 * @par ����:
 * ��Ч TLB��
 *
 * @attention
 * <ul>
 * <li>��ΪӲ�����ԣ�TLB��Ч��ʱ�򣬻���Ѿ�������TLB��Ч���ҽ�������Ҫ�û�����������</li>
 * </ul>
 *
 * @param  enTlbType    [IN] ����#OS_TLB_TYPE��ITLB����DTLB
 * @param  enInvPolicy  [IN] ����#OS_TLB_INV_POLICY��page inv,context inv,all inv
 * @param  pVirAddr     [IN] ����#MMU_VA_T�������ַ,���page inv��ʽ��Ч
 * @param  uwContextID  [IN] ����#UINT32��context ID�����page inv��context inv��Ч
 *
 * @retval #OS_ERRNO_MMU_TLB_INV_POLICY_INVALID             0x0200121f��TLB ��Ч���ԷǷ���
 * @retval #OS_ERRNO_MMU_TLB_INV_CONTEXT_ID_INVALID         0x0200123a����ЧTLB�����ContextID�Ƿ���
 * @retval #OS_ERRNO_MMU_TLB_TYPE_INVALID                   0x0200121e��TLB���ʹ���
 * @retval #OS_ERRNO_MMU_PA_VA_MEM_ALLOC_FAIL               0x0200123f����ֲ����µ�ʵ��ӳ��ڵ������ڴ�ʧ�ܡ�
 * @retval #SRE_OK                                          0x00000000���ɹ���
 * @retval SRE_OK �ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuL2TlbOrdSet
 */
extern UINT32 SRE_MmuTlbInv(OS_TLB_TYPE enTlbType , OS_TLB_INV_POLICY enInvPolicy,
                           MMU_VA_T pVirAddr, UINT32 uwContextID);

/**
 * @ingroup  SRE_mmu

 * @brief ����L2 TLB���ҵ�˳��
 *
 * @par ����:
 * ����L2 TLB���ҵ�˳��
 *
 * @attention
 * <ul>
 * <li>����Ҫ�ڴӺ�����֮ǰΪ�Լ���������˳�򣬷���������쳣��</li>
 * <li>�����ڴӺ�����ǰΪ�Ӻ���������˳�򣬷�����ܲ����쳣��</li>
 * <li>uwOrdValue��ʾ8��ҳ��Ĳ���˳��ÿ4bit��ʾһ�����ͣ���4bit�н���3bit��Ч��</li>
 * <li>8��������˳���ж�Ҫ���ҽ�һ�Ρ�</li>
 * <li>ҳ������0:4K 1:8K 2:16K 3:64K 4:256K 5:1M 6:4M 7:16M</li>
 * <li>��uwOrdValue=0x76543210����ʾ��4K��8K��16K��64K��256K��1M��4M��16M˳����ҡ�</li>
 * <li>Ӳ��Ĭ�ϵ�����˳����0x76543210��</li>
 * </ul>
 *
 * @param  uwCoreID             [IN] ����#UINT32���˺ŷ�Χ[0,33]��
 * @param  uwOrdValue           [IN] ����#UINT32��L2ҳ��Ĳ���˳��
 *
 * @retval #OS_ERRNO_MMU_L2TLB_ORDER_ERR    0x02001236��L2 TLB����˳�����
 * @retval #OS_ERRNO_MMU_COREID_ERR         0x02001237���˺Ŵ���
 * @retval #SRE_OK                          0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuTlbInv
 */
extern UINT32 SRE_MmuL2TlbOrdSet(UINT32 uwCoreID ,UINT32 uwOrdValue);


/**
 * @ingroup  SRE_mmu

 * @brief ��ѯMMUҳ������ֵ��
 *
 * @par ����:
 * ��ѯ��ǰ�ڴ��MMUҳ������ֵ��
 *
 * @attention
 * <ul>
 * <li>��֤��ѯ�ĵ�ַ�Ѿ�����MMUӳ�䡣</li>
 * </ul>
 *
 * @param  pVirAddr     [IN] ����#MMU_VA_T�������ַ��
 * @param  puwMemAttr   [OUT]����#UINT32 *��ʵ�������MMUҳ������ֵ��
 *
 * @retval #OS_ERRNO_MMU_ATTR_OUTPUT_POINT_NULL 0x0200123c����ȡMMU�ڴ�����ʱ�����ָ�����Ϊ�ա�
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED        0x02001210�������ַδӳ�䡣
 * @retval #SRE_OK                              0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuTlbInv
 */
extern UINT32 SRE_MmuMemAttrGet(MMU_VA_T pVirAddr, UINT32 *puwMemAttr);

/**
 * @ingroup  SRE_mmu

 * @brief ����ָ���ε�MMUҳ������
 *
 * @par ����:
 * ����ָ���ε�MMUҳ�����ԡ�
 *
 * @attention
 * <ul>
 * <li>��֤��ѯ�ĵ�ַ�Ѿ�����MMUӳ�䡣</li>
 * <li>�Ĵ����ռ�[0x10000000,0x1fffffff]��[0x90000000,0x9fffffff]��ҳ�����Բ������޸ġ�</li>
 * </ul>
 *
 * @param  pVirAddr     [IN] ����#MMU_VA_T�������ַ��
 * @param  uwSize       [IN] ����#UINT32�������ַ���ȡ�
 * @param  uwMemAttr    [IN] ����#UINT32�����õ��ڴ�����ֵ��
 *
 * @retval #OS_ERRNO_MMU_NOT_PAGE_ALIGNED                 0x02001201�������ַ�򳤶ȷ�page���롣
 * @retval #OS_ERRNO_MMU_PAGEMAP_STATE_INVALID            0x02001224�����õ��ڴ����ԷǷ���
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW                    0x02001209���ڴ��ַ���������
 * @retval #OS_ERRNO_MMU_PAGE_NOT_ALIGNED                 0x0200123b��MMUҳ��ȥӳ��(��������)ʱ������Ĳ���δ�������õ�ҳ���С���롣
 * @retval #OS_ERRNO_MMU_ADDR_NOT_MAPPED                  0x02001210�������ַδӳ�䡣
 * @retval #OS_ERRNO_MMU_SETATTR_PROTECT_REGION_COVERRED  0x02001250��MMU�޸�����ʱ�ڴ�ΰ������ܱ����ļĴ����ռ䡣
 * @retval #OS_ERRNO_MMU_MSG_NODE_ALLOC_FAILED            0x0200124e��MMU��Ϣ����ʱ��������Ϣ�ڵ�ʧ�ܡ�
 * @retval #OS_ERRNO_MMU_REG_REGION_PROTECT               0x0200124f��MMU�޸�����ʱ�������޸ļĴ����ռ����ԡ�
 * @retval #SRE_OK                                        0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see SRE_MmuTlbInv
 */
extern UINT32 SRE_MmuMemAttrSet(MMU_VA_T pVirAddr, UINT32 uwSize, UINT32 uwMemAttr);

/**
 * @ingroup  SRE_mmu
 * @brief TlbԤȡ
 *
 * @par ����:
 * ͨ�������ַ��MMUҳ�����Ԥȡ��L2 TLB,����ض�ҳ�����Ѿ���L2 TLB�У�����Ԥȡ�������á�
 *
 * @attention
 * <ul>
 * <li>�����ظ�Ԥȡ���ڶ����൱����Ч������</li>
 * </ul>
 *
 * @param  pVirAddr           [IN] ����#MMU_VA_T�������ַ
 *
 * @retval #SRE_OK  �ɹ�
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuTlbLock
 */
OS_SEC_ALW_INLINE INLINE  UINT32 SRE_MmuTlbPreload(MMU_VA_T pVirAddr)
{
    __asm__ __volatile__("mmupf %0 " :: "r"((UINT32)pVirAddr));
    return SRE_OK;
}

/**
 * @ingroup  SRE_mmu
 * @brief TlbԤȡ������
 *
 * @par ����:
 * ͨ�������ַ��MMUҳ�����Ԥȡ��L2 TLB������,����ض�ҳ�����Ѿ���L2 TLB���Ҽ���������Ԥȡ�����������á�
 *
 * @attention
 * <ul>
 * <li>�����ظ��������ڶ����൱����Ч������</li>
 * </ul>
 *
 * @param  pVirAddr           [IN] ����#MMU_VA_T�������ַ
 *
 * @retval #SRE_OK  �ɹ�
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuTlbPreload
 */
OS_SEC_ALW_INLINE INLINE UINT32 SRE_MmuTlbLock(MMU_VA_T pVirAddr)
{
    __asm__ __volatile__("mmupflck %0 "  :: "r"((UINT32)pVirAddr));
    return SRE_OK;
}

/**
 * @ingroup  SRE_mmu
 * @brief Tlb����
 *
 * @par ����:
 * ͨ�������ַ�Ѱ�����L2 Tlb�е�ҳ��������������Ӧ��ҳ�����L2 Tlb�У����ν����������á�
 *
 * @attention
 * <ul>
 * <li>�����ظ��������ڶ����൱����Ч������</li>
 * </ul>
 *
 * @param  pVirAddr           [IN] ����#MMU_VA_T�������ַ
 *
 * @retval #SRE_OK  �ɹ�
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MmuTlbPreload
 */
OS_SEC_ALW_INLINE INLINE UINT32 SRE_MmuTlbUnlock(MMU_VA_T pVirAddr)
{
    __asm__ __volatile__("mmuulck %0 "  :: "r"((UINT32)pVirAddr));
    return SRE_OK;
}

#if (OS_OPTION_BM_SRE == NO)
/**
 * @ingroup  SRE_mng
 * @brief ӳ�������ַ�������ַ��
 *
 * @par ����:
 * ���ݴ������pVStart��pPStart��uwLen�������⡢�����ַӳ�䣬������uwAttr�����ڴ����ԡ�
 * �ýӿڽ�֧�����غ˸����˻����Ǹ�ָ���Ӻ˽���MMUӳ��
 * @attention
 * <ul>
 * <li>uwLenΪ0ʱ�����е�ַӳ�䣬ֱ�ӷ��سɹ���</li>
 * <li>SD6183ƽ̨��ַӳ��ʱ������ӳ��ɴ�ҳ��</li>
 * <li>SD6183ƽ̨MMUȥӳ�估ӳ����ڴ�����cacheһ�������û���֤��</li>
 * <li>SD6183ƽ̨MMU���õ���ʵ��ַ�����ȶ����밴��4K���룬����ǿ�ִ�еĴ���Σ����밴��8K����</li>
 * <li>��֧�����غ˵���</li>
 * </ul>
 *
 * @param  uwInstID       [IN] ����#UINT32��ʵ��ID��
 * @param  uwCoreID       [IN] ����#UINT32��Ӳ�߳�ID��
 * @param  pVStart        [IN] ����#MMU_VA_T��ӳ�������ַ��ʼ��ַ��
 * @param  pPStart        [IN] ����#MMU_PA_T��ӳ�������ַ��ʼ��ַ��
 * @param  uwLen          [IN] ����#UINT32��ӳ����ڴ��С��
 * @param  uwAttr         [IN] ����#UINT32���ڴ����ԣ�SD6183ƽ̨uwAttr��ЧbitλΪ(bit7-0)��bit2-0:read,write,execute; bit3:shareable; bit4:speculative; bit7-5:cache attributes;
 *
 * @retval #OS_ERRNO_MMU_INST_ID_TOO_MAX        0x02001246��ʵ��ID�������ֵ��
 * @retval #OS_ERRNO_MMU_CORE_ID_TOO_MAX        0x02001247��Ӳ���߳�ID�������ֵ
 * @retval #OS_ERRNO_MMU_INST_NOT_READY         0x02001248��ʵ��δ׼����
 * @retval #OS_ERRNO_MMU_COREID_NOT_EXIST       0x02001249��coreID����
 * @retval #OS_ERRNO_MMU_NO_LEVEL1_MEMORY       0x02001203��δ���뵽һ��ҳ���ڴ档
 * @retval #OS_ERRNO_MMU_ADDR_MAPPED            0x02001204�����������ַ�Ѿ�ӳ�����
 * @retval #OS_ERRNO_MMU_NO_LEVEL2_MEMORY       0x02001205��δ���뵽����ҳ���ڴ档
 * @retval #OS_ERRNO_MMU_NO_MAP_INFO_MEMORY     0x02001206��δ���뵽ҳ��ӳ����Ϣ�ڴ档
 * @retval #OS_ERRNO_MMU_ADDR_OVERFLOW          0x02001209����ַ�����
 * @retval #OS_ERRNO_MMU_ATTRIBUTE_ERR          0x02001217�����uwState��ATTRIBUTE�������ò���ȷ��
 * @retval #OS_ERRNO_MMU_ACCESS_ERR             0x02001218�����uwState��ACCESS�������ò���ȷ��
 * @retval #OS_ERRNO_MMU_PA_VA_MEM_ALLOC_FAIL   0x0200123f���µ�ʵ��ӳ��ڵ������ڴ�ʧ�ܡ�
 * @retval #OS_ERRNO_MMU_MSG_UNINIT             0x02001244������ָ���˵�MMUʱ��δ���MMU��Ϣ���г�ʼ����
 * @retval #OS_ERRNO_MMU_MSG_SEND_FAIL          0x02001245������ָ���˵�MMUʱ����ָ���˷�����Ϣʧ�ܡ�
 * @retval #OS_ERRNO_MMU_INST_NOT_READY         0x02001248��ʵ��δ׼���á�
 * @retval #SRE_OK                              0x00000000�����⡢�����ַӳ��ɹ���
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see NA
 */
extern UINT32 SRE_MmuMcAssign(UINT32 uwInstID,UINT32 uwCoreID, MMU_VA_T pVStart, MMU_PA_T pPStart, UINT32 uwLen, UINT32 uwAttr);
#endif

#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_MMU_H */


