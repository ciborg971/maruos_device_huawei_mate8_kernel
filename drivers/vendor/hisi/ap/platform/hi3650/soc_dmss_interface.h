/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dmss_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-09 16:17:08
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��9��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DMSS.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DMSS_INTERFACE_H__
#define __SOC_DMSS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_DMSS
 ****************************************************************************/
/* �Ĵ���˵����RTL������Ϣ0
   λ����UNION�ṹ:  SOC_DMSS_ASI_RTL_INF0_UNION */
#define SOC_DMSS_ASI_RTL_INF0_ADDR(base, asi_base)    ((base) + (0x000+0x800*(asi_base)))

/* �Ĵ���˵����RTL������Ϣ1
   λ����UNION�ṹ:  SOC_DMSS_ASI_RTL_INF1_UNION */
#define SOC_DMSS_ASI_RTL_INF1_ADDR(base, asi_base)    ((base) + (0x004+0x800*(asi_base)))

/* �Ĵ���˵����RTL������Ϣ2
   λ����UNION�ṹ:  SOC_DMSS_ASI_RTL_INF2_UNION */
#define SOC_DMSS_ASI_RTL_INF2_ADDR(base, asi_base)    ((base) + (0x008+0x800*(asi_base)))

/* �Ĵ���˵����RTL������Ϣ3
   λ����UNION�ṹ:  SOC_DMSS_ASI_RTL_INF3_UNION */
#define SOC_DMSS_ASI_RTL_INF3_ADDR(base, asi_base)    ((base) + (0x00C+0x800*(asi_base)))

/* �Ĵ���˵������̬ʱ���ſ�
   λ����UNION�ṹ:  SOC_DMSS_ASI_STA_CKG_UNION */
#define SOC_DMSS_ASI_STA_CKG_ADDR(base, asi_base)     ((base) + (0x010+0x800*(asi_base)))

/* �Ĵ���˵������̬ʱ���ſ�
   λ����UNION�ṹ:  SOC_DMSS_ASI_DYN_CKG_UNION */
#define SOC_DMSS_ASI_DYN_CKG_ADDR(base, asi_base)     ((base) + (0x014+0x800*(asi_base)))

/* �Ĵ���˵�����첽��ʱ���ſ�
   λ����UNION�ṹ:  SOC_DMSS_ASI_ASYNC_BRG_UNION */
#define SOC_DMSS_ASI_ASYNC_BRG_ADDR(base, asi_base)   ((base) + (0x018+0x800*(asi_base)))

/* �Ĵ���˵������ַ��λ
   λ����UNION�ṹ:  SOC_DMSS_ASI_ADDR_SHIFT_UNION */
#define SOC_DMSS_ASI_ADDR_SHIFT_ADDR(base, asi_base)  ((base) + (0x020+0x800*(asi_base)))

/* �Ĵ���˵����д��������ƥ��
   λ����UNION�ṹ:  SOC_DMSS_ASI_RATE_ADPT_UNION */
#define SOC_DMSS_ASI_RATE_ADPT_ADDR(base, asi_base)   ((base) + (0x030+0x800*(asi_base)))

/* �Ĵ���˵�������������0
   λ����UNION�ṹ:  SOC_DMSS_ASI_RDR_CTRL0_UNION */
#define SOC_DMSS_ASI_RDR_CTRL0_ADDR(base, asi_base)   ((base) + (0x040+0x800*(asi_base)))

/* �Ĵ���˵�������������1
   λ����UNION�ṹ:  SOC_DMSS_ASI_RDR_CTRL1_UNION */
#define SOC_DMSS_ASI_RDR_CTRL1_ADDR(base, asi_base)   ((base) + (0x044+0x800*(asi_base)))

/* �Ĵ���˵�������������2
   λ����UNION�ṹ:  SOC_DMSS_ASI_RDR_CTRL2_UNION */
#define SOC_DMSS_ASI_RDR_CTRL2_ADDR(base, asi_base)   ((base) + (0x048+0x800*(asi_base)))

/* �Ĵ���˵����RBUF�ļ��ģʽ����0
   λ����UNION�ṹ:  SOC_DMSS_ASI_RBUF_INTLV0_UNION */
#define SOC_DMSS_ASI_RBUF_INTLV0_ADDR(base, asi_base)  ((base) + (0x060+0x800*(asi_base)))

/* �Ĵ���˵����RBUF�ļ��ģʽ����1
   λ����UNION�ṹ:  SOC_DMSS_ASI_RBUF_INTLV1_UNION */
#define SOC_DMSS_ASI_RBUF_INTLV1_ADDR(base, asi_base)  ((base) + (0x064+0x800*(asi_base)))

/* �Ĵ���˵�����������ȼ�����
   λ����UNION�ṹ:  SOC_DMSS_ASI_QOS_CTRL_UNION */
#define SOC_DMSS_ASI_QOS_CTRL_ADDR(base, asi_base)    ((base) + (0x100+0x800*(asi_base)))

/* �Ĵ���˵����д�������ȼ�ӳ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_QOS_WRPRI_UNION */
#define SOC_DMSS_ASI_QOS_WRPRI_ADDR(base, asi_base)   ((base) + (0x104+0x800*(asi_base)))

/* �Ĵ���˵�������������ȼ�ӳ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_QOS_RDPRI_UNION */
#define SOC_DMSS_ASI_QOS_RDPRI_ADDR(base, asi_base)   ((base) + (0x108+0x800*(asi_base)))

/* �Ĵ���˵�����������ȼ�����Ӧ����ӳ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_QOS_ADPT_UNION */
#define SOC_DMSS_ASI_QOS_ADPT_ADDR(base, asi_base)    ((base) + (0x10C+0x800*(asi_base)))

/* �Ĵ���˵�����������ȼ�����0
            ���ɵ������ƶ��������ȼ�����ͬʱ���ƶ�д�������ȼ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_QOS_RGLR0_UNION */
#define SOC_DMSS_ASI_QOS_RGLR0_ADDR(base, asi_base)   ((base) + (0x120+0x800*(asi_base)))

/* �Ĵ���˵���������������ȼ�0
   λ����UNION�ṹ:  SOC_DMSS_ASI_QOS_RGLR0_PRI_UNION */
#define SOC_DMSS_ASI_QOS_RGLR0_PRI_ADDR(base, asi_base)  ((base) + (0x124+0x800*(asi_base)))

/* �Ĵ���˵�����������ȼ�����1
            ��ֻ�ɵ�������д�������ȼ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_QOS_RGLR1_UNION */
#define SOC_DMSS_ASI_QOS_RGLR1_ADDR(base, asi_base)   ((base) + (0x128+0x800*(asi_base)))

/* �Ĵ���˵���������������ȼ�1
   λ����UNION�ṹ:  SOC_DMSS_ASI_QOS_RGLR1_PRI_UNION */
#define SOC_DMSS_ASI_QOS_RGLR1_PRI_ADDR(base, asi_base)  ((base) + (0x12C+0x800*(asi_base)))

/* �Ĵ���˵����������������0
            ���ɵ������ƶ�������ͬʱ���ƶ�д�ܴ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_QOS_LMTR0_UNION */
#define SOC_DMSS_ASI_QOS_LMTR0_ADDR(base, asi_base)   ((base) + (0x140+0x800*(asi_base)))

/* �Ĵ���˵����������������1
            ��ֻ�ɵ�������д����
   λ����UNION�ṹ:  SOC_DMSS_ASI_QOS_LMTR1_UNION */
#define SOC_DMSS_ASI_QOS_LMTR1_ADDR(base, asi_base)   ((base) + (0x144+0x800*(asi_base)))

/* �Ĵ���˵����������OSTD����
   λ����UNION�ṹ:  SOC_DMSS_ASI_QOS_RDOSTD_UNION */
#define SOC_DMSS_ASI_QOS_RDOSTD_ADDR(base, asi_base)  ((base) + (0x160+0x800*(asi_base)))

/* �Ĵ���˵����������OSTD״̬ͳ��
   λ����UNION�ṹ:  SOC_DMSS_ASI_QOS_RDOSTD_ST_UNION */
#define SOC_DMSS_ASI_QOS_RDOSTD_ST_ADDR(base, asi_base)  ((base) + (0x164+0x800*(asi_base)))

/* �Ĵ���˵��������ͳ�ƿ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_FLUX_STAT_CTRL_UNION */
#define SOC_DMSS_ASI_FLUX_STAT_CTRL_ADDR(base, asi_base)  ((base) + (0x170+0x800*(asi_base)))

/* �Ĵ���˵����д����ͳ��
   λ����UNION�ṹ:  SOC_DMSS_ASI_FLUX_STAT_WR_UNION */
#define SOC_DMSS_ASI_FLUX_STAT_WR_ADDR(base, asi_base)  ((base) + (0x178+0x800*(asi_base)))

/* �Ĵ���˵����������ͳ��
   λ����UNION�ṹ:  SOC_DMSS_ASI_FLUX_STAT_RD_UNION */
#define SOC_DMSS_ASI_FLUX_STAT_RD_ADDR(base, asi_base)  ((base) + (0x17C+0x800*(asi_base)))

/* �Ĵ���˵����д����ͬMID�������ȼ�����ʹ��
   λ����UNION�ṹ:  SOC_DMSS_ASI_PUSH_WRMID_UNION */
#define SOC_DMSS_ASI_PUSH_WRMID_ADDR(base, asi_base)  ((base) + (0x180+0x800*(asi_base)))

/* �Ĵ���˵����������ͬMID�������ȼ�����ʹ��
   λ����UNION�ṹ:  SOC_DMSS_ASI_PUSH_RDMID_UNION */
#define SOC_DMSS_ASI_PUSH_RDMID_ADDR(base, asi_base)  ((base) + (0x184+0x800*(asi_base)))

/* �Ĵ���˵����������ȫ����������üĴ���
            ����secur_boot_lock�źű����߳���һ��ʱ������ʱ���˼Ĵ���������ѡ������ؼĴ���������Ϊֻ����ֻ��ͨ��ϵͳ��λ���������
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_LD_SEL_UNION */
#define SOC_DMSS_ASI_SEC_LD_SEL_ADDR(base, asi_base)  ((base) + (0x410+0x800*(asi_base)))

/* �Ĵ���˵������ȫ�ж�ʹ��
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_INT_EN_UNION */
#define SOC_DMSS_ASI_SEC_INT_EN_ADDR(base, asi_base)  ((base) + (0x420+0x800*(asi_base)))

/* �Ĵ���˵������ȫ�ж�״̬
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_INT_STATUS_UNION */
#define SOC_DMSS_ASI_SEC_INT_STATUS_ADDR(base, asi_base)  ((base) + (0x424+0x800*(asi_base)))

/* �Ĵ���˵������¼�׸�ԽȨ�������Ϣ0
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_FAIL_CMD_INF0_UNION */
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF0_ADDR(base, asi_base)  ((base) + (0x480+0x800*(asi_base)))

/* �Ĵ���˵������¼�׸�ԽȨ�������Ϣ1
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_UNION */
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_ADDR(base, asi_base)  ((base) + (0x484+0x800*(asi_base)))

/* �Ĵ���˵������¼�׸�ԽȨ�������Ϣ2
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_UNION */
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_ADDR(base, asi_base)  ((base) + (0x488+0x800*(asi_base)))

/* �Ĵ���˵�������ɲ��Կ��ƼĴ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_ITCRG_UNION */
#define SOC_DMSS_ASI_SEC_ITCRG_ADDR(base, asi_base)   ((base) + (0x4C0+0x800*(asi_base)))

/* �Ĵ���˵�������ɲ�������Ĵ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_ITIP_UNION */
#define SOC_DMSS_ASI_SEC_ITIP_ADDR(base, asi_base)    ((base) + (0x4C4+0x800*(asi_base)))

/* �Ĵ���˵�������ɲ�������Ĵ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_ITOP_UNION */
#define SOC_DMSS_ASI_SEC_ITOP_ADDR(base, asi_base)    ((base) + (0x4C8+0x800*(asi_base)))

/* �Ĵ���˵������ַ����ӳ��
            ��������������sucure_boot_lock�źű����߹�����ld_region_map����Ϊ1���Ҷ�Ӧregion��ld_regions��ѡ����Χ�ڡ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_RGN_MAP_UNION */
#define SOC_DMSS_ASI_SEC_RGN_MAP_ADDR(base, sec_rgns, asi_base)  ((base) + (0x500+0x10*(sec_rgns)+0x800*(asi_base)))

/* �Ĵ���˵��������ַ�����Ȩ����������
            ��������������sucure_boot_lock�źű����߹�����ld_region_attrib����Ϊ1���Ҷ�Ӧregion��ld_regions��ѡ����Χ�ڡ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_RGN_ATTRIB_UNION */
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_ADDR(base, sec_rgns, asi_base)  ((base) + (0x504+0x10*(sec_rgns)+0x800*(asi_base)))

/* �Ĵ���˵����д����ƥ��MasterID��������
            ��������������sucure_boot_lock�źű����߹�����ld_mid_wr����Ϊ1���Ҷ�Ӧregion��ld_regions��ѡ����Χ�ڡ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_MID_WR_UNION */
#define SOC_DMSS_ASI_SEC_MID_WR_ADDR(base, sec_rgns, asi_base)  ((base) + (0x508+0x10*(sec_rgns)+0x800*(asi_base)))

/* �Ĵ���˵����������ƥ��MasterID��������
            ��������������sucure_boot_lock�źű����߹�����ld_mid_rd����Ϊ1���Ҷ�Ӧregion��ld_regions��ѡ����Χ�ڡ���
   λ����UNION�ṹ:  SOC_DMSS_ASI_SEC_MID_RD_UNION */
#define SOC_DMSS_ASI_SEC_MID_RD_ADDR(base, sec_rgns, asi_base)  ((base) + (0x50C+0x10*(sec_rgns)+0x800*(asi_base)))

/* �Ĵ���˵����DFX����Ҫģ�鹤��״̬
   λ����UNION�ṹ:  SOC_DMSS_ASI_DFX_MODULE_UNION */
#define SOC_DMSS_ASI_DFX_MODULE_ADDR(base, asi_base)  ((base) + (0x700+0x800*(asi_base)))

/* �Ĵ���˵����DFX��FIFO����״̬
   λ����UNION�ṹ:  SOC_DMSS_ASI_DFX_FIFO_UNION */
#define SOC_DMSS_ASI_DFX_FIFO_ADDR(base, asi_base)    ((base) + (0x704+0x800*(asi_base)))

/* �Ĵ���˵����DFX��״̬������״̬
   λ����UNION�ṹ:  SOC_DMSS_ASI_DFX_FSM_UNION */
#define SOC_DMSS_ASI_DFX_FSM_ADDR(base, asi_base)     ((base) + (0x708+0x800*(asi_base)))

/* �Ĵ���˵����DFX��дOSTD״̬
   λ����UNION�ṹ:  SOC_DMSS_ASI_DFX_WROSTD_UNION */
#define SOC_DMSS_ASI_DFX_WROSTD_ADDR(base, asi_base)  ((base) + (0x70C+0x800*(asi_base)))

/* �Ĵ���˵����DFX��REORDERģ��״̬0
   λ����UNION�ṹ:  SOC_DMSS_ASI_DFX_RDR0_UNION */
#define SOC_DMSS_ASI_DFX_RDR0_ADDR(base, asi_base)    ((base) + (0x710+0x800*(asi_base)))

/* �Ĵ���˵����DFX��REORDERģ��״̬1
   λ����UNION�ṹ:  SOC_DMSS_ASI_DFX_RDR1_UNION */
#define SOC_DMSS_ASI_DFX_RDR1_ADDR(base, asi_base)    ((base) + (0x714+0x800*(asi_base)))

/* �Ĵ���˵����DFX���쳣������Ϣ�ж�ʹ��
   λ����UNION�ṹ:  SOC_DMSS_ASI_DFX_INT_EN_UNION */
#define SOC_DMSS_ASI_DFX_INT_EN_ADDR(base, asi_base)  ((base) + (0x720+0x800*(asi_base)))

/* �Ĵ���˵����DFX���쳣������Ϣ�ж�
   λ����UNION�ṹ:  SOC_DMSS_ASI_DFX_INT_STATUS_UNION */
#define SOC_DMSS_ASI_DFX_INT_STATUS_ADDR(base, asi_base)  ((base) + (0x724+0x800*(asi_base)))

/* �Ĵ���˵����DFX���쳣������Ϣ��¼
   λ����UNION�ṹ:  SOC_DMSS_ASI_DFX_ABNM_INF_UNION */
#define SOC_DMSS_ASI_DFX_ABNM_INF_ADDR(base, asi_base)  ((base) + (0x728+0x800*(asi_base)))

/* �Ĵ���˵����DFX�������������״̬
            ����RTL������DMSS_SIM_DFX_ENΪ0��ͨ��ASIC�汾����Ϊ0��FPGA��EMULATOR�汾����Ϊ1������˼Ĵ��������ڣ�
   λ����UNION�ṹ:  SOC_DMSS_ASI_DFX_LOAD_UNION */
#define SOC_DMSS_ASI_DFX_LOAD_ADDR(base, asi_base)    ((base) + (0x760+0x800*(asi_base)))

/* �Ĵ���˵��������汾��Ϣ
   λ����UNION�ṹ:  SOC_DMSS_GLB_RTL_VER_UNION */
#define SOC_DMSS_GLB_RTL_VER_ADDR(base)               ((base) + (0x6000))

/* �Ĵ���˵��������������Ϣ0
   λ����UNION�ṹ:  SOC_DMSS_GLB_RTL_INF0_UNION */
#define SOC_DMSS_GLB_RTL_INF0_ADDR(base)              ((base) + (0x6004))

/* �Ĵ���˵��������������Ϣ1
   λ����UNION�ṹ:  SOC_DMSS_GLB_RTL_INF1_UNION */
#define SOC_DMSS_GLB_RTL_INF1_ADDR(base)              ((base) + (0x6008))

/* �Ĵ���˵����MEMORY����
   λ����UNION�ṹ:  SOC_DMSS_GLB_RAM_TMOD_UNION */
#define SOC_DMSS_GLB_RAM_TMOD_ADDR(base)              ((base) + (0x6018))

/* �Ĵ���˵�������üĴ�������
   λ����UNION�ṹ:  SOC_DMSS_GLB_CFG_LOCK_UNION */
#define SOC_DMSS_GLB_CFG_LOCK_ADDR(base)              ((base) + (0x6020))

/* �Ĵ���˵������̬ʱ���ſ�
   λ����UNION�ṹ:  SOC_DMSS_GLB_DYN_CKG_UNION */
#define SOC_DMSS_GLB_DYN_CKG_ADDR(base)               ((base) + (0x6024))

/* �Ĵ���˵����ȫ���ж�״̬�鿴
   λ����UNION�ṹ:  SOC_DMSS_GLB_INT_STATUS_UNION */
#define SOC_DMSS_GLB_INT_STATUS_ADDR(base)            ((base) + (0x6030))

/* �Ĵ���˵����ȫ���ж�״̬���
   λ����UNION�ṹ:  SOC_DMSS_GLB_INT_CLEAR_UNION */
#define SOC_DMSS_GLB_INT_CLEAR_ADDR(base)             ((base) + (0x6034))

/* �Ĵ���˵����exclusive��������
   λ����UNION�ṹ:  SOC_DMSS_GLB_EXCLU_UNION */
#define SOC_DMSS_GLB_EXCLU_ADDR(base)                 ((base) + (0x6040))

/* �Ĵ���˵����ȫ�ֵ�ַ��֯ģʽ
   λ����UNION�ṹ:  SOC_DMSS_GLB_ADDR_INTLV_UNION */
#define SOC_DMSS_GLB_ADDR_INTLV_ADDR(base)            ((base) + (0x6100))

/* �Ĵ���˵����ȫ�ֵ�ַ����ģʽ
   λ����UNION�ṹ:  SOC_DMSS_GLB_ADDR_SCRMBL_UNION */
#define SOC_DMSS_GLB_ADDR_SCRMBL_ADDR(base)           ((base) + (0x6110))

/* �Ĵ���˵����RBUF�Ĵ�����ʼˮ������0
   λ����UNION�ṹ:  SOC_DMSS_GLB_RBUF_TRSFR_WL0_UNION */
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_ADDR(base)        ((base) + (0x6140))

/* �Ĵ���˵����RBUF�Ĵ�����ʼˮ������1
   λ����UNION�ṹ:  SOC_DMSS_GLB_RBUF_TRSFR_WL1_UNION */
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_ADDR(base)        ((base) + (0x6144))

/* �Ĵ���˵����RBUF�����ѹ����
   λ����UNION�ṹ:  SOC_DMSS_GLB_RBUF_BP_UNION */
