/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_seceng_s_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:56
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_SECENG_S.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_SECENG_S_INTERFACE_H__
#define __SOC_SECENG_S_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_SECENG_S
 ****************************************************************************/
/* �Ĵ���˵����This register maps the virtual register R0 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP0_UNION */
#define SOC_SECENG_S_MEMORY_MAP0_ADDR(base)           ((base) + (0x00000))

/* �Ĵ���˵����This register maps the virtual register R1 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP1_UNION */
#define SOC_SECENG_S_MEMORY_MAP1_ADDR(base)           ((base) + (0x00004))

/* �Ĵ���˵����This register maps the virtual register R2 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP2_UNION */
#define SOC_SECENG_S_MEMORY_MAP2_ADDR(base)           ((base) + (0x00008))

/* �Ĵ���˵����This register maps the virtual register R3 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP3_UNION */
#define SOC_SECENG_S_MEMORY_MAP3_ADDR(base)           ((base) + (0x0000C))

/* �Ĵ���˵����This register maps the virtual register R4 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP4_UNION */
#define SOC_SECENG_S_MEMORY_MAP4_ADDR(base)           ((base) + (0x00010))

/* �Ĵ���˵����This register maps the virtual register R5 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP5_UNION */
#define SOC_SECENG_S_MEMORY_MAP5_ADDR(base)           ((base) + (0x00014))

/* �Ĵ���˵����This register maps the virtual register R6 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP6_UNION */
#define SOC_SECENG_S_MEMORY_MAP6_ADDR(base)           ((base) + (0x00018))

/* �Ĵ���˵����This register maps the virtual register R7 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP7_UNION */
#define SOC_SECENG_S_MEMORY_MAP7_ADDR(base)           ((base) + (0x0001C))

/* �Ĵ���˵����This register maps the virtual register R8 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP8_UNION */
#define SOC_SECENG_S_MEMORY_MAP8_ADDR(base)           ((base) + (0x00020))

/* �Ĵ���˵����This register maps the virtual register R9 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP9_UNION */
#define SOC_SECENG_S_MEMORY_MAP9_ADDR(base)           ((base) + (0x00024))

/* �Ĵ���˵����This register maps the virtual register R10 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP10_UNION */
#define SOC_SECENG_S_MEMORY_MAP10_ADDR(base)          ((base) + (0x00028))

/* �Ĵ���˵����This register maps the virtual register R11 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP11_UNION */
#define SOC_SECENG_S_MEMORY_MAP11_ADDR(base)          ((base) + (0x0002C))

/* �Ĵ���˵����This register maps the virtual register R12 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP12_UNION */
#define SOC_SECENG_S_MEMORY_MAP12_ADDR(base)          ((base) + (0x00030))

/* �Ĵ���˵����This register maps the virtual register R13 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP13_UNION */
#define SOC_SECENG_S_MEMORY_MAP13_ADDR(base)          ((base) + (0x00034))

/* �Ĵ���˵����This register maps the virtual register R14 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP14_UNION */
#define SOC_SECENG_S_MEMORY_MAP14_ADDR(base)          ((base) + (0x00038))

/* �Ĵ���˵����This register maps the virtual register R15 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP15_UNION */
#define SOC_SECENG_S_MEMORY_MAP15_ADDR(base)          ((base) + (0x0003C))

/* �Ĵ���˵����This register maps the virtual register R16 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP16_UNION */
#define SOC_SECENG_S_MEMORY_MAP16_ADDR(base)          ((base) + (0x00040))

/* �Ĵ���˵����This register maps the virtual register R17 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP17_UNION */
#define SOC_SECENG_S_MEMORY_MAP17_ADDR(base)          ((base) + (0x00044))

/* �Ĵ���˵����This register maps the virtual register R18 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP18_UNION */
#define SOC_SECENG_S_MEMORY_MAP18_ADDR(base)          ((base) + (0x00048))

/* �Ĵ���˵����This register maps the virtual register R19 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP19_UNION */
#define SOC_SECENG_S_MEMORY_MAP19_ADDR(base)          ((base) + (0x0004C))

/* �Ĵ���˵����This register maps the virtual register R20 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP20_UNION */
#define SOC_SECENG_S_MEMORY_MAP20_ADDR(base)          ((base) + (0x00050))

/* �Ĵ���˵����This register maps the virtual register R21 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP21_UNION */
#define SOC_SECENG_S_MEMORY_MAP21_ADDR(base)          ((base) + (0x00054))

/* �Ĵ���˵����This register maps the virtual register R22 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP22_UNION */
#define SOC_SECENG_S_MEMORY_MAP22_ADDR(base)          ((base) + (0x00058))

/* �Ĵ���˵����This register maps the virtual register R23 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP23_UNION */
#define SOC_SECENG_S_MEMORY_MAP23_ADDR(base)          ((base) + (0x0005C))

/* �Ĵ���˵����This register maps the virtual register R24 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP24_UNION */
#define SOC_SECENG_S_MEMORY_MAP24_ADDR(base)          ((base) + (0x00060))

/* �Ĵ���˵����This register maps the virtual register R25 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP25_UNION */
#define SOC_SECENG_S_MEMORY_MAP25_ADDR(base)          ((base) + (0x00064))

/* �Ĵ���˵����This register maps the virtual register R26 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP26_UNION */
#define SOC_SECENG_S_MEMORY_MAP26_ADDR(base)          ((base) + (0x00068))

/* �Ĵ���˵����This register maps the virtual register R27 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP27_UNION */
#define SOC_SECENG_S_MEMORY_MAP27_ADDR(base)          ((base) + (0x0006C))

/* �Ĵ���˵����This register maps the virtual register R28 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP28_UNION */
#define SOC_SECENG_S_MEMORY_MAP28_ADDR(base)          ((base) + (0x00070))

/* �Ĵ���˵����This register maps the virtual register R29 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP29_UNION */
#define SOC_SECENG_S_MEMORY_MAP29_ADDR(base)          ((base) + (0x00074))

/* �Ĵ���˵����This register maps the virtual register R30 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP30_UNION */
#define SOC_SECENG_S_MEMORY_MAP30_ADDR(base)          ((base) + (0x00078))

/* �Ĵ���˵����This register maps the virtual register R31 to a physical address in memory��
   λ����UNION�ṹ:  SOC_SECENG_S_MEMORY_MAP31_UNION */
#define SOC_SECENG_S_MEMORY_MAP31_ADDR(base)          ((base) + (0x0007C))

/* �Ĵ���˵����This register holds the PKA's OPCODE��
   λ����UNION�ṹ:  SOC_SECENG_S_OPCODE_UNION */
#define SOC_SECENG_S_OPCODE_ADDR(base)                ((base) + (0x00080))

/* �Ĵ���˵����This register maps N_NP_T0_T1 to a virtual address��
   λ����UNION�ṹ:  SOC_SECENG_S_N_NP_T0_T1_ADDR_UNION */
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_ADDR(base)       ((base) + (0x00084))

/* �Ĵ���˵����This register holds the PKA pipe status��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_STATUS_UNION */
#define SOC_SECENG_S_PKA_STATUS_ADDR(base)            ((base) + (0x00088))

/* �Ĵ���˵����Writing to this register triggers a software reset of the PKA��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_SW_RESET_UNION */
#define SOC_SECENG_S_PKA_SW_RESET_ADDR(base)          ((base) + (0x0008C))

/* �Ĵ���˵����This register holds the size of the operation��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_L0_UNION */
#define SOC_SECENG_S_PKA_L0_ADDR(base)                ((base) + (0x00090))

/* �Ĵ���˵����This register holds the size of the operation��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_L1_UNION */
#define SOC_SECENG_S_PKA_L1_ADDR(base)                ((base) + (0x00094))

/* �Ĵ���˵����This register holds the size of the operation��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_L2_UNION */
#define SOC_SECENG_S_PKA_L2_ADDR(base)                ((base) + (0x00098))

/* �Ĵ���˵����This register holds the size of the operation��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_L3_UNION */
#define SOC_SECENG_S_PKA_L3_ADDR(base)                ((base) + (0x0009C))

/* �Ĵ���˵����This register holds the size of the operation��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_L4_UNION */
#define SOC_SECENG_S_PKA_L4_ADDR(base)                ((base) + (0x000A0))

/* �Ĵ���˵����This register holds the size of the operation��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_L5_UNION */
#define SOC_SECENG_S_PKA_L5_ADDR(base)                ((base) + (0x000A4))

/* �Ĵ���˵����This register holds the size of the operation��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_L6_UNION */
#define SOC_SECENG_S_PKA_L6_ADDR(base)                ((base) + (0x000A8))

/* �Ĵ���˵����This register holds the size of the operation��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_L7_UNION */
#define SOC_SECENG_S_PKA_L7_ADDR(base)                ((base) + (0x000AC))

/* �Ĵ���˵����This register indicates whether the PKA pipe is ready to receive a new OPCODE��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_PIPE_RDY_UNION */
#define SOC_SECENG_S_PKA_PIPE_RDY_ADDR(base)          ((base) + (0x000B0))

/* �Ĵ���˵����This register indicates whether PKA operation is completed��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_DONE_UNION */
#define SOC_SECENG_S_PKA_DONE_ADDR(base)              ((base) + (0x000B4))

/* �Ĵ���˵����This register defines which PKA FSM monitor is being output��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_MON_SELECT_UNION */
#define SOC_SECENG_S_PKA_MON_SELECT_ADDR(base)        ((base) + (0x000B8))

/* �Ĵ���˵����This register enables/disables all the debug mechanism��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_DEBUG_REG_EN_UNION */
#define SOC_SECENG_S_PKA_DEBUG_REG_EN_ADDR(base)      ((base) + (0x000BC))

/* �Ĵ���˵����This register holds the debug counter's value��
   λ����UNION�ṹ:  SOC_SECENG_S_DEBUG_CNT_ADDR_UNION */
#define SOC_SECENG_S_DEBUG_CNT_ADDR_ADDR(base)        ((base) + (0x000C0))

/* �Ĵ���˵����This register indicates whether the PKA is in halt state��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_DEBUG_HALT_UNION */
#define SOC_SECENG_S_PKA_DEBUG_HALT_ADDR(base)        ((base) + (0x000C8))

/* �Ĵ���˵����This register holds the PKA address' offset��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_MSB_ADDR_UNION */
#define SOC_SECENG_S_PKA_MSB_ADDR_ADDR(base)          ((base) + (0x000CC))

/* �Ĵ���˵����This register holds the PKA monitor bus' register output��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_MON_READ_UNION */
#define SOC_SECENG_S_PKA_MON_READ_ADDR(base)          ((base) + (0x000D0))

/* �Ĵ���˵����Interrupt masking register��
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_IMR_UNION */
#define SOC_SECENG_S_RNG_IMR_ADDR(base)               ((base) + (0x00100))

/* �Ĵ���˵����Status register��
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_ISR_UNION */
#define SOC_SECENG_S_RNG_ISR_ADDR(base)               ((base) + (0x00104))

/* �Ĵ���˵����Interrupt/status bit clear Register��
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_ICR_UNION */
#define SOC_SECENG_S_RNG_ICR_ADDR(base)               ((base) + (0x00108))

/* �Ĵ���˵����This register handles TRNG configuration��
   λ����UNION�ṹ:  SOC_SECENG_S_TRNG_CONFIG_UNION */
#define SOC_SECENG_S_TRNG_CONFIG_ADDR(base)           ((base) + (0x0010C))

/* �Ĵ���˵����This register indicates that the TRNG data is valid��
   λ����UNION�ṹ:  SOC_SECENG_S_TRNG_VALID_UNION */
#define SOC_SECENG_S_TRNG_VALID_ADDR(base)            ((base) + (0x00110))

/* �Ĵ���˵����This register contains the data collected in the TRNG[31_0]��
   λ����UNION�ṹ:  SOC_SECENG_S_EHR_DATA_0_UNION */
#define SOC_SECENG_S_EHR_DATA_0_ADDR(base)            ((base) + (0x00114))

/* �Ĵ���˵����This register contains the data collected in the TRNG[63_32]��
   λ����UNION�ṹ:  SOC_SECENG_S_EHR_DATA_1_UNION */
#define SOC_SECENG_S_EHR_DATA_1_ADDR(base)            ((base) + (0x00118))

/* �Ĵ���˵����This register contains the data collected in the TRNG[95_64]��
   λ����UNION�ṹ:  SOC_SECENG_S_EHR_DATA_2_UNION */
#define SOC_SECENG_S_EHR_DATA_2_ADDR(base)            ((base) + (0x0011C))

/* �Ĵ���˵����This register contains the data collected in the TRNG[127_96]��
   λ����UNION�ṹ:  SOC_SECENG_S_EHR_DATA_3_UNION */
#define SOC_SECENG_S_EHR_DATA_3_ADDR(base)            ((base) + (0x00120))

/* �Ĵ���˵����This register contains the data collected in the TRNG[159_128]��
   λ����UNION�ṹ:  SOC_SECENG_S_EHR_DATA_4_UNION */
#define SOC_SECENG_S_EHR_DATA_4_ADDR(base)            ((base) + (0x00124))

/* �Ĵ���˵����This register contains the data collected in the TRNG[191_160]��
   λ����UNION�ṹ:  SOC_SECENG_S_EHR_DATA_5_UNION */
#define SOC_SECENG_S_EHR_DATA_5_ADDR(base)            ((base) + (0x00128))

/* �Ĵ���˵����This register holds the enable signal for the random source��
   λ����UNION�ṹ:  SOC_SECENG_S_RND_SOURCE_ENABLE_UNION */
#define SOC_SECENG_S_RND_SOURCE_ENABLE_ADDR(base)     ((base) + (0x0012C))

/* �Ĵ���˵����Counts clocks between sampling of random bit��
   λ����UNION�ṹ:  SOC_SECENG_S_SAMPLE_CNT1_UNION */
#define SOC_SECENG_S_SAMPLE_CNT1_ADDR(base)           ((base) + (0x00130))

/* �Ĵ���˵����Statistics about autocorrelation test activations��
   λ����UNION�ṹ:  SOC_SECENG_S_AUTOCORR_STATISTIC_UNION */
#define SOC_SECENG_S_AUTOCORR_STATISTIC_ADDR(base)    ((base) + (0x00134))

/* �Ĵ���˵����Debug regsiter
   λ����UNION�ṹ:  SOC_SECENG_S_TRNG_DEBUG_CONTROL_UNION */
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_ADDR(base)    ((base) + (0x00138))

/* �Ĵ���˵����Generate SW reset solely to RNG block��
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_SW_RESET_UNION */
#define SOC_SECENG_S_RNG_SW_RESET_ADDR(base)          ((base) + (0x00140))

/* �Ĵ���˵����Defines the RNG in debug mode
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_DEBUG_EN_INPUT_UNION */
#define SOC_SECENG_S_RNG_DEBUG_EN_INPUT_ADDR(base)    ((base) + (0x001B4))

/* �Ĵ���˵����RNG busy indication
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_BUSY_UNION */
#define SOC_SECENG_S_RNG_BUSY_ADDR(base)              ((base) + (0x001B8))

/* �Ĵ���˵����Resets the counter of collected bits in the TRNG
   λ����UNION�ṹ:  SOC_SECENG_S_RST_BITS_COUNTER_UNION */
#define SOC_SECENG_S_RST_BITS_COUNTER_ADDR(base)      ((base) + (0x001BC))

/* �Ĵ���˵����This register holds the RNG version
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_VERSION_UNION */
#define SOC_SECENG_S_RNG_VERSION_ADDR(base)           ((base) + (0x001C0))

/* �Ĵ���˵����Writing to this register enables/disables the RNG clock��
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_CLK_ENABLE_UNION */
#define SOC_SECENG_S_RNG_CLK_ENABLE_ADDR(base)        ((base) + (0x001C4))

/* �Ĵ���˵����Writing to this register enables/disables the RNG DMA��
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_DMA_ENABLE_UNION */
#define SOC_SECENG_S_RNG_DMA_ENABLE_ADDR(base)        ((base) + (0x001C8))

/* �Ĵ���˵����This register defines which ring-oscillator length should be used when using the RNG DMA��
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_DMA_SRC_MASK_UNION */
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_ADDR(base)      ((base) + (0x001CC))

/* �Ĵ���˵����This register defines the start address of the DMA for the TRNG data��
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_DMA_SRAM_ADDR_UNION */
#define SOC_SECENG_S_RNG_DMA_SRAM_ADDR_ADDR(base)     ((base) + (0x001D0))

/* �Ĵ���˵����This register defines the number of 192-bits samples that the DMA collects per RNG configuration��
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_DMA_SAMPLES_NUM_UNION */
#define SOC_SECENG_S_RNG_DMA_SAMPLES_NUM_ADDR(base)   ((base) + (0x001D4))

/* �Ĵ���˵����This register defines the maximum number of clock cycles per TRNG collection of 192 samples�� If the number of cycles for a collection exceeds this threshold, TRNG signals an interrupt��
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_WATCHDOG_VAL_UNION */
#define SOC_SECENG_S_RNG_WATCHDOG_VAL_ADDR(base)      ((base) + (0x001D8))

/* �Ĵ���˵����This register holds the RNG DMA status��
   λ����UNION�ṹ:  SOC_SECENG_S_RNG_DMA_STATUS_UNION */
#define SOC_SECENG_S_RNG_DMA_STATUS_ADDR(base)        ((base) + (0x001DC))

/* �Ĵ���˵����The AES clock enable register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_AES_CLK_ENABLE_UNION */
#define SOC_SECENG_S_AES_CLK_ENABLE_ADDR(base)        ((base) + (0x00810))

/* �Ĵ���˵����The DES clock enable register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_DES_CLK_ENABLE_UNION */
#define SOC_SECENG_S_DES_CLK_ENABLE_ADDR(base)        ((base) + (0x00814))

/* �Ĵ���˵����The HASH clock enable register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_HASH_CLK_ENABLE_UNION */
#define SOC_SECENG_S_HASH_CLK_ENABLE_ADDR(base)       ((base) + (0x00818))

/* �Ĵ���˵����The PKA clock enable register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_PKA_CLK_ENABLE_UNION */
#define SOC_SECENG_S_PKA_CLK_ENABLE_ADDR(base)        ((base) + (0x0081C))

/* �Ĵ���˵����DMA_CLK enable register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_DMA_CLK_ENABLE_UNION */
#define SOC_SECENG_S_DMA_CLK_ENABLE_ADDR(base)        ((base) + (0x00820))

/* �Ĵ���˵����The CryptoCell clocks' status register�� If LCS is secure, all engines' clocks are disabled�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_CLK_STATUS_UNION */
#define SOC_SECENG_S_CLK_STATUS_ADDR(base)            ((base) + (0x00824))

/* �Ĵ���˵����Defines the cryptographic flow��
   λ����UNION�ṹ:  SOC_SECENG_S_CRYPTO_CTL_UNION */
#define SOC_SECENG_S_CRYPTO_CTL_ADDR(base)            ((base) + (0x00900))

/* �Ĵ���˵����This register is set when the cryptographic core is busy��
   λ����UNION�ṹ:  SOC_SECENG_S_CRYPTO_BUSY_UNION */
#define SOC_SECENG_S_CRYPTO_BUSY_ADDR(base)           ((base) + (0x00910))

/* �Ĵ���˵����This register is set when the Hash engine is busy��
   λ����UNION�ṹ:  SOC_SECENG_S_HASH_BUSY_UNION */
#define SOC_SECENG_S_HASH_BUSY_ADDR(base)             ((base) + (0x0091C))

/* �Ĵ���˵����This register holds the current CryptoCell version��
   λ����UNION�ṹ:  SOC_SECENG_S_VERSION_UNION */
#define SOC_SECENG_S_VERSION_ADDR(base)               ((base) + (0x00928))

/* �Ĵ���˵����A general RD/WR register�� For Firmware use��
   λ����UNION�ṹ:  SOC_SECENG_S_CONTEXT_ID_UNION */
#define SOC_SECENG_S_CONTEXT_ID_ADDR(base)            ((base) + (0x00930))

/* �Ĵ���˵����This register holds the flow ID of the descriptor that caused that last error��
   λ����UNION�ṹ:  SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO0_UNION */
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO0_ADDR(base) ((base) + (0x00940))

/* �Ĵ���˵����This register holds the flow ID of the descriptor that caused that one-before-last error��
   λ����UNION�ṹ:  SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO1_UNION */
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO1_ADDR(base) ((base) + (0x00944))

/* �Ĵ���˵����This register holds the flow ID of the descriptor that caused that one-before-last error��
   λ����UNION�ṹ:  SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO2_UNION */
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO2_ADDR(base) ((base) + (0x00948))

/* �Ĵ���˵����This register holds the flow ID of the descriptor that caused that one-before-last error��
   λ����UNION�ṹ:  SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO3_UNION */
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO3_ADDR(base) ((base) + (0x0094C))

/* �Ĵ���˵����The Interrupt Request register�� Each bit of this register holds the interrupt status of a single interrupt source��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_RGF_IRR_UNION */
#define SOC_SECENG_S_HOST_RGF_IRR_ADDR(base)          ((base) + (0x00A00))

/* �Ĵ���˵����The Interrupt Mask register. Each bit of this register holds the mask of a single interrupt source.
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_RGF_IMR_UNION */
#define SOC_SECENG_S_HOST_RGF_IMR_ADDR(base)          ((base) + (0x00A04))

/* �Ĵ���˵����Interrupt Clear Register��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_RGF_ICR_UNION */
#define SOC_SECENG_S_HOST_RGF_ICR_ADDR(base)          ((base) + (0x00A08))

/* �Ĵ���˵����This register defines the endianness of the Host-accessible registers��
            NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_RGF_ENDIAN_UNION */
#define SOC_SECENG_S_HOST_RGF_ENDIAN_ADDR(base)       ((base) + (0x00A0C))

/* �Ĵ���˵����Writing to this register generates a general reset to CryptoCell�� This reset takes about 4 core clock cycles�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_RGF_CC_SW_RST_UNION */
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_ADDR(base)    ((base) + (0x00A20))

/* �Ĵ���˵����This register holds the CryptoCell product signature��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_RGF_SIGNATURE_UNION */
#define SOC_SECENG_S_HOST_RGF_SIGNATURE_ADDR(base)    ((base) + (0x00A24))

/* �Ĵ���˵����This register holds the values of CryptoCell's pre-synthesis flags
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_BOOT_UNION */
#define SOC_SECENG_S_HOST_BOOT_ADDR(base)             ((base) + (0x00A28))

/* �Ĵ���˵����Provisioning constant mask
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_PROVISION_CONST_MASK_UNION */
#define SOC_SECENG_S_HOST_PROVISION_CONST_MASK_ADDR(base) ((base) + (0x00A30))

/* �Ĵ���˵����AES hardware key select
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_CRYPTOKEY_SEL_UNION */
#define SOC_SECENG_S_HOST_CRYPTOKEY_SEL_ADDR(base)    ((base) + (0x00A38))

/* �Ĵ���˵����This register defines whether the Host has access to the cry_kernel registers directly (compatibility mode) and not only through the descriptors�� The default value is 0 - no access��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_HOST_CRY_ACCESS_EN_UNION */
#define SOC_SECENG_S_HOST_HOST_CRY_ACCESS_EN_ADDR(base) ((base) + (0x0A44))

/* �Ĵ���˵����The DCU��Debug Control Unit��enable register��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_DCU_EN_UNION */
#define SOC_SECENG_S_HOST_DCU_EN_ADDR(base)           ((base) + (0x0A64))

/* �Ĵ���˵����Secure Timer BIST Kick signal��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_SECURE_TIMER_BIST_KICK_UNION */
#define SOC_SECENG_S_HOST_SECURE_TIMER_BIST_KICK_ADDR(base) ((base) + (0x0A68))

/* �Ĵ���˵����this register holds the Secure Timer BIST result��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_SECURE_TIMER_BIST_VAL_UNION */
#define SOC_SECENG_S_HOST_SECURE_TIMER_BIST_VAL_ADDR(base) ((base) + (0x0A6C))

/* �Ĵ���˵����Writing to this register sets/resets the CryptoCell to Always-On test signal��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_CC_AO_TEST_UNION */
#define SOC_SECENG_S_HOST_CC_AO_TEST_ADDR(base)       ((base) + (0x0A70))

/* �Ĵ���˵����Writing to this register resets the low-resolution Secure Timer (residing in the Always-On model)��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_RST_UNION */
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_RST_ADDR(base) ((base) + (0x0A74))

/* �Ĵ���˵����This register holds the low-resolution Secure Timer value, bits 31:0 (residing in the Always-On model)��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_0_UNION */
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_0_ADDR(base) ((base) + (0x0A78))

/* �Ĵ���˵����This register holds the low-resolution Secure Timer value, bits 63:32 (residing in the Always-On model)��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_1_UNION */
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_1_ADDR(base) ((base) + (0x0A7C))

/* �Ĵ���˵����Writing to this register resets the high-resolution Secure Timer��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_RST_UNION */
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_RST_ADDR(base) ((base) + (0x0A80))

/* �Ĵ���˵����This register holds the high-resolution Secure Timer value, bits 31:0��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_0_UNION */
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_0_ADDR(base) ((base) + (0x0A84))

/* �Ĵ���˵����This register holds the high-resolution Secure Timer value, bits 39:32��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_1_UNION */
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_1_ADDR(base) ((base) + (0x0A88))

/* �Ĵ���˵����This register holds the high-resolution Secure Timer value, bits 31:0��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_0_UNION */
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_0_ADDR(base) ((base) + (0x0A8C))

/* �Ĵ���˵����This register holds the high-resolution Secure Timer value, bits 39:32��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_1_UNION */
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_1_ADDR(base) ((base) + (0x0A90))

/* �Ĵ���˵����This register holds the latched value of the low-resolution Secure Timer, bits 31:0 (latched at reset of high-resolution timer)��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_0_UNION */
#define SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_0_ADDR(base) ((base) + (0x0A94))

/* �Ĵ���˵����This register holds the latched value of the low-resolution Secure Timer, bits 64:32 (latched at reset of high-resolution timer)��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_1_UNION */
#define SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_1_ADDR(base) ((base) + (0x0A98))

/* �Ĵ���˵����reflects HW Defines in the NVM
   λ����UNION�ṹ:  SOC_SECENG_S_NVM_CC_BOOT_UNION */
#define SOC_SECENG_S_NVM_CC_BOOT_ADDR(base)           ((base) + (0x00AA0))

/* �Ĵ���˵����This register serves for indirect access to the NVM�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_AIB_ADDR_REG_UNION */
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_ADDR(base)     ((base) + (0x00AA4))

/* �Ĵ���˵����The write data for AIB transactions should be written to this register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_AIB_WDATA_REG_UNION */
#define SOC_SECENG_S_HOST_AIB_WDATA_REG_ADDR(base)    ((base) + (0x00AA8))

/* �Ĵ���˵����The data for AIB transactions can be read from this register��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_AIB_RDATA_REG_UNION */
#define SOC_SECENG_S_HOST_AIB_RDATA_REG_ADDR(base)    ((base) + (0x00AAC))

/* �Ĵ���˵����This register reflects the fuse_aib_prog_completed input, which indicates that the fuse programming was completed�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_AIB_FUSE_PROG_COMPLETED_UNION */
#define SOC_SECENG_S_AIB_FUSE_PROG_COMPLETED_ADDR(base) ((base) + (0x00AB0))

/* �Ĵ���˵����This register reflects the fuse_aib_ack input, which indicates that the AIB transaction was completed�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_AIB_FUSE_ACK_UNION */
#define SOC_SECENG_S_AIB_FUSE_ACK_ADDR(base)          ((base) + (0x00AB4))

/* �Ĵ���˵����AIB debug status register��
   λ����UNION�ṹ:  SOC_SECENG_S_AIB_DEBUG_STATUS_UNION */
#define SOC_SECENG_S_AIB_DEBUG_STATUS_ADDR(base)      ((base) + (0x00AB8))

/* �Ĵ���˵����Indicates that the LCS register holds a valid value�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_LCS_IS_VALID_UNION */
#define SOC_SECENG_S_LCS_IS_VALID_ADDR(base)          ((base) + (0x00ABC))

/* �Ĵ���˵����Bits [31:0] of the Session key
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_SESSION_KEY0_UNION */
#define SOC_SECENG_S_HOST_SESSION_KEY0_ADDR(base)     ((base) + (0x00AC0))

/* �Ĵ���˵����Bits [63:32] of the Session key
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_SESSION_KEY1_UNION */
#define SOC_SECENG_S_HOST_SESSION_KEY1_ADDR(base)     ((base) + (0x00AC4))

/* �Ĵ���˵����Bits [95:64] of the Session key
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_SESSION_KEY2_UNION */
#define SOC_SECENG_S_HOST_SESSION_KEY2_ADDR(base)     ((base) + (0x00AC8))

/* �Ĵ���˵����Bits [127:96] of the Session key�� Writing to this register also creates a write pulse toward the always-on module��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_SESSION_KEY3_UNION */
#define SOC_SECENG_S_HOST_SESSION_KEY3_ADDR(base)     ((base) + (0x00ACC))

/* �Ĵ���˵����Indication from the always-on register that the session key is valid��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_SEESION_KEY_IS_VALID_UNION */
#define SOC_SECENG_S_HOST_SEESION_KEY_IS_VALID_ADDR(base) ((base) + (0x00AD0))

/* �Ĵ���˵����The lifecycle state register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_LCS_REG_UNION */
#define SOC_SECENG_S_LCS_REG_ADDR(base)               ((base) + (0x00AD4))

/* �Ĵ���˵����Host disable security for the current power cycle��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_CPC_SECURITY_DISABLE_UNION */
#define SOC_SECENG_S_HOST_CPC_SECURITY_DISABLE_ADDR(base) ((base) + (0x00AD8))

/* �Ĵ���˵����The Always-On state counter��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_AO_CC_STATE_COUNTER_UNION */
#define SOC_SECENG_S_HOST_AO_CC_STATE_COUNTER_ADDR(base) ((base) + (0x00ADC))

/* �Ĵ���˵����State counter increment�� Writing any value to this address asserts the CC_AO_STATE_COUNTER_INC outputs for 1 cycle��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_CC_AO_STATE_COUNTER_INC_UNION */
#define SOC_SECENG_S_HOST_CC_AO_STATE_COUNTER_INC_ADDR(base) ((base) + (0x00AE0))

/* �Ĵ���˵����This register reflects the Host AO_CC_IS_SD input from the Always-On that determines the LCS is Secure-Disabled��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_AO_CC_IS_SD_UNION */
#define SOC_SECENG_S_HOST_AO_CC_IS_SD_ADDR(base)      ((base) + (0x00AE4))

/* �Ĵ���˵����This register interface is used to update the RKEK registers when the device is in RMA mode, The RKEK is updated by shifting when MSB word is written first�� After the eighth writing the registers are blocked for further writing�� (write -once)��
   λ����UNION�ṹ:  SOC_SECENG_S_HOST_RMA_RKEK_WR_UNION */
