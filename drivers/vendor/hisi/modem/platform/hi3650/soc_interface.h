
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_interface.h
  �� �� ��   : ����
  ��    ��   : luoqingquan
  ��������   : 2013��2��5��
  ����޸�   :
  ��������   : soc_interface.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��2��5��
    ��    ��   : luoqingquan
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_INTERFACE_H__
#define __SOC_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/



/****************************************************************************
    1)�������Ͷ���,����ԭʼ�������Ͷ���
    2)���ܰ��������κ�ͷ�ļ�
    3) SOC�ṩ����ַΪ32λ�ģ�������תΪ16λ�ĸ������ʹ��
    BASE_ADDR:         32λ��ַ
    BASE_ADDR_HIGH/LOW:16λ��ַ
 ****************************************************************************/

#ifndef BIT_X
#define BIT_X(num)                          (((unsigned long)0x01) << (num))
#endif


/****************************************************************************
 *                   ������ַ�ռ����ַƫ�ƶ���                             *
 *                                                                          *
 ****************************************************************************/
/* ZSP ����ռ��ַƫ�� */
#define ZSP_ITCM_BASE_ADDR                  ((unsigned long)0x00000000)
#define ZSP_ITCM_BASE_ADDR_HIGH             ((unsigned long)ZSP_ITCM_BASE_ADDR>>16)

/* ZSP ���ݿռ��ַƫ�� */
#define ZSP_DTCM_BASE_ADDR                  ((unsigned long)0x00000000)
#define ZSP_DTCM_BASE_ADDR_HIGH             ((unsigned long)ZSP_DTCM_BASE_ADDR>>16)

/* (W)BBP ��ַƫ�� */
#define WBBP_BASE_ADDR                      (SOC_BBP_WCDMA_BASE_ADDR)
#define WBBP_BASE_ADDR_HIGH                 ((unsigned long)WBBP_BASE_ADDR>>16)

#ifdef INSTANCE_1
/* GBBP ��ַƫ�� */
#define SOC_BBP_GSM_BASE_ADDR               ((unsigned long)SOC_BBP_GSM1_BASE_ADDR)
#define SOC_BBP_GSM_BASE_ADDR_HIGH          ((unsigned long)SOC_BBP_GSM1_BASE_ADDR>>16)

/* GBBP�ǵ���������ַ */
#define SOC_BBP_GSM_ON_BASE_ADDR            ((unsigned long)SOC_BBP_GSM1_ON_BASE_ADDR)
#define SOC_BBP_GSM_ON_BASE_ADDR_HIGH       ((unsigned long)SOC_BBP_GSM1_ON_BASE_ADDR>>16)
#else
/* GBBP ��ַƫ�� */
#define SOC_BBP_GSM_BASE_ADDR               ((unsigned long)SOC_BBP_GSM0_BASE_ADDR)
#define SOC_BBP_GSM_BASE_ADDR_HIGH          ((unsigned long)SOC_BBP_GSM0_BASE_ADDR>>16)

/* GBBP�ǵ���������ַ */
#define SOC_BBP_GSM_ON_BASE_ADDR            ((unsigned long)SOC_BBP_GSM0_ON_BASE_ADDR)
#define SOC_BBP_GSM_ON_BASE_ADDR_HIGH       ((unsigned long)SOC_BBP_GSM0_ON_BASE_ADDR>>16)
#endif

#define GBBP_BASE_ADDR                      (SOC_BBP_GSM_BASE_ADDR)

/* AHB�����ַƫ�� */
#define AHB_BASE_ADDR                       (uwAhbBaseAddr)

#define AHB_BASE_ADDR_HIGH                  ((unsigned long)AHB_BASE_ADDR>>16)

/* BBPCOMM�Ļ���ַ */
#define BBPCOMM_BASE_ADDR                   (SOC_BBP_COMM_BASE_ADDR)

/*UPACC ����ַ*/
#define HSUPA_UPACC_BASE_ADDR               (SOC_UPACC_BASE_ADDR)
#define HSUPA_UPACC_BASE_ADDR_HIGH          ((unsigned long)HSUPA_UPACC_BASE_ADDR>>16)

