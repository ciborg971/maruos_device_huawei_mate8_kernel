/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_dpp_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:02
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_DPP.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_DPP_INTERFACE_H__
#define __SOC_DSS_DPP_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_DPP
 ****************************************************************************/
/* �Ĵ���˵�������Ĵ���ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_DPP_DPP_RD_SHADOW_SEL_UNION */
#define SOC_DSS_DPP_DPP_RD_SHADOW_SEL_ADDR(base)      ((base) + (0x000))

/* �Ĵ���˵����DPP�汾��Ϣ
   λ����UNION�ṹ:  SOC_DSS_DPP_DPP_ID_UNION */
#define SOC_DSS_DPP_DPP_ID_ADDR(base)                 ((base) + (0x004))

/* �Ĵ���˵����DPPͼ����
   λ����UNION�ṹ:  SOC_DSS_DPP_DPP_IMG_HRZ_UNION */
#define SOC_DSS_DPP_DPP_IMG_HRZ_ADDR(base)            ((base) + (0x008))

/* �Ĵ���˵����DPPͼ��߶�
   λ����UNION�ṹ:  SOC_DSS_DPP_DPP_IMG_VRT_UNION */
#define SOC_DSS_DPP_DPP_IMG_VRT_ADDR(base)            ((base) + (0x00C))

/* �Ĵ���˵����COLORBAR���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DPP_CLRBAR_CTRL_UNION */
#define SOC_DSS_DPP_CLRBAR_CTRL_ADDR(base)            ((base) + (0x010))

/* �Ĵ���˵����DITHER���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DPP_DITHER_UNION */
#define SOC_DSS_DPP_DITHER_ADDR(base)                 ((base) + (0x014))

/* �Ĵ���˵����SBL���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DPP_SBL_UNION */
#define SOC_DSS_DPP_SBL_ADDR(base)                    ((base) + (0x018))

/* �Ĵ���˵����һ��ģ��ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_DPP_DPP_CLK_SEL_UNION */
#define SOC_DSS_DPP_DPP_CLK_SEL_ADDR(base)            ((base) + (0x01C))

/* �Ĵ���˵����һ��ģ��ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_DPP_DPP_CLK_EN_UNION */
#define SOC_DSS_DPP_DPP_CLK_EN_ADDR(base)             ((base) + (0x020))

/* �Ĵ���˵����DPP �������������������debug
   λ����UNION�ṹ:  SOC_DSS_DPP_DPP_DBG_CNT_UNION */
#define SOC_DSS_DPP_DPP_DBG_CNT_ADDR(base)            ((base) + (0x024))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DPP_LCP_XCC_COEF_00_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_00_ADDR(base)        ((base) + (0x100))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DPP_LCP_XCC_COEF_01_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_01_ADDR(base)        ((base) + (0x104))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DPP_LCP_XCC_COEF_02_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_02_ADDR(base)        ((base) + (0x108))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DPP_LCP_XCC_COEF_03_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_03_ADDR(base)        ((base) + (0x10C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DPP_LCP_XCC_COEF_10_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_10_ADDR(base)        ((base) + (0x110))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DPP_LCP_XCC_COEF_11_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_11_ADDR(base)        ((base) + (0x114))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DPP_LCP_XCC_COEF_12_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_12_ADDR(base)        ((base) + (0x118))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DPP_LCP_XCC_COEF_13_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_13_ADDR(base)        ((base) + (0x11C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DPP_LCP_XCC_COEF_20_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_20_ADDR(base)        ((base) + (0x120))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DPP_LCP_XCC_COEF_21_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_21_ADDR(base)        ((base) + (0x124))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DPP_LCP_XCC_COEF_22_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_22_ADDR(base)        ((base) + (0x128))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DPP_LCP_XCC_COEF_23_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_23_ADDR(base)        ((base) + (0x12C))

/* �Ĵ���˵��������������Чλѡ��
   λ����UNION�ṹ:  SOC_DSS_DPP_GMP_BYPASS_EN_UNION */
#define SOC_DSS_DPP_GMP_BYPASS_EN_ADDR(base)          ((base) + (0x130))

/* �Ĵ���˵������·GAMAģ��
   λ����UNION�ṹ:  SOC_DSS_DPP_XCC_BYPASS_EN_UNION */
#define SOC_DSS_DPP_XCC_BYPASS_EN_ADDR(base)          ((base) + (0x134))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DPP_IGM_MEM_CTRL_UNION */
#define SOC_DSS_DPP_IGM_MEM_CTRL_ADDR(base)           ((base) + (0x138))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DPP_GMP_MEM_CTRL_UNION */
#define SOC_DSS_DPP_GMP_MEM_CTRL_ADDR(base)           ((base) + (0x13C))

/* �Ĵ���˵��������0ɫ����������ֵ
   λ����UNION�ṹ:  SOC_DSS_DPP_R0_H_UNION */
#define SOC_DSS_DPP_R0_H_ADDR(base)                   ((base) + (0x200))

/* �Ĵ���˵��������1ɫ����������ֵ
   λ����UNION�ṹ:  SOC_DSS_DPP_R1_H_UNION */
#define SOC_DSS_DPP_R1_H_ADDR(base)                   ((base) + (0x204))

/* �Ĵ���˵��������2ɫ����������ֵ
   λ����UNION�ṹ:  SOC_DSS_DPP_R2_H_UNION */
#define SOC_DSS_DPP_R2_H_ADDR(base)                   ((base) + (0x208))

/* �Ĵ���˵��������3ɫ����������ֵ
   λ����UNION�ṹ:  SOC_DSS_DPP_R3_H_UNION */
#define SOC_DSS_DPP_R3_H_ADDR(base)                   ((base) + (0x20C))

/* �Ĵ���˵��������4ɫ����������ֵ
   λ����UNION�ṹ:  SOC_DSS_DPP_R4_H_UNION */
#define SOC_DSS_DPP_R4_H_ADDR(base)                   ((base) + (0x210))

/* �Ĵ���˵��������5ɫ����������ֵ
   λ����UNION�ṹ:  SOC_DSS_DPP_R5_H_UNION */
#define SOC_DSS_DPP_R5_H_ADDR(base)                   ((base) + (0x214))

/* �Ĵ���˵��������6ɫ����������ֵ
   λ����UNION�ṹ:  SOC_DSS_DPP_R6_H_UNION */
#define SOC_DSS_DPP_R6_H_ADDR(base)                   ((base) + (0x218))

/* �Ĵ���˵��������ʹ��
   λ����UNION�ṹ:  SOC_DSS_DPP_ACM_EN_UNION */
#define SOC_DSS_DPP_ACM_EN_ADDR(base)                 ((base) + (0x21C))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DPP_ACM_MEM_CTRL_UNION */
#define SOC_DSS_DPP_ACM_MEM_CTRL_ADDR(base)           ((base) + (0x220))

/* �Ĵ���˵����ֱ��ͼͳ������
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_HIST_RESET_UNION */
#define SOC_DSS_DPP_CE_HIST_RESET_ADDR(base)          ((base) + (0x230))

/* �Ĵ���˵����ֱ��ͼͳ�ƿ���
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_HIST_CTL_UNION */
#define SOC_DSS_DPP_CE_HIST_CTL_ADDR(base)            ((base) + (0x234))

/* �Ĵ���˵����ֱ��ͼͳ�Ƶ�֡����
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_HIST_FRAME_CNT_UNION */
#define SOC_DSS_DPP_CE_HIST_FRAME_CNT_ADDR(base)      ((base) + (0x238))

/* �Ĵ���˵����ͼ��Ŀ�͸�
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_SIZE_UNION */
#define SOC_DSS_DPP_CE_SIZE_ADDR(base)                ((base) + (0x23C))

/* �Ĵ���˵�������һ֡������в�����ֱ��ͼͳ��
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_NO_STAT_LINES_UNION */
#define SOC_DSS_DPP_CE_NO_STAT_LINES_ADDR(base)       ((base) + (0x240))

