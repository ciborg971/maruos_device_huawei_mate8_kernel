/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_asc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:18:04
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ASC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ASC_INTERFACE_H__
#define __SOC_ASC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_ASC
 ****************************************************************************/
/* �Ĵ���˵����ASCģ��ʹ��/Bypass�Ĵ�����
   λ����UNION�ṹ:  SOC_ASC_EN_UNION */
#define SOC_ASC_EN_ADDR(base)                         ((base) + (0x000))

/* �Ĵ���˵����regioni��ȫ����Ȩ�����üĴ�����
   λ����UNION�ṹ:  SOC_ASC_REGION_NON_SECURE_UNION */
#define SOC_ASC_REGION_NON_SECURE_ADDR(base, i)       ((base) + (0x010+0x20*(i)))

/* �Ĵ���˵����regioni��ʼ��ַ��λ�Ĵ�����
   λ����UNION�ṹ:  SOC_ASC_REGION_START_ADDR_LOW_UNION */
#define SOC_ASC_REGION_START_ADDR_LOW_ADDR(base, i)   ((base) + (0x014+0x20*(i)))

/* �Ĵ���˵����regioni��ʼ��ַ��λ�Ĵ�����
   λ����UNION�ṹ:  SOC_ASC_REGION_START_ADDR_HIGH_UNION */
#define SOC_ASC_REGION_START_ADDR_HIGH_ADDR(base, i)  ((base) + (0x018+0x20*(i)))

/* �Ĵ���˵����regioni������ַ��32λ�Ĵ�����
   λ����UNION�ṹ:  SOC_ASC_REGION_END_ADDR_LOW_UNION */
#define SOC_ASC_REGION_END_ADDR_LOW_ADDR(base, i)     ((base) + (0x01C+0x20*(i)))

/* �Ĵ���˵����regioni������ַ��λ�Ĵ�����
   λ����UNION�ṹ:  SOC_ASC_REGION_END_ADDR_HIGH_UNION */
#define SOC_ASC_REGION_END_ADDR_HIGH_ADDR(base, i)    ((base) + (0x020+0x20*(i)))

/* �Ĵ���˵�����ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_ASC_INT_STATUS_UNION */
#define SOC_ASC_INT_STATUS_ADDR(base)                 ((base) + (0x120))

/* �Ĵ���˵�����ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_ASC_INT_CLEAR_UNION */
#define SOC_ASC_INT_CLEAR_ADDR(base)                  ((base) + (0x124))

/* �Ĵ���˵����ԽȨ������ַ��λ�Ĵ�����
   λ����UNION�ṹ:  SOC_ASC_FAIL_ADDR_LOW_UNION */
#define SOC_ASC_FAIL_ADDR_LOW_ADDR(base)              ((base) + (0x128))

/* �Ĵ���˵����ԽȨ������ַ��λ�Ĵ�����
   λ����UNION�ṹ:  SOC_ASC_FAIL_ADDR_HIGH_UNION */
#define SOC_ASC_FAIL_ADDR_HIGH_ADDR(base)             ((base) + (0x12C))

/* �Ĵ���˵����ԽȨ����ID�Ĵ�����
   λ����UNION�ṹ:  SOC_ASC_FAIL_ID_UNION */
#define SOC_ASC_FAIL_ID_ADDR(base)                    ((base) + (0x130))

/* �Ĵ���˵����ԽȨ�������ͼĴ�����
   λ����UNION�ṹ:  SOC_ASC_FAIL_INFO_UNION */
