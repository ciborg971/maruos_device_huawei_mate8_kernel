/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_syscounter_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:23:13
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_SYSCOUNTER.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_SYSCOUNTER_INTERFACE_H__
#define __SOC_SYSCOUNTER_INTERFACE_H__

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
/* �Ĵ���˵�������������ƼĴ�������Ҫ�ڰ�ȫģʽ�½���д���ʲ�����
   λ����UNION�ṹ:  SOC_SYSCOUNTER_CNTCR_UNION */
#define SOC_SYSCOUNTER_CNTCR_ADDR(base)               ((base) + (0x0000))

/* �Ĵ���˵����������״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SYSCOUNTER_CNTSR_UNION */
#define SOC_SYSCOUNTER_CNTSR_ADDR(base)               ((base) + (0x0004))

/* �Ĵ���˵��������������ֵ��32λ�Ĵ�������Ҫ�ڰ�ȫģʽ�½���д���ʲ�����
   λ����UNION�ṹ:  SOC_SYSCOUNTER_CNTCV_L32_UNION */
#define SOC_SYSCOUNTER_CNTCV_L32_ADDR(base)           ((base) + (0x0008))

/* �Ĵ���˵��������������ֵ��32λ�Ĵ�������Ҫ�ڰ�ȫģʽ�½���д���ʲ�����
   λ����UNION�ṹ:  SOC_SYSCOUNTER_CNTCV_H32_UNION */
#define SOC_SYSCOUNTER_CNTCV_H32_ADDR(base)           ((base) + (0x000C))

/* �Ĵ���˵����Ƶ��ģʽ0����Ҫ�ڰ�ȫģʽ�½���д���ʲ�����
   λ����UNION�ṹ:  SOC_SYSCOUNTER_CNTFID0_UNION */
#define SOC_SYSCOUNTER_CNTFID0_ADDR(base)             ((base) + (0x0020))

/* �Ĵ���˵����Ƶ��ģʽ1����Ҫ�ڰ�ȫģʽ�½���д���ʲ�����
   λ����UNION�ṹ:  SOC_SYSCOUNTER_CNTFID1_UNION */
#define SOC_SYSCOUNTER_CNTFID1_ADDR(base)             ((base) + (0x0024))

/* �Ĵ���˵����Ƶ��ģʽ2����Ҫ�ڰ�ȫģʽ�½���д���ʲ�����
   λ����UNION�ṹ:  SOC_SYSCOUNTER_CNTFID2_UNION */
#define SOC_SYSCOUNTER_CNTFID2_ADDR(base)             ((base) + (0x0028))

/* �Ĵ���˵��������������ֵ��32λ�Ĵ���
   λ����UNION�ṹ:  SOC_SYSCOUNTER_CNTCV_L32_NS_UNION */
#define SOC_SYSCOUNTER_CNTCV_L32_NS_ADDR(base)        ((base) + (0x1008))

/* �Ĵ���˵��������������ֵ��32λ�Ĵ���
   λ����UNION�ṹ:  SOC_SYSCOUNTER_CNTCV_H32_NS_UNION */
