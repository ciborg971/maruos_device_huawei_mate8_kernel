/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_seceng_p_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:54
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_SECENG_P.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_SECENG_P_INTERFACE_H__
#define __SOC_SECENG_P_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_SECENG_P
 ****************************************************************************/
/* �Ĵ���˵����The AES clock enable register.
            NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_AES_CLK_ENABLE_UNION */
#define SOC_SECENG_P_AES_CLK_ENABLE_ADDR(base)        ((base) + (0x00810))

/* �Ĵ���˵����The DES clock enable register. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_DES_CLK_ENABLE_UNION */
#define SOC_SECENG_P_DES_CLK_ENABLE_ADDR(base)        ((base) + (0x00814))

/* �Ĵ���˵����The HASH clock enable register. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_HASH_CLK_ENABLE_UNION */
#define SOC_SECENG_P_HASH_CLK_ENABLE_ADDR(base)       ((base) + (0x00818))

/* �Ĵ���˵����DMA_CLK enable register. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_DMA_CLK_ENABLE_UNION */
#define SOC_SECENG_P_DMA_CLK_ENABLE_ADDR(base)        ((base) + (0x00820))

/* �Ĵ���˵����The CryptoCell clocks' status register. If LCS is secure, all engines' clocks are disabled. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_CLK_STATUS_UNION */
#define SOC_SECENG_P_CLK_STATUS_ADDR(base)            ((base) + (0x00824))

/* �Ĵ���˵����Defines the cryptographic flow.
   λ����UNION�ṹ:  SOC_SECENG_P_CRYPTO_CTL_UNION */
#define SOC_SECENG_P_CRYPTO_CTL_ADDR(base)            ((base) + (0x00900))

/* �Ĵ���˵����This register is set when the cryptographic core is busy.
   λ����UNION�ṹ:  SOC_SECENG_P_CRYPTO_BUSY_UNION */
#define SOC_SECENG_P_CRYPTO_BUSY_ADDR(base)           ((base) + (0x00910))

/* �Ĵ���˵����This register is set when the Hash engine is busy.
   λ����UNION�ṹ:  SOC_SECENG_P_HASH_BUSY_UNION */
#define SOC_SECENG_P_HASH_BUSY_ADDR(base)             ((base) + (0x0091C))

/* �Ĵ���˵����This register holds the current CryptoCell version.
   λ����UNION�ṹ:  SOC_SECENG_P_VERSION_UNION */
#define SOC_SECENG_P_VERSION_ADDR(base)               ((base) + (0x00928))

/* �Ĵ���˵����A general RD/WR register. For Firmware use.
   λ����UNION�ṹ:  SOC_SECENG_P_CONTEXT_ID_UNION */
#define SOC_SECENG_P_CONTEXT_ID_ADDR(base)            ((base) + (0x00930))

/* �Ĵ���˵����This register holds the flow ID of the descriptor that caused that last error.
   λ����UNION�ṹ:  SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO0_UNION */
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO0_ADDR(base) ((base) + (0x00940))

/* �Ĵ���˵����This register holds the flow ID of the descriptor that caused that one-before-last error.
   λ����UNION�ṹ:  SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO1_UNION */
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO1_ADDR(base) ((base) + (0x00944))

/* �Ĵ���˵����This register holds the flow ID of the descriptor that caused that two-before-last error.
   λ����UNION�ṹ:  SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO2_UNION */
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO2_ADDR(base) ((base) + (0x00948))

/* �Ĵ���˵����This register holds the flow ID of the descriptor that caused that three-before-last error.
   λ����UNION�ṹ:  SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO3_UNION */
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO3_ADDR(base) ((base) + (0x0094C))

/* �Ĵ���˵����Interrupt Request Register - holds interrupt status. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_IRR_UNION */
#define SOC_SECENG_P_HOST_IRR_ADDR(base)              ((base) + (0x00A00))

/* �Ĵ���˵����Interrupt Mask Register.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_IMR_UNION */
#define SOC_SECENG_P_HOST_IMR_ADDR(base)              ((base) + (0x00A04))

/* �Ĵ���˵����Interrupt Clear Register.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_ICR_UNION */
#define SOC_SECENG_P_HOST_ICR_ADDR(base)              ((base) + (0x00A08))

/* �Ĵ���˵����Host cannot access the SRAM up to this threshold level (address) . NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_SEP_SRAM_THRESHOLD_UNION */
#define SOC_SECENG_P_HOST_SEP_SRAM_THRESHOLD_ADDR(base) ((base) + (0x00A10))

/* �Ĵ���˵����SEP_BUSY indication. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_SEP_BUSY_UNION */
#define SOC_SECENG_P_HOST_SEP_BUSY_ADDR(base)         ((base) + (0x00A14))

/* �Ĵ���˵����SEP_SW_MONITOR Register.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_SEP_SW_MONITOR_UNION */
#define SOC_SECENG_P_HOST_SEP_SW_MONITOR_ADDR(base)   ((base) + (0x00A20))

/* �Ĵ���˵����Entire CryptoCell software reset NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_CC_SW_RST_UNION */
#define SOC_SECENG_P_HOST_CC_SW_RST_ADDR(base)        ((base) + (0x00A40))

/* �Ĵ���˵����sep-host communication register #0. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_SEP_HOST_GPR0_UNION */
#define SOC_SECENG_P_HOST_SEP_HOST_GPR0_ADDR(base)    ((base) + (0x00A80))

/* �Ĵ���˵����host-sep communication register #0. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_HOST_SEP_GPR0_UNION */
#define SOC_SECENG_P_HOST_HOST_SEP_GPR0_ADDR(base)    ((base) + (0x00A84))

/* �Ĵ���˵����sep-host communication register #1
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_SEP_HOST_GPR1_UNION */
#define SOC_SECENG_P_HOST_SEP_HOST_GPR1_ADDR(base)    ((base) + (0x00A88))

/* �Ĵ���˵����host-sep communication register #1 NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_HOST_SEP_GPR1_UNION */
#define SOC_SECENG_P_HOST_HOST_SEP_GPR1_ADDR(base)    ((base) + (0x00A8C))

/* �Ĵ���˵����sep-host communication register #2
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_SEP_HOST_GPR2_UNION */
#define SOC_SECENG_P_HOST_SEP_HOST_GPR2_ADDR(base)    ((base) + (0x00A90))

/* �Ĵ���˵����host-sep communication register #2
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_HOST_SEP_GPR2_UNION */
#define SOC_SECENG_P_HOST_HOST_SEP_GPR2_ADDR(base)    ((base) + (0x00A94))

/* �Ĵ���˵����sep-host communication register #3
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_SEP_HOST_GPR3_UNION */
#define SOC_SECENG_P_HOST_SEP_HOST_GPR3_ADDR(base)    ((base) + (0x00A98))

/* �Ĵ���˵����host-sep communication register #3
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_HOST_SEP_GPR3_UNION */
#define SOC_SECENG_P_HOST_HOST_SEP_GPR3_ADDR(base)    ((base) + (0x00A9C))

/* �Ĵ���˵����sep-host communication register #4
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_SEP_HOST_GPR4_UNION */
#define SOC_SECENG_P_HOST_SEP_HOST_GPR4_ADDR(base)    ((base) + (0x00AA0))

/* �Ĵ���˵����host-sep communication register #4
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_HOST_SEP_GPR4_UNION */
#define SOC_SECENG_P_HOST_HOST_SEP_GPR4_ADDR(base)    ((base) + (0x00AA4))

/* �Ĵ���˵����sep-host communication register #5
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_SEP_HOST_GPR5_UNION */
#define SOC_SECENG_P_HOST_SEP_HOST_GPR5_ADDR(base)    ((base) + (0x00AA8))

/* �Ĵ���˵����host-sep communication register #5
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_HOST_SEP_GPR5_UNION */
#define SOC_SECENG_P_HOST_HOST_SEP_GPR5_ADDR(base)    ((base) + (0x00AAC))

/* �Ĵ���˵����sep-host communication register #6
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_SEP_HOST_GPR6_UNION */
#define SOC_SECENG_P_HOST_SEP_HOST_GPR6_ADDR(base)    ((base) + (0x00AB0))

/* �Ĵ���˵����host-sep communication register #6
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_HOST_SEP_GPR6_UNION */
#define SOC_SECENG_P_HOST_HOST_SEP_GPR6_ADDR(base)    ((base) + (0x00AB4))

/* �Ĵ���˵����sep-host communication register #7
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_SEP_HOST_GPR7_UNION */
#define SOC_SECENG_P_HOST_SEP_HOST_GPR7_ADDR(base)    ((base) + (0x00AB8))

/* �Ĵ���˵����host-sep communication register #7
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_HOST_SEP_GPR7_UNION */
#define SOC_SECENG_P_HOST_HOST_SEP_GPR7_ADDR(base)    ((base) + (0x00ABC))

/* �Ĵ���˵����CryptoCell signature
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_CC_SIGNATURE_UNION */
#define SOC_SECENG_P_HOST_CC_SIGNATURE_ADDR(base)     ((base) + (0x00AC8))

/* �Ĵ���˵����Host endianness configuration register. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_HOST_ENDIAN_UNION */
#define SOC_SECENG_P_HOST_HOST_ENDIAN_ADDR(base)      ((base) + (0x00AD0))

/* �Ĵ���˵����Host endianness configuration register. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_IRQ_TIMER_INIT_VAL_UNION */
#define SOC_SECENG_P_HOST_IRQ_TIMER_INIT_VAL_ADDR(base) ((base) + (0x0AD4))

/* �Ĵ���˵����This register holds the HW version. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_HOST_VERSION_UNION */
#define SOC_SECENG_P_HOST_VERSION_ADDR(base)          ((base) + (0x0AD8))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=0
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHT0_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHT0_ADDR(base)    ((base) + (0x00B00))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=1
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHT1_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHT1_ADDR(base)    ((base) + (0x00B04))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=2
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHT2_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHT2_ADDR(base)    ((base) + (0x00B08))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=3
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHT3_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHT3_ADDR(base)    ((base) + (0x00B0C))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=4
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHT4_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHT4_ADDR(base)    ((base) + (0x00B10))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=5
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHT5_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHT5_ADDR(base)    ((base) + (0x00B14))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=8
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHT8_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHT8_ADDR(base)    ((base) + (0x00B20))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=9
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHT9_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHT9_ADDR(base)    ((base) + (0x00B24))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=10
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHT10_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHT10_ADDR(base)   ((base) + (0x00B28))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=11
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHT11_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHT11_ADDR(base)   ((base) + (0x00B2C))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=0 and last indication bit set.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHTLAST0_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST0_ADDR(base) ((base) + (0x00B40))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=1 and last indication bit set.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHTLAST1_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST1_ADDR(base) ((base) + (0x00B44))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=2 and last indication bit set.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHTLAST2_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST2_ADDR(base) ((base) + (0x00B48))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=3 and last indication bit set.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHTLAST3_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST3_ADDR(base) ((base) + (0x00B4C))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=4 and last indication bit set.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHTLAST4_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST4_ADDR(base) ((base) + (0x00B50))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=5 and last indication bit set.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHTLAST5_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST5_ADDR(base) ((base) + (0x00B54))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=8 and last indication bit set.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_ADDR(base) ((base) + (0x00B60))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=9 and last indication bit set.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHTLAST9_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST9_ADDR(base) ((base) + (0x00B64))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=10 and last indication bit set.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHTLAST10_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST10_ADDR(base) ((base) + (0x00B68))

/* �Ĵ���˵����This register holds the number of uncompleted write transactions, with ID=11 and last indication bit set.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_INFLIGHTLAST11_UNION */
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST11_ADDR(base) ((base) + (0x00B6C))

/* �Ĵ���˵����This register holds the status of AXI port 0.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_PIDTABLE0_UNION */
#define SOC_SECENG_P_AXIM_PIDTABLE0_ADDR(base)        ((base) + (0x00B70))

/* �Ĵ���˵����This register holds the status of AXI port 1.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_PIDTABLE1_UNION */
#define SOC_SECENG_P_AXIM_PIDTABLE1_ADDR(base)        ((base) + (0x00B74))

/* �Ĵ���˵����This register holds the status of AXI port 2.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_PIDTABLE2_UNION */
#define SOC_SECENG_P_AXIM_PIDTABLE2_ADDR(base)        ((base) + (0x00B78))

/* �Ĵ���˵����This register holds the status of AXI port 3.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_PIDTABLE3_UNION */
#define SOC_SECENG_P_AXIM_PIDTABLE3_ADDR(base)        ((base) + (0x00B7C))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=0.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_COMP0_UNION */
#define SOC_SECENG_P_AXIM_MON_COMP0_ADDR(base)        ((base) + (0x00B80))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=1.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_COMP1_UNION */
#define SOC_SECENG_P_AXIM_MON_COMP1_ADDR(base)        ((base) + (0x00B84))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=2.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_COMP2_UNION */
#define SOC_SECENG_P_AXIM_MON_COMP2_ADDR(base)        ((base) + (0x00B88))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=3.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_COMP3_UNION */
#define SOC_SECENG_P_AXIM_MON_COMP3_ADDR(base)        ((base) + (0x00B8C))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=4.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_COMP4_UNION */
#define SOC_SECENG_P_AXIM_MON_COMP4_ADDR(base)        ((base) + (0x00B90))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=5.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_COMP5_UNION */
#define SOC_SECENG_P_AXIM_MON_COMP5_ADDR(base)        ((base) + (0x00B94))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=8.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_COMP8_UNION */
#define SOC_SECENG_P_AXIM_MON_COMP8_ADDR(base)        ((base) + (0x00BA0))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=9.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_COMP9_UNION */
#define SOC_SECENG_P_AXIM_MON_COMP9_ADDR(base)        ((base) + (0x00BA4))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=10.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_COMP10_UNION */
#define SOC_SECENG_P_AXIM_MON_COMP10_ADDR(base)       ((base) + (0x00BA8))

/* �Ĵ���˵����This register holds the completion counter of the transaction with ID=11.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_COMP11_UNION */
#define SOC_SECENG_P_AXIM_MON_COMP11_ADDR(base)       ((base) + (0x00BAC))

/* �Ĵ���˵����max latency for read transactions
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_RMAX_UNION */
#define SOC_SECENG_P_AXIM_MON_RMAX_ADDR(base)         ((base) + (0x00BB4))

/* �Ĵ���˵����min latency for read transactions
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_RMIN_UNION */
#define SOC_SECENG_P_AXIM_MON_RMIN_ADDR(base)         ((base) + (0x00BB8))

/* �Ĵ���˵����max latency for write transactions
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_WMAX_UNION */
#define SOC_SECENG_P_AXIM_MON_WMAX_ADDR(base)         ((base) + (0x00BBC))

/* �Ĵ���˵����min latency for write transactions
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_WMIN_UNION */
#define SOC_SECENG_P_AXIM_MON_WMIN_ADDR(base)         ((base) + (0x00BC0))

/* �Ĵ���˵����Error information
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_MON_ERR_UNION */
#define SOC_SECENG_P_AXIM_MON_ERR_ADDR(base)          ((base) + (0x00BC4))

/* �Ĵ���˵����read channel status
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_RDSTAT_UNION */
#define SOC_SECENG_P_AXIM_RDSTAT_ADDR(base)           ((base) + (0x00BC8))

/* �Ĵ���˵����Accumulated read latency
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_RLATENCY_UNION */
#define SOC_SECENG_P_AXIM_RLATENCY_ADDR(base)         ((base) + (0x00BD0))

/* �Ĵ���˵����Accumulated read bursts
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_RBURST_UNION */
#define SOC_SECENG_P_AXIM_RBURST_ADDR(base)           ((base) + (0x00BD4))

/* �Ĵ���˵����Accumulated write latency
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_WLATENCY_UNION */
#define SOC_SECENG_P_AXIM_WLATENCY_ADDR(base)         ((base) + (0x00BD8))

/* �Ĵ���˵����Accumulated write bursts
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_WBURST_UNION */
#define SOC_SECENG_P_AXIM_WBURST_ADDR(base)           ((base) + (0x00BDC))

/* �Ĵ���˵����AXI master cache-type configuration.
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_CACHETYPE_CFG_UNION */
#define SOC_SECENG_P_AXIM_CACHETYPE_CFG_ADDR(base)    ((base) + (0x00BE0))

/* �Ĵ���˵����AXIM Protection field configuration
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_PROT_CFG_UNION */
#define SOC_SECENG_P_AXIM_PROT_CFG_ADDR(base)         ((base) + (0x00BE4))

/* �Ĵ���˵����AXI master configuration
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_CFG1_UNION */
#define SOC_SECENG_P_AXIM_CFG1_ADDR(base)             ((base) + (0x00BE8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_ACE_CONST_UNION */
#define SOC_SECENG_P_AXIM_ACE_CONST_ADDR(base)        ((base) + (0x0BEC))

/* �Ĵ���˵����AXI master configuration for DMA
   λ����UNION�ṹ:  SOC_SECENG_P_AXIM_CACHE_PARAMS_UNION */
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_ADDR(base)     ((base) + (0x0BF0))

/* �Ĵ���˵����Control AXI master.
   λ����UNION�ṹ:  SOC_SECENG_P_ADDR_AXIM_CTRL_UNION */
#define SOC_SECENG_P_ADDR_AXIM_CTRL_ADDR(base)        ((base) + (0x0BF4))

/* �Ĵ���˵����This address can be used by the CPU to write data directly to the DIN buffer to be sent to engines.
   λ����UNION�ṹ:  SOC_SECENG_P_DIN_BUFFER_UNION */
#define SOC_SECENG_P_DIN_BUFFER_ADDR(base)            ((base) + (0x00C00))

/* �Ĵ���˵����Indicates whether memory (AXI) source DMA (DIN) is busy.
   λ����UNION�ṹ:  SOC_SECENG_P_DIN_MEM_DMA_BUSY_UNION */
#define SOC_SECENG_P_DIN_MEM_DMA_BUSY_ADDR(base)      ((base) + (0x00C20))

/* �Ĵ���˵����Location of LLI table located in the SRAM. in SINGLE/MULTI_LLI mode, writing to this register triggers the DMA. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_SRC_LLI_SRAM_ADDR_UNION */
#define SOC_SECENG_P_SRC_LLI_SRAM_ADDR_ADDR(base)     ((base) + (0x00C24))

/* �Ĵ���˵����This register is used in direct LLI mode - holds the location of the data source in the memory (AXI).
   λ����UNION�ṹ:  SOC_SECENG_P_SRC_LLI_WORD0_UNION */
#define SOC_SECENG_P_SRC_LLI_WORD0_ADDR(base)         ((base) + (0x00C28))

