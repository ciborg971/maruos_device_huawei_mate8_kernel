/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_nandc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:21
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_NANDC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_NANDC_INTERFACE_H__
#define __SOC_NANDC_INTERFACE_H__

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
/* �Ĵ���˵�������ݶ�д��Ŀ�Ĵ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_DATANUM_UNION */
#define SOC_NANDC_NFC_DATANUM_ADDR(base)              ((base) + (0x00))

/* �Ĵ���˵�����ȴ����ƼĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_WSC_UNION */
#define SOC_NANDC_NFC_WSC_ADDR(base)                  ((base) + (0x04))

/* �Ĵ���˵�����������üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_DEVCFG_UNION */
#define SOC_NANDC_NFC_DEVCFG_ADDR(base)               ((base) + (0x08))

/* �Ĵ���˵�����������üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_CMDCFG_UNION */
#define SOC_NANDC_NFC_CMDCFG_ADDR(base)               ((base) + (0x0C))

/* �Ĵ���˵��������Ĵ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_COM_UNION */
#define SOC_NANDC_NFC_COM_ADDR(base)                  ((base) + (0x10))

/* �Ĵ���˵������λ��ַ���üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_ADDRL_UNION */
#define SOC_NANDC_NFC_ADDRL_ADDR(base)                ((base) + (0x14))

/* �Ĵ���˵������λ��ַ���üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_ADDRH_UNION */
#define SOC_NANDC_NFC_ADDRH_ADDR(base)                ((base) + (0x18))

/* �Ĵ���˵����NANDC buffer���üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_BUFEN_UNION */
#define SOC_NANDC_NFC_BUFEN_ADDR(base)                ((base) + (0x1C))

/* �Ĵ���˵����buffer��д���ƼĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_BUFCTRL_UNION */
#define SOC_NANDC_NFC_BUFCTRL_ADDR(base)              ((base) + (0x20))

/* �Ĵ���˵�����ж�ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_INTEN_UNION */
#define SOC_NANDC_NFC_INTEN_ADDR(base)                ((base) + (0x24))

/* �Ĵ���˵�����ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_INTSTATUS_UNION */
#define SOC_NANDC_NFC_INTSTATUS_ADDR(base)            ((base) + (0x28))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_INTCLR_UNION */
#define SOC_NANDC_NFC_INTCLR_ADDR(base)               ((base) + (0x2C))

/* �Ĵ���˵�����������Ĵ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_STARTRD_UNION */
#define SOC_NANDC_NFC_STARTRD_ADDR(base)              ((base) + (0x30))

/* �Ĵ���˵����cs don��t careģʽʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_CSDNEN_UNION */
#define SOC_NANDC_NFC_CSDNEN_ADDR(base)               ((base) + (0x34))

/* �Ĵ���˵��������ʼ��ַ1���üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_LOCK_SA1_UNION */
#define SOC_NANDC_NFC_LOCK_SA1_ADDR(base)             ((base) + (0x38))

/* �Ĵ���˵�������������ַ���üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_LOCK_ED1_UNION */
#define SOC_NANDC_NFC_LOCK_ED1_ADDR(base)             ((base) + (0x3C))

/* �Ĵ���˵��������ʼ��ַ2���üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_LOCK_SA2_UNION */
#define SOC_NANDC_NFC_LOCK_SA2_ADDR(base)             ((base) + (0x40))

/* �Ĵ���˵�������������ַ���üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_LOCK_ED2_UNION */
#define SOC_NANDC_NFC_LOCK_ED2_ADDR(base)             ((base) + (0x44))

/* �Ĵ���˵��������ʼ��ַ2���üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_LOCK_SA3_UNION */
#define SOC_NANDC_NFC_LOCK_SA3_ADDR(base)             ((base) + (0x48))

/* �Ĵ���˵�������������ַ���üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_LOCK_ED3_UNION */
#define SOC_NANDC_NFC_LOCK_ED3_ADDR(base)             ((base) + (0x4C))

/* �Ĵ���˵��������ʼ��ַ1���üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_LOCK_SA4_UNION */
#define SOC_NANDC_NFC_LOCK_SA4_ADDR(base)             ((base) + (0x50))

/* �Ĵ���˵�������������ַ���üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_LOCK_ED4_UNION */
#define SOC_NANDC_NFC_LOCK_ED4_ADDR(base)             ((base) + (0x54))

/* �Ĵ���˵����Flashlockʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_FLASHLOCK_ENABLE_UNION */
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_ADDR(base)     ((base) + (0x58))

/* �Ĵ���˵����Flashlock���ƼĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_FLASHLOCK_CONTRL_UNION */
#define SOC_NANDC_NFC_FLASHLOCK_CONTRL_ADDR(base)     ((base) + (0x5C))

/* �Ĵ���˵����Flashlock�������üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_FLASHLOCK_COM1_UNION */
#define SOC_NANDC_NFC_FLASHLOCK_COM1_ADDR(base)       ((base) + (0x60))

/* �Ĵ���˵����Flashlock�������üĴ���
   λ����UNION�ṹ:  SOC_NANDC_NFC_FLASHLOCK_COM2_UNION */
