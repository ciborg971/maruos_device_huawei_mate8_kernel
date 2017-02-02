

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_GIC_NS_INTERFACE_H__
#define __SOC_GIC_NS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) GIC400_NS
 ****************************************************************************/
/* �Ĵ���˵����Distributor��ʹ�ܿ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_CTLR_NS_UNION */
#define SOC_GIC_NS_GICD_CTLR_NS_ADDR(base)            ((base) + (0x1000))

/* �Ĵ���˵�����жϿ��������ͼĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_TYPER_UNION */
#define SOC_GIC_NS_GICD_TYPER_ADDR(base)              ((base) + (0x1004))

/* �Ĵ���˵�����ַ�������ʶ��Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_IIDR_UNION */
#define SOC_GIC_NS_GICD_IIDR_ADDR(base)               ((base) + (0x1008))

/* �Ĵ���˵�����ж�ʹ�ܼĴ���0��SGI/PPI��
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ISENABLER0_UNION */
#define SOC_GIC_NS_GICD_ISENABLER0_ADDR(base)         ((base) + (0x1100))

/* �Ĵ���˵�����ж�ʹ�ܼĴ�����SPI��
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ISENABLERN_UNION */
#define SOC_GIC_NS_GICD_ISENABLERN_ADDR(base, N)      ((base) + (0x1104+(4*(N))))

/* �Ĵ���˵�����ж�����Ĵ���0��SGI/PPI��
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ICENABLER0_UNION */
#define SOC_GIC_NS_GICD_ICENABLER0_ADDR(base)         ((base) + (0x1180))

/* �Ĵ���˵�����ж�����Ĵ�����SPI��
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ICENABLERn_UNION */
#define SOC_GIC_NS_GICD_ICENABLERn_ADDR(base, N)      ((base) + (0x1184+(4*(N))))

/* �Ĵ���˵�����ж�Pending���üĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ISPENDRN_UNION */
#define SOC_GIC_NS_GICD_ISPENDRN_ADDR(base, N)        ((base) + (0x1200+(4*(N))))

/* �Ĵ���˵�����ж�Pending����Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ICPENDRn_UNION */
#define SOC_GIC_NS_GICD_ICPENDRn_ADDR(base, N)        ((base) + (0x1280+(4*(N))))

/* �Ĵ���˵�����ж�Active���üĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ISACTIVERn_UNION */
#define SOC_GIC_NS_GICD_ISACTIVERn_ADDR(base, N)      ((base) + (0x1300+(4*(N))))

/* �Ĵ���˵�����ж�Active����Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ICACTIVERn_UNION */
#define SOC_GIC_NS_GICD_ICACTIVERn_ADDR(base, N)      ((base) + (0x1380+(4*(N))))

/* �Ĵ���˵�����ж����ȼ����üĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_IPRIORITYRn_UNION */
#define SOC_GIC_NS_GICD_IPRIORITYRn_ADDR(base, N)     ((base) + (0x1400+(4*(N))))

/* �Ĵ���˵�����ж�Ŀ�괦�����Ĵ�����SGI and PPI��
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ITARGETSR0_7_UNION */
#define SOC_GIC_NS_GICD_ITARGETSR0_7_ADDR(base, N)    ((base) + (0x1800+(4*(N))))

/* �Ĵ���˵�����ж�Ŀ�괦�����Ĵ�����SPI��
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ITARGETSRn_UNION */
#define SOC_GIC_NS_GICD_ITARGETSRn_ADDR(base, N)      ((base) + (0x1820+(4*(N))))

/* �Ĵ���˵�����ж����üĴ�����SGI��
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ICFGR0_UNION */
#define SOC_GIC_NS_GICD_ICFGR0_ADDR(base)             ((base) + (0x1C00))

/* �Ĵ���˵�����ж����üĴ�����PPI��
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ICFGR1_UNION */
#define SOC_GIC_NS_GICD_ICFGR1_ADDR(base)             ((base) + (0x1C04))

/* �Ĵ���˵�����ж����üĴ�����SPI��
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_ICFGRn_UNION */
#define SOC_GIC_NS_GICD_ICFGRn_ADDR(base, N)          ((base) + (0x1C08+(4*(N))))

/* �Ĵ���˵����PPI�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_PPISR_UNION */
#define SOC_GIC_NS_GICD_PPISR_ADDR(base)              ((base) + (0x1D00))

/* �Ĵ���˵����SPI�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_SPISRn_UNION */
#define SOC_GIC_NS_GICD_SPISRn_ADDR(base, N)          ((base) + (0x1D04+(4*(N))))

/* �Ĵ���˵����SGI�жϼĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_SGIR_UNION */
#define SOC_GIC_NS_GICD_SGIR_ADDR(base)               ((base) + (0x1F00))

/* �Ĵ���˵����SGI Clear-Pending Registers
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_CPENDSGIRn_UNION */
#define SOC_GIC_NS_GICD_CPENDSGIRn_ADDR(base, N)      ((base) + (0x1F10+(4*(N))))

/* �Ĵ���˵����SGI Set-Pending Registers
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_SPENDSGIRn_UNION */
#define SOC_GIC_NS_GICD_SPENDSGIRn_ADDR(base, N)      ((base) + (0x1F20+(4*(N))))

/* �Ĵ���˵��������ID4�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_PIDR4_UNION */
#define SOC_GIC_NS_GICD_PIDR4_ADDR(base)              ((base) + (0x1FD0))

/* �Ĵ���˵��������ID5�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_PIDR5_UNION */
#define SOC_GIC_NS_GICD_PIDR5_ADDR(base)              ((base) + (0x1FD4))

/* �Ĵ���˵��������ID6�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_PIDR6_UNION */
#define SOC_GIC_NS_GICD_PIDR6_ADDR(base)              ((base) + (0x1FD8))

/* �Ĵ���˵��������ID7�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_PIDR7_UNION */
#define SOC_GIC_NS_GICD_PIDR7_ADDR(base)              ((base) + (0x1FDC))

/* �Ĵ���˵��������ID0�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_PIDR0_UNION */
#define SOC_GIC_NS_GICD_PIDR0_ADDR(base)              ((base) + (0x1FE0))

/* �Ĵ���˵��������ID1�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_PIDR1_UNION */
#define SOC_GIC_NS_GICD_PIDR1_ADDR(base)              ((base) + (0x1FE4))

/* �Ĵ���˵��������ID2�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_PIDR2_UNION */
#define SOC_GIC_NS_GICD_PIDR2_ADDR(base)              ((base) + (0x1FE8))

/* �Ĵ���˵��������ID3�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_PIDR3_UNION */
#define SOC_GIC_NS_GICD_PIDR3_ADDR(base)              ((base) + (0x1FEC))

/* �Ĵ���˵����ģ��ID0�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_CIDR0_UNION */
#define SOC_GIC_NS_GICD_CIDR0_ADDR(base)              ((base) + (0x1FF0))

/* �Ĵ���˵����ģ��ID1�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_CIDR1_UNION */
#define SOC_GIC_NS_GICD_CIDR1_ADDR(base)              ((base) + (0x1FF4))

/* �Ĵ���˵����ģ��ID2�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_CIDR2_UNION */
#define SOC_GIC_NS_GICD_CIDR2_ADDR(base)              ((base) + (0x1FF8))

/* �Ĵ���˵����ģ��ID3�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICD_CIDR3_UNION */
#define SOC_GIC_NS_GICD_CIDR3_ADDR(base)              ((base) + (0x1FFC))

/* �Ĵ���˵����CPU Interfaceʹ���Լ�������ƼĴ��������ر�ע�⣺GICC_CTLR��banked���˼Ĵ�������secure access�µı��ݡ�����non_secure �ı��ݵ�λ���䲻һ������
   λ����UNION�ṹ:  SOC_GIC_NS_GICC_CTLR_NS_UNION */
#define SOC_GIC_NS_GICC_CTLR_NS_ADDR(base)            ((base) + (0x2000))

/* �Ĵ���˵����CPU�ӿ����ȼ����μĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICC_PMR_UNION */
#define SOC_GIC_NS_GICC_PMR_ADDR(base)                ((base) + (0x2004))

/* �Ĵ���˵����CPU�ӿ�BPR�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICC_BPR_NS_UNION */
#define SOC_GIC_NS_GICC_BPR_NS_ADDR(base)             ((base) + (0x2008))

/* �Ĵ���˵����CPU�ӿ��ж�ȷ�ϼĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICC_IAR_UNION */
#define SOC_GIC_NS_GICC_IAR_ADDR(base)                ((base) + (0x200C))

/* �Ĵ���˵����CPU�ӿ��жϽ����Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICC_EOIR_UNION */
#define SOC_GIC_NS_GICC_EOIR_ADDR(base)               ((base) + (0x2010))

/* �Ĵ���˵����CPU�ӿ�Running���ȼ��Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICC_RPR_UNION */
#define SOC_GIC_NS_GICC_RPR_ADDR(base)                ((base) + (0x2014))

/* �Ĵ���˵����CPU�ӿ�������ȼ�pending�жϼĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICC_HPPIR_UNION */
#define SOC_GIC_NS_GICC_HPPIR_ADDR(base)              ((base) + (0x2018))

/* �Ĵ���˵����CPU�ӿ�ʶ��Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICC_IIDR_UNION */
#define SOC_GIC_NS_GICC_IIDR_ADDR(base)               ((base) + (0x20FC))

/* �Ĵ���˵����CPU�ӿ��ж�Deactivate�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICC_DIR_UNION */
#define SOC_GIC_NS_GICC_DIR_ADDR(base)                ((base) + (0x3000))

/* �Ĵ���˵����Hypervisor���ƼĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICH_HCR_UNION */
#define SOC_GIC_NS_GICH_HCR_ADDR(base)                ((base) + (0x4000))

/* �Ĵ���˵����VGIC���ͼĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICH_VTR_UNION */
#define SOC_GIC_NS_GICH_VTR_ADDR(base)                ((base) + (0x4004))

/* �Ĵ���˵����Virtual machine���ƼĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICH_VMCR_UNION */
#define SOC_GIC_NS_GICH_VMCR_ADDR(base)               ((base) + (0x4008))

/* �Ĵ���˵����Maintenance�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICH_MISR_UNION */
#define SOC_GIC_NS_GICH_MISR_ADDR(base)               ((base) + (0x4010))

/* �Ĵ���˵����EOI״̬�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICH_EISR0_UNION */
#define SOC_GIC_NS_GICH_EISR0_ADDR(base)              ((base) + (0x4020))

/* �Ĵ���˵������list register״̬�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICH_ELSR0_UNION */
#define SOC_GIC_NS_GICH_ELSR0_ADDR(base)              ((base) + (0x4030))

/* �Ĵ���˵������Ծ���ȼ��Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICH_APR0_UNION */
#define SOC_GIC_NS_GICH_APR0_ADDR(base)               ((base) + (0x40F0))

/* �Ĵ���˵����list register 0
   λ����UNION�ṹ:  SOC_GIC_NS_GICH_LR0_UNION */
#define SOC_GIC_NS_GICH_LR0_ADDR(base)                ((base) + (0x4100))

/* �Ĵ���˵����list register 1
   λ����UNION�ṹ:  SOC_GIC_NS_GICH_LR1_UNION */
#define SOC_GIC_NS_GICH_LR1_ADDR(base)                ((base) + (0x4104))

/* �Ĵ���˵����list register 2
   λ����UNION�ṹ:  SOC_GIC_NS_GICH_LR2_UNION */
#define SOC_GIC_NS_GICH_LR2_ADDR(base)                ((base) + (0x4108))

/* �Ĵ���˵����list register 3
   λ����UNION�ṹ:  SOC_GIC_NS_GICH_LR3_UNION */
#define SOC_GIC_NS_GICH_LR3_ADDR(base)                ((base) + (0x410C))

/* �Ĵ���˵����Virtual machine���ƼĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_CTLR_UNION */
#define SOC_GIC_NS_GICV_CTLR_ADDR(base)               ((base) + (0x6000))

/* �Ĵ���˵����Virtual machine���ȼ�mask�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_PMR_UNION */
#define SOC_GIC_NS_GICV_PMR_ADDR(base)                ((base) + (0x6004))

/* �Ĵ���˵����Virtual machine Binary point�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_BPR_UNION */
#define SOC_GIC_NS_GICV_BPR_ADDR(base)                ((base) + (0x6008))

/* �Ĵ���˵����Virtual machine�ж���Ӧ�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_IAR_UNION */
#define SOC_GIC_NS_GICV_IAR_ADDR(base)                ((base) + (0x600C))

/* �Ĵ���˵����Virtual machine EOI�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_EOIR_UNION */
#define SOC_GIC_NS_GICV_EOIR_ADDR(base)               ((base) + (0x6010))

/* �Ĵ���˵����Virtual machine Running Priority�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_RPR_UNION */
#define SOC_GIC_NS_GICV_RPR_ADDR(base)                ((base) + (0x6014))

