/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_hipackphy_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:43
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_HIPACKPHY.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_HIPACKPHY_INTERFACE_H__
#define __SOC_HIPACKPHY_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/2) register_PACK
 ****************************************************************************/
/* �Ĵ���˵����This register shows current version of the PHY Control Block
   λ����UNION�ṹ:  SOC_HIPACKPHY_REVISION_UNION */
#define SOC_HIPACKPHY_REVISION_ADDR(base)             ((base) + (0x000))

/* �Ĵ���˵����This register control the initialization of the PHY. Please note that write to this register will be ignored if init_en is already at '1' state.
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYINITCTRL_UNION */
#define SOC_HIPACKPHY_PHYINITCTRL_ADDR(base)          ((base) + (0x004))

/* �Ĵ���˵����This register shows the PHY status.
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYINITSTATUS_UNION */
#define SOC_HIPACKPHY_PHYINITSTATUS_ADDR(base)        ((base) + (0x008))

/* �Ĵ���˵����This register control the clock gated of PHY
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYCLKGATED_UNION */
#define SOC_HIPACKPHY_PHYCLKGATED_ADDR(base)          ((base) + (0x000C))

/* �Ĵ���˵����This register specified the timing parameter required by the PHY.
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYTIMER0_UNION */
#define SOC_HIPACKPHY_PHYTIMER0_ADDR(base)            ((base) + (0x010))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYTIMER1_UNION */
#define SOC_HIPACKPHY_PHYTIMER1_ADDR(base)            ((base) + (0x014))

/* �Ĵ���˵����This register specified the timing paramters for PLL in both address /command, and data block.
   λ����UNION�ṹ:  SOC_HIPACKPHY_PLLCTRL_UNION */
#define SOC_HIPACKPHY_PLLCTRL_ADDR(base)              ((base) + (0x018))

/* �Ĵ���˵����This register specified the control for PLL in both address /command, and data block.
   λ����UNION�ṹ:  SOC_HIPACKPHY_PLLTIMER_UNION */
#define SOC_HIPACKPHY_PLLTIMER_ADDR(base)             ((base) + (0x01C))

/* �Ĵ���˵����This register specify the control for delay measurement of the read delay line.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DLYMEASCTRL_UNION */
#define SOC_HIPACKPHY_DLYMEASCTRL_ADDR(base)          ((base) + (0x020))

/* �Ĵ���˵����This register specify the control the ZQ calibration.
   λ����UNION�ṹ:  SOC_HIPACKPHY_IMPCTRL_UNION */
#define SOC_HIPACKPHY_IMPCTRL_ADDR(base)              ((base) + (0x024))

/* �Ĵ���˵����This register specify the ZQ calibration result.
   λ����UNION�ṹ:  SOC_HIPACKPHY_IMPSTATUS_UNION */
#define SOC_HIPACKPHY_IMPSTATUS_ADDR(base)            ((base) + (0x028))

/* �Ĵ���˵����This register is used to configure the DRAM system.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DRAMCFG_UNION */
#define SOC_HIPACKPHY_DRAMCFG_ADDR(base)              ((base) + (0x02C))

/* �Ĵ���˵����This register specify the DRAM timing parameters. Please note that the command delay specified in this register only apply to command issued by the PHY controller internally.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DRAMTIMER0_UNION */
#define SOC_HIPACKPHY_DRAMTIMER0_ADDR(base)           ((base) + (0x030))

/* �Ĵ���˵����This register specify the DRAM timing parameters. Please note that the command delay specified in this register only apply to command issued by the PHY controller internally.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DRAMTIMER1_UNION */
#define SOC_HIPACKPHY_DRAMTIMER1_ADDR(base)           ((base) + (0x034))

/* �Ĵ���˵����This register specify the DRAM timing parameters. Please note that the command delay specified in this register only apply to command issued by the PHY controller internally.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DRAMTIMER2_UNION */
#define SOC_HIPACKPHY_DRAMTIMER2_ADDR(base)           ((base) + (0x038))

/* �Ĵ���˵����This register specify the DRAM timing parameters. Please note that the command delay specified in this register only apply to command issued by the PHY controller internally.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DRAMTIMER3_UNION */
#define SOC_HIPACKPHY_DRAMTIMER3_ADDR(base)           ((base) + (0x03C))

/* �Ĵ���˵����This register specify the DRAM Write Leveling timing parameter. This register only applied to DDR3/LPDDR3 type SDRAM.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DRAMTIMER4_UNION */
#define SOC_HIPACKPHY_DRAMTIMER4_ADDR(base)           ((base) + (0x040))

/* �Ĵ���˵����This register specify the ODT control on different rank while reading or writing to particular rank.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ODTCR_UNION */
#define SOC_HIPACKPHY_ODTCR_ADDR(base)                ((base) + (0x044))

/* �Ĵ���˵����This register specify the training control.
   λ����UNION�ṹ:  SOC_HIPACKPHY_TRAINCTRL0_UNION */
#define SOC_HIPACKPHY_TRAINCTRL0_ADDR(base)           ((base) + (0x048))

/* �Ĵ���˵����This register specify the training rank control.
   λ����UNION�ṹ:  SOC_HIPACKPHY_RANKEN_UNION */
#define SOC_HIPACKPHY_RANKEN_ADDR(base)               ((base) + (0x04C))

/* �Ĵ���˵����This register specify the starting memory address where can be used to do data training. The minimum space required for data training should be 64-bytes, and the allocated memory should be 64-bytes alignment.
   λ����UNION�ṹ:  SOC_HIPACKPHY_TRAINMADDR_UNION */
#define SOC_HIPACKPHY_TRAINMADDR_ADDR(base)           ((base) + (0x0050))

/* �Ĵ���˵����This register specify the behavior of the built-in self test.
   λ����UNION�ṹ:  SOC_HIPACKPHY_BISTCTRL_UNION */
#define SOC_HIPACKPHY_BISTCTRL_ADDR(base)             ((base) + (0x0054))

/* �Ĵ���˵����This register specify the BIST data used for DRAM loopback test. Please note that this register only valid while the bist_pat is set to "User Defined"
   λ����UNION�ṹ:  SOC_HIPACKPHY_BISTDATA0_UNION */
#define SOC_HIPACKPHY_BISTDATA0_ADDR(base)            ((base) + (0x0058))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_HIPACKPHY_BISTDATA1_UNION */
#define SOC_HIPACKPHY_BISTDATA1_ADDR(base)            ((base) + (0x005C))

/* �Ĵ���˵����This register shows the result and status of BIST testing.
   λ����UNION�ṹ:  SOC_HIPACKPHY_BISTSTATUS_UNION */
#define SOC_HIPACKPHY_BISTSTATUS_ADDR(base)           ((base) + (0x0060))

/* �Ĵ���˵����This register defines the contents of the Mode Register.
   λ����UNION�ṹ:  SOC_HIPACKPHY_MODEREG01_UNION */
#define SOC_HIPACKPHY_MODEREG01_ADDR(base)            ((base) + (0x0064))

/* �Ĵ���˵����This register defines the contents of the Mode Register.
   λ����UNION�ṹ:  SOC_HIPACKPHY_MODEREG23_UNION */
#define SOC_HIPACKPHY_MODEREG23_ADDR(base)            ((base) + (0x0068))

/* �Ĵ���˵����Write/Read DET Pattern Register.
            These fields are used to fine-tune the training procedure. Users are not recommend to modify them.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DETPATTERN_UNION */
#define SOC_HIPACKPHY_DETPATTERN_ADDR(base)           ((base) + (0x006C))

/* �Ĵ���˵����Miscellaneous control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_MISC_UNION */
#define SOC_HIPACKPHY_MISC_ADDR(base)                 ((base) + (0x0070))

/* �Ĵ���˵����Rank to rank delay control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_RNK2RNK_UNION */
#define SOC_HIPACKPHY_RNK2RNK_ADDR(base)              ((base) + (0x0074))

/* �Ĵ���˵����PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYCTRL0_UNION */
#define SOC_HIPACKPHY_PHYCTRL0_ADDR(base)             ((base) + (0x0078))

/* �Ĵ���˵����PHY debug registers
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYDBG_UNION */
#define SOC_HIPACKPHY_PHYDBG_ADDR(base)               ((base) + (0x007C))

/* �Ĵ���˵����ReTrain Control
   λ����UNION�ṹ:  SOC_HIPACKPHY_RETCTRL0_UNION */
#define SOC_HIPACKPHY_RETCTRL0_ADDR(base)             ((base) + (0x0080))

/* �Ĵ���˵����DM Swap Selection
   λ����UNION�ṹ:  SOC_HIPACKPHY_DMSEL_UNION */
#define SOC_HIPACKPHY_DMSEL_ADDR(base)                ((base) + (0x0084))

/* �Ĵ���˵����IO control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_IOCTL_UNION */
#define SOC_HIPACKPHY_IOCTL_ADDR(base)                ((base) + (0x0088))

/* �Ĵ���˵����Swap of DQ in PHY
   λ����UNION�ṹ:  SOC_HIPACKPHY_DQSSEL_UNION */
#define SOC_HIPACKPHY_DQSSEL_ADDR(base)               ((base) + (0x008C))

/* �Ĵ���˵����AC PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYCTRL1_UNION */
#define SOC_HIPACKPHY_PHYCTRL1_ADDR(base)             ((base) + (0x0090))

/* �Ĵ���˵����This register is for PLL phase select within the PHY. And should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNCKCTRL_UNION */
#define SOC_HIPACKPHY_DXNCKCTRL_ADDR(base)            ((base) + (0x0094))

/* �Ĵ���˵����PHY PLL control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYPLLCTRL_AC_UNION */
#define SOC_HIPACKPHY_PHYPLLCTRL_AC_ADDR(base)        ((base) + (0x0098))

/* �Ĵ���˵����PHY PLL control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYPLLCTRL_DX_UNION */
#define SOC_HIPACKPHY_PHYPLLCTRL_DX_ADDR(base)        ((base) + (0x009C))

/* �Ĵ���˵����This register is for setting S/W training mode
   λ����UNION�ṹ:  SOC_HIPACKPHY_SWTMODE_UNION */
#define SOC_HIPACKPHY_SWTMODE_ADDR(base)              ((base) + (0x00A0))

/* �Ĵ���˵����This register is for issuing write DQS in S/W write leveling training
   λ����UNION�ṹ:  SOC_HIPACKPHY_SWTWLDQS_UNION */
#define SOC_HIPACKPHY_SWTWLDQS_ADDR(base)             ((base) + (0x00A4))

/* �Ĵ���˵����S/W training result
   λ����UNION�ṹ:  SOC_HIPACKPHY_SWTRLT_UNION */
#define SOC_HIPACKPHY_SWTRLT_ADDR(base)               ((base) + (0x00A8))

/* �Ĵ���˵����PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYCTRL2_UNION */
#define SOC_HIPACKPHY_PHYCTRL2_ADDR(base)             ((base) + (0x00AC))

/* �Ĵ���˵����PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_IOCTL1_UNION */
#define SOC_HIPACKPHY_IOCTL1_ADDR(base)               ((base) + (0x00B0))

/* �Ĵ���˵����PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_IOCTL2_UNION */
#define SOC_HIPACKPHY_IOCTL2_ADDR(base)               ((base) + (0x00B4))

/* �Ĵ���˵����This register specify the starting memory address where can be used to do data training. The minimum space required for data training should be 64-bytes, and the allocated memory should be 64-bytes alignment.
   λ����UNION�ṹ:  SOC_HIPACKPHY_TRAINMADDRTG1_UNION */
#define SOC_HIPACKPHY_TRAINMADDRTG1_ADDR(base)        ((base) + (0x00B8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_HIPACKPHY_DRAMTIMER5_UNION */
#define SOC_HIPACKPHY_DRAMTIMER5_ADDR(base)           ((base) + (0x0BC))

/* �Ĵ���˵����VREF Training Control Register.
            This register specify the common settings of the VREF training.
   λ����UNION�ṹ:  SOC_HIPACKPHY_VREFTCTRL_UNION */
#define SOC_HIPACKPHY_VREFTCTRL_ADDR(base)            ((base) + (0x00C0))

/* �Ĵ���˵����DRAM VREF Training Control Regiser.
            Register in this field are used to controls the behavior of the VREF training.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DVRFTCTRL_UNION */
#define SOC_HIPACKPHY_DVRFTCTRL_ADDR(base)            ((base) + (0x00C4))

/* �Ĵ���˵����Host VREF Training Control Regiser.
            Register in this field are used to controls the behavior of the Host VREF training.
   λ����UNION�ṹ:  SOC_HIPACKPHY_HVRFTCTRL_UNION */
#define SOC_HIPACKPHY_HVRFTCTRL_ADDR(base)            ((base) + (0x00C8))

/* �Ĵ���˵����This register control the data training.
   λ����UNION�ṹ:  SOC_HIPACKPHY_TRAINCTRL1_UNION */
#define SOC_HIPACKPHY_TRAINCTRL1_ADDR(base)           ((base) + (0x00D0))

/* �Ĵ���˵����This register control the data training.
   λ����UNION�ṹ:  SOC_HIPACKPHY_TRAINCTRL2_UNION */
#define SOC_HIPACKPHY_TRAINCTRL2_ADDR(base)           ((base) + (0x00D4))

/* �Ĵ���˵����This register control the register bank.
   λ����UNION�ṹ:  SOC_HIPACKPHY_REGBANKCTRL_UNION */
#define SOC_HIPACKPHY_REGBANKCTRL_ADDR(base)          ((base) + (0x00D8))

/* �Ĵ���˵����This register control the data training.
   λ����UNION�ṹ:  SOC_HIPACKPHY_TRAINCTRL3_UNION */
#define SOC_HIPACKPHY_TRAINCTRL3_ADDR(base)           ((base) + (0x00DC))

/* �Ĵ���˵����This register defines the contents of the Mode Register.
   λ����UNION�ṹ:  SOC_HIPACKPHY_MODEREG45_UNION */
#define SOC_HIPACKPHY_MODEREG45_ADDR(base)            ((base) + (0x00E0))

/* �Ĵ���˵����This register defines the contents of the Mode Register.
   λ����UNION�ṹ:  SOC_HIPACKPHY_MODEREG67_UNION */
#define SOC_HIPACKPHY_MODEREG67_ADDR(base)            ((base) + (0x00E4))

/* �Ĵ���˵����This register control the data training.
   λ����UNION�ṹ:  SOC_HIPACKPHY_TRAINCTRL6_UNION */
#define SOC_HIPACKPHY_TRAINCTRL6_ADDR(base)           ((base) + (0x0E8))

/* �Ĵ���˵����Write/Read DET Pattern INDEX Register.
            These fields are used to select the related DETPATTERN. Users are not recommend to modify them.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DETPATINDEX_UNION */
#define SOC_HIPACKPHY_DETPATINDEX_ADDR(base)          ((base) + (0x00EC))

/* �Ĵ���˵����PHY PLL control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYPLLCTRL_DX2_UNION */
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_ADDR(base)       ((base) + (0x00F0))

/* �Ĵ���˵����PHY PLL control register 3
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYPLLCTRL_DX3_UNION */
#define SOC_HIPACKPHY_PHYPLLCTRL_DX3_ADDR(base)       ((base) + (0x00F4))

/* �Ĵ���˵����PHY PLL control register 4
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYPLLCTRL_DX4_UNION */
#define SOC_HIPACKPHY_PHYPLLCTRL_DX4_ADDR(base)       ((base) + (0x00F8))

/* �Ĵ���˵����PHY PLL control register 5
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYPLLCTRL_DX5_UNION */
#define SOC_HIPACKPHY_PHYPLLCTRL_DX5_ADDR(base)       ((base) + (0x00FC))

/* �Ĵ���˵����This register control the comparison while BIST activated.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACBISTCTRL0_UNION */
#define SOC_HIPACKPHY_ACBISTCTRL0_ADDR(base)          ((base) + (0x100))

/* �Ĵ���˵����This register control the comparison while BIST activated.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACBISTCTRL1_UNION */
#define SOC_HIPACKPHY_ACBISTCTRL1_ADDR(base)          ((base) + (0x104))

/* �Ĵ���˵����This register shows the results and status of the BIST test. Please note that this register is read-only, and can only be reset by bist_op setting to BIST Reset.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACBISTSTS0_UNION */
#define SOC_HIPACKPHY_ACBISTSTS0_ADDR(base)           ((base) + (0x108))

/* �Ĵ���˵����This register shows the results and status of the BIST test. Please note that this register is read-only, and can only be reset by bist_op setting to BIST Reset.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACBISTSTS1_UNION */
#define SOC_HIPACKPHY_ACBISTSTS1_ADDR(base)           ((base) + (0x10C))

/* �Ĵ���˵����This register indicate the wdet lb roundary.
   λ����UNION�ṹ:  SOC_HIPACKPHY_WDXBOUND_DFS_UNION */
#define SOC_HIPACKPHY_WDXBOUND_DFS_ADDR(base)         ((base) + (0x110))

/* �Ĵ���˵����This register control the data training.
   λ����UNION�ṹ:  SOC_HIPACKPHY_TRAINCTRL4_UNION */
#define SOC_HIPACKPHY_TRAINCTRL4_ADDR(base)           ((base) + (0x114))

/* �Ĵ���˵����This register control the data training.
   λ����UNION�ṹ:  SOC_HIPACKPHY_TRAINCTRL5_UNION */
#define SOC_HIPACKPHY_TRAINCTRL5_ADDR(base)           ((base) + (0x118))

/* �Ĵ���˵����This register control the data training.
   λ����UNION�ṹ:  SOC_HIPACKPHY_TRAINCTRL7_UNION */
#define SOC_HIPACKPHY_TRAINCTRL7_ADDR(base)           ((base) + (0x11C))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCMDBDL0_UNION */
#define SOC_HIPACKPHY_ACCMDBDL0_ADDR(base)            ((base) + (0x120))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCMDBDL1_UNION */
#define SOC_HIPACKPHY_ACCMDBDL1_ADDR(base)            ((base) + (0x124))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCMDBDL2_UNION */
#define SOC_HIPACKPHY_ACCMDBDL2_ADDR(base)            ((base) + (0x128))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCMDBDL3_UNION */
#define SOC_HIPACKPHY_ACCMDBDL3_ADDR(base)            ((base) + (0x12C))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCMDBDL4_UNION */
#define SOC_HIPACKPHY_ACCMDBDL4_ADDR(base)            ((base) + (0x130))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCMDBDL5_UNION */
#define SOC_HIPACKPHY_ACCMDBDL5_ADDR(base)            ((base) + (0x134))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCMDBDL6_UNION */
#define SOC_HIPACKPHY_ACCMDBDL6_ADDR(base)            ((base) + (0x138))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCMDBDL7_UNION */
#define SOC_HIPACKPHY_ACCMDBDL7_ADDR(base)            ((base) + (0x13C))

/* �Ĵ���˵����AC address bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACADDRBDL0_UNION */
#define SOC_HIPACKPHY_ACADDRBDL0_ADDR(base)           ((base) + (0x140))

/* �Ĵ���˵����AC address bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACADDRBDL1_UNION */
#define SOC_HIPACKPHY_ACADDRBDL1_ADDR(base)           ((base) + (0x144))

/* �Ĵ���˵����AC address bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACADDRBDL2_UNION */
#define SOC_HIPACKPHY_ACADDRBDL2_ADDR(base)           ((base) + (0x148))

/* �Ĵ���˵����AC address bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACADDRBDL3_UNION */
#define SOC_HIPACKPHY_ACADDRBDL3_ADDR(base)           ((base) + (0x14C))

/* �Ĵ���˵����AC address bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACADDRBDL4_UNION */
#define SOC_HIPACKPHY_ACADDRBDL4_ADDR(base)           ((base) + (0x150))

/* �Ĵ���˵����AC address bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACADDRBDL5_UNION */
#define SOC_HIPACKPHY_ACADDRBDL5_ADDR(base)           ((base) + (0x154))

/* �Ĵ���˵����AC address bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACADDRBDL6_UNION */
#define SOC_HIPACKPHY_ACADDRBDL6_ADDR(base)           ((base) + (0x158))

/* �Ĵ���˵����AC address bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACADDRBDL7_UNION */
#define SOC_HIPACKPHY_ACADDRBDL7_ADDR(base)           ((base) + (0x15C))

/* �Ĵ���˵����AC address bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACADDRBDL8_UNION */
#define SOC_HIPACKPHY_ACADDRBDL8_ADDR(base)           ((base) + (0x160))

/* �Ĵ���˵����AC address bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACADDRBDL9_UNION */
#define SOC_HIPACKPHY_ACADDRBDL9_ADDR(base)           ((base) + (0x164))

/* �Ĵ���˵����AC clock bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCLKBDL_UNION */
#define SOC_HIPACKPHY_ACCLKBDL_ADDR(base)             ((base) + (0x168))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYCTL0_UNION */
#define SOC_HIPACKPHY_ACPHYCTL0_ADDR(base)            ((base) + (0x170))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYCTL1_UNION */
#define SOC_HIPACKPHY_ACPHYCTL1_ADDR(base)            ((base) + (0x174))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYCTL2_UNION */
#define SOC_HIPACKPHY_ACPHYCTL2_ADDR(base)            ((base) + (0x178))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYCTL3_UNION */
#define SOC_HIPACKPHY_ACPHYCTL3_ADDR(base)            ((base) + (0x17C))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYCTL4_UNION */
#define SOC_HIPACKPHY_ACPHYCTL4_ADDR(base)            ((base) + (0x180))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYCTL5_UNION */
#define SOC_HIPACKPHY_ACPHYCTL5_ADDR(base)            ((base) + (0x184))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYCTL6_UNION */
#define SOC_HIPACKPHY_ACPHYCTL6_ADDR(base)            ((base) + (0x188))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYCTL7_UNION */
#define SOC_HIPACKPHY_ACPHYCTL7_ADDR(base)            ((base) + (0x018C))

/* �Ĵ���˵����This register is for PHY debug only.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACDEBUG_UNION */
#define SOC_HIPACKPHY_ACDEBUG_ADDR(base)              ((base) + (0x0190))

/* �Ĵ���˵����AC block PHY reserved control pins. This register is for PHY control and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYRSVDC_UNION */
#define SOC_HIPACKPHY_ACPHYRSVDC_ADDR(base)           ((base) + (0x0194))

/* �Ĵ���˵����AC block PHY reserved control pins. This register is for PHY control and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYRSVDS_UNION */
#define SOC_HIPACKPHY_ACPHYRSVDS_ADDR(base)           ((base) + (0x0198))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYCTL8_UNION */
#define SOC_HIPACKPHY_ACPHYCTL8_ADDR(base)            ((base) + (0x019C))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCMDBDL8_UNION */
#define SOC_HIPACKPHY_ACCMDBDL8_ADDR(base)            ((base) + (0x1A0))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCMDBDL9_UNION */
#define SOC_HIPACKPHY_ACCMDBDL9_ADDR(base)            ((base) + (0x1A4))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCMDBDL10_UNION */
#define SOC_HIPACKPHY_ACCMDBDL10_ADDR(base)           ((base) + (0x1A8))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACCMDBDL11_UNION */
#define SOC_HIPACKPHY_ACCMDBDL11_ADDR(base)           ((base) + (0x1AC))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYDCC_UNION */
#define SOC_HIPACKPHY_ACPHYDCC_ADDR(base)             ((base) + (0x01B0))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYCTL9_UNION */
#define SOC_HIPACKPHY_ACPHYCTL9_ADDR(base)            ((base) + (0x01B4))

/* �Ĵ���˵����CA SWAP index register
   λ����UNION�ṹ:  SOC_HIPACKPHY_CATSWAPINDEX_UNION */
#define SOC_HIPACKPHY_CATSWAPINDEX_ADDR(base)         ((base) + (0x01B8))

/* �Ĵ���˵����CA SWAP select register, indexed by CATSWAPINDEX
   λ����UNION�ṹ:  SOC_HIPACKPHY_CATSWAPSEL_UNION */
#define SOC_HIPACKPHY_CATSWAPSEL_ADDR(base)           ((base) + (0x01BC))

/* �Ĵ���˵����CA Training Timer0
   λ����UNION�ṹ:  SOC_HIPACKPHY_CATTIMER0_UNION */
#define SOC_HIPACKPHY_CATTIMER0_ADDR(base)            ((base) + (0x01C0))

/* �Ĵ���˵����CA Training Timer1
   λ����UNION�ṹ:  SOC_HIPACKPHY_CATTIMER1_UNION */
#define SOC_HIPACKPHY_CATTIMER1_ADDR(base)            ((base) + (0x01C4))

/* �Ĵ���˵����CA Training Configuration
   λ����UNION�ṹ:  SOC_HIPACKPHY_CATCONFIG_UNION */
#define SOC_HIPACKPHY_CATCONFIG_ADDR(base)            ((base) + (0x01C8))

/* �Ĵ���˵����CA Training result for debug
   λ����UNION�ṹ:  SOC_HIPACKPHY_CATRESULT_UNION */
#define SOC_HIPACKPHY_CATRESULT_ADDR(base)            ((base) + (0x01CC))

/* �Ĵ���˵����SW CA Training DQ result from PHY
   λ����UNION�ṹ:  SOC_HIPACKPHY_PHYDQRESULT_UNION */
#define SOC_HIPACKPHY_PHYDQRESULT_ADDR(base)          ((base) + (0x01D0))

/* �Ĵ���˵����CA Training addr phase boundary
   λ����UNION�ṹ:  SOC_HIPACKPHY_ADDRPHBOUND_UNION */
#define SOC_HIPACKPHY_ADDRPHBOUND_ADDR(base)          ((base) + (0x01D4))

/* �Ĵ���˵����SW CA Training pattern for  positive CK edge
   λ����UNION�ṹ:  SOC_HIPACKPHY_SWCATPATTERN_P_UNION */
#define SOC_HIPACKPHY_SWCATPATTERN_P_ADDR(base)       ((base) + (0x01D8))

/* �Ĵ���˵����SW CA Training pattern for  negative CK edge
   λ����UNION�ṹ:  SOC_HIPACKPHY_SWCATPATTERN_N_UNION */
#define SOC_HIPACKPHY_SWCATPATTERN_N_ADDR(base)       ((base) + (0x01DC))

/* �Ĵ���˵����Programmed MRS sequence in the DRAM initialization
   λ����UNION�ṹ:  SOC_HIPACKPHY_MRS_SEQ_PROG_UNION */
#define SOC_HIPACKPHY_MRS_SEQ_PROG_ADDR(base)         ((base) + (0x01E0))

/* �Ĵ���˵����Low Power Control Register
   λ����UNION�ṹ:  SOC_HIPACKPHY_LPCTRL_UNION */
#define SOC_HIPACKPHY_LPCTRL_ADDR(base)               ((base) + (0x01E4))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYCTL10_UNION */
#define SOC_HIPACKPHY_ACPHYCTL10_ADDR(base)           ((base) + (0x1E8))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ACPHYCTL11_UNION */
#define SOC_HIPACKPHY_ACPHYCTL11_ADDR(base)           ((base) + (0x1EC))

/* �Ĵ���˵����Host PHY VREF(AC) Training Result. This register shows the training result of the Host PHY VREF(AC) training.
            This register is only valid while the application is LPDDR4.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AHVREFT_STATUS_UNION */
#define SOC_HIPACKPHY_AHVREFT_STATUS_ADDR(base)       ((base) + (0x1F0))

/* �Ĵ���˵����DRAM VREF(AC) Training Result. This register shows the training result of the DRAM VREF(DQ) training.
            This register is only valid while the application is LPDDR4.
   λ����UNION�ṹ:  SOC_HIPACKPHY_ADVREF_STATUS_UNION */
#define SOC_HIPACKPHY_ADVREF_STATUS_ADDR(base)        ((base) + (0x1F4))

/* �Ĵ���˵����DFI MISC control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_DFIMISCCTRL_UNION */
#define SOC_HIPACKPHY_DFIMISCCTRL_ADDR(base)          ((base) + (0x1FC))

/* �Ĵ���˵����This register is used to control if the loopback data is compre during BIST of Data Blocks.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNBISTCTRL_UNION */
#define SOC_HIPACKPHY_DXNBISTCTRL_ADDR(base, n)       ((base) + (0x200+(n)*0x80))

/* �Ĵ���˵����This register shows the results and status of the BIST test. Please note that this register is read-only, and can only be reset by bist_op setting to BIST Reset.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNBISTSTS_UNION */
#define SOC_HIPACKPHY_DXNBISTSTS_ADDR(base, n)        ((base) + (0x204+(n)*0x80))

/* �Ĵ���˵����This register is used to control Data Block
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNCTRL_UNION */
#define SOC_HIPACKPHY_DXNCTRL_ADDR(base, n)           ((base) + (0x208+(n)*0x80))

/* �Ĵ���˵����This register is used to control the bit delay line of the DATA block.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNWDQNBDL0_UNION */
#define SOC_HIPACKPHY_DXNWDQNBDL0_ADDR(base, m, n)    ((base) + (0x210+(m)*0x400+(n)*0x80))

/* �Ĵ���˵����This register is used to control the bit delay line of the DATA block.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNWDQNBDL1_UNION */
#define SOC_HIPACKPHY_DXNWDQNBDL1_ADDR(base, m, n)    ((base) + (0x214+(m)*0x400+(n)*0x80))

/* �Ĵ���˵����This register is used to control the bit delay line of the DATA block.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNWDQNBDL2_UNION */
#define SOC_HIPACKPHY_DXNWDQNBDL2_ADDR(base, m, n)    ((base) + (0x218+(m)*0x400+(n)*0x80))

/* �Ĵ���˵����This register is used to control the bit delay line of the DATA block.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNRDQNBDL0_UNION */
#define SOC_HIPACKPHY_DXNRDQNBDL0_ADDR(base, m, n, l)  ((base) + (0x21C+(l)*0x800+(m)*0x400+(n)*0x80))

/* �Ĵ���˵����This register is used to control the bit delay line of the DATA block.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNRDQNBDL1_UNION */
#define SOC_HIPACKPHY_DXNRDQNBDL1_ADDR(base, m, n, l)  ((base) + (0x220+(l)*0x800+(m)*0x400+(n)*0x80))

/* �Ĵ���˵����This register is used to control the bit delay line of the DATA block.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNRDQNBDL2_UNION */
#define SOC_HIPACKPHY_DXNRDQNBDL2_ADDR(base, m, n, l)  ((base) + (0x224+(l)*0x800+(m)*0x400+(n)*0x80))

/* �Ĵ���˵����Output Enable Delay Line Control. This register specify the dely line value of the output enable delay line within PHY data block.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNOEBDL_UNION */
#define SOC_HIPACKPHY_DXNOEBDL_ADDR(base, n)          ((base) + (0x228+(n)*0x80))

/* �Ĵ���˵����This register is used to control the local delay line.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNRDQSDLY_UNION */
#define SOC_HIPACKPHY_DXNRDQSDLY_ADDR(base, n)        ((base) + (0x22C+(n)*0x80))

/* �Ĵ���˵����This register is used to control the write leveling DQS delays.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNWDQSDLY_UNION */
#define SOC_HIPACKPHY_DXNWDQSDLY_ADDR(base, n)        ((base) + (0x230+(n)*0x80))

/* �Ĵ���˵����This register is used to control the write leveling delay line.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNWDQDLY_UNION */
#define SOC_HIPACKPHY_DXNWDQDLY_ADDR(base, m, n)      ((base) + (0x234+(m)*0x400+(n)*0x80))

/* �Ĵ���˵����This reister is used to control if PHY controller add extra system latency.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNWLSL_UNION */
#define SOC_HIPACKPHY_DXNWLSL_ADDR(base, n)           ((base) + (0x238+(n)*0x80))

/* �Ĵ���˵����This register is used to control the latch enable within the PHY to get the stable data.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNGDS_UNION */
#define SOC_HIPACKPHY_DXNGDS_ADDR(base, n)            ((base) + (0x23C+(n)*0x80))

/* �Ĵ���˵����This register is used to control the local delay line.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNRDQSGDLY_UNION */
#define SOC_HIPACKPHY_DXNRDQSGDLY_ADDR(base, m, n)    ((base) + (0x240+(n)*0x80+(m)*0x400))

/* �Ĵ���˵����This register is used to latch the WDQ left boundary of current rank after WDET
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNWDQNLB0_UNION */
#define SOC_HIPACKPHY_DXNWDQNLB0_ADDR(base, n)        ((base) + (0x244+(n)*0x80))

/* �Ĵ���˵����This register is used to control the local delay line.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNRDQSDLYSUB_UNION */
#define SOC_HIPACKPHY_DXNRDQSDLYSUB_ADDR(base, n)     ((base) + (0x248+(n)*0x80))

/* �Ĵ���˵����DATA block clock bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNCLKBDL_UNION */
#define SOC_HIPACKPHY_DXNCLKBDL_ADDR(base, n)         ((base) + (0x24C+(n)*0x80))

/* �Ĵ���˵����Read data eye boundary. This register indicates the left/right boundary of RDQSQDL of the data eye.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNRDBOUND_UNION */
#define SOC_HIPACKPHY_DXNRDBOUND_ADDR(base, n)        ((base) + (0x250+(n)*0x80))

/* �Ĵ���˵����Write data eye boundary. This register indicates the left/right boundary of WDQSQDL of the data eye.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNWRBOUND_UNION */
#define SOC_HIPACKPHY_DXNWRBOUND_ADDR(base, n)        ((base) + (0x254+(n)*0x80))

/* �Ĵ���˵����DX PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXPHYCTRL_UNION */
#define SOC_HIPACKPHY_DXPHYCTRL_ADDR(base, n)         ((base) + (0x258+(n)*0x80))

/* �Ĵ���˵����This register is used to latch the WDQ left boundary of current rank after WDET
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNWDQNLB1_UNION */
#define SOC_HIPACKPHY_DXNWDQNLB1_ADDR(base, n)        ((base) + (0x25C+(n)*0x80))

/* �Ĵ���˵����Data block PHY miscellaneous control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNMISCCTRL0_UNION */
#define SOC_HIPACKPHY_DXNMISCCTRL0_ADDR(base, n)      ((base) + (0x260+(n)*0x80))

/* �Ĵ���˵����Data block PHY miscellaneous control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNMISCCTRL1_UNION */
#define SOC_HIPACKPHY_DXNMISCCTRL1_ADDR(base, n)      ((base) + (0x264+(n)*0x80))

/* �Ĵ���˵����Data block PHY debug signals
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXDEBUG0_UNION */
#define SOC_HIPACKPHY_DXDEBUG0_ADDR(base, n)          ((base) + (0x268+(n)*0x80))

/* �Ĵ���˵����Data block PHY debug signals
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXDEBUG1_UNION */
#define SOC_HIPACKPHY_DXDEBUG1_ADDR(base, n)          ((base) + (0x26C+(n)*0x80))

/* �Ĵ���˵����DRAM VREF(DQ) Training Result. This register shows the training result of the DRAM VREF(DQ) training.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DVREFT_STATUS_UNION */
#define SOC_HIPACKPHY_DVREFT_STATUS_ADDR(base, n)     ((base) + (0x270+(n)*0x80))

/* �Ĵ���˵����Host PHY VREF(DQ) Training Result. This register shows the training result of the Host PHY VREF(DQ) training.
   λ����UNION�ṹ:  SOC_HIPACKPHY_HVREFT_STATUS_UNION */
#define SOC_HIPACKPHY_HVREFT_STATUS_ADDR(base, n)     ((base) + (0x274+(n)*0x80))

/* �Ĵ���˵����Data block PHY debug/miscellaneous control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXDEBUGCONFIG_UNION */
#define SOC_HIPACKPHY_DXDEBUGCONFIG_ADDR(base, n)     ((base) + (0x278+(n)*0x80))

/* �Ĵ���˵����Data block PHY DCC control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNDCC_UNION */
#define SOC_HIPACKPHY_DXNDCC_ADDR(base, n)            ((base) + (0x27C+(n)*0x80))

/* �Ĵ���˵����Data block PHY debug/miscellaneous control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DXNMISCCTRL3_UNION */
#define SOC_HIPACKPHY_DXNMISCCTRL3_ADDR(base, n)      ((base) + (0x20C+(n)*0x80))

/* �Ĵ���˵����IO control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_IOCTL3_UNION */
#define SOC_HIPACKPHY_IOCTL3_ADDR(base)               ((base) + (0xFF0))

/* �Ĵ���˵����IO control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_IOCTL4_UNION */
#define SOC_HIPACKPHY_IOCTL4_ADDR(base)               ((base) + (0xFF4))

/* �Ĵ���˵����IO control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_IOCTL5_UNION */
#define SOC_HIPACKPHY_IOCTL5_ADDR(base)               ((base) + (0xFF8))



/****************************************************************************
                     (2/2) register_DDRPHY_STATIC
 ****************************************************************************/
/* �Ĵ���˵����This register specified the timing paramters for PLL in both address /command, and data block.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_PLLCTRL_UNION */
#define SOC_HIPACKPHY_AC_PLLCTRL_ADDR(base)           ((base) + (0x010))

/* �Ĵ���˵����PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_PHYCTRL0_UNION */
#define SOC_HIPACKPHY_AC_PHYCTRL0_ADDR(base)          ((base) + (0x014))

/* �Ĵ���˵����IO control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_IOCTL_UNION */
#define SOC_HIPACKPHY_AC_IOCTL_ADDR(base)             ((base) + (0x018))

/* �Ĵ���˵����AC PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_PHYCTRL1_UNION */
#define SOC_HIPACKPHY_AC_PHYCTRL1_ADDR(base)          ((base) + (0x01C))

/* �Ĵ���˵����PHY PLL control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_UNION */
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_ADDR(base)     ((base) + (0x020))

/* �Ĵ���˵����PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_IOCTL1_UNION */
#define SOC_HIPACKPHY_AC_IOCTL1_ADDR(base)            ((base) + (0x024))

/* �Ĵ���˵����PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_IOCTL2_UNION */
#define SOC_HIPACKPHY_AC_IOCTL2_ADDR(base)            ((base) + (0x028))

/* �Ĵ���˵����PHY PLL control register 3
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_UNION */
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_ADDR(base)    ((base) + (0x02C))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACCMDBDL0_UNION */
#define SOC_HIPACKPHY_AC_ACCMDBDL0_ADDR(base)         ((base) + (0x038))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACCMDBDL2_UNION */
#define SOC_HIPACKPHY_AC_ACCMDBDL2_ADDR(base)         ((base) + (0x040))

/* �Ĵ���˵����AC command bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACCMDBDL4_UNION */
#define SOC_HIPACKPHY_AC_ACCMDBDL4_ADDR(base)         ((base) + (0x048))

/* �Ĵ���˵����AC clock bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACCLKBDL_UNION */
#define SOC_HIPACKPHY_AC_ACCLKBDL_ADDR(base)          ((base) + (0x050))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYCTL0_UNION */
#define SOC_HIPACKPHY_AC_ACPHYCTL0_ADDR(base)         ((base) + (0x054))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYCTL1_UNION */
#define SOC_HIPACKPHY_AC_ACPHYCTL1_ADDR(base)         ((base) + (0x058))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYCTL2_UNION */
#define SOC_HIPACKPHY_AC_ACPHYCTL2_ADDR(base)         ((base) + (0x05C))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYCTL3_UNION */
#define SOC_HIPACKPHY_AC_ACPHYCTL3_ADDR(base)         ((base) + (0x060))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYCTL4_UNION */
#define SOC_HIPACKPHY_AC_ACPHYCTL4_ADDR(base)         ((base) + (0x064))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYCTL5_UNION */
#define SOC_HIPACKPHY_AC_ACPHYCTL5_ADDR(base)         ((base) + (0x068))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYCTL6_UNION */
#define SOC_HIPACKPHY_AC_ACPHYCTL6_ADDR(base)         ((base) + (0x06C))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYCTL7_UNION */
#define SOC_HIPACKPHY_AC_ACPHYCTL7_ADDR(base)         ((base) + (0x070))

/* �Ĵ���˵����This register is for PHY debug only.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACDEBUG_UNION */
#define SOC_HIPACKPHY_AC_ACDEBUG_ADDR(base)           ((base) + (0x074))

/* �Ĵ���˵����AC block PHY reserved control pins. This register is for PHY control and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYRSVDC_UNION */
#define SOC_HIPACKPHY_AC_ACPHYRSVDC_ADDR(base)        ((base) + (0x078))

/* �Ĵ���˵����AC block PHY reserved control pins. This register is for PHY control and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYRSVDS_UNION */
#define SOC_HIPACKPHY_AC_ACPHYRSVDS_ADDR(base)        ((base) + (0x07C))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYDCC_UNION */
#define SOC_HIPACKPHY_AC_ACPHYDCC_ADDR(base)          ((base) + (0x094))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYCTL9_UNION */
#define SOC_HIPACKPHY_AC_ACPHYCTL9_ADDR(base)         ((base) + (0x098))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYCTL10_UNION */
#define SOC_HIPACKPHY_AC_ACPHYCTL10_ADDR(base)        ((base) + (0x09C))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYCTL11_UNION */
#define SOC_HIPACKPHY_AC_ACPHYCTL11_ADDR(base)        ((base) + (0x0A0))

/* �Ĵ���˵����IO control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_IOCTL3_UNION */
#define SOC_HIPACKPHY_AC_IOCTL3_ADDR(base)            ((base) + (0x0A4))

/* �Ĵ���˵����IO control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_IOCTL4_UNION */
#define SOC_HIPACKPHY_AC_IOCTL4_ADDR(base)            ((base) + (0x0A8))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYDCC1_UNION */
#define SOC_HIPACKPHY_AC_ACPHYDCC1_ADDR(base)         ((base) + (0x0AC))

/* �Ĵ���˵����AC block PHY control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_ACPHYDCC2_UNION */
#define SOC_HIPACKPHY_AC_ACPHYDCC2_ADDR(base)         ((base) + (0x0B0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_IOCTL5_UNION */
#define SOC_HIPACKPHY_AC_IOCTL5_ADDR(base)            ((base) + (0x0B4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_HIPACKPHY_AC_IOCTL6_UNION */
#define SOC_HIPACKPHY_AC_IOCTL6_ADDR(base)            ((base) + (0x0B8))

/* �Ĵ���˵����PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_PHYCTRL0_UNION */
#define SOC_HIPACKPHY_DX_PHYCTRL0_ADDR(base)          ((base) + (0x200))

/* �Ĵ���˵����IO control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_IOCTL_UNION */
#define SOC_HIPACKPHY_DX_IOCTL_ADDR(base)             ((base) + (0x204))

/* �Ĵ���˵����Swap of DQ in PHY
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DQSSEL_UNION */
#define SOC_HIPACKPHY_DX_DQSSEL_ADDR(base)            ((base) + (0x208))

/* �Ĵ���˵����This register is for PLL phase select within the PHY. And should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXNCKCTRL_UNION */
#define SOC_HIPACKPHY_DX_DXNCKCTRL_ADDR(base)         ((base) + (0x20C))

/* �Ĵ���˵����PHY PLL control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_UNION */
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_ADDR(base)     ((base) + (0x210))

/* �Ĵ���˵����PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_PHYCTRL2_UNION */
#define SOC_HIPACKPHY_DX_PHYCTRL2_ADDR(base)          ((base) + (0x214))

/* �Ĵ���˵����PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_IOCTL1_UNION */
#define SOC_HIPACKPHY_DX_IOCTL1_ADDR(base)            ((base) + (0x218))

/* �Ĵ���˵����PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_IOCTL2_UNION */
#define SOC_HIPACKPHY_DX_IOCTL2_ADDR(base)            ((base) + (0x21C))

/* �Ĵ���˵����PHY PLL control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_UNION */
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_ADDR(base)    ((base) + (0x220))

/* �Ĵ���˵����PHY PLL control register 3
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_UNION */
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_ADDR(base)    ((base) + (0x224))

/* �Ĵ���˵����DATA block clock bit delay line setting
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXNCLKBDL_UNION */
#define SOC_HIPACKPHY_DX_DXNCLKBDL_ADDR(base)         ((base) + (0x230))

/* �Ĵ���˵����DX PHY control registers 
            Register in this field are connected to PHY interface directly
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXPHYCTRL_UNION */
#define SOC_HIPACKPHY_DX_DXPHYCTRL_ADDR(base)         ((base) + (0x234))

/* �Ĵ���˵����Data block PHY miscellaneous control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXNMISCCTRL0_UNION */
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_ADDR(base, p)   ((base) + (0x238+(p)*0x80))

/* �Ĵ���˵����Data block PHY miscellaneous control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXNMISCCTRL1_UNION */
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_ADDR(base, p)   ((base) + (0x264+(p)*0x80))

/* �Ĵ���˵����Data block PHY debug signals
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXDEBUG0_UNION */
#define SOC_HIPACKPHY_DX_DXDEBUG0_ADDR(base, p)       ((base) + (0x23C+(p)*0x80))

/* �Ĵ���˵����Data block PHY reserved control pins. This register is for PHY control and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXPHYRSVD_UNION */
#define SOC_HIPACKPHY_DX_DXPHYRSVD_ADDR(base, p)      ((base) + (0x244+(p)*0x80))

/* �Ĵ���˵����Data block PHY miscellaneous control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXNMISCCTRL2_UNION */
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_ADDR(base, p)   ((base) + (0x248+(p)*0x80))

/* �Ĵ���˵����Data block PHY debug/miscellaneous control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXDEBUGCONFIG_UNION */
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_ADDR(base, p)  ((base) + (0x24C+(p)*0x80))

/* �Ĵ���˵����Data block PHY DCC control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXNDCC_UNION */
#define SOC_HIPACKPHY_DX_DXNDCC_ADDR(base, p)         ((base) + (0x250+(p)*0x80))

/* �Ĵ���˵����Data block PHY debug/miscellaneous control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXNMISCCTRL3_UNION */
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_ADDR(base, p)   ((base) + (0x254+(p)*0x80))

/* �Ĵ���˵����Data block PHY debug/miscellaneous control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXNMISCCTRL4_UNION */
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_ADDR(base, p)   ((base) + (0x258+(p)*0x80))

/* �Ĵ���˵����IO control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_IOCTL3_UNION */
#define SOC_HIPACKPHY_DX_IOCTL3_ADDR(base, p)         ((base) + (0x25C+(p)*0x80))

/* �Ĵ���˵����IO control register
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_IOCTL5_UNION */
#define SOC_HIPACKPHY_DX_IOCTL5_ADDR(base)            ((base) + (0x260))

/* �Ĵ���˵����Data block PHY DCC control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXNDCC1_UNION */
#define SOC_HIPACKPHY_DX_DXNDCC1_ADDR(base, p)        ((base) + (0x268+(p)*0x80))

/* �Ĵ���˵����Data block PHY DCC control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXNDCC2_UNION */
#define SOC_HIPACKPHY_DX_DXNDCC2_ADDR(base, p)        ((base) + (0x26c+(p)*0x80))

/* �Ĵ���˵����Data block PHY DCC control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXNDCC3_UNION */
#define SOC_HIPACKPHY_DX_DXNDCC3_ADDR(base, p)        ((base) + (0x270+(p)*0x80))

/* �Ĵ���˵����Data block PHY DCC control register. This register is for PHY control, and should not be modified.
   λ����UNION�ṹ:  SOC_HIPACKPHY_DX_DXNDCC4_UNION */
#define SOC_HIPACKPHY_DX_DXNDCC4_ADDR(base, p)        ((base) + (0x274+(p)*0x80))





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
                     (1/2) register_PACK
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_REVISION_UNION
 �ṹ˵��  : REVISION �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000012�����:32
 �Ĵ���˵��: This register shows current version of the PHY Control Block
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  minor    : 8;  /* bit[0-7]  : This field shows the minor version of this PHY control block. */
        unsigned int  major    : 8;  /* bit[8-15] : This field shows the major version of this PHY control block */
        unsigned int  reserved : 16; /* bit[16-31]: -- */
    } reg;
} SOC_HIPACKPHY_REVISION_UNION;
#endif
#define SOC_HIPACKPHY_REVISION_minor_START     (0)
#define SOC_HIPACKPHY_REVISION_minor_END       (7)
#define SOC_HIPACKPHY_REVISION_major_START     (8)
#define SOC_HIPACKPHY_REVISION_major_END       (15)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYINITCTRL_UNION
 �ṹ˵��  : PHYINITCTRL �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x0000000E�����:32
 �Ĵ���˵��: This register control the initialization of the PHY. Please note that write to this register will be ignored if init_en is already at '1' state.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  init_en        : 1;  /* bit[0]    : PHY Initialization Enable. 
                                                          Writing a '1' to this field will trigger the PHY initialization seqiemce.The exact initializtion executed is specified in bits 1 ~ 15 of this register. If the PHY initialization finished, this bit will be cleared to a '0'. Please note that writing a '0' to this field takes no effect. */
        unsigned int  pll_init_en    : 1;  /* bit[1]    : PLL Initialization Enable. 
                                                          If this field is used to activate the PLL initilization. If set to a '1', the PLL will be reset, and waiting for a period of time for PLL to locked. */
        unsigned int  dlymeas_en     : 1;  /* bit[2]    : Delay Measurement Enable.
                                                          This field is used to enable if intial delay measurement of the read delay line is activated. If set to a '1', the delay measurement will be enabled. */
        unsigned int  zcal_en        : 1;  /* bit[3]    : Impedance Calibration Enable.
                                                          This field is used to specified if the impedance caliblration will be executed. This bit will be cleared to a '0', once if the impedance calibration done. */
        unsigned int  wl_en          : 1;  /* bit[4]    : Write Leveling Enable.
                                                          Writing this field to a '1' will start the write leveling sequence. This field will be cleared to a '0' after write leveling finished.
                                                          Please note that the write leveling only applied to DDR3 only. */
        unsigned int  gt_en          : 1;  /* bit[5]    : Gate Training Enable. Writing this field to a '1' will start the gate training sequence. This field will be cleared to a '0' after gate training finished. */
        unsigned int  gdst_en        : 1;  /* bit[6]    : PHY Read Data Latch Train Enable.
                                                          Writing this field to a '1' will start the read data latch position training. This field will be cleared to a '0' after GDS training finished. */
        unsigned int  wl2_en         : 1;  /* bit[7]    : Second Write Leveling Enable. 
                                                          Writing this field to a '1' will start the write latency adjustment. This field will be cleared to a '0' after adjustment finished.
                                                          Please note that the write leveing adjustment only applied to DDR3 only. */
        unsigned int  rdet_en        : 1;  /* bit[8]    : Read Data Eye Training Enable. 
                                                          Writing this field to a '1' will start the read data eye training sequence. This field will be cleared to a '0' after read data eye training finished. */
        unsigned int  wdet_en        : 1;  /* bit[9]    : Write Data Eye Training Enable. 
                                                          Writing this field to a '1' will start the write data eye training sequence. This field will be cleared to a '0' after write data eye training finished. */
        unsigned int  dram_init_en   : 1;  /* bit[10]   : DRAM Initialization Enable
                                                          This field is used to control if the internal DRAM initialization sequence will be executed after PHY initialization done. For LPDDR2/3, this field will complete the initial sequence including tINIT3~tINIT5 & tZQC. */
        unsigned int  cat_en         : 1;  /* bit[11]   : HW CA Traninig Enable.
                                                          Writing this field to a '1' will start the HW CA Training sequence. This field will be cleared to a '0' after CA Training finished.
                                                          Please note that the CA Training only applied to LPDDR3 only. */
        unsigned int  dram_rst       : 1;  /* bit[12]   : DRAM Reset. 
                                                          This field is used to initiate the DRAM reset sequence. If this field is set to a '1', the RESET# and CKE will be pulled LOW for t_dram_rst. After t_dram_rst, the CKE RESET# was pulled to HIGH while keeping CKE at LOW for t_cke_low. After t_cke_low, the the CKE was pulled to HIGH, and after t_cke_high, this field is cleared to '0' automatically. For LPDDR2/3, only the CKE will be active during DRAM reset sequence. */
        unsigned int  phy_rst        : 1;  /* bit[13]   : PHY Reset. 
                                                          This field is used to set PHY reset signal. To issue reset signal to PHY, this field should be set to a '1'. To end the reset signal to PHY this field should be cleared to a '0'. 
                                                          Please note that the reset signal connect to A/C block and all of the Data blocks. */
        unsigned int  pack_rst       : 1;  /* bit[14]   : PACK Reset.
                                                          This field is used to issue reset to the all digital circuit of the PACK including register file. If this field is set to a '1', all of the digital part, including control register, of the PHY will be set to default value. The reset will be automatically executed, and this bit will be cleared to a '0' after reset finished. */
        unsigned int  phyconn_rst    : 1;  /* bit[15]   : PHY Counter Reset. 
                                                          This field is used to set PHY counter reset signal. To issue reset signal to PHY counter, this field should be set to a '1'. To end the reset signal to PHY counter this field should be cleared to a '0'. 
                                                          Please note that the reset signal connect to A/C block counter and all of the Data blocks counter. */
        unsigned int  dvreft_en      : 1;  /* bit[16]   : DRAM VREF(DQ) Training Enable.
                                                          Writing this field to a '1' will start the DRAM VREF(DQ) training sequence. This field will be cleared to a '0' after the DRAM VREF(DQ) training finished. */
        unsigned int  hvreft_en      : 1;  /* bit[17]   : Host VREF(DQ) Training Enable.
                                                          Writing this field to a '1' will start the host VREF(DQ) training sequence. This field will be cleared to a '0' after the host VREF training finished. */
        unsigned int  dxdvrefs_en    : 1;  /* bit[18]   : DRAM VREF(DQ) Synchronize Operations.
                                                          This field controls if MRS with VREF value specified in the DVREFT_STATUS.vrftres_dvref should be synchronize to the DRAM. This operation usually used for the user to synchronize the newly assigned VREF value to DRAM after VREF training.
                                                          Note that if DDR4 configured, the VREF(DQ) synchronization will turn-on PDA function automatically. For non-PDA mode or DRAM type other than DDR4, the user must use SMR from Memory Controller to set the VREF value to DRAM. */
        unsigned int  acdvreft_en    : 1;  /* bit[19]   : DRAM VREF(AC) Training Enable.
                                                          Writing this field to a '1' will start the DRAM VREF(AC) training sequence. This field will be cleared to a '0' after the DRAM VREF(AC) training finished. */
        unsigned int  achvreft_en    : 1;  /* bit[20]   : Host VREF(AC) Training Enable.
                                                          Writing this field to a '1' will start the host VREF(AC) training sequence. This field will be cleared to a '0' after the host VREF training finished. */
        unsigned int  acdvrefs_en    : 1;  /* bit[21]   : DRAM VREF(AC) Synchronize Operations.
                                                          This field controls if DQS toggling with VREF value specified in the ADVREF_STATUS.ac_vrftres_dvref should be synchronize to the DRAM.  */
        unsigned int  reserved       : 9;  /* bit[22-30]: -- */
        unsigned int  ctl_cke_bypass : 1;  /* bit[31]   : PACK's CKE bypass function enable.
                                                          1'b1: CKE was controlled by MC even when PACK controls the DFI interface
                                                          1'b0: CKE was controlled by PACK when PACK controls the DFI interface */
    } reg;
} SOC_HIPACKPHY_PHYINITCTRL_UNION;
#endif
#define SOC_HIPACKPHY_PHYINITCTRL_init_en_START         (0)
#define SOC_HIPACKPHY_PHYINITCTRL_init_en_END           (0)
#define SOC_HIPACKPHY_PHYINITCTRL_pll_init_en_START     (1)
#define SOC_HIPACKPHY_PHYINITCTRL_pll_init_en_END       (1)
#define SOC_HIPACKPHY_PHYINITCTRL_dlymeas_en_START      (2)
#define SOC_HIPACKPHY_PHYINITCTRL_dlymeas_en_END        (2)
#define SOC_HIPACKPHY_PHYINITCTRL_zcal_en_START         (3)
#define SOC_HIPACKPHY_PHYINITCTRL_zcal_en_END           (3)
#define SOC_HIPACKPHY_PHYINITCTRL_wl_en_START           (4)
#define SOC_HIPACKPHY_PHYINITCTRL_wl_en_END             (4)
#define SOC_HIPACKPHY_PHYINITCTRL_gt_en_START           (5)
#define SOC_HIPACKPHY_PHYINITCTRL_gt_en_END             (5)
#define SOC_HIPACKPHY_PHYINITCTRL_gdst_en_START         (6)
#define SOC_HIPACKPHY_PHYINITCTRL_gdst_en_END           (6)
#define SOC_HIPACKPHY_PHYINITCTRL_wl2_en_START          (7)
#define SOC_HIPACKPHY_PHYINITCTRL_wl2_en_END            (7)
#define SOC_HIPACKPHY_PHYINITCTRL_rdet_en_START         (8)
#define SOC_HIPACKPHY_PHYINITCTRL_rdet_en_END           (8)
#define SOC_HIPACKPHY_PHYINITCTRL_wdet_en_START         (9)
#define SOC_HIPACKPHY_PHYINITCTRL_wdet_en_END           (9)
#define SOC_HIPACKPHY_PHYINITCTRL_dram_init_en_START    (10)
#define SOC_HIPACKPHY_PHYINITCTRL_dram_init_en_END      (10)
#define SOC_HIPACKPHY_PHYINITCTRL_cat_en_START          (11)
#define SOC_HIPACKPHY_PHYINITCTRL_cat_en_END            (11)
#define SOC_HIPACKPHY_PHYINITCTRL_dram_rst_START        (12)
#define SOC_HIPACKPHY_PHYINITCTRL_dram_rst_END          (12)
#define SOC_HIPACKPHY_PHYINITCTRL_phy_rst_START         (13)
#define SOC_HIPACKPHY_PHYINITCTRL_phy_rst_END           (13)
#define SOC_HIPACKPHY_PHYINITCTRL_pack_rst_START        (14)
#define SOC_HIPACKPHY_PHYINITCTRL_pack_rst_END          (14)
#define SOC_HIPACKPHY_PHYINITCTRL_phyconn_rst_START     (15)
#define SOC_HIPACKPHY_PHYINITCTRL_phyconn_rst_END       (15)
#define SOC_HIPACKPHY_PHYINITCTRL_dvreft_en_START       (16)
#define SOC_HIPACKPHY_PHYINITCTRL_dvreft_en_END         (16)
#define SOC_HIPACKPHY_PHYINITCTRL_hvreft_en_START       (17)
#define SOC_HIPACKPHY_PHYINITCTRL_hvreft_en_END         (17)
#define SOC_HIPACKPHY_PHYINITCTRL_dxdvrefs_en_START     (18)
#define SOC_HIPACKPHY_PHYINITCTRL_dxdvrefs_en_END       (18)
#define SOC_HIPACKPHY_PHYINITCTRL_acdvreft_en_START     (19)
#define SOC_HIPACKPHY_PHYINITCTRL_acdvreft_en_END       (19)
#define SOC_HIPACKPHY_PHYINITCTRL_achvreft_en_START     (20)
#define SOC_HIPACKPHY_PHYINITCTRL_achvreft_en_END       (20)
#define SOC_HIPACKPHY_PHYINITCTRL_acdvrefs_en_START     (21)
#define SOC_HIPACKPHY_PHYINITCTRL_acdvrefs_en_END       (21)
#define SOC_HIPACKPHY_PHYINITCTRL_ctl_cke_bypass_START  (31)
#define SOC_HIPACKPHY_PHYINITCTRL_ctl_cke_bypass_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYINITSTATUS_UNION
 �ṹ˵��  : PHYINITSTATUS �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register shows the PHY status.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0     : 1;  /* bit[0]    : -- */
        unsigned int  pll_lock_err   : 1;  /* bit[1]    : PLL Locked Fail.
                                                          This flag indicate if one of the PLL within the PHY fail to assert locked flag after t_pll_lock timer.
                                                          The error status is cleard by writing a '1' to this field. */
        unsigned int  dlymeas_err    : 1;  /* bit[2]    : Delay Measurement Fail.
                                                          This flag indicate if one of the initial delay measurement failed. The error status is cleard by writing a '1' to this field. */
        unsigned int  zcal_err       : 1;  /* bit[3]    : Impedance Calibration Error.
                                                          This flag indicate if an error happened during impedance calibration. The error status is cleard by writing a '1' to this field. */
        unsigned int  wl_err         : 1;  /* bit[4]    : Write Leveling Error.
                                                          This flag indicate if an error happened during write leveling. The error status is cleard by writing a '1' to this field. */
        unsigned int  gt_err         : 1;  /* bit[5]    : Gate Training Error.
                                                          This flag indicate if an error happened during gate training. The error status is cleard by writing a '1' to this field. */
        unsigned int  gdst_err       : 1;  /* bit[6]    : PHY Read Data Latch Train Error.
                                                          This flag indicate if an error happened during read data latch training. This error status is cleared by writing a '1' to this field. */
        unsigned int  wl2_err        : 1;  /* bit[7]    : Write Leveling Adjustment Error.
                                                          This flag indicate if an error happened during write leveling adjustment. The error status is cleard by writing a '1' to this field. */
        unsigned int  rdet_err       : 1;  /* bit[8]    : Read Data Eye Calibration Error.
                                                          This flag indicate if an error happened during read data eye calibration. The error status is cleard by writing a '1' to this field. */
        unsigned int  wdet_err       : 1;  /* bit[9]    : Write Data Eye Calibration Error.
                                                          This flag indicate if an error happened during write data eye calibration. The error status is cleard by writing a '1' to this field. */
        unsigned int  cat_err        : 1;  /* bit[10]   : CA Training Error.
                                                          This flag indicate if an error happened during CA Trainig. The error status is cleard by writing a '1' to this field. */
        unsigned int  fst_rdet_wrg   : 1;  /* bit[11]   : Fast read data eye training warning.
                                                          This flag indicate if any change happened during fast read eye trainig or read data eye re-training. The status is cleard by writing a '1' to this field. */
        unsigned int  fst_rdet_err   : 1;  /* bit[12]   : Fast read data eye training error.
                                                          This flag indicate if right and left side both fail during fast read eye trainig or read data eye re-training. The status is cleard by writing a '1' to this field. */
        unsigned int  wdert_wrg      : 1;  /* bit[13]   : Write data eye retraining warning.
                                                          This flag indicate if any change happened during write eye retrainig. The status is cleard by writing a '1' to this field. */
        unsigned int  wdert_err      : 1;  /* bit[14]   : Write data eye retraining error.
                                                          This flag indicate if right and left side both fail during write eye retrainig. The status is cleard by writing a '1' to this field. */
        unsigned int  reserved_1     : 16; /* bit[15-30]:  */
        unsigned int  retrain_active : 1;  /* bit[31]   : Retrain active flag. Indicate if PACK is under the retrain stage.
                                                          1: retrain is active
                                                          0: retrain is not active */
    } reg;
} SOC_HIPACKPHY_PHYINITSTATUS_UNION;
#endif
#define SOC_HIPACKPHY_PHYINITSTATUS_pll_lock_err_START    (1)
#define SOC_HIPACKPHY_PHYINITSTATUS_pll_lock_err_END      (1)
#define SOC_HIPACKPHY_PHYINITSTATUS_dlymeas_err_START     (2)
#define SOC_HIPACKPHY_PHYINITSTATUS_dlymeas_err_END       (2)
#define SOC_HIPACKPHY_PHYINITSTATUS_zcal_err_START        (3)
#define SOC_HIPACKPHY_PHYINITSTATUS_zcal_err_END          (3)
#define SOC_HIPACKPHY_PHYINITSTATUS_wl_err_START          (4)
#define SOC_HIPACKPHY_PHYINITSTATUS_wl_err_END            (4)
#define SOC_HIPACKPHY_PHYINITSTATUS_gt_err_START          (5)
#define SOC_HIPACKPHY_PHYINITSTATUS_gt_err_END            (5)
#define SOC_HIPACKPHY_PHYINITSTATUS_gdst_err_START        (6)
#define SOC_HIPACKPHY_PHYINITSTATUS_gdst_err_END          (6)
#define SOC_HIPACKPHY_PHYINITSTATUS_wl2_err_START         (7)
#define SOC_HIPACKPHY_PHYINITSTATUS_wl2_err_END           (7)
#define SOC_HIPACKPHY_PHYINITSTATUS_rdet_err_START        (8)
#define SOC_HIPACKPHY_PHYINITSTATUS_rdet_err_END          (8)
#define SOC_HIPACKPHY_PHYINITSTATUS_wdet_err_START        (9)
#define SOC_HIPACKPHY_PHYINITSTATUS_wdet_err_END          (9)
#define SOC_HIPACKPHY_PHYINITSTATUS_cat_err_START         (10)
#define SOC_HIPACKPHY_PHYINITSTATUS_cat_err_END           (10)
#define SOC_HIPACKPHY_PHYINITSTATUS_fst_rdet_wrg_START    (11)
#define SOC_HIPACKPHY_PHYINITSTATUS_fst_rdet_wrg_END      (11)
#define SOC_HIPACKPHY_PHYINITSTATUS_fst_rdet_err_START    (12)
#define SOC_HIPACKPHY_PHYINITSTATUS_fst_rdet_err_END      (12)
#define SOC_HIPACKPHY_PHYINITSTATUS_wdert_wrg_START       (13)
#define SOC_HIPACKPHY_PHYINITSTATUS_wdert_wrg_END         (13)
#define SOC_HIPACKPHY_PHYINITSTATUS_wdert_err_START       (14)
#define SOC_HIPACKPHY_PHYINITSTATUS_wdert_err_END         (14)
#define SOC_HIPACKPHY_PHYINITSTATUS_retrain_active_START  (31)
#define SOC_HIPACKPHY_PHYINITSTATUS_retrain_active_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYCLKGATED_UNION
 �ṹ˵��  : PHYCLKGATED �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x40302000�����:32
 �Ĵ���˵��: This register control the clock gated of PHY
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dx_phy_clkgated : 4;  /* bit[0-3]  : Clock gated for circuits in DAT blocks
                                                           1: Clock is enabled
                                                           0: Clock is gated
                                                           Note: These bits are automatically set as '1' when PLL is clocked without error */
        unsigned int  reserved_0      : 4;  /* bit[4-7]  :  */
        unsigned int  ac_phy_clkgated : 1;  /* bit[8]    : Clock gated for the circuits in AC block except CK and CK related circuits
                                                           1: Clock is enabled
                                                           0: Clock is gated
                                                           Note: This bit is automatically set as '1' when PLL is clocked without error */
        unsigned int  ck_phy_clkgated : 4;  /* bit[9-12] : Dedicated clock gated control for the output CK and releated circuits
                                                           1: Clock is enabled
                                                           0: Clock is gated
                                                           Note: This bit is automatically set as '1' when PLL is clocked without error */
        unsigned int  dx_phgated_en   : 1;  /* bit[13]   : PHY Phase Clock Gated Function (automatically controlled by PACK's FSM) Enabled.
                                                           1: enable
                                                           0: disable */
        unsigned int  dx_phclkgated   : 1;  /* bit[14]   : PHY Phase Clock Gated control. This filed takes effect only when dx_phgated_en=1'b0. If dx_phgated_en='1b1, this field will be used and the gated function is automatically controlled by PACK's FSM. 
                                                           1: Clock enable 
                                                           0: Clock disable */
        unsigned int  dx_phgated_men  : 1;  /* bit[15]   : PHY Phase Clock Gated manual control enable. This filed takes effect only when dx_phgated_en=1'b0. If dx_phgated_en is HIGH and this filed is HIGH, the user can use dx_phclkgated to manually control the clock gating of PHY Phase Clock. 
                                                           1: enable manual control
                                                           0: disable manual control */
        unsigned int  cfg_tx_rx_gcnt  : 8;  /* bit[16-23]: tx/rx data gating counter. Ths field indicate the length of gating signal for tx/rx data in RS.
                                                           Note1: Set 0 to make gating signal always be high in bypass mode or DRAM WL is less than 6.
                                                           Note2: User must consider read/write latency to guarantee valid data can be gated by gating signal. If (RL/WL + (RS+1)*2) bigger then the default value, user must enlarge it. */
        unsigned int  reserved_1      : 6;  /* bit[24-29]:  */
        unsigned int  cfg_gcken_ca_rs : 1;  /* bit[30]   : Gating control for ca signal in RS.
                                                           Free run in default setting */
        unsigned int  byp_pll_lock    : 1;  /* bit[31]   : Bypass the pll lock signal. Users can assert this field to bypass pll lock signal when doing the pll re-lock procedure in the bypass mode (DFS) or when the pll lock signal can not be used.
                                                           1: Bypass the pll lock (do not use the pll lock singal to gate the PHY clocks)
                                                           0: Use the pll lock to gate the PHY clocks to prevent clock glitch */
    } reg;
} SOC_HIPACKPHY_PHYCLKGATED_UNION;
#endif
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phy_clkgated_START  (0)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phy_clkgated_END    (3)
#define SOC_HIPACKPHY_PHYCLKGATED_ac_phy_clkgated_START  (8)
#define SOC_HIPACKPHY_PHYCLKGATED_ac_phy_clkgated_END    (8)
#define SOC_HIPACKPHY_PHYCLKGATED_ck_phy_clkgated_START  (9)
#define SOC_HIPACKPHY_PHYCLKGATED_ck_phy_clkgated_END    (12)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phgated_en_START    (13)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phgated_en_END      (13)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phclkgated_START    (14)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phclkgated_END      (14)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phgated_men_START   (15)
#define SOC_HIPACKPHY_PHYCLKGATED_dx_phgated_men_END     (15)
#define SOC_HIPACKPHY_PHYCLKGATED_cfg_tx_rx_gcnt_START   (16)
#define SOC_HIPACKPHY_PHYCLKGATED_cfg_tx_rx_gcnt_END     (23)
#define SOC_HIPACKPHY_PHYCLKGATED_cfg_gcken_ca_rs_START  (30)
#define SOC_HIPACKPHY_PHYCLKGATED_cfg_gcken_ca_rs_END    (30)
#define SOC_HIPACKPHY_PHYCLKGATED_byp_pll_lock_START     (31)
#define SOC_HIPACKPHY_PHYCLKGATED_byp_pll_lock_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYTIMER0_UNION
 �ṹ˵��  : PHYTIMER0 �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x2710000F�����:32
 �Ĵ���˵��: This register specified the timing parameter required by the PHY.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_dram_reset    : 8;  /* bit[0-7]  : DDR3 DRAM Reset. This field is used to specify the time issuing RESET signaling to the DRAM (number of PCLK clock cycles). */
        unsigned int  reserved        : 4;  /* bit[8-11] : -- */
        unsigned int  t_dram_cke_high : 20; /* bit[12-31]: DRAM CKE High Initialization.
                                                           This field sepcify the number of PCLK clock cycles of first DRAM command from CKE pulled to HIGH. (LPDDR23 tINIT3) */
    } reg;
} SOC_HIPACKPHY_PHYTIMER0_UNION;
#endif
#define SOC_HIPACKPHY_PHYTIMER0_t_dram_reset_START     (0)
#define SOC_HIPACKPHY_PHYTIMER0_t_dram_reset_END       (7)
#define SOC_HIPACKPHY_PHYTIMER0_t_dram_cke_high_START  (12)
#define SOC_HIPACKPHY_PHYTIMER0_t_dram_cke_high_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYTIMER1_UNION
 �ṹ˵��  : PHYTIMER1 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00002000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_dram_cke_low : 20; /* bit[0-19] : DRAM CKE Low Initialization.
                                                          This field sepcify the number of PCLK clock cycles which CKE should be kept LOW after reset power and clock stable.  */
        unsigned int  reserved       : 12; /* bit[20-31]: -- */
    } reg;
} SOC_HIPACKPHY_PHYTIMER1_UNION;
#endif
#define SOC_HIPACKPHY_PHYTIMER1_t_dram_cke_low_START  (0)
#define SOC_HIPACKPHY_PHYTIMER1_t_dram_cke_low_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PLLCTRL_UNION
 �ṹ˵��  : PLLCTRL �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000300�����:32
 �Ĵ���˵��: This register specified the timing paramters for PLL in both address /command, and data block.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pll_pwdn            : 3;  /* bit[0-2]  : PLL Power Down.
                                                               This field is used to set the power down status of the PLL input. If this field is set to a '1', the PLL power down pin will be activated. Writing a '0' to this field will remove the deactivated the PLL power down pin.
                                                               Bit[2] for AC PLL
                                                               Bit[1] for DX1 (DATA1) PLL
                                                               Bit[0] for DX0 (DATA0) PLL */
        unsigned int  reserved_0          : 1;  /* bit[3]    : -- */
        unsigned int  pll_freq_range      : 2;  /* bit[4-5]  : PLL Frequency Range Select.
                                                               This field specify the frequency input range of the PLLs. */
        unsigned int  ac_pll_bp_refpfd    : 1;  /* bit[6]    : Reference to PLL datasheet. Move to AC_Static_Reg */
        unsigned int  ac_pll_bp_refvco    : 1;  /* bit[7]    : Reference to PLL datasheet. Move to AC_Static_Reg */
        unsigned int  ac_pll_enphsel      : 1;  /* bit[8]    : Reference to PLL datasheet. Move to AC_Static_Reg */
        unsigned int  ac_pll_en_cal       : 1;  /* bit[9]    : Reference to PLL datasheet. Move to AC_Static_Reg */
        unsigned int  ac_pll_initsel      : 1;  /* bit[10]   : Reference to PLL datasheet. Move to AC_Static_Reg */
        unsigned int  ac_pll_lockt_sel    : 1;  /* bit[11]   : Reference to PLL datasheet. Move to AC_Static_Reg */
        unsigned int  ac_pll_fopetestfb   : 1;  /* bit[12]   : Reference to PLL datasheet. Move to AC_Static_Reg */
        unsigned int  ac_pll_fopetestref  : 1;  /* bit[13]   : Reference to PLL datasheet. Move to AC_Static_Reg */
        unsigned int  ac_pll_lockin       : 1;  /* bit[14]   : Reference to PLL datasheet. Move to AC_Static_Reg */
        unsigned int  ac_pll_outn         : 1;  /* bit[15]   : Reference to PLL datasheet */
        unsigned int  ac_pll_outp         : 1;  /* bit[16]   : Reference to PLL datasheet */
        unsigned int  reserved_1          : 7;  /* bit[17-23]:  */
        unsigned int  dx_pll_powerdown_23 : 2;  /* bit[24-25]: PLL Power Down.
                                                               This field is used to set the power down status of the PLL input. If this field is set to a '1', the PLL power down pin will be activated. Writing a '0' to this field will remove the deactivated the PLL power down pin.
                                                               Bit[1] for DX1 (DATA3) PLL
                                                               Bit[0] for DX0 (DATA2) PLL */
        unsigned int  reserved_2          : 2;  /* bit[26-27]:  */
        unsigned int  dx_pll_powerdown_47 : 4;  /* bit[28-31]: PLL Power Down.
                                                               This field is used to set the power down status of the PLL input. If this field is set to a '1', the PLL power down pin will be activated. Writing a '0' to this field will remove the deactivated the PLL power down pin.
                                                               Bit[3] for DX3 (DATA7) PLL
                                                               Bit[2] for DX2 (DATA6) PLL
                                                               Bit[1] for DX1 (DATA5) PLL
                                                               Bit[0] for DX0 (DATA4) PLL */
    } reg;
} SOC_HIPACKPHY_PLLCTRL_UNION;
#endif
#define SOC_HIPACKPHY_PLLCTRL_pll_pwdn_START             (0)
#define SOC_HIPACKPHY_PLLCTRL_pll_pwdn_END               (2)
#define SOC_HIPACKPHY_PLLCTRL_pll_freq_range_START       (4)
#define SOC_HIPACKPHY_PLLCTRL_pll_freq_range_END         (5)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_bp_refpfd_START     (6)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_bp_refpfd_END       (6)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_bp_refvco_START     (7)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_bp_refvco_END       (7)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_enphsel_START       (8)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_enphsel_END         (8)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_en_cal_START        (9)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_en_cal_END          (9)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_initsel_START       (10)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_initsel_END         (10)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_lockt_sel_START     (11)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_lockt_sel_END       (11)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_fopetestfb_START    (12)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_fopetestfb_END      (12)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_fopetestref_START   (13)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_fopetestref_END     (13)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_lockin_START        (14)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_lockin_END          (14)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_outn_START          (15)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_outn_END            (15)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_outp_START          (16)
#define SOC_HIPACKPHY_PLLCTRL_ac_pll_outp_END            (16)
#define SOC_HIPACKPHY_PLLCTRL_dx_pll_powerdown_23_START  (24)
#define SOC_HIPACKPHY_PLLCTRL_dx_pll_powerdown_23_END    (25)
#define SOC_HIPACKPHY_PLLCTRL_dx_pll_powerdown_47_START  (28)
#define SOC_HIPACKPHY_PLLCTRL_dx_pll_powerdown_47_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PLLTIMER_UNION
 �ṹ˵��  : PLLTIMER �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x4E200080�����:32
 �Ĵ���˵��: This register specified the control for PLL in both address /command, and data block.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_pll_rst  : 8;  /* bit[0-7]  : PLL Reset Time.
                                                      This field specified the number of PCLK clock cycles to issue reset to the PLL.  */
        unsigned int  reserved   : 8;  /* bit[8-15] : -- */
        unsigned int  t_pll_lock : 16; /* bit[16-31]: PLL Lock Time.
                                                      This field specified the number of PCLK clock cycles wait for the PLLs to be locked. */
    } reg;
} SOC_HIPACKPHY_PLLTIMER_UNION;
#endif
#define SOC_HIPACKPHY_PLLTIMER_t_pll_rst_START   (0)
#define SOC_HIPACKPHY_PLLTIMER_t_pll_rst_END     (7)
#define SOC_HIPACKPHY_PLLTIMER_t_pll_lock_START  (16)
#define SOC_HIPACKPHY_PLLTIMER_t_pll_lock_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DLYMEASCTRL_UNION
 �ṹ˵��  : DLYMEASCTRL �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x0C000471�����:32
 �Ĵ���˵��: This register specify the control for delay measurement of the read delay line.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dly_meas_type       : 1;  /* bit[0]    : Delay Measurement Type Control.
                                                               This field sould be used with dly_meas_type_2T.
                                                               {dly_meas_type_2T,dly_meas_type}:
                                                               2'b11: delay measure for 3T
                                                               2'b10: delay measure for 2T
                                                               2'b01: delay measure for 1T
                                                               2'b00: delay measure for 0.5T
                                                               3T type only be supported in high frequency, upper 1866 */
        unsigned int  dly_track_type      : 1;  /* bit[1]    : Delay Tracking Type.
                                                               This field specify if priority updated from the PHY was used while dynamic tracking. If this field is set to a '1', the priority update from the PHY is used. */
        unsigned int  dlytrack_dqsgth     : 2;  /* bit[2-3]  : Dynamic DQSG Update Threshold.
                                                               This field specify the number of taps accumulated before to update the RDQSG delay line.
                                                               2,3: means update every time
                                                               1: means update every 2 times
                                                               0: means update 4 times */
        unsigned int  dynamic_dqsgen      : 1;  /* bit[4]    : Dynamic DQSG Tracking Enable.
                                                               Note:
                                                               if phy side dxctl_reg_DQSG_extend_en_DQS=0x1 (DQSG extend function enabled), this field shoud be set as 0x0 (desabled) */
        unsigned int  dynamic_dqsen       : 1;  /* bit[5]    : Dynamic DQS Tracking Enable.
                                                               This field should be set as HIGH when delay measurement. */
        unsigned int  phy_autoref_en      : 1;  /* bit[6]    : PHY Auto-Refresh Tracking Enable. */
        unsigned int  dly_meas_type_2t    : 1;  /* bit[7]    : Delay Measurement Type Control.
                                                               This field sould be used with dly_meas_type.
                                                               {dly_meas_type_2T,dly_meas_type}:
                                                               2'b11: delay measure for 3T
                                                               2'b10: delay measure for 2T
                                                               2'b01: delay measure for 1T
                                                               2'b00: delay measure for 0.5T
                                                               3T type only be supported in high frequency, upper 1866 */
        unsigned int  dly_track_limit     : 7;  /* bit[8-14] : Delay Tracking Limit.
                                                               This field specify the maximum number of accumulated taps allowed while dynamic tracking.  */
        unsigned int  reserved_0          : 1;  /* bit[15]   :  */
        unsigned int  dynamic_dqsg_ph_dis : 1;  /* bit[16]   : Dynamic DQSG Tracking phase-tuning disable.
                                                               1: disable tuning rdqsgphase during tracking
                                                               0: enable tuning rdqsgphase during tracking when dynamic_dqsgen=0x1 (default)
                                                               Note: when dynamic_dqsg_ph_dis=0x0, gtrten should be set as 0x0 */
        unsigned int  reserved_1          : 3;  /* bit[17-19]:  */
        unsigned int  dlytrack_dqsth      : 2;  /* bit[20-21]: Dynamic DQS Update Threshold.
                                                               This field specify the number of taps accumulated before to update the RDQS delay line.
                                                               2,3: means update every time
                                                               1: means update every 2 times
                                                               0: means update 4 times
                                                               Note: if dly_track_type=0x1, this field will not take effect. */
        unsigned int  dlytrack_dqsg_tap   : 2;  /* bit[22-23]: Dynamic tracking DQSG Tap.
                                                               0: +/- 1 (default)
                                                               1: +/- 2
                                                               2: +/- 3
                                                               3: +/- 4 */
        unsigned int  dlytrack_dqs_tap    : 2;  /* bit[24-25]: Dynamic tracking DQS Tap.
                                                               0: +/- 1 (default for dlymeas_type = 1T)
                                                               1: +/- 2
                                                               2: +/- 3
                                                               3: +/- 4 */
        unsigned int  dlytrack_cyc_tap    : 4;  /* bit[26-29]: Dynamic tracking DQSCYC Tap.
                                                               0: +/- 1
                                                               1: +/- 2
                                                               2: +/- 3
                                                               3: +/- 4 (default for dlymeas_type = 1T)
                                                               N: +/- (N+1) */
        unsigned int  rdqsg_mondly_type   : 2;  /* bit[30-31]: RDQSG Monitor(Tracking) type.
                                                               This field specify the RDQSG monitor type for rdqsgphase dynamic tracking. The rdqsgphase will be updated according to this type in gate re-train. Must set to 0 for DDR3/4
                                                               0: 30 degree (default)
                                                               1: 60 degree
                                                               2: 90 degree (for PLL low power mode - only 0/90/180/270)
                                                               3: reserved (do not use) */
    } reg;
} SOC_HIPACKPHY_DLYMEASCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_meas_type_START        (0)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_meas_type_END          (0)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_track_type_START       (1)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_track_type_END         (1)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqsgth_START      (2)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqsgth_END        (3)
#define SOC_HIPACKPHY_DLYMEASCTRL_dynamic_dqsgen_START       (4)
#define SOC_HIPACKPHY_DLYMEASCTRL_dynamic_dqsgen_END         (4)
#define SOC_HIPACKPHY_DLYMEASCTRL_dynamic_dqsen_START        (5)
#define SOC_HIPACKPHY_DLYMEASCTRL_dynamic_dqsen_END          (5)
#define SOC_HIPACKPHY_DLYMEASCTRL_phy_autoref_en_START       (6)
#define SOC_HIPACKPHY_DLYMEASCTRL_phy_autoref_en_END         (6)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_meas_type_2t_START     (7)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_meas_type_2t_END       (7)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_track_limit_START      (8)
#define SOC_HIPACKPHY_DLYMEASCTRL_dly_track_limit_END        (14)
#define SOC_HIPACKPHY_DLYMEASCTRL_dynamic_dqsg_ph_dis_START  (16)
#define SOC_HIPACKPHY_DLYMEASCTRL_dynamic_dqsg_ph_dis_END    (16)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqsth_START       (20)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqsth_END         (21)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqsg_tap_START    (22)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqsg_tap_END      (23)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqs_tap_START     (24)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_dqs_tap_END       (25)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_cyc_tap_START     (26)
#define SOC_HIPACKPHY_DLYMEASCTRL_dlytrack_cyc_tap_END       (29)
#define SOC_HIPACKPHY_DLYMEASCTRL_rdqsg_mondly_type_START    (30)
#define SOC_HIPACKPHY_DLYMEASCTRL_rdqsg_mondly_type_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_IMPCTRL_UNION
 �ṹ˵��  : IMPCTRL �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x8C008220�����:32
 �Ĵ���˵��: This register specify the control the ZQ calibration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  zcomp_rsp_dly       : 6;  /* bit[0-5]  : ZQ Comparator Response Time.
                                                               This field specify the delay that the zcomp result after apply the zctrl. */
        unsigned int  tzcomp_upddly       : 6;  /* bit[6-11] : ZCALRT Waiting Timer after Update Driving (Unit: pclk) */
        unsigned int  zcomp_num           : 4;  /* bit[12-15]: ZQ Comparator iteration Time.
                                                               This field specify the iteration time of zcomp changing detection. */
        unsigned int  zcalrt_range        : 6;  /* bit[16-21]: ZCALRT Update Driving when Difference > zcalrt_range */
        unsigned int  reserved            : 4;  /* bit[22-25]: -- */
        unsigned int  zcal_platch_inv     : 1;  /* bit[26]   : ZQCAL P Latch Code Inversion
                                                               0: Not Invert
                                                               1: Invert P-Latch Code Used in LPDDR4 for I/O Workaround */
        unsigned int  zcal_pnsequence     : 1;  /* bit[27]   : ZQCAL P/N Calibration Sequence
                                                               1: P->N
                                                               0: N->P (K3V5 LPDDR3/4 I/O) */
        unsigned int  zcal_errstopup      : 1;  /* bit[28]   : ZCAL stop to update code when error.
                                                               1: stop to update code when error
                                                               0: update code even when error */
        unsigned int  zcalrt_updckelh_dis : 1;  /* bit[29]   : ZCALRT Update Driving Control
                                                               1'b1: Update Driving but not De-Assert/Assert CKE
                                                               1'b0: CKE Low, Update Driving, CKE High */
        unsigned int  zcalrt_en           : 1;  /* bit[30]   : ZCAL Re-Train Enable, Need to Enable 'retrain_en' First */
        unsigned int  zcfuzzy_en          : 1;  /* bit[31]   : ZQ Comparator result selection by weighted method. When disable this function the precision could be improved but has the possibility to get failed ZQ Comparison. When enable this function it can be guaranteed to get successful ZQ Comparion.
                                                               0: disable
                                                               1: enable (default) */
    } reg;
} SOC_HIPACKPHY_IMPCTRL_UNION;
#endif
#define SOC_HIPACKPHY_IMPCTRL_zcomp_rsp_dly_START        (0)
#define SOC_HIPACKPHY_IMPCTRL_zcomp_rsp_dly_END          (5)
#define SOC_HIPACKPHY_IMPCTRL_tzcomp_upddly_START        (6)
#define SOC_HIPACKPHY_IMPCTRL_tzcomp_upddly_END          (11)
#define SOC_HIPACKPHY_IMPCTRL_zcomp_num_START            (12)
#define SOC_HIPACKPHY_IMPCTRL_zcomp_num_END              (15)
#define SOC_HIPACKPHY_IMPCTRL_zcalrt_range_START         (16)
#define SOC_HIPACKPHY_IMPCTRL_zcalrt_range_END           (21)
#define SOC_HIPACKPHY_IMPCTRL_zcal_platch_inv_START      (26)
#define SOC_HIPACKPHY_IMPCTRL_zcal_platch_inv_END        (26)
#define SOC_HIPACKPHY_IMPCTRL_zcal_pnsequence_START      (27)
#define SOC_HIPACKPHY_IMPCTRL_zcal_pnsequence_END        (27)
#define SOC_HIPACKPHY_IMPCTRL_zcal_errstopup_START       (28)
#define SOC_HIPACKPHY_IMPCTRL_zcal_errstopup_END         (28)
#define SOC_HIPACKPHY_IMPCTRL_zcalrt_updckelh_dis_START  (29)
#define SOC_HIPACKPHY_IMPCTRL_zcalrt_updckelh_dis_END    (29)
#define SOC_HIPACKPHY_IMPCTRL_zcalrt_en_START            (30)
#define SOC_HIPACKPHY_IMPCTRL_zcalrt_en_END              (30)
#define SOC_HIPACKPHY_IMPCTRL_zcfuzzy_en_START           (31)
#define SOC_HIPACKPHY_IMPCTRL_zcfuzzy_en_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_IMPSTATUS_UNION
 �ṹ˵��  : IMPSTATUS �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00200020�����:32
 �Ĵ���˵��: This register specify the ZQ calibration result.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  zcode_ndrv      : 6;  /* bit[0-5]  : N-Drive Impedance Control Code.
                                                           This field is used to specify the n-driver impedance control code. This register will be update by user or will be updated every time the ZQ calibration doen. */
        unsigned int  reserved_0      : 1;  /* bit[6]    :  */
        unsigned int  ndrv_cal_result : 1;  /* bit[7]    : N-Drive Calibration Result.
                                                           This field specify the ZQ calibration result. The valid encoding is:
                                                           0: Calibration done with OK.
                                                           1: Calibration down with Error.
                                                           Writing an '1' to this field will clear this field to a '0'. */
        unsigned int  zcode_ndrv_cal  : 7;  /* bit[8-14] : N-Drive Impedance Calibration Code.
                                                           This field shows the n-driver calibration code during impedance calibration. */
        unsigned int  reserved_1      : 1;  /* bit[15]   : -- */
        unsigned int  zcode_pdrv      : 6;  /* bit[16-21]: P-Drive Impedance Control Code.
                                                           This field is used to specify the p-driver impedance control code. This register will be update by user or will be updated every time the ZQ calibration doen. */
        unsigned int  reserved_2      : 1;  /* bit[22]   :  */
        unsigned int  pdrv_cal_result : 1;  /* bit[23]   : P-Drive Calibration Result.
                                                           This field specify the ZQ calibration result. The valid encoding is:
                                                           0: Calibration done with OK.
                                                           1: Calibration down with Error.
                                                           Writing an '1' to this field will clear this field to a '0'. */
        unsigned int  zcode_pdrv_cal  : 7;  /* bit[24-30]: P-Drive Impedance Calibration Code.
                                                           This field shows the p-driver calibration code during impedance calibration. */
        unsigned int  reserved_3      : 1;  /* bit[31]   : -- */
    } reg;
} SOC_HIPACKPHY_IMPSTATUS_UNION;
#endif
#define SOC_HIPACKPHY_IMPSTATUS_zcode_ndrv_START       (0)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_ndrv_END         (5)
#define SOC_HIPACKPHY_IMPSTATUS_ndrv_cal_result_START  (7)
#define SOC_HIPACKPHY_IMPSTATUS_ndrv_cal_result_END    (7)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_ndrv_cal_START   (8)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_ndrv_cal_END     (14)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_pdrv_START       (16)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_pdrv_END         (21)
#define SOC_HIPACKPHY_IMPSTATUS_pdrv_cal_result_START  (23)
#define SOC_HIPACKPHY_IMPSTATUS_pdrv_cal_result_END    (23)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_pdrv_cal_START   (24)
#define SOC_HIPACKPHY_IMPSTATUS_zcode_pdrv_cal_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DRAMCFG_UNION
 �ṹ˵��  : DRAMCFG �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000C05�����:32
 �Ĵ���˵��: This register is used to configure the DRAM system.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dram_type            : 3;  /* bit[0-2]  : DRAM Type Selection.
                                                                This field specify the DDR RAM type.The valid encoding is as below:
                                                                000: DDR1
                                                                001: DDR2
                                                                010: DDR3
                                                                011: DDR3L
                                                                100: LPDDR1
                                                                101: LPDDR2/LPDDR3
                                                                110: LPDDR4 */
        unsigned int  dram_type_exd        : 1;  /* bit[3]    : Extended DRAM Type Selection.
                                                                {dram_type_exd,dram_type[2:0]}:
                                                                4'b1010: DDR4
                                                                4'b0xxx: refer to dram_type[2:0] only */
        unsigned int  nosra                : 1;  /* bit[4]    : No Simultaneous Rank Access.
                                                                This field specify if simultaneously rank access on the same clock cycle is allowed. If set to a '1', the rank access will be take in turn. 
                                                                It shall be noted this bit can only enabled when number of rank is 2 or 4.
                                                                This bit shall be set as 0 in single rank configuration */
        unsigned int  ma2t                 : 1;  /* bit[5]    : Two Cycle on Address / Command.
                                                                This field specify if 2T timing should be used by PHY controller internally generated DRAM command. */
        unsigned int  maddr_mir            : 1;  /* bit[6]    : [***Note***] Legacy Simple Swap Feature - Do Not Use It
                                                                Address mirroring
                                                                This bit shall be set as 0 in single rank configuration */
        unsigned int  lpddr23_mrw11_en     : 1;  /* bit[7]    : LPDDR234 initalization MRW11 enable.
                                                                1: Issue MRW11 commands during initialization sequence.
                                                                0: disable (default) */
        unsigned int  lpddr23_pre_en       : 1;  /* bit[8]    : LPDDR23 initalization precharge all enable.
                                                                1: Issue precharge all command before RESET command during initialization sequence.
                                                                0: disable (default) */
        unsigned int  lpddr23_mrw1617_en   : 1;  /* bit[9]    : LPDDR23 initalization MRW16/17 enable.
                                                                1: Issue MRW16 and MRW17 commands during initialization sequence.
                                                                0: disable (default)
                                                                -------------------LPDDR4---------------------
                                                                LPDDR4 initalization MRW22/23 enable. */
        unsigned int  lpddr23_zqc_en       : 1;  /* bit[10]   : LPDDR23 initalization ZQC (init) enable.
                                                                1: Issue ZQC(init) commands during initialization sequence rank by rank (default).
                                                                0: disable (do not use)
                                                                Note:
                                                                Due to DRAM devices may expect ZQC(init) shoud be issued before any MRW, do not set lpddr23_zqc_en=0x0 */
        unsigned int  lpddr23_mrw_rst_ca3t : 1;  /* bit[11]   : LPDDR23 MRW RESET extend 3T enable.
                                                                1: Extend MRW RESET for 3T.
                                                                0: disable */
        unsigned int  lpddr23_early_cat_en : 1;  /* bit[12]   : LPDDR23 early CA Training after MRW RESET.
                                                                1: enable
                                                                0: disable */
        unsigned int  ddr4par_en           : 1;  /* bit[13]   : DDR4 Parity Check Mode Enable to Generate PAR for the Requests Generated by PACK */
        unsigned int  mrs_seq_prog_en      : 1;  /* bit[14]   : MRS with programmed sequence enable.
                                                                When enabled, PACK adopts the sequence programmed in the MRS_SEQ_PROG register. When disabled, PACK adopts the default MRS sequence for different type of dram.
                                                                1. enable
                                                                0. disable (default) */
        unsigned int  reserved             : 17; /* bit[15-31]: -- */
    } reg;
} SOC_HIPACKPHY_DRAMCFG_UNION;
#endif
#define SOC_HIPACKPHY_DRAMCFG_dram_type_START             (0)
#define SOC_HIPACKPHY_DRAMCFG_dram_type_END               (2)
#define SOC_HIPACKPHY_DRAMCFG_dram_type_exd_START         (3)
#define SOC_HIPACKPHY_DRAMCFG_dram_type_exd_END           (3)
#define SOC_HIPACKPHY_DRAMCFG_nosra_START                 (4)
#define SOC_HIPACKPHY_DRAMCFG_nosra_END                   (4)
#define SOC_HIPACKPHY_DRAMCFG_ma2t_START                  (5)
#define SOC_HIPACKPHY_DRAMCFG_ma2t_END                    (5)
#define SOC_HIPACKPHY_DRAMCFG_maddr_mir_START             (6)
#define SOC_HIPACKPHY_DRAMCFG_maddr_mir_END               (6)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_mrw11_en_START      (7)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_mrw11_en_END        (7)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_pre_en_START        (8)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_pre_en_END          (8)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_mrw1617_en_START    (9)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_mrw1617_en_END      (9)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_zqc_en_START        (10)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_zqc_en_END          (10)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_mrw_rst_ca3t_START  (11)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_mrw_rst_ca3t_END    (11)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_early_cat_en_START  (12)
#define SOC_HIPACKPHY_DRAMCFG_lpddr23_early_cat_en_END    (12)
#define SOC_HIPACKPHY_DRAMCFG_ddr4par_en_START            (13)
#define SOC_HIPACKPHY_DRAMCFG_ddr4par_en_END              (13)
#define SOC_HIPACKPHY_DRAMCFG_mrs_seq_prog_en_START       (14)
#define SOC_HIPACKPHY_DRAMCFG_mrs_seq_prog_en_END         (14)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DRAMTIMER0_UNION
 �ṹ˵��  : DRAMTIMER0 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register specify the DRAM timing parameters. Please note that the command delay specified in this register only apply to command issued by the PHY controller internally.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_rtp : 4;  /* bit[0-3]  : Read to Precharge Command Delay.
                                                 The unit is 4 clock cycles. */
        unsigned int  t_wtr : 4;  /* bit[4-7]  : Write to Read Command Delay. (Unit: 2 Clocks) */
        unsigned int  t_rp  : 4;  /* bit[8-11] : Precharge Command Period.
                                                 The unit is 4 clock cycles. */
        unsigned int  t_rcd : 4;  /* bit[12-15]: Activated to Read / Write Delay.
                                                 The unit is 2 clock cycles. */
        unsigned int  t_ras : 6;  /* bit[16-21]: Activated to Precharge Command Delay. (Unit: 2 Clocks) */
        unsigned int  t_rrd : 4;  /* bit[22-25]: Activated to Activated on Different Bank Command Delay. (Unit: 2 Clocks) */
        unsigned int  t_rc  : 6;  /* bit[26-31]: Activated to Activated on Same Bank Command Delay.
                                                 Note : Unit in 2xnCK */
    } reg;
} SOC_HIPACKPHY_DRAMTIMER0_UNION;
#endif
#define SOC_HIPACKPHY_DRAMTIMER0_t_rtp_START  (0)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rtp_END    (3)
#define SOC_HIPACKPHY_DRAMTIMER0_t_wtr_START  (4)
#define SOC_HIPACKPHY_DRAMTIMER0_t_wtr_END    (7)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rp_START   (8)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rp_END     (11)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rcd_START  (12)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rcd_END    (15)
#define SOC_HIPACKPHY_DRAMTIMER0_t_ras_START  (16)
#define SOC_HIPACKPHY_DRAMTIMER0_t_ras_END    (21)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rrd_START  (22)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rrd_END    (25)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rc_START   (26)
#define SOC_HIPACKPHY_DRAMTIMER0_t_rc_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DRAMTIMER1_UNION
 �ṹ˵��  : DRAMTIMER1 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register specify the DRAM timing parameters. Please note that the command delay specified in this register only apply to command issued by the PHY controller internally.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_mrd    : 4;  /* bit[0-3]  : Load Mode Register to Load Mode Register Command Delay. Not used. */
        unsigned int  t_mod    : 5;  /* bit[4-8]  : Load Mode Register to Non Load Mode Register Command Delay. This field is used as max(t_mod,t_mrd) in DDR3. This filed is used as max(t_mrw,tmrd) in LPDDR3 and used as t_mrw in LPDDR2.
                                                    Note : Unit in 2xnCK */
        unsigned int  t_faw    : 6;  /* bit[9-14] : Four Bank Activated Period. This field only applied to 8 bank device only. (Unit: 2 Clocks) */
        unsigned int  reserved_0: 1;  /* bit[15]   : -- */
        unsigned int  t_rfc    : 9;  /* bit[16-24]: Refresh to Refresh Command Delay. */
        unsigned int  t_rtw    : 5;  /* bit[25-29]: Read to Write Command Delay.
                                                    This field specify if extra cycle inserted between read and write command. (to compensate tdqsck)
                                                    This value should be 3 for common condition when DDR3 is used.
                                                    This value should be 6 for common condition when LPDDR2/3 is used. */
        unsigned int  reserved_1: 2;  /* bit[30-31]: -- */
    } reg;
} SOC_HIPACKPHY_DRAMTIMER1_UNION;
#endif
#define SOC_HIPACKPHY_DRAMTIMER1_t_mrd_START     (0)
#define SOC_HIPACKPHY_DRAMTIMER1_t_mrd_END       (3)
#define SOC_HIPACKPHY_DRAMTIMER1_t_mod_START     (4)
#define SOC_HIPACKPHY_DRAMTIMER1_t_mod_END       (8)
#define SOC_HIPACKPHY_DRAMTIMER1_t_faw_START     (9)
#define SOC_HIPACKPHY_DRAMTIMER1_t_faw_END       (14)
#define SOC_HIPACKPHY_DRAMTIMER1_t_rfc_START     (16)
#define SOC_HIPACKPHY_DRAMTIMER1_t_rfc_END       (24)
#define SOC_HIPACKPHY_DRAMTIMER1_t_rtw_START     (25)
#define SOC_HIPACKPHY_DRAMTIMER1_t_rtw_END       (29)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DRAMTIMER2_UNION
 �ṹ˵��  : DRAMTIMER2 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register specify the DRAM timing parameters. Please note that the command delay specified in this register only apply to command issued by the PHY controller internally.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_xs     : 10; /* bit[0-9]  : Self Refresh Exit Delay. */
        unsigned int  t_xp     : 5;  /* bit[10-14]: Power Down Exit Delay.
                                                    The minimun value should be:
                                                    Larger or equal to 1 in 1:1 mode
                                                    Larger or equal to 2 in 1:2 mode */
        unsigned int  reserved_0: 1;  /* bit[15]   : -- */
        unsigned int  t_cke    : 4;  /* bit[16-19]: CKE minimum pulse width. */
        unsigned int  t_dllk   : 10; /* bit[20-29]: DLL Lock time. */
        unsigned int  reserved_1: 1;  /* bit[30]   : -- */
        unsigned int  t_ccd    : 1;  /* bit[31]   : Read to Read and Write to Write Command Delay.
                                                    0 = BL/2 (For DDR3, this value should be 4)
                                                    1 = BL/2 + 1 (For DDR3, this value should be 5) */
    } reg;
} SOC_HIPACKPHY_DRAMTIMER2_UNION;
#endif
#define SOC_HIPACKPHY_DRAMTIMER2_t_xs_START      (0)
#define SOC_HIPACKPHY_DRAMTIMER2_t_xs_END        (9)
#define SOC_HIPACKPHY_DRAMTIMER2_t_xp_START      (10)
#define SOC_HIPACKPHY_DRAMTIMER2_t_xp_END        (14)
#define SOC_HIPACKPHY_DRAMTIMER2_t_cke_START     (16)
#define SOC_HIPACKPHY_DRAMTIMER2_t_cke_END       (19)
#define SOC_HIPACKPHY_DRAMTIMER2_t_dllk_START    (20)
#define SOC_HIPACKPHY_DRAMTIMER2_t_dllk_END      (29)
#define SOC_HIPACKPHY_DRAMTIMER2_t_ccd_START     (31)
#define SOC_HIPACKPHY_DRAMTIMER2_t_ccd_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DRAMTIMER3_UNION
 �ṹ˵��  : DRAMTIMER3 �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x02100200�����:32
 �Ĵ���˵��: This register specify the DRAM timing parameters. Please note that the command delay specified in this register only apply to command issued by the PHY controller internally.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_zcal    : 10; /* bit[0-9]  : ZQ Calibration to Command Delay.
                                                     This field specify the number of clock cycles to wait after initial ZQ calibration.
                                                     For DDR3 ZQ normal operation full calibration, this value is divided by 2. For DDR3 ZQ initialization calibration, this value is divided by 4. For LPDDR2/3, this field specify the value of tZQINIT during initialization.
                                                     Note : Unit in 2xnCK */
        unsigned int  t_init5   : 14; /* bit[10-23]: LPDDR Device Initialization Time.
                                                     This field specify the time need for the LPDDR to set the DAI bit to a '1'. */
        unsigned int  tdshtrain : 4;  /* bit[24-27]: VREF Training Timer Control */
        unsigned int  t_wr      : 4;  /* bit[28-31]: Write recovery cycle */
    } reg;
} SOC_HIPACKPHY_DRAMTIMER3_UNION;
#endif
#define SOC_HIPACKPHY_DRAMTIMER3_t_zcal_START     (0)
#define SOC_HIPACKPHY_DRAMTIMER3_t_zcal_END       (9)
#define SOC_HIPACKPHY_DRAMTIMER3_t_init5_START    (10)
#define SOC_HIPACKPHY_DRAMTIMER3_t_init5_END      (23)
#define SOC_HIPACKPHY_DRAMTIMER3_tdshtrain_START  (24)
#define SOC_HIPACKPHY_DRAMTIMER3_tdshtrain_END    (27)
#define SOC_HIPACKPHY_DRAMTIMER3_t_wr_START       (28)
#define SOC_HIPACKPHY_DRAMTIMER3_t_wr_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DRAMTIMER4_UNION
 �ṹ˵��  : DRAMTIMER4 �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x50340000�����:32
 �Ĵ���˵��: This register specify the DRAM Write Leveling timing parameter. This register only applied to DDR3/LPDDR3 type SDRAM.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_wlmrd    : 6;  /* bit[0-5]  : Write Leveling Mode Programmed (Load Mode Register) to first DQS/DQS# rising edge delay. (dficlk cycle) */
        unsigned int  t_wr_ext   : 1;  /* bit[6]    : Write recovery cycle extend bit */
        unsigned int  t_wlo      : 5;  /* bit[7-11] : Write Leveling Output Delay.
                                                      This field specify the write leveling output delay in cycles. (Unit in 2nCK) */
        unsigned int  t_odt      : 4;  /* bit[12-15]: ODT turn-on cycles */
        unsigned int  t_ccd_s    : 4;  /* bit[16-19]: DDR4 Read to Read and Write to Write Command Delay for different bank group
                                                      -------------------LPDDR4---------------------
                                                      In LPDDR4, This is Used for tCCDMW Configuration.
                                                      Formula : t_ccd = (4*TCCD@BL16)>>2
                                                      Ex: BL16: (4*8)>>2=8 */
        unsigned int  t_vref     : 3;  /* bit[20-22]: VREF(DQ) Update Delays.
                                                      This field specify the number of clock cycles waits after VREF to DRAM updated. The actual number of cycles waits is calculated as : (2 ^ t_vref) x 16 */
        unsigned int  reserved   : 1;  /* bit[23]   :  */
        unsigned int  t_odton    : 4;  /* bit[24-27]: ODT turn-on latency low 4 bits (Number of cycle from write command to assert of ODT) */
        unsigned int  t_ccd_ddr4 : 4;  /* bit[28-31]: DDR4 Read to Read and Write to Write Command Delay for same bank group (corresponding to t_ccd_l).
                                                      -------------------LPDDR4---------------------
                                                      In LPDDR4, This is Used for tCCD Configuration.
                                                      Formula : t_ccd = (BL/2)>>2
                                                      Ex: BL16: (16/2)>>2=2
                                                      BL32: (32/2)>>2=4
                                                      Formula with bl32atonthefly : ((BL==2'b0)?4'h8:(BL==2'b01)?'h10:(bl32atonthefly?'h10:'h8))>>2 */
    } reg;
} SOC_HIPACKPHY_DRAMTIMER4_UNION;
#endif
#define SOC_HIPACKPHY_DRAMTIMER4_t_wlmrd_START     (0)
#define SOC_HIPACKPHY_DRAMTIMER4_t_wlmrd_END       (5)
#define SOC_HIPACKPHY_DRAMTIMER4_t_wr_ext_START    (6)
#define SOC_HIPACKPHY_DRAMTIMER4_t_wr_ext_END      (6)
#define SOC_HIPACKPHY_DRAMTIMER4_t_wlo_START       (7)
#define SOC_HIPACKPHY_DRAMTIMER4_t_wlo_END         (11)
#define SOC_HIPACKPHY_DRAMTIMER4_t_odt_START       (12)
#define SOC_HIPACKPHY_DRAMTIMER4_t_odt_END         (15)
#define SOC_HIPACKPHY_DRAMTIMER4_t_ccd_s_START     (16)
#define SOC_HIPACKPHY_DRAMTIMER4_t_ccd_s_END       (19)
#define SOC_HIPACKPHY_DRAMTIMER4_t_vref_START      (20)
#define SOC_HIPACKPHY_DRAMTIMER4_t_vref_END        (22)
#define SOC_HIPACKPHY_DRAMTIMER4_t_odton_START     (24)
#define SOC_HIPACKPHY_DRAMTIMER4_t_odton_END       (27)
#define SOC_HIPACKPHY_DRAMTIMER4_t_ccd_ddr4_START  (28)
#define SOC_HIPACKPHY_DRAMTIMER4_t_ccd_ddr4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ODTCR_UNION
 �ṹ˵��  : ODTCR �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register specify the ODT control on different rank while reading or writing to particular rank.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wodt_rank0 : 4;  /* bit[0-3]  : Write Rank0 ODT Control.
                                                      This field specify the ODT issued while write on Rank0. The real valid bit-width is the rumber of rank. */
        unsigned int  wodt_rank1 : 4;  /* bit[4-7]  : Write Rank1 ODT Control.
                                                      This field specify the ODT issued while write on Rank1. The real valid bit-width is the rumber of rank. */
        unsigned int  wodt_rank2 : 4;  /* bit[8-11] : Write Rank2 ODT Control.
                                                      This field specify the ODT issued while write on Rank2. The real valid bit-width is the rumber of rank. */
        unsigned int  wodt_rank3 : 4;  /* bit[12-15]: Write Rank3 ODT Control.
                                                      This field specify the ODT issued while write on Rank3. The real valid bit-width is the rumber of rank. */
        unsigned int  reserved   : 16; /* bit[16-31]: -- */
    } reg;
} SOC_HIPACKPHY_ODTCR_UNION;
#endif
#define SOC_HIPACKPHY_ODTCR_wodt_rank0_START  (0)
#define SOC_HIPACKPHY_ODTCR_wodt_rank0_END    (3)
#define SOC_HIPACKPHY_ODTCR_wodt_rank1_START  (4)
#define SOC_HIPACKPHY_ODTCR_wodt_rank1_END    (7)
#define SOC_HIPACKPHY_ODTCR_wodt_rank2_START  (8)
#define SOC_HIPACKPHY_ODTCR_wodt_rank2_END    (11)
#define SOC_HIPACKPHY_ODTCR_wodt_rank3_START  (12)
#define SOC_HIPACKPHY_ODTCR_wodt_rank3_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_TRAINCTRL0_UNION
 �ṹ˵��  : TRAINCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x60441080�����:32
 �Ĵ���˵��: This register specify the training control.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dtr_rank    : 4;  /* bit[0-3]  : Training Rank.
                                                       This register specify the rank used to do training. And after training done, this field is used to select the source of rank specific settings.
                                                       0x0: rank0
                                                       0x1: rank1
                                                       �� */
        unsigned int  dqsgsl_mrgn : 6;  /* bit[4-9]  : Read DQS Gate Margin
                                                       This field specify the margin to reserve after DQS gate training. The number of phyase specify in this field will be decreased to create DQS gating margin. 
                                                       The valid encoding of the setting is as below:
                                                       6'b00100: 1/4 cycle
                                                       6'b01000: 1/2 cycle (recommended)
                                                       6'b01100: 3/4 cycle
                                                       6'b10000: 1 cycle
                                                       Note:suggest user setting to 9 in DDR4 */
        unsigned int  dqsgrt_shft : 6;  /* bit[10-15]: Gate Retraing Shift Window.
                                                       This field specify the value to be shift if gate phase adjustment required after gate retraining checks. 
                                                       The phase movement will be the setting value multiple by 2. Please note that 3'b000 is reserved, and should not be used. The recommended value is set as dqsgrt_chk. */
        unsigned int  dqsgrt_chk  : 6;  /* bit[16-21]: Gate Retraing Check Window.
                                                       This field specify the delta value to be checked during gate retraining check. The delta will be added/substrated from the read DQS gate. This two position will be checked to determine if gating phase adjustment required. 
                                                       The phase movement will be the setting value multiple by 2. Please note that 3'b000 is reserved, and should not be used. The recommended values are 0x1~0x3 under 1600 Mbps. */
        unsigned int  gtfback_en  : 1;  /* bit[22]   : GT fine-stage back feature enable. When this feature is enabled, the gate training will go back to get gt_result=0x0 between coarse-tune and fine-tune stage.
                                                       1: enable (default)
                                                       0: disable */
        unsigned int  reserved    : 1;  /* bit[23]   :  */
        unsigned int  gtdsdly     : 6;  /* bit[24-29]: Gate / Read Latch Training Response Delay.
                                                       This field specify the waiting time to check the response from PHY while doing Gate and Read Latch training. (unit 1nCK)
                                                       Formula :
                                                        gtdsdly= 'h20 + burst_length/2 */
        unsigned int  dtrerrstop  : 1;  /* bit[30]   : Data Training Error Stop.
                                                       This field controls if the data training will be terminated if error happened. The data training will be stopped if this bit is set to a '1'. If this bit set to a '0', the training will continue even have error happened. The error status will be recorded either this bit set to a '0' or '1'. */
        unsigned int  detskipeyop : 1;  /* bit[31]   : Skip Eye Opening of Data Eye Training.
                                                       This field is to specified if the eye opening should be skipped. If this field is set to a '1', the eye opening before data eye training will be skipped. If this field is set to a '0', the eye opening will be executed before data eye training. */
    } reg;
} SOC_HIPACKPHY_TRAINCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL0_dtr_rank_START     (0)
#define SOC_HIPACKPHY_TRAINCTRL0_dtr_rank_END       (3)
#define SOC_HIPACKPHY_TRAINCTRL0_dqsgsl_mrgn_START  (4)
#define SOC_HIPACKPHY_TRAINCTRL0_dqsgsl_mrgn_END    (9)
#define SOC_HIPACKPHY_TRAINCTRL0_dqsgrt_shft_START  (10)
#define SOC_HIPACKPHY_TRAINCTRL0_dqsgrt_shft_END    (15)
#define SOC_HIPACKPHY_TRAINCTRL0_dqsgrt_chk_START   (16)
#define SOC_HIPACKPHY_TRAINCTRL0_dqsgrt_chk_END     (21)
#define SOC_HIPACKPHY_TRAINCTRL0_gtfback_en_START   (22)
#define SOC_HIPACKPHY_TRAINCTRL0_gtfback_en_END     (22)
#define SOC_HIPACKPHY_TRAINCTRL0_gtdsdly_START      (24)
#define SOC_HIPACKPHY_TRAINCTRL0_gtdsdly_END        (29)
#define SOC_HIPACKPHY_TRAINCTRL0_dtrerrstop_START   (30)
#define SOC_HIPACKPHY_TRAINCTRL0_dtrerrstop_END     (30)
#define SOC_HIPACKPHY_TRAINCTRL0_detskipeyop_START  (31)
#define SOC_HIPACKPHY_TRAINCTRL0_detskipeyop_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_RANKEN_UNION
 �ṹ˵��  : RANKEN �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000003�����:32
 �Ĵ���˵��: This register specify the training rank control.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rank_en       : 16; /* bit[0-15] : Training Rank enable.
                                                         This register specify if the rank is enabled or not. This field is used to indicated if the dtr_rank is enabled. 
                                                         1: enable (default)
                                                         0: disable
                                                         Bit0 indicates the RANK0.
                                                         Bit1 indicates the RANK1.
                                                         ��
                                                         Bit15 indicateds the RANK15.
                                                         The maximum number of RANK is specified by the system. */
        unsigned int  dtbankgrp     : 3;  /* bit[16-18]: Data Training Bank Group.
                                                         This register is used as the memory bank group address where is used during data training if required.
                                                         And TRAINMADDR will be used with this field.
                                                         [***Constraint***]
                                                         1. dtbank[2] Must be equal to dtbankgrp[0] */
        unsigned int  reserved_0    : 1;  /* bit[19]   : -- */
        unsigned int  dtbankgrp_tg1 : 3;  /* bit[20-22]: Data Training Bank Group Another.
                                                         This register is used as the memory bank group address where is used during data training if required.
                                                         If it is different from dtbankgrp, BG toggle mode enable to access data cross BG (for tCCD=4) and TRAINMADDRTG1 will be used with this field.
                                                         Basically, this is used in DDR4. If wanting to use this feature in other thank DDR4, only bit 0 can be used due to BG0 used for BA2.
                                                         For example, dtbankgrp_tg1==3'b001 and dtbankgrp==3'b000
                                                         [***Constraint***]
                                                         1. dtbank_tg1[2] Must be equal to dtbankgrp_tg1[0] */
        unsigned int  reserved_1    : 1;  /* bit[23]   : -- */
        unsigned int  reserved_2    : 8;  /* bit[24-31]: -- */
    } reg;
} SOC_HIPACKPHY_RANKEN_UNION;
#endif
#define SOC_HIPACKPHY_RANKEN_rank_en_START        (0)
#define SOC_HIPACKPHY_RANKEN_rank_en_END          (15)
#define SOC_HIPACKPHY_RANKEN_dtbankgrp_START      (16)
#define SOC_HIPACKPHY_RANKEN_dtbankgrp_END        (18)
#define SOC_HIPACKPHY_RANKEN_dtbankgrp_tg1_START  (20)
#define SOC_HIPACKPHY_RANKEN_dtbankgrp_tg1_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_TRAINMADDR_UNION
 �ṹ˵��  : TRAINMADDR �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register specify the starting memory address where can be used to do data training. The minimum space required for data training should be 64-bytes, and the allocated memory should be 64-bytes alignment.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dtbank   : 3;  /* bit[0-2]  : Data Training Bank Address.
                                                    This register is used as the memory bank address where is used during data training if required.
                                                    [***Constraint***]
                                                    1. dtbank[2] Must be equal to dtbankgrp[0] */
        unsigned int  reserved : 1;  /* bit[3]    : -- */
        unsigned int  dtcol    : 12; /* bit[4-15] : Data Training Column Address.
                                                    This register is used as the column address which is used during data training if required. The field should be 0. */
        unsigned int  dtrow    : 16; /* bit[16-31]: Data Training Row Address.
                                                    This register is used as the memory row address where is used during data training if required. */
    } reg;
} SOC_HIPACKPHY_TRAINMADDR_UNION;
#endif
#define SOC_HIPACKPHY_TRAINMADDR_dtbank_START    (0)
#define SOC_HIPACKPHY_TRAINMADDR_dtbank_END      (2)
#define SOC_HIPACKPHY_TRAINMADDR_dtcol_START     (4)
#define SOC_HIPACKPHY_TRAINMADDR_dtcol_END       (15)
#define SOC_HIPACKPHY_TRAINMADDR_dtrow_START     (16)
#define SOC_HIPACKPHY_TRAINMADDR_dtrow_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_BISTCTRL_UNION
 �ṹ˵��  : BISTCTRL �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register specify the behavior of the built-in self test.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bist_op            : 2;  /* bit[0-1]  : During Reg Write this field is for Bist Operation Select.
                                                               This field specify the BIST operation. The valid encoding is as below.
                                                               00: BIST Stop.
                                                               01: BIST Run.
                                                               10: BIST Reset.
                                                               11: Reserved.
                                                               Writing the Reset will clear all the status register, and this field will be cleared to BIST Stop.
                                                              
                                                              During Reg Read this field is for BIST active status (only bit0 is valid, bit1 is read as 1'b0)
                                                               1: BIST active
                                                               0: BIST not active */
        unsigned int  reserved_0         : 2;  /* bit[2-3]  : -- */
        unsigned int  bist_mode          : 3;  /* bit[4-6]  : BIST Mode Select.
                                                              This field specify the mode of BIST testing. The valid encoding is as below.
                                                              000: Pattern generated only.
                                                              (1. does not compare data 
                                                               2. does not need DRAM devices
                                                               3. the pattern is determinded by bist_pat)
                                                              100: Loopback is before output buffer.
                                                              101: Loopback is after output buffer.
                                                              110: DRAM read / write mode.
                                                              Other encodings except above is reserved.
                                                              It shall be noted that bist_mode is only allowed to be changed when bist_done is 1. And when DATA Loopback mode is selected, swapwl_en/swap_en should be set as all zeros (no swap).
                                                              In normal operation, this field should be set as 3'b110. The 3'b100/3'b101 will switch ddrphy to LPBK mode. */
        unsigned int  reserved_1         : 1;  /* bit[7]    : -- */
        unsigned int  bist_pat           : 3;  /* bit[8-10] : BIST Pattern Generation.
                                                              This field specify the BIST pattern generated for test. It shall be noted that bist_pat is only allowed to be changed when bist_done is 1.
                                                              000: Walking 0.
                                                              001: Walking 1.
                                                              010: LFSR-based random generation.
                                                              011: User programmed.
                                                              100: DX Cross Talk 0, only in case of dx bist
                                                              101: DX Cross Talk 1, only in case of dx bist
                                                              110: DX SSO, only in case of dx bist */
        unsigned int  sso_bist_cnt       : 3;  /* bit[11-13]: DX SSO pattern counter to configurate the 1/0 length 
                                                              0: 1X, 1: 1/2X, 2: 1/4X, 3: 1/8X */
        unsigned int  reserved_2         : 1;  /* bit[14-14]: -- */
        unsigned int  dfi_phyupd_disable : 1;  /* bit[15]   : Disable DFI PHY Update Interface to MC
                                                              1: Disable PHY Update Interface to MC (Used in DX BIST in Case of Sending PHY Update Request to MC) */
        unsigned int  bist_fail_stop     : 8;  /* bit[16-23]: Bist Stop Error Count.
                                                              This field specify the number of failure which the BIST should stop.If this field is set to 0x00, the bist will run infinite until BIST operation is stopped or reset. If non-zero value specified, the BIST will stopped while the accumulated error reach the count specified in this field. */
        unsigned int  rnk_sw_mode        : 1;  /* bit[24]   : Rank switching mode
                                                              If this register set to 1, write/read command will switch rank automatically. */
        unsigned int  brst_cnt           : 7;  /* bit[25-31]: The number of Burst.
                                                              0: one burst; 1: five burst; �� 127: 509 burst. The write/read cycle time must not over refresh cycle time be required. */
    } reg;
} SOC_HIPACKPHY_BISTCTRL_UNION;
#endif
#define SOC_HIPACKPHY_BISTCTRL_bist_op_START             (0)
#define SOC_HIPACKPHY_BISTCTRL_bist_op_END               (1)
#define SOC_HIPACKPHY_BISTCTRL_bist_mode_START           (4)
#define SOC_HIPACKPHY_BISTCTRL_bist_mode_END             (6)
#define SOC_HIPACKPHY_BISTCTRL_bist_pat_START            (8)
#define SOC_HIPACKPHY_BISTCTRL_bist_pat_END              (10)
#define SOC_HIPACKPHY_BISTCTRL_sso_bist_cnt_START        (11)
#define SOC_HIPACKPHY_BISTCTRL_sso_bist_cnt_END          (13)
#define SOC_HIPACKPHY_BISTCTRL_dfi_phyupd_disable_START  (15)
#define SOC_HIPACKPHY_BISTCTRL_dfi_phyupd_disable_END    (15)
#define SOC_HIPACKPHY_BISTCTRL_bist_fail_stop_START      (16)
#define SOC_HIPACKPHY_BISTCTRL_bist_fail_stop_END        (23)
#define SOC_HIPACKPHY_BISTCTRL_rnk_sw_mode_START         (24)
#define SOC_HIPACKPHY_BISTCTRL_rnk_sw_mode_END           (24)
#define SOC_HIPACKPHY_BISTCTRL_brst_cnt_START            (25)
#define SOC_HIPACKPHY_BISTCTRL_brst_cnt_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_BISTDATA0_UNION
 �ṹ˵��  : BISTDATA0 �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register specify the BIST data used for DRAM loopback test. Please note that this register only valid while the bist_pat is set to "User Defined"
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bist_data_b0 : 8;  /* bit[0-7]  : BIST Data Byte 0.
                                                        This field is used as the first beat of burst during BIST test. */
        unsigned int  bist_data_b1 : 8;  /* bit[8-15] : BIST Data Byte 1.
                                                        This field is used as the second beat of burst during BIST test. */
        unsigned int  bist_data_b2 : 8;  /* bit[16-23]: BIST Data Byte 2.
                                                        This field is used as the third beat of burst during BIST test. */
        unsigned int  bist_data_b3 : 8;  /* bit[24-31]: BIST Data Byte 3.
                                                        This field is used as the forth beat of burst during BIST test */
    } reg;
} SOC_HIPACKPHY_BISTDATA0_UNION;
#endif
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b0_START  (0)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b0_END    (7)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b1_START  (8)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b1_END    (15)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b2_START  (16)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b2_END    (23)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b3_START  (24)
#define SOC_HIPACKPHY_BISTDATA0_bist_data_b3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_BISTDATA1_UNION
 �ṹ˵��  : BISTDATA1 �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bist_data_b4 : 8;  /* bit[0-7]  : BIST Data Byte 4.
                                                        This field is used as the forth beat of burst during BIST test. */
        unsigned int  bist_data_b5 : 8;  /* bit[8-15] : BIST Data Byte 5.
                                                        This field is used as the fifth beat of burst during BIST test. */
        unsigned int  bist_data_b6 : 8;  /* bit[16-23]: BIST Data Byte 6.
                                                        This field is used as the sixth beat of burst during BIST test. */
        unsigned int  bist_data_b7 : 8;  /* bit[24-31]: BIST Data Byte 7.
                                                        This field is used as the eighth beat of burst during BIST test */
    } reg;
} SOC_HIPACKPHY_BISTDATA1_UNION;
#endif
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b4_START  (0)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b4_END    (7)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b5_START  (8)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b5_END    (15)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b6_START  (16)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b6_END    (23)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b7_START  (24)
#define SOC_HIPACKPHY_BISTDATA1_bist_data_b7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_BISTSTATUS_UNION
 �ṹ˵��  : BISTSTATUS �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000001�����:32
 �Ĵ���˵��: This register shows the result and status of BIST testing.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bist_done  : 1;  /* bit[0]   : BIST Done 
                                                     This bit shows if the BIST is done. Please note that if the burst count was set to 0, this field will never be asserted. */
        unsigned int  bist_acerr : 1;  /* bit[1]   : BIST Error on AC Block.
                                                     This bit shows if any error happened on the AC during BIST testing. */
        unsigned int  bist_dxerr : 1;  /* bit[2]   : BIST Error on DX Blocks.
                                                     This bit shows if any error happened on the DXn during BIST testing. */
        unsigned int  reserved   : 29; /* bit[3-31]: -- */
    } reg;
} SOC_HIPACKPHY_BISTSTATUS_UNION;
#endif
#define SOC_HIPACKPHY_BISTSTATUS_bist_done_START   (0)
#define SOC_HIPACKPHY_BISTSTATUS_bist_done_END     (0)
#define SOC_HIPACKPHY_BISTSTATUS_bist_acerr_START  (1)
#define SOC_HIPACKPHY_BISTSTATUS_bist_acerr_END    (1)
#define SOC_HIPACKPHY_BISTSTATUS_bist_dxerr_START  (2)
#define SOC_HIPACKPHY_BISTSTATUS_bist_dxerr_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_MODEREG01_UNION
 �ṹ˵��  : MODEREG01 �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines the contents of the Mode Register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mr0 : 16; /* bit[0-15] : Mode Register 0.
                                               For DDR/DDR2/DDR3/LPDDR, this register sepcify the content of Mode Register 0. Note that the MR0[8] for DDR3/4 DLL Reset takes no effect by this settings. It is handled by the design during DRAM initialization.
                                               For LPDDR2/LPDDR3, this register defines the MR1/MR2 of the mode register.
                                                bit[15:8]: MR2 OP
                                                bit[7:0]: MR1 OP
                                               
                                               Note: the BL (Burst Length) will affect the PACK/PHY behavior, too. It should be set properly.
                                               bit[1:0] will be used to decide PACK/PHY BurstLenght 4/8.
                                               DDR3 - bit[1] 1:BL4, 0:BL8
                                               DDR2/LPDDRx - bit[0] 1:BL8, 0:BL4
                                               -------------------LPDDR4---------------------
                                               {MR2, MR1}
                                               MR2 - WR Lev, WLS, WL, RL,
                                               MR1 - RPST, nWR (for AP), RD-PRE, WR-PRE, BL */
        unsigned int  mr1 : 16; /* bit[16-31]: Mode Register 1.
                                               For DDR/DDR2/DDR3/LPDDR, this register sepcify the content of Extend Mode Register 1.
                                               For LPDDR2/LPDDR3, this register defines the content of MR3/MR11 ( mode register).
                                                bit[31:24]: MR11 OP
                                                bit[23:16]: MR3 OP
                                               -------------------LPDDR4---------------------
                                               {MR11, MR3}
                                               MR3 - DBI-WR, DBI-RD, PDDS, PPRP WR, PST, PU-CAL, */
    } reg;
} SOC_HIPACKPHY_MODEREG01_UNION;
#endif
#define SOC_HIPACKPHY_MODEREG01_mr0_START  (0)
#define SOC_HIPACKPHY_MODEREG01_mr0_END    (15)
#define SOC_HIPACKPHY_MODEREG01_mr1_START  (16)
#define SOC_HIPACKPHY_MODEREG01_mr1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_MODEREG23_UNION
 �ṹ˵��  : MODEREG23 �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0xFF0A0000�����:32
 �Ĵ���˵��: This register defines the contents of the Mode Register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mr2 : 16; /* bit[0-15] : Mode Register 2.
                                               For DDR/DDR2/DDR3, this register is used to specify the Extend Mode Register 2. 
                                               For LPDDR2/LPDDR3, this register is used to specify the MR16/17.
                                                bit[15:8]: MR17 OP
                                                bit[ 7:0]: MR16 OP
                                               -------------------LPDDR4---------------------
                                               {MR22, MR23}
                                               MR22 - ODTD-CA, ODTE-CS, ODTE-CK
                                               MR23 - DQS interval timer run time setting */
        unsigned int  mr3 : 16; /* bit[16-31]: Mode Register 3.
                                               For DDR/DDR2/DDR3, this register is used to specify the Extend Mode Register 3 and default value be 0x0.
                                               For LPDDR23, this register is for ZQ command - [31:24]OP, [23:16]MA and default be 0xFF0A. The ZQ commands will be issued rank by rank after tINIT5.
                                                bit[31:24]: MR10 OP
                                                bit[23:16]: MR10 MA
                                               ---------------------DDR4----------------------
                                               MR3 Setting */
    } reg;
} SOC_HIPACKPHY_MODEREG23_UNION;
#endif
#define SOC_HIPACKPHY_MODEREG23_mr2_START  (0)
#define SOC_HIPACKPHY_MODEREG23_mr2_END    (15)
#define SOC_HIPACKPHY_MODEREG23_mr3_START  (16)
#define SOC_HIPACKPHY_MODEREG23_mr3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DETPATTERN_UNION
 �ṹ˵��  : DETPATTERN �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Write/Read DET Pattern Register.
            These fields are used to fine-tune the training procedure. Users are not recommend to modify them.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  det_pat_pat : 32; /* bit[0-31]: DET pattern content.
                                                      The pattern content is pointed by the DETPATINDEX.
                                                      
                                                      Note: when DETPATINDEX select the non-defined content, the write will not take effect and the read will return the RDET index 0 data. */
    } reg;
} SOC_HIPACKPHY_DETPATTERN_UNION;
#endif
#define SOC_HIPACKPHY_DETPATTERN_det_pat_pat_START  (0)
#define SOC_HIPACKPHY_DETPATTERN_det_pat_pat_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_MISC_UNION
 �ṹ˵��  : MISC �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x08140000�����:32
 �Ĵ���˵��: Miscellaneous control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_wl      : 8;  /* bit[0-7]  : PHY write latency.
                                                       It defines the number of cycles from wrire command to assert of wrdata_en and is equal to CWL+AL
                                                       (for LPDDR2/3, the filed should be WL+1). If the DFI clock ratio is 1:2, cfg_wl should be equal or greater than 2 */
        unsigned int  cfg_rl      : 8;  /* bit[8-15] : PHY read latency.
                                                       It defines the number of cycles from read command to assert of rddata_en.
                                                       DDR3/4: CL+AL-4
                                                       LPDDR2/3: RL+RD(tdqsck(min)/tCK)-3
                                                       LPDDR4: RL+3+RD(tdqsck(min)/tCK)-(dfi_clk_ratio==0)?3:5)
                                                       *) dfi_clk_ratio==0 - 1:1 Mode
                                                       *) dfi_clk_ratio==1 - 1:2 Mode */
        unsigned int  scramb_en   : 1;  /* bit[16]   : Data scrambler enable
                                                       Set as '1' to enable data sramble function */
        unsigned int  addr_toggle : 1;  /* bit[17]   : Toggle addess bus every clock cycle
                                                       This bit is set as '1' for burn-in test only */
        unsigned int  addr_delay  : 1;  /* bit[18]   : Add 1-T delay on address/command 
                                                       This bit shall be set as '1' when CWL=5 */
        unsigned int  cfg_dlyupd  : 1;  /* bit[19]   : To enable transparent mode of delay update module. When this bit is set to 1, the delay setting in registers will be applied to PHY immediately */
        unsigned int  swap_en     : 3;  /* bit[20-22]: Swap DQ bus
                                                       000: No Swap
                                                       001: Swap 1
                                                       010: Swap 2
                                                       011: Swap 3
                                                       100: Swap 4
                                                       105: Swap 5
                                                       Note: when DATA BIST Loopback mode is selected, this field should be set as 0x0. */
        unsigned int  reserved_0  : 2;  /* bit[23-24]:  */
        unsigned int  swapdm_en   : 2;  /* bit[25-26]: Swap DM bus
                                                       00: No Swap
                                                       01: 16-Bit T2 Swap */
        unsigned int  swapwl_en   : 3;  /* bit[27-29]: Swap WL/CA Result
                                                       000: No Swap
                                                       001: Swap 1
                                                       010: Swap 2
                                                       011: Swap 3
                                                       100: Swap 4
                                                       Note: when DATA BIST Loopback mode is selected, this field should be set as 0x0. */
        unsigned int  reserved_1  : 2;  /* bit[30-31]:  */
    } reg;
} SOC_HIPACKPHY_MISC_UNION;
#endif
#define SOC_HIPACKPHY_MISC_cfg_wl_START       (0)
#define SOC_HIPACKPHY_MISC_cfg_wl_END         (7)
#define SOC_HIPACKPHY_MISC_cfg_rl_START       (8)
#define SOC_HIPACKPHY_MISC_cfg_rl_END         (15)
#define SOC_HIPACKPHY_MISC_scramb_en_START    (16)
#define SOC_HIPACKPHY_MISC_scramb_en_END      (16)
#define SOC_HIPACKPHY_MISC_addr_toggle_START  (17)
#define SOC_HIPACKPHY_MISC_addr_toggle_END    (17)
#define SOC_HIPACKPHY_MISC_addr_delay_START   (18)
#define SOC_HIPACKPHY_MISC_addr_delay_END     (18)
#define SOC_HIPACKPHY_MISC_cfg_dlyupd_START   (19)
#define SOC_HIPACKPHY_MISC_cfg_dlyupd_END     (19)
#define SOC_HIPACKPHY_MISC_swap_en_START      (20)
#define SOC_HIPACKPHY_MISC_swap_en_END        (22)
#define SOC_HIPACKPHY_MISC_swapdm_en_START    (25)
#define SOC_HIPACKPHY_MISC_swapdm_en_END      (26)
#define SOC_HIPACKPHY_MISC_swapwl_en_START    (27)
#define SOC_HIPACKPHY_MISC_swapwl_en_END      (29)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_RNK2RNK_UNION
 �ṹ˵��  : RNK2RNK �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: Rank to rank delay control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trnkwtw   : 5;  /* bit[0-4]  : Delay from write to write command targeted to different ranks User need fill a proper value if there are rank switching application. Eg. 0x0a with 1600 MT/s */
        unsigned int  trnkrtr   : 5;  /* bit[5-9]  : Delay from read to read command targeted to different ranks User need fill a proper value if there are rank switching application. Eg. 0x0a with 1600 MT/s */
        unsigned int  trnkrtw   : 5;  /* bit[10-14]: Delay from read to write command targeted to different ranks User need fill a proper value if there are rank switching application. Eg. 0x0a with 1600 MT/s */
        unsigned int  trnkwtr   : 5;  /* bit[15-19]: Delay from write to read command targeted to different ranks. User need fill a proper value if there are rank switching application. Eg. 0x0a with 1600 MT/s */
        unsigned int  reserved  : 9;  /* bit[20-28]: Delay from write to read command targeted to different ranks. User need fill a proper value if there are rank switching application. Eg. 0x0a with 1600 MT/s */
        unsigned int  dfi2iomap : 3;  /* bit[29-31]: DFI2IO Mapping Selection
                                                     3'h0: Direct Mapping (By Pass)
                                                     3'h1: DDR4 Comapct Mapping
                                                     3'h2: DDR3 Comapct Mapping
                                                     3'h3: GB Remapping Only
                                                     3'h4: D3-L2-P2
                                                     3'h5: D4-L2-P2
                                                     3'h6: D4-L4-P4
                                                     3'h7: D4-L4-P2 */
    } reg;
} SOC_HIPACKPHY_RNK2RNK_UNION;
#endif
#define SOC_HIPACKPHY_RNK2RNK_trnkwtw_START    (0)
#define SOC_HIPACKPHY_RNK2RNK_trnkwtw_END      (4)
#define SOC_HIPACKPHY_RNK2RNK_trnkrtr_START    (5)
#define SOC_HIPACKPHY_RNK2RNK_trnkrtr_END      (9)
#define SOC_HIPACKPHY_RNK2RNK_trnkrtw_START    (10)
#define SOC_HIPACKPHY_RNK2RNK_trnkrtw_END      (14)
#define SOC_HIPACKPHY_RNK2RNK_trnkwtr_START    (15)
#define SOC_HIPACKPHY_RNK2RNK_trnkwtr_END      (19)
#define SOC_HIPACKPHY_RNK2RNK_dfi2iomap_START  (29)
#define SOC_HIPACKPHY_RNK2RNK_dfi2iomap_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYCTRL0_UNION
 �ṹ˵��  : PHYCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00003180�����:32
 �Ĵ���˵��: PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0]    :  */
        unsigned int  reg_sel_dficlk_rx : 1;  /* bit[1]    : PHY RX Path Clock Selection
                                                             0: Internal Clock
                                                             1: DFI Clock */
        unsigned int  sel_pos_rx        : 1;  /* bit[2]    : PHY output trigger edge selection.
                                                             1: rising edge
                                                             0: falling edge */
        unsigned int  lp_ck_sel         : 2;  /* bit[3-4]  : Dummy Reg - Not Used */
        unsigned int  reserved_1        : 2;  /* bit[5-6]  :  */
        unsigned int  cmdoen            : 1;  /* bit[7]    : Move to AC_Static_Reg */
        unsigned int  ckoen             : 3;  /* bit[8-10] : Move to AC_Static_Reg */
        unsigned int  ckeoen            : 1;  /* bit[11]   : Move to AC_Static_Reg
                                                             -> Change Default Value to 0 for K3V5 Top Usage */
        unsigned int  csoen             : 1;  /* bit[12]   : Move to AC_Static_Reg */
        unsigned int  resetoen          : 1;  /* bit[13]   : Move to AC_Static_Reg */
        unsigned int  reserved_2        : 18; /* bit[14-31]: -- */
    } reg;
} SOC_HIPACKPHY_PHYCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_PHYCTRL0_reg_sel_dficlk_rx_START  (1)
#define SOC_HIPACKPHY_PHYCTRL0_reg_sel_dficlk_rx_END    (1)
#define SOC_HIPACKPHY_PHYCTRL0_sel_pos_rx_START         (2)
#define SOC_HIPACKPHY_PHYCTRL0_sel_pos_rx_END           (2)
#define SOC_HIPACKPHY_PHYCTRL0_lp_ck_sel_START          (3)
#define SOC_HIPACKPHY_PHYCTRL0_lp_ck_sel_END            (4)
#define SOC_HIPACKPHY_PHYCTRL0_cmdoen_START             (7)
#define SOC_HIPACKPHY_PHYCTRL0_cmdoen_END               (7)
#define SOC_HIPACKPHY_PHYCTRL0_ckoen_START              (8)
#define SOC_HIPACKPHY_PHYCTRL0_ckoen_END                (10)
#define SOC_HIPACKPHY_PHYCTRL0_ckeoen_START             (11)
#define SOC_HIPACKPHY_PHYCTRL0_ckeoen_END               (11)
#define SOC_HIPACKPHY_PHYCTRL0_csoen_START              (12)
#define SOC_HIPACKPHY_PHYCTRL0_csoen_END                (12)
#define SOC_HIPACKPHY_PHYCTRL0_resetoen_START           (13)
#define SOC_HIPACKPHY_PHYCTRL0_resetoen_END             (13)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYDBG_UNION
 �ṹ˵��  : PHYDBG �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PHY debug registers
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dqs_gated_error  : 8;  /* bit[0-7]  : DQS gated error flag
                                                            This error flag can only be cleared by issuing PHY reset */
        unsigned int  reserved_0       : 8;  /* bit[8-15] : -- */
        unsigned int  dqsb_gated_error : 8;  /* bit[16-23]: DQSN gated error flag
                                                            This error flag can only be cleared by issuing PHY reset */
        unsigned int  reserved_1       : 8;  /* bit[24-31]: -- */
    } reg;
} SOC_HIPACKPHY_PHYDBG_UNION;
#endif
#define SOC_HIPACKPHY_PHYDBG_dqs_gated_error_START   (0)
#define SOC_HIPACKPHY_PHYDBG_dqs_gated_error_END     (7)
#define SOC_HIPACKPHY_PHYDBG_dqsb_gated_error_START  (16)
#define SOC_HIPACKPHY_PHYDBG_dqsb_gated_error_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_RETCTRL0_UNION
 �ṹ˵��  : RETCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00012400�����:32
 �Ĵ���˵��: ReTrain Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phyupd_resp  : 13; /* bit[0-12] : PHY update response latency
                                                        When PHY asserts dfi_phyupd_req to MC, MC should assert dfi_phyupd_ack no later than number of cycles set by the response latency */
        unsigned int  retrain_en   : 1;  /* bit[13]   : PHY Retraining Enable.
                                                        This field is used to control if PHY will be enabled to request memory controller for retraining. */
        unsigned int  gtrten       : 1;  /* bit[14]   : Gate Retraining Active.
                                                        This field controls if the gate retraining should be executed during retraining on-going. This filed should be asserted only after the initial gate training done.
                                                        Note: when dynamic_dqsg_ph_dis=0x0, gtrten should be set as 0x0 */
        unsigned int  rderten      : 1;  /* bit[15]   : Read data eye retrain enable */
        unsigned int  retrain_thrd : 16; /* bit[16-31]: Retraining threshold
                                                        PHY counts number of AREF issued by MC and when the number is equal to the threshold value, the retraining operation is triggerd to be started. Only a non zero value is valid. When Setting to 0x0, Disable Trigger PHY Update by Refresh Count. */
    } reg;
} SOC_HIPACKPHY_RETCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_RETCTRL0_phyupd_resp_START   (0)
#define SOC_HIPACKPHY_RETCTRL0_phyupd_resp_END     (12)
#define SOC_HIPACKPHY_RETCTRL0_retrain_en_START    (13)
#define SOC_HIPACKPHY_RETCTRL0_retrain_en_END      (13)
#define SOC_HIPACKPHY_RETCTRL0_gtrten_START        (14)
#define SOC_HIPACKPHY_RETCTRL0_gtrten_END          (14)
#define SOC_HIPACKPHY_RETCTRL0_rderten_START       (15)
#define SOC_HIPACKPHY_RETCTRL0_rderten_END         (15)
#define SOC_HIPACKPHY_RETCTRL0_retrain_thrd_START  (16)
#define SOC_HIPACKPHY_RETCTRL0_retrain_thrd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DMSEL_UNION
 �ṹ˵��  : DMSEL �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00504A0A�����:32
 �Ĵ���˵��: DM Swap Selection
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_dmswap_sel          : 4;  /* bit[0-3]  : [3:2] DM1 Swap Selection
                                                                     [1:0] DM0 Swap Selection */
        unsigned int  rt_onebyone               : 1;  /* bit[4]    : Enable retraining one by one
                                                                     grt/gdsrt and rdert be excuted one by one if the field be set. If only wdert be enabled, this field must be 0 */
        unsigned int  fast_wl2_en               : 1;  /* bit[5]    : Enable fast 2nd wirte leveling.
                                                                     Must guaratee the write latency and only be useful when CK-DQS skew < 0.5T */
        unsigned int  wlpulsecnt                : 2;  /* bit[6-7]  : WL WDQS Pulse Count
                                                                     ---- 1:1 Mode ----
                                                                     0: 1 WDQS Pulse (DDR3/4/LPDDR3)
                                                                     1: 2 WDQS Pulse (For LPDDR4)
                                                                     2: 3 WDQS Pulse
                                                                     3: 4 WDQS Pulse
                                                                     ---- 1:2 Mode ----
                                                                     0: 2 WDQS Pulse for LPDDR4 (1 WDQS Pulse for LPDDR3)
                                                                     1: 4 WDQS Pulse
                                                                     2: 6 WDQS Pulse
                                                                     3: 8 WDQS Pulse */
        unsigned int  tphy_wrdata               : 1;  /* bit[8]    : DFI tphy_wrdata Timing Parameter (WREN->WDATA) [Extension 2 bit at tphy_wrdata_ext]
                                                                     Criteria: 
                                                                     1. When Setting to 0x1, reg_OE_extend1T_en msut be 0x1
                                                                     2. When DX Loopback Test, Need to Set to 1'b0
                                                                     3. For LPDDR4 WREN Rank Switch, Need set DX Static Register 'dxctl_reg_phy_wdata_ranksw' as well */
        unsigned int  ddr4_dm_inv_en            : 1;  /* bit[9]    : DDR4 DM inverse enable, dram controller can define dm' s active level by setting this field.
                                                                     In case of internal loopback must set to 1. */
        unsigned int  rs_rstcont_passthrough    : 1;  /* bit[10]   : ac/dx ctl resetcont pass through */
        unsigned int  rs_rst_passthrough        : 1;  /* bit[11]   : ac/dx ctl reset pass through */
        unsigned int  rs_passthrough            : 1;  /* bit[12]   : 1: Path Pass through Directly in order to Reduce Latency (Using in Low-Frequency Mode due to Critial Timing Path) */
        unsigned int  phystop_en                : 1;  /* bit[13]   : Enable Trigger PHY Update by PHYSTOP Signal */
        unsigned int  phyupd_type_nopre         : 2;  /* bit[14-15]: PHY Update Type Value for Telling MC without Precharge before dfi_phyupd_ack asserted. */
        unsigned int  phyupd_type_pre           : 2;  /* bit[16-17]: PHY Update Type Value for Telling MC with Precharge before dfi_phyupd_ack asserted.
                                                                     Criteria: Keep it 0x0 */
        unsigned int  packdbgout                : 1;  /* bit[18]   : PACK Debug Signal Output Enable */
        unsigned int  rsneg_rstcont_passthrough : 1;  /* bit[19]   : ac/dx ctl resetcont pass through
                                                                     0: Negative Edge Clock Sample RS to Improve Hold-Time Margin between PACK & PHY
                                                                     Note: In V7R5, rsneg_passthrough/rsneg_rst_passthrough/rsneg_rstcont_passthrough/rx_rsneg_passthrough must set with the same value. (either all zeros, or all ones). */
        unsigned int  rsneg_rst_passthrough     : 1;  /* bit[20]   : ac/dx ctl reset pass through
                                                                     0: Negative Edge Clock Sample RS to Improve Hold-Time Margin between PACK & PHY
                                                                     Note: In V7R5, rsneg_passthrough/rsneg_rst_passthrough/rsneg_rstcont_passthrough/rx_rsneg_passthrough must set with the same value. (either all zeros, or all ones). */
        unsigned int  rsneg_passthrough         : 1;  /* bit[21]   : 0: Negative Edge Clock Sample RS to Improve Hold-Time Margin between PACK & PHY
                                                                     1: Path Pass through Directly in order to Reduce Latency (Using in Low-Frequency Mode due to Critial Timing Path)
                                                                     Note: In V7R5, rsneg_passthrough/rsneg_rst_passthrough/rsneg_rstcont_passthrough/rx_rsneg_passthrough must set with the same value. (either all zeros, or all ones). */
        unsigned int  wlexitmode                : 1;  /* bit[22]   : 0: DQS Floating before DRMA MRS WL Exit (DDR3/4/LPDDR3)
                                                                     1: DQS Keeping Drive before DRAM MRS WL Exit (LPDDR4)
                                                                     Note: Using cfgwlmrd Timer Setting to Keep DQS Drive */
        unsigned int  bl32atonthefly            : 1;  /* bit[23]   : LPDDR4 BL16/32 Selection at On-the-Fly
                                                                     0: Use BL16 at On-the-Fly to Reduce Training Time
                                                                     1: Use BL32 at On-the-Fly for Longer Burst Access */
        unsigned int  swapdfibyte_en            : 3;  /* bit[24-26]: Swap DFI Byte Lane
                                                                     000: No Swap
                                                                     001~101: Swap Table Setting */
        unsigned int  swapaddr_en               : 3;  /* bit[27-29]: Swap LPDDR2/3/4 ADDRESS bus
                                                                     000: No Swap
                                                                     001 ~101: Refer LPCA Swap Table */
        unsigned int  tphy_wrdata_ext           : 2;  /* bit[30-31]: tphy_wrdata Extension
                                                                     Total tphy_wrdata Bit is [2:0] */
    } reg;
} SOC_HIPACKPHY_DMSEL_UNION;
#endif
#define SOC_HIPACKPHY_DMSEL_dxctl_dmswap_sel_START           (0)
#define SOC_HIPACKPHY_DMSEL_dxctl_dmswap_sel_END             (3)
#define SOC_HIPACKPHY_DMSEL_rt_onebyone_START                (4)
#define SOC_HIPACKPHY_DMSEL_rt_onebyone_END                  (4)
#define SOC_HIPACKPHY_DMSEL_fast_wl2_en_START                (5)
#define SOC_HIPACKPHY_DMSEL_fast_wl2_en_END                  (5)
#define SOC_HIPACKPHY_DMSEL_wlpulsecnt_START                 (6)
#define SOC_HIPACKPHY_DMSEL_wlpulsecnt_END                   (7)
#define SOC_HIPACKPHY_DMSEL_tphy_wrdata_START                (8)
#define SOC_HIPACKPHY_DMSEL_tphy_wrdata_END                  (8)
#define SOC_HIPACKPHY_DMSEL_ddr4_dm_inv_en_START             (9)
#define SOC_HIPACKPHY_DMSEL_ddr4_dm_inv_en_END               (9)
#define SOC_HIPACKPHY_DMSEL_rs_rstcont_passthrough_START     (10)
#define SOC_HIPACKPHY_DMSEL_rs_rstcont_passthrough_END       (10)
#define SOC_HIPACKPHY_DMSEL_rs_rst_passthrough_START         (11)
#define SOC_HIPACKPHY_DMSEL_rs_rst_passthrough_END           (11)
#define SOC_HIPACKPHY_DMSEL_rs_passthrough_START             (12)
#define SOC_HIPACKPHY_DMSEL_rs_passthrough_END               (12)
#define SOC_HIPACKPHY_DMSEL_phystop_en_START                 (13)
#define SOC_HIPACKPHY_DMSEL_phystop_en_END                   (13)
#define SOC_HIPACKPHY_DMSEL_phyupd_type_nopre_START          (14)
#define SOC_HIPACKPHY_DMSEL_phyupd_type_nopre_END            (15)
#define SOC_HIPACKPHY_DMSEL_phyupd_type_pre_START            (16)
#define SOC_HIPACKPHY_DMSEL_phyupd_type_pre_END              (17)
#define SOC_HIPACKPHY_DMSEL_packdbgout_START                 (18)
#define SOC_HIPACKPHY_DMSEL_packdbgout_END                   (18)
#define SOC_HIPACKPHY_DMSEL_rsneg_rstcont_passthrough_START  (19)
#define SOC_HIPACKPHY_DMSEL_rsneg_rstcont_passthrough_END    (19)
#define SOC_HIPACKPHY_DMSEL_rsneg_rst_passthrough_START      (20)
#define SOC_HIPACKPHY_DMSEL_rsneg_rst_passthrough_END        (20)
#define SOC_HIPACKPHY_DMSEL_rsneg_passthrough_START          (21)
#define SOC_HIPACKPHY_DMSEL_rsneg_passthrough_END            (21)
#define SOC_HIPACKPHY_DMSEL_wlexitmode_START                 (22)
#define SOC_HIPACKPHY_DMSEL_wlexitmode_END                   (22)
#define SOC_HIPACKPHY_DMSEL_bl32atonthefly_START             (23)
#define SOC_HIPACKPHY_DMSEL_bl32atonthefly_END               (23)
#define SOC_HIPACKPHY_DMSEL_swapdfibyte_en_START             (24)
#define SOC_HIPACKPHY_DMSEL_swapdfibyte_en_END               (26)
#define SOC_HIPACKPHY_DMSEL_swapaddr_en_START                (27)
#define SOC_HIPACKPHY_DMSEL_swapaddr_en_END                  (29)
#define SOC_HIPACKPHY_DMSEL_tphy_wrdata_ext_START            (30)
#define SOC_HIPACKPHY_DMSEL_tphy_wrdata_ext_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_IOCTL_UNION
 �ṹ˵��  : IOCTL �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x43FFF999�����:32
 �Ĵ���˵��: IO control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  diff_dqs_en                 : 1;  /* bit[0]    : Differential DQS enable
                                                                       Move to DX_Static_Reg */
        unsigned int  dxiopldn                    : 1;  /* bit[1]    : Move to DX_Static_Reg */
        unsigned int  aciopldn                    : 1;  /* bit[2]    : Move to AC_Static_Reg */
        unsigned int  ioctl_genvref_dram_refsel_2 : 2;  /* bit[3-4]  : Move to AC/DX_Static_Reg */
        unsigned int  ioctl_genvref_dram_refsel_1 : 2;  /* bit[5-6]  : Move to AC/DX_Static_Reg */
        unsigned int  ioctl_genvref_dram_refsel_0 : 2;  /* bit[7-8]  : Move to AC/DX_Static_Reg */
        unsigned int  ioctl_genvref_dram_pd       : 2;  /* bit[9-10] : Move to AC/DX_Static_Reg */
        unsigned int  ronsel                      : 3;  /* bit[11-13]: Move to DX_Static_Reg */
        unsigned int  ronsel_dqs                  : 3;  /* bit[14-16]: Move to DX_Static_Reg */
        unsigned int  ronsel_ac1t                 : 3;  /* bit[17-19]: Move to AC_Static_Reg */
        unsigned int  ronsel_ac2t                 : 3;  /* bit[20-22]: Move to AC_Static_Reg */
        unsigned int  ronsel_ck                   : 3;  /* bit[23-25]: Move to AC_Static_Reg */
        unsigned int  odtsel                      : 3;  /* bit[26-28]: Dummy Reg - Not Used */
        unsigned int  odtsel_dqs                  : 3;  /* bit[29-31]: Move to DX_Static_Reg */
    } reg;
} SOC_HIPACKPHY_IOCTL_UNION;
#endif
#define SOC_HIPACKPHY_IOCTL_diff_dqs_en_START                  (0)
#define SOC_HIPACKPHY_IOCTL_diff_dqs_en_END                    (0)
#define SOC_HIPACKPHY_IOCTL_dxiopldn_START                     (1)
#define SOC_HIPACKPHY_IOCTL_dxiopldn_END                       (1)
#define SOC_HIPACKPHY_IOCTL_aciopldn_START                     (2)
#define SOC_HIPACKPHY_IOCTL_aciopldn_END                       (2)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_refsel_2_START  (3)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_refsel_2_END    (4)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_refsel_1_START  (5)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_refsel_1_END    (6)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_refsel_0_START  (7)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_refsel_0_END    (8)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_pd_START        (9)
#define SOC_HIPACKPHY_IOCTL_ioctl_genvref_dram_pd_END          (10)
#define SOC_HIPACKPHY_IOCTL_ronsel_START                       (11)
#define SOC_HIPACKPHY_IOCTL_ronsel_END                         (13)
#define SOC_HIPACKPHY_IOCTL_ronsel_dqs_START                   (14)
#define SOC_HIPACKPHY_IOCTL_ronsel_dqs_END                     (16)
#define SOC_HIPACKPHY_IOCTL_ronsel_ac1t_START                  (17)
#define SOC_HIPACKPHY_IOCTL_ronsel_ac1t_END                    (19)
#define SOC_HIPACKPHY_IOCTL_ronsel_ac2t_START                  (20)
#define SOC_HIPACKPHY_IOCTL_ronsel_ac2t_END                    (22)
#define SOC_HIPACKPHY_IOCTL_ronsel_ck_START                    (23)
#define SOC_HIPACKPHY_IOCTL_ronsel_ck_END                      (25)
#define SOC_HIPACKPHY_IOCTL_odtsel_START                       (26)
#define SOC_HIPACKPHY_IOCTL_odtsel_END                         (28)
#define SOC_HIPACKPHY_IOCTL_odtsel_dqs_START                   (29)
#define SOC_HIPACKPHY_IOCTL_odtsel_dqs_END                     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DQSSEL_UNION
 �ṹ˵��  : DQSSEL �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0xFF00FF00�����:32
 �Ĵ���˵��: Swap of DQ in PHY
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dqswap_sel : 32; /* bit[0-31]: DQ swap in PHY
                                                     Each bit decides the relative DQS with DQ
                                                     1: Relative to DQS1
                                                     0: Relative to DQS0 
                                                     Move to DX_Static_Reg */
    } reg;
} SOC_HIPACKPHY_DQSSEL_UNION;
#endif
#define SOC_HIPACKPHY_DQSSEL_dqswap_sel_START  (0)
#define SOC_HIPACKPHY_DQSSEL_dqswap_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYCTRL1_UNION
 �ṹ˵��  : PHYCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00A00000�����:32
 �Ĵ���˵��: AC PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0     : 16; /* bit[0-15] :  */
        unsigned int  ac_pll_thrm    : 1;  /* bit[16]   : Dummy Reg - Not Used */
        unsigned int  ac_pll_testpem : 1;  /* bit[17]   : Dummy Reg - Not Used */
        unsigned int  ac_pll_testen  : 1;  /* bit[18]   : Move to AC_Static_Reg */
        unsigned int  ac_pll_init    : 1;  /* bit[19]   : Move to AC_Static_Reg */
        unsigned int  ac_pll_cpi     : 3;  /* bit[20-22]: Move to AC_Static_Reg */
        unsigned int  ac_pll_sp      : 3;  /* bit[23-25]: Move to AC_Static_Reg */
        unsigned int  ac_pll_lt      : 2;  /* bit[26-27]: Move to AC_Static_Reg */
        unsigned int  ac_pll_calt    : 1;  /* bit[28]   : Dummy Reg - Not Used */
        unsigned int  ac_pll_calm    : 1;  /* bit[29]   : Dummy Reg - Not Used */
        unsigned int  ac_pll_cal     : 1;  /* bit[30]   : Dummy Reg - Not Used */
        unsigned int  reserved_1     : 1;  /* bit[31]   :  */
    } reg;
} SOC_HIPACKPHY_PHYCTRL1_UNION;
#endif
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_thrm_START     (16)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_thrm_END       (16)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_testpem_START  (17)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_testpem_END    (17)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_testen_START   (18)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_testen_END     (18)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_init_START     (19)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_init_END       (19)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_cpi_START      (20)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_cpi_END        (22)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_sp_START       (23)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_sp_END         (25)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_lt_START       (26)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_lt_END         (27)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_calt_START     (28)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_calt_END       (28)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_calm_START     (29)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_calm_END       (29)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_cal_START      (30)
#define SOC_HIPACKPHY_PHYCTRL1_ac_pll_cal_END        (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNCKCTRL_UNION
 �ṹ˵��  : DXNCKCTRL �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is for PLL phase select within the PHY. And should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dx_ckd2      : 3;  /* bit[0-2] : Dummy Reg - Not Used */
        unsigned int  dx_ck0p_mclk : 3;  /* bit[3-5] : Move to DX_Static_Reg */
        unsigned int  reserved     : 26; /* bit[6-31]:  */
    } reg;
} SOC_HIPACKPHY_DXNCKCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DXNCKCTRL_dx_ckd2_START       (0)
#define SOC_HIPACKPHY_DXNCKCTRL_dx_ckd2_END         (2)
#define SOC_HIPACKPHY_DXNCKCTRL_dx_ck0p_mclk_START  (3)
#define SOC_HIPACKPHY_DXNCKCTRL_dx_ck0p_mclk_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYPLLCTRL_AC_UNION
 �ṹ˵��  : PHYPLLCTRL_AC �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: PHY PLL control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ac_pll_test : 8;  /* bit[0-7] : AC PLL test mode
                                                      1: Test mode
                                                      0: Normal mode
                                                      Move to AC_Static_Reg */
        unsigned int  reserved    : 23; /* bit[8-30]:  */
        unsigned int  ac_pll_lock : 1;  /* bit[31]  : AC PLL LOCK signal
                                                      1: Locked
                                                      0: Not Locked */
    } reg;
} SOC_HIPACKPHY_PHYPLLCTRL_AC_UNION;
#endif
#define SOC_HIPACKPHY_PHYPLLCTRL_AC_ac_pll_test_START  (0)
#define SOC_HIPACKPHY_PHYPLLCTRL_AC_ac_pll_test_END    (7)
#define SOC_HIPACKPHY_PHYPLLCTRL_AC_ac_pll_lock_START  (31)
#define SOC_HIPACKPHY_PHYPLLCTRL_AC_ac_pll_lock_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYPLLCTRL_DX_UNION
 �ṹ˵��  : PHYPLLCTRL_DX �Ĵ����ṹ���塣��ַƫ����:0x009C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PHY PLL control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dx_pll_test : 16; /* bit[0-15] : PLL Test for 16-Bit Data Block
                                                       7:0 - 16-Bit Block 0
                                                       15:8 - 16-Bit Block 1
                                                       Move to DX_Static_Reg */
        unsigned int  reserved    : 12; /* bit[16-27]:  */
        unsigned int  dx_pll_lock : 4;  /* bit[28-31]: ND: Number of DATA PHY Block
                                                       DX PLL LOCK signals for each bytelane
                                                       1: Locked
                                                       0: Not Locked
                                                       (In Balong, only bit0 is valid) */
    } reg;
} SOC_HIPACKPHY_PHYPLLCTRL_DX_UNION;
#endif
#define SOC_HIPACKPHY_PHYPLLCTRL_DX_dx_pll_test_START  (0)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX_dx_pll_test_END    (15)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX_dx_pll_lock_START  (28)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX_dx_pll_lock_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_SWTMODE_UNION
 �ṹ˵��  : SWTMODE �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is for setting S/W training mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw_wlmode     : 1;  /* bit[0]    : Set this bit to 1 when performing S/W write leveling training */
        unsigned int  sw_gtmode     : 1;  /* bit[1]    : Set this bit to 1 when performing S/W trianing gate training or GDS training */
        unsigned int  reserved_0    : 2;  /* bit[2-3]  :  */
        unsigned int  sw_wlmodeb    : 8;  /* bit[4-11] : Set with proper values when performing S/W LP4 CBT training. Each bit indicated a bytelane.
                                                         1: dqs be output mode
                                                         0: dqs be input mode
                                                         Note: the real valid bit-width is the number of bytelane. */
        unsigned int  reserved_1    : 19; /* bit[12-30]:  */
        unsigned int  wl_wdqs_gated : 1;  /* bit[31]   : Used to disable Write Leveling wdqs strobe when tuning the related PH/BDL to prevent glitch.
                                                         1: gated (disable wdqs strobe)
                                                         0: not gated */
    } reg;
} SOC_HIPACKPHY_SWTMODE_UNION;
#endif
#define SOC_HIPACKPHY_SWTMODE_sw_wlmode_START      (0)
#define SOC_HIPACKPHY_SWTMODE_sw_wlmode_END        (0)
#define SOC_HIPACKPHY_SWTMODE_sw_gtmode_START      (1)
#define SOC_HIPACKPHY_SWTMODE_sw_gtmode_END        (1)
#define SOC_HIPACKPHY_SWTMODE_sw_wlmodeb_START     (4)
#define SOC_HIPACKPHY_SWTMODE_sw_wlmodeb_END       (11)
#define SOC_HIPACKPHY_SWTMODE_wl_wdqs_gated_START  (31)
#define SOC_HIPACKPHY_SWTMODE_wl_wdqs_gated_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_SWTWLDQS_UNION
 �ṹ˵��  : SWTWLDQS �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is for issuing write DQS in S/W write leveling training
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw_wl_dqs : 1;  /* bit[0]   : Write 1 to this bit once will issue one DQS pulse from PHY to DRAM */
        unsigned int  reserved  : 31; /* bit[1-31]: -- */
    } reg;
} SOC_HIPACKPHY_SWTWLDQS_UNION;
#endif
#define SOC_HIPACKPHY_SWTWLDQS_sw_wl_dqs_START  (0)
#define SOC_HIPACKPHY_SWTWLDQS_sw_wl_dqs_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_SWTRLT_UNION
 �ṹ˵��  : SWTRLT �Ĵ����ṹ���塣��ַƫ����:0x00A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: S/W training result
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wl_dq_result : 8;  /* bit[0-7]  : Each bit is corresponded to one byte lane. 
                                                        LSB is bytelane0.
                                                        MSB is bytelane7. */
        unsigned int  gt_result    : 8;  /* bit[8-15] : Each bit is corresponded to one byte lane. 
                                                        LSB is bytelane0.
                                                        MSB is bytelane7. */
        unsigned int  gds_result   : 8;  /* bit[16-23]: Each bit is corresponded to one byte lane. 
                                                        LSB is bytelane0.
                                                        MSB is bytelane7. */
        unsigned int  reserved     : 8;  /* bit[24-31]: -- */
    } reg;
} SOC_HIPACKPHY_SWTRLT_UNION;
#endif
#define SOC_HIPACKPHY_SWTRLT_wl_dq_result_START  (0)
#define SOC_HIPACKPHY_SWTRLT_wl_dq_result_END    (7)
#define SOC_HIPACKPHY_SWTRLT_gt_result_START     (8)
#define SOC_HIPACKPHY_SWTRLT_gt_result_END       (15)
#define SOC_HIPACKPHY_SWTRLT_gds_result_START    (16)
#define SOC_HIPACKPHY_SWTRLT_gds_result_END      (23)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYCTRL2_UNION
 �ṹ˵��  : PHYCTRL2 �Ĵ����ṹ���塣��ַƫ����:0x00AC����ֵ:0x0000000A�����:32
 �Ĵ���˵��: PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_dqsgerror            : 1;  /* bit[0]   : Control DATA16BIT_blk.BUFRESETCONTN_gated_DQSGERROR */
        unsigned int  phy_gatetdc              : 1;  /* bit[1]   : Control DATA16BIT_blk.BUFRESETCONTN_gated_TDC */
        unsigned int  phy_odten_gated          : 1;  /* bit[2]   : Control DATA16BIT_blk.reg_ODTEN_Gated */
        unsigned int  phy_dummypad_use         : 1;  /* bit[3]   : Control DATA16BIT_blk.reg_dummypad_use */
        unsigned int  phy_dyn_pupden           : 1;  /* bit[4]   : Control DATA16BIT_blk.reg_dynamic_PUPDEN_16b */
        unsigned int  dx_reg_dvalid_selfgen_en : 1;  /* bit[5]   : 0: GDS use DFI rden signals to generate the dvalid signal (default)
                                                                   1: GDS use self mechanism to generate the dvalid signal
                                                                   Move to DX_Static_Reg */
        unsigned int  reserved                 : 26; /* bit[6-31]:  */
    } reg;
} SOC_HIPACKPHY_PHYCTRL2_UNION;
#endif
#define SOC_HIPACKPHY_PHYCTRL2_phy_dqsgerror_START             (0)
#define SOC_HIPACKPHY_PHYCTRL2_phy_dqsgerror_END               (0)
#define SOC_HIPACKPHY_PHYCTRL2_phy_gatetdc_START               (1)
#define SOC_HIPACKPHY_PHYCTRL2_phy_gatetdc_END                 (1)
#define SOC_HIPACKPHY_PHYCTRL2_phy_odten_gated_START           (2)
#define SOC_HIPACKPHY_PHYCTRL2_phy_odten_gated_END             (2)
#define SOC_HIPACKPHY_PHYCTRL2_phy_dummypad_use_START          (3)
#define SOC_HIPACKPHY_PHYCTRL2_phy_dummypad_use_END            (3)
#define SOC_HIPACKPHY_PHYCTRL2_phy_dyn_pupden_START            (4)
#define SOC_HIPACKPHY_PHYCTRL2_phy_dyn_pupden_END              (4)
#define SOC_HIPACKPHY_PHYCTRL2_dx_reg_dvalid_selfgen_en_START  (5)
#define SOC_HIPACKPHY_PHYCTRL2_dx_reg_dvalid_selfgen_en_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_IOCTL1_UNION
 �ṹ˵��  : IOCTL1 �Ĵ����ṹ���塣��ַƫ����:0x00B0����ֵ:0x00F00000�����:32
 �Ĵ���˵��: PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ioctl_genvref_range_2      : 6;  /* bit[0-5]  : Move to AC/DX_Static_Reg */
        unsigned int  odt_ioctl_rdsel_p          : 3;  /* bit[6-8]  : Move to DX_Static_Reg */
        unsigned int  odt_ioctl_rdsel_n          : 3;  /* bit[9-11] : Move to DX_Static_Reg */
        unsigned int  ioctl_genvref_pd           : 6;  /* bit[12-17]: Move to AC/DX_Static_Reg */
        unsigned int  ioctl_genvref_dram_range_2 : 2;  /* bit[18-19]: Move to AC/DX_Static_Reg */
        unsigned int  ioctl_genvref_dram_range_1 : 2;  /* bit[20-21]: Move to AC/DX_Static_Reg */
        unsigned int  ioctl_genvref_dram_range_0 : 2;  /* bit[22-23]: Move to AC/DX_Static_Reg */
        unsigned int  ioctl_squeach_pd           : 4;  /* bit[24-27]: Move to DX_Static_Reg */
        unsigned int  odt_ioctl_ronsel           : 3;  /* bit[28-30]: Move to DX_Static_Reg */
        unsigned int  ioctl_odt_iopldn           : 1;  /* bit[31]   : Move to DX_Static_Reg */
    } reg;
} SOC_HIPACKPHY_IOCTL1_UNION;
#endif
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_range_2_START       (0)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_range_2_END         (5)
#define SOC_HIPACKPHY_IOCTL1_odt_ioctl_rdsel_p_START           (6)
#define SOC_HIPACKPHY_IOCTL1_odt_ioctl_rdsel_p_END             (8)
#define SOC_HIPACKPHY_IOCTL1_odt_ioctl_rdsel_n_START           (9)
#define SOC_HIPACKPHY_IOCTL1_odt_ioctl_rdsel_n_END             (11)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_pd_START            (12)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_pd_END              (17)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_dram_range_2_START  (18)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_dram_range_2_END    (19)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_dram_range_1_START  (20)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_dram_range_1_END    (21)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_dram_range_0_START  (22)
#define SOC_HIPACKPHY_IOCTL1_ioctl_genvref_dram_range_0_END    (23)
#define SOC_HIPACKPHY_IOCTL1_ioctl_squeach_pd_START            (24)
#define SOC_HIPACKPHY_IOCTL1_ioctl_squeach_pd_END              (27)
#define SOC_HIPACKPHY_IOCTL1_odt_ioctl_ronsel_START            (28)
#define SOC_HIPACKPHY_IOCTL1_odt_ioctl_ronsel_END              (30)
#define SOC_HIPACKPHY_IOCTL1_ioctl_odt_iopldn_START            (31)
#define SOC_HIPACKPHY_IOCTL1_ioctl_odt_iopldn_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_IOCTL2_UNION
 �ṹ˵��  : IOCTL2 �Ĵ����ṹ���塣��ַƫ����:0x00B4����ֵ:0xBF03FFFF�����:32
 �Ĵ���˵��: PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ioctl_genvref_range_0  : 6;  /* bit[0-5]  : Move to AC/DX_Static_Reg */
        unsigned int  ioctl_genvref_range_1  : 6;  /* bit[6-11] : Move to AC/DX_Static_Reg */
        unsigned int  ioctl_genvref_refsel_0 : 6;  /* bit[12-17]: Move to AC/DX_Static_Reg */
        unsigned int  ioctl_genvref_refsel_1 : 6;  /* bit[18-23]: Move to AC/DX_Static_Reg */
        unsigned int  ioctl_genvref_refsel_2 : 6;  /* bit[24-29]: Move to AC/DX_Static_Reg */
        unsigned int  top_topctl_odt_o       : 1;  /* bit[30]   : Dummy Reg - Not Used */
        unsigned int  top_topctl_odt_oe      : 1;  /* bit[31]   : Dummy Reg - Not Used */
    } reg;
} SOC_HIPACKPHY_IOCTL2_UNION;
#endif
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_range_0_START   (0)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_range_0_END     (5)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_range_1_START   (6)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_range_1_END     (11)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_refsel_0_START  (12)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_refsel_0_END    (17)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_refsel_1_START  (18)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_refsel_1_END    (23)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_refsel_2_START  (24)
#define SOC_HIPACKPHY_IOCTL2_ioctl_genvref_refsel_2_END    (29)
#define SOC_HIPACKPHY_IOCTL2_top_topctl_odt_o_START        (30)
#define SOC_HIPACKPHY_IOCTL2_top_topctl_odt_o_END          (30)
#define SOC_HIPACKPHY_IOCTL2_top_topctl_odt_oe_START       (31)
#define SOC_HIPACKPHY_IOCTL2_top_topctl_odt_oe_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_TRAINMADDRTG1_UNION
 �ṹ˵��  : TRAINMADDRTG1 �Ĵ����ṹ���塣��ַƫ����:0x00B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register specify the starting memory address where can be used to do data training. The minimum space required for data training should be 64-bytes, and the allocated memory should be 64-bytes alignment.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dtbank_tg1 : 3;  /* bit[0-2]  : Data Training Bank Address for BG toggling.
                                                      This register is used as the memory bank address where is used during data training if required for BG toggling.
                                                      [***Constraint***]
                                                      1. When RANKEN.dtbankgrp==RANKEN.dtbankgrp_tg1, Make TRAINMADDR.dtbank==TRAINMADDRTG1.dtbank_tg1
                                                      2. dtbank_tg1[2] Must be equal dtbankgrp_tg1[0] */
        unsigned int  reserved   : 1;  /* bit[3]    : -- */
        unsigned int  dtcol_tg1  : 12; /* bit[4-15] : Data Training Column Address for BG toggling.
                                                      This register is used as the column address which is used during data training if required for BG toggling. The field should be 0. */
        unsigned int  dtrow_tg1  : 16; /* bit[16-31]: Data Training Row Address for BG toggling.
                                                      This register is used as the memory row address where is used during data training if required for BG toggling. */
    } reg;
} SOC_HIPACKPHY_TRAINMADDRTG1_UNION;
#endif
#define SOC_HIPACKPHY_TRAINMADDRTG1_dtbank_tg1_START  (0)
#define SOC_HIPACKPHY_TRAINMADDRTG1_dtbank_tg1_END    (2)
#define SOC_HIPACKPHY_TRAINMADDRTG1_dtcol_tg1_START   (4)
#define SOC_HIPACKPHY_TRAINMADDRTG1_dtcol_tg1_END     (15)
#define SOC_HIPACKPHY_TRAINMADDRTG1_dtrow_tg1_START   (16)
#define SOC_HIPACKPHY_TRAINMADDRTG1_dtrow_tg1_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DRAMTIMER5_UNION
 �ṹ˵��  : DRAMTIMER5 �Ĵ����ṹ���塣��ַƫ����:0x0BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_wl      : 8;  /* bit[0-7]  : Write latency (AL+CWL) - Uused to Calculate twt(Same Rank and Different Rank), twr
                                                     -------------------LPDDR4---------------------
                                                     In LPDDR4, Need to Add Additional 3 (WL+3) */
        unsigned int  t_odton_h : 4;  /* bit[8-11] : ODT turn-on latency high 4 bits (Number of cycle from write command to assert of ODT) */
        unsigned int  reserved  : 20; /* bit[12-31]: -- */
    } reg;
} SOC_HIPACKPHY_DRAMTIMER5_UNION;
#endif
#define SOC_HIPACKPHY_DRAMTIMER5_t_wl_START       (0)
#define SOC_HIPACKPHY_DRAMTIMER5_t_wl_END         (7)
#define SOC_HIPACKPHY_DRAMTIMER5_t_odton_h_START  (8)
#define SOC_HIPACKPHY_DRAMTIMER5_t_odton_h_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_VREFTCTRL_UNION
 �ṹ˵��  : VREFTCTRL �Ĵ����ṹ���塣��ַƫ����:0x00C0����ֵ:0x00000010�����:32
 �Ĵ���˵��: VREF Training Control Register.
            This register specify the common settings of the VREF training.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vreft_bist_runtime : 8;  /* bit[0-7] : VREF Training BIST Run Count.
                                                             This register specify the number of clock cycles waits after enabling the bist engine to verify if current DRAM VREF or host PHY VREF setting is okay during VREF training. The actual number of cycles waits is calculated as:
                                                             (vreft_bist_runtime+1) x 128 cycles. */
        unsigned int  reserved           : 24; /* bit[8-31]: -- */
    } reg;
} SOC_HIPACKPHY_VREFTCTRL_UNION;
#endif
#define SOC_HIPACKPHY_VREFTCTRL_vreft_bist_runtime_START  (0)
#define SOC_HIPACKPHY_VREFTCTRL_vreft_bist_runtime_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DVRFTCTRL_UNION
 �ṹ˵��  : DVRFTCTRL �Ĵ����ṹ���塣��ַƫ����:0x00C4����ֵ:0x00041032�����:32
 �Ĵ���˵��: DRAM VREF Training Control Regiser.
            Register in this field are used to controls the behavior of the VREF training.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dvreft_maxv   : 6;  /* bit[0-5]  : DRAM VREF(DQ) Training Maximum Value.
                                                         This field is used as the maximum allowed value used at the DRAM side during VREF(DQ) training. The VREF(DQ) value at the DRAM side will continuously increased until the testing failed or the "dvreft_maxv" value reached. If the current training value increased greater than the maximum value, the increased value will be limited at the maximum value. */
        unsigned int  dvreft_minv   : 6;  /* bit[6-11] : DRAM VREF(DQ) Training Minimum Value.
                                                         This field is used as the minimum allowed value used at the DRAM side during VREF(DQ) training. The VREF(DQ) value at the DRAM side will continuously decreased until the testing failed or the "dvreft_minv" value reached. If the current training value decreased smaller than the minimum value, the decreased value will be limited at the minimum value. */
        unsigned int  dvreft_step   : 6;  /* bit[12-17]: DRAM VREF(DQ) Training Step Size.
                                                         This field is used as the increase/decrease value during the DRAM VREF(DQ) training. */
        unsigned int  dvreft_hckpts : 4;  /* bit[18-21]: DRAM VREF(DQ) Training Horizontal Check Points.
                                                         This field is used to specify if the write DQ timing should be checks during DRAM VREF(DQ) training. The write DQ phase of will be adjust left and right from current phase to verify if current VREF(DQ) value is correct. If any testing points of current VREF(DQ) failed, the current VREF(DQ) will be treated as either upper or lower boundary of the DRAM VREF(DQ) training. 
                                                         Setting the MSB bit of this field to a '1' will enable the horizontal testing points. Setting the MSB bit of this field to a '0' will disable the horizontal check points. Only current write DQ phase will be check at specific VREF(DQ).
                                                         4'b0XXX : Horizontal checking disabled.
                                                         4'b1000 : Reserved
                                                         4'b1001 : +/- 1 WDQ PLL Phase
                                                         4'b1010 : +/- 2 WDQ PLL Phase
                                                         ......
                                                         4'b1111 : +/- 7 WDQ PLL Phase */
        unsigned int  reserved      : 9;  /* bit[22-30]: -- */
        unsigned int  pdaen         : 1;  /* bit[31]   : Per-DRAM-Addressability Enable.
                                                         This register is used to controls if the PDA mode is turned-on during the DRAM side VREF(DQ) training. If this field is set to a '1', the PDA mode will be turned-on before VREF(DQ) setting. If this field is set to a '0', the PDA mode will be disabled.
                                                         Note that this field only valid while the DRAM type is specified as DDR4. */
    } reg;
} SOC_HIPACKPHY_DVRFTCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_maxv_START    (0)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_maxv_END      (5)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_minv_START    (6)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_minv_END      (11)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_step_START    (12)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_step_END      (17)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_hckpts_START  (18)
#define SOC_HIPACKPHY_DVRFTCTRL_dvreft_hckpts_END    (21)
#define SOC_HIPACKPHY_DVRFTCTRL_pdaen_START          (31)
#define SOC_HIPACKPHY_DVRFTCTRL_pdaen_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_HVRFTCTRL_UNION
 �ṹ˵��  : HVRFTCTRL �Ĵ����ṹ���塣��ַƫ����:0x00C8����ֵ:0x00081010�����:32
 �Ĵ���˵��: Host VREF Training Control Regiser.
            Register in this field are used to controls the behavior of the Host VREF training.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hvreft_maxv   : 6;  /* bit[0-5]  : Host PHY VREF Training Maximum Value.
                                                         This field is used as the maximum allowed value used at the host PHY side during VREF(DQ) training. The VREF(DQ) value at the DRAM side will continuously increased until the testing failed or the "hvreft_maxv" value reached. If the current training value increased greater than the maximum value, the increased value will be limited at the maximum value. */
        unsigned int  hvreft_minv   : 6;  /* bit[6-11] : Host PHY VREF Training Minimum Value.
                                                         This field is used as the minimum allowed value used at the host PHY side during VREF(DQ) training. The VREF(DQ) value at the host PHY side will continuously decreased until the testing failed or the "hvreft_minv" value reached. If the current training value decreased smaller than the minimum value, the decreased value will be limited at the minimum value. */
        unsigned int  hvreft_step   : 6;  /* bit[12-17]: Host PHY VREF(DQ) Training Step Size.
                                                         This field is used as the increase/decrease value during the host PHY VREF(DQ) training. */
        unsigned int  hvreft_hckpts : 6;  /* bit[18-23]: Host PHY VREF Training Horizontal Check Points.
                                                         This field is used to specify if the write DQ timing should be checks during host PHY VREF(DQ) training. The write DQ phase of will be adjust left and right from current phase to verify if current VREF(DQ) value is correct. If any testing points of current VREF(DQ) failed, the current VREF(DQ) will be treated as either upper or lower boundary of the host PHY VREF(DQ) training. 
                                                         Setting the MSB bit of this field to a '1' will enable the horizontal testing points. Setting the MSB bit of this field to a '0' will disable the horizontal check points. Only current write DQ phase will be check at specific VREF(DQ).
                                                         6'b0XXXXX : Horizontal checking disabled.
                                                         6'b100000 : Reserved
                                                         6'b100001 : +/- 1 RDQS BDL
                                                         6'b100010 : +/- 2 RDQS BDL
                                                         ......
                                                         6'b111111 : +/- 31 RDQS BDL
                                                         For Host PHY VREF(AC) training, due to no receiving CA delay value adjustable, this value will no be used, and only center point checked. */
        unsigned int  reserved      : 8;  /* bit[24-31]: -- */
    } reg;
} SOC_HIPACKPHY_HVRFTCTRL_UNION;
#endif
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_maxv_START    (0)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_maxv_END      (5)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_minv_START    (6)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_minv_END      (11)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_step_START    (12)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_step_END      (17)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_hckpts_START  (18)
#define SOC_HIPACKPHY_HVRFTCTRL_hvreft_hckpts_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_TRAINCTRL1_UNION
 �ṹ˵��  : TRAINCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x00D0����ֵ:0xF066F366�����:32
 �Ĵ���˵��: This register control the data training.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdet_samp_num      : 4;  /* bit[0-3]  : Write DET sample number control. The multiple sample is used to overcome the meta situations.
                                                              Valid value: 1~15 */
        unsigned int  wdet_trysamp_num   : 4;  /* bit[4-7]  : Write DET try sample number control. The field is used to constrain the try times of multiple sample in deskew. User can enlarge the value or set to 0 to get more accuracy to data training.
                                                              0: disable trysamp_num constraint
                                                              Valid value: 1~15 (Unit: 4 times) */
        unsigned int  cfg_fast_rdet_cnt  : 3;  /* bit[8-10] : The field indicate the number of retrain loops during fast read data eye training */
        unsigned int  wdet_ct_dqs_en     : 1;  /* bit[11]   : Center write dq enable */
        unsigned int  wrdet_av_en        : 1;  /* bit[12]   : Write DET average stage enable */
        unsigned int  wdet_rbs_en        : 1;  /* bit[13]   : Write DET right boundary search enable. */
        unsigned int  wdet_ds_en         : 1;  /* bit[14]   : Write DET deskew enable. */
        unsigned int  wdet_lbs_en        : 1;  /* bit[15]   : Write DET left boundary search enable. */
        unsigned int  rdet_samp_num      : 4;  /* bit[16-19]: Read DET sample number control. The multiple sample is used to overcome the meta situations.
                                                              Valid value: 1~15 */
        unsigned int  rdet_trysamp_num   : 4;  /* bit[20-23]: Read DET try sample number control. The field is used to constrain the try times of multiple sample in deskew. User can enlarge the value or set to 0 to get more accuracy to data training.
                                                              0: disable trysamp_num constraint
                                                              Valid value: 1~15 (Unit: 4 times) */
        unsigned int  cfg_comp_en        : 1;  /* bit[24]   : Fast read data eye training compensation enable, cannot use */
        unsigned int  fast_rdet_en       : 1;  /* bit[25]   : Fast read data eye training enable */
        unsigned int  rdet_dq_evenodd_en : 1;  /* bit[26]   : DQ Even/Odd Training Separation Enable. If this field is enabled, rdet_fcomp_en should be set as 0x1 to make training can recognize even/odd conditions. */
        unsigned int  rdet_ct_dqs_en     : 1;  /* bit[27]   : Center read dq enable */
        unsigned int  rdet_av_en         : 1;  /* bit[28]   : Read DET average stage enable */
        unsigned int  rdet_rbs_en        : 1;  /* bit[29]   : Read DET right boundary search enable. */
        unsigned int  rdet_ds_en         : 1;  /* bit[30]   : Read DET deskew enable. */
        unsigned int  rdet_lbs_en        : 1;  /* bit[31]   : Read DET left boundary search enable. */
    } reg;
} SOC_HIPACKPHY_TRAINCTRL1_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_samp_num_START       (0)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_samp_num_END         (3)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_trysamp_num_START    (4)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_trysamp_num_END      (7)
#define SOC_HIPACKPHY_TRAINCTRL1_cfg_fast_rdet_cnt_START   (8)
#define SOC_HIPACKPHY_TRAINCTRL1_cfg_fast_rdet_cnt_END     (10)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_ct_dqs_en_START      (11)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_ct_dqs_en_END        (11)
#define SOC_HIPACKPHY_TRAINCTRL1_wrdet_av_en_START         (12)
#define SOC_HIPACKPHY_TRAINCTRL1_wrdet_av_en_END           (12)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_rbs_en_START         (13)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_rbs_en_END           (13)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_ds_en_START          (14)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_ds_en_END            (14)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_lbs_en_START         (15)
#define SOC_HIPACKPHY_TRAINCTRL1_wdet_lbs_en_END           (15)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_samp_num_START       (16)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_samp_num_END         (19)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_trysamp_num_START    (20)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_trysamp_num_END      (23)
#define SOC_HIPACKPHY_TRAINCTRL1_cfg_comp_en_START         (24)
#define SOC_HIPACKPHY_TRAINCTRL1_cfg_comp_en_END           (24)
#define SOC_HIPACKPHY_TRAINCTRL1_fast_rdet_en_START        (25)
#define SOC_HIPACKPHY_TRAINCTRL1_fast_rdet_en_END          (25)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_dq_evenodd_en_START  (26)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_dq_evenodd_en_END    (26)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_ct_dqs_en_START      (27)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_ct_dqs_en_END        (27)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_av_en_START          (28)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_av_en_END            (28)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_rbs_en_START         (29)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_rbs_en_END           (29)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_ds_en_START          (30)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_ds_en_END            (30)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_lbs_en_START         (31)
#define SOC_HIPACKPHY_TRAINCTRL1_rdet_lbs_en_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_TRAINCTRL2_UNION
 �ṹ˵��  : TRAINCTRL2 �Ĵ����ṹ���塣��ַƫ����:0x00D4����ֵ:0x0000CC55�����:32
 �Ĵ���˵��: This register control the data training.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mrr_pat_a       : 8;  /* bit[0-7]  : MRR32/MPR0 pattern.This filed should follow the LPDDR2/3, DDR4 spec. */
        unsigned int  mrr_pat_b       : 8;  /* bit[8-15] : MRR40/MPR1 pattern. This filed should follow the LPDDR2/3, DDR4 spec. */
        unsigned int  mrr_pat_mask    : 8;  /* bit[16-23]: MRR/MPR pattern mask.
                                                           1: masked (does not compare data)
                                                           0: not masked */
        unsigned int  gds_automrg_en  : 1;  /* bit[24]   : GDS train/re-train auto tuning enable.
                                                           1'b1: enable gds auto margin tuning
                                                           1'b0: disable gds auto margin tuning (default) (will increase gds when GDS train/retrain is done)
                                                           K3V5 should use the 0x0 setting. */
        unsigned int  fast_gt_en      : 1;  /* bit[25]   : fast gate training during auto training or retraining. fast_dqsgsl_mrgn have set to 0 if this field asserted. */
        unsigned int  fast_gdst_en    : 1;  /* bit[26]   : fast gds training during auto training or retraining */
        unsigned int  mrr_bl4         : 1;  /* bit[27]   : MRR burst 4 indicator. If MRR was used in the Read DET, pack needs to know if MRR burst is 4 (LPDDR2) or 8 (LPDDR3).
                                                           1: MRR32/40 burst length = 4
                                                           0: MRR32/40 burst length = 8 (default) */
        unsigned int  mrr_pat_order   : 3;  /* bit[28-30]: MRR/MPR pattern order. If MRR/MPR was used in the Read DET, pack will issue 3 MRR/MPR commands. The order is indicated by bit0->bit1->bit2.
                                                           1: use MRR40/MPR1
                                                           0: use MRR32/MPR0 */
        unsigned int  rdet_method_sel : 1;  /* bit[31]   : Read DET method selection. 
                                                           1: When LPDDR2/3, use MRR32/40.
                                                            When DDR4, use MPR read.
                                                            When LPDDR4, use MPC Read DQ Calibration Command
                                                            Other DRAM types are not supourt.
                                                           0: use Write-then-Read */
    } reg;
} SOC_HIPACKPHY_TRAINCTRL2_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_a_START        (0)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_a_END          (7)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_b_START        (8)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_b_END          (15)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_mask_START     (16)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_mask_END       (23)
#define SOC_HIPACKPHY_TRAINCTRL2_gds_automrg_en_START   (24)
#define SOC_HIPACKPHY_TRAINCTRL2_gds_automrg_en_END     (24)
#define SOC_HIPACKPHY_TRAINCTRL2_fast_gt_en_START       (25)
#define SOC_HIPACKPHY_TRAINCTRL2_fast_gt_en_END         (25)
#define SOC_HIPACKPHY_TRAINCTRL2_fast_gdst_en_START     (26)
#define SOC_HIPACKPHY_TRAINCTRL2_fast_gdst_en_END       (26)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_bl4_START          (27)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_bl4_END            (27)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_order_START    (28)
#define SOC_HIPACKPHY_TRAINCTRL2_mrr_pat_order_END      (30)
#define SOC_HIPACKPHY_TRAINCTRL2_rdet_method_sel_START  (31)
#define SOC_HIPACKPHY_TRAINCTRL2_rdet_method_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_REGBANKCTRL_UNION
 �ṹ˵��  : REGBANKCTRL �Ĵ����ṹ���塣��ַƫ����:0x00D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register control the register bank.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_sel   : 1;  /* bit[0]   : register bank selection that related to DFS
                                                   0: select bank 0 while APB read/write
                                                   1: select bank 1 while APB read/write */
        unsigned int  op_sel   : 1;  /* bit[1]   : register bank selection that related to DFS. Note after switch the op_sel, should toggle phyconn_rst to reset PHY counter to prevent glitch due to ph/bdl changings.
                                                   0: select bank 0 for PHY operating
                                                   1: select bank 1 for PHY operating */
        unsigned int  reserved : 30; /* bit[2-31]:  */
    } reg;
} SOC_HIPACKPHY_REGBANKCTRL_UNION;
#endif
#define SOC_HIPACKPHY_REGBANKCTRL_wr_sel_START    (0)
#define SOC_HIPACKPHY_REGBANKCTRL_wr_sel_END      (0)
#define SOC_HIPACKPHY_REGBANKCTRL_op_sel_START    (1)
#define SOC_HIPACKPHY_REGBANKCTRL_op_sel_END      (1)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_TRAINCTRL3_UNION
 �ṹ˵��  : TRAINCTRL3 �Ĵ����ṹ���塣��ַƫ����:0x00DC����ֵ:0xEA620333�����:32
 �Ĵ���˵��: This register control the data training.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rpat_cnt_num      : 4;  /* bit[0-3]  : RDET pattern length control. This field is used to set the pattern length. The same RDET pattern will be extended as the following settings (field value+1):
                                                             0x0: pattern length=1
                                                             0x1: pattern length=2
                                                             ��
                                                             0xF: pattern length=16 */
        unsigned int  wpat_cnt_num      : 4;  /* bit[4-7]  : WDET pattern length control. This field is used to set the pattern length. The same WDET pattern will be extended as the following settings (field value+1):
                                                             0x0: pattern length=1
                                                             0x1: pattern length=2
                                                             ��
                                                             0xF: pattern length=16 */
        unsigned int  rpat_cnt_num_open : 4;  /* bit[8-11] : RDET/WDET pattern length control for eyeopen/deskew. This field is used to set the pattern length for eyeopen. The same RDET pattern will be extended as the following settings (field value+1):
                                                             0x0: pattern length=1
                                                             0x1: pattern length=2
                                                             ��
                                                             0xF: pattern length=16 */
        unsigned int  wderten           : 1;  /* bit[12]   : Write data eye retrain enable. (For LPDDR4) */
        unsigned int  wdet_rank_en      : 1;  /* bit[13]   : Multi rank training enable. This register is used to enable multi rank training during write data eye retraining (For LPDDR4) */
        unsigned int  wrenrkswen        : 1;  /* bit[14]   : WREN Rank Switch Enable
                                                             0: Disable WREN Rank Switch
                                                             1: Enable to Make WREN Rank Switch to Select Different Write DQ Rank Delay (For LPDDR4) */
        unsigned int  nopre4wrdet       : 1;  /* bit[15]   : Not Send Precharge (before MPC commands) for Write/Read DET by LPDDR4 MPC Command 
                                                             1: Not Send Precharge for WRDET by LPDDR4 MPC Commands */
        unsigned int  gdsrt_backtap     : 3;  /* bit[16-18]: GDS re-train back tap. This field is used to control the number of back tap when GDS re-train.
                                                             The valid range is 1~7.
                                                             The recommended range is 1~2. */
        unsigned int  rdet_rank_en      : 1;  /* bit[19]   : Multi rank training enable. This register is used to enable multi rank training during read data eye retraining or fast read data eye training */
        unsigned int  rdet_dbi_en       : 1;  /* bit[20]   : RDET for DBI enable.
                                                             1: enable
                                                             0: disable (default)
                                                             If this field is enabled, rdet_fcomp_en should be set as 0x1 to make training can recognize pass/fail conditions. */
        unsigned int  cat_pat_toggle_en : 1;  /* bit[21]   : HW CAT pattern toggling.
                                                             1: enable (default)
                                                             0: disable
                                                             Note:
                                                             This field should be set as 0x1 in LPDDR4. */
        unsigned int  rpt_mode_en       : 1;  /* bit[22]   : Enable Gate Training to use "Read Preamble Train mode" (DDR4/LPDDR4 only). When this field is diabled in DDR4, GT will use legacy mode (issuing normal read commands).
                                                             1: enable (default) - recommended
                                                             0: disable
                                                             
                                                             Note: when this field is disabled in DDR4, the IOCTL3.dxctl_ioctl_pupdmode should be set as 0x1 to pullup the RDQS during GT.
                                                             -------------------LPDDR4---------------------
                                                             1: Entering Read Preamble Training Mode (RPT) and Using MPC RD DQ Calibration for GT/GDS Training and Re-Training (should be set 0x1 in LPDDR4) */
        unsigned int  wdet_method_sel   : 1;  /* bit[23]   : WDET Method Selection
                                                             -------------------LPDDR4---------------------
                                                             1: WDET by MPC RD/WR FIFO Commands */
        unsigned int  fast_gt_cnt       : 5;  /* bit[24-28]: The number of read command be issured during fast gate training  */
        unsigned int  phaseradix3en     : 1;  /* bit[29]   : Phase Radix 3 Calculation Enable.
                                                             1: (default) Enable Phase Radix 3 Calculation
                                                             0: Using Radix 2 Calculation for Phase
                                                             Note: 
                                                             In mission mode, phaseradix3en should be set as 0x1.
                                                             In bypass mode, phaseradix3en should be set as 0x0. */
        unsigned int  rdet_fcomp_en     : 1;  /* bit[30]   : RDET rdata full-compare enable.
                                                             1: (default) rdata full-compare (enhance the rdata error-detection ability) - recommended
                                                             0: rdata partial-compare (enhace the pre-write error tolerance)
                                                             Note: Not support rdet_fcomp_en=0x0 in LPDDR4  */
        unsigned int  exd_gtres_en      : 1;  /* bit[31]   : Extended gate result enable. When set as HIGH, the pack will use additional information (EN_DQSx_regread) to help extend the gate result in the "fine tune stage of gate train "and "gate re-train".
                                                             0: disable
                                                             1: enable (default)
                                                             Note:
                                                              This field should be set as 0x0 (disabled) when LP4 RD post-amble = 1.5*tCK, because phy's EN_DQSx_regread can not be used */
    } reg;
} SOC_HIPACKPHY_TRAINCTRL3_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL3_rpat_cnt_num_START       (0)
#define SOC_HIPACKPHY_TRAINCTRL3_rpat_cnt_num_END         (3)
#define SOC_HIPACKPHY_TRAINCTRL3_wpat_cnt_num_START       (4)
#define SOC_HIPACKPHY_TRAINCTRL3_wpat_cnt_num_END         (7)
#define SOC_HIPACKPHY_TRAINCTRL3_rpat_cnt_num_open_START  (8)
#define SOC_HIPACKPHY_TRAINCTRL3_rpat_cnt_num_open_END    (11)
#define SOC_HIPACKPHY_TRAINCTRL3_wderten_START            (12)
#define SOC_HIPACKPHY_TRAINCTRL3_wderten_END              (12)
#define SOC_HIPACKPHY_TRAINCTRL3_wdet_rank_en_START       (13)
#define SOC_HIPACKPHY_TRAINCTRL3_wdet_rank_en_END         (13)
#define SOC_HIPACKPHY_TRAINCTRL3_wrenrkswen_START         (14)
#define SOC_HIPACKPHY_TRAINCTRL3_wrenrkswen_END           (14)
#define SOC_HIPACKPHY_TRAINCTRL3_nopre4wrdet_START        (15)
#define SOC_HIPACKPHY_TRAINCTRL3_nopre4wrdet_END          (15)
#define SOC_HIPACKPHY_TRAINCTRL3_gdsrt_backtap_START      (16)
#define SOC_HIPACKPHY_TRAINCTRL3_gdsrt_backtap_END        (18)
#define SOC_HIPACKPHY_TRAINCTRL3_rdet_rank_en_START       (19)
#define SOC_HIPACKPHY_TRAINCTRL3_rdet_rank_en_END         (19)
#define SOC_HIPACKPHY_TRAINCTRL3_rdet_dbi_en_START        (20)
#define SOC_HIPACKPHY_TRAINCTRL3_rdet_dbi_en_END          (20)
#define SOC_HIPACKPHY_TRAINCTRL3_cat_pat_toggle_en_START  (21)
#define SOC_HIPACKPHY_TRAINCTRL3_cat_pat_toggle_en_END    (21)
#define SOC_HIPACKPHY_TRAINCTRL3_rpt_mode_en_START        (22)
#define SOC_HIPACKPHY_TRAINCTRL3_rpt_mode_en_END          (22)
#define SOC_HIPACKPHY_TRAINCTRL3_wdet_method_sel_START    (23)
#define SOC_HIPACKPHY_TRAINCTRL3_wdet_method_sel_END      (23)
#define SOC_HIPACKPHY_TRAINCTRL3_fast_gt_cnt_START        (24)
#define SOC_HIPACKPHY_TRAINCTRL3_fast_gt_cnt_END          (28)
#define SOC_HIPACKPHY_TRAINCTRL3_phaseradix3en_START      (29)
#define SOC_HIPACKPHY_TRAINCTRL3_phaseradix3en_END        (29)
#define SOC_HIPACKPHY_TRAINCTRL3_rdet_fcomp_en_START      (30)
#define SOC_HIPACKPHY_TRAINCTRL3_rdet_fcomp_en_END        (30)
#define SOC_HIPACKPHY_TRAINCTRL3_exd_gtres_en_START       (31)
#define SOC_HIPACKPHY_TRAINCTRL3_exd_gtres_en_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_MODEREG45_UNION
 �ṹ˵��  : MODEREG45 �Ĵ����ṹ���塣��ַƫ����:0x00E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines the contents of the Mode Register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mr4 : 16; /* bit[0-15] : Mode Register 4.
                                               For DDR4, this register is used to specify the Extend Mode Register 4.
                                               -------------------LPDDR4---------------------
                                               {MR20,MR15} 
                                               MR15 - Lower-Byte Invert Register for DQ Calibration (default = 55H)
                                               MR20 - Upper-Byte Invert Register for DQ Calibration (default = 55H) */
        unsigned int  mr5 : 16; /* bit[16-31]: Mode Register 5.
                                               For DDR4, this register is used to specify the Extend Mode Register 5.
                                               -------------------LPDDR4---------------------
                                               {MR40, MR32} 
                                               MR32 - DQ Calibration Pattern ��A�� (default = 5AH)
                                               MR40 - DQ Calibration Pattern ��B�� (default = 3CH) */
    } reg;
} SOC_HIPACKPHY_MODEREG45_UNION;
#endif
#define SOC_HIPACKPHY_MODEREG45_mr4_START  (0)
#define SOC_HIPACKPHY_MODEREG45_mr4_END    (15)
#define SOC_HIPACKPHY_MODEREG45_mr5_START  (16)
#define SOC_HIPACKPHY_MODEREG45_mr5_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_MODEREG67_UNION
 �ṹ˵��  : MODEREG67 �Ĵ����ṹ���塣��ַƫ����:0x00E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register defines the contents of the Mode Register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mr6 : 16; /* bit[0-15] : Mode Register 6.
                                               For DDR4, this register is used to specify the Extend Mode Register 6. 
                                               -------------------LPDDR4---------------------
                                               {MR14, MR13}
                                               MR13 - FSP-OP FSP-WR DMD RRO VRCG VRO RPT CBT
                                               MR14 - VR(dq) VREF(dq)
                                               Note that only the VR(dq) of MR14 will be used while executing DRAM VREF(DQ) training. */
        unsigned int  mr7 : 16; /* bit[16-31]: Mode Register 7.
                                               RFU. 
                                               -------------------LPDDR4---------------------
                                               MR12 - VR(ac) VREF(ac)
                                               Note that only the VR(ac) of MR12 will be used while executing DRAM VREF(AC) training. */
    } reg;
} SOC_HIPACKPHY_MODEREG67_UNION;
#endif
#define SOC_HIPACKPHY_MODEREG67_mr6_START  (0)
#define SOC_HIPACKPHY_MODEREG67_mr6_END    (15)
#define SOC_HIPACKPHY_MODEREG67_mr7_START  (16)
#define SOC_HIPACKPHY_MODEREG67_mr7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_TRAINCTRL6_UNION
 �ṹ˵��  : TRAINCTRL6 �Ĵ����ṹ���塣��ַƫ����:0x0E8����ֵ:0x40730000�����:32
 �Ĵ���˵��: This register control the data training.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phyupdtimer      : 16; /* bit[0-15] : Timer to Trigger PHY Update (Unit: 16 pclk)
                                                            0: Disable
                                                            Others: n*16 pclk */
        unsigned int  cfg_reg_sync_cnt : 4;  /* bit[16-19]: config the delay of phyconnt reset when delay line update */
        unsigned int  cat_re_deskew_en : 1;  /* bit[20]   : CAT re-deskew eanble when addrnbdl underflow during deskew fine-tune stage.
                                                            0: disable
                                                            1: enable (default) - recommended */
        unsigned int  det_re_deskew_en : 1;  /* bit[21]   : DET re-deskew eanble when dqnbdl underflow during deskew fine-tune stage.
                                                            0: disable
                                                            1: enable (default) - recommended */
        unsigned int  half_ph_bdl_en   : 1;  /* bit[22]   : 1: Use rdqsbdl30/2 to emulate 15 degree phase (a half phase) for WDET
                                                            0: disable
                                                            Note:
                                                            Because the half_ph_bdl_en adopts wdqnbdl/wdmbdl to emulate one-half phase (15 degree), there are some limitations for it (to prevent overflow conditions):
                                                             (1) used only in 2133 Mbps (& above) & mission mode
                                                             (2) used only in bypass mode or 2-phase mode with
                                                             wdet_byp_mode=0x1
                                                             wet_ph_step=0x3
                                                             wdet_ds_en=0x0
                                                             wdet_rb2nd_fine_en=0x0
                                                             phaseradix3en=0x0
                                                             wdet_lb_backtap=0x0
                                                             wdet_rb_backtap=0x0 */
        unsigned int  bdlcarry_done    : 1;  /* bit[23]   : 1: If BDL is carry out during some train states (WL/GT), treats it as boundary instead as an error.
                                                            0: disable
                                                            Note:
                                                            Set 0x1 in byp_mode/2phase mode */
        unsigned int  row_react_period : 8;  /* bit[24-31]: Row Re-Active period. This field is used as the period to re-issue PRE-ACT commands to met max. tRAS requirement during DET training. The unit is 4 READ/WRITE commands.
                                                            0: ��, means do not re-issue PRE-ACT command pair.
                                                            N: means every N*4 READ/WRITE commands, re-issue PRE-ACT command pair. */
    } reg;
} SOC_HIPACKPHY_TRAINCTRL6_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL6_phyupdtimer_START       (0)
#define SOC_HIPACKPHY_TRAINCTRL6_phyupdtimer_END         (15)
#define SOC_HIPACKPHY_TRAINCTRL6_cfg_reg_sync_cnt_START  (16)
#define SOC_HIPACKPHY_TRAINCTRL6_cfg_reg_sync_cnt_END    (19)
#define SOC_HIPACKPHY_TRAINCTRL6_cat_re_deskew_en_START  (20)
#define SOC_HIPACKPHY_TRAINCTRL6_cat_re_deskew_en_END    (20)
#define SOC_HIPACKPHY_TRAINCTRL6_det_re_deskew_en_START  (21)
#define SOC_HIPACKPHY_TRAINCTRL6_det_re_deskew_en_END    (21)
#define SOC_HIPACKPHY_TRAINCTRL6_half_ph_bdl_en_START    (22)
#define SOC_HIPACKPHY_TRAINCTRL6_half_ph_bdl_en_END      (22)
#define SOC_HIPACKPHY_TRAINCTRL6_bdlcarry_done_START     (23)
#define SOC_HIPACKPHY_TRAINCTRL6_bdlcarry_done_END       (23)
#define SOC_HIPACKPHY_TRAINCTRL6_row_react_period_START  (24)
#define SOC_HIPACKPHY_TRAINCTRL6_row_react_period_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DETPATINDEX_UNION
 �ṹ˵��  : DETPATINDEX �Ĵ����ṹ���塣��ַƫ����:0x00EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Write/Read DET Pattern INDEX Register.
            These fields are used to select the related DETPATTERN. Users are not recommend to modify them.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  det_pat_index : 4;  /* bit[0-3]  : DET pattern index
                                                         The valid value for RDET pattern is 0x0~0xB.
                                                         The valid value for WDET WDQ pattern is 0x0~0xB.
                                                         The valid value for WDET WDM pattern is 0x0.
                                                         Note: when select the non-defined index, the write will not take effect and the read will return the RDET index 0 data. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  :  */
        unsigned int  det_pat_dir   : 2;  /* bit[8-9]  : DET pattern direction index
                                                         3'd0: RDET pattern
                                                         3'd1: RDET RDM Pattern
                                                         3'd2: WDET WDQ pattern
                                                         3'd3: WDET WDM pattern */
        unsigned int  reserved_1    : 22; /* bit[10-31]:  */
    } reg;
} SOC_HIPACKPHY_DETPATINDEX_UNION;
#endif
#define SOC_HIPACKPHY_DETPATINDEX_det_pat_index_START  (0)
#define SOC_HIPACKPHY_DETPATINDEX_det_pat_index_END    (3)
#define SOC_HIPACKPHY_DETPATINDEX_det_pat_dir_START    (8)
#define SOC_HIPACKPHY_DETPATINDEX_det_pat_dir_END      (9)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYPLLCTRL_DX2_UNION
 �ṹ˵��  : PHYPLLCTRL_DX2 �Ĵ����ṹ���塣��ַƫ����:0x00F0����ֵ:0x000000F0�����:32
 �Ĵ���˵��: PHY PLL control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dx_pll_bp_refpfd   : 2;  /* bit[0-1]  : Move to DX_Static_Reg */
        unsigned int  dx_pll_bp_refvco   : 2;  /* bit[2-3]  : Move to DX_Static_Reg */
        unsigned int  dx_pll_enphsel     : 2;  /* bit[4-5]  : Move to DX_Static_Reg */
        unsigned int  dx_pll_en_cal      : 2;  /* bit[6-7]  : Move to DX_Static_Reg */
        unsigned int  dx_pll_initsel     : 2;  /* bit[8-9]  : Move to DX_Static_Reg */
        unsigned int  dx_pll_lockt_sel   : 2;  /* bit[10-11]: Move to DX_Static_Reg */
        unsigned int  dx_pll_fopetestfb  : 2;  /* bit[12-13]: Move to DX_Static_Reg */
        unsigned int  dx_pll_fopetestref : 2;  /* bit[14-15]: Move to DX_Static_Reg */
        unsigned int  dx_pll_lockin      : 2;  /* bit[16-17]: Move to DX_Static_Reg */
        unsigned int  dx_pll_outn        : 2;  /* bit[18-19]: Dummy Reg - Not Used */
        unsigned int  dx_pll_outp        : 2;  /* bit[20-21]: Dummy Reg - Not Used */
        unsigned int  reserved           : 10; /* bit[22-31]:  */
    } reg;
} SOC_HIPACKPHY_PHYPLLCTRL_DX2_UNION;
#endif
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_bp_refpfd_START    (0)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_bp_refpfd_END      (1)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_bp_refvco_START    (2)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_bp_refvco_END      (3)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_enphsel_START      (4)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_enphsel_END        (5)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_en_cal_START       (6)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_en_cal_END         (7)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_initsel_START      (8)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_initsel_END        (9)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_lockt_sel_START    (10)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_lockt_sel_END      (11)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_fopetestfb_START   (12)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_fopetestfb_END     (13)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_fopetestref_START  (14)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_fopetestref_END    (15)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_lockin_START       (16)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_lockin_END         (17)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_outn_START         (18)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_outn_END           (19)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_outp_START         (20)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX2_dx_pll_outp_END           (21)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYPLLCTRL_DX3_UNION
 �ṹ˵��  : PHYPLLCTRL_DX3 �Ĵ����ṹ���塣��ַƫ����:0x00F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: PHY PLL control register 3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phazmeter_1    : 16; /* bit[0-15] : Move to AC/DX_Static_Reg */
        unsigned int  phazmeter_st_1 : 16; /* bit[16-31]: Move to AC/DX_Static_Reg */
    } reg;
} SOC_HIPACKPHY_PHYPLLCTRL_DX3_UNION;
#endif
#define SOC_HIPACKPHY_PHYPLLCTRL_DX3_phazmeter_1_START     (0)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX3_phazmeter_1_END       (15)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX3_phazmeter_st_1_START  (16)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX3_phazmeter_st_1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYPLLCTRL_DX4_UNION
 �ṹ˵��  : PHYPLLCTRL_DX4 �Ĵ����ṹ���塣��ַƫ����:0x00F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: PHY PLL control register 4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phazmeter_2    : 16; /* bit[0-15] : Move to AC/DX_Static_Reg */
        unsigned int  phazmeter_st_2 : 16; /* bit[16-31]: Move to AC/DX_Static_Reg */
    } reg;
} SOC_HIPACKPHY_PHYPLLCTRL_DX4_UNION;
#endif
#define SOC_HIPACKPHY_PHYPLLCTRL_DX4_phazmeter_2_START     (0)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX4_phazmeter_2_END       (15)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX4_phazmeter_st_2_START  (16)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX4_phazmeter_st_2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYPLLCTRL_DX5_UNION
 �ṹ˵��  : PHYPLLCTRL_DX5 �Ĵ����ṹ���塣��ַƫ����:0x00FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: PHY PLL control register 5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phazmeter_3    : 16; /* bit[0-15] : Move to AC/DX_Static_Reg */
        unsigned int  phazmeter_st_3 : 16; /* bit[16-31]: Move to AC/DX_Static_Reg */
    } reg;
} SOC_HIPACKPHY_PHYPLLCTRL_DX5_UNION;
#endif
#define SOC_HIPACKPHY_PHYPLLCTRL_DX5_phazmeter_3_START     (0)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX5_phazmeter_3_END       (15)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX5_phazmeter_st_3_START  (16)
#define SOC_HIPACKPHY_PHYPLLCTRL_DX5_phazmeter_st_3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACBISTCTRL0_UNION
 �ṹ˵��  : ACBISTCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x40000000�����:32
 �Ĵ���˵��: This register control the comparison while BIST activated.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_cmp_mask : 16; /* bit[0-15] : Memory Address Loopback Compare Mask.
                                                         This field is used to control if the comparison of the loopback data on address bits are disabled. 
                                                         0: Not compare 
                                                         1: Compare */
        unsigned int  ba_cmp_mask   : 3;  /* bit[16-18]: Bank Address Loopback Compare Mask.
                                                         This field is used to control if the comparison of the loopback data on bank address bits are disabled.
                                                         0: Not compare 
                                                         1: Compare */
        unsigned int  we_cmp_mask   : 1;  /* bit[19]   : Write Enable Loopback Compare Mask.
                                                         This field is used to control if the comparison of the loopback data on WE are disabled.
                                                         0: Not compare 
                                                         1: Compare */
        unsigned int  cas_cmp_mask  : 1;  /* bit[20]   : CAS Loopback Compare Mask.
                                                         This field is used to control if the comparison of the loopback data on CAS are disabled.
                                                         0: Not compare 
                                                         1: Compare */
        unsigned int  ras_cmp_mask  : 1;  /* bit[21]   : RAS Loopback Compare Mask.
                                                         This field is used to control if the comparison of the loopback data on RAS are disabled.
                                                         0: Not compare 
                                                         1: Compare */
        unsigned int  cs_cmp_mask   : 4;  /* bit[22-25]: CS Loopback Compare Mask.
                                                         This field is used to control if the comparison of the loopback data on CS bits are disabled. 
                                                         0: Not compare 
                                                         1: Compare */
        unsigned int  rst_cmp_mask  : 1;  /* bit[26]   : RST Loopback Compare Mask
                                                         This field is used to control if the comparison of the loopback data on RST bit are disabled. 
                                                         0: Not compare 
                                                         1: Compare */
        unsigned int  acbist_en     : 1;  /* bit[27]   : Bist Enable.
                                                         This signal specify if the AC block is included for loopback test while bist_op is set to BIST Enable. */
        unsigned int  aclpbk_tg     : 1;  /* bit[28]   : AC Loopback toggle control. The user shold not modify this bit. It is related to the Analog PHY design.
                                                         1:40PHY
                                                         0:28LPP PHY (default) */
        unsigned int  ac_rdffsel    : 3;  /* bit[29-31]: AC Loopback Read Latch Select */
    } reg;
} SOC_HIPACKPHY_ACBISTCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_ACBISTCTRL0_addr_cmp_mask_START  (0)
#define SOC_HIPACKPHY_ACBISTCTRL0_addr_cmp_mask_END    (15)
#define SOC_HIPACKPHY_ACBISTCTRL0_ba_cmp_mask_START    (16)
#define SOC_HIPACKPHY_ACBISTCTRL0_ba_cmp_mask_END      (18)
#define SOC_HIPACKPHY_ACBISTCTRL0_we_cmp_mask_START    (19)
#define SOC_HIPACKPHY_ACBISTCTRL0_we_cmp_mask_END      (19)
#define SOC_HIPACKPHY_ACBISTCTRL0_cas_cmp_mask_START   (20)
#define SOC_HIPACKPHY_ACBISTCTRL0_cas_cmp_mask_END     (20)
#define SOC_HIPACKPHY_ACBISTCTRL0_ras_cmp_mask_START   (21)
#define SOC_HIPACKPHY_ACBISTCTRL0_ras_cmp_mask_END     (21)
#define SOC_HIPACKPHY_ACBISTCTRL0_cs_cmp_mask_START    (22)
#define SOC_HIPACKPHY_ACBISTCTRL0_cs_cmp_mask_END      (25)
#define SOC_HIPACKPHY_ACBISTCTRL0_rst_cmp_mask_START   (26)
#define SOC_HIPACKPHY_ACBISTCTRL0_rst_cmp_mask_END     (26)
#define SOC_HIPACKPHY_ACBISTCTRL0_acbist_en_START      (27)
#define SOC_HIPACKPHY_ACBISTCTRL0_acbist_en_END        (27)
#define SOC_HIPACKPHY_ACBISTCTRL0_aclpbk_tg_START      (28)
#define SOC_HIPACKPHY_ACBISTCTRL0_aclpbk_tg_END        (28)
#define SOC_HIPACKPHY_ACBISTCTRL0_ac_rdffsel_START     (29)
#define SOC_HIPACKPHY_ACBISTCTRL0_ac_rdffsel_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACBISTCTRL1_UNION
 �ṹ˵��  : ACBISTCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register control the comparison while BIST activated.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  odt_cmp_mask : 4;  /* bit[0-3]  : ODT Loopback Compare Mask.
                                                        This field is used to control if the comparison of the loopback data on ODT bits are disabled. 
                                                        0: Not compare 
                                                        1: Compare */
        unsigned int  cke_cmp_mask : 4;  /* bit[4-7]  : CKE Loopback Compare Mask.
                                                        This field is used to control if the comparison of the loopback data on CKE bits are disabled. 
                                                        0: Not compare 
                                                        1: Compare */
        unsigned int  ac_lfsr_seed : 8;  /* bit[8-15] : LFSR Seed Value.
                                                        This field is uesed to specify the initial seed value of the LFSR generator to this byte lane. */
        unsigned int  par_cmp_mask : 1;  /* bit[16]   : PAR Loopback Compare Mask.
                                                        This field is used to control if the comparison of the loopback data on PAR bits are disabled.Only valid in DDR4 MODE 
                                                        0: Not compare 
                                                        1: Compare */
        unsigned int  bg1_cmp_mask : 1;  /* bit[17]   : BG1 Loopback Compare Mask.
                                                        This field is used to control if the comparison of the loopback data on BG1 bits are disabled.Only valid in DDR4 MODE.In DDR4 MODE,the port BA2 is execute as BG0.
                                                        0: Not compare 
                                                        1: Compare */
        unsigned int  act_cmp_mask : 1;  /* bit[18]   : ACT Loopback Compare Mask.
                                                        This field is used to control if the comparison of the loopback data on ACT bits are disabled.Only valid in DDR4 MODE 
                                                        0: Not compare 
                                                        1: Compare */
        unsigned int  prbs_mode    : 1;  /* bit[19]   : PRBS mode select.
                                                        0:PRBS16
                                                        1:PRBS11 */
        unsigned int  addro_fp     : 1;  /* bit[20]   : Flip addro loopback data enable
                                                        0: Not inverted
                                                        1: Make addro's loopback data inverted to addr's */
        unsigned int  reserved     : 11; /* bit[21-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACBISTCTRL1_UNION;
#endif
#define SOC_HIPACKPHY_ACBISTCTRL1_odt_cmp_mask_START  (0)
#define SOC_HIPACKPHY_ACBISTCTRL1_odt_cmp_mask_END    (3)
#define SOC_HIPACKPHY_ACBISTCTRL1_cke_cmp_mask_START  (4)
#define SOC_HIPACKPHY_ACBISTCTRL1_cke_cmp_mask_END    (7)
#define SOC_HIPACKPHY_ACBISTCTRL1_ac_lfsr_seed_START  (8)
#define SOC_HIPACKPHY_ACBISTCTRL1_ac_lfsr_seed_END    (15)
#define SOC_HIPACKPHY_ACBISTCTRL1_par_cmp_mask_START  (16)
#define SOC_HIPACKPHY_ACBISTCTRL1_par_cmp_mask_END    (16)
#define SOC_HIPACKPHY_ACBISTCTRL1_bg1_cmp_mask_START  (17)
#define SOC_HIPACKPHY_ACBISTCTRL1_bg1_cmp_mask_END    (17)
#define SOC_HIPACKPHY_ACBISTCTRL1_act_cmp_mask_START  (18)
#define SOC_HIPACKPHY_ACBISTCTRL1_act_cmp_mask_END    (18)
#define SOC_HIPACKPHY_ACBISTCTRL1_prbs_mode_START     (19)
#define SOC_HIPACKPHY_ACBISTCTRL1_prbs_mode_END       (19)
#define SOC_HIPACKPHY_ACBISTCTRL1_addro_fp_START      (20)
#define SOC_HIPACKPHY_ACBISTCTRL1_addro_fp_END        (20)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACBISTSTS0_UNION
 �ṹ˵��  : ACBISTSTS0 �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register shows the results and status of the BIST test. Please note that this register is read-only, and can only be reset by bist_op setting to BIST Reset.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_bist_err : 16; /* bit[0-15] : BIST Error on Address Bus. */
        unsigned int  ba_bist_err   : 3;  /* bit[16-18]: BIST Error on Bank Address. */
        unsigned int  we_bist_err   : 1;  /* bit[19]   : BIST Error on Write Enable. */
        unsigned int  cas_bist_err  : 1;  /* bit[20]   : BIST Error on CAS. */
        unsigned int  ras_bist_err  : 1;  /* bit[21]   : BIST Error on RAS. */
        unsigned int  cs_bist_err   : 4;  /* bit[22-25]: BIST Error on CS. */
        unsigned int  rst_bist_err  : 1;  /* bit[26]   : BIST Error on RST. */
        unsigned int  par_bist_err  : 1;  /* bit[27]   : BIST Error on PAR */
        unsigned int  bg1_bist_err  : 1;  /* bit[28]   : BIST Error on BG1 */
        unsigned int  act_bist_err  : 1;  /* bit[29]   : BIST Error on ACT */
        unsigned int  reserved      : 2;  /* bit[30-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACBISTSTS0_UNION;
#endif
#define SOC_HIPACKPHY_ACBISTSTS0_addr_bist_err_START  (0)
#define SOC_HIPACKPHY_ACBISTSTS0_addr_bist_err_END    (15)
#define SOC_HIPACKPHY_ACBISTSTS0_ba_bist_err_START    (16)
#define SOC_HIPACKPHY_ACBISTSTS0_ba_bist_err_END      (18)
#define SOC_HIPACKPHY_ACBISTSTS0_we_bist_err_START    (19)
#define SOC_HIPACKPHY_ACBISTSTS0_we_bist_err_END      (19)
#define SOC_HIPACKPHY_ACBISTSTS0_cas_bist_err_START   (20)
#define SOC_HIPACKPHY_ACBISTSTS0_cas_bist_err_END     (20)
#define SOC_HIPACKPHY_ACBISTSTS0_ras_bist_err_START   (21)
#define SOC_HIPACKPHY_ACBISTSTS0_ras_bist_err_END     (21)
#define SOC_HIPACKPHY_ACBISTSTS0_cs_bist_err_START    (22)
#define SOC_HIPACKPHY_ACBISTSTS0_cs_bist_err_END      (25)
#define SOC_HIPACKPHY_ACBISTSTS0_rst_bist_err_START   (26)
#define SOC_HIPACKPHY_ACBISTSTS0_rst_bist_err_END     (26)
#define SOC_HIPACKPHY_ACBISTSTS0_par_bist_err_START   (27)
#define SOC_HIPACKPHY_ACBISTSTS0_par_bist_err_END     (27)
#define SOC_HIPACKPHY_ACBISTSTS0_bg1_bist_err_START   (28)
#define SOC_HIPACKPHY_ACBISTSTS0_bg1_bist_err_END     (28)
#define SOC_HIPACKPHY_ACBISTSTS0_act_bist_err_START   (29)
#define SOC_HIPACKPHY_ACBISTSTS0_act_bist_err_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACBISTSTS1_UNION
 �ṹ˵��  : ACBISTSTS1 �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register shows the results and status of the BIST test. Please note that this register is read-only, and can only be reset by bist_op setting to BIST Reset.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  odt_bist_err : 4;  /* bit[0-3] : BIST Error on ODT.  */
        unsigned int  cke_bist_err : 4;  /* bit[4-7] : BIST Error on CKE. */
        unsigned int  reserved     : 24; /* bit[8-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACBISTSTS1_UNION;
#endif
#define SOC_HIPACKPHY_ACBISTSTS1_odt_bist_err_START  (0)
#define SOC_HIPACKPHY_ACBISTSTS1_odt_bist_err_END    (3)
#define SOC_HIPACKPHY_ACBISTSTS1_cke_bist_err_START  (4)
#define SOC_HIPACKPHY_ACBISTSTS1_cke_bist_err_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_WDXBOUND_DFS_UNION
 �ṹ˵��  : WDXBOUND_DFS �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register indicate the wdet lb roundary.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdqphase_left_bytelane0 : 6;  /* bit[0-5]  : bytelane0 wdqphase_left (current rank). */
        unsigned int  reserved_0              : 2;  /* bit[6-7]  :  */
        unsigned int  wdqphase_left_bytelane1 : 6;  /* bit[8-13] : bytelane1 wdqphase_left (current rank). */
        unsigned int  reserved_1              : 2;  /* bit[14-15]:  */
        unsigned int  wdq0bdl_left_bytelane0  : 7;  /* bit[16-22]: bytelane0 DQ0 wdqnbdl_left (current rank) */
        unsigned int  wdet_err                : 1;  /* bit[23]   : WDET error flag. Read only. */
        unsigned int  wdq0bdl_left_bytelane1  : 7;  /* bit[24-30]: bytelane1 DQ0 wdqnbdl_left (current rank) */
        unsigned int  init_en                 : 1;  /* bit[31]   : PHY Iinitialization enable. Read only.
                                                                   1: busy
                                                                   0: idle */
    } reg;
} SOC_HIPACKPHY_WDXBOUND_DFS_UNION;
#endif
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdqphase_left_bytelane0_START  (0)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdqphase_left_bytelane0_END    (5)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdqphase_left_bytelane1_START  (8)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdqphase_left_bytelane1_END    (13)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdq0bdl_left_bytelane0_START   (16)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdq0bdl_left_bytelane0_END     (22)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdet_err_START                 (23)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdet_err_END                   (23)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdq0bdl_left_bytelane1_START   (24)
#define SOC_HIPACKPHY_WDXBOUND_DFS_wdq0bdl_left_bytelane1_END     (30)
#define SOC_HIPACKPHY_WDXBOUND_DFS_init_en_START                  (31)
#define SOC_HIPACKPHY_WDXBOUND_DFS_init_en_END                    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_TRAINCTRL4_UNION
 �ṹ˵��  : TRAINCTRL4 �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x2A032121�����:32
 �Ĵ���˵��: This register control the data training.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdet_lb_backtap  : 4;  /* bit[0-3]  : Write DET Left Boundary backtap.
                                                            This field is used to offset (-) the wdqphase before do the Left Boundary fine-tune Search to overcome meta-stable zone. */
        unsigned int  wdet_rb_backtap  : 4;  /* bit[4-7]  : Write DET Right Boundary backtap.
                                                            This field is used to offset (-) the wdqphase before do the Right Boundary Search to overcome meta-stable zone. */
        unsigned int  wdert_shift_step : 3;  /* bit[8-10] : Write data eye retrain shift step (Unit PLL Phase)
                                                            Note: The mapping from register value to delay degree, please reference to sheet "Phase8_6_2 Mapping" when phaseradix3en enabled
                                                            If wdert_bdl_mode==1
                                                            0: 1/64 T
                                                            1: 1/32 T
                                                            2: 1/16 T
                                                            3: 1/8 T
                                                            4: 1/4 T */
        unsigned int  rdert_bdl_mode   : 1;  /* bit[11]   : Using rdqnbdl/rdmbdl instead of rdqsbdl during RDERT.
                                                            It only workable when there are enough margin for decreasing/increasing bdl step to avoid underflow/overflow therefore user have to guarantee margin by software method. */
        unsigned int  rdet_lb_backtap  : 4;  /* bit[12-15]: Read DET Left Boundary backtap.
                                                            This field is used to offset (+) the rdqsbdl before do the Left Boundary fine-tune Search to overcome meta-stable zone. */
        unsigned int  rdet_rb_backtap  : 9;  /* bit[16-24]: Read DET Right Boundary backtap.
                                                            This field is used to offset (+) the rdqsbdl before do the Right Boundary Search to overcome meta-stable zone. */
        unsigned int  fast_comp_step   : 2;  /* bit[25-26]: fast read data eye training compensation step
                                                            0: 1/4T
                                                            1: 1/8T
                                                            2: 1/16T
                                                            3: 1/32T
                                                            , cannot use */
        unsigned int  fast_shift_step  : 2;  /* bit[27-28]: fast read data eye training shift step 
                                                            0: 1/8T
                                                            1: 1/16T
                                                            2: 1/32T
                                                            3: 1/64T
                                                            , cannot use */
        unsigned int  fast_check_step  : 2;  /* bit[29-30]: fast read data eye training check step 
                                                            0: 1/4T
                                                            1: 1/8T
                                                            2: 1/16T
                                                            3: 1/32T */
        unsigned int  rdet_dq_rank_en  : 1;  /* bit[31]   : DQ Rank Training Separation Enable
                                                            0: All rank share rank0 rdqnbdl (default)
                                                            1: Each rank owns its 
                                                             -> (RDET) rdqnbdl , rdmbdl
                                                             -> (WDET) wdqphase, wdqnbdl, wdmbdl */
    } reg;
} SOC_HIPACKPHY_TRAINCTRL4_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL4_wdet_lb_backtap_START   (0)
#define SOC_HIPACKPHY_TRAINCTRL4_wdet_lb_backtap_END     (3)
#define SOC_HIPACKPHY_TRAINCTRL4_wdet_rb_backtap_START   (4)
#define SOC_HIPACKPHY_TRAINCTRL4_wdet_rb_backtap_END     (7)
#define SOC_HIPACKPHY_TRAINCTRL4_wdert_shift_step_START  (8)
#define SOC_HIPACKPHY_TRAINCTRL4_wdert_shift_step_END    (10)
#define SOC_HIPACKPHY_TRAINCTRL4_rdert_bdl_mode_START    (11)
#define SOC_HIPACKPHY_TRAINCTRL4_rdert_bdl_mode_END      (11)
#define SOC_HIPACKPHY_TRAINCTRL4_rdet_lb_backtap_START   (12)
#define SOC_HIPACKPHY_TRAINCTRL4_rdet_lb_backtap_END     (15)
#define SOC_HIPACKPHY_TRAINCTRL4_rdet_rb_backtap_START   (16)
#define SOC_HIPACKPHY_TRAINCTRL4_rdet_rb_backtap_END     (24)
#define SOC_HIPACKPHY_TRAINCTRL4_fast_comp_step_START    (25)
#define SOC_HIPACKPHY_TRAINCTRL4_fast_comp_step_END      (26)
#define SOC_HIPACKPHY_TRAINCTRL4_fast_shift_step_START   (27)
#define SOC_HIPACKPHY_TRAINCTRL4_fast_shift_step_END     (28)
#define SOC_HIPACKPHY_TRAINCTRL4_fast_check_step_START   (29)
#define SOC_HIPACKPHY_TRAINCTRL4_fast_check_step_END     (30)
#define SOC_HIPACKPHY_TRAINCTRL4_rdet_dq_rank_en_START   (31)
#define SOC_HIPACKPHY_TRAINCTRL4_rdet_dq_rank_en_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_TRAINCTRL5_UNION
 �ṹ˵��  : TRAINCTRL5 �Ĵ����ṹ���塣��ַƫ����:0x118����ֵ:0x10010100�����:32
 �Ĵ���˵��: This register control the data training.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdet_bdl_step      : 2;  /* bit[0-1]  : WDET BDL step.
                                                              0: 1 (default)
                                                              1: 2
                                                              2: 3
                                                              3: 4 */
        unsigned int  wdet_ph_step       : 2;  /* bit[2-3]  : WDET Phase step.
                                                              0: 1 (default)
                                                              1: 2
                                                              2: 3 (Not Used when PLL Phase is 30 Degree Base)
                                                              3: 4 (90 degree)
                                                              Only can be 0 during write data eye retrain (wdert) active
                                                              Note: The mapping from register value to delay degree, please reference to sheet "Phase8_6_2 Mapping" when phaseradix3en enabled */
        unsigned int  rdet_bdl_step      : 2;  /* bit[4-5]  : RDET dq BDL step.
                                                              0: 1 (default)
                                                              1: 2
                                                              2: 3
                                                              3: 4 */
        unsigned int  rdet_ph_step       : 2;  /* bit[6-7]  : RDET rdqs BDL step.
                                                              0: 1 (default)
                                                              1: 2
                                                              2: 3
                                                              3: 4 */
        unsigned int  rdet_open_jstep    : 4;  /* bit[8-11] : RDET EYE OPEN final jump step.
                                                              0: No jump
                                                              1~15: means 1~15 (default:1) */
        unsigned int  gt_bdl_step        : 4;  /* bit[12-15]: Gate Train BDL step.
                                                              0: 1 (default)
                                                              1~15: means 2~16 */
        unsigned int  gt_ph_step         : 2;  /* bit[16-17]: Gate Train Phase step.
                                                              0: 1
                                                              1: 2 (default)
                                                              2: 3
                                                              3: 4 (90 degree)
                                                              Note: The mapping from register value to delay degree, please reference to sheet "Phase8_6_2 Mapping" when phaseradix3en enabled */
        unsigned int  wldqsen            : 1;  /* bit[18]   : control dqs during the period of t_wlmrd be undriven or not, the option only be considered with DDR3 */
        unsigned int  trainctl_nopostpre : 1;  /* bit[19]   : Not Send PRE-ALL when Exit Train Control
                                                              1'b1: Send NOP instead of PRE-ALL when Exit Train Control */
        unsigned int  wl_bdl_step        : 2;  /* bit[20-21]: WL BDL step.
                                                              0: 1 (default)
                                                              1: 2
                                                              2: 3
                                                              3: 4 */
        unsigned int  wl_ph_step         : 2;  /* bit[22-23]: WL Phase step.
                                                              0: 1 (default)
                                                              1: 2
                                                              2: 3
                                                              3: 4 (90 degree)
                                                              Note: The mapping from register value to delay degree, please reference to sheet "Phase8_6_2 Mapping" when phaseradix3en enabled */
        unsigned int  cat_bdl_step       : 2;  /* bit[24-25]: CA Train BDL step.
                                                              0: 1 (default)
                                                              1: 2
                                                              2: 3
                                                              3: 4 */
        unsigned int  cat_ph_step        : 2;  /* bit[26-27]: CA Train Phase step.
                                                              0: 1 (default)
                                                              1: 2
                                                              2: 3
                                                              3: 4 (90 degree)
                                                              Note: The mapping from register value to delay degree, please reference to sheet "Phase8_6_2 Mapping" when phaseradix3en enabled */
        unsigned int  wdert_check_step   : 3;  /* bit[28-30]: Write data eye retrain check step (Unit PLL Phase)
                                                              Note: The mapping from register value to delay degree, please reference to sheet "Phase8_6_2 Mapping" when phaseradix3en enabled
                                                              If wdert_bdl_mode==1
                                                              0: 1/64 T
                                                              1: 1/32 T
                                                              2: 1/16 T
                                                              3: 1/8 T
                                                              4: 1/4 T */
        unsigned int  wdert_bdl_mode     : 1;  /* bit[31]   : Using BDL tap(smaller resolution) instead of phase delay for WDERT check/shift step. 
                                                              It only workable when there are enough margin for decreasing/increasing bdl step to avoid underflow/overflow therefore user have to guarantee margin by software method. */
    } reg;
} SOC_HIPACKPHY_TRAINCTRL5_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL5_wdet_bdl_step_START       (0)
#define SOC_HIPACKPHY_TRAINCTRL5_wdet_bdl_step_END         (1)
#define SOC_HIPACKPHY_TRAINCTRL5_wdet_ph_step_START        (2)
#define SOC_HIPACKPHY_TRAINCTRL5_wdet_ph_step_END          (3)
#define SOC_HIPACKPHY_TRAINCTRL5_rdet_bdl_step_START       (4)
#define SOC_HIPACKPHY_TRAINCTRL5_rdet_bdl_step_END         (5)
#define SOC_HIPACKPHY_TRAINCTRL5_rdet_ph_step_START        (6)
#define SOC_HIPACKPHY_TRAINCTRL5_rdet_ph_step_END          (7)
#define SOC_HIPACKPHY_TRAINCTRL5_rdet_open_jstep_START     (8)
#define SOC_HIPACKPHY_TRAINCTRL5_rdet_open_jstep_END       (11)
#define SOC_HIPACKPHY_TRAINCTRL5_gt_bdl_step_START         (12)
#define SOC_HIPACKPHY_TRAINCTRL5_gt_bdl_step_END           (15)
#define SOC_HIPACKPHY_TRAINCTRL5_gt_ph_step_START          (16)
#define SOC_HIPACKPHY_TRAINCTRL5_gt_ph_step_END            (17)
#define SOC_HIPACKPHY_TRAINCTRL5_wldqsen_START             (18)
#define SOC_HIPACKPHY_TRAINCTRL5_wldqsen_END               (18)
#define SOC_HIPACKPHY_TRAINCTRL5_trainctl_nopostpre_START  (19)
#define SOC_HIPACKPHY_TRAINCTRL5_trainctl_nopostpre_END    (19)
#define SOC_HIPACKPHY_TRAINCTRL5_wl_bdl_step_START         (20)
#define SOC_HIPACKPHY_TRAINCTRL5_wl_bdl_step_END           (21)
#define SOC_HIPACKPHY_TRAINCTRL5_wl_ph_step_START          (22)
#define SOC_HIPACKPHY_TRAINCTRL5_wl_ph_step_END            (23)
#define SOC_HIPACKPHY_TRAINCTRL5_cat_bdl_step_START        (24)
#define SOC_HIPACKPHY_TRAINCTRL5_cat_bdl_step_END          (25)
#define SOC_HIPACKPHY_TRAINCTRL5_cat_ph_step_START         (26)
#define SOC_HIPACKPHY_TRAINCTRL5_cat_ph_step_END           (27)
#define SOC_HIPACKPHY_TRAINCTRL5_wdert_check_step_START    (28)
#define SOC_HIPACKPHY_TRAINCTRL5_wdert_check_step_END      (30)
#define SOC_HIPACKPHY_TRAINCTRL5_wdert_bdl_mode_START      (31)
#define SOC_HIPACKPHY_TRAINCTRL5_wdert_bdl_mode_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_TRAINCTRL7_UNION
 �ṹ˵��  : TRAINCTRL7 �Ĵ����ṹ���塣��ַƫ����:0x11C����ֵ:0x01100010�����:32
 �Ĵ���˵��: This register control the data training.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mr0_cl_m2              : 4;  /* bit[0-3]  : DDR4 mr0 CL-2 setting for gt_rdbi_handle_en=0x1.
                                                                  This filed is used when mr0_cl_m2_sel=0x1. Due to some CL settings are still reserved in DDR4 specification, when the CL-2 setting is belong to reserved fileds the user should use the mr0_cl_m2 instead */
        unsigned int  dlymeas_upd_rdqsbdl_en : 1;  /* bit[4]    : If this field set to 1, the rdqsbdl will be updated to T/4 value calculated from rdqscyc when delay measure */
        unsigned int  wlsyncrank_en          : 1;  /* bit[5]    : Write leveling results sync enable
                                                                  1: In two rank environment, the wdqphase of rank0 will copy to rank1 if dtrank set to 0, if dtrank set to 1, copy rank1 to rank0
                                                                  0: disable */
        unsigned int  gt_rdbi_handle_en      : 1;  /* bit[6]    : DDR4 GT RDBI handle enable.
                                                                  1: enable DDR4 GT RDBI handle
                                                                  0: disable (default)
                                                                  When enabled, PACK will turn off RDBI during GT with RTP mode temporarily. */
        unsigned int  gdsrt_mrank_en         : 1;  /* bit[7]    : Multi-rank gds retrain enable.
                                                                  1: enable multi-rank gds retrain 
                                                                  0: disable (default) */
        unsigned int  cfg_rl_rdbi_off        : 4;  /* bit[8-11] : DDR4 cfg_rl offset value when rdbi off.
                                                                  This field is used when gt_rdbi_handle_en=0x1, to make cfg_rl = cfg_rl - cfg_rl_rdbi_off for rdbi off condition during Gate Training with DDR4 RPT mode. */
        unsigned int  fast_dqsgsl_mrgn       : 6;  /* bit[12-17]: Read DQS Gate Margin
                                                                  This field specify the margin to reserve after fast DQS gate training. The number of phyase specify in this field will be decreased to create DQS gating margin. Have set to 0 in DDR4/3. */
        unsigned int  reserved_0             : 2;  /* bit[18-19]:  */
        unsigned int  wdet_open_bdl_jstep    : 4;  /* bit[20-23]: WDET EYE OPEN final bdl jump step.
                                                                  0: No jump
                                                                  1~15: means 1~15 (default:1) */
        unsigned int  wdet_open_ph_jstep     : 4;  /* bit[24-27]: WDET EYE OPEN final phase jump step.
                                                                  0: No jump
                                                                  1~15: means 1~15 (default:1) */
        unsigned int  reserved_1             : 1;  /* bit[28]   :  */
        unsigned int  trainctl_gtrnowait     : 1;  /* bit[29]   : No Wait State before GT-Retrain
                                                                  1: Skip Wait State before GT-Retrain to Save Re-Train Timing */
        unsigned int  rpt_nomrs              : 1;  /* bit[30]   : Not Send MRS to Entering RPT Mode
                                                                  1: Used in LPDDR4, Not Entering RPT Mode and Use MPC Command for GT/GDS Training when rpt_mode_en==1
                                                                  0: Enter RPT Mode when rtp_mode_en==1 */
        unsigned int  info_full_tccd_sel     : 1;  /* bit[31]   : 1: use tccd_l when info fifo full
                                                                  0: use tccd_s when info fifo full (default)
                                                                  (should be set as 0x1 for DDR4 2tCK Read Preamble) */
    } reg;
} SOC_HIPACKPHY_TRAINCTRL7_UNION;
#endif
#define SOC_HIPACKPHY_TRAINCTRL7_mr0_cl_m2_START               (0)
#define SOC_HIPACKPHY_TRAINCTRL7_mr0_cl_m2_END                 (3)
#define SOC_HIPACKPHY_TRAINCTRL7_dlymeas_upd_rdqsbdl_en_START  (4)
#define SOC_HIPACKPHY_TRAINCTRL7_dlymeas_upd_rdqsbdl_en_END    (4)
#define SOC_HIPACKPHY_TRAINCTRL7_wlsyncrank_en_START           (5)
#define SOC_HIPACKPHY_TRAINCTRL7_wlsyncrank_en_END             (5)
#define SOC_HIPACKPHY_TRAINCTRL7_gt_rdbi_handle_en_START       (6)
#define SOC_HIPACKPHY_TRAINCTRL7_gt_rdbi_handle_en_END         (6)
#define SOC_HIPACKPHY_TRAINCTRL7_gdsrt_mrank_en_START          (7)
#define SOC_HIPACKPHY_TRAINCTRL7_gdsrt_mrank_en_END            (7)
#define SOC_HIPACKPHY_TRAINCTRL7_cfg_rl_rdbi_off_START         (8)
#define SOC_HIPACKPHY_TRAINCTRL7_cfg_rl_rdbi_off_END           (11)
#define SOC_HIPACKPHY_TRAINCTRL7_fast_dqsgsl_mrgn_START        (12)
#define SOC_HIPACKPHY_TRAINCTRL7_fast_dqsgsl_mrgn_END          (17)
#define SOC_HIPACKPHY_TRAINCTRL7_wdet_open_bdl_jstep_START     (20)
#define SOC_HIPACKPHY_TRAINCTRL7_wdet_open_bdl_jstep_END       (23)
#define SOC_HIPACKPHY_TRAINCTRL7_wdet_open_ph_jstep_START      (24)
#define SOC_HIPACKPHY_TRAINCTRL7_wdet_open_ph_jstep_END        (27)
#define SOC_HIPACKPHY_TRAINCTRL7_trainctl_gtrnowait_START      (29)
#define SOC_HIPACKPHY_TRAINCTRL7_trainctl_gtrnowait_END        (29)
#define SOC_HIPACKPHY_TRAINCTRL7_rpt_nomrs_START               (30)
#define SOC_HIPACKPHY_TRAINCTRL7_rpt_nomrs_END                 (30)
#define SOC_HIPACKPHY_TRAINCTRL7_info_full_tccd_sel_START      (31)
#define SOC_HIPACKPHY_TRAINCTRL7_info_full_tccd_sel_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCMDBDL0_UNION
 �ṹ˵��  : ACCMDBDL0 �Ĵ����ṹ���塣��ַƫ����:0x120����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  odt0_bdl : 7;  /* bit[0-6]  : Bit delay line setting of ODT0
                                                    Move to AC_Static_Reg */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  odt1_bdl : 7;  /* bit[16-22]: Bit delay line setting of ODT1
                                                    Move to AC_Static_Reg */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACCMDBDL0_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL0_odt0_bdl_START  (0)
#define SOC_HIPACKPHY_ACCMDBDL0_odt0_bdl_END    (6)
#define SOC_HIPACKPHY_ACCMDBDL0_odt1_bdl_START  (16)
#define SOC_HIPACKPHY_ACCMDBDL0_odt1_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCMDBDL1_UNION
 �ṹ˵��  : ACCMDBDL1 �Ĵ����ṹ���塣��ַƫ����:0x124����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  odt2_bdl : 7;  /* bit[0-6]  : Bit delay line setting of ODT2 */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  odt3_bdl : 7;  /* bit[16-22]: Bit delay line setting of ODT3 */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACCMDBDL1_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL1_odt2_bdl_START  (0)
#define SOC_HIPACKPHY_ACCMDBDL1_odt2_bdl_END    (6)
#define SOC_HIPACKPHY_ACCMDBDL1_odt3_bdl_START  (16)
#define SOC_HIPACKPHY_ACCMDBDL1_odt3_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCMDBDL2_UNION
 �ṹ˵��  : ACCMDBDL2 �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cs0_bdl  : 7;  /* bit[0-6]  : Bit delay line setting of CS0 */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  cs1_bdl  : 7;  /* bit[16-22]: Bit delay line setting of CS1 */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACCMDBDL2_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL2_cs0_bdl_START   (0)
#define SOC_HIPACKPHY_ACCMDBDL2_cs0_bdl_END     (6)
#define SOC_HIPACKPHY_ACCMDBDL2_cs1_bdl_START   (16)
#define SOC_HIPACKPHY_ACCMDBDL2_cs1_bdl_END     (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCMDBDL3_UNION
 �ṹ˵��  : ACCMDBDL3 �Ĵ����ṹ���塣��ַƫ����:0x12C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cs2_bdl  : 7;  /* bit[0-6]  : Bit delay line setting of CS2 */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  cs3_bdl  : 7;  /* bit[16-22]: Bit delay line setting of CS3 */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACCMDBDL3_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL3_cs2_bdl_START   (0)
#define SOC_HIPACKPHY_ACCMDBDL3_cs2_bdl_END     (6)
#define SOC_HIPACKPHY_ACCMDBDL3_cs3_bdl_START   (16)
#define SOC_HIPACKPHY_ACCMDBDL3_cs3_bdl_END     (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCMDBDL4_UNION
 �ṹ˵��  : ACCMDBDL4 �Ĵ����ṹ���塣��ַƫ����:0x130����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cke0_bdl : 7;  /* bit[0-6]  : Bit delay line setting of CKE0
                                                    Move to AC_Static_Reg */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  cke1_bdl : 7;  /* bit[16-22]: Bit delay line setting of CKE1
                                                    Move to AC_Static_Reg */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACCMDBDL4_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL4_cke0_bdl_START  (0)
#define SOC_HIPACKPHY_ACCMDBDL4_cke0_bdl_END    (6)
#define SOC_HIPACKPHY_ACCMDBDL4_cke1_bdl_START  (16)
#define SOC_HIPACKPHY_ACCMDBDL4_cke1_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCMDBDL5_UNION
 �ṹ˵��  : ACCMDBDL5 �Ĵ����ṹ���塣��ַƫ����:0x134����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cke2_bdl : 7;  /* bit[0-6]  : Bit delay line setting of CKE2 */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  cke3_bdl : 7;  /* bit[16-22]: Bit delay line setting of CKE3 */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACCMDBDL5_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL5_cke2_bdl_START  (0)
#define SOC_HIPACKPHY_ACCMDBDL5_cke2_bdl_END    (6)
#define SOC_HIPACKPHY_ACCMDBDL5_cke3_bdl_START  (16)
#define SOC_HIPACKPHY_ACCMDBDL5_cke3_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCMDBDL6_UNION
 �ṹ˵��  : ACCMDBDL6 �Ĵ����ṹ���塣��ַƫ����:0x138����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  we_bdl   : 7;  /* bit[0-6]  : Bit delay line setting of WE */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  cas_bdl  : 7;  /* bit[16-22]: Bit delay line setting of CAS */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACCMDBDL6_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL6_we_bdl_START    (0)
#define SOC_HIPACKPHY_ACCMDBDL6_we_bdl_END      (6)
#define SOC_HIPACKPHY_ACCMDBDL6_cas_bdl_START   (16)
#define SOC_HIPACKPHY_ACCMDBDL6_cas_bdl_END     (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCMDBDL7_UNION
 �ṹ˵��  : ACCMDBDL7 �Ĵ����ṹ���塣��ַƫ����:0x13C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ras_bdl    : 7;  /* bit[0-6]  : Bit delay line setting of RAS */
        unsigned int  reserved_0 : 9;  /* bit[7-15] : -- */
        unsigned int  resetn_bdl : 7;  /* bit[16-22]: Bit delay line setting of RESETN */
        unsigned int  reserved_1 : 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACCMDBDL7_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL7_ras_bdl_START     (0)
#define SOC_HIPACKPHY_ACCMDBDL7_ras_bdl_END       (6)
#define SOC_HIPACKPHY_ACCMDBDL7_resetn_bdl_START  (16)
#define SOC_HIPACKPHY_ACCMDBDL7_resetn_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACADDRBDL0_UNION
 �ṹ˵��  : ACADDRBDL0 �Ĵ����ṹ���塣��ַƫ����:0x140����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC address bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr0_bdl : 7;  /* bit[0-6]  : Bit delay line setting of ADDR0 */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  addr1_bdl : 7;  /* bit[16-22]: Bit delay line setting of ADDR1 */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACADDRBDL0_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL0_addr0_bdl_START  (0)
#define SOC_HIPACKPHY_ACADDRBDL0_addr0_bdl_END    (6)
#define SOC_HIPACKPHY_ACADDRBDL0_addr1_bdl_START  (16)
#define SOC_HIPACKPHY_ACADDRBDL0_addr1_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACADDRBDL1_UNION
 �ṹ˵��  : ACADDRBDL1 �Ĵ����ṹ���塣��ַƫ����:0x144����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC address bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr2_bdl : 7;  /* bit[0-6]  : Bit delay line setting of ADDR2 */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  addr3_bdl : 7;  /* bit[16-22]: Bit delay line setting of ADDR3 */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACADDRBDL1_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL1_addr2_bdl_START  (0)
#define SOC_HIPACKPHY_ACADDRBDL1_addr2_bdl_END    (6)
#define SOC_HIPACKPHY_ACADDRBDL1_addr3_bdl_START  (16)
#define SOC_HIPACKPHY_ACADDRBDL1_addr3_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACADDRBDL2_UNION
 �ṹ˵��  : ACADDRBDL2 �Ĵ����ṹ���塣��ַƫ����:0x148����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC address bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr4_bdl : 7;  /* bit[0-6]  : Bit delay line setting of ADDR4 */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  addr5_bdl : 7;  /* bit[16-22]: Bit delay line setting of ADDR5 */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACADDRBDL2_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL2_addr4_bdl_START  (0)
#define SOC_HIPACKPHY_ACADDRBDL2_addr4_bdl_END    (6)
#define SOC_HIPACKPHY_ACADDRBDL2_addr5_bdl_START  (16)
#define SOC_HIPACKPHY_ACADDRBDL2_addr5_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACADDRBDL3_UNION
 �ṹ˵��  : ACADDRBDL3 �Ĵ����ṹ���塣��ַƫ����:0x14C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC address bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr6_bdl : 7;  /* bit[0-6]  : Bit delay line setting of ADDR6 */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  addr7_bdl : 7;  /* bit[16-22]: Bit delay line setting of ADDR7 */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACADDRBDL3_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL3_addr6_bdl_START  (0)
#define SOC_HIPACKPHY_ACADDRBDL3_addr6_bdl_END    (6)
#define SOC_HIPACKPHY_ACADDRBDL3_addr7_bdl_START  (16)
#define SOC_HIPACKPHY_ACADDRBDL3_addr7_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACADDRBDL4_UNION
 �ṹ˵��  : ACADDRBDL4 �Ĵ����ṹ���塣��ַƫ����:0x150����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC address bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr8_bdl : 7;  /* bit[0-6]  : Bit delay line setting of ADDR8 */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  addr9_bdl : 7;  /* bit[16-22]: Bit delay line setting of ADDR9 */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACADDRBDL4_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL4_addr8_bdl_START  (0)
#define SOC_HIPACKPHY_ACADDRBDL4_addr8_bdl_END    (6)
#define SOC_HIPACKPHY_ACADDRBDL4_addr9_bdl_START  (16)
#define SOC_HIPACKPHY_ACADDRBDL4_addr9_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACADDRBDL5_UNION
 �ṹ˵��  : ACADDRBDL5 �Ĵ����ṹ���塣��ַƫ����:0x154����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC address bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr10_bdl : 7;  /* bit[0-6]  : Bit delay line setting of ADDR10 */
        unsigned int  reserved_0 : 9;  /* bit[7-15] : -- */
        unsigned int  addr11_bdl : 7;  /* bit[16-22]: Bit delay line setting of ADDR11 */
        unsigned int  reserved_1 : 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACADDRBDL5_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL5_addr10_bdl_START  (0)
#define SOC_HIPACKPHY_ACADDRBDL5_addr10_bdl_END    (6)
#define SOC_HIPACKPHY_ACADDRBDL5_addr11_bdl_START  (16)
#define SOC_HIPACKPHY_ACADDRBDL5_addr11_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACADDRBDL6_UNION
 �ṹ˵��  : ACADDRBDL6 �Ĵ����ṹ���塣��ַƫ����:0x158����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC address bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr12_bdl : 7;  /* bit[0-6]  : Bit delay line setting of ADDR12 */
        unsigned int  reserved_0 : 9;  /* bit[7-15] : -- */
        unsigned int  addr13_bdl : 7;  /* bit[16-22]: Bit delay line setting of ADDR13 */
        unsigned int  reserved_1 : 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACADDRBDL6_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL6_addr12_bdl_START  (0)
#define SOC_HIPACKPHY_ACADDRBDL6_addr12_bdl_END    (6)
#define SOC_HIPACKPHY_ACADDRBDL6_addr13_bdl_START  (16)
#define SOC_HIPACKPHY_ACADDRBDL6_addr13_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACADDRBDL7_UNION
 �ṹ˵��  : ACADDRBDL7 �Ĵ����ṹ���塣��ַƫ����:0x15C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC address bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr14_bdl : 7;  /* bit[0-6]  : Bit delay line setting of ADDR14 */
        unsigned int  reserved_0 : 9;  /* bit[7-15] : -- */
        unsigned int  addr15_bdl : 7;  /* bit[16-22]: Bit delay line setting of ADDR15 */
        unsigned int  reserved_1 : 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACADDRBDL7_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL7_addr14_bdl_START  (0)
#define SOC_HIPACKPHY_ACADDRBDL7_addr14_bdl_END    (6)
#define SOC_HIPACKPHY_ACADDRBDL7_addr15_bdl_START  (16)
#define SOC_HIPACKPHY_ACADDRBDL7_addr15_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACADDRBDL8_UNION
 �ṹ˵��  : ACADDRBDL8 �Ĵ����ṹ���塣��ַƫ����:0x160����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC address bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ba0_bdl  : 7;  /* bit[0-6]  : Bit delay line setting of BA0 */
        unsigned int  reserved_0: 9;  /* bit[7-15] : -- */
        unsigned int  ba1_bdl  : 7;  /* bit[16-22]: Bit delay line setting of BA1 */
        unsigned int  reserved_1: 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACADDRBDL8_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL8_ba0_bdl_START   (0)
#define SOC_HIPACKPHY_ACADDRBDL8_ba0_bdl_END     (6)
#define SOC_HIPACKPHY_ACADDRBDL8_ba1_bdl_START   (16)
#define SOC_HIPACKPHY_ACADDRBDL8_ba1_bdl_END     (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACADDRBDL9_UNION
 �ṹ˵��  : ACADDRBDL9 �Ĵ����ṹ���塣��ַƫ����:0x164����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC address bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ba2_bdl  : 7;  /* bit[0-6] : Bit delay line setting of BA2 */
        unsigned int  reserved : 25; /* bit[7-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACADDRBDL9_UNION;
#endif
#define SOC_HIPACKPHY_ACADDRBDL9_ba2_bdl_START   (0)
#define SOC_HIPACKPHY_ACADDRBDL9_ba2_bdl_END     (6)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCLKBDL_UNION
 �ṹ˵��  : ACCLKBDL �Ĵ����ṹ���塣��ַƫ����:0x168����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC clock bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dramclk0_bdl : 7;  /* bit[0-6]  : Move to AC_Static_Reg */
        unsigned int  reserved_0   : 1;  /* bit[7]    : -- */
        unsigned int  dramclk1_bdl : 7;  /* bit[8-14] : Move to AC_Static_Reg */
        unsigned int  reserved_1   : 1;  /* bit[15]   :  */
        unsigned int  refclk_bdl   : 5;  /* bit[16-20]: Bit delay line setting of REFCLK
                                                        Move to AC_Static_Reg */
        unsigned int  reserved_2   : 3;  /* bit[21-23]:  */
        unsigned int  fbclk_bdl    : 5;  /* bit[24-28]: Bit delay line setting of FBCLK
                                                        Move to AC_Static_Reg */
        unsigned int  reserved_3   : 3;  /* bit[29-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACCLKBDL_UNION;
#endif
#define SOC_HIPACKPHY_ACCLKBDL_dramclk0_bdl_START  (0)
#define SOC_HIPACKPHY_ACCLKBDL_dramclk0_bdl_END    (6)
#define SOC_HIPACKPHY_ACCLKBDL_dramclk1_bdl_START  (8)
#define SOC_HIPACKPHY_ACCLKBDL_dramclk1_bdl_END    (14)
#define SOC_HIPACKPHY_ACCLKBDL_refclk_bdl_START    (16)
#define SOC_HIPACKPHY_ACCLKBDL_refclk_bdl_END      (20)
#define SOC_HIPACKPHY_ACCLKBDL_fbclk_bdl_START     (24)
#define SOC_HIPACKPHY_ACCLKBDL_fbclk_bdl_END       (28)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYCTL0_UNION
 �ṹ˵��  : ACPHYCTL0 �Ĵ����ṹ���塣��ַƫ����:0x170����ֵ:0x00002010�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enshift_a0           : 1;  /* bit[0]    : PHY control registers. */
        unsigned int  margin_a0            : 1;  /* bit[1]    : PHY control registers. */
        unsigned int  margin_a1            : 1;  /* bit[2]    : PHY control registers. */
        unsigned int  dramclk_h            : 1;  /* bit[3]    : PHY control registers.
                                                                Move to AC_Static_Reg */
        unsigned int  dramclk_l            : 1;  /* bit[4]    : PHY control registers.
                                                                Move to AC_Static_Reg */
        unsigned int  lvdqclkdiv2          : 1;  /* bit[5]    : PHY control registers.
                                                                Move to AC_Static_Reg */
        unsigned int  bufphyclk_div2       : 1;  /* bit[6]    : PHY control registers.
                                                                Move to AC_Static_Reg */
        unsigned int  ac_byp_clk_gated_dis : 1;  /* bit[7]    : AC clock gated disable in bypass mode.
                                                                0: turn off clocks in bypass mode (default)
                                                                1: turn on clocks in bypass mode
                                                                Move to AC_Static_Reg */
        unsigned int  ac_byp_ck90_cmd_code : 9;  /* bit[8-16] : Move to AC_Static_Reg
                                                                Only bit[7:1] are valid. Used as {bit[7:1],1'b1}. The bit[8] is useless. */
        unsigned int  reserved             : 15; /* bit[17-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACPHYCTL0_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL0_enshift_a0_START            (0)
#define SOC_HIPACKPHY_ACPHYCTL0_enshift_a0_END              (0)
#define SOC_HIPACKPHY_ACPHYCTL0_margin_a0_START             (1)
#define SOC_HIPACKPHY_ACPHYCTL0_margin_a0_END               (1)
#define SOC_HIPACKPHY_ACPHYCTL0_margin_a1_START             (2)
#define SOC_HIPACKPHY_ACPHYCTL0_margin_a1_END               (2)
#define SOC_HIPACKPHY_ACPHYCTL0_dramclk_h_START             (3)
#define SOC_HIPACKPHY_ACPHYCTL0_dramclk_h_END               (3)
#define SOC_HIPACKPHY_ACPHYCTL0_dramclk_l_START             (4)
#define SOC_HIPACKPHY_ACPHYCTL0_dramclk_l_END               (4)
#define SOC_HIPACKPHY_ACPHYCTL0_lvdqclkdiv2_START           (5)
#define SOC_HIPACKPHY_ACPHYCTL0_lvdqclkdiv2_END             (5)
#define SOC_HIPACKPHY_ACPHYCTL0_bufphyclk_div2_START        (6)
#define SOC_HIPACKPHY_ACPHYCTL0_bufphyclk_div2_END          (6)
#define SOC_HIPACKPHY_ACPHYCTL0_ac_byp_clk_gated_dis_START  (7)
#define SOC_HIPACKPHY_ACPHYCTL0_ac_byp_clk_gated_dis_END    (7)
#define SOC_HIPACKPHY_ACPHYCTL0_ac_byp_ck90_cmd_code_START  (8)
#define SOC_HIPACKPHY_ACPHYCTL0_ac_byp_ck90_cmd_code_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYCTL1_UNION
 �ṹ˵��  : ACPHYCTL1 �Ĵ����ṹ���塣��ַƫ����:0x174����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dram1sel_reset : 1;  /* bit[0]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  dram1sel_cs    : 1;  /* bit[1]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  dram1sel_cke   : 1;  /* bit[2]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  dram1sel_odt   : 1;  /* bit[3]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  dram1sel_ras   : 1;  /* bit[4]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  dram1sel_cas   : 1;  /* bit[5]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  dram1sel_we    : 1;  /* bit[6]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  reserved_0     : 1;  /* bit[7]    : -- */
        unsigned int  dram1sel_ba    : 3;  /* bit[8-10] : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  reserved_1     : 5;  /* bit[11-15]: -- */
        unsigned int  dram1sel_addr  : 16; /* bit[16-31]: PHY control registers. */
    } reg;
} SOC_HIPACKPHY_ACPHYCTL1_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_reset_START  (0)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_reset_END    (0)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_cs_START     (1)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_cs_END       (1)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_cke_START    (2)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_cke_END      (2)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_odt_START    (3)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_odt_END      (3)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_ras_START    (4)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_ras_END      (4)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_cas_START    (5)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_cas_END      (5)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_we_START     (6)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_we_END       (6)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_ba_START     (8)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_ba_END       (10)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_addr_START   (16)
#define SOC_HIPACKPHY_ACPHYCTL1_dram1sel_addr_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYCTL2_UNION
 �ṹ˵��  : ACPHYCTL2 �Ĵ����ṹ���塣��ַƫ����:0x178����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sdrsel_reset : 1;  /* bit[0]    : PHY control registers.
                                                        Move to AC_Static_Reg */
        unsigned int  sdrsel_cs    : 1;  /* bit[1]    : PHY control registers.
                                                        Move to AC_Static_Reg */
        unsigned int  sdrsel_cke   : 1;  /* bit[2]    : PHY control registers.
                                                        Move to AC_Static_Reg */
        unsigned int  sdrsel_odt   : 1;  /* bit[3]    : PHY control registers.
                                                        Move to AC_Static_Reg */
        unsigned int  sdrsel_ras   : 1;  /* bit[4]    : PHY control registers.
                                                        Move to AC_Static_Reg */
        unsigned int  sdrsel_cas   : 1;  /* bit[5]    : PHY control registers.
                                                        Move to AC_Static_Reg */
        unsigned int  sdrsel_we    : 1;  /* bit[6]    : PHY control registers.
                                                        Move to AC_Static_Reg */
        unsigned int  reserved_0   : 1;  /* bit[7]    : -- */
        unsigned int  sdrsel_ba    : 3;  /* bit[8-10] : PHY control registers.
                                                        Move to AC_Static_Reg */
        unsigned int  reserved_1   : 5;  /* bit[11-15]: -- */
        unsigned int  sdrsel_addr  : 16; /* bit[16-31]: PHY control registers. */
    } reg;
} SOC_HIPACKPHY_ACPHYCTL2_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_reset_START  (0)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_reset_END    (0)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_cs_START     (1)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_cs_END       (1)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_cke_START    (2)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_cke_END      (2)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_odt_START    (3)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_odt_END      (3)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_ras_START    (4)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_ras_END      (4)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_cas_START    (5)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_cas_END      (5)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_we_START     (6)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_we_END       (6)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_ba_START     (8)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_ba_END       (10)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_addr_START   (16)
#define SOC_HIPACKPHY_ACPHYCTL2_sdrsel_addr_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYCTL3_UNION
 �ṹ˵��  : ACPHYCTL3 �Ĵ����ṹ���塣��ַƫ����:0x17C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  posedge_reset : 1;  /* bit[0]    : PHY control registers.
                                                         Move to AC_Static_Reg */
        unsigned int  posedge_cs    : 1;  /* bit[1]    : PHY control registers.
                                                         Move to AC_Static_Reg */
        unsigned int  posedge_cke   : 1;  /* bit[2]    : PHY control registers.
                                                         Move to AC_Static_Reg */
        unsigned int  posedge_odt   : 1;  /* bit[3]    : PHY control registers.
                                                         Move to AC_Static_Reg */
        unsigned int  posedge_ras   : 1;  /* bit[4]    : PHY control registers.
                                                         Move to AC_Static_Reg */
        unsigned int  posedge_cas   : 1;  /* bit[5]    : PHY control registers.
                                                         Move to AC_Static_Reg */
        unsigned int  posedge_we    : 1;  /* bit[6]    : PHY control registers.
                                                         Move to AC_Static_Reg */
        unsigned int  reserved_0    : 1;  /* bit[7]    : -- */
        unsigned int  posedge_ba    : 3;  /* bit[8-10] : PHY control registers.
                                                         Move to AC_Static_Reg */
        unsigned int  reserved_1    : 5;  /* bit[11-15]: -- */
        unsigned int  posedge_addr  : 16; /* bit[16-31]: PHY control registers. */
    } reg;
} SOC_HIPACKPHY_ACPHYCTL3_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_reset_START  (0)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_reset_END    (0)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_cs_START     (1)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_cs_END       (1)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_cke_START    (2)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_cke_END      (2)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_odt_START    (3)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_odt_END      (3)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_ras_START    (4)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_ras_END      (4)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_cas_START    (5)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_cas_END      (5)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_we_START     (6)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_we_END       (6)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_ba_START     (8)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_ba_END       (10)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_addr_START   (16)
#define SOC_HIPACKPHY_ACPHYCTL3_posedge_addr_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYCTL4_UNION
 �ṹ˵��  : ACPHYCTL4 �Ĵ����ṹ���塣��ַƫ����:0x180����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timing2t_reset : 1;  /* bit[0]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  timing2t_cs    : 1;  /* bit[1]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  timing2t_cke   : 1;  /* bit[2]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  timing2t_odt   : 1;  /* bit[3]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  timing2t_ras   : 1;  /* bit[4]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  timing2t_cas   : 1;  /* bit[5]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  timing2t_we    : 1;  /* bit[6]    : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  reserved_0     : 1;  /* bit[7]    : -- */
        unsigned int  timing2t_ba    : 3;  /* bit[8-10] : PHY control registers.
                                                          Move to AC_Static_Reg */
        unsigned int  reserved_1     : 5;  /* bit[11-15]: -- */
        unsigned int  timing2t_addr  : 16; /* bit[16-31]: PHY control registers. */
    } reg;
} SOC_HIPACKPHY_ACPHYCTL4_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_reset_START  (0)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_reset_END    (0)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_cs_START     (1)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_cs_END       (1)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_cke_START    (2)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_cke_END      (2)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_odt_START    (3)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_odt_END      (3)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_ras_START    (4)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_ras_END      (4)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_cas_START    (5)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_cas_END      (5)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_we_START     (6)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_we_END       (6)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_ba_START     (8)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_ba_END       (10)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_addr_START   (16)
#define SOC_HIPACKPHY_ACPHYCTL4_timing2t_addr_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYCTL5_UNION
 �ṹ˵��  : ACPHYCTL5 �Ĵ����ṹ���塣��ַƫ����:0x184����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk1x_dramclk0   : 4;  /* bit[0-3]  : PHY control registers.
                                                            Move to AC_Static_Reg */
        unsigned int  clk1x_dramclk1   : 4;  /* bit[4-7]  : PHY control registers.
                                                            Move to AC_Static_Reg */
        unsigned int  clk1x_cmd2t_ctl  : 4;  /* bit[8-11] : PHY control registers. */
        unsigned int  clk1x_cmd2t      : 4;  /* bit[12-15]: PHY control registers.
                                                            Move to AC_Static_Reg */
        unsigned int  clk1x_cmd1t      : 4;  /* bit[16-19]: PHY control registers.
                                                            Move to AC_Static_Reg */
        unsigned int  clk1x_mclk       : 4;  /* bit[20-23]: PHY control registers.
                                                            Move to AC_Static_Reg */
        unsigned int  clk1x_cmd2t_ctl2 : 4;  /* bit[24-27]: PHY control registers. */
        unsigned int  reserved         : 4;  /* bit[28-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACPHYCTL5_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_dramclk0_START    (0)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_dramclk0_END      (3)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_dramclk1_START    (4)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_dramclk1_END      (7)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd2t_ctl_START   (8)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd2t_ctl_END     (11)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd2t_START       (12)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd2t_END         (15)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd1t_START       (16)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd1t_END         (19)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_mclk_START        (20)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_mclk_END          (23)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd2t_ctl2_START  (24)
#define SOC_HIPACKPHY_ACPHYCTL5_clk1x_cmd2t_ctl2_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYCTL6_UNION
 �ṹ˵��  : ACPHYCTL6 �Ĵ����ṹ���塣��ַƫ����:0x188����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk2x_dramclk0   : 4;  /* bit[0-3]  : PHY control registers.
                                                            Move to AC_Static_Reg */
        unsigned int  clk2x_dramclk1   : 4;  /* bit[4-7]  : PHY control registers.
                                                            Move to AC_Static_Reg */
        unsigned int  clk2x_cmd2t_ctl  : 4;  /* bit[8-11] : PHY control registers. */
        unsigned int  clk2x_cmd2t      : 4;  /* bit[12-15]: PHY control registers.
                                                            Move to AC_Static_Reg */
        unsigned int  clk2x_cmd1t      : 4;  /* bit[16-19]: PHY control registers.
                                                            Move to AC_Static_Reg */
        unsigned int  clk2x_mclk       : 4;  /* bit[20-23]: PHY control registers.
                                                            Move to AC_Static_Reg */
        unsigned int  clk2x_cmd2t_ctl2 : 4;  /* bit[24-27]: PHY control registers. */
        unsigned int  reserved         : 4;  /* bit[28-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACPHYCTL6_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_dramclk0_START    (0)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_dramclk0_END      (3)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_dramclk1_START    (4)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_dramclk1_END      (7)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd2t_ctl_START   (8)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd2t_ctl_END     (11)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd2t_START       (12)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd2t_END         (15)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd1t_START       (16)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd1t_END         (19)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_mclk_START        (20)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_mclk_END          (23)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd2t_ctl2_START  (24)
#define SOC_HIPACKPHY_ACPHYCTL6_clk2x_cmd2t_ctl2_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYCTL7_UNION
 �ṹ˵��  : ACPHYCTL7 �Ĵ����ṹ���塣��ַƫ����:0x018C����ֵ:0x00800000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ckd2_mclk       : 3;  /* bit[0-2]  : Dummy Reg - Not Used */
        unsigned int  ck0p_mclk       : 3;  /* bit[3-5]  : Move to AC_Static_Reg */
        unsigned int  ck1p_dclk0      : 3;  /* bit[6-8]  : Configure DRAM CK0 Clock Phase from PLL 1 tap : 1/16 T
                                                           Move to AC_Static_Reg */
        unsigned int  ck2p_dclk1      : 3;  /* bit[9-11] : Configure DRAM CK1 Clock Phase from PLL 1 tap : 1/16 T
                                                           Move to AC_Static_Reg */
        unsigned int  ck3p_cmd1t      : 3;  /* bit[12-14]: Move to AC_Static_Reg */
        unsigned int  reserved_0      : 3;  /* bit[15-17]:  */
        unsigned int  ck5p_cmd2tc     : 3;  /* bit[18-20]: Dummy Reg - Not Used */
        unsigned int  halft_cmd2tctl  : 1;  /* bit[21]   : Dummy Reg - Not Used */
        unsigned int  reserved_1      : 1;  /* bit[22]   :  */
        unsigned int  halft_cmd1t     : 1;  /* bit[23]   : Move to AC_Static_Reg */
        unsigned int  halft_dramclk1  : 1;  /* bit[24]   : Move to AC_Static_Reg */
        unsigned int  halft_dramclk0  : 1;  /* bit[25]   : Move to AC_Static_Reg */
        unsigned int  halft_cmd2tctl2 : 1;  /* bit[26]   : Dummy Reg - Not Used */
        unsigned int  reserved_2      : 5;  /* bit[27-31]:  */
    } reg;
} SOC_HIPACKPHY_ACPHYCTL7_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL7_ckd2_mclk_START        (0)
#define SOC_HIPACKPHY_ACPHYCTL7_ckd2_mclk_END          (2)
#define SOC_HIPACKPHY_ACPHYCTL7_ck0p_mclk_START        (3)
#define SOC_HIPACKPHY_ACPHYCTL7_ck0p_mclk_END          (5)
#define SOC_HIPACKPHY_ACPHYCTL7_ck1p_dclk0_START       (6)
#define SOC_HIPACKPHY_ACPHYCTL7_ck1p_dclk0_END         (8)
#define SOC_HIPACKPHY_ACPHYCTL7_ck2p_dclk1_START       (9)
#define SOC_HIPACKPHY_ACPHYCTL7_ck2p_dclk1_END         (11)
#define SOC_HIPACKPHY_ACPHYCTL7_ck3p_cmd1t_START       (12)
#define SOC_HIPACKPHY_ACPHYCTL7_ck3p_cmd1t_END         (14)
#define SOC_HIPACKPHY_ACPHYCTL7_ck5p_cmd2tc_START      (18)
#define SOC_HIPACKPHY_ACPHYCTL7_ck5p_cmd2tc_END        (20)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_cmd2tctl_START   (21)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_cmd2tctl_END     (21)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_cmd1t_START      (23)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_cmd1t_END        (23)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_dramclk1_START   (24)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_dramclk1_END     (24)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_dramclk0_START   (25)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_dramclk0_END     (25)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_cmd2tctl2_START  (26)
#define SOC_HIPACKPHY_ACPHYCTL7_halft_cmd2tctl2_END    (26)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACDEBUG_UNION
 �ṹ˵��  : ACDEBUG �Ĵ����ṹ���塣��ַƫ����:0x0190����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is for PHY debug only.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ac_rdcnt       : 3;  /* bit[0-2]  : Move to AC_Static_Reg */
        unsigned int  reserved_0     : 5;  /* bit[3-7]  :  */
        unsigned int  deskew_regread : 1;  /* bit[8]    : Move to AC_Static_Reg */
        unsigned int  reserved_1     : 7;  /* bit[9-15] :  */
        unsigned int  acdbg_config   : 4;  /* bit[16-19]: Move to AC_Static_Reg */
        unsigned int  reserved_2     : 12; /* bit[20-31]:  */
    } reg;
} SOC_HIPACKPHY_ACDEBUG_UNION;
#endif
#define SOC_HIPACKPHY_ACDEBUG_ac_rdcnt_START        (0)
#define SOC_HIPACKPHY_ACDEBUG_ac_rdcnt_END          (2)
#define SOC_HIPACKPHY_ACDEBUG_deskew_regread_START  (8)
#define SOC_HIPACKPHY_ACDEBUG_deskew_regread_END    (8)
#define SOC_HIPACKPHY_ACDEBUG_acdbg_config_START    (16)
#define SOC_HIPACKPHY_ACDEBUG_acdbg_config_END      (19)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYRSVDC_UNION
 �ṹ˵��  : ACPHYRSVDC �Ĵ����ṹ���塣��ַƫ����:0x0194����ֵ:0xFFFF0000�����:32
 �Ĵ���˵��: AC block PHY reserved control pins. This register is for PHY control and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ac_rsv_control : 32; /* bit[0-31]: Reserved registers for the future.
                                                         PHY side's ACPHYRSVDC is moved to AC_Static_Reg
                                                         ----------------------------------------
                                                         bit[29:24] - [K3V5] No ODT Mode NDRV Setting (Using All One as Default)
                                                         ----------------------------------------
                                                         bit[17]-wdet_rb2nd_fine_en:
                                                         WDET RBoundray 2nd fine-tune.
                                                         1: Enable (default)
                                                         0: Disable
                                                         
                                                         bit[16]-wdet_ave_domp_en:
                                                         WDET phase average error (0.5phase) compenstaion function.
                                                         1: Enable (default)
                                                         0: Disable
                                                         
                                                         ----------------------------------------
                                                         bit[5] - [K3V5] non_odt_mode_en
                                                         0: Using Original IO NDRV Setting
                                                         1: Using [29:24] to Control NDRV Stting (Prefer to set All One at Non-ODT Mode)
                                                         ----------------------------------------
                                                         
                                                         bit[4]-wdet_byp_mode:
                                                         1:Enable
                                                         0:Disable(default)
                                                         Note: if enabled,
                                                         half_ph_bdl_en=0x1
                                                         wet_ph_step=0x3
                                                         wdet_ds_en=0x0
                                                         wdet_rb2nd_fine_en=0x0
                                                         phaseradix3en=0x0
                                                         wdet_lb_backtap=0x0
                                                         wdet_rb_backtap=0x0
                                                         
                                                         bit[3]-rdet_lb_ctdone_stop
                                                         0: Keep Reduce RDQSBDL until All Bytes with any Failed when LB Search
                                                         1: RDQSBDL will Stop to Reduce with Any Failed Respectively
                                                         bit[2]-wdet_lb_ctdone_stop
                                                         
                                                         bit[1]-cat_deskew_skip:
                                                         1: skip deskew in CAT/CBT
                                                         0: do deskew in CAT/CBT (default)
                                                         
                                                         bit[0]-fast_wdet_en:
                                                         1: enable
                                                         0: disable (default) */
    } reg;
} SOC_HIPACKPHY_ACPHYRSVDC_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYRSVDC_ac_rsv_control_START  (0)
#define SOC_HIPACKPHY_ACPHYRSVDC_ac_rsv_control_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYRSVDS_UNION
 �ṹ˵��  : ACPHYRSVDS �Ĵ����ṹ���塣��ַƫ����:0x0198����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY reserved control pins. This register is for PHY control and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ac_rsv_status : 32; /* bit[0-31]: Reserved registers for the future.
                                                        Move to AC_Static_Reg */
    } reg;
} SOC_HIPACKPHY_ACPHYRSVDS_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYRSVDS_ac_rsv_status_START  (0)
#define SOC_HIPACKPHY_ACPHYRSVDS_ac_rsv_status_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYCTL8_UNION
 �ṹ˵��  : ACPHYCTL8 �Ĵ����ṹ���塣��ַƫ����:0x019C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ac_ck6p_reserve  : 3;  /* bit[0-2]  : Dummy Reg - Not Used */
        unsigned int  ac_ck7p_reserve  : 3;  /* bit[3-5]  : Dummy Reg - Not Used */
        unsigned int  ac_ck8p_reserve  : 3;  /* bit[6-8]  : Dummy Reg - Not Used */
        unsigned int  ac_ck9p_reserve  : 3;  /* bit[9-11] : Dummy Reg - Not Used */
        unsigned int  ac_ck10p_reserve : 3;  /* bit[12-14]: Dummy Reg - Not Used */
        unsigned int  ac_ck11p_reserve : 3;  /* bit[15-17]: Dummy Reg - Not Used */
        unsigned int  ac_ck12p_reserve : 3;  /* bit[18-20]: Dummy Reg - Not Used */
        unsigned int  reserved         : 11; /* bit[21-31]:  */
    } reg;
} SOC_HIPACKPHY_ACPHYCTL8_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck6p_reserve_START   (0)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck6p_reserve_END     (2)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck7p_reserve_START   (3)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck7p_reserve_END     (5)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck8p_reserve_START   (6)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck8p_reserve_END     (8)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck9p_reserve_START   (9)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck9p_reserve_END     (11)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck10p_reserve_START  (12)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck10p_reserve_END    (14)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck11p_reserve_START  (15)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck11p_reserve_END    (17)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck12p_reserve_START  (18)
#define SOC_HIPACKPHY_ACPHYCTL8_ac_ck12p_reserve_END    (20)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCMDBDL8_UNION
 �ṹ˵��  : ACCMDBDL8 �Ĵ����ṹ���塣��ַƫ����:0x1A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  odt1_bdl0 : 7;  /* bit[0-6]  : Dummy Reg - Not Used */
        unsigned int  reserved_0: 9;  /* bit[7-15] :  */
        unsigned int  odt1_bdl1 : 7;  /* bit[16-22]: Dummy Reg - Not Used */
        unsigned int  reserved_1: 9;  /* bit[23-31]:  */
    } reg;
} SOC_HIPACKPHY_ACCMDBDL8_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL8_odt1_bdl0_START  (0)
#define SOC_HIPACKPHY_ACCMDBDL8_odt1_bdl0_END    (6)
#define SOC_HIPACKPHY_ACCMDBDL8_odt1_bdl1_START  (16)
#define SOC_HIPACKPHY_ACCMDBDL8_odt1_bdl1_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCMDBDL9_UNION
 �ṹ˵��  : ACCMDBDL9 �Ĵ����ṹ���塣��ַƫ����:0x1A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  odt1_bdl2 : 7;  /* bit[0-6]  : Dummy Reg - Not Used */
        unsigned int  reserved_0: 9;  /* bit[7-15] :  */
        unsigned int  odt1_bdl3 : 7;  /* bit[16-22]: Dummy Reg - Not Used */
        unsigned int  reserved_1: 9;  /* bit[23-31]:  */
    } reg;
} SOC_HIPACKPHY_ACCMDBDL9_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL9_odt1_bdl2_START  (0)
#define SOC_HIPACKPHY_ACCMDBDL9_odt1_bdl2_END    (6)
#define SOC_HIPACKPHY_ACCMDBDL9_odt1_bdl3_START  (16)
#define SOC_HIPACKPHY_ACCMDBDL9_odt1_bdl3_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCMDBDL10_UNION
 �ṹ˵��  : ACCMDBDL10 �Ĵ����ṹ���塣��ַƫ����:0x1A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cs1_bdl0 : 7;  /* bit[0-6]  : Dummy Reg - Not Used */
        unsigned int  reserved_0: 9;  /* bit[7-15] :  */
        unsigned int  cs1_bdl1 : 7;  /* bit[16-22]: Dummy Reg - Not Used */
        unsigned int  reserved_1: 9;  /* bit[23-31]:  */
    } reg;
} SOC_HIPACKPHY_ACCMDBDL10_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL10_cs1_bdl0_START  (0)
#define SOC_HIPACKPHY_ACCMDBDL10_cs1_bdl0_END    (6)
#define SOC_HIPACKPHY_ACCMDBDL10_cs1_bdl1_START  (16)
#define SOC_HIPACKPHY_ACCMDBDL10_cs1_bdl1_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACCMDBDL11_UNION
 �ṹ˵��  : ACCMDBDL11 �Ĵ����ṹ���塣��ַƫ����:0x1AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cs1_bdl2 : 7;  /* bit[0-6]  : Dummy Reg - Not Used */
        unsigned int  reserved_0: 9;  /* bit[7-15] :  */
        unsigned int  cs1_bdl3 : 7;  /* bit[16-22]: Dummy Reg - Not Used */
        unsigned int  reserved_1: 9;  /* bit[23-31]:  */
    } reg;
} SOC_HIPACKPHY_ACCMDBDL11_UNION;
#endif
#define SOC_HIPACKPHY_ACCMDBDL11_cs1_bdl2_START  (0)
#define SOC_HIPACKPHY_ACCMDBDL11_cs1_bdl2_END    (6)
#define SOC_HIPACKPHY_ACCMDBDL11_cs1_bdl3_START  (16)
#define SOC_HIPACKPHY_ACCMDBDL11_cs1_bdl3_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYDCC_UNION
 �ṹ˵��  : ACPHYDCC �Ĵ����ṹ���塣��ַƫ����:0x01B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acdcc_dq1       : 3;  /* bit[0-2]  : Move to AC_Static_Reg */
        unsigned int  acdcc_dq0       : 3;  /* bit[3-5]  : Move to AC_Static_Reg */
        unsigned int  acdcc_dqs1      : 3;  /* bit[6-8]  : Move to AC_Static_Reg */
        unsigned int  acdcc_dqs0      : 3;  /* bit[9-11] : Move to AC_Static_Reg */
        unsigned int  acdcc_mclk      : 3;  /* bit[12-14]: Move to AC_Static_Reg */
        unsigned int  reserved_0      : 1;  /* bit[15]   :  */
        unsigned int  acdcc_dq1_byt1  : 3;  /* bit[16-18]: Move to AC_Static_Reg */
        unsigned int  acdcc_dq0_byt1  : 3;  /* bit[19-21]: Move to AC_Static_Reg */
        unsigned int  acdcc_dqs1_byt1 : 3;  /* bit[22-24]: Move to AC_Static_Reg */
        unsigned int  acdcc_dqs0_byt1 : 3;  /* bit[25-27]: Move to AC_Static_Reg */
        unsigned int  acdcc_mclk_byt1 : 3;  /* bit[28-30]: Move to AC_Static_Reg */
        unsigned int  reserved_1      : 1;  /* bit[31]   :  */
    } reg;
} SOC_HIPACKPHY_ACPHYDCC_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq1_START        (0)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq1_END          (2)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq0_START        (3)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq0_END          (5)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs1_START       (6)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs1_END         (8)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs0_START       (9)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs0_END         (11)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_mclk_START       (12)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_mclk_END         (14)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq1_byt1_START   (16)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq1_byt1_END     (18)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq0_byt1_START   (19)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dq0_byt1_END     (21)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs1_byt1_START  (22)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs1_byt1_END    (24)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs0_byt1_START  (25)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_dqs0_byt1_END    (27)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_mclk_byt1_START  (28)
#define SOC_HIPACKPHY_ACPHYDCC_acdcc_mclk_byt1_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYCTL9_UNION
 �ṹ˵��  : ACPHYCTL9 �Ĵ����ṹ���塣��ַƫ����:0x01B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acsdrsel_cs1    : 1;  /* bit[0]    : Move to AC_Static_Reg */
        unsigned int  acsdrsel_cke1   : 1;  /* bit[1]    : Move to AC_Static_Reg */
        unsigned int  acsdrsel_odt1   : 1;  /* bit[2]    : Move to AC_Static_Reg */
        unsigned int  acposedge_cs1   : 1;  /* bit[3]    : Move to AC_Static_Reg */
        unsigned int  acposedge_cke1  : 1;  /* bit[4]    : Move to AC_Static_Reg */
        unsigned int  acposedge_odt1  : 1;  /* bit[5]    : Move to AC_Static_Reg */
        unsigned int  acdram1sel_cs1  : 1;  /* bit[6]    : Move to AC_Static_Reg */
        unsigned int  acdram1sel_cke1 : 1;  /* bit[7]    : Move to AC_Static_Reg */
        unsigned int  acdram1sel_odt1 : 1;  /* bit[8]    : Move to AC_Static_Reg */
        unsigned int  actiming2t_cs1  : 1;  /* bit[9]    : Move to AC_Static_Reg */
        unsigned int  actiming2t_cke1 : 1;  /* bit[10]   : Move to AC_Static_Reg */
        unsigned int  actiming2t_odt1 : 1;  /* bit[11]   : Move to AC_Static_Reg */
        unsigned int  reserved        : 20; /* bit[12-31]:  */
    } reg;
} SOC_HIPACKPHY_ACPHYCTL9_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL9_acsdrsel_cs1_START     (0)
#define SOC_HIPACKPHY_ACPHYCTL9_acsdrsel_cs1_END       (0)
#define SOC_HIPACKPHY_ACPHYCTL9_acsdrsel_cke1_START    (1)
#define SOC_HIPACKPHY_ACPHYCTL9_acsdrsel_cke1_END      (1)
#define SOC_HIPACKPHY_ACPHYCTL9_acsdrsel_odt1_START    (2)
#define SOC_HIPACKPHY_ACPHYCTL9_acsdrsel_odt1_END      (2)
#define SOC_HIPACKPHY_ACPHYCTL9_acposedge_cs1_START    (3)
#define SOC_HIPACKPHY_ACPHYCTL9_acposedge_cs1_END      (3)
#define SOC_HIPACKPHY_ACPHYCTL9_acposedge_cke1_START   (4)
#define SOC_HIPACKPHY_ACPHYCTL9_acposedge_cke1_END     (4)
#define SOC_HIPACKPHY_ACPHYCTL9_acposedge_odt1_START   (5)
#define SOC_HIPACKPHY_ACPHYCTL9_acposedge_odt1_END     (5)
#define SOC_HIPACKPHY_ACPHYCTL9_acdram1sel_cs1_START   (6)
#define SOC_HIPACKPHY_ACPHYCTL9_acdram1sel_cs1_END     (6)
#define SOC_HIPACKPHY_ACPHYCTL9_acdram1sel_cke1_START  (7)
#define SOC_HIPACKPHY_ACPHYCTL9_acdram1sel_cke1_END    (7)
#define SOC_HIPACKPHY_ACPHYCTL9_acdram1sel_odt1_START  (8)
#define SOC_HIPACKPHY_ACPHYCTL9_acdram1sel_odt1_END    (8)
#define SOC_HIPACKPHY_ACPHYCTL9_actiming2t_cs1_START   (9)
#define SOC_HIPACKPHY_ACPHYCTL9_actiming2t_cs1_END     (9)
#define SOC_HIPACKPHY_ACPHYCTL9_actiming2t_cke1_START  (10)
#define SOC_HIPACKPHY_ACPHYCTL9_actiming2t_cke1_END    (10)
#define SOC_HIPACKPHY_ACPHYCTL9_actiming2t_odt1_START  (11)
#define SOC_HIPACKPHY_ACPHYCTL9_actiming2t_odt1_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_CATSWAPINDEX_UNION
 �ṹ˵��  : CATSWAPINDEX �Ĵ����ṹ���塣��ַƫ����:0x01B8����ֵ:0x80000000�����:32
 �Ĵ���˵��: CA SWAP index register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cat_swap_index  : 4;  /* bit[0-3] : CAT SWAP index register.
                                                          The valid range (vr) is 0~8.
                                                          0 is for:
                                                           cat_swap_bl_sel[11:0]
                                                          1~8 are for:
                                                           {3'd0,cat_swap_dqsel[(vr*4+3)*5+:5],
                                                           3'd0,cat_swap_dqsel[(vr*4+2)*5+:5],
                                                           3'd0,cat_swap_dqsel[(vr*4+1)*5+:5],
                                                           3'd0,cat_swap_dqsel[(vr*4+0)*5+:5]} */
        unsigned int  reserved        : 27; /* bit[4-30]: -- */
        unsigned int  cat_swap_legacy : 1;  /* bit[31]  : cat_swap_legacy register.
                                                          1. Use legacy swap (default)
                                                          0. Use CATSWAPSEL re-mapping */
    } reg;
} SOC_HIPACKPHY_CATSWAPINDEX_UNION;
#endif
#define SOC_HIPACKPHY_CATSWAPINDEX_cat_swap_index_START   (0)
#define SOC_HIPACKPHY_CATSWAPINDEX_cat_swap_index_END     (3)
#define SOC_HIPACKPHY_CATSWAPINDEX_cat_swap_legacy_START  (31)
#define SOC_HIPACKPHY_CATSWAPINDEX_cat_swap_legacy_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_CATSWAPSEL_UNION
 �ṹ˵��  : CATSWAPSEL �Ĵ����ṹ���塣��ַƫ����:0x01BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CA SWAP select register, indexed by CATSWAPINDEX
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cat_swap_sel : 32; /* bit[0-31]: CAT SWAP select content.
                                                       The content is pointed by the CATSWAPINDEX. Please refer to the datasheet for detailed contents.
                                                       
                                                       cat_swap_blsel[N*3+:3]:
                                                        bytelane select (N=0~3), CAT need ony 32-bit phy_wlresult. This field is used to decide whiech 4-bytelane of phy_wlresult are used by CAT.
                                                       
                                                       cat_swap_dqsel[B*5+:5]:
                                                        dq select (B=0~32)
                                                       
                                                       Note: when CATSWAPINDEX select the non-defined content, the write will not take effect and the read will return the index 0 data. */
    } reg;
} SOC_HIPACKPHY_CATSWAPSEL_UNION;
#endif
#define SOC_HIPACKPHY_CATSWAPSEL_cat_swap_sel_START  (0)
#define SOC_HIPACKPHY_CATSWAPSEL_cat_swap_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_CATTIMER0_UNION
 �ṹ˵��  : CATTIMER0 �Ĵ����ṹ���塣��ַƫ����:0x01C0����ֵ:0x0B1E0B0B�����:32
 �Ĵ���˵��: CA Training Timer0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcackel  : 6;  /* bit[0-5]  : LPDDR3 - tCACKEL
                                                    LPDDR4 - this field is not used, PACK uses t_mod instead */
        unsigned int  reserved_0: 2;  /* bit[6-7]  : -- */
        unsigned int  tcaent   : 8;  /* bit[8-15] : tCAENT, unit is 2nCK. */
        unsigned int  tcacd    : 8;  /* bit[16-23]: tCACD */
        unsigned int  tcackeh  : 6;  /* bit[24-29]: LPDDR3 - tCACKEH
                                                    LPDDR4 - tCKCKEH */
        unsigned int  reserved_1: 2;  /* bit[30-31]: -- */
    } reg;
} SOC_HIPACKPHY_CATTIMER0_UNION;
#endif
#define SOC_HIPACKPHY_CATTIMER0_tcackel_START   (0)
#define SOC_HIPACKPHY_CATTIMER0_tcackel_END     (5)
#define SOC_HIPACKPHY_CATTIMER0_tcaent_START    (8)
#define SOC_HIPACKPHY_CATTIMER0_tcaent_END      (15)
#define SOC_HIPACKPHY_CATTIMER0_tcacd_START     (16)
#define SOC_HIPACKPHY_CATTIMER0_tcacd_END       (23)
#define SOC_HIPACKPHY_CATTIMER0_tcackeh_START   (24)
#define SOC_HIPACKPHY_CATTIMER0_tcackeh_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_CATTIMER1_UNION
 �ṹ˵��  : CATTIMER1 �Ĵ����ṹ���塣��ַƫ����:0x01C4����ֵ:0x0000040B�����:32
 �Ĵ���˵��: CA Training Timer1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcaext   : 8;  /* bit[0-7]  : tCAEXT, unit is 2nCK.
                                                    LPDDR3 - used as tCAEXT
                                                    LPDDR4 - used as tFC(Long) */
        unsigned int  tmrz     : 6;  /* bit[8-13] : tMRZ (dficlk cycle)
                                                    LPDDR3 - tMRZ
                                                    LPDDR4 - tCKEHDQS */
        unsigned int  reserved : 18; /* bit[14-31]: -- */
    } reg;
} SOC_HIPACKPHY_CATTIMER1_UNION;
#endif
#define SOC_HIPACKPHY_CATTIMER1_tcaext_START    (0)
#define SOC_HIPACKPHY_CATTIMER1_tcaext_END      (7)
#define SOC_HIPACKPHY_CATTIMER1_tmrz_START      (8)
#define SOC_HIPACKPHY_CATTIMER1_tmrz_END        (13)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_CATCONFIG_UNION
 �ṹ˵��  : CATCONFIG �Ĵ����ṹ���塣��ַƫ����:0x01C8����ֵ:0x001A2666�����:32
 �Ĵ���˵��: CA Training Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ca_samp_num_bdl   : 4;  /* bit[0-3]  : HW CA Training - sample count for CA BDL:
                                                             Valid value: 1~15 */
        unsigned int  ca_samp_num_ph    : 4;  /* bit[4-7]  : HW CA Training - sample count for CA phase:
                                                             Valid value: 1~15 */
        unsigned int  ca_trysamp_num    : 4;  /* bit[8-11] : HW CA Training - constrain the times of multi-sample count in deskew. User can enlarge the value or set to 0 to get more accuracy to data training.
                                                             0: disable trysamp_num constraint
                                                             Valid value: 1~15 (Unit: 4 times) */
        unsigned int  cat_rb_backtap    : 4;  /* bit[12-15]: HW CA Training Right Boundary back tap. This field is used to offset (-) the addrph_a before do the Right Boundary Search to overcome meta-stable zone. */
        unsigned int  sw_cat_eyet       : 1;  /* bit[16]   : SW CA Training - enable the CA Eye-train by HW, only valid when SW CAT in LPDDR4.
                                                             Before assert sw_cat_eyet the SW CAT should:
                                                             1. Enter the CAT mode first by issuing MR13 with OP[0]=0x1
                                                             2. Make CKE LOW
                                                             3. Set VREFCA by DQS[0]/DQ[6:0] */
        unsigned int  cat_openeye_en    : 1;  /* bit[17]   : HW CA Trainig - openeye enable
                                                             1: enable (default)
                                                             0: disable */
        unsigned int  cat_cat_phydq_sel : 1;  /* bit[18]   : HW CA Trainig - PHY DQ CA result selection:
                                                             1: MSB selected
                                                             0: LSB selected (default) */
        unsigned int  cat_restore_en    : 1;  /* bit[19]   : HW CA Trainig - restore enable. If set as HIGH, the CA train will restore the ca phase before 2nd CA train (mapping stage) starts. This field is recommended to set as HIGH.
                                                             1: enable (default)
                                                             0: disable */
        unsigned int  cat_lb_backtap    : 4;  /* bit[20-23]: HW CA Training Left Boundary back tap. This field is used to offset (-) the addrph_a before do the Left Boundary fine-tune Search to overcome meta-stable zone. */
        unsigned int  sw_cat_mrw42      : 1;  /* bit[24]   : SW CA Training, cleared by HW.
                                                             LPDDR3 - issue the MRW42 command
                                                             LPDDR4 - issue MR13 to exit CBT mode */
        unsigned int  sw_cat_mrw48      : 1;  /* bit[25]   : SW CA Training, , cleared by HW.
                                                             LPDDR3 - issue the MRW48 command
                                                             LPDDR4 - Set VREFCA by DQS[0]/DQ[6:0] */
        unsigned int  sw_cat_mrw41      : 1;  /* bit[26]   : SW CA Training, cleared by HW.
                                                             LPDDR3 - issue the MRW41 command
                                                             LPDDR4 - issue MR13 to enter CBT mode */
        unsigned int  sw_cat_strobe     : 1;  /* bit[27]   : SW CA Training - issue the predefined SW CA pattern, cleared by HW */
        unsigned int  sw_cat_cke_high   : 1;  /* bit[28]   : SW CA Training - request the CKE to be HIGH, cleared by HW */
        unsigned int  sw_cat_cke_low    : 1;  /* bit[29]   : SW CA Training - request the CKE to be LOW, cleared by HW */
        unsigned int  sw_cat_dqvalid    : 1;  /* bit[30]   : SW CA Training - indicate if the SW CAT egnine is ready to accept next SW CAT operation. This bit will be deasserted when any SW CAT operation is asserted. Then after the related timing is satisfied or operation is done, this bit will be asserted automatically to indicated it is ok to accept next operation.
                                                             1: valid
                                                             0: not valid
                                                             
                                                             Note:
                                                             1. This bit is valid to polling only when SW CAT operation is issued by SW.
                                                             2. SW CAT operations and realted timings are:
                                                             sw_cat_cke_low (tcaent)
                                                             sw_cat_cke_high (tcaext)
                                                             sw_cat_strobe (tcacd)
                                                             sw_cat_mrw* (tcackel)
                                                             sw_cat_eyet (waif for cat done - LP4 only) */
        unsigned int  sw_cat_en         : 1;  /* bit[31]   : SW CA Training - enable bit. Assert this bit, PACK will enter the SW CA Training state. After the SW CA Training is done, this bit should be de-assert by firmware.
                                                             1: enable
                                                             0: disable (default)
                                                             The following bits are valid only when sw_cat_en=0x1:
                                                             sw_cat_dqvalid
                                                             sw_cat_cke_low/high
                                                             sw_cat_mrw41/48/42
                                                             sw_cat_eyet */
    } reg;
} SOC_HIPACKPHY_CATCONFIG_UNION;
#endif
#define SOC_HIPACKPHY_CATCONFIG_ca_samp_num_bdl_START    (0)
#define SOC_HIPACKPHY_CATCONFIG_ca_samp_num_bdl_END      (3)
#define SOC_HIPACKPHY_CATCONFIG_ca_samp_num_ph_START     (4)
#define SOC_HIPACKPHY_CATCONFIG_ca_samp_num_ph_END       (7)
#define SOC_HIPACKPHY_CATCONFIG_ca_trysamp_num_START     (8)
#define SOC_HIPACKPHY_CATCONFIG_ca_trysamp_num_END       (11)
#define SOC_HIPACKPHY_CATCONFIG_cat_rb_backtap_START     (12)
#define SOC_HIPACKPHY_CATCONFIG_cat_rb_backtap_END       (15)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_eyet_START        (16)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_eyet_END          (16)
#define SOC_HIPACKPHY_CATCONFIG_cat_openeye_en_START     (17)
#define SOC_HIPACKPHY_CATCONFIG_cat_openeye_en_END       (17)
#define SOC_HIPACKPHY_CATCONFIG_cat_cat_phydq_sel_START  (18)
#define SOC_HIPACKPHY_CATCONFIG_cat_cat_phydq_sel_END    (18)
#define SOC_HIPACKPHY_CATCONFIG_cat_restore_en_START     (19)
#define SOC_HIPACKPHY_CATCONFIG_cat_restore_en_END       (19)
#define SOC_HIPACKPHY_CATCONFIG_cat_lb_backtap_START     (20)
#define SOC_HIPACKPHY_CATCONFIG_cat_lb_backtap_END       (23)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_mrw42_START       (24)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_mrw42_END         (24)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_mrw48_START       (25)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_mrw48_END         (25)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_mrw41_START       (26)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_mrw41_END         (26)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_strobe_START      (27)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_strobe_END        (27)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_cke_high_START    (28)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_cke_high_END      (28)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_cke_low_START     (29)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_cke_low_END       (29)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_dqvalid_START     (30)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_dqvalid_END       (30)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_en_START          (31)
#define SOC_HIPACKPHY_CATCONFIG_sw_cat_en_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_CATRESULT_UNION
 �ṹ˵��  : CATRESULT �Ĵ����ṹ���塣��ַƫ����:0x01CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CA Training result for debug
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cat_reault : 10; /* bit[0-9]  : CA Training - HW CA Training result for each address bit during each HW CA Trainig state. These bits are only meaningful after HW CA Training done and are only used for debug purpose.
                                                      1: OK
                                                      0: Failed */
        unsigned int  reserved   : 22; /* bit[10-31]: -- */
    } reg;
} SOC_HIPACKPHY_CATRESULT_UNION;
#endif
#define SOC_HIPACKPHY_CATRESULT_cat_reault_START  (0)
#define SOC_HIPACKPHY_CATRESULT_cat_reault_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_PHYDQRESULT_UNION
 �ṹ˵��  : PHYDQRESULT �Ĵ����ṹ���塣��ַƫ����:0x01D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW CA Training DQ result from PHY
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_dq_result : 32; /* bit[0-31]: SW CA Training - SW CA Training latched results from DRAM device.
                                                        For LPDDR3 CA Training, the meaningful bits are [15:0] (map to DQ[15:0]). PACK and PHY will not latch these bits, so these bits are what you get on the DRAM device's DQ. */
    } reg;
} SOC_HIPACKPHY_PHYDQRESULT_UNION;
#endif
#define SOC_HIPACKPHY_PHYDQRESULT_phy_dq_result_START  (0)
#define SOC_HIPACKPHY_PHYDQRESULT_phy_dq_result_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ADDRPHBOUND_UNION
 �ṹ˵��  : ADDRPHBOUND �Ĵ����ṹ���塣��ַƫ����:0x01D4����ֵ:0x00080000�����:32
 �Ĵ���˵��: CA Training addr phase boundary
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrph_a_right : 5;  /* bit[0-4]  : HW CA Training, these bits record the right boundary of addr phase after HW CA Traininig. (for debug purpose) */
        unsigned int  reserved_0     : 3;  /* bit[5-7]  : -- */
        unsigned int  addrph_a_left  : 5;  /* bit[8-12] : HW CA Training, these bits record the left boundary of addr phase after HW CA Traininig. (for debug purpose) */
        unsigned int  reserved_1     : 3;  /* bit[13-15]: -- */
        unsigned int  addrph_a       : 5;  /* bit[16-20]: HW CA Training, these bits record the left boundary of addr phase after HW CA Traininig. (for debug purpose) */
        unsigned int  reserved_2     : 3;  /* bit[21-23]: -- */
        unsigned int  addrph_a_ori   : 5;  /* bit[24-28]: HW CA Training, these bits record the addr phase before HW CA Traininig. (for debug purpose) */
        unsigned int  reserved_3     : 1;  /* bit[29]   : -- */
        unsigned int  cat_err        : 1;  /* bit[30]   : CAT error flag. Read only. */
        unsigned int  init_en        : 1;  /* bit[31]   : PHY Iinitialization enable. Read only.
                                                          1: busy
                                                          0: idle */
    } reg;
} SOC_HIPACKPHY_ADDRPHBOUND_UNION;
#endif
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_right_START  (0)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_right_END    (4)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_left_START   (8)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_left_END     (12)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_START        (16)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_END          (20)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_ori_START    (24)
#define SOC_HIPACKPHY_ADDRPHBOUND_addrph_a_ori_END      (28)
#define SOC_HIPACKPHY_ADDRPHBOUND_cat_err_START         (30)
#define SOC_HIPACKPHY_ADDRPHBOUND_cat_err_END           (30)
#define SOC_HIPACKPHY_ADDRPHBOUND_init_en_START         (31)
#define SOC_HIPACKPHY_ADDRPHBOUND_init_en_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_SWCATPATTERN_P_UNION
 �ṹ˵��  : SWCATPATTERN_P �Ĵ����ṹ���塣��ַƫ����:0x01D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW CA Training pattern for  positive CK edge
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw_cat_pat_p : 10; /* bit[0-9]  : SW CA Training pattern for positive CK edge.
                                                        Note:
                                                        This field should be set as 0x3FF in LPDDR4. User can fill any patterns in other dram types. */
        unsigned int  reserved     : 22; /* bit[10-31]: -- */
    } reg;
} SOC_HIPACKPHY_SWCATPATTERN_P_UNION;
#endif
#define SOC_HIPACKPHY_SWCATPATTERN_P_sw_cat_pat_p_START  (0)
#define SOC_HIPACKPHY_SWCATPATTERN_P_sw_cat_pat_p_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_SWCATPATTERN_N_UNION
 �ṹ˵��  : SWCATPATTERN_N �Ĵ����ṹ���塣��ַƫ����:0x01DC����ֵ:0x000003FF�����:32
 �Ĵ���˵��: SW CA Training pattern for  negative CK edge
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw_cat_pat_n : 10; /* bit[0-9]  : SW CA Training pattern for negative CK edge.
                                                        This field should be set as ~sw_cat_pat_p */
        unsigned int  reserved     : 22; /* bit[10-31]: -- */
    } reg;
} SOC_HIPACKPHY_SWCATPATTERN_N_UNION;
#endif
#define SOC_HIPACKPHY_SWCATPATTERN_N_sw_cat_pat_n_START  (0)
#define SOC_HIPACKPHY_SWCATPATTERN_N_sw_cat_pat_n_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_MRS_SEQ_PROG_UNION
 �ṹ˵��  : MRS_SEQ_PROG �Ĵ����ṹ���塣��ַƫ����:0x01E0����ֵ:0x00124563�����:32
 �Ĵ���˵��: Programmed MRS sequence in the DRAM initialization
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mrs_seq_prog : 32; /* bit[0-31]: Programmed MRS sequence in the DRAM initialization. This field is used when mrs_seq_prog_en=0x1. The default sequence is for DDR4 (issue MR3->MR6->MR5->MR4->MR2->MR1->MR0)
                                                       
                                                       The format is [n*4+:4], n is 0~7.
                                                       The issued order is n=0,1,2,��7.
                                                       DDR4:
                                                        valid n = 0~6,
                                                        valid [n*4+:4] is 3,6,5,4,2,1,0
                                                       DDR3: 
                                                        valid n = 0~3,
                                                        valid [n*4+:4] is 2,3,1,0
                                                       LPDDR2/3:
                                                        valid n = 5,
                                                        valid [n*4+:4] is 1,2,3,9,0xE(MR16),0xF(MR17) */
    } reg;
} SOC_HIPACKPHY_MRS_SEQ_PROG_UNION;
#endif
#define SOC_HIPACKPHY_MRS_SEQ_PROG_mrs_seq_prog_START  (0)
#define SOC_HIPACKPHY_MRS_SEQ_PROG_mrs_seq_prog_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_LPCTRL_UNION
 �ṹ˵��  : LPCTRL �Ĵ����ṹ���塣��ַƫ����:0x01E4����ֵ:0xFE808688�����:32
 �Ĵ���˵��: Low Power Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_dram_clk_enable          : 4;  /* bit[0-3]  : DFI DRAM clock enable timing parameter. This field will be use to count down before dram CK is turned-on. */
        unsigned int  t_dram_clk_disable         : 4;  /* bit[4-7]  : DFI DRAM clock disable timing parameter. This field will be use to count down before dram CK is turned-off. */
        unsigned int  t_wakeup_thrd_lv3          : 4;  /* bit[8-11] : DFI Low Power contorl interafce timing threhold,
                                                                      >= wakeup_thrd_lv2: PHY clock gating, disable AC output enable
                                                                      >= wakeup_thrd_lv3: PHY clock gating, disable AC output enable, PHY PLL power down
                                                                      Note: wakeup_thrd_lv3 should >= wakeup_thrd_lv2 */
        unsigned int  t_resp                     : 4;  /* bit[12-15]: DFI Low Power control interface timing parameter. Should be smaller than DFI's tlp_resp. */
        unsigned int  lp_pll_powerdown_disable   : 1;  /* bit[16]   : Disable LP PLL Disable function when Low-Power Assert.
                                                                      1: Turn-off the related LP funtion
                                                                      0: Turn-on the related LP funtion (default) */
        unsigned int  lp_dx_phy_phgated_disable  : 1;  /* bit[17]   : Disable DX PHY Clock Phase Gating function when Low-Power Assert.
                                                                      1: Turn-off the related LP funtion
                                                                      0: Turn-on the related LP funtion (default) */
        unsigned int  lp_dx_phy_clkgated_disable : 1;  /* bit[18]   : Disable LP DX PHY Clock Gating function when Low-Power Assert.
                                                                      1: Turn-off the related LP funtion
                                                                      0: Turn-on the related LP funtion (default) */
        unsigned int  lp_ac_phy_clkgated_disable : 1;  /* bit[19]   : Disable LP AC PHY Clock Gating function when Low-Power Asser.
                                                                      1: Turn-off the related LP funtion
                                                                      0: Turn-on the related LP funtion (default) */
        unsigned int  lp_cmdoen_disable          : 1;  /* bit[20]   : Disable the LP CMDOEN function when Low-Power Assert. If turn-on this function, the IO output of CA will be floating to save IO power.
                                                                      1: Turn-off the related LP funtion
                                                                      0: Turn-on the related LP funtion (default) */
        unsigned int  t_wakeup_thrd_lv2          : 4;  /* bit[21-24]: DFI Low Power contorl interafce timing threhold,
                                                                      >= wakeup_thrd_lv2: PHY clock gating, disable AC output enable
                                                                      >= wakeup_thrd_lv3: PHY clock gating, disable AC output enable, PHY PLL disalbe
                                                                      Note: wakeup_thrd_lv3 should >= wakeup_thrd_lv2 */
        unsigned int  gcken_dxbist               : 1;  /* bit[25]   : Manual gating control - DATA BIST clock gating.
                                                                      1: clock on (default)
                                                                      0: clock off
                                                                      The DATA BIST clock gating also affected by the "gcken_auto_en" and "gcken_dxbist" settings. Please see the descriptions in these registers. */
        unsigned int  gcken_acbist               : 1;  /* bit[26]   : Manual gating control - AC BIST clock gating.
                                                                      1: clock on (default)
                                                                      0: clock off
                                                                      The AC BIST clock gating also affected by the "gcken_auto_en" and "gcken_acbist" settings. Please see the descriptions in these registers. */
        unsigned int  gcken_retrain              : 1;  /* bit[27]   : Manual gating control - Re-training clock gating.
                                                                      1: clock on (default)
                                                                      0: clock off
                                                                      The Re-training clock gating also affected by the "gcken_auto_en" and "gcken_retrain" settings. Please see the descriptions in these registers. */
        unsigned int  gcken_dtrain               : 1;  /* bit[28]   : Manual gating control - DATA Training clock gating.
                                                                      1: clock on (default)
                                                                      0: clock off
                                                                      The DATA Training clock gating also affected by the "gcken_auto_en" and "gcken_dtrain" settings. Please see the descriptions in these registers. */
        unsigned int  gcken_dinit                : 1;  /* bit[29]   : Manual gating control - DRAM initialization clock gating.
                                                                      1: clock on (default)
                                                                      0: clock off
                                                                      The DRAM initialization clock gating also affected by the "gcken_auto_en" and "gcken_dfi_main" settings. Please see the descriptions in these registers. */
        unsigned int  gcken_dfi_main             : 1;  /* bit[30]   : Manual gating control - Main DFI clock gating switch .
                                                                      1: clock on (defalt)
                                                                      0: clock off
                                                                      When this field is set as LOW (clock off), it will gate all of internal registers except that interface with Memory Controller (DFI). If this register is set to a '0', the folliwng gating controls will be ignored, and clocks will be gated. */
        unsigned int  gcken_auto_en              : 1;  /* bit[31]   : Auto gated clock control enable. If this field is set as HIGH, HW will control, together with the manual control will combied to control the PACK high-level clock gating automatically/dynamically. If this register is set to a '1', the following gating control register combined with PACK hardware controls will be used to controls the clock gatings. If this regsiter is set to a '0', only the following gating control register will be used to control the clock gatings.
                                                                      1: on (default)
                                                                      0: off */
    } reg;
} SOC_HIPACKPHY_LPCTRL_UNION;
#endif
#define SOC_HIPACKPHY_LPCTRL_t_dram_clk_enable_START           (0)
#define SOC_HIPACKPHY_LPCTRL_t_dram_clk_enable_END             (3)
#define SOC_HIPACKPHY_LPCTRL_t_dram_clk_disable_START          (4)
#define SOC_HIPACKPHY_LPCTRL_t_dram_clk_disable_END            (7)
#define SOC_HIPACKPHY_LPCTRL_t_wakeup_thrd_lv3_START           (8)
#define SOC_HIPACKPHY_LPCTRL_t_wakeup_thrd_lv3_END             (11)
#define SOC_HIPACKPHY_LPCTRL_t_resp_START                      (12)
#define SOC_HIPACKPHY_LPCTRL_t_resp_END                        (15)
#define SOC_HIPACKPHY_LPCTRL_lp_pll_powerdown_disable_START    (16)
#define SOC_HIPACKPHY_LPCTRL_lp_pll_powerdown_disable_END      (16)
#define SOC_HIPACKPHY_LPCTRL_lp_dx_phy_phgated_disable_START   (17)
#define SOC_HIPACKPHY_LPCTRL_lp_dx_phy_phgated_disable_END     (17)
#define SOC_HIPACKPHY_LPCTRL_lp_dx_phy_clkgated_disable_START  (18)
#define SOC_HIPACKPHY_LPCTRL_lp_dx_phy_clkgated_disable_END    (18)
#define SOC_HIPACKPHY_LPCTRL_lp_ac_phy_clkgated_disable_START  (19)
#define SOC_HIPACKPHY_LPCTRL_lp_ac_phy_clkgated_disable_END    (19)
#define SOC_HIPACKPHY_LPCTRL_lp_cmdoen_disable_START           (20)
#define SOC_HIPACKPHY_LPCTRL_lp_cmdoen_disable_END             (20)
#define SOC_HIPACKPHY_LPCTRL_t_wakeup_thrd_lv2_START           (21)
#define SOC_HIPACKPHY_LPCTRL_t_wakeup_thrd_lv2_END             (24)
#define SOC_HIPACKPHY_LPCTRL_gcken_dxbist_START                (25)
#define SOC_HIPACKPHY_LPCTRL_gcken_dxbist_END                  (25)
#define SOC_HIPACKPHY_LPCTRL_gcken_acbist_START                (26)
#define SOC_HIPACKPHY_LPCTRL_gcken_acbist_END                  (26)
#define SOC_HIPACKPHY_LPCTRL_gcken_retrain_START               (27)
#define SOC_HIPACKPHY_LPCTRL_gcken_retrain_END                 (27)
#define SOC_HIPACKPHY_LPCTRL_gcken_dtrain_START                (28)
#define SOC_HIPACKPHY_LPCTRL_gcken_dtrain_END                  (28)
#define SOC_HIPACKPHY_LPCTRL_gcken_dinit_START                 (29)
#define SOC_HIPACKPHY_LPCTRL_gcken_dinit_END                   (29)
#define SOC_HIPACKPHY_LPCTRL_gcken_dfi_main_START              (30)
#define SOC_HIPACKPHY_LPCTRL_gcken_dfi_main_END                (30)
#define SOC_HIPACKPHY_LPCTRL_gcken_auto_en_START               (31)
#define SOC_HIPACKPHY_LPCTRL_gcken_auto_en_END                 (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYCTL10_UNION
 �ṹ˵��  : ACPHYCTL10 �Ĵ����ṹ���塣��ַƫ����:0x1E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk1x_dramclk0_byt1 : 3;  /* bit[0-2]  : PHY control registers.
                                                               Move to AC_Static_Reg */
        unsigned int  clk1x_dramclk1_byt1 : 3;  /* bit[3-5]  : PHY control registers.
                                                               Move to AC_Static_Reg */
        unsigned int  clk1x_cmd2t_byt1    : 3;  /* bit[6-8]  : PHY control registers.
                                                               Move to AC_Static_Reg */
        unsigned int  clk1x_cmd1t_byt1    : 3;  /* bit[9-11] : PHY control registers.
                                                               Move to AC_Static_Reg */
        unsigned int  clk1x_mclk_byt1     : 3;  /* bit[12-14]: PHY control registers.
                                                               Move to AC_Static_Reg */
        unsigned int  reserved_0          : 1;  /* bit[15]   :  */
        unsigned int  clk2x_dramclk0_byt1 : 3;  /* bit[16-18]: PHY control registers.
                                                               Move to AC_Static_Reg */
        unsigned int  clk2x_dramclk1_byt1 : 3;  /* bit[19-21]: PHY control registers.
                                                               Move to AC_Static_Reg */
        unsigned int  clk2x_cmd2t_byt1    : 3;  /* bit[22-24]: PHY control registers.
                                                               Move to AC_Static_Reg */
        unsigned int  clk2x_cmd1t_byt1    : 3;  /* bit[25-27]: PHY control registers.
                                                               Move to AC_Static_Reg */
        unsigned int  clk2x_mclk_byt1     : 3;  /* bit[28-30]: PHY control registers.
                                                               Move to AC_Static_Reg */
        unsigned int  reserved_1          : 1;  /* bit[31]   : -- */
    } reg;
} SOC_HIPACKPHY_ACPHYCTL10_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_dramclk0_byt1_START  (0)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_dramclk0_byt1_END    (2)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_dramclk1_byt1_START  (3)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_dramclk1_byt1_END    (5)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_cmd2t_byt1_START     (6)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_cmd2t_byt1_END       (8)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_cmd1t_byt1_START     (9)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_cmd1t_byt1_END       (11)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_mclk_byt1_START      (12)
#define SOC_HIPACKPHY_ACPHYCTL10_clk1x_mclk_byt1_END        (14)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_dramclk0_byt1_START  (16)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_dramclk0_byt1_END    (18)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_dramclk1_byt1_START  (19)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_dramclk1_byt1_END    (21)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_cmd2t_byt1_START     (22)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_cmd2t_byt1_END       (24)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_cmd1t_byt1_START     (25)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_cmd1t_byt1_END       (27)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_mclk_byt1_START      (28)
#define SOC_HIPACKPHY_ACPHYCTL10_clk2x_mclk_byt1_END        (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ACPHYCTL11_UNION
 �ṹ˵��  : ACPHYCTL11 �Ĵ����ṹ���塣��ַƫ����:0x1EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck1p_dclk0_byt1         : 3;  /* bit[0-2]  : Byte 1 DRAM CK0 Clock Phase from PLL 1
                                                                   Move to AC_Static_Reg */
        unsigned int  ck2p_dclk1_byt1         : 3;  /* bit[3-5]  : Byte 1 DRAM CK1 Clock Phase from PLL 1
                                                                   Move to AC_Static_Reg */
        unsigned int  ck3p_cmd1t_byt1         : 3;  /* bit[6-8]  : Byte 1
                                                                   Move to AC_Static_Reg */
        unsigned int  ck4p_cmd2t_byt1         : 3;  /* bit[9-11] : Byte 1 CA Phase
                                                                   Move to AC_Static_Reg */
        unsigned int  reserved_0              : 11; /* bit[12-22]:  */
        unsigned int  ac_reg_byone_cmdr1t_sel : 1;  /* bit[23]   : Move to AC_Static_Reg */
        unsigned int  ac_reg_cmd_byt1_phsel   : 4;  /* bit[24-27]: Move to AC_Static_Reg */
        unsigned int  reserved_1              : 4;  /* bit[28-31]: -- */
    } reg;
} SOC_HIPACKPHY_ACPHYCTL11_UNION;
#endif
#define SOC_HIPACKPHY_ACPHYCTL11_ck1p_dclk0_byt1_START          (0)
#define SOC_HIPACKPHY_ACPHYCTL11_ck1p_dclk0_byt1_END            (2)
#define SOC_HIPACKPHY_ACPHYCTL11_ck2p_dclk1_byt1_START          (3)
#define SOC_HIPACKPHY_ACPHYCTL11_ck2p_dclk1_byt1_END            (5)
#define SOC_HIPACKPHY_ACPHYCTL11_ck3p_cmd1t_byt1_START          (6)
#define SOC_HIPACKPHY_ACPHYCTL11_ck3p_cmd1t_byt1_END            (8)
#define SOC_HIPACKPHY_ACPHYCTL11_ck4p_cmd2t_byt1_START          (9)
#define SOC_HIPACKPHY_ACPHYCTL11_ck4p_cmd2t_byt1_END            (11)
#define SOC_HIPACKPHY_ACPHYCTL11_ac_reg_byone_cmdr1t_sel_START  (23)
#define SOC_HIPACKPHY_ACPHYCTL11_ac_reg_byone_cmdr1t_sel_END    (23)
#define SOC_HIPACKPHY_ACPHYCTL11_ac_reg_cmd_byt1_phsel_START    (24)
#define SOC_HIPACKPHY_ACPHYCTL11_ac_reg_cmd_byt1_phsel_END      (27)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AHVREFT_STATUS_UNION
 �ṹ˵��  : AHVREFT_STATUS �Ĵ����ṹ���塣��ַƫ����:0x1F0����ֵ:0x00000008�����:32
 �Ĵ���˵��: Host PHY VREF(AC) Training Result. This register shows the training result of the Host PHY VREF(AC) training.
            This register is only valid while the application is LPDDR4.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vrftres_ahvref    : 6;  /* bit[0-5]  : Host PHY VREF(AC) Control Value.
                                                             This field is used to control the host PHY VREF. If the Host PHY VREF(AC) training is enabled to execute, this field will be updated to the training results.
                                                             The MSB of this field only valid while the application is LPDDR4. For ohter application, the MSB of this field should be kept as 1'b0. */
        unsigned int  vrftres_ahvref_lb : 6;  /* bit[6-11] : Host PHY VREF(AC) Training Lower Boundary.
                                                             This field shows the results of lower boundary of the host PHY VREF(AC) training.
                                                             The MSB of this field only valid while the application is LPDDR4. For ohter application, the MSB of this field is don't care. */
        unsigned int  vrftres_ahvref_ub : 6;  /* bit[12-17]: Host PHY VREF(AC) Training Upper Boundary.
                                                             This field shows the results of upper boundary of the host PHY VREF(AC) training.
                                                             The MSB of this field only valid while the application is LPDDR4. For ohter application, the MSB of this field is don't care. */
        unsigned int  reserved          : 14; /* bit[18-31]: -- */
    } reg;
} SOC_HIPACKPHY_AHVREFT_STATUS_UNION;
#endif
#define SOC_HIPACKPHY_AHVREFT_STATUS_vrftres_ahvref_START     (0)
#define SOC_HIPACKPHY_AHVREFT_STATUS_vrftres_ahvref_END       (5)
#define SOC_HIPACKPHY_AHVREFT_STATUS_vrftres_ahvref_lb_START  (6)
#define SOC_HIPACKPHY_AHVREFT_STATUS_vrftres_ahvref_lb_END    (11)
#define SOC_HIPACKPHY_AHVREFT_STATUS_vrftres_ahvref_ub_START  (12)
#define SOC_HIPACKPHY_AHVREFT_STATUS_vrftres_ahvref_ub_END    (17)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_ADVREF_STATUS_UNION
 �ṹ˵��  : ADVREF_STATUS �Ĵ����ṹ���塣��ַƫ����:0x1F4����ֵ:0x00000019�����:32
 �Ĵ���˵��: DRAM VREF(AC) Training Result. This register shows the training result of the DRAM VREF(DQ) training.
            This register is only valid while the application is LPDDR4.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ac_vrftres_dvref      : 6;  /* bit[0-5]  : DRAM VREF(AC) Training Result
                                                                 This field shows the DRAM VREF settings.
                                                                 Before DRAM VREF training, this value will be used as the initial value of VREF(AC) training, and after training, this value shows the final training result.
                                                                 If DRAM VREF(AC) value after training need to be modified, the user has to do VREF(AC) synchronization operations after writing to this register. */
        unsigned int  ac_vrftres_dvref_lb   : 6;  /* bit[6-11] : DRAM VREF(AC) Training Lower Boundary.
                                                                 This field shows the lower boundary of VREF(AC) value during VREF(AC) training.  */
        unsigned int  ac_vrftres_dvref_ub   : 6;  /* bit[12-17]: DRAM VREF(AC) Training Upper Boundary.
                                                                 This field shows the upper boundary of VREF(AC) value during VREF(AC) training.  */
        unsigned int  ac_vrftres_dlb_status : 3;  /* bit[18-20]: DRAM VREF(AC) Training Status (Lower Boundary)
                                                                 This field shows the training status of lower boundary of VREF training. These three bits represents the CAT results of horizontal check points. If the bit is set to a '1', the CAT results contains errors. If the bit is '0', it indicate that the corresponding bit is not checked or CAT succeed.
                                                                 ac_vrftres_dlb_status[0] : Status of original delays.
                                                                 ac_vrftres_dlb_status[1] : Status of +delta delays.
                                                                 ac_vrftres_dlb_status[0] : Status of -delta delays. */
        unsigned int  ac_vrftres_dub_status : 3;  /* bit[21-23]: DRAM VREF(AC) Training Status (Upper Boundary)
                                                                 This field shows the training status of upper boundary of AC VREF training. These three bits represents the CAT results of horizontal check points. If the bit is set to a '1', the CAT results contains errors. If the bit is '0', it indicate that the corresponding bit is not checked or CAT succeed.
                                                                 ac_vrftres_dub_status[0] : Status of original delays.
                                                                 ac_vrftres_dub_status[1] : Status of +delta delays.
                                                                 ac_vrftres_dub_status[0] : Status of -delta delays. */
        unsigned int  reserved              : 7;  /* bit[24-30]: -- */
        unsigned int  ac_vreftres_set_type  : 1;  /* bit[31]   : DRAM VREF(AC) Value Set Type.
                                                                 This field controls the type of the DRAM VREF(AC) value assignment to DRAM.
                                                                 If this field is set to a 0, a normal mode register write was trigger to MR2.
                                                                 If this field is set to a '1', the DRAM VREF(AC) set process as specified in the CBT (Command Bus Training) was execute to assign the VREF(AC) value to DRAM. Note that this type can only be selected if currently the DRAM is in CBT mode. */
    } reg;
} SOC_HIPACKPHY_ADVREF_STATUS_UNION;
#endif
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dvref_START       (0)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dvref_END         (5)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dvref_lb_START    (6)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dvref_lb_END      (11)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dvref_ub_START    (12)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dvref_ub_END      (17)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dlb_status_START  (18)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dlb_status_END    (20)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dub_status_START  (21)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vrftres_dub_status_END    (23)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vreftres_set_type_START   (31)
#define SOC_HIPACKPHY_ADVREF_STATUS_ac_vreftres_set_type_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DFIMISCCTRL_UNION
 �ṹ˵��  : DFIMISCCTRL �Ĵ����ṹ���塣��ַƫ����:0x1FC����ֵ:0xC0000008�����:32
 �Ĵ���˵��: DFI MISC control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_lpwakeup_fg     : 5;  /* bit[0-4] : DFI LP wakeup time for fine-grain. This field is used instead of the fixed 16 cyeles defined in DFI specification when the mc_lp_wakeup issued by MC is zero. */
        unsigned int  reserved          : 25; /* bit[5-29]: -- */
        unsigned int  gcken_apb_ctrlreg : 1;  /* bit[30]  : Manual gating control - HIPACK_CTRLREG APB clock gating.
                                                            1: clock on (default)
                                                            0: clock off
                                                            Note that if gcken_apb_ctrlreg=0x0, the HIPACK_CTRLREG APB clock is truned off even gcken_apb_auto_en=0x1. */
        unsigned int  gcken_apb_auto_en : 1;  /* bit[31]  : APB automatic gating control enable. (HIPACK_CTRLREG APB clock gating)
                                                            1: enable (default)
                                                            0: disable (manual control) */
    } reg;
} SOC_HIPACKPHY_DFIMISCCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DFIMISCCTRL_t_lpwakeup_fg_START      (0)
#define SOC_HIPACKPHY_DFIMISCCTRL_t_lpwakeup_fg_END        (4)
#define SOC_HIPACKPHY_DFIMISCCTRL_gcken_apb_ctrlreg_START  (30)
#define SOC_HIPACKPHY_DFIMISCCTRL_gcken_apb_ctrlreg_END    (30)
#define SOC_HIPACKPHY_DFIMISCCTRL_gcken_apb_auto_en_START  (31)
#define SOC_HIPACKPHY_DFIMISCCTRL_gcken_apb_auto_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNBISTCTRL_UNION
 �ṹ˵��  : DXNBISTCTRL �Ĵ����ṹ���塣��ַƫ����:0x200+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to control if the loopback data is compre during BIST of Data Blocks.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bist_en      : 1;  /* bit[0]    : Bist Enable.
                                                        This signal specify if the Data block is included for DX BIST/loopback test while bist_op is set to BIST Enable.
                                                        Note in the Data loopback mode, the BL (Burst Length) should be set as 8 by setting MODEREG01.mr0 properly. */
        unsigned int  reserved_0   : 7;  /* bit[1-7]  : -- */
        unsigned int  dq_cmp_mask  : 8;  /* bit[8-15] : DQ DX BIST/Loopback Compare Mask.
                                                        This field is used to control if the comparison of the loopback data on DQ bits are disabled. 
                                                        0: Not compare 
                                                        1: Compare */
        unsigned int  dqm_cmp_mask : 1;  /* bit[16]   : DQM Loopback Compare Mask.
                                                        This field is used to control if the comparison of the loopback data on DQM bits are disabled. 
                                                        0: Not compare 
                                                        1: Compare */
        unsigned int  prbs_mode    : 2;  /* bit[17-18]: PRBS mode select.
                                                        00:PRBS16
                                                        01:PRBS11
                                                        10:PRBS4 
                                                        11: Reserved */
        unsigned int  reserved_1   : 5;  /* bit[19-23]: -- */
        unsigned int  lfsr_seed    : 8;  /* bit[24-31]: LFSR Seed Value.
                                                        This field is uesed to specify the initial seed value of the LFSR generator to this byte lane.
                                                        If the PRBS4 mode was selected, the lower part (bit 0 to 3) of this register specified the initial seed of the PRBS. The higher part (bit 4 to 6) specify the index of starting inversed bit. */
    } reg;
} SOC_HIPACKPHY_DXNBISTCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DXNBISTCTRL_bist_en_START       (0)
#define SOC_HIPACKPHY_DXNBISTCTRL_bist_en_END         (0)
#define SOC_HIPACKPHY_DXNBISTCTRL_dq_cmp_mask_START   (8)
#define SOC_HIPACKPHY_DXNBISTCTRL_dq_cmp_mask_END     (15)
#define SOC_HIPACKPHY_DXNBISTCTRL_dqm_cmp_mask_START  (16)
#define SOC_HIPACKPHY_DXNBISTCTRL_dqm_cmp_mask_END    (16)
#define SOC_HIPACKPHY_DXNBISTCTRL_prbs_mode_START     (17)
#define SOC_HIPACKPHY_DXNBISTCTRL_prbs_mode_END       (18)
#define SOC_HIPACKPHY_DXNBISTCTRL_lfsr_seed_START     (24)
#define SOC_HIPACKPHY_DXNBISTCTRL_lfsr_seed_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNBISTSTS_UNION
 �ṹ˵��  : DXNBISTSTS �Ĵ����ṹ���塣��ַƫ����:0x204+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register shows the results and status of the BIST test. Please note that this register is read-only, and can only be reset by bist_op setting to BIST Reset.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dq_cmp_rerr : 8;  /* bit[0-7]  : BIST Error on DQ at rising edge of DQS */
        unsigned int  dq_cmp_ferr : 8;  /* bit[8-15] : BIST Error on DQ at falling edge of DQS. */
        unsigned int  dqm_cmp_err : 1;  /* bit[16]   : BIST Error on DQM. */
        unsigned int  reserved    : 15; /* bit[17-31]: -- */
    } reg;
} SOC_HIPACKPHY_DXNBISTSTS_UNION;
#endif
#define SOC_HIPACKPHY_DXNBISTSTS_dq_cmp_rerr_START  (0)
#define SOC_HIPACKPHY_DXNBISTSTS_dq_cmp_rerr_END    (7)
#define SOC_HIPACKPHY_DXNBISTSTS_dq_cmp_ferr_START  (8)
#define SOC_HIPACKPHY_DXNBISTSTS_dq_cmp_ferr_END    (15)
#define SOC_HIPACKPHY_DXNBISTSTS_dqm_cmp_err_START  (16)
#define SOC_HIPACKPHY_DXNBISTSTS_dqm_cmp_err_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNCTRL_UNION
 �ṹ˵��  : DXNCTRL �Ĵ����ṹ���塣��ַƫ����:0x208+(n)*0x80����ֵ:0x00F80000�����:32
 �Ĵ���˵��: This register is used to control Data Block
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bl_dis         : 1;  /* bit[0]    : Byte Lane Disable. 
                                                          This field specify if the corresponding byte lane is in use. If the corresponding byte lane is not used, the PLL/DDL will be power down, and the output driver will be turn off. */
        unsigned int  dm_dis         : 1;  /* bit[1]    : Data mask disable.
                                                          This field specify if the corresponding write data mask (DM) is enabled or not. When this field is set to 1, the corresponding DM is not used and calibrated while performing training opreation. */
        unsigned int  reserved_0     : 5;  /* bit[2-6]  : -- */
        unsigned int  gck_dbi_autoen : 1;  /* bit[7]    : Dynamic Stop Clock Enable for DBI Generation Module
                                                          1: Enable Dynamic Stop Clock
                                                          0: Free-Run Clock
                                                          ----------------------------------------
                                                          [NOTE]
                                                          When Change DFI Command Bus, Need to Set gck_dbi_autoen==1'b0 to Make Clock Free Run to Sync PACK Internal Register with DFI Command Bus, such as Make CKE Low when PLL Lock when DFS.
                                                          [Exception Condition]
                                                          The Following Configuration ***Do Not*** Have this Limitation (Always Make gck_dbi_autoen On)
                                                          1. MC DBI Mode & MPC for WDET
                                                          2. PACK DBI Mode & Normal R/W forWDET */
        unsigned int  dbi_write_mode : 2;  /* bit[8-9]  : Write DBI algorithm
                                                          0��Base 0 algorithm,decrease the number of Low Levle in one bytelane.
                                                          1��Base 1 algorithm,decrease the number of High Level in one bytelane
                                                          2��AC algorithm,decrease the number of Roll Over in one bytelane
                                                          3��reserved */
        unsigned int  dbi_read_en    : 2;  /* bit[10-11]: This field must be 0 in DDR3 mode.
                                                          0��No read DBI function
                                                          1��MC execute ReadData Inversion
                                                          2��PACK execute ReadData Inversion
                                                          3��reserved */
        unsigned int  dbi_write_en   : 2;  /* bit[12-13]: This field must be 0 in DDR3 mode,and must be 0 before Training Done in DDR4 mode.
                                                          0:No Write DBI function 
                                                          1:MC support DBI signal
                                                          2:PACK generate DBI signal
                                                          3:Reserved */
        unsigned int  dbi_polarity   : 1;  /* bit[14]   : DBI Polarity for RDBI & WDBI
                                                          0: DBI==0 Invert Data (Used for DDR4)
                                                          1: DBI==1 Invert Data (Used for LPDDR4) */
        unsigned int  wdbi_mask_en   : 1;  /* bit[15]   : LPDDR4 Mask Write Data Generation when WDBI Enable
                                                          1: Mask Write Data Generation when WDBI Enable */
        unsigned int  wdbi_mask_data : 8;  /* bit[16-23]: LPDDR4 Mask Write Data Pattern when WDBI Enable
                                                          Spec: [7:2] Must Have the Number of 1'b1 >= 5 */
        unsigned int  reserved_1     : 8;  /* bit[24-31]: -- */
    } reg;
} SOC_HIPACKPHY_DXNCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DXNCTRL_bl_dis_START          (0)
#define SOC_HIPACKPHY_DXNCTRL_bl_dis_END            (0)
#define SOC_HIPACKPHY_DXNCTRL_dm_dis_START          (1)
#define SOC_HIPACKPHY_DXNCTRL_dm_dis_END            (1)
#define SOC_HIPACKPHY_DXNCTRL_gck_dbi_autoen_START  (7)
#define SOC_HIPACKPHY_DXNCTRL_gck_dbi_autoen_END    (7)
#define SOC_HIPACKPHY_DXNCTRL_dbi_write_mode_START  (8)
#define SOC_HIPACKPHY_DXNCTRL_dbi_write_mode_END    (9)
#define SOC_HIPACKPHY_DXNCTRL_dbi_read_en_START     (10)
#define SOC_HIPACKPHY_DXNCTRL_dbi_read_en_END       (11)
#define SOC_HIPACKPHY_DXNCTRL_dbi_write_en_START    (12)
#define SOC_HIPACKPHY_DXNCTRL_dbi_write_en_END      (13)
#define SOC_HIPACKPHY_DXNCTRL_dbi_polarity_START    (14)
#define SOC_HIPACKPHY_DXNCTRL_dbi_polarity_END      (14)
#define SOC_HIPACKPHY_DXNCTRL_wdbi_mask_en_START    (15)
#define SOC_HIPACKPHY_DXNCTRL_wdbi_mask_en_END      (15)
#define SOC_HIPACKPHY_DXNCTRL_wdbi_mask_data_START  (16)
#define SOC_HIPACKPHY_DXNCTRL_wdbi_mask_data_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNWDQNBDL0_UNION
 �ṹ˵��  : DXNWDQNBDL0 �Ĵ����ṹ���塣��ַƫ����:0x210+(m)*0x400+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to control the bit delay line of the DATA block.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdq0bdl  : 7;  /* bit[0-6]  : Delay Select of WDQ0.
                                                    This field specify the delay value of the bit delay line on write path of DQ0. */
        unsigned int  reserved_0: 1;  /* bit[7]    : -- */
        unsigned int  wdq1bdl  : 7;  /* bit[8-14] : Delay Select of WDQ1.
                                                    This field specify the delay value of the bit delay line on write path of DQ1. */
        unsigned int  reserved_1: 1;  /* bit[15]   : -- */
        unsigned int  wdq2bdl  : 7;  /* bit[16-22]: Delay Select of WDQ2.
                                                    This field specify the delay value of the bit delay line on write path of DQ2. */
        unsigned int  reserved_2: 1;  /* bit[23]   : -- */
        unsigned int  wdq3bdl  : 7;  /* bit[24-30]: Delay Select of WDQ3.
                                                    This field specify the delay value of the bit delay line on write path of DQ3. */
        unsigned int  reserved_3: 1;  /* bit[31]   : -- */
    } reg;
} SOC_HIPACKPHY_DXNWDQNBDL0_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq0bdl_START   (0)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq0bdl_END     (6)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq1bdl_START   (8)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq1bdl_END     (14)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq2bdl_START   (16)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq2bdl_END     (22)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq3bdl_START   (24)
#define SOC_HIPACKPHY_DXNWDQNBDL0_wdq3bdl_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNWDQNBDL1_UNION
 �ṹ˵��  : DXNWDQNBDL1 �Ĵ����ṹ���塣��ַƫ����:0x214+(m)*0x400+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to control the bit delay line of the DATA block.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdq4bdl  : 7;  /* bit[0-6]  : Delay Select of WDQ4.
                                                    This field specify the delay value of the bit delay line on write path of DQ0. */
        unsigned int  reserved_0: 1;  /* bit[7]    : -- */
        unsigned int  wdq5bdl  : 7;  /* bit[8-14] : Delay Select of WDQ5.
                                                    This field specify the delay value of the bit delay line on write path of DQ1. */
        unsigned int  reserved_1: 1;  /* bit[15]   : -- */
        unsigned int  wdq6bdl  : 7;  /* bit[16-22]: Delay Select of WDQ6.
                                                    This field specify the delay value of the bit delay line on write path of DQ2. */
        unsigned int  reserved_2: 1;  /* bit[23]   : -- */
        unsigned int  wdq7bdl  : 7;  /* bit[24-30]: Delay Select of WDQ7.
                                                    This field specify the delay value of the bit delay line on write path of DQ3. */
        unsigned int  reserved_3: 1;  /* bit[31]   :  */
    } reg;
} SOC_HIPACKPHY_DXNWDQNBDL1_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq4bdl_START   (0)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq4bdl_END     (6)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq5bdl_START   (8)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq5bdl_END     (14)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq6bdl_START   (16)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq6bdl_END     (22)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq7bdl_START   (24)
#define SOC_HIPACKPHY_DXNWDQNBDL1_wdq7bdl_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNWDQNBDL2_UNION
 �ṹ˵��  : DXNWDQNBDL2 �Ĵ����ṹ���塣��ַƫ����:0x218+(m)*0x400+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to control the bit delay line of the DATA block.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdmbdl   : 7;  /* bit[0-6] : Delay Select of WDQM.
                                                   This field specify the delay value of the bit delay line on DQM. */
        unsigned int  reserved : 25; /* bit[7-31]:  */
    } reg;
} SOC_HIPACKPHY_DXNWDQNBDL2_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQNBDL2_wdmbdl_START    (0)
#define SOC_HIPACKPHY_DXNWDQNBDL2_wdmbdl_END      (6)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNRDQNBDL0_UNION
 �ṹ˵��  : DXNRDQNBDL0 �Ĵ����ṹ���塣��ַƫ����:0x21C+(l)*0x800+(m)*0x400+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to control the bit delay line of the DATA block.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdq0bdl  : 7;  /* bit[0-6]  : Delay Select of RDQ0.
                                                    This field specify the delay value of the bit delay line on write path of DQ0. */
        unsigned int  reserved_0: 1;  /* bit[7]    : -- */
        unsigned int  rdq1bdl  : 7;  /* bit[8-14] : Delay Select of RDQ1.
                                                    This field specify the delay value of the bit delay line on write path of DQ1. */
        unsigned int  reserved_1: 1;  /* bit[15]   : -- */
        unsigned int  rdq2bdl  : 7;  /* bit[16-22]: Delay Select of RDQ2.
                                                    This field specify the delay value of the bit delay line on write path of DQ2. */
        unsigned int  reserved_2: 1;  /* bit[23]   : -- */
        unsigned int  rdq3bdl  : 7;  /* bit[24-30]: Delay Select of RDQ3.
                                                    This field specify the delay value of the bit delay line on write path of DQ3. */
        unsigned int  reserved_3: 1;  /* bit[31]   : -- */
    } reg;
} SOC_HIPACKPHY_DXNRDQNBDL0_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq0bdl_START   (0)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq0bdl_END     (6)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq1bdl_START   (8)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq1bdl_END     (14)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq2bdl_START   (16)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq2bdl_END     (22)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq3bdl_START   (24)
#define SOC_HIPACKPHY_DXNRDQNBDL0_rdq3bdl_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNRDQNBDL1_UNION
 �ṹ˵��  : DXNRDQNBDL1 �Ĵ����ṹ���塣��ַƫ����:0x220+(l)*0x800+(m)*0x400+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to control the bit delay line of the DATA block.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdq4bdl  : 7;  /* bit[0-6]  : Delay Select of RDQ4.
                                                    This field specify the delay value of the bit delay line on write path of DQ0. */
        unsigned int  reserved_0: 1;  /* bit[7]    : -- */
        unsigned int  rdq5bdl  : 7;  /* bit[8-14] : Delay Select of RDQ5.
                                                    This field specify the delay value of the bit delay line on write path of DQ1. */
        unsigned int  reserved_1: 1;  /* bit[15]   : -- */
        unsigned int  rdq6bdl  : 7;  /* bit[16-22]: Delay Select of RDQ6.
                                                    This field specify the delay value of the bit delay line on write path of DQ2. */
        unsigned int  reserved_2: 1;  /* bit[23]   : -- */
        unsigned int  rdq7bdl  : 7;  /* bit[24-30]: Delay Select of RDQ7.
                                                    This field specify the delay value of the bit delay line on write path of DQ3. */
        unsigned int  reserved_3: 1;  /* bit[31]   : -- */
    } reg;
} SOC_HIPACKPHY_DXNRDQNBDL1_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq4bdl_START   (0)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq4bdl_END     (6)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq5bdl_START   (8)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq5bdl_END     (14)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq6bdl_START   (16)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq6bdl_END     (22)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq7bdl_START   (24)
#define SOC_HIPACKPHY_DXNRDQNBDL1_rdq7bdl_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNRDQNBDL2_UNION
 �ṹ˵��  : DXNRDQNBDL2 �Ĵ����ṹ���塣��ַƫ����:0x224+(l)*0x800+(m)*0x400+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to control the bit delay line of the DATA block.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdmbdl   : 7;  /* bit[0-6] : Delay Select of RDQM.
                                                   This field specify the delay value of the bit delay line on loopback read path of DQM. */
        unsigned int  reserved : 25; /* bit[7-31]:  */
    } reg;
} SOC_HIPACKPHY_DXNRDQNBDL2_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDQNBDL2_rdmbdl_START    (0)
#define SOC_HIPACKPHY_DXNRDQNBDL2_rdmbdl_END      (6)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNOEBDL_UNION
 �ṹ˵��  : DXNOEBDL �Ĵ����ṹ���塣��ַƫ����:0x228+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: Output Enable Delay Line Control. This register specify the dely line value of the output enable delay line within PHY data block.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  oen_bdl    : 7;  /* bit[0-6]  : DQ Output Enable Delay Control. */
        unsigned int  reserved_0 : 9;  /* bit[7-15] : --- */
        unsigned int  wdqsoe_bdl : 7;  /* bit[16-22]: Write DQS Output Enable Delay Control. */
        unsigned int  reserved_1 : 9;  /* bit[23-31]: --- */
    } reg;
} SOC_HIPACKPHY_DXNOEBDL_UNION;
#endif
#define SOC_HIPACKPHY_DXNOEBDL_oen_bdl_START     (0)
#define SOC_HIPACKPHY_DXNOEBDL_oen_bdl_END       (6)
#define SOC_HIPACKPHY_DXNOEBDL_wdqsoe_bdl_START  (16)
#define SOC_HIPACKPHY_DXNOEBDL_wdqsoe_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNRDQSDLY_UNION
 �ṹ˵��  : DXNRDQSDLY �Ĵ����ṹ���塣��ַƫ����:0x22C+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to control the local delay line.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdqsbdl  : 9;  /* bit[0-8]  : Read DQS Delay Select.
                                                    This field specify the phase shift of the Read DQS to create 90 degree delays. */
        unsigned int  reserved_0: 7;  /* bit[9-15] : -- */
        unsigned int  rdqscyc  : 9;  /* bit[16-24]: Read DQS Clock Phase Select.
                                                    This field indicate how many taps does one clock cycle has with 1-T delay measurement type. This field indicate how many taps does a half of clock cycle has with half-T delay measurement type. This field will be used to create 90 degree delays for RDQS. */
        unsigned int  reserved_1: 7;  /* bit[25-31]: -- */
    } reg;
} SOC_HIPACKPHY_DXNRDQSDLY_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDQSDLY_rdqsbdl_START   (0)
#define SOC_HIPACKPHY_DXNRDQSDLY_rdqsbdl_END     (8)
#define SOC_HIPACKPHY_DXNRDQSDLY_rdqscyc_START   (16)
#define SOC_HIPACKPHY_DXNRDQSDLY_rdqscyc_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNWDQSDLY_UNION
 �ṹ˵��  : DXNWDQSDLY �Ĵ����ṹ���塣��ַƫ����:0x230+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to control the write leveling DQS delays.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdqsbdl   : 7;  /* bit[0-6]  : Write Leveling DQS Delay Select.
                                                     This field specify the delay value of delay applied on WDQS for write leveling. 
                                                     wdqsoe_bdl and oen_bdl will be overwritten while wdqsbdl written. Wdqsbdl must must be written first if you want to control individually. */
        unsigned int  reserved_0: 1;  /* bit[7]    : -- */
        unsigned int  wdqsphase : 4;  /* bit[8-11] : Write DQS Clock Phase Select.
                                                     Note: The mapping from register value to delay degree, please reference to sheet "Phase8_6_2 Mapping" when phaseradix3en enabled */
        unsigned int  reserved_1: 20; /* bit[12-31]: -- */
    } reg;
} SOC_HIPACKPHY_DXNWDQSDLY_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQSDLY_wdqsbdl_START    (0)
#define SOC_HIPACKPHY_DXNWDQSDLY_wdqsbdl_END      (6)
#define SOC_HIPACKPHY_DXNWDQSDLY_wdqsphase_START  (8)
#define SOC_HIPACKPHY_DXNWDQSDLY_wdqsphase_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNWDQDLY_UNION
 �ṹ˵��  : DXNWDQDLY �Ĵ����ṹ���塣��ַƫ����:0x234+(m)*0x400+(n)*0x80����ֵ:0x00000C00�����:32
 �Ĵ���˵��: This register is used to control the write leveling delay line.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 8;  /* bit[0-7]  : -- */
        unsigned int  wdqphase : 6;  /* bit[8-13] : Write data eye clock phase select.
                                                    Note: The mapping from register value to delay degree, please reference to sheet "Phase8_6_2 Mapping" when phaseradix3en enabled */
        unsigned int  reserved_1: 18; /* bit[14-31]: -- */
    } reg;
} SOC_HIPACKPHY_DXNWDQDLY_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQDLY_wdqphase_START  (8)
#define SOC_HIPACKPHY_DXNWDQDLY_wdqphase_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNWLSL_UNION
 �ṹ˵��  : DXNWLSL �Ĵ����ṹ���塣��ַƫ����:0x238+(n)*0x80����ֵ:0x00010000�����:32
 �Ĵ���˵��: This reister is used to control if PHY controller add extra system latency.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 16; /* bit[0-15] : -- */
        unsigned int  wlsl     : 2;  /* bit[16-17]: Write Leveling System Latency.
                                                    This is used to adjust the write latency after write leveling. */
        unsigned int  reserved_1: 14; /* bit[18-31]: -- */
    } reg;
} SOC_HIPACKPHY_DXNWLSL_UNION;
#endif
#define SOC_HIPACKPHY_DXNWLSL_wlsl_START      (16)
#define SOC_HIPACKPHY_DXNWLSL_wlsl_END        (17)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNGDS_UNION
 �ṹ˵��  : DXNGDS �Ĵ����ṹ���塣��ַƫ����:0x23C+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to control the latch enable within the PHY to get the stable data.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gds      : 4;  /* bit[0-3] : Rank0 Read Data Latch Delays.
                                                   This field is used as a reference stable region for the PHY to latch the read data. */
        unsigned int  reserved : 28; /* bit[4-31]: -- */
    } reg;
} SOC_HIPACKPHY_DXNGDS_UNION;
#endif
#define SOC_HIPACKPHY_DXNGDS_gds_START       (0)
#define SOC_HIPACKPHY_DXNGDS_gds_END         (3)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNRDQSGDLY_UNION
 �ṹ˵��  : DXNRDQSGDLY �Ĵ����ṹ���塣��ַƫ����:0x240+(n)*0x80+(m)*0x400����ֵ:0x00000010�����:32
 �Ĵ���˵��: This register is used to control the local delay line.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdqsgbdl    : 7;  /* bit[0-6]  : Read DQS Gateing Delay Select.
                                                       This field specify the delay value of the read gating delay after DQS dummy PAD. */
        unsigned int  reserved_0  : 2;  /* bit[7-8]  :  */
        unsigned int  rdqsgphase  : 6;  /* bit[9-14] : Read DQS Gating Clock Phase Select.
                                                       Note: The mapping from register value to delay degree, please reference to sheet "Phase8_6_2 Mapping" when phaseradix3en enabled */
        unsigned int  reserved_1  : 1;  /* bit[15]   :  */
        unsigned int  rdqsgtxbdl  : 7;  /* bit[16-22]: Read DQS Gate Delay Select.
                                                       This field specify the delay value of the read gating delay before DQS dummy PAD. */
        unsigned int  reserved_2  : 1;  /* bit[23]   :  */
        unsigned int  org_rdqsgph : 6;  /* bit[24-29]: Original Read DQS Gate phase before HW GATE training post-update stage. (debug purpose). */
        unsigned int  reserved_3  : 2;  /* bit[30-31]: -- */
    } reg;
} SOC_HIPACKPHY_DXNRDQSGDLY_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDQSGDLY_rdqsgbdl_START     (0)
#define SOC_HIPACKPHY_DXNRDQSGDLY_rdqsgbdl_END       (6)
#define SOC_HIPACKPHY_DXNRDQSGDLY_rdqsgphase_START   (9)
#define SOC_HIPACKPHY_DXNRDQSGDLY_rdqsgphase_END     (14)
#define SOC_HIPACKPHY_DXNRDQSGDLY_rdqsgtxbdl_START   (16)
#define SOC_HIPACKPHY_DXNRDQSGDLY_rdqsgtxbdl_END     (22)
#define SOC_HIPACKPHY_DXNRDQSGDLY_org_rdqsgph_START  (24)
#define SOC_HIPACKPHY_DXNRDQSGDLY_org_rdqsgph_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNWDQNLB0_UNION
 �ṹ˵��  : DXNWDQNLB0 �Ĵ����ṹ���塣��ַƫ����:0x244+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to latch the WDQ left boundary of current rank after WDET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdq0bdl_left : 7;  /* bit[0-6]  : Left boundary of WDQ0. */
        unsigned int  reserved_0   : 1;  /* bit[7]    : -- */
        unsigned int  wdq1bdl_left : 7;  /* bit[8-14] : Left boundary of WDQ1. */
        unsigned int  reserved_1   : 1;  /* bit[15]   : -- */
        unsigned int  wdq2bdl_left : 7;  /* bit[16-22]: Left boundary of WDQ2. */
        unsigned int  reserved_2   : 1;  /* bit[23]   : -- */
        unsigned int  wdq3bdl_left : 7;  /* bit[24-30]: Left boundary of WDQ3. */
        unsigned int  reserved_3   : 1;  /* bit[31]   : -- */
    } reg;
} SOC_HIPACKPHY_DXNWDQNLB0_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq0bdl_left_START  (0)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq0bdl_left_END    (6)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq1bdl_left_START  (8)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq1bdl_left_END    (14)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq2bdl_left_START  (16)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq2bdl_left_END    (22)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq3bdl_left_START  (24)
#define SOC_HIPACKPHY_DXNWDQNLB0_wdq3bdl_left_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNRDQSDLYSUB_UNION
 �ṹ˵��  : DXNRDQSDLYSUB �Ĵ����ṹ���塣��ַƫ����:0x248+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to control the local delay line.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdqsbdl30  : 9;  /* bit[0-8]  : The 30 degree phase delays. This field will be set automatically by HW when delay measure is done and will be used to fine tune the WDET result when half_ph_bdl_en=0x1. */
        unsigned int  reserved_0 : 7;  /* bit[9-15] : -- */
        unsigned int  bdl_mondly : 9;  /* bit[16-24]: This field specify the delay for DQSG_mondly_DQS. When rdqsg_mondly_type = 0/1/2 (30/60/90 degree), this field should be the delay of 30/60/90 degree respectively. This field will be set automatically by HW when delay measure is done. */
        unsigned int  reserved_1 : 7;  /* bit[25-31]: -- */
    } reg;
} SOC_HIPACKPHY_DXNRDQSDLYSUB_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDQSDLYSUB_rdqsbdl30_START   (0)
#define SOC_HIPACKPHY_DXNRDQSDLYSUB_rdqsbdl30_END     (8)
#define SOC_HIPACKPHY_DXNRDQSDLYSUB_bdl_mondly_START  (16)
#define SOC_HIPACKPHY_DXNRDQSDLYSUB_bdl_mondly_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNCLKBDL_UNION
 �ṹ˵��  : DXNCLKBDL �Ĵ����ṹ���塣��ַƫ����:0x24C+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: DATA block clock bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dx_fbclk_bdl  : 5;  /* bit[0-4]  : Bit delay line setting of FBCLK
                                                         Move to DX_Static_Reg */
        unsigned int  reserved_0    : 11; /* bit[5-15] : -- */
        unsigned int  dx_refclk_bdl : 5;  /* bit[16-20]: Bit delay line setting of REFCLK
                                                         Move to DX_Static_Reg */
        unsigned int  reserved_1    : 11; /* bit[21-31]: -- */
    } reg;
} SOC_HIPACKPHY_DXNCLKBDL_UNION;
#endif
#define SOC_HIPACKPHY_DXNCLKBDL_dx_fbclk_bdl_START   (0)
#define SOC_HIPACKPHY_DXNCLKBDL_dx_fbclk_bdl_END     (4)
#define SOC_HIPACKPHY_DXNCLKBDL_dx_refclk_bdl_START  (16)
#define SOC_HIPACKPHY_DXNCLKBDL_dx_refclk_bdl_END    (20)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNRDBOUND_UNION
 �ṹ˵��  : DXNRDBOUND �Ĵ����ṹ���塣��ַƫ����:0x250+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: Read data eye boundary. This register indicates the left/right boundary of RDQSQDL of the data eye.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdqsbdl_right : 9;  /* bit[0-8]  : Right boundary of read data eye. */
        unsigned int  reserved_0    : 7;  /* bit[9-15] : --- */
        unsigned int  rdqsbdl_left  : 9;  /* bit[16-24]: Left boundary of read data eye. */
        unsigned int  reserved_1    : 7;  /* bit[25-31]: --- */
    } reg;
} SOC_HIPACKPHY_DXNRDBOUND_UNION;
#endif
#define SOC_HIPACKPHY_DXNRDBOUND_rdqsbdl_right_START  (0)
#define SOC_HIPACKPHY_DXNRDBOUND_rdqsbdl_right_END    (8)
#define SOC_HIPACKPHY_DXNRDBOUND_rdqsbdl_left_START   (16)
#define SOC_HIPACKPHY_DXNRDBOUND_rdqsbdl_left_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNWRBOUND_UNION
 �ṹ˵��  : DXNWRBOUND �Ĵ����ṹ���塣��ַƫ����:0x254+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: Write data eye boundary. This register indicates the left/right boundary of WDQSQDL of the data eye.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdqphase_right : 6;  /* bit[0-5]  : Right boundary of the write data eye. */
        unsigned int  reserved_0     : 10; /* bit[6-15] : --- */
        unsigned int  wdqphase_left  : 6;  /* bit[16-21]: Left boundary of the write data eye. */
        unsigned int  reserved_1     : 2;  /* bit[22-23]: --- */
        unsigned int  wdq0bdl_left   : 7;  /* bit[24-30]: Left boundary of the write data eye (DQ0). */
        unsigned int  reserved_2     : 1;  /* bit[31]   : --- */
    } reg;
} SOC_HIPACKPHY_DXNWRBOUND_UNION;
#endif
#define SOC_HIPACKPHY_DXNWRBOUND_wdqphase_right_START  (0)
#define SOC_HIPACKPHY_DXNWRBOUND_wdqphase_right_END    (5)
#define SOC_HIPACKPHY_DXNWRBOUND_wdqphase_left_START   (16)
#define SOC_HIPACKPHY_DXNWRBOUND_wdqphase_left_END     (21)
#define SOC_HIPACKPHY_DXNWRBOUND_wdq0bdl_left_START    (24)
#define SOC_HIPACKPHY_DXNWRBOUND_wdq0bdl_left_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXPHYCTRL_UNION
 �ṹ˵��  : DXPHYCTRL �Ĵ����ṹ���塣��ַƫ����:0x258+(n)*0x80����ֵ:0x000000A0�����:32
 �Ĵ���˵��: DX PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dx_pll_thrm    : 1;  /* bit[0]    : Dummy Reg - Not Used */
        unsigned int  dx_pll_testpem : 1;  /* bit[1]    : Dummy Reg - Not Used */
        unsigned int  dx_pll_testen  : 1;  /* bit[2]    : Move to DX_Static_Reg */
        unsigned int  dx_pll_init    : 1;  /* bit[3]    : Move to DX_Static_Reg */
        unsigned int  dx_pll_cpi     : 3;  /* bit[4-6]  : Move to DX_Static_Reg */
        unsigned int  dx_pll_sp      : 3;  /* bit[7-9]  : Move to DX_Static_Reg */
        unsigned int  dx_pll_lt      : 2;  /* bit[10-11]: Move to DX_Static_Reg */
        unsigned int  dx_pll_calt    : 1;  /* bit[12]   : Dummy Reg - Not Used */
        unsigned int  dx_pll_calm    : 1;  /* bit[13]   : Dummy Reg - Not Used */
        unsigned int  dx_pll_cal     : 1;  /* bit[14]   : Dummy Reg - Not Used */
        unsigned int  reserved       : 17; /* bit[15-31]:  */
    } reg;
} SOC_HIPACKPHY_DXPHYCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_thrm_START     (0)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_thrm_END       (0)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_testpem_START  (1)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_testpem_END    (1)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_testen_START   (2)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_testen_END     (2)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_init_START     (3)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_init_END       (3)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_cpi_START      (4)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_cpi_END        (6)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_sp_START       (7)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_sp_END         (9)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_lt_START       (10)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_lt_END         (11)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_calt_START     (12)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_calt_END       (12)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_calm_START     (13)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_calm_END       (13)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_cal_START      (14)
#define SOC_HIPACKPHY_DXPHYCTRL_dx_pll_cal_END        (14)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNWDQNLB1_UNION
 �ṹ˵��  : DXNWDQNLB1 �Ĵ����ṹ���塣��ַƫ����:0x25C+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is used to latch the WDQ left boundary of current rank after WDET
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdq4bdl_left : 7;  /* bit[0-6]  : Left boundary of WDQ4. */
        unsigned int  reserved_0   : 1;  /* bit[7]    : -- */
        unsigned int  wdq5bdl_left : 7;  /* bit[8-14] : Left boundary of WDQ5. */
        unsigned int  reserved_1   : 1;  /* bit[15]   : -- */
        unsigned int  wdq6bdl_left : 7;  /* bit[16-22]: Left boundary of WDQ6. */
        unsigned int  reserved_2   : 1;  /* bit[23]   : -- */
        unsigned int  wdq7bdl_left : 7;  /* bit[24-30]: Left boundary of WDQ7. */
        unsigned int  reserved_3   : 1;  /* bit[31]   : -- */
    } reg;
} SOC_HIPACKPHY_DXNWDQNLB1_UNION;
#endif
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq4bdl_left_START  (0)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq4bdl_left_END    (6)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq5bdl_left_START  (8)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq5bdl_left_END    (14)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq6bdl_left_START  (16)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq6bdl_left_END    (22)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq7bdl_left_START  (24)
#define SOC_HIPACKPHY_DXNWDQNLB1_wdq7bdl_left_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNMISCCTRL0_UNION
 �ṹ˵��  : DXNMISCCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x260+(n)*0x80����ֵ:0x00020000�����:32
 �Ĵ���˵��: Data block PHY miscellaneous control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rxn_2nd_dq                : 8;  /* bit[0-7] : After modify this field, it need the "phyconn_rst" to update the latest setting. When user want to use dly_track_type=1 tracking type, this field should be set as 0xFF before initial trainings and dly_track_type should be set as 0x1 after initial trainings.
                                                                    Move to DX_Static_Reg */
        unsigned int  rxp_2nd_dq                : 8;  /* bit[8-15]: After modify this field, it need the "phyconn_rst" to update the latest setting. When user want to use dly_track_type=1 tracking type, this field should be set as 0xFF before initial trainings and dly_track_type should be set as 0x1 after initial trainings.
                                                                    Move to DX_Static_Reg */
        unsigned int  dx_margin_a1              : 1;  /* bit[16]  : After modify this field, it need the "phyconn_rst" to update the latest setting. When user want to use dly_track_type=1 tracking type, this field should be set as 0x1 before initial trainings and dly_track_type should be set as 0x1 after initial trainings. */
        unsigned int  dx_dqs_l                  : 1;  /* bit[17]  : Move to DX_Static_Reg */
        unsigned int  dx_dqs_h                  : 1;  /* bit[18]  : Move to DX_Static_Reg */
        unsigned int  dx_rxn_2nd_dm             : 1;  /* bit[19]  : After modify this field, it need the "phyconn_rst" to update the latest setting. When user want to use dly_track_type=1 tracking type, this field should be set as 0x1 before initial trainings and dly_track_type should be set as 0x1 after initial trainings.
                                                                    Move to DX_Static_Reg */
        unsigned int  dx_rxp_2nd_dm             : 1;  /* bit[20]  : After modify this field, it need the "phyconn_rst" to update the latest setting. When user want to use dly_track_type=1 tracking type, this field should be set as 0x1 before initial trainings and dly_track_type should be set as 0x1 after initial trainings.
                                                                    Move to DX_Static_Reg */
        unsigned int  dqsgatedla                : 1;  /* bit[21]  : Move to DX_Static_Reg */
        unsigned int  lvdqclkdiv2               : 1;  /* bit[22]  : Move to DX_Static_Reg */
        unsigned int  bufphyclkdiv2             : 1;  /* bit[23]  : Move to DX_Static_Reg */
        unsigned int  margin_a0                 : 1;  /* bit[24]  : After modify this field, it need the "phyconn_rst" to update the latest setting. When user want to use dly_track_type=1 tracking type, this field should be set as 0x1 before initial trainings and dly_track_type should be set as 0x1 after initial trainings. */
        unsigned int  enshift_a0                : 1;  /* bit[25]  :  */
        unsigned int  ptrgated_en               : 1;  /* bit[26]  : Move to DX_Static_Reg */
        unsigned int  reserved_0                : 1;  /* bit[27]  :  */
        unsigned int  dx_reg_dqsg_extend_en_dqs : 1;  /* bit[28]  : 0: Disable the DQSG extending function (default)
                                                                    1: Enable the DQSG extending function
                                                                    Move to DX_Static_Reg */
        unsigned int  dx_reg_dqsg_extend_2t_dqs : 1;  /* bit[29]  : 0: Extend DQSG 1T dfi_clk, when reg_DQSG_extend_en=1 (default)
                                                                    1: Extend DQSG 2T dfi_clk, when reg_DQSG_extend_en=1
                                                                    Move to DX_Static_Reg */
        unsigned int  dx_reg_rxfifo_r1t_sel_dqs : 1;  /* bit[30]  : 0: GDS no leading 1T (default)
                                                                    1: GDS leading 1T
                                                                    Move to DX_Static_Reg */
        unsigned int  reserved_1                : 1;  /* bit[31]  : -- */
    } reg;
} SOC_HIPACKPHY_DXNMISCCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_DXNMISCCTRL0_rxn_2nd_dq_START                 (0)
#define SOC_HIPACKPHY_DXNMISCCTRL0_rxn_2nd_dq_END                   (7)
#define SOC_HIPACKPHY_DXNMISCCTRL0_rxp_2nd_dq_START                 (8)
#define SOC_HIPACKPHY_DXNMISCCTRL0_rxp_2nd_dq_END                   (15)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_margin_a1_START               (16)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_margin_a1_END                 (16)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_dqs_l_START                   (17)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_dqs_l_END                     (17)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_dqs_h_START                   (18)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_dqs_h_END                     (18)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_rxn_2nd_dm_START              (19)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_rxn_2nd_dm_END                (19)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_rxp_2nd_dm_START              (20)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_rxp_2nd_dm_END                (20)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dqsgatedla_START                 (21)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dqsgatedla_END                   (21)
#define SOC_HIPACKPHY_DXNMISCCTRL0_lvdqclkdiv2_START                (22)
#define SOC_HIPACKPHY_DXNMISCCTRL0_lvdqclkdiv2_END                  (22)
#define SOC_HIPACKPHY_DXNMISCCTRL0_bufphyclkdiv2_START              (23)
#define SOC_HIPACKPHY_DXNMISCCTRL0_bufphyclkdiv2_END                (23)
#define SOC_HIPACKPHY_DXNMISCCTRL0_margin_a0_START                  (24)
#define SOC_HIPACKPHY_DXNMISCCTRL0_margin_a0_END                    (24)
#define SOC_HIPACKPHY_DXNMISCCTRL0_enshift_a0_START                 (25)
#define SOC_HIPACKPHY_DXNMISCCTRL0_enshift_a0_END                   (25)
#define SOC_HIPACKPHY_DXNMISCCTRL0_ptrgated_en_START                (26)
#define SOC_HIPACKPHY_DXNMISCCTRL0_ptrgated_en_END                  (26)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_reg_dqsg_extend_en_dqs_START  (28)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_reg_dqsg_extend_en_dqs_END    (28)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_reg_dqsg_extend_2t_dqs_START  (29)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_reg_dqsg_extend_2t_dqs_END    (29)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_reg_rxfifo_r1t_sel_dqs_START  (30)
#define SOC_HIPACKPHY_DXNMISCCTRL0_dx_reg_rxfifo_r1t_sel_dqs_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNMISCCTRL1_UNION
 �ṹ˵��  : DXNMISCCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x264+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: Data block PHY miscellaneous control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mclk2x    : 4;  /* bit[0-3]  : Move to DX_Static_Reg */
        unsigned int  mclk1x    : 4;  /* bit[4-7]  : Move to DX_Static_Reg */
        unsigned int  dqsclk2x  : 4;  /* bit[8-11] : Move to DX_Static_Reg */
        unsigned int  dqsclk1x  : 4;  /* bit[12-15]: Move to DX_Static_Reg */
        unsigned int  dqsgclk2x : 4;  /* bit[16-19]: Move to DX_Static_Reg */
        unsigned int  dqsgclk1x : 4;  /* bit[20-23]: Move to DX_Static_Reg */
        unsigned int  dqclk2x   : 4;  /* bit[24-27]: Move to DX_Static_Reg */
        unsigned int  dqclk1x   : 4;  /* bit[28-31]: Move to DX_Static_Reg */
    } reg;
} SOC_HIPACKPHY_DXNMISCCTRL1_UNION;
#endif
#define SOC_HIPACKPHY_DXNMISCCTRL1_mclk2x_START     (0)
#define SOC_HIPACKPHY_DXNMISCCTRL1_mclk2x_END       (3)
#define SOC_HIPACKPHY_DXNMISCCTRL1_mclk1x_START     (4)
#define SOC_HIPACKPHY_DXNMISCCTRL1_mclk1x_END       (7)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsclk2x_START   (8)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsclk2x_END     (11)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsclk1x_START   (12)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsclk1x_END     (15)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsgclk2x_START  (16)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsgclk2x_END    (19)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsgclk1x_START  (20)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqsgclk1x_END    (23)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqclk2x_START    (24)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqclk2x_END      (27)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqclk1x_START    (28)
#define SOC_HIPACKPHY_DXNMISCCTRL1_dqclk1x_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXDEBUG0_UNION
 �ṹ˵��  : DXDEBUG0 �Ĵ����ṹ���塣��ַƫ����:0x268+(n)*0x80����ֵ:0x00010000�����:32
 �Ĵ���˵��: Data block PHY debug signals
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdmbdl_left : 7;  /* bit[0-6]  : Left boundary of WDM */
        unsigned int  reserved    : 9;  /* bit[7-15] :  */
        unsigned int  dqs0_gold   : 16; /* bit[16-31]: Debug signals */
    } reg;
} SOC_HIPACKPHY_DXDEBUG0_UNION;
#endif
#define SOC_HIPACKPHY_DXDEBUG0_wdmbdl_left_START  (0)
#define SOC_HIPACKPHY_DXDEBUG0_wdmbdl_left_END    (6)
#define SOC_HIPACKPHY_DXDEBUG0_dqs0_gold_START    (16)
#define SOC_HIPACKPHY_DXDEBUG0_dqs0_gold_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXDEBUG1_UNION
 �ṹ˵��  : DXDEBUG1 �Ĵ����ṹ���塣��ַƫ����:0x26C+(n)*0x80����ֵ:0x00010001�����:32
 �Ĵ���˵��: Data block PHY debug signals
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dqs0b : 16; /* bit[0-15] : DQS Debug signals. Please note in the simulation these fields may have unknown values. */
        unsigned int  dqs0  : 16; /* bit[16-31]: DQS Debug signals. Please note in the simulation these fields may have unknown values. */
    } reg;
} SOC_HIPACKPHY_DXDEBUG1_UNION;
#endif
#define SOC_HIPACKPHY_DXDEBUG1_dqs0b_START  (0)
#define SOC_HIPACKPHY_DXDEBUG1_dqs0b_END    (15)
#define SOC_HIPACKPHY_DXDEBUG1_dqs0_START   (16)
#define SOC_HIPACKPHY_DXDEBUG1_dqs0_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DVREFT_STATUS_UNION
 �ṹ˵��  : DVREFT_STATUS �Ĵ����ṹ���塣��ַƫ����:0x270+(n)*0x80����ֵ:0x00000019�����:32
 �Ĵ���˵��: DRAM VREF(DQ) Training Result. This register shows the training result of the DRAM VREF(DQ) training.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vrftres_dvref      : 6;  /* bit[0-5]  : DRAM VREF(DQ) Training Result
                                                              This field shows the DRAM VREF settings.
                                                              Before DRAM VREF training, this value will be used as the initial value of VREF training, and after training, this value shows the final training result.
                                                              If DRAM VREF value after training need to be modified, the user has to do VREF synchronization operations after writing to this register. */
        unsigned int  vrftres_dvref_lb   : 6;  /* bit[6-11] : DRAM VREF(DQ) Training Lower Boundary.
                                                              This field shows the lower boundary of VREF(DQ) value during VREF(DQ) training.  */
        unsigned int  vrftres_dvref_ub   : 6;  /* bit[12-17]: DRAM VREF(DQ) Training Upper Boundary.
                                                              This field shows the upper boundary of VREF(DQ) value during VREF(DQ) training.  */
        unsigned int  vrftres_dlb_status : 3;  /* bit[18-20]: DRAM VREF(DQ) Training Status (Lower Boundary)
                                                              This field shows the training status of lower boundary of VREF training. These three bits represents the BIST results of horizontal check points. If the bit is set to a '1', the BIST results contains errors. If the bit is '0', it indicate that the corresponding bit is not checked or BIST succeed.
                                                              vrftres_dlb_status[0] : Status of original delays.
                                                              vrftres_dlb_status[1] : Status of +delta delays.
                                                              vrftres_dlb_status[0] : Status of -delta delays. */
        unsigned int  vrftres_dub_status : 3;  /* bit[21-23]: DRAM VREF(DQ) Training Status (Upper Boundary)
                                                              This field shows the training status of upper boundary of VREF training. These three bits represents the BIST results of horizontal check points. If the bit is set to a '1', the BIST results contains errors. If the bit is '0', it indicate that the corresponding bit is not checked or BIST succeed.
                                                              vrftres_dub_status[0] : Status of original delays.
                                                              vrftres_dub_status[1] : Status of +delta delays.
                                                              vrftres_dub_status[0] : Status of -delta delays. */
        unsigned int  reserved           : 8;  /* bit[24-31]: -- */
    } reg;
} SOC_HIPACKPHY_DVREFT_STATUS_UNION;
#endif
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dvref_START       (0)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dvref_END         (5)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dvref_lb_START    (6)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dvref_lb_END      (11)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dvref_ub_START    (12)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dvref_ub_END      (17)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dlb_status_START  (18)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dlb_status_END    (20)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dub_status_START  (21)
#define SOC_HIPACKPHY_DVREFT_STATUS_vrftres_dub_status_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_HVREFT_STATUS_UNION
 �ṹ˵��  : HVREFT_STATUS �Ĵ����ṹ���塣��ַƫ����:0x274+(n)*0x80����ֵ:0x00000008�����:32
 �Ĵ���˵��: Host PHY VREF(DQ) Training Result. This register shows the training result of the Host PHY VREF(DQ) training.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vrftres_hvref      : 6;  /* bit[0-5]  : Host PHY VREF(DQ) Control Value.
                                                              This field is used to control the host PHY VREF. If the Host PHY VREF(DQ) training is enabled to execute, this field will be updated to the training results. */
        unsigned int  vrftres_hvref_lb   : 6;  /* bit[6-11] : Host PHY VREF(DQ) Training Lower Boundary.
                                                              This field shows the results of lower boundary of the host PHY VREF(DQ) training. */
        unsigned int  vrftres_dvref_ub   : 6;  /* bit[12-17]: Host PHY VREF(DQ) Training Upper Boundary.
                                                              This field shows the results of upper boundary of the host PHY VREF(DQ) training. */
        unsigned int  vrftres_hlb_status : 3;  /* bit[18-20]: Host PHY VREF(DQ) Training Status (Lower Boundary)
                                                              This field shows the training status of lower boundary of VREF training. These three bits represents the BIST results of horizontal check points. If the bit is set to a '1', the BIST results contains errors. If the bit is '0', it indicate that the corresponding bit is not checked or BIST succeed.
                                                              vrftres_hlb_status[0] : Status of original delays.
                                                              vrftres_hlb_status[1] : Status of +delta delays.
                                                              vrftres_hlb_status[0] : Status of -delta delays. */
        unsigned int  vrftres_hub_status : 3;  /* bit[21-23]: Host PHY VREF(DQ) Training Status (Upper Boundary)
                                                              This field shows the training status of upper boundary of host PHY VREF training. These three bits represents the BIST results of horizontal check points. If the bit is set to a '1', the BIST results contains errors. If the bit is '0', it indicate that the corresponding bit is not checked or BIST succeed.
                                                              vrftres_hub_status[0] : Status of original delays.
                                                              vrftres_hub_status[1] : Status of +delta delays.
                                                              vrftres_hub_status[0] : Status of -delta delays. */
        unsigned int  reserved           : 8;  /* bit[24-31]: -- */
    } reg;
} SOC_HIPACKPHY_HVREFT_STATUS_UNION;
#endif
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hvref_START       (0)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hvref_END         (5)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hvref_lb_START    (6)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hvref_lb_END      (11)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_dvref_ub_START    (12)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_dvref_ub_END      (17)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hlb_status_START  (18)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hlb_status_END    (20)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hub_status_START  (21)
#define SOC_HIPACKPHY_HVREFT_STATUS_vrftres_hub_status_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXDEBUGCONFIG_UNION
 �ṹ˵��  : DXDEBUGCONFIG �Ĵ����ṹ���塣��ַƫ����:0x278+(n)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: Data block PHY debug/miscellaneous control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg_dbg_reffb_postdly : 1;  /* bit[0]   : Dummy Reg - Not Used */
        unsigned int  reg_dbg_reffb_predly  : 1;  /* bit[1]   : Dummy Reg - Not Used */
        unsigned int  reg_dbg_pllclk_sel    : 1;  /* bit[2]   : Dummy Reg - Not Used */
        unsigned int  reg_dbg_prepost_sel   : 1;  /* bit[3]   : Dummy Reg - Not Used */
        unsigned int  deskew_regread        : 1;  /* bit[4]   : Move to DX_Static_Reg */
        unsigned int  reserved              : 27; /* bit[5-31]: --- */
    } reg;
} SOC_HIPACKPHY_DXDEBUGCONFIG_UNION;
#endif
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_reffb_postdly_START  (0)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_reffb_postdly_END    (0)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_reffb_predly_START   (1)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_reffb_predly_END     (1)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_pllclk_sel_START     (2)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_pllclk_sel_END       (2)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_prepost_sel_START    (3)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_reg_dbg_prepost_sel_END      (3)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_deskew_regread_START         (4)
#define SOC_HIPACKPHY_DXDEBUGCONFIG_deskew_regread_END           (4)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNDCC_UNION
 �ṹ˵��  : DXNDCC �Ĵ����ṹ���塣��ַƫ����:0x27C+(n)*0x80����ֵ:0x00020000�����:32
 �Ĵ���˵��: Data block PHY DCC control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_dq_dcc              : 3;  /* bit[0-2]  : [2]-dly_sel_xxx_DCC_16b
                                                                     [1]-ctrlC_xxx_DCC_16b
                                                                     [0]-ctrl2_xxx_DCC_16b
                                                                     Move to DX_Static_Reg */
        unsigned int  dxctl_dqsg_dcc            : 3;  /* bit[3-5]  : [2]-dly_sel_xxx_DCC_16b
                                                                     [1]-ctrlC_xxx_DCC_16b
                                                                     [0]-ctrl2_xxx_DCC_16b
                                                                     Move to DX_Static_Reg */
        unsigned int  dxctl_dqs_dcc             : 3;  /* bit[6-8]  : [2]-dly_sel_xxx_DCC_16b
                                                                     [1]-ctrlC_xxx_DCC_16b
                                                                     [0]-ctrl2_xxx_DCC_16b
                                                                     Move to DX_Static_Reg */
        unsigned int  dxctl_mclk_dcc            : 3;  /* bit[9-11] : [2]-dly_sel_xxx_DCC_16b
                                                                     [1]-ctrlC_xxx_DCC_16b
                                                                     [0]-ctrl2_xxx_DCC_16b
                                                                     Move to DX_Static_Reg */
        unsigned int  dx_byp_ck90_data_code_dqs : 9;  /* bit[12-20]: Move to DX_Static_Reg
                                                                     Only bit[7:1] are valid. Used as {bit[7:1],1'b1}. The bit[8] is useless. */
        unsigned int  reserved                  : 11; /* bit[21-31]: --- */
    } reg;
} SOC_HIPACKPHY_DXNDCC_UNION;
#endif
#define SOC_HIPACKPHY_DXNDCC_dxctl_dq_dcc_START               (0)
#define SOC_HIPACKPHY_DXNDCC_dxctl_dq_dcc_END                 (2)
#define SOC_HIPACKPHY_DXNDCC_dxctl_dqsg_dcc_START             (3)
#define SOC_HIPACKPHY_DXNDCC_dxctl_dqsg_dcc_END               (5)
#define SOC_HIPACKPHY_DXNDCC_dxctl_dqs_dcc_START              (6)
#define SOC_HIPACKPHY_DXNDCC_dxctl_dqs_dcc_END                (8)
#define SOC_HIPACKPHY_DXNDCC_dxctl_mclk_dcc_START             (9)
#define SOC_HIPACKPHY_DXNDCC_dxctl_mclk_dcc_END               (11)
#define SOC_HIPACKPHY_DXNDCC_dx_byp_ck90_data_code_dqs_START  (12)
#define SOC_HIPACKPHY_DXNDCC_dx_byp_ck90_data_code_dqs_END    (20)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DXNMISCCTRL3_UNION
 �ṹ˵��  : DXNMISCCTRL3 �Ĵ����ṹ���塣��ַƫ����:0x20C+(n)*0x80����ֵ:0x00D80000�����:32
 �Ĵ���˵��: Data block PHY debug/miscellaneous control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dqsg_extdly_dqs   : 3;  /* bit[0-2]  : Move to DX_Static_Reg */
        unsigned int  reserved_0        : 1;  /* bit[3]    :  */
        unsigned int  reserved_1        : 7;  /* bit[4-10] : Move to DX_Static_Reg */
        unsigned int  reserved_2        : 1;  /* bit[11]   :  */
        unsigned int  rxext_dly         : 3;  /* bit[12-14]: Move to DX_Static_Reg */
        unsigned int  reserved_3        : 1;  /* bit[15]   :  */
        unsigned int  dqsdly_demux_code : 3;  /* bit[16-18]: Move to DX_Static_Reg */
        unsigned int  post_margin_code  : 3;  /* bit[19-21]: Move to DX_Static_Reg */
        unsigned int  pre_margin_code   : 3;  /* bit[22-24]: Move to DX_Static_Reg */
        unsigned int  dqsgclk2x_rank1   : 3;  /* bit[25-27]: Move to DX_Static_Reg */
        unsigned int  dqsgclk1x_rank1   : 3;  /* bit[28-30]: Move to DX_Static_Reg */
        unsigned int  reserved_4        : 1;  /* bit[31]   : --- */
    } reg;
} SOC_HIPACKPHY_DXNMISCCTRL3_UNION;
#endif
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsg_extdly_dqs_START    (0)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsg_extdly_dqs_END      (2)
#define SOC_HIPACKPHY_DXNMISCCTRL3_rxext_dly_START          (12)
#define SOC_HIPACKPHY_DXNMISCCTRL3_rxext_dly_END            (14)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsdly_demux_code_START  (16)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsdly_demux_code_END    (18)
#define SOC_HIPACKPHY_DXNMISCCTRL3_post_margin_code_START   (19)
#define SOC_HIPACKPHY_DXNMISCCTRL3_post_margin_code_END     (21)
#define SOC_HIPACKPHY_DXNMISCCTRL3_pre_margin_code_START    (22)
#define SOC_HIPACKPHY_DXNMISCCTRL3_pre_margin_code_END      (24)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsgclk2x_rank1_START    (25)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsgclk2x_rank1_END      (27)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsgclk1x_rank1_START    (28)
#define SOC_HIPACKPHY_DXNMISCCTRL3_dqsgclk1x_rank1_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_IOCTL3_UNION
 �ṹ˵��  : IOCTL3 �Ĵ����ṹ���塣��ַƫ����:0xFF0����ֵ:0x0000C000�����:32
 �Ĵ���˵��: IO control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ac1t_ioctl_rdsel_p   : 3;  /* bit[0-2]  : Move to AC_Static_Reg */
        unsigned int  ac1t_ioctl_rdsel_n   : 3;  /* bit[3-5]  : Move to AC_Static_Reg */
        unsigned int  ac1t_ioctl_tdsel_p   : 4;  /* bit[6-9]  : Move to AC_Static_Reg */
        unsigned int  ac1t_ioctl_tdsel_n   : 4;  /* bit[10-13]: Move to AC_Static_Reg */
        unsigned int  ioctl_ap_rx_mode     : 2;  /* bit[14-15]: 2'b00: Low-Speed Loopback
                                                                2'b01: Middle Loopback
                                                                2'b10: High-Speed External Loopback, for DDR3/DDR3L
                                                                2'b11: High-Speed External Loopback, for DDR4/LPDDR3 */
        unsigned int  ioctl_odtn           : 1;  /* bit[16]   : Dummy Reg - Not Used */
        unsigned int  ioctl_odtp           : 1;  /* bit[17]   : Dummy Reg - Not Used */
        unsigned int  odt_ioctl_tdsel_p    : 4;  /* bit[18-21]: Move to DX_Static_Reg */
        unsigned int  odt_ioctl_tdsel_n    : 4;  /* bit[22-25]: Move to DX_Static_Reg */
        unsigned int  rx_rx_passthrough    : 1;  /* bit[26]   : add RX RS passthrough reg */
        unsigned int  rx_rsneg_passthrough : 1;  /* bit[27]   : add RX RSneg passthrough reg
                                                                Note: In V7R5, rsneg_passthrough/rsneg_rst_passthrough/rsneg_rstcont_passthrough/rx_rsneg_passthrough must set with the same value. (either all zeros, or all ones). */
        unsigned int  reserved             : 4;  /* bit[28-31]: --- */
    } reg;
} SOC_HIPACKPHY_IOCTL3_UNION;
#endif
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_rdsel_p_START    (0)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_rdsel_p_END      (2)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_rdsel_n_START    (3)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_rdsel_n_END      (5)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_tdsel_p_START    (6)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_tdsel_p_END      (9)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_tdsel_n_START    (10)
#define SOC_HIPACKPHY_IOCTL3_ac1t_ioctl_tdsel_n_END      (13)
#define SOC_HIPACKPHY_IOCTL3_ioctl_ap_rx_mode_START      (14)
#define SOC_HIPACKPHY_IOCTL3_ioctl_ap_rx_mode_END        (15)
#define SOC_HIPACKPHY_IOCTL3_ioctl_odtn_START            (16)
#define SOC_HIPACKPHY_IOCTL3_ioctl_odtn_END              (16)
#define SOC_HIPACKPHY_IOCTL3_ioctl_odtp_START            (17)
#define SOC_HIPACKPHY_IOCTL3_ioctl_odtp_END              (17)
#define SOC_HIPACKPHY_IOCTL3_odt_ioctl_tdsel_p_START     (18)
#define SOC_HIPACKPHY_IOCTL3_odt_ioctl_tdsel_p_END       (21)
#define SOC_HIPACKPHY_IOCTL3_odt_ioctl_tdsel_n_START     (22)
#define SOC_HIPACKPHY_IOCTL3_odt_ioctl_tdsel_n_END       (25)
#define SOC_HIPACKPHY_IOCTL3_rx_rx_passthrough_START     (26)
#define SOC_HIPACKPHY_IOCTL3_rx_rx_passthrough_END       (26)
#define SOC_HIPACKPHY_IOCTL3_rx_rsneg_passthrough_START  (27)
#define SOC_HIPACKPHY_IOCTL3_rx_rsneg_passthrough_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_IOCTL4_UNION
 �ṹ˵��  : IOCTL4 �Ĵ����ṹ���塣��ַƫ����:0xFF4����ֵ:0x00000000�����:32
 �Ĵ���˵��: IO control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_ioctl_rdsel_p   : 3;  /* bit[0-2]  : Move to AC_Static_Reg */
        unsigned int  ck_ioctl_rdsel_n   : 3;  /* bit[3-5]  : Move to AC_Static_Reg */
        unsigned int  ck_ioctl_tdsel_p   : 4;  /* bit[6-9]  : Move to AC_Static_Reg */
        unsigned int  ck_ioctl_tdsel_n   : 4;  /* bit[10-13]: Move to AC_Static_Reg */
        unsigned int  ac2t_ioctl_rdsel_p : 3;  /* bit[14-16]: Move to AC_Static_Reg */
        unsigned int  ac2t_ioctl_rdsel_n : 3;  /* bit[17-19]: Move to AC_Static_Reg */
        unsigned int  ac2t_ioctl_tdsel_p : 4;  /* bit[20-23]: Move to AC_Static_Reg */
        unsigned int  ac2t_ioctl_tdsel_n : 4;  /* bit[24-27]: Move to AC_Static_Reg */
        unsigned int  reserved           : 4;  /* bit[28-31]: --- */
    } reg;
} SOC_HIPACKPHY_IOCTL4_UNION;
#endif
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_rdsel_p_START    (0)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_rdsel_p_END      (2)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_rdsel_n_START    (3)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_rdsel_n_END      (5)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_tdsel_p_START    (6)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_tdsel_p_END      (9)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_tdsel_n_START    (10)
#define SOC_HIPACKPHY_IOCTL4_ck_ioctl_tdsel_n_END      (13)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_rdsel_p_START  (14)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_rdsel_p_END    (16)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_rdsel_n_START  (17)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_rdsel_n_END    (19)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_tdsel_p_START  (20)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_tdsel_p_END    (23)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_tdsel_n_START  (24)
#define SOC_HIPACKPHY_IOCTL4_ac2t_ioctl_tdsel_n_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_IOCTL5_UNION
 �ṹ˵��  : IOCTL5 �Ĵ����ṹ���塣��ַƫ����:0xFF8����ֵ:0x00000000�����:32
 �Ĵ���˵��: IO control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dqs_ioctl_rdsel_p : 3;  /* bit[0-2]  : Move to DX_Static_Reg */
        unsigned int  dqs_ioctl_rdsel_n : 3;  /* bit[3-5]  : Move to DX_Static_Reg */
        unsigned int  dqs_ioctl_tdsel_p : 4;  /* bit[6-9]  : Move to DX_Static_Reg */
        unsigned int  dqs_ioctl_tdsel_n : 4;  /* bit[10-13]: Move to DX_Static_Reg */
        unsigned int  dx_ioctl_rdsel_p  : 3;  /* bit[14-16]: Move to DX_Static_Reg */
        unsigned int  dx_ioctl_rdsel_n  : 3;  /* bit[17-19]: Move to DX_Static_Reg */
        unsigned int  dx_ioctl_tdsel_p  : 4;  /* bit[20-23]: Move to DX_Static_Reg */
        unsigned int  dx_ioctl_tdsel_n  : 4;  /* bit[24-27]: Move to DX_Static_Reg */
        unsigned int  reserved          : 4;  /* bit[28-31]: --- */
    } reg;
} SOC_HIPACKPHY_IOCTL5_UNION;
#endif
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_rdsel_p_START  (0)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_rdsel_p_END    (2)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_rdsel_n_START  (3)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_rdsel_n_END    (5)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_tdsel_p_START  (6)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_tdsel_p_END    (9)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_tdsel_n_START  (10)
#define SOC_HIPACKPHY_IOCTL5_dqs_ioctl_tdsel_n_END    (13)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_rdsel_p_START   (14)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_rdsel_p_END     (16)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_rdsel_n_START   (17)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_rdsel_n_END     (19)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_tdsel_p_START   (20)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_tdsel_p_END     (23)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_tdsel_n_START   (24)
#define SOC_HIPACKPHY_IOCTL5_dx_ioctl_tdsel_n_END     (27)




/****************************************************************************
                     (2/2) register_DDRPHY_STATIC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_PLLCTRL_UNION
 �ṹ˵��  : AC_PLLCTRL �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x000003C0�����:32
 �Ĵ���˵��: This register specified the timing paramters for PLL in both address /command, and data block.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0            : 6;  /* bit[0-5]  : -- */
        unsigned int  acctl_pll_bp_refpfd   : 1;  /* bit[6]    : Reference to PLL datasheet */
        unsigned int  acctl_pll_bp_refvco   : 1;  /* bit[7]    : Reference to PLL datasheet */
        unsigned int  acctl_pll_enphsel     : 1;  /* bit[8]    : Reference to PLL datasheet
                                                                 PLL 6/2 Phase Selection
                                                                 1: 6 Phase Output
                                                                 0: 2 Phase Output */
        unsigned int  acctl_pll_en_cal      : 1;  /* bit[9]    : Reference to PLL datasheet */
        unsigned int  acctl_pll_initsel     : 1;  /* bit[10]   : Reference to PLL datasheet */
        unsigned int  acctl_pll_lockt_sel   : 1;  /* bit[11]   : Reference to PLL datasheet */
        unsigned int  acctl_pll_fopetestfb  : 1;  /* bit[12]   : Reference to PLL datasheet */
        unsigned int  acctl_pll_fopetestref : 1;  /* bit[13]   : Reference to PLL datasheet */
        unsigned int  acctl_pll_lockin      : 1;  /* bit[14]   : Reference to PLL datasheet */
        unsigned int  reserved_1            : 17; /* bit[15-31]: -- */
    } reg;
} SOC_HIPACKPHY_AC_PLLCTRL_UNION;
#endif
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_bp_refpfd_START    (6)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_bp_refpfd_END      (6)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_bp_refvco_START    (7)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_bp_refvco_END      (7)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_enphsel_START      (8)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_enphsel_END        (8)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_en_cal_START       (9)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_en_cal_END         (9)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_initsel_START      (10)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_initsel_END        (10)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_lockt_sel_START    (11)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_lockt_sel_END      (11)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_fopetestfb_START   (12)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_fopetestfb_END     (12)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_fopetestref_START  (13)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_fopetestref_END    (13)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_lockin_START       (14)
#define SOC_HIPACKPHY_AC_PLLCTRL_acctl_pll_lockin_END         (14)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_PHYCTRL0_UNION
 �ṹ˵��  : AC_PHYCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x0013F3FD�����:32
 �Ĵ���˵��: PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_odtoen            : 1;  /* bit[0]    :  */
        unsigned int  reserved_0              : 1;  /* bit[1]    :  */
        unsigned int  acctl_cmdoen            : 8;  /* bit[2-9]  :  */
        unsigned int  reserved_1              : 2;  /* bit[10-11]:  */
        unsigned int  acctl_ckoen             : 1;  /* bit[12]   :  */
        unsigned int  acctl_ckeoen            : 2;  /* bit[13-14]:  */
        unsigned int  acctl_csoen             : 2;  /* bit[15-16]:  */
        unsigned int  acctl_resetoen          : 1;  /* bit[17]   :  */
        unsigned int  lpddr_mode              : 1;  /* bit[18]   : 0: lpddr3e mode
                                                                   1: lpddr4 mode */
        unsigned int  lpbk_addr_v_sel         : 1;  /* bit[19]   : 1: lpbk use addr_v[1:0]
                                                                   0: lpbk use addr[1:0] */
        unsigned int  wfifo_acctl_gcken       : 1;  /* bit[20]   :  */
        unsigned int  wfifo_acctl_passthrough : 1;  /* bit[21]   :  */
        unsigned int  reserved_2              : 10; /* bit[22-31]: -- */
    } reg;
} SOC_HIPACKPHY_AC_PHYCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_odtoen_START             (0)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_odtoen_END               (0)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_cmdoen_START             (2)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_cmdoen_END               (9)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_ckoen_START              (12)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_ckoen_END                (12)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_ckeoen_START             (13)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_ckeoen_END               (14)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_csoen_START              (15)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_csoen_END                (16)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_resetoen_START           (17)
#define SOC_HIPACKPHY_AC_PHYCTRL0_acctl_resetoen_END             (17)
#define SOC_HIPACKPHY_AC_PHYCTRL0_lpddr_mode_START               (18)
#define SOC_HIPACKPHY_AC_PHYCTRL0_lpddr_mode_END                 (18)
#define SOC_HIPACKPHY_AC_PHYCTRL0_lpbk_addr_v_sel_START          (19)
#define SOC_HIPACKPHY_AC_PHYCTRL0_lpbk_addr_v_sel_END            (19)
#define SOC_HIPACKPHY_AC_PHYCTRL0_wfifo_acctl_gcken_START        (20)
#define SOC_HIPACKPHY_AC_PHYCTRL0_wfifo_acctl_gcken_END          (20)
#define SOC_HIPACKPHY_AC_PHYCTRL0_wfifo_acctl_passthrough_START  (21)
#define SOC_HIPACKPHY_AC_PHYCTRL0_wfifo_acctl_passthrough_END    (21)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_IOCTL_UNION
 �ṹ˵��  : AC_IOCTL �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x03FE020A�����:32
 �Ĵ���˵��: IO control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                        : 1;  /* bit[0]    :  */
        unsigned int  acctl_ioctl_diffck_en             : 1;  /* bit[1]    :  */
        unsigned int  acctl_ioctl_aciopldn              : 1;  /* bit[2]    :  */
        unsigned int  acctl_ioctl_genvref_dram_refsel_2 : 1;  /* bit[3]    :  */
        unsigned int  reserved_1                        : 1;  /* bit[4]    :  */
        unsigned int  acctl_ioctl_genvref_dram_refsel_1 : 1;  /* bit[5]    :  */
        unsigned int  reserved_2                        : 1;  /* bit[6]    :  */
        unsigned int  acctl_ioctl_genvref_dram_refsel_0 : 1;  /* bit[7]    :  */
        unsigned int  reserved_3                        : 1;  /* bit[8]    :  */
        unsigned int  acctl_ioctl_genvref_dram_pd       : 1;  /* bit[9]    :  */
        unsigned int  reserved_4                        : 7;  /* bit[10-16]:  */
        unsigned int  ac1t_ioctl_ronsel                 : 3;  /* bit[17-19]:  */
        unsigned int  ac2t_ioctl_ronsel                 : 3;  /* bit[20-22]:  */
        unsigned int  ck_ioctl_ronsel                   : 3;  /* bit[23-25]:  */
        unsigned int  reserved_5                        : 6;  /* bit[26-31]:  */
    } reg;
} SOC_HIPACKPHY_AC_IOCTL_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_diffck_en_START              (1)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_diffck_en_END                (1)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_aciopldn_START               (2)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_aciopldn_END                 (2)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_refsel_2_START  (3)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_refsel_2_END    (3)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_refsel_1_START  (5)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_refsel_1_END    (5)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_refsel_0_START  (7)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_refsel_0_END    (7)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_pd_START        (9)
#define SOC_HIPACKPHY_AC_IOCTL_acctl_ioctl_genvref_dram_pd_END          (9)
#define SOC_HIPACKPHY_AC_IOCTL_ac1t_ioctl_ronsel_START                  (17)
#define SOC_HIPACKPHY_AC_IOCTL_ac1t_ioctl_ronsel_END                    (19)
#define SOC_HIPACKPHY_AC_IOCTL_ac2t_ioctl_ronsel_START                  (20)
#define SOC_HIPACKPHY_AC_IOCTL_ac2t_ioctl_ronsel_END                    (22)
#define SOC_HIPACKPHY_AC_IOCTL_ck_ioctl_ronsel_START                    (23)
#define SOC_HIPACKPHY_AC_IOCTL_ck_ioctl_ronsel_END                      (25)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_PHYCTRL1_UNION
 �ṹ˵��  : AC_PHYCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00A00000�����:32
 �Ĵ���˵��: AC PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0       : 18; /* bit[0-17] :  */
        unsigned int  acctl_pll_testen : 1;  /* bit[18]   :  */
        unsigned int  acctl_pll_init   : 1;  /* bit[19]   :  */
        unsigned int  acctl_pll_cpi    : 3;  /* bit[20-22]:  */
        unsigned int  acctl_pll_sp     : 2;  /* bit[23-24]:  */
        unsigned int  reserved_1       : 1;  /* bit[25]   :  */
        unsigned int  acctl_pll_lt     : 2;  /* bit[26-27]:  */
        unsigned int  reserved_2       : 4;  /* bit[28-31]:  */
    } reg;
} SOC_HIPACKPHY_AC_PHYCTRL1_UNION;
#endif
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_testen_START  (18)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_testen_END    (18)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_init_START    (19)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_init_END      (19)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_cpi_START     (20)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_cpi_END       (22)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_sp_START      (23)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_sp_END        (24)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_lt_START      (26)
#define SOC_HIPACKPHY_AC_PHYCTRL1_acctl_pll_lt_END        (27)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_UNION
 �ṹ˵��  : AC_PHYPLLCTRL_AC �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x0000000A�����:32
 �Ĵ���˵��: PHY PLL control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_pll_test : 6;  /* bit[0-5] : AC PLL test mode
                                                         1: Test mode
                                                         0: Normal mode */
        unsigned int  reserved       : 25; /* bit[6-30]:  */
        unsigned int  acctl_pll_lock : 1;  /* bit[31]  : AC PLL LOCK signal
                                                         1: Locked
                                                         0: Not Locked */
    } reg;
} SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_UNION;
#endif
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_acctl_pll_test_START  (0)
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_acctl_pll_test_END    (5)
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_acctl_pll_lock_START  (31)
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_AC_acctl_pll_lock_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_IOCTL1_UNION
 �ṹ˵��  : AC_IOCTL1 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x03140F0F�����:32
 �Ĵ���˵��: PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_ioctl_genvref_range_2      : 4;  /* bit[0-3]  :  */
        unsigned int  reserved_0                       : 4;  /* bit[4-7]  :  */
        unsigned int  acctl_ioctl_genvref_pd           : 4;  /* bit[8-11] :  */
        unsigned int  reserved_1                       : 6;  /* bit[12-17]:  */
        unsigned int  acctl_ioctl_genvref_dram_range_2 : 1;  /* bit[18]   :  */
        unsigned int  reserved_2                       : 1;  /* bit[19]   :  */
        unsigned int  acctl_ioctl_genvref_dram_range_1 : 1;  /* bit[20]   :  */
        unsigned int  reserved_3                       : 1;  /* bit[21]   :  */
        unsigned int  acctl_ioctl_genvref_dram_range_0 : 1;  /* bit[22]   :  */
        unsigned int  reserved_4                       : 1;  /* bit[23]   :  */
        unsigned int  acctl_zcal_vbias_n               : 2;  /* bit[24-25]:  */
        unsigned int  acctl_zcal_vbias_p               : 2;  /* bit[26-27]:  */
        unsigned int  reserved_5                       : 4;  /* bit[28-31]:  */
    } reg;
} SOC_HIPACKPHY_AC_IOCTL1_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_range_2_START       (0)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_range_2_END         (3)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_pd_START            (8)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_pd_END              (11)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_dram_range_2_START  (18)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_dram_range_2_END    (18)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_dram_range_1_START  (20)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_dram_range_1_END    (20)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_dram_range_0_START  (22)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_ioctl_genvref_dram_range_0_END    (22)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_zcal_vbias_n_START                (24)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_zcal_vbias_n_END                  (25)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_zcal_vbias_p_START                (26)
#define SOC_HIPACKPHY_AC_IOCTL1_acctl_zcal_vbias_p_END                  (27)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_IOCTL2_UNION
 �ṹ˵��  : AC_IOCTL2 �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x0F0003C0�����:32
 �Ĵ���˵��: PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_ioctl_genvref_range_0  : 4;  /* bit[0-3]  :  */
        unsigned int  reserved_0                   : 2;  /* bit[4-5]  :  */
        unsigned int  acctl_ioctl_genvref_range_1  : 4;  /* bit[6-9]  :  */
        unsigned int  reserved_1                   : 2;  /* bit[10-11]:  */
        unsigned int  acctl_ioctl_genvref_refsel_0 : 4;  /* bit[12-15]:  */
        unsigned int  reserved_2                   : 2;  /* bit[16-17]:  */
        unsigned int  acctl_ioctl_genvref_refsel_1 : 4;  /* bit[18-21]:  */
        unsigned int  reserved_3                   : 2;  /* bit[22-23]:  */
        unsigned int  acctl_ioctl_genvref_refsel_2 : 4;  /* bit[24-27]:  */
        unsigned int  vref_lpbkmode                : 2;  /* bit[28-29]: Host VREF Selections
                                                                        This field together with the DX_Static_Register/IOCTL2.dq_vref_sel select the VREF value applied to the I/O cells.
                                                                        {vref_lpbkmode[0], IOCTL2.dq_vref_sel}
                                                                        2'b00 : Select the VREF value from this registers.
                                                                        2'b01 : Select the VREF value from the HVREFT_STATUS.vrftres_hvref (Byte lane 0)
                                                                        2'b1X: Select the VREF value from the AHVREFT_STATUS.vrftres_ahvref.
                                                                        The MSB of this register is not used, and reserved for future used. */
        unsigned int  reserved_4                   : 2;  /* bit[30-31]:  */
    } reg;
} SOC_HIPACKPHY_AC_IOCTL2_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_range_0_START   (0)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_range_0_END     (3)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_range_1_START   (6)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_range_1_END     (9)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_refsel_0_START  (12)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_refsel_0_END    (15)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_refsel_1_START  (18)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_refsel_1_END    (21)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_refsel_2_START  (24)
#define SOC_HIPACKPHY_AC_IOCTL2_acctl_ioctl_genvref_refsel_2_END    (27)
#define SOC_HIPACKPHY_AC_IOCTL2_vref_lpbkmode_START                 (28)
#define SOC_HIPACKPHY_AC_IOCTL2_vref_lpbkmode_END                   (29)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_UNION
 �ṹ˵��  : AC_PHYPLLCTRL_DX3 �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PHY PLL control register 3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_phazmeter_in     : 16; /* bit[0-15] :  */
        unsigned int  acctl_phazmeter_status : 16; /* bit[16-31]:  */
    } reg;
} SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_UNION;
#endif
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_acctl_phazmeter_in_START      (0)
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_acctl_phazmeter_in_END        (15)
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_acctl_phazmeter_status_START  (16)
#define SOC_HIPACKPHY_AC_PHYPLLCTRL_DX3_acctl_phazmeter_status_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACCMDBDL0_UNION
 �ṹ˵��  : AC_ACCMDBDL0 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_odt_bdl  : 7;  /* bit[0-6]  : Bit delay line setting of ODT0 */
        unsigned int  reserved_0     : 9;  /* bit[7-15] : -- */
        unsigned int  acctl_odt1_bdl : 7;  /* bit[16-22]: Bit delay line setting of ODT1 */
        unsigned int  reserved_1     : 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_AC_ACCMDBDL0_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACCMDBDL0_acctl_odt_bdl_START   (0)
#define SOC_HIPACKPHY_AC_ACCMDBDL0_acctl_odt_bdl_END     (6)
#define SOC_HIPACKPHY_AC_ACCMDBDL0_acctl_odt1_bdl_START  (16)
#define SOC_HIPACKPHY_AC_ACCMDBDL0_acctl_odt1_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACCMDBDL2_UNION
 �ṹ˵��  : AC_ACCMDBDL2 �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_reset_bdl : 7;  /* bit[0-6] : Bit delay line setting of RESET */
        unsigned int  reserved        : 25; /* bit[7-31]: -- */
    } reg;
} SOC_HIPACKPHY_AC_ACCMDBDL2_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACCMDBDL2_acctl_reset_bdl_START  (0)
#define SOC_HIPACKPHY_AC_ACCMDBDL2_acctl_reset_bdl_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACCMDBDL4_UNION
 �ṹ˵��  : AC_ACCMDBDL4 �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC command bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_cke_bdl  : 7;  /* bit[0-6]  : Bit delay line setting of CKE0 */
        unsigned int  reserved_0     : 9;  /* bit[7-15] : -- */
        unsigned int  acctl_cke1_bdl : 7;  /* bit[16-22]: Bit delay line setting of CKE1 */
        unsigned int  reserved_1     : 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_AC_ACCMDBDL4_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACCMDBDL4_acctl_cke_bdl_START   (0)
#define SOC_HIPACKPHY_AC_ACCMDBDL4_acctl_cke_bdl_END     (6)
#define SOC_HIPACKPHY_AC_ACCMDBDL4_acctl_cke1_bdl_START  (16)
#define SOC_HIPACKPHY_AC_ACCMDBDL4_acctl_cke1_bdl_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACCLKBDL_UNION
 �ṹ˵��  : AC_ACCLKBDL �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC clock bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_dramclk0_bdl : 7;  /* bit[0-6]  :  */
        unsigned int  reserved_0         : 1;  /* bit[7]    : -- */
        unsigned int  acctl_dramclk1_bdl : 7;  /* bit[8-14] :  */
        unsigned int  reserved_1         : 1;  /* bit[15]   :  */
        unsigned int  acctl_refclk_bdl   : 5;  /* bit[16-20]: Bit delay line setting of REFCLK */
        unsigned int  reserved_2         : 3;  /* bit[21-23]:  */
        unsigned int  acctl_fbclk_bdl    : 5;  /* bit[24-28]: Bit delay line setting of FBCLK */
        unsigned int  reserved_3         : 3;  /* bit[29-31]: -- */
    } reg;
} SOC_HIPACKPHY_AC_ACCLKBDL_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_dramclk0_bdl_START  (0)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_dramclk0_bdl_END    (6)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_dramclk1_bdl_START  (8)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_dramclk1_bdl_END    (14)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_refclk_bdl_START    (16)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_refclk_bdl_END      (20)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_fbclk_bdl_START     (24)
#define SOC_HIPACKPHY_AC_ACCLKBDL_acctl_fbclk_bdl_END       (28)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYCTL0_UNION
 �ṹ˵��  : AC_ACPHYCTL0 �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x28002010�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                    : 3;  /* bit[0-2]  : PHY control registers. */
        unsigned int  acctl_dramclk_h               : 1;  /* bit[3]    : PHY control registers. */
        unsigned int  acctl_dramclk_l               : 1;  /* bit[4]    : PHY control registers. */
        unsigned int  acctl_lvdqclkdiv2             : 1;  /* bit[5]    : PHY control registers. */
        unsigned int  acctl_bufphyclk_div2          : 1;  /* bit[6]    : PHY control registers. */
        unsigned int  acctl_byp_clk_gated_dis       : 1;  /* bit[7]    : AC clock gated disable in bypass mode.
                                                                         0: turn off clocks in bypass mode (default)
                                                                         1: turn on clocks in bypass mode */
        unsigned int  acctl_byp_ck90_cmd_code       : 18; /* bit[8-25] : Only bit[7:1] are valid. Used as {bit[7:1],1'b1}. The bit[8] is useless. */
        unsigned int  acctl_reg_reset_pin_sync_mode : 1;  /* bit[26]   :  */
        unsigned int  acctl_reg_sel_pos_rx          : 1;  /* bit[27]   :  */
        unsigned int  acctl_ppfifo_ptr_en           : 1;  /* bit[28]   :  */
        unsigned int  acctl_sync_ppfifo_ptr         : 1;  /* bit[29]   :  */
        unsigned int  reserved_1                    : 2;  /* bit[30-31]: -- */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL0_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_dramclk_h_START                (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_dramclk_h_END                  (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_dramclk_l_START                (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_dramclk_l_END                  (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_lvdqclkdiv2_START              (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_lvdqclkdiv2_END                (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_bufphyclk_div2_START           (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_bufphyclk_div2_END             (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_byp_clk_gated_dis_START        (7)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_byp_clk_gated_dis_END          (7)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_byp_ck90_cmd_code_START        (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_byp_ck90_cmd_code_END          (25)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_reg_reset_pin_sync_mode_START  (26)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_reg_reset_pin_sync_mode_END    (26)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_reg_sel_pos_rx_START           (27)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_reg_sel_pos_rx_END             (27)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_ppfifo_ptr_en_START            (28)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_ppfifo_ptr_en_END              (28)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_sync_ppfifo_ptr_START          (29)
#define SOC_HIPACKPHY_AC_ACPHYCTL0_acctl_sync_ppfifo_ptr_END            (29)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYCTL1_UNION
 �ṹ˵��  : AC_ACPHYCTL1 �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000001�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_dram1sel_reset : 1;  /* bit[0]    : PHY control registers. */
        unsigned int  acctl_dram1sel_cs    : 1;  /* bit[1]    : PHY control registers. */
        unsigned int  acctl_dram1sel_cke   : 1;  /* bit[2]    : PHY control registers. */
        unsigned int  acctl_dram1sel_odt   : 1;  /* bit[3]    : PHY control registers. */
        unsigned int  acctl_dram1sel_ras   : 1;  /* bit[4]    : PHY control registers. */
        unsigned int  acctl_dram1sel_cas   : 1;  /* bit[5]    : dlyline_soft_reset
                                                                set 1 to reset dlyline
                                                                1��reset 
                                                                0��not reset */
        unsigned int  acctl_dram1sel_we    : 1;  /* bit[6]    : dbg_pll_sel��
                                                                1��ѡ��pll debug�źŵ�IO
                                                                0��ѡ��phy debug�źŵ�IO */
        unsigned int  reserved_0           : 1;  /* bit[7]    : -- */
        unsigned int  acctl_dram1sel_ba    : 3;  /* bit[8-10] : PHY control registers. */
        unsigned int  reserved_1           : 5;  /* bit[11-15]: -- */
        unsigned int  acctl_dram1sel_addr  : 16; /* bit[16-31]: PHY control registers. */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL1_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_reset_START  (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_reset_END    (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_cs_START     (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_cs_END       (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_cke_START    (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_cke_END      (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_odt_START    (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_odt_END      (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_ras_START    (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_ras_END      (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_cas_START    (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_cas_END      (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_we_START     (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_we_END       (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_ba_START     (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_ba_END       (10)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_addr_START   (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL1_acctl_dram1sel_addr_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYCTL2_UNION
 �ṹ˵��  : AC_ACPHYCTL2 �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_sdrsel_reset : 1;  /* bit[0]    : PHY control registers. */
        unsigned int  acctl_sdrsel_cs    : 1;  /* bit[1]    : PHY control registers. */
        unsigned int  acctl_sdrsel_cke   : 1;  /* bit[2]    : PHY control registers. */
        unsigned int  acctl_sdrsel_odt   : 1;  /* bit[3]    : PHY control registers. */
        unsigned int  acctl_sdrsel_ras   : 1;  /* bit[4]    : PHY control registers. */
        unsigned int  acctl_sdrsel_cas   : 1;  /* bit[5]    : PHY control registers. */
        unsigned int  acctl_sdrsel_we    : 1;  /* bit[6]    : PHY control registers. */
        unsigned int  reserved_0         : 1;  /* bit[7]    : -- */
        unsigned int  acctl_sdrsel_ba    : 3;  /* bit[8-10] : PHY control registers. */
        unsigned int  reserved_1         : 5;  /* bit[11-15]: -- */
        unsigned int  acctl_sdrsel_addr  : 16; /* bit[16-31]: PHY control registers. */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL2_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_reset_START  (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_reset_END    (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_cs_START     (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_cs_END       (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_cke_START    (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_cke_END      (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_odt_START    (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_odt_END      (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_ras_START    (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_ras_END      (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_cas_START    (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_cas_END      (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_we_START     (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_we_END       (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_ba_START     (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_ba_END       (10)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_addr_START   (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL2_acctl_sdrsel_addr_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYCTL3_UNION
 �ṹ˵��  : AC_ACPHYCTL3 �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_posedge_reset : 1;  /* bit[0]    : PHY control registers. */
        unsigned int  acctl_posedge_cs    : 1;  /* bit[1]    : PHY control registers. */
        unsigned int  acctl_posedge_cke   : 1;  /* bit[2]    : PHY control registers. */
        unsigned int  acctl_posedge_odt   : 1;  /* bit[3]    : PHY control registers. */
        unsigned int  acctl_posedge_ras   : 1;  /* bit[4]    : PHY control registers. */
        unsigned int  acctl_posedge_cas   : 1;  /* bit[5]    : PHY control registers. */
        unsigned int  acctl_posedge_we    : 1;  /* bit[6]    : PHY control registers. */
        unsigned int  reserved_0          : 1;  /* bit[7]    : -- */
        unsigned int  acctl_posedge_ba    : 3;  /* bit[8-10] : PHY control registers. */
        unsigned int  reserved_1          : 5;  /* bit[11-15]: -- */
        unsigned int  acctl_posedge_addr  : 16; /* bit[16-31]: PHY control registers. */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL3_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_reset_START  (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_reset_END    (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_cs_START     (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_cs_END       (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_cke_START    (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_cke_END      (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_odt_START    (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_odt_END      (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_ras_START    (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_ras_END      (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_cas_START    (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_cas_END      (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_we_START     (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_we_END       (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_ba_START     (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_ba_END       (10)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_addr_START   (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL3_acctl_posedge_addr_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYCTL4_UNION
 �ṹ˵��  : AC_ACPHYCTL4 �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_timing2t_reset : 1;  /* bit[0]    : PHY control registers. */
        unsigned int  acctl_timing2t_cs    : 1;  /* bit[1]    : PHY control registers. */
        unsigned int  acctl_timing2t_cke   : 1;  /* bit[2]    : PHY control registers. */
        unsigned int  acctl_timing2t_odt   : 1;  /* bit[3]    : PHY control registers. */
        unsigned int  acctl_timing2t_ras   : 1;  /* bit[4]    : PHY control registers. */
        unsigned int  acctl_timing2t_cas   : 1;  /* bit[5]    : PHY control registers. */
        unsigned int  acctl_timing2t_we    : 1;  /* bit[6]    : PHY control registers. */
        unsigned int  reserved_0           : 1;  /* bit[7]    : -- */
        unsigned int  acctl_timing2t_ba    : 3;  /* bit[8-10] : PHY control registers. */
        unsigned int  reserved_1           : 5;  /* bit[11-15]: -- */
        unsigned int  acctl_timing2t_addr  : 16; /* bit[16-31]: PHY control registers. */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL4_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_reset_START  (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_reset_END    (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_cs_START     (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_cs_END       (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_cke_START    (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_cke_END      (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_odt_START    (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_odt_END      (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_ras_START    (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_ras_END      (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_cas_START    (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_cas_END      (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_we_START     (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_we_END       (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_ba_START     (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_ba_END       (10)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_addr_START   (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL4_acctl_timing2t_addr_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYCTL5_UNION
 �ṹ˵��  : AC_ACPHYCTL5 �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_clk1x_dramclk0 : 3;  /* bit[0-2]  : PHY control registers. */
        unsigned int  reserved_0           : 1;  /* bit[3]    :  */
        unsigned int  acctl_clk1x_dramclk1 : 3;  /* bit[4-6]  : PHY control registers. */
        unsigned int  reserved_1           : 1;  /* bit[7]    :  */
        unsigned int  reserved_2           : 3;  /* bit[8-10] : PHY control registers. */
        unsigned int  reserved_3           : 1;  /* bit[11]   :  */
        unsigned int  acctl_clk1x_cmd2t    : 3;  /* bit[12-14]: PHY control registers. */
        unsigned int  reserved_4           : 1;  /* bit[15]   :  */
        unsigned int  acctl_clk1x_cmd1t    : 3;  /* bit[16-18]: PHY control registers. */
        unsigned int  reserved_5           : 1;  /* bit[19]   :  */
        unsigned int  acctl_clk1x_mclk     : 3;  /* bit[20-22]: PHY control registers. */
        unsigned int  reserved_6           : 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL5_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_dramclk0_START  (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_dramclk0_END    (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_dramclk1_START  (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_dramclk1_END    (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_cmd2t_START     (12)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_cmd2t_END       (14)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_cmd1t_START     (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_cmd1t_END       (18)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_mclk_START      (20)
#define SOC_HIPACKPHY_AC_ACPHYCTL5_acctl_clk1x_mclk_END        (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYCTL6_UNION
 �ṹ˵��  : AC_ACPHYCTL6 �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_clk2x_dramclk0 : 3;  /* bit[0-2]  : PHY control registers. */
        unsigned int  reserved_0           : 1;  /* bit[3]    :  */
        unsigned int  acctl_clk2x_dramclk1 : 3;  /* bit[4-6]  : PHY control registers. */
        unsigned int  reserved_1           : 1;  /* bit[7]    :  */
        unsigned int  reserved_2           : 3;  /* bit[8-10] : PHY control registers. */
        unsigned int  reserved_3           : 1;  /* bit[11]   :  */
        unsigned int  acctl_clk2x_cmd2t    : 3;  /* bit[12-14]: PHY control registers. */
        unsigned int  reserved_4           : 1;  /* bit[15]   :  */
        unsigned int  acctl_clk2x_cmd1t    : 3;  /* bit[16-18]: PHY control registers. */
        unsigned int  reserved_5           : 1;  /* bit[19]   :  */
        unsigned int  acctl_clk2x_mclk     : 3;  /* bit[20-22]: PHY control registers. */
        unsigned int  reserved_6           : 9;  /* bit[23-31]: -- */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL6_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_dramclk0_START  (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_dramclk0_END    (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_dramclk1_START  (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_dramclk1_END    (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_cmd2t_START     (12)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_cmd2t_END       (14)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_cmd1t_START     (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_cmd1t_END       (18)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_mclk_START      (20)
#define SOC_HIPACKPHY_AC_ACPHYCTL6_acctl_clk2x_mclk_END        (22)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYCTL7_UNION
 �ṹ˵��  : AC_ACPHYCTL7 �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00800000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 3;  /* bit[0-2]  :  */
        unsigned int  acctl_ck0p_mclk      : 3;  /* bit[3-5]  :  */
        unsigned int  acctl_ck1p_dclk0     : 3;  /* bit[6-8]  : Configure DRAM CK0 Clock Phase from PLL 1 tap : 1/16 T */
        unsigned int  acctl_ck2p_dclk1     : 3;  /* bit[9-11] : Configure DRAM CK1 Clock Phase from PLL 1 tap : 1/16 T */
        unsigned int  acctl_ck3p_cmd1t     : 3;  /* bit[12-14]:  */
        unsigned int  reserved_1           : 8;  /* bit[15-22]:  */
        unsigned int  acctl_halft_cmd1t    : 1;  /* bit[23]   :  */
        unsigned int  acctl_halft_dramclk1 : 1;  /* bit[24]   :  */
        unsigned int  acctl_halft_dramclk0 : 1;  /* bit[25]   :  */
        unsigned int  cmd1t2t_sel          : 1;  /* bit[26]   : 1: cmd2t
                                                                0: cmd1t */
        unsigned int  reserved_2           : 5;  /* bit[27-31]:  */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL7_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck0p_mclk_START       (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck0p_mclk_END         (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck1p_dclk0_START      (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck1p_dclk0_END        (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck2p_dclk1_START      (9)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck2p_dclk1_END        (11)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck3p_cmd1t_START      (12)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_ck3p_cmd1t_END        (14)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_halft_cmd1t_START     (23)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_halft_cmd1t_END       (23)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_halft_dramclk1_START  (24)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_halft_dramclk1_END    (24)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_halft_dramclk0_START  (25)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_acctl_halft_dramclk0_END    (25)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_cmd1t2t_sel_START           (26)
#define SOC_HIPACKPHY_AC_ACPHYCTL7_cmd1t2t_sel_END             (26)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACDEBUG_UNION
 �ṹ˵��  : AC_ACDEBUG �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is for PHY debug only.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acdbg_rdcnt          : 6;  /* bit[0-5]  :  */
        unsigned int  reserved_0           : 2;  /* bit[6-7]  :  */
        unsigned int  acctl_deskew_regread : 1;  /* bit[8]    :  */
        unsigned int  reserved_1           : 7;  /* bit[9-15] :  */
        unsigned int  acdbg_config         : 4;  /* bit[16-19]:  */
        unsigned int  reserved_2           : 12; /* bit[20-31]:  */
    } reg;
} SOC_HIPACKPHY_AC_ACDEBUG_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACDEBUG_acdbg_rdcnt_START           (0)
#define SOC_HIPACKPHY_AC_ACDEBUG_acdbg_rdcnt_END             (5)
#define SOC_HIPACKPHY_AC_ACDEBUG_acctl_deskew_regread_START  (8)
#define SOC_HIPACKPHY_AC_ACDEBUG_acctl_deskew_regread_END    (8)
#define SOC_HIPACKPHY_AC_ACDEBUG_acdbg_config_START          (16)
#define SOC_HIPACKPHY_AC_ACDEBUG_acdbg_config_END            (19)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYRSVDC_UNION
 �ṹ˵��  : AC_ACPHYRSVDC �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0xFFFF0000�����:32
 �Ĵ���˵��: AC block PHY reserved control pins. This register is for PHY control and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_rsvdctrl : 32; /* bit[0-31]: Reserved registers for the future. */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYRSVDC_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYRSVDC_acctl_rsvdctrl_START  (0)
#define SOC_HIPACKPHY_AC_ACPHYRSVDC_acctl_rsvdctrl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYRSVDS_UNION
 �ṹ˵��  : AC_ACPHYRSVDS �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY reserved control pins. This register is for PHY control and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_rsvdstatus : 32; /* bit[0-31]: Reserved registers for the future. */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYRSVDS_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYRSVDS_acctl_rsvdstatus_START  (0)
#define SOC_HIPACKPHY_AC_ACPHYRSVDS_acctl_rsvdstatus_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYDCC_UNION
 �ṹ˵��  : AC_ACPHYDCC �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x00000020�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_dq1_dcc       : 3;  /* bit[0-2]  : acctl_byp_ck90_cmd_code_shadow[2:0] */
        unsigned int  acctl_dq0_dcc       : 3;  /* bit[3-5]  : acctl_byp_ck90_cmd_code_shadow[5:3] */
        unsigned int  acctl_dqs1_dcc      : 3;  /* bit[6-8]  : acctl_byp_ck90_cmd_code_shadow[8:6] */
        unsigned int  acctl_dqs0_dcc      : 3;  /* bit[9-11] : acctl_byp_ck90_cmd_code_shadow[11:9] */
        unsigned int  acctl_mclk_dcc      : 3;  /* bit[12-14]: acctl_byp_ck90_cmd_code_shadow[14:12] */
        unsigned int  reserved_0          : 1;  /* bit[15]   :  */
        unsigned int  acctl_dq1_dcc_byt1  : 3;  /* bit[16-18]: acctl_byp_ck90_cmd_code_shadow[17:15] */
        unsigned int  acctl_dq0_dcc_byt1  : 3;  /* bit[19-21]:  */
        unsigned int  acctl_dqs1_dcc_byt1 : 3;  /* bit[22-24]:  */
        unsigned int  acctl_dqs0_dcc_byt1 : 3;  /* bit[25-27]:  */
        unsigned int  acctl_mclk_dcc_byt1 : 3;  /* bit[28-30]:  */
        unsigned int  reserved_1          : 1;  /* bit[31]   :  */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYDCC_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq1_dcc_START        (0)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq1_dcc_END          (2)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq0_dcc_START        (3)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq0_dcc_END          (5)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs1_dcc_START       (6)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs1_dcc_END         (8)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs0_dcc_START       (9)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs0_dcc_END         (11)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_mclk_dcc_START       (12)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_mclk_dcc_END         (14)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq1_dcc_byt1_START   (16)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq1_dcc_byt1_END     (18)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq0_dcc_byt1_START   (19)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dq0_dcc_byt1_END     (21)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs1_dcc_byt1_START  (22)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs1_dcc_byt1_END    (24)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs0_dcc_byt1_START  (25)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_dqs0_dcc_byt1_END    (27)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_mclk_dcc_byt1_START  (28)
#define SOC_HIPACKPHY_AC_ACPHYDCC_acctl_mclk_dcc_byt1_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYCTL9_UNION
 �ṹ˵��  : AC_ACPHYCTL9 �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_sdrsel_cs1    : 1;  /* bit[0]    :  */
        unsigned int  acctl_sdrsel_cke1   : 1;  /* bit[1]    :  */
        unsigned int  acctl_sdrsel_odt1   : 1;  /* bit[2]    :  */
        unsigned int  acctl_posedge_cs1   : 1;  /* bit[3]    :  */
        unsigned int  acctl_posedge_cke1  : 1;  /* bit[4]    :  */
        unsigned int  acctl_posedge_odt1  : 1;  /* bit[5]    :  */
        unsigned int  acctl_dram1sel_cs1  : 1;  /* bit[6]    :  */
        unsigned int  acctl_dram1sel_cke1 : 1;  /* bit[7]    :  */
        unsigned int  acctl_dram1sel_odt1 : 1;  /* bit[8]    :  */
        unsigned int  acctl_timing2t_cs1  : 1;  /* bit[9]    :  */
        unsigned int  acctl_timing2t_cke1 : 1;  /* bit[10]   :  */
        unsigned int  acctl_timing2t_odt1 : 1;  /* bit[11]   :  */
        unsigned int  reserved            : 20; /* bit[12-31]:  */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL9_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_sdrsel_cs1_START     (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_sdrsel_cs1_END       (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_sdrsel_cke1_START    (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_sdrsel_cke1_END      (1)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_sdrsel_odt1_START    (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_sdrsel_odt1_END      (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_posedge_cs1_START    (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_posedge_cs1_END      (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_posedge_cke1_START   (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_posedge_cke1_END     (4)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_posedge_odt1_START   (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_posedge_odt1_END     (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_dram1sel_cs1_START   (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_dram1sel_cs1_END     (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_dram1sel_cke1_START  (7)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_dram1sel_cke1_END    (7)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_dram1sel_odt1_START  (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_dram1sel_odt1_END    (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_timing2t_cs1_START   (9)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_timing2t_cs1_END     (9)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_timing2t_cke1_START  (10)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_timing2t_cke1_END    (10)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_timing2t_odt1_START  (11)
#define SOC_HIPACKPHY_AC_ACPHYCTL9_acctl_timing2t_odt1_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYCTL10_UNION
 �ṹ˵��  : AC_ACPHYCTL10 �Ĵ����ṹ���塣��ַƫ����:0x09C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_clk1x_dramclk0_byt1 : 3;  /* bit[0-2]  : PHY control registers. */
        unsigned int  acctl_clk1x_dramclk1_byt1 : 3;  /* bit[3-5]  : PHY control registers. */
        unsigned int  acctl_clk1x_cmd2t_byt1    : 3;  /* bit[6-8]  : PHY control registers. */
        unsigned int  acctl_clk1x_cmd1t_byt1    : 3;  /* bit[9-11] : PHY control registers. */
        unsigned int  acctl_clk1x_mclk_byt1     : 3;  /* bit[12-14]: PHY control registers. */
        unsigned int  reserved_0                : 1;  /* bit[15]   :  */
        unsigned int  acctl_clk2x_dramclk0_byt1 : 3;  /* bit[16-18]: PHY control registers. */
        unsigned int  acctl_clk2x_dramclk1_byt1 : 3;  /* bit[19-21]: PHY control registers. */
        unsigned int  acctl_clk2x_cmd2t_byt1    : 3;  /* bit[22-24]: PHY control registers. */
        unsigned int  acctl_clk2x_cmd1t_byt1    : 3;  /* bit[25-27]: PHY control registers. */
        unsigned int  acctl_clk2x_mclk_byt1     : 3;  /* bit[28-30]: PHY control registers. */
        unsigned int  reserved_1                : 1;  /* bit[31]   : -- */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL10_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_dramclk0_byt1_START  (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_dramclk0_byt1_END    (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_dramclk1_byt1_START  (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_dramclk1_byt1_END    (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_cmd2t_byt1_START     (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_cmd2t_byt1_END       (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_cmd1t_byt1_START     (9)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_cmd1t_byt1_END       (11)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_mclk_byt1_START      (12)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk1x_mclk_byt1_END        (14)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_dramclk0_byt1_START  (16)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_dramclk0_byt1_END    (18)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_dramclk1_byt1_START  (19)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_dramclk1_byt1_END    (21)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_cmd2t_byt1_START     (22)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_cmd2t_byt1_END       (24)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_cmd1t_byt1_START     (25)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_cmd1t_byt1_END       (27)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_mclk_byt1_START      (28)
#define SOC_HIPACKPHY_AC_ACPHYCTL10_acctl_clk2x_mclk_byt1_END        (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYCTL11_UNION
 �ṹ˵��  : AC_ACPHYCTL11 �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_ck1p_dclk0_byt1      : 3;  /* bit[0-2]  : Byte 1 DRAM CK0 Clock Phase from PLL 1 */
        unsigned int  acctl_ck2p_dclk1_byt1      : 3;  /* bit[3-5]  : Byte 1 DRAM CK1 Clock Phase from PLL 1 */
        unsigned int  acctl_ck3p_cmd1t_byt1      : 3;  /* bit[6-8]  : Byte 1 */
        unsigned int  acctl_ck4p_cmd2t_byt1      : 3;  /* bit[9-11] : Byte 1 CA Phase */
        unsigned int  reserved_0                 : 11; /* bit[12-22]:  */
        unsigned int  acctl_reg_byone_cmdr1t_sel : 1;  /* bit[23]   : CTL_CS to DDR_CS latency
                                                                      0: 2T
                                                                      1: 1T */
        unsigned int  acctl_reg_cmd_byt1_phsel   : 4;  /* bit[24-27]:  */
        unsigned int  reserved_1                 : 4;  /* bit[28-31]: -- */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYCTL11_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck1p_dclk0_byt1_START       (0)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck1p_dclk0_byt1_END         (2)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck2p_dclk1_byt1_START       (3)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck2p_dclk1_byt1_END         (5)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck3p_cmd1t_byt1_START       (6)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck3p_cmd1t_byt1_END         (8)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck4p_cmd2t_byt1_START       (9)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_ck4p_cmd2t_byt1_END         (11)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_reg_byone_cmdr1t_sel_START  (23)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_reg_byone_cmdr1t_sel_END    (23)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_reg_cmd_byt1_phsel_START    (24)
#define SOC_HIPACKPHY_AC_ACPHYCTL11_acctl_reg_cmd_byt1_phsel_END      (27)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_IOCTL3_UNION
 �ṹ˵��  : AC_IOCTL3 �Ĵ����ṹ���塣��ַƫ����:0x0A4����ֵ:0x03F100F4�����:32
 �Ĵ���˵��: IO control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ac1t_ioctl_rdsel_p     : 4;  /* bit[0-3]  :  */
        unsigned int  ac1t_ioctl_rdsel_n     : 4;  /* bit[4-7]  :  */
        unsigned int  ac1t_ioctl_tdsel_p     : 4;  /* bit[8-11] :  */
        unsigned int  ac1t_ioctl_tdsel_n     : 4;  /* bit[12-15]:  */
        unsigned int  acctl_ioctl_zq_rx_mode : 2;  /* bit[16-17]:  */
        unsigned int  ioctl_reset_rx_mode0   : 1;  /* bit[18]   :  */
        unsigned int  ioctl_reset_rx_mode1   : 1;  /* bit[19]   :  */
        unsigned int  ioctl_cs_rx_mode0      : 2;  /* bit[20-21]:  */
        unsigned int  ioctl_cs_rx_mode1      : 2;  /* bit[22-23]:  */
        unsigned int  ioctl_ck_rx_mode0      : 1;  /* bit[24]   :  */
        unsigned int  ioctl_ck_rx_mode1      : 1;  /* bit[25]   :  */
        unsigned int  ioctl_cke_rx_mode0     : 2;  /* bit[26-27]:  */
        unsigned int  ioctl_cke_rx_mode1     : 2;  /* bit[28-29]:  */
        unsigned int  ioctl_odt_rx_mode0     : 1;  /* bit[30]   :  */
        unsigned int  ioctl_odt_rx_mode1     : 1;  /* bit[31]   : --- */
    } reg;
} SOC_HIPACKPHY_AC_IOCTL3_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_rdsel_p_START      (0)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_rdsel_p_END        (3)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_rdsel_n_START      (4)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_rdsel_n_END        (7)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_tdsel_p_START      (8)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_tdsel_p_END        (11)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_tdsel_n_START      (12)
#define SOC_HIPACKPHY_AC_IOCTL3_ac1t_ioctl_tdsel_n_END        (15)
#define SOC_HIPACKPHY_AC_IOCTL3_acctl_ioctl_zq_rx_mode_START  (16)
#define SOC_HIPACKPHY_AC_IOCTL3_acctl_ioctl_zq_rx_mode_END    (17)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_reset_rx_mode0_START    (18)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_reset_rx_mode0_END      (18)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_reset_rx_mode1_START    (19)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_reset_rx_mode1_END      (19)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cs_rx_mode0_START       (20)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cs_rx_mode0_END         (21)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cs_rx_mode1_START       (22)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cs_rx_mode1_END         (23)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_ck_rx_mode0_START       (24)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_ck_rx_mode0_END         (24)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_ck_rx_mode1_START       (25)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_ck_rx_mode1_END         (25)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cke_rx_mode0_START      (26)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cke_rx_mode0_END        (27)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cke_rx_mode1_START      (28)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_cke_rx_mode1_END        (29)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_odt_rx_mode0_START      (30)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_odt_rx_mode0_END        (30)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_odt_rx_mode1_START      (31)
#define SOC_HIPACKPHY_AC_IOCTL3_ioctl_odt_rx_mode1_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_IOCTL4_UNION
 �ṹ˵��  : AC_IOCTL4 �Ĵ����ṹ���塣��ַƫ����:0x0A8����ֵ:0x00F400F4�����:32
 �Ĵ���˵��: IO control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_ioctl_rdsel_p   : 4;  /* bit[0-3]  :  */
        unsigned int  ck_ioctl_rdsel_n   : 4;  /* bit[4-7]  :  */
        unsigned int  ck_ioctl_tdsel_p   : 4;  /* bit[8-11] :  */
        unsigned int  ck_ioctl_tdsel_n   : 4;  /* bit[12-15]:  */
        unsigned int  ac2t_ioctl_rdsel_p : 4;  /* bit[16-19]:  */
        unsigned int  ac2t_ioctl_rdsel_n : 4;  /* bit[20-23]:  */
        unsigned int  ac2t_ioctl_tdsel_p : 4;  /* bit[24-27]:  */
        unsigned int  ac2t_ioctl_tdsel_n : 4;  /* bit[28-31]: --- */
    } reg;
} SOC_HIPACKPHY_AC_IOCTL4_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_rdsel_p_START    (0)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_rdsel_p_END      (3)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_rdsel_n_START    (4)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_rdsel_n_END      (7)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_tdsel_p_START    (8)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_tdsel_p_END      (11)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_tdsel_n_START    (12)
#define SOC_HIPACKPHY_AC_IOCTL4_ck_ioctl_tdsel_n_END      (15)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_rdsel_p_START  (16)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_rdsel_p_END    (19)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_rdsel_n_START  (20)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_rdsel_n_END    (23)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_tdsel_p_START  (24)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_tdsel_p_END    (27)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_tdsel_n_START  (28)
#define SOC_HIPACKPHY_AC_IOCTL4_ac2t_ioctl_tdsel_n_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYDCC1_UNION
 �ṹ˵��  : AC_ACPHYDCC1 �Ĵ����ṹ���塣��ַƫ����:0x0AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_reg_mclk_dcc_v : 5;  /* bit[0-4]  :  */
        unsigned int  acctl_reg_mclk_dcc_h : 5;  /* bit[5-9]  :  */
        unsigned int  acctl_reg_dq0_dcc_v  : 5;  /* bit[10-14]:  */
        unsigned int  acctl_reg_dq0_dcc_h  : 5;  /* bit[15-19]:  */
        unsigned int  acctl_reg_dq1_dcc_v  : 5;  /* bit[20-24]:  */
        unsigned int  acctl_reg_dq1_dcc_h  : 5;  /* bit[25-29]:  */
        unsigned int  reserved             : 2;  /* bit[30-31]:  */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYDCC1_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_mclk_dcc_v_START  (0)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_mclk_dcc_v_END    (4)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_mclk_dcc_h_START  (5)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_mclk_dcc_h_END    (9)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq0_dcc_v_START   (10)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq0_dcc_v_END     (14)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq0_dcc_h_START   (15)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq0_dcc_h_END     (19)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq1_dcc_v_START   (20)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq1_dcc_v_END     (24)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq1_dcc_h_START   (25)
#define SOC_HIPACKPHY_AC_ACPHYDCC1_acctl_reg_dq1_dcc_h_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_ACPHYDCC2_UNION
 �ṹ˵��  : AC_ACPHYDCC2 �Ĵ����ṹ���塣��ַƫ����:0x0B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: AC block PHY control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acctl_reg_dqs0_dcc_h : 5;  /* bit[0-4] :  */
        unsigned int  reserved             : 27; /* bit[5-31]:  */
    } reg;
} SOC_HIPACKPHY_AC_ACPHYDCC2_UNION;
#endif
#define SOC_HIPACKPHY_AC_ACPHYDCC2_acctl_reg_dqs0_dcc_h_START  (0)
#define SOC_HIPACKPHY_AC_ACPHYDCC2_acctl_reg_dqs0_dcc_h_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_IOCTL5_UNION
 �ṹ˵��  : AC_IOCTL5 �Ĵ����ṹ���塣��ַƫ����:0x0B4����ֵ:0xFFFF00F0�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved              : 1;  /* bit[0]    :  */
        unsigned int  ioctl_cs_sp           : 2;  /* bit[1-2]  :  */
        unsigned int  ioctl_ck_sp           : 1;  /* bit[3]    :  */
        unsigned int  ioctl_reset_sp        : 1;  /* bit[4]    :  */
        unsigned int  ioctl_cke_sp          : 2;  /* bit[5-6]  :  */
        unsigned int  ioctl_odt_sp          : 1;  /* bit[7]    :  */
        unsigned int  ioctl_addr_sp         : 6;  /* bit[8-13] :  */
        unsigned int  ioctl_addr_v_sp       : 2;  /* bit[14-15]:  */
        unsigned int  ioctl_addr_rx_mode0   : 6;  /* bit[16-21]:  */
        unsigned int  ioctl_addr_rx_mode1   : 6;  /* bit[22-27]:  */
        unsigned int  ioctl_addr_v_rx_mode0 : 2;  /* bit[28-29]:  */
        unsigned int  ioctl_addr_v_rx_mode1 : 2;  /* bit[30-31]:  */
    } reg;
} SOC_HIPACKPHY_AC_IOCTL5_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_cs_sp_START            (1)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_cs_sp_END              (2)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_ck_sp_START            (3)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_ck_sp_END              (3)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_reset_sp_START         (4)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_reset_sp_END           (4)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_cke_sp_START           (5)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_cke_sp_END             (6)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_odt_sp_START           (7)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_odt_sp_END             (7)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_sp_START          (8)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_sp_END            (13)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_v_sp_START        (14)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_v_sp_END          (15)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_rx_mode0_START    (16)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_rx_mode0_END      (21)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_rx_mode1_START    (22)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_rx_mode1_END      (27)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_v_rx_mode0_START  (28)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_v_rx_mode0_END    (29)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_v_rx_mode1_START  (30)
#define SOC_HIPACKPHY_AC_IOCTL5_ioctl_addr_v_rx_mode1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_AC_IOCTL6_UNION
 �ṹ˵��  : AC_IOCTL6 �Ĵ����ṹ���塣��ַƫ����:0x0B8����ֵ:0x004FFF1D�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ioctl_zcal_lpddr4en   : 1;  /* bit[0]    :  */
        unsigned int  ioctl_reset_lpddr4en  : 1;  /* bit[1]    :  */
        unsigned int  ioctl_cs_lpddr4en     : 2;  /* bit[2-3]  :  */
        unsigned int  ioctl_ck_lpddr4en     : 1;  /* bit[4]    :  */
        unsigned int  ioctl_cke_lpddr4en    : 2;  /* bit[5-6]  :  */
        unsigned int  ioctl_odt_lpddr4en    : 1;  /* bit[7]    :  */
        unsigned int  ioctl_addr_lpddr4en   : 6;  /* bit[8-13] :  */
        unsigned int  ioctl_addr_v_lpddr4en : 2;  /* bit[14-15]:  */
        unsigned int  ioctl_zcal_rdsel_n    : 4;  /* bit[16-19]:  */
        unsigned int  ioctl_zcal_rdsel_p    : 4;  /* bit[20-23]:  */
        unsigned int  ioctl_odtp            : 1;  /* bit[24]   :  */
        unsigned int  ioctl_odtn            : 1;  /* bit[25]   :  */
        unsigned int  ioctl_odtsel          : 3;  /* bit[26-28]:  */
        unsigned int  reserved              : 3;  /* bit[29-31]:  */
    } reg;
} SOC_HIPACKPHY_AC_IOCTL6_UNION;
#endif
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_zcal_lpddr4en_START    (0)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_zcal_lpddr4en_END      (0)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_reset_lpddr4en_START   (1)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_reset_lpddr4en_END     (1)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_cs_lpddr4en_START      (2)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_cs_lpddr4en_END        (3)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_ck_lpddr4en_START      (4)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_ck_lpddr4en_END        (4)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_cke_lpddr4en_START     (5)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_cke_lpddr4en_END       (6)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odt_lpddr4en_START     (7)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odt_lpddr4en_END       (7)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_addr_lpddr4en_START    (8)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_addr_lpddr4en_END      (13)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_addr_v_lpddr4en_START  (14)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_addr_v_lpddr4en_END    (15)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_zcal_rdsel_n_START     (16)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_zcal_rdsel_n_END       (19)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_zcal_rdsel_p_START     (20)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_zcal_rdsel_p_END       (23)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odtp_START             (24)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odtp_END               (24)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odtn_START             (25)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odtn_END               (25)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odtsel_START           (26)
#define SOC_HIPACKPHY_AC_IOCTL6_ioctl_odtsel_END             (28)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_PHYCTRL0_UNION
 �ṹ˵��  : DX_PHYCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x200����ֵ:0x00000000�����:32
 �Ĵ���˵��: PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]:  */
    } reg;
} SOC_HIPACKPHY_DX_PHYCTRL0_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_IOCTL_UNION
 �ṹ˵��  : DX_IOCTL �Ĵ����ṹ���塣��ַƫ����:0x204����ֵ:0x0001FA0C�����:32
 �Ĵ���˵��: IO control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                        : 1;  /* bit[0]    :  */
        unsigned int  dxctl_ioctl_dxiopldn              : 1;  /* bit[1]    :  */
        unsigned int  top_ioctl_odt_oe                  : 1;  /* bit[2]    :  */
        unsigned int  dxctl_ioctl_genvref_dram_refsel_2 : 1;  /* bit[3]    :  */
        unsigned int  reserved_1                        : 1;  /* bit[4]    :  */
        unsigned int  dxctl_ioctl_genvref_dram_refsel_1 : 1;  /* bit[5]    :  */
        unsigned int  reserved_2                        : 1;  /* bit[6]    :  */
        unsigned int  dxctl_ioctl_genvref_dram_refsel_0 : 1;  /* bit[7]    :  */
        unsigned int  reserved_3                        : 1;  /* bit[8]    :  */
        unsigned int  dxctl_ioctl_genvref_dram_pd       : 1;  /* bit[9]    :  */
        unsigned int  reserved_4                        : 1;  /* bit[10]   :  */
        unsigned int  dx_ioctl_ronsel                   : 3;  /* bit[11-13]:  */
        unsigned int  dqs_ioctl_ronsel                  : 3;  /* bit[14-16]:  */
        unsigned int  reserved_5                        : 7;  /* bit[17-23]:  */
        unsigned int  ioctl_dq_odtn                     : 1;  /* bit[24]   :  */
        unsigned int  ioctl_dq_odtp                     : 1;  /* bit[25]   :  */
        unsigned int  ioctl_dqs_odtn                    : 1;  /* bit[26]   :  */
        unsigned int  ioctl_dqs_odtp                    : 1;  /* bit[27]   :  */
        unsigned int  reserved_6                        : 1;  /* bit[28]   :  */
        unsigned int  dqs_ioctl_odtsel                  : 3;  /* bit[29-31]:  */
    } reg;
} SOC_HIPACKPHY_DX_IOCTL_UNION;
#endif
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_dxiopldn_START               (1)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_dxiopldn_END                 (1)
#define SOC_HIPACKPHY_DX_IOCTL_top_ioctl_odt_oe_START                   (2)
#define SOC_HIPACKPHY_DX_IOCTL_top_ioctl_odt_oe_END                     (2)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_refsel_2_START  (3)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_refsel_2_END    (3)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_refsel_1_START  (5)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_refsel_1_END    (5)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_refsel_0_START  (7)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_refsel_0_END    (7)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_pd_START        (9)
#define SOC_HIPACKPHY_DX_IOCTL_dxctl_ioctl_genvref_dram_pd_END          (9)
#define SOC_HIPACKPHY_DX_IOCTL_dx_ioctl_ronsel_START                    (11)
#define SOC_HIPACKPHY_DX_IOCTL_dx_ioctl_ronsel_END                      (13)
#define SOC_HIPACKPHY_DX_IOCTL_dqs_ioctl_ronsel_START                   (14)
#define SOC_HIPACKPHY_DX_IOCTL_dqs_ioctl_ronsel_END                     (16)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dq_odtn_START                      (24)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dq_odtn_END                        (24)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dq_odtp_START                      (25)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dq_odtp_END                        (25)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dqs_odtn_START                     (26)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dqs_odtn_END                       (26)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dqs_odtp_START                     (27)
#define SOC_HIPACKPHY_DX_IOCTL_ioctl_dqs_odtp_END                       (27)
#define SOC_HIPACKPHY_DX_IOCTL_dqs_ioctl_odtsel_START                   (29)
#define SOC_HIPACKPHY_DX_IOCTL_dqs_ioctl_odtsel_END                     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DQSSEL_UNION
 �ṹ˵��  : DX_DQSSEL �Ĵ����ṹ���塣��ַƫ����:0x208����ֵ:0x00000000�����:32
 �Ĵ���˵��: Swap of DQ in PHY
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_dqswap_sel : 16; /* bit[0-15] :  */
        unsigned int  dxctl_dmswap_sel : 2;  /* bit[16-17]:  */
        unsigned int  reserved         : 14; /* bit[18-31]: DQ swap in PHY
                                                            Each bit decides the relative DQS with DQ
                                                            1: Relative to DQS1
                                                            0: Relative to DQS0  */
    } reg;
} SOC_HIPACKPHY_DX_DQSSEL_UNION;
#endif
#define SOC_HIPACKPHY_DX_DQSSEL_dxctl_dqswap_sel_START  (0)
#define SOC_HIPACKPHY_DX_DQSSEL_dxctl_dqswap_sel_END    (15)
#define SOC_HIPACKPHY_DX_DQSSEL_dxctl_dmswap_sel_START  (16)
#define SOC_HIPACKPHY_DX_DQSSEL_dxctl_dmswap_sel_END    (17)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXNCKCTRL_UNION
 �ṹ˵��  : DX_DXNCKCTRL �Ĵ����ṹ���塣��ַƫ����:0x20C����ֵ:0x00000000�����:32
 �Ĵ���˵��: This register is for PLL phase select within the PHY. And should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_ck0p_mclk     : 3;  /* bit[0-2]  :  */
        unsigned int  reserved_0          : 1;  /* bit[3]    :  */
        unsigned int  dxctl_ck9p_cmd1t    : 3;  /* bit[4-6]  :  */
        unsigned int  reserved_1          : 1;  /* bit[7]    :  */
        unsigned int  dxctl_ck10p_cmd2t   : 3;  /* bit[8-10] :  */
        unsigned int  reserved_2          : 1;  /* bit[11]   :  */
        unsigned int  dxctl_ck11p_dramclk : 3;  /* bit[12-14]:  */
        unsigned int  reserved_3          : 17; /* bit[15-31]:  */
    } reg;
} SOC_HIPACKPHY_DX_DXNCKCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck0p_mclk_START      (0)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck0p_mclk_END        (2)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck9p_cmd1t_START     (4)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck9p_cmd1t_END       (6)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck10p_cmd2t_START    (8)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck10p_cmd2t_END      (10)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck11p_dramclk_START  (12)
#define SOC_HIPACKPHY_DX_DXNCKCTRL_dxctl_ck11p_dramclk_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_UNION
 �ṹ˵��  : DX_PHYPLLCTRL_DX �Ĵ����ṹ���塣��ַƫ����:0x210����ֵ:0x0000000A�����:32
 �Ĵ���˵��: PHY PLL control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_pll_test : 6;  /* bit[0-5] : PLL Test for 16-Bit Data Block
                                                         7:0 - 16-Bit Block 0
                                                         15:8 - 16-Bit Block 1 */
        unsigned int  reserved       : 25; /* bit[6-30]:  */
        unsigned int  dxctl_pll_lock : 1;  /* bit[31]  : ND: Number of DATA PHY Block
                                                         DX PLL LOCK signals for each bytelane
                                                         1: Locked
                                                         0: Not Locked
                                                         (In Balong, only bit0 is valid) */
    } reg;
} SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_UNION;
#endif
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_dxctl_pll_test_START  (0)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_dxctl_pll_test_END    (5)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_dxctl_pll_lock_START  (31)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX_dxctl_pll_lock_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_PHYCTRL2_UNION
 �ṹ˵��  : DX_PHYCTRL2 �Ĵ����ṹ���塣��ַƫ����:0x214����ֵ:0x20080000�����:32
 �Ĵ���˵��: PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                  : 4;  /* bit[0-3]  :  */
        unsigned int  ut_mode                     : 1;  /* bit[4]    : 1: ut
                                                                       0: other */
        unsigned int  dxctl_reg_dvalid_selfgen_en : 1;  /* bit[5]    : 0: GDS use DFI rden signals to generate the dvalid signal (default)
                                                                       1: GDS use self mechanism to generate the dvalid signal. Some bubble might occur for DVALID */
        unsigned int  reserved_1                  : 10; /* bit[6-15] :  */
        unsigned int  lpddr4_mode                 : 1;  /* bit[16]   : 0: lpddr3e mode
                                                                       1: lpddr4 mode */
        unsigned int  phy_type                    : 2;  /* bit[17-18]: for dxdlyline configure
                                                                       00: phya 
                                                                       01: phyb 
                                                                       10: phyc
                                                                       11: phyd */
        unsigned int  dxctl_reg_sel_pos_rx        : 1;  /* bit[19]   :  */
        unsigned int  reserved_2                  : 3;  /* bit[20-22]:  */
        unsigned int  dxctl_reg_wfifo_mode        : 1;  /* bit[23]   :  */
        unsigned int  dxctl_reg_rdffsel_2rank_en  : 1;  /* bit[24]   :  */
        unsigned int  dxctl_ppfifo_ptr_en         : 1;  /* bit[25]   :  */
        unsigned int  dxctl_reg_phy_wdata_ranksw  : 3;  /* bit[26-28]:  */
        unsigned int  wfifo_dxctl_gcken           : 1;  /* bit[29]   :  */
        unsigned int  wfifo_dxctl_passthrough     : 1;  /* bit[30]   :  */
        unsigned int  reserved_3                  : 1;  /* bit[31]   :  */
    } reg;
} SOC_HIPACKPHY_DX_PHYCTRL2_UNION;
#endif
#define SOC_HIPACKPHY_DX_PHYCTRL2_ut_mode_START                      (4)
#define SOC_HIPACKPHY_DX_PHYCTRL2_ut_mode_END                        (4)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_dvalid_selfgen_en_START  (5)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_dvalid_selfgen_en_END    (5)
#define SOC_HIPACKPHY_DX_PHYCTRL2_lpddr4_mode_START                  (16)
#define SOC_HIPACKPHY_DX_PHYCTRL2_lpddr4_mode_END                    (16)
#define SOC_HIPACKPHY_DX_PHYCTRL2_phy_type_START                     (17)
#define SOC_HIPACKPHY_DX_PHYCTRL2_phy_type_END                       (18)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_sel_pos_rx_START         (19)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_sel_pos_rx_END           (19)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_wfifo_mode_START         (23)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_wfifo_mode_END           (23)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_rdffsel_2rank_en_START   (24)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_rdffsel_2rank_en_END     (24)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_ppfifo_ptr_en_START          (25)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_ppfifo_ptr_en_END            (25)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_phy_wdata_ranksw_START   (26)
#define SOC_HIPACKPHY_DX_PHYCTRL2_dxctl_reg_phy_wdata_ranksw_END     (28)
#define SOC_HIPACKPHY_DX_PHYCTRL2_wfifo_dxctl_gcken_START            (29)
#define SOC_HIPACKPHY_DX_PHYCTRL2_wfifo_dxctl_gcken_END              (29)
#define SOC_HIPACKPHY_DX_PHYCTRL2_wfifo_dxctl_passthrough_START      (30)
#define SOC_HIPACKPHY_DX_PHYCTRL2_wfifo_dxctl_passthrough_END        (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_IOCTL1_UNION
 �ṹ˵��  : DX_IOCTL1 �Ĵ����ṹ���塣��ַƫ����:0x218����ֵ:0x73140000�����:32
 �Ĵ���˵��: PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_ioctl_genvref_range_2      : 2;  /* bit[0-1]  :  */
        unsigned int  reserved_0                       : 4;  /* bit[2-5]  :  */
        unsigned int  dxctl_odt_ioctl_rdsel_p          : 3;  /* bit[6-8]  : dxctl_reg_phy_wdata_ranksw shadow register */
        unsigned int  dxctl_odt_ioctl_rdsel_n          : 3;  /* bit[9-11] :  */
        unsigned int  dxctl_ioctl_genvref_pd           : 2;  /* bit[12-13]:  */
        unsigned int  reserved_1                       : 4;  /* bit[14-17]:  */
        unsigned int  dxctl_ioctl_genvref_dram_range_2 : 1;  /* bit[18]   :  */
        unsigned int  reserved_2                       : 1;  /* bit[19]   :  */
        unsigned int  dxctl_ioctl_genvref_dram_range_1 : 1;  /* bit[20]   :  */
        unsigned int  reserved_3                       : 1;  /* bit[21]   :  */
        unsigned int  dxctl_ioctl_genvref_dram_range_0 : 1;  /* bit[22]   :  */
        unsigned int  reserved_4                       : 1;  /* bit[23]   :  */
        unsigned int  dxctl_ioctl_squeach_pd           : 2;  /* bit[24-25]:  */
        unsigned int  reserved_5                       : 2;  /* bit[26-27]:  */
        unsigned int  dxctl_odt_ioctl_ronsel           : 3;  /* bit[28-30]:  */
        unsigned int  dxctl_ioctl_odt_iopldn           : 1;  /* bit[31]   :  */
    } reg;
} SOC_HIPACKPHY_DX_IOCTL1_UNION;
#endif
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_range_2_START       (0)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_range_2_END         (1)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_odt_ioctl_rdsel_p_START           (6)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_odt_ioctl_rdsel_p_END             (8)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_odt_ioctl_rdsel_n_START           (9)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_odt_ioctl_rdsel_n_END             (11)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_pd_START            (12)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_pd_END              (13)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_dram_range_2_START  (18)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_dram_range_2_END    (18)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_dram_range_1_START  (20)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_dram_range_1_END    (20)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_dram_range_0_START  (22)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_genvref_dram_range_0_END    (22)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_squeach_pd_START            (24)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_squeach_pd_END              (25)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_odt_ioctl_ronsel_START            (28)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_odt_ioctl_ronsel_END              (30)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_odt_iopldn_START            (31)
#define SOC_HIPACKPHY_DX_IOCTL1_dxctl_ioctl_odt_iopldn_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_IOCTL2_UNION
 �ṹ˵��  : DX_IOCTL2 �Ĵ����ṹ���塣��ַƫ����:0x21C����ֵ:0xE80000C3�����:32
 �Ĵ���˵��: PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_ioctl_genvref_range_0  : 2;  /* bit[0-1]  :  */
        unsigned int  reserved_0                   : 4;  /* bit[2-5]  :  */
        unsigned int  dxctl_ioctl_genvref_range_1  : 2;  /* bit[6-7]  :  */
        unsigned int  reserved_1                   : 4;  /* bit[8-11] :  */
        unsigned int  dxctl_ioctl_genvref_refsel_0 : 2;  /* bit[12-13]:  */
        unsigned int  reserved_2                   : 4;  /* bit[14-17]:  */
        unsigned int  dxctl_ioctl_genvref_refsel_1 : 2;  /* bit[18-19]:  */
        unsigned int  reserved_3                   : 4;  /* bit[20-23]:  */
        unsigned int  dxctl_ioctl_genvref_refsel_2 : 2;  /* bit[24-25]:  */
        unsigned int  reserved_4                   : 1;  /* bit[26]   :  */
        unsigned int  dq_vref_sel                  : 1;  /* bit[27]   : 1: refsel from pack
                                                                        0: refsel from register */
        unsigned int  ioctl_dq_sp                  : 1;  /* bit[28]   :  */
        unsigned int  ioctl_dq_lpddr4en            : 1;  /* bit[29]   :  */
        unsigned int  ioctl_dq_rx_mode0            : 1;  /* bit[30]   :  */
        unsigned int  ioctl_dq_rx_mode1            : 1;  /* bit[31]   :  */
    } reg;
} SOC_HIPACKPHY_DX_IOCTL2_UNION;
#endif
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_range_0_START   (0)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_range_0_END     (1)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_range_1_START   (6)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_range_1_END     (7)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_refsel_0_START  (12)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_refsel_0_END    (13)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_refsel_1_START  (18)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_refsel_1_END    (19)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_refsel_2_START  (24)
#define SOC_HIPACKPHY_DX_IOCTL2_dxctl_ioctl_genvref_refsel_2_END    (25)
#define SOC_HIPACKPHY_DX_IOCTL2_dq_vref_sel_START                   (27)
#define SOC_HIPACKPHY_DX_IOCTL2_dq_vref_sel_END                     (27)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_sp_START                   (28)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_sp_END                     (28)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_lpddr4en_START             (29)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_lpddr4en_END               (29)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_rx_mode0_START             (30)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_rx_mode0_END               (30)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_rx_mode1_START             (31)
#define SOC_HIPACKPHY_DX_IOCTL2_ioctl_dq_rx_mode1_END               (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_UNION
 �ṹ˵��  : DX_PHYPLLCTRL_DX2 �Ĵ����ṹ���塣��ַƫ����:0x220����ֵ:0x00000055�����:32
 �Ĵ���˵��: PHY PLL control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl__pll_bp_refpfd   : 1;  /* bit[0]    :  */
        unsigned int  reserved_0             : 1;  /* bit[1]    :  */
        unsigned int  dxctl__pll_bp_refvco   : 1;  /* bit[2]    :  */
        unsigned int  reserved_1             : 1;  /* bit[3]    :  */
        unsigned int  dxctl__pll_enphsel     : 1;  /* bit[4]    : PLL 6/2 Phase Selection
                                                                  1: 6 Phase Output
                                                                  0: 2 Phase Output */
        unsigned int  reserved_2             : 1;  /* bit[5]    :  */
        unsigned int  dxctl__pll_en_cal      : 1;  /* bit[6]    :  */
        unsigned int  reserved_3             : 1;  /* bit[7]    :  */
        unsigned int  dxctl__pll_initsel     : 1;  /* bit[8]    :  */
        unsigned int  reserved_4             : 1;  /* bit[9]    :  */
        unsigned int  dxctl__pll_lockt_sel   : 1;  /* bit[10]   :  */
        unsigned int  reserved_5             : 1;  /* bit[11]   :  */
        unsigned int  dxctl__pll_fopetestfb  : 1;  /* bit[12]   :  */
        unsigned int  reserved_6             : 1;  /* bit[13]   :  */
        unsigned int  dxctl__pll_fopetestref : 1;  /* bit[14]   :  */
        unsigned int  reserved_7             : 1;  /* bit[15]   :  */
        unsigned int  dxctl_pll_lockin       : 1;  /* bit[16]   :  */
        unsigned int  reserved_8             : 15; /* bit[17-31]:  */
    } reg;
} SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_UNION;
#endif
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_bp_refpfd_START    (0)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_bp_refpfd_END      (0)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_bp_refvco_START    (2)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_bp_refvco_END      (2)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_enphsel_START      (4)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_enphsel_END        (4)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_en_cal_START       (6)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_en_cal_END         (6)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_initsel_START      (8)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_initsel_END        (8)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_lockt_sel_START    (10)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_lockt_sel_END      (10)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_fopetestfb_START   (12)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_fopetestfb_END     (12)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_fopetestref_START  (14)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl__pll_fopetestref_END    (14)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl_pll_lockin_START        (16)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX2_dxctl_pll_lockin_END          (16)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_UNION
 �ṹ˵��  : DX_PHYPLLCTRL_DX3 �Ĵ����ṹ���塣��ַƫ����:0x224����ֵ:0x00000020�����:32
 �Ĵ���˵��: PHY PLL control register 3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_phazmeter_in     : 16; /* bit[0-15] : [8:0]:dxctl_byp_ck90_data_code_dqs_shadow byte0[8:0] */
        unsigned int  dxctl_phazmeter_status : 16; /* bit[16-31]:  */
    } reg;
} SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_UNION;
#endif
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_dxctl_phazmeter_in_START      (0)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_dxctl_phazmeter_in_END        (15)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_dxctl_phazmeter_status_START  (16)
#define SOC_HIPACKPHY_DX_PHYPLLCTRL_DX3_dxctl_phazmeter_status_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXNCLKBDL_UNION
 �ṹ˵��  : DX_DXNCLKBDL �Ĵ����ṹ���塣��ַƫ����:0x230����ֵ:0x00000000�����:32
 �Ĵ���˵��: DATA block clock bit delay line setting
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_fbclk_bdl  : 4;  /* bit[0-3]  : Bit delay line setting of FBCLK */
        unsigned int  reserved_0       : 12; /* bit[4-15] : -- */
        unsigned int  dxctl_refclk_bdl : 4;  /* bit[16-19]: Bit delay line setting of REFCLK */
        unsigned int  reserved_1       : 12; /* bit[20-31]: -- */
    } reg;
} SOC_HIPACKPHY_DX_DXNCLKBDL_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNCLKBDL_dxctl_fbclk_bdl_START   (0)
#define SOC_HIPACKPHY_DX_DXNCLKBDL_dxctl_fbclk_bdl_END     (3)
#define SOC_HIPACKPHY_DX_DXNCLKBDL_dxctl_refclk_bdl_START  (16)
#define SOC_HIPACKPHY_DX_DXNCLKBDL_dxctl_refclk_bdl_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXPHYCTRL_UNION
 �ṹ˵��  : DX_DXPHYCTRL �Ĵ����ṹ���塣��ַƫ����:0x234����ֵ:0x00000080�����:32
 �Ĵ���˵��: DX PHY control registers 
            Register in this field are connected to PHY interface directly
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0       : 2;  /* bit[0-1]  :  */
        unsigned int  dxctl_pll_testen : 1;  /* bit[2]    : dxctl_byp_ck90_data_code_dqs_shadow byte1[0] */
        unsigned int  dxctl_pll_init   : 1;  /* bit[3]    : dxctl_byp_ck90_data_code_dqs_shadow byte1[1] */
        unsigned int  dxctl_pll_cpi    : 3;  /* bit[4-6]  : dxctl_byp_ck90_data_code_dqs_shadow byte1[4:2] */
        unsigned int  dxctl_pll_sp     : 2;  /* bit[7-8]  : dxctl_byp_ck90_data_code_dqs_shadow byte1[6:5] */
        unsigned int  reserved_1       : 1;  /* bit[9]    :  */
        unsigned int  dxctl_pll_lt     : 2;  /* bit[10-11]: dxctl_byp_ck90_data_code_dqs_shadow byte1[8:7] */
        unsigned int  reserved_2       : 20; /* bit[12-31]:  */
    } reg;
} SOC_HIPACKPHY_DX_DXPHYCTRL_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_testen_START  (2)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_testen_END    (2)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_init_START    (3)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_init_END      (3)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_cpi_START     (4)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_cpi_END       (6)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_sp_START      (7)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_sp_END        (8)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_lt_START      (10)
#define SOC_HIPACKPHY_DX_DXPHYCTRL_dxctl_pll_lt_END        (11)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXNMISCCTRL0_UNION
 �ṹ˵��  : DX_DXNMISCCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x238+(p)*0x80����ֵ:0x00020000�����:32
 �Ĵ���˵��: Data block PHY miscellaneous control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_rxn_2nd_dq             : 8;  /* bit[0-7] : After modify this field, it need the "phyconn_rst" to update the latest setting. When user want to use dly_track_type=1 tracking type, this field should be set as 0xFF before initial trainings and dly_track_type should be set as 0x1 after initial trainings. */
        unsigned int  dxctl_rxp_2nd_dq             : 8;  /* bit[8-15]: After modify this field, it need the "phyconn_rst" to update the latest setting. When user want to use dly_track_type=1 tracking type, this field should be set as 0xFF before initial trainings and dly_track_type should be set as 0x1 after initial trainings. */
        unsigned int  reserved_0                   : 1;  /* bit[16]  :  */
        unsigned int  dxctl_dqs_l                  : 1;  /* bit[17]  : -- */
        unsigned int  dxctl_dqs_h                  : 1;  /* bit[18]  : -- */
        unsigned int  dxctl_rxn_2nd_dm             : 1;  /* bit[19]  : After modify this field, it need the "phyconn_rst" to update the latest setting. When user want to use dly_track_type=1 tracking type, this field should be set as 0x1 before initial trainings and dly_track_type should be set as 0x1 after initial trainings. */
        unsigned int  dxctl_rxp_2nd_dm             : 1;  /* bit[20]  : After modify this field, it need the "phyconn_rst" to update the latest setting. When user want to use dly_track_type=1 tracking type, this field should be set as 0x1 before initial trainings and dly_track_type should be set as 0x1 after initial trainings. */
        unsigned int  dxctl_dqsgatedla             : 1;  /* bit[21]  :  */
        unsigned int  dxctl_lvdqclkdiv2            : 1;  /* bit[22]  :  */
        unsigned int  dxctl_bufphyclkdiv2          : 1;  /* bit[23]  :  */
        unsigned int  dxctl_reg_sel_lvdqsclkdiv2   : 1;  /* bit[24]  :  */
        unsigned int  dxctl_reg_wpst_1p5ten        : 1;  /* bit[25]  : 1.5T Write Postamble Support
                                                                       1: Support Write Postamble 1.5T (reg_OE_extend1T_en Must set 1'b1 First) */
        unsigned int  dxctl_ptrgated_en            : 1;  /* bit[26]  :  */
        unsigned int  dxctl_reg_dqsg_toggle_en     : 1;  /* bit[27]  :  */
        unsigned int  dxctl_reg_dqsg_extend_en_dqs : 1;  /* bit[28]  : 0: Disable the DQSG extending function (default)
                                                                       1: Enable the DQSG extending function */
        unsigned int  dxctl_reg_dqsg_extend_2t_dqs : 1;  /* bit[29]  : 0: Extend DQSG 1T dfi_clk, when reg_DQSG_extend_en=1 (default)
                                                                       1: Extend DQSG 2T dfi_clk, when reg_DQSG_extend_en=1 */
        unsigned int  dxctl_reg_rxfifo_r1t_sel_dqs : 1;  /* bit[30]  : 0: GDS no leading 1T (default)
                                                                       1: GDS leading 1T */
        unsigned int  reserved_1                   : 1;  /* bit[31]  : -- */
    } reg;
} SOC_HIPACKPHY_DX_DXNMISCCTRL0_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxn_2nd_dq_START              (0)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxn_2nd_dq_END                (7)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxp_2nd_dq_START              (8)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxp_2nd_dq_END                (15)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_dqs_l_START                   (17)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_dqs_l_END                     (17)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_dqs_h_START                   (18)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_dqs_h_END                     (18)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxn_2nd_dm_START              (19)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxn_2nd_dm_END                (19)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxp_2nd_dm_START              (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_rxp_2nd_dm_END                (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_dqsgatedla_START              (21)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_dqsgatedla_END                (21)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_lvdqclkdiv2_START             (22)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_lvdqclkdiv2_END               (22)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_bufphyclkdiv2_START           (23)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_bufphyclkdiv2_END             (23)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_sel_lvdqsclkdiv2_START    (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_sel_lvdqsclkdiv2_END      (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_wpst_1p5ten_START         (25)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_wpst_1p5ten_END           (25)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_ptrgated_en_START             (26)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_ptrgated_en_END               (26)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_dqsg_toggle_en_START      (27)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_dqsg_toggle_en_END        (27)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_dqsg_extend_en_dqs_START  (28)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_dqsg_extend_en_dqs_END    (28)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_dqsg_extend_2t_dqs_START  (29)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_dqsg_extend_2t_dqs_END    (29)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_rxfifo_r1t_sel_dqs_START  (30)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL0_dxctl_reg_rxfifo_r1t_sel_dqs_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXNMISCCTRL1_UNION
 �ṹ˵��  : DX_DXNMISCCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x264+(p)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: Data block PHY miscellaneous control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_mclk2x    : 3;  /* bit[0-2]  : -- */
        unsigned int  reserved_0      : 1;  /* bit[3]    :  */
        unsigned int  dxctl_mclk1x    : 3;  /* bit[4-6]  : -- */
        unsigned int  reserved_1      : 1;  /* bit[7]    :  */
        unsigned int  dxctl_dqsclk2x  : 3;  /* bit[8-10] : -- */
        unsigned int  reserved_2      : 1;  /* bit[11]   :  */
        unsigned int  dxctl_dqsclk1x  : 3;  /* bit[12-14]:  */
        unsigned int  reserved_3      : 1;  /* bit[15]   :  */
        unsigned int  dxctl_dqsgclk2x : 3;  /* bit[16-18]:  */
        unsigned int  reserved_4      : 1;  /* bit[19]   :  */
        unsigned int  dxctl_dqsgclk1x : 3;  /* bit[20-22]:  */
        unsigned int  reserved_5      : 1;  /* bit[23]   :  */
        unsigned int  dxctl_dqclk2x   : 3;  /* bit[24-26]:  */
        unsigned int  reserved_6      : 1;  /* bit[27]   :  */
        unsigned int  dxctl_dqclk1x   : 3;  /* bit[28-30]:  */
        unsigned int  reserved_7      : 1;  /* bit[31]   : --- */
    } reg;
} SOC_HIPACKPHY_DX_DXNMISCCTRL1_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_mclk2x_START     (0)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_mclk2x_END       (2)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_mclk1x_START     (4)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_mclk1x_END       (6)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsclk2x_START   (8)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsclk2x_END     (10)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsclk1x_START   (12)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsclk1x_END     (14)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsgclk2x_START  (16)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsgclk2x_END    (18)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsgclk1x_START  (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqsgclk1x_END    (22)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqclk2x_START    (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqclk2x_END      (26)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqclk1x_START    (28)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL1_dxctl_dqclk1x_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXDEBUG0_UNION
 �ṹ˵��  : DX_DXDEBUG0 �Ĵ����ṹ���塣��ַƫ����:0x23C+(p)*0x80����ֵ:0x00005415�����:32
 �Ĵ���˵��: Data block PHY debug signals
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxdbg_dqs_cb           : 3;  /* bit[0-2]  :  */
        unsigned int  dxdbg_dqs_ca           : 3;  /* bit[3-5]  :  */
        unsigned int  dxdbg_dqs_rdcnt        : 4;  /* bit[6-9]  :  */
        unsigned int  dxdbg_dqs_s2b          : 1;  /* bit[10]   :  */
        unsigned int  dxdbg_dqs_s2a          : 1;  /* bit[11]   :  */
        unsigned int  dxdbg_dqs_s1b          : 1;  /* bit[12]   :  */
        unsigned int  dxdbg_dqs_s1a          : 1;  /* bit[13]   :  */
        unsigned int  dxdbg_dqs_s0b          : 1;  /* bit[14]   :  */
        unsigned int  dxdbg_dqs_s0a          : 1;  /* bit[15]   :  */
        unsigned int  dxctl_rlresult_gds_dqs : 8;  /* bit[16-23]:  */
        unsigned int  reserved               : 8;  /* bit[24-31]: Debug signals */
    } reg;
} SOC_HIPACKPHY_DX_DXDEBUG0_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_cb_START            (0)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_cb_END              (2)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_ca_START            (3)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_ca_END              (5)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_rdcnt_START         (6)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_rdcnt_END           (9)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s2b_START           (10)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s2b_END             (10)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s2a_START           (11)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s2a_END             (11)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s1b_START           (12)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s1b_END             (12)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s1a_START           (13)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s1a_END             (13)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s0b_START           (14)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s0b_END             (14)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s0a_START           (15)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxdbg_dqs_s0a_END             (15)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxctl_rlresult_gds_dqs_START  (16)
#define SOC_HIPACKPHY_DX_DXDEBUG0_dxctl_rlresult_gds_dqs_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXPHYRSVD_UNION
 �ṹ˵��  : DX_DXPHYRSVD �Ĵ����ṹ���塣��ַƫ����:0x244+(p)*0x80����ֵ:0x0000FF00�����:32
 �Ĵ���˵��: Data block PHY reserved control pins. This register is for PHY control and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_rsvdctrl : 16; /* bit[0-15] : Reserved registers for the future. */
        unsigned int  reserved       : 16; /* bit[16-31]: Reserved registers for the future. */
    } reg;
} SOC_HIPACKPHY_DX_DXPHYRSVD_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXPHYRSVD_dxctl_rsvdctrl_START  (0)
#define SOC_HIPACKPHY_DX_DXPHYRSVD_dxctl_rsvdctrl_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXNMISCCTRL2_UNION
 �ṹ˵��  : DX_DXNMISCCTRL2 �Ĵ����ṹ���塣��ַƫ����:0x248+(p)*0x80����ֵ:0x0030325E�����:32
 �Ĵ���˵��: Data block PHY miscellaneous control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bufresetcontn_gated_dqsgerror    : 1;  /* bit[0]    : [10]: reg_OE_extend1T_en
                                                                            [9]: reg_dqsg_TX_2path
                                                                            [8]: reg_squeach_en
                                                                            [7]: reg_dqsglat1T_en
                                                                            [6]: reg_sel_halfT_gated_16b
                                                                            [5]: reg_dynamic_PUPDEN_16b
                                                                            [4]: reg_dummypad_use
                                                                            [3]: reg_ODTEN_gated
                                                                            [2]: reg_GDS_r1T_sel_16b
                                                                            [1]: BUFRESETCONTN_gated_TDC
                                                                            [0]: BUFRESETCONTN_gated_DQSGERROR
                                                                             -> Need to Configure to 1'b0 at Gate Training Phase and Gate Re-Train Phase when exd_gtres_en==1'b1 */
        unsigned int  bufresetcontn_gated_tdc          : 1;  /* bit[1]    :  */
        unsigned int  reg_gds_r1t_sel                  : 1;  /* bit[2]    :  */
        unsigned int  reg_odten_gated                  : 1;  /* bit[3]    :  */
        unsigned int  reg_dummypad_use                 : 1;  /* bit[4]    :  */
        unsigned int  reg_dynamic_pupden               : 1;  /* bit[5]    :  */
        unsigned int  reg_sel_halft_gated              : 1;  /* bit[6]    :  */
        unsigned int  reg_dqsglat1t_en                 : 1;  /* bit[7]    :  */
        unsigned int  reg_squeach_en                   : 1;  /* bit[8]    :  */
        unsigned int  reg_dqsg_tx_2path                : 1;  /* bit[9]    :  */
        unsigned int  reg_oe_extend1t_en               : 1;  /* bit[10]   :  */
        unsigned int  dxctl_reg_perbit_mode_en         : 1;  /* bit[11]   : Must be 0x0 due to Feature Removed */
        unsigned int  dxctl_reg_phy_dqsdly_stop_enable : 1;  /* bit[12]   : 0x1: Enable PHY Stop for DQS Delay
                                                                            0x0: Disable */
        unsigned int  dxctl_reg_phy_dqsg_stop_enable   : 1;  /* bit[13]   :  */
        unsigned int  dxctl_reg_dqsdly_demux_gated_1   : 1;  /* bit[14]   :  */
        unsigned int  dxctl_reg_dqsgdly_demux_gated_0  : 1;  /* bit[15]   :  */
        unsigned int  dxctl_reg_post_margin_gated_1    : 1;  /* bit[16]   :  */
        unsigned int  dxctl_reg_post_margin_gated_0    : 1;  /* bit[17]   :  */
        unsigned int  dxctl_reg_pre_margin_gated_1     : 1;  /* bit[18]   :  */
        unsigned int  dxctl_reg_pre_margin_gated_0     : 1;  /* bit[19]   :  */
        unsigned int  dxctl_reg_pn_dlyen               : 1;  /* bit[20]   :  */
        unsigned int  dxctl_reset_n_phyupdate_req      : 1;  /* bit[21]   : 0x1: Enable PHY Stop for DQS Gate
                                                                            0x0: Disable */
        unsigned int  dxctl_reg_tspc_sel               : 1;  /* bit[22]   :  */
        unsigned int  dxctl_reg_sel_combout            : 1;  /* bit[23]   :  */
        unsigned int  dxctl_reg_post_gateden           : 1;  /* bit[24]   :  */
        unsigned int  reserved_0                       : 2;  /* bit[25-26]:  */
        unsigned int  dxctl_byp_clk_gated_dis          : 1;  /* bit[27]   : DX clock gated disable in bypass mode.
                                                                            0: turn off clocks in bypass mode (default)
                                                                            1: turn on clocks in bypass mode */
        unsigned int  reserved_1                       : 4;  /* bit[28-31]: --- */
    } reg;
} SOC_HIPACKPHY_DX_DXNMISCCTRL2_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_bufresetcontn_gated_dqsgerror_START     (0)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_bufresetcontn_gated_dqsgerror_END       (0)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_bufresetcontn_gated_tdc_START           (1)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_bufresetcontn_gated_tdc_END             (1)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_gds_r1t_sel_START                   (2)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_gds_r1t_sel_END                     (2)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_odten_gated_START                   (3)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_odten_gated_END                     (3)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dummypad_use_START                  (4)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dummypad_use_END                    (4)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dynamic_pupden_START                (5)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dynamic_pupden_END                  (5)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_sel_halft_gated_START               (6)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_sel_halft_gated_END                 (6)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dqsglat1t_en_START                  (7)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dqsglat1t_en_END                    (7)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_squeach_en_START                    (8)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_squeach_en_END                      (8)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dqsg_tx_2path_START                 (9)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_dqsg_tx_2path_END                   (9)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_oe_extend1t_en_START                (10)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_reg_oe_extend1t_en_END                  (10)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_perbit_mode_en_START          (11)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_perbit_mode_en_END            (11)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_phy_dqsdly_stop_enable_START  (12)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_phy_dqsdly_stop_enable_END    (12)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_phy_dqsg_stop_enable_START    (13)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_phy_dqsg_stop_enable_END      (13)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_dqsdly_demux_gated_1_START    (14)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_dqsdly_demux_gated_1_END      (14)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_dqsgdly_demux_gated_0_START   (15)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_dqsgdly_demux_gated_0_END     (15)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_post_margin_gated_1_START     (16)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_post_margin_gated_1_END       (16)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_post_margin_gated_0_START     (17)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_post_margin_gated_0_END       (17)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_pre_margin_gated_1_START      (18)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_pre_margin_gated_1_END        (18)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_pre_margin_gated_0_START      (19)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_pre_margin_gated_0_END        (19)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_pn_dlyen_START                (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_pn_dlyen_END                  (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reset_n_phyupdate_req_START       (21)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reset_n_phyupdate_req_END         (21)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_tspc_sel_START                (22)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_tspc_sel_END                  (22)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_sel_combout_START             (23)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_sel_combout_END               (23)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_post_gateden_START            (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_reg_post_gateden_END              (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_byp_clk_gated_dis_START           (27)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL2_dxctl_byp_clk_gated_dis_END             (27)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXDEBUGCONFIG_UNION
 �ṹ˵��  : DX_DXDEBUGCONFIG �Ĵ����ṹ���塣��ַƫ����:0x24C+(p)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: Data block PHY debug/miscellaneous control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_dbg_config            : 4;  /* bit[0-3]  :  */
        unsigned int  dxctl_deskew_regread        : 1;  /* bit[4]    :  */
        unsigned int  reserved_0                  : 3;  /* bit[5-7]  :  */
        unsigned int  dxctl_reg_dbg_fotest        : 1;  /* bit[8]    :  */
        unsigned int  dxctl_reg_dbg_dqsdly_odtpad : 1;  /* bit[9]    :  */
        unsigned int  dxctl_reg_dbg_gated_n       : 1;  /* bit[10]   :  */
        unsigned int  reserved_1                  : 21; /* bit[11-31]: --- */
    } reg;
} SOC_HIPACKPHY_DX_DXDEBUGCONFIG_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_dbg_config_START             (0)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_dbg_config_END               (3)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_deskew_regread_START         (4)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_deskew_regread_END           (4)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_reg_dbg_fotest_START         (8)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_reg_dbg_fotest_END           (8)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_reg_dbg_dqsdly_odtpad_START  (9)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_reg_dbg_dqsdly_odtpad_END    (9)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_reg_dbg_gated_n_START        (10)
#define SOC_HIPACKPHY_DX_DXDEBUGCONFIG_dxctl_reg_dbg_gated_n_END          (10)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXNDCC_UNION
 �ṹ˵��  : DX_DXNDCC �Ĵ����ṹ���塣��ַƫ����:0x250+(p)*0x80����ֵ:0x02000000�����:32
 �Ĵ���˵��: Data block PHY DCC control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_dq_dcc                 : 5;  /* bit[0-4]  : [2]-dly_sel_xxx_DCC_16b
                                                                        [1]-ctrlC_xxx_DCC_16b
                                                                        [0]-ctrl2_xxx_DCC_16b */
        unsigned int  dxctl_dqsg_dcc               : 5;  /* bit[5-9]  : [2]-dly_sel_xxx_DCC_16b
                                                                        [1]-ctrlC_xxx_DCC_16b
                                                                        [0]-ctrl2_xxx_DCC_16b */
        unsigned int  dxctl_dqs_dcc                : 5;  /* bit[10-14]: [2]-dly_sel_xxx_DCC_16b
                                                                        [1]-ctrlC_xxx_DCC_16b
                                                                        [0]-ctrl2_xxx_DCC_16b */
        unsigned int  dxctl_mclk_dcc               : 5;  /* bit[15-19]: [2]-dly_sel_xxx_DCC_16b
                                                                        [1]-ctrlC_xxx_DCC_16b
                                                                        [0]-ctrl2_xxx_DCC_16b */
        unsigned int  dxctl_byp_ck90_data_code_dqs : 9;  /* bit[20-28]:  */
        unsigned int  reserved                     : 3;  /* bit[29-31]: --- */
    } reg;
} SOC_HIPACKPHY_DX_DXNDCC_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_dq_dcc_START                  (0)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_dq_dcc_END                    (4)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_dqsg_dcc_START                (5)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_dqsg_dcc_END                  (9)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_dqs_dcc_START                 (10)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_dqs_dcc_END                   (14)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_mclk_dcc_START                (15)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_mclk_dcc_END                  (19)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_byp_ck90_data_code_dqs_START  (20)
#define SOC_HIPACKPHY_DX_DXNDCC_dxctl_byp_ck90_data_code_dqs_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXNMISCCTRL3_UNION
 �ṹ˵��  : DX_DXNMISCCTRL3 �Ĵ����ṹ���塣��ַƫ����:0x254+(p)*0x80����ֵ:0x00D80000�����:32
 �Ĵ���˵��: Data block PHY debug/miscellaneous control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_dqsg_extdly_dqs   : 3;  /* bit[0-2]  :  */
        unsigned int  reserved_0              : 9;  /* bit[3-11] :  */
        unsigned int  dxctl_rxext_dly         : 3;  /* bit[12-14]:  */
        unsigned int  reserved_1              : 1;  /* bit[15]   :  */
        unsigned int  dxctl_dqsdly_demux_code : 3;  /* bit[16-18]:  */
        unsigned int  dxctl_post_margin_code  : 3;  /* bit[19-21]:  */
        unsigned int  dxctl_pre_margin_code   : 3;  /* bit[22-24]:  */
        unsigned int  dxctl_dqsgclk2x_rank1   : 3;  /* bit[25-27]:  */
        unsigned int  dxctl_dqsgclk1x_rank1   : 3;  /* bit[28-30]:  */
        unsigned int  reserved_2              : 1;  /* bit[31]   : --- */
    } reg;
} SOC_HIPACKPHY_DX_DXNMISCCTRL3_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsg_extdly_dqs_START    (0)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsg_extdly_dqs_END      (2)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_rxext_dly_START          (12)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_rxext_dly_END            (14)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsdly_demux_code_START  (16)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsdly_demux_code_END    (18)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_post_margin_code_START   (19)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_post_margin_code_END     (21)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_pre_margin_code_START    (22)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_pre_margin_code_END      (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsgclk2x_rank1_START    (25)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsgclk2x_rank1_END      (27)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsgclk1x_rank1_START    (28)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL3_dxctl_dqsgclk1x_rank1_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXNMISCCTRL4_UNION
 �ṹ˵��  : DX_DXNMISCCTRL4 �Ĵ����ṹ���塣��ַƫ����:0x258+(p)*0x80����ֵ:0x0001014F�����:32
 �Ĵ���˵��: Data block PHY debug/miscellaneous control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_reg_clkgated_dis        : 4;  /* bit[0-3]  : Disable PHY Clock Gating by Read/Write Command (1: Disable, 0:Enable) */
        unsigned int  dxctl_reg_dbgmode_byt1_sel    : 1;  /* bit[4]    :  */
        unsigned int  dxctl_reg_dbgmode_sel         : 1;  /* bit[5]    :  */
        unsigned int  dxctl_reg_rst_n               : 1;  /* bit[6]    :  */
        unsigned int  reserved_0                    : 1;  /* bit[7]    :  */
        unsigned int  dxctl_reg_asy_cmd_decode_sel  : 1;  /* bit[8]    :  */
        unsigned int  reserved_1                    : 3;  /* bit[9-11] :  */
        unsigned int  dxctl_pack_cfg_rs_passthrough : 1;  /* bit[12]   :  */
        unsigned int  reserved_2                    : 3;  /* bit[13-15]:  */
        unsigned int  dxctl_reg_clkgated_en_dqs     : 1;  /* bit[16]   :  */
        unsigned int  reserved_3                    : 3;  /* bit[17-19]:  */
        unsigned int  dxctl_reg_1rank_only_en_dqs   : 1;  /* bit[20]   :  */
        unsigned int  reserved_4                    : 3;  /* bit[21-23]:  */
        unsigned int  dxctl_reg_dqsg_toggle_code90  : 6;  /* bit[24-29]: Only bit[7:1] are valid. Used as {bit[7:1],1'b1}. The bit[8] is useless. */
        unsigned int  reserved_5                    : 2;  /* bit[30-31]: --- */
    } reg;
} SOC_HIPACKPHY_DX_DXNMISCCTRL4_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_clkgated_dis_START         (0)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_clkgated_dis_END           (3)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_dbgmode_byt1_sel_START     (4)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_dbgmode_byt1_sel_END       (4)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_dbgmode_sel_START          (5)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_dbgmode_sel_END            (5)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_rst_n_START                (6)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_rst_n_END                  (6)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_asy_cmd_decode_sel_START   (8)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_asy_cmd_decode_sel_END     (8)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_pack_cfg_rs_passthrough_START  (12)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_pack_cfg_rs_passthrough_END    (12)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_clkgated_en_dqs_START      (16)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_clkgated_en_dqs_END        (16)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_1rank_only_en_dqs_START    (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_1rank_only_en_dqs_END      (20)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_dqsg_toggle_code90_START   (24)
#define SOC_HIPACKPHY_DX_DXNMISCCTRL4_dxctl_reg_dqsg_toggle_code90_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_IOCTL3_UNION
 �ṹ˵��  : DX_IOCTL3 �Ĵ����ṹ���塣��ַƫ����:0x25C+(p)*0x80����ֵ:0x0000783F�����:32
 �Ĵ���˵��: IO control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ioctl_dqs_rx_mode0     : 1;  /* bit[0]    :  */
        unsigned int  ioctl_dqs_rx_mode1     : 1;  /* bit[1]    :  */
        unsigned int  ioctl_dm_rx_mode0      : 1;  /* bit[2]    :  */
        unsigned int  ioctl_dm_rx_mode1      : 1;  /* bit[3]    :  */
        unsigned int  ioctl_dummy_rx_mode0   : 1;  /* bit[4]    :  */
        unsigned int  ioctl_dummy_rx_mode1   : 1;  /* bit[5]    :  */
        unsigned int  reserved_0             : 2;  /* bit[6-7]  :  */
        unsigned int  dxctl_ioctl_dm_sp      : 1;  /* bit[8]    :  */
        unsigned int  dxctl_ioctl_dummy_sp   : 1;  /* bit[9]    :  */
        unsigned int  dxctl_ioctl_dqs_sp     : 1;  /* bit[10]   :  */
        unsigned int  dxctl_ioctl_diffdqs_en : 1;  /* bit[11]   : Differential DQS enable */
        unsigned int  ioctl_dqs_lpddr4en     : 1;  /* bit[12]   :  */
        unsigned int  ioctl_dm_lpddr4en      : 1;  /* bit[13]   :  */
        unsigned int  ioctl_dummy_lpddr4en   : 1;  /* bit[14]   :  */
        unsigned int  reserved_1             : 17; /* bit[15-31]: --- */
    } reg;
} SOC_HIPACKPHY_DX_IOCTL3_UNION;
#endif
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dqs_rx_mode0_START      (0)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dqs_rx_mode0_END        (0)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dqs_rx_mode1_START      (1)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dqs_rx_mode1_END        (1)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dm_rx_mode0_START       (2)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dm_rx_mode0_END         (2)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dm_rx_mode1_START       (3)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dm_rx_mode1_END         (3)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dummy_rx_mode0_START    (4)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dummy_rx_mode0_END      (4)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dummy_rx_mode1_START    (5)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dummy_rx_mode1_END      (5)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_dm_sp_START       (8)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_dm_sp_END         (8)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_dummy_sp_START    (9)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_dummy_sp_END      (9)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_dqs_sp_START      (10)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_dqs_sp_END        (10)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_diffdqs_en_START  (11)
#define SOC_HIPACKPHY_DX_IOCTL3_dxctl_ioctl_diffdqs_en_END    (11)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dqs_lpddr4en_START      (12)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dqs_lpddr4en_END        (12)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dm_lpddr4en_START       (13)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dm_lpddr4en_END         (13)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dummy_lpddr4en_START    (14)
#define SOC_HIPACKPHY_DX_IOCTL3_ioctl_dummy_lpddr4en_END      (14)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_IOCTL5_UNION
 �ṹ˵��  : DX_IOCTL5 �Ĵ����ṹ���塣��ַƫ����:0x260����ֵ:0x00F400F4�����:32
 �Ĵ���˵��: IO control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dqs_ioctl_rdsel_p : 4;  /* bit[0-3]  :  */
        unsigned int  dqs_ioctl_rdsel_n : 4;  /* bit[4-7]  :  */
        unsigned int  dqs_ioctl_tdsel_p : 4;  /* bit[8-11] :  */
        unsigned int  dqs_ioctl_tdsel_n : 4;  /* bit[12-15]:  */
        unsigned int  dx_ioctl_rdsel_p  : 4;  /* bit[16-19]:  */
        unsigned int  dx_ioctl_rdsel_n  : 4;  /* bit[20-23]:  */
        unsigned int  dx_ioctl_tdsel_p  : 4;  /* bit[24-27]:  */
        unsigned int  dx_ioctl_tdsel_n  : 4;  /* bit[28-31]: --- */
    } reg;
} SOC_HIPACKPHY_DX_IOCTL5_UNION;
#endif
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_rdsel_p_START  (0)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_rdsel_p_END    (3)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_rdsel_n_START  (4)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_rdsel_n_END    (7)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_tdsel_p_START  (8)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_tdsel_p_END    (11)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_tdsel_n_START  (12)
#define SOC_HIPACKPHY_DX_IOCTL5_dqs_ioctl_tdsel_n_END    (15)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_rdsel_p_START   (16)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_rdsel_p_END     (19)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_rdsel_n_START   (20)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_rdsel_n_END     (23)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_tdsel_p_START   (24)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_tdsel_p_END     (27)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_tdsel_n_START   (28)
#define SOC_HIPACKPHY_DX_IOCTL5_dx_ioctl_tdsel_n_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXNDCC1_UNION
 �ṹ˵��  : DX_DXNDCC1 �Ĵ����ṹ���塣��ַƫ����:0x268+(p)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: Data block PHY DCC control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_reg_rx_dcc_dq0 : 5;  /* bit[0-4]  :  */
        unsigned int  dxctl_reg_rx_dcc_dq1 : 5;  /* bit[5-9]  :  */
        unsigned int  dxctl_reg_rx_dcc_dq2 : 5;  /* bit[10-14]:  */
        unsigned int  dxctl_reg_rx_dcc_dq3 : 5;  /* bit[15-19]:  */
        unsigned int  dxctl_reg_rx_dcc_dm  : 5;  /* bit[20-24]:  */
        unsigned int  reserved             : 7;  /* bit[25-31]:  */
    } reg;
} SOC_HIPACKPHY_DX_DXNDCC1_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq0_START  (0)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq0_END    (4)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq1_START  (5)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq1_END    (9)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq2_START  (10)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq2_END    (14)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq3_START  (15)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dq3_END    (19)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dm_START   (20)
#define SOC_HIPACKPHY_DX_DXNDCC1_dxctl_reg_rx_dcc_dm_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXNDCC2_UNION
 �ṹ˵��  : DX_DXNDCC2 �Ĵ����ṹ���塣��ַƫ����:0x26c+(p)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: Data block PHY DCC control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_reg_rx_dcc_dq4 : 5;  /* bit[0-4]  :  */
        unsigned int  dxctl_reg_rx_dcc_dq5 : 5;  /* bit[5-9]  :  */
        unsigned int  dxctl_reg_rx_dcc_dq6 : 5;  /* bit[10-14]:  */
        unsigned int  dxctl_reg_rx_dcc_dq7 : 5;  /* bit[15-19]:  */
        unsigned int  reserved             : 12; /* bit[20-31]:  */
    } reg;
} SOC_HIPACKPHY_DX_DXNDCC2_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq4_START  (0)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq4_END    (4)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq5_START  (5)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq5_END    (9)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq6_START  (10)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq6_END    (14)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq7_START  (15)
#define SOC_HIPACKPHY_DX_DXNDCC2_dxctl_reg_rx_dcc_dq7_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXNDCC3_UNION
 �ṹ˵��  : DX_DXNDCC3 �Ĵ����ṹ���塣��ַƫ����:0x270+(p)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: Data block PHY DCC control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_reg_tx_dcc_dq0 : 5;  /* bit[0-4]  :  */
        unsigned int  dxctl_reg_tx_dcc_dq1 : 5;  /* bit[5-9]  :  */
        unsigned int  dxctl_reg_tx_dcc_dq2 : 5;  /* bit[10-14]:  */
        unsigned int  dxctl_reg_tx_dcc_dq3 : 5;  /* bit[15-19]:  */
        unsigned int  dxctl_reg_tx_dcc_dm  : 5;  /* bit[20-24]:  */
        unsigned int  dxctl_reg_tx_dcc_dqs : 5;  /* bit[25-29]:  */
        unsigned int  reserved             : 2;  /* bit[30-31]:  */
    } reg;
} SOC_HIPACKPHY_DX_DXNDCC3_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq0_START  (0)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq0_END    (4)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq1_START  (5)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq1_END    (9)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq2_START  (10)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq2_END    (14)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq3_START  (15)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dq3_END    (19)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dm_START   (20)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dm_END     (24)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dqs_START  (25)
#define SOC_HIPACKPHY_DX_DXNDCC3_dxctl_reg_tx_dcc_dqs_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_HIPACKPHY_DX_DXNDCC4_UNION
 �ṹ˵��  : DX_DXNDCC4 �Ĵ����ṹ���塣��ַƫ����:0x274+(p)*0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: Data block PHY DCC control register. This register is for PHY control, and should not be modified.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dxctl_reg_tx_dcc_dq4 : 5;  /* bit[0-4]  :  */
        unsigned int  dxctl_reg_tx_dcc_dq5 : 5;  /* bit[5-9]  :  */
        unsigned int  dxctl_reg_tx_dcc_dq6 : 5;  /* bit[10-14]:  */
        unsigned int  dxctl_reg_tx_dcc_dq7 : 5;  /* bit[15-19]:  */
        unsigned int  reserved             : 12; /* bit[20-31]:  */
    } reg;
} SOC_HIPACKPHY_DX_DXNDCC4_UNION;
#endif
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq4_START  (0)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq4_END    (4)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq5_START  (5)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq5_END    (9)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq6_START  (10)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq6_END    (14)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq7_START  (15)
#define SOC_HIPACKPHY_DX_DXNDCC4_dxctl_reg_tx_dcc_dq7_END    (19)






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

#endif /* end of soc_hipackphy_interface.h */