#define SOC_ASC_FAIL_INFO_ADDR(base)                  ((base) + (0x134))





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
                     (1/1) register_ASC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ASC_EN_UNION
 �ṹ˵��  : EN �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASCģ��ʹ��/Bypass�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asc_en   : 1;  /* bit[0]   : 0-asc bypass��default��
                                                   1-asc enable��
                                                   ASC Bypassģʽ�£�ASCģ���AXI Master�ӿں�AXI Slave�ӿ���ֱͨ�ġ�
                                                   ASC Enableģʽ�£�ASCģ����鵱ǰ��д��ַ���Ӧ��PROT[1]�ź��Ƿ���Region0~Region7�ĵ�ַ�Ͱ�ȫ����ƥ�䣬��ƥ�䣬��AXI slave�ӿ��ź�͸������Ӧ��AXI Master�ӿ��źš�����ƥ�䣬����ݷ������ͽ�WSTRB��Ϊȫ�㣬�򽫶�������Ϊȫ�㣬������ERROR��Ӧ���ϱ��жϡ� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_ASC_EN_UNION;
#endif
#define SOC_ASC_EN_asc_en_START    (0)
#define SOC_ASC_EN_asc_en_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_ASC_REGION_NON_SECURE_UNION
 �ṹ˵��  : REGION_NON_SECURE �Ĵ����ṹ���塣��ַƫ����:0x010+0x20*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: regioni��ȫ����Ȩ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  region_non_secure : 1;  /* bit[0]   : regioni��ȫ����Ȩ�����á�
                                                            0-regioni������ȫ���ʡ�
                                                            1-regioni����ȫ���ʺͷǰ�ȫ���ʡ� */
        unsigned int  reserved          : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_ASC_REGION_NON_SECURE_UNION;
#endif
#define SOC_ASC_REGION_NON_SECURE_region_non_secure_START  (0)
#define SOC_ASC_REGION_NON_SECURE_region_non_secure_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASC_REGION_START_ADDR_LOW_UNION
 �ṹ˵��  : REGION_START_ADDR_LOW �Ĵ����ṹ���塣��ַƫ����:0x014+0x20*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: regioni��ʼ��ַ��λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved              : 12; /* bit[0-11] : ������ */
        unsigned int  region_start_addr_low : 20; /* bit[12-31]: regioni��ʼ��ַ��bit[31:12]��
                                                                 Region��ĩ��ַ����С��������Ϊ4KB����ˣ���ʼ��ַ�ĵ�λbit[11:0]��ASCģ���ڲ�����Ϊ0x000��������ַ�ĵ�λbit[11:0]��ASC�ڲ�����Ϊ0xFFF�� */
    } reg;
} SOC_ASC_REGION_START_ADDR_LOW_UNION;
#endif
#define SOC_ASC_REGION_START_ADDR_LOW_region_start_addr_low_START  (12)
#define SOC_ASC_REGION_START_ADDR_LOW_region_start_addr_low_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASC_REGION_START_ADDR_HIGH_UNION
 �ṹ˵��  : REGION_START_ADDR_HIGH �Ĵ����ṹ���塣��ַƫ����:0x018+0x20*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: regioni��ʼ��ַ��λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  region_start_addr_high : 32; /* bit[0-31]: regioni��ʼ��ַ�ĸ�λ�� */
    } reg;
} SOC_ASC_REGION_START_ADDR_HIGH_UNION;
#endif
#define SOC_ASC_REGION_START_ADDR_HIGH_region_start_addr_high_START  (0)
#define SOC_ASC_REGION_START_ADDR_HIGH_region_start_addr_high_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASC_REGION_END_ADDR_LOW_UNION
 �ṹ˵��  : REGION_END_ADDR_LOW �Ĵ����ṹ���塣��ַƫ����:0x01C+0x20*(i)����ֵ:0x00000FFF�����:32
 �Ĵ���˵��: regioni������ַ��32λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved            : 12; /* bit[0-11] : ������ */
        unsigned int  region_end_addr_low : 20; /* bit[12-31]: regioni������ַ��bit[31:0]��
                                                               Region��ĩ��ַ����С��������Ϊ4KB����ˣ���ʼ��ַ�ĵ�λbit[11:0]��ASCģ���ڲ�����Ϊ0x000��������ַ�ĵ�λbit[11:0]��ASC�ڲ�����Ϊ0xFFF�� */
    } reg;
} SOC_ASC_REGION_END_ADDR_LOW_UNION;
#endif
#define SOC_ASC_REGION_END_ADDR_LOW_region_end_addr_low_START  (12)
#define SOC_ASC_REGION_END_ADDR_LOW_region_end_addr_low_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASC_REGION_END_ADDR_HIGH_UNION
 �ṹ˵��  : REGION_END_ADDR_HIGH �Ĵ����ṹ���塣��ַƫ����:0x020+0x20*(i)����ֵ:0x00000000�����:32
 �Ĵ���˵��: regioni������ַ��λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  region_end_addr_high : 32; /* bit[0-31]: regioni������ַ�ĸ�λ���֡� */
    } reg;
} SOC_ASC_REGION_END_ADDR_HIGH_UNION;
#endif
#define SOC_ASC_REGION_END_ADDR_HIGH_region_end_addr_high_START  (0)
#define SOC_ASC_REGION_END_ADDR_HIGH_region_end_addr_high_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASC_INT_STATUS_UNION
 �ṹ˵��  : INT_STATUS �Ĵ����ṹ���塣��ַƫ����:0x120����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_status : 1;  /* bit[0]   : 0-���жϡ�
                                                     1-ԽȨ�����жϡ����ǰ�ȫ�������ʽ�����ȫ���ʵ�regionʱ�����ж���Ч�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_ASC_INT_STATUS_UNION;
#endif
#define SOC_ASC_INT_STATUS_int_status_START  (0)
#define SOC_ASC_INT_STATUS_int_status_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASC_INT_CLEAR_UNION
 �ṹ˵��  : INT_CLEAR �Ĵ����ṹ���塣��ַƫ����:0x124����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_clear : 1;  /* bit[0]   : д1�����Ӧ�жϡ�д0��Ӱ�졣�����Ƿ���0x0�� */
        unsigned int  reserved  : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_ASC_INT_CLEAR_UNION;
