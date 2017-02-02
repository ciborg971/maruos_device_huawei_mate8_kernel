/**
 * @file sre_hw_mpu.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������SD6182 mpuģ���ⲿͷ�ļ��� \n
 */

/**
*@defgroup  SRE_hw_mpu MPU
*@ingroup SRE_inspect
*/


#ifndef _SRE_HW_MPU_H
#define _SRE_HW_MPU_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#if (OS_CPU_TYPE != OS_SD6183)
/**
 * @ingroup SRE_hw_mpu
 * ��ʾ���е�MPU��Ԫ��
 */
#define OS_MPU_ID_ALL                    0xFFFF

/**
 * @ingroup SRE_hw_mpu
 * ��ʾδ�����ַ��MPU�α�š�
 */
#define OS_MPU_UNSIGNED_RANGE_IDX        0xFFFF

/**
 * @ingroup SRE_hw_mpu
 * ��ʾʹ�ܣ����ڸ�ָ����MPU��Ԫ���öα�������ʱ��ָ���öα����Ƿ�ʹ�ܡ�
 */
#define OS_MPU_RANGE_ENABLE              1

/**
 * @ingroup SRE_hw_mpu
 * ��ʾȥʹ�ܣ����ڸ�ָ����MPU��Ԫ���öα�������ʱ��ָ���öα����Ƿ�ʹ�ܡ�
 */
#define OS_MPU_RANGE_DISABLE             0

/**
 * @ingroup SRE_hw_mpu
 * ��ʾ�ɶ���д����������ָ��Group���ָ��MPU�εĶ�д�������ԡ�
 */
#define OS_MPU_NO_PROTECTED              0

/**
 * @ingroup SRE_hw_mpu
 * ��ʾ�ɶ�����д����������ָ��Group���ָ��MPU�εĶ�д�������ԡ�
 */
#define OS_MPU_WRITE_PROTECTED           1

/**
 * @ingroup SRE_hw_mpu
 * ��ʾ���ɶ���д����������ָ��Group���ָ��MPU�εĶ�д�������ԡ�
 */
#define OS_MPU_READ_PROTECTED            2

/**
 * @ingroup SRE_hw_mpu
 * ��ʾ���ɶ�����д����������ָ��Group���ָ��MPU�εĶ�д�������ԡ�
 */
#define OS_MPU_ALL_PROTECTED             3

/**
 * @ingroup SRE_hw_mpu
 * ��ʾ��һ��Υ���ı���������Υ���˶�id�ı�����
 */
#define OS_MPU_OFFEND_READ_ID_PROTECTED  1

/**
 * @ingroup SRE_hw_mpu
 * ��ʾ��һ��Υ���ı���������Υ����дid�ı�����
 */
#define OS_MPU_OFFEND_WRITE_ID_PROTECTED 2

#if (OS_CPU_TYPE == OS_SD6182)

/**
 * @ingroup SRE_hw_mpu
 * SD6182 MPU���ö��ֵ
 */
