/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_ivp32_dsp_subsys_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-04-08 11:47:21
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��4��8��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_IVP32_DSP_SUBSYS.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_IVP32_DSP_SUBSYS_INTERFACE_H__
#define __SOC_IVP32_DSP_SUBSYS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/2) IVP32_CFG_NON_SEC_REG
 ****************************************************************************/
/* �Ĵ���˵����IVP32 DSP CORE��ID��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_PRID_UNION */
#define SOC_IVP32_DSP_SUBSYS_PRID_ADDR(base)          ((base) + (0x0000))

/* �Ĵ���˵����On chip debug���á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_OCDHALTONRESET_UNION */
#define SOC_IVP32_DSP_SUBSYS_OCDHALTONRESET_ADDR(base) ((base) + (0x0004))

/* �Ĵ���˵����Ƭ��Ƭ������ģʽѡ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_STATVECTORSEL_UNION */
#define SOC_IVP32_DSP_SUBSYS_STATVECTORSEL_ADDR(base) ((base) + (0x0008))

/* �Ĵ���˵����DSP CORE pipeline����ʹ�ܡ�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_RUNSTALL_UNION */
#define SOC_IVP32_DSP_SUBSYS_RUNSTALL_ADDR(base)      ((base) + (0x000C))

/* �Ĵ���˵����DSP CORE�Ŀ���״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_PWAITMODE_UNION */
#define SOC_IVP32_DSP_SUBSYS_PWAITMODE_ADDR(base)     ((base) + (0x0010))

/* �Ĵ���˵����DSP CORE���ⲿ�����ж�״̬��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_BINTERRUPT_UNION */
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_ADDR(base)    ((base) + (0x0100))

/* �Ĵ���˵����дNMI�жϡ�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_NMI_UNION */
#define SOC_IVP32_DSP_SUBSYS_NMI_ADDR(base)           ((base) + (0x0104))

/* �Ĵ���˵����DSP CORE����λʹ�����á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_UNION */
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_ADDR(base) ((base) + (0x0200))

/* �Ĵ���˵����DSP CORE����λ�������á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_UNION */
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_ADDR(base) ((base) + (0x0204))

/* �Ĵ���˵����DSP CORE����λ״̬��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_UNION */
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_ADDR(base) ((base) + (0x0208))

/* �Ĵ���˵����Timer��WDG�Ĳο�ʱ��ѡ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_UNION */
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_ADDR(base) ((base) + (0x020C))

/* �Ĵ���˵����Timer��WDG�ӿں�CNT�Ĺ���ʱ�����ſء�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_UNION */
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_ADDR(base) ((base) + (0x0210))

/* �Ĵ���˵���������Զ��ſ�ʹ�ܡ�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_UNION */
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_ADDR(base) ((base) + (0x0214))

/* �Ĵ���˵����Timer0~1��WatchDog����λʹ�����á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_UNION */
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_ADDR(base) ((base) + (0x0218))

/* �Ĵ���˵����Timer0~1��WatchDog�����������á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_UNION */
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_ADDR(base) ((base) + (0x021C))

/* �Ĵ���˵����Timer0~1��WatchDog����״̬��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_UNION */
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_ADDR(base) ((base) + (0x0220))

/* �Ĵ���˵����DSP CORE�����ſء�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_DSPCORE_GATE_UNION */
#define SOC_IVP32_DSP_SUBSYS_DSPCORE_GATE_ADDR(base)  ((base) + (0x0224))

/* �Ĵ���˵����DSP CORE�����ſ�״̬��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_DSPCRE_GATE_ST_UNION */
#define SOC_IVP32_DSP_SUBSYS_DSPCRE_GATE_ST_ADDR(base) ((base) + (0x0228))

/* �Ĵ���˵����AXI interconnect���߶˿����ȵȼ����á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_UNION */
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ADDR(base) ((base) + (0x030C))

/* �Ĵ���˵����IVP32 DSP SYSTEM��master�ӿ�QoS�ȼ���̬���á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_UNION */
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_ADDR(base) ((base) + (0x0310))

/* �Ĵ���˵����memory�����źš�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_UNION */
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_ADDR(base)     ((base) + (0x0320))

/* �Ĵ���˵����memory�����źš�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_UNION */
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_ADDR(base)     ((base) + (0x0324))

/* �Ĵ���˵����memory�����źš�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_UNION */
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_ADDR(base)     ((base) + (0x0328))

/* �Ĵ���˵����CRG�����Timer0~1��WatchDog�Ľӿ�ʱ�Ӻͼ��������ſ�״̬��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_UNION */
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_ADDR(base) ((base) + (0x032C))

/* �Ĵ���˵����SMMU��S��prog�ӿڵ�Awakeup����Bypass���á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_ADDR(base) ((base) + (0x0330))

/* �Ĵ���˵����SMMU�͹�������״̬��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_ADDR(base) ((base) + (0x033C))

/* �Ĵ���˵����Timer0~1��WatchDog��APB�ӿڷ������߼�BYPASS���á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_UNION */
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_ADDR(base) ((base) + (0x0340))

/* �Ĵ���˵����Address Monitor����ʹ�����á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_ADDR(base)   ((base) + (0x0400))

/* �Ĵ���˵����Address Monitor�ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON_CLR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_CLR_ADDR(base)  ((base) + (0x0404))

/* �Ĵ���˵����Address Monitor�ж�ʹ�����á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_ADDR(base) ((base) + (0x0408))

/* �Ĵ���˵����Address Monitor�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_ADDR(base) ((base) + (0x040C))

/* �Ĵ���˵����Address Monitor0�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_BASE_ADDR(base) ((base) + (0x0410))

/* �Ĵ���˵����Address Monitor0�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_LEN_ADDR(base) ((base) + (0x0414))

/* �Ĵ���˵����Address Monitor0�����д�����Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_AWADDR_ADDR(base) ((base) + (0x0418))

/* �Ĵ���˵����Address Monitor0����Ķ������Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_ARADDR_ADDR(base) ((base) + (0x041C))

/* �Ĵ���˵����Address Monitor1�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_BASE_ADDR(base) ((base) + (0x0420))

/* �Ĵ���˵����Address Monitor1�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ���
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_LEN_ADDR(base) ((base) + (0x0424))

/* �Ĵ���˵����Address Monitor1�����д�����Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_AWADDR_ADDR(base) ((base) + (0x0428))

/* �Ĵ���˵����Address Monitor1����Ķ������Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_ARADDR_ADDR(base) ((base) + (0x042C))

/* �Ĵ���˵����Address Monitor2�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ���
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_BASE_ADDR(base) ((base) + (0x0430))

/* �Ĵ���˵����Address Monitor2�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_LEN_ADDR(base) ((base) + (0x0434))

/* �Ĵ���˵����Address Monitor2�����д�����Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_AWADDR_ADDR(base) ((base) + (0x0438))

/* �Ĵ���˵����Address Monitor2����Ķ������Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_ARADDR_ADDR(base) ((base) + (0x043C))

/* �Ĵ���˵����Address Monitor3�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_BASE_ADDR(base) ((base) + (0x0440))

/* �Ĵ���˵����Address Monitor3�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_LEN_ADDR(base) ((base) + (0x0444))

/* �Ĵ���˵����Address Monitor3�����д�����Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_AWADDR_ADDR(base) ((base) + (0x0448))

/* �Ĵ���˵����Address Monitor3����Ķ������Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_ARADDR_ADDR(base) ((base) + (0x044C))

/* �Ĵ���˵����Address Monitor4�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_BASE_ADDR(base) ((base) + (0x0450))

/* �Ĵ���˵����Address Monitor4�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_LEN_ADDR(base) ((base) + (0x0454))

/* �Ĵ���˵����Address Monitor4�����д�����Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_AWADDR_ADDR(base) ((base) + (0x0458))

/* �Ĵ���˵����Address Monitor4����Ķ������Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_ARADDR_ADDR(base) ((base) + (0x045C))

/* �Ĵ���˵����Address Monitor5�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_BASE_ADDR(base) ((base) + (0x0460))

/* �Ĵ���˵����Address Monitor5�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_LEN_ADDR(base) ((base) + (0x0464))

/* �Ĵ���˵����Address Monitor5�����д�����Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_AWADDR_ADDR(base) ((base) + (0x0468))

/* �Ĵ���˵����Address Monitor5����Ķ������Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_ARADDR_ADDR(base) ((base) + (0x046C))

/* �Ĵ���˵����Address Monitor6�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_BASE_ADDR(base) ((base) + (0x0470))

/* �Ĵ���˵����Address Monitor6�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_LEN_ADDR(base) ((base) + (0x0474))

/* �Ĵ���˵����Address Monitor6�����д�����Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_AWADDR_ADDR(base) ((base) + (0x0478))

/* �Ĵ���˵����Address Monitor6����Ķ������Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_ARADDR_ADDR(base) ((base) + (0x047C))

/* �Ĵ���˵����Address Monitor7�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_BASE_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_BASE_ADDR(base) ((base) + (0x0480))

/* �Ĵ���˵����Address Monitor7�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_LEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_LEN_ADDR(base) ((base) + (0x0484))

/* �Ĵ���˵����Address Monitor7�����д�����Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_AWADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_AWADDR_ADDR(base) ((base) + (0x0488))

/* �Ĵ���˵����Address Monitor7����Ķ������Ƿ����ʵĵ�ַ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_ARADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_ARADDR_ADDR(base) ((base) + (0x048C))

/* �Ĵ���˵����SMMU500��TBU��TCU���ſء�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_ADDR(base)    ((base) + (0x0500))

/* �Ĵ���˵����SMMU��TBU��TCU���ſ�״̬��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_ADDR(base)    ((base) + (0x0504))

/* �Ĵ���˵����SMMU��TBU��TCUӲ���Զ��ſ���ʱ��������
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_ADDR(base) ((base) + (0x050C))

/* �Ĵ���˵����SMMU��TBU��TCU����λʹ�ܡ�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_ADDR(base)   ((base) + (0x0510))

/* �Ĵ���˵����SMMU��TBU��TCU����λ���롣
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_ADDR(base)  ((base) + (0x0514))

/* �Ĵ���˵����SMMU��TBU��TCU����λ״̬��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_ADDR(base)   ((base) + (0x0518))

/* �Ĵ���˵������ϵͳ�汾�Ĵ�����
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_SUBSYS_VERSION_NUM_UNION */
#define SOC_IVP32_DSP_SUBSYS_SUBSYS_VERSION_NUM_ADDR(base) ((base) + (0x0800))



/****************************************************************************
                     (2/2) IVP32_CFG_SEC_REG
 ****************************************************************************/
/* �Ĵ���˵����IVP32 DSP��slave�ӿڵİ�ȫ�������á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_IVP32_SLV_SEC_SEL_UNION */
#define SOC_IVP32_DSP_SUBSYS_IVP32_SLV_SEC_SEL_ADDR(base) ((base) + (0x0300))

/* �Ĵ���˵����IVP32 DSP��master�ӿڵİ�ȫ�������á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_UNION */
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_ADDR(base) ((base) + (0x0304))

/* �Ĵ���˵����APB�ӿ����谲ȫ����ѡ��
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_UNION */
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_ADDR(base) ((base) + (0x0308))

/* �Ĵ���˵����IVP32 DSP SYSTEM��master�ӿڵ�ַremap��ʼ��ַ��̬���á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_START_REMAP_ADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_START_REMAP_ADDR_ADDR(base) ((base) + (0x0314))

/* �Ĵ���˵����IVP32 DSP SYSTEM��master�ӿڵ�ַremap��Сѡ��̬���á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_REMAP_LENGTH_UNION */
#define SOC_IVP32_DSP_SUBSYS_REMAP_LENGTH_ADDR(base)  ((base) + (0x0318))

/* �Ĵ���˵����IVP32 DSP SYSTEM��master�ӿڵ�ַremap��DDR�Ļ���ַ��̬���á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_DDR_REMAP_ADDR_UNION */
#define SOC_IVP32_DSP_SUBSYS_DDR_REMAP_ADDR_ADDR(base) ((base) + (0x031C))

/* �Ĵ���˵������ַremap�Ĵ�����ȫ�������á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_UNION */
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_ADDR(base) ((base) + (0x0334))

/* �Ĵ���˵����DSP CORE��Micro-DMA��MID���á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_UNION */
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_ADDR(base) ((base) + (0x0338))