/* �Ĵ���˵����This register is used in direct LLI mode - holds the number of bytes to be read from the memory (AXI). Writing to this register triggers the DMA. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_SRC_LLI_WORD1_UNION */
#define SOC_SECENG_P_SRC_LLI_WORD1_ADDR(base)         ((base) + (0x00C2C))

/* �Ĵ���˵����Location of data (start address) to be read from SRAM. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_SRAM_SRC_ADDR_UNION */
#define SOC_SECENG_P_SRAM_SRC_ADDR_ADDR(base)         ((base) + (0x00C30))

/* �Ĵ���˵����This register holds the size of the data (in bytes) to be read from the SRAM. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_DIN_SRAM_BYTES_LEN_UNION */
#define SOC_SECENG_P_DIN_SRAM_BYTES_LEN_ADDR(base)    ((base) + (0x00C34))

/* �Ĵ���˵����This register holds the status of the SRAM DMA DIN.
   λ����UNION�ṹ:  SOC_SECENG_P_DIN_SRAM_DMA_BUSY_UNION */
#define SOC_SECENG_P_DIN_SRAM_DMA_BUSY_ADDR(base)     ((base) + (0x00C38))

/* �Ĵ���˵����This register defines the endianness of the DIN interface to SRAM.
   λ����UNION�ṹ:  SOC_SECENG_P_DIN_SRAM_ENDIANNESS_UNION */
#define SOC_SECENG_P_DIN_SRAM_ENDIANNESS_ADDR(base)   ((base) + (0x00C3C))

/* �Ĵ���˵����This register holds RDID and PROT when using the CPU.
   λ����UNION�ṹ:  SOC_SECENG_P_AXI_CPU_DIN_PARAMS_UNION */
#define SOC_SECENG_P_AXI_CPU_DIN_PARAMS_ADDR(base)    ((base) + (0x00C40))

/* �Ĵ���˵����DIN software reset.
   λ����UNION�ṹ:  SOC_SECENG_P_DIN_SW_RESET_UNION */
#define SOC_SECENG_P_DIN_SW_RESET_ADDR(base)          ((base) + (0x00C44))

/* �Ĵ���˵����Data path to DIN is OTF
   λ����UNION�ṹ:  SOC_SECENG_P_DIN_CPU_DATA_SIZE_UNION */
#define SOC_SECENG_P_DIN_CPU_DATA_SIZE_ADDR(base)     ((base) + (0x0C48))

/* �Ĵ���˵����Indication that the next write from the CPU is the last one. This is needed only when the data size is NOT modulo 4 (e.g. HASH padding).
   λ����UNION�ṹ:  SOC_SECENG_P_WRITE_ALIGN_LAST_UNION */
#define SOC_SECENG_P_WRITE_ALIGN_LAST_ADDR(base)      ((base) + (0x00C4C))

/* �Ĵ���˵����DIN FIFO empty indication
   λ����UNION�ṹ:  SOC_SECENG_P_FIFO_IN_EMPTY_UNION */
#define SOC_SECENG_P_FIFO_IN_EMPTY_ADDR(base)         ((base) + (0x00C50))

/* �Ĵ���˵����Disables the outstanding DIN request
   λ����UNION�ṹ:  SOC_SECENG_P_DISABLE_OUTSTD_REQ_UNION */
#define SOC_SECENG_P_DISABLE_OUTSTD_REQ_ADDR(base)    ((base) + (0x00C54))

/* �Ĵ���˵����Writing to this register resets the DIN_FIFO pointers.
   λ����UNION�ṹ:  SOC_SECENG_P_DIN_FIFO_RST_PNTR_UNION */
#define SOC_SECENG_P_DIN_FIFO_RST_PNTR_ADDR(base)     ((base) + (0x00C58))

/* �Ĵ���˵����Cryptographic result - CPU can directly access it. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_DOUT_BUFFER_UNION */
#define SOC_SECENG_P_DOUT_BUFFER_ADDR(base)           ((base) + (0x00D00))

/* �Ĵ���˵����DOUT memory DMA busy - Indicates that memory (AXI) destination DMA (DOUT) is busy,
   λ����UNION�ṹ:  SOC_SECENG_P_DOUT_MEM_DMA_BUSY_UNION */
#define SOC_SECENG_P_DOUT_MEM_DMA_BUSY_ADDR(base)     ((base) + (0x00D20))

/* �Ĵ���˵����This register holds the destination LLI table address in SRAM. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_DST_LLI_SRAM_ADDR_UNION */
#define SOC_SECENG_P_DST_LLI_SRAM_ADDR_ADDR(base)     ((base) + (0x00D24))

/* �Ĵ���˵����This register is used in direct LLI mode - holds the location of the data destination in the memory (AXI)
   λ����UNION�ṹ:  SOC_SECENG_P_DST_LLI_WORD0_UNION */
#define SOC_SECENG_P_DST_LLI_WORD0_ADDR(base)         ((base) + (0x00D28))

/* �Ĵ���˵����This register is used in direct LLI mode - holds the number of bytes to be written to the memory (AXI).
   λ����UNION�ṹ:  SOC_SECENG_P_DST_LLI_WORD1_UNION */
#define SOC_SECENG_P_DST_LLI_WORD1_ADDR(base)         ((base) + (0x00D2C))

/* �Ĵ���˵����Location of result to be sent to in SRAM NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_SRAM_DEST_ADDR_UNION */
#define SOC_SECENG_P_SRAM_DEST_ADDR_ADDR(base)        ((base) + (0x00D30))

/* �Ĵ���˵����This register holds the size of the data (in bytes) to be written to the SRAM. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_DOUT_SRAM_BYTES_LEN_UNION */
#define SOC_SECENG_P_DOUT_SRAM_BYTES_LEN_ADDR(base)   ((base) + (0x00D34))

/* �Ĵ���˵����This register holds the status of the SRAM DMA DOUT.
   λ����UNION�ṹ:  SOC_SECENG_P_DOUT_SRAM_DMA_BUSY_UNION */
#define SOC_SECENG_P_DOUT_SRAM_DMA_BUSY_ADDR(base)    ((base) + (0x00D38))

/* �Ĵ���˵����This register defines the endianness of the DOUT interface from SRAM.
   λ����UNION�ṹ:  SOC_SECENG_P_DOUT_SRAM_ENDIANNESS_UNION */
#define SOC_SECENG_P_DOUT_SRAM_ENDIANNESS_ADDR(base)  ((base) + (0x00D3C))

/* �Ĵ���˵����Indication that the next read from the CPU is the last one. This is needed only when the data size is NOT modulo 4 (e.g. HASH padding).
   λ����UNION�ṹ:  SOC_SECENG_P_READ_ALIGN_LAST_UNION */
#define SOC_SECENG_P_READ_ALIGN_LAST_ADDR(base)       ((base) + (0x00D44))

/* �Ĵ���˵����DOUT_FIFO_EMPTY Register.
   λ����UNION�ṹ:  SOC_SECENG_P_DOUT_FIFO_EMPTY_UNION */
#define SOC_SECENG_P_DOUT_FIFO_EMPTY_ADDR(base)       ((base) + (0x00D50))

/* �Ĵ���˵����AXI_CPU_DOUT_PARAMS Register.
   λ����UNION�ṹ:  SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_UNION */
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_ADDR(base)   ((base) + (0x00D54))

/* �Ĵ���˵����Software reset for DOUT.
   λ����UNION�ṹ:  SOC_SECENG_P_DOUT_SW_RESET_UNION */
#define SOC_SECENG_P_DOUT_SW_RESET_ADDR(base)         ((base) + (0x00D58))

/* �Ĵ���˵����This register counts the number of completed descriptors in which the ACK_NEEDED field equals 1.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_UNION */
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_ADDR(base) ((base) + (0x00E00))

/* �Ĵ���˵����This register counts the number of completed descriptors in which the ACK_NEEDED field equals 2.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_UNION */
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_ADDR(base) ((base) + (0x00E04))

/* �Ĵ���˵����This register holds the status of the completion counters.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_COMPLETION_STATUS_UNION */
#define SOC_SECENG_P_DSCRPTR_COMPLETION_STATUS_ADDR(base) ((base) + (0x00E3C))

/* �Ĵ���˵����Software reset for descriptors.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_SW_RESET_UNION */
#define SOC_SECENG_P_DSCRPTR_SW_RESET_ADDR(base)      ((base) + (0x00E40))

/* �Ĵ���˵����This register enables the use of special descriptors
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_DEBUG_MODE_UNION */
#define SOC_SECENG_P_DSCRPTR_DEBUG_MODE_ADDR(base)    ((base) + (0x00E4C))

/* �Ĵ���˵����This register counts the number of descriptors dropped by queue filtered module, after not complying with the restrictions.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_CNT_UNION */
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_CNT_ADDR(base) ((base) + (0x00E50))

/* �Ĵ���˵����This register counts the number of descriptors dropped by queue filtered module, after not complying with the restrictions and the destination is system memory.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_MEM_CNT_UNION */
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_MEM_CNT_ADDR(base) ((base) + (0x00E54))

/* �Ĵ���˵����This register holds which restriction failed to be complied with.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_FILTER_DEBUG_UNION */
#define SOC_SECENG_P_DSCRPTR_FILTER_DEBUG_ADDR(base)  ((base) + (0x00E58))

/* �Ĵ���˵����This register holds the address to which CryptoCell writes when descriptor does not comply with restriction.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_UNION */
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_ADDR(base) ((base) + (0x00E5C))

/* �Ĵ���˵����This register holds the size of the SRAM queue.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE_SRAM_SIZE_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE_SRAM_SIZE_ADDR(base) ((base) + (0x00E60))

/* �Ĵ���˵����This register enables the Host to write a descriptor using a single address.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_SINGLE_ADDR_EN_UNION */
#define SOC_SECENG_P_DSCRPTR_SINGLE_ADDR_EN_ADDR(base) ((base) + (0x0E64))

/* �Ĵ���˵����This register holds the number of cycles measured when using the special performance descriptor.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_MEASURE_CNTR_UNION */
#define SOC_SECENG_P_DSCRPTR_MEASURE_CNTR_ADDR(base)  ((base) + (0x0E68))

/* �Ĵ���˵����This register holds the upper 16bits of the address to which CryptoCell writes when descriptor does not comply with restriction.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_UNION */
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_ADDR(base) ((base) + (0x0E6C))

/* �Ĵ���˵����This register holds word0 of the descriptor.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE0_WORD0_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD0_ADDR(base)  ((base) + (0x00E80))

/* �Ĵ���˵����This register holds word1 of the descriptor.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_ADDR(base)  ((base) + (0x00E84))

/* �Ĵ���˵����This register holds word2 of the descriptor.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE0_WORD2_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD2_ADDR(base)  ((base) + (0x00E88))

/* �Ĵ���˵����This register holds word3 of the descriptor.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_ADDR(base)  ((base) + (0x00E8C))

/* �Ĵ���˵����This register holds word4 of the descriptor.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_ADDR(base)  ((base) + (0x00E90))

/* �Ĵ���˵����This register holds word5 of the descriptor.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_ADDR(base)  ((base) + (0x00E94))

/* �Ĵ���˵����This register holds the watermark value of descriptor queue0.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE0_WATERMARK_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WATERMARK_ADDR(base) ((base) + (0x00E98))

/* �Ĵ���˵����This register holds the number of empty entries in descriptor queue0.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE0_CONTENT_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE0_CONTENT_ADDR(base) ((base) + (0x00E9C))

/* �Ĵ���˵����This register holds word0 of descriptor queue1.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE1_WORD0_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD0_ADDR(base)  ((base) + (0x00EA0))

/* �Ĵ���˵����This register holds word1 of descriptor queue1.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_ADDR(base)  ((base) + (0x00EA4))

/* �Ĵ���˵����This register holds word2 of descriptor queue1.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE1_WORD2_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD2_ADDR(base)  ((base) + (0x00EA8))

/* �Ĵ���˵����This register holds word3 of descriptor queue1.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_ADDR(base)  ((base) + (0x00EAC))

/* �Ĵ���˵����This register holds word4 of descriptor queue1.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_ADDR(base)  ((base) + (0x00EB0))

/* �Ĵ���˵����This register holds word5 of descriptor queue1.
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_ADDR(base)  ((base) + (0x0EB4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE1_WATERMARK_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WATERMARK_ADDR(base) ((base) + (0x00EB8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_SECENG_P_DSCRPTR_QUEUE1_CONTENT_UNION */
#define SOC_SECENG_P_DSCRPTR_QUEUE1_CONTENT_ADDR(base) ((base) + (0x00EBC))

/* �Ĵ���˵����READ WRITE DATA FROM SRAM NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
   λ����UNION�ṹ:  SOC_SECENG_P_SRAM_DATA_UNION */
#define SOC_SECENG_P_SRAM_DATA_ADDR(base)             ((base) + (0x00F00))

/* �Ĵ���˵����first address given to SRAM DMA for read/write transactions from SRAM
   λ����UNION�ṹ:  SOC_SECENG_P_SRAM_ADDR_UNION */
#define SOC_SECENG_P_SRAM_ADDR_ADDR(base)             ((base) + (0x00F04))

/* �Ĵ���˵����reserved
   λ����UNION�ṹ:  SOC_SECENG_P_SRAM_DATA_READY_UNION */
#define SOC_SECENG_P_SRAM_DATA_READY_ADDR(base)       ((base) + (0x00F08))





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
                     (1/1) register_SECENG_P
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AES_CLK_ENABLE_UNION
 �ṹ˵��  : AES_CLK_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x00810����ֵ:0x00000000�����:32
 �Ĵ���˵��: The AES clock enable register.
            NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : 1'b1: the AES clock is enabled.
                                                   1'b0: the AES clock is disabled. */
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_AES_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_P_AES_CLK_ENABLE_en_START        (0)
#define SOC_SECENG_P_AES_CLK_ENABLE_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DES_CLK_ENABLE_UNION
 �ṹ˵��  : DES_CLK_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x00814����ֵ:0x00000000�����:32
 �Ĵ���˵��: The DES clock enable register. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : 1'b1: the DES clock is enabled.
                                                   1'b0: the DES clock is disabled.  */
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DES_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_P_DES_CLK_ENABLE_en_START        (0)
#define SOC_SECENG_P_DES_CLK_ENABLE_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HASH_CLK_ENABLE_UNION
 �ṹ˵��  : HASH_CLK_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x00818����ֵ:0x00000000�����:32
 �Ĵ���˵��: The HASH clock enable register. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : 1'b1: the HASH clock is enabled.
                                                   1'b0: the HASH clock is disabled.  */
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_HASH_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_P_HASH_CLK_ENABLE_en_START        (0)
#define SOC_SECENG_P_HASH_CLK_ENABLE_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DMA_CLK_ENABLE_UNION
 �ṹ˵��  : DMA_CLK_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x00820����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_CLK enable register. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : 1'b1: the DMA clock is enabled.
                                                   1'b0: the DMA clock is disabled.  */
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DMA_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_P_DMA_CLK_ENABLE_en_START        (0)
#define SOC_SECENG_P_DMA_CLK_ENABLE_en_END          (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_CLK_STATUS_UNION
 �ṹ˵��  : CLK_STATUS �Ĵ����ṹ���塣��ַƫ����:0x00824����ֵ:0x00000100�����:32
 �Ĵ���˵��: The CryptoCell clocks' status register. If LCS is secure, all engines' clocks are disabled. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
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
                                                          1'b0: the DES clock is disabled. */
        unsigned int  hash_clk_status : 1;  /* bit[2]   : 1'b1: the HASH clock is enabled.
                                                          1'b0: the HASH clock is disabled.  */
        unsigned int  pka_clk_status  : 1;  /* bit[3]   : 1'b1: the PKA clock is enabled.
                                                          1'b0: the PKA clock is disabled.  */
        unsigned int  reserved_0      : 4;  /* bit[4-7] : reserved */
        unsigned int  dma_clk_status  : 1;  /* bit[8]   : 1'b1: the DMA clock is enabled.
                                                          1'b0: the DMA clock is disabled.  */
        unsigned int  reserved_1      : 23; /* bit[9-31]: reserved */
    } reg;
} SOC_SECENG_P_CLK_STATUS_UNION;
#endif
#define SOC_SECENG_P_CLK_STATUS_aes_clk_status_START   (0)
#define SOC_SECENG_P_CLK_STATUS_aes_clk_status_END     (0)
#define SOC_SECENG_P_CLK_STATUS_des_clk_status_START   (1)
#define SOC_SECENG_P_CLK_STATUS_des_clk_status_END     (1)
#define SOC_SECENG_P_CLK_STATUS_hash_clk_status_START  (2)
#define SOC_SECENG_P_CLK_STATUS_hash_clk_status_END    (2)
#define SOC_SECENG_P_CLK_STATUS_pka_clk_status_START   (3)
#define SOC_SECENG_P_CLK_STATUS_pka_clk_status_END     (3)
#define SOC_SECENG_P_CLK_STATUS_dma_clk_status_START   (8)
#define SOC_SECENG_P_CLK_STATUS_dma_clk_status_END     (8)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_CRYPTO_CTL_UNION
 �ṹ˵��  : CRYPTO_CTL �Ĵ����ṹ���塣��ַƫ����:0x00900����ֵ:0x00000000�����:32
 �Ĵ���˵��: Defines the cryptographic flow.
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
                                                   5'b1011 - reserved
                                                   5'b1000 - reserved  */
        unsigned int  reserved : 27; /* bit[5-31]: reserved */
    } reg;
} SOC_SECENG_P_CRYPTO_CTL_UNION;
#endif
#define SOC_SECENG_P_CRYPTO_CTL_mode_START      (0)
#define SOC_SECENG_P_CRYPTO_CTL_mode_END        (4)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_CRYPTO_BUSY_UNION
 �ṹ˵��  : CRYPTO_BUSY �Ĵ����ṹ���塣��ַƫ����:0x00910����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is set when the cryptographic core is busy.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crypto_busy : 1;  /* bit[0]   : 0 - Ready. 1 - Busy. 
                                                      Asserted when aes_busy or des_busy or hash_busy or rc4_busy or c2_busy are asserted or when the DIN fifo is not empty  */
        unsigned int  reserved    : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_CRYPTO_BUSY_UNION;
#endif
#define SOC_SECENG_P_CRYPTO_BUSY_crypto_busy_START  (0)
#define SOC_SECENG_P_CRYPTO_BUSY_crypto_busy_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HASH_BUSY_UNION
 �ṹ˵��  : HASH_BUSY �Ĵ����ṹ���塣��ַƫ����:0x0091C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is set when the Hash engine is busy.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hash_busy : 1;  /* bit[0]   : 0 - Ready. 1 - Busy. 
                                                    Asserted when hash engine is busy. */
        unsigned int  reserved  : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_HASH_BUSY_UNION;