typedef enum tagMpuNum
{
    OS_MPU_DSP_CLUST0_CORE0_LL2  = 0,    /**< DSP0 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST0_CORE1_LL2  = 1,    /**< DSP1 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST0_CORE2_LL2  = 2,    /**< DSP2 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST0_CORE3_LL2  = 3,    /**< DSP3 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST0_CORE4_LL2  = 4,    /**< DSP4 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST1_CORE0_LL2  = 5,    /**< DSP5 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST1_CORE1_LL2  = 6,    /**< DSP6 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST1_CORE2_LL2  = 7,    /**< DSP7 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST1_CORE3_LL2  = 8,    /**< DSP8 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST1_CORE4_LL2  = 9,    /**< DSP9 �˵�Local L2 MPU���               */
    OS_MPU_HACCC_CLUST_CORE0_LL2 = 10,   /**< HACCC0 �˵�Local L2 MPU���             */
    OS_MPU_HACCC_CLUST_CORE1_LL2 = 11,   /**< HACCC1 �˵�Local L2 MPU���             */
    OS_MPU_CPU_CLUST_CORE0_LL2   = 12,   /**< CPU0 �˵�Local L2 MPU���               */
    OS_MPU_CPU_CLUST_CORE1_LL2   = 13,   /**< CPU1 �˵�Local L2 MPU���               */
    OS_MPU_CPU_CLUST_CORE2_LL2   = 14,   /**< CPU2 �˵�Local L2 MPU���               */
    OS_MPU_CPU_CLUST_CORE3_LL2   = 15,   /**< CPU3 �˵�Local L2 MPU���               */
    OS_MPU_CPU_CLUST_CORE4_LL2   = 16,   /**< CPU4 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST0_L2M0       = 17,   /**< DSP Cluster0 �ĵ�0��Shared L2 MPU���   */
    OS_MPU_DSP_CLUST0_L2M1       = 18,   /**< DSP Cluster0 �ĵ�1��Shared L2 MPU���   */
    OS_MPU_DSP_CLUST0_L2M2       = 19,   /**< DSP Cluster0 �ĵ�2��Shared L2 MPU���   */
    OS_MPU_DSP_CLUST0_L2M3       = 20,   /**< DSP Cluster0 �ĵ�3��Shared L2 MPU���   */
    OS_MPU_DSP_CLUST0_L2M4       = 21,   /**< DSP Cluster0 �ĵ�4��Shared L2 MPU���   */
    OS_MPU_DSP_CLUST1_L2M0       = 22,   /**< DSP Cluster1 �ĵ�0��Shared L2 MPU���   */
    OS_MPU_DSP_CLUST1_L2M1       = 23,   /**< DSP Cluster1 �ĵ�1��Shared L2 MPU���   */
    OS_MPU_DSP_CLUST1_L2M2       = 24,   /**< DSP Cluster1 �ĵ�2��Shared L2 MPU���   */
    OS_MPU_DSP_CLUST1_L2M3       = 25,   /**< DSP Cluster1 �ĵ�3��Shared L2 MPU���   */
    OS_MPU_DSP_CLUST1_L2M4       = 26,   /**< DSP Cluster1 �ĵ�4��Shared L2 MPU���   */
    OS_MPU_HACCC_CLUST_L2M0      = 27,   /**< HACC Cluster �ĵ�0��Shared L2 MPU���   */
    OS_MPU_HACCC_CLUST_L2M1      = 28,   /**< HACC Cluster �ĵ�1��Shared L2 MPU���   */
    OS_MPU_HACCC_CLUST_L2M2      = 29,   /**< HACC Cluster �ĵ�2��Shared L2 MPU���   */
    OS_MPU_HACCC_CLUST_L2M3      = 30,   /**< HACC Cluster �ĵ�3��Shared L2 MPU���   */
    OS_MPU_CPU_CLUST_L2M0        = 31,   /**< CPU Cluster �ĵ�0��Shared L2 MPU���    */
    OS_MPU_CPU_CLUST_L2M1        = 32,   /**< CPU Cluster �ĵ�1��Shared L2 MPU���    */
    OS_MPU_CPU_CLUST_L2M2        = 33,   /**< CPU Cluster �ĵ�2��Shared L2 MPU���    */
    OS_MPU_L3_CMI0               = 34,   /**< L3M0 MPU���                            */
    OS_MPU_L3_CMI1               = 35,   /**< L3M1 MPU���                            */
    OS_MPU_DDR                   = 36,   /**< DDR MPU���                             */
    OS_MPU_HACCC_CLUST_LSIP      = 37,   /**< HACC Cluster Lsip MPU���               */
    OS_MPU_MAIN_CLUST_LSIP       = 38,   /**< Main Cluster Lsip MPU���               */
    OS_MPU_SRIO                  = 39    /**< sRIO Register MPU���                   */
}OS_MPU_ID_E;

#elif (OS_CPU_TYPE == OS_SD6157)

/**
 * @ingroup SRE_hw_mpu
 * SD6157 MPU���ö��ֵ
 */
