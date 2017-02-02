/**
 * @file sre_hw.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������Ӳ�����ģ��Ķ���ͷ�ļ��� \n
 */

 /**@defgroup SRE_hw Ӳ��֧��
   *@ingroup SRE_kernel
 */

#ifndef _SRE_HW_H
#define _SRE_HW_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_hw
 *  Ӳ�������Ϣ�����룺����ʵ����������ʱ����Ĳ���ΪNULL
 *
 * ֵ: 0x02002000
 *
 * �������: ��ȷ������Ĳ�����ΪNULL
 */
#define OS_ERRNO_HW_START_PARAM_CFG_NULL                        SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x00)

/**
 * @ingroup SRE_hw
 *  Ӳ�������Ϣ�����룺����ʵ����������ʱ��ʵ���ڸ��������ò�һ��
 *
 * ֵ: 0x02002001
 *
 * �������: ��ȷ��ʵ�������к����õ���������һ��
 */
#define OS_ERRNO_HW_START_PARAM_INCONSISTENT                    SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x01)

/**
 * @ingroup SRE_hw
 *  Ӳ�������Ϣ�����룺������ʱ��δ��#SRE_HardBootInit�е���#SRE_StartParamCfg�ӿڽ���������������
 *
 * ֵ: 0x02002002
 *
 * �������: ��ȷ������#SRE_HardBootInit�е���#SRE_StartParamCfg�ӿڽ���������������
 */
#define OS_ERRNO_HW_START_PARAM_NOT_CFG                         SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x02)

/**
 * @ingroup SRE_hw
 *  Ӳ�������Ϣ�����룺�豸ID����
 *
 * ֵ: 0x02002003
 *
 * �������: �豸ID��ȡֵ[0 ,2]
 */
#define OS_ERRNO_HW_DEVICE_ID_ERR                               SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x03)

/**
 * @ingroup SRE_hw
 *  Ӳ�������Ϣ�����룺uwCommVmid�����������
 *
 * ֵ: 0x02002004
 *
 * �������: COMM VMID��ȡֵ��Χ[0 ,7]
 */
#define OS_ERRNO_HW_VMID_ID_ERR                                 SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x04)

/**
 * @ingroup SRE_hw
 *  Ӳ�������Ϣ������: Cored ID����
 *
 * ֵ: 0x02002005
 *
 * �������: ȷ��Cored ID���ܴ��ڵ���оƬ֧�ֵ�������[OS_MAX_CORE_NUM]��ͬʱ�������ôӺ������������ѴӺ�ʱ��κ�ID����������ID
 */
#define OS_ERRNO_HW_CORE_ID_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x05)


/**
 * @ingroup SRE_hw
 *  Ӳ�������Ϣ�����룺�����ṹָ�����ΪNULL
 *
 * ֵ: 0x02002006
 *
 * �������: SD6183ƽ̨��ȷ����������������ṹָ�벻ΪNULL
 */
#define OS_ERRNO_HW_SLAVE_CORE_BOOTPARA_NULL                    SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x06)


/**
 * @ingroup SRE_hw
 *  Ӳ�������Ϣ�����룺���������ж���Ŀ����Ϊ0
 *
 * ֵ: 0x02002007
 *
 * �������: SD6183ƽ̨��ȷ���������û�ģʽ����MMU MAPʱ�����صĶ�������Ϊ0
 */
#define OS_ERRNO_HW_SLAVE_CORE_BOOTSECNUM_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x07)

/**
 * @ingroup SRE_hw
 *  Ӳ�������Ϣ�����룺�����ж����ȼ��Ƿ�
 *
 * ֵ: 0x02002008
 *
 * �������: SD6183ƽ̨��ȷ�����˻��ѴӺ˵Ļ����ж����ȼ���ΧΪ[1, 7]
 */
#define OS_ERRNO_HW_CORE_WAKE_UP_PRI_ERROR                      SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x08)