/* �Ĵ���˵����SMMU��integ_sec_override�ź����á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_SMMU_INTEG_SEC_OVERRIDE_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_INTEG_SEC_OVERRIDE_ADDR(base) ((base) + (0x051C))

/* �Ĵ���˵����SMMU��spniden�źŵ����á�
   λ����UNION�ṹ:  SOC_IVP32_DSP_SUBSYS_SMMU_SPNIDEN_UNION */
#define SOC_IVP32_DSP_SUBSYS_SMMU_SPNIDEN_ADDR(base)  ((base) + (0x0520))





/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  6 STRUCT����
*****************************************************************************/



/*****************************************************************************
  7 UNION����
*****************************************************************************/

/****************************************************************************
                     (1/2) IVP32_CFG_NON_SEC_REG
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_PRID_UNION
 �ṹ˵��  : PRID �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: IVP32 DSP CORE��ID��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prid     : 16; /* bit[0-15] : processor ID���ڶ��DSPϵͳ����������DSP��ID��
                                                    ���ǵ�ϵͳ��ֻ��һ��DSP CORE���ʿɽ����ź�ͨ���Ĵ�������Ϊ����ֵ�� */
        unsigned int  reserved : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_PRID_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_PRID_prid_START      (0)
#define SOC_IVP32_DSP_SUBSYS_PRID_prid_END        (15)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_OCDHALTONRESET_UNION
 �ṹ˵��  : OCDHALTONRESET �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: On chip debug���á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ocdhaltonreset : 1;  /* bit[0]   : ��Breset����ʱ������ѡ��DSP CORE�Ĺ���ģʽ��
                                                          0������ģʽ��
                                                          1��OCDHaltMode������debug��
                                                         ���źŵ�processor���븴λ�󣬹�����normalģʽ��ʱ���仯û���κ�Ӱ�죻 */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_OCDHALTONRESET_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_OCDHALTONRESET_ocdhaltonreset_START  (0)
#define SOC_IVP32_DSP_SUBSYS_OCDHALTONRESET_ocdhaltonreset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_STATVECTORSEL_UNION
 �ṹ˵��  : STATVECTORSEL �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ƭ��Ƭ������ģʽѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statvectorsel : 1;  /* bit[0]   : ��Breset����ʱ������ѡ��DSP COREĬ��������ʽ��
                                                         0��Iram������
                                                         1��DDR������
                                                        ���ź���Ҫ��Breset�ź�����ǰ����10CYCLES�ȶ�������Breset�ź����ͺ����ٱ���10��CYCLES�ȶ�������ᵼ��DSP CORE��������Ԥ�ڵ�״���� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_STATVECTORSEL_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_STATVECTORSEL_statvectorsel_START  (0)
#define SOC_IVP32_DSP_SUBSYS_STATVECTORSEL_statvectorsel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_RUNSTALL_UNION
 �ṹ˵��  : RUNSTALL �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000001�����:32
 �Ĵ���˵��: DSP CORE pipeline����ʹ�ܡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  runstall : 1;  /* bit[0]   : ��Dreset�ź����ͺ������ǰ�����ź��������Ч����ʹprocessorֹͣ���У���ʱ���ⲿ��AXI master����ͨ��IVP32 DSP��AXI slave�ӿڷ���Iram��Dram��
                                                   ���ź��ڸ�λ����󣬲���DSP��������һ��ʱ���������ߣ�Ҳ��ʹDSP��pipelineֹͣ���������ǲ���������߹����� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_RUNSTALL_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_RUNSTALL_runstall_START  (0)
#define SOC_IVP32_DSP_SUBSYS_RUNSTALL_runstall_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_PWAITMODE_UNION
 �ṹ˵��  : PWAITMODE �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSP CORE�Ŀ���״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwaitmode : 1;  /* bit[0]   :  */
        unsigned int  reserved  : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_PWAITMODE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_PWAITMODE_pwaitmode_START  (0)
#define SOC_IVP32_DSP_SUBSYS_PWAITMODE_pwaitmode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_BINTERRUPT_UNION
 �ṹ˵��  : BINTERRUPT �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSP CORE���ⲿ�����ж�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_normal_ns_ipc : 1;  /* bit[0]    : �ǰ�ȫIPC��ͨ�ж�״̬������Ч */
        unsigned int  intr0_ns_ipc       : 1;  /* bit[1]    : �ǰ�ȫIPC�����ж�0״̬������Ч */
        unsigned int  intr1_ns_ipc       : 1;  /* bit[2]    : �ǰ�ȫIPC�����ж�1״̬������Ч */
        unsigned int  intr_normal_s_ipc  : 1;  /* bit[3]    : ��ȫIPC��ͨ�ж�״̬������Ч */
        unsigned int  intr0_s_ipc        : 1;  /* bit[4]    : ��ȫIPC�����ж�0״̬������Ч */
        unsigned int  intr1_s_ipc        : 1;  /* bit[5]    : ��ȫIPC�����ж�1״̬������Ч */
        unsigned int  intr_timer0_0      : 1;  /* bit[6]    : Timer0_0�ж�״̬������Ч */
        unsigned int  intr_timer0_1      : 1;  /* bit[7]    : Timer0_1�ж�״̬������Ч */
        unsigned int  reserved_0         : 1;  /* bit[8]    : ���� */
        unsigned int  reserved_1         : 1;  /* bit[9]    : ���� */
        unsigned int  reserved_2         : 1;  /* bit[10]   : ���� */
        unsigned int  reserved_3         : 1;  /* bit[11]   : ���� */
        unsigned int  intr_uart_print    : 1;  /* bit[12]   : ��ӡ�����ж�״̬������Ч */
        unsigned int  reserved_4         : 1;  /* bit[13]   : ���� */
        unsigned int  reserved_5         : 1;  /* bit[14]   : ���� */
        unsigned int  reserved_6         : 1;  /* bit[15]   : ���� */
        unsigned int  reserved_7         : 1;  /* bit[16]   : ���� */
        unsigned int  reserved_8         : 1;  /* bit[17]   : ���� */
        unsigned int  intr_wdg           : 1;  /* bit[18]   : WatchDog�ж�״̬������Ч */
        unsigned int  intr_timer1_0      : 1;  /* bit[19]   : Timer1_0�ж�״̬������Ч */
        unsigned int  intr_timer1_1      : 1;  /* bit[20]   : Timer1_1�ж�״̬������Ч */
        unsigned int  intr_isp           : 1;  /* bit[21]   : ISP�ж�״̬������Ч */
        unsigned int  reserved_9         : 1;  /* bit[22]   : ���� */
        unsigned int  reserved_10        : 1;  /* bit[23]   : ���� */
        unsigned int  reserved_11        : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_BINTERRUPT_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_normal_ns_ipc_START  (0)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_normal_ns_ipc_END    (0)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr0_ns_ipc_START        (1)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr0_ns_ipc_END          (1)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr1_ns_ipc_START        (2)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr1_ns_ipc_END          (2)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_normal_s_ipc_START   (3)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_normal_s_ipc_END     (3)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr0_s_ipc_START         (4)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr0_s_ipc_END           (4)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr1_s_ipc_START         (5)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr1_s_ipc_END           (5)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer0_0_START       (6)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer0_0_END         (6)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer0_1_START       (7)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer0_1_END         (7)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_uart_print_START     (12)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_uart_print_END       (12)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_wdg_START            (18)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_wdg_END              (18)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer1_0_START       (19)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer1_0_END         (19)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer1_1_START       (20)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_timer1_1_END         (20)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_isp_START            (21)
#define SOC_IVP32_DSP_SUBSYS_BINTERRUPT_intr_isp_END              (21)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_NMI_UNION
 �ṹ˵��  : NMI �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000000�����:32
 �Ĵ���˵��: дNMI�жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nmi      : 16; /* bit[0-15] : ���ļĴ�����ֵ��λ�����IVP32 DSP��NMI�жϣ�����Ч */
        unsigned int  reserved : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_NMI_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_NMI_nmi_START       (0)
#define SOC_IVP32_DSP_SUBSYS_NMI_nmi_END         (15)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_UNION
 �ṹ˵��  : DSP_CORE_RESET_EN �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSP CORE����λʹ�����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_debug_en     : 1;  /* bit[0]   : ֻ����üĴ���д1��������λDSP CORE��debug�߼���
                                                           д0���κ����壻 */
        unsigned int  rst_processor_en : 1;  /* bit[1]   : ֻ����üĴ���д1��������λDSP CORE��processor�߼���
                                                           д0���κ����壻 */
        unsigned int  rst_jtag_en      : 1;  /* bit[2]   : ֻ����üĴ���д1��������λDSP CORE��jtag�߼���
                                                           д0���κ����壻 */
        unsigned int  reserved         : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_rst_debug_en_START      (0)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_rst_debug_en_END        (0)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_rst_processor_en_START  (1)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_rst_processor_en_END    (1)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_rst_jtag_en_START       (2)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_EN_rst_jtag_en_END         (2)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_UNION
 �ṹ˵��  : DSP_CORE_RESET_DIS �Ĵ����ṹ���塣��ַƫ����:0x0204����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSP CORE����λ�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_debug_dis     : 1;  /* bit[0]   : ֻ����üĴ���д1�����ܳ���λDSP CORE��debug�߼�����λ��
                                                            д0���κ����壻 */
        unsigned int  rst_processor_dis : 1;  /* bit[1]   : ֻ����üĴ���д1�����ܳ���λDSP CORE��processor����λ��
                                                            д0���κ����壻 */
        unsigned int  rst_jtag_dis      : 1;  /* bit[2]   : ֻ����üĴ���д1�����ܳ���λDSP CORE��jtag����λ��
                                                            д0���κ����壻 */
        unsigned int  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_rst_debug_dis_START      (0)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_rst_debug_dis_END        (0)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_rst_processor_dis_START  (1)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_rst_processor_dis_END    (1)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_rst_jtag_dis_START       (2)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_DIS_rst_jtag_dis_END         (2)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_UNION
 �ṹ˵��  : DSP_CORE_RESET_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0208����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSP CORE����λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_debug_st     : 1;  /* bit[0]   : DSP CORE debug�߼��ĸ�λ״̬��
                                                           0����λ���룻
                                                           1����λ��Ч */
        unsigned int  rst_processor_st : 1;  /* bit[1]   : DSP CORE processor�ĸ�λ״̬��
                                                           0����λ���룻
                                                           1����λ��Ч */
        unsigned int  rst_jtag_st      : 1;  /* bit[2]   : DSP CORE jtag�ĸ�λ״̬��
                                                           0����λ���룻
                                                           1����λ��Ч */
        unsigned int  reserved         : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_rst_debug_st_START      (0)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_rst_debug_st_END        (0)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_rst_processor_st_START  (1)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_rst_processor_st_END    (1)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_rst_jtag_st_START       (2)
#define SOC_IVP32_DSP_SUBSYS_DSP_CORE_RESET_STATUS_rst_jtag_st_END         (2)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_UNION
 �ṹ˵��  : REF_CLOCK_SEL �Ĵ����ṹ���塣��ַƫ����:0x020C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Timer��WDG�Ĳο�ʱ��ѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  refclk_sel_timer0_0 : 1;  /* bit[0]   : Timer0_0�������Ĳο�ʱ��ѡ��
                                                              0:32KHz�ο�ʱ�ӣ�
                                                              1:19.2MHz�ο�ʱ�ӣ� */
        unsigned int  refclk_sel_timer0_1 : 1;  /* bit[1]   : Timer0_1�������Ĳο�ʱ��ѡ��
                                                              0:32KHz�ο�ʱ�ӣ�
                                                              1:19.2MHz�ο�ʱ�ӣ� */
        unsigned int  refclk_sel_timer1_0 : 1;  /* bit[2]   : Timer1_0�������Ĳο�ʱ��ѡ��
                                                              0:32KHz�ο�ʱ�ӣ�
                                                              1:19.2MHz�ο�ʱ�ӣ� */
        unsigned int  refclk_sel_timer1_1 : 1;  /* bit[3]   : Timer1_1�������Ĳο�ʱ��ѡ��
                                                              0:32KHz�ο�ʱ�ӣ�
                                                              1:19.2MHz�ο�ʱ�ӣ� */
        unsigned int  refclk_sel_wdg      : 1;  /* bit[4]   : WatchDog�������Ĳο�ʱ��ѡ��
                                                              0:32KHz�ο�ʱ�ӣ�
                                                              1:APB �ӿ�ʱ�ӣ�125MHz�� */
        unsigned int  reserved            : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer0_0_START  (0)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer0_0_END    (0)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer0_1_START  (1)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer0_1_END    (1)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer1_0_START  (2)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer1_0_END    (2)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer1_1_START  (3)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_timer1_1_END    (3)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_wdg_START       (4)