#endif
#define SOC_SECENG_P_HASH_BUSY_hash_busy_START  (0)
#define SOC_SECENG_P_HASH_BUSY_hash_busy_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_VERSION_UNION
 �ṹ˵��  : VERSION �Ĵ����ṹ���塣��ַƫ����:0x00928����ֵ:0xAF400001�����:32
 �Ĵ���˵��: This register holds the current CryptoCell version.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  version : 32; /* bit[0-31]: auto-generated, hard-coded unique number  */
    } reg;
} SOC_SECENG_P_VERSION_UNION;
#endif
#define SOC_SECENG_P_VERSION_version_START  (0)
#define SOC_SECENG_P_VERSION_version_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_CONTEXT_ID_UNION
 �ṹ˵��  : CONTEXT_ID �Ĵ����ṹ���塣��ַƫ����:0x00930����ֵ:0x00000000�����:32
 �Ĵ���˵��: A general RD/WR register. For Firmware use.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  context_id : 8;  /* bit[0-7] : Context ID */
        unsigned int  reserved   : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_CONTEXT_ID_UNION;
#endif
#define SOC_SECENG_P_CONTEXT_ID_context_id_START  (0)
#define SOC_SECENG_P_CONTEXT_ID_context_id_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO0_UNION
 �ṹ˵��  : HASH_COMPARE_ERR_ID_FIFO0 �Ĵ����ṹ���塣��ַƫ����:0x00940����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the flow ID of the descriptor that caused that last error.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hash_compare_error_id_fifo0 : 26; /* bit[0-25] : Holds the flow ID of the descriptor that caused that last error. */
        unsigned int  reserved                    : 6;  /* bit[26-31]: reserved */
    } reg;
} SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO0_UNION;
#endif
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO0_hash_compare_error_id_fifo0_START  (0)
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO0_hash_compare_error_id_fifo0_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO1_UNION
 �ṹ˵��  : HASH_COMPARE_ERR_ID_FIFO1 �Ĵ����ṹ���塣��ַƫ����:0x00944����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the flow ID of the descriptor that caused that one-before-last error.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hash_compare_error_id_fifo1 : 26; /* bit[0-25] : Holds the flow ID of the descriptor that caused that one-before-last error. */
        unsigned int  reserved                    : 6;  /* bit[26-31]: reserved */
    } reg;
} SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO1_UNION;
#endif
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO1_hash_compare_error_id_fifo1_START  (0)
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO1_hash_compare_error_id_fifo1_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO2_UNION
 �ṹ˵��  : HASH_COMPARE_ERR_ID_FIFO2 �Ĵ����ṹ���塣��ַƫ����:0x00948����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the flow ID of the descriptor that caused that two-before-last error.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hash_compare_error_id_fifo2 : 26; /* bit[0-25] : Holds the flow ID of the descriptor that caused that two-before-last error. */
        unsigned int  reserved                    : 6;  /* bit[26-31]: reserved */
    } reg;
} SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO2_UNION;
#endif
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO2_hash_compare_error_id_fifo2_START  (0)
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO2_hash_compare_error_id_fifo2_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO3_UNION
 �ṹ˵��  : HASH_COMPARE_ERR_ID_FIFO3 �Ĵ����ṹ���塣��ַƫ����:0x0094C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the flow ID of the descriptor that caused that three-before-last error.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hash_compare_error_id_fifo3 : 26; /* bit[0-25] : Holds the flow ID of the descriptor that caused that three-before-last error. */
        unsigned int  reserved                    : 6;  /* bit[26-31]: reserved */
    } reg;
} SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO3_UNION;
#endif
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO3_hash_compare_error_id_fifo3_START  (0)
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO3_hash_compare_error_id_fifo3_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_IRR_UNION
 �ṹ˵��  : HOST_IRR �Ĵ����ṹ���塣��ַƫ����:0x00A00����ֵ:0x00000000�����:32
 �Ĵ���˵��: Interrupt Request Register - holds interrupt status. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                 : 2;  /* bit[0-1]  : reserved */
        unsigned int  dscrptr_completion_low_int : 1;  /* bit[2]    : descriptor completion interrupt */
        unsigned int  host_sram_vio              : 1;  /* bit[3]    : when Host try to access the private section in the SRAM (below HOST_SEP_SRAM_THRESHOLD value) this interrupt request bit is set  */
        unsigned int  sram_to_din_int            : 1;  /* bit[4]    : Din SRAM DMA done indication. all data was delivered to Din bu0er from SRAM */
        unsigned int  dout_to_sram_int           : 1;  /* bit[5]    : Dout SRAM DMA done indication. all data from Dout bu0er was delivered to SRAM */
        unsigned int  mem_to_din_int             : 1;  /* bit[6]    : Din MEM DMA done indication. all data was delivered to Din buffer from memory */
        unsigned int  dout_to_mem_int            : 1;  /* bit[7]    : Dout MEM DMA done indication. all data from Dout buffer was delivered to MEM */
        unsigned int  axi_err_int                : 1;  /* bit[8]    : AXI error interrupt. */
        unsigned int  pka_exp_int                : 1;  /* bit[9]    : PKA end of operation indication */
        unsigned int  rng_int                    : 1;  /* bit[10]   : this interrupt request bit holds all RNG status bits that may cause an interrupt from RNG block */
        unsigned int  sep_host_gpr0_int          : 1;  /* bit[11]   : write event indication for GPR0 */
        unsigned int  sep_host_gpr1_int          : 1;  /* bit[12]   : write event indication for GPR1 */
        unsigned int  sep_host_gpr2_int          : 1;  /* bit[13]   : write event indication for GPR2 */
        unsigned int  sep_host_gpr3_int          : 1;  /* bit[14]   : write event indication for GPR3 */
        unsigned int  sep_host_gpr4_int          : 1;  /* bit[15]   : write event indication for GPR4 */
        unsigned int  sep_host_gpr5_int          : 1;  /* bit[16]   : write event indication for GPR5 */
        unsigned int  sep_host_gpr6_int          : 1;  /* bit[17]   : write event indication for GPR6 */
        unsigned int  sep_host_gpr7_int          : 1;  /* bit[18]   : write event indication for GPR7 */
        unsigned int  dscrptr_watermark0_int     : 1;  /* bit[19]   : descriptor watermark interrupt for queue0 */
        unsigned int  dscrptr_watermark1_int     : 1;  /* bit[20]   : descriptor watermark interrupt for queue1,if exists */
        unsigned int  reserved_1                 : 1;  /* bit[21]   : reserved */
        unsigned int  hash_cmp_error_int         : 1;  /* bit[22]   : Hash compare error interrupt */
        unsigned int  axim_cmp_int               : 1;  /* bit[23]   : AXI master completion interrupt */
        unsigned int  reserved_2                 : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_SECENG_P_HOST_IRR_UNION;
#endif
#define SOC_SECENG_P_HOST_IRR_dscrptr_completion_low_int_START  (2)
#define SOC_SECENG_P_HOST_IRR_dscrptr_completion_low_int_END    (2)
#define SOC_SECENG_P_HOST_IRR_host_sram_vio_START               (3)
#define SOC_SECENG_P_HOST_IRR_host_sram_vio_END                 (3)
#define SOC_SECENG_P_HOST_IRR_sram_to_din_int_START             (4)
#define SOC_SECENG_P_HOST_IRR_sram_to_din_int_END               (4)
#define SOC_SECENG_P_HOST_IRR_dout_to_sram_int_START            (5)
#define SOC_SECENG_P_HOST_IRR_dout_to_sram_int_END              (5)
#define SOC_SECENG_P_HOST_IRR_mem_to_din_int_START              (6)
#define SOC_SECENG_P_HOST_IRR_mem_to_din_int_END                (6)
#define SOC_SECENG_P_HOST_IRR_dout_to_mem_int_START             (7)
#define SOC_SECENG_P_HOST_IRR_dout_to_mem_int_END               (7)
#define SOC_SECENG_P_HOST_IRR_axi_err_int_START                 (8)
#define SOC_SECENG_P_HOST_IRR_axi_err_int_END                   (8)
#define SOC_SECENG_P_HOST_IRR_pka_exp_int_START                 (9)
#define SOC_SECENG_P_HOST_IRR_pka_exp_int_END                   (9)
#define SOC_SECENG_P_HOST_IRR_rng_int_START                     (10)
#define SOC_SECENG_P_HOST_IRR_rng_int_END                       (10)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr0_int_START           (11)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr0_int_END             (11)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr1_int_START           (12)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr1_int_END             (12)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr2_int_START           (13)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr2_int_END             (13)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr3_int_START           (14)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr3_int_END             (14)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr4_int_START           (15)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr4_int_END             (15)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr5_int_START           (16)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr5_int_END             (16)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr6_int_START           (17)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr6_int_END             (17)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr7_int_START           (18)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr7_int_END             (18)
#define SOC_SECENG_P_HOST_IRR_dscrptr_watermark0_int_START      (19)
#define SOC_SECENG_P_HOST_IRR_dscrptr_watermark0_int_END        (19)
#define SOC_SECENG_P_HOST_IRR_dscrptr_watermark1_int_START      (20)
#define SOC_SECENG_P_HOST_IRR_dscrptr_watermark1_int_END        (20)
#define SOC_SECENG_P_HOST_IRR_hash_cmp_error_int_START          (22)
#define SOC_SECENG_P_HOST_IRR_hash_cmp_error_int_END            (22)
#define SOC_SECENG_P_HOST_IRR_axim_cmp_int_START                (23)
#define SOC_SECENG_P_HOST_IRR_axim_cmp_int_END                  (23)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_IMR_UNION
 �ṹ˵��  : HOST_IMR �Ĵ����ṹ���塣��ַƫ����:0x00A04����ֵ:0x01FFFFFF�����:32
 �Ĵ���˵��: Interrupt Mask Register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0              : 2;  /* bit[0-1]  : reserved */
        unsigned int  dscrptr_completion_mask : 1;  /* bit[2]    : Descriptor completion interrupt mask. */
        unsigned int  host_sram_vio_mask      : 1;  /* bit[3]    : Host SRAM violation interrupt mask. */
        unsigned int  sram_to_din_mask        : 1;  /* bit[4]    : DIN SRAM DMA done interrupt mask. */
        unsigned int  dout_to_sram_mask       : 1;  /* bit[5]    : DOUT SRAM DMA done interrupt mask. */
        unsigned int  mem_to_din_mask         : 1;  /* bit[6]    : DIN MEM DMA done interrupt mask. */
        unsigned int  dout_to_mem_mask        : 1;  /* bit[7]    : DOUT MEM DMA done interrupt mask. */
        unsigned int  axi_err_mask            : 1;  /* bit[8]    : AXI error interrupt mask. */
        unsigned int  pka_exp_mask            : 1;  /* bit[9]    : PKA end of operation interrupt mask. */
        unsigned int  rng_int_mask            : 1;  /* bit[10]   : RNG interrupt mask. */
        unsigned int  sep_host_gpr0_mask      : 1;  /* bit[11]   : SEP_HOST_GPR0 interrupt mask. */
        unsigned int  sep_host_gpr1_mask      : 1;  /* bit[12]   : SEP_HOST_GPR1 interrupt mask. */
        unsigned int  sep_host_gpr2_mask      : 1;  /* bit[13]   : SEP_HOST_GPR2 interrupt mask. */
        unsigned int  sep_host_gpr3_mask      : 1;  /* bit[14]   : SEP_HOST_GPR3 interrupt mask. */
        unsigned int  sep_host_gpr4_mask      : 1;  /* bit[15]   : SEP_HOST_GPR4 interrupt mask. */
        unsigned int  sep_host_gpr5_mask      : 1;  /* bit[16]   : SEP_HOST_GPR5 interrupt mask. */
        unsigned int  sep_host_gpr6_mask      : 1;  /* bit[17]   : SEP_HOST_GPR6 interrupt mask. */
        unsigned int  sep_host_gpr7_mask      : 1;  /* bit[18]   : SEP_HOST_GPR7 interrupt mask. */
        unsigned int  dscrptr_watermark_mask0 : 1;  /* bit[19]   : Descriptor queue0 watermark interrupt mask. */
        unsigned int  dscrptr_watermark_mask1 : 1;  /* bit[20]   : Descriptor queue1 (if exists) watermark interrupt mask. */
        unsigned int  reserved_1              : 1;  /* bit[21]   : reserved */
        unsigned int  hash_cmp_error_mask     : 1;  /* bit[22]   : Hash compare error interrupt mask. */
        unsigned int  axim_comp_mask          : 1;  /* bit[23]   : AXI master completion interrupt mask. */
        unsigned int  reserved_2              : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_SECENG_P_HOST_IMR_UNION;
#endif
#define SOC_SECENG_P_HOST_IMR_dscrptr_completion_mask_START  (2)
#define SOC_SECENG_P_HOST_IMR_dscrptr_completion_mask_END    (2)
#define SOC_SECENG_P_HOST_IMR_host_sram_vio_mask_START       (3)
#define SOC_SECENG_P_HOST_IMR_host_sram_vio_mask_END         (3)
#define SOC_SECENG_P_HOST_IMR_sram_to_din_mask_START         (4)
#define SOC_SECENG_P_HOST_IMR_sram_to_din_mask_END           (4)
#define SOC_SECENG_P_HOST_IMR_dout_to_sram_mask_START        (5)
#define SOC_SECENG_P_HOST_IMR_dout_to_sram_mask_END          (5)
#define SOC_SECENG_P_HOST_IMR_mem_to_din_mask_START          (6)
#define SOC_SECENG_P_HOST_IMR_mem_to_din_mask_END            (6)
#define SOC_SECENG_P_HOST_IMR_dout_to_mem_mask_START         (7)
#define SOC_SECENG_P_HOST_IMR_dout_to_mem_mask_END           (7)
#define SOC_SECENG_P_HOST_IMR_axi_err_mask_START             (8)
#define SOC_SECENG_P_HOST_IMR_axi_err_mask_END               (8)
#define SOC_SECENG_P_HOST_IMR_pka_exp_mask_START             (9)
#define SOC_SECENG_P_HOST_IMR_pka_exp_mask_END               (9)
#define SOC_SECENG_P_HOST_IMR_rng_int_mask_START             (10)
#define SOC_SECENG_P_HOST_IMR_rng_int_mask_END               (10)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr0_mask_START       (11)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr0_mask_END         (11)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr1_mask_START       (12)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr1_mask_END         (12)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr2_mask_START       (13)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr2_mask_END         (13)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr3_mask_START       (14)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr3_mask_END         (14)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr4_mask_START       (15)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr4_mask_END         (15)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr5_mask_START       (16)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr5_mask_END         (16)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr6_mask_START       (17)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr6_mask_END         (17)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr7_mask_START       (18)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr7_mask_END         (18)
#define SOC_SECENG_P_HOST_IMR_dscrptr_watermark_mask0_START  (19)
#define SOC_SECENG_P_HOST_IMR_dscrptr_watermark_mask0_END    (19)
#define SOC_SECENG_P_HOST_IMR_dscrptr_watermark_mask1_START  (20)
#define SOC_SECENG_P_HOST_IMR_dscrptr_watermark_mask1_END    (20)
#define SOC_SECENG_P_HOST_IMR_hash_cmp_error_mask_START      (22)
#define SOC_SECENG_P_HOST_IMR_hash_cmp_error_mask_END        (22)
#define SOC_SECENG_P_HOST_IMR_axim_comp_mask_START           (23)
#define SOC_SECENG_P_HOST_IMR_axim_comp_mask_END             (23)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_ICR_UNION
 �ṹ˵��  : HOST_ICR �Ĵ����ṹ���塣��ַƫ����:0x00A08����ֵ:0x00000000�����:32
 �Ĵ���˵��: Interrupt Clear Register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                     : 2;  /* bit[0-1]  : reserved */
        unsigned int  dscrptr_completion_clear       : 1;  /* bit[2]    : Descriptor completion interrupt clear. */
        unsigned int  host_sram_vio_clear            : 1;  /* bit[3]    : Host SRAM violation interrupt clear. */
        unsigned int  sram_to_din_clear              : 1;  /* bit[4]    : DIN SRAM DMA done interrupt clear. */
        unsigned int  dout_to_sram_clear             : 1;  /* bit[5]    : DOUT SRAM DMA done interrupt clear. */
        unsigned int  mem_to_din_clear               : 1;  /* bit[6]    : DIN MEM DMA done interrupt clear. */
        unsigned int  dout_to_mem_clear              : 1;  /* bit[7]    : DOUT MEM DMA done interrupt clear. */
        unsigned int  axi_err_clear                  : 1;  /* bit[8]    : AXI error interrupt clear. */
        unsigned int  pka_exp_clear                  : 1;  /* bit[9]    : PKA end of operation interrupt clear. */
        unsigned int  rng_int_clear                  : 1;  /* bit[10]   : RNG interrupt clear. */
        unsigned int  sep_host_gpr0_clear            : 1;  /* bit[11]   : SEP_HOST_GPR0 interrupt clear. */
        unsigned int  sep_host_gpr1_clear            : 1;  /* bit[12]   : SEP_HOST_GPR1 interrupt clear. */
        unsigned int  sep_host_gpr2_clear            : 1;  /* bit[13]   : SEP_HOST_GPR2 interrupt clear. */
        unsigned int  sep_host_gpr3_clear            : 1;  /* bit[14]   : SEP_HOST_GPR3 interrupt clear. */
        unsigned int  sep_host_gpr4_clear            : 1;  /* bit[15]   : SEP_HOST_GPR4 interrupt clear. */
        unsigned int  sep_host_gpr5_clear            : 1;  /* bit[16]   : SEP_HOST_GPR5 interrupt clear. */
        unsigned int  sep_host_gpr6_clear            : 1;  /* bit[17]   : SEP_HOST_GPR6 interrupt clear. */
        unsigned int  sep_host_gpr7_clear            : 1;  /* bit[18]   : SEP_HOST_GPR7 interrupt clear. */
        unsigned int  dscrptr_watermark_queue0_clear : 1;  /* bit[19]   : Descriptor queue0 watermark interrupt clear. */
        unsigned int  dscrptr_watermark_queue1_clear : 1;  /* bit[20]   : Descriptor queue1 (if exists) watermark interrupt clear. */
        unsigned int  reserved_1                     : 1;  /* bit[21]   : reserved */
        unsigned int  hash_cmp_error_clear           : 1;  /* bit[22]   : Hash compare error interrupt clear. */
        unsigned int  axim_comp_clear                : 1;  /* bit[23]   : AXI master completion interrupt clear. */
        unsigned int  reserved_2                     : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_SECENG_P_HOST_ICR_UNION;