#endif
#define SOC_ASC_INT_CLEAR_int_clear_START  (0)
#define SOC_ASC_INT_CLEAR_int_clear_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASC_FAIL_ADDR_LOW_UNION
 �ṹ˵��  : FAIL_ADDR_LOW �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԽȨ������ַ��λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fail_addr_low : 32; /* bit[0-31]: ����ԽȨ�����ķ��ʵ�ַ�ĵ�bit[31:0]�� */
    } reg;
} SOC_ASC_FAIL_ADDR_LOW_UNION;
#endif
#define SOC_ASC_FAIL_ADDR_LOW_fail_addr_low_START  (0)
#define SOC_ASC_FAIL_ADDR_LOW_fail_addr_low_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASC_FAIL_ADDR_HIGH_UNION
 �ṹ˵��  : FAIL_ADDR_HIGH �Ĵ����ṹ���塣��ַƫ����:0x12C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԽȨ������ַ��λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fail_addr_high : 32; /* bit[0-31]: ����ԽȨ�����ķ��ʵ�ַ�ĸ�λ���֡� */
    } reg;
} SOC_ASC_FAIL_ADDR_HIGH_UNION;
#endif
#define SOC_ASC_FAIL_ADDR_HIGH_fail_addr_high_START  (0)
#define SOC_ASC_FAIL_ADDR_HIGH_fail_addr_high_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASC_FAIL_ID_UNION
 �ṹ˵��  : FAIL_ID �Ĵ����ṹ���塣��ַƫ����:0x130����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԽȨ����ID�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fail_id  : 24; /* bit[0-23] : ����ԽȨ������IDֵ�� */
        unsigned int  reserved : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_ASC_FAIL_ID_UNION;
#endif
#define SOC_ASC_FAIL_ID_fail_id_START   (0)
#define SOC_ASC_FAIL_ID_fail_id_END     (23)