#define SOC_DMSS_GLB_RBUF_BP_ADDR(base, rbuf_bp_grps)  ((base) + (0x6150+0x4*(rbuf_bp_grps)))

/* �Ĵ���˵����DFX��RBUF״̬0
   λ����UNION�ṹ:  SOC_DMSS_GLB_DFX_RBUF0_UNION */
#define SOC_DMSS_GLB_DFX_RBUF0_ADDR(base, chans)      ((base) + (0x6700+0x10*(chans)))

/* �Ĵ���˵����DFX��RBUF״̬1
   λ����UNION�ṹ:  SOC_DMSS_GLB_DFX_RBUF1_UNION */
#define SOC_DMSS_GLB_DFX_RBUF1_ADDR(base, chans)      ((base) + (0x6704+0x10*(chans)))

/* �Ĵ���˵����DFX��RBUF״̬2
   λ����UNION�ṹ:  SOC_DMSS_GLB_DFX_RBUF2_UNION */
#define SOC_DMSS_GLB_DFX_RBUF2_ADDR(base, chans)      ((base) + (0x6708+0x10*(chans)))

/* �Ĵ���˵����DFX��RBUF״̬3
   λ����UNION�ṹ:  SOC_DMSS_GLB_DFX_RBUF3_UNION */
#define SOC_DMSS_GLB_DFX_RBUF3_ADDR(base, chans)      ((base) + (0x670C+0x10*(chans)))

/* �Ĵ���˵����DFX��DMI�������ٲ�״̬
   λ����UNION�ṹ:  SOC_DMSS_GLB_DFX_DMI_GRNT_UNION */
#define SOC_DMSS_GLB_DFX_DMI_GRNT_ADDR(base)          ((base) + (0x6740))

/* �Ĵ���˵����DFX������ASI�Ĺ���״̬
   λ����UNION�ṹ:  SOC_DMSS_GLB_DFX_ASI_BUSY_UNION */
#define SOC_DMSS_GLB_DFX_ASI_BUSY_ADDR(base)          ((base) + (0x6750))

/* �Ĵ���˵����DFX�������������״̬
            ����RTL������DMSS_SIM_DFX_ENΪ0��ͨ��ASIC�汾����Ϊ0��FPGA��EMULATOR�汾����Ϊ1������˼Ĵ��������ڣ�
   λ����UNION�ṹ:  SOC_DMSS_GLB_DFX_LOAD_UNION */
#define SOC_DMSS_GLB_DFX_LOAD_ADDR(base)              ((base) + (0x6760))





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
                     (1/1) register_DMSS
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_RTL_INF0_UNION
 �ṹ˵��  : ASI_RTL_INF0 �Ĵ����ṹ���塣��ַƫ����:0x000+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: RTL������Ϣ0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_data_width    : 1;  /* bit[0]    : �Խӵ�AXI���ߵ�ַλ��
                                                             0��64bits
                                                             1��128bits */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : ���� */
        unsigned int  rtl_clk_mode      : 2;  /* bit[4-5]  : �Խ�AXI����ʱ����DMSS��ʱ�ӵĹ�ϵ
                                                             0x0����Ƶͬ������Ƶ��AXI���߲಻��������multicycle�����Ը�Ƶʱ����ʱ�򣩣�
                                                             0x1����Ƶͬ������Ƶ��AXI���߲��������multicycle���ɰ���Ƶʱ����ʱ�򣩣�
                                                             0x2���첽��
                                                             0x3��ͬƵͬ����
                                                             ע�⣺���Խ�ʱ�ӹ�ϵ�����첽ʱ���첽��ؼĴ�����Ч�� */
        unsigned int  reserved_1        : 10; /* bit[6-15] : ���� */
        unsigned int  rtl_rdr_que_depth : 2;  /* bit[16-17]: ����ģ��Ķ�������м����ȣ���ЧΪ�������������outstanding����
                                                             0�� 8 read cmd��
                                                             1��16 read cmd��
                                                             2��24 read cmd��
                                                             3��32 read cmd�� */
        unsigned int  reserved_2        : 2;  /* bit[18-19]: ���� */
        unsigned int  rtl_rdr_buf_num   : 2;  /* bit[20-21]: ����ģ��ı���buffer��ȡ�
                                                             0�� 8 read burst��
                                                             1��16 read burst��
                                                             2��24 read burst��
                                                             3��32 read burst�� */
        unsigned int  reserved_3        : 2;  /* bit[22-23]: ���� */
        unsigned int  rtl_rdr_en        : 1;  /* bit[24]   : ͬID�������ܡ�
                                                             0����֧�֣�
                                                             1��֧�֡�
                                                             ע�⣺
                                                             1.ֻ����ϵͳ���汣֤��ǰASI�����յ�outstanding��ͬID��������κζ�����Ҳ���ᱻASI��ֳɶ��ͬID�Ķ�����ʱ���ſ���RTL����Ϊ��֧�ֱ����ܣ�
                                                             2.����֧��ͬID�������ܣ���������ؼĴ�����Ч�� */
        unsigned int  reserved_4        : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_DMSS_ASI_RTL_INF0_UNION;
#endif
#define SOC_DMSS_ASI_RTL_INF0_rtl_data_width_START     (0)
#define SOC_DMSS_ASI_RTL_INF0_rtl_data_width_END       (0)
#define SOC_DMSS_ASI_RTL_INF0_rtl_clk_mode_START       (4)
#define SOC_DMSS_ASI_RTL_INF0_rtl_clk_mode_END         (5)
#define SOC_DMSS_ASI_RTL_INF0_rtl_rdr_que_depth_START  (16)
#define SOC_DMSS_ASI_RTL_INF0_rtl_rdr_que_depth_END    (17)
#define SOC_DMSS_ASI_RTL_INF0_rtl_rdr_buf_num_START    (20)
#define SOC_DMSS_ASI_RTL_INF0_rtl_rdr_buf_num_END      (21)
#define SOC_DMSS_ASI_RTL_INF0_rtl_rdr_en_START         (24)
#define SOC_DMSS_ASI_RTL_INF0_rtl_rdr_en_END           (24)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_RTL_INF1_UNION
 �ṹ˵��  : ASI_RTL_INF1 �Ĵ����ṹ���塣��ַƫ����:0x004+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: RTL������Ϣ1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_wcmd_fifo_depth : 5;  /* bit[0-4]  : д����FIFO������ȡ�
                                                               0x0�� 1 write cmd��
                                                               0x1�� 2 write cmd��
                                                               ����
                                                               0x31��32 write cmd�� */
        unsigned int  reserved_0          : 3;  /* bit[5-7]  : ���� */
        unsigned int  rtl_wd_fifo_depth   : 5;  /* bit[8-12] : д����FIFO������ȡ�
                                                               0x0�� 1 write transfer��
                                                               0x1�� 2 write transfer��
                                                               ����
                                                               0x31��32 write transfer�� */
        unsigned int  reserved_1          : 3;  /* bit[13-15]: ���� */
        unsigned int  rtl_b_fifo_depth    : 5;  /* bit[16-20]: д��ӦFIFO������ȡ�
                                                               0x0�� 1 write response��
                                                               0x1�� 2 write response��
                                                               ����
                                                               0x31��32 write response�� */
        unsigned int  reserved_2          : 3;  /* bit[21-23]: ���� */
        unsigned int  rtl_ra_fifo_depth   : 5;  /* bit[24-28]: ����ƥ��д����FIFO������ȡ�
                                                               0x0�� 1 write transfer��
                                                               0x1�� 2 write transfer��
                                                               ����
                                                               0x31��32 write transfer�� */
        unsigned int  reserved_3          : 3;  /* bit[29-31]: ���� */
    } reg;
} SOC_DMSS_ASI_RTL_INF1_UNION;
#endif
#define SOC_DMSS_ASI_RTL_INF1_rtl_wcmd_fifo_depth_START  (0)
#define SOC_DMSS_ASI_RTL_INF1_rtl_wcmd_fifo_depth_END    (4)
#define SOC_DMSS_ASI_RTL_INF1_rtl_wd_fifo_depth_START    (8)
#define SOC_DMSS_ASI_RTL_INF1_rtl_wd_fifo_depth_END      (12)
#define SOC_DMSS_ASI_RTL_INF1_rtl_b_fifo_depth_START     (16)
#define SOC_DMSS_ASI_RTL_INF1_rtl_b_fifo_depth_END       (20)
#define SOC_DMSS_ASI_RTL_INF1_rtl_ra_fifo_depth_START    (24)
#define SOC_DMSS_ASI_RTL_INF1_rtl_ra_fifo_depth_END      (28)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_RTL_INF2_UNION
 �ṹ˵��  : ASI_RTL_INF2 �Ĵ����ṹ���塣��ַƫ����:0x008+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: RTL������Ϣ2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_rbar_fifo_depth : 5;  /* bit[0-4]  : ��barrier����FIFO������ȡ�
                                                               0x0�� 1 barrier cmd��
                                                               0x1�� 2 barrier cmd��
                                                               ����
                                                               0x31��32 barrier cmd�� */
        unsigned int  reserved_0          : 3;  /* bit[5-7]  : ���� */
        unsigned int  rtl_rd_fifo_depth   : 5;  /* bit[8-12] : ������FIFO������ȡ�
                                                               0x0�� 1 read transfer��
                                                               0x1�� 2 read transfer��
                                                               ����
                                                               0x31��32 read transfer�� */
        unsigned int  reserved_1          : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_DMSS_ASI_RTL_INF2_UNION;
#endif
#define SOC_DMSS_ASI_RTL_INF2_rtl_rbar_fifo_depth_START  (0)
#define SOC_DMSS_ASI_RTL_INF2_rtl_rbar_fifo_depth_END    (4)
#define SOC_DMSS_ASI_RTL_INF2_rtl_rd_fifo_depth_START    (8)
#define SOC_DMSS_ASI_RTL_INF2_rtl_rd_fifo_depth_END      (12)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_RTL_INF3_UNION
 �ṹ˵��  : ASI_RTL_INF3 �Ĵ����ṹ���塣��ַƫ����:0x00C+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: RTL������Ϣ3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_sec_rgn_num : 5;  /* bit[0-4] : ��ȫģ���regions������
                                                          5'd0���ް�ȫģ�飻
                                                          5'd1��1regions��
                                                          5'd2��2regions��
                                                          5'd3��3regions��
                                                          ����
                                                          ע�⣺���ް�ȫģ��ʱ����ȫ������ؼĴ�����Ч�� */
        unsigned int  reserved        : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_DMSS_ASI_RTL_INF3_UNION;
#endif
#define SOC_DMSS_ASI_RTL_INF3_rtl_sec_rgn_num_START  (0)
#define SOC_DMSS_ASI_RTL_INF3_rtl_sec_rgn_num_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_STA_CKG_UNION
 �ṹ˵��  : ASI_STA_CKG �Ĵ����ṹ���塣��ַƫ����:0x010+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��̬ʱ���ſ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_en_asi : 1;  /* bit[0]   : ASI��̬ʱ���ſأ�
                                                    0����ֹ��
                                                    1��ʹ�ܣ��رյ�ǰASI����ʱ�ӡ�
                                                    ע�⣺
                                                    ֻ��ȷ����ǰASI��������Խӵ�master�豸�����޷���ʱ���ſ���ʹ��ASI��̬ʱ���ſأ�����ᵼ��ϵͳ������ */
        unsigned int  reserved  : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DMSS_ASI_STA_CKG_UNION;
#endif
#define SOC_DMSS_ASI_STA_CKG_gt_en_asi_START  (0)
#define SOC_DMSS_ASI_STA_CKG_gt_en_asi_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_DYN_CKG_UNION
 �ṹ˵��  : ASI_DYN_CKG �Ĵ����ṹ���塣��ַƫ����:0x014+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��̬ʱ���ſ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ckg_byp_asi     : 1;  /* bit[0]    : ASIģ��Ķ�̬ʱ���ſأ�
                                                           0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                           1��ʱ�ӳ����� */
        unsigned int  ckg_byp_ra      : 1;  /* bit[1]    : RAģ��Ķ�̬ʱ���ſأ�
                                                           0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                           1��ʱ�ӳ����� */
        unsigned int  ckg_byp_ax      : 1;  /* bit[2]    : AXģ��Ķ�̬ʱ���ſأ�
                                                           0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                           1��ʱ�ӳ����� */
        unsigned int  ckg_byp_cs      : 1;  /* bit[3]    : CSģ��Ķ�̬ʱ���ſأ�
                                                           0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                           1��ʱ�ӳ����� */
        unsigned int  ckg_byp_wd      : 1;  /* bit[4]    : WDģ��Ķ�̬ʱ���ſأ�
                                                           0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                           1��ʱ�ӳ����� */
        unsigned int  ckg_byp_b       : 1;  /* bit[5]    : Bģ��Ķ�̬ʱ���ſأ�
                                                           0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                           1��ʱ�ӳ����� */
        unsigned int  ckg_byp_rd      : 1;  /* bit[6]    : RDģ��Ķ�̬ʱ���ſأ�
                                                           0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                           1��ʱ�ӳ����� */
        unsigned int  ckg_byp_fkrd    : 1;  /* bit[7]    : FKRDģ��Ķ�̬ʱ���ſأ�
                                                           0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                           1��ʱ�ӳ����� */
        unsigned int  ckg_byp_sec     : 1;  /* bit[8]    : SECģ��Ķ�̬ʱ���ſأ�
                                                           0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                           1��ʱ�ӳ�����
                                                           ע�⣺
                                                           ��ǰASI�Ƿ��а�ȫģ�飬����ͨ���Ĵ���ASI_RTL_INF0.rtl_sec_rgn_numȷ�ϡ� */
        unsigned int  ckg_byp_rdr_est : 1;  /* bit[9]    : RDR_ESTģ��Ķ�̬ʱ���ſأ�
                                                           0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                           1��ʱ�ӳ�����
                                                           ע�⣺
                                                           ��ǰASI�Ƿ��б���ģ�飬����ͨ���Ĵ���ASI_RTL_INF0.rtl_rdr_enȷ�ϡ� */
        unsigned int  ckg_byp_rdr_buf : 1;  /* bit[10]   : RDR_BUFģ��Ķ�̬ʱ���ſأ�
                                                           0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                           1��ʱ�ӳ�����
                                                           ע�⣺
                                                           ��ǰASI�Ƿ��б���ģ�飬����ͨ���Ĵ���ASI_RTL_INF0.rtl_rdr_enȷ�ϡ� */
        unsigned int  ckg_byp_async   : 1;  /* bit[11]   : ASYNCģ��Ķ�̬ʱ���ſأ�
                                                           0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                           1��ʱ�ӳ�����
                                                           ע�⣺
                                                           ��ǰASI�Ƿ����첽�ţ�����ͨ���Ĵ���ASI_RTL_INF0.rtl_clk_modeȷ�ϡ� */
        unsigned int  reserved        : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DMSS_ASI_DYN_CKG_UNION;
#endif
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_asi_START      (0)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_asi_END        (0)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_ra_START       (1)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_ra_END         (1)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_ax_START       (2)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_ax_END         (2)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_cs_START       (3)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_cs_END         (3)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_wd_START       (4)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_wd_END         (4)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_b_START        (5)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_b_END          (5)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_rd_START       (6)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_rd_END         (6)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_fkrd_START     (7)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_fkrd_END       (7)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_sec_START      (8)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_sec_END        (8)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_rdr_est_START  (9)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_rdr_est_END    (9)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_rdr_buf_START  (10)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_rdr_buf_END    (10)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_async_START    (11)
#define SOC_DMSS_ASI_DYN_CKG_ckg_byp_async_END      (11)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_ASYNC_BRG_UNION
 �ṹ˵��  : ASI_ASYNC_BRG �Ĵ����ṹ���塣��ַƫ����:0x018+0x800*(asi_base)����ֵ:0x0000007F�����:32
 �Ĵ���˵��: �첽��ʱ���ſ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cactive_wl : 7;  /* bit[0-6] : �첽���ſؼ�����ˮ�����ã�
                                                     n:���첽��CACTIVE�ź����Ͳ�����n��ʱ�����ں󣬹ر��첽��ʱ��
                                                     ע�⣺
                                                     ���첽�Ŷ�̬ʱ���ſ�����Ϊ�����������������Ч�� */
        unsigned int  reserved   : 25; /* bit[7-31]: ���� */
    } reg;
} SOC_DMSS_ASI_ASYNC_BRG_UNION;
#endif
#define SOC_DMSS_ASI_ASYNC_BRG_cactive_wl_START  (0)
#define SOC_DMSS_ASI_ASYNC_BRG_cactive_wl_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_ADDR_SHIFT_UNION
 �ṹ˵��  : ASI_ADDR_SHIFT �Ĵ����ṹ���塣��ַƫ����:0x020+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ַ��λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_shift_mode : 2;  /* bit[0-1] : ��ַ��λģʽ��
                                                          0x0,0x3������λ��
                                                          0x1�������߷��ʵ�4~4.5GB��ַ����Ϊ3.5~4GB��ַ��
                                                          0x2�������߷��ʵ�8~8.5GB��ַ����Ϊ3.5~4GB��ַ��
                                                          ע�⣺
                                                          1.��ȫģ���������Ȩ�޼��ʱ��ʹ�õĵ�ַ����λǰ��ԭʼ��ַ��
                                                          2.�˼Ĵ���ֻ����ϵͳ��ʼ��ʱ��̬���á� */
        unsigned int  reserved        : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DMSS_ASI_ADDR_SHIFT_UNION;
#endif
#define SOC_DMSS_ASI_ADDR_SHIFT_addr_shift_mode_START  (0)
#define SOC_DMSS_ASI_ADDR_SHIFT_addr_shift_mode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_RATE_ADPT_UNION
 �ṹ˵��  : ASI_RATE_ADPT �Ĵ����ṹ���塣��ַƫ����:0x030+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: д��������ƥ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_en       : 1;  /* bit[0]   : rate adapterʹ�ܣ�
                                                      0����ֹ������д�������κ����ƣ�
                                                      1��ʹ�ܣ�ֻ�е����յ�ָ����Ŀ��ra_trsfr_wl+1����д����transfer�������յ�wlast֮�󣬲��������Ӧ��д���������ģ�顣
                                                      ע�⣺
                                                      1.��ʹ��rate adapter��д�������Ƚ��յ����Ӧ��д����֮�󣬲ſ���󼶴��䣬�����Կɱ�����ASI֮��д�����д������������ܵ��µ�������ȡ���ھ����ϵͳ���ܣ���
                                                      2.�˼Ĵ��������Զ�̬���ã�������ܵ���ϵͳ������ */
        unsigned int  reserved_0  : 3;  /* bit[1-3] : ���� */
        unsigned int  ra_trsfr_wl : 4;  /* bit[4-7] : rate adapterˮ�����ã�
                                                      n�������յ���д����transfer�����ﵽn+1��ʱ�����Ӧ��д����ſ��Ա������󼶴���
                                                      ע�⣺
                                                      �˼Ĵ��������õ����ֵ��Ϊra_fifo����ȼ�һ�� */
        unsigned int  reserved_1  : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DMSS_ASI_RATE_ADPT_UNION;
#endif
#define SOC_DMSS_ASI_RATE_ADPT_ra_en_START        (0)
#define SOC_DMSS_ASI_RATE_ADPT_ra_en_END          (0)
#define SOC_DMSS_ASI_RATE_ADPT_ra_trsfr_wl_START  (4)
#define SOC_DMSS_ASI_RATE_ADPT_ra_trsfr_wl_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_RDR_CTRL0_UNION
 �ṹ˵��  : ASI_RDR_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x040+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���������0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdr_id_match : 32; /* bit[0-31]: ����ƥ��ID��
                                                       ��rdr_id_mask���ʹ�ã���cmd_id & rdr_id_mask = rdr_id_matchʱ����Ϊ��ǰcmd_id���ɹ�ƥ�䡣�ɹ�ƥ���ID�ɲ���򲻲��루ȡ����rdr_id_mode��ID����ļ�ء�
                                                       ע�⣺
                                                       1.ʵ�ʿ�����λ��ȡ����RTL��IDλ�����ã���ͨ��GLB_RTL_INF�Ĵ����в�ѯ��
                                                       2.�˼Ĵ��������Զ�̬���ã�������ܵ���ϵͳ������ */
    } reg;
} SOC_DMSS_ASI_RDR_CTRL0_UNION;
#endif
#define SOC_DMSS_ASI_RDR_CTRL0_rdr_id_match_START  (0)
#define SOC_DMSS_ASI_RDR_CTRL0_rdr_id_match_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_RDR_CTRL1_UNION
 �ṹ˵��  : ASI_RDR_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x044+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���������1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdr_id_mask : 32; /* bit[0-31]: ����ID���룺
                                                      ��rdr_id_match���ʹ�ã���cmd_id & rdr_id_mask = rdr_id_matchʱ����Ϊ��ǰcmd_id���ɹ�ƥ�䡣�ɹ�ƥ���ID�ɲ���򲻲��루ȡ����rdr_id_mode��ID����ļ�ء�
                                                      ע�⣺
                                                      1.ʵ�ʿ�����λ��ȡ����RTL��IDλ�����ã���ͨ��GLB_RTL_INF�Ĵ����в�ѯ��
                                                      2.�˼Ĵ��������Զ�̬���ã�������ܵ���ϵͳ������ */
    } reg;
} SOC_DMSS_ASI_RDR_CTRL1_UNION;
#endif
#define SOC_DMSS_ASI_RDR_CTRL1_rdr_id_mask_START  (0)
#define SOC_DMSS_ASI_RDR_CTRL1_rdr_id_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_RDR_CTRL2_UNION
 �ṹ˵��  : ASI_RDR_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x048+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���������2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdr_id_mode : 1;  /* bit[0]   : ����IDģʽ��
                                                      0:ƥ��ɹ���ID�����뱣���ж���
                                                      1:ƥ��ʧ�ܵ�ID�����뱣���ж��� */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DMSS_ASI_RDR_CTRL2_UNION;
