/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_tzpc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-04-08 11:48:25
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��4��8��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_TZPC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_TZPC_INTERFACE_H__
#define __SOC_TZPC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) TZPC
 ****************************************************************************/
/* �Ĵ���˵�������ڿ��ư�ȫ�����������С
            �Ӳ�TZMA���ж�secram�Ŀ��ƣ���4KBΪ��λ
            0x00000000 = no secure region
            0x00000001 = 4KB secure region
            0x00000002 = 8KB secure region
            ��
            0x000001FF = 2044KB secure region
            0x00000200 �����ϵ����ý�������secram�ռ����ɰ�ȫ�ռ䡣
   λ����UNION�ṹ:  SOC_TZPC_R0SIZE_UNION */
#define SOC_TZPC_R0SIZE_ADDR(base)                    ((base) + (0x000))

/* �Ĵ���˵����IP��ȫ����״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT0STAT_UNION */
#define SOC_TZPC_DECPROT0STAT_ADDR(base)              ((base) + (0x800))

/* �Ĵ���˵����IP��ȫ������λ�Ĵ���0��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT0SET_UNION */
#define SOC_TZPC_DECPROT0SET_ADDR(base)               ((base) + (0x804))

/* �Ĵ���˵����IP��ȫ��������Ĵ���0��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT0CLR_UNION */
#define SOC_TZPC_DECPROT0CLR_ADDR(base)               ((base) + (0x808))

/* �Ĵ���˵����IP��ȫ����״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT1STAT_UNION */
#define SOC_TZPC_DECPROT1STAT_ADDR(base)              ((base) + (0x80C))

/* �Ĵ���˵����IP��ȫ������λ�Ĵ���1��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT1SET_UNION */
#define SOC_TZPC_DECPROT1SET_ADDR(base)               ((base) + (0x810))

/* �Ĵ���˵����IP��ȫ��������Ĵ���1��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT1CLR_UNION */
#define SOC_TZPC_DECPROT1CLR_ADDR(base)               ((base) + (0x814))

/* �Ĵ���˵����IP��ȫ����״̬�Ĵ���2��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT2STAT_UNION */
#define SOC_TZPC_DECPROT2STAT_ADDR(base)              ((base) + (0x818))

/* �Ĵ���˵����IP��ȫ������λ�Ĵ���2��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT2SET_UNION */
#define SOC_TZPC_DECPROT2SET_ADDR(base)               ((base) + (0x81C))

/* �Ĵ���˵����IP��ȫ��������Ĵ���2��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT2CLR_UNION */
#define SOC_TZPC_DECPROT2CLR_ADDR(base)               ((base) + (0x820))

/* �Ĵ���˵����IP��ȫ����״̬�Ĵ���3��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT3STAT_UNION */
#define SOC_TZPC_DECPROT3STAT_ADDR(base)              ((base) + (0x824))

/* �Ĵ���˵����IP��ȫ������λ�Ĵ���3��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT3SET_UNION */
#define SOC_TZPC_DECPROT3SET_ADDR(base)               ((base) + (0x828))

/* �Ĵ���˵����IP��ȫ��������Ĵ���3��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT3CLR_UNION */
#define SOC_TZPC_DECPROT3CLR_ADDR(base)               ((base) + (0x82C))

/* �Ĵ���˵����IP��ȫ����״̬�Ĵ���4��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT4STAT_UNION */
#define SOC_TZPC_DECPROT4STAT_ADDR(base)              ((base) + (0x830))

/* �Ĵ���˵����IP��ȫ������λ�Ĵ���4��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT4SET_UNION */
#define SOC_TZPC_DECPROT4SET_ADDR(base)               ((base) + (0x834))

/* �Ĵ���˵����IP��ȫ��������Ĵ���4��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT4CLR_UNION */
#define SOC_TZPC_DECPROT4CLR_ADDR(base)               ((base) + (0x838))

/* �Ĵ���˵����IP��ȫ����״̬�Ĵ���5��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT5STAT_UNION */
#define SOC_TZPC_DECPROT5STAT_ADDR(base)              ((base) + (0x83C))

/* �Ĵ���˵����IP��ȫ������λ�Ĵ���5��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT5SET_UNION */
#define SOC_TZPC_DECPROT5SET_ADDR(base)               ((base) + (0x840))

/* �Ĵ���˵����IP��ȫ��������Ĵ���5��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT5CLR_UNION */
#define SOC_TZPC_DECPROT5CLR_ADDR(base)               ((base) + (0x844))

/* �Ĵ���˵����IP��ȫ����״̬�Ĵ���6��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT6STAT_UNION */
#define SOC_TZPC_DECPROT6STAT_ADDR(base)              ((base) + (0x848))

/* �Ĵ���˵����IP��ȫ������λ�Ĵ���6��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT6SET_UNION */
#define SOC_TZPC_DECPROT6SET_ADDR(base)               ((base) + (0x84C))

/* �Ĵ���˵����IP��ȫ��������Ĵ���6��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT6CLR_UNION */
#define SOC_TZPC_DECPROT6CLR_ADDR(base)               ((base) + (0x850))

/* �Ĵ���˵����IP��ȫ����״̬�Ĵ���7��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT7STAT_UNION */
#define SOC_TZPC_DECPROT7STAT_ADDR(base)              ((base) + (0x854))

/* �Ĵ���˵����IP��ȫ������λ�Ĵ���7��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT7SET_UNION */
#define SOC_TZPC_DECPROT7SET_ADDR(base)               ((base) + (0x858))

/* �Ĵ���˵����IP��ȫ��������Ĵ���7��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT7CLR_UNION */
#define SOC_TZPC_DECPROT7CLR_ADDR(base)               ((base) + (0x85C))

/* �Ĵ���˵����IP��ȫ����״̬�Ĵ���8��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT8STAT_UNION */
#define SOC_TZPC_DECPROT8STAT_ADDR(base)              ((base) + (0x860))

/* �Ĵ���˵����IP��ȫ������λ�Ĵ���8��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT8SET_UNION */
#define SOC_TZPC_DECPROT8SET_ADDR(base)               ((base) + (0x864))

/* �Ĵ���˵����IP��ȫ��������Ĵ���8��
   λ����UNION�ṹ:  SOC_TZPC_DECPROT8CLR_UNION */
#define SOC_TZPC_DECPROT8CLR_ADDR(base)               ((base) + (0x868))

/* �Ĵ���˵��������reg0�Ĵ�������Ϣ��
   λ����UNION�ṹ:  SOC_TZPC_REG0_STAT_UNION */
#define SOC_TZPC_REG0_STAT_ADDR(base)                 ((base) + (0x86C))

/* �Ĵ���˵��������reg1�Ĵ�������Ϣ��
   λ����UNION�ṹ:  SOC_TZPC_REG1_STAT_UNION */
#define SOC_TZPC_REG1_STAT_ADDR(base)                 ((base) + (0x870))





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
                     (1/1) TZPC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_TZPC_R0SIZE_UNION
 �ṹ˵��  : R0SIZE �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x000003FF�����:32
 �Ĵ���˵��: ���ڿ��ư�ȫ�����������С
            �Ӳ�TZMA���ж�secram�Ŀ��ƣ���4KBΪ��λ
            0x00000000 = no secure region
            0x00000001 = 4KB secure region
            0x00000002 = 8KB secure region
            ��
            0x000001FF = 2044KB secure region
            0x00000200 �����ϵ����ý�������secram�ռ����ɰ�ȫ�ռ䡣
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 10; /* bit[0-9]  : ������ */
        unsigned int  reserved_1: 22; /* bit[10-31]: ������ */
    } reg;
} SOC_TZPC_R0SIZE_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT0STAT_UNION
 �ṹ˵��  : DECPROT0STAT �Ĵ����ṹ���塣��ַƫ����:0x800����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ����״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efusec        : 1;  /* bit[0] : efusec slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  rtc0          : 1;  /* bit[1] : rtc0 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  rtc1          : 1;  /* bit[2] : rtc1 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  sci0          : 1;  /* bit[3] : sci0 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  sci1          : 1;  /* bit[4] : sci1 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  syscnt        : 1;  /* bit[5] : syscnt slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  sctrl_region1 : 1;  /* bit[6] : sctrl region1(0x4020A000~0x4020A7FF)�ϵ�Ĭ��Ϊ��ȫ���ԡ�  */
        unsigned int  sctrl_region2 : 1;  /* bit[7] : sctrl region2(0xA800~0xA9FF AC00~AFFF)�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  sctrl_region3 : 1;  /* bit[8] : sctrl region3(0xAA00~0xAAFF)ASP��ϵͳ��λ�İ�ȫ���ƣ��ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  sctrl_region4 : 1;  /* bit[9] : sctrl region4(0xAB00~0xABFF)Sensor_sub��ϵͳ��λ�İ�ȫ���ƣ��ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio22        : 1;  /* bit[10]: gpio22 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio23        : 1;  /* bit[11]: gpio23 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio24        : 1;  /* bit[12]: gpio24 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio25        : 1;  /* bit[13]: gpio25 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio26        : 1;  /* bit[14]: gpio26 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio27        : 1;  /* bit[15]: gpio27 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  ao_ioc        : 1;  /* bit[16]: ao_ioc slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  bb_drx        : 1;  /* bit[17]: bb_drx slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  time0         : 1;  /* bit[18]: time0 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  time1         : 1;  /* bit[19]: time1 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  time2         : 1;  /* bit[20]: time2 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  time3         : 1;  /* bit[21]: time3 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  time4         : 1;  /* bit[22]: time4 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  time5         : 1;  /* bit[23]: time5 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  time6         : 1;  /* bit[24]: time6 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  time7         : 1;  /* bit[25]: time7 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  time8         : 1;  /* bit[26]: time8 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  mmbuf         : 1;  /* bit[27]: mmbuf slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  asc           : 1;  /* bit[28]: asc slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  reserved_0    : 1;  /* bit[29]: ������ */
        unsigned int  reserved_1    : 1;  /* bit[30]: ������ */
        unsigned int  reserved_2    : 1;  /* bit[31]: ������ */
    } reg;
} SOC_TZPC_DECPROT0STAT_UNION;
#endif
#define SOC_TZPC_DECPROT0STAT_efusec_START         (0)
#define SOC_TZPC_DECPROT0STAT_efusec_END           (0)
#define SOC_TZPC_DECPROT0STAT_rtc0_START           (1)
#define SOC_TZPC_DECPROT0STAT_rtc0_END             (1)
#define SOC_TZPC_DECPROT0STAT_rtc1_START           (2)
#define SOC_TZPC_DECPROT0STAT_rtc1_END             (2)
#define SOC_TZPC_DECPROT0STAT_sci0_START           (3)
#define SOC_TZPC_DECPROT0STAT_sci0_END             (3)
#define SOC_TZPC_DECPROT0STAT_sci1_START           (4)
#define SOC_TZPC_DECPROT0STAT_sci1_END             (4)
#define SOC_TZPC_DECPROT0STAT_syscnt_START         (5)
#define SOC_TZPC_DECPROT0STAT_syscnt_END           (5)
#define SOC_TZPC_DECPROT0STAT_sctrl_region1_START  (6)
#define SOC_TZPC_DECPROT0STAT_sctrl_region1_END    (6)
#define SOC_TZPC_DECPROT0STAT_sctrl_region2_START  (7)
#define SOC_TZPC_DECPROT0STAT_sctrl_region2_END    (7)
#define SOC_TZPC_DECPROT0STAT_sctrl_region3_START  (8)
#define SOC_TZPC_DECPROT0STAT_sctrl_region3_END    (8)
#define SOC_TZPC_DECPROT0STAT_sctrl_region4_START  (9)
#define SOC_TZPC_DECPROT0STAT_sctrl_region4_END    (9)
#define SOC_TZPC_DECPROT0STAT_gpio22_START         (10)
#define SOC_TZPC_DECPROT0STAT_gpio22_END           (10)
#define SOC_TZPC_DECPROT0STAT_gpio23_START         (11)
#define SOC_TZPC_DECPROT0STAT_gpio23_END           (11)
#define SOC_TZPC_DECPROT0STAT_gpio24_START         (12)
#define SOC_TZPC_DECPROT0STAT_gpio24_END           (12)
#define SOC_TZPC_DECPROT0STAT_gpio25_START         (13)
#define SOC_TZPC_DECPROT0STAT_gpio25_END           (13)
#define SOC_TZPC_DECPROT0STAT_gpio26_START         (14)
#define SOC_TZPC_DECPROT0STAT_gpio26_END           (14)
#define SOC_TZPC_DECPROT0STAT_gpio27_START         (15)
#define SOC_TZPC_DECPROT0STAT_gpio27_END           (15)
#define SOC_TZPC_DECPROT0STAT_ao_ioc_START         (16)
#define SOC_TZPC_DECPROT0STAT_ao_ioc_END           (16)
#define SOC_TZPC_DECPROT0STAT_bb_drx_START         (17)
#define SOC_TZPC_DECPROT0STAT_bb_drx_END           (17)
#define SOC_TZPC_DECPROT0STAT_time0_START          (18)
#define SOC_TZPC_DECPROT0STAT_time0_END            (18)
#define SOC_TZPC_DECPROT0STAT_time1_START          (19)
#define SOC_TZPC_DECPROT0STAT_time1_END            (19)
#define SOC_TZPC_DECPROT0STAT_time2_START          (20)
#define SOC_TZPC_DECPROT0STAT_time2_END            (20)
#define SOC_TZPC_DECPROT0STAT_time3_START          (21)
#define SOC_TZPC_DECPROT0STAT_time3_END            (21)
#define SOC_TZPC_DECPROT0STAT_time4_START          (22)
#define SOC_TZPC_DECPROT0STAT_time4_END            (22)
#define SOC_TZPC_DECPROT0STAT_time5_START          (23)
#define SOC_TZPC_DECPROT0STAT_time5_END            (23)
#define SOC_TZPC_DECPROT0STAT_time6_START          (24)
#define SOC_TZPC_DECPROT0STAT_time6_END            (24)
#define SOC_TZPC_DECPROT0STAT_time7_START          (25)
#define SOC_TZPC_DECPROT0STAT_time7_END            (25)
#define SOC_TZPC_DECPROT0STAT_time8_START          (26)
#define SOC_TZPC_DECPROT0STAT_time8_END            (26)
#define SOC_TZPC_DECPROT0STAT_mmbuf_START          (27)
#define SOC_TZPC_DECPROT0STAT_mmbuf_END            (27)
#define SOC_TZPC_DECPROT0STAT_asc_START            (28)
#define SOC_TZPC_DECPROT0STAT_asc_END              (28)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT0SET_UNION
 �ṹ˵��  : DECPROT0SET �Ĵ����ṹ���塣��ַƫ����:0x804����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ������λ�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efusec        : 1;  /* bit[0] : IP��ȫ������λ��
                                                      0��IP��ȫ���Բ��䣻
                                                      1��IP��ȫ�����á�1���� */
        unsigned int  rtc0          : 1;  /* bit[1] :  */
        unsigned int  rtc1          : 1;  /* bit[2] :  */
        unsigned int  sci0          : 1;  /* bit[3] :  */
        unsigned int  sci1          : 1;  /* bit[4] :  */
        unsigned int  syscnt        : 1;  /* bit[5] :  */
        unsigned int  sctrl_region1 : 1;  /* bit[6] :  */
        unsigned int  sctrl_region2 : 1;  /* bit[7] :  */
        unsigned int  sctrl_region3 : 1;  /* bit[8] :  */
        unsigned int  sctrl_region4 : 1;  /* bit[9] :  */
        unsigned int  gpio22        : 1;  /* bit[10]:  */
        unsigned int  gpio23        : 1;  /* bit[11]:  */
        unsigned int  gpio24        : 1;  /* bit[12]:  */
        unsigned int  gpio25        : 1;  /* bit[13]:  */
        unsigned int  gpio26        : 1;  /* bit[14]:  */
        unsigned int  gpio27        : 1;  /* bit[15]:  */
        unsigned int  ao_ioc        : 1;  /* bit[16]:  */
        unsigned int  bb_drx        : 1;  /* bit[17]:  */
        unsigned int  time0         : 1;  /* bit[18]:  */
        unsigned int  time1         : 1;  /* bit[19]:  */
        unsigned int  time2         : 1;  /* bit[20]:  */
        unsigned int  time3         : 1;  /* bit[21]:  */
        unsigned int  time4         : 1;  /* bit[22]:  */
        unsigned int  time5         : 1;  /* bit[23]:  */
        unsigned int  time6         : 1;  /* bit[24]:  */
        unsigned int  time7         : 1;  /* bit[25]:  */
        unsigned int  time8         : 1;  /* bit[26]:  */
        unsigned int  mmbuf         : 1;  /* bit[27]:  */
        unsigned int  asc           : 1;  /* bit[28]:  */
        unsigned int  reserved_0    : 1;  /* bit[29]:  */
        unsigned int  reserved_1    : 1;  /* bit[30]:  */
        unsigned int  reserved_2    : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT0SET_UNION;
