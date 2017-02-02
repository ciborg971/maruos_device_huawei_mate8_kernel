/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_smmu_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:23:00
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_SMMU.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_SMMU_INTERFACE_H__
#define __SOC_SMMU_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_define
 ****************************************************************************/
/* �Ĵ���˵����SMMU Global Control Register
   λ����UNION�ṹ:  SOC_SMMU_SCR_UNION */
#define SOC_SMMU_SCR_ADDR(base)                       ((base) + (0x0000))

/* �Ĵ���˵����SMMU Memory Control Register
   λ����UNION�ṹ:  SOC_SMMU_MEMCTRL_UNION */
#define SOC_SMMU_MEMCTRL_ADDR(base)                   ((base) + (0x0004))

/* �Ĵ���˵����SMMU Low Power Control Register
   λ����UNION�ṹ:  SOC_SMMU_LP_CTRL_UNION */
#define SOC_SMMU_LP_CTRL_ADDR(base)                   ((base) + (0x0008))

/* �Ĵ���˵����SMMU Interrupt Mask Register for Secure contest bank
   λ����UNION�ṹ:  SOC_SMMU_INTMAS_S_UNION */
#define SOC_SMMU_INTMAS_S_ADDR(base)                  ((base) + (0x0010))

/* �Ĵ���˵����SMMU Interrupt Raw Status for Secure contest bank
   λ����UNION�ṹ:  SOC_SMMU_INTRAW_S_UNION */
#define SOC_SMMU_INTRAW_S_ADDR(base)                  ((base) + (0x0014))

/* �Ĵ���˵����SMMU Interrupt Status after Mask for Secure contest bank
   λ����UNION�ṹ:  SOC_SMMU_INTSTAT_S_UNION */
#define SOC_SMMU_INTSTAT_S_ADDR(base)                 ((base) + (0x0018))

/* �Ĵ���˵����SMMU Interrupt Clear Register for Secure contest bank
   λ����UNION�ṹ:  SOC_SMMU_INTCLR_S_UNION */
#define SOC_SMMU_INTCLR_S_ADDR(base)                  ((base) + (0x001C))

/* �Ĵ���˵����SMMU Interrupt Mask Register for Non Secure contest bank
   λ����UNION�ṹ:  SOC_SMMU_INTMASK_NS_UNION */
#define SOC_SMMU_INTMASK_NS_ADDR(base)                ((base) + (0x0020))

/* �Ĵ���˵����SMMU Interrupt Raw Status for Non Secure contest bank
   λ����UNION�ṹ:  SOC_SMMU_INTRAW_NS_UNION */
#define SOC_SMMU_INTRAW_NS_ADDR(base)                 ((base) + (0x0024))

/* �Ĵ���˵����SMMU Interrupt Status after Mask for Non Secure contest bank
   λ����UNION�ṹ:  SOC_SMMU_INTSTAT_NS_UNION */
#define SOC_SMMU_INTSTAT_NS_ADDR(base)                ((base) + (0x0028))

/* �Ĵ���˵����SMMU Interrupt Clear Register for Secure contest bank
   λ����UNION�ṹ:  SOC_SMMU_INTCLR_NS_UNION */
#define SOC_SMMU_INTCLR_NS_ADDR(base)                 ((base) + (0x002C))

/* �Ĵ���˵����SMMU Control Register per Stream
   λ����UNION�ṹ:  SOC_SMMU_SMRx_UNION */
#define SOC_SMMU_SMRx_ADDR(base, n)                   ((base) + (0x0030+(n)*0x4))

/* �Ĵ���˵����SMMU Pressure Remap register
   λ����UNION�ṹ:  SOC_SMMU_PRESS_REMAP_UNION */
#define SOC_SMMU_PRESS_REMAP_ADDR(base)               ((base) + (0x012C))

/* �Ĵ���˵����SMMU SMR Reload Enable Register0
   λ����UNION�ṹ:  SOC_SMMU_RLD_EN0_UNION */
#define SOC_SMMU_RLD_EN0_ADDR(base)                   ((base) + (0x01F0))

/* �Ĵ���˵����SMMU SMR Reload Enable Register1
   λ����UNION�ṹ:  SOC_SMMU_RLD_EN1_UNION */
#define SOC_SMMU_RLD_EN1_ADDR(base)                   ((base) + (0x01F4))

/* �Ĵ���˵����SMMU System Control Register for Secure Context Bank
   λ����UNION�ṹ:  SOC_SMMU_SCB_SCTRL_UNION */
#define SOC_SMMU_SCB_SCTRL_ADDR(base)                 ((base) + (0x0200))

/* �Ĵ���˵����SMMU System Control Register for Non-Secure Context Bank
            
            Can be accessed in Non-Secure mode
   λ����UNION�ṹ:  SOC_SMMU_CB_SCTRL_UNION */
#define SOC_SMMU_CB_SCTRL_ADDR(base)                  ((base) + (0x0204))

/* �Ĵ���˵����SMMU Translation Table Base Register for Secure Context Bank
   λ����UNION�ṹ:  SOC_SMMU_SCB_TTBR_UNION */
#define SOC_SMMU_SCB_TTBR_ADDR(base)                  ((base) + (0x0208))

/* �Ĵ���˵����SMMU Translation Table Base Register for Non-Secure Context Bank0
            
            Can be accessed in Non-Secure mode
   λ����UNION�ṹ:  SOC_SMMU_CB_TTBR0_UNION */
#define SOC_SMMU_CB_TTBR0_ADDR(base)                  ((base) + (0x020C))

/* �Ĵ���˵����SMMU Translation Table Base Register for Non-Secure Context Bank1
            
            Can be accessed in Non-Secure mode
   λ����UNION�ṹ:  SOC_SMMU_CB_TTBR1_UNION */
#define SOC_SMMU_CB_TTBR1_ADDR(base)                  ((base) + (0x0210))

/* �Ĵ���˵����SMMU Translation Table Base Control Register for Secure Context Bank
   λ����UNION�ṹ:  SOC_SMMU_SCB_TTBCR_UNION */
#define SOC_SMMU_SCB_TTBCR_ADDR(base)                 ((base) + (0x0214))

/* �Ĵ���˵����SMMU Translation Table Base Control Register for Non-Secure Context Bank
            
            Can be accessed in Non-Secure mode
   λ����UNION�ṹ:  SOC_SMMU_CB_TTBCR_UNION */
#define SOC_SMMU_CB_TTBCR_ADDR(base)                  ((base) + (0x0218))

/* �Ĵ���˵����SMMU Offset Address Register for Secure Context Bank
   λ����UNION�ṹ:  SOC_SMMU_OFFSET_ADDR_S_UNION */
#define SOC_SMMU_OFFSET_ADDR_S_ADDR(base)             ((base) + (0x0220))

/* �Ĵ���˵����SMMU Offset Address Register for Non-Secure Context Bank
            
            Can be accessed in Non-Secure mode
   λ����UNION�ṹ:  SOC_SMMU_OFFSET_ADDR_NS_UNION */
#define SOC_SMMU_OFFSET_ADDR_NS_ADDR(base)            ((base) + (0x0224))

/* �Ĵ���˵����Register for MSB of all 33-bits address configuration
   λ����UNION�ṹ:  SOC_SMMU_ADDR_MSB_UNION */
#define SOC_SMMU_ADDR_MSB_ADDR(base)                  ((base) + (0x0300))

/* �Ĵ���˵����SMMU Error Address of TLB miss for Read transaction
   λ����UNION�ṹ:  SOC_SMMU_ERR_RDADDR_UNION */
#define SOC_SMMU_ERR_RDADDR_ADDR(base)                ((base) + (0x0304))

/* �Ĵ���˵����SMMU Error Address of TLB miss for Write transaction
   λ����UNION�ṹ:  SOC_SMMU_ERR_WRADDR_UNION */
#define SOC_SMMU_ERR_WRADDR_ADDR(base)                ((base) + (0x0308))

/* �Ĵ���˵����Register of record of address information for the error scenario
   λ����UNION�ṹ:  SOC_SMMU_FAULT_ADDR_UNION */
#define SOC_SMMU_FAULT_ADDR_ADDR(base)                ((base) + (0x0310))

/* �Ĵ���˵����Register of record of stream id and index id information for the error scenario
   λ����UNION�ṹ:  SOC_SMMU_FAULT_ID_UNION */
#define SOC_SMMU_FAULT_ID_ADDR(base)                  ((base) + (0x0314))

/* �Ĵ���˵����Register of record of  faults
   λ����UNION�ṹ:  SOC_SMMU_FAULT_INFO_UNION */
#define SOC_SMMU_FAULT_INFO_ADDR(base)                ((base) + (0x0318))

/* �Ĵ���˵����SMMU Debug Pointer of TLB
   λ����UNION�ṹ:  SOC_SMMU_DBGRPTR_TLB_UNION */
#define SOC_SMMU_DBGRPTR_TLB_ADDR(base)               ((base) + (0x0400))

/* �Ĵ���˵����SMMU Debug Data of TLB
   λ����UNION�ṹ:  SOC_SMMU_DBGRDATA_TLB_UNION */
#define SOC_SMMU_DBGRDATA_TLB_ADDR(base)              ((base) + (0x0404))

/* �Ĵ���˵����SMMU Debug Pointer of Cache
   λ����UNION�ṹ:  SOC_SMMU_DBGRPTR_CACHE_UNION */
#define SOC_SMMU_DBGRPTR_CACHE_ADDR(base)             ((base) + (0x0408))

/* �Ĵ���˵����SMMU Debug Data of Cache
   λ����UNION�ṹ:  SOC_SMMU_DBGRDATA0_CACHE_UNION */
#define SOC_SMMU_DBGRDATA0_CACHE_ADDR(base)           ((base) + (0x040C))