/* �Ĵ���˵����Virtual machine ������ȼ�pending�жϼĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_HPPIR_UNION */
#define SOC_GIC_NS_GICV_HPPIR_ADDR(base)              ((base) + (0x6018))

/* �Ĵ���˵����Virtual machine aliased Binary point�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_ABPR_UNION */
#define SOC_GIC_NS_GICV_ABPR_ADDR(base)               ((base) + (0x601C))

/* �Ĵ���˵����Virtual machine aliased�ж���Ӧ�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_AIAR_UNION */
#define SOC_GIC_NS_GICV_AIAR_ADDR(base)               ((base) + (0x6020))

/* �Ĵ���˵����Virtual machine aliased EOI�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_AEOIR_UNION */
#define SOC_GIC_NS_GICV_AEOIR_ADDR(base)              ((base) + (0x6024))

/* �Ĵ���˵����Virtual machine aliased ������ȼ�pending�жϼĴ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_AHPPIR_UNION */
#define SOC_GIC_NS_GICV_AHPPIR_ADDR(base)             ((base) + (0x6028))

/* �Ĵ���˵����Virtual machine��Ծ���ȼ��Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_APR0_UNION */
#define SOC_GIC_NS_GICV_APR0_ADDR(base)               ((base) + (0x60D0))

/* �Ĵ���˵����Virtual machine CPU�ӿ�ʶ��Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_IIDR_UNION */
#define SOC_GIC_NS_GICV_IIDR_ADDR(base)               ((base) + (0x60FC))

/* �Ĵ���˵����Virtual machine CPU�ӿ��ж�Deactivate�Ĵ���
   λ����UNION�ṹ:  SOC_GIC_NS_GICV_DIR_UNION */
#define SOC_GIC_NS_GICV_DIR_ADDR(base)                ((base) + (0x7000))





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
                     (1/1) GIC400_NS
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_CTLR_NS_UNION
 �ṹ˵��  : GICD_CTLR_NS �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Distributor��ʹ�ܿ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EnableGrp0 : 1;  /* bit[0]   : Distributor��Group0�жϵ�ʹ�ܿ��ơ� 0�� Group0�жϲ�ʹ�ܣ� 
                                                     1�� Group0�ж�ʹ�ܡ� */
        unsigned int  EnableGrp1 : 1;  /* bit[1]   : Distributor��Group1�жϵ�ʹ�ܿ��ơ� 0�� Group1�жϲ�ʹ�ܣ� 
                                                     1�� Group1�ж�ʹ�ܡ� */
        unsigned int  reserved   : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_GIC_NS_GICD_CTLR_NS_UNION;
#endif
#define SOC_GIC_NS_GICD_CTLR_NS_EnableGrp0_START  (0)
#define SOC_GIC_NS_GICD_CTLR_NS_EnableGrp0_END    (0)
#define SOC_GIC_NS_GICD_CTLR_NS_EnableGrp1_START  (1)
#define SOC_GIC_NS_GICD_CTLR_NS_EnableGrp1_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_TYPER_UNION
 �ṹ˵��  : GICD_TYPER �Ĵ����ṹ���塣��ַƫ����:0x1004����ֵ:0x0000FCE9�����:32
 �Ĵ���˵��: �жϿ��������ͼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ITLinesNumber : 5;  /* bit[0-4]  : ָʾGIC֧�ֵ��жϸ���
                                                         00000: 32���жϣ���֧���ⲿ�ж�
                                                         00001: 64���жϣ�����32���ⲿ�ж�
                                                         00010: 96���жϣ�����64���ⲿ�ж�
                                                         .
                                                         .
                                                         01111: 512���жϣ�����480���ⲿ�ж� */
        unsigned int  CPUNumber     : 3;  /* bit[5-7]  : ָʾCPU�ӿڵĸ���
                                                         000: 1
                                                         001: 2
                                                         010: 3
                                                         011: 4
                                                         ����ֵΪ������չʹ�� */
        unsigned int  reserved_0    : 2;  /* bit[8-9]  :  */
        unsigned int  SecurityExtn  : 1;  /* bit[10]   : ָʾGIC�Ƿ�֧�ְ�ȫ��չ
                                                         0: ��֧��
                                                         1: ֧�� */
        unsigned int  LSPI          : 5;  /* bit[11-15]: ����LSPI(Lockable Shared Peripheral Interrupt)�жϸ�����
                                                         31 LSPI��ʾ�ж�ID 32-62
                                                         CFGSDISABLE�ź�Ϊ�ߣ������ж�LSPI��ؼĴ�������������ֹ */
        unsigned int  reserved_1    : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_GIC_NS_GICD_TYPER_UNION;
#endif
#define SOC_GIC_NS_GICD_TYPER_ITLinesNumber_START  (0)
#define SOC_GIC_NS_GICD_TYPER_ITLinesNumber_END    (4)
#define SOC_GIC_NS_GICD_TYPER_CPUNumber_START      (5)
#define SOC_GIC_NS_GICD_TYPER_CPUNumber_END        (7)
#define SOC_GIC_NS_GICD_TYPER_SecurityExtn_START   (10)
#define SOC_GIC_NS_GICD_TYPER_SecurityExtn_END     (10)
#define SOC_GIC_NS_GICD_TYPER_LSPI_START           (11)
#define SOC_GIC_NS_GICD_TYPER_LSPI_END             (15)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_IIDR_UNION
 �ṹ˵��  : GICD_IIDR �Ĵ����ṹ���塣��ַƫ����:0x1008����ֵ:0x20000000�����:32
 �Ĵ���˵��: �ַ�������ʶ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Implementer : 12; /* bit[0-11] : ������
                                                       0x43B: ARM */
        unsigned int  Revision    : 4;  /* bit[12-15]: GIC�ĸ��汾�� */
        unsigned int  Variant     : 4;  /* bit[16-19]: GIC�����汾�� */
        unsigned int  reserved    : 4;  /* bit[20-23]: ���� */
        unsigned int  ProductID   : 8;  /* bit[24-31]: ������
                                                       0x010: Cortex-A53 MPCore */
    } reg;
} SOC_GIC_NS_GICD_IIDR_UNION;
#endif
#define SOC_GIC_NS_GICD_IIDR_Implementer_START  (0)
#define SOC_GIC_NS_GICD_IIDR_Implementer_END    (11)
#define SOC_GIC_NS_GICD_IIDR_Revision_START     (12)
#define SOC_GIC_NS_GICD_IIDR_Revision_END       (15)
#define SOC_GIC_NS_GICD_IIDR_Variant_START      (16)
#define SOC_GIC_NS_GICD_IIDR_Variant_END        (19)
#define SOC_GIC_NS_GICD_IIDR_ProductID_START    (24)
#define SOC_GIC_NS_GICD_IIDR_ProductID_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ISENABLER0_UNION
 �ṹ˵��  : GICD_ISENABLER0 �Ĵ����ṹ���塣��ַƫ����:0x1100����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: �ж�ʹ�ܼĴ���0��SGI/PPI��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  setenable : 32; /* bit[0-31]: ÿbit���ƶ�Ӧ���жϷַ�ʹ�ܣ��˼Ĵ���ֻ���SGI��SPI�ж�
                                                    ��������
                                                    0: �ַ���ֹ
                                                    1: �ַ�ʹ��
                                                    д������
                                                    0: ��Ч
                                                    1: ʹ�ַܷ�
                                                    ע�⣺��SGI�ж���ص�bitд��Ч������SGI�жϣ���λ̬Ϊʹ�ܡ����������жϸ�λʱ���ڰ�ȫ��Group0�����Էǰ�ȫ������ֵΪ0x00000000,
                                                    ֻ��д1��д0�ԸüĴ������� */
    } reg;
} SOC_GIC_NS_GICD_ISENABLER0_UNION;
#endif
#define SOC_GIC_NS_GICD_ISENABLER0_setenable_START  (0)
#define SOC_GIC_NS_GICD_ISENABLER0_setenable_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ISENABLERN_UNION
 �ṹ˵��  : GICD_ISENABLERN �Ĵ����ṹ���塣��ַƫ����:0x1104+(4*(N))����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�ʹ�ܼĴ�����SPI��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  setenable : 32; /* bit[0-31]: ÿbit���ƶ�Ӧ���жϷַ�ʹ�ܣ��˼Ĵ���ֻ���PPI�ж�
                                                    ��������
                                                    0: �ַ���ֹ
                                                    1: �ַ�ʹ��
                                                    д������
                                                    0: ��Ч
                                                    1: ʹ�ַܷ�
                                                    ��ַƫ�Ƽ��㷽����
                                                    -> IDΪ�жϺ�
                                                    -> ÿ���Ĵ�����ƫ�Ƶ�ַΪ(0x1104+(4*n))��nΪID/32������
                                                    -> ÿ���ж϶�Ӧ�Ĵ����ڲ���bitΪID/32������
                                                    ע�⣺ֻ��д1��д0�ԸüĴ������� */
    } reg;
} SOC_GIC_NS_GICD_ISENABLERN_UNION;
#endif
#define SOC_GIC_NS_GICD_ISENABLERN_setenable_START  (0)
#define SOC_GIC_NS_GICD_ISENABLERN_setenable_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ICENABLER0_UNION
 �ṹ˵��  : GICD_ICENABLER0 �Ĵ����ṹ���塣��ַƫ����:0x1180����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: �ж�����Ĵ���0��SGI/PPI��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ClearEnable : 32; /* bit[0-31]: ÿbit���ƶ�Ӧ���жϷַ���ֹ���˼Ĵ���ֻ���SGI��SPI�ж�
                                                      ��������
                                                      0: �ַ���ֹ
                                                      1: �ַ�ʹ��
                                                      д������
                                                      0: ��Ч
                                                      1: ��ֹ�ַ�
                                                      ע�⣺��SGI�ж���ص�bitд��Ч������SGI�жϣ���λ̬Ϊʹ�ܡ����������жϸ�λʱ���ڰ�ȫ��Group0�����Էǰ�ȫ������ֵΪ0x00000000 */
    } reg;
} SOC_GIC_NS_GICD_ICENABLER0_UNION;
#endif
#define SOC_GIC_NS_GICD_ICENABLER0_ClearEnable_START  (0)
#define SOC_GIC_NS_GICD_ICENABLER0_ClearEnable_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ICENABLERn_UNION
 �ṹ˵��  : GICD_ICENABLERn �Ĵ����ṹ���塣��ַƫ����:0x1184+(4*(N))����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ�����SPI��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ClearEnable : 32; /* bit[0-31]: ÿbit���ƶ�Ӧ���жϷַ���ֹ���˼Ĵ���ֻ���PPI�ж�
                                                      ��������
                                                      0: �ַ���ֹ
                                                      1: �ַ�ʹ��
                                                      д������
                                                      0: ��Ч
                                                      1: ��ֹ�ַ�
                                                      ��ַƫ�Ƽ��㷽����
                                                      -> IDΪ�жϺ�
                                                      -> ÿ���Ĵ�����ƫ�Ƶ�ַΪ(0x1184+(4*n))��nΪID/32������
                                                      -> ÿ���ж϶�Ӧ�Ĵ����ڲ���bitΪID/32������ */
    } reg;
} SOC_GIC_NS_GICD_ICENABLERn_UNION;
#endif
#define SOC_GIC_NS_GICD_ICENABLERn_ClearEnable_START  (0)
#define SOC_GIC_NS_GICD_ICENABLERn_ClearEnable_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ISPENDRN_UNION
 �ṹ˵��  : GICD_ISPENDRN �Ĵ����ṹ���塣��ַƫ����:0x1200+(4*(N))����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�Pending���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SetPending : 32; /* bit[0-31]: ÿbit���ƶ�Ӧ�жϵ�pending״̬������active and pending״̬��
                                                     ��������
                                                     0: ��pending״̬
                                                     1: pending״̬
                                                     д������ֻ���SPI��PPI�жϣ�SGI�жϵ�Pending״̬��GICD_SPENDSGIRn�Ĵ������ƣ���
                                                     0: ��Ч
                                                     1: ���ڱ��ش����͵�ƽ�����ж�Ч����ͬ
                                                      ���ش���:
                                                      - ���֮ǰΪinactive�������pending״̬
                                                      - ���֮ǰΪactive�������active and pending״̬
                                                      - ���֮ǰΪpending������Ч
                                                      ��ƽ����:
                                                      - ���֮ǰΪinactive�������pending״̬
                                                      - ���֮ǰΪactive�������pending and active״̬
                                                      - ���֮ǰΪpending��д���Ĵ�����Ч���������źų���֮����Ȼ����pending״̬
                                                     ��ַƫ�Ƽ��㷽����
                                                     -> IDΪ�жϺ�
                                                     -> ÿ���Ĵ�����ƫ�Ƶ�ַΪ(0x1200+(4*n))��nΪID/32������
                                                     -> ÿ���ж϶�Ӧ�Ĵ����ڲ���bitΪID/32������ */
    } reg;
} SOC_GIC_NS_GICD_ISPENDRN_UNION;
#endif
#define SOC_GIC_NS_GICD_ISPENDRN_SetPending_START  (0)
#define SOC_GIC_NS_GICD_ISPENDRN_SetPending_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ICPENDRn_UNION
 �ṹ˵��  : GICD_ICPENDRn �Ĵ����ṹ���塣��ַƫ����:0x1280+(4*(N))����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�Pending����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ClearPending : 32; /* bit[0-31]: ÿbit�����Ӧ�жϵ�pending״̬������active and pending״̬��
                                                       ��������
                                                       0: ��pending״̬
                                                       1: pending״̬
                                                       д������ֻ���SPI��PPI�жϣ�SGI�жϵ�Pending״̬��GICD_SPENDSGIRn�Ĵ������ƣ���
                                                       0: ��Ч
                                                       1: ���ڱ��ش����͵�ƽ�����ж�Ч����ͬ
                                                        ���ش���:
                                                        - ���֮ǰΪpending�������inactive״̬
                                                        - ���֮ǰΪactive and pending�������active״̬
                                                        - ���֮ǰΪpending������Ч
                                                        ��ƽ����:
                                                        ����жϵ�pending״ֻ̬����дGICD_ISPENDRn�Ĵ���ʹ�ܣ���
                                                        - ���֮ǰΪpending�������active״̬
                                                        - ���֮ǰΪactive and pending�������active״̬
                                                        ����ԭ���pendingʹ�ܣ�ֻҪ�ж��ź���Ч����ʼ�ձ���pending״̬
                                                       ��ַƫ�Ƽ��㷽����
                                                       -> IDΪ�жϺ�
                                                       -> ÿ���Ĵ�����ƫ�Ƶ�ַΪ(0x1280+(4*n))��nΪID/32������
                                                       -> ÿ���ж϶�Ӧ�Ĵ����ڲ���bitΪID/32������
                                                       ��ע��Writes 0 Has no effect. */
    } reg;
} SOC_GIC_NS_GICD_ICPENDRn_UNION;
#endif
#define SOC_GIC_NS_GICD_ICPENDRn_ClearPending_START  (0)
#define SOC_GIC_NS_GICD_ICPENDRn_ClearPending_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ISACTIVERn_UNION
 �ṹ˵��  : GICD_ISACTIVERn �Ĵ����ṹ���塣��ַƫ����:0x1300+(4*(N))����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�Active���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SetActive : 32; /* bit[0-31]: ÿbitʹ�ܶ�Ӧ�жϵ�Active״̬
                                                    ��������
                                                     0: No Active
                                                     1: Active
                                                    д������
                                                     0: ��Ч
                                                     1: ����ж�״̬û��Active�������Active̬������Ѿ�Active������Ч
                                                    ��ַƫ�Ƽ��㷽����
                                                    -> IDΪ�жϺ�
                                                    -> ÿ���Ĵ�����ƫ�Ƶ�ַΪ(0x1300+(4*n))��nΪID/32������
                                                    -> ÿ���ж϶�Ӧ�Ĵ����ڲ���bitΪID/32������ */
    } reg;
} SOC_GIC_NS_GICD_ISACTIVERn_UNION;
#endif
#define SOC_GIC_NS_GICD_ISACTIVERn_SetActive_START  (0)
#define SOC_GIC_NS_GICD_ISACTIVERn_SetActive_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ICACTIVERn_UNION
 �ṹ˵��  : GICD_ICACTIVERn �Ĵ����ṹ���塣��ַƫ����:0x1380+(4*(N))����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�Active����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ClearActive : 32; /* bit[0-31]: ÿbit�����Ӧ�жϵ�Active״̬
                                                      ��������
                                                       0: No Active
                                                       1: Active
                                                      д������
                                                       0: ��Ч
                                                       1: ����ж�״̬�Ѿ�ΪActive�������Active״̬�����û��Active������Ч
                                                      ��ַƫ�Ƽ��㷽����
                                                      -> IDΪ�жϺ�
                                                      -> ÿ���Ĵ�����ƫ�Ƶ�ַΪ(0x1380+(4*n))��nΪID/32������
                                                      -> ÿ���ж϶�Ӧ�Ĵ����ڲ���bitΪID/32������ */
    } reg;
} SOC_GIC_NS_GICD_ICACTIVERn_UNION;
#endif
#define SOC_GIC_NS_GICD_ICACTIVERn_ClearActive_START  (0)
#define SOC_GIC_NS_GICD_ICACTIVERn_ClearActive_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_IPRIORITYRn_UNION
 �ṹ˵��  : GICD_IPRIORITYRn �Ĵ����ṹ���塣��ַƫ����:0x1400+(4*(N))����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж����ȼ����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0            : 4;  /* bit[0-3]  :  */
        unsigned int  Priority_byte_offset0 : 4;  /* bit[4-7]  : Each priority field holds a priority value. The lower the value, the greater the priority of the corresponding interrupt.
                                                                 The GIC-400 implements 32 priority levels in Secure state and 16 priority levels in 
                                                                 Non-secure state. */
        unsigned int  reserved_1            : 4;  /* bit[8-11] :  */
        unsigned int  Priority_byte_offset1 : 4;  /* bit[12-15]:  */
        unsigned int  reserved_2            : 4;  /* bit[16-19]:  */
        unsigned int  Priority_byte_offset2 : 4;  /* bit[20-23]:  */
        unsigned int  reserved_3            : 4;  /* bit[24-27]:  */
        unsigned int  Priority_byte_offset3 : 4;  /* bit[28-31]:  */
    } reg;
} SOC_GIC_NS_GICD_IPRIORITYRn_UNION;
#endif
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset0_START  (4)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset0_END    (7)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset1_START  (12)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset1_END    (15)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset2_START  (20)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset2_END    (23)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset3_START  (28)
#define SOC_GIC_NS_GICD_IPRIORITYRn_Priority_byte_offset3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ITARGETSR0_7_UNION
 �ṹ˵��  : GICD_ITARGETSR0_7 �Ĵ����ṹ���塣��ַƫ����:0x1800+(4*(N))����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�Ŀ�괦�����Ĵ�����SGI and PPI��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CPUtargets_byte_offset0 : 8;  /* bit[0-7]  : Processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor. For example, a value of 0x3 means that the Pending 
                                                                   interrupt is sent to processors 0 and 1.
                                                                   For GICD_ITARGETSR0 to GICD_ITARGETSR7, a read of any CPU targets field returns 
                                                                   the number of the processor performing the read */
        unsigned int  CPUtargets_byte_offset1 : 8;  /* bit[8-15] :  */
        unsigned int  CPUtargets_byte_offset2 : 8;  /* bit[16-23]:  */
        unsigned int  CPUtargets_byte_offset3 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_GIC_NS_GICD_ITARGETSR0_7_UNION;