#define SOC_SECENG_S_HOST_RMA_RKEK_WR_ADDR(base)      ((base) + (0x00AE8))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=0��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHT0_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHT0_ADDR(base)    ((base) + (0x00B00))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=0��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHT1_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHT1_ADDR(base)    ((base) + (0x00B04))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=2��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHT2_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHT2_ADDR(base)    ((base) + (0x00B08))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=3��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHT3_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHT3_ADDR(base)    ((base) + (0x00B0C))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=4��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHT4_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHT4_ADDR(base)    ((base) + (0x00B10))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=5��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHT5_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHT5_ADDR(base)    ((base) + (0x00B14))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=8��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHT8_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHT8_ADDR(base)    ((base) + (0x00B20))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=9��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHT9_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHT9_ADDR(base)    ((base) + (0x00B24))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=10��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHT10_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHT10_ADDR(base)   ((base) + (0x00B28))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=11��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHT11_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHT11_ADDR(base)   ((base) + (0x00B2C))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=0 and last indication bit set��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHTLAST0_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST0_ADDR(base) ((base) + (0x00B40))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=1 and last indication bit set��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHTLAST1_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST1_ADDR(base) ((base) + (0x00B44))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=1 and last indication bit set��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHTLAST2_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST2_ADDR(base) ((base) + (0x00B48))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=3 and last indication bit set��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHTLAST3_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST3_ADDR(base) ((base) + (0x00B4C))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=4 and last indication bit set��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHTLAST4_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST4_ADDR(base) ((base) + (0x00B50))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=5 and last indication bit set��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHTLAST5_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST5_ADDR(base) ((base) + (0x00B54))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=8 and last indication bit set��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHTLAST8_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST8_ADDR(base) ((base) + (0x00B60))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=9 and last indication bit set��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHTLAST9_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST9_ADDR(base) ((base) + (0x00B64))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=10 and last indication bit set��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHTLAST10_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST10_ADDR(base) ((base) + (0x00B68))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=11 and last indication bit set��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_INFLIGHTLAST11_UNION */
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST11_ADDR(base) ((base) + (0x00B6C))

/* �Ĵ���˵����This register holds the status of AXI port 0��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_PIDTABLE0_UNION */
#define SOC_SECENG_S_AXIM_PIDTABLE0_ADDR(base)        ((base) + (0x00B70))

/* �Ĵ���˵����This register holds the status of AXI port 1��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_PIDTABLE1_UNION */
#define SOC_SECENG_S_AXIM_PIDTABLE1_ADDR(base)        ((base) + (0x00B74))

/* �Ĵ���˵����This register holds the status of AXI port 2��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_PIDTABLE2_UNION */
#define SOC_SECENG_S_AXIM_PIDTABLE2_ADDR(base)        ((base) + (0x00B78))

/* �Ĵ���˵����This register holds the status of AXI port 3��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_PIDTABLE3_UNION */
#define SOC_SECENG_S_AXIM_PIDTABLE3_ADDR(base)        ((base) + (0x00B7C))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=0��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_COMP0_UNION */
#define SOC_SECENG_S_AXIM_MON_COMP0_ADDR(base)        ((base) + (0x00B80))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=1��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_COMP1_UNION */
#define SOC_SECENG_S_AXIM_MON_COMP1_ADDR(base)        ((base) + (0x00B84))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=2��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_COMP2_UNION */
#define SOC_SECENG_S_AXIM_MON_COMP2_ADDR(base)        ((base) + (0x00B88))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=3��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_COMP3_UNION */
#define SOC_SECENG_S_AXIM_MON_COMP3_ADDR(base)        ((base) + (0x00B8C))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=4��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_COMP4_UNION */
#define SOC_SECENG_S_AXIM_MON_COMP4_ADDR(base)        ((base) + (0x00B90))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=5��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_COMP5_UNION */
#define SOC_SECENG_S_AXIM_MON_COMP5_ADDR(base)        ((base) + (0x00B94))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=8��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_COMP8_UNION */
#define SOC_SECENG_S_AXIM_MON_COMP8_ADDR(base)        ((base) + (0x00BA0))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=9��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_COMP9_UNION */
#define SOC_SECENG_S_AXIM_MON_COMP9_ADDR(base)        ((base) + (0x00BA4))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=10��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_COMP10_UNION */
#define SOC_SECENG_S_AXIM_MON_COMP10_ADDR(base)       ((base) + (0x00BA8))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=11��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_COMP11_UNION */
#define SOC_SECENG_S_AXIM_MON_COMP11_ADDR(base)       ((base) + (0x00BAC))

/* �Ĵ���˵����Maximal latency for read transactions��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_RMAX_UNION */
#define SOC_SECENG_S_AXIM_MON_RMAX_ADDR(base)         ((base) + (0x00BB4))

/* �Ĵ���˵����Minimal latency for read transactions��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_RMIN_UNION */
#define SOC_SECENG_S_AXIM_MON_RMIN_ADDR(base)         ((base) + (0x00BB8))

/* �Ĵ���˵����Maximal latency for write transactions��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_WMAX_UNION */
#define SOC_SECENG_S_AXIM_MON_WMAX_ADDR(base)         ((base) + (0x00BBC))

/* �Ĵ���˵����Minimal latency for write transactions��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_WMIN_UNION */
#define SOC_SECENG_S_AXIM_MON_WMIN_ADDR(base)         ((base) + (0x00BC0))

/* �Ĵ���˵����Error information��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_MON_ERR_UNION */
#define SOC_SECENG_S_AXIM_MON_ERR_ADDR(base)          ((base) + (0x00BC4))

/* �Ĵ���˵����read channel status��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_RDSTAT_UNION */
#define SOC_SECENG_S_AXIM_RDSTAT_ADDR(base)           ((base) + (0x00BC8))

/* �Ĵ���˵����Accumulated read latency��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_RLATENCY_UNION */
#define SOC_SECENG_S_AXIM_RLATENCY_ADDR(base)         ((base) + (0x00BD0))

/* �Ĵ���˵����Accumulated read bursts��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_RBURST_UNION */
#define SOC_SECENG_S_AXIM_RBURST_ADDR(base)           ((base) + (0x00BD4))

/* �Ĵ���˵����Accumulated write latency��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_WLATENCY_UNION */
#define SOC_SECENG_S_AXIM_WLATENCY_ADDR(base)         ((base) + (0x00BD8))

/* �Ĵ���˵����Accumulated write bursts��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_WBURST_UNION */
#define SOC_SECENG_S_AXIM_WBURST_ADDR(base)           ((base) + (0x00BDC))

/* �Ĵ���˵����AXI master cache-type configuration��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_CACHETYPE_CFG_UNION */
#define SOC_SECENG_S_AXIM_CACHETYPE_CFG_ADDR(base)    ((base) + (0x00BE0))

/* �Ĵ���˵����AXIM Protection field configuration��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_PROT_CFG_UNION */
#define SOC_SECENG_S_AXIM_PROT_CFG_ADDR(base)         ((base) + (0x00BE4))

/* �Ĵ���˵����AXI master configuration��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_CFG1_UNION */
#define SOC_SECENG_S_AXIM_CFG1_ADDR(base)             ((base) + (0x00BE8))

/* �Ĵ���˵����AXIM ACE CONST��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_ACE_CONST_UNION */
#define SOC_SECENG_S_AXIM_ACE_CONST_ADDR(base)        ((base) + (0x00BEC))

/* �Ĵ���˵����AXI master configuration for DMA��
   λ����UNION�ṹ:  SOC_SECENG_S_AXIM_CACHE_PARAMS_UNION */
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_ADDR(base)     ((base) + (0x00BF0))

/* �Ĵ���˵����Control AXI master��
   λ����UNION�ṹ:  SOC_SECENG_S_ADDR_AXIM_CTRL_UNION */
#define SOC_SECENG_S_ADDR_AXIM_CTRL_ADDR(base)        ((base) + (0x00BF4))

/* �Ĵ���˵����This address can be used by the CPU to write data directly to the DIN buffer to be sent to engines��
   λ����UNION�ṹ:  SOC_SECENG_S_DIN_BUFFER_UNION */
#define SOC_SECENG_S_DIN_BUFFER_ADDR(base)            ((base) + (0x00C00))

/* �Ĵ���˵����Indicates whether memory (AXI) source DMA (DIN) is busy��
   λ����UNION�ṹ:  SOC_SECENG_S_DIN_MEM_DMA_BUSY_UNION */
#define SOC_SECENG_S_DIN_MEM_DMA_BUSY_ADDR(base)      ((base) + (0x00C20))

/* �Ĵ���˵����Location of LLI table located in the SRAM�� in SINGLE/MULTI_LLI mode, writing to this register triggers the DMA�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_SRC_LLI_SRAM_ADDR_UNION */
#define SOC_SECENG_S_SRC_LLI_SRAM_ADDR_ADDR(base)     ((base) + (0x00C24))

/* �Ĵ���˵����This register is used in direct LLI mode - holds the location of the data source in the memory (AXI)��
   λ����UNION�ṹ:  SOC_SECENG_S_SRC_LLI_WORD0_UNION */
#define SOC_SECENG_S_SRC_LLI_WORD0_ADDR(base)         ((base) + (0x00C28))

/* �Ĵ���˵����This register is used in direct LLI mode - holds the number of bytes to be read from the memory (AXI)�� Writing to this register triggers the DMA�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_SRC_LLI_WORD1_UNION */
#define SOC_SECENG_S_SRC_LLI_WORD1_ADDR(base)         ((base) + (0x00C2C))

/* �Ĵ���˵����Location of data (start address) to be read from SRAM�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_SRAM_SRC_ADDR_UNION */
#define SOC_SECENG_S_SRAM_SRC_ADDR_ADDR(base)         ((base) + (0x00C30))

/* �Ĵ���˵����This register holds the size of the data (in bytes) to be read from the SRAM�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_DIN_SRAM_BYTES_LEN_UNION */
#define SOC_SECENG_S_DIN_SRAM_BYTES_LEN_ADDR(base)    ((base) + (0x00C34))

/* �Ĵ���˵����This register holds the status of the SRAM DMA DIN��
   λ����UNION�ṹ:  SOC_SECENG_S_DIN_SRAM_DMA_BUSY_UNION */
#define SOC_SECENG_S_DIN_SRAM_DMA_BUSY_ADDR(base)     ((base) + (0x00C38))

/* �Ĵ���˵����This register defines the endianness of the DIN interface to SRAM��
   λ����UNION�ṹ:  SOC_SECENG_S_DIN_SRAM_ENDIANNESS_UNION */
#define SOC_SECENG_S_DIN_SRAM_ENDIANNESS_ADDR(base)   ((base) + (0x00C3C))

/* �Ĵ���˵����This register holds RDID and PROT when using the CPU��
   λ����UNION�ṹ:  SOC_SECENG_S_AXI_CPU_DIN_PARAMS_UNION */
#define SOC_SECENG_S_AXI_CPU_DIN_PARAMS_ADDR(base)    ((base) + (0x00C40))

/* �Ĵ���˵����DIN software reset��
   λ����UNION�ṹ:  SOC_SECENG_S_DIN_SW_RESET_UNION */
#define SOC_SECENG_S_DIN_SW_RESET_ADDR(base)          ((base) + (0x00C44))

/* �Ĵ���˵����Data path to DIN is OTF��
   λ����UNION�ṹ:  SOC_SECENG_S_DIN_CPU_DATA_SIZE_UNION */
#define SOC_SECENG_S_DIN_CPU_DATA_SIZE_ADDR(base)     ((base) + (0x0C48))

/* �Ĵ���˵����Indication that the next write from the CPU is the last one�� This is needed only when the data size is NOT modulo 4 (e.g. HASH padding)��
   λ����UNION�ṹ:  SOC_SECENG_S_WRITE_ALIGN_LAST_UNION */
#define SOC_SECENG_S_WRITE_ALIGN_LAST_ADDR(base)      ((base) + (0x00C4C))

/* �Ĵ���˵����DIN FIFO empty indication��
   λ����UNION�ṹ:  SOC_SECENG_S_FIFO_IN_EMPTY_UNION */
#define SOC_SECENG_S_FIFO_IN_EMPTY_ADDR(base)         ((base) + (0x00C50))

/* �Ĵ���˵����Disables the outstanding DIN request��
   λ����UNION�ṹ:  SOC_SECENG_S_DISABLE_OUTSTD_REQ_UNION */
#define SOC_SECENG_S_DISABLE_OUTSTD_REQ_ADDR(base)    ((base) + (0x00C54))

/* �Ĵ���˵����Writing to this register resets the DIN_FIFO pointers��
   λ����UNION�ṹ:  SOC_SECENG_S_DIN_FIFO_RST_PNTR_UNION */
#define SOC_SECENG_S_DIN_FIFO_RST_PNTR_ADDR(base)     ((base) + (0x00C58))

/* �Ĵ���˵����Cryptographic result - CPU can directly access it�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_DOUT_BUFFER_UNION */
#define SOC_SECENG_S_DOUT_BUFFER_ADDR(base)           ((base) + (0x00D00))

/* �Ĵ���˵����DOUT memory DMA busy - Indicates that memory (AXI) destination DMA (DOUT) is busy��
   λ����UNION�ṹ:  SOC_SECENG_S_DOUT_MEM_DMA_BUSY_UNION */
#define SOC_SECENG_S_DOUT_MEM_DMA_BUSY_ADDR(base)     ((base) + (0x00D20))

/* �Ĵ���˵����This register holds the destination LLI table address in SRAM�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_DST_LLI_SRAM_ADDR_UNION */
#define SOC_SECENG_S_DST_LLI_SRAM_ADDR_ADDR(base)     ((base) + (0x00D24))

/* �Ĵ���˵����This register is used in direct LLI mode - holds the location of the data destination in the memory (AXI)
   λ����UNION�ṹ:  SOC_SECENG_S_DST_LLI_WORD0_UNION */
#define SOC_SECENG_S_DST_LLI_WORD0_ADDR(base)         ((base) + (0x00D28))

/* �Ĵ���˵����This register is used in direct LLI mode - holds the number of bytes to be written to the memory (AXI)��
   λ����UNION�ṹ:  SOC_SECENG_S_DST_LLI_WORD1_UNION */
#define SOC_SECENG_S_DST_LLI_WORD1_ADDR(base)         ((base) + (0x00D2C))

/* �Ĵ���˵����Location of result to be sent to in SRAM NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_SRAM_DEST_ADDR_UNION */
#define SOC_SECENG_S_SRAM_DEST_ADDR_ADDR(base)        ((base) + (0x00D30))

/* �Ĵ���˵����This register holds the size of the data (in bytes) to be written to the SRAM�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_DOUT_SRAM_BYTES_LEN_UNION */
#define SOC_SECENG_S_DOUT_SRAM_BYTES_LEN_ADDR(base)   ((base) + (0x00D34))

/* �Ĵ���˵����This register holds the status of the SRAM DMA DOUT��
   λ����UNION�ṹ:  SOC_SECENG_S_DOUT_SRAM_DMA_BUSY_UNION */
#define SOC_SECENG_S_DOUT_SRAM_DMA_BUSY_ADDR(base)    ((base) + (0x00D38))

/* �Ĵ���˵����This register defines the endianness of the DOUT interface from SRAM��
   λ����UNION�ṹ:  SOC_SECENG_S_DOUT_SRAM_ENDIANNESS_UNION */
#define SOC_SECENG_S_DOUT_SRAM_ENDIANNESS_ADDR(base)  ((base) + (0x00D3C))

/* �Ĵ���˵����Indication that the next read from the CPU is the last one�� This is needed only when the data size is NOT modulo 4 (e.g. HASH padding)��
   λ����UNION�ṹ:  SOC_SECENG_S_READ_ALIGN_LAST_UNION */
#define SOC_SECENG_S_READ_ALIGN_LAST_ADDR(base)       ((base) + (0x00D44))

/* �Ĵ���˵����DOUT_FIFO_EMPTY Register��
   λ����UNION�ṹ:  SOC_SECENG_S_DOUT_FIFO_EMPTY_UNION */
#define SOC_SECENG_S_DOUT_FIFO_EMPTY_ADDR(base)       ((base) + (0x00D50))

/* �Ĵ���˵����AXI_CPU_DOUT_PARAMS Register��
   λ����UNION�ṹ:  SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_UNION */
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_ADDR(base)   ((base) + (0x00D54))

/* �Ĵ���˵����Software reset for DOUT��
   λ����UNION�ṹ:  SOC_SECENG_S_DOUT_SW_RESET_UNION */
#define SOC_SECENG_S_DOUT_SW_RESET_ADDR(base)         ((base) + (0x00D58))

/* �Ĵ���˵����This register counts the number of completed descriptors in which the ACK_NEEDED field equals 1��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_UNION */
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_ADDR(base) ((base) + (0x00E00))

/* �Ĵ���˵����This register counts the number of completed descriptors in which the ACK_NEEDED field equals 2��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_UNION */
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_ADDR(base) ((base) + (0x00E04))

/* �Ĵ���˵����This register holds the status of the completion counters��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_COMPLETION_STATUS_UNION */
#define SOC_SECENG_S_DSCRPTR_COMPLETION_STATUS_ADDR(base) ((base) + (0x00E3C))

/* �Ĵ���˵����Software reset for descriptors��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_SW_RESET_UNION */
#define SOC_SECENG_S_DSCRPTR_SW_RESET_ADDR(base)      ((base) + (0x00E40))

/* �Ĵ���˵����This register enables the use of special descriptors��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_DEBUG_MODE_UNION */
#define SOC_SECENG_S_DSCRPTR_DEBUG_MODE_ADDR(base)    ((base) + (0x00E4C))

/* �Ĵ���˵����This register enables the Host to write a descriptor using a single address��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_SINGLE_ADDR_EN_UNION */
#define SOC_SECENG_S_DSCRPTR_SINGLE_ADDR_EN_ADDR(base) ((base) + (0x0E64))

/* �Ĵ���˵����This register holds the number of cycles measured when using the special performance descriptor��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_MEASURE_CNTR_UNION */
#define SOC_SECENG_S_DSCRPTR_MEASURE_CNTR_ADDR(base)  ((base) + (0x0E68))

/* �Ĵ���˵����This register holds the upper 16bits of the address to which CryptoCell writes when descriptor does not comply with restriction��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_UNION */
#define SOC_SECENG_S_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_ADDR(base) ((base) + (0x0E6C))

/* �Ĵ���˵����This register holds word0 of the descriptor��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_QUEUE0_WORD0_UNION */
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD0_ADDR(base)  ((base) + (0x00E80))

/* �Ĵ���˵����This register holds word1 of the descriptor��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_UNION */
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_ADDR(base)  ((base) + (0x00E84))

/* �Ĵ���˵����This register holds word2 of the descriptor��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_QUEUE0_WORD2_UNION */
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD2_ADDR(base)  ((base) + (0x00E88))

/* �Ĵ���˵����This register holds word3 of the descriptor��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_UNION */
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_ADDR(base)  ((base) + (0x00E8C))

/* �Ĵ���˵����This register holds word4 of the descripto��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_UNION */
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_ADDR(base)  ((base) + (0x00E90))

/* �Ĵ���˵����This register holds word5 of the descriptor��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_UNION */
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_ADDR(base)  ((base) + (0x00E94))

/* �Ĵ���˵����This register holds the watermark value of descriptor queue0��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_QUEUE0_WATERMARK_UNION */
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WATERMARK_ADDR(base) ((base) + (0x00E98))

/* �Ĵ���˵����This register holds the number of empty entries in descriptor queue0��
   λ����UNION�ṹ:  SOC_SECENG_S_DSCRPTR_QUEUE0_CONTENT_UNION */
#define SOC_SECENG_S_DSCRPTR_QUEUE0_CONTENT_ADDR(base) ((base) + (0x00E9C))

/* �Ĵ���˵����READ WRITE DATA FROM SRAM NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
   λ����UNION�ṹ:  SOC_SECENG_S_SRAM_DATA_UNION */
#define SOC_SECENG_S_SRAM_DATA_ADDR(base)             ((base) + (0x00F00))

/* �Ĵ���˵����first address given to SRAM DMA for read/write transactions from SRAM��
   λ����UNION�ṹ:  SOC_SECENG_S_SRAM_ADDR_UNION */
#define SOC_SECENG_S_SRAM_ADDR_ADDR(base)             ((base) + (0x00F04))

/* �Ĵ���˵����sram data ready��
   λ����UNION�ṹ:  SOC_SECENG_S_SRAM_DATA_READY_UNION */
#define SOC_SECENG_S_SRAM_DATA_READY_ADDR(base)       ((base) + (0x00F08))





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
                     (1/1) register_SECENG_S
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP0_UNION
 �ṹ˵��  : MEMORY_MAP0 �Ĵ����ṹ���塣��ַƫ����:0x00000����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R0 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map0 : 10; /* bit[2-11] : Memory map 0,
                                                       Contains the physical address in memory to map the R0 register to. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP0_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP0_memory_map0_START  (2)
#define SOC_SECENG_S_MEMORY_MAP0_memory_map0_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP1_UNION
 �ṹ˵��  : MEMORY_MAP1 �Ĵ����ṹ���塣��ַƫ����:0x00004����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R1 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map1 : 10; /* bit[2-11] : Memory map 1,
                                                       Contains the physical address in memory to map the R1 register to. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP1_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP1_memory_map1_START  (2)
#define SOC_SECENG_S_MEMORY_MAP1_memory_map1_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP2_UNION
 �ṹ˵��  : MEMORY_MAP2 �Ĵ����ṹ���塣��ַƫ����:0x00008����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R2 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map2 : 10; /* bit[2-11] : Memory map 2,
                                                       Contains the physical address in memory to map the R2 register to. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP2_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP2_memory_map2_START  (2)
#define SOC_SECENG_S_MEMORY_MAP2_memory_map2_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP3_UNION
 �ṹ˵��  : MEMORY_MAP3 �Ĵ����ṹ���塣��ַƫ����:0x0000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R3 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map3 : 10; /* bit[2-11] : Memory map 3,
                                                       Contains the physical address in memory to map the R3 register to. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP3_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP3_memory_map3_START  (2)
#define SOC_SECENG_S_MEMORY_MAP3_memory_map3_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP4_UNION
 �ṹ˵��  : MEMORY_MAP4 �Ĵ����ṹ���塣��ַƫ����:0x00010����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R4 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map4 : 10; /* bit[2-11] : Memory map 4,
                                                       Contains the physical address in memory to map the R4 register to. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP4_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP4_memory_map4_START  (2)
#define SOC_SECENG_S_MEMORY_MAP4_memory_map4_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP5_UNION
 �ṹ˵��  : MEMORY_MAP5 �Ĵ����ṹ���塣��ַƫ����:0x00014����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R5 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map5 : 10; /* bit[2-11] : Memory map 5,
                                                       Contains the physical address in memory to map the R5 register to. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP5_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP5_memory_map5_START  (2)
#define SOC_SECENG_S_MEMORY_MAP5_memory_map5_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP6_UNION
 �ṹ˵��  : MEMORY_MAP6 �Ĵ����ṹ���塣��ַƫ����:0x00018����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R6 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map6 : 10; /* bit[2-11] : Memory map 6,
                                                       Contains the physical address in memory to map the R6 register to. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP6_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP6_memory_map6_START  (2)
#define SOC_SECENG_S_MEMORY_MAP6_memory_map6_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP7_UNION
 �ṹ˵��  : MEMORY_MAP7 �Ĵ����ṹ���塣��ַƫ����:0x0001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R7 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map7 : 10; /* bit[2-11] : Memory map 7,
                                                       Contains the physical address in memory to map the R7 register to. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP7_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP7_memory_map7_START  (2)
#define SOC_SECENG_S_MEMORY_MAP7_memory_map7_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP8_UNION
 �ṹ˵��  : MEMORY_MAP8 �Ĵ����ṹ���塣��ַƫ����:0x00020����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R8 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map8 : 10; /* bit[2-11] : Memory map 8,
                                                       Contains the physical address in memory to map the R8 register to. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP8_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP8_memory_map8_START  (2)
#define SOC_SECENG_S_MEMORY_MAP8_memory_map8_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP9_UNION
 �ṹ˵��  : MEMORY_MAP9 �Ĵ����ṹ���塣��ַƫ����:0x00024����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R9 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map9 : 10; /* bit[2-11] : Memory map 9,
                                                       Contains the physical address in memory to map the R9 register to. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP9_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP9_memory_map9_START  (2)
#define SOC_SECENG_S_MEMORY_MAP9_memory_map9_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP10_UNION
 �ṹ˵��  : MEMORY_MAP10 �Ĵ����ṹ���塣��ַƫ����:0x00028����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R10 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map10 : 10; /* bit[2-11] : Memory map 10,
                                                        Contains the physical address in memory to map the R10 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP10_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP10_memory_map10_START  (2)
#define SOC_SECENG_S_MEMORY_MAP10_memory_map10_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP11_UNION
 �ṹ˵��  : MEMORY_MAP11 �Ĵ����ṹ���塣��ַƫ����:0x0002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R11 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map11 : 10; /* bit[2-11] : Memory map 11,
                                                        Contains the physical address in memory to map the R11 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP11_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP11_memory_map11_START  (2)
#define SOC_SECENG_S_MEMORY_MAP11_memory_map11_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP12_UNION
 �ṹ˵��  : MEMORY_MAP12 �Ĵ����ṹ���塣��ַƫ����:0x00030����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R12 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map12 : 10; /* bit[2-11] : Memory map 12,
                                                        Contains the physical address in memory to map the R12 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP12_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP12_memory_map12_START  (2)
#define SOC_SECENG_S_MEMORY_MAP12_memory_map12_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP13_UNION
 �ṹ˵��  : MEMORY_MAP13 �Ĵ����ṹ���塣��ַƫ����:0x00034����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R13 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map13 : 10; /* bit[2-11] : Memory map 13,
                                                        Contains the physical address in memory to map the R13 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP13_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP13_memory_map13_START  (2)
#define SOC_SECENG_S_MEMORY_MAP13_memory_map13_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP14_UNION
 �ṹ˵��  : MEMORY_MAP14 �Ĵ����ṹ���塣��ַƫ����:0x00038����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R14 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map14 : 10; /* bit[2-11] : Memory map 14,
                                                        Contains the physical address in memory to map the R14 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP14_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP14_memory_map14_START  (2)
#define SOC_SECENG_S_MEMORY_MAP14_memory_map14_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP15_UNION
 �ṹ˵��  : MEMORY_MAP15 �Ĵ����ṹ���塣��ַƫ����:0x0003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R15 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map15 : 10; /* bit[2-11] : Memory map 15,
                                                        Contains the physical address in memory to map the R15 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP15_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP15_memory_map15_START  (2)
#define SOC_SECENG_S_MEMORY_MAP15_memory_map15_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP16_UNION
 �ṹ˵��  : MEMORY_MAP16 �Ĵ����ṹ���塣��ַƫ����:0x00040����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R16 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map16 : 10; /* bit[2-11] : Memory map 16,
                                                        Contains the physical address in memory to map the R16 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP16_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP16_memory_map16_START  (2)
#define SOC_SECENG_S_MEMORY_MAP16_memory_map16_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP17_UNION
 �ṹ˵��  : MEMORY_MAP17 �Ĵ����ṹ���塣��ַƫ����:0x00044����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R17 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map17 : 10; /* bit[2-11] : Memory map 17,
                                                        Contains the physical address in memory to map the R17 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP17_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP17_memory_map17_START  (2)
#define SOC_SECENG_S_MEMORY_MAP17_memory_map17_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP18_UNION
 �ṹ˵��  : MEMORY_MAP18 �Ĵ����ṹ���塣��ַƫ����:0x00048����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R18 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map18 : 10; /* bit[2-11] : Memory map 18,
                                                        Contains the physical address in memory to map the R18 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP18_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP18_memory_map18_START  (2)
#define SOC_SECENG_S_MEMORY_MAP18_memory_map18_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP19_UNION
 �ṹ˵��  : MEMORY_MAP19 �Ĵ����ṹ���塣��ַƫ����:0x0004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R19 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map19 : 10; /* bit[2-11] : Memory map 19,
                                                        Contains the physical address in memory to map the R19 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP19_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP19_memory_map19_START  (2)
#define SOC_SECENG_S_MEMORY_MAP19_memory_map19_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP20_UNION
 �ṹ˵��  : MEMORY_MAP20 �Ĵ����ṹ���塣��ַƫ����:0x00050����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R20 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map20 : 10; /* bit[2-11] : Memory map 20,
                                                        Contains the physical address in memory to map the R20 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP20_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP20_memory_map20_START  (2)
#define SOC_SECENG_S_MEMORY_MAP20_memory_map20_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP21_UNION
 �ṹ˵��  : MEMORY_MAP21 �Ĵ����ṹ���塣��ַƫ����:0x00054����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R21 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map21 : 10; /* bit[2-11] : Memory map 21,
                                                        Contains the physical address in memory to map the R21 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP21_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP21_memory_map21_START  (2)
#define SOC_SECENG_S_MEMORY_MAP21_memory_map21_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP22_UNION
 �ṹ˵��  : MEMORY_MAP22 �Ĵ����ṹ���塣��ַƫ����:0x00058����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R22 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map22 : 10; /* bit[2-11] : Memory map 22,
                                                        Contains the physical address in memory to map the R22 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP22_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP22_memory_map22_START  (2)
#define SOC_SECENG_S_MEMORY_MAP22_memory_map22_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP23_UNION
 �ṹ˵��  : MEMORY_MAP23 �Ĵ����ṹ���塣��ַƫ����:0x0005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R23 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map23 : 10; /* bit[2-11] : Memory map 23,
                                                        Contains the physical address in memory to map the R23 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP23_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP23_memory_map23_START  (2)
#define SOC_SECENG_S_MEMORY_MAP23_memory_map23_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP24_UNION
 �ṹ˵��  : MEMORY_MAP24 �Ĵ����ṹ���塣��ַƫ����:0x00060����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R24 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map24 : 10; /* bit[2-11] : Memory map 24,
                                                        Contains the physical address in memory to map the R24 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP24_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP24_memory_map24_START  (2)
#define SOC_SECENG_S_MEMORY_MAP24_memory_map24_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP25_UNION
 �ṹ˵��  : MEMORY_MAP25 �Ĵ����ṹ���塣��ַƫ����:0x00064����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R25 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map25 : 10; /* bit[2-11] : Memory map 25,
                                                        Contains the physical address in memory to map the R25 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP25_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP25_memory_map25_START  (2)
#define SOC_SECENG_S_MEMORY_MAP25_memory_map25_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP26_UNION
 �ṹ˵��  : MEMORY_MAP26 �Ĵ����ṹ���塣��ַƫ����:0x00068����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R26 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map26 : 10; /* bit[2-11] : Memory map 26,
                                                        Contains the physical address in memory to map the R26 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP26_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP26_memory_map26_START  (2)
#define SOC_SECENG_S_MEMORY_MAP26_memory_map26_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP27_UNION
 �ṹ˵��  : MEMORY_MAP27 �Ĵ����ṹ���塣��ַƫ����:0x0006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R27 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map27 : 10; /* bit[2-11] : Memory map 27,
                                                        Contains the physical address in memory to map the R27 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP27_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP27_memory_map27_START  (2)
#define SOC_SECENG_S_MEMORY_MAP27_memory_map27_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP28_UNION
 �ṹ˵��  : MEMORY_MAP28 �Ĵ����ṹ���塣��ַƫ����:0x00070����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R28 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map28 : 10; /* bit[2-11] : Memory map 28,
                                                        Contains the physical address in memory to map the R28 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP28_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP28_memory_map28_START  (2)
#define SOC_SECENG_S_MEMORY_MAP28_memory_map28_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP29_UNION
 �ṹ˵��  : MEMORY_MAP29 �Ĵ����ṹ���塣��ַƫ����:0x00074����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R29 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map29 : 10; /* bit[2-11] : Memory map 29,
                                                        Contains the physical address in memory to map the R29 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP29_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP29_memory_map29_START  (2)
#define SOC_SECENG_S_MEMORY_MAP29_memory_map29_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP30_UNION
 �ṹ˵��  : MEMORY_MAP30 �Ĵ����ṹ���塣��ַƫ����:0x00078����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R30 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map30 : 10; /* bit[2-11] : Memory map 30,
                                                        Contains the physical address in memory to map the R30 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP30_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP30_memory_map30_START  (2)
#define SOC_SECENG_S_MEMORY_MAP30_memory_map30_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_MEMORY_MAP31_UNION
 �ṹ˵��  : MEMORY_MAP31 �Ĵ����ṹ���塣��ַƫ����:0x0007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register maps the virtual register R31 to a physical address in memory��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 2;  /* bit[0-1]  : ���� */
        unsigned int  memory_map31 : 10; /* bit[2-11] : Memory map 31,
                                                        Contains the physical address in memory to map the R31 register to. */
        unsigned int  reserved_1   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_MEMORY_MAP31_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP31_memory_map31_START  (2)