/**
 * @ingroup SRE_hw
 *  Ӳ�������Ϣ�����룺���������������������ַ�����ص�
 *
 * ֵ: 0x02002009
 *
 * �������: SD6183ƽ̨��ȷ�������������������������ַ�Ƿ������ص�
 */
#define OS_ERRNO_HW_SEC_AREA_OVERLAY_IN_VIR_ADDR                SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x09)

/**
 * @ingroup SRE_hw
 * �����룺�������������õ�������������ַvecbase���Ϸ���
 *
 * ֵ: 0x0200200a
 *
 * �������: ���SD6183ƽ̨Ӳ�߳�������������ַvecbase(���õ����ַ���Ӧ��ʵ��ַ)����֤4K�ֽڶ����Ҷ�Ӧ��ʵ��ַ����Ϊ�㡣
 */
#define OS_ERRNO_HW_VECBASE_ADDR_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x0a)

/**
 * @ingroup SRE_hw
 * �����룺�������������õ�ϵͳջ��ַ���Ϸ���
 *
 * ֵ: 0x0200200b
 *
 * �������: ���SD6183ƽ̨Ӳ�߳�����ϵͳջ��ַ����Ҫ��֤16�ֽڶ����Ҳ���Ϊ�㣻ͬʱ�Ų��ջ��ַ����ӳ����Ƿ�������Ϊ��򲻶���������
 */
#define OS_ERRNO_HW_SYS_STACK_ADDR_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x0b)

/**
 * @ingroup SRE_hw
 * �����룺�������������õĶѵ�ַ�����롣
 *
 * ֵ: 0x0200200c
 *
 * �������: ���SD6183ƽ̨Ӳ�߳�����ϵͳ�ѵ�ַ��ע������Ϊ���ַ������֤16�ֽڶ��롣
 */
#define OS_ERRNO_HW_HEAP_ADDR_NOT_ALIGNED                       SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x0c)


/**
 * @ingroup SRE_hw
 * �����룺����Ĳ����Ƿ���Ŀǰֻ֧��BALONG��ISP����
 *
 * ֵ: 0x02002012
 *
 * �������: �뱣֤����Ĳ����Ϸ���
 */
#define OS_ERRNO_HW_PLATFORM_INFO_PTR_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_HW, 0x12)

/**
 * @ingroup SRE_Hw
 * Ӳ�������Ϣ��
 *
 */
typedef struct tagHwModInfo
{
    UINT32 uwGiccCtrlOffset;      /**< оƬGIC CPU Interface��ַƫ�ƣ�Cortex_AXϵ��оƬ��Ч */
} HW_MOD_INFO_S;

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**@ingroup SRE_Hw
 * ���������ṹ�嶨��
 */

typedef struct tagStartParam
{
    UINT16 usInstID;              /**< ʵ��ID���������������������չ             */
    UINT16 usReserved;            /**< ���� */
    UINT16 usGHwSemStartID;       /**< ��ʵ�������Global Hwsem��ʼ����ID */
    UINT16 usGHwSemNum;           /**< ��ʵ�������Global Hwsem����*/
    UINT16 usCpuLHwSemStartID;    /**< ��ʵ�������CPU(SD6183 DSP2) cluster Local Hwsem��ʼ����ID */
    UINT16 usCpuLHwSemNum;        /**< ��ʵ�������CPU(SD6183 DSP2) cluster Local Hwsem����*/
    UINT16 usHacLHwSemStartID;    /**< ��ʵ�������HACCC cluster Local Hwsem��ʼ����ID */
    UINT16 usHacLHwSemNum;        /**< ��ʵ�������HACCC cluster Local Hwsem����*/
    UINT16 usDsp0LHwSemStartID;   /**< ��ʵ�������DSP0 cluster Local Hwsem��ʼ����ID */
    UINT16 usDsp0LHwSemNum;       /**< ��ʵ�������DSP0 cluster Local Hwsem����*/
    UINT16 usDsp1LHwSemStartID;   /**< ��ʵ�������DSP1 cluster Local Hwsem��ʼ����ID */
    UINT16 usDsp1LHwSemNum;       /**< ��ʵ�������DSP1 cluster Local hwsem����*/
    UINT16 usNorGMsgmBufStart;    /**< ��ʵ�������Global MSGM��ͨ��Ϣ������ʼ��ַ(MSGM��Դ���û�����ʱ��Ч)*/
    UINT16 usNorGMsgmBufLen;      /**< ��ʵ�������Global MSGM��ͨ��Ϣ���峤��(MSGM��Դ���û�����ʱ��Ч)*/
    UINT16 usNorLMsgmBufStart;    /**< ��ʵ�������Local MSGM��ͨ��Ϣ������ʼ��ַ(MSGM��Դ���û�����ʱ��Ч)*/
    UINT16 usNorLMsgmBufLen;      /**< ��ʵ�������Local MSGM��ͨ��Ϣ���峤��(MSGM��Դ���û�����ʱ��Ч)*/
 } START_PARAM_S;