typedef enum tagMpuNum
{
    OS_MPU_DSP_CLUST0_CORE0_LL2  = 0,    /**< DSP0 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST0_CORE1_LL2  = 1,    /**< DSP1 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST0_CORE2_LL2  = 2,    /**< DSP2 �˵�Local L2 MPU���               */
    OS_MPU_CPU_CLUST_CORE0_LL2   = 3,    /**< CPU0 �˵�Local L2 MPU���               */
    OS_MPU_DSP_CLUST0_L2M0       = 4,    /**< DSP Cluster0 �ĵ�0��Shared L2 MPU���   */
    OS_MPU_DSP_CLUST0_L2M1       = 5,    /**< DSP Cluster0 �ĵ�1��Shared L2 MPU���   */
    OS_MPU_DSP_CLUST0_L2M2       = 6,    /**< DSP Cluster0 �ĵ�2��Shared L2 MPU���   */
    OS_MPU_DSP_CLUST0_L2M3       = 7,    /**< DSP Cluster0 �ĵ�3��Shared L2 MPU���   */
    OS_MPU_CPU_CLUST_L2M0        = 8,    /**< CPU Cluster �ĵ�0��Shared L2 MPU���    */
    OS_MPU_DDR                   = 9,    /**< DDR MPU���                             */
    OS_MPU_MAIN_CLUST_LSIP       = 10    /**< Main Cluster Lsip MPU���               */
}OS_MPU_ID_E;

#endif

/**
 * @ingroup SRE_hw_mpu
 * MPU��������Ϣ�ṹ�嶨�塣
 *
 * ����ָ����MPU����ʱָ���Ĳ�����Ϣ��
 */
typedef struct tagMpuCfgInfo
{
    UINT16 usRangeId;     /**< ��ID����ͬ��MPU�����õĶ���Ŀ��һ����ȡֵ��ΧҲ��һ��(0 ~ N-1��NΪ������Ŀ)��OS_MPU_UNSIGNED_RANGE_IDX����δ����ĵ�ַ��*/
    UINT16 usEnable;      /**< �Ƿ�ʹ�ܣ�OS_MPU_RANGE_ENABLE��ʹ��MPU������OS_MPU_RANGE_DISABLE����ֹMPU���� */
    UINT32 uwStartAddr;   /**< �ε���ʼ��ַ����ͬMPU�в�ͬ�Ķ���Ҫ�� */
    UINT32 uwEndAddr;     /**< �εĽ�����ַ����ͬMPU�в�ͬ�Ķ���Ҫ��  */
    UINT32 uwWriteProt;   /**< д������ÿ��bit����һ��group��1--�������Ӧ��groupд��ε�ַ��0--�����Ӧ��groupд��ε�ַ */
    UINT32 uwReadProt;    /**< ��������ÿ��bit����һ��group��1--�������Ӧ��group����ε�ַ��0--�����Ӧ��group����ε�ַ */
}MPU_SLV_CFG_INFO_S;

/**
 * @ingroup SRE_hw_mpu
 * MPU�쳣ʱ����¼���쳣��Ϣ��
 *
 * MPU�쳣ʱ����¼���쳣��Ϣ�ṹ�塣
 */
typedef struct tagMpuExcInfo
{
     UINT32  uwFaultAddr;   /**< �쳣ʱ���ʵĵ�ַ                                 */
     UINT16  usTranId;      /**< ����ID����ǰ��Ч                                 */
     UINT8   ucGroupId;     /**< ������ʵ�master��Ӧ��Group ID                   */
     UINT8   ucFaultType;   /**< �쳣������: 01-Υ�������ʱ�����02-Υ��д���ʱ��� */
} MPU_EXC_INFO_S;


/**
 * @ingroup SRE_hw_mpu
 * ��ʾ�쳣��Ϣ��
 */
typedef VOID (*MPU_EXC_HOOK_FUNC) (UINT16 usMpuId, MPU_EXC_INFO_S *pstMpuExcInfo);

/*
 * MPUģ������붨�塣
 */

/**
 * @ingroup SRE_hw_mpu
 * MPU�����룺�����Group Id�Ƿ���
 *
 * ֵ: 0x02002101
 *
 * �������: ��ȷ��������ȷ��Group Id����ΧΪ[0,31]��
 */