/* DMA ��ַƫ�� */
#define DMAC_BASE_ADDR                      ((unsigned long)0x20380000)
#define DMAC_BASE_ADDR_HIGH                 ((unsigned long)DMAC_BASE_ADDR>>16)

#define SOC_BASE_ADDR                       HI_SYSCTRL_BASE_ADDR
#define SOC_BASE_ADDR_HIGH                  ((unsigned long)SOC_BASE_ADDR>>16)

/* Ϊ�˺ͱ���оƬͳһ���в���ϵͳ�����ֵ�ַ���Ƶ�AHB�� */
#define SYS_CTRL_ADDRESS                    ( SOC_BASE_ADDR_HIGH )

#define SOC_LP_CFG_ASIC_BASE_ADDR           (0xFFF3F000)
#define SOC_LP_CFG_SIZE                     (0x1000)
#define SOC_PERI_CFG_ASIC_BASE_ADDR         (0xFFF35000)
#define SOC_PERI_CFG_SIZE                   (0x1000)
#define SOC_HARQ_MEM_ASIC_BASE_ADDR         (0xEA000000)
#define SOC_HARQ_MEM_SIZE                   (0x70000)

#if 0
/*********************SSI0 �Ĵ�����ַ****************************************/
#define HAL_SSI0_BASE_ADDR                  ((unsigned long)0x5F061000)
#define HAL_SSI0_BASE_ADDR_HIGH             ((unsigned long)HAL_SSI0_BASE_ADDR>>16)
#endif
#define IPCRIS_BASE_ADDR                    ((unsigned long)0x27054000 )
#define IPCRIS_BASE_ADDR_HIGH               ((unsigned long)IPCRIS_BASE_ADDR>>16)
#define IPCRIS_BASE_ADDR_LOW                (0x4000)

/*APM�������ַ*/
#define APM_BASE_ADDR                       (0x0)    /* _H2ASN_Skip */

#define SOC_TIMER_BASE_ADDR                 ((unsigned long)0x27067000 )

/****************************************************************************
 *                   ������ַ�ռ����ַת����                               *
 *                                                                          *
 ****************************************************************************/
#define SOC_WBBP_CLK_SEL_ADDR               ( SOC_BASE_ADDR + 0x148 )



/*============================DMA���������ŵ�ַ===============================*/
#define DMA_LLI_PARA_HIGH_ADDR                  (AHB_BASE_ADDR_HIGH)



/****************************************************************************
 *                   DSPʹ�õĶ�ʱ������                                    *
 *                                                                          *
 ****************************************************************************/

/******************************************************************************
 ����Timer��ʹ��˵��:
 1.����ʹ�õ�Dual-Timer����ʹ�ã�Ϊ�˺ͱ��б���һ�£�SOC��������Timer
 2.SOC Ŀǰ���������� Dual-Timer����û�з���ʹ��
 3.Ĭ�ϸ�ZSP����һ��Timer,��ͬʱ����8����ʱ����ǰ4��Ϊ32Kʱ�ӣ���4��Ϊ19.2Mʱ��
 4.���ǵ�ϵͳ�ȶ��ԣ�����NMI�ж�����ӦTimer�жϣ�SOCĬ��������Ϊ�ر�
 5.Ϊ�˷����������ά��������������Timer0��Timer1�ı��������ģ��ڲ�ͬ�汾��
   ���оƬ��ͬ��TimerX��Ӧ��ֻҪTimer�Ļ��Ʋ��ı䣬ӳ��Ĺ��̽��������üĴ���
   ��ַ�ı仯��

 ******************************************************************************/

#define ARM_SOC_CPUVIEW_TIMER_VALUE         (0x90003000)    /* CPU View Timer�������������֤����ͨ�� */
#define ARM_SOC_CPUVIEW_TIMER_LOAD          (0x90003000)    /* CPU View Timer�������������֤����ͨ�� */
#define ARM_SOC_CPUVIEW_TIMER_CTRL          (0x90003000)    /* CPU View Timer�������������֤����ͨ�� */






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


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/
extern unsigned int                     uwAhbBaseAddr;


/*****************************************************************************
  10 ��������
*****************************************************************************/






#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_interface.h */