#endif
#define SOC_TZPC_DECPROT0SET_efusec_START         (0)
#define SOC_TZPC_DECPROT0SET_efusec_END           (0)
#define SOC_TZPC_DECPROT0SET_rtc0_START           (1)
#define SOC_TZPC_DECPROT0SET_rtc0_END             (1)
#define SOC_TZPC_DECPROT0SET_rtc1_START           (2)
#define SOC_TZPC_DECPROT0SET_rtc1_END             (2)
#define SOC_TZPC_DECPROT0SET_sci0_START           (3)
#define SOC_TZPC_DECPROT0SET_sci0_END             (3)
#define SOC_TZPC_DECPROT0SET_sci1_START           (4)
#define SOC_TZPC_DECPROT0SET_sci1_END             (4)
#define SOC_TZPC_DECPROT0SET_syscnt_START         (5)
#define SOC_TZPC_DECPROT0SET_syscnt_END           (5)
#define SOC_TZPC_DECPROT0SET_sctrl_region1_START  (6)
#define SOC_TZPC_DECPROT0SET_sctrl_region1_END    (6)
#define SOC_TZPC_DECPROT0SET_sctrl_region2_START  (7)
#define SOC_TZPC_DECPROT0SET_sctrl_region2_END    (7)
#define SOC_TZPC_DECPROT0SET_sctrl_region3_START  (8)
#define SOC_TZPC_DECPROT0SET_sctrl_region3_END    (8)
#define SOC_TZPC_DECPROT0SET_sctrl_region4_START  (9)
#define SOC_TZPC_DECPROT0SET_sctrl_region4_END    (9)
#define SOC_TZPC_DECPROT0SET_gpio22_START         (10)
#define SOC_TZPC_DECPROT0SET_gpio22_END           (10)
#define SOC_TZPC_DECPROT0SET_gpio23_START         (11)
#define SOC_TZPC_DECPROT0SET_gpio23_END           (11)
#define SOC_TZPC_DECPROT0SET_gpio24_START         (12)
#define SOC_TZPC_DECPROT0SET_gpio24_END           (12)
#define SOC_TZPC_DECPROT0SET_gpio25_START         (13)
#define SOC_TZPC_DECPROT0SET_gpio25_END           (13)
#define SOC_TZPC_DECPROT0SET_gpio26_START         (14)
#define SOC_TZPC_DECPROT0SET_gpio26_END           (14)
#define SOC_TZPC_DECPROT0SET_gpio27_START         (15)
#define SOC_TZPC_DECPROT0SET_gpio27_END           (15)
#define SOC_TZPC_DECPROT0SET_ao_ioc_START         (16)
#define SOC_TZPC_DECPROT0SET_ao_ioc_END           (16)
#define SOC_TZPC_DECPROT0SET_bb_drx_START         (17)
#define SOC_TZPC_DECPROT0SET_bb_drx_END           (17)
#define SOC_TZPC_DECPROT0SET_time0_START          (18)
#define SOC_TZPC_DECPROT0SET_time0_END            (18)
#define SOC_TZPC_DECPROT0SET_time1_START          (19)
#define SOC_TZPC_DECPROT0SET_time1_END            (19)
#define SOC_TZPC_DECPROT0SET_time2_START          (20)
#define SOC_TZPC_DECPROT0SET_time2_END            (20)
#define SOC_TZPC_DECPROT0SET_time3_START          (21)
#define SOC_TZPC_DECPROT0SET_time3_END            (21)
#define SOC_TZPC_DECPROT0SET_time4_START          (22)
#define SOC_TZPC_DECPROT0SET_time4_END            (22)
#define SOC_TZPC_DECPROT0SET_time5_START          (23)
#define SOC_TZPC_DECPROT0SET_time5_END            (23)
#define SOC_TZPC_DECPROT0SET_time6_START          (24)
#define SOC_TZPC_DECPROT0SET_time6_END            (24)
#define SOC_TZPC_DECPROT0SET_time7_START          (25)
#define SOC_TZPC_DECPROT0SET_time7_END            (25)
#define SOC_TZPC_DECPROT0SET_time8_START          (26)
#define SOC_TZPC_DECPROT0SET_time8_END            (26)
#define SOC_TZPC_DECPROT0SET_mmbuf_START          (27)
#define SOC_TZPC_DECPROT0SET_mmbuf_END            (27)
#define SOC_TZPC_DECPROT0SET_asc_START            (28)
#define SOC_TZPC_DECPROT0SET_asc_END              (28)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT0CLR_UNION
 �ṹ˵��  : DECPROT0CLR �Ĵ����ṹ���塣��ַƫ����:0x808����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ��������Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efusec        : 1;  /* bit[0] : IP��ȫ�������㣺
                                                      0��IP��ȫ���Բ��䣻
                                                      1��IP��ȫ�����á�0���� */
        unsigned int  rtc0          : 1;  /* bit[1] :  */
        unsigned int  rtc1          : 1;  /* bit[2] :  */
        unsigned int  sci0          : 1;  /* bit[3] :  */
        unsigned int  sci1          : 1;  /* bit[4] :  */
        unsigned int  syscnt        : 1;  /* bit[5] :  */
        unsigned int  sctrl_region1 : 1;  /* bit[6] :  */
        unsigned int  sctrl_region2 : 1;  /* bit[7] :  */
        unsigned int  sctrl_region3 : 1;  /* bit[8] :  */
        unsigned int  sctrl_region4 : 1;  /* bit[9] :  */
        unsigned int  gpio22        : 1;  /* bit[10]:  */
        unsigned int  gpio23        : 1;  /* bit[11]:  */
        unsigned int  gpio24        : 1;  /* bit[12]:  */
        unsigned int  gpio25        : 1;  /* bit[13]:  */
        unsigned int  gpio26        : 1;  /* bit[14]:  */
        unsigned int  gpio27        : 1;  /* bit[15]:  */
        unsigned int  ao_ioc        : 1;  /* bit[16]:  */
        unsigned int  bb_drx        : 1;  /* bit[17]:  */
        unsigned int  time0         : 1;  /* bit[18]:  */
        unsigned int  time1         : 1;  /* bit[19]:  */
        unsigned int  time2         : 1;  /* bit[20]:  */
        unsigned int  time3         : 1;  /* bit[21]:  */
        unsigned int  time4         : 1;  /* bit[22]:  */
        unsigned int  time5         : 1;  /* bit[23]:  */
        unsigned int  time6         : 1;  /* bit[24]:  */
        unsigned int  time7         : 1;  /* bit[25]:  */
        unsigned int  time8         : 1;  /* bit[26]:  */
        unsigned int  mmbuf         : 1;  /* bit[27]:  */
        unsigned int  asc           : 1;  /* bit[28]:  */
        unsigned int  reserved_0    : 1;  /* bit[29]:  */
        unsigned int  reserved_1    : 1;  /* bit[30]:  */
        unsigned int  reserved_2    : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT0CLR_UNION;