#define SOC_NANDC_NFC_FLASHLOCK_COM2_ADDR(base)       ((base) + (0x64))





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
 �ṹ��    : SOC_NANDC_NFC_DATANUM_UNION
 �ṹ˵��  : NFC_DATANUM �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x00000840�����:32
 �Ĵ���˵��: ���ݶ�д��Ŀ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data_num : 12; /* bit[0-11] : ��дbyte����Ŀ��0����д0��byte��
                                                    ȱʡ��д2112 (528*4) byte�� */
        unsigned int  reserved : 20; /* bit[12-31]: ������ */
    } reg;
} SOC_NANDC_NFC_DATANUM_UNION;
#endif
#define SOC_NANDC_NFC_DATANUM_data_num_START  (0)
#define SOC_NANDC_NFC_DATANUM_data_num_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_WSC_UNION
 �ṹ˵��  : NFC_WSC �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x0000F333�����:32
 �Ĵ���˵��: �ȴ����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wt_pulse        : 4;  /* bit[0-3]  : NandFlashд�źŵ͵�ƽ��ȡ�
                                                           4��b0000��һ��ʱ������
                                                           ��
                                                           4��b1111��16��ʱ������ */
        unsigned int  rd_pulse        : 4;  /* bit[4-7]  : NandFlash���źŵ͵�ƽ��ȡ�
                                                           4��b0000��һ��ʱ������
                                                           ��
                                                           4��b1111��16��ʱ������ */
        unsigned int  rdwt_high       : 4;  /* bit[8-11] : NandFlash��/д�źŸߵ�ƽ���
                                                           4��b0001��2��ʱ������
                                                           ��
                                                           4��b1111��16��ʱ������
                                                           ע����������Ϊ0�� */
        unsigned int  wait_busy       : 4;  /* bit[12-15]: NandFlash��������һ����ַ��busy״̬����ʱ��
                                                           4��h0��2��ʱ�����ڡ�
                                                           4��hF��32��ʱ������ */
        unsigned int  cs_wait_wide_wr : 4;  /* bit[16-19]: cs don��t care�����ready/busy�ź����ͺ�cs��Ч���ӳ�ʱ�䣺
                                                           4��h0��0��ʱ�����ڡ�
                                                           4��hF��15��ʱ������ */
        unsigned int  reserved        : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_NANDC_NFC_WSC_UNION;
#endif
#define SOC_NANDC_NFC_WSC_wt_pulse_START         (0)
#define SOC_NANDC_NFC_WSC_wt_pulse_END           (3)
#define SOC_NANDC_NFC_WSC_rd_pulse_START         (4)
#define SOC_NANDC_NFC_WSC_rd_pulse_END           (7)
#define SOC_NANDC_NFC_WSC_rdwt_high_START        (8)
#define SOC_NANDC_NFC_WSC_rdwt_high_END          (11)
#define SOC_NANDC_NFC_WSC_wait_busy_START        (12)
#define SOC_NANDC_NFC_WSC_wait_busy_END          (15)
#define SOC_NANDC_NFC_WSC_cs_wait_wide_wr_START  (16)
#define SOC_NANDC_NFC_WSC_cs_wait_wide_wr_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_DEVCFG_UNION
 �ṹ˵��  : NFC_DEVCFG �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_size : 1;  /* bit[0]   : NandFlash��ҳ��С��
                                                    0��512 byte/page
                                                    1��2K byte/page��
                                                    ��λֵ�ɹܽ�nand_page_sizeȡ������ */
        unsigned int  bus_wide  : 1;  /* bit[1]   : NandFlash�������߿�ȡ�
                                                    0��8bit��1��16bit��
                                                    ��λֵ�ɹܽ�nand_bus_wide������ */
        unsigned int  reserved  : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_NANDC_NFC_DEVCFG_UNION;
#endif
#define SOC_NANDC_NFC_DEVCFG_page_size_START  (0)
#define SOC_NANDC_NFC_DEVCFG_page_size_END    (0)
#define SOC_NANDC_NFC_DEVCFG_bus_wide_START   (1)
#define SOC_NANDC_NFC_DEVCFG_bus_wide_END     (1)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_CMDCFG_UNION
 �ṹ˵��  : NFC_CMDCFG �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_num      : 3;  /* bit[0-2]  : Controller����NandFlash�ĵ�ַ������
                                                         ȱʡֵ�ɹܽ�nand_addr_num[1:0]��������ϵ���¡�
                                                         nand_addr_num��0����address cycles��5��nand_addr_num��1����address cycles��4��nand_addr_num��2����address cycles��3�� */
        unsigned int  reserved_0    : 1;  /* bit[3]    : ���� */
        unsigned int  ca_sequence   : 1;  /* bit[4]    : Controller����NandFlash�������ַ��ʽ
                                                         0�����͡�comand1����ַ��
                                                         1�����͡�comand1����ַ��command2����
                                                         ��λֵ�ɹܽ�nand_page_size������nand_page_size����0����λֵΪ0��nand_page_size����1����λֵΪ1�� */
        unsigned int  com_only      : 1;  /* bit[5]    : 0��Controller���������ַ�󣬸���Controller��ǰ�Ķ�д״̬��������д����״̬����
                                                         1��Controllerֻ���������ַ����������д����״̬���� */
        unsigned int  rdwt_mode     : 1;  /* bit[6]    : 0����NandFlash������
                                                         1����NandFlashд���� */
        unsigned int  busy_not_care : 1;  /* bit[7]    : 0����busy״̬�²�����nand flash�������
                                                         1����busy״̬�¿�����nand flash�������� */
        unsigned int  cs_sel        : 2;  /* bit[8-9]  : CS select��
                                                         00��ѡ��cs0_n��
                                                         01��ѡ��cs1_n��
                                                         10��ѡ��cs2_n��
                                                         11��ѡ��cs3_n�� */
        unsigned int  reserved_1    : 2;  /* bit[10-11]: ���� */
        unsigned int  ebi_n         : 1;  /* bit[12]   : 0��CS don��t careʱEBI�����ͣ�
                                                         1��CS don��t careʱEBIҲ���͡� */
        unsigned int  reserved_2    : 19; /* bit[13-31]: ������ */
    } reg;
} SOC_NANDC_NFC_CMDCFG_UNION;
#endif
#define SOC_NANDC_NFC_CMDCFG_addr_num_START       (0)
#define SOC_NANDC_NFC_CMDCFG_addr_num_END         (2)
#define SOC_NANDC_NFC_CMDCFG_ca_sequence_START    (4)
#define SOC_NANDC_NFC_CMDCFG_ca_sequence_END      (4)
#define SOC_NANDC_NFC_CMDCFG_com_only_START       (5)
#define SOC_NANDC_NFC_CMDCFG_com_only_END         (5)
#define SOC_NANDC_NFC_CMDCFG_rdwt_mode_START      (6)
#define SOC_NANDC_NFC_CMDCFG_rdwt_mode_END        (6)
#define SOC_NANDC_NFC_CMDCFG_busy_not_care_START  (7)
#define SOC_NANDC_NFC_CMDCFG_busy_not_care_END    (7)
#define SOC_NANDC_NFC_CMDCFG_cs_sel_START         (8)
#define SOC_NANDC_NFC_CMDCFG_cs_sel_END           (9)
#define SOC_NANDC_NFC_CMDCFG_ebi_n_START          (12)
#define SOC_NANDC_NFC_CMDCFG_ebi_n_END            (12)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_COM_UNION
 �ṹ˵��  : NFC_COM �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x00003000�����:32
 �Ĵ���˵��: ����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  command1 : 8;  /* bit[0-7]  : Controller����NandFlash�ĵ�һ������ */
        unsigned int  command2 : 8;  /* bit[8-15] : Controller����NandFlash�ĵڶ������� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_NANDC_NFC_COM_UNION;
#endif
#define SOC_NANDC_NFC_COM_command1_START  (0)
#define SOC_NANDC_NFC_COM_command1_END    (7)
#define SOC_NANDC_NFC_COM_command2_START  (8)
#define SOC_NANDC_NFC_COM_command2_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_ADDRL_UNION
 �ṹ˵��  : NFC_ADDRL �Ĵ����ṹ���塣��ַƫ����:0x14����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��λ��ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_l : 32; /* bit[0-31]: NANDFlash��32bit��ַ�� */
    } reg;
} SOC_NANDC_NFC_ADDRL_UNION;
#endif
#define SOC_NANDC_NFC_ADDRL_addr_l_START  (0)
#define SOC_NANDC_NFC_ADDRL_addr_l_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_ADDRH_UNION
 �ṹ˵��  : NFC_ADDRH �Ĵ����ṹ���塣��ַƫ����:0x18����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��λ��ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_h   : 8;  /* bit[0-7] : NANDFlash��16bit��ַ�� */
        unsigned int  reserved : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_NANDC_NFC_ADDRH_UNION;