#endif
#define SOC_SECENG_P_HOST_ICR_dscrptr_completion_clear_START        (2)
#define SOC_SECENG_P_HOST_ICR_dscrptr_completion_clear_END          (2)
#define SOC_SECENG_P_HOST_ICR_host_sram_vio_clear_START             (3)
#define SOC_SECENG_P_HOST_ICR_host_sram_vio_clear_END               (3)
#define SOC_SECENG_P_HOST_ICR_sram_to_din_clear_START               (4)
#define SOC_SECENG_P_HOST_ICR_sram_to_din_clear_END                 (4)
#define SOC_SECENG_P_HOST_ICR_dout_to_sram_clear_START              (5)
#define SOC_SECENG_P_HOST_ICR_dout_to_sram_clear_END                (5)
#define SOC_SECENG_P_HOST_ICR_mem_to_din_clear_START                (6)
#define SOC_SECENG_P_HOST_ICR_mem_to_din_clear_END                  (6)
#define SOC_SECENG_P_HOST_ICR_dout_to_mem_clear_START               (7)
#define SOC_SECENG_P_HOST_ICR_dout_to_mem_clear_END                 (7)
#define SOC_SECENG_P_HOST_ICR_axi_err_clear_START                   (8)
#define SOC_SECENG_P_HOST_ICR_axi_err_clear_END                     (8)
#define SOC_SECENG_P_HOST_ICR_pka_exp_clear_START                   (9)
#define SOC_SECENG_P_HOST_ICR_pka_exp_clear_END                     (9)
#define SOC_SECENG_P_HOST_ICR_rng_int_clear_START                   (10)
#define SOC_SECENG_P_HOST_ICR_rng_int_clear_END                     (10)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr0_clear_START             (11)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr0_clear_END               (11)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr1_clear_START             (12)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr1_clear_END               (12)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr2_clear_START             (13)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr2_clear_END               (13)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr3_clear_START             (14)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr3_clear_END               (14)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr4_clear_START             (15)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr4_clear_END               (15)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr5_clear_START             (16)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr5_clear_END               (16)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr6_clear_START             (17)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr6_clear_END               (17)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr7_clear_START             (18)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr7_clear_END               (18)
#define SOC_SECENG_P_HOST_ICR_dscrptr_watermark_queue0_clear_START  (19)
#define SOC_SECENG_P_HOST_ICR_dscrptr_watermark_queue0_clear_END    (19)
#define SOC_SECENG_P_HOST_ICR_dscrptr_watermark_queue1_clear_START  (20)
#define SOC_SECENG_P_HOST_ICR_dscrptr_watermark_queue1_clear_END    (20)
#define SOC_SECENG_P_HOST_ICR_hash_cmp_error_clear_START            (22)
#define SOC_SECENG_P_HOST_ICR_hash_cmp_error_clear_END              (22)
#define SOC_SECENG_P_HOST_ICR_axim_comp_clear_START                 (23)
#define SOC_SECENG_P_HOST_ICR_axim_comp_clear_END                   (23)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_SEP_SRAM_THRESHOLD_UNION
 �ṹ˵��  : HOST_SEP_SRAM_THRESHOLD �Ĵ����ṹ���塣��ַƫ����:0x00A10����ֵ:0x00000FFF�����:32
 �Ĵ���˵��: Host cannot access the SRAM up to this threshold level (address) . NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sep_sram_threshold : 12; /* bit[0-11] : SRAM_THRESHOLD MAX_SRAM_ADDRESS is the last address of the SRAM. */
        unsigned int  reserved           : 20; /* bit[12-31]: reserved */
    } reg;
} SOC_SECENG_P_HOST_SEP_SRAM_THRESHOLD_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_SRAM_THRESHOLD_sep_sram_threshold_START  (0)
#define SOC_SECENG_P_HOST_SEP_SRAM_THRESHOLD_sep_sram_threshold_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_SEP_BUSY_UNION
 �ṹ˵��  : HOST_SEP_BUSY �Ĵ����ṹ���塣��ַƫ����:0x00A14����ֵ:0x00000001�����:32
 �Ĵ���˵��: SEP_BUSY indication. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sep_busy : 1;  /* bit[0]   : This field reflects the status of the SEP_BUSY read-only register. */
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_HOST_SEP_BUSY_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_BUSY_sep_busy_START  (0)
#define SOC_SECENG_P_HOST_SEP_BUSY_sep_busy_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_SEP_SW_MONITOR_UNION
 �ṹ˵��  : HOST_SEP_SW_MONITOR �Ĵ����ṹ���塣��ַƫ����:0x00A20����ֵ:0x00000000�����:32
 �Ĵ���˵��: SEP_SW_MONITOR Register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sep_sw_monitor : 32; /* bit[0-31]: The SEP SW monitor. This value is written by the SEP, and can be read by the Host */
    } reg;
} SOC_SECENG_P_HOST_SEP_SW_MONITOR_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_SW_MONITOR_sep_sw_monitor_START  (0)
#define SOC_SECENG_P_HOST_SEP_SW_MONITOR_sep_sw_monitor_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_CC_SW_RST_UNION
 �ṹ˵��  : HOST_CC_SW_RST �Ĵ����ṹ���塣��ַƫ����:0x00A40����ֵ:0x00000000�����:32
 �Ĵ���˵��: Entire CryptoCell software reset NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cc_sw_rst_req   : 1;  /* bit[0]   : Writing '1' generates a SW_RST to the entire CryptoCell. Reset occurs only after AXIM and AXIS is inactive (axim/s_sysreq is generated). Reset takes about 4 core clocks */
        unsigned int  cc_sw_rst_force : 1;  /* bit[1]   : Writing '1' generates a SW_RST to the entire CryptoCell. the reset takes about 4 core clocks */
        unsigned int  axis_sysreq     : 1;  /* bit[2]   : Writing '1' sets the AXIS into wait state, in which pending transactions are completed, but no new transactions are served. Writing '0' is not supported by the host - since no new transactions are served. */
        unsigned int  axim_sysreq     : 1;  /* bit[3]   : Writing '1' sets the AXIM into wait state, in which pending transactions are completed, but no new transactions are served. Writing '0' sets the AXIM back to normal state. */
        unsigned int  reserved        : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_SECENG_P_HOST_CC_SW_RST_UNION;