#define SOC_SECENG_S_MEMORY_MAP31_memory_map31_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_OPCODE_UNION
 �ṹ˵��  : OPCODE �Ĵ����ṹ���塣��ַƫ����:0x00080����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the PKA's OPCODE��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tag    : 6;  /* bit[0-5]  : Holds the operation's tag. */
        unsigned int  reg_r  : 6;  /* bit[6-11] : result register virtual address 0-15 */
        unsigned int  reg_b  : 6;  /* bit[12-17]: operand B virtual address 0-15 */
        unsigned int  reg_a  : 6;  /* bit[18-23]: operand A virtual address 0-15 */
        unsigned int  len    : 3;  /* bit[24-26]: The length of the operation. The value serves as a pointer to PKA length register, for example, if the value is 0, PKA_L0 holds the size of the operation. */
        unsigned int  opcode : 5;  /* bit[27-31]: Defines the PKA operation 
                                                  0x4 Add,Inc 
                                                  0x5 Sub,Dec,Neg
                                                  0x6 ModAdd,ModInc
                                                  0x7 ModSub,ModDec,ModNeg
                                                  0x8 AND,TST0,CLR0
                                                  0x9 OR,COPY,SET0
                                                  0xa XOR,FLIP0,INVERT,COMPARE 
                                                  0xc SHR0
                                                  0xd SHR1
                                                  0xe SHL0
                                                  0xf SHL1
                                                  0x10 MulLow
                                                  0x11 ModMul
                                                  0x12 ModMulN
                                                  0x13 ModExp
                                                  0x14 Division 
                                                  0x15 Div
                                                  0x16 ModDiv
                                                  0x00 Terminate  */
    } reg;
} SOC_SECENG_S_OPCODE_UNION;
#endif
#define SOC_SECENG_S_OPCODE_tag_START     (0)
#define SOC_SECENG_S_OPCODE_tag_END       (5)
#define SOC_SECENG_S_OPCODE_reg_r_START   (6)
#define SOC_SECENG_S_OPCODE_reg_r_END     (11)
#define SOC_SECENG_S_OPCODE_reg_b_START   (12)
#define SOC_SECENG_S_OPCODE_reg_b_END     (17)
#define SOC_SECENG_S_OPCODE_reg_a_START   (18)
#define SOC_SECENG_S_OPCODE_reg_a_END     (23)
#define SOC_SECENG_S_OPCODE_len_START     (24)
#define SOC_SECENG_S_OPCODE_len_END       (26)
#define SOC_SECENG_S_OPCODE_opcode_START  (27)
#define SOC_SECENG_S_OPCODE_opcode_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_N_NP_T0_T1_ADDR_UNION
 �ṹ˵��  : N_NP_T0_T1_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00084����ֵ:0x000FF820�����:32
 �Ĵ���˵��: This register maps N_NP_T0_T1 to a virtual address��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  n_virtual_addr  : 5;  /* bit[0-4]  : Virtual address of register n */
        unsigned int  np_virtual_addr : 5;  /* bit[5-9]  : Virtual address of register np */
        unsigned int  t0_virtual_addr : 5;  /* bit[10-14]: Virtual address of temporary register number 0 */
        unsigned int  t1_virtual_addr : 5;  /* bit[15-19]: Virtual address of temporary register number 1 */
        unsigned int  reserved        : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_SECENG_S_N_NP_T0_T1_ADDR_UNION;
#endif
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_n_virtual_addr_START   (0)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_n_virtual_addr_END     (4)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_np_virtual_addr_START  (5)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_np_virtual_addr_END    (9)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_t0_virtual_addr_START  (10)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_t0_virtual_addr_END    (14)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_t1_virtual_addr_START  (15)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_t1_virtual_addr_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_STATUS_UNION
 �ṹ˵��  : PKA_STATUS �Ĵ����ṹ���塣��ַƫ����:0x00088����ֵ:0x00000001�����:32
 �Ĵ���˵��: This register holds the PKA pipe status��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pipe_is_rdy    : 1;  /* bit[0]    : Pka ready signal
                                                          0 - pipe full 
                                                          1 -pka ready for new command */
        unsigned int  pka_busy       : 1;  /* bit[1]    : Indicates if the engine is busy */
        unsigned int  alu_out_zero   : 1;  /* bit[2]    : Indicates if the result of ALU OUT is zero. */
        unsigned int  alu_modovrflw  : 1;  /* bit[3]    : Modular overflow flag. */
        unsigned int  div_by_zero    : 1;  /* bit[4]    : Indication if the division is done by zero. */
        unsigned int  alu_carry      : 1;  /* bit[5]    : Holds the carry of the last ALU operation. */
        unsigned int  alu_sign_out   : 1;  /* bit[6]    : Indicates the last operation's sign (MSB). */
        unsigned int  modinv_of_zero : 1;  /* bit[7]    : Indicates the Modular inverse of zero. */
        unsigned int  pka_cpu_busy   : 1;  /* bit[8]    : Indicates whether PKA is busy. */
        unsigned int  opcode         : 5;  /* bit[9-13] : Holds the last OPCODE used. */
        unsigned int  tag            : 6;  /* bit[14-19]: Tag of the Last Operation */
        unsigned int  reserved       : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_STATUS_UNION;
#endif
#define SOC_SECENG_S_PKA_STATUS_pipe_is_rdy_START     (0)
#define SOC_SECENG_S_PKA_STATUS_pipe_is_rdy_END       (0)
#define SOC_SECENG_S_PKA_STATUS_pka_busy_START        (1)
#define SOC_SECENG_S_PKA_STATUS_pka_busy_END          (1)
#define SOC_SECENG_S_PKA_STATUS_alu_out_zero_START    (2)
#define SOC_SECENG_S_PKA_STATUS_alu_out_zero_END      (2)
#define SOC_SECENG_S_PKA_STATUS_alu_modovrflw_START   (3)
#define SOC_SECENG_S_PKA_STATUS_alu_modovrflw_END     (3)
#define SOC_SECENG_S_PKA_STATUS_div_by_zero_START     (4)
#define SOC_SECENG_S_PKA_STATUS_div_by_zero_END       (4)
#define SOC_SECENG_S_PKA_STATUS_alu_carry_START       (5)
#define SOC_SECENG_S_PKA_STATUS_alu_carry_END         (5)
#define SOC_SECENG_S_PKA_STATUS_alu_sign_out_START    (6)
#define SOC_SECENG_S_PKA_STATUS_alu_sign_out_END      (6)
#define SOC_SECENG_S_PKA_STATUS_modinv_of_zero_START  (7)
#define SOC_SECENG_S_PKA_STATUS_modinv_of_zero_END    (7)
#define SOC_SECENG_S_PKA_STATUS_pka_cpu_busy_START    (8)
#define SOC_SECENG_S_PKA_STATUS_pka_cpu_busy_END      (8)
#define SOC_SECENG_S_PKA_STATUS_opcode_START          (9)
#define SOC_SECENG_S_PKA_STATUS_opcode_END            (13)
#define SOC_SECENG_S_PKA_STATUS_tag_START             (14)
#define SOC_SECENG_S_PKA_STATUS_tag_END               (19)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_SW_RESET_UNION
 �ṹ˵��  : PKA_SW_RESET �Ĵ����ṹ���塣��ַƫ����:0x0008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Writing to this register triggers a software reset of the PKA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_sw_reset : 1;  /* bit[0]   : pka software reset the reset mechansim will take about four pka clocks untill the reset line is de-asserted */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_SW_RESET_UNION;
#endif
#define SOC_SECENG_S_PKA_SW_RESET_pka_sw_reset_START  (0)
#define SOC_SECENG_S_PKA_SW_RESET_pka_sw_reset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_L0_UNION
 �ṹ˵��  : PKA_L0 �Ĵ����ṹ���塣��ַƫ����:0x00090����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the size of the operation��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_l0   : 13; /* bit[0-12] : Size of the operation in bytes. */
        unsigned int  reserved : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_L0_UNION;
#endif
#define SOC_SECENG_S_PKA_L0_pka_l0_START    (0)
#define SOC_SECENG_S_PKA_L0_pka_l0_END      (12)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_L1_UNION
 �ṹ˵��  : PKA_L1 �Ĵ����ṹ���塣��ַƫ����:0x00094����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the size of the operation��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_l1   : 13; /* bit[0-12] : Size of the operation in bytes. */
        unsigned int  reserved : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_L1_UNION;
#endif
#define SOC_SECENG_S_PKA_L1_pka_l1_START    (0)
#define SOC_SECENG_S_PKA_L1_pka_l1_END      (12)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_L2_UNION
 �ṹ˵��  : PKA_L2 �Ĵ����ṹ���塣��ַƫ����:0x00098����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the size of the operation��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_l2   : 13; /* bit[0-12] : Size of the operation in bytes. */
        unsigned int  reserved : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_L2_UNION;
#endif
#define SOC_SECENG_S_PKA_L2_pka_l2_START    (0)
#define SOC_SECENG_S_PKA_L2_pka_l2_END      (12)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_L3_UNION
 �ṹ˵��  : PKA_L3 �Ĵ����ṹ���塣��ַƫ����:0x0009C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the size of the operation��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_l3   : 13; /* bit[0-12] : Size of the operation in bytes. */
        unsigned int  reserved : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_L3_UNION;
#endif
#define SOC_SECENG_S_PKA_L3_pka_l3_START    (0)
#define SOC_SECENG_S_PKA_L3_pka_l3_END      (12)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_L4_UNION
 �ṹ˵��  : PKA_L4 �Ĵ����ṹ���塣��ַƫ����:0x000A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the size of the operation��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_l4   : 13; /* bit[0-12] : Size of the operation in bytes. */
        unsigned int  reserved : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_L4_UNION;
#endif
#define SOC_SECENG_S_PKA_L4_pka_l4_START    (0)
#define SOC_SECENG_S_PKA_L4_pka_l4_END      (12)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_L5_UNION
 �ṹ˵��  : PKA_L5 �Ĵ����ṹ���塣��ַƫ����:0x000A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the size of the operation��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_l5   : 13; /* bit[0-12] : Size of the operation in bytes. */
        unsigned int  reserved : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_L5_UNION;
#endif
#define SOC_SECENG_S_PKA_L5_pka_l5_START    (0)
#define SOC_SECENG_S_PKA_L5_pka_l5_END      (12)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_L6_UNION
 �ṹ˵��  : PKA_L6 �Ĵ����ṹ���塣��ַƫ����:0x000A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the size of the operation��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_l6   : 13; /* bit[0-12] : Size of the operation in bytes. */
        unsigned int  reserved : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_L6_UNION;
#endif
#define SOC_SECENG_S_PKA_L6_pka_l6_START    (0)
#define SOC_SECENG_S_PKA_L6_pka_l6_END      (12)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_L7_UNION
 �ṹ˵��  : PKA_L7 �Ĵ����ṹ���塣��ַƫ����:0x000AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the size of the operation��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_l7   : 13; /* bit[0-12] : Size of the operation in bytes. */
        unsigned int  reserved : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_L7_UNION;
#endif
#define SOC_SECENG_S_PKA_L7_pka_l7_START    (0)
#define SOC_SECENG_S_PKA_L7_pka_l7_END      (12)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_PIPE_RDY_UNION
 �ṹ˵��  : PKA_PIPE_RDY �Ĵ����ṹ���塣��ַƫ����:0x000B0����ֵ:0x00000001�����:32
 �Ĵ���˵��: This register indicates whether the PKA pipe is ready to receive a new OPCODE��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_pipe_rdy : 1;  /* bit[0]   : Indication whether PKA pipe is ready for new OPCODE. */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_PIPE_RDY_UNION;
#endif
#define SOC_SECENG_S_PKA_PIPE_RDY_pka_pipe_rdy_START  (0)
#define SOC_SECENG_S_PKA_PIPE_RDY_pka_pipe_rdy_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_DONE_UNION
 �ṹ˵��  : PKA_DONE �Ĵ����ṹ���塣��ַƫ����:0x000B4����ֵ:0x00000001�����:32
 �Ĵ���˵��: This register indicates whether PKA operation is completed��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_done : 1;  /* bit[0]   : Indicates if PKA operation is completed, and pipe is empty. */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_DONE_UNION;
#endif
#define SOC_SECENG_S_PKA_DONE_pka_done_START  (0)
#define SOC_SECENG_S_PKA_DONE_pka_done_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_MON_SELECT_UNION
 �ṹ˵��  : PKA_MON_SELECT �Ĵ����ṹ���塣��ַƫ����:0x000B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines which PKA FSM monitor is being output��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_mon_select : 4;  /* bit[0-3] : Defines which PKA FSM monitor is being output. */
        unsigned int  reserved       : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_MON_SELECT_UNION;
#endif
#define SOC_SECENG_S_PKA_MON_SELECT_pka_mon_select_START  (0)
#define SOC_SECENG_S_PKA_MON_SELECT_pka_mon_select_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_DEBUG_REG_EN_UNION
 �ṹ˵��  : PKA_DEBUG_REG_EN �Ĵ����ṹ���塣��ַƫ����:0x000BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register enables/disables all the debug mechanism��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_debug_reg_en : 1;  /* bit[0]   : Enables all the debug mechanism when set. */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_DEBUG_REG_EN_UNION;
#endif
#define SOC_SECENG_S_PKA_DEBUG_REG_EN_pka_debug_reg_en_START  (0)
#define SOC_SECENG_S_PKA_DEBUG_REG_EN_pka_debug_reg_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DEBUG_CNT_ADDR_UNION
 �ṹ˵��  : DEBUG_CNT_ADDR �Ĵ����ṹ���塣��ַƫ����:0x000C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the debug counter's value��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_cnt_addr : 20; /* bit[0-19] : The clock counter initial values. clock is disabled when counter expires. Triggered when pka_debug_en is set from DCU[2] */
        unsigned int  reserved       : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_SECENG_S_DEBUG_CNT_ADDR_UNION;
#endif
#define SOC_SECENG_S_DEBUG_CNT_ADDR_debug_cnt_addr_START  (0)
#define SOC_SECENG_S_DEBUG_CNT_ADDR_debug_cnt_addr_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_DEBUG_HALT_UNION
 �ṹ˵��  : PKA_DEBUG_HALT �Ĵ����ṹ���塣��ַƫ����:0x000C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register indicates whether the PKA is in halt state��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_debug_halt : 1;  /* bit[0]   : In debug mode: PKA is in halt state. */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_DEBUG_HALT_UNION;
#endif
#define SOC_SECENG_S_PKA_DEBUG_HALT_pka_debug_halt_START  (0)
#define SOC_SECENG_S_PKA_DEBUG_HALT_pka_debug_halt_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_MSB_ADDR_UNION
 �ṹ˵��  : PKA_MSB_ADDR �Ĵ����ṹ���塣��ַƫ����:0x000CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the PKA address' offset��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_msb_addr : 2;  /* bit[0-1] : This register is the OFFSET of the PKA address connected to the SRAM the actual address as connected to SRAM is pka_addr_sram = {pka_msb_addr pka_addr}  */
        unsigned int  reserved     : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_MSB_ADDR_UNION;
#endif
#define SOC_SECENG_S_PKA_MSB_ADDR_pka_msb_addr_START  (0)
#define SOC_SECENG_S_PKA_MSB_ADDR_pka_msb_addr_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_MON_READ_UNION
 �ṹ˵��  : PKA_MON_READ �Ĵ����ṹ���塣��ַƫ����:0x000D0����ֵ:0x0000FEEF�����:32
 �Ĵ���˵��: This register holds the PKA monitor bus' register output��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pka_mon_read : 32; /* bit[0-31]: Holds the PKA monitor bus' register output. */
    } reg;
} SOC_SECENG_S_PKA_MON_READ_UNION;
#endif
#define SOC_SECENG_S_PKA_MON_READ_pka_mon_read_START  (0)
#define SOC_SECENG_S_PKA_MON_READ_pka_mon_read_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_IMR_UNION
 �ṹ˵��  : RNG_IMR �Ĵ����ṹ���塣��ַƫ����:0x00100����ֵ:0x0000003F�����:32
 �Ĵ���˵��: Interrupt masking register��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ehr_valid_int_mask    : 1;  /* bit[0]   : value 1'b1-mask interrupt, no interrupt will be generated */
        unsigned int  autocorr_err_int_mask : 1;  /* bit[1]   : value 1'b1-mask interrupt, no interrupt will be generated */
        unsigned int  crngt_err_int_mask    : 1;  /* bit[2]   : value 1'b1-mask interrupt, no interrupt will be generated */
        unsigned int  vn_err_int_mask       : 1;  /* bit[3]   : value 1'b1-mask interrupt, no interrupt will be generated */
        unsigned int  watchdog_int_mask     : 1;  /* bit[4]   : value 1'b1-mask interrupt, no interrupt will be generated */
        unsigned int  rng_dma_done_int      : 1;  /* bit[5]   : value 1'b1-mask interrupt, no interrupt will be generated */
        unsigned int  reserved              : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_IMR_UNION;
#endif
#define SOC_SECENG_S_RNG_IMR_ehr_valid_int_mask_START     (0)
#define SOC_SECENG_S_RNG_IMR_ehr_valid_int_mask_END       (0)
#define SOC_SECENG_S_RNG_IMR_autocorr_err_int_mask_START  (1)
#define SOC_SECENG_S_RNG_IMR_autocorr_err_int_mask_END    (1)
#define SOC_SECENG_S_RNG_IMR_crngt_err_int_mask_START     (2)
#define SOC_SECENG_S_RNG_IMR_crngt_err_int_mask_END       (2)
#define SOC_SECENG_S_RNG_IMR_vn_err_int_mask_START        (3)
#define SOC_SECENG_S_RNG_IMR_vn_err_int_mask_END          (3)
#define SOC_SECENG_S_RNG_IMR_watchdog_int_mask_START      (4)
#define SOC_SECENG_S_RNG_IMR_watchdog_int_mask_END        (4)
#define SOC_SECENG_S_RNG_IMR_rng_dma_done_int_START       (5)
#define SOC_SECENG_S_RNG_IMR_rng_dma_done_int_END         (5)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_ISR_UNION
 �ṹ˵��  : RNG_ISR �Ĵ����ṹ���塣��ַƫ����:0x00104����ֵ:0x00000000�����:32
 �Ĵ���˵��: Status register��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ehr_valid          : 1;  /* bit[0]    : value 1'b1 indicates that 192 bits have been collected in the TRNG and are ready to be read */
        unsigned int  autocorr_err       : 1;  /* bit[1]    : value 1'b1 indicates Autocorrelation test failed four times in a row. when it set TRNG cease from functioning until next reset  */
        unsigned int  crngt_err          : 1;  /* bit[2]    : value 1'b1 indicates CRNGT in the TRNG test failed. failure occurs when two consecutive blocks of 16 collected bits are equal */
        unsigned int  vn_err             : 1;  /* bit[3]    : value 1'b1 indicates Von Neuman error. error in von Neuman occurs if 32 consecutive collected bits are identical ZERO or ONE  */
        unsigned int  watchdog_int_mask  : 1;  /* bit[4]    : value 1'b1 indicates watchdog expired */
        unsigned int  rng_dma_done       : 1;  /* bit[5]    : value 1'b1 indicates RNG dma to SRAM completed. */
        unsigned int  reserved_0         : 10; /* bit[6-15] : ���� */
        unsigned int  reseeding_done     : 1;  /* bit[16]   : value 1'b1 indicates completion of reseeding algorithm with no errors */
        unsigned int  instantiation_done : 1;  /* bit[17]   : value 1'b1 indicates completion of instantiation algorithm with no errors */
        unsigned int  final_update_done  : 1;  /* bit[18]   : value 1'b1 indicates completion of final update algorithm */
        unsigned int  output_ready       : 1;  /* bit[19]   : value 1'b1 indicates that the result of PRNG is valid and ready to be read. the result can be read from RNG_READOUT register. */
        unsigned int  reseed_cntr_full   : 1;  /* bit[20]   : value 1'b1 indicates that reseed counter has reached 2^48 requiring to run the reseed algorithm before generating new random numbers.  */
        unsigned int  reseed_cntr_top_40 : 1;  /* bit[21]   : value 1'b1 indicates that top 40 bits of reseed counter are set (that is the reseed counter is larger than 2^48-2^8). this is a recommendation for running the reseed algorithm before the counter will reach its max value.  */
        unsigned int  prng_crngt_err     : 1;  /* bit[22]   : value 1'b1 indicates CRNGT in the PRNG test failed. failure occurs when two consecutive results of AES are equal */
        unsigned int  req_size           : 1;  /* bit[23]   : value 1'b1 indicates that the request size counter which represent how many generations of random bits in the PRNG has been produced has reached 2^12 thus requiring a working state update before generating new random numbers. */
        unsigned int  kat_err            : 1;  /* bit[24]   : value 1'b1 indicates that one of the KAT (Known answer tests) tests failed. When set the entire engine cease to function */
        unsigned int  which_kat_err      : 2;  /* bit[25-26]: when KAT_ERR bit is set these bits represent which Known answer test had failed: 
                                                              2'b00 - first test of instantiation
                                                              2'b01 - second test of instantiation
                                                              2'b10 - first test of reseeding
                                                              2'b11 - second test of reseeding  */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_ISR_UNION;
#endif
#define SOC_SECENG_S_RNG_ISR_ehr_valid_START           (0)
#define SOC_SECENG_S_RNG_ISR_ehr_valid_END             (0)
#define SOC_SECENG_S_RNG_ISR_autocorr_err_START        (1)
#define SOC_SECENG_S_RNG_ISR_autocorr_err_END          (1)
#define SOC_SECENG_S_RNG_ISR_crngt_err_START           (2)
#define SOC_SECENG_S_RNG_ISR_crngt_err_END             (2)
#define SOC_SECENG_S_RNG_ISR_vn_err_START              (3)
#define SOC_SECENG_S_RNG_ISR_vn_err_END                (3)
#define SOC_SECENG_S_RNG_ISR_watchdog_int_mask_START   (4)
#define SOC_SECENG_S_RNG_ISR_watchdog_int_mask_END     (4)
#define SOC_SECENG_S_RNG_ISR_rng_dma_done_START        (5)
#define SOC_SECENG_S_RNG_ISR_rng_dma_done_END          (5)
#define SOC_SECENG_S_RNG_ISR_reseeding_done_START      (16)
#define SOC_SECENG_S_RNG_ISR_reseeding_done_END        (16)
#define SOC_SECENG_S_RNG_ISR_instantiation_done_START  (17)
#define SOC_SECENG_S_RNG_ISR_instantiation_done_END    (17)
#define SOC_SECENG_S_RNG_ISR_final_update_done_START   (18)
#define SOC_SECENG_S_RNG_ISR_final_update_done_END     (18)
#define SOC_SECENG_S_RNG_ISR_output_ready_START        (19)
#define SOC_SECENG_S_RNG_ISR_output_ready_END          (19)
#define SOC_SECENG_S_RNG_ISR_reseed_cntr_full_START    (20)
#define SOC_SECENG_S_RNG_ISR_reseed_cntr_full_END      (20)
#define SOC_SECENG_S_RNG_ISR_reseed_cntr_top_40_START  (21)
#define SOC_SECENG_S_RNG_ISR_reseed_cntr_top_40_END    (21)
#define SOC_SECENG_S_RNG_ISR_prng_crngt_err_START      (22)
#define SOC_SECENG_S_RNG_ISR_prng_crngt_err_END        (22)
#define SOC_SECENG_S_RNG_ISR_req_size_START            (23)
#define SOC_SECENG_S_RNG_ISR_req_size_END              (23)
#define SOC_SECENG_S_RNG_ISR_kat_err_START             (24)
#define SOC_SECENG_S_RNG_ISR_kat_err_END               (24)
#define SOC_SECENG_S_RNG_ISR_which_kat_err_START       (25)
#define SOC_SECENG_S_RNG_ISR_which_kat_err_END         (26)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_ICR_UNION
 �ṹ˵��  : RNG_ICR �Ĵ����ṹ���塣��ַƫ����:0x00108����ֵ:0x00000000�����:32
 �Ĵ���˵��: Interrupt/status bit clear Register��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ehr_valid          : 1;  /* bit[0]    : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  autocorr_err       : 1;  /* bit[1]    : can't be cleared by SW !!! Only RNG reset clears this bit */
        unsigned int  crngt_err          : 1;  /* bit[2]    : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  vn_err             : 1;  /* bit[3]    : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  rng_watchdog       : 1;  /* bit[4]    : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  rng_dma_done       : 1;  /* bit[5]    : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  reserved_0         : 10; /* bit[6-15] : ���� */
        unsigned int  reseeding_done     : 1;  /* bit[16]   : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  instantiation_done : 1;  /* bit[17]   : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  final_update_done  : 1;  /* bit[18]   : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  output_ready       : 1;  /* bit[19]   : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  reseed_cntr_full   : 1;  /* bit[20]   : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  reseed_cntr_top_40 : 1;  /* bit[21]   : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  prng_crngt_err     : 1;  /* bit[22]   : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  req_size           : 1;  /* bit[23]   : write value 1'b1 - clear corresponding bit in RNG_ISR */
        unsigned int  kat_err            : 1;  /* bit[24]   : KAT_ERR - cannot be cleared by SW. Only RNG reset clears this bit */
        unsigned int  which_kat_err      : 2;  /* bit[25-26]: can't be cleared by SW !!! Only RNG reset clears those bits */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_ICR_UNION;
#endif
#define SOC_SECENG_S_RNG_ICR_ehr_valid_START           (0)
#define SOC_SECENG_S_RNG_ICR_ehr_valid_END             (0)
#define SOC_SECENG_S_RNG_ICR_autocorr_err_START        (1)
#define SOC_SECENG_S_RNG_ICR_autocorr_err_END          (1)
#define SOC_SECENG_S_RNG_ICR_crngt_err_START           (2)
#define SOC_SECENG_S_RNG_ICR_crngt_err_END             (2)
#define SOC_SECENG_S_RNG_ICR_vn_err_START              (3)
#define SOC_SECENG_S_RNG_ICR_vn_err_END                (3)
#define SOC_SECENG_S_RNG_ICR_rng_watchdog_START        (4)
#define SOC_SECENG_S_RNG_ICR_rng_watchdog_END          (4)
#define SOC_SECENG_S_RNG_ICR_rng_dma_done_START        (5)
#define SOC_SECENG_S_RNG_ICR_rng_dma_done_END          (5)
#define SOC_SECENG_S_RNG_ICR_reseeding_done_START      (16)
#define SOC_SECENG_S_RNG_ICR_reseeding_done_END        (16)
#define SOC_SECENG_S_RNG_ICR_instantiation_done_START  (17)
#define SOC_SECENG_S_RNG_ICR_instantiation_done_END    (17)
#define SOC_SECENG_S_RNG_ICR_final_update_done_START   (18)
#define SOC_SECENG_S_RNG_ICR_final_update_done_END     (18)
#define SOC_SECENG_S_RNG_ICR_output_ready_START        (19)
#define SOC_SECENG_S_RNG_ICR_output_ready_END          (19)
#define SOC_SECENG_S_RNG_ICR_reseed_cntr_full_START    (20)
#define SOC_SECENG_S_RNG_ICR_reseed_cntr_full_END      (20)
#define SOC_SECENG_S_RNG_ICR_reseed_cntr_top_40_START  (21)
#define SOC_SECENG_S_RNG_ICR_reseed_cntr_top_40_END    (21)
#define SOC_SECENG_S_RNG_ICR_prng_crngt_err_START      (22)
#define SOC_SECENG_S_RNG_ICR_prng_crngt_err_END        (22)
#define SOC_SECENG_S_RNG_ICR_req_size_START            (23)
#define SOC_SECENG_S_RNG_ICR_req_size_END              (23)
#define SOC_SECENG_S_RNG_ICR_kat_err_START             (24)
#define SOC_SECENG_S_RNG_ICR_kat_err_END               (24)
#define SOC_SECENG_S_RNG_ICR_which_kat_err_START       (25)
#define SOC_SECENG_S_RNG_ICR_which_kat_err_END         (26)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_TRNG_CONFIG_UNION
 �ṹ˵��  : TRNG_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x0010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register handles TRNG configuration��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rnd_src_sel : 2;  /* bit[0-1] : Defines the length of the oscillator ring (= the number of inverters) out of four possible selections. */
        unsigned int  sop_sel     : 1;  /* bit[2]   : Secure Output Port selection: 
                                                      1'b1 - sop_data port reflects TRNG output (EHR_DATA)
                                                      1'b0 - sop_data port reflects PRNG output (RNG_READOUT). NOTE: secure output is used for direct connection of the RNG block outputs to an engine input key.If CryptoCell does not include a HW PRNG - this field should be set to 1. */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_SECENG_S_TRNG_CONFIG_UNION;
#endif
#define SOC_SECENG_S_TRNG_CONFIG_rnd_src_sel_START  (0)
#define SOC_SECENG_S_TRNG_CONFIG_rnd_src_sel_END    (1)
#define SOC_SECENG_S_TRNG_CONFIG_sop_sel_START      (2)
#define SOC_SECENG_S_TRNG_CONFIG_sop_sel_END        (2)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_TRNG_VALID_UNION
 �ṹ˵��  : TRNG_VALID �Ĵ����ṹ���塣��ַƫ����:0x00110����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register indicates that the TRNG data is valid��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ehr_valid : 1;  /* bit[0]   : 1'b1 indicates that collection of bits in the TRNG is completed, and data can be read from the EHR_DATA register. */
        unsigned int  reserved  : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_TRNG_VALID_UNION;