#elif ((OS_HARDWARE_PLATFORM == OS_HIDSP))

/**
 * @ingroup SRE_hw
 * �Ӻ�������ӳ��ζ��塣
 */
typedef  struct tagSecAttr{
    UINT32 uwSecVA;
    UINT32 uwSecPA;
    UINT32 uwSecSize;
    UINT32 uwSecAttr;
}SEC_ATTR_S;

/**
 * @ingroup SRE_hw
 * �Ӻ����������ṹ�壬���������ôӺ�����������ͨ��osSlavePreBoot�ӿ���δ���
 */
typedef  struct tagSlaveCoreBootPara
{
    UINT32  uwCoreId;           /**<ȡֵ��Χ0~33*/
    UINT32  uwVmid;             /**<ϵͳģʽcontext ID, ��OS��װcontext ID�� VMID��bit5~7��|THDID��bit4��*/
    UINT32  uwPageTblAddr;      /**<MMUҳ����ڻ���ַ����֤0x4000(16K)����*/
    UINT32  uwPageTblLen;       /**<MMUҳ��ռ�õ��ڴ泤�ȣ�һ��������ҳ���ܳ��ȣ�����֤���ڵ���һ��ҳ����0x4000��16K��,�ұ�֤0x400(1K)���롣ҳ���С���ñ��뱣֤��������жε�ӳ�䣬����Ԥ��ҳ���ȿռ䣬��ҳ��������Ϊ0x4000������Ҫ��֤ӳ������жΣ��������߷�ʽӳ���OSӳ�䣩����Ҫ����ҳ��ռ䡣
                                  1������ҳ�����ʼ��ַΪ(uwPageTblAddr + 0x4000)������ҳ��ռ乩��OS���������еĶ�ӳ�估�û�����SRE_MmuAssign�ӿ�ӳ��ʹ��;
                                  2�������׶ι�����ʹ�õĶ���ҳ��ռ����: �������������õĶ�(stSecInfo)�򹤾߼���ӳ��Ķ�(Ŀǰ��mmu_config�л�ȡ)���ҳ�ӳ�����ʼ��ַ��bit[31,30]����ͬ�ĶΣ���ӳ��εĳ���С��1M�����������µ�ӳ�����ΪN, ����ҳ��ռ�ô�СΪ(N * 1K)Bytes.
                                  3������MMU�ӿ�SRE_MmuAssignʹ�õĶ���ҳ��ռ�: �������pVStart��ַ��ӳ�䳤��uwLen������1K�ռ������ҳ��ԭ��ͬ��������ӳ���ϵһ�¡�
                                */
    BOOL    bMmuMapFlag;        /**<TRUE:��ʾOS����MMUҳ��ӳ��MAP�Ľ���; False:ͨ�����߽���MMUҳ��ӳ��MAP�Ľ���*/
    UINT32  uwVecbase;          /**<Ӳ�߳�������������ַ��ע������Ϊ���ַ����ָ��vecbase����֤4K�ֽڶ���*/
    UINT32  uwSysHeap;          /**<Ӳ�߳�����ϵͳ�ѵ�ַ��ע������Ϊ���ַ������֤16�ֽڶ��룬����LSP�����õĶѵ�ַ����һ��*/
    UINT32  uwSysStack;         /**<Ӳ�߳�����ϵͳջ��ַ��ϵͳջ��ջ�ף�ע������Ϊ���ַ������֤16�ֽڶ��룬�Ҳ���Ϊ�㣬����LSP���õ�ջ��ַ����һ��*/
    UINT32  uwSecNum;           /**<���õ�ӳ��θ���*/
    SEC_ATTR_S  stSecInfo[0];   /**<�ô���ʼ˳����ӳ��Ķνṹ����*/
}SLAVE_CORE_BOOTPARA_S;