#endif
#define SOC_DMSS_ASI_RDR_CTRL2_rdr_id_mode_START  (0)
#define SOC_DMSS_ASI_RDR_CTRL2_rdr_id_mode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_RBUF_INTLV0_UNION
 �ṹ˵��  : ASI_RBUF_INTLV0 �Ĵ����ṹ���塣��ַƫ����:0x060+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: RBUF�ļ��ģʽ����0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intlv_mid_0  : 2;  /* bit[0-1]  : ��MID��ֻʶ�������λ��Ϊ0�Ķ��������RBUF�����ݼ��ģʽ�����á�
                                                        0x0��0x1�����ģʽһ���յ���һ��transferʱ�����������󣨱�֤��������Сlatency����
                                                        0x2�����ģʽ�����յ����һ��transferʱ�����������󣨱�֤���ݲ�����壩��
                                                        0x3�����ģʽ�����յ������õ�transfer��������������transferʱ���������������������ο�������ʼˮ��ASI_RBUF_TRSFR_WL�Ĵ������������ã��ɱ�֤��β������Сlatency����
                                                        ˵����
                                                        ���ģʽ��ʱ�����ݴ�����ʼˮ�����ú�����д�뵽RBUF�����ʣ�
                                                        1.���ܱ�֤���ݷ��͹����У�����ʣ�����ݶ��ܼ�ʱд��RBUF�����䲻�ᱻ��壻
                                                        2.���ܱ�֤���ݷ��͵����һ��tansferʱ�����������ñ�д��RBUF�����ܱ�֤β���ݵ���Сlatency��RBUF��̬latencyΪ4��5cycles��ȡ����RTL���ã� */
        unsigned int  intlv_mid_1  : 2;  /* bit[2-3]  : ͬintlv_mid_0���� */
        unsigned int  intlv_mid_2  : 2;  /* bit[4-5]  : ͬintlv_mid_0���� */
        unsigned int  intlv_mid_3  : 2;  /* bit[6-7]  : ͬintlv_mid_0���� */
        unsigned int  intlv_mid_4  : 2;  /* bit[8-9]  : ͬintlv_mid_0���� */
        unsigned int  intlv_mid_5  : 2;  /* bit[10-11]: ͬintlv_mid_0���� */
        unsigned int  intlv_mid_6  : 2;  /* bit[12-13]: ͬintlv_mid_0���� */
        unsigned int  intlv_mid_7  : 2;  /* bit[14-15]: ͬintlv_mid_0���� */
        unsigned int  intlv_mid_8  : 2;  /* bit[16-17]: ͬintlv_mid_0���� */
        unsigned int  intlv_mid_9  : 2;  /* bit[18-19]: ͬintlv_mid_0���� */
        unsigned int  intlv_mid_10 : 2;  /* bit[20-21]: ͬintlv_mid_0���� */
        unsigned int  intlv_mid_11 : 2;  /* bit[22-23]: ͬintlv_mid_0���� */
        unsigned int  intlv_mid_12 : 2;  /* bit[24-25]: ͬintlv_mid_0���� */
        unsigned int  intlv_mid_13 : 2;  /* bit[26-27]: ͬintlv_mid_0���� */
        unsigned int  intlv_mid_14 : 2;  /* bit[28-29]: ͬintlv_mid_0���� */
        unsigned int  intlv_mid_15 : 2;  /* bit[30-31]: ͬintlv_mid_0���� */
    } reg;
} SOC_DMSS_ASI_RBUF_INTLV0_UNION;
#endif
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_0_START   (0)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_0_END     (1)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_1_START   (2)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_1_END     (3)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_2_START   (4)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_2_END     (5)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_3_START   (6)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_3_END     (7)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_4_START   (8)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_4_END     (9)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_5_START   (10)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_5_END     (11)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_6_START   (12)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_6_END     (13)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_7_START   (14)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_7_END     (15)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_8_START   (16)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_8_END     (17)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_9_START   (18)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_9_END     (19)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_10_START  (20)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_10_END    (21)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_11_START  (22)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_11_END    (23)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_12_START  (24)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_12_END    (25)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_13_START  (26)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_13_END    (27)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_14_START  (28)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_14_END    (29)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_15_START  (30)
#define SOC_DMSS_ASI_RBUF_INTLV0_intlv_mid_15_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_RBUF_INTLV1_UNION
 �ṹ˵��  : ASI_RBUF_INTLV1 �Ĵ����ṹ���塣��ַƫ����:0x064+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: RBUF�ļ��ģʽ����1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intlv_mid_16 : 2;  /* bit[0-1]  : ��MID��ֻʶ�������λ��Ϊ16�Ķ��������RBUF�����ݼ��ģʽ�����á�
                                                        0x0��0x1�����ģʽһ���յ���һ��transferʱ�����������󣨱�֤��������Сlatency����
                                                        0x2�����ģʽ�����յ����һ��transferʱ�����������󣨱�֤���ݲ�����壩��
                                                        0x3�����ģʽ�����յ������õ�transfer���������������transferʱ���������������������ο�������ʼˮ��ASI_RBUF_TRSFR_WL�Ĵ������������ã��ɱ�֤��β������Сlatency����
                                                        ˵����
                                                        ���ģʽ��ʱ�����ݴ�����ʼˮ�����ú�����д�뵽RBUF�����ʣ�
                                                        1.���ܱ�֤���ݷ��͹����У�����ʣ�����ݶ��ܼ�ʱд��RBUF�����䲻�ᱻ��壻
                                                        2.���ܱ�֤���ݷ��͵����һ��tansferʱ�����������ñ�д��RBUF�����ܱ�֤β���ݵ���Сlatency��RBUF��̬latencyΪ4��5cycles��ȡ����RTL���ã� */
        unsigned int  intlv_mid_17 : 2;  /* bit[2-3]  : ͬintlv_mid_16���� */
        unsigned int  intlv_mid_18 : 2;  /* bit[4-5]  : ͬintlv_mid_16���� */
        unsigned int  intlv_mid_19 : 2;  /* bit[6-7]  : ͬintlv_mid_16���� */
        unsigned int  intlv_mid_20 : 2;  /* bit[8-9]  : ͬintlv_mid_16���� */
        unsigned int  intlv_mid_21 : 2;  /* bit[10-11]: ͬintlv_mid_16���� */
        unsigned int  intlv_mid_22 : 2;  /* bit[12-13]: ͬintlv_mid_16���� */
        unsigned int  intlv_mid_23 : 2;  /* bit[14-15]: ͬintlv_mid_16���� */
        unsigned int  intlv_mid_24 : 2;  /* bit[16-17]: ͬintlv_mid_16���� */
        unsigned int  intlv_mid_25 : 2;  /* bit[18-19]: ͬintlv_mid_16���� */
        unsigned int  intlv_mid_26 : 2;  /* bit[20-21]: ͬintlv_mid_16���� */
        unsigned int  intlv_mid_27 : 2;  /* bit[22-23]: ͬintlv_mid_16���� */
        unsigned int  intlv_mid_28 : 2;  /* bit[24-25]: ͬintlv_mid_16���� */
        unsigned int  intlv_mid_29 : 2;  /* bit[26-27]: ͬintlv_mid_16���� */
        unsigned int  intlv_mid_30 : 2;  /* bit[28-29]: ͬintlv_mid_16���� */
        unsigned int  intlv_mid_31 : 2;  /* bit[30-31]: ͬintlv_mid_16���� */
    } reg;
} SOC_DMSS_ASI_RBUF_INTLV1_UNION;
#endif
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_16_START  (0)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_16_END    (1)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_17_START  (2)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_17_END    (3)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_18_START  (4)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_18_END    (5)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_19_START  (6)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_19_END    (7)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_20_START  (8)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_20_END    (9)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_21_START  (10)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_21_END    (11)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_22_START  (12)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_22_END    (13)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_23_START  (14)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_23_END    (15)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_24_START  (16)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_24_END    (17)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_25_START  (18)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_25_END    (19)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_26_START  (20)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_26_END    (21)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_27_START  (22)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_27_END    (23)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_28_START  (24)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_28_END    (25)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_29_START  (26)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_29_END    (27)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_30_START  (28)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_30_END    (29)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_31_START  (30)
#define SOC_DMSS_ASI_RBUF_INTLV1_intlv_mid_31_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_QOS_CTRL_UNION
 �ṹ˵��  : ASI_QOS_CTRL �Ĵ����ṹ���塣��ַƫ����:0x100+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ȼ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pri_push_en      : 1;  /* bit[0]    : �˿����ȼ�����ʹ�ܣ�
                                                            0����ֹ��
                                                            1��ʹ�ܡ�
                                                            ע�⣺
                                                            ���ȼ�����ʹ�ܺ󣬽�������ˮ�����Լ��ⲿ����Ķ�������е�������ȼ������ݸ���ǰ������˿��ٲõ�����԰��������Ӯ���ٲá��Ƿ�ı䱻����������������ȼ�ȡ����������arb_pri_use�� */
        unsigned int  push_qos_en      : 1;  /* bit[1]    : Pushed���ȼ�����ʹ�ܣ�
                                                            0����ֹ��
                                                            1��ʹ�ܡ�
                                                            ע�⣺
                                                            1.NOC���ߵ�Pressure�źţ������������߷�ѹʱ�������ȼ�������DMSS�ڲ������ȼ����ݣ�
                                                            2.��pri_push_en==1ʱ���˼Ĵ�����Ч�� */
        unsigned int  hurry_qos_en     : 1;  /* bit[2]    : Hurry���ȼ�����ʹ�ܣ�
                                                            0����ֹ��
                                                            1��ʹ�ܡ�
                                                            ע�⣺
                                                            1.NOC���ߵ�Hurry�źţ������κ�ʱ�̴������ȼ�������DMSS�ڲ������ȼ����ݣ�
                                                            2.��pri_push_en==1ʱ���˼Ĵ�����Ч�� */
        unsigned int  arb_pri_use      : 1;  /* bit[3]    : ʹ���ٲ����ȼ���Ϊ������������ȼ���
                                                            0����ֹ�������������ȼ�ֻ������AxQOS�źŵ�ӳ�䣬��regulator�����õ����ȼ���
                                                            1��ʹ�ܣ�����������Դ֮�⣬�����������ȼ��������������ȼ����ݺ����ȼ�����Ӧ�ȷ�ʽ�õ������ȼ��� */
        unsigned int  rw_arb_mode      : 1;  /* bit[4]    : ͬһ�˿��ڶ�д�����ٲ�ģʽ��
                                                            0�����������д���ͣ�
                                                             a.�ȵ����ٲã�
                                                             b.ͬʱ�����ͬʱ����ѹ��ʱ�������ȶ������д�����˳�������ٲã�
                                                            1�������������ȼ���
                                                             a.�ȵ����ٲã�
                                                             b.ͬʱ�����ͬʱ����ѹ��ʱ�������������ȼ��ٲã�
                                                             c.�����ȼ���ͬ������LRUԭ���ٲø���һ��δ����ٲõ���� */
        unsigned int  reserved_0       : 3;  /* bit[5-7]  : ���� */
        unsigned int  rw_arb_dis       : 1;  /* bit[8]    : ��д�����ٲý�ֹ��
                                                            0���������ж�д�ٲã�
                                                            1����ֹ��д�ٲã���ѹAXI���ߵĶ�д����� */
        unsigned int  reserved_1       : 3;  /* bit[9-11] : ���� */
        unsigned int  rd_wrap_split_en : 1;  /* bit[12]   : wrap��������ʹ�ܣ�
                                                            0������֣���DDRC�Զ����wrap���ݾ��ƣ�
                                                            1����֣��ӵ�ַ�����ϱ߽紦�������ֳ�����INCR��� */
        unsigned int  reserved_2       : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_DMSS_ASI_QOS_CTRL_UNION;
#endif
#define SOC_DMSS_ASI_QOS_CTRL_pri_push_en_START       (0)
#define SOC_DMSS_ASI_QOS_CTRL_pri_push_en_END         (0)
#define SOC_DMSS_ASI_QOS_CTRL_push_qos_en_START       (1)
#define SOC_DMSS_ASI_QOS_CTRL_push_qos_en_END         (1)
#define SOC_DMSS_ASI_QOS_CTRL_hurry_qos_en_START      (2)
#define SOC_DMSS_ASI_QOS_CTRL_hurry_qos_en_END        (2)
#define SOC_DMSS_ASI_QOS_CTRL_arb_pri_use_START       (3)
#define SOC_DMSS_ASI_QOS_CTRL_arb_pri_use_END         (3)
#define SOC_DMSS_ASI_QOS_CTRL_rw_arb_mode_START       (4)
#define SOC_DMSS_ASI_QOS_CTRL_rw_arb_mode_END         (4)
#define SOC_DMSS_ASI_QOS_CTRL_rw_arb_dis_START        (8)
#define SOC_DMSS_ASI_QOS_CTRL_rw_arb_dis_END          (8)
#define SOC_DMSS_ASI_QOS_CTRL_rd_wrap_split_en_START  (12)
#define SOC_DMSS_ASI_QOS_CTRL_rd_wrap_split_en_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_QOS_WRPRI_UNION
 �ṹ˵��  : ASI_QOS_WRPRI �Ĵ����ṹ���塣��ַƫ����:0x104+0x800*(asi_base)����ֵ:0x76543210�����:32
 �Ĵ���˵��: д�������ȼ�ӳ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_pri0  : 3;  /* bit[0-2]  : ��awqos[2:0]==0ʱ��д��������ȼ�����ֵ��
                                                    0x0��������ȼ���
                                                    ����
                                                    0x7��������ȼ��� */
        unsigned int  reserved_0: 1;  /* bit[3]    : ���� */
        unsigned int  wr_pri1  : 3;  /* bit[4-6]  : ��ͬwr_pri0������ */
        unsigned int  reserved_1: 1;  /* bit[7]    : ���� */
        unsigned int  wr_pri2  : 3;  /* bit[8-10] : ��ͬwr_pri0������ */
        unsigned int  reserved_2: 1;  /* bit[11]   : ���� */
        unsigned int  wr_pri3  : 3;  /* bit[12-14]: ��ͬwr_pri0������ */
        unsigned int  reserved_3: 1;  /* bit[15]   : ���� */
        unsigned int  wr_pri4  : 3;  /* bit[16-18]: ��ͬwr_pri0������ */
        unsigned int  reserved_4: 1;  /* bit[19]   : ���� */
        unsigned int  wr_pri5  : 3;  /* bit[20-22]: ��ͬwr_pri0������ */
        unsigned int  reserved_5: 1;  /* bit[23]   : ���� */
        unsigned int  wr_pri6  : 3;  /* bit[24-26]: ��ͬwr_pri0������ */
        unsigned int  reserved_6: 1;  /* bit[27]   : ���� */
        unsigned int  wr_pri7  : 3;  /* bit[28-30]: ��ͬwr_pri0������ */
        unsigned int  reserved_7: 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DMSS_ASI_QOS_WRPRI_UNION;
#endif
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri0_START   (0)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri0_END     (2)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri1_START   (4)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri1_END     (6)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri2_START   (8)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri2_END     (10)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri3_START   (12)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri3_END     (14)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri4_START   (16)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri4_END     (18)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri5_START   (20)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri5_END     (22)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri6_START   (24)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri6_END     (26)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri7_START   (28)
#define SOC_DMSS_ASI_QOS_WRPRI_wr_pri7_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_QOS_RDPRI_UNION
 �ṹ˵��  : ASI_QOS_RDPRI �Ĵ����ṹ���塣��ַƫ����:0x108+0x800*(asi_base)����ֵ:0x76543210�����:32
 �Ĵ���˵��: ���������ȼ�ӳ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_pri0  : 3;  /* bit[0-2]  : ��arqos[2:0]==0ʱ������������ȼ�����ֵ��
                                                    0x0��������ȼ���
                                                    ����
                                                    0x7��������ȼ��� */
        unsigned int  reserved_0: 1;  /* bit[3]    : ���� */
        unsigned int  rd_pri1  : 3;  /* bit[4-6]  : ��ͬrd_pri0������ */
        unsigned int  reserved_1: 1;  /* bit[7]    : ���� */
        unsigned int  rd_pri2  : 3;  /* bit[8-10] : ��ͬrd_pri0������ */
        unsigned int  reserved_2: 1;  /* bit[11]   : ���� */
        unsigned int  rd_pri3  : 3;  /* bit[12-14]: ��ͬrd_pri0������ */
        unsigned int  reserved_3: 1;  /* bit[15]   : ���� */
        unsigned int  rd_pri4  : 3;  /* bit[16-18]: ��ͬrd_pri0������ */
        unsigned int  reserved_4: 1;  /* bit[19]   : ���� */
        unsigned int  rd_pri5  : 3;  /* bit[20-22]: ��ͬrd_pri0������ */
        unsigned int  reserved_5: 1;  /* bit[23]   : ���� */
        unsigned int  rd_pri6  : 3;  /* bit[24-26]: ��ͬrd_pri0������ */
        unsigned int  reserved_6: 1;  /* bit[27]   : ���� */
        unsigned int  rd_pri7  : 3;  /* bit[28-30]: ��ͬrd_pri0������ */
        unsigned int  reserved_7: 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DMSS_ASI_QOS_RDPRI_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri0_START   (0)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri0_END     (2)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri1_START   (4)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri1_END     (6)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri2_START   (8)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri2_END     (10)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri3_START   (12)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri3_END     (14)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri4_START   (16)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri4_END     (18)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri5_START   (20)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri5_END     (22)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri6_START   (24)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri6_END     (26)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri7_START   (28)
#define SOC_DMSS_ASI_QOS_RDPRI_rd_pri7_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_QOS_ADPT_UNION
 �ṹ˵��  : ASI_QOS_ADPT �Ĵ����ṹ���塣��ַƫ����:0x10C+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ȼ�����Ӧ����ӳ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_adpt_low  : 4;  /* bit[0-3]  : ���������ȼ�����Ӧ�������ã��͵�λ��
                                                        0x0����ֹ���ȼ�����Ӧ���ܣ�
                                                        0x1��0xF��N��16��ʱ�����ڡ�
                                                        ˵����
                                                        ÿ������Ӧ���ڵ�����������ȼ��Զ�����һ����ֱ����������������ȼ������ȼ�6���� */
        unsigned int  rd_adpt_lvl  : 3;  /* bit[4-6]  : ���������ȼ�����Ӧ��������ˮ��
                                                        0x0��0x6���������ȼ����ڴ�ˮ��ʱ��ʹ�øߵ�λ���ã�����ʹ�õ͵�λ���ã�
                                                        0x7��reserved��
                                                        ������
                                                        0x3�����ȼ�4~5�Ķ�����ʹ��rd_pri_adpt_high�����ȼ�0��3�Ķ�����ʹ��rd_pri_adpt_low�� */
        unsigned int  reserved_0   : 1;  /* bit[7]    : ���� */
        unsigned int  rd_adpt_high : 4;  /* bit[8-11] : ���������ȼ�����Ӧ�������ã��ߵ�λ��
                                                        ͬrd_pri_adpt_low�����á� */
        unsigned int  reserved_1   : 4;  /* bit[12-15]: ���� */
        unsigned int  wr_adpt_low  : 4;  /* bit[16-19]: д�������ȼ�����Ӧ�������ã��͵�λ��
                                                        ͬrd_pri_adpt_low�����á� */
        unsigned int  wr_adpt_lvl  : 3;  /* bit[20-22]: д�������ȼ�����Ӧ��������ˮ��
                                                        ͬrd_pri_adpt_lvl�����á� */
        unsigned int  reserved_2   : 1;  /* bit[23]   : ���� */
        unsigned int  wr_adpt_high : 4;  /* bit[24-27]: д�������ȼ�����Ӧ�������ã��ߵ�λ��
                                                        ͬrd_pri_adpt_low�����á� */
        unsigned int  reserved_3   : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_DMSS_ASI_QOS_ADPT_UNION;
