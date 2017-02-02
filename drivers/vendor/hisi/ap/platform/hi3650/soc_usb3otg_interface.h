/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_usb3otg_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-04-15 11:19:52
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��4��15��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_USB3OTG.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_USB3OTG_INTERFACE_H__
#define __SOC_USB3OTG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* �Ĵ���˵�������ܼĴ�������
   λ����UNION�ṹ:  SOC_USB3OTG_CAPLENGTH_UNION */
#define SOC_USB3OTG_CAPLENGTH_ADDR(base)              ((base) + (0x0000))

/* �Ĵ���˵�����ṹ����1
   λ����UNION�ṹ:  SOC_USB3OTG_HCSPARAMS1_UNION */
#define SOC_USB3OTG_HCSPARAMS1_ADDR(base)             ((base) + (0x0004))

/* �Ĵ���˵�����ṹ����2
   λ����UNION�ṹ:  SOC_USB3OTG_HCSPARAMS2_UNION */
#define SOC_USB3OTG_HCSPARAMS2_ADDR(base)             ((base) + (0x0008))

/* �Ĵ���˵�����ṹ����3
   λ����UNION�ṹ:  SOC_USB3OTG_HCSPARAMS3_UNION */
#define SOC_USB3OTG_HCSPARAMS3_ADDR(base)             ((base) + (0x000C))

/* �Ĵ���˵�����������Բ���
   λ����UNION�ṹ:  SOC_USB3OTG_HCCPARAMS_UNION */
#define SOC_USB3OTG_HCCPARAMS_ADDR(base)              ((base) + (0x0010))

/* �Ĵ���˵����Doorbell Arrayƫ�Ƶ�ַ
   λ����UNION�ṹ:  SOC_USB3OTG_DBOFF_UNION */
#define SOC_USB3OTG_DBOFF_ADDR(base)                  ((base) + (0x0014))

/* �Ĵ���˵����RunTimer�ռ�ƫ�Ƶ�ַ
   λ����UNION�ṹ:  SOC_USB3OTG_RTSOFF_UNION */
#define SOC_USB3OTG_RTSOFF_ADDR(base)                 ((base) + (0x0018))

/* �Ĵ���˵��������Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_USBCMD_UNION */
#define SOC_USB3OTG_USBCMD_ADDR(base)                 ((base) + (0x0020))

/* �Ĵ���˵����״̬�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_USBSTS_UNION */
#define SOC_USB3OTG_USBSTS_ADDR(base)                 ((base) + (0x0024))

/* �Ĵ���˵����ҳ��С�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_PAGESIZE_UNION */
#define SOC_USB3OTG_PAGESIZE_ADDR(base)               ((base) + (0x0028))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_USB3OTG_DNCTRL_UNION */
#define SOC_USB3OTG_DNCTRL_ADDR(base)                 ((base) + (0x0034))

/* �Ĵ���˵����Command Ring Control�Ĵ�����32λ
   λ����UNION�ṹ:  SOC_USB3OTG_CRCR_L_UNION */
#define SOC_USB3OTG_CRCR_L_ADDR(base)                 ((base) + (0x0038))

/* �Ĵ���˵����Command Ring Control�Ĵ�����32λ
   λ����UNION�ṹ:  SOC_USB3OTG_CRCR_H_UNION */
#define SOC_USB3OTG_CRCR_H_ADDR(base)                 ((base) + (0x003C))

/* �Ĵ���˵����Device Context Basic Address Array Pointer��32λ
   λ����UNION�ṹ:  SOC_USB3OTG_DCBAAP_L_UNION */
#define SOC_USB3OTG_DCBAAP_L_ADDR(base)               ((base) + (0x0050))

/* �Ĵ���˵����Device Context Basic Address Array Pointer��32λ
   λ����UNION�ṹ:  SOC_USB3OTG_DCBAAP_H_UNION */
#define SOC_USB3OTG_DCBAAP_H_ADDR(base)               ((base) + (0x0054))

/* �Ĵ���˵�������üĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_CONFIG_UNION */
#define SOC_USB3OTG_CONFIG_ADDR(base)                 ((base) + (0x0058))

/* �Ĵ���˵�����˿ڿ��ƺ�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_PORTSC_UNION */
#define SOC_USB3OTG_PORTSC_ADDR(base)                 ((base) + (0x0420))

/* �Ĵ���˵�����˿ڹ��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_PORTPMSC_20_UNION */
#define SOC_USB3OTG_PORTPMSC_20_ADDR(base)            ((base) + (0x0424))

/* �Ĵ���˵����Port Link Information�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_PORTLI_UNION */
#define SOC_USB3OTG_PORTLI_ADDR(base)                 ((base) + (0x0428))

/* �Ĵ���˵�����˿�LPM���ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_PORTHLPMC_20_UNION */
#define SOC_USB3OTG_PORTHLPMC_20_ADDR(base)           ((base) + (0x042C))

/* �Ĵ���˵����MicroFrame Index�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_MFINDEX_UNION */
#define SOC_USB3OTG_MFINDEX_ADDR(base)                ((base) + (0x440))

/* �Ĵ���˵����Interrupter Management�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_IMAN_UNION */
#define SOC_USB3OTG_IMAN_ADDR(base)                   ((base) + (0x460))

/* �Ĵ���˵����Interrupt Moderation�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_IMOD_UNION */
#define SOC_USB3OTG_IMOD_ADDR(base)                   ((base) + (0x464))

/* �Ĵ���˵����Event Ring Segment Table Size�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_ERSTSZ_UNION */
#define SOC_USB3OTG_ERSTSZ_ADDR(base)                 ((base) + (0x468))

/* �Ĵ���˵����Event Ring Segment Table����ַ��λ�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_ERSTBA_L_UNION */
#define SOC_USB3OTG_ERSTBA_L_ADDR(base)               ((base) + (0x470))

/* �Ĵ���˵����Event Ring Segment Table����ַ��λ�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_ERSTBA_H_UNION */
#define SOC_USB3OTG_ERSTBA_H_ADDR(base)               ((base) + (0x474))

/* �Ĵ���˵����Event Ring Dequeue Pointer��λ�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_ERDP_L_UNION */
#define SOC_USB3OTG_ERDP_L_ADDR(base)                 ((base) + (0x478))

/* �Ĵ���˵����Event Ring Dequeue Pointer��λ�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_ERDP_H_UNION */
#define SOC_USB3OTG_ERDP_H_ADDR(base)                 ((base) + (0x47C))

/* �Ĵ���˵����Doorbell�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_DB_UNION */
#define SOC_USB3OTG_DB_ADDR(base)                     ((base) + (0x480))

/* �Ĵ���˵����USB Legacy Support Capability�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_USBLEGSUP_UNION */
#define SOC_USB3OTG_USBLEGSUP_ADDR(base)              ((base) + (0x8A0))

/* �Ĵ���˵����USB legavy support control/status�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_USBLEGCTLSTS_UNION */
#define SOC_USB3OTG_USBLEGCTLSTS_ADDR(base)           ((base) + (0x8A4))

/* �Ĵ���˵����SOC�������üĴ���0
   λ����UNION�ṹ:  SOC_USB3OTG_GSBUSCFG0_UNION */
#define SOC_USB3OTG_GSBUSCFG0_ADDR(base)              ((base) + (0xC100))

/* �Ĵ���˵����SOC�������üĴ���1
   λ����UNION�ṹ:  SOC_USB3OTG_GSBUSCFG1_UNION */
#define SOC_USB3OTG_GSBUSCFG1_ADDR(base)              ((base) + (0xC104))

/* �Ĵ���˵��������ˮ�߿��ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_GTXTHRCFG_UNION */
#define SOC_USB3OTG_GTXTHRCFG_ADDR(base)              ((base) + (0xC108))

/* �Ĵ���˵��������ˮ�߿��ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_GRXTHRCFG_UNION */
#define SOC_USB3OTG_GRXTHRCFG_ADDR(base)              ((base) + (0xC10C))

/* �Ĵ���˵����ȫ�ֿ��ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_GCTL_UNION */
#define SOC_USB3OTG_GCTL_ADDR(base)                   ((base) + (0xC110))

/* �Ĵ���˵����ȫ�ֵ�Դ����״̬�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_GPMSTS_UNION */
#define SOC_USB3OTG_GPMSTS_ADDR(base)                 ((base) + (0xC114))

/* �Ĵ���˵����ȫ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_GSTS_UNION */
#define SOC_USB3OTG_GSTS_ADDR(base)                   ((base) + (0xC118))

/* �Ĵ���˵�����û����ƼĴ���1
   λ����UNION�ṹ:  SOC_USB3OTG_GUCTL1_UNION */
#define SOC_USB3OTG_GUCTL1_ADDR(base)                 ((base) + (0xC11C))

/* �Ĵ���˵�����������汾�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_GSNPSID_UNION */
#define SOC_USB3OTG_GSNPSID_ADDR(base)                ((base) + (0xC120))

/* �Ĵ���˵�����û����ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_GUCTL_UNION */
#define SOC_USB3OTG_GUCTL_ADDR(base)                  ((base) + (0xC12C))

/* �Ĵ���˵�������ߴ����ַ�Ĵ���L
   λ����UNION�ṹ:  SOC_USB3OTG_GBUSERRADDRL_UNION */
#define SOC_USB3OTG_GBUSERRADDRL_ADDR(base)           ((base) + (0xC130))

/* �Ĵ���˵�������ߴ����ַ�Ĵ���H
   λ����UNION�ṹ:  SOC_USB3OTG_GBUSERRADDRH_UNION */
#define SOC_USB3OTG_GBUSERRADDRH_ADDR(base)           ((base) + (0xC134))

/* �Ĵ���˵����Ӳ�������Ĵ���0
   λ����UNION�ṹ:  SOC_USB3OTG_GHWPARAMS0_UNION */
#define SOC_USB3OTG_GHWPARAMS0_ADDR(base)             ((base) + (0xC140))

/* �Ĵ���˵����Ӳ�������Ĵ���1
   λ����UNION�ṹ:  SOC_USB3OTG_GHWPARAMS1_UNION */
#define SOC_USB3OTG_GHWPARAMS1_ADDR(base)             ((base) + (0xC144))

/* �Ĵ���˵����Ӳ�������Ĵ���2
   λ����UNION�ṹ:  SOC_USB3OTG_GHWPARAMS2_UNION */
#define SOC_USB3OTG_GHWPARAMS2_ADDR(base)             ((base) + (0xC148))

/* �Ĵ���˵����Ӳ�������Ĵ���3
   λ����UNION�ṹ:  SOC_USB3OTG_GHWPARAMS3_UNION */
#define SOC_USB3OTG_GHWPARAMS3_ADDR(base)             ((base) + (0xC14C))

/* �Ĵ���˵����Ӳ�������Ĵ���4
   λ����UNION�ṹ:  SOC_USB3OTG_GHWPARAMS4_UNION */
#define SOC_USB3OTG_GHWPARAMS4_ADDR(base)             ((base) + (0xC150))

/* �Ĵ���˵����Ӳ�������Ĵ���5
   λ����UNION�ṹ:  SOC_USB3OTG_GHWPARAMS5_UNION */
#define SOC_USB3OTG_GHWPARAMS5_ADDR(base)             ((base) + (0xC154))

/* �Ĵ���˵����Ӳ�������Ĵ���6
   λ����UNION�ṹ:  SOC_USB3OTG_GHWPARAMS6_UNION */
#define SOC_USB3OTG_GHWPARAMS6_ADDR(base)             ((base) + (0xC158))

/* �Ĵ���˵����Ӳ�������Ĵ���7
   λ����UNION�ṹ:  SOC_USB3OTG_GHWPARAMS7_UNION */
#define SOC_USB3OTG_GHWPARAMS7_ADDR(base)             ((base) + (0xC15C))

/* �Ĵ���˵����Ӳ�������Ĵ���8
   λ����UNION�ṹ:  SOC_USB3OTG_GHWPARAMS8_UNION */
#define SOC_USB3OTG_GHWPARAMS8_ADDR(base)             ((base) + (0xC600))

/* �Ĵ���˵����Queue/FIFOʣ��ռ�debug�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_GDBGFIFOSPACE_UNION */
#define SOC_USB3OTG_GDBGFIFOSPACE_ADDR(base)          ((base) + (0xC160))

/* �Ĵ���˵����LTSSM debug�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_GDBGLTSSM_UNION */
#define SOC_USB3OTG_GDBGLTSSM_ADDR(base)              ((base) + (0xC164))

/* �Ĵ���˵����LNMCC debug�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_GDBGLNMCC_UNION */
#define SOC_USB3OTG_GDBGLNMCC_ADDR(base)              ((base) + (0xC168))

/* �Ĵ���˵����BMU debug�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_GCBGBMU_UNION */
#define SOC_USB3OTG_GCBGBMU_ADDR(base)                ((base) + (0xC16C))

/* �Ĵ���˵����LSPMUX debug�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_GDBGLSPMUX_UNION */
#define SOC_USB3OTG_GDBGLSPMUX_ADDR(base)             ((base) + (0xC170))

/* �Ĵ���˵����LSP debug�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_GDBGLSP_UNION */
#define SOC_USB3OTG_GDBGLSP_ADDR(base)                ((base) + (0xC174))

/* �Ĵ���˵����endpoint debug�Ĵ���0
   λ����UNION�ṹ:  SOC_USB3OTG_GDBGEPINFO0_UNION */
#define SOC_USB3OTG_GDBGEPINFO0_ADDR(base)            ((base) + (0xC178))

/* �Ĵ���˵����endpoint debug�Ĵ���1
   λ����UNION�ṹ:  SOC_USB3OTG_GDBGEPINFO1_UNION */
#define SOC_USB3OTG_GDBGEPINFO1_ADDR(base)            ((base) + (0xC17C))

/* �Ĵ���˵����USB2 PHY���üĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_GUSB2PHYCFG_UNION */
#define SOC_USB3OTG_GUSB2PHYCFG_ADDR(base)            ((base) + (0xC200))

/* �Ĵ���˵����USB3 PIPE���ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_GUSB3PIPECTL_UNION */
#define SOC_USB3OTG_GUSB3PIPECTL_ADDR(base)           ((base) + (0xC2C0))

/* �Ĵ���˵��������FIFOm��С���üĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_GTXFIFOSIZm_UNION */
#define SOC_USB3OTG_GTXFIFOSIZm_ADDR(base)            ((base) + (0xC300+m*0x4))

/* �Ĵ���˵��������FIFOn��С���üĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_GRXFIFOSIZn_UNION */
#define SOC_USB3OTG_GRXFIFOSIZn_ADDR(base, n)         ((base) + (0xC380+(n)*0x4))

/* �Ĵ���˵�����¼�buffer��ַ��32λ
   λ����UNION�ṹ:  SOC_USB3OTG_GEVNTADRLo_UNION */
#define SOC_USB3OTG_GEVNTADRLo_ADDR(base)             ((base) + (0xC400))

/* �Ĵ���˵�����¼�buffer��ַ��32λ
   λ����UNION�ṹ:  SOC_USB3OTG_GEVNTADRHi_UNION */
#define SOC_USB3OTG_GEVNTADRHi_ADDR(base)             ((base) + (0xC404))

/* �Ĵ���˵�����¼�buffer��С�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_GEVNTSIZ_UNION */
#define SOC_USB3OTG_GEVNTSIZ_ADDR(base)               ((base) + (0xC408))

/* �Ĵ���˵�����¼���Ŀ�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_GEVNTCOUNT_UNION */
#define SOC_USB3OTG_GEVNTCOUNT_ADDR(base)             ((base) + (0xC40C))

/* �Ĵ���˵����Device����FIFO���ȼ�
   λ����UNION�ṹ:  SOC_USB3OTG_GTXFIFOPRIDEV_UNION */
#define SOC_USB3OTG_GTXFIFOPRIDEV_ADDR(base)          ((base) + (0xC610))

/* �Ĵ���˵����Host����FIFO���ȼ�
   λ����UNION�ṹ:  SOC_USB3OTG_GTXFIFOPRIHST_UNION */
#define SOC_USB3OTG_GTXFIFOPRIHST_ADDR(base)          ((base) + (0xC618))

/* �Ĵ���˵����Host����FIFO���ȼ�
   λ����UNION�ṹ:  SOC_USB3OTG_GRXFIFOPRIHST_UNION */
#define SOC_USB3OTG_GRXFIFOPRIHST_ADDR(base)          ((base) + (0xC61C))

/* �Ĵ���˵����Host�ߵ����ȼ�Ȩ������
   λ����UNION�ṹ:  SOC_USB3OTG_GDMAHLRATIO_UNION */
#define SOC_USB3OTG_GDMAHLRATIO_ADDR(base)            ((base) + (0xC624))

/* �Ĵ���˵����֡���ȵ����Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_GFLADJ_UNION */
#define SOC_USB3OTG_GFLADJ_ADDR(base)                 ((base) + (0xC630))

/* �Ĵ���˵����device���üĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_DCFG_UNION */
#define SOC_USB3OTG_DCFG_ADDR(base)                   ((base) + (0xC700))

/* �Ĵ���˵����device���ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_DCTL_UNION */
#define SOC_USB3OTG_DCTL_ADDR(base)                   ((base) + (0xC704))

/* �Ĵ���˵����device�¼�ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_DEVNTEN_UNION */
#define SOC_USB3OTG_DEVNTEN_ADDR(base)                ((base) + (0xC708))

/* �Ĵ���˵����Device״̬�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_DSTS_UNION */
#define SOC_USB3OTG_DSTS_ADDR(base)                   ((base) + (0xC70C))

/* �Ĵ���˵����һ����������Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_DGCMDPAR_UNION */
#define SOC_USB3OTG_DGCMDPAR_ADDR(base)               ((base) + (0xC710))

/* �Ĵ���˵����һ��������ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_DGCMD_UNION */
#define SOC_USB3OTG_DGCMD_ADDR(base)                  ((base) + (0xC714))

/* �Ĵ���˵�����˵㼤��Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_DALEPENA_UNION */
#define SOC_USB3OTG_DALEPENA_ADDR(base)               ((base) + (0xC720))

/* �Ĵ���˵�����˵�m��������Ĵ���2
   λ����UNION�ṹ:  SOC_USB3OTG_DEPCMDPAR2m_UNION */
#define SOC_USB3OTG_DEPCMDPAR2m_ADDR(base)            ((base) + (0xC800+m*0x10))

/* �Ĵ���˵�����˵�m��������Ĵ���1
   λ����UNION�ṹ:  SOC_USB3OTG_DEPCMDPAR1m_UNION */
#define SOC_USB3OTG_DEPCMDPAR1m_ADDR(base)            ((base) + (0xC804+m*0x10))

/* �Ĵ���˵�����˵�m��������Ĵ���0
   λ����UNION�ṹ:  SOC_USB3OTG_DEPCMDPAR0m_UNION */
#define SOC_USB3OTG_DEPCMDPAR0m_ADDR(base)            ((base) + (0xC808+m*0x10))

/* �Ĵ���˵�����˵�m����Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_DEPCMDm_UNION */
#define SOC_USB3OTG_DEPCMDm_ADDR(base)                ((base) + (0xC80C+m*0x10))

/* �Ĵ���˵����OTG���üĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_OCFG_UNION */
#define SOC_USB3OTG_OCFG_ADDR(base)                   ((base) + (0xCC00))

/* �Ĵ���˵����OTG���ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_OCTL_UNION */
#define SOC_USB3OTG_OCTL_ADDR(base)                   ((base) + (0xCC04))

/* �Ĵ���˵����OTG�¼��Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_OEVNT_UNION */
#define SOC_USB3OTG_OEVNT_ADDR(base)                  ((base) + (0xCC08))

/* �Ĵ���˵����OTG�¼�ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_OEVNTEN_UNION */
#define SOC_USB3OTG_OEVNTEN_ADDR(base)                ((base) + (0xCC0C))

/* �Ĵ���˵����OTG״̬�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_OSTS_UNION */
#define SOC_USB3OTG_OSTS_ADDR(base)                   ((base) + (0xCC10))

/* �Ĵ���˵����ADP���üĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_ADPCFG_UNION */
#define SOC_USB3OTG_ADPCFG_ADDR(base)                 ((base) + (0xCC20))

/* �Ĵ���˵����ADP���ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_ADPCTL_UNION */
#define SOC_USB3OTG_ADPCTL_ADDR(base)                 ((base) + (0xCC24))

/* �Ĵ���˵����ADP�¼��Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_ADPEVNT_UNION */
#define SOC_USB3OTG_ADPEVNT_ADDR(base)                ((base) + (0xCC28))

/* �Ĵ���˵����ADP�¼��Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_ADPEVNTEN_UNION */
#define SOC_USB3OTG_ADPEVNTEN_ADDR(base)              ((base) + (0xCC28))

/* �Ĵ���˵����BC���üĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_BCFG_UNION */
#define SOC_USB3OTG_BCFG_ADDR(base)                   ((base) + (0xCC30))

/* �Ĵ���˵����BC�¼��Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_BCEVT_UNION */
#define SOC_USB3OTG_BCEVT_ADDR(base)                  ((base) + (0xCC38))