#endif
#define SOC_NANDC_NFC_ADDRH_addr_h_START    (0)
#define SOC_NANDC_NFC_ADDRH_addr_h_END      (7)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_BUFEN_UNION
 �ṹ˵��  : NFC_BUFEN �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x00000006�����:32
 �Ĵ���˵��: NANDC buffer���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  boot_mode_n     : 1;  /* bit[0]   : 0��NandFlash Controller����bootģʽ��
                                                          1��NandFlash Controller����normalģʽ�� */
        unsigned int  ecc_bypass      : 1;  /* bit[1]   : 0��ECCУ��ʹ�ܡ�1��ECCУ���ֹ�� */
        unsigned int  secc_bypass     : 1;  /* bit[2]   : 0��LSN����ECCУ��ʹ�ܡ�
                                                          1��LSN����ECCУ���ֹ�� */
        unsigned int  ecc_crct_bypass : 1;  /* bit[3]   : 0��ECC 1bit����ʹ�ܡ�
                                                          1��ECC 1bit�����ֹ�� */
        unsigned int  reserved        : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_NANDC_NFC_BUFEN_UNION;
#endif
#define SOC_NANDC_NFC_BUFEN_boot_mode_n_START      (0)
#define SOC_NANDC_NFC_BUFEN_boot_mode_n_END        (0)
#define SOC_NANDC_NFC_BUFEN_ecc_bypass_START       (1)
#define SOC_NANDC_NFC_BUFEN_ecc_bypass_END         (1)
#define SOC_NANDC_NFC_BUFEN_secc_bypass_START      (2)
#define SOC_NANDC_NFC_BUFEN_secc_bypass_END        (2)
#define SOC_NANDC_NFC_BUFEN_ecc_crct_bypass_START  (3)
#define SOC_NANDC_NFC_BUFEN_ecc_crct_bypass_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_BUFCTRL_UNION
 �ṹ˵��  : NFC_BUFCTRL �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x0000000F�����:32
 �Ĵ���˵��: buffer��д���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buffer_ready : 4;  /* bit[0-3] : ÿ��bit��Ӧһ��buffer��
                                                       ������ʱ����NandFlash��ȡ�����ݣ�д����bit0��ʼ����һ��״̬Ϊ1��buffer�������һ��״̬Ϊ1��buffer��
                                                       д����ʱ����bit0��ʼ����һ��bitΪ1��buffer������д��NandFlash */
        unsigned int  reserved     : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_NANDC_NFC_BUFCTRL_UNION;