#endif
#define SOC_DMSS_ASI_QOS_ADPT_rd_adpt_low_START   (0)
#define SOC_DMSS_ASI_QOS_ADPT_rd_adpt_low_END     (3)
#define SOC_DMSS_ASI_QOS_ADPT_rd_adpt_lvl_START   (4)
#define SOC_DMSS_ASI_QOS_ADPT_rd_adpt_lvl_END     (6)
#define SOC_DMSS_ASI_QOS_ADPT_rd_adpt_high_START  (8)
#define SOC_DMSS_ASI_QOS_ADPT_rd_adpt_high_END    (11)
#define SOC_DMSS_ASI_QOS_ADPT_wr_adpt_low_START   (16)
#define SOC_DMSS_ASI_QOS_ADPT_wr_adpt_low_END     (19)
#define SOC_DMSS_ASI_QOS_ADPT_wr_adpt_lvl_START   (20)
#define SOC_DMSS_ASI_QOS_ADPT_wr_adpt_lvl_END     (22)
#define SOC_DMSS_ASI_QOS_ADPT_wr_adpt_high_START  (24)
#define SOC_DMSS_ASI_QOS_ADPT_wr_adpt_high_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_QOS_RGLR0_UNION
 �ṹ˵��  : ASI_QOS_RGLR0 �Ĵ����ṹ���塣��ַƫ����:0x120+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ȼ�����0
            ���ɵ������ƶ��������ȼ�����ͬʱ���ƶ�д�������ȼ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rglr_saturation : 14; /* bit[0-13] : �������ޣ�
                                                           ����ֵ=��������(B)/16��
                                                           ˵����
                                                           ���Խ���������Ʒ�ʽ��Ч�ɻ��ڻ������ڵ��������ƣ��������޾����˻�������Լ������ڵ�������������������(B)/�趨����ˮ��(B/Hz)=������ȣ�cycle�����������õ��趨����̶�������£���������Խ�󣬻���Խ���Կ���ǰ��˲ʱ����仯Խ�����У���ʱ����ƺ��ƽ������ҲԽ�ӽ����õ��������������ƺ��˲ʱ����ı仯Ҳ���ܻ�Խ���ҡ�
                                                           ע�⣺regulatorʹ��ʱ������������Ϊ0�� */
        unsigned int  reserved_0      : 2;  /* bit[14-15]: ���� */
        unsigned int  rglr_bandwidth  : 13; /* bit[16-28]: �趨��������
                                                           ����ֵ=�趨��������(B/Hz)*256=��������(MB/s)/����Ƶ�ʣ�MHz��*256
                                                           ���磺����Ƶ��Ϊ400MHz����ǰ�˿ڵ��趨����Ϊ1400MB/s�����������ֵΪ1400/400*256=896=0x380
                                                           ˵����
                                                           ��256��Ŀ���Ǳ����趨��������ĸ�8λС���� */
        unsigned int  reserved_1      : 1;  /* bit[29]   : ���� */
        unsigned int  rglr_type       : 1;  /* bit[30]   : �������ȼ����Ƶ��������ͣ�
                                                           0��ֻ���ƶ��������ȼ���
                                                           1��ͬʱ���ƶ�д�������ȼ���
                                                           ע�⣺
                                                           ������Ϊ��ͬʱ���ƶ�д�������ȼ���ʱ��ASI_QOS_RGLR1�����Զ���ֹʹ�á� */
        unsigned int  rglr_en         : 1;  /* bit[31]   : regulatorʹ�ܣ�
                                                           0����ֹ��
                                                           1��ʹ�ܡ� */
    } reg;
} SOC_DMSS_ASI_QOS_RGLR0_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_saturation_START  (0)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_saturation_END    (13)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_bandwidth_START   (16)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_bandwidth_END     (28)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_type_START        (30)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_type_END          (30)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_en_START          (31)
#define SOC_DMSS_ASI_QOS_RGLR0_rglr_en_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_QOS_RGLR0_PRI_UNION
 �ṹ˵��  : ASI_QOS_RGLR0_PRI �Ĵ����ṹ���塣��ַƫ����:0x124+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����������ȼ�0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rglr_pri0 : 3;  /* bit[0-2]  : ������δ�ﵽASI_QOS_RGLR0�����ô���ʱ����������ȼ�����ֵ��
                                                     0x0��������ȼ���
                                                     ����
                                                     0x7��������ȼ���
                                                     ע�⣺
                                                     ��rglr_type����Ϊ��ֻ���ƶ��������ȼ�������ֻ�ı�д�������ȼ���������Ϊ��ͬʱ���ƶ�д�������ȼ�������ͬʱ�ı����д�������ȼ��� */
        unsigned int  reserved_0: 5;  /* bit[3-7]  : ���� */
        unsigned int  rglr_pri1 : 3;  /* bit[8-10] : ������ﵽASI_QOS_RGLR0�����ô���ʱ����������ȼ�����ֵ��
                                                     0x0��������ȼ���
                                                     ����
                                                     0x7��������ȼ���
                                                     ע�⣺
                                                     ��rglr_type����Ϊ��ֻ���ƶ��������ȼ�������ֻ�ı�д�������ȼ���������Ϊ��ͬʱ���ƶ�д�������ȼ�������ͬʱ�ı����д�������ȼ��� */
        unsigned int  reserved_1: 21; /* bit[11-31]: ���� */
    } reg;
} SOC_DMSS_ASI_QOS_RGLR0_PRI_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RGLR0_PRI_rglr_pri0_START  (0)
#define SOC_DMSS_ASI_QOS_RGLR0_PRI_rglr_pri0_END    (2)
#define SOC_DMSS_ASI_QOS_RGLR0_PRI_rglr_pri1_START  (8)
#define SOC_DMSS_ASI_QOS_RGLR0_PRI_rglr_pri1_END    (10)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_QOS_RGLR1_UNION
 �ṹ˵��  : ASI_QOS_RGLR1 �Ĵ����ṹ���塣��ַƫ����:0x128+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ȼ�����1
            ��ֻ�ɵ�������д�������ȼ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rglr_saturation : 14; /* bit[0-13] : �������ޣ�
                                                           ����ֵ=��������(B)/16��
                                                           ˵����
                                                           ���Խ���������Ʒ�ʽ��Ч�ɻ��ڻ������ڵ��������ƣ��������޾����˻�������Լ������ڵ�������������������(B)/�趨����ˮ��(B/Hz)=������ȣ�cycle�����������õ��趨����̶�������£���������Խ�󣬻���Խ���Կ���ǰ��˲ʱ����仯Խ�����У���ʱ����ƺ��ƽ������ҲԽ�ӽ����õ��������������ƺ��˲ʱ����ı仯Ҳ���ܻ�Խ���ҡ�
                                                           ע�⣺regulatorʹ��ʱ������������Ϊ0�� */
        unsigned int  reserved_0      : 2;  /* bit[14-15]: ���� */
        unsigned int  rglr_bandwidth  : 13; /* bit[16-28]: �趨��������
                                                           ����ֵ=�趨��������(B/Hz)*256=��������(MB/s)/����Ƶ�ʣ�MHz��*256
                                                           ���磺����Ƶ��Ϊ400MHz����ǰ�˿ڵ��趨����Ϊ1400MB/s�����������ֵΪ1400/400*256=896=0x380
                                                           ˵����
                                                           ��256��Ŀ���Ǳ����趨��������ĸ�8λС���� */
        unsigned int  reserved_1      : 2;  /* bit[29-30]: ���� */
        unsigned int  rglr_en         : 1;  /* bit[31]   : regulatorʹ�ܣ�
                                                           0����ֹ��
                                                           1��ʹ�ܡ�
                                                           ע�⣺
                                                           1.ASI_QOS_RGLR1ֻ�ܿ���д����
                                                           2.��ASI_QOS_RGLR0����Ϊ��ͬʱ���ƶ�д�������ʱ��ASI_QOS_RGLR1�����Զ���ֹʹ�á� */
    } reg;
} SOC_DMSS_ASI_QOS_RGLR1_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RGLR1_rglr_saturation_START  (0)
#define SOC_DMSS_ASI_QOS_RGLR1_rglr_saturation_END    (13)
#define SOC_DMSS_ASI_QOS_RGLR1_rglr_bandwidth_START   (16)
#define SOC_DMSS_ASI_QOS_RGLR1_rglr_bandwidth_END     (28)
#define SOC_DMSS_ASI_QOS_RGLR1_rglr_en_START          (31)
#define SOC_DMSS_ASI_QOS_RGLR1_rglr_en_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_QOS_RGLR1_PRI_UNION
 �ṹ˵��  : ASI_QOS_RGLR1_PRI �Ĵ����ṹ���塣��ַƫ����:0x12C+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����������ȼ�1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rglr_pri0 : 3;  /* bit[0-2]  : ������δ�ﵽASI_QOS_RGLR0�����ô���ʱ��д��������ȼ�����ֵ��
                                                     0x0��������ȼ���
                                                     ����
                                                     0x7��������ȼ��� */
        unsigned int  reserved_0: 5;  /* bit[3-7]  : ���� */
        unsigned int  rglr_pri1 : 3;  /* bit[8-10] : ������ﵽASI_QOS_RGLR0�����ô���ʱ��д��������ȼ�����ֵ��
                                                     0x0��������ȼ���
                                                     ����
                                                     0x7��������ȼ��� */
        unsigned int  reserved_1: 21; /* bit[11-31]: ���� */
    } reg;
} SOC_DMSS_ASI_QOS_RGLR1_PRI_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RGLR1_PRI_rglr_pri0_START  (0)
#define SOC_DMSS_ASI_QOS_RGLR1_PRI_rglr_pri0_END    (2)
#define SOC_DMSS_ASI_QOS_RGLR1_PRI_rglr_pri1_START  (8)
#define SOC_DMSS_ASI_QOS_RGLR1_PRI_rglr_pri1_END    (10)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_QOS_LMTR0_UNION
 �ṹ˵��  : ASI_QOS_LMTR0 �Ĵ����ṹ���塣��ַƫ����:0x140+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������������0
            ���ɵ������ƶ�������ͬʱ���ƶ�д�ܴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lmtr_saturation : 14; /* bit[0-13] : �������ޣ�
                                                           ����ֵ=��������(B)/16��
                                                           ˵����
                                                           ���Խ���������Ʒ�ʽ��Ч�ɻ��ڻ������ڵ��������ƣ��������޾����˻�������Լ������ڵ�������������������(B)/����ƽ������(B/Hz)=������ȣ�cycle�����������õ�����ƽ������̶�������£���������Խ�󣬻���Խ���Կ���ǰ��˲ʱ����仯Խ�����У���ʱ����ƺ��ƽ������ҲԽ�ӽ����õ�����ƽ�����������ƺ��˲ʱ����ı仯Ҳ���ܻ�Խ���ҡ�
                                                           ���磬���������Ϊ���۴����1/3ʱ��Ϊ����˵��������һ�������Ӧһ�����ݣ���������λ��16B���������ʵ���ǿ�������������ݣ�����������������ֵΪ1��������������3�����������1������ͨ������������������ֵΪ2��������������6�����������2������ͨ��������2�����ݾͿ�������ͨ�����Դ����ơ�������Ӳ���ӳٵ����أ�����������޵���Ч����ֵ����Ϊ2��
                                                           ע�⣺��������ʹ��ʱ������������Ϊ0�� */
        unsigned int  reserved_0      : 2;  /* bit[14-15]: ���� */
        unsigned int  lmtr_bandwidth  : 13; /* bit[16-28]: ����ƽ������
                                                           ����ֵ=����ƽ������(B/Hz)*256=�������(MB/s)/����Ƶ�ʣ�MHz��*256
                                                           ���磺����Ƶ��Ϊ400MHz����ǰ�˿ڵ��������Ϊ1400MB/s�����������ֵΪ1400/400*256=896=0x380
                                                           ˵����
                                                           1.��256��Ŀ���Ǳ�������ƽ������ĸ�8λС����
                                                           2.���ƺ��˲ʱ������ܻᳬ��������������ķ�Χȡ���ڴ������޵����ã�
                                                           3.���ƺ�ĳ�ʱ��ƽ������С�ڵ�������ƽ������ */
        unsigned int  reserved_1      : 1;  /* bit[29]   : ���� */
        unsigned int  lmtr_type       : 1;  /* bit[30]   : �����������Ƶ��������ͣ�
                                                           0��ֻ���ƶ�����
                                                           1��ͬʱ���ƶ�д�ܴ���
                                                           ע�⣺
                                                           ������Ϊ��ͬʱ���ƶ�д�������ʱ��ASI_QOS_LMTR1�����Զ���ֹʹ�á� */
        unsigned int  lmtr_en         : 1;  /* bit[31]   : limiterʹ�ܣ�
                                                           0����ֹ��
                                                           1��ʹ�ܡ�
                                                           ע�⣺ */
    } reg;
} SOC_DMSS_ASI_QOS_LMTR0_UNION;
#endif
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_saturation_START  (0)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_saturation_END    (13)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_bandwidth_START   (16)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_bandwidth_END     (28)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_type_START        (30)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_type_END          (30)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_en_START          (31)
#define SOC_DMSS_ASI_QOS_LMTR0_lmtr_en_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_QOS_LMTR1_UNION
 �ṹ˵��  : ASI_QOS_LMTR1 �Ĵ����ṹ���塣��ַƫ����:0x144+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������������1
            ��ֻ�ɵ�������д����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lmtr_saturation : 14; /* bit[0-13] : �������ޣ�
                                                           ����ֵ=��������(B)/16��
                                                           ˵����
                                                           ���Խ���������Ʒ�ʽ��Ч�ɻ��ڻ������ڵ��������ƣ��������޾����˻�������Լ������ڵ�������������������(B)/����ƽ������(B/Hz)=������ȣ�cycle�����������õ�����ƽ������̶�������£���������Խ�󣬻���Խ���Կ���ǰ��˲ʱ����仯Խ�����У���ʱ����ƺ��ƽ������ҲԽ�ӽ����õ�����ƽ�����������ƺ��˲ʱ����ı仯Ҳ���ܻ�Խ���ҡ�
                                                           ���磬���������Ϊ���۴����1/3ʱ��Ϊ����˵��������һ�������Ӧһ�����ݣ���������λ��16B���������ʵ���ǿ�������������ݣ�����������������ֵΪ1��������������3�����������1������ͨ������������������ֵΪ2��������������6�����������2������ͨ��������2�����ݾͿ�������ͨ�����Դ����ơ�������Ӳ���ӳٵ����أ�����������޵���Ч����ֵ����Ϊ2��
                                                           ע�⣺��������ʹ��ʱ������������Ϊ0�� */
        unsigned int  reserved_0      : 2;  /* bit[14-15]: ���� */
        unsigned int  lmtr_bandwidth  : 13; /* bit[16-28]: ����ƽ������
                                                           ����ֵ=����ƽ������(B/Hz)*256=�������(MB/s)/����Ƶ�ʣ�MHz��*256
                                                           ���磺����Ƶ��Ϊ400MHz����ǰ�˿ڵ��������Ϊ1400MB/s�����������ֵΪ1400/400*256=896=0x380
                                                           ˵����
                                                           1.��256��Ŀ���Ǳ�������ƽ������ĸ�8λС����
                                                           2.���ƺ��˲ʱ������ܻᳬ��������������ķ�Χȡ���ڴ������޵����ã�
                                                           3.���ƺ�ĳ�ʱ��ƽ������С�ڵ�������ƽ������ */
        unsigned int  reserved_1      : 2;  /* bit[29-30]: ���� */
        unsigned int  lmtr_en         : 1;  /* bit[31]   : limiterʹ�ܣ�
                                                           0����ֹ��
                                                           1��ʹ�ܡ�
                                                           ע�⣺
                                                           1.ASI_QOS_LMTR1ֻ�ܿ���д����
                                                           2.��ASI_QOS_LMTR0����Ϊ��ͬʱ���ƶ�д�������ʱ��ASI_QOS_LMTR1�����Զ���ֹʹ�á� */
    } reg;
} SOC_DMSS_ASI_QOS_LMTR1_UNION;
#endif
#define SOC_DMSS_ASI_QOS_LMTR1_lmtr_saturation_START  (0)
#define SOC_DMSS_ASI_QOS_LMTR1_lmtr_saturation_END    (13)
#define SOC_DMSS_ASI_QOS_LMTR1_lmtr_bandwidth_START   (16)
#define SOC_DMSS_ASI_QOS_LMTR1_lmtr_bandwidth_END     (28)
#define SOC_DMSS_ASI_QOS_LMTR1_lmtr_en_START          (31)
#define SOC_DMSS_ASI_QOS_LMTR1_lmtr_en_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_QOS_RDOSTD_UNION
 �ṹ˵��  : ASI_QOS_RDOSTD �Ĵ����ṹ���塣��ַƫ����:0x160+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������OSTD����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_ostd_lvl : 8;  /* bit[0-7] : ������outstanding��OSTD��ˮ�ߣ�
                                                      0x00�������������OSTD������
                                                      0x01��0x7C���������������OSTD������
                                                      ע�⣺
                                                      1.��������outstanding�ﵽ�趨ˮ��ʱ���������ж����
                                                      2.д����������fast response�����ԣ��޷�׼ȷ������outstanding�� */
        unsigned int  reserved    : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DMSS_ASI_QOS_RDOSTD_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RDOSTD_rd_ostd_lvl_START  (0)
#define SOC_DMSS_ASI_QOS_RDOSTD_rd_ostd_lvl_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_QOS_RDOSTD_ST_UNION
 �ṹ˵��  : ASI_QOS_RDOSTD_ST �Ĵ����ṹ���塣��ַƫ����:0x164+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������OSTD״̬ͳ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_ostd_st : 8;  /* bit[0-7] : ������OSTDͳ��״̬�� */
        unsigned int  reserved   : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DMSS_ASI_QOS_RDOSTD_ST_UNION;
#endif
#define SOC_DMSS_ASI_QOS_RDOSTD_ST_rd_ostd_st_START  (0)
#define SOC_DMSS_ASI_QOS_RDOSTD_ST_rd_ostd_st_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_FLUX_STAT_CTRL_UNION
 �ṹ˵��  : ASI_FLUX_STAT_CTRL �Ĵ����ṹ���塣��ַƫ����:0x170+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͳ�ƿ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_stat_rd_en : 1;  /* bit[0]   : ���������ʹ�ܡ�
                                                          0���رգ�
                                                          1��ʹ�ܡ�
                                                          ˵����
                                                          1.����ͳ�ƽ����¼�������Ĵ���AXI_FLUX_STAT_RD�У�
                                                          2.�����Ĵ������������ƣ�
                                                          3.��������flux_stat_rd_en�������Ĵ����Զ����㡣 */
        unsigned int  flux_stat_wr_en : 1;  /* bit[1]   : д�������ʹ�ܡ�
                                                          0���رգ�
                                                          1��ʹ�ܡ�
                                                          ˵����
                                                          1.����ͳ�ƽ����¼�������Ĵ���AXI_FLUX_STAT_WR�У�
                                                          2.�����Ĵ������������ƣ�
                                                          3.��������flux_stat_wr_en�������Ĵ����Զ����㡣 */
        unsigned int  reserved        : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DMSS_ASI_FLUX_STAT_CTRL_UNION;