/* �Ĵ���˵����BC�¼�ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_BCEVTEN_UNION */
#define SOC_USB3OTG_BCEVTEN_ADDR(base)                ((base) + (0xCC3C))





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
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_CAPLENGTH_UNION
 �ṹ˵��  : CAPLENGTH �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x01000020�����:32
 �Ĵ���˵��: ���ܼĴ�������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CAPLENGTH  : 8;  /* bit[0-7]  : ָʾ�����Ĵ�����ַƫ���� */
        unsigned int  reserved   : 8;  /* bit[8-15] : ������ */
        unsigned int  HCIVERSION : 16; /* bit[16-31]: ָʾxHCIЭ��汾�� */
    } reg;
} SOC_USB3OTG_CAPLENGTH_UNION;
#endif
#define SOC_USB3OTG_CAPLENGTH_CAPLENGTH_START   (0)
#define SOC_USB3OTG_CAPLENGTH_CAPLENGTH_END     (7)
#define SOC_USB3OTG_CAPLENGTH_HCIVERSION_START  (16)
#define SOC_USB3OTG_CAPLENGTH_HCIVERSION_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_HCSPARAMS1_UNION
 �ṹ˵��  : HCSPARAMS1 �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x0200017F�����:32
 �Ĵ���˵��: �ṹ����1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MaxSlots : 8;  /* bit[0-7]  : ָʾHost��������֧�ֵ����Device Context���ݽṹ������Doorbell Array entry��������Ч����1~255������0�������� */
        unsigned int  MaxIntrs : 11; /* bit[8-18] : ָʾHOST�����������ṩ���ٸ��жϸ�SOC��
                                                    ����ֵͬʱ������Runtime�Ĵ����ռ���ж��ٸ��жϼĴ�������Ч��ֵ��Χ��0x1~0x400.��ֵ0�����塣 */
        unsigned int  reserved : 5;  /* bit[19-23]: ������ */
        unsigned int  MaxPorts : 8;  /* bit[24-31]: ָʾHOST��������֧�ֵ����port������ͬʱ����ֵ������Operational�Ĵ����ռ��ڣ�Port���üĴ�����������ֵ����Ч��Χ0x1~0xFF�� */
    } reg;
} SOC_USB3OTG_HCSPARAMS1_UNION;
#endif
#define SOC_USB3OTG_HCSPARAMS1_MaxSlots_START  (0)
#define SOC_USB3OTG_HCSPARAMS1_MaxSlots_END    (7)
#define SOC_USB3OTG_HCSPARAMS1_MaxIntrs_START  (8)
#define SOC_USB3OTG_HCSPARAMS1_MaxIntrs_END    (18)
#define SOC_USB3OTG_HCSPARAMS1_MaxPorts_START  (24)
#define SOC_USB3OTG_HCSPARAMS1_MaxPorts_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_HCSPARAMS2_UNION
 �ṹ˵��  : HCSPARAMS2 �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x040000F1�����:32
 �Ĵ���˵��: �ṹ����2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  IST                   : 4;  /* bit[0-3]  : ��ȷ�� */
        unsigned int  ERST_Max              : 4;  /* bit[4-7]  : ָʾEvent Ring Segment Table entry����:2ERST_Max����ERST_Max����Ч��ֵΪ0~15�� */
        unsigned int  reserved              : 13; /* bit[8-20] : ������ */
        unsigned int  Max_Scratchpad_Bufs_H : 5;  /* bit[21-25]: ָʾsoftware��Ҫ��������Scratchpad Buffer��xHC����Ч��ֵ0~31. */
        unsigned int  SPR                   : 1;  /* bit[26]   :  */
        unsigned int  Max_Scratchpad_Bufs_L : 5;  /* bit[27-31]: ָʾsoftware��Ҫ��������Scratchpad Buffer��xHC����Ч��ֵ0~31. */
    } reg;
} SOC_USB3OTG_HCSPARAMS2_UNION;
#endif
#define SOC_USB3OTG_HCSPARAMS2_IST_START                    (0)
#define SOC_USB3OTG_HCSPARAMS2_IST_END                      (3)
#define SOC_USB3OTG_HCSPARAMS2_ERST_Max_START               (4)
#define SOC_USB3OTG_HCSPARAMS2_ERST_Max_END                 (7)
#define SOC_USB3OTG_HCSPARAMS2_Max_Scratchpad_Bufs_H_START  (21)
#define SOC_USB3OTG_HCSPARAMS2_Max_Scratchpad_Bufs_H_END    (25)
#define SOC_USB3OTG_HCSPARAMS2_SPR_START                    (26)
#define SOC_USB3OTG_HCSPARAMS2_SPR_END                      (26)
#define SOC_USB3OTG_HCSPARAMS2_Max_Scratchpad_Bufs_L_START  (27)
#define SOC_USB3OTG_HCSPARAMS2_Max_Scratchpad_Bufs_L_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_HCSPARAMS3_UNION
 �ṹ˵��  : HCSPARAMS3 �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x07FF0000�����:32
 �Ĵ���˵��: �ṹ����3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  U1_Exit_Latency : 8;  /* bit[0-7]  : root hub Port Link State��U1��U0�������ʱʱ�䡣�������Ч��ֵ8'h0~8'h0A��������ֵΪ������ */
        unsigned int  reserved        : 8;  /* bit[8-15] : ������ */
        unsigned int  U2_Exit_Latency : 16; /* bit[16-31]: root hub Port Link State��U2��U0�������ʱʱ�䡣�������Ч��ֵ16'h0~16'h07FF��������ֵΪ������ */
    } reg;
} SOC_USB3OTG_HCSPARAMS3_UNION;
#endif
#define SOC_USB3OTG_HCSPARAMS3_U1_Exit_Latency_START  (0)
#define SOC_USB3OTG_HCSPARAMS3_U1_Exit_Latency_END    (7)
#define SOC_USB3OTG_HCSPARAMS3_U2_Exit_Latency_START  (16)
#define SOC_USB3OTG_HCSPARAMS3_U2_Exit_Latency_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_HCCPARAMS_UNION
 �ṹ˵��  : HCCPARAMS �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x0220F06C�����:32
 �Ĵ���˵��: �������Բ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  AC64       : 1;  /* bit[0]    : ָʾ����ϵͳ�ڴ��������
                                                      0:32bitϵͳ�ڴ��ַ��Χ��
                                                      1:64bitϵͳ�ڴ��ַ��Χ�� */
        unsigned int  BNC        : 1;  /* bit[1]    : HOST�������Ƿ�ִ��Bandwidth Negotiation��
                                                      0����ִ�У�
                                                      1��ִ�С� */
        unsigned int  CSZ        : 1;  /* bit[2]    : HOST������ʹ�õ�Context���ݽṹ��С��
                                                      0��ʹ��32 Byte��С��Context���ݽṹ��
                                                      1��ʹ��64 Byte��С��Context���ݽṹ�� */
        unsigned int  PPC        : 1;  /* bit[3]    : ָʾHOST�������Ƿ����Port Power Switches��
                                                      0����������
                                                      1�������� */
        unsigned int  PIND       : 1;  /* bit[4]    : ָʾHOST��������root hub ports�Ƿ�֧��port indicator control����Ϊ1ʱ����HOST��״̬����ƼĴ����д���һ��RW��bit�����ڿ���port indicator��״̬��
                                                      0����֧�֣�
                                                      1��֧�֡� */
        unsigned int  LHRC       : 1;  /* bit[5]    : ָʾHOST�������Ƿ�֧��Light Host Controller Reset����λӰ��USBCMD��LHCRSTλ�Ĺ��ܡ�
                                                      0����֧�֣�
                                                      1��֧�֡� */
        unsigned int  LTC        : 1;  /* bit[6]    : ָʾ�Ƿ�֧��Latency Tolerance Messaging���ԡ�
                                                      0����֧�֣�
                                                      1��֧�֡� */
        unsigned int  NSS        : 1;  /* bit[7]    : ָʾ�Ƿ�֧��Secondary Stream IDs��
                                                      0��֧�֣�
                                                      1����֧�֡� */
        unsigned int  PAE        : 1;  /* bit[8]    : ���� */
        unsigned int  reserved   : 3;  /* bit[9-11] : ���� */
        unsigned int  MaxPSASize : 4;  /* bit[12-15]: ָʾ��֧�ֵ����Primary Stream Array��С�����㷽����2MaxPSASize+1����ֵ��Ч��Χ1~15�� */
        unsigned int  xECP       : 16; /* bit[16-31]: ָʾextended capability�Ĵ��ڵ�ַ������ֵ���ڼ����1��extended capabitity����ʼ��ַ���������£�
                                                      BASE+(xECP<<2)��BASE����������Ĵ����Ļ���ַ�� */
    } reg;
} SOC_USB3OTG_HCCPARAMS_UNION;
#endif
#define SOC_USB3OTG_HCCPARAMS_AC64_START        (0)
#define SOC_USB3OTG_HCCPARAMS_AC64_END          (0)
#define SOC_USB3OTG_HCCPARAMS_BNC_START         (1)
#define SOC_USB3OTG_HCCPARAMS_BNC_END           (1)
#define SOC_USB3OTG_HCCPARAMS_CSZ_START         (2)
#define SOC_USB3OTG_HCCPARAMS_CSZ_END           (2)
#define SOC_USB3OTG_HCCPARAMS_PPC_START         (3)
#define SOC_USB3OTG_HCCPARAMS_PPC_END           (3)
#define SOC_USB3OTG_HCCPARAMS_PIND_START        (4)
#define SOC_USB3OTG_HCCPARAMS_PIND_END          (4)
#define SOC_USB3OTG_HCCPARAMS_LHRC_START        (5)
#define SOC_USB3OTG_HCCPARAMS_LHRC_END          (5)
#define SOC_USB3OTG_HCCPARAMS_LTC_START         (6)
#define SOC_USB3OTG_HCCPARAMS_LTC_END           (6)
#define SOC_USB3OTG_HCCPARAMS_NSS_START         (7)
#define SOC_USB3OTG_HCCPARAMS_NSS_END           (7)
#define SOC_USB3OTG_HCCPARAMS_PAE_START         (8)
#define SOC_USB3OTG_HCCPARAMS_PAE_END           (8)
#define SOC_USB3OTG_HCCPARAMS_MaxPSASize_START  (12)
#define SOC_USB3OTG_HCCPARAMS_MaxPSASize_END    (15)
#define SOC_USB3OTG_HCCPARAMS_xECP_START        (16)
#define SOC_USB3OTG_HCCPARAMS_xECP_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DBOFF_UNION
 �ṹ˵��  : DBOFF �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00001280�����:32
 �Ĵ���˵��: Doorbell Arrayƫ�Ƶ�ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved              : 2;  /* bit[0-1] : ���� */
        unsigned int  Doorbell_Array_Offset : 30; /* bit[2-31]: ������Doorbell Array��ƫ�Ƶ�ַ������ֵͨ����32bit����ģ����������֧��virtualization����ô������PAGESIZE���롣 */
    } reg;
} SOC_USB3OTG_DBOFF_UNION;
#endif
#define SOC_USB3OTG_DBOFF_Doorbell_Array_Offset_START  (2)
#define SOC_USB3OTG_DBOFF_Doorbell_Array_Offset_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_RTSOFF_UNION
 �ṹ˵��  : RTSOFF �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00008800�����:32
 �Ĵ���˵��: RunTimer�ռ�ƫ�Ƶ�ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                      : 5;  /* bit[0-4] : ���� */
        unsigned int  Runtime_Register_Space_Offset : 27; /* bit[5-31]: Runtime�Ĵ����ռ��ƫ�Ƶ�ַ�� */
    } reg;
} SOC_USB3OTG_RTSOFF_UNION;
#endif
#define SOC_USB3OTG_RTSOFF_Runtime_Register_Space_Offset_START  (5)
#define SOC_USB3OTG_RTSOFF_Runtime_Register_Space_Offset_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_USBCMD_UNION
 �ṹ˵��  : USBCMD �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Run_Stop : 1;  /* bit[0]    : ������Ϊ1��xHC����ִ�в����������Ϊ0��xHCֹͣ�κεĲ�������ȥhalts��
                                                    0��STOP��
                                                    1��RUN�� */
        unsigned int  HCRST    : 1;  /* bit[1]    : ������ڶ�xHC���и�λ���������������Ϊ1ʱ��USB2���ж˿ڲ��ᷢ��USB reset������������USB3 Root Hub���ж˿ڷ���Hot��Warm Reset���������ҵ�reset process��ɺ󣬿��������Զ�������0��
                                                    0����λ����������
                                                    1��ִ�и�λ������ */
        unsigned int  INTE     : 1;  /* bit[2]    : HOSTϵͳ���ж�ʹ��λ��
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  HSEE     : 1;  /* bit[3]    : hostϵͳ����ʹ�ܡ�����bitΪ1������USBSTS�Ĵ�����HSEλҲΪ1ʱ����ôxHC�ͻᷢ��һ��out-of-band�Ĵ����źŸ�host��
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  reserved_0: 3;  /* bit[4-6]  : ������ */
        unsigned int  LHCRST   : 1;  /* bit[7]    : ��HCCPARAMS��LHRCλΪ1�ǣ���ô����������xHC���и�λ���������ǲ���Ӱ��ports��״̬����������Auxiliary�ڵļĴ���������ֵ���䡣
                                                    0����λ�����Ѿ���ɣ�
                                                    1����λ�������ڽ��С� */
        unsigned int  CSS      : 1;  /* bit[8]    : ������Save״̬����HCHλΪ1��������ø�λΪ1ʱ����ôxHC�ͻ��ڲ����κ�״̬������Щ״̬������xHC����Restore����ʹ�á�����������ø�bitΪ0�����ߵ�HCHΪ0ʱ���ø�bitΪ1����ô���ᷢ��Save�Ĳ�����
                                                    0����ִ��Save������
                                                    1�����HCH״̬����Save������ */
        unsigned int  CRS      : 1;  /* bit[9]    : ��������Restore״̬������bit����Ϊ1����HCHΪ1ʱ������Restore���������ǵ���bitΪ1��Run/StopλҲΪ1������HCHΪ0�����߸�λΪ0ʱ�������ᷢ��Restore������
                                                    0��������Restore������
                                                    1�����Run/Stop��HCH������Restore������ */
        unsigned int  EWE      : 1;  /* bit[10]   : ��Ϊ1����MFINDEX�Ĵ�����0x03FFF��0x0ʱ���ͻᷢ��һ��MFINDEX Wrap Event��Ϊ0ʱ������ */
        unsigned int  EU3S     : 1;  /* bit[11]   : ��Ϊ1���Ҵ���U3��disconnect��disabled����powered-off״̬ʱ��ֹͣMFINDEX�Ĵ�����������Ϊ0���Ҵ���disconnect��disabled����powered-off״̬ʱ��ֹͣMFINDEX�Ĵ��������� */
        unsigned int  reserved_1: 20; /* bit[12-31]: ���� */
    } reg;
} SOC_USB3OTG_USBCMD_UNION;
#endif
#define SOC_USB3OTG_USBCMD_Run_Stop_START  (0)
#define SOC_USB3OTG_USBCMD_Run_Stop_END    (0)
#define SOC_USB3OTG_USBCMD_HCRST_START     (1)
#define SOC_USB3OTG_USBCMD_HCRST_END       (1)
#define SOC_USB3OTG_USBCMD_INTE_START      (2)
#define SOC_USB3OTG_USBCMD_INTE_END        (2)
#define SOC_USB3OTG_USBCMD_HSEE_START      (3)
#define SOC_USB3OTG_USBCMD_HSEE_END        (3)
#define SOC_USB3OTG_USBCMD_LHCRST_START    (7)
#define SOC_USB3OTG_USBCMD_LHCRST_END      (7)
#define SOC_USB3OTG_USBCMD_CSS_START       (8)
#define SOC_USB3OTG_USBCMD_CSS_END         (8)
#define SOC_USB3OTG_USBCMD_CRS_START       (9)
#define SOC_USB3OTG_USBCMD_CRS_END         (9)
#define SOC_USB3OTG_USBCMD_EWE_START       (10)
#define SOC_USB3OTG_USBCMD_EWE_END         (10)
#define SOC_USB3OTG_USBCMD_EU3S_START      (11)
#define SOC_USB3OTG_USBCMD_EU3S_END        (11)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_USBSTS_UNION
 �ṹ˵��  : USBSTS �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000801�����:32
 �Ĵ���˵��: ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HCH      : 1;  /* bit[0]    : ָʾ�Ƿ����Halted״̬��
                                                    0��û�н���Halted״̬��
                                                    1������Halted״̬�� */
        unsigned int  reserved_0: 1;  /* bit[1]    : ���� */
        unsigned int  HSE      : 1;  /* bit[2]    : HOSTϵͳ����ָʾ��
                                                    0��������
                                                    1���д��� */
        unsigned int  EINT     : 1;  /* bit[3]    : Event�ж�ָʾ��
                                                    0��û��Interrupt Pending�жϴ�0��1�Ĺ��̣�
                                                    1����Interrupt Pending�жϴ�0��1�Ĺ��̡� */
        unsigned int  PCD      : 1;  /* bit[4]    : �˿ڱ仯��⡣
                                                    0��portû�б仯��
                                                    1��port�б仯�� */
        unsigned int  reserved_1: 3;  /* bit[5-7]  : ���� */
        unsigned int  SSS      : 1;  /* bit[8]    : Save State Statusָʾλ��
                                                    0��Save������ɣ�
                                                    1��USBCMD��CSSΪ1���ҷ�����Save������ */
        unsigned int  RSS      : 1;  /* bit[9]    : Restore State Statusָʾλ��
                                                    0��Restore������ɣ�
                                                    1��USBCMD��CRSΪ1���ҷ�����Restore������ */
        unsigned int  SRE      : 1;  /* bit[10]   : ָʾSave��Restore�����Ƿ����˴���
                                                    0��û�У�
                                                    1���С� */
        unsigned int  CNR      : 1;  /* bit[11]   : ָʾ�������Ƿ��Ѿ�׼���á���û��׼���ã�������ܽ���Doorbell��Operation�Ĵ����Ĳ�������������Hardware��λ����ֵΪ1��ָ�����Խ��ܼĴ��������������������0��
                                                    0��ready��
                                                    1��not ready�� */
        unsigned int  HCE      : 1;  /* bit[12]   : xHC�ڲ��д���ָʾ�����д���ʱ�������Ҫ���¸�λ������xHC��
                                                    0��û�д���
                                                    1�������˴��� */
        unsigned int  reserved_2: 19; /* bit[13-31]: ������ */
    } reg;
} SOC_USB3OTG_USBSTS_UNION;
#endif
#define SOC_USB3OTG_USBSTS_HCH_START       (0)
#define SOC_USB3OTG_USBSTS_HCH_END         (0)
#define SOC_USB3OTG_USBSTS_HSE_START       (2)
#define SOC_USB3OTG_USBSTS_HSE_END         (2)
#define SOC_USB3OTG_USBSTS_EINT_START      (3)
#define SOC_USB3OTG_USBSTS_EINT_END        (3)
#define SOC_USB3OTG_USBSTS_PCD_START       (4)
#define SOC_USB3OTG_USBSTS_PCD_END         (4)
#define SOC_USB3OTG_USBSTS_SSS_START       (8)
#define SOC_USB3OTG_USBSTS_SSS_END         (8)
#define SOC_USB3OTG_USBSTS_RSS_START       (9)
#define SOC_USB3OTG_USBSTS_RSS_END         (9)
#define SOC_USB3OTG_USBSTS_SRE_START       (10)
#define SOC_USB3OTG_USBSTS_SRE_END         (10)
#define SOC_USB3OTG_USBSTS_CNR_START       (11)
#define SOC_USB3OTG_USBSTS_CNR_END         (11)
#define SOC_USB3OTG_USBSTS_HCE_START       (12)
#define SOC_USB3OTG_USBSTS_HCE_END         (12)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_PAGESIZE_UNION
 �ṹ˵��  : PAGESIZE �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000001�����:32
 �Ĵ���˵��: ҳ��С�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_size : 16; /* bit[0-15] : ���ڼ���xHC֧�ֵ�page��С�����㷽����2(page_size+12)�� */
        unsigned int  reserved  : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_USB3OTG_PAGESIZE_UNION;
#endif
#define SOC_USB3OTG_PAGESIZE_page_size_START  (0)
#define SOC_USB3OTG_PAGESIZE_page_size_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DNCTRL_UNION
 �ṹ˵��  : DNCTRL �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  notification_enable : 16; /* bit[0-15] : ���� */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_USB3OTG_DNCTRL_UNION;
#endif
#define SOC_USB3OTG_DNCTRL_notification_enable_START  (0)
#define SOC_USB3OTG_DNCTRL_notification_enable_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_CRCR_L_UNION
 �ṹ˵��  : CRCR_L �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: Command Ring Control�Ĵ�����32λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RCS                  : 1;  /* bit[0]   : Ring Cycle State����λ��ͬ��xHC��Consumer Cycle State(CCS)״̬����Command Ring Running(CRR)Ϊ1ʱ��д��bit��Ч�� */
        unsigned int  CS                   : 1;  /* bit[1]   : Command Stop��������Ϊ1ʱ������ɵ�ǰ����ִ�е�command��ֹͣCommand Ring�Ĳ�����������Command Ring Stopped����Command Completion Event��Command TRBָ������ΪCommand Ring Dequeue Pointer����ֵ��
                                                               ���´���дDB Reasionʱ����дrestart the command Ring operation��
                                                               ��CRRΪ0ʱ����bitд��Ч�� */
        unsigned int  CA                   : 1;  /* bit[2]   : Command Abort��������Ϊ1ʱ��������ֹ��ǰ������ִ�е�command��ֹͣCommand Ring������Command Ring Stopped����Command Completion Event��
                                                               ���´���дDB Reasionʱ����дrestart the command Ring operation��
                                                               ��CRRΪ0ʱ����bitд��Ч�� */
        unsigned int  CRR                  : 1;  /* bit[3]   : Command Ring Running����R/SλΪ1����Doorbell�Ĵ�����DB Reasion��ΪController Commandʱ����bit��1����CS��CAΪ1������R/SΪ0ʱ����bit��0. */
        unsigned int  reserved             : 2;  /* bit[4-5] : ���� */
        unsigned int  command_ring_pointor : 26; /* bit[6-31]: ��CRCR_Hһ��ָ��Command Ring���ݽṹ�Ļ���ַ��64 Byte���룩����CRR=1ʱ����bitд��Ч������Զ����0. */
    } reg;
} SOC_USB3OTG_CRCR_L_UNION;
#endif
#define SOC_USB3OTG_CRCR_L_RCS_START                   (0)
#define SOC_USB3OTG_CRCR_L_RCS_END                     (0)
#define SOC_USB3OTG_CRCR_L_CS_START                    (1)
#define SOC_USB3OTG_CRCR_L_CS_END                      (1)
#define SOC_USB3OTG_CRCR_L_CA_START                    (2)
#define SOC_USB3OTG_CRCR_L_CA_END                      (2)
#define SOC_USB3OTG_CRCR_L_CRR_START                   (3)
#define SOC_USB3OTG_CRCR_L_CRR_END                     (3)
#define SOC_USB3OTG_CRCR_L_command_ring_pointor_START  (6)
#define SOC_USB3OTG_CRCR_L_command_ring_pointor_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_CRCR_H_UNION
 �ṹ˵��  : CRCR_H �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Command Ring Control�Ĵ�����32λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  command_ring_pointor : 32; /* bit[0-31]: ��CRCR_L[31��6]һ������Command Ring���ݽṹ�Ļ���ַ����CRR=1ʱ����bitд��Ч������Զ����0. */
    } reg;
} SOC_USB3OTG_CRCR_H_UNION;
#endif
#define SOC_USB3OTG_CRCR_H_command_ring_pointor_START  (0)
#define SOC_USB3OTG_CRCR_H_command_ring_pointor_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DCBAAP_L_UNION
 �ṹ˵��  : DCBAAP_L �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: Device Context Basic Address Array Pointer��32λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved     : 6;  /* bit[0-5] : ���� */
        unsigned int  DCBAAR_point : 26; /* bit[6-31]: ��DCBAAP_Hһ����Device Context Basic Address Array���ݻ����Ļ���ַ�� */
    } reg;
} SOC_USB3OTG_DCBAAP_L_UNION;
#endif
#define SOC_USB3OTG_DCBAAP_L_DCBAAR_point_START  (6)
#define SOC_USB3OTG_DCBAAP_L_DCBAAR_point_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DCBAAP_H_UNION
 �ṹ˵��  : DCBAAP_H �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: Device Context Basic Address Array Pointer��32λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DCBAAR_point : 32; /* bit[0-31]: ��DCBAAP_L[31��6]һ����Device Context Basic Address Array���ݻ����Ļ���ַ�� */
    } reg;
} SOC_USB3OTG_DCBAAP_H_UNION;
#endif
#define SOC_USB3OTG_DCBAAP_H_DCBAAR_point_START  (0)
#define SOC_USB3OTG_DCBAAP_H_DCBAAR_point_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_CONFIG_UNION
 �ṹ˵��  : CONFIG �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MaxSlotsEn : 8;  /* bit[0-7] : ָ��ʹ�ܵ�����Device Slots����Ч��ֵ��Χ0~MaxSlots.0��ʾ�ر����е�Device Slots�� */
        unsigned int  reserved   : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_USB3OTG_CONFIG_UNION;