#endif
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset0_START  (0)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset0_END    (7)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset1_START  (8)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset1_END    (15)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset2_START  (16)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset2_END    (23)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset3_START  (24)
#define SOC_GIC_NS_GICD_ITARGETSR0_7_CPUtargets_byte_offset3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ITARGETSRn_UNION
 �ṹ˵��  : GICD_ITARGETSRn �Ĵ����ṹ���塣��ַƫ����:0x1820+(4*(N))����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�Ŀ�괦�����Ĵ�����SPI��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CPUtargets_byte_offset0 : 8;  /* bit[0-7]  : Processors in the system number from 0, and each bit in a CPU targets field refers to the corresponding processor. For example, a value of 0x3 means that the Pending 
                                                                   interrupt is sent to processors 0 and 1.
                                                                   For GICD_ITARGETSR0 to GICD_ITARGETSR7, a read of any CPU targets field returns 
                                                                   the number of the processor performing the read */
        unsigned int  CPUtargets_byte_offset1 : 8;  /* bit[8-15] :  */
        unsigned int  CPUtargets_byte_offset2 : 8;  /* bit[16-23]:  */
        unsigned int  CPUtargets_byte_offset3 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_GIC_NS_GICD_ITARGETSRn_UNION;
#endif
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset0_START  (0)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset0_END    (7)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset1_START  (8)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset1_END    (15)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset2_START  (16)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset2_END    (23)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset3_START  (24)
#define SOC_GIC_NS_GICD_ITARGETSRn_CPUtargets_byte_offset3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ICFGR0_UNION
 �ṹ˵��  : GICD_ICFGR0 �Ĵ����ṹ���塣��ַƫ����:0x1C00����ֵ:0xAAAAAAAA�����:32
 �Ĵ���˵��: �ж����üĴ�����SGI��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SGIConfigF0  : 2;  /* bit[0-1]  :  */
        unsigned int  SGIConfigF1  : 2;  /* bit[2-3]  :  */
        unsigned int  SGIConfigF2  : 2;  /* bit[4-5]  :  */
        unsigned int  SGIConfigF3  : 2;  /* bit[6-7]  :  */
        unsigned int  SGIConfigF4  : 2;  /* bit[8-9]  :  */
        unsigned int  SGIConfigF5  : 2;  /* bit[10-11]:  */
        unsigned int  SGIConfigF6  : 2;  /* bit[12-13]:  */
        unsigned int  SGIConfigF7  : 2;  /* bit[14-15]:  */
        unsigned int  SGIConfigF8  : 2;  /* bit[16-17]:  */
        unsigned int  SGIConfigF9  : 2;  /* bit[18-19]:  */
        unsigned int  SGIConfigF10 : 2;  /* bit[20-21]:  */
        unsigned int  SGIConfigF11 : 2;  /* bit[22-23]:  */
        unsigned int  SGIConfigF12 : 2;  /* bit[24-25]:  */
        unsigned int  SGIConfigF13 : 2;  /* bit[26-27]:  */
        unsigned int  SGIConfigF14 : 2;  /* bit[28-29]:  */
        unsigned int  SGIConfigF15 : 2;  /* bit[30-31]: ÿ2bitΪһ��offset���ֱ��ӦSGI�ж�0~15������
                                                        bit[0]: reserved
                                                        bit[1]: ��ʾ�жϵĴ���״̬
                                                         0: ��ƽ����
                                                         1: ���ش��� */
    } reg;
} SOC_GIC_NS_GICD_ICFGR0_UNION;
#endif
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF0_START   (0)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF0_END     (1)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF1_START   (2)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF1_END     (3)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF2_START   (4)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF2_END     (5)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF3_START   (6)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF3_END     (7)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF4_START   (8)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF4_END     (9)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF5_START   (10)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF5_END     (11)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF6_START   (12)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF6_END     (13)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF7_START   (14)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF7_END     (15)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF8_START   (16)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF8_END     (17)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF9_START   (18)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF9_END     (19)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF10_START  (20)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF10_END    (21)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF11_START  (22)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF11_END    (23)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF12_START  (24)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF12_END    (25)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF13_START  (26)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF13_END    (27)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF14_START  (28)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF14_END    (29)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF15_START  (30)
#define SOC_GIC_NS_GICD_ICFGR0_SGIConfigF15_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ICFGR1_UNION
 �ṹ˵��  : GICD_ICFGR1 �Ĵ����ṹ���塣��ַƫ����:0x1C04����ֵ:0x55540000�����:32
 �Ĵ���˵��: �ж����üĴ�����PPI��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PPIConfig0  : 2;  /* bit[0-1]  :  */
        unsigned int  PPIConfig1  : 2;  /* bit[2-3]  :  */
        unsigned int  PPIConfig2  : 2;  /* bit[4-5]  :  */
        unsigned int  PPIConfig3  : 2;  /* bit[6-7]  :  */
        unsigned int  PPIConfig4  : 2;  /* bit[8-9]  :  */
        unsigned int  PPIConfig5  : 2;  /* bit[10-11]:  */
        unsigned int  PPIConfig6  : 2;  /* bit[12-13]:  */
        unsigned int  PPIConfig7  : 2;  /* bit[14-15]:  */
        unsigned int  PPIConfig8  : 2;  /* bit[16-17]:  */
        unsigned int  PPIConfig9  : 2;  /* bit[18-19]:  */
        unsigned int  PPIConfig10 : 2;  /* bit[20-21]:  */
        unsigned int  PPIConfig11 : 2;  /* bit[22-23]:  */
        unsigned int  PPIConfig12 : 2;  /* bit[24-25]:  */
        unsigned int  PPIConfig13 : 2;  /* bit[26-27]:  */
        unsigned int  PPIConfig14 : 2;  /* bit[28-29]:  */
        unsigned int  PPIConfig15 : 2;  /* bit[30-31]: ÿ2bitΪһ��offset���ֱ��ӦPPI�ж�0~15������
                                                       bit[0]: reserved
                                                       bit[1]: ��ʾ�жϵĴ���״̬
                                                        0: ��ƽ����
                                                        1: ���ش��� */
    } reg;
} SOC_GIC_NS_GICD_ICFGR1_UNION;
#endif
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig0_START   (0)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig0_END     (1)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig1_START   (2)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig1_END     (3)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig2_START   (4)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig2_END     (5)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig3_START   (6)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig3_END     (7)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig4_START   (8)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig4_END     (9)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig5_START   (10)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig5_END     (11)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig6_START   (12)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig6_END     (13)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig7_START   (14)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig7_END     (15)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig8_START   (16)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig8_END     (17)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig9_START   (18)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig9_END     (19)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig10_START  (20)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig10_END    (21)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig11_START  (22)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig11_END    (23)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig12_START  (24)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig12_END    (25)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig13_START  (26)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig13_END    (27)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig14_START  (28)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig14_END    (29)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig15_START  (30)
#define SOC_GIC_NS_GICD_ICFGR1_PPIConfig15_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_ICFGRn_UNION
 �ṹ˵��  : GICD_ICFGRn �Ĵ����ṹ���塣��ַƫ����:0x1C08+(4*(N))����ֵ:0x55540000�����:32
 �Ĵ���˵��: �ж����üĴ�����SPI��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PPIConfig0  : 2;  /* bit[0-1]  :  */
        unsigned int  PPIConfig1  : 2;  /* bit[2-3]  :  */
        unsigned int  PPIConfig2  : 2;  /* bit[4-5]  :  */
        unsigned int  PPIConfig3  : 2;  /* bit[6-7]  :  */
        unsigned int  PPIConfig4  : 2;  /* bit[8-9]  :  */
        unsigned int  PPIConfig5  : 2;  /* bit[10-11]:  */
        unsigned int  PPIConfig6  : 2;  /* bit[12-13]:  */
        unsigned int  PPIConfig7  : 2;  /* bit[14-15]:  */
        unsigned int  PPIConfig8  : 2;  /* bit[16-17]:  */
        unsigned int  PPIConfig9  : 2;  /* bit[18-19]:  */
        unsigned int  PPIConfig10 : 2;  /* bit[20-21]:  */
        unsigned int  PPIConfig11 : 2;  /* bit[22-23]:  */
        unsigned int  PPIConfig12 : 2;  /* bit[24-25]:  */
        unsigned int  PPIConfig13 : 2;  /* bit[26-27]:  */
        unsigned int  PPIConfig14 : 2;  /* bit[28-29]:  */
        unsigned int  PPIConfig15 : 2;  /* bit[30-31]: ÿ2bitΪһ��offset���ֱ��ӦPPI�ж�0~15������
                                                       bit[0]: reserved
                                                       bit[1]: ��ʾ�жϵĴ���״̬
                                                        0: ��ƽ����
                                                        1: ���ش��� */
    } reg;
} SOC_GIC_NS_GICD_ICFGRn_UNION;
#endif
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig0_START   (0)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig0_END     (1)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig1_START   (2)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig1_END     (3)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig2_START   (4)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig2_END     (5)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig3_START   (6)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig3_END     (7)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig4_START   (8)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig4_END     (9)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig5_START   (10)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig5_END     (11)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig6_START   (12)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig6_END     (13)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig7_START   (14)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig7_END     (15)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig8_START   (16)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig8_END     (17)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig9_START   (18)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig9_END     (19)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig10_START  (20)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig10_END    (21)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig11_START  (22)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig11_END    (23)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig12_START  (24)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig12_END    (25)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig13_START  (26)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig13_END    (27)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig14_START  (28)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig14_END    (29)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig15_START  (30)
#define SOC_GIC_NS_GICD_ICFGRn_PPIConfig15_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_PPISR_UNION
 �ṹ˵��  : GICD_PPISR �Ĵ����ṹ���塣��ַƫ����:0x1D00����ֵ:0x00000000�����:32
 �Ĵ���˵��: PPI�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 9;  /* bit[0-8]  :  */
        unsigned int  PPIStatus : 7;  /* bit[9-15] : ָʾPPI�жϵĵ�ǰ״̬
                                                     0: PPI0 - nFIQ
                                                     1: PPI1 - Secure physical timer event
                                                     2: PPI2 - Non-secure physical timer event
                                                     3: PPI3 - nIRQ
                                                     4: PPI4 - Virtual timer event
                                                     5: PPI5 - Hypervisor timer event
                                                     6: PPI6 - Virtual Maintenance Interrupt */
        unsigned int  reserved_1: 16; /* bit[16-31]: ���� */
    } reg;
} SOC_GIC_NS_GICD_PPISR_UNION;
#endif
#define SOC_GIC_NS_GICD_PPISR_PPIStatus_START  (9)
#define SOC_GIC_NS_GICD_PPISR_PPIStatus_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_SPISRn_UNION
 �ṹ˵��  : GICD_SPISRn �Ĵ����ṹ���塣��ַƫ����:0x1D04+(4*(N))����ֵ:0x00000000�����:32
 �Ĵ���˵��: SPI�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  IRQS : 32; /* bit[0-31]: ָʾSPI�жϵĵ�ǰ״̬��ÿbit��Ӧһ��SPI�жϡ�
                                               ��ַƫ�Ƽ��㷽����
                                               -> IDΪ�жϺ�
                                               -> ÿ���Ĵ�����ƫ�Ƶ�ַΪ(0x1D04+(4*n))��nΪID/32������
                                               -> ÿ���ж϶�Ӧ�Ĵ����ڲ���bitΪID/32������ */
    } reg;
} SOC_GIC_NS_GICD_SPISRn_UNION;
#endif
#define SOC_GIC_NS_GICD_SPISRn_IRQS_START  (0)
#define SOC_GIC_NS_GICD_SPISRn_IRQS_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_SGIR_UNION
 �ṹ˵��  : GICD_SGIR �Ĵ����ṹ���塣��ַƫ����:0x1F00����ֵ:0x00000000�����:32
 �Ĵ���˵��: SGI�жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SGIINTID         : 4;  /* bit[0-3]  : ������Ҫ�ַ����ض�CPU�ӿڵ�SGI�жϺţ���ΧΪ0~15 */
        unsigned int  reserved_0       : 11; /* bit[4-14] : ���� */
        unsigned int  NSATT            : 1;  /* bit[15]   : SGI�жϵİ�ȫ������ã�
                                                            0: ֻ�е����ĳ��CPU�ӿڣ�SGI�жϱ�����ΪGroup0����SGIINTIDָʾ���жϷַ�����Ӧ��CPU�ӿ�
                                                            1: ֻ�����ĳ��CPU�ӿڣ�SGI�жϱ�����ΪGroup0����SGIINTIDָʾ���жϷַ�����Ӧ��CPU�ӿ� */
        unsigned int  CPUTargetList    : 8;  /* bit[16-23]: ָʾ�ж�Ŀ�괦������Ӧ��CPU�ӿڣ�ÿbit��ʾһ��CPU�ӿڣ�����CPUTargetList[0]��ӦCPU�ӿ�0�����Ϊȫ�㣬���жϲ��ַ� */
        unsigned int  TargetListFilter : 2;  /* bit[24-25]: ָ��Distributor��β���SGI�ж�
                                                            00: ���жϷַ���CPUTargetList��ָ����CPU�ӿ�
                                                            01: ���жϷַ�����������������Ӧ��CPU�ӿ����������CPU�ӿ�
                                                            10: ���ж�ֻ�ַ���������������Ӧ��CPU�ӿ�
                                                            11: ���� */
        unsigned int  reserved_1       : 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_GIC_NS_GICD_SGIR_UNION;