#define OS_ERRNO_MPU_GROUP_ID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x01)

/**
 * @ingroup SRE_hw_mpu
 * MPU�����룺�����MPU Id�Ƿ���
 *
 * ֵ: 0x02002102
 *
 * �������: ��ȷ��������ȷ��MPU Id����ΧΪSD6182:[0,39],SD6157:[0,10]��
 */
#define OS_ERRNO_MPU_ID_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x02)

/**
 * @ingroup SRE_hw_mpu
 * MPU�����룺�û�Ϊָ����MPU��Ԫ���ñ�������ʱ������Ķθ����Ƿ�
 *
 * ֵ: 0x02002103
 *
 * �������: ��ȷ������Ķθ����Ϸ�(��Ϊ0�Ҳ�����ָ��MPU��ԪӲ��֧�ֵ����ɻ��ֵ�MPU����(����δ���ֵĶ�)������DDRΪ33��sRIOΪ2������Ϊ5)��
 */
#define OS_ERRNO_MPU_RANGE_NUM_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x03)

/**
 * @ingroup SRE_hw_mpu
 * MPU�����룺�û�����Ķ�Id�Ƿ�
 *
 * ֵ: 0x02002104
 *
 * �������: ��ȷ������Ķθ����Ϸ�(Ϊ#OS_MPU_ID_ALL�򲻳���ָ��MPU��Ԫ֧�ֵ������(����DDRΪ31��sRIOΪ0������Ϊ3))��
 */
#define OS_ERRNO_MPU_RANGE_ID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x04)

/**
 * @ingroup SRE_hw_mpu
 * MPU�����룺�û�Ϊָ����MPU��Ԫ���ñ�������ʱ������Ķ�������Ϣ�������׵�ַΪNULL
 *
 * ֵ: 0x02002105
 *
 * �������: ��ȷ��������Ч�Ļ�������ַ
 */
#define OS_ERRNO_MPU_RANGE_BUFF_NULL                        SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x05)

/**
 * @ingroup SRE_hw_mpu
 * MPU�����룺�û�����ı���MPU���Եĵ�ַΪNULL
 *
 * ֵ: 0x02002106
 *
 * �������: ��ȷ������ı���MPU���Եĵ�ַ��NULL��
 */
#define OS_ERRNO_MPU_QUERY_PTR_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x06)

/**
 * @ingroup SRE_hw_mpu
 * MPU�����룺�û���ָ����MPU��Ԫ���öα�������ʱ��ָ���Ķ�ʹ��״̬�Ƿ�
 *
 * ֵ: 0x02002107
 *
 * �������: ��ȷ������Ķ�ʹ��״̬Ϊ#OS_MPU_RANGE_ENABLE��#OS_MPU_RANGE_DISABLE��
 */
#define OS_ERRNO_MPU_RANGE_ENA_STATUS_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x07)

/**
 * @ingroup SRE_hw_mpu
 * MPU�����룺ע��MPU�쳣���Ӻ���ʱ���Ѿ�ע�ᡣ
 *
 * ֵ: 0x02002108
 *
 * �������: ��ȷ��ע��MPU�쳣���Ӻ���ʱ���쳣���Ӻ���δ��ע�ᣬ��ǰ��֧��ע��һ��MPU�쳣���Ӻ�����
 */
#define OS_ERRNO_MPU_EXC_INFO_HOOK_IS_FULL                  SRE_ERRNO_OS_ERROR(OS_MID_MPU, 0x08)