#endif
#define SOC_USB3OTG_CONFIG_MaxSlotsEn_START  (0)
#define SOC_USB3OTG_CONFIG_MaxSlotsEn_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_PORTSC_UNION
 �ṹ˵��  : PORTSC �Ĵ����ṹ���塣��ַƫ����:0x0420����ֵ:0x000002A0�����:32
 �Ĵ���˵��: �˿ڿ��ƺ�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CCS       : 1;  /* bit[0]    : ָʾ��ǰ����״̬����PP=0ʱ����bitΪ0��
                                                     0�����豸���ӣ�
                                                     1��û���豸���ӡ� */
        unsigned int  PED       : 1;  /* bit[1]    : �˿�ʹ����رա���λֻ����xHCʹ�ܸ�bit�����رն˿�ʱ������reset�⣬�����κε����ݴ��䶼�ڸ�port��������
                                                     ����USB2Э��˿ڣ����˿ڹرպ������Ҫreset�ö˿�(PR=1)���Ӷ�PED=1�˿�ʹ�ܡ�
                                                     ����USB3Э��˿ڣ�
                                                     ���˿ڴ���Polling״̬���˿�Ӧ���Զ�ʹ�ܲ����ڳɹ����link training��PED=1�����˿ڹر�ʱ�������Ҫ����PLSΪ5���Ӷ��˿ڽ���disconnect״̬��
                                                     ��PR=1ʱ��PED�����Ϊ0��reset��ɺ󣬵�PR��1��Ϊ0��PED��1��
                                                     0���˿ڹرգ�
                                                     1���˿�ʹ�ܡ� */
        unsigned int  reserved_0: 1;  /* bit[2]    : ���� */
        unsigned int  OCA       : 1;  /* bit[3]    : Over-current Active��ָʾ�˿��Ƿ�����������ҹ���������ȥ�����ܹ��Զ���0��
                                                     0���˿�û�й�������
                                                     1���˿ڲ����˹������� */
        unsigned int  PR        : 1;  /* bit[4]    : Port Reset����������ø�bitΪ1ʱ��USB���߷���reset���С�PRһֱ����Ϊ1ֱ��reset������ɡ���PPΪ0ʱ����bitΪ0��
                                                     0���˿�û���ڸ�λ�У�
                                                     1���˿ڸ�λ�� */
        unsigned int  PLS       : 4;  /* bit[5-8]  : Port Link Stateָʾ��
                                                     0��U0״̬��
                                                     1��U1״̬��
                                                     2��U2״̬��
                                                     3��U3״̬��
                                                     4��Disable״̬��
                                                     5��RxDelect״̬��
                                                     6��Inactive״̬��
                                                     7��Polling״̬��
                                                     8��Recovery״̬��
                                                     9��Hot Reset״̬��
                                                     10��Compliance Mode״̬��
                                                     11��Test Mode״̬��
                                                     12~14��������
                                                     15��Resume״̬�� */
        unsigned int  PP        : 1;  /* bit[9]    : Port Powerָʾ����PPC=1��xHC���е�Դ���ƿ��أ����Ҹ�bit�ܹ���ӳ�ÿ��ص�״̬(0=off, 1=on)����PPC=0��xHC�����е�Դ���ƿ��أ�ÿ���˿ڶ�Ӳ�����ӵ�Դ��
                                                     0���˿ڴ���Powered-off״̬��
                                                     1���˿ڲ�����Powered-off״̬�� */
        unsigned int  PortSpeed : 4;  /* bit[10-13]: ָʾattached�豸�ٶȡ�����ֻ����CCS=1ʱ�������塣
                                                     0��û�ж�����ٶȣ�
                                                     1-15��Protocol Speed ID(PSI)�� */
        unsigned int  PIC       : 2;  /* bit[14-15]: Port Indicator Control����PIND=0ʱ�����ø��������á�
                                                     0��OFF��
                                                     1��Amber��
                                                     2��Green��
                                                     ��PP=0������Ϊ0�� */
        unsigned int  LWS       : 1;  /* bit[16]   : Port Link State Write Strobe������bitΪ1��������PLS��д��ֵ��������PLSд�����ֵ��Ч�� */
        unsigned int  CSC       : 1;  /* bit[17]   : Connect Status Change��ָʾCCS��Cold Attach Status(CAS)�Ƿ��б仯�����������PP=0ʹCCS�任�������������WPR=1ʹCAS�仯ʱ����bit������1����CSC�Ѿ�Ϊ1�������û�н�������������κεĶ˿��豸����״̬�����仯��xHC���Ὣ��bit��1�� */
        unsigned int  PEC       : 1;  /* bit[18]   : Port Enable/Disable Changeָʾ����������PP=0�����PED�仯���ܽ���bit��1������USB2Э��˿ڣ�ֻ����port disable�����²�д1������USB3Э��˿ڣ���bit����д1��
                                                     0��PEDû�б仯��
                                                     1��PED�б仯�� */
        unsigned int  WRC       : 1;  /* bit[19]   : Warm Port Reset Changeָʾ����Warm Reset������ɺ󣬸�bit��1����������PP=0��PED=0��ǿ�Ʒ����Warm Reset���ܽ���bit��1����bitֻ��USB3Э��˿����ã�USB2Э��˿�Ϊ������
                                                     0��no change��
                                                     1��Wram Reset Complete�� */
        unsigned int  OCC       : 1;  /* bit[20]   : Over-current Changeָʾ����OCA��0��1�����ߴ�1��0�����������bit��1�� */
        unsigned int  PRC       : 1;  /* bit[21]   : Port Reset Changeָʾ����PR��1��0ʱ����bit��1.��������PP=0��PED=0ǿ�Ƹ�λֹͣ�����ܽ���bit��1.
                                                     0��on change;
                                                     1��reset complete�� */
        unsigned int  PLC       : 1;  /* bit[22]   : Port Link State Changeָʾ�������µ�PLS�仯ʱ����bit��1��
                                                     U3 -> Resume;
                                                     Resume -> Recovery -> U0;
                                                     Resume -> U0;
                                                     U3 -> Recovery -> U0;
                                                     U3 -> U0;
                                                     U2 -> U0;
                                                     U1 -> U0;
                                                     Any state -> Inactive.
                                                     0��no change;
                                                     1��Link state change. */
        unsigned int  CEC       : 1;  /* bit[23]   : Port Config Error Change��ָʾ�˿�������link partnerʱʧ�ܡ���bitֻ��USB3Э��˿���Ч��USB2Э��˿ڸ�bitΪ������
                                                     0��no change��
                                                     1��Port config error detected�� */
        unsigned int  CAS       : 1;  /* bit[24]   : Cold Attach Status. */
        unsigned int  WCE       : 1;  /* bit[25]   : Wake on Connect Enale.����bit��1��ʹ�ܶ˿ڽ��豸connect��Ϊһ��wake-up event�� */
        unsigned int  WDE       : 1;  /* bit[26]   : Wake on Disconnect Enable������bit��1��ʹ�ܶ˿ڽ��豸disconnect��Ϊһ��wake-up event�� */
        unsigned int  WOE       : 1;  /* bit[27]   : Wake on Over-current Enable.����bit��1��ʹ�ܶ˿ڽ�over-current��Ϊһ��wake-up event�� */
        unsigned int  reserved_1: 2;  /* bit[28-29]: ���� */
        unsigned int  DR        : 1;  /* bit[30]   : Device Removable.ָʾ�Խӵ��豸�Ƿ���Ƴ���
                                                     0���Խ��豸���Ƴ���
                                                     1���Խ��豸�����Ƴ��� */
        unsigned int  WPR       : 1;  /* bit[31]   : Warm Port Resetָʾ�����������Ϊ1������Warm Reset��������bitֻ��USBЭ��˿���Ч��USB2�˿ڱ����� */
    } reg;
} SOC_USB3OTG_PORTSC_UNION;
#endif
#define SOC_USB3OTG_PORTSC_CCS_START        (0)
#define SOC_USB3OTG_PORTSC_CCS_END          (0)
#define SOC_USB3OTG_PORTSC_PED_START        (1)
#define SOC_USB3OTG_PORTSC_PED_END          (1)
#define SOC_USB3OTG_PORTSC_OCA_START        (3)
#define SOC_USB3OTG_PORTSC_OCA_END          (3)
#define SOC_USB3OTG_PORTSC_PR_START         (4)
#define SOC_USB3OTG_PORTSC_PR_END           (4)
#define SOC_USB3OTG_PORTSC_PLS_START        (5)
#define SOC_USB3OTG_PORTSC_PLS_END          (8)
#define SOC_USB3OTG_PORTSC_PP_START         (9)
#define SOC_USB3OTG_PORTSC_PP_END           (9)
#define SOC_USB3OTG_PORTSC_PortSpeed_START  (10)
#define SOC_USB3OTG_PORTSC_PortSpeed_END    (13)
#define SOC_USB3OTG_PORTSC_PIC_START        (14)
#define SOC_USB3OTG_PORTSC_PIC_END          (15)
#define SOC_USB3OTG_PORTSC_LWS_START        (16)
#define SOC_USB3OTG_PORTSC_LWS_END          (16)
#define SOC_USB3OTG_PORTSC_CSC_START        (17)
#define SOC_USB3OTG_PORTSC_CSC_END          (17)
#define SOC_USB3OTG_PORTSC_PEC_START        (18)
#define SOC_USB3OTG_PORTSC_PEC_END          (18)
#define SOC_USB3OTG_PORTSC_WRC_START        (19)
#define SOC_USB3OTG_PORTSC_WRC_END          (19)
#define SOC_USB3OTG_PORTSC_OCC_START        (20)
#define SOC_USB3OTG_PORTSC_OCC_END          (20)
#define SOC_USB3OTG_PORTSC_PRC_START        (21)
#define SOC_USB3OTG_PORTSC_PRC_END          (21)
#define SOC_USB3OTG_PORTSC_PLC_START        (22)
#define SOC_USB3OTG_PORTSC_PLC_END          (22)
#define SOC_USB3OTG_PORTSC_CEC_START        (23)
#define SOC_USB3OTG_PORTSC_CEC_END          (23)
#define SOC_USB3OTG_PORTSC_CAS_START        (24)
#define SOC_USB3OTG_PORTSC_CAS_END          (24)
#define SOC_USB3OTG_PORTSC_WCE_START        (25)
#define SOC_USB3OTG_PORTSC_WCE_END          (25)
#define SOC_USB3OTG_PORTSC_WDE_START        (26)
#define SOC_USB3OTG_PORTSC_WDE_END          (26)
#define SOC_USB3OTG_PORTSC_WOE_START        (27)
#define SOC_USB3OTG_PORTSC_WOE_END          (27)
#define SOC_USB3OTG_PORTSC_DR_START         (30)
#define SOC_USB3OTG_PORTSC_DR_END           (30)
#define SOC_USB3OTG_PORTSC_WPR_START        (31)
#define SOC_USB3OTG_PORTSC_WPR_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_PORTPMSC_20_UNION
 �ṹ˵��  : PORTPMSC_20 �Ĵ����ṹ���塣��ַƫ����:0x0424����ֵ:0x00000000�����:32
 �Ĵ���˵��: �˿ڹ��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  L1S               : 3;  /* bit[0-2]  : L1 Status.����Ӵ˵�֪L1-based suspend�����Ƿ�ɹ���
                                                             0��Invalid��
                                                             1��Success��
                                                             2��Not Yet;
                                                             3��not supported;
                                                             4��timeout/Error;
                                                             5-7��reserved�� */
        unsigned int  RWE               : 1;  /* bit[3]    : Remote Wake Enable.���ʹ�ø�bitʹ��/��ʹ���豸��L1��Զ�̻��ѡ� */
        unsigned int  HIRD              : 4;  /* bit[4-7]  : Host Initiated Resume Duration.���ʹ�ø����֪�Խӵ��豸HOST��ú���resume�Ӷ��˳�L1״̬����ֵ0��Ӧ50us���������ֵÿ��1��ʱ������75us�����磺0001��Ӧ125us�� */
        unsigned int  L1_Device_Slot    : 8;  /* bit[8-15] : ������ø���ֵָʾ */
        unsigned int  HLE               : 1;  /* bit[16]   : Hardware LPM Enable.����bitΪ1ʱ��hardware controller LPM�ڸö˿�ʹ�ܡ���HLC=0,�������� */
        unsigned int  reserved          : 11; /* bit[17-27]: ���� */
        unsigned int  Port_Test_Control : 4;  /* bit[28-31]: ��0��ֵָʾPORT�������ģʽ��
                                                             0: Test mode not enable;
                                                             1: Test J_STATE;
                                                             2: Test K_STATE;
                                                             3: Test SE0_NAK;
                                                             4: Test Packet;
                                                             5: Test FORCE_ENABLE;
                                                             6-14: reserved;
                                                             15: Port Test control error. */
    } reg;
} SOC_USB3OTG_PORTPMSC_20_UNION;
#endif
#define SOC_USB3OTG_PORTPMSC_20_L1S_START                (0)
#define SOC_USB3OTG_PORTPMSC_20_L1S_END                  (2)
#define SOC_USB3OTG_PORTPMSC_20_RWE_START                (3)
#define SOC_USB3OTG_PORTPMSC_20_RWE_END                  (3)
#define SOC_USB3OTG_PORTPMSC_20_HIRD_START               (4)
#define SOC_USB3OTG_PORTPMSC_20_HIRD_END                 (7)
#define SOC_USB3OTG_PORTPMSC_20_L1_Device_Slot_START     (8)
#define SOC_USB3OTG_PORTPMSC_20_L1_Device_Slot_END       (15)
#define SOC_USB3OTG_PORTPMSC_20_HLE_START                (16)
#define SOC_USB3OTG_PORTPMSC_20_HLE_END                  (16)
#define SOC_USB3OTG_PORTPMSC_20_Port_Test_Control_START  (28)
#define SOC_USB3OTG_PORTPMSC_20_Port_Test_Control_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_PORTLI_UNION
 �ṹ˵��  : PORTLI �Ĵ����ṹ���塣��ַƫ����:0x0428����ֵ:0x00000000�����:32
 �Ĵ���˵��: Port Link Information�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  link_error_count : 16; /* bit[0-15] : ���ض˿ڼ�⵽��link error���� */
        unsigned int  reserved         : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_USB3OTG_PORTLI_UNION;
#endif
#define SOC_USB3OTG_PORTLI_link_error_count_START  (0)
#define SOC_USB3OTG_PORTLI_link_error_count_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_PORTHLPMC_20_UNION
 �ṹ˵��  : PORTHLPMC_20 �Ĵ����ṹ���塣��ַƫ����:0x042C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �˿�LPM���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HIRDM      : 2;  /* bit[0-1]  :  */
        unsigned int  L1_timeout : 8;  /* bit[2-9]  :  */
        unsigned int  HIRDD      : 4;  /* bit[10-13]:  */
        unsigned int  reserved   : 18; /* bit[14-31]:  */
    } reg;
} SOC_USB3OTG_PORTHLPMC_20_UNION;
#endif
#define SOC_USB3OTG_PORTHLPMC_20_HIRDM_START       (0)
#define SOC_USB3OTG_PORTHLPMC_20_HIRDM_END         (1)
#define SOC_USB3OTG_PORTHLPMC_20_L1_timeout_START  (2)
#define SOC_USB3OTG_PORTHLPMC_20_L1_timeout_END    (9)
#define SOC_USB3OTG_PORTHLPMC_20_HIRDD_START       (10)
#define SOC_USB3OTG_PORTHLPMC_20_HIRDD_END         (13)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_MFINDEX_UNION
 �ṹ˵��  : MFINDEX �Ĵ����ṹ���塣��ַƫ����:0x440����ֵ:0x00000000�����:32
 �Ĵ���˵��: MicroFrame Index�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  microframe_index : 14; /* bit[0-13] : ÿ��125us������ֵ��1. */
        unsigned int  reserved         : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_USB3OTG_MFINDEX_UNION;
#endif
#define SOC_USB3OTG_MFINDEX_microframe_index_START  (0)
#define SOC_USB3OTG_MFINDEX_microframe_index_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_IMAN_UNION
 �ṹ˵��  : IMAN �Ĵ����ṹ���塣��ַƫ����:0x460����ֵ:0x00000000�����:32
 �Ĵ���˵��: Interrupter Management�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  IP       : 1;  /* bit[0]   : Interrupt Pending.ָʾ��ǰ���ж���״̬��
                                                   0���ж������ж�����;
                                                   1: �ж���û���ж�����. */
        unsigned int  IE       : 1;  /* bit[1]   : Interrupt Enable.ָʾ�ж����Ƿ�ʹ�ܲ����жϡ�
                                                   0���ж�����ֹ�����жϣ�
                                                   1����IP=1������IMODCΪ0����ô�ͻ�����жϡ� */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_USB3OTG_IMAN_UNION;
#endif
#define SOC_USB3OTG_IMAN_IP_START        (0)
#define SOC_USB3OTG_IMAN_IP_END          (0)
#define SOC_USB3OTG_IMAN_IE_START        (1)
#define SOC_USB3OTG_IMAN_IE_END          (1)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_IMOD_UNION
 �ṹ˵��  : IMOD �Ĵ����ṹ���塣��ַƫ����:0x464����ֵ:0x00000FA0�����:32
 �Ĵ���˵��: Interrupt Moderation�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  IMODI : 16; /* bit[0-15] : interrupt moderation interval.�ڲ��жϵ���С�������250nsΪ������ӡ�������ֵΪ0�������ж���������ʱ�����������жϡ� */
        unsigned int  IMODC : 16; /* bit[16-31]: Interrupt Moderation Counter.��IP=0������IMODI��ֵ�����¼���0��ֹͣ�� */
    } reg;
} SOC_USB3OTG_IMOD_UNION;
#endif
#define SOC_USB3OTG_IMOD_IMODI_START  (0)
#define SOC_USB3OTG_IMOD_IMODI_END    (15)
#define SOC_USB3OTG_IMOD_IMODC_START  (16)
#define SOC_USB3OTG_IMOD_IMODC_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_ERSTSZ_UNION
 �ṹ˵��  : ERSTSZ �Ĵ����ṹ���塣��ַƫ����:0x468����ֵ:0x00000000�����:32
 �Ĵ���˵��: Event Ring Segment Table Size�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_ring_segment_table_size : 16; /* bit[0-15] : ����ָʾ��Ч��Event Ring Segment Table entry����������Table�Ļ���ַ��Event Ring Segment Table Base Address�Ĵ���ָ��������ֵ�����ֵ��HCSPARAMS2��ERST_max������
                                                                         ���ڶ����ж�����������ֵΪ0ʱ��Event Ring�رա�����ԭʼ�ж�����������ֵΪ0ʱ������Event Ring�Ĳ���Ԥ֪��Ϊ�� */
        unsigned int  reserved                      : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_USB3OTG_ERSTSZ_UNION;
#endif
#define SOC_USB3OTG_ERSTSZ_event_ring_segment_table_size_START  (0)
#define SOC_USB3OTG_ERSTSZ_event_ring_segment_table_size_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_ERSTBA_L_UNION
 �ṹ˵��  : ERSTBA_L �Ĵ����ṹ���塣��ַƫ����:0x470����ֵ:0x00000000�����:32
 �Ĵ���˵��: Event Ring Segment Table����ַ��λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                              : 6;  /* bit[0-5] : ���� */
        unsigned int  event_ring_segment_table_base_address : 26; /* bit[6-31]: ��ERSTBA_Hһ��ָʾEvent Ring Segment Table����ַ����HCH=0ʱ�����ܶԸ�������޸ġ� */
    } reg;
} SOC_USB3OTG_ERSTBA_L_UNION;
#endif
#define SOC_USB3OTG_ERSTBA_L_event_ring_segment_table_base_address_START  (6)
#define SOC_USB3OTG_ERSTBA_L_event_ring_segment_table_base_address_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_ERSTBA_H_UNION
 �ṹ˵��  : ERSTBA_H �Ĵ����ṹ���塣��ַƫ����:0x474����ֵ:0x00000000�����:32
 �Ĵ���˵��: Event Ring Segment Table����ַ��λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_ring_segment_table_base_address : 32; /* bit[0-31]: ��ERSTBA_L[31��6]һ��ָʾEvent Ring Segment Table����ַ����HCH=0ʱ�����ܶԸ�������޸ġ� */
    } reg;
} SOC_USB3OTG_ERSTBA_H_UNION;
#endif
#define SOC_USB3OTG_ERSTBA_H_event_ring_segment_table_base_address_START  (0)
#define SOC_USB3OTG_ERSTBA_H_event_ring_segment_table_base_address_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_ERDP_L_UNION
 �ṹ˵��  : ERDP_L �Ĵ����ṹ���塣��ַƫ����:0x478����ֵ:0x00000000�����:32
 �Ĵ���˵��: Event Ring Dequeue Pointer��λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DESI                       : 3;  /* bit[0-2] : Dequeue ERST Segment Index.xHCʹ�ø������ӿ�ȷ��Event Ring full������ */
        unsigned int  EHB                        : 1;  /* bit[3]   : Event Handler Busy.��IP=1ʱ��bit��1�����ҵ�event_ring_dequeue_pointer��ֵ�������Ҫ����bit��0. */
        unsigned int  event_ring_dequeue_pointer : 28; /* bit[4-31]: ��ERDP_Hһ��ָ��dequeue pointer�Ļ���ַ�� */
    } reg;
} SOC_USB3OTG_ERDP_L_UNION;
#endif
#define SOC_USB3OTG_ERDP_L_DESI_START                        (0)
#define SOC_USB3OTG_ERDP_L_DESI_END                          (2)
#define SOC_USB3OTG_ERDP_L_EHB_START                         (3)
#define SOC_USB3OTG_ERDP_L_EHB_END                           (3)
#define SOC_USB3OTG_ERDP_L_event_ring_dequeue_pointer_START  (4)
#define SOC_USB3OTG_ERDP_L_event_ring_dequeue_pointer_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_ERDP_H_UNION
 �ṹ˵��  : ERDP_H �Ĵ����ṹ���塣��ַƫ����:0x47C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Event Ring Dequeue Pointer��λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_ring_dequeue_pointer : 32; /* bit[0-31]: ��ERDP_L[31��4]һ��ָ��dequeue pointer�Ļ���ַ�� */
    } reg;
} SOC_USB3OTG_ERDP_H_UNION;
#endif
#define SOC_USB3OTG_ERDP_H_event_ring_dequeue_pointer_START  (0)
#define SOC_USB3OTG_ERDP_H_event_ring_dequeue_pointer_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DB_UNION
 �ṹ˵��  : DB �Ĵ����ṹ���塣��ַƫ����:0x480����ֵ:0x00000000�����:32
 �Ĵ���˵��: Doorbell�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DB_tagger    : 8;  /* bit[0-7]  : ��ʾdoorbellָ����Ŀ�ꡣ��ֵ0ר������Command Ring��
                                                        Device Context Doorbells(1-255):
                                                        0:reserved;
                                                        1:control EP0 enqueue pointer update
                                                        2:EP1 OUT enqueue pointer update;
                                                        3:EP1 IN enqueue pointer update;
                                                        ��
                                                        30:EP15 OUT enqueue pointer update;
                                                        31:EP15 IN enqueue pointer update;
                                                        32-247:reserved;
                                                        248-255:Vendor Defined.
                                                        Host Controller Doorbell:
                                                        0:command doorbell;
                                                        1-247:reserved;
                                                        248-255:Vendor defined.
                                                        ���������ֵʱ����0. */
        unsigned int  reserved     : 8;  /* bit[8-15] : ���� */
        unsigned int  DB_Stream_ID : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_USB3OTG_DB_UNION;
#endif
#define SOC_USB3OTG_DB_DB_tagger_START     (0)
#define SOC_USB3OTG_DB_DB_tagger_END       (7)
#define SOC_USB3OTG_DB_DB_Stream_ID_START  (16)
#define SOC_USB3OTG_DB_DB_Stream_ID_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_USBLEGSUP_UNION
 �ṹ˵��  : USBLEGSUP �Ĵ����ṹ���塣��ַƫ����:0x8A0����ֵ:0x00000401�����:32
 �Ĵ���˵��: USB Legacy Support Capability�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  capability_ID           : 8;  /* bit[0-7]  : ʶ����չ��ʲô���� */
        unsigned int  next_capability_pointer : 8;  /* bit[8-15] : ָʾ�¸����ܵĻ���ַ. */
        unsigned int  HC_BIOS_owned_semaphore : 1;  /* bit[16]   : BIOS���ø���ֵ�Խ���xHC��ownership */
        unsigned int  reserved_0              : 7;  /* bit[17-23]: ���� */
        unsigned int  HC_OS_owned_semaphore   : 1;  /* bit[24]   : ϵͳ������ø�bit��������xHC��ownership. */
        unsigned int  reserved_1              : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_USB3OTG_USBLEGSUP_UNION;
