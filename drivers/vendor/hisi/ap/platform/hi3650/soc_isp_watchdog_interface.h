/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_watchdog_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:11
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_WatchDog.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_WATCHDOG_INTERFACE_H__
#define __SOC_ISP_WATCHDOG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) WatchDog
 ****************************************************************************/
/* �Ĵ���˵����������ֵ�Ĵ���������WatchDog�ڲ��������ļ�����ֵ��
   λ����UNION�ṹ:  SOC_ISP_WatchDog_WDG_LOAD_UNION */
#define SOC_ISP_WatchDog_WDG_LOAD_ADDR(base)          ((base) + (0x0000))

/* �Ĵ���˵������������ǰֵ�Ĵ���������WatchDog�ڲ��������ĵ�ǰ����ֵ��
   λ����UNION�ṹ:  SOC_ISP_WatchDog_WDG_VALUE_UNION */
#define SOC_ISP_WatchDog_WDG_VALUE_ADDR(base)         ((base) + (0x0004))

/* �Ĵ���˵�������ƼĴ���������WatchDog�Ĵ�/�رա��жϺ͸�λ���ܡ�
   λ����UNION�ṹ:  SOC_ISP_WatchDog_WDG_CONTROL_UNION */
#define SOC_ISP_WatchDog_WDG_CONTROL_ADDR(base)       ((base) + (0x0008))

/* �Ĵ���˵�����ж�����Ĵ��������WatchDog�жϣ�ʹWatchDog���������ֵ���м��������Ĵ�����ֻд�Ĵ�����д��ȥ����ֵ����������WatchDog���жϣ��ڲ���������д���ֵ���޸�λֵ��
   λ����UNION�ṹ:  SOC_ISP_WatchDog_WDG_INTCLR_UNION */
#define SOC_ISP_WatchDog_WDG_INTCLR_ADDR(base)        ((base) + (0x000C))

/* �Ĵ���˵����ԭʼ�жϼĴ�����
   λ����UNION�ṹ:  SOC_ISP_WatchDog_WDG_RIS_UNION */
#define SOC_ISP_WatchDog_WDG_RIS_ADDR(base)           ((base) + (0x0010))

/* �Ĵ���˵�������κ��жϼĴ�����
   λ����UNION�ṹ:  SOC_ISP_WatchDog_WDG_MIS_UNION */
#define SOC_ISP_WatchDog_WDG_MIS_ADDR(base)           ((base) + (0x0014))

/* �Ĵ���˵����LOCK�Ĵ���������WatchDog�Ĵ����Ķ�дȨ�ޡ�
   λ����UNION�ṹ:  SOC_ISP_WatchDog_WDG_LOCK_UNION */
#define SOC_ISP_WatchDog_WDG_LOCK_ADDR(base)          ((base) + (0x0C00))





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
                     (1/1) WatchDog
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_WatchDog_WDG_LOAD_UNION
 �ṹ˵��  : WDG_LOAD �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: ������ֵ�Ĵ���������WatchDog�ڲ��������ļ�����ֵ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdg_load : 32; /* bit[0-31]: Watchdog�ڲ��ݼ��������ĳ�ʼֵ����ֵһ����ˢ�£��������������������� */
    } reg;
} SOC_ISP_WatchDog_WDG_LOAD_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_LOAD_wdg_load_START  (0)
#define SOC_ISP_WatchDog_WDG_LOAD_wdg_load_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_WatchDog_WDG_VALUE_UNION
 �ṹ˵��  : WDG_VALUE �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: ��������ǰֵ�Ĵ���������WatchDog�ڲ��������ĵ�ǰ����ֵ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdogvalue : 32; /* bit[0-31]: ���ڵݼ������ļ�������ǰֵ�� */
    } reg;
} SOC_ISP_WatchDog_WDG_VALUE_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_VALUE_wdogvalue_START  (0)
#define SOC_ISP_WatchDog_WDG_VALUE_wdogvalue_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_WatchDog_WDG_CONTROL_UNION
 �ṹ˵��  : WDG_CONTROL �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ƼĴ���������WatchDog�Ĵ�/�رա��жϺ͸�λ���ܡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inten    : 1;  /* bit[0]   : WatchDog�ж��ź����ʹ�ܡ�
                                                   0��������ֹͣ����������ֵ���ֵ�ǰֵ���䣬WatchDog���رգ�
                                                   1����������������ʹ���жϣ�WatchDog��������
                                                   ���ж���ǰ����ֹ�����ж��ٴα�ʹ��ʱ���������ӼĴ���WdogLoad�������ֵ�����¿�ʼ������ */
        unsigned int  resen    : 1;  /* bit[1]   : WatchDog��λ�ź����ʹ�ܡ�
                                                   0����ֹ��
                                                   1��ʹ�ܡ� */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_ISP_WatchDog_WDG_CONTROL_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_CONTROL_inten_START     (0)