/**
 * @ingroup  SRE_hw_mpu
 * @brief ��ָ����MPU��Ԫ���ñ������ԡ�
 *
 * @par ����:
 * ��usMpuIdָ����MPU��Ԫ���ñ������ԣ�MPU����Ϣ��������ַΪpastRangeInfo�����õĶθ���ΪusRangeNum��
 *
 * @attention
 * <ul>
 * <li>�ò�����֧��SD6182��SD6157ƽ̨��</li>
 * <li>�ò�����֧��ESLƽ̨��</li>
 * <li>�û����øýӿ�ʱ����Ҫ��֤��Ӧ��MPU��Դ�ɱ�����ʹ��(δ���ض�)������ᵼ�º˹�����</li>
 * <li>�ò��������ø���MPU�����Ե�ͬʱ��򿪸�MPU��Ԫ��ȫ��MPUʹ�ܿ��أ��������ö�ʹ�ܣ�����иò������MPU�α����ͻ���Ч��</li>
 * <li>����#SRE_MpuDisable��#SRE_MpuRestore�Լ��ýӿڶ������MPUʹ�ܿ��أ����Բ�������#SRE_MpuDisable��#SRE_MpuRestore֮����øýӿڣ�������ܻ����ʹ��״̬���ҡ�</li>
 * <li>MPU�������ܲ�����Global/Local��Cacheable/Uncacheable���ʣ�����������ʵ�ʵ�����ռ䣬�Ը��ֲ�ͬ���߼���ַ���ʾ�������������</li>
 * <li>Ӳ������ݸ���MPU��Ԫ�ı��������Զ������û����õĶ���ʼ��ַ�Ͷν�����ַ����Ӧ��λ(��������Ϊ4Kʱ�����Ե�12bit����������Ϊ1Mʱ�����Ե�20bit)��Ȼ���û��������ʼ��ַ
       ��Ӧ��λ��0����ɱ�������ʼ��ַ�����û�����Ľ�����ַ��Ӧ��λ��1����ɱ����Ľ�����ַ��</li>
 * <li>����#OS_MPU_HACCC_CLUST_LSIP��#OS_MPU_MAIN_CLUST_LSIP������MPU��Ԫ��Ӳ����Ƶ�Ŀ��ֻ���ڱ���HACCC�Ĵ��������û����ó�������ַ�Σ����ܻ�����Ӳ���߼�����</li>
 * <li>�������usRangeIdΪ#OS_MPU_UNSIGNED_RANGE_IDXʱ����ʾ�Ը�MPU��δ���ֵ�ַ��(����MPU���б��������г����ѻ��ֶ�����������е�ַ�ռ�)���ж��������ã����Ҹ�MPU���÷�Χ���û���֤��</li>
 * </ul>
 * @param  usMpuId       [IN] ����Ϊ#UINT16��MPU ID�ţ�ȡֵ��ΧΪSD6182:[0,39],SD6157:[0,10]��
 * @param  usRangeNum    [IN] ����Ϊ#UINT16��MPU����Ϣ��������Ԫ����������DDR��SRIO MPU��ȡֵ��Χ�ֱ�Ϊ(0,33]��(0,2],��������MPU��ȡֵ��ΧΪ(0,5]��
 * @param  pastRangeInfo [IN] ����Ϊ#MPU_SLV_CFG_INFO_S��MPU����Ϣ�������׵�ַ��
 *
 * @retval #OS_ERRNO_MPU_ID_INVALID                 0x02002102�������MPU Id�Ƿ���
 * @retval #OS_ERRNO_MPU_RANGE_NUM_INVALID          0x02002103���û�Ϊָ����MPU��Ԫ���ñ�������ʱ������Ķθ����Ƿ���
 * @retval #OS_ERRNO_MPU_RANGE_ID_INVALID           0x02002104���û�����Ķ�Id�Ƿ���
 * @retval #OS_ERRNO_MPU_RANGE_BUFF_NULL            0x02002105���û�Ϊָ����MPU��Ԫ���ñ�������ʱ������Ķ�������Ϣ�������׵�ַΪNULL��
 * @retval #OS_ERRNO_MPU_RANGE_ENA_STATUS_INVALID   0x02002107, �û���ָ����MPU��Ԫ���öα�������ʱ��ָ���Ķ�ʹ��״̬�Ƿ���
 * @retval #SRE_OK                                  0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_hw_mpu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MpuDisable | SRE_MpuRestore
 */
extern UINT32 SRE_MpuCfg(UINT16 usMpuId,UINT16 usRangeNum, const MPU_SLV_CFG_INFO_S *pastRangeInfo);