#endif
#define SOC_TZPC_DECPROT0CLR_efusec_START         (0)
#define SOC_TZPC_DECPROT0CLR_efusec_END           (0)
#define SOC_TZPC_DECPROT0CLR_rtc0_START           (1)
#define SOC_TZPC_DECPROT0CLR_rtc0_END             (1)
#define SOC_TZPC_DECPROT0CLR_rtc1_START           (2)
#define SOC_TZPC_DECPROT0CLR_rtc1_END             (2)
#define SOC_TZPC_DECPROT0CLR_sci0_START           (3)
#define SOC_TZPC_DECPROT0CLR_sci0_END             (3)
#define SOC_TZPC_DECPROT0CLR_sci1_START           (4)
#define SOC_TZPC_DECPROT0CLR_sci1_END             (4)
#define SOC_TZPC_DECPROT0CLR_syscnt_START         (5)
#define SOC_TZPC_DECPROT0CLR_syscnt_END           (5)
#define SOC_TZPC_DECPROT0CLR_sctrl_region1_START  (6)
#define SOC_TZPC_DECPROT0CLR_sctrl_region1_END    (6)
#define SOC_TZPC_DECPROT0CLR_sctrl_region2_START  (7)
#define SOC_TZPC_DECPROT0CLR_sctrl_region2_END    (7)
#define SOC_TZPC_DECPROT0CLR_sctrl_region3_START  (8)
#define SOC_TZPC_DECPROT0CLR_sctrl_region3_END    (8)
#define SOC_TZPC_DECPROT0CLR_sctrl_region4_START  (9)
#define SOC_TZPC_DECPROT0CLR_sctrl_region4_END    (9)
#define SOC_TZPC_DECPROT0CLR_gpio22_START         (10)
#define SOC_TZPC_DECPROT0CLR_gpio22_END           (10)
#define SOC_TZPC_DECPROT0CLR_gpio23_START         (11)
#define SOC_TZPC_DECPROT0CLR_gpio23_END           (11)
#define SOC_TZPC_DECPROT0CLR_gpio24_START         (12)
#define SOC_TZPC_DECPROT0CLR_gpio24_END           (12)
#define SOC_TZPC_DECPROT0CLR_gpio25_START         (13)
#define SOC_TZPC_DECPROT0CLR_gpio25_END           (13)
#define SOC_TZPC_DECPROT0CLR_gpio26_START         (14)
#define SOC_TZPC_DECPROT0CLR_gpio26_END           (14)
#define SOC_TZPC_DECPROT0CLR_gpio27_START         (15)
#define SOC_TZPC_DECPROT0CLR_gpio27_END           (15)
#define SOC_TZPC_DECPROT0CLR_ao_ioc_START         (16)
#define SOC_TZPC_DECPROT0CLR_ao_ioc_END           (16)
#define SOC_TZPC_DECPROT0CLR_bb_drx_START         (17)
#define SOC_TZPC_DECPROT0CLR_bb_drx_END           (17)
#define SOC_TZPC_DECPROT0CLR_time0_START          (18)
#define SOC_TZPC_DECPROT0CLR_time0_END            (18)
#define SOC_TZPC_DECPROT0CLR_time1_START          (19)
#define SOC_TZPC_DECPROT0CLR_time1_END            (19)
#define SOC_TZPC_DECPROT0CLR_time2_START          (20)
#define SOC_TZPC_DECPROT0CLR_time2_END            (20)
#define SOC_TZPC_DECPROT0CLR_time3_START          (21)
#define SOC_TZPC_DECPROT0CLR_time3_END            (21)
#define SOC_TZPC_DECPROT0CLR_time4_START          (22)
#define SOC_TZPC_DECPROT0CLR_time4_END            (22)
#define SOC_TZPC_DECPROT0CLR_time5_START          (23)
#define SOC_TZPC_DECPROT0CLR_time5_END            (23)
#define SOC_TZPC_DECPROT0CLR_time6_START          (24)
#define SOC_TZPC_DECPROT0CLR_time6_END            (24)
#define SOC_TZPC_DECPROT0CLR_time7_START          (25)
#define SOC_TZPC_DECPROT0CLR_time7_END            (25)
#define SOC_TZPC_DECPROT0CLR_time8_START          (26)
#define SOC_TZPC_DECPROT0CLR_time8_END            (26)
#define SOC_TZPC_DECPROT0CLR_mmbuf_START          (27)
#define SOC_TZPC_DECPROT0CLR_mmbuf_END            (27)
#define SOC_TZPC_DECPROT0CLR_asc_START            (28)
#define SOC_TZPC_DECPROT0CLR_asc_END              (28)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT1STAT_UNION
 �ṹ˵��  : DECPROT1STAT �Ĵ����ṹ���塣��ַƫ����:0x80C����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ����״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 1;  /* bit[0] : ������ */
        unsigned int  reserved_1    : 1;  /* bit[1] : ������ */
        unsigned int  timer9        : 1;  /* bit[2] : timer9 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  timer10       : 1;  /* bit[3] : timer10 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  timer11       : 1;  /* bit[4] : timer11 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  timer12       : 1;  /* bit[5] : timer12 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  pctrl_region1 : 1;  /* bit[6] : PCTRL(0xA8A09000~0xA8A093FF)�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  pctrl_region2 : 1;  /* bit[7] : PCTRL(0xA8A09400~0xA8A097FF)�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  pctrl_region3 : 1;  /* bit[8] : PCTRL(0xA8A09800~0xA8A09BFF)�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  pctrl_region4 : 1;  /* bit[9] : PCTRL(0xA8A09C00~0xA8A09FFF)�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  pwm           : 1;  /* bit[10]: pwm slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  reserved_2    : 1;  /* bit[11]: ������ */
        unsigned int  watchdog0     : 1;  /* bit[12]: watchdog0 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  watchdog1     : 1;  /* bit[13]: watchdog1 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio0         : 1;  /* bit[14]: gpio0 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio1         : 1;  /* bit[15]: gpio1 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio2         : 1;  /* bit[16]: gpio2 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio3         : 1;  /* bit[17]: gpio3 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio4         : 1;  /* bit[18]: gpio4 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio5         : 1;  /* bit[19]: gpio5 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio6         : 1;  /* bit[20]: gpio6 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio7         : 1;  /* bit[21]: gpio7 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio8         : 1;  /* bit[22]: gpio8 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio9         : 1;  /* bit[23]: gpio9 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio10        : 1;  /* bit[24]: gpio10 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio11        : 1;  /* bit[25]: gpio11 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio12        : 1;  /* bit[26]: gpio12 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio13        : 1;  /* bit[27]: gpio13 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio14        : 1;  /* bit[28]: gpio14 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio15        : 1;  /* bit[29]: gpio15 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio16        : 1;  /* bit[30]: gpio16 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio17        : 1;  /* bit[31]: gpio17 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
    } reg;
} SOC_TZPC_DECPROT1STAT_UNION;
#endif
#define SOC_TZPC_DECPROT1STAT_timer9_START         (2)
#define SOC_TZPC_DECPROT1STAT_timer9_END           (2)
#define SOC_TZPC_DECPROT1STAT_timer10_START        (3)
#define SOC_TZPC_DECPROT1STAT_timer10_END          (3)
#define SOC_TZPC_DECPROT1STAT_timer11_START        (4)
#define SOC_TZPC_DECPROT1STAT_timer11_END          (4)
#define SOC_TZPC_DECPROT1STAT_timer12_START        (5)
#define SOC_TZPC_DECPROT1STAT_timer12_END          (5)
#define SOC_TZPC_DECPROT1STAT_pctrl_region1_START  (6)
#define SOC_TZPC_DECPROT1STAT_pctrl_region1_END    (6)
#define SOC_TZPC_DECPROT1STAT_pctrl_region2_START  (7)
#define SOC_TZPC_DECPROT1STAT_pctrl_region2_END    (7)
#define SOC_TZPC_DECPROT1STAT_pctrl_region3_START  (8)
#define SOC_TZPC_DECPROT1STAT_pctrl_region3_END    (8)
#define SOC_TZPC_DECPROT1STAT_pctrl_region4_START  (9)
#define SOC_TZPC_DECPROT1STAT_pctrl_region4_END    (9)
#define SOC_TZPC_DECPROT1STAT_pwm_START            (10)
#define SOC_TZPC_DECPROT1STAT_pwm_END              (10)
#define SOC_TZPC_DECPROT1STAT_watchdog0_START      (12)
#define SOC_TZPC_DECPROT1STAT_watchdog0_END        (12)
#define SOC_TZPC_DECPROT1STAT_watchdog1_START      (13)
#define SOC_TZPC_DECPROT1STAT_watchdog1_END        (13)
#define SOC_TZPC_DECPROT1STAT_gpio0_START          (14)
#define SOC_TZPC_DECPROT1STAT_gpio0_END            (14)
#define SOC_TZPC_DECPROT1STAT_gpio1_START          (15)
#define SOC_TZPC_DECPROT1STAT_gpio1_END            (15)
#define SOC_TZPC_DECPROT1STAT_gpio2_START          (16)
#define SOC_TZPC_DECPROT1STAT_gpio2_END            (16)
#define SOC_TZPC_DECPROT1STAT_gpio3_START          (17)
#define SOC_TZPC_DECPROT1STAT_gpio3_END            (17)
#define SOC_TZPC_DECPROT1STAT_gpio4_START          (18)
#define SOC_TZPC_DECPROT1STAT_gpio4_END            (18)
#define SOC_TZPC_DECPROT1STAT_gpio5_START          (19)
#define SOC_TZPC_DECPROT1STAT_gpio5_END            (19)
#define SOC_TZPC_DECPROT1STAT_gpio6_START          (20)
#define SOC_TZPC_DECPROT1STAT_gpio6_END            (20)
#define SOC_TZPC_DECPROT1STAT_gpio7_START          (21)
#define SOC_TZPC_DECPROT1STAT_gpio7_END            (21)
#define SOC_TZPC_DECPROT1STAT_gpio8_START          (22)
#define SOC_TZPC_DECPROT1STAT_gpio8_END            (22)
#define SOC_TZPC_DECPROT1STAT_gpio9_START          (23)
#define SOC_TZPC_DECPROT1STAT_gpio9_END            (23)
#define SOC_TZPC_DECPROT1STAT_gpio10_START         (24)
#define SOC_TZPC_DECPROT1STAT_gpio10_END           (24)
#define SOC_TZPC_DECPROT1STAT_gpio11_START         (25)
#define SOC_TZPC_DECPROT1STAT_gpio11_END           (25)
#define SOC_TZPC_DECPROT1STAT_gpio12_START         (26)
#define SOC_TZPC_DECPROT1STAT_gpio12_END           (26)
#define SOC_TZPC_DECPROT1STAT_gpio13_START         (27)
#define SOC_TZPC_DECPROT1STAT_gpio13_END           (27)
#define SOC_TZPC_DECPROT1STAT_gpio14_START         (28)
#define SOC_TZPC_DECPROT1STAT_gpio14_END           (28)
#define SOC_TZPC_DECPROT1STAT_gpio15_START         (29)
#define SOC_TZPC_DECPROT1STAT_gpio15_END           (29)
#define SOC_TZPC_DECPROT1STAT_gpio16_START         (30)
#define SOC_TZPC_DECPROT1STAT_gpio16_END           (30)
#define SOC_TZPC_DECPROT1STAT_gpio17_START         (31)
#define SOC_TZPC_DECPROT1STAT_gpio17_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT1SET_UNION
 �ṹ˵��  : DECPROT1SET �Ĵ����ṹ���塣��ַƫ����:0x810����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ������λ�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 1;  /* bit[0] : IP��ȫ������λ��
                                                      0��IP��ȫ���Բ��䣻
                                                      1��IP��ȫ�����á�1���� */
        unsigned int  reserved_1    : 1;  /* bit[1] :  */
        unsigned int  timer9        : 1;  /* bit[2] :  */
        unsigned int  timer10       : 1;  /* bit[3] :  */
        unsigned int  timer11       : 1;  /* bit[4] :  */
        unsigned int  timer12       : 1;  /* bit[5] :  */
        unsigned int  pctrl_region1 : 1;  /* bit[6] :  */
        unsigned int  pctrl_region2 : 1;  /* bit[7] :  */
        unsigned int  pctrl_region3 : 1;  /* bit[8] :  */
        unsigned int  pctrl_region4 : 1;  /* bit[9] :  */
        unsigned int  pwm           : 1;  /* bit[10]:  */
        unsigned int  reserved_2    : 1;  /* bit[11]:  */
        unsigned int  watchdog0     : 1;  /* bit[12]:  */
        unsigned int  watchdog1     : 1;  /* bit[13]:  */
        unsigned int  gpio0         : 1;  /* bit[14]:  */
        unsigned int  gpio1         : 1;  /* bit[15]:  */
        unsigned int  gpio2         : 1;  /* bit[16]:  */
        unsigned int  gpio3         : 1;  /* bit[17]:  */
        unsigned int  gpio4         : 1;  /* bit[18]:  */
        unsigned int  gpio5         : 1;  /* bit[19]:  */
        unsigned int  gpio6         : 1;  /* bit[20]:  */
        unsigned int  gpio7         : 1;  /* bit[21]:  */
        unsigned int  gpio8         : 1;  /* bit[22]:  */
        unsigned int  gpio9         : 1;  /* bit[23]:  */
        unsigned int  gpio10        : 1;  /* bit[24]:  */
        unsigned int  gpio11        : 1;  /* bit[25]:  */
        unsigned int  gpio12        : 1;  /* bit[26]:  */
        unsigned int  gpio13        : 1;  /* bit[27]:  */
        unsigned int  gpio14        : 1;  /* bit[28]:  */
        unsigned int  gpio15        : 1;  /* bit[29]:  */
        unsigned int  gpio16        : 1;  /* bit[30]:  */
        unsigned int  gpio17        : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT1SET_UNION;
#endif
#define SOC_TZPC_DECPROT1SET_timer9_START         (2)
#define SOC_TZPC_DECPROT1SET_timer9_END           (2)
#define SOC_TZPC_DECPROT1SET_timer10_START        (3)
#define SOC_TZPC_DECPROT1SET_timer10_END          (3)
#define SOC_TZPC_DECPROT1SET_timer11_START        (4)
#define SOC_TZPC_DECPROT1SET_timer11_END          (4)
#define SOC_TZPC_DECPROT1SET_timer12_START        (5)
#define SOC_TZPC_DECPROT1SET_timer12_END          (5)
#define SOC_TZPC_DECPROT1SET_pctrl_region1_START  (6)
#define SOC_TZPC_DECPROT1SET_pctrl_region1_END    (6)
#define SOC_TZPC_DECPROT1SET_pctrl_region2_START  (7)
#define SOC_TZPC_DECPROT1SET_pctrl_region2_END    (7)
#define SOC_TZPC_DECPROT1SET_pctrl_region3_START  (8)
#define SOC_TZPC_DECPROT1SET_pctrl_region3_END    (8)
#define SOC_TZPC_DECPROT1SET_pctrl_region4_START  (9)
#define SOC_TZPC_DECPROT1SET_pctrl_region4_END    (9)
#define SOC_TZPC_DECPROT1SET_pwm_START            (10)
#define SOC_TZPC_DECPROT1SET_pwm_END              (10)
#define SOC_TZPC_DECPROT1SET_watchdog0_START      (12)
#define SOC_TZPC_DECPROT1SET_watchdog0_END        (12)
#define SOC_TZPC_DECPROT1SET_watchdog1_START      (13)
#define SOC_TZPC_DECPROT1SET_watchdog1_END        (13)
#define SOC_TZPC_DECPROT1SET_gpio0_START          (14)
#define SOC_TZPC_DECPROT1SET_gpio0_END            (14)
#define SOC_TZPC_DECPROT1SET_gpio1_START          (15)
#define SOC_TZPC_DECPROT1SET_gpio1_END            (15)
#define SOC_TZPC_DECPROT1SET_gpio2_START          (16)
#define SOC_TZPC_DECPROT1SET_gpio2_END            (16)
#define SOC_TZPC_DECPROT1SET_gpio3_START          (17)
#define SOC_TZPC_DECPROT1SET_gpio3_END            (17)
#define SOC_TZPC_DECPROT1SET_gpio4_START          (18)
#define SOC_TZPC_DECPROT1SET_gpio4_END            (18)
#define SOC_TZPC_DECPROT1SET_gpio5_START          (19)
#define SOC_TZPC_DECPROT1SET_gpio5_END            (19)
#define SOC_TZPC_DECPROT1SET_gpio6_START          (20)
#define SOC_TZPC_DECPROT1SET_gpio6_END            (20)
#define SOC_TZPC_DECPROT1SET_gpio7_START          (21)
#define SOC_TZPC_DECPROT1SET_gpio7_END            (21)
#define SOC_TZPC_DECPROT1SET_gpio8_START          (22)
#define SOC_TZPC_DECPROT1SET_gpio8_END            (22)
#define SOC_TZPC_DECPROT1SET_gpio9_START          (23)
#define SOC_TZPC_DECPROT1SET_gpio9_END            (23)
#define SOC_TZPC_DECPROT1SET_gpio10_START         (24)
#define SOC_TZPC_DECPROT1SET_gpio10_END           (24)
#define SOC_TZPC_DECPROT1SET_gpio11_START         (25)
#define SOC_TZPC_DECPROT1SET_gpio11_END           (25)
#define SOC_TZPC_DECPROT1SET_gpio12_START         (26)
#define SOC_TZPC_DECPROT1SET_gpio12_END           (26)
#define SOC_TZPC_DECPROT1SET_gpio13_START         (27)
#define SOC_TZPC_DECPROT1SET_gpio13_END           (27)
#define SOC_TZPC_DECPROT1SET_gpio14_START         (28)
#define SOC_TZPC_DECPROT1SET_gpio14_END           (28)
#define SOC_TZPC_DECPROT1SET_gpio15_START         (29)
#define SOC_TZPC_DECPROT1SET_gpio15_END           (29)
#define SOC_TZPC_DECPROT1SET_gpio16_START         (30)
#define SOC_TZPC_DECPROT1SET_gpio16_END           (30)
#define SOC_TZPC_DECPROT1SET_gpio17_START         (31)
#define SOC_TZPC_DECPROT1SET_gpio17_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT1CLR_UNION
 �ṹ˵��  : DECPROT1CLR �Ĵ����ṹ���塣��ַƫ����:0x814����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ��������Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 1;  /* bit[0] : IP��ȫ�������㣺
                                                      0��IP��ȫ���Բ��䣻
                                                      1��IP��ȫ�����á�0���� */
        unsigned int  reserved_1    : 1;  /* bit[1] :  */
        unsigned int  timer9        : 1;  /* bit[2] :  */
        unsigned int  timer10       : 1;  /* bit[3] :  */
        unsigned int  timer11       : 1;  /* bit[4] :  */
        unsigned int  timer12       : 1;  /* bit[5] :  */
        unsigned int  pctrl_region1 : 1;  /* bit[6] :  */
        unsigned int  pctrl_region2 : 1;  /* bit[7] :  */
        unsigned int  pctrl_region3 : 1;  /* bit[8] :  */
        unsigned int  pctrl_region4 : 1;  /* bit[9] :  */
        unsigned int  pwm           : 1;  /* bit[10]:  */
        unsigned int  reserved_2    : 1;  /* bit[11]:  */
        unsigned int  watchdog0     : 1;  /* bit[12]:  */
        unsigned int  watchdog1     : 1;  /* bit[13]:  */
        unsigned int  gpio0         : 1;  /* bit[14]:  */
        unsigned int  gpio1         : 1;  /* bit[15]:  */
        unsigned int  gpio2         : 1;  /* bit[16]:  */
        unsigned int  gpio3         : 1;  /* bit[17]:  */
        unsigned int  gpio4         : 1;  /* bit[18]:  */
        unsigned int  gpio5         : 1;  /* bit[19]:  */
        unsigned int  gpio6         : 1;  /* bit[20]:  */
        unsigned int  gpio7         : 1;  /* bit[21]:  */
        unsigned int  gpio8         : 1;  /* bit[22]:  */
        unsigned int  gpio9         : 1;  /* bit[23]:  */
        unsigned int  gpio10        : 1;  /* bit[24]:  */
        unsigned int  gpio11        : 1;  /* bit[25]:  */
        unsigned int  gpio12        : 1;  /* bit[26]:  */
        unsigned int  gpio13        : 1;  /* bit[27]:  */
        unsigned int  gpio14        : 1;  /* bit[28]:  */
        unsigned int  gpio15        : 1;  /* bit[29]:  */
        unsigned int  gpio16        : 1;  /* bit[30]:  */
        unsigned int  gpio17        : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT1CLR_UNION;