#endif
#define SOC_NANDC_NFC_BUFCTRL_buffer_ready_START  (0)
#define SOC_NANDC_NFC_BUFCTRL_buffer_ready_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_INTEN_UNION
 �ṹ˵��  : NFC_INTEN �Ĵ����ṹ���塣��ַƫ����:0x24����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cod_done_cs0_en        : 1;  /* bit[0]    : Controller��CS0�����������������͵�ַ��ʹ�ܲ����ж� */
        unsigned int  read_done_cs0_en       : 1;  /* bit[1]    : CS0�������������������ʹ�ܲ����ж� */
        unsigned int  write_done_cs0_en      : 1;  /* bit[2]    : CS0�������д����������ʹ�ܲ����ж� */
        unsigned int  reserved_0             : 1;  /* bit[3]    : ����λ */
        unsigned int  cod_done_cs1_en        : 1;  /* bit[4]    : Controller��CS1�����������������͵�ַ��ʹ�ܲ����ж� */
        unsigned int  read_done_cs1_en       : 1;  /* bit[5]    : CS1�������������������ʹ�ܲ����ж� */
        unsigned int  write_done_cs1_en      : 1;  /* bit[6]    : CS1�������д����������ʹ�ܲ����ж� */
        unsigned int  reserved_1             : 1;  /* bit[7]    : ����λ */
        unsigned int  cod_done_cs2_en        : 1;  /* bit[8]    : Controller��CS2�����������������͵�ַ��ʹ�ܲ����ж� */
        unsigned int  read_done_cs2_en       : 1;  /* bit[9]    : CS2�������������������ʹ�ܲ����ж� */
        unsigned int  write_done_cs2_en      : 1;  /* bit[10]   : CS2�������д����������ʹ�ܲ����ж� */
        unsigned int  reserved_2             : 1;  /* bit[11]   : ����λ */
        unsigned int  cod_done_cs3_en        : 1;  /* bit[12]   : Controller��CS3�����������������͵�ַ��ʹ�ܲ����ж� */
        unsigned int  read_done_cs3_en       : 1;  /* bit[13]   : CS3�������������������ʹ�ܲ����ж� */
        unsigned int  write_done_cs3_en      : 1;  /* bit[14]   : Ecc 2bits ʹ�ܱ����жϣ�
                                                                  ���bit[21]Ϊ1��ָʾ1bit�жϣ���ôbit[14]ͬʱָʾΪ0������������1bit error�жϣ�
                                                                  ���bit[21]Ϊ1��ָʾ1bit�жϣ���bit[14]ҲΪ1����ô����1bit error�����������2bits error����Ϊ1bit error������� */
        unsigned int  reserved_3             : 1;  /* bit[15]   : ���� */
        unsigned int  allbufferready_en      : 1;  /* bit[16]   : ��״̬�£�����buffer������Ч��ʹ�ܲ����ж� */
        unsigned int  buffer1_ready_en       : 1;  /* bit[17]   : ��״̬�£�buffer1������Ч��ʹ�ܲ����жϡ� */
        unsigned int  buffer2_ready_en       : 1;  /* bit[18]   : ��״̬�£�buffer2������Ч��ʹ�ܲ����жϡ� */
        unsigned int  buffer3_ready_en       : 1;  /* bit[19]   : ��״̬�£�buffer3������Ч��ʹ�ܲ����жϡ� */
        unsigned int  buffer4_ready_en       : 1;  /* bit[20]   : ��״̬�£�buffer4������Ч��ʹ�ܲ����ж��źš� */
        unsigned int  data_ecc_1bit_error_en : 1;  /* bit[21]   : eccУ��1bit����ʹ�ܲ����ж��ź� */
        unsigned int  data_ecc_2bit_error_en : 1;  /* bit[22]   : eccУ��2bit���ϳ���ʹ�ܲ����ж��ź� */
        unsigned int  lsn_ecc_1bit_error_en  : 1;  /* bit[23]   : lsn ����eccУ��1bit����ʹ�ܲ����ж��ź� */
        unsigned int  lsn_ecc_2bit_error_en  : 1;  /* bit[24]   : lsn ����eccУ��2bit���ϳ���ʹ�ܲ����ж��ź� */
        unsigned int  flashlock_error_en     : 1;  /* bit[25]   : �Ƿ���дflashlock���ݳ���ʹ�ܲ����ж��ź� */
        unsigned int  reserved_4             : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_NANDC_NFC_INTEN_UNION;