#endif
#define SOC_DMSS_ASI_FLUX_STAT_CTRL_flux_stat_rd_en_START  (0)
#define SOC_DMSS_ASI_FLUX_STAT_CTRL_flux_stat_rd_en_END    (0)
#define SOC_DMSS_ASI_FLUX_STAT_CTRL_flux_stat_wr_en_START  (1)
#define SOC_DMSS_ASI_FLUX_STAT_CTRL_flux_stat_wr_en_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_FLUX_STAT_WR_UNION
 �ṹ˵��  : ASI_FLUX_STAT_WR �Ĵ����ṹ���塣��ַƫ����:0x178+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: д����ͳ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_stat_wr : 32; /* bit[0-31]: д����ͳ�ƣ������ASI_FLUX_STAT_CTRL�Ĵ���ʹ�ã���
                                                       ˵����
                                                       1.�ۼ�����д�����Ӧ��������������λΪByte��
                                                       2.����һ��ͳ�ƿ�ʼʱ�Զ����㣻
                                                       3.�������Ƽ�����
                                                       4.32bit��������������Ϊ4GB�� */
    } reg;
} SOC_DMSS_ASI_FLUX_STAT_WR_UNION;
#endif
#define SOC_DMSS_ASI_FLUX_STAT_WR_flux_stat_wr_START  (0)
#define SOC_DMSS_ASI_FLUX_STAT_WR_flux_stat_wr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_FLUX_STAT_RD_UNION
 �ṹ˵��  : ASI_FLUX_STAT_RD �Ĵ����ṹ���塣��ַƫ����:0x17C+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ͳ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_stat_rd : 32; /* bit[0-31]: ������ͳ�ƣ������ASI_FLUX_STAT_CTRL�Ĵ���ʹ�ã���
                                                       ˵����
                                                       1.�ۼ����ж������Ӧ��������������λΪByte��
                                                       2.����һ��ͳ�ƿ�ʼʱ�Զ����㣻
                                                       3.�������Ƽ�����
                                                       4.32bit��������������Ϊ4GB�� */
    } reg;
} SOC_DMSS_ASI_FLUX_STAT_RD_UNION;
#endif
#define SOC_DMSS_ASI_FLUX_STAT_RD_flux_stat_rd_START  (0)
#define SOC_DMSS_ASI_FLUX_STAT_RD_flux_stat_rd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_PUSH_WRMID_UNION
 �ṹ˵��  : ASI_PUSH_WRMID �Ĵ����ṹ���塣��ַƫ����:0x180+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: д����ͬMID�������ȼ�����ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_mid_sel : 32; /* bit[0-31]: д����MID�������λ���ı���ƥ��ѡ��
                                                     wr_mid_sel[n]=0������MID=n�������QOSBUF�н�ֹͬMIDд�������ȼ����ݹ��ܣ�
                                                     wr_mid_sel[n]=1������MID=n�������QOSBUF��ʹ��ͬMIDд�������ȼ����ݹ��ܡ� */
    } reg;
} SOC_DMSS_ASI_PUSH_WRMID_UNION;
#endif
#define SOC_DMSS_ASI_PUSH_WRMID_wr_mid_sel_START  (0)
#define SOC_DMSS_ASI_PUSH_WRMID_wr_mid_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_PUSH_RDMID_UNION
 �ṹ˵��  : ASI_PUSH_RDMID �Ĵ����ṹ���塣��ַƫ����:0x184+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ͬMID�������ȼ�����ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_mid_sel : 32; /* bit[0-31]: ������MID�������λ���ı���ƥ��ѡ��
                                                     rd_mid_sel[n]=0������MID=n�������QOSBUF�н�ֹͬMID���������ȼ����ݹ��ܣ�
                                                     rd_mid_sel[n]=1������MID=n�������QOSBUF��ʹ��ͬMID���������ȼ����ݹ��ܡ� */
    } reg;
} SOC_DMSS_ASI_PUSH_RDMID_UNION;
#endif
#define SOC_DMSS_ASI_PUSH_RDMID_rd_mid_sel_START  (0)
#define SOC_DMSS_ASI_PUSH_RDMID_rd_mid_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_LD_SEL_UNION
 �ṹ˵��  : ASI_SEC_LD_SEL �Ĵ����ṹ���塣��ַƫ����:0x410+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ȫ����������üĴ���
            ����secur_boot_lock�źű����߳���һ��ʱ������ʱ���˼Ĵ���������ѡ������ؼĴ���������Ϊֻ����ֻ��ͨ��ϵͳ��λ���������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ld_rgn_map    : 1;  /* bit[0]    : ����sucure_boot_lock�źź�������ld_rgns_selѡ��region��ASI_SEC_REGION_MAP�Ĵ���Ϊֻ����
                                                         0����������
                                                         1��������
                                                         ���Ĵ�����������������sucure_boot_lock�źű����߹��� */
        unsigned int  ld_rgn_attrib : 1;  /* bit[1]    : ����sucure_boot_lock�źź�������ld_rgns_selѡ��region��ASI_SEC_REGION_ATTRIB�Ĵ���Ϊֻ����
                                                         0����������
                                                         1��������
                                                         ���Ĵ�����������������sucure_boot_lock�źű����߹��� */
        unsigned int  ld_mid_rd     : 1;  /* bit[2]    : ����sucure_boot_lock�źź�������ld_rgns_selѡ��region��ASI_SEC_MID_RD�Ĵ���Ϊֻ����
                                                         0����������
                                                         1��������
                                                         ���Ĵ�����������������sucure_boot_lock�źű����߹��� */
        unsigned int  ld_mid_wr     : 1;  /* bit[3]    : ����sucure_boot_lock�źź�������ld_rgns_selѡ��region��ASI_SEC_MID_WR�Ĵ���Ϊֻ����
                                                         0����������
                                                         1��������
                                                         ���Ĵ�����������������sucure_boot_lock�źű����߹��� */
        unsigned int  reserved_0    : 12; /* bit[4-15] : ���� */
        unsigned int  ld_rgns_sel   : 5;  /* bit[16-20]: ѡ���轫������üĴ�������Ϊֻ����regions��Χ��
                                                         sec_ld_rgns_sel=N�������λ��ѡ��������N+1��rgn��
                                                         ������
                                                         sec_ld_rgns_sel=5��rgn15~rgn10����ؼĴ�����ѡ��������no_of_rgns=16����
                                                         ע�⣺
                                                         1.��ѡ����rgn��������ʵ��rgn����no_of_rgns����ѡ��ȫ��rgn��
                                                         2.��ĳrgn��ѡ������ld_mid_wr/ld_mid_rd/lg_rgn_attrib/ld_rgn_map����Ϊ���������rgn��Ӧ������������üĴ����Ա�ѡ����
                                                         ��1��ASI_SEC_RGN_MAP��
                                                         ��2��ASI_SEC_RGN_ATTRIB��
                                                         ��3��ASI_SEC_MID_WR��
                                                         ��4��ASI_SEC_MID_RD��
                                                         ���Ĵ�����������������sucure_boot_lock�źű����߹��� */
        unsigned int  reserved_1    : 11; /* bit[21-31]: ���� */
    } reg;
} SOC_DMSS_ASI_SEC_LD_SEL_UNION;
#endif
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_rgn_map_START     (0)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_rgn_map_END       (0)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_rgn_attrib_START  (1)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_rgn_attrib_END    (1)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_mid_rd_START      (2)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_mid_rd_END        (2)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_mid_wr_START      (3)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_mid_wr_END        (3)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_rgns_sel_START    (16)
#define SOC_DMSS_ASI_SEC_LD_SEL_ld_rgns_sel_END      (20)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_INT_EN_UNION
 �ṹ˵��  : ASI_SEC_INT_EN �Ĵ����ṹ���塣��ַƫ����:0x420+0x800*(asi_base)����ֵ:0x00000001�����:32
 �Ĵ���˵��: ��ȫ�ж�ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_en   : 1;  /* bit[0]   : ԽȨ������ж����ʹ�ܡ�
                                                   0����ֹ��
                                                   1��ʹ�ܡ�
                                                   ˵����
                                                   1.����ԽȨ�������ʱ�����ϱ��жϲ���¼ԽȨ������Ϣ����ο�ASI_SEC_FAIL_CMD_INF�Ĵ�������
                                                   2.ֻ�ܽ�ֹ�ж����������ؼĴ������ǻ�������¼�ж�״̬��ԽȨ������Ϣ�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DMSS_ASI_SEC_INT_EN_UNION;
#endif
#define SOC_DMSS_ASI_SEC_INT_EN_int_en_START    (0)
#define SOC_DMSS_ASI_SEC_INT_EN_int_en_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_INT_STATUS_UNION
 �ṹ˵��  : ASI_SEC_INT_STATUS �Ĵ����ṹ���塣��ַƫ����:0x424+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫ�ж�״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_status  : 1;  /* bit[0]   : �ж�״ָ̬ʾ
                                                      0���ж�δ������
                                                      1���ж��Ѳ�����
                                                      ע�⣺��GLOBALģ���GLB_INT_STATUS�Ĵ����У���ʶ����ж��������ĸ�ASI�е�SECģ�� */
        unsigned int  int_overrun : 1;  /* bit[1]   : ����ж�ָʾ
                                                      0���ж�δ������ֻ������һ�Σ�
                                                      1���ж��Ѳ�����Ρ� */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DMSS_ASI_SEC_INT_STATUS_UNION;
#endif
#define SOC_DMSS_ASI_SEC_INT_STATUS_int_status_START   (0)
#define SOC_DMSS_ASI_SEC_INT_STATUS_int_status_END     (0)
#define SOC_DMSS_ASI_SEC_INT_STATUS_int_overrun_START  (1)
#define SOC_DMSS_ASI_SEC_INT_STATUS_int_overrun_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_FAIL_CMD_INF0_UNION
 �ṹ˵��  : ASI_SEC_FAIL_CMD_INF0 �Ĵ����ṹ���塣��ַƫ����:0x480+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��¼�׸�ԽȨ�������Ϣ0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_low : 32; /* bit[0-31]: �ж�״̬���ǰ���׸�ԽȨ����ĵ�32λ��ַ */
    } reg;
} SOC_DMSS_ASI_SEC_FAIL_CMD_INF0_UNION;
#endif
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF0_address_low_START  (0)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF0_address_low_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_UNION
 �ṹ˵��  : ASI_SEC_FAIL_CMD_INF1 �Ĵ����ṹ���塣��ַƫ����:0x484+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��¼�׸�ԽȨ�������Ϣ1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_high : 8;  /* bit[0-7]  : �ж�״̬���ǰ���׸�ԽȨ����ĸ�λ��ַ��������ڸ�λ��ַ�� */
        unsigned int  reserved_0   : 8;  /* bit[8-15] : ���� */
        unsigned int  privileged   : 1;  /* bit[16]   : �ж�״̬���ǰ�׸�ԽȨ�������Ȩģʽ��Ϣ
                                                        0��unprivileged���ʣ�
                                                        1��privileged���ʡ� */
        unsigned int  nonsecure    : 1;  /* bit[17]   : �ж�״̬���ǰ�׸�ԽȨ����İ�ȫģʽ��Ϣ
                                                        0��secure���ʣ�
                                                        1��non-secure���ʡ� */
        unsigned int  reserved_1   : 2;  /* bit[18-19]: ���� */
        unsigned int  access_type  : 1;  /* bit[20]   : �ж�״̬���ǰ�׸�ԽȨ����Ķ�дģʽ��Ϣ
                                                        0��read���ʣ�
                                                        1��write���ʡ� */
        unsigned int  reserved_2   : 11; /* bit[21-31]: ���� */
    } reg;
} SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_UNION;
#endif
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_address_high_START  (0)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_address_high_END    (7)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_privileged_START    (16)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_privileged_END      (16)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_nonsecure_START     (17)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_nonsecure_END       (17)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_access_type_START   (20)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF1_access_type_END     (20)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_UNION
 �ṹ˵��  : ASI_SEC_FAIL_CMD_INF2 �Ĵ����ṹ���塣��ַƫ����:0x488+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��¼�׸�ԽȨ�������Ϣ2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id  : 24; /* bit[0-23] : �ж�״̬���ǰ���׸�ԽȨ���������ID */
        unsigned int  mid : 8;  /* bit[24-31]: �ж�״̬���ǰ���׸�ԽȨ���������MasterID */
    } reg;
} SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_UNION;
#endif
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_id_START   (0)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_id_END     (23)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_mid_START  (24)
#define SOC_DMSS_ASI_SEC_FAIL_CMD_INF2_mid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_ITCRG_UNION
 �ṹ˵��  : ASI_SEC_ITCRG �Ĵ����ṹ���塣��ַƫ����:0x4C0+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ɲ��Կ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_test_en : 1;  /* bit[0]   : �жϲ���ʹ�ܡ�
                                                      0����ֹ��
                                                      1��ʹ�ܡ�
                                                      ע�⣺ʹ�ܴ˼Ĵ�����ģ����ж��������SEC_ITOP�Ĵ������þ����� */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DMSS_ASI_SEC_ITCRG_UNION;
#endif
#define SOC_DMSS_ASI_SEC_ITCRG_int_test_en_START  (0)
#define SOC_DMSS_ASI_SEC_ITCRG_int_test_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_ITIP_UNION
 �ṹ˵��  : ASI_SEC_ITIP �Ĵ����ṹ���塣��ַƫ����:0x4C4+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ɲ�������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itip_secure_boot_lock : 1;  /* bit[0]   : �Ĵ�������������״ָ̬ʾ��
                                                                0��δ������
                                                                1���������� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DMSS_ASI_SEC_ITIP_UNION;
#endif
#define SOC_DMSS_ASI_SEC_ITIP_itip_secure_boot_lock_START  (0)
#define SOC_DMSS_ASI_SEC_ITIP_itip_secure_boot_lock_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_ITOP_UNION
 �ṹ˵��  : ASI_SEC_ITOP �Ĵ����ṹ���塣��ַƫ����:0x4C8+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ɲ�������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itop_int : 1;  /* bit[0]   : �ж�״̬���á�
                                                   0���͵�ƽ��
                                                   1���ߵ�ƽ��
                                                   ע�⣺ֻ�е��жϲ���ʹ��ʱ���˼Ĵ���������Ч����ʱ����ģ���ڲ������������жϡ� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DMSS_ASI_SEC_ITOP_UNION;
#endif
#define SOC_DMSS_ASI_SEC_ITOP_itop_int_START  (0)
#define SOC_DMSS_ASI_SEC_ITOP_itop_int_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_RGN_MAP_UNION
 �ṹ˵��  : ASI_SEC_RGN_MAP �Ĵ����ṹ���塣��ַƫ����:0x500+0x10*(sec_rgns)+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ַ����ӳ��
            ��������������sucure_boot_lock�źű����߹�����ld_region_map����Ϊ1���Ҷ�Ӧregion��ld_regions��ѡ����Χ�ڡ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rgn_base_addr : 24; /* bit[0-23] : �����������ʼ��ַ���ã���λ���֣�
                                                         ���õ�ַ��[39:16]λ��
                                                         ע�⣺
                                                         1.rgn0�������ã�Ĭ�ϸ���������ַ�ռ䣻
                                                         2.�豣֤exclusive������ʵĵ�ַ��������Ӧ�ķ���Ȩ�ޣ�����exclusive�����޷���������ء� */
        unsigned int  rgn_size      : 6;  /* bit[24-29]: ��ǰ����Ĵ�С��
                                                         6'd15�� 64KB��
                                                         6'd16��128KB����ʱrgn_base_addr[ 0]��������Ϊ�㣻
                                                         6'd17��256KB����ʱrgn_base_addr[ 1:0]��������Ϊ�㣻
                                                         6'd18��512KB����ʱrgn_base_addr[ 2:0]��������Ϊ�㣻
                                                         6'd19�� 1MB����ʱrgn_base_addr[ 3:0]��������Ϊ�㣻
                                                         6'd20�� 2MB����ʱrgn_base_addr[ 4:0]��������Ϊ�㣻
                                                         6'd21�� 4MB����ʱrgn_base_addr[ 5:0]��������Ϊ�㣻
                                                         6'd22�� 8MB����ʱrgn_base_addr[ 6:0]��������Ϊ�㣻
                                                         6'd23�� 16MB����ʱrgn_base_addr[ 7:0]��������Ϊ�㣻
                                                         6'd24�� 32MB����ʱrgn_base_addr[ 8:0]��������Ϊ�㣻
                                                         6'd25�� 64MB����ʱrgn_base_addr[ 9:0]��������Ϊ�㣻
                                                         6'd26��128MB����ʱrgn_base_addr[10:0]��������Ϊ�㣻
                                                         6'd27��256MB����ʱrgn_base_addr[11:0]��������Ϊ�㣻
                                                         6'd28��512MB����ʱrgn_base_addr[12:0]��������Ϊ�㣻
                                                         6'd29�� 1GB����ʱrgn_base_addr[13:0]��������Ϊ�㣻
                                                         6'd30�� 2GB����ʱrgn_base_addr[14:0]��������Ϊ�㣻
                                                         6'd31�� 4GB����ʱrgn_base_addr[15:0]��������Ϊ�㣻
                                                         6'd32�� 8GB����ʱrgn_base_addr[16:0]��������Ϊ�㣻
                                                         6'd33�� 16GB����ʱrgn_base_addr[17:0]��������Ϊ�㣻
                                                         6'd34�� 32GB����ʱrgn_base_addr[18:0]��������Ϊ�㣻
                                                         6'd35�� 64GB����ʱrgn_base_addr[19:0]��������Ϊ�㣻
                                                         6'd36��128GB����ʱrgn_base_addr[20:0]��������Ϊ�㣻
                                                         6'd37��256GB����ʱrgn_base_addr[21:0]��������Ϊ�㣻
                                                         6'd38��512GB����ʱrgn_base_addr[22:0]��������Ϊ�㣻
                                                         6'd39��1TB�� ��ʱrgn_base_addr[23:0]��������Ϊ�㡣
                                                         ע�⣺
                                                         1.rgn0�������ã�Ĭ�ϸ���������ַ�ռ䣻
                                                         2.Ϊÿ���������õ������С���ۼ�����������ʼ��ַ�󣬲��������ܵĵ�ַ�ռ��С�� */
        unsigned int  reserved      : 1;  /* bit[30]   : ���� */
        unsigned int  rgn_en        : 1;  /* bit[31]   : ���������ʹ�ܿ���
                                                         0����ʹ�ܣ�
                                                         1��ʹ�ܣ�
                                                         ע�⣺region0�������ã�Ĭ��ʹ�ܡ� */
    } reg;
} SOC_DMSS_ASI_SEC_RGN_MAP_UNION;
#endif
#define SOC_DMSS_ASI_SEC_RGN_MAP_rgn_base_addr_START  (0)
#define SOC_DMSS_ASI_SEC_RGN_MAP_rgn_base_addr_END    (23)
#define SOC_DMSS_ASI_SEC_RGN_MAP_rgn_size_START       (24)
#define SOC_DMSS_ASI_SEC_RGN_MAP_rgn_size_END         (29)
#define SOC_DMSS_ASI_SEC_RGN_MAP_rgn_en_START         (31)
#define SOC_DMSS_ASI_SEC_RGN_MAP_rgn_en_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_RGN_ATTRIB_UNION
 �ṹ˵��  : ASI_SEC_RGN_ATTRIB �Ĵ����ṹ���塣��ַƫ����:0x504+0x10*(sec_rgns)+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ַ�����Ȩ����������
            ��������������sucure_boot_lock�źű����߹�����ld_region_attrib����Ϊ1���Ҷ�Ӧregion��ld_regions��ѡ����Χ�ڡ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sp             : 4;  /* bit[0-3]  : ��ǰ����İ�ȫȨ�����ԡ�
                                                          sp[3]����ȫ�����ԣ�
                                                          sp[2]����ȫд���ԣ�
                                                          sp[1]���ǰ�ȫ�����ԣ�
                                                          sp[0]���ǰ�ȫд���ԣ�
                                                          sp[n]=0����ֹ���ʣ�
                                                          sp[n]=1��������ʡ� */
        unsigned int  security_inv   : 1;  /* bit[4]    : ��ȫȨ�޷�תʹ��
                                                          0����ֹ����ĳregion����ǰ�ȫ�Ķ�/д����Ҳ�ض�����ȫ�Ķ�/д��
                                                          1��ʹ�ܣ��ǰ�ȫ��/д�Ͱ�ȫ��/дȨ��֮����������ϵ��������趨�� */
        unsigned int  reserved_0     : 3;  /* bit[5-7]  : ���� */
        unsigned int  mid_en         : 1;  /* bit[8]    : MasterIDƥ�书��ʹ�ܡ�
                                                          0����ֹ��
                                                          1��ʹ�ܡ� */
        unsigned int  mid_inv        : 1;  /* bit[9]    : MasterIDƥ��Ȩ�޷�ת
                                                          0��MIDƥ��ɹ�������ſɻ�÷���Ȩ�ޣ�
                                                          1��MIDƥ��ʧ�ܵ�����ſɻ�÷���Ȩ�ޡ� */
        unsigned int  reserved_1     : 6;  /* bit[10-15]: ���� */
        unsigned int  subrgn_disable : 16; /* bit[16-31]: ��ǰ�����16���ȴ�����������Ρ�
                                                          subrgn_disable[n]=0��������nʹ�ܣ���ǰ�������ڵ�����Ȩ�ޣ�ȡ���ڵ�ǰrgn����
                                                          subrgn_disable[n]=1��������n���Σ���ǰ�������ڵ�����Ȩ�ޣ�ȡ���ڸ������ȼ�rgn����
                                                          ע�⣺
                                                          rgn0��������������Ĭ�ϸ���������ַ�ռ䡣 */
    } reg;
} SOC_DMSS_ASI_SEC_RGN_ATTRIB_UNION;
#endif
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_sp_START              (0)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_sp_END                (3)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_security_inv_START    (4)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_security_inv_END      (4)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_mid_en_START          (8)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_mid_en_END            (8)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_mid_inv_START         (9)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_mid_inv_END           (9)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_subrgn_disable_START  (16)
#define SOC_DMSS_ASI_SEC_RGN_ATTRIB_subrgn_disable_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_MID_WR_UNION
 �ṹ˵��  : ASI_SEC_MID_WR �Ĵ����ṹ���塣��ַƫ����:0x508+0x10*(sec_rgns)+0x800*(asi_base)����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: д����ƥ��MasterID��������
            ��������������sucure_boot_lock�źű����߹�����ld_mid_wr����Ϊ1���Ҷ�Ӧregion��ld_regions��ѡ����Χ�ڡ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mid_sel_wr : 32; /* bit[0-31]: MID�ı���ƥ��ѡ��д�����
                                                     mid_sel_wr[n]=0��д����MID�ĵ���λΪnʱ��������ΪMIDƥ��ʧ�ܣ�
                                                     mid_sel_wr[n]=1��д����MID�ĵ���λΪnʱ��������ΪMIDƥ��ɹ���
                                                     ˵����
                                                     ��ʹ��MIDƥ�书��ʱ��ֻ�е�MID�ɹ�ƥ���һ�ð�ȫȨ��ʱ����Ӧ�����������ͨ���� */
    } reg;
} SOC_DMSS_ASI_SEC_MID_WR_UNION;
#endif
#define SOC_DMSS_ASI_SEC_MID_WR_mid_sel_wr_START  (0)
#define SOC_DMSS_ASI_SEC_MID_WR_mid_sel_wr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_SEC_MID_RD_UNION
 �ṹ˵��  : ASI_SEC_MID_RD �Ĵ����ṹ���塣��ַƫ����:0x50C+0x10*(sec_rgns)+0x800*(asi_base)����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: ������ƥ��MasterID��������
            ��������������sucure_boot_lock�źű����߹�����ld_mid_rd����Ϊ1���Ҷ�Ӧregion��ld_regions��ѡ����Χ�ڡ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mid_sel_rd : 32; /* bit[0-31]: MID�ı���ƥ��ѡ�񣨶������
                                                     mid_sel_rd[n]=0��������MID�ĵ���λΪnʱ��������ΪMIDƥ��ʧ�ܣ�
                                                     mid_sel_rd[n]=1��������MID�ĵ���λΪnʱ��������ΪMIDƥ��ɹ���
                                                     ˵����
                                                     ��ʹ��MIDƥ�书��ʱ��ֻ�е�MID�ɹ�ƥ���һ�ð�ȫȨ��ʱ����Ӧ�����������ͨ���� */
    } reg;
} SOC_DMSS_ASI_SEC_MID_RD_UNION;
#endif
#define SOC_DMSS_ASI_SEC_MID_RD_mid_sel_rd_START  (0)
#define SOC_DMSS_ASI_SEC_MID_RD_mid_sel_rd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_DFX_MODULE_UNION
 �ṹ˵��  : ASI_DFX_MODULE �Ĵ����ṹ���塣��ַƫ����:0x700+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX����Ҫģ�鹤��״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asi_busy      : 1;  /* bit[0]    : ����ASI��״̬��
                                                         0��idle��
                                                         1��busy��
                                                         ˵����
                                                         idleʱ��������ģ�����idle��δ�����첽��״̬������������������ݾ��Ѵ�����ϡ� */
        unsigned int  asi_temp_busy : 1;  /* bit[1]    : ����ASI��״̬��
                                                         0��idle��
                                                         1��busy��
                                                         ˵����
                                                         idleʱ��������ģ�����idle��δ�����첽��״̬�����������ж����ݻ�δ�Ӻ�ģ�鷵�ء� */
        unsigned int  reserved_0    : 2;  /* bit[2-3]  : ���� */
        unsigned int  ra_busy       : 1;  /* bit[4]    : ASI_RAģ���״̬��
                                                         0��idle��
                                                         1��busy�� */
        unsigned int  ax_busy       : 1;  /* bit[5]    : ASI_AXģ���״̬��
                                                         0��idle��
                                                         1��busy�� */
        unsigned int  cs_busy       : 1;  /* bit[6]    : ASI_CSģ���״̬��
                                                         0��idle��
                                                         1��busy�� */
        unsigned int  wd_busy       : 1;  /* bit[7]    : ASI_WDģ���״̬��
                                                         0��idle��
                                                         1��busy�� */
        unsigned int  b_busy        : 1;  /* bit[8]    : ASI_Bģ���״̬��
                                                         0��idle��
                                                         1��busy�� */
        unsigned int  rd_busy       : 1;  /* bit[9]    : ASI_RDģ���״̬��
                                                         0��idle��
                                                         1��busy�� */
        unsigned int  fkrd_busy     : 1;  /* bit[10]   : ASI_FKRDģ���״̬��
                                                         0��idle��
                                                         1��busy�� */
        unsigned int  sec_busy      : 1;  /* bit[11]   : ASI_SECģ���״̬��
                                                         0��idle��
                                                         1��busy�� */
        unsigned int  rdr_est_busy  : 1;  /* bit[12]   : RDR_ESTģ���״̬��
                                                         0��idle��
                                                         1��busy�� */
        unsigned int  rdr_buf_busy  : 1;  /* bit[13]   : RDR_BUFģ���״̬��
                                                         0��idle��
                                                         1��busy�� */
        unsigned int  reserved_1    : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DMSS_ASI_DFX_MODULE_UNION;