#endif
#define SOC_TZPC_DECPROT1CLR_timer9_START         (2)
#define SOC_TZPC_DECPROT1CLR_timer9_END           (2)
#define SOC_TZPC_DECPROT1CLR_timer10_START        (3)
#define SOC_TZPC_DECPROT1CLR_timer10_END          (3)
#define SOC_TZPC_DECPROT1CLR_timer11_START        (4)
#define SOC_TZPC_DECPROT1CLR_timer11_END          (4)
#define SOC_TZPC_DECPROT1CLR_timer12_START        (5)
#define SOC_TZPC_DECPROT1CLR_timer12_END          (5)
#define SOC_TZPC_DECPROT1CLR_pctrl_region1_START  (6)
#define SOC_TZPC_DECPROT1CLR_pctrl_region1_END    (6)
#define SOC_TZPC_DECPROT1CLR_pctrl_region2_START  (7)
#define SOC_TZPC_DECPROT1CLR_pctrl_region2_END    (7)
#define SOC_TZPC_DECPROT1CLR_pctrl_region3_START  (8)
#define SOC_TZPC_DECPROT1CLR_pctrl_region3_END    (8)
#define SOC_TZPC_DECPROT1CLR_pctrl_region4_START  (9)
#define SOC_TZPC_DECPROT1CLR_pctrl_region4_END    (9)
#define SOC_TZPC_DECPROT1CLR_pwm_START            (10)
#define SOC_TZPC_DECPROT1CLR_pwm_END              (10)
#define SOC_TZPC_DECPROT1CLR_watchdog0_START      (12)
#define SOC_TZPC_DECPROT1CLR_watchdog0_END        (12)
#define SOC_TZPC_DECPROT1CLR_watchdog1_START      (13)
#define SOC_TZPC_DECPROT1CLR_watchdog1_END        (13)
#define SOC_TZPC_DECPROT1CLR_gpio0_START          (14)
#define SOC_TZPC_DECPROT1CLR_gpio0_END            (14)
#define SOC_TZPC_DECPROT1CLR_gpio1_START          (15)
#define SOC_TZPC_DECPROT1CLR_gpio1_END            (15)
#define SOC_TZPC_DECPROT1CLR_gpio2_START          (16)
#define SOC_TZPC_DECPROT1CLR_gpio2_END            (16)
#define SOC_TZPC_DECPROT1CLR_gpio3_START          (17)
#define SOC_TZPC_DECPROT1CLR_gpio3_END            (17)
#define SOC_TZPC_DECPROT1CLR_gpio4_START          (18)
#define SOC_TZPC_DECPROT1CLR_gpio4_END            (18)
#define SOC_TZPC_DECPROT1CLR_gpio5_START          (19)
#define SOC_TZPC_DECPROT1CLR_gpio5_END            (19)
#define SOC_TZPC_DECPROT1CLR_gpio6_START          (20)
#define SOC_TZPC_DECPROT1CLR_gpio6_END            (20)
#define SOC_TZPC_DECPROT1CLR_gpio7_START          (21)
#define SOC_TZPC_DECPROT1CLR_gpio7_END            (21)
#define SOC_TZPC_DECPROT1CLR_gpio8_START          (22)
#define SOC_TZPC_DECPROT1CLR_gpio8_END            (22)
#define SOC_TZPC_DECPROT1CLR_gpio9_START          (23)
#define SOC_TZPC_DECPROT1CLR_gpio9_END            (23)
#define SOC_TZPC_DECPROT1CLR_gpio10_START         (24)
#define SOC_TZPC_DECPROT1CLR_gpio10_END           (24)
#define SOC_TZPC_DECPROT1CLR_gpio11_START         (25)
#define SOC_TZPC_DECPROT1CLR_gpio11_END           (25)
#define SOC_TZPC_DECPROT1CLR_gpio12_START         (26)
#define SOC_TZPC_DECPROT1CLR_gpio12_END           (26)
#define SOC_TZPC_DECPROT1CLR_gpio13_START         (27)
#define SOC_TZPC_DECPROT1CLR_gpio13_END           (27)
#define SOC_TZPC_DECPROT1CLR_gpio14_START         (28)
#define SOC_TZPC_DECPROT1CLR_gpio14_END           (28)
#define SOC_TZPC_DECPROT1CLR_gpio15_START         (29)
#define SOC_TZPC_DECPROT1CLR_gpio15_END           (29)
#define SOC_TZPC_DECPROT1CLR_gpio16_START         (30)
#define SOC_TZPC_DECPROT1CLR_gpio16_END           (30)
#define SOC_TZPC_DECPROT1CLR_gpio17_START         (31)
#define SOC_TZPC_DECPROT1CLR_gpio17_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT2STAT_UNION
 �ṹ˵��  : DECPROT2STAT �Ĵ����ṹ���塣��ַƫ����:0x818����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ����״̬�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio18   : 1;  /* bit[0] : gpio18 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio19   : 1;  /* bit[1] : gpio19 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio20   : 1;  /* bit[2] : gpio20 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  gpio21   : 1;  /* bit[3] : gpio21 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  reserved_0: 1;  /* bit[4] : ������ */
        unsigned int  reserved_1: 1;  /* bit[5] : ������ */
        unsigned int  reserved_2: 1;  /* bit[6] : ������ */
        unsigned int  reserved_3: 1;  /* bit[7] : ������ */
        unsigned int  reserved_4: 1;  /* bit[8] : ������ */
        unsigned int  reserved_5: 1;  /* bit[9] : ������ */
        unsigned int  reserved_6: 1;  /* bit[10]: ������ */
        unsigned int  reserved_7: 1;  /* bit[11]: ������ */
        unsigned int  reserved_8: 1;  /* bit[12]: ������ */
        unsigned int  reserved_9: 1;  /* bit[13]: ������ */
        unsigned int  reserved_10: 1;  /* bit[14]: ������ */
        unsigned int  reserved_11: 1;  /* bit[15]: ������ */
        unsigned int  reserved_12: 1;  /* bit[16]: ������ */
        unsigned int  reserved_13: 1;  /* bit[17]: ������ */
        unsigned int  reserved_14: 1;  /* bit[18]: ������ */
        unsigned int  reserved_15: 1;  /* bit[19]: ������ */
        unsigned int  reserved_16: 1;  /* bit[20]: ������ */
        unsigned int  reserved_17: 1;  /* bit[21]: ������ */
        unsigned int  reserved_18: 1;  /* bit[22]: ������ */
        unsigned int  reserved_19: 1;  /* bit[23]: ������ */
        unsigned int  reserved_20: 1;  /* bit[24]: ������ */
        unsigned int  reserved_21: 1;  /* bit[25]: ������ */
        unsigned int  reserved_22: 1;  /* bit[26]: ������ */
        unsigned int  reserved_23: 1;  /* bit[27]: ������ */
        unsigned int  reserved_24: 1;  /* bit[28]: ������ */
        unsigned int  reserved_25: 1;  /* bit[29]: ������ */
        unsigned int  reserved_26: 1;  /* bit[30]: ������ */
        unsigned int  reserved_27: 1;  /* bit[31]: ������ */
    } reg;
} SOC_TZPC_DECPROT2STAT_UNION;
#endif
#define SOC_TZPC_DECPROT2STAT_gpio18_START    (0)
#define SOC_TZPC_DECPROT2STAT_gpio18_END      (0)
#define SOC_TZPC_DECPROT2STAT_gpio19_START    (1)
#define SOC_TZPC_DECPROT2STAT_gpio19_END      (1)
#define SOC_TZPC_DECPROT2STAT_gpio20_START    (2)
#define SOC_TZPC_DECPROT2STAT_gpio20_END      (2)
#define SOC_TZPC_DECPROT2STAT_gpio21_START    (3)
#define SOC_TZPC_DECPROT2STAT_gpio21_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT2SET_UNION
 �ṹ˵��  : DECPROT2SET �Ĵ����ṹ���塣��ַƫ����:0x81C����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ������λ�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio18   : 1;  /* bit[0] : IP��ȫ������λ��
                                                 0��IP��ȫ���Բ��䣻
                                                 1��IP��ȫ�����á�1���� */
        unsigned int  gpio19   : 1;  /* bit[1] :  */
        unsigned int  gpio20   : 1;  /* bit[2] :  */
        unsigned int  gpio21   : 1;  /* bit[3] :  */
        unsigned int  reserved_0: 1;  /* bit[4] :  */
        unsigned int  reserved_1: 1;  /* bit[5] :  */
        unsigned int  reserved_2: 1;  /* bit[6] :  */
        unsigned int  reserved_3: 1;  /* bit[7] :  */
        unsigned int  reserved_4: 1;  /* bit[8] :  */
        unsigned int  reserved_5: 1;  /* bit[9] :  */
        unsigned int  reserved_6: 1;  /* bit[10]:  */
        unsigned int  reserved_7: 1;  /* bit[11]:  */
        unsigned int  reserved_8: 1;  /* bit[12]:  */
        unsigned int  reserved_9: 1;  /* bit[13]:  */
        unsigned int  reserved_10: 1;  /* bit[14]:  */
        unsigned int  reserved_11: 1;  /* bit[15]:  */
        unsigned int  reserved_12: 1;  /* bit[16]:  */
        unsigned int  reserved_13: 1;  /* bit[17]:  */
        unsigned int  reserved_14: 1;  /* bit[18]:  */
        unsigned int  reserved_15: 1;  /* bit[19]:  */
        unsigned int  reserved_16: 1;  /* bit[20]:  */
        unsigned int  reserved_17: 1;  /* bit[21]:  */
        unsigned int  reserved_18: 1;  /* bit[22]:  */
        unsigned int  reserved_19: 1;  /* bit[23]:  */
        unsigned int  reserved_20: 1;  /* bit[24]:  */
        unsigned int  reserved_21: 1;  /* bit[25]:  */
        unsigned int  reserved_22: 1;  /* bit[26]:  */
        unsigned int  reserved_23: 1;  /* bit[27]:  */
        unsigned int  reserved_24: 1;  /* bit[28]:  */
        unsigned int  reserved_25: 1;  /* bit[29]:  */
        unsigned int  reserved_26: 1;  /* bit[30]:  */
        unsigned int  reserved_27: 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT2SET_UNION;
#endif
#define SOC_TZPC_DECPROT2SET_gpio18_START    (0)
#define SOC_TZPC_DECPROT2SET_gpio18_END      (0)
#define SOC_TZPC_DECPROT2SET_gpio19_START    (1)
#define SOC_TZPC_DECPROT2SET_gpio19_END      (1)
#define SOC_TZPC_DECPROT2SET_gpio20_START    (2)
#define SOC_TZPC_DECPROT2SET_gpio20_END      (2)
#define SOC_TZPC_DECPROT2SET_gpio21_START    (3)
#define SOC_TZPC_DECPROT2SET_gpio21_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT2CLR_UNION
 �ṹ˵��  : DECPROT2CLR �Ĵ����ṹ���塣��ַƫ����:0x820����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ��������Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio18   : 1;  /* bit[0] : IP��ȫ�������㣺
                                                 0��IP��ȫ���Բ��䣻
                                                 1��IP��ȫ�����á�0���� */
        unsigned int  gpio19   : 1;  /* bit[1] :  */
        unsigned int  gpio20   : 1;  /* bit[2] :  */
        unsigned int  gpio21   : 1;  /* bit[3] :  */
        unsigned int  reserved_0: 1;  /* bit[4] :  */
        unsigned int  reserved_1: 1;  /* bit[5] :  */
        unsigned int  reserved_2: 1;  /* bit[6] :  */
        unsigned int  reserved_3: 1;  /* bit[7] :  */
        unsigned int  reserved_4: 1;  /* bit[8] :  */
        unsigned int  reserved_5: 1;  /* bit[9] :  */
        unsigned int  reserved_6: 1;  /* bit[10]:  */
        unsigned int  reserved_7: 1;  /* bit[11]:  */
        unsigned int  reserved_8: 1;  /* bit[12]:  */
        unsigned int  reserved_9: 1;  /* bit[13]:  */
        unsigned int  reserved_10: 1;  /* bit[14]:  */
        unsigned int  reserved_11: 1;  /* bit[15]:  */
        unsigned int  reserved_12: 1;  /* bit[16]:  */
        unsigned int  reserved_13: 1;  /* bit[17]:  */
        unsigned int  reserved_14: 1;  /* bit[18]:  */
        unsigned int  reserved_15: 1;  /* bit[19]:  */
        unsigned int  reserved_16: 1;  /* bit[20]:  */
        unsigned int  reserved_17: 1;  /* bit[21]:  */
        unsigned int  reserved_18: 1;  /* bit[22]:  */
        unsigned int  reserved_19: 1;  /* bit[23]:  */
        unsigned int  reserved_20: 1;  /* bit[24]:  */
        unsigned int  reserved_21: 1;  /* bit[25]:  */
        unsigned int  reserved_22: 1;  /* bit[26]:  */
        unsigned int  reserved_23: 1;  /* bit[27]:  */
        unsigned int  reserved_24: 1;  /* bit[28]:  */
        unsigned int  reserved_25: 1;  /* bit[29]:  */
        unsigned int  reserved_26: 1;  /* bit[30]:  */
        unsigned int  reserved_27: 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT2CLR_UNION;