#endif
#define SOC_GIC_NS_GICD_SGIR_SGIINTID_START          (0)
#define SOC_GIC_NS_GICD_SGIR_SGIINTID_END            (3)
#define SOC_GIC_NS_GICD_SGIR_NSATT_START             (15)
#define SOC_GIC_NS_GICD_SGIR_NSATT_END               (15)
#define SOC_GIC_NS_GICD_SGIR_CPUTargetList_START     (16)
#define SOC_GIC_NS_GICD_SGIR_CPUTargetList_END       (23)
#define SOC_GIC_NS_GICD_SGIR_TargetListFilter_START  (24)
#define SOC_GIC_NS_GICD_SGIR_TargetListFilter_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_CPENDSGIRn_UNION
 �ṹ˵��  : GICD_CPENDSGIRn �Ĵ����ṹ���塣��ַƫ����:0x1F10+(4*(N))����ֵ:0x00000000�����:32
 �Ĵ���˵��: SGI Clear-Pending Registers
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SGI_clear_pending_bits : 32; /* bit[0-31]: For each bit:
                                                                 Reads 0 SGI x from the corresponding processor is not pendinga.
                                                                  1 SGI x from the corresponding processor is pendinga.
                                                                 Writes 0 Has no effect.
                                                                  1 Removes the pending state of SGI x for the corresponding processor. */
    } reg;
} SOC_GIC_NS_GICD_CPENDSGIRn_UNION;
#endif
#define SOC_GIC_NS_GICD_CPENDSGIRn_SGI_clear_pending_bits_START  (0)
#define SOC_GIC_NS_GICD_CPENDSGIRn_SGI_clear_pending_bits_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_SPENDSGIRn_UNION
 �ṹ˵��  : GICD_SPENDSGIRn �Ĵ����ṹ���塣��ַƫ����:0x1F20+(4*(N))����ֵ:0x00000000�����:32
 �Ĵ���˵��: SGI Set-Pending Registers
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SGI_set_pending_bits : 32; /* bit[0-31]: For each bit:
                                                               Reads 0 SGI x for the corresponding processor is not pendinga.
                                                                1 SGI x for the corresponding processor is pendinga.
                                                               Writes 0 Has no effect.
                                                                1 Adds the pending state of SGI x for the corresponding processor
                                                               if it is not already pending. If SGI x is already pending for the corresponding processor then the write has no effect. */
    } reg;
} SOC_GIC_NS_GICD_SPENDSGIRn_UNION;
#endif
#define SOC_GIC_NS_GICD_SPENDSGIRn_SGI_set_pending_bits_START  (0)
#define SOC_GIC_NS_GICD_SPENDSGIRn_SGI_set_pending_bits_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_PIDR4_UNION
 �ṹ˵��  : GICD_PIDR4 �Ĵ����ṹ���塣��ַƫ����:0x1FD0����ֵ:0x00000004�����:32
 �Ĵ���˵��: ����ID4�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  continuationcode       : 4;  /* bit[0-3] :  */
        unsigned int  reserved               : 4;  /* bit[4-7] :  */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR4_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR4_continuationcode_START        (0)
#define SOC_GIC_NS_GICD_PIDR4_continuationcode_END          (3)
#define SOC_GIC_NS_GICD_PIDR4_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR4_implementation_defined_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_PIDR5_UNION
 �ṹ˵��  : GICD_PIDR5 �Ĵ����ṹ���塣��ַƫ����:0x1FD4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ID5�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 8;  /* bit[0-7] :  */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR5_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR5_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR5_implementation_defined_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_PIDR6_UNION
 �ṹ˵��  : GICD_PIDR6 �Ĵ����ṹ���塣��ַƫ����:0x1FD8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ID6�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 8;  /* bit[0-7] :  */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR6_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR6_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR6_implementation_defined_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_PIDR7_UNION
 �ṹ˵��  : GICD_PIDR7 �Ĵ����ṹ���塣��ַƫ����:0x1FDC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ID7�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 8;  /* bit[0-7] :  */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR7_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR7_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR7_implementation_defined_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_PIDR0_UNION
 �ṹ˵��  : GICD_PIDR0 �Ĵ����ṹ���塣��ַƫ����:0x1FE0����ֵ:0x00000090�����:32
 �Ĵ���˵��: ����ID0�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  devid_7_0              : 8;  /* bit[0-7] : Bits [7:0] of the ARM-defined DevID field */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR0_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR0_devid_7_0_START               (0)
#define SOC_GIC_NS_GICD_PIDR0_devid_7_0_END                 (7)
#define SOC_GIC_NS_GICD_PIDR0_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR0_implementation_defined_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_PIDR1_UNION
 �ṹ˵��  : GICD_PIDR1 �Ĵ����ṹ���塣��ַƫ����:0x1FE4����ֵ:0x000000B4�����:32
 �Ĵ���˵��: ����ID1�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  devid_11_8             : 4;  /* bit[0-3] : Bits [11:8] of the ARM-defined DevID field */
        unsigned int  archid_3_0             : 4;  /* bit[4-7] : Bits [3:0] of the ARM-defined ArchID field */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR1_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR1_devid_11_8_START              (0)
#define SOC_GIC_NS_GICD_PIDR1_devid_11_8_END                (3)
#define SOC_GIC_NS_GICD_PIDR1_archid_3_0_START              (4)
#define SOC_GIC_NS_GICD_PIDR1_archid_3_0_END                (7)
#define SOC_GIC_NS_GICD_PIDR1_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR1_implementation_defined_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_PIDR2_UNION
 �ṹ˵��  : GICD_PIDR2 �Ĵ����ṹ���塣��ַƫ����:0x1FE8����ֵ:0x0000002B�����:32
 �Ĵ���˵��: ����ID2�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  archid_6_4             : 3;  /* bit[0-2] : Bits [6:4] of the ARM-defined ArchID field */
        unsigned int  UsesJEPcode            : 1;  /* bit[3]   : ARM-defined UsesJEPcode field */
        unsigned int  ArchRev                : 4;  /* bit[4-7] : ArchRev field */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR2_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR2_archid_6_4_START              (0)