#endif
#define SOC_USB3OTG_USBLEGSUP_capability_ID_START            (0)
#define SOC_USB3OTG_USBLEGSUP_capability_ID_END              (7)
#define SOC_USB3OTG_USBLEGSUP_next_capability_pointer_START  (8)
#define SOC_USB3OTG_USBLEGSUP_next_capability_pointer_END    (15)
#define SOC_USB3OTG_USBLEGSUP_HC_BIOS_owned_semaphore_START  (16)
#define SOC_USB3OTG_USBLEGSUP_HC_BIOS_owned_semaphore_END    (16)
#define SOC_USB3OTG_USBLEGSUP_HC_OS_owned_semaphore_START    (24)
#define SOC_USB3OTG_USBLEGSUP_HC_OS_owned_semaphore_END      (24)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_USBLEGCTLSTS_UNION
 �ṹ˵��  : USBLEGCTLSTS �Ĵ����ṹ���塣��ַƫ����:0x8A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: USB legavy support control/status�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  USB_SMI_enable                  : 1;  /* bit[0]    : ����bitΪ1����SMI on event interruptλҲΪ1����ô��������������SMI */
        unsigned int  reserved_0                      : 3;  /* bit[1-3]  : ���� */
        unsigned int  SMI_on_host_system_error_enable : 1;  /* bit[4]    : ����bitΪ1����SMI on host system errorλҲΪ1����ô��������������SMI */
        unsigned int  reserved_1                      : 8;  /* bit[5-12] : ���� */
        unsigned int  SMI_on_OS_ownership_enable      : 1;  /* bit[13]   : ����bitΪ1����OS owenership changeλҲΪ1����ô��������������SMI */
        unsigned int  SMI_on_PCI_command_enable       : 1;  /* bit[14]   : ����bitΪ1����SMI on PCI cammandλҲΪ1����ô��������������SMI */
        unsigned int  SMI_on_BAR_enable               : 1;  /* bit[15]   : ����bitΪ1����BARҲΪ1����ô��������������SMI */
        unsigned int  SMI_on_event_interrupt          : 1;  /* bit[16]   : ��bit��EINTһ�� */
        unsigned int  reserved_2                      : 3;  /* bit[17-19]: ���� */
        unsigned int  SMI_on_host_system_error        : 1;  /* bit[20]   : ��bit��HSEһ�� */
        unsigned int  reserved_3                      : 8;  /* bit[21-28]: ���� */
        unsigned int  SMI_on_OS_ownership_change      : 1;  /* bit[29]   : ��ӳUSBLEGSUP�Ĵ���HC OS owned semaphore��ı仯 */
        unsigned int  SMI_on_PCI_command              : 1;  /* bit[30]   : ��PCI command�Ĵ�����д��ʱ����bitΪ1 */
        unsigned int  SMI_on_BAR                      : 1;  /* bit[31]   : ��BAR�Ĵ�����д��ʱ����bitΪ1 */
    } reg;
} SOC_USB3OTG_USBLEGCTLSTS_UNION;
#endif
#define SOC_USB3OTG_USBLEGCTLSTS_USB_SMI_enable_START                   (0)
#define SOC_USB3OTG_USBLEGCTLSTS_USB_SMI_enable_END                     (0)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_host_system_error_enable_START  (4)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_host_system_error_enable_END    (4)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_OS_ownership_enable_START       (13)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_OS_ownership_enable_END         (13)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_PCI_command_enable_START        (14)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_PCI_command_enable_END          (14)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_BAR_enable_START                (15)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_BAR_enable_END                  (15)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_event_interrupt_START           (16)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_event_interrupt_END             (16)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_host_system_error_START         (20)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_host_system_error_END           (20)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_OS_ownership_change_START       (29)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_OS_ownership_change_END         (29)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_PCI_command_START               (30)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_PCI_command_END                 (30)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_BAR_START                       (31)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_BAR_END                         (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GSBUSCFG0_UNION
 �ṹ˵��  : GSBUSCFG0 �Ĵ����ṹ���塣��ַƫ����:0xC100����ֵ:0x0000000E�����:32
 �Ĵ���˵��: SOC�������üĴ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INCRBrstEna    : 1;  /* bit[0]    : ������burstʹ�ܡ�ע�⣺��bit��������Ϊ0��
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  INCR4BrstEna   : 1;  /* bit[1]    : INCR4ʹ�ܡ�
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  INCR8BrstEna   : 1;  /* bit[2]    : INCR8ʹ�ܡ�
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  INCR16BrstEna  : 1;  /* bit[3]    : INCR16ʹ�ܡ�
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  INCR32BrstEna  : 1;  /* bit[4]    : INCR32ʹ�ܡ�ע�⣺��bit��������Ϊ0��
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  INCR64BrstEna  : 1;  /* bit[5]    : INCR64ʹ�ܡ�ע�⣺��bit��������Ϊ0��
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  INCR128BrstEna : 1;  /* bit[6]    : INCR128ʹ�ܡ�ע�⣺��bit��������Ϊ0��
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  INCR256BrstEna : 1;  /* bit[7]    : INCR256ʹ�ܡ�ע�⣺��bit��������Ϊ0��
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  reserved_0     : 2;  /* bit[8-9]  : ������ */
        unsigned int  DescBigEnd     : 1;  /* bit[10]   : ��������С�����á�
                                                          0��С�ˣ�
                                                          1����ˡ� */
        unsigned int  DatBigEnd      : 1;  /* bit[11]   : ���ݴ�С�����á�
                                                          0��С�ˣ�
                                                          1����ˡ� */
        unsigned int  reserved_1     : 4;  /* bit[12-15]: ������ */
        unsigned int  DesWrReqInfo   : 4;  /* bit[16-19]: д����������AXI-cache���á� */
        unsigned int  DatWrReqInfo   : 4;  /* bit[20-23]: д���ݲ���AXI-cache���á� */
        unsigned int  DesRdReqInfo   : 4;  /* bit[24-27]: ������������AXI-cache���á� */
        unsigned int  DatRdReqInfo   : 4;  /* bit[28-31]: �����ݲ���AXI-cache���á� */
    } reg;
} SOC_USB3OTG_GSBUSCFG0_UNION;
#endif
#define SOC_USB3OTG_GSBUSCFG0_INCRBrstEna_START     (0)
#define SOC_USB3OTG_GSBUSCFG0_INCRBrstEna_END       (0)
#define SOC_USB3OTG_GSBUSCFG0_INCR4BrstEna_START    (1)
#define SOC_USB3OTG_GSBUSCFG0_INCR4BrstEna_END      (1)
#define SOC_USB3OTG_GSBUSCFG0_INCR8BrstEna_START    (2)
#define SOC_USB3OTG_GSBUSCFG0_INCR8BrstEna_END      (2)
#define SOC_USB3OTG_GSBUSCFG0_INCR16BrstEna_START   (3)
#define SOC_USB3OTG_GSBUSCFG0_INCR16BrstEna_END     (3)
#define SOC_USB3OTG_GSBUSCFG0_INCR32BrstEna_START   (4)
#define SOC_USB3OTG_GSBUSCFG0_INCR32BrstEna_END     (4)
#define SOC_USB3OTG_GSBUSCFG0_INCR64BrstEna_START   (5)
#define SOC_USB3OTG_GSBUSCFG0_INCR64BrstEna_END     (5)
#define SOC_USB3OTG_GSBUSCFG0_INCR128BrstEna_START  (6)
#define SOC_USB3OTG_GSBUSCFG0_INCR128BrstEna_END    (6)
#define SOC_USB3OTG_GSBUSCFG0_INCR256BrstEna_START  (7)
#define SOC_USB3OTG_GSBUSCFG0_INCR256BrstEna_END    (7)
#define SOC_USB3OTG_GSBUSCFG0_DescBigEnd_START      (10)
#define SOC_USB3OTG_GSBUSCFG0_DescBigEnd_END        (10)
#define SOC_USB3OTG_GSBUSCFG0_DatBigEnd_START       (11)
#define SOC_USB3OTG_GSBUSCFG0_DatBigEnd_END         (11)
#define SOC_USB3OTG_GSBUSCFG0_DesWrReqInfo_START    (16)
#define SOC_USB3OTG_GSBUSCFG0_DesWrReqInfo_END      (19)
#define SOC_USB3OTG_GSBUSCFG0_DatWrReqInfo_START    (20)
#define SOC_USB3OTG_GSBUSCFG0_DatWrReqInfo_END      (23)
#define SOC_USB3OTG_GSBUSCFG0_DesRdReqInfo_START    (24)
#define SOC_USB3OTG_GSBUSCFG0_DesRdReqInfo_END      (27)
#define SOC_USB3OTG_GSBUSCFG0_DatRdReqInfo_START    (28)
#define SOC_USB3OTG_GSBUSCFG0_DatRdReqInfo_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GSBUSCFG1_UNION
 �ṹ˵��  : GSBUSCFG1 �Ĵ����ṹ���塣��ַƫ����:0xC104����ֵ:0x00000300�����:32
 �Ĵ���˵��: SOC�������üĴ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0     : 8;  /* bit[0-7]  : ������ */
        unsigned int  PipeTransLimit : 4;  /* bit[8-11] : AXI����outstanding������á�
                                                          4'h0�����Ϊ1��
                                                          4'h1�����Ϊ2��
                                                          ����
                                                          4'hF�����Ϊ16�� */
        unsigned int  EN1KPAGE       : 1;  /* bit[12]   : 1Kҳ��߽�ʹ�ܡ�
                                                          Ĭ��AXI����߽�Ϊ4KB�������λʹ�ܣ���AXI����߽�Ϊ1KB��burst�����ַ���ܿ�1K�߽硣
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  reserved_1     : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_USB3OTG_GSBUSCFG1_UNION;
#endif
#define SOC_USB3OTG_GSBUSCFG1_PipeTransLimit_START  (8)
#define SOC_USB3OTG_GSBUSCFG1_PipeTransLimit_END    (11)
#define SOC_USB3OTG_GSBUSCFG1_EN1KPAGE_START        (12)
#define SOC_USB3OTG_GSBUSCFG1_EN1KPAGE_END          (12)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GTXTHRCFG_UNION
 �ṹ˵��  : GTXTHRCFG �Ĵ����ṹ���塣��ַƫ����:0xC108����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ˮ�߿��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 16; /* bit[0-15] : ������ */
        unsigned int  USBMaxTxBurstSize : 8;  /* bit[16-23]: �����burst���ȡ� */
        unsigned int  USBTxPktCnt       : 4;  /* bit[24-27]: USB���Ͱ�����������USBTxPktCntSelΪ1ʱ��Ч�� */
        unsigned int  reserved_1        : 1;  /* bit[28]   : ������ */
        unsigned int  USBTxPktCntSel    : 1;  /* bit[29]   : �������ˮ��ģʽʹ�ܡ�
                                                             �����bit��ʹ�ܣ�����FIFO�����������ݿ�ʼUSB���ߴ��䡣
                                                             �����bitʹ�ܣ�����FIFO��Ԥȡ��USBTxPktCnt�����ݰ�֮��ʼUSB���䡣
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  reserved_2        : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_USB3OTG_GTXTHRCFG_UNION;
#endif
#define SOC_USB3OTG_GTXTHRCFG_USBMaxTxBurstSize_START  (16)
#define SOC_USB3OTG_GTXTHRCFG_USBMaxTxBurstSize_END    (23)
#define SOC_USB3OTG_GTXTHRCFG_USBTxPktCnt_START        (24)
#define SOC_USB3OTG_GTXTHRCFG_USBTxPktCnt_END          (27)
#define SOC_USB3OTG_GTXTHRCFG_USBTxPktCntSel_START     (29)
#define SOC_USB3OTG_GTXTHRCFG_USBTxPktCntSel_END       (29)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GRXTHRCFG_UNION
 �ṹ˵��  : GRXTHRCFG �Ĵ����ṹ���塣��ַƫ����:0xC10C����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ˮ�߿��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 19; /* bit[0-18] : ������ */
        unsigned int  USBMaxRxBurstSize : 5;  /* bit[19-23]: ������burst���ȡ� */
        unsigned int  USBRxPktCnt       : 4;  /* bit[24-27]: USB���հ�����������USBRxPktCntSel��1ʱ��Ч�� */
        unsigned int  reserved_1        : 1;  /* bit[28]   : ������ */
        unsigned int  USBRxPktCntSel    : 1;  /* bit[29]   : �������ˮ��ģʽʹ�ܡ�
                                                             �����bit��ʹ�ܣ�����FIFO����1�����ݰ��Ŀռ俪ʼ����USB���ݡ�
                                                             �����bitʹ�ܣ������FIFO����USBRxPktCnt�����ݰ��ռ�֮��ʼ����USB���ݡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  reserved_2        : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_USB3OTG_GRXTHRCFG_UNION;
#endif
#define SOC_USB3OTG_GRXTHRCFG_USBMaxRxBurstSize_START  (19)
#define SOC_USB3OTG_GRXTHRCFG_USBMaxRxBurstSize_END    (23)
#define SOC_USB3OTG_GRXTHRCFG_USBRxPktCnt_START        (24)
#define SOC_USB3OTG_GRXTHRCFG_USBRxPktCnt_END          (27)
#define SOC_USB3OTG_GRXTHRCFG_USBRxPktCntSel_START     (29)
#define SOC_USB3OTG_GRXTHRCFG_USBRxPktCntSel_END       (29)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GCTL_UNION
 �ṹ˵��  : GCTL �Ĵ����ṹ���塣��ַƫ����:0xC110����ֵ:0x00193000�����:32
 �Ĵ���˵��: ȫ�ֿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DsblClkGtng       : 1;  /* bit[0]    : Disableʱ��gating�� */
        unsigned int  GblHibernationEn  : 1;  /* bit[1]    : Hibernationʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  U2EXIT_LFPS       : 1;  /* bit[2]    : U2�˳�LFPS���á�
                                                             0��248ns��LFPS�ź���Ϊ��Ч�˳��źţ�
                                                             1�����U2�˳�֮ǰ�ȴ�8us�� */
        unsigned int  DisScramble       : 1;  /* bit[3]    : ��֯ȥʹ�ܡ� */
        unsigned int  ScaleDown         : 2;  /* bit[4-5]  : ScaleDownģʽ�������ڷ��档 */
        unsigned int  RAMClkSel         : 2;  /* bit[6-7]  : RAMʱ��ѡ��
                                                             00������ʱ�ӣ�
                                                             01��PIPE�ӿ�ʱ�ӣ�
                                                             10��PIPE�ӿ�2��Ƶʱ�ӡ�
                                                             11�������� */
        unsigned int  DebugAttach       : 1;  /* bit[8]    : Attach����ʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  DisU1U2TimerScale : 1;  /* bit[9]    : U1U2 timer scaledown����ȥʹ�ܡ�
                                                             ����ScaleDown����Ϊ2'bx1ʱ��Ч�� */
        unsigned int  SOFTITPSYNC       : 1;  /* bit[10]   : ��ITP����ʹ�ܡ�
                                                             ��Ϊhostʱ�����ʹ�ܸù��ܣ��������ʹ��ref_clk��Ϊ�ڲ�ITP������ʱ�ӡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  CoreSoftReset     : 1;  /* bit[11]   : ��������λ���ơ�
                                                             0������λ��
                                                             1����λ�� */
        unsigned int  PrtCapDir         : 2;  /* bit[12-13]: �˿����á�
                                                             01��Host��
                                                             10��Device��
                                                             11��OTG�� */
        unsigned int  FrmSclDwn         : 2;  /* bit[14-15]: ֡����������á���������SOF/uSOF/ITP�������̡�
                                                             ����SS/HSģʽ��
                                                             2'h3��֡�������Ϊ15.625us��
                                                             2'h2��֡�������Ϊ31.25us��
                                                             2'h1��֡�������Ϊ62.5us��
                                                             2'h0��֡���Ϊ125us�� */
        unsigned int  U2RSTECN          : 1;  /* bit[16]   : ���POLL����LMP���������У�SS����ʧ�ܣ�device����Ϊ��SS�豸���ӡ�
                                                             �����λ����Ϊ1��device��SS����ʧ��֮�󣬻��᳢��3��SS���ӡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  BypassSetAddr     : 1;  /* bit[17]   : SetAddress��·ʹ�ܡ���λʹ�ܣ���deviceʹ��DCFG[DevAddr]��Ϊ��ַ������SetAddress���䡣�ù���ֻ�����ڷ��档
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  MasterFiltBypass  : 1;  /* bit[18]   : Filter��·��·ʹ�ܡ���λ����Ϊ1���������ź�utmiotg_iddig��utmiotg_vbusvalid��utmiotg_bvalid��utmisrp_sessend��pipe3_PowerPresent��Filter��·����·��
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  GPwrDnScale       : 13; /* bit[19-31]: �͹���ʱ�ӷ�Ƶϵ����ָ��suspend_clk��ƵΪ16KHz�ķ�Ƶϵ���� */
    } reg;
} SOC_USB3OTG_GCTL_UNION;
#endif
#define SOC_USB3OTG_GCTL_DsblClkGtng_START        (0)
#define SOC_USB3OTG_GCTL_DsblClkGtng_END          (0)
#define SOC_USB3OTG_GCTL_GblHibernationEn_START   (1)
#define SOC_USB3OTG_GCTL_GblHibernationEn_END     (1)
#define SOC_USB3OTG_GCTL_U2EXIT_LFPS_START        (2)
#define SOC_USB3OTG_GCTL_U2EXIT_LFPS_END          (2)
#define SOC_USB3OTG_GCTL_DisScramble_START        (3)
#define SOC_USB3OTG_GCTL_DisScramble_END          (3)
#define SOC_USB3OTG_GCTL_ScaleDown_START          (4)
#define SOC_USB3OTG_GCTL_ScaleDown_END            (5)
#define SOC_USB3OTG_GCTL_RAMClkSel_START          (6)
#define SOC_USB3OTG_GCTL_RAMClkSel_END            (7)
#define SOC_USB3OTG_GCTL_DebugAttach_START        (8)
#define SOC_USB3OTG_GCTL_DebugAttach_END          (8)
#define SOC_USB3OTG_GCTL_DisU1U2TimerScale_START  (9)
#define SOC_USB3OTG_GCTL_DisU1U2TimerScale_END    (9)
#define SOC_USB3OTG_GCTL_SOFTITPSYNC_START        (10)
#define SOC_USB3OTG_GCTL_SOFTITPSYNC_END          (10)
#define SOC_USB3OTG_GCTL_CoreSoftReset_START      (11)
#define SOC_USB3OTG_GCTL_CoreSoftReset_END        (11)
#define SOC_USB3OTG_GCTL_PrtCapDir_START          (12)
#define SOC_USB3OTG_GCTL_PrtCapDir_END            (13)
#define SOC_USB3OTG_GCTL_FrmSclDwn_START          (14)
#define SOC_USB3OTG_GCTL_FrmSclDwn_END            (15)
#define SOC_USB3OTG_GCTL_U2RSTECN_START           (16)
#define SOC_USB3OTG_GCTL_U2RSTECN_END             (16)
#define SOC_USB3OTG_GCTL_BypassSetAddr_START      (17)
#define SOC_USB3OTG_GCTL_BypassSetAddr_END        (17)
#define SOC_USB3OTG_GCTL_MasterFiltBypass_START   (18)
#define SOC_USB3OTG_GCTL_MasterFiltBypass_END     (18)
#define SOC_USB3OTG_GCTL_GPwrDnScale_START        (19)
#define SOC_USB3OTG_GCTL_GPwrDnScale_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GPMSTS_UNION
 �ṹ˵��  : GPMSTS �Ĵ����ṹ���塣��ַƫ����:0xC114����ֵ:0x0000�����:32
 �Ĵ���˵��: ȫ�ֵ�Դ����״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  U2Wakeup : 10; /* bit[0-9]  : USB2.0�˿ڻ���������
                                                    Bit[0]����⵽������
                                                    Bit[1]����⵽resume��
                                                    Bit[2]����⵽���ӣ�
                                                    Bit[3]����⵽�Ͽ����ӣ�
                                                    Bit[4]���ϴ�����״̬��
                                                    Bit[5]��ID״̬�仯��
                                                    Bit[6]����⵽SRP����
                                                    Bit[7]��������
                                                    Bit[8]����⵽��λ��
                                                    Bit[9]����⵽resume״̬�仯�� */
        unsigned int  reserved_0: 2;  /* bit[10-11]: ������ */
        unsigned int  U3Wakeup : 5;  /* bit[12-16]: USB3.0�˿ڻ���������
                                                    Bit[12]����⵽������
                                                    bit[13]����⵽Resume��
                                                    bit[14]����⵽���ӣ�
                                                    bit[15]����⵽�Ͽ����ӣ�
                                                    bit[16]���ϴ�����״̬�� */
        unsigned int  reserved_1: 11; /* bit[17-27]: ������ */
        unsigned int  PortSel  : 4;  /* bit[28-31]: �˿�ѡ�� */
    } reg;
} SOC_USB3OTG_GPMSTS_UNION;
#endif
#define SOC_USB3OTG_GPMSTS_U2Wakeup_START  (0)
#define SOC_USB3OTG_GPMSTS_U2Wakeup_END    (9)
#define SOC_USB3OTG_GPMSTS_U3Wakeup_START  (12)
#define SOC_USB3OTG_GPMSTS_U3Wakeup_END    (16)
#define SOC_USB3OTG_GPMSTS_PortSel_START   (28)
#define SOC_USB3OTG_GPMSTS_PortSel_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GSTS_UNION
 �ṹ˵��  : GSTS �Ĵ����ṹ���塣��ַƫ����:0xC118����ֵ:0x0000�����:32
 �Ĵ���˵��: ȫ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 4;  /* bit[0-3]  : ������ */
        unsigned int  BusErrAddrVld : 1;  /* bit[4]    : ���ߴ��� */
        unsigned int  CSRTimeout    : 1;  /* bit[5]    : �Ĵ������ʳ�ʱ��д1����� */
        unsigned int  Device_IP     : 1;  /* bit[6]    : Device�ж���Ч�� */
        unsigned int  Host_IP       : 1;  /* bit[7]    : Host�ж���Ч�� */
        unsigned int  ADP_IP        : 1;  /* bit[8]    : ADP�жϴ����� */
        unsigned int  BC_IP         : 1;  /* bit[9]    : BC�жϴ����� */
        unsigned int  OTG_IP        : 1;  /* bit[10]   : ��OTG�жϴ����� */
        unsigned int  reserved_1    : 9;  /* bit[11-19]: ������ */
        unsigned int  CBELT         : 12; /* bit[20-31]: ��ǰBELT(Best Effort Latency Tolerance Value)�� */
    } reg;
} SOC_USB3OTG_GSTS_UNION;
#endif
#define SOC_USB3OTG_GSTS_BusErrAddrVld_START  (4)
#define SOC_USB3OTG_GSTS_BusErrAddrVld_END    (4)
#define SOC_USB3OTG_GSTS_CSRTimeout_START     (5)
#define SOC_USB3OTG_GSTS_CSRTimeout_END       (5)
#define SOC_USB3OTG_GSTS_Device_IP_START      (6)
#define SOC_USB3OTG_GSTS_Device_IP_END        (6)
#define SOC_USB3OTG_GSTS_Host_IP_START        (7)
#define SOC_USB3OTG_GSTS_Host_IP_END          (7)
#define SOC_USB3OTG_GSTS_ADP_IP_START         (8)
#define SOC_USB3OTG_GSTS_ADP_IP_END           (8)
#define SOC_USB3OTG_GSTS_BC_IP_START          (9)
#define SOC_USB3OTG_GSTS_BC_IP_END            (9)
#define SOC_USB3OTG_GSTS_OTG_IP_START         (10)
#define SOC_USB3OTG_GSTS_OTG_IP_END           (10)
#define SOC_USB3OTG_GSTS_CBELT_START          (20)
#define SOC_USB3OTG_GSTS_CBELT_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GUCTL1_UNION
 �ṹ˵��  : GUCTL1 �Ĵ����ṹ���塣��ַƫ����:0xC11C����ֵ:0x0002�����:32
 �Ĵ���˵��: �û����ƼĴ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  LOA_FILTER_EN : 1;  /* bit[0]   : LOA(Loss of Activity)�˲�ʹ�ܡ�ʹ�ܸù��ܣ�������3��������⵽LOA�Ż�ȥʹ�ܶ˿ڡ������ý���Host��Ч��
                                                        0����ʹ�ܣ�
                                                        1��ʹ�ܡ� */
        unsigned int  reserved      : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_USB3OTG_GUCTL1_UNION;
