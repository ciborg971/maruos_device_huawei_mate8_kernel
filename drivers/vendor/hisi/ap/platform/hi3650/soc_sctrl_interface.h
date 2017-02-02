/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_sctrl_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-04-08 11:47:49
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��4��8��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_SCTRL.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_SCTRL_INTERFACE_H__
#define __SOC_SCTRL_INTERFACE_H__

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
/* �Ĵ���˵����ϵͳ�������Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCCTRL_UNION */
#define SOC_SCTRL_SCCTRL_ADDR(base)                   ((base) + (0x000))

/* �Ĵ���˵����ϵͳ״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCSYSSTAT_UNION */
#define SOC_SCTRL_SCSYSSTAT_ADDR(base)                ((base) + (0x004))

/* �Ĵ���˵����������ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCXTALCTRL_UNION */
#define SOC_SCTRL_SCXTALCTRL_ADDR(base)               ((base) + (0x010))

/* �Ĵ���˵���������ȶ�ʱ�����üĴ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCXTALTIMEOUT0_UNION */
#define SOC_SCTRL_SCXTALTIMEOUT0_ADDR(base)           ((base) + (0x014))

/* �Ĵ���˵���������ȶ�ʱ�����üĴ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCXTALTIMEOUT1_UNION */
#define SOC_SCTRL_SCXTALTIMEOUT1_ADDR(base)           ((base) + (0x018))

/* �Ĵ���˵�����������״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCXTALSTAT_UNION */
#define SOC_SCTRL_SCXTALSTAT_ADDR(base)               ((base) + (0x01C))

/* �Ĵ���˵����PPLL0���ƼĴ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCPPLLCTRL0_UNION */
#define SOC_SCTRL_SCPPLLCTRL0_ADDR(base)              ((base) + (0x020))

/* �Ĵ���˵����PPLL0���ƼĴ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCPPLLCTRL1_UNION */
#define SOC_SCTRL_SCPPLLCTRL1_ADDR(base)              ((base) + (0x024))

/* �Ĵ���˵����PPLL0 SSC���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCPPLLSSCCTRL_UNION */
#define SOC_SCTRL_SCPPLLSSCCTRL_ADDR(base)            ((base) + (0x028))

/* �Ĵ���˵����PPLL0״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCPPLLSTAT_UNION */
#define SOC_SCTRL_SCPPLLSTAT_ADDR(base)               ((base) + (0x02C))

/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCPEREN0_UNION */
#define SOC_SCTRL_SCPEREN0_ADDR(base)                 ((base) + (0x030))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERDIS0_UNION */
#define SOC_SCTRL_SCPERDIS0_ADDR(base)                ((base) + (0x034))

/* �Ĵ���˵��������ʱ��ʹ��״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERCLKEN0_UNION */
#define SOC_SCTRL_SCPERCLKEN0_ADDR(base)              ((base) + (0x038))

/* �Ĵ���˵��������ʱ������״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTAT0_UNION */
#define SOC_SCTRL_SCPERSTAT0_ADDR(base)               ((base) + (0x03C))

/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCPEREN1_UNION */
#define SOC_SCTRL_SCPEREN1_ADDR(base)                 ((base) + (0x040))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERDIS1_UNION */
#define SOC_SCTRL_SCPERDIS1_ADDR(base)                ((base) + (0x044))

/* �Ĵ���˵��������ʱ��ʹ��״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERCLKEN1_UNION */
#define SOC_SCTRL_SCPERCLKEN1_ADDR(base)              ((base) + (0x048))

/* �Ĵ���˵��������ʱ������״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTAT1_UNION */
#define SOC_SCTRL_SCPERSTAT1_ADDR(base)               ((base) + (0x04C))

/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCPEREN2_UNION */
#define SOC_SCTRL_SCPEREN2_ADDR(base)                 ((base) + (0x050))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERDIS2_UNION */
#define SOC_SCTRL_SCPERDIS2_ADDR(base)                ((base) + (0x054))

/* �Ĵ���˵��������ʱ��ʹ��״̬�Ĵ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERCLKEN2_UNION */
#define SOC_SCTRL_SCPERCLKEN2_ADDR(base)              ((base) + (0x058))

/* �Ĵ���˵��������ʱ������״̬�Ĵ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTAT2_UNION */
#define SOC_SCTRL_SCPERSTAT2_ADDR(base)               ((base) + (0x05C))

/* �Ĵ���˵����ϵͳTIMERʱ��ѡ��Ϳ��ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCTIMERCTRL_UNION */
#define SOC_SCTRL_SCTIMERCTRL_ADDR(base)              ((base) + (0x060))

/* �Ĵ���˵����FPLL0���ƼĴ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCFPLLCTRL0_UNION */
#define SOC_SCTRL_SCFPLLCTRL0_ADDR(base)              ((base) + (0x064))

/* �Ĵ���˵����FPLL0���ƼĴ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCFPLLCTRL1_UNION */
#define SOC_SCTRL_SCFPLLCTRL1_ADDR(base)              ((base) + (0x068))

/* �Ĵ���˵����FPLL0���ƼĴ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCFPLLCTRL2_UNION */
#define SOC_SCTRL_SCFPLLCTRL2_ADDR(base)              ((base) + (0x06C))

/* �Ĵ���˵����FPLL0���ƼĴ���3��
   λ����UNION�ṹ:  SOC_SCTRL_SCFPLLCTRL3_UNION */
#define SOC_SCTRL_SCFPLLCTRL3_ADDR(base)              ((base) + (0x070))

/* �Ĵ���˵����FPLL0״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCFPLLSTAT_UNION */
#define SOC_SCTRL_SCFPLLSTAT_ADDR(base)               ((base) + (0x074))

/* �Ĵ���˵��������ʱ������״̬�Ĵ���3��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTAT3_UNION */
#define SOC_SCTRL_SCPERSTAT3_ADDR(base)               ((base) + (0x07C))

/* �Ĵ���˵����������λʹ�ܼĴ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTEN0_UNION */
#define SOC_SCTRL_SCPERRSTEN0_ADDR(base)              ((base) + (0x080))

/* �Ĵ���˵����������λ����Ĵ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTDIS0_UNION */
#define SOC_SCTRL_SCPERRSTDIS0_ADDR(base)             ((base) + (0x084))

/* �Ĵ���˵����������λ״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTSTAT0_UNION */
#define SOC_SCTRL_SCPERRSTSTAT0_ADDR(base)            ((base) + (0x088))

/* �Ĵ���˵����������λʹ�ܼĴ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTEN1_UNION */
#define SOC_SCTRL_SCPERRSTEN1_ADDR(base)              ((base) + (0x08C))

/* �Ĵ���˵����������λ����Ĵ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTDIS1_UNION */
#define SOC_SCTRL_SCPERRSTDIS1_ADDR(base)             ((base) + (0x090))

/* �Ĵ���˵����������λ״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTSTAT1_UNION */
#define SOC_SCTRL_SCPERRSTSTAT1_ADDR(base)            ((base) + (0x094))

/* �Ĵ���˵����������λʹ�ܼĴ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTEN2_UNION */
#define SOC_SCTRL_SCPERRSTEN2_ADDR(base)              ((base) + (0x098))

/* �Ĵ���˵����������λ����Ĵ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTDIS2_UNION */
#define SOC_SCTRL_SCPERRSTDIS2_ADDR(base)             ((base) + (0x09C))

/* �Ĵ���˵����������λ״̬�Ĵ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTSTAT2_UNION */
#define SOC_SCTRL_SCPERRSTSTAT2_ADDR(base)            ((base) + (0x0A0))

/* �Ĵ���˵����IP�����߹������ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCIPCLKRSTBUS_UNION */
#define SOC_SCTRL_SCIPCLKRSTBUS_ADDR(base)            ((base) + (0x0A4))

/* �Ĵ���˵����������ϵͳISOʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCISOEN_UNION */
#define SOC_SCTRL_SCISOEN_ADDR(base)                  ((base) + (0x0C0))

/* �Ĵ���˵����������ϵͳISOʹ�ܳ����Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCISODIS_UNION */
#define SOC_SCTRL_SCISODIS_ADDR(base)                 ((base) + (0x0C4))

/* �Ĵ���˵����������ϵͳISOʹ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCISOSTAT_UNION */
#define SOC_SCTRL_SCISOSTAT_ADDR(base)                ((base) + (0x0C8))

/* �Ĵ���˵����������ϵͳ��Դʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCPWREN_UNION */
#define SOC_SCTRL_SCPWREN_ADDR(base)                  ((base) + (0x0D0))

/* �Ĵ���˵����������ϵͳ��Դʹ�ܳ����Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCPWRDIS_UNION */
#define SOC_SCTRL_SCPWRDIS_ADDR(base)                 ((base) + (0x0D4))

/* �Ĵ���˵����������ϵͳ��Դʹ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCPWRSTAT_UNION */
#define SOC_SCTRL_SCPWRSTAT_ADDR(base)                ((base) + (0x0D8))

/* �Ĵ���˵����������ϵͳ���յ�Դ״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCPWRACK_UNION */
#define SOC_SCTRL_SCPWRACK_ADDR(base)                 ((base) + (0x0DC))

/* �Ĵ���˵��������������ʱ�����üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERPWRDOWNTIME_UNION */
#define SOC_SCTRL_SCPERPWRDOWNTIME_ADDR(base)         ((base) + (0x0E0))

/* �Ĵ���˵�����������ϵ�ʱ�����üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERPWRUPTIME_UNION */
#define SOC_SCTRL_SCPERPWRUPTIME_ADDR(base)           ((base) + (0x0E4))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCCLKDIV0_UNION */
#define SOC_SCTRL_SCCLKDIV0_ADDR(base)                ((base) + (0x100))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCCLKDIV1_UNION */
#define SOC_SCTRL_SCCLKDIV1_ADDR(base)                ((base) + (0x104))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCCLKDIV2_UNION */
#define SOC_SCTRL_SCCLKDIV2_ADDR(base)                ((base) + (0x108))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���3��
   λ����UNION�ṹ:  SOC_SCTRL_SCCLKDIV3_UNION */
#define SOC_SCTRL_SCCLKDIV3_ADDR(base)                ((base) + (0x10C))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���4��
   λ����UNION�ṹ:  SOC_SCTRL_SCCLKDIV4_UNION */
#define SOC_SCTRL_SCCLKDIV4_ADDR(base)                ((base) + (0x110))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���5��
   λ����UNION�ṹ:  SOC_SCTRL_SCCLKDIV5_UNION */
#define SOC_SCTRL_SCCLKDIV5_ADDR(base)                ((base) + (0x114))

/* �Ĵ���˵����������ƼĴ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERCTRL0_UNION */
#define SOC_SCTRL_SCPERCTRL0_ADDR(base)               ((base) + (0x200))

/* �Ĵ���˵����������ƼĴ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERCTRL1_UNION */
#define SOC_SCTRL_SCPERCTRL1_ADDR(base)               ((base) + (0x204))

/* �Ĵ���˵����������ƼĴ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERCTRL2_UNION */
#define SOC_SCTRL_SCPERCTRL2_ADDR(base)               ((base) + (0x208))

/* �Ĵ���˵����������ƼĴ���3��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERCTRL3_UNION */
#define SOC_SCTRL_SCPERCTRL3_ADDR(base)               ((base) + (0x20C))

/* �Ĵ���˵����������ƼĴ���4��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERCTRL4_UNION */
#define SOC_SCTRL_SCPERCTRL4_ADDR(base)               ((base) + (0x210))

/* �Ĵ���˵����������ƼĴ���5��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERCTRL5_UNION */
#define SOC_SCTRL_SCPERCTRL5_ADDR(base)               ((base) + (0x214))

/* �Ĵ���˵����������ƼĴ���6��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERCTRL6_UNION */
#define SOC_SCTRL_SCPERCTRL6_ADDR(base)               ((base) + (0x218))

/* �Ĵ���˵��������״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS0_UNION */
#define SOC_SCTRL_SCPERSTATUS0_ADDR(base)             ((base) + (0x21C))

/* �Ĵ���˵��������״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS1_UNION */
#define SOC_SCTRL_SCPERSTATUS1_ADDR(base)             ((base) + (0x220))

/* �Ĵ���˵��������״̬�Ĵ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS2_UNION */
#define SOC_SCTRL_SCPERSTATUS2_ADDR(base)             ((base) + (0x224))

/* �Ĵ���˵��������״̬�Ĵ���3��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS3_UNION */
#define SOC_SCTRL_SCPERSTATUS3_ADDR(base)             ((base) + (0x228))

/* �Ĵ���˵��������״̬�Ĵ���4��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS4_UNION */
#define SOC_SCTRL_SCPERSTATUS4_ADDR(base)             ((base) + (0x22C))

/* �Ĵ���˵��������״̬�Ĵ���5��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS5_UNION */
#define SOC_SCTRL_SCPERSTATUS5_ADDR(base)             ((base) + (0x230))

/* �Ĵ���˵��������״̬�Ĵ���6��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS6_UNION */
#define SOC_SCTRL_SCPERSTATUS6_ADDR(base)             ((base) + (0x234))

/* �Ĵ���˵��������״̬�Ĵ���7��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS7_UNION */
#define SOC_SCTRL_SCPERSTATUS7_ADDR(base)             ((base) + (0x238))

/* �Ĵ���˵��������״̬�Ĵ���8��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS8_UNION */
#define SOC_SCTRL_SCPERSTATUS8_ADDR(base)             ((base) + (0x23C))

/* �Ĵ���˵��������״̬�Ĵ���9��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS9_UNION */
#define SOC_SCTRL_SCPERSTATUS9_ADDR(base)             ((base) + (0x240))

/* �Ĵ���˵��������״̬�Ĵ���10��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS10_UNION */
#define SOC_SCTRL_SCPERSTATUS10_ADDR(base)            ((base) + (0x244))

/* �Ĵ���˵��������״̬�Ĵ���11��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS11_UNION */
#define SOC_SCTRL_SCPERSTATUS11_ADDR(base)            ((base) + (0x248))

/* �Ĵ���˵��������״̬�Ĵ���12��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS12_UNION */
#define SOC_SCTRL_SCPERSTATUS12_ADDR(base)            ((base) + (0x24C))

/* �Ĵ���˵��������״̬�Ĵ���13��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS13_UNION */
#define SOC_SCTRL_SCPERSTATUS13_ADDR(base)            ((base) + (0x250))

/* �Ĵ���˵��������״̬�Ĵ���14��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERSTATUS14_UNION */
#define SOC_SCTRL_SCPERSTATUS14_ADDR(base)            ((base) + (0x254))

/* �Ĵ���˵����������ƼĴ���7��
   λ����UNION�ṹ:  SOC_SCTRL_SCPERCTRL7_UNION */
#define SOC_SCTRL_SCPERCTRL7_ADDR(base)               ((base) + (0x270))

/* �Ĵ���˵�����ڲ�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCINNERSTAT_UNION */
#define SOC_SCTRL_SCINNERSTAT_ADDR(base)              ((base) + (0x280))

/* �Ĵ���˵��������ָʾϵͳ������������˯�ߵ�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCDEEPSLEEPED_UNION */
#define SOC_SCTRL_SCDEEPSLEEPED_ADDR(base)            ((base) + (0x300))

/* �Ĵ���˵����MRB EFUSE BUSY״ָ̬ʾ�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCMRBBUSYSTAT_UNION */
#define SOC_SCTRL_SCMRBBUSYSTAT_ADDR(base)            ((base) + (0x304))

/* �Ĵ���˵�������ڱ��������ڵ�ַ�ļĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCSWADDR_UNION */
#define SOC_SCTRL_SCSWADDR_ADDR(base)                 ((base) + (0x308))

/* �Ĵ���˵�������ڱ���DDRѵ�����ݵĵ�ַ�ļĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCDDRADDR_UNION */
#define SOC_SCTRL_SCDDRADDR_ADDR(base)                ((base) + (0x30C))

/* �Ĵ���˵�������ڱ���DDRѵ�����ݵļĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCDDRDATA_UNION */
#define SOC_SCTRL_SCDDRDATA_ADDR(base)                ((base) + (0x310))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA0_UNION */
#define SOC_SCTRL_SCBAKDATA0_ADDR(base)               ((base) + (0x314))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA1_UNION */
#define SOC_SCTRL_SCBAKDATA1_ADDR(base)               ((base) + (0x318))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA2_UNION */
#define SOC_SCTRL_SCBAKDATA2_ADDR(base)               ((base) + (0x31C))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���3��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA3_UNION */
#define SOC_SCTRL_SCBAKDATA3_ADDR(base)               ((base) + (0x320))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���4��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA4_UNION */
#define SOC_SCTRL_SCBAKDATA4_ADDR(base)               ((base) + (0x324))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���5��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA5_UNION */
#define SOC_SCTRL_SCBAKDATA5_ADDR(base)               ((base) + (0x328))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���6��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA6_UNION */
#define SOC_SCTRL_SCBAKDATA6_ADDR(base)               ((base) + (0x32C))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���7��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA7_UNION */
#define SOC_SCTRL_SCBAKDATA7_ADDR(base)               ((base) + (0x330))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���8��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA8_UNION */
#define SOC_SCTRL_SCBAKDATA8_ADDR(base)               ((base) + (0x334))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���9��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA9_UNION */
#define SOC_SCTRL_SCBAKDATA9_ADDR(base)               ((base) + (0x338))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���10��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA10_UNION */
#define SOC_SCTRL_SCBAKDATA10_ADDR(base)              ((base) + (0x33C))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���11��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA11_UNION */
#define SOC_SCTRL_SCBAKDATA11_ADDR(base)              ((base) + (0x340))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���12��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA12_UNION */
#define SOC_SCTRL_SCBAKDATA12_ADDR(base)              ((base) + (0x344))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���13��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA13_UNION */
#define SOC_SCTRL_SCBAKDATA13_ADDR(base)              ((base) + (0x348))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���14��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA14_UNION */
#define SOC_SCTRL_SCBAKDATA14_ADDR(base)              ((base) + (0x34C))

/* �Ĵ���˵�����������ʹ�õĴ洢���ݼĴ���15��
   λ����UNION�ṹ:  SOC_SCTRL_SCBAKDATA15_UNION */
#define SOC_SCTRL_SCBAKDATA15_ADDR(base)              ((base) + (0x350))

/* �Ĵ���˵�����ۺϺ���ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCINT_GATHER_STAT_UNION */
#define SOC_SCTRL_SCINT_GATHER_STAT_ADDR(base)        ((base) + (0x450))

/* �Ĵ���˵�����ж��������üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCINT_MASK_UNION */
#define SOC_SCTRL_SCINT_MASK_ADDR(base)               ((base) + (0x454))

/* �Ĵ���˵����ԭʼ�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCINT_STAT_UNION */
#define SOC_SCTRL_SCINT_STAT_ADDR(base)               ((base) + (0x458))

/* �Ĵ���˵����DRX�жϷ������üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCDRX_INT_CFG_UNION */
#define SOC_SCTRL_SCDRX_INT_CFG_ADDR(base)            ((base) + (0x45C))

/* �Ĵ���˵����LPMCU WFI�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCLPMCUWFI_INT_UNION */
#define SOC_SCTRL_SCLPMCUWFI_INT_ADDR(base)           ((base) + (0x460))

/* �Ĵ���˵�����ж��������üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCINT_MASK1_UNION */
#define SOC_SCTRL_SCINT_MASK1_ADDR(base)              ((base) + (0x464))

/* �Ĵ���˵����ԭʼ�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCINT_STAT1_UNION */
#define SOC_SCTRL_SCINT_STAT1_ADDR(base)              ((base) + (0x468))

/* �Ĵ���˵�����ж��������üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCINT_MASK2_UNION */
#define SOC_SCTRL_SCINT_MASK2_ADDR(base)              ((base) + (0x46C))

/* �Ĵ���˵����ԭʼ�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCINT_STAT2_UNION */
#define SOC_SCTRL_SCINT_STAT2_ADDR(base)              ((base) + (0x470))

/* �Ĵ���˵����MALI DBGACK BYPASS���üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCMALIBYPCFG_UNION */
#define SOC_SCTRL_SCMALIBYPCFG_ADDR(base)             ((base) + (0x48C))

/* �Ĵ���˵����LPMCU��ϵͳʱ��ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCLPMCUCLKEN_UNION */
#define SOC_SCTRL_SCLPMCUCLKEN_ADDR(base)             ((base) + (0x500))

/* �Ĵ���˵����LPMCU��ϵͳ��λʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCLPMCURSTEN_UNION */
#define SOC_SCTRL_SCLPMCURSTEN_ADDR(base)             ((base) + (0x504))

/* �Ĵ���˵����LPMCU��ϵͳ��λ����Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCLPMCURSTDIS_UNION */
#define SOC_SCTRL_SCLPMCURSTDIS_ADDR(base)            ((base) + (0x508))

/* �Ĵ���˵����LPMCU��ϵͳ��λʹ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCLPMCURSTSTAT_UNION */
#define SOC_SCTRL_SCLPMCURSTSTAT_ADDR(base)           ((base) + (0x50C))

/* �Ĵ���˵����LPMCU��ϵͳ�������üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCLPMCUCTRL_UNION */
#define SOC_SCTRL_SCLPMCUCTRL_ADDR(base)              ((base) + (0x510))

/* �Ĵ���˵����LPMCU��ϵͳ״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCLPMCUSTAT_UNION */
#define SOC_SCTRL_SCLPMCUSTAT_ADDR(base)              ((base) + (0x514))

/* �Ĵ���˵����LPMCU RAM ���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCLPMCURAMCTRL_UNION */
#define SOC_SCTRL_SCLPMCURAMCTRL_ADDR(base)           ((base) + (0x518))

/* �Ĵ���˵����BBPDRX��ϵͳ״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCBBPDRXSTAT0_UNION */
#define SOC_SCTRL_SCBBPDRXSTAT0_ADDR(base)            ((base) + (0x530))

/* �Ĵ���˵����BBPDRX��ϵͳ״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_SCTRL_SCBBPDRXSTAT1_UNION */
#define SOC_SCTRL_SCBBPDRXSTAT1_ADDR(base)            ((base) + (0x534))

/* �Ĵ���˵����BBPDRX��ϵͳ״̬�Ĵ���2��
   λ����UNION�ṹ:  SOC_SCTRL_SCBBPDRXSTAT2_UNION */
#define SOC_SCTRL_SCBBPDRXSTAT2_ADDR(base)            ((base) + (0x538))

/* �Ĵ���˵����BBPDRX��ϵͳ״̬�Ĵ���3��
   λ����UNION�ṹ:  SOC_SCTRL_SCBBPDRXSTAT3_UNION */
#define SOC_SCTRL_SCBBPDRXSTAT3_ADDR(base)            ((base) + (0x53C))

/* �Ĵ���˵����BBPDRX��ϵͳ״̬�Ĵ���4��
   λ����UNION�ṹ:  SOC_SCTRL_SCBBPDRXSTAT4_UNION */
#define SOC_SCTRL_SCBBPDRXSTAT4_ADDR(base)            ((base) + (0x540))

/* �Ĵ���˵����A53 EVENT���μĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCA53_EVENT_MASK_UNION */
#define SOC_SCTRL_SCA53_EVENT_MASK_ADDR(base)         ((base) + (0x550))

/* �Ĵ���˵����A57 EVENT���μĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCA57_EVENT_MASK_UNION */
#define SOC_SCTRL_SCA57_EVENT_MASK_ADDR(base)         ((base) + (0x554))

/* �Ĵ���˵����IOMCU EVENT���μĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCIOMCU_EVENT_MASK_UNION */
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_ADDR(base)       ((base) + (0x558))

/* �Ĵ���˵����LPMCU EVENT���μĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCLPMCU_EVENT_MASK_UNION */
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_ADDR(base)       ((base) + (0x55C))

/* �Ĵ���˵����MCPU EVENT���μĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCMCPU_EVENT_MASK_UNION */
#define SOC_SCTRL_SCMCPU_EVENT_MASK_ADDR(base)        ((base) + (0x560))

/* �Ĵ���˵����EVENT״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCEVENT_STAT_UNION */
#define SOC_SCTRL_SCEVENT_STAT_ADDR(base)             ((base) + (0x564))

/* �Ĵ���˵����MCPU EVENT���μĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCISPA7_EVENT_MASK_UNION */
#define SOC_SCTRL_SCISPA7_EVENT_MASK_ADDR(base)       ((base) + (0x568))

/* �Ĵ���˵����IOMCUʱ�ӿ��ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCIOMCUCLKCTRL_UNION */
#define SOC_SCTRL_SCIOMCUCLKCTRL_ADDR(base)           ((base) + (0x580))

/* �Ĵ���˵����IOMCUʱ�ӿ����ź�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCIOMCUCLKSTAT_UNION */
#define SOC_SCTRL_SCIOMCUCLKSTAT_ADDR(base)           ((base) + (0x584))

/* �Ĵ���˵����IOMCU��ϵͳʱ��ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCIOMCUCLKEN_UNION */
#define SOC_SCTRL_SCIOMCUCLKEN_ADDR(base)             ((base) + (0x588))

/* �Ĵ���˵����IOMCU��ϵͳ��λʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCIOMCURSTEN_UNION */
#define SOC_SCTRL_SCIOMCURSTEN_ADDR(base)             ((base) + (0x58C))

/* �Ĵ���˵����IOMCU��ϵͳ��λ����Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCIOMCURSTDIS_UNION */
#define SOC_SCTRL_SCIOMCURSTDIS_ADDR(base)            ((base) + (0x590))

/* �Ĵ���˵����IOMCU��ϵͳ��λʹ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCIOMCURSTSTAT_UNION */
#define SOC_SCTRL_SCIOMCURSTSTAT_ADDR(base)           ((base) + (0x594))

/* �Ĵ���˵����IOMCU��ϵͳ�������üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCIOMCUCTRL_UNION */
#define SOC_SCTRL_SCIOMCUCTRL_ADDR(base)              ((base) + (0x598))

/* �Ĵ���˵����IOMCU��ϵͳ״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCIOMCUSTAT_UNION */
#define SOC_SCTRL_SCIOMCUSTAT_ADDR(base)              ((base) + (0x59C))

/* �Ĵ���˵����JTAGѡ����ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCJTAG_SEL_UNION */
#define SOC_SCTRL_SCJTAG_SEL_ADDR(base)               ((base) + (0x800))

/* �Ĵ���˵����MODEM_KEY0��
   λ����UNION�ṹ:  SOC_SCTRL_SCMODEM_KEY0_UNION */
#define SOC_SCTRL_SCMODEM_KEY0_ADDR(base)             ((base) + (0x804))

/* �Ĵ���˵����MODEM_KEY1��
   λ����UNION�ṹ:  SOC_SCTRL_SCMODEM_KEY1_UNION */
#define SOC_SCTRL_SCMODEM_KEY1_ADDR(base)             ((base) + (0x808))

/* �Ĵ���˵����MODEM_KEY2��
   λ����UNION�ṹ:  SOC_SCTRL_SCMODEM_KEY2_UNION */
#define SOC_SCTRL_SCMODEM_KEY2_ADDR(base)             ((base) + (0x80C))

/* �Ĵ���˵����MODEM_KEY3��
   λ����UNION�ṹ:  SOC_SCTRL_SCMODEM_KEY3_UNION */
#define SOC_SCTRL_SCMODEM_KEY3_ADDR(base)             ((base) + (0x810))

/* �Ĵ���˵����DJTAG���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCCFG_DJTAG_UNION */
#define SOC_SCTRL_SCCFG_DJTAG_ADDR(base)              ((base) + (0x814))

/* �Ĵ���˵����CP15DISABLE���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCCP15_DISABLE_UNION */
#define SOC_SCTRL_SCCP15_DISABLE_ADDR(base)           ((base) + (0x818))

/* �Ĵ���˵����ʱ�Ӽ���״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCCLKCNTSTAT_UNION */
#define SOC_SCTRL_SCCLKCNTSTAT_ADDR(base)             ((base) + (0x81C))

/* �Ĵ���˵����ʱ�Ӽ������üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCCLKCNTCFG_UNION */
#define SOC_SCTRL_SCCLKCNTCFG_ADDR(base)              ((base) + (0x820))

/* �Ĵ���˵����ʱ�Ӽ�ؿ��ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCCLKMONCTRL_UNION */
#define SOC_SCTRL_SCCLKMONCTRL_ADDR(base)             ((base) + (0x824))

/* �Ĵ���˵����ʱ�Ӽ���ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCCLKMONINT_UNION */
#define SOC_SCTRL_SCCLKMONINT_ADDR(base)              ((base) + (0x828))

/* �Ĵ���˵����ARM debug en���üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCCFG_ARM_DBGEN_UNION */
#define SOC_SCTRL_SCCFG_ARM_DBGEN_ADDR(base)          ((base) + (0x82C))

/* �Ĵ���˵����ARM debug key0���üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCARM_DBG_KEY0_UNION */
#define SOC_SCTRL_SCARM_DBG_KEY0_ADDR(base)           ((base) + (0x830))

/* �Ĵ���˵����ARM debug key1���üĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCARM_DBG_KEY1_UNION */
#define SOC_SCTRL_SCARM_DBG_KEY1_ADDR(base)           ((base) + (0x834))

/* �Ĵ���˵����ARM debug en״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCARM_DBGEN_STAT_UNION */
#define SOC_SCTRL_SCARM_DBGEN_STAT_ADDR(base)         ((base) + (0x838))

/* �Ĵ���˵����EFUSE PAD��д���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCEFUSECTRL_UNION */
#define SOC_SCTRL_SCEFUSECTRL_ADDR(base)              ((base) + (0x83C))

/* �Ĵ���˵����SECSʱ���ſؼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCEFUSESEL_UNION */
#define SOC_SCTRL_SCEFUSESEL_ADDR(base)               ((base) + (0x840))

/* �Ĵ���˵����EFUSE SECURITY״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCSECURITYSTAT_UNION */
#define SOC_SCTRL_SCSECURITYSTAT_ADDR(base)           ((base) + (0x844))

/* �Ĵ���˵����EFUSE CHIP_ID0�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCCHIP_ID0_UNION */
#define SOC_SCTRL_SCCHIP_ID0_ADDR(base)               ((base) + (0x848))

/* �Ĵ���˵����EFUSE CHIP_ID1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCCHIP_ID1_UNION */
#define SOC_SCTRL_SCCHIP_ID1_ADDR(base)               ((base) + (0x84C))

/* �Ĵ���˵����CPU��ȫ���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCCPUSECCTRL_UNION */
#define SOC_SCTRL_SCCPUSECCTRL_ADDR(base)             ((base) + (0x850))

/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���0����ȫ����
   λ����UNION�ṹ:  SOC_SCTRL_SCPEREN0_SEC_UNION */
#define SOC_SCTRL_SCPEREN0_SEC_ADDR(base)             ((base) + (0x900))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���0����ȫ����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERDIS0_SEC_UNION */
#define SOC_SCTRL_SCPERDIS0_SEC_ADDR(base)            ((base) + (0x904))

/* �Ĵ���˵��������ʱ��ʹ��״̬�Ĵ���0����ȫ����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERCLKEN0_SEC_UNION */
#define SOC_SCTRL_SCPERCLKEN0_SEC_ADDR(base)          ((base) + (0x908))

/* �Ĵ���˵����������λʹ�ܼĴ���0����ȫ����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTEN0_SEC_UNION */
#define SOC_SCTRL_SCPERRSTEN0_SEC_ADDR(base)          ((base) + (0x950))

/* �Ĵ���˵����������λ����Ĵ���0����ȫ����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTDIS0_SEC_UNION */
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ADDR(base)         ((base) + (0x954))

/* �Ĵ���˵����������λ״̬�Ĵ���0����ȫ����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTSTAT0_SEC_UNION */
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ADDR(base)        ((base) + (0x958))

/* �Ĵ���˵������ȫTIMER���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCTRL_SCTIMERCTRL_SEC_UNION */
#define SOC_SCTRL_SCTIMERCTRL_SEC_ADDR(base)          ((base) + (0x9A0))

/* �Ĵ���˵����������λʹ�ܼĴ���1����ȫ����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTEN1_SEC_UNION */
#define SOC_SCTRL_SCPERRSTEN1_SEC_ADDR(base)          ((base) + (0xA50))

/* �Ĵ���˵����������λ����Ĵ���1����ȫ����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTDIS1_SEC_UNION */
#define SOC_SCTRL_SCPERRSTDIS1_SEC_ADDR(base)         ((base) + (0xA54))

/* �Ĵ���˵����������λ״̬�Ĵ���1����ȫ����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTSTAT1_SEC_UNION */
#define SOC_SCTRL_SCPERRSTSTAT1_SEC_ADDR(base)        ((base) + (0xA58))

/* �Ĵ���˵����������λʹ�ܼĴ���2����ȫ����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTEN2_SEC_UNION */
#define SOC_SCTRL_SCPERRSTEN2_SEC_ADDR(base)          ((base) + (0xB50))

/* �Ĵ���˵����������λ����Ĵ���2����ȫ����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTDIS2_SEC_UNION */
#define SOC_SCTRL_SCPERRSTDIS2_SEC_ADDR(base)         ((base) + (0xB54))

/* �Ĵ���˵����������λ״̬�Ĵ���2����ȫ����
   λ����UNION�ṹ:  SOC_SCTRL_SCPERRSTSTAT2_SEC_UNION */
#define SOC_SCTRL_SCPERRSTSTAT2_SEC_ADDR(base)        ((base) + (0xB58))

/* �Ĵ���˵����SOCID�Ĵ���0��
   λ����UNION�ṹ:  SOC_SCTRL_SCSOCID0_UNION */
#define SOC_SCTRL_SCSOCID0_ADDR(base)                 ((base) + (0xE00))





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
 �ṹ��    : SOC_SCTRL_SCCTRL_UNION
 �ṹ˵��  : SCCTRL �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000012�����:32
 �Ĵ���˵��: ϵͳ�������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modectrl                                 : 3;  /* bit[0-2]  : ϵͳģʽ���ơ����ﶨ����ϵͳ�����Ĺ���ģʽ��
                                                                                    000��SLEEP��
                                                                                    001��DOZE��
                                                                                    01X�� SLOW��
                                                                                    1XX:��NORMAL�� */
        unsigned int  modestatus                               : 4;  /* bit[3-6]  : ָʾϵͳ������ϵͳ״̬����ǰ����ģʽ��
                                                                                    0000��SLEEP��
                                                                                    0001��DOZE��
                                                                                    0011��XTAL CTL��
                                                                                    1000��XTAL_OFF��
                                                                                    1011��SW to XTAL��
                                                                                    1001��SW from XTAL��
                                                                                    0010��SLOW��
                                                                                    0110��PLL CTL��
                                                                                    1110��SW to PLL��
                                                                                    1010��SW from PLL��
                                                                                    0100��NORMAL��
                                                                                    Others�������� */
        unsigned int  reserved_0                               : 1;  /* bit[7]    : ������ */
        unsigned int  timeforcehigh                            : 1;  /* bit[8]    : Timerʹ�ܶ�ǿ�����ߵ�Ӳ��ʹ�����á�
                                                                                    0��Ӳ���������Զ�������
                                                                                    1����ϵͳʱ����32Kʱ��Ӳ���Զ�ǿ������Timer��ʹ�ܡ� */
        unsigned int  timeren0sel                              : 1;  /* bit[9]    : Time0ʱ��ʹ�ܲο�ʱ��ѡ��
                                                                                    0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                                                    1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren0ov                               : 1;  /* bit[10]   : Timer0ʱ��ʹ�ܿ��ơ�
                                                                                    0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren0sel]ָ����
                                                                                    1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren1sel                              : 1;  /* bit[11]   : Time1ʱ��ʹ�ܲο�ʱ��ѡ��
                                                                                    0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                                                    1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren1ov                               : 1;  /* bit[12]   : Timer1ʱ��ʹ�ܿ��ơ�
                                                                                    0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren1sel]ָ����
                                                                                    1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  mdmtimer_stop_dbg_bp                     : 1;  /* bit[13]   : modem timer auto stop in modem cpu debug bypass
                                                                                    0:modem timer auto stop in modem cpu debug
                                                                                    1:modem timer not auto stop in modem cpu debug�� */
        unsigned int  reserved_1                               : 1;  /* bit[14]   : ������ */
        unsigned int  reserved_2                               : 1;  /* bit[15]   : ������ */
        unsigned int  sc_aonoc_asp_mst_i_mainnopendingtrans_bp : 1;  /* bit[16]   : sc_aonoc_asp_mst_i_mainnopendingtrans bypass
                                                                                    0:bypass;
                                                                                    1:sc_aonoc_asp_mst_i_mainnopendingtrans is one input of sc_noc_aobus_idle_flag is AndGate�� */
        unsigned int  timeren4sel                              : 1;  /* bit[17]   : Time4ʱ��ʹ�ܲο�ʱ��ѡ��
                                                                                    0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                                                    1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren4ov                               : 1;  /* bit[18]   : Timer4ʱ��ʹ�ܿ��ơ�
                                                                                    0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren4sel]ָ����
                                                                                    1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren5sel                              : 1;  /* bit[19]   : Time5ʱ��ʹ�ܲο�ʱ��ѡ��
                                                                                    0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                                                    1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren5ov                               : 1;  /* bit[20]   : Timer5ʱ��ʹ�ܿ��ơ�
                                                                                    0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren5sel]ָ����
                                                                                    1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren6sel                              : 1;  /* bit[21]   : Time6ʱ��ʹ�ܲο�ʱ��ѡ��
                                                                                    0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                                                    1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren6ov                               : 1;  /* bit[22]   : Timer6ʱ��ʹ�ܿ��ơ�
                                                                                    0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren6sel]ָ����
                                                                                    1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren7sel                              : 1;  /* bit[23]   : Time7ʱ��ʹ�ܲο�ʱ��ѡ��
                                                                                    0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                                                    1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren7ov                               : 1;  /* bit[24]   : Timer7ʱ��ʹ�ܿ��ơ�
                                                                                    0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren7sel]ָ����
                                                                                    1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  deepsleepen                              : 1;  /* bit[25]   : ����DEEP SLEEPģʽʹ�ܼĴ��������ø�bit����״̬������������̣���NORMALģʽ�����ã����modectrl�����ã�
                                                                                    0����ʾ��ʹ�ܣ�
                                                                                    1����ʾʹ�ܡ� */
        unsigned int  reserved_3                               : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_SCTRL_SCCTRL_UNION;
#endif
#define SOC_SCTRL_SCCTRL_modectrl_START                                  (0)
#define SOC_SCTRL_SCCTRL_modectrl_END                                    (2)
#define SOC_SCTRL_SCCTRL_modestatus_START                                (3)
#define SOC_SCTRL_SCCTRL_modestatus_END                                  (6)
#define SOC_SCTRL_SCCTRL_timeforcehigh_START                             (8)
#define SOC_SCTRL_SCCTRL_timeforcehigh_END                               (8)
#define SOC_SCTRL_SCCTRL_timeren0sel_START                               (9)
#define SOC_SCTRL_SCCTRL_timeren0sel_END                                 (9)
#define SOC_SCTRL_SCCTRL_timeren0ov_START                                (10)
#define SOC_SCTRL_SCCTRL_timeren0ov_END                                  (10)
#define SOC_SCTRL_SCCTRL_timeren1sel_START                               (11)
#define SOC_SCTRL_SCCTRL_timeren1sel_END                                 (11)
#define SOC_SCTRL_SCCTRL_timeren1ov_START                                (12)
#define SOC_SCTRL_SCCTRL_timeren1ov_END                                  (12)
#define SOC_SCTRL_SCCTRL_mdmtimer_stop_dbg_bp_START                      (13)
#define SOC_SCTRL_SCCTRL_mdmtimer_stop_dbg_bp_END                        (13)
#define SOC_SCTRL_SCCTRL_sc_aonoc_asp_mst_i_mainnopendingtrans_bp_START  (16)
#define SOC_SCTRL_SCCTRL_sc_aonoc_asp_mst_i_mainnopendingtrans_bp_END    (16)
#define SOC_SCTRL_SCCTRL_timeren4sel_START                               (17)
#define SOC_SCTRL_SCCTRL_timeren4sel_END                                 (17)
#define SOC_SCTRL_SCCTRL_timeren4ov_START                                (18)
#define SOC_SCTRL_SCCTRL_timeren4ov_END                                  (18)
#define SOC_SCTRL_SCCTRL_timeren5sel_START                               (19)
#define SOC_SCTRL_SCCTRL_timeren5sel_END                                 (19)
#define SOC_SCTRL_SCCTRL_timeren5ov_START                                (20)
#define SOC_SCTRL_SCCTRL_timeren5ov_END                                  (20)
#define SOC_SCTRL_SCCTRL_timeren6sel_START                               (21)
#define SOC_SCTRL_SCCTRL_timeren6sel_END                                 (21)
#define SOC_SCTRL_SCCTRL_timeren6ov_START                                (22)
#define SOC_SCTRL_SCCTRL_timeren6ov_END                                  (22)
#define SOC_SCTRL_SCCTRL_timeren7sel_START                               (23)
#define SOC_SCTRL_SCCTRL_timeren7sel_END                                 (23)
#define SOC_SCTRL_SCCTRL_timeren7ov_START                                (24)
#define SOC_SCTRL_SCCTRL_timeren7ov_END                                  (24)
#define SOC_SCTRL_SCCTRL_deepsleepen_START                               (25)
#define SOC_SCTRL_SCCTRL_deepsleepen_END                                 (25)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCSYSSTAT_UNION
 �ṹ˵��  : SCSYSSTAT �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: ϵͳ״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reset_source : 32; /* bit[0-31]: д�����üĴ���д������ֵ�ᴥ��ϵͳ��λ��
                                                       �������üĴ���������λԴ��
                                                       ��λԴָʾ��
                                                       [17:14]:ddr_fatal_inter
                                                       0:no int 1:int
                                                       [13]:wait_ddr_selfreflash_timeout
                                                       0:no timeout 1:timeout
                                                       [12]:isp_a7_wd_rst_req
                                                       0:no rst req 1:rst req
                                                       [11]:ivp32_wd_rst_req
                                                       0:no rst req 1:rst req
                                                       [10]:modem_wd_rst_req
                                                       0:no rst req 1:rst req
                                                       [9]:asp_subsys_wd_req
                                                       0:no rst req 1:rst req
                                                       [8]:IOMCU_rst_req
                                                       0:no rst req 1:rst req
                                                       [7]:modem_tsensor_rst_req
                                                       0:no rst req 1:rst req
                                                       [6]:LPMCU_rst_req
                                                       0:no rst req 1:rst req
                                                       [5]:wd1_rst_req
                                                       0:no rst req 1:rst req
                                                       [4]:wd0_rst_req
                                                       0:no rst req 1:rst req
                                                       [3]:soft_rst_req
                                                       0:no rst req 1:rst req
                                                       [2]:g3d_tsensor_rst_req
                                                       0:no rst req 1:rst req
                                                       [1]:a53_tsensor1_rst_req
                                                       0:no rst req 1:rst req
                                                       [0]:a53_tsensor0_rst_req
                                                       0:no rst req 1:rst req�� */
    } reg;
} SOC_SCTRL_SCSYSSTAT_UNION;
#endif
#define SOC_SCTRL_SCSYSSTAT_reset_source_START  (0)
#define SOC_SCTRL_SCSYSSTAT_reset_source_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCXTALCTRL_UNION
 �ṹ˵��  : SCXTALCTRL �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00210280�����:32
 �Ĵ���˵��: ������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcxopresel_apb     : 1;  /* bit[0]    : ����ѡ��Ԥ���ã�
                                                              �´λ���ʱ�л���ѡ������ֻ��tcxosoft_apbΪ0����tcxohardcon_bypassΪ1ʱ�ù��ܲ���Ч���� */
        unsigned int  tcxohardcon_bypass : 1;  /* bit[1]    : ����ѡ��Ӳ���л����Σ�
                                                              1��ѡ��Ԥ���ù���
                                                              0��ѡ��Ӳ���Զ��л��� */
        unsigned int  tcxosel_apb        : 1;  /* bit[2]    : �������л�ѡ��
                                                              1��ѡ��TCXO1
                                                              0��ѡ��TCXO0�� */
        unsigned int  tcxosoft_apb       : 1;  /* bit[3]    : �������л�ѡ��
                                                              1��ѡ��tcxosel_apb
                                                              0��ѡ��Ԥ�л�����Ӳ���Զ��л��� */
        unsigned int  defau_tcxo         : 1;  /* bit[4]    : ��DRX�жϵ���Ĭ��ѡ��TCXO
                                                              1��ѡ����1
                                                              0��ѡ����0�� */
        unsigned int  tcxofast_ctrl0     : 1;  /* bit[5]    : ����0������������
                                                              1�������������ж�ֱ�Ӵ�tcxo�����ã�
                                                              0������������ϵͳ״̬���л���tcxo���� */
        unsigned int  tcxofast_ctrl1     : 1;  /* bit[6]    : ����1������������
                                                              1�������������ж�ֱ�Ӵ�tcxo�����ã�
                                                              0������������ϵͳ״̬���л���tcxo���� */
        unsigned int  ctrlen1_apb        : 1;  /* bit[7]    : ����1���ʹ�ܿ��ƣ�
                                                              1������ʹ��
                                                              0������ȥʹ�ܡ� */
        unsigned int  ctrlsel1_apb       : 1;  /* bit[8]    : ����1�������ѡ��
                                                              1��ѡ��ctrlen1_apb
                                                              0��ѡ��Ӳ���Զ����ơ� */
        unsigned int  ctrlen0_apb        : 1;  /* bit[9]    : ����0���ʹ�ܿ��ƣ�
                                                              1������ʹ��
                                                              0������ȥʹ�ܡ� */
        unsigned int  ctrlsel0_apb       : 1;  /* bit[10]   : ����0�������ѡ��
                                                              1��ѡ��ctrlen0_apb
                                                              0��ѡ��Ӳ���Զ����ơ� */
        unsigned int  timeout_bypass0    : 1;  /* bit[11]   : ״̬����⾧��0��ʱBYPASS����
                                                              1��BYPASSʹ��
                                                              0��BYPASSȥʹ�ܡ� */
        unsigned int  timeout_bypass1    : 1;  /* bit[12]   : ״̬����⾧��1��ʱBYPASS����
                                                              1��BYPASSʹ��
                                                              0��BYPASSȥʹ�ܡ� */
        unsigned int  tcxoseq_bypass     : 1;  /* bit[13]   : ״̬����⾧��ر����BYPASS���ƣ��͹���mp3�������ú�ϵͳģʽ����sleep���ر�TCXO��
                                                              1��BYPASSʹ��
                                                              0��BYPASSȥʹ�ܡ� */
        unsigned int  tcxoseq0_time      : 5;  /* bit[14-18]: �ؾ���0���ABB BUF��ʱ��������32KHZΪʱ�����ڡ� */
        unsigned int  tcxoseq1_time      : 5;  /* bit[19-23]: �ؾ���1���ABB BUF��ʱ��������32KHZΪʱ�����ڡ� */
        unsigned int  tcxodown_bypass0   : 1;  /* bit[24]   : ϵͳ����suspendʱ״̬���Ƿ�رվ���0��
                                                              0���ر�
                                                              1�����ر�
                                                              ��IOMCU���á� */
        unsigned int  tcxodown_bypass1   : 1;  /* bit[25]   : ϵͳ����suspendʱ״̬���Ƿ�رվ���1��
                                                              0���ر�
                                                              1�����ر�
                                                              ��IOMCU���á� */
        unsigned int  reserved           : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_SCTRL_SCXTALCTRL_UNION;
#endif
#define SOC_SCTRL_SCXTALCTRL_tcxopresel_apb_START      (0)
#define SOC_SCTRL_SCXTALCTRL_tcxopresel_apb_END        (0)
#define SOC_SCTRL_SCXTALCTRL_tcxohardcon_bypass_START  (1)
#define SOC_SCTRL_SCXTALCTRL_tcxohardcon_bypass_END    (1)
#define SOC_SCTRL_SCXTALCTRL_tcxosel_apb_START         (2)
#define SOC_SCTRL_SCXTALCTRL_tcxosel_apb_END           (2)
#define SOC_SCTRL_SCXTALCTRL_tcxosoft_apb_START        (3)
#define SOC_SCTRL_SCXTALCTRL_tcxosoft_apb_END          (3)
#define SOC_SCTRL_SCXTALCTRL_defau_tcxo_START          (4)
#define SOC_SCTRL_SCXTALCTRL_defau_tcxo_END            (4)
#define SOC_SCTRL_SCXTALCTRL_tcxofast_ctrl0_START      (5)
#define SOC_SCTRL_SCXTALCTRL_tcxofast_ctrl0_END        (5)
#define SOC_SCTRL_SCXTALCTRL_tcxofast_ctrl1_START      (6)
#define SOC_SCTRL_SCXTALCTRL_tcxofast_ctrl1_END        (6)
#define SOC_SCTRL_SCXTALCTRL_ctrlen1_apb_START         (7)
#define SOC_SCTRL_SCXTALCTRL_ctrlen1_apb_END           (7)
#define SOC_SCTRL_SCXTALCTRL_ctrlsel1_apb_START        (8)
#define SOC_SCTRL_SCXTALCTRL_ctrlsel1_apb_END          (8)
#define SOC_SCTRL_SCXTALCTRL_ctrlen0_apb_START         (9)
#define SOC_SCTRL_SCXTALCTRL_ctrlen0_apb_END           (9)
#define SOC_SCTRL_SCXTALCTRL_ctrlsel0_apb_START        (10)
#define SOC_SCTRL_SCXTALCTRL_ctrlsel0_apb_END          (10)
#define SOC_SCTRL_SCXTALCTRL_timeout_bypass0_START     (11)
#define SOC_SCTRL_SCXTALCTRL_timeout_bypass0_END       (11)
#define SOC_SCTRL_SCXTALCTRL_timeout_bypass1_START     (12)
#define SOC_SCTRL_SCXTALCTRL_timeout_bypass1_END       (12)
#define SOC_SCTRL_SCXTALCTRL_tcxoseq_bypass_START      (13)
#define SOC_SCTRL_SCXTALCTRL_tcxoseq_bypass_END        (13)
#define SOC_SCTRL_SCXTALCTRL_tcxoseq0_time_START       (14)
#define SOC_SCTRL_SCXTALCTRL_tcxoseq0_time_END         (18)
#define SOC_SCTRL_SCXTALCTRL_tcxoseq1_time_START       (19)
#define SOC_SCTRL_SCXTALCTRL_tcxoseq1_time_END         (23)
#define SOC_SCTRL_SCXTALCTRL_tcxodown_bypass0_START    (24)
#define SOC_SCTRL_SCXTALCTRL_tcxodown_bypass0_END      (24)
#define SOC_SCTRL_SCXTALCTRL_tcxodown_bypass1_START    (25)
#define SOC_SCTRL_SCXTALCTRL_tcxodown_bypass1_END      (25)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCXTALTIMEOUT0_UNION
 �ṹ˵��  : SCXTALTIMEOUT0 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000032�����:32
 �Ĵ���˵��: �����ȶ�ʱ�����üĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeoutcnt0_apb : 32; /* bit[0-31]: 32KHZʱ�����ڡ� */
    } reg;
} SOC_SCTRL_SCXTALTIMEOUT0_UNION;
#endif
#define SOC_SCTRL_SCXTALTIMEOUT0_timeoutcnt0_apb_START  (0)
#define SOC_SCTRL_SCXTALTIMEOUT0_timeoutcnt0_apb_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCXTALTIMEOUT1_UNION
 �ṹ˵��  : SCXTALTIMEOUT1 �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000032�����:32
 �Ĵ���˵��: �����ȶ�ʱ�����üĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeoutcnt1_apb : 32; /* bit[0-31]: 32KHZʱ�����ڡ� */
    } reg;
} SOC_SCTRL_SCXTALTIMEOUT1_UNION;
#endif
#define SOC_SCTRL_SCXTALTIMEOUT1_timeoutcnt1_apb_START  (0)
#define SOC_SCTRL_SCXTALTIMEOUT1_timeoutcnt1_apb_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCXTALSTAT_UNION
 �ṹ˵��  : SCXTALSTAT �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000E3F�����:32
 �Ĵ���˵��: �������״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcxo_en0        : 1;  /* bit[0]    : ����0������״̬
                                                           0:������ 1������򿪡� */
        unsigned int  tcxo_en1        : 1;  /* bit[1]    : ����1������״̬
                                                           0:������ 1������򿪡� */
        unsigned int  tcxo_timeout1   : 1;  /* bit[2]    : ����1��ʱ״̬
                                                           0��δ��ʱ��1����ʱ�� */
        unsigned int  tcxo_timeout0   : 1;  /* bit[3]    : ����0��ʱ״̬
                                                           0��δ��ʱ��1����ʱ�� */
        unsigned int  sysclk_en1      : 1;  /* bit[4]    : ����1��Դʹ��״̬
                                                           0���ر� 1���򿪡� */
        unsigned int  sysclk_en0      : 1;  /* bit[5]    : ����0��Դʹ��״̬
                                                           0���ر� 1���򿪡� */
        unsigned int  sysclk_sel      : 1;  /* bit[6]    : ����ѡ��״̬
                                                           0��tcxo0 1��tcxo1�� */
        unsigned int  clkgt_ctrl0     : 1;  /* bit[7]    : ����0���������clk gate�ź�
                                                           0���ر� 1���򿪡� */
        unsigned int  clkgt_ctrl1     : 1;  /* bit[8]    : ����1���������clk gate�ź�
                                                           0���ر� 1���򿪡� */
        unsigned int  clkgt_ctrl      : 1;  /* bit[9]    : ���������CRG��clk gate�ź�
                                                           0���ر� 1���򿪡� */
        unsigned int  abbbuf_en0      : 1;  /* bit[10]   : ABB BUF0��ʹ��״̬
                                                           0���ر� 1���򿪡� */
        unsigned int  abbbuf_en1      : 1;  /* bit[11]   : ABB BUF1��ʹ��״̬
                                                           0���ر� 1���򿪡� */
        unsigned int  tcxoseq_finish0 : 1;  /* bit[12]   : ����0�ر����ָʾ״̬
                                                           0��δ�ر� 1���ر���ɡ� */
        unsigned int  tcxoseq_finish1 : 1;  /* bit[13]   : ����1�ر����ָʾ״̬
                                                           0��δ�ر� 1���ر���ɡ� */
        unsigned int  reserved        : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_SCTRL_SCXTALSTAT_UNION;
#endif
#define SOC_SCTRL_SCXTALSTAT_tcxo_en0_START         (0)
#define SOC_SCTRL_SCXTALSTAT_tcxo_en0_END           (0)
#define SOC_SCTRL_SCXTALSTAT_tcxo_en1_START         (1)
#define SOC_SCTRL_SCXTALSTAT_tcxo_en1_END           (1)
#define SOC_SCTRL_SCXTALSTAT_tcxo_timeout1_START    (2)
#define SOC_SCTRL_SCXTALSTAT_tcxo_timeout1_END      (2)
#define SOC_SCTRL_SCXTALSTAT_tcxo_timeout0_START    (3)
#define SOC_SCTRL_SCXTALSTAT_tcxo_timeout0_END      (3)
#define SOC_SCTRL_SCXTALSTAT_sysclk_en1_START       (4)
#define SOC_SCTRL_SCXTALSTAT_sysclk_en1_END         (4)
#define SOC_SCTRL_SCXTALSTAT_sysclk_en0_START       (5)
#define SOC_SCTRL_SCXTALSTAT_sysclk_en0_END         (5)
#define SOC_SCTRL_SCXTALSTAT_sysclk_sel_START       (6)
#define SOC_SCTRL_SCXTALSTAT_sysclk_sel_END         (6)
#define SOC_SCTRL_SCXTALSTAT_clkgt_ctrl0_START      (7)
#define SOC_SCTRL_SCXTALSTAT_clkgt_ctrl0_END        (7)
#define SOC_SCTRL_SCXTALSTAT_clkgt_ctrl1_START      (8)
#define SOC_SCTRL_SCXTALSTAT_clkgt_ctrl1_END        (8)
#define SOC_SCTRL_SCXTALSTAT_clkgt_ctrl_START       (9)
#define SOC_SCTRL_SCXTALSTAT_clkgt_ctrl_END         (9)
#define SOC_SCTRL_SCXTALSTAT_abbbuf_en0_START       (10)
#define SOC_SCTRL_SCXTALSTAT_abbbuf_en0_END         (10)
#define SOC_SCTRL_SCXTALSTAT_abbbuf_en1_START       (11)
#define SOC_SCTRL_SCXTALSTAT_abbbuf_en1_END         (11)
#define SOC_SCTRL_SCXTALSTAT_tcxoseq_finish0_START  (12)
#define SOC_SCTRL_SCXTALSTAT_tcxoseq_finish0_END    (12)
#define SOC_SCTRL_SCXTALSTAT_tcxoseq_finish1_START  (13)
#define SOC_SCTRL_SCXTALSTAT_tcxoseq_finish1_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPPLLCTRL0_UNION
 �ṹ˵��  : SCPPLLCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00904B06�����:32
 �Ĵ���˵��: PPLL0���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll0_en       : 1;  /* bit[0-0]  : PPLL0���ʹ�ܿ��ƣ����յ�ʹ���ɸ������źš�IOMCU������ź�IOMCU_pll_ctrl��asp_ppll0_en_req ����
                                                          0��ȥʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  ppll0_bp       : 1;  /* bit[1-1]  : PPLL0 Bypass���ơ�
                                                          0������������
                                                          1��Bypass�� */
        unsigned int  ppll0_refdiv   : 6;  /* bit[2-7]  : PPLL0����ʱ�ӷ�Ƶ������Ƶ��=����ֵ+1�� */
        unsigned int  ppll0_fbdiv    : 12; /* bit[8-19] : PPLL0����ʱ��������Ƶ������Ƶ��=����ֵ+1
                                                          �� */
        unsigned int  ppll0_postdiv1 : 3;  /* bit[20-22]: PPLL0���ʱ�ӷ�Ƶ��1����Ƶ��=����ֵ+1�� */
        unsigned int  ppll0_postdiv2 : 3;  /* bit[23-25]: PPLL0���ʱ�ӷ�Ƶ��2����Ƶ��=����ֵ+1�� */
        unsigned int  reserved       : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_SCTRL_SCPPLLCTRL0_UNION;
#endif
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_en_START        (0)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_en_END          (0)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_bp_START        (1)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_bp_END          (1)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_refdiv_START    (2)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_refdiv_END      (7)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_fbdiv_START     (8)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_fbdiv_END       (19)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_postdiv1_START  (20)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_postdiv1_END    (22)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_postdiv2_START  (23)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_postdiv2_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPPLLCTRL1_UNION
 �ṹ˵��  : SCPPLLCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x06000000�����:32
 �Ĵ���˵��: PPLL0���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll0_fracdiv : 24; /* bit[0-23] : PPLL0����ʱ�ӷ�����Ƶ������Ƶ��=����ֵ+1�� */
        unsigned int  ppll0_int_mod : 1;  /* bit[24-24]: PPLL0������Ƶģʽ��
                                                         0��������Ƶģʽ��
                                                         1��������Ƶģʽ��
                                                         ע�⣺��PLL֧�ַ�����Ƶ��������Ƶģʽ������SSC��ʱ��Ҫ�����ֻʹ�÷�����Ƶģʽ�� */
        unsigned int  ppll0_cfg_vld : 1;  /* bit[25-25]: PPLL0������Ч��־��
                                                         0��������Ч��
                                                         1��������Ч�� */
        unsigned int  gt_clk_ppll0  : 1;  /* bit[26-26]: PPLL0�ſ��źš�
                                                         0��PPLL0���ʱ���ſأ�
                                                         1��PPLL0���ʱ�Ӳ��ſء����ȴ�PLL�ȶ���������ø�bit���� */
        unsigned int  reserved_0    : 1;  /* bit[27-27]: ������ */
        unsigned int  reserved_1    : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_SCTRL_SCPPLLCTRL1_UNION;
#endif
#define SOC_SCTRL_SCPPLLCTRL1_ppll0_fracdiv_START  (0)
#define SOC_SCTRL_SCPPLLCTRL1_ppll0_fracdiv_END    (23)
#define SOC_SCTRL_SCPPLLCTRL1_ppll0_int_mod_START  (24)
#define SOC_SCTRL_SCPPLLCTRL1_ppll0_int_mod_END    (24)
#define SOC_SCTRL_SCPPLLCTRL1_ppll0_cfg_vld_START  (25)
#define SOC_SCTRL_SCPPLLCTRL1_ppll0_cfg_vld_END    (25)
#define SOC_SCTRL_SCPPLLCTRL1_gt_clk_ppll0_START   (26)
#define SOC_SCTRL_SCPPLLCTRL1_gt_clk_ppll0_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPPLLSSCCTRL_UNION
 �ṹ˵��  : SCPPLLSSCCTRL �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x0000019F�����:32
 �Ĵ���˵��: PPLL0 SSC���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll0_ssc_reset      : 1;  /* bit[0]    : ��λ�źţ�����Ч��
                                                                0����λȡ��
                                                                1����λ��Ч
                                                                ע��������PLL���������и�λ������ᵼ��PLLʧ���� */
        unsigned int  ppll0_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator������Ч��
                                                                0����������
                                                                1��bypass�� */
        unsigned int  ppll0_ssc_downspread : 1;  /* bit[2]    : ѡ��center spread��down spread
                                                                0��Center Spread
                                                                1��Down Spread�� */
        unsigned int  ppll0_ssc_spread     : 3;  /* bit[3-5]  : ���õ������(spread%)
                                                                3'b000 = 0
                                                                3'b001 = 0.049%
                                                                3'b010 = 0.098%
                                                                3'b011 = 0.195%
                                                                3'b100 = 0.391%
                                                                3'b101 = 0.781%
                                                                3'b110 = 1.563%
                                                                3'b111 = 3.125%�� */
        unsigned int  ppll0_ssc_divval     : 4;  /* bit[6-9]  : ����Ƶ�׵��Ƶ�Ƶ�ʣ�һ��ԼΪ32KHz��
                                                                freq=(CLKSSCG / (DIVVAL * #points))������pointsΪ128����REFDIV=1ʱ��CLKSSCG=FREF�� */
        unsigned int  reserved             : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_SCTRL_SCPPLLSSCCTRL_UNION;
#endif
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_reset_START       (0)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_reset_END         (0)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_disable_START     (1)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_disable_END       (1)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_downspread_START  (2)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_downspread_END    (2)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_spread_START      (3)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_spread_END        (5)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_divval_START      (6)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_divval_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPPLLSTAT_UNION
 �ṹ˵��  : SCPPLLSTAT �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PPLL0״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pllstat       : 1;  /* bit[0]   : PPLL0״ָ̬ʾ��
                                                        0��δ�ȶ���
                                                        1�����ȶ��� */
        unsigned int  ppll0_en_stat : 1;  /* bit[1]   : PPLL0����ʹ��״ָ̬ʾ����ppll0_en��IOMCU_pll_ctrl�򣩡�
                                                        0��ȥʹ�ܣ�
                                                        1��ʹ�ܡ� */
        unsigned int  reserved      : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_SCTRL_SCPPLLSTAT_UNION;
#endif
#define SOC_SCTRL_SCPPLLSTAT_pllstat_START        (0)
#define SOC_SCTRL_SCPPLLSTAT_pllstat_END          (0)
#define SOC_SCTRL_SCPPLLSTAT_ppll0_en_stat_START  (1)
#define SOC_SCTRL_SCPPLLSTAT_ppll0_en_stat_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPEREN0_UNION
 �ṹ˵��  : SCPEREN0 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ref_crc    : 1;  /* bit[0]  : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_rtc       : 1;  /* bit[1]  : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_rtc1      : 1;  /* bit[2]  : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_timer0    : 1;  /* bit[3]  : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_timer0     : 1;  /* bit[4]  : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  reserved          : 2;  /* bit[5-6]: ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_timer2    : 1;  /* bit[7]  : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_timer2     : 1;  /* bit[8]  : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_timer3    : 1;  /* bit[9]  : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_timer3     : 1;  /* bit[10] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_ao_gpio0  : 1;  /* bit[11] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_ao_gpio1  : 1;  /* bit[12] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_ao_gpio2  : 1;  /* bit[13] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_ao_gpio3  : 1;  /* bit[14] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_ao_ioc    : 1;  /* bit[15] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_out0       : 1;  /* bit[16] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_out1       : 1;  /* bit[17] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_jtag_auth  : 1;  /* bit[18] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_syscnt    : 1;  /* bit[19] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_syscnt     : 1;  /* bit[20] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_ao_gpio4  : 1;  /* bit[21] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_ao_gpio5  : 1;  /* bit[22] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_sci0       : 1;  /* bit[23] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_sci1       : 1;  /* bit[24] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_memrep     : 1;  /* bit[25] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_asp_subsys : 1;  /* bit[26] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_asp_tcxo   : 1;  /* bit[27] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_bbpdrx     : 1;  /* bit[28] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_aobus      : 1;  /* bit[29] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_efusec    : 1;  /* bit[30] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_ppll0_sscg : 1;  /* bit[31] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
    } reg;
} SOC_SCTRL_SCPEREN0_UNION;
#endif
#define SOC_SCTRL_SCPEREN0_gt_clk_ref_crc_START     (0)
#define SOC_SCTRL_SCPEREN0_gt_clk_ref_crc_END       (0)
#define SOC_SCTRL_SCPEREN0_gt_pclk_rtc_START        (1)
#define SOC_SCTRL_SCPEREN0_gt_pclk_rtc_END          (1)
#define SOC_SCTRL_SCPEREN0_gt_pclk_rtc1_START       (2)
#define SOC_SCTRL_SCPEREN0_gt_pclk_rtc1_END         (2)
#define SOC_SCTRL_SCPEREN0_gt_pclk_timer0_START     (3)
#define SOC_SCTRL_SCPEREN0_gt_pclk_timer0_END       (3)
#define SOC_SCTRL_SCPEREN0_gt_clk_timer0_START      (4)
#define SOC_SCTRL_SCPEREN0_gt_clk_timer0_END        (4)
#define SOC_SCTRL_SCPEREN0_gt_pclk_timer2_START     (7)
#define SOC_SCTRL_SCPEREN0_gt_pclk_timer2_END       (7)
#define SOC_SCTRL_SCPEREN0_gt_clk_timer2_START      (8)
#define SOC_SCTRL_SCPEREN0_gt_clk_timer2_END        (8)
#define SOC_SCTRL_SCPEREN0_gt_pclk_timer3_START     (9)
#define SOC_SCTRL_SCPEREN0_gt_pclk_timer3_END       (9)
#define SOC_SCTRL_SCPEREN0_gt_clk_timer3_START      (10)
#define SOC_SCTRL_SCPEREN0_gt_clk_timer3_END        (10)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio0_START   (11)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio0_END     (11)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio1_START   (12)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio1_END     (12)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio2_START   (13)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio2_END     (13)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio3_START   (14)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio3_END     (14)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_ioc_START     (15)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_ioc_END       (15)
#define SOC_SCTRL_SCPEREN0_gt_clk_out0_START        (16)
#define SOC_SCTRL_SCPEREN0_gt_clk_out0_END          (16)
#define SOC_SCTRL_SCPEREN0_gt_clk_out1_START        (17)
#define SOC_SCTRL_SCPEREN0_gt_clk_out1_END          (17)
#define SOC_SCTRL_SCPEREN0_gt_clk_jtag_auth_START   (18)
#define SOC_SCTRL_SCPEREN0_gt_clk_jtag_auth_END     (18)
#define SOC_SCTRL_SCPEREN0_gt_pclk_syscnt_START     (19)
#define SOC_SCTRL_SCPEREN0_gt_pclk_syscnt_END       (19)
#define SOC_SCTRL_SCPEREN0_gt_clk_syscnt_START      (20)
#define SOC_SCTRL_SCPEREN0_gt_clk_syscnt_END        (20)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio4_START   (21)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio4_END     (21)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio5_START   (22)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio5_END     (22)
#define SOC_SCTRL_SCPEREN0_gt_clk_sci0_START        (23)
#define SOC_SCTRL_SCPEREN0_gt_clk_sci0_END          (23)
#define SOC_SCTRL_SCPEREN0_gt_clk_sci1_START        (24)
#define SOC_SCTRL_SCPEREN0_gt_clk_sci1_END          (24)
#define SOC_SCTRL_SCPEREN0_gt_clk_memrep_START      (25)
#define SOC_SCTRL_SCPEREN0_gt_clk_memrep_END        (25)
#define SOC_SCTRL_SCPEREN0_gt_clk_asp_subsys_START  (26)
#define SOC_SCTRL_SCPEREN0_gt_clk_asp_subsys_END    (26)
#define SOC_SCTRL_SCPEREN0_gt_clk_asp_tcxo_START    (27)
#define SOC_SCTRL_SCPEREN0_gt_clk_asp_tcxo_END      (27)
#define SOC_SCTRL_SCPEREN0_gt_clk_bbpdrx_START      (28)
#define SOC_SCTRL_SCPEREN0_gt_clk_bbpdrx_END        (28)
#define SOC_SCTRL_SCPEREN0_gt_clk_aobus_START       (29)
#define SOC_SCTRL_SCPEREN0_gt_clk_aobus_END         (29)
#define SOC_SCTRL_SCPEREN0_gt_pclk_efusec_START     (30)
#define SOC_SCTRL_SCPEREN0_gt_pclk_efusec_END       (30)
#define SOC_SCTRL_SCPEREN0_gt_clk_ppll0_sscg_START  (31)
#define SOC_SCTRL_SCPEREN0_gt_clk_ppll0_sscg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERDIS0_UNION
 �ṹ˵��  : SCPERDIS0 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ref_crc    : 1;  /* bit[0]  : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_rtc       : 1;  /* bit[1]  : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_rtc1      : 1;  /* bit[2]  : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_timer0    : 1;  /* bit[3]  : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_timer0     : 1;  /* bit[4]  : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  reserved          : 2;  /* bit[5-6]: ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_timer2    : 1;  /* bit[7]  : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_timer2     : 1;  /* bit[8]  : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_timer3    : 1;  /* bit[9]  : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_timer3     : 1;  /* bit[10] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_ao_gpio0  : 1;  /* bit[11] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_ao_gpio1  : 1;  /* bit[12] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_ao_gpio2  : 1;  /* bit[13] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_ao_gpio3  : 1;  /* bit[14] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_ao_ioc    : 1;  /* bit[15] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_out0       : 1;  /* bit[16] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_out1       : 1;  /* bit[17] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_jtag_auth  : 1;  /* bit[18] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_syscnt    : 1;  /* bit[19] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_syscnt     : 1;  /* bit[20] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_ao_gpio4  : 1;  /* bit[21] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_ao_gpio5  : 1;  /* bit[22] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_sci0       : 1;  /* bit[23] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_sci1       : 1;  /* bit[24] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_memrep     : 1;  /* bit[25] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_asp_subsys : 1;  /* bit[26] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_asp_tcxo   : 1;  /* bit[27] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_bbpdrx     : 1;  /* bit[28] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_aobus      : 1;  /* bit[29] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_efusec    : 1;  /* bit[30] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_ppll0_sscg : 1;  /* bit[31] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
    } reg;
} SOC_SCTRL_SCPERDIS0_UNION;
#endif
#define SOC_SCTRL_SCPERDIS0_gt_clk_ref_crc_START     (0)
#define SOC_SCTRL_SCPERDIS0_gt_clk_ref_crc_END       (0)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_rtc_START        (1)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_rtc_END          (1)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_rtc1_START       (2)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_rtc1_END         (2)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_timer0_START     (3)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_timer0_END       (3)
#define SOC_SCTRL_SCPERDIS0_gt_clk_timer0_START      (4)
#define SOC_SCTRL_SCPERDIS0_gt_clk_timer0_END        (4)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_timer2_START     (7)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_timer2_END       (7)
#define SOC_SCTRL_SCPERDIS0_gt_clk_timer2_START      (8)
#define SOC_SCTRL_SCPERDIS0_gt_clk_timer2_END        (8)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_timer3_START     (9)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_timer3_END       (9)
#define SOC_SCTRL_SCPERDIS0_gt_clk_timer3_START      (10)
#define SOC_SCTRL_SCPERDIS0_gt_clk_timer3_END        (10)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio0_START   (11)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio0_END     (11)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio1_START   (12)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio1_END     (12)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio2_START   (13)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio2_END     (13)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio3_START   (14)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio3_END     (14)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_ioc_START     (15)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_ioc_END       (15)
#define SOC_SCTRL_SCPERDIS0_gt_clk_out0_START        (16)
#define SOC_SCTRL_SCPERDIS0_gt_clk_out0_END          (16)
#define SOC_SCTRL_SCPERDIS0_gt_clk_out1_START        (17)
#define SOC_SCTRL_SCPERDIS0_gt_clk_out1_END          (17)
#define SOC_SCTRL_SCPERDIS0_gt_clk_jtag_auth_START   (18)
#define SOC_SCTRL_SCPERDIS0_gt_clk_jtag_auth_END     (18)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_syscnt_START     (19)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_syscnt_END       (19)
#define SOC_SCTRL_SCPERDIS0_gt_clk_syscnt_START      (20)
#define SOC_SCTRL_SCPERDIS0_gt_clk_syscnt_END        (20)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio4_START   (21)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio4_END     (21)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio5_START   (22)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio5_END     (22)
#define SOC_SCTRL_SCPERDIS0_gt_clk_sci0_START        (23)
#define SOC_SCTRL_SCPERDIS0_gt_clk_sci0_END          (23)
#define SOC_SCTRL_SCPERDIS0_gt_clk_sci1_START        (24)
#define SOC_SCTRL_SCPERDIS0_gt_clk_sci1_END          (24)
#define SOC_SCTRL_SCPERDIS0_gt_clk_memrep_START      (25)
#define SOC_SCTRL_SCPERDIS0_gt_clk_memrep_END        (25)
#define SOC_SCTRL_SCPERDIS0_gt_clk_asp_subsys_START  (26)
#define SOC_SCTRL_SCPERDIS0_gt_clk_asp_subsys_END    (26)
#define SOC_SCTRL_SCPERDIS0_gt_clk_asp_tcxo_START    (27)
#define SOC_SCTRL_SCPERDIS0_gt_clk_asp_tcxo_END      (27)
#define SOC_SCTRL_SCPERDIS0_gt_clk_bbpdrx_START      (28)
#define SOC_SCTRL_SCPERDIS0_gt_clk_bbpdrx_END        (28)
#define SOC_SCTRL_SCPERDIS0_gt_clk_aobus_START       (29)
#define SOC_SCTRL_SCPERDIS0_gt_clk_aobus_END         (29)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_efusec_START     (30)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_efusec_END       (30)
#define SOC_SCTRL_SCPERDIS0_gt_clk_ppll0_sscg_START  (31)
#define SOC_SCTRL_SCPERDIS0_gt_clk_ppll0_sscg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERCLKEN0_UNION
 �ṹ˵��  : SCPERCLKEN0 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0xF3FFFFFF�����:32
 �Ĵ���˵��: ����ʱ��ʹ��״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ref_crc    : 1;  /* bit[0]  : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_rtc       : 1;  /* bit[1]  : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_rtc1      : 1;  /* bit[2]  : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer0    : 1;  /* bit[3]  : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer0     : 1;  /* bit[4]  : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  reserved          : 2;  /* bit[5-6]: ��SCPERCLKEN0_SEC[1:0]timer1�� */
        unsigned int  gt_pclk_timer2    : 1;  /* bit[7]  : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer2     : 1;  /* bit[8]  : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer3    : 1;  /* bit[9]  : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer3     : 1;  /* bit[10] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_gpio0  : 1;  /* bit[11] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_gpio1  : 1;  /* bit[12] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_gpio2  : 1;  /* bit[13] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_gpio3  : 1;  /* bit[14] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_ioc    : 1;  /* bit[15] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_out0       : 1;  /* bit[16] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_out1       : 1;  /* bit[17] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_jtag_auth  : 1;  /* bit[18] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_syscnt    : 1;  /* bit[19] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_syscnt     : 1;  /* bit[20] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_gpio4  : 1;  /* bit[21] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_gpio5  : 1;  /* bit[22] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_sci0       : 1;  /* bit[23] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_sci1       : 1;  /* bit[24] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_memrep     : 1;  /* bit[25] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_asp_subsys : 1;  /* bit[26] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_asp_tcxo   : 1;  /* bit[27] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_bbpdrx     : 1;  /* bit[28] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_aobus      : 1;  /* bit[29] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_efusec    : 1;  /* bit[30] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_ppll0_sscg : 1;  /* bit[31] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_SCTRL_SCPERCLKEN0_UNION;
#endif
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_ref_crc_START     (0)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_ref_crc_END       (0)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_rtc_START        (1)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_rtc_END          (1)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_rtc1_START       (2)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_rtc1_END         (2)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_timer0_START     (3)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_timer0_END       (3)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_timer0_START      (4)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_timer0_END        (4)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_timer2_START     (7)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_timer2_END       (7)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_timer2_START      (8)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_timer2_END        (8)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_timer3_START     (9)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_timer3_END       (9)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_timer3_START      (10)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_timer3_END        (10)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio0_START   (11)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio0_END     (11)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio1_START   (12)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio1_END     (12)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio2_START   (13)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio2_END     (13)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio3_START   (14)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio3_END     (14)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_ioc_START     (15)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_ioc_END       (15)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_out0_START        (16)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_out0_END          (16)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_out1_START        (17)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_out1_END          (17)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_jtag_auth_START   (18)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_jtag_auth_END     (18)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_syscnt_START     (19)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_syscnt_END       (19)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_syscnt_START      (20)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_syscnt_END        (20)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio4_START   (21)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio4_END     (21)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio5_START   (22)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio5_END     (22)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_sci0_START        (23)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_sci0_END          (23)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_sci1_START        (24)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_sci1_END          (24)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_memrep_START      (25)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_memrep_END        (25)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_asp_subsys_START  (26)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_asp_subsys_END    (26)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_asp_tcxo_START    (27)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_asp_tcxo_END      (27)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_bbpdrx_START      (28)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_bbpdrx_END        (28)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_aobus_START       (29)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_aobus_END         (29)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_efusec_START     (30)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_efusec_END       (30)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_ppll0_sscg_START  (31)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_ppll0_sscg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTAT0_UNION
 �ṹ˵��  : SCPERSTAT0 �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0xF3FFFFFF�����:32
 �Ĵ���˵��: ����ʱ������״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ref_crc    : 1;  /* bit[0] : ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_rtc       : 1;  /* bit[1] : ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_rtc1      : 1;  /* bit[2] : ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer0    : 1;  /* bit[3] : ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer0     : 1;  /* bit[4] : ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer1    : 1;  /* bit[5] : ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer1     : 1;  /* bit[6] : ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer2    : 1;  /* bit[7] : ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer2     : 1;  /* bit[8] : ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer3    : 1;  /* bit[9] : ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer3     : 1;  /* bit[10]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_gpio0  : 1;  /* bit[11]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_gpio1  : 1;  /* bit[12]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_gpio2  : 1;  /* bit[13]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_gpio3  : 1;  /* bit[14]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_ioc    : 1;  /* bit[15]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_out0       : 1;  /* bit[16]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_out1       : 1;  /* bit[17]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_jtag_auth  : 1;  /* bit[18]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_syscnt    : 1;  /* bit[19]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_syscnt     : 1;  /* bit[20]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_gpio4  : 1;  /* bit[21]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_ao_gpio5  : 1;  /* bit[22]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_sci0       : 1;  /* bit[23]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_sci1       : 1;  /* bit[24]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_memrep     : 1;  /* bit[25]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_asp_subsys : 1;  /* bit[26]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_asp_tcxo   : 1;  /* bit[27]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_bbpdrx     : 1;  /* bit[28]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_aobus      : 1;  /* bit[29]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_efusec    : 1;  /* bit[30]: ����ʱ������״̬��
                                                          0��IPʱ�ӽ�ֹ״̬��
                                                          1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_ppll0_sscg : 1;  /* bit[31]: �����Ĵ����ĸ�λֵ��SCTRL�������ź�peri_clk_stat0[31:0]�ĸ�λֵ������ */
    } reg;
} SOC_SCTRL_SCPERSTAT0_UNION;
#endif
#define SOC_SCTRL_SCPERSTAT0_gt_clk_ref_crc_START     (0)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_ref_crc_END       (0)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_rtc_START        (1)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_rtc_END          (1)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_rtc1_START       (2)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_rtc1_END         (2)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer0_START     (3)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer0_END       (3)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer0_START      (4)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer0_END        (4)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer1_START     (5)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer1_END       (5)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer1_START      (6)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer1_END        (6)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer2_START     (7)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer2_END       (7)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer2_START      (8)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer2_END        (8)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer3_START     (9)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer3_END       (9)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer3_START      (10)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer3_END        (10)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio0_START   (11)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio0_END     (11)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio1_START   (12)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio1_END     (12)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio2_START   (13)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio2_END     (13)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio3_START   (14)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio3_END     (14)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_ioc_START     (15)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_ioc_END       (15)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_out0_START        (16)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_out0_END          (16)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_out1_START        (17)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_out1_END          (17)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_jtag_auth_START   (18)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_jtag_auth_END     (18)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_syscnt_START     (19)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_syscnt_END       (19)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_syscnt_START      (20)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_syscnt_END        (20)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio4_START   (21)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio4_END     (21)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio5_START   (22)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio5_END     (22)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_sci0_START        (23)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_sci0_END          (23)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_sci1_START        (24)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_sci1_END          (24)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_memrep_START      (25)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_memrep_END        (25)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_asp_subsys_START  (26)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_asp_subsys_END    (26)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_asp_tcxo_START    (27)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_asp_tcxo_END      (27)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_bbpdrx_START      (28)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_bbpdrx_END        (28)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_aobus_START       (29)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_aobus_END         (29)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_efusec_START     (30)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_efusec_END       (30)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_ppll0_sscg_START  (31)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_ppll0_sscg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPEREN1_UNION
 �ṹ˵��  : SCPEREN1 �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_asp_dw_axi                : 1;  /* bit[0]    : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_asp_x2h                   : 1;  /* bit[1]    : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_asp_h2p                   : 1;  /* bit[2]    : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_asp_cfg                       : 1;  /* bit[3]    : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_bbpdrx_oth                : 1;  /* bit[4]    : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_aobus_noc                 : 1;  /* bit[5]    : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_noc_aobus2mmbuf           : 1;  /* bit[6]    : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  ddr_loopback_en                  : 1;  /* bit[7]    : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_aclk_asc                      : 1;  /* bit[8]    : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  reserved_0                       : 1;  /* bit[9]    : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_timer4                   : 1;  /* bit[10]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_timer4                    : 1;  /* bit[11]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_timer5                   : 1;  /* bit[12]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_timer5                    : 1;  /* bit[13]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_timer6                   : 1;  /* bit[14]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_timer6                    : 1;  /* bit[15]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_timer7                   : 1;  /* bit[16]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_timer7                    : 1;  /* bit[17]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_timer8                   : 1;  /* bit[18]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_timer8                    : 1;  /* bit[19]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_timerclk_refh                 : 1;  /* bit[20]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  reserved_1                       : 1;  /* bit[21]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_aclk_mmbuf                    : 1;  /* bit[22]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_mmbuf                    : 1;  /* bit[23]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_mmbuf_dss                 : 1;  /* bit[24]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_mmbufcfg                 : 1;  /* bit[25]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_autodiv_aobus_noc         : 1;  /* bit[26]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  reserved_2                       : 3;  /* bit[27-29]: ����ʱ��ʹ�ܿ��ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1ʹ��IPʱ�ӡ� */
        unsigned int  aobus2mmbuf_auto_gate_bypass     : 1;  /* bit[30]   : aobus2mmbuf_auto_gate_bypass
                                                                            0��д0��Ч��
                                                                            1��д1 auto gate bypass�� */
        unsigned int  wait_ddr_selfreflash_done_bypass : 1;  /* bit[31]   : [31]:wait_ddr_selfreflash_done_bypass
                                                                            0��д0��Ч��
                                                                            1��д1 done bypass�� */
    } reg;
} SOC_SCTRL_SCPEREN1_UNION;
#endif
#define SOC_SCTRL_SCPEREN1_gt_clk_asp_dw_axi_START                 (0)
#define SOC_SCTRL_SCPEREN1_gt_clk_asp_dw_axi_END                   (0)
#define SOC_SCTRL_SCPEREN1_gt_clk_asp_x2h_START                    (1)
#define SOC_SCTRL_SCPEREN1_gt_clk_asp_x2h_END                      (1)
#define SOC_SCTRL_SCPEREN1_gt_clk_asp_h2p_START                    (2)
#define SOC_SCTRL_SCPEREN1_gt_clk_asp_h2p_END                      (2)
#define SOC_SCTRL_SCPEREN1_gt_asp_cfg_START                        (3)
#define SOC_SCTRL_SCPEREN1_gt_asp_cfg_END                          (3)
#define SOC_SCTRL_SCPEREN1_gt_clk_bbpdrx_oth_START                 (4)
#define SOC_SCTRL_SCPEREN1_gt_clk_bbpdrx_oth_END                   (4)
#define SOC_SCTRL_SCPEREN1_gt_clk_aobus_noc_START                  (5)
#define SOC_SCTRL_SCPEREN1_gt_clk_aobus_noc_END                    (5)
#define SOC_SCTRL_SCPEREN1_gt_clk_noc_aobus2mmbuf_START            (6)
#define SOC_SCTRL_SCPEREN1_gt_clk_noc_aobus2mmbuf_END              (6)
#define SOC_SCTRL_SCPEREN1_ddr_loopback_en_START                   (7)
#define SOC_SCTRL_SCPEREN1_ddr_loopback_en_END                     (7)
#define SOC_SCTRL_SCPEREN1_gt_aclk_asc_START                       (8)
#define SOC_SCTRL_SCPEREN1_gt_aclk_asc_END                         (8)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer4_START                    (10)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer4_END                      (10)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer4_START                     (11)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer4_END                       (11)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer5_START                    (12)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer5_END                      (12)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer5_START                     (13)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer5_END                       (13)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer6_START                    (14)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer6_END                      (14)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer6_START                     (15)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer6_END                       (15)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer7_START                    (16)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer7_END                      (16)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer7_START                     (17)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer7_END                       (17)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer8_START                    (18)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer8_END                      (18)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer8_START                     (19)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer8_END                       (19)
#define SOC_SCTRL_SCPEREN1_gt_timerclk_refh_START                  (20)
#define SOC_SCTRL_SCPEREN1_gt_timerclk_refh_END                    (20)
#define SOC_SCTRL_SCPEREN1_gt_aclk_mmbuf_START                     (22)
#define SOC_SCTRL_SCPEREN1_gt_aclk_mmbuf_END                       (22)
#define SOC_SCTRL_SCPEREN1_gt_pclk_mmbuf_START                     (23)
#define SOC_SCTRL_SCPEREN1_gt_pclk_mmbuf_END                       (23)
#define SOC_SCTRL_SCPEREN1_gt_clk_mmbuf_dss_START                  (24)
#define SOC_SCTRL_SCPEREN1_gt_clk_mmbuf_dss_END                    (24)
#define SOC_SCTRL_SCPEREN1_gt_pclk_mmbufcfg_START                  (25)
#define SOC_SCTRL_SCPEREN1_gt_pclk_mmbufcfg_END                    (25)
#define SOC_SCTRL_SCPEREN1_gt_clk_autodiv_aobus_noc_START          (26)
#define SOC_SCTRL_SCPEREN1_gt_clk_autodiv_aobus_noc_END            (26)
#define SOC_SCTRL_SCPEREN1_aobus2mmbuf_auto_gate_bypass_START      (30)
#define SOC_SCTRL_SCPEREN1_aobus2mmbuf_auto_gate_bypass_END        (30)
#define SOC_SCTRL_SCPEREN1_wait_ddr_selfreflash_done_bypass_START  (31)
#define SOC_SCTRL_SCPEREN1_wait_ddr_selfreflash_done_bypass_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERDIS1_UNION
 �ṹ˵��  : SCPERDIS1 �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_asp_dw_axi                : 1;  /* bit[0]    : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_clk_asp_x2h                   : 1;  /* bit[1]    : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_clk_asp_h2p                   : 1;  /* bit[2]    : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_asp_cfg                       : 1;  /* bit[3]    : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_clk_bbpdrx_oth                : 1;  /* bit[4]    : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_clk_aobus_noc                 : 1;  /* bit[5]    : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_clk_noc_aobus2mmbuf           : 1;  /* bit[6]    : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  ddr_loopback_en                  : 1;  /* bit[7]    : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_aclk_asc                      : 1;  /* bit[8]    : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  reserved_0                       : 1;  /* bit[9]    : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_timer4                   : 1;  /* bit[10]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_clk_timer4                    : 1;  /* bit[11]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_timer5                   : 1;  /* bit[12]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_clk_timer5                    : 1;  /* bit[13]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_timer6                   : 1;  /* bit[14]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_clk_timer6                    : 1;  /* bit[15]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_timer7                   : 1;  /* bit[16]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_clk_timer7                    : 1;  /* bit[17]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_timer8                   : 1;  /* bit[18]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_clk_timer8                    : 1;  /* bit[19]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_timerclk_refh                 : 1;  /* bit[20]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  reserved_1                       : 1;  /* bit[21]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_aclk_mmbuf                    : 1;  /* bit[22]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_mmbuf                    : 1;  /* bit[23]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_clk_mmbuf_dss                 : 1;  /* bit[24]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_mmbufcfg                 : 1;  /* bit[25]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  gt_clk_autodiv_aobus_noc         : 1;  /* bit[26]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  reserved_2                       : 3;  /* bit[27-29]: ����ʱ�ӽ�ֹ���ƣ�
                                                                            0��д0��Ч��
                                                                            1��д1��ֹIPʱ�ӡ� */
        unsigned int  aobus2mmbuf_auto_gate_bypass     : 1;  /* bit[30]   : aobus2mmbuf_auto_gate_bypass
                                                                            0��д0��Ч��
                                                                            1��д1 auto gate not bypass�� */
        unsigned int  wait_ddr_selfreflash_done_bypass : 1;  /* bit[31]   : [31]:wait_ddr_selfreflash_done_bypass
                                                                            0��д0��Ч��
                                                                            1��д1 done not bypass�� */
    } reg;
} SOC_SCTRL_SCPERDIS1_UNION;
#endif
#define SOC_SCTRL_SCPERDIS1_gt_clk_asp_dw_axi_START                 (0)
#define SOC_SCTRL_SCPERDIS1_gt_clk_asp_dw_axi_END                   (0)
#define SOC_SCTRL_SCPERDIS1_gt_clk_asp_x2h_START                    (1)
#define SOC_SCTRL_SCPERDIS1_gt_clk_asp_x2h_END                      (1)
#define SOC_SCTRL_SCPERDIS1_gt_clk_asp_h2p_START                    (2)
#define SOC_SCTRL_SCPERDIS1_gt_clk_asp_h2p_END                      (2)
#define SOC_SCTRL_SCPERDIS1_gt_asp_cfg_START                        (3)
#define SOC_SCTRL_SCPERDIS1_gt_asp_cfg_END                          (3)
#define SOC_SCTRL_SCPERDIS1_gt_clk_bbpdrx_oth_START                 (4)
#define SOC_SCTRL_SCPERDIS1_gt_clk_bbpdrx_oth_END                   (4)
#define SOC_SCTRL_SCPERDIS1_gt_clk_aobus_noc_START                  (5)
#define SOC_SCTRL_SCPERDIS1_gt_clk_aobus_noc_END                    (5)
#define SOC_SCTRL_SCPERDIS1_gt_clk_noc_aobus2mmbuf_START            (6)
#define SOC_SCTRL_SCPERDIS1_gt_clk_noc_aobus2mmbuf_END              (6)
#define SOC_SCTRL_SCPERDIS1_ddr_loopback_en_START                   (7)
#define SOC_SCTRL_SCPERDIS1_ddr_loopback_en_END                     (7)
#define SOC_SCTRL_SCPERDIS1_gt_aclk_asc_START                       (8)
#define SOC_SCTRL_SCPERDIS1_gt_aclk_asc_END                         (8)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer4_START                    (10)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer4_END                      (10)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer4_START                     (11)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer4_END                       (11)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer5_START                    (12)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer5_END                      (12)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer5_START                     (13)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer5_END                       (13)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer6_START                    (14)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer6_END                      (14)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer6_START                     (15)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer6_END                       (15)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer7_START                    (16)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer7_END                      (16)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer7_START                     (17)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer7_END                       (17)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer8_START                    (18)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer8_END                      (18)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer8_START                     (19)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer8_END                       (19)
#define SOC_SCTRL_SCPERDIS1_gt_timerclk_refh_START                  (20)
#define SOC_SCTRL_SCPERDIS1_gt_timerclk_refh_END                    (20)
#define SOC_SCTRL_SCPERDIS1_gt_aclk_mmbuf_START                     (22)
#define SOC_SCTRL_SCPERDIS1_gt_aclk_mmbuf_END                       (22)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_mmbuf_START                     (23)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_mmbuf_END                       (23)
#define SOC_SCTRL_SCPERDIS1_gt_clk_mmbuf_dss_START                  (24)
#define SOC_SCTRL_SCPERDIS1_gt_clk_mmbuf_dss_END                    (24)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_mmbufcfg_START                  (25)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_mmbufcfg_END                    (25)
#define SOC_SCTRL_SCPERDIS1_gt_clk_autodiv_aobus_noc_START          (26)
#define SOC_SCTRL_SCPERDIS1_gt_clk_autodiv_aobus_noc_END            (26)
#define SOC_SCTRL_SCPERDIS1_aobus2mmbuf_auto_gate_bypass_START      (30)
#define SOC_SCTRL_SCPERDIS1_aobus2mmbuf_auto_gate_bypass_END        (30)
#define SOC_SCTRL_SCPERDIS1_wait_ddr_selfreflash_done_bypass_START  (31)
#define SOC_SCTRL_SCPERDIS1_wait_ddr_selfreflash_done_bypass_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERCLKEN1_UNION
 �ṹ˵��  : SCPERCLKEN1 �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0xBC1FFC70�����:32
 �Ĵ���˵��: ����ʱ��ʹ��״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_asp_dw_axi                : 1;  /* bit[0]    : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_asp_x2h                   : 1;  /* bit[1]    : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_asp_h2p                   : 1;  /* bit[2]    : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_asp_cfg                       : 1;  /* bit[3]    : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_bbpdrx_oth                : 1;  /* bit[4]    : modem��ϵͳ�͸�bbpdrx��ʱ��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_aobus_noc                 : 1;  /* bit[5]    : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_noc_aobus2mmbuf           : 1;  /* bit[6]    : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  ddr_loopback_en                  : 1;  /* bit[7]    : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_aclk_asc                      : 1;  /* bit[8]    : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  reserved_0                       : 1;  /* bit[9]    : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer4                   : 1;  /* bit[10]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer4                    : 1;  /* bit[11]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer5                   : 1;  /* bit[12]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer5                    : 1;  /* bit[13]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer6                   : 1;  /* bit[14]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer6                    : 1;  /* bit[15]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer7                   : 1;  /* bit[16]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer7                    : 1;  /* bit[17]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer8                   : 1;  /* bit[18]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer8                    : 1;  /* bit[19]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_timerclk_refh                 : 1;  /* bit[20]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  reserved_1                       : 1;  /* bit[21]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_aclk_mmbuf                    : 1;  /* bit[22]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_mmbuf                    : 1;  /* bit[23]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_mmbuf_dss                 : 1;  /* bit[24]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_mmbufcfg                 : 1;  /* bit[25]   : 0��ʱ�ӹرգ�
                                                                            1��ʱ�ӿ�����
                                                                            ��������ֵ��iomcu��audio�ʹ�����λͶƱȷ����������򿪾�ʱ�ӣ��������󶼹رղŹر�ʱ�ӡ� */
        unsigned int  gt_clk_autodiv_aobus_noc         : 1;  /* bit[26]   : ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  reserved_2                       : 3;  /* bit[27-29]: [29:28]:reserved
                                                                            [27]:����˿�peri_clk_en1[27]��gt_clk_ao_cc����
                                                                            ����ʱ��ʹ��״̬��
                                                                            0��IPʱ�ӽ�ֹ״̬��
                                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  aobus2mmbuf_auto_gate_bypass     : 1;  /* bit[30]   : aobus2mmbuf_auto_gate_bypass
                                                                            0:no bypass
                                                                            1:bypass�� */
        unsigned int  wait_ddr_selfreflash_done_bypass : 1;  /* bit[31]   : [31]:wait_ddr_selfreflash_done_bypass
                                                                            0:no bypass
                                                                            1:bypass�� */
    } reg;
} SOC_SCTRL_SCPERCLKEN1_UNION;
#endif
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_asp_dw_axi_START                 (0)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_asp_dw_axi_END                   (0)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_asp_x2h_START                    (1)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_asp_x2h_END                      (1)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_asp_h2p_START                    (2)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_asp_h2p_END                      (2)
#define SOC_SCTRL_SCPERCLKEN1_gt_asp_cfg_START                        (3)
#define SOC_SCTRL_SCPERCLKEN1_gt_asp_cfg_END                          (3)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_bbpdrx_oth_START                 (4)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_bbpdrx_oth_END                   (4)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_aobus_noc_START                  (5)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_aobus_noc_END                    (5)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_noc_aobus2mmbuf_START            (6)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_noc_aobus2mmbuf_END              (6)
#define SOC_SCTRL_SCPERCLKEN1_ddr_loopback_en_START                   (7)
#define SOC_SCTRL_SCPERCLKEN1_ddr_loopback_en_END                     (7)
#define SOC_SCTRL_SCPERCLKEN1_gt_aclk_asc_START                       (8)
#define SOC_SCTRL_SCPERCLKEN1_gt_aclk_asc_END                         (8)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer4_START                    (10)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer4_END                      (10)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer4_START                     (11)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer4_END                       (11)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer5_START                    (12)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer5_END                      (12)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer5_START                     (13)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer5_END                       (13)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer6_START                    (14)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer6_END                      (14)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer6_START                     (15)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer6_END                       (15)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer7_START                    (16)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer7_END                      (16)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer7_START                     (17)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer7_END                       (17)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer8_START                    (18)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer8_END                      (18)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer8_START                     (19)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer8_END                       (19)
#define SOC_SCTRL_SCPERCLKEN1_gt_timerclk_refh_START                  (20)
#define SOC_SCTRL_SCPERCLKEN1_gt_timerclk_refh_END                    (20)
#define SOC_SCTRL_SCPERCLKEN1_gt_aclk_mmbuf_START                     (22)
#define SOC_SCTRL_SCPERCLKEN1_gt_aclk_mmbuf_END                       (22)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_mmbuf_START                     (23)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_mmbuf_END                       (23)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_mmbuf_dss_START                  (24)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_mmbuf_dss_END                    (24)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_mmbufcfg_START                  (25)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_mmbufcfg_END                    (25)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_autodiv_aobus_noc_START          (26)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_autodiv_aobus_noc_END            (26)
#define SOC_SCTRL_SCPERCLKEN1_aobus2mmbuf_auto_gate_bypass_START      (30)
#define SOC_SCTRL_SCPERCLKEN1_aobus2mmbuf_auto_gate_bypass_END        (30)
#define SOC_SCTRL_SCPERCLKEN1_wait_ddr_selfreflash_done_bypass_START  (31)
#define SOC_SCTRL_SCPERCLKEN1_wait_ddr_selfreflash_done_bypass_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTAT1_UNION
 �ṹ˵��  : SCPERSTAT1 �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x44FFFC70�����:32
 �Ĵ���˵��: ����ʱ������״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_asp_dw_axi           : 1;  /* bit[0] : ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_asp_x2h              : 1;  /* bit[1] : ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_asp_h2p              : 1;  /* bit[2] : ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_asp_cfg                  : 1;  /* bit[3] : ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_104m_bbpdrx          : 1;  /* bit[4] : modem��ϵͳ�͸�bbpdrx��ʱ��
                                                                    ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  st_clk_noc_aobus2sysbusddrc : 1;  /* bit[5] : ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  st_clk_noc_aobus2mmbuf      : 1;  /* bit[6] : ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  reserved_0                  : 1;  /* bit[7] : ������ */
        unsigned int  st_aclk_asc                 : 1;  /* bit[8] : ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  reserved_1                  : 1;  /* bit[9] : ������ */
        unsigned int  gt_pclk_timer4              : 1;  /* bit[10]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer4               : 1;  /* bit[11]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer5              : 1;  /* bit[12]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer5               : 1;  /* bit[13]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer6              : 1;  /* bit[14]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer6               : 1;  /* bit[15]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer7              : 1;  /* bit[16]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer7               : 1;  /* bit[17]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_timer8              : 1;  /* bit[18]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer8               : 1;  /* bit[19]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_timerclk_refh            : 1;  /* bit[20]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_monitor              : 1;  /* bit[21]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  st_aclk_mmbuf               : 1;  /* bit[22]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  st_pclk_mmbuf               : 1;  /* bit[23]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  st_aclk_mmbuf_dss           : 1;  /* bit[24]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_mmbufcfg            : 1;  /* bit[25]: 0��ʱ�ӹرգ�
                                                                    1��ʱ�ӿ�����
                                                                    ��������ֵ��iomcu��audio��SCPERCLKEN1[25]����λͶƱȷ����������򿪾�ʱ�ӣ��������󶼹رղŹر�ʱ�ӡ� */
        unsigned int  reserved_2                  : 1;  /* bit[26]: ������ */
        unsigned int  swdone_clk_asp_subsys_div   : 1;  /* bit[27]: clk_asp_subsysDIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                    0��δ��ɣ�
                                                                    1����ɡ� */
        unsigned int  swdone_clk_sci_div          : 1;  /* bit[28]: clk_sci DIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                    0��δ��ɣ�
                                                                    1����ɡ� */
        unsigned int  swdone_clk_aobus_div        : 1;  /* bit[29]: clk_aobus DIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                    0��δ��ɣ�
                                                                    1����ɡ� */
        unsigned int  aobusclksw2sys              : 1;  /* bit[30]: aobus clk�л�������ʱ��ָʾ������Ч�� */
        unsigned int  aobusclksw2pll              : 1;  /* bit[31]: aobus clk�л���PLLʱ��ָʾ������Ч�� */
    } reg;
} SOC_SCTRL_SCPERSTAT1_UNION;
#endif
#define SOC_SCTRL_SCPERSTAT1_gt_clk_asp_dw_axi_START            (0)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_asp_dw_axi_END              (0)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_asp_x2h_START               (1)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_asp_x2h_END                 (1)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_asp_h2p_START               (2)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_asp_h2p_END                 (2)
#define SOC_SCTRL_SCPERSTAT1_gt_asp_cfg_START                   (3)
#define SOC_SCTRL_SCPERSTAT1_gt_asp_cfg_END                     (3)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_104m_bbpdrx_START           (4)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_104m_bbpdrx_END             (4)
#define SOC_SCTRL_SCPERSTAT1_st_clk_noc_aobus2sysbusddrc_START  (5)
#define SOC_SCTRL_SCPERSTAT1_st_clk_noc_aobus2sysbusddrc_END    (5)
#define SOC_SCTRL_SCPERSTAT1_st_clk_noc_aobus2mmbuf_START       (6)
#define SOC_SCTRL_SCPERSTAT1_st_clk_noc_aobus2mmbuf_END         (6)
#define SOC_SCTRL_SCPERSTAT1_st_aclk_asc_START                  (8)
#define SOC_SCTRL_SCPERSTAT1_st_aclk_asc_END                    (8)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer4_START               (10)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer4_END                 (10)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer4_START                (11)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer4_END                  (11)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer5_START               (12)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer5_END                 (12)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer5_START                (13)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer5_END                  (13)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer6_START               (14)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer6_END                 (14)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer6_START                (15)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer6_END                  (15)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer7_START               (16)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer7_END                 (16)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer7_START                (17)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer7_END                  (17)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer8_START               (18)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer8_END                 (18)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer8_START                (19)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer8_END                  (19)
#define SOC_SCTRL_SCPERSTAT1_gt_timerclk_refh_START             (20)
#define SOC_SCTRL_SCPERSTAT1_gt_timerclk_refh_END               (20)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_monitor_START               (21)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_monitor_END                 (21)
#define SOC_SCTRL_SCPERSTAT1_st_aclk_mmbuf_START                (22)
#define SOC_SCTRL_SCPERSTAT1_st_aclk_mmbuf_END                  (22)
#define SOC_SCTRL_SCPERSTAT1_st_pclk_mmbuf_START                (23)
#define SOC_SCTRL_SCPERSTAT1_st_pclk_mmbuf_END                  (23)
#define SOC_SCTRL_SCPERSTAT1_st_aclk_mmbuf_dss_START            (24)
#define SOC_SCTRL_SCPERSTAT1_st_aclk_mmbuf_dss_END              (24)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_mmbufcfg_START             (25)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_mmbufcfg_END               (25)
#define SOC_SCTRL_SCPERSTAT1_swdone_clk_asp_subsys_div_START    (27)
#define SOC_SCTRL_SCPERSTAT1_swdone_clk_asp_subsys_div_END      (27)
#define SOC_SCTRL_SCPERSTAT1_swdone_clk_sci_div_START           (28)
#define SOC_SCTRL_SCPERSTAT1_swdone_clk_sci_div_END             (28)
#define SOC_SCTRL_SCPERSTAT1_swdone_clk_aobus_div_START         (29)
#define SOC_SCTRL_SCPERSTAT1_swdone_clk_aobus_div_END           (29)
#define SOC_SCTRL_SCPERSTAT1_aobusclksw2sys_START               (30)
#define SOC_SCTRL_SCPERSTAT1_aobusclksw2sys_END                 (30)
#define SOC_SCTRL_SCPERSTAT1_aobusclksw2pll_START               (31)
#define SOC_SCTRL_SCPERSTAT1_aobusclksw2pll_END                 (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPEREN2_UNION
 �ṹ˵��  : SCPEREN2 �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_SCTRL_SCPEREN2_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERDIS2_UNION
 �ṹ˵��  : SCPERDIS2 �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERDIS2_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERCLKEN2_UNION
 �ṹ˵��  : SCPERCLKEN2 �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: ����ʱ��ʹ��״̬�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERCLKEN2_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTAT2_UNION
 �ṹ˵��  : SCPERSTAT2 �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: ����ʱ������״̬�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scperstat2 : 32; /* bit[0-31]: [14]:reset_dram_n
                                                     �͸�Ƭ��DRAM�ĸ�λ��0��ʾrst��
                                                     [13]:memrep_sw2tcxo
                                                     memrep��ʱ���л�״ָ̬ʾ�� 1��memrep��ʱ���л���tcxo�� 0��memrep�� ʱ��δ40Mʱ�ӣ�
                                                     [12]:swdone_clk_memrep_div
                                                     memrep ʱ�ӷ�Ƶ���ָʾ�źţ� 1 ��ɣ�0 δ��ɣ�
                                                     [11]:asp_subsys_sw2pll
                                                     asp Դʱ���л�Դ�л�ָʾ 1���л���PLL�� 0�� �л���FLL��
                                                     [10]:mmbuf_sw2pll
                                                     [9]:mmbuf_sw2fll
                                                     [8]:mmbuf_sw2tcxo
                                                     mmbuf ʱ��Դ�л�ָʾ�� �ֱ�Ϊ1��ʱ���ʾ�л�����Ӧʱ��Դ��
                                                     [7]:aobusnoc_sw2pll
                                                     [6]:aobusnoc_sw2ddr
                                                     [5]:aobusnoc_sw2fll
                                                     [4]:aobusnoc_sw2tcxo
                                                     ʱ��Դ�л�ָʾ�� �ֱ�Ϊ1��ʱ���ʾ�л�����Ӧʱ��Դ��
                                                     [3]:swdone_clk_iomcu_pll_div
                                                     [2]:swdone_clk_aobus_noc_div
                                                     [1]:swdone_pclk_mmbuf_div
                                                     [0]:swdone_aclk_mmbuf_div
                                                     ������Ƶdiv ��Ƶ����л�ָʾ��1 ��ʾ��Ƶ��ɣ�0 ��ʾ��Ƶ������
                                                     ������������ */
    } reg;
} SOC_SCTRL_SCPERSTAT2_UNION;
#endif
#define SOC_SCTRL_SCPERSTAT2_scperstat2_START  (0)
#define SOC_SCTRL_SCPERSTAT2_scperstat2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCTIMERCTRL_UNION
 �ṹ˵��  : SCTIMERCTRL �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00000000�����:32
 �Ĵ���˵��: ϵͳTIMERʱ��ѡ��Ϳ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeren8ov   : 1;  /* bit[0]    : Timer8ʱ��ʹ�ܿ��ơ�
                                                        0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren0sel]ָ����
                                                        1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren8sel  : 1;  /* bit[1]    : Time8ʱ��ʹ�ܲο�ʱ��ѡ��
                                                        0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                        1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren9ov   : 1;  /* bit[2]    : Timer9ʱ��ʹ�ܿ��ơ�
                                                        0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren1sel]ָ����
                                                        1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren9sel  : 1;  /* bit[3]    : Time9ʱ��ʹ�ܲο�ʱ��ѡ��
                                                        0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                        1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren10ov  : 1;  /* bit[4]    : Timer10ʱ��ʹ�ܿ��ơ�
                                                        0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren2sel]ָ����
                                                        1��ʹ���źű�ǿ�����ߡ�
                                                        ע����TIMER�а�ȫ�������󣬿�ͨ�����ð�ȫ����timer_secu_enλ��ǿ��ѡ��32KHZʱ�ӡ� */
        unsigned int  timeren10sel : 1;  /* bit[5]    : Time10ʱ��ʹ�ܲο�ʱ��ѡ��
                                                        0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                        1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren11ov  : 1;  /* bit[6]    : Timer11ʱ��ʹ�ܿ��ơ�
                                                        0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren3sel]ָ����
                                                        1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren11sel : 1;  /* bit[7]    : Time11ʱ��ʹ�ܲο�ʱ��ѡ��
                                                        0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                        1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren12ov  : 1;  /* bit[8]    : Timer12ʱ��ʹ�ܿ��ơ�
                                                        0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren4sel]ָ����
                                                        1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren12sel : 1;  /* bit[9]    : Time12ʱ��ʹ�ܲο�ʱ��ѡ��
                                                        0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                        1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren13ov  : 1;  /* bit[10]   : Timer13ʱ��ʹ�ܿ��ơ�
                                                        0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren5sel]ָ����
                                                        1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren13sel : 1;  /* bit[11]   : Time13ʱ��ʹ�ܲο�ʱ��ѡ��
                                                        0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                        1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren14ov  : 1;  /* bit[12]   : Timer14ʱ��ʹ�ܿ��ơ�
                                                        0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren6sel]ָ����
                                                        1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren14sel : 1;  /* bit[13]   : Time14ʱ��ʹ�ܲο�ʱ��ѡ��
                                                        0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                        1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren15ov  : 1;  /* bit[14]   : Timer15ʱ��ʹ�ܿ��ơ�
                                                        0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren7sel]ָ����
                                                        1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren15sel : 1;  /* bit[15]   : Time15ʱ��ʹ�ܲο�ʱ��ѡ��
                                                        0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                        1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren16ov  : 1;  /* bit[16]   : Timer16ʱ��ʹ�ܿ��ơ�
                                                        0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren6sel]ָ����
                                                        1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren16sel : 1;  /* bit[17]   : Time16ʱ��ʹ�ܲο�ʱ��ѡ��
                                                        0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                        1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren17ov  : 1;  /* bit[18]   : Timer17ʱ��ʹ�ܿ��ơ�
                                                        0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren7sel]ָ����
                                                        1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren17sel : 1;  /* bit[19]   : Time17ʱ��ʹ�ܲο�ʱ��ѡ��
                                                        0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                        1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  reserved     : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_SCTRL_SCTIMERCTRL_UNION;
#endif
#define SOC_SCTRL_SCTIMERCTRL_timeren8ov_START    (0)
#define SOC_SCTRL_SCTIMERCTRL_timeren8ov_END      (0)
#define SOC_SCTRL_SCTIMERCTRL_timeren8sel_START   (1)
#define SOC_SCTRL_SCTIMERCTRL_timeren8sel_END     (1)
#define SOC_SCTRL_SCTIMERCTRL_timeren9ov_START    (2)
#define SOC_SCTRL_SCTIMERCTRL_timeren9ov_END      (2)
#define SOC_SCTRL_SCTIMERCTRL_timeren9sel_START   (3)
#define SOC_SCTRL_SCTIMERCTRL_timeren9sel_END     (3)
#define SOC_SCTRL_SCTIMERCTRL_timeren10ov_START   (4)
#define SOC_SCTRL_SCTIMERCTRL_timeren10ov_END     (4)
#define SOC_SCTRL_SCTIMERCTRL_timeren10sel_START  (5)
#define SOC_SCTRL_SCTIMERCTRL_timeren10sel_END    (5)
#define SOC_SCTRL_SCTIMERCTRL_timeren11ov_START   (6)
#define SOC_SCTRL_SCTIMERCTRL_timeren11ov_END     (6)
#define SOC_SCTRL_SCTIMERCTRL_timeren11sel_START  (7)
#define SOC_SCTRL_SCTIMERCTRL_timeren11sel_END    (7)
#define SOC_SCTRL_SCTIMERCTRL_timeren12ov_START   (8)
#define SOC_SCTRL_SCTIMERCTRL_timeren12ov_END     (8)
#define SOC_SCTRL_SCTIMERCTRL_timeren12sel_START  (9)
#define SOC_SCTRL_SCTIMERCTRL_timeren12sel_END    (9)
#define SOC_SCTRL_SCTIMERCTRL_timeren13ov_START   (10)
#define SOC_SCTRL_SCTIMERCTRL_timeren13ov_END     (10)
#define SOC_SCTRL_SCTIMERCTRL_timeren13sel_START  (11)
#define SOC_SCTRL_SCTIMERCTRL_timeren13sel_END    (11)
#define SOC_SCTRL_SCTIMERCTRL_timeren14ov_START   (12)
#define SOC_SCTRL_SCTIMERCTRL_timeren14ov_END     (12)
#define SOC_SCTRL_SCTIMERCTRL_timeren14sel_START  (13)
#define SOC_SCTRL_SCTIMERCTRL_timeren14sel_END    (13)
#define SOC_SCTRL_SCTIMERCTRL_timeren15ov_START   (14)
#define SOC_SCTRL_SCTIMERCTRL_timeren15ov_END     (14)
#define SOC_SCTRL_SCTIMERCTRL_timeren15sel_START  (15)
#define SOC_SCTRL_SCTIMERCTRL_timeren15sel_END    (15)
#define SOC_SCTRL_SCTIMERCTRL_timeren16ov_START   (16)
#define SOC_SCTRL_SCTIMERCTRL_timeren16ov_END     (16)
#define SOC_SCTRL_SCTIMERCTRL_timeren16sel_START  (17)
#define SOC_SCTRL_SCTIMERCTRL_timeren16sel_END    (17)
#define SOC_SCTRL_SCTIMERCTRL_timeren17ov_START   (18)
#define SOC_SCTRL_SCTIMERCTRL_timeren17ov_END     (18)
#define SOC_SCTRL_SCTIMERCTRL_timeren17sel_START  (19)
#define SOC_SCTRL_SCTIMERCTRL_timeren17sel_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCFPLLCTRL0_UNION
 �ṹ˵��  : SCFPLLCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x00904B06�����:32
 �Ĵ���˵��: FPLL0���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpll0_en    : 1;  /* bit[0]   : [0]:fpll0_en ��bit��asp_fpll_en_req��iomcu_fpll_en_reqͶƱȷ������һ��bitΪ1��fpll������bit��Ϊ0�ر�fpll��
                                                      1:PLL����������0:powerdown
                                                      1.��ʼ���ü�⵽EN�ź������غ�30��cycle��Lock�ź����ߡ� */
        unsigned int  fpll_bypass : 1;  /* bit[1]   : [1]:pll_bypass 
                                                      1:bypass FOUT =FREF ,����������ȼ�����EN=x��POSTDIV=XX �������bypass
                                                      0:����������FOUT=FREF*FCW/POSTDIV�� */
        unsigned int  scfpllctrl0 : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_SCTRL_SCFPLLCTRL0_UNION;
#endif
#define SOC_SCTRL_SCFPLLCTRL0_fpll0_en_START     (0)
#define SOC_SCTRL_SCFPLLCTRL0_fpll0_en_END       (0)
#define SOC_SCTRL_SCFPLLCTRL0_fpll_bypass_START  (1)
#define SOC_SCTRL_SCFPLLCTRL0_fpll_bypass_END    (1)
#define SOC_SCTRL_SCFPLLCTRL0_scfpllctrl0_START  (2)
#define SOC_SCTRL_SCFPLLCTRL0_scfpllctrl0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCFPLLCTRL1_UNION
 �ṹ˵��  : SCFPLLCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00904B06�����:32
 �Ĵ���˵��: FPLL0���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpll_fcw     : 13; /* bit[0-12] : BIT[12:0] =FCW ʵ��1~8191 ��Ƶ��Ҫ���Ӧ��ʮ��������Ϊ��Ƶ���� */
        unsigned int  fpll_postdiv : 2;  /* bit[13-14]: BIT[14:13]=POSTDIV ��option���ܣ�������ȥ��������ʵ��·�Ƿ���Ҫ�����ݲ�Ʒ����������
                                                        00:FOUT�͵�ƽ 01:1��Ƶ 01:2��Ƶ 11��4��Ƶ�� */
        unsigned int  scfpllctrl1  : 17; /* bit[15-31]: ������ */
    } reg;
} SOC_SCTRL_SCFPLLCTRL1_UNION;
#endif
#define SOC_SCTRL_SCFPLLCTRL1_fpll_fcw_START      (0)
#define SOC_SCTRL_SCFPLLCTRL1_fpll_fcw_END        (12)
#define SOC_SCTRL_SCFPLLCTRL1_fpll_postdiv_START  (13)
#define SOC_SCTRL_SCFPLLCTRL1_fpll_postdiv_END    (14)
#define SOC_SCTRL_SCFPLLCTRL1_scfpllctrl1_START   (15)
#define SOC_SCTRL_SCFPLLCTRL1_scfpllctrl1_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCFPLLCTRL2_UNION
 �ṹ˵��  : SCFPLLCTRL2 �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00904B06�����:32
 �Ĵ���˵��: FPLL0���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scfpllctrl2 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_SCTRL_SCFPLLCTRL2_UNION;
#endif
#define SOC_SCTRL_SCFPLLCTRL2_scfpllctrl2_START  (0)
#define SOC_SCTRL_SCFPLLCTRL2_scfpllctrl2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCFPLLCTRL3_UNION
 �ṹ˵��  : SCFPLLCTRL3 �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00904B06�����:32
 �Ĵ���˵��: FPLL0���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scfpllctrl3 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_SCTRL_SCFPLLCTRL3_UNION;
#endif
#define SOC_SCTRL_SCFPLLCTRL3_scfpllctrl3_START  (0)
#define SOC_SCTRL_SCFPLLCTRL3_scfpllctrl3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCFPLLSTAT_UNION
 �ṹ˵��  : SCFPLLSTAT �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00000000�����:32
 �Ĵ���˵��: FPLL0״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scfpllstat : 32; /* bit[0-31]: [0]:LOCK 1:Ƶ������ 0:Ƶ��δ����
                                                     ���ౣ���� */
    } reg;
} SOC_SCTRL_SCFPLLSTAT_UNION;
#endif
#define SOC_SCTRL_SCFPLLSTAT_scfpllstat_START  (0)
#define SOC_SCTRL_SCFPLLSTAT_scfpllstat_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTAT3_UNION
 �ṹ˵��  : SCPERSTAT3 �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: ����ʱ������״̬�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERSTAT3_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTEN0_UNION
 �ṹ˵��  : SCPERRSTEN0 �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0      : 1;  /* bit[0]    : IP��λʹ�ܣ�
                                                           0��IP��λʹ��״̬���䣻
                                                           1��IP��λʹ�ܡ� */
        unsigned int  ip_rst_rtc      : 1;  /* bit[1]    : ����ͬbit0�� */
        unsigned int  ip_rst_rtc1     : 1;  /* bit[2]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer0   : 1;  /* bit[3]    : ����ͬbit0�� */
        unsigned int  reserved_1      : 1;  /* bit[4]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer2   : 1;  /* bit[5]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer3   : 1;  /* bit[6]    : ����ͬbit0�� */
        unsigned int  rst_asp_cfg     : 1;  /* bit[7]    : ����ͬbit0�� */
        unsigned int  rst_asp_dw_axi  : 1;  /* bit[8]    : ����ͬbit0�� */
        unsigned int  rst_asp_x2h     : 1;  /* bit[9]    : ����ͬbit0�� */
        unsigned int  rst_asp_h2p     : 1;  /* bit[10]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio0 : 1;  /* bit[11]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio1 : 1;  /* bit[12]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio2 : 1;  /* bit[13]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio3 : 1;  /* bit[14]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio4 : 1;  /* bit[15]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio5 : 1;  /* bit[16]   : ����ͬbit0�� */
        unsigned int  reserved_2      : 1;  /* bit[17]   : ������ */
        unsigned int  ip_rst_ao_ioc   : 1;  /* bit[18]   : ����ͬbit0 */
        unsigned int  ip_prst_syscnt  : 1;  /* bit[19]   : ����ͬbit0 */
        unsigned int  ip_rst_syscnt   : 1;  /* bit[20]   : ����ͬbit0 */
        unsigned int  reserved_3      : 2;  /* bit[21-22]: ������ */
        unsigned int  ip_rst_sci0     : 1;  /* bit[23]   : ����ͬbit0�� */
        unsigned int  ip_rst_sci1     : 1;  /* bit[24]   : ����ͬbit0�� */
        unsigned int  reserved_4      : 1;  /* bit[25]   : ������ */
        unsigned int  reserved_5      : 1;  /* bit[26]   : ����ͬbit0�� */
        unsigned int  ip_rst_bbpdrx   : 1;  /* bit[27]   : ����ͬbit0�� */
        unsigned int  reserved_6      : 1;  /* bit[28]   : ������ */
        unsigned int  ip_rst_aobus    : 1;  /* bit[29]   : ����ͬbit0�� */
        unsigned int  sc_rst_src_clr  : 1;  /* bit[30]   : ��λԴ��Ϣ������ƣ�
                                                           0��д0��Ч����
                                                           1����λԴ��Ϣ��������رո�λԴ��¼���ܡ� */
        unsigned int  sc_pmurst_ctrl  : 1;  /* bit[31]   : PMU��λ������ƣ�
                                                           0��д0��Ч����
                                                           1���ر�PMU��λ���ܲ��ҿ���AP��λ���ܡ� */
    } reg;
} SOC_SCTRL_SCPERRSTEN0_UNION;
#endif
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_rtc_START       (1)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_rtc_END         (1)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_rtc1_START      (2)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_rtc1_END        (2)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_timer0_START    (3)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_timer0_END      (3)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_timer2_START    (5)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_timer2_END      (5)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_timer3_START    (6)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_timer3_END      (6)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_cfg_START      (7)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_cfg_END        (7)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_dw_axi_START   (8)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_dw_axi_END     (8)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_x2h_START      (9)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_x2h_END        (9)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_h2p_START      (10)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_h2p_END        (10)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio0_START  (11)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio0_END    (11)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio1_START  (12)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio1_END    (12)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio2_START  (13)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio2_END    (13)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio3_START  (14)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio3_END    (14)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio4_START  (15)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio4_END    (15)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio5_START  (16)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio5_END    (16)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_ioc_START    (18)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_ioc_END      (18)
#define SOC_SCTRL_SCPERRSTEN0_ip_prst_syscnt_START   (19)
#define SOC_SCTRL_SCPERRSTEN0_ip_prst_syscnt_END     (19)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_syscnt_START    (20)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_syscnt_END      (20)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_sci0_START      (23)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_sci0_END        (23)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_sci1_START      (24)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_sci1_END        (24)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_bbpdrx_START    (27)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_bbpdrx_END      (27)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_aobus_START     (29)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_aobus_END       (29)
#define SOC_SCTRL_SCPERRSTEN0_sc_rst_src_clr_START   (30)
#define SOC_SCTRL_SCPERRSTEN0_sc_rst_src_clr_END     (30)
#define SOC_SCTRL_SCPERRSTEN0_sc_pmurst_ctrl_START   (31)
#define SOC_SCTRL_SCPERRSTEN0_sc_pmurst_ctrl_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTDIS0_UNION
 �ṹ˵��  : SCPERRSTDIS0 �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0      : 1;  /* bit[0]    : IP��λ���룺
                                                           0��IP��λʹ��״̬���䣻
                                                           1��IP��λ���롣 */
        unsigned int  ip_rst_rtc      : 1;  /* bit[1]    : ����ͬbit0�� */
        unsigned int  ip_rst_rtc1     : 1;  /* bit[2]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer0   : 1;  /* bit[3]    : ����ͬbit0�� */
        unsigned int  reserved_1      : 1;  /* bit[4]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer2   : 1;  /* bit[5]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer3   : 1;  /* bit[6]    : ����ͬbit0�� */
        unsigned int  rst_asp_cfg     : 1;  /* bit[7]    : ����ͬbit0�� */
        unsigned int  rst_asp_dw_axi  : 1;  /* bit[8]    : ����ͬbit0�� */
        unsigned int  rst_asp_x2h     : 1;  /* bit[9]    : ����ͬbit0�� */
        unsigned int  rst_asp_h2p     : 1;  /* bit[10]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio0 : 1;  /* bit[11]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio1 : 1;  /* bit[12]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio2 : 1;  /* bit[13]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio3 : 1;  /* bit[14]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio4 : 1;  /* bit[15]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio5 : 1;  /* bit[16]   : ����ͬbit0�� */
        unsigned int  reserved_2      : 1;  /* bit[17]   : ������ */
        unsigned int  ip_rst_ao_ioc   : 1;  /* bit[18]   : ����ͬbit0�� */
        unsigned int  ip_prst_syscnt  : 1;  /* bit[19]   : ����ͬbit0�� */
        unsigned int  ip_rst_syscnt   : 1;  /* bit[20]   : ����ͬbit0�� */
        unsigned int  reserved_3      : 2;  /* bit[21-22]: ������ */
        unsigned int  ip_rst_sci0     : 1;  /* bit[23]   : ����ͬbit0�� */
        unsigned int  ip_rst_sci1     : 1;  /* bit[24]   : ����ͬbit0�� */
        unsigned int  reserved_4      : 1;  /* bit[25]   : ������ */
        unsigned int  reserved_5      : 1;  /* bit[26]   : ����ͬbit0�� */
        unsigned int  ip_rst_bbpdrx   : 1;  /* bit[27]   : ����ͬbit0�� */
        unsigned int  reserved_6      : 1;  /* bit[28]   : ������ */
        unsigned int  ip_rst_aobus    : 1;  /* bit[29]   : ����ͬbit0�� */
        unsigned int  sc_rst_src_clr  : 1;  /* bit[30]   : ��λԴ����źſ��ƣ�
                                                           0��д0��Ч����
                                                           1����λԴ�������������λԴ��¼�������á� */
        unsigned int  sc_pmurst_ctrl  : 1;  /* bit[31]   : PMU��λ���ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1������PMU��λ���ܲ��ҹر�AP��λ���ܡ� */
    } reg;
} SOC_SCTRL_SCPERRSTDIS0_UNION;
#endif
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_rtc_START       (1)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_rtc_END         (1)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_rtc1_START      (2)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_rtc1_END        (2)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_timer0_START    (3)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_timer0_END      (3)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_timer2_START    (5)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_timer2_END      (5)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_timer3_START    (6)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_timer3_END      (6)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_cfg_START      (7)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_cfg_END        (7)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_dw_axi_START   (8)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_dw_axi_END     (8)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_x2h_START      (9)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_x2h_END        (9)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_h2p_START      (10)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_h2p_END        (10)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio0_START  (11)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio0_END    (11)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio1_START  (12)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio1_END    (12)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio2_START  (13)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio2_END    (13)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio3_START  (14)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio3_END    (14)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio4_START  (15)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio4_END    (15)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio5_START  (16)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio5_END    (16)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_ioc_START    (18)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_ioc_END      (18)
#define SOC_SCTRL_SCPERRSTDIS0_ip_prst_syscnt_START   (19)
#define SOC_SCTRL_SCPERRSTDIS0_ip_prst_syscnt_END     (19)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_syscnt_START    (20)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_syscnt_END      (20)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_sci0_START      (23)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_sci0_END        (23)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_sci1_START      (24)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_sci1_END        (24)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_bbpdrx_START    (27)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_bbpdrx_END      (27)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_aobus_START     (29)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_aobus_END       (29)
#define SOC_SCTRL_SCPERRSTDIS0_sc_rst_src_clr_START   (30)
#define SOC_SCTRL_SCPERRSTDIS0_sc_rst_src_clr_END     (30)
#define SOC_SCTRL_SCPERRSTDIS0_sc_pmurst_ctrl_START   (31)
#define SOC_SCTRL_SCPERRSTDIS0_sc_pmurst_ctrl_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTSTAT0_UNION
 �ṹ˵��  : SCPERRSTSTAT0 �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x04000780�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0      : 1;  /* bit[0]    : ������λʹ��״̬��
                                                           0��IP��λʹ�ܳ�����
                                                           1��IP��λʹ�ܣ�
                                                           ��peri_rst_ctrl[0]�ɰ�ȫ��SCPERRSTSTAT0_SEC.ip_rst_ao_cc��������� */
        unsigned int  ip_rst_rtc      : 1;  /* bit[1]    : ����ͬbit0�� */
        unsigned int  ip_rst_rtc1     : 1;  /* bit[2]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer0   : 1;  /* bit[3]    : ����ͬbit0�� */
        unsigned int  reserved_1      : 1;  /* bit[4]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer2   : 1;  /* bit[5]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer3   : 1;  /* bit[6]    : ����ͬbit0�� */
        unsigned int  rst_asp_cfg     : 1;  /* bit[7]    : ����ͬbit0�� */
        unsigned int  rst_asp_dw_axi  : 1;  /* bit[8]    : ����ͬbit0�� */
        unsigned int  rst_asp_x2h     : 1;  /* bit[9]    : ����ͬbit0�� */
        unsigned int  rst_asp_h2p     : 1;  /* bit[10]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio0 : 1;  /* bit[11]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio1 : 1;  /* bit[12]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio2 : 1;  /* bit[13]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio3 : 1;  /* bit[14]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio4 : 1;  /* bit[15]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_gpio5 : 1;  /* bit[16]   : ����ͬbit0�� */
        unsigned int  reserved_2      : 1;  /* bit[17]   : ������ */
        unsigned int  ip_rst_ao_ioc   : 1;  /* bit[18]   : ����ͬbit0�� */
        unsigned int  ip_prst_syscnt  : 1;  /* bit[19]   : ����ͬbit0�� */
        unsigned int  ip_rst_syscnt   : 1;  /* bit[20]   : ����ͬbit0�� */
        unsigned int  reserved_3      : 2;  /* bit[21-22]: ������ */
        unsigned int  ip_rst_sci0     : 1;  /* bit[23]   : ����ͬbit0�� */
        unsigned int  ip_rst_sci1     : 1;  /* bit[24]   : ����ͬbit0�� */
        unsigned int  reserved_4      : 1;  /* bit[25]   : ������ */
        unsigned int  reserved_5      : 1;  /* bit[26]   : ����ͬbit0�� */
        unsigned int  ip_rst_bbpdrx   : 1;  /* bit[27]   : ����ͬbit0�� */
        unsigned int  reserved_6      : 1;  /* bit[28]   : ������ */
        unsigned int  ip_rst_aobus    : 1;  /* bit[29]   : ����ͬbit0�� */
        unsigned int  sc_rst_src_clr  : 1;  /* bit[30]   : ��λԴ�������״̬��
                                                           0��������λԴ��¼���ܣ�
                                                           1�������λԴ��¼���ܣ�
                                                           ��bit����Ϊ1����Ҫ������Ϊ0�� */
        unsigned int  sc_pmurst_ctrl  : 1;  /* bit[31]   : PMU��λ���ܿ���״̬��
                                                           0������PMU��λ���ܲ��ҽ���AP��λ���ܣ�
                                                           1������PMU��λ���ܲ��ҿ���AP��λ���ܡ� */
    } reg;
} SOC_SCTRL_SCPERRSTSTAT0_UNION;
#endif
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_rtc_START       (1)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_rtc_END         (1)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_rtc1_START      (2)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_rtc1_END        (2)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_timer0_START    (3)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_timer0_END      (3)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_timer2_START    (5)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_timer2_END      (5)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_timer3_START    (6)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_timer3_END      (6)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_cfg_START      (7)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_cfg_END        (7)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_dw_axi_START   (8)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_dw_axi_END     (8)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_x2h_START      (9)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_x2h_END        (9)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_h2p_START      (10)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_h2p_END        (10)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio0_START  (11)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio0_END    (11)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio1_START  (12)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio1_END    (12)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio2_START  (13)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio2_END    (13)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio3_START  (14)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio3_END    (14)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio4_START  (15)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio4_END    (15)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio5_START  (16)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio5_END    (16)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_ioc_START    (18)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_ioc_END      (18)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_prst_syscnt_START   (19)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_prst_syscnt_END     (19)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_syscnt_START    (20)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_syscnt_END      (20)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_sci0_START      (23)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_sci0_END        (23)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_sci1_START      (24)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_sci1_END        (24)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_bbpdrx_START    (27)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_bbpdrx_END      (27)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_aobus_START     (29)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_aobus_END       (29)
#define SOC_SCTRL_SCPERRSTSTAT0_sc_rst_src_clr_START   (30)
#define SOC_SCTRL_SCPERRSTSTAT0_sc_rst_src_clr_END     (30)
#define SOC_SCTRL_SCPERRSTSTAT0_sc_pmurst_ctrl_START   (31)
#define SOC_SCTRL_SCPERRSTSTAT0_sc_pmurst_ctrl_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTEN1_UNION
 �ṹ˵��  : SCPERRSTEN1 �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0]    : IP��λʹ�ܣ�
                                                                   0��IP��λʹ��״̬���䣻
                                                                   1��IP��λʹ�ܡ� */
        unsigned int  reserved_1              : 1;  /* bit[1]    : ����ͬbit0�� */
        unsigned int  reserved_2              : 1;  /* bit[2]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer4           : 1;  /* bit[3]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer5           : 1;  /* bit[4]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer6           : 1;  /* bit[5]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer7           : 1;  /* bit[6]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer8           : 1;  /* bit[7]    : ����ͬbit0�� */
        unsigned int  ip_rst_aobus_noc        : 1;  /* bit[8]    : ����ͬbit0�� */
        unsigned int  reserved_3              : 1;  /* bit[9]    : ����ͬbit0�� */
        unsigned int  reserved_4              : 1;  /* bit[10]   : ����ͬbit0�� */
        unsigned int  ip_rst_mmbuf            : 1;  /* bit[11]   : ����ͬbit0�� */
        unsigned int  ip_rst_mmbufcfg         : 1;  /* bit[12]   : ����ͬbit0�� */
        unsigned int  ip_rst_autodiv_aobusnoc : 1;  /* bit[13]   : ����ͬbit0�� */
        unsigned int  reserved_5              : 2;  /* bit[14-15]: ����ͬbit0�� */
        unsigned int  ip_rst_dram_tmp_0       : 2;  /* bit[16-17]: dram��λ����
                                                                   0���޲���
                                                                   1����SCPERRSTSTAT1.ip_rst_dram_tmp_0��Ӧbit��1�� */
        unsigned int  reserved_6              : 14; /* bit[18-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTEN1_UNION;
#endif
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer4_START            (3)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer4_END              (3)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer5_START            (4)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer5_END              (4)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer6_START            (5)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer6_END              (5)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer7_START            (6)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer7_END              (6)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer8_START            (7)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer8_END              (7)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_aobus_noc_START         (8)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_aobus_noc_END           (8)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_mmbuf_START             (11)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_mmbuf_END               (11)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_mmbufcfg_START          (12)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_mmbufcfg_END            (12)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_autodiv_aobusnoc_START  (13)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_autodiv_aobusnoc_END    (13)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_dram_tmp_0_START        (16)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_dram_tmp_0_END          (17)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTDIS1_UNION
 �ṹ˵��  : SCPERRSTDIS1 �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0]    : IP��λ���룺
                                                                   0��IP��λʹ��״̬���䣻
                                                                   1��IP��λ���롣 */
        unsigned int  reserved_1              : 1;  /* bit[1]    : ����ͬbit0�� */
        unsigned int  reserved_2              : 1;  /* bit[2]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer4           : 1;  /* bit[3]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer5           : 1;  /* bit[4]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer6           : 1;  /* bit[5]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer7           : 1;  /* bit[6]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer8           : 1;  /* bit[7]    : ����ͬbit0�� */
        unsigned int  ip_rst_aobus_noc        : 1;  /* bit[8]    : ����ͬbit0�� */
        unsigned int  reserved_3              : 1;  /* bit[9]    : ����ͬbit0�� */
        unsigned int  reserved_4              : 1;  /* bit[10]   : ����ͬbit0�� */
        unsigned int  ip_rst_mmbuf            : 1;  /* bit[11]   : ����ͬbit0�� */
        unsigned int  ip_rst_mmbufcfg         : 1;  /* bit[12]   : ����ͬbit0�� */
        unsigned int  ip_rst_autodiv_aobusnoc : 1;  /* bit[13]   : ����ͬbit0�� */
        unsigned int  reserved_5              : 2;  /* bit[14-15]: ����ͬbit0�� */
        unsigned int  ip_rst_dram_tmp_0       : 2;  /* bit[16-17]: dram��λ����
                                                                   0���޲���
                                                                   1����SCPERRSTSTAT1.ip_rst_dram_tmp_0��Ӧbit��0�� */
        unsigned int  reserved_6              : 14; /* bit[18-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTDIS1_UNION;
#endif
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer4_START            (3)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer4_END              (3)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer5_START            (4)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer5_END              (4)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer6_START            (5)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer6_END              (5)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer7_START            (6)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer7_END              (6)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer8_START            (7)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer8_END              (7)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_aobus_noc_START         (8)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_aobus_noc_END           (8)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_mmbuf_START             (11)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_mmbuf_END               (11)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_mmbufcfg_START          (12)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_mmbufcfg_END            (12)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_autodiv_aobusnoc_START  (13)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_autodiv_aobusnoc_END    (13)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_dram_tmp_0_START        (16)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_dram_tmp_0_END          (17)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTSTAT1_UNION
 �ṹ˵��  : SCPERRSTSTAT1 �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x00001805�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0]    : IP��λ���룺
                                                                   0��IP��λʹ�ܳ�����
                                                                   1��IP��λʹ�ܡ� */
        unsigned int  reserved_1              : 1;  /* bit[1]    : ����ͬbit0�� */
        unsigned int  reserved_2              : 1;  /* bit[2]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer4           : 1;  /* bit[3]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer5           : 1;  /* bit[4]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer6           : 1;  /* bit[5]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer7           : 1;  /* bit[6]    : ����ͬbit0�� */
        unsigned int  ip_rst_timer8           : 1;  /* bit[7]    : ����ͬbit0�� */
        unsigned int  ip_rst_aobus_noc        : 1;  /* bit[8]    : ����ͬbit0�� */
        unsigned int  reserved_3              : 1;  /* bit[9]    : ����ͬbit0�� */
        unsigned int  reserved_4              : 1;  /* bit[10]   : ����ͬbit0�� */
        unsigned int  ip_rst_mmbuf            : 1;  /* bit[11]   : ����ͬbit0�� */
        unsigned int  ip_rst_mmbufcfg         : 1;  /* bit[12]   : ����ͬbit0�� */
        unsigned int  ip_rst_autodiv_aobusnoc : 1;  /* bit[13]   : ����ͬbit0�� */
        unsigned int  reserved_5              : 2;  /* bit[14-15]: ����ͬbit0�� */
        unsigned int  ip_rst_dram_tmp_0       : 2;  /* bit[16-17]: dram��λ״̬0
                                                                   01��dram��λ����0����
                                                                   ������dram����λ
                                                                   ����softrst_dram_dis=1'b1ʱ��SCPERRSTSTAT2.ip_rst_dram_tmp_0=2'b01��SCPERRSTSTAT2.ip_rst_dram_tmp_1=2'b01ͬʱ����ʱ����dram������λ��
                                                                   ��softrst_dram_dis=1'b1ʱ��SCPERRSTSTAT2.ip_rst_dram_tmp_0=2'b01��SCPERRSTSTAT2.ip_rst_dram_tmp_1=2'b01������ʱ����dram��������⸴λ�� */
        unsigned int  reserved_6              : 14; /* bit[18-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTSTAT1_UNION;
#endif
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer4_START            (3)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer4_END              (3)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer5_START            (4)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer5_END              (4)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer6_START            (5)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer6_END              (5)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer7_START            (6)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer7_END              (6)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer8_START            (7)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer8_END              (7)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_aobus_noc_START         (8)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_aobus_noc_END           (8)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_mmbuf_START             (11)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_mmbuf_END               (11)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_mmbufcfg_START          (12)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_mmbufcfg_END            (12)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_autodiv_aobusnoc_START  (13)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_autodiv_aobusnoc_END    (13)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_dram_tmp_0_START        (16)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_dram_tmp_0_END          (17)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTEN2_UNION
 �ṹ˵��  : SCPERRSTEN2 �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0]   : 
                                                            IP��λʹ�ܣ�
                                                            0��IP��λʹ��״̬���䣻
                                                            1��IP��λʹ�ܡ� */
        unsigned int  reserved_1        : 1;  /* bit[1]   : ����ͬbit0�� */
        unsigned int  reserved_2        : 1;  /* bit[2]   : ����ͬbit0�� */
        unsigned int  reserved_3        : 1;  /* bit[3]   : ����ͬbit0�� */
        unsigned int  softrst_dram_dis  : 1;  /* bit[4]   : dram��λ����ʹ��
                                                            0���޲���
                                                            1����SCPERRSTSTAT2.softrst_dram_dis��Ӧbit��1�� */
        unsigned int  ip_rst_dram_tmp_1 : 2;  /* bit[5-6] : dram��λ����
                                                            0���޲���
                                                            1����SCPERRSTSTAT2.ip_rst_dram_tmp_0��Ӧbit��1�� */
        unsigned int  reserved_4        : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTEN2_UNION;
#endif
#define SOC_SCTRL_SCPERRSTEN2_softrst_dram_dis_START   (4)
#define SOC_SCTRL_SCPERRSTEN2_softrst_dram_dis_END     (4)
#define SOC_SCTRL_SCPERRSTEN2_ip_rst_dram_tmp_1_START  (5)
#define SOC_SCTRL_SCPERRSTEN2_ip_rst_dram_tmp_1_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTDIS2_UNION
 �ṹ˵��  : SCPERRSTDIS2 �Ĵ����ṹ���塣��ַƫ����:0x09C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0]   : IP��λʹ�ܣ�
                                                            0��IP��λʹ��״̬���䣻
                                                            1��IP��λʹ�ܡ� */
        unsigned int  reserved_1        : 1;  /* bit[1]   : ����ͬbit0�� */
        unsigned int  reserved_2        : 1;  /* bit[2]   : ����ͬbit0�� */
        unsigned int  reserved_3        : 1;  /* bit[3]   : ����ͬbit0�� */
        unsigned int  softrst_dram_dis  : 1;  /* bit[4]   : dram��λ����ʹ��
                                                            0���޲���
                                                            1����SCPERRSTSTAT2.softrst_dram_dis��Ӧbit��0�� */
        unsigned int  ip_rst_dram_tmp_1 : 2;  /* bit[5-6] : dram��λ����
                                                            0���޲���
                                                            1����SCPERRSTSTAT2.ip_rst_dram_tmp_0��Ӧbit��0�� */
        unsigned int  reserved_4        : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTDIS2_UNION;
#endif
#define SOC_SCTRL_SCPERRSTDIS2_softrst_dram_dis_START   (4)
#define SOC_SCTRL_SCPERRSTDIS2_softrst_dram_dis_END     (4)
#define SOC_SCTRL_SCPERRSTDIS2_ip_rst_dram_tmp_1_START  (5)
#define SOC_SCTRL_SCPERRSTDIS2_ip_rst_dram_tmp_1_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTSTAT2_UNION
 �ṹ˵��  : SCPERRSTSTAT2 �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0]   : �źŶ˿��ɰ�ȫ��SCPERRSTSTAT1_SEC.ip_rst_asp_subsys����
                                                            0��IP��λʹ�ܳ�����
                                                            1��IP��λʹ�ܡ� */
        unsigned int  reserved_1        : 1;  /* bit[1]   : �źŶ˿��ɰ�ȫ��SCPERRSTSTAT2_SEC.ip_rst_iomcu����
                                                            ������λʹ��״̬�� */
        unsigned int  reserved_2        : 1;  /* bit[2]   : �źŶ˿��ɰ�ȫ��SCPERRSTSTAT0_SEC.ip_rst_asc����
                                                            ������λʹ��״̬�� */
        unsigned int  reserved_3        : 1;  /* bit[3]   : ����ͬbit0�� */
        unsigned int  softrst_dram_dis  : 1;  /* bit[4]   : dram��λ����ʹ��
                                                            0��dram��λ����״̬���ֲ���
                                                            1��dram��λ���ܿ��޸ģ�����softrst_dram_dis=1'b1ʱ��SCPERRSTSTAT2.ip_rst_dram_tmp_0=2'b01��SCPERRSTSTAT2.ip_rst_dram_tmp_1=2'b01ͬʱ����ʱ����dram������λ��
                                                            ��softrst_dram_dis=1'b1ʱ��SCPERRSTSTAT2.ip_rst_dram_tmp_0=2'b01��SCPERRSTSTAT2.ip_rst_dram_tmp_1=2'b01������ʱ����dram��������⸴λ�� */
        unsigned int  ip_rst_dram_tmp_1 : 2;  /* bit[5-6] : dram��λ״̬1
                                                            01��dram��λ����1����
                                                            ������dram����λ
                                                            ����softrst_dram_dis=1'b1ʱ��SCPERRSTSTAT2.ip_rst_dram_tmp_0=2'b01��SCPERRSTSTAT2.ip_rst_dram_tmp_1=2'b01ͬʱ����ʱ����dram������λ��
                                                            ��softrst_dram_dis=1'b1ʱ��SCPERRSTSTAT2.ip_rst_dram_tmp_0=2'b01��SCPERRSTSTAT2.ip_rst_dram_tmp_1=2'b01������ʱ����dram��������⸴λ�� */
        unsigned int  reserved_4        : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTSTAT2_UNION;
#endif
#define SOC_SCTRL_SCPERRSTSTAT2_softrst_dram_dis_START   (4)
#define SOC_SCTRL_SCPERRSTSTAT2_softrst_dram_dis_END     (4)
#define SOC_SCTRL_SCPERRSTSTAT2_ip_rst_dram_tmp_1_START  (5)
#define SOC_SCTRL_SCPERRSTSTAT2_ip_rst_dram_tmp_1_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCIPCLKRSTBUS_UNION
 �ṹ˵��  : SCIPCLKRSTBUS �Ĵ����ṹ���塣��ַƫ����:0x0A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: IP�����߹������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_gt_rtc_bypass    : 1;  /* bit[0]    : ���߷���������bypass
                                                                0:ʹ�ܸ�λ&ʱ���ſط����߹�������
                                                                1:BYPASS��λ&ʱ���ſط����߹������ܡ� */
        unsigned int  rst_gt_rtc1_bypass   : 1;  /* bit[1]    : ����ͬbit0�� */
        unsigned int  rst_gt_timer0_bypass : 1;  /* bit[2]    : ����ͬbit0�� */
        unsigned int  rst_gt_timer1_bypass : 1;  /* bit[3]    : ����ͬbit0�� */
        unsigned int  rst_gt_timer2_bypass : 1;  /* bit[4]    : ����ͬbit0�� */
        unsigned int  rst_gt_timer3_bypass : 1;  /* bit[5]    : ����ͬbit0�� */
        unsigned int  rst_gt_gpio0_bypass  : 1;  /* bit[6]    : ����ͬbit0�� */
        unsigned int  rst_gt_gpio1_bypass  : 1;  /* bit[7]    : ����ͬbit0�� */
        unsigned int  rst_gt_gpio2_bypass  : 1;  /* bit[8]    : ����ͬbit0�� */
        unsigned int  rst_gt_gpio3_bypass  : 1;  /* bit[9]    : ����ͬbit0�� */
        unsigned int  rst_gt_gpio4_bypass  : 1;  /* bit[10]   : ����ͬbit0�� */
        unsigned int  rst_gt_gpio5_bypass  : 1;  /* bit[11]   : ����ͬbit0�� */
        unsigned int  rst_gt_ioc_bypass    : 1;  /* bit[12]   : ����ͬbit0�� */
        unsigned int  rst_gt_syscnt_bypass : 1;  /* bit[13]   : ����ͬbit0�� */
        unsigned int  rst_gt_sci0_bypass   : 1;  /* bit[14]   : ����ͬbit0�� */
        unsigned int  rst_gt_sci1_bypass   : 1;  /* bit[15]   : ����ͬbit0�� */
        unsigned int  rst_gt_bbpdrx_bypass : 1;  /* bit[16]   : ����ͬbit0�� */
        unsigned int  rst_gt_efusec_bypass : 1;  /* bit[17]   : ����ͬbit0�� */
        unsigned int  rst_gt_timer4_bypass : 1;  /* bit[18]   : ����ͬbit0�� */
        unsigned int  rst_gt_timer5_bypass : 1;  /* bit[19]   : ����ͬbit0�� */
        unsigned int  rst_gt_timer6_bypass : 1;  /* bit[20]   : ����ͬbit0�� */
        unsigned int  rst_gt_timer7_bypass : 1;  /* bit[21]   : ����ͬbit0�� */
        unsigned int  rst_gt_timer8_bypass : 1;  /* bit[22]   : ����ͬbit0�� */
        unsigned int  rst_gt_mmbuf_bypass  : 1;  /* bit[23]   : ����ͬbit0�� */
        unsigned int  rst_gt_asc_bypass    : 1;  /* bit[24]   : ����ͬbit0�� */
        unsigned int  reserved             : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_SCTRL_SCIPCLKRSTBUS_UNION;
#endif
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_rtc_bypass_START     (0)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_rtc_bypass_END       (0)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_rtc1_bypass_START    (1)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_rtc1_bypass_END      (1)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer0_bypass_START  (2)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer0_bypass_END    (2)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer1_bypass_START  (3)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer1_bypass_END    (3)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer2_bypass_START  (4)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer2_bypass_END    (4)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer3_bypass_START  (5)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer3_bypass_END    (5)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio0_bypass_START   (6)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio0_bypass_END     (6)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio1_bypass_START   (7)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio1_bypass_END     (7)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio2_bypass_START   (8)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio2_bypass_END     (8)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio3_bypass_START   (9)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio3_bypass_END     (9)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio4_bypass_START   (10)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio4_bypass_END     (10)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio5_bypass_START   (11)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio5_bypass_END     (11)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_ioc_bypass_START     (12)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_ioc_bypass_END       (12)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_syscnt_bypass_START  (13)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_syscnt_bypass_END    (13)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_sci0_bypass_START    (14)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_sci0_bypass_END      (14)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_sci1_bypass_START    (15)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_sci1_bypass_END      (15)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_bbpdrx_bypass_START  (16)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_bbpdrx_bypass_END    (16)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_efusec_bypass_START  (17)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_efusec_bypass_END    (17)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer4_bypass_START  (18)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer4_bypass_END    (18)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer5_bypass_START  (19)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer5_bypass_END    (19)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer6_bypass_START  (20)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer6_bypass_END    (20)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer7_bypass_START  (21)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer7_bypass_END    (21)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer8_bypass_START  (22)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer8_bypass_END    (22)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_mmbuf_bypass_START   (23)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_mmbuf_bypass_END     (23)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_asc_bypass_START     (24)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_asc_bypass_END       (24)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCISOEN_UNION
 �ṹ˵��  : SCISOEN �Ĵ����ṹ���塣��ַƫ����:0x0C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ϵͳISOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audioisoen    : 1;  /* bit[0]   : Audio��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ�����д0��Ч�� */
        unsigned int  iomcuisoen    : 1;  /* bit[1]   : IOMCU��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ�����д0��Ч�� */
        unsigned int  debugsubisoen : 1;  /* bit[2]   : Debug��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ�����д0��Ч�� */
        unsigned int  mmbufisoen    : 1;  /* bit[3]   : MMBUF��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ�����д0��Ч�� */
        unsigned int  reserved      : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCISOEN_UNION;
#endif
#define SOC_SCTRL_SCISOEN_audioisoen_START     (0)
#define SOC_SCTRL_SCISOEN_audioisoen_END       (0)
#define SOC_SCTRL_SCISOEN_iomcuisoen_START     (1)
#define SOC_SCTRL_SCISOEN_iomcuisoen_END       (1)
#define SOC_SCTRL_SCISOEN_debugsubisoen_START  (2)
#define SOC_SCTRL_SCISOEN_debugsubisoen_END    (2)
#define SOC_SCTRL_SCISOEN_mmbufisoen_START     (3)
#define SOC_SCTRL_SCISOEN_mmbufisoen_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCISODIS_UNION
 �ṹ˵��  : SCISODIS �Ĵ����ṹ���塣��ַƫ����:0x0C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ϵͳISOʹ�ܳ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audioisoen    : 1;  /* bit[0]   : Audio��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISO����������д0��Ч�� */
        unsigned int  iomcuisoen    : 1;  /* bit[1]   : IOMCU��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISO����������д0��Ч�� */
        unsigned int  debugsubisoen : 1;  /* bit[2]   : Debug��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISO����������д0��Ч�� */
        unsigned int  mmbufisoen    : 1;  /* bit[3]   : MMBUF��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISO����������д0��Ч�� */
        unsigned int  reserved      : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCISODIS_UNION;
#endif
#define SOC_SCTRL_SCISODIS_audioisoen_START     (0)
#define SOC_SCTRL_SCISODIS_audioisoen_END       (0)
#define SOC_SCTRL_SCISODIS_iomcuisoen_START     (1)
#define SOC_SCTRL_SCISODIS_iomcuisoen_END       (1)
#define SOC_SCTRL_SCISODIS_debugsubisoen_START  (2)
#define SOC_SCTRL_SCISODIS_debugsubisoen_END    (2)
#define SOC_SCTRL_SCISODIS_mmbufisoen_START     (3)
#define SOC_SCTRL_SCISODIS_mmbufisoen_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCISOSTAT_UNION
 �ṹ˵��  : SCISOSTAT �Ĵ����ṹ���塣��ַƫ����:0x0C8����ֵ:0x0000000B�����:32
 �Ĵ���˵��: ������ϵͳISOʹ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audioisoen    : 1;  /* bit[0]   : Audio��ϵͳISO��Ԫʹ�ܿ��ƣ�1--ISOʹ�ܡ� */
        unsigned int  iomcuisoen    : 1;  /* bit[1]   : IOMCU��ϵͳISO��Ԫʹ�ܿ��ƣ�1--ISOʹ�ܡ� */
        unsigned int  debugsubisoen : 1;  /* bit[2]   : Debug��ϵͳISO��Ԫʹ�ܿ��ƣ�1--ISOʹ�ܡ� */
        unsigned int  mmbufisoen    : 1;  /* bit[3]   : MMBUF��ϵͳISO��Ԫʹ�ܿ��ƣ�1--ISOʹ�ܡ� */
        unsigned int  reserved      : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCISOSTAT_UNION;
#endif
#define SOC_SCTRL_SCISOSTAT_audioisoen_START     (0)
#define SOC_SCTRL_SCISOSTAT_audioisoen_END       (0)
#define SOC_SCTRL_SCISOSTAT_iomcuisoen_START     (1)
#define SOC_SCTRL_SCISOSTAT_iomcuisoen_END       (1)
#define SOC_SCTRL_SCISOSTAT_debugsubisoen_START  (2)
#define SOC_SCTRL_SCISOSTAT_debugsubisoen_END    (2)
#define SOC_SCTRL_SCISOSTAT_mmbufisoen_START     (3)
#define SOC_SCTRL_SCISOSTAT_mmbufisoen_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPWREN_UNION
 �ṹ˵��  : SCPWREN �Ĵ����ṹ���塣��ַƫ����:0x0D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ϵͳ��Դʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audiopwren    : 1;  /* bit[0]   : AUDIO��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  iomcupwren    : 1;  /* bit[1]   : IOMCU��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  debugsubpwren : 1;  /* bit[2]   : Debug��ϵͳ��Դ��Ԫʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ�����д0��Ч�� */
        unsigned int  mmbufpwren    : 1;  /* bit[3]   : MMBUF��ϵͳ��Դ��Ԫʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ�����д0��Ч�� */
        unsigned int  reserved      : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCPWREN_UNION;
#endif
#define SOC_SCTRL_SCPWREN_audiopwren_START     (0)
#define SOC_SCTRL_SCPWREN_audiopwren_END       (0)
#define SOC_SCTRL_SCPWREN_iomcupwren_START     (1)
#define SOC_SCTRL_SCPWREN_iomcupwren_END       (1)
#define SOC_SCTRL_SCPWREN_debugsubpwren_START  (2)
#define SOC_SCTRL_SCPWREN_debugsubpwren_END    (2)
#define SOC_SCTRL_SCPWREN_mmbufpwren_START     (3)
#define SOC_SCTRL_SCPWREN_mmbufpwren_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPWRDIS_UNION
 �ṹ˵��  : SCPWRDIS �Ĵ����ṹ���塣��ַƫ����:0x0D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ϵͳ��Դʹ�ܳ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audiopwren    : 1;  /* bit[0]   : AUDIO��ϵͳ��Դʹ�ܳ������ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  iomcupwren    : 1;  /* bit[1]   : IOMCU��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դ���������� */
        unsigned int  debugsubpwren : 1;  /* bit[2]   : Debug��ϵͳ��Դ��Ԫʹ�ܿ��ƣ�д1ִ�е�Դ����������д0��Ч�� */
        unsigned int  mmbufpwren    : 1;  /* bit[3]   : MMBUF��ϵͳ��Դ��Ԫʹ�ܿ��ƣ�д1ִ�е�Դ����������д0��Ч�� */
        unsigned int  reserved      : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCPWRDIS_UNION;
#endif
#define SOC_SCTRL_SCPWRDIS_audiopwren_START     (0)
#define SOC_SCTRL_SCPWRDIS_audiopwren_END       (0)
#define SOC_SCTRL_SCPWRDIS_iomcupwren_START     (1)
#define SOC_SCTRL_SCPWRDIS_iomcupwren_END       (1)
#define SOC_SCTRL_SCPWRDIS_debugsubpwren_START  (2)
#define SOC_SCTRL_SCPWRDIS_debugsubpwren_END    (2)
#define SOC_SCTRL_SCPWRDIS_mmbufpwren_START     (3)
#define SOC_SCTRL_SCPWRDIS_mmbufpwren_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPWRSTAT_UNION
 �ṹ˵��  : SCPWRSTAT �Ĵ����ṹ���塣��ַƫ����:0x0D8����ֵ:0x00000004�����:32
 �Ĵ���˵��: ������ϵͳ��Դʹ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audiopwrstat    : 1;  /* bit[0]   : AUDIO��ϵͳ��Դʹ��״̬��
                                                          0��AUDIO��ϵͳ��Դʹ�ܳ�����
                                                          1��AUDIO��ϵͳ��Դʹ�ܡ� */
        unsigned int  iomcupwrstat    : 1;  /* bit[1]   : IOMCU��ϵͳ��Դʹ��״̬��
                                                          0��IOMCU��ϵͳ��Դʹ�ܳ�����
                                                          1��IOMCU��ϵͳ��Դʹ�ܡ� */
        unsigned int  debugsubpwrstat : 1;  /* bit[2]   : Debug��ϵͳ��Դ��Ԫʹ�ܿ���״̬��
                                                          0--��Դ�ر�
                                                          1--��Դʹ�ܡ� */
        unsigned int  mmbufpwrstat    : 1;  /* bit[3]   : MMBUF��ϵͳ��Դ��Ԫʹ�ܿ���״̬��
                                                          0--��Դ�ر�
                                                          1--��Դʹ�ܡ� */
        unsigned int  reserved        : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCPWRSTAT_UNION;
#endif
#define SOC_SCTRL_SCPWRSTAT_audiopwrstat_START     (0)
#define SOC_SCTRL_SCPWRSTAT_audiopwrstat_END       (0)
#define SOC_SCTRL_SCPWRSTAT_iomcupwrstat_START     (1)
#define SOC_SCTRL_SCPWRSTAT_iomcupwrstat_END       (1)
#define SOC_SCTRL_SCPWRSTAT_debugsubpwrstat_START  (2)
#define SOC_SCTRL_SCPWRSTAT_debugsubpwrstat_END    (2)
#define SOC_SCTRL_SCPWRSTAT_mmbufpwrstat_START     (3)
#define SOC_SCTRL_SCPWRSTAT_mmbufpwrstat_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPWRACK_UNION
 �ṹ˵��  : SCPWRACK �Ĵ����ṹ���塣��ַƫ����:0x0DC����ֵ:0x00000004�����:32
 �Ĵ���˵��: ������ϵͳ���յ�Դ״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audiopwrack    : 1;  /* bit[0]   : AUDIO��ϵͳ��Դ����״̬��
                                                         0��AUDIO��ϵͳ��Դ�ж�״̬��
                                                         1��AUDIO��ϵͳ��Դ����״̬�� */
        unsigned int  reserved_0     : 1;  /* bit[1]   : ��NL��bit���Ż����⣬�޸ĵ���m7_sc_stat[1]����
                                                         IOMCU��ϵͳ��Դ��Դ����״̬��
                                                         0��IOMCU��ϵͳ��Դʹ�ܳ�����
                                                         1��IOMCU��ϵͳ��Դʹ�ܡ� */
        unsigned int  debugsubpwrack : 1;  /* bit[2]   : Debug��ϵͳ��Դ��Ԫ��Դ����״̬��
                                                         0--��Դ�ر�
                                                         1--��Դʹ�ܡ� */
        unsigned int  mmbufpwrack    : 1;  /* bit[3]   : MMBUF��ϵͳ��Դ��Ԫ��Դ����״̬��
                                                         0--��Դ�ر�
                                                         1--��Դʹ�ܡ� */
        unsigned int  reserved_1     : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCPWRACK_UNION;
#endif
#define SOC_SCTRL_SCPWRACK_audiopwrack_START     (0)
#define SOC_SCTRL_SCPWRACK_audiopwrack_END       (0)
#define SOC_SCTRL_SCPWRACK_debugsubpwrack_START  (2)
#define SOC_SCTRL_SCPWRACK_debugsubpwrack_END    (2)
#define SOC_SCTRL_SCPWRACK_mmbufpwrack_START     (3)
#define SOC_SCTRL_SCPWRACK_mmbufpwrack_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERPWRDOWNTIME_UNION
 �ṹ˵��  : SCPERPWRDOWNTIME �Ĵ����ṹ���塣��ַƫ����:0x0E0����ֵ:0x01FFFFEE�����:32
 �Ĵ���˵��: ����������ʱ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_pwr_down_time  : 25; /* bit[0-24]: ָʾPMU�����������������ʱ�䡣�ȶ�ʱ����㹫ʽ����33554432-peri_pwr_down_time+3������ʱ��Ϊ32K��(�µ����ʱ���ԼΪ600us,Ĭ��Ϊ����20��32Kʱ������)�� */
        unsigned int  timeout_op_rston    : 1;  /* bit[25]  : timeout operation on power FSM stats rston
                                                              1'b0:timeout operation bypass
                                                              1'b1:timeout enable�� */
        unsigned int  timeout_op_clkoff   : 1;  /* bit[26]  : timeout operation on power FSM stats clkoff
                                                              1'b0:timeout operation bypass
                                                              1'b1:timeout enable */
        unsigned int  timeout_op_eniso    : 1;  /* bit[27]  : timeout operation on power FSM stats eniso
                                                              1'b0:timeout operation bypass
                                                              1'b1:timeout enable�� */
        unsigned int  timeout_op_downperi : 1;  /* bit[28]  : timeout operation on power FSM stats downperi
                                                              1'b0:timeout operation bypass
                                                              1'b1:timeout enable�� */
        unsigned int  timeout_op_rston2   : 1;  /* bit[29]  : timeout operation on power FSM stats rston2
                                                              1'b0:timeout operation bypass
                                                              1'b1:timeout enable�� */
        unsigned int  timeout_op_disiso   : 1;  /* bit[30]  : timeout operation on power FSM stats disiso
                                                              1'b0:timeout operation bypass
                                                              1'b1:timeout enable�� */
        unsigned int  reserved            : 1;  /* bit[31]  : ������ */
    } reg;
} SOC_SCTRL_SCPERPWRDOWNTIME_UNION;
#endif
#define SOC_SCTRL_SCPERPWRDOWNTIME_peri_pwr_down_time_START   (0)
#define SOC_SCTRL_SCPERPWRDOWNTIME_peri_pwr_down_time_END     (24)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_rston_START     (25)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_rston_END       (25)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_clkoff_START    (26)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_clkoff_END      (26)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_eniso_START     (27)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_eniso_END       (27)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_downperi_START  (28)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_downperi_END    (28)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_rston2_START    (29)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_rston2_END      (29)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_disiso_START    (30)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_disiso_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERPWRUPTIME_UNION
 �ṹ˵��  : SCPERPWRUPTIME �Ĵ����ṹ���塣��ַƫ����:0x0E4����ֵ:0x01FFFFD8�����:32
 �Ĵ���˵��: �������ϵ�ʱ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_pwr_up_time : 25; /* bit[0-24] : ָʾPMU���������ϵ������ʱ�䡣�ȶ�ʱ����㹫ʽ����33554432-peri_pwr_up_time+3������ʱ��Ϊ32K��(�ϵ絽��������ɴ�ԼΪ1.26msĬ��Ϊ����42��32Kʱ������)�� */
        unsigned int  reserved         : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERPWRUPTIME_UNION;
#endif
#define SOC_SCTRL_SCPERPWRUPTIME_peri_pwr_up_time_START  (0)
#define SOC_SCTRL_SCPERPWRUPTIME_peri_pwr_up_time_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCLKDIV0_UNION
 �ṹ˵��  : SCCLKDIV0 �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00000202�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_asp_subsys   : 3;  /* bit[0-2]  : ASP SUBSYSʱ�ӷ�Ƶ�ȡ���Դʱ��ΪPPLL0��
                                                               3'h0:1��
                                                               3'h1:2��
                                                               3'h2:3��
                                                               3'h3:4��
                                                               ����
                                                               3'h7:8�� */
        unsigned int  sc_div_hifidsp      : 6;  /* bit[3-8]  : HIFIDSPʱ�ӷ�Ƶ�ȡ�
                                                               6'h0:1��
                                                               6'h1:2��
                                                               6'h2:3��
                                                               6'h3:4��
                                                               ��
                                                               6'h1F:64�� */
        unsigned int  sc_div_sci          : 2;  /* bit[9-10] : SCIʱ�ӷ�Ƶ�ȡ�(Դʱ��Ϊclk_aobus 60MHzʱ�ӣ���Ƶ��������)
                                                               2'h0:1��
                                                               2'h1:2��
                                                               2'h2:3��
                                                               2'h3:4�� */
        unsigned int  sc_clk_asp_pll_sel  : 1;  /* bit[11]   : ������ ASP ��ʱ��ѡ��FLL����PPLL0��������bit��
                                                               0:PPLL0
                                                               1:FPLL�� */
        unsigned int  sc_sel_mmbuf_backup : 1;  /* bit[12]   : MMBUF����400MHzѡ��
                                                               0:PPLL0
                                                               1:����400MHz�� */
        unsigned int  sc_sel_memrep       : 1;  /* bit[13]   : memrepʱ��ѡ��
                                                               0:19.2Mhz
                                                               1:40MHz�� */
        unsigned int  reserved            : 1;  /* bit[14]   : ������  */
        unsigned int  extclk_en           : 1;  /* bit[15]   : ����ʱ��ʹ�ܣ�����Ч�� */
        unsigned int  scclkdiv0_msk       : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                               ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_SCTRL_SCCLKDIV0_UNION;
#endif
#define SOC_SCTRL_SCCLKDIV0_sc_div_asp_subsys_START    (0)
#define SOC_SCTRL_SCCLKDIV0_sc_div_asp_subsys_END      (2)
#define SOC_SCTRL_SCCLKDIV0_sc_div_hifidsp_START       (3)
#define SOC_SCTRL_SCCLKDIV0_sc_div_hifidsp_END         (8)
#define SOC_SCTRL_SCCLKDIV0_sc_div_sci_START           (9)
#define SOC_SCTRL_SCCLKDIV0_sc_div_sci_END             (10)
#define SOC_SCTRL_SCCLKDIV0_sc_clk_asp_pll_sel_START   (11)
#define SOC_SCTRL_SCCLKDIV0_sc_clk_asp_pll_sel_END     (11)
#define SOC_SCTRL_SCCLKDIV0_sc_sel_mmbuf_backup_START  (12)
#define SOC_SCTRL_SCCLKDIV0_sc_sel_mmbuf_backup_END    (12)
#define SOC_SCTRL_SCCLKDIV0_sc_sel_memrep_START        (13)
#define SOC_SCTRL_SCCLKDIV0_sc_sel_memrep_END          (13)
#define SOC_SCTRL_SCCLKDIV0_extclk_en_START            (15)
#define SOC_SCTRL_SCCLKDIV0_extclk_en_END              (15)
#define SOC_SCTRL_SCCLKDIV0_scclkdiv0_msk_START        (16)
#define SOC_SCTRL_SCCLKDIV0_scclkdiv0_msk_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCLKDIV1_UNION
 �ṹ˵��  : SCCLKDIV1 �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000017�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_aobus     : 6;  /* bit[0-5]  : AOBUSʱ�ӷ�Ƶ��ѡ��(Դʱ��ΪPPLL0ʱ�ӣ���Ƶ�ȵ�������)
                                                            6'h0:1��
                                                            6'h1:2��
                                                            6'h2:3��
                                                            ��
                                                            6'h3E:63��
                                                            6'h3F:64�� */
        unsigned int  div_clkout0_tcxo : 3;  /* bit[6-8]  : clkout0 tcxoʱ�ӷ�Ƶ��ѡ�񣺣�Դʱ��Ϊ19.2MHz�ľ���ʱ�ӣ�
                                                            3'h0:1��
                                                            3'h1:2��
                                                            3'h2:3��
                                                            ��
                                                            3'h6:7��
                                                            3'h7:8�� */
        unsigned int  div_clkout1_tcxo : 3;  /* bit[9-11] : clkout1 tcxoʱ�ӷ�Ƶ��ѡ�񣺣�Դʱ��Ϊ19.2MHz�ľ���ʱ�ӣ�
                                                            3'h0:1��
                                                            3'h1:2��
                                                            3'h2:3��
                                                            ��
                                                            3'h6:7��
                                                            3'h7:8�� */
        unsigned int  sel_clkout0      : 2;  /* bit[12-13]: clkout0 ʱ��Դѡ��
                                                            0��32KHz��
                                                            1��19.2MHzʱ�ӷ�Ƶ��
                                                            2/3��PPLL3ʱ�ӷ�Ƶ�� */
        unsigned int  sel_clkout1      : 2;  /* bit[14-15]: clkout1 ʱ��Դѡ��
                                                            0��32KHz��
                                                            1��19.2MHzʱ�ӷ�Ƶ��
                                                            2/3��PPLL3ʱ�ӷ�Ƶ�� */
        unsigned int  scclkdiv1_msk    : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                            ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_SCTRL_SCCLKDIV1_UNION;
#endif
#define SOC_SCTRL_SCCLKDIV1_sc_div_aobus_START      (0)
#define SOC_SCTRL_SCCLKDIV1_sc_div_aobus_END        (5)
#define SOC_SCTRL_SCCLKDIV1_div_clkout0_tcxo_START  (6)
#define SOC_SCTRL_SCCLKDIV1_div_clkout0_tcxo_END    (8)
#define SOC_SCTRL_SCCLKDIV1_div_clkout1_tcxo_START  (9)
#define SOC_SCTRL_SCCLKDIV1_div_clkout1_tcxo_END    (11)
#define SOC_SCTRL_SCCLKDIV1_sel_clkout0_START       (12)
#define SOC_SCTRL_SCCLKDIV1_sel_clkout0_END         (13)
#define SOC_SCTRL_SCCLKDIV1_sel_clkout1_START       (14)
#define SOC_SCTRL_SCCLKDIV1_sel_clkout1_END         (15)
#define SOC_SCTRL_SCCLKDIV1_scclkdiv1_msk_START     (16)
#define SOC_SCTRL_SCCLKDIV1_scclkdiv1_msk_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCLKDIV2_UNION
 �ṹ˵��  : SCCLKDIV2 �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00003FFF�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_asp_subsys  : 1;  /* bit[0]    : ʱ���ſ����ã�
                                                              0��ʱ�ӹرգ�
                                                              1��ʱ�ӿ����� */
        unsigned int  gt_hifidsp_clk_div : 1;  /* bit[1]    : ʱ���ſ����ã�
                                                              0��ʱ�ӹرգ�
                                                              1��ʱ�ӿ����� */
        unsigned int  gt_clk_sci         : 1;  /* bit[2]    : ʱ���ſ����ã�
                                                              0��ʱ�ӹرգ�
                                                              1��ʱ�ӿ����� */
        unsigned int  gt_clk_aobus       : 1;  /* bit[3]    : ʱ���ſ����ã�
                                                              0��ʱ�ӹرգ�
                                                              1��ʱ�ӿ����� */
        unsigned int  gt_asp_hclk_div    : 1;  /* bit[4]    : ʱ���ſ����ã�
                                                              0��ʱ�ӹرգ�
                                                              1��ʱ�ӿ����� */
        unsigned int  gt_sclk_tp         : 1;  /* bit[5]    : ʱ���ſ����ã�
                                                              0��ʱ�ӹرգ�
                                                              1��ʱ�ӿ����� */
        unsigned int  gt_pll_clk_mmbuf   : 1;  /* bit[6]    : mmbuf pll��Ƶǰʱ���ſ����ã�
                                                              0��ʱ�ӹرգ�
                                                              1��ʱ�ӿ�����
                                                              ��������ֵ��iomcu��audio�ʹ�����λͶƱȷ����������򿪾�ʱ�ӣ��������󶼹رղŹر�ʱ�ӡ� */
        unsigned int  gt_pclk_mmbuf      : 1;  /* bit[7]    : mmbuf pll��Ƶ��ʱ���ſ����ã�
                                                              0��ʱ�ӹرգ�
                                                              1��ʱ�ӿ����� */
        unsigned int  sel_clk_mmbuf      : 2;  /* bit[8-9]  : mmbufʱ����Դѡ��
                                                              00��TCXO
                                                              01��FPLL
                                                              1x: PPLL0
                                                              ��������ֵ��iomcu��audio�ʹ�����λͶƱȷ�����������ܵȼ������ٲã�PPLL0>FPLL>TCXO�� */
        unsigned int  sc_div2_mmbuf      : 2;  /* bit[10-11]: mmbuf��Ƶ�ȿ��ƣ���Ƶ��=����ֵ+1�� */
        unsigned int  sc_div4_mmbuf      : 4;  /* bit[12-15]: mmbuf��Ƶ�ȿ��ƣ���Ƶ��=����ֵ+1�� */
        unsigned int  scclkdiv2_msk      : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                              ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_SCTRL_SCCLKDIV2_UNION;
#endif
#define SOC_SCTRL_SCCLKDIV2_gt_clk_asp_subsys_START   (0)
#define SOC_SCTRL_SCCLKDIV2_gt_clk_asp_subsys_END     (0)
#define SOC_SCTRL_SCCLKDIV2_gt_hifidsp_clk_div_START  (1)
#define SOC_SCTRL_SCCLKDIV2_gt_hifidsp_clk_div_END    (1)
#define SOC_SCTRL_SCCLKDIV2_gt_clk_sci_START          (2)
#define SOC_SCTRL_SCCLKDIV2_gt_clk_sci_END            (2)
#define SOC_SCTRL_SCCLKDIV2_gt_clk_aobus_START        (3)
#define SOC_SCTRL_SCCLKDIV2_gt_clk_aobus_END          (3)
#define SOC_SCTRL_SCCLKDIV2_gt_asp_hclk_div_START     (4)
#define SOC_SCTRL_SCCLKDIV2_gt_asp_hclk_div_END       (4)
#define SOC_SCTRL_SCCLKDIV2_gt_sclk_tp_START          (5)
#define SOC_SCTRL_SCCLKDIV2_gt_sclk_tp_END            (5)
#define SOC_SCTRL_SCCLKDIV2_gt_pll_clk_mmbuf_START    (6)
#define SOC_SCTRL_SCCLKDIV2_gt_pll_clk_mmbuf_END      (6)
#define SOC_SCTRL_SCCLKDIV2_gt_pclk_mmbuf_START       (7)
#define SOC_SCTRL_SCCLKDIV2_gt_pclk_mmbuf_END         (7)
#define SOC_SCTRL_SCCLKDIV2_sel_clk_mmbuf_START       (8)
#define SOC_SCTRL_SCCLKDIV2_sel_clk_mmbuf_END         (9)
#define SOC_SCTRL_SCCLKDIV2_sc_div2_mmbuf_START       (10)
#define SOC_SCTRL_SCCLKDIV2_sc_div2_mmbuf_END         (11)
#define SOC_SCTRL_SCCLKDIV2_sc_div4_mmbuf_START       (12)
#define SOC_SCTRL_SCCLKDIV2_sc_div4_mmbuf_END         (15)
#define SOC_SCTRL_SCCLKDIV2_scclkdiv2_msk_START       (16)
#define SOC_SCTRL_SCCLKDIV2_scclkdiv2_msk_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCLKDIV3_UNION
 �ṹ˵��  : SCCLKDIV3 �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00007C0F�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aobus_auto_waitcfg_out : 10; /* bit[0-9]  : Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������á� */
        unsigned int  aobus_div_auto_cfg     : 6;  /* bit[10-15]: Ӳ���Զ���Ƶ��������
                                                                  6'h00:1��
                                                                  6'h01:2��
                                                                  ��
                                                                  6'h3F:64�� */
        unsigned int  scclkdiv3_msk          : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                                  ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_SCTRL_SCCLKDIV3_UNION;
#endif
#define SOC_SCTRL_SCCLKDIV3_aobus_auto_waitcfg_out_START  (0)
#define SOC_SCTRL_SCCLKDIV3_aobus_auto_waitcfg_out_END    (9)
#define SOC_SCTRL_SCCLKDIV3_aobus_div_auto_cfg_START      (10)
#define SOC_SCTRL_SCCLKDIV3_aobus_div_auto_cfg_END        (15)
#define SOC_SCTRL_SCCLKDIV3_scclkdiv3_msk_START           (16)
#define SOC_SCTRL_SCCLKDIV3_scclkdiv3_msk_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCLKDIV4_UNION
 �ṹ˵��  : SCCLKDIV4 �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00008DE5�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_aobus_noc     : 4;  /* bit[0-3]  : aobus ppll0�����Ƶ�� */
        unsigned int  sel_clk_aobus_noc : 2;  /* bit[4-5]  : aobus clkѡ��pll
                                                             00��TCXO
                                                             01��FPLL
                                                             10��DDRPLL
                                                             11: PPLL0
                                                             ��������ֵ��iomcu��audio�ʹ�����λͶƱȷ�����������ܵȼ������ٲã�DDRPLL>PPLL0>FPLL>TCXO�� */
        unsigned int  gt_aobus_noc_ini  : 1;  /* bit[6]    : aobus ppll0����ſ�
                                                             0��ʱ�ӹرգ�
                                                             1��ʱ�ӿ�����
                                                             ��������ֵ��iomcu��audio�ʹ�����λͶƱȷ����������򿪾�ʱ�ӣ��������󶼹رղŹر�ʱ�ӡ� */
        unsigned int  reserved          : 1;  /* bit[7]    : ������ */
        unsigned int  sc_div_asp_hclk   : 2;  /* bit[8-9]  : asp hclk��Ƶ�ȡ�(Դʱ��Ϊclk_asp_subsys)
                                                             2'h0:1��
                                                             2'h1:2��
                                                             2'h2:3��
                                                             2'h3:4�� */
        unsigned int  gt_clk_memrep     : 1;  /* bit[10]   : clk memrep pll����ſء� */
        unsigned int  sc_div_memrep     : 5;  /* bit[11-15]: clk memrep pll�����Ƶ
                                                             ��Ƶ��Ϊ������ֵ��10������*2+2,Ĭ��ֵ36��Ƶ�� */
        unsigned int  scclkdiv4_msk     : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                             ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_SCTRL_SCCLKDIV4_UNION;
#endif
#define SOC_SCTRL_SCCLKDIV4_div_aobus_noc_START      (0)
#define SOC_SCTRL_SCCLKDIV4_div_aobus_noc_END        (3)
#define SOC_SCTRL_SCCLKDIV4_sel_clk_aobus_noc_START  (4)
#define SOC_SCTRL_SCCLKDIV4_sel_clk_aobus_noc_END    (5)
#define SOC_SCTRL_SCCLKDIV4_gt_aobus_noc_ini_START   (6)
#define SOC_SCTRL_SCCLKDIV4_gt_aobus_noc_ini_END     (6)
#define SOC_SCTRL_SCCLKDIV4_sc_div_asp_hclk_START    (8)
#define SOC_SCTRL_SCCLKDIV4_sc_div_asp_hclk_END      (9)
#define SOC_SCTRL_SCCLKDIV4_gt_clk_memrep_START      (10)
#define SOC_SCTRL_SCCLKDIV4_gt_clk_memrep_END        (10)
#define SOC_SCTRL_SCCLKDIV4_sc_div_memrep_START      (11)
#define SOC_SCTRL_SCCLKDIV4_sc_div_memrep_END        (15)
#define SOC_SCTRL_SCCLKDIV4_scclkdiv4_msk_START      (16)
#define SOC_SCTRL_SCCLKDIV4_scclkdiv4_msk_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCLKDIV5_UNION
 �ṹ˵��  : SCCLKDIV5 �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x000003FF�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aobus_div_auto_reduce_bypass : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                        0����bypass��
                                                                        1��bypass�� */
        unsigned int  aobus_auto_waitcfg_in        : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������á� */
        unsigned int  aobus_clk_sw_req_cfg         : 2;  /* bit[11-12]: aobus�����л����󣬴˽ӿڽ���normal���ã�ʵ�����õ�bit��Ч:
                                                                        x1��aobus�л�Ϊtcxoʱ��
                                                                        ������aobus�л�Ϊϵͳʱ�ӡ� */
        unsigned int  reserved                     : 3;  /* bit[13-15]: ������ */
        unsigned int  scclkdiv5_msk                : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                                        ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_SCTRL_SCCLKDIV5_UNION;
#endif
#define SOC_SCTRL_SCCLKDIV5_aobus_div_auto_reduce_bypass_START  (0)
#define SOC_SCTRL_SCCLKDIV5_aobus_div_auto_reduce_bypass_END    (0)
#define SOC_SCTRL_SCCLKDIV5_aobus_auto_waitcfg_in_START         (1)
#define SOC_SCTRL_SCCLKDIV5_aobus_auto_waitcfg_in_END           (10)
#define SOC_SCTRL_SCCLKDIV5_aobus_clk_sw_req_cfg_START          (11)
#define SOC_SCTRL_SCCLKDIV5_aobus_clk_sw_req_cfg_END            (12)
#define SOC_SCTRL_SCCLKDIV5_scclkdiv5_msk_START                 (16)
#define SOC_SCTRL_SCCLKDIV5_scclkdiv5_msk_END                   (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERCTRL0_UNION
 �ṹ˵��  : SCPERCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x200����ֵ:0x00000C9B�����:32
 �Ĵ���˵��: ������ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 16; /* bit[0-15] : ������ */
        unsigned int  efuse_remap : 1;  /* bit[16]   : �͸�EFUSEC��REMAP����
                                                       0:not remap 1:image remap�� */
        unsigned int  reserved_1  : 3;  /* bit[17-19]: ������ */
        unsigned int  reserved_2  : 12; /* bit[20-31]: mmbuf_sec_ctrl��SCPERCLKEN0_SEC[31:20]���ơ� */
    } reg;
} SOC_SCTRL_SCPERCTRL0_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL0_efuse_remap_START  (16)
#define SOC_SCTRL_SCPERCTRL0_efuse_remap_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERCTRL1_UNION
 �ṹ˵��  : SCPERCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x204����ֵ:0xFFFFFFF8�����:32
 �Ĵ���˵��: ������ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_disable : 32; /* bit[0-31]: ����ָʾ����IP�Ƿ���Ҫ��mem repair:
                                                         0�����޸���1�����޸�
                                                         AO_SUBSYS MRB0
                                                         PERI_SUBSYS(����ֻ����LP_M3) MRB1
                                                         DEBUG_SEC_HSIC_PERI_SUBSYS MRB2
                                                         MODEM_SUBSYS MRB3
                                                         BBP_COM_TOP_PD MRB4
                                                         BBP_IRM_TOP_PD MRB5
                                                         A9_WRAP_PD MRB6
                                                         DSP_WRAP_PD MRB7
                                                         BBP_LTE_TOP_PD MRB8
                                                         A57_SUBSYS MRB9
                                                         A53_SUBSYS MRB10
                                                         AUDIO_SUBSYS MRB11
                                                         IOMUC_SUBSYS MRB12
                                                         MMBUF_SUBSYS MRB13
                                                         DSS MRB14
                                                         ISP_SUBSYS MRB15
                                                         IVP32_DSP_SUBSYS MRB16
                                                         VDEC MRB17
                                                         VENC MRB18
                                                         GPU_SUBSYS MRB19
                                                         BBP_CS_CORE MRB20�� */
    } reg;
} SOC_SCTRL_SCPERCTRL1_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL1_repair_disable_START  (0)
#define SOC_SCTRL_SCPERCTRL1_repair_disable_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERCTRL2_UNION
 �ṹ˵��  : SCPERCTRL2 �Ĵ����ṹ���塣��ַƫ����:0x208����ֵ:0x00000715�����:32
 �Ĵ���˵��: ������ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_spram_rtsel    : 2;  /* bit[0-1]  : ao_spram_rtsel����ο�memory�ֲᡣ */
        unsigned int  ao_spram_wtsel    : 2;  /* bit[2-3]  : ao_spram_wtsel����ο�memory�ֲᡣ */
        unsigned int  ao_spmbsram_rtsel : 2;  /* bit[4-5]  : ao_spmbsram_rtselĿǰδʹ�á� */
        unsigned int  ao_spmbsram_wtsel : 2;  /* bit[6-7]  : ao_spmbsram_wtselĿǰδʹ�á� */
        unsigned int  ao_rom_rtsel      : 2;  /* bit[8-9]  : ao_rom_rtselĿǰδʹ�á� */
        unsigned int  ao_rom_ptsel      : 2;  /* bit[10-11]: ao_rom_ptselĿǰδʹ�á� */
        unsigned int  ao_rom_trb        : 2;  /* bit[12-13]: ao_rom_trbĿǰδʹ�á� */
        unsigned int  ao_rom_tm         : 1;  /* bit[14]   : ao_rom_tmĿǰδʹ�á� */
        unsigned int  mmbuf_sram_sd     : 1;  /* bit[15]   : mmbuf_sram_sd memory�����źţ�����ο�memory�ֲᡣ */
        unsigned int  reserved_0        : 8;  /* bit[16-23]: ������ */
        unsigned int  jtaq_to_sdcard    : 1;  /* bit[24]   : �͸�JTAG MUX�Ŀ����ź�
                                                             0:dsp jtagʹ��ͨ��jtag�˿ڽ��е���
                                                             1��dsp jtagʹ��ͨ��SD�ܽŶ˿ڽ��е��ԡ� */
        unsigned int  sc_djtaq_sel      : 1;  /* bit[25]   : ����bit����ѡ��DJTAG����JTAG���
                                                             0:jtag
                                                             1:djtag�� */
        unsigned int  reserved_1        : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERCTRL2_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL2_ao_spram_rtsel_START     (0)
#define SOC_SCTRL_SCPERCTRL2_ao_spram_rtsel_END       (1)
#define SOC_SCTRL_SCPERCTRL2_ao_spram_wtsel_START     (2)
#define SOC_SCTRL_SCPERCTRL2_ao_spram_wtsel_END       (3)
#define SOC_SCTRL_SCPERCTRL2_ao_spmbsram_rtsel_START  (4)
#define SOC_SCTRL_SCPERCTRL2_ao_spmbsram_rtsel_END    (5)
#define SOC_SCTRL_SCPERCTRL2_ao_spmbsram_wtsel_START  (6)
#define SOC_SCTRL_SCPERCTRL2_ao_spmbsram_wtsel_END    (7)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_rtsel_START       (8)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_rtsel_END         (9)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_ptsel_START       (10)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_ptsel_END         (11)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_trb_START         (12)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_trb_END           (13)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_tm_START          (14)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_tm_END            (14)
#define SOC_SCTRL_SCPERCTRL2_mmbuf_sram_sd_START      (15)
#define SOC_SCTRL_SCPERCTRL2_mmbuf_sram_sd_END        (15)
#define SOC_SCTRL_SCPERCTRL2_jtaq_to_sdcard_START     (24)
#define SOC_SCTRL_SCPERCTRL2_jtaq_to_sdcard_END       (24)
#define SOC_SCTRL_SCPERCTRL2_sc_djtaq_sel_START       (25)
#define SOC_SCTRL_SCPERCTRL2_sc_djtaq_sel_END         (25)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERCTRL3_UNION
 �ṹ˵��  : SCPERCTRL3 �Ĵ����ṹ���塣��ַƫ����:0x20C����ֵ:0x00004000�����:32
 �Ĵ���˵��: ������ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_debug_sel         : 1;  /* bit[0]    : ͨ��AHB����DEBUG����ѡ��
                                                                    0��AHB�˿ڲ��ܷ���SRAM��
                                                                    1��AHB�˿ڿ��Է���SRAM�� */
        unsigned int  reset_memrep_msk         : 1;  /* bit[1]    : reset_memrep_msk
                                                                    0:bisr��λ�����repair_frm_efu
                                                                    1:bisr��λ�󲻸���repair_frm_efu�� */
        unsigned int  repair_iddq              : 1;  /* bit[2]    : 1'b0:��IDDQģʽ
                                                                    1'b1:BISR����EFUSE����IDDQģʽ�� */
        unsigned int  repair_frm_sram          : 1;  /* bit[3]    : ָʾ�޸�������ԴSRAM��
                                                                    1'b0:�޸�������ԴEFUSE��
                                                                    1'b1:�޸�������ԴSRAM�� */
        unsigned int  repair_frm_efu           : 1;  /* bit[4]    : ָʾ�޸�������ԴEFUSE��
                                                                    1'b0:
                                                                    1'b1:�޸�������ԴEFUSE
                                                                    ���ź���reset_memrep_n�źŵ��������Զ���Ϊ1�� */
        unsigned int  dram_pwr_ctl             : 3;  /* bit[5-7]  : �����ڲ�˫�˿�RAM POWER,����ο�memory�ֲᡣ */
        unsigned int  efusec_timeout_bypass    : 1;  /* bit[8]    : efusec timeout bypass����δʹ�ã��� */
        unsigned int  bbdrx_timeout_bypass     : 1;  /* bit[9]    : bbdrx timeout bypass
                                                                    0:no bypass 1:bypass�� */
        unsigned int  sleep_mode_cfgbus_bypass : 1;  /* bit[10]   : 1'b0:sleepmode��Чʱ��ʱ��
                                                                    1'b1:sleepmode��Чʱ����ʱ�ӡ� */
        unsigned int  sleep_mode_lpmcu_bypass  : 1;  /* bit[11]   : 1'b0:sleepmode��Чʱ��ʱ��
                                                                    1'b1:sleepmode��Чʱ����ʱ�ӡ� */
        unsigned int  ao_mrb_rst_msk           : 1;  /* bit[12]   : ao��memroy�޸��������α���,��bit��Ҫ��suspend��������Ϊ1'b1
                                                                    1'b0:resume������LPM3����SCtrl��bit�Ĵ���Ϊ0���������Σ���ʱBISR���Ը���Ӧ����Ҫ�޸�AO����MRB
                                                                    1'b1:��suspend�����У���LPM3����оƬ����˯��̬֮ǰ������SCtrl��bit�Ĵ���Ϊ1���������ε�����BISR����ĸ�λ0��ƽ��Ȼ����������˯�����̡� */
        unsigned int  sleep_mode_aobus_bypass  : 1;  /* bit[13]   : 1'b0:sleepmode��Чʱ��ʱ��
                                                                    1'b1:sleepmode��Чʱ����ʱ�ӡ� */
        unsigned int  bbp_clk_en               : 1;  /* bit[14]   : �͸�BBPDRX��ʱ��ʹ���źţ�
                                                                    1'b0:��ʱ��
                                                                    1'b1:��ʱ�ӡ� */
        unsigned int  reserved                 : 1;  /* bit[15]   : ������ */
        unsigned int  bbp_on_ctrl              : 16; /* bit[16-31]: bbp_on_ctrl��Ԥ������ʹ��
                                                                    [3]bbp_timer_srst_en bbp on �� bbp 64bit timer ʱ�Ӷ�Ӧ����λʹ���źţ�
                                                                    1����λ
                                                                    0������λ
                                                                    [2]bbp_32k_srst_en bbp on �� bbp 32k ʱ�Ӷ�Ӧ����λʹ���źţ�
                                                                    1����λ
                                                                    0������λ 
                                                                    [1]g2_104m_srst_en bbp on �� g2 104Mʱ�Ӷ�Ӧ����λʹ���źţ�
                                                                    1����λ
                                                                    0������λ 
                                                                    [0]g1_104m_srst_en bbp on �� g1 104Mʱ�Ӷ�Ӧ����λʹ���źţ�
                                                                    1����λ
                                                                    0������λ �� */
    } reg;
} SOC_SCTRL_SCPERCTRL3_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL3_repair_debug_sel_START          (0)
#define SOC_SCTRL_SCPERCTRL3_repair_debug_sel_END            (0)
#define SOC_SCTRL_SCPERCTRL3_reset_memrep_msk_START          (1)
#define SOC_SCTRL_SCPERCTRL3_reset_memrep_msk_END            (1)
#define SOC_SCTRL_SCPERCTRL3_repair_iddq_START               (2)
#define SOC_SCTRL_SCPERCTRL3_repair_iddq_END                 (2)
#define SOC_SCTRL_SCPERCTRL3_repair_frm_sram_START           (3)
#define SOC_SCTRL_SCPERCTRL3_repair_frm_sram_END             (3)
#define SOC_SCTRL_SCPERCTRL3_repair_frm_efu_START            (4)
#define SOC_SCTRL_SCPERCTRL3_repair_frm_efu_END              (4)
#define SOC_SCTRL_SCPERCTRL3_dram_pwr_ctl_START              (5)
#define SOC_SCTRL_SCPERCTRL3_dram_pwr_ctl_END                (7)
#define SOC_SCTRL_SCPERCTRL3_efusec_timeout_bypass_START     (8)
#define SOC_SCTRL_SCPERCTRL3_efusec_timeout_bypass_END       (8)
#define SOC_SCTRL_SCPERCTRL3_bbdrx_timeout_bypass_START      (9)
#define SOC_SCTRL_SCPERCTRL3_bbdrx_timeout_bypass_END        (9)
#define SOC_SCTRL_SCPERCTRL3_sleep_mode_cfgbus_bypass_START  (10)
#define SOC_SCTRL_SCPERCTRL3_sleep_mode_cfgbus_bypass_END    (10)
#define SOC_SCTRL_SCPERCTRL3_sleep_mode_lpmcu_bypass_START   (11)
#define SOC_SCTRL_SCPERCTRL3_sleep_mode_lpmcu_bypass_END     (11)
#define SOC_SCTRL_SCPERCTRL3_ao_mrb_rst_msk_START            (12)
#define SOC_SCTRL_SCPERCTRL3_ao_mrb_rst_msk_END              (12)
#define SOC_SCTRL_SCPERCTRL3_sleep_mode_aobus_bypass_START   (13)
#define SOC_SCTRL_SCPERCTRL3_sleep_mode_aobus_bypass_END     (13)
#define SOC_SCTRL_SCPERCTRL3_bbp_clk_en_START                (14)
#define SOC_SCTRL_SCPERCTRL3_bbp_clk_en_END                  (14)
#define SOC_SCTRL_SCPERCTRL3_bbp_on_ctrl_START               (16)
#define SOC_SCTRL_SCPERCTRL3_bbp_on_ctrl_END                 (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERCTRL4_UNION
 �ṹ˵��  : SCPERCTRL4 �Ĵ����ṹ���塣��ַƫ����:0x210����ֵ:0x09280000�����:32
 �Ĵ���˵��: ������ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddr_ret_en : 4;  /* bit[0-3]  : ����DDRPHY����Retentionģʽ�Ŀ����źţ�4��ͨ���������ƣ�
                                                      1'b0��ret��Ч��
                                                      1'b1��ret��Ч�� */
        unsigned int  reserved_0 : 1;  /* bit[4]    : xo_mode_a2d �ź�ָʾ��ǰ32K��Դ��19.2MHz/586 ����32768Hz��
                                                      0��ʾ19.2MHz/586��
                                                      1��ʾ32768Hz;
                                                      ע�⣺������������ô�bit�� */
        unsigned int  reserved_1 : 3;  /* bit[5-7]  : ������ */
        unsigned int  crc_value  : 21; /* bit[8-28] : RTCԭ����32K RCʱ��ͬ����19.2MHzʱ����������1024��RCʱ�Ӽ��������ڣ�ͳ��19.2MHz��ʱ�Ӹ������õ���ֵA��
                                                      ��֪A=N*1024+B������N��BΪ��������A�����������N������B��
                                                      b) 32K��ԴΪ19.2MHz/586 ʱ��NΪ586�� BΪ0��
                                                      c) 32K��ԴΪ32768Hz ʱ�� NΪ585�� BΪ960��
                                                      ��11bit ��������N����10bit ��������B�� */
        unsigned int  reserved_2 : 3;  /* bit[29-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERCTRL4_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL4_ddr_ret_en_START  (0)
#define SOC_SCTRL_SCPERCTRL4_ddr_ret_en_END    (3)
#define SOC_SCTRL_SCPERCTRL4_crc_value_START   (8)
#define SOC_SCTRL_SCPERCTRL4_crc_value_END     (28)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERCTRL5_UNION
 �ṹ˵��  : SCPERCTRL5 �Ĵ����ṹ���塣��ַƫ����:0x214����ֵ:0x00101003�����:32
 �Ĵ���˵��: ������ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usim0_io_sel18    : 1;  /* bit[0]    : USIM��0��ODIO��ѹ�л������ź�
                                                             0��3.3V 1��1.8V�� */
        unsigned int  usim1_io_sel18    : 1;  /* bit[1]    : USIM��1��ODIO��ѹ�л������ź�
                                                             0��3.3V 1��1.8V�� */
        unsigned int  sdcard_io_sel18   : 1;  /* bit[2]    : SDCARD��ODIO��ѹ�л��ź�
                                                             0��3.3V 1��1.8V�� */
        unsigned int  reserved_0        : 3;  /* bit[3-5]  : ������ */
        unsigned int  reserved_1        : 1;  /* bit[6]    : ������ */
        unsigned int  usim_od_en        : 1;  /* bit[7]    : USIM����������ѡ���ź�
                                                             0����©�����OD��
                                                             1����̬ģʽ��push-pull���� */
        unsigned int  tp_sel            : 4;  /* bit[8-11] : �����źŷ���ѡ����ϸ���������ο���������ĵ��� */
        unsigned int  ao_hpm_clk_div    : 6;  /* bit[12-17]: ao HPMʱ�ӷ�Ƶ��������ֵҪ�����1����Ƶ��=����ֵ+1�� */
        unsigned int  ao_hpm_en         : 1;  /* bit[18]   : ao HPMʹ�ܡ�
                                                             0:disable 1:enable�� */
        unsigned int  ao_hpmx_en        : 1;  /* bit[19]   : ao HPMXʹ�ܡ�
                                                             0:disable 1:enable�� */
        unsigned int  sc_noc_timeout_en : 1;  /* bit[20]   : sc_noc_timeout_en
                                                             0��not timeout 1:timeout�� */
        unsigned int  peri_ctrl5_other  : 11; /* bit[21-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERCTRL5_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL5_usim0_io_sel18_START     (0)
#define SOC_SCTRL_SCPERCTRL5_usim0_io_sel18_END       (0)
#define SOC_SCTRL_SCPERCTRL5_usim1_io_sel18_START     (1)
#define SOC_SCTRL_SCPERCTRL5_usim1_io_sel18_END       (1)
#define SOC_SCTRL_SCPERCTRL5_sdcard_io_sel18_START    (2)
#define SOC_SCTRL_SCPERCTRL5_sdcard_io_sel18_END      (2)
#define SOC_SCTRL_SCPERCTRL5_usim_od_en_START         (7)
#define SOC_SCTRL_SCPERCTRL5_usim_od_en_END           (7)
#define SOC_SCTRL_SCPERCTRL5_tp_sel_START             (8)
#define SOC_SCTRL_SCPERCTRL5_tp_sel_END               (11)
#define SOC_SCTRL_SCPERCTRL5_ao_hpm_clk_div_START     (12)
#define SOC_SCTRL_SCPERCTRL5_ao_hpm_clk_div_END       (17)
#define SOC_SCTRL_SCPERCTRL5_ao_hpm_en_START          (18)
#define SOC_SCTRL_SCPERCTRL5_ao_hpm_en_END            (18)
#define SOC_SCTRL_SCPERCTRL5_ao_hpmx_en_START         (19)
#define SOC_SCTRL_SCPERCTRL5_ao_hpmx_en_END           (19)
#define SOC_SCTRL_SCPERCTRL5_sc_noc_timeout_en_START  (20)
#define SOC_SCTRL_SCPERCTRL5_sc_noc_timeout_en_END    (20)
#define SOC_SCTRL_SCPERCTRL5_peri_ctrl5_other_START   (21)
#define SOC_SCTRL_SCPERCTRL5_peri_ctrl5_other_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERCTRL6_UNION
 �ṹ˵��  : SCPERCTRL6 �Ĵ����ṹ���塣��ַƫ����:0x218����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_io_ret            : 1;  /* bit[0-0]  : ���������������IO Retetion��
                                                                  0��Retetion������
                                                                  1��Retetionʹ�ܡ� */
        unsigned int  sc_noc_aobus_idle_flag : 1;  /* bit[1]    : sc_noc_aobus_idle_flag
                                                                  0��aobus not idle
                                                                  1:aobus idle
                                                                  ���ź���4���źţ�
                                                                  sc_aonoc_asp_mst_i_mainnopendingtrans
                                                                  iomcu_axi_ahb_nopendingtrans
                                                                  iomcu_axi_mst_nopendingtrans
                                                                  iomcu_dma_mst_nopendingtrans
                                                                  λ�룬ÿ���ź�֧��bypass�����ź���Чʱ��sys bus���Զ���Ƶ�� */
        unsigned int  efuse_arm_dbg_ctrl     : 2;  /* bit[2-3]  : ��ȫdebug�ȼ�
                                                                  00��debug enable default
                                                                  01����ϵͳ��Ȩ��sc�ڲ������cfg_arm_dbgen[3:0]����
                                                                  10����dx��Ȩ��dx�ڲ������cfg_arm_dbgen_dx[3:0]����
                                                                  11����efuse��дֵefuse_arm_dbgen[3:0]���ơ� */
        unsigned int  peri_bootio_ret        : 1;  /* bit[4-4]  : �������������IO Retetion��
                                                                  0��Retetion������
                                                                  1��Retetionʹ�ܡ� */
        unsigned int  peri_bootio_ret_mode   : 1;  /* bit[5-5]  : �������������IO Retetion����ģʽ��
                                                                  0���ɱ���4������ֵ���ƣ�
                                                                  1����Ӳ���Զ����ơ� */
        unsigned int  reserved_0             : 2;  /* bit[6-7]  : �˿���sel_clk_aobus_noc_comb����,Ĭ��ֵΪ0x2,aobus clkʱ����Դѡ��
                                                                  00��TCXO
                                                                  01��FPLL
                                                                  10��DDRPLL
                                                                  11: PPLL0
                                                                  ��������ֵ��iomcu��audio��sel_clk_aobus_noc����λͶƱȷ�����������ܵȼ������ٲã�DDRPLL>PPLL0>FPLL>TCXO�� */
        unsigned int  reserved_1             : 2;  /* bit[8-9]  : �˿���sel_clk_mmbuf_comb����,Ĭ��ֵΪ0x3,mmbufʱ����Դѡ��
                                                                  00��TCXO
                                                                  01��FPLL
                                                                  1x: PPLL0
                                                                  ��������ֵ��iomcu��audio��sel_clk_mmbuf����λͶƱȷ�����������ܵȼ������ٲã�PPLL0>FPLL>TCXO�� */
        unsigned int  reserved_2             : 9;  /* bit[10-18]: ������ */
        unsigned int  gt_rst_asc             : 1;  /* bit[19]   : ������ */
        unsigned int  reserved_3             : 1;  /* bit[20]   : ��ԭʼ�ж�aomcu_ao_noc_mainstatalarm_int��maskλaomcu_ao_noc_mainstatalarm_intmsk�����ȷ�����������£�
                                                                  0:no int;
                                                                  1:int produced�� */
        unsigned int  reserved_4             : 1;  /* bit[21]   : ��ԭʼ�ж�aomcu_ao_noc_mainfault_int��maskλaomcu_ao_noc_mainfault_intmsk�����ȷ�����������£�
                                                                  0:no int;
                                                                  1:int produced�� */
        unsigned int  reserved_5             : 1;  /* bit[22]   : ��ԭʼ�ж�asp_transaction_probe_mainstatalarm_int��maskλasp_transaction_probe_mainstatalarm_intmsk�����ȷ�����������£�
                                                                  0:no int;
                                                                  1:int produced�� */
        unsigned int  reserved_6             : 1;  /* bit[23]   : ��ԭʼ�ж�asp_error_probe_observer_mainfault_int��maskλasp_error_probe_observer_mainfault_intmsk�����ȷ�����������£�
                                                                  0:no int;
                                                                  1:int produced�� */
        unsigned int  reserved_7             : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERCTRL6_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL6_peri_io_ret_START             (0)
#define SOC_SCTRL_SCPERCTRL6_peri_io_ret_END               (0)
#define SOC_SCTRL_SCPERCTRL6_sc_noc_aobus_idle_flag_START  (1)
#define SOC_SCTRL_SCPERCTRL6_sc_noc_aobus_idle_flag_END    (1)
#define SOC_SCTRL_SCPERCTRL6_efuse_arm_dbg_ctrl_START      (2)
#define SOC_SCTRL_SCPERCTRL6_efuse_arm_dbg_ctrl_END        (3)
#define SOC_SCTRL_SCPERCTRL6_peri_bootio_ret_START         (4)
#define SOC_SCTRL_SCPERCTRL6_peri_bootio_ret_END           (4)
#define SOC_SCTRL_SCPERCTRL6_peri_bootio_ret_mode_START    (5)
#define SOC_SCTRL_SCPERCTRL6_peri_bootio_ret_mode_END      (5)
#define SOC_SCTRL_SCPERCTRL6_gt_rst_asc_START              (19)
#define SOC_SCTRL_SCPERCTRL6_gt_rst_asc_END                (19)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS0_UNION
 �ṹ˵��  : SCPERSTATUS0 �Ĵ����ṹ���塣��ַƫ����:0x21C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_dwaxi_dlock_wr  : 1;  /* bit[0]    : asp��ϵͳ�ڲ�bus������ָʾ�źš� */
        unsigned int  asp_dwaxi_dlock_id  : 4;  /* bit[1-4]  : asp��ϵͳ�ڲ�bus������ָʾ�źš� */
        unsigned int  asp_dwaxi_dlock_slv : 3;  /* bit[5-7]  : asp��ϵͳ�ڲ�bus������ָʾ�źš� */
        unsigned int  asp_dwaxi_dlock_mst : 2;  /* bit[8-9]  : asp��ϵͳ�ڲ�bus������ָʾ�źš� */
        unsigned int  tp_a0_grp           : 10; /* bit[10-19]: ���Թܽ�
                                                               sys_mode[0] AO�ܽ�-A0 A0_0
                                                               sys_mode[1] AO�ܽ�-A0 A0_1
                                                               sys_mode[2] AO�ܽ�-A0 A0_2
                                                               sys_mode[3] AO�ܽ�-A0 A0_3
                                                               clkgt_ctrl AO�ܽ�-A0 A0_4
                                                               por_int_n AO�ܽ�-A0 A0_5
                                                               sclk_tp AO�ܽ�-A0 A0_6
                                                               xtal_sw_ack AO�ܽ�-A0 A0_7
                                                               preset_efusec_n AO�ܽ�-A0 A0_8
                                                               reset_memrep_n AO�ܽ�-A0 A0_9�� */
        unsigned int  tp_a1_grp           : 10; /* bit[20-29]: ���Թܽ�
                                                               sys_pw_stat[0] AO�ܽ�-A1 A1_0
                                                               sys_pw_stat[1] AO�ܽ�-A1 A1_1
                                                               sys_pw_stat[2] AO�ܽ�-A1 A1_2
                                                               sys_pw_stat[3] AO�ܽ�-A1 A1_3
                                                               tcxo0_en AO�ܽ�-A1 A1_4
                                                               tcxo1_en AO�ܽ�-A1 A1_5
                                                               clkgt_ctrl0 AO�ܽ�-A1 A1_6
                                                               clkgt_ctrl1 AO�ܽ�-A1 A1_7
                                                               abbbuf_en0 AO�ܽ�-A1 A1_8
                                                               abbbuf_en1 AO�ܽ�-A1 A1_9�� */
        unsigned int  reserved_0          : 1;  /* bit[30]   : ������ */
        unsigned int  reserved_1          : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_SCTRL_SCPERSTATUS0_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_wr_START   (0)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_wr_END     (0)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_id_START   (1)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_id_END     (4)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_slv_START  (5)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_slv_END    (7)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_mst_START  (8)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_mst_END    (9)
#define SOC_SCTRL_SCPERSTATUS0_tp_a0_grp_START            (10)
#define SOC_SCTRL_SCPERSTATUS0_tp_a0_grp_END              (19)
#define SOC_SCTRL_SCPERSTATUS0_tp_a1_grp_START            (20)
#define SOC_SCTRL_SCPERSTATUS0_tp_a1_grp_END              (29)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS1_UNION
 �ṹ˵��  : SCPERSTATUS1 �Ĵ����ṹ���塣��ַƫ����:0x220����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  err_flag : 32; /* bit[0-31]: memory repairģ��errָʾ�� */
    } reg;
} SOC_SCTRL_SCPERSTATUS1_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS1_err_flag_START  (0)
#define SOC_SCTRL_SCPERSTATUS1_err_flag_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS2_UNION
 �ṹ˵��  : SCPERSTATUS2 �Ĵ����ṹ���塣��ַƫ����:0x224����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_a2_grp : 10; /* bit[0-9]  : ���Թܽ�
                                                     tcxoseq_finish0 AO�ܽ�-A2 A2_0
                                                     tcxoseq_finish1 AO�ܽ�-A2 A2_1
                                                     tcxo_timeout0 AO�ܽ�-A2 A2_2
                                                     tcxo_timeout1 AO�ܽ�-A2 A2_3
                                                     tcxoseq_stat0[0] AO�ܽ�-A4 A2 A4_0 A2_4
                                                     tcxoseq_stat0[1] AO�ܽ�-A4 A2 A4_0 A2_5
                                                     tcxoseq_stat0[2] AO�ܽ�-A4 A2 A4_0 A2_6
                                                     tcxoseq_stat1[0] AO�ܽ�-A4 A2 A4_0 A2_7
                                                     tcxoseq_stat1[1] AO�ܽ�-A4 A2 A4_0 A2_8
                                                     tcxoseq_stat1[2] AO�ܽ�-A4 A2 A4_0 A2_9�� */
        unsigned int  tp_a3_grp : 10; /* bit[10-19]: ���Թܽ�
                                                     sys_been_deepsleepde AO�ܽ�-A4 A3 A4_6 A3_0
                                                     sys_been_ltsleeped AO�ܽ�-A4 A3 A4_6 A3_1
                                                     intr_ao_wakeup0 AO�ܽ�-A4 A3 A4_6 A3_2
                                                     intr_ao_wakeup1 AO�ܽ�-A8 A3 A8_1 A3_3
                                                     intr_peri_wakeup AO�ܽ�-A8 A3 A8_8 A3_4�� */
        unsigned int  tp_a4_grp : 10; /* bit[20-29]: ���Թܽ�
                                                     ao_fll_tp[9:0] AO�ܽ�-A4 A4_0~9�� */
        unsigned int  reserved  : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERSTATUS2_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS2_tp_a2_grp_START  (0)
#define SOC_SCTRL_SCPERSTATUS2_tp_a2_grp_END    (9)
#define SOC_SCTRL_SCPERSTATUS2_tp_a3_grp_START  (10)
#define SOC_SCTRL_SCPERSTATUS2_tp_a3_grp_END    (19)
#define SOC_SCTRL_SCPERSTATUS2_tp_a4_grp_START  (20)
#define SOC_SCTRL_SCPERSTATUS2_tp_a4_grp_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS3_UNION
 �ṹ˵��  : SCPERSTATUS3 �Ĵ����ṹ���塣��ַƫ����:0x228����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_done : 32; /* bit[0-31]: ��bit��Ӧ1·MRB��
                                                      0����·MRB���ڸô�memory�޸������У�û������repair�� 
                                                      1����·MRB���ڸô�memory�޸������У�������repair�� */
    } reg;
} SOC_SCTRL_SCPERSTATUS3_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS3_repair_done_START  (0)
#define SOC_SCTRL_SCPERSTATUS3_repair_done_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS4_UNION
 �ṹ˵��  : SCPERSTATUS4 �Ĵ����ṹ���塣��ַƫ����:0x22C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbdrx_timeout_dbg_info : 32; /* bit[0-31]: bbdrx_timeout_dbg_info
                                                                 [22]:pready_s
                                                                 0:not ready 1:ready
                                                                 [21]:dbg_timeout
                                                                 0:not timeout 1:timeout
                                                                 [20]:dbg_pwrite
                                                                 0:read 1:write
                                                                 [19:0]:dbg_addr�� */
    } reg;
} SOC_SCTRL_SCPERSTATUS4_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS4_bbdrx_timeout_dbg_info_START  (0)
#define SOC_SCTRL_SCPERSTATUS4_bbdrx_timeout_dbg_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS5_UNION
 �ṹ˵��  : SCPERSTATUS5 �Ĵ����ṹ���塣��ַƫ����:0x230����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_a9_grp                               : 10; /* bit[0-9]  : ���Թܽţ����庬��ο�tp�����ĵ�
                                                                                   ppll0_lock AO�ܽ�-A9 A9_4
                                                                                   ppll0_en AO�ܽ�-A9 A9_5
                                                                                   xtal_sw_req AO�ܽ�-A9 A9_6
                                                                                   pll_sw_req AO�ܽ�-A9 A9_7
                                                                                   pll_sw_ack AO�ܽ�-A9 A9_8
                                                                                   reset_peri_n AO�ܽ�-A9 A9_9�� */
        unsigned int  tp_a10_grp                              : 10; /* bit[10-19]: ���Թܽţ����庬��ο�tp�����ĵ�
                                                                                   tp_iomcu[0] AO�ܽ�-A10 A10_0
                                                                                   tp_iomcu[1] AO�ܽ�-A10 A10_1
                                                                                   tp_iomcu[2] AO�ܽ�-A10 A10_2
                                                                                   tp_iomcu[3] AO�ܽ�-A10 A10_3
                                                                                   tp_iomcu[4] AO�ܽ�-A10 A10_4
                                                                                   tp_iomcu[5] AO�ܽ�-A10 A10_5
                                                                                   tp_iomcu[6] AO�ܽ�-A10 A10_6
                                                                                   tp_iomcu[7] AO�ܽ�-A10 A10_7
                                                                                   tp_iomcu[8] AO�ܽ�-A10 A10_8
                                                                                   tp_iomcu[9] AO�ܽ�-A10 A10_9�� */
        unsigned int  aomcu_ao_noc_mainstatalarm_int          : 1;  /* bit[20]   : aomcu_ao_noc_mainstatalarm_intĿǰδʹ�á� */
        unsigned int  aomcu_ao_noc_mainfault_int              : 1;  /* bit[21]   : aomcu_ao_noc_mainfault_intĿǰδʹ�á� */
        unsigned int  asp_transaction_probe_mainstatalarm_int : 1;  /* bit[22]   : asp_transaction_probe_mainstatalarm_int0:no int 1:int occur �� */
        unsigned int  asp_error_probe_observer_mainfault_int  : 1;  /* bit[23]   : asp_error_probe_observer_mainfault_intĿǰδʹ�á� */
        unsigned int  repair_start_point_err                  : 1;  /* bit[24]   : [0]:repair_start_point_err
                                                                                   ָʾ�����޸��Ƿ��״̬����idle̬��ʼ��
                                                                                   0���ǣ�
                                                                                   1���񣨷����޸��������󣩡� */
        unsigned int  pack_is0_err                            : 1;  /* bit[25]   : ָʾ�޸�ʱ��EFUSE/SRAM�����ݰ��Ƿ�ȫ0��
                                                                                   0����ȫ0��
                                                                                   1��ȫ0�����ݰ����󣩡� */
        unsigned int  repair_finish                           : 1;  /* bit[26]   : ָʾ�ô��޸������Ƿ���ɣ�
                                                                                   0���ô��޸�����û�н�����
                                                                                   1���ô��޸����̽����� */
        unsigned int  mdmcpu_dbgack                           : 1;  /* bit[27]   : modem dbgack
                                                                                   0��debug not acknowledged
                                                                                   1:debug acknowledged�� */
        unsigned int  cfg_ispa7_dbgen_dx                      : 4;  /* bit[28-31]: [31:28]:cfg_ispa7_dbgen_dx�� */
    } reg;
} SOC_SCTRL_SCPERSTATUS5_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS5_tp_a9_grp_START                                (0)
#define SOC_SCTRL_SCPERSTATUS5_tp_a9_grp_END                                  (9)
#define SOC_SCTRL_SCPERSTATUS5_tp_a10_grp_START                               (10)
#define SOC_SCTRL_SCPERSTATUS5_tp_a10_grp_END                                 (19)
#define SOC_SCTRL_SCPERSTATUS5_aomcu_ao_noc_mainstatalarm_int_START           (20)
#define SOC_SCTRL_SCPERSTATUS5_aomcu_ao_noc_mainstatalarm_int_END             (20)
#define SOC_SCTRL_SCPERSTATUS5_aomcu_ao_noc_mainfault_int_START               (21)
#define SOC_SCTRL_SCPERSTATUS5_aomcu_ao_noc_mainfault_int_END                 (21)
#define SOC_SCTRL_SCPERSTATUS5_asp_transaction_probe_mainstatalarm_int_START  (22)
#define SOC_SCTRL_SCPERSTATUS5_asp_transaction_probe_mainstatalarm_int_END    (22)
#define SOC_SCTRL_SCPERSTATUS5_asp_error_probe_observer_mainfault_int_START   (23)
#define SOC_SCTRL_SCPERSTATUS5_asp_error_probe_observer_mainfault_int_END     (23)
#define SOC_SCTRL_SCPERSTATUS5_repair_start_point_err_START                   (24)
#define SOC_SCTRL_SCPERSTATUS5_repair_start_point_err_END                     (24)
#define SOC_SCTRL_SCPERSTATUS5_pack_is0_err_START                             (25)
#define SOC_SCTRL_SCPERSTATUS5_pack_is0_err_END                               (25)
#define SOC_SCTRL_SCPERSTATUS5_repair_finish_START                            (26)
#define SOC_SCTRL_SCPERSTATUS5_repair_finish_END                              (26)
#define SOC_SCTRL_SCPERSTATUS5_mdmcpu_dbgack_START                            (27)
#define SOC_SCTRL_SCPERSTATUS5_mdmcpu_dbgack_END                              (27)
#define SOC_SCTRL_SCPERSTATUS5_cfg_ispa7_dbgen_dx_START                       (28)
#define SOC_SCTRL_SCPERSTATUS5_cfg_ispa7_dbgen_dx_END                         (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS6_UNION
 �ṹ˵��  : SCPERSTATUS6 �Ĵ����ṹ���塣��ַƫ����:0x234����ֵ:0x00020000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_stat6 : 32; /* bit[0-31]: other:reserved
                                                     [31:30]AO_BUS��ʱ���л� asp_aobus_clk_sw_req��not use
                                                     [29:28]MMBUF��ʱ���л� asp_mmbuf_clk_sw_req��not use
                                                     [27]AO_BUS��ʱ���ſ� asp_aobus_clk_en_req��1bit,1���� 0���رգ�not use
                                                     [26]MMBUF��ʱ���ſ� asp_mmbuf_clk_en_req��1bit,1���� 0���رգ�not use
                                                     [25]FLL�Ŀ��ؿ��� asp_fpll_en_req��1bit,1���� 0���رգ�not use
                                                     [24]PPLL0�Ŀ��ؿ��� asp_ppll0_en_req ��1bit,1���� 0���رգ�not use
                                                     [23:20]:cfg_mcu_dbgen_dx
                                                     ={spniden,spiden,niden,dbgen}
                                                     0:disable 1:enable
                                                     [19:16]:cfg_arm_dbgen_dx
                                                     ={spniden,spiden,niden,dbgen}
                                                     0:disable 1:enable
                                                     [14]sc_aonoc_asp_mst_i_mainnopendingtrans
                                                     0:trans 1:no pending trans
                                                     [13]sc_aobus_service_target_mainnopendingtrans
                                                     0:trans 1:no pending trans
                                                     [12]iomcu_power_idleack
                                                     0��not idle 1:idle
                                                     [11]iomcu_power_idle
                                                     0��not idle 1:idle
                                                     [10]iomcu_apb_slv_maintimeout
                                                     0��not timeout 1:timeout
                                                     [9]iomcu_ahb_slv_maintimeout
                                                     0��not timeout 1:timeout
                                                     [8]noc_asp_power_idleack
                                                     0��not idle 1:idle
                                                     [7]reserved
                                                     [6]������
                                                     [5]noc_asp_power_idle
                                                     0��not idle 1:idle
                                                     [4]reserved
                                                     [3]������
                                                     [2]noc_asp_cfg_t_maintimeout
                                                     0��not timeout 1:timeout
                                                     [1]reserved
                                                     [0]noc_aobus_mmbuf_t_maintimeout
                                                     0��not timeout 1:timeout�� */
    } reg;
} SOC_SCTRL_SCPERSTATUS6_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS6_peri_stat6_START  (0)
#define SOC_SCTRL_SCPERSTATUS6_peri_stat6_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS7_UNION
 �ṹ˵��  : SCPERSTATUS7 �Ĵ����ṹ���塣��ַƫ����:0x238����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_finish_flag : 32; /* bit[0-31]: ÿ1bit��Ӧ1·MRB��ָʾMRB�Ƿ��޸��޸����(û�������޸�Ҳ��Ϊ��һ���޸����)��
                                                             0����MRB�޸�û����ɣ�
                                                             1����MRB�޸���ɡ�
                                                             [31:19]ΪԤ��λ�� */
    } reg;
} SOC_SCTRL_SCPERSTATUS7_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS7_repair_finish_flag_START  (0)
#define SOC_SCTRL_SCPERSTATUS7_repair_finish_flag_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS8_UNION
 �ṹ˵��  : SCPERSTATUS8 �Ĵ����ṹ���塣��ַƫ����:0x23C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_data_err0 : 32; /* bit[0-31]: [2:0]->MRB0,[5:3]->MRB1,��,{repair_data_err1[0],[31:30]}->MRB10��ÿ�麬�壺
                                                           000������������
                                                           001�������յ�ѹ�����ݰ������յ��˷�ѹ�����ݰ���
                                                           010�������յ���ѹ�����ݰ������յ���ѹ�����ݰ���
                                                           011���յ������ݽ�ѹ��bit������С�ڶ�ӦMRB������bit�����ȣ�
                                                           100���յ������ݽ�ѹ��bit�����ȴ��ڶ�ӦMRB������bit�����ȣ�
                                                           101�����ݰ���[15:13]���Ȳ���3'b000��Ҳ����3'b001�� */
    } reg;
} SOC_SCTRL_SCPERSTATUS8_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS8_repair_data_err0_START  (0)
#define SOC_SCTRL_SCPERSTATUS8_repair_data_err0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS9_UNION
 �ṹ˵��  : SCPERSTATUS9 �Ĵ����ṹ���塣��ַƫ����:0x240����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���9��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_data_err1 : 32; /* bit[0-31]: [3:1]->MRB11,[6:4]->MRB12,��,[30:28]->MRB20��ÿ�麬�壺
                                                           000������������
                                                           001�������յ�ѹ�����ݰ������յ��˷�ѹ�����ݰ���
                                                           010�������յ���ѹ�����ݰ������յ���ѹ�����ݰ���
                                                           011���յ������ݽ�ѹ��bit������С�ڶ�ӦMRB������bit�����ȣ�
                                                           100���յ������ݽ�ѹ��bit�����ȴ��ڶ�ӦMRB������bit�����ȣ�
                                                           101�����ݰ���[15:13]���Ȳ���3'b000��Ҳ����3'b001�� */
    } reg;
} SOC_SCTRL_SCPERSTATUS9_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS9_repair_data_err1_START  (0)
#define SOC_SCTRL_SCPERSTATUS9_repair_data_err1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS10_UNION
 �ṹ˵��  : SCPERSTATUS10 �Ĵ����ṹ���塣��ַƫ����:0x244����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���10��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_data_err2 : 32; /* bit[0-31]: {[1:0],repair_data_err1[31]}->MRB21,[4:2]->MRB22,��,[31:29]->MRB31��ÿ�麬�壺
                                                           000������������
                                                           001�������յ�ѹ�����ݰ������յ��˷�ѹ�����ݰ���
                                                           010�������յ���ѹ�����ݰ������յ���ѹ�����ݰ���
                                                           011���յ������ݽ�ѹ��bit������С�ڶ�ӦMRB������bit�����ȣ�
                                                           100���յ������ݽ�ѹ��bit�����ȴ��ڶ�ӦMRB������bit�����ȣ�
                                                           101�����ݰ���[15:13]���Ȳ���3'b000��Ҳ����3'b001�� */
    } reg;
} SOC_SCTRL_SCPERSTATUS10_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS10_repair_data_err2_START  (0)
#define SOC_SCTRL_SCPERSTATUS10_repair_data_err2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS11_UNION
 �ṹ˵��  : SCPERSTATUS11 �Ĵ����ṹ���塣��ַƫ����:0x248����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���11��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mrb_need_repair : 32; /* bit[0-31]: ÿbit��Ӧ1·MRB��ָʾ��MRB�Ƿ������bit1(��MRB�л���)��
                                                          0��û�л��㣻
                                                          1���л��㡣 */
    } reg;
} SOC_SCTRL_SCPERSTATUS11_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS11_mrb_need_repair_START  (0)
#define SOC_SCTRL_SCPERSTATUS11_mrb_need_repair_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS12_UNION
 �ṹ˵��  : SCPERSTATUS12 �Ĵ����ṹ���塣��ַƫ����:0x24C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���12��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_disable_flag : 32; /* bit[0-31]: ûbit��Ӧ1·MRB��ָʾ��MRB�Ƿ���ʵ���������޸�(MRB0/1/2����Ӳ������)��
                                                              0�������޸���
                                                              1����ֹ�޸��� */
    } reg;
} SOC_SCTRL_SCPERSTATUS12_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS12_repair_disable_flag_START  (0)
#define SOC_SCTRL_SCPERSTATUS12_repair_disable_flag_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS13_UNION
 �ṹ˵��  : SCPERSTATUS13 �Ĵ����ṹ���塣��ַƫ����:0x250����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���13��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_hpm_opc      : 10; /* bit[0-9]  : ao HPMԭʼ�����롣 */
        unsigned int  ao_hpm_opc_vld  : 1;  /* bit[10]   : ao HPMԭʼ��������Ч��״ָ̬ʾ��
                                                           0:not valid 1:valid�� */
        unsigned int  reserved        : 1;  /* bit[11]   : ������ */
        unsigned int  ao_hpmx_opc     : 10; /* bit[12-21]: ao HPMXԭʼ�����롣 */
        unsigned int  ao_hpmx_opc_vld : 1;  /* bit[22]   : ao HPMXԭʼ��������Ч��״ָ̬ʾ��
                                                           0:not valid 1:valid�� */
        unsigned int  scperstatus13   : 9;  /* bit[23-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERSTATUS13_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS13_ao_hpm_opc_START       (0)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpm_opc_END         (9)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpm_opc_vld_START   (10)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpm_opc_vld_END     (10)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpmx_opc_START      (12)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpmx_opc_END        (21)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpmx_opc_vld_START  (22)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpmx_opc_vld_END    (22)
#define SOC_SCTRL_SCPERSTATUS13_scperstatus13_START    (23)
#define SOC_SCTRL_SCPERSTATUS13_scperstatus13_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERSTATUS14_UNION
 �ṹ˵��  : SCPERSTATUS14 �Ĵ����ṹ���塣��ַƫ����:0x254����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���14��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scperstatus14 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERSTATUS14_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS14_scperstatus14_START  (0)
#define SOC_SCTRL_SCPERSTATUS14_scperstatus14_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERCTRL7_UNION
 �ṹ˵��  : SCPERCTRL7 �Ĵ����ṹ���塣��ַƫ����:0x270����ֵ:0x0000000C�����:32
 �Ĵ���˵��: ������ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_mmbuf_pending_en                    : 1;  /* bit[0]    : clk_mmbuf��������pending�ź�sc_noc_aobus_idle_flag�Զ��ر�
                                                                                      0��disable
                                                                                      1��enable�� */
        unsigned int  reserved                                   : 1;  /* bit[1]    : ������ */
        unsigned int  noc_asp_power_idlereq                      : 1;  /* bit[2]    : noc_asp_power_idlereq 0:not req 1:idle req�� */
        unsigned int  iomcu_power_idlereq                        : 1;  /* bit[3]    : iomcu_power_idlereq 0:not req 1:idle req�� */
        unsigned int  aomcu_ao_noc_mainstatalarm_intmsk          : 1;  /* bit[4]    : aomcu_ao_noc_mainstatalarm_intmsk
                                                                                      0:int msk
                                                                                      1:int enable�� */
        unsigned int  aomcu_ao_noc_mainfault_intmsk              : 1;  /* bit[5]    : aomcu_ao_noc_mainfault_intmsk
                                                                                      0:int msk
                                                                                      1:int enable�� */
        unsigned int  asp_transaction_probe_mainstatalarm_intmsk : 1;  /* bit[6]    : asp_transaction_probe_mainstatalarm_intmsk
                                                                                      0:int msk
                                                                                      1:int enable�� */
        unsigned int  asp_error_probe_observer_mainfault_intmsk  : 1;  /* bit[7]    : asp_error_probe_observer_mainfault_intmsk
                                                                                      0:int msk
                                                                                      1:int enable�� */
        unsigned int  msk_noc_aobus_mmbuf_t_maintimeout          : 1;  /* bit[8]    : msk_noc_aobus_mmbuf_t_maintimeout
                                                                                      0:int msk
                                                                                      1:int enable�� */
        unsigned int  msk_noc_asp_cfg_t_maintimeout              : 1;  /* bit[9]    : msk_noc_asp_cfg_t_maintimeout
                                                                                      0:int msk
                                                                                      1:int enable�� */
        unsigned int  msk_iomcu_ahb_slv_maintimeout              : 1;  /* bit[10]   : msk_iomcu_ahb_slv_maintimeout
                                                                                      0:int msk
                                                                                      1:int enable�� */
        unsigned int  msk_iomcu_apb_slv_maintimeout              : 1;  /* bit[11]   : msk_iomcu_apb_slv_maintimeout
                                                                                      0:int msk
                                                                                      1:int enable�� */
        unsigned int  scperctrl7                                 : 4;  /* bit[12-15]: ������ */
        unsigned int  scperctrl7_msk                             : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                                                      ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_SCTRL_SCPERCTRL7_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL7_gt_clk_mmbuf_pending_en_START                     (0)
#define SOC_SCTRL_SCPERCTRL7_gt_clk_mmbuf_pending_en_END                       (0)
#define SOC_SCTRL_SCPERCTRL7_noc_asp_power_idlereq_START                       (2)
#define SOC_SCTRL_SCPERCTRL7_noc_asp_power_idlereq_END                         (2)
#define SOC_SCTRL_SCPERCTRL7_iomcu_power_idlereq_START                         (3)
#define SOC_SCTRL_SCPERCTRL7_iomcu_power_idlereq_END                           (3)
#define SOC_SCTRL_SCPERCTRL7_aomcu_ao_noc_mainstatalarm_intmsk_START           (4)
#define SOC_SCTRL_SCPERCTRL7_aomcu_ao_noc_mainstatalarm_intmsk_END             (4)
#define SOC_SCTRL_SCPERCTRL7_aomcu_ao_noc_mainfault_intmsk_START               (5)
#define SOC_SCTRL_SCPERCTRL7_aomcu_ao_noc_mainfault_intmsk_END                 (5)
#define SOC_SCTRL_SCPERCTRL7_asp_transaction_probe_mainstatalarm_intmsk_START  (6)
#define SOC_SCTRL_SCPERCTRL7_asp_transaction_probe_mainstatalarm_intmsk_END    (6)
#define SOC_SCTRL_SCPERCTRL7_asp_error_probe_observer_mainfault_intmsk_START   (7)
#define SOC_SCTRL_SCPERCTRL7_asp_error_probe_observer_mainfault_intmsk_END     (7)
#define SOC_SCTRL_SCPERCTRL7_msk_noc_aobus_mmbuf_t_maintimeout_START           (8)
#define SOC_SCTRL_SCPERCTRL7_msk_noc_aobus_mmbuf_t_maintimeout_END             (8)
#define SOC_SCTRL_SCPERCTRL7_msk_noc_asp_cfg_t_maintimeout_START               (9)
#define SOC_SCTRL_SCPERCTRL7_msk_noc_asp_cfg_t_maintimeout_END                 (9)
#define SOC_SCTRL_SCPERCTRL7_msk_iomcu_ahb_slv_maintimeout_START               (10)
#define SOC_SCTRL_SCPERCTRL7_msk_iomcu_ahb_slv_maintimeout_END                 (10)
#define SOC_SCTRL_SCPERCTRL7_msk_iomcu_apb_slv_maintimeout_START               (11)
#define SOC_SCTRL_SCPERCTRL7_msk_iomcu_apb_slv_maintimeout_END                 (11)
#define SOC_SCTRL_SCPERCTRL7_scperctrl7_START                                  (12)
#define SOC_SCTRL_SCPERCTRL7_scperctrl7_END                                    (15)
#define SOC_SCTRL_SCPERCTRL7_scperctrl7_msk_START                              (16)
#define SOC_SCTRL_SCPERCTRL7_scperctrl7_msk_END                                (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCINNERSTAT_UNION
 �ṹ˵��  : SCINNERSTAT �Ĵ����ṹ���塣��ַƫ����:0x280����ֵ:0x02E00000�����:32
 �Ĵ���˵��: �ڲ�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  memory_repair_bypass    : 1;  /* bit[0]    : Memory repair bypass�ź�״̬������efuse�� */
        unsigned int  hardw_ctrl_sel0         : 1;  /* bit[1]    : test_mode0�źž�������״̬�� */
        unsigned int  factest_mode            : 2;  /* bit[2-3]  : FACTEST_MODE[1:0]=
                                                                   2'b00: SYS EFUSE QA TEST
                                                                   2'b01: FAC_TEST�� */
        unsigned int  memory_repair_bypass_hw : 10; /* bit[4-13] : Memory repair bypass hardware�ź�״̬��������gpu��أ�����efuse�� */
        unsigned int  isp_face_detect_fuse    : 1;  /* bit[14]   : ISP�ڲ�����to control whether FD(face detect) works */
        unsigned int  reserved_0              : 1;  /* bit[15]   : ������ */
        unsigned int  ate_mode                : 3;  /* bit[16-18]: ATE_MODE[2:0]=
                                                                   3'b000 ABB TEST
                                                                   3'b001: Tsensor TEST
                                                                   3'b010: SYS EFUSE TEST
                                                                   3'b011: BISR EFUSE TEST
                                                                   3'b100: BOOT_MODE_NAND
                                                                   Other: ABB TEST�� */
        unsigned int  vote_clk_gt_sel_flag    : 7;  /* bit[19-25]: [25:24]:sel_clk_aobus_noc
                                                                   00��TCXO
                                                                   01��FPLL
                                                                   10��DDRPLL
                                                                   11: PPLL0
                                                                   ��������ֵ��iomcu��audio�ʹ�����λͶƱȷ�����������ܵȼ������ٲã�DDRPLL>PPLL0>FPLL>TCXO
                                                                   [23:22]:sel_clk_mmbuf
                                                                   mmbufʱ����Դѡ��
                                                                   00��TCXO
                                                                   01��FPLL
                                                                   1x: PPLL0
                                                                   ��������ֵ��iomcu��audio�ʹ�����λͶƱȷ�����������ܵȼ������ٲã�PPLL0>FPLL>TCXO
                                                                   [21]:gt_aobus_noc_ini
                                                                   aobus ppll0����ſ�
                                                                   0��ʱ�ӹرգ�
                                                                   1��ʱ�ӿ�����
                                                                   ��������ֵ��iomcu��audio�ʹ�����λͶƱȷ����������򿪾�ʱ�ӣ��������󶼹رղŹر�ʱ�ӣ�
                                                                   [20]:gt_pclk_mmbufcfg
                                                                   0��ʱ�ӹرգ�
                                                                   1��ʱ�ӿ�����
                                                                   ��������ֵ��iomcu��audio�ʹ�����λͶƱȷ����������򿪾�ʱ�ӣ��������󶼹رղŹر�ʱ�ӣ�
                                                                   [19]:gt_clk_mmbuf
                                                                   mmbuf pll��Ƶǰʱ���ſ����ã�
                                                                   0��ʱ�ӹرգ�
                                                                   1��ʱ�ӿ�����
                                                                   ��������ֵ��iomcu��audio�ʹ�����λͶƱȷ����������򿪾�ʱ�ӣ��������󶼹رղŹر�ʱ�ӡ� */
        unsigned int  reserved_1              : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_SCTRL_SCINNERSTAT_UNION;
#endif
#define SOC_SCTRL_SCINNERSTAT_memory_repair_bypass_START     (0)
#define SOC_SCTRL_SCINNERSTAT_memory_repair_bypass_END       (0)
#define SOC_SCTRL_SCINNERSTAT_hardw_ctrl_sel0_START          (1)
#define SOC_SCTRL_SCINNERSTAT_hardw_ctrl_sel0_END            (1)
#define SOC_SCTRL_SCINNERSTAT_factest_mode_START             (2)
#define SOC_SCTRL_SCINNERSTAT_factest_mode_END               (3)
#define SOC_SCTRL_SCINNERSTAT_memory_repair_bypass_hw_START  (4)
#define SOC_SCTRL_SCINNERSTAT_memory_repair_bypass_hw_END    (13)
#define SOC_SCTRL_SCINNERSTAT_isp_face_detect_fuse_START     (14)
#define SOC_SCTRL_SCINNERSTAT_isp_face_detect_fuse_END       (14)
#define SOC_SCTRL_SCINNERSTAT_ate_mode_START                 (16)
#define SOC_SCTRL_SCINNERSTAT_ate_mode_END                   (18)
#define SOC_SCTRL_SCINNERSTAT_vote_clk_gt_sel_flag_START     (19)
#define SOC_SCTRL_SCINNERSTAT_vote_clk_gt_sel_flag_END       (25)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCDEEPSLEEPED_UNION
 �ṹ˵��  : SCDEEPSLEEPED �Ĵ����ṹ���塣��ַƫ����:0x300����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ָʾϵͳ������������˯�ߵ�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  deepsleeped     : 1;  /* bit[0]    : ϵͳ�Ƿ��������������״̬����DEEP SLEEPģʽָʾλ��
                                                           0��ϵͳû�н����DEEP SLEEP״̬��
                                                           1��ϵͳ���������DEEP SLEEP״̬��û�б����塣
                                                           ���Ըñ���λд1�����λ��״̬����λֵ���� */
        unsigned int  reserved_0      : 3;  /* bit[1-3]  : ������ */
        unsigned int  sleeped         : 1;  /* bit[4]    : ϵͳ�Ƿ����������ϵͳ״̬���� SLEEPģʽָʾλ��
                                                           0��ϵͳû�н����SLEEP״̬��
                                                           1��ϵͳ���������SLEEP״̬��û�б����塣
                                                           ���Ըñ���λд1�����λ��״̬����λֵ���� */
        unsigned int  reserved_1      : 15; /* bit[5-19] : ������ */
        unsigned int  reserved_2      : 11; /* bit[20-30]: reserved_efuse0 
                                                           bit20:reserved��bit1987������coresight��deviceen�źŸ�λccs��bypass�����źţ�
                                                           0��deviceen�ź��޷���λccs
                                                           1��deviceen�źſ��Ը�λccs
                                                           bit30:usbphy�ο�ʱ��19.2MHzѡ��
                                                           0��ѡ��abb buffer���ʱ��
                                                           1��ѡ��ppll0���ʱ��
                                                           other:reserved�� */
        unsigned int  reserved_3      : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_SCTRL_SCDEEPSLEEPED_UNION;
#endif
#define SOC_SCTRL_SCDEEPSLEEPED_deepsleeped_START      (0)
#define SOC_SCTRL_SCDEEPSLEEPED_deepsleeped_END        (0)
#define SOC_SCTRL_SCDEEPSLEEPED_sleeped_START          (4)
#define SOC_SCTRL_SCDEEPSLEEPED_sleeped_END            (4)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCMRBBUSYSTAT_UNION
 �ṹ˵��  : SCMRBBUSYSTAT �Ĵ����ṹ���塣��ַƫ����:0x304����ֵ:0x00000000�����:32
 �Ĵ���˵��: MRB EFUSE BUSY״ָ̬ʾ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mrb_efuse_busy : 32; /* bit[0-31]: ����ָʾ����IP�Ƿ����mem repair:
                                                         0������ɣ�1����δ���
                                                         ����ָʾ����IP�Ƿ���Ҫ��mem repair:
                                                         0�����޸���1�����޸�
                                                         AO_SUBSYS MRB0
                                                         PERI_SUBSYS(����ֻ����LP_M3) MRB1
                                                         DEBUG_SEC_HSIC_PERI_SUBSYS MRB2
                                                         MODEM_SUBSYS MRB3
                                                         BBP_COM_TOP_PD MRB4
                                                         BBP_IRM_TOP_PD MRB5
                                                         A9_WRAP_PD MRB6
                                                         DSP_WRAP_PD MRB7
                                                         BBP_LTE_TOP_PD MRB8
                                                         A57_SUBSYS MRB9
                                                         A53_SUBSYS MRB10
                                                         AUDIO_SUBSYS MRB11
                                                         IOMUC_SUBSYS MRB12
                                                         MMBUF_SUBSYS MRB13
                                                         DSS MRB14
                                                         ISP_SUBSYS MRB15
                                                         IVP32_DSP_SUBSYS MRB16
                                                         VDEC MRB17
                                                         VENC MRB18
                                                         GPU_SUBSYS MRB19
                                                         BBP_CS_CORE MRB20�� */
    } reg;
} SOC_SCTRL_SCMRBBUSYSTAT_UNION;
#endif
#define SOC_SCTRL_SCMRBBUSYSTAT_mrb_efuse_busy_START  (0)
#define SOC_SCTRL_SCMRBBUSYSTAT_mrb_efuse_busy_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCSWADDR_UNION
 �ṹ˵��  : SCSWADDR �Ĵ����ṹ���塣��ַƫ����:0x308����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ڱ��������ڵ�ַ�ļĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  swaddr : 32; /* bit[0-31]: �����������ڵ�ַ�� */
    } reg;
} SOC_SCTRL_SCSWADDR_UNION;
#endif
#define SOC_SCTRL_SCSWADDR_swaddr_START  (0)
#define SOC_SCTRL_SCSWADDR_swaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCDDRADDR_UNION
 �ṹ˵��  : SCDDRADDR �Ĵ����ṹ���塣��ַƫ����:0x30C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ڱ���DDRѵ�����ݵĵ�ַ�ļĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddrtrainaddr : 32; /* bit[0-31]: ����DDRѵ�����ݵĵ�ַ�� */
    } reg;
} SOC_SCTRL_SCDDRADDR_UNION;
#endif
#define SOC_SCTRL_SCDDRADDR_ddrtrainaddr_START  (0)
#define SOC_SCTRL_SCDDRADDR_ddrtrainaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCDDRDATA_UNION
 �ṹ˵��  : SCDDRDATA �Ĵ����ṹ���塣��ַƫ����:0x310����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ڱ���DDRѵ�����ݵļĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddrtraindata : 32; /* bit[0-31]: ����DDR��ѵ�����ݡ� */
    } reg;
} SOC_SCTRL_SCDDRDATA_UNION;
#endif
#define SOC_SCTRL_SCDDRDATA_ddrtraindata_START  (0)
#define SOC_SCTRL_SCDDRDATA_ddrtraindata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA0_UNION
 �ṹ˵��  : SCBAKDATA0 �Ĵ����ṹ���塣��ַƫ����:0x314����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���0��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA0_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA0_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA0_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA1_UNION
 �ṹ˵��  : SCBAKDATA1 �Ĵ����ṹ���塣��ַƫ����:0x318����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���1��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA1_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA1_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA1_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA2_UNION
 �ṹ˵��  : SCBAKDATA2 �Ĵ����ṹ���塣��ַƫ����:0x31C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���2��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA2_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA2_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA2_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA3_UNION
 �ṹ˵��  : SCBAKDATA3 �Ĵ����ṹ���塣��ַƫ����:0x320����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���3��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA3_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA3_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA3_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA4_UNION
 �ṹ˵��  : SCBAKDATA4 �Ĵ����ṹ���塣��ַƫ����:0x324����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���4��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA4_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA4_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA4_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA5_UNION
 �ṹ˵��  : SCBAKDATA5 �Ĵ����ṹ���塣��ַƫ����:0x328����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���5��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA5_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA5_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA5_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA6_UNION
 �ṹ˵��  : SCBAKDATA6 �Ĵ����ṹ���塣��ַƫ����:0x32C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���6��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA6_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA6_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA6_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA7_UNION
 �ṹ˵��  : SCBAKDATA7 �Ĵ����ṹ���塣��ַƫ����:0x330����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���7��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA7_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA7_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA7_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA8_UNION
 �ṹ˵��  : SCBAKDATA8 �Ĵ����ṹ���塣��ַƫ����:0x334����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���8��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA8_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA8_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA8_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA9_UNION
 �ṹ˵��  : SCBAKDATA9 �Ĵ����ṹ���塣��ַƫ����:0x338����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���9��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���9��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA9_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA9_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA9_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA10_UNION
 �ṹ˵��  : SCBAKDATA10 �Ĵ����ṹ���塣��ַƫ����:0x33C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���10��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���10��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA10_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA10_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA10_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA11_UNION
 �ṹ˵��  : SCBAKDATA11 �Ĵ����ṹ���塣��ַƫ����:0x340����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���11��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���11��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA11_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA11_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA11_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA12_UNION
 �ṹ˵��  : SCBAKDATA12 �Ĵ����ṹ���塣��ַƫ����:0x344����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���12��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���12��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA12_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA12_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA12_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA13_UNION
 �ṹ˵��  : SCBAKDATA13 �Ĵ����ṹ���塣��ַƫ����:0x348����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���13��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���13��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA13_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA13_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA13_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA14_UNION
 �ṹ˵��  : SCBAKDATA14 �Ĵ����ṹ���塣��ַƫ����:0x34C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���14��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���14��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA14_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA14_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA14_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBAKDATA15_UNION
 �ṹ˵��  : SCBAKDATA15 �Ĵ����ṹ���塣��ַƫ����:0x350����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʹ�õĴ洢���ݼĴ���15��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: �����Ԥ�������ݼĴ���15��������ʱ���ݵĻ��档 */
    } reg;
} SOC_SCTRL_SCBAKDATA15_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA15_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA15_bakdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCINT_GATHER_STAT_UNION
 �ṹ˵��  : SCINT_GATHER_STAT �Ĵ����ṹ���塣��ַƫ����:0x450����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ۺϺ���ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_wakeup_sys : 1;  /* bit[0]   : 1���ж���Ч��
                                                         0���ж���Ч��
                                                         ע�����ж�״̬���Ѿ������ж���������֮���״̬�� */
        unsigned int  drx0_int       : 1;  /* bit[1]   : 1���ж���Ч��
                                                         0���ж���Ч��
                                                         ע�����ж�״̬���Ѿ������ж���������֮���״̬�� */
        unsigned int  drx1_int       : 1;  /* bit[2]   : 1���ж���Ч��
                                                         0���ж���Ч��
                                                         ע�����ж�״̬���Ѿ������ж���������֮���״̬�� */
        unsigned int  notdrx_int     : 1;  /* bit[3]   : 1���ж���Ч��
                                                         0���ж���Ч��
                                                         ע�����ж�״̬���Ѿ������ж���������֮���״̬�� */
        unsigned int  reserved       : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCINT_GATHER_STAT_UNION;
#endif
#define SOC_SCTRL_SCINT_GATHER_STAT_int_wakeup_sys_START  (0)
#define SOC_SCTRL_SCINT_GATHER_STAT_int_wakeup_sys_END    (0)
#define SOC_SCTRL_SCINT_GATHER_STAT_drx0_int_START        (1)
#define SOC_SCTRL_SCINT_GATHER_STAT_drx0_int_END          (1)
#define SOC_SCTRL_SCINT_GATHER_STAT_drx1_int_START        (2)
#define SOC_SCTRL_SCINT_GATHER_STAT_drx1_int_END          (2)
#define SOC_SCTRL_SCINT_GATHER_STAT_notdrx_int_START      (3)
#define SOC_SCTRL_SCINT_GATHER_STAT_notdrx_int_END        (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCINT_MASK_UNION
 �ṹ˵��  : SCINT_MASK �Ĵ����ṹ���塣��ַƫ����:0x454����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж��������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio_22_int             : 1;  /* bit[0] : �ж����μĴ�����
                                                                0��������Ч��
                                                                1��������Ч�� */
        unsigned int  gpio_23_int             : 1;  /* bit[1] : ����ͬbit0�� */
        unsigned int  gpio_24_int             : 1;  /* bit[2] : ����ͬbit0�� */
        unsigned int  gpio_25_int             : 1;  /* bit[3] : ����ͬbit0�� */
        unsigned int  gpio_26_int             : 1;  /* bit[4] : ����ͬbit0�� */
        unsigned int  gpio_27_int             : 1;  /* bit[5] : ����ͬbit0�� */
        unsigned int  rtc_int                 : 1;  /* bit[6] : ����ͬbit0�� */
        unsigned int  rtc1_int                : 1;  /* bit[7] : ����ͬbit0�� */
        unsigned int  timer00_int             : 1;  /* bit[8] : ����ͬbit0�� */
        unsigned int  timer01_int             : 1;  /* bit[9] : ����ͬbit0�� */
        unsigned int  timer10_int             : 1;  /* bit[10]: ����ͬbit0�� */
        unsigned int  timer11_int             : 1;  /* bit[11]: ����ͬbit0�� */
        unsigned int  timer20_int             : 1;  /* bit[12]: ����ͬbit0�� */
        unsigned int  timer21_int             : 1;  /* bit[13]: ����ͬbit0�� */
        unsigned int  timer30_int             : 1;  /* bit[14]: ����ͬbit0�� */
        unsigned int  timer31_int             : 1;  /* bit[15]: ����ͬbit0�� */
        unsigned int  timer40_int             : 1;  /* bit[16]: ����ͬbit0�� */
        unsigned int  timer41_int             : 1;  /* bit[17]: ����ͬbit0�� */
        unsigned int  timer50_int             : 1;  /* bit[18]: ����ͬbit0�� */
        unsigned int  timer51_int             : 1;  /* bit[19]: ����ͬbit0�� */
        unsigned int  timer60_int             : 1;  /* bit[20]: ����ͬbit0�� */
        unsigned int  timer61_int             : 1;  /* bit[21]: ����ͬbit0�� */
        unsigned int  timer70_int             : 1;  /* bit[22]: ����ͬbit0�� */
        unsigned int  timer71_int             : 1;  /* bit[23]: ����ͬbit0�� */
        unsigned int  timer80_int             : 1;  /* bit[24]: ����ͬbit0�� */
        unsigned int  timer81_int             : 1;  /* bit[25]: ����ͬbit0�� */
        unsigned int  intr_asp_ipc_arm        : 1;  /* bit[26]: ����ͬbit0�� */
        unsigned int  intr_asp_watchdog       : 1;  /* bit[27]: ����ͬbit0�� */
        unsigned int  intr_iomcu_wdog         : 1;  /* bit[28]: ����ͬbit0�� */
        unsigned int  intr_iomcu_gpio_comb    : 1;  /* bit[29]: ����IOMCU GPIO�жϻ��Ѿ����ϵͳ�� */
        unsigned int  intr_iomcu_gpio_comb_sc : 1;  /* bit[30]: ����IOMCU GPIO�жϻ���ϵͳ����bit 30Ϊ0��bit 29Ϊ1ʱ��ֻ���Ѿ���bit 30��29��Ϊ1ʱ��Ϊһ�㻽���жϡ� */
        unsigned int  intr_wakeup_iomcu       : 1;  /* bit[31]: ����ͬbit0�� */
    } reg;
} SOC_SCTRL_SCINT_MASK_UNION;
#endif
#define SOC_SCTRL_SCINT_MASK_gpio_22_int_START              (0)
#define SOC_SCTRL_SCINT_MASK_gpio_22_int_END                (0)
#define SOC_SCTRL_SCINT_MASK_gpio_23_int_START              (1)
#define SOC_SCTRL_SCINT_MASK_gpio_23_int_END                (1)
#define SOC_SCTRL_SCINT_MASK_gpio_24_int_START              (2)
#define SOC_SCTRL_SCINT_MASK_gpio_24_int_END                (2)
#define SOC_SCTRL_SCINT_MASK_gpio_25_int_START              (3)
#define SOC_SCTRL_SCINT_MASK_gpio_25_int_END                (3)
#define SOC_SCTRL_SCINT_MASK_gpio_26_int_START              (4)
#define SOC_SCTRL_SCINT_MASK_gpio_26_int_END                (4)
#define SOC_SCTRL_SCINT_MASK_gpio_27_int_START              (5)
#define SOC_SCTRL_SCINT_MASK_gpio_27_int_END                (5)
#define SOC_SCTRL_SCINT_MASK_rtc_int_START                  (6)
#define SOC_SCTRL_SCINT_MASK_rtc_int_END                    (6)
#define SOC_SCTRL_SCINT_MASK_rtc1_int_START                 (7)
#define SOC_SCTRL_SCINT_MASK_rtc1_int_END                   (7)
#define SOC_SCTRL_SCINT_MASK_timer00_int_START              (8)
#define SOC_SCTRL_SCINT_MASK_timer00_int_END                (8)
#define SOC_SCTRL_SCINT_MASK_timer01_int_START              (9)
#define SOC_SCTRL_SCINT_MASK_timer01_int_END                (9)
#define SOC_SCTRL_SCINT_MASK_timer10_int_START              (10)
#define SOC_SCTRL_SCINT_MASK_timer10_int_END                (10)
#define SOC_SCTRL_SCINT_MASK_timer11_int_START              (11)
#define SOC_SCTRL_SCINT_MASK_timer11_int_END                (11)
#define SOC_SCTRL_SCINT_MASK_timer20_int_START              (12)
#define SOC_SCTRL_SCINT_MASK_timer20_int_END                (12)
#define SOC_SCTRL_SCINT_MASK_timer21_int_START              (13)
#define SOC_SCTRL_SCINT_MASK_timer21_int_END                (13)
#define SOC_SCTRL_SCINT_MASK_timer30_int_START              (14)
#define SOC_SCTRL_SCINT_MASK_timer30_int_END                (14)
#define SOC_SCTRL_SCINT_MASK_timer31_int_START              (15)
#define SOC_SCTRL_SCINT_MASK_timer31_int_END                (15)
#define SOC_SCTRL_SCINT_MASK_timer40_int_START              (16)
#define SOC_SCTRL_SCINT_MASK_timer40_int_END                (16)
#define SOC_SCTRL_SCINT_MASK_timer41_int_START              (17)
#define SOC_SCTRL_SCINT_MASK_timer41_int_END                (17)
#define SOC_SCTRL_SCINT_MASK_timer50_int_START              (18)
#define SOC_SCTRL_SCINT_MASK_timer50_int_END                (18)
#define SOC_SCTRL_SCINT_MASK_timer51_int_START              (19)
#define SOC_SCTRL_SCINT_MASK_timer51_int_END                (19)
#define SOC_SCTRL_SCINT_MASK_timer60_int_START              (20)
#define SOC_SCTRL_SCINT_MASK_timer60_int_END                (20)
#define SOC_SCTRL_SCINT_MASK_timer61_int_START              (21)
#define SOC_SCTRL_SCINT_MASK_timer61_int_END                (21)
#define SOC_SCTRL_SCINT_MASK_timer70_int_START              (22)
#define SOC_SCTRL_SCINT_MASK_timer70_int_END                (22)
#define SOC_SCTRL_SCINT_MASK_timer71_int_START              (23)
#define SOC_SCTRL_SCINT_MASK_timer71_int_END                (23)
#define SOC_SCTRL_SCINT_MASK_timer80_int_START              (24)
#define SOC_SCTRL_SCINT_MASK_timer80_int_END                (24)
#define SOC_SCTRL_SCINT_MASK_timer81_int_START              (25)
#define SOC_SCTRL_SCINT_MASK_timer81_int_END                (25)
#define SOC_SCTRL_SCINT_MASK_intr_asp_ipc_arm_START         (26)
#define SOC_SCTRL_SCINT_MASK_intr_asp_ipc_arm_END           (26)
#define SOC_SCTRL_SCINT_MASK_intr_asp_watchdog_START        (27)
#define SOC_SCTRL_SCINT_MASK_intr_asp_watchdog_END          (27)
#define SOC_SCTRL_SCINT_MASK_intr_iomcu_wdog_START          (28)
#define SOC_SCTRL_SCINT_MASK_intr_iomcu_wdog_END            (28)
#define SOC_SCTRL_SCINT_MASK_intr_iomcu_gpio_comb_START     (29)
#define SOC_SCTRL_SCINT_MASK_intr_iomcu_gpio_comb_END       (29)
#define SOC_SCTRL_SCINT_MASK_intr_iomcu_gpio_comb_sc_START  (30)
#define SOC_SCTRL_SCINT_MASK_intr_iomcu_gpio_comb_sc_END    (30)
#define SOC_SCTRL_SCINT_MASK_intr_wakeup_iomcu_START        (31)
#define SOC_SCTRL_SCINT_MASK_intr_wakeup_iomcu_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCINT_STAT_UNION
 �ṹ˵��  : SCINT_STAT �Ĵ����ṹ���塣��ַƫ����:0x458����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio_22_int          : 1;  /* bit[0] : �ж�״̬�Ĵ�����
                                                             0���ж���Ч��
                                                             1���ж���Ч�� */
        unsigned int  gpio_23_int          : 1;  /* bit[1] : ����ͬbit0�� */
        unsigned int  gpio_24_int          : 1;  /* bit[2] : ����ͬbit0�� */
        unsigned int  gpio_25_int          : 1;  /* bit[3] : ����ͬbit0�� */
        unsigned int  gpio_26_int          : 1;  /* bit[4] : ����ͬbit0�� */
        unsigned int  gpio_27_int          : 1;  /* bit[5] : ����ͬbit0�� */
        unsigned int  rtc_int              : 1;  /* bit[6] : ����ͬbit0�� */
        unsigned int  rtc1_int             : 1;  /* bit[7] : ����ͬbit0�� */
        unsigned int  timer00_int          : 1;  /* bit[8] : ����ͬbit0�� */
        unsigned int  timer01_int          : 1;  /* bit[9] : ����ͬbit0�� */
        unsigned int  timer10_int          : 1;  /* bit[10]: ����ͬbit0�� */
        unsigned int  timer11_int          : 1;  /* bit[11]: ����ͬbit0�� */
        unsigned int  timer20_int          : 1;  /* bit[12]: ����ͬbit0�� */
        unsigned int  timer21_int          : 1;  /* bit[13]: ����ͬbit0�� */
        unsigned int  timer30_int          : 1;  /* bit[14]: ����ͬbit0�� */
        unsigned int  timer31_int          : 1;  /* bit[15]: ����ͬbit0�� */
        unsigned int  timer40_int          : 1;  /* bit[16]: ����ͬbit0�� */
        unsigned int  timer41_int          : 1;  /* bit[17]: ����ͬbit0�� */
        unsigned int  timer50_int          : 1;  /* bit[18]: ����ͬbit0�� */
        unsigned int  timer51_int          : 1;  /* bit[19]: ����ͬbit0�� */
        unsigned int  timer60_int          : 1;  /* bit[20]: ����ͬbit0�� */
        unsigned int  timer61_int          : 1;  /* bit[21]: ����ͬbit0�� */
        unsigned int  timer70_int          : 1;  /* bit[22]: ����ͬbit0�� */
        unsigned int  timer71_int          : 1;  /* bit[23]: ����ͬbit0�� */
        unsigned int  timer80_int          : 1;  /* bit[24]: ����ͬbit0�� */
        unsigned int  timer81_int          : 1;  /* bit[25]: ����ͬbit0�� */
        unsigned int  intr_asp_ipc_arm     : 1;  /* bit[26]: ����ͬbit0�� */
        unsigned int  intr_asp_watchdog    : 1;  /* bit[27]: ����ͬbit0�� */
        unsigned int  intr_iomcu_wdog      : 1;  /* bit[28]: ����ͬbit0�� */
        unsigned int  intr_iomcu_gpio_comb : 1;  /* bit[29]: ����ͬbit0�� */
        unsigned int  intr_wakeup_iomcu    : 1;  /* bit[30]: ����ͬbit0�� */
        unsigned int  reserved             : 1;  /* bit[31]: ������ */
    } reg;
} SOC_SCTRL_SCINT_STAT_UNION;
#endif
#define SOC_SCTRL_SCINT_STAT_gpio_22_int_START           (0)
#define SOC_SCTRL_SCINT_STAT_gpio_22_int_END             (0)
#define SOC_SCTRL_SCINT_STAT_gpio_23_int_START           (1)
#define SOC_SCTRL_SCINT_STAT_gpio_23_int_END             (1)
#define SOC_SCTRL_SCINT_STAT_gpio_24_int_START           (2)
#define SOC_SCTRL_SCINT_STAT_gpio_24_int_END             (2)
#define SOC_SCTRL_SCINT_STAT_gpio_25_int_START           (3)
#define SOC_SCTRL_SCINT_STAT_gpio_25_int_END             (3)
#define SOC_SCTRL_SCINT_STAT_gpio_26_int_START           (4)
#define SOC_SCTRL_SCINT_STAT_gpio_26_int_END             (4)
#define SOC_SCTRL_SCINT_STAT_gpio_27_int_START           (5)
#define SOC_SCTRL_SCINT_STAT_gpio_27_int_END             (5)
#define SOC_SCTRL_SCINT_STAT_rtc_int_START               (6)
#define SOC_SCTRL_SCINT_STAT_rtc_int_END                 (6)
#define SOC_SCTRL_SCINT_STAT_rtc1_int_START              (7)
#define SOC_SCTRL_SCINT_STAT_rtc1_int_END                (7)
#define SOC_SCTRL_SCINT_STAT_timer00_int_START           (8)
#define SOC_SCTRL_SCINT_STAT_timer00_int_END             (8)
#define SOC_SCTRL_SCINT_STAT_timer01_int_START           (9)
#define SOC_SCTRL_SCINT_STAT_timer01_int_END             (9)
#define SOC_SCTRL_SCINT_STAT_timer10_int_START           (10)
#define SOC_SCTRL_SCINT_STAT_timer10_int_END             (10)
#define SOC_SCTRL_SCINT_STAT_timer11_int_START           (11)
#define SOC_SCTRL_SCINT_STAT_timer11_int_END             (11)
#define SOC_SCTRL_SCINT_STAT_timer20_int_START           (12)
#define SOC_SCTRL_SCINT_STAT_timer20_int_END             (12)
#define SOC_SCTRL_SCINT_STAT_timer21_int_START           (13)
#define SOC_SCTRL_SCINT_STAT_timer21_int_END             (13)
#define SOC_SCTRL_SCINT_STAT_timer30_int_START           (14)
#define SOC_SCTRL_SCINT_STAT_timer30_int_END             (14)
#define SOC_SCTRL_SCINT_STAT_timer31_int_START           (15)
#define SOC_SCTRL_SCINT_STAT_timer31_int_END             (15)
#define SOC_SCTRL_SCINT_STAT_timer40_int_START           (16)
#define SOC_SCTRL_SCINT_STAT_timer40_int_END             (16)
#define SOC_SCTRL_SCINT_STAT_timer41_int_START           (17)
#define SOC_SCTRL_SCINT_STAT_timer41_int_END             (17)
#define SOC_SCTRL_SCINT_STAT_timer50_int_START           (18)
#define SOC_SCTRL_SCINT_STAT_timer50_int_END             (18)
#define SOC_SCTRL_SCINT_STAT_timer51_int_START           (19)
#define SOC_SCTRL_SCINT_STAT_timer51_int_END             (19)
#define SOC_SCTRL_SCINT_STAT_timer60_int_START           (20)
#define SOC_SCTRL_SCINT_STAT_timer60_int_END             (20)
#define SOC_SCTRL_SCINT_STAT_timer61_int_START           (21)
#define SOC_SCTRL_SCINT_STAT_timer61_int_END             (21)
#define SOC_SCTRL_SCINT_STAT_timer70_int_START           (22)
#define SOC_SCTRL_SCINT_STAT_timer70_int_END             (22)
#define SOC_SCTRL_SCINT_STAT_timer71_int_START           (23)
#define SOC_SCTRL_SCINT_STAT_timer71_int_END             (23)
#define SOC_SCTRL_SCINT_STAT_timer80_int_START           (24)
#define SOC_SCTRL_SCINT_STAT_timer80_int_END             (24)
#define SOC_SCTRL_SCINT_STAT_timer81_int_START           (25)
#define SOC_SCTRL_SCINT_STAT_timer81_int_END             (25)
#define SOC_SCTRL_SCINT_STAT_intr_asp_ipc_arm_START      (26)
#define SOC_SCTRL_SCINT_STAT_intr_asp_ipc_arm_END        (26)
#define SOC_SCTRL_SCINT_STAT_intr_asp_watchdog_START     (27)
#define SOC_SCTRL_SCINT_STAT_intr_asp_watchdog_END       (27)
#define SOC_SCTRL_SCINT_STAT_intr_iomcu_wdog_START       (28)
#define SOC_SCTRL_SCINT_STAT_intr_iomcu_wdog_END         (28)
#define SOC_SCTRL_SCINT_STAT_intr_iomcu_gpio_comb_START  (29)
#define SOC_SCTRL_SCINT_STAT_intr_iomcu_gpio_comb_END    (29)
#define SOC_SCTRL_SCINT_STAT_intr_wakeup_iomcu_START     (30)
#define SOC_SCTRL_SCINT_STAT_intr_wakeup_iomcu_END       (30)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCDRX_INT_CFG_UNION
 �ṹ˵��  : SCDRX_INT_CFG �Ĵ����ṹ���塣��ַƫ����:0x45C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DRX�жϷ������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drx0_int             : 1;  /* bit[0]   : ldrx2arm_wakeup_int
                                                               �ж����üĴ�����
                                                               0������DRX0���жϣ�
                                                               1������DRX1���жϡ� */
        unsigned int  drx1_int             : 1;  /* bit[1]   : tdrx2arm_wakeup_int������ͬbit0�� */
        unsigned int  drx2_int             : 1;  /* bit[2]   : g1_int_bbp_to_cpu_32k������ͬbit0�� */
        unsigned int  drx3_int             : 1;  /* bit[3]   : g2_int_bbp_to_cpu_32k������ͬbit0�� */
        unsigned int  drx4_int             : 1;  /* bit[4]   : intr_wbbp_arm_int02������ͬbit0�� */
        unsigned int  intr_iomcu_gpio_comb : 1;  /* bit[5]   : intr_iomcu_gpio_comb������ͬbit0�� */
        unsigned int  drx5_int             : 1;  /* bit[6]   : intr_cbbp_int01������ͬbit0�� */
        unsigned int  reserved_0           : 1;  /* bit[7]   : ������ */
        unsigned int  reserved_1           : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_SCTRL_SCDRX_INT_CFG_UNION;
#endif
#define SOC_SCTRL_SCDRX_INT_CFG_drx0_int_START              (0)
#define SOC_SCTRL_SCDRX_INT_CFG_drx0_int_END                (0)
#define SOC_SCTRL_SCDRX_INT_CFG_drx1_int_START              (1)
#define SOC_SCTRL_SCDRX_INT_CFG_drx1_int_END                (1)
#define SOC_SCTRL_SCDRX_INT_CFG_drx2_int_START              (2)
#define SOC_SCTRL_SCDRX_INT_CFG_drx2_int_END                (2)
#define SOC_SCTRL_SCDRX_INT_CFG_drx3_int_START              (3)
#define SOC_SCTRL_SCDRX_INT_CFG_drx3_int_END                (3)
#define SOC_SCTRL_SCDRX_INT_CFG_drx4_int_START              (4)
#define SOC_SCTRL_SCDRX_INT_CFG_drx4_int_END                (4)
#define SOC_SCTRL_SCDRX_INT_CFG_intr_iomcu_gpio_comb_START  (5)
#define SOC_SCTRL_SCDRX_INT_CFG_intr_iomcu_gpio_comb_END    (5)
#define SOC_SCTRL_SCDRX_INT_CFG_drx5_int_START              (6)
#define SOC_SCTRL_SCDRX_INT_CFG_drx5_int_END                (6)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCLPMCUWFI_INT_UNION
 �ṹ˵��  : SCLPMCUWFI_INT �Ĵ����ṹ���塣��ַƫ����:0x460����ֵ:0x00000000�����:32
 �Ĵ���˵��: LPMCU WFI�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpmcu_wfi_int : 1;  /* bit[0]   : д�������LPMCU_wfi_int�жϣ�
                                                        ����������LPMCU_wfi_int�ж�״̬�� */
        unsigned int  reserved      : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCLPMCUWFI_INT_UNION;
#endif
#define SOC_SCTRL_SCLPMCUWFI_INT_lpmcu_wfi_int_START  (0)
#define SOC_SCTRL_SCLPMCUWFI_INT_lpmcu_wfi_int_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCINT_MASK1_UNION
 �ṹ˵��  : SCINT_MASK1 �Ĵ����ṹ���塣��ַƫ����:0x464����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж��������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drx0_int : 1;  /* bit[0]   : �ж����μĴ�����
                                                   0��������Ч��
                                                   1��������Ч�� */
        unsigned int  drx1_int : 1;  /* bit[1]   : ����ͬbit0�� */
        unsigned int  drx2_int : 1;  /* bit[2]   : ����ͬbit0�� */
        unsigned int  drx3_int : 1;  /* bit[3]   : ����ͬbit0�� */
        unsigned int  drx4_int : 1;  /* bit[4]   : ����ͬbit0�� */
        unsigned int  drx5_int : 1;  /* bit[5]   : ����ͬbit0�� */
        unsigned int  reserved_0: 1;  /* bit[6]   : ������ */
        unsigned int  reserved_1: 25; /* bit[7-31]: ������ */
    } reg;
} SOC_SCTRL_SCINT_MASK1_UNION;
#endif
#define SOC_SCTRL_SCINT_MASK1_drx0_int_START  (0)
#define SOC_SCTRL_SCINT_MASK1_drx0_int_END    (0)
#define SOC_SCTRL_SCINT_MASK1_drx1_int_START  (1)
#define SOC_SCTRL_SCINT_MASK1_drx1_int_END    (1)
#define SOC_SCTRL_SCINT_MASK1_drx2_int_START  (2)
#define SOC_SCTRL_SCINT_MASK1_drx2_int_END    (2)
#define SOC_SCTRL_SCINT_MASK1_drx3_int_START  (3)
#define SOC_SCTRL_SCINT_MASK1_drx3_int_END    (3)
#define SOC_SCTRL_SCINT_MASK1_drx4_int_START  (4)
#define SOC_SCTRL_SCINT_MASK1_drx4_int_END    (4)
#define SOC_SCTRL_SCINT_MASK1_drx5_int_START  (5)
#define SOC_SCTRL_SCINT_MASK1_drx5_int_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCINT_STAT1_UNION
 �ṹ˵��  : SCINT_STAT1 �Ĵ����ṹ���塣��ַƫ����:0x468����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drx0_int : 1;  /* bit[0]   : ldrx2arm_wakeup_int
                                                   �ж�״̬�Ĵ�����
                                                   0���ж���Ч��
                                                   1���ж���Ч�� */
        unsigned int  drx1_int : 1;  /* bit[1]   : tdrx2arm_wakeup_int������ͬbit0�� */
        unsigned int  drx2_int : 1;  /* bit[2]   : g1_int_bbp_to_cpu_32k������ͬbit0�� */
        unsigned int  drx3_int : 1;  /* bit[3]   : g2_int_bbp_to_cpu_32k������ͬbit0 */
        unsigned int  drx4_int : 1;  /* bit[4]   : intr_wbbp_arm_int02������ͬbit0�� */
        unsigned int  drx5_int : 1;  /* bit[5]   : intr_cbbp_int01������ͬbit0�� */
        unsigned int  reserved_0: 1;  /* bit[6]   : ������ */
        unsigned int  reserved_1: 25; /* bit[7-31]: ������ */
    } reg;
} SOC_SCTRL_SCINT_STAT1_UNION;
#endif
#define SOC_SCTRL_SCINT_STAT1_drx0_int_START  (0)
#define SOC_SCTRL_SCINT_STAT1_drx0_int_END    (0)
#define SOC_SCTRL_SCINT_STAT1_drx1_int_START  (1)
#define SOC_SCTRL_SCINT_STAT1_drx1_int_END    (1)
#define SOC_SCTRL_SCINT_STAT1_drx2_int_START  (2)
#define SOC_SCTRL_SCINT_STAT1_drx2_int_END    (2)
#define SOC_SCTRL_SCINT_STAT1_drx3_int_START  (3)
#define SOC_SCTRL_SCINT_STAT1_drx3_int_END    (3)
#define SOC_SCTRL_SCINT_STAT1_drx4_int_START  (4)
#define SOC_SCTRL_SCINT_STAT1_drx4_int_END    (4)
#define SOC_SCTRL_SCINT_STAT1_drx5_int_START  (5)
#define SOC_SCTRL_SCINT_STAT1_drx5_int_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCINT_MASK2_UNION
 �ṹ˵��  : SCINT_MASK2 �Ĵ����ṹ���塣��ַƫ����:0x46C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж��������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gic_irq_int0       : 1;  /* bit[0]   : �ж����μĴ�����
                                                             0��������Ч��
                                                             1��������Ч�� */
        unsigned int  gic_irq_int1       : 1;  /* bit[1]   : ����ͬbit0�� */
        unsigned int  gic_fiq_int2       : 1;  /* bit[2]   : ����ͬbit0�� */
        unsigned int  gic_fiq_int3       : 1;  /* bit[3]   : ����ͬbit0�� */
        unsigned int  intr_lpmcu_wdog    : 1;  /* bit[4]   : ����ͬbit0�� */
        unsigned int  lpmcu_wfi_int      : 1;  /* bit[5]   : ����ͬbit0�� */
        unsigned int  clk_monitor_intmsk : 1;  /* bit[6]   : ����ͬbit0�� */
        unsigned int  reserved           : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_SCTRL_SCINT_MASK2_UNION;
#endif
#define SOC_SCTRL_SCINT_MASK2_gic_irq_int0_START        (0)
#define SOC_SCTRL_SCINT_MASK2_gic_irq_int0_END          (0)
#define SOC_SCTRL_SCINT_MASK2_gic_irq_int1_START        (1)
#define SOC_SCTRL_SCINT_MASK2_gic_irq_int1_END          (1)
#define SOC_SCTRL_SCINT_MASK2_gic_fiq_int2_START        (2)
#define SOC_SCTRL_SCINT_MASK2_gic_fiq_int2_END          (2)
#define SOC_SCTRL_SCINT_MASK2_gic_fiq_int3_START        (3)
#define SOC_SCTRL_SCINT_MASK2_gic_fiq_int3_END          (3)
#define SOC_SCTRL_SCINT_MASK2_intr_lpmcu_wdog_START     (4)
#define SOC_SCTRL_SCINT_MASK2_intr_lpmcu_wdog_END       (4)
#define SOC_SCTRL_SCINT_MASK2_lpmcu_wfi_int_START       (5)
#define SOC_SCTRL_SCINT_MASK2_lpmcu_wfi_int_END         (5)
#define SOC_SCTRL_SCINT_MASK2_clk_monitor_intmsk_START  (6)
#define SOC_SCTRL_SCINT_MASK2_clk_monitor_intmsk_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCINT_STAT2_UNION
 �ṹ˵��  : SCINT_STAT2 �Ĵ����ṹ���塣��ַƫ����:0x470����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gic_irq_int0     : 1;  /* bit[0]   : �ж�״̬�Ĵ�����
                                                           0���ж���Ч��
                                                           1���ж���Ч�� */
        unsigned int  gic_irq_int1     : 1;  /* bit[1]   : ����ͬbit0�� */
        unsigned int  gic_fiq_int0     : 1;  /* bit[2]   : ����ͬbit0�� */
        unsigned int  gic_fiq_int1     : 1;  /* bit[3]   : ����ͬbit0�� */
        unsigned int  intr_lpmcu_wdog  : 1;  /* bit[4]   : ����ͬbit0�� */
        unsigned int  clk_monitor_intr : 1;  /* bit[5]   : ����ͬbit0�� */
        unsigned int  reserved         : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_SCTRL_SCINT_STAT2_UNION;
#endif
#define SOC_SCTRL_SCINT_STAT2_gic_irq_int0_START      (0)
#define SOC_SCTRL_SCINT_STAT2_gic_irq_int0_END        (0)
#define SOC_SCTRL_SCINT_STAT2_gic_irq_int1_START      (1)
#define SOC_SCTRL_SCINT_STAT2_gic_irq_int1_END        (1)
#define SOC_SCTRL_SCINT_STAT2_gic_fiq_int0_START      (2)
#define SOC_SCTRL_SCINT_STAT2_gic_fiq_int0_END        (2)
#define SOC_SCTRL_SCINT_STAT2_gic_fiq_int1_START      (3)
#define SOC_SCTRL_SCINT_STAT2_gic_fiq_int1_END        (3)
#define SOC_SCTRL_SCINT_STAT2_intr_lpmcu_wdog_START   (4)
#define SOC_SCTRL_SCINT_STAT2_intr_lpmcu_wdog_END     (4)
#define SOC_SCTRL_SCINT_STAT2_clk_monitor_intr_START  (5)
#define SOC_SCTRL_SCINT_STAT2_clk_monitor_intr_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCMALIBYPCFG_UNION
 �ṹ˵��  : SCMALIBYPCFG �Ĵ����ṹ���塣��ַƫ����:0x48C����ֵ:0x00000001�����:32
 �Ĵ���˵��: MALI DBGACK BYPASS���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mali_dbgack_byp : 1;  /* bit[0]   : 0��bypass��Ч��
                                                          1��bypass��Ч�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCMALIBYPCFG_UNION;
#endif
#define SOC_SCTRL_SCMALIBYPCFG_mali_dbgack_byp_START  (0)
#define SOC_SCTRL_SCMALIBYPCFG_mali_dbgack_byp_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCLPMCUCLKEN_UNION
 �ṹ˵��  : SCLPMCUCLKEN �Ĵ����ṹ���塣��ַƫ����:0x500����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: LPMCU��ϵͳʱ��ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dapclkoff_sys_n        : 1;  /* bit[0]    : M3 DAPCLKʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  ssi1_clk_clkoff_sys_n  : 1;  /* bit[1]    : PMU_SSI1��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  rom_clk_clkoff_sys_n   : 1;  /* bit[2]    : BOOTROM��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  ram_clk_clkoff_sys_n   : 1;  /* bit[3]    : LP_RAM��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  aon_clk_clkoff_sys_n   : 1;  /* bit[4]    : AON_SUBSYS���ʽӿڵ�ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  ddrc_clk_clkoff_sys_n  : 1;  /* bit[5]    : DDRC���ýӿڵ�ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  tsen_clk_clkoff_sys_n  : 1;  /* bit[6]    : TSENSORC��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  pmc_clk_clkoff_sys_n   : 1;  /* bit[7]    : PMC��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  uart_clk_clkoff_sys_n  : 1;  /* bit[8]    : UART��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  i2c_clk_clkoff_sys_n   : 1;  /* bit[9]    : PMU_I2C��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  ssi_clk_clkoff_sys_n   : 1;  /* bit[10]   : PMU_SSI��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  pcrg_clk_clkoff_sys_n  : 1;  /* bit[11]   : ����CRG���ýӿڵ�ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  nandc_clk_clkoff_sys_n : 1;  /* bit[12]   : NANDC��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  wdog_clk_clkoff_sys_n  : 1;  /* bit[13]   : LP_WDG��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  tim_clk_clkoff_sys_n   : 1;  /* bit[14]   : LP_TIMER��ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  cssys_clk_clkoff_sys_n : 1;  /* bit[15]   : CSSYS���ʽӿڵ�ʱ���ſ�ϵͳ���ơ�0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  sclpmcuclken_msk       : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                                  ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_SCTRL_SCLPMCUCLKEN_UNION;
#endif
#define SOC_SCTRL_SCLPMCUCLKEN_dapclkoff_sys_n_START         (0)
#define SOC_SCTRL_SCLPMCUCLKEN_dapclkoff_sys_n_END           (0)
#define SOC_SCTRL_SCLPMCUCLKEN_ssi1_clk_clkoff_sys_n_START   (1)
#define SOC_SCTRL_SCLPMCUCLKEN_ssi1_clk_clkoff_sys_n_END     (1)
#define SOC_SCTRL_SCLPMCUCLKEN_rom_clk_clkoff_sys_n_START    (2)
#define SOC_SCTRL_SCLPMCUCLKEN_rom_clk_clkoff_sys_n_END      (2)
#define SOC_SCTRL_SCLPMCUCLKEN_ram_clk_clkoff_sys_n_START    (3)
#define SOC_SCTRL_SCLPMCUCLKEN_ram_clk_clkoff_sys_n_END      (3)
#define SOC_SCTRL_SCLPMCUCLKEN_aon_clk_clkoff_sys_n_START    (4)
#define SOC_SCTRL_SCLPMCUCLKEN_aon_clk_clkoff_sys_n_END      (4)
#define SOC_SCTRL_SCLPMCUCLKEN_ddrc_clk_clkoff_sys_n_START   (5)
#define SOC_SCTRL_SCLPMCUCLKEN_ddrc_clk_clkoff_sys_n_END     (5)
#define SOC_SCTRL_SCLPMCUCLKEN_tsen_clk_clkoff_sys_n_START   (6)
#define SOC_SCTRL_SCLPMCUCLKEN_tsen_clk_clkoff_sys_n_END     (6)
#define SOC_SCTRL_SCLPMCUCLKEN_pmc_clk_clkoff_sys_n_START    (7)
#define SOC_SCTRL_SCLPMCUCLKEN_pmc_clk_clkoff_sys_n_END      (7)
#define SOC_SCTRL_SCLPMCUCLKEN_uart_clk_clkoff_sys_n_START   (8)
#define SOC_SCTRL_SCLPMCUCLKEN_uart_clk_clkoff_sys_n_END     (8)
#define SOC_SCTRL_SCLPMCUCLKEN_i2c_clk_clkoff_sys_n_START    (9)
#define SOC_SCTRL_SCLPMCUCLKEN_i2c_clk_clkoff_sys_n_END      (9)
#define SOC_SCTRL_SCLPMCUCLKEN_ssi_clk_clkoff_sys_n_START    (10)
#define SOC_SCTRL_SCLPMCUCLKEN_ssi_clk_clkoff_sys_n_END      (10)
#define SOC_SCTRL_SCLPMCUCLKEN_pcrg_clk_clkoff_sys_n_START   (11)
#define SOC_SCTRL_SCLPMCUCLKEN_pcrg_clk_clkoff_sys_n_END     (11)
#define SOC_SCTRL_SCLPMCUCLKEN_nandc_clk_clkoff_sys_n_START  (12)
#define SOC_SCTRL_SCLPMCUCLKEN_nandc_clk_clkoff_sys_n_END    (12)
#define SOC_SCTRL_SCLPMCUCLKEN_wdog_clk_clkoff_sys_n_START   (13)
#define SOC_SCTRL_SCLPMCUCLKEN_wdog_clk_clkoff_sys_n_END     (13)
#define SOC_SCTRL_SCLPMCUCLKEN_tim_clk_clkoff_sys_n_START    (14)
#define SOC_SCTRL_SCLPMCUCLKEN_tim_clk_clkoff_sys_n_END      (14)
#define SOC_SCTRL_SCLPMCUCLKEN_cssys_clk_clkoff_sys_n_START  (15)
#define SOC_SCTRL_SCLPMCUCLKEN_cssys_clk_clkoff_sys_n_END    (15)
#define SOC_SCTRL_SCLPMCUCLKEN_sclpmcuclken_msk_START        (16)
#define SOC_SCTRL_SCLPMCUCLKEN_sclpmcuclken_msk_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCLPMCURSTEN_UNION
 �ṹ˵��  : SCLPMCURSTEN �Ĵ����ṹ���塣��ַƫ����:0x504����ֵ:0x00000000�����:32
 �Ĵ���˵��: LPMCU��ϵͳ��λʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_software_req       : 1;  /* bit[0]    : 0:�ޱ仯 1:SCLPMCURSTSTAT��Ӧbit��1�� */
        unsigned int  coresight_soft_rst_req : 1;  /* bit[1]    : bit����ο�bit0�� */
        unsigned int  ssi1_soft_rst_req      : 1;  /* bit[2]    : bit����ο�bit0�� */
        unsigned int  rom_soft_rst_req       : 1;  /* bit[3]    : bit����ο�bit0�� */
        unsigned int  ram_soft_rst_req       : 1;  /* bit[4]    : bit����ο�bit0�� */
        unsigned int  aon_soft_rst_req       : 1;  /* bit[5]    : bit����ο�bit0�� */
        unsigned int  ddrc_soft_rst_req      : 1;  /* bit[6]    : bit����ο�bit0�� */
        unsigned int  tsen_soft_rst_req      : 1;  /* bit[7]    : bit����ο�bit0�� */
        unsigned int  pmc_soft_rst_req       : 1;  /* bit[8]    : bit����ο�bit0�� */
        unsigned int  uart_soft_rst_req      : 1;  /* bit[9]    : bit����ο�bit0�� */
        unsigned int  i2c_soft_rst_req       : 1;  /* bit[10]   : bit����ο�bit0�� */
        unsigned int  ssi_soft_rst_req       : 1;  /* bit[11]   : bit����ο�bit0�� */
        unsigned int  pcrg_soft_rst_req      : 1;  /* bit[12]   : bit����ο�bit0�� */
        unsigned int  nandc_soft_rst_req     : 1;  /* bit[13]   : bit����ο�bit0�� */
        unsigned int  wdog_soft_rst_req      : 1;  /* bit[14]   : bit����ο�bit0�� */
        unsigned int  tim_soft_rst_req       : 1;  /* bit[15]   : bit����ο�bit0�� */
        unsigned int  cssys_soft_rst_req     : 1;  /* bit[16]   : bit����ο�bit0�� */
        unsigned int  m3_lp_rst_req          : 1;  /* bit[17]   : bit����ο�bit0�� */
        unsigned int  reserved               : 14; /* bit[18-31]: ������ */
    } reg;
} SOC_SCTRL_SCLPMCURSTEN_UNION;
#endif
#define SOC_SCTRL_SCLPMCURSTEN_rst_software_req_START        (0)
#define SOC_SCTRL_SCLPMCURSTEN_rst_software_req_END          (0)
#define SOC_SCTRL_SCLPMCURSTEN_coresight_soft_rst_req_START  (1)
#define SOC_SCTRL_SCLPMCURSTEN_coresight_soft_rst_req_END    (1)
#define SOC_SCTRL_SCLPMCURSTEN_ssi1_soft_rst_req_START       (2)
#define SOC_SCTRL_SCLPMCURSTEN_ssi1_soft_rst_req_END         (2)
#define SOC_SCTRL_SCLPMCURSTEN_rom_soft_rst_req_START        (3)
#define SOC_SCTRL_SCLPMCURSTEN_rom_soft_rst_req_END          (3)
#define SOC_SCTRL_SCLPMCURSTEN_ram_soft_rst_req_START        (4)
#define SOC_SCTRL_SCLPMCURSTEN_ram_soft_rst_req_END          (4)
#define SOC_SCTRL_SCLPMCURSTEN_aon_soft_rst_req_START        (5)
#define SOC_SCTRL_SCLPMCURSTEN_aon_soft_rst_req_END          (5)
#define SOC_SCTRL_SCLPMCURSTEN_ddrc_soft_rst_req_START       (6)
#define SOC_SCTRL_SCLPMCURSTEN_ddrc_soft_rst_req_END         (6)
#define SOC_SCTRL_SCLPMCURSTEN_tsen_soft_rst_req_START       (7)
#define SOC_SCTRL_SCLPMCURSTEN_tsen_soft_rst_req_END         (7)
#define SOC_SCTRL_SCLPMCURSTEN_pmc_soft_rst_req_START        (8)
#define SOC_SCTRL_SCLPMCURSTEN_pmc_soft_rst_req_END          (8)
#define SOC_SCTRL_SCLPMCURSTEN_uart_soft_rst_req_START       (9)
#define SOC_SCTRL_SCLPMCURSTEN_uart_soft_rst_req_END         (9)
#define SOC_SCTRL_SCLPMCURSTEN_i2c_soft_rst_req_START        (10)
#define SOC_SCTRL_SCLPMCURSTEN_i2c_soft_rst_req_END          (10)
#define SOC_SCTRL_SCLPMCURSTEN_ssi_soft_rst_req_START        (11)
#define SOC_SCTRL_SCLPMCURSTEN_ssi_soft_rst_req_END          (11)
#define SOC_SCTRL_SCLPMCURSTEN_pcrg_soft_rst_req_START       (12)
#define SOC_SCTRL_SCLPMCURSTEN_pcrg_soft_rst_req_END         (12)
#define SOC_SCTRL_SCLPMCURSTEN_nandc_soft_rst_req_START      (13)
#define SOC_SCTRL_SCLPMCURSTEN_nandc_soft_rst_req_END        (13)
#define SOC_SCTRL_SCLPMCURSTEN_wdog_soft_rst_req_START       (14)
#define SOC_SCTRL_SCLPMCURSTEN_wdog_soft_rst_req_END         (14)
#define SOC_SCTRL_SCLPMCURSTEN_tim_soft_rst_req_START        (15)
#define SOC_SCTRL_SCLPMCURSTEN_tim_soft_rst_req_END          (15)
#define SOC_SCTRL_SCLPMCURSTEN_cssys_soft_rst_req_START      (16)
#define SOC_SCTRL_SCLPMCURSTEN_cssys_soft_rst_req_END        (16)
#define SOC_SCTRL_SCLPMCURSTEN_m3_lp_rst_req_START           (17)
#define SOC_SCTRL_SCLPMCURSTEN_m3_lp_rst_req_END             (17)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCLPMCURSTDIS_UNION
 �ṹ˵��  : SCLPMCURSTDIS �Ĵ����ṹ���塣��ַƫ����:0x508����ֵ:0x00000000�����:32
 �Ĵ���˵��: LPMCU��ϵͳ��λ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_software_req       : 1;  /* bit[0]    : 0:�ޱ仯 1:SCLPMCURSTSTAT��Ӧbit��0�� */
        unsigned int  coresight_soft_rst_req : 1;  /* bit[1]    : bit����ο�bit0�� */
        unsigned int  ssi1_soft_rst_req      : 1;  /* bit[2]    : bit����ο�bit0�� */
        unsigned int  rom_soft_rst_req       : 1;  /* bit[3]    : bit����ο�bit0�� */
        unsigned int  ram_soft_rst_req       : 1;  /* bit[4]    : bit����ο�bit0�� */
        unsigned int  aon_soft_rst_req       : 1;  /* bit[5]    : bit����ο�bit0�� */
        unsigned int  ddrc_soft_rst_req      : 1;  /* bit[6]    : bit����ο�bit0�� */
        unsigned int  tsen_soft_rst_req      : 1;  /* bit[7]    : bit����ο�bit0�� */
        unsigned int  pmc_soft_rst_req       : 1;  /* bit[8]    : bit����ο�bit0�� */
        unsigned int  uart_soft_rst_req      : 1;  /* bit[9]    : bit����ο�bit0�� */
        unsigned int  i2c_soft_rst_req       : 1;  /* bit[10]   : bit����ο�bit0�� */
        unsigned int  ssi_soft_rst_req       : 1;  /* bit[11]   : bit����ο�bit0�� */
        unsigned int  pcrg_soft_rst_req      : 1;  /* bit[12]   : bit����ο�bit0�� */
        unsigned int  nandc_soft_rst_req     : 1;  /* bit[13]   : bit����ο�bit0�� */
        unsigned int  wdog_soft_rst_req      : 1;  /* bit[14]   : bit����ο�bit0�� */
        unsigned int  tim_soft_rst_req       : 1;  /* bit[15]   : bit����ο�bit0�� */
        unsigned int  cssys_soft_rst_req     : 1;  /* bit[16]   : bit����ο�bit0�� */
        unsigned int  m3_lp_rst_req          : 1;  /* bit[17]   : bit����ο�bit0�� */
        unsigned int  reserved               : 14; /* bit[18-31]: ������ */
    } reg;
} SOC_SCTRL_SCLPMCURSTDIS_UNION;
#endif
#define SOC_SCTRL_SCLPMCURSTDIS_rst_software_req_START        (0)
#define SOC_SCTRL_SCLPMCURSTDIS_rst_software_req_END          (0)
#define SOC_SCTRL_SCLPMCURSTDIS_coresight_soft_rst_req_START  (1)
#define SOC_SCTRL_SCLPMCURSTDIS_coresight_soft_rst_req_END    (1)
#define SOC_SCTRL_SCLPMCURSTDIS_ssi1_soft_rst_req_START       (2)
#define SOC_SCTRL_SCLPMCURSTDIS_ssi1_soft_rst_req_END         (2)
#define SOC_SCTRL_SCLPMCURSTDIS_rom_soft_rst_req_START        (3)
#define SOC_SCTRL_SCLPMCURSTDIS_rom_soft_rst_req_END          (3)
#define SOC_SCTRL_SCLPMCURSTDIS_ram_soft_rst_req_START        (4)
#define SOC_SCTRL_SCLPMCURSTDIS_ram_soft_rst_req_END          (4)
#define SOC_SCTRL_SCLPMCURSTDIS_aon_soft_rst_req_START        (5)
#define SOC_SCTRL_SCLPMCURSTDIS_aon_soft_rst_req_END          (5)
#define SOC_SCTRL_SCLPMCURSTDIS_ddrc_soft_rst_req_START       (6)
#define SOC_SCTRL_SCLPMCURSTDIS_ddrc_soft_rst_req_END         (6)
#define SOC_SCTRL_SCLPMCURSTDIS_tsen_soft_rst_req_START       (7)
#define SOC_SCTRL_SCLPMCURSTDIS_tsen_soft_rst_req_END         (7)
#define SOC_SCTRL_SCLPMCURSTDIS_pmc_soft_rst_req_START        (8)
#define SOC_SCTRL_SCLPMCURSTDIS_pmc_soft_rst_req_END          (8)
#define SOC_SCTRL_SCLPMCURSTDIS_uart_soft_rst_req_START       (9)
#define SOC_SCTRL_SCLPMCURSTDIS_uart_soft_rst_req_END         (9)
#define SOC_SCTRL_SCLPMCURSTDIS_i2c_soft_rst_req_START        (10)
#define SOC_SCTRL_SCLPMCURSTDIS_i2c_soft_rst_req_END          (10)
#define SOC_SCTRL_SCLPMCURSTDIS_ssi_soft_rst_req_START        (11)
#define SOC_SCTRL_SCLPMCURSTDIS_ssi_soft_rst_req_END          (11)
#define SOC_SCTRL_SCLPMCURSTDIS_pcrg_soft_rst_req_START       (12)
#define SOC_SCTRL_SCLPMCURSTDIS_pcrg_soft_rst_req_END         (12)
#define SOC_SCTRL_SCLPMCURSTDIS_nandc_soft_rst_req_START      (13)
#define SOC_SCTRL_SCLPMCURSTDIS_nandc_soft_rst_req_END        (13)
#define SOC_SCTRL_SCLPMCURSTDIS_wdog_soft_rst_req_START       (14)
#define SOC_SCTRL_SCLPMCURSTDIS_wdog_soft_rst_req_END         (14)
#define SOC_SCTRL_SCLPMCURSTDIS_tim_soft_rst_req_START        (15)
#define SOC_SCTRL_SCLPMCURSTDIS_tim_soft_rst_req_END          (15)
#define SOC_SCTRL_SCLPMCURSTDIS_cssys_soft_rst_req_START      (16)
#define SOC_SCTRL_SCLPMCURSTDIS_cssys_soft_rst_req_END        (16)
#define SOC_SCTRL_SCLPMCURSTDIS_m3_lp_rst_req_START           (17)
#define SOC_SCTRL_SCLPMCURSTDIS_m3_lp_rst_req_END             (17)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCLPMCURSTSTAT_UNION
 �ṹ˵��  : SCLPMCURSTSTAT �Ĵ����ṹ���塣��ַƫ����:0x50C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LPMCU��ϵͳ��λʹ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_software_req       : 1;  /* bit[0]    : M3 Core��λ������Чʱ���ḴλM3 Core�������߼�
                                                                  0��unrst req 1:rst req�� */
        unsigned int  coresight_soft_rst_req : 1;  /* bit[1]    : M3 CoreSight ϵͳ�����λ���󣬸�λ���е�coresight�����bit����ο�bit0�� */
        unsigned int  ssi1_soft_rst_req      : 1;  /* bit[2]    : PMU_SSI1�ĸ�λ������Чʱ���ḴλPMU_SSI1�����߼���bit����ο�bit0�� */
        unsigned int  rom_soft_rst_req       : 1;  /* bit[3]    : BOOTROM�ĸ�λ������Чʱ���ḴλBOOTROM�ӿ��߼���bit����ο�bit0�� */
        unsigned int  ram_soft_rst_req       : 1;  /* bit[4]    : LP_RAM�ĸ�λ������Чʱ���ḴλLP_RAM�ӿ��߼���bit����ο�bit0�� */
        unsigned int  aon_soft_rst_req       : 1;  /* bit[5]    : AON_SUBSYS���ʽӿڵĸ�λ������Чʱ���Ḵλ����AON_SUBSYS�Ľӿ��߼���bit����ο�bit0�� */
        unsigned int  ddrc_soft_rst_req      : 1;  /* bit[6]    : DDRC���ýӿڵĸ�λ������Чʱ���ḴλDDRC�����ýӿ��߼���bit����ο�bit0�� */
        unsigned int  tsen_soft_rst_req      : 1;  /* bit[7]    : TSENSORC�ĸ�λ������Чʱ���ḴλTSENSORC�����߼���bit����ο�bit0�� */
        unsigned int  pmc_soft_rst_req       : 1;  /* bit[8]    : PMC�ĸ�λ������Чʱ���ḴλPMC�������߼���bit����ο�bit0�� */
        unsigned int  uart_soft_rst_req      : 1;  /* bit[9]    : UART�ĸ�λ������Чʱ���ḴλUART�����߼���bit����ο�bit0�� */
        unsigned int  i2c_soft_rst_req       : 1;  /* bit[10]   : PMU_I2C�ĸ�λ������Чʱ���ḴλPMU_I2C�����߼���bit����ο�bit0�� */
        unsigned int  ssi_soft_rst_req       : 1;  /* bit[11]   : PMU_SSI�ĸ�λ������Чʱ���ḴλPMU_SSI�����߼���bit����ο�bit0�� */
        unsigned int  pcrg_soft_rst_req      : 1;  /* bit[12]   : ����CRG���ýӿڵĸ�λ������Чʱ���Ḵλ����CRG�����ýӿ��߼���bit����ο�bit0�� */
        unsigned int  nandc_soft_rst_req     : 1;  /* bit[13]   : NANDC�ĸ�λ������Чʱ���ḴλNANDC�����߼���bit����ο�bit0�� */
        unsigned int  wdog_soft_rst_req      : 1;  /* bit[14]   : LP_WDG�ĸ�λ������Чʱ���Ḵλwatchdog�����߼���bit����ο�bit0�� */
        unsigned int  tim_soft_rst_req       : 1;  /* bit[15]   : LP_TIMER�ĸ�λ������Чʱ���Ḵλtimer�����߼���bit����ο�bit0�� */
        unsigned int  cssys_soft_rst_req     : 1;  /* bit[16]   : CSSYS���ʽӿڵĸ�λ������Чʱ���Ḵλ����CSSYS�Ľӿ��߼���bit����ο�bit0�� */
        unsigned int  m3_lp_rst_req          : 1;  /* bit[17]   : lpm3 rst����bit����ο�bit0�� */
        unsigned int  reserved               : 14; /* bit[18-31]: ������ */
    } reg;
} SOC_SCTRL_SCLPMCURSTSTAT_UNION;
#endif
#define SOC_SCTRL_SCLPMCURSTSTAT_rst_software_req_START        (0)
#define SOC_SCTRL_SCLPMCURSTSTAT_rst_software_req_END          (0)
#define SOC_SCTRL_SCLPMCURSTSTAT_coresight_soft_rst_req_START  (1)
#define SOC_SCTRL_SCLPMCURSTSTAT_coresight_soft_rst_req_END    (1)
#define SOC_SCTRL_SCLPMCURSTSTAT_ssi1_soft_rst_req_START       (2)
#define SOC_SCTRL_SCLPMCURSTSTAT_ssi1_soft_rst_req_END         (2)
#define SOC_SCTRL_SCLPMCURSTSTAT_rom_soft_rst_req_START        (3)
#define SOC_SCTRL_SCLPMCURSTSTAT_rom_soft_rst_req_END          (3)
#define SOC_SCTRL_SCLPMCURSTSTAT_ram_soft_rst_req_START        (4)
#define SOC_SCTRL_SCLPMCURSTSTAT_ram_soft_rst_req_END          (4)
#define SOC_SCTRL_SCLPMCURSTSTAT_aon_soft_rst_req_START        (5)
#define SOC_SCTRL_SCLPMCURSTSTAT_aon_soft_rst_req_END          (5)
#define SOC_SCTRL_SCLPMCURSTSTAT_ddrc_soft_rst_req_START       (6)
#define SOC_SCTRL_SCLPMCURSTSTAT_ddrc_soft_rst_req_END         (6)
#define SOC_SCTRL_SCLPMCURSTSTAT_tsen_soft_rst_req_START       (7)
#define SOC_SCTRL_SCLPMCURSTSTAT_tsen_soft_rst_req_END         (7)
#define SOC_SCTRL_SCLPMCURSTSTAT_pmc_soft_rst_req_START        (8)
#define SOC_SCTRL_SCLPMCURSTSTAT_pmc_soft_rst_req_END          (8)
#define SOC_SCTRL_SCLPMCURSTSTAT_uart_soft_rst_req_START       (9)
#define SOC_SCTRL_SCLPMCURSTSTAT_uart_soft_rst_req_END         (9)
#define SOC_SCTRL_SCLPMCURSTSTAT_i2c_soft_rst_req_START        (10)
#define SOC_SCTRL_SCLPMCURSTSTAT_i2c_soft_rst_req_END          (10)
#define SOC_SCTRL_SCLPMCURSTSTAT_ssi_soft_rst_req_START        (11)
#define SOC_SCTRL_SCLPMCURSTSTAT_ssi_soft_rst_req_END          (11)
#define SOC_SCTRL_SCLPMCURSTSTAT_pcrg_soft_rst_req_START       (12)
#define SOC_SCTRL_SCLPMCURSTSTAT_pcrg_soft_rst_req_END         (12)
#define SOC_SCTRL_SCLPMCURSTSTAT_nandc_soft_rst_req_START      (13)
#define SOC_SCTRL_SCLPMCURSTSTAT_nandc_soft_rst_req_END        (13)
#define SOC_SCTRL_SCLPMCURSTSTAT_wdog_soft_rst_req_START       (14)
#define SOC_SCTRL_SCLPMCURSTSTAT_wdog_soft_rst_req_END         (14)
#define SOC_SCTRL_SCLPMCURSTSTAT_tim_soft_rst_req_START        (15)
#define SOC_SCTRL_SCLPMCURSTSTAT_tim_soft_rst_req_END          (15)
#define SOC_SCTRL_SCLPMCURSTSTAT_cssys_soft_rst_req_START      (16)
#define SOC_SCTRL_SCLPMCURSTSTAT_cssys_soft_rst_req_END        (16)
#define SOC_SCTRL_SCLPMCURSTSTAT_m3_lp_rst_req_START           (17)
#define SOC_SCTRL_SCLPMCURSTSTAT_m3_lp_rst_req_END             (17)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCLPMCUCTRL_UNION
 �ṹ˵��  : SCLPMCUCTRL �Ĵ����ṹ���塣��ַƫ����:0x510����ֵ:0x000002E8�����:32
 �Ĵ���˵��: LPMCU��ϵͳ�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m3_lp_gnspwm_clkoff_n : 1;  /* bit[0]    : m3_lp_clkoff_n[16]��gnspwm��ʱ�����ſ�
                                                                 0���ر�ʱ�ӣ�1������ʱ�ӡ� */
        unsigned int  mpudisable            : 1;  /* bit[1]    : M3�ڴ汣����Ԫ�����ź�
                                                                 0:enable 1:disable�� */
        unsigned int  nmi_in                : 1;  /* bit[2]    : �ⲿ���������ж�����
                                                                 0��no int 1:int occur�� */
        unsigned int  bus_div_clk_sel       : 2;  /* bit[3-4]  : bus_div_clk��Ƶ��ѡ���ź�
                                                                 00��bus_clk��1��Ƶ
                                                                 01��bus_clk��2��Ƶ
                                                                 10��bus_clk��3��Ƶ
                                                                 11��bus_clk��4��Ƶ�� */
        unsigned int  sysresetreq_en        : 1;  /* bit[5]    : M3 SYSRESETREQʹ�ܿ��ơ�
                                                                 0��M3�����ϵͳ��λ���󲻻ᱻM3 CRG��Ӧ��1��M3�����ϵͳ��λ����ɱ�M3 CRG��Ӧ�� */
        unsigned int  reserved_0            : 5;  /* bit[6-10] : ������ */
        unsigned int  lpmcuidle_bypass      : 1;  /* bit[11]   : ϵͳ״̬��LPMCU IDLE�ж�BYPASS���ƣ�
                                                                 1'b1��bypass��Ч
                                                                 1'b0��bypass��Ч�� */
        unsigned int  reserved_1            : 12; /* bit[12-23]: ������ */
        unsigned int  reserved_2            : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_SCTRL_SCLPMCUCTRL_UNION;
#endif
#define SOC_SCTRL_SCLPMCUCTRL_m3_lp_gnspwm_clkoff_n_START  (0)
#define SOC_SCTRL_SCLPMCUCTRL_m3_lp_gnspwm_clkoff_n_END    (0)
#define SOC_SCTRL_SCLPMCUCTRL_mpudisable_START             (1)
#define SOC_SCTRL_SCLPMCUCTRL_mpudisable_END               (1)
#define SOC_SCTRL_SCLPMCUCTRL_nmi_in_START                 (2)
#define SOC_SCTRL_SCLPMCUCTRL_nmi_in_END                   (2)
#define SOC_SCTRL_SCLPMCUCTRL_bus_div_clk_sel_START        (3)
#define SOC_SCTRL_SCLPMCUCTRL_bus_div_clk_sel_END          (4)
#define SOC_SCTRL_SCLPMCUCTRL_sysresetreq_en_START         (5)
#define SOC_SCTRL_SCLPMCUCTRL_sysresetreq_en_END           (5)
#define SOC_SCTRL_SCLPMCUCTRL_lpmcuidle_bypass_START       (11)
#define SOC_SCTRL_SCLPMCUCTRL_lpmcuidle_bypass_END         (11)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCLPMCUSTAT_UNION
 �ṹ˵��  : SCLPMCUSTAT �Ĵ����ṹ���塣��ַƫ����:0x514����ֵ:0x00000000�����:32
 �Ĵ���˵��: LPMCU��ϵͳ״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sysresetreq_sign_out_stat : 1;  /* bit[0]   : M3 SYSRESETREQ��λ�¼���־���
                                                                    ����
                                                                    0:no rst 1:rst�� */
        unsigned int  sleeping                  : 1;  /* bit[1]   : M3 ����״ָ̬ʾ�ź�
                                                                    0:no sleeping 1:sleeping�� */
        unsigned int  lockup                    : 1;  /* bit[2]   : M3 core����ָʾ�ź�
                                                                    0: no lockup 1:lockup�� */
        unsigned int  halted                    : 1;  /* bit[3]   : M3 coreͣ��ָʾ�źţ�debug״̬��
                                                                    0��no halt 1:halted�� */
        unsigned int  reserved                  : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCLPMCUSTAT_UNION;
#endif
#define SOC_SCTRL_SCLPMCUSTAT_sysresetreq_sign_out_stat_START  (0)
#define SOC_SCTRL_SCLPMCUSTAT_sysresetreq_sign_out_stat_END    (0)
#define SOC_SCTRL_SCLPMCUSTAT_sleeping_START                   (1)
#define SOC_SCTRL_SCLPMCUSTAT_sleeping_END                     (1)
#define SOC_SCTRL_SCLPMCUSTAT_lockup_START                     (2)
#define SOC_SCTRL_SCLPMCUSTAT_lockup_END                       (2)
#define SOC_SCTRL_SCLPMCUSTAT_halted_START                     (3)
#define SOC_SCTRL_SCLPMCUSTAT_halted_END                       (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCLPMCURAMCTRL_UNION
 �ṹ˵��  : SCLPMCURAMCTRL �Ĵ����ṹ���塣��ַƫ����:0x518����ֵ:0x00000000�����:32
 �Ĵ���˵��: LPMCU RAM ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpramctrl_sel       : 1;  /* bit[0]    : LPMCU ram�͹���ģʽ����ѡ��
                                                               1���������
                                                               0��״̬�����ơ� */
        unsigned int  lpram0_mod          : 2;  /* bit[1-2]  : LPMCU ram0�͹���ģʽ����
                                                               00;normal
                                                               01:sleep
                                                               10:deepsleep
                                                               11:power-down�� */
        unsigned int  lpram1_mod          : 2;  /* bit[3-4]  : LPMCU ram1�͹���ģʽ����
                                                               00;normal
                                                               01:sleep
                                                               10:deepsleep
                                                               11:power-down�� */
        unsigned int  lpram2_mod          : 2;  /* bit[5-6]  : LPMCU ram2�͹���ģʽ����
                                                               00;normal
                                                               01:sleep
                                                               10:deepsleep
                                                               11:power-down�� */
        unsigned int  lpram3_mod          : 2;  /* bit[7-8]  : LPMCU ram3�͹���ģʽ����
                                                               00;normal
                                                               01:sleep
                                                               10:deepsleep
                                                               11:power-down�� */
        unsigned int  lpram0ctrl_soft     : 3;  /* bit[9-11] : LPMCU ram0�͹��Ŀ����ź�������ã�
                                                               bit9:slp
                                                               bit10:dslp
                                                               bit11:sd
                                                               000:normal
                                                               001:sleep
                                                               010:deepsleep
                                                               100:powerdown�� */
        unsigned int  lpram1ctrl_soft     : 3;  /* bit[12-14]: LPMCU ram1�͹��Ŀ����ź�������ã�
                                                               bit12:slp
                                                               bit13:dslp
                                                               bit14:sd
                                                               000:normal
                                                               001:sleep
                                                               010:deepsleep
                                                               100:powerdown�� */
        unsigned int  lpram2ctrl_soft     : 3;  /* bit[15-17]: LPMCU ram2�͹��Ŀ����ź�������ã�
                                                               bit15:slp
                                                               bit16:dslp
                                                               bit17:sd
                                                               000:normal
                                                               001:sleep
                                                               010:deepsleep
                                                               100:powerdown�� */
        unsigned int  lpram3ctrl_soft     : 3;  /* bit[18-20]: LPMCU ram3�͹��Ŀ����ź�������ã�
                                                               bit18:slp
                                                               bit19:dslp
                                                               bit20:sd
                                                               000:normal
                                                               001:sleep
                                                               010:deepsleep
                                                               100:powerdown�� */
        unsigned int  memrep_ram_mod      : 2;  /* bit[21-22]: memrep ram�͹���ģʽ���ã�״̬�����ƣ�
                                                               00:normal
                                                               01:sleep
                                                               10:deepsleep
                                                               11:power-down�� */
        unsigned int  memrep_ramctrl_soft : 3;  /* bit[23-25]: memrep ram�͹��Ŀ����ź�������ã�
                                                               bit23:slp
                                                               bit24:dslp
                                                               bit25:sd
                                                               000:normal
                                                               001:sleep
                                                               010:deepsleep
                                                               100:powerdown�� */
        unsigned int  reserved            : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_SCTRL_SCLPMCURAMCTRL_UNION;
#endif
#define SOC_SCTRL_SCLPMCURAMCTRL_lpramctrl_sel_START        (0)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpramctrl_sel_END          (0)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram0_mod_START           (1)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram0_mod_END             (2)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram1_mod_START           (3)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram1_mod_END             (4)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram2_mod_START           (5)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram2_mod_END             (6)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram3_mod_START           (7)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram3_mod_END             (8)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram0ctrl_soft_START      (9)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram0ctrl_soft_END        (11)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram1ctrl_soft_START      (12)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram1ctrl_soft_END        (14)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram2ctrl_soft_START      (15)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram2ctrl_soft_END        (17)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram3ctrl_soft_START      (18)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram3ctrl_soft_END        (20)
#define SOC_SCTRL_SCLPMCURAMCTRL_memrep_ram_mod_START       (21)
#define SOC_SCTRL_SCLPMCURAMCTRL_memrep_ram_mod_END         (22)
#define SOC_SCTRL_SCLPMCURAMCTRL_memrep_ramctrl_soft_START  (23)
#define SOC_SCTRL_SCLPMCURAMCTRL_memrep_ramctrl_soft_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBBPDRXSTAT0_UNION
 �ṹ˵��  : SCBBPDRXSTAT0 �Ĵ����ṹ���塣��ַƫ����:0x530����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPDRX��ϵͳ״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g2_gdrx_depsleep_flag    : 1;  /* bit[0]   : ״ָ̬ʾ�źţ�����Ч�� */
        unsigned int  g1_gdrx_depsleep_flag    : 1;  /* bit[1]   : ״ָ̬ʾ�źţ�����Ч�� */
        unsigned int  wdrx_deepsleep_flag      : 1;  /* bit[2]   : ״ָ̬ʾ�źţ�����Ч�� */
        unsigned int  cdrx_deepsleep_flag_1x   : 1;  /* bit[3]   : ״ָ̬ʾ�źţ�����Ч�� */
        unsigned int  cdrx_deepsleep_flag_evdo : 1;  /* bit[4]   : ״ָ̬ʾ�źţ�����Ч�� */
        unsigned int  reserved                 : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_SCTRL_SCBBPDRXSTAT0_UNION;
#endif
#define SOC_SCTRL_SCBBPDRXSTAT0_g2_gdrx_depsleep_flag_START     (0)
#define SOC_SCTRL_SCBBPDRXSTAT0_g2_gdrx_depsleep_flag_END       (0)
#define SOC_SCTRL_SCBBPDRXSTAT0_g1_gdrx_depsleep_flag_START     (1)
#define SOC_SCTRL_SCBBPDRXSTAT0_g1_gdrx_depsleep_flag_END       (1)
#define SOC_SCTRL_SCBBPDRXSTAT0_wdrx_deepsleep_flag_START       (2)
#define SOC_SCTRL_SCBBPDRXSTAT0_wdrx_deepsleep_flag_END         (2)
#define SOC_SCTRL_SCBBPDRXSTAT0_cdrx_deepsleep_flag_1x_START    (3)
#define SOC_SCTRL_SCBBPDRXSTAT0_cdrx_deepsleep_flag_1x_END      (3)
#define SOC_SCTRL_SCBBPDRXSTAT0_cdrx_deepsleep_flag_evdo_START  (4)
#define SOC_SCTRL_SCBBPDRXSTAT0_cdrx_deepsleep_flag_evdo_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBBPDRXSTAT1_UNION
 �ṹ˵��  : SCBBPDRXSTAT1 �Ĵ����ṹ���塣��ַƫ����:0x534����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPDRX��ϵͳ״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldrx2dbg_abs_timer : 32; /* bit[0-31]: ldrx2dbg_abs_timer�ĵ�32bit��(32KHzʱ����ļ���)�� */
    } reg;
} SOC_SCTRL_SCBBPDRXSTAT1_UNION;
#endif
#define SOC_SCTRL_SCBBPDRXSTAT1_ldrx2dbg_abs_timer_START  (0)
#define SOC_SCTRL_SCBBPDRXSTAT1_ldrx2dbg_abs_timer_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBBPDRXSTAT2_UNION
 �ṹ˵��  : SCBBPDRXSTAT2 �Ĵ����ṹ���塣��ַƫ����:0x538����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPDRX��ϵͳ״̬�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldrx2dbg_abs_timer : 32; /* bit[0-31]: ldrx2dbg_abs_timer�ĸ�32bit��(32KHzʱ����ļ���)�� */
    } reg;
} SOC_SCTRL_SCBBPDRXSTAT2_UNION;
#endif
#define SOC_SCTRL_SCBBPDRXSTAT2_ldrx2dbg_abs_timer_START  (0)
#define SOC_SCTRL_SCBBPDRXSTAT2_ldrx2dbg_abs_timer_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBBPDRXSTAT3_UNION
 �ṹ˵��  : SCBBPDRXSTAT3 �Ĵ����ṹ���塣��ַƫ����:0x53C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPDRX��ϵͳ״̬�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldrx2dbg_abs_timer_sleep : 32; /* bit[0-31]: ���һ�ν���sleepʱldrx2dbg_abs_timer�ĵ�32bit��(32KHzʱ����ļ���)�� */
    } reg;
} SOC_SCTRL_SCBBPDRXSTAT3_UNION;
#endif
#define SOC_SCTRL_SCBBPDRXSTAT3_ldrx2dbg_abs_timer_sleep_START  (0)
#define SOC_SCTRL_SCBBPDRXSTAT3_ldrx2dbg_abs_timer_sleep_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCBBPDRXSTAT4_UNION
 �ṹ˵��  : SCBBPDRXSTAT4 �Ĵ����ṹ���塣��ַƫ����:0x540����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPDRX��ϵͳ״̬�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldrx2dbg_abs_timer_sleep : 32; /* bit[0-31]: ���һ�ν���sleepʱldrx2dbg_abs_timer�ĸ�32bit��(32KHzʱ����ļ���)�� */
    } reg;
} SOC_SCTRL_SCBBPDRXSTAT4_UNION;
#endif
#define SOC_SCTRL_SCBBPDRXSTAT4_ldrx2dbg_abs_timer_sleep_START  (0)
#define SOC_SCTRL_SCBBPDRXSTAT4_ldrx2dbg_abs_timer_sleep_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCA53_EVENT_MASK_UNION
 �ṹ˵��  : SCA53_EVENT_MASK �Ĵ����ṹ���塣��ַƫ����:0x550����ֵ:0x0000000F�����:32
 �Ĵ���˵��: A53 EVENT���μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event_mask   : 1;  /* bit[0]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  a57_event_mask   : 1;  /* bit[1]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  iomcu_event_mask : 1;  /* bit[2]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  lpmcu_event_mask : 1;  /* bit[3]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  mcpu_event_mask  : 1;  /* bit[4]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  ispa7_event_mask : 1;  /* bit[5]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  reserved         : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_SCTRL_SCA53_EVENT_MASK_UNION;
#endif
#define SOC_SCTRL_SCA53_EVENT_MASK_a53_event_mask_START    (0)
#define SOC_SCTRL_SCA53_EVENT_MASK_a53_event_mask_END      (0)
#define SOC_SCTRL_SCA53_EVENT_MASK_a57_event_mask_START    (1)
#define SOC_SCTRL_SCA53_EVENT_MASK_a57_event_mask_END      (1)
#define SOC_SCTRL_SCA53_EVENT_MASK_iomcu_event_mask_START  (2)
#define SOC_SCTRL_SCA53_EVENT_MASK_iomcu_event_mask_END    (2)
#define SOC_SCTRL_SCA53_EVENT_MASK_lpmcu_event_mask_START  (3)
#define SOC_SCTRL_SCA53_EVENT_MASK_lpmcu_event_mask_END    (3)
#define SOC_SCTRL_SCA53_EVENT_MASK_mcpu_event_mask_START   (4)
#define SOC_SCTRL_SCA53_EVENT_MASK_mcpu_event_mask_END     (4)
#define SOC_SCTRL_SCA53_EVENT_MASK_ispa7_event_mask_START  (5)
#define SOC_SCTRL_SCA53_EVENT_MASK_ispa7_event_mask_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCA57_EVENT_MASK_UNION
 �ṹ˵��  : SCA57_EVENT_MASK �Ĵ����ṹ���塣��ַƫ����:0x554����ֵ:0x0000000F�����:32
 �Ĵ���˵��: A57 EVENT���μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event_mask   : 1;  /* bit[0]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  a57_event_mask   : 1;  /* bit[1]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  iomcu_event_mask : 1;  /* bit[2]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  lpmcu_event_mask : 1;  /* bit[3]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  mcpu_event_mask  : 1;  /* bit[4]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  ispa7_event_mask : 1;  /* bit[5]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  reserved         : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_SCTRL_SCA57_EVENT_MASK_UNION;
#endif
#define SOC_SCTRL_SCA57_EVENT_MASK_a53_event_mask_START    (0)
#define SOC_SCTRL_SCA57_EVENT_MASK_a53_event_mask_END      (0)
#define SOC_SCTRL_SCA57_EVENT_MASK_a57_event_mask_START    (1)
#define SOC_SCTRL_SCA57_EVENT_MASK_a57_event_mask_END      (1)
#define SOC_SCTRL_SCA57_EVENT_MASK_iomcu_event_mask_START  (2)
#define SOC_SCTRL_SCA57_EVENT_MASK_iomcu_event_mask_END    (2)
#define SOC_SCTRL_SCA57_EVENT_MASK_lpmcu_event_mask_START  (3)
#define SOC_SCTRL_SCA57_EVENT_MASK_lpmcu_event_mask_END    (3)
#define SOC_SCTRL_SCA57_EVENT_MASK_mcpu_event_mask_START   (4)
#define SOC_SCTRL_SCA57_EVENT_MASK_mcpu_event_mask_END     (4)
#define SOC_SCTRL_SCA57_EVENT_MASK_ispa7_event_mask_START  (5)
#define SOC_SCTRL_SCA57_EVENT_MASK_ispa7_event_mask_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCIOMCU_EVENT_MASK_UNION
 �ṹ˵��  : SCIOMCU_EVENT_MASK �Ĵ����ṹ���塣��ַƫ����:0x558����ֵ:0x0000000F�����:32
 �Ĵ���˵��: IOMCU EVENT���μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event_mask   : 1;  /* bit[0]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  a57_event_mask   : 1;  /* bit[1]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  iomcu_event_mask : 1;  /* bit[2]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  lpmcu_event_mask : 1;  /* bit[3]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  mcpu_event_mask  : 1;  /* bit[4]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  ispa7_event_mask : 1;  /* bit[5]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  reserved         : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_SCTRL_SCIOMCU_EVENT_MASK_UNION;
#endif
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_a53_event_mask_START    (0)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_a53_event_mask_END      (0)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_a57_event_mask_START    (1)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_a57_event_mask_END      (1)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_iomcu_event_mask_START  (2)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_iomcu_event_mask_END    (2)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_lpmcu_event_mask_START  (3)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_lpmcu_event_mask_END    (3)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_mcpu_event_mask_START   (4)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_mcpu_event_mask_END     (4)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_ispa7_event_mask_START  (5)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_ispa7_event_mask_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCLPMCU_EVENT_MASK_UNION
 �ṹ˵��  : SCLPMCU_EVENT_MASK �Ĵ����ṹ���塣��ַƫ����:0x55C����ֵ:0x0000000F�����:32
 �Ĵ���˵��: LPMCU EVENT���μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event_mask   : 1;  /* bit[0]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  a57_event_mask   : 1;  /* bit[1]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  iomcu_event_mask : 1;  /* bit[2]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  lpmcu_event_mask : 1;  /* bit[3]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  mcpu_event_mask  : 1;  /* bit[4]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  ispa7_event_mask : 1;  /* bit[5]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  reserved         : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_SCTRL_SCLPMCU_EVENT_MASK_UNION;
#endif
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_a53_event_mask_START    (0)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_a53_event_mask_END      (0)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_a57_event_mask_START    (1)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_a57_event_mask_END      (1)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_iomcu_event_mask_START  (2)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_iomcu_event_mask_END    (2)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_lpmcu_event_mask_START  (3)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_lpmcu_event_mask_END    (3)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_mcpu_event_mask_START   (4)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_mcpu_event_mask_END     (4)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_ispa7_event_mask_START  (5)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_ispa7_event_mask_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCMCPU_EVENT_MASK_UNION
 �ṹ˵��  : SCMCPU_EVENT_MASK �Ĵ����ṹ���塣��ַƫ����:0x560����ֵ:0x00000000�����:32
 �Ĵ���˵��: MCPU EVENT���μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event_mask   : 1;  /* bit[0]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  a57_event_mask   : 1;  /* bit[1]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  iomcu_event_mask : 1;  /* bit[2]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  lpmcu_event_mask : 1;  /* bit[3]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  mcpu_event_mask  : 1;  /* bit[4]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  ispa7_event_mask : 1;  /* bit[5]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  reserved         : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_SCTRL_SCMCPU_EVENT_MASK_UNION;
#endif
#define SOC_SCTRL_SCMCPU_EVENT_MASK_a53_event_mask_START    (0)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_a53_event_mask_END      (0)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_a57_event_mask_START    (1)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_a57_event_mask_END      (1)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_iomcu_event_mask_START  (2)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_iomcu_event_mask_END    (2)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_lpmcu_event_mask_START  (3)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_lpmcu_event_mask_END    (3)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_mcpu_event_mask_START   (4)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_mcpu_event_mask_END     (4)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_ispa7_event_mask_START  (5)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_ispa7_event_mask_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCEVENT_STAT_UNION
 �ṹ˵��  : SCEVENT_STAT �Ĵ����ṹ���塣��ַƫ����:0x564����ֵ:0x00000000�����:32
 �Ĵ���˵��: EVENT״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event   : 1;  /* bit[0]   : 1��event��Ч��
                                                      0��event��Ч�� */
        unsigned int  a57_event   : 1;  /* bit[1]   : 1��event��Ч��
                                                      0��event��Ч�� */
        unsigned int  iomcu_event : 1;  /* bit[2]   : 1��event��Ч��
                                                      0��event��Ч�� */
        unsigned int  lpmcu_event : 1;  /* bit[3]   : 1��event��Ч��
                                                      0��event��Ч�� */
        unsigned int  mcpu_event  : 1;  /* bit[4]   : 1��event��Ч��
                                                      0��event��Ч�� */
        unsigned int  ispa7_event : 1;  /* bit[5]   : 1��event��Ч��
                                                      0��event��Ч�� */
        unsigned int  reserved    : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_SCTRL_SCEVENT_STAT_UNION;
#endif
#define SOC_SCTRL_SCEVENT_STAT_a53_event_START    (0)
#define SOC_SCTRL_SCEVENT_STAT_a53_event_END      (0)
#define SOC_SCTRL_SCEVENT_STAT_a57_event_START    (1)
#define SOC_SCTRL_SCEVENT_STAT_a57_event_END      (1)
#define SOC_SCTRL_SCEVENT_STAT_iomcu_event_START  (2)
#define SOC_SCTRL_SCEVENT_STAT_iomcu_event_END    (2)
#define SOC_SCTRL_SCEVENT_STAT_lpmcu_event_START  (3)
#define SOC_SCTRL_SCEVENT_STAT_lpmcu_event_END    (3)
#define SOC_SCTRL_SCEVENT_STAT_mcpu_event_START   (4)
#define SOC_SCTRL_SCEVENT_STAT_mcpu_event_END     (4)
#define SOC_SCTRL_SCEVENT_STAT_ispa7_event_START  (5)
#define SOC_SCTRL_SCEVENT_STAT_ispa7_event_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCISPA7_EVENT_MASK_UNION
 �ṹ˵��  : SCISPA7_EVENT_MASK �Ĵ����ṹ���塣��ַƫ����:0x568����ֵ:0x0000000F�����:32
 �Ĵ���˵��: MCPU EVENT���μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event_mask   : 1;  /* bit[0]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  a57_event_mask   : 1;  /* bit[1]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  iomcu_event_mask : 1;  /* bit[2]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  lpmcu_event_mask : 1;  /* bit[3]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  mcpu_event_mask  : 1;  /* bit[4]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  ispa7_event_mask : 1;  /* bit[5]   : 1��������Ч��
                                                           0��������Ч�� */
        unsigned int  reserved         : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_SCTRL_SCISPA7_EVENT_MASK_UNION;
#endif
#define SOC_SCTRL_SCISPA7_EVENT_MASK_a53_event_mask_START    (0)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_a53_event_mask_END      (0)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_a57_event_mask_START    (1)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_a57_event_mask_END      (1)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_iomcu_event_mask_START  (2)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_iomcu_event_mask_END    (2)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_lpmcu_event_mask_START  (3)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_lpmcu_event_mask_END    (3)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_mcpu_event_mask_START   (4)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_mcpu_event_mask_END     (4)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_ispa7_event_mask_START  (5)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_ispa7_event_mask_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCIOMCUCLKCTRL_UNION
 �ṹ˵��  : SCIOMCUCLKCTRL �Ĵ����ṹ���塣��ַƫ����:0x580����ֵ:0x00000003�����:32
 �Ĵ���˵��: IOMCUʱ�ӿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_iomcu_pll_div   : 1;  /* bit[0]    : IOMCU PLL��Ƶ��ʹ�ܣ�
                                                              0��ʹ�ܹر�
                                                              1��ʹ�ܴ�
                                                              ���յ�ʹ���ź��ɸ������ź���IOMCU_pll_div_ctrl���� */
        unsigned int  gt_iomcu_sys_div   : 1;  /* bit[1]    : IOMCU SYS��Ƶ��ʹ�ܣ�
                                                              0��ʹ�ܹر�
                                                              1��ʹ�ܴ�
                                                              ���յ�ʹ���ź��ɸ������ź���IOMCU_sys_div_ctrl���� */
        unsigned int  reserved           : 14; /* bit[2-15] : ������ */
        unsigned int  sciomcuclkctrl_msk : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                              ֻ�е�clkdivmasken��Ӧ�ı���λд1'b1��дclkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_SCTRL_SCIOMCUCLKCTRL_UNION;
#endif
#define SOC_SCTRL_SCIOMCUCLKCTRL_gt_iomcu_pll_div_START    (0)
#define SOC_SCTRL_SCIOMCUCLKCTRL_gt_iomcu_pll_div_END      (0)
#define SOC_SCTRL_SCIOMCUCLKCTRL_gt_iomcu_sys_div_START    (1)
#define SOC_SCTRL_SCIOMCUCLKCTRL_gt_iomcu_sys_div_END      (1)
#define SOC_SCTRL_SCIOMCUCLKCTRL_sciomcuclkctrl_msk_START  (16)
#define SOC_SCTRL_SCIOMCUCLKCTRL_sciomcuclkctrl_msk_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCIOMCUCLKSTAT_UNION
 �ṹ˵��  : SCIOMCUCLKSTAT �Ĵ����ṹ���塣��ַƫ����:0x584����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCUʱ�ӿ����ź�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_pll_ctrl        : 1;  /* bit[0]   : IOMCU�����PLLʹ��״̬��
                                                                0��ʹ�ܹر�
                                                                1��ʹ�ܴ򿪡� */
        unsigned int  iomcu_pll_div_ctrl    : 1;  /* bit[1]   : IOMCU�����PLL DIVʹ��״̬��
                                                                0��ʹ�ܹر�
                                                                1��ʹ�ܴ򿪡� */
        unsigned int  iomcu_sys_div_ctrl    : 1;  /* bit[2]   : IOMCU�����SYS DIVʹ��״̬��
                                                                0��ʹ�ܹر�
                                                                1��ʹ�ܴ򿪡� */
        unsigned int  gt_iomcu_pll_div_stat : 1;  /* bit[3]   : IOMCU��PLL DIVʹ������״̬��gt_IOMCU_pll_div��IOMCU_pll_div_ctrl�򣩣�
                                                                0��ʹ�ܹر�
                                                                1��ʹ�ܴ򿪡� */
        unsigned int  gt_iomcu_sys_div_stat : 1;  /* bit[4]   : IOMCU��SYS DIVʹ������״̬��gt_IOMCU_sys_div��IOMCU_sys_div_ctrl�򣩣�
                                                                0��ʹ�ܹر�
                                                                1��ʹ�ܴ򿪡� */
        unsigned int  reserved              : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_SCTRL_SCIOMCUCLKSTAT_UNION;
#endif
#define SOC_SCTRL_SCIOMCUCLKSTAT_iomcu_pll_ctrl_START         (0)
#define SOC_SCTRL_SCIOMCUCLKSTAT_iomcu_pll_ctrl_END           (0)
#define SOC_SCTRL_SCIOMCUCLKSTAT_iomcu_pll_div_ctrl_START     (1)
#define SOC_SCTRL_SCIOMCUCLKSTAT_iomcu_pll_div_ctrl_END       (1)
#define SOC_SCTRL_SCIOMCUCLKSTAT_iomcu_sys_div_ctrl_START     (2)
#define SOC_SCTRL_SCIOMCUCLKSTAT_iomcu_sys_div_ctrl_END       (2)
#define SOC_SCTRL_SCIOMCUCLKSTAT_gt_iomcu_pll_div_stat_START  (3)
#define SOC_SCTRL_SCIOMCUCLKSTAT_gt_iomcu_pll_div_stat_END    (3)
#define SOC_SCTRL_SCIOMCUCLKSTAT_gt_iomcu_sys_div_stat_START  (4)
#define SOC_SCTRL_SCIOMCUCLKSTAT_gt_iomcu_sys_div_stat_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCIOMCUCLKEN_UNION
 �ṹ˵��  : SCIOMCUCLKEN �Ĵ����ṹ���塣��ַƫ����:0x588����ֵ:0x00003FFF�����:32
 �Ĵ���˵��: IOMCU��ϵͳʱ��ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved         : 16; /* bit[0-15] : ������ */
        unsigned int  sciomcuclken_msk : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                            ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_SCTRL_SCIOMCUCLKEN_UNION;
#endif
#define SOC_SCTRL_SCIOMCUCLKEN_sciomcuclken_msk_START  (16)
#define SOC_SCTRL_SCIOMCUCLKEN_sciomcuclken_msk_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCIOMCURSTEN_UNION
 �ṹ˵��  : SCIOMCURSTEN �Ĵ����ṹ���塣��ַƫ����:0x58C����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU��ϵͳ��λʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_SCTRL_SCIOMCURSTEN_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCIOMCURSTDIS_UNION
 �ṹ˵��  : SCIOMCURSTDIS �Ĵ����ṹ���塣��ַƫ����:0x590����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU��ϵͳ��λ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_SCTRL_SCIOMCURSTDIS_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCIOMCURSTSTAT_UNION
 �ṹ˵��  : SCIOMCURSTSTAT �Ĵ����ṹ���塣��ַƫ����:0x594����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU��ϵͳ��λʹ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_SCTRL_SCIOMCURSTSTAT_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCIOMCUCTRL_UNION
 �ṹ˵��  : SCIOMCUCTRL �Ĵ����ṹ���塣��ַƫ����:0x598����ֵ:0x00000005�����:32
 �Ĵ���˵��: IOMCU��ϵͳ�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]   : ������ */
        unsigned int  nmi_int  : 1;  /* bit[1]   : �ⲿ���������ж�����
                                                   0:no nmi 1:nmi int�� */
        unsigned int  reserved_1: 1;  /* bit[2]   : ������ */
        unsigned int  reserved_2: 29; /* bit[3-31]: ������ */
    } reg;
} SOC_SCTRL_SCIOMCUCTRL_UNION;
#endif
#define SOC_SCTRL_SCIOMCUCTRL_nmi_int_START   (1)
#define SOC_SCTRL_SCIOMCUCTRL_nmi_int_END     (1)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCIOMCUSTAT_UNION
 �ṹ˵��  : SCIOMCUSTAT �Ĵ����ṹ���塣��ַƫ����:0x59C����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU��ϵͳ״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_sysresetreq               : 1;  /* bit[0]    : iomcu_sysresetreq������
                                                                           0:normal 1:rst have occurred�� */
        unsigned int  iomcu_m7_state                  : 3;  /* bit[1-3]  : [3]sleeping
                                                                           0:no sleeping 1:sleeping
                                                                           [2]lockup
                                                                           0:no lockup 1:lockup
                                                                           [1]halted
                                                                           0:no halted 1:halted�� */
        unsigned int  iomcu_dma_mst_nopendingtrans_bp : 1;  /* bit[4]    : iomcu_dma_mst_nopendingtrans bypass
                                                                           0:bypass;
                                                                           1:iomcu_dma_mst_nopendingtrans is one input of sc_noc_aobus_idle_flag is AndGate�� */
        unsigned int  iomcu_axi_mst_nopendingtrans_bp : 1;  /* bit[5]    : iomcu_axi_mst_nopendingtrans bypass
                                                                           0:bypass;
                                                                           1:iomcu_axi_mst_nopendingtrans is one input of sc_noc_aobus_idle_flag is AndGate�� */
        unsigned int  iomcu_axi_ahb_nopendingtrans_bp : 1;  /* bit[6]    : iomcu_axi_ahb_nopendingtrans bypass
                                                                           0:bypass;
                                                                           1:iomcu_axi_ahb_nopendingtrans is one input of sc_noc_aobus_idle_flag is AndGate�� */
        unsigned int  m7_sc_stat                      : 9;  /* bit[7-15] : m7_sc_stat[7:0]
                                                                           [0]:m7 deepsleep
                                                                           [1]:iomcu_mtcmos_ack �������Ż���EC�޸ĵ���bit��IOMCU��ϵͳ��Դ��Դ����״̬��
                                                                           0��IOMCU��ϵͳ��Դʹ�ܳ�����
                                                                           1��IOMCU��ϵͳ��Դʹ�ܡ�
                                                                           others:reserved�� */
        unsigned int  iomcu_dma_mst_nopendingtrans    : 1;  /* bit[16]   : iomcu_dma_mst_nopendingtrans
                                                                           0:bus have trans 1:bus no pending trans�� */
        unsigned int  iomcu_axi_mst_nopendingtrans    : 1;  /* bit[17]   : iomcu_axi_mst_nopendingtrans
                                                                           0:bus have trans 1:bus no pending trans�� */
        unsigned int  reserved                        : 1;  /* bit[18]   : ������ */
        unsigned int  iomcu_axi_ahb_nopendingtrans    : 1;  /* bit[19]   : iomcu_axi_ahb_nopendingtrans
                                                                           0:bus have trans 1:bus no pending trans�� */
        unsigned int  iomcu_stat                      : 12; /* bit[20-31]: others:reserved
                                                                           [31:30]AO_BUS��ʱ���л� iomcu_aobus_clk_sw_req��
                                                                           [29:28]MMBUF��ʱ���л� iomcu_mmbuf_clk_sw_req��
                                                                           [27]AO_BUS��ʱ���ſ� iomcu_aobus_clk_en_req��1bit,1���� 0���ر�
                                                                           [26]MMBUF��ʱ���ſ� iomcu_mmbuf_clk_en_req��1bit,1���� 0���ر�
                                                                           [25]FLL�Ŀ��ؿ��� iomcu_fpll_en_req��1bit,1���� 0���ر�
                                                                           [24]PPLL0�Ŀ��ؿ��� �ѵ��������� */
    } reg;
} SOC_SCTRL_SCIOMCUSTAT_UNION;
#endif
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_sysresetreq_START                (0)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_sysresetreq_END                  (0)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_m7_state_START                   (1)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_m7_state_END                     (3)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_dma_mst_nopendingtrans_bp_START  (4)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_dma_mst_nopendingtrans_bp_END    (4)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_mst_nopendingtrans_bp_START  (5)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_mst_nopendingtrans_bp_END    (5)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_ahb_nopendingtrans_bp_START  (6)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_ahb_nopendingtrans_bp_END    (6)
#define SOC_SCTRL_SCIOMCUSTAT_m7_sc_stat_START                       (7)
#define SOC_SCTRL_SCIOMCUSTAT_m7_sc_stat_END                         (15)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_dma_mst_nopendingtrans_START     (16)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_dma_mst_nopendingtrans_END       (16)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_mst_nopendingtrans_START     (17)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_mst_nopendingtrans_END       (17)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_ahb_nopendingtrans_START     (19)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_ahb_nopendingtrans_END       (19)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_stat_START                       (20)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_stat_END                         (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCJTAG_SEL_UNION
 �ṹ˵��  : SCJTAG_SEL �Ĵ����ṹ���塣��ַƫ����:0x800����ֵ:0x00000000�����:32
 �Ĵ���˵��: JTAGѡ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  processor_jtag_sel : 1;  /* bit[0]   : 0��DSPͨ��ר��DSP jtag�˿ڼ�SD�����ùܽŵ���ʱ����ʱcoresight jtag����ͨ��ͨ��DSP��Coresight jtag���ö˿ڶ˿ڵ��ԣ�
                                                             1��DSP��ͨ��ͨ��DSP��Coresight jtag���ö˿ڵ���ʱ����ʱcoresight jtag���ܵ��ԡ� */
        unsigned int  dsp_jtag_sel       : 2;  /* bit[1-2] : 10��hifi dsp��JTAG
                                                             01��bbp dsp��JTAG
                                                             others��ivp32 dsp��JTAG�� */
        unsigned int  reserved           : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_SCTRL_SCJTAG_SEL_UNION;
#endif
#define SOC_SCTRL_SCJTAG_SEL_processor_jtag_sel_START  (0)
#define SOC_SCTRL_SCJTAG_SEL_processor_jtag_sel_END    (0)
#define SOC_SCTRL_SCJTAG_SEL_dsp_jtag_sel_START        (1)
#define SOC_SCTRL_SCJTAG_SEL_dsp_jtag_sel_END          (2)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCMODEM_KEY0_UNION
 �ṹ˵��  : SCMODEM_KEY0 �Ĵ����ṹ���塣��ַƫ����:0x804����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM_KEY0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_key0 : 32; /* bit[0-31]: modem_key0�� */
    } reg;
} SOC_SCTRL_SCMODEM_KEY0_UNION;
#endif
#define SOC_SCTRL_SCMODEM_KEY0_modem_key0_START  (0)
#define SOC_SCTRL_SCMODEM_KEY0_modem_key0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCMODEM_KEY1_UNION
 �ṹ˵��  : SCMODEM_KEY1 �Ĵ����ṹ���塣��ַƫ����:0x808����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM_KEY1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_key1 : 32; /* bit[0-31]: modem_key1�� */
    } reg;
} SOC_SCTRL_SCMODEM_KEY1_UNION;
#endif
#define SOC_SCTRL_SCMODEM_KEY1_modem_key1_START  (0)
#define SOC_SCTRL_SCMODEM_KEY1_modem_key1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCMODEM_KEY2_UNION
 �ṹ˵��  : SCMODEM_KEY2 �Ĵ����ṹ���塣��ַƫ����:0x80C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM_KEY2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_key2 : 32; /* bit[0-31]: modem_key2�� */
    } reg;
} SOC_SCTRL_SCMODEM_KEY2_UNION;
#endif
#define SOC_SCTRL_SCMODEM_KEY2_modem_key2_START  (0)
#define SOC_SCTRL_SCMODEM_KEY2_modem_key2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCMODEM_KEY3_UNION
 �ṹ˵��  : SCMODEM_KEY3 �Ĵ����ṹ���塣��ַƫ����:0x810����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM_KEY3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_key3 : 32; /* bit[0-31]: modem_key3�� */
    } reg;
} SOC_SCTRL_SCMODEM_KEY3_UNION;
#endif
#define SOC_SCTRL_SCMODEM_KEY3_modem_key3_START  (0)
#define SOC_SCTRL_SCMODEM_KEY3_modem_key3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCFG_DJTAG_UNION
 �ṹ˵��  : SCCFG_DJTAG �Ĵ����ṹ���塣��ַƫ����:0x814����ֵ:0x00000000�����:32
 �Ĵ���˵��: DJTAG���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_djtag : 1;  /* bit[0]   : 1��djtag disable
                                                    0��normal
                                                    дһ��������������֤ͨ�������ݲ���д�벢��ֻ�е�efuse_djtag_ctrlΪ2'b01ʱ��cfg_djtag�������djtag_disable�� */
        unsigned int  reserved  : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCCFG_DJTAG_UNION;
#endif
#define SOC_SCTRL_SCCFG_DJTAG_cfg_djtag_START  (0)
#define SOC_SCTRL_SCCFG_DJTAG_cfg_djtag_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCP15_DISABLE_UNION
 �ṹ˵��  : SCCP15_DISABLE �Ĵ����ṹ���塣��ַƫ����:0x818����ֵ:0x00000000�����:32
 �Ĵ���˵��: CP15DISABLE���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cp15disable0 : 1;  /* bit[0]    : A53 CPU0�Ŀ���bit��д1������CPU0��λ�����ؽ����� */
        unsigned int  a53_cp15disable1 : 1;  /* bit[1]    : A53 CPU1�Ŀ���bit��д1������CPU1��λ�����ؽ����� */
        unsigned int  a53_cp15disable2 : 1;  /* bit[2]    : A53 CPU2�Ŀ���bit��д1������CPU2��λ�����ؽ����� */
        unsigned int  a53_cp15disable3 : 1;  /* bit[3]    : A53 CPU3�Ŀ���bit��д1������CPU3��λ�����ؽ����� */
        unsigned int  a57_cp15disable0 : 1;  /* bit[4]    : A57 CPU0�Ŀ���bit��д1������CPU0��λ�����ؽ����� */
        unsigned int  a57_cp15disable1 : 1;  /* bit[5]    : A57 CPU1�Ŀ���bit��д1������CPU1��λ�����ؽ����� */
        unsigned int  a57_cp15disable2 : 1;  /* bit[6]    : A57 CPU2�Ŀ���bit��д1������CPU2��λ�����ؽ����� */
        unsigned int  a57_cp15disable3 : 1;  /* bit[7]    : A57 CPU3�Ŀ���bit��д1������CPU3��λ�����ؽ����� */
        unsigned int  ispa7cp15disable : 1;  /* bit[8]    : ISPA7 CPU�Ŀ���bit��д1������CPU��λ�����ؽ����� */
        unsigned int  gicdisable       : 1;  /* bit[9]    : GIC�Ŀ���bit��д1������GIC��λ�����ؽ����� */
        unsigned int  reserved         : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_SCTRL_SCCP15_DISABLE_UNION;
#endif
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable0_START  (0)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable0_END    (0)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable1_START  (1)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable1_END    (1)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable2_START  (2)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable2_END    (2)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable3_START  (3)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable3_END    (3)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable0_START  (4)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable0_END    (4)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable1_START  (5)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable1_END    (5)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable2_START  (6)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable2_END    (6)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable3_START  (7)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable3_END    (7)
#define SOC_SCTRL_SCCP15_DISABLE_ispa7cp15disable_START  (8)
#define SOC_SCTRL_SCCP15_DISABLE_ispa7cp15disable_END    (8)
#define SOC_SCTRL_SCCP15_DISABLE_gicdisable_START        (9)
#define SOC_SCTRL_SCCP15_DISABLE_gicdisable_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCLKCNTSTAT_UNION
 �ṹ˵��  : SCCLKCNTSTAT �Ĵ����ṹ���塣��ַƫ����:0x81C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ�Ӽ���״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_stat : 16; /* bit[0-15] : clk_monitorģ��ʱ�Ӽ���״̬�Ĵ�������clk_cnt_en = 1'b1����32KHz˯��ʱ���������½���ʱ���£��������ά�ֲ��䡣 */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SCTRL_SCCLKCNTSTAT_UNION;
#endif
#define SOC_SCTRL_SCCLKCNTSTAT_cnt_stat_START  (0)
#define SOC_SCTRL_SCCLKCNTSTAT_cnt_stat_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCLKCNTCFG_UNION
 �ṹ˵��  : SCCLKCNTCFG �Ĵ����ṹ���塣��ַƫ����:0x820����ֵ:0x40000340�����:32
 �Ĵ���˵��: ʱ�Ӽ������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_cfg        : 16; /* bit[0-15] : clk_monitorģ��ʱ�Ӽ������üĴ����� */
        unsigned int  timer_secu_en  : 1;  /* bit[16]   : AO��TIMER1��ȫ���ƣ�ʹ��ʱTIMER1��ʱ����Ч����λ���룬timer_clk_en2��timer_clk_en3Ϊ32KHZʱ��
                                                          0����ȫ���Ʋ�ʹ�ܣ�timer2,3��ѡ��32K��TCXO��4��Ƶʱ�ӣ�
                                                          1����ȫ����ʹ�ܣ�timer2,3��ֻʹ��32Kʱ�ӣ����Ҵ�ʱtimer2,3�޷��޸��ſ�ʹ�ܡ� */
        unsigned int  reserved       : 13; /* bit[17-29]: ������ */
        unsigned int  clk_cnt_en     : 1;  /* bit[30]   : clk_cntʹ�����á�
                                                          0����ʹ��
                                                          1��ʹ�ܡ� */
        unsigned int  clk_monitor_en : 1;  /* bit[31]   : clk_monitorģ��ʹ�����á�
                                                          0����ʹ��
                                                          1��ʹ��
                                                          ע��Ҫ������cnt_cfg[15:0]��������clk_monitor_en�� */
    } reg;
} SOC_SCTRL_SCCLKCNTCFG_UNION;
#endif
#define SOC_SCTRL_SCCLKCNTCFG_cnt_cfg_START         (0)
#define SOC_SCTRL_SCCLKCNTCFG_cnt_cfg_END           (15)
#define SOC_SCTRL_SCCLKCNTCFG_timer_secu_en_START   (16)
#define SOC_SCTRL_SCCLKCNTCFG_timer_secu_en_END     (16)
#define SOC_SCTRL_SCCLKCNTCFG_clk_cnt_en_START      (30)
#define SOC_SCTRL_SCCLKCNTCFG_clk_cnt_en_END        (30)
#define SOC_SCTRL_SCCLKCNTCFG_clk_monitor_en_START  (31)
#define SOC_SCTRL_SCCLKCNTCFG_clk_monitor_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCLKMONCTRL_UNION
 �ṹ˵��  : SCCLKMONCTRL �Ĵ����ṹ���塣��ַƫ����:0x824����ֵ:0x00000002�����:32
 �Ĵ���˵��: ʱ�Ӽ�ؿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_clr  : 1;  /* bit[0]   : �ж����
                                                    0�������ж�
                                                    1�����ж�
                                                    ע��д1֮��Ҫ��д0�������һֱ�������жϵ�״̬�� */
        unsigned int  intr_mask : 1;  /* bit[1]   : �ж�����
                                                    0���������ж�
                                                    1�������жϡ� */
        unsigned int  reserved  : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_SCTRL_SCCLKMONCTRL_UNION;
#endif
#define SOC_SCTRL_SCCLKMONCTRL_intr_clr_START   (0)
#define SOC_SCTRL_SCCLKMONCTRL_intr_clr_END     (0)
#define SOC_SCTRL_SCCLKMONCTRL_intr_mask_START  (1)
#define SOC_SCTRL_SCCLKMONCTRL_intr_mask_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCLKMONINT_UNION
 �ṹ˵��  : SCCLKMONINT �Ĵ����ṹ���塣��ַƫ����:0x828����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ�Ӽ���ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  raw_intr : 1;  /* bit[0]   : �ж�ָʾ
                                                   0�����ж�
                                                   1�����жϡ� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCCLKMONINT_UNION;
#endif
#define SOC_SCTRL_SCCLKMONINT_raw_intr_START  (0)
#define SOC_SCTRL_SCCLKMONINT_raw_intr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCFG_ARM_DBGEN_UNION
 �ṹ˵��  : SCCFG_ARM_DBGEN �Ĵ����ṹ���塣��ַƫ����:0x82C����ֵ:0x00000002�����:32
 �Ĵ���˵��: ARM debug en���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_arm_dbgen : 4;  /* bit[0-3] : ARM debugen���á�����ϵͳ�Ĵ����߼�����ÿ���ϵ縴λ֮���ֵֻ��дһ�Ρ���
                                                        [3:0]={spniden,spiden,niden,dbgen}
                                                        0:disable 1:enable�� */
        unsigned int  reserved      : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCCFG_ARM_DBGEN_UNION;
#endif
#define SOC_SCTRL_SCCFG_ARM_DBGEN_cfg_arm_dbgen_START  (0)
#define SOC_SCTRL_SCCFG_ARM_DBGEN_cfg_arm_dbgen_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCARM_DBG_KEY0_UNION
 �ṹ˵��  : SCARM_DBG_KEY0 �Ĵ����ṹ���塣��ַƫ����:0x830����ֵ:0x00000000�����:32
 �Ĵ���˵��: ARM debug key0���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arm_dbg_key0 : 32; /* bit[0-31]: arm_dbg_key�ĵ�32λ������ϵͳ�Ĵ����߼�����ÿ���ϵ縴λ֮���ֵֻ��д3�Σ��� */
    } reg;
} SOC_SCTRL_SCARM_DBG_KEY0_UNION;
#endif
#define SOC_SCTRL_SCARM_DBG_KEY0_arm_dbg_key0_START  (0)
#define SOC_SCTRL_SCARM_DBG_KEY0_arm_dbg_key0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCARM_DBG_KEY1_UNION
 �ṹ˵��  : SCARM_DBG_KEY1 �Ĵ����ṹ���塣��ַƫ����:0x834����ֵ:0x00000000�����:32
 �Ĵ���˵��: ARM debug key1���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arm_dbg_key1 : 32; /* bit[0-31]: arm_dbg_key�ĸ�32λ������ϵͳ�Ĵ����߼�����ÿ���ϵ縴λ֮���ֵֻ��д3�Σ��� */
    } reg;
} SOC_SCTRL_SCARM_DBG_KEY1_UNION;
#endif
#define SOC_SCTRL_SCARM_DBG_KEY1_arm_dbg_key1_START  (0)
#define SOC_SCTRL_SCARM_DBG_KEY1_arm_dbg_key1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCARM_DBGEN_STAT_UNION
 �ṹ˵��  : SCARM_DBGEN_STAT �Ĵ����ṹ���塣��ַƫ����:0x838����ֵ:0x00000000�����:32
 �Ĵ���˵��: ARM debug en״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arm_dbgen_wr : 1;  /* bit[0]   : ARM debugen wr״̬�Ĵ�����
                                                       0����ǰ����дcfg_arm_dbgen�Ĵ�����1����ǰ��дcfg_arm_dbgen�Ĵ����� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCARM_DBGEN_STAT_UNION;
#endif
#define SOC_SCTRL_SCARM_DBGEN_STAT_arm_dbgen_wr_START  (0)
#define SOC_SCTRL_SCARM_DBGEN_STAT_arm_dbgen_wr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCEFUSECTRL_UNION
 �ṹ˵��  : SCEFUSECTRL �Ĵ����ṹ���塣��ַƫ����:0x83C����ֵ:0x00000000�����:32
 �Ĵ���˵��: EFUSE PAD��д���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sys_efuse_pad_sel : 1;  /* bit[0]   : 0��PAD��д��
                                                            1�������д�� */
        unsigned int  reserved          : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCEFUSECTRL_UNION;
#endif
#define SOC_SCTRL_SCEFUSECTRL_sys_efuse_pad_sel_START  (0)
#define SOC_SCTRL_SCEFUSECTRL_sys_efuse_pad_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCEFUSESEL_UNION
 �ṹ˵��  : SCEFUSESEL �Ĵ����ṹ���塣��ַƫ����:0x840����ֵ:0x00000000�����:32
 �Ĵ���˵��: SECSʱ���ſؼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_secs : 1;  /* bit[0]   : secsʱ���ſؿ��ƣ�
                                                      0��IPʱ�ӽ�ֹ��
                                                      1��IPʱ��ʹ�ܡ� */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCEFUSESEL_UNION;
#endif
#define SOC_SCTRL_SCEFUSESEL_gt_clk_secs_START  (0)
#define SOC_SCTRL_SCEFUSESEL_gt_clk_secs_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCSECURITYSTAT_UNION
 �ṹ˵��  : SCSECURITYSTAT �Ĵ����ṹ���塣��ַƫ����:0x844����ֵ:0x00000000�����:32
 �Ĵ���˵��: EFUSE SECURITY״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emmc_sel : 1;  /* bit[0]   : ����efuse��emmc_selָʾ
                                                   0��emmc5.0
                                                   1��emmc4.5�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCSECURITYSTAT_UNION;
#endif
#define SOC_SCTRL_SCSECURITYSTAT_emmc_sel_START  (0)
#define SOC_SCTRL_SCSECURITYSTAT_emmc_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCHIP_ID0_UNION
 �ṹ˵��  : SCCHIP_ID0 �Ĵ����ṹ���塣��ַƫ����:0x848����ֵ:0x00000000�����:32
 �Ĵ���˵��: EFUSE CHIP_ID0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CHIP_ID0 : 32; /* bit[0-31]: CHIP_ID��32bit�� */
    } reg;
} SOC_SCTRL_SCCHIP_ID0_UNION;
#endif
#define SOC_SCTRL_SCCHIP_ID0_CHIP_ID0_START  (0)
#define SOC_SCTRL_SCCHIP_ID0_CHIP_ID0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCHIP_ID1_UNION
 �ṹ˵��  : SCCHIP_ID1 �Ĵ����ṹ���塣��ַƫ����:0x84C����ֵ:0x00000000�����:32
 �Ĵ���˵��: EFUSE CHIP_ID1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CHIP_ID1 : 32; /* bit[0-31]: CHIP_ID��32bit�� */
    } reg;
} SOC_SCTRL_SCCHIP_ID1_UNION;
#endif
#define SOC_SCTRL_SCCHIP_ID1_CHIP_ID1_START  (0)
#define SOC_SCTRL_SCCHIP_ID1_CHIP_ID1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCCPUSECCTRL_UNION
 �ṹ˵��  : SCCPUSECCTRL �Ĵ����ṹ���塣��ַƫ����:0x850����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU��ȫ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cryptodisable : 4;  /* bit[0-3] : ���˼�������disable
                                                            0��Enable the Cryptography engine��
                                                            1��Disable the Cryptography engine�� */
        unsigned int  a57_cryptodisable : 4;  /* bit[4-7] : ���˼�������disable
                                                            0��Enable the Cryptography engine��
                                                            1��Disable the Cryptography engine�� */
        unsigned int  reserved          : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_SCTRL_SCCPUSECCTRL_UNION;
#endif
#define SOC_SCTRL_SCCPUSECCTRL_a53_cryptodisable_START  (0)
#define SOC_SCTRL_SCCPUSECCTRL_a53_cryptodisable_END    (3)
#define SOC_SCTRL_SCCPUSECCTRL_a57_cryptodisable_START  (4)
#define SOC_SCTRL_SCCPUSECCTRL_a57_cryptodisable_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPEREN0_SEC_UNION
 �ṹ˵��  : SCPEREN0_SEC �Ĵ����ṹ���塣��ַƫ����:0x900����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���0����ȫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_timer1    : 1;  /* bit[0]    : ����ʱ��ʹ�ܿ��ƣ�
                                                             0��д0��Ч����
                                                             1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_timer1     : 1;  /* bit[1]    : ����ͬbit0�� */
        unsigned int  gt_clk_clkmonitor : 1;  /* bit[2]    : ����ͬbit0�� */
        unsigned int  gt_clk_ao_cc      : 1;  /* bit[3]    : ����ͬbit0�� */
        unsigned int  reserved          : 16; /* bit[4-19] : ����ͬbit0�� */
        unsigned int  mmbuf_sec_ctrl    : 12; /* bit[20-31]: ��ȫ���ƣ�
                                                             0��д0��Ч����
                                                             1��SCPERCLKEN0_SEC.mmbuf_sec_ctrl��Ӧbit��1�� */
    } reg;
} SOC_SCTRL_SCPEREN0_SEC_UNION;
#endif
#define SOC_SCTRL_SCPEREN0_SEC_gt_pclk_timer1_START     (0)
#define SOC_SCTRL_SCPEREN0_SEC_gt_pclk_timer1_END       (0)
#define SOC_SCTRL_SCPEREN0_SEC_gt_clk_timer1_START      (1)
#define SOC_SCTRL_SCPEREN0_SEC_gt_clk_timer1_END        (1)
#define SOC_SCTRL_SCPEREN0_SEC_gt_clk_clkmonitor_START  (2)
#define SOC_SCTRL_SCPEREN0_SEC_gt_clk_clkmonitor_END    (2)
#define SOC_SCTRL_SCPEREN0_SEC_gt_clk_ao_cc_START       (3)
#define SOC_SCTRL_SCPEREN0_SEC_gt_clk_ao_cc_END         (3)
#define SOC_SCTRL_SCPEREN0_SEC_mmbuf_sec_ctrl_START     (20)
#define SOC_SCTRL_SCPEREN0_SEC_mmbuf_sec_ctrl_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERDIS0_SEC_UNION
 �ṹ˵��  : SCPERDIS0_SEC �Ĵ����ṹ���塣��ַƫ����:0x904����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���0����ȫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_timer1    : 1;  /* bit[0]    : ����ʱ�ӽ�ֹ���ƣ�
                                                             0��д0��Ч����
                                                             1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_timer1     : 1;  /* bit[1]    : ����ͬbit0�� */
        unsigned int  gt_clk_clkmonitor : 1;  /* bit[2]    : ����ͬbit0�� */
        unsigned int  gt_clk_ao_cc      : 1;  /* bit[3]    : ����ͬbit0�� */
        unsigned int  reserved          : 16; /* bit[4-19] : ����ͬbit0�� */
        unsigned int  mmbuf_sec_ctrl    : 12; /* bit[20-31]: ��ȫ���ƣ�
                                                             0��д0��Ч����
                                                             1��SCPERCLKEN0_SEC.mmbuf_sec_ctrl��Ӧbit��0�� */
    } reg;
} SOC_SCTRL_SCPERDIS0_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERDIS0_SEC_gt_pclk_timer1_START     (0)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_pclk_timer1_END       (0)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_clk_timer1_START      (1)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_clk_timer1_END        (1)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_clk_clkmonitor_START  (2)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_clk_clkmonitor_END    (2)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_clk_ao_cc_START       (3)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_clk_ao_cc_END         (3)
#define SOC_SCTRL_SCPERDIS0_SEC_mmbuf_sec_ctrl_START     (20)
#define SOC_SCTRL_SCPERDIS0_SEC_mmbuf_sec_ctrl_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERCLKEN0_SEC_UNION
 �ṹ˵��  : SCPERCLKEN0_SEC �Ĵ����ṹ���塣��ַƫ����:0x908����ֵ:0x003FFFFF�����:32
 �Ĵ���˵��: ����ʱ��ʹ��״̬�Ĵ���0����ȫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_timer1    : 1;  /* bit[0]    : ����ʱ��ʹ��״̬��
                                                             0��IPʱ��ʹ�ܳ���״̬��
                                                             1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_timer1     : 1;  /* bit[1]    : ����ͬbit0�� */
        unsigned int  gt_clk_clkmonitor : 1;  /* bit[2]    : ����ͬbit0�� */
        unsigned int  gt_clk_ao_cc      : 1;  /* bit[3]    : ����ͬbit0�� */
        unsigned int  reserved          : 16; /* bit[4-19] : ����ͬbit0�� */
        unsigned int  mmbuf_sec_ctrl    : 12; /* bit[20-31]: ��ȫ״̬
                                                             tzpcdecprot5[20] ENABLE_FIREWALL 
                                                             0��disable firewall
                                                             1�� enable firewall
                                                             tzpcdecprot5[21] ERR_RESP 
                                                             0�� disable err resp
                                                             1�� enable err resp
                                                             tzpcdecprot5[22] REGION0_IS_SEC(0xea800000~0xea80c7ff) 0����ȫ��1���ǰ�ȫ
                                                             tzpcdecprot5[23] REGION1_IS_SEC(0xea80c800~0xea818fff) 0����ȫ��1���ǰ�ȫ
                                                             tzpcdecprot5[24] REGION2_IS_SEC(0xea819000~0xea8257ff) 0����ȫ��1���ǰ�ȫ
                                                             tzpcdecprot5[25] REGION3_IS_SEC(0xea825800~0xea831fff) 0����ȫ��1���ǰ�ȫ
                                                             tzpcdecprot5[26] REGION4_IS_SEC(0xea832000~0xea83e7ff) 0����ȫ��1���ǰ�ȫ
                                                             tzpcdecprot5[27] REGION5_IS_SEC(0xea83e800~0xea84afff) 0����ȫ��1���ǰ�ȫ
                                                             tzpcdecprot5[28] REGION6_IS_SEC(0xea84b000~0xea8577ff) 0����ȫ��1���ǰ�ȫ
                                                             tzpcdecprot5[29] REGION7_IS_SEC(0xea857800~0xea863fff) 0����ȫ��1���ǰ�ȫ
                                                             tzpcdecprot5[30] Reserved Ĭ�ϰ�ȫ
                                                             tzpcdecprot5[31] Reserved Ĭ�ϰ�ȫ�� */
    } reg;
} SOC_SCTRL_SCPERCLKEN0_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_pclk_timer1_START     (0)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_pclk_timer1_END       (0)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_clk_timer1_START      (1)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_clk_timer1_END        (1)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_clk_clkmonitor_START  (2)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_clk_clkmonitor_END    (2)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_clk_ao_cc_START       (3)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_clk_ao_cc_END         (3)
#define SOC_SCTRL_SCPERCLKEN0_SEC_mmbuf_sec_ctrl_START     (20)
#define SOC_SCTRL_SCPERCLKEN0_SEC_mmbuf_sec_ctrl_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTEN0_SEC_UNION
 �ṹ˵��  : SCPERRSTEN0_SEC �Ĵ����ṹ���塣��ַƫ����:0x950����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���0����ȫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_timer1 : 1;  /* bit[0]   : IP��λʹ�ܣ�
                                                        0��IP��λʹ��״̬���䣻
                                                        1��IP��λʹ�ܡ� */
        unsigned int  ip_rst_asc    : 1;  /* bit[1]   : ����ͬbit0�� */
        unsigned int  reserved_0    : 1;  /* bit[2]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_cc  : 1;  /* bit[3]   : ����ͬbit0�� */
        unsigned int  reserved_1    : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTEN0_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTEN0_SEC_ip_rst_timer1_START  (0)
#define SOC_SCTRL_SCPERRSTEN0_SEC_ip_rst_timer1_END    (0)
#define SOC_SCTRL_SCPERRSTEN0_SEC_ip_rst_asc_START     (1)
#define SOC_SCTRL_SCPERRSTEN0_SEC_ip_rst_asc_END       (1)
#define SOC_SCTRL_SCPERRSTEN0_SEC_ip_rst_ao_cc_START   (3)
#define SOC_SCTRL_SCPERRSTEN0_SEC_ip_rst_ao_cc_END     (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTDIS0_SEC_UNION
 �ṹ˵��  : SCPERRSTDIS0_SEC �Ĵ����ṹ���塣��ַƫ����:0x954����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���0����ȫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_timer1 : 1;  /* bit[0]   : IP��λ���룺
                                                        0��IP��λʹ��״̬���䣻
                                                        1��IP��λ���롣 */
        unsigned int  ip_rst_asc    : 1;  /* bit[1]   : ����ͬbit0�� */
        unsigned int  reserved_0    : 1;  /* bit[2]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_cc  : 1;  /* bit[3]   : ����ͬbit0�� */
        unsigned int  reserved_1    : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTDIS0_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ip_rst_timer1_START  (0)
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ip_rst_timer1_END    (0)
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ip_rst_asc_START     (1)
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ip_rst_asc_END       (1)
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ip_rst_ao_cc_START   (3)
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ip_rst_ao_cc_END     (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTSTAT0_SEC_UNION
 �ṹ˵��  : SCPERRSTSTAT0_SEC �Ĵ����ṹ���塣��ַƫ����:0x958����ֵ:0x00000002�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���0����ȫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_timer1 : 1;  /* bit[0]   : ������λʹ��״̬��
                                                        0��IP��λʹ�ܳ�����
                                                        1��IP��λʹ�ܡ� */
        unsigned int  ip_rst_asc    : 1;  /* bit[1]   : ����ͬbit0�� */
        unsigned int  reserved_0    : 1;  /* bit[2]   : ����ͬbit0�� */
        unsigned int  ip_rst_ao_cc  : 1;  /* bit[3]   : ����ͬbit0�� */
        unsigned int  reserved_1    : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTSTAT0_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ip_rst_timer1_START  (0)
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ip_rst_timer1_END    (0)
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ip_rst_asc_START     (1)
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ip_rst_asc_END       (1)
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ip_rst_ao_cc_START   (3)
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ip_rst_ao_cc_END     (3)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCTIMERCTRL_SEC_UNION
 �ṹ˵��  : SCTIMERCTRL_SEC �Ĵ����ṹ���塣��ַƫ����:0x9A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫTIMER���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeren2sel    : 1;  /* bit[0]   : Time2ʱ��ʹ�ܲο�ʱ��ѡ��
                                                         0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                         1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren2ov     : 1;  /* bit[1]   : Timer2ʱ��ʹ�ܿ��ơ�
                                                         0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren2sel]ָ����
                                                         1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren3sel    : 1;  /* bit[2]   : Time3ʱ��ʹ�ܲο�ʱ��ѡ��
                                                         0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                         1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren3ov     : 1;  /* bit[3]   : Timer3ʱ��ʹ�ܿ��ơ�
                                                         0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren3sel]ָ����
                                                         1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  reserved       : 27; /* bit[4-30]: ������ */
        unsigned int  timerforcehigh : 1;  /* bit[31]  : Timer23ʹ�ܶ�ǿ�����ߵ�Ӳ��ʹ�����á�
                                                         0��Ӳ���������Զ�������
                                                         1����ϵͳʱ����32Kʱ��Ӳ���Զ�ǿ������Timer23��ʹ�ܡ� */
    } reg;
} SOC_SCTRL_SCTIMERCTRL_SEC_UNION;
#endif
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren2sel_START     (0)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren2sel_END       (0)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren2ov_START      (1)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren2ov_END        (1)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren3sel_START     (2)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren3sel_END       (2)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren3ov_START      (3)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren3ov_END        (3)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timerforcehigh_START  (31)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timerforcehigh_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTEN1_SEC_UNION
 �ṹ˵��  : SCPERRSTEN1_SEC �Ĵ����ṹ���塣��ַƫ����:0xA50����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���1����ȫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_asp_subsys : 1;  /* bit[0]   : IP��λʹ�ܣ�
                                                            0��IP��λʹ��״̬���䣻
                                                            1��IP��λʹ�ܡ� */
        unsigned int  reserved          : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTEN1_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTEN1_SEC_ip_rst_asp_subsys_START  (0)
#define SOC_SCTRL_SCPERRSTEN1_SEC_ip_rst_asp_subsys_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTDIS1_SEC_UNION
 �ṹ˵��  : SCPERRSTDIS1_SEC �Ĵ����ṹ���塣��ַƫ����:0xA54����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���1����ȫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_asp_subsys : 1;  /* bit[0]   : IP��λ���룺
                                                            0��IP��λʹ��״̬���䣻
                                                            1��IP��λ���롣 */
        unsigned int  reserved          : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTDIS1_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTDIS1_SEC_ip_rst_asp_subsys_START  (0)
#define SOC_SCTRL_SCPERRSTDIS1_SEC_ip_rst_asp_subsys_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTSTAT1_SEC_UNION
 �ṹ˵��  : SCPERRSTSTAT1_SEC �Ĵ����ṹ���塣��ַƫ����:0xA58����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���1����ȫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_asp_subsys : 1;  /* bit[0]   : �������crg��rsten2[0]
                                                            ������λʹ��״̬��
                                                            0��IP��λʹ�ܳ�����
                                                            1��IP��λʹ�ܡ� */
        unsigned int  reserved          : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTSTAT1_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTSTAT1_SEC_ip_rst_asp_subsys_START  (0)
#define SOC_SCTRL_SCPERRSTSTAT1_SEC_ip_rst_asp_subsys_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTEN2_SEC_UNION
 �ṹ˵��  : SCPERRSTEN2_SEC �Ĵ����ṹ���塣��ַƫ����:0xB50����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���2����ȫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_iomcu : 1;  /* bit[0]   : IP��λʹ�ܣ�
                                                       0��IP��λʹ��״̬���䣻
                                                       1��IP��λʹ�ܡ� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTEN2_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTEN2_SEC_ip_rst_iomcu_START  (0)
#define SOC_SCTRL_SCPERRSTEN2_SEC_ip_rst_iomcu_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTDIS2_SEC_UNION
 �ṹ˵��  : SCPERRSTDIS2_SEC �Ĵ����ṹ���塣��ַƫ����:0xB54����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���2����ȫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_iomcu : 1;  /* bit[0]   : IP��λ���룺
                                                       0��IP��λʹ��״̬���䣻
                                                       1��IP��λ���롣 */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTDIS2_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTDIS2_SEC_ip_rst_iomcu_START  (0)
#define SOC_SCTRL_SCPERRSTDIS2_SEC_ip_rst_iomcu_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCPERRSTSTAT2_SEC_UNION
 �ṹ˵��  : SCPERRSTSTAT2_SEC �Ĵ����ṹ���塣��ַƫ����:0xB58����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���2����ȫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_iomcu : 1;  /* bit[0]   : �������crg��rsten2[1]
                                                       ������λʹ��״̬��
                                                       0��IP��λʹ�ܳ�����
                                                       1��IP��λʹ�ܡ� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SCTRL_SCPERRSTSTAT2_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTSTAT2_SEC_ip_rst_iomcu_START  (0)
#define SOC_SCTRL_SCPERRSTSTAT2_SEC_ip_rst_iomcu_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCTRL_SCSOCID0_UNION
 �ṹ˵��  : SCSOCID0 �Ĵ����ṹ���塣��ַƫ����:0xE00����ֵ:0x36500100�����:32
 �Ĵ���˵��: SOCID�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  version_code : 16; /* bit[0-15] : 0x0100��оƬ�İ汾�š�
                                                        ASICʹ�ã�TSMC16FF_TSMC_MEM ��Ĭ��ֵΪ0x36500100
                                                        FPGAʹ�ã� FPGA_XILINX ��Ĭ��ֵΪ 0x36501000
                                                        emulatorʹ�ã�EMULATOR_VERSION �� Ĭ��ֵΪ 0x36502000�� */
        unsigned int  chip_code    : 16; /* bit[16-31]: 0x3650��оƬ�ı�� */
    } reg;
} SOC_SCTRL_SCSOCID0_UNION;
#endif
#define SOC_SCTRL_SCSOCID0_version_code_START  (0)
#define SOC_SCTRL_SCSOCID0_version_code_END    (15)
#define SOC_SCTRL_SCSOCID0_chip_code_START     (16)
#define SOC_SCTRL_SCSOCID0_chip_code_END       (31)






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

#endif /* end of soc_sctrl_interface.h */