#define SOC_IVP32_DSP_SUBSYS_REF_CLOCK_SEL_refclk_sel_wdg_END         (4)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_UNION
 �ṹ˵��  : APB_GATE_CLOCK �Ĵ����ṹ���塣��ַƫ����:0x0210����ֵ:0x0000003F�����:32
 �Ĵ���˵��: Timer��WDG�ӿں�CNT�Ĺ���ʱ�����ſء�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_wdg_if     : 1;  /* bit[0]   : WDG�ӿ�ʱ�����ſأ����ڵ͹��ģ���WDG��ʹ�ã������޷���ʱ���ر�ʱ�Ӵﵽ�͹��ĵ�Ŀ��
                                                             0:�ر�ʱ�ӣ�
                                                             1:��ʱ�ӣ� */
        unsigned int  gt_pclk_wdg_cnt    : 1;  /* bit[1]   : WDG������ʱ�����ſأ����ڵ͹��ģ���WDG��ʹ��ʱ���ر�ʱ�Ӵﵽ�͹��ĵ�Ŀ��
                                                             0:�ر�ʱ�ӣ�
                                                             1:��ʱ�ӣ� */
        unsigned int  gt_pclk_timer0_if  : 1;  /* bit[2]   : Timer0�ӿ�ʱ�����ſأ����ڵ͹��ģ���Timer��ʹ�ã������޷���ʱ���ر�ʱ�Ӵﵽ�͹��ĵ�Ŀ��
                                                             0:�ر�ʱ�ӣ�
                                                             1:��ʱ�ӣ� */
        unsigned int  gt_pclk_timer0_cnt : 1;  /* bit[3]   : Timer0������ʱ�����ſأ���Timer��ʹ��ʱ���ر�ʱ�Ӵﵽ�͹��ĵ�Ŀ��
                                                             0:�ر�ʱ�ӣ�
                                                             1:��ʱ�ӣ� */
        unsigned int  gt_pclk_timer1_if  : 1;  /* bit[4]   : Timer1�ӿ�ʱ�����ſأ����ڵ͹��ģ���Timer��ʹ�ã������޷���ʱ���ر�ʱ�Ӵﵽ�͹��ĵ�Ŀ��
                                                             0:�ر�ʱ�ӣ�
                                                             1:��ʱ�ӣ� */
        unsigned int  gt_pclk_timer1_cnt : 1;  /* bit[5]   : Timer1������ʱ�����ſأ���Timer��ʹ��ʱ���ر�ʱ�Ӵﵽ�͹��ĵ�Ŀ��
                                                             0:�ر�ʱ�ӣ�
                                                             1:��ʱ�ӣ� */
        unsigned int  reserved           : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_wdg_if_START      (0)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_wdg_if_END        (0)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_wdg_cnt_START     (1)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_wdg_cnt_END       (1)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer0_if_START   (2)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer0_if_END     (2)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer0_cnt_START  (3)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer0_cnt_END    (3)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer1_if_START   (4)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer1_if_END     (4)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer1_cnt_START  (5)
#define SOC_IVP32_DSP_SUBSYS_APB_GATE_CLOCK_gt_pclk_timer1_cnt_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_UNION
 �ṹ˵��  : BUS_GATE_CLOCK �Ĵ����ṹ���塣��ַƫ����:0x0214����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����Զ��ſ�ʹ�ܡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dw_axi_m1_cg_en      : 1;  /* bit[0]    : dw_axi����m1�ӿ��Զ��ſأ����ڵ͹������
                                                                0:�ر��Զ��ſأ�
                                                                1:���Զ��ſأ� */
        unsigned int  dw_axi_m2_cg_en      : 1;  /* bit[1]    : dw_axi����m2�ӿ��Զ��ſأ����ڵ͹������
                                                                0:�ر��Զ��ſأ�
                                                                1:���Զ��ſأ� */
        unsigned int  dw_axi_s1_cg_en      : 1;  /* bit[2]    : dw_axi����s1�ӿ��Զ��ſأ����ڵ͹������
                                                                0:�ر��Զ��ſأ�
                                                                1:���Զ��ſأ� */
        unsigned int  dw_axi_s2_cg_en      : 1;  /* bit[3]    : dw_axi����s2�ӿ��Զ��ſأ����ڵ͹������
                                                                0:�ر��Զ��ſأ�
                                                                1:���Զ��ſأ� */
        unsigned int  dw_axi_s3_cg_en      : 1;  /* bit[4]    : dw_axi����s3�ӿ��Զ��ſأ����ڵ͹������
                                                                0:�ر��Զ��ſأ�
                                                                1:���Զ��ſأ� */
        unsigned int  dw_axi_s4_cg_en      : 1;  /* bit[5]    : dw_axi����s4�ӿ��Զ��ſأ����ڵ͹������
                                                                0:�ر��Զ��ſأ�
                                                                1:���Զ��ſأ� */
        unsigned int  dw_axi_s5_cg_en      : 1;  /* bit[6]    : dw_axi����s5�ӿ��Զ��ſأ����ڵ͹������
                                                                0:�ر��Զ��ſأ�
                                                                1:���Զ��ſأ� */
        unsigned int  defaut_slv_cg_en     : 1;  /* bit[7]    : dw_axi����default slave�ӿ��Զ��ſأ����ڵ͹������
                                                                0:�ر��Զ��ſأ�
                                                                1:���Զ��ſأ� */
        unsigned int  x2p_pclk_cg_en       : 1;  /* bit[8]    : x2p��APB�ӿ��Զ��ſأ����ڵ͹������
                                                                0:�ر��Զ��ſأ�
                                                                1:���Զ��ſأ� */
        unsigned int  x2p_aclk_cg_en       : 1;  /* bit[9]    : x2p��AXI�ӿ��Զ��ſأ����ڵ͹������
                                                                0:�ر��Զ��ſأ�
                                                                1:���Զ��ſأ� */
        unsigned int  ivp32_cfg_pclk_cg_en : 1;  /* bit[10]   : ivp32_cfgģ��APB�ӿ��Զ��ſأ����ڵ͹������
                                                                0:�ر��Զ��ſأ�
                                                                1:���Զ��ſأ�
                                                                �Զ��ſ�ֻ������ƼĴ�����д�߼���ʱ�ӣ������ſ�ͬ�������߼���ʱ�ӣ� */
        unsigned int  x2x_aclk_cg_en       : 1;  /* bit[11]   : x2xͬ���Žӿ��Զ��ſأ����ڵ͹������
                                                                0:�ر��Զ��ſأ�
                                                                1:���Զ��ſأ� */
        unsigned int  reserved             : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_m1_cg_en_START       (0)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_m1_cg_en_END         (0)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_m2_cg_en_START       (1)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_m2_cg_en_END         (1)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s1_cg_en_START       (2)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s1_cg_en_END         (2)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s2_cg_en_START       (3)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s2_cg_en_END         (3)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s3_cg_en_START       (4)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s3_cg_en_END         (4)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s4_cg_en_START       (5)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s4_cg_en_END         (5)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s5_cg_en_START       (6)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_dw_axi_s5_cg_en_END         (6)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_defaut_slv_cg_en_START      (7)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_defaut_slv_cg_en_END        (7)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_x2p_pclk_cg_en_START        (8)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_x2p_pclk_cg_en_END          (8)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_x2p_aclk_cg_en_START        (9)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_x2p_aclk_cg_en_END          (9)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_ivp32_cfg_pclk_cg_en_START  (10)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_ivp32_cfg_pclk_cg_en_END    (10)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_x2x_aclk_cg_en_START        (11)
#define SOC_IVP32_DSP_SUBSYS_BUS_GATE_CLOCK_x2x_aclk_cg_en_END          (11)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_UNION
 �ṹ˵��  : TIMER_WDG_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x0218����ֵ:0x00000000�����:32
 �Ĵ���˵��: Timer0~1��WatchDog����λʹ�����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reset_timer0_en   : 1;  /* bit[0]   : ֻ����üĴ���д1��������λTimer0��
                                                            д0���κ����壻 */
        unsigned int  reset_timer1_en   : 1;  /* bit[1]   : ֻ����üĴ���д1��������λTimer1��
                                                            д0���κ����壻 */
        unsigned int  reset_watchdog_en : 1;  /* bit[2]   : ֻ����üĴ���д1��������λWatchDog��
                                                            д0���κ����壻 */
        unsigned int  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_reset_timer0_en_START    (0)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_reset_timer0_en_END      (0)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_reset_timer1_en_START    (1)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_reset_timer1_en_END      (1)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_reset_watchdog_en_START  (2)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_EN_reset_watchdog_en_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_UNION
 �ṹ˵��  : TIMER_WDG_RST_DIS �Ĵ����ṹ���塣��ַƫ����:0x021C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Timer0~1��WatchDog�����������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reset_timer0_dis   : 1;  /* bit[0]   : ֻ����üĴ���д1�����ܳ���λTimer0����λ��
                                                             д0���κ����壻 */
        unsigned int  reset_timer1_dis   : 1;  /* bit[1]   : ֻ����üĴ���д1�����ܳ���λTimer1����λ��
                                                             д0���κ����壻 */
        unsigned int  reset_watchdog_dis : 1;  /* bit[2]   : ֻ����üĴ���д1�����ܳ���λWatchDog����λ��
                                                             д0���κ����壻 */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_reset_timer0_dis_START    (0)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_reset_timer0_dis_END      (0)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_reset_timer1_dis_START    (1)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_reset_timer1_dis_END      (1)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_reset_watchdog_dis_START  (2)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_DIS_reset_watchdog_dis_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_UNION
 �ṹ˵��  : TIMER_WDG_RST_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0220����ֵ:0x00000007�����:32
 �Ĵ���˵��: Timer0~1��WatchDog����״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reset_timer0_status   : 1;  /* bit[0]   : Timer0�ĸ�λ״̬��
                                                                0����λ��Ч��
                                                                1����λ���� */
        unsigned int  reset_timer1_status   : 1;  /* bit[1]   : Timer1�ĸ�λ״̬��
                                                                0����λ��Ч��
                                                                1����λ���� */
        unsigned int  reset_watchdog_status : 1;  /* bit[2]   : WatchDog�ĸ�λ״̬��
                                                                0����λ��Ч��
                                                                1����λ���� */
        unsigned int  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_reset_timer0_status_START    (0)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_reset_timer0_status_END      (0)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_reset_timer1_status_START    (1)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_reset_timer1_status_END      (1)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_reset_watchdog_status_START  (2)