/* �Ĵ���˵����������ֵ
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_BLACK_REGION_THRE_UNION */
#define SOC_DSS_DPP_CE_BLACK_REGION_THRE_ADDR(base)   ((base) + (0x244))

/* �Ĵ���˵����������ֵ
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_WHITE_REGION_THRE_UNION */
#define SOC_DSS_DPP_CE_WHITE_REGION_THRE_ADDR(base)   ((base) + (0x248))

/* �Ĵ���˵����LUT��ƹ��ѡ��
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_LUT_SEL_UNION */
#define SOC_DSS_DPP_CE_LUT_SEL_ADDR(base)             ((base) + (0x24C))

/* �Ĵ���˵����CE��·ѡ��
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_LUT_ENABLE_UNION */
#define SOC_DSS_DPP_CE_LUT_ENABLE_ADDR(base)          ((base) + (0x250))

/* �Ĵ���˵����LUT��дȨ�޷���ָʾ
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_LUT_USING_IND_UNION */
#define SOC_DSS_DPP_CE_LUT_USING_IND_ADDR(base)       ((base) + (0x254))

/* �Ĵ���˵����CE����ָʾ
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_STATE_IND_UNION */
#define SOC_DSS_DPP_CE_STATE_IND_ADDR(base)           ((base) + (0x258))

/* �Ĵ���˵����CE MEM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_MEM_CTRL_UNION */
#define SOC_DSS_DPP_CE_MEM_CTRL_ADDR(base)            ((base) + (0x25C))

/* �Ĵ���˵�������лҶ��ܺ�
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_TOTALGRAY_UNION */
#define SOC_DSS_DPP_CE_TOTALGRAY_ADDR(base)           ((base) + (0x264))

/* �Ĵ���˵�����������صĸ���
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_TOTALPIXL_UNION */
#define SOC_DSS_DPP_CE_TOTALPIXL_ADDR(base)           ((base) + (0x268))

/* �Ĵ���˵����ֱ��ͼ���ֵ��Ӧ�ĻҶ�ֵ
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_MEAN_UNION */
#define SOC_DSS_DPP_CE_MEAN_ADDR(base)                ((base) + (0x26C))

/* �Ĵ���˵������λ��0~3
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_PEC0_3_UNION */
#define SOC_DSS_DPP_CE_PEC0_3_ADDR(base)              ((base) + (0x270))

/* �Ĵ���˵������λ��4~7
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_PEC4_7_UNION */
#define SOC_DSS_DPP_CE_PEC4_7_ADDR(base)              ((base) + (0x274))

/* �Ĵ���˵������λ��8
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_PEC8_UNION */
#define SOC_DSS_DPP_CE_PEC8_ADDR(base)                ((base) + (0x278))

/* �Ĵ���˵�����������
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_BLACK_NUM_UNION */
#define SOC_DSS_DPP_CE_BLACK_NUM_ADDR(base)           ((base) + (0x27C))

/* �Ĵ���˵�����������
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_WHITE_NUM_UNION */
#define SOC_DSS_DPP_CE_WHITE_NUM_ADDR(base)           ((base) + (0x280))

/* �Ĵ���˵�����ϱ�ֱ��ͼָʾ
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_HIST_RPT_IND_UNION */
#define SOC_DSS_DPP_CE_HIST_RPT_IND_ADDR(base)        ((base) + (0x284))

/* �Ĵ���˵��������������Чλѡ��
   λ����UNION�ṹ:  SOC_DSS_DPP_GAMA_SHORTBIT_EN_UNION */
#define SOC_DSS_DPP_GAMA_SHORTBIT_EN_ADDR(base)       ((base) + (0x300))

/* �Ĵ���˵������·GAMAģ��
   λ����UNION�ṹ:  SOC_DSS_DPP_GAMA_BYPASS_EN_UNION */
#define SOC_DSS_DPP_GAMA_BYPASS_EN_ADDR(base)         ((base) + (0x304))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DPP_GAMA_MEM_CTRL_UNION */
#define SOC_DSS_DPP_GAMA_MEM_CTRL_ADDR(base)          ((base) + (0x308))

/* �Ĵ���˵����ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
   λ����UNION�ṹ:  SOC_DSS_DPP_REG_DEFAULT_UNION */
#define SOC_DSS_DPP_REG_DEFAULT_ADDR(base)            ((base) + (0x030C))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DPP_SBL_MEM_CTRL_UNION */
#define SOC_DSS_DPP_SBL_MEM_CTRL_ADDR(base)           ((base) + (0x310))

/* �Ĵ���˵����DPP�����üĴ���
   λ����UNION�ṹ:  SOC_DSS_DPP_DPP_DBG_UNION */
#define SOC_DSS_DPP_DPP_DBG_ADDR(base)                ((base) + (0x314))

/* �Ĵ���˵����GAMAϵ�����ұ�
   λ����UNION�ṹ:  SOC_DSS_DPP_U_GAMA_COEF_UNION */
#define SOC_DSS_DPP_U_GAMA_COEF_ADDR(base)            ((base) + (0x0400))

/* �Ĵ���˵����ACM H�������ұ�
   λ����UNION�ṹ:  SOC_DSS_DPP_U_H_COEF_UNION */
#define SOC_DSS_DPP_U_H_COEF_ADDR(base)               ((base) + (0x1000))

/* �Ĵ���˵����ACM SATA�������ұ�
   λ����UNION�ṹ:  SOC_DSS_DPP_U_SATA_COEF_UNION */
#define SOC_DSS_DPP_U_SATA_COEF_ADDR(base)            ((base) + (0x1A00))

/* �Ĵ���˵����ACM SATR�������ұ�
   λ����UNION�ṹ:  SOC_DSS_DPP_U_SATR_COEF_UNION */
#define SOC_DSS_DPP_U_SATR_COEF_ADDR(base)            ((base) + (0x1C00))

/* �Ĵ���˵�����ϱ�ֱ��ͼmemory0
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_HIST_RPT0_UNION */
#define SOC_DSS_DPP_CE_HIST_RPT0_ADDR(base)           ((base) + (0x2000��0x23FF))

/* �Ĵ���˵�����ϱ�ֱ��ͼmemory1
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_HIST_RPT1_UNION */
#define SOC_DSS_DPP_CE_HIST_RPT1_ADDR(base)           ((base) + (0x2400��0x27FF))

/* �Ĵ���˵����LUT �� memory0
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_LUT0_UNION */
#define SOC_DSS_DPP_CE_LUT0_ADDR(base)                ((base) + (0x2800))

/* �Ĵ���˵����LUT �� memory1
   λ����UNION�ṹ:  SOC_DSS_DPP_CE_LUT1_UNION */
#define SOC_DSS_DPP_CE_LUT1_ADDR(base)                ((base) + (0x2C00))

/* �Ĵ���˵����GMP���ұ�
   λ����UNION�ṹ:  SOC_DSS_DPP_U_GMP_COEF_UNION */
#define SOC_DSS_DPP_U_GMP_COEF_ADDR(base)             ((base) + (0x3000��0x7CCF))

/* �Ĵ���˵����IGM R�������ұ�
   λ����UNION�ṹ:  SOC_DSS_DPP_U_IGM_R_COEF_UNION */
#define SOC_DSS_DPP_U_IGM_R_COEF_ADDR(base)           ((base) + (0xB000))

/* �Ĵ���˵����IGM G�������ұ�
   λ����UNION�ṹ:  SOC_DSS_DPP_U_IGM_G_COEF_UNION */
#define SOC_DSS_DPP_U_IGM_G_COEF_ADDR(base)           ((base) + (0xB400))

/* �Ĵ���˵����IGM B�������ұ�
   λ����UNION�ṹ:  SOC_DSS_DPP_U_IGM_B_COEF_UNION */