#endif
#define SOC_NANDC_NFC_INTEN_cod_done_cs0_en_START         (0)
#define SOC_NANDC_NFC_INTEN_cod_done_cs0_en_END           (0)
#define SOC_NANDC_NFC_INTEN_read_done_cs0_en_START        (1)
#define SOC_NANDC_NFC_INTEN_read_done_cs0_en_END          (1)
#define SOC_NANDC_NFC_INTEN_write_done_cs0_en_START       (2)
#define SOC_NANDC_NFC_INTEN_write_done_cs0_en_END         (2)
#define SOC_NANDC_NFC_INTEN_cod_done_cs1_en_START         (4)
#define SOC_NANDC_NFC_INTEN_cod_done_cs1_en_END           (4)
#define SOC_NANDC_NFC_INTEN_read_done_cs1_en_START        (5)
#define SOC_NANDC_NFC_INTEN_read_done_cs1_en_END          (5)
#define SOC_NANDC_NFC_INTEN_write_done_cs1_en_START       (6)
#define SOC_NANDC_NFC_INTEN_write_done_cs1_en_END         (6)
#define SOC_NANDC_NFC_INTEN_cod_done_cs2_en_START         (8)
#define SOC_NANDC_NFC_INTEN_cod_done_cs2_en_END           (8)
#define SOC_NANDC_NFC_INTEN_read_done_cs2_en_START        (9)
#define SOC_NANDC_NFC_INTEN_read_done_cs2_en_END          (9)
#define SOC_NANDC_NFC_INTEN_write_done_cs2_en_START       (10)
#define SOC_NANDC_NFC_INTEN_write_done_cs2_en_END         (10)
#define SOC_NANDC_NFC_INTEN_cod_done_cs3_en_START         (12)
#define SOC_NANDC_NFC_INTEN_cod_done_cs3_en_END           (12)
#define SOC_NANDC_NFC_INTEN_read_done_cs3_en_START        (13)
#define SOC_NANDC_NFC_INTEN_read_done_cs3_en_END          (13)
#define SOC_NANDC_NFC_INTEN_write_done_cs3_en_START       (14)
#define SOC_NANDC_NFC_INTEN_write_done_cs3_en_END         (14)
#define SOC_NANDC_NFC_INTEN_allbufferready_en_START       (16)
#define SOC_NANDC_NFC_INTEN_allbufferready_en_END         (16)
#define SOC_NANDC_NFC_INTEN_buffer1_ready_en_START        (17)
#define SOC_NANDC_NFC_INTEN_buffer1_ready_en_END          (17)
#define SOC_NANDC_NFC_INTEN_buffer2_ready_en_START        (18)
#define SOC_NANDC_NFC_INTEN_buffer2_ready_en_END          (18)
#define SOC_NANDC_NFC_INTEN_buffer3_ready_en_START        (19)
#define SOC_NANDC_NFC_INTEN_buffer3_ready_en_END          (19)
#define SOC_NANDC_NFC_INTEN_buffer4_ready_en_START        (20)
#define SOC_NANDC_NFC_INTEN_buffer4_ready_en_END          (20)
#define SOC_NANDC_NFC_INTEN_data_ecc_1bit_error_en_START  (21)
#define SOC_NANDC_NFC_INTEN_data_ecc_1bit_error_en_END    (21)
#define SOC_NANDC_NFC_INTEN_data_ecc_2bit_error_en_START  (22)
#define SOC_NANDC_NFC_INTEN_data_ecc_2bit_error_en_END    (22)
#define SOC_NANDC_NFC_INTEN_lsn_ecc_1bit_error_en_START   (23)
#define SOC_NANDC_NFC_INTEN_lsn_ecc_1bit_error_en_END     (23)
#define SOC_NANDC_NFC_INTEN_lsn_ecc_2bit_error_en_START   (24)
#define SOC_NANDC_NFC_INTEN_lsn_ecc_2bit_error_en_END     (24)
#define SOC_NANDC_NFC_INTEN_flashlock_error_en_START      (25)
#define SOC_NANDC_NFC_INTEN_flashlock_error_en_END        (25)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_INTSTATUS_UNION
 �ṹ˵��  : NFC_INTSTATUS �Ĵ����ṹ���塣��ַƫ����:0x28����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cod_done_cs0        : 1;  /* bit[0]    : Controller��CS0�����������������͵�ַ�󣬲����ж��ź� */
        unsigned int  read_done_cs0       : 1;  /* bit[1]    : CS0������������������������ж� */
        unsigned int  write_done_cs0      : 1;  /* bit[2]    : CS0�������д���������������ж��ź� */
        unsigned int  reserved_0          : 1;  /* bit[3]    : ���� */
        unsigned int  cod_done_cs1        : 1;  /* bit[4]    : Controller��CS1�����������������͵�ַ�󣬲����ж��ź� */
        unsigned int  read_done_cs1       : 1;  /* bit[5]    : CS1������������������������ж��ź� */
        unsigned int  write_done_cs1      : 1;  /* bit[6]    : CS1�������д���������������ж��ź� */
        unsigned int  reserved_1          : 1;  /* bit[7]    : ���� */
        unsigned int  cod_done_cs2        : 1;  /* bit[8]    : Controller��CS2�����������������͵�ַ�󣬲����ж��ź� */
        unsigned int  read_done_cs2       : 1;  /* bit[9]    : CS2������������������������ж��ź� */
        unsigned int  write_done_cs2      : 1;  /* bit[10]   : CS2�������д���������������ж��ź� */
        unsigned int  reserved_2          : 1;  /* bit[11]   : ���� */
        unsigned int  cod_done_cs3        : 1;  /* bit[12]   : Controller��CS3�����������������͵�ַ�󣬲����ж��ź� */
        unsigned int  read_done_cs3       : 1;  /* bit[13]   : CS3������������������������ж��ź� */
        unsigned int  write_done_cs3      : 1;  /* bit[14]   : CS3�������д���������������ж��ź� */
        unsigned int  reserved_3          : 1;  /* bit[15]   : ���� */
        unsigned int  allbufferready      : 1;  /* bit[16]   : ��״̬�£�����buffer������Ч�������ж��ź� */
        unsigned int  buffer1_ready       : 1;  /* bit[17]   : ��״̬�£�buffer1������Ч�������ж��źš� */
        unsigned int  buffer2_ready       : 1;  /* bit[18]   : ��״̬�£�buffer2������Ч�������ж��źš� */
        unsigned int  buffer3_ready       : 1;  /* bit[19]   : ��״̬�£�buffer3������Ч�������ж��źš� */
        unsigned int  buffer4_ready       : 1;  /* bit[20]   : ��״̬�£�buffer4������Ч�������ж��źš� */
        unsigned int  data_ecc_1bit_error : 1;  /* bit[21]   : eccУ��1bit���������ж��ź� */
        unsigned int  data_ecc_2bit_error : 1;  /* bit[22]   : eccУ��2bit���ϳ��������ж��ź� */
        unsigned int  lsn_ecc_1bit_error  : 1;  /* bit[23]   : lsn ����eccУ��1bit���ϳ��������ж��ź� */
        unsigned int  lsn_ecc_2bit_error  : 1;  /* bit[24]   : lsn ����eccУ��2bit���ϳ��������ж��ź� */
        unsigned int  flashlock_error     : 1;  /* bit[25]   : �Ƿ���дflashlock���ݳ��������ж��ź� */
        unsigned int  reserved_4          : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_NANDC_NFC_INTSTATUS_UNION;
