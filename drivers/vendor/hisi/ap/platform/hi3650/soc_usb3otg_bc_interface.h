/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_usb3otg_bc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-04-29 15:47:09
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��4��29��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_USB3OTG_BC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_USB3OTG_BC_INTERFACE_H__
#define __SOC_USB3OTG_BC_INTERFACE_H__

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
/* �Ĵ���˵����ѡ����ƼĴ���0
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_CTRL0_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_ADDR(base)       ((base) + (0x00))

/* �Ĵ���˵����USB�������������üĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_CTRL1_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_ADDR(base)       ((base) + (0x04))

/* �Ĵ���˵����PHY�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_CTRL2_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL2_ADDR(base)       ((base) + (0x08))

/* �Ĵ���˵����ѡ����ƼĴ���3
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_CTRL3_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_ADDR(base)       ((base) + (0x0C))

/* �Ĵ���˵����legacy USB���������Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_CTRL4_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_ADDR(base)       ((base) + (0x10))

/* �Ĵ���˵����SS���������Ĵ���1
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_CTRL5_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_ADDR(base)       ((base) + (0x14))

/* �Ĵ���˵����SS���������Ĵ���2
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_CTRL6_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_ADDR(base)       ((base) + (0x18))

/* �Ĵ���˵����ѡ����ƼĴ���7
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_CTRL7_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ADDR(base)       ((base) + (0x1C))

/* �Ĵ���˵����״̬�Ĵ���0
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_STS0_UNION */
#define SOC_USB3OTG_BC_USBOTG3_STS0_ADDR(base)        ((base) + (0x20))

/* �Ĵ���˵����״̬�Ĵ���1
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_STS1_UNION */
#define SOC_USB3OTG_BC_USBOTG3_STS1_ADDR(base)        ((base) + (0x24))

/* �Ĵ���˵����״̬�Ĵ���2
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_STS2_UNION */
#define SOC_USB3OTG_BC_USBOTG3_STS2_ADDR(base)        ((base) + (0x28))

/* �Ĵ���˵����״̬�Ĵ���3
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_STS3_UNION */
#define SOC_USB3OTG_BC_USBOTG3_STS3_ADDR(base)        ((base) + (0x2C))

/* �Ĵ���˵����BC�������Ĵ���0
   λ����UNION�ṹ:  SOC_USB3OTG_BC_BC_CTRL0_UNION */
#define SOC_USB3OTG_BC_BC_CTRL0_ADDR(base)            ((base) + (0x30))

/* �Ĵ���˵����BC�������Ĵ���1
   λ����UNION�ṹ:  SOC_USB3OTG_BC_BC_CTRL1_UNION */
#define SOC_USB3OTG_BC_BC_CTRL1_ADDR(base)            ((base) + (0x34))

/* �Ĵ���˵����BC�������Ĵ���2
   λ����UNION�ṹ:  SOC_USB3OTG_BC_BC_CTRL2_UNION */
#define SOC_USB3OTG_BC_BC_CTRL2_ADDR(base)            ((base) + (0x38))

/* �Ĵ���˵����BC״̬�Ĵ���0
   λ����UNION�ṹ:  SOC_USB3OTG_BC_BC_STS0_UNION */
#define SOC_USB3OTG_BC_BC_STS0_ADDR(base)             ((base) + (0x3C))

/* �Ĵ���˵����RAM���ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_BC_RAM_CTRL_UNION */
#define SOC_USB3OTG_BC_RAM_CTRL_ADDR(base)            ((base) + (0x40))

/* �Ĵ���˵����״̬�Ĵ���4
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USBOTG3_STS4_UNION */
#define SOC_USB3OTG_BC_USBOTG3_STS4_ADDR(base)        ((base) + (0x44))

/* �Ĵ���˵����PHY���ƼĴ���
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USB3PHY_CTRL_UNION */
#define SOC_USB3OTG_BC_USB3PHY_CTRL_ADDR(base)        ((base) + (0x48))

/* �Ĵ���˵����PHY״̬�Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USB3PHY_STS_UNION */
#define SOC_USB3OTG_BC_USB3PHY_STS_ADDR(base)         ((base) + (0x4C))

/* �Ĵ���˵����PHY�ڲ��Ĵ���״̬
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USB3PHY_CR_STS_UNION */
#define SOC_USB3OTG_BC_USB3PHY_CR_STS_ADDR(base)      ((base) + (0x50))

/* �Ĵ���˵����PHY�ڲ��Ĵ�������
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USB3PHY_CR_CTRL_UNION */
#define SOC_USB3OTG_BC_USB3PHY_CR_CTRL_ADDR(base)     ((base) + (0x54))

/* �Ĵ���˵����USBԤ���Ĵ���
   λ����UNION�ṹ:  SOC_USB3OTG_BC_USB3_RES_UNION */