#define SOC_DSS_DPP_U_IGM_B_COEF_ADDR(base)           ((base) + (0xB800))





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
                     (1/1) reg_DPP
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_DPP_RD_SHADOW_SEL_UNION
 �ṹ˵��  : DPP_RD_SHADOW_SEL �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���Ĵ���ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_rd_shadow : 1;  /* bit[0]   : 1'b0 :�������Ĵ���
                                                        1'b1 :��Ӱ�ӼĴ��� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DPP_DPP_RD_SHADOW_SEL_UNION;
#endif
#define SOC_DSS_DPP_DPP_RD_SHADOW_SEL_dpp_rd_shadow_START  (0)
#define SOC_DSS_DPP_DPP_RD_SHADOW_SEL_dpp_rd_shadow_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_DPP_ID_UNION
 �ṹ˵��  : DPP_ID �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00003650�����:32
 �Ĵ���˵��: DPP�汾��Ϣ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp0_id : 32; /* bit[0-31]: ���� */
    } reg;
} SOC_DSS_DPP_DPP_ID_UNION;
#endif
#define SOC_DSS_DPP_DPP_ID_dpp0_id_START  (0)
#define SOC_DSS_DPP_DPP_ID_dpp0_id_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_DPP_IMG_HRZ_UNION
 �ṹ˵��  : DPP_IMG_HRZ �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: DPPͼ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp0_size_hrz : 13; /* bit[0-12] : DPPͼ����-1 */
        unsigned int  reserved      : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_DSS_DPP_DPP_IMG_HRZ_UNION;
#endif
#define SOC_DSS_DPP_DPP_IMG_HRZ_dpp0_size_hrz_START  (0)
#define SOC_DSS_DPP_DPP_IMG_HRZ_dpp0_size_hrz_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_DPP_IMG_VRT_UNION
 �ṹ˵��  : DPP_IMG_VRT �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DPPͼ��߶�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp0_size_vrz : 13; /* bit[0-12] : DPPͼ��߶�-1 */
        unsigned int  reserved      : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_DSS_DPP_DPP_IMG_VRT_UNION;
#endif
#define SOC_DSS_DPP_DPP_IMG_VRT_dpp0_size_vrz_START  (0)
#define SOC_DSS_DPP_DPP_IMG_VRT_dpp0_size_vrz_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CLRBAR_CTRL_UNION
 �ṹ˵��  : CLRBAR_CTRL �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: COLORBAR���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clrbar_en    : 1;  /* bit[0-0]  : colorbarʹ�ܣ�
                                                        0�� colorbar �رգ�
                                                        1�� colorbar ������ */
        unsigned int  clrbar_mode  : 1;  /* bit[1-1]  : colorbarģʽѡ��
                                                        00��������
                                                        01��������
                                                        ������������ */
        unsigned int  reserved     : 22; /* bit[2-23] : ���� */
        unsigned int  clrbar_width : 8;  /* bit[24-31]: corlorbar RGB������ȣ�д��ֵΪʵ��ֵ��1��ȡֵ��ΧΪ1~256 */
    } reg;
} SOC_DSS_DPP_CLRBAR_CTRL_UNION;
#endif
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_en_START     (0)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_en_END       (0)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_mode_START   (1)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_mode_END     (1)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_width_START  (24)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_width_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_DITHER_UNION
 �ṹ˵��  : DITHER �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: DITHER���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dither_en  : 1;  /* bit[0]   : Ditheringʹ�ܣ�
                                                     0��Dithering��ʹ��
                                                     1��Ditheringʹ�� */
        unsigned int  dither_fmt : 1;  /* bit[1]   : dither���������λ��
                                                     0: 16bpp��
                                                     1: 18bpp�� */
        unsigned int  dither_sel : 1;  /* bit[2]   : �����㷨ѡ��
                                                     0�������������뷨���������ͳһ�������ʽ
                                                     1������Dithering�㷨���������ͳһ�������ʽ�� */
        unsigned int  reserved   : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_DSS_DPP_DITHER_UNION;
#endif
#define SOC_DSS_DPP_DITHER_dither_en_START   (0)
#define SOC_DSS_DPP_DITHER_dither_en_END     (0)
#define SOC_DSS_DPP_DITHER_dither_fmt_START  (1)
#define SOC_DSS_DPP_DITHER_dither_fmt_END    (1)
#define SOC_DSS_DPP_DITHER_dither_sel_START  (2)
#define SOC_DSS_DPP_DITHER_dither_sel_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_SBL_UNION
 �ṹ˵��  : SBL �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: SBL���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sbl_en   : 1;  /* bit[0]   : SBLʹ�ܼĴ���
                                                   0��sbl bypass 
                                                   1��sblʹ�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DPP_SBL_UNION;
#endif
#define SOC_DSS_DPP_SBL_sbl_en_START    (0)
#define SOC_DSS_DPP_SBL_sbl_en_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_DPP_CLK_SEL_UNION
 �ṹ˵��  : DPP_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                      1����ʾǿ�ƴ�ʱ�ӡ�
                                                      0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                      bit0������apb��
                                                      bit1������reg��
                                                      bit2������sbl��
                                                      bit3������cb��
                                                      bit4������acm��
                                                      bit5������lcp��
                                                      bit6������gama��
                                                      bit7������dith�� */
    } reg;
} SOC_DSS_DPP_DPP_CLK_SEL_UNION;
#endif
#define SOC_DSS_DPP_DPP_CLK_SEL_dpp_clk_sel_START  (0)
#define SOC_DSS_DPP_DPP_CLK_SEL_dpp_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_DPP_CLK_EN_UNION
 �ṹ˵��  : DPP_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                     1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                     0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                     bit0������apb��
                                                     bit1������reg��
                                                     bit2������sbl��
                                                     bit3������cb��
                                                     bit4������acm��
                                                     bit5������lcp��
                                                     bit6������gama��
                                                     bit7������dith�� */
    } reg;
} SOC_DSS_DPP_DPP_CLK_EN_UNION;
#endif
#define SOC_DSS_DPP_DPP_CLK_EN_dpp_clk_en_START  (0)
#define SOC_DSS_DPP_DPP_CLK_EN_dpp_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_DPP_DBG_CNT_UNION
 �ṹ˵��  : DPP_DBG_CNT �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: DPP �������������������debug
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_h_cnt : 13; /* bit[0-12] : ˮƽ��ȼ����� */
        unsigned int  reserved_0: 3;  /* bit[13-15]: ���� */
        unsigned int  dpp_v_cnt : 13; /* bit[16-28]: ��ֱ���������� */
        unsigned int  reserved_1: 3;  /* bit[29-31]: ���� */
    } reg;
} SOC_DSS_DPP_DPP_DBG_CNT_UNION;
#endif
#define SOC_DSS_DPP_DPP_DBG_CNT_dpp_h_cnt_START  (0)
#define SOC_DSS_DPP_DPP_DBG_CNT_dpp_h_cnt_END    (12)
#define SOC_DSS_DPP_DPP_DBG_CNT_dpp_v_cnt_START  (16)
#define SOC_DSS_DPP_DPP_DBG_CNT_dpp_v_cnt_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_LCP_XCC_COEF_00_UNION
 �ṹ˵��  : LCP_XCC_COEF_00 �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_00  : 16; /* bit[0-15] : XCCϵ��00 */
        unsigned int  reserved : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_00_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_00_coef_00_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_00_coef_00_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_LCP_XCC_COEF_01_UNION
 �ṹ˵��  : LCP_XCC_COEF_01 �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00008000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_01  : 17; /* bit[0-16] : XCCϵ��01 */
        unsigned int  reserved : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_01_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_01_coef_01_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_01_coef_01_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_LCP_XCC_COEF_02_UNION
 �ṹ˵��  : LCP_XCC_COEF_02 �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_02  : 17; /* bit[0-16] : XCCϵ��02 */
        unsigned int  reserved : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_02_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_02_coef_02_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_02_coef_02_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_LCP_XCC_COEF_03_UNION
 �ṹ˵��  : LCP_XCC_COEF_03 �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_03  : 17; /* bit[0-16] : XCCϵ��03 */
        unsigned int  reserved : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_03_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_03_coef_03_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_03_coef_03_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_LCP_XCC_COEF_10_UNION
 �ṹ˵��  : LCP_XCC_COEF_10 �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_10  : 16; /* bit[0-15] : XCCϵ��10 */
        unsigned int  reserved : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_10_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_10_coef_10_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_10_coef_10_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_LCP_XCC_COEF_11_UNION
 �ṹ˵��  : LCP_XCC_COEF_11 �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_11  : 17; /* bit[0-16] : XCCϵ��11 */
        unsigned int  reserved : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_11_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_11_coef_11_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_11_coef_11_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_LCP_XCC_COEF_12_UNION
 �ṹ˵��  : LCP_XCC_COEF_12 �Ĵ����ṹ���塣��ַƫ����:0x118����ֵ:0x00008000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_12  : 17; /* bit[0-16] : XCCϵ��12 */
        unsigned int  reserved : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_12_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_12_coef_12_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_12_coef_12_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_LCP_XCC_COEF_13_UNION
 �ṹ˵��  : LCP_XCC_COEF_13 �Ĵ����ṹ���塣��ַƫ����:0x11C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_13  : 17; /* bit[0-16] : XCCϵ��13 */
        unsigned int  reserved : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_13_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_13_coef_13_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_13_coef_13_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_LCP_XCC_COEF_20_UNION
 �ṹ˵��  : LCP_XCC_COEF_20 �Ĵ����ṹ���塣��ַƫ����:0x120����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_20  : 16; /* bit[0-15] : XCCϵ��20 */
        unsigned int  reserved : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_20_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_20_coef_20_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_20_coef_20_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_LCP_XCC_COEF_21_UNION
 �ṹ˵��  : LCP_XCC_COEF_21 �Ĵ����ṹ���塣��ַƫ����:0x124����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_21  : 17; /* bit[0-16] : XCCϵ��21 */
        unsigned int  reserved : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_21_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_21_coef_21_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_21_coef_21_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_LCP_XCC_COEF_22_UNION
 �ṹ˵��  : LCP_XCC_COEF_22 �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_22  : 17; /* bit[0-16] : XCCϵ��22 */
        unsigned int  reserved : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_22_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_22_coef_22_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_22_coef_22_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_LCP_XCC_COEF_23_UNION
 �ṹ˵��  : LCP_XCC_COEF_23 �Ĵ����ṹ���塣��ַƫ����:0x12C����ֵ:0x00008000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_23  : 17; /* bit[0-16] : XCCϵ��23 */
        unsigned int  reserved : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_23_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_23_coef_23_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_23_coef_23_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_GMP_BYPASS_EN_UNION
 �ṹ˵��  : GMP_BYPASS_EN �Ĵ����ṹ���塣��ַƫ����:0x130����ֵ:0x00000001�����:32
 �Ĵ���˵��: ����������Чλѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gmp_bypass_en : 1;  /* bit[0]   : 1��GMP��· */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DPP_GMP_BYPASS_EN_UNION;