#endif
#define SOC_USB3OTG_GUCTL1_LOA_FILTER_EN_START  (0)
#define SOC_USB3OTG_GUCTL1_LOA_FILTER_EN_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GSNPSID_UNION
 �ṹ˵��  : GSNPSID �Ĵ����ṹ���塣��ַƫ����:0xC120����ֵ:0x5533290A�����:32
 �Ĵ���˵��: �������汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SynopsysID : 32; /* bit[0-31]: �������汾ID�� */
    } reg;
} SOC_USB3OTG_GSNPSID_UNION;
#endif
#define SOC_USB3OTG_GSNPSID_SynopsysID_START  (0)
#define SOC_USB3OTG_GSNPSID_SynopsysID_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GUCTL_UNION
 �ṹ˵��  : GUCTL �Ĵ����ṹ���塣��ַƫ����:0xC12C����ֵ:0x02008010�����:32
 �Ĵ���˵��: �û����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DTFT                : 9;  /* bit[0-8]  : Device��ʱ΢������ʱʱ��Ϊ��DTFT*256*8ns�� */
        unsigned int  DTCT                : 2;  /* bit[9-10] : Device��ʱ�ֵ��ڡ�
                                                               00: ��DTFTֵ���棻
                                                               01: 500us��
                                                               10: 1.5ms��
                                                               11: 6.5ms�� */
        unsigned int  CSR                 : 1;  /* bit[11]   : ��FS Bulk OUT����֮�䣬���������ӳ١�
                                                               0����ʹ�ܣ�
                                                               1��host��������bulk OUT����֮�����12us�ӳ١� */
        unsigned int  ExtCapSuptEN        : 1;  /* bit[12]   : ֧���ⲿ��չxHCI Capability�Ĵ�����
                                                               0����ʹ�ܣ�
                                                               1��ʹ�ܡ� */
        unsigned int  EnOverlapChk        : 1;  /* bit[13]   : Զ��Ux״̬�˳������У�ʹ��LFPS�ص���⡣
                                                               0����ʹ�ܣ�
                                                               1��ʹ�ܡ� */
        unsigned int  USBHstInAutoRetryEn : 1;  /* bit[14]   : Host IN�����Զ�����ʹ�ܡ�
                                                               0����ʹ�ܣ�
                                                               1��ʹ�ܡ� */
        unsigned int  CMDevAddr           : 1;  /* bit[15]   : device��ַ����ģʽ��
                                                               0��device��ַ����slot ID��
                                                               1���յ�AddressDevice�����device��ַ������
                                                               ��bit��������Ϊ1��0������debug�� */
        unsigned int  ResBwHSEPS          : 1;  /* bit[16]   : ����HS���ڴ��䣬��������85������Ĭ����������80������ */
        unsigned int  SprsCtrlTransEn     : 1;  /* bit[17]   : ϡ���������ʹ�ܡ�
                                                               ��λʹ�ܣ�host������������һ��΢֡�ڴ������������� */
        unsigned int  PSQExtrResSp        : 3;  /* bit[18-20]: PSQ(Protocol Status Queue)����ı����ռ䡣Debug���ܣ�����ģʽ����Ҫʹ�á� */
        unsigned int  NoExtrDl            : 1;  /* bit[21]   : SOF�͵�һ����֮�����ʱ���ơ�
                                                               0��Host�ڷ���SOF֮��ȴ�2us֮���͵�һ������
                                                               1��host�ڷ���SOF֮���������͵�һ������ */
        unsigned int  REFCLKPER           : 10; /* bit[22-31]: ����ʱ���ź�ref_clk�������ã���nsΪ��λ�� */
    } reg;
} SOC_USB3OTG_GUCTL_UNION;
#endif
#define SOC_USB3OTG_GUCTL_DTFT_START                 (0)
#define SOC_USB3OTG_GUCTL_DTFT_END                   (8)
#define SOC_USB3OTG_GUCTL_DTCT_START                 (9)
#define SOC_USB3OTG_GUCTL_DTCT_END                   (10)
#define SOC_USB3OTG_GUCTL_CSR_START                  (11)
#define SOC_USB3OTG_GUCTL_CSR_END                    (11)
#define SOC_USB3OTG_GUCTL_ExtCapSuptEN_START         (12)
#define SOC_USB3OTG_GUCTL_ExtCapSuptEN_END           (12)
#define SOC_USB3OTG_GUCTL_EnOverlapChk_START         (13)
#define SOC_USB3OTG_GUCTL_EnOverlapChk_END           (13)
#define SOC_USB3OTG_GUCTL_USBHstInAutoRetryEn_START  (14)
#define SOC_USB3OTG_GUCTL_USBHstInAutoRetryEn_END    (14)
#define SOC_USB3OTG_GUCTL_CMDevAddr_START            (15)
#define SOC_USB3OTG_GUCTL_CMDevAddr_END              (15)
#define SOC_USB3OTG_GUCTL_ResBwHSEPS_START           (16)
#define SOC_USB3OTG_GUCTL_ResBwHSEPS_END             (16)
#define SOC_USB3OTG_GUCTL_SprsCtrlTransEn_START      (17)
#define SOC_USB3OTG_GUCTL_SprsCtrlTransEn_END        (17)
#define SOC_USB3OTG_GUCTL_PSQExtrResSp_START         (18)
#define SOC_USB3OTG_GUCTL_PSQExtrResSp_END           (20)
#define SOC_USB3OTG_GUCTL_NoExtrDl_START             (21)
#define SOC_USB3OTG_GUCTL_NoExtrDl_END               (21)
#define SOC_USB3OTG_GUCTL_REFCLKPER_START            (22)
#define SOC_USB3OTG_GUCTL_REFCLKPER_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GBUSERRADDRL_UNION
 �ṹ˵��  : GBUSERRADDRL �Ĵ����ṹ���塣��ַƫ����:0xC130����ֵ:0x0000�����:32
 �Ĵ���˵��: ���ߴ����ַ�Ĵ���L
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  BusAddrl : 32; /* bit[0-31]: ���ߴ����ַ,��32λ�� */
    } reg;
} SOC_USB3OTG_GBUSERRADDRL_UNION;
#endif
#define SOC_USB3OTG_GBUSERRADDRL_BusAddrl_START  (0)
#define SOC_USB3OTG_GBUSERRADDRL_BusAddrl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GBUSERRADDRH_UNION
 �ṹ˵��  : GBUSERRADDRH �Ĵ����ṹ���塣��ַƫ����:0xC134����ֵ:0x0000�����:32
 �Ĵ���˵��: ���ߴ����ַ�Ĵ���H
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  BusAddrh : 32; /* bit[0-31]: ���ߴ����ַ,��32λ�� */
    } reg;
} SOC_USB3OTG_GBUSERRADDRH_UNION;
#endif
#define SOC_USB3OTG_GBUSERRADDRH_BusAddrh_START  (0)
#define SOC_USB3OTG_GBUSERRADDRH_BusAddrh_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GHWPARAMS0_UNION
 �ṹ˵��  : GHWPARAMS0 �Ĵ����ṹ���塣��ַƫ����:0xC140����ֵ:0x2020400A�����:32
 �Ĵ���˵��: Ӳ�������Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_MODE      : 3;  /* bit[0-2]  : ������ģʽѡ��DRD��
                                                              0: Device(NPI or Non-NPI)
                                                              1: Host
                                                              2: DRD
                                                              3��Hub */
        unsigned int  DWC_USB3_MBUS_TYPE : 3;  /* bit[3-5]  : Master�������ͣ�AXI��
                                                              0:AHB
                                                              1:AXI
                                                              2:Reserved
                                                              3:Native
                                                              4:NPI */
        unsigned int  DWC_USB3_SBUS_TYPE : 2;  /* bit[6-7]  : slave�������ͣ�AHB��
                                                              0:AHB
                                                              1:AXI
                                                              2:Reserved
                                                              3:Native */
        unsigned int  DWC_USB3_MDWIDTH   : 8;  /* bit[8-15] : master��������λ��64bit�� */
        unsigned int  DWC_USB3_SDWIDTH   : 8;  /* bit[16-23]: slave��������λ��32bit�� */
        unsigned int  DWC_USB3_AWIDTH    : 8;  /* bit[24-31]: ��ַλ��32bit�� */
    } reg;
} SOC_USB3OTG_GHWPARAMS0_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MODE_START       (0)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MODE_END         (2)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MBUS_TYPE_START  (3)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MBUS_TYPE_END    (5)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_SBUS_TYPE_START  (6)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_SBUS_TYPE_END    (7)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MDWIDTH_START    (8)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MDWIDTH_END      (15)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_SDWIDTH_START    (16)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_SDWIDTH_END      (23)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_AWIDTH_START     (24)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_AWIDTH_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GHWPARAMS1_UNION
 �ṹ˵��  : GHWPARAMS1 �Ĵ����ṹ���塣��ַƫ����:0xC144����ֵ:0x2E0C938�����:32
 �Ĵ���˵��: Ӳ�������Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_IDWIDTH        : 3;  /* bit[0-2]  : ID��ȡ� */
        unsigned int  DWC_USB3_BURSTWIDTH     : 3;  /* bit[3-5]  : ����burst�����źſ�ȡ� */
        unsigned int  DWC_USB3_DATAINFOWIDTH  : 3;  /* bit[6-8]  : OCP����datainfoλ�� */
        unsigned int  DWC_USB3_REQINFOWIDTH   : 3;  /* bit[9-11] : AXI����awcacheλ�� */
        unsigned int  DWC_USB3_ASPACEWIDTH    : 3;  /* bit[12-14]: AXI����awprotλ�� */
        unsigned int  DWC_USB3_DEVICE_NUM_INT : 6;  /* bit[15-20]: Device�жϸ����� */
        unsigned int  DWC_USB3_NUM_RAMS       : 2;  /* bit[21-22]: RAM������
                                                                   2��2����
                                                                   3��3���� */
        unsigned int  DWC_USB3_SRAM_TYP       : 1;  /* bit[23]   : RAM����ѡ��
                                                                   0��˫�˿�RAM��
                                                                   1�����˿�RAM�� */
        unsigned int  DWC_USB3_EN_PWROPT      : 2;  /* bit[24-25]: �����Ż�����ѡ��
                                                                   0���ޣ�
                                                                   1��ʱ���ſأ�
                                                                   2��ʱ���ſغͶ���ģʽ�� */
        unsigned int  reserved                : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_USB3OTG_GHWPARAMS1_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_IDWIDTH_START         (0)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_IDWIDTH_END           (2)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_BURSTWIDTH_START      (3)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_BURSTWIDTH_END        (5)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_DATAINFOWIDTH_START   (6)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_DATAINFOWIDTH_END     (8)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_REQINFOWIDTH_START    (9)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_REQINFOWIDTH_END      (11)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_ASPACEWIDTH_START     (12)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_ASPACEWIDTH_END       (14)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_DEVICE_NUM_INT_START  (15)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_DEVICE_NUM_INT_END    (20)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_NUM_RAMS_START        (21)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_NUM_RAMS_END          (22)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_SRAM_TYP_START        (23)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_SRAM_TYP_END          (23)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_EN_PWROPT_START       (24)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_EN_PWROPT_END         (25)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GHWPARAMS2_UNION
 �ṹ˵��  : GHWPARAMS2 �Ĵ����ṹ���塣��ַƫ����:0xC148����ֵ:0x12345678�����:32
 �Ĵ���˵��: Ӳ�������Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_USERID : 32; /* bit[0-31]: �û�ID�Ĵ����� */
    } reg;
} SOC_USB3OTG_GHWPARAMS2_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS2_DWC_USB3_USERID_START  (0)
#define SOC_USB3OTG_GHWPARAMS2_DWC_USB3_USERID_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GHWPARAMS3_UNION
 �ṹ˵��  : GHWPARAMS3 �Ĵ����ṹ���塣��ַƫ����:0xC14C����ֵ:0x10420085�����:32
 �Ĵ���˵��: Ӳ�������Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_SSPHY_INTERFACE           : 2;  /* bit[0-1]  : SS PHY�ӿڡ�
                                                                              0���ޣ�
                                                                              1��PIPE3�� */
        unsigned int  DWC_USB3_HSPHY_INTERFACE           : 2;  /* bit[2-3]  : HS PHY�ӿڡ�
                                                                              0:NONE
                                                                              1:UTMI+
                                                                              2:ULPI
                                                                              3:UTMI+ and ULPI */
        unsigned int  DWC_USB3_FSPHY_INTERFACE           : 2;  /* bit[4-5]  : FS PHY�ӿڡ�
                                                                              0���ޣ�
                                                                              1��ר�д��нӿڣ�
                                                                              2����UTMI���� */
        unsigned int  DWC_USB3_HSPHY_DWIDTH              : 2;  /* bit[6-7]  : UTMI�ӿ�����λ��
                                                                              0��8bit��
                                                                              1��16bit��
                                                                              2��8/16bit�� */
        unsigned int  reserved_0                         : 2;  /* bit[8-9]  : ������ */
        unsigned int  DWC_USB3_VENDOR_CTL_INTERFACE      : 1;  /* bit[10]   : �Ƿ�֧��UTMI+ Vendor Control�ӿڡ�
                                                                              0����֧�֣�
                                                                              1��֧�֡� */
        unsigned int  reserved_1                         : 1;  /* bit[11]   : ������ */
        unsigned int  DWC_USB3_NUM_EPS                   : 6;  /* bit[12-17]: Device֧�ֵĶ˵������ */
        unsigned int  DWC_USB3_NUM_IN_EPS                : 5;  /* bit[18-22]: ͬʱ�����IN�˵������ */
        unsigned int  DWC_USB3_CACHE_TOTAL_XFER_RESOURCE : 8;  /* bit[23-30]: cache transfer��Դ�� */
        unsigned int  reserved_2                         : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_USB3OTG_GHWPARAMS3_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_SSPHY_INTERFACE_START            (0)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_SSPHY_INTERFACE_END              (1)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_HSPHY_INTERFACE_START            (2)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_HSPHY_INTERFACE_END              (3)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_FSPHY_INTERFACE_START            (4)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_FSPHY_INTERFACE_END              (5)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_HSPHY_DWIDTH_START               (6)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_HSPHY_DWIDTH_END                 (7)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_VENDOR_CTL_INTERFACE_START       (10)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_VENDOR_CTL_INTERFACE_END         (10)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_NUM_EPS_START                    (12)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_NUM_EPS_END                      (17)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_NUM_IN_EPS_START                 (18)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_NUM_IN_EPS_END                   (22)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_CACHE_TOTAL_XFER_RESOURCE_START  (23)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_CACHE_TOTAL_XFER_RESOURCE_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GHWPARAMS4_UNION
 �ṹ˵��  : GHWPARAMS4 �Ĵ����ṹ���塣��ַƫ����:0xC150����ֵ:0x47822010�����:32
 �Ĵ���˵��: Ӳ�������Ĵ���4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_CACHE_TRBS_PER_TRANSFER : 6;  /* bit[0-5]  : ÿ��transferԤȡ��TRB�� */
        unsigned int  reserved_0                       : 7;  /* bit[6-12] : ������ */
        unsigned int  DWC_USB3_HIBER_SCRATCHBUFS       : 4;  /* bit[13-16]: ����ģʽ�£������ڲ�״̬��buffer������ */
        unsigned int  DWC_USB3_NUM_SS_USB_INSTANCE     : 4;  /* bit[17-20]: ֧��SuperSpeed�˿ڸ����� */
        unsigned int  reserved_1                       : 2;  /* bit[21-22]: ������ */
        unsigned int  DWC_USB3_EN_ISOC_SUPT            : 1;  /* bit[23]   : �Ƿ�֧��ͬ�����䡣
                                                                            0����֧�֣�
                                                                            1��֧�֡� */
        unsigned int  DWC_USB3_BMU_PTL_DEPTH           : 4;  /* bit[24-27]: BMUģ��PTL��ȡ� */
        unsigned int  DWC_USB3_BMU_LSP_DEPTH           : 4;  /* bit[28-31]: BMUģ��LSP��ȡ� */
    } reg;
} SOC_USB3OTG_GHWPARAMS4_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_CACHE_TRBS_PER_TRANSFER_START  (0)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_CACHE_TRBS_PER_TRANSFER_END    (5)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_HIBER_SCRATCHBUFS_START        (13)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_HIBER_SCRATCHBUFS_END          (16)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_NUM_SS_USB_INSTANCE_START      (17)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_NUM_SS_USB_INSTANCE_END        (20)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_EN_ISOC_SUPT_START             (23)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_EN_ISOC_SUPT_END               (23)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_BMU_PTL_DEPTH_START            (24)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_BMU_PTL_DEPTH_END              (27)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_BMU_LSP_DEPTH_START            (28)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_BMU_LSP_DEPTH_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GHWPARAMS5_UNION
 �ṹ˵��  : GHWPARAMS5 �Ĵ����ṹ���塣��ַƫ����:0xC154����ֵ:0x4204108�����:32
 �Ĵ���˵��: Ӳ�������Ĵ���5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_BMU_BUSGM_DEPTH : 4;  /* bit[0-3]  : AXI����GMģ��buffer��ȡ� */
        unsigned int  DWC_USB3_RXQ_FIFO_DEPTH  : 6;  /* bit[4-9]  : �������������ȡ� */
        unsigned int  DWC_USB3_TXQ_FIFO_DEPTH  : 6;  /* bit[10-15]: �������������ȡ� */
        unsigned int  DWC_USB3_DWQ_FIFO_DEPTH  : 6;  /* bit[16-21]: ������д������ȡ� */
        unsigned int  DWC_USB3_DFQ_FIFO_DEPTH  : 6;  /* bit[22-27]: ������Ԥȡ������ȡ� */
        unsigned int  reserved                 : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_USB3OTG_GHWPARAMS5_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_BMU_BUSGM_DEPTH_START  (0)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_BMU_BUSGM_DEPTH_END    (3)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_RXQ_FIFO_DEPTH_START   (4)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_RXQ_FIFO_DEPTH_END     (9)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_TXQ_FIFO_DEPTH_START   (10)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_TXQ_FIFO_DEPTH_END     (15)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_DWQ_FIFO_DEPTH_START   (16)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_DWQ_FIFO_DEPTH_END     (21)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_DFQ_FIFO_DEPTH_START   (22)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_DFQ_FIFO_DEPTH_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GHWPARAMS6_UNION
 �ṹ˵��  : GHWPARAMS6 �Ĵ����ṹ���塣��ַƫ����:0xC158����ֵ:0x0800BC20�����:32
 �Ĵ���˵��: Ӳ�������Ĵ���6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_PSQ_FIFO_DEPTH : 6;  /* bit[0-5]  : Э��״̬������ȡ� */
        unsigned int  reserved_0              : 1;  /* bit[6]    : ������ */
        unsigned int  DWC_USB3_EN_FPGA        : 1;  /* bit[7]    : �Ƿ�ʹ��FPGAʱ���Ż���
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  reserved_1              : 2;  /* bit[8-9]  : ������ */
        unsigned int  DWC_USB3_EN_SRP         : 1;  /* bit[10]   : �Ƿ�ʹ��SRP��
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  DWC_USB3_EN_HNP         : 1;  /* bit[11]   : �Ƿ�ʹ��HNP��
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  DWC_USB3_EN_ADP         : 1;  /* bit[12]   : �Ƿ�ʹ��ADP��
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  DWC_USB3_OTG3_SUPT      : 1;  /* bit[13]   : �Ƿ�֧��OTG3.0��
                                                                   0����֧�֣�
                                                                   1��֧�֡� */
        unsigned int  DWC_USB3_EN_BC          : 1;  /* bit[14]   : BCʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  DWC_USB3_EN_BUS_FILTER  : 1;  /* bit[15]   : ʹ��OTG����źŵ�filter�� */
        unsigned int  DWC_USB3_RAM0_DEPTH     : 16; /* bit[16-31]: RAM0��ȡ� */
    } reg;
} SOC_USB3OTG_GHWPARAMS6_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_PSQ_FIFO_DEPTH_START  (0)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_PSQ_FIFO_DEPTH_END    (5)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_FPGA_START         (7)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_FPGA_END           (7)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_SRP_START          (10)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_SRP_END            (10)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_HNP_START          (11)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_HNP_END            (11)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_ADP_START          (12)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_ADP_END            (12)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_OTG3_SUPT_START       (13)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_OTG3_SUPT_END         (13)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_BC_START           (14)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_BC_END             (14)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_BUS_FILTER_START   (15)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_BUS_FILTER_END     (15)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_RAM0_DEPTH_START      (16)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_RAM0_DEPTH_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GHWPARAMS7_UNION
 �ṹ˵��  : GHWPARAMS7 �Ĵ����ṹ���塣��ַƫ����:0xC15C����ֵ:0x07761000�����:32
 �Ĵ���˵��: Ӳ�������Ĵ���7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_RAM1_DEPTH : 16; /* bit[0-15] : RAM1��ȡ� */
        unsigned int  DWC_USB3_RAM2_DEPTH : 16; /* bit[16-31]: RAM2��ȡ� */
    } reg;
} SOC_USB3OTG_GHWPARAMS7_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS7_DWC_USB3_RAM1_DEPTH_START  (0)
#define SOC_USB3OTG_GHWPARAMS7_DWC_USB3_RAM1_DEPTH_END    (15)
#define SOC_USB3OTG_GHWPARAMS7_DWC_USB3_RAM2_DEPTH_START  (16)
#define SOC_USB3OTG_GHWPARAMS7_DWC_USB3_RAM2_DEPTH_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GHWPARAMS8_UNION
 �ṹ˵��  : GHWPARAMS8 �Ĵ����ṹ���塣��ַƫ����:0xC600����ֵ:0x000007D0�����:32
 �Ĵ���˵��: Ӳ�������Ĵ���8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DWC_USB3_DCACHE_DEPTH_INFO : 32; /* bit[0-31]: dcache�����Ϣ�� */
    } reg;
} SOC_USB3OTG_GHWPARAMS8_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS8_DWC_USB3_DCACHE_DEPTH_INFO_START  (0)
#define SOC_USB3OTG_GHWPARAMS8_DWC_USB3_DCACHE_DEPTH_INFO_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GDBGFIFOSPACE_UNION
 �ṹ˵��  : GDBGFIFOSPACE �Ĵ����ṹ���塣��ַƫ����:0xC160����ֵ:0x0000�����:32
 �Ĵ���˵��: Queue/FIFOʣ��ռ�debug�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  FIFOSek        : 8;  /* bit[0-7]  : FIFO/Queueѡ��
                                                          8��b0001_1111 to 8'b0000_0000: ����FIFO31������FIFO0��
                                                          8��b0011_1111 to 8'b0010_0000: ����FIFO31������FIFO0��
                                                          8'b0101_1111 to 8'b0100_0000: �����������31�������������0��
                                                          8'b0111_1111 to 8'b0110_0000: �����������31�������������0��
                                                          8'b1001_1111 to 8'b1000_0000: ������Ϣ����31��������Ϣ����0��
                                                          8��b1010_0000: ������Ԥȡ���У�
                                                          8'b1010_0001: �¼����У�
                                                          8'b1010_0010: Э��״̬���С� */
        unsigned int  reserved       : 8;  /* bit[8-15] : ������ */
        unsigned int  SpaceAvailable : 16; /* bit[16-31]: ʣ��ռ䡣 */
    } reg;
} SOC_USB3OTG_GDBGFIFOSPACE_UNION;
#endif
#define SOC_USB3OTG_GDBGFIFOSPACE_FIFOSek_START         (0)
#define SOC_USB3OTG_GDBGFIFOSPACE_FIFOSek_END           (7)
#define SOC_USB3OTG_GDBGFIFOSPACE_SpaceAvailable_START  (16)
#define SOC_USB3OTG_GDBGFIFOSPACE_SpaceAvailable_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GDBGLTSSM_UNION
 �ṹ˵��  : GDBGLTSSM �Ĵ����ṹ���塣��ַƫ����:0xC164����ֵ:0x0000�����:32
 �Ĵ���˵��: LTSSM debug�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ltssm : 32; /* bit[0-31]: LTSSM debug��Ϣ�� */
    } reg;
} SOC_USB3OTG_GDBGLTSSM_UNION;
#endif
#define SOC_USB3OTG_GDBGLTSSM_ltssm_START  (0)
#define SOC_USB3OTG_GDBGLTSSM_ltssm_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GDBGLNMCC_UNION
 �ṹ˵��  : GDBGLNMCC �Ĵ����ṹ���塣��ַƫ����:0xC168����ֵ:0x0000�����:32
 �Ĵ���˵��: LNMCC debug�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  LNMCC_BERC : 9;  /* bit[0-8] : ָʾ�˿���������Ϣ�� */
        unsigned int  reserved   : 23; /* bit[9-31]: ������ */
    } reg;
} SOC_USB3OTG_GDBGLNMCC_UNION;
#endif
#define SOC_USB3OTG_GDBGLNMCC_LNMCC_BERC_START  (0)
#define SOC_USB3OTG_GDBGLNMCC_LNMCC_BERC_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GCBGBMU_UNION
 �ṹ˵��  : GCBGBMU �Ĵ����ṹ���塣��ַƫ����:0xC16C����ֵ:0x0000�����:32
 �Ĵ���˵��: BMU debug�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CCU : 4;  /* bit[0-3] : CCU debug��Ϣ�� */
        unsigned int  DCU : 4;  /* bit[4-7] : DCU debug��Ϣ�� */
        unsigned int  BCU : 24; /* bit[8-31]: BCU debug��Ϣ�� */
    } reg;
} SOC_USB3OTG_GCBGBMU_UNION;
#endif
#define SOC_USB3OTG_GCBGBMU_CCU_START  (0)
#define SOC_USB3OTG_GCBGBMU_CCU_END    (3)
#define SOC_USB3OTG_GCBGBMU_DCU_START  (4)
#define SOC_USB3OTG_GCBGBMU_DCU_END    (7)
#define SOC_USB3OTG_GCBGBMU_BCU_START  (8)
#define SOC_USB3OTG_GCBGBMU_BCU_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GDBGLSPMUX_UNION
 �ṹ˵��  : GDBGLSPMUX �Ĵ����ṹ���塣��ַƫ����:0xC170����ֵ:0x0000�����:32
 �Ĵ���˵��: LSPMUX debug�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  LSPMUX : 32; /* bit[0-31]: LSPMUX debug��Ϣ�� */
    } reg;
} SOC_USB3OTG_GDBGLSPMUX_UNION;
#endif
#define SOC_USB3OTG_GDBGLSPMUX_LSPMUX_START  (0)
#define SOC_USB3OTG_GDBGLSPMUX_LSPMUX_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GDBGLSP_UNION
 �ṹ˵��  : GDBGLSP �Ĵ����ṹ���塣��ַƫ����:0xC174����ֵ:0x0000�����:32
 �Ĵ���˵��: LSP debug�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  LSP : 32; /* bit[0-31]: LSP debug��Ϣ�� */
    } reg;
} SOC_USB3OTG_GDBGLSP_UNION;
#endif
#define SOC_USB3OTG_GDBGLSP_LSP_START  (0)
#define SOC_USB3OTG_GDBGLSP_LSP_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GDBGEPINFO0_UNION
 �ṹ˵��  : GDBGEPINFO0 �Ĵ����ṹ���塣��ַƫ����:0xC178����ֵ:0x0000�����:32
 �Ĵ���˵��: endpoint debug�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EpDbg : 32; /* bit[0-31]: endpoint debug��Ϣ��32λ�� */
    } reg;
} SOC_USB3OTG_GDBGEPINFO0_UNION;
#endif
#define SOC_USB3OTG_GDBGEPINFO0_EpDbg_START  (0)
#define SOC_USB3OTG_GDBGEPINFO0_EpDbg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GDBGEPINFO1_UNION
 �ṹ˵��  : GDBGEPINFO1 �Ĵ����ṹ���塣��ַƫ����:0xC17C����ֵ:0x0000�����:32
 �Ĵ���˵��: endpoint debug�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EpDbg : 32; /* bit[0-31]: endpoint debug��Ϣ��32λ�� */
    } reg;
} SOC_USB3OTG_GDBGEPINFO1_UNION;
#endif
#define SOC_USB3OTG_GDBGEPINFO1_EpDbg_START  (0)
#define SOC_USB3OTG_GDBGEPINFO1_EpDbg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GUSB2PHYCFG_UNION
 �ṹ˵��  : GUSB2PHYCFG �Ĵ����ṹ���塣��ַƫ����:0xC200����ֵ:0x2400�����:32
 �Ĵ���˵��: USB2 PHY���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TOutCal           : 3;  /* bit[0-2]  : ��ʱʱ������� */
        unsigned int  PHYIf             : 1;  /* bit[3]    : UTMI�ӿ�λ��ѡ��
                                                             0��8bit��
                                                             1��16bit�� */
        unsigned int  reserved_0        : 2;  /* bit[4-5]  : ������ */
        unsigned int  SusPHY            : 1;  /* bit[6]    : Suspend USB2.0 PHY�� */
        unsigned int  reserved_1        : 1;  /* bit[7]    : ������ */
        unsigned int  EnblSlpM          : 1;  /* bit[8]    : ʹ��utmi_sleep_n��utmi_l1_suspend_n */
        unsigned int  reserved_2        : 1;  /* bit[9]    : ������ */
        unsigned int  USBTrdTim         : 4;  /* bit[10-13]: USB2.0ת��ʱ�䡣
                                                             4'h5������16λUTMI�ӿڣ�
                                                             4'h9������8λUTMI�ӿڡ� */
        unsigned int  reserved_3        : 16; /* bit[14-29]: ������ */
        unsigned int  U2_FREECLK_EXISTS : 1;  /* bit[30]   : USB2.0 PHY�Ƿ����ṩfree clock��
                                                             0�����ܣ�
                                                             1���ܡ� */
        unsigned int  PHYSoftRst        : 1;  /* bit[31]   : ��λ���ơ�
                                                             0������λ��
                                                             1����λ�� */
    } reg;
} SOC_USB3OTG_GUSB2PHYCFG_UNION;
#endif
#define SOC_USB3OTG_GUSB2PHYCFG_TOutCal_START            (0)
#define SOC_USB3OTG_GUSB2PHYCFG_TOutCal_END              (2)
#define SOC_USB3OTG_GUSB2PHYCFG_PHYIf_START              (3)
#define SOC_USB3OTG_GUSB2PHYCFG_PHYIf_END                (3)
#define SOC_USB3OTG_GUSB2PHYCFG_SusPHY_START             (6)
#define SOC_USB3OTG_GUSB2PHYCFG_SusPHY_END               (6)
#define SOC_USB3OTG_GUSB2PHYCFG_EnblSlpM_START           (8)
#define SOC_USB3OTG_GUSB2PHYCFG_EnblSlpM_END             (8)
#define SOC_USB3OTG_GUSB2PHYCFG_USBTrdTim_START          (10)
#define SOC_USB3OTG_GUSB2PHYCFG_USBTrdTim_END            (13)
#define SOC_USB3OTG_GUSB2PHYCFG_U2_FREECLK_EXISTS_START  (30)
#define SOC_USB3OTG_GUSB2PHYCFG_U2_FREECLK_EXISTS_END    (30)
#define SOC_USB3OTG_GUSB2PHYCFG_PHYSoftRst_START         (31)
#define SOC_USB3OTG_GUSB2PHYCFG_PHYSoftRst_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GUSB3PIPECTL_UNION
 �ṹ˵��  : GUSB3PIPECTL �Ĵ����ṹ���塣��ַƫ����:0xC2C0����ֵ:0x10C8002�����:32
 �Ĵ���˵��: USB3 PIPE���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ElesticBufferMode   : 1;  /* bit[0]    : Elasticity bufferģʽ���á�
                                                               1��ȫ��bufferģʽ��
                                                               0������bufferģʽ�� */
        unsigned int  TxDeemphasis        : 2;  /* bit[1-2]  : �����ź�ȥ���ؿ��ơ�
                                                               00��6dBȥ���أ�
                                                               01��3.5dBȥ���أ�
                                                               10����ȥ���أ�
                                                               11�������� */
        unsigned int  TxMargin            : 3;  /* bit[3-5]  : PIPE TxMargin�ź����á� */
        unsigned int  TxSwing             : 1;  /* bit[6]    : PIPE TxSwing�ź����á� */
        unsigned int  reserved            : 1;  /* bit[7]    : ������ */
        unsigned int  RxDetToPolling      : 1;  /* bit[8]    : ��RX_DECT״̬����Polling.LFPS״̬�ӳٿ��ơ�
                                                               0���ӳ�400us��
                                                               1�����ӳ١� */
        unsigned int  LFPSFilt            : 1;  /* bit[9]    : LFPS�˲�ʹ�ܡ� */
        unsigned int  P3ExSigP2           : 1;  /* bit[10]   : ������U3�˳����֣�ֱ��ʹPHY����P2״̬����������Ϊ0�� */
        unsigned int  P3P2TranOK          : 1;  /* bit[11]   : P2P3״ֱ̬����ת������Ҫ����P0״̬����������Ϊ0�� */
        unsigned int  LFPSP0Algn          : 1;  /* bit[12]   : LFPS�ź�P0���롣��������Ϊ0�� */
        unsigned int  SkipRxDet           : 1;  /* bit[13]   : �������ռ�⡣ */
        unsigned int  AbortRxDetInU2      : 1;  /* bit[14]   : ��U2״̬��ֹ���ռ�⡣��������Ϊ0�� */
        unsigned int  DatWidth            : 2;  /* bit[15-16]: PIPE�ӿ�����λ��
                                                               00��32bit��
                                                               01��16bit��
                                                               10��8bit��
                                                               11��reserved�� */
        unsigned int  Suspend_en          : 1;  /* bit[17]   : Suspend USB3.0 SS PHY�� */
        unsigned int  DelayP1P2P3En       : 1;  /* bit[18]   : �ӳٽ���P1/P2/P3״̬ʹ�ܡ�
                                                               0��ʹ�ܣ�
                                                               1����ʹ�ܡ� */
        unsigned int  DelayP1P2P3         : 3;  /* bit[19-21]: �ӳٽ���P1/P2/P3״̬�� */
        unsigned int  DisRxDetU3RxDet     : 1;  /* bit[22]   : ��U3����Rx.Det״̬���Ƿ�ʹ�ܽ��ռ�⡣
                                                               0��ʹ�ܣ�
                                                               1����ʹ�ܡ� */
        unsigned int  StartRxdetU3ExDet   : 1;  /* bit[23]   : ʹ�ܽ�������⡣
                                                               0����ʹ�ܣ�
                                                               1��ʹ�ܡ� */
        unsigned int  RequestP1P2P3       : 1;  /* bit[24]   : ����������U1/U2/U3״̬������������PHY������Ӧ��P1/P2/P3״̬��
                                                               0����ʹ�ܣ�
                                                               1��ʹ�ܡ�
                                                               ��λ��������Ϊ1�� */
        unsigned int  U1U2ExitFailToRecov : 1;  /* bit[25]   : U1/U2����ʧ��״̬���ơ�
                                                               1�����U1/U2 LFPS����ʧ�ܣ�LTSSM״̬����U1/U2ת�Ƶ�recovery״̬�����recoveryʧ�ܣ�LTSSM��ת�Ƶ�SS.Inactive״̬��
                                                               0�����U1/U2 LFPS����ʧ�ܣ�LTSSM״̬����U1/U2ת�Ƶ�SS.Inactive״̬�� */
        unsigned int  PingEnhancementEn   : 1;  /* bit[26]   : �ӳ�PING��ʱʱ��ʹ�ܡ���������Ϊ0��
                                                               0����ʹ�ܣ�
                                                               1��ʹ�ܡ� */
        unsigned int  UxExitInPx          : 1;  /* bit[27]   : �͹���״̬�˳����ơ���������Ϊ0��
                                                               0����PHY��P0״̬ʱ���������˳�U1/U2/U3״̬��
                                                               1����PHY��P1/P2/P3״̬ʱ���������˳���Ӧ��U1/U2/U3״̬�� */
        unsigned int  DisRxDetP3          : 1;  /* bit[28]   : ��P3״̬���Ƿ�ʹ�ܽ��ռ�⡣
                                                               0��ʹ�ܣ�
                                                               1����ʹ�ܡ� */
        unsigned int  u2SSInactP3ok       : 1;  /* bit[29]   : P3״̬���ơ�
                                                               0����·����U2��SS.Inactive��ʹPHY����P2״̬��
                                                               1����·����U2��SS.Inactive��ʹPHY����P3״̬�� */
        unsigned int  HstPrtCmpl          : 1;  /* bit[30]   : Host�˿ڼ���ģʽ���ơ� */
        unsigned int  PHYSoftRst          : 1;  /* bit[31]   : USB3.0 PHY��λ���ơ�
                                                               0������λ��
                                                               1����λ�� */
    } reg;
} SOC_USB3OTG_GUSB3PIPECTL_UNION;
#endif
#define SOC_USB3OTG_GUSB3PIPECTL_ElesticBufferMode_START    (0)
#define SOC_USB3OTG_GUSB3PIPECTL_ElesticBufferMode_END      (0)
#define SOC_USB3OTG_GUSB3PIPECTL_TxDeemphasis_START         (1)
#define SOC_USB3OTG_GUSB3PIPECTL_TxDeemphasis_END           (2)
#define SOC_USB3OTG_GUSB3PIPECTL_TxMargin_START             (3)
#define SOC_USB3OTG_GUSB3PIPECTL_TxMargin_END               (5)
#define SOC_USB3OTG_GUSB3PIPECTL_TxSwing_START              (6)
#define SOC_USB3OTG_GUSB3PIPECTL_TxSwing_END                (6)
#define SOC_USB3OTG_GUSB3PIPECTL_RxDetToPolling_START       (8)
#define SOC_USB3OTG_GUSB3PIPECTL_RxDetToPolling_END         (8)
#define SOC_USB3OTG_GUSB3PIPECTL_LFPSFilt_START             (9)
#define SOC_USB3OTG_GUSB3PIPECTL_LFPSFilt_END               (9)
#define SOC_USB3OTG_GUSB3PIPECTL_P3ExSigP2_START            (10)
#define SOC_USB3OTG_GUSB3PIPECTL_P3ExSigP2_END              (10)
#define SOC_USB3OTG_GUSB3PIPECTL_P3P2TranOK_START           (11)
#define SOC_USB3OTG_GUSB3PIPECTL_P3P2TranOK_END             (11)
#define SOC_USB3OTG_GUSB3PIPECTL_LFPSP0Algn_START           (12)
#define SOC_USB3OTG_GUSB3PIPECTL_LFPSP0Algn_END             (12)
#define SOC_USB3OTG_GUSB3PIPECTL_SkipRxDet_START            (13)
#define SOC_USB3OTG_GUSB3PIPECTL_SkipRxDet_END              (13)
#define SOC_USB3OTG_GUSB3PIPECTL_AbortRxDetInU2_START       (14)
#define SOC_USB3OTG_GUSB3PIPECTL_AbortRxDetInU2_END         (14)
#define SOC_USB3OTG_GUSB3PIPECTL_DatWidth_START             (15)
#define SOC_USB3OTG_GUSB3PIPECTL_DatWidth_END               (16)
#define SOC_USB3OTG_GUSB3PIPECTL_Suspend_en_START           (17)
#define SOC_USB3OTG_GUSB3PIPECTL_Suspend_en_END             (17)
#define SOC_USB3OTG_GUSB3PIPECTL_DelayP1P2P3En_START        (18)
#define SOC_USB3OTG_GUSB3PIPECTL_DelayP1P2P3En_END          (18)
#define SOC_USB3OTG_GUSB3PIPECTL_DelayP1P2P3_START          (19)
#define SOC_USB3OTG_GUSB3PIPECTL_DelayP1P2P3_END            (21)
#define SOC_USB3OTG_GUSB3PIPECTL_DisRxDetU3RxDet_START      (22)
#define SOC_USB3OTG_GUSB3PIPECTL_DisRxDetU3RxDet_END        (22)
#define SOC_USB3OTG_GUSB3PIPECTL_StartRxdetU3ExDet_START    (23)
#define SOC_USB3OTG_GUSB3PIPECTL_StartRxdetU3ExDet_END      (23)
#define SOC_USB3OTG_GUSB3PIPECTL_RequestP1P2P3_START        (24)
#define SOC_USB3OTG_GUSB3PIPECTL_RequestP1P2P3_END          (24)
#define SOC_USB3OTG_GUSB3PIPECTL_U1U2ExitFailToRecov_START  (25)
#define SOC_USB3OTG_GUSB3PIPECTL_U1U2ExitFailToRecov_END    (25)
#define SOC_USB3OTG_GUSB3PIPECTL_PingEnhancementEn_START    (26)
#define SOC_USB3OTG_GUSB3PIPECTL_PingEnhancementEn_END      (26)
#define SOC_USB3OTG_GUSB3PIPECTL_UxExitInPx_START           (27)
#define SOC_USB3OTG_GUSB3PIPECTL_UxExitInPx_END             (27)
#define SOC_USB3OTG_GUSB3PIPECTL_DisRxDetP3_START           (28)
#define SOC_USB3OTG_GUSB3PIPECTL_DisRxDetP3_END             (28)
#define SOC_USB3OTG_GUSB3PIPECTL_u2SSInactP3ok_START        (29)
#define SOC_USB3OTG_GUSB3PIPECTL_u2SSInactP3ok_END          (29)
#define SOC_USB3OTG_GUSB3PIPECTL_HstPrtCmpl_START           (30)
#define SOC_USB3OTG_GUSB3PIPECTL_HstPrtCmpl_END             (30)
#define SOC_USB3OTG_GUSB3PIPECTL_PHYSoftRst_START           (31)
#define SOC_USB3OTG_GUSB3PIPECTL_PHYSoftRst_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GTXFIFOSIZm_UNION
 �ṹ˵��  : GTXFIFOSIZm �Ĵ����ṹ���塣��ַƫ����:0xC300+m*0x4����ֵ:0x0000�����:32
 �Ĵ���˵��: ����FIFOm��С���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TxFDep    : 16; /* bit[0-15] : ����FIFO��ȡ� */
        unsigned int  TxFStAddr : 16; /* bit[16-31]: ����FIFO��ʼ��ַ�� */
    } reg;
} SOC_USB3OTG_GTXFIFOSIZm_UNION;
#endif
#define SOC_USB3OTG_GTXFIFOSIZm_TxFDep_START     (0)
#define SOC_USB3OTG_GTXFIFOSIZm_TxFDep_END       (15)
#define SOC_USB3OTG_GTXFIFOSIZm_TxFStAddr_START  (16)
#define SOC_USB3OTG_GTXFIFOSIZm_TxFStAddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GRXFIFOSIZn_UNION
 �ṹ˵��  : GRXFIFOSIZn �Ĵ����ṹ���塣��ַƫ����:0xC380+(n)*0x4����ֵ:0x0000�����:32
 �Ĵ���˵��: ����FIFOn��С���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RxFDep    : 16; /* bit[0-15] : ����FIFO��ȡ� */
        unsigned int  RxFStAddr : 16; /* bit[16-31]: ����FIFO��ʼ��ַ�� */
    } reg;
} SOC_USB3OTG_GRXFIFOSIZn_UNION;
#endif
#define SOC_USB3OTG_GRXFIFOSIZn_RxFDep_START     (0)
#define SOC_USB3OTG_GRXFIFOSIZn_RxFDep_END       (15)
#define SOC_USB3OTG_GRXFIFOSIZn_RxFStAddr_START  (16)
#define SOC_USB3OTG_GRXFIFOSIZn_RxFStAddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GEVNTADRLo_UNION
 �ṹ˵��  : GEVNTADRLo �Ĵ����ṹ���塣��ַƫ����:0xC400����ֵ:0x0000�����:32
 �Ĵ���˵��: �¼�buffer��ַ��32λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EvntAdrLo : 32; /* bit[0-31]: �¼�buffer��ַ��32λ�� */
    } reg;
} SOC_USB3OTG_GEVNTADRLo_UNION;
#endif
#define SOC_USB3OTG_GEVNTADRLo_EvntAdrLo_START  (0)
#define SOC_USB3OTG_GEVNTADRLo_EvntAdrLo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GEVNTADRHi_UNION
 �ṹ˵��  : GEVNTADRHi �Ĵ����ṹ���塣��ַƫ����:0xC404����ֵ:0x0000�����:32
 �Ĵ���˵��: �¼�buffer��ַ��32λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EvntAdrHi : 32; /* bit[0-31]: �¼�buffer��ַ��32λ�� */
    } reg;
} SOC_USB3OTG_GEVNTADRHi_UNION;
#endif
#define SOC_USB3OTG_GEVNTADRHi_EvntAdrHi_START  (0)
#define SOC_USB3OTG_GEVNTADRHi_EvntAdrHi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GEVNTSIZ_UNION
 �ṹ˵��  : GEVNTSIZ �Ĵ����ṹ���塣��ַƫ����:0xC408����ֵ:0x0000�����:32
 �Ĵ���˵��: �¼�buffer��С�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EVNTSiz     : 16; /* bit[0-15] : �¼�buffer��С�����ֽ�Ϊ��λ����СΪ32�ֽڡ� */
        unsigned int  reserved    : 15; /* bit[16-30]: ������ */
        unsigned int  EvntIntMask : 1;  /* bit[31]   : �¼��ж�����λ������Ϊ1�����жϲ�������� */
    } reg;
} SOC_USB3OTG_GEVNTSIZ_UNION;
#endif
#define SOC_USB3OTG_GEVNTSIZ_EVNTSiz_START      (0)
#define SOC_USB3OTG_GEVNTSIZ_EVNTSiz_END        (15)
#define SOC_USB3OTG_GEVNTSIZ_EvntIntMask_START  (31)
#define SOC_USB3OTG_GEVNTSIZ_EvntIntMask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GEVNTCOUNT_UNION
 �ṹ˵��  : GEVNTCOUNT �Ĵ����ṹ���塣��ַƫ����:0xC40C����ֵ:0x0000�����:32
 �Ĵ���˵��: �¼���Ŀ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EVNTCount : 16; /* bit[0-15] : �¼���Ŀ��
                                                     �ԸüĴ������ж������������¼�buffer��ʣ���¼�������
                                                     �ԸüĴ�������д������Ӳ����ʣ���¼�������ȥ���д���ֵ��
                                                     ����Ϊ0�ᴥ���жϡ� */
        unsigned int  reserved  : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_USB3OTG_GEVNTCOUNT_UNION;