#define SOC_GIC_NS_GICD_PIDR2_archid_6_4_END                (2)
#define SOC_GIC_NS_GICD_PIDR2_UsesJEPcode_START             (3)
#define SOC_GIC_NS_GICD_PIDR2_UsesJEPcode_END               (3)
#define SOC_GIC_NS_GICD_PIDR2_ArchRev_START                 (4)
#define SOC_GIC_NS_GICD_PIDR2_ArchRev_END                   (7)
#define SOC_GIC_NS_GICD_PIDR2_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR2_implementation_defined_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_PIDR3_UNION
 �ṹ˵��  : GICD_PIDR3 �Ĵ����ṹ���塣��ַƫ����:0x1FEC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ID3�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 4;  /* bit[0-3] :  */
        unsigned int  Revision               : 4;  /* bit[4-7] : ARM-defined Revision field */
        unsigned int  implementation_defined : 24; /* bit[8-31]:  */
    } reg;
} SOC_GIC_NS_GICD_PIDR3_UNION;
#endif
#define SOC_GIC_NS_GICD_PIDR3_Revision_START                (4)
#define SOC_GIC_NS_GICD_PIDR3_Revision_END                  (7)
#define SOC_GIC_NS_GICD_PIDR3_implementation_defined_START  (8)
#define SOC_GIC_NS_GICD_PIDR3_implementation_defined_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_CIDR0_UNION
 �ṹ˵��  : GICD_CIDR0 �Ĵ����ṹ���塣��ַƫ����:0x1FF0����ֵ:0x0000000D�����:32
 �Ĵ���˵��: ģ��ID0�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Component : 32; /* bit[0-31]: ģ��ID0�Ĵ��� */
    } reg;
} SOC_GIC_NS_GICD_CIDR0_UNION;
#endif
#define SOC_GIC_NS_GICD_CIDR0_Component_START  (0)
#define SOC_GIC_NS_GICD_CIDR0_Component_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_CIDR1_UNION
 �ṹ˵��  : GICD_CIDR1 �Ĵ����ṹ���塣��ַƫ����:0x1FF4����ֵ:0x000000F0�����:32
 �Ĵ���˵��: ģ��ID1�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Component : 32; /* bit[0-31]: ģ��ID1�Ĵ��� */
    } reg;
} SOC_GIC_NS_GICD_CIDR1_UNION;
#endif
#define SOC_GIC_NS_GICD_CIDR1_Component_START  (0)
#define SOC_GIC_NS_GICD_CIDR1_Component_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_CIDR2_UNION
 �ṹ˵��  : GICD_CIDR2 �Ĵ����ṹ���塣��ַƫ����:0x1FF8����ֵ:0x00000005�����:32
 �Ĵ���˵��: ģ��ID2�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Component : 32; /* bit[0-31]: ģ��ID2�Ĵ��� */
    } reg;
} SOC_GIC_NS_GICD_CIDR2_UNION;
#endif
#define SOC_GIC_NS_GICD_CIDR2_Component_START  (0)
#define SOC_GIC_NS_GICD_CIDR2_Component_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICD_CIDR3_UNION
 �ṹ˵��  : GICD_CIDR3 �Ĵ����ṹ���塣��ַƫ����:0x1FFC����ֵ:0x000000B1�����:32
 �Ĵ���˵��: ģ��ID3�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Component : 32; /* bit[0-31]: ģ��ID3�Ĵ��� */
    } reg;
} SOC_GIC_NS_GICD_CIDR3_UNION;
#endif
#define SOC_GIC_NS_GICD_CIDR3_Component_START  (0)
#define SOC_GIC_NS_GICD_CIDR3_Component_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICC_CTLR_NS_UNION
 �ṹ˵��  : GICC_CTLR_NS �Ĵ����ṹ���塣��ַƫ����:0x2000����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU Interfaceʹ���Լ�������ƼĴ��������ر�ע�⣺GICC_CTLR��banked���˼Ĵ�������secure access�µı��ݡ�����non_secure �ı��ݵ�λ���䲻һ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enablegrp1    : 1;  /* bit[0]    : ��Group1���ж϶��ԣ� 
                                                         0����ʹ�ܸ��ж� 
                                                         1��ʹ�ܸ��ж� */
        unsigned int  reserved_0    : 4;  /* bit[1-4]  : reserved */
        unsigned int  fiqbypdisgrp1 : 1;  /* bit[5]    : ��FIQs��ʹ��ʱ�� 
                                                         0��Bypass FIQ���͵��������� 
                                                         1��Bypass FIQ�����͵��������� */
        unsigned int  irqbypdisgrp1 : 1;  /* bit[6]    : ��IRQs��ʹ��ʱ�� 
                                                         0��Bypass IRQ���͵��������� 
                                                         1��Bypass IRQ�����͵��������� */
        unsigned int  reserved_1    : 2;  /* bit[7-8]  : reserved */
        unsigned int  eoimodens     : 1;  /* bit[9]    : ������Ϊ�ǰ�ȫ����ʱ�� 
                                                         0������GICC_EOIR�������priority drop��deactive 
                                                         1������GICC_EOIRֻ�����priority drop����deactive��ͨ������GICC_DIR��ɡ� */
        unsigned int  reserved_2    : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_GIC_NS_GICC_CTLR_NS_UNION;
#endif
#define SOC_GIC_NS_GICC_CTLR_NS_enablegrp1_START     (0)
#define SOC_GIC_NS_GICC_CTLR_NS_enablegrp1_END       (0)
#define SOC_GIC_NS_GICC_CTLR_NS_fiqbypdisgrp1_START  (5)
#define SOC_GIC_NS_GICC_CTLR_NS_fiqbypdisgrp1_END    (5)
#define SOC_GIC_NS_GICC_CTLR_NS_irqbypdisgrp1_START  (6)
#define SOC_GIC_NS_GICC_CTLR_NS_irqbypdisgrp1_END    (6)
#define SOC_GIC_NS_GICC_CTLR_NS_eoimodens_START      (9)
#define SOC_GIC_NS_GICC_CTLR_NS_eoimodens_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICC_PMR_UNION
 �ṹ˵��  : GICC_PMR �Ĵ����ṹ���塣��ַƫ����:0x2004����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU�ӿ����ȼ����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  priority_low : 3;  /* bit[0-2] : For GIC-400 there is just 32 Priority Level, so the bit[2:0] should read as zero */
        unsigned int  priority     : 5;  /* bit[3-7] : CPU�ӿ����ȼ����εĵȼ������ж����ȼ����ڴ˼Ĵ�����ֵ�����ж��͸�Ŀ�괦���������֧��256�����ȼ���
                                                       0x00-0xFF(0-255): 256���ȼ�
                                                       0x00-0xFE(0-254): 128���ȼ���ż����
                                                       0x00-0xFC(0-252): 64���ȼ�������Ϊ4��
                                                       0x00-0xF8(0-248): 32���ȼ�������Ϊ8��
                                                       0x00-0xF0(0-240): 16���ȼ�������Ϊ16��
                                                       ������Ϊ0xFFʱ����ʾ�����ж϶������� */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_GIC_NS_GICC_PMR_UNION;
#endif
#define SOC_GIC_NS_GICC_PMR_priority_low_START  (0)
#define SOC_GIC_NS_GICC_PMR_priority_low_END    (2)
#define SOC_GIC_NS_GICC_PMR_priority_START      (3)
#define SOC_GIC_NS_GICC_PMR_priority_END        (7)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICC_BPR_NS_UNION
 �ṹ˵��  : GICC_BPR_NS �Ĵ����ṹ���塣��ַƫ����:0x2008����ֵ:0x00000003�����:32
 �Ĵ���˵��: CPU�ӿ�BPR�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  binarypoint : 3;  /* bit[0-2] : ����8-bit�ж����ȼ�����ζ�Ӧ���ڶ����ж���ռ������group���ȼ����Լ������ȼ���
                                                      ע���ǰ�ȫ���ʣ�Ĭ��ֵΪ0x3 */
        unsigned int  reserved    : 29; /* bit[3-31]:  */
    } reg;
} SOC_GIC_NS_GICC_BPR_NS_UNION;
#endif
#define SOC_GIC_NS_GICC_BPR_NS_binarypoint_START  (0)
#define SOC_GIC_NS_GICC_BPR_NS_binarypoint_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICC_IAR_UNION
 �ṹ˵��  : GICC_IAR �Ĵ����ṹ���塣��ַƫ����:0x200C����ֵ:0x000003FF�����:32
 �Ĵ���˵��: CPU�ӿ��ж�ȷ�ϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InterruptID : 10; /* bit[0-9]  : �жϺ� */
        unsigned int  cpuid       : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ����򷵻ط����ж������CPU�ӿڱ�ţ��������������жϣ����򷵻�0 */
        unsigned int  reserved    : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_GIC_NS_GICC_IAR_UNION;
#endif
#define SOC_GIC_NS_GICC_IAR_InterruptID_START  (0)
#define SOC_GIC_NS_GICC_IAR_InterruptID_END    (9)
#define SOC_GIC_NS_GICC_IAR_cpuid_START        (10)
#define SOC_GIC_NS_GICC_IAR_cpuid_END          (12)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICC_EOIR_UNION
 �ṹ˵��  : GICC_EOIR �Ĵ����ṹ���塣��ַƫ����:0x2010����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU�ӿ��жϽ����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EOIINTID : 10; /* bit[0-9]  : �жϺţ���GICC_IARһ�� */
        unsigned int  CPUID    : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ�������GICC_IARһ�£��������������жϣ�������Ч */
        unsigned int  reserved : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_GIC_NS_GICC_EOIR_UNION;
#endif
#define SOC_GIC_NS_GICC_EOIR_EOIINTID_START  (0)
#define SOC_GIC_NS_GICC_EOIR_EOIINTID_END    (9)
#define SOC_GIC_NS_GICC_EOIR_CPUID_START     (10)
#define SOC_GIC_NS_GICC_EOIR_CPUID_END       (12)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICC_RPR_UNION
 �ṹ˵��  : GICC_RPR �Ĵ����ṹ���塣��ַƫ����:0x2014����ֵ:0x000000FF�����:32
 �Ĵ���˵��: CPU�ӿ�Running���ȼ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Priority : 8;  /* bit[0-7] : ��ǰCPU�ӿڵ�running���ȼ� */
        unsigned int  reserved : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_GIC_NS_GICC_RPR_UNION;