#define SOC_SYSCOUNTER_CNTCV_H32_NS_ADDR(base)        ((base) + (0x100C))





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
 �ṹ��    : SOC_SYSCOUNTER_CNTCR_UNION
 �ṹ˵��  : CNTCR �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���������ƼĴ�������Ҫ�ڰ�ȫģʽ�½���д���ʲ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]    : ʹ�ܼ�������
                                                    0��ϵͳ�������رղ�������
                                                    1��ϵͳ������ʹ�ܹ����� */
        unsigned int  hdbg     : 1;  /* bit[1]    : Halt-on-Debug������Halt-On-Debug�ź��Ƿ���ͣϵͳ���������¡�
                                                    0��ϵͳ����������Halt-on-debug�źţ�
                                                    1������ЧHalt-On-Debug�ź�ʱ����ͣϵͳ���������¡� */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : ������ */
        unsigned int  fcreq    : 3;  /* bit[8-10] : Ƶ��ģʽ����ѡ��ֻ�����е�1bit��������Ϊ1���޸����е�bit����ѡ���Ӧ�ļ���Ƶ�ʡ��������ֵ���ı�ϵͳ�������ķ�תƵ�ʡ�
                                                    0b001��ѡ���׼Ƶ�ʣ�
                                                    0b010��ѡ���׼Ƶ��2��
                                                    0b100��ѡ���׼Ƶ��3��
                                                    ����ֵ����Ч�� */
        unsigned int  reserved_1: 21; /* bit[11-31]: ������ */
    } reg;
} SOC_SYSCOUNTER_CNTCR_UNION;
#endif
#define SOC_SYSCOUNTER_CNTCR_en_START        (0)
#define SOC_SYSCOUNTER_CNTCR_en_END          (0)
#define SOC_SYSCOUNTER_CNTCR_hdbg_START      (1)
#define SOC_SYSCOUNTER_CNTCR_hdbg_END        (1)
#define SOC_SYSCOUNTER_CNTCR_fcreq_START     (8)
#define SOC_SYSCOUNTER_CNTCR_fcreq_END       (10)


/*****************************************************************************
 �ṹ��    : SOC_SYSCOUNTER_CNTSR_UNION
 �ṹ˵��  : CNTSR �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]    : ������ */
        unsigned int  dbgh     : 1;  /* bit[1]    : ָʾ�������Ƿ�����Halt-on-debug�źű���ͣ������
                                                    0��������δ����ͣ��
                                                    1������������ͣ�� */
        unsigned int  reserved_1: 6;  /* bit[2-7]  : ������ */
        unsigned int  fcack    : 3;  /* bit[8-10] : Ƶ�ʸı�ȷ�ϣ�ָʾ��ǰ������Ƶ��ģʽ��� */
        unsigned int  reserved_2: 21; /* bit[11-31]: ������ */
    } reg;
} SOC_SYSCOUNTER_CNTSR_UNION;
#endif
#define SOC_SYSCOUNTER_CNTSR_dbgh_START      (1)
#define SOC_SYSCOUNTER_CNTSR_dbgh_END        (1)
#define SOC_SYSCOUNTER_CNTSR_fcack_START     (8)
#define SOC_SYSCOUNTER_CNTSR_fcack_END       (10)