#endif
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs0_START         (0)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs0_END           (0)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs0_START        (1)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs0_END          (1)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs0_START       (2)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs0_END         (2)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs1_START         (4)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs1_END           (4)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs1_START        (5)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs1_END          (5)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs1_START       (6)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs1_END         (6)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs2_START         (8)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs2_END           (8)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs2_START        (9)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs2_END          (9)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs2_START       (10)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs2_END         (10)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs3_START         (12)
#define SOC_NANDC_NFC_INTSTATUS_cod_done_cs3_END           (12)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs3_START        (13)
#define SOC_NANDC_NFC_INTSTATUS_read_done_cs3_END          (13)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs3_START       (14)
#define SOC_NANDC_NFC_INTSTATUS_write_done_cs3_END         (14)
#define SOC_NANDC_NFC_INTSTATUS_allbufferready_START       (16)
#define SOC_NANDC_NFC_INTSTATUS_allbufferready_END         (16)
#define SOC_NANDC_NFC_INTSTATUS_buffer1_ready_START        (17)
#define SOC_NANDC_NFC_INTSTATUS_buffer1_ready_END          (17)
#define SOC_NANDC_NFC_INTSTATUS_buffer2_ready_START        (18)
#define SOC_NANDC_NFC_INTSTATUS_buffer2_ready_END          (18)
#define SOC_NANDC_NFC_INTSTATUS_buffer3_ready_START        (19)
#define SOC_NANDC_NFC_INTSTATUS_buffer3_ready_END          (19)
#define SOC_NANDC_NFC_INTSTATUS_buffer4_ready_START        (20)
#define SOC_NANDC_NFC_INTSTATUS_buffer4_ready_END          (20)
#define SOC_NANDC_NFC_INTSTATUS_data_ecc_1bit_error_START  (21)
#define SOC_NANDC_NFC_INTSTATUS_data_ecc_1bit_error_END    (21)
#define SOC_NANDC_NFC_INTSTATUS_data_ecc_2bit_error_START  (22)
#define SOC_NANDC_NFC_INTSTATUS_data_ecc_2bit_error_END    (22)
#define SOC_NANDC_NFC_INTSTATUS_lsn_ecc_1bit_error_START   (23)
#define SOC_NANDC_NFC_INTSTATUS_lsn_ecc_1bit_error_END     (23)
#define SOC_NANDC_NFC_INTSTATUS_lsn_ecc_2bit_error_START   (24)
#define SOC_NANDC_NFC_INTSTATUS_lsn_ecc_2bit_error_END     (24)
#define SOC_NANDC_NFC_INTSTATUS_flashlock_error_START      (25)
#define SOC_NANDC_NFC_INTSTATUS_flashlock_error_END        (25)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_INTCLR_UNION
 �ṹ˵��  : NFC_INTCLR �Ĵ����ṹ���塣��ַƫ����:0x2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  command_done_cs0    : 1;  /* bit[0]    : ���Controller��CS0�����������������͵�ַ��������ж� */
        unsigned int  read_done_cs0       : 1;  /* bit[1]    : ���CS0������������������������ж� */
        unsigned int  write_done_cs0      : 1;  /* bit[2]    : ���CS0�������д����������������ж� */
        unsigned int  reserved_0          : 1;  /* bit[3]    : ����λ */
        unsigned int  command_done_cs1    : 1;  /* bit[4]    : ���Controller��CS1�����������������͵�ַ��������ж� */
        unsigned int  read_done_cs1       : 1;  /* bit[5]    : ���CS1������������������������ж� */
        unsigned int  write_done_cs1      : 1;  /* bit[6]    : ���CS1�������д���������������ж� */
        unsigned int  reserved_1          : 1;  /* bit[7]    : ����λ */
        unsigned int  command_done_cs2    : 1;  /* bit[8]    : ���Controller��CS2�����������������͵�ַ��������ж� */
        unsigned int  read_done_cs2       : 1;  /* bit[9]    : ���CS2������������������������ж� */
        unsigned int  write_done_cs2      : 1;  /* bit[10]   : ���CS2�������д���������������ж� */
        unsigned int  reserved_2          : 1;  /* bit[11]   : ����λ */
        unsigned int  command_done_cs3    : 1;  /* bit[12]   : ���Controller��CS3�����������������͵�ַ��������ж� */
        unsigned int  read_done_cs3       : 1;  /* bit[13]   : ���CS3������������������������ж� */
        unsigned int  write_done_cs3      : 1;  /* bit[14]   : ���Ecc 2bits ����������жϣ�
                                                               ���bit[21]Ϊ1��ָʾ1bit�жϣ���ôbit[14]ͬʱָʾΪ0������������1bit error�жϣ�
                                                               ���bit[21]Ϊ1��ָʾ1bit�жϣ���bit[14]ҲΪ1����ô����1bit error�����������2bits error����Ϊ1bit error������� */
        unsigned int  reserved_3          : 1;  /* bit[15]   : ����λ */
        unsigned int  all_buffer_ready    : 1;  /* bit[16]   : �����״̬�£�����buffer������Ч�������ж� */
        unsigned int  buffer1_ready       : 1;  /* bit[17]   : �����״̬�£�buffer1������Ч�������жϡ�  */
        unsigned int  buffer2_ready       : 1;  /* bit[18]   : �����״̬�£�buffer2������Ч�������жϡ� */
        unsigned int  buffer3_ready       : 1;  /* bit[19]   : �����״̬�£�buffer3������Ч�������жϡ� */
        unsigned int  buffer4_ready       : 1;  /* bit[20]   : �����״̬�£�buffer4������Ч�������ж� */
        unsigned int  data_ecc_1bit_error : 1;  /* bit[21]   : ���eccУ��1bit���ϳ���������ж� */
        unsigned int  data_ecc_2bit_error : 1;  /* bit[22]   : ���eccУ��2bit���ϳ���������ж� */
        unsigned int  lsn_err_1bit_error  : 1;  /* bit[23]   : ���lsn ����eccУ��1bit����������ж� */
        unsigned int  lsn_err_2bit_error  : 1;  /* bit[24]   : ���lsn ����eccУ��2bit���ϳ���������ж� */
        unsigned int  flashlock_error     : 1;  /* bit[25]   : ����Ƿ���дflashlock���ݳ���������ж� */
        unsigned int  reserved_4          : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_NANDC_NFC_INTCLR_UNION;