#endif
#define SOC_USB3OTG_GEVNTCOUNT_EVNTCount_START  (0)
#define SOC_USB3OTG_GEVNTCOUNT_EVNTCount_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GTXFIFOPRIDEV_UNION
 �ṹ˵��  : GTXFIFOPRIDEV �Ĵ����ṹ���塣��ַƫ����:0xC610����ֵ:0x0000�����:32
 �Ĵ���˵��: Device����FIFO���ȼ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TxFifoPri : 16; /* bit[0-15] : ����FIFO���ȼ�����������DMA�ٲõ����ȼ���ÿbit��Ӧһ���˵㷢��FIFO�����ȼ���
                                                     0�������ȼ���
                                                     1�������ȼ��� */
        unsigned int  reserved  : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_USB3OTG_GTXFIFOPRIDEV_UNION;
#endif
#define SOC_USB3OTG_GTXFIFOPRIDEV_TxFifoPri_START  (0)
#define SOC_USB3OTG_GTXFIFOPRIDEV_TxFifoPri_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GTXFIFOPRIHST_UNION
 �ṹ˵��  : GTXFIFOPRIHST �Ĵ����ṹ���塣��ַƫ����:0xC618����ֵ:0x0000�����:32
 �Ĵ���˵��: Host����FIFO���ȼ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TxFifoPri : 3;  /* bit[0-2] : ����FIFO���ȼ�����������DMA�ٲõ����ȼ���Bit[2]��ӦSuperSpeed�˿ڷ���FIFO��bit[1]��ӦHighSpeed�˿ڷ���FIFO��bit[0]��ӦFullSpeed/LowSpeed�˿ڷ���FIFO��
                                                    0�������ȼ���
                                                    1�������ȼ��� */
        unsigned int  reserved  : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_USB3OTG_GTXFIFOPRIHST_UNION;
#endif
#define SOC_USB3OTG_GTXFIFOPRIHST_TxFifoPri_START  (0)
#define SOC_USB3OTG_GTXFIFOPRIHST_TxFifoPri_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GRXFIFOPRIHST_UNION
 �ṹ˵��  : GRXFIFOPRIHST �Ĵ����ṹ���塣��ַƫ����:0xC61C����ֵ:0x0000�����:32
 �Ĵ���˵��: Host����FIFO���ȼ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RxFifoPri : 3;  /* bit[0-2] : ����FIFO���ȼ�����������DMA�ٲõ����ȼ���Bit[2]��ӦSuperSpeed�˿ڷ���FIFO��bit[1]��ӦHighSpeed�˿ڷ���FIFO��bit[0]��ӦFullSpeed/LowSpeed�˿ڷ���FIFO��
                                                    0�������ȼ���
                                                    1�������ȼ��� */
        unsigned int  reserved  : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_USB3OTG_GRXFIFOPRIHST_UNION;