#define SOC_IVP32_DSP_SUBSYS_TIMER_WDG_RST_STATUS_reset_watchdog_status_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_DSPCORE_GATE_UNION
 �ṹ˵��  : DSPCORE_GATE �Ĵ����ṹ���塣��ַƫ����:0x0224����ֵ:0x00000001�����:32
 �Ĵ���˵��: DSP CORE�����ſء�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivp32_dspcore_gt : 1;  /* bit[0]   : DSP CORE��ʱ�����ſأ�
                                                           0:�ر�ʱ�ӣ�
                                                           1:��ʱ�ӣ� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_DSPCORE_GATE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_DSPCORE_GATE_ivp32_dspcore_gt_START  (0)
#define SOC_IVP32_DSP_SUBSYS_DSPCORE_GATE_ivp32_dspcore_gt_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_DSPCRE_GATE_ST_UNION
 �ṹ˵��  : DSPCRE_GATE_ST �Ĵ����ṹ���塣��ַƫ����:0x0228����ֵ:0x00000001�����:32
 �Ĵ���˵��: DSP CORE�����ſ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivp32_dspcore_gate_st : 1;  /* bit[0]   : DSP CORE��ʱ�����ſ�״̬��
                                                                0:�ر�ʱ�ӣ�
                                                                1:��ʱ�ӣ� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_DSPCRE_GATE_ST_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_DSPCRE_GATE_ST_ivp32_dspcore_gate_st_START  (0)
#define SOC_IVP32_DSP_SUBSYS_DSPCRE_GATE_ST_ivp32_dspcore_gate_st_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_UNION
 �ṹ˵��  : INTERCONNECT_PRIORITY_CFG �Ĵ����ṹ���塣��ַƫ����:0x030C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXI interconnect���߶˿����ȵȼ����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivp32_slv_priority  : 3;  /* bit[0-2]  : ����AXI interconnect��S1�ڣ�����VIP32 DSP CORE��priority�ȼ���������SUBSYS�ڲ�slave�˿�response���ص����ȵȼ���
                                                               3'h0����������ȵȼ���3'h7��������ȵȼ��� */
        unsigned int  ddr_priority        : 3;  /* bit[3-5]  : ����AXI interconnect��S2�ڣ�����DDR�˿ڣ�priority�ȼ���������SUBSYS�ڲ���slave�˿�response���ص����ȵȼ���
                                                               3'h0����������ȵȼ���3'h7��������ȵȼ��� */
        unsigned int  peri_priority       : 3;  /* bit[6-8]  : ����AXI interconnect��S3�ڣ�����VTimer0~1��WatchDog��CFGģ�飩priority�ȼ���������SUBSYS�ڲ���slave�˿�response���ص����ȵȼ���
                                                               3'h0����������ȵȼ���3'h7��������ȵȼ��� */
        unsigned int  smmu_cfg_priority   : 3;  /* bit[9-11] : ����AXI interconnect��S4�ڣ�����SMMU���ÿڣ�priority�ȼ���������SUBSYS�ڲ���slave�˿�response���ص����ȵȼ���
                                                               3'h0����������ȵȼ���3'h7��������ȵȼ��� */
        unsigned int  ap_cfg_priority     : 3;  /* bit[12-14]: ����AXI interconnect��S5�ڣ�����SYS_BUS���ߣ�priority�ȼ���������SUBSYS�ڲ���slave�˿�response���ص����ȵȼ���
                                                               3'h0����������ȵȼ���3'h7��������ȵȼ��� */
        unsigned int  ivp32_mst_priority  : 1;  /* bit[15]   : ����AXI interconnect��M1�ڣ�����IVP32_DSP_subsys��master�ӿڣ�priority�ȼ���������SUBSYS�ڲ���master�˿ڷ���interconnect S�ڵ����ȵȼ���
                                                               1'b0����������ȵȼ���1'b1��������ȵȼ��� */
        unsigned int  subsys_cfg_priority : 1;  /* bit[16]   : ����AXI interconnect��M2�ڣ�����ISYS_BUS��master�ڣ�priority�ȼ���������SUBSYS�ڲ���master�˿ڷ���interconnect S�ڵ����ȵȼ���
                                                               1'b0����������ȵȼ���1'b1��������ȵȼ��� */
        unsigned int  reserved            : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ivp32_slv_priority_START   (0)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ivp32_slv_priority_END     (2)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ddr_priority_START         (3)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ddr_priority_END           (5)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_peri_priority_START        (6)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_peri_priority_END          (8)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_smmu_cfg_priority_START    (9)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_smmu_cfg_priority_END      (11)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ap_cfg_priority_START      (12)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ap_cfg_priority_END        (14)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ivp32_mst_priority_START   (15)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_ivp32_mst_priority_END     (15)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_subsys_cfg_priority_START  (16)
#define SOC_IVP32_DSP_SUBSYS_INTERCONNECT_PRIORITY_CFG_subsys_cfg_priority_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_UNION
 �ṹ˵��  : IVP32_SYSTEM_QOS_CFG �Ĵ����ṹ���塣��ַƫ����:0x0310����ֵ:0x00000000�����:32
 �Ĵ���˵��: IVP32 DSP SYSTEM��master�ӿ�QoS�ȼ���̬���á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  processor_wr_qos : 4;  /* bit[0-3]  : IVP32 SYSTEM DSP CORE��дͨ����QoS�ȼ���̬���� */
        unsigned int  processor_rd_qos : 4;  /* bit[4-7]  : IVP32 SYSTEM DSP CORE�Ķ�ͨ����QoS�ȼ���̬���� */
        unsigned int  micro_dma_wr_qos : 4;  /* bit[8-11] : IVP32 SYSTEM Micro-DMA��дͨ����QoS�ȼ���̬���� */
        unsigned int  micro_dma_rd_qos : 4;  /* bit[12-15]: IVP32 SYSTEM Micro-DMA�Ķ�ͨ����QoS�ȼ���̬���� */
        unsigned int  reserved         : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_processor_wr_qos_START  (0)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_processor_wr_qos_END    (3)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_processor_rd_qos_START  (4)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_processor_rd_qos_END    (7)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_micro_dma_wr_qos_START  (8)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_micro_dma_wr_qos_END    (11)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_micro_dma_rd_qos_START  (12)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SYSTEM_QOS_CFG_micro_dma_rd_qos_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_UNION
 �ṹ˵��  : MEM_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0320����ֵ:0x00A800A8�����:32
 �Ĵ���˵��: memory�����źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dram1_mem_ctrls : 16; /* bit[0-15] : ͬ�� */
        unsigned int  iram_mem_ctrls  : 16; /* bit[16-31]: iram��memory controller�źţ�
                                                           bit0��sleep mode������Ч��
                                                           bit1��deep sleep mode������Ч��deep sleepģʽ������ʹmemory��ʧ�洢���ݣ�ֻ�Ǵ�deep sleepģʽ���Ѻ���Ҫ����ns��ʱ��ſ���ʹ�ã�
                                                           bit2��shut down������Ч��
                                                           ��3bit�ź��κ�bit����Ч����memory������Ч״̬����ʱ��memory�Ķ�д����Ч�ģ������ж�����Ϊ����̬��
                                                           bit3~bit10��ֵ���ֲ��䣬��Ҫ�����޸ģ�������memory�޷�ʹ�ã�
                                                           bit11~bit15��reserve�����κ����壻 */
    } reg;
} SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_dram1_mem_ctrls_START  (0)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_dram1_mem_ctrls_END    (15)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_iram_mem_ctrls_START   (16)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL0_iram_mem_ctrls_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_UNION
 �ṹ˵��  : MEM_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x0324����ֵ:0x00A800A8�����:32
 �Ĵ���˵��: memory�����źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itag_mem_ctrls  : 16; /* bit[0-15] : ͬ�� */
        unsigned int  dram0_mem_ctrls : 16; /* bit[16-31]: ͬ�� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_itag_mem_ctrls_START   (0)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_itag_mem_ctrls_END     (15)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_dram0_mem_ctrls_START  (16)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL1_dram0_mem_ctrls_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_UNION
 �ṹ˵��  : MEM_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x0328����ֵ:0x00A800A8�����:32
 �Ĵ���˵��: memory�����źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smmu_mem_ctrls   : 16; /* bit[0-15] : ͬ�� */
        unsigned int  icache_mem_ctrls : 16; /* bit[16-31]: ͬ�� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_smmu_mem_ctrls_START    (0)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_smmu_mem_ctrls_END      (15)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_icache_mem_ctrls_START  (16)
#define SOC_IVP32_DSP_SUBSYS_MEM_CTRL2_icache_mem_ctrls_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_UNION
 �ṹ˵��  : CRG_PERI_GT_ST �Ĵ����ṹ���塣��ַƫ����:0x032C����ֵ:0x0000003F�����:32
 �Ĵ���˵��: CRG�����Timer0~1��WatchDog�Ľӿ�ʱ�Ӻͼ��������ſ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crg_wdg_if_gt_st     : 1;  /* bit[0]   : WatchDog��APB�ӿ�ʱ�����ſ�״̬��
                                                               0��ʱ�Ӵ��ڹر�״̬��
                                                               1��ʱ�Ӵ��ڴ�״̬�� */
        unsigned int  crg_wdg_cnt_gt_st    : 1;  /* bit[1]   : WatchDog�ļ�����ʱ�����ſ�״̬��
                                                               0��ʱ�Ӵ��ڹر�״̬��
                                                               1��ʱ�Ӵ��ڴ�״̬�� */
        unsigned int  crg_timer0_if_gt_st  : 1;  /* bit[2]   : Timer0��APB�ӿ�ʱ�����ſ�״̬��
                                                               0��ʱ�Ӵ��ڹر�״̬��
                                                               1��ʱ�Ӵ��ڴ�״̬�� */
        unsigned int  crg_timer0_cnt_gt_st : 1;  /* bit[3]   : Timer0�ļ�����ʱ�����ſ�״̬��
                                                               0��ʱ�Ӵ��ڹر�״̬��
                                                               1��ʱ�Ӵ��ڴ�״̬�� */
        unsigned int  crg_timer1_if_gt_st  : 1;  /* bit[4]   : Timer1��APB�ӿ�ʱ�����ſ�״̬��
                                                               0��ʱ�Ӵ��ڹر�״̬��
                                                               1��ʱ�Ӵ��ڴ�״̬�� */
        unsigned int  crg_timer1_cnt_gt_st : 1;  /* bit[5]   : Timer1�ļ�����ʱ�����ſ�״̬��
                                                               0��ʱ�Ӵ��ڹر�״̬��
                                                               1��ʱ�Ӵ��ڴ�״̬�� */
        unsigned int  reserved             : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_wdg_if_gt_st_START      (0)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_wdg_if_gt_st_END        (0)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_wdg_cnt_gt_st_START     (1)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_wdg_cnt_gt_st_END       (1)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer0_if_gt_st_START   (2)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer0_if_gt_st_END     (2)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer0_cnt_gt_st_START  (3)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer0_cnt_gt_st_END    (3)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer1_if_gt_st_START   (4)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer1_if_gt_st_END     (4)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer1_cnt_gt_st_START  (5)