#endif
#define SOC_TZPC_DECPROT2CLR_gpio18_START    (0)
#define SOC_TZPC_DECPROT2CLR_gpio18_END      (0)
#define SOC_TZPC_DECPROT2CLR_gpio19_START    (1)
#define SOC_TZPC_DECPROT2CLR_gpio19_END      (1)
#define SOC_TZPC_DECPROT2CLR_gpio20_START    (2)
#define SOC_TZPC_DECPROT2CLR_gpio20_END      (2)
#define SOC_TZPC_DECPROT2CLR_gpio21_START    (3)
#define SOC_TZPC_DECPROT2CLR_gpio21_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT3STAT_UNION
 �ṹ˵��  : DECPROT3STAT �Ĵ����ṹ���塣��ַƫ����:0x824����ֵ:0x00030303�����:32
 �Ĵ���˵��: IP��ȫ����״̬�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vdec_firewall  : 8;  /* bit[0-7]  : bit0��firewall��ʹ�ܿ��ƣ�Ĭ��ʹ�ܡ�
                                                          bit1��firewall����ԽȨ�Ƿ��ϱ�error��Ĭ���ϱ���
                                                          bit2��vdec slv�İ�ȫ���ԣ�Ĭ���ǰ�ȫ���ԡ�
                                                          bit[5:3]��������
                                                          bit6��Ĭ��Ϊ0��
                                                          0: VDEC���ڰ�ȫ̬����vdec���ڰ�ȫ̬ʱ�����ڲ��ؼ��Ĵ������ܹ����ǰ�ȫos���ʡ�
                                                          1��VDEC���ڷǰ�ȫ̬����vdec���ڷǰ�ȫ̬ʱ�����ڲ����мĴ����ܹ����ǰ�ȫos\��ȫos���ʡ�
                                                          bit7������VDEC������ǿ��ת��Ϊ��ȫ����ʹ��λ��Ĭ��Ϊ0����ʹ�ܣ������ù��ܣ���ʼ��ʱ��Ҫ����Ϊ1���� */
        unsigned int  venc_firewall  : 8;  /* bit[8-15] : bit0��firewall��ʹ�ܿ��ƣ�Ĭ��ʹ�ܡ�
                                                          bit1��firewall����ԽȨ�Ƿ��ϱ�error��Ĭ���ϱ���
                                                          bit2��venc slv�İ�ȫ���ԣ�Ĭ���ǰ�ȫ���ԡ�
                                                          bit[7:3]�������� */
        unsigned int  hkmem_firewall : 8;  /* bit[16-23]: bit0��firewall��ʹ�ܿ��ƣ�Ĭ��ʹ�ܡ�
                                                          bit1��firewall����ԽȨ�Ƿ��ϱ�error��Ĭ���ϱ���
                                                          bit2��hkmem slv�İ�ȫ���ԣ�Ĭ���ǰ�ȫ���ԡ�
                                                          bit[7:3]�������� */
        unsigned int  g3d            : 1;  /* bit[24]   : g3d slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  reserved_0     : 1;  /* bit[25]   : ������ */
        unsigned int  emmc0          : 1;  /* bit[26]   : emmc0 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  emmc1          : 1;  /* bit[27]   : emmc1 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  sd30           : 1;  /* bit[28]   : sd30 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  sdio0          : 1;  /* bit[29]   : sdio0 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  sdio1          : 1;  /* bit[30]   : sdio1 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  reserved_1     : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_TZPC_DECPROT3STAT_UNION;
#endif
#define SOC_TZPC_DECPROT3STAT_vdec_firewall_START   (0)
#define SOC_TZPC_DECPROT3STAT_vdec_firewall_END     (7)
#define SOC_TZPC_DECPROT3STAT_venc_firewall_START   (8)
#define SOC_TZPC_DECPROT3STAT_venc_firewall_END     (15)
#define SOC_TZPC_DECPROT3STAT_hkmem_firewall_START  (16)
#define SOC_TZPC_DECPROT3STAT_hkmem_firewall_END    (23)
#define SOC_TZPC_DECPROT3STAT_g3d_START             (24)
#define SOC_TZPC_DECPROT3STAT_g3d_END               (24)
#define SOC_TZPC_DECPROT3STAT_emmc0_START           (26)
#define SOC_TZPC_DECPROT3STAT_emmc0_END             (26)
#define SOC_TZPC_DECPROT3STAT_emmc1_START           (27)
#define SOC_TZPC_DECPROT3STAT_emmc1_END             (27)
#define SOC_TZPC_DECPROT3STAT_sd30_START            (28)
#define SOC_TZPC_DECPROT3STAT_sd30_END              (28)
#define SOC_TZPC_DECPROT3STAT_sdio0_START           (29)
#define SOC_TZPC_DECPROT3STAT_sdio0_END             (29)
#define SOC_TZPC_DECPROT3STAT_sdio1_START           (30)
#define SOC_TZPC_DECPROT3STAT_sdio1_END             (30)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT3SET_UNION
 �ṹ˵��  : DECPROT3SET �Ĵ����ṹ���塣��ַƫ����:0x828����ֵ:0x00030303�����:32
 �Ĵ���˵��: IP��ȫ������λ�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vdec_firewall  : 8;  /* bit[0-7]  : IP��ȫ������λ��
                                                          0��IP��ȫ���Բ��䣻
                                                          1��IP��ȫ�����á�1���� */
        unsigned int  venc_firewall  : 8;  /* bit[8-15] :  */
        unsigned int  hkmem_firewall : 8;  /* bit[16-23]:  */
        unsigned int  g3d            : 1;  /* bit[24]   :  */
        unsigned int  reserved_0     : 1;  /* bit[25]   :  */
        unsigned int  emmc0          : 1;  /* bit[26]   :  */
        unsigned int  emmc1          : 1;  /* bit[27]   :  */
        unsigned int  sd30           : 1;  /* bit[28]   :  */
        unsigned int  sdio0          : 1;  /* bit[29]   :  */
        unsigned int  sdio1          : 1;  /* bit[30]   :  */
        unsigned int  reserved_1     : 1;  /* bit[31]   :  */
    } reg;
} SOC_TZPC_DECPROT3SET_UNION;
#endif
#define SOC_TZPC_DECPROT3SET_vdec_firewall_START   (0)
#define SOC_TZPC_DECPROT3SET_vdec_firewall_END     (7)
#define SOC_TZPC_DECPROT3SET_venc_firewall_START   (8)
#define SOC_TZPC_DECPROT3SET_venc_firewall_END     (15)
#define SOC_TZPC_DECPROT3SET_hkmem_firewall_START  (16)
#define SOC_TZPC_DECPROT3SET_hkmem_firewall_END    (23)
#define SOC_TZPC_DECPROT3SET_g3d_START             (24)
#define SOC_TZPC_DECPROT3SET_g3d_END               (24)
#define SOC_TZPC_DECPROT3SET_emmc0_START           (26)
#define SOC_TZPC_DECPROT3SET_emmc0_END             (26)
#define SOC_TZPC_DECPROT3SET_emmc1_START           (27)
#define SOC_TZPC_DECPROT3SET_emmc1_END             (27)
#define SOC_TZPC_DECPROT3SET_sd30_START            (28)
#define SOC_TZPC_DECPROT3SET_sd30_END              (28)
#define SOC_TZPC_DECPROT3SET_sdio0_START           (29)
#define SOC_TZPC_DECPROT3SET_sdio0_END             (29)
#define SOC_TZPC_DECPROT3SET_sdio1_START           (30)
#define SOC_TZPC_DECPROT3SET_sdio1_END             (30)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT3CLR_UNION
 �ṹ˵��  : DECPROT3CLR �Ĵ����ṹ���塣��ַƫ����:0x82C����ֵ:0x00030303�����:32
 �Ĵ���˵��: IP��ȫ��������Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vdec_firewall  : 8;  /* bit[0-7]  : IP��ȫ�������㣺
                                                          0��IP��ȫ���Բ��䣻
                                                          1��IP��ȫ�����á�0���� */
        unsigned int  venc_firewall  : 8;  /* bit[8-15] :  */
        unsigned int  hkmem_firewall : 8;  /* bit[16-23]:  */
        unsigned int  g3d            : 1;  /* bit[24]   :  */
        unsigned int  reserved_0     : 1;  /* bit[25]   :  */
        unsigned int  emmc0          : 1;  /* bit[26]   :  */
        unsigned int  emmc1          : 1;  /* bit[27]   :  */
        unsigned int  sd30           : 1;  /* bit[28]   :  */
        unsigned int  sdio0          : 1;  /* bit[29]   :  */
        unsigned int  sdio1          : 1;  /* bit[30]   :  */
        unsigned int  reserved_1     : 1;  /* bit[31]   :  */
    } reg;
} SOC_TZPC_DECPROT3CLR_UNION;
#endif
#define SOC_TZPC_DECPROT3CLR_vdec_firewall_START   (0)
#define SOC_TZPC_DECPROT3CLR_vdec_firewall_END     (7)
#define SOC_TZPC_DECPROT3CLR_venc_firewall_START   (8)
#define SOC_TZPC_DECPROT3CLR_venc_firewall_END     (15)
#define SOC_TZPC_DECPROT3CLR_hkmem_firewall_START  (16)
#define SOC_TZPC_DECPROT3CLR_hkmem_firewall_END    (23)
#define SOC_TZPC_DECPROT3CLR_g3d_START             (24)
#define SOC_TZPC_DECPROT3CLR_g3d_END               (24)
#define SOC_TZPC_DECPROT3CLR_emmc0_START           (26)
#define SOC_TZPC_DECPROT3CLR_emmc0_END             (26)
#define SOC_TZPC_DECPROT3CLR_emmc1_START           (27)
#define SOC_TZPC_DECPROT3CLR_emmc1_END             (27)
#define SOC_TZPC_DECPROT3CLR_sd30_START            (28)
#define SOC_TZPC_DECPROT3CLR_sd30_END              (28)
#define SOC_TZPC_DECPROT3CLR_sdio0_START           (29)
#define SOC_TZPC_DECPROT3CLR_sdio0_END             (29)
#define SOC_TZPC_DECPROT3CLR_sdio1_START           (30)
#define SOC_TZPC_DECPROT3CLR_sdio1_END             (30)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT4STAT_UNION
 �ṹ˵��  : DECPROT4STAT �Ĵ����ṹ���塣��ַƫ����:0x830����ֵ:0x00000001�����:32
 �Ĵ���˵��: IP��ȫ����״̬�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socp       : 1;  /* bit[0] : socp slv�ϵ�Ĭ��Ϊ�ǰ�ȫ���ԣ�socp ip����߱��˰�ȫ�ǰ�ȫ���ԣ�����Ҫtzpc���а�ȫ�ǰ�ȫ���ơ� */
        unsigned int  usb3otg    : 1;  /* bit[1] : USB3OTG���ڲ��Ĵ����� slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  usb3otg_bc : 1;  /* bit[2] : USB3OTG ��BC�Ĵ����� slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  perf_stat  : 1;  /* bit[3] : perf_stat slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  reserved_0 : 1;  /* bit[4] : ������ */
        unsigned int  ipcns      : 1;  /* bit[5] : ipcns slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  ipc        : 1;  /* bit[6] : ipc slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  ioc        : 1;  /* bit[7] : ioc slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  vcodecbus  : 1;  /* bit[8] : VCODECBUS(0xE8920000~0xE895FFFF) slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  reserved_1 : 1;  /* bit[9] : ������ */
        unsigned int  hkadc_ssi  : 1;  /* bit[10]: hkadcssi slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  codec_ssi  : 1;  /* bit[11]: codecssi slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  reserved_2 : 1;  /* bit[12]: ������ */
        unsigned int  ipc_mdm    : 1;  /* bit[13]: ipc_mdm slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  uart0      : 1;  /* bit[14]: uart0 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  uart1      : 1;  /* bit[15]: uart1 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  uart2      : 1;  /* bit[16]: uart2 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  uart4      : 1;  /* bit[17]: uart4 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  uart5      : 1;  /* bit[18]: uart5 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  spi1       : 1;  /* bit[19]: spi1 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  i2c3       : 1;  /* bit[20]: i2c3 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  i2c4       : 1;  /* bit[21]: i2c4 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  ddrc       : 1;  /* bit[22]: DDRC�ڲ��ؼ��Ĵ�������ʹ�ܿ��ƣ�ʹ�����󽫲������ùؼ��Ĵ�����Ĭ��Ϊ0����ʹ������ */
        unsigned int  bisr       : 1;  /* bit[23]: bisr slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  reserved_3 : 1;  /* bit[24]: ������ */
        unsigned int  reserved_4 : 1;  /* bit[25]: ������ */
        unsigned int  reserved_5 : 1;  /* bit[26]: ������ */
        unsigned int  reserved_6 : 1;  /* bit[27]: ������ */
        unsigned int  reserved_7 : 1;  /* bit[28]: ������ */
        unsigned int  reserved_8 : 1;  /* bit[29]: ������ */
        unsigned int  reserved_9 : 1;  /* bit[30]: ������ */
        unsigned int  reserved_10: 1;  /* bit[31]: ������ */
    } reg;
} SOC_TZPC_DECPROT4STAT_UNION;
#endif
#define SOC_TZPC_DECPROT4STAT_socp_START        (0)
#define SOC_TZPC_DECPROT4STAT_socp_END          (0)
#define SOC_TZPC_DECPROT4STAT_usb3otg_START     (1)
#define SOC_TZPC_DECPROT4STAT_usb3otg_END       (1)
#define SOC_TZPC_DECPROT4STAT_usb3otg_bc_START  (2)
#define SOC_TZPC_DECPROT4STAT_usb3otg_bc_END    (2)
#define SOC_TZPC_DECPROT4STAT_perf_stat_START   (3)
#define SOC_TZPC_DECPROT4STAT_perf_stat_END     (3)
#define SOC_TZPC_DECPROT4STAT_ipcns_START       (5)
#define SOC_TZPC_DECPROT4STAT_ipcns_END         (5)
#define SOC_TZPC_DECPROT4STAT_ipc_START         (6)
#define SOC_TZPC_DECPROT4STAT_ipc_END           (6)
#define SOC_TZPC_DECPROT4STAT_ioc_START         (7)
#define SOC_TZPC_DECPROT4STAT_ioc_END           (7)
#define SOC_TZPC_DECPROT4STAT_vcodecbus_START   (8)
#define SOC_TZPC_DECPROT4STAT_vcodecbus_END     (8)
#define SOC_TZPC_DECPROT4STAT_hkadc_ssi_START   (10)
#define SOC_TZPC_DECPROT4STAT_hkadc_ssi_END     (10)
#define SOC_TZPC_DECPROT4STAT_codec_ssi_START   (11)
#define SOC_TZPC_DECPROT4STAT_codec_ssi_END     (11)
#define SOC_TZPC_DECPROT4STAT_ipc_mdm_START     (13)
#define SOC_TZPC_DECPROT4STAT_ipc_mdm_END       (13)
#define SOC_TZPC_DECPROT4STAT_uart0_START       (14)
#define SOC_TZPC_DECPROT4STAT_uart0_END         (14)
#define SOC_TZPC_DECPROT4STAT_uart1_START       (15)
#define SOC_TZPC_DECPROT4STAT_uart1_END         (15)
#define SOC_TZPC_DECPROT4STAT_uart2_START       (16)
#define SOC_TZPC_DECPROT4STAT_uart2_END         (16)
#define SOC_TZPC_DECPROT4STAT_uart4_START       (17)
#define SOC_TZPC_DECPROT4STAT_uart4_END         (17)
#define SOC_TZPC_DECPROT4STAT_uart5_START       (18)
#define SOC_TZPC_DECPROT4STAT_uart5_END         (18)
#define SOC_TZPC_DECPROT4STAT_spi1_START        (19)
#define SOC_TZPC_DECPROT4STAT_spi1_END          (19)
#define SOC_TZPC_DECPROT4STAT_i2c3_START        (20)
#define SOC_TZPC_DECPROT4STAT_i2c3_END          (20)
#define SOC_TZPC_DECPROT4STAT_i2c4_START        (21)
#define SOC_TZPC_DECPROT4STAT_i2c4_END          (21)
#define SOC_TZPC_DECPROT4STAT_ddrc_START        (22)
#define SOC_TZPC_DECPROT4STAT_ddrc_END          (22)
#define SOC_TZPC_DECPROT4STAT_bisr_START        (23)
#define SOC_TZPC_DECPROT4STAT_bisr_END          (23)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT4SET_UNION
 �ṹ˵��  : DECPROT4SET �Ĵ����ṹ���塣��ַƫ����:0x834����ֵ:0x00000001�����:32
 �Ĵ���˵��: IP��ȫ������λ�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socp       : 1;  /* bit[0] : IP��ȫ������λ��
                                                   0��IP��ȫ���Բ��䣻
                                                   1��IP��ȫ�����á�1���� */
        unsigned int  usb3otg    : 1;  /* bit[1] :  */
        unsigned int  usb3otg_bc : 1;  /* bit[2] :  */
        unsigned int  perf_stat  : 1;  /* bit[3] :  */
        unsigned int  reserved_0 : 1;  /* bit[4] :  */
        unsigned int  ipcns      : 1;  /* bit[5] :  */
        unsigned int  ipc        : 1;  /* bit[6] :  */
        unsigned int  ioc        : 1;  /* bit[7] :  */
        unsigned int  vcodecbus  : 1;  /* bit[8] :  */
        unsigned int  reserved_1 : 1;  /* bit[9] :  */
        unsigned int  hkadc_ssi  : 1;  /* bit[10]:  */
        unsigned int  codec_ssi  : 1;  /* bit[11]:  */
        unsigned int  reserved_2 : 1;  /* bit[12]:  */
        unsigned int  ipc_mdm    : 1;  /* bit[13]:  */
        unsigned int  uart0      : 1;  /* bit[14]:  */
        unsigned int  uart1      : 1;  /* bit[15]:  */
        unsigned int  uart2      : 1;  /* bit[16]:  */
        unsigned int  uart4      : 1;  /* bit[17]:  */
        unsigned int  uart5      : 1;  /* bit[18]:  */
        unsigned int  spi1       : 1;  /* bit[19]:  */
        unsigned int  i2c3       : 1;  /* bit[20]:  */
        unsigned int  i2c4       : 1;  /* bit[21]:  */
        unsigned int  ddrc       : 1;  /* bit[22]:  */
        unsigned int  bisr       : 1;  /* bit[23]:  */
        unsigned int  reserved_3 : 1;  /* bit[24]:  */
        unsigned int  reserved_4 : 1;  /* bit[25]:  */
        unsigned int  reserved_5 : 1;  /* bit[26]:  */
        unsigned int  reserved_6 : 1;  /* bit[27]:  */
        unsigned int  reserved_7 : 1;  /* bit[28]:  */
        unsigned int  reserved_8 : 1;  /* bit[29]:  */
        unsigned int  reserved_9 : 1;  /* bit[30]:  */
        unsigned int  reserved_10: 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT4SET_UNION;