/**
 * @ingroup  SRE_hw_mpu
 * @brief ����ָ����Group���ָ����MPU�εĶ�д���ԡ�
 *
 * @par ����:
 * ����ָ��Group�����usMpuId��usRangeIdָ����MPU�εĶ�д���ԡ�
 *
 * @attention
 * <ul>
 * <li>�ò�����֧��SD6182��SD6157ƽ̨��</li>
 * <li>�ò�����֧��ESLƽ̨��</li>
 * <li>�û����øýӿ�ʱ����Ҫ��֤��Ӧ��MPU��Դ�ɱ�����ʹ��(δ���ض�)������ᵼ�º˹�����</li>
 * <li>�������usRangeIdΪOS_MPU_UNSIGNED_RANGE_IDX����ʾ���õ�δ�����ַ��MPU�ζ�д���ԡ�</li>
 * <li>��ָ����MPU��δ������SRE_MpuCfg�ӿ����ù��������õĶ�д���Բ���Ч��</li>
 * </ul>
 * @param  usGroupId     [IN] ����Ϊ#UINT16��Group ID�ţ���Χ[0,31]��
 * @param  usMpuId       [IN] ����Ϊ#UINT16��MPU ID�ţ���ΧSD6182:[0,39],SD6157:[0,10]��
 * @param  usRangeId     [IN] ����Ϊ#UINT16��MPU�ε�ID�ţ���Χ����ն�ӦMPU��Ԫ��Ӳ�����
 * @param  usWrProt      [IN] ����Ϊ#UINT16�������õĶ�д���ԣ�bit0����д������ֵ1--������д��ֵ0--����д��bit1�����������ֵ1--���������ֵ0--�������
 *
 * @retval #OS_ERRNO_MPU_GROUP_ID_INVALID      0x02002101�������Group Id�Ƿ���
 * @retval #OS_ERRNO_MPU_ID_INVALID            0x02002102�������MPU Id�Ƿ���
 * @retval #OS_ERRNO_MPU_RANGE_ID_INVALID      0x02002104���û�����Ķ�Id�Ƿ���
 * @retval #SRE_OK                             0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_hw_mpu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MpuDisable | SRE_MpuRestore
 */
extern UINT32 SRE_MpuMasterCfg(UINT16 usGroupId, UINT16 usMpuId, UINT16 usRangeId, UINT16 usWrProt);

/**
 * @ingroup  SRE_hw_mpu
 * @brief ����ָ����Group���ָ����MPU�εĶ�д���ԡ�
 *
 * @par ����:
 * ��ѯָ��Group�����usMpuId��usRangeIdָ����MPU�εĶ�д���ԣ����������pusWrProt��
 *
 * @attention
 * <ul>
 * <li>�ò�����֧��SD6182��SD6157ƽ̨��</li>
 * <li>�ò�����֧��ESLƽ̨��</li>
 * <li>�û����øýӿ�ʱ����Ҫ��֤��Ӧ��MPU��Դ�ɱ�����ʹ��(δ���ض�)������ᵼ�º˹�����</li>
 * <li>�������usRangeIdΪOS_MPU_RANGE_ID_ALL����ʾ��ѯ��δ�����ַ��MPU�ζ�д���ԡ�</li>
 * </ul>
 * @param  usGroupId     [IN] ����Ϊ#UINT16��Group ID�ţ���Χ[0,31]��
 * @param  usMpuId       [IN] ����Ϊ#UINT16��MPU ID�ţ���ΧSD6182:[0,39],SD6157:[0,10]��
 * @param  usRangeId     [IN] ����Ϊ#UINT16��MPU�ε�ID�ţ���Χ����ն�ӦMPU��Ԫ��Ӳ�����
 * @param  pusWrProt     [OUT] ����Ϊ#UINT16 *����ѯ�����Ķ�д���ԣ�bit0����д������ֵ1--������д��ֵ0--����д��bit1�����������ֵ1--���������ֵ0--�������
 *
 * @retval #OS_ERRNO_MPU_GROUP_ID_INVALID      0x02002101�������Group Id�Ƿ���
 * @retval #OS_ERRNO_MPU_ID_INVALID            0x02002102�������MPU Id�Ƿ���
 * @retval #OS_ERRNO_MPU_RANGE_ID_INVALID      0x02002104���û�����Ķ�Id�Ƿ���
 * @retval #OS_ERRNO_MPU_QUERY_PTR_NULL        0x02002106������ı����ѯ����ĵ�ַΪNULL��
 * @retval #SRE_OK                             0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_hw_mpu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MpuDisable | SRE_MpuRestore
 */