#endif
#define SOC_SECENG_P_HOST_CC_SW_RST_cc_sw_rst_req_START    (0)
#define SOC_SECENG_P_HOST_CC_SW_RST_cc_sw_rst_req_END      (0)
#define SOC_SECENG_P_HOST_CC_SW_RST_cc_sw_rst_force_START  (1)
#define SOC_SECENG_P_HOST_CC_SW_RST_cc_sw_rst_force_END    (1)
#define SOC_SECENG_P_HOST_CC_SW_RST_axis_sysreq_START      (2)
#define SOC_SECENG_P_HOST_CC_SW_RST_axis_sysreq_END        (2)
#define SOC_SECENG_P_HOST_CC_SW_RST_axim_sysreq_START      (3)
#define SOC_SECENG_P_HOST_CC_SW_RST_axim_sysreq_END        (3)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_SEP_HOST_GPR0_UNION
 �ṹ˵��  : HOST_SEP_HOST_GPR0 �Ĵ����ṹ���塣��ַƫ����:0x00A80����ֵ:0x00000000�����:32
 �Ĵ���˵��: sep-host communication register #0. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sep_host_gpr0 : 32; /* bit[0-31]: SEP to Host GPR 0. When the SEP writes to this register SEP_HOST_GPR0_int is generated towards the host */
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR0_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR0_sep_host_gpr0_START  (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR0_sep_host_gpr0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_HOST_SEP_GPR0_UNION
 �ṹ˵��  : HOST_HOST_SEP_GPR0 �Ĵ����ṹ���塣��ַƫ����:0x00A84����ֵ:0x00000000�����:32
 �Ĵ���˵��: host-sep communication register #0. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_sep_gpr0 : 32; /* bit[0-31]: Host to SEP GPR 0. When the Host writes to this register HOST_SEP_GPR0_int is generated towards the SEP */
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR0_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR0_host_sep_gpr0_START  (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR0_host_sep_gpr0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_SEP_HOST_GPR1_UNION
 �ṹ˵��  : HOST_SEP_HOST_GPR1 �Ĵ����ṹ���塣��ַƫ����:0x00A88����ֵ:0x00000000�����:32
 �Ĵ���˵��: sep-host communication register #1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sep_host_gpr1 : 32; /* bit[0-31]: SEP to Host GPR 1. When the SEP writes to this register SEP_HOST_GPR1_int is generated towards the host */
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR1_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR1_sep_host_gpr1_START  (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR1_sep_host_gpr1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_HOST_SEP_GPR1_UNION
 �ṹ˵��  : HOST_HOST_SEP_GPR1 �Ĵ����ṹ���塣��ַƫ����:0x00A8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: host-sep communication register #1 NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_sep_gpr1 : 32; /* bit[0-31]: Host to SEP GPR 1. When the Host writes to this register HOST_SEP_GPR1_int is generated towards the SEP */
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR1_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR1_host_sep_gpr1_START  (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR1_host_sep_gpr1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_SEP_HOST_GPR2_UNION
 �ṹ˵��  : HOST_SEP_HOST_GPR2 �Ĵ����ṹ���塣��ַƫ����:0x00A90����ֵ:0x00000000�����:32
 �Ĵ���˵��: sep-host communication register #2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sep_host_gpr2 : 32; /* bit[0-31]: SEP to Host GPR 2. When the SEP writes to this register SEP_HOST_GPR2_int is generated towards the Host */
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR2_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR2_sep_host_gpr2_START  (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR2_sep_host_gpr2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_HOST_SEP_GPR2_UNION
 �ṹ˵��  : HOST_HOST_SEP_GPR2 �Ĵ����ṹ���塣��ַƫ����:0x00A94����ֵ:0x00000000�����:32
 �Ĵ���˵��: host-sep communication register #2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_sep_gpr2 : 32; /* bit[0-31]: Host to SEP GPR 2. When the Host writes to this register HOST_SEP_GPR2_int is generated towards the SEP */
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR2_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR2_host_sep_gpr2_START  (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR2_host_sep_gpr2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_SEP_HOST_GPR3_UNION
 �ṹ˵��  : HOST_SEP_HOST_GPR3 �Ĵ����ṹ���塣��ַƫ����:0x00A98����ֵ:0x00000000�����:32
 �Ĵ���˵��: sep-host communication register #3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sep_host_gpr3 : 32; /* bit[0-31]: SEP to Host GPR 3. When the SEP writes to this register SEP_HOST_GPR3_int is generated towards the Host */
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR3_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR3_sep_host_gpr3_START  (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR3_sep_host_gpr3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_HOST_SEP_GPR3_UNION
 �ṹ˵��  : HOST_HOST_SEP_GPR3 �Ĵ����ṹ���塣��ַƫ����:0x00A9C����ֵ:0x00000000�����:32
 �Ĵ���˵��: host-sep communication register #3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_sep_gpr3 : 32; /* bit[0-31]: Host to SEP GPR 3. When the Host writes to this register HOST_SEP_GPR3_int is generated towards the SEP */
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR3_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR3_host_sep_gpr3_START  (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR3_host_sep_gpr3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_SEP_HOST_GPR4_UNION
 �ṹ˵��  : HOST_SEP_HOST_GPR4 �Ĵ����ṹ���塣��ַƫ����:0x00AA0����ֵ:0x00000000�����:32
 �Ĵ���˵��: sep-host communication register #4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sep_host_gpr4 : 32; /* bit[0-31]: SEP to Host GPR 4. When the SEP writes to this register SEP_HOST_GPR4_int is generated towards the Host */
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR4_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR4_sep_host_gpr4_START  (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR4_sep_host_gpr4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_HOST_SEP_GPR4_UNION
 �ṹ˵��  : HOST_HOST_SEP_GPR4 �Ĵ����ṹ���塣��ַƫ����:0x00AA4����ֵ:0x00000000�����:32
 �Ĵ���˵��: host-sep communication register #4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_sep_gpr4 : 32; /* bit[0-31]: Host to SEP GPR 4. When the Host writes to this register HOST_SEP_GPR4_int is generated towards the SEP */
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR4_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR4_host_sep_gpr4_START  (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR4_host_sep_gpr4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_SEP_HOST_GPR5_UNION
 �ṹ˵��  : HOST_SEP_HOST_GPR5 �Ĵ����ṹ���塣��ַƫ����:0x00AA8����ֵ:0x00000000�����:32
 �Ĵ���˵��: sep-host communication register #5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sep_host_gpr5 : 32; /* bit[0-31]: SEP to Host GPR 5. When the SEP writes to this register SEP_HOST_GPR5_int is generated towards the Host */
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR5_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR5_sep_host_gpr5_START  (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR5_sep_host_gpr5_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_HOST_SEP_GPR5_UNION
 �ṹ˵��  : HOST_HOST_SEP_GPR5 �Ĵ����ṹ���塣��ַƫ����:0x00AAC����ֵ:0x00000000�����:32
 �Ĵ���˵��: host-sep communication register #5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_sep_gpr5 : 32; /* bit[0-31]: Host to SEP GPR 5. When the Host writes to this register HOST_SEP_GPR5_int is generated towards the SEP */
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR5_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR5_host_sep_gpr5_START  (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR5_host_sep_gpr5_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_SEP_HOST_GPR6_UNION
 �ṹ˵��  : HOST_SEP_HOST_GPR6 �Ĵ����ṹ���塣��ַƫ����:0x00AB0����ֵ:0x00000000�����:32
 �Ĵ���˵��: sep-host communication register #6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sep_host_gpr6 : 32; /* bit[0-31]: SEP to Host GPR 6. When the SEP writes to this register SEP_HOST_GPR6_int is generated towards the Host */
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR6_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR6_sep_host_gpr6_START  (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR6_sep_host_gpr6_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_HOST_SEP_GPR6_UNION
 �ṹ˵��  : HOST_HOST_SEP_GPR6 �Ĵ����ṹ���塣��ַƫ����:0x00AB4����ֵ:0x00000000�����:32
 �Ĵ���˵��: host-sep communication register #6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_sep_gpr6 : 32; /* bit[0-31]: Host to SEP GPR 6. When the Host writes to this register HOST_SEP_GPR6_int is generated towards the SEP */
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR6_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR6_host_sep_gpr6_START  (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR6_host_sep_gpr6_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_SEP_HOST_GPR7_UNION
 �ṹ˵��  : HOST_SEP_HOST_GPR7 �Ĵ����ṹ���塣��ַƫ����:0x00AB8����ֵ:0x00000000�����:32
 �Ĵ���˵��: sep-host communication register #7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sep_host_gpr7 : 32; /* bit[0-31]: SEP to Host GPR 7. When the SEP writes to this register SEP_HOST_GPR7_int is generated towards the Host */
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR7_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR7_sep_host_gpr7_START  (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR7_sep_host_gpr7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_HOST_SEP_GPR7_UNION
 �ṹ˵��  : HOST_HOST_SEP_GPR7 �Ĵ����ṹ���塣��ַƫ����:0x00ABC����ֵ:0x00000000�����:32
 �Ĵ���˵��: host-sep communication register #7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_sep_gpr7 : 32; /* bit[0-31]: Host to SEP GPR 7. When the Host writes to this register HOST_SEP_GPR7_int is generated towards the SEP */
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR7_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR7_host_sep_gpr7_START  (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR7_host_sep_gpr7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_CC_SIGNATURE_UNION
 �ṹ˵��  : HOST_CC_SIGNATURE �Ĵ����ṹ���塣��ַƫ����:0x00AC8����ֵ:0xDCC63000�����:32
 �Ĵ���˵��: CryptoCell signature
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_cc_signature : 32; /* bit[0-31]: This register reflects the SEP boot status and CryptoCell availability to Host:
                                                            �� Register value is 0x0cc63000 if SEP boot is on-going
                                                            �� Register value is 0xdcc63000 once SEP boot is done */
    } reg;
} SOC_SECENG_P_HOST_CC_SIGNATURE_UNION;
#endif
#define SOC_SECENG_P_HOST_CC_SIGNATURE_host_cc_signature_START  (0)
#define SOC_SECENG_P_HOST_CC_SIGNATURE_host_cc_signature_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_HOST_ENDIAN_UNION
 �ṹ˵��  : HOST_HOST_ENDIAN �Ĵ����ṹ���塣��ַƫ����:0x00AD0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Host endianness configuration register. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0       : 2;  /* bit[0-1]  : reserved */
        unsigned int  din_dd_end       : 1;  /* bit[2]    : Control the endainess of DD. 
                                                            Default little */
        unsigned int  din_dma_end      : 1;  /* bit[3]    : Control the endainess of DMA. 
                                                            Default little */
        unsigned int  reserved_1       : 2;  /* bit[4-5]  : reserved */
        unsigned int  dout_dd_end      : 1;  /* bit[6]    : Control the endainess of DD. 
                                                            Default little */
        unsigned int  dout_dma_end     : 1;  /* bit[7]    : Control the endainess of DMA. 
                                                            Default little */
        unsigned int  intenal_word_end : 8;  /* bit[8-15] : Control the endainess of DMA. 
                                                            Default little */
        unsigned int  reserved_2       : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_HOST_HOST_ENDIAN_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_ENDIAN_din_dd_end_START        (2)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_din_dd_end_END          (2)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_din_dma_end_START       (3)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_din_dma_end_END         (3)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_dout_dd_end_START       (6)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_dout_dd_end_END         (6)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_dout_dma_end_START      (7)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_dout_dma_end_END        (7)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_intenal_word_end_START  (8)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_intenal_word_end_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_IRQ_TIMER_INIT_VAL_UNION
 �ṹ˵��  : HOST_IRQ_TIMER_INIT_VAL �Ĵ����ṹ���塣��ַƫ����:0x0AD4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Host endianness configuration register. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_irq_timer_init_val : 24; /* bit[0-23] : This field determines the amount of delay cycles on the IRQ to the Host. When this field is set to zero, the delay mechanism is disabled */
        unsigned int  reserved                : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_SECENG_P_HOST_IRQ_TIMER_INIT_VAL_UNION;
#endif
#define SOC_SECENG_P_HOST_IRQ_TIMER_INIT_VAL_host_irq_timer_init_val_START  (0)
#define SOC_SECENG_P_HOST_IRQ_TIMER_INIT_VAL_host_irq_timer_init_val_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_HOST_VERSION_UNION
 �ṹ˵��  : HOST_VERSION �Ĵ����ṹ���塣��ַƫ����:0x0AD8����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the HW version. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_version : 32; /* bit[0-31]: HW version the same value as on CRY_REG_FILE */
    } reg;
} SOC_SECENG_P_HOST_VERSION_UNION;
#endif
#define SOC_SECENG_P_HOST_VERSION_host_version_START  (0)
#define SOC_SECENG_P_HOST_VERSION_host_version_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHT0_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT0 �Ĵ����ṹ���塣��ַƫ����:0x00B00����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT0_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT0_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT0_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHT1_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT1 �Ĵ����ṹ���塣��ַƫ����:0x00B04����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT1_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT1_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT1_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHT2_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT2 �Ĵ����ṹ���塣��ַƫ����:0x00B08����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT2_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT2_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT2_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHT3_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT3 �Ĵ����ṹ���塣��ַƫ����:0x00B0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT3_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT3_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT3_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHT4_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT4 �Ĵ����ṹ���塣��ַƫ����:0x00B10����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT4_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT4_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT4_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHT5_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT5 �Ĵ����ṹ���塣��ַƫ����:0x00B14����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT5_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT5_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT5_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHT8_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT8 �Ĵ����ṹ���塣��ַƫ����:0x00B20����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT8_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT8_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT8_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHT9_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT9 �Ĵ����ṹ���塣��ַƫ����:0x00B24����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=9
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT9_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT9_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT9_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHT10_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT10 �Ĵ����ṹ���塣��ַƫ����:0x00B28����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=10
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT10_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT10_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT10_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHT11_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHT11 �Ĵ����ṹ���塣��ַƫ����:0x00B2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=11
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT11_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT11_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT11_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHTLAST0_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST0 �Ĵ����ṹ���塣��ַƫ����:0x00B40����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=0 and last indication bit set.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST0_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST0_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST0_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHTLAST1_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST1 �Ĵ����ṹ���塣��ַƫ����:0x00B44����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=1 and last indication bit set.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST1_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST1_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST1_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHTLAST2_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST2 �Ĵ����ṹ���塣��ַƫ����:0x00B48����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=2 and last indication bit set.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST2_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST2_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST2_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHTLAST3_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST3 �Ĵ����ṹ���塣��ַƫ����:0x00B4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=3 and last indication bit set.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST3_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST3_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST3_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHTLAST4_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST4 �Ĵ����ṹ���塣��ַƫ����:0x00B50����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=4 and last indication bit set.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST4_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST4_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST4_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHTLAST5_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST5 �Ĵ����ṹ���塣��ַƫ����:0x00B54����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=5 and last indication bit set.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST5_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST5_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST5_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST8 �Ĵ����ṹ���塣��ַƫ����:0x00B60����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=8 and last indication bit set.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  unused       : 24; /* bit[8-31]:  */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_inflightcntr_END    (7)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_unused_START        (8)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_unused_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHTLAST9_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST9 �Ĵ����ṹ���塣��ַƫ����:0x00B64����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=9 and last indication bit set.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST9_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST9_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST9_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHTLAST10_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST10 �Ĵ����ṹ���塣��ַƫ����:0x00B68����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=10 and last indication bit set.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST10_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST10_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST10_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_INFLIGHTLAST11_UNION
 �ṹ˵��  : AXIM_MON_INFLIGHTLAST11 �Ĵ����ṹ���塣��ַƫ����:0x00B6C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of uncompleted write transactions, with ID=11 and last indication bit set.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inflightcntr : 8;  /* bit[0-7] : number of non-completed write transactions for last bursts */
        unsigned int  reserved     : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST11_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST11_inflightcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST11_inflightcntr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_PIDTABLE0_UNION
 �ṹ˵��  : AXIM_PIDTABLE0 �Ĵ����ṹ���塣��ַƫ����:0x00B70����ֵ:0x00004000�����:32
 �Ĵ���˵��: This register holds the status of AXI port 0.
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
        unsigned int  reserved    : 17; /* bit[15-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_PIDTABLE0_UNION;
#endif
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_broken1_START  (0)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_broken1_END    (0)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_broken2_START  (1)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_broken2_END    (1)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_oscntr_START   (2)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_oscntr_END     (9)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_id_START       (10)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_id_END         (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_PIDTABLE1_UNION
 �ṹ˵��  : AXIM_PIDTABLE1 �Ĵ����ṹ���塣��ַƫ����:0x00B74����ֵ:0x00004000�����:32
 �Ĵ���˵��: This register holds the status of AXI port 1.
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
        unsigned int  reserved    : 17; /* bit[15-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_PIDTABLE1_UNION;
#endif
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_broken1_START  (0)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_broken1_END    (0)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_broken2_START  (1)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_broken2_END    (1)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_oscntr_START   (2)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_oscntr_END     (9)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_id_START       (10)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_id_END         (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_PIDTABLE2_UNION
 �ṹ˵��  : AXIM_PIDTABLE2 �Ĵ����ṹ���塣��ַƫ����:0x00B78����ֵ:0x00004000�����:32
 �Ĵ���˵��: This register holds the status of AXI port 2.
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
        unsigned int  reserved    : 17; /* bit[15-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_PIDTABLE2_UNION;
#endif
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_broken1_START  (0)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_broken1_END    (0)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_broken2_START  (1)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_broken2_END    (1)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_oscntr_START   (2)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_oscntr_END     (9)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_id_START       (10)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_id_END         (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_PIDTABLE3_UNION
 �ṹ˵��  : AXIM_PIDTABLE3 �Ĵ����ṹ���塣��ַƫ����:0x00B7C����ֵ:0x00004000�����:32
 �Ĵ���˵��: This register holds the status of AXI port 3.
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
        unsigned int  reserved    : 17; /* bit[15-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_PIDTABLE3_UNION;
#endif
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_broken1_START  (0)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_broken1_END    (0)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_broken2_START  (1)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_broken2_END    (1)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_oscntr_START   (2)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_oscntr_END     (9)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_id_START       (10)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_id_END         (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_COMP0_UNION
 �ṹ˵��  : AXIM_MON_COMP0 �Ĵ����ṹ���塣��ַƫ����:0x00B80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=0.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 0 */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP0_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP0_complastcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_COMP0_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_COMP1_UNION
 �ṹ˵��  : AXIM_MON_COMP1 �Ĵ����ṹ���塣��ַƫ����:0x00B84����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 1 */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP1_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP1_complastcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_COMP1_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_COMP2_UNION
 �ṹ˵��  : AXIM_MON_COMP2 �Ĵ����ṹ���塣��ַƫ����:0x00B88����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=2.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 2 */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP2_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP2_complastcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_COMP2_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_COMP3_UNION
 �ṹ˵��  : AXIM_MON_COMP3 �Ĵ����ṹ���塣��ַƫ����:0x00B8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=3.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 3 */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP3_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP3_complastcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_COMP3_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_COMP4_UNION
 �ṹ˵��  : AXIM_MON_COMP4 �Ĵ����ṹ���塣��ַƫ����:0x00B90����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=4.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 4 */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP4_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP4_complastcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_COMP4_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_COMP5_UNION
 �ṹ˵��  : AXIM_MON_COMP5 �Ĵ����ṹ���塣��ַƫ����:0x00B94����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=5.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 5 */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP5_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP5_complastcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_COMP5_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_COMP8_UNION
 �ṹ˵��  : AXIM_MON_COMP8 �Ĵ����ṹ���塣��ַƫ����:0x00BA0����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=8.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 8 */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP8_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP8_complastcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_COMP8_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_COMP9_UNION
 �ṹ˵��  : AXIM_MON_COMP9 �Ĵ����ṹ���塣��ַƫ����:0x00BA4����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=9.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 9 */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP9_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP9_complastcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_COMP9_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_COMP10_UNION
 �ṹ˵��  : AXIM_MON_COMP10 �Ĵ����ṹ���塣��ַƫ����:0x00BA8����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=10.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 10 */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP10_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP10_complastcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_COMP10_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_COMP11_UNION
 �ṹ˵��  : AXIM_MON_COMP11 �Ĵ����ṹ���塣��ַƫ����:0x00BAC����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the completion counter of the transaction with ID=11.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  complastcntr : 16; /* bit[0-15] : Number of completed write transactions for last bursts (BREADY && BVALID) for bid == 11 */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP11_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP11_complastcntr_START  (0)
#define SOC_SECENG_P_AXIM_MON_COMP11_complastcntr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_RMAX_UNION
 �ṹ˵��  : AXIM_MON_RMAX �Ĵ����ṹ���塣��ַƫ����:0x00BB4����ֵ:0x00000000�����:32
 �Ĵ���˵��: max latency for read transactions
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rmax : 32; /* bit[0-31]: measured max latency in core_clk/64 clock cycles from last read */
    } reg;
} SOC_SECENG_P_AXIM_MON_RMAX_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_RMAX_rmax_START  (0)
#define SOC_SECENG_P_AXIM_MON_RMAX_rmax_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_RMIN_UNION
 �ṹ˵��  : AXIM_MON_RMIN �Ĵ����ṹ���塣��ַƫ����:0x00BB8����ֵ:0x000007FF�����:32
 �Ĵ���˵��: min latency for read transactions
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rmin : 32; /* bit[0-31]: measured min latency in core_clk/64 clock cycles from last read */
    } reg;
} SOC_SECENG_P_AXIM_MON_RMIN_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_RMIN_rmin_START  (0)
#define SOC_SECENG_P_AXIM_MON_RMIN_rmin_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_WMAX_UNION
 �ṹ˵��  : AXIM_MON_WMAX �Ĵ����ṹ���塣��ַƫ����:0x00BBC����ֵ:0x00000000�����:32
 �Ĵ���˵��: max latency for write transactions
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wmax : 32; /* bit[0-31]: measured max latency in core_clk/64 clock cycles from last write */
    } reg;
} SOC_SECENG_P_AXIM_MON_WMAX_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_WMAX_wmax_START  (0)
#define SOC_SECENG_P_AXIM_MON_WMAX_wmax_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_WMIN_UNION
 �ṹ˵��  : AXIM_MON_WMIN �Ĵ����ṹ���塣��ַƫ����:0x00BC0����ֵ:0x000007FF�����:32
 �Ĵ���˵��: min latency for write transactions
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wmin : 32; /* bit[0-31]: measured min latency in core_clk/64 clock cycles from last write */
    } reg;
} SOC_SECENG_P_AXIM_MON_WMIN_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_WMIN_wmin_START  (0)
#define SOC_SECENG_P_AXIM_MON_WMIN_wmin_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_MON_ERR_UNION
 �ṹ˵��  : AXIM_MON_ERR �Ĵ����ṹ���塣��ַƫ����:0x00BC4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Error information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bresp    : 2;  /* bit[0-1]  : BRESP of the captured error */
        unsigned int  bid      : 4;  /* bit[2-5]  : BID that caused the error */
        unsigned int  reserved_0: 10; /* bit[6-15] : reserved */
        unsigned int  rresp    : 2;  /* bit[16-17]: RRESP of the captured errro */
        unsigned int  rid      : 4;  /* bit[18-21]: RID that caused the error */
        unsigned int  reserved_1: 10; /* bit[22-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_MON_ERR_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_ERR_bresp_START     (0)
#define SOC_SECENG_P_AXIM_MON_ERR_bresp_END       (1)
#define SOC_SECENG_P_AXIM_MON_ERR_bid_START       (2)
#define SOC_SECENG_P_AXIM_MON_ERR_bid_END         (5)
#define SOC_SECENG_P_AXIM_MON_ERR_rresp_START     (16)
#define SOC_SECENG_P_AXIM_MON_ERR_rresp_END       (17)
#define SOC_SECENG_P_AXIM_MON_ERR_rid_START       (18)
#define SOC_SECENG_P_AXIM_MON_ERR_rid_END         (21)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_RDSTAT_UNION
 �ṹ˵��  : AXIM_RDSTAT �Ĵ����ṹ���塣��ַƫ����:0x00BC8����ֵ:0x00000000�����:32
 �Ĵ���˵��: read channel status
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  oscntr   : 4;  /* bit[0-3] : total number of outstanding bursts */
        unsigned int  reserved : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_RDSTAT_UNION;
#endif
#define SOC_SECENG_P_AXIM_RDSTAT_oscntr_START    (0)
#define SOC_SECENG_P_AXIM_RDSTAT_oscntr_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_RLATENCY_UNION
 �ṹ˵��  : AXIM_RLATENCY �Ĵ����ṹ���塣��ַƫ����:0x00BD0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Accumulated read latency
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rlatency : 32; /* bit[0-31]: accumulated rd latency , correlated with RBURST */
    } reg;
} SOC_SECENG_P_AXIM_RLATENCY_UNION;
#endif
#define SOC_SECENG_P_AXIM_RLATENCY_rlatency_START  (0)
#define SOC_SECENG_P_AXIM_RLATENCY_rlatency_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_RBURST_UNION
 �ṹ˵��  : AXIM_RBURST �Ĵ����ṹ���塣��ַƫ����:0x00BD4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Accumulated read bursts
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rburst : 32; /* bit[0-31]: accumulated rd bursts */
    } reg;
} SOC_SECENG_P_AXIM_RBURST_UNION;
#endif
#define SOC_SECENG_P_AXIM_RBURST_rburst_START  (0)
#define SOC_SECENG_P_AXIM_RBURST_rburst_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_WLATENCY_UNION
 �ṹ˵��  : AXIM_WLATENCY �Ĵ����ṹ���塣��ַƫ����:0x00BD8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Accumulated write latency
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wlatency : 32; /* bit[0-31]: accumulated wr latency , correlated with WBURST */
    } reg;
} SOC_SECENG_P_AXIM_WLATENCY_UNION;
#endif
#define SOC_SECENG_P_AXIM_WLATENCY_wlatency_START  (0)
#define SOC_SECENG_P_AXIM_WLATENCY_wlatency_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_WBURST_UNION
 �ṹ˵��  : AXIM_WBURST �Ĵ����ṹ���塣��ַƫ����:0x00BDC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Accumulated write bursts
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wburst : 32; /* bit[0-31]: accumulated wr bursts */
    } reg;
} SOC_SECENG_P_AXIM_WBURST_UNION;
#endif
#define SOC_SECENG_P_AXIM_WBURST_wburst_START  (0)
#define SOC_SECENG_P_AXIM_WBURST_wburst_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_CACHETYPE_CFG_UNION
 �ṹ˵��  : AXIM_CACHETYPE_CFG �Ĵ����ṹ���塣��ַƫ����:0x00BE0����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXI master cache-type configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0 : 8;  /* bit[0-7]  : reserved */
        unsigned int  dd_arcache : 4;  /* bit[8-11] : Control the ARCACHE value of the direct data. */
        unsigned int  reserved_1 : 12; /* bit[12-23]: reserved */
        unsigned int  dd_awcache : 4;  /* bit[24-27]: Control the AWCACHE value of the direct data. */
        unsigned int  reserved_2 : 4;  /* bit[28-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_CACHETYPE_CFG_UNION;
#endif
#define SOC_SECENG_P_AXIM_CACHETYPE_CFG_dd_arcache_START  (8)
#define SOC_SECENG_P_AXIM_CACHETYPE_CFG_dd_arcache_END    (11)
#define SOC_SECENG_P_AXIM_CACHETYPE_CFG_dd_awcache_START  (24)
#define SOC_SECENG_P_AXIM_CACHETYPE_CFG_dd_awcache_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_PROT_CFG_UNION
 �ṹ˵��  : AXIM_PROT_CFG �Ĵ����ṹ���塣��ַƫ����:0x00BE4����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXIM Protection field configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 4;  /* bit[0-3]  : reserved */
        unsigned int  dd_arprot : 1;  /* bit[4]    : Control the ARPROT value of the direct data. */
        unsigned int  reserved_1: 7;  /* bit[5-11] : reserved */
        unsigned int  dd_awprot : 1;  /* bit[12]   : Control the AWPROT value of the direct data. */
        unsigned int  reserved_2: 19; /* bit[13-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_PROT_CFG_UNION;
#endif
#define SOC_SECENG_P_AXIM_PROT_CFG_dd_arprot_START  (4)
#define SOC_SECENG_P_AXIM_PROT_CFG_dd_arprot_END    (4)
#define SOC_SECENG_P_AXIM_PROT_CFG_dd_awprot_START  (12)
#define SOC_SECENG_P_AXIM_PROT_CFG_dd_awprot_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_CFG1_UNION
 �ṹ˵��  : AXIM_CFG1 �Ĵ����ṹ���塣��ַƫ����:0x00BE8����ֵ:0x001F0087�����:32
 �Ĵ���˵��: AXI master configuration
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
        unsigned int  brespmask         : 1;  /* bit[4]    : Masking interrupt sources: BRESP_ERR */
        unsigned int  rrespmask         : 1;  /* bit[5]    : Masking interrupt sources: RRESP_ERR */
        unsigned int  infltmask         : 1;  /* bit[6]    : Masking interrupt sources: INFLIGHT_ERR */
        unsigned int  ompmask           : 1;  /* bit[7]    : Masking interrupt sources: completion counter incremented - if both compmask and interrupt sources are unmasked, completion event has the highest priority. */
        unsigned int  reserved_0        : 8;  /* bit[8-15] : reserved */
        unsigned int  accum_limit       : 5;  /* bit[16-20]: Limit number of outstanding write transactions. AXIM stops issuing new requests after crossing this value. */
        unsigned int  reserved_1        : 11; /* bit[21-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_CFG1_UNION;
#endif
#define SOC_SECENG_P_AXIM_CFG1_rd_after_wr_stall_START  (0)
#define SOC_SECENG_P_AXIM_CFG1_rd_after_wr_stall_END    (3)
#define SOC_SECENG_P_AXIM_CFG1_brespmask_START          (4)
#define SOC_SECENG_P_AXIM_CFG1_brespmask_END            (4)
#define SOC_SECENG_P_AXIM_CFG1_rrespmask_START          (5)
#define SOC_SECENG_P_AXIM_CFG1_rrespmask_END            (5)
#define SOC_SECENG_P_AXIM_CFG1_infltmask_START          (6)
#define SOC_SECENG_P_AXIM_CFG1_infltmask_END            (6)
#define SOC_SECENG_P_AXIM_CFG1_ompmask_START            (7)
#define SOC_SECENG_P_AXIM_CFG1_ompmask_END              (7)
#define SOC_SECENG_P_AXIM_CFG1_accum_limit_START        (16)
#define SOC_SECENG_P_AXIM_CFG1_accum_limit_END          (20)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_ACE_CONST_UNION
 �ṹ˵��  : AXIM_ACE_CONST �Ĵ����ṹ���塣��ַƫ����:0x0BEC����ֵ:0x11FC100A�����:32
 �Ĵ���˵��: 
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
        unsigned int  reserved            : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_ACE_CONST_UNION;
#endif
#define SOC_SECENG_P_AXIM_ACE_CONST_ardomain_START             (0)
#define SOC_SECENG_P_AXIM_ACE_CONST_ardomain_END               (1)
#define SOC_SECENG_P_AXIM_ACE_CONST_awdomain_START             (2)
#define SOC_SECENG_P_AXIM_ACE_CONST_awdomain_END               (3)
#define SOC_SECENG_P_AXIM_ACE_CONST_arbar_START                (4)
#define SOC_SECENG_P_AXIM_ACE_CONST_arbar_END                  (5)
#define SOC_SECENG_P_AXIM_ACE_CONST_awbar_START                (6)
#define SOC_SECENG_P_AXIM_ACE_CONST_awbar_END                  (7)
#define SOC_SECENG_P_AXIM_ACE_CONST_arsnoop_START              (8)
#define SOC_SECENG_P_AXIM_ACE_CONST_arsnoop_END                (11)
#define SOC_SECENG_P_AXIM_ACE_CONST_awsnoop_not_aligned_START  (12)
#define SOC_SECENG_P_AXIM_ACE_CONST_awsnoop_not_aligned_END    (14)
#define SOC_SECENG_P_AXIM_ACE_CONST_awsnoop_aligned_START      (15)
#define SOC_SECENG_P_AXIM_ACE_CONST_awsnoop_aligned_END        (17)
#define SOC_SECENG_P_AXIM_ACE_CONST_awaddr_not_masked_START    (18)
#define SOC_SECENG_P_AXIM_ACE_CONST_awaddr_not_masked_END      (24)
#define SOC_SECENG_P_AXIM_ACE_CONST_awlen_val_START            (25)
#define SOC_SECENG_P_AXIM_ACE_CONST_awlen_val_END              (28)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXIM_CACHE_PARAMS_UNION
 �ṹ˵��  : AXIM_CACHE_PARAMS �Ĵ����ṹ���塣��ַƫ����:0x0BF0����ֵ:0x00000777�����:32
 �Ĵ���˵��: AXI master configuration for DMA
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
        unsigned int  reserved     : 20; /* bit[12-31]: reserved */
    } reg;
} SOC_SECENG_P_AXIM_CACHE_PARAMS_UNION;
#endif
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_awcache_last_START  (0)
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_awcache_last_END    (3)
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_awcache_START       (4)
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_awcache_END         (7)
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_arcache_START       (8)
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_arcache_END         (11)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_ADDR_AXIM_CTRL_UNION
 �ṹ˵��  : ADDR_AXIM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0BF4����ֵ:0x00000002�����:32
 �Ĵ���˵��: Control AXI master.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_axim_ctrl : 4;  /* bit[0-3] : Limit outstanding number of read transactions. */
        unsigned int  reserved       : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_SECENG_P_ADDR_AXIM_CTRL_UNION;