#endif
#define SOC_DSS_DPP_GMP_BYPASS_EN_gmp_bypass_en_START  (0)
#define SOC_DSS_DPP_GMP_BYPASS_EN_gmp_bypass_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_XCC_BYPASS_EN_UNION
 �ṹ˵��  : XCC_BYPASS_EN �Ĵ����ṹ���塣��ַƫ����:0x134����ֵ:0x00000001�����:32
 �Ĵ���˵��: ��·GAMAģ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xcc_bypass_en : 1;  /* bit[0]   : 1��XCC��· */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DPP_XCC_BYPASS_EN_UNION;
#endif
#define SOC_DSS_DPP_XCC_BYPASS_EN_xcc_bypass_en_START  (0)
#define SOC_DSS_DPP_XCC_BYPASS_EN_xcc_bypass_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_IGM_MEM_CTRL_UNION
 �ṹ˵��  : IGM_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x138����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  igm_mem_ctrl : 4;  /* bit[0-3] : ���ԼĴ�����igmģ����memory�͹������ã�
                                                       [3]: reseverd; 
                                                       [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                       [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                       [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved     : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_DPP_IGM_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_IGM_MEM_CTRL_igm_mem_ctrl_START  (0)
#define SOC_DSS_DPP_IGM_MEM_CTRL_igm_mem_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_GMP_MEM_CTRL_UNION
 �ṹ˵��  : GMP_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x13C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gmp_mem_ctrl : 4;  /* bit[0-3] : ���ԼĴ�����gmpģ����memory�͹������ã�
                                                       [3]: reseverd; 
                                                       [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                       [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                       [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved     : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_DPP_GMP_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_GMP_MEM_CTRL_gmp_mem_ctrl_START  (0)
#define SOC_DSS_DPP_GMP_MEM_CTRL_gmp_mem_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_R0_H_UNION
 �ṹ˵��  : R0_H �Ĵ����ṹ���塣��ַƫ����:0x200����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����0ɫ����������ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r0_lh    : 10; /* bit[0-9]  : ����0��ɫ������ֵ */
        unsigned int  reserved_0: 6;  /* bit[10-15]: ���� */
        unsigned int  r0_hh    : 10; /* bit[16-25]: ����0��ɫ������ֵ */
        unsigned int  reserved_1: 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_DSS_DPP_R0_H_UNION;
#endif
#define SOC_DSS_DPP_R0_H_r0_lh_START     (0)
#define SOC_DSS_DPP_R0_H_r0_lh_END       (9)
#define SOC_DSS_DPP_R0_H_r0_hh_START     (16)
#define SOC_DSS_DPP_R0_H_r0_hh_END       (25)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_R1_H_UNION
 �ṹ˵��  : R1_H �Ĵ����ṹ���塣��ַƫ����:0x204����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����1ɫ����������ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r1_lh    : 10; /* bit[0-9]  : ����1��ɫ������ֵ */
        unsigned int  reserved_0: 6;  /* bit[10-15]: ���� */
        unsigned int  r1_hh    : 10; /* bit[16-25]: ����1��ɫ������ֵ */
        unsigned int  reserved_1: 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_DSS_DPP_R1_H_UNION;
#endif
#define SOC_DSS_DPP_R1_H_r1_lh_START     (0)
#define SOC_DSS_DPP_R1_H_r1_lh_END       (9)
#define SOC_DSS_DPP_R1_H_r1_hh_START     (16)
#define SOC_DSS_DPP_R1_H_r1_hh_END       (25)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_R2_H_UNION
 �ṹ˵��  : R2_H �Ĵ����ṹ���塣��ַƫ����:0x208����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����2ɫ����������ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r2_lh    : 10; /* bit[0-9]  : ����2��ɫ������ֵ */
        unsigned int  reserved_0: 6;  /* bit[10-15]: ���� */
        unsigned int  r2_hh    : 10; /* bit[16-25]: ����2��ɫ������ֵ */
        unsigned int  reserved_1: 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_DSS_DPP_R2_H_UNION;
#endif
#define SOC_DSS_DPP_R2_H_r2_lh_START     (0)
#define SOC_DSS_DPP_R2_H_r2_lh_END       (9)
#define SOC_DSS_DPP_R2_H_r2_hh_START     (16)
#define SOC_DSS_DPP_R2_H_r2_hh_END       (25)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_R3_H_UNION
 �ṹ˵��  : R3_H �Ĵ����ṹ���塣��ַƫ����:0x20C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����3ɫ����������ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r3_lh    : 10; /* bit[0-9]  : ����3��ɫ������ֵ */
        unsigned int  reserved_0: 6;  /* bit[10-15]: ���� */
        unsigned int  r3_hh    : 10; /* bit[16-25]: ����3��ɫ������ֵ */
        unsigned int  reserved_1: 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_DSS_DPP_R3_H_UNION;