#endif
#define SOC_NANDC_NFC_INTCLR_command_done_cs0_START     (0)
#define SOC_NANDC_NFC_INTCLR_command_done_cs0_END       (0)
#define SOC_NANDC_NFC_INTCLR_read_done_cs0_START        (1)
#define SOC_NANDC_NFC_INTCLR_read_done_cs0_END          (1)
#define SOC_NANDC_NFC_INTCLR_write_done_cs0_START       (2)
#define SOC_NANDC_NFC_INTCLR_write_done_cs0_END         (2)
#define SOC_NANDC_NFC_INTCLR_command_done_cs1_START     (4)
#define SOC_NANDC_NFC_INTCLR_command_done_cs1_END       (4)
#define SOC_NANDC_NFC_INTCLR_read_done_cs1_START        (5)
#define SOC_NANDC_NFC_INTCLR_read_done_cs1_END          (5)
#define SOC_NANDC_NFC_INTCLR_write_done_cs1_START       (6)
#define SOC_NANDC_NFC_INTCLR_write_done_cs1_END         (6)
#define SOC_NANDC_NFC_INTCLR_command_done_cs2_START     (8)
#define SOC_NANDC_NFC_INTCLR_command_done_cs2_END       (8)
#define SOC_NANDC_NFC_INTCLR_read_done_cs2_START        (9)
#define SOC_NANDC_NFC_INTCLR_read_done_cs2_END          (9)
#define SOC_NANDC_NFC_INTCLR_write_done_cs2_START       (10)
#define SOC_NANDC_NFC_INTCLR_write_done_cs2_END         (10)
#define SOC_NANDC_NFC_INTCLR_command_done_cs3_START     (12)
#define SOC_NANDC_NFC_INTCLR_command_done_cs3_END       (12)
#define SOC_NANDC_NFC_INTCLR_read_done_cs3_START        (13)
#define SOC_NANDC_NFC_INTCLR_read_done_cs3_END          (13)
#define SOC_NANDC_NFC_INTCLR_write_done_cs3_START       (14)
#define SOC_NANDC_NFC_INTCLR_write_done_cs3_END         (14)
#define SOC_NANDC_NFC_INTCLR_all_buffer_ready_START     (16)
#define SOC_NANDC_NFC_INTCLR_all_buffer_ready_END       (16)
#define SOC_NANDC_NFC_INTCLR_buffer1_ready_START        (17)
#define SOC_NANDC_NFC_INTCLR_buffer1_ready_END          (17)
#define SOC_NANDC_NFC_INTCLR_buffer2_ready_START        (18)
#define SOC_NANDC_NFC_INTCLR_buffer2_ready_END          (18)
#define SOC_NANDC_NFC_INTCLR_buffer3_ready_START        (19)
#define SOC_NANDC_NFC_INTCLR_buffer3_ready_END          (19)
#define SOC_NANDC_NFC_INTCLR_buffer4_ready_START        (20)
#define SOC_NANDC_NFC_INTCLR_buffer4_ready_END          (20)
#define SOC_NANDC_NFC_INTCLR_data_ecc_1bit_error_START  (21)
#define SOC_NANDC_NFC_INTCLR_data_ecc_1bit_error_END    (21)
#define SOC_NANDC_NFC_INTCLR_data_ecc_2bit_error_START  (22)
#define SOC_NANDC_NFC_INTCLR_data_ecc_2bit_error_END    (22)
#define SOC_NANDC_NFC_INTCLR_lsn_err_1bit_error_START   (23)
#define SOC_NANDC_NFC_INTCLR_lsn_err_1bit_error_END     (23)
#define SOC_NANDC_NFC_INTCLR_lsn_err_2bit_error_START   (24)
#define SOC_NANDC_NFC_INTCLR_lsn_err_2bit_error_END     (24)
#define SOC_NANDC_NFC_INTCLR_flashlock_error_START      (25)
#define SOC_NANDC_NFC_INTCLR_flashlock_error_END        (25)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_STARTRD_UNION
 �ṹ˵��  : NFC_STARTRD �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  write_only_self_clear : 1;  /* bit[0]   : ����������״̬�� */
        unsigned int  reserved              : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_NANDC_NFC_STARTRD_UNION;
#endif
#define SOC_NANDC_NFC_STARTRD_write_only_self_clear_START  (0)
#define SOC_NANDC_NFC_STARTRD_write_only_self_clear_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_CSDNEN_UNION
 �ṹ˵��  : NFC_CSDNEN �Ĵ����ṹ���塣��ַƫ����:0x34����ֵ:0x00000000�����:32
 �Ĵ���˵��: cs don��t careģʽʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csdnen   : 1;  /* bit[0]   : ʹ��nand flash controller��cs don��t care����ģʽ */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_NANDC_NFC_CSDNEN_UNION;
#endif
#define SOC_NANDC_NFC_CSDNEN_csdnen_START    (0)
#define SOC_NANDC_NFC_CSDNEN_csdnen_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_LOCK_SA1_UNION
 �ṹ˵��  : NFC_LOCK_SA1 �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʼ��ַ1���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_start_addr1 : 26; /* bit[0-25] : ��ʾflashlock��ʼ��ַ����2���ر�ʾflashƬѡ����24���ر�ʾnandflash��row��ַ */
        unsigned int  reserved              : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_NANDC_NFC_LOCK_SA1_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_SA1_flashlock_start_addr1_START  (0)
#define SOC_NANDC_NFC_LOCK_SA1_flashlock_start_addr1_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_LOCK_ED1_UNION
 �ṹ˵��  : NFC_LOCK_ED1 �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���������ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_end_addr1 : 26; /* bit[0-25] : ��ʾflashlock��ʼ��ַ����2���ر�ʾflashƬѡ����24���ر�ʾnandflash��row��ַ */
        unsigned int  reserved            : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_NANDC_NFC_LOCK_ED1_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_ED1_flashlock_end_addr1_START  (0)
#define SOC_NANDC_NFC_LOCK_ED1_flashlock_end_addr1_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_LOCK_SA2_UNION
 �ṹ˵��  : NFC_LOCK_SA2 �Ĵ����ṹ���塣��ַƫ����:0x40����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʼ��ַ2���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_start_addr2 : 26; /* bit[0-25] : ��ʾflashlock��ʼ��ַ����2���ر�ʾflashƬѡ����24���ر�ʾnandflash��row��ַ */
        unsigned int  reserved              : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_NANDC_NFC_LOCK_SA2_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_SA2_flashlock_start_addr2_START  (0)
#define SOC_NANDC_NFC_LOCK_SA2_flashlock_start_addr2_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_LOCK_ED2_UNION
 �ṹ˵��  : NFC_LOCK_ED2 �Ĵ����ṹ���塣��ַƫ����:0x44����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���������ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_end_addr2 : 26; /* bit[0-25] : ��ʾflashlock��ʼ��ַ����2���ر�ʾflashƬѡ����24���ر�ʾnandflash��row��ַ */
        unsigned int  reserved            : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_NANDC_NFC_LOCK_ED2_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_ED2_flashlock_end_addr2_START  (0)
#define SOC_NANDC_NFC_LOCK_ED2_flashlock_end_addr2_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_LOCK_SA3_UNION
 �ṹ˵��  : NFC_LOCK_SA3 �Ĵ����ṹ���塣��ַƫ����:0x48����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʼ��ַ2���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_start_addr3 : 26; /* bit[0-25] : ��ʾflashlock��ʼ��ַ����2���ر�ʾflashƬѡ����24���ر�ʾnandflash��row��ַ */
        unsigned int  reserved              : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_NANDC_NFC_LOCK_SA3_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_SA3_flashlock_start_addr3_START  (0)