#endif
#define SOC_GIC_NS_GICC_RPR_Priority_START  (0)
#define SOC_GIC_NS_GICC_RPR_Priority_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICC_HPPIR_UNION
 �ṹ˵��  : GICC_HPPIR �Ĵ����ṹ���塣��ַƫ����:0x2018����ֵ:0x000003FF�����:32
 �Ĵ���˵��: CPU�ӿ�������ȼ�pending�жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PENDINTID : 10; /* bit[0-9]  : �жϺ� */
        unsigned int  CPUID     : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ����򷵻����ɸ��жϵ�CPUID */
        unsigned int  reserved  : 19; /* bit[13-31]:  */
    } reg;
} SOC_GIC_NS_GICC_HPPIR_UNION;
#endif
#define SOC_GIC_NS_GICC_HPPIR_PENDINTID_START  (0)
#define SOC_GIC_NS_GICC_HPPIR_PENDINTID_END    (9)
#define SOC_GIC_NS_GICC_HPPIR_CPUID_START      (10)
#define SOC_GIC_NS_GICC_HPPIR_CPUID_END        (12)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICC_IIDR_UNION
 �ṹ˵��  : GICC_IIDR �Ĵ����ṹ���塣��ַƫ����:0x20FC����ֵ:0x0202043B�����:32
 �Ĵ���˵��: CPU�ӿ�ʶ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  implementer : 12; /* bit[0-11] : ������
                                                       0x43B: ARM */
        unsigned int  revision    : 4;  /* bit[12-15]: CPU�ӿڰ汾
                                                       0x0: Revision 0 */
        unsigned int  archversion : 4;  /* bit[16-19]: GIC��ϵ�ṹ�汾
                                                       0x2: Version 2.0 */
        unsigned int  productid   : 12; /* bit[20-31]: ������
                                                       0x010: Cortex-A53 MPCore */
    } reg;
} SOC_GIC_NS_GICC_IIDR_UNION;
#endif
#define SOC_GIC_NS_GICC_IIDR_implementer_START  (0)
#define SOC_GIC_NS_GICC_IIDR_implementer_END    (11)
#define SOC_GIC_NS_GICC_IIDR_revision_START     (12)
#define SOC_GIC_NS_GICC_IIDR_revision_END       (15)
#define SOC_GIC_NS_GICC_IIDR_archversion_START  (16)
#define SOC_GIC_NS_GICC_IIDR_archversion_END    (19)
#define SOC_GIC_NS_GICC_IIDR_productid_START    (20)
#define SOC_GIC_NS_GICC_IIDR_productid_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICC_DIR_UNION
 �ṹ˵��  : GICC_DIR �Ĵ����ṹ���塣��ַƫ����:0x3000����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU�ӿ��ж�Deactivate�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InterruptID : 10; /* bit[0-9]  : �жϺ� */
        unsigned int  CPUID       : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ������ṩ��������Ĵ�����CPUID */
        unsigned int  reserved    : 19; /* bit[13-31]:  */
    } reg;
} SOC_GIC_NS_GICC_DIR_UNION;
#endif
#define SOC_GIC_NS_GICC_DIR_InterruptID_START  (0)
#define SOC_GIC_NS_GICC_DIR_InterruptID_END    (9)
#define SOC_GIC_NS_GICC_DIR_CPUID_START        (10)
#define SOC_GIC_NS_GICC_DIR_CPUID_END          (12)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICH_HCR_UNION
 �ṹ˵��  : GICH_HCR �Ĵ����ṹ���塣��ַƫ����:0x4000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Hypervisor���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  En       : 1;  /* bit[0]    : virtual CPU interface��ȫ��ʹ��
                                                    0��virtual CPU interfaceȥʹ��
                                                    1��virtual CPU interfaceʹ�� */
        unsigned int  UIE      : 1;  /* bit[1]    : underflow�ж�ʹ�ܣ�
                                                    0��Maintenance�ж�ȥʹ��
                                                    1����list register�����ֻ��һ��entry�����Ϊ��Ч�ж�ʱ����Maintenance�ж� */
        unsigned int  LRENPIE  : 1;  /* bit[2]    : list register��entry�ж�ʹ�ܣ�
                                                    0��Maintenance�ж�ȥʹ��
                                                    1��EOICount��Ϊ0ʱ����Maintenance�ж� */
        unsigned int  NPIE     : 1;  /* bit[3]    : ��pending�ж�ʹ�ܣ�
                                                    0��Maintenance�ж�ȥʹ��
                                                    1��list register����pending�ж�ʱ����Maintenance�ж� */
        unsigned int  VGrp0EIE : 1;  /* bit[4]    : VMʹ��group0�ж�ʹ�ܣ�
                                                    0��Maintenance�ж�ȥʹ��
                                                    1��GICV_CTLR.EnableGrp0��Ϊ1ʱ����Maintenance�ж� */
        unsigned int  VGrp0DIE : 1;  /* bit[5]    : VMȥʹ��group0�ж�ʹ�ܣ�
                                                    0��Maintenance�ж�ȥʹ��
                                                    1��GICV_CTLR.EnableGrp0��Ϊ0ʱ����Maintenance�ж� */
        unsigned int  VGrp1EIE : 1;  /* bit[6]    : VMʹ��group1�ж�ʹ�ܣ�
                                                    0��Maintenance�ж�ȥʹ��
                                                    1��GICV_CTLR.EnableGrp1��Ϊ1ʱ����Maintenance�ж� */
        unsigned int  VGrp1DIE : 1;  /* bit[7]    : VMȥʹ��group1�ж�ʹ�ܣ�
                                                    0��Maintenance�ж�ȥʹ��
                                                    1��GICV_CTLR.EnableGrp1��Ϊ0ʱ����Maintenance�ж� */
        unsigned int  reserved : 19; /* bit[8-26] : ���� */
        unsigned int  EOICount : 5;  /* bit[27-31]: ��list register��û��entry��EOI���� */
    } reg;
} SOC_GIC_NS_GICH_HCR_UNION;
#endif
#define SOC_GIC_NS_GICH_HCR_En_START        (0)
#define SOC_GIC_NS_GICH_HCR_En_END          (0)
#define SOC_GIC_NS_GICH_HCR_UIE_START       (1)
#define SOC_GIC_NS_GICH_HCR_UIE_END         (1)
#define SOC_GIC_NS_GICH_HCR_LRENPIE_START   (2)
#define SOC_GIC_NS_GICH_HCR_LRENPIE_END     (2)
#define SOC_GIC_NS_GICH_HCR_NPIE_START      (3)
#define SOC_GIC_NS_GICH_HCR_NPIE_END        (3)
#define SOC_GIC_NS_GICH_HCR_VGrp0EIE_START  (4)
#define SOC_GIC_NS_GICH_HCR_VGrp0EIE_END    (4)
#define SOC_GIC_NS_GICH_HCR_VGrp0DIE_START  (5)
#define SOC_GIC_NS_GICH_HCR_VGrp0DIE_END    (5)
#define SOC_GIC_NS_GICH_HCR_VGrp1EIE_START  (6)
#define SOC_GIC_NS_GICH_HCR_VGrp1EIE_END    (6)
#define SOC_GIC_NS_GICH_HCR_VGrp1DIE_START  (7)
#define SOC_GIC_NS_GICH_HCR_VGrp1DIE_END    (7)
#define SOC_GIC_NS_GICH_HCR_EOICount_START  (27)
#define SOC_GIC_NS_GICH_HCR_EOICount_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICH_VTR_UNION
 �ṹ˵��  : GICH_VTR �Ĵ����ṹ���塣��ַƫ����:0x4004����ֵ:0x8C000003�����:32
 �Ĵ���˵��: VGIC���ͼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ListRegs : 6;  /* bit[0-5]  : ʵ���˵�list register�ĸ�����1 */
        unsigned int  reserved : 20; /* bit[6-25] : ���� */
        unsigned int  PREbits  : 3;  /* bit[26-28]: ʵ���˵���ռλ����1 */
        unsigned int  PRIbits  : 3;  /* bit[29-31]: ʵ���˵����ȼ�λ����1 */
    } reg;
} SOC_GIC_NS_GICH_VTR_UNION;
#endif
#define SOC_GIC_NS_GICH_VTR_ListRegs_START  (0)
#define SOC_GIC_NS_GICH_VTR_ListRegs_END    (5)
#define SOC_GIC_NS_GICH_VTR_PREbits_START   (26)
#define SOC_GIC_NS_GICH_VTR_PREbits_END     (28)
#define SOC_GIC_NS_GICH_VTR_PRIbits_START   (29)
#define SOC_GIC_NS_GICH_VTR_PRIbits_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICH_VMCR_UNION
 �ṹ˵��  : GICH_VMCR �Ĵ����ṹ���塣��ַƫ����:0x4008����ֵ:0x004C0000�����:32
 �Ĵ���˵��: Virtual machine���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  VMGrp0En  : 1;  /* bit[0]    : Alias of GICV_CTLR.EnableGrp0 */
        unsigned int  VMGrp1En  : 1;  /* bit[1]    : Alias of GICV_CTLR.EnableGrp1 */
        unsigned int  VMAckCtl  : 1;  /* bit[2]    : Alias of GICV_CTLR.AckCtl */
        unsigned int  VMFIQEn   : 1;  /* bit[3]    : Alias of GICV_CTLR.FIQEn */
        unsigned int  VMCBPR    : 1;  /* bit[4]    : Alias of GICV_CTLR.CBPR */
        unsigned int  reserved_0: 4;  /* bit[5-8]  : ���� */
        unsigned int  VEM       : 1;  /* bit[9]    : Alias of GICV_CTLR.EOImode */
        unsigned int  reserved_1: 8;  /* bit[10-17]: ���� */
        unsigned int  VMABP     : 3;  /* bit[18-20]: Alias of GICV_ABPR.Binary point */
        unsigned int  VMBP      : 3;  /* bit[21-23]: Alias of GICV_BPR.Binary point */
        unsigned int  reserved_2: 3;  /* bit[24-26]: ���� */
        unsigned int  VMPriMask : 5;  /* bit[27-31]: Alias of GICV_PMR.Priority */
    } reg;
} SOC_GIC_NS_GICH_VMCR_UNION;
#endif
#define SOC_GIC_NS_GICH_VMCR_VMGrp0En_START   (0)
#define SOC_GIC_NS_GICH_VMCR_VMGrp0En_END     (0)
#define SOC_GIC_NS_GICH_VMCR_VMGrp1En_START   (1)
#define SOC_GIC_NS_GICH_VMCR_VMGrp1En_END     (1)
#define SOC_GIC_NS_GICH_VMCR_VMAckCtl_START   (2)
#define SOC_GIC_NS_GICH_VMCR_VMAckCtl_END     (2)
#define SOC_GIC_NS_GICH_VMCR_VMFIQEn_START    (3)
#define SOC_GIC_NS_GICH_VMCR_VMFIQEn_END      (3)
#define SOC_GIC_NS_GICH_VMCR_VMCBPR_START     (4)
#define SOC_GIC_NS_GICH_VMCR_VMCBPR_END       (4)
#define SOC_GIC_NS_GICH_VMCR_VEM_START        (9)
#define SOC_GIC_NS_GICH_VMCR_VEM_END          (9)
#define SOC_GIC_NS_GICH_VMCR_VMABP_START      (18)
#define SOC_GIC_NS_GICH_VMCR_VMABP_END        (20)
#define SOC_GIC_NS_GICH_VMCR_VMBP_START       (21)
#define SOC_GIC_NS_GICH_VMCR_VMBP_END         (23)
#define SOC_GIC_NS_GICH_VMCR_VMPriMask_START  (27)
#define SOC_GIC_NS_GICH_VMCR_VMPriMask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICH_MISR_UNION
 �ṹ˵��  : GICH_MISR �Ĵ����ṹ���塣��ַƫ����:0x4010����ֵ:0x00000000�����:32
 �Ĵ���˵��: Maintenance�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EOI      : 1;  /* bit[0]   : EOI maintenance�ж� */
        unsigned int  U        : 1;  /* bit[1]   : Underflow maintenance�ж� */
        unsigned int  LRENP    : 1;  /* bit[2]   : list register��entry maintenance�ж� */
        unsigned int  NP       : 1;  /* bit[3]   : list register����pending maintenance�ж� */
        unsigned int  VGrp0E   : 1;  /* bit[4]   : ʹ��group0 maintenance�ж� */
        unsigned int  VGrp0D   : 1;  /* bit[5]   : ȥʹ��group0 maintenance�ж� */
        unsigned int  VGrp1E   : 1;  /* bit[6]   : ʹ��group1 maintenance�ж� */
        unsigned int  VGrp1D   : 1;  /* bit[7]   : ȥʹ��group1 maintenance�ж� */
        unsigned int  reserved : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_GIC_NS_GICH_MISR_UNION;