#endif
#define SOC_DSS_DPP_R3_H_r3_lh_START     (0)
#define SOC_DSS_DPP_R3_H_r3_lh_END       (9)
#define SOC_DSS_DPP_R3_H_r3_hh_START     (16)
#define SOC_DSS_DPP_R3_H_r3_hh_END       (25)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_R4_H_UNION
 �ṹ˵��  : R4_H �Ĵ����ṹ���塣��ַƫ����:0x210����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����4ɫ����������ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r4_lh    : 10; /* bit[0-9]  : ����4��ɫ������ֵ */
        unsigned int  reserved_0: 6;  /* bit[10-15]: ���� */
        unsigned int  r4_hh    : 10; /* bit[16-25]: ����4��ɫ������ֵ */
        unsigned int  reserved_1: 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_DSS_DPP_R4_H_UNION;
#endif
#define SOC_DSS_DPP_R4_H_r4_lh_START     (0)
#define SOC_DSS_DPP_R4_H_r4_lh_END       (9)
#define SOC_DSS_DPP_R4_H_r4_hh_START     (16)
#define SOC_DSS_DPP_R4_H_r4_hh_END       (25)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_R5_H_UNION
 �ṹ˵��  : R5_H �Ĵ����ṹ���塣��ַƫ����:0x214����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����5ɫ����������ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r5_lh    : 10; /* bit[0-9]  : ����5��ɫ������ֵ */
        unsigned int  reserved_0: 6;  /* bit[10-15]: ���� */
        unsigned int  r5_hh    : 10; /* bit[16-25]: ����5��ɫ������ֵ */
        unsigned int  reserved_1: 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_DSS_DPP_R5_H_UNION;
#endif
#define SOC_DSS_DPP_R5_H_r5_lh_START     (0)
#define SOC_DSS_DPP_R5_H_r5_lh_END       (9)
#define SOC_DSS_DPP_R5_H_r5_hh_START     (16)
#define SOC_DSS_DPP_R5_H_r5_hh_END       (25)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_R6_H_UNION
 �ṹ˵��  : R6_H �Ĵ����ṹ���塣��ַƫ����:0x218����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����6ɫ����������ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r6_lh    : 10; /* bit[0-9]  : ����6��ɫ������ֵ */
        unsigned int  reserved_0: 6;  /* bit[10-15]: ���� */
        unsigned int  r6_hh    : 10; /* bit[16-25]: ����6��ɫ������ֵ */
        unsigned int  reserved_1: 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_DSS_DPP_R6_H_UNION;
#endif
#define SOC_DSS_DPP_R6_H_r6_lh_START     (0)
#define SOC_DSS_DPP_R6_H_r6_lh_END       (9)
#define SOC_DSS_DPP_R6_H_r6_hh_START     (16)
#define SOC_DSS_DPP_R6_H_r6_hh_END       (25)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_ACM_EN_UNION
 �ṹ˵��  : ACM_EN �Ĵ����ṹ���塣��ַƫ����:0x21C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acm_en        : 1;  /* bit[0]   : ACMʹ�ܼĴ��� */
        unsigned int  reserved_0    : 3;  /* bit[1-3] : ���� */
        unsigned int  acm_valid_num : 3;  /* bit[4-6] : ����ѡ��Ĵ�����ɫ�ȵ�������ѡ�� */
        unsigned int  reserved_1    : 25; /* bit[7-31]: ���� */
    } reg;
} SOC_DSS_DPP_ACM_EN_UNION;
#endif
#define SOC_DSS_DPP_ACM_EN_acm_en_START         (0)
#define SOC_DSS_DPP_ACM_EN_acm_en_END           (0)
#define SOC_DSS_DPP_ACM_EN_acm_valid_num_START  (4)
#define SOC_DSS_DPP_ACM_EN_acm_valid_num_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_ACM_MEM_CTRL_UNION
 �ṹ˵��  : ACM_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x220����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acm_mem_ctrl : 4;  /* bit[0-3] : ���ԼĴ�����acmģ����memory�͹������ã�
                                                       [3]: reseverd; 
                                                       [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                       [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                       [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved     : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_DPP_ACM_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_ACM_MEM_CTRL_acm_mem_ctrl_START  (0)
#define SOC_DSS_DPP_ACM_MEM_CTRL_acm_mem_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_HIST_RESET_UNION
 �ṹ˵��  : CE_HIST_RESET �Ĵ����ṹ���塣��ַƫ����:0x230����ֵ:0x00000000�����:32
 �Ĵ���˵��: ֱ��ͼͳ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_hist_reset : 1;  /* bit[0]   : 1��b1����ͳ�������㡣
                                                        1��b0������ͳ��
                                                        �������˵��д��Ĵ�������Ӳ����˵�Ƚ�д1�Ķ������������ȵ�֡ͬ�������ֱ��ͼͳ�Ƶ���Ϣ���㡣 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_HIST_RESET_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_RESET_ce_hist_reset_START  (0)
#define SOC_DSS_DPP_CE_HIST_RESET_ce_hist_reset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_HIST_CTL_UNION
 �ṹ˵��  : CE_HIST_CTL �Ĵ����ṹ���塣��ַƫ����:0x234����ֵ:0x00000000�����:32
 �Ĵ���˵��: ֱ��ͼͳ�ƿ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_hist_ctl : 3;  /* bit[0-2] : bit0: start д1��֡ͬ���ﵽ��ʼͳ��
                                                      bit1: cancle д1������ֹͣͳ��
                                                      bit2: stop д1��ȴ�֡ͬ�������ֹͣͳ�ơ� */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_HIST_CTL_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_CTL_ce_hist_ctl_START  (0)
#define SOC_DSS_DPP_CE_HIST_CTL_ce_hist_ctl_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_HIST_FRAME_CNT_UNION
 �ṹ˵��  : CE_HIST_FRAME_CNT �Ĵ����ṹ���塣��ַƫ����:0x238����ֵ:0x00000000�����:32
 �Ĵ���˵��: ֱ��ͼͳ�Ƶ�֡����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_hist_frame_cnt : 6;  /* bit[0-5] : 2560x1600 �C 4
                                                            XGA (1024 x 768) - 21 
                                                            WSVGA (1024 x 600) - 27 
                                                            WVGA (800 x 480) - 43 
                                                            VGA (640 x 480) - 54 
                                                            Reset State: 0x0 */
        unsigned int  reserved          : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_HIST_FRAME_CNT_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_FRAME_CNT_ce_hist_frame_cnt_START  (0)
#define SOC_DSS_DPP_CE_HIST_FRAME_CNT_ce_hist_frame_cnt_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_SIZE_UNION
 �ṹ˵��  : CE_SIZE �Ĵ����ṹ���塣��ַƫ����:0x23C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͼ��Ŀ�͸�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_height : 13; /* bit[0-12] : ͼ��Ŀ�-1 */
        unsigned int  reserved_0: 3;  /* bit[13-15]: ���� */
        unsigned int  ce_width  : 13; /* bit[16-28]: ͼ��ĸ�-1 */
        unsigned int  reserved_1: 3;  /* bit[29-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_SIZE_UNION;
#endif
#define SOC_DSS_DPP_CE_SIZE_ce_height_START  (0)
#define SOC_DSS_DPP_CE_SIZE_ce_height_END    (12)
#define SOC_DSS_DPP_CE_SIZE_ce_width_START   (16)
#define SOC_DSS_DPP_CE_SIZE_ce_width_END     (28)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_NO_STAT_LINES_UNION
 �ṹ˵��  : CE_NO_STAT_LINES �Ĵ����ṹ���塣��ַƫ����:0x240����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���һ֡������в�����ֱ��ͼͳ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_no_stat_lines : 8;  /* bit[0-7] : ce_hist_frame_cnt��ֵΪn����n֮֡ǰ��ȫ������ͳ��ֱ��ͼ����n֡�����ce_no_stat_lines�в�ͳ�ơ�ͳ�ƽ�������ϱ��жϡ� */
        unsigned int  reserved         : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_NO_STAT_LINES_UNION;