#endif
#define SOC_SECENG_S_TRNG_VALID_ehr_valid_START  (0)
#define SOC_SECENG_S_TRNG_VALID_ehr_valid_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_EHR_DATA_0_UNION
 �ṹ˵��  : EHR_DATA_0 �Ĵ����ṹ���塣��ַƫ����:0x00114����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register contains the data collected in the TRNG[31_0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ehr_data : 32; /* bit[0-31]: Collected bit in the TRNG[31_0] , NOTE - can only be set while in debug mode (rng_debug_enable input is set) */
    } reg;
} SOC_SECENG_S_EHR_DATA_0_UNION;
#endif
#define SOC_SECENG_S_EHR_DATA_0_ehr_data_START  (0)
#define SOC_SECENG_S_EHR_DATA_0_ehr_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_EHR_DATA_1_UNION
 �ṹ˵��  : EHR_DATA_1 �Ĵ����ṹ���塣��ַƫ����:0x00118����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register contains the data collected in the TRNG[63_32]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ehr_data : 32; /* bit[0-31]: Collected bit in the TRNG[63_32] , NOTE - can only be set while in debug mode (rng_debug_enable input is set) */
    } reg;
} SOC_SECENG_S_EHR_DATA_1_UNION;
#endif
#define SOC_SECENG_S_EHR_DATA_1_ehr_data_START  (0)
#define SOC_SECENG_S_EHR_DATA_1_ehr_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_EHR_DATA_2_UNION
 �ṹ˵��  : EHR_DATA_2 �Ĵ����ṹ���塣��ַƫ����:0x0011C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register contains the data collected in the TRNG[95_64]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ehr_data : 32; /* bit[0-31]: Collected bit in the TRNG[95_64] , NOTE - can only be set while in debug mode (rng_debug_enable input is set) */
    } reg;
} SOC_SECENG_S_EHR_DATA_2_UNION;
#endif
#define SOC_SECENG_S_EHR_DATA_2_ehr_data_START  (0)
#define SOC_SECENG_S_EHR_DATA_2_ehr_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_EHR_DATA_3_UNION
 �ṹ˵��  : EHR_DATA_3 �Ĵ����ṹ���塣��ַƫ����:0x00120����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register contains the data collected in the TRNG[127_96]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ehr_data : 32; /* bit[0-31]: Collected bit in the TRNG[127_96] , NOTE - can only be set while in debug mode (rng_debug_enable input is set) */
    } reg;
} SOC_SECENG_S_EHR_DATA_3_UNION;
#endif
#define SOC_SECENG_S_EHR_DATA_3_ehr_data_START  (0)
#define SOC_SECENG_S_EHR_DATA_3_ehr_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_EHR_DATA_4_UNION
 �ṹ˵��  : EHR_DATA_4 �Ĵ����ṹ���塣��ַƫ����:0x00124����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register contains the data collected in the TRNG[159_128]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ehr_data : 32; /* bit[0-31]: Collected bit in the TRNG[159_128], NOTE - can only be set while in debug mode (rng_debug_enable input is set) */
    } reg;
} SOC_SECENG_S_EHR_DATA_4_UNION;
#endif
#define SOC_SECENG_S_EHR_DATA_4_ehr_data_START  (0)
#define SOC_SECENG_S_EHR_DATA_4_ehr_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_EHR_DATA_5_UNION
 �ṹ˵��  : EHR_DATA_5 �Ĵ����ṹ���塣��ַƫ����:0x00128����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register contains the data collected in the TRNG[191_160]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ehr_data : 32; /* bit[0-31]: Collected bit in the TRNG[191_160], NOTE - can only be set while in debug mode (rng_debug_enable input is set) */
    } reg;
} SOC_SECENG_S_EHR_DATA_5_UNION;
#endif
#define SOC_SECENG_S_EHR_DATA_5_ehr_data_START  (0)
#define SOC_SECENG_S_EHR_DATA_5_ehr_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RND_SOURCE_ENABLE_UNION
 �ṹ˵��  : RND_SOURCE_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x0012C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the enable signal for the random source��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rnd_src_en : 1;  /* bit[0]   : Enable signal for the random source */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_RND_SOURCE_ENABLE_UNION;
#endif
#define SOC_SECENG_S_RND_SOURCE_ENABLE_rnd_src_en_START  (0)
#define SOC_SECENG_S_RND_SOURCE_ENABLE_rnd_src_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_SAMPLE_CNT1_UNION
 �ṹ˵��  : SAMPLE_CNT1 �Ĵ����ṹ���塣��ַƫ����:0x00130����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: Counts clocks between sampling of random bit��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sample_cntr1 : 32; /* bit[0-31]: Sets the number of rng_clk cycles between two consecutive ring oscillator samples. NOTE! If the Von-Neumann is bypassed, the minimum value for sample counter must not be less than decimal seventeen. */
    } reg;
} SOC_SECENG_S_SAMPLE_CNT1_UNION;
#endif
#define SOC_SECENG_S_SAMPLE_CNT1_sample_cntr1_START  (0)
#define SOC_SECENG_S_SAMPLE_CNT1_sample_cntr1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AUTOCORR_STATISTIC_UNION
 �ṹ˵��  : AUTOCORR_STATISTIC �Ĵ����ṹ���塣��ַƫ����:0x00134����ֵ:0x00000000�����:32
 �Ĵ���˵��: Statistics about autocorrelation test activations��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  autocorr_trys  : 14; /* bit[0-13] : Count each time an autocorrelation test starts. Any write to the register resets the counter. Stops collecting statistics if one of the counters has reached the limit. */
        unsigned int  autocorr_fails : 8;  /* bit[14-21]: Count each time an autocorrelation test fails. Any write to the register resets the counter. Stops collecting statistics if one of the counters has reached the limit. */
        unsigned int  reserved       : 10; /* bit[22-31]: ���� */
    } reg;
} SOC_SECENG_S_AUTOCORR_STATISTIC_UNION;
#endif
#define SOC_SECENG_S_AUTOCORR_STATISTIC_autocorr_trys_START   (0)
#define SOC_SECENG_S_AUTOCORR_STATISTIC_autocorr_trys_END     (13)
#define SOC_SECENG_S_AUTOCORR_STATISTIC_autocorr_fails_START  (14)
#define SOC_SECENG_S_AUTOCORR_STATISTIC_autocorr_fails_END    (21)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_TRNG_DEBUG_CONTROL_UNION
 �ṹ˵��  : TRNG_DEBUG_CONTROL �Ĵ����ṹ���塣��ַƫ����:0x00138����ֵ:0x00000000�����:32
 �Ĵ���˵��: Debug regsiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0            : 1;  /* bit[0]   : ���� */
        unsigned int  vnc_bypass            : 1;  /* bit[1]   : When this bit is set, the Von-Neumann balancer is bypassed (including the 32 consecutive bits test). NOTE! Can only be set while in debug mode. If TRNG_TESTS_BYPASS_EN HW flag is defined, this bit can be set while not in debug mode. */
        unsigned int  trng_crngt_bypass     : 1;  /* bit[2]   : When this bit is set, the CRNGT test in the TRNG is bypassed. NOTE! Can only be set while in debug mode. If TRNG_TESTS_BYPASS_EN HW flag is defined, this bit can be set while not in debug mode. */
        unsigned int  auto_correlate_bypass : 1;  /* bit[3]   : When this bit is set, the autocorrelation test in the TRNG module is bypassed. NOTE! Can only be set while in debug mode. If TRNG_TESTS_BYPASS_EN HW flag is defined, this bit can be set while not in debug mode. */
        unsigned int  reserved_1            : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_SECENG_S_TRNG_DEBUG_CONTROL_UNION;
#endif
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_vnc_bypass_START             (1)
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_vnc_bypass_END               (1)
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_trng_crngt_bypass_START      (2)
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_trng_crngt_bypass_END        (2)
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_auto_correlate_bypass_START  (3)
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_auto_correlate_bypass_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_SW_RESET_UNION
 �ṹ˵��  : RNG_SW_RESET �Ĵ����ṹ���塣��ַƫ����:0x00140����ֵ:0x00000000�����:32
 �Ĵ���˵��: Generate SW reset solely to RNG block��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rng_sw_reset : 1;  /* bit[0]   : Any value written (1'b0 or 1'b1) causes a reset cycle to the TRNG block. The reset mechanism takes about four RNG clock cycles until the reset line is de-asserted. */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_SW_RESET_UNION;
#endif
#define SOC_SECENG_S_RNG_SW_RESET_rng_sw_reset_START  (0)
#define SOC_SECENG_S_RNG_SW_RESET_rng_sw_reset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_DEBUG_EN_INPUT_UNION
 �ṹ˵��  : RNG_DEBUG_EN_INPUT �Ĵ����ṹ���塣��ַƫ����:0x001B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Defines the RNG in debug mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rng_debug_en : 1;  /* bit[0]   : Reflects the rng_debug_enable input port */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_DEBUG_EN_INPUT_UNION;
#endif
#define SOC_SECENG_S_RNG_DEBUG_EN_INPUT_rng_debug_en_START  (0)
#define SOC_SECENG_S_RNG_DEBUG_EN_INPUT_rng_debug_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_BUSY_UNION
 �ṹ˵��  : RNG_BUSY �Ĵ����ṹ���塣��ַƫ����:0x001B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: RNG busy indication
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rng_busy  : 1;  /* bit[0]   : reflect rng_busy output port which Consist of trng_busy and prng_busy */
        unsigned int  trng_busy : 1;  /* bit[1]   : reflect trng_busy */
        unsigned int  prng_busy : 1;  /* bit[2]   : reflect prng_busy */
        unsigned int  reserved  : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_BUSY_UNION;
#endif
#define SOC_SECENG_S_RNG_BUSY_rng_busy_START   (0)
#define SOC_SECENG_S_RNG_BUSY_rng_busy_END     (0)
#define SOC_SECENG_S_RNG_BUSY_trng_busy_START  (1)
#define SOC_SECENG_S_RNG_BUSY_trng_busy_END    (1)
#define SOC_SECENG_S_RNG_BUSY_prng_busy_START  (2)
#define SOC_SECENG_S_RNG_BUSY_prng_busy_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RST_BITS_COUNTER_UNION
 �ṹ˵��  : RST_BITS_COUNTER �Ĵ����ṹ���塣��ַƫ����:0x001BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Resets the counter of collected bits in the TRNG
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_bits_counter : 1;  /* bit[0]   : Writing any value to this address resets the bits counter and trng valid registers. RND_SORCE_ENABLE register must be unset in order for reset to take place. */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_RST_BITS_COUNTER_UNION;
#endif
#define SOC_SECENG_S_RST_BITS_COUNTER_rst_bits_counter_START  (0)
#define SOC_SECENG_S_RST_BITS_COUNTER_rst_bits_counter_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_VERSION_UNION
 �ṹ˵��  : RNG_VERSION �Ĵ����ṹ���塣��ַƫ����:0x001C0����ֵ:0x0000000F�����:32
 �Ĵ���˵��: This register holds the RNG version
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ehr_width_192        : 1;  /* bit[0]   : 0 - 128 bit HER
                                                               1 - 192 bit EHR */
        unsigned int  crngt_exists         : 1;  /* bit[1]   : 0 - not exists
                                                               1 - exists */
        unsigned int  autocorr_exists      : 1;  /* bit[2]   : 0 - not exists
                                                               1 - exists */
        unsigned int  trng_tests_bypass_en : 1;  /* bit[3]   : 0 - not enable
                                                               1 - trng tests bypass enable */
        unsigned int  prng_exists          : 1;  /* bit[4]   : 0 - not exists
                                                               1 - exists */
        unsigned int  kat_exists           : 1;  /* bit[5]   : 0 - not exists
                                                               1 - exists */
        unsigned int  reseeding_exists     : 1;  /* bit[6]   : 0 - not exists
                                                               1 - exists */
        unsigned int  rng_use_5_sboxes     : 1;  /* bit[7]   : 0 - 20 SBOX AES
                                                               1 - 5 SBOX AES */
        unsigned int  reserved             : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_VERSION_UNION;
#endif
#define SOC_SECENG_S_RNG_VERSION_ehr_width_192_START         (0)
#define SOC_SECENG_S_RNG_VERSION_ehr_width_192_END           (0)
#define SOC_SECENG_S_RNG_VERSION_crngt_exists_START          (1)
#define SOC_SECENG_S_RNG_VERSION_crngt_exists_END            (1)
#define SOC_SECENG_S_RNG_VERSION_autocorr_exists_START       (2)
#define SOC_SECENG_S_RNG_VERSION_autocorr_exists_END         (2)
#define SOC_SECENG_S_RNG_VERSION_trng_tests_bypass_en_START  (3)
#define SOC_SECENG_S_RNG_VERSION_trng_tests_bypass_en_END    (3)
#define SOC_SECENG_S_RNG_VERSION_prng_exists_START           (4)
#define SOC_SECENG_S_RNG_VERSION_prng_exists_END             (4)
#define SOC_SECENG_S_RNG_VERSION_kat_exists_START            (5)
#define SOC_SECENG_S_RNG_VERSION_kat_exists_END              (5)
#define SOC_SECENG_S_RNG_VERSION_reseeding_exists_START      (6)
#define SOC_SECENG_S_RNG_VERSION_reseeding_exists_END        (6)
#define SOC_SECENG_S_RNG_VERSION_rng_use_5_sboxes_START      (7)
#define SOC_SECENG_S_RNG_VERSION_rng_use_5_sboxes_END        (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_CLK_ENABLE_UNION
 �ṹ˵��  : RNG_CLK_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x001C4����ֵ:0x00000001�����:32
 �Ĵ���˵��: Writing to this register enables/disables the RNG clock��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : write value 1'b1 - Enable RNG clock */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_S_RNG_CLK_ENABLE_en_START        (0)
#define SOC_SECENG_S_RNG_CLK_ENABLE_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_DMA_ENABLE_UNION
 �ṹ˵��  : RNG_DMA_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x001C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Writing to this register enables/disables the RNG DMA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : write value 1'b1 - Enable RNG DMA to SRAM. The Value is cleared when DMA completes its operation */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_DMA_ENABLE_UNION;
#endif
#define SOC_SECENG_S_RNG_DMA_ENABLE_en_START        (0)
#define SOC_SECENG_S_RNG_DMA_ENABLE_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_DMA_SRC_MASK_UNION
 �ṹ˵��  : RNG_DMA_SRC_MASK �Ĵ����ṹ���塣��ַƫ����:0x001CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines which ring-oscillator length should be used when using the RNG DMA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en_src_sel0 : 1;  /* bit[0]   : write value 1'b1 - Enable SRC_SEL 0 */
        unsigned int  en_src_sel1 : 1;  /* bit[1]   : write value 1'b1 - Enable SRC_SEL 1 */
        unsigned int  en_src_sel2 : 1;  /* bit[2]   : write value 1'b1 - Enable SRC_SEL 2 */
        unsigned int  en_src_sel3 : 1;  /* bit[3]   : write value 1'b1 - Enable SRC_SEL 3 */
        unsigned int  reserved    : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_DMA_SRC_MASK_UNION;
#endif
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel0_START  (0)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel0_END    (0)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel1_START  (1)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel1_END    (1)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel2_START  (2)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel2_END    (2)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel3_START  (3)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel3_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_DMA_SRAM_ADDR_UNION
 �ṹ˵��  : RNG_DMA_SRAM_ADDR �Ĵ����ṹ���塣��ַƫ����:0x001D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines the start address of the DMA for the TRNG data��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rng_sram_dma_addr : 14; /* bit[0-13] : Defines the start address of the DMA for the TRNG data. */
        unsigned int  reserved          : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_DMA_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_S_RNG_DMA_SRAM_ADDR_rng_sram_dma_addr_START  (0)
#define SOC_SECENG_S_RNG_DMA_SRAM_ADDR_rng_sram_dma_addr_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_DMA_SAMPLES_NUM_UNION
 �ṹ˵��  : RNG_DMA_SAMPLES_NUM �Ĵ����ṹ���塣��ַƫ����:0x001D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines the number of 192-bits samples that the DMA collects per RNG configuration��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rng_samples_num : 8;  /* bit[0-7] : Defines the number of 192-bits samples that the DMA collects per RNG configuration. */
        unsigned int  reserved        : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_DMA_SAMPLES_NUM_UNION;
#endif
#define SOC_SECENG_S_RNG_DMA_SAMPLES_NUM_rng_samples_num_START  (0)
#define SOC_SECENG_S_RNG_DMA_SAMPLES_NUM_rng_samples_num_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_WATCHDOG_VAL_UNION
 �ṹ˵��  : RNG_WATCHDOG_VAL �Ĵ����ṹ���塣��ַƫ����:0x001D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines the maximum number of clock cycles per TRNG collection of 192 samples�� If the number of cycles for a collection exceeds this threshold, TRNG signals an interrupt��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rng_watchdog_val : 32; /* bit[0-31]: Defines the maximum number of clock cycles per TRNG collection of 192 samples. If the number of cycles for a collection exceeds this threshold, TRNG signals an interrupt. */
    } reg;
} SOC_SECENG_S_RNG_WATCHDOG_VAL_UNION;
#endif
#define SOC_SECENG_S_RNG_WATCHDOG_VAL_rng_watchdog_val_START  (0)
#define SOC_SECENG_S_RNG_WATCHDOG_VAL_rng_watchdog_val_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_RNG_DMA_STATUS_UNION
 �ṹ˵��  : RNG_DMA_STATUS �Ĵ����ṹ���塣��ַƫ����:0x001DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the RNG DMA status��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rng_dma_busy   : 1;  /* bit[0]    : Indicates whether DMA is busy. */
        unsigned int  dma_src_sel    : 2;  /* bit[1-2]  : The active ring oscillator length using by DMA */
        unsigned int  num_of_samples : 8;  /* bit[3-10] : Number of samples already collected in the current ring oscillator length. */
        unsigned int  reserved       : 21; /* bit[11-31]: ���� */
    } reg;
} SOC_SECENG_S_RNG_DMA_STATUS_UNION;
#endif
#define SOC_SECENG_S_RNG_DMA_STATUS_rng_dma_busy_START    (0)
#define SOC_SECENG_S_RNG_DMA_STATUS_rng_dma_busy_END      (0)
#define SOC_SECENG_S_RNG_DMA_STATUS_dma_src_sel_START     (1)
#define SOC_SECENG_S_RNG_DMA_STATUS_dma_src_sel_END       (2)
#define SOC_SECENG_S_RNG_DMA_STATUS_num_of_samples_START  (3)
#define SOC_SECENG_S_RNG_DMA_STATUS_num_of_samples_END    (10)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AES_CLK_ENABLE_UNION
 �ṹ˵��  : AES_CLK_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x00810����ֵ:0x00000000�����:32
 �Ĵ���˵��: The AES clock enable register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : 1'b1: the AES clock is enabled.
                                                   1'b0: the AES clock is disabled.  */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_AES_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_S_AES_CLK_ENABLE_en_START        (0)
#define SOC_SECENG_S_AES_CLK_ENABLE_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DES_CLK_ENABLE_UNION
 �ṹ˵��  : DES_CLK_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x00814����ֵ:0x00000000�����:32
 �Ĵ���˵��: The DES clock enable register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : 1'b1: the DES clock is enabled.
                                                   1'b0: the DES clock is disabled.  */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DES_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_S_DES_CLK_ENABLE_en_START        (0)
#define SOC_SECENG_S_DES_CLK_ENABLE_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HASH_CLK_ENABLE_UNION
 �ṹ˵��  : HASH_CLK_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x00818����ֵ:0x00000000�����:32
 �Ĵ���˵��: The HASH clock enable register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : 1'b1: the HASH clock is enabled.
                                                   1'b0: the HASH clock is disabled.  */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HASH_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_S_HASH_CLK_ENABLE_en_START        (0)
#define SOC_SECENG_S_HASH_CLK_ENABLE_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_PKA_CLK_ENABLE_UNION
 �ṹ˵��  : PKA_CLK_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x0081C����ֵ:0x00000000�����:32
 �Ĵ���˵��: The PKA clock enable register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : 1'b1: the PKA clock is enabled.
                                                   1'b0: the PKA clock is disabled.  */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_PKA_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_S_PKA_CLK_ENABLE_en_START        (0)
#define SOC_SECENG_S_PKA_CLK_ENABLE_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DMA_CLK_ENABLE_UNION
 �ṹ˵��  : DMA_CLK_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x00820����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_CLK enable register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : 1'b1: the DMA clock is enabled.
                                                   1'b0: the DMA clock is disabled.  */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DMA_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_S_DMA_CLK_ENABLE_en_START        (0)
#define SOC_SECENG_S_DMA_CLK_ENABLE_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_CLK_STATUS_UNION
 �ṹ˵��  : CLK_STATUS �Ĵ����ṹ���塣��ַƫ����:0x00824����ֵ:0x00000100�����:32
 �Ĵ���˵��: The CryptoCell clocks' status register�� If LCS is secure, all engines' clocks are disabled�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aes_clk_status  : 1;  /* bit[0]   : 1'b1: the AES clock is enabled.
                                                          1'b0: the AES clock is disabled.  */
        unsigned int  des_clk_status  : 1;  /* bit[1]   : 1'b1: the DES clock is enabled.
                                                          1'b0: the DES clock is disabled.  */
        unsigned int  hash_clk_status : 1;  /* bit[2]   : 1'b1: the HASH clock is enabled.
                                                          1'b0: the HASH clock is disabled.  */
        unsigned int  pka_clk_status  : 1;  /* bit[3]   : 1'b1: the PKA clock is enabled.
                                                          1'b0: the PKA clock is disabled.  */
        unsigned int  reserved_0      : 4;  /* bit[4-7] : ���� */
        unsigned int  dma_clk_status  : 1;  /* bit[8]   : 1'b1: the DMA clock is enabled.
                                                          1'b0: the DMA clock is disabled.  */
        unsigned int  reserved_1      : 23; /* bit[9-31]: ���� */
    } reg;
} SOC_SECENG_S_CLK_STATUS_UNION;
#endif
#define SOC_SECENG_S_CLK_STATUS_aes_clk_status_START   (0)
#define SOC_SECENG_S_CLK_STATUS_aes_clk_status_END     (0)
#define SOC_SECENG_S_CLK_STATUS_des_clk_status_START   (1)
#define SOC_SECENG_S_CLK_STATUS_des_clk_status_END     (1)
#define SOC_SECENG_S_CLK_STATUS_hash_clk_status_START  (2)
#define SOC_SECENG_S_CLK_STATUS_hash_clk_status_END    (2)
#define SOC_SECENG_S_CLK_STATUS_pka_clk_status_START   (3)
#define SOC_SECENG_S_CLK_STATUS_pka_clk_status_END     (3)
#define SOC_SECENG_S_CLK_STATUS_dma_clk_status_START   (8)
#define SOC_SECENG_S_CLK_STATUS_dma_clk_status_END     (8)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_CRYPTO_CTL_UNION
 �ṹ˵��  : CRYPTO_CTL �Ĵ����ṹ���塣��ַƫ����:0x00900����ֵ:0x00000000�����:32
 �Ĵ���˵��: Defines the cryptographic flow��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 5;  /* bit[0-4] : Determines the active cryptographic engine.
                                                   5'b0000 - BYPASS 
                                                   5'b0001 - AES 
                                                   5'b0010 - AES_TO_HASH 
                                                   5'b0011 - AES_AND_HASH 
                                                   5'b0100 - DES 
                                                   5'b0101 - DES_TO_HASH 
                                                   5'b0110 - DES_AND_HASH 
                                                   5'b0111 - HASH 
                                                   5'b1001 - AES_MAC_AND_BYPASS
                                                   5'b1010 - AES_TO_HASH_AND_DOUT
                                                   5'b1011 - Reserved
                                                   5'b1000 - Reserved */
        unsigned int  reserved : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_SECENG_S_CRYPTO_CTL_UNION;
#endif
#define SOC_SECENG_S_CRYPTO_CTL_mode_START      (0)
#define SOC_SECENG_S_CRYPTO_CTL_mode_END        (4)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_CRYPTO_BUSY_UNION
 �ṹ˵��  : CRYPTO_BUSY �Ĵ����ṹ���塣��ַƫ����:0x00910����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is set when the cryptographic core is busy��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crypto_busy : 1;  /* bit[0]   : 1'b0 - Ready
                                                      1'b1 - Busy Asserted when AES_BUSY or DES_BUSY or HASH_BUSY are asserted or when the DIN FIFO is not empty. */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_CRYPTO_BUSY_UNION;
#endif
#define SOC_SECENG_S_CRYPTO_BUSY_crypto_busy_START  (0)
#define SOC_SECENG_S_CRYPTO_BUSY_crypto_busy_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HASH_BUSY_UNION
 �ṹ˵��  : HASH_BUSY �Ĵ����ṹ���塣��ַƫ����:0x0091C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is set when the Hash engine is busy��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hash_busy : 1;  /* bit[0]   : 1'b0 - Ready
                                                    1'b1 - Busy Asserted when hash engine is busy. */
        unsigned int  reserved  : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HASH_BUSY_UNION;
#endif
#define SOC_SECENG_S_HASH_BUSY_hash_busy_START  (0)
#define SOC_SECENG_S_HASH_BUSY_hash_busy_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_VERSION_UNION
 �ṹ˵��  : VERSION �Ĵ����ṹ���塣��ַƫ����:0x00928����ֵ:0xBF400002�����:32
 �Ĵ���˵��: This register holds the current CryptoCell version��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  version : 32; /* bit[0-31]: Auto-generated, hard-coded unique number. */
    } reg;
} SOC_SECENG_S_VERSION_UNION;
#endif
#define SOC_SECENG_S_VERSION_version_START  (0)
#define SOC_SECENG_S_VERSION_version_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_CONTEXT_ID_UNION
 �ṹ˵��  : CONTEXT_ID �Ĵ����ṹ���塣��ַƫ����:0x00930����ֵ:0x00000000�����:32
 �Ĵ���˵��: A general RD/WR register�� For Firmware use��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  context_id : 8;  /* bit[0-7] : Context ID */
        unsigned int  reserved   : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_CONTEXT_ID_UNION;
#endif
#define SOC_SECENG_S_CONTEXT_ID_context_id_START  (0)
#define SOC_SECENG_S_CONTEXT_ID_context_id_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO0_UNION
 �ṹ˵��  : HASH_COMPARE_ERR_ID_FIFO0 �Ĵ����ṹ���塣��ַƫ����:0x00940����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the flow ID of the descriptor that caused that last error��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hash_compare_error_id_fifo0 : 26; /* bit[0-25] : Holds the flow ID of the descriptor that caused that last error. */
        unsigned int  reserved                    : 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO0_UNION;
#endif
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO0_hash_compare_error_id_fifo0_START  (0)
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO0_hash_compare_error_id_fifo0_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO1_UNION
 �ṹ˵��  : HASH_COMPARE_ERR_ID_FIFO1 �Ĵ����ṹ���塣��ַƫ����:0x00944����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the flow ID of the descriptor that caused that one-before-last error��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hash_compare_error_id_fifo1 : 26; /* bit[0-25] : Holds the flow ID of the descriptor that caused that one-before-last error. */
        unsigned int  reserved                    : 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO1_UNION;
#endif
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO1_hash_compare_error_id_fifo1_START  (0)
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO1_hash_compare_error_id_fifo1_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO2_UNION
 �ṹ˵��  : HASH_COMPARE_ERR_ID_FIFO2 �Ĵ����ṹ���塣��ַƫ����:0x00948����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the flow ID of the descriptor that caused that one-before-last error��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hash_compare_error_id_fifo2 : 26; /* bit[0-25] : Holds the flow ID of the descriptor that caused that two-before-last error. */
        unsigned int  reserved                    : 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO2_UNION;
#endif
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO2_hash_compare_error_id_fifo2_START  (0)
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO2_hash_compare_error_id_fifo2_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO3_UNION
 �ṹ˵��  : HASH_COMPARE_ERR_ID_FIFO3 �Ĵ����ṹ���塣��ַƫ����:0x0094C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the flow ID of the descriptor that caused that one-before-last error��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hash_compare_error_id_fifo3 : 26; /* bit[0-25] : Holds the flow ID of the descriptor that caused that three-before-last error. */
        unsigned int  reserved                    : 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO3_UNION;
#endif
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO3_hash_compare_error_id_fifo3_START  (0)
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO3_hash_compare_error_id_fifo3_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_RGF_IRR_UNION
 �ṹ˵��  : HOST_RGF_IRR �Ĵ����ṹ���塣��ַƫ����:0x00A00����ֵ:0x00000000�����:32
 �Ĵ���˵��: The Interrupt Request register�� Each bit of this register holds the interrupt status of a single interrupt source��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                 : 1;  /* bit[0]    : ���� */
        unsigned int  reserved_1                 : 1;  /* bit[1]    : ���� */
        unsigned int  dscrptr_completion_low_int : 1;  /* bit[2]    : The descriptor completion interrupt status. */
        unsigned int  reserved_2                 : 1;  /* bit[3]    : ���� */
        unsigned int  sram_to_din_int            : 1;  /* bit[4]    : The SRAM to DIN DMA done interrupt status. This interrupt is asserted when all data was delivered to DIN buffer from SRAM. */
        unsigned int  dout_to_sram_int           : 1;  /* bit[5]    : The DOUT to SRAM DMA done interrupt status. This interrupt is asserted when all data was delivered to SRAM buffer from DOUT. */
        unsigned int  mem_to_din_int             : 1;  /* bit[6]    : The memory to DIN DMA done interrupt status. This interrupt is asserted when all data was delivered to DIN buffer from memory. */
        unsigned int  dout_to_mem_int            : 1;  /* bit[7]    : The DOUT to memory DMA done interrupt status. This interrupt is asserted when all data was delivered to memory buffer from DOUT. */
        unsigned int  axi_err_int                : 1;  /* bit[8]    : The AXI error interrupt status. */
        unsigned int  pka_exp_int                : 1;  /* bit[9]    : The AXI error interrupt status. */
        unsigned int  rng_int                    : 1;  /* bit[10]   : The AXI error interrupt status. */
        unsigned int  reserved_3                 : 1;  /* bit[11]   : ���� */
        unsigned int  reserved_4                 : 1;  /* bit[12]   : ���� */
        unsigned int  reserved_5                 : 1;  /* bit[13]   : ���� */
        unsigned int  reserved_6                 : 1;  /* bit[14]   : ���� */
        unsigned int  reserved_7                 : 1;  /* bit[15]   : ���� */
        unsigned int  reserved_8                 : 1;  /* bit[16]   : ���� */
        unsigned int  reserved_9                 : 1;  /* bit[17]   : ���� */
        unsigned int  reserved_10                : 1;  /* bit[18]   : ���� */
        unsigned int  dscrptr_watermark_int      : 1;  /* bit[19]   : The AXI error interrupt status. */
        unsigned int  dscrptr_watermark1_int     : 1;  /* bit[20]   : The AXI error interrupt status. */
        unsigned int  reserved_11                : 1;  /* bit[21]   : ���� */
        unsigned int  hash_cmp_error_int         : 1;  /* bit[22]   : The AXI error interrupt status. */
        unsigned int  secure_timer_int           : 1;  /* bit[23]   : The AXI master completion interrupt status. */
        unsigned int  axim_comp_int              : 1;  /* bit[24]   : The Secure Timer interrupt status. */
        unsigned int  reserved_12                : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_RGF_IRR_UNION;