#define SOC_IVP32_DSP_SUBSYS_CRG_PERI_GT_ST_crg_timer1_cnt_gt_st_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_UNION
 �ṹ˵��  : SMMU_AWAKEBYPASS �Ĵ����ṹ���塣��ַƫ����:0x0330����ֵ:0x0000000F�����:32
 �Ĵ���˵��: SMMU��S��prog�ӿڵ�Awakeup����Bypass���á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smmu_tbu_awake_bypass : 1;  /* bit[0]   : TBU awakeup����Bypassʹ�ܣ�
                                                                0��ʹ��awakeup���ܣ�
                                                                1��Bypassawakeup���ܣ� */
        unsigned int  smmu_tcu_awake_bypass : 1;  /* bit[1]   : TCU awakeup����Bypassʹ�ܣ�
                                                                0��ʹ��awakeup���ܣ�
                                                                1��Bypassawakeup���ܣ� */
        unsigned int  smmu_tbu_hwgt_bypass  : 1;  /* bit[2]   : TBU �Զ��ſع���Bypassʹ�ܣ�
                                                                0��ʹ���Զ��ſع��ܣ��ҵ�smmu_tbu_awake_bypass����Ϊ0ʱ���Զ��ſز�����Ч����
                                                                1��Bypass �Զ��ſأ� */
        unsigned int  smmu_tcu_hwgt_bypass  : 1;  /* bit[3]   : TCU �Զ��ſع���Bypassʹ�ܣ�
                                                                0��ʹ���Զ��ſع��ܣ��ҵ�smmu_tcu_awake_bypass����Ϊ0ʱ���Զ��ſز�����Ч����
                                                                1��Bypass �Զ��ſأ� */
        unsigned int  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tbu_awake_bypass_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tbu_awake_bypass_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tcu_awake_bypass_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tcu_awake_bypass_END    (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tbu_hwgt_bypass_START   (2)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tbu_hwgt_bypass_END     (2)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tcu_hwgt_bypass_START   (3)
#define SOC_IVP32_DSP_SUBSYS_SMMU_AWAKEBYPASS_smmu_tcu_hwgt_bypass_END     (3)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_UNION
 �ṹ˵��  : SMMU_PWR_HANDSHAKE_ST �Ĵ����ṹ���塣��ַƫ����:0x033C����ֵ:0x00000003�����:32
 �Ĵ���˵��: SMMU�͹�������״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smmu_tbu_pwr_handshake_st : 1;  /* bit[0]   : TBU �͹�������״̬��
                                                                    0������͹���״̬��
                                                                    1���˳��͹���״̬�� */
        unsigned int  smmu_tcu_pwr_handshake_st : 1;  /* bit[1]   : TCU �͹�������״̬��
                                                                    0������͹���״̬��
                                                                    1���˳��͹���״̬�� */
        unsigned int  reserved                  : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_smmu_tbu_pwr_handshake_st_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_smmu_tbu_pwr_handshake_st_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_smmu_tcu_pwr_handshake_st_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_PWR_HANDSHAKE_ST_smmu_tcu_pwr_handshake_st_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_UNION
 �ṹ˵��  : APB_IF_DLOCK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x0340����ֵ:0x00000000�����:32
 �Ĵ���˵��: Timer0~1��WatchDog��APB�ӿڷ������߼�BYPASS���á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dlock_bp_timer0 : 1;  /* bit[0]   : Timer0��APB�ӿڷ������߼�BYPAAS���ã�
                                                          0��ʹ�ܷ������߼���
                                                          1��BYPASS�������߼��� */
        unsigned int  dlock_bp_timer1 : 1;  /* bit[1]   : Timer1��APB�ӿڷ������߼�BYPAAS���ã�
                                                          0��ʹ�ܷ������߼���
                                                          1��BYPASS�������߼��� */
        unsigned int  dlock_bp_wdg    : 1;  /* bit[2]   : WatchDog��APB�ӿڷ������߼�BYPAAS���ã�
                                                          0��ʹ�ܷ������߼���
                                                          1��BYPASS�������߼��� */
        unsigned int  reserved        : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_dlock_bp_timer0_START  (0)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_dlock_bp_timer0_END    (0)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_dlock_bp_timer1_START  (1)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_dlock_bp_timer1_END    (1)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_dlock_bp_wdg_START     (2)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_DLOCK_BYPASS_dlock_bp_wdg_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_UNION
 �ṹ˵��  : ADDR_MON_EN �Ĵ����ṹ���塣��ַƫ����:0x0400����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor����ʹ�����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon0_en : 1;  /* bit[0]   : Address Monitor0����ʹ�����ã�
                                                       0��Disable Address Monitor��
                                                       1��Enable Address Monitor�� */
        unsigned int  addr_mon1_en : 1;  /* bit[1]   : Address Monitor1����ʹ�����ã�
                                                       0��Disable Address Monitor��
                                                       1��Enable Address Monitor�� */
        unsigned int  addr_mon2_en : 1;  /* bit[2]   : Address Monitor2����ʹ�����ã�
                                                       0��Disable Address Monitor��
                                                       1��Enable Address Monitor�� */
        unsigned int  addr_mon3_en : 1;  /* bit[3]   : Address Monitor3����ʹ�����ã�
                                                       0��Disable Address Monitor��
                                                       1��Enable Address Monitor�� */
        unsigned int  addr_mon4_en : 1;  /* bit[4]   : Address Monitor4����ʹ�����ã�
                                                       0��Disable Address Monitor��
                                                       1��Enable Address Monitor�� */
        unsigned int  addr_mon5_en : 1;  /* bit[5]   : Address Monitor5����ʹ�����ã�
                                                       0��Disable Address Monitor��
                                                       1��Enable Address Monitor�� */
        unsigned int  addr_mon6_en : 1;  /* bit[6]   : Address Monitor6����ʹ�����ã�
                                                       0��Disable Address Monitor��
                                                       1��Enable Address Monitor�� */
        unsigned int  addr_mon7_en : 1;  /* bit[7]   : Address Monitor7����ʹ�����ã�
                                                       0��Disable Address Monitor��
                                                       1��Enable Address Monitor�� */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon0_en_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon0_en_END    (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon1_en_START  (1)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon1_en_END    (1)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon2_en_START  (2)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon2_en_END    (2)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon3_en_START  (3)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon3_en_END    (3)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon4_en_START  (4)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon4_en_END    (4)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon5_en_START  (5)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon5_en_END    (5)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon6_en_START  (6)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon6_en_END    (6)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon7_en_START  (7)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_EN_addr_mon7_en_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON_CLR_UNION
 �ṹ˵��  : ADDR_MON_CLR �Ĵ����ṹ���塣��ַƫ����:0x0404����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor�ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon_clr : 1;  /* bit[0]   : ��ļĴ���д��1�����ܹ����Address Monitor���ж��Լ��ж�״̬�Ĵ�����ֵ��ͬʱ���addr_monx_hit_axaddr��ֵ��
                                                       �üĴ������ɶ��� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON_CLR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_CLR_addr_mon_clr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_CLR_addr_mon_clr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_UNION
 �ṹ˵��  : ADDR_MON_INTR_EN �Ĵ����ṹ���塣��ַƫ����:0x0408����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor�ж�ʹ�����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon0_intr_en : 1;  /* bit[0]   : ͬ�� */
        unsigned int  addr_mon1_intr_en : 1;  /* bit[1]   : ͬ�� */
        unsigned int  addr_mon2_intr_en : 1;  /* bit[2]   : ͬ�� */
        unsigned int  addr_mon3_intr_en : 1;  /* bit[3]   : ͬ�� */
        unsigned int  addr_mon4_intr_en : 1;  /* bit[4]   : ͬ�� */
        unsigned int  addr_mon5_intr_en : 1;  /* bit[5]   : ͬ�� */
        unsigned int  addr_mon6_intr_en : 1;  /* bit[6]   : ͬ�� */
        unsigned int  addr_mon7_intr_en : 1;  /* bit[7]   : Address Monitor7�ж�ʹ�����ã�
                                                            0��Disable Address Monitor0���ж������
                                                            1��Enable Address Monitor���ж������
                                                            Address Monitor���ж�addr_mon_intr=(addr_mon7_intr_en&(addr_mon7_awhit|addr_mon7_arhit))|(addr_mon6_intr_en&(addr_mon6_awhit|addr_mon6_arhit))|��|(addr_mon0_intr_en&(addr_mon0_awhit|addr_mon0_arhit))��
                                                            ��ֻ��address monitor7���ж����ʹ����Чʱ����address monitor7ͳ�Ƶ��Ƿ���ַ����ʱ��addr_mon_intr��������Ч�����ж�ʹ��ʹ����Чʱ����ʹaddress monitor7ͳ�Ƶ��Ƿ���ַ���ʣ�addr_mon_intr��Ȼ������Ч��������address monitorû��ͳ�Ƶ��Ƿ���ַ���ʣ������ж����ʹ����Ч���� */
        unsigned int  reserved          : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon0_intr_en_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon0_intr_en_END    (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon1_intr_en_START  (1)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon1_intr_en_END    (1)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon2_intr_en_START  (2)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon2_intr_en_END    (2)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon3_intr_en_START  (3)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon3_intr_en_END    (3)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon4_intr_en_START  (4)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon4_intr_en_END    (4)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon5_intr_en_START  (5)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon5_intr_en_END    (5)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon6_intr_en_START  (6)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon6_intr_en_END    (6)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon7_intr_en_START  (7)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_EN_addr_mon7_intr_en_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_UNION
 �ṹ˵��  : ADDR_MON_INTR_STAT �Ĵ����ṹ���塣��ַƫ����:0x040C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon7_arhit : 1;  /* bit[0]    : ͬ�� */
        unsigned int  addr_mon7_awhit : 1;  /* bit[1]    : ͬ�� */
        unsigned int  addr_mon6_arhit : 1;  /* bit[2]    : ͬ�� */
        unsigned int  addr_mon6_awhit : 1;  /* bit[3]    : ͬ�� */
        unsigned int  addr_mon5_arhit : 1;  /* bit[4]    : ͬ�� */
        unsigned int  addr_mon5_awhit : 1;  /* bit[5]    : ͬ�� */
        unsigned int  addr_mon4_arhit : 1;  /* bit[6]    : ͬ�� */
        unsigned int  addr_mon4_awhit : 1;  /* bit[7]    : ͬ�� */
        unsigned int  addr_mon3_arhit : 1;  /* bit[8]    : ͬ�� */
        unsigned int  addr_mon3_awhit : 1;  /* bit[9]    : ͬ�� */
        unsigned int  addr_mon2_arhit : 1;  /* bit[10]   : ͬ�� */
        unsigned int  addr_mon2_awhit : 1;  /* bit[11]   : ͬ�� */
        unsigned int  addr_mon1_arhit : 1;  /* bit[12]   : ͬ�� */
        unsigned int  addr_mon1_awhit : 1;  /* bit[13]   : ͬ�� */
        unsigned int  addr_mon0_arhit : 1;  /* bit[14]   : Address Monitor0��ͨ���Ƿ��жԷǷ���ַ�ķ�������Address Monitor0�ļ�ط�Χ��
                                                           0���ޣ�
                                                           1���У� */
        unsigned int  addr_mon0_awhit : 1;  /* bit[15]   : Address Monitor0дͨ���Ƿ��жԷǷ���ַ�ķ�������Address Monitor0�ļ�ط�Χ��
                                                           0���ޣ�
                                                           1���У� */
        unsigned int  reserved        : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon7_arhit_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon7_arhit_END    (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon7_awhit_START  (1)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon7_awhit_END    (1)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon6_arhit_START  (2)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon6_arhit_END    (2)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon6_awhit_START  (3)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon6_awhit_END    (3)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon5_arhit_START  (4)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon5_arhit_END    (4)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon5_awhit_START  (5)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon5_awhit_END    (5)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon4_arhit_START  (6)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon4_arhit_END    (6)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon4_awhit_START  (7)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon4_awhit_END    (7)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon3_arhit_START  (8)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon3_arhit_END    (8)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon3_awhit_START  (9)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon3_awhit_END    (9)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon2_arhit_START  (10)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon2_arhit_END    (10)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon2_awhit_START  (11)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon2_awhit_END    (11)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon1_arhit_START  (12)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon1_arhit_END    (12)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon1_awhit_START  (13)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon1_awhit_END    (13)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon0_arhit_START  (14)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon0_arhit_END    (14)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon0_awhit_START  (15)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON_INTR_STAT_addr_mon0_awhit_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_BASE_UNION
 �ṹ˵��  : ADDR_MON0_ADDR_BASE �Ĵ����ṹ���塣��ַƫ����:0x0410����ֵ:0x000E8000�����:32
 �Ĵ���˵��: Address Monitor0�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon0_addr_base : 20; /* bit[0-19] : Address Monitor0�Ƿ���ַ���ʼ�ص���ʼ��ַ����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon0_addr_base����С�ڵ���addr_mon0_addr_base+addr_mon0_addr_len��Address Monitor0�ļ�ط�Χ��ʱ����ᴥ��addr_mon0_awhit/addr_mon0_arhit��Ч������addr_mon0_awhit/addr_mon0_arhit��ֵ���ֲ��䣻 */
        unsigned int  reserved            : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_BASE_addr_mon0_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_BASE_addr_mon0_addr_base_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_LEN_UNION
 �ṹ˵��  : ADDR_MON0_ADDR_LEN �Ĵ����ṹ���塣��ַƫ����:0x0414����ֵ:0x000003FF�����:32
 �Ĵ���˵��: Address Monitor0�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon0_addr_len : 20; /* bit[0-19] : Address Monitor0�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon0_addr_base����С�ڵ���addr_mon0_addr_base+addr_mon0_addr_len��Address Monitor0�ļ�ط�Χ��ʱ����ᴥ��addr_mon0_awhit/addr_mon0_arhit��Ч������addr_mon0_awhit/addr_mon0_arhit��ֵ���ֲ��䣻
                                                              addr_mon0_addr_len�ĵ�λ��4KB����Address Monitor0�ĵ�ַ��صľ���Ϊ4KB�� */
        unsigned int  reserved           : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_LEN_addr_mon0_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_ADDR_LEN_addr_mon0_addr_len_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_AWADDR_UNION
 �ṹ˵��  : ADDR_MON0_HIT_AWADDR �Ĵ����ṹ���塣��ַƫ����:0x0418����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor0�����д�����Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon0_hit_awaddr : 32; /* bit[0-31]: Address Monitor0�����д�����Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon0_awhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_AWADDR_addr_mon0_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_AWADDR_addr_mon0_hit_awaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_ARADDR_UNION
 �ṹ˵��  : ADDR_MON0_HIT_ARADDR �Ĵ����ṹ���塣��ַƫ����:0x041C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor0����Ķ������Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon0_hit_araddr : 32; /* bit[0-31]: Address Monitor0����Ķ������Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon0_arhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_ARADDR_addr_mon0_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON0_HIT_ARADDR_addr_mon0_hit_araddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_BASE_UNION
 �ṹ˵��  : ADDR_MON1_ADDR_BASE �Ĵ����ṹ���塣��ַƫ����:0x0420����ֵ:0x000E8500�����:32
 �Ĵ���˵��: Address Monitor1�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon1_addr_base : 20; /* bit[0-19] : Address Monitor1�Ƿ���ַ���ʼ�ص���ʼ��ַ����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon1_addr_base����С�ڵ���addr_mon1_addr_base+addr_mon1_addr_len��Address Monitor1�ļ�ط�Χ��ʱ����ᴥ��addr_mon1_awhit/addr_mon1_arhit��Ч������addr_mon1_awhit/addr_mon1_arhit��ֵ���ֲ��䣻 */
        unsigned int  reserved            : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_BASE_addr_mon1_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_BASE_addr_mon1_addr_base_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_LEN_UNION
 �ṹ˵��  : ADDR_MON1_ADDR_LEN �Ĵ����ṹ���塣��ַƫ����:0x0424����ֵ:0x0000010F�����:32
 �Ĵ���˵��: Address Monitor1�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon1_addr_len : 20; /* bit[0-19] : Address Monitor1�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon1_addr_base����С�ڵ���addr_mon1_addr_base+addr_mon1_addr_len��Address Monitor1�ļ�ط�Χ��ʱ����ᴥ��addr_mon1_awhit/addr_mon1_arhit��Ч������addr_mon1_awhit/addr_mon1_arhit��ֵ���ֲ��䣻
                                                              addr_mon1_addr_len�ĵ�λ��4KB����Address Monitor1�ĵ�ַ��صľ���Ϊ4KB�� */
        unsigned int  reserved           : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_LEN_addr_mon1_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_ADDR_LEN_addr_mon1_addr_len_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_AWADDR_UNION
 �ṹ˵��  : ADDR_MON1_HIT_AWADDR �Ĵ����ṹ���塣��ַƫ����:0x0428����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor1�����д�����Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon1_hit_awaddr : 32; /* bit[0-31]: Address Monitor1�����д�����Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon1_awhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_AWADDR_addr_mon1_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_AWADDR_addr_mon1_hit_awaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_ARADDR_UNION
 �ṹ˵��  : ADDR_MON1_HIT_ARADDR �Ĵ����ṹ���塣��ַƫ����:0x042C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor1����Ķ������Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon1_hit_araddr : 32; /* bit[0-31]: Address Monitor1����Ķ������Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon1_arhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_ARADDR_addr_mon1_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON1_HIT_ARADDR_addr_mon1_hit_araddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_BASE_UNION
 �ṹ˵��  : ADDR_MON2_ADDR_BASE �Ĵ����ṹ���塣��ַƫ����:0x0430����ֵ:0x000E8612�����:32
 �Ĵ���˵��: Address Monitor2�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon2_addr_base : 20; /* bit[0-19] : Address Monitor2�Ƿ���ַ���ʼ�ص���ʼ��ַ����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon2_addr_base����С�ڵ���addr_mon2_addr_base+addr_mon2_addr_len��Address Monitor2�ļ�ط�Χ��ʱ����ᴥ��addr_mon2_awhit/addr_mon2_arhit��Ч������addr_mon2_awhit/addr_mon2_arhit��ֵ���ֲ��䣻 */
        unsigned int  reserved            : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_BASE_addr_mon2_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_BASE_addr_mon2_addr_base_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_LEN_UNION
 �ṹ˵��  : ADDR_MON2_ADDR_LEN �Ĵ����ṹ���塣��ַƫ����:0x0434����ֵ:0x000005ED�����:32
 �Ĵ���˵��: Address Monitor2�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon2_addr_len : 20; /* bit[0-19] : Address Monitor2�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon2_addr_base����С�ڵ���addr_mon2_addr_base+addr_mon2_addr_len��Address Monitor2�ļ�ط�Χ��ʱ����ᴥ��addr_mon2_awhit/addr_mon2_arhit��Ч������addr_mon2_awhit/addr_mon2_arhit��ֵ���ֲ��䣻
                                                              addr_mon2_addr_len�ĵ�λ��4KB����Address Monitor2�ĵ�ַ��صľ���Ϊ4KB�� */
        unsigned int  reserved           : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_LEN_addr_mon2_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_ADDR_LEN_addr_mon2_addr_len_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_AWADDR_UNION
 �ṹ˵��  : ADDR_MON2_HIT_AWADDR �Ĵ����ṹ���塣��ַƫ����:0x0438����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor2�����д�����Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon2_hit_awaddr : 32; /* bit[0-31]: Address Monitor2�����д�����Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon2_awhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_AWADDR_addr_mon2_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_AWADDR_addr_mon2_hit_awaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_ARADDR_UNION
 �ṹ˵��  : ADDR_MON2_HIT_ARADDR �Ĵ����ṹ���塣��ַƫ����:0x043C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor2����Ķ������Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon2_hit_araddr : 32; /* bit[0-31]: Address Monitor2����Ķ������Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon2_arhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_ARADDR_addr_mon2_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON2_HIT_ARADDR_addr_mon2_hit_araddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_BASE_UNION
 �ṹ˵��  : ADDR_MON3_ADDR_BASE �Ĵ����ṹ���塣��ַƫ����:0x0440����ֵ:0x000E8C00�����:32
 �Ĵ���˵��: Address Monitor3�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon3_addr_base : 20; /* bit[0-19] : Address Monitor3�Ƿ���ַ���ʼ�ص���ʼ��ַ����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon3_addr_base����С�ڵ���addr_mon3_addr_base+addr_mon3_addr_len��Address Monitor3�ļ�ط�Χ��ʱ����ᴥ��addr_mon3_awhit/addr_mon3_arhit��Ч������addr_mon3_awhit/addr_mon3_arhit��ֵ���ֲ��䣻 */
        unsigned int  reserved            : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_BASE_addr_mon3_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_BASE_addr_mon3_addr_base_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_LEN_UNION
 �ṹ˵��  : ADDR_MON3_ADDR_LEN �Ĵ����ṹ���塣��ַƫ����:0x0444����ֵ:0x0000017F�����:32
 �Ĵ���˵��: Address Monitor3�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon3_addr_len : 20; /* bit[0-19] : Address Monitor3�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon3_addr_base����С�ڵ���addr_mon3_addr_base+addr_mon3_addr_len��Address Monitor3�ļ�ط�Χ��ʱ����ᴥ��addr_mon3_awhit/addr_mon3_arhit��Ч������addr_mon3_awhit/addr_mon3_arhit��ֵ���ֲ��䣻
                                                              addr_mon3_addr_len�ĵ�λ��4KB����Address Monitor3�ĵ�ַ��صľ���Ϊ4KB�� */
        unsigned int  reserved           : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_LEN_addr_mon3_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_ADDR_LEN_addr_mon3_addr_len_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_AWADDR_UNION
 �ṹ˵��  : ADDR_MON3_HIT_AWADDR �Ĵ����ṹ���塣��ַƫ����:0x0448����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor3�����д�����Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon3_hit_awaddr : 32; /* bit[0-31]: Address Monitor3�����д�����Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon3_awhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_AWADDR_addr_mon3_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_AWADDR_addr_mon3_hit_awaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_ARADDR_UNION
 �ṹ˵��  : ADDR_MON3_HIT_ARADDR �Ĵ����ṹ���塣��ַƫ����:0x044C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor3����Ķ������Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon3_hit_araddr : 32; /* bit[0-31]: Address Monitor3����Ķ������Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon3_arhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_ARADDR_addr_mon3_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON3_HIT_ARADDR_addr_mon3_hit_araddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_BASE_UNION
 �ṹ˵��  : ADDR_MON4_ADDR_BASE �Ĵ����ṹ���塣��ַƫ����:0x0450����ֵ:0x000E8D84�����:32
 �Ĵ���˵��: Address Monitor4�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon4_addr_base : 20; /* bit[0-19] : Address Monitor4�Ƿ���ַ���ʼ�ص���ʼ��ַ����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon4_addr_base����С�ڵ���addr_mon4_addr_base+addr_mon4_addr_len��Address Monitor4�ļ�ط�Χ��ʱ����ᴥ��addr_mon4_awhit/addr_mon4_arhit��Ч������addr_mon4_awhit/addr_mon4_arhit��ֵ���ֲ��䣻 */
        unsigned int  reserved            : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_BASE_addr_mon4_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_BASE_addr_mon4_addr_base_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_LEN_UNION
 �ṹ˵��  : ADDR_MON4_ADDR_LEN �Ĵ����ṹ���塣��ַƫ����:0x0454����ֵ:0x0000007B�����:32
 �Ĵ���˵��: Address Monitor4�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon4_addr_len : 20; /* bit[0-19] : Address Monitor4�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon4_addr_base����С�ڵ���addr_mon4_addr_base+addr_mon4_addr_len��Address Monitor4�ļ�ط�Χ��ʱ����ᴥ��addr_mon4_awhit/addr_mon4_arhit��Ч������addr_mon4_awhit/addr_mon4_arhit��ֵ���ֲ��䣻
                                                              addr_mon4_addr_len�ĵ�λ��4KB����Address Monitor4�ĵ�ַ��صľ���Ϊ4KB�� */
        unsigned int  reserved           : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_LEN_addr_mon4_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_ADDR_LEN_addr_mon4_addr_len_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_AWADDR_UNION
 �ṹ˵��  : ADDR_MON4_HIT_AWADDR �Ĵ����ṹ���塣��ַƫ����:0x0458����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor4�����д�����Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon4_hit_awaddr : 32; /* bit[0-31]: Address Monitor4�����д�����Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon4_awhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_AWADDR_addr_mon4_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_AWADDR_addr_mon4_hit_awaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_ARADDR_UNION
 �ṹ˵��  : ADDR_MON4_HIT_ARADDR �Ĵ����ṹ���塣��ַƫ����:0x045C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor4����Ķ������Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon4_hit_araddr : 32; /* bit[0-31]: Address Monitor4����Ķ������Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon4_arhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_ARADDR_addr_mon4_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON4_HIT_ARADDR_addr_mon4_hit_araddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_BASE_UNION
 �ṹ˵��  : ADDR_MON5_ADDR_BASE �Ĵ����ṹ���塣��ַƫ����:0x0460����ֵ:0x000E8E00�����:32
 �Ĵ���˵��: Address Monitor5�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon5_addr_base : 20; /* bit[0-19] : Address Monitor5�Ƿ���ַ���ʼ�ص���ʼ��ַ����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon5_addr_base����С�ڵ���addr_mon5_addr_base+addr_mon5_addr_len��Address Monitor5�ļ�ط�Χ��ʱ����ᴥ��addr_mon5_awhit/addr_mon5_arhit��Ч������addr_mon5_awhit/addr_mon5_arhit��ֵ���ֲ��䣻 */
        unsigned int  reserved            : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_BASE_addr_mon5_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_BASE_addr_mon5_addr_base_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_LEN_UNION
 �ṹ˵��  : ADDR_MON5_ADDR_LEN �Ĵ����ṹ���塣��ַƫ����:0x0464����ֵ:0x0001622F�����:32
 �Ĵ���˵��: Address Monitor5�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon5_addr_len : 20; /* bit[0-19] : Address Monitor5�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon5_addr_base����С�ڵ���addr_mon5_addr_base+addr_mon5_addr_len��Address Monitor5�ļ�ط�Χ��ʱ����ᴥ��addr_mon5_awhit/addr_mon5_arhit��Ч������addr_mon5_awhit/addr_mon5_arhit��ֵ���ֲ��䣻
                                                              addr_mon5_addr_len�ĵ�λ��4KB����Address Monitor5�ĵ�ַ��صľ���Ϊ4KB�� */
        unsigned int  reserved           : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_LEN_addr_mon5_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_ADDR_LEN_addr_mon5_addr_len_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_AWADDR_UNION
 �ṹ˵��  : ADDR_MON5_HIT_AWADDR �Ĵ����ṹ���塣��ַƫ����:0x0468����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor5�����д�����Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon5_hit_awaddr : 32; /* bit[0-31]: Address Monitor5�����д�����Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon5_awhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_AWADDR_addr_mon5_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_AWADDR_addr_mon5_hit_awaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_ARADDR_UNION
 �ṹ˵��  : ADDR_MON5_HIT_ARADDR �Ĵ����ṹ���塣��ַƫ����:0x046C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor5����Ķ������Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon5_hit_araddr : 32; /* bit[0-31]: Address Monitor5����Ķ������Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon5_arhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_ARADDR_addr_mon5_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON5_HIT_ARADDR_addr_mon5_hit_araddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_BASE_UNION
 �ṹ˵��  : ADDR_MON6_ADDR_BASE �Ĵ����ṹ���塣��ַƫ����:0x0470����ֵ:0x000FF031�����:32
 �Ĵ���˵��: Address Monitor6�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon6_addr_base : 20; /* bit[0-19] : Address Monitor6�Ƿ���ַ���ʼ�ص���ʼ��ַ����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon6_addr_base����С�ڵ���addr_mon6_addr_base+addr_mon6_addr_len��Address Monitor6�ļ�ط�Χ��ʱ����ᴥ��addr_mon6_awhit/addr_mon6_arhit��Ч������addr_mon6_awhit/addr_mon6_arhit��ֵ���ֲ��䣻 */
        unsigned int  reserved            : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_BASE_addr_mon6_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_BASE_addr_mon6_addr_base_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_LEN_UNION
 �ṹ˵��  : ADDR_MON6_ADDR_LEN �Ĵ����ṹ���塣��ַƫ����:0x0474����ֵ:0x00000FCE�����:32
 �Ĵ���˵��: Address Monitor6�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon6_addr_len : 20; /* bit[0-19] : Address Monitor6�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon6_addr_base����С�ڵ���addr_mon6_addr_base+addr_mon6_addr_len��Address Monitor6�ļ�ط�Χ��ʱ����ᴥ��addr_mon6_awhit/addr_mon6_arhit��Ч������addr_mon6_awhit/addr_mon6_arhit��ֵ���ֲ��䣻
                                                              addr_mon6_addr_len�ĵ�λ��4KB����Address Monitor6�ĵ�ַ��صľ���Ϊ4KB�� */
        unsigned int  reserved           : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_LEN_addr_mon6_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_ADDR_LEN_addr_mon6_addr_len_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_AWADDR_UNION
 �ṹ˵��  : ADDR_MON6_HIT_AWADDR �Ĵ����ṹ���塣��ַƫ����:0x0478����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor6�����д�����Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon6_hit_awaddr : 32; /* bit[0-31]: Address Monitor6�����д�����Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon6_awhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_AWADDR_addr_mon6_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_AWADDR_addr_mon6_hit_awaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_ARADDR_UNION
 �ṹ˵��  : ADDR_MON6_HIT_ARADDR �Ĵ����ṹ���塣��ַƫ����:0x047C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor6����Ķ������Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon6_hit_araddr : 32; /* bit[0-31]: Address Monitor6����Ķ������Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon6_arhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_ARADDR_addr_mon6_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON6_HIT_ARADDR_addr_mon6_hit_araddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_BASE_UNION
 �ṹ˵��  : ADDR_MON7_ADDR_BASE �Ĵ����ṹ���塣��ַƫ����:0x0480����ֵ:0x000E8000�����:32
 �Ĵ���˵��: Address Monitor7�Ƿ���ַ���ʼ�ص���ʼ��ַ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon7_addr_base : 20; /* bit[0-19] : Address Monitor7�Ƿ���ַ���ʼ�ص���ʼ��ַ����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon7_addr_base����С�ڵ���addr_mon7_addr_base+addr_mon7_addr_len��Address Monitor7�ļ�ط�Χ��ʱ����ᴥ��addr_mon7_awhit/addr_mon7_arhit��Ч������addr_mon7_awhit/addr_mon7_arhit��ֵ���ֲ��䣻 */
        unsigned int  reserved            : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_BASE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_BASE_addr_mon7_addr_base_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_BASE_addr_mon7_addr_base_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_LEN_UNION
 �ṹ˵��  : ADDR_MON7_ADDR_LEN �Ĵ����ṹ���塣��ַƫ����:0x0484����ֵ:0x00000BFF�����:32
 �Ĵ���˵��: Address Monitor7�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon7_addr_len : 20; /* bit[0-19] : Address Monitor7�Ƿ���ַ���ʼ�صĵ�ַ�ռ��С����IVP32 DSP��master�ӿڵķ��ʵ�ַawaddr/araddr�ĸ�20bit���ڵ���addr_mon7_addr_base����С�ڵ���addr_mon7_addr_base+addr_mon7_addr_len��Address Monitor7�ļ�ط�Χ��ʱ����ᴥ��addr_mon7_awhit/addr_mon7_arhit��Ч������addr_mon7_awhit/addr_mon7_arhit��ֵ���ֲ��䣻
                                                              addr_mon7_addr_len�ĵ�λ��4KB����Address Monitor7�ĵ�ַ��صľ���Ϊ4KB�� */
        unsigned int  reserved           : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_LEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_LEN_addr_mon7_addr_len_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_ADDR_LEN_addr_mon7_addr_len_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_AWADDR_UNION
 �ṹ˵��  : ADDR_MON7_HIT_AWADDR �Ĵ����ṹ���塣��ַƫ����:0x0488����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor7�����д�����Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon7_hit_awaddr : 32; /* bit[0-31]: Address Monitor7�����д�����Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon7_awhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_AWADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_AWADDR_addr_mon7_hit_awaddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_AWADDR_addr_mon7_hit_awaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_ARADDR_UNION
 �ṹ˵��  : ADDR_MON7_HIT_ARADDR �Ĵ����ṹ���塣��ַƫ����:0x048C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Address Monitor7����Ķ������Ƿ����ʵĵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_mon7_hit_araddr : 32; /* bit[0-31]: Address Monitor7����Ķ������Ƿ����ʵĵ�ַ��
                                                               ֻ�е�addr_mon7_arhit��Ч������1��ʱ���üĴ�����ֵ������Ч�ء� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_ARADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_ARADDR_addr_mon7_hit_araddr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_ADDR_MON7_HIT_ARADDR_addr_mon7_hit_araddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_UNION
 �ṹ˵��  : SMMU_SW_GT �Ĵ����ṹ���塣��ַƫ����:0x0500����ֵ:0x00000003�����:32
 �Ĵ���˵��: SMMU500��TBU��TCU���ſء�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_bclk_smmu_soft : 1;  /* bit[0]   : TBUʱ�����ſأ�
                                                            0:�ر�ʱ�ӣ�
                                                            1:��ʱ�ӣ� */
        unsigned int  gt_cclk_smmu_soft : 1;  /* bit[1]   : TCUʱ�����ſأ�
                                                            0:�ر�ʱ�ӣ�
                                                            1:��ʱ�ӣ� */
        unsigned int  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_gt_bclk_smmu_soft_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_gt_bclk_smmu_soft_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_gt_cclk_smmu_soft_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_SW_GT_gt_cclk_smmu_soft_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_UNION
 �ṹ˵��  : SMMU_GT_ST �Ĵ����ṹ���塣��ַƫ����:0x0504����ֵ:0x00000003�����:32
 �Ĵ���˵��: SMMU��TBU��TCU���ſ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  st_smmu_bclk : 1;  /* bit[0]   : SMMU��TBU���ſ�״̬��
                                                       0��ʱ�Ӵ��ڹر�״̬��
                                                       1��ʱ�Ӵ��ڴ�״̬�� */
        unsigned int  st_smmu_cclk : 1;  /* bit[1]   : SMMU��TCU���ſ�״̬��
                                                       0��ʱ�Ӵ��ڹر�״̬��
                                                       1��ʱ�Ӵ��ڴ�״̬�� */
        unsigned int  reserved     : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_st_smmu_bclk_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_st_smmu_bclk_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_st_smmu_cclk_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_GT_ST_st_smmu_cclk_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_UNION
 �ṹ˵��  : SMMU_HW_GT_CNT �Ĵ����ṹ���塣��ַƫ����:0x050C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU��TBU��TCUӲ���Զ��ſ���ʱ��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cactive_smmu_bclk_cnt : 6;  /* bit[0-5]  : ��������SMMU���Զ��ſ�ʹ��ʱ����TBU����ʱ��ʱ�ӱ��ִ�״̬��ʱ�䡣 */
        unsigned int  cactive_smmu_cclk_cnt : 6;  /* bit[6-11] : ��������SMMU���Զ��ſ�ʹ��ʱ����TCU����ʱ��ʱ�ӱ��ִ�״̬��ʱ�䡣 */
        unsigned int  reserved              : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_cactive_smmu_bclk_cnt_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_cactive_smmu_bclk_cnt_END    (5)
#define SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_cactive_smmu_cclk_cnt_START  (6)
#define SOC_IVP32_DSP_SUBSYS_SMMU_HW_GT_CNT_cactive_smmu_cclk_cnt_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_UNION
 �ṹ˵��  : SMMU_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x0510����ֵ:0x00000003�����:32
 �Ĵ���˵��: SMMU��TBU��TCU����λʹ�ܡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  brst_smmu_en : 1;  /* bit[0]   : ֻ����üĴ���д1��������λTBU��
                                                       д0���κ����壻 */
        unsigned int  crst_smmu_en : 1;  /* bit[1]   : ֻ����üĴ���д1��������λTCU��
                                                       д0���κ����壻 */
        unsigned int  reserved     : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_brst_smmu_en_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_brst_smmu_en_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_crst_smmu_en_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_EN_crst_smmu_en_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_UNION
 �ṹ˵��  : SMMU_RST_DIS �Ĵ����ṹ���塣��ַƫ����:0x0514����ֵ:0x00000003�����:32
 �Ĵ���˵��: SMMU��TBU��TCU����λ���롣
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  brst_smmu_dis : 1;  /* bit[0]   : ֻ����üĴ���д1�����ܳ���λTBU��λ��
                                                        д0���κ����壻 */
        unsigned int  crst_smmu_dis : 1;  /* bit[1]   : ֻ����üĴ���д1�����ܳ���λTCU��λ��
                                                        д0���κ����壻 */
        unsigned int  reserved      : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_brst_smmu_dis_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_brst_smmu_dis_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_crst_smmu_dis_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_DIS_crst_smmu_dis_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_UNION
 �ṹ˵��  : SMMU_RST_ST �Ĵ����ṹ���塣��ַƫ����:0x0518����ֵ:0x00000003�����:32
 �Ĵ���˵��: SMMU��TBU��TCU����λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  brst_smmu_st : 1;  /* bit[0]   : TBU�ĸ�λ״̬��
                                                       0����λ��Ч��
                                                       1����λ���� */
        unsigned int  crst_smmu_st : 1;  /* bit[1]   : TCU�ĸ�λ״̬��
                                                       0����λ��Ч��
                                                       1����λ���� */
        unsigned int  reserved     : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_brst_smmu_st_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_brst_smmu_st_END    (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_crst_smmu_st_START  (1)
#define SOC_IVP32_DSP_SUBSYS_SMMU_RST_ST_crst_smmu_st_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_SUBSYS_VERSION_NUM_UNION
 �ṹ˵��  : SUBSYS_VERSION_NUM �Ĵ����ṹ���塣��ַƫ����:0x0800����ֵ:0x0304000D�����:32
 �Ĵ���˵��: ��ϵͳ�汾�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  subsys_version_num : 32; /* bit[0-31]: �汾�Ĵ�������汾������¼�İ汾��Ŷ�Ӧ�� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SUBSYS_VERSION_NUM_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SUBSYS_VERSION_NUM_subsys_version_num_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SUBSYS_VERSION_NUM_subsys_version_num_END    (31)




/****************************************************************************
                     (2/2) IVP32_CFG_SEC_REG
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_IVP32_SLV_SEC_SEL_UNION
 �ṹ˵��  : IVP32_SLV_SEC_SEL �Ĵ����ṹ���塣��ַƫ����:0x0300����ֵ:0x00000001�����:32
 �Ĵ���˵��: IVP32 DSP��slave�ӿڵİ�ȫ�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivp32_slv_sec_sel : 1;  /* bit[0]   : ����IVP32 DSP��slave�ӿڵİ�ȫ���ԣ�
                                                            0����ȫ��
                                                            1���ǰ�ȫ */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_IVP32_SLV_SEC_SEL_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_IVP32_SLV_SEC_SEL_ivp32_slv_sec_sel_START  (0)
#define SOC_IVP32_DSP_SUBSYS_IVP32_SLV_SEC_SEL_ivp32_slv_sec_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_UNION
 �ṹ˵��  : IVP32_MST_SEC_SEL �Ĵ����ṹ���塣��ַƫ����:0x0304����ֵ:0x0000000F�����:32
 �Ĵ���˵��: IVP32 DSP��master�ӿڵİ�ȫ�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_rd_sec_sel       : 1;  /* bit[0]   : ����Micro-DMA��ͨ���İ�ȫ���ԣ�
                                                               0����ȫ��
                                                               1���ǰ�ȫ */
        unsigned int  dma_wr_sec_sel       : 1;  /* bit[1]   : ����Micro-DMAдͨ���İ�ȫ���ԣ�
                                                               0����ȫ��
                                                               1���ǰ�ȫ */
        unsigned int  processor_rd_sec_sel : 1;  /* bit[2]   : ����DSP CORE��ͨ���İ�ȫ���ԣ�
                                                               0����ȫ��
                                                               1���ǰ�ȫ */
        unsigned int  process_wr_sec_sel   : 1;  /* bit[3]   : ����DSP COREдͨ���İ�ȫ���ԣ�
                                                               0����ȫ��
                                                               1���ǰ�ȫ */
        unsigned int  reserved             : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_dma_rd_sec_sel_START        (0)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_dma_rd_sec_sel_END          (0)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_dma_wr_sec_sel_START        (1)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_dma_wr_sec_sel_END          (1)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_processor_rd_sec_sel_START  (2)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_processor_rd_sec_sel_END    (2)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_process_wr_sec_sel_START    (3)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_SEC_SEL_process_wr_sec_sel_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_UNION
 �ṹ˵��  : APB_IF_SEC_SEL �Ĵ����ṹ���塣��ַƫ����:0x0308����ֵ:0x000F000F�����:32
 �Ĵ���˵��: APB�ӿ����谲ȫ����ѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timer0_if_sec_sel       : 1;  /* bit[0]    : ����Timer0 APB�ӿڵİ�ȫ���ԣ�
                                                                   0����ȫ��
                                                                   1���ǰ�ȫ */
        unsigned int  timer1_if_sec_sel       : 1;  /* bit[1]    : ����Timer1 APB�ӿڵİ�ȫ���ԣ�
                                                                   0����ȫ��
                                                                   1���ǰ�ȫ */
        unsigned int  wdg_if_sec_sel          : 1;  /* bit[2]    : ����WatchDog APB�ӿڵİ�ȫ���ԣ�
                                                                   0����ȫ��
                                                                   1���ǰ�ȫ */
        unsigned int  cfg_if_sec_sel          : 1;  /* bit[3]    : ����CFG APB�ӿڵİ�ȫ���ԣ�
                                                                   0����ȫ��
                                                                   1���ǰ�ȫ */
        unsigned int  reserved_0              : 12; /* bit[4-15] : ���� */
        unsigned int  timer0_if_sec_sel_wr_en : 1;  /* bit[16]   : timer0_if_sec_sel�Ĵ���дʹ�ܣ�ֻ����д��timer0_if_sec_sel�Ĵ�����ͬʱ�Ը�bitд1���ſ����޸�timer0_if_sec_sel��ֵ */
        unsigned int  timer1_if_sec_sel_wr_en : 1;  /* bit[17]   : timer1_if_sec_sel�Ĵ���дʹ�ܣ�ֻ����д��timer1_if_sec_sel�Ĵ�����ͬʱ�Ը�bitд1���ſ����޸�timer1_if_sec_sel��ֵ */
        unsigned int  wdg_if_sec_sel_wr_en    : 1;  /* bit[18]   : wdg_if_sec_sel�Ĵ���дʹ�ܣ�ֻ����д��wdg_if_sec_sel�Ĵ�����ͬʱ�Ը�bitд1���ſ����޸�wdg_if_sec_sel��ֵ */
        unsigned int  cfg_if_sec_sel_wr_en    : 1;  /* bit[19]   : cfg_if_sec_sel�Ĵ���дʹ�ܣ�ֻ����д��cfg_if_sec_sel�Ĵ�����ͬʱ�Ը�bitд1���ſ����޸�cfg_if_sec_sel��ֵ */
        unsigned int  reserved_1              : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer0_if_sec_sel_START        (0)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer0_if_sec_sel_END          (0)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer1_if_sec_sel_START        (1)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer1_if_sec_sel_END          (1)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_wdg_if_sec_sel_START           (2)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_wdg_if_sec_sel_END             (2)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_cfg_if_sec_sel_START           (3)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_cfg_if_sec_sel_END             (3)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer0_if_sec_sel_wr_en_START  (16)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer0_if_sec_sel_wr_en_END    (16)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer1_if_sec_sel_wr_en_START  (17)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_timer1_if_sec_sel_wr_en_END    (17)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_wdg_if_sec_sel_wr_en_START     (18)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_wdg_if_sec_sel_wr_en_END       (18)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_cfg_if_sec_sel_wr_en_START     (19)
#define SOC_IVP32_DSP_SUBSYS_APB_IF_SEC_SEL_cfg_if_sec_sel_wr_en_END       (19)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_START_REMAP_ADDR_UNION
 �ṹ˵��  : START_REMAP_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0314����ֵ:0x00000E00�����:32
 �Ĵ���˵��: IVP32 DSP SYSTEM��master�ӿڵ�ַremap��ʼ��ַ��̬���á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_remap_addr : 12; /* bit[0-11] : �üĴ�����ֵͨ����IVP32 DSP SYSTEM��master�ӿڵ�ַivp32_dsp_mst_addr_base�ĸ�12bit�Ƚϣ���ѡ��remap��ַ����㣬remap��ַ����Ϊ1MB��
                                                            Ĭ��ֵΪ0xE00����ʾremap����ʼ��ַΪ0xE0000000��
                                                            remap�߼����£�
                                                            if ((ivp32_dsp_mst_addr_base[31:20] >= tart_remap_addr[31:20] ) && (ivp32_dsp_mst_addr_base[31:20] <= start_remap_addr + remap_length) ) 
                                                             ivp32_dsp_mst_addr = ddr_remap_addr + ivp32_dsp_mst_addr_base - start_remap_addr ) else
                                                             ivp32_dsp_mst_addr = ivp32_dsp_mst_addr_base
                                                            ����remap_length��ddr_remap_addr�������еļĴ���������
                                                            ע�⣺
                                                             1.�����DDR����IVP������ҪԼ���üĴ���������ֵ����Ϊ0xe00�����Խ���üĴ�����Ĭ��ֵ��ò�Ҫ�޸ģ�
                                                             2.���Լ���ĵ�ַ��Χ����start_remap_addr + remap_length ������С�ڵ���0xe7f�� */
        unsigned int  reserved         : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_START_REMAP_ADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_START_REMAP_ADDR_start_remap_addr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_START_REMAP_ADDR_start_remap_addr_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_REMAP_LENGTH_UNION
 �ṹ˵��  : REMAP_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x0318����ֵ:0x0000007F�����:32
 �Ĵ���˵��: IVP32 DSP SYSTEM��master�ӿڵ�ַremap��Сѡ��̬���á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remap_length : 8;  /* bit[0-7] : ��������IVP32 DSP SYSTEM��master�ӿڵ�ַremap�Ŀռ��С����λΪ1MB��
                                                       �������ֵΪn���ʾremap�ĵ�ַ��ΧΪ(n+1)MB�� */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_REMAP_LENGTH_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_REMAP_LENGTH_remap_length_START  (0)
#define SOC_IVP32_DSP_SUBSYS_REMAP_LENGTH_remap_length_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_DDR_REMAP_ADDR_UNION
 �ṹ˵��  : DDR_REMAP_ADDR �Ĵ����ṹ���塣��ַƫ����:0x031C����ֵ:0x00000800�����:32
 �Ĵ���˵��: IVP32 DSP SYSTEM��master�ӿڵ�ַremap��DDR�Ļ���ַ��̬���á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddr_remap_addr : 12; /* bit[0-11] : ��������IVP32 DSP SYSTEM��master�ӿڵ�ַremap��DDR�Ļ���ַ������Ϊ1MB��
                                                          Ĭ��ֵΪ0x800����ʾ��IVP32 DSP SYSTEM��master�ӿڵ�ַremap������ַΪ0x800��DDR��ַ�ռ䣻
                                                          ע�⣺
                                                           remap��DDR�ĵ�ַ�ռ䣬��ddr_remap_addr + remap_length ������С�ڵ���0xdff�� */
        unsigned int  reserved       : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_DDR_REMAP_ADDR_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_DDR_REMAP_ADDR_ddr_remap_addr_START  (0)
#define SOC_IVP32_DSP_SUBSYS_DDR_REMAP_ADDR_ddr_remap_addr_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_UNION
 �ṹ˵��  : REMAP_SECURITY_CFG �Ĵ����ṹ���塣��ַƫ����:0x0334����ֵ:0x00000007�����:32
 �Ĵ���˵��: ��ַremap�Ĵ�����ȫ�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_remap_addr_sec_sel : 1;  /* bit[0]   : ddr_remap_addr�Ĵ�����ȫ�������ã�
                                                                   0����ȫ��
                                                                   1���ǰ�ȫ�� */
        unsigned int  remap_length_sec_sel     : 1;  /* bit[1]   : remap_length�Ĵ�����ȫ�������ã�
                                                                   0����ȫ��
                                                                   1���ǰ�ȫ�� */
        unsigned int  ddr_remap_addr_sec_sel   : 1;  /* bit[2]   : start_remap_addr�Ĵ�����ȫ�������ã�
                                                                   0����ȫ��
                                                                   1���ǰ�ȫ�� */
        unsigned int  reserved                 : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_start_remap_addr_sec_sel_START  (0)
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_start_remap_addr_sec_sel_END    (0)
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_remap_length_sec_sel_START      (1)
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_remap_length_sec_sel_END        (1)
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_ddr_remap_addr_sec_sel_START    (2)
#define SOC_IVP32_DSP_SUBSYS_REMAP_SECURITY_CFG_ddr_remap_addr_sec_sel_END      (2)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_UNION
 �ṹ˵��  : IVP32_MST_MID_CFG �Ĵ����ṹ���塣��ַƫ����:0x0338����ֵ:0x00000359�����:32
 �Ĵ���˵��: DSP CORE��Micro-DMA��MID���á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_dsp_core_mid  : 5;  /* bit[0-4]  : ����DSP CORE��MID�� */
        unsigned int  cfg_micro_dma_mid : 5;  /* bit[5-9]  : ����Micro-DMA��MID�� */
        unsigned int  reserved          : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_cfg_dsp_core_mid_START   (0)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_cfg_dsp_core_mid_END     (4)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_cfg_micro_dma_mid_START  (5)
#define SOC_IVP32_DSP_SUBSYS_IVP32_MST_MID_CFG_cfg_micro_dma_mid_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_SMMU_INTEG_SEC_OVERRIDE_UNION
 �ṹ˵��  : SMMU_INTEG_SEC_OVERRIDE �Ĵ����ṹ���塣��ַƫ����:0x051C����ֵ:0x00000001�����:32
 �Ĵ���˵��: SMMU��integ_sec_override�ź����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  integ_sec_override : 1;  /* bit[0]   : SMMU��integ_sec_override�źţ����ڰ�ȫ���ƣ�
                                                             �������Ϊ0��
                                                              a.TBU�ӿڣ�IVP32����DDR���İ�ȫ���Կ��Ա�͸����
                                                             �������Ϊ1����ʱ��Ҫ����spniden�Ĵ���Ϊ0����
                                                              a.���еļ��ɼĴ������Ա��ǰ�ȫ�������ʣ�����ACR�Ĵ�����DEBUG�Ĵ�����
                                                              b.��ȫ���ԼĴ������ɱ����ʣ�
                                                              c.TBU�ӿڣ�IVP32����DDR�������в���������Ϊ�ǰ�ȫ������
                                                             ��ע�����źŵ�ֵ��ֻ����SMMU��λ����ʱ�̱���������λ����������ã�û���κ����塣 */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_INTEG_SEC_OVERRIDE_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_INTEG_SEC_OVERRIDE_integ_sec_override_START  (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_INTEG_SEC_OVERRIDE_integ_sec_override_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IVP32_DSP_SUBSYS_SMMU_SPNIDEN_UNION
 �ṹ˵��  : SMMU_SPNIDEN �Ĵ����ṹ���塣��ַƫ����:0x0520����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU��spniden�źŵ����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spniden  : 1;  /* bit[0]   : SMMU��spniden�źţ����ڰ�ȫ�����������ƣ�
                                                   0�����԰�ȫ�������м�����
                                                   1���԰�ȫ�������м����� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_IVP32_DSP_SUBSYS_SMMU_SPNIDEN_UNION;
#endif
#define SOC_IVP32_DSP_SUBSYS_SMMU_SPNIDEN_spniden_START   (0)
#define SOC_IVP32_DSP_SUBSYS_SMMU_SPNIDEN_spniden_END     (0)






/*****************************************************************************
  8 OTHERS����
*****************************************************************************/



/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_ivp32_dsp_subsys_interface.h */