#endif
#define SOC_TZPC_DECPROT4SET_socp_START        (0)
#define SOC_TZPC_DECPROT4SET_socp_END          (0)
#define SOC_TZPC_DECPROT4SET_usb3otg_START     (1)
#define SOC_TZPC_DECPROT4SET_usb3otg_END       (1)
#define SOC_TZPC_DECPROT4SET_usb3otg_bc_START  (2)
#define SOC_TZPC_DECPROT4SET_usb3otg_bc_END    (2)
#define SOC_TZPC_DECPROT4SET_perf_stat_START   (3)
#define SOC_TZPC_DECPROT4SET_perf_stat_END     (3)
#define SOC_TZPC_DECPROT4SET_ipcns_START       (5)
#define SOC_TZPC_DECPROT4SET_ipcns_END         (5)
#define SOC_TZPC_DECPROT4SET_ipc_START         (6)
#define SOC_TZPC_DECPROT4SET_ipc_END           (6)
#define SOC_TZPC_DECPROT4SET_ioc_START         (7)
#define SOC_TZPC_DECPROT4SET_ioc_END           (7)
#define SOC_TZPC_DECPROT4SET_vcodecbus_START   (8)
#define SOC_TZPC_DECPROT4SET_vcodecbus_END     (8)
#define SOC_TZPC_DECPROT4SET_hkadc_ssi_START   (10)
#define SOC_TZPC_DECPROT4SET_hkadc_ssi_END     (10)
#define SOC_TZPC_DECPROT4SET_codec_ssi_START   (11)
#define SOC_TZPC_DECPROT4SET_codec_ssi_END     (11)
#define SOC_TZPC_DECPROT4SET_ipc_mdm_START     (13)
#define SOC_TZPC_DECPROT4SET_ipc_mdm_END       (13)
#define SOC_TZPC_DECPROT4SET_uart0_START       (14)
#define SOC_TZPC_DECPROT4SET_uart0_END         (14)
#define SOC_TZPC_DECPROT4SET_uart1_START       (15)
#define SOC_TZPC_DECPROT4SET_uart1_END         (15)
#define SOC_TZPC_DECPROT4SET_uart2_START       (16)
#define SOC_TZPC_DECPROT4SET_uart2_END         (16)
#define SOC_TZPC_DECPROT4SET_uart4_START       (17)
#define SOC_TZPC_DECPROT4SET_uart4_END         (17)
#define SOC_TZPC_DECPROT4SET_uart5_START       (18)
#define SOC_TZPC_DECPROT4SET_uart5_END         (18)
#define SOC_TZPC_DECPROT4SET_spi1_START        (19)
#define SOC_TZPC_DECPROT4SET_spi1_END          (19)
#define SOC_TZPC_DECPROT4SET_i2c3_START        (20)
#define SOC_TZPC_DECPROT4SET_i2c3_END          (20)
#define SOC_TZPC_DECPROT4SET_i2c4_START        (21)
#define SOC_TZPC_DECPROT4SET_i2c4_END          (21)
#define SOC_TZPC_DECPROT4SET_ddrc_START        (22)
#define SOC_TZPC_DECPROT4SET_ddrc_END          (22)
#define SOC_TZPC_DECPROT4SET_bisr_START        (23)
#define SOC_TZPC_DECPROT4SET_bisr_END          (23)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT4CLR_UNION
 �ṹ˵��  : DECPROT4CLR �Ĵ����ṹ���塣��ַƫ����:0x838����ֵ:0x00000001�����:32
 �Ĵ���˵��: IP��ȫ��������Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socp       : 1;  /* bit[0] : IP��ȫ�������㣺
                                                   0��IP��ȫ���Բ��䣻
                                                   1��IP��ȫ�����á�0���� */
        unsigned int  usb3otg    : 1;  /* bit[1] :  */
        unsigned int  usb3otg_bc : 1;  /* bit[2] :  */
        unsigned int  perf_stat  : 1;  /* bit[3] :  */
        unsigned int  reserved_0 : 1;  /* bit[4] :  */
        unsigned int  ipcns      : 1;  /* bit[5] :  */
        unsigned int  ipc        : 1;  /* bit[6] :  */
        unsigned int  ioc        : 1;  /* bit[7] :  */
        unsigned int  vcodecbus  : 1;  /* bit[8] :  */
        unsigned int  reserved_1 : 1;  /* bit[9] :  */
        unsigned int  hkadc_ssi  : 1;  /* bit[10]:  */
        unsigned int  codec_ssi  : 1;  /* bit[11]:  */
        unsigned int  reserved_2 : 1;  /* bit[12]:  */
        unsigned int  ipc_mdm    : 1;  /* bit[13]:  */
        unsigned int  uart0      : 1;  /* bit[14]:  */
        unsigned int  uart1      : 1;  /* bit[15]:  */
        unsigned int  uart2      : 1;  /* bit[16]:  */
        unsigned int  uart4      : 1;  /* bit[17]:  */
        unsigned int  uart5      : 1;  /* bit[18]:  */
        unsigned int  spi1       : 1;  /* bit[19]:  */
        unsigned int  i2c3       : 1;  /* bit[20]:  */
        unsigned int  i2c4       : 1;  /* bit[21]:  */
        unsigned int  ddrc       : 1;  /* bit[22]:  */
        unsigned int  bisr       : 1;  /* bit[23]:  */
        unsigned int  reserved_3 : 1;  /* bit[24]:  */
        unsigned int  reserved_4 : 1;  /* bit[25]:  */
        unsigned int  reserved_5 : 1;  /* bit[26]:  */
        unsigned int  reserved_6 : 1;  /* bit[27]:  */
        unsigned int  reserved_7 : 1;  /* bit[28]:  */
        unsigned int  reserved_8 : 1;  /* bit[29]:  */
        unsigned int  reserved_9 : 1;  /* bit[30]:  */
        unsigned int  reserved_10: 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT4CLR_UNION;
#endif
#define SOC_TZPC_DECPROT4CLR_socp_START        (0)
#define SOC_TZPC_DECPROT4CLR_socp_END          (0)
#define SOC_TZPC_DECPROT4CLR_usb3otg_START     (1)
#define SOC_TZPC_DECPROT4CLR_usb3otg_END       (1)
#define SOC_TZPC_DECPROT4CLR_usb3otg_bc_START  (2)
#define SOC_TZPC_DECPROT4CLR_usb3otg_bc_END    (2)
#define SOC_TZPC_DECPROT4CLR_perf_stat_START   (3)
#define SOC_TZPC_DECPROT4CLR_perf_stat_END     (3)
#define SOC_TZPC_DECPROT4CLR_ipcns_START       (5)
#define SOC_TZPC_DECPROT4CLR_ipcns_END         (5)
#define SOC_TZPC_DECPROT4CLR_ipc_START         (6)
#define SOC_TZPC_DECPROT4CLR_ipc_END           (6)
#define SOC_TZPC_DECPROT4CLR_ioc_START         (7)
#define SOC_TZPC_DECPROT4CLR_ioc_END           (7)
#define SOC_TZPC_DECPROT4CLR_vcodecbus_START   (8)
#define SOC_TZPC_DECPROT4CLR_vcodecbus_END     (8)
#define SOC_TZPC_DECPROT4CLR_hkadc_ssi_START   (10)
#define SOC_TZPC_DECPROT4CLR_hkadc_ssi_END     (10)
#define SOC_TZPC_DECPROT4CLR_codec_ssi_START   (11)
#define SOC_TZPC_DECPROT4CLR_codec_ssi_END     (11)
#define SOC_TZPC_DECPROT4CLR_ipc_mdm_START     (13)
#define SOC_TZPC_DECPROT4CLR_ipc_mdm_END       (13)
#define SOC_TZPC_DECPROT4CLR_uart0_START       (14)
#define SOC_TZPC_DECPROT4CLR_uart0_END         (14)
#define SOC_TZPC_DECPROT4CLR_uart1_START       (15)
#define SOC_TZPC_DECPROT4CLR_uart1_END         (15)
#define SOC_TZPC_DECPROT4CLR_uart2_START       (16)
#define SOC_TZPC_DECPROT4CLR_uart2_END         (16)
#define SOC_TZPC_DECPROT4CLR_uart4_START       (17)
#define SOC_TZPC_DECPROT4CLR_uart4_END         (17)
#define SOC_TZPC_DECPROT4CLR_uart5_START       (18)
#define SOC_TZPC_DECPROT4CLR_uart5_END         (18)
#define SOC_TZPC_DECPROT4CLR_spi1_START        (19)
#define SOC_TZPC_DECPROT4CLR_spi1_END          (19)
#define SOC_TZPC_DECPROT4CLR_i2c3_START        (20)
#define SOC_TZPC_DECPROT4CLR_i2c3_END          (20)
#define SOC_TZPC_DECPROT4CLR_i2c4_START        (21)
#define SOC_TZPC_DECPROT4CLR_i2c4_END          (21)
#define SOC_TZPC_DECPROT4CLR_ddrc_START        (22)
#define SOC_TZPC_DECPROT4CLR_ddrc_END          (22)
#define SOC_TZPC_DECPROT4CLR_bisr_START        (23)
#define SOC_TZPC_DECPROT4CLR_bisr_END          (23)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT5STAT_UNION
 �ṹ˵��  : DECPROT5STAT �Ĵ����ṹ���塣��ַƫ����:0x83C����ֵ:0x00300000�����:32
 �Ĵ���˵��: IP��ȫ����״̬�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3_pmussi1  : 1;  /* bit[0] : lpm3_pmussi1 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  ddrc          : 1;  /* bit[1] : ddrc slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  lpm3_tsensorc : 1;  /* bit[2] : lpm3_tsensorc slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  lpm3_pmc      : 1;  /* bit[3] : lpm3_pmc slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  lpm3_uart     : 1;  /* bit[4] : lpm3_uart slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  lpm3_pmui2c   : 1;  /* bit[5] : lpm3_pmui2c slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  lpm3_pmussi0  : 1;  /* bit[6] : lpm3_pmussi0 slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  crg_region1   : 1;  /* bit[7] : CRG(region1��0x000~0xBFF)�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  crg_region2   : 1;  /* bit[8] : CRG(region2��0xC00~0xC7F)IVP��ϵͳ��λ���ƣ��ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  crg_region3   : 1;  /* bit[9] : CRG(region3��0xC80~0xCFF)ISP��ϵͳ��λ���ƣ��ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  crg_region4   : 1;  /* bit[10]: CRG(region4��0xD00~0xDFF)Modem��ϵͳ��λ���ƣ��ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  crg_region5   : 1;  /* bit[11]: CRG(region5��0xE00~0xFFF)���ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  lpm3_wd       : 1;  /* bit[12]: lpm3_wd slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  lpm3_timer    : 1;  /* bit[13]: lpm3_timer slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  lpm3_config   : 1;  /* bit[14]: lpm3_config slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  lpm3_nandc    : 1;  /* bit[15]: lpm3_nandc slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  lpm3_gnspwm   : 1;  /* bit[16]: lpm3_gnspwm slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  lpm3_ram      : 1;  /* bit[17]: lpm3_ram slv�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  reserved_0    : 1;  /* bit[18]: ������ */
        unsigned int  reserved_1    : 1;  /* bit[19]: ������ */
        unsigned int  reserved_2    : 1;  /* bit[20]: ������ */
        unsigned int  reserved_3    : 1;  /* bit[21]: ������ */
        unsigned int  reserved_4    : 1;  /* bit[22]: ������ */
        unsigned int  reserved_5    : 1;  /* bit[23]: ������ */
        unsigned int  reserved_6    : 1;  /* bit[24]: ������ */
        unsigned int  reserved_7    : 1;  /* bit[25]: ������ */
        unsigned int  reserved_8    : 1;  /* bit[26]: ������ */
        unsigned int  reserved_9    : 1;  /* bit[27]: ������ */
        unsigned int  reserved_10   : 1;  /* bit[28]: ������ */
        unsigned int  reserved_11   : 1;  /* bit[29]: ������ */
        unsigned int  reserved_12   : 1;  /* bit[30]: ������ */
        unsigned int  reserved_13   : 1;  /* bit[31]: ������ */
    } reg;
} SOC_TZPC_DECPROT5STAT_UNION;
#endif
#define SOC_TZPC_DECPROT5STAT_lpm3_pmussi1_START   (0)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmussi1_END     (0)
#define SOC_TZPC_DECPROT5STAT_ddrc_START           (1)
#define SOC_TZPC_DECPROT5STAT_ddrc_END             (1)
#define SOC_TZPC_DECPROT5STAT_lpm3_tsensorc_START  (2)
#define SOC_TZPC_DECPROT5STAT_lpm3_tsensorc_END    (2)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmc_START       (3)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmc_END         (3)
#define SOC_TZPC_DECPROT5STAT_lpm3_uart_START      (4)
#define SOC_TZPC_DECPROT5STAT_lpm3_uart_END        (4)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmui2c_START    (5)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmui2c_END      (5)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmussi0_START   (6)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmussi0_END     (6)
#define SOC_TZPC_DECPROT5STAT_crg_region1_START    (7)
#define SOC_TZPC_DECPROT5STAT_crg_region1_END      (7)
#define SOC_TZPC_DECPROT5STAT_crg_region2_START    (8)
#define SOC_TZPC_DECPROT5STAT_crg_region2_END      (8)
#define SOC_TZPC_DECPROT5STAT_crg_region3_START    (9)
#define SOC_TZPC_DECPROT5STAT_crg_region3_END      (9)
#define SOC_TZPC_DECPROT5STAT_crg_region4_START    (10)
#define SOC_TZPC_DECPROT5STAT_crg_region4_END      (10)
#define SOC_TZPC_DECPROT5STAT_crg_region5_START    (11)
#define SOC_TZPC_DECPROT5STAT_crg_region5_END      (11)
#define SOC_TZPC_DECPROT5STAT_lpm3_wd_START        (12)
#define SOC_TZPC_DECPROT5STAT_lpm3_wd_END          (12)
#define SOC_TZPC_DECPROT5STAT_lpm3_timer_START     (13)
#define SOC_TZPC_DECPROT5STAT_lpm3_timer_END       (13)
#define SOC_TZPC_DECPROT5STAT_lpm3_config_START    (14)
#define SOC_TZPC_DECPROT5STAT_lpm3_config_END      (14)
#define SOC_TZPC_DECPROT5STAT_lpm3_nandc_START     (15)
#define SOC_TZPC_DECPROT5STAT_lpm3_nandc_END       (15)
#define SOC_TZPC_DECPROT5STAT_lpm3_gnspwm_START    (16)
#define SOC_TZPC_DECPROT5STAT_lpm3_gnspwm_END      (16)
#define SOC_TZPC_DECPROT5STAT_lpm3_ram_START       (17)
#define SOC_TZPC_DECPROT5STAT_lpm3_ram_END         (17)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT5SET_UNION
 �ṹ˵��  : DECPROT5SET �Ĵ����ṹ���塣��ַƫ����:0x840����ֵ:0x00300000�����:32
 �Ĵ���˵��: IP��ȫ������λ�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3_pmussi1  : 1;  /* bit[0] : IP��ȫ������λ��
                                                      0��IP��ȫ���Բ��䣻
                                                      1��IP��ȫ�����á�1���� */
        unsigned int  ddrc          : 1;  /* bit[1] :  */
        unsigned int  lpm3_tsensorc : 1;  /* bit[2] :  */
        unsigned int  lpm3_pmc      : 1;  /* bit[3] :  */
        unsigned int  lpm3_uart     : 1;  /* bit[4] :  */
        unsigned int  lpm3_pmui2c   : 1;  /* bit[5] :  */
        unsigned int  lpm3_pmussi0  : 1;  /* bit[6] :  */
        unsigned int  crg_region1   : 1;  /* bit[7] :  */
        unsigned int  crg_region2   : 1;  /* bit[8] :  */
        unsigned int  crg_region3   : 1;  /* bit[9] :  */
        unsigned int  crg_region4   : 1;  /* bit[10]:  */
        unsigned int  crg_region5   : 1;  /* bit[11]:  */
        unsigned int  lpm3_wd       : 1;  /* bit[12]:  */
        unsigned int  lpm3_timer    : 1;  /* bit[13]:  */
        unsigned int  lpm3_config   : 1;  /* bit[14]:  */
        unsigned int  lpm3_nandc    : 1;  /* bit[15]:  */
        unsigned int  lpm3_gnspwm   : 1;  /* bit[16]:  */
        unsigned int  lpm3_ram      : 1;  /* bit[17]:  */
        unsigned int  reserved_0    : 1;  /* bit[18]:  */
        unsigned int  reserved_1    : 1;  /* bit[19]:  */
        unsigned int  reserved_2    : 1;  /* bit[20]:  */
        unsigned int  reserved_3    : 1;  /* bit[21]:  */
        unsigned int  reserved_4    : 1;  /* bit[22]:  */
        unsigned int  reserved_5    : 1;  /* bit[23]:  */
        unsigned int  reserved_6    : 1;  /* bit[24]:  */
        unsigned int  reserved_7    : 1;  /* bit[25]:  */
        unsigned int  reserved_8    : 1;  /* bit[26]:  */
        unsigned int  reserved_9    : 1;  /* bit[27]:  */
        unsigned int  reserved_10   : 1;  /* bit[28]:  */
        unsigned int  reserved_11   : 1;  /* bit[29]:  */
        unsigned int  reserved_12   : 1;  /* bit[30]:  */
        unsigned int  reserved_13   : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT5SET_UNION;