extern UINT32 SRE_MpuMasterQuery(UINT16 usGroupId, UINT16 usMpuId, UINT16 usRangeId, UINT16 *pusWrProt);

/**
 * @ingroup  SRE_hw_mpu
 * @brief ��ָֹ��MPU��Ԫ�ı������ܡ�
 *
 * @par ����:
 * ��ֹusMpuIdָ����MPU��Ԫ�ı������ܡ�
 *
 * @attention
 * <ul>
 * <li>�ò�����֧��SD6182��SD6157ƽ̨��</li>
 * <li>�ò�����֧��ESLƽ̨��</li>
 * <li>�û����øýӿ�ʱ����Ҫ��֤��Ӧ��MPU��Դ�ɱ�����ʹ��(δ���ض�)������ᵼ�º˹�����</li>
 * <li>�������usMpuIdΪ#OS_MPU_ID_ALL����ʾ��ֹ����MPU��Ԫ�ı������ܡ�</li>
 * <li>ȥʹ�ܺ󣬻ָ�ʹ��ǰ�����ܽ���mpu�����ò����������´�ȥʹ�ܲ��ɹ���</li>
 * </ul>
 * @param  usMpuId     [IN] ����Ϊ#UINT16��MPU ID�ţ���ΧSD6182:[0,39],SD6157:[0,10]���ߵ���OS_MPU_ID_ALL��
 *
 * @retval #OS_ERRNO_MPU_ID_INVALID            0x02002102�������MPU Id�Ƿ���
 * @retval #SRE_OK                             0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_hw_mpu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MpuRestore
 */
extern UINT32 SRE_MpuDisable(UINT16 usMpuId);

/**
 * @ingroup  SRE_hw_mpu
 * @brief �ָ�ָ��MPU��Ԫ�ı������ܡ�
 *
 * @par ����:
 * �ָ�usMpuIdָ����MPU��Ԫ�ı������ܡ�
 *
 * @attention
 * <ul>
 * <li>�ò�����֧��SD6182��SD6157ƽ̨��</li>
 * <li>�ò�����֧��ESLƽ̨��</li>
 * <li>�û����øýӿ�ʱ����Ҫ��֤��Ӧ��MPU��Դ�ɱ�����ʹ��(δ���ض�)������ᵼ�º˹�����</li>
 * <li>�������usMpuIdΪ#OS_MPU_ID_ALL����ʾ�ָ�����MPU��Ԫ�ı������ܡ�</li>
 * </ul>
 * @param  usMpuId     [IN] ����Ϊ#UINT16��MPU ID�ţ���ΧSD6182:[0,39],SD6157:[0,10]���ߵ���OS_MPU_ID_ALL��
 *
 * @retval #OS_ERRNO_MPU_ID_INVALID            0x02002102�������MPU Id�Ƿ���
 * @retval #SRE_OK                             0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_hw_mpu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MpuDisable
 */
extern UINT32 SRE_MpuRestore(UINT16 usMpuId);