#define SOC_ISP_WatchDog_WDG_CONTROL_inten_END       (0)
#define SOC_ISP_WatchDog_WDG_CONTROL_resen_START     (1)
#define SOC_ISP_WatchDog_WDG_CONTROL_resen_END       (1)


/*****************************************************************************
 �ṹ��    : SOC_ISP_WatchDog_WDG_INTCLR_UNION
 �ṹ˵��  : WDG_INTCLR �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ��������WatchDog�жϣ�ʹWatchDog���������ֵ���м��������Ĵ�����ֻд�Ĵ�����д��ȥ����ֵ����������WatchDog���жϣ��ڲ���������д���ֵ���޸�λֵ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdg_intclr : 32; /* bit[0-31]: �ԸüĴ���д������ֵ�����WatchDog���жϣ���ʹWatchDog�ӼĴ���WDG_LOAD�����������ֵ���¼����� */
    } reg;
} SOC_ISP_WatchDog_WDG_INTCLR_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_INTCLR_wdg_intclr_START  (0)
#define SOC_ISP_WatchDog_WDG_INTCLR_wdg_intclr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_WatchDog_WDG_RIS_UNION
 �ṹ˵��  : WDG_RIS �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ�жϼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdogris  : 1;  /* bit[0]   : WatchDogԭʼ�ж�״̬�����������ļ���ֵ�ݼ���0ʱ����λ��1��
                                                   0��δ�����жϣ�
                                                   1���Ѳ����жϡ� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_ISP_WatchDog_WDG_RIS_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_RIS_wdogris_START   (0)
#define SOC_ISP_WatchDog_WDG_RIS_wdogris_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_WatchDog_WDG_MIS_UNION
 �ṹ˵��  : WDG_MIS �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���κ��жϼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdogmis  : 1;  /* bit[0]   : WatchDog�����κ��ж�״̬��
                                                   0��δ�����жϻ����жϱ����Σ�
                                                   1���Ѳ����жϡ� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_ISP_WatchDog_WDG_MIS_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_MIS_wdogmis_START   (0)
#define SOC_ISP_WatchDog_WDG_MIS_wdogmis_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_WatchDog_WDG_LOCK_UNION
 �ṹ˵��  : WDG_LOCK �Ĵ����ṹ���塣��ַƫ����:0x0C00����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOCK�Ĵ���������WatchDog�Ĵ����Ķ�дȨ�ޡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdg_lock : 32; /* bit[0-31]: ��üĴ���д��0x1ACC_E551���ɴ����мĴ�����дȨ�ޣ�
                                                   ��üĴ���д������ֵ��ر�дȨ�ޡ�
                                                   ���üĴ������ؼ�����״̬������д��üĴ�����ֵ��
                                                   0x0000_0000������д���ʣ�δ��������
                                                   0x0000_0001����ֹд���ʣ��Ѽ������� */
    } reg;
} SOC_ISP_WatchDog_WDG_LOCK_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_LOCK_wdg_lock_START  (0)
#define SOC_ISP_WatchDog_WDG_LOCK_wdg_lock_END    (31)






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

#endif /* end of soc_isp_watchdog_interface.h */