#endif
#define SOC_TZPC_DECPROT5SET_lpm3_pmussi1_START   (0)
#define SOC_TZPC_DECPROT5SET_lpm3_pmussi1_END     (0)
#define SOC_TZPC_DECPROT5SET_ddrc_START           (1)
#define SOC_TZPC_DECPROT5SET_ddrc_END             (1)
#define SOC_TZPC_DECPROT5SET_lpm3_tsensorc_START  (2)
#define SOC_TZPC_DECPROT5SET_lpm3_tsensorc_END    (2)
#define SOC_TZPC_DECPROT5SET_lpm3_pmc_START       (3)
#define SOC_TZPC_DECPROT5SET_lpm3_pmc_END         (3)
#define SOC_TZPC_DECPROT5SET_lpm3_uart_START      (4)
#define SOC_TZPC_DECPROT5SET_lpm3_uart_END        (4)
#define SOC_TZPC_DECPROT5SET_lpm3_pmui2c_START    (5)
#define SOC_TZPC_DECPROT5SET_lpm3_pmui2c_END      (5)
#define SOC_TZPC_DECPROT5SET_lpm3_pmussi0_START   (6)
#define SOC_TZPC_DECPROT5SET_lpm3_pmussi0_END     (6)
#define SOC_TZPC_DECPROT5SET_crg_region1_START    (7)
#define SOC_TZPC_DECPROT5SET_crg_region1_END      (7)
#define SOC_TZPC_DECPROT5SET_crg_region2_START    (8)
#define SOC_TZPC_DECPROT5SET_crg_region2_END      (8)
#define SOC_TZPC_DECPROT5SET_crg_region3_START    (9)
#define SOC_TZPC_DECPROT5SET_crg_region3_END      (9)
#define SOC_TZPC_DECPROT5SET_crg_region4_START    (10)
#define SOC_TZPC_DECPROT5SET_crg_region4_END      (10)
#define SOC_TZPC_DECPROT5SET_crg_region5_START    (11)
#define SOC_TZPC_DECPROT5SET_crg_region5_END      (11)
#define SOC_TZPC_DECPROT5SET_lpm3_wd_START        (12)
#define SOC_TZPC_DECPROT5SET_lpm3_wd_END          (12)
#define SOC_TZPC_DECPROT5SET_lpm3_timer_START     (13)
#define SOC_TZPC_DECPROT5SET_lpm3_timer_END       (13)
#define SOC_TZPC_DECPROT5SET_lpm3_config_START    (14)
#define SOC_TZPC_DECPROT5SET_lpm3_config_END      (14)
#define SOC_TZPC_DECPROT5SET_lpm3_nandc_START     (15)
#define SOC_TZPC_DECPROT5SET_lpm3_nandc_END       (15)
#define SOC_TZPC_DECPROT5SET_lpm3_gnspwm_START    (16)
#define SOC_TZPC_DECPROT5SET_lpm3_gnspwm_END      (16)
#define SOC_TZPC_DECPROT5SET_lpm3_ram_START       (17)
#define SOC_TZPC_DECPROT5SET_lpm3_ram_END         (17)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT5CLR_UNION
 �ṹ˵��  : DECPROT5CLR �Ĵ����ṹ���塣��ַƫ����:0x844����ֵ:0x00300000�����:32
 �Ĵ���˵��: IP��ȫ��������Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3_pmussi1  : 1;  /* bit[0] : IP��ȫ�������㣺
                                                      0��IP��ȫ���Բ��䣻
                                                      1��IP��ȫ�����á�0���� */
        unsigned int  ddrc          : 1;  /* bit[1] :  */
        unsigned int  lpm3_tsensorc : 1;  /* bit[2] :  */
        unsigned int  lpm3_pmc      : 1;  /* bit[3] :  */
        unsigned int  lpm3_uart     : 1;  /* bit[4] :  */
        unsigned int  lpm3_pmui2c   : 1;  /* bit[5] :  */
        unsigned int  lpm3_pmussi0  : 1;  /* bit[6] :  */
        unsigned int  crg_region1   : 1;  /* bit[7] :  */
        unsigned int  crg_region2   : 1;  /* bit[8] :  */
        unsigned int  crg_region3   : 1;  /* bit[9] :  */
        unsigned int  crg_region4   : 1;  /* bit[10]:  */
        unsigned int  crg_region5   : 1;  /* bit[11]:  */
        unsigned int  lpm3_wd       : 1;  /* bit[12]:  */
        unsigned int  lpm3_timer    : 1;  /* bit[13]:  */
        unsigned int  lpm3_config   : 1;  /* bit[14]:  */
        unsigned int  lpm3_nandc    : 1;  /* bit[15]:  */
        unsigned int  lpm3_gnspwm   : 1;  /* bit[16]:  */
        unsigned int  lpm3_ram      : 1;  /* bit[17]:  */
        unsigned int  reserved_0    : 1;  /* bit[18]:  */
        unsigned int  reserved_1    : 1;  /* bit[19]:  */
        unsigned int  reserved_2    : 1;  /* bit[20]:  */
        unsigned int  reserved_3    : 1;  /* bit[21]:  */
        unsigned int  reserved_4    : 1;  /* bit[22]:  */
        unsigned int  reserved_5    : 1;  /* bit[23]:  */
        unsigned int  reserved_6    : 1;  /* bit[24]:  */
        unsigned int  reserved_7    : 1;  /* bit[25]:  */
        unsigned int  reserved_8    : 1;  /* bit[26]:  */
        unsigned int  reserved_9    : 1;  /* bit[27]:  */
        unsigned int  reserved_10   : 1;  /* bit[28]:  */
        unsigned int  reserved_11   : 1;  /* bit[29]:  */
        unsigned int  reserved_12   : 1;  /* bit[30]:  */
        unsigned int  reserved_13   : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT5CLR_UNION;
#endif
#define SOC_TZPC_DECPROT5CLR_lpm3_pmussi1_START   (0)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmussi1_END     (0)
#define SOC_TZPC_DECPROT5CLR_ddrc_START           (1)
#define SOC_TZPC_DECPROT5CLR_ddrc_END             (1)
#define SOC_TZPC_DECPROT5CLR_lpm3_tsensorc_START  (2)
#define SOC_TZPC_DECPROT5CLR_lpm3_tsensorc_END    (2)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmc_START       (3)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmc_END         (3)
#define SOC_TZPC_DECPROT5CLR_lpm3_uart_START      (4)
#define SOC_TZPC_DECPROT5CLR_lpm3_uart_END        (4)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmui2c_START    (5)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmui2c_END      (5)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmussi0_START   (6)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmussi0_END     (6)
#define SOC_TZPC_DECPROT5CLR_crg_region1_START    (7)
#define SOC_TZPC_DECPROT5CLR_crg_region1_END      (7)
#define SOC_TZPC_DECPROT5CLR_crg_region2_START    (8)
#define SOC_TZPC_DECPROT5CLR_crg_region2_END      (8)
#define SOC_TZPC_DECPROT5CLR_crg_region3_START    (9)
#define SOC_TZPC_DECPROT5CLR_crg_region3_END      (9)
#define SOC_TZPC_DECPROT5CLR_crg_region4_START    (10)
#define SOC_TZPC_DECPROT5CLR_crg_region4_END      (10)
#define SOC_TZPC_DECPROT5CLR_crg_region5_START    (11)
#define SOC_TZPC_DECPROT5CLR_crg_region5_END      (11)
#define SOC_TZPC_DECPROT5CLR_lpm3_wd_START        (12)
#define SOC_TZPC_DECPROT5CLR_lpm3_wd_END          (12)
#define SOC_TZPC_DECPROT5CLR_lpm3_timer_START     (13)
#define SOC_TZPC_DECPROT5CLR_lpm3_timer_END       (13)
#define SOC_TZPC_DECPROT5CLR_lpm3_config_START    (14)
#define SOC_TZPC_DECPROT5CLR_lpm3_config_END      (14)
#define SOC_TZPC_DECPROT5CLR_lpm3_nandc_START     (15)
#define SOC_TZPC_DECPROT5CLR_lpm3_nandc_END       (15)
#define SOC_TZPC_DECPROT5CLR_lpm3_gnspwm_START    (16)
#define SOC_TZPC_DECPROT5CLR_lpm3_gnspwm_END      (16)
#define SOC_TZPC_DECPROT5CLR_lpm3_ram_START       (17)
#define SOC_TZPC_DECPROT5CLR_lpm3_ram_END         (17)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT6STAT_UNION
 �ṹ˵��  : DECPROT6STAT �Ĵ����ṹ���塣��ַƫ����:0x848����ֵ:0x0007FE60�����:32
 �Ĵ���˵��: IP��ȫ����״̬�Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3             : 1;  /* bit[0] : lpm3 mst�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  reserved_0       : 1;  /* bit[1] : ������ */
        unsigned int  reserved_1       : 1;  /* bit[2] : ������ */
        unsigned int  emmc0            : 1;  /* bit[3] : emmc0 mst�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  emmc1            : 1;  /* bit[4] : emmc1 mst�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  sd30             : 1;  /* bit[5] : sd30 mst�ϵ�Ĭ��Ϊ�ǰ�ȫ���ԡ� */
        unsigned int  sdio0            : 1;  /* bit[6] : sdio0 mst�ϵ�Ĭ��Ϊ�ǰ�ȫ���ԡ� */
        unsigned int  sdio1            : 1;  /* bit[7] : sdio1 mst�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  usb3otg          : 1;  /* bit[8] : usb3otg mst�ϵ�Ĭ��Ϊ��ȫ���ԡ� */
        unsigned int  g3d              : 1;  /* bit[9] : g3d mst�ϵ�Ĭ��Ϊ�ǰ�ȫ���ԡ� */
        unsigned int  reserved_2       : 1;  /* bit[10]: ������ */
        unsigned int  vdec             : 1;  /* bit[11]: vdec mst�ϵ�Ĭ��Ϊ�ǰ�ȫ���ԡ� */
        unsigned int  venc             : 1;  /* bit[12]: venc mst�ϵ�Ĭ��Ϊ�ǰ�ȫ���ԡ� */
        unsigned int  reserved_3       : 1;  /* bit[13]: ������ */
        unsigned int  reserved_4       : 1;  /* bit[14]: ������ */
        unsigned int  isp_a7tocfg      : 1;  /* bit[15]: isp_a7tocfg mst�ϵ�Ĭ��Ϊ�ǰ�ȫ���ԡ� */
        unsigned int  isp_a7_axi_mst   : 1;  /* bit[16]: isp_a7_axi_mst mst�ϵ�Ĭ��Ϊ�ǰ�ȫ���ԡ� */
        unsigned int  isp_core_axi_mst : 1;  /* bit[17]: isp_core_axi_mst mst�ϵ�Ĭ��Ϊ�ǰ�ȫ���ԡ� */
        unsigned int  perf_stat        : 1;  /* bit[18]: perf_stat mst�ϵ�Ĭ��Ϊ�ǰ�ȫ���ԡ� */
        unsigned int  reserved_5       : 1;  /* bit[19]: ������ */
        unsigned int  reserved_6       : 1;  /* bit[20]: ������ */
        unsigned int  reserved_7       : 1;  /* bit[21]: ������ */
        unsigned int  reserved_8       : 1;  /* bit[22]: ������ */
        unsigned int  reserved_9       : 1;  /* bit[23]: ������ */
        unsigned int  reserved_10      : 1;  /* bit[24]: ������ */
        unsigned int  reserved_11      : 1;  /* bit[25]: ������ */
        unsigned int  reserved_12      : 1;  /* bit[26]: ������ */
        unsigned int  reserved_13      : 1;  /* bit[27]: ������ */
        unsigned int  reserved_14      : 1;  /* bit[28]: ������ */
        unsigned int  reserved_15      : 1;  /* bit[29]: ������ */
        unsigned int  reserved_16      : 1;  /* bit[30]: ������ */
        unsigned int  reserved_17      : 1;  /* bit[31]: ������ */
    } reg;
} SOC_TZPC_DECPROT6STAT_UNION;
#endif
#define SOC_TZPC_DECPROT6STAT_lpm3_START              (0)
#define SOC_TZPC_DECPROT6STAT_lpm3_END                (0)
#define SOC_TZPC_DECPROT6STAT_emmc0_START             (3)
#define SOC_TZPC_DECPROT6STAT_emmc0_END               (3)
#define SOC_TZPC_DECPROT6STAT_emmc1_START             (4)
#define SOC_TZPC_DECPROT6STAT_emmc1_END               (4)
#define SOC_TZPC_DECPROT6STAT_sd30_START              (5)
#define SOC_TZPC_DECPROT6STAT_sd30_END                (5)
#define SOC_TZPC_DECPROT6STAT_sdio0_START             (6)
#define SOC_TZPC_DECPROT6STAT_sdio0_END               (6)
#define SOC_TZPC_DECPROT6STAT_sdio1_START             (7)
#define SOC_TZPC_DECPROT6STAT_sdio1_END               (7)
#define SOC_TZPC_DECPROT6STAT_usb3otg_START           (8)
#define SOC_TZPC_DECPROT6STAT_usb3otg_END             (8)
#define SOC_TZPC_DECPROT6STAT_g3d_START               (9)
#define SOC_TZPC_DECPROT6STAT_g3d_END                 (9)
#define SOC_TZPC_DECPROT6STAT_vdec_START              (11)
#define SOC_TZPC_DECPROT6STAT_vdec_END                (11)
#define SOC_TZPC_DECPROT6STAT_venc_START              (12)
#define SOC_TZPC_DECPROT6STAT_venc_END                (12)
#define SOC_TZPC_DECPROT6STAT_isp_a7tocfg_START       (15)
#define SOC_TZPC_DECPROT6STAT_isp_a7tocfg_END         (15)
#define SOC_TZPC_DECPROT6STAT_isp_a7_axi_mst_START    (16)
#define SOC_TZPC_DECPROT6STAT_isp_a7_axi_mst_END      (16)
#define SOC_TZPC_DECPROT6STAT_isp_core_axi_mst_START  (17)
#define SOC_TZPC_DECPROT6STAT_isp_core_axi_mst_END    (17)
#define SOC_TZPC_DECPROT6STAT_perf_stat_START         (18)
#define SOC_TZPC_DECPROT6STAT_perf_stat_END           (18)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT6SET_UNION
 �ṹ˵��  : DECPROT6SET �Ĵ����ṹ���塣��ַƫ����:0x84C����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ������λ�Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3             : 1;  /* bit[0] : IP��ȫ������λ��
                                                         0��IP��ȫ���Բ��䣻
                                                         1��IP��ȫ�����á�1���� */
        unsigned int  reserved_0       : 1;  /* bit[1] :  */
        unsigned int  reserved_1       : 1;  /* bit[2] :  */
        unsigned int  emmc0            : 1;  /* bit[3] :  */
        unsigned int  emmc1            : 1;  /* bit[4] :  */
        unsigned int  sd30             : 1;  /* bit[5] :  */
        unsigned int  sdio0            : 1;  /* bit[6] :  */
        unsigned int  sdio1            : 1;  /* bit[7] :  */
        unsigned int  usb3otg          : 1;  /* bit[8] :  */
        unsigned int  g3d              : 1;  /* bit[9] :  */
        unsigned int  reserved_2       : 1;  /* bit[10]:  */
        unsigned int  vdec             : 1;  /* bit[11]:  */
        unsigned int  venc             : 1;  /* bit[12]:  */
        unsigned int  reserved_3       : 1;  /* bit[13]:  */
        unsigned int  reserved_4       : 1;  /* bit[14]:  */
        unsigned int  isp_a7tocfg      : 1;  /* bit[15]:  */
        unsigned int  isp_a7_axi_mst   : 1;  /* bit[16]:  */
        unsigned int  isp_core_axi_mst : 1;  /* bit[17]:  */
        unsigned int  perf_stat        : 1;  /* bit[18]:  */
        unsigned int  reserved_5       : 1;  /* bit[19]:  */
        unsigned int  reserved_6       : 1;  /* bit[20]:  */
        unsigned int  reserved_7       : 1;  /* bit[21]:  */
        unsigned int  reserved_8       : 1;  /* bit[22]:  */
        unsigned int  reserved_9       : 1;  /* bit[23]:  */
        unsigned int  reserved_10      : 1;  /* bit[24]:  */
        unsigned int  reserved_11      : 1;  /* bit[25]:  */
        unsigned int  reserved_12      : 1;  /* bit[26]:  */
        unsigned int  reserved_13      : 1;  /* bit[27]:  */
        unsigned int  reserved_14      : 1;  /* bit[28]:  */
        unsigned int  reserved_15      : 1;  /* bit[29]:  */
        unsigned int  reserved_16      : 1;  /* bit[30]:  */
        unsigned int  reserved_17      : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT6SET_UNION;
