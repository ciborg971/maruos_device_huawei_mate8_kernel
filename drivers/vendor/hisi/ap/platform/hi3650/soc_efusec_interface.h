/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_efusec_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:27
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_EFUSEC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_EFUSEC_INTERFACE_H__
#define __SOC_EFUSEC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) EFUSEC
 ****************************************************************************/
/* �Ĵ���˵�������üĴ���������ʹ�ܶ�/��д���̣��������ʱ���߼��Զ���RDn���Ϊ0������д���ʱ���߼��Զ���PGEn���Ϊ0��.
   λ����UNION�ṹ:  SOC_EFUSEC_CFG_UNION */
#define SOC_EFUSEC_CFG_ADDR(base)                     ((base) + (0x000))

/* �Ĵ���˵����״̬�Ĵ��������ڱ�����/��д״̬
   λ����UNION�ṹ:  SOC_EFUSEC_STATUS_UNION */
#define SOC_EFUSEC_STATUS_ADDR(base)                  ((base) + (0x004))

/* �Ĵ���˵������ȡ/��д��ַ�Ĵ�������eufse���飬ÿ��Ϊ32bit����efuse������д���߶�ȡ��ʱ����һ��groupΪ��λ
   λ����UNION�ṹ:  SOC_EFUSEC_EFUSE_GROUP_UNION */
#define SOC_EFUSEC_EFUSE_GROUP_ADDR(base)             ((base) + (0x008))

/* �Ĵ���˵����ÿ�ε���дֵ�Ĵ���
   λ����UNION�ṹ:  SOC_EFUSEC_PG_VALUE_UNION */
#define SOC_EFUSEC_PG_VALUE_ADDR(base)                ((base) + (0x00C))

/* �Ĵ���˵����efuse�ڲ�״̬��ת������ֵ�Ĵ�����ͬʱ��ֵ����4��Ϊefuse�������ڼ�strobe�ź������ȼ���ֵ
   λ����UNION�ṹ:  SOC_EFUSEC_COUNT_UNION */
#define SOC_EFUSEC_COUNT_ADDR(base)                   ((base) + (0x010))

/* �Ĵ���˵����һ����д�ڼ�strobe�ź�����ʱ�������
   λ����UNION�ṹ:  SOC_EFUSEC_PGM_COUNT_UNION */
#define SOC_EFUSEC_PGM_COUNT_ADDR(base)               ((base) + (0x014))

/* �Ĵ���˵������������efuse��ȡ�����ݼĴ���
   λ����UNION�ṹ:  SOC_EFUSEC_DATA_UNION */
#define SOC_EFUSEC_DATA_ADDR(base)                    ((base) + (0x018))

/* �Ĵ���˵�������efuse�ϵ�⸴λ���group==127��ȡ�����ݼĴ��������������жϵȡ���ʼֵ���û�ͨ��efuse��дȷ��
   λ����UNION�ṹ:  SOC_EFUSEC_HW_CFG_UNION */
#define SOC_EFUSEC_HW_CFG_ADDR(base)                  ((base) + (0x01C))





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
                     (1/1) EFUSEC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_EFUSEC_CFG_UNION
 �ṹ˵��  : CFG �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���üĴ���������ʹ�ܶ�/��д���̣��������ʱ���߼��Զ���RDn���Ϊ0������д���ʱ���߼��Զ���PGEn���Ϊ0��.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pgen     : 1;  /* bit[0]   : ��дʹ���źţ���һ����д��ɺ��߼�����Ϊ�Զ�����
                                                   0����ʹ��
                                                   1��ʹ�� */
        unsigned int  pre_pg   : 1;  /* bit[1]   : Ԥ��дʹ���źţ�ʹ�ܺ�Ӳ������PGENB�ź�
                                                   0����ʹ��
                                                   1��ʹ�� */
        unsigned int  rden     : 1;  /* bit[2]   : ��ʹ���źţ���һ�ζ���ɺ��߼�����Ϊ�Զ�����
                                                   0����ʹ��
                                                   1��ʹ�� */
        unsigned int  aib_sel  : 1;  /* bit[3]   : AIB�ӿ�ѡ���ź�
                                                   0��ѡ��AIB����efuse������
                                                   1��ѡ��APB����efuse������ */
        unsigned int  reserved_0: 1;  /* bit[4]   : ���� */
        unsigned int  pd_en    : 1;  /* bit[5]   : efuse power-down����
                                                   0����ʹ��
                                                   1��ʹ�� */
        unsigned int  reserved_1: 26; /* bit[6-31]: ���� */
    } reg;
} SOC_EFUSEC_CFG_UNION;
#endif
#define SOC_EFUSEC_CFG_pgen_START      (0)
#define SOC_EFUSEC_CFG_pgen_END        (0)
#define SOC_EFUSEC_CFG_pre_pg_START    (1)
#define SOC_EFUSEC_CFG_pre_pg_END      (1)
#define SOC_EFUSEC_CFG_rden_START      (2)
#define SOC_EFUSEC_CFG_rden_END        (2)
#define SOC_EFUSEC_CFG_aib_sel_START   (3)
#define SOC_EFUSEC_CFG_aib_sel_END     (3)
#define SOC_EFUSEC_CFG_pd_en_START     (5)
#define SOC_EFUSEC_CFG_pd_en_END       (5)