#endif
#define SOC_SECENG_S_HOST_RGF_IRR_dscrptr_completion_low_int_START  (2)
#define SOC_SECENG_S_HOST_RGF_IRR_dscrptr_completion_low_int_END    (2)
#define SOC_SECENG_S_HOST_RGF_IRR_sram_to_din_int_START             (4)
#define SOC_SECENG_S_HOST_RGF_IRR_sram_to_din_int_END               (4)
#define SOC_SECENG_S_HOST_RGF_IRR_dout_to_sram_int_START            (5)
#define SOC_SECENG_S_HOST_RGF_IRR_dout_to_sram_int_END              (5)
#define SOC_SECENG_S_HOST_RGF_IRR_mem_to_din_int_START              (6)
#define SOC_SECENG_S_HOST_RGF_IRR_mem_to_din_int_END                (6)
#define SOC_SECENG_S_HOST_RGF_IRR_dout_to_mem_int_START             (7)
#define SOC_SECENG_S_HOST_RGF_IRR_dout_to_mem_int_END               (7)
#define SOC_SECENG_S_HOST_RGF_IRR_axi_err_int_START                 (8)
#define SOC_SECENG_S_HOST_RGF_IRR_axi_err_int_END                   (8)
#define SOC_SECENG_S_HOST_RGF_IRR_pka_exp_int_START                 (9)
#define SOC_SECENG_S_HOST_RGF_IRR_pka_exp_int_END                   (9)
#define SOC_SECENG_S_HOST_RGF_IRR_rng_int_START                     (10)
#define SOC_SECENG_S_HOST_RGF_IRR_rng_int_END                       (10)
#define SOC_SECENG_S_HOST_RGF_IRR_dscrptr_watermark_int_START       (19)
#define SOC_SECENG_S_HOST_RGF_IRR_dscrptr_watermark_int_END         (19)
#define SOC_SECENG_S_HOST_RGF_IRR_dscrptr_watermark1_int_START      (20)
#define SOC_SECENG_S_HOST_RGF_IRR_dscrptr_watermark1_int_END        (20)
#define SOC_SECENG_S_HOST_RGF_IRR_hash_cmp_error_int_START          (22)
#define SOC_SECENG_S_HOST_RGF_IRR_hash_cmp_error_int_END            (22)
#define SOC_SECENG_S_HOST_RGF_IRR_secure_timer_int_START            (23)
#define SOC_SECENG_S_HOST_RGF_IRR_secure_timer_int_END              (23)
#define SOC_SECENG_S_HOST_RGF_IRR_axim_comp_int_START               (24)
#define SOC_SECENG_S_HOST_RGF_IRR_axim_comp_int_END                 (24)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_RGF_IMR_UNION
 �ṹ˵��  : HOST_RGF_IMR �Ĵ����ṹ���塣��ַƫ����:0x00A04����ֵ:0x01FFFFFF�����:32
 �Ĵ���˵��: The Interrupt Mask register. Each bit of this register holds the mask of a single interrupt source.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0]    : ���� */
        unsigned int  reserved_1              : 1;  /* bit[1]    : ���� */
        unsigned int  dscrptr_completion_mask : 1;  /* bit[2]    : The descriptor completion interrupt mask. */
        unsigned int  reserved_2              : 1;  /* bit[3]    : ���� */
        unsigned int  sram_to_din_mask        : 1;  /* bit[4]    : The SRAM to DIN DMA done interrupt mask. */
        unsigned int  dout_to_sram_mask       : 1;  /* bit[5]    : The DOUT to SRAM DMA done interrupt mask. */
        unsigned int  mem_to_din_mask         : 1;  /* bit[6]    : The memory to DIN DMA done interrupt mask. */
        unsigned int  dout_to_mem_mask        : 1;  /* bit[7]    : The DOUT to memory DMA done interrupt mask. */
        unsigned int  axi_err_mask            : 1;  /* bit[8]    : The AXI error interrupt mask. */
        unsigned int  pka_exp_mask            : 1;  /* bit[9]    : The PKA end of operation interrupt mask. */
        unsigned int  rng_mask                : 1;  /* bit[10]   : The RNG interrupt mask. */
        unsigned int  reserved_3              : 8;  /* bit[11-18]: ���� */
        unsigned int  dscrptr_watermark_mask0 : 1;  /* bit[19]   : The descriptor queue0 watermark interrupt mask. */
        unsigned int  dscrptr_watermark_mask1 : 1;  /* bit[20]   : The descriptor queue1 watermark interrupt mask. */
        unsigned int  reserved_4              : 1;  /* bit[21]   : ���� */
        unsigned int  hash_cmp_error          : 1;  /* bit[22]   : The Hash compare error interrupt mask */
        unsigned int  secure_timer_int_mask   : 1;  /* bit[23]   : The AXI master completion interrupt mask. */
        unsigned int  axim_comp_int_mask      : 1;  /* bit[24]   : The Secure Timer interrupt mask. */
        unsigned int  reserved_5              : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_RGF_IMR_UNION;
#endif
#define SOC_SECENG_S_HOST_RGF_IMR_dscrptr_completion_mask_START  (2)
#define SOC_SECENG_S_HOST_RGF_IMR_dscrptr_completion_mask_END    (2)
#define SOC_SECENG_S_HOST_RGF_IMR_sram_to_din_mask_START         (4)
#define SOC_SECENG_S_HOST_RGF_IMR_sram_to_din_mask_END           (4)
#define SOC_SECENG_S_HOST_RGF_IMR_dout_to_sram_mask_START        (5)
#define SOC_SECENG_S_HOST_RGF_IMR_dout_to_sram_mask_END          (5)
#define SOC_SECENG_S_HOST_RGF_IMR_mem_to_din_mask_START          (6)
#define SOC_SECENG_S_HOST_RGF_IMR_mem_to_din_mask_END            (6)
#define SOC_SECENG_S_HOST_RGF_IMR_dout_to_mem_mask_START         (7)
#define SOC_SECENG_S_HOST_RGF_IMR_dout_to_mem_mask_END           (7)
#define SOC_SECENG_S_HOST_RGF_IMR_axi_err_mask_START             (8)
#define SOC_SECENG_S_HOST_RGF_IMR_axi_err_mask_END               (8)
#define SOC_SECENG_S_HOST_RGF_IMR_pka_exp_mask_START             (9)
#define SOC_SECENG_S_HOST_RGF_IMR_pka_exp_mask_END               (9)
#define SOC_SECENG_S_HOST_RGF_IMR_rng_mask_START                 (10)
#define SOC_SECENG_S_HOST_RGF_IMR_rng_mask_END                   (10)
#define SOC_SECENG_S_HOST_RGF_IMR_dscrptr_watermark_mask0_START  (19)
#define SOC_SECENG_S_HOST_RGF_IMR_dscrptr_watermark_mask0_END    (19)
#define SOC_SECENG_S_HOST_RGF_IMR_dscrptr_watermark_mask1_START  (20)
#define SOC_SECENG_S_HOST_RGF_IMR_dscrptr_watermark_mask1_END    (20)
#define SOC_SECENG_S_HOST_RGF_IMR_hash_cmp_error_START           (22)
#define SOC_SECENG_S_HOST_RGF_IMR_hash_cmp_error_END             (22)
#define SOC_SECENG_S_HOST_RGF_IMR_secure_timer_int_mask_START    (23)
#define SOC_SECENG_S_HOST_RGF_IMR_secure_timer_int_mask_END      (23)
#define SOC_SECENG_S_HOST_RGF_IMR_axim_comp_int_mask_START       (24)
#define SOC_SECENG_S_HOST_RGF_IMR_axim_comp_int_mask_END         (24)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_RGF_ICR_UNION
 �ṹ˵��  : HOST_RGF_ICR �Ĵ����ṹ���塣��ַƫ����:0x00A08����ֵ:0x00000000�����:32
 �Ĵ���˵��: Interrupt Clear Register��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                     : 1;  /* bit[0]    : ���� */
        unsigned int  reserved_1                     : 1;  /* bit[1]    : ���� */
        unsigned int  dscrptr_completion_clear       : 1;  /* bit[2]    : The descriptor completion interrupt clear. */
        unsigned int  reserved_2                     : 1;  /* bit[3]    : ���� */
        unsigned int  sram_to_din_clear              : 1;  /* bit[4]    : The SRAM to DIN DMA done interrupt clear. */
        unsigned int  dout_to_sram_clear             : 1;  /* bit[5]    : The DOUT to SRAM DMA done interrupt clear. */
        unsigned int  mem_to_din_clear               : 1;  /* bit[6]    : The memory to DIN DMA done interrupt clear. */
        unsigned int  dout_to_mem_clear              : 1;  /* bit[7]    : The DOUT to memory DMA done interrupt clear. */
        unsigned int  axi_err_clear                  : 1;  /* bit[8]    : The AXI error interrupt clear. */
        unsigned int  pka_exp_clear                  : 1;  /* bit[9]    : The PKA end of operation interrupt clear. */
        unsigned int  rng_int_clear                  : 1;  /* bit[10]   : The RNG interrupt clear. */
        unsigned int  reserved_3                     : 1;  /* bit[11]   : ���� */
        unsigned int  reserved_4                     : 1;  /* bit[12]   : ���� */
        unsigned int  reserved_5                     : 1;  /* bit[13]   : ���� */
        unsigned int  reserved_6                     : 1;  /* bit[14]   : ���� */
        unsigned int  reserved_7                     : 1;  /* bit[15]   : ���� */
        unsigned int  reserved_8                     : 1;  /* bit[16]   : ���� */
        unsigned int  reserved_9                     : 1;  /* bit[17]   : ���� */
        unsigned int  reserved_10                    : 1;  /* bit[18]   : ���� */
        unsigned int  dscrptr_watermark_queue0_clear : 1;  /* bit[19]   : The descriptor queue0 watermark interrupt clear. */
        unsigned int  dscrptr_watermark_queue1_clear : 1;  /* bit[20]   : The descriptor queue1 watermark interrupt clear. */
        unsigned int  reserved_11                    : 1;  /* bit[21]   : ���� */
        unsigned int  hash_cmp_error_clear           : 1;  /* bit[22]   : The Hash compare error interrupt clear */
        unsigned int  secure_timer_int_clear         : 1;  /* bit[23]   : The AXI master completion interrupt clear. */
        unsigned int  axim_comp_int_clear            : 1;  /* bit[24]   : The AXI master completion interrupt clear. */
        unsigned int  reserved_12                    : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_RGF_ICR_UNION;
#endif
#define SOC_SECENG_S_HOST_RGF_ICR_dscrptr_completion_clear_START        (2)
#define SOC_SECENG_S_HOST_RGF_ICR_dscrptr_completion_clear_END          (2)
#define SOC_SECENG_S_HOST_RGF_ICR_sram_to_din_clear_START               (4)
#define SOC_SECENG_S_HOST_RGF_ICR_sram_to_din_clear_END                 (4)
#define SOC_SECENG_S_HOST_RGF_ICR_dout_to_sram_clear_START              (5)
#define SOC_SECENG_S_HOST_RGF_ICR_dout_to_sram_clear_END                (5)
#define SOC_SECENG_S_HOST_RGF_ICR_mem_to_din_clear_START                (6)
#define SOC_SECENG_S_HOST_RGF_ICR_mem_to_din_clear_END                  (6)
#define SOC_SECENG_S_HOST_RGF_ICR_dout_to_mem_clear_START               (7)
#define SOC_SECENG_S_HOST_RGF_ICR_dout_to_mem_clear_END                 (7)
#define SOC_SECENG_S_HOST_RGF_ICR_axi_err_clear_START                   (8)
#define SOC_SECENG_S_HOST_RGF_ICR_axi_err_clear_END                     (8)
#define SOC_SECENG_S_HOST_RGF_ICR_pka_exp_clear_START                   (9)
#define SOC_SECENG_S_HOST_RGF_ICR_pka_exp_clear_END                     (9)
#define SOC_SECENG_S_HOST_RGF_ICR_rng_int_clear_START                   (10)
#define SOC_SECENG_S_HOST_RGF_ICR_rng_int_clear_END                     (10)
#define SOC_SECENG_S_HOST_RGF_ICR_dscrptr_watermark_queue0_clear_START  (19)
#define SOC_SECENG_S_HOST_RGF_ICR_dscrptr_watermark_queue0_clear_END    (19)
#define SOC_SECENG_S_HOST_RGF_ICR_dscrptr_watermark_queue1_clear_START  (20)
#define SOC_SECENG_S_HOST_RGF_ICR_dscrptr_watermark_queue1_clear_END    (20)
#define SOC_SECENG_S_HOST_RGF_ICR_hash_cmp_error_clear_START            (22)
#define SOC_SECENG_S_HOST_RGF_ICR_hash_cmp_error_clear_END              (22)
#define SOC_SECENG_S_HOST_RGF_ICR_secure_timer_int_clear_START          (23)
#define SOC_SECENG_S_HOST_RGF_ICR_secure_timer_int_clear_END            (23)
#define SOC_SECENG_S_HOST_RGF_ICR_axim_comp_int_clear_START             (24)
#define SOC_SECENG_S_HOST_RGF_ICR_axim_comp_int_clear_END               (24)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_RGF_ENDIAN_UNION
 �ṹ˵��  : HOST_RGF_ENDIAN �Ĵ����ṹ���塣��ַƫ����:0x00A0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines the endianness of the Host-accessible registers��
            NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 3;  /* bit[0-2]  : ���� */
        unsigned int  dout_wr_bg  : 1;  /* bit[3]    : DOUT write endianess
                                                       0 - little endia
                                                       1 - big endian */
        unsigned int  reserved_1  : 3;  /* bit[4-6]  : ���� */
        unsigned int  din_rd_bg   : 1;  /* bit[7]    : DIN read endianess
                                                       0 - little endia
                                                       1 - big endian */
        unsigned int  reserved_2  : 3;  /* bit[8-10] : ���� */
        unsigned int  dout_wr_wbg : 1;  /* bit[11]   : DOUT write word endianess
                                                       0 - little endia
                                                       1 - big endian */
        unsigned int  reserved_3  : 3;  /* bit[12-14]: ���� */
        unsigned int  din_rd_wbg  : 1;  /* bit[15]   : DIN read word endianess
                                                       0 - little endia
                                                       1 - big endian */
        unsigned int  reserved_4  : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_RGF_ENDIAN_UNION;
#endif
#define SOC_SECENG_S_HOST_RGF_ENDIAN_dout_wr_bg_START   (3)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_dout_wr_bg_END     (3)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_din_rd_bg_START    (7)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_din_rd_bg_END      (7)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_dout_wr_wbg_START  (11)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_dout_wr_wbg_END    (11)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_din_rd_wbg_START   (15)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_din_rd_wbg_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_RGF_CC_SW_RST_UNION
 �ṹ˵��  : HOST_RGF_CC_SW_RST �Ĵ����ṹ���塣��ַƫ����:0x00A20����ֵ:0x00000000�����:32
 �Ĵ���˵��: Writing to this register generates a general reset to CryptoCell�� This reset takes about 4 core clock cycles�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cc_sw_rst_req   : 1;  /* bit[0]   : Writing '1' to this field generates a general reset to CryptoCell. Reset occurs only after AXI master and AXI slave are inactive (axim/s_sysreq is generated). */
        unsigned int  cc_sw_rst_force : 1;  /* bit[1]   : Writing '1' to this field generates a general reset to CryptoCell, even if the AXI master or slave are busy. This bit should only be used in case the AXI master or slave are stuck at "BUSY" state. In this case, "CC_SW_RST_REQ" cannot be used. As when using this field, a reset is forced without waiting for the AXI master and slave to return to idle, a system hang may be caused. In which case, it may be required to reset the AXI bus after using this field. */
        unsigned int  axis_sysreq     : 1;  /* bit[2]   : Writing '1' sets the AXI slave into wait state, in which pending transactions are completed, but no new transactions are served. Writing '0' is not supported by the Host, as no new transactions are served. */
        unsigned int  axim_sysreq     : 1;  /* bit[3]   : Writing '1' sets the AXI master into wait state, in which pending transactions are completed, but no new transactions are served. Writing '0' sets the AXI master back to normal state. */
        unsigned int  reserved        : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_RGF_CC_SW_RST_UNION;
#endif
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_cc_sw_rst_req_START    (0)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_cc_sw_rst_req_END      (0)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_cc_sw_rst_force_START  (1)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_cc_sw_rst_force_END    (1)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_axis_sysreq_START      (2)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_axis_sysreq_END        (2)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_axim_sysreq_START      (3)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_axim_sysreq_END        (3)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_RGF_SIGNATURE_UNION
 �ṹ˵��  : HOST_RGF_SIGNATURE �Ĵ����ṹ���塣��ַƫ����:0x00A24����ֵ:0xD5C63000�����:32
 �Ĵ���˵��: This register holds the CryptoCell product signature��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_signature : 32; /* bit[0-31]: Identification ��signature��: always returns a fixed value, used by Host driver to verify CryptoCell presence at this address. */
    } reg;
} SOC_SECENG_S_HOST_RGF_SIGNATURE_UNION;
#endif
#define SOC_SECENG_S_HOST_RGF_SIGNATURE_host_signature_START  (0)
#define SOC_SECENG_S_HOST_RGF_SIGNATURE_host_signature_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_BOOT_UNION
 �ṹ˵��  : HOST_BOOT �Ĵ����ṹ���塣��ַƫ����:0x00A28����ֵ:0x5FFBDACE�����:32
 �Ĵ���˵��: This register holds the values of CryptoCell's pre-synthesis flags
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  power_gating_exists     : 1;  /* bit[0]  : Indicates if CryptoCell includes Power gating:
                                                                 �� 1'b0 - CryptoCell does not include Power Gating
                                                                 �� 1'b1 - CryptoCell includes Power Gating */
        unsigned int  large_rkek              : 1;  /* bit[1]  : Indicates the size of the HW key (KDR(RKEK)):
                                                                 �� 1'b0 - 128b
                                                                 �� 1'b1 - 256b */
        unsigned int  hask_in_fuses           : 1;  /* bit[2]  : If set, indicates that the Hash value of KDR (RKEK) is saved in the NVM. */
        unsigned int  ext_mem_secured         : 1;  /* bit[3]  : Indicates if the external memory is secured:
                                                                 �� 1'b0 - the memory is not secure (keys should be encrypted).
                                                                 �� 1'b1 - memory is secure. */
        unsigned int  reserved_0              : 1;  /* bit[4]  : ���� */
        unsigned int  rkek_ecc_exists_n       : 1;  /* bit[5]  : If set indicates that the RKEK ECC is saved in not saved in the NVM */
        unsigned int  sram_size               : 3;  /* bit[6-8]: Indicates the SRAM size:
                                                                 �� 0 - there is no SRAM.
                                                                 �� 1 - SRAM size is 4 KB.
                                                                 �� 2 - SRAM size is 8 KB.
                                                                 �� 3 - SRAM size is 16 KB.
                                                                 �� 4 - SRAM size is 32 KB.
                                                                 �� 5 - SRAM size is 64 KB. */
        unsigned int  dscrptr_exists          : 1;  /* bit[9]  : Indicates if CryptoCell includes descriptors queues:
                                                                 �� 1'b0 - CryptoCell does not include descriptor queues.
                                                                 �� 1'b1 - CryptoCell includes descriptor queues. */
        unsigned int  pau__exists             : 1;  /* bit[10] : Indicates if CryptoCell includes the PAU module:
                                                                 �� 1'b0 - CryptoCell does not include the PAU module.
                                                                 �� 1'b1 - CryptoCell includes the PAU module. */
        unsigned int  rng_exists              : 1;  /* bit[11] : Indicates if CryptoCell includes the RNG module:
                                                                 �� 1'b0 - CryptoCell does not include the RNG module.
                                                                 �� 1'b1 - CryptoCell includes the RNG module. */
        unsigned int  pka_exists              : 1;  /* bit[12] : Indicates if CryptoCell includes the PKA engine:
                                                                 �� 1'b0 - CryptoCell does not include the PKA engine.
                                                                 �� 1'b1 - CryptoCell includes the PKA engine. */
        unsigned int  reserved_1              : 1;  /* bit[13] : ���� */
        unsigned int  sha_512_prsnt           : 1;  /* bit[14] : Indicates if HASH engine supports SHA 512 and SHA 384:
                                                                 �� 1'b0 - The HASH engine does not support SHA 512 and SHA 384.
                                                                 �� 1'b1 - The HASH engine supports SHA 512 and SHA 384. */
        unsigned int  sha_256_prsnt           : 1;  /* bit[15] : Indicates if HASH engine supports SHA 256 and SHA 224
                                                                 �� 1'b0 - The HASH engine does not support SHA 256 and SHA 224
                                                                 �� 1'b1 - The HASH engine supports SHA 256 and SHA 224 */
        unsigned int  md5_prsnt               : 1;  /* bit[16] : Indicates if HASH engine supports MD5.
                                                                 �� 1'b0 - The HASH engine does not support MD5.
                                                                 �� 1'b1 - The HASH engine supports MD5. */
        unsigned int  hash_exists             : 1;  /* bit[17] : Indicates if CryptoCell includes the HASH engine:
                                                                 �� 1'b0 - CryptoCell does not include the HASH engine.
                                                                 �� 1'b1 - CryptoCell includes the HASH engine. */
        unsigned int  reserved_2              : 1;  /* bit[18] : ���� */
        unsigned int  des_exists              : 1;  /* bit[19] : Indicates if CryptoCell includes the DES engine:
                                                                 �� 1'b0 - CryptoCell does not include the DES engine.
                                                                 �� 1'b1 - CryptoCell includes the DES engine. */
        unsigned int  aes_xcbc_mac_exists     : 1;  /* bit[20] : Indicates if AES engine supports AES XCBC-MAC:
                                                                 �� 1'b0 - The AES engine does not support AES XCBC-MAC.
                                                                 �� 1'b1 - The AES engine supports AES XCBC-MAC. */
        unsigned int  aes_cmac_exists         : 1;  /* bit[21] : Indicates if AES engine supports AES CMAC:
                                                                 �� 1'b0 - The AES engine does not support AES CMAC..
                                                                 �� 1'b1 - The AES engine supports AES CMAC. */
        unsigned int  aes_ccm_exists          : 1;  /* bit[22] : Indicates if AES engine supports AES CCM:
                                                                 �� 1'b0 - The AES engine does not support AES CCM.
                                                                 �� 1'b1 - The AES engine supports AES CCM. */
        unsigned int  aes_xex_hw_t_calc       : 1;  /* bit[23] : Indicates if AES engine supports automatic HW XTS-AES 'T' calculation in data unit boundaries:
                                                                 �� 1'b0 - The AES engine does not support automatic 'T' calculation.
                                                                 �� 1'b1 - The AES engine supports automatic 'T' calculation. */
        unsigned int  aes_xex_exists          : 1;  /* bit[24] : Indicates if AES engine supports XTS-AES:
                                                                 �� 1'b0 - The AES engine does not support XTS-AES.
                                                                 �� 1'b1 - The AES engine supports XTS-AES. */
        unsigned int  ctr_exists              : 1;  /* bit[25] : Indicates if AES engine supports automatic AES CTR:
                                                                 �� 1'b0 - The AES engine does not support AES CTR.
                                                                 �� 1'b1 - The AES engine supports AES CTR. */
        unsigned int  aes_din_byte_resolution : 1;  /* bit[26] : Indicates if AES engine supports operations in resolution of bytes, or in resolution of AES blocks:
                                                                 �� 1'b0 - The AES engine support only full AES blocks (16 bytes) operations.
                                                                 �� 1'b1 - The AES engine supports operations in any size (in byte resolution).. */
        unsigned int  tunneling_enb           : 1;  /* bit[27] : reserved */
        unsigned int  support_256_192_key     : 1;  /* bit[28] : Indicates if AES engine supports all key sizes, or only 128b keys:
                                                                 �� 1'b0 - The AES engine supports only 128b keys.
                                                                 �� 1'b1 - The AES engine supports all key sizes (128/192/256b). */
        unsigned int  only_encrypt            : 1;  /* bit[29] : Indicates if AES engine supports only encrypt operations or both encrypt and decrypt operations:
                                                                 �� 1'b0 - The AES engine supports encrypt and decrypt operations.
                                                                 �� 1'b1 - The AES engine supports only encrypt operations. */
        unsigned int  aes_exists              : 1;  /* bit[30] : Indicates if CryptoCell includes the AES engine:
                                                                 �� 1'b0 - CryptoCell does not include the AES engine.
                                                                 �� 1'b1 - CryptoCell includes the AES engine. */
        unsigned int  reserved_3              : 1;  /* bit[31] : ���� */
    } reg;
} SOC_SECENG_S_HOST_BOOT_UNION;
#endif
#define SOC_SECENG_S_HOST_BOOT_power_gating_exists_START      (0)
#define SOC_SECENG_S_HOST_BOOT_power_gating_exists_END        (0)
#define SOC_SECENG_S_HOST_BOOT_large_rkek_START               (1)
#define SOC_SECENG_S_HOST_BOOT_large_rkek_END                 (1)
#define SOC_SECENG_S_HOST_BOOT_hask_in_fuses_START            (2)
#define SOC_SECENG_S_HOST_BOOT_hask_in_fuses_END              (2)
#define SOC_SECENG_S_HOST_BOOT_ext_mem_secured_START          (3)
#define SOC_SECENG_S_HOST_BOOT_ext_mem_secured_END            (3)
#define SOC_SECENG_S_HOST_BOOT_rkek_ecc_exists_n_START        (5)
#define SOC_SECENG_S_HOST_BOOT_rkek_ecc_exists_n_END          (5)
#define SOC_SECENG_S_HOST_BOOT_sram_size_START                (6)
#define SOC_SECENG_S_HOST_BOOT_sram_size_END                  (8)
#define SOC_SECENG_S_HOST_BOOT_dscrptr_exists_START           (9)
#define SOC_SECENG_S_HOST_BOOT_dscrptr_exists_END             (9)
#define SOC_SECENG_S_HOST_BOOT_pau__exists_START              (10)
#define SOC_SECENG_S_HOST_BOOT_pau__exists_END                (10)
#define SOC_SECENG_S_HOST_BOOT_rng_exists_START               (11)
#define SOC_SECENG_S_HOST_BOOT_rng_exists_END                 (11)
#define SOC_SECENG_S_HOST_BOOT_pka_exists_START               (12)
#define SOC_SECENG_S_HOST_BOOT_pka_exists_END                 (12)
#define SOC_SECENG_S_HOST_BOOT_sha_512_prsnt_START            (14)
#define SOC_SECENG_S_HOST_BOOT_sha_512_prsnt_END              (14)
#define SOC_SECENG_S_HOST_BOOT_sha_256_prsnt_START            (15)
#define SOC_SECENG_S_HOST_BOOT_sha_256_prsnt_END              (15)
#define SOC_SECENG_S_HOST_BOOT_md5_prsnt_START                (16)
#define SOC_SECENG_S_HOST_BOOT_md5_prsnt_END                  (16)
#define SOC_SECENG_S_HOST_BOOT_hash_exists_START              (17)
#define SOC_SECENG_S_HOST_BOOT_hash_exists_END                (17)
#define SOC_SECENG_S_HOST_BOOT_des_exists_START               (19)
#define SOC_SECENG_S_HOST_BOOT_des_exists_END                 (19)
#define SOC_SECENG_S_HOST_BOOT_aes_xcbc_mac_exists_START      (20)
#define SOC_SECENG_S_HOST_BOOT_aes_xcbc_mac_exists_END        (20)
#define SOC_SECENG_S_HOST_BOOT_aes_cmac_exists_START          (21)
#define SOC_SECENG_S_HOST_BOOT_aes_cmac_exists_END            (21)
#define SOC_SECENG_S_HOST_BOOT_aes_ccm_exists_START           (22)
#define SOC_SECENG_S_HOST_BOOT_aes_ccm_exists_END             (22)
#define SOC_SECENG_S_HOST_BOOT_aes_xex_hw_t_calc_START        (23)
#define SOC_SECENG_S_HOST_BOOT_aes_xex_hw_t_calc_END          (23)
#define SOC_SECENG_S_HOST_BOOT_aes_xex_exists_START           (24)
#define SOC_SECENG_S_HOST_BOOT_aes_xex_exists_END             (24)
#define SOC_SECENG_S_HOST_BOOT_ctr_exists_START               (25)
#define SOC_SECENG_S_HOST_BOOT_ctr_exists_END                 (25)
#define SOC_SECENG_S_HOST_BOOT_aes_din_byte_resolution_START  (26)
#define SOC_SECENG_S_HOST_BOOT_aes_din_byte_resolution_END    (26)
#define SOC_SECENG_S_HOST_BOOT_tunneling_enb_START            (27)
#define SOC_SECENG_S_HOST_BOOT_tunneling_enb_END              (27)
#define SOC_SECENG_S_HOST_BOOT_support_256_192_key_START      (28)
#define SOC_SECENG_S_HOST_BOOT_support_256_192_key_END        (28)
#define SOC_SECENG_S_HOST_BOOT_only_encrypt_START             (29)
#define SOC_SECENG_S_HOST_BOOT_only_encrypt_END               (29)
#define SOC_SECENG_S_HOST_BOOT_aes_exists_START               (30)
#define SOC_SECENG_S_HOST_BOOT_aes_exists_END                 (30)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_PROVISION_CONST_MASK_UNION
 �ṹ˵��  : HOST_PROVISION_CONST_MASK �Ĵ����ṹ���塣��ַƫ����:0x00A30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Provisioning constant mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  provision_mask : 1;  /* bit[0]   : Writing 1 to this field masks the provision constant. */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_PROVISION_CONST_MASK_UNION;
#endif
#define SOC_SECENG_S_HOST_PROVISION_CONST_MASK_provision_mask_START  (0)
#define SOC_SECENG_S_HOST_PROVISION_CONST_MASK_provision_mask_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_CRYPTOKEY_SEL_UNION
 �ṹ˵��  : HOST_CRYPTOKEY_SEL �Ĵ����ṹ���塣��ַƫ����:0x00A38����ֵ:0x00000000�����:32
 �Ĵ���˵��: AES hardware key select
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_crypto_key : 2;  /* bit[0-1] : Select the source of the HW key that is used by the AES engine:
                                                         �� 2'h0 - RKEK
                                                         �� 2'h1 - the hard coded provision constant.
                                                         �� 2'h2 - the session key. 
                                                         NOTE! if the 'MASK_PROV_CONST' register is set, and the 'CRYPTOKEY_SEL' is set to 1, then the HW key that is connected to the AES engine is zero. */
        unsigned int  reserved       : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_CRYPTOKEY_SEL_UNION;
#endif
#define SOC_SECENG_S_HOST_CRYPTOKEY_SEL_sel_crypto_key_START  (0)
#define SOC_SECENG_S_HOST_CRYPTOKEY_SEL_sel_crypto_key_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_HOST_CRY_ACCESS_EN_UNION
 �ṹ˵��  : HOST_HOST_CRY_ACCESS_EN �Ĵ����ṹ���塣��ַƫ����:0x0A44����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines whether the Host has access to the cry_kernel registers directly (compatibility mode) and not only through the descriptors�� The default value is 0 - no access��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_cry_access_en : 1;  /* bit[0]   : This field defines whether the Host has access to the cry_kernel registers directly (compatibility mode) and not only through the descriptors. The default value is 0 - no access. */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_HOST_CRY_ACCESS_EN_UNION;