#endif
#define SOC_TZPC_DECPROT6SET_lpm3_START              (0)
#define SOC_TZPC_DECPROT6SET_lpm3_END                (0)
#define SOC_TZPC_DECPROT6SET_emmc0_START             (3)
#define SOC_TZPC_DECPROT6SET_emmc0_END               (3)
#define SOC_TZPC_DECPROT6SET_emmc1_START             (4)
#define SOC_TZPC_DECPROT6SET_emmc1_END               (4)
#define SOC_TZPC_DECPROT6SET_sd30_START              (5)
#define SOC_TZPC_DECPROT6SET_sd30_END                (5)
#define SOC_TZPC_DECPROT6SET_sdio0_START             (6)
#define SOC_TZPC_DECPROT6SET_sdio0_END               (6)
#define SOC_TZPC_DECPROT6SET_sdio1_START             (7)
#define SOC_TZPC_DECPROT6SET_sdio1_END               (7)
#define SOC_TZPC_DECPROT6SET_usb3otg_START           (8)
#define SOC_TZPC_DECPROT6SET_usb3otg_END             (8)
#define SOC_TZPC_DECPROT6SET_g3d_START               (9)
#define SOC_TZPC_DECPROT6SET_g3d_END                 (9)
#define SOC_TZPC_DECPROT6SET_vdec_START              (11)
#define SOC_TZPC_DECPROT6SET_vdec_END                (11)
#define SOC_TZPC_DECPROT6SET_venc_START              (12)
#define SOC_TZPC_DECPROT6SET_venc_END                (12)
#define SOC_TZPC_DECPROT6SET_isp_a7tocfg_START       (15)
#define SOC_TZPC_DECPROT6SET_isp_a7tocfg_END         (15)
#define SOC_TZPC_DECPROT6SET_isp_a7_axi_mst_START    (16)
#define SOC_TZPC_DECPROT6SET_isp_a7_axi_mst_END      (16)
#define SOC_TZPC_DECPROT6SET_isp_core_axi_mst_START  (17)
#define SOC_TZPC_DECPROT6SET_isp_core_axi_mst_END    (17)
#define SOC_TZPC_DECPROT6SET_perf_stat_START         (18)
#define SOC_TZPC_DECPROT6SET_perf_stat_END           (18)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT6CLR_UNION
 �ṹ˵��  : DECPROT6CLR �Ĵ����ṹ���塣��ַƫ����:0x850����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ��������Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3             : 1;  /* bit[0] : IP��ȫ�������㣺
                                                         0��IP��ȫ���Բ��䣻
                                                         1��IP��ȫ�����á�0���� */
        unsigned int  reserved_0       : 1;  /* bit[1] :  */
        unsigned int  reserved_1       : 1;  /* bit[2] :  */
        unsigned int  emmc0            : 1;  /* bit[3] :  */
        unsigned int  emmc1            : 1;  /* bit[4] :  */
        unsigned int  sd30             : 1;  /* bit[5] :  */
        unsigned int  sdio0            : 1;  /* bit[6] :  */
        unsigned int  sdio1            : 1;  /* bit[7] :  */
        unsigned int  usb3otg          : 1;  /* bit[8] :  */
        unsigned int  g3d              : 1;  /* bit[9] :  */
        unsigned int  reserved_2       : 1;  /* bit[10]:  */
        unsigned int  vdec             : 1;  /* bit[11]:  */
        unsigned int  venc             : 1;  /* bit[12]:  */
        unsigned int  reserved_3       : 1;  /* bit[13]:  */
        unsigned int  reserved_4       : 1;  /* bit[14]:  */
        unsigned int  isp_a7tocfg      : 1;  /* bit[15]:  */
        unsigned int  isp_a7_axi_mst   : 1;  /* bit[16]:  */
        unsigned int  isp_core_axi_mst : 1;  /* bit[17]:  */
        unsigned int  perf_stat        : 1;  /* bit[18]:  */
        unsigned int  reserved_5       : 1;  /* bit[19]:  */
        unsigned int  reserved_6       : 1;  /* bit[20]:  */
        unsigned int  reserved_7       : 1;  /* bit[21]:  */
        unsigned int  reserved_8       : 1;  /* bit[22]:  */
        unsigned int  reserved_9       : 1;  /* bit[23]:  */
        unsigned int  reserved_10      : 1;  /* bit[24]:  */
        unsigned int  reserved_11      : 1;  /* bit[25]:  */
        unsigned int  reserved_12      : 1;  /* bit[26]:  */
        unsigned int  reserved_13      : 1;  /* bit[27]:  */
        unsigned int  reserved_14      : 1;  /* bit[28]:  */
        unsigned int  reserved_15      : 1;  /* bit[29]:  */
        unsigned int  reserved_16      : 1;  /* bit[30]:  */
        unsigned int  reserved_17      : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT6CLR_UNION;
#endif
#define SOC_TZPC_DECPROT6CLR_lpm3_START              (0)
#define SOC_TZPC_DECPROT6CLR_lpm3_END                (0)
#define SOC_TZPC_DECPROT6CLR_emmc0_START             (3)
#define SOC_TZPC_DECPROT6CLR_emmc0_END               (3)
#define SOC_TZPC_DECPROT6CLR_emmc1_START             (4)
#define SOC_TZPC_DECPROT6CLR_emmc1_END               (4)
#define SOC_TZPC_DECPROT6CLR_sd30_START              (5)
#define SOC_TZPC_DECPROT6CLR_sd30_END                (5)
#define SOC_TZPC_DECPROT6CLR_sdio0_START             (6)
#define SOC_TZPC_DECPROT6CLR_sdio0_END               (6)
#define SOC_TZPC_DECPROT6CLR_sdio1_START             (7)
#define SOC_TZPC_DECPROT6CLR_sdio1_END               (7)
#define SOC_TZPC_DECPROT6CLR_usb3otg_START           (8)
#define SOC_TZPC_DECPROT6CLR_usb3otg_END             (8)
#define SOC_TZPC_DECPROT6CLR_g3d_START               (9)
#define SOC_TZPC_DECPROT6CLR_g3d_END                 (9)
#define SOC_TZPC_DECPROT6CLR_vdec_START              (11)
#define SOC_TZPC_DECPROT6CLR_vdec_END                (11)
#define SOC_TZPC_DECPROT6CLR_venc_START              (12)
#define SOC_TZPC_DECPROT6CLR_venc_END                (12)
#define SOC_TZPC_DECPROT6CLR_isp_a7tocfg_START       (15)
#define SOC_TZPC_DECPROT6CLR_isp_a7tocfg_END         (15)
#define SOC_TZPC_DECPROT6CLR_isp_a7_axi_mst_START    (16)
#define SOC_TZPC_DECPROT6CLR_isp_a7_axi_mst_END      (16)
#define SOC_TZPC_DECPROT6CLR_isp_core_axi_mst_START  (17)
#define SOC_TZPC_DECPROT6CLR_isp_core_axi_mst_END    (17)
#define SOC_TZPC_DECPROT6CLR_perf_stat_START         (18)
#define SOC_TZPC_DECPROT6CLR_perf_stat_END           (18)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT7STAT_UNION
 �ṹ˵��  : DECPROT7STAT �Ĵ����ṹ���塣��ַƫ����:0x854����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ����״̬�Ĵ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_TZPC_DECPROT7STAT_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT7SET_UNION
 �ṹ˵��  : DECPROT7SET �Ĵ����ṹ���塣��ַƫ����:0x858����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ������λ�Ĵ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_TZPC_DECPROT7SET_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT7CLR_UNION
 �ṹ˵��  : DECPROT7CLR �Ĵ����ṹ���塣��ַƫ����:0x85C����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP��ȫ��������Ĵ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_TZPC_DECPROT7CLR_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT8STAT_UNION
 �ṹ˵��  : DECPROT8STAT �Ĵ����ṹ���塣��ַƫ����:0x860����ֵ:0x00000007�����:32
 �Ĵ���˵��: IP��ȫ����״̬�Ĵ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vivobus_firewall : 8;  /* bit[0-7] : bit0��firewall��ʹ�ܿ��ƣ�Ĭ��ʹ�ܡ�
                                                           bit1��firewall����ԽȨ�Ƿ��ϱ�error��Ĭ���ϱ���
                                                           bit2��isp_subsys slv�İ�ȫ���ԣ�Ĭ���Ƿǰ�ȫ���ԡ�
                                                           bit3��VIVOBUS(0xE86C0000~0xE8DFFFFF) slv�İ�ȫ���ԣ�Ĭ���ǰ�ȫ���ԡ�
                                                           bit[7:4]�������� */
        unsigned int  reserved_0       : 23; /* bit[8-30]: ������ */
        unsigned int  reserved_1       : 1;  /* bit[31]  : ������ */
    } reg;
} SOC_TZPC_DECPROT8STAT_UNION;
#endif
#define SOC_TZPC_DECPROT8STAT_vivobus_firewall_START  (0)
#define SOC_TZPC_DECPROT8STAT_vivobus_firewall_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT8SET_UNION
 �ṹ˵��  : DECPROT8SET �Ĵ����ṹ���塣��ַƫ����:0x864����ֵ:0x00000007�����:32
 �Ĵ���˵��: IP��ȫ������λ�Ĵ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vivobus_firewall : 8;  /* bit[0-7] : IP��ȫ������λ��
                                                           0��IP��ȫ���Բ��䣻
                                                           1��IP��ȫ�����á�1���� */
        unsigned int  reserved_0       : 23; /* bit[8-30]:  */
        unsigned int  reserved_1       : 1;  /* bit[31]  :  */
    } reg;
} SOC_TZPC_DECPROT8SET_UNION;
#endif
#define SOC_TZPC_DECPROT8SET_vivobus_firewall_START  (0)
#define SOC_TZPC_DECPROT8SET_vivobus_firewall_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_DECPROT8CLR_UNION
 �ṹ˵��  : DECPROT8CLR �Ĵ����ṹ���塣��ַƫ����:0x868����ֵ:0x00000007�����:32
 �Ĵ���˵��: IP��ȫ��������Ĵ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vivobus_firewall : 8;  /* bit[0-7] : IP��ȫ�������㣺
                                                           0��IP��ȫ���Բ��䣻
                                                           1��IP��ȫ�����á�0���� */
        unsigned int  reserved_0       : 23; /* bit[8-30]:  */
        unsigned int  reserved_1       : 1;  /* bit[31]  :  */
    } reg;
} SOC_TZPC_DECPROT8CLR_UNION;
#endif
#define SOC_TZPC_DECPROT8CLR_vivobus_firewall_START  (0)
#define SOC_TZPC_DECPROT8CLR_vivobus_firewall_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_TZPC_REG0_STAT_UNION
 �ṹ˵��  : REG0_STAT �Ĵ����ṹ���塣��ַƫ����:0x86C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����reg0�Ĵ�������Ϣ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_TZPC_REG0_STAT_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_TZPC_REG1_STAT_UNION
 �ṹ˵��  : REG1_STAT �Ĵ����ṹ���塣��ַƫ����:0x870����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����reg1�Ĵ�������Ϣ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_TZPC_REG1_STAT_UNION;
#endif






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

#endif /* end of soc_tzpc_interface.h */