/**@ingroup SRE_Hw
 * ���������ṹ�嶨��
 */
typedef struct tagStartParam
{
    UINT16 usInstID;             /**< ʵ��ID���������������������չ     */
    UINT16 usReserved;           /**< ���� */
    UINT16 usGHwSemStartID;      /**< ��ʵ�������Global Hwsem��ʼ����ID */
    UINT16 usGHwSemNum;          /**< ��ʵ�������Global Hwsem����*/
    UINT16 usDsp0LHwSemStartID;  /**< ��ʵ�������DSP cluster0 Local Hwsem��ʼ����ID */
    UINT16 usDsp0LHwSemNum;      /**< ��ʵ�������DSP cluster0 Local Hwsem����*/
    UINT16 usDsp1LHwSemStartID;  /**< ��ʵ�������DSP cluster1 Local Hwsem��ʼ����ID */
    UINT16 usDsp1LHwSemNum;      /**< ��ʵ�������DSP cluster1 Local Hwsem����*/
    UINT16 usDsp2LHwSemStartID;  /**< ��ʵ�������DSP cluster2 Local Hwsem��ʼ����ID */
    UINT16 usDsp2LHwSemNum;      /**< ��ʵ�������DSP cluster2 Local Hwsem����*/
    UINT16 usHacLHwSemStartID;   /**< ��ʵ�������HACCC cluster Local Hwsem��ʼ����ID */
    UINT16 usHacLHwSemNum;       /**< ��ʵ�������HACCC cluster Local Hwsem����*/
 } START_PARAM_S;

#elif (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup SRE_Hw
 * Cortex-AXƽ̨��Ʒ���ͱ�š�
 */
typedef enum
{
    PLATFORM_BALONG = 0,      /**< Balong��Ʒ */
    PLATFORM_ISP,             /**< ISP��Ʒ    */
    PLATFORM_BUIT
}OS_PLATFORM_TYPE_S;
#endif