#endif
#define SOC_SECENG_P_ADDR_AXIM_CTRL_addr_axim_ctrl_START  (0)
#define SOC_SECENG_P_ADDR_AXIM_CTRL_addr_axim_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DIN_BUFFER_UNION
 �ṹ˵��  : DIN_BUFFER �Ĵ����ṹ���塣��ַƫ����:0x00C00����ֵ:0x00000000�����:32
 �Ĵ���˵��: This address can be used by the CPU to write data directly to the DIN buffer to be sent to engines.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  din_buffer_data : 32; /* bit[0-31]: This register is mapped into 8 addresses in order to enable a CPU burst. */
    } reg;
} SOC_SECENG_P_DIN_BUFFER_UNION;
#endif
#define SOC_SECENG_P_DIN_BUFFER_din_buffer_data_START  (0)
#define SOC_SECENG_P_DIN_BUFFER_din_buffer_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DIN_MEM_DMA_BUSY_UNION
 �ṹ˵��  : DIN_MEM_DMA_BUSY �Ĵ����ṹ���塣��ַƫ����:0x00C20����ֵ:0x00000000�����:32
 �Ĵ���˵��: Indicates whether memory (AXI) source DMA (DIN) is busy.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  din_mem_dma_busy : 1;  /* bit[0]   : DIN memory DMA busy:
                                                           1'b1: busy.
                                                           1'b0: not busy.  */
        unsigned int  reserved         : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DIN_MEM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_P_DIN_MEM_DMA_BUSY_din_mem_dma_busy_START  (0)
#define SOC_SECENG_P_DIN_MEM_DMA_BUSY_din_mem_dma_busy_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_SRC_LLI_SRAM_ADDR_UNION
 �ṹ˵��  : SRC_LLI_SRAM_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00C24����ֵ:0x00000000�����:32
 �Ĵ���˵��: Location of LLI table located in the SRAM. in SINGLE/MULTI_LLI mode, writing to this register triggers the DMA. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_lli_sram_addr : 15; /* bit[0-14] : source LLI table address in SRAM */
        unsigned int  reserved          : 17; /* bit[15-31]: reserved */
    } reg;
} SOC_SECENG_P_SRC_LLI_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_P_SRC_LLI_SRAM_ADDR_src_lli_sram_addr_START  (0)
#define SOC_SECENG_P_SRC_LLI_SRAM_ADDR_src_lli_sram_addr_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_SRC_LLI_WORD0_UNION
 �ṹ˵��  : SRC_LLI_WORD0 �Ĵ����ṹ���塣��ַƫ����:0x00C28����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used in direct LLI mode - holds the location of the data source in the memory (AXI).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_lli_word0 : 32; /* bit[0-31]: Source address within memory */
    } reg;
} SOC_SECENG_P_SRC_LLI_WORD0_UNION;
#endif
#define SOC_SECENG_P_SRC_LLI_WORD0_src_lli_word0_START  (0)
#define SOC_SECENG_P_SRC_LLI_WORD0_src_lli_word0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_SRC_LLI_WORD1_UNION
 �ṹ˵��  : SRC_LLI_WORD1 �Ĵ����ṹ���塣��ַƫ����:0x00C2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used in direct LLI mode - holds the number of bytes to be read from the memory (AXI). Writing to this register triggers the DMA. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
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
} SOC_SECENG_P_SRC_LLI_WORD1_UNION;
#endif
#define SOC_SECENG_P_SRC_LLI_WORD1_bytes_num_START  (0)
#define SOC_SECENG_P_SRC_LLI_WORD1_bytes_num_END    (29)
#define SOC_SECENG_P_SRC_LLI_WORD1_first_START      (30)
#define SOC_SECENG_P_SRC_LLI_WORD1_first_END        (30)
#define SOC_SECENG_P_SRC_LLI_WORD1_last_START       (31)
#define SOC_SECENG_P_SRC_LLI_WORD1_last_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_SRAM_SRC_ADDR_UNION
 �ṹ˵��  : SRAM_SRC_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00C30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Location of data (start address) to be read from SRAM. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_source : 32; /* bit[0-31]: SRAM source base address of data */
    } reg;
} SOC_SECENG_P_SRAM_SRC_ADDR_UNION;
#endif
#define SOC_SECENG_P_SRAM_SRC_ADDR_sram_source_START  (0)
#define SOC_SECENG_P_SRAM_SRC_ADDR_sram_source_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DIN_SRAM_BYTES_LEN_UNION
 �ṹ˵��  : DIN_SRAM_BYTES_LEN �Ĵ����ṹ���塣��ַƫ����:0x00C34����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the size of the data (in bytes) to be read from the SRAM. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bytes_len : 32; /* bit[0-31]: Size of data to read from SRAM (bytes). 
                                                    This is the trigger to the SRAM SRC DMA */
    } reg;
} SOC_SECENG_P_DIN_SRAM_BYTES_LEN_UNION;
#endif
#define SOC_SECENG_P_DIN_SRAM_BYTES_LEN_bytes_len_START  (0)
#define SOC_SECENG_P_DIN_SRAM_BYTES_LEN_bytes_len_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DIN_SRAM_DMA_BUSY_UNION
 �ṹ˵��  : DIN_SRAM_DMA_BUSY �Ĵ����ṹ���塣��ַƫ����:0x00C38����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the status of the SRAM DMA DIN.
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
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DIN_SRAM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_P_DIN_SRAM_DMA_BUSY_busy_START      (0)
#define SOC_SECENG_P_DIN_SRAM_DMA_BUSY_busy_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DIN_SRAM_ENDIANNESS_UNION
 �ṹ˵��  : DIN_SRAM_ENDIANNESS �Ĵ����ṹ���塣��ַƫ����:0x00C3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines the endianness of the DIN interface to SRAM.
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
        unsigned int  reserved            : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DIN_SRAM_ENDIANNESS_UNION;
#endif
#define SOC_SECENG_P_DIN_SRAM_ENDIANNESS_sram_din_endianness_START  (0)
#define SOC_SECENG_P_DIN_SRAM_ENDIANNESS_sram_din_endianness_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXI_CPU_DIN_PARAMS_UNION
 �ṹ˵��  : AXI_CPU_DIN_PARAMS �Ĵ����ṹ���塣��ַƫ����:0x00C40����ֵ:0x00000028�����:32
 �Ĵ���˵��: This register holds RDID and PROT when using the CPU.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdid     : 4;  /* bit[0-3]  : AXI transaction ID when using the CPU (compatibility mode). */
        unsigned int  reserved_0: 4;  /* bit[4-7]  : reserved */
        unsigned int  prot     : 2;  /* bit[8-9]  : AXI transaction PROT when using the CPU (compatibility mode). */
        unsigned int  reserved_1: 22; /* bit[10-31]: reserved */
    } reg;
} SOC_SECENG_P_AXI_CPU_DIN_PARAMS_UNION;
#endif
#define SOC_SECENG_P_AXI_CPU_DIN_PARAMS_rdid_START      (0)
#define SOC_SECENG_P_AXI_CPU_DIN_PARAMS_rdid_END        (3)
#define SOC_SECENG_P_AXI_CPU_DIN_PARAMS_prot_START      (8)
#define SOC_SECENG_P_AXI_CPU_DIN_PARAMS_prot_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DIN_SW_RESET_UNION
 �ṹ˵��  : DIN_SW_RESET �Ĵ����ṹ���塣��ַƫ����:0x00C44����ֵ:0x00000000�����:32
 �Ĵ���˵��: DIN software reset.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  kick_sw_reset : 1;  /* bit[0]   : RESET the DIN */
        unsigned int  reserved      : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DIN_SW_RESET_UNION;
#endif
#define SOC_SECENG_P_DIN_SW_RESET_kick_sw_reset_START  (0)
#define SOC_SECENG_P_DIN_SW_RESET_kick_sw_reset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DIN_CPU_DATA_SIZE_UNION
 �ṹ˵��  : DIN_CPU_DATA_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0C48����ֵ:0x00000000�����:32
 �Ĵ���˵��: Data path to DIN is OTF
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_din_size : 16; /* bit[0-15] : When using CPU direct write to the DIN buffer, the size of input data in bytes should be written to this register. */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_DIN_CPU_DATA_SIZE_UNION;
#endif
#define SOC_SECENG_P_DIN_CPU_DATA_SIZE_cpu_din_size_START  (0)
#define SOC_SECENG_P_DIN_CPU_DATA_SIZE_cpu_din_size_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_WRITE_ALIGN_LAST_UNION
 �ṹ˵��  : WRITE_ALIGN_LAST �Ĵ����ṹ���塣��ַƫ����:0x00C4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Indication that the next write from the CPU is the last one. This is needed only when the data size is NOT modulo 4 (e.g. HASH padding).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  last     : 1;  /* bit[0]   : 1 - next data from CPU is the last word */
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_WRITE_ALIGN_LAST_UNION;
#endif
#define SOC_SECENG_P_WRITE_ALIGN_LAST_last_START      (0)
#define SOC_SECENG_P_WRITE_ALIGN_LAST_last_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_FIFO_IN_EMPTY_UNION
 �ṹ˵��  : FIFO_IN_EMPTY �Ĵ����ṹ���塣��ַƫ����:0x00C50����ֵ:0x00000001�����:32
 �Ĵ���˵��: DIN FIFO empty indication
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  empty    : 1;  /* bit[0]   : 1 - fifo empty */
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_FIFO_IN_EMPTY_UNION;
#endif
#define SOC_SECENG_P_FIFO_IN_EMPTY_empty_START     (0)
#define SOC_SECENG_P_FIFO_IN_EMPTY_empty_END       (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DISABLE_OUTSTD_REQ_UNION
 �ṹ˵��  : DISABLE_OUTSTD_REQ �Ĵ����ṹ���塣��ַƫ����:0x00C54����ֵ:0x00000000�����:32
 �Ĵ���˵��: Disables the outstanding DIN request
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
        unsigned int  reserved           : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DISABLE_OUTSTD_REQ_UNION;
#endif
#define SOC_SECENG_P_DISABLE_OUTSTD_REQ_disable_outstd_req_START  (0)
#define SOC_SECENG_P_DISABLE_OUTSTD_REQ_disable_outstd_req_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DIN_FIFO_RST_PNTR_UNION
 �ṹ˵��  : DIN_FIFO_RST_PNTR �Ĵ����ṹ���塣��ַƫ����:0x00C58����ֵ:0x00000000�����:32
 �Ĵ���˵��: Writing to this register resets the DIN_FIFO pointers.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst      : 1;  /* bit[0]   : writing any value to this address will reset the DIN_FIFO pointers */
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DIN_FIFO_RST_PNTR_UNION;
#endif
#define SOC_SECENG_P_DIN_FIFO_RST_PNTR_rst_START       (0)
#define SOC_SECENG_P_DIN_FIFO_RST_PNTR_rst_END         (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DOUT_BUFFER_UNION
 �ṹ˵��  : DOUT_BUFFER �Ĵ����ṹ���塣��ַƫ����:0x00D00����ֵ:0x00000000�����:32
 �Ĵ���˵��: Cryptographic result - CPU can directly access it. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_buffer_data : 32; /* bit[0-31]: This address can be used by the CPU to read data directly from the DOUT buffer. */
    } reg;
} SOC_SECENG_P_DOUT_BUFFER_UNION;
#endif
#define SOC_SECENG_P_DOUT_BUFFER_dout_buffer_data_START  (0)
#define SOC_SECENG_P_DOUT_BUFFER_dout_buffer_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DOUT_MEM_DMA_BUSY_UNION
 �ṹ˵��  : DOUT_MEM_DMA_BUSY �Ĵ����ṹ���塣��ַƫ����:0x00D20����ֵ:0x00000000�����:32
 �Ĵ���˵��: DOUT memory DMA busy - Indicates that memory (AXI) destination DMA (DOUT) is busy,
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
        unsigned int  reserved          : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DOUT_MEM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_P_DOUT_MEM_DMA_BUSY_dout_mem_dma_busy_START  (0)
#define SOC_SECENG_P_DOUT_MEM_DMA_BUSY_dout_mem_dma_busy_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DST_LLI_SRAM_ADDR_UNION
 �ṹ˵��  : DST_LLI_SRAM_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00D24����ֵ:0x0000001E�����:32
 �Ĵ���˵��: This register holds the destination LLI table address in SRAM. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst_lli_sram_addr : 15; /* bit[0-14] : The destination LLI table address in SRAM */
        unsigned int  reserved          : 17; /* bit[15-31]: reserved */
    } reg;
} SOC_SECENG_P_DST_LLI_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_P_DST_LLI_SRAM_ADDR_dst_lli_sram_addr_START  (0)
#define SOC_SECENG_P_DST_LLI_SRAM_ADDR_dst_lli_sram_addr_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DST_LLI_WORD0_UNION
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
} SOC_SECENG_P_DST_LLI_WORD0_UNION;
#endif
#define SOC_SECENG_P_DST_LLI_WORD0_dst_lli_word0_START  (0)
#define SOC_SECENG_P_DST_LLI_WORD0_dst_lli_word0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DST_LLI_WORD1_UNION
 �ṹ˵��  : DST_LLI_WORD1 �Ĵ����ṹ���塣��ַƫ����:0x00D2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used in direct LLI mode - holds the number of bytes to be written to the memory (AXI).
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
} SOC_SECENG_P_DST_LLI_WORD1_UNION;
#endif
#define SOC_SECENG_P_DST_LLI_WORD1_bytes_num_START  (0)
#define SOC_SECENG_P_DST_LLI_WORD1_bytes_num_END    (29)
#define SOC_SECENG_P_DST_LLI_WORD1_first_START      (30)
#define SOC_SECENG_P_DST_LLI_WORD1_first_END        (30)
#define SOC_SECENG_P_DST_LLI_WORD1_last_START       (31)
#define SOC_SECENG_P_DST_LLI_WORD1_last_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_SRAM_DEST_ADDR_UNION
 �ṹ˵��  : SRAM_DEST_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00D30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Location of result to be sent to in SRAM NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_dest : 32; /* bit[0-31]: SRAM destination base address for data */
    } reg;
} SOC_SECENG_P_SRAM_DEST_ADDR_UNION;
#endif
#define SOC_SECENG_P_SRAM_DEST_ADDR_sram_dest_START  (0)
#define SOC_SECENG_P_SRAM_DEST_ADDR_sram_dest_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DOUT_SRAM_BYTES_LEN_UNION
 �ṹ˵��  : DOUT_SRAM_BYTES_LEN �Ĵ����ṹ���塣��ַƫ����:0x00D34����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the size of the data (in bytes) to be written to the SRAM. NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bytes_len : 32; /* bit[0-31]: Size of data to write to SRAM (bytes). This is the trigger to the SRAM DST DMA */
    } reg;
} SOC_SECENG_P_DOUT_SRAM_BYTES_LEN_UNION;
#endif
#define SOC_SECENG_P_DOUT_SRAM_BYTES_LEN_bytes_len_START  (0)
#define SOC_SECENG_P_DOUT_SRAM_BYTES_LEN_bytes_len_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DOUT_SRAM_DMA_BUSY_UNION
 �ṹ˵��  : DOUT_SRAM_DMA_BUSY �Ĵ����ṹ���塣��ַƫ����:0x00D38����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the status of the SRAM DMA DOUT.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  busy     : 1;  /* bit[0]   : 0 - all data was written to SRAM 
                                                   1 - DOUT SRAM DMA busy */
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DOUT_SRAM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_P_DOUT_SRAM_DMA_BUSY_busy_START      (0)
#define SOC_SECENG_P_DOUT_SRAM_DMA_BUSY_busy_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DOUT_SRAM_ENDIANNESS_UNION
 �ṹ˵��  : DOUT_SRAM_ENDIANNESS �Ĵ����ṹ���塣��ַƫ����:0x00D3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines the endianness of the DOUT interface from SRAM.
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
        unsigned int  reserved             : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DOUT_SRAM_ENDIANNESS_UNION;