#endif
#define SOC_DMSS_ASI_DFX_MODULE_asi_busy_START       (0)
#define SOC_DMSS_ASI_DFX_MODULE_asi_busy_END         (0)
#define SOC_DMSS_ASI_DFX_MODULE_asi_temp_busy_START  (1)
#define SOC_DMSS_ASI_DFX_MODULE_asi_temp_busy_END    (1)
#define SOC_DMSS_ASI_DFX_MODULE_ra_busy_START        (4)
#define SOC_DMSS_ASI_DFX_MODULE_ra_busy_END          (4)
#define SOC_DMSS_ASI_DFX_MODULE_ax_busy_START        (5)
#define SOC_DMSS_ASI_DFX_MODULE_ax_busy_END          (5)
#define SOC_DMSS_ASI_DFX_MODULE_cs_busy_START        (6)
#define SOC_DMSS_ASI_DFX_MODULE_cs_busy_END          (6)
#define SOC_DMSS_ASI_DFX_MODULE_wd_busy_START        (7)
#define SOC_DMSS_ASI_DFX_MODULE_wd_busy_END          (7)
#define SOC_DMSS_ASI_DFX_MODULE_b_busy_START         (8)
#define SOC_DMSS_ASI_DFX_MODULE_b_busy_END           (8)
#define SOC_DMSS_ASI_DFX_MODULE_rd_busy_START        (9)
#define SOC_DMSS_ASI_DFX_MODULE_rd_busy_END          (9)
#define SOC_DMSS_ASI_DFX_MODULE_fkrd_busy_START      (10)
#define SOC_DMSS_ASI_DFX_MODULE_fkrd_busy_END        (10)
#define SOC_DMSS_ASI_DFX_MODULE_sec_busy_START       (11)
#define SOC_DMSS_ASI_DFX_MODULE_sec_busy_END         (11)
#define SOC_DMSS_ASI_DFX_MODULE_rdr_est_busy_START   (12)
#define SOC_DMSS_ASI_DFX_MODULE_rdr_est_busy_END     (12)
#define SOC_DMSS_ASI_DFX_MODULE_rdr_buf_busy_START   (13)
#define SOC_DMSS_ASI_DFX_MODULE_rdr_buf_busy_END     (13)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_DFX_FIFO_UNION
 �ṹ˵��  : ASI_DFX_FIFO �Ĵ����ṹ���塣��ַƫ����:0x704+0x800*(asi_base)����ֵ:0x00550555�����:32
 �Ĵ���˵��: DFX��FIFO����״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_wfifo_st    : 2;  /* bit[0-1]  : ASI_RAģ����д����FIFO��״̬��
                                                          0x0��busy��
                                                          0x1��emtpy��
                                                          0x2��full��
                                                          0x3��reserved�� */
        unsigned int  wd_cmdfifo_st  : 2;  /* bit[2-3]  : ASI_WDģ����д����FIFO��״̬��
                                                          0x0��busy��
                                                          0x1��emtpy��
                                                          0x2��full��
                                                          0x3��reserved�� */
        unsigned int  b_respfifo_st  : 2;  /* bit[4-5]  : ASI_Bģ����д��ӦFIFO��״̬��
                                                          0x0��busy��
                                                          0x1��emtpy��
                                                          0x2��full��
                                                          0x3��reserved�� */
        unsigned int  rd_rfifo_st    : 2;  /* bit[6-7]  : ASI_RDģ���ж�����FIFO��״̬��
                                                          0x0��busy��
                                                          0x1��emtpy��
                                                          0x2��full��
                                                          0x3��reserved�� */
        unsigned int  rd_barfifo_st  : 2;  /* bit[8-9]  : ASI_RDģ���ж�barrier����FIFO��״̬��
                                                          0x0��busy��
                                                          0x1��emtpy��
                                                          0x2��full��
                                                          0x3��reserved�� */
        unsigned int  fkrd_fkfifo_st : 2;  /* bit[10-11]: ASI_FKRDģ���мٶ�����FIFO��״̬��
                                                          0x0��busy��
                                                          0x1��emtpy��
                                                          0x2��full��
                                                          0x3��reserved�� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  dmi0_wfifo_st  : 2;  /* bit[16-17]: DMI0ģ����д����FIFO��״̬��
                                                          0x0��busy��
                                                          0x1��emtpy��
                                                          0x2��full��
                                                          0x3��reserved�� */
        unsigned int  dmi1_wfifo_st  : 2;  /* bit[18-19]: DMI1ģ����д����FIFO��״̬��
                                                          0x0��busy��
                                                          0x1��emtpy��
                                                          0x2��full��
                                                          0x3��reserved�� */
        unsigned int  dmi2_wfifo_st  : 2;  /* bit[20-21]: DMI2ģ����д����FIFO��״̬��
                                                          0x0��busy��
                                                          0x1��emtpy��
                                                          0x2��full��
                                                          0x3��reserved�� */
        unsigned int  dmi3_wfifo_st  : 2;  /* bit[22-23]: DMI3ģ����д����FIFO��״̬��
                                                          0x0��busy��
                                                          0x1��emtpy��
                                                          0x2��full��
                                                          0x3��reserved�� */
        unsigned int  reserved_1     : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DMSS_ASI_DFX_FIFO_UNION;
#endif
#define SOC_DMSS_ASI_DFX_FIFO_ra_wfifo_st_START     (0)
#define SOC_DMSS_ASI_DFX_FIFO_ra_wfifo_st_END       (1)
#define SOC_DMSS_ASI_DFX_FIFO_wd_cmdfifo_st_START   (2)
#define SOC_DMSS_ASI_DFX_FIFO_wd_cmdfifo_st_END     (3)
#define SOC_DMSS_ASI_DFX_FIFO_b_respfifo_st_START   (4)
#define SOC_DMSS_ASI_DFX_FIFO_b_respfifo_st_END     (5)
#define SOC_DMSS_ASI_DFX_FIFO_rd_rfifo_st_START     (6)
#define SOC_DMSS_ASI_DFX_FIFO_rd_rfifo_st_END       (7)
#define SOC_DMSS_ASI_DFX_FIFO_rd_barfifo_st_START   (8)
#define SOC_DMSS_ASI_DFX_FIFO_rd_barfifo_st_END     (9)
#define SOC_DMSS_ASI_DFX_FIFO_fkrd_fkfifo_st_START  (10)
#define SOC_DMSS_ASI_DFX_FIFO_fkrd_fkfifo_st_END    (11)
#define SOC_DMSS_ASI_DFX_FIFO_dmi0_wfifo_st_START   (16)
#define SOC_DMSS_ASI_DFX_FIFO_dmi0_wfifo_st_END     (17)
#define SOC_DMSS_ASI_DFX_FIFO_dmi1_wfifo_st_START   (18)
#define SOC_DMSS_ASI_DFX_FIFO_dmi1_wfifo_st_END     (19)
#define SOC_DMSS_ASI_DFX_FIFO_dmi2_wfifo_st_START   (20)
#define SOC_DMSS_ASI_DFX_FIFO_dmi2_wfifo_st_END     (21)
#define SOC_DMSS_ASI_DFX_FIFO_dmi3_wfifo_st_START   (22)
#define SOC_DMSS_ASI_DFX_FIFO_dmi3_wfifo_st_END     (23)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_DFX_FSM_UNION
 �ṹ˵��  : ASI_DFX_FSM �Ĵ����ṹ���塣��ַƫ����:0x708+0x800*(asi_base)����ֵ:0x00000001�����:32
 �Ĵ���˵��: DFX��״̬������״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cs_fsm_st : 8;  /* bit[0-7] : ASI_CSģ��������״̬������ת״̬��
                                                    0x001��st_idle��
                                                    0x002��st_bar��
                                                    0x004��st_ex_chk��
                                                    0x008��st_ex_wait��
                                                    0x010��st_ex_rw��
                                                    0x020��st_nar��
                                                    0x040��st_wrap��
                                                    0x080��st_realign��
                                                    ������reserve�� */
        unsigned int  reserved  : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DMSS_ASI_DFX_FSM_UNION;
#endif
#define SOC_DMSS_ASI_DFX_FSM_cs_fsm_st_START  (0)
#define SOC_DMSS_ASI_DFX_FSM_cs_fsm_st_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_DFX_WROSTD_UNION
 �ṹ˵��  : ASI_DFX_WROSTD �Ĵ����ṹ���塣��ַƫ����:0x70C+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX��дOSTD״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_ostd_st : 5;  /* bit[0-4] : д����outstandingͳ�ơ�
                                                     ע�⣺
                                                     ����DMSS����fast-response��ʽ����д����ģ�����˴�ͳ�Ƶ�outstanding���ܴ���������д���д���ݵĴ���״̬�����磬�˴�ͳ��Ϊ��ʱ������������д�����д�����ѱ���ģ�鴦����ϡ� */
        unsigned int  reserved   : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_DMSS_ASI_DFX_WROSTD_UNION;
#endif
#define SOC_DMSS_ASI_DFX_WROSTD_wr_ostd_st_START  (0)
#define SOC_DMSS_ASI_DFX_WROSTD_wr_ostd_st_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_DFX_RDR0_UNION
 �ṹ˵��  : ASI_DFX_RDR0 �Ĵ����ṹ���塣��ַƫ����:0x710+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX��REORDERģ��״̬0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdr_cmd_que_cnt_st : 8;  /* bit[0-7]  : REORDERģ����������е���������� */
        unsigned int  rdr_buf_cnt_st     : 8;  /* bit[8-15] : REORDERģ������buffer�е�����burst������ */
        unsigned int  rdr_bid_use_cnt_st : 8;  /* bit[16-23]: REORDERģ���ѷ����buffer ID������ */
        unsigned int  reserved           : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DMSS_ASI_DFX_RDR0_UNION;
#endif
#define SOC_DMSS_ASI_DFX_RDR0_rdr_cmd_que_cnt_st_START  (0)
#define SOC_DMSS_ASI_DFX_RDR0_rdr_cmd_que_cnt_st_END    (7)
#define SOC_DMSS_ASI_DFX_RDR0_rdr_buf_cnt_st_START      (8)
#define SOC_DMSS_ASI_DFX_RDR0_rdr_buf_cnt_st_END        (15)
#define SOC_DMSS_ASI_DFX_RDR0_rdr_bid_use_cnt_st_START  (16)
#define SOC_DMSS_ASI_DFX_RDR0_rdr_bid_use_cnt_st_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_DFX_RDR1_UNION
 �ṹ˵��  : ASI_DFX_RDR1 �Ĵ����ṹ���塣��ַƫ����:0x714+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX��REORDERģ��״̬1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdr_buf_rcv_done_st : 32; /* bit[0-31]: REORDERģ������buffer�е�����burst�Ƿ������ϣ�
                                                              rdr_buf_rcv_done_st[n]=0������buffer��n��entryδ����burst���߶�Ӧburst����δ������ϣ�
                                                              rdr_buf_rcv_done_st[n]=1������buffer��n��entry��Ӧburst���ݽ�����ϡ� */
    } reg;
} SOC_DMSS_ASI_DFX_RDR1_UNION;
#endif
#define SOC_DMSS_ASI_DFX_RDR1_rdr_buf_rcv_done_st_START  (0)
#define SOC_DMSS_ASI_DFX_RDR1_rdr_buf_rcv_done_st_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_DFX_INT_EN_UNION
 �ṹ˵��  : ASI_DFX_INT_EN �Ĵ����ṹ���塣��ַƫ����:0x720+0x800*(asi_base)����ֵ:0x00000001�����:32
 �Ĵ���˵��: DFX���쳣������Ϣ�ж�ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_int_en : 1;  /* bit[0]   : �쳣������ж����ʹ�ܡ�
                                                     0����ֹ��
                                                     1��ʹ�ܡ�
                                                     ˵����
                                                     1.�����쳣����ʱ�����ϱ��жϲ���¼�쳣����������Ϣ(��ѯASI_DFX_ABNM_INFO�Ĵ���)��
                                                     2.ֻ�ܽ�ֹ�ж����������ؼĴ������ǻ�������¼�ж�״̬���쳣������Ϣ�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DMSS_ASI_DFX_INT_EN_UNION;
#endif
#define SOC_DMSS_ASI_DFX_INT_EN_dfx_int_en_START  (0)
#define SOC_DMSS_ASI_DFX_INT_EN_dfx_int_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_DFX_INT_STATUS_UNION
 �ṹ˵��  : ASI_DFX_INT_STATUS �Ĵ����ṹ���塣��ַƫ����:0x724+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX���쳣������Ϣ�ж�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_int_status : 1;  /* bit[0]   : �ж�״ָ̬ʾ
                                                         0���ж�δ������
                                                         1���ж��Ѳ����� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DMSS_ASI_DFX_INT_STATUS_UNION;
#endif
#define SOC_DMSS_ASI_DFX_INT_STATUS_dfx_int_status_START  (0)
#define SOC_DMSS_ASI_DFX_INT_STATUS_dfx_int_status_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_DFX_ABNM_INF_UNION
 �ṹ˵��  : ASI_DFX_ABNM_INF �Ĵ����ṹ���塣��ַƫ����:0x728+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX���쳣������Ϣ��¼
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  abnm_link_err  : 1;  /* bit[0]    : ·�ɴ������������δ���ӵ�DMI�����ܻᵼ��ϵͳ�������� */
        unsigned int  abnm_rdr_split : 1;  /* bit[1]    : �������δ��������ģ�������£��������֣����ܻᵼ��ϵͳ�������� */
        unsigned int  abnm_ex_len    : 1;  /* bit[2]    : Υ������Լ�����յ��˷�INCR1��exclusive������ܻᵼ��exclusive������Ч���� */
        unsigned int  abnm_nar_wrap  : 1;  /* bit[3]    : Υ������Լ�����յ���narrow���͵�WRAP������ܻᵼ��ϵͳ�������� */
        unsigned int  abnm_fix       : 1;  /* bit[4]    : Υ������Լ�����յ���FIX���͵����ǿ��ת����INCR������� */
        unsigned int  abnm_len16     : 1;  /* bit[5]    : Υ������Լ�����յ��˴���burst16��������ܻᵼ��ϵͳ�������� */
        unsigned int  reserved       : 10; /* bit[6-15] : ���� */
        unsigned int  abnm_cmd_mid   : 15; /* bit[16-30]: �׸��쳣�����MasterID��
                                                          ע�⣺
                                                          ���ж��������������һ���µ��ж�ʱ���˼Ĵ�����Ϣ�Żᱻ���¡� */
        unsigned int  abnm_cmd_type  : 1;  /* bit[31]   : �׸��쳣����Ķ�д���ͣ�
                                                          0�������
                                                          1��д���
                                                          ע�⣺
                                                          ���ж��������������һ���µ��ж�ʱ���˼Ĵ�����Ϣ�Żᱻ���¡� */
    } reg;
} SOC_DMSS_ASI_DFX_ABNM_INF_UNION;
#endif
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_link_err_START   (0)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_link_err_END     (0)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_rdr_split_START  (1)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_rdr_split_END    (1)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_ex_len_START     (2)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_ex_len_END       (2)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_nar_wrap_START   (3)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_nar_wrap_END     (3)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_fix_START        (4)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_fix_END          (4)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_len16_START      (5)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_len16_END        (5)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_cmd_mid_START    (16)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_cmd_mid_END      (30)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_cmd_type_START   (31)
#define SOC_DMSS_ASI_DFX_ABNM_INF_abnm_cmd_type_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_ASI_DFX_LOAD_UNION
 �ṹ˵��  : ASI_DFX_LOAD �Ĵ����ṹ���塣��ַƫ����:0x760+0x800*(asi_base)����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX�������������״̬
            ����RTL������DMSS_SIM_DFX_ENΪ0��ͨ��ASIC�汾����Ϊ0��FPGA��EMULATOR�汾����Ϊ1������˼Ĵ��������ڣ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_wfifo_load_st    : 1;  /* bit[0]    : ASI_RAģ����д����FIFO�ķ��渺��״̬��
                                                               0x0��fifoδ�ﵽ��full״̬��
                                                               0x1��fifo�ﵽ��full״̬�� */
        unsigned int  wd_cmdfifo_load_st  : 1;  /* bit[1]    : ASI_WDģ����д����FIFO�ķ��渺��״̬��
                                                               0x0��fifoδ�ﵽ��full״̬��
                                                               0x1��fifo�ﵽ��full״̬�� */
        unsigned int  b_respfifo_load_st  : 1;  /* bit[2]    : ASI_Bģ����д��ӦFIFO�ķ��渺��״̬��
                                                               0x0��fifoδ�ﵽ��full״̬��
                                                               0x1��fifo�ﵽ��full״̬�� */
        unsigned int  rd_rfifo_load_st    : 1;  /* bit[3]    : ASI_RDģ���ж�����FIFO�ķ��渺��״̬��
                                                               0x0��fifoδ�ﵽ��full״̬��
                                                               0x1��fifo�ﵽ��full״̬�� */
        unsigned int  rd_barfifo_load_st  : 1;  /* bit[4]    : ASI_RDģ���ж�barrier����FIFO�ķ��渺��״̬��
                                                               0x0��fifoδ�ﵽ��full״̬��
                                                               0x1��fifo�ﵽ��full״̬�� */
        unsigned int  fkrd_fkfifo_load_st : 1;  /* bit[5]    : ASI_FKRDģ���мٶ�����FIFO�ķ��渺��״̬��
                                                               0x0��fifoδ�ﵽ��full״̬��
                                                               0x1��fifo�ﵽ��full״̬�� */
        unsigned int  rdr_cmd_que_load_st : 1;  /* bit[6]    : REORDERģ����������еķ��渺��״̬��
                                                               0x0���������δ�ﵽ��full״̬��
                                                               0x1��������дﵽ��full״̬�� */
        unsigned int  rdr_bid_use_load_st : 1;  /* bit[7]    : REORDERģ�����ѷ����buffer ID�����ķ��渺��״̬��
                                                               0x0��δ�ﵽ��buffer ID����ľ�״̬��
                                                               0x1���ﵽ��buffer ID����ľ�״̬�� */
        unsigned int  dmi0_wfifo_load_st  : 1;  /* bit[8]    : DMI0ģ����д����FIFO�ķ��渺��״̬��
                                                               0x0��fifoδ�ﵽ��full״̬��
                                                               0x1��fifo�ﵽ��full״̬�� */
        unsigned int  dmi1_wfifo_load_st  : 1;  /* bit[9]    : DMI1ģ����д����FIFO�ķ��渺��״̬��
                                                               0x0��fifoδ�ﵽ��full״̬��
                                                               0x1��fifo�ﵽ��full״̬�� */
        unsigned int  dmi2_wfifo_load_st  : 1;  /* bit[10]   : DMI2ģ����д����FIFO�ķ��渺��״̬��
                                                               0x0��fifoδ�ﵽ��full״̬��
                                                               0x1��fifo�ﵽ��full״̬�� */
        unsigned int  dmi3_wfifo_load_st  : 1;  /* bit[11]   : DMI3ģ����д����FIFO�ķ��渺��״̬��
                                                               0x0��fifoδ�ﵽ��full״̬��
                                                               0x1��fifo�ﵽ��full״̬�� */
        unsigned int  reserved            : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DMSS_ASI_DFX_LOAD_UNION;