#if ((OS_HARDWARE_PLATFORM == OS_HIDSP) || (OS_HARDWARE_PLATFORM == OS_DSP220) \
|| (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 * @ingroup  SRE_hw
 * @brief ����ʵ������������
 *
 * @par ����:
 * ����pstStartParam����������ʵ������������OS���ݸ����ý�Hwsem��MSGM������Դ��ʵ�����зֶι���
 *
 * @attention
 * <ul>
 * <li>ֻ֧��SD6182/SD6157/SD6183ƽ̨��</li>
 * <li>�û�������#SRE_HardBootInit������DDR������غ���øú����������ʼ��ʧ�ܡ�</li>
 * <li>ʵ�������õ���Դ�ֶβ����ص����úϷ������û���֤��</li>
 * <li>OS�̶�ʹ��0��Ӳ���ź�����Ϊʵ���以�⣬�û�����ͨ����API��0��Ӳ���ź������ø�OS��</li>
 * </ul>
 *
 * @param  pstStartParam   [IN] ����#START_PARAM_S������������
 *
 * @retval #OS_ERRNO_HW_START_PARAM_CFG_NULL          0x02002000������ʵ����������ʱ����Ĳ���ΪNULL��
 * @retval #OS_ERRNO_HW_START_PARAM_INCONSISTENT      0x02002001������ʵ����������ʱ��ʵ���ڸ��������ò�һ�¡�
 * @retval #OS_ERRNO_HW_START_PARAM_NOT_CFG           0x02002002��������ʱ��δ��#SRE_HardBootInit�е���#SRE_StartParamCfg�ӿڽ��������������á�
 * @retval #OS_ERRNO_HWSEM_CFG_GLB_START_ID_INVALID   0x02002425������ʵ����������ʱ�����ȫ��Ӳ���ź�����ʼID�Ƿ���
 * @retval #OS_ERRNO_HWSEM_CFG_GLB_NUM_INVALID        0x02002426������ʵ����������ʱ�����ȫ��Ӳ���ź��������Ƿ�
 * @retval #OS_ERRNO_HWSEM_CFG_GLB_REGION_INVALID     0x02002427������ʵ����������ʱ���õ�ȫ��Ӳ���ź�������Ƿ���
 * @retval #OS_ERRNO_HWSEM_CFG_LOCAL_START_ID_INVALID 0x02002428������ʵ����������ʱ����ľֲ�Ӳ���ź�����ʼID����
 * @retval #OS_ERRNO_HWSEM_CFG_LOCAL_NUM_INVALID      0x02002429������ʵ����������ʱ����ľֲ�Ӳ���ź��������Ƿ���
 * @retval #OS_ERRNO_HWSEM_CFG_LOCAL_REGION_INVALID   0x0200242a������ʵ����������ʱ���õľֲ�Ӳ���ź�������Ƿ���
 * @retval #OS_ERRNO_MSGM_CFG_ADDR_OR_LEN_NOT_ALIGN   0x02002b3f������ʵ����������ʱ�����MSGM������ʼ��ַ�򳤶ȷ�4�ֽڶ��롣
 * @retval #OS_ERRNO_MSGM_CFG_START_ADDR_INVALID      0x02002b40������ʵ����������ʱ�����MSGM������ʼ��ַ�Ƿ���
 * @retval #OS_ERRNO_MSGM_CFG_QUEUE_LEN_INVALID       0x02002b41������ʵ����������ʱ�����MSGM���г��ȷǷ���
 * @retval #OS_ERRNO_MSGM_CFG_QUEUE_REGION_INVALID    0x02002b42������ʵ����������ʱ�����MSGM������ʼ��ַ�ͳ��Ⱦ���������Ƿ���
 * @retval #SRE_OK                                    0x00000000�������������óɹ���
 * @par ����:
 * <ul><li>sre_hw.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see
 **/
extern UINT32 SRE_StartParamCfg(START_PARAM_S  *pstStartParam);
#endif

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)
/**
 * @ingroup SRE_hw
 * �豸���
 */
typedef enum _tagOsDevice
{
    OS_DEVICE_HWSEM_ID = 0,/**< Ӳ���ź���ID*/
    OS_DEVICE_MSGM_ID = 1, /**< MSGM ID     */
    OS_DEVICE_TIMER_ID = 2 /**< ȫ�ֶ�ʱ��ID*/
} OS_DEVICE_TYPE_E;