/**
 * @ingroup  SRE_hw_mpu
 * @brief ��ѯMPU�����жϡ�
 *
 * @par ����:
 * ��ѯusMpuIdָ����MPU�����жϡ�������MPU�жϣ���ѯ֮�󣬻�������Ӧ���жϡ�
 *
 * @attention
 * <ul>
 * <li>�ò�����֧��SD6182��SD6157ƽ̨��</li>
 * <li>�ò�����֧��ESLƽ̨��</li>
 * <li>�û����øýӿ�ʱ����Ҫ��֤��Ӧ��MPU��Դ�ɱ�����ʹ��(δ���ض�)������ᵼ�º˹�����</li>
 * <li>����ѯ����DDR MPU�������Ѿ�ע��MPU�쳣���Ӻ���ʱ�������ڶ��AXI�ڵ�MPU�ж�ʱ�����ε����쳣���Ӻ�����</li>
 * <li>����ѯ����DDR MPU����Υ��MPU��������ʱ�����ظ��û����쳣��ַ��ʵ���쳣��ַ�ĵ�30Bit��</li>
 * <li>����ѯ����LL2 MPU��������Υ��MPU��������ʱ�����ظ��û����쳣��ַ��ȫ��Uncache��ַ��</li>
 * <li>���ó�ʼ��MPU Dfx���ܽӿں󣬲��ܵ��ô˽ӿڣ�����᷵����ش����롣</li>
 * </ul>
 * @param  usMpuId     [IN] ����Ϊ#UINT16��MPU ID�ţ���ΧSD6182:[0,39],SD6157:[0,10]��
 *
 * @retval #OS_ERRNO_MPU_ID_INVALID            0x02002102�������MPU Id�Ƿ���
 * @retval #SRE_OK                             0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_hw_mpu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see None
 */
extern UINT32 SRE_MpuIntQuery(UINT16 usMpuId);

/**
 * @ingroup  SRE_hw_mpu
 * @brief ע��MPU�쳣���Ӻ�����
 *
 * @par ����:
 * ע��MPU�쳣���Ӻ�����
 *
 * @attention
 * <ul>
 * <li>�ò�����֧��SD6182��SD6157ƽ̨��</li>
 * <li>�ò�����֧��ESLƽ̨��</li>
 * <li>�������pfnHookΪNULLʱ����ʾȡ��MPU�쳣���Ӻ�����</li>
 * <li>���û�ʹ��#SRE_MpuIntQuery��ѯMPU�����ж���Ϣʱ�������ڴ����жϣ���ýӿ�ע���MPU�쳣���Ӻ����ᱻ���á�</li>
 * </ul>
 * @param  pfnHook     [IN] ����Ϊ#MPU_EXC_HOOK_FUNC��MPU�쳣���Ӻ�����
 *
 * @retval #OS_ERRNO_MPU_EXC_INFO_HOOK_IS_FULL 0x02002108��ע��MPU�쳣���Ӻ���ʱ���Ѿ�ע�ᡣ
 * @retval #SRE_OK                             0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_hw_mpu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see None
 */
extern UINT32 SRE_MpuExcHookReg(MPU_EXC_HOOK_FUNC pfnHook);

/**
 * @ingroup  SRE_hw_mpu
 * @brief ��ʼ��MPU Dfx���ܡ�
 *
 * @par ����:
 * ��ʼ��MPU Dfx����, ʹ��MPU�����жϡ�
 *
 * @attention
 * <ul>
 * <li>�ò�����֧��SD6182��SD6157ƽ̨��</li>
 * <li>�ò�����֧��ESLƽ̨��</li>
 * <li>�û����øýӿ�ʱ����Ҫ��֤����ʼ��DFX���ܵ�MPU��Դ�ɱ�����ʹ��(δ���ض�)������ᵼ�º˹�����</li>
 * <li>�������usMpuIdΪ#OS_MPU_ID_ALL����ʾ��ʼ������MPU DFX���ܡ�</li>
 * <li>�������˵��ô˽ӿڣ��˼以�����û���֤��</li>
 * </ul>
 * @param  usMpuId     [IN] ����Ϊ#UINT16��MPU ID�ţ���ΧSD6182:[0,39],SD6157:[0,10]���ߵ���OS_MPU_ID_ALL��
 *
 * @retval #OS_ERRNO_MPU_ID_INVALID            0x02002102�������MPU Id�Ƿ���
 * @retval #SRE_OK                             0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_hw_mpu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see None
 */
extern UINT32 SRE_MpuDfxInit(UINT16 usMpuId);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* _SRE_HW_MPU_H */