#endif
#define SOC_GIC_NS_GICH_MISR_EOI_START       (0)
#define SOC_GIC_NS_GICH_MISR_EOI_END         (0)
#define SOC_GIC_NS_GICH_MISR_U_START         (1)
#define SOC_GIC_NS_GICH_MISR_U_END           (1)
#define SOC_GIC_NS_GICH_MISR_LRENP_START     (2)
#define SOC_GIC_NS_GICH_MISR_LRENP_END       (2)
#define SOC_GIC_NS_GICH_MISR_NP_START        (3)
#define SOC_GIC_NS_GICH_MISR_NP_END          (3)
#define SOC_GIC_NS_GICH_MISR_VGrp0E_START    (4)
#define SOC_GIC_NS_GICH_MISR_VGrp0E_END      (4)
#define SOC_GIC_NS_GICH_MISR_VGrp0D_START    (5)
#define SOC_GIC_NS_GICH_MISR_VGrp0D_END      (5)
#define SOC_GIC_NS_GICH_MISR_VGrp1E_START    (6)
#define SOC_GIC_NS_GICH_MISR_VGrp1E_END      (6)
#define SOC_GIC_NS_GICH_MISR_VGrp1D_START    (7)
#define SOC_GIC_NS_GICH_MISR_VGrp1D_END      (7)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICH_EISR0_UNION
 �ṹ˵��  : GICH_EISR0 �Ĵ����ṹ���塣��ַƫ����:0x4020����ֵ:0x00000000�����:32
 �Ĵ���˵��: EOI״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  List_register_ECO_status : 32; /* bit[0-31]: 0����Ӧ��list register������EOI
                                                                   1����Ӧ��list register������EOI */
    } reg;
} SOC_GIC_NS_GICH_EISR0_UNION;
#endif
#define SOC_GIC_NS_GICH_EISR0_List_register_ECO_status_START  (0)
#define SOC_GIC_NS_GICH_EISR0_List_register_ECO_status_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICH_ELSR0_UNION
 �ṹ˵��  : GICH_ELSR0 �Ĵ����ṹ���塣��ַƫ����:0x4030����ֵ:0x0000000F�����:32
 �Ĵ���˵��: ��list register״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  List_register_status : 32; /* bit[0-31]: 0����Ӧ��list register������Ч�ж�
                                                               1����Ӧ��list register����������Ч�ж� */
    } reg;
} SOC_GIC_NS_GICH_ELSR0_UNION;
#endif
#define SOC_GIC_NS_GICH_ELSR0_List_register_status_START  (0)
#define SOC_GIC_NS_GICH_ELSR0_List_register_status_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICH_APR0_UNION
 �ṹ˵��  : GICH_APR0 �Ĵ����ṹ���塣��ַƫ����:0x40F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ծ���ȼ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Active_priority_bits : 32; /* bit[0-31]: ������Ӧλ����ռ�����Ƿ��Ծ��
                                                               0������Ծ
                                                               1����Ծ */
    } reg;
} SOC_GIC_NS_GICH_APR0_UNION;
#endif
#define SOC_GIC_NS_GICH_APR0_Active_priority_bits_START  (0)
#define SOC_GIC_NS_GICH_APR0_Active_priority_bits_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICH_LR0_UNION
 �ṹ˵��  : GICH_LR0 �Ĵ����ṹ���塣��ַƫ����:0x4100����ֵ:0x00000000�����:32
 �Ĵ���˵��: list register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  VirtualID  : 10; /* bit[0-9]  : ���ж�ͨ��GICV_IAR��Ӧʱ����ID���ظ�Guest OS */
        unsigned int  PhysicalID : 10; /* bit[10-19]: ��GICH_LR.HW=0ʱ��
                                                      [19] EOI ָʾ�ж��Ƿ�ΪEOI maintenance�ж�
                                                      [18:13] Reserved, SBZ
                                                      [12:10] CPUID
                                                      ��GICH_LR.HW=1ʱ��
                                                      ����Hypervisor�͸�distributor�������ж�ID */
        unsigned int  reserved   : 3;  /* bit[20-22]: ���� */
        unsigned int  Priority   : 5;  /* bit[23-27]: ���ȼ� */
        unsigned int  State      : 2;  /* bit[28-29]: �ж�״̬��
                                                      00��invalid
                                                      01��pending
                                                      10��active
                                                      11��pending&active */
        unsigned int  Grp1       : 1;  /* bit[30]   : �����ж��Ƿ�Ϊgruop1��
                                                      0���ж�Ϊgroup0
                                                      1���ж�Ϊgroup1 */
        unsigned int  HW         : 1;  /* bit[31]   : �����ж��Ƿ�ΪӲ�жϣ�
                                                      0���ж�Ϊ���ж�
                                                      1���ж�ΪӲ�ж� */
    } reg;
} SOC_GIC_NS_GICH_LR0_UNION;
#endif
#define SOC_GIC_NS_GICH_LR0_VirtualID_START   (0)
#define SOC_GIC_NS_GICH_LR0_VirtualID_END     (9)
#define SOC_GIC_NS_GICH_LR0_PhysicalID_START  (10)
#define SOC_GIC_NS_GICH_LR0_PhysicalID_END    (19)
#define SOC_GIC_NS_GICH_LR0_Priority_START    (23)
#define SOC_GIC_NS_GICH_LR0_Priority_END      (27)
#define SOC_GIC_NS_GICH_LR0_State_START       (28)
#define SOC_GIC_NS_GICH_LR0_State_END         (29)
#define SOC_GIC_NS_GICH_LR0_Grp1_START        (30)
#define SOC_GIC_NS_GICH_LR0_Grp1_END          (30)
#define SOC_GIC_NS_GICH_LR0_HW_START          (31)
#define SOC_GIC_NS_GICH_LR0_HW_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICH_LR1_UNION
 �ṹ˵��  : GICH_LR1 �Ĵ����ṹ���塣��ַƫ����:0x4104����ֵ:0x00000000�����:32
 �Ĵ���˵��: list register 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  VirtualID  : 10; /* bit[0-9]  : ���ж�ͨ��GICV_IAR��Ӧʱ����ID���ظ�Guest OS */
        unsigned int  PhysicalID : 10; /* bit[10-19]: ��GICH_LR.HW=0ʱ��
                                                      [19] EOI ָʾ�ж��Ƿ�ΪEOI maintenance�ж�
                                                      [18:13] Reserved, SBZ
                                                      [12:10] CPUID
                                                      ��GICH_LR.HW=1ʱ��
                                                      ����Hypervisor�͸�distributor�������ж�ID */
        unsigned int  reserved   : 3;  /* bit[20-22]: ���� */
        unsigned int  Priority   : 5;  /* bit[23-27]: ���ȼ� */
        unsigned int  State      : 2;  /* bit[28-29]: �ж�״̬��
                                                      00��invalid
                                                      01��pending
                                                      10��active
                                                      11��pending&active */
        unsigned int  Grp1       : 1;  /* bit[30]   : �����ж��Ƿ�Ϊgruop1��
                                                      0���ж�Ϊgroup0
                                                      1���ж�Ϊgroup1 */
        unsigned int  HW         : 1;  /* bit[31]   : �����ж��Ƿ�ΪӲ�жϣ�
                                                      0���ж�Ϊ���ж�
                                                      1���ж�ΪӲ�ж� */
    } reg;
} SOC_GIC_NS_GICH_LR1_UNION;
#endif
#define SOC_GIC_NS_GICH_LR1_VirtualID_START   (0)
#define SOC_GIC_NS_GICH_LR1_VirtualID_END     (9)
#define SOC_GIC_NS_GICH_LR1_PhysicalID_START  (10)
#define SOC_GIC_NS_GICH_LR1_PhysicalID_END    (19)
#define SOC_GIC_NS_GICH_LR1_Priority_START    (23)
#define SOC_GIC_NS_GICH_LR1_Priority_END      (27)
#define SOC_GIC_NS_GICH_LR1_State_START       (28)
#define SOC_GIC_NS_GICH_LR1_State_END         (29)
#define SOC_GIC_NS_GICH_LR1_Grp1_START        (30)
#define SOC_GIC_NS_GICH_LR1_Grp1_END          (30)
#define SOC_GIC_NS_GICH_LR1_HW_START          (31)
#define SOC_GIC_NS_GICH_LR1_HW_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICH_LR2_UNION
 �ṹ˵��  : GICH_LR2 �Ĵ����ṹ���塣��ַƫ����:0x4108����ֵ:0x00000000�����:32
 �Ĵ���˵��: list register 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  VirtualID  : 10; /* bit[0-9]  : ���ж�ͨ��GICV_IAR��Ӧʱ����ID���ظ�Guest OS */
        unsigned int  PhysicalID : 10; /* bit[10-19]: ��GICH_LR.HW=0ʱ��
                                                      [19] EOI ָʾ�ж��Ƿ�ΪEOI maintenance�ж�
                                                      [18:13] Reserved, SBZ
                                                      [12:10] CPUID
                                                      ��GICH_LR.HW=1ʱ��
                                                      ����Hypervisor�͸�distributor�������ж�ID */
        unsigned int  reserved   : 3;  /* bit[20-22]: ���� */
        unsigned int  Priority   : 5;  /* bit[23-27]: ���ȼ� */
        unsigned int  State      : 2;  /* bit[28-29]: �ж�״̬��
                                                      00��invalid
                                                      01��pending
                                                      10��active
                                                      11��pending&active */
        unsigned int  Grp1       : 1;  /* bit[30]   : �����ж��Ƿ�Ϊgruop1��
                                                      0���ж�Ϊgroup0
                                                      1���ж�Ϊgroup1 */
        unsigned int  HW         : 1;  /* bit[31]   : �����ж��Ƿ�ΪӲ�жϣ�
                                                      0���ж�Ϊ���ж�
                                                      1���ж�ΪӲ�ж� */
    } reg;
} SOC_GIC_NS_GICH_LR2_UNION;
#endif
#define SOC_GIC_NS_GICH_LR2_VirtualID_START   (0)
#define SOC_GIC_NS_GICH_LR2_VirtualID_END     (9)
#define SOC_GIC_NS_GICH_LR2_PhysicalID_START  (10)
#define SOC_GIC_NS_GICH_LR2_PhysicalID_END    (19)
#define SOC_GIC_NS_GICH_LR2_Priority_START    (23)
#define SOC_GIC_NS_GICH_LR2_Priority_END      (27)
#define SOC_GIC_NS_GICH_LR2_State_START       (28)
#define SOC_GIC_NS_GICH_LR2_State_END         (29)
#define SOC_GIC_NS_GICH_LR2_Grp1_START        (30)
#define SOC_GIC_NS_GICH_LR2_Grp1_END          (30)
#define SOC_GIC_NS_GICH_LR2_HW_START          (31)
#define SOC_GIC_NS_GICH_LR2_HW_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICH_LR3_UNION
 �ṹ˵��  : GICH_LR3 �Ĵ����ṹ���塣��ַƫ����:0x410C����ֵ:0x00000000�����:32
 �Ĵ���˵��: list register 3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  VirtualID  : 10; /* bit[0-9]  : ���ж�ͨ��GICV_IAR��Ӧʱ����ID���ظ�Guest OS */
        unsigned int  PhysicalID : 10; /* bit[10-19]: ��GICH_LR.HW=0ʱ��
                                                      [19] EOI ָʾ�ж��Ƿ�ΪEOI maintenance�ж�
                                                      [18:13] Reserved, SBZ
                                                      [12:10] CPUID
                                                      ��GICH_LR.HW=1ʱ��
                                                      ����Hypervisor�͸�distributor�������ж�ID */
        unsigned int  reserved   : 3;  /* bit[20-22]: ���� */
        unsigned int  Priority   : 5;  /* bit[23-27]: ���ȼ� */
        unsigned int  State      : 2;  /* bit[28-29]: �ж�״̬��
                                                      00��invalid
                                                      01��pending
                                                      10��active
                                                      11��pending&active */
        unsigned int  Grp1       : 1;  /* bit[30]   : �����ж��Ƿ�Ϊgruop1��
                                                      0���ж�Ϊgroup0
                                                      1���ж�Ϊgroup1 */
        unsigned int  HW         : 1;  /* bit[31]   : �����ж��Ƿ�ΪӲ�жϣ�
                                                      0���ж�Ϊ���ж�
                                                      1���ж�ΪӲ�ж� */
    } reg;
} SOC_GIC_NS_GICH_LR3_UNION;
#endif
#define SOC_GIC_NS_GICH_LR3_VirtualID_START   (0)
#define SOC_GIC_NS_GICH_LR3_VirtualID_END     (9)
#define SOC_GIC_NS_GICH_LR3_PhysicalID_START  (10)
#define SOC_GIC_NS_GICH_LR3_PhysicalID_END    (19)
#define SOC_GIC_NS_GICH_LR3_Priority_START    (23)
#define SOC_GIC_NS_GICH_LR3_Priority_END      (27)
#define SOC_GIC_NS_GICH_LR3_State_START       (28)
#define SOC_GIC_NS_GICH_LR3_State_END         (29)
#define SOC_GIC_NS_GICH_LR3_Grp1_START        (30)
#define SOC_GIC_NS_GICH_LR3_Grp1_END          (30)
#define SOC_GIC_NS_GICH_LR3_HW_START          (31)
#define SOC_GIC_NS_GICH_LR3_HW_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_CTLR_UNION
 �ṹ˵��  : GICV_CTLR �Ĵ����ṹ���塣��ַƫ����:0x6000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Virtual machine���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EnableGrp0 : 1;  /* bit[0]    : ʹ��������CPU interface��virtual machine����Group0�����жϣ�
                                                      0��ȥʹ��Group0�ж�
                                                      1��ʹ��Group0�ж� */
        unsigned int  EnableGrp1 : 1;  /* bit[1]    : ʹ��������CPU interface��virtual machine����Group1�����жϣ�
                                                      0��ȥʹ��Group1�ж�
                                                      1��ʹ��Group1�ж� */
        unsigned int  AckCtl     : 1;  /* bit[2]    : ARM������ʹ�ø�bit
                                                      ��������ȼ�pending�ж�ΪGroup1�ж�ʱ����GICV_IAR�Ķ������Ƿ������CPU interface��Ӧ�жϣ�
                                                      0�����ص�IDΪ1022
                                                      1������Group1�жϵ�ID */
        unsigned int  FIQEn      : 1;  /* bit[3]    : Group0�ж��Ƿ�Ϊ����FIQ��
                                                      0��Group0�ж�Ϊ����IRQ
                                                      1��Group0�ж�Ϊ����FIQ */
        unsigned int  CBPR       : 1;  /* bit[4]    : Group0��Group1�����ж��Ƿ���GICV_BPR���ƣ�
                                                      0��GICV_BPR����Group0�����жϣ�GICV_ABPR����Group1�����ж�
                                                      1��GICV_BPR����Group0��Group1�����ж� */
        unsigned int  reserved   : 4;  /* bit[5-8]  : ���� */
        unsigned int  EOImode    : 1;  /* bit[9]    : Ӱ��GICV_EOIR,GICV_AEOIR,GICV_DIR
                                                      0��GICV_EOIR��GICV_AEOIRͬʱִ�����ȼ�drop���ж�ʧЧ������GICV_DIRδ֪
                                                      1��GICV_EOIR��GICV_AEOIRִֻ�����ȼ�drop��GICV_DIRִֻ���ж�ʧЧ���� */
        unsigned int  HW         : 22; /* bit[10-31]: �����ж��Ƿ�ΪӲ�жϣ�
                                                      0���ж�Ϊ���ж�
                                                      1���ж�ΪӲ�ж� */
    } reg;
} SOC_GIC_NS_GICV_CTLR_UNION;
#endif
#define SOC_GIC_NS_GICV_CTLR_EnableGrp0_START  (0)
#define SOC_GIC_NS_GICV_CTLR_EnableGrp0_END    (0)
#define SOC_GIC_NS_GICV_CTLR_EnableGrp1_START  (1)
#define SOC_GIC_NS_GICV_CTLR_EnableGrp1_END    (1)
#define SOC_GIC_NS_GICV_CTLR_AckCtl_START      (2)
#define SOC_GIC_NS_GICV_CTLR_AckCtl_END        (2)
#define SOC_GIC_NS_GICV_CTLR_FIQEn_START       (3)
#define SOC_GIC_NS_GICV_CTLR_FIQEn_END         (3)
#define SOC_GIC_NS_GICV_CTLR_CBPR_START        (4)
#define SOC_GIC_NS_GICV_CTLR_CBPR_END          (4)
#define SOC_GIC_NS_GICV_CTLR_EOImode_START     (9)
#define SOC_GIC_NS_GICV_CTLR_EOImode_END       (9)
#define SOC_GIC_NS_GICV_CTLR_HW_START          (10)
#define SOC_GIC_NS_GICV_CTLR_HW_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_PMR_UNION
 �ṹ˵��  : GICV_PMR �Ĵ����ṹ���塣��ַƫ����:0x6004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Virtual machine���ȼ�mask�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 3;  /* bit[0-2] : ���� */
        unsigned int  Priority : 5;  /* bit[3-7] : CPU�ӿ����ȼ����εĵȼ������ж����ȼ����ڴ˼Ĵ�����ֵ�����ж��͸�Ŀ�괦���������֧��256�����ȼ���
                                                   0x00-0xFF(0-255): 256���ȼ�
                                                   0x00-0xFE(0-254): 128���ȼ���ż����
                                                   0x00-0xFC(0-252): 64���ȼ�������Ϊ4��
                                                   0x00-0xF8(0-248): 32���ȼ�������Ϊ8��
                                                   0x00-0xF0(0-240): 16���ȼ�������Ϊ16��
                                                   ������Ϊ0xFFʱ����ʾ�����ж϶������� */
        unsigned int  reserved_1: 24; /* bit[8-31]: ���� */
    } reg;
} SOC_GIC_NS_GICV_PMR_UNION;
#endif
#define SOC_GIC_NS_GICV_PMR_Priority_START  (3)
#define SOC_GIC_NS_GICV_PMR_Priority_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_BPR_UNION
 �ṹ˵��  : GICV_BPR �Ĵ����ṹ���塣��ַƫ����:0x6008����ֵ:0x00000002�����:32
 �Ĵ���˵��: Virtual machine Binary point�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  BinaryPoint : 3;  /* bit[0-2] : ����8-bit�ж����ȼ�����ζ�Ӧ���ڶ����ж���ռ������group���ȼ����Լ������ȼ���
                                                      ע���ǰ�ȫ���ʣ�Ĭ��ֵΪ0x3 */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_GIC_NS_GICV_BPR_UNION;