#endif
#define SOC_SECENG_S_HOST_HOST_CRY_ACCESS_EN_host_cry_access_en_START  (0)
#define SOC_SECENG_S_HOST_HOST_CRY_ACCESS_EN_host_cry_access_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_DCU_EN_UNION
 �ṹ˵��  : HOST_DCU_EN �Ĵ����ṹ���塣��ַƫ����:0x0A64����ֵ:0x00000000�����:32
 �Ĵ���˵��: The DCU��Debug Control Unit��enable register��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  secure_CPU_dbgen_en      : 1;  /* bit[0]    : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����MCPU��dbgen�ź��Լ�M3��M7��dbgen�źš�
                                                                    д��bitΪ1��MCPU��dbgen������Ϊ0x1��
                                                                    д��bitΪ0��MCPU��dbgen������Ϊ0x0��
                                                                    ͬʱд�üĴ�����bit2��bit0Ϊ1����M3��M7��dbgen�źű�����Ϊ0x1�� */
        unsigned int  secure_CPU_niden_en      : 1;  /* bit[1]    : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����MCPU��niden�źź�M7��niden�źš�
                                                                    д��bitΪ1��MCPU��niden������Ϊ0x1��
                                                                    д��bitΪ0��MCPU��niden������Ϊ0x0��
                                                                    ͬʱд�üĴ�����bit3��bit1Ϊ1����M7��niden�źű�����Ϊ0x1�� */
        unsigned int  secure_CPU_spiden_en     : 1;  /* bit[2]    : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����MCPU��M7��spiden�ź��Լ�M3��M7��dbgen�źš�
                                                                    д��bitΪ1��MCPU��M7��spiden������Ϊ0x1��
                                                                    д��bitΪ0��MCPU��M7��spiden������Ϊ0x0��
                                                                    ͬʱд�üĴ�����bit2��bit0Ϊ1����M3��M7��dbgen�źű�����Ϊ0x1�� */
        unsigned int  secure_CPU_spniden_en    : 1;  /* bit[3]    : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����MCPU��spniden�źź�M7��niden�źš�
                                                                    д��bitΪ1��MCPU��spniden������Ϊ0x1��
                                                                    д��bitΪ0��MCPU��spniden������Ϊ0x0��
                                                                    ͬʱд�üĴ�����bit3��bit1Ϊ1����M7��niden�źű�����Ϊ0x1�� */
        unsigned int  switch_CPU_dbgen_en      : 1;  /* bit[4]    : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����A53��MAIA��dbgen�źţ�
                                                                    д��bitΪ1��A53��MAIA��dbgen������Ϊ0x1��
                                                                    д��bitΪ0��A53��MAIA��dbgen������Ϊ0x0�� */
        unsigned int  switch_CPU_niden_en      : 1;  /* bit[5]    : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����A53��MAIA�Լ�CCI400��niden�źţ�
                                                                    д��bitΪ1��A53��MAIA�Լ�CCI400��niden������Ϊ0x1��
                                                                    д��bitΪ0��A53��MAIA�Լ�CCI400��niden������Ϊ0x0�� */
        unsigned int  switch_CPU_spiden_en     : 1;  /* bit[6]    : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����A53��MAIA��spiden�źţ�
                                                                    д��bitΪ1��A53��MAIA��spiden������Ϊ0x1��
                                                                    д��bitΪ0��A53��MAIA��spiden������Ϊ0x0�� */
        unsigned int  switch_CPU_spniden_en    : 1;  /* bit[7]    : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����A53��MAIA�Լ�CCI400��spniden�źţ�
                                                                    д��bitΪ1��A53��MAIA�Լ�CCI400��spniden������Ϊ0x1��
                                                                    д��bitΪ0��A53��MAIA�Լ�CCI400��spniden������Ϊ0x0�� */
        unsigned int  nonsecure_CPU_dbgen_en   : 1;  /* bit[8]    : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����ISP A7��dbgen�źţ�
                                                                    д��bitΪ1��ISP A7��dbgen������Ϊ0x1��
                                                                    д��bitΪ0��ISP A7��dbgen������Ϊ0x0�� */
        unsigned int  nonsecure_CPU_niden_en   : 1;  /* bit[9]    : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����ISP A7��niden�źţ�
                                                                    д��bitΪ1��ISP A7��niden������Ϊ0x1��
                                                                    д��bitΪ0��ISP A7��niden������Ϊ0x0�� */
        unsigned int  nonsecure_CPU_spiden_en  : 1;  /* bit[10]   : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����ISP A7��spiden�źţ�
                                                                    д��bitΪ1��ISP A7��spiden������Ϊ0x1��
                                                                    д��bitΪ0��ISP A7��spiden������Ϊ0x0�� */
        unsigned int  nonsecure_CPU_spniden_en : 1;  /* bit[11]   : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����ISP A7��spniden�źţ�
                                                                    д��bitΪ1��ISP A7��spniden������Ϊ0x1��
                                                                    д��bitΪ0��ISP A7��spniden������Ϊ0x0�� */
        unsigned int  reserved_0               : 5;  /* bit[12-16]: ���� */
        unsigned int  ivp_dsp_dbgen_en         : 1;  /* bit[17]   : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����IVP DSP��dbgen�źţ�
                                                                    д��bitΪ1��IVP DSP��dbgen������Ϊ0x1��
                                                                    д��bitΪ0��IVP DSP��dbgen������Ϊ0x0�� */
        unsigned int  hifi_dsp_dbgen_en        : 1;  /* bit[18]   : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����hifi DSP��dbgen�źţ�
                                                                    д��bitΪ1��hifi DSP��dbgen������Ϊ0x1��
                                                                    д��bitΪ0��hifi DSP��dbgen������Ϊ0x0�� */
        unsigned int  BBE16_dsp_dbgen_en       : 1;  /* bit[19]   : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����BBE16��dbgen�źţ�
                                                                    д��bitΪ1��BBE16��dbgen������Ϊ0x1��
                                                                    д��bitΪ0��BBE16��dbgen������Ϊ0x0�� */
        unsigned int  coresight_deviceen_en    : 1;  /* bit[20]   : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����coresight��deviceen�źţ�
                                                                    д��bitΪ1��coresight��deviceen������Ϊ0x1��
                                                                    д��bitΪ0��coresight��deviceen������Ϊ0x0�� */
        unsigned int  coresight_dbgen_en       : 1;  /* bit[21]   : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����coresight��dbgen�źţ�
                                                                    д��bitΪ1��coresight��dbgen������Ϊ0x1��
                                                                    д��bitΪ0��coresight��dbgen������Ϊ0x0�� */
        unsigned int  coresight_niden_en       : 1;  /* bit[22]   : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����coresight��niden�źţ�
                                                                    д��bitΪ1��coresight��niden������Ϊ0x1��
                                                                    д��bitΪ0��coresight��niden������Ϊ0x0�� */
        unsigned int  coresight_spiden_en      : 1;  /* bit[23]   : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����coresight��spiden�źţ�
                                                                    д��bitΪ1��coresight��spiden������Ϊ0x1��
                                                                    д��bitΪ0��coresight��spiden������Ϊ0x0�� */
        unsigned int  coresight_spniden_en     : 1;  /* bit[24]   : ��bit����debug�ȼ�Ϊ֤����֤��ʽ��efuse bit2025Ϊ0��efuse bit2026Ϊ1����coresight��spniden�źţ�
                                                                    д��bitΪ1��coresight��spniden������Ϊ0x1��
                                                                    д��bitΪ0��coresight��spniden������Ϊ0x0�� */
        unsigned int  reserved_1               : 6;  /* bit[25-30]: ���� */
        unsigned int  lock_bit                 : 1;  /* bit[31]   : Writing 1 to this field locks the DCU_EN bits for further writing.
                                                                    ��bitΪ���Ĵ�����д��������λ��һ����bit��д1֮���ٸ�д���Ĵ�����������Ч�� */
    } reg;
} SOC_SECENG_S_HOST_DCU_EN_UNION;
#endif
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_dbgen_en_START       (0)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_dbgen_en_END         (0)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_niden_en_START       (1)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_niden_en_END         (1)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_spiden_en_START      (2)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_spiden_en_END        (2)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_spniden_en_START     (3)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_spniden_en_END       (3)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_dbgen_en_START       (4)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_dbgen_en_END         (4)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_niden_en_START       (5)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_niden_en_END         (5)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_spiden_en_START      (6)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_spiden_en_END        (6)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_spniden_en_START     (7)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_spniden_en_END       (7)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_dbgen_en_START    (8)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_dbgen_en_END      (8)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_niden_en_START    (9)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_niden_en_END      (9)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_spiden_en_START   (10)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_spiden_en_END     (10)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_spniden_en_START  (11)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_spniden_en_END    (11)
#define SOC_SECENG_S_HOST_DCU_EN_ivp_dsp_dbgen_en_START          (17)
#define SOC_SECENG_S_HOST_DCU_EN_ivp_dsp_dbgen_en_END            (17)
#define SOC_SECENG_S_HOST_DCU_EN_hifi_dsp_dbgen_en_START         (18)
#define SOC_SECENG_S_HOST_DCU_EN_hifi_dsp_dbgen_en_END           (18)
#define SOC_SECENG_S_HOST_DCU_EN_BBE16_dsp_dbgen_en_START        (19)
#define SOC_SECENG_S_HOST_DCU_EN_BBE16_dsp_dbgen_en_END          (19)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_deviceen_en_START     (20)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_deviceen_en_END       (20)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_dbgen_en_START        (21)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_dbgen_en_END          (21)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_niden_en_START        (22)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_niden_en_END          (22)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_spiden_en_START       (23)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_spiden_en_END         (23)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_spniden_en_START      (24)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_spniden_en_END        (24)
#define SOC_SECENG_S_HOST_DCU_EN_lock_bit_START                  (31)
#define SOC_SECENG_S_HOST_DCU_EN_lock_bit_END                    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_SECURE_TIMER_BIST_KICK_UNION
 �ṹ˵��  : HOST_SECURE_TIMER_BIST_KICK �Ĵ����ṹ���塣��ַƫ����:0x0A68����ֵ:0x00000000�����:32
 �Ĵ���˵��: Secure Timer BIST Kick signal��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_secure_timer_bist_kick : 1;  /* bit[0]   : Secure Timer BIST Kick signal. The BIST starts at the following AO_CLK tick. */
        unsigned int  reserved                    : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_SECURE_TIMER_BIST_KICK_UNION;
#endif
#define SOC_SECENG_S_HOST_SECURE_TIMER_BIST_KICK_host_secure_timer_bist_kick_START  (0)
#define SOC_SECENG_S_HOST_SECURE_TIMER_BIST_KICK_host_secure_timer_bist_kick_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_SECURE_TIMER_BIST_VAL_UNION
 �ṹ˵��  : HOST_SECURE_TIMER_BIST_VAL �Ĵ����ṹ���塣��ַƫ����:0x0A6C����ֵ:0x00000000�����:32
 �Ĵ���˵��: this register holds the Secure Timer BIST result��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_secure_timer_bist_val : 16; /* bit[0-15] : Secure Timer BIST result. */
        unsigned int  reserved                   : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_SECURE_TIMER_BIST_VAL_UNION;
#endif
#define SOC_SECENG_S_HOST_SECURE_TIMER_BIST_VAL_host_secure_timer_bist_val_START  (0)
#define SOC_SECENG_S_HOST_SECURE_TIMER_BIST_VAL_host_secure_timer_bist_val_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_CC_AO_TEST_UNION
 �ṹ˵��  : HOST_CC_AO_TEST �Ĵ����ṹ���塣��ַƫ����:0x0A70����ֵ:0x00000000�����:32
 �Ĵ���˵��: Writing to this register sets/resets the CryptoCell to Always-On test signal��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_cc_ao_test : 1;  /* bit[0]   : CryptoCell-Secure to Always-On test signal value. */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_CC_AO_TEST_UNION;
#endif
#define SOC_SECENG_S_HOST_CC_AO_TEST_host_cc_ao_test_START  (0)
#define SOC_SECENG_S_HOST_CC_AO_TEST_host_cc_ao_test_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_RST_UNION
 �ṹ˵��  : HOST_LOW_RES_SECURE_TIMER_RST �Ĵ����ṹ���塣��ַƫ����:0x0A74����ֵ:0x00000000�����:32
 �Ĵ���˵��: Writing to this register resets the low-resolution Secure Timer (residing in the Always-On model)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_low_res_secure_timer_rst : 1;  /* bit[0]   : Reset the low-resolution Secure Timer (residing in the Always-On model). */
        unsigned int  reserved                      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_RST_UNION;
#endif
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_RST_host_low_res_secure_timer_rst_START  (0)
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_RST_host_low_res_secure_timer_rst_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_0_UNION
 �ṹ˵��  : HOST_LOW_RES_SECURE_TIMER_0 �Ĵ����ṹ���塣��ַƫ����:0x0A78����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the low-resolution Secure Timer value, bits 31:0 (residing in the Always-On model)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_low_res_secure_timer_0 : 32; /* bit[0-31]: Lower 32 bits of the low-resolution Secure Timer. */
    } reg;
} SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_0_UNION;
#endif
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_0_host_low_res_secure_timer_0_START  (0)
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_0_host_low_res_secure_timer_0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_1_UNION
 �ṹ˵��  : HOST_LOW_RES_SECURE_TIMER_1 �Ĵ����ṹ���塣��ַƫ����:0x0A7C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the low-resolution Secure Timer value, bits 63:32 (residing in the Always-On model)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_low_res_secure_timer_1 : 32; /* bit[0-31]: Upper 32 bits of the low-resolution Secure Timer. */
    } reg;
} SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_1_UNION;
#endif
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_1_host_low_res_secure_timer_1_START  (0)
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_1_host_low_res_secure_timer_1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_RST_UNION
 �ṹ˵��  : HOST_HIGH_RES_SECURE_TIMER_RST �Ĵ����ṹ���塣��ַƫ����:0x0A80����ֵ:0x00000000�����:32
 �Ĵ���˵��: Writing to this register resets the high-resolution Secure Timer��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_high_res_secure_timer_rst : 1;  /* bit[0]   : Reset the high-resolution Secure Timer. */
        unsigned int  reserved                       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_RST_UNION;
#endif
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_RST_host_high_res_secure_timer_rst_START  (0)
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_RST_host_high_res_secure_timer_rst_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_0_UNION
 �ṹ˵��  : HOST_HIGH_RES_SECURE_TIMER_0 �Ĵ����ṹ���塣��ַƫ����:0x0A84����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the high-resolution Secure Timer value, bits 31:0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_high_res_secure_timer_0 : 32; /* bit[0-31]: Lower 32 bits of the high-resolution Secure Timer. */
    } reg;
} SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_0_UNION;
#endif
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_0_host_high_res_secure_timer_0_START  (0)
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_0_host_high_res_secure_timer_0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_1_UNION
 �ṹ˵��  : HOST_HIGH_RES_SECURE_TIMER_1 �Ĵ����ṹ���塣��ַƫ����:0x0A88����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the high-resolution Secure Timer value, bits 39:32��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_high_res_secure_timer_1 : 8;  /* bit[0-7] : Upper 8 bits of the high-resolution Secure Timer. */
        unsigned int  reserved                     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_1_UNION;
#endif
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_1_host_high_res_secure_timer_1_START  (0)
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_1_host_high_res_secure_timer_1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_0_UNION
 �ṹ˵��  : HOST_HIGH_RES_SECURE_TIMER_TH_0 �Ĵ����ṹ���塣��ַƫ����:0x0A8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the high-resolution Secure Timer value, bits 31:0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_high_res_secure_timer_th_0 : 32; /* bit[0-31]: Lower 32 bits of the high-resolution Secure Timer threshold (threshold for Interrupt to be set) */
    } reg;
} SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_0_UNION;
#endif
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_0_host_high_res_secure_timer_th_0_START  (0)
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_0_host_high_res_secure_timer_th_0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_1_UNION
 �ṹ˵��  : HOST_HIGH_RES_SECURE_TIMER_TH_1 �Ĵ����ṹ���塣��ַƫ����:0x0A90����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the high-resolution Secure Timer value, bits 39:32��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_high_res_secure_timer_th_1 : 8;  /* bit[0-7] : Upper 8 bits of the high-resolution Secure Timer threshold (threshold for Interrupt to be set) */
        unsigned int  reserved                        : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_1_UNION;
#endif
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_1_host_high_res_secure_timer_th_1_START  (0)
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_1_host_high_res_secure_timer_th_1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_0_UNION
 �ṹ˵��  : HOST_LATCHED_EXTERNAL_TIMER_0 �Ĵ����ṹ���塣��ַƫ����:0x0A94����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the latched value of the low-resolution Secure Timer, bits 31:0 (latched at reset of high-resolution timer)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_latched_external_timer_0 : 32; /* bit[0-31]: Lower 32 bits of the latched low-resolution Secure Timer value. */
    } reg;
} SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_0_UNION;
#endif
#define SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_0_host_latched_external_timer_0_START  (0)
#define SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_0_host_latched_external_timer_0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_1_UNION
 �ṹ˵��  : HOST_LATCHED_EXTERNAL_TIMER_1 �Ĵ����ṹ���塣��ַƫ����:0x0A98����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the latched value of the low-resolution Secure Timer, bits 64:32 (latched at reset of high-resolution timer)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_latched_external_timer_1 : 32; /* bit[0-31]: Upper 32 bits of the latched low-resolution Secure Timer value. */
    } reg;
} SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_1_UNION;
#endif
#define SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_1_host_latched_external_timer_1_START  (0)
#define SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_1_host_latched_external_timer_1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_NVM_CC_BOOT_UNION
 �ṹ˵��  : NVM_CC_BOOT �Ĵ����ṹ���塣��ַƫ����:0x00AA0����ֵ:0x00000006�����:32
 �Ĵ���˵��: reflects HW Defines in the NVM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0]   : ���� */
        unsigned int  large_rkek_local    : 1;  /* bit[1]   : This field defines the HW key size:
                                                              �� 1'b0 - 128bit
                                                              �� 1'b1 - 256bit */
        unsigned int  hash_in_fuses_local : 1;  /* bit[2]   : This field defines whether the NVM includes a HASH digest of the OEM key. */
        unsigned int  reserved_1          : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_SECENG_S_NVM_CC_BOOT_UNION;
#endif
#define SOC_SECENG_S_NVM_CC_BOOT_large_rkek_local_START     (1)
#define SOC_SECENG_S_NVM_CC_BOOT_large_rkek_local_END       (1)
#define SOC_SECENG_S_NVM_CC_BOOT_hash_in_fuses_local_START  (2)
#define SOC_SECENG_S_NVM_CC_BOOT_hash_in_fuses_local_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_AIB_ADDR_REG_UNION
 �ṹ˵��  : HOST_AIB_ADDR_REG �Ĵ����ṹ���塣��ַƫ����:0x00AA4����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register serves for indirect access to the NVM�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_aib_addr_reg : 12; /* bit[0-11] : The AIB address. Bit [1:0] should be 2'b0. */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: ���� */
        unsigned int  read_access       : 1;  /* bit[16]   : For read access, this field should be set to 1. */
        unsigned int  write_access      : 1;  /* bit[17]   : For write access, this field should be set to 1. */
        unsigned int  reserved_1        : 14; /* bit[18-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_AIB_ADDR_REG_UNION;
#endif
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_host_aib_addr_reg_START  (0)
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_host_aib_addr_reg_END    (11)
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_read_access_START        (16)
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_read_access_END          (16)
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_write_access_START       (17)
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_write_access_END         (17)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_AIB_WDATA_REG_UNION
 �ṹ˵��  : HOST_AIB_WDATA_REG �Ĵ����ṹ���塣��ַƫ����:0x00AA8����ֵ:0x00000000�����:32
 �Ĵ���˵��: The write data for AIB transactions should be written to this register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_aib_wdata_reg : 32; /* bit[0-31]: The write data for AIB transactions should be written to this field. */
    } reg;
} SOC_SECENG_S_HOST_AIB_WDATA_REG_UNION;
#endif
#define SOC_SECENG_S_HOST_AIB_WDATA_REG_host_aib_wdata_reg_START  (0)
#define SOC_SECENG_S_HOST_AIB_WDATA_REG_host_aib_wdata_reg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_AIB_RDATA_REG_UNION
 �ṹ˵��  : HOST_AIB_RDATA_REG �Ĵ����ṹ���塣��ַƫ����:0x00AAC����ֵ:0x00000000�����:32
 �Ĵ���˵��: The data for AIB transactions can be read from this register��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_aib_rdata_reg : 32; /* bit[0-31]: The data for AIB transactions can be read from this field. */
    } reg;
} SOC_SECENG_S_HOST_AIB_RDATA_REG_UNION;
#endif
#define SOC_SECENG_S_HOST_AIB_RDATA_REG_host_aib_rdata_reg_START  (0)
#define SOC_SECENG_S_HOST_AIB_RDATA_REG_host_aib_rdata_reg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AIB_FUSE_PROG_COMPLETED_UNION
 �ṹ˵��  : AIB_FUSE_PROG_COMPLETED �Ĵ����ṹ���塣��ַƫ����:0x00AB0����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register reflects the fuse_aib_prog_completed input, which indicates that the fuse programming was completed�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aib_fuse_prog_completed : 1;  /* bit[0]   : Indicates if the fuse programming operation has been completed. */
        unsigned int  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_AIB_FUSE_PROG_COMPLETED_UNION;
#endif
#define SOC_SECENG_S_AIB_FUSE_PROG_COMPLETED_aib_fuse_prog_completed_START  (0)
#define SOC_SECENG_S_AIB_FUSE_PROG_COMPLETED_aib_fuse_prog_completed_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AIB_FUSE_ACK_UNION
 �ṹ˵��  : AIB_FUSE_ACK �Ĵ����ṹ���塣��ַƫ����:0x00AB4����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register reflects the fuse_aib_ack input, which indicates that the AIB transaction was completed�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aib_fuse_ack_reg : 1;  /* bit[0]   : Indicates if the AIB transaction has been completed. */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_AIB_FUSE_ACK_UNION;
#endif
#define SOC_SECENG_S_AIB_FUSE_ACK_aib_fuse_ack_reg_START  (0)
#define SOC_SECENG_S_AIB_FUSE_ACK_aib_fuse_ack_reg_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AIB_DEBUG_STATUS_UNION
 �ṹ˵��  : AIB_DEBUG_STATUS �Ĵ����ṹ���塣��ַƫ����:0x00AB8����ֵ:0x00000000�����:32
 �Ĵ���˵��: AIB debug status register��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  forbidden_cpu_access : 1;  /* bit[0]   : Indicates that the last Host access operation was to forbidden area, changed after boot. */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_AIB_DEBUG_STATUS_UNION;
#endif
#define SOC_SECENG_S_AIB_DEBUG_STATUS_forbidden_cpu_access_START  (0)
#define SOC_SECENG_S_AIB_DEBUG_STATUS_forbidden_cpu_access_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_LCS_IS_VALID_UNION
 �ṹ˵��  : LCS_IS_VALID �Ĵ����ṹ���塣��ַƫ����:0x00ABC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Indicates that the LCS register holds a valid value�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lcs_is_valid_reg : 1;  /* bit[0]   : Indicates whether LCS is valid. */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_LCS_IS_VALID_UNION;
#endif
#define SOC_SECENG_S_LCS_IS_VALID_lcs_is_valid_reg_START  (0)
#define SOC_SECENG_S_LCS_IS_VALID_lcs_is_valid_reg_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_SESSION_KEY0_UNION
 �ṹ˵��  : HOST_SESSION_KEY0 �Ĵ����ṹ���塣��ַƫ����:0x00AC0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Bits [31:0] of the Session key
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  session_key0_reg : 32; /* bit[0-31]: Bits [31:0] of the Session key */
    } reg;
} SOC_SECENG_S_HOST_SESSION_KEY0_UNION;
#endif
#define SOC_SECENG_S_HOST_SESSION_KEY0_session_key0_reg_START  (0)
#define SOC_SECENG_S_HOST_SESSION_KEY0_session_key0_reg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_SESSION_KEY1_UNION
 �ṹ˵��  : HOST_SESSION_KEY1 �Ĵ����ṹ���塣��ַƫ����:0x00AC4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Bits [63:32] of the Session key
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  session_key1_reg : 32; /* bit[0-31]: Bits [63:32] of the Session key */
    } reg;
} SOC_SECENG_S_HOST_SESSION_KEY1_UNION;
#endif
#define SOC_SECENG_S_HOST_SESSION_KEY1_session_key1_reg_START  (0)
#define SOC_SECENG_S_HOST_SESSION_KEY1_session_key1_reg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_SESSION_KEY2_UNION
 �ṹ˵��  : HOST_SESSION_KEY2 �Ĵ����ṹ���塣��ַƫ����:0x00AC8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Bits [95:64] of the Session key
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  session_key2_reg : 32; /* bit[0-31]: Bits [95:64] of the Session key */
    } reg;
} SOC_SECENG_S_HOST_SESSION_KEY2_UNION;
#endif
#define SOC_SECENG_S_HOST_SESSION_KEY2_session_key2_reg_START  (0)
#define SOC_SECENG_S_HOST_SESSION_KEY2_session_key2_reg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_SESSION_KEY3_UNION
 �ṹ˵��  : HOST_SESSION_KEY3 �Ĵ����ṹ���塣��ַƫ����:0x00ACC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Bits [127:96] of the Session key�� Writing to this register also creates a write pulse toward the always-on module��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  session_key3_reg : 32; /* bit[0-31]: Bits [127:96] of the Session key.
                                                           also kick for write the seesion key.
                                                           writing to this register also creates write pulse toward the always-on module */
    } reg;
} SOC_SECENG_S_HOST_SESSION_KEY3_UNION;
#endif
#define SOC_SECENG_S_HOST_SESSION_KEY3_session_key3_reg_START  (0)
#define SOC_SECENG_S_HOST_SESSION_KEY3_session_key3_reg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_SEESION_KEY_IS_VALID_UNION
 �ṹ˵��  : HOST_SEESION_KEY_IS_VALID �Ĵ����ṹ���塣��ַƫ����:0x00AD0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Indication from the always-on register that the session key is valid��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  session_key_is_valid : 1;  /* bit[0]   : Indicates that session key is ready for use. */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_SEESION_KEY_IS_VALID_UNION;
#endif
#define SOC_SECENG_S_HOST_SEESION_KEY_IS_VALID_session_key_is_valid_START  (0)
#define SOC_SECENG_S_HOST_SEESION_KEY_IS_VALID_session_key_is_valid_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_LCS_REG_UNION
 �ṹ˵��  : LCS_REG �Ĵ����ṹ���塣��ַƫ����:0x00AD4����ֵ:0x00000005�����:32
 �Ĵ���˵��: The lifecycle state register�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lcs_reg             : 8;  /* bit[0-7]  : Indicates the LCS (Lifecycle State) value.
                                                               0x0:CM,Chip Manufacture LCS;
                                                               0x1:DM,Device Manufacture LCS;
                                                               0x3:Security Disabled LCS;
                                                               0x5:Security LCS;
                                                               0x7:RMA LCS;
                                                               others:Invalid */
        unsigned int  error_kdr_zero_cnt  : 1;  /* bit[8]    : Indication that the number of zeroes in the loaded KDR is not equal to the value set in the manufacture flag. */
        unsigned int  error_prov_zero_cnt : 1;  /* bit[9]    : Indication that the number of zeroes in the loaded PROVISION key is not equal to the value set in the manufacture flag. */
        unsigned int  reserved            : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_SECENG_S_LCS_REG_UNION;
#endif
#define SOC_SECENG_S_LCS_REG_lcs_reg_START              (0)
#define SOC_SECENG_S_LCS_REG_lcs_reg_END                (7)
#define SOC_SECENG_S_LCS_REG_error_kdr_zero_cnt_START   (8)
#define SOC_SECENG_S_LCS_REG_error_kdr_zero_cnt_END     (8)
#define SOC_SECENG_S_LCS_REG_error_prov_zero_cnt_START  (9)
#define SOC_SECENG_S_LCS_REG_error_prov_zero_cnt_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_CPC_SECURITY_DISABLE_UNION
 �ṹ˵��  : HOST_CPC_SECURITY_DISABLE �Ĵ����ṹ���塣��ַƫ����:0x00AD8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Host disable security for the current power cycle��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_security_disable : 1;  /* bit[0]   : Host disabled security for the Current Power Cycle (CPC), a.k.a. Temporary Security Disable mode. */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_CPC_SECURITY_DISABLE_UNION;
#endif
#define SOC_SECENG_S_HOST_CPC_SECURITY_DISABLE_host_security_disable_START  (0)
#define SOC_SECENG_S_HOST_CPC_SECURITY_DISABLE_host_security_disable_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_AO_CC_STATE_COUNTER_UNION
 �ṹ˵��  : HOST_AO_CC_STATE_COUNTER �Ĵ����ṹ���塣��ַƫ����:0x00ADC����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: The Always-On state counter��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_cc_state_counter : 32; /* bit[0-31]: This input reflects the state counter input from the persistent state IF. */
    } reg;
} SOC_SECENG_S_HOST_AO_CC_STATE_COUNTER_UNION;
#endif
#define SOC_SECENG_S_HOST_AO_CC_STATE_COUNTER_ao_cc_state_counter_START  (0)
#define SOC_SECENG_S_HOST_AO_CC_STATE_COUNTER_ao_cc_state_counter_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_CC_AO_STATE_COUNTER_INC_UNION
 �ṹ˵��  : HOST_CC_AO_STATE_COUNTER_INC �Ĵ����ṹ���塣��ַƫ����:0x00AE0����ֵ:0x00000000�����:32
 �Ĵ���˵��: State counter increment�� Writing any value to this address asserts the CC_AO_STATE_COUNTER_INC outputs for 1 cycle��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cc_ao_state_counter_inc : 1;  /* bit[0]   : Writing any value to this address asserts the CC_AO_STATE_COUNTER_INC outputs for 1 cycle. This operation is supposed to increment the external always-on state counter register. */
        unsigned int  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_CC_AO_STATE_COUNTER_INC_UNION;
#endif
#define SOC_SECENG_S_HOST_CC_AO_STATE_COUNTER_INC_cc_ao_state_counter_inc_START  (0)
#define SOC_SECENG_S_HOST_CC_AO_STATE_COUNTER_INC_cc_ao_state_counter_inc_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_AO_CC_IS_SD_UNION
 �ṹ˵��  : HOST_AO_CC_IS_SD �Ĵ����ṹ���塣��ַƫ����:0x00AE4����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register reflects the Host AO_CC_IS_SD input from the Always-On that determines the LCS is Secure-Disabled��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_cc_lcs_is_sd : 1;  /* bit[0]   : This field reflects the Host AO_CC_IS_SD input from the Always-On that determines the LCS is Secure-Disabled */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_AO_CC_IS_SD_UNION;
#endif
#define SOC_SECENG_S_HOST_AO_CC_IS_SD_ao_cc_lcs_is_sd_START  (0)
#define SOC_SECENG_S_HOST_AO_CC_IS_SD_ao_cc_lcs_is_sd_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_HOST_RMA_RKEK_WR_UNION
 �ṹ˵��  : HOST_RMA_RKEK_WR �Ĵ����ṹ���塣��ַƫ����:0x00AE8����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register interface is used to update the RKEK registers when the device is in RMA mode, The RKEK is updated by shifting when MSB word is written first�� After the eighth writing the registers are blocked for further writing�� (write -once)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_rma_rkek_write : 1;  /* bit[0]   : This field is used to update the RKEK registers when the device is in RMA mode, The RKEK is updated by shifting when MSB word is written first. After the eighth writing the registers are blocked for further writing. (write -once) */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_HOST_RMA_RKEK_WR_UNION;