/*****************************************************************************
 �ṹ��    : SOC_SYSCOUNTER_CNTCV_L32_UNION
 �ṹ˵��  : CNTCV_L32 �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����������ֵ��32λ�Ĵ�������Ҫ�ڰ�ȫģʽ�½���д���ʲ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcv_l32 : 32; /* bit[0-31]: ����������ֵ�ĵ�32λ�Ĵ�����
                                                    ע�⣺ϵͳ������ʵ��ԭ�Ӳ������ơ���ʵ�ֻ����ǣ�һ��ȫ�µķ��ʣ�������ʵ�32λ����ֵ����ͬʱ����32λ������ģ���ڲ������´η��ʸ�32λ����ʱ���ͷ��ظ�λ���ݣ�����������ʵ�λ���ݣ���ʹ�ø��µĵ�λ���ݡ���һ�������ĵ�32λ�͸�32λ������֮������Ϊ���η��ʲ��������� */
    } reg;
} SOC_SYSCOUNTER_CNTCV_L32_UNION;
#endif
#define SOC_SYSCOUNTER_CNTCV_L32_cntcv_l32_START  (0)
#define SOC_SYSCOUNTER_CNTCV_L32_cntcv_l32_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SYSCOUNTER_CNTCV_H32_UNION
 �ṹ˵��  : CNTCV_H32 �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����������ֵ��32λ�Ĵ�������Ҫ�ڰ�ȫģʽ�½���д���ʲ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcv_h32 : 32; /* bit[0-31]: ����������ֵ�ĸ�32λ�Ĵ�����ԭ�ӷ��ʹ���ģʽ��CNTCV_L32�� */
    } reg;
} SOC_SYSCOUNTER_CNTCV_H32_UNION;
#endif
#define SOC_SYSCOUNTER_CNTCV_H32_cntcv_h32_START  (0)
#define SOC_SYSCOUNTER_CNTCV_H32_cntcv_h32_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SYSCOUNTER_CNTFID0_UNION
 �ṹ˵��  : CNTFID0 �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ƶ��ģʽ0����Ҫ�ڰ�ȫģʽ�½���д���ʲ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntfid0 : 32; /* bit[0-31]: Ƶ��ģʽ0����Ӧ��ϵͳ�����������Ļ�׼Ƶ�ʡ� */
    } reg;
} SOC_SYSCOUNTER_CNTFID0_UNION;
#endif
#define SOC_SYSCOUNTER_CNTFID0_cntfid0_START  (0)
#define SOC_SYSCOUNTER_CNTFID0_cntfid0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SYSCOUNTER_CNTFID1_UNION
 �ṹ˵��  : CNTFID1 �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ƶ��ģʽ1����Ҫ�ڰ�ȫģʽ�½���д���ʲ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntfid1 : 32; /* bit[0-31]: Ƶ��ģʽ1����Ӧ��ϵͳ��������ѡ����Ƶ��1�� */
    } reg;
} SOC_SYSCOUNTER_CNTFID1_UNION;
#endif
#define SOC_SYSCOUNTER_CNTFID1_cntfid1_START  (0)
#define SOC_SYSCOUNTER_CNTFID1_cntfid1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SYSCOUNTER_CNTFID2_UNION
 �ṹ˵��  : CNTFID2 �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ƶ��ģʽ2����Ҫ�ڰ�ȫģʽ�½���д���ʲ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntfid2 : 32; /* bit[0-31]: Ƶ��ģʽ2����Ӧ��ϵͳ��������ѡ����Ƶ��2�� */
    } reg;
} SOC_SYSCOUNTER_CNTFID2_UNION;
#endif
#define SOC_SYSCOUNTER_CNTFID2_cntfid2_START  (0)
#define SOC_SYSCOUNTER_CNTFID2_cntfid2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SYSCOUNTER_CNTCV_L32_NS_UNION
 �ṹ˵��  : CNTCV_L32_NS �Ĵ����ṹ���塣��ַƫ����:0x1008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����������ֵ��32λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcv_l32_ns : 32; /* bit[0-31]: ����������ֵ�ĵ�32λ�Ĵ�����λ�ڷǰ�ȫ�ĵ�ַ�ռ䡣������ʽ��CNTCV_L32�� */
    } reg;
} SOC_SYSCOUNTER_CNTCV_L32_NS_UNION;
#endif
#define SOC_SYSCOUNTER_CNTCV_L32_NS_cntcv_l32_ns_START  (0)
#define SOC_SYSCOUNTER_CNTCV_L32_NS_cntcv_l32_ns_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SYSCOUNTER_CNTCV_H32_NS_UNION
 �ṹ˵��  : CNTCV_H32_NS �Ĵ����ṹ���塣��ַƫ����:0x100C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����������ֵ��32λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcv_h32_ns : 32; /* bit[0-31]: ����������ֵ�ĸ�32λ�Ĵ�����λ�ڷǰ�ȫ�ĵ�ַ�ռ䡣ԭ�ӷ��ʹ���ģʽ��CNTCV_H32�� */
    } reg;
} SOC_SYSCOUNTER_CNTCV_H32_NS_UNION;
#endif
#define SOC_SYSCOUNTER_CNTCV_H32_NS_cntcv_h32_ns_START  (0)
#define SOC_SYSCOUNTER_CNTCV_H32_NS_cntcv_h32_ns_END    (31)






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

#endif /* end of soc_syscounter_interface.h */