#define SOC_USB3OTG_BC_USB3_RES_ADDR(base)            ((base) + (0x58))





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
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_CTRL0_UNION
 �ṹ˵��  : USBOTG3_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x00000008�����:32
 �Ĵ���˵��: ѡ����ƼĴ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  idpullup_sel     : 1;  /* bit[0]    : ID��������ʹ��ѡ��
                                                            0����������
                                                            1���Ĵ��� */
        unsigned int  idpullup         : 1;  /* bit[1]    : ID��������ʹ�� */
        unsigned int  iddig_sel        : 1;  /* bit[2]    : ACA�ӿ���Դѡ��
                                                            00�����ԼĴ�����
                                                            01������PHY��iddig��
                                                            10������PHY��ACA�ӿڣ�
                                                            ���������� */
        unsigned int  iddig            : 1;  /* bit[3]    : ����ģʽʶ�� */
        unsigned int  drvvbus_sel      : 1;  /* bit[4]    : ����vbus��ѹѡ��
                                                            0�����Կ�������
                                                            1�����ԼĴ��� */
        unsigned int  drvvbus          : 1;  /* bit[5]    : ʹ��vbusʩ�ӵ�ѹ */
        unsigned int  vbusvalid_sel    : 1;  /* bit[6]    : ��������vbusvalid�ź���Դѡ��
                                                            0��ѡ��PHY�����vbusvalid;
                                                            1��ѡ���ڲ���drvvbus�ź� */
        unsigned int  sc_avalid        : 1;  /* bit[7]    : �Ĵ�����sc_avalid */
        unsigned int  avalid_sel       : 1;  /* bit[8]    : avalidѡ��
                                                            0��ѡͨPHY��avalid_
                                                            1��ѡͨ�Ĵ�����sc_avalid */
        unsigned int  sc_bvalid        : 1;  /* bit[9]    : �Ĵ�����sc_bvalid */
        unsigned int  bvalid_sel       : 1;  /* bit[10]   : bvalidѡ��
                                                            0��ѡͨPHY��bvalid_
                                                            1��ѡͨ�Ĵ�����sc_bvalid */
        unsigned int  sc_powerpresent  : 1;  /* bit[11]   : �Ĵ�����sc_powerpresent */
        unsigned int  powerpresent_sel : 1;  /* bit[12]   : powerpresentѡ��
                                                            0��ѡͨPHY��powerpresent
                                                            1��ѡͨ�Ĵ�����sc_powerpresent */
        unsigned int  sc_sessvld       : 1;  /* bit[13]   : �Ĵ�����sc_sessvld */
        unsigned int  sessvld_sel      : 1;  /* bit[14]   : Session Validѡ��
                                                            0��ѡͨPHY��sessvld
                                                            1��ѡͨ�Ĵ�����sc_sessvld */
        unsigned int  reserved         : 17; /* bit[15-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL0_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_idpullup_sel_START      (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_idpullup_sel_END        (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_idpullup_START          (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_idpullup_END            (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_iddig_sel_START         (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_iddig_sel_END           (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_iddig_START             (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_iddig_END               (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_drvvbus_sel_START       (4)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_drvvbus_sel_END         (4)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_drvvbus_START           (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_drvvbus_END             (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_vbusvalid_sel_START     (6)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_vbusvalid_sel_END       (6)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_sc_avalid_START         (7)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_sc_avalid_END           (7)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_avalid_sel_START        (8)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_avalid_sel_END          (8)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_sc_bvalid_START         (9)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_sc_bvalid_END           (9)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_bvalid_sel_START        (10)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_bvalid_sel_END          (10)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_sc_powerpresent_START   (11)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_sc_powerpresent_END     (11)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_powerpresent_sel_START  (12)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_powerpresent_sel_END    (12)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_sc_sessvld_START        (13)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_sc_sessvld_END          (13)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_sessvld_sel_START       (14)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_sessvld_sel_END         (14)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_CTRL1_UNION
 �ṹ˵��  : USBOTG3_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x00020080�����:32
 �Ĵ���˵��: USB�������������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_u2_port_disable            : 1;  /* bit[0]    : USB2.0�˿�ȥʹ�ܿ��ơ�
                                                                           0���˿�ʹ��
                                                                           1���˿�ȥʹ�� */
        unsigned int  host_u3_port_disable            : 1;  /* bit[1]    : USB2 SS�˿�ȥʹ�ܿ��ơ�
                                                                           0���˿�ʹ��
                                                                           1���˿�ȥʹ�� */
        unsigned int  hub_port_overcurrent            : 2;  /* bit[2-3]  : ������������ָʾ����λ����SS �˿ڣ���λ����legacy�˿ڡ� */
        unsigned int  hub_port_perm_attach            : 2;  /* bit[4-5]  : ����ָʾ�Ƿ����豸�������������ж˿��ϡ���λ����SS �˿ڣ���λ����legacy�˿�
                                                                           1����������
                                                                           0������������ */
        unsigned int  host_port_power_control_present : 1;  /* bit[6]    : �˿ڵ�Դ���ơ�
                                                                           1��ָʾ�˿��е�Դ����
                                                                           0���˿�û�е�Դ���� */
        unsigned int  xhc_bme                         : 1;  /* bit[7]    : ʹ������master���̶�Ϊ1�� */
        unsigned int  bus_filter_bypass               : 4;  /* bit[8-11] : ���߹�����·���ơ�
                                                                           [3]:��·utmiotg_iddig�Ĺ���
                                                                           [2]:��·utmisrp_bvalid�Ĺ���
                                                                           [1]:��·pipe3_PowerPresent�Ĺ���
                                                                           [0]:��·utmiotg_vbusvalid�Ĺ��� */
        unsigned int  fladj_30mhz_reg                 : 6;  /* bit[12-17]: HS jitter������У׼micro-frame��׼ȷ�ȡ� */
        unsigned int  reserved                        : 14; /* bit[18-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL1_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_host_u2_port_disable_START             (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_host_u2_port_disable_END               (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_host_u3_port_disable_START             (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_host_u3_port_disable_END               (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_hub_port_overcurrent_START             (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_hub_port_overcurrent_END               (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_hub_port_perm_attach_START             (4)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_hub_port_perm_attach_END               (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_host_port_power_control_present_START  (6)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_host_port_power_control_present_END    (6)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_xhc_bme_START                          (7)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_xhc_bme_END                            (7)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_bus_filter_bypass_START                (8)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_bus_filter_bypass_END                  (11)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_fladj_30mhz_reg_START                  (12)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_fladj_30mhz_reg_END                    (17)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_CTRL2_UNION
 �ṹ˵��  : USBOTG3_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x00000000�����:32
 �Ĵ���˵��: PHY�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  test_powerdown_hsp : 1;  /* bit[0]   : ���ٵ�·�µ���� */
        unsigned int  test_powerdown_ssp : 1;  /* bit[1]   : ���ٵ�·�µ���� */
        unsigned int  reserved           : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL2_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL2_test_powerdown_hsp_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL2_test_powerdown_hsp_END    (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL2_test_powerdown_ssp_START  (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL2_test_powerdown_ssp_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_CTRL3_UNION
 �ṹ˵��  : USBOTG3_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x00000004�����:32
 �Ĵ���˵��: ѡ����ƼĴ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  commononn     : 1;  /* bit[0]   : PHY��COMMON��·��Դ���� */
        unsigned int  otgdisable    : 1;  /* bit[1]   : �ر�PHY��OTG���ԡ� */
        unsigned int  retenablen    : 1;  /* bit[2]   : ������ȱʡֵΪ1�� */
        unsigned int  txbitstuffen  : 1;  /* bit[3]   : ��opmode=2'b11ʱ������DATAIN[7:0]�ϵ�bit stuffing
                                                        1: Bit stuffingʹ��
                                                        0: Bit stuffingȥʹ��. */
        unsigned int  txbitstuffehn : 1;  /* bit[4]   : ��opmode=2'b11ʱ������DATAIN[15:8]�ϵ�bit stuffing
                                                        1: Bit stuffingʹ��
                                                        0: Bit stuffingȥʹ��. */
        unsigned int  vbusvldextsel : 1;  /* bit[5]   : VBUS��Чѡ��
                                                        0������PHY�ڲ��Ƚ���
                                                        1�����ԼĴ��� */
        unsigned int  vbusvldext    : 1;  /* bit[6]   : VBUS��Ч */
        unsigned int  reserved      : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL3_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_commononn_START      (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_commononn_END        (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_otgdisable_START     (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_otgdisable_END       (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_retenablen_START     (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_retenablen_END       (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_txbitstuffen_START   (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_txbitstuffen_END     (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_txbitstuffehn_START  (4)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_txbitstuffehn_END    (4)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_vbusvldextsel_START  (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_vbusvldextsel_END    (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_vbusvldext_START     (6)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_vbusvldext_END       (6)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_CTRL4_UNION
 �ṹ˵��  : USBOTG3_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x00E466DB�����:32
 �Ĵ���˵��: legacy USB���������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  compdistune       : 3;  /* bit[0-2]  : Hostģʽ���豸������ֵ���ڡ� */
        unsigned int  otgtune           : 3;  /* bit[3-5]  : ����Vbus��ֵ�� */
        unsigned int  sqrxtune          : 3;  /* bit[6-8]  : HSģʽ��squelch��ѹ��ֵ���� */
        unsigned int  txfslstune        : 4;  /* bit[9-12] : FS/LSģʽ�£�����Ԫ�迹���ڡ� */
        unsigned int  txhsxvtune        : 2;  /* bit[13-14]: HSģʽ�£���ͼ�������ڲ��� */
        unsigned int  txpreempamptune   : 2;  /* bit[15-16]: ��������������ֵ�� */
        unsigned int  txpreemppulsetune : 1;  /* bit[17]   : Ԥ���ص�������ʱ�����������ȱʡֵΪ0. */
        unsigned int  txrestune         : 2;  /* bit[18-19]: ��������Դ���迹ƥ�䡣ȱʡֵ2'b01. */
        unsigned int  txrisetune        : 2;  /* bit[20-21]: HSģʽ����/�½�ʱ�����������ȱʡֵΪ2'b10 */
        unsigned int  txvreftune        : 4;  /* bit[22-25]: �� �� ֱ �� �� ƽ �� �� �� ȱ ʡ ֵ Ϊ4��b1000.������ֵΪ 400mv */
        unsigned int  reserved          : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL4_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_compdistune_START        (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_compdistune_END          (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_otgtune_START            (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_otgtune_END              (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_sqrxtune_START           (6)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_sqrxtune_END             (8)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txfslstune_START         (9)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txfslstune_END           (12)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txhsxvtune_START         (13)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txhsxvtune_END           (14)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txpreempamptune_START    (15)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txpreempamptune_END      (16)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txpreemppulsetune_START  (17)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txpreemppulsetune_END    (17)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txrestune_START          (18)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txrestune_END            (19)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txrisetune_START         (20)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txrisetune_END           (21)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txvreftune_START         (22)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txvreftune_END           (25)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_CTRL5_UNION
 �ṹ˵��  : USBOTG3_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x14����ֵ:0xFEE38605�����:32
 �Ĵ���˵��: SS���������Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  los_bias        : 3;  /* bit[0-2]  : LoS�������ֵ���ơ� */
        unsigned int  rx_los_mask_val : 10; /* bit[3-12] : ����LoS��Ĥ��ȡ���Ҫ�����ǹ��˲�����LPPS���źš� */
        unsigned int  tx_deemph_3p5db : 6;  /* bit[13-18]: 3.5DBȥ���� */
        unsigned int  tx_deemph_6db   : 6;  /* bit[19-24]: 6DBȥ���� */
        unsigned int  tx_swing_full   : 7;  /* bit[25-31]: TXǿ�ȵ��� */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL5_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_los_bias_START         (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_los_bias_END           (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_rx_los_mask_val_START  (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_rx_los_mask_val_END    (12)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_tx_deemph_3p5db_START  (13)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_tx_deemph_3p5db_END    (18)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_tx_deemph_6db_START    (19)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_tx_deemph_6db_END      (24)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_tx_swing_full_START    (25)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_tx_swing_full_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_CTRL6_UNION
 �ṹ˵��  : USBOTG3_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x18����ֵ:0x00000004�����:32
 �Ĵ���˵��: SS���������Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_vboost_lvl  : 3;  /* bit[0-2]  : TX��ѹBoost��ƽ���ơ� */
        unsigned int  testpoint_en   : 1;  /* bit[3]    : testpointʹ�� */
        unsigned int  refclk_mux_sel : 1;  /* bit[4]    : PHY�ο�ʱ��Դѡ��
                                                          0����IO�ṩ19.2MHz
                                                          1����PLL��Ƶ����Ƶ����䣬Ĭ��24MHz */
        unsigned int  testpoint_sel  : 5;  /* bit[5-9]  : testpoint sel */
        unsigned int  hsxcvrextctl0  : 1;  /* bit[10]   : HS Transceiver�첽���� */
        unsigned int  reserved       : 21; /* bit[11-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL6_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_tx_vboost_lvl_START   (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_tx_vboost_lvl_END     (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_testpoint_en_START    (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_testpoint_en_END      (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_refclk_mux_sel_START  (4)
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_refclk_mux_sel_END    (4)
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_testpoint_sel_START   (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_testpoint_sel_END     (9)
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_hsxcvrextctl0_START   (10)
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_hsxcvrextctl0_END     (10)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_CTRL7_UNION
 �ṹ˵��  : USBOTG3_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x000200E2�����:32
 �Ĵ���˵��: ѡ����ƼĴ���7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  refclksel          : 2;  /* bit[0-1]  : �ο�ʱ��ѡ��ȱʡΪ2'b10. */
        unsigned int  fsel               : 6;  /* bit[2-7]  : �ο�ʱ��Ƶ��ѡ��
                                                              6'h38: 19.2MHz
                                                              6'h2A: 24MHz */
        unsigned int  mpll_multiplier    : 7;  /* bit[8-14] : MPLLƵ�ʳ������ơ�Ĭ��Ϊ0������Ҫ������ */
        unsigned int  ref_clkdiv2        : 1;  /* bit[15]   : ����ο�ʱ�ӷ�Ƶ���ơ�
                                                              1���ο�ʱ�Ӵ���100MHz
                                                              0���ο�ʱ�ӵ���100MHz */
        unsigned int  ref_ssp_en         : 1;  /* bit[16]   : SS���ܲο�ʱ��ʹ�� */
        unsigned int  ssc_en             : 1;  /* bit[17]   : ��Ƶʹ�ܡ�
                                                              1��ʹ����Ƶ
                                                              0��ȥʹ�� */
        unsigned int  ssc_range          : 3;  /* bit[18-20]: ��Ƶʱ�ӷ�Χ����λPPM��
                                                              3'b000:-4980
                                                              3'b001: -4492
                                                              3'b010:-4003
                                                              ���������� */
        unsigned int  ssc_ref_clk_sel    : 9;  /* bit[21-29]: ��Ƶ�ο�ʱ��ƫ�ơ� */
        unsigned int  lane0_ext_pclk_req : 1;  /* bit[30]   : �ⲿPIPEʱ��ʹ������ */
        unsigned int  lane0_tx2rx_loopbk : 1;  /* bit[31]   : Loopbackʹ�ܿ��� */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL7_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_refclksel_START           (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_refclksel_END             (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_fsel_START                (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_fsel_END                  (7)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_mpll_multiplier_START     (8)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_mpll_multiplier_END       (14)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ref_clkdiv2_START         (15)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ref_clkdiv2_END           (15)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ref_ssp_en_START          (16)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ref_ssp_en_END            (16)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ssc_en_START              (17)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ssc_en_END                (17)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ssc_range_START           (18)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ssc_range_END             (20)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ssc_ref_clk_sel_START     (21)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ssc_ref_clk_sel_END       (29)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_lane0_ext_pclk_req_START  (30)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_lane0_ext_pclk_req_END    (30)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_lane0_tx2rx_loopbk_START  (31)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_lane0_tx2rx_loopbk_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_STS0_UNION
 �ṹ˵��  : USBOTG3_STS0 �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: ״̬�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_STS0_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_STS0_debug_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_STS0_debug_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_STS1_UNION
 �ṹ˵��  : USBOTG3_STS1 �Ĵ����ṹ���塣��ַƫ����:0x24����ֵ:0x00000000�����:32
 �Ĵ���˵��: ״̬�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debugh : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_STS1_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_STS1_debugh_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_STS1_debugh_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_STS2_UNION
 �ṹ˵��  : USBOTG3_STS2 �Ĵ����ṹ���塣��ַƫ����:0x28����ֵ:0x00000000�����:32
 �Ĵ���˵��: ״̬�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  logic_analyzer_trace : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_STS2_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_STS2_logic_analyzer_trace_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_STS2_logic_analyzer_trace_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_STS3_UNION
 �ṹ˵��  : USBOTG3_STS3 �Ĵ����ṹ���塣��ַƫ����:0x2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ״̬�Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  logic_analyzer_traceh : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_STS3_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_STS3_logic_analyzer_traceh_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_STS3_logic_analyzer_traceh_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_BC_CTRL0_UNION
 �ṹ˵��  : BC_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0x00000205�����:32
 �Ĵ���˵��: BC�������Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_opmode     : 2;  /* bit[0-1]  : �����ʱ��OPMODE�Ŀ��� */
        unsigned int  bc_xcvrselect : 2;  /* bit[2-3]  : ���ģʽʱ��PHY��transmiterѡ�� */
        unsigned int  bc_termselect : 1;  /* bit[4]    : ���ģʽʱ��PHY���迹ѡ�� */
        unsigned int  bc_txvalid    : 1;  /* bit[5]    : ���ģʽ��TX��Чʹ�ܿ��� */
        unsigned int  bc_txvalidh   : 1;  /* bit[6]    : ���ģʽ��TX��Чʹ�ܿ��� */
        unsigned int  bc_dppulldown : 1;  /* bit[7]    : ���ģʽ��DP������������� */
        unsigned int  bc_dmpulldown : 1;  /* bit[8]    : ���ģʽ��DM������������� */
        unsigned int  bc_suspend_n  : 1;  /* bit[9]    : ���ģʽ��suspendn���ơ�ȱʡΪ1 */
        unsigned int  bc_idpullup   : 1;  /* bit[10]   : ���ģʽ��idpullup���� */
        unsigned int  reserved      : 21; /* bit[11-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_BC_CTRL0_UNION;
#endif
#define SOC_USB3OTG_BC_BC_CTRL0_bc_opmode_START      (0)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_opmode_END        (1)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_xcvrselect_START  (2)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_xcvrselect_END    (3)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_termselect_START  (4)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_termselect_END    (4)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_txvalid_START     (5)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_txvalid_END       (5)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_txvalidh_START    (6)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_txvalidh_END      (6)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_dppulldown_START  (7)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_dppulldown_END    (7)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_dmpulldown_START  (8)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_dmpulldown_END    (8)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_suspend_n_START   (9)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_suspend_n_END     (9)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_idpullup_START    (10)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_idpullup_END      (10)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_BC_CTRL1_UNION
 �ṹ˵��  : BC_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x34����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC�������Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_mode  : 1;  /* bit[0]   : �����ģʽʹ�ܡ�
                                                   1��ʹ�ܳ����
                                                   0������ⲻʹ�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_BC_CTRL1_UNION;
#endif
#define SOC_USB3OTG_BC_BC_CTRL1_bc_mode_START   (0)
#define SOC_USB3OTG_BC_BC_CTRL1_bc_mode_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_BC_CTRL2_UNION
 �ṹ˵��  : BC_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC�������Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_phy_acaenb     : 1;  /* bit[0]   : ACA�ӿ�ʹ�� */
        unsigned int  bc_phy_dcdenb     : 1;  /* bit[1]   : DCD���ʹ�� */
        unsigned int  bc_phy_chrgsel    : 1;  /* bit[2]   : ���Դѡ��
                                                            1��Դ��ѹ����DM����DP������
                                                            0��Դ��ѹ����DP����DM������ */
        unsigned int  bc_phy_vdatarcenb : 1;  /* bit[3]   : ���Դʹ�ܿ��ơ�
                                                            1��Դ��ѹʹ��
                                                            0��Դ��ѹȥʹ�� */
        unsigned int  bc_phy_vdatdetenb : 1;  /* bit[4]   : ������Ӽ��ʹ�ܡ�
                                                            1��DATA����ѹʹ��
                                                            0��DATA����ѹȥʹ�� */
        unsigned int  reserved          : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_BC_CTRL2_UNION;
#endif
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_acaenb_START      (0)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_acaenb_END        (0)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_dcdenb_START      (1)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_dcdenb_END        (1)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_chrgsel_START     (2)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_chrgsel_END       (2)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_vdatarcenb_START  (3)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_vdatarcenb_END    (3)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_vdatdetenb_START  (4)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_vdatdetenb_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_BC_STS0_UNION
 �ṹ˵��  : BC_STS0 �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC״̬�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_sessvld      : 1;  /* bit[0]    : session ��Ч */
        unsigned int  bc_rid_a        : 1;  /* bit[1]    : ACA�ӿ�״̬ */
        unsigned int  bc_rid_b        : 1;  /* bit[2]    : ACA�ӿ�״̬ */
        unsigned int  bc_rid_c        : 1;  /* bit[3]    : ACA�ӿ�״̬ */
        unsigned int  bc_rid_float    : 1;  /* bit[4]    : ACA�ӿ�״̬ */
        unsigned int  bc_rid_gnd      : 1;  /* bit[5]    : ACA�ӿ�״̬ */
        unsigned int  bc_phy_fsvplus  : 1;  /* bit[6]    : DP״̬ */
        unsigned int  bc_phy_fsvminus : 1;  /* bit[7]    : DM״̬ */
        unsigned int  bc_phy_chgdet   : 1;  /* bit[8]    : ��������״̬��
                                                           1����⵽�����
                                                           0��δ��⵽ */
        unsigned int  bc_linestate    : 2;  /* bit[9-10] : ��������״̬ */
        unsigned int  reserved        : 21; /* bit[11-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_BC_STS0_UNION;
#endif
#define SOC_USB3OTG_BC_BC_STS0_bc_sessvld_START       (0)
#define SOC_USB3OTG_BC_BC_STS0_bc_sessvld_END         (0)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_a_START         (1)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_a_END           (1)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_b_START         (2)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_b_END           (2)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_c_START         (3)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_c_END           (3)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_float_START     (4)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_float_END       (4)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_gnd_START       (5)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_gnd_END         (5)
#define SOC_USB3OTG_BC_BC_STS0_bc_phy_fsvplus_START   (6)
#define SOC_USB3OTG_BC_BC_STS0_bc_phy_fsvplus_END     (6)
#define SOC_USB3OTG_BC_BC_STS0_bc_phy_fsvminus_START  (7)
#define SOC_USB3OTG_BC_BC_STS0_bc_phy_fsvminus_END    (7)
#define SOC_USB3OTG_BC_BC_STS0_bc_phy_chgdet_START    (8)
#define SOC_USB3OTG_BC_BC_STS0_bc_phy_chgdet_END      (8)
#define SOC_USB3OTG_BC_BC_STS0_bc_linestate_START     (9)
#define SOC_USB3OTG_BC_BC_STS0_bc_linestate_END       (10)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_RAM_CTRL_UNION
 �ṹ˵��  : RAM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x40����ֵ:0x00000000�����:32
 �Ĵ���˵��: RAM���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ram0_slp : 1;  /* bit[0]   : ram0�͹��Ŀ��� */
        unsigned int  ram1_slp : 1;  /* bit[1]   : ram1�͹��Ŀ��� */
        unsigned int  ram2_slp : 1;  /* bit[2]   : ram2�͹��Ŀ��� */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_RAM_CTRL_UNION;
#endif
#define SOC_USB3OTG_BC_RAM_CTRL_ram0_slp_START  (0)
#define SOC_USB3OTG_BC_RAM_CTRL_ram0_slp_END    (0)
#define SOC_USB3OTG_BC_RAM_CTRL_ram1_slp_START  (1)
#define SOC_USB3OTG_BC_RAM_CTRL_ram1_slp_END    (1)
#define SOC_USB3OTG_BC_RAM_CTRL_ram2_slp_START  (2)
#define SOC_USB3OTG_BC_RAM_CTRL_ram2_slp_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USBOTG3_STS4_UNION
 �ṹ˵��  : USBOTG3_STS4 �Ĵ����ṹ���塣��ַƫ����:0x44����ֵ:0x00000000�����:32
 �Ĵ���˵��: ״̬�Ĵ���4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_chirp_on : 1;  /* bit[0]   : ������ */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_STS4_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_STS4_bc_chirp_on_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_STS4_bc_chirp_on_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USB3PHY_CTRL_UNION
 �ṹ˵��  : USB3PHY_CTRL �Ĵ����ṹ���塣��ַƫ����:0x48����ֵ:0x00012010�����:32
 �Ĵ���˵��: PHY���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usb3otg_phy_atereset             : 1;  /* bit[0]    : ATE���Ը�λ�ź� */
        unsigned int  usb3otg_phy_autorsmenb           : 1;  /* bit[1]    : �Զ�����ģʽʹ�ܿ��� */
        unsigned int  usb3otg_phy_loopbackenb          : 1;  /* bit[2]    : ���ز���ʹ��
                                                                            1: HS�����߼�ʹ��
                                                                            0:HS�����߼�ȥʹ�� */
        unsigned int  usb3otg_phy_vatestenb            : 1;  /* bit[3]    : ģ����Թܽ�ʹ��ѡ��
                                                                            1: ID�ܽſ��������۲�ģ���ѹ
                                                                            0: ģ����Ե�ѹ������ID�Ϲ۲� */
        unsigned int  usb3otg_phy_vdatreftune          : 2;  /* bit[4-5]  : ���ݹܽŲο���ѹ���� */
        unsigned int  usb3otg_phy_alt_clk_en           : 1;  /* bit[6]    : ��ѡʱ��ʹ�� */
        unsigned int  usb3otg_phy_alt_clk_sel          : 1;  /* bit[7]    : ʱ��Դѡ��
                                                                            1: ʹ��alternateʱ��.
                                                                            0: ʹ���ڲ�MPLL��ʱ��.  */
        unsigned int  usb3otg_phy_lane0_tx_term_offset : 5;  /* bit[8-12] : ���Ͷ��迹offset���� */
        unsigned int  usb3otg_phy_los_level            : 5;  /* bit[13-17]: LoS�����ֵ */
        unsigned int  usb3otg_phy_mpll_refssc_clk_en   : 1;  /* bit[18]   : ��Ƶʱ��ʹ�ܿ��� */
        unsigned int  usb3otg_phy_ref_use_pad          : 1;  /* bit[19]   : PAD�ο�ʱ��ʹ�ܿ���
                                                                            1��ʹ��PAD�ο�ʱ��
                                                                            0��ʹ��Ƭ�ϲο�ʱ�� */
        unsigned int  usb3otg_phy_ref_use_xo           : 1;  /* bit[20]   : ����  */
        unsigned int  usb3otg_phy_ref_xo_en            : 1;  /* bit[21]   : ����  */
        unsigned int  usb3otg_phy_rtune_req            : 1;  /* bit[22]   : ����������� */
        unsigned int  usb3otg_phy_test_burnin          : 1;  /* bit[23]   : test_burninʹ�� */
        unsigned int  reserved                         : 8;  /* bit[24-31]:  */
    } reg;
} SOC_USB3OTG_BC_USB3PHY_CTRL_UNION;
#endif
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_atereset_START              (0)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_atereset_END                (0)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_autorsmenb_START            (1)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_autorsmenb_END              (1)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_loopbackenb_START           (2)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_loopbackenb_END             (2)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_vatestenb_START             (3)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_vatestenb_END               (3)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_vdatreftune_START           (4)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_vdatreftune_END             (5)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_alt_clk_en_START            (6)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_alt_clk_en_END              (6)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_alt_clk_sel_START           (7)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_alt_clk_sel_END             (7)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_lane0_tx_term_offset_START  (8)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_lane0_tx_term_offset_END    (12)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_los_level_START             (13)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_los_level_END               (17)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_mpll_refssc_clk_en_START    (18)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_mpll_refssc_clk_en_END      (18)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_ref_use_pad_START           (19)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_ref_use_pad_END             (19)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_ref_use_xo_START            (20)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_ref_use_xo_END              (20)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_ref_xo_en_START             (21)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_ref_xo_en_END               (21)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_rtune_req_START             (22)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_rtune_req_END               (22)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_test_burnin_START           (23)
#define SOC_USB3OTG_BC_USB3PHY_CTRL_usb3otg_phy_test_burnin_END             (23)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USB3PHY_STS_UNION
 �ṹ˵��  : USB3PHY_STS �Ĵ����ṹ���塣��ַƫ����:0x4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PHY״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usb3otg_phy_ref_clkreq_n : 1;  /* bit[0]   : Reference Clock Removal Acknowledge */
        unsigned int  usb3otg_phy_rtune_ack    : 1;  /* bit[1]   : ����tune��Ӧ */
        unsigned int  hssquelch0               : 1;  /* bit[2]   : HS squelch���ָʾ */
        unsigned int  hsrxdat0                 : 1;  /* bit[3]   : HS�������첽������� */
        unsigned int  reserved                 : 28; /* bit[4-31]:  */
    } reg;
} SOC_USB3OTG_BC_USB3PHY_STS_UNION;
#endif
#define SOC_USB3OTG_BC_USB3PHY_STS_usb3otg_phy_ref_clkreq_n_START  (0)
#define SOC_USB3OTG_BC_USB3PHY_STS_usb3otg_phy_ref_clkreq_n_END    (0)
#define SOC_USB3OTG_BC_USB3PHY_STS_usb3otg_phy_rtune_ack_START     (1)
#define SOC_USB3OTG_BC_USB3PHY_STS_usb3otg_phy_rtune_ack_END       (1)
#define SOC_USB3OTG_BC_USB3PHY_STS_hssquelch0_START                (2)
#define SOC_USB3OTG_BC_USB3PHY_STS_hssquelch0_END                  (2)
#define SOC_USB3OTG_BC_USB3PHY_STS_hsrxdat0_START                  (3)
#define SOC_USB3OTG_BC_USB3PHY_STS_hsrxdat0_END                    (3)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USB3PHY_CR_STS_UNION
 �ṹ˵��  : USB3PHY_CR_STS �Ĵ����ṹ���塣��ַƫ����:0x50����ֵ:0x00000000�����:32
 �Ĵ���˵��: PHY�ڲ��Ĵ���״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usb3otg_phy_cr_ack      : 1;  /* bit[0]    : CR Acknowledgement */
        unsigned int  usb3otg_phy_cr_data_out : 16; /* bit[1-16] : CR Data Output Bus */
        unsigned int  reserved                : 15; /* bit[17-31]:  */
    } reg;
} SOC_USB3OTG_BC_USB3PHY_CR_STS_UNION;
#endif
#define SOC_USB3OTG_BC_USB3PHY_CR_STS_usb3otg_phy_cr_ack_START       (0)
#define SOC_USB3OTG_BC_USB3PHY_CR_STS_usb3otg_phy_cr_ack_END         (0)
#define SOC_USB3OTG_BC_USB3PHY_CR_STS_usb3otg_phy_cr_data_out_START  (1)
#define SOC_USB3OTG_BC_USB3PHY_CR_STS_usb3otg_phy_cr_data_out_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USB3PHY_CR_CTRL_UNION
 �ṹ˵��  : USB3PHY_CR_CTRL �Ĵ����ṹ���塣��ַƫ����:0x54����ֵ:0x00000000�����:32
 �Ĵ���˵��: PHY�ڲ��Ĵ�������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usb3otg_phy_cr_cap_addr : 1;  /* bit[0]    : CR Capture Address */
        unsigned int  usb3otg_phy_cr_cap_data : 1;  /* bit[1]    : CR Capture Data */
        unsigned int  usb3otg_phy_cr_read     : 1;  /* bit[2]    : CR Read */
        unsigned int  usb3otg_phy_cr_write    : 1;  /* bit[3]    : CR Write */
        unsigned int  usb3otg_phy_cr_data_in  : 16; /* bit[4-19] : CR Address and Write Data Input Bus */
        unsigned int  reserved                : 12; /* bit[20-31]:  */
    } reg;
} SOC_USB3OTG_BC_USB3PHY_CR_CTRL_UNION;
#endif
#define SOC_USB3OTG_BC_USB3PHY_CR_CTRL_usb3otg_phy_cr_cap_addr_START  (0)
#define SOC_USB3OTG_BC_USB3PHY_CR_CTRL_usb3otg_phy_cr_cap_addr_END    (0)
#define SOC_USB3OTG_BC_USB3PHY_CR_CTRL_usb3otg_phy_cr_cap_data_START  (1)
#define SOC_USB3OTG_BC_USB3PHY_CR_CTRL_usb3otg_phy_cr_cap_data_END    (1)
#define SOC_USB3OTG_BC_USB3PHY_CR_CTRL_usb3otg_phy_cr_read_START      (2)
#define SOC_USB3OTG_BC_USB3PHY_CR_CTRL_usb3otg_phy_cr_read_END        (2)
#define SOC_USB3OTG_BC_USB3PHY_CR_CTRL_usb3otg_phy_cr_write_START     (3)
#define SOC_USB3OTG_BC_USB3PHY_CR_CTRL_usb3otg_phy_cr_write_END       (3)
#define SOC_USB3OTG_BC_USB3PHY_CR_CTRL_usb3otg_phy_cr_data_in_START   (4)
#define SOC_USB3OTG_BC_USB3PHY_CR_CTRL_usb3otg_phy_cr_data_in_END     (19)


/*****************************************************************************
 �ṹ��    : SOC_USB3OTG_BC_USB3_RES_UNION
 �ṹ˵��  : USB3_RES �Ĵ����ṹ���塣��ַƫ����:0x58����ֵ:0x00000000�����:32
 �Ĵ���˵��: USBԤ���Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usb3_res : 32; /* bit[0-31]: �����Ĵ��� */
    } reg;
} SOC_USB3OTG_BC_USB3_RES_UNION;
#endif
#define SOC_USB3OTG_BC_USB3_RES_usb3_res_START  (0)
#define SOC_USB3OTG_BC_USB3_RES_usb3_res_END    (31)






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

#endif /* end of soc_usb3otg_bc_interface.h */