#endif
#define SOC_SECENG_S_HOST_RMA_RKEK_WR_host_rma_rkek_write_START  (0)
#define SOC_SECENG_S_HOST_RMA_RKEK_WR_host_rma_rkek_write_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHT0_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT0 �Ĵ����ṹ���塣��ַƫ����:0x00B00����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT0_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT0_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT0_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHT1_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT1 �Ĵ����ṹ���塣��ַƫ����:0x00B04����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT1_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT1_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT1_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHT2_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT2 �Ĵ����ṹ���塣��ַƫ����:0x00B08����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT2_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT2_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT2_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHT3_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT3 �Ĵ����ṹ���塣��ַƫ����:0x00B0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT3_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT3_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT3_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHT4_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT4 �Ĵ����ṹ���塣��ַƫ����:0x00B10����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT4_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT4_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT4_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHT5_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT5 �Ĵ����ṹ���塣��ַƫ����:0x00B14����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT5_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT5_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT5_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHT8_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT8 �Ĵ����ṹ���塣��ַƫ����:0x00B20����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT8_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT8_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT8_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHT9_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT9 �Ĵ����ṹ���塣��ַƫ����:0x00B24����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=9��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT9_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT9_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT9_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHT10_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT10 �Ĵ����ṹ���塣��ַƫ����:0x00B28����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=10��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT10_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT10_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT10_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHT11_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT11 �Ĵ����ṹ���塣��ַƫ����:0x00B2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=11��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT11_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT11_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT11_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHTLAST0_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST0 �Ĵ����ṹ���塣��ַƫ����:0x00B40����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=0 and last indication bit set��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST0_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST0_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST0_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHTLAST1_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST1 �Ĵ����ṹ���塣��ַƫ����:0x00B44����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=1 and last indication bit set��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST1_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST1_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST1_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHTLAST2_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST2 �Ĵ����ṹ���塣��ַƫ����:0x00B48����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=1 and last indication bit set��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST2_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST2_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST2_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHTLAST3_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST3 �Ĵ����ṹ���塣��ַƫ����:0x00B4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=3 and last indication bit set��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST3_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST3_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST3_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHTLAST4_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST4 �Ĵ����ṹ���塣��ַƫ����:0x00B50����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=4 and last indication bit set��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST4_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST4_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST4_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHTLAST5_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST5 �Ĵ����ṹ���塣��ַƫ����:0x00B54����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=5 and last indication bit set��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST5_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST5_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST5_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHTLAST8_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST8 �Ĵ����ṹ���塣��ַƫ����:0x00B60����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=8 and last indication bit set��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST8_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST8_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST8_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHTLAST9_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST9 �Ĵ����ṹ���塣��ַƫ����:0x00B64����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=9 and last indication bit set��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST9_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST9_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST9_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHTLAST10_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST10 �Ĵ����ṹ���塣��ַƫ����:0x00B68����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=10 and last indication bit set��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST10_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST10_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST10_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_INFLIGHTLAST11_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST11 �Ĵ����ṹ���塣��ַƫ����:0x00B6C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=11 and last indication bit set��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST11_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST11_inflightcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST11_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_PIDTABLE0_UNION
 �ṹ˵��  : AXIM_PIDTABLE0 �Ĵ����ṹ���塣��ַƫ����:0x00B70����ֵ:0x00004000�����:32
 �Ĵ���˵��: This register holds the status of AXI port 0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pid_broken1 : 1;  /* bit[0]    : 1st part of broken burst is in the pipe */
        unsigned int  pid_broken2 : 1;  /* bit[1]    : 2nd part of broken burst is in the pipe */
        unsigned int  pid_oscntr  : 8;  /* bit[2-9]  : num of outstanding busrst for the selected port */
        unsigned int  pid_id      : 5;  /* bit[10-14]: ID of the selected port */
        unsigned int  reserved    : 17; /* bit[15-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_PIDTABLE0_UNION;
#endif
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_broken1_START  (0)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_broken1_END    (0)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_broken2_START  (1)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_broken2_END    (1)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_oscntr_START   (2)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_oscntr_END     (9)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_id_START       (10)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_id_END         (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_PIDTABLE1_UNION
 �ṹ˵��  : AXIM_PIDTABLE1 �Ĵ����ṹ���塣��ַƫ����:0x00B74����ֵ:0x00004000�����:32
 �Ĵ���˵��: This register holds the status of AXI port 1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pid_broken1 : 1;  /* bit[0]    : 1st part of broken burst is in the pipe */
        unsigned int  pid_broken2 : 1;  /* bit[1]    : 2nd part of broken burst is in the pipe */
        unsigned int  pid_oscntr  : 8;  /* bit[2-9]  : num of outstanding busrst for the selected port */
        unsigned int  pid_id      : 5;  /* bit[10-14]: ID of the selected port */
        unsigned int  reserved    : 17; /* bit[15-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_PIDTABLE1_UNION;
#endif
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_broken1_START  (0)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_broken1_END    (0)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_broken2_START  (1)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_broken2_END    (1)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_oscntr_START   (2)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_oscntr_END     (9)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_id_START       (10)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_id_END         (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_PIDTABLE2_UNION
 �ṹ˵��  : AXIM_PIDTABLE2 �Ĵ����ṹ���塣��ַƫ����:0x00B78����ֵ:0x00004000�����:32
 �Ĵ���˵��: This register holds the status of AXI port 2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pid_broken1 : 1;  /* bit[0]    : 1st part of broken burst is in the pipe */
        unsigned int  pid_broken2 : 1;  /* bit[1]    : 2nd part of broken burst is in the pipe */
        unsigned int  pid_oscntr  : 8;  /* bit[2-9]  : num of outstanding busrst for the selected port */
        unsigned int  pid_id      : 5;  /* bit[10-14]: ID of the selected port */
        unsigned int  reserved    : 17; /* bit[15-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_PIDTABLE2_UNION;
#endif
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_broken1_START  (0)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_broken1_END    (0)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_broken2_START  (1)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_broken2_END    (1)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_oscntr_START   (2)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_oscntr_END     (9)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_id_START       (10)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_id_END         (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_PIDTABLE3_UNION
 �ṹ˵��  : AXIM_PIDTABLE3 �Ĵ����ṹ���塣��ַƫ����:0x00B7C����ֵ:0x00004000�����:32
 �Ĵ���˵��: This register holds the status of AXI port 3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pid_broken1 : 1;  /* bit[0]    : 1st part of broken burst is in the pipe. */
        unsigned int  pid_broken2 : 1;  /* bit[1]    : 2nd part of broken burst is in the pipe */
        unsigned int  pid_oscntr  : 8;  /* bit[2-9]  : Number of outstanding bursts for the selected port. */
        unsigned int  pid_id      : 5;  /* bit[10-14]: ID of the selected port. */
        unsigned int  reserved    : 17; /* bit[15-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_PIDTABLE3_UNION;
#endif
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_broken1_START  (0)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_broken1_END    (0)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_broken2_START  (1)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_broken2_END    (1)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_oscntr_START   (2)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_oscntr_END     (9)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_id_START       (10)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_id_END         (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_COMP0_UNION
 �ṹ˵��  : AXIM_MON_COMP0 �Ĵ����ṹ���塣��ַƫ����:0x00B80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 0 */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP0_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP0_complastcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_COMP0_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_COMP1_UNION
 �ṹ˵��  : AXIM_MON_COMP1 �Ĵ����ṹ���塣��ַƫ����:0x00B84����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 1 */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP1_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP1_complastcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_COMP1_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_COMP2_UNION
 �ṹ˵��  : AXIM_MON_COMP2 �Ĵ����ṹ���塣��ַƫ����:0x00B88����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 2 */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP2_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP2_complastcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_COMP2_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_COMP3_UNION
 �ṹ˵��  : AXIM_MON_COMP3 �Ĵ����ṹ���塣��ַƫ����:0x00B8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 3 */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP3_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP3_complastcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_COMP3_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_COMP4_UNION
 �ṹ˵��  : AXIM_MON_COMP4 �Ĵ����ṹ���塣��ַƫ����:0x00B90����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 4 */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP4_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP4_complastcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_COMP4_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_COMP5_UNION
 �ṹ˵��  : AXIM_MON_COMP5 �Ĵ����ṹ���塣��ַƫ����:0x00B94����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 5 */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP5_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP5_complastcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_COMP5_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_COMP8_UNION
 �ṹ˵��  : AXIM_MON_COMP8 �Ĵ����ṹ���塣��ַƫ����:0x00BA0����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 8 */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP8_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP8_complastcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_COMP8_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_COMP9_UNION
 �ṹ˵��  : AXIM_MON_COMP9 �Ĵ����ṹ���塣��ַƫ����:0x00BA4����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=9��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 9 */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP9_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP9_complastcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_COMP9_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_COMP10_UNION
 �ṹ˵��  : AXIM_MON_COMP10 �Ĵ����ṹ���塣��ַƫ����:0x00BA8����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=10��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 10 */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP10_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP10_complastcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_COMP10_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_COMP11_UNION
 �ṹ˵��  : AXIM_MON_COMP11 �Ĵ����ṹ���塣��ַƫ����:0x00BAC����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=11��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 11 */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP11_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP11_complastcntr_START  (0)
#define SOC_SECENG_S_AXIM_MON_COMP11_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_RMAX_UNION
 �ṹ˵��  : AXIM_MON_RMAX �Ĵ����ṹ���塣��ַƫ����:0x00BB4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Maximal latency for read transactions��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rmax : 32; /* bit[0-31]: Measured maximal latency in CORE_CLK/64 clock cycles from last read. */
    } reg;
} SOC_SECENG_S_AXIM_MON_RMAX_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_RMAX_rmax_START  (0)
#define SOC_SECENG_S_AXIM_MON_RMAX_rmax_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_RMIN_UNION
 �ṹ˵��  : AXIM_MON_RMIN �Ĵ����ṹ���塣��ַƫ����:0x00BB8����ֵ:0x000007FF�����:32
 �Ĵ���˵��: Minimal latency for read transactions��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rmin : 32; /* bit[0-31]: Measured minimal latency in CORE_CLK/64 clock cycles from last read. */
    } reg;
} SOC_SECENG_S_AXIM_MON_RMIN_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_RMIN_rmin_START  (0)
#define SOC_SECENG_S_AXIM_MON_RMIN_rmin_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_WMAX_UNION
 �ṹ˵��  : AXIM_MON_WMAX �Ĵ����ṹ���塣��ַƫ����:0x00BBC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Maximal latency for write transactions��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wmax : 32; /* bit[0-31]: Measured maximal latency in CORE_CLK/64 clock cycles from last read. */
    } reg;
} SOC_SECENG_S_AXIM_MON_WMAX_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_WMAX_wmax_START  (0)
#define SOC_SECENG_S_AXIM_MON_WMAX_wmax_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_WMIN_UNION
 �ṹ˵��  : AXIM_MON_WMIN �Ĵ����ṹ���塣��ַƫ����:0x00BC0����ֵ:0x000007FF�����:32
 �Ĵ���˵��: Minimal latency for write transactions��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wmin : 32; /* bit[0-31]: Measured minimal latency in CORE_CLK/64 clock cycles from last read. */
    } reg;
} SOC_SECENG_S_AXIM_MON_WMIN_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_WMIN_wmin_START  (0)
#define SOC_SECENG_S_AXIM_MON_WMIN_wmin_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_MON_ERR_UNION
 �ṹ˵��  : AXIM_MON_ERR �Ĵ����ṹ���塣��ַƫ����:0x00BC4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error information��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bresp    : 2;  /* bit[0-1]  : BRESP of the captured error */
        unsigned int  bid      : 4;  /* bit[2-5]  : BID that caused the error */
        unsigned int  reserved_0: 1;  /* bit[6]    : ���� */
        unsigned int  reserved_1: 9;  /* bit[7-15] : ���� */
        unsigned int  rresp    : 2;  /* bit[16-17]: RRESP of the captured errro */
        unsigned int  rid      : 4;  /* bit[18-21]: RID that cause the error */
        unsigned int  reserved_2: 10; /* bit[22-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_MON_ERR_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_ERR_bresp_START     (0)
#define SOC_SECENG_S_AXIM_MON_ERR_bresp_END       (1)
#define SOC_SECENG_S_AXIM_MON_ERR_bid_START       (2)
#define SOC_SECENG_S_AXIM_MON_ERR_bid_END         (5)
#define SOC_SECENG_S_AXIM_MON_ERR_rresp_START     (16)
#define SOC_SECENG_S_AXIM_MON_ERR_rresp_END       (17)
#define SOC_SECENG_S_AXIM_MON_ERR_rid_START       (18)
#define SOC_SECENG_S_AXIM_MON_ERR_rid_END         (21)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_RDSTAT_UNION
 �ṹ˵��  : AXIM_RDSTAT �Ĵ����ṹ���塣��ַƫ����:0x00BC8����ֵ:0x00000000�����:32
 �Ĵ���˵��: read channel status��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  oscntr   : 4;  /* bit[0-3] : total number of outstanding bursts */
        unsigned int  reserved : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_RDSTAT_UNION;
#endif
#define SOC_SECENG_S_AXIM_RDSTAT_oscntr_START    (0)
#define SOC_SECENG_S_AXIM_RDSTAT_oscntr_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_RLATENCY_UNION
 �ṹ˵��  : AXIM_RLATENCY �Ĵ����ṹ���塣��ַƫ����:0x00BD0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Accumulated read latency��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rlatency : 32; /* bit[0-31]: accumulated rd latency , correlated with RBURST */
    } reg;
} SOC_SECENG_S_AXIM_RLATENCY_UNION;
#endif
#define SOC_SECENG_S_AXIM_RLATENCY_rlatency_START  (0)
#define SOC_SECENG_S_AXIM_RLATENCY_rlatency_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_RBURST_UNION
 �ṹ˵��  : AXIM_RBURST �Ĵ����ṹ���塣��ַƫ����:0x00BD4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Accumulated read bursts��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rburst : 32; /* bit[0-31]: accumulated read bursts */
    } reg;
} SOC_SECENG_S_AXIM_RBURST_UNION;
#endif
#define SOC_SECENG_S_AXIM_RBURST_rburst_START  (0)
#define SOC_SECENG_S_AXIM_RBURST_rburst_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_WLATENCY_UNION
 �ṹ˵��  : AXIM_WLATENCY �Ĵ����ṹ���塣��ַƫ����:0x00BD8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Accumulated write latency��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wlatency : 32; /* bit[0-31]: accumulated wr latency , correlated with WBURST */
    } reg;
} SOC_SECENG_S_AXIM_WLATENCY_UNION;
#endif
#define SOC_SECENG_S_AXIM_WLATENCY_wlatency_START  (0)
#define SOC_SECENG_S_AXIM_WLATENCY_wlatency_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_WBURST_UNION
 �ṹ˵��  : AXIM_WBURST �Ĵ����ṹ���塣��ַƫ����:0x00BDC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Accumulated write bursts��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wburst : 32; /* bit[0-31]: accumulated wr bursts */
    } reg;
} SOC_SECENG_S_AXIM_WBURST_UNION;
#endif
#define SOC_SECENG_S_AXIM_WBURST_wburst_START  (0)
#define SOC_SECENG_S_AXIM_WBURST_wburst_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_CACHETYPE_CFG_UNION
 �ṹ˵��  : AXIM_CACHETYPE_CFG �Ĵ����ṹ���塣��ַƫ����:0x00BE0����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXI master cache-type configuration��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0 : 4;  /* bit[0-3]  : ���� */
        unsigned int  reserved_1 : 4;  /* bit[4-7]  : ���� */
        unsigned int  dd_arcache : 4;  /* bit[8-11] : Control the ARCACHE value of the direct data. */
        unsigned int  reserved_2 : 4;  /* bit[12-15]: ���� */
        unsigned int  reserved_3 : 4;  /* bit[16-19]: ���� */
        unsigned int  reserved_4 : 4;  /* bit[20-23]: ���� */
        unsigned int  dd_awcache : 4;  /* bit[24-27]: Control the AWCACHE value of the direct data. */
        unsigned int  reserved_5 : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_CACHETYPE_CFG_UNION;
#endif
#define SOC_SECENG_S_AXIM_CACHETYPE_CFG_dd_arcache_START  (8)
#define SOC_SECENG_S_AXIM_CACHETYPE_CFG_dd_arcache_END    (11)
#define SOC_SECENG_S_AXIM_CACHETYPE_CFG_dd_awcache_START  (24)
#define SOC_SECENG_S_AXIM_CACHETYPE_CFG_dd_awcache_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_PROT_CFG_UNION
 �ṹ˵��  : AXIM_PROT_CFG �Ĵ����ṹ���塣��ַƫ����:0x00BE4����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXIM Protection field configuration��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 2;  /* bit[0-1]  : ���� */
        unsigned int  reserved_1: 2;  /* bit[2-3]  : ���� */
        unsigned int  dd_arprot : 1;  /* bit[4]    : Control the ARPROT value of the direct data. */
        unsigned int  reserved_2: 3;  /* bit[5-7]  : ���� */
        unsigned int  reserved_3: 2;  /* bit[8-9]  : ���� */
        unsigned int  reserved_4: 2;  /* bit[10-11]: ���� */
        unsigned int  dd_awprot : 1;  /* bit[12]   : Control the AWPROT value of the direct data. */
        unsigned int  reserved_5: 3;  /* bit[13-15]: ���� */
        unsigned int  reserved_6: 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_PROT_CFG_UNION;
#endif
#define SOC_SECENG_S_AXIM_PROT_CFG_dd_arprot_START  (4)
#define SOC_SECENG_S_AXIM_PROT_CFG_dd_arprot_END    (4)
#define SOC_SECENG_S_AXIM_PROT_CFG_dd_awprot_START  (12)
#define SOC_SECENG_S_AXIM_PROT_CFG_dd_awprot_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_CFG1_UNION
 �ṹ˵��  : AXIM_CFG1 �Ĵ����ṹ���塣��ַƫ����:0x00BE8����ֵ:0x001F0087�����:32
 �Ĵ���˵��: AXI master configuration��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_after_wr_stall : 4;  /* bit[0-3]  : Enable/disable read after write stall for each of the clients:
                                                             �� 1 - enable
                                                             �� 0 - disable */
        unsigned int  brespmask         : 1;  /* bit[4]    : masking interrupt sources : bresp_err */
        unsigned int  rrespmask         : 1;  /* bit[5]    : masking interrupt sources : rresp_err */
        unsigned int  infltmask         : 1;  /* bit[6]    : masking interrupt sources : inflight_err */
        unsigned int  compmask          : 1;  /* bit[7]    : masking interrupt sources : completion counter incremented - if both compmask and interrupt sources are unmasked , completion event will have the highest priority */
        unsigned int  reserved_0        : 8;  /* bit[8-15] : ���� */
        unsigned int  accum_limit       : 5;  /* bit[16-20]: limit numenr of outstanding write transaction , axim will stop issue new requests after crossing this value */
        unsigned int  reserved_1        : 11; /* bit[21-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_CFG1_UNION;
#endif
#define SOC_SECENG_S_AXIM_CFG1_rd_after_wr_stall_START  (0)
#define SOC_SECENG_S_AXIM_CFG1_rd_after_wr_stall_END    (3)
#define SOC_SECENG_S_AXIM_CFG1_brespmask_START          (4)
#define SOC_SECENG_S_AXIM_CFG1_brespmask_END            (4)
#define SOC_SECENG_S_AXIM_CFG1_rrespmask_START          (5)
#define SOC_SECENG_S_AXIM_CFG1_rrespmask_END            (5)
#define SOC_SECENG_S_AXIM_CFG1_infltmask_START          (6)
#define SOC_SECENG_S_AXIM_CFG1_infltmask_END            (6)
#define SOC_SECENG_S_AXIM_CFG1_compmask_START           (7)
#define SOC_SECENG_S_AXIM_CFG1_compmask_END             (7)
#define SOC_SECENG_S_AXIM_CFG1_accum_limit_START        (16)
#define SOC_SECENG_S_AXIM_CFG1_accum_limit_END          (20)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_ACE_CONST_UNION
 �ṹ˵��  : AXIM_ACE_CONST �Ĵ����ṹ���塣��ַƫ����:0x00BEC����ֵ:0x11FC100A�����:32
 �Ĵ���˵��: AXIM ACE CONST��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ardomain            : 2;  /* bit[0-1]  : ACE ARDOMAIN constant value. */
        unsigned int  awdomain            : 2;  /* bit[2-3]  : ACE AWDOMAIN constant value. */
        unsigned int  arbar               : 2;  /* bit[4-5]  : ACE ARBAR constant value. */
        unsigned int  awbar               : 2;  /* bit[6-7]  : ACE AWBAR constant value. */
        unsigned int  arsnoop             : 4;  /* bit[8-11] : ACE ARSNOOP constant value. */
        unsigned int  awsnoop_not_aligned : 3;  /* bit[12-14]: ACE AWSNOOP constant value when unaligned transaction is used. */
        unsigned int  awsnoop_aligned     : 3;  /* bit[15-17]: ACE AWSNOOP constant value when aligned transaction is used. */
        unsigned int  awaddr_not_masked   : 7;  /* bit[18-24]: AWADDRESS not mask value */
        unsigned int  awlen_val           : 4;  /* bit[25-28]: AWLEN value */
        unsigned int  reserved            : 3;  /* bit[29-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_ACE_CONST_UNION;
#endif
#define SOC_SECENG_S_AXIM_ACE_CONST_ardomain_START             (0)
#define SOC_SECENG_S_AXIM_ACE_CONST_ardomain_END               (1)
#define SOC_SECENG_S_AXIM_ACE_CONST_awdomain_START             (2)
#define SOC_SECENG_S_AXIM_ACE_CONST_awdomain_END               (3)
#define SOC_SECENG_S_AXIM_ACE_CONST_arbar_START                (4)
#define SOC_SECENG_S_AXIM_ACE_CONST_arbar_END                  (5)
#define SOC_SECENG_S_AXIM_ACE_CONST_awbar_START                (6)
#define SOC_SECENG_S_AXIM_ACE_CONST_awbar_END                  (7)
#define SOC_SECENG_S_AXIM_ACE_CONST_arsnoop_START              (8)
#define SOC_SECENG_S_AXIM_ACE_CONST_arsnoop_END                (11)
#define SOC_SECENG_S_AXIM_ACE_CONST_awsnoop_not_aligned_START  (12)
#define SOC_SECENG_S_AXIM_ACE_CONST_awsnoop_not_aligned_END    (14)
#define SOC_SECENG_S_AXIM_ACE_CONST_awsnoop_aligned_START      (15)
#define SOC_SECENG_S_AXIM_ACE_CONST_awsnoop_aligned_END        (17)
#define SOC_SECENG_S_AXIM_ACE_CONST_awaddr_not_masked_START    (18)
#define SOC_SECENG_S_AXIM_ACE_CONST_awaddr_not_masked_END      (24)
#define SOC_SECENG_S_AXIM_ACE_CONST_awlen_val_START            (25)
#define SOC_SECENG_S_AXIM_ACE_CONST_awlen_val_END              (28)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXIM_CACHE_PARAMS_UNION
 �ṹ˵��  : AXIM_CACHE_PARAMS �Ĵ����ṹ���塣��ַƫ����:0x00BF0����ֵ:0x00000777�����:32
 �Ĵ���˵��: AXI master configuration for DMA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awcache_last : 4;  /* bit[0-3]  : Configure the AWCACHE last transaction for DMA. */
        unsigned int  awcache      : 4;  /* bit[4-7]  : Configure the AWCACHE transaction for DMA. */
        unsigned int  arcache      : 4;  /* bit[8-11] : Configure the ARCACHE last transaction for DMA. */
        unsigned int  reserved     : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_SECENG_S_AXIM_CACHE_PARAMS_UNION;
#endif
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_awcache_last_START  (0)
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_awcache_last_END    (3)
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_awcache_START       (4)
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_awcache_END         (7)
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_arcache_START       (8)
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_arcache_END         (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_ADDR_AXIM_CTRL_UNION
 �ṹ˵��  : ADDR_AXIM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x00BF4����ֵ:0x00000002�����:32
 �Ĵ���˵��: Control AXI master��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_axim_ctrl : 4;  /* bit[0-3] : Limit outstanding number of read transactions. */
        unsigned int  reserved       : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_SECENG_S_ADDR_AXIM_CTRL_UNION;
#endif
#define SOC_SECENG_S_ADDR_AXIM_CTRL_addr_axim_ctrl_START  (0)
#define SOC_SECENG_S_ADDR_AXIM_CTRL_addr_axim_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DIN_BUFFER_UNION
 �ṹ˵��  : DIN_BUFFER �Ĵ����ṹ���塣��ַƫ����:0x00C00����ֵ:0x00000000�����:32
 �Ĵ���˵��: This address can be used by the CPU to write data directly to the DIN buffer to be sent to engines��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  din_buffer_data : 32; /* bit[0-31]: This register is mapped into 8 addresses in order to enable a CPU burst. */
    } reg;
} SOC_SECENG_S_DIN_BUFFER_UNION;
#endif
#define SOC_SECENG_S_DIN_BUFFER_din_buffer_data_START  (0)
#define SOC_SECENG_S_DIN_BUFFER_din_buffer_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DIN_MEM_DMA_BUSY_UNION
 �ṹ˵��  : DIN_MEM_DMA_BUSY �Ĵ����ṹ���塣��ַƫ����:0x00C20����ֵ:0x00000000�����:32
 �Ĵ���˵��: Indicates whether memory (AXI) source DMA (DIN) is busy��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  din_mem_dma_busy : 1;  /* bit[0]   : DIN memory DMA busy:
                                                           1'b1: busy.
                                                           1'b0: not busy. */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DIN_MEM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_S_DIN_MEM_DMA_BUSY_din_mem_dma_busy_START  (0)
#define SOC_SECENG_S_DIN_MEM_DMA_BUSY_din_mem_dma_busy_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_SRC_LLI_SRAM_ADDR_UNION
 �ṹ˵��  : SRC_LLI_SRAM_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00C24����ֵ:0x00000000�����:32
 �Ĵ���˵��: Location of LLI table located in the SRAM�� in SINGLE/MULTI_LLI mode, writing to this register triggers the DMA�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_lli_sram_addr : 15; /* bit[0-14] : Source LLI table address in SRAM. */
        unsigned int  reserved          : 17; /* bit[15-31]: ���� */
    } reg;
} SOC_SECENG_S_SRC_LLI_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_S_SRC_LLI_SRAM_ADDR_src_lli_sram_addr_START  (0)
#define SOC_SECENG_S_SRC_LLI_SRAM_ADDR_src_lli_sram_addr_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_SRC_LLI_WORD0_UNION
 �ṹ˵��  : SRC_LLI_WORD0 �Ĵ����ṹ���塣��ַƫ����:0x00C28����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used in direct LLI mode - holds the location of the data source in the memory (AXI)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_lli_word0 : 32; /* bit[0-31]: Source address within memory. */
    } reg;
} SOC_SECENG_S_SRC_LLI_WORD0_UNION;
#endif
#define SOC_SECENG_S_SRC_LLI_WORD0_src_lli_word0_START  (0)
#define SOC_SECENG_S_SRC_LLI_WORD0_src_lli_word0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_SRC_LLI_WORD1_UNION
 �ṹ˵��  : SRC_LLI_WORD1 �Ĵ����ṹ���塣��ַƫ����:0x00C2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used in direct LLI mode - holds the number of bytes to be read from the memory (AXI)�� Writing to this register triggers the DMA�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bytes_num : 30; /* bit[0-29]: Total number of bytes to read using DMA in this entry */
        unsigned int  first     : 1;  /* bit[30]  : 1- Indicate the first LLI entry */
        unsigned int  last      : 1;  /* bit[31]  : 1- Indicate the last LLI entry */
    } reg;
} SOC_SECENG_S_SRC_LLI_WORD1_UNION;
#endif
#define SOC_SECENG_S_SRC_LLI_WORD1_bytes_num_START  (0)
#define SOC_SECENG_S_SRC_LLI_WORD1_bytes_num_END    (29)
#define SOC_SECENG_S_SRC_LLI_WORD1_first_START      (30)
#define SOC_SECENG_S_SRC_LLI_WORD1_first_END        (30)
#define SOC_SECENG_S_SRC_LLI_WORD1_last_START       (31)
#define SOC_SECENG_S_SRC_LLI_WORD1_last_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_SRAM_SRC_ADDR_UNION
 �ṹ˵��  : SRAM_SRC_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00C30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Location of data (start address) to be read from SRAM�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_source : 32; /* bit[0-31]: SRAM source base address of data */
    } reg;
} SOC_SECENG_S_SRAM_SRC_ADDR_UNION;
#endif
#define SOC_SECENG_S_SRAM_SRC_ADDR_sram_source_START  (0)
#define SOC_SECENG_S_SRAM_SRC_ADDR_sram_source_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DIN_SRAM_BYTES_LEN_UNION
 �ṹ˵��  : DIN_SRAM_BYTES_LEN �Ĵ����ṹ���塣��ַƫ����:0x00C34����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the size of the data (in bytes) to be read from the SRAM�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bytes_len : 32; /* bit[0-31]: Size of data to read from SRAM (bytes). This is the trigger to the SRAM SRC DMA */
    } reg;
} SOC_SECENG_S_DIN_SRAM_BYTES_LEN_UNION;
#endif
#define SOC_SECENG_S_DIN_SRAM_BYTES_LEN_bytes_len_START  (0)
#define SOC_SECENG_S_DIN_SRAM_BYTES_LEN_bytes_len_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DIN_SRAM_DMA_BUSY_UNION
 �ṹ˵��  : DIN_SRAM_DMA_BUSY �Ĵ����ṹ���塣��ַƫ����:0x00C38����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the status of the SRAM DMA DIN��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  busy     : 1;  /* bit[0]   : DIN SRAM DMA busy:
                                                   1'b1: busy.
                                                   1'b0: not busy.  */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DIN_SRAM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_S_DIN_SRAM_DMA_BUSY_busy_START      (0)
#define SOC_SECENG_S_DIN_SRAM_DMA_BUSY_busy_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DIN_SRAM_ENDIANNESS_UNION
 �ṹ˵��  : DIN_SRAM_ENDIANNESS �Ĵ����ṹ���塣��ַƫ����:0x00C3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines the endianness of the DIN interface to SRAM��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_din_endianness : 1;  /* bit[0]   : Defines the endianness of DIN interface to SRAM:
                                                              �� 1'b1 - big-endianness
                                                              �� 1'b0 - little endianness */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DIN_SRAM_ENDIANNESS_UNION;
#endif
#define SOC_SECENG_S_DIN_SRAM_ENDIANNESS_sram_din_endianness_START  (0)
#define SOC_SECENG_S_DIN_SRAM_ENDIANNESS_sram_din_endianness_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXI_CPU_DIN_PARAMS_UNION
 �ṹ˵��  : AXI_CPU_DIN_PARAMS �Ĵ����ṹ���塣��ַƫ����:0x00C40����ֵ:0x00000028�����:32
 �Ĵ���˵��: This register holds RDID and PROT when using the CPU��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdid     : 4;  /* bit[0-3]  : AXI transaction ID when using the CPU (compatibility mode). */
        unsigned int  reserved_0: 4;  /* bit[4-7]  : ���� */
        unsigned int  prot     : 2;  /* bit[8-9]  : AXI transaction PROT when using the CPU (compatibility mode). */
        unsigned int  reserved_1: 22; /* bit[10-31]: ���� */
    } reg;
} SOC_SECENG_S_AXI_CPU_DIN_PARAMS_UNION;
#endif
#define SOC_SECENG_S_AXI_CPU_DIN_PARAMS_rdid_START      (0)
#define SOC_SECENG_S_AXI_CPU_DIN_PARAMS_rdid_END        (3)
#define SOC_SECENG_S_AXI_CPU_DIN_PARAMS_prot_START      (8)
#define SOC_SECENG_S_AXI_CPU_DIN_PARAMS_prot_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DIN_SW_RESET_UNION
 �ṹ˵��  : DIN_SW_RESET �Ĵ����ṹ���塣��ַƫ����:0x00C44����ֵ:0x00000000�����:32
 �Ĵ���˵��: DIN software reset��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  kick_sw_reset : 1;  /* bit[0]   : RESET the DIN */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DIN_SW_RESET_UNION;
#endif
#define SOC_SECENG_S_DIN_SW_RESET_kick_sw_reset_START  (0)
#define SOC_SECENG_S_DIN_SW_RESET_kick_sw_reset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DIN_CPU_DATA_SIZE_UNION
 �ṹ˵��  : DIN_CPU_DATA_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0C48����ֵ:0x00000000�����:32
 �Ĵ���˵��: Data path to DIN is OTF��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_din_size : 16; /* bit[0-15] : When using CPU direct write to the DIN buffer, the size of input data in bytes should be written to this register�� */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_DIN_CPU_DATA_SIZE_UNION;
#endif
#define SOC_SECENG_S_DIN_CPU_DATA_SIZE_cpu_din_size_START  (0)
#define SOC_SECENG_S_DIN_CPU_DATA_SIZE_cpu_din_size_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_WRITE_ALIGN_LAST_UNION
 �ṹ˵��  : WRITE_ALIGN_LAST �Ĵ����ṹ���塣��ַƫ����:0x00C4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Indication that the next write from the CPU is the last one�� This is needed only when the data size is NOT modulo 4 (e.g. HASH padding)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  last     : 1;  /* bit[0]   : 1 - next data from CPU is the last word�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_WRITE_ALIGN_LAST_UNION;
#endif
#define SOC_SECENG_S_WRITE_ALIGN_LAST_last_START      (0)
#define SOC_SECENG_S_WRITE_ALIGN_LAST_last_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_FIFO_IN_EMPTY_UNION
 �ṹ˵��  : FIFO_IN_EMPTY �Ĵ����ṹ���塣��ַƫ����:0x00C50����ֵ:0x00000001�����:32
 �Ĵ���˵��: DIN FIFO empty indication��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  empty    : 1;  /* bit[0]   : 1 - fifo empty */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_FIFO_IN_EMPTY_UNION;