#endif
#define SOC_SECENG_P_DOUT_SRAM_ENDIANNESS_dout_sram_endianness_START  (0)
#define SOC_SECENG_P_DOUT_SRAM_ENDIANNESS_dout_sram_endianness_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_READ_ALIGN_LAST_UNION
 �ṹ˵��  : READ_ALIGN_LAST �Ĵ����ṹ���塣��ַƫ����:0x00D44����ֵ:0x00000000�����:32
 �Ĵ���˵��: Indication that the next read from the CPU is the last one. This is needed only when the data size is NOT modulo 4 (e.g. HASH padding).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  last     : 1;  /* bit[0]   : 1 - Flush the read aligner content (used for reading the last data). */
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_READ_ALIGN_LAST_UNION;
#endif
#define SOC_SECENG_P_READ_ALIGN_LAST_last_START      (0)
#define SOC_SECENG_P_READ_ALIGN_LAST_last_END        (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DOUT_FIFO_EMPTY_UNION
 �ṹ˵��  : DOUT_FIFO_EMPTY �Ĵ����ṹ���塣��ַƫ����:0x00D50����ֵ:0x00000001�����:32
 �Ĵ���˵��: DOUT_FIFO_EMPTY Register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_fifo_empty : 1;  /* bit[0]   : 1'b0 - DOUT fifo is not empty 
                                                          1'b1 - DOUT fifo is empty */
        unsigned int  reserved        : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DOUT_FIFO_EMPTY_UNION;
#endif
#define SOC_SECENG_P_DOUT_FIFO_EMPTY_dout_fifo_empty_START  (0)
#define SOC_SECENG_P_DOUT_FIFO_EMPTY_dout_fifo_empty_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_UNION
 �ṹ˵��  : AXI_CPU_DOUT_PARAMS �Ĵ����ṹ���塣��ַƫ����:0x00D54����ֵ:0x00008770�����:32
 �Ĵ���˵��: AXI_CPU_DOUT_PARAMS Register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cache_type       : 4;  /* bit[0-3]  : Cache type of AXI transaction when using CPU */
        unsigned int  reserved_0       : 8;  /* bit[4-11] : reserved */
        unsigned int  wrid             : 4;  /* bit[12-15]: AXI transaction ID when using CPU. */
        unsigned int  prot             : 2;  /* bit[16-17]: AXI transaction PROT when using CPU. */
        unsigned int  force_cpu_params : 1;  /* bit[18]   : The CPU params also apply to descriptor output transactions. */
        unsigned int  reserved_1       : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_UNION;
#endif
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_cache_type_START        (0)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_cache_type_END          (3)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_wrid_START              (12)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_wrid_END                (15)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_prot_START              (16)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_prot_END                (17)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_force_cpu_params_START  (18)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_force_cpu_params_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DOUT_SW_RESET_UNION
 �ṹ˵��  : DOUT_SW_RESET �Ĵ����ṹ���塣��ַƫ����:0x00D58����ֵ:0x00000000�����:32
 �Ĵ���˵��: Software reset for DOUT.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_sw_reset : 1;  /* bit[0]   : Resets the DOUT. */
        unsigned int  reserved      : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DOUT_SW_RESET_UNION;
#endif
#define SOC_SECENG_P_DOUT_SW_RESET_dout_sw_reset_START  (0)
#define SOC_SECENG_P_DOUT_SW_RESET_dout_sw_reset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_UNION
 �ṹ˵��  : DSCRPTR_COMPLETION_COUNTER0 �Ĵ����ṹ���塣��ַƫ����:0x00E00����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register counts the number of completed descriptors in which the ACK_NEEDED field equals 1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  completion_counter : 6;  /* bit[0-5] : This counter counts completed descriptors in which the ACK_NEEDED field equals 1. */
        unsigned int  overflow_counter   : 1;  /* bit[6]   : If this bit is set, completion counter 0 overflowed. */
        unsigned int  reserved           : 25; /* bit[7-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_completion_counter_START  (0)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_completion_counter_END    (5)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_overflow_counter_START    (6)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_overflow_counter_END      (6)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_UNION
 �ṹ˵��  : DSCRPTR_COMPLETION_COUNTER1 �Ĵ����ṹ���塣��ַƫ����:0x00E04����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register counts the number of completed descriptors in which the ACK_NEEDED field equals 2.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  completion_counter : 6;  /* bit[0-5] : This counter counts completed descriptors in which the ACK_NEEDED field equals 2. */
        unsigned int  overflow_counter   : 1;  /* bit[6]   : If this bit is set, completion counter 1 overflowed. */
        unsigned int  reserved           : 25; /* bit[7-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_completion_counter_START  (0)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_completion_counter_END    (5)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_overflow_counter_START    (6)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_overflow_counter_END      (6)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_COMPLETION_STATUS_UNION
 �ṹ˵��  : DSCRPTR_COMPLETION_STATUS �Ĵ����ṹ���塣��ַƫ����:0x00E3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the status of the completion counters.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  completion_counter_status : 2;  /* bit[0-1] : Each bit in this register indicates, for the corresponding completion counter, whether it was incremented since the last time it was read (a read from a counter resets the relevant bit). */
        unsigned int  reserved                  : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_COMPLETION_STATUS_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_COMPLETION_STATUS_completion_counter_status_START  (0)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_STATUS_completion_counter_status_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_SW_RESET_UNION
 �ṹ˵��  : DSCRPTR_SW_RESET �Ĵ����ṹ���塣��ַƫ����:0x00E40����ֵ:0x00000000�����:32
 �Ĵ���˵��: Software reset for descriptors.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dscrptr_sw_reset : 1;  /* bit[0]   : Descriptor reset. */
        unsigned int  reserved         : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_SW_RESET_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_SW_RESET_dscrptr_sw_reset_START  (0)
#define SOC_SECENG_P_DSCRPTR_SW_RESET_dscrptr_sw_reset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_DEBUG_MODE_UNION
 �ṹ˵��  : DSCRPTR_DEBUG_MODE �Ĵ����ṹ���塣��ַƫ����:0x00E4C����ֵ:0x00000001�����:32
 �Ĵ���˵��: This register enables the use of special descriptors
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dscrptr_debug_mode : 1;  /* bit[0]   : Enables using the special descriptors (the descriptor that performs a general Host write). */
        unsigned int  reserved           : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_DEBUG_MODE_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_DEBUG_MODE_dscrptr_debug_mode_START  (0)
#define SOC_SECENG_P_DSCRPTR_DEBUG_MODE_dscrptr_debug_mode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_CNT_UNION
 �ṹ˵��  : DSCRPTR_FILTER_DROPPED_CNT �Ĵ����ṹ���塣��ַƫ����:0x00E50����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register counts the number of descriptors dropped by queue filtered module, after not complying with the restrictions.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dscrptr_filter_drop_count : 32; /* bit[0-31]: Counts the number of descriptors dropped by queue filtered module, after not complying with the restrictions. */
    } reg;
} SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_CNT_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_CNT_dscrptr_filter_drop_count_START  (0)
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_CNT_dscrptr_filter_drop_count_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_MEM_CNT_UNION
 �ṹ˵��  : DSCRPTR_FILTER_DROPPED_MEM_CNT �Ĵ����ṹ���塣��ַƫ����:0x00E54����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register counts the number of descriptors dropped by queue filtered module, after not complying with the restrictions and the destination is system memory.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dscrptr_filter_drop_mem_count : 32; /* bit[0-31]: Counts the number of descriptors dropped by queue filtered module, after not complying with the restrictions and the destination is system memory. */
    } reg;
} SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_MEM_CNT_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_MEM_CNT_dscrptr_filter_drop_mem_count_START  (0)
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_MEM_CNT_dscrptr_filter_drop_mem_count_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_FILTER_DEBUG_UNION
 �ṹ˵��  : DSCRPTR_FILTER_DEBUG �Ĵ����ṹ���塣��ַƫ����:0x00E58����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds which restriction failed to be complied with.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dscrptr_debug_mode : 8;  /* bit[0-7] : Holds the restriction that failed in the active dropped descriptor:
                                                             �� 8'h0 - the ns restriction failed.
                                                             �� 8'h1 - the DMA mode restriction failed.
                                                             �� 8'h2 - the data flow restriction failed.
                                                             �� 8'h3 - the Secret key restriction failed.
                                                             �� 8'h4 - the DOUT_ADDRESS restriction failed.
                                                             �� 8'h5 - the DIN_ADDRESS restriction failed.
                                                             �� 8'h6 - the encrypt restriction failed
                                                             �� 8'h7 - the cipher mode restriction failed. */
        unsigned int  reserved           : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_FILTER_DEBUG_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_FILTER_DEBUG_dscrptr_debug_mode_START  (0)
#define SOC_SECENG_P_DSCRPTR_FILTER_DEBUG_dscrptr_debug_mode_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_UNION
 �ṹ˵��  : DSCRPTR_FILTER_DROPPED_ADDRESS �Ĵ����ṹ���塣��ַƫ����:0x00E5C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the address to which CryptoCell writes when descriptor does not comply with restriction.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dropped_address : 32; /* bit[0-31]: The address to which CryptoCell writes when descriptor does not comply with restriction. */
    } reg;
} SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_dropped_address_START  (0)
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_dropped_address_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE_SRAM_SIZE_UNION
 �ṹ˵��  : DSCRPTR_QUEUE_SRAM_SIZE �Ĵ����ṹ���塣��ַƫ����:0x00E60����ֵ:0x000002AA�����:32
 �Ĵ���˵��: This register holds the size of the SRAM queue.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_queue_size : 10; /* bit[0-9]  : Maximum number of descriptors the SRAM can hold. */
        unsigned int  reserved        : 22; /* bit[10-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE_SRAM_SIZE_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE_SRAM_SIZE_sram_queue_size_START  (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE_SRAM_SIZE_sram_queue_size_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_SINGLE_ADDR_EN_UNION
 �ṹ˵��  : DSCRPTR_SINGLE_ADDR_EN �Ĵ����ṹ���塣��ַƫ����:0x0E64����ֵ:0x00000001�����:32
 �Ĵ���˵��: This register enables the Host to write a descriptor using a single address.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dscrptr_single_addr_en : 1;  /* bit[0]   : This bit allows the Host to access a single address when writing descriptors. */
        unsigned int  reserved               : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_SINGLE_ADDR_EN_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_SINGLE_ADDR_EN_dscrptr_single_addr_en_START  (0)