#endif
#define SOC_DMSS_ASI_DFX_LOAD_ra_wfifo_load_st_START     (0)
#define SOC_DMSS_ASI_DFX_LOAD_ra_wfifo_load_st_END       (0)
#define SOC_DMSS_ASI_DFX_LOAD_wd_cmdfifo_load_st_START   (1)
#define SOC_DMSS_ASI_DFX_LOAD_wd_cmdfifo_load_st_END     (1)
#define SOC_DMSS_ASI_DFX_LOAD_b_respfifo_load_st_START   (2)
#define SOC_DMSS_ASI_DFX_LOAD_b_respfifo_load_st_END     (2)
#define SOC_DMSS_ASI_DFX_LOAD_rd_rfifo_load_st_START     (3)
#define SOC_DMSS_ASI_DFX_LOAD_rd_rfifo_load_st_END       (3)
#define SOC_DMSS_ASI_DFX_LOAD_rd_barfifo_load_st_START   (4)
#define SOC_DMSS_ASI_DFX_LOAD_rd_barfifo_load_st_END     (4)
#define SOC_DMSS_ASI_DFX_LOAD_fkrd_fkfifo_load_st_START  (5)
#define SOC_DMSS_ASI_DFX_LOAD_fkrd_fkfifo_load_st_END    (5)
#define SOC_DMSS_ASI_DFX_LOAD_rdr_cmd_que_load_st_START  (6)
#define SOC_DMSS_ASI_DFX_LOAD_rdr_cmd_que_load_st_END    (6)
#define SOC_DMSS_ASI_DFX_LOAD_rdr_bid_use_load_st_START  (7)
#define SOC_DMSS_ASI_DFX_LOAD_rdr_bid_use_load_st_END    (7)
#define SOC_DMSS_ASI_DFX_LOAD_dmi0_wfifo_load_st_START   (8)
#define SOC_DMSS_ASI_DFX_LOAD_dmi0_wfifo_load_st_END     (8)
#define SOC_DMSS_ASI_DFX_LOAD_dmi1_wfifo_load_st_START   (9)
#define SOC_DMSS_ASI_DFX_LOAD_dmi1_wfifo_load_st_END     (9)
#define SOC_DMSS_ASI_DFX_LOAD_dmi2_wfifo_load_st_START   (10)
#define SOC_DMSS_ASI_DFX_LOAD_dmi2_wfifo_load_st_END     (10)
#define SOC_DMSS_ASI_DFX_LOAD_dmi3_wfifo_load_st_START   (11)
#define SOC_DMSS_ASI_DFX_LOAD_dmi3_wfifo_load_st_END     (11)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_RTL_VER_UNION
 �ṹ˵��  : GLB_RTL_VER �Ĵ����ṹ���塣��ַƫ����:0x6000����ֵ:0x01000000�����:32
 �Ĵ���˵��: ����汾��Ϣ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_tag  : 8;  /* bit[0-7]  : RTL�����TAG��š� */
        unsigned int  reserved_0: 8;  /* bit[8-15] : ���� */
        unsigned int  version  : 12; /* bit[16-27]: �汾��ţ�
                                                    0x100��HiDMSSV100 */
        unsigned int  reserved_1: 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_DMSS_GLB_RTL_VER_UNION;
#endif
#define SOC_DMSS_GLB_RTL_VER_rtl_tag_START   (0)
#define SOC_DMSS_GLB_RTL_VER_rtl_tag_END     (7)
#define SOC_DMSS_GLB_RTL_VER_version_START   (16)
#define SOC_DMSS_GLB_RTL_VER_version_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_RTL_INF0_UNION
 �ṹ˵��  : GLB_RTL_INF0 �Ĵ����ṹ���塣��ַƫ����:0x6004����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����������Ϣ0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_addr_width     : 4;  /* bit[0-3]  : AXI���ߵ�ַλ��
                                                              0:32bits��
                                                              1:33bits��
                                                              2:34bits��
                                                              3:35bits��
                                                              4:36bits��
                                                              5:37bits��
                                                              6:38bits��
                                                              7:39bits��
                                                              8:40bits��
                                                              ������reserved�� */
        unsigned int  rtl_id_width       : 5;  /* bit[4-8]  : AXI����IDλ��
                                                              0:reserved��
                                                              1:1bits��
                                                              2:2bits��
                                                              ����
                                                              31:31bits�� */
        unsigned int  reserved_0         : 3;  /* bit[9-11] : ���� */
        unsigned int  rtl_mid_width      : 4;  /* bit[12-15]: Master IDλ��
                                                              0:reserved��
                                                              1:1bits��
                                                              2:2bits��
                                                              ����
                                                              15:15bits�� */
        unsigned int  rtl_dmi_num        : 1;  /* bit[16]   : DMI(DDRC Master Interface)����
                                                              0��1��DMI��
                                                              1��2��DMI�� */
        unsigned int  reserved_1         : 1;  /* bit[17]   : ���� */
        unsigned int  rtl_ch_num_pre_dmi : 1;  /* bit[18]   : ÿ��DMI�Խӵ�ͨ������
                                                              0��1 channel per DMI��
                                                              1��2 channel per DMI�� */
        unsigned int  reserved_2         : 1;  /* bit[19]   : ���� */
        unsigned int  rtl_asi_num        : 4;  /* bit[20-23]: ASI��AXI Slave Interface��������
                                                              0x0�� 1��ASI��
                                                              ����
                                                              0xB��12��ASI��
                                                              ������reserved */
        unsigned int  rtl_exclusive_num  : 6;  /* bit[24-29]: ��ͬʱ���ӵĲ�ͬexclusive�������������
                                                              0x00����֧��exclusive���
                                                              0x01��1����
                                                              0x02��2����
                                                              ����
                                                              0x1F��31����
                                                              0x20��32����
                                                              ������reserved */
        unsigned int  reserved_3         : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DMSS_GLB_RTL_INF0_UNION;
#endif
#define SOC_DMSS_GLB_RTL_INF0_rtl_addr_width_START      (0)
#define SOC_DMSS_GLB_RTL_INF0_rtl_addr_width_END        (3)
#define SOC_DMSS_GLB_RTL_INF0_rtl_id_width_START        (4)
#define SOC_DMSS_GLB_RTL_INF0_rtl_id_width_END          (8)
#define SOC_DMSS_GLB_RTL_INF0_rtl_mid_width_START       (12)
#define SOC_DMSS_GLB_RTL_INF0_rtl_mid_width_END         (15)
#define SOC_DMSS_GLB_RTL_INF0_rtl_dmi_num_START         (16)
#define SOC_DMSS_GLB_RTL_INF0_rtl_dmi_num_END           (16)
#define SOC_DMSS_GLB_RTL_INF0_rtl_ch_num_pre_dmi_START  (18)
#define SOC_DMSS_GLB_RTL_INF0_rtl_ch_num_pre_dmi_END    (18)
#define SOC_DMSS_GLB_RTL_INF0_rtl_asi_num_START         (20)
#define SOC_DMSS_GLB_RTL_INF0_rtl_asi_num_END           (23)
#define SOC_DMSS_GLB_RTL_INF0_rtl_exclusive_num_START   (24)
#define SOC_DMSS_GLB_RTL_INF0_rtl_exclusive_num_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_RTL_INF1_UNION
 �ṹ˵��  : GLB_RTL_INF1 �Ĵ����ṹ���塣��ַƫ����:0x6008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����������Ϣ1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtl_rbuf_buf_num : 6;  /* bit[0-5] : RBUFģ�������buffer��ȡ�
                                                           0��δ����RBUF��ʹ����cross bar�Ľ����ṹ��
                                                           1��2 read burst��
                                                           2��3 read burst��
                                                           ����
                                                           63��64 read burst�� */
        unsigned int  reserved         : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DMSS_GLB_RTL_INF1_UNION;
#endif
#define SOC_DMSS_GLB_RTL_INF1_rtl_rbuf_buf_num_START  (0)
#define SOC_DMSS_GLB_RTL_INF1_rtl_rbuf_buf_num_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_RAM_TMOD_UNION
 �ṹ˵��  : GLB_RAM_TMOD �Ĵ����ṹ���塣��ַƫ����:0x6018����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEMORY����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ram_tmod : 16; /* bit[0-15] : ����MEMORY�Ĳ�ͬ���ͼ��������� */
        unsigned int  reserved : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DMSS_GLB_RAM_TMOD_UNION;
#endif
#define SOC_DMSS_GLB_RAM_TMOD_ram_tmod_START  (0)
#define SOC_DMSS_GLB_RAM_TMOD_ram_tmod_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_CFG_LOCK_UNION
 �ṹ˵��  : GLB_CFG_LOCK �Ĵ����ṹ���塣��ַƫ����:0x6020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���üĴ�������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_lock        : 1;  /* bit[0]    : ����DMSS�����еļĴ�������ģ��(��GLB��ȫ��ASI�ڵ����üĴ���)��
                                                           0����������
                                                           1�������������Ĵ�������������üĴ������޷���Ч���ʣ��ɷ�ֹ����������͹��ģ�����ʱǿ�ж�ȡ������ܶ���δ����ʱ�����һ�μĴ�����ȡֵ���� */
        unsigned int  reserved_0      : 15; /* bit[1-15] : ���� */
        unsigned int  cfg_lock_int_en : 1;  /* bit[16]   : �Ĵ������������ж�ʹ�ܣ�
                                                           0����ֹ��
                                                           1��ʹ�ܡ�
                                                           ˵����
                                                           ���Ĵ�������ʱ�����жԼĴ��������÷��ʣ�������Ĵ������������жϡ��ж�״̬��GLB_INT_STATUS�Ĵ����С� */
        unsigned int  reserved_1      : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_DMSS_GLB_CFG_LOCK_UNION;
#endif
#define SOC_DMSS_GLB_CFG_LOCK_cfg_lock_START         (0)
#define SOC_DMSS_GLB_CFG_LOCK_cfg_lock_END           (0)
#define SOC_DMSS_GLB_CFG_LOCK_cfg_lock_int_en_START  (16)
#define SOC_DMSS_GLB_CFG_LOCK_cfg_lock_int_en_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_DYN_CKG_UNION
 �ṹ˵��  : GLB_DYN_CKG �Ĵ����ṹ���塣��ַƫ����:0x6024����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��̬ʱ���ſ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ckg_byp_rbuf_src   : 1;  /* bit[0]   : RBUF_SRCģ��Ķ�̬ʱ���ſأ�
                                                             0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                             1��ʱ�ӳ����� */
        unsigned int  ckg_byp_rbuf_dst   : 1;  /* bit[1]   : RBUF_DSTģ��Ķ�̬ʱ���ſأ�
                                                             0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                             1��ʱ�ӳ����� */
        unsigned int  ckg_byp_dmi_wdfifo : 1;  /* bit[2]   : DMIģ����д����fifo�Ķ�̬ʱ���ſأ�
                                                             0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                             1��ʱ�ӳ����� */
        unsigned int  ckg_byp_dmi        : 1;  /* bit[3]   : DMIģ��Ķ�̬ʱ���ſأ�
                                                             0��ģ��idleʱ���Զ��ر�ʱ�ӣ�
                                                             1��ʱ�ӳ����� */
        unsigned int  reserved           : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DMSS_GLB_DYN_CKG_UNION;
#endif
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_rbuf_src_START    (0)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_rbuf_src_END      (0)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_rbuf_dst_START    (1)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_rbuf_dst_END      (1)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_dmi_wdfifo_START  (2)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_dmi_wdfifo_END    (2)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_dmi_START         (3)
#define SOC_DMSS_GLB_DYN_CKG_ckg_byp_dmi_END           (3)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_INT_STATUS_UNION
 �ṹ˵��  : GLB_INT_STATUS �Ĵ����ṹ���塣��ַƫ����:0x6030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ȫ���ж�״̬�鿴
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asi_sec_int  : 12; /* bit[0-11] : ��ȫ�����ж�״̬��
                                                        asi_sec_int[n]=1����ȫ�ж�����ASIn�� */
        unsigned int  reserved_0   : 4;  /* bit[12-15]: ���� */
        unsigned int  asi_dfx_int  : 12; /* bit[16-27]: DFX�����ж�״̬��
                                                        asi_dfx_int[n]=1��DFX�ж�����ASIn�� */
        unsigned int  cfg_lock_int : 1;  /* bit[28]   : �Ĵ������������жϡ�
                                                        ˵����
                                                        ���Ĵ�������ʱ�����жԼĴ��������÷��ʣ�������Ĵ������������жϡ��ж�ʹ����GLB_CFG_LOCK�Ĵ����С� */
        unsigned int  reserved_1   : 3;  /* bit[29-31]: ���� */
    } reg;
} SOC_DMSS_GLB_INT_STATUS_UNION;
#endif
#define SOC_DMSS_GLB_INT_STATUS_asi_sec_int_START   (0)
#define SOC_DMSS_GLB_INT_STATUS_asi_sec_int_END     (11)
#define SOC_DMSS_GLB_INT_STATUS_asi_dfx_int_START   (16)
#define SOC_DMSS_GLB_INT_STATUS_asi_dfx_int_END     (27)
#define SOC_DMSS_GLB_INT_STATUS_cfg_lock_int_START  (28)
#define SOC_DMSS_GLB_INT_STATUS_cfg_lock_int_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_INT_CLEAR_UNION
 �ṹ˵��  : GLB_INT_CLEAR �Ĵ����ṹ���塣��ַƫ����:0x6034����ֵ:0x00000000�����:32
 �Ĵ���˵��: ȫ���ж�״̬���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asi_sec_int_clear  : 12; /* bit[0-11] : ��Ӧbitд1���������ӦASI�İ�ȫ�����ж�״̬��
                                                              asi_sec_int_clear[n]=1������İ�ȫ�����ж�״̬����ASIn�� */
        unsigned int  reserved_0         : 4;  /* bit[12-15]: ���� */
        unsigned int  asi_dfx_int_clear  : 12; /* bit[16-27]: ��Ӧbitд1���������ӦASI��DFX�����ж�״̬��
                                                              asi_dfx_int_clear[n]=1�������DFX�ж�״̬����ASIn�� */
        unsigned int  cfg_lock_int_clear : 1;  /* bit[28]   : ��Ӧbitд1��������Ĵ������������жϡ� */
        unsigned int  reserved_1         : 3;  /* bit[29-31]: ���� */
    } reg;
} SOC_DMSS_GLB_INT_CLEAR_UNION;
#endif
#define SOC_DMSS_GLB_INT_CLEAR_asi_sec_int_clear_START   (0)
#define SOC_DMSS_GLB_INT_CLEAR_asi_sec_int_clear_END     (11)
#define SOC_DMSS_GLB_INT_CLEAR_asi_dfx_int_clear_START   (16)
#define SOC_DMSS_GLB_INT_CLEAR_asi_dfx_int_clear_END     (27)
#define SOC_DMSS_GLB_INT_CLEAR_cfg_lock_int_clear_START  (28)
#define SOC_DMSS_GLB_INT_CLEAR_cfg_lock_int_clear_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_EXCLU_UNION
 �ṹ˵��  : GLB_EXCLU �Ĵ����ṹ���塣��ַƫ����:0x6040����ֵ:0x00000001�����:32
 �Ĵ���˵��: exclusive��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exclu_en : 1;  /* bit[0]   : exclusive����ʹ�ܣ�
                                                   0����ֹ������exclusive���������ͨ�����
                                                   1��ʹ�ܣ�֧��exclusive��� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DMSS_GLB_EXCLU_UNION;
#endif
#define SOC_DMSS_GLB_EXCLU_exclu_en_START  (0)
#define SOC_DMSS_GLB_EXCLU_exclu_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_ADDR_INTLV_UNION
 �ṹ˵��  : GLB_ADDR_INTLV �Ĵ����ṹ���塣��ַƫ����:0x6100����ֵ:0x00000000�����:32
 �Ĵ���˵��: ȫ�ֵ�ַ��֯ģʽ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intlv_mode    : 1;  /* bit[0]   : ͨ��ӳ��ģʽ��
                                                        0x0��˫ͨ����֯��
                                                        0x1����ͨ����֯��
                                                        ע�⣺
                                                        �˼Ĵ���ֻ����ϵͳ��ʼ��ʱ��̬���á� */
        unsigned int  reserved_0    : 3;  /* bit[1-3] : ���� */
        unsigned int  intlv_granule : 3;  /* bit[4-6] : ��ַ��֯���ȣ�
                                                        0x0��128Byte��
                                                        0x1��256Byte��
                                                        0x2��512Byte��
                                                        0x3�� 1KByte��
                                                        0x4�� 2KByte��
                                                        0x5�� 4KByte��
                                                        ע�⣺
                                                        1.�����Դ�����Ϊ�߽磬������ַ������ͨ����
                                                        2.��ַ��֯���ȱ�����ڵ��ڵ�ַ��������(��RTL�궨��)��
                                                        3.�˼Ĵ���ֻ����ϵͳ��ʼ��ʱ��̬���á� */
        unsigned int  reserved_1    : 25; /* bit[7-31]: ���� */
    } reg;
} SOC_DMSS_GLB_ADDR_INTLV_UNION;
#endif
#define SOC_DMSS_GLB_ADDR_INTLV_intlv_mode_START     (0)
#define SOC_DMSS_GLB_ADDR_INTLV_intlv_mode_END       (0)
#define SOC_DMSS_GLB_ADDR_INTLV_intlv_granule_START  (4)
#define SOC_DMSS_GLB_ADDR_INTLV_intlv_granule_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_ADDR_SCRMBL_UNION
 �ṹ˵��  : GLB_ADDR_SCRMBL �Ĵ����ṹ���塣��ַƫ����:0x6110����ֵ:0x00000000�����:32
 �Ĵ���˵��: ȫ�ֵ�ַ����ģʽ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bnk_scrmbl : 4;  /* bit[0-3] : BANK��ַ����ģʽ��
                                                     0�������룻
                                                     1��addr[14:12] = addr[14:12] xor addr[20:18]��˫ͨ����
                                                     2��addr[14:12] = addr[14:12] xor addr[21:19]��˫ͨ����
                                                     3��addr[14:12] = addr[14:12] xor addr[22:20]��˫ͨ����
                                                     4��addr[13:11] = addr[13:11] xor addr[19:17]����ͨ����
                                                     5��addr[13:11] = addr[13:11] xor addr[20:18]����ͨ����
                                                     6��addr[13:11] = addr[13:11] xor addr[21:19]����ͨ����
                                                     7~15��reserved
                                                     ˵����
                                                     1.�˴���addr���ǳ�ȡ��֯λ֮���ͨ���ڵ�ַ��
                                                     2.���Ź���ΪRTL���ơ�
                                                     3.�˼Ĵ���ֻ����ϵͳ��ʼ��ʱ��̬���á� */
        unsigned int  reserved   : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DMSS_GLB_ADDR_SCRMBL_UNION;