#define SOC_NANDC_NFC_LOCK_SA3_flashlock_start_addr3_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_LOCK_ED3_UNION
 �ṹ˵��  : NFC_LOCK_ED3 �Ĵ����ṹ���塣��ַƫ����:0x4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���������ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_end_addr3 : 26; /* bit[0-25] : ��ʾflashlock��ʼ��ַ����2���ر�ʾflashƬѡ����24���ر�ʾnandflash��row��ַ */
        unsigned int  reserved            : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_NANDC_NFC_LOCK_ED3_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_ED3_flashlock_end_addr3_START  (0)
#define SOC_NANDC_NFC_LOCK_ED3_flashlock_end_addr3_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_LOCK_SA4_UNION
 �ṹ˵��  : NFC_LOCK_SA4 �Ĵ����ṹ���塣��ַƫ����:0x50����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʼ��ַ1���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_start_addr4 : 26; /* bit[0-25] : ��ʾflashlock��ʼ��ַ����2���ر�ʾflashƬѡ����24���ر�ʾnandflash��row��ַ */
        unsigned int  reserved              : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_NANDC_NFC_LOCK_SA4_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_SA4_flashlock_start_addr4_START  (0)
#define SOC_NANDC_NFC_LOCK_SA4_flashlock_start_addr4_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_LOCK_ED4_UNION
 �ṹ˵��  : NFC_LOCK_ED4 �Ĵ����ṹ���塣��ַƫ����:0x54����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���������ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_end_addr4 : 26; /* bit[0-25] : ��ʾflashlock��ʼ��ַ����2���ر�ʾflashƬѡ����24���ر�ʾnandflash��row��ַ */
        unsigned int  reserved            : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_NANDC_NFC_LOCK_ED4_UNION;
#endif
#define SOC_NANDC_NFC_LOCK_ED4_flashlock_end_addr4_START  (0)
#define SOC_NANDC_NFC_LOCK_ED4_flashlock_end_addr4_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_FLASHLOCK_ENABLE_UNION
 �ṹ˵��  : NFC_FLASHLOCK_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x58����ֵ:0x00000003�����:32
 �Ĵ���˵��: Flashlockʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashlock_whole_enable : 1;  /* bit[0]   : flashlockȫ��ʹ��/ȥʹ�ܣ�Ĭ��flashlockȫ��ʹ��. */
        unsigned int  flashlock_enable       : 1;  /* bit[1]   : ��ʾflashlockʹ��/ȥʹ�ܣ�Ĭ��flashlockʹ��. */
        unsigned int  reserved               : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_NANDC_NFC_FLASHLOCK_ENABLE_UNION;
#endif
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_flashlock_whole_enable_START  (0)
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_flashlock_whole_enable_END    (0)
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_flashlock_enable_START        (1)
#define SOC_NANDC_NFC_FLASHLOCK_ENABLE_flashlock_enable_END          (1)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_FLASHLOCK_CONTRL_UNION
 �ṹ˵��  : NFC_FLASHLOCK_CONTRL �Ĵ����ṹ���塣��ַƫ����:0x5C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Flashlock���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flashloc_control : 1;  /* bit[0]   : ��ʾflashlockģʽ��
                                                           0��ʾ��lockģʽ��
                                                           1��ʾ��lock-downģʽ
                                                           �ñ���һ����д1���� */
        unsigned int  reserved         : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_NANDC_NFC_FLASHLOCK_CONTRL_UNION;
#endif
#define SOC_NANDC_NFC_FLASHLOCK_CONTRL_flashloc_control_START  (0)
#define SOC_NANDC_NFC_FLASHLOCK_CONTRL_flashloc_control_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_FLASHLOCK_COM1_UNION
 �ṹ˵��  : NFC_FLASHLOCK_COM1 �Ĵ����ṹ���塣��ַƫ����:0x60����ֵ:0x85816060�����:32
 �Ĵ���˵��: Flashlock�������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  block_command1 : 8;  /* bit[0-7]  : ��ʾflashlock block��������Ĵ���1 */
        unsigned int  block_command2 : 8;  /* bit[8-15] : ��ʾflashlock block��������Ĵ���2 */
        unsigned int  page_command1  : 8;  /* bit[16-23]: ��ʾflashlock page��������Ĵ���1 */
        unsigned int  page_command2  : 8;  /* bit[24-31]: ��ʾflashlock page��������Ĵ���2 */
    } reg;
} SOC_NANDC_NFC_FLASHLOCK_COM1_UNION;
#endif
#define SOC_NANDC_NFC_FLASHLOCK_COM1_block_command1_START  (0)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_block_command1_END    (7)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_block_command2_START  (8)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_block_command2_END    (15)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_page_command1_START   (16)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_page_command1_END     (23)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_page_command2_START   (24)
#define SOC_NANDC_NFC_FLASHLOCK_COM1_page_command2_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_NANDC_NFC_FLASHLOCK_COM2_UNION
 �ṹ˵��  : NFC_FLASHLOCK_COM2 �Ĵ����ṹ���塣��ַƫ����:0x64����ֵ:0x85858585�����:32
 �Ĵ���˵��: Flashlock�������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_command3 : 8;  /* bit[0-7]  : ��ʾflashlock page��������Ĵ���3 */
        unsigned int  page_command4 : 8;  /* bit[8-15] : ��ʾflashlock page��������Ĵ���4 */
        unsigned int  page_command5 : 8;  /* bit[16-23]: ��ʾflashlock page��������Ĵ���5 */
        unsigned int  page_command6 : 8;  /* bit[24-31]: ��ʾflashlock page��������Ĵ���6 */
    } reg;
} SOC_NANDC_NFC_FLASHLOCK_COM2_UNION;
#endif
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command3_START  (0)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command3_END    (7)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command4_START  (8)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command4_END    (15)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command5_START  (16)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command5_END    (23)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command6_START  (24)
#define SOC_NANDC_NFC_FLASHLOCK_COM2_page_command6_END    (31)






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

#endif /* end of soc_nandc_interface.h */