#endif
#define SOC_DSS_DPP_CE_NO_STAT_LINES_ce_no_stat_lines_START  (0)
#define SOC_DSS_DPP_CE_NO_STAT_LINES_ce_no_stat_lines_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_BLACK_REGION_THRE_UNION
 �ṹ˵��  : CE_BLACK_REGION_THRE �Ĵ����ṹ���塣��ַƫ����:0x244����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_black_region_thre : 8;  /* bit[0-7] : ������ֵ���Ҷ�С�����ֵ����ֵ��1 */
        unsigned int  reserved             : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_BLACK_REGION_THRE_UNION;
#endif
#define SOC_DSS_DPP_CE_BLACK_REGION_THRE_ce_black_region_thre_START  (0)
#define SOC_DSS_DPP_CE_BLACK_REGION_THRE_ce_black_region_thre_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_WHITE_REGION_THRE_UNION
 �ṹ˵��  : CE_WHITE_REGION_THRE �Ĵ����ṹ���塣��ַƫ����:0x248����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_white_region_thre : 8;  /* bit[0-7] : ������ֵ���Ҷȴ������ֵ����ֵ��1 */
        unsigned int  reserved             : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_WHITE_REGION_THRE_UNION;
#endif
#define SOC_DSS_DPP_CE_WHITE_REGION_THRE_ce_white_region_thre_START  (0)
#define SOC_DSS_DPP_CE_WHITE_REGION_THRE_ce_white_region_thre_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_LUT_SEL_UNION
 �ṹ˵��  : CE_LUT_SEL �Ĵ����ṹ���塣��ַƫ����:0x24C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LUT��ƹ��ѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_lut_sel : 1;  /* bit[0]   : ����ƹ��LUT�Ķ�дȨ�޷��䡣
                                                     0����ʾ�����LUT0����дȨ�ޣ�оƬ��LUT1���ж�Ȩ�ޡ�
                                                     1����ʾ�����LUT1����дȨ�ޣ�оƬ��LUT0���ж�Ȩ�ޡ� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_LUT_SEL_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT_SEL_ce_lut_sel_START  (0)
#define SOC_DSS_DPP_CE_LUT_SEL_ce_lut_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_LUT_ENABLE_UNION
 �ṹ˵��  : CE_LUT_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x250����ֵ:0x00000000�����:32
 �Ĵ���˵��: CE��·ѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_lut_enable  : 1;  /* bit[0]   : 1��Y������ֵ��ΪLUT��ĵ�ַ���ó��µ�Y������
                                                         0��CE��·��Y�������ò�LUT��ֱ���͸��󼶡� */
        unsigned int  ce_hist_enable : 1;  /* bit[1]   : 1��ceֱ��ͼͳ�ƹ���ʹ��
                                                         0��ceֱ��ͼͳ�ƹ��ܲ�ʹ�� */
        unsigned int  reserved       : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_LUT_ENABLE_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT_ENABLE_ce_lut_enable_START   (0)
#define SOC_DSS_DPP_CE_LUT_ENABLE_ce_lut_enable_END     (0)
#define SOC_DSS_DPP_CE_LUT_ENABLE_ce_hist_enable_START  (1)
#define SOC_DSS_DPP_CE_LUT_ENABLE_ce_hist_enable_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_LUT_USING_IND_UNION
 �ṹ˵��  : CE_LUT_USING_IND �Ĵ����ṹ���塣��ַƫ����:0x254����ֵ:0x00000000�����:32
 �Ĵ���˵��: LUT��дȨ�޷���ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_lut_using_ind : 1;  /* bit[0]   : ָʾĿǰƹ��LUT�Ķ�дȨ�޵ķ������
                                                           0����ʾ�����LUT0���ж�дȨ�ޣ�о��LUT1���ж�дȨ�ޡ�
                                                           1����ʾ�����LUT1���ж�дȨ�ޣ�оƬLUT0���ж�дȨ�ޡ� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_LUT_USING_IND_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT_USING_IND_ce_lut_using_ind_START  (0)
#define SOC_DSS_DPP_CE_LUT_USING_IND_ce_lut_using_ind_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_STATE_IND_UNION
 �ṹ˵��  : CE_STATE_IND �Ĵ����ṹ���塣��ַƫ����:0x258����ֵ:0x00000000�����:32
 �Ĵ���˵��: CE����ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_state_ind : 1;  /* bit[0]   : ���Թ۲�ʹ��
                                                       1:CEģ�鴦�ڹ���״̬
                                                       0��CEģ�鴦�ڿ���״̬ */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_STATE_IND_UNION;
#endif
#define SOC_DSS_DPP_CE_STATE_IND_ce_state_ind_START  (0)
#define SOC_DSS_DPP_CE_STATE_IND_ce_state_ind_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_MEM_CTRL_UNION
 �ṹ˵��  : CE_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x25C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CE MEM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_lut_mem_ctrl : 4;  /* bit[0-3] : ���ԼĴ�����ce lutģ����memory�͹������ã� 
                                                          [3]: reseverd; 
                                                          [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                          [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                          [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  ce_his_mem_ctrl : 4;  /* bit[4-7] : ���ԼĴ�����ce hisģ����memory�͹������ã�
                                                          [3]: reseverd; 
                                                          [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                          [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                          [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved        : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_CE_MEM_CTRL_ce_lut_mem_ctrl_START  (0)
#define SOC_DSS_DPP_CE_MEM_CTRL_ce_lut_mem_ctrl_END    (3)
#define SOC_DSS_DPP_CE_MEM_CTRL_ce_his_mem_ctrl_START  (4)
#define SOC_DSS_DPP_CE_MEM_CTRL_ce_his_mem_ctrl_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_TOTALGRAY_UNION
 �ṹ˵��  : CE_TOTALGRAY �Ĵ����ṹ���塣��ַƫ����:0x264����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���лҶ��ܺ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_totalgray : 32; /* bit[0-31]: �ܻҶ� */
    } reg;
} SOC_DSS_DPP_CE_TOTALGRAY_UNION;
#endif
#define SOC_DSS_DPP_CE_TOTALGRAY_ce_totalgray_START  (0)
#define SOC_DSS_DPP_CE_TOTALGRAY_ce_totalgray_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_TOTALPIXL_UNION
 �ṹ˵��  : CE_TOTALPIXL �Ĵ����ṹ���塣��ַƫ����:0x268����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������صĸ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_totalpixl : 24; /* bit[0-23] : ͳ�Ƶ������ظ����� */
        unsigned int  reserved     : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_TOTALPIXL_UNION;
#endif
#define SOC_DSS_DPP_CE_TOTALPIXL_ce_totalpixl_START  (0)
#define SOC_DSS_DPP_CE_TOTALPIXL_ce_totalpixl_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_MEAN_UNION
 �ṹ˵��  : CE_MEAN �Ĵ����ṹ���塣��ַƫ����:0x26C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ֱ��ͼ���ֵ��Ӧ�ĻҶ�ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_mean  : 8;  /* bit[0-7] : һ���Ҷ�ֵ������Ҷ�ֵ��Ӧ���������. */
        unsigned int  reserved : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_MEAN_UNION;