#endif
#define SOC_GIC_NS_GICV_BPR_BinaryPoint_START  (0)
#define SOC_GIC_NS_GICV_BPR_BinaryPoint_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_IAR_UNION
 �ṹ˵��  : GICV_IAR �Ĵ����ṹ���塣��ַƫ����:0x600C����ֵ:0x000003FF�����:32
 �Ĵ���˵��: Virtual machine�ж���Ӧ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InterruptID : 10; /* bit[0-9]  : �жϺ� */
        unsigned int  CPUID       : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ����򷵻ط����ж������CPU�ӿڱ�ţ��������������жϣ����򷵻�0 */
        unsigned int  reserved    : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_GIC_NS_GICV_IAR_UNION;
#endif
#define SOC_GIC_NS_GICV_IAR_InterruptID_START  (0)
#define SOC_GIC_NS_GICV_IAR_InterruptID_END    (9)
#define SOC_GIC_NS_GICV_IAR_CPUID_START        (10)
#define SOC_GIC_NS_GICV_IAR_CPUID_END          (12)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_EOIR_UNION
 �ṹ˵��  : GICV_EOIR �Ĵ����ṹ���塣��ַƫ����:0x6010����ֵ:0x00000000�����:32
 �Ĵ���˵��: Virtual machine EOI�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EOIINTID : 10; /* bit[0-9]  : �жϺţ���GICC_IARһ�� */
        unsigned int  CPUID    : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ�������GICC_IARһ�£��������������жϣ�������Ч */
        unsigned int  reserved : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_GIC_NS_GICV_EOIR_UNION;
#endif
#define SOC_GIC_NS_GICV_EOIR_EOIINTID_START  (0)
#define SOC_GIC_NS_GICV_EOIR_EOIINTID_END    (9)
#define SOC_GIC_NS_GICV_EOIR_CPUID_START     (10)
#define SOC_GIC_NS_GICV_EOIR_CPUID_END       (12)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_RPR_UNION
 �ṹ˵��  : GICV_RPR �Ĵ����ṹ���塣��ַƫ����:0x6014����ֵ:0x000000FF�����:32
 �Ĵ���˵��: Virtual machine Running Priority�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CPUID    : 8;  /* bit[0-7] : ��ǰCPU�ӿڵ�running���ȼ� */
        unsigned int  reserved : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_GIC_NS_GICV_RPR_UNION;
#endif
#define SOC_GIC_NS_GICV_RPR_CPUID_START     (0)
#define SOC_GIC_NS_GICV_RPR_CPUID_END       (7)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_HPPIR_UNION
 �ṹ˵��  : GICV_HPPIR �Ĵ����ṹ���塣��ַƫ����:0x6018����ֵ:0x000003FF�����:32
 �Ĵ���˵��: Virtual machine ������ȼ�pending�жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PENDINTID : 10; /* bit[0-9]  : �жϺ� */
        unsigned int  CPUID     : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ����򷵻����ɸ��жϵ�CPUID */
        unsigned int  reserved  : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_GIC_NS_GICV_HPPIR_UNION;
#endif
#define SOC_GIC_NS_GICV_HPPIR_PENDINTID_START  (0)
#define SOC_GIC_NS_GICV_HPPIR_PENDINTID_END    (9)
#define SOC_GIC_NS_GICV_HPPIR_CPUID_START      (10)
#define SOC_GIC_NS_GICV_HPPIR_CPUID_END        (12)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_ABPR_UNION
 �ṹ˵��  : GICV_ABPR �Ĵ����ṹ���塣��ַƫ����:0x601C����ֵ:0x00000003�����:32
 �Ĵ���˵��: Virtual machine aliased Binary point�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  BinaryPoint : 3;  /* bit[0-2] : ����8-bit�ж����ȼ�����ζ�Ӧ���ڶ����ж���ռ������group���ȼ����Լ������ȼ��� */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_GIC_NS_GICV_ABPR_UNION;
#endif
#define SOC_GIC_NS_GICV_ABPR_BinaryPoint_START  (0)
#define SOC_GIC_NS_GICV_ABPR_BinaryPoint_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_AIAR_UNION
 �ṹ˵��  : GICV_AIAR �Ĵ����ṹ���塣��ַƫ����:0x6020����ֵ:0x000003FF�����:32
 �Ĵ���˵��: Virtual machine aliased�ж���Ӧ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InterruptID : 10; /* bit[0-9]  : �жϺ� */
        unsigned int  CPUID       : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ����򷵻ط����ж������CPU�ӿڱ�ţ��������������жϣ����򷵻�0 */
        unsigned int  reserved    : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_GIC_NS_GICV_AIAR_UNION;
#endif
#define SOC_GIC_NS_GICV_AIAR_InterruptID_START  (0)
#define SOC_GIC_NS_GICV_AIAR_InterruptID_END    (9)
#define SOC_GIC_NS_GICV_AIAR_CPUID_START        (10)
#define SOC_GIC_NS_GICV_AIAR_CPUID_END          (12)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_AEOIR_UNION
 �ṹ˵��  : GICV_AEOIR �Ĵ����ṹ���塣��ַƫ����:0x6024����ֵ:0x00000000�����:32
 �Ĵ���˵��: Virtual machine aliased EOI�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InterruptID : 10; /* bit[0-9]  : �жϺţ���GICC_IARһ�� */
        unsigned int  CPUID       : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ�������GICC_IARһ�£��������������жϣ�������Ч */
        unsigned int  reserved    : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_GIC_NS_GICV_AEOIR_UNION;
#endif
#define SOC_GIC_NS_GICV_AEOIR_InterruptID_START  (0)
#define SOC_GIC_NS_GICV_AEOIR_InterruptID_END    (9)
#define SOC_GIC_NS_GICV_AEOIR_CPUID_START        (10)
#define SOC_GIC_NS_GICV_AEOIR_CPUID_END          (12)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_AHPPIR_UNION
 �ṹ˵��  : GICV_AHPPIR �Ĵ����ṹ���塣��ַƫ����:0x6028����ֵ:0x000003FF�����:32
 �Ĵ���˵��: Virtual machine aliased ������ȼ�pending�жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PENDINTID : 10; /* bit[0-9]  : �����Group1�жϣ��򷵻��жϺţ����򣬷���0x3FF */
        unsigned int  CPUID     : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ����򷵻����ɸ��жϵ�CPUID */
        unsigned int  reserved  : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_GIC_NS_GICV_AHPPIR_UNION;
#endif
#define SOC_GIC_NS_GICV_AHPPIR_PENDINTID_START  (0)
#define SOC_GIC_NS_GICV_AHPPIR_PENDINTID_END    (9)
#define SOC_GIC_NS_GICV_AHPPIR_CPUID_START      (10)
#define SOC_GIC_NS_GICV_AHPPIR_CPUID_END        (12)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_APR0_UNION
 �ṹ˵��  : GICV_APR0 �Ĵ����ṹ���塣��ַƫ����:0x60D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Virtual machine��Ծ���ȼ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Active_priority_bits : 32; /* bit[0-31]: ������Ӧλ����ռ�����Ƿ��Ծ��
                                                               0������Ծ
                                                               1����Ծ */
    } reg;
} SOC_GIC_NS_GICV_APR0_UNION;
#endif
#define SOC_GIC_NS_GICV_APR0_Active_priority_bits_START  (0)
#define SOC_GIC_NS_GICV_APR0_Active_priority_bits_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_IIDR_UNION
 �ṹ˵��  : GICV_IIDR �Ĵ����ṹ���塣��ַƫ����:0x60FC����ֵ:0x0202043B�����:32
 �Ĵ���˵��: Virtual machine CPU�ӿ�ʶ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Implementer : 12; /* bit[0-11] : ������
                                                       0x43B: ARM */
        unsigned int  Revision    : 4;  /* bit[12-15]: CPU�ӿڰ汾
                                                       0x0: Revision 0 */
        unsigned int  ArchVersion : 4;  /* bit[16-19]: GIC��ϵ�ṹ�汾
                                                       0x2: Version 2.0 */
        unsigned int  ProductID   : 12; /* bit[20-31]: ������
                                                       0x010: Cortex-A53 MPCore */
    } reg;
} SOC_GIC_NS_GICV_IIDR_UNION;
#endif
#define SOC_GIC_NS_GICV_IIDR_Implementer_START  (0)
#define SOC_GIC_NS_GICV_IIDR_Implementer_END    (11)
#define SOC_GIC_NS_GICV_IIDR_Revision_START     (12)
#define SOC_GIC_NS_GICV_IIDR_Revision_END       (15)
#define SOC_GIC_NS_GICV_IIDR_ArchVersion_START  (16)
#define SOC_GIC_NS_GICV_IIDR_ArchVersion_END    (19)
#define SOC_GIC_NS_GICV_IIDR_ProductID_START    (20)
#define SOC_GIC_NS_GICV_IIDR_ProductID_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_GIC_NS_GICV_DIR_UNION
 �ṹ˵��  : GICV_DIR �Ĵ����ṹ���塣��ַƫ����:0x7000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Virtual machine CPU�ӿ��ж�Deactivate�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InterruptID : 10; /* bit[0-9]  : �жϺ� */
        unsigned int  CPUID       : 3;  /* bit[10-12]: ���ڶ��ϵͳ�е�SGI�жϣ������ṩ��������Ĵ�����CPUID */
        unsigned int  reserved    : 19; /* bit[13-31]:  */
    } reg;
} SOC_GIC_NS_GICV_DIR_UNION;
#endif
#define SOC_GIC_NS_GICV_DIR_InterruptID_START  (0)
#define SOC_GIC_NS_GICV_DIR_InterruptID_END    (9)
#define SOC_GIC_NS_GICV_DIR_CPUID_START        (10)
#define SOC_GIC_NS_GICV_DIR_CPUID_END          (12)






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

#endif /* end of soc_gic_ns_interface.h */