/**
 * @ingroup SRE_hw
 * @brief Comm VMID���ýӿڡ�
 *
 * @par ����:
 * ����COMM VMID��ʹ��VMID��顣
 * @attention
 * <ul>
 * <li>������SD6183ƽ̨��</li>
 * <li>main����֮�󣬵���Ӳ���ź�����VMID���ã�������ܳ���Ӳ���ź���VMID������ʹ�ܵ������</li>
 * </ul>
 *
 * @param uwDeviceID    [IN] ����#UINT32���豸ID��ȡֵ��Χ[0,2],����ο�#OS_DEVICE_TYPE_E��
 * @param uwCommVmid    [IN] ����#UINT32��Comm Vmidֵ��ȡֵ��Χ[0,7]��
 *
 * @retval #OS_ERRNO_HW_VMID_ID_ERR      0x02002004��uwCommVmid�����������
 * @retval #OS_ERRNO_HW_DEVICE_ID_ERR    0x02002003���豸ID����
 * @retval #SRE_OK                       0x00000000�����سɹ���
 *
 * @par ����:
 * <ul><li>sre_hw.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern UINT32 SRE_CommVmidSet(UINT32 uwDeviceID, UINT32 uwCommVmid);

typedef enum
{
    OS_SUPER_MODE,
    OS_USER_MODE,
    OS_ERR_MODE
}OS_SYS_MODE;

/**
 * @ingroup SRE_hw
 * @brief VMID�л��ӿڡ�
 *
 * @par ����:
 * ���豾�˵�VMID��
 * @attention
 * <ul>
 * <li>������SD6183ƽ̨��</li>
 * </ul>
 *
 * @param enMode        [IN] ����#OS_SYS_MODE���л�VMID��ģʽ������ģʽ�����û�ģʽ��
 * @param ucCntxID      [IN] ����#UINT8���л���contextIDֵ��
 *
 * @retval #OS_ERRNO_SYS_MODE_INVALID      0x0200000f�������ģʽ����
 * @retval #SRE_OK                         0x00000000�����سɹ���
 *
 * @par ����:
 * <ul><li>sre_hw.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see ��
 */
extern  UINT32 SRE_CntxIdSwitch(OS_SYS_MODE enMode, UINT8 ucCntxID);

#endif

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup  SRE_hw
 * @brief ע����������Cortex-AXƽ̨Balong��ISP��Ʒ��־
 *
 * @par ����:
 * ע����������Cortex-AXƽ̨Balong��ISP��Ʒ�ı�־��
 *
 * @attention
 * <ul>
 * <li>ֻ֧��Cortex-AXƽ̨����������SRE_HardBootInit�����ȵ��á�</li>
 * <li>��</li>
 * </ul>
 *
 * @param enPlatFormFlag    [IN] ����#OS_PLATFORM_TYPE_S��Cortex-AXƽ̨��Ʒ���͡�
 *
 * @retval #OS_ERRNO_HW_PLATFORM_INFO_PTR_INVALID    0x02002012��enPlatFormFlag�����������
 * @retval #SRE_OK                                   0x00000000�����سɹ���
 *
 * @par ����:
 * <ul><li>sre_hw.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see NONE
 **/
extern UINT32 SRE_PlatFormReg(OS_PLATFORM_TYPE_S enPlatFormFlag);

/**
 * @ingroup  SRE_hw
 * @brief ARM��DSB����
 *
 * @par ����:
 * ARM��DSB���ܣ��ȴ��ڴ������ϣ��ڴ����δ����֮ǰ��CPU������������ڴ�ͼĴ�����
 *
 * @attention
 * <ul>
 * <li>ֻ֧��Cortex-AXƽ̨��</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_hw.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_DMB
 **/
#ifndef _WIN32
#define SRE_DSB() OS_EMBED_ASM("dsb")
#else
#define SRE_DSB()
#endif

/**
 * @ingroup  SRE_hw
 * @brief ARM��DMB����
 *
 * @par ����:
 * ARM��DMB���ܣ��ȴ��ڴ������ϣ��ڴ����δ����֮ǰ��CPU������������ڴ档
 *
 * @attention
 * <ul>
 * <li>ֻ֧��Cortex-AXƽ̨��</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_hw.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_DSB
 **/
#ifndef _WIN32
#define SRE_DMB() OS_EMBED_ASM("dmb")
#else
#define SRE_DMB()
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HW_H */