#endif
#define SOC_DMSS_GLB_ADDR_SCRMBL_bnk_scrmbl_START  (0)
#define SOC_DMSS_GLB_ADDR_SCRMBL_bnk_scrmbl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_RBUF_TRSFR_WL0_UNION
 �ṹ˵��  : GLB_RBUF_TRSFR_WL0 �Ĵ����ṹ���塣��ַƫ����:0x6140����ֵ:0x00000000�����:32
 �Ĵ���˵��: RBUF�Ĵ�����ʼˮ������0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 4;  /* bit[0-3]  : ���� */
        unsigned int  trsfr_wl_bl_2 : 1;  /* bit[4]    : ��RBUF�յ�burst lengthΪ2��transfer����Ϊ2���Ķ�����ʱ����ʼ�ᴫ�������ˮ�����ã�
                                                         0x0��ÿ���ջ��ܵ�1��transfer�����������transferʱ��������������
                                                         0x1��ÿ���ջ��ܵ�2��transfer�����������transferʱ��������������
                                                         ˵����
                                                         1.������ֻ�ڵ�ǰ��������MID�ļ��ģʽ������Ϊģʽ��ʱ����Ч�����ģʽ��������ο�ASI���ֵ�ASI_RBUF_INTLV�Ĵ�����
                                                         2.����Ϊ���ģʽ��ʱ��ÿ������Ϊburst2�����ݣ�ÿ����RBUF�л��ܵ�transfer�����ﵽ�˼Ĵ������õ�ˮ��ʱ�����ܿ�ʼ�������ݴ��䣬ֱ����ǰburstȫ��������ϣ��ڴ�����;�����ѽ��յ�transfer�Ѵ�����϶�ʣ�����ݻ�δ���յ�����ɼ�崫������ͨ·�����ݡ� */
        unsigned int  reserved_1    : 3;  /* bit[5-7]  : ���� */
        unsigned int  trsfr_wl_bl_3 : 2;  /* bit[8-9]  : ͬwl_bl2�����á� */
        unsigned int  reserved_2    : 2;  /* bit[10-11]: ���� */
        unsigned int  trsfr_wl_bl_4 : 2;  /* bit[12-13]: ͬwl_bl2�����á� */
        unsigned int  reserved_3    : 2;  /* bit[14-15]: ���� */
        unsigned int  trsfr_wl_bl_5 : 3;  /* bit[16-18]: ͬwl_bl2�����á� */
        unsigned int  reserved_4    : 1;  /* bit[19]   : ���� */
        unsigned int  trsfr_wl_bl_6 : 3;  /* bit[20-22]: ͬwl_bl2�����á� */
        unsigned int  reserved_5    : 1;  /* bit[23]   : ���� */
        unsigned int  trsfr_wl_bl_7 : 3;  /* bit[24-26]: ͬwl_bl2�����á� */
        unsigned int  reserved_6    : 1;  /* bit[27]   : ���� */
        unsigned int  trsfr_wl_bl_8 : 3;  /* bit[28-30]: ͬwl_bl2�����á� */
        unsigned int  reserved_7    : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DMSS_GLB_RBUF_TRSFR_WL0_UNION;
#endif
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_2_START  (4)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_2_END    (4)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_3_START  (8)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_3_END    (9)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_4_START  (12)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_4_END    (13)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_5_START  (16)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_5_END    (18)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_6_START  (20)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_6_END    (22)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_7_START  (24)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_7_END    (26)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_8_START  (28)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL0_trsfr_wl_bl_8_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_RBUF_TRSFR_WL1_UNION
 �ṹ˵��  : GLB_RBUF_TRSFR_WL1 �Ĵ����ṹ���塣��ַƫ����:0x6144����ֵ:0x00000000�����:32
 �Ĵ���˵��: RBUF�Ĵ�����ʼˮ������1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trsfr_wl_bl_9  : 4;  /* bit[0-3]  : ��RBUF�յ�burst lengthΪ9��transfer����Ϊ9���Ķ�����ʱ����ʼ�ᴫ�������ˮ�����ã�
                                                          0x0��ÿ���ջ��ܵ�1��transfer�����������transferʱ��������������
                                                          0x1��ÿ���ջ��ܵ�2��transfer�����������transferʱ��������������
                                                          ����
                                                          0x8��ÿ���ջ��ܵ�9��transfer�����������transferʱ��������������
                                                          ˵����
                                                          1.������ֻ�ڵ�ǰ��������MID�ļ��ģʽ������Ϊģʽ��ʱ����Ч�����ģʽ��������ο�ASI���ֵ�ASI_RBUF_INTLV�Ĵ�����
                                                          2.����Ϊ���ģʽ��ʱ��ÿ������Ϊburst9�����ݣ�ÿ����RBUF�л��ܵ�transfer�����ﵽ�˼Ĵ������õ�ˮ��ʱ�����ܿ�ʼ�������ݴ��䣬ֱ����ǰburstȫ��������ϣ��ڴ�����;�����ѽ��յ�transfer�Ѵ�����϶�ʣ�����ݻ�δ���յ�����ɼ�崫������ͨ·�����ݡ� */
        unsigned int  trsfr_wl_bl_10 : 4;  /* bit[4-7]  : ͬwl_bl9�����á� */
        unsigned int  trsfr_wl_bl_11 : 4;  /* bit[8-11] : ͬwl_bl9�����á� */
        unsigned int  trsfr_wl_bl_12 : 4;  /* bit[12-15]: ͬwl_bl9�����á� */
        unsigned int  trsfr_wl_bl_13 : 4;  /* bit[16-19]: ͬwl_bl9�����á� */
        unsigned int  trsfr_wl_bl_14 : 4;  /* bit[20-23]: ͬwl_bl9�����á� */
        unsigned int  trsfr_wl_bl_15 : 4;  /* bit[24-27]: ͬwl_bl9�����á� */
        unsigned int  trsfr_wl_bl_16 : 4;  /* bit[28-31]: ͬwl_bl9�����á� */
    } reg;
} SOC_DMSS_GLB_RBUF_TRSFR_WL1_UNION;
#endif
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_9_START   (0)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_9_END     (3)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_10_START  (4)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_10_END    (7)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_11_START  (8)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_11_END    (11)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_12_START  (12)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_12_END    (15)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_13_START  (16)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_13_END    (19)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_14_START  (20)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_14_END    (23)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_15_START  (24)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_15_END    (27)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_16_START  (28)
#define SOC_DMSS_GLB_RBUF_TRSFR_WL1_trsfr_wl_bl_16_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_RBUF_BP_UNION
 �ṹ˵��  : GLB_RBUF_BP �Ĵ����ṹ���塣��ַƫ����:0x6150+0x4*(rbuf_bp_grps)����ֵ:0x00000000�����:32
 �Ĵ���˵��: RBUF�����ѹ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rbuf_bp_grp : 16; /* bit[0-15] : ���ѹ�����ѡ��
                                                       rbuf_bp_grp[n]=0��ASIn������������0��
                                                       rbuf_bp_grp[n]=1��ASIn����������0��
                                                       ˵����
                                                       ��������ͬһ�������ASI��������RBUF�е�����burst�����ﵽ��Ӧrbuf_bp_wl���õ�ˮ��ʱ���ͳ���ѹ�źŸ�����ģ�飨DDRC�������ж�ӦASI�����ѹ��
                                                       ע�⣺
                                                       �˼Ĵ���ֻ����ϵͳ��ʼ��ʱ��̬���á� */
        unsigned int  rbuf_bp_wl  : 16; /* bit[16-31]: ���ѹ�����ˮ�ߣ�
                                                       0���ر����ѹ���ܣ�
                                                       ����
                                                       n����ǰ��������ѹˮ�ߡ�
                                                       ˵����
                                                       1.��ǰ����������ASI��Ӧ������burst�����ﵽrubf_bp_wlʱ���ͳ���ѹ�źŸ�����ģ�飨DDRC�������ж�ӦASI�����ѹ��
                                                       2.ˮ���������ֵΪRBUF�е�BUFFER��ȡ�
                                                       ע�⣺
                                                       ���ܶ�̬�������ѹ���ܣ���������ʹ�ܵ�����£���̬����ˮ�ߡ� */
    } reg;
} SOC_DMSS_GLB_RBUF_BP_UNION;
#endif
#define SOC_DMSS_GLB_RBUF_BP_rbuf_bp_grp_START  (0)
#define SOC_DMSS_GLB_RBUF_BP_rbuf_bp_grp_END    (15)
#define SOC_DMSS_GLB_RBUF_BP_rbuf_bp_wl_START   (16)
#define SOC_DMSS_GLB_RBUF_BP_rbuf_bp_wl_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_DFX_RBUF0_UNION
 �ṹ˵��  : GLB_DFX_RBUF0 �Ĵ����ṹ���塣��ַƫ����:0x6700+0x10*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX��RBUF״̬0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vque0_cnt_st : 8;  /* bit[0-7]  : RBUF��buffer�д�����ASI0������burst������ */
        unsigned int  vque1_cnt_st : 8;  /* bit[8-15] : ͬvque0_cnt�� */
        unsigned int  vque2_cnt_st : 8;  /* bit[16-23]: ͬvque0_cnt�� */
        unsigned int  vque3_cnt_st : 8;  /* bit[24-31]: ͬvque0_cnt�� */
    } reg;
} SOC_DMSS_GLB_DFX_RBUF0_UNION;
#endif
#define SOC_DMSS_GLB_DFX_RBUF0_vque0_cnt_st_START  (0)
#define SOC_DMSS_GLB_DFX_RBUF0_vque0_cnt_st_END    (7)
#define SOC_DMSS_GLB_DFX_RBUF0_vque1_cnt_st_START  (8)
#define SOC_DMSS_GLB_DFX_RBUF0_vque1_cnt_st_END    (15)
#define SOC_DMSS_GLB_DFX_RBUF0_vque2_cnt_st_START  (16)
#define SOC_DMSS_GLB_DFX_RBUF0_vque2_cnt_st_END    (23)
#define SOC_DMSS_GLB_DFX_RBUF0_vque3_cnt_st_START  (24)
#define SOC_DMSS_GLB_DFX_RBUF0_vque3_cnt_st_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_DFX_RBUF1_UNION
 �ṹ˵��  : GLB_DFX_RBUF1 �Ĵ����ṹ���塣��ַƫ����:0x6704+0x10*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX��RBUF״̬1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vque4_cnt_st : 8;  /* bit[0-7]  : RBUF��buffer�д�����ASI4������burst������ */
        unsigned int  vque5_cnt_st : 8;  /* bit[8-15] : ͬvque4_cnt�� */
        unsigned int  vque6_cnt_st : 8;  /* bit[16-23]: ͬvque4_cnt�� */
        unsigned int  vque7_cnt_st : 8;  /* bit[24-31]: ͬvque4_cnt�� */
    } reg;
} SOC_DMSS_GLB_DFX_RBUF1_UNION;
#endif
#define SOC_DMSS_GLB_DFX_RBUF1_vque4_cnt_st_START  (0)
#define SOC_DMSS_GLB_DFX_RBUF1_vque4_cnt_st_END    (7)
#define SOC_DMSS_GLB_DFX_RBUF1_vque5_cnt_st_START  (8)
#define SOC_DMSS_GLB_DFX_RBUF1_vque5_cnt_st_END    (15)
#define SOC_DMSS_GLB_DFX_RBUF1_vque6_cnt_st_START  (16)
#define SOC_DMSS_GLB_DFX_RBUF1_vque6_cnt_st_END    (23)
#define SOC_DMSS_GLB_DFX_RBUF1_vque7_cnt_st_START  (24)
#define SOC_DMSS_GLB_DFX_RBUF1_vque7_cnt_st_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_DFX_RBUF2_UNION
 �ṹ˵��  : GLB_DFX_RBUF2 �Ĵ����ṹ���塣��ַƫ����:0x6708+0x10*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX��RBUF״̬2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vque8_cnt_st  : 8;  /* bit[0-7]  : RBUF��buffer�д�����ASI8������burst������ */
        unsigned int  vque9_cnt_st  : 8;  /* bit[8-15] : ͬvque8_cnt�� */
        unsigned int  vque10_cnt_st : 8;  /* bit[16-23]: ͬvque8_cnt�� */
        unsigned int  vque11_cnt_st : 8;  /* bit[24-31]: ͬvque8_cnt�� */
    } reg;
} SOC_DMSS_GLB_DFX_RBUF2_UNION;
#endif
#define SOC_DMSS_GLB_DFX_RBUF2_vque8_cnt_st_START   (0)
#define SOC_DMSS_GLB_DFX_RBUF2_vque8_cnt_st_END     (7)
#define SOC_DMSS_GLB_DFX_RBUF2_vque9_cnt_st_START   (8)
#define SOC_DMSS_GLB_DFX_RBUF2_vque9_cnt_st_END     (15)
#define SOC_DMSS_GLB_DFX_RBUF2_vque10_cnt_st_START  (16)
#define SOC_DMSS_GLB_DFX_RBUF2_vque10_cnt_st_END    (23)
#define SOC_DMSS_GLB_DFX_RBUF2_vque11_cnt_st_START  (24)
#define SOC_DMSS_GLB_DFX_RBUF2_vque11_cnt_st_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_DFX_RBUF3_UNION
 �ṹ˵��  : GLB_DFX_RBUF3 �Ĵ����ṹ���塣��ַƫ����:0x670C+0x10*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX��RBUF״̬3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vque_grp0_cnt_st : 8;  /* bit[0-7]  : RBUF��buffer�У����ѹ����0�е�����burst������ */
        unsigned int  vque_grp1_cnt_st : 8;  /* bit[8-15] : ͬvque_grp0_cnt�� */
        unsigned int  vque_grp2_cnt_st : 8;  /* bit[16-23]: ͬvque_grp0_cnt�� */
        unsigned int  vque_grp3_cnt_st : 8;  /* bit[24-31]: ͬvque_grp0_cnt�� */
    } reg;
} SOC_DMSS_GLB_DFX_RBUF3_UNION;
#endif
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp0_cnt_st_START  (0)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp0_cnt_st_END    (7)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp1_cnt_st_START  (8)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp1_cnt_st_END    (15)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp2_cnt_st_START  (16)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp2_cnt_st_END    (23)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp3_cnt_st_START  (24)
#define SOC_DMSS_GLB_DFX_RBUF3_vque_grp3_cnt_st_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_DFX_DMI_GRNT_UNION
 �ṹ˵��  : GLB_DFX_DMI_GRNT �Ĵ����ṹ���塣��ַƫ����:0x6740����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX��DMI�������ٲ�״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmi0_grant : 16; /* bit[0-15] : DMI0�������ٲ�״̬��
                                                      dmi_grant[n]=0��ASInδ���DMI0�������ٲã�
                                                      dmi_grant[n]=1��ASIn�����DMI0�������ٲá� */
        unsigned int  dmi1_grant : 16; /* bit[16-31]: ͬdmi0_grant�� */
    } reg;
} SOC_DMSS_GLB_DFX_DMI_GRNT_UNION;
#endif
#define SOC_DMSS_GLB_DFX_DMI_GRNT_dmi0_grant_START  (0)
#define SOC_DMSS_GLB_DFX_DMI_GRNT_dmi0_grant_END    (15)
#define SOC_DMSS_GLB_DFX_DMI_GRNT_dmi1_grant_START  (16)
#define SOC_DMSS_GLB_DFX_DMI_GRNT_dmi1_grant_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_DFX_ASI_BUSY_UNION
 �ṹ˵��  : GLB_DFX_ASI_BUSY �Ĵ����ṹ���塣��ַƫ����:0x6750����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX������ASI�Ĺ���״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asi_busy : 12; /* bit[0-11] : ����ASI�Ĺ���״̬��
                                                    asi_busy[n]=0��ASIn����idle״̬��
                                                    asi_busy[n]=1��ASIn����busy״̬��
                                                    ˵����
                                                    1.�����idle��ָ��ASI����outstanding��������ݺ���Ӧ�����Ѿ����״����ꣻ
                                                    2.��ϵͳ������ĳasi_busy=1ʱ���ɼ�����Ӧ��д/��outstanding״̬��wr_ostd_st��rd_ostd_st�Ĵ�����������������һ����Ϊ�㣬��ܿ�����д/����������������߾����㣬�������ӦDDRC��DMC����ؼĴ�����dmc_cv/dmc_ct/wgntfifo_e/rdtimeout_intsts�ȣ�
                                                    3.Austin��Ŀ�У�����ASI�Խӵ�masterΪ��
                                                    ASI0�� MODEM
                                                    ASI1/2�� VCODEC
                                                    ASI3/4�� VIVO
                                                    ASI5�� IVP32
                                                    ASI6/7�� CCI��CPU��
                                                    ASI8�� SYS_PERI
                                                    ASI9/10��GPU */
        unsigned int  reserved : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DMSS_GLB_DFX_ASI_BUSY_UNION;
#endif
#define SOC_DMSS_GLB_DFX_ASI_BUSY_asi_busy_START  (0)
#define SOC_DMSS_GLB_DFX_ASI_BUSY_asi_busy_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DMSS_GLB_DFX_LOAD_UNION
 �ṹ˵��  : GLB_DFX_LOAD �Ĵ����ṹ���塣��ַƫ����:0x6760����ֵ:0x00000000�����:32
 �Ĵ���˵��: DFX�������������״̬
            ����RTL������DMSS_SIM_DFX_ENΪ0��ͨ��ASIC�汾����Ϊ0��FPGA��EMULATOR�汾����Ϊ1������˼Ĵ��������ڣ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rbuf0_load_cnt_st : 8;  /* bit[0-7]  : RBUF��buffer0�ķ��渺�������
                                                             n�����浽������burst�ﵽ������������ */
        unsigned int  rbuf1_load_cnt_st : 8;  /* bit[8-15] : ͬrbuf0_load_cnt_st�� */
        unsigned int  rbuf2_load_cnt_st : 8;  /* bit[16-23]: ͬrbuf0_load_cnt_st�� */
        unsigned int  rbuf3_load_cnt_st : 8;  /* bit[24-31]: ͬrbuf0_load_cnt_st�� */
    } reg;
} SOC_DMSS_GLB_DFX_LOAD_UNION;
#endif
#define SOC_DMSS_GLB_DFX_LOAD_rbuf0_load_cnt_st_START  (0)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf0_load_cnt_st_END    (7)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf1_load_cnt_st_START  (8)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf1_load_cnt_st_END    (15)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf2_load_cnt_st_START  (16)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf2_load_cnt_st_END    (23)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf3_load_cnt_st_START  (24)
#define SOC_DMSS_GLB_DFX_LOAD_rbuf3_load_cnt_st_END    (31)






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

#endif /* end of soc_dmss_interface.h */