/*****************************************************************************
 �ṹ��    : SOC_ASC_FAIL_INFO_UNION
 �ṹ˵��  : FAIL_INFO �Ĵ����ṹ���塣��ַƫ����:0x134����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԽȨ�������ͼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fail_wr    : 1;  /* bit[0]    : ����ԽȨд������
                                                      0-û��ԽȨд���ʡ�
                                                      1-����ԽȨд���ʡ� */
        unsigned int  fail_rd    : 1;  /* bit[1]    : ����ԽȨ��������
                                                      0-û��ԽȨ�����ʡ�
                                                      1-����ԽȨ�����ʡ� */
        unsigned int  fail_len   : 4;  /* bit[2-5]  : ����ԽȨ������LEN�ź�ֵ��
                                                      �����ԽȨ������������AXI SLAVE�ӿڵ�ARLEN�ź�ֵ��
                                                      �����ԽȨд����������AXI SLAVE�ӿڵ�AWLEN�ź�ֵ�� */
        unsigned int  fail_size  : 3;  /* bit[6-8]  : ����ԽȨ������SIZE�ź�ֵ��
                                                      �����ԽȨ������������AXI SLAVE�ӿڵ�ARSIZE�ź�ֵ��
                                                      �����ԽȨд����������AXI SLAVE�ӿڵ�AWSIZE�ź�ֵ�� */
        unsigned int  fail_burst : 2;  /* bit[9-10] : ����ԽȨ������BURST�ź�ֵ��
                                                      �����ԽȨ������������AXI SLAVE�ӿڵ�ARBURST�ź�ֵ��
                                                      �����ԽȨд����������AXI SLAVE�ӿڵ�AWBURST�ź�ֵ�� */
        unsigned int  fail_lock  : 2;  /* bit[11-12]: ����ԽȨ������LOCK�ź�ֵ��
                                                      �����ԽȨ������������AXI SLAVE�ӿڵ�ARLOCK�ź�ֵ��
                                                      �����ԽȨд����������AXI SLAVE�ӿڵ�AWLOCK�ź�ֵ�� */
        unsigned int  fail_cache : 4;  /* bit[13-16]: ����ԽȨ������CACHE�ź�ֵ��
                                                      �����ԽȨ������������AXI SLAVE�ӿڵ�ARCACHE�ź�ֵ��
                                                      �����ԽȨд����������AXI SLAVE�ӿڵ�AWCACHE�ź�ֵ�� */
        unsigned int  fail_prot  : 3;  /* bit[17-19]: ����ԽȨ������PROT�ź�ֵ��
                                                      �����ԽȨ������������AXI SLAVE�ӿڵ�ARPROT�ź�ֵ��
                                                      �����ԽȨд����������AXI SLAVE�ӿڵ�AWPROT�ź�ֵ�� */
        unsigned int  reserved   : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_ASC_FAIL_INFO_UNION;
#endif
#define SOC_ASC_FAIL_INFO_fail_wr_START     (0)
#define SOC_ASC_FAIL_INFO_fail_wr_END       (0)
#define SOC_ASC_FAIL_INFO_fail_rd_START     (1)
#define SOC_ASC_FAIL_INFO_fail_rd_END       (1)
#define SOC_ASC_FAIL_INFO_fail_len_START    (2)
#define SOC_ASC_FAIL_INFO_fail_len_END      (5)
#define SOC_ASC_FAIL_INFO_fail_size_START   (6)
#define SOC_ASC_FAIL_INFO_fail_size_END     (8)
#define SOC_ASC_FAIL_INFO_fail_burst_START  (9)
#define SOC_ASC_FAIL_INFO_fail_burst_END    (10)
#define SOC_ASC_FAIL_INFO_fail_lock_START   (11)
#define SOC_ASC_FAIL_INFO_fail_lock_END     (12)
#define SOC_ASC_FAIL_INFO_fail_cache_START  (13)
#define SOC_ASC_FAIL_INFO_fail_cache_END    (16)
#define SOC_ASC_FAIL_INFO_fail_prot_START   (17)
#define SOC_ASC_FAIL_INFO_fail_prot_END     (19)






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

#endif /* end of soc_asc_interface.h */