#endif
#define SOC_USB3OTG_GRXFIFOPRIHST_RxFifoPri_START  (0)
#define SOC_USB3OTG_GRXFIFOPRIHST_RxFifoPri_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GDMAHLRATIO_UNION
 �ṹ˵��  : GDMAHLRATIO �Ĵ����ṹ���塣��ַƫ����:0xC624����ֵ:0x0404�����:32
 �Ĵ���˵��: Host�ߵ����ȼ�Ȩ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TxFifoRatio : 5;  /* bit[0-4]  : ����FIFO���á� */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  : ������ */
        unsigned int  RxFifoRatio : 5;  /* bit[8-12] : ����FIFO���á�SuperSpeed�˿���USB2.0�˿ڽ����ٲ�ʱ������Roud-Robin����������������ѯ������ */
        unsigned int  reserved_1  : 19; /* bit[13-31]: ������ */
    } reg;
} SOC_USB3OTG_GDMAHLRATIO_UNION;
#endif
#define SOC_USB3OTG_GDMAHLRATIO_TxFifoRatio_START  (0)
#define SOC_USB3OTG_GDMAHLRATIO_TxFifoRatio_END    (4)
#define SOC_USB3OTG_GDMAHLRATIO_RxFifoRatio_START  (8)
#define SOC_USB3OTG_GDMAHLRATIO_RxFifoRatio_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_GFLADJ_UNION
 �ṹ˵��  : GFLADJ �Ĵ����ṹ���塣��ַƫ����:0xC630����ֵ:0x8C80C8A0�����:32
 �Ĵ���˵��: ֡���ȵ����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fladj : 32; /* bit[0-31]: ֡���ȵ����Ĵ����� */
    } reg;
} SOC_USB3OTG_GFLADJ_UNION;
#endif
#define SOC_USB3OTG_GFLADJ_fladj_START  (0)
#define SOC_USB3OTG_GFLADJ_fladj_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DCFG_UNION
 �ṹ˵��  : DCFG �Ĵ����ṹ���塣��ַƫ����:0xC700����ֵ:0x80000�����:32
 �Ĵ���˵��: device���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DevSpd         : 3;  /* bit[0-2]  : Device�ٶȡ��������device��֧�ֵ����ö���ٶȡ�
                                                          000��High Speed��
                                                          001��Full Speed��
                                                          100��Super Speed��
                                                          Others��reserved�� */
        unsigned int  DevAddr        : 7;  /* bit[3-9]  : device��ַ��
                                                          ����������յ�SetAddress������޸ĸ������յ�USB��λ�󣬽��������㡣 */
        unsigned int  reserved_0     : 2;  /* bit[10-11]: ������ */
        unsigned int  IntrNum        : 5;  /* bit[12-16]: �Ƕ˵���ص��ж���Ŀ�� */
        unsigned int  NumP           : 5;  /* bit[17-21]: ���հ��������������ACK����NumP�򡣿��Ը��ݽ���FIFO��С����������buffer�Ĵ�С��ϵͳ��latency�������� */
        unsigned int  LPMCap         : 1;  /* bit[22]   : LPMʹ�ܡ�
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  IgnoreStreamPP : 1;  /* bit[23]   : ����PP(Packets Pending)������֧��stream��bulk�˵���Ч��
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  reserved_1     : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_USB3OTG_DCFG_UNION;
#endif
#define SOC_USB3OTG_DCFG_DevSpd_START          (0)
#define SOC_USB3OTG_DCFG_DevSpd_END            (2)
#define SOC_USB3OTG_DCFG_DevAddr_START         (3)
#define SOC_USB3OTG_DCFG_DevAddr_END           (9)
#define SOC_USB3OTG_DCFG_IntrNum_START         (12)
#define SOC_USB3OTG_DCFG_IntrNum_END           (16)
#define SOC_USB3OTG_DCFG_NumP_START            (17)
#define SOC_USB3OTG_DCFG_NumP_END              (21)
#define SOC_USB3OTG_DCFG_LPMCap_START          (22)
#define SOC_USB3OTG_DCFG_LPMCap_END            (22)
#define SOC_USB3OTG_DCFG_IgnoreStreamPP_START  (23)
#define SOC_USB3OTG_DCFG_IgnoreStreamPP_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DCTL_UNION
 �ṹ˵��  : DCTL �Ĵ����ṹ���塣��ַƫ����:0xC704����ֵ:0x0000�����:32
 �Ĵ���˵��: device���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0      : 1;  /* bit[0]    : ������ */
        unsigned int  TstCtl          : 4;  /* bit[1-4]  : ����ģʽ���ƣ�
                                                           0000������ģʽ��ʹ��
                                                           0001��Test_J
                                                           0010: Test_K
                                                           0011: Test_SE0_NAK
                                                           0100: Test Packet
                                                           0101: Test_Force_enable
                                                           others:reserved */
        unsigned int  ULstChngReq     : 4;  /* bit[5-8]  : ��·״̬�仯����
                                                           ����SS��
                                                           0000�� No Action
                                                           0100: SS.Disabled
                                                           0101: Rx.Detect
                                                           0110: SS.Inactive
                                                           1000: Recovery
                                                           1010: Compliance
                                                           1011: Loopback
                                                           others: reserved
                                                           ����HS/FS/LS��
                                                           1000�� Remote wakeup request
                                                           others��reserved */
        unsigned int  AcceptU1Ena     : 1;  /* bit[9]    : ����U1��ʼ���� */
        unsigned int  InitU1Ena       : 1;  /* bit[10]   : ��ʼ��U1ʹ�ܡ� */
        unsigned int  AcceptU2Ena     : 1;  /* bit[11]   : ����U2ʹ�ܡ� */
        unsigned int  InitU2Ena       : 1;  /* bit[12]   : ��ʼ��U2ʹ�ܡ� */
        unsigned int  reserved_1      : 3;  /* bit[13-15]: ������ */
        unsigned int  CSS             : 1;  /* bit[16]   : Controller Save State */
        unsigned int  CRS             : 1;  /* bit[17]   : Controller Restore State */
        unsigned int  L1HibernationEn : 1;  /* bit[18]   : L1״̬����ʹ�ܡ�
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܡ� */
        unsigned int  KeepConnect     : 1;  /* bit[19]   : �������ӿ��ơ�������Ϊ1����ʹRunStop����Ϊ0��Ҳ��Host��������״̬�� */
        unsigned int  AppL1Res        : 4;  /* bit[20-23]: ��LPM Errata��ʹ��ʱ��
                                                           bit[23]LPM��Ӧ��
                                                           ���LPMCap=0����������������κ���Ӧ��
                                                           ���LPMCap=1��
                                                           0���ɹ��յ�LPM��֮�󣬸��ݷ���FIFO״̬��OUT�˵�״̬����ACK����
                                                           1���ɹ��յ�LPM��֮�󷵻�ACK����
                                                           Bit[22:20]������
                                                           
                                                           ��LPM Errateʹ��ʱ��
                                                           bit[23:20]LPM NYET��Ӧˮ�ߡ�
                                                           ���LPMCap=0����������������κ���Ӧ��
                                                           ���LPMCap=1����������������ʱ����ACK��
                                                           ��1��û��PID��CRC5����
                                                           ��2�����յ���Ч��bLinkState��
                                                           ��3������FIFOΪ�գ���out�˵���У�
                                                           ��4�����յ���BESLС�ڵ���LPM_NYET_thres[3:0]�� */
        unsigned int  HIRD_Thres      : 5;  /* bit[24-28]: HIRDˮ�ߡ�
                                                           ͬʱ����һ��������������ͬʱ������ź�utmi_l1_suspend_n��utmi_sleep_n��Ϊ��Ч��
                                                           ��HIRDֵ���ڻ����HIRD_Thres[3:0]
                                                           ��HIRD_Thres[4]=1
                                                           ������������֮һ��������������ź�utmi_sleep_n��Ϊ��Ч��
                                                           ��HIRDֵС��HIRD_Thres[3:0]
                                                           ��HIRD_Thres[4]=0
                                                           HIRD_Thres[3:0]����
                                                           0000 60us
                                                           0001 135us
                                                           0010 210us
                                                           0011 285us
                                                           0100 360us
                                                           0101 435us
                                                           0110 510us
                                                           0111 585us
                                                           1000 660us
                                                           1001 735us
                                                           1010 810us
                                                           1011 885us
                                                           1100 960us
                                                           1101��1111 Invalid */
        unsigned int  reserved_2      : 1;  /* bit[29]   : ������ */
        unsigned int  CSftRst         : 1;  /* bit[30]   : ��������λ������
                                                           0������λ��
                                                           1����λ�� */
        unsigned int  RunStop         : 1;  /* bit[31]   : Run/Stop��д1����������������д0ֹͣ������������ */
    } reg;
} SOC_USB3OTG_DCTL_UNION;
#endif
#define SOC_USB3OTG_DCTL_TstCtl_START           (1)
#define SOC_USB3OTG_DCTL_TstCtl_END             (4)
#define SOC_USB3OTG_DCTL_ULstChngReq_START      (5)
#define SOC_USB3OTG_DCTL_ULstChngReq_END        (8)
#define SOC_USB3OTG_DCTL_AcceptU1Ena_START      (9)
#define SOC_USB3OTG_DCTL_AcceptU1Ena_END        (9)
#define SOC_USB3OTG_DCTL_InitU1Ena_START        (10)
#define SOC_USB3OTG_DCTL_InitU1Ena_END          (10)
#define SOC_USB3OTG_DCTL_AcceptU2Ena_START      (11)
#define SOC_USB3OTG_DCTL_AcceptU2Ena_END        (11)
#define SOC_USB3OTG_DCTL_InitU2Ena_START        (12)
#define SOC_USB3OTG_DCTL_InitU2Ena_END          (12)
#define SOC_USB3OTG_DCTL_CSS_START              (16)
#define SOC_USB3OTG_DCTL_CSS_END                (16)
#define SOC_USB3OTG_DCTL_CRS_START              (17)
#define SOC_USB3OTG_DCTL_CRS_END                (17)
#define SOC_USB3OTG_DCTL_L1HibernationEn_START  (18)
#define SOC_USB3OTG_DCTL_L1HibernationEn_END    (18)
#define SOC_USB3OTG_DCTL_KeepConnect_START      (19)
#define SOC_USB3OTG_DCTL_KeepConnect_END        (19)
#define SOC_USB3OTG_DCTL_AppL1Res_START         (20)
#define SOC_USB3OTG_DCTL_AppL1Res_END           (23)
#define SOC_USB3OTG_DCTL_HIRD_Thres_START       (24)
#define SOC_USB3OTG_DCTL_HIRD_Thres_END         (28)
#define SOC_USB3OTG_DCTL_CSftRst_START          (30)
#define SOC_USB3OTG_DCTL_CSftRst_END            (30)
#define SOC_USB3OTG_DCTL_RunStop_START          (31)
#define SOC_USB3OTG_DCTL_RunStop_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DEVNTEN_UNION
 �ṹ˵��  : DEVNTEN �Ĵ����ṹ���塣��ַƫ����:0xC708����ֵ:0x0000�����:32
 �Ĵ���˵��: device�¼�ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DisconnEvtEn        : 1;  /* bit[0]    : �Ͽ������¼�ʹ�ܡ� */
        unsigned int  USBRstEn            : 1;  /* bit[1]    : USB��λ�¼�ʹ�ܡ� */
        unsigned int  ConnectDoneEn       : 1;  /* bit[2]    : ��������¼�ʹ�ܡ� */
        unsigned int  ULStsChngEn         : 1;  /* bit[3]    : ��·״̬�仯�����¼�ʹ�ܡ� */
        unsigned int  WkUpEvntEn          : 1;  /* bit[4]    : ��⵽Resume/Remote Wakeup�¼�ʹ�ܡ� */
        unsigned int  HibernationReqEvtEn : 1;  /* bit[5]    : Hibernation�����¼�ʹ�ܡ� */
        unsigned int  U3L2L1SuspEn        : 1;  /* bit[6]    : U3/L2-L1 suspend�¼��� */
        unsigned int  SofEn               : 1;  /* bit[7]    : SOF�¼�ʹ�ܡ� */
        unsigned int  reserved_0          : 1;  /* bit[8]    : ������ */
        unsigned int  ErrticErrEn         : 1;  /* bit[9]    : ��ȷ�������¼�ʹ�ܡ� */
        unsigned int  reserved_1          : 2;  /* bit[10-11]: ������ */
        unsigned int  VndrDevTstRcvedEn   : 1;  /* bit[12]   : �յ�LMP�¼��� */
        unsigned int  reserved_2          : 19; /* bit[13-31]: ������ */
    } reg;
} SOC_USB3OTG_DEVNTEN_UNION;
#endif
#define SOC_USB3OTG_DEVNTEN_DisconnEvtEn_START         (0)
#define SOC_USB3OTG_DEVNTEN_DisconnEvtEn_END           (0)
#define SOC_USB3OTG_DEVNTEN_USBRstEn_START             (1)
#define SOC_USB3OTG_DEVNTEN_USBRstEn_END               (1)
#define SOC_USB3OTG_DEVNTEN_ConnectDoneEn_START        (2)
#define SOC_USB3OTG_DEVNTEN_ConnectDoneEn_END          (2)
#define SOC_USB3OTG_DEVNTEN_ULStsChngEn_START          (3)
#define SOC_USB3OTG_DEVNTEN_ULStsChngEn_END            (3)
#define SOC_USB3OTG_DEVNTEN_WkUpEvntEn_START           (4)
#define SOC_USB3OTG_DEVNTEN_WkUpEvntEn_END             (4)
#define SOC_USB3OTG_DEVNTEN_HibernationReqEvtEn_START  (5)
#define SOC_USB3OTG_DEVNTEN_HibernationReqEvtEn_END    (5)
#define SOC_USB3OTG_DEVNTEN_U3L2L1SuspEn_START         (6)
#define SOC_USB3OTG_DEVNTEN_U3L2L1SuspEn_END           (6)
#define SOC_USB3OTG_DEVNTEN_SofEn_START                (7)
#define SOC_USB3OTG_DEVNTEN_SofEn_END                  (7)
#define SOC_USB3OTG_DEVNTEN_ErrticErrEn_START          (9)
#define SOC_USB3OTG_DEVNTEN_ErrticErrEn_END            (9)
#define SOC_USB3OTG_DEVNTEN_VndrDevTstRcvedEn_START    (12)
#define SOC_USB3OTG_DEVNTEN_VndrDevTstRcvedEn_END      (12)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DSTS_UNION
 �ṹ˵��  : DSTS �Ĵ����ṹ���塣��ַƫ����:0xC70C����ֵ:0x0000�����:32
 �Ĵ���˵��: Device״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ConnectSpd  : 3;  /* bit[0-2]  : �����ٶȡ�
                                                       100��Super Speed��
                                                       000��High Speed��
                                                       001��Full Speed��
                                                       010��LowSpeed��
                                                       011��Full Speed�� */
        unsigned int  SOFFN       : 14; /* bit[3-16] : ֡/΢֡�š� */
        unsigned int  RxFIFOEmpty : 1;  /* bit[17]   : ����FIFO��״ָ̬ʾ�� */
        unsigned int  USBLnkSts   : 4;  /* bit[18-21]: ��·״̬��
                                                       ����SS��
                                                       LTSSM״̬��״̬��
                                                       0000:U0
                                                       0001:U1
                                                       0010:U2
                                                       0011:U3
                                                       0100:SS.Disable
                                                       0101:Rx.Detect
                                                       0110:SS.Inactive
                                                       0111:Poll
                                                       1000:Recovery
                                                       1001:HotReset
                                                       1010:Compliance
                                                       1011:Loopback
                                                       1111:Resume/Reset
                                                       ����HS/FS/LS��
                                                       0000:On state
                                                       0010:Sleep state
                                                       0011:Suspend state
                                                       0100:Disconnect state
                                                       0101:Early suspend state
                                                       1110:Reset */
        unsigned int  DevCtrlHlt  : 1;  /* bit[22]   : ������ֹͣ�� */
        unsigned int  CoreIdle    : 1;  /* bit[23]   : Idle״ָ̬ʾ�� */
        unsigned int  SSS         : 1;  /* bit[24]   : Save״ָ̬ʾ�� */
        unsigned int  RSS         : 1;  /* bit[25]   : Restore״ָ̬ʾ�� */
        unsigned int  reserved_0  : 2;  /* bit[26-27]: ������ */
        unsigned int  SRE         : 1;  /* bit[28]   : Save/Store���� */
        unsigned int  DCNRD       : 1;  /* bit[29]   : ������û��׼���á�
                                                       ָʾ�˳�hibernationû����ɡ� */
        unsigned int  reserved_1  : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_USB3OTG_DSTS_UNION;
#endif
#define SOC_USB3OTG_DSTS_ConnectSpd_START   (0)
#define SOC_USB3OTG_DSTS_ConnectSpd_END     (2)
#define SOC_USB3OTG_DSTS_SOFFN_START        (3)
#define SOC_USB3OTG_DSTS_SOFFN_END          (16)
#define SOC_USB3OTG_DSTS_RxFIFOEmpty_START  (17)
#define SOC_USB3OTG_DSTS_RxFIFOEmpty_END    (17)
#define SOC_USB3OTG_DSTS_USBLnkSts_START    (18)
#define SOC_USB3OTG_DSTS_USBLnkSts_END      (21)
#define SOC_USB3OTG_DSTS_DevCtrlHlt_START   (22)
#define SOC_USB3OTG_DSTS_DevCtrlHlt_END     (22)
#define SOC_USB3OTG_DSTS_CoreIdle_START     (23)
#define SOC_USB3OTG_DSTS_CoreIdle_END       (23)
#define SOC_USB3OTG_DSTS_SSS_START          (24)
#define SOC_USB3OTG_DSTS_SSS_END            (24)
#define SOC_USB3OTG_DSTS_RSS_START          (25)
#define SOC_USB3OTG_DSTS_RSS_END            (25)
#define SOC_USB3OTG_DSTS_SRE_START          (28)
#define SOC_USB3OTG_DSTS_SRE_END            (28)
#define SOC_USB3OTG_DSTS_DCNRD_START        (29)
#define SOC_USB3OTG_DSTS_DCNRD_END          (29)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DGCMDPAR_UNION
 �ṹ˵��  : DGCMDPAR �Ĵ����ṹ���塣��ַƫ����:0xC710����ֵ:0x0000�����:32
 �Ĵ���˵��: һ����������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  parameter : 32; /* bit[0-31]: ��������� */
    } reg;
} SOC_USB3OTG_DGCMDPAR_UNION;
#endif
#define SOC_USB3OTG_DGCMDPAR_parameter_START  (0)
#define SOC_USB3OTG_DGCMDPAR_parameter_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DGCMD_UNION
 �ṹ˵��  : DGCMD �Ĵ����ṹ���塣��ַƫ����:0xC714����ֵ:0x0000�����:32
 �Ĵ���˵��: һ��������ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CmdTyp   : 8;  /* bit[0-7]  : �������͡�
                                                    02h���������ڲ���
                                                    04h�����ñ�ǩbuffer��ַ��32λ
                                                    05h�����ñ�ǩbuffer��ַ��32λ
                                                    07h������device notification
                                                    08h��ѡ���FIFO Flush����
                                                    0Ah�����е�FIFO Flush����
                                                    0Ch�����ö˵�NRDY
                                                    10h��Soc���߻��ز��� */
        unsigned int  CmdIOC   : 1;  /* bit[8]    : ��������ж�ʹ�ܡ�����Ϊ1�����������֮�������������ж��¼���
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  reserved_0: 1;  /* bit[9]    : ������ */
        unsigned int  CmdAct   : 1;  /* bit[10]   : ����
                                                    ���д1����������ʼִ�����������ɺ��bit�Զ����㡣 */
        unsigned int  reserved_1: 4;  /* bit[11-14]: ������ */
        unsigned int  CmdSts   : 1;  /* bit[15]   : ����״̬��
                                                    0������ɹ���
                                                    1��������� */
        unsigned int  reserved_2: 16; /* bit[16-31]: ������ */
    } reg;
} SOC_USB3OTG_DGCMD_UNION;
#endif
#define SOC_USB3OTG_DGCMD_CmdTyp_START    (0)
#define SOC_USB3OTG_DGCMD_CmdTyp_END      (7)
#define SOC_USB3OTG_DGCMD_CmdIOC_START    (8)
#define SOC_USB3OTG_DGCMD_CmdIOC_END      (8)
#define SOC_USB3OTG_DGCMD_CmdAct_START    (10)
#define SOC_USB3OTG_DGCMD_CmdAct_END      (10)
#define SOC_USB3OTG_DGCMD_CmdSts_START    (15)
#define SOC_USB3OTG_DGCMD_CmdSts_END      (15)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DALEPENA_UNION
 �ṹ˵��  : DALEPENA �Ĵ����ṹ���塣��ַƫ����:0xC720����ֵ:0x0000�����:32
 �Ĵ���˵��: �˵㼤��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  USBActEp : 32; /* bit[0-31]: ÿbit��Ӧһ���˵㡣
                                                   Bit[0]:EP0-OUT
                                                   bit[1]:EP0_IN
                                                   bit[2]:EP1-OUT
                                                   bit[3]:EP2-IN
                                                   ����
                                                   bit[31]:EP15-IN
                                                   0���˵�û�м��
                                                   1���˵㼤� */
    } reg;
} SOC_USB3OTG_DALEPENA_UNION;
#endif
#define SOC_USB3OTG_DALEPENA_USBActEp_START  (0)
#define SOC_USB3OTG_DALEPENA_USBActEp_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DEPCMDPAR2m_UNION
 �ṹ˵��  : DEPCMDPAR2m �Ĵ����ṹ���塣��ַƫ����:0xC800+m*0x10����ֵ:0x0000�����:32
 �Ĵ���˵��: �˵�m��������Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  parameter2 : 32; /* bit[0-31]: �����Ĵ����� */
    } reg;
} SOC_USB3OTG_DEPCMDPAR2m_UNION;
#endif
#define SOC_USB3OTG_DEPCMDPAR2m_parameter2_START  (0)
#define SOC_USB3OTG_DEPCMDPAR2m_parameter2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DEPCMDPAR1m_UNION
 �ṹ˵��  : DEPCMDPAR1m �Ĵ����ṹ���塣��ַƫ����:0xC804+m*0x10����ֵ:0x0000�����:32
 �Ĵ���˵��: �˵�m��������Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  parameter1 : 32; /* bit[0-31]: �����Ĵ����� */
    } reg;
} SOC_USB3OTG_DEPCMDPAR1m_UNION;
#endif
#define SOC_USB3OTG_DEPCMDPAR1m_parameter1_START  (0)
#define SOC_USB3OTG_DEPCMDPAR1m_parameter1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DEPCMDPAR0m_UNION
 �ṹ˵��  : DEPCMDPAR0m �Ĵ����ṹ���塣��ַƫ����:0xC808+m*0x10����ֵ:0x0000�����:32
 �Ĵ���˵��: �˵�m��������Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  parameter0 : 32; /* bit[0-31]: �����Ĵ����� */
    } reg;
} SOC_USB3OTG_DEPCMDPAR0m_UNION;
#endif
#define SOC_USB3OTG_DEPCMDPAR0m_parameter0_START  (0)
#define SOC_USB3OTG_DEPCMDPAR0m_parameter0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_DEPCMDm_UNION
 �ṹ˵��  : DEPCMDm �Ĵ����ṹ���塣��ַƫ����:0xC80C+m*0x10����ֵ:0x0000�����:32
 �Ĵ���˵��: �˵�m����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CmdTyp        : 4;  /* bit[0-3]  : �������͡�������������������ɵĲ������͡�
                                                         0001���˵����ã�
                                                         0010: ����Դ���ã�
                                                         0011: ��ȡ�˵�״̬��
                                                         0100: ����STALL��
                                                         0101: ���STALL��
                                                         0110: �������䣻
                                                         0111: ���´��䣻
                                                         1000: �������䣻
                                                         1001: �����µ����ã�
                                                         others��reserved�� */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : ������ */
        unsigned int  CmdIOC        : 1;  /* bit[8]    : ��������ж�ʹ�ܡ� */
        unsigned int  reserved_1    : 1;  /* bit[9]    : ������ */
        unsigned int  CmdAct        : 1;  /* bit[10]   : ����
                                                         ���д1����������ʼִ�����������ɺ��bit�Զ����㡣 */
        unsigned int  HiPri_ForceRM : 1;  /* bit[11]   : HighPriority/ForceRM�� */
        unsigned int  CmdStatus     : 4;  /* bit[12-15]: �������״̬�� */
        unsigned int  CommandParam  : 16; /* bit[16-31]: ����д����ʱ������Ϊ���������
                                                         ���ڷ�ISO�˵��Start Transfer���stream ID��
                                                         ����ISO�˵��Start Transfer���StartMicroFrameNum��
                                                         ����Update Transfer��End Transfer��StartNew Configuration���[22:16]ΪTransfer Resource Index
                                                         
                                                         ���ڶ�����������Ϊ�¼������� */
    } reg;
} SOC_USB3OTG_DEPCMDm_UNION;
#endif
#define SOC_USB3OTG_DEPCMDm_CmdTyp_START         (0)
#define SOC_USB3OTG_DEPCMDm_CmdTyp_END           (3)
#define SOC_USB3OTG_DEPCMDm_CmdIOC_START         (8)
#define SOC_USB3OTG_DEPCMDm_CmdIOC_END           (8)
#define SOC_USB3OTG_DEPCMDm_CmdAct_START         (10)
#define SOC_USB3OTG_DEPCMDm_CmdAct_END           (10)
#define SOC_USB3OTG_DEPCMDm_HiPri_ForceRM_START  (11)
#define SOC_USB3OTG_DEPCMDm_HiPri_ForceRM_END    (11)
#define SOC_USB3OTG_DEPCMDm_CmdStatus_START      (12)
#define SOC_USB3OTG_DEPCMDm_CmdStatus_END        (15)
#define SOC_USB3OTG_DEPCMDm_CommandParam_START   (16)
#define SOC_USB3OTG_DEPCMDm_CommandParam_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_OCFG_UNION
 �ṹ˵��  : OCFG �Ĵ����ṹ���塣��ַƫ����:0xCC00����ֵ:0x0000�����:32
 �Ĵ���˵��: OTG���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SRPCap          : 1;  /* bit[0]   : SRPʹ�ܡ�
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  HNPCap          : 1;  /* bit[1]   : RSP/HNPʹ�ܡ�
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  OTGVersion      : 1;  /* bit[2]   : ��������Ϊ0�� */
        unsigned int  OTGSftRstMsk    : 1;  /* bit[3]   : OTG��λ���μĴ�����
                                                          0��The xHCI-based USBCMD.HCRST and DCTL.CSftRst will reset the OTG logic of the core
                                                          1: The xHCI-based USBCMD.HCRST and DCTL.CSftRst will be masked form the OTG logic of the core��
                                                          ��GCTL.PrtCapDir=2'b11ʱ����bit��������Ϊ1����������Ϊ0�� */
        unsigned int  OTGHibDisMsk    : 1;  /* bit[4]   : ���߹���������OTG�¼���
                                                          0����Run/Stop����Ϊ1֮ǰ��������OTG�¼���
                                                          1�������Ρ�
                                                          �������ܸ�bit��������Ϊ0�� */
        unsigned int  DisPrtPwrCutOff : 1;  /* bit[5]   : ȥʹ�ܶ˿�VBUS�Զ��ضϡ�
                                                          0�����A_WAIT_BCON��ʱ���������Զ��ض�VBUS��
                                                          1�����Զ��ض�VBUS�� */
        unsigned int  reserved        : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_USB3OTG_OCFG_UNION;
#endif
#define SOC_USB3OTG_OCFG_SRPCap_START           (0)
#define SOC_USB3OTG_OCFG_SRPCap_END             (0)
#define SOC_USB3OTG_OCFG_HNPCap_START           (1)
#define SOC_USB3OTG_OCFG_HNPCap_END             (1)
#define SOC_USB3OTG_OCFG_OTGVersion_START       (2)
#define SOC_USB3OTG_OCFG_OTGVersion_END         (2)
#define SOC_USB3OTG_OCFG_OTGSftRstMsk_START     (3)
#define SOC_USB3OTG_OCFG_OTGSftRstMsk_END       (3)
#define SOC_USB3OTG_OCFG_OTGHibDisMsk_START     (4)
#define SOC_USB3OTG_OCFG_OTGHibDisMsk_END       (4)
#define SOC_USB3OTG_OCFG_DisPrtPwrCutOff_START  (5)
#define SOC_USB3OTG_OCFG_DisPrtPwrCutOff_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_OCTL_UNION
 �ṹ˵��  : OCTL �Ĵ����ṹ���塣��ַƫ����:0xCC04����ֵ:0x0000�����:32
 �Ĵ���˵��: OTG���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HstSetHNPEn    : 1;  /* bit[0]   : host RSP/HNPʹ�ܡ�
                                                         0����ʹ�ܣ�
                                                         1��ʹ�ܡ� */
        unsigned int  DevSetHNPEn    : 1;  /* bit[1]   : device RSP/HNPʹ�ܡ�
                                                         0����ʹ�ܣ�
                                                         1��ʹ�ܡ� */
        unsigned int  TermSelDLPulse : 1;  /* bit[2]   : ��SRP�����У����ø�bit���������ϲ������塣
                                                         0����utmi_txvalid�������壻
                                                         1����utmi_termsel�������塣 */
        unsigned int  SesReq         : 1;  /* bit[3]   : �Ự����
                                                         0��������
                                                         1�������� */
        unsigned int  HNPReq         : 1;  /* bit[4]   : HNP����
                                                         0��������
                                                         1�������� */
        unsigned int  PrtPwrCtl      : 1;  /* bit[5]   : �˿ڵ�Դ���ơ�
                                                         ��ΪA-deviceʱ�����ø�bit����VBUS��
                                                         0��VBUS��ʹ�ܣ�
                                                         1��VBUSʹ�ܡ� */
        unsigned int  PeriMode       : 1;  /* bit[6]   : ģʽ���á�
                                                         0��Hostģʽ��
                                                         1��Deviceģʽ�� */
        unsigned int  OTG3_GOERR     : 1;  /* bit[7]   : ���ø�bit��LTSSM״̬����ת������״̬��������ɸ�bit�Զ����㡣��TRSP_ACK_ERR, TRSP_CNF_ERR����TRSP_WRST_ERR��ʱ����������������ø�bitΪ1�� */
        unsigned int  reserved       : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_USB3OTG_OCTL_UNION;