#define SOC_SECENG_P_DSCRPTR_SINGLE_ADDR_EN_dscrptr_single_addr_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_MEASURE_CNTR_UNION
 �ṹ˵��  : DSCRPTR_MEASURE_CNTR �Ĵ����ṹ���塣��ַƫ����:0x0E68����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the number of cycles measured when using the special performance descriptor.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  measure_cntr : 32; /* bit[0-31]: Counter for descriptors performance measurement, start and finish with a special descriptor. Reading this register clears it. */
    } reg;
} SOC_SECENG_P_DSCRPTR_MEASURE_CNTR_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_MEASURE_CNTR_measure_cntr_START  (0)
#define SOC_SECENG_P_DSCRPTR_MEASURE_CNTR_measure_cntr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_UNION
 �ṹ˵��  : DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH �Ĵ����ṹ���塣��ַƫ����:0x0E6C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds the upper 16bits of the address to which CryptoCell writes when descriptor does not comply with restriction.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dropped_address_high : 16; /* bit[0-15] : The high 16bits address to which CryptoCell writes when descriptor is dropped. */
        unsigned int  reserved             : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_dropped_address_high_START  (0)
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_dropped_address_high_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE0_WORD0_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WORD0 �Ĵ����ṹ���塣��ַƫ����:0x00E80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word0 of the descriptor.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  din_dma_address : 32; /* bit[0-31]: If the 'DIN DMA mode' is:
                                                          �� SRAM - The address of the source DMA data in the SRAM
                                                          �� Direct LLI - The address of the source DMA data in the system RAM (through the AXI master)
                                                          �� MLLI - The address of the source LLI list in the SRAM. */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_WORD0_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD0_din_dma_address_START  (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD0_din_dma_address_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WORD1 �Ĵ����ṹ���塣��ַƫ����:0x00E84����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word1 of the descriptor.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  din_dma_mode     : 2;  /* bit[0-1]  : 2'h0 - NO DMA
                                                            �� 2'h1 - SRAM
                                                            �� 2'h2 - Direct LLI
                                                            �� 2'h3 - MLLI  */
        unsigned int  din_size         : 24; /* bit[2-25] : If the 'DIN DMA mode' is:
                                                            �� SRAM - The size of the data. Must to be multiple of 4bytes.
                                                            �� Direct LLI - The size of the data.
                                                            �� MLLI - This field is not used. */
        unsigned int  ns_bit           : 1;  /* bit[26]   : NS bit for current descriptor. */
        unsigned int  din_const_value  : 1;  /* bit[27]   : This bit forces DIN data to be constant value taken from the address field. When this bit is set, the DIN_DMA_MODE must be set to SRAM. */
        unsigned int  not_last         : 1;  /* bit[28]   : Not last descriptor - when this field is set, it signals that the last LLI of the current descriptor is not the last block of the AES. When using flow SRAM this bit indicates the endianness of SRAM to DIN interface. */
        unsigned int  reserved         : 1;  /* bit[29]   : reserved */
        unsigned int  din_virtual_host : 2;  /* bit[30-31]: Defines the ID of the Host in the current transaction (DIN). */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_dma_mode_START      (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_dma_mode_END        (1)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_size_START          (2)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_size_END            (25)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_ns_bit_START            (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_ns_bit_END              (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_const_value_START   (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_const_value_END     (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_not_last_START          (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_not_last_END            (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_virtual_host_START  (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_virtual_host_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE0_WORD2_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WORD2 �Ĵ����ṹ���塣��ַƫ����:0x00E88����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word2 of the descriptor.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_dma_address : 32; /* bit[0-31]: If the 'DOUT DMA mode' is:
                                                           �� SRAM - The address of the destination DMA data in the SRAM.
                                                           �� Direct LLI - The address of the destination DMA data in the system RAM (through the AXI master).
                                                           �� MLLI - The address of the destination LLI list in the SRAM.  */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_WORD2_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD2_dout_dma_address_START  (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD2_dout_dma_address_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WORD3 �Ĵ����ṹ���塣��ַƫ����:0x00E8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word3 of the descriptor.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_dma_mode     : 2;  /* bit[0-1]  : �� 2'h0 - NO DMA
                                                             �� 2'h1 - SRAM
                                                             �� 2'h2 - Direct LLI
                                                             �� 2'h3 - MLLI  */
        unsigned int  dout_size         : 24; /* bit[2-25] : If the 'DOUT DMA mode' is:
                                                             �� SRAM - The size of the data. Must to be multiple of 4bytes.
                                                             �� Direct LLI - The size of the data.
                                                             �� MLLI - This field is not used. */
        unsigned int  ns_bit            : 1;  /* bit[26]   : NS bit for current transaction. */
        unsigned int  dout_last_ind     : 1;  /* bit[27]   : Indicates last transaction. This AWCACHE value of the last AXI transaction is uncached and unbufferred. */
        unsigned int  reserved          : 1;  /* bit[28]   : reserved */
        unsigned int  hash_xor_bit      : 1;  /* bit[29]   : When this bit is set - the DIN data to HASH is xored with xor-register. */
        unsigned int  dout_virtual_host : 2;  /* bit[30-31]: Defines the ID of the Host for the current transaction (DOUT) */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_dma_mode_START      (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_dma_mode_END        (1)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_size_START          (2)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_size_END            (25)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_ns_bit_START             (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_ns_bit_END               (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_last_ind_START      (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_last_ind_END        (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_hash_xor_bit_START       (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_hash_xor_bit_END         (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_virtual_host_START  (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_virtual_host_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WORD4 �Ĵ����ṹ���塣��ַƫ����:0x00E90����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word4 of the descriptor.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data_flow_mode       : 6;  /* bit[0-5]  : �� 6'd0 - BYPASS
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
                                                                �� 6'd44 - SET-FLOW-ID */
        unsigned int  aes_sel_n_hash       : 1;  /* bit[6]    : if this bit is set, the entire HASH flow is done with AES_MAC. */
        unsigned int  aes_xor_crypto_key   : 1;  /* bit[7]    : When using AES, if this field is set, then the AES HW key is xored with the already loaded key. */
        unsigned int  ack_needed           : 2;  /* bit[8-9]  : �� 0x0 - no interrupt is triggered and no completion counter is incremented when the current descriptor is complete.
                                                                �� 0x1-0x2 - when the descriptor is complete, an interrupt is generated, and the relevant completion counter (according to the field value) is incremented.  */
        unsigned int  cipher_mode          : 4;  /* bit[10-13]: Value AES DES/TDES HASH/AESMAC
                                                                �� 0x0 ECB DES -ECB ECB MD5
                                                                �� 0x1 CBC DES- CBC CBC SHA1
                                                                �� 0x2 CTR TDES ECB N/A SHA256
                                                                �� 0x3 CBC -MAC TDES CBC SHA224
                                                                �� 0x4 XTS N/A SHA512
                                                                �� 0x5 XCBC MAC SHA384
                                                                �� 0x6 N/A
                                                                �� 0x7 CMAC
                                                                �� 0x8 CCM A
                                                                �� 0x9 CCM E
                                                                �� 0xA CCM P
                                                                �� 0xB CBC-CTS */
        unsigned int  cmac_size0           : 1;  /* bit[14]   : AES_CMAC_SIZE0 - kicks a CMAC operation with size zero. */
        unsigned int  cipher_do            : 2;  /* bit[15-16]: If the current flow is AES:
                                                                �� 2'd0 - AES INTERNAL KEY
                                                                �� 2'd1 - AES_SK - RKEK.
                                                                �� 2'd2 - AES_SK - PROV_KEY
                                                                �� 2'd3 - Reserved
                                                                If the current flow is HASH:
                                                                �� 2'd1 - Do hash padding */
        unsigned int  cipher_conf0         : 2;  /* bit[17-18]: If the current flow is AES:
                                                                �� 2'd0 - encrypt: AES mode is encrypt.
                                                                �� 2'd1 - decrypt: AES mode is decrypt.
                                                                �� 2'd2 - Reserved
                                                                �� 2'd1 - hash output compared - currently not supported.
                                                                �� 2'd2 - hash output is big-endianness (need for HMAC flow).  */
        unsigned int  cipher_conf1         : 1;  /* bit[19]   : If the current flow is AES �C Reserved.
                                                                If the current flow is HASH - 1'b1 - Enable hash padding in the end of block. */
        unsigned int  cipher_conf2         : 2;  /* bit[20-21]: If the current flow is AES - Reserved.
                                                                If the current flow is HASH:
                                                                �� 2'd0 �C do not truncate output
                                                                �� 2'd1 - truncate to 96bits
                                                                �� 2'd2 - truncate to 128bits */
        unsigned int  key_size             : 2;  /* bit[22-23]: If the Data flow mode is setup AES:
                                                                �� 2'h0 - AES KEY_SIZE = 128b
                                                                �� 2'h1 - AES KEY_SIZE = 192b
                                                                �� 2'h2 - AES KEY_SIZE = 256b
                                                                If the Data flow mode is setup DES:
                                                                �� 2'h0 - DES key number = 1 key
                                                                �� 2'h1 - DES key number = 2 keys
                                                                �� 2'h2 - DES key number = 3 keys */
        unsigned int  setup_operation      : 4;  /* bit[24-27]: �� 4'd0 - NONE
                                                                �� 4'd1 - Load state0 from DIN. The functionality of bit depend on the current flow.
                                                                �� AES - load IV from DIN.
                                                                �� DES - load IV.
                                                                �� HASH - load H (digest).
                                                                �� 4'd2 - Load state1 from DIN.
                                                                �� AES - load CTR.
                                                                �� HASH - load data to compare - not supported.
                                                                �� 4'd3 - Load state2 from DIN.
                                                                �� AES - - load prev_iv.
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
                                                                �� 4'd10 - write state2 to DOUT.
                                                                �� AES - store prev_iv.
                                                                �� 4'd11 - write state3 to DOUT.
                                                                �� AES - store xex_key. */
        unsigned int  din_sram_endianness  : 1;  /* bit[28]   : When using DIN source as SRAM, this bit swaps the bytes order of the word read from the SRAM and decreases the address after each word. */
        unsigned int  dout_sram_endianness : 1;  /* bit[29]   : When using DOUT destination as SRAM, this bit swaps the bytes order of the word written to SRAM and decreases the address after each word. */
        unsigned int  word_swap            : 1;  /* bit[30]   : Change the word order of all setup-finalize descriptor from the following engines AES, AES_MAC,DES. */
        unsigned int  bytes_swap           : 1;  /* bit[31]   : Change the bytes order of all setup-finalize descriptor from the following engines AES, AES_MAC,DES. */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_data_flow_mode_START        (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_data_flow_mode_END          (5)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_aes_sel_n_hash_START        (6)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_aes_sel_n_hash_END          (6)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_aes_xor_crypto_key_START    (7)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_aes_xor_crypto_key_END      (7)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_ack_needed_START            (8)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_ack_needed_END              (9)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_mode_START           (10)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_mode_END             (13)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cmac_size0_START            (14)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cmac_size0_END              (14)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_do_START             (15)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_do_END               (16)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_conf0_START          (17)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_conf0_END            (18)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_conf1_START          (19)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_conf1_END            (19)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_conf2_START          (20)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_conf2_END            (21)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_key_size_START              (22)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_key_size_END                (23)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_setup_operation_START       (24)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_setup_operation_END         (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_din_sram_endianness_START   (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_din_sram_endianness_END     (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_dout_sram_endianness_START  (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_dout_sram_endianness_END    (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_word_swap_START             (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_word_swap_END               (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_bytes_swap_START            (31)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_bytes_swap_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WORD5 �Ĵ����ṹ���塣��ַƫ����:0x00E94����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word5 of the descriptor.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  din_addr_high  : 16; /* bit[0-15] : When using 48-bits AXI address, this field defines the highest 16bits of the DIN address. */
        unsigned int  dout_addr_high : 16; /* bit[16-31]: When using 48-bits AXI address, this field defines the highest 16bits of the DOUT address. */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_din_addr_high_START   (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_din_addr_high_END     (15)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_dout_addr_high_START  (16)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_dout_addr_high_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE0_WATERMARK_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_WATERMARK �Ĵ����ṹ���塣��ַƫ����:0x00E98����ֵ:0x000003FF�����:32
 �Ĵ���˵��: This register holds the watermark value of descriptor queue0.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  watermark : 10; /* bit[0-9]  : queue 0 watermark: if the amount of empty entries exceeds the watermark level, an interrupt is issued. possible values 0-14. */
        unsigned int  reserved  : 22; /* bit[10-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_WATERMARK_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WATERMARK_watermark_START  (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WATERMARK_watermark_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE0_CONTENT_UNION
 �ṹ˵��  : DSCRPTR_QUEUE0_CONTENT �Ĵ����ṹ���塣��ַƫ����:0x00E9C����ֵ:0x000002AA�����:32
 �Ĵ���˵��: This register holds the number of empty entries in descriptor queue0.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  queue0_content : 10; /* bit[0-9]  : The number of empty entries in queue0 */
        unsigned int  reserved       : 22; /* bit[10-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_CONTENT_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_CONTENT_queue0_content_START  (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_CONTENT_queue0_content_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE1_WORD0_UNION
 �ṹ˵��  : DSCRPTR_QUEUE1_WORD0 �Ĵ����ṹ���塣��ַƫ����:0x00EA0����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word0 of descriptor queue1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  din_dma_address : 32; /* bit[0-31]: If the 'DIN DMA mode' is:
                                                          �� SRAM - The address of the source DMA data in the SRAM
                                                          �� Direct LLI - The address of the source DMA data in the system RAM (through the AXI master)
                                                          �� MLLI - The address of the source LLI list in the SRAM. */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_WORD0_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD0_din_dma_address_START  (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD0_din_dma_address_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_UNION
 �ṹ˵��  : DSCRPTR_QUEUE1_WORD1 �Ĵ����ṹ���塣��ַƫ����:0x00EA4����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word1 of descriptor queue1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  din_dma_mode     : 2;  /* bit[0-1]  : �� 2'h0 - NO DMA
                                                            �� 2'h1 - SRAM
                                                            �� 2'h2 - Direct LLI
                                                            �� 2'h3 - MLLI */
        unsigned int  din_size         : 24; /* bit[2-25] : If the 'DIN DMA mode' is:
                                                            �� SRAM - The size of the data. Must to be multiple of 4bytes.
                                                            �� Direct LLI - The size of the data.
                                                            �� MLLI - This field is not used. */
        unsigned int  ns_bit           : 1;  /* bit[26]   : NS bit for current descriptor. */
        unsigned int  din_const_value  : 1;  /* bit[27]   : This bit forces DIN data to be constant value taken from the address field. When this bit is set, the DIN_DMA_MODE must be set to SRAM. */
        unsigned int  not_last         : 1;  /* bit[28]   : Not last descriptor - when this field is set, it signals that the last LLI of the current descriptor is not the last block of the AES. When using flow SRAM this bit indicates the endianness of SRAM to DIN interface. */
        unsigned int  reserved         : 1;  /* bit[29]   : reserved */
        unsigned int  din_virtual_host : 2;  /* bit[30-31]: Defines the ID of the Host in the current transaction (DIN). */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_dma_mode_START      (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_dma_mode_END        (1)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_size_START          (2)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_size_END            (25)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_ns_bit_START            (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_ns_bit_END              (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_const_value_START   (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_const_value_END     (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_not_last_START          (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_not_last_END            (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_virtual_host_START  (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_virtual_host_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE1_WORD2_UNION
 �ṹ˵��  : DSCRPTR_QUEUE1_WORD2 �Ĵ����ṹ���塣��ַƫ����:0x00EA8����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word2 of descriptor queue1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_dma_address : 32; /* bit[0-31]: If the 'DOUT DMA mode' is:
                                                           �� SRAM - The address of the destination DMA data in the SRAM.
                                                           �� Direct LLI - The address of the destination DMA data in the system RAM (through the AXI master).
                                                           �� MLLI - The address of the destination LLI list in the SRAM. */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_WORD2_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD2_dout_dma_address_START  (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD2_dout_dma_address_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_UNION
 �ṹ˵��  : DSCRPTR_QUEUE1_WORD3 �Ĵ����ṹ���塣��ַƫ����:0x00EAC����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word3 of descriptor queue1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dout_dma_mode     : 2;  /* bit[0-1]  : �� 2'h0 - NO DMA
                                                             �� 2'h1 - SRAM
                                                             �� 2'h2 - Direct LLI
                                                             �� 2'h3 - MLLI */
        unsigned int  dout_size         : 24; /* bit[2-25] : If the 'DOUT DMA mode' is:
                                                             �� SRAM - The size of the data. Must to be multiple of 4bytes.
                                                             �� Direct LLI - The size of the data.
                                                             �� MLLI - This field is not used. */
        unsigned int  ns_bit            : 1;  /* bit[26]   : NS bit for current transaction. */
        unsigned int  dout_last_ind     : 1;  /* bit[27]   : Indicates last transaction. This AWCACHE value of the last AXI transaction is uncached and unbufferred. */
        unsigned int  reserved          : 1;  /* bit[28]   : reserved */
        unsigned int  hash_xor_bit      : 1;  /* bit[29]   : When this bit is set - the DIN data to HASH is xored with xor-register. */
        unsigned int  dout_virtual_host : 2;  /* bit[30-31]: Defines the ID of the Host for the current transaction (DOUT) */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_dma_mode_START      (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_dma_mode_END        (1)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_size_START          (2)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_size_END            (25)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_ns_bit_START             (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_ns_bit_END               (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_last_ind_START      (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_last_ind_END        (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_hash_xor_bit_START       (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_hash_xor_bit_END         (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_virtual_host_START  (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_virtual_host_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_UNION
 �ṹ˵��  : DSCRPTR_QUEUE1_WORD4 �Ĵ����ṹ���塣��ַƫ����:0x00EB0����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word4 of descriptor queue1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data_flow_mode       : 6;  /* bit[0-5]  : �� 6'd0 - BYPASS
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
                                                                �� 6'd44 - SET-FLOW-ID */
        unsigned int  aes_sel_n_hash       : 1;  /* bit[6]    : if this bit is set, the entire HASH flow is done with AES_MAC. */
        unsigned int  aes_xor_crypto_key   : 1;  /* bit[7]    : When using AES, if this field is set, then the AES HW key is xored with the already loaded key. */
        unsigned int  ack_needed           : 2;  /* bit[8-9]  : �� 0x0 - no interrupt is triggered and no completion counter is incremented when the current descriptor is complete.
                                                                �� 0x1-0x2 - when the descriptor is complete, an interrupt is generated, and the relevant completion counter (according to the field value) is incremented.  */
        unsigned int  cipher_mode          : 4;  /* bit[10-13]: Value AES DES/TDES HASH/AESMAC
                                                                �� 0x0 ECB DES -ECB ECB MD5
                                                                �� 0x1 CBC DES- CBC CBC SHA1
                                                                �� 0x2 CTR TDES ECB N/A SHA256
                                                                �� 0x3 CBC -MAC TDES CBC SHA224
                                                                �� 0x4 XTS N/A SHA512
                                                                �� 0x5 XCBC MAC SHA384
                                                                �� 0x6 N/A
                                                                �� 0x7 CMAC
                                                                �� 0x8 CCM A
                                                                �� 0x9 CCM E
                                                                �� 0xA CCM P
                                                                �� 0xB CBC-CTS */
        unsigned int  cmac_size0           : 1;  /* bit[14]   : AES_CMAC_SIZE0 - kicks a CMAC operation with size zero. */
        unsigned int  cipher_do            : 2;  /* bit[15-16]: If the current flow is AES:
                                                                �� 2'd0 - AES INTERNAL KEY
                                                                �� 2'd1 - AES_SK - RKEK.
                                                                �� 2'd2 - AES_SK - PROV_KEY
                                                                �� 2'd3 - Reserved
                                                                If the current flow is HASH:
                                                                �� 2'd1 - Do hash padding */
        unsigned int  cipher_conf0         : 2;  /* bit[17-18]: If the current flow is AES:
                                                                �� 2'd0 - encrypt: AES mode is encrypt.
                                                                �� 2'd1 - decrypt: AES mode is decrypt.
                                                                �� 2'd2 - Reserved
                                                                �� 2'd1 - hash output compared - currently not supported.
                                                                �� 2'd2 - hash output is big-endianness (need for HMAC flow). */
        unsigned int  cipher_conf1         : 1;  /* bit[19]   : If the current flow is AES �C Reserved.
                                                                If the current flow is HASH - 1'b1 - Enable hash padding in the end of block.  */
        unsigned int  cipher_conf2         : 2;  /* bit[20-21]: If the current flow is AES - Reserved.
                                                                If the current flow is HASH:
                                                                �� 2'd0 �C do not truncate output
                                                                �� 2'd1 - truncate to 96bits
                                                                �� 2'd2 - truncate to 128bits */
        unsigned int  key_size             : 2;  /* bit[22-23]: If the Data flow mode is setup AES:
                                                                �� 2'h0 - AES KEY_SIZE = 128b
                                                                �� 2'h1 - AES KEY_SIZE = 192b
                                                                �� 2'h2 - AES KEY_SIZE = 256b
                                                                If the Data flow mode is setup DES:
                                                                �� 2'h0 - DES key number = 1 key
                                                                �� 2'h1 - DES key number = 2 keys
                                                                �� 2'h2 - DES key number = 3 keys */
        unsigned int  setup_operation      : 4;  /* bit[24-27]: �� 4'd0 - NONE
                                                                �� 4'd1 - Load state0 from DIN. The functionality of bit depend on the current flow.
                                                                �� AES - load IV from DIN.
                                                                �� DES - load IV.
                                                                �� HASH - load H (digest).
                                                                �� 4'd2 - Load state1 from DIN.
                                                                �� AES - load CTR.
                                                                �� HASH - load data to compare - not supported.
                                                                �� 4'd3 - Load state2 from DIN.
                                                                �� AES - - load prev_iv.
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
                                                                �� 4'd10 - write state2 to DOUT.
                                                                �� AES - store prev_iv.
                                                                �� 4'd11 - write state3 to DOUT.
                                                                �� AES - store xex_key. */
        unsigned int  din_sram_endianness  : 1;  /* bit[28]   : When using DIN source as SRAM, this bit swaps the bytes order of the word read from the SRAM and decreases the address after each word. */
        unsigned int  dout_sram_endianness : 1;  /* bit[29]   : When using DOUT destination as SRAM, this bit swaps the bytes order of the word written to SRAM and decreases the address after each word. */
        unsigned int  word_swap            : 1;  /* bit[30]   : Change the word order of all setup-finalize descriptor from the following engines AES, AES_MAC,DES. */
        unsigned int  bytes_swap           : 1;  /* bit[31]   : Change the bytes order of all setup-finalize descriptor from the following engines AES, AES_MAC,DES. */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_data_flow_mode_START        (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_data_flow_mode_END          (5)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_aes_sel_n_hash_START        (6)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_aes_sel_n_hash_END          (6)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_aes_xor_crypto_key_START    (7)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_aes_xor_crypto_key_END      (7)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_ack_needed_START            (8)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_ack_needed_END              (9)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_mode_START           (10)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_mode_END             (13)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cmac_size0_START            (14)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cmac_size0_END              (14)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_do_START             (15)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_do_END               (16)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_conf0_START          (17)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_conf0_END            (18)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_conf1_START          (19)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_conf1_END            (19)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_conf2_START          (20)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_conf2_END            (21)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_key_size_START              (22)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_key_size_END                (23)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_setup_operation_START       (24)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_setup_operation_END         (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_din_sram_endianness_START   (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_din_sram_endianness_END     (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_dout_sram_endianness_START  (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_dout_sram_endianness_END    (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_word_swap_START             (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_word_swap_END               (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_bytes_swap_START            (31)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_bytes_swap_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_UNION
 �ṹ˵��  : DSCRPTR_QUEUE1_WORD5 �Ĵ����ṹ���塣��ַƫ����:0x0EB4����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register holds word5 of descriptor queue1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  din_addr_high  : 16; /* bit[0-15] : When using 48-bits AXI address, this field defines the highest 16bits of the DIN address. */
        unsigned int  dout_addr_high : 16; /* bit[16-31]: When using 48-bits AXI address, this field defines the highest 16bits of the DOUT address. */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_din_addr_high_START   (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_din_addr_high_END     (15)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_dout_addr_high_START  (16)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_dout_addr_high_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE1_WATERMARK_UNION
 �ṹ˵��  : DSCRPTR_QUEUE1_WATERMARK �Ĵ����ṹ���塣��ַƫ����:0x00EB8����ֵ:0x000002AA�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  watermark : 10; /* bit[0-9]  : queue 1 watermark: if the amount of empty entries exceeds the watermark level, an interrupt is issued. possible values 0-14. */
        unsigned int  reserved  : 22; /* bit[10-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_WATERMARK_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WATERMARK_watermark_START  (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WATERMARK_watermark_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_DSCRPTR_QUEUE1_CONTENT_UNION
 �ṹ˵��  : DSCRPTR_QUEUE1_CONTENT �Ĵ����ṹ���塣��ַƫ����:0x00EBC����ֵ:0x000002AA�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  queue1_content : 10; /* bit[0-9]  : The number of empty entries in queue1 */
        unsigned int  reserved       : 22; /* bit[10-31]: reserved */
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_CONTENT_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_CONTENT_queue1_content_START  (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_CONTENT_queue1_content_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_SRAM_DATA_UNION
 �ṹ˵��  : SRAM_DATA �Ĵ����ṹ���塣��ַƫ����:0x00F00����ֵ:0x00000000�����:32
 �Ĵ���˵��: READ WRITE DATA FROM SRAM NOTE! This is a special register, affected by internal logic. Test result of this register is NA.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_data : 32; /* bit[0-31]: 32 bit write or read from SRAM: read - triggers the SRAM read DMA address automatically incremented write - triggers the SRAM write DMA address automatically incremented */
    } reg;
} SOC_SECENG_P_SRAM_DATA_UNION;
#endif
#define SOC_SECENG_P_SRAM_DATA_sram_data_START  (0)
#define SOC_SECENG_P_SRAM_DATA_sram_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_SRAM_ADDR_UNION
 �ṹ˵��  : SRAM_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00F04����ֵ:0x00000000�����:32
 �Ĵ���˵��: first address given to SRAM DMA for read/write transactions from SRAM
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_addr : 15; /* bit[0-14] : SRAM starting adddress */
        unsigned int  reserved  : 17; /* bit[15-31]: reserved */
    } reg;
} SOC_SECENG_P_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_P_SRAM_ADDR_sram_addr_START  (0)
#define SOC_SECENG_P_SRAM_ADDR_sram_addr_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_SECENG_P_SRAM_DATA_READY_UNION
 �ṹ˵��  : SRAM_DATA_READY �Ĵ����ṹ���塣��ַƫ����:0x00F08����ֵ:0x00000001�����:32
 �Ĵ���˵��: reserved
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_ready : 1;  /* bit[0]   : SRAM content is ready for read in SRAM_DATA register */
        unsigned int  reserved   : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_SECENG_P_SRAM_DATA_READY_UNION;
#endif
#define SOC_SECENG_P_SRAM_DATA_READY_sram_ready_START  (0)
#define SOC_SECENG_P_SRAM_DATA_READY_sram_ready_END    (0)






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

#endif /* end of soc_seceng_p_interface.h */