/* �Ĵ���˵����SMMU Debug Data of Cache
   λ����UNION�ṹ:  SOC_SMMU_DBGRDATA1_CACHE_UNION */
#define SOC_SMMU_DBGRDATA1_CACHE_ADDR(base)           ((base) + (0x0410))

/* �Ĵ���˵����Cache Invalid Register of all invalidation
   λ����UNION�ṹ:  SOC_SMMU_SCACHEI_ALL_UNION */
#define SOC_SMMU_SCACHEI_ALL_ADDR(base)               ((base) + (0x0414))

/* �Ĵ���˵����Cache Invalid Register of Level1 invalidation
   λ����UNION�ṹ:  SOC_SMMU_SCACHEI_L1_UNION */
#define SOC_SMMU_SCACHEI_L1_ADDR(base)                ((base) + (0x0418))

/* �Ĵ���˵����Cache Invalid Register of Level2 and Level3 invalidation
   λ����UNION�ṹ:  SOC_SMMU_SCACHEI_L2L3_UNION */
#define SOC_SMMU_SCACHEI_L2L3_ADDR(base)              ((base) + (0x041C))

/* �Ĵ���˵����SMMU Override of VA address
   λ����UNION�ṹ:  SOC_SMMU_OVA_ADDR_UNION */
#define SOC_SMMU_OVA_ADDR_ADDR(base)                  ((base) + (0x0500))

/* �Ĵ���˵����SMMU Override of PA address
   λ����UNION�ṹ:  SOC_SMMU_OPA_ADDR_UNION */
#define SOC_SMMU_OPA_ADDR_ADDR(base)                  ((base) + (0x0504))

/* �Ĵ���˵����SMMU Override of VA configuration
   λ����UNION�ṹ:  SOC_SMMU_OVA_CTRL_UNION */
#define SOC_SMMU_OVA_CTRL_ADDR(base)                  ((base) + (0x0508))

/* �Ĵ���˵����SMMU Override of Prefetch address
   λ����UNION�ṹ:  SOC_SMMU_OPREF_ADDR_UNION */
#define SOC_SMMU_OPREF_ADDR_ADDR(base)                ((base) + (0x0510))

/* �Ĵ���˵����SMMU Override of Prefetch configuration
   λ����UNION�ṹ:  SOC_SMMU_OPREF_CTRL_UNION */
#define SOC_SMMU_OPREF_CTRL_ADDR(base)                ((base) + (0x0514))

/* �Ĵ���˵����Counter for Override of prefetch
   λ����UNION�ṹ:  SOC_SMMU_OPREF_CNT_UNION */