#endif
#define SOC_DSS_DPP_CE_MEAN_ce_mean_START   (0)
#define SOC_DSS_DPP_CE_MEAN_ce_mean_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_PEC0_3_UNION
 �ṹ˵��  : CE_PEC0_3 �Ĵ����ṹ���塣��ַƫ����:0x270����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��λ��0~3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_pec0 : 8;  /* bit[0-7]  : ��λ��0�Ҷ�ֵ */
        unsigned int  ce_pec1 : 8;  /* bit[8-15] : ��λ��1�Ҷ�ֵ */
        unsigned int  ce_pec2 : 8;  /* bit[16-23]: ��λ��2�Ҷ�ֵ */
        unsigned int  ce_pec3 : 8;  /* bit[24-31]: ��λ��3�Ҷ�ֵ */
    } reg;
} SOC_DSS_DPP_CE_PEC0_3_UNION;
#endif
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec0_START  (0)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec0_END    (7)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec1_START  (8)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec1_END    (15)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec2_START  (16)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec2_END    (23)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec3_START  (24)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_PEC4_7_UNION
 �ṹ˵��  : CE_PEC4_7 �Ĵ����ṹ���塣��ַƫ����:0x274����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��λ��4~7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_pec4 : 8;  /* bit[0-7]  : ��λ��4�Ҷ�ֵ */
        unsigned int  ce_pec5 : 8;  /* bit[8-15] : ��λ��5�Ҷ�ֵ */
        unsigned int  ce_pec6 : 8;  /* bit[16-23]: ��λ��6�Ҷ�ֵ */
        unsigned int  ce_pec7 : 8;  /* bit[24-31]: ��λ��7�Ҷ�ֵ */
    } reg;
} SOC_DSS_DPP_CE_PEC4_7_UNION;
#endif
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec4_START  (0)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec4_END    (7)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec5_START  (8)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec5_END    (15)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec6_START  (16)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec6_END    (23)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec7_START  (24)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_PEC8_UNION
 �ṹ˵��  : CE_PEC8 �Ĵ����ṹ���塣��ַƫ����:0x278����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��λ��8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_pec8  : 8;  /* bit[0-7] : ��λ��8�Ҷ�ֵ */
        unsigned int  reserved : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_PEC8_UNION;
#endif
#define SOC_DSS_DPP_CE_PEC8_ce_pec8_START   (0)
#define SOC_DSS_DPP_CE_PEC8_ce_pec8_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_BLACK_NUM_UNION
 �ṹ˵��  : CE_BLACK_NUM �Ĵ����ṹ���塣��ַƫ����:0x27C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_black_num : 24; /* bit[0-23] : ������� */
        unsigned int  reserved     : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_BLACK_NUM_UNION;
#endif
#define SOC_DSS_DPP_CE_BLACK_NUM_ce_black_num_START  (0)
#define SOC_DSS_DPP_CE_BLACK_NUM_ce_black_num_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_WHITE_NUM_UNION
 �ṹ˵��  : CE_WHITE_NUM �Ĵ����ṹ���塣��ַƫ����:0x280����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_white_num : 24; /* bit[0-23] : ������� */
        unsigned int  reserved     : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_WHITE_NUM_UNION;
#endif
#define SOC_DSS_DPP_CE_WHITE_NUM_ce_white_num_START  (0)
#define SOC_DSS_DPP_CE_WHITE_NUM_ce_white_num_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_HIST_RPT_IND_UNION
 �ṹ˵��  : CE_HIST_RPT_IND �Ĵ����ṹ���塣��ַƫ����:0x284����ֵ:0x00000001�����:32
 �Ĵ���˵��: �ϱ�ֱ��ͼָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_hist_rpt_ind : 1;  /* bit[0]   : 0����ʾ��ȡֱ��ͼmemory0���ϱ����
                                                          1����ʾ��ȡֱ��ͼmemory1���ϱ���� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_HIST_RPT_IND_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_RPT_IND_ce_hist_rpt_ind_START  (0)
#define SOC_DSS_DPP_CE_HIST_RPT_IND_ce_hist_rpt_ind_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_GAMA_SHORTBIT_EN_UNION
 �ṹ˵��  : GAMA_SHORTBIT_EN �Ĵ����ṹ���塣��ַƫ����:0x300����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����������Чλѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shortbit_en : 1;  /* bit[0]   : 1������24bit���������룻
                                                      0������36bit���������� */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DPP_GAMA_SHORTBIT_EN_UNION;
#endif
#define SOC_DSS_DPP_GAMA_SHORTBIT_EN_shortbit_en_START  (0)
#define SOC_DSS_DPP_GAMA_SHORTBIT_EN_shortbit_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_GAMA_BYPASS_EN_UNION
 �ṹ˵��  : GAMA_BYPASS_EN �Ĵ����ṹ���塣��ַƫ����:0x304����ֵ:0x00000001�����:32
 �Ĵ���˵��: ��·GAMAģ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass_en : 1;  /* bit[0]   : 1��GAMA����· */
        unsigned int  reserved  : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DPP_GAMA_BYPASS_EN_UNION;
#endif
#define SOC_DSS_DPP_GAMA_BYPASS_EN_bypass_en_START  (0)
#define SOC_DSS_DPP_GAMA_BYPASS_EN_bypass_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_GAMA_MEM_CTRL_UNION
 �ṹ˵��  : GAMA_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x308����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gama_mem_ctrl : 4;  /* bit[0-3] : ���ԼĴ�����gamaģ����memory�͹������ã�
                                                        [3]: reseverd; 
                                                        [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                        [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                        [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved      : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_DPP_GAMA_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_GAMA_MEM_CTRL_gama_mem_ctrl_START  (0)
#define SOC_DSS_DPP_GAMA_MEM_CTRL_gama_mem_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_REG_DEFAULT_UNION
 �ṹ˵��  : REG_DEFAULT �Ĵ����ṹ���塣��ַƫ����:0x030C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg_default : 1;  /* bit[0]   :  */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_DPP_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_DPP_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_DPP_REG_DEFAULT_reg_default_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_SBL_MEM_CTRL_UNION
 �ṹ˵��  : SBL_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x310����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sbl_mem_ctrl : 4;  /* bit[0-3] : ���ԼĴ�����sblģ����memory�͹������ã�
                                                       [3]: reseverd; 
                                                       [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                       [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                       [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved     : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_DPP_SBL_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_SBL_MEM_CTRL_sbl_mem_ctrl_START  (0)
#define SOC_DSS_DPP_SBL_MEM_CTRL_sbl_mem_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_DPP_DBG_UNION
 �ṹ˵��  : DPP_DBG �Ĵ����ṹ���塣��ַƫ����:0x314����ֵ:0x00010000�����:32
 �Ĵ���˵��: DPP�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_dbg : 32; /* bit[0-31]: [31:18]:reserved;
                                                  [17]��sbl��λʹ�ܡ�
                                                   1'b0����λ��ʹ��
                                                   1'b1����λʹ��
                                                  [16]��sbl��λ��Ӳ������ģʽѡ��
                                                   1'b0��ѡ��sbl��underflow�����µ���λģʽ
                                                   1'b1��ѡ��sbl��underflow�����µ�Ӳ������ģʽ
                                                  [15:4]:reserved;
                                                  [3]��ѡ��ACM LUT��������ʱ���Ƿ�����ɿ�.
                                                   1'b0��������ɿأ������ACM��ʹ�ܻ���DPP�ǹ���״̬ʱ��������ACM LUT��
                                                   1'b1������ɿأ������ͨ��bit2��ѡ��ACM LUT�Ƿ�������䣻
                                                  [2]��ACM LUT�Ƿ��������.
                                                   1'b0����ʱACM LUT������䣬���������ʱACM���ڹ�����ACM��LUT��������Ϊ0��
                                                   1'b1�����ACMʹ�ܣ�����������䣬���ACM��ʹ�ܣ�������䣻
                                                  [1]��reserved;
                                                  [0]��ѡ���͸�SBL��frm_end����DPP�ڲ�����ldi_frm_end.
                                                   1'b0��DPP�ڲ�frm_end
                                                   1'b1�� ldi_frm_end */
    } reg;
} SOC_DSS_DPP_DPP_DBG_UNION;
#endif
#define SOC_DSS_DPP_DPP_DBG_dpp_dbg_START  (0)
#define SOC_DSS_DPP_DPP_DBG_dpp_dbg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_U_GAMA_COEF_UNION
 �ṹ˵��  : U_GAMA_COEF �Ĵ����ṹ���塣��ַƫ����:0x0400����ֵ:0x00000000�����:32
 �Ĵ���˵��: GAMAϵ�����ұ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_gama_coef : 8;  /* bit[0-7] : GAMAϵ�����ұ����ַ�������������֧������ϵ�����Ա */
        unsigned int  reserved    : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_DPP_U_GAMA_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_GAMA_COEF_u_gama_coef_START  (0)