#endif
#define SOC_USB3OTG_OCTL_HstSetHNPEn_START     (0)
#define SOC_USB3OTG_OCTL_HstSetHNPEn_END       (0)
#define SOC_USB3OTG_OCTL_DevSetHNPEn_START     (1)
#define SOC_USB3OTG_OCTL_DevSetHNPEn_END       (1)
#define SOC_USB3OTG_OCTL_TermSelDLPulse_START  (2)
#define SOC_USB3OTG_OCTL_TermSelDLPulse_END    (2)
#define SOC_USB3OTG_OCTL_SesReq_START          (3)
#define SOC_USB3OTG_OCTL_SesReq_END            (3)
#define SOC_USB3OTG_OCTL_HNPReq_START          (4)
#define SOC_USB3OTG_OCTL_HNPReq_END            (4)
#define SOC_USB3OTG_OCTL_PrtPwrCtl_START       (5)
#define SOC_USB3OTG_OCTL_PrtPwrCtl_END         (5)
#define SOC_USB3OTG_OCTL_PeriMode_START        (6)
#define SOC_USB3OTG_OCTL_PeriMode_END          (6)
#define SOC_USB3OTG_OCTL_OTG3_GOERR_START      (7)
#define SOC_USB3OTG_OCTL_OTG3_GOERR_END        (7)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_OEVNT_UNION
 �ṹ˵��  : OEVNT �Ĵ����ṹ���塣��ַƫ����:0xCC08����ֵ:0x0000�����:32
 �Ĵ���˵��: OTG�¼��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  OEVNTError            : 1;  /* bit[0]    : OTG�¼����� */
        unsigned int  SesReqSts             : 1;  /* bit[1]    : �Ự����״̬�� */
        unsigned int  HstNegStss            : 1;  /* bit[2]    : HNP״̬��
                                                                 0��HNPʧ�ܣ�
                                                                 1��HNP�ɹ��� */
        unsigned int  BSesVld               : 1;  /* bit[3]    : B-Session״̬��
                                                                 0����Ч��
                                                                 1����Ч�� */
        unsigned int  reserved_0            : 4;  /* bit[4-7]  : ������ */
        unsigned int  OTGBVbsChg            : 1;  /* bit[8]    : ��ǰģʽΪB-deviceģʽ��VBUS״̬�仯�¼��� */
        unsigned int  OTGBSrpChg            : 1;  /* bit[9]    : ��ǰģʽΪB-deviceģʽ��SRP״̬�仯�¼��� */
        unsigned int  OTGBHnpChg            : 1;  /* bit[10]   : ��ǰģʽΪB-deviceģʽ��HNP״̬�仯�¼��� */
        unsigned int  OTGBDevBHostEndEvnt   : 1;  /* bit[11]   : ��ǰģʽΪB-deviceģʽ��B-device���host��ɫ�¼��� */
        unsigned int  reserved_1            : 4;  /* bit[12-15]: ������ */
        unsigned int  OTGADevSessEndDetEvnt : 1;  /* bit[16]   : �Ự�����¼��� */
        unsigned int  OTGADevEvtInfo        : 1;  /* bit[17]   : ��⵽SRP�¼��� */
        unsigned int  OTGADevHNPChngEvnt    : 1;  /* bit[18]   : A-device HNP�¼�������OTG2.0��Ч�� */
        unsigned int  OTGADevHostEvnt       : 1;  /* bit[19]   : A-device����host��ɫ�¼��� */
        unsigned int  OTGADevBHostEndEvnt   : 1;  /* bit[20]   : ��ǰģʽΪA-deviceģʽ��B-device���host��ɫ�¼��� */
        unsigned int  OTGADevIdleEvnt       : 1;  /* bit[21]   : A-device����A-IDLE״̬�¼��� */
        unsigned int  HRRInitNotifEvnt      : 1;  /* bit[22]   : ��ΪA-host����B-host���������յ���initialλ��Host Role Request Device Notification TPʱ����bit��λ�� */
        unsigned int  HRRConfNotifEvnt      : 1;  /* bit[23]   : Host Role Requestȷ��֪ͨ�¼���
                                                                 ��ΪA-host����B-host���������յ���Confrimλ��Host Role Request Device Notification TPʱ����bit��λ�� */
        unsigned int  OTGConIDStsChngEvnt   : 1;  /* bit[24]   : ID״̬�仯�¼��� */
        unsigned int  OTGHibEntryEvnt       : 1;  /* bit[25]   : ���붬���¼��� */
        unsigned int  OTGDevRunStpSetEcnt   : 1;  /* bit[26]   : Device Run/Stop�����¼��� */
        unsigned int  OTGXhciRunStpSetEvnt  : 1;  /* bit[27]   : Host Run/Stop�����¼��� */
        unsigned int  reserved_2            : 3;  /* bit[28-30]: ������ */
        unsigned int  DeviceMode            : 1;  /* bit[31]   : ��ǰģʽ��
                                                                 0��A-device��
                                                                 1��B-device�� */
    } reg;
} SOC_USB3OTG_OEVNT_UNION;
#endif
#define SOC_USB3OTG_OEVNT_OEVNTError_START             (0)
#define SOC_USB3OTG_OEVNT_OEVNTError_END               (0)
#define SOC_USB3OTG_OEVNT_SesReqSts_START              (1)
#define SOC_USB3OTG_OEVNT_SesReqSts_END                (1)
#define SOC_USB3OTG_OEVNT_HstNegStss_START             (2)
#define SOC_USB3OTG_OEVNT_HstNegStss_END               (2)
#define SOC_USB3OTG_OEVNT_BSesVld_START                (3)
#define SOC_USB3OTG_OEVNT_BSesVld_END                  (3)
#define SOC_USB3OTG_OEVNT_OTGBVbsChg_START             (8)
#define SOC_USB3OTG_OEVNT_OTGBVbsChg_END               (8)
#define SOC_USB3OTG_OEVNT_OTGBSrpChg_START             (9)
#define SOC_USB3OTG_OEVNT_OTGBSrpChg_END               (9)
#define SOC_USB3OTG_OEVNT_OTGBHnpChg_START             (10)
#define SOC_USB3OTG_OEVNT_OTGBHnpChg_END               (10)
#define SOC_USB3OTG_OEVNT_OTGBDevBHostEndEvnt_START    (11)
#define SOC_USB3OTG_OEVNT_OTGBDevBHostEndEvnt_END      (11)
#define SOC_USB3OTG_OEVNT_OTGADevSessEndDetEvnt_START  (16)
#define SOC_USB3OTG_OEVNT_OTGADevSessEndDetEvnt_END    (16)
#define SOC_USB3OTG_OEVNT_OTGADevEvtInfo_START         (17)
#define SOC_USB3OTG_OEVNT_OTGADevEvtInfo_END           (17)
#define SOC_USB3OTG_OEVNT_OTGADevHNPChngEvnt_START     (18)
#define SOC_USB3OTG_OEVNT_OTGADevHNPChngEvnt_END       (18)
#define SOC_USB3OTG_OEVNT_OTGADevHostEvnt_START        (19)
#define SOC_USB3OTG_OEVNT_OTGADevHostEvnt_END          (19)
#define SOC_USB3OTG_OEVNT_OTGADevBHostEndEvnt_START    (20)
#define SOC_USB3OTG_OEVNT_OTGADevBHostEndEvnt_END      (20)
#define SOC_USB3OTG_OEVNT_OTGADevIdleEvnt_START        (21)
#define SOC_USB3OTG_OEVNT_OTGADevIdleEvnt_END          (21)
#define SOC_USB3OTG_OEVNT_HRRInitNotifEvnt_START       (22)
#define SOC_USB3OTG_OEVNT_HRRInitNotifEvnt_END         (22)
#define SOC_USB3OTG_OEVNT_HRRConfNotifEvnt_START       (23)
#define SOC_USB3OTG_OEVNT_HRRConfNotifEvnt_END         (23)
#define SOC_USB3OTG_OEVNT_OTGConIDStsChngEvnt_START    (24)
#define SOC_USB3OTG_OEVNT_OTGConIDStsChngEvnt_END      (24)
#define SOC_USB3OTG_OEVNT_OTGHibEntryEvnt_START        (25)
#define SOC_USB3OTG_OEVNT_OTGHibEntryEvnt_END          (25)
#define SOC_USB3OTG_OEVNT_OTGDevRunStpSetEcnt_START    (26)
#define SOC_USB3OTG_OEVNT_OTGDevRunStpSetEcnt_END      (26)
#define SOC_USB3OTG_OEVNT_OTGXhciRunStpSetEvnt_START   (27)
#define SOC_USB3OTG_OEVNT_OTGXhciRunStpSetEvnt_END     (27)
#define SOC_USB3OTG_OEVNT_DeviceMode_START             (31)
#define SOC_USB3OTG_OEVNT_DeviceMode_END               (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_OEVNTEN_UNION
 �ṹ˵��  : OEVNTEN �Ĵ����ṹ���塣��ַƫ����:0xCC0C����ֵ:0x0000�����:32
 �Ĵ���˵��: OTG�¼�ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0              : 8;  /* bit[0-7]  : ������ */
        unsigned int  OTGBVbsChgEn            : 1;  /* bit[8]    : OTGBVbsChg�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  OTGBSrpChgEn            : 1;  /* bit[9]    : OTGBSrpChg�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  OTGBHnpChgEn            : 1;  /* bit[10]   : OTGBHnpChg�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  OTGBDevBHostEndEvntEn   : 1;  /* bit[11]   : OTGBDevBHostEndEvnt�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  reserved_1              : 4;  /* bit[12-15]: ������ */
        unsigned int  OTGADevSessEndDetEvntEn : 1;  /* bit[16]   : OTGADevSessEnd�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  OTGADevEvtInfoEn        : 1;  /* bit[17]   : OTGADevEvtInfo�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  OTGADevHNPChngEvntEn    : 1;  /* bit[18]   : OTGADevHNPChngEvnt�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  OTGADevHostEvntEn       : 1;  /* bit[19]   : OTGADevHostEvnt�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  OTGADevBHostEndEvntEn   : 1;  /* bit[20]   : OTGADevBHostEndEvnt�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  OTGADevIdleEvntEn       : 1;  /* bit[21]   : OTGADevIdleEvnt�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  HRRInitNotifEvntEn      : 1;  /* bit[22]   : HRRInitNotifEvnt�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  HRRConfNotifEvntEn      : 1;  /* bit[23]   : HRRConfNotifEvnt�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  OTGConIDStsChngEvntEn   : 1;  /* bit[24]   : OTGConIDStsChngEvnt�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  OTGHibEntryEvntEn       : 1;  /* bit[25]   : OTGHibEntryEvnt�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  OTGDevRunStpSetEcntEn   : 1;  /* bit[26]   : OTGDevRunStpSetEcnt�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  OTGXhciRunStpSetEvntEn  : 1;  /* bit[27]   : OTGXhciRunStpSetEvnt�¼�ʹ�ܡ�
                                                                   0����ʹ�ܣ�
                                                                   1��ʹ�ܡ� */
        unsigned int  reserved_2              : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_USB3OTG_OEVNTEN_UNION;
#endif
#define SOC_USB3OTG_OEVNTEN_OTGBVbsChgEn_START             (8)
#define SOC_USB3OTG_OEVNTEN_OTGBVbsChgEn_END               (8)
#define SOC_USB3OTG_OEVNTEN_OTGBSrpChgEn_START             (9)
#define SOC_USB3OTG_OEVNTEN_OTGBSrpChgEn_END               (9)
#define SOC_USB3OTG_OEVNTEN_OTGBHnpChgEn_START             (10)
#define SOC_USB3OTG_OEVNTEN_OTGBHnpChgEn_END               (10)
#define SOC_USB3OTG_OEVNTEN_OTGBDevBHostEndEvntEn_START    (11)
#define SOC_USB3OTG_OEVNTEN_OTGBDevBHostEndEvntEn_END      (11)
#define SOC_USB3OTG_OEVNTEN_OTGADevSessEndDetEvntEn_START  (16)
#define SOC_USB3OTG_OEVNTEN_OTGADevSessEndDetEvntEn_END    (16)
#define SOC_USB3OTG_OEVNTEN_OTGADevEvtInfoEn_START         (17)
#define SOC_USB3OTG_OEVNTEN_OTGADevEvtInfoEn_END           (17)
#define SOC_USB3OTG_OEVNTEN_OTGADevHNPChngEvntEn_START     (18)
#define SOC_USB3OTG_OEVNTEN_OTGADevHNPChngEvntEn_END       (18)
#define SOC_USB3OTG_OEVNTEN_OTGADevHostEvntEn_START        (19)
#define SOC_USB3OTG_OEVNTEN_OTGADevHostEvntEn_END          (19)
#define SOC_USB3OTG_OEVNTEN_OTGADevBHostEndEvntEn_START    (20)
#define SOC_USB3OTG_OEVNTEN_OTGADevBHostEndEvntEn_END      (20)
#define SOC_USB3OTG_OEVNTEN_OTGADevIdleEvntEn_START        (21)
#define SOC_USB3OTG_OEVNTEN_OTGADevIdleEvntEn_END          (21)
#define SOC_USB3OTG_OEVNTEN_HRRInitNotifEvntEn_START       (22)
#define SOC_USB3OTG_OEVNTEN_HRRInitNotifEvntEn_END         (22)
#define SOC_USB3OTG_OEVNTEN_HRRConfNotifEvntEn_START       (23)
#define SOC_USB3OTG_OEVNTEN_HRRConfNotifEvntEn_END         (23)
#define SOC_USB3OTG_OEVNTEN_OTGConIDStsChngEvntEn_START    (24)
#define SOC_USB3OTG_OEVNTEN_OTGConIDStsChngEvntEn_END      (24)
#define SOC_USB3OTG_OEVNTEN_OTGHibEntryEvntEn_START        (25)
#define SOC_USB3OTG_OEVNTEN_OTGHibEntryEvntEn_END          (25)
#define SOC_USB3OTG_OEVNTEN_OTGDevRunStpSetEcntEn_START    (26)
#define SOC_USB3OTG_OEVNTEN_OTGDevRunStpSetEcntEn_END      (26)
#define SOC_USB3OTG_OEVNTEN_OTGXhciRunStpSetEvntEn_START   (27)
#define SOC_USB3OTG_OEVNTEN_OTGXhciRunStpSetEvntEn_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_OSTS_UNION
 �ṹ˵��  : OSTS �Ĵ����ṹ���塣��ַƫ����:0xCC10����ֵ:0x0000�����:32
 �Ĵ���˵��: OTG״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ConIDSts        : 1;  /* bit[0]    : ID״̬��
                                                           0��A-device��
                                                           1��B-device�� */
        unsigned int  VbusVld         : 1;  /* bit[1]    : VBUS��Ч״̬��
                                                           0����Ч��
                                                           1����Ч�� */
        unsigned int  BSesVld         : 1;  /* bit[2]    : B�Ự��Ч״̬��
                                                           0����Ч��
                                                           1����Ч�� */
        unsigned int  xHCIPrtPower    : 1;  /* bit[3]    : xHCI PORTSC.PP״̬�� */
        unsigned int  PeripheralState : 1;  /* bit[4]    : ģʽ״̬��
                                                           0��Host��
                                                           1��Peripheral�� */
        unsigned int  reserved_0      : 3;  /* bit[5-7]  : ������ */
        unsigned int  OTG2State       : 4;  /* bit[8-11] : OTG 2.0״̬��
                                                           0000��A_IDLE��
                                                           0001: A_WAIT_VRISE��
                                                           0010: A_WAIT_BCON��
                                                           0011: A_WAIT_VFALL��
                                                           0100: A_VBUS_ERR��
                                                           0101: A_HOST��
                                                           0110: A_SUSPEND��
                                                           1111: A_PERIPHERAL��
                                                           0111: A_WAIT_PPWR��
                                                           1000: B_IDLE��
                                                           1001: B_SRP_INIT��
                                                           1010: B_PERIPHERAL��
                                                           1011: B_WAIT_ACON��
                                                           1100: b_HOST��
                                                           1101: A_WAIT_SWITCH��
                                                           1110: B_WAIT_SWITCH��
                                                           others��reserved�� */
        unsigned int  HstRunStp       : 1;  /* bit[12]   : Host Run/Stop״̬��
                                                           0��Run/Stop����Ϊ0��
                                                           1��Run/Stop����Ϊ1�� */
        unsigned int  DevRunStp       : 1;  /* bit[13]   : Device Run/Stop״̬��
                                                           0��Run/Stop����Ϊ0��
                                                           1��Run/Stop����Ϊ1�� */
        unsigned int  reserved_1      : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_USB3OTG_OSTS_UNION;
#endif
#define SOC_USB3OTG_OSTS_ConIDSts_START         (0)
#define SOC_USB3OTG_OSTS_ConIDSts_END           (0)
#define SOC_USB3OTG_OSTS_VbusVld_START          (1)
#define SOC_USB3OTG_OSTS_VbusVld_END            (1)
#define SOC_USB3OTG_OSTS_BSesVld_START          (2)
#define SOC_USB3OTG_OSTS_BSesVld_END            (2)
#define SOC_USB3OTG_OSTS_xHCIPrtPower_START     (3)
#define SOC_USB3OTG_OSTS_xHCIPrtPower_END       (3)
#define SOC_USB3OTG_OSTS_PeripheralState_START  (4)
#define SOC_USB3OTG_OSTS_PeripheralState_END    (4)
#define SOC_USB3OTG_OSTS_OTG2State_START        (8)
#define SOC_USB3OTG_OSTS_OTG2State_END          (11)
#define SOC_USB3OTG_OSTS_HstRunStp_START        (12)
#define SOC_USB3OTG_OSTS_HstRunStp_END          (12)
#define SOC_USB3OTG_OSTS_DevRunStp_START        (13)
#define SOC_USB3OTG_OSTS_DevRunStp_END          (13)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_ADPCFG_UNION
 �ṹ˵��  : ADPCFG �Ĵ����ṹ���塣��ַƫ����:0xCC20����ֵ:0x0000�����:32
 �Ĵ���˵��: ADP���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved   : 26; /* bit[0-25] : ������ */
        unsigned int  PrbDschg   : 2;  /* bit[26-27]: Probe�ŵ�ʱ�䡣
                                                      00��4ms
                                                      01��8ms
                                                      10��16ms
                                                      11��32ms */
        unsigned int  ProbeDelta : 2;  /* bit[28-29]: Probe Delta���ã���32KHzʱ������Ϊ��λ��
                                                      00��1��ʱ������
                                                      01��2��ʱ������
                                                      10��3��ʱ������
                                                      11��4��ʱ������ */
        unsigned int  PrbPer     : 2;  /* bit[30-31]: Probe�������á�
                                                      00��0.775��
                                                      01��1.55��
                                                      10��2.275��
                                                      11��reserved */
    } reg;
} SOC_USB3OTG_ADPCFG_UNION;
#endif
#define SOC_USB3OTG_ADPCFG_PrbDschg_START    (26)
#define SOC_USB3OTG_ADPCFG_PrbDschg_END      (27)
#define SOC_USB3OTG_ADPCFG_ProbeDelta_START  (28)
#define SOC_USB3OTG_ADPCFG_ProbeDelta_END    (29)
#define SOC_USB3OTG_ADPCFG_PrbPer_START      (30)
#define SOC_USB3OTG_ADPCFG_PrbPer_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_ADPCTL_UNION
 �ṹ˵��  : ADPCTL �Ĵ����ṹ���塣��ַƫ����:0xCC24����ֵ:0x0000�����:32
 �Ĵ���˵��: ADP���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 24; /* bit[0-23] : ������ */
        unsigned int  WB       : 1;  /* bit[24]   : дbusy״̬��
                                                    ����ڸ�bitΪ0������²��ܶ�дADPCFG��ADPCTL�Ĵ����� */
        unsigned int  ADPRes   : 1;  /* bit[25]   : ADP��λ������Ϊ1��λADP����������λ��ɸ�bit�Զ����㡣 */
        unsigned int  ADPEn    : 1;  /* bit[26]   : ADPʹ�ܡ�
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  EnaSns   : 1;  /* bit[27]   : Senseʹ�ܡ�
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  EnaPrb   : 1;  /* bit[28]   : Probeʹ�ܡ�
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  reserved_1: 3;  /* bit[29-31]: ������ */
    } reg;
} SOC_USB3OTG_ADPCTL_UNION;
#endif
#define SOC_USB3OTG_ADPCTL_WB_START        (24)
#define SOC_USB3OTG_ADPCTL_WB_END          (24)
#define SOC_USB3OTG_ADPCTL_ADPRes_START    (25)
#define SOC_USB3OTG_ADPCTL_ADPRes_END      (25)
#define SOC_USB3OTG_ADPCTL_ADPEn_START     (26)
#define SOC_USB3OTG_ADPCTL_ADPEn_END       (26)
#define SOC_USB3OTG_ADPCTL_EnaSns_START    (27)
#define SOC_USB3OTG_ADPCTL_EnaSns_END      (27)
#define SOC_USB3OTG_ADPCTL_EnaPrb_START    (28)
#define SOC_USB3OTG_ADPCTL_EnaPrb_END      (28)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_ADPEVNT_UNION
 �ṹ˵��  : ADPEVNT �Ĵ����ṹ���塣��ַƫ����:0xCC28����ֵ:0x0000�����:32
 �Ĵ���˵��: ADP�¼��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RTIM            : 16; /* bit[0-15] : RAMPʱ�䡣 */
        unsigned int  reserved_0      : 9;  /* bit[16-24]: ������ */
        unsigned int  ADPRstCmpltEvnt : 1;  /* bit[25]   : ADP��λ����¼��� */
        unsigned int  ADPTimeoutEvnt  : 1;  /* bit[26]   : ADP��ʱ�¼��� */
        unsigned int  ADPSnsEvnt      : 1;  /* bit[27]   : ADP Sense�¼��� */
        unsigned int  ADPEVTInfo      : 1;  /* bit[28]   : ADP Probe�¼��� */
        unsigned int  reserved_1      : 3;  /* bit[29-31]: ������ */
    } reg;
} SOC_USB3OTG_ADPEVNT_UNION;
#endif
#define SOC_USB3OTG_ADPEVNT_RTIM_START             (0)
#define SOC_USB3OTG_ADPEVNT_RTIM_END               (15)
#define SOC_USB3OTG_ADPEVNT_ADPRstCmpltEvnt_START  (25)
#define SOC_USB3OTG_ADPEVNT_ADPRstCmpltEvnt_END    (25)
#define SOC_USB3OTG_ADPEVNT_ADPTimeoutEvnt_START   (26)
#define SOC_USB3OTG_ADPEVNT_ADPTimeoutEvnt_END     (26)
#define SOC_USB3OTG_ADPEVNT_ADPSnsEvnt_START       (27)
#define SOC_USB3OTG_ADPEVNT_ADPSnsEvnt_END         (27)
#define SOC_USB3OTG_ADPEVNT_ADPEVTInfo_START       (28)
#define SOC_USB3OTG_ADPEVNT_ADPEVTInfo_END         (28)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_ADPEVNTEN_UNION
 �ṹ˵��  : ADPEVNTEN �Ĵ����ṹ���塣��ַƫ����:0xCC28����ֵ:0x0000�����:32
 �Ĵ���˵��: ADP�¼��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 25; /* bit[0-24] : ������ */
        unsigned int  ADPRstCmpltEvntEn : 1;  /* bit[25]   : ADP��λ����¼�ʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  ADPTimeoutEvntEn  : 1;  /* bit[26]   : ADP��ʱ�¼�ʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  ADPSnsEvntEn      : 1;  /* bit[27]   : ADP Sense�¼�ʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  ADPEVTInfoEn      : 1;  /* bit[28]   : ADP Probe�¼�ʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  reserved_1        : 3;  /* bit[29-31]: ������ */
    } reg;
} SOC_USB3OTG_ADPEVNTEN_UNION;
#endif
#define SOC_USB3OTG_ADPEVNTEN_ADPRstCmpltEvntEn_START  (25)
#define SOC_USB3OTG_ADPEVNTEN_ADPRstCmpltEvntEn_END    (25)
#define SOC_USB3OTG_ADPEVNTEN_ADPTimeoutEvntEn_START   (26)
#define SOC_USB3OTG_ADPEVNTEN_ADPTimeoutEvntEn_END     (26)
#define SOC_USB3OTG_ADPEVNTEN_ADPSnsEvntEn_START       (27)
#define SOC_USB3OTG_ADPEVNTEN_ADPSnsEvntEn_END         (27)
#define SOC_USB3OTG_ADPEVNTEN_ADPEVTInfoEn_START       (28)
#define SOC_USB3OTG_ADPEVNTEN_ADPEVTInfoEn_END         (28)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BCFG_UNION
 �ṹ˵��  : BCFG �Ĵ����ṹ���塣��ַƫ����:0xCC30����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chirp_en  : 1;  /* bit[0]   : chirpʹ�ܡ������� */
        unsigned int  IDDIG_SEL : 1;  /* bit[1]   : IDDIGѡ��
                                                    1����������RID_A��RID_GND��ֵ������ID��ֵ
                                                    0��ID��ֵȡ���ڿ������˿��ϵ�IDDIG���� */
        unsigned int  reserved  : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_USB3OTG_BCFG_UNION;
#endif
#define SOC_USB3OTG_BCFG_chirp_en_START   (0)
#define SOC_USB3OTG_BCFG_chirp_en_END     (0)
#define SOC_USB3OTG_BCFG_IDDIG_SEL_START  (1)
#define SOC_USB3OTG_BCFG_IDDIG_SEL_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BCEVT_UNION
 �ṹ˵��  : BCEVT �Ĵ����ṹ���塣��ַƫ����:0xCC38����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC�¼��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MultValIdBc : 5;  /* bit[0-4]  : �����ACA�ӿ��ϵ�ֵ��
                                                       [4]:bc_rid_float
                                                       [3]:bc_rid_gnd
                                                       [2]:bc_rid_a
                                                       [1]:bc_rid_b
                                                       [0]:bc_rid_c */
        unsigned int  reserved_0  : 19; /* bit[5-23] : ������ */
        unsigned int  mv_chngevnt : 1;  /* bit[24]   : ָʾACA�ӿ��ϵ�ֵ�ı仯�¼��� */
        unsigned int  reserved_1  : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_USB3OTG_BCEVT_UNION;
#endif
#define SOC_USB3OTG_BCEVT_MultValIdBc_START  (0)
#define SOC_USB3OTG_BCEVT_MultValIdBc_END    (4)
#define SOC_USB3OTG_BCEVT_mv_chngevnt_START  (24)
#define SOC_USB3OTG_BCEVT_mv_chngevnt_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BCEVTEN_UNION
 �ṹ˵��  : BCEVTEN �Ĵ����ṹ���塣��ַƫ����:0xCC3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC�¼�ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0     : 24; /* bit[0-23] : ������ */
        unsigned int  mv_chngevntena : 1;  /* bit[24]   : ʹ��ACAֵ�ı仯�¼��� */
        unsigned int  reserved_1     : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_USB3OTG_BCEVTEN_UNION;
#endif
#define SOC_USB3OTG_BCEVTEN_mv_chngevntena_START  (24)
#define SOC_USB3OTG_BCEVTEN_mv_chngevntena_END    (24)






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

#endif /* end of soc_usb3otg_interface.h */