#define SOC_SMMU_OPREF_CNT_ADDR(base)                 ((base) + (0x0518))





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
                     (1/1) reg_define
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_SMMU_SCR_UNION
 �ṹ˵��  : SCR �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000001�����:32
 �Ĵ���˵��: SMMU Global Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  glb_bypass  : 1;  /* bit[0]    : Global bypass ,high represents enable the bypass. */
        unsigned int  reserved_0  : 2;  /* bit[1-2]  :  */
        unsigned int  int_en      : 1;  /* bit[3]    : Interrupt enable control signal
                                                       0: Interrupt disable
                                                       1: Interrupt enable */
        unsigned int  cache_l1_en : 1;  /* bit[4]    : Level 1 Cache Enable */
        unsigned int  cache_l2_en : 1;  /* bit[5]    : Level 2 Cache Enable */
        unsigned int  reserved_1  : 9;  /* bit[6-14] :  */
        unsigned int  rd_shadow   : 1;  /* bit[15]   : SMR Shadow register read enable. */
        unsigned int  ptw_pf      : 4;  /* bit[16-19]: Maximum read outstanding of PTW request. */
        unsigned int  ptw_mid     : 8;  /* bit[20-27]: MID of PTW request */
        unsigned int  reserved_2  : 4;  /* bit[28-31]:  */
    } reg;
} SOC_SMMU_SCR_UNION;
#endif
#define SOC_SMMU_SCR_glb_bypass_START   (0)
#define SOC_SMMU_SCR_glb_bypass_END     (0)
#define SOC_SMMU_SCR_int_en_START       (3)
#define SOC_SMMU_SCR_int_en_END         (3)
#define SOC_SMMU_SCR_cache_l1_en_START  (4)
#define SOC_SMMU_SCR_cache_l1_en_END    (4)
#define SOC_SMMU_SCR_cache_l2_en_START  (5)
#define SOC_SMMU_SCR_cache_l2_en_END    (5)
#define SOC_SMMU_SCR_rd_shadow_START    (15)
#define SOC_SMMU_SCR_rd_shadow_END      (15)
#define SOC_SMMU_SCR_ptw_pf_START       (16)
#define SOC_SMMU_SCR_ptw_pf_END         (19)
#define SOC_SMMU_SCR_ptw_mid_START      (20)
#define SOC_SMMU_SCR_ptw_mid_END        (27)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_MEMCTRL_UNION
 �ṹ˵��  : MEMCTRL �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00280028�����:32
 �Ĵ���˵��: SMMU Memory Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_wr : 16; /* bit[0-15] : Memory Control for write bank
                                                       for TSMC 16FF RAM
                                                       [0] : SLP
                                                       [1] : DSLP
                                                       [2] : SD
                                                       [4:3]: RTSEL
                                                       [6:5]: WTSEL */
        unsigned int  mem_ctrl_rd : 16; /* bit[16-31]: Memory Control for read bank
                                                       for TSMC 16FF RAM
                                                       [0] : SLP
                                                       [1] : DSLP
                                                       [2] : SD
                                                       [4:3]: RTSEL
                                                       [6:5]: WTSEL */
    } reg;
} SOC_SMMU_MEMCTRL_UNION;
#endif
#define SOC_SMMU_MEMCTRL_mem_ctrl_wr_START  (0)
#define SOC_SMMU_MEMCTRL_mem_ctrl_wr_END    (15)
#define SOC_SMMU_MEMCTRL_mem_ctrl_rd_START  (16)
#define SOC_SMMU_MEMCTRL_mem_ctrl_rd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_LP_CTRL_UNION
 �ṹ˵��  : LP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Low Power Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  auto_clk_gt_en     : 1;  /* bit[0]   : Auto Clock gating enable. */
        unsigned int  pwrdn_handshake_en : 1;  /* bit[1]   : Power Down handshake enable.Assert this bit to indicate the power down flow, and Low Power Control software must wait the smmu_idle bit to start power down flow. */
        unsigned int  smmu_idle          : 1;  /* bit[2]   : Indication of IDLE state of SMMU, which means no pending transtions in SMMU. Read-only bit, only valid when pwrdn_handshake_en asserted, and can be cleared by reset or deassert of pwrdn_handshake_en.  */
        unsigned int  reserved           : 29; /* bit[3-31]:  */
    } reg;
} SOC_SMMU_LP_CTRL_UNION;
#endif
#define SOC_SMMU_LP_CTRL_auto_clk_gt_en_START      (0)
#define SOC_SMMU_LP_CTRL_auto_clk_gt_en_END        (0)
#define SOC_SMMU_LP_CTRL_pwrdn_handshake_en_START  (1)
#define SOC_SMMU_LP_CTRL_pwrdn_handshake_en_END    (1)
#define SOC_SMMU_LP_CTRL_smmu_idle_START           (2)
#define SOC_SMMU_LP_CTRL_smmu_idle_END             (2)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_INTMAS_S_UNION
 �ṹ˵��  : INTMAS_S �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Interrupt Mask Register for Secure contest bank
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ints_permis_msk      : 1;  /* bit[0]   : When the input transaction��s attributes doesn��t match the attributes descripted in the page table, the mmu will raise a fault for this.
                                                               1'b1: Mask the interrupt
                                                               1'b0: Not mask the interrupt */
        unsigned int  ints_ext_msk         : 1;  /* bit[1]   : When mmu receive an en error response the mmu will record this as a fault.
                                                               1'b1: Mask the interrupt
                                                               1'b0: Not mask the interrupt */
        unsigned int  ints_tlbmiss_msk     : 1;  /* bit[2]   : When there is a TLB miss generated during the translation process, the mmu will record this.
                                                               1'b1: Mask the interrupt
                                                               1'b0: Not mask the interrupt */
        unsigned int  ints_ptw_trans_msk   : 1;  /* bit[3]   : When PTW transaciont receive an error response, occur this fault.
                                                               1'b1: Mask the interrupt
                                                               1'b0: Not mask the interrupt */
        unsigned int  ints_ptw_invalid_msk : 1;  /* bit[4]   : When PTW transaction receive an invalid page table descriptor, occur this fault.
                                                               1'b1: Mask the interrupt
                                                               1'b0: Not mask the interrupt */
        unsigned int  ints_ptw_ns_msk      : 1;  /* bit[5]   : When PTW transaction receive an page table whose ns bit is not match to the prefetch transaction, occur this fault.
                                                               1'b1: Mask the interrupt
                                                               1'b0: Not mask the interrupt */
        unsigned int  reserved             : 26; /* bit[6-31]:  */
    } reg;
} SOC_SMMU_INTMAS_S_UNION;
#endif
#define SOC_SMMU_INTMAS_S_ints_permis_msk_START       (0)
#define SOC_SMMU_INTMAS_S_ints_permis_msk_END         (0)
#define SOC_SMMU_INTMAS_S_ints_ext_msk_START          (1)
#define SOC_SMMU_INTMAS_S_ints_ext_msk_END            (1)
#define SOC_SMMU_INTMAS_S_ints_tlbmiss_msk_START      (2)
#define SOC_SMMU_INTMAS_S_ints_tlbmiss_msk_END        (2)
#define SOC_SMMU_INTMAS_S_ints_ptw_trans_msk_START    (3)
#define SOC_SMMU_INTMAS_S_ints_ptw_trans_msk_END      (3)
#define SOC_SMMU_INTMAS_S_ints_ptw_invalid_msk_START  (4)
#define SOC_SMMU_INTMAS_S_ints_ptw_invalid_msk_END    (4)
#define SOC_SMMU_INTMAS_S_ints_ptw_ns_msk_START       (5)
#define SOC_SMMU_INTMAS_S_ints_ptw_ns_msk_END         (5)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_INTRAW_S_UNION
 �ṹ˵��  : INTRAW_S �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Interrupt Raw Status for Secure contest bank
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ints_permis_raw      : 1;  /* bit[0]   : When the input transaction��s attributes doesn��t match the attributes descripted in the page table, the mmu will raise a fault for this.
                                                               1'b1: Interrupt Occured
                                                               1'b0: No interrupt */
        unsigned int  ints_ext_raw         : 1;  /* bit[1]   : When mmu receive an en error response the mmu will record this as a fault.
                                                               1'b1: Interrupt Occured
                                                               1'b0: No interrupt */
        unsigned int  ints_tlbmiss_raw     : 1;  /* bit[2]   : When there is a TLB miss generated during the translation process, the mmu will record this.
                                                               1'b1: Interrupt Occured
                                                               1'b0: No interrupt */
        unsigned int  ints_ptw_trans_raw   : 1;  /* bit[3]   : When PTW transaciont receive an error response, occur this fault.
                                                               1'b1: Interrupt Occured
                                                               1'b0: No interrupt */
        unsigned int  ints_ptw_invalid_raw : 1;  /* bit[4]   : When PTW transaction receive an invalid page table descriptor, occur this fault.
                                                               1'b1: Interrupt Occured
                                                               1'b0: No interrupt */
        unsigned int  ints_ptw_ns_raw      : 1;  /* bit[5]   : When PTW transaction receive an page table whose ns bit is not match to the prefetch transaction, occur this fault.
                                                               1'b1: Interrupt Occured
                                                               1'b0: No interrupt */
        unsigned int  reserved             : 26; /* bit[6-31]:  */
    } reg;
} SOC_SMMU_INTRAW_S_UNION;
#endif
#define SOC_SMMU_INTRAW_S_ints_permis_raw_START       (0)
#define SOC_SMMU_INTRAW_S_ints_permis_raw_END         (0)
#define SOC_SMMU_INTRAW_S_ints_ext_raw_START          (1)
#define SOC_SMMU_INTRAW_S_ints_ext_raw_END            (1)
#define SOC_SMMU_INTRAW_S_ints_tlbmiss_raw_START      (2)
#define SOC_SMMU_INTRAW_S_ints_tlbmiss_raw_END        (2)
#define SOC_SMMU_INTRAW_S_ints_ptw_trans_raw_START    (3)
#define SOC_SMMU_INTRAW_S_ints_ptw_trans_raw_END      (3)
#define SOC_SMMU_INTRAW_S_ints_ptw_invalid_raw_START  (4)
#define SOC_SMMU_INTRAW_S_ints_ptw_invalid_raw_END    (4)
#define SOC_SMMU_INTRAW_S_ints_ptw_ns_raw_START       (5)
#define SOC_SMMU_INTRAW_S_ints_ptw_ns_raw_END         (5)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_INTSTAT_S_UNION
 �ṹ˵��  : INTSTAT_S �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Interrupt Status after Mask for Secure contest bank
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ints_permis_stat      : 1;  /* bit[0]   : When the input transaction��s attributes doesn��t match the attributes descripted in the page table, the mmu will raise a fault for this.
                                                                1'b1: Interrupt Occured
                                                                1'b0: No interrupt */
        unsigned int  ints_ext_stat         : 1;  /* bit[1]   : When mmu receive an en error response the mmu will record this as a fault.
                                                                1'b1: Interrupt Occured
                                                                1'b0: No interrupt */
        unsigned int  ints_tlbmiss_stat     : 1;  /* bit[2]   : When there is a TLB miss generated during the translation process, the mmu will record this.
                                                                1'b1: Interrupt Occured
                                                                1'b0: No interrupt */
        unsigned int  ints_ptw_trans_stat   : 1;  /* bit[3]   : When PTW transaciont receive an error response, occur this fault.
                                                                1'b1: Interrupt Occured
                                                                1'b0: No interrupt */
        unsigned int  ints_ptw_invalid_stat : 1;  /* bit[4]   : When PTW transaction receive an invalid page table descriptor, occur this fault.
                                                                1'b1: Interrupt Occured
                                                                1'b0: No interrupt */
        unsigned int  ints_ptw_ns_stat      : 1;  /* bit[5]   : When PTW transaction receive an page table whose ns bit is not match to the prefetch transaction, occur this fault.
                                                                1'b1: Interrupt Occured
                                                                1'b0: No interrupt */
        unsigned int  reserved              : 26; /* bit[6-31]:  */
    } reg;
} SOC_SMMU_INTSTAT_S_UNION;
#endif
#define SOC_SMMU_INTSTAT_S_ints_permis_stat_START       (0)
#define SOC_SMMU_INTSTAT_S_ints_permis_stat_END         (0)
#define SOC_SMMU_INTSTAT_S_ints_ext_stat_START          (1)
#define SOC_SMMU_INTSTAT_S_ints_ext_stat_END            (1)
#define SOC_SMMU_INTSTAT_S_ints_tlbmiss_stat_START      (2)
#define SOC_SMMU_INTSTAT_S_ints_tlbmiss_stat_END        (2)
#define SOC_SMMU_INTSTAT_S_ints_ptw_trans_stat_START    (3)
#define SOC_SMMU_INTSTAT_S_ints_ptw_trans_stat_END      (3)
#define SOC_SMMU_INTSTAT_S_ints_ptw_invalid_stat_START  (4)
#define SOC_SMMU_INTSTAT_S_ints_ptw_invalid_stat_END    (4)
#define SOC_SMMU_INTSTAT_S_ints_ptw_ns_stat_START       (5)
#define SOC_SMMU_INTSTAT_S_ints_ptw_ns_stat_END         (5)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_INTCLR_S_UNION
 �ṹ˵��  : INTCLR_S �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Interrupt Clear Register for Secure contest bank
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ints_permis_clr      : 1;  /* bit[0]   : When the input transaction��s attributes doesn��t match the attributes descripted in the page table, the mmu will raise a fault for this.
                                                               1'b1: Clear the interrupt
                                                               1'b0: Not effect */
        unsigned int  ints_ext_clr         : 1;  /* bit[1]   : When mmu receive an en error response the mmu will record this as a fault.
                                                               1'b1: Clear the interrupt
                                                               1'b0: Not effect */
        unsigned int  ints_tlbmiss_clr     : 1;  /* bit[2]   : When there is a TLB miss generated during the translation process, the mmu will record this.
                                                               1'b1: Clear the interrupt
                                                               1'b0: Not effect */
        unsigned int  ints_ptw_trans_clr   : 1;  /* bit[3]   : When PTW transaciont receive an error response, occur this fault.
                                                               1'b1: Clear the interrupt
                                                               1'b0: Not effect */
        unsigned int  ints_ptw_invalid_clr : 1;  /* bit[4]   : When PTW transaction receive an invalid page table descriptor, occur this fault.
                                                               1'b1: Clear the interrupt
                                                               1'b0: Not effect */
        unsigned int  ints_ptw_ns_clr      : 1;  /* bit[5]   : When PTW transaction receive an page table whose ns bit is not match to the prefetch transaction, occur this fault.
                                                               1'b1: Clear the interrupt
                                                               1'b0: Not effect */
        unsigned int  reserved             : 26; /* bit[6-31]:  */
    } reg;
} SOC_SMMU_INTCLR_S_UNION;
#endif
#define SOC_SMMU_INTCLR_S_ints_permis_clr_START       (0)
#define SOC_SMMU_INTCLR_S_ints_permis_clr_END         (0)
#define SOC_SMMU_INTCLR_S_ints_ext_clr_START          (1)
#define SOC_SMMU_INTCLR_S_ints_ext_clr_END            (1)
#define SOC_SMMU_INTCLR_S_ints_tlbmiss_clr_START      (2)
#define SOC_SMMU_INTCLR_S_ints_tlbmiss_clr_END        (2)
#define SOC_SMMU_INTCLR_S_ints_ptw_trans_clr_START    (3)
#define SOC_SMMU_INTCLR_S_ints_ptw_trans_clr_END      (3)
#define SOC_SMMU_INTCLR_S_ints_ptw_invalid_clr_START  (4)
#define SOC_SMMU_INTCLR_S_ints_ptw_invalid_clr_END    (4)
#define SOC_SMMU_INTCLR_S_ints_ptw_ns_clr_START       (5)
#define SOC_SMMU_INTCLR_S_ints_ptw_ns_clr_END         (5)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_INTMASK_NS_UNION
 �ṹ˵��  : INTMASK_NS �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Interrupt Mask Register for Non Secure contest bank
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intns_permis_msk      : 1;  /* bit[0]   : When the input transaction��s attributes doesn��t match the attributes descripted in the page table, the mmu will raise a fault for this.
                                                                1'b1: Mask the interrupt
                                                                1'b0: Not mask the interrupt */
        unsigned int  intns_ext_msk         : 1;  /* bit[1]   : When mmu receive an en error response the mmu will record this as a fault.
                                                                1'b1: Mask the interrupt
                                                                1'b0: Not mask the interrupt */
        unsigned int  intns_tlbmiss_msk     : 1;  /* bit[2]   : When there is a TLB miss generated during the translation process, the mmu will record this.
                                                                1'b1: Mask the interrupt
                                                                1'b0: Not mask the interrupt */
        unsigned int  intns_ptw_trans_msk   : 1;  /* bit[3]   : When PTW transaciont receive an error response, occur this fault.
                                                                1'b1: Mask the interrupt
                                                                1'b0: Not mask the interrupt */
        unsigned int  intns_ptw_invalid_msk : 1;  /* bit[4]   : When PTW transaction receive an invalid page table descriptor, occur this fault.
                                                                1'b1: Mask the interrupt
                                                                1'b0: Not mask the interrupt */
        unsigned int  intns_ptw_ns_msk      : 1;  /* bit[5]   : When PTW transaction receive an page table whose ns bit is not match to the prefetch transaction, occur this fault.
                                                                1'b1: Mask the interrupt
                                                                1'b0: Not mask the interrupt */
        unsigned int  reserved              : 26; /* bit[6-31]:  */
    } reg;
} SOC_SMMU_INTMASK_NS_UNION;
#endif
#define SOC_SMMU_INTMASK_NS_intns_permis_msk_START       (0)
#define SOC_SMMU_INTMASK_NS_intns_permis_msk_END         (0)
#define SOC_SMMU_INTMASK_NS_intns_ext_msk_START          (1)
#define SOC_SMMU_INTMASK_NS_intns_ext_msk_END            (1)
#define SOC_SMMU_INTMASK_NS_intns_tlbmiss_msk_START      (2)
#define SOC_SMMU_INTMASK_NS_intns_tlbmiss_msk_END        (2)
#define SOC_SMMU_INTMASK_NS_intns_ptw_trans_msk_START    (3)
#define SOC_SMMU_INTMASK_NS_intns_ptw_trans_msk_END      (3)
#define SOC_SMMU_INTMASK_NS_intns_ptw_invalid_msk_START  (4)
#define SOC_SMMU_INTMASK_NS_intns_ptw_invalid_msk_END    (4)
#define SOC_SMMU_INTMASK_NS_intns_ptw_ns_msk_START       (5)
#define SOC_SMMU_INTMASK_NS_intns_ptw_ns_msk_END         (5)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_INTRAW_NS_UNION
 �ṹ˵��  : INTRAW_NS �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Interrupt Raw Status for Non Secure contest bank
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intns_permis_raw      : 1;  /* bit[0]   : When the input transaction��s attributes doesn��t match the attributes descripted in the page table, the mmu will raise a fault for this.
                                                                1'b1: Interrupt Occured
                                                                1'b0: No interrupt */
        unsigned int  intns_ext_raw         : 1;  /* bit[1]   : When mmu receive an en error response the mmu will record this as a fault.
                                                                1'b1: Interrupt Occured
                                                                1'b0: No interrupt */
        unsigned int  intns_tlbmiss_raw     : 1;  /* bit[2]   : When there is a TLB miss generated during the translation process, the mmu will record this.
                                                                1'b1: Interrupt Occured
                                                                1'b0: No interrupt */
        unsigned int  intns_ptw_trans_raw   : 1;  /* bit[3]   : When PTW transaciont receive an error response, occur this fault.
                                                                1'b1: Interrupt Occured
                                                                1'b0: No interrupt */
        unsigned int  intns_ptw_invalid_raw : 1;  /* bit[4]   : When PTW transaction receive an invalid page table descriptor, occur this fault.
                                                                1'b1: Interrupt Occured
                                                                1'b0: No interrupt */
        unsigned int  intns_ptw_ns_raw      : 1;  /* bit[5]   : When PTW transaction receive an page table whose ns bit is not match to the prefetch transaction, occur this fault.
                                                                1'b1: Interrupt Occured
                                                                1'b0: No interrupt */
        unsigned int  reserved              : 26; /* bit[6-31]:  */
    } reg;
} SOC_SMMU_INTRAW_NS_UNION;
#endif
#define SOC_SMMU_INTRAW_NS_intns_permis_raw_START       (0)
#define SOC_SMMU_INTRAW_NS_intns_permis_raw_END         (0)
#define SOC_SMMU_INTRAW_NS_intns_ext_raw_START          (1)
#define SOC_SMMU_INTRAW_NS_intns_ext_raw_END            (1)
#define SOC_SMMU_INTRAW_NS_intns_tlbmiss_raw_START      (2)
#define SOC_SMMU_INTRAW_NS_intns_tlbmiss_raw_END        (2)
#define SOC_SMMU_INTRAW_NS_intns_ptw_trans_raw_START    (3)
#define SOC_SMMU_INTRAW_NS_intns_ptw_trans_raw_END      (3)
#define SOC_SMMU_INTRAW_NS_intns_ptw_invalid_raw_START  (4)
#define SOC_SMMU_INTRAW_NS_intns_ptw_invalid_raw_END    (4)
#define SOC_SMMU_INTRAW_NS_intns_ptw_ns_raw_START       (5)
#define SOC_SMMU_INTRAW_NS_intns_ptw_ns_raw_END         (5)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_INTSTAT_NS_UNION
 �ṹ˵��  : INTSTAT_NS �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Interrupt Status after Mask for Non Secure contest bank
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intns_permis_stat      : 1;  /* bit[0]   : When the input transaction��s attributes doesn��t match the attributes descripted in the page table, the mmu will raise a fault for this.
                                                                 1'b1: Interrupt Occured
                                                                 1'b0: No interrupt */
        unsigned int  intns_ext_stat         : 1;  /* bit[1]   : When mmu receive an en error response the mmu will record this as a fault.
                                                                 1'b1: Interrupt Occured
                                                                 1'b0: No interrupt */
        unsigned int  intns_tlbmiss_stat     : 1;  /* bit[2]   : When there is a TLB miss generated during the translation process, the mmu will record this.
                                                                 1'b1: Interrupt Occured
                                                                 1'b0: No interrupt */
        unsigned int  intns_ptw_trans_stat   : 1;  /* bit[3]   : When PTW transaciont receive an error response, occur this fault.
                                                                 1'b1: Interrupt Occured
                                                                 1'b0: No interrupt */
        unsigned int  intns_ptw_invalid_stat : 1;  /* bit[4]   : When PTW transaction receive an invalid page table descriptor, occur this fault.
                                                                 1'b1: Interrupt Occured
                                                                 1'b0: No interrupt */
        unsigned int  intns_ptw_ns_stat      : 1;  /* bit[5]   : When PTW transaction receive an page table whose ns bit is not match to the prefetch transaction, occur this fault.
                                                                 1'b1: Interrupt Occured
                                                                 1'b0: No interrupt */
        unsigned int  reserved               : 26; /* bit[6-31]:  */
    } reg;
} SOC_SMMU_INTSTAT_NS_UNION;
#endif
#define SOC_SMMU_INTSTAT_NS_intns_permis_stat_START       (0)
#define SOC_SMMU_INTSTAT_NS_intns_permis_stat_END         (0)
#define SOC_SMMU_INTSTAT_NS_intns_ext_stat_START          (1)
#define SOC_SMMU_INTSTAT_NS_intns_ext_stat_END            (1)
#define SOC_SMMU_INTSTAT_NS_intns_tlbmiss_stat_START      (2)
#define SOC_SMMU_INTSTAT_NS_intns_tlbmiss_stat_END        (2)
#define SOC_SMMU_INTSTAT_NS_intns_ptw_trans_stat_START    (3)
#define SOC_SMMU_INTSTAT_NS_intns_ptw_trans_stat_END      (3)
#define SOC_SMMU_INTSTAT_NS_intns_ptw_invalid_stat_START  (4)
#define SOC_SMMU_INTSTAT_NS_intns_ptw_invalid_stat_END    (4)
#define SOC_SMMU_INTSTAT_NS_intns_ptw_ns_stat_START       (5)
#define SOC_SMMU_INTSTAT_NS_intns_ptw_ns_stat_END         (5)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_INTCLR_NS_UNION
 �ṹ˵��  : INTCLR_NS �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Interrupt Clear Register for Secure contest bank
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intns_permis_clr      : 1;  /* bit[0]   : When the input transaction��s attributes doesn��t match the attributes descripted in the page table, the mmu will raise a fault for this.
                                                                1'b1: Clear the interrupt
                                                                1'b0: Not effect */
        unsigned int  intns_ext_clr         : 1;  /* bit[1]   : When mmu receive an en error response the mmu will record this as a fault.
                                                                1'b1: Clear the interrupt
                                                                1'b0: Not effect */
        unsigned int  intns_tlbmiss_clr     : 1;  /* bit[2]   : When there is a TLB miss generated during the translation process, the mmu will record this.
                                                                1'b1: Clear the interrupt
                                                                1'b0: Not effect */
        unsigned int  intns_ptw_trans_clr   : 1;  /* bit[3]   : When PTW transaciont receive an error response, occur this fault.
                                                                1'b1: Clear the interrupt
                                                                1'b0: Not effect */
        unsigned int  intns_ptw_invalid_clr : 1;  /* bit[4]   : When PTW transaction receive an invalid page table descriptor, occur this fault.
                                                                1'b1: Clear the interrupt
                                                                1'b0: Not effect */
        unsigned int  intns_ptw_ns_clr      : 1;  /* bit[5]   : When PTW transaction receive an page table whose ns bit is not match to the prefetch transaction, occur this fault.
                                                                1'b1: Clear the interrupt
                                                                1'b0: Not effect */
        unsigned int  reserved              : 26; /* bit[6-31]:  */
    } reg;
} SOC_SMMU_INTCLR_NS_UNION;
#endif
#define SOC_SMMU_INTCLR_NS_intns_permis_clr_START       (0)
#define SOC_SMMU_INTCLR_NS_intns_permis_clr_END         (0)
#define SOC_SMMU_INTCLR_NS_intns_ext_clr_START          (1)
#define SOC_SMMU_INTCLR_NS_intns_ext_clr_END            (1)
#define SOC_SMMU_INTCLR_NS_intns_tlbmiss_clr_START      (2)
#define SOC_SMMU_INTCLR_NS_intns_tlbmiss_clr_END        (2)
#define SOC_SMMU_INTCLR_NS_intns_ptw_trans_clr_START    (3)
#define SOC_SMMU_INTCLR_NS_intns_ptw_trans_clr_END      (3)
#define SOC_SMMU_INTCLR_NS_intns_ptw_invalid_clr_START  (4)
#define SOC_SMMU_INTCLR_NS_intns_ptw_invalid_clr_END    (4)
#define SOC_SMMU_INTCLR_NS_intns_ptw_ns_clr_START       (5)
#define SOC_SMMU_INTCLR_NS_intns_ptw_ns_clr_END         (5)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_SMRx_UNION
 �ṹ˵��  : SMRx �Ĵ����ṹ���塣��ַƫ����:0x0030+(n)*0x4����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Control Register per Stream
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smr_bypass      : 1;  /* bit[0]    : Bypass control based on stream */
        unsigned int  reserved        : 2;  /* bit[1-2]  :  */
        unsigned int  smr_nscfg       : 1;  /* bit[3]    : Secure/Nonsecure Context configuration on Stream basis when non-bypass mode
                                                           0: secure
                                                           1: non-secure */
        unsigned int  smr_invld_en    : 1;  /* bit[4]    : PTW Cache invalid by stream enable. When enable, PTW Cache will be invalided by stream id when pref_initial assert. */
        unsigned int  smr_ptw_qos     : 7;  /* bit[5-11] : Qos control for PTW transaction */
        unsigned int  smr_offset_addr : 20; /* bit[12-31]: The Offset Addr register is applied for the bypass mode, in bypass mode, a global offset is configured inside MMU, and using VA+offset to get the final output PA. The offset address is at a 1Mbyte granularity */
    } reg;
} SOC_SMMU_SMRx_UNION;
#endif
#define SOC_SMMU_SMRx_smr_bypass_START       (0)
#define SOC_SMMU_SMRx_smr_bypass_END         (0)
#define SOC_SMMU_SMRx_smr_nscfg_START        (3)
#define SOC_SMMU_SMRx_smr_nscfg_END          (3)
#define SOC_SMMU_SMRx_smr_invld_en_START     (4)
#define SOC_SMMU_SMRx_smr_invld_en_END       (4)
#define SOC_SMMU_SMRx_smr_ptw_qos_START      (5)
#define SOC_SMMU_SMRx_smr_ptw_qos_END        (11)
#define SOC_SMMU_SMRx_smr_offset_addr_START  (12)
#define SOC_SMMU_SMRx_smr_offset_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_PRESS_REMAP_UNION
 �ṹ˵��  : PRESS_REMAP �Ĵ����ṹ���塣��ַƫ����:0x012C����ֵ:0x0000�����:32
 �Ĵ���˵��: SMMU Pressure Remap register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0 : 16; /* bit[0-15] :  */
        unsigned int  remap_en0  : 1;  /* bit[16]   : Enable the remap function of pressure.Used for ISP/DSS TBU0 read channel */
        unsigned int  remap_sel0 : 1;  /* bit[17]   : Remap function selection.
                                                      0: All pressure remap to 2'b00
                                                      1: Pressure, except 2'b11, remap to 2'b00 */
        unsigned int  remap_en1  : 1;  /* bit[18]   : Enable the remap function of pressure.Used for ISP TBU0 write channel or DSS TBU1 read channel */
        unsigned int  remap_sel1 : 1;  /* bit[19]   : Remap function selection.
                                                      0: All pressure remap to 2'b00
                                                      1: Pressure, except 2'b11, remap to 2'b00 */
        unsigned int  reserved_1 : 12; /* bit[20-31]:  */
    } reg;
} SOC_SMMU_PRESS_REMAP_UNION;
#endif
#define SOC_SMMU_PRESS_REMAP_remap_en0_START   (16)
#define SOC_SMMU_PRESS_REMAP_remap_en0_END     (16)
#define SOC_SMMU_PRESS_REMAP_remap_sel0_START  (17)
#define SOC_SMMU_PRESS_REMAP_remap_sel0_END    (17)
#define SOC_SMMU_PRESS_REMAP_remap_en1_START   (18)
#define SOC_SMMU_PRESS_REMAP_remap_en1_END     (18)
#define SOC_SMMU_PRESS_REMAP_remap_sel1_START  (19)
#define SOC_SMMU_PRESS_REMAP_remap_sel1_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_RLD_EN0_UNION
 �ṹ˵��  : RLD_EN0 �Ĵ����ṹ���塣��ַƫ����:0x01F0����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: SMMU SMR Reload Enable Register0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smr_rld_en0 : 32; /* bit[0-31]: SMR Register enable control, each bit represents one stream bias on the stream id. */
    } reg;
} SOC_SMMU_RLD_EN0_UNION;
#endif
#define SOC_SMMU_RLD_EN0_smr_rld_en0_START  (0)
#define SOC_SMMU_RLD_EN0_smr_rld_en0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_RLD_EN1_UNION
 �ṹ˵��  : RLD_EN1 �Ĵ����ṹ���塣��ַƫ����:0x01F4����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: SMMU SMR Reload Enable Register1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smr_rld_en1 : 32; /* bit[0-31]: SMR Register enable control, each bit represents one stream bias on the stream id. */
    } reg;
} SOC_SMMU_RLD_EN1_UNION;
#endif
#define SOC_SMMU_RLD_EN1_smr_rld_en1_START  (0)
#define SOC_SMMU_RLD_EN1_smr_rld_en1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_SCB_SCTRL_UNION
 �ṹ˵��  : SCB_SCTRL �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU System Control Register for Secure Context Bank
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scb_bypass   : 1;  /* bit[0]   : Bypass control for Secure Context Bank. */
        unsigned int  scb_sc_nscfg : 2;  /* bit[1-2] : Non-secure Configuration for Secure Context Bank when bypass enable.
                                                       00 �C Use secure attribute as presented with transaction
                                                       01 �C Reserved
                                                       10 �C Secure
                                                       11 �C Non-secure */
        unsigned int  reserved     : 29; /* bit[3-31]:  */
    } reg;
} SOC_SMMU_SCB_SCTRL_UNION;
#endif
#define SOC_SMMU_SCB_SCTRL_scb_bypass_START    (0)
#define SOC_SMMU_SCB_SCTRL_scb_bypass_END      (0)
#define SOC_SMMU_SCB_SCTRL_scb_sc_nscfg_START  (1)
#define SOC_SMMU_SCB_SCTRL_scb_sc_nscfg_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_CB_SCTRL_UNION
 �ṹ˵��  : CB_SCTRL �Ĵ����ṹ���塣��ַƫ����:0x0204����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU System Control Register for Non-Secure Context Bank
            
            Can be accessed in Non-Secure mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cb_bypass   : 1;  /* bit[0]   : Bypass control for Non-Secure Context Bank. */
        unsigned int  cb_sc_nscfg : 2;  /* bit[1-2] : Non-secure Configuration for Non- Secure Context Bank when bypass enable.
                                                      00 �C Use secure attribute as presented with transaction
                                                      01 �C Reserved
                                                      10 �C Secure
                                                      11 �C Non-secure */
        unsigned int  reserved    : 29; /* bit[3-31]:  */
    } reg;
} SOC_SMMU_CB_SCTRL_UNION;
#endif
#define SOC_SMMU_CB_SCTRL_cb_bypass_START    (0)
#define SOC_SMMU_CB_SCTRL_cb_bypass_END      (0)
#define SOC_SMMU_CB_SCTRL_cb_sc_nscfg_START  (1)
#define SOC_SMMU_CB_SCTRL_cb_sc_nscfg_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_SCB_TTBR_UNION
 �ṹ˵��  : SCB_TTBR �Ĵ����ṹ���塣��ַƫ����:0x0208����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Translation Table Base Register for Secure Context Bank
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scb_ttbr : 32; /* bit[0-31]: Base Address of translation table for Secure Context Bank */
    } reg;
} SOC_SMMU_SCB_TTBR_UNION;
#endif
#define SOC_SMMU_SCB_TTBR_scb_ttbr_START  (0)
#define SOC_SMMU_SCB_TTBR_scb_ttbr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_CB_TTBR0_UNION
 �ṹ˵��  : CB_TTBR0 �Ĵ����ṹ���塣��ַƫ����:0x020C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Translation Table Base Register for Non-Secure Context Bank0
            
            Can be accessed in Non-Secure mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cb_ttbr0 : 32; /* bit[0-31]: Base Address of translation table for Non-Secure Context Bank0 */
    } reg;
} SOC_SMMU_CB_TTBR0_UNION;
#endif
#define SOC_SMMU_CB_TTBR0_cb_ttbr0_START  (0)
#define SOC_SMMU_CB_TTBR0_cb_ttbr0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_CB_TTBR1_UNION
 �ṹ˵��  : CB_TTBR1 �Ĵ����ṹ���塣��ַƫ����:0x0210����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Translation Table Base Register for Non-Secure Context Bank1
            
            Can be accessed in Non-Secure mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cb_ttbr1 : 32; /* bit[0-31]: Base Address of translation table for Non-Secure Context Bank1 */
    } reg;
} SOC_SMMU_CB_TTBR1_UNION;
#endif
#define SOC_SMMU_CB_TTBR1_cb_ttbr1_START  (0)
#define SOC_SMMU_CB_TTBR1_cb_ttbr1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_SCB_TTBCR_UNION
 �ṹ˵��  : SCB_TTBCR �Ĵ����ṹ���塣��ַƫ����:0x0214����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Translation Table Base Control Register for Secure Context Bank
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scb_ttbcr_des   : 1;  /* bit[0]   : Descriptor select for Secure Context Bank.
                                                          0: Short Descriptor
                                                          1: Long Descriptor */
        unsigned int  scb_ttbcr_nscfg : 1;  /* bit[1]   : Override the PTW transaction's property.
                                                          0: Use the transaction's security property
                                                          1: Use non-secure to override the transaction's security property. */
        unsigned int  scb_ttbr_msb    : 2;  /* bit[2-3] : MSB of SMMU_SCB_TTBR when larger than 32bits */
        unsigned int  reserved        : 28; /* bit[4-31]:  */
    } reg;
} SOC_SMMU_SCB_TTBCR_UNION;
#endif
#define SOC_SMMU_SCB_TTBCR_scb_ttbcr_des_START    (0)
#define SOC_SMMU_SCB_TTBCR_scb_ttbcr_des_END      (0)
#define SOC_SMMU_SCB_TTBCR_scb_ttbcr_nscfg_START  (1)
#define SOC_SMMU_SCB_TTBCR_scb_ttbcr_nscfg_END    (1)
#define SOC_SMMU_SCB_TTBCR_scb_ttbr_msb_START     (2)
#define SOC_SMMU_SCB_TTBCR_scb_ttbr_msb_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_CB_TTBCR_UNION
 �ṹ˵��  : CB_TTBCR �Ĵ����ṹ���塣��ַƫ����:0x0218����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Translation Table Base Control Register for Non-Secure Context Bank
            
            Can be accessed in Non-Secure mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cb_ttbcr_des  : 1;  /* bit[0]    : Descriptor select of the SMMU_CB_TTBR0 addressed region of Non-Secure Context Bank
                                                         0: Short Descriptor
                                                         1: Long Descriptor */
        unsigned int  cb_ttbcr_t0sz : 3;  /* bit[1-3]  : The Size offset of the SMMU_CB_TTBR0 addressed region, encoded as a 3 bits signed number giving the size of the region as 232-T0SZ.
                                                         Used for Long descriptor */
        unsigned int  cb_ttbcr_n    : 3;  /* bit[4-6]  : The Size offset of the SMMU_CB_TTBR0 addressed region, encoded as a 3 bits signed number giving the size of the region as 232-n.
                                                         Used for Short descriptor */
        unsigned int  cb_ttbr0_msb  : 2;  /* bit[7-8]  : MSB of SMMU_CB_TTBR0 when larger than 32bits */
        unsigned int  reserved_0    : 7;  /* bit[9-15] :  */
        unsigned int  cb_ttbcr_t1sz : 3;  /* bit[16-18]: The Size offset of the SMMU_CB_TTBR1 addressed region, encoded as a 3 bits signed number giving the size of the region as 232-T1SZ. */
        unsigned int  cb_ttbr1_msb  : 2;  /* bit[19-20]: MSB of SMMU_CB_TTBR1 when larger than 32bits */
        unsigned int  reserved_1    : 11; /* bit[21-31]:  */
    } reg;
} SOC_SMMU_CB_TTBCR_UNION;
#endif
#define SOC_SMMU_CB_TTBCR_cb_ttbcr_des_START   (0)
#define SOC_SMMU_CB_TTBCR_cb_ttbcr_des_END     (0)
#define SOC_SMMU_CB_TTBCR_cb_ttbcr_t0sz_START  (1)
#define SOC_SMMU_CB_TTBCR_cb_ttbcr_t0sz_END    (3)
#define SOC_SMMU_CB_TTBCR_cb_ttbcr_n_START     (4)
#define SOC_SMMU_CB_TTBCR_cb_ttbcr_n_END       (6)
#define SOC_SMMU_CB_TTBCR_cb_ttbr0_msb_START   (7)
#define SOC_SMMU_CB_TTBCR_cb_ttbr0_msb_END     (8)
#define SOC_SMMU_CB_TTBCR_cb_ttbcr_t1sz_START  (16)
#define SOC_SMMU_CB_TTBCR_cb_ttbcr_t1sz_END    (18)
#define SOC_SMMU_CB_TTBCR_cb_ttbr1_msb_START   (19)
#define SOC_SMMU_CB_TTBCR_cb_ttbr1_msb_END     (20)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_OFFSET_ADDR_S_UNION
 �ṹ˵��  : OFFSET_ADDR_S �Ĵ����ṹ���塣��ַƫ����:0x0220����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Offset Address Register for Secure Context Bank
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  offset_addr_s : 14; /* bit[0-13] : The Offset Addr register is applied for the bypass mode, in bypass mode, a global offset is configured inside MMU, and using VA+offset to get the final output PA. The offset address is at a 1Mbyte granularity */
        unsigned int  reserved      : 18; /* bit[14-31]:  */
    } reg;
} SOC_SMMU_OFFSET_ADDR_S_UNION;
#endif
#define SOC_SMMU_OFFSET_ADDR_S_offset_addr_s_START  (0)
#define SOC_SMMU_OFFSET_ADDR_S_offset_addr_s_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_OFFSET_ADDR_NS_UNION
 �ṹ˵��  : OFFSET_ADDR_NS �Ĵ����ṹ���塣��ַƫ����:0x0224����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Offset Address Register for Non-Secure Context Bank
            
            Can be accessed in Non-Secure mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  offset_addr_ns : 14; /* bit[0-13] : The Offset Addr register is applied for the bypass mode, in bypass mode, a global offset is configured inside MMU, and using VA+offset to get the final output PA. The offset address is at a 1Mbyte granularity */
        unsigned int  reserved       : 18; /* bit[14-31]:  */
    } reg;
} SOC_SMMU_OFFSET_ADDR_NS_UNION;
#endif
#define SOC_SMMU_OFFSET_ADDR_NS_offset_addr_ns_START  (0)
#define SOC_SMMU_OFFSET_ADDR_NS_offset_addr_ns_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_ADDR_MSB_UNION
 �ṹ˵��  : ADDR_MSB �Ĵ����ṹ���塣��ַƫ����:0x0300����ֵ:0x00000000�����:32
 �Ĵ���˵��: Register for MSB of all 33-bits address configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  msb_errrd : 2;  /* bit[0-1] : The MSB of err_rd_addr */
        unsigned int  msb_errwr : 2;  /* bit[2-3] : The MSB of err_wr_addr */
        unsigned int  msb_fault : 2;  /* bit[4-5] : The MSB of override_fault_addr */
        unsigned int  msb_ova   : 2;  /* bit[6-7] : The MSB of override_va_addr */
        unsigned int  reserved  : 24; /* bit[8-31]:  */
    } reg;
} SOC_SMMU_ADDR_MSB_UNION;
#endif
#define SOC_SMMU_ADDR_MSB_msb_errrd_START  (0)
#define SOC_SMMU_ADDR_MSB_msb_errrd_END    (1)
#define SOC_SMMU_ADDR_MSB_msb_errwr_START  (2)
#define SOC_SMMU_ADDR_MSB_msb_errwr_END    (3)
#define SOC_SMMU_ADDR_MSB_msb_fault_START  (4)
#define SOC_SMMU_ADDR_MSB_msb_fault_END    (5)
#define SOC_SMMU_ADDR_MSB_msb_ova_START    (6)
#define SOC_SMMU_ADDR_MSB_msb_ova_END      (7)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_ERR_RDADDR_UNION
 �ṹ˵��  : ERR_RDADDR �Ĵ����ṹ���塣��ַƫ����:0x0304����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Error Address of TLB miss for Read transaction
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  err_rd_addr : 32; /* bit[0-31]: The Error Addr register is applied for TLB Miss, if there is a TLB miss error, The read address will be override.Here is only 32-bits of the address, the highest bit is shown in SMMU_ADDR_MSB.msb_errrd */
    } reg;
} SOC_SMMU_ERR_RDADDR_UNION;
#endif
#define SOC_SMMU_ERR_RDADDR_err_rd_addr_START  (0)
#define SOC_SMMU_ERR_RDADDR_err_rd_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_ERR_WRADDR_UNION
 �ṹ˵��  : ERR_WRADDR �Ĵ����ṹ���塣��ַƫ����:0x0308����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Error Address of TLB miss for Write transaction
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  err_wr_addr : 32; /* bit[0-31]: The Error Addr register is applied for TLB Miss, if there is a TLB miss error, The read address will be override.Here is only 32-bits of the address, the highest bit is shown in SMMU_ADDR_MSB.msb_errwr */
    } reg;
} SOC_SMMU_ERR_WRADDR_UNION;
#endif
#define SOC_SMMU_ERR_WRADDR_err_wr_addr_START  (0)
#define SOC_SMMU_ERR_WRADDR_err_wr_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_FAULT_ADDR_UNION
 �ṹ˵��  : FAULT_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0310����ֵ:0x00000000�����:32
 �Ĵ���˵��: Register of record of address information for the error scenario
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fault_addr : 32; /* bit[0-31]: Record of the address which caused the error. Here is only 32-bits of the address, the highest bit is shown in SMMU_ADDR_MSB.msb_fault */
    } reg;
} SOC_SMMU_FAULT_ADDR_UNION;
#endif
#define SOC_SMMU_FAULT_ADDR_fault_addr_START  (0)
#define SOC_SMMU_FAULT_ADDR_fault_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_FAULT_ID_UNION
 �ṹ˵��  : FAULT_ID �Ĵ����ṹ���塣��ַƫ����:0x0314����ֵ:0x00000000�����:32
 �Ĵ���˵��: Register of record of stream id and index id information for the error scenario
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fault_index_id : 16; /* bit[0-15] : Record of the index id relative to the address recorded in SMMU_FAULT_ADDR */
        unsigned int  fault_strm_id  : 16; /* bit[16-31]: Record of the stream id relative to the address recorded in SMMU_FAULT_ADDR */
    } reg;
} SOC_SMMU_FAULT_ID_UNION;
#endif
#define SOC_SMMU_FAULT_ID_fault_index_id_START  (0)
#define SOC_SMMU_FAULT_ID_fault_index_id_END    (15)
#define SOC_SMMU_FAULT_ID_fault_strm_id_START   (16)
#define SOC_SMMU_FAULT_ID_fault_strm_id_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_FAULT_INFO_UNION
 �ṹ˵��  : FAULT_INFO �Ĵ����ṹ���塣��ַƫ����:0x0318����ֵ:0x00000000�����:32
 �Ĵ���˵��: Register of record of  faults
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fault_tlbmiss_err : 2;  /* bit[0-1]  : Record of the type of TLB miss fault
                                                             2'b00: no fault
                                                             2'b01: write transaction
                                                             2'b10: read transaction
                                                             2'b11: reserved */
        unsigned int  fault_permis_err  : 2;  /* bit[2-3]  : Record of the type of Permission fault
                                                             2'b00: no fault
                                                             2'b01: non-secure write transaction access secure region
                                                             2'b10: non-secure read transaction access secure region
                                                             2'b11: write transaction access Read-Only region */
        unsigned int  fautl_ext_err     : 2;  /* bit[4-5]  : Recored of the type of External fault
                                                             2'b00: no fault
                                                             2'b01: write transaction error
                                                             2'b10: read transaction error
                                                             2'b11: reserved */
        unsigned int  fault_ext_err_id  : 10; /* bit[6-15] : AXI ID of Exteranl fault transaction relative. */
        unsigned int  reserved          : 7;  /* bit[16-22]:  */
        unsigned int  fault_type        : 1;  /* bit[23]   : Type of Fault source.
                                                             0: TBU
                                                             1: PTW */
        unsigned int  fault_ptw_num     : 4;  /* bit[24-27]: The number of PTW Queue which occur a fault. */
        unsigned int  fault_tbu_num     : 4;  /* bit[28-31]: The number of TBU Port which occur a fault. */
    } reg;
} SOC_SMMU_FAULT_INFO_UNION;
#endif
#define SOC_SMMU_FAULT_INFO_fault_tlbmiss_err_START  (0)
#define SOC_SMMU_FAULT_INFO_fault_tlbmiss_err_END    (1)
#define SOC_SMMU_FAULT_INFO_fault_permis_err_START   (2)
#define SOC_SMMU_FAULT_INFO_fault_permis_err_END     (3)
#define SOC_SMMU_FAULT_INFO_fautl_ext_err_START      (4)
#define SOC_SMMU_FAULT_INFO_fautl_ext_err_END        (5)
#define SOC_SMMU_FAULT_INFO_fault_ext_err_id_START   (6)
#define SOC_SMMU_FAULT_INFO_fault_ext_err_id_END     (15)
#define SOC_SMMU_FAULT_INFO_fault_type_START         (23)
#define SOC_SMMU_FAULT_INFO_fault_type_END           (23)
#define SOC_SMMU_FAULT_INFO_fault_ptw_num_START      (24)
#define SOC_SMMU_FAULT_INFO_fault_ptw_num_END        (27)
#define SOC_SMMU_FAULT_INFO_fault_tbu_num_START      (28)
#define SOC_SMMU_FAULT_INFO_fault_tbu_num_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_DBGRPTR_TLB_UNION
 �ṹ˵��  : DBGRPTR_TLB �Ĵ����ṹ���塣��ַƫ����:0x0400����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Debug Pointer of TLB
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_tlbword_pointer  : 3;  /* bit[0-2]  : Point a word within a TLB Entry, each TLB Entry contains 8 words of page table. */
        unsigned int  dbg_tlbentry_pointer : 13; /* bit[3-15] : Point a specific TLB Entry */
        unsigned int  reserved             : 14; /* bit[16-29]:  */
        unsigned int  dbg_tlb_type         : 1;  /* bit[30]   : The type of TLB Entry
                                                                0: read
                                                                1: write */
        unsigned int  dbg_tlb_en           : 1;  /* bit[31]   : Debug of TLB enable. */
    } reg;
} SOC_SMMU_DBGRPTR_TLB_UNION;
#endif
#define SOC_SMMU_DBGRPTR_TLB_dbg_tlbword_pointer_START   (0)
#define SOC_SMMU_DBGRPTR_TLB_dbg_tlbword_pointer_END     (2)
#define SOC_SMMU_DBGRPTR_TLB_dbg_tlbentry_pointer_START  (3)
#define SOC_SMMU_DBGRPTR_TLB_dbg_tlbentry_pointer_END    (15)
#define SOC_SMMU_DBGRPTR_TLB_dbg_tlb_type_START          (30)
#define SOC_SMMU_DBGRPTR_TLB_dbg_tlb_type_END            (30)
#define SOC_SMMU_DBGRPTR_TLB_dbg_tlb_en_START            (31)
#define SOC_SMMU_DBGRPTR_TLB_dbg_tlb_en_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_DBGRDATA_TLB_UNION
 �ṹ˵��  : DBGRDATA_TLB �Ĵ����ṹ���塣��ַƫ����:0x0404����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Debug Data of TLB
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_tlb_rdata : 26; /* bit[0-25] : Data of one word of a TLB Entry
                                                         [24] : Valid bit
                                                         [23:22]: Access Permission
                                                         [21] : Secure/Non-secure 
                                                         [21:0] : PA */
        unsigned int  reserved      : 6;  /* bit[26-31]:  */
    } reg;
} SOC_SMMU_DBGRDATA_TLB_UNION;
#endif
#define SOC_SMMU_DBGRDATA_TLB_dbg_tlb_rdata_START  (0)
#define SOC_SMMU_DBGRDATA_TLB_dbg_tlb_rdata_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_DBGRPTR_CACHE_UNION
 �ṹ˵��  : DBGRPTR_CACHE �Ĵ����ṹ���塣��ַƫ����:0x0408����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Debug Pointer of Cache
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_cache_level      : 2;  /* bit[0-1]  : Pointing to specific Cache level */
        unsigned int  dbg_cache_l1_pointer : 2;  /* bit[2-3]  : Pointing to a specific entry of L1 cache  */
        unsigned int  dbg_cache_l1_ns      : 1;  /* bit[4]    : Pointing to a specific entry of L1 cache of secure or non-secure */
        unsigned int  dbg_cache_l2_strmid  : 11; /* bit[5-15] : Pointing to a specific stream id of PTW of L2 cache */
        unsigned int  reserved             : 15; /* bit[16-30]:  */
        unsigned int  dbg_cache_en         : 1;  /* bit[31]   : Debug of PTW Cache enable. */
    } reg;
} SOC_SMMU_DBGRPTR_CACHE_UNION;
#endif
#define SOC_SMMU_DBGRPTR_CACHE_dbg_cache_level_START       (0)
#define SOC_SMMU_DBGRPTR_CACHE_dbg_cache_level_END         (1)
#define SOC_SMMU_DBGRPTR_CACHE_dbg_cache_l1_pointer_START  (2)
#define SOC_SMMU_DBGRPTR_CACHE_dbg_cache_l1_pointer_END    (3)
#define SOC_SMMU_DBGRPTR_CACHE_dbg_cache_l1_ns_START       (4)
#define SOC_SMMU_DBGRPTR_CACHE_dbg_cache_l1_ns_END         (4)
#define SOC_SMMU_DBGRPTR_CACHE_dbg_cache_l2_strmid_START   (5)
#define SOC_SMMU_DBGRPTR_CACHE_dbg_cache_l2_strmid_END     (15)
#define SOC_SMMU_DBGRPTR_CACHE_dbg_cache_en_START          (31)
#define SOC_SMMU_DBGRPTR_CACHE_dbg_cache_en_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_DBGRDATA0_CACHE_UNION
 �ṹ˵��  : DBGRDATA0_CACHE �Ĵ����ṹ���塣��ַƫ����:0x040C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Debug Data of Cache
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_cache_rdata0 : 24; /* bit[0-23] : Data of PTW Cache
                                                            [23] : Valid bit
                                                            [22] : Secure/Non-Secure
                                                            [21:0]: Next Level Table Address */
        unsigned int  reserved         : 8;  /* bit[24-31]:  */
    } reg;
} SOC_SMMU_DBGRDATA0_CACHE_UNION;
#endif
#define SOC_SMMU_DBGRDATA0_CACHE_dbg_cache_rdata0_START  (0)
#define SOC_SMMU_DBGRDATA0_CACHE_dbg_cache_rdata0_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_DBGRDATA1_CACHE_UNION
 �ṹ˵��  : DBGRDATA1_CACHE �Ĵ����ṹ���塣��ַƫ����:0x0410����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Debug Data of Cache
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_cache_rdata1 : 12; /* bit[0-11] : Data of PTW Cache
                                                            [11:0]:VA TAG of Cache line */
        unsigned int  reserved         : 20; /* bit[12-31]:  */
    } reg;
} SOC_SMMU_DBGRDATA1_CACHE_UNION;
#endif
#define SOC_SMMU_DBGRDATA1_CACHE_dbg_cache_rdata1_START  (0)
#define SOC_SMMU_DBGRDATA1_CACHE_dbg_cache_rdata1_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_SCACHEI_ALL_UNION
 �ṹ˵��  : SCACHEI_ALL �Ĵ����ṹ���塣��ַƫ����:0x0414����ֵ:0x00000000�����:32
 �Ĵ���˵��: Cache Invalid Register of all invalidation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cache_all_invalid : 1;  /* bit[0]   : An operation initiated using SMMU_SCACHEIALL will invalid the content stored in the PTW cache which indicate by SMMU_SCACHEI_ALL.level */
        unsigned int  cache_all_level   : 2;  /* bit[1-2] : The PTW cache will be invalid according to the PTW level. */
        unsigned int  reserved          : 29; /* bit[3-31]:  */
    } reg;
} SOC_SMMU_SCACHEI_ALL_UNION;
#endif
#define SOC_SMMU_SCACHEI_ALL_cache_all_invalid_START  (0)
#define SOC_SMMU_SCACHEI_ALL_cache_all_invalid_END    (0)
#define SOC_SMMU_SCACHEI_ALL_cache_all_level_START    (1)
#define SOC_SMMU_SCACHEI_ALL_cache_all_level_END      (2)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_SCACHEI_L1_UNION
 �ṹ˵��  : SCACHEI_L1 �Ĵ����ṹ���塣��ַƫ����:0x0418����ֵ:0x00000000�����:32
 �Ĵ���˵��: Cache Invalid Register of Level1 invalidation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cache_l1_invalid  : 1;  /* bit[0]   : An operation initiated using SMMU_SCACHEIALL will invalid the content stored in the PTW cache which indicate by SMMU_SCACHEI_L1.security */
        unsigned int  cache_l1_security : 1;  /* bit[1]   : The PTW cache will be invalid according to the security attribute. */
        unsigned int  reserved          : 30; /* bit[2-31]:  */
    } reg;
} SOC_SMMU_SCACHEI_L1_UNION;
#endif
#define SOC_SMMU_SCACHEI_L1_cache_l1_invalid_START   (0)
#define SOC_SMMU_SCACHEI_L1_cache_l1_invalid_END     (0)
#define SOC_SMMU_SCACHEI_L1_cache_l1_security_START  (1)
#define SOC_SMMU_SCACHEI_L1_cache_l1_security_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_SCACHEI_L2L3_UNION
 �ṹ˵��  : SCACHEI_L2L3 �Ĵ����ṹ���塣��ַƫ����:0x041C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Cache Invalid Register of Level2 and Level3 invalidation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cache_l2l3_invalid : 1;  /* bit[0]    : An operation initiated using SMMU_SCACHEIALL will invalid the content stored in the PTW cache which indicate by SMMU_SCACHEI_L2L3.streamid */
        unsigned int  cache_l2l3_strmid  : 15; /* bit[1-15] : The PTW cache will be invalid according to the stream ID. */
        unsigned int  reserved           : 16; /* bit[16-31]:  */
    } reg;
} SOC_SMMU_SCACHEI_L2L3_UNION;
#endif
#define SOC_SMMU_SCACHEI_L2L3_cache_l2l3_invalid_START  (0)
#define SOC_SMMU_SCACHEI_L2L3_cache_l2l3_invalid_END    (0)
#define SOC_SMMU_SCACHEI_L2L3_cache_l2l3_strmid_START   (1)
#define SOC_SMMU_SCACHEI_L2L3_cache_l2l3_strmid_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_OVA_ADDR_UNION
 �ṹ˵��  : OVA_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0500����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Override of VA address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  override_va : 32; /* bit[0-31]: The override VA address for debug purpose. Here is only 32-bits of the address, the highest bit is shown in SMMU_ADDR_MSB.msb_ova */
    } reg;
} SOC_SMMU_OVA_ADDR_UNION;
#endif
#define SOC_SMMU_OVA_ADDR_override_va_START  (0)
#define SOC_SMMU_OVA_ADDR_override_va_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_OPA_ADDR_UNION
 �ṹ˵��  : OPA_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0504����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Override of PA address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  override_acquire_pa : 22; /* bit[0-21] : The acquired PA address relative to SMMU_VA_ADDR when mmu accomplish the TLB index process */
        unsigned int  override_pa_done    : 1;  /* bit[22]   : Indicate the PA has been acquired from the TLB,this register's content is valid. */
        unsigned int  reserved            : 9;  /* bit[23-31]:  */
    } reg;
} SOC_SMMU_OPA_ADDR_UNION;
#endif
#define SOC_SMMU_OPA_ADDR_override_acquire_pa_START  (0)
#define SOC_SMMU_OPA_ADDR_override_acquire_pa_END    (21)
#define SOC_SMMU_OPA_ADDR_override_pa_done_START     (22)
#define SOC_SMMU_OPA_ADDR_override_pa_done_END       (22)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_OVA_CTRL_UNION
 �ṹ˵��  : OVA_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0508����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Override of VA configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  override_va_cfg      : 1;  /* bit[0]    : enable the VA address override by SMMU_VA_ADDR register
                                                                0 - Won��t override the origninal VA address
                                                                1 �C Override the orignianl VA address */
        unsigned int  override_va_security : 1;  /* bit[1]    : Security Attribute
                                                                0�C Represents for non-secure 
                                                                1�C Represents for secure */
        unsigned int  override_va_type     : 1;  /* bit[2]    : The override VA type for debug purpose.
                                                                0: read
                                                                1: write */
        unsigned int  override_va_indexid  : 13; /* bit[3-15] : the override VA Index ID for debug purpose */
        unsigned int  override_va_strmid   : 12; /* bit[16-27]: the override VA Stream ID for debug purpose */
        unsigned int  override_tbu_num     : 4;  /* bit[28-31]: The number of TBU Port to do the override. */
    } reg;
} SOC_SMMU_OVA_CTRL_UNION;
#endif
#define SOC_SMMU_OVA_CTRL_override_va_cfg_START       (0)
#define SOC_SMMU_OVA_CTRL_override_va_cfg_END         (0)
#define SOC_SMMU_OVA_CTRL_override_va_security_START  (1)
#define SOC_SMMU_OVA_CTRL_override_va_security_END    (1)
#define SOC_SMMU_OVA_CTRL_override_va_type_START      (2)
#define SOC_SMMU_OVA_CTRL_override_va_type_END        (2)
#define SOC_SMMU_OVA_CTRL_override_va_indexid_START   (3)
#define SOC_SMMU_OVA_CTRL_override_va_indexid_END     (15)
#define SOC_SMMU_OVA_CTRL_override_va_strmid_START    (16)
#define SOC_SMMU_OVA_CTRL_override_va_strmid_END      (27)
#define SOC_SMMU_OVA_CTRL_override_tbu_num_START      (28)
#define SOC_SMMU_OVA_CTRL_override_tbu_num_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_OPREF_ADDR_UNION
 �ṹ˵��  : OPREF_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0510����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Override of Prefetch address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  override_pref_addr : 32; /* bit[0-31]: The override prefetch address for debug purpose. */
    } reg;
} SOC_SMMU_OPREF_ADDR_UNION;
#endif
#define SOC_SMMU_OPREF_ADDR_override_pref_addr_START  (0)
#define SOC_SMMU_OPREF_ADDR_override_pref_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_OPREF_CTRL_UNION
 �ṹ˵��  : OPREF_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0514����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMMU Override of Prefetch configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  override_pref_cfg      : 1;  /* bit[0]    : Control the prefetch address override by SMMU_Prefetch ADDR register
                                                                  0 - Won��t override the origninal prefetch address
                                                                  1 �C Override the orignianl prefetch address */
        unsigned int  override_pref_security : 1;  /* bit[1]    : Security Attribute
                                                                  0�C Represents for non-secure 
                                                                  1�C Represents for secure */
        unsigned int  override_pref_type     : 1;  /* bit[2]    : The override Prefetch type signal for debug purpose
                                                                  0 - read
                                                                  1 - write */
        unsigned int  override_pref_initial  : 1;  /* bit[3]    : The override Prefetch initial signal for debug purpose */
        unsigned int  override_pref_indexid  : 12; /* bit[4-15] : the override Prefetch Index ID for debug purpose */
        unsigned int  override_pref_strmid   : 16; /* bit[16-31]: the override Prefetch Stream ID for debug purpose */
    } reg;
} SOC_SMMU_OPREF_CTRL_UNION;
#endif
#define SOC_SMMU_OPREF_CTRL_override_pref_cfg_START       (0)
#define SOC_SMMU_OPREF_CTRL_override_pref_cfg_END         (0)
#define SOC_SMMU_OPREF_CTRL_override_pref_security_START  (1)
#define SOC_SMMU_OPREF_CTRL_override_pref_security_END    (1)
#define SOC_SMMU_OPREF_CTRL_override_pref_type_START      (2)
#define SOC_SMMU_OPREF_CTRL_override_pref_type_END        (2)
#define SOC_SMMU_OPREF_CTRL_override_pref_initial_START   (3)
#define SOC_SMMU_OPREF_CTRL_override_pref_initial_END     (3)
#define SOC_SMMU_OPREF_CTRL_override_pref_indexid_START   (4)
#define SOC_SMMU_OPREF_CTRL_override_pref_indexid_END     (15)
#define SOC_SMMU_OPREF_CTRL_override_pref_strmid_START    (16)
#define SOC_SMMU_OPREF_CTRL_override_pref_strmid_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_SMMU_OPREF_CNT_UNION
 �ṹ˵��  : OPREF_CNT �Ĵ����ṹ���塣��ַƫ����:0x0518����ֵ:0x00000000�����:32
 �Ĵ���˵��: Counter for Override of prefetch
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  override_pref_cnt : 32; /* bit[0-31]: Cycle counter for override of prefetch, start to count when set override_pref_cfg to 1, and stop at the end of override of prefetch. */
    } reg;
} SOC_SMMU_OPREF_CNT_UNION;
#endif
#define SOC_SMMU_OPREF_CNT_override_pref_cnt_START  (0)
#define SOC_SMMU_OPREF_CNT_override_pref_cnt_END    (31)






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

#endif /* end of soc_smmu_interface.h */