/*****************************************************************************
 �ṹ��    : SOC_EFUSEC_STATUS_UNION
 �ṹ˵��  : STATUS �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: ״̬�Ĵ��������ڱ�����/��д״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg_status    : 1;  /* bit[0]   : ��д״̬��
                                                       0��δ���
                                                       1����� */
        unsigned int  rd_status    : 1;  /* bit[1]   : efuse��״̬
                                                       0��δ���
                                                       1�����һ�ζ����� */
        unsigned int  pgenb_status : 1;  /* bit[2]   : Ԥ��д��λ���״̬
                                                       0��δ���
                                                       1�����Ԥ��д��λ״̬ */
        unsigned int  rd_error     : 1;  /* bit[3]   : efuse��ǰgroup��ַ�Ƿ��ǽ�ֹ��
                                                       0����
                                                       1���� */
        unsigned int  pd_status    : 1;  /* bit[4]   : power-down״̬
                                                       0������״̬
                                                       1��power-down״̬ */
        unsigned int  reserved     : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_EFUSEC_STATUS_UNION;
#endif
#define SOC_EFUSEC_STATUS_pg_status_START     (0)
#define SOC_EFUSEC_STATUS_pg_status_END       (0)
#define SOC_EFUSEC_STATUS_rd_status_START     (1)
#define SOC_EFUSEC_STATUS_rd_status_END       (1)
#define SOC_EFUSEC_STATUS_pgenb_status_START  (2)
#define SOC_EFUSEC_STATUS_pgenb_status_END    (2)
#define SOC_EFUSEC_STATUS_rd_error_START      (3)
#define SOC_EFUSEC_STATUS_rd_error_END        (3)
#define SOC_EFUSEC_STATUS_pd_status_START     (4)
#define SOC_EFUSEC_STATUS_pd_status_END       (4)


/*****************************************************************************
 �ṹ��    : SOC_EFUSEC_EFUSE_GROUP_UNION
 �ṹ˵��  : EFUSE_GROUP �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȡ/��д��ַ�Ĵ�������eufse���飬ÿ��Ϊ32bit����efuse������д���߶�ȡ��ʱ����һ��groupΪ��λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efuse_group : 7;  /* bit[0-6] : ��ȡ/��д��ַgroup, */
        unsigned int  reserved    : 25; /* bit[7-31]: ���� */
    } reg;
} SOC_EFUSEC_EFUSE_GROUP_UNION;
#endif
#define SOC_EFUSEC_EFUSE_GROUP_efuse_group_START  (0)
#define SOC_EFUSEC_EFUSE_GROUP_efuse_group_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_EFUSEC_PG_VALUE_UNION
 �ṹ˵��  : PG_VALUE �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ÿ�ε���дֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg_value : 32; /* bit[0-31]: һ��32bit����д��Ϣ
                                                   0������д��bit��
                                                   1����д��bit�� */
    } reg;
} SOC_EFUSEC_PG_VALUE_UNION;
#endif
#define SOC_EFUSEC_PG_VALUE_pg_value_START  (0)
#define SOC_EFUSEC_PG_VALUE_pg_value_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_EFUSEC_COUNT_UNION
 �ṹ˵��  : COUNT �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: efuse�ڲ�״̬��ת������ֵ�Ĵ�����ͬʱ��ֵ����4��Ϊefuse�������ڼ�strobe�ź������ȼ���ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efusec_count : 8;  /* bit[0-7] : EFUSE�ڲ�״̬��תʹ�õļ���ֵ */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_EFUSEC_COUNT_UNION;
#endif
#define SOC_EFUSEC_COUNT_efusec_count_START  (0)
#define SOC_EFUSEC_COUNT_efusec_count_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_EFUSEC_PGM_COUNT_UNION
 �ṹ˵��  : PGM_COUNT �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: һ����д�ڼ�strobe�ź�����ʱ�������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pgm_count : 16; /* bit[0-15] : һ����д�ڼ�strobe�ź�����ʱ����������Բο�ʱ��Ϊ����ʱ�ӣ� */
        unsigned int  reserved  : 16; /* bit[16-31]:  */
    } reg;
} SOC_EFUSEC_PGM_COUNT_UNION;
#endif
#define SOC_EFUSEC_PGM_COUNT_pgm_count_START  (0)
#define SOC_EFUSEC_PGM_COUNT_pgm_count_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_EFUSEC_DATA_UNION
 �ṹ˵��  : DATA �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��������efuse��ȡ�����ݼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efuse_data : 32; /* bit[0-31]: ��������efuse��ȡ������ */
    } reg;
} SOC_EFUSEC_DATA_UNION;
#endif
#define SOC_EFUSEC_DATA_efuse_data_START  (0)
#define SOC_EFUSEC_DATA_efuse_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_EFUSEC_HW_CFG_UNION
 �ṹ˵��  : HW_CFG �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���efuse�ϵ�⸴λ���group==127��ȡ�����ݼĴ��������������жϵȡ���ʼֵ���û�ͨ��efuse��дȷ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efusec_hw_cfg : 32; /* bit[0-31]: ���efuse�ϵ�⸴λ���group==15��ȡ�����ݣ���ϸ��Ϣ��EFUSE��Ϣ�Ų��� */
    } reg;
} SOC_EFUSEC_HW_CFG_UNION;
#endif
#define SOC_EFUSEC_HW_CFG_efusec_hw_cfg_START  (0)
#define SOC_EFUSEC_HW_CFG_efusec_hw_cfg_END    (31)






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

#endif /* end of soc_efusec_interface.h */