#endif
#define SOC_SECENG_S_FIFO_IN_EMPTY_empty_START     (0)
#define SOC_SECENG_S_FIFO_IN_EMPTY_empty_END       (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DISABLE_OUTSTD_REQ_UNION
 �ṹ˵��  : DISABLE_OUTSTD_REQ �Ĵ����ṹ���塣��ַƫ����:0x00C54����ֵ:0x00000000�����:32
 �Ĵ���˵��: Disables the outstanding DIN request��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  disable_outstd_req : 1;  /* bit[0]   : Disables the outstanding request:
                                                             �� 1'b0 - enable
                                                             �� 1'b1 - disable */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DISABLE_OUTSTD_REQ_UNION;
#endif
#define SOC_SECENG_S_DISABLE_OUTSTD_REQ_disable_outstd_req_START  (0)
#define SOC_SECENG_S_DISABLE_OUTSTD_REQ_disable_outstd_req_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DIN_FIFO_RST_PNTR_UNION
 �ṹ˵��  : DIN_FIFO_RST_PNTR �Ĵ����ṹ���塣��ַƫ����:0x00C58����ֵ:0x00000000�����:32
 �Ĵ���˵��: Writing to this register resets the DIN_FIFO pointers��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst      : 1;  /* bit[0]   : Writing any value to this address resets the DIN_FIFO pointers�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DIN_FIFO_RST_PNTR_UNION;
#endif
#define SOC_SECENG_S_DIN_FIFO_RST_PNTR_rst_START       (0)
#define SOC_SECENG_S_DIN_FIFO_RST_PNTR_rst_END         (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DOUT_BUFFER_UNION
 �ṹ˵��  : DOUT_BUFFER �Ĵ����ṹ���塣��ַƫ����:0x00D00����ֵ:0x00000000�����:32
 �Ĵ���˵��: Cryptographic result - CPU can directly access it�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_buffer_data : 32; /* bit[0-31]: This address can be used by the CPU to read data directly from the DOUT buffer�� */
    } reg;
} SOC_SECENG_S_DOUT_BUFFER_UNION;
#endif
#define SOC_SECENG_S_DOUT_BUFFER_dout_buffer_data_START  (0)
#define SOC_SECENG_S_DOUT_BUFFER_dout_buffer_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DOUT_MEM_DMA_BUSY_UNION
 �ṹ˵��  : DOUT_MEM_DMA_BUSY �Ĵ����ṹ���塣��ַƫ����:0x00D20����ֵ:0x00000000�����:32
 �Ĵ���˵��: DOUT memory DMA busy - Indicates that memory (AXI) destination DMA (DOUT) is busy��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_mem_dma_busy : 1;  /* bit[0]   : DOUT memory DMA busy:
                                                            1'b1: busy.
                                                            1'b0: not busy.  */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DOUT_MEM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_S_DOUT_MEM_DMA_BUSY_dout_mem_dma_busy_START  (0)
#define SOC_SECENG_S_DOUT_MEM_DMA_BUSY_dout_mem_dma_busy_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DST_LLI_SRAM_ADDR_UNION
 �ṹ˵��  : DST_LLI_SRAM_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00D24����ֵ:0x0000001E�����:32
 �Ĵ���˵��: This register holds the destination LLI table address in SRAM�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst_lli_sram_addr : 15; /* bit[0-14] : The destination LLI table address in SRAM */
        unsigned int  reserved          : 17; /* bit[15-31]: ���� */
    } reg;
} SOC_SECENG_S_DST_LLI_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_S_DST_LLI_SRAM_ADDR_dst_lli_sram_addr_START  (0)
#define SOC_SECENG_S_DST_LLI_SRAM_ADDR_dst_lli_sram_addr_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DST_LLI_WORD0_UNION
 �ṹ˵��  : DST_LLI_WORD0 �Ĵ����ṹ���塣��ַƫ����:0x00D28����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used in direct LLI mode - holds the location of the data destination in the memory (AXI)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst_lli_word0 : 32; /* bit[0-31]: Destination address within memory */
    } reg;
} SOC_SECENG_S_DST_LLI_WORD0_UNION;
#endif
#define SOC_SECENG_S_DST_LLI_WORD0_dst_lli_word0_START  (0)
#define SOC_SECENG_S_DST_LLI_WORD0_dst_lli_word0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DST_LLI_WORD1_UNION
 �ṹ˵��  : DST_LLI_WORD1 �Ĵ����ṹ���塣��ַƫ����:0x00D2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used in direct LLI mode - holds the number of bytes to be written to the memory (AXI)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bytes_num : 30; /* bit[0-29]: Total byte number to be written by DMA in this entry */
        unsigned int  first     : 1;  /* bit[30]  : 1- Indicate the first LLI entry */
        unsigned int  last      : 1;  /* bit[31]  : 1- Indicate the last LLI entry */
    } reg;
} SOC_SECENG_S_DST_LLI_WORD1_UNION;
#endif
#define SOC_SECENG_S_DST_LLI_WORD1_bytes_num_START  (0)
#define SOC_SECENG_S_DST_LLI_WORD1_bytes_num_END    (29)
#define SOC_SECENG_S_DST_LLI_WORD1_first_START      (30)
#define SOC_SECENG_S_DST_LLI_WORD1_first_END        (30)
#define SOC_SECENG_S_DST_LLI_WORD1_last_START       (31)
#define SOC_SECENG_S_DST_LLI_WORD1_last_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_SRAM_DEST_ADDR_UNION
 �ṹ˵��  : SRAM_DEST_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00D30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Location of result to be sent to in SRAM NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_dest : 32; /* bit[0-31]: SRAM destination base address for data */
    } reg;
} SOC_SECENG_S_SRAM_DEST_ADDR_UNION;
#endif
#define SOC_SECENG_S_SRAM_DEST_ADDR_sram_dest_START  (0)
#define SOC_SECENG_S_SRAM_DEST_ADDR_sram_dest_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DOUT_SRAM_BYTES_LEN_UNION
 �ṹ˵��  : DOUT_SRAM_BYTES_LEN �Ĵ����ṹ���塣��ַƫ����:0x00D34����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the size of the data (in bytes) to be written to the SRAM�� NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bytes_len : 32; /* bit[0-31]: Size of data to write to SRAM (bytes). This is the trigger to the SRAM DST DMA */
    } reg;
} SOC_SECENG_S_DOUT_SRAM_BYTES_LEN_UNION;
#endif
#define SOC_SECENG_S_DOUT_SRAM_BYTES_LEN_bytes_len_START  (0)
#define SOC_SECENG_S_DOUT_SRAM_BYTES_LEN_bytes_len_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DOUT_SRAM_DMA_BUSY_UNION
 �ṹ˵��  : DOUT_SRAM_DMA_BUSY �Ĵ����ṹ���塣��ַƫ����:0x00D38����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the status of the SRAM DMA DOUT��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  busy     : 1;  /* bit[0]   : 0 - all data was written to SRAM
                                                   1 - DOUT SRAM DMA busy */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DOUT_SRAM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_S_DOUT_SRAM_DMA_BUSY_busy_START      (0)
#define SOC_SECENG_S_DOUT_SRAM_DMA_BUSY_busy_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DOUT_SRAM_ENDIANNESS_UNION
 �ṹ˵��  : DOUT_SRAM_ENDIANNESS �Ĵ����ṹ���塣��ַƫ����:0x00D3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines the endianness of the DOUT interface from SRAM��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_sram_endianness : 1;  /* bit[0]   : Defines the endianness of DOUT interface from SRAM:
                                                               �� 1'b1 - big-endianness
                                                               �� 1'b0 - little endianness */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DOUT_SRAM_ENDIANNESS_UNION;
#endif
#define SOC_SECENG_S_DOUT_SRAM_ENDIANNESS_dout_sram_endianness_START  (0)
#define SOC_SECENG_S_DOUT_SRAM_ENDIANNESS_dout_sram_endianness_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_READ_ALIGN_LAST_UNION
 �ṹ˵��  : READ_ALIGN_LAST �Ĵ����ṹ���塣��ַƫ����:0x00D44����ֵ:0x00000000�����:32
 �Ĵ���˵��: Indication that the next read from the CPU is the last one�� This is needed only when the data size is NOT modulo 4 (e.g. HASH padding)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  last     : 1;  /* bit[0]   : 1 - Flush the read aligner content (used for reading the last data). */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_READ_ALIGN_LAST_UNION;
#endif
#define SOC_SECENG_S_READ_ALIGN_LAST_last_START      (0)
#define SOC_SECENG_S_READ_ALIGN_LAST_last_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DOUT_FIFO_EMPTY_UNION
 �ṹ˵��  : DOUT_FIFO_EMPTY �Ĵ����ṹ���塣��ַƫ����:0x00D50����ֵ:0x00000000�����:32
 �Ĵ���˵��: DOUT_FIFO_EMPTY Register��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_fifo_empty : 1;  /* bit[0]   : 1'b0 - DOUT fifo isn't empty
                                                          1'b1 - DOUT fifo is empty */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DOUT_FIFO_EMPTY_UNION;
#endif
#define SOC_SECENG_S_DOUT_FIFO_EMPTY_dout_fifo_empty_START  (0)
#define SOC_SECENG_S_DOUT_FIFO_EMPTY_dout_fifo_empty_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_UNION
 �ṹ˵��  : AXI_CPU_DOUT_PARAMS �Ĵ����ṹ���塣��ַƫ����:0x00D54����ֵ:0x00008000�����:32
 �Ĵ���˵��: AXI_CPU_DOUT_PARAMS Register��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cache_type       : 4;  /* bit[0-3]  : Cache type of AXI transaction when using CPU */
        unsigned int  reserved_0       : 4;  /* bit[4-7]  : ���� */
        unsigned int  reserved_1       : 4;  /* bit[8-11] : ���� */
        unsigned int  wrid             : 4;  /* bit[12-15]: AXI transaction ID when using CPU. */
        unsigned int  prot             : 2;  /* bit[16-17]: AXI transaction PROT when using CPU. */
        unsigned int  force_cpu_params : 1;  /* bit[18]   : The cpu params is also forced to descriptor output transactions. */
        unsigned int  reserved_2       : 13; /* bit[19-31]: ���� */
    } reg;
} SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_UNION;
#endif
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_cache_type_START        (0)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_cache_type_END          (3)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_wrid_START              (12)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_wrid_END                (15)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_prot_START              (16)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_prot_END                (17)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_force_cpu_params_START  (18)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_force_cpu_params_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DOUT_SW_RESET_UNION
 �ṹ˵��  : DOUT_SW_RESET �Ĵ����ṹ���塣��ַƫ����:0x00D58����ֵ:0x00000000�����:32
 �Ĵ���˵��: Software reset for DOUT��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_sw_reset : 1;  /* bit[0]   : reset the DOUT */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DOUT_SW_RESET_UNION;
#endif
#define SOC_SECENG_S_DOUT_SW_RESET_dout_sw_reset_START  (0)
#define SOC_SECENG_S_DOUT_SW_RESET_dout_sw_reset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_UNION
 �ṹ˵��  : DSCRPTR_COMPLETION_COUNTER0 �Ĵ����ṹ���塣��ַƫ����:0x00E00����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register counts the number of completed descriptors in which the ACK_NEEDED field equals 1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  completion_counter : 6;  /* bit[0-5] : This counter counts completion of descriptors in which the ack_needed field equals 1 */
        unsigned int  overflow_counter   : 1;  /* bit[6]   : if bit is set completion counter 0 was overflowed */
        unsigned int  reserved           : 25; /* bit[7-31]: ���� */
    } reg;
} SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_completion_counter_START  (0)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_completion_counter_END    (5)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_overflow_counter_START    (6)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_overflow_counter_END      (6)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_UNION
 �ṹ˵��  : DSCRPTR_COMPLETION_COUNTER1 �Ĵ����ṹ���塣��ַƫ����:0x00E04����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register counts the number of completed descriptors in which the ACK_NEEDED field equals 2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  completion_counter : 6;  /* bit[0-5] : This counter counts completion of descriptors in which the ack_needed field equals 2 */
        unsigned int  overflow_counter   : 1;  /* bit[6]   : if bit is set completion counter 1 was overflowed */
        unsigned int  reserved           : 25; /* bit[7-31]: ���� */
    } reg;
} SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_completion_counter_START  (0)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_completion_counter_END    (5)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_overflow_counter_START    (6)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_overflow_counter_END      (6)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_COMPLETION_STATUS_UNION
 �ṹ˵��  : DSCRPTR_COMPLETION_STATUS �Ĵ����ṹ���塣��ַƫ����:0x00E3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the status of the completion counters��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  completion_counter_status : 2;  /* bit[0-1] : Each bit in this register indicates, for the corresponding completion counter, whether it was incremented since the last time it was read (a read from a counter resets the relevant bit). */
        unsigned int  reserved                  : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_SECENG_S_DSCRPTR_COMPLETION_STATUS_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_COMPLETION_STATUS_completion_counter_status_START  (0)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_STATUS_completion_counter_status_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_SW_RESET_UNION
 �ṹ˵��  : DSCRPTR_SW_RESET �Ĵ����ṹ���塣��ַƫ����:0x00E40����ֵ:0x00000000�����:32
 �Ĵ���˵��: Software reset for descriptors��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dscrptr_sw_reset : 1;  /* bit[0]   : Descriptor reset. */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DSCRPTR_SW_RESET_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_SW_RESET_dscrptr_sw_reset_START  (0)
#define SOC_SECENG_S_DSCRPTR_SW_RESET_dscrptr_sw_reset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_DEBUG_MODE_UNION
 �ṹ˵��  : DSCRPTR_DEBUG_MODE �Ĵ����ṹ���塣��ַƫ����:0x00E4C����ֵ:0x00000001�����:32
 �Ĵ���˵��: This register enables the use of special descriptors��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dscrptr_debug_mode : 1;  /* bit[0]   : Enables using the special descriptors (the descriptor that performs a general Host write, and the descriptors that disable context switching). */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DSCRPTR_DEBUG_MODE_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_DEBUG_MODE_dscrptr_debug_mode_START  (0)
#define SOC_SECENG_S_DSCRPTR_DEBUG_MODE_dscrptr_debug_mode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_SINGLE_ADDR_EN_UNION
 �ṹ˵��  : DSCRPTR_SINGLE_ADDR_EN �Ĵ����ṹ���塣��ַƫ����:0x0E64����ֵ:0x00000001�����:32
 �Ĵ���˵��: This register enables the Host to write a descriptor using a single address��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dscrptr_single_addr : 1;  /* bit[0]   : This bit allows the Host to access a single address when writing descriptors. */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_DSCRPTR_SINGLE_ADDR_EN_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_SINGLE_ADDR_EN_dscrptr_single_addr_START  (0)
#define SOC_SECENG_S_DSCRPTR_SINGLE_ADDR_EN_dscrptr_single_addr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_MEASURE_CNTR_UNION
 �ṹ˵��  : DSCRPTR_MEASURE_CNTR �Ĵ����ṹ���塣��ַƫ����:0x0E68����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of cycles measured when using the special performance descriptor��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  measure_cntr : 32; /* bit[0-31]: Counter for descriptors performance measurement, start and finish with a special descriptor. Reading this register clears it. */
    } reg;
} SOC_SECENG_S_DSCRPTR_MEASURE_CNTR_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_MEASURE_CNTR_measure_cntr_START  (0)
#define SOC_SECENG_S_DSCRPTR_MEASURE_CNTR_measure_cntr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_UNION
 �ṹ˵��  : DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH �Ĵ����ṹ���塣��ַƫ����:0x0E6C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the upper 16bits of the address to which CryptoCell writes when descriptor does not comply with restriction��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dropped_address_high : 16; /* bit[0-15] : The high 16bits address to which CryptoCell writes when descriptor is dropped. */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SECENG_S_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_dropped_address_high_START  (0)
#define SOC_SECENG_S_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_dropped_address_high_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_QUEUE0_WORD0_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WORD0 �Ĵ����ṹ���塣��ַƫ����:0x00E80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word0 of the descriptor��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  din_dma_address : 32; /* bit[0-31]: When in DIN DMA mode: */
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WORD0_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD0_din_dma_address_START  (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD0_din_dma_address_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WORD1 �Ĵ����ṹ���塣��ַƫ����:0x00E84����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word1 of the descriptor��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  din_dma_mode     : 2;  /* bit[0-1]  : DIN DMA mode:
                                                            0x0: NO DMA.
                                                            0x1: SRAM.
                                                            0x2: Direct LLI.
                                                            0x3: MLLI.  */
        unsigned int  din_size         : 24; /* bit[2-25] : When in DIN DMA mode:
                                                            �� SRAM - The size of the data. Must to be multiple of 4bytes.
                                                            �� Direct LLI - The size of the data.
                                                            �� MLLI - This field is not used.  */
        unsigned int  ns_bit           : 1;  /* bit[26]   : NS bit when using AXI flow or endianness when using SRAM flow. 1.NS bit for current transaction. When SRAM flow is selected , this bit indicates that the SRAM endianness is active. */
        unsigned int  din_const_value  : 1;  /* bit[27]   : This bit forces DIN data to be a constant value taken from the address field. When this bit is set, the DIN_DMA_MODE must be set to SRAM. */
        unsigned int  not_last         : 1;  /* bit[28]   : Not last descriptor - when this field is set, it signals that the last LLI of the current descriptor is not the last block of the AES. */
        unsigned int  lock_queue       : 1;  /* bit[29]   : Lock active queue. Disables context switching between the queues (works only when debug_mode is set). */
        unsigned int  din_virtual_host : 2;  /* bit[30-31]: Defines the host ID for the current transaction (DIN). */
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_dma_mode_START      (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_dma_mode_END        (1)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_size_START          (2)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_size_END            (25)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_ns_bit_START            (26)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_ns_bit_END              (26)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_const_value_START   (27)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_const_value_END     (27)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_not_last_START          (28)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_not_last_END            (28)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_lock_queue_START        (29)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_lock_queue_END          (29)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_virtual_host_START  (30)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_virtual_host_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_QUEUE0_WORD2_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WORD2 �Ĵ����ṹ���塣��ַƫ����:0x00E88����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word2 of the descriptor��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_dma_address : 32; /* bit[0-31]: When in DOUT DMA mode:
                                                           �� SRAM: The address of the destination DMA data in the SRAM.
                                                           �� Direct LLI: The address of the destination DMA data in the system RAM (through the AXI master).
                                                           �� MLLI: The address of the destination LLI list in the SRAM. */
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WORD2_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD2_dout_dma_address_START  (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD2_dout_dma_address_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WORD3 �Ĵ����ṹ���塣��ַƫ����:0x00E8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word3 of the descriptor��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_dma_mode     : 2;  /* bit[0-1]  : DOUT DMA mode:
                                                             �� 2'h0 - NO DMA
                                                             �� 2'h1 - SRAM
                                                             �� 2'h2 - Direct LLI
                                                             �� 2'h3 - MLLI */
        unsigned int  dout_size         : 24; /* bit[2-25] : When in DOUT DMA mode:
                                                             �� SRAM - The size of the data. Must to be multiple of 4bytes.
                                                             �� Direct LLI - The size of the data.
                                                             �� MLLI - This field is not used. */
        unsigned int  ns_bit            : 1;  /* bit[26]   : NS bit for current transaction */
        unsigned int  dout_last_ind     : 1;  /* bit[27]   : Indicates last transaction. This AWCACHE value of the last AXI transaction is uncached and unbufferred. */
        unsigned int  reserved          : 1;  /* bit[28]   : ���� */
        unsigned int  hash_xor_bit      : 1;  /* bit[29]   : When this bit is set - the DIN data to HASH is xored with xor-register. */
        unsigned int  dout_virtual_host : 2;  /* bit[30-31]: Defines the ID of the Host for the current transaction (DOUT) */
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_dma_mode_START      (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_dma_mode_END        (1)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_size_START          (2)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_size_END            (25)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_ns_bit_START             (26)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_ns_bit_END               (26)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_last_ind_START      (27)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_last_ind_END        (27)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_hash_xor_bit_START       (29)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_hash_xor_bit_END         (29)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_virtual_host_START  (30)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_virtual_host_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WORD4 �Ĵ����ṹ���塣��ַƫ����:0x00E90����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word4 of the descripto��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data_flow_mode       : 6;  /* bit[0-5]  : Data-flow mode:
                                                                �� 6'd0 - BYPASS
                                                                �� 6'd1 - DIN-AES-DOUT
                                                                �� 6'd2 - AES-to-HASH
                                                                �� 6'd3 - AES-and-HASH
                                                                �� 6'd4 - DIN-DES-DOUT
                                                                �� 6'd5 - DES-to-HASH
                                                                �� 6'd6 - DES-and-HASH
                                                                �� 6'd7 - DIN-HASH
                                                                �� 6'd8 - DIN-HASH-and-BYPASS
                                                                �� 6'd9 - AES-MAC-and-BYPASS
                                                                �� 6'd10 - AES-to-HASH-and-DOUT
                                                                �� 6'd11 - Reserved
                                                                �� 6'd12 - DES-to-HASH-and-DOUT
                                                                �� 6'd13 - AES-to-AES-to-HASH-and DOUT
                                                                �� 6'd14 - AES-to-AES-to-HASH
                                                                �� 6'd15 - AES-to-HASH-and-AES
                                                                �� 6'd16 - Reserved
                                                                �� 6'd17 - DIN-AES-AESMAC
                                                                �� 6'd18 - HASH-to-DOUT
                                                                SETUP MODES:
                                                                �� 6'd32 - S_DIN-to AES
                                                                �� 6'd33 - S_DIN-to_AES2
                                                                �� 6d34 - S_DIN-to-DES
                                                                �� 6'd35 - Reserved
                                                                �� 6'd36 - Reserved
                                                                �� 6'd37 - S_Din-to-HASH
                                                                �� 6'd38 - S_AES-to-DOUT
                                                                �� 6'd39 - S_AES2-to-DOUT
                                                                �� 6'd40 - Reserved
                                                                �� 6'd41 - Reserved
                                                                �� 6'd42 - S_DES-to-DOUT
                                                                �� 6'd43 - S_HASH_to_DOUT
                                                                �� 6'd44 - SET-FLOW-ID  */
        unsigned int  reserved             : 1;  /* bit[6]    : ���� */
        unsigned int  aes_xor_crypto_key   : 1;  /* bit[7]    : when using AES, if this field is set, then the aes HW key is xored with the already loaded key. */
        unsigned int  ack_needed           : 2;  /* bit[8-9]  : �� 0x0 - no interrupt is triggered and no completion counter is incremented when the current descriptor is complete.
                                                                �� 0x1-0x2 - when the descriptor is complete, an interrupt is generated, and the relevant completion counter (according to the field value) is incremented. */
        unsigned int  cipher_mode          : 4;  /* bit[10-13]: Value AES DES/TDES HASH/AESMAC:
                                                                �� 0x0 ECB DES-ECB ECB MD5
                                                                �� 0x1 CBC DES-CBC CBC SHA1
                                                                �� 0x2 CTR TDES ECB N/A SHA256
                                                                �� 0x3 CBC-MAC TDES CBC SHA224
                                                                �� 0x4 XTS N/A SHA512
                                                                �� 0x5 XCBC MAC SHA384
                                                                �� 0x6 OFB
                                                                �� 0x7 CMAC
                                                                �� 0x8 CCM A
                                                                �� 0x9 CCM E
                                                                �� 0xA CCM P
                                                                �� 0xB CBC-CTS */
        unsigned int  cmac_size0           : 1;  /* bit[14]   : AES_CMAC_SIZE0 - kicks a CMAC operation with size zero. */
        unsigned int  cipher_do            : 2;  /* bit[15-16]: If the current flow is AES:
                                                                �� 2'd0 - AES INTERNAL KEY
                                                                �� 2'd1 - AES_SK - RKEK
                                                                �� 2'd2 - AES_SK - PROV_KEY
                                                                �� 2'd3 - Reserved
                                                                If the current flow is HASH:
                                                                �� 2'd1 - Do hash padding. */
        unsigned int  cipher_conf0         : 2;  /* bit[17-18]: If the current flow is AES:
                                                                �� 2'd0 - encrypt: aes mode is encrypt.
                                                                �� 2'd1 - decrypt: aes mode is decrypt.
                                                                �� 2'd1 - Reserved.
                                                                If the current flow is HASH:
                                                                �� 2'd1 - hash output compared - currently not supported.
                                                                �� 2'd2 - hash output is big-endianness (need for HMAC flow). */
        unsigned int  cipher_conf1         : 1;  /* bit[19]   : If the current flow is AES: Reserved.
                                                                If the current flow is HASH:
                                                                �� 1'b1 - Enable hash padding in the end of block.  */
        unsigned int  cipher_conf2         : 2;  /* bit[20-21]: If the current flow is AES: Reserved.
                                                                If the current flow is HASH:
                                                                �� 2'd0 - do not truncate output.
                                                                �� 2'd1 - truncate to 96bits.
                                                                �� 2'd2 - truncate to 128bits. */
        unsigned int  key_size             : 2;  /* bit[22-23]: If the Data flow mode is setup AES:
                                                                �� 2'h0 - AES KEY_SIZE = 128b
                                                                �� 2'h1 - AES KEY_SIZE = 192b
                                                                �� 2'h2 - AES KEY_SIZE = 256b
                                                                If the Data flow mode is setup DES:
                                                                �� 2'h0 - DES key number = 1 key
                                                                �� 2'h1 - DES key number = 2 keys
                                                                �� 2'h2 - DES key number = 3 keys  */
        unsigned int  setup_operation      : 4;  /* bit[24-27]: �� 4'd0 - NONE
                                                                �� 4'd1 - Load state0 from DIN. The functionality of bit depend on the current flow:
                                                                �� AES - load IV from DIN.
                                                                �� DES - load IV.
                                                                �� HASH - load H (digest).
                                                                �� 4'd2 - Load state1 from DIN.
                                                                �� AES - load CTR.
                                                                �� HASH - load data to compare - not supported.
                                                                �� 4'd3 - Load state2 from DIN .
                                                                �� AES - load prev_iv.
                                                                �� 4'd4 - Load key0 from DIN.
                                                                �� AES - load key.
                                                                �� DES - load key.
                                                                �� HASH - load Hash current length register for padding.
                                                                �� 4'd5 - Load AES xex key from DIN.
                                                                // Store States
                                                                �� 4'd8 - Write state0 to DOUT.
                                                                �� AES - store IV.
                                                                �� DES - store IV.
                                                                �� HASH - store H - save the digest.
                                                                �� 4'd9 - Write state1 to DOUT2.
                                                                �� AES - store CTR.
                                                                �� HASH - store current length.
                                                                �� 4'd10 - write state2 to DOUT .
                                                                �� AES - store prev_iv.
                                                                �� 4'd11 - write state3 to DOUT.
                                                                �� AES - store xex_key. */
        unsigned int  din_sram_endianness  : 1;  /* bit[28]   : When using DIN source as SRAM, this bit swaps the bytes order of the word read from the SRAM and decreases the address after each word. */
        unsigned int  dout_sram_endianness : 1;  /* bit[29]   : When using DOUT destination as SRAM, this bit swaps the bytes order of the word written to SRAM and decreases the address after each word. */
        unsigned int  word_swap            : 1;  /* bit[30]   : Change the word order of all setup-finalize descriptor from the following engines AES, DES. */
        unsigned int  bytes_swap           : 1;  /* bit[31]   : Change the bytes order of all setup-finalize descriptor from the following engines AES, DES.  */
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_data_flow_mode_START        (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_data_flow_mode_END          (5)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_aes_xor_crypto_key_START    (7)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_aes_xor_crypto_key_END      (7)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_ack_needed_START            (8)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_ack_needed_END              (9)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_mode_START           (10)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_mode_END             (13)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cmac_size0_START            (14)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cmac_size0_END              (14)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_do_START             (15)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_do_END               (16)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_conf0_START          (17)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_conf0_END            (18)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_conf1_START          (19)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_conf1_END            (19)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_conf2_START          (20)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_conf2_END            (21)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_key_size_START              (22)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_key_size_END                (23)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_setup_operation_START       (24)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_setup_operation_END         (27)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_din_sram_endianness_START   (28)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_din_sram_endianness_END     (28)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_dout_sram_endianness_START  (29)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_dout_sram_endianness_END    (29)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_word_swap_START             (30)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_word_swap_END               (30)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_bytes_swap_START            (31)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_bytes_swap_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WORD5 �Ĵ����ṹ���塣��ַƫ����:0x00E94����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word5 of the descriptor��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_addr_high : 16; /* bit[0-15] : When using 48-bits AXI address, this field defines the highest 16bits of the DOUT address. */
        unsigned int  din_addr_high  : 16; /* bit[16-31]: When using 48-bits AXI address, this field defines the highest 16bits of the DIN address. */
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_dout_addr_high_START  (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_dout_addr_high_END    (15)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_din_addr_high_START   (16)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_din_addr_high_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_QUEUE0_WATERMARK_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WATERMARK �Ĵ����ṹ���塣��ַƫ����:0x00E98����ֵ:0x0000001F�����:32
 �Ĵ���˵��: This register holds the watermark value of descriptor queue0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  watermark : 5;  /* bit[0-4] : queue 0 watermark: if the amount of empty entries exceeds the watermark level, an interrupt is issued. possible values 0-14. */
        unsigned int  reserved  : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WATERMARK_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WATERMARK_watermark_START  (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WATERMARK_watermark_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_DSCRPTR_QUEUE0_CONTENT_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_CONTENT �Ĵ����ṹ���塣��ַƫ����:0x00E9C����ֵ:0x0000000F�����:32
 �Ĵ���˵��: This register holds the number of empty entries in descriptor queue0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  queue0_content : 4;  /* bit[0-3] : The number of empty entries in queue0 */
        unsigned int  reserved       : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_CONTENT_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_CONTENT_queue0_content_START  (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_CONTENT_queue0_content_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_SRAM_DATA_UNION
 �ṹ˵��  : SRAM_DATA �Ĵ����ṹ���塣��ַƫ����:0x00F00����ֵ:0x00000000�����:32
 �Ĵ���˵��: READ WRITE DATA FROM SRAM NOTE! This is a special register, affected by internal logic�� Test result of this register is NA��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_data : 32; /* bit[0-31]: 32 bit write or read from SRAM: 
                                                    read - triggers the SRAM read DMA address automatically incremented��
                                                    write - triggers the SRAM write DMA address automatically incremented */
    } reg;
} SOC_SECENG_S_SRAM_DATA_UNION;
#endif
#define SOC_SECENG_S_SRAM_DATA_sram_data_START  (0)
#define SOC_SECENG_S_SRAM_DATA_sram_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_SRAM_ADDR_UNION
 �ṹ˵��  : SRAM_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00F04����ֵ:0x00000000�����:32
 �Ĵ���˵��: first address given to SRAM DMA for read/write transactions from SRAM��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_addr : 15; /* bit[0-14] : SRAM starting address */
        unsigned int  reserved  : 17; /* bit[15-31]: ���� */
    } reg;
} SOC_SECENG_S_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_S_SRAM_ADDR_sram_addr_START  (0)
#define SOC_SECENG_S_SRAM_ADDR_sram_addr_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_S_SRAM_DATA_READY_UNION
 �ṹ˵��  : SRAM_DATA_READY �Ĵ����ṹ���塣��ַƫ����:0x00F08����ֵ:0x00000001�����:32
 �Ĵ���˵��: sram data ready��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_ready : 1;  /* bit[0]   : SRAM content is ready for read in SRAM_DATA register */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SECENG_S_SRAM_DATA_READY_UNION;
#endif
#define SOC_SECENG_S_SRAM_DATA_READY_sram_ready_START  (0)
#define SOC_SECENG_S_SRAM_DATA_READY_sram_ready_END    (0)






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

#endif /* end of soc_seceng_s_interface.h */