#define SOC_DSS_DPP_U_GAMA_COEF_u_gama_coef_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_U_H_COEF_UNION
 �ṹ˵��  : U_H_COEF �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ACM H�������ұ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  h_l_out  : 10; /* bit[0-9]  : U_HL_COEFϵ�����ұ����ַ�������������֧������ϵ�����Ա */
        unsigned int  reserved_0: 6;  /* bit[10-15]: ���� */
        unsigned int  h_r_out  : 10; /* bit[16-25]: U_HR_COEFϵ�����ұ����ַ�������������֧������ϵ�����Ա */
        unsigned int  reserved_1: 6;  /* bit[26-31]:  */
    } reg;
} SOC_DSS_DPP_U_H_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_H_COEF_h_l_out_START   (0)
#define SOC_DSS_DPP_U_H_COEF_h_l_out_END     (9)
#define SOC_DSS_DPP_U_H_COEF_h_r_out_START   (16)
#define SOC_DSS_DPP_U_H_COEF_h_r_out_END     (25)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_U_SATA_COEF_UNION
 �ṹ˵��  : U_SATA_COEF �Ĵ����ṹ���塣��ַƫ����:0x1A00����ֵ:0x00000000�����:32
 �Ĵ���˵��: ACM SATA�������ұ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sata_l_out : 8;  /* bit[0-7]  : U_SATAL_COEFϵ�����ұ����ַ�������������֧������ϵ�����Ա */
        unsigned int  sata_r_out : 8;  /* bit[8-15] : U_SATAR_COEFϵ�����ұ����ַ�������������֧������ϵ�����Ա */
        unsigned int  reserved   : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_DPP_U_SATA_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_SATA_COEF_sata_l_out_START  (0)
#define SOC_DSS_DPP_U_SATA_COEF_sata_l_out_END    (7)
#define SOC_DSS_DPP_U_SATA_COEF_sata_r_out_START  (8)
#define SOC_DSS_DPP_U_SATA_COEF_sata_r_out_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_U_SATR_COEF_UNION
 �ṹ˵��  : U_SATR_COEF �Ĵ����ṹ���塣��ַƫ����:0x1C00����ֵ:0x00000000�����:32
 �Ĵ���˵��: ACM SATR�������ұ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  satr_l_out : 8;  /* bit[0-7]  : U_SATRL_COEFϵ�����ұ����ַ�������������֧������ϵ�����Ա */
        unsigned int  satr_r_out : 8;  /* bit[8-15] : U_SATRR_COEFϵ�����ұ����ַ�������������֧������ϵ�����Ա */
        unsigned int  reserved   : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_DPP_U_SATR_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_SATR_COEF_satr_l_out_START  (0)
#define SOC_DSS_DPP_U_SATR_COEF_satr_l_out_END    (7)
#define SOC_DSS_DPP_U_SATR_COEF_satr_r_out_START  (8)
#define SOC_DSS_DPP_U_SATR_COEF_satr_r_out_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_HIST_RPT0_UNION
 �ṹ˵��  : CE_HIST_RPT0 �Ĵ����ṹ���塣��ַƫ����:0x2000��0x23FF����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ϱ�ֱ��ͼmemory0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_hist_rpt0 : 24; /* bit[0-23] : ��ǰ��֡��ֱ��ͼͳ���ϱ� */
        unsigned int  reserved     : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_HIST_RPT0_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_RPT0_ce_hist_rpt0_START  (0)
#define SOC_DSS_DPP_CE_HIST_RPT0_ce_hist_rpt0_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_HIST_RPT1_UNION
 �ṹ˵��  : CE_HIST_RPT1 �Ĵ����ṹ���塣��ַƫ����:0x2400��0x27FF����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ϱ�ֱ��ͼmemory1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_hist_rpt1 : 24; /* bit[0-23] : ��ǰ��֡��ֱ��ͼͳ���ϱ� */
        unsigned int  reserved     : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_HIST_RPT1_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_RPT1_ce_hist_rpt1_START  (0)
#define SOC_DSS_DPP_CE_HIST_RPT1_ce_hist_rpt1_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_LUT0_UNION
 �ṹ˵��  : CE_LUT0 �Ĵ����ṹ���塣��ַƫ����:0x2800����ֵ:0x00000000�����:32
 �Ĵ���˵��: LUT �� memory0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_lut0 : 8;  /* bit[0-7] : ��ǰ��֡ʹ�õ�LUT���ұ����ַ�������������֧������ϵ�����Ա */
        unsigned int  reserved: 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_LUT0_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT0_ce_lut0_START  (0)
#define SOC_DSS_DPP_CE_LUT0_ce_lut0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_CE_LUT1_UNION
 �ṹ˵��  : CE_LUT1 �Ĵ����ṹ���塣��ַƫ����:0x2C00����ֵ:0x00000000�����:32
 �Ĵ���˵��: LUT �� memory1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_lut1 : 8;  /* bit[0-7] : ��ǰ��֡ʹ�õ�LUT���ұ����ַ�������������֧������ϵ�����Ա */
        unsigned int  reserved: 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_DPP_CE_LUT1_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT1_ce_lut1_START  (0)
#define SOC_DSS_DPP_CE_LUT1_ce_lut1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_U_GMP_COEF_UNION
 �ṹ˵��  : U_GMP_COEF �Ĵ����ṹ���塣��ַƫ����:0x3000��0x7CCF����ֵ:0x00000000�����:32
 �Ĵ���˵��: GMP���ұ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_gmp_coef : 32; /* bit[0-31]: GMP���ұ� */
    } reg;
} SOC_DSS_DPP_U_GMP_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_GMP_COEF_u_gmp_coef_START  (0)
#define SOC_DSS_DPP_U_GMP_COEF_u_gmp_coef_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_U_IGM_R_COEF_UNION
 �ṹ˵��  : U_IGM_R_COEF �Ĵ����ṹ���塣��ַƫ����:0xB000����ֵ:0x00000000�����:32
 �Ĵ���˵��: IGM R�������ұ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_igm_r_coef : 12; /* bit[0-11] : IGM R�������ұ����ַ�������������֧������ϵ�����Ա */
        unsigned int  reserved     : 20; /* bit[12-31]:  */
    } reg;
} SOC_DSS_DPP_U_IGM_R_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_IGM_R_COEF_u_igm_r_coef_START  (0)
#define SOC_DSS_DPP_U_IGM_R_COEF_u_igm_r_coef_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_U_IGM_G_COEF_UNION
 �ṹ˵��  : U_IGM_G_COEF �Ĵ����ṹ���塣��ַƫ����:0xB400����ֵ:0x00000000�����:32
 �Ĵ���˵��: IGM G�������ұ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_igm_g_coef : 12; /* bit[0-11] : IGM G�������ұ����ַ�������������֧������ϵ�����Ա */
        unsigned int  reserved     : 20; /* bit[12-31]:  */
    } reg;
} SOC_DSS_DPP_U_IGM_G_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_IGM_G_COEF_u_igm_g_coef_START  (0)
#define SOC_DSS_DPP_U_IGM_G_COEF_u_igm_g_coef_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DPP_U_IGM_B_COEF_UNION
 �ṹ˵��  : U_IGM_B_COEF �Ĵ����ṹ���塣��ַƫ����:0xB800����ֵ:0x00000000�����:32
 �Ĵ���˵��: IGM B�������ұ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_igm_b_coef : 12; /* bit[0-11] : IGM B�������ұ����ַ�������������֧������ϵ�����Ա */
        unsigned int  reserved     : 20; /* bit[12-31]:  */
    } reg;
} SOC_DSS_DPP_U_IGM_B_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_IGM_B_COEF_u_igm_b_coef_START  (0)
#define SOC_DSS_DPP_U_IGM_B_COEF_u_igm_b_coef_END    (11)






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

#endif /* end of soc_dss_dpp_interface.h */
