/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : phy_abb_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-08-06 17:27:13
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��8��6��
    ��    ��   : x00347325
    �޸�����   : �ӡ�TV300 ABB�Ĵ�������V1.2(nManager3.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __ABB_INTERFACE_TV300_H__
#define __ABB_INTERFACE_TV300_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define ABB_BASE_ADDR               ( 0x0000 )

/***======================================================================***
                     (1/1) register_define_ssi_reg
 ***======================================================================***/
/* �Ĵ���˵����RX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             Others��Reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11��reserved��
   UNION�ṹ:  ABB_RX_2G_DIG_1_UNION */
#define ABB_RX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x0)

/* �Ĵ���˵����RX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_2G_DIG_2_UNION */
#define ABB_RX_2G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x1)

/* �Ĵ���˵����TX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2��-------,--------,15.36MHz,--------,--------
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��)
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_2G_DIG_1_UNION */
#define ABB_TX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x2)

/* �Ĵ���˵����TX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ (Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_2G_DIG_2_UNION */
#define ABB_TX_2G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x3)

/* �Ĵ���˵����TX 2Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_TX_2G_DIG_3_UNION */
#define ABB_TX_2G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x4)

/* �Ĵ���˵����CH0 RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             Others��Reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11��reserved��
   UNION�ṹ:  ABB_RX_CH0_3G_DIG_1_UNION */
#define ABB_RX_CH0_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x5)

/* �Ĵ���˵����CH0 RX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_CH0_3G_DIG_2_UNION */
#define ABB_RX_CH0_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x6)

/* �Ĵ���˵����CH0 TX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2��-------,--------,15.36MHz,--------,--------
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_CH0_3G_DIG_1_UNION */
#define ABB_TX_CH0_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x7)

/* �Ĵ���˵����CH0 TX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ(Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_CH0_3G_DIG_2_UNION */
#define ABB_TX_CH0_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x8)

/* �Ĵ���˵����CH0 TX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_TX_CH0_3G_DIG_3_UNION */
#define ABB_TX_CH0_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x9)

/* �Ĵ���˵����CH0 RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             Others��Reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11��reserved��
   UNION�ṹ:  ABB_RX_CH0_4G_DIG_1_UNION */
#define ABB_RX_CH0_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0xA)

/* �Ĵ���˵����CH0 RX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_CH0_4G_DIG_2_UNION */
#define ABB_RX_CH0_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0xB)

/* �Ĵ���˵����CH0 TX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2��-------,--------,15.36MHz,--------,--------
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_CH0_4G_DIG_1_UNION */
#define ABB_TX_CH0_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0xC)

/* �Ĵ���˵����CH0 TX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ(Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_CH0_4G_DIG_2_UNION */
#define ABB_TX_CH0_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0xD)

/* �Ĵ���˵����CH0 TX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_TX_CH0_4G_DIG_3_UNION */
#define ABB_TX_CH0_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0xE)

/* �Ĵ���˵����RX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             Others��Reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11��reserved��
   UNION�ṹ:  ABB_RX_TDS_DIG_1_UNION */
#define ABB_RX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0xF)

/* �Ĵ���˵����RX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_TDS_DIG_2_UNION */
#define ABB_RX_TDS_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x10)

/* �Ĵ���˵����TX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXģʽ���ƣ�
             000��2G
             001��3G
             010��4G &amp; ET &amp; APT
             011��TDS(Ĭ��)
             Others��CA
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2��-------,--------,15.36MHz,--------,--------
             Others��Reserved
 bit[1]      TXͨ������˲�����bypass�ź�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_TDS_DIG_1_UNION */
#define ABB_TX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0x11)

/* �Ĵ���˵����TX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ(Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_TDS_DIG_2_UNION */
#define ABB_TX_TDS_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x12)

/* �Ĵ���˵����TX TDSģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_TX_TDS_DIG_3_UNION */
#define ABB_TX_TDS_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x13)

/* �Ĵ���˵����CH1 RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             Others��Reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11��reserved��
   UNION�ṹ:  ABB_RX_CH1_4G_DIG_1_UNION */
#define ABB_RX_CH1_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x1A)

/* �Ĵ���˵����CH1 RX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_CH1_4G_DIG_2_UNION */
#define ABB_RX_CH1_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x1B)

/* �Ĵ���˵����CH1 TX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2��-------,--------,15.36MHz,--------,--------
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_CH1_4G_DIG_1_UNION */
#define ABB_TX_CH1_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x1C)

/* �Ĵ���˵����CH1 TX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ(Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_CH1_4G_DIG_2_UNION */
#define ABB_TX_CH1_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x1D)

/* �Ĵ���˵����CH1 TX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_TX_CH1_4G_DIG_3_UNION */
#define ABB_TX_CH1_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x1E)

/* �Ĵ���˵����RX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SC
             010��4G &amp; ET &amp; APT
             011��3G_DC
             100��TDS
             Others��CA
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11��reserved��
   UNION�ṹ:  ABB_RX_IDLE_DIG_1_UNION */
#define ABB_RX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x1F)

/* �Ĵ���˵����RX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_IDLE_DIG_2_UNION */
#define ABB_RX_IDLE_DIG_2_ADDR                        (ABB_BASE_ADDR + 0x20)

/* �Ĵ���˵����TX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2��-------,--------,15.36MHz,--------,--------
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_IDLE_DIG_1_UNION */
#define ABB_TX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x21)

/* �Ĵ���˵����TX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ(Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_IDLE_DIG_2_UNION */
#define ABB_TX_IDLE_DIG_2_ADDR                        (ABB_BASE_ADDR + 0x22)

/* �Ĵ���˵����TX IDLEģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_TX_IDLE_DIG_3_UNION */
#define ABB_TX_IDLE_DIG_3_ADDR                        (ABB_BASE_ADDR + 0x23)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr00��
   ��      ����RXA_I ADC Power Down����
            0��Power On
            1��Power Down(Ĭ��)
            (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ ���� */
#define ABB_RX_2G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x24)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������ch0_reg_analog_wr01��
   ��      ����Current Seting For Mode
            1x��LTE mode Current
            01��3G_DC &amp; X mode Current
            00��3G &amp; 2G mode Current
   UNION�ṹ ���� */
#define ABB_RX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x25)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������reg_analog_wr48��
   ��      ����TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
            000��14MHz
            001��28MHz
            010��9.3MHz
            011��18.7MHz
            100��7MHz(Ĭ��)
            101��14MHz
            110��28MHz
            111��56MHz
            Ĭ�����÷�����
            4G:001   2G:100   Others:000
   UNION�ṹ ���� */
#define ABB_TX_2G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x26)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������reg_analog_wr49��
   ��      ����{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
   UNION�ṹ ���� */
#define ABB_TX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x27)

/* �Ĵ���˵����CH0 RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr00��
   ��      ����RXA_I ADC Power Down����
            0��Power On
            1��Power Down(Ĭ��)
            (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ ���� */
#define ABB_RX_CH0_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x28)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr01��
   ��      ����Current Seting For Mode
            1x��LTE mode Current
            01��3G_DC &amp; X mode Current
            00��3G &amp; 2G mode Current
   UNION�ṹ ���� */
#define ABB_RX_CH0_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x29)

/* �Ĵ���˵����CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr48��
   ��      ����TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
            000��14MHz(Ĭ��)
            001��28MHz
            010��9.3MHz
            011��18.7MHz
            100��7MHz
            101��14MHz
            110��28MHz
            111��56MHz
            Ĭ�����÷�����
            4G:001   2G:100   Others:000
   UNION�ṹ ���� */
#define ABB_TX_CH0_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2A)

/* �Ĵ���˵����CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr49��
   ��      ����{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
   UNION�ṹ ���� */
#define ABB_TX_CH0_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2B)

/* �Ĵ���˵����CH0 RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr00��
   ��      ����RXA_I ADC Power Down����
            0��Power On
            1��Power Down(Ĭ��)
            (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ ���� */
#define ABB_RX_CH0_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2C)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr01��
   ��      ����Current Seting For Mode
            1x��LTE mode Current
            01��3G_DC &amp; X mode Current
            00��3G &amp; 2G mode Current
   UNION�ṹ ���� */
#define ABB_RX_CH0_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2D)

/* �Ĵ���˵����CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr48��
   ��      ����TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
            000��14MHz
            001��28MHz(Ĭ��)
            010��9.3MHz
            011��18.7MHz
            100��7MHz
            101��14MHz
            110��28MHz
            111��56MHz
            Ĭ�����÷�����
            4G:001   2G:100   Others:000
   UNION�ṹ ���� */
#define ABB_TX_CH0_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2E)

/* �Ĵ���˵����CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr49��
   ��      ����{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
   UNION�ṹ ���� */
#define ABB_TX_CH0_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2F)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr00��
   ��      ����RXA_I ADC Power Down����
            0��Power On
            1��Power Down(Ĭ��)
            (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ ���� */
#define ABB_RX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x30)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������ch0_reg_analog_wr01��
   ��      ����Current Seting For Mode
            1x��LTE mode Current
            01��3G_DC &amp; X mode Current
            00��3G &amp; 2G mode Current
   UNION�ṹ ���� */
#define ABB_RX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x31)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������reg_analog_wr48��
   ��      ����TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
            000��14MHz(Ĭ��)
            001��28MHz
            010��9.3MHz
            011��18.7MHz
            100��7MHz
            101��14MHz
            110��28MHz
            111��56MHz
            Ĭ�����÷�����
            4G:001   2G:100   Others:000
   UNION�ṹ ���� */
#define ABB_TX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x32)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������reg_analog_wr49��
   ��      ����{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
   UNION�ṹ ���� */
#define ABB_TX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x33)

/* �Ĵ���˵����CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr00��
   ��      ����RXA_I ADC Power Down����
            0��Power On
            1��Power Down(Ĭ��)
            (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ ���� */
#define ABB_RX_CH1_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x38)

/* �Ĵ���˵����CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr01��
   ��      ����Current Seting For Mode
            1x��LTE mode Current
            01��3G_DC &amp; X mode Current
            00��3G &amp; 2G mode Current
   UNION�ṹ ���� */
#define ABB_RX_CH1_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x39)

/* �Ĵ���˵����CH1 TX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr48��
   ��      ����TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
            000��14MHz
            001��28MHz(Ĭ��)
            010��9.3MHz
            011��18.7MHz
            100��7MHz
            101��14MHz
            110��28MHz
            111��56MHz
            Ĭ�����÷�����
            4G:001   2G:100   Others:000
   UNION�ṹ ���� */
#define ABB_TX_CH1_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x3A)

/* �Ĵ���˵����CH1 TX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr49��
   ��      ����{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
   UNION�ṹ ���� */
#define ABB_TX_CH1_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x3B)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr00��
   ��      ����RXA_I ADC Power Down����
            0��Power On
            1��Power Down(Ĭ��)
            (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ ���� */
#define ABB_RX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3C)

/* �Ĵ���˵����IDLE���üĴ����������߿��߼�������reg_analog_wr01��
   ��      ����Current Seting For Mode
            1x��LTE mode Current
            01��3G_DC &amp; X mode Current
            00��3G &amp; 2G mode Current
   UNION�ṹ ���� */
#define ABB_RX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3D)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr48��
   ��      ����TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
            000��14MHz
            001��28MHz
            010��9.3MHz
            011��18.7MHz
            100��7MHz(Ĭ��)
            101��14MHz
            110��28MHz
            111��56MHz
            Ĭ�����÷�����
            4G:001   2G:100   Others:000
   UNION�ṹ ���� */
#define ABB_TX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3E)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr49��
   ��      ����{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
   UNION�ṹ ���� */
#define ABB_TX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3F)

/* �Ĵ���˵����version�Ĵ�����
   ��      ������ģ�ⲿ�־����汾�Ĵ���ֵ
   UNION�ṹ ���� */
#define ABB_CH1_VERSION_ADDR                          (ABB_BASE_ADDR + 0x40)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7]      ���ֲ���TXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
 bit[6]      ���ֲ���RXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
 bit[5:3]    bit[4:3]����ģʽ���ƣ�
             00������ģʽ(Ĭ��)
             01�������㷨�߼�����ģʽ
             10��RXģ�����ģʽ(bypass RX�����˲���)
             11��Reserved
             bit[5]RXCͨ������ʹ�ܣ�
             0������ģʽ(Ĭ��)��RXAͨ��ѡ��RXA��������������
             1��RXCͨ������ģʽ(��RXCͨ���������ݸ��õ�RXAͨ��)
 bit[2:1]    RXģ�����ģʽ��ͨ��ѡ��
             00�����RXA Iģ�����������(Ĭ��)
             01�����RXA Qģ�����������
             10�����RXB Iģ�����������
             11�����RXB Qģ�����������
 bit[0]      ȫ����λ�źţ�comstarV520 Reserved
             0������λ(Ĭ��)
             1����λ�������ֵ�·��ģ���·
   UNION�ṹ:  ABB_CH1_TESTMODE_UNION */
#define ABB_CH1_TESTMODE_ADDR                         (ABB_BASE_ADDR + 0x41)

/* �Ĵ���˵����ͨ�����ƼĴ�����
 bit[7:2]    ����
 bit[1]      CH1ͨ��RXB������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
 bit[0]      CH1ͨ��RXA������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
   UNION�ṹ:  ABB_CH1_CTRL_UNION */
#define ABB_CH1_CTRL_ADDR                             (ABB_BASE_ADDR + 0x42)

/* �Ĵ���˵����TXͨ��offset�Ĵ�����
   ��      ����TXͨ��I·dc offset����
   UNION�ṹ ���� */
#define ABB_CH1_TX_I_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x48)

/* �Ĵ���˵����TXͨ��offset�Ĵ�����
   ��      ����TXͨ��Q·dc offset����
   UNION�ṹ ���� */
#define ABB_CH1_TX_Q_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x49)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4A)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXAͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH1_RXA_I_COEF1_UNION */
#define ABB_CH1_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4B)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4C)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXAͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH1_RXA_I_COEF3_UNION */
#define ABB_CH1_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4D)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4E)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4F)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXAͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXAͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH1_RXA_Q_COEF1_UNION */
#define ABB_CH1_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x50)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x51)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXAͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH1_RXA_Q_COEF3_UNION */
#define ABB_CH1_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x52)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x53)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x54)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXBͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH1_RXB_I_COEF1_UNION */
#define ABB_CH1_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x55)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x56)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXBͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH1_RXB_I_COEF3_UNION */
#define ABB_CH1_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x57)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x58)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x59)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXBͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXBͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH1_RXB_Q_COEF1_UNION */
#define ABB_CH1_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x5A)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x5B)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXBͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH1_RXB_Q_COEF3_UNION */
#define ABB_CH1_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x5C)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x5D)

/* �Ĵ���˵����RXAͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXA����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXA����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH1_REG_RXA_DCR_CFG_UNION */
#define ABB_CH1_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x5E)

/* �Ĵ���˵����RXBͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXB����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXB����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH1_REG_RXB_DCR_CFG_UNION */
#define ABB_CH1_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x5F)

/* �Ĵ���˵����BLOCKING DCR���ܿ��ƼĴ�����
 bit[7:2]    ����
 bit[1]      RXB����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
 bit[0]      RXA����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
   UNION�ṹ:  ABB_CH1_REG_RX_DCR_CTRL_UNION */
#define ABB_CH1_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0x60)

/* �Ĵ���˵����RXAͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXA����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M
 bit[4:0]    RXA����BLOCKING�ϱ�ֵ,2���ݴ�M
   UNION�ṹ:  ABB_CH1_RXA_BLOCKING_UNION */
#define ABB_CH1_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x61)

/* �Ĵ���˵����RXBͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXB����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M
 bit[4:0]    RXB����BLOCKING�ϱ�ֵ,2���ݴ�M
   UNION�ṹ:  ABB_CH1_RXB_BLOCKING_UNION */
#define ABB_CH1_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x62)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x63)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXA_DC_I_2_UNION */
#define ABB_CH1_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x64)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x65)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXA_DC_Q_2_UNION */
#define ABB_CH1_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x66)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x67)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXB_DC_I_2_UNION */
#define ABB_CH1_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x68)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x69)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXB_DC_Q_2_UNION */
#define ABB_CH1_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x6A)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      ����
 bit[6]      TX SDģ������������·ʹ�ܣ�
             0��������������·��
             1������������·��Ĭ�ϣ���
 bit[5]      Tuning code��Դѡ��
             0���Ĵ�������
             1���Զ����£�Ĭ�ϣ�
 bit[4]      TXͨ��SDM Dither���ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TX DEM�����������޷���λ��
             00��0.8125
             01��0.796875(Ĭ��)
             10��0.765625
             11��0.75
 bit[1]      TXͨ��DEMУ׼����ģʽ
             0����������
             1��У׼̬��DEM���Ϊdem_code_man
 bit[0]      TXͨ��SDMģ���쳣ʱ��λ����
             0��ֻ��λSDMģ��
             1����λ����TXͨ��
   UNION�ṹ:  ABB_CH1_REG_DEBUG_DIG0_UNION */
#define ABB_CH1_REG_DEBUG_DIG0_ADDR                   (ABB_BASE_ADDR + 0x6B)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��DEM����ֹ����ã�ֻ��DEMУ׼̬��������,��λ
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_DIG1_ADDR                   (ABB_BASE_ADDR + 0x6C)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��DEM����ֹ����ã�ֻ��DEMУ׼̬��������,��λ
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_DIG2_ADDR                   (ABB_BASE_ADDR + 0x6D)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��SDMģ���쳣��λ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_DIG3_ADDR                   (ABB_BASE_ADDR + 0x6E)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      �������ֵ��ԼĴ���
            bit[7]��ģʽ�л���λ��������ʹ��
            0����ʹ��
            1��ʹ��
            bit[6:4]��ģʽ�л���λ��������ֵ����λΪ8 cycles
            bit[3]��Reserved
            bit[2]��TX��Ƶ��ʹ��bypass����
            0����bypass
            1��bypass
            bit[1]��RX��Ƶ��ʹ��bypass����
            0����bypass
            1��bypass
            bit[0]���ܽ�CH1_CLK_52M���ʱ��ѡ��
            0�����CH1_CLK_52M
            1�����CH1_CLK_61D44M
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_DIG4_ADDR                   (ABB_BASE_ADDR + 0x6F)

/* �Ĵ���˵����Power Down���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_WR02_ADDR                  (ABB_BASE_ADDR + 0x70)

/* �Ĵ���˵������ģ�ӿ�ʱ�ӿ��ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_WR03_ADDR                  (ABB_BASE_ADDR + 0x71)

/* �Ĵ���˵����Other���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_WR04_ADDR                  (ABB_BASE_ADDR + 0x72)

/* �Ĵ���˵����ADC��һ������������tuning�Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_WR05_ADDR                  (ABB_BASE_ADDR + 0x73)

/* �Ĵ���˵����ADC�ڶ�������������tuning�Ĵ�����
   ��      ����ADC�ڶ�������������tuning
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_WR06_ADDR                  (ABB_BASE_ADDR + 0x74)

/* �Ĵ���˵����ADC����������������tuning�Ĵ�����
   ��      ����ADC����������������tuning
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_WR07_ADDR                  (ABB_BASE_ADDR + 0x75)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_WR08_ADDR                  (ABB_BASE_ADDR + 0x76)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_WR09_ADDR                  (ABB_BASE_ADDR + 0x77)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_WR10_ADDR                  (ABB_BASE_ADDR + 0x78)

/* �Ĵ���˵����ʱ�ӷ��ؿ��ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_WR38_ADDR                  (ABB_BASE_ADDR + 0x79)

/* �Ĵ���˵����DUM���ƼĴ�����
   ��      ����RX DEM Mode Selection,bit 2,��ch0_reg_analog_wr00��bit3��bit0��ϳ�3bit��ʵ������9����ϣ�
            000��DWA
            001��CLA1
            010��CLA2
            011��CLA3
            100��CLA4
            101��CLA5
            110��CLA6
            111��CLA7
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_WR39_ADDR                  (ABB_BASE_ADDR + 0x7A)

/* �Ĵ���˵������־λֻ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_RO0_ADDR                   (ABB_BASE_ADDR + 0x7B)

/* �Ĵ���˵����RCУ׼ֻ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_RO1_ADDR                   (ABB_BASE_ADDR + 0x7C)

/* �Ĵ���˵����ģ��ֻ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_RO2_ADDR                   (ABB_BASE_ADDR + 0x7D)

/* �Ĵ���˵����ģ��ֻ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_RO3_ADDR                   (ABB_BASE_ADDR + 0x7E)

/* �Ĵ���˵����ģ��ֻ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_RO4_ADDR                   (ABB_BASE_ADDR + 0x7F)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA0_ADDR                   (ABB_BASE_ADDR + 0x80)

/* �Ĵ���˵����PLL LOCK���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA1_ADDR                   (ABB_BASE_ADDR + 0x81)

/* �Ĵ���˵����PLL���ƼĴ�����
   ��      ��������ʱ�ӿ���
            1������ʱ�Ӵ�
            0������ʱ�ӹر�
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA2_ADDR                   (ABB_BASE_ADDR + 0x82)

/* �Ĵ���˵����PLL���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA3_ADDR                   (ABB_BASE_ADDR + 0x83)

/* �Ĵ���˵����PLL���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA4_ADDR                   (ABB_BASE_ADDR + 0x84)

/* �Ĵ���˵���������������ƼĴ�����
   ��      ����ABB_REF_Fast_UP����
            0���ر�(Ĭ��)
            1������
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA5_ADDR                   (ABB_BASE_ADDR + 0x85)

/* �Ĵ���˵����Bandgap��TCXO���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA6_ADDR                   (ABB_BASE_ADDR + 0x86)

/* �Ĵ���˵�����������ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA7_ADDR                   (ABB_BASE_ADDR + 0x87)

/* �Ĵ���˵�����������ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA8_ADDR                   (ABB_BASE_ADDR + 0x88)

/* �Ĵ���˵����ADC���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA9_ADDR                   (ABB_BASE_ADDR + 0x89)

/* �Ĵ���˵����ADC��λ���ƼĴ�����
   ��      ����ADC��RST_CAP����
            0��Reset CAP123
            1����Reset CAP123
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0x8A)

/* �Ĵ���˵����ADC���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA11_ADDR                  (ABB_BASE_ADDR + 0x8B)

/* �Ĵ���˵����ADC���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA12_ADDR                  (ABB_BASE_ADDR + 0x8C)

/* �Ĵ���˵����ADC���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA13_ADDR                  (ABB_BASE_ADDR + 0x8D)

/* �Ĵ���˵����ADC���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0x8E)

/* �Ĵ���˵����ADC�ӳٿ��ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0x8F)

/* �Ĵ���˵����ADC���ƼĴ�����
   ��      ����RX���PDM�������
            0��adder encoder���ӷ��������
            1��de-bubble encoder���������������
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0x90)

/* �Ĵ���˵����PLL���ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0x91)

/* �Ĵ���˵����TX�ֹ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0x92)

/* �Ĵ���˵����ʱ��ʹ�ܿ��ƼĴ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0x93)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0x94)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0x95)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0x96)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0x97)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0x98)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0x99)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����ADC������1���ݿ����룬ΪFF Corner׼���Ķ��ⲹ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0x9A)

/* �Ĵ���˵����ģ�����ֻ���Ĵ�����
   ��      ����RXA Iͨ��OP1 OffsetУ���Ƿ������־λ
            0��δ���
            1��У׼���
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ARO0_ADDR                   (ABB_BASE_ADDR + 0x9B)

/* �Ĵ���˵����version�Ĵ�����
   ��      ������ģ�ⲿ�־����汾�Ĵ���ֵ
   UNION�ṹ ���� */
#define ABB_CH0_VERSION_ADDR                          (ABB_BASE_ADDR + 0xA0)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7]      ���ֲ���TXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
 bit[6]      ���ֲ���RXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
 bit[5:3]    bit[4:3]����ģʽ���ƣ�
             00������ģʽ(Ĭ��)
             01�������㷨�߼�����ģʽ
             10��RXģ�����ģʽ(bypass RX�����˲���)
             11������/ģ��ӿڻ���
             bit[5]RXCͨ������ʹ�ܣ���ComstarV510 reserved��
             0������ģʽ(Ĭ��)��RXAͨ��ѡ��RXA��������������
             1��RXCͨ������ģʽ(��RXCͨ���������ݸ��õ�RXAͨ��)
 bit[2:1]    RXģ�����ģʽ��ͨ��ѡ��
             00�����RXA Iģ�����������(Ĭ��)
             01�����RXA Qģ�����������
             10�����RXB Iģ�����������
             11�����RXB Qģ�����������
 bit[0]      ȫ����λ�źţ�
             0������λ(Ĭ��)
             1����λ�������ֵ�·��ģ���·
   UNION�ṹ:  ABB_CH0_TESTMODE_UNION */
#define ABB_CH0_TESTMODE_ADDR                         (ABB_BASE_ADDR + 0xA1)

/* �Ĵ���˵����ͨ�����ƼĴ�����
 bit[7:2]    ����
 bit[1]      CH0ͨ��RXB������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
 bit[0]      CH0ͨ��RXA������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
   UNION�ṹ:  ABB_CH0_CTRL_UNION */
#define ABB_CH0_CTRL_ADDR                             (ABB_BASE_ADDR + 0xA2)

/* �Ĵ���˵����TXͨ��offset�Ĵ�����
   ��      ����TXͨ��I·dc offset����
   UNION�ṹ ���� */
#define ABB_CH0_TX_I_OFFSET_ADDR                      (ABB_BASE_ADDR + 0xA8)

/* �Ĵ���˵����TXͨ��offset�Ĵ�����
   ��      ����TXͨ��Q·dc offset����
   UNION�ṹ ���� */
#define ABB_CH0_TX_Q_OFFSET_ADDR                      (ABB_BASE_ADDR + 0xA9)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0xAA)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXAͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH0_RXA_I_COEF1_UNION */
#define ABB_CH0_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0xAB)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0xAC)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXAͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH0_RXA_I_COEF3_UNION */
#define ABB_CH0_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0xAD)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0xAE)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0xAF)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXAͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXAͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH0_RXA_Q_COEF1_UNION */
#define ABB_CH0_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0xB0)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0xB1)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXAͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH0_RXA_Q_COEF3_UNION */
#define ABB_CH0_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0xB2)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0xB3)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0xB4)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXBͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH0_RXB_I_COEF1_UNION */
#define ABB_CH0_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0xB5)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0xB6)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXBͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH0_RXB_I_COEF3_UNION */
#define ABB_CH0_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0xB7)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0xB8)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0xB9)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXBͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXBͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH0_RXB_Q_COEF1_UNION */
#define ABB_CH0_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0xBA)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0xBB)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXBͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH0_RXB_Q_COEF3_UNION */
#define ABB_CH0_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0xBC)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0xBD)

/* �Ĵ���˵����RXAͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXA����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXA����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH0_REG_RXA_DCR_CFG_UNION */
#define ABB_CH0_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0xBE)

/* �Ĵ���˵����RXBͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXB����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXB����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH0_REG_RXB_DCR_CFG_UNION */
#define ABB_CH0_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0xBF)

/* �Ĵ���˵����BLOCKING DCR���ܿ��ƼĴ�����
 bit[7:2]    ����
 bit[1]      RXB����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
 bit[0]      RXA����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
   UNION�ṹ:  ABB_CH0_REG_RX_DCR_CTRL_UNION */
#define ABB_CH0_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0xC0)

/* �Ĵ���˵����RXAͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXA����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M
 bit[4:0]    RXA����BLOCKING�ϱ�ֵ,2���ݴ�M
   UNION�ṹ:  ABB_CH0_RXA_BLOCKING_UNION */
#define ABB_CH0_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0xC1)

/* �Ĵ���˵����RXBͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXB����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M
 bit[4:0]    RXB����BLOCKING�ϱ�ֵ,2���ݴ�M
   UNION�ṹ:  ABB_CH0_RXB_BLOCKING_UNION */
#define ABB_CH0_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0xC2)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0xC3)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXA_DC_I_2_UNION */
#define ABB_CH0_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0xC4)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0xC5)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXA_DC_Q_2_UNION */
#define ABB_CH0_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0xC6)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0xC7)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXB_DC_I_2_UNION */
#define ABB_CH0_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0xC8)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0xC9)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXB_DC_Q_2_UNION */
#define ABB_CH0_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0xCA)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      ����
 bit[6]      TX SDģ������������·ʹ�ܣ�
             0��������������·��
             1������������·��Ĭ�ϣ���
 bit[5]      Tuning code��Դѡ��
             0���Ĵ�������
             1���Զ����£�Ĭ�ϣ�
 bit[4]      TXͨ��SDM Dither���ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TX DEM�����������޷���λ��
             00��0.8125
             01��0.796875(Ĭ��)
             10��0.765625
             11��0.75
 bit[1]      TXͨ��DEMУ׼����ģʽ
             0����������
             1��У׼̬��DEM���Ϊdem_code_man
 bit[0]      TXͨ��SDMģ���쳣ʱ��λ����
             0��ֻ��λSDMģ��
             1����λ����TXͨ��
   UNION�ṹ:  ABB_CH0_REG_DEBUG_DIG0_UNION */
#define ABB_CH0_REG_DEBUG_DIG0_ADDR                   (ABB_BASE_ADDR + 0xCB)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��DEM����ֹ����ã�ֻ��DEMУ׼̬��������,��λ
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_DIG1_ADDR                   (ABB_BASE_ADDR + 0xCC)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��DEM����ֹ����ã�ֻ��DEMУ׼̬��������,��λ
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_DIG2_ADDR                   (ABB_BASE_ADDR + 0xCD)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��SDMģ���쳣��λ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_DIG3_ADDR                   (ABB_BASE_ADDR + 0xCE)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      �������ֵ��ԼĴ���
            bit[7]��ģʽ�л���λ��������ʹ��
            0����ʹ��
            1��ʹ��
            bit[6:4]��ģʽ�л���λ��������ֵ����λΪ8 cycles
            bit[3]��Reserved
            bit[2]��TX��Ƶ��ʹ��bypass����
            0����bypass
            1��bypass
            bit[1]��RX��Ƶ��ʹ��bypass����
            0����bypass
            1��bypass
            bit[0]���ܽ�CH0_CLK_52M���ʱ��ѡ��
            0�����CH0_CLK_52M
            1�����CH0_CLK_61D44M
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_DIG4_ADDR                   (ABB_BASE_ADDR + 0xCF)

/* �Ĵ���˵����Power Down���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_WR02_ADDR                  (ABB_BASE_ADDR + 0xD0)

/* �Ĵ���˵������ģ�ӿ�ʱ�ӿ��ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_WR03_ADDR                  (ABB_BASE_ADDR + 0xD1)

/* �Ĵ���˵����Other���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_WR04_ADDR                  (ABB_BASE_ADDR + 0xD2)

/* �Ĵ���˵����ADC��һ������������tuning�Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_WR05_ADDR                  (ABB_BASE_ADDR + 0xD3)

/* �Ĵ���˵����ADC�ڶ�������������tuning�Ĵ�����
   ��      ����ADC�ڶ�������������tuning
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_WR06_ADDR                  (ABB_BASE_ADDR + 0xD4)

/* �Ĵ���˵����ADC����������������tuning�Ĵ�����
   ��      ����ADC����������������tuning
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_WR07_ADDR                  (ABB_BASE_ADDR + 0xD5)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_WR08_ADDR                  (ABB_BASE_ADDR + 0xD6)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_WR09_ADDR                  (ABB_BASE_ADDR + 0xD7)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_WR10_ADDR                  (ABB_BASE_ADDR + 0xD8)

/* �Ĵ���˵����ʱ�ӷ��ؿ��ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_WR38_ADDR                  (ABB_BASE_ADDR + 0xD9)

/* �Ĵ���˵����DUM���ƼĴ�����
   ��      ����RX DEM Mode Selection,bit 2,��ch0_reg_analog_wr00��bit3��bit0��ϳ�3bit��ʵ������9����ϣ�
            000��DWA
            001��CLA1
            010��CLA2
            011��CLA3
            100��CLA4
            101��CLA5
            110��CLA6
            111��CLA7
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_WR39_ADDR                  (ABB_BASE_ADDR + 0xDA)

/* �Ĵ���˵������־λֻ���Ĵ�����
   ��      ����WPLL��LOCK�ź�
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_RO0_ADDR                   (ABB_BASE_ADDR + 0xDB)

/* �Ĵ���˵����RCУ׼ֻ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_RO1_ADDR                   (ABB_BASE_ADDR + 0xDC)

/* �Ĵ���˵����ģ��ֻ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_RO2_ADDR                   (ABB_BASE_ADDR + 0xDD)

/* �Ĵ���˵����ģ��ֻ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_RO3_ADDR                   (ABB_BASE_ADDR + 0xDE)

/* �Ĵ���˵����ģ��ֻ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_RO4_ADDR                   (ABB_BASE_ADDR + 0xDF)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����GPLL VCO Current����
            00��X1.2
            01��X1.1(Ĭ��)
            10��X1.1
            11��X1.0
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA0_ADDR                   (ABB_BASE_ADDR + 0xE0)

/* �Ĵ���˵����PLL LOCK���ƼĴ�����
   ��      ����WPLL VCO Current����
            00��X0.7
            01��X1(Ĭ��)
            10��X1
            11��X1.3
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA1_ADDR                   (ABB_BASE_ADDR + 0xE1)

/* �Ĵ���˵����PLL���ƼĴ�����
   ��      ��������ʱ�ӿ���
            1������ʱ�Ӵ�
            0������ʱ�ӹر�
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA2_ADDR                   (ABB_BASE_ADDR + 0xE2)

/* �Ĵ���˵����PLL���ƼĴ�����
   ��      ����GPLL��ɱõ�������(����Ч)
            0000��4u
            0001��6u
            0010��8u
            0011��10u(Ĭ��)
            0100��12u
            0101��14u
            0110��16u
            0111��18u
            ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA3_ADDR                   (ABB_BASE_ADDR + 0xE3)

/* �Ĵ���˵����PLL���ƼĴ�����
   ��      ����WPLL��ɱõ�������(����Ч)
            0000��4u
            0001��6u
            0010��8u
            0011��10u(Ĭ��)
            0100��12u
            0101��14u
            0110��16u
            0111��18u
            ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA4_ADDR                   (ABB_BASE_ADDR + 0xE4)

/* �Ĵ���˵���������������ƼĴ�����
   ��      ����ABB_REF_Fast_UP����
            0���ر�(Ĭ��)
            1������
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA5_ADDR                   (ABB_BASE_ADDR + 0xE5)

/* �Ĵ���˵����Bandgap��TCXO���ƼĴ�����
   ��      ����reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA6_ADDR                   (ABB_BASE_ADDR + 0xE6)

/* �Ĵ���˵�����������ƼĴ�����
   ��      ����reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA7_ADDR                   (ABB_BASE_ADDR + 0xE7)

/* �Ĵ���˵�����������ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA8_ADDR                   (ABB_BASE_ADDR + 0xE8)

/* �Ĵ���˵����ADC���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA9_ADDR                   (ABB_BASE_ADDR + 0xE9)

/* �Ĵ���˵����ADC��λ���ƼĴ�����
   ��      ����ADC��RST_CAP����
            0��Reset CAP123
            1����Reset CAP123
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0xEA)

/* �Ĵ���˵����ADC���ƼĴ�����
   ��      ����Refence��ѹģ��ǿ��PD�ź�
            0�� Reference��ѹģ��״̬��BG_EN�źż�����ģ��PD�ź��Զ�����
            1�� Reference��ѹģ��ǿ��Power Down
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA11_ADDR                  (ABB_BASE_ADDR + 0xEB)

/* �Ĵ���˵����ADC���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA12_ADDR                  (ABB_BASE_ADDR + 0xEC)

/* �Ĵ���˵����ADC���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA13_ADDR                  (ABB_BASE_ADDR + 0xED)

/* �Ĵ���˵����ADC���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0xEE)

/* �Ĵ���˵����ADC�ӳٿ��ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0xEF)

/* �Ĵ���˵����ADC���ƼĴ�����
   ��      ����RX���PDM�������
            0��adder encoder���ӷ��������
            1��de-bubble encoder���������������
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xF0)

/* �Ĵ���˵����PLL���ԼĴ�����
   ��      ����PLL���Ƶ�ѹ����PAD�ź�ѡ��
            00/11�����Ƶ�ѹ����PAD����
            01��GPLL������Ƶ�ѹ��PAD
            10��WPLL������Ƶ�ѹ��PAD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xF1)

/* �Ĵ���˵����TX�ֹ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xF2)

/* �Ĵ���˵����ʱ��ʹ�ܿ��ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xF3)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xF4)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xF5)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0xF6)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0xF7)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0xF8)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xF9)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����ADC������1���ݿ����룬ΪFF Corner׼���Ķ��ⲹ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xFA)

/* �Ĵ���˵����ģ�����ֻ���Ĵ�����
   ��      ����RXA Iͨ��OP1 OffsetУ���Ƿ������־λ
            0��δ���
            1��У׼���
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ARO0_ADDR                   (ABB_BASE_ADDR + 0xFB)

/* �Ĵ���˵����SINE���ͼĴ�����
 bit[7:4]    ���Ҳ�����Ƶ�ʿ��ƣ���λ(freq of tx_hb_clk)/32�����䷶ΧΪ1~f
 bit[3:2]    ���Ҳ����ͷ��ȿ���
             00��������
             01��3/4����
             10��1/2����
             11��1/4����
 bit[1]      ch1���Ҳ�����ʹ��
             0��������
             1������
 bit[0]      ch0���Ҳ�����ʹ��
             0��������
             1������
   UNION�ṹ:  ABB_SINE_GENERATE_UNION */
#define ABB_SINE_GENERATE_ADDR                        (ABB_BASE_ADDR + 0xFF)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������reg_analog_wr50��
   ��      ����TX ����ʱ����ѡ��
            0������(Ĭ��)
            1������
   UNION�ṹ ���� */
#define ABB_TX_2G_ANA_3_ADDR                          (ABB_BASE_ADDR + 0x100)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������reg_analog_wr51��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_2G_ANA_4_ADDR                          (ABB_BASE_ADDR + 0x101)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������reg_analog_wr52��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_2G_ANA_5_ADDR                          (ABB_BASE_ADDR + 0x102)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr53��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_2G_ANA_3_ADDR                          (ABB_BASE_ADDR + 0x103)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr54��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_2G_ANA_4_ADDR                          (ABB_BASE_ADDR + 0x104)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr55��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_2G_ANA_5_ADDR                          (ABB_BASE_ADDR + 0x105)

/* �Ĵ���˵����CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr50��
   ��      ����TX ����ʱ����ѡ��
            0������(Ĭ��)
            1������
   UNION�ṹ ���� */
#define ABB_TX_CH0_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x106)

/* �Ĵ���˵����CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr51��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_CH0_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x107)

/* �Ĵ���˵����CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr52��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_CH0_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x108)

/* �Ĵ���˵����CH0 RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr53��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH0_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x109)

/* �Ĵ���˵����CH0 RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr54��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH0_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x10A)

/* �Ĵ���˵����CH0 RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr55��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH0_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x10B)

/* �Ĵ���˵����CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr50��
   ��      ����TX ����ʱ����ѡ��
            0������(Ĭ��)
            1������
   UNION�ṹ ���� */
#define ABB_TX_CH0_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x10C)

/* �Ĵ���˵����CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr51��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_CH0_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x10D)

/* �Ĵ���˵����CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr52��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_CH0_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x10E)

/* �Ĵ���˵����CH0 RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr53��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH0_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x10F)

/* �Ĵ���˵����CH0 RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr54��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH0_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x110)

/* �Ĵ���˵����CH0 RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr55��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH0_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x111)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������reg_analog_wr50��
   ��      ����TX ����ʱ����ѡ��
            0������(Ĭ��)
            1������
   UNION�ṹ ���� */
#define ABB_TX_TDS_ANA_3_ADDR                         (ABB_BASE_ADDR + 0x112)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������reg_analog_wr51��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_TDS_ANA_4_ADDR                         (ABB_BASE_ADDR + 0x113)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������reg_analog_wr52��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_TDS_ANA_5_ADDR                         (ABB_BASE_ADDR + 0x114)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr53��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_TDS_ANA_3_ADDR                         (ABB_BASE_ADDR + 0x115)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr54��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_TDS_ANA_4_ADDR                         (ABB_BASE_ADDR + 0x116)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr55��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_TDS_ANA_5_ADDR                         (ABB_BASE_ADDR + 0x117)

/* �Ĵ���˵����CH1 TX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr50��
   ��      ����TX ����ʱ����ѡ��
            0������(Ĭ��)
            1������
   UNION�ṹ ���� */
#define ABB_TX_CH1_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x118)

/* �Ĵ���˵����CH1 TX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr51��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_CH1_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x119)

/* �Ĵ���˵����CH1 TX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr52��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_CH1_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x11A)

/* �Ĵ���˵����CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr53��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH1_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x11B)

/* �Ĵ���˵����CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr54��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH1_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x11C)

/* �Ĵ���˵����CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr55��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH1_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x11D)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr50��
   ��      ����TX ����ʱ����ѡ��
            0������(Ĭ��)
            1������
   UNION�ṹ ���� */
#define ABB_TX_IDLE_ANA_3_ADDR                        (ABB_BASE_ADDR + 0x12A)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr51��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_IDLE_ANA_4_ADDR                        (ABB_BASE_ADDR + 0x12B)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr52��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_IDLE_ANA_5_ADDR                        (ABB_BASE_ADDR + 0x12C)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr53��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_IDLE_ANA_3_ADDR                        (ABB_BASE_ADDR + 0x12D)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr54��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_IDLE_ANA_4_ADDR                        (ABB_BASE_ADDR + 0x12E)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr55��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_IDLE_ANA_5_ADDR                        (ABB_BASE_ADDR + 0x12F)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA27_ADDR                  (ABB_BASE_ADDR + 0x130)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA28_ADDR                  (ABB_BASE_ADDR + 0x131)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA29_ADDR                  (ABB_BASE_ADDR + 0x132)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA30_ADDR                  (ABB_BASE_ADDR + 0x133)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA31_ADDR                  (ABB_BASE_ADDR + 0x134)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA32_ADDR                  (ABB_BASE_ADDR + 0x135)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA33_ADDR                  (ABB_BASE_ADDR + 0x136)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA34_ADDR                  (ABB_BASE_ADDR + 0x137)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA35_ADDR                  (ABB_BASE_ADDR + 0x138)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA36_ADDR                  (ABB_BASE_ADDR + 0x139)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA37_ADDR                  (ABB_BASE_ADDR + 0x13A)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA38_ADDR                  (ABB_BASE_ADDR + 0x13B)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA39_ADDR                  (ABB_BASE_ADDR + 0x13C)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA40_ADDR                  (ABB_BASE_ADDR + 0x13D)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA41_ADDR                  (ABB_BASE_ADDR + 0x13E)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
            ComstarV511_Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA42_ADDR                  (ABB_BASE_ADDR + 0x13F)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA27_ADDR                  (ABB_BASE_ADDR + 0x140)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA28_ADDR                  (ABB_BASE_ADDR + 0x141)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA29_ADDR                  (ABB_BASE_ADDR + 0x142)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA30_ADDR                  (ABB_BASE_ADDR + 0x143)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA31_ADDR                  (ABB_BASE_ADDR + 0x144)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA32_ADDR                  (ABB_BASE_ADDR + 0x145)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA33_ADDR                  (ABB_BASE_ADDR + 0x146)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA34_ADDR                  (ABB_BASE_ADDR + 0x147)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA35_ADDR                  (ABB_BASE_ADDR + 0x148)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA36_ADDR                  (ABB_BASE_ADDR + 0x149)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA37_ADDR                  (ABB_BASE_ADDR + 0x14A)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA38_ADDR                  (ABB_BASE_ADDR + 0x14B)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA39_ADDR                  (ABB_BASE_ADDR + 0x14C)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA40_ADDR                  (ABB_BASE_ADDR + 0x14D)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA41_ADDR                  (ABB_BASE_ADDR + 0x14E)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA42_ADDR                  (ABB_BASE_ADDR + 0x14F)

/* �Ĵ���˵����CH1 RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             Others��Reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11��reserved��
   UNION�ṹ:  ABB_RX_CH1_3G_DIG_1_UNION */
#define ABB_RX_CH1_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x180)

/* �Ĵ���˵����CH1 RX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_CH1_3G_DIG_2_UNION */
#define ABB_RX_CH1_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x181)

/* �Ĵ���˵����CH1 TX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2��-------,--------,15.36MHz,--------,--------
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_CH1_3G_DIG_1_UNION */
#define ABB_TX_CH1_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x182)

/* �Ĵ���˵����CH1 TX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ(Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_CH1_3G_DIG_2_UNION */
#define ABB_TX_CH1_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x183)

/* �Ĵ���˵����CH1 TX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_TX_CH1_3G_DIG_3_UNION */
#define ABB_TX_CH1_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x184)

/* �Ĵ���˵����CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr00��
   ��      ����RXA_I ADC Power Down����
            0��Power On
            1��Power Down(Ĭ��)
            (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ ���� */
#define ABB_RX_CH1_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x185)

/* �Ĵ���˵����CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr01��
   ��      ����Current Seting For Mode
            1x��LTE mode Current
            01��3G_DC &amp; X mode Current
            00��3G &amp; 2G mode Current
   UNION�ṹ ���� */
#define ABB_RX_CH1_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x186)

/* �Ĵ���˵����CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr53��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH1_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x187)

/* �Ĵ���˵����CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr54��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH1_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x188)

/* �Ĵ���˵����CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr55��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH1_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x189)

/* �Ĵ���˵����CH1 TX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr48��
   ��      ����TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
            000��14MHz(Ĭ��)
            001��28MHz
            010��9.3MHz
            011��18.7MHz
            100��7MHz
            101��14MHz
            110��28MHz
            111��56MHz
            Ĭ�����÷�����
            4G:001   2G:100   Others:000
   UNION�ṹ ���� */
#define ABB_TX_CH1_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x18A)

/* �Ĵ���˵����CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr49��
   ��      ����{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
   UNION�ṹ ���� */
#define ABB_TX_CH1_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x18B)

/* �Ĵ���˵����CH1 TX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr50��
   ��      ����TX ����ʱ����ѡ��
            0������(Ĭ��)
            1������
   UNION�ṹ ���� */
#define ABB_TX_CH1_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x18C)

/* �Ĵ���˵����CH1 TX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr51��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_CH1_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x18D)

/* �Ĵ���˵����CH1 TX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr52��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_CH1_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x18E)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr56��
   ��      ����BWCT_OP1 OP1�������
            1x�� LTEģʽ
            01�� WDC &amp; X ģʽ
            00�� W &amp; Gģʽ
   UNION�ṹ ���� */
#define ABB_RX_2G_ANA_6_ADDR                          (ABB_BASE_ADDR + 0x18F)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr57��
   ��      ����������DACƫ�õ�������
            0 ��������������ܺ�
            1 С�������������ܲ�
   UNION�ṹ ���� */
#define ABB_RX_2G_ANA_7_ADDR                          (ABB_BASE_ADDR + 0x190)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr58��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_2G_ANA_8_ADDR                          (ABB_BASE_ADDR + 0x191)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr59��
   ��      ����W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
            2'b00��2560chip��(WģĬ��)
            2'b01��512chip��
            2'b10��1024chip��(XģĬ��)
            2'b11��2048chip��
   UNION�ṹ ���� */
#define ABB_RX_2G_ANA_9_ADDR                          (ABB_BASE_ADDR + 0x192)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr60��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_2G_ANA_10_ADDR                         (ABB_BASE_ADDR + 0x193)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr61��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_2G_ANA_11_ADDR                         (ABB_BASE_ADDR + 0x194)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr56��
   ��      ����BWCT_OP1 OP1�������
            1x�� LTEģʽ
            01�� WDC &amp; X ģʽ
            00�� W &amp; Gģʽ
   UNION�ṹ ���� */
#define ABB_RX_CH0_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0x195)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr57��
   ��      ����������DACƫ�õ�������
            0 ��������������ܺ�
            1 С�������������ܲ�
   UNION�ṹ ���� */
#define ABB_RX_CH0_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0x196)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr58��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH0_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0x197)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr59��
   ��      ����W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
            2'b00��2560chip��(WģĬ��)
            2'b01��512chip��
            2'b10��1024chip��(XģĬ��)
            2'b11��2048chip��
   UNION�ṹ ���� */
#define ABB_RX_CH0_3G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0x198)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr60��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_CH0_3G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0x199)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr61��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_CH0_3G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0x19A)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr56��
   ��      ����BWCT_OP1 OP1�������
            1x�� LTEģʽ
            01�� WDC &amp; X ģʽ
            00�� W &amp; Gģʽ
   UNION�ṹ ���� */
#define ABB_RX_CH0_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0x19B)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr57��
   ��      ����������DACƫ�õ�������
            0 ��������������ܺ�
            1 С�������������ܲ�
   UNION�ṹ ���� */
#define ABB_RX_CH0_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0x19C)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr58��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH0_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0x19D)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr59��
   ��      ����W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
            2'b00��2560chip��(WģĬ��)
            2'b01��512chip��
            2'b10��1024chip��(XģĬ��)
            2'b11��2048chip��
   UNION�ṹ ���� */
#define ABB_RX_CH0_4G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0x19E)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr60��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_CH0_4G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0x19F)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr61��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_CH0_4G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0x1A0)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr56��
   ��      ����BWCT_OP1 OP1�������
            1x�� LTEģʽ
            01�� WDC &amp; X ģʽ
            00�� W &amp; Gģʽ
   UNION�ṹ ���� */
#define ABB_RX_TDS_ANA_6_ADDR                         (ABB_BASE_ADDR + 0x1A1)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr57��
   ��      ����������DACƫ�õ�������
            0 ��������������ܺ�
            1 С�������������ܲ�
   UNION�ṹ ���� */
#define ABB_RX_TDS_ANA_7_ADDR                         (ABB_BASE_ADDR + 0x1A2)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr58��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_TDS_ANA_8_ADDR                         (ABB_BASE_ADDR + 0x1A3)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr59��
   ��      ����W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
            2'b00��2560chip��(WģĬ��)
            2'b01��512chip��
            2'b10��1024chip��(XģĬ��)
            2'b11��2048chip��
   UNION�ṹ ���� */
#define ABB_RX_TDS_ANA_9_ADDR                         (ABB_BASE_ADDR + 0x1A4)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr60��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_TDS_ANA_10_ADDR                        (ABB_BASE_ADDR + 0x1A5)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr61��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_TDS_ANA_11_ADDR                        (ABB_BASE_ADDR + 0x1A6)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr56��
   ��      ����BWCT_OP1 OP1�������
            1x�� LTEģʽ
            01�� WDC &amp; X ģʽ
            00�� W &amp; Gģʽ
   UNION�ṹ ���� */
#define ABB_RX_IDLE_ANA_6_ADDR                        (ABB_BASE_ADDR + 0x1A7)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr57��
   ��      ����������DACƫ�õ�������
            0 ��������������ܺ�
            1 С�������������ܲ�
   UNION�ṹ ���� */
#define ABB_RX_IDLE_ANA_7_ADDR                        (ABB_BASE_ADDR + 0x1A8)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr58��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_IDLE_ANA_8_ADDR                        (ABB_BASE_ADDR + 0x1A9)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr59��
   ��      ����W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
            2'b00��2560chip��(WģĬ��)
            2'b01��512chip��
            2'b10��1024chip��(XģĬ��)
            2'b11��2048chip��
   UNION�ṹ ���� */
#define ABB_RX_IDLE_ANA_9_ADDR                        (ABB_BASE_ADDR + 0x1AA)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr60��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_IDLE_ANA_10_ADDR                       (ABB_BASE_ADDR + 0x1AB)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr61��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_IDLE_ANA_11_ADDR                       (ABB_BASE_ADDR + 0x1AC)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr56��
   ��      ����BWCT_OP1 OP1�������
            1x�� LTEģʽ
            01�� WDC &amp; X ģʽ
            00�� W &amp; Gģʽ
   UNION�ṹ ���� */
#define ABB_RX_CH1_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0x1AD)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr57��
   ��      ����������DACƫ�õ�������
            0 ��������������ܺ�
            1 С�������������ܲ�
   UNION�ṹ ���� */
#define ABB_RX_CH1_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0x1AE)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr58��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH1_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0x1AF)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr59��
   ��      ����W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
            2'b00��2560chip��(WģĬ��)
            2'b01��512chip��
            2'b10��1024chip��(XģĬ��)
            2'b11��2048chip��
   UNION�ṹ ���� */
#define ABB_RX_CH1_3G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0x1B1)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr60��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_CH1_3G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0x1B2)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr61��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_CH1_3G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0x1B3)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr56��
   ��      ����BWCT_OP1 OP1�������
            1x�� LTEģʽ
            01�� WDC &amp; X ģʽ
            00�� W &amp; Gģʽ
   UNION�ṹ ���� */
#define ABB_RX_CH1_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0x1B4)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr57��
   ��      ����������DACƫ�õ�������
            0 ��������������ܺ�
            1 С�������������ܲ�
   UNION�ṹ ���� */
#define ABB_RX_CH1_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0x1B5)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr58��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH1_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0x1B6)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr59��
   ��      ����W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
            2'b00��2560chip��(WģĬ��)
            2'b01��512chip��
            2'b10��1024chip��(XģĬ��)
            2'b11��2048chip��
   UNION�ṹ ���� */
#define ABB_RX_CH1_4G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0x1B7)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr60��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_CH1_4G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0x1B8)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr61��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_CH1_4G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0x1B9)

/* �Ĵ���˵�����߿�ǿ������ʹ�ܡ�
 bit[7]      ����
 bit[6]      TXͨ��ǿ���߿�
 bit[5]      RXBͨ��ǿ���߿�
 bit[4]      RXAͨ��ǿ���߿�
 bit[3]      ����
 bit[2]      TXͨ���߿�ѡ��ǿ��ʹ��
             0��ѡ���߿�ʹ��
             1��ѡ��ǿ��ʹ��
 bit[1]      RXBͨ���߿�ѡ��ǿ��ʹ��
             0��ѡ���߿�ʹ��
             1��ѡ��ǿ��ʹ��
 bit[0]      RXAͨ���߿�ѡ��ǿ��ʹ��
             0��ѡ���߿�ʹ��
             1��ѡ��ǿ��ʹ��
   UNION�ṹ:  ABB_CH1_LINE_SEL_UNION */
#define ABB_CH1_LINE_SEL_ADDR                         (ABB_BASE_ADDR + 0x1C0)

/* �Ĵ���˵����ģʽ�߿�ǿ�����á�
 bit[7]      ����
 bit[6]      �߿��ź�CH1_LINE_CTRL_MODEǿ������ʹ��
 bit[5:3]    �߿��ź�CH1_RX_LINE_CTRL_MODEǿ������ֵ
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��ETģʽ
             6��APTģʽ
             7��CAģʽ
 bit[2:0]    �߿��ź�CH1_TX_LINE_CTRL_MODEǿ������ֵ
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��ETģʽ
             6��APTģʽ
             7��CAģʽ
   UNION�ṹ:  ABB_CH1_LINE_CFG_UNION */
#define ABB_CH1_LINE_CFG_ADDR                         (ABB_BASE_ADDR + 0x1C1)

/* �Ĵ���˵����ʱ���ſؼĴ�����
 bit[7:3]    ����
 bit[2]      �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ��
 bit[1]      �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ
 bit[0]      BLOCKING�Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
   UNION�ṹ:  ABB_CH1_CLK_SEL_UNION */
#define ABB_CH1_CLK_SEL_ADDR                          (ABB_BASE_ADDR + 0x1C2)

/* �Ĵ���˵�����߿�ǿ������ʹ�ܡ�
 bit[7]      ����
 bit[6]      TXͨ��ǿ���߿�
 bit[5]      RXBͨ��ǿ���߿�
 bit[4]      RXAͨ��ǿ���߿�
 bit[3]      ����
 bit[2]      TXͨ���߿�ѡ��ǿ��ʹ��
             0��ѡ���߿�ʹ��
             1��ѡ��ǿ��ʹ��
 bit[1]      RXBͨ���߿�ѡ��ǿ��ʹ��
             0��ѡ���߿�ʹ��
             1��ѡ��ǿ��ʹ��
 bit[0]      RXAͨ���߿�ѡ��ǿ��ʹ��
             0��ѡ���߿�ʹ��
             1��ѡ��ǿ��ʹ��
   UNION�ṹ:  ABB_CH0_LINE_SEL_UNION */
#define ABB_CH0_LINE_SEL_ADDR                         (ABB_BASE_ADDR + 0x1D0)

/* �Ĵ���˵����ģʽ�߿�ǿ�����á�
 bit[7]      ����
 bit[6]      �߿��ź�CH0_LINE_CTRL_MODEǿ������ʹ��
 bit[5:3]    �߿��ź�CH0_RX_LINE_CTRL_MODEǿ������ֵ
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��ETģʽ
             6��APTģʽ
             7��CAģʽ
 bit[2:0]    �߿��ź�CH0_TX_LINE_CTRL_MODEǿ������ֵ
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��ETģʽ
             6��APTģʽ
             7��CAģʽ
   UNION�ṹ:  ABB_CH0_LINE_CFG_UNION */
#define ABB_CH0_LINE_CFG_ADDR                         (ABB_BASE_ADDR + 0x1D1)

/* �Ĵ���˵����ʱ���ſؼĴ�����
 bit[7:3]    ����
 bit[2]      �߿��ź�CH0_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ��
 bit[1]      �߿��ź�CH0_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ
 bit[0]      BLOCKING�Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
   UNION�ṹ:  ABB_CH0_CLK_SEL_UNION */
#define ABB_CH0_CLK_SEL_ADDR                          (ABB_BASE_ADDR + 0x1D2)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH1_LINE_RPT0_ADDR                        (ABB_BASE_ADDR + 0x1E0)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH1_LINE_RPT1_ADDR                        (ABB_BASE_ADDR + 0x1E1)

/* �Ĵ���˵����RX���ֹ���ģʽ�ϱ��Ĵ�����
   ��      ����RXͨ��ģʽ�����ϱ���
            000��2G(Ĭ��)
            001��3G_SC
            010��4G &amp; ET &amp; APT
            011��3G_DC
            100��TDS
            Others��CA
   UNION�ṹ ���� */
#define ABB_CH1_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1E2)

/* �Ĵ���˵����TX���ֹ���ģʽ�ϱ��Ĵ�����
   ��      ����TXͨ��ģʽ�����ϱ���
            000��2G(Ĭ��)
            001��3G
            010��4G &amp; ET &amp; APT
            011��TDS
            Others��CA
   UNION�ṹ ���� */
#define ABB_CH1_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1E3)

/* �Ĵ���˵����RX���ֹ���״̬�ϱ��Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1E4)

/* �Ĵ���˵����TX���ֹ���״̬�ϱ��Ĵ�����
   ��      ����TXͨ��FIFO����״̬
   UNION�ṹ ���� */
#define ABB_CH1_TX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1E5)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH0_LINE_RPT0_ADDR                        (ABB_BASE_ADDR + 0x1F0)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH0_LINE_RPT1_ADDR                        (ABB_BASE_ADDR + 0x1F1)

/* �Ĵ���˵����RX���ֹ���ģʽ�ϱ��Ĵ�����
   ��      ����RXͨ��ģʽ���ƣ�
            000��2G(Ĭ��)
            001��3G_SC/TDS_B/4G_C
            010��4G
            011��3G_DC/4G_B
            100��TDS
            101��CDMA
            Others��Reserved
   UNION�ṹ ���� */
#define ABB_CH0_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1F2)

/* �Ĵ���˵����TX���ֹ���ģʽ�ϱ��Ĵ�����
   ��      ����TXͨ��ģʽ���ƣ�
            000��2G(Ĭ��)
            001��3G
            010��4G
            011��TDS
            100��CDMA
            Others��Reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1F3)

/* �Ĵ���˵����RX���ֹ���״̬�ϱ��Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1F4)

/* �Ĵ���˵����TX���ֹ���״̬�ϱ��Ĵ�����
   ��      ����TXͨ��FIFO����״̬
   UNION�ṹ ���� */
#define ABB_CH0_TX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1F5)

/* �Ĵ���˵����RXBͨ��ѡ��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RXB_CH_SEL_ADDR                           (ABB_BASE_ADDR + 0x1F6)

/* �Ĵ���˵����ͨ��0 TDS���üĴ�����
 bit[7:3]    ����
 bit[2:0]    ͨ��0 TDSģʽ��ʱ�������üĴ���������ֵ��ʱ�ӹ�ϵΪ
             0: delay 0 chip
             1: delay 4/120 chips
             2: delay 8/120 chips
             3: delay 11/120 chips
             4: delay 15/120 chips
             5: delay 19/120 chips
             6: delay 23/120 chips
             7: delay 26/120 chips
   UNION�ṹ:  ABB_CH0_TDS_RX_DLY_UNION */
#define ABB_CH0_TDS_RX_DLY_ADDR                       (ABB_BASE_ADDR + 0x200)

/* �Ĵ���˵����ͨ��0���üĴ�����
   ��      ����ͨ��0 flush���[7:0]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ ���� */
#define ABB_CH0_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x232)

/* �Ĵ���˵����ͨ��0���üĴ�����
 bit[7:3]    ͨ��0 FLUSHֵ��Ĭ��Ϊ8��
 bit[2:0]    ͨ��0 flush���[10:8]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ:  ABB_CH0_FLUSH_CFG1_UNION */
#define ABB_CH0_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x233)

/* �Ĵ���˵����ͨ��1 TDS���üĴ�����
 bit[7:3]    ����
 bit[2:0]    ͨ��1 TDSģʽ��ʱ�������üĴ���������ֵ��ʱ�ӹ�ϵΪ
             0: delay 0 chip
             1: delay 4/120 chips
             2: delay 8/120 chips
             3: delay 11/120 chips
             4: delay 15/120 chips
             5: delay 19/120 chips
             6: delay 23/120 chips
             7: delay 26/120 chips
   UNION�ṹ:  ABB_CH1_TDS_RX_DLY_UNION */
#define ABB_CH1_TDS_RX_DLY_ADDR                       (ABB_BASE_ADDR + 0x262)

/* �Ĵ���˵����ͨ��1���üĴ�����
   ��      ����ͨ��1 flush���[7:0]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ ���� */
#define ABB_CH1_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x294)

/* �Ĵ���˵����ͨ��1���üĴ�����
 bit[7:3]    ͨ��1 FLUSHֵ��Ĭ��Ϊ8��
 bit[2:0]    ͨ��1 flush���[10:8]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ:  ABB_CH1_FLUSH_CFG1_UNION */
#define ABB_CH1_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x295)

/* �Ĵ���˵����RX Cģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA(Ĭ��)
             Others��Reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11��reserved��
   UNION�ṹ:  ABB_RX_C_DIG_1_UNION */
#define ABB_RX_C_DIG_1_ADDR                           (ABB_BASE_ADDR + 0x400)

/* �Ĵ���˵����RX Cģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_C_DIG_2_UNION */
#define ABB_RX_C_DIG_2_ADDR                           (ABB_BASE_ADDR + 0x401)

/* �Ĵ���˵����TX Cģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2��-------,--------,15.36MHz,--------,--------
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��)
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_C_DIG_1_UNION */
#define ABB_TX_C_DIG_1_ADDR                           (ABB_BASE_ADDR + 0x402)

/* �Ĵ���˵����TX Cģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ (Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_C_DIG_2_UNION */
#define ABB_TX_C_DIG_2_ADDR                           (ABB_BASE_ADDR + 0x403)

/* �Ĵ���˵����TX Cģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_TX_C_DIG_3_UNION */
#define ABB_TX_C_DIG_3_ADDR                           (ABB_BASE_ADDR + 0x404)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr00��
   ��      ����RXA_I ADC Power Down����
            0��Power On
            1��Power Down(Ĭ��)
            (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ ���� */
#define ABB_RX_C_ANA_1_ADDR                           (ABB_BASE_ADDR + 0x405)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr01��
   ��      ����Current Seting For Mode
            1x��LTE mode Current
            01��3G_DC &amp; X mode Current
            00��3G &amp; 2G mode Current
   UNION�ṹ ���� */
#define ABB_RX_C_ANA_2_ADDR                           (ABB_BASE_ADDR + 0x406)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr53��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_C_ANA_3_ADDR                           (ABB_BASE_ADDR + 0x407)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr54��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_C_ANA_4_ADDR                           (ABB_BASE_ADDR + 0x408)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr55��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_C_ANA_5_ADDR                           (ABB_BASE_ADDR + 0x409)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr56��
   ��      ����BWCT_OP1 OP1�������
            1x�� LTEģʽ
            01�� WDC &amp; X ģʽ
            00�� W &amp; Gģʽ
   UNION�ṹ ���� */
#define ABB_RX_C_ANA_6_ADDR                           (ABB_BASE_ADDR + 0x40A)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr57��
   ��      ����������DACƫ�õ�������
            0 ��������������ܺ�
            1 С�������������ܲ�
   UNION�ṹ ���� */
#define ABB_RX_C_ANA_7_ADDR                           (ABB_BASE_ADDR + 0x40B)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr58��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_C_ANA_8_ADDR                           (ABB_BASE_ADDR + 0x40C)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr59��
   ��      ����W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
            2'b00��2560chip��(WģĬ��)
            2'b01��512chip��
            2'b10��1024chip��(XģĬ��)
            2'b11��2048chip��
   UNION�ṹ ���� */
#define ABB_RX_C_ANA_9_ADDR                           (ABB_BASE_ADDR + 0x40D)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr60��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_C_ANA_10_ADDR                          (ABB_BASE_ADDR + 0x40E)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr61��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_C_ANA_11_ADDR                          (ABB_BASE_ADDR + 0x40F)

/* �Ĵ���˵����TX C���üĴ����������߿��߼�������reg_analog_wr48��
   ��      ����TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
            000��14MHz(Ĭ��)
            001��28MHz
            010��9.3MHz
            011��18.7MHz
            100��7MHz
            101��14MHz
            110��28MHz
            111��56MHz
            Ĭ�����÷�����
            4G:001   2G:100   Others:000
   UNION�ṹ ���� */
#define ABB_TX_C_ANA_1_ADDR                           (ABB_BASE_ADDR + 0x410)

/* �Ĵ���˵����TX C���üĴ����������߿��߼�������reg_analog_wr49��
   ��      ����{tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
   UNION�ṹ ���� */
#define ABB_TX_C_ANA_2_ADDR                           (ABB_BASE_ADDR + 0x411)

/* �Ĵ���˵����TX C���üĴ����������߿��߼�������reg_analog_wr50��
   ��      ����TX ����ʱ����ѡ��
            0������(Ĭ��)
            1������
   UNION�ṹ ���� */
#define ABB_TX_C_ANA_3_ADDR                           (ABB_BASE_ADDR + 0x412)

/* �Ĵ���˵����TX C���üĴ����������߿��߼�������reg_analog_wr51��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_C_ANA_4_ADDR                           (ABB_BASE_ADDR + 0x413)

/* �Ĵ���˵����TX C���üĴ����������߿��߼�������reg_analog_wr52��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_C_ANA_5_ADDR                           (ABB_BASE_ADDR + 0x414)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
 bit[7:6]    ����
 bit[5:0]    TX�����˲���ϵ��C0,6bit�з�����
   UNION�ṹ:  ABB_TX_COEF1_UNION */
#define ABB_TX_COEF1_ADDR                             (ABB_BASE_ADDR + 0x415)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
   ��      ����TX�����˲���ϵ��C1,8bit�з�����
   UNION�ṹ ���� */
#define ABB_TX_COEF2_ADDR                             (ABB_BASE_ADDR + 0x416)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
   ��      ����TX�����˲���ϵ��C2��8λ,10bit�з�����
   UNION�ṹ ���� */
#define ABB_TX_COEF3_ADDR                             (ABB_BASE_ADDR + 0x417)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
 bit[7:2]    ����
 bit[1:0]    TX�����˲���ϵ��C2��2λ,10bit�з�����
   UNION�ṹ:  ABB_TX_COEF4_UNION */
#define ABB_TX_COEF4_ADDR                             (ABB_BASE_ADDR + 0x418)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
   ��      ����TX�����˲���ϵ��C3��8λ,10bit�޷�����
   UNION�ṹ ���� */
#define ABB_TX_COEF5_ADDR                             (ABB_BASE_ADDR + 0x419)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
 bit[7:2]    ����
 bit[1:0]    TX�����˲���ϵ��C3��2λ,10bit�޷�����
   UNION�ṹ:  ABB_TX_COEF6_UNION */
#define ABB_TX_COEF6_ADDR                             (ABB_BASE_ADDR + 0x41A)

/* �Ĵ���˵����delay����ѡ���ź�
 bit[7:6]    ����
 bit[5:4]    Delay2��ѡ���źţ�
             00��20us��
             01��50us��
             10��200us��
             11��500us��
 bit[3:2]    ����
 bit[1:0]    Delay1��ѡ���źţ�
             00��50us��
             01��100us��
             10��200us��
             11��500us��
   UNION�ṹ:  ABB_BIST_DELAY_SEL_UNION */
#define ABB_BIST_DELAY_SEL_ADDR                       (ABB_BASE_ADDR + 0x500)

/* �Ĵ���˵����ģʽbypass�ź�
 bit[7]      ����
 bit[6:0]    ģʽbypass�źţ�ÿ��ģʽռһ��bit
             [0]��1��ʾGģ��BIST��bypass��0��ʾGģ��BIST����������
             [1]��1��ʾWCDMAģSC��BIST��bypass��0��ʾWCDMAģSC��BIST����������
             [2]��1��ʾWCDMAģDC��BIST��bypass��0��ʾWCDMAģDC��BIST����������
             [3]��1��ʾLTEģ��BIST��bypass��0��ʾLTEģ��BIST����������
             [4]��1��ʾETģ��BIST��bypass��0��ʾETģ��BIST����������
             [5]��1��ʾCAģ��BIST��bypass��0��ʾCAģ��BIST����������
             [6]��1��ʾCDMAģ��BIST��bypass��0��ʾCDMAģ��BIST����������
   UNION�ṹ:  ABB_BIST_MODE_BYPASS_UNION */
#define ABB_BIST_MODE_BYPASS_ADDR                     (ABB_BASE_ADDR + 0x501)

/* �Ĵ���˵����Rx��bypass�ź�
 bit[7:4]    ����
 bit[3:0]    Rx��bypass�źţ�
             [0]��Rx_1��bypass�źţ�0��ʾ��Ҫ��Rx_1��BIST��1��ʾ������
             [1]��Rx_2��bypass�źţ�0��ʾ��Ҫ��Rx_2��BIST��1��ʾ������
             [2]��Rx_3��bypass�źţ�0��ʾ��Ҫ��Rx_3��BIST��1��ʾ������
             [3]��Rx_4��bypass�źţ�0��ʾ��Ҫ��Rx_4��BIST��1��ʾ������
   UNION�ṹ:  ABB_BIST_RX_BYPASS_UNION */
#define ABB_BIST_RX_BYPASS_ADDR                       (ABB_BASE_ADDR + 0x502)

/* �Ĵ���˵����BIST����ʹ���ź�
 bit[7:2]    ����
 bit[1]      BISTʱ���ſ�ʹ���źţ�0��ʾʱ���ſ���Ч��1��ʾʱ���ſ���·��
 bit[0]      BIST����ʹ���źţ����ź�Ϊ��ƽ�źš�
   UNION�ṹ:  ABB_ABB_BIST_EN_UNION */
#define ABB_ABB_BIST_EN_ADDR                          (ABB_BASE_ADDR + 0x503)

/* �Ĵ���˵��������״̬
 bit[7:1]    ����
 bit[0]      1�����Խ��� 0�����ڲ��ԣ�en��������0��
   UNION�ṹ:  ABB_BIST_SNDR_CAL_DONE_UNION */
#define ABB_BIST_SNDR_CAL_DONE_ADDR                   (ABB_BASE_ADDR + 0x504)

/* �Ĵ���˵�����������6�������Ƿ�pass
 bit[7:6]    ����
 bit[5:0]    ÿһ�μ������6�������Ƿ�pass��
             [0]:1��ʾDC_Iָ��pass��0��ʾ��pass��
             [1]:1��ʾDC_Qָ��pass��0��ʾ��pass��
             [2]:1��ʾSNDR_Iָ��pass��0��ʾ��pass��
             [3]:1��ʾSNDR_Qָ��pass��0��ʾ��pass��
             [4]:1��ʾGAIN_MISMATCHָ��pass��0��ʾ��pass��
             [5]:1��ʾGAIN_ERRORָ��pass��0��ʾ��pass��
   UNION�ṹ:  ABB_BIST_PARA_PASS_FLAG_UNION */
#define ABB_BIST_PARA_PASS_FLAG_ADDR                  (ABB_BASE_ADDR + 0x505)

/* �Ĵ���˵����Rx_1��Bist������
 bit[7]      ����
 bit[6:0]    Rx_1��Bist��������ÿ��ģʽ1bit��
             [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
             [1]��1��ʾWCDMAģSC��BIST pass��0��ʾWCDMAģSC��BIST fail��
             [2]��1��ʾWCDMAģDC��BIST pass��0��ʾWCDMAģDC��BIST fail��
             [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
             [4]��1��ʾETģ��BIST pass��0��ʾETģ��BIST fail��
             [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
             [6]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail��
   UNION�ṹ:  ABB_ABB_BIST_PASS_FLAG_1_UNION */
#define ABB_ABB_BIST_PASS_FLAG_1_ADDR                 (ABB_BASE_ADDR + 0x506)

/* �Ĵ���˵����Rx_2��Bist������
 bit[7]      ����
 bit[6:0]    Rx_2��Bist��������ÿ��ģʽ1bit��
             [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
             [1]��1��ʾWCDMAģSC��BIST pass��0��ʾWCDMAģSC��BIST fail��
             [2]��1��ʾWCDMAģDC��BIST pass��0��ʾWCDMAģDC��BIST fail��
             [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
             [4]��1��ʾETģ��BIST pass��0��ʾETģ��BIST fail��
             [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
             [6]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail��
   UNION�ṹ:  ABB_ABB_BIST_PASS_FLAG_2_UNION */
#define ABB_ABB_BIST_PASS_FLAG_2_ADDR                 (ABB_BASE_ADDR + 0x507)

/* �Ĵ���˵����Rx_3��Bist������
 bit[7]      ����
 bit[6:0]    Rx_3��Bist��������ÿ��ģʽ1bit��
             [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
             [1]��1��ʾWCDMAģSC��BIST pass��0��ʾWCDMAģSC��BIST fail��
             [2]��1��ʾWCDMAģDC��BIST pass��0��ʾWCDMAģDC��BIST fail��
             [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
             [4]��1��ʾETģ��BIST pass��0��ʾETģ��BIST fail��
             [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
             [6]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail��
   UNION�ṹ:  ABB_ABB_BIST_PASS_FLAG_3_UNION */
#define ABB_ABB_BIST_PASS_FLAG_3_ADDR                 (ABB_BASE_ADDR + 0x508)

/* �Ĵ���˵����Rx_4��Bist������
 bit[7]      ����
 bit[6:0]    Rx_4��Bist��������ÿ��ģʽ1bit��
             [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
             [1]��1��ʾWCDMAģSC��BIST pass��0��ʾWCDMAģSC��BIST fail��
             [2]��1��ʾWCDMAģDC��BIST pass��0��ʾWCDMAģDC��BIST fail��
             [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
             [4]��1��ʾETģ��BIST pass��0��ʾETģ��BIST fail��
             [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
             [6]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail��
   UNION�ṹ:  ABB_ABB_BIST_PASS_FLAG_4_UNION */
#define ABB_ABB_BIST_PASS_FLAG_4_ADDR                 (ABB_BASE_ADDR + 0x509)

/* �Ĵ���˵����I·DC�ϱ���8λ���
   ��      ����I·DC�ϱ���8λ��I·DC�ϱ�Ϊ11bit�з�������
   UNION�ṹ ���� */
#define ABB_BIST_DC_I_1_ADDR                          (ABB_BASE_ADDR + 0x50A)

/* �Ĵ���˵����I·DC�ϱ���3λ���
 bit[7:3]    ����
 bit[2:0]    I·DC�ϱ���3λ��I·DC�ϱ�Ϊ11bit�з�������
   UNION�ṹ:  ABB_BIST_DC_I_2_UNION */
#define ABB_BIST_DC_I_2_ADDR                          (ABB_BASE_ADDR + 0x50B)

/* �Ĵ���˵����Q·DC�ϱ���8λ���
   ��      ����Q·DC�ϱ������8bit�з�������
   UNION�ṹ ���� */
#define ABB_BIST_DC_Q_1_ADDR                          (ABB_BASE_ADDR + 0x50C)

/* �Ĵ���˵����Q·DC�ϱ���3λ���
 bit[7:3]    ����
 bit[2:0]    I·DC�ϱ���3λ��I·DC�ϱ�Ϊ11bit�з�������
   UNION�ṹ:  ABB_BIST_DC_Q_2_UNION */
#define ABB_BIST_DC_Q_2_ADDR                          (ABB_BASE_ADDR + 0x50D)

/* �Ĵ���˵����i·��������ֵ
   ��      ����i·��������ֵ, 8bit�޷�������
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_I_ADDR                          (ABB_BASE_ADDR + 0x50E)

/* �Ĵ���˵����q·��������ֵ
   ��      ����q·��������ֵ, 8bit�޷�������
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_Q_ADDR                          (ABB_BASE_ADDR + 0x50F)

/* �Ĵ���˵����Gain_mismatch���
   ��      ����Gain_mismatch���,8bit�޷�������
   UNION�ṹ ���� */
#define ABB_BIST_GAIN_MISMATCH_ADDR                   (ABB_BASE_ADDR + 0x510)

/* �Ĵ���˵����Gain_error���
   ��      ����Gain_error���,8bit�޷�������
   UNION�ṹ ���� */
#define ABB_BIST_GAIN_ERROR_ADDR                      (ABB_BASE_ADDR + 0x511)

/* �Ĵ���˵����GPLL���ʱ���ſع���ʹ��
 bit[7:4]    ����
 bit[3]      Gģ����PLLѡ��
             0��ѡ��GPLL������ʱ�ӷ���Ĭ��ѡ��GPLL��˫ʱ�ӷ���Ĭ��ѡ��SCPLL��
             1��ѡ��SCPLL��
 bit[2]      Gģ����PLLѡ��
             0��ѡ��GPLL������/˫ʱ�ӷ���Ĭ��ѡ��GPLL��
             1��ѡ��SCPLL��
 bit[1]      GPLL�ȶ�ָʾ��0��ʾGPLLδ�ȶ���1��ʾGPLL�ȶ���GPLL�ȶ�����ʱ�������
 bit[0]      GPLLʱ���ſع���ʹ�ܣ�
             0��gpllʱ���ſع��ܹرգ�
             1��gpllʱ���ſع��ܴ򿪡�
   UNION�ṹ:  ABB_GPLL_GATE_EN_UNION */
#define ABB_GPLL_GATE_EN_ADDR                         (ABB_BASE_ADDR + 0x602)

/* �Ĵ���˵����GPLL���ʱ���ſ�ʱ������
 bit[7:2]    ����
 bit[1:0]    GPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
             00��gpll����5us���ȶ���
             01��gpll����10us���ȶ���
             10��gpll����15us���ȶ���
             11��gpll����20us���ȶ���
   UNION�ṹ:  ABB_GPLL_GATE_TIME_UNION */
#define ABB_GPLL_GATE_TIME_ADDR                       (ABB_BASE_ADDR + 0x603)

/* �Ĵ���˵����SC_PLL�������ƼĴ���
 bit[7:6]    ����
 bit[5]      SCPLL����ָʾ��
 bit[4]      SCPLL�ȶ�ָʾ��0��ʾSCPLLδ�ȶ���1��ʾSCPLL�ȶ���SCPLL�ȶ�����ʱ�������
 bit[3]      SCPLL�ſ�ʹ���źš�
 bit[2:1]    SCPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
             00��SCPLL����75us��ʱ���ȶ���
             01��SCPLL����100us��ʱ���ȶ���
             10��SCPLL����115us��ʱ���ȶ���
             11��SCPLL����125us��ʱ���ȶ���
 bit[0]      SCPLLʹ���źš�����ͨ��CFG�ӿ����ô�scpll��
   UNION�ṹ:  ABB_SCPLL_LOCK_CTRL_UNION */
#define ABB_SCPLL_LOCK_CTRL_ADDR                      (ABB_BASE_ADDR + 0x604)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
   ��      ����[7]:Reserved;
            [6:4]��PLL���Ƶ����postdiv2��Ĭ��ֵΪ1��
            [3]:Reserved;
            [2:0]��PLL���Ƶ����postdiv1��Ĭ��ֵΪ5��
   UNION�ṹ ���� */
#define ABB_SCPLL_POSTDIV_ADDR                        (ABB_BASE_ADDR + 0x605)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
   ��      ����[7:0]��PLL������Ƶ����fbdiv[11:0]�ĵ�8bit��fbdiv[11:0]Ĭ��ֵΪ64.
   UNION�ṹ ���� */
#define ABB_SCPLL_FBDIV_L_ADDR                        (ABB_BASE_ADDR + 0x606)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
 bit[7:4]    ����
 bit[3:0]    PLL������Ƶ����fbdiv[11:0]�ĸ�4bit��
   UNION�ṹ:  ABB_SCPLL_FBDIV_H_UNION */
#define ABB_SCPLL_FBDIV_H_ADDR                        (ABB_BASE_ADDR + 0x607)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
 bit[7:6]    ����
 bit[5:0]    PLL�ο���Ƶ����refdiv[5:0]��Ĭ��ֵΪ1��
   UNION�ṹ:  ABB_SCPLL_REFDIV_UNION */
#define ABB_SCPLL_REFDIV_ADDR                         (ABB_BASE_ADDR + 0x608)

/* �Ĵ���˵����SC_PLL��Ƶ�����ƼĴ���
   ��      ����[7:6]��Reserved��
            [5]��DACPD��Ĭ��ֵΪ0(��)��
            [4]��PLL FOUT4PHASEPD���ƣ�����Ч��Ĭ��ֵ1���رգ���
            [3]��DSMPD��С��ģʽPD�źţ�Ĭ��ֵ0���򿪣���
            [2]��PLL ��·���ƣ�Ĭ��ֵ0��PLL��·����bypass����
            [1]��PLL FOUTPOSTDIVPD���ƣ�����Ч��Ĭ��ֵ0���򿪣���
            [0]��PLL FOUTVCOPD���ƣ�����Ч��Ĭ��ֵ0���򿪣���
   UNION�ṹ ���� */
#define ABB_SCPLL_FREQ_CTRL_ADDR                      (ABB_BASE_ADDR + 0x609)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[7:0]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL_FRAC1_ADDR                          (ABB_BASE_ADDR + 0x60A)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[15:8]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL_FRAC2_ADDR                          (ABB_BASE_ADDR + 0x60B)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[23:16]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL_FRAC3_ADDR                          (ABB_BASE_ADDR + 0x60C)

/* �Ĵ���˵����SC_PLL�������ƼĴ���
 bit[7:1]    ����
 bit[0]      SCPLL�������ø���ָʾ��
             scpll_en�򿪺����������scpll_postdiv��scpll_fbdiv��scpll_frac������������scpll_sfg_update������ͬʱ���£�scpll_en����ʱ�����ò����������£�����Ҫ����scpll_sfg_update��
   UNION�ṹ:  ABB_SCPLL_CFG_UPDATE_UNION */
#define ABB_SCPLL_CFG_UPDATE_ADDR                     (ABB_BASE_ADDR + 0x60D)

/* �Ĵ���˵����BBP��245D76Mʱ���ſؼĴ���
 bit[7:3]    ����
 bit[2]      ��BBP��SCPLL 104Mʱ���ſ��źš�0�������ʱ�ӣ�ʱ������͵�ƽ��1�����ʱ�ӡ�Ĭ��ֵ0�������ʱ�ӣ���
 bit[1]      ��BBP��SCPLL 245D76Mʱ���ſ��źš�0�������ʱ�ӣ�ʱ������͵�ƽ��1�����ʱ�ӡ�Ĭ��ֵ0�������ʱ�ӣ���
 bit[0]      ��BBP��WPLL 245D76Mʱ���ſ��źš�0�������ʱ�ӣ�ʱ������͵�ƽ��1�����ʱ�ӡ�Ĭ��ֵ0�������ʱ�ӣ���
   UNION�ṹ:  ABB_BBP_SLEEP_EN_UNION */
#define ABB_BBP_SLEEP_EN_ADDR                         (ABB_BASE_ADDR + 0x60E)

/* �Ĵ���˵����WPLL���ʱ���ſع���ʹ��
 bit[7:2]    ����
 bit[1]      WPLL�ȶ�ָʾ��0��ʾWPLLδ�ȶ���1��ʾWPLL�ȶ���WPLL�ȶ�����ʱ�������
 bit[0]      WPLLʱ���ſع���ʹ�ܣ�
             0��wpllʱ���ſع��ܹرգ�
             1��wpllʱ���ſع��ܴ򿪡�
   UNION�ṹ:  ABB_WPLL_GATE_EN_UNION */
#define ABB_WPLL_GATE_EN_ADDR                         (ABB_BASE_ADDR + 0x60F)

/* �Ĵ���˵����WPLL���ʱ���ſ�ʱ������
 bit[7:2]    ����
 bit[1:0]    WPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
             00��wpll����5us���ȶ���
             01��wpll����10us���ȶ���
             10��wpll����15us���ȶ���
             11��wpll����20us���ȶ���
   UNION�ṹ:  ABB_WPLL_GATE_TIME_UNION */
#define ABB_WPLL_GATE_TIME_ADDR                       (ABB_BASE_ADDR + 0x610)

/* �Ĵ���˵����WPLL���ʱ���ſ�ʱ������
 bit[7:3]    ����
 bit[2]      G PLL FREFѡ��
             0��ѡch0 TCXO������ʱ�ӷ���Ĭ��ѡ0��˫ʱ�ӷ���Ĭ��ѡ1��
             1��ѡch1 TCXO��
 bit[1]      W PLL FREFѡ��
             0��ѡch0 TCXO������/˫ʱ�ӷ���Ĭ��ѡ0��
             1��ѡch1 TCXO��
 bit[0]      SC PLL FREFѡ��
             0��ѡch0 TCXO������/˫ʱ�ӷ���Ĭ��ѡ0��
             1��ѡch1 TCXO��
   UNION�ṹ:  ABB_PLL_FREF_SEL_UNION */
#define ABB_PLL_FREF_SEL_ADDR                         (ABB_BASE_ADDR + 0x611)

/* �Ĵ���˵����SOCʱ��ѡ���ź�
 bit[7:1]    ����
 bit[0]      SOC PLLѡ��
             0��SOCʱ��ѡSCPLL����Ĭ��ѡSCPLL��
             1��SOCʱ��ѡWPLL��
   UNION�ṹ:  ABB_SOC_PLL_SEL_UNION */
#define ABB_SOC_PLL_SEL_ADDR                          (ABB_BASE_ADDR + 0x612)

/* �Ĵ���˵����CH0ͨ��RXA HB�˲������档
   ��      ����CH0ͨ��RXA I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH0_RXAI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x613)

/* �Ĵ���˵����CH0ͨ��RXA HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��RXA I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH0_RXAI_HB_GAIN_2_UNION */
#define ABB_CH0_RXAI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x614)

/* �Ĵ���˵����CH0ͨ��RXA HB�˲������档
   ��      ����CH0ͨ��RXA Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH0_RXAQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x615)

/* �Ĵ���˵����CH0ͨ��RXA HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��RXA Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH0_RXAQ_HB_GAIN_2_UNION */
#define ABB_CH0_RXAQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x616)

/* �Ĵ���˵����CH0ͨ��RXB HB�˲������档
   ��      ����CH0ͨ��RXB I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH0_RXBI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x617)

/* �Ĵ���˵����CH0ͨ��RXB HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��RXB I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH0_RXBI_HB_GAIN_2_UNION */
#define ABB_CH0_RXBI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x618)

/* �Ĵ���˵����CH0ͨ��RXB HB�˲������档
   ��      ����CH0ͨ��RXB Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH0_RXBQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x619)

/* �Ĵ���˵����CH0ͨ��RXB HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��RXB Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH0_RXBQ_HB_GAIN_2_UNION */
#define ABB_CH0_RXBQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x61A)

/* �Ĵ���˵����CH1ͨ��RXA HB�˲������档
   ��      ����CH1ͨ��RXA I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH1_RXAI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x61B)

/* �Ĵ���˵����CH1ͨ��RXA HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH1ͨ��RXA I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH1_RXAI_HB_GAIN_2_UNION */
#define ABB_CH1_RXAI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x61C)

/* �Ĵ���˵����CH1ͨ��RXA HB�˲������档
   ��      ����CH1ͨ��RXA Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH1_RXAQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x61D)

/* �Ĵ���˵����CH1ͨ��RXA HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH1ͨ��RXA Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH1_RXAQ_HB_GAIN_2_UNION */
#define ABB_CH1_RXAQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x61E)

/* �Ĵ���˵����CH1ͨ��RXB HB�˲������档
   ��      ����CH1ͨ��RXB I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH1_RXBI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x61F)

/* �Ĵ���˵����CH1ͨ��RXB HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH1ͨ��RXB I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH1_RXBI_HB_GAIN_2_UNION */
#define ABB_CH1_RXBI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x620)

/* �Ĵ���˵����CH1ͨ��RXB HB�˲������档
   ��      ����CH1ͨ��RXB Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH1_RXBQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x621)

/* �Ĵ���˵����CH1ͨ��RXB HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH1ͨ��RXB Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH1_RXBQ_HB_GAIN_2_UNION */
#define ABB_CH1_RXBQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x622)

/* �Ĵ���˵����RXʱ���ſ��ӳٹ������á�
 bit[7:3]    ����
 bit[2:1]    RXʱ���ſ��ӳٵ�19.2MHzʱ�Ӹ�����
                 L/CA/Xģ   W/TDSģ  Gģ
             00��  1          2      32��  (Ĭ��)
             01��  2          4      64��
             10��  4          8      128��
             11��  reserved
 bit[0]      RXʱ���ſ��ӳٹ���ʹ�ܡ��ù��ܴ򿪺�RX����·�����ӱ�RX���ݺ�VLD�ź��ӳٹرա�
   UNION�ṹ:  ABB_RX_EN_DELAY_UNION */
#define ABB_RX_EN_DELAY_ADDR                          (ABB_BASE_ADDR + 0x623)

/* �Ĵ���˵����TX ET�������üĴ���1��
 bit[7]      ѡ��CH0����CH1֧��ET��
             0��CH0��Ĭ�ϣ���
             1��CH1��
 bit[6]      ETͨ��������bypass�ź�
             0����bypass��2����������Ĭ�ϣ���
             1��bypass�������н�������
 bit[5:4]    ����
 bit[3]      ETУ׼ģ����λ�Ĵ�����
             0������λ��
             1����λ��
 bit[2]      ETͨ����λ�Ĵ�����
             0������λ��
             1����λ��
 bit[1]      ETͨ������˲�����bypass�ź�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      ETͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_ET_DIG_1_UNION */
#define ABB_TX_ET_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x700)

/* �Ĵ���˵����TX ET�������üĴ���2��
 bit[7]      ET TXͨ��dem bypass��
             0��DEM��(Ĭ��)
             1��DEM bypass
 bit[6]      ET Calibrationͨ��dem bypass��
             0��DEM��(Ĭ��)
             1��DEM bypass
 bit[5]      ET TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ(Ĭ��)
             1��ʹ��DWAģʽ
 bit[4]      ET Calibrationͨ��demģʽ���ƣ�
             0��ʹ��CLAģʽ(Ĭ��)
             1��ʹ��DWAģʽ
 bit[3]      ET LSB���bit���ֵ����
 bit[2:1]    TXͨ��DEM constϵ����
             0��0
             1��2
             2��4(Ĭ��)
             3��6
 bit[0]      ETͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!et_gating_en)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_ET_DIG_2_UNION */
#define ABB_TX_ET_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x701)

/* �Ĵ���˵����TX ET�������üĴ���3��
 bit[7]      ����
 bit[6]      ET DAC��������ʱ���Ƿ�ʹ��calibration�������У׼��
             0����ʹ�ܣ�
             1��ʹ�ܡ�
 bit[5]      ����
 bit[4]      ETУ׼�������á�ET DAC��������ʱ�������ַ�����ET DAC�������У׼��
             0����Calibration DAC��ͨ��Calibration DAC�����ET DAC�������У׼��
             1���ر�Calibration DAC����IREG�Ĵ��������Ȩ��ET OUT�������У׼��
 bit[3:2]    ���е����Ƚ�ʱ����ʱ���ơ�Ĭ�ϲ���153.6MHzʱ�ӽ�����ʱ��
             00��30��ʱ�����ڣ�
             01��75��ʱ�����ڣ�
             10��150��ʱ�����ڣ�
             11��300��ʱ�����ڡ�
 bit[1]      ETͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ETͨ��calibrationʹ�ܡ��������������calibration��ɺ󣬸�bit�Զ����㡣
             0����ʹ�ܣ�
             1��ʹ�ܡ�
   UNION�ṹ:  ABB_TX_ET_DIG_3_UNION */
#define ABB_TX_ET_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x702)

/* �Ĵ���˵����TX ET�������üĴ���4��
 bit[7]      ����
 bit[6]      ETͨ���㷨����ģʽʹ�ܡ���ģʽʹ�ܣ���RXͨ�����ݻ��ص���ͨ��et_ch_selѡ�񻷻ص�ch0ͨ������ch1ͨ����
             0����ʹ�ܣ�
             1��ʹ�ܡ�
 bit[5]      ETͨ���ӿڻ���ģʽʹ�ܡ���ģʽʹ�ܣ���ET TX����ͨ��RXͨ�����ء�ͨ��et_ch_selѡ�񻷻ص�ch0ͨ������ch1ͨ����
             0����ʹ�ܣ�
             1��ʹ�ܡ�
 bit[4]      ET��Ƶ��ʹ��bypass����
             0����bypass
             1��bypass
 bit[3]      ETģʽǿ������ʹ�ܡ�
             0����ʹ�ܣ�
             1��ʹ�ܡ�
 bit[2]      ETģʽǿ������ֵ��
 bit[1]      ET�߿�ǿ������ʹ�ܡ�
             0����ʹ�ܣ�
             1��ʹ�ܡ�
 bit[0]      ET�߿�ǿ������ֵ��
   UNION�ṹ:  ABB_TX_ET_DIG_4_UNION */
#define ABB_TX_ET_DIG_4_ADDR                          (ABB_BASE_ADDR + 0x703)

/* �Ĵ���˵����ETͨ��offset���üĴ�����
   ��      ����ETͨ��offset���üĴ�����
   UNION�ṹ ���� */
#define ABB_ET_DC_OFFSET_ADDR                         (ABB_BASE_ADDR + 0x704)

/* �Ĵ���˵����ETͨ��״̬�ϱ��Ĵ���
 bit[7]      ETͨ��У׼��ɡ�
 bit[6:3]    ����
 bit[2]      ET HB�˲������ָʾ��
 bit[1]      ET CIC6�˲������ָʾ��
 bit[0]      ET�����˲������ָʾ��
   UNION�ṹ:  ABB_ET_STATE_RPT_UNION */
#define ABB_ET_STATE_RPT_ADDR                         (ABB_BASE_ADDR + 0x705)

/* �Ĵ���˵����ETͨ��ITEMPУ׼����Ĵ�����λ��
 bit[7:2]    ����
 bit[1:0]    ITEMPУ׼�����λ��
   UNION�ṹ:  ABB_ET_ITEMP_REG_MSB_UNION */
#define ABB_ET_ITEMP_REG_MSB_ADDR                     (ABB_BASE_ADDR + 0x706)

/* �Ĵ���˵����ETͨ��ITEMPУ׼����Ĵ�����λ��
   ��      ����ITEMPУ׼�����λ��
   UNION�ṹ ���� */
#define ABB_ET_ITEMP_REG_LSB_ADDR                     (ABB_BASE_ADDR + 0x707)

/* �Ĵ���˵����ETͨ��ICELL1У׼����Ĵ�����
   ��      ����ICELL1У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG1_ADDR                        (ABB_BASE_ADDR + 0x708)

/* �Ĵ���˵����ETͨ��ICELL2У׼����Ĵ�����
   ��      ����ICELL2У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG2_ADDR                        (ABB_BASE_ADDR + 0x709)

/* �Ĵ���˵����ETͨ��ICELL3У׼����Ĵ�����
   ��      ����ICELL3У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG3_ADDR                        (ABB_BASE_ADDR + 0x70A)

/* �Ĵ���˵����ETͨ��ICELL4У׼����Ĵ�����
   ��      ����ICELL4У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG4_ADDR                        (ABB_BASE_ADDR + 0x70B)

/* �Ĵ���˵����ETͨ��ICELL5У׼����Ĵ�����
   ��      ����ICELL5У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG5_ADDR                        (ABB_BASE_ADDR + 0x70C)

/* �Ĵ���˵����ETͨ��ICELL6У׼����Ĵ�����
   ��      ����ICELL6У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG6_ADDR                        (ABB_BASE_ADDR + 0x70D)

/* �Ĵ���˵����ETͨ��ICELL7У׼����Ĵ�����
   ��      ����ICELL7У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG7_ADDR                        (ABB_BASE_ADDR + 0x70E)

/* �Ĵ���˵����ETͨ��ICELL8У׼����Ĵ�����
   ��      ����ICELL8У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG8_ADDR                        (ABB_BASE_ADDR + 0x70F)

/* �Ĵ���˵����ETͨ��ICELL9У׼����Ĵ�����
   ��      ����ICELL9У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG9_ADDR                        (ABB_BASE_ADDR + 0x710)

/* �Ĵ���˵����ETͨ��ICELL10У׼����Ĵ�����
   ��      ����ICELL10У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG10_ADDR                       (ABB_BASE_ADDR + 0x711)

/* �Ĵ���˵����ETͨ��ICELL11У׼����Ĵ�����
   ��      ����ICELL11У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG11_ADDR                       (ABB_BASE_ADDR + 0x712)

/* �Ĵ���˵����ETͨ��ICELL12У׼����Ĵ�����
   ��      ����ICELL12У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG12_ADDR                       (ABB_BASE_ADDR + 0x713)

/* �Ĵ���˵����ETͨ��ICELL13У׼����Ĵ�����
   ��      ����ICELL13У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG13_ADDR                       (ABB_BASE_ADDR + 0x714)

/* �Ĵ���˵����ETͨ��ICELL14У׼����Ĵ�����
   ��      ����ICELL14У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG14_ADDR                       (ABB_BASE_ADDR + 0x715)

/* �Ĵ���˵����ETͨ��ICELL15У׼����Ĵ�����
   ��      ����ICELL15У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG15_ADDR                       (ABB_BASE_ADDR + 0x716)

/* �Ĵ���˵����ETͨ��ICELL16У׼����Ĵ�����
   ��      ����ICELL16У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG16_ADDR                       (ABB_BASE_ADDR + 0x717)

/* �Ĵ���˵����ETͨ��ICELL17У׼����Ĵ�����
   ��      ����ICELL17У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG17_ADDR                       (ABB_BASE_ADDR + 0x718)

/* �Ĵ���˵����ETͨ��ICELL18У׼����Ĵ�����
   ��      ����ICELL18У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG18_ADDR                       (ABB_BASE_ADDR + 0x719)

/* �Ĵ���˵����ETͨ��ICELL19У׼����Ĵ�����
   ��      ����ICELL19У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG19_ADDR                       (ABB_BASE_ADDR + 0x71A)

/* �Ĵ���˵����ETͨ��ICELL20У׼����Ĵ�����
   ��      ����ICELL20У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG20_ADDR                       (ABB_BASE_ADDR + 0x71B)

/* �Ĵ���˵����ETͨ��ICELL21У׼����Ĵ�����
   ��      ����ICELL21У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG21_ADDR                       (ABB_BASE_ADDR + 0x71C)

/* �Ĵ���˵����ETͨ��ICELL22У׼����Ĵ�����
   ��      ����ICELL22У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG22_ADDR                       (ABB_BASE_ADDR + 0x71D)

/* �Ĵ���˵����ETͨ��ICELL23У׼����Ĵ�����
   ��      ����ICELL23У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG23_ADDR                       (ABB_BASE_ADDR + 0x71E)

/* �Ĵ���˵����ETͨ��ICELL24У׼����Ĵ�����
   ��      ����ICELL24У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG24_ADDR                       (ABB_BASE_ADDR + 0x71F)

/* �Ĵ���˵����ETͨ��ICELL25У׼����Ĵ�����
   ��      ����ICELL25У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG25_ADDR                       (ABB_BASE_ADDR + 0x720)

/* �Ĵ���˵����ETͨ��ICELL26У׼����Ĵ�����
   ��      ����ICELL26У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG26_ADDR                       (ABB_BASE_ADDR + 0x721)

/* �Ĵ���˵����ETͨ��ICELL27У׼����Ĵ�����
   ��      ����ICELL27У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG27_ADDR                       (ABB_BASE_ADDR + 0x722)

/* �Ĵ���˵����ETͨ��ICELL28У׼����Ĵ�����
   ��      ����ICELL28У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG28_ADDR                       (ABB_BASE_ADDR + 0x723)

/* �Ĵ���˵����ETͨ��ICELL29У׼����Ĵ�����
   ��      ����ICELL29У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG29_ADDR                       (ABB_BASE_ADDR + 0x724)

/* �Ĵ���˵����ETͨ��ICELL30У׼����Ĵ�����
   ��      ����ICELL30У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG30_ADDR                       (ABB_BASE_ADDR + 0x725)

/* �Ĵ���˵����ETͨ��ICELL31У׼����Ĵ�����
   ��      ����ICELL31У׼���
   UNION�ṹ ���� */
#define ABB_ET_ICELL_REG31_ADDR                       (ABB_BASE_ADDR + 0x726)

/* �Ĵ���˵����ETͨ��ICELL�����������1��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���1��
   UNION�ṹ:  ABB_ET_ICELL_SORT1_UNION */
#define ABB_ET_ICELL_SORT1_ADDR                       (ABB_BASE_ADDR + 0x727)

/* �Ĵ���˵����ETͨ��ICELL�����������2��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���2��
   UNION�ṹ:  ABB_ET_ICELL_SORT2_UNION */
#define ABB_ET_ICELL_SORT2_ADDR                       (ABB_BASE_ADDR + 0x728)

/* �Ĵ���˵����ETͨ��ICELL�����������3��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���3��
   UNION�ṹ:  ABB_ET_ICELL_SORT3_UNION */
#define ABB_ET_ICELL_SORT3_ADDR                       (ABB_BASE_ADDR + 0x729)

/* �Ĵ���˵����ETͨ��ICELL�����������4��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���4��
   UNION�ṹ:  ABB_ET_ICELL_SORT4_UNION */
#define ABB_ET_ICELL_SORT4_ADDR                       (ABB_BASE_ADDR + 0x72A)

/* �Ĵ���˵����ETͨ��ICELL�����������5��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���5��
   UNION�ṹ:  ABB_ET_ICELL_SORT5_UNION */
#define ABB_ET_ICELL_SORT5_ADDR                       (ABB_BASE_ADDR + 0x72B)

/* �Ĵ���˵����ETͨ��ICELL�����������6��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���6��
   UNION�ṹ:  ABB_ET_ICELL_SORT6_UNION */
#define ABB_ET_ICELL_SORT6_ADDR                       (ABB_BASE_ADDR + 0x72C)

/* �Ĵ���˵����ETͨ��ICELL�����������7��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���7��
   UNION�ṹ:  ABB_ET_ICELL_SORT7_UNION */
#define ABB_ET_ICELL_SORT7_ADDR                       (ABB_BASE_ADDR + 0x72D)

/* �Ĵ���˵����ETͨ��ICELL�����������8��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���8��
   UNION�ṹ:  ABB_ET_ICELL_SORT8_UNION */
#define ABB_ET_ICELL_SORT8_ADDR                       (ABB_BASE_ADDR + 0x72E)

/* �Ĵ���˵����ETͨ��ICELL�����������9��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���9��
   UNION�ṹ:  ABB_ET_ICELL_SORT9_UNION */
#define ABB_ET_ICELL_SORT9_ADDR                       (ABB_BASE_ADDR + 0x72F)

/* �Ĵ���˵����ETͨ��ICELL�����������10��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���10��
   UNION�ṹ:  ABB_ET_ICELL_SORT10_UNION */
#define ABB_ET_ICELL_SORT10_ADDR                      (ABB_BASE_ADDR + 0x730)

/* �Ĵ���˵����ETͨ��ICELL�����������11��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���11��
   UNION�ṹ:  ABB_ET_ICELL_SORT11_UNION */
#define ABB_ET_ICELL_SORT11_ADDR                      (ABB_BASE_ADDR + 0x731)

/* �Ĵ���˵����ETͨ��ICELL�����������12��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���12��
   UNION�ṹ:  ABB_ET_ICELL_SORT12_UNION */
#define ABB_ET_ICELL_SORT12_ADDR                      (ABB_BASE_ADDR + 0x732)

/* �Ĵ���˵����ETͨ��ICELL�����������13��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���13��
   UNION�ṹ:  ABB_ET_ICELL_SORT13_UNION */
#define ABB_ET_ICELL_SORT13_ADDR                      (ABB_BASE_ADDR + 0x733)

/* �Ĵ���˵����ETͨ��ICELL�����������14��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���14��
   UNION�ṹ:  ABB_ET_ICELL_SORT14_UNION */
#define ABB_ET_ICELL_SORT14_ADDR                      (ABB_BASE_ADDR + 0x734)

/* �Ĵ���˵����ETͨ��ICELL�����������15��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���15��
   UNION�ṹ:  ABB_ET_ICELL_SORT15_UNION */
#define ABB_ET_ICELL_SORT15_ADDR                      (ABB_BASE_ADDR + 0x735)

/* �Ĵ���˵����ETͨ��ICELL�����������16��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���16��
   UNION�ṹ:  ABB_ET_ICELL_SORT16_UNION */
#define ABB_ET_ICELL_SORT16_ADDR                      (ABB_BASE_ADDR + 0x736)

/* �Ĵ���˵����ETͨ��ICELL�����������17��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���17��
   UNION�ṹ:  ABB_ET_ICELL_SORT17_UNION */
#define ABB_ET_ICELL_SORT17_ADDR                      (ABB_BASE_ADDR + 0x737)

/* �Ĵ���˵����ETͨ��ICELL�����������18��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���18��
   UNION�ṹ:  ABB_ET_ICELL_SORT18_UNION */
#define ABB_ET_ICELL_SORT18_ADDR                      (ABB_BASE_ADDR + 0x738)

/* �Ĵ���˵����ETͨ��ICELL�����������19��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���19��
   UNION�ṹ:  ABB_ET_ICELL_SORT19_UNION */
#define ABB_ET_ICELL_SORT19_ADDR                      (ABB_BASE_ADDR + 0x739)

/* �Ĵ���˵����ETͨ��ICELL�����������20��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���20��
   UNION�ṹ:  ABB_ET_ICELL_SORT20_UNION */
#define ABB_ET_ICELL_SORT20_ADDR                      (ABB_BASE_ADDR + 0x73A)

/* �Ĵ���˵����ETͨ��ICELL�����������21��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���21��
   UNION�ṹ:  ABB_ET_ICELL_SORT21_UNION */
#define ABB_ET_ICELL_SORT21_ADDR                      (ABB_BASE_ADDR + 0x73B)

/* �Ĵ���˵����ETͨ��ICELL�����������22��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���22��
   UNION�ṹ:  ABB_ET_ICELL_SORT22_UNION */
#define ABB_ET_ICELL_SORT22_ADDR                      (ABB_BASE_ADDR + 0x73C)

/* �Ĵ���˵����ETͨ��ICELL�����������23��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���23��
   UNION�ṹ:  ABB_ET_ICELL_SORT23_UNION */
#define ABB_ET_ICELL_SORT23_ADDR                      (ABB_BASE_ADDR + 0x73D)

/* �Ĵ���˵����ETͨ��ICELL�����������24��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���24��
   UNION�ṹ:  ABB_ET_ICELL_SORT24_UNION */
#define ABB_ET_ICELL_SORT24_ADDR                      (ABB_BASE_ADDR + 0x73E)

/* �Ĵ���˵����ETͨ��ICELL�����������25��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���25��
   UNION�ṹ:  ABB_ET_ICELL_SORT25_UNION */
#define ABB_ET_ICELL_SORT25_ADDR                      (ABB_BASE_ADDR + 0x73F)

/* �Ĵ���˵����ETͨ��ICELL�����������26��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���26��
   UNION�ṹ:  ABB_ET_ICELL_SORT26_UNION */
#define ABB_ET_ICELL_SORT26_ADDR                      (ABB_BASE_ADDR + 0x740)

/* �Ĵ���˵����ETͨ��ICELL�����������27��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���27��
   UNION�ṹ:  ABB_ET_ICELL_SORT27_UNION */
#define ABB_ET_ICELL_SORT27_ADDR                      (ABB_BASE_ADDR + 0x741)

/* �Ĵ���˵����ETͨ��ICELL�����������28��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���28��
   UNION�ṹ:  ABB_ET_ICELL_SORT28_UNION */
#define ABB_ET_ICELL_SORT28_ADDR                      (ABB_BASE_ADDR + 0x742)

/* �Ĵ���˵����ETͨ��ICELL�����������29��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���29��
   UNION�ṹ:  ABB_ET_ICELL_SORT29_UNION */
#define ABB_ET_ICELL_SORT29_ADDR                      (ABB_BASE_ADDR + 0x743)

/* �Ĵ���˵����ETͨ��ICELL�����������30��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���30��
   UNION�ṹ:  ABB_ET_ICELL_SORT30_UNION */
#define ABB_ET_ICELL_SORT30_ADDR                      (ABB_BASE_ADDR + 0x744)

/* �Ĵ���˵����ETͨ��ICELL�����������31��
 bit[7:5]    ����
 bit[4:0]    ICELL�������Ĵ���31��
   UNION�ṹ:  ABB_ET_ICELL_SORT31_UNION */
#define ABB_ET_ICELL_SORT31_ADDR                      (ABB_BASE_ADDR + 0x745)

/* �Ĵ���˵����ETͨ��ICELL�Ĵ�������
 bit[7:1]    ����
 bit[0]      ���øüĴ��������¼Ĵ���ET_ICELL_REG1~ET_ICELL_SORT31���Ĵ����������֮����Ҫ����Ϊ0��
   UNION�ṹ:  ABB_ET_ICELL_UPDATE_UNION */
#define ABB_ET_ICELL_UPDATE_ADDR                      (ABB_BASE_ADDR + 0x746)

/* �Ĵ���˵����ETͨ��ICELLУ׼�����־�Ĵ���3
   ��      ����У׼ICELL31~ICELL24�����־��
   UNION�ṹ ���� */
#define ABB_ET_ICELL_OVERFLOW3_ADDR                   (ABB_BASE_ADDR + 0x747)

/* �Ĵ���˵����ETͨ��ICELLУ׼�����־�Ĵ���3
   ��      ����У׼ICELL23~ICELL16�����־��
   UNION�ṹ ���� */
#define ABB_ET_ICELL_OVERFLOW2_ADDR                   (ABB_BASE_ADDR + 0x748)

/* �Ĵ���˵����ETͨ��ICELLУ׼�����־�Ĵ���1
   ��      ����У׼ICELL15~ICELL8�����־��
   UNION�ṹ ���� */
#define ABB_ET_ICELL_OVERFLOW1_ADDR                   (ABB_BASE_ADDR + 0x749)

/* �Ĵ���˵����ETͨ��ICELLУ׼�����־�Ĵ���0
   ��      ����У׼ICELL7~ICELL1��ITEMP�����־��
   UNION�ṹ ���� */
#define ABB_ET_ICELL_OVERFLOW0_ADDR                   (ABB_BASE_ADDR + 0x74A)

/* �Ĵ���˵����SINE���ͼĴ�����
 bit[7:4]    ���Ҳ�����Ƶ�ʿ��ƣ���λ(freq of tx_hb_clk)/32�����䷶ΧΪ1~f
 bit[3:2]    ���Ҳ����ͷ��ȿ���
             00��������
             01��3/4����
             10��1/2����
             11��1/4����
 bit[1]      ����
 bit[0]      etͨ�����Ҳ�����ʹ�ܡ���λʹ�ܣ���ETͨ���������Ҳ��źţ���ͨ��sine_sw_reqѡ��CH0����CH1�������Ҳ��źš�
             0��������
             1������
   UNION�ṹ:  ABB_ET_SINE_GENERATE_UNION */
#define ABB_ET_SINE_GENERATE_ADDR                     (ABB_BASE_ADDR + 0x74B)

/* �Ĵ���˵����ETģʽ���üĴ����������߿��߼�������et_reg_debug_ana28��
   ��      ����ѡ��CH0����CH1֧��ET��
            0��CH0��Ĭ�ϣ�
            1��CH1��
   UNION�ṹ ���� */
#define ABB_ET_ET_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x780)

/* �Ĵ���˵����ETģʽ���üĴ����������߿��߼�������et_reg_debug_ana29��
   ��      ����ETģʽ���ƼĴ���2
   UNION�ṹ ���� */
#define ABB_ET_ET_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x781)

/* �Ĵ���˵����APTģʽ���üĴ����������߿��߼�������et_reg_debug_ana28��
   ��      ����ѡ��CH0����CH1֧��ET��
            0��CH0��Ĭ�ϣ�
            1��CH1��
   UNION�ṹ ���� */
#define ABB_ET_APT_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x782)

/* �Ĵ���˵����APTģʽ���üĴ����������߿��߼�������et_reg_debug_ana29��
   ��      ����ETģʽ���ƼĴ���2
   UNION�ṹ ���� */
#define ABB_ET_APT_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x783)

/* �Ĵ���˵����ETģʽ���üĴ����������߿��߼�������et_reg_debug_ana28��
   ��      ����ѡ��CH0����CH1֧��ET��
            0��CH0��Ĭ�ϣ�
            1��CH1��
   UNION�ṹ ���� */
#define ABB_ET_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x784)

/* �Ĵ���˵����ETģʽ���üĴ����������߿��߼�������et_reg_debug_ana29��
   ��      ����ETģʽ���ƼĴ���2
   UNION�ṹ ���� */
#define ABB_ET_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x785)





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

/***======================================================================***
                     (1/1) register_define_ssi_reg
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : ABB_RX_2G_DIG_1_UNION
 �ṹ˵��  : rx_2g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x0����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_2g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                            00���̶�ϵ��1��
                                                            01���̶�ϵ��2��
                                                            10���̶�ϵ��3��
                                                            11��reserved�� */
        unsigned long  rx_comp_fix_2g    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                            0��ϵ�����̶����ɼĴ�������
                                                            1��ϵ���̶� */
        unsigned long  rx_hb_bp_2g       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                            0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                            1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_2g        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                      /TDS_B/4G_C,        /4G_B,
                                                            00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
                                                            others��reserved */
        unsigned long  rx_mode_dig_2g    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                            000��2G(Ĭ��)
                                                            001��3G_SC/TDS_B/4G_C
                                                            010��4G
                                                            011��3G_DC/4G_B
                                                            100��TDS
                                                            101��CDMA
                                                            Others��Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_1_UNION;
#define ABB_RX_2G_DIG_1_rx_comp_sel_b0_2g_START  (0)
#define ABB_RX_2G_DIG_1_rx_comp_sel_b0_2g_END    (0)
#define ABB_RX_2G_DIG_1_rx_comp_fix_2g_START     (1)
#define ABB_RX_2G_DIG_1_rx_comp_fix_2g_END       (1)
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_START        (2)
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_END          (2)
#define ABB_RX_2G_DIG_1_rx_rate_2g_START         (3)
#define ABB_RX_2G_DIG_1_rx_rate_2g_END           (4)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_START     (5)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_DIG_2_UNION
 �ṹ˵��  : rx_2g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x1����ֵ:0x13�����:8
 �Ĵ���˵��: RX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_2g         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_2g         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_2g       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                            00��gainΪ0.5(Ĭ��)
                                                            01��gainΪ0.75
                                                            10��gainΪ0.85
                                                            11��Reserved */
        unsigned long  rx_comp_bp_2g     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                            0����bypass
                                                            1��bypass(Ĭ��) */
        unsigned long  rx_clk_inv_2g     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                            0������
                                                            1������ */
        unsigned long  rx_flush_en_2g    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                            0����ʹ��
                                                            1��ʹ�� */
        unsigned long  rx_comp_sel_b1_2g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_2_UNION;
#define ABB_RX_2G_DIG_2_rxa_pd_2g_START          (0)
#define ABB_RX_2G_DIG_2_rxa_pd_2g_END            (0)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_START          (1)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_END            (1)
#define ABB_RX_2G_DIG_2_gain_sel_2g_START        (2)
#define ABB_RX_2G_DIG_2_gain_sel_2g_END          (3)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_START      (4)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_END        (4)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_START      (5)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_END        (5)
#define ABB_RX_2G_DIG_2_rx_flush_en_2g_START     (6)
#define ABB_RX_2G_DIG_2_rx_flush_en_2g_END       (6)
#define ABB_RX_2G_DIG_2_rx_comp_sel_b1_2g_START  (7)
#define ABB_RX_2G_DIG_2_rx_comp_sel_b1_2g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_2G_DIG_1_UNION
 �ṹ˵��  : tx_2g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x2����ֵ:0x02�����:8
 �Ĵ���˵��: TX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_2g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                         0����bypass(Ĭ��)
                                                         1��bypass */
        unsigned long  tx_hb_bp_2g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
                                                         1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��) */
        unsigned long  tx_rate_2g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                              2G,     3G,     4G,      TDS,      CDMA
                                                             (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                         0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
                                                         1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                         2��-------,--------,15.36MHz,--------,--------
                                                         Others��Reserved */
        unsigned long  tx_mode_dig_2g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                         000��2G(Ĭ��)
                                                         001��3G
                                                         010��4G
                                                         011��TDS
                                                         100��CDMA
                                                         Others��Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_1_UNION;
#define ABB_TX_2G_DIG_1_tx_comp_bp_2g_START   (0)
#define ABB_TX_2G_DIG_1_tx_comp_bp_2g_END     (0)
#define ABB_TX_2G_DIG_1_tx_hb_bp_2g_START     (1)
#define ABB_TX_2G_DIG_1_tx_hb_bp_2g_END       (1)
#define ABB_TX_2G_DIG_1_tx_rate_2g_START      (2)
#define ABB_TX_2G_DIG_1_tx_rate_2g_END        (4)
#define ABB_TX_2G_DIG_1_tx_mode_dig_2g_START  (5)
#define ABB_TX_2G_DIG_1_tx_mode_dig_2g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_2G_DIG_2_UNION
 �ṹ˵��  : tx_2g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x3����ֵ:0x23�����:8
 �Ĵ���˵��: TX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_q_pd_2g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_2g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_2g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                           0��0(Ĭ��)
                                                           1��2
                                                           2��4
                                                           3��6 */
        unsigned long  uddwa_dith_en_2g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  dem_dwa_en_2g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                           0��ʹ��CLAģʽ
                                                           1��ʹ��DWAģʽ (Ĭ��) */
        unsigned long  dem_lsb_bp_2g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                           0��DEM LSB ��(Ĭ��)
                                                           1��DEM LSB bypass */
        unsigned long  dem_msb_bp_2g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                           0��DEM MSB��(Ĭ��)
                                                           1��DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_2_UNION;
#define ABB_TX_2G_DIG_2_tx_q_pd_2g_START        (0)
#define ABB_TX_2G_DIG_2_tx_q_pd_2g_END          (0)
#define ABB_TX_2G_DIG_2_tx_i_pd_2g_START        (1)
#define ABB_TX_2G_DIG_2_tx_i_pd_2g_END          (1)
#define ABB_TX_2G_DIG_2_dem_const_2g_START      (2)
#define ABB_TX_2G_DIG_2_dem_const_2g_END        (3)
#define ABB_TX_2G_DIG_2_uddwa_dith_en_2g_START  (4)
#define ABB_TX_2G_DIG_2_uddwa_dith_en_2g_END    (4)
#define ABB_TX_2G_DIG_2_dem_dwa_en_2g_START     (5)
#define ABB_TX_2G_DIG_2_dem_dwa_en_2g_END       (5)
#define ABB_TX_2G_DIG_2_dem_lsb_bp_2g_START     (6)
#define ABB_TX_2G_DIG_2_dem_lsb_bp_2g_END       (6)
#define ABB_TX_2G_DIG_2_dem_msb_bp_2g_START     (7)
#define ABB_TX_2G_DIG_2_dem_msb_bp_2g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_2G_DIG_3_UNION
 �ṹ˵��  : tx_2g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x4����ֵ:0x01�����:8
 �Ĵ���˵��: TX 2Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : ���� */
        unsigned long  tx_flush_en_2g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                         0����ʹ��
                                                         1��ʹ�� */
        unsigned long  tx_comp_sel_2g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                         00���̶�ϵ��1��
                                                         01���̶�ϵ��2��
                                                         10���̶�ϵ��3��
                                                         11������ϵ���� */
        unsigned long  reserved_1     : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_3_UNION;
#define ABB_TX_2G_DIG_3_tx_flush_en_2g_START  (1)
#define ABB_TX_2G_DIG_3_tx_flush_en_2g_END    (1)
#define ABB_TX_2G_DIG_3_tx_comp_sel_2g_START  (2)
#define ABB_TX_2G_DIG_3_tx_comp_sel_2g_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_3G_DIG_1_UNION
 �ṹ˵��  : rx_ch0_3g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x5����ֵ:0x26�����:8
 �Ĵ���˵��: CH0 RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_comp_sel_b0_3g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                                00���̶�ϵ��1��
                                                                01���̶�ϵ��2��
                                                                10���̶�ϵ��3��
                                                                11��reserved�� */
        unsigned long  ch0_rx_comp_fix_3g    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                                0��ϵ�����̶����ɼĴ�������
                                                                1��ϵ���̶� */
        unsigned long  ch0_rx_hb_bp_3g       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                                0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                                1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  ch0_rx_rate_3g        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                    2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                          /TDS_B/4G_C,        /4G_B,
                                                                00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
                                                                others��reserved */
        unsigned long  ch0_rx_mode_dig_3g    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                                000��2G(Ĭ��)
                                                                001��3G_SC/TDS_B/4G_C
                                                                010��4G
                                                                011��3G_DC/4G_B
                                                                100��TDS
                                                                101��CDMA
                                                                Others��Reserved */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_DIG_1_UNION;
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_comp_sel_b0_3g_START  (0)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_comp_sel_b0_3g_END    (0)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_comp_fix_3g_START     (1)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_comp_fix_3g_END       (1)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_hb_bp_3g_START        (2)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_hb_bp_3g_END          (2)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_rate_3g_START         (3)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_rate_3g_END           (4)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_mode_dig_3g_START     (5)
#define ABB_RX_CH0_3G_DIG_1_ch0_rx_mode_dig_3g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_3G_DIG_2_UNION
 �ṹ˵��  : rx_ch0_3g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x6����ֵ:0x03�����:8
 �Ĵ���˵��: CH0 RX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_pd_3g         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                                0����CLOCK GATING
                                                                1��CLOCK GATING(Ĭ��)
                                                                (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  ch0_rxb_pd_3g         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                                0����CLOCK GATING
                                                                1��CLOCK GATING(Ĭ��)
                                                                (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  ch0_gain_sel_3g       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                                00��gainΪ0.5(Ĭ��)
                                                                01��gainΪ0.75
                                                                10��gainΪ0.85
                                                                11��Reserved */
        unsigned long  ch0_rx_comp_bp_3g     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                                0����bypass(Ĭ��)
                                                                1��bypass */
        unsigned long  ch0_rx_clk_inv_3g     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                                0������
                                                                1������ */
        unsigned long  ch0_rx_flush_en_3g    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                                0����ʹ��
                                                                1��ʹ�� */
        unsigned long  ch0_rx_comp_sel_b1_3g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_DIG_2_UNION;
#define ABB_RX_CH0_3G_DIG_2_ch0_rxa_pd_3g_START          (0)
#define ABB_RX_CH0_3G_DIG_2_ch0_rxa_pd_3g_END            (0)
#define ABB_RX_CH0_3G_DIG_2_ch0_rxb_pd_3g_START          (1)
#define ABB_RX_CH0_3G_DIG_2_ch0_rxb_pd_3g_END            (1)
#define ABB_RX_CH0_3G_DIG_2_ch0_gain_sel_3g_START        (2)
#define ABB_RX_CH0_3G_DIG_2_ch0_gain_sel_3g_END          (3)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_comp_bp_3g_START      (4)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_comp_bp_3g_END        (4)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_clk_inv_3g_START      (5)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_clk_inv_3g_END        (5)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_flush_en_3g_START     (6)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_flush_en_3g_END       (6)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_comp_sel_b1_3g_START  (7)
#define ABB_RX_CH0_3G_DIG_2_ch0_rx_comp_sel_b1_3g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_3G_DIG_1_UNION
 �ṹ˵��  : tx_ch0_3g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x7����ֵ:0x20�����:8
 �Ĵ���˵��: CH0 TX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_bp_3g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass */
        unsigned long  ch0_tx_hb_bp_3g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  ch0_tx_rate_3g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                                  2G,     3G,     4G,      TDS,      CDMA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
                                                             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                             2��-------,--------,15.36MHz,--------,--------
                                                             Others��Reserved */
        unsigned long  ch0_tx_mode_dig_3g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                             000��2G(Ĭ��)
                                                             001��3G
                                                             010��4G
                                                             011��TDS
                                                             100��CDMA
                                                             Others��Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_1_UNION;
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_comp_bp_3g_START   (0)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_comp_bp_3g_END     (0)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_hb_bp_3g_START     (1)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_hb_bp_3g_END       (1)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_rate_3g_START      (2)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_rate_3g_END        (4)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_mode_dig_3g_START  (5)
#define ABB_TX_CH0_3G_DIG_1_ch0_tx_mode_dig_3g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_3G_DIG_2_UNION
 �ṹ˵��  : tx_ch0_3g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x8����ֵ:0x23�����:8
 �Ĵ���˵��: CH0 TX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_q_pd_3g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch0_tx_i_pd_3g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch0_dem_const_3g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                               0��0(Ĭ��)
                                                               1��2
                                                               2��4
                                                               3��6 */
        unsigned long  ch0_uddwa_dith_en_3g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                               0����ʹ��
                                                               1��ʹ�� */
        unsigned long  ch0_dem_dwa_en_3g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                               0��ʹ��CLAģʽ
                                                               1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  ch0_dem_lsb_bp_3g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                               0��DEM LSB ��(Ĭ��)
                                                               1��DEM LSB bypass */
        unsigned long  ch0_dem_msb_bp_3g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                               0��DEM MSB��(Ĭ��)
                                                               1��DEM MSB bypass */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_2_UNION;
#define ABB_TX_CH0_3G_DIG_2_ch0_tx_q_pd_3g_START        (0)
#define ABB_TX_CH0_3G_DIG_2_ch0_tx_q_pd_3g_END          (0)
#define ABB_TX_CH0_3G_DIG_2_ch0_tx_i_pd_3g_START        (1)
#define ABB_TX_CH0_3G_DIG_2_ch0_tx_i_pd_3g_END          (1)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_const_3g_START      (2)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_const_3g_END        (3)
#define ABB_TX_CH0_3G_DIG_2_ch0_uddwa_dith_en_3g_START  (4)
#define ABB_TX_CH0_3G_DIG_2_ch0_uddwa_dith_en_3g_END    (4)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_dwa_en_3g_START     (5)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_dwa_en_3g_END       (5)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_lsb_bp_3g_START     (6)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_lsb_bp_3g_END       (6)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_msb_bp_3g_START     (7)
#define ABB_TX_CH0_3G_DIG_2_ch0_dem_msb_bp_3g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_3G_DIG_3_UNION
 �ṹ˵��  : tx_ch0_3g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x9����ֵ:0x01�����:8
 �Ĵ���˵��: CH0 TX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0         : 1;  /* bit[0]  : ���� */
        unsigned long  ch0_tx_flush_en_3g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  ch0_tx_comp_sel_3g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11������ϵ���� */
        unsigned long  reserved_1         : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_3_UNION;
#define ABB_TX_CH0_3G_DIG_3_ch0_tx_flush_en_3g_START  (1)
#define ABB_TX_CH0_3G_DIG_3_ch0_tx_flush_en_3g_END    (1)
#define ABB_TX_CH0_3G_DIG_3_ch0_tx_comp_sel_3g_START  (2)
#define ABB_TX_CH0_3G_DIG_3_ch0_tx_comp_sel_3g_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_4G_DIG_1_UNION
 �ṹ˵��  : rx_ch0_4g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0xA����ֵ:0x42�����:8
 �Ĵ���˵��: CH0 RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_comp_sel_b0_4g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                                00���̶�ϵ��1��
                                                                01���̶�ϵ��2��
                                                                10���̶�ϵ��3��
                                                                11��reserved�� */
        unsigned long  ch0_rx_comp_fix_4g    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                                0��ϵ�����̶����ɼĴ�������
                                                                1��ϵ���̶� */
        unsigned long  ch0_rx_hb_bp_4g       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                                0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                                1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  ch0_rx_rate_4g        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                    2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                          /TDS_B/4G_C,        /4G_B,
                                                                00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
                                                                others��reserved */
        unsigned long  ch0_rx_mode_dig_4g    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                                000��2G(Ĭ��)
                                                                001��3G_SC/TDS_B/4G_C
                                                                010��4G
                                                                011��3G_DC/4G_B
                                                                100��TDS
                                                                101��CDMA
                                                                Others��Reserved */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_DIG_1_UNION;
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_comp_sel_b0_4g_START  (0)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_comp_sel_b0_4g_END    (0)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_comp_fix_4g_START     (1)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_comp_fix_4g_END       (1)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_hb_bp_4g_START        (2)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_hb_bp_4g_END          (2)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_rate_4g_START         (3)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_rate_4g_END           (4)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_mode_dig_4g_START     (5)
#define ABB_RX_CH0_4G_DIG_1_ch0_rx_mode_dig_4g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_4G_DIG_2_UNION
 �ṹ˵��  : rx_ch0_4g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0xB����ֵ:0x03�����:8
 �Ĵ���˵��: CH0 RX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_pd_4g         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                                0����CLOCK GATING
                                                                1��CLOCK GATING(Ĭ��)
                                                                (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  ch0_rxb_pd_4g         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                                0����CLOCK GATING
                                                                1��CLOCK GATING(Ĭ��)
                                                                (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  ch0_gain_sel_4g       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                                00��gainΪ0.5(Ĭ��)
                                                                01��gainΪ0.75
                                                                10��gainΪ0.85
                                                                11��Reserved */
        unsigned long  ch0_rx_comp_bp_4g     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                                0����bypass(Ĭ��)
                                                                1��bypass */
        unsigned long  ch0_rx_clk_inv_4g     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                                0������
                                                                1������ */
        unsigned long  ch0_rx_flush_en_4g    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                                0����ʹ��
                                                                1��ʹ�� */
        unsigned long  ch0_rx_comp_sel_b1_4g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_DIG_2_UNION;
#define ABB_RX_CH0_4G_DIG_2_ch0_rxa_pd_4g_START          (0)
#define ABB_RX_CH0_4G_DIG_2_ch0_rxa_pd_4g_END            (0)
#define ABB_RX_CH0_4G_DIG_2_ch0_rxb_pd_4g_START          (1)
#define ABB_RX_CH0_4G_DIG_2_ch0_rxb_pd_4g_END            (1)
#define ABB_RX_CH0_4G_DIG_2_ch0_gain_sel_4g_START        (2)
#define ABB_RX_CH0_4G_DIG_2_ch0_gain_sel_4g_END          (3)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_comp_bp_4g_START      (4)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_comp_bp_4g_END        (4)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_clk_inv_4g_START      (5)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_clk_inv_4g_END        (5)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_flush_en_4g_START     (6)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_flush_en_4g_END       (6)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_comp_sel_b1_4g_START  (7)
#define ABB_RX_CH0_4G_DIG_2_ch0_rx_comp_sel_b1_4g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_4G_DIG_1_UNION
 �ṹ˵��  : tx_ch0_4g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0xC����ֵ:0x40�����:8
 �Ĵ���˵��: CH0 TX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_bp_4g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass */
        unsigned long  ch0_tx_hb_bp_4g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  ch0_tx_rate_4g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                                  2G,     3G,     4G,      TDS,      CDMA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
                                                             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                             2��-------,--------,15.36MHz,--------,--------
                                                             Others��Reserved */
        unsigned long  ch0_tx_mode_dig_4g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                             000��2G(Ĭ��)
                                                             001��3G
                                                             010��4G
                                                             011��TDS
                                                             100��CDMA
                                                             Others��Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_1_UNION;
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_comp_bp_4g_START   (0)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_comp_bp_4g_END     (0)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_hb_bp_4g_START     (1)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_hb_bp_4g_END       (1)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_rate_4g_START      (2)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_rate_4g_END        (4)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_mode_dig_4g_START  (5)
#define ABB_TX_CH0_4G_DIG_1_ch0_tx_mode_dig_4g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_4G_DIG_2_UNION
 �ṹ˵��  : tx_ch0_4g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0xD����ֵ:0x23�����:8
 �Ĵ���˵��: CH0 TX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_q_pd_4g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch0_tx_i_pd_4g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch0_dem_const_4g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                               0��0(Ĭ��)
                                                               1��2
                                                               2��4
                                                               3��6 */
        unsigned long  ch0_uddwa_dith_en_4g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                               0����ʹ��
                                                               1��ʹ�� */
        unsigned long  ch0_dem_dwa_en_4g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                               0��ʹ��CLAģʽ
                                                               1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  ch0_dem_lsb_bp_4g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                               0��DEM LSB ��(Ĭ��)
                                                               1��DEM LSB bypass */
        unsigned long  ch0_dem_msb_bp_4g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                               0��DEM MSB��(Ĭ��)
                                                               1��DEM MSB bypass */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_2_UNION;
#define ABB_TX_CH0_4G_DIG_2_ch0_tx_q_pd_4g_START        (0)
#define ABB_TX_CH0_4G_DIG_2_ch0_tx_q_pd_4g_END          (0)
#define ABB_TX_CH0_4G_DIG_2_ch0_tx_i_pd_4g_START        (1)
#define ABB_TX_CH0_4G_DIG_2_ch0_tx_i_pd_4g_END          (1)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_const_4g_START      (2)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_const_4g_END        (3)
#define ABB_TX_CH0_4G_DIG_2_ch0_uddwa_dith_en_4g_START  (4)
#define ABB_TX_CH0_4G_DIG_2_ch0_uddwa_dith_en_4g_END    (4)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_dwa_en_4g_START     (5)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_dwa_en_4g_END       (5)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_lsb_bp_4g_START     (6)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_lsb_bp_4g_END       (6)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_msb_bp_4g_START     (7)
#define ABB_TX_CH0_4G_DIG_2_ch0_dem_msb_bp_4g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_4G_DIG_3_UNION
 �ṹ˵��  : tx_ch0_4g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0xE����ֵ:0x01�����:8
 �Ĵ���˵��: CH0 TX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0         : 1;  /* bit[0]  : ���� */
        unsigned long  ch0_tx_flush_en_4g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  ch0_tx_comp_sel_4g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11������ϵ���� */
        unsigned long  reserved_1         : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_3_UNION;
#define ABB_TX_CH0_4G_DIG_3_ch0_tx_flush_en_4g_START  (1)
#define ABB_TX_CH0_4G_DIG_3_ch0_tx_flush_en_4g_END    (1)
#define ABB_TX_CH0_4G_DIG_3_ch0_tx_comp_sel_4g_START  (2)
#define ABB_TX_CH0_4G_DIG_3_ch0_tx_comp_sel_4g_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_DIG_1_UNION
 �ṹ˵��  : rx_tds_dig_1 �Ĵ����ṹ���塣��ַƫ����:0xF����ֵ:0x26�����:8
 �Ĵ���˵��: RX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_tds : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11��reserved�� */
        unsigned long  rx_comp_fix_tds    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                             0��ϵ�����̶����ɼĴ�������
                                                             1��ϵ���̶� */
        unsigned long  rx_hb_bp_tds       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_tds        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                 2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                       /TDS_B/4G_C,        /4G_B,
                                                             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
                                                             others��reserved */
        unsigned long  rx_mode_dig_tds    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                             000��2G(Ĭ��)
                                                             001��3G_SC/TDS_B/4G_C
                                                             010��4G
                                                             011��3G_DC/4G_B
                                                             100��TDS
                                                             101��CDMA
                                                             Others��Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_1_UNION;
#define ABB_RX_TDS_DIG_1_rx_comp_sel_b0_tds_START  (0)
#define ABB_RX_TDS_DIG_1_rx_comp_sel_b0_tds_END    (0)
#define ABB_RX_TDS_DIG_1_rx_comp_fix_tds_START     (1)
#define ABB_RX_TDS_DIG_1_rx_comp_fix_tds_END       (1)
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_START        (2)
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_END          (2)
#define ABB_RX_TDS_DIG_1_rx_rate_tds_START         (3)
#define ABB_RX_TDS_DIG_1_rx_rate_tds_END           (4)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_START     (5)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_DIG_2_UNION
 �ṹ˵��  : rx_tds_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0xD3�����:8
 �Ĵ���˵��: RX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_tds         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_tds         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_tds       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                             00��gainΪ0.5(Ĭ��)
                                                             01��gainΪ0.75
                                                             10��gainΪ0.85
                                                             11��Reserved */
        unsigned long  rx_comp_bp_tds     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                             0����bypass
                                                             1��bypass(Ĭ��) */
        unsigned long  rx_clk_inv_tds     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                             0������
                                                             1������ */
        unsigned long  rx_flush_en_tds    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  rx_comp_sel_b1_tds : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_2_UNION;
#define ABB_RX_TDS_DIG_2_rxa_pd_tds_START          (0)
#define ABB_RX_TDS_DIG_2_rxa_pd_tds_END            (0)
#define ABB_RX_TDS_DIG_2_rxb_pd_tds_START          (1)
#define ABB_RX_TDS_DIG_2_rxb_pd_tds_END            (1)
#define ABB_RX_TDS_DIG_2_gain_sel_tds_START        (2)
#define ABB_RX_TDS_DIG_2_gain_sel_tds_END          (3)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_tds_START      (4)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_tds_END        (4)
#define ABB_RX_TDS_DIG_2_rx_clk_inv_tds_START      (5)
#define ABB_RX_TDS_DIG_2_rx_clk_inv_tds_END        (5)
#define ABB_RX_TDS_DIG_2_rx_flush_en_tds_START     (6)
#define ABB_RX_TDS_DIG_2_rx_flush_en_tds_END       (6)
#define ABB_RX_TDS_DIG_2_rx_comp_sel_b1_tds_START  (7)
#define ABB_RX_TDS_DIG_2_rx_comp_sel_b1_tds_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_DIG_1_UNION
 �ṹ˵��  : tx_tds_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x11����ֵ:0x60�����:8
 �Ĵ���˵��: TX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_tds  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                          0����bypass(Ĭ��)
                                                          1��bypass */
        unsigned long  tx_hb_bp_tds    : 1;  /* bit[1]  : TXͨ������˲�����bypass�ź�
                                                          0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                          1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_tds     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                               2G,     3G,     4G,      TDS,      CDMA
                                                              (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                          0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
                                                          1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                          2��-------,--------,15.36MHz,--------,--------
                                                          Others��Reserved */
        unsigned long  tx_mode_dig_tds : 3;  /* bit[5-7]: TXģʽ���ƣ�
                                                          000��2G
                                                          001��3G
                                                          010��4G &amp; ET &amp; APT
                                                          011��TDS(Ĭ��)
                                                          Others��CA */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_1_UNION;
#define ABB_TX_TDS_DIG_1_tx_comp_bp_tds_START   (0)
#define ABB_TX_TDS_DIG_1_tx_comp_bp_tds_END     (0)
#define ABB_TX_TDS_DIG_1_tx_hb_bp_tds_START     (1)
#define ABB_TX_TDS_DIG_1_tx_hb_bp_tds_END       (1)
#define ABB_TX_TDS_DIG_1_tx_rate_tds_START      (2)
#define ABB_TX_TDS_DIG_1_tx_rate_tds_END        (4)
#define ABB_TX_TDS_DIG_1_tx_mode_dig_tds_START  (5)
#define ABB_TX_TDS_DIG_1_tx_mode_dig_tds_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_DIG_2_UNION
 �ṹ˵��  : tx_tds_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x12����ֵ:0x23�����:8
 �Ĵ���˵��: TX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_q_pd_tds       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_tds       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_tds     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                            0��0(Ĭ��)
                                                            1��2
                                                            2��4
                                                            3��6 */
        unsigned long  uddwa_dith_en_tds : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                            0����ʹ��
                                                            1��ʹ�� */
        unsigned long  dem_dwa_en_tds    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                            0��ʹ��CLAģʽ
                                                            1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  dem_lsb_bp_tds    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                            0��DEM LSB ��(Ĭ��)
                                                            1��DEM LSB bypass */
        unsigned long  dem_msb_bp_tds    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                            0��DEM MSB��(Ĭ��)
                                                            1��DEM MSB bypass */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_2_UNION;
#define ABB_TX_TDS_DIG_2_tx_q_pd_tds_START        (0)
#define ABB_TX_TDS_DIG_2_tx_q_pd_tds_END          (0)
#define ABB_TX_TDS_DIG_2_tx_i_pd_tds_START        (1)
#define ABB_TX_TDS_DIG_2_tx_i_pd_tds_END          (1)
#define ABB_TX_TDS_DIG_2_dem_const_tds_START      (2)
#define ABB_TX_TDS_DIG_2_dem_const_tds_END        (3)
#define ABB_TX_TDS_DIG_2_uddwa_dith_en_tds_START  (4)
#define ABB_TX_TDS_DIG_2_uddwa_dith_en_tds_END    (4)
#define ABB_TX_TDS_DIG_2_dem_dwa_en_tds_START     (5)
#define ABB_TX_TDS_DIG_2_dem_dwa_en_tds_END       (5)
#define ABB_TX_TDS_DIG_2_dem_lsb_bp_tds_START     (6)
#define ABB_TX_TDS_DIG_2_dem_lsb_bp_tds_END       (6)
#define ABB_TX_TDS_DIG_2_dem_msb_bp_tds_START     (7)
#define ABB_TX_TDS_DIG_2_dem_msb_bp_tds_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_DIG_3_UNION
 �ṹ˵��  : tx_tds_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x13����ֵ:0x01�����:8
 �Ĵ���˵��: TX TDSģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0      : 1;  /* bit[0]  : ���� */
        unsigned long  tx_flush_en_tds : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                          0����ʹ��
                                                          1��ʹ�� */
        unsigned long  tx_comp_sel_tds : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                          00���̶�ϵ��1��
                                                          01���̶�ϵ��2��
                                                          10���̶�ϵ��3��
                                                          11������ϵ���� */
        unsigned long  reserved_1      : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_3_UNION;
#define ABB_TX_TDS_DIG_3_tx_flush_en_tds_START  (1)
#define ABB_TX_TDS_DIG_3_tx_flush_en_tds_END    (1)
#define ABB_TX_TDS_DIG_3_tx_comp_sel_tds_START  (2)
#define ABB_TX_TDS_DIG_3_tx_comp_sel_tds_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_4G_DIG_1_UNION
 �ṹ˵��  : rx_ch1_4g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x1A����ֵ:0x42�����:8
 �Ĵ���˵��: CH1 RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_comp_sel_b0_4g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                                00���̶�ϵ��1��
                                                                01���̶�ϵ��2��
                                                                10���̶�ϵ��3��
                                                                11��reserved�� */
        unsigned long  ch1_rx_comp_fix_4g    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                                0��ϵ�����̶����ɼĴ�������
                                                                1��ϵ���̶� */
        unsigned long  ch1_rx_hb_bp_4g       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                                0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                                1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  ch1_rx_rate_4g        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                    2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                          /TDS_B/4G_C,        /4G_B,
                                                                00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
                                                                others��reserved */
        unsigned long  ch1_rx_mode_dig_4g    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                                000��2G(Ĭ��)
                                                                001��3G_SC/TDS_B/4G_C
                                                                010��4G
                                                                011��3G_DC/4G_B
                                                                100��TDS
                                                                101��CDMA
                                                                Others��Reserved */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_4G_DIG_1_UNION;
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_comp_sel_b0_4g_START  (0)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_comp_sel_b0_4g_END    (0)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_comp_fix_4g_START     (1)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_comp_fix_4g_END       (1)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_hb_bp_4g_START        (2)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_hb_bp_4g_END          (2)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_rate_4g_START         (3)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_rate_4g_END           (4)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_mode_dig_4g_START     (5)
#define ABB_RX_CH1_4G_DIG_1_ch1_rx_mode_dig_4g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_4G_DIG_2_UNION
 �ṹ˵��  : rx_ch1_4g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x1B����ֵ:0x03�����:8
 �Ĵ���˵��: CH1 RX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_pd_4g         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                                0����CLOCK GATING
                                                                1��CLOCK GATING(Ĭ��)
                                                                (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  ch1_rxb_pd_4g         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                                0����CLOCK GATING
                                                                1��CLOCK GATING(Ĭ��)
                                                                (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  ch1_gain_sel_4g       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                                00��gainΪ0.5(Ĭ��)
                                                                01��gainΪ0.75
                                                                10��gainΪ0.85
                                                                11��Reserved */
        unsigned long  ch1_rx_comp_bp_4g     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                                0����bypass(Ĭ��)
                                                                1��bypass */
        unsigned long  ch1_rx_clk_inv_4g     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                                0������
                                                                1������ */
        unsigned long  ch1_rx_flush_en_4g    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                                0����ʹ��
                                                                1��ʹ�� */
        unsigned long  ch1_rx_comp_sel_b1_4g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_4G_DIG_2_UNION;
#define ABB_RX_CH1_4G_DIG_2_ch1_rxa_pd_4g_START          (0)
#define ABB_RX_CH1_4G_DIG_2_ch1_rxa_pd_4g_END            (0)
#define ABB_RX_CH1_4G_DIG_2_ch1_rxb_pd_4g_START          (1)
#define ABB_RX_CH1_4G_DIG_2_ch1_rxb_pd_4g_END            (1)
#define ABB_RX_CH1_4G_DIG_2_ch1_gain_sel_4g_START        (2)
#define ABB_RX_CH1_4G_DIG_2_ch1_gain_sel_4g_END          (3)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_comp_bp_4g_START      (4)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_comp_bp_4g_END        (4)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_clk_inv_4g_START      (5)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_clk_inv_4g_END        (5)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_flush_en_4g_START     (6)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_flush_en_4g_END       (6)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_comp_sel_b1_4g_START  (7)
#define ABB_RX_CH1_4G_DIG_2_ch1_rx_comp_sel_b1_4g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH1_4G_DIG_1_UNION
 �ṹ˵��  : tx_ch1_4g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x40�����:8
 �Ĵ���˵��: CH1 TX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_bp_4g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass */
        unsigned long  ch1_tx_hb_bp_4g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  ch1_tx_rate_4g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                                  2G,     3G,     4G,      TDS,      CDMA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
                                                             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                             2��-------,--------,15.36MHz,--------,--------
                                                             Others��Reserved */
        unsigned long  ch1_tx_mode_dig_4g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                             000��2G(Ĭ��)
                                                             001��3G
                                                             010��4G
                                                             011��TDS
                                                             100��CDMA
                                                             Others��Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_4G_DIG_1_UNION;
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_comp_bp_4g_START   (0)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_comp_bp_4g_END     (0)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_hb_bp_4g_START     (1)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_hb_bp_4g_END       (1)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_rate_4g_START      (2)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_rate_4g_END        (4)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_mode_dig_4g_START  (5)
#define ABB_TX_CH1_4G_DIG_1_ch1_tx_mode_dig_4g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH1_4G_DIG_2_UNION
 �ṹ˵��  : tx_ch1_4g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x1D����ֵ:0x23�����:8
 �Ĵ���˵��: CH1 TX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_q_pd_4g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch1_tx_i_pd_4g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch1_dem_const_4g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                               0��0(Ĭ��)
                                                               1��2
                                                               2��4
                                                               3��6 */
        unsigned long  ch1_uddwa_dith_en_4g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                               0����ʹ��
                                                               1��ʹ�� */
        unsigned long  ch1_dem_dwa_en_4g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                               0��ʹ��CLAģʽ
                                                               1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  ch1_dem_lsb_bp_4g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                               0��DEM LSB ��(Ĭ��)
                                                               1��DEM LSB bypass */
        unsigned long  ch1_dem_msb_bp_4g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                               0��DEM MSB��(Ĭ��)
                                                               1��DEM MSB bypass */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_4G_DIG_2_UNION;
#define ABB_TX_CH1_4G_DIG_2_ch1_tx_q_pd_4g_START        (0)
#define ABB_TX_CH1_4G_DIG_2_ch1_tx_q_pd_4g_END          (0)
#define ABB_TX_CH1_4G_DIG_2_ch1_tx_i_pd_4g_START        (1)
#define ABB_TX_CH1_4G_DIG_2_ch1_tx_i_pd_4g_END          (1)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_const_4g_START      (2)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_const_4g_END        (3)
#define ABB_TX_CH1_4G_DIG_2_ch1_uddwa_dith_en_4g_START  (4)
#define ABB_TX_CH1_4G_DIG_2_ch1_uddwa_dith_en_4g_END    (4)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_dwa_en_4g_START     (5)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_dwa_en_4g_END       (5)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_lsb_bp_4g_START     (6)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_lsb_bp_4g_END       (6)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_msb_bp_4g_START     (7)
#define ABB_TX_CH1_4G_DIG_2_ch1_dem_msb_bp_4g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH1_4G_DIG_3_UNION
 �ṹ˵��  : tx_ch1_4g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x1E����ֵ:0x01�����:8
 �Ĵ���˵��: CH1 TX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0         : 1;  /* bit[0]  : ���� */
        unsigned long  ch1_tx_flush_en_4g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  ch1_tx_comp_sel_4g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11������ϵ���� */
        unsigned long  reserved_1         : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_4G_DIG_3_UNION;
#define ABB_TX_CH1_4G_DIG_3_ch1_tx_flush_en_4g_START  (1)
#define ABB_TX_CH1_4G_DIG_3_ch1_tx_flush_en_4g_END    (1)
#define ABB_TX_CH1_4G_DIG_3_ch1_tx_comp_sel_4g_START  (2)
#define ABB_TX_CH1_4G_DIG_3_ch1_tx_comp_sel_4g_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_DIG_1_UNION
 �ṹ˵��  : rx_idle_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x1F����ֵ:0x00�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_idle : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                              00���̶�ϵ��1��
                                                              01���̶�ϵ��2��
                                                              10���̶�ϵ��3��
                                                              11��reserved�� */
        unsigned long  rx_comp_fix_idle    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                              0��ϵ�����̶����ɼĴ�������
                                                              1��ϵ���̶� */
        unsigned long  rx_hb_bp_idle       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                              0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                              1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_idle        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                  2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                        /TDS_B/4G_C,        /4G_B,
                                                              00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
                                                              others��reserved */
        unsigned long  rx_mode_dig_idle    : 3;  /* bit[5-7]: RXģʽ���ƣ�
                                                              000��2G(Ĭ��)
                                                              001��3G_SC
                                                              010��4G &amp; ET &amp; APT
                                                              011��3G_DC
                                                              100��TDS
                                                              Others��CA */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_1_UNION;
#define ABB_RX_IDLE_DIG_1_rx_comp_sel_b0_idle_START  (0)
#define ABB_RX_IDLE_DIG_1_rx_comp_sel_b0_idle_END    (0)
#define ABB_RX_IDLE_DIG_1_rx_comp_fix_idle_START     (1)
#define ABB_RX_IDLE_DIG_1_rx_comp_fix_idle_END       (1)
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_START        (2)
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_END          (2)
#define ABB_RX_IDLE_DIG_1_rx_rate_idle_START         (3)
#define ABB_RX_IDLE_DIG_1_rx_rate_idle_END           (4)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_START     (5)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_DIG_2_UNION
 �ṹ˵��  : rx_idle_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x13�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_idle         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                              0����CLOCK GATING
                                                              1��CLOCK GATING(Ĭ��)
                                                              (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_idle         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                              0����CLOCK GATING
                                                              1��CLOCK GATING(Ĭ��)
                                                              (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_idle       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                              00��gainΪ0.5(Ĭ��)
                                                              01��gainΪ0.75
                                                              10��gainΪ0.85
                                                              11��Reserved */
        unsigned long  rx_comp_bp_idle     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                              0����bypass(Ĭ��)
                                                              1��bypass */
        unsigned long  rx_clk_inv_idle     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                              0������
                                                              1������ */
        unsigned long  rx_flush_en_idle    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                              0����ʹ��
                                                              1��ʹ�� */
        unsigned long  rx_comp_sel_b1_idle : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_2_UNION;
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_START          (0)
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_END            (0)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_START          (1)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_END            (1)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_START        (2)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_END          (3)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_START      (4)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_END        (4)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_START      (5)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_END        (5)
#define ABB_RX_IDLE_DIG_2_rx_flush_en_idle_START     (6)
#define ABB_RX_IDLE_DIG_2_rx_flush_en_idle_END       (6)
#define ABB_RX_IDLE_DIG_2_rx_comp_sel_b1_idle_START  (7)
#define ABB_RX_IDLE_DIG_2_rx_comp_sel_b1_idle_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_DIG_1_UNION
 �ṹ˵��  : tx_idle_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x21����ֵ:0x02�����:8
 �Ĵ���˵��: TX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_idle  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                           0����bypass(Ĭ��)
                                                           1��bypass */
        unsigned long  tx_hb_bp_idle    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                           0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                           1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_idle     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                                2G,     3G,     4G,      TDS,      CDMA
                                                               (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                           0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
                                                           1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                           2��-------,--------,15.36MHz,--------,--------
                                                           Others��Reserved */
        unsigned long  tx_mode_dig_idle : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                           000��2G(Ĭ��)
                                                           001��3G
                                                           010��4G
                                                           011��TDS
                                                           100��CDMA
                                                           Others��Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_1_UNION;
#define ABB_TX_IDLE_DIG_1_tx_comp_bp_idle_START   (0)
#define ABB_TX_IDLE_DIG_1_tx_comp_bp_idle_END     (0)
#define ABB_TX_IDLE_DIG_1_tx_hb_bp_idle_START     (1)
#define ABB_TX_IDLE_DIG_1_tx_hb_bp_idle_END       (1)
#define ABB_TX_IDLE_DIG_1_tx_rate_idle_START      (2)
#define ABB_TX_IDLE_DIG_1_tx_rate_idle_END        (4)
#define ABB_TX_IDLE_DIG_1_tx_mode_dig_idle_START  (5)
#define ABB_TX_IDLE_DIG_1_tx_mode_dig_idle_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_DIG_2_UNION
 �ṹ˵��  : tx_idle_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x22����ֵ:0x23�����:8
 �Ĵ���˵��: TX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_q_pd_idle       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_idle       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_idle     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                             0��0(Ĭ��)
                                                             1��2
                                                             2��4
                                                             3��6 */
        unsigned long  uddwa_dith_en_idle : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  dem_dwa_en_idle    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                             0��ʹ��CLAģʽ
                                                             1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  dem_lsb_bp_idle    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                             0��DEM LSB ��(Ĭ��)
                                                             1��DEM LSB bypass */
        unsigned long  dem_msb_bp_idle    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                             0��DEM MSB��(Ĭ��)
                                                             1��DEM MSB bypass */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_2_UNION;
#define ABB_TX_IDLE_DIG_2_tx_q_pd_idle_START        (0)
#define ABB_TX_IDLE_DIG_2_tx_q_pd_idle_END          (0)
#define ABB_TX_IDLE_DIG_2_tx_i_pd_idle_START        (1)
#define ABB_TX_IDLE_DIG_2_tx_i_pd_idle_END          (1)
#define ABB_TX_IDLE_DIG_2_dem_const_idle_START      (2)
#define ABB_TX_IDLE_DIG_2_dem_const_idle_END        (3)
#define ABB_TX_IDLE_DIG_2_uddwa_dith_en_idle_START  (4)
#define ABB_TX_IDLE_DIG_2_uddwa_dith_en_idle_END    (4)
#define ABB_TX_IDLE_DIG_2_dem_dwa_en_idle_START     (5)
#define ABB_TX_IDLE_DIG_2_dem_dwa_en_idle_END       (5)
#define ABB_TX_IDLE_DIG_2_dem_lsb_bp_idle_START     (6)
#define ABB_TX_IDLE_DIG_2_dem_lsb_bp_idle_END       (6)
#define ABB_TX_IDLE_DIG_2_dem_msb_bp_idle_START     (7)
#define ABB_TX_IDLE_DIG_2_dem_msb_bp_idle_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_DIG_3_UNION
 �ṹ˵��  : tx_idle_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x23����ֵ:0x01�����:8
 �Ĵ���˵��: TX IDLEģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0       : 1;  /* bit[0]  : ���� */
        unsigned long  tx_flush_en_idle : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  tx_comp_sel_idle : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                           00���̶�ϵ��1��
                                                           01���̶�ϵ��2��
                                                           10���̶�ϵ��3��
                                                           11������ϵ���� */
        unsigned long  reserved_1       : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_3_UNION;
#define ABB_TX_IDLE_DIG_3_tx_flush_en_idle_START  (1)
#define ABB_TX_IDLE_DIG_3_tx_flush_en_idle_END    (1)
#define ABB_TX_IDLE_DIG_3_tx_comp_sel_idle_START  (2)
#define ABB_TX_IDLE_DIG_3_tx_comp_sel_idle_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TESTMODE_UNION
 �ṹ˵��  : ch1_testmode �Ĵ����ṹ���塣��ַƫ����:0x41����ֵ:0x00�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_pwr_on_rst  : 1;  /* bit[0]  : ȫ����λ�źţ�comstarV520 Reserved
                                                          0������λ(Ĭ��)
                                                          1����λ�������ֵ�·��ģ���· */
        unsigned long  ch1_rx_chnl_sel : 2;  /* bit[1-2]: RXģ�����ģʽ��ͨ��ѡ��
                                                          00�����RXA Iģ�����������(Ĭ��)
                                                          01�����RXA Qģ�����������
                                                          10�����RXB Iģ�����������
                                                          11�����RXB Qģ����������� */
        unsigned long  ch1_test_mode   : 3;  /* bit[3-5]: bit[4:3]����ģʽ���ƣ�
                                                          00������ģʽ(Ĭ��)
                                                          01�������㷨�߼�����ģʽ
                                                          10��RXģ�����ģʽ(bypass RX�����˲���)
                                                          11��Reserved
                                                          bit[5]RXCͨ������ʹ�ܣ�
                                                          0������ģʽ(Ĭ��)��RXAͨ��ѡ��RXA��������������
                                                          1��RXCͨ������ģʽ(��RXCͨ���������ݸ��õ�RXAͨ��) */
        unsigned long  ch1_rx_sw_rst   : 1;  /* bit[6]  : ���ֲ���RXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
        unsigned long  ch1_tx_sw_rst   : 1;  /* bit[7]  : ���ֲ���TXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TESTMODE_UNION;
#define ABB_CH1_TESTMODE_ch1_pwr_on_rst_START   (0)
#define ABB_CH1_TESTMODE_ch1_pwr_on_rst_END     (0)
#define ABB_CH1_TESTMODE_ch1_rx_chnl_sel_START  (1)
#define ABB_CH1_TESTMODE_ch1_rx_chnl_sel_END    (2)
#define ABB_CH1_TESTMODE_ch1_test_mode_START    (3)
#define ABB_CH1_TESTMODE_ch1_test_mode_END      (5)
#define ABB_CH1_TESTMODE_ch1_rx_sw_rst_START    (6)
#define ABB_CH1_TESTMODE_ch1_rx_sw_rst_END      (6)
#define ABB_CH1_TESTMODE_ch1_tx_sw_rst_START    (7)
#define ABB_CH1_TESTMODE_ch1_tx_sw_rst_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_CTRL_UNION
 �ṹ˵��  : ch1_ctrl �Ĵ����ṹ���塣��ַƫ����:0x42����ֵ:0x03�����:8
 �Ĵ���˵��: ͨ�����ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_loop_out : 1;  /* bit[0]  : CH1ͨ��RXA������������źţ�0�����ز�����źţ�1������ͬʱ����źţ� */
        unsigned long  ch1_rxb_loop_out : 1;  /* bit[1]  : CH1ͨ��RXB������������źţ�0�����ز�����źţ�1������ͬʱ����źţ� */
        unsigned long  reserved         : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_CTRL_UNION;
#define ABB_CH1_CTRL_ch1_rxa_loop_out_START  (0)
#define ABB_CH1_CTRL_ch1_rxa_loop_out_END    (0)
#define ABB_CH1_CTRL_ch1_rxb_loop_out_START  (1)
#define ABB_CH1_CTRL_ch1_rxb_loop_out_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXA_I_COEF1_UNION
 �ṹ˵��  : ch1_rxa_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0x4B����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_i_c1     : 7;  /* bit[0-6]: RXAͨ��I·�����˲���ϵ��C1,�з����� */
        unsigned long  ch1_rxa_i_c3_msb : 1;  /* bit[7]  : RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_I_COEF1_UNION;
#define ABB_CH1_RXA_I_COEF1_ch1_rxa_i_c1_START      (0)
#define ABB_CH1_RXA_I_COEF1_ch1_rxa_i_c1_END        (6)
#define ABB_CH1_RXA_I_COEF1_ch1_rxa_i_c3_msb_START  (7)
#define ABB_CH1_RXA_I_COEF1_ch1_rxa_i_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXA_I_COEF3_UNION
 �ṹ˵��  : ch1_rxa_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0x4D����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_i_c5 : 7;  /* bit[0-6]: RXAͨ��I·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_I_COEF3_UNION;
#define ABB_CH1_RXA_I_COEF3_ch1_rxa_i_c5_START  (0)
#define ABB_CH1_RXA_I_COEF3_ch1_rxa_i_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXA_Q_COEF1_UNION
 �ṹ˵��  : ch1_rxa_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0x50����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_q_c1     : 7;  /* bit[0-6]: RXAͨ��Q·�����˲���ϵ��C1,�з����� */
        unsigned long  ch1_rxa_q_c3_msb : 1;  /* bit[7]  : RXAͨ��Q·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_Q_COEF1_UNION;
#define ABB_CH1_RXA_Q_COEF1_ch1_rxa_q_c1_START      (0)
#define ABB_CH1_RXA_Q_COEF1_ch1_rxa_q_c1_END        (6)
#define ABB_CH1_RXA_Q_COEF1_ch1_rxa_q_c3_msb_START  (7)
#define ABB_CH1_RXA_Q_COEF1_ch1_rxa_q_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXA_Q_COEF3_UNION
 �ṹ˵��  : ch1_rxa_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0x52����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_q_c5 : 7;  /* bit[0-6]: RXAͨ��Q·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_Q_COEF3_UNION;
#define ABB_CH1_RXA_Q_COEF3_ch1_rxa_q_c5_START  (0)
#define ABB_CH1_RXA_Q_COEF3_ch1_rxa_q_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_I_COEF1_UNION
 �ṹ˵��  : ch1_rxb_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0x55����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_i_c1     : 7;  /* bit[0-6]: RXBͨ��I·�����˲���ϵ��C1,�з����� */
        unsigned long  ch1_rxb_i_c3_msb : 1;  /* bit[7]  : RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_I_COEF1_UNION;
#define ABB_CH1_RXB_I_COEF1_ch1_rxb_i_c1_START      (0)
#define ABB_CH1_RXB_I_COEF1_ch1_rxb_i_c1_END        (6)
#define ABB_CH1_RXB_I_COEF1_ch1_rxb_i_c3_msb_START  (7)
#define ABB_CH1_RXB_I_COEF1_ch1_rxb_i_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_I_COEF3_UNION
 �ṹ˵��  : ch1_rxb_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0x57����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_i_c5 : 7;  /* bit[0-6]: RXBͨ��I·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_I_COEF3_UNION;
#define ABB_CH1_RXB_I_COEF3_ch1_rxb_i_c5_START  (0)
#define ABB_CH1_RXB_I_COEF3_ch1_rxb_i_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_Q_COEF1_UNION
 �ṹ˵��  : ch1_rxb_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0x5A����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_q_c1     : 7;  /* bit[0-6]: RXBͨ��Q·�����˲���ϵ��C1,�з����� */
        unsigned long  ch1_rxb_q_c3_msb : 1;  /* bit[7]  : RXBͨ��Q·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_Q_COEF1_UNION;
#define ABB_CH1_RXB_Q_COEF1_ch1_rxb_q_c1_START      (0)
#define ABB_CH1_RXB_Q_COEF1_ch1_rxb_q_c1_END        (6)
#define ABB_CH1_RXB_Q_COEF1_ch1_rxb_q_c3_msb_START  (7)
#define ABB_CH1_RXB_Q_COEF1_ch1_rxb_q_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_Q_COEF3_UNION
 �ṹ˵��  : ch1_rxb_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0x5C����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_q_c5 : 7;  /* bit[0-6]: RXBͨ��Q·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_Q_COEF3_UNION;
#define ABB_CH1_RXB_Q_COEF3_ch1_rxb_q_c5_START  (0)
#define ABB_CH1_RXB_Q_COEF3_ch1_rxb_q_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXA_DCR_CFG_UNION
 �ṹ˵��  : ch1_reg_rxa_dcr_cfg �Ĵ����ṹ���塣��ַƫ����:0x5E����ֵ:0x46�����:8
 �Ĵ���˵��: RXAͨ��BLOCKING DCR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_cfg_rxa_dcr_dly    : 5;  /* bit[0-4]: RXA����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣 */
        unsigned long  ch1_cfg_rxa_dcr_l_para : 3;  /* bit[5-7]: RXA����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ�� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXA_DCR_CFG_UNION;
#define ABB_CH1_REG_RXA_DCR_CFG_ch1_cfg_rxa_dcr_dly_START     (0)
#define ABB_CH1_REG_RXA_DCR_CFG_ch1_cfg_rxa_dcr_dly_END       (4)
#define ABB_CH1_REG_RXA_DCR_CFG_ch1_cfg_rxa_dcr_l_para_START  (5)
#define ABB_CH1_REG_RXA_DCR_CFG_ch1_cfg_rxa_dcr_l_para_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXB_DCR_CFG_UNION
 �ṹ˵��  : ch1_reg_rxb_dcr_cfg �Ĵ����ṹ���塣��ַƫ����:0x5F����ֵ:0x46�����:8
 �Ĵ���˵��: RXBͨ��BLOCKING DCR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_cfg_rxb_dcr_dly    : 5;  /* bit[0-4]: RXB����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣 */
        unsigned long  ch1_cfg_rxb_dcr_l_para : 3;  /* bit[5-7]: RXB����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ�� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXB_DCR_CFG_UNION;
#define ABB_CH1_REG_RXB_DCR_CFG_ch1_cfg_rxb_dcr_dly_START     (0)
#define ABB_CH1_REG_RXB_DCR_CFG_ch1_cfg_rxb_dcr_dly_END       (4)
#define ABB_CH1_REG_RXB_DCR_CFG_ch1_cfg_rxb_dcr_l_para_START  (5)
#define ABB_CH1_REG_RXB_DCR_CFG_ch1_cfg_rxb_dcr_l_para_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RX_DCR_CTRL_UNION
 �ṹ˵��  : ch1_reg_rx_dcr_ctrl �Ĵ����ṹ���塣��ַƫ����:0x60����ֵ:0x00�����:8
 �Ĵ���˵��: BLOCKING DCR���ܿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_cfg_rxa_dcr_bypass : 1;  /* bit[0]  : RXA����BLOCKING DCR����bypass���ơ�
                                                                 0��DCR���ܲ�bypasss��
                                                                 1��DCR����bypass�� */
        unsigned long  ch1_cfg_rxb_dcr_bypass : 1;  /* bit[1]  : RXB����BLOCKING DCR����bypass���ơ�
                                                                 0��DCR���ܲ�bypasss��
                                                                 1��DCR����bypass�� */
        unsigned long  reserved               : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RX_DCR_CTRL_UNION;
#define ABB_CH1_REG_RX_DCR_CTRL_ch1_cfg_rxa_dcr_bypass_START  (0)
#define ABB_CH1_REG_RX_DCR_CTRL_ch1_cfg_rxa_dcr_bypass_END    (0)
#define ABB_CH1_REG_RX_DCR_CTRL_ch1_cfg_rxb_dcr_bypass_START  (1)
#define ABB_CH1_REG_RX_DCR_CTRL_ch1_cfg_rxb_dcr_bypass_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXA_BLOCKING_UNION
 �ṹ˵��  : ch1_rxa_blocking �Ĵ����ṹ���塣��ַƫ����:0x61����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��BLOCKING�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_blk_coeff : 5;  /* bit[0-4]: RXA����BLOCKING�ϱ�ֵ,2���ݴ�M */
        unsigned long  ch1_rxa_blk_power : 3;  /* bit[5-7]: RXA����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_BLOCKING_UNION;
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_coeff_START  (0)
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_coeff_END    (4)
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_power_START  (5)
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_power_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_BLOCKING_UNION
 �ṹ˵��  : ch1_rxb_blocking �Ĵ����ṹ���塣��ַƫ����:0x62����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��BLOCKING�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_blk_coeff : 5;  /* bit[0-4]: RXB����BLOCKING�ϱ�ֵ,2���ݴ�M */
        unsigned long  ch1_rxb_blk_power : 3;  /* bit[5-7]: RXB����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_BLOCKING_UNION;
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_coeff_START  (0)
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_coeff_END    (4)
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_power_START  (5)
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_power_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXA_DC_I_2_UNION
 �ṹ˵��  : ch1_reg_rxa_dc_i_2 �Ĵ����ṹ���塣��ַƫ����:0x64����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch1_rxa_dc_i_2 : 4;  /* bit[4-7]: RXA����I·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXA_DC_I_2_UNION;
#define ABB_CH1_REG_RXA_DC_I_2_ch1_rxa_dc_i_2_START  (4)
#define ABB_CH1_REG_RXA_DC_I_2_ch1_rxa_dc_i_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXA_DC_Q_2_UNION
 �ṹ˵��  : ch1_reg_rxa_dc_q_2 �Ĵ����ṹ���塣��ַƫ����:0x66����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch1_rxa_dc_q_2 : 4;  /* bit[4-7]: RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXA_DC_Q_2_UNION;
#define ABB_CH1_REG_RXA_DC_Q_2_ch1_rxa_dc_q_2_START  (4)
#define ABB_CH1_REG_RXA_DC_Q_2_ch1_rxa_dc_q_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXB_DC_I_2_UNION
 �ṹ˵��  : ch1_reg_rxb_dc_i_2 �Ĵ����ṹ���塣��ַƫ����:0x68����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch1_rxb_dc_i_2 : 4;  /* bit[4-7]: RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXB_DC_I_2_UNION;
#define ABB_CH1_REG_RXB_DC_I_2_ch1_rxb_dc_i_2_START  (4)
#define ABB_CH1_REG_RXB_DC_I_2_ch1_rxb_dc_i_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXB_DC_Q_2_UNION
 �ṹ˵��  : ch1_reg_rxb_dc_q_2 �Ĵ����ṹ���塣��ַƫ����:0x6A����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch1_rxb_dc_q_2 : 4;  /* bit[4-7]: RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXB_DC_Q_2_UNION;
#define ABB_CH1_REG_RXB_DC_Q_2_ch1_rxb_dc_q_2_START  (4)
#define ABB_CH1_REG_RXB_DC_Q_2_ch1_rxb_dc_q_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_DIG0_UNION
 �ṹ˵��  : ch1_reg_debug_dig0 �Ĵ����ṹ���塣��ַƫ����:0x6B����ֵ:0x64�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_sdm_rst_ctrl  : 1;  /* bit[0]  : TXͨ��SDMģ���쳣ʱ��λ����
                                                            0��ֻ��λSDMģ��
                                                            1����λ����TXͨ�� */
        unsigned long  ch1_dem_mode      : 1;  /* bit[1]  : TXͨ��DEMУ׼����ģʽ
                                                            0����������
                                                            1��У׼̬��DEM���Ϊdem_code_man */
        unsigned long  ch1_tx_dem_sat    : 2;  /* bit[2-3]: TX DEM�����������޷���λ��
                                                            00��0.8125
                                                            01��0.796875(Ĭ��)
                                                            10��0.765625
                                                            11��0.75 */
        unsigned long  ch1_dither_en     : 1;  /* bit[4]  : TXͨ��SDM Dither���ƣ�
                                                            0����ʹ��
                                                            1��ʹ�� */
        unsigned long  ch1_tuning_val_en : 1;  /* bit[5]  : Tuning code��Դѡ��
                                                            0���Ĵ�������
                                                            1���Զ����£�Ĭ�ϣ� */
        unsigned long  ch1_tx_main_sd_bp : 1;  /* bit[6]  : TX SDģ������������·ʹ�ܣ�
                                                            0��������������·��
                                                            1������������·��Ĭ�ϣ��� */
        unsigned long  reserved          : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_DIG0_UNION;
#define ABB_CH1_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_START   (0)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_END     (0)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dem_mode_START       (1)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dem_mode_END         (1)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tx_dem_sat_START     (2)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tx_dem_sat_END       (3)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dither_en_START      (4)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dither_en_END        (4)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tuning_val_en_START  (5)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tuning_val_en_END    (5)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tx_main_sd_bp_START  (6)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tx_main_sd_bp_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TESTMODE_UNION
 �ṹ˵��  : ch0_testmode �Ĵ����ṹ���塣��ַƫ����:0xA1����ֵ:0x00�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_pwr_on_rst  : 1;  /* bit[0]  : ȫ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ�������ֵ�·��ģ���· */
        unsigned long  ch0_rx_chnl_sel : 2;  /* bit[1-2]: RXģ�����ģʽ��ͨ��ѡ��
                                                          00�����RXA Iģ�����������(Ĭ��)
                                                          01�����RXA Qģ�����������
                                                          10�����RXB Iģ�����������
                                                          11�����RXB Qģ����������� */
        unsigned long  ch0_test_mode   : 3;  /* bit[3-5]: bit[4:3]����ģʽ���ƣ�
                                                          00������ģʽ(Ĭ��)
                                                          01�������㷨�߼�����ģʽ
                                                          10��RXģ�����ģʽ(bypass RX�����˲���)
                                                          11������/ģ��ӿڻ���
                                                          bit[5]RXCͨ������ʹ�ܣ���ComstarV510 reserved��
                                                          0������ģʽ(Ĭ��)��RXAͨ��ѡ��RXA��������������
                                                          1��RXCͨ������ģʽ(��RXCͨ���������ݸ��õ�RXAͨ��) */
        unsigned long  ch0_rx_sw_rst   : 1;  /* bit[6]  : ���ֲ���RXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
        unsigned long  ch0_tx_sw_rst   : 1;  /* bit[7]  : ���ֲ���TXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TESTMODE_UNION;
#define ABB_CH0_TESTMODE_ch0_pwr_on_rst_START   (0)
#define ABB_CH0_TESTMODE_ch0_pwr_on_rst_END     (0)
#define ABB_CH0_TESTMODE_ch0_rx_chnl_sel_START  (1)
#define ABB_CH0_TESTMODE_ch0_rx_chnl_sel_END    (2)
#define ABB_CH0_TESTMODE_ch0_test_mode_START    (3)
#define ABB_CH0_TESTMODE_ch0_test_mode_END      (5)
#define ABB_CH0_TESTMODE_ch0_rx_sw_rst_START    (6)
#define ABB_CH0_TESTMODE_ch0_rx_sw_rst_END      (6)
#define ABB_CH0_TESTMODE_ch0_tx_sw_rst_START    (7)
#define ABB_CH0_TESTMODE_ch0_tx_sw_rst_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_CTRL_UNION
 �ṹ˵��  : ch0_ctrl �Ĵ����ṹ���塣��ַƫ����:0xA2����ֵ:0x03�����:8
 �Ĵ���˵��: ͨ�����ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_loop_out : 1;  /* bit[0]  : CH0ͨ��RXA������������źţ�0�����ز�����źţ�1������ͬʱ����źţ� */
        unsigned long  ch0_rxb_loop_out : 1;  /* bit[1]  : CH0ͨ��RXB������������źţ�0�����ز�����źţ�1������ͬʱ����źţ� */
        unsigned long  reserved         : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CTRL_UNION;
#define ABB_CH0_CTRL_ch0_rxa_loop_out_START  (0)
#define ABB_CH0_CTRL_ch0_rxa_loop_out_END    (0)
#define ABB_CH0_CTRL_ch0_rxb_loop_out_START  (1)
#define ABB_CH0_CTRL_ch0_rxb_loop_out_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_I_COEF1_UNION
 �ṹ˵��  : ch0_rxa_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0xAB����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_i_c1     : 7;  /* bit[0-6]: RXAͨ��I·�����˲���ϵ��C1,�з����� */
        unsigned long  ch0_rxa_i_c3_msb : 1;  /* bit[7]  : RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_COEF1_UNION;
#define ABB_CH0_RXA_I_COEF1_ch0_rxa_i_c1_START      (0)
#define ABB_CH0_RXA_I_COEF1_ch0_rxa_i_c1_END        (6)
#define ABB_CH0_RXA_I_COEF1_ch0_rxa_i_c3_msb_START  (7)
#define ABB_CH0_RXA_I_COEF1_ch0_rxa_i_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_I_COEF3_UNION
 �ṹ˵��  : ch0_rxa_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0xAD����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_i_c5 : 7;  /* bit[0-6]: RXAͨ��I·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_COEF3_UNION;
#define ABB_CH0_RXA_I_COEF3_ch0_rxa_i_c5_START  (0)
#define ABB_CH0_RXA_I_COEF3_ch0_rxa_i_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_Q_COEF1_UNION
 �ṹ˵��  : ch0_rxa_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0xB0����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_q_c1     : 7;  /* bit[0-6]: RXAͨ��Q·�����˲���ϵ��C1,�з����� */
        unsigned long  ch0_rxa_q_c3_msb : 1;  /* bit[7]  : RXAͨ��Q·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_COEF1_UNION;
#define ABB_CH0_RXA_Q_COEF1_ch0_rxa_q_c1_START      (0)
#define ABB_CH0_RXA_Q_COEF1_ch0_rxa_q_c1_END        (6)
#define ABB_CH0_RXA_Q_COEF1_ch0_rxa_q_c3_msb_START  (7)
#define ABB_CH0_RXA_Q_COEF1_ch0_rxa_q_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_Q_COEF3_UNION
 �ṹ˵��  : ch0_rxa_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0xB2����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_q_c5 : 7;  /* bit[0-6]: RXAͨ��Q·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_COEF3_UNION;
#define ABB_CH0_RXA_Q_COEF3_ch0_rxa_q_c5_START  (0)
#define ABB_CH0_RXA_Q_COEF3_ch0_rxa_q_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_I_COEF1_UNION
 �ṹ˵��  : ch0_rxb_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0xB5����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_i_c1     : 7;  /* bit[0-6]: RXBͨ��I·�����˲���ϵ��C1,�з����� */
        unsigned long  ch0_rxb_i_c3_msb : 1;  /* bit[7]  : RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_COEF1_UNION;
#define ABB_CH0_RXB_I_COEF1_ch0_rxb_i_c1_START      (0)
#define ABB_CH0_RXB_I_COEF1_ch0_rxb_i_c1_END        (6)
#define ABB_CH0_RXB_I_COEF1_ch0_rxb_i_c3_msb_START  (7)
#define ABB_CH0_RXB_I_COEF1_ch0_rxb_i_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_I_COEF3_UNION
 �ṹ˵��  : ch0_rxb_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0xB7����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_i_c5 : 7;  /* bit[0-6]: RXBͨ��I·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_COEF3_UNION;
#define ABB_CH0_RXB_I_COEF3_ch0_rxb_i_c5_START  (0)
#define ABB_CH0_RXB_I_COEF3_ch0_rxb_i_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_Q_COEF1_UNION
 �ṹ˵��  : ch0_rxb_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0xBA����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_q_c1     : 7;  /* bit[0-6]: RXBͨ��Q·�����˲���ϵ��C1,�з����� */
        unsigned long  ch0_rxb_q_c3_msb : 1;  /* bit[7]  : RXBͨ��Q·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_COEF1_UNION;
#define ABB_CH0_RXB_Q_COEF1_ch0_rxb_q_c1_START      (0)
#define ABB_CH0_RXB_Q_COEF1_ch0_rxb_q_c1_END        (6)
#define ABB_CH0_RXB_Q_COEF1_ch0_rxb_q_c3_msb_START  (7)
#define ABB_CH0_RXB_Q_COEF1_ch0_rxb_q_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_Q_COEF3_UNION
 �ṹ˵��  : ch0_rxb_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0xBC����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_q_c5 : 7;  /* bit[0-6]: RXBͨ��Q·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_COEF3_UNION;
#define ABB_CH0_RXB_Q_COEF3_ch0_rxb_q_c5_START  (0)
#define ABB_CH0_RXB_Q_COEF3_ch0_rxb_q_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXA_DCR_CFG_UNION
 �ṹ˵��  : ch0_reg_rxa_dcr_cfg �Ĵ����ṹ���塣��ַƫ����:0xBE����ֵ:0x46�����:8
 �Ĵ���˵��: RXAͨ��BLOCKING DCR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_cfg_rxa_dcr_dly    : 5;  /* bit[0-4]: RXA����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣 */
        unsigned long  ch0_cfg_rxa_dcr_l_para : 3;  /* bit[5-7]: RXA����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ�� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXA_DCR_CFG_UNION;
#define ABB_CH0_REG_RXA_DCR_CFG_ch0_cfg_rxa_dcr_dly_START     (0)
#define ABB_CH0_REG_RXA_DCR_CFG_ch0_cfg_rxa_dcr_dly_END       (4)
#define ABB_CH0_REG_RXA_DCR_CFG_ch0_cfg_rxa_dcr_l_para_START  (5)
#define ABB_CH0_REG_RXA_DCR_CFG_ch0_cfg_rxa_dcr_l_para_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXB_DCR_CFG_UNION
 �ṹ˵��  : ch0_reg_rxb_dcr_cfg �Ĵ����ṹ���塣��ַƫ����:0xBF����ֵ:0x46�����:8
 �Ĵ���˵��: RXBͨ��BLOCKING DCR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_cfg_rxb_dcr_dly    : 5;  /* bit[0-4]: RXB����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣 */
        unsigned long  ch0_cfg_rxb_dcr_l_para : 3;  /* bit[5-7]: RXB����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ�� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXB_DCR_CFG_UNION;
#define ABB_CH0_REG_RXB_DCR_CFG_ch0_cfg_rxb_dcr_dly_START     (0)
#define ABB_CH0_REG_RXB_DCR_CFG_ch0_cfg_rxb_dcr_dly_END       (4)
#define ABB_CH0_REG_RXB_DCR_CFG_ch0_cfg_rxb_dcr_l_para_START  (5)
#define ABB_CH0_REG_RXB_DCR_CFG_ch0_cfg_rxb_dcr_l_para_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RX_DCR_CTRL_UNION
 �ṹ˵��  : ch0_reg_rx_dcr_ctrl �Ĵ����ṹ���塣��ַƫ����:0xC0����ֵ:0x00�����:8
 �Ĵ���˵��: BLOCKING DCR���ܿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_cfg_rxa_dcr_bypass : 1;  /* bit[0]  : RXA����BLOCKING DCR����bypass���ơ�
                                                                 0��DCR���ܲ�bypasss��
                                                                 1��DCR����bypass�� */
        unsigned long  ch0_cfg_rxb_dcr_bypass : 1;  /* bit[1]  : RXB����BLOCKING DCR����bypass���ơ�
                                                                 0��DCR���ܲ�bypasss��
                                                                 1��DCR����bypass�� */
        unsigned long  reserved               : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RX_DCR_CTRL_UNION;
#define ABB_CH0_REG_RX_DCR_CTRL_ch0_cfg_rxa_dcr_bypass_START  (0)
#define ABB_CH0_REG_RX_DCR_CTRL_ch0_cfg_rxa_dcr_bypass_END    (0)
#define ABB_CH0_REG_RX_DCR_CTRL_ch0_cfg_rxb_dcr_bypass_START  (1)
#define ABB_CH0_REG_RX_DCR_CTRL_ch0_cfg_rxb_dcr_bypass_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_BLOCKING_UNION
 �ṹ˵��  : ch0_rxa_blocking �Ĵ����ṹ���塣��ַƫ����:0xC1����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��BLOCKING�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_blk_coeff : 5;  /* bit[0-4]: RXA����BLOCKING�ϱ�ֵ,2���ݴ�M */
        unsigned long  ch0_rxa_blk_power : 3;  /* bit[5-7]: RXA����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_BLOCKING_UNION;
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_coeff_START  (0)
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_coeff_END    (4)
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_power_START  (5)
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_power_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_BLOCKING_UNION
 �ṹ˵��  : ch0_rxb_blocking �Ĵ����ṹ���塣��ַƫ����:0xC2����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��BLOCKING�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_blk_coeff : 5;  /* bit[0-4]: RXB����BLOCKING�ϱ�ֵ,2���ݴ�M */
        unsigned long  ch0_rxb_blk_power : 3;  /* bit[5-7]: RXB����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_BLOCKING_UNION;
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_coeff_START  (0)
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_coeff_END    (4)
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_power_START  (5)
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_power_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXA_DC_I_2_UNION
 �ṹ˵��  : ch0_reg_rxa_dc_i_2 �Ĵ����ṹ���塣��ַƫ����:0xC4����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch0_rxa_dc_i_2 : 4;  /* bit[4-7]: RXA����I·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXA_DC_I_2_UNION;
#define ABB_CH0_REG_RXA_DC_I_2_ch0_rxa_dc_i_2_START  (4)
#define ABB_CH0_REG_RXA_DC_I_2_ch0_rxa_dc_i_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXA_DC_Q_2_UNION
 �ṹ˵��  : ch0_reg_rxa_dc_q_2 �Ĵ����ṹ���塣��ַƫ����:0xC6����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch0_rxa_dc_q_2 : 4;  /* bit[4-7]: RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXA_DC_Q_2_UNION;
#define ABB_CH0_REG_RXA_DC_Q_2_ch0_rxa_dc_q_2_START  (4)
#define ABB_CH0_REG_RXA_DC_Q_2_ch0_rxa_dc_q_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXB_DC_I_2_UNION
 �ṹ˵��  : ch0_reg_rxb_dc_i_2 �Ĵ����ṹ���塣��ַƫ����:0xC8����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch0_rxb_dc_i_2 : 4;  /* bit[4-7]: RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXB_DC_I_2_UNION;
#define ABB_CH0_REG_RXB_DC_I_2_ch0_rxb_dc_i_2_START  (4)
#define ABB_CH0_REG_RXB_DC_I_2_ch0_rxb_dc_i_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXB_DC_Q_2_UNION
 �ṹ˵��  : ch0_reg_rxb_dc_q_2 �Ĵ����ṹ���塣��ַƫ����:0xCA����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch0_rxb_dc_q_2 : 4;  /* bit[4-7]: RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXB_DC_Q_2_UNION;
#define ABB_CH0_REG_RXB_DC_Q_2_ch0_rxb_dc_q_2_START  (4)
#define ABB_CH0_REG_RXB_DC_Q_2_ch0_rxb_dc_q_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_DIG0_UNION
 �ṹ˵��  : ch0_reg_debug_dig0 �Ĵ����ṹ���塣��ַƫ����:0xCB����ֵ:0x64�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_sdm_rst_ctrl  : 1;  /* bit[0]  : TXͨ��SDMģ���쳣ʱ��λ����
                                                            0��ֻ��λSDMģ��
                                                            1����λ����TXͨ�� */
        unsigned long  ch0_dem_mode      : 1;  /* bit[1]  : TXͨ��DEMУ׼����ģʽ
                                                            0����������
                                                            1��У׼̬��DEM���Ϊdem_code_man */
        unsigned long  ch0_tx_dem_sat    : 2;  /* bit[2-3]: TX DEM�����������޷���λ��
                                                            00��0.8125
                                                            01��0.796875(Ĭ��)
                                                            10��0.765625
                                                            11��0.75 */
        unsigned long  ch0_dither_en     : 1;  /* bit[4]  : TXͨ��SDM Dither���ƣ�
                                                            0����ʹ��
                                                            1��ʹ�� */
        unsigned long  ch0_tuning_val_en : 1;  /* bit[5]  : Tuning code��Դѡ��
                                                            0���Ĵ�������
                                                            1���Զ����£�Ĭ�ϣ� */
        unsigned long  ch0_tx_main_sd_bp : 1;  /* bit[6]  : TX SDģ������������·ʹ�ܣ�
                                                            0��������������·��
                                                            1������������·��Ĭ�ϣ��� */
        unsigned long  reserved          : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_DIG0_UNION;
#define ABB_CH0_REG_DEBUG_DIG0_ch0_sdm_rst_ctrl_START   (0)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_sdm_rst_ctrl_END     (0)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dem_mode_START       (1)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dem_mode_END         (1)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tx_dem_sat_START     (2)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tx_dem_sat_END       (3)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dither_en_START      (4)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dither_en_END        (4)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tuning_val_en_START  (5)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tuning_val_en_END    (5)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tx_main_sd_bp_START  (6)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tx_main_sd_bp_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_SINE_GENERATE_UNION
 �ṹ˵��  : sine_generate �Ĵ����ṹ���塣��ַƫ����:0xFF����ֵ:0x10�����:8
 �Ĵ���˵��: SINE���ͼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_sine_enable : 1;  /* bit[0]  : ch0���Ҳ�����ʹ��
                                                          0��������
                                                          1������ */
        unsigned long  ch1_sine_enable : 1;  /* bit[1]  : ch1���Ҳ�����ʹ��
                                                          0��������
                                                          1������ */
        unsigned long  sine_amp        : 2;  /* bit[2-3]: ���Ҳ����ͷ��ȿ���
                                                          00��������
                                                          01��3/4����
                                                          10��1/2����
                                                          11��1/4���� */
        unsigned long  sine_freq       : 4;  /* bit[4-7]: ���Ҳ�����Ƶ�ʿ��ƣ���λ(freq of tx_hb_clk)/32�����䷶ΧΪ1~f */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_SINE_GENERATE_UNION;
#define ABB_SINE_GENERATE_ch0_sine_enable_START  (0)
#define ABB_SINE_GENERATE_ch0_sine_enable_END    (0)
#define ABB_SINE_GENERATE_ch1_sine_enable_START  (1)
#define ABB_SINE_GENERATE_ch1_sine_enable_END    (1)
#define ABB_SINE_GENERATE_sine_amp_START         (2)
#define ABB_SINE_GENERATE_sine_amp_END           (3)
#define ABB_SINE_GENERATE_sine_freq_START        (4)
#define ABB_SINE_GENERATE_sine_freq_END          (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_3G_DIG_1_UNION
 �ṹ˵��  : rx_ch1_3g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x180����ֵ:0x26�����:8
 �Ĵ���˵��: CH1 RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_comp_sel_b0_3g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                                00���̶�ϵ��1��
                                                                01���̶�ϵ��2��
                                                                10���̶�ϵ��3��
                                                                11��reserved�� */
        unsigned long  ch1_rx_comp_fix_3g    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                                0��ϵ�����̶����ɼĴ�������
                                                                1��ϵ���̶� */
        unsigned long  ch1_rx_hb_bp_3g       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                                0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                                1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  ch1_rx_rate_3g        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                    2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                          /TDS_B/4G_C,        /4G_B,
                                                                00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
                                                                others��reserved */
        unsigned long  ch1_rx_mode_dig_3g    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                                000��2G(Ĭ��)
                                                                001��3G_SC/TDS_B/4G_C
                                                                010��4G
                                                                011��3G_DC/4G_B
                                                                100��TDS
                                                                101��CDMA
                                                                Others��Reserved */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_3G_DIG_1_UNION;
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_comp_sel_b0_3g_START  (0)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_comp_sel_b0_3g_END    (0)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_comp_fix_3g_START     (1)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_comp_fix_3g_END       (1)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_hb_bp_3g_START        (2)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_hb_bp_3g_END          (2)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_rate_3g_START         (3)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_rate_3g_END           (4)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_mode_dig_3g_START     (5)
#define ABB_RX_CH1_3G_DIG_1_ch1_rx_mode_dig_3g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_3G_DIG_2_UNION
 �ṹ˵��  : rx_ch1_3g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x181����ֵ:0x03�����:8
 �Ĵ���˵��: CH1 RX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_pd_3g         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                                0����CLOCK GATING
                                                                1��CLOCK GATING(Ĭ��)
                                                                (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  ch1_rxb_pd_3g         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                                0����CLOCK GATING
                                                                1��CLOCK GATING(Ĭ��)
                                                                (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  ch1_gain_sel_3g       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                                00��gainΪ0.5(Ĭ��)
                                                                01��gainΪ0.75
                                                                10��gainΪ0.85
                                                                11��Reserved */
        unsigned long  ch1_rx_comp_bp_3g     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                                0����bypass(Ĭ��)
                                                                1��bypass */
        unsigned long  ch1_rx_clk_inv_3g     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                                0������
                                                                1������ */
        unsigned long  ch1_rx_flush_en_3g    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                                0����ʹ��
                                                                1��ʹ�� */
        unsigned long  ch1_rx_comp_sel_b1_3g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_3G_DIG_2_UNION;
#define ABB_RX_CH1_3G_DIG_2_ch1_rxa_pd_3g_START          (0)
#define ABB_RX_CH1_3G_DIG_2_ch1_rxa_pd_3g_END            (0)
#define ABB_RX_CH1_3G_DIG_2_ch1_rxb_pd_3g_START          (1)
#define ABB_RX_CH1_3G_DIG_2_ch1_rxb_pd_3g_END            (1)
#define ABB_RX_CH1_3G_DIG_2_ch1_gain_sel_3g_START        (2)
#define ABB_RX_CH1_3G_DIG_2_ch1_gain_sel_3g_END          (3)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_comp_bp_3g_START      (4)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_comp_bp_3g_END        (4)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_clk_inv_3g_START      (5)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_clk_inv_3g_END        (5)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_flush_en_3g_START     (6)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_flush_en_3g_END       (6)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_comp_sel_b1_3g_START  (7)
#define ABB_RX_CH1_3G_DIG_2_ch1_rx_comp_sel_b1_3g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH1_3G_DIG_1_UNION
 �ṹ˵��  : tx_ch1_3g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x182����ֵ:0x20�����:8
 �Ĵ���˵��: CH1 TX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_bp_3g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass */
        unsigned long  ch1_tx_hb_bp_3g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  ch1_tx_rate_3g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                                  2G,     3G,     4G,      TDS,      CDMA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
                                                             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                             2��-------,--------,15.36MHz,--------,--------
                                                             Others��Reserved */
        unsigned long  ch1_tx_mode_dig_3g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                             000��2G(Ĭ��)
                                                             001��3G
                                                             010��4G
                                                             011��TDS
                                                             100��CDMA
                                                             Others��Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_3G_DIG_1_UNION;
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_comp_bp_3g_START   (0)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_comp_bp_3g_END     (0)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_hb_bp_3g_START     (1)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_hb_bp_3g_END       (1)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_rate_3g_START      (2)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_rate_3g_END        (4)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_mode_dig_3g_START  (5)
#define ABB_TX_CH1_3G_DIG_1_ch1_tx_mode_dig_3g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH1_3G_DIG_2_UNION
 �ṹ˵��  : tx_ch1_3g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x183����ֵ:0x23�����:8
 �Ĵ���˵��: CH1 TX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_q_pd_3g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch1_tx_i_pd_3g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch1_dem_const_3g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                               0��0(Ĭ��)
                                                               1��2
                                                               2��4
                                                               3��6 */
        unsigned long  ch1_uddwa_dith_en_3g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                               0����ʹ��
                                                               1��ʹ�� */
        unsigned long  ch1_dem_dwa_en_3g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                               0��ʹ��CLAģʽ
                                                               1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  ch1_dem_lsb_bp_3g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                               0��DEM LSB ��(Ĭ��)
                                                               1��DEM LSB bypass */
        unsigned long  ch1_dem_msb_bp_3g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                               0��DEM MSB��(Ĭ��)
                                                               1��DEM MSB bypass */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_3G_DIG_2_UNION;
#define ABB_TX_CH1_3G_DIG_2_ch1_tx_q_pd_3g_START        (0)
#define ABB_TX_CH1_3G_DIG_2_ch1_tx_q_pd_3g_END          (0)
#define ABB_TX_CH1_3G_DIG_2_ch1_tx_i_pd_3g_START        (1)
#define ABB_TX_CH1_3G_DIG_2_ch1_tx_i_pd_3g_END          (1)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_const_3g_START      (2)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_const_3g_END        (3)
#define ABB_TX_CH1_3G_DIG_2_ch1_uddwa_dith_en_3g_START  (4)
#define ABB_TX_CH1_3G_DIG_2_ch1_uddwa_dith_en_3g_END    (4)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_dwa_en_3g_START     (5)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_dwa_en_3g_END       (5)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_lsb_bp_3g_START     (6)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_lsb_bp_3g_END       (6)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_msb_bp_3g_START     (7)
#define ABB_TX_CH1_3G_DIG_2_ch1_dem_msb_bp_3g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH1_3G_DIG_3_UNION
 �ṹ˵��  : tx_ch1_3g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x184����ֵ:0x01�����:8
 �Ĵ���˵��: CH1 TX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0         : 1;  /* bit[0]  : ���� */
        unsigned long  ch1_tx_flush_en_3g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  ch1_tx_comp_sel_3g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11������ϵ���� */
        unsigned long  reserved_1         : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_3G_DIG_3_UNION;
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_flush_en_3g_START  (1)
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_flush_en_3g_END    (1)
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_comp_sel_3g_START  (2)
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_comp_sel_3g_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH1_LINE_SEL_UNION
 �ṹ˵��  : ch1_line_sel �Ĵ����ṹ���塣��ַƫ����:0x1C0����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�ǿ������ʹ�ܡ�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_en_sel : 1;  /* bit[0]: RXAͨ���߿�ѡ��ǿ��ʹ��
                                                       0��ѡ���߿�ʹ��
                                                       1��ѡ��ǿ��ʹ�� */
        unsigned long  ch1_rxb_en_sel : 1;  /* bit[1]: RXBͨ���߿�ѡ��ǿ��ʹ��
                                                       0��ѡ���߿�ʹ��
                                                       1��ѡ��ǿ��ʹ�� */
        unsigned long  ch1_tx_en_sel  : 1;  /* bit[2]: TXͨ���߿�ѡ��ǿ��ʹ��
                                                       0��ѡ���߿�ʹ��
                                                       1��ѡ��ǿ��ʹ�� */
        unsigned long  reserved_0     : 1;  /* bit[3]: ���� */
        unsigned long  ch1_rxa_en_cfg : 1;  /* bit[4]: RXAͨ��ǿ���߿� */
        unsigned long  ch1_rxb_en_cfg : 1;  /* bit[5]: RXBͨ��ǿ���߿� */
        unsigned long  ch1_tx_en_cfg  : 1;  /* bit[6]: TXͨ��ǿ���߿� */
        unsigned long  reserved_1     : 1;  /* bit[7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_SEL_UNION;
#define ABB_CH1_LINE_SEL_ch1_rxa_en_sel_START  (0)
#define ABB_CH1_LINE_SEL_ch1_rxa_en_sel_END    (0)
#define ABB_CH1_LINE_SEL_ch1_rxb_en_sel_START  (1)
#define ABB_CH1_LINE_SEL_ch1_rxb_en_sel_END    (1)
#define ABB_CH1_LINE_SEL_ch1_tx_en_sel_START   (2)
#define ABB_CH1_LINE_SEL_ch1_tx_en_sel_END     (2)
#define ABB_CH1_LINE_SEL_ch1_rxa_en_cfg_START  (4)
#define ABB_CH1_LINE_SEL_ch1_rxa_en_cfg_END    (4)
#define ABB_CH1_LINE_SEL_ch1_rxb_en_cfg_START  (5)
#define ABB_CH1_LINE_SEL_ch1_rxb_en_cfg_END    (5)
#define ABB_CH1_LINE_SEL_ch1_tx_en_cfg_START   (6)
#define ABB_CH1_LINE_SEL_ch1_tx_en_cfg_END     (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_LINE_CFG_UNION
 �ṹ˵��  : ch1_line_cfg �Ĵ����ṹ���塣��ַƫ����:0x1C1����ֵ:0x00�����:8
 �Ĵ���˵��: ģʽ�߿�ǿ�����á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_line_ctrl_mode_cfg : 3;  /* bit[0-2]: �߿��ź�CH1_TX_LINE_CTRL_MODEǿ������ֵ
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��ETģʽ
                                                                    6��APTģʽ
                                                                    7��CAģʽ */
        unsigned long  ch1_rx_line_ctrl_mode_cfg : 3;  /* bit[3-5]: �߿��ź�CH1_RX_LINE_CTRL_MODEǿ������ֵ
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��ETģʽ
                                                                    6��APTģʽ
                                                                    7��CAģʽ */
        unsigned long  ch1_line_ctrl_mode_sel    : 1;  /* bit[6]  : �߿��ź�CH1_LINE_CTRL_MODEǿ������ʹ�� */
        unsigned long  reserved                  : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_CFG_UNION;
#define ABB_CH1_LINE_CFG_ch1_tx_line_ctrl_mode_cfg_START  (0)
#define ABB_CH1_LINE_CFG_ch1_tx_line_ctrl_mode_cfg_END    (2)
#define ABB_CH1_LINE_CFG_ch1_rx_line_ctrl_mode_cfg_START  (3)
#define ABB_CH1_LINE_CFG_ch1_rx_line_ctrl_mode_cfg_END    (5)
#define ABB_CH1_LINE_CFG_ch1_line_ctrl_mode_sel_START     (6)
#define ABB_CH1_LINE_CFG_ch1_line_ctrl_mode_sel_END       (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_CLK_SEL_UNION
 �ṹ˵��  : ch1_clk_sel �Ĵ����ṹ���塣��ַƫ����:0x1C2����ֵ:0x00�����:8
 �Ĵ���˵��: ʱ���ſؼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_blk_clk_sel : 1;  /* bit[0]  : BLOCKING�Զ��ſ�ʹ�ܣ�
                                                          0��ʹ��
                                                          1����ʹ�� */
        unsigned long  ch1_blk_en_cfg  : 1;  /* bit[1]  : �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ */
        unsigned long  ch1_blk_en_sel  : 1;  /* bit[2]  : �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ�� */
        unsigned long  reserved        : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_CLK_SEL_UNION;
#define ABB_CH1_CLK_SEL_ch1_blk_clk_sel_START  (0)
#define ABB_CH1_CLK_SEL_ch1_blk_clk_sel_END    (0)
#define ABB_CH1_CLK_SEL_ch1_blk_en_cfg_START   (1)
#define ABB_CH1_CLK_SEL_ch1_blk_en_cfg_END     (1)
#define ABB_CH1_CLK_SEL_ch1_blk_en_sel_START   (2)
#define ABB_CH1_CLK_SEL_ch1_blk_en_sel_END     (2)


/*****************************************************************************
 �ṹ��    : ABB_CH0_LINE_SEL_UNION
 �ṹ˵��  : ch0_line_sel �Ĵ����ṹ���塣��ַƫ����:0x1D0����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�ǿ������ʹ�ܡ�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_en_sel : 1;  /* bit[0]: RXAͨ���߿�ѡ��ǿ��ʹ��
                                                       0��ѡ���߿�ʹ��
                                                       1��ѡ��ǿ��ʹ�� */
        unsigned long  ch0_rxb_en_sel : 1;  /* bit[1]: RXBͨ���߿�ѡ��ǿ��ʹ��
                                                       0��ѡ���߿�ʹ��
                                                       1��ѡ��ǿ��ʹ�� */
        unsigned long  ch0_tx_en_sel  : 1;  /* bit[2]: TXͨ���߿�ѡ��ǿ��ʹ��
                                                       0��ѡ���߿�ʹ��
                                                       1��ѡ��ǿ��ʹ�� */
        unsigned long  reserved_0     : 1;  /* bit[3]: ���� */
        unsigned long  ch0_rxa_en_cfg : 1;  /* bit[4]: RXAͨ��ǿ���߿� */
        unsigned long  ch0_rxb_en_cfg : 1;  /* bit[5]: RXBͨ��ǿ���߿� */
        unsigned long  ch0_tx_en_cfg  : 1;  /* bit[6]: TXͨ��ǿ���߿� */
        unsigned long  reserved_1     : 1;  /* bit[7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_SEL_UNION;
#define ABB_CH0_LINE_SEL_ch0_rxa_en_sel_START  (0)
#define ABB_CH0_LINE_SEL_ch0_rxa_en_sel_END    (0)
#define ABB_CH0_LINE_SEL_ch0_rxb_en_sel_START  (1)
#define ABB_CH0_LINE_SEL_ch0_rxb_en_sel_END    (1)
#define ABB_CH0_LINE_SEL_ch0_tx_en_sel_START   (2)
#define ABB_CH0_LINE_SEL_ch0_tx_en_sel_END     (2)
#define ABB_CH0_LINE_SEL_ch0_rxa_en_cfg_START  (4)
#define ABB_CH0_LINE_SEL_ch0_rxa_en_cfg_END    (4)
#define ABB_CH0_LINE_SEL_ch0_rxb_en_cfg_START  (5)
#define ABB_CH0_LINE_SEL_ch0_rxb_en_cfg_END    (5)
#define ABB_CH0_LINE_SEL_ch0_tx_en_cfg_START   (6)
#define ABB_CH0_LINE_SEL_ch0_tx_en_cfg_END     (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_LINE_CFG_UNION
 �ṹ˵��  : ch0_line_cfg �Ĵ����ṹ���塣��ַƫ����:0x1D1����ֵ:0x00�����:8
 �Ĵ���˵��: ģʽ�߿�ǿ�����á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_line_ctrl_mode_cfg : 3;  /* bit[0-2]: �߿��ź�CH0_TX_LINE_CTRL_MODEǿ������ֵ
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��ETģʽ
                                                                    6��APTģʽ
                                                                    7��CAģʽ */
        unsigned long  ch0_rx_line_ctrl_mode_cfg : 3;  /* bit[3-5]: �߿��ź�CH0_RX_LINE_CTRL_MODEǿ������ֵ
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��ETģʽ
                                                                    6��APTģʽ
                                                                    7��CAģʽ */
        unsigned long  ch0_line_ctrl_mode_sel    : 1;  /* bit[6]  : �߿��ź�CH0_LINE_CTRL_MODEǿ������ʹ�� */
        unsigned long  reserved                  : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_CFG_UNION;
#define ABB_CH0_LINE_CFG_ch0_tx_line_ctrl_mode_cfg_START  (0)
#define ABB_CH0_LINE_CFG_ch0_tx_line_ctrl_mode_cfg_END    (2)
#define ABB_CH0_LINE_CFG_ch0_rx_line_ctrl_mode_cfg_START  (3)
#define ABB_CH0_LINE_CFG_ch0_rx_line_ctrl_mode_cfg_END    (5)
#define ABB_CH0_LINE_CFG_ch0_line_ctrl_mode_sel_START     (6)
#define ABB_CH0_LINE_CFG_ch0_line_ctrl_mode_sel_END       (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_CLK_SEL_UNION
 �ṹ˵��  : ch0_clk_sel �Ĵ����ṹ���塣��ַƫ����:0x1D2����ֵ:0x00�����:8
 �Ĵ���˵��: ʱ���ſؼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_blk_clk_sel : 1;  /* bit[0]  : BLOCKING�Զ��ſ�ʹ�ܣ�
                                                          0��ʹ��
                                                          1����ʹ�� */
        unsigned long  ch0_blk_en_cfg  : 1;  /* bit[1]  : �߿��ź�CH0_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ */
        unsigned long  ch0_blk_en_sel  : 1;  /* bit[2]  : �߿��ź�CH0_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ�� */
        unsigned long  reserved        : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CLK_SEL_UNION;
#define ABB_CH0_CLK_SEL_ch0_blk_clk_sel_START  (0)
#define ABB_CH0_CLK_SEL_ch0_blk_clk_sel_END    (0)
#define ABB_CH0_CLK_SEL_ch0_blk_en_cfg_START   (1)
#define ABB_CH0_CLK_SEL_ch0_blk_en_cfg_END     (1)
#define ABB_CH0_CLK_SEL_ch0_blk_en_sel_START   (2)
#define ABB_CH0_CLK_SEL_ch0_blk_en_sel_END     (2)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TDS_RX_DLY_UNION
 �ṹ˵��  : CH0_TDS_RX_DLY �Ĵ����ṹ���塣��ַƫ����:0x200����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0 TDS���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tds_rx_dly : 3;  /* bit[0-2]: ͨ��0 TDSģʽ��ʱ�������üĴ���������ֵ��ʱ�ӹ�ϵΪ
                                                         0: delay 0 chip
                                                         1: delay 4/120 chips
                                                         2: delay 8/120 chips
                                                         3: delay 11/120 chips
                                                         4: delay 15/120 chips
                                                         5: delay 19/120 chips
                                                         6: delay 23/120 chips
                                                         7: delay 26/120 chips */
        unsigned long  reserved       : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TDS_RX_DLY_UNION;
#define ABB_CH0_TDS_RX_DLY_ch0_tds_rx_dly_START  (0)
#define ABB_CH0_TDS_RX_DLY_ch0_tds_rx_dly_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_CH0_FLUSH_CFG1_UNION
 �ṹ˵��  : CH0_FLUSH_CFG1 �Ĵ����ṹ���塣��ַƫ����:0x233����ֵ:0x40�����:8
 �Ĵ���˵��: ͨ��0���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_flush_width_msb : 3;  /* bit[0-2]: ͨ��0 flush���[10:8]����λΪ19.2Mʱ�����ڡ� */
        unsigned long  ch0_flush_value     : 5;  /* bit[3-7]: ͨ��0 FLUSHֵ��Ĭ��Ϊ8�� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_FLUSH_CFG1_UNION;
#define ABB_CH0_FLUSH_CFG1_ch0_flush_width_msb_START  (0)
#define ABB_CH0_FLUSH_CFG1_ch0_flush_width_msb_END    (2)
#define ABB_CH0_FLUSH_CFG1_ch0_flush_value_START      (3)
#define ABB_CH0_FLUSH_CFG1_ch0_flush_value_END        (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TDS_RX_DLY_UNION
 �ṹ˵��  : CH1_TDS_RX_DLY �Ĵ����ṹ���塣��ַƫ����:0x262����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��1 TDS���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tds_rx_dly : 3;  /* bit[0-2]: ͨ��1 TDSģʽ��ʱ�������üĴ���������ֵ��ʱ�ӹ�ϵΪ
                                                         0: delay 0 chip
                                                         1: delay 4/120 chips
                                                         2: delay 8/120 chips
                                                         3: delay 11/120 chips
                                                         4: delay 15/120 chips
                                                         5: delay 19/120 chips
                                                         6: delay 23/120 chips
                                                         7: delay 26/120 chips */
        unsigned long  reserved       : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TDS_RX_DLY_UNION;
#define ABB_CH1_TDS_RX_DLY_ch1_tds_rx_dly_START  (0)
#define ABB_CH1_TDS_RX_DLY_ch1_tds_rx_dly_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_CH1_FLUSH_CFG1_UNION
 �ṹ˵��  : CH1_FLUSH_CFG1 �Ĵ����ṹ���塣��ַƫ����:0x295����ֵ:0x40�����:8
 �Ĵ���˵��: ͨ��1���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_flush_width_msb : 3;  /* bit[0-2]: ͨ��1 flush���[10:8]����λΪ19.2Mʱ�����ڡ� */
        unsigned long  ch1_flush_value     : 5;  /* bit[3-7]: ͨ��1 FLUSHֵ��Ĭ��Ϊ8�� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_FLUSH_CFG1_UNION;
#define ABB_CH1_FLUSH_CFG1_ch1_flush_width_msb_START  (0)
#define ABB_CH1_FLUSH_CFG1_ch1_flush_width_msb_END    (2)
#define ABB_CH1_FLUSH_CFG1_ch1_flush_value_START      (3)
#define ABB_CH1_FLUSH_CFG1_ch1_flush_value_END        (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_DIG_1_UNION
 �ṹ˵��  : rx_c_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x400����ֵ:0xA6�����:8
 �Ĵ���˵��: RX Cģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_c : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                           00���̶�ϵ��1��
                                                           01���̶�ϵ��2��
                                                           10���̶�ϵ��3��
                                                           11��reserved�� */
        unsigned long  rx_comp_fix_c    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                           0��ϵ�����̶����ɼĴ�������
                                                           1��ϵ���̶� */
        unsigned long  rx_hb_bp_c       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                           0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                           1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_c        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                               2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                     /TDS_B/4G_C,        /4G_B,
                                                           00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
                                                           others��reserved */
        unsigned long  rx_mode_dig_c    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                           000��2G
                                                           001��3G_SC/TDS_B/4G_C
                                                           010��4G
                                                           011��3G_DC/4G_B
                                                           100��TDS
                                                           101��CDMA(Ĭ��)
                                                           Others��Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_1_UNION;
#define ABB_RX_C_DIG_1_rx_comp_sel_b0_c_START  (0)
#define ABB_RX_C_DIG_1_rx_comp_sel_b0_c_END    (0)
#define ABB_RX_C_DIG_1_rx_comp_fix_c_START     (1)
#define ABB_RX_C_DIG_1_rx_comp_fix_c_END       (1)
#define ABB_RX_C_DIG_1_rx_hb_bp_c_START        (2)
#define ABB_RX_C_DIG_1_rx_hb_bp_c_END          (2)
#define ABB_RX_C_DIG_1_rx_rate_c_START         (3)
#define ABB_RX_C_DIG_1_rx_rate_c_END           (4)
#define ABB_RX_C_DIG_1_rx_mode_dig_c_START     (5)
#define ABB_RX_C_DIG_1_rx_mode_dig_c_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_DIG_2_UNION
 �ṹ˵��  : rx_c_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x401����ֵ:0x93�����:8
 �Ĵ���˵��: RX Cģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_c         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_c         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_c       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                           00��gainΪ0.5(Ĭ��)
                                                           01��gainΪ0.75
                                                           10��gainΪ0.85
                                                           11��Reserved */
        unsigned long  rx_comp_bp_c     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                           0����bypass
                                                           1��bypass(Ĭ��) */
        unsigned long  rx_clk_inv_c     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                           0������
                                                           1������ */
        unsigned long  rx_flush_en_c    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  rx_comp_sel_b1_c : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_2_UNION;
#define ABB_RX_C_DIG_2_rxa_pd_c_START          (0)
#define ABB_RX_C_DIG_2_rxa_pd_c_END            (0)
#define ABB_RX_C_DIG_2_rxb_pd_c_START          (1)
#define ABB_RX_C_DIG_2_rxb_pd_c_END            (1)
#define ABB_RX_C_DIG_2_gain_sel_c_START        (2)
#define ABB_RX_C_DIG_2_gain_sel_c_END          (3)
#define ABB_RX_C_DIG_2_rx_comp_bp_c_START      (4)
#define ABB_RX_C_DIG_2_rx_comp_bp_c_END        (4)
#define ABB_RX_C_DIG_2_rx_clk_inv_c_START      (5)
#define ABB_RX_C_DIG_2_rx_clk_inv_c_END        (5)
#define ABB_RX_C_DIG_2_rx_flush_en_c_START     (6)
#define ABB_RX_C_DIG_2_rx_flush_en_c_END       (6)
#define ABB_RX_C_DIG_2_rx_comp_sel_b1_c_START  (7)
#define ABB_RX_C_DIG_2_rx_comp_sel_b1_c_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_C_DIG_1_UNION
 �ṹ˵��  : tx_c_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x402����ֵ:0x82�����:8
 �Ĵ���˵��: TX Cģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_c  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                        0����bypass(Ĭ��)
                                                        1��bypass */
        unsigned long  tx_hb_bp_c    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                        0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
                                                        1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��) */
        unsigned long  tx_rate_c     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                             2G,     3G,     4G,      TDS,      CDMA
                                                            (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                        0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
                                                        1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                        2��-------,--------,15.36MHz,--------,--------
                                                        Others��Reserved */
        unsigned long  tx_mode_dig_c : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                        000��2G(Ĭ��)
                                                        001��3G
                                                        010��4G
                                                        011��TDS
                                                        100��CDMA
                                                        Others��Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_DIG_1_UNION;
#define ABB_TX_C_DIG_1_tx_comp_bp_c_START   (0)
#define ABB_TX_C_DIG_1_tx_comp_bp_c_END     (0)
#define ABB_TX_C_DIG_1_tx_hb_bp_c_START     (1)
#define ABB_TX_C_DIG_1_tx_hb_bp_c_END       (1)
#define ABB_TX_C_DIG_1_tx_rate_c_START      (2)
#define ABB_TX_C_DIG_1_tx_rate_c_END        (4)
#define ABB_TX_C_DIG_1_tx_mode_dig_c_START  (5)
#define ABB_TX_C_DIG_1_tx_mode_dig_c_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_C_DIG_2_UNION
 �ṹ˵��  : tx_c_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x403����ֵ:0x23�����:8
 �Ĵ���˵��: TX Cģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_q_pd_c       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                          0����CLOCK GATING
                                                          1��CLOCK GATING(Ĭ��)
                                                          (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_c       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                          0����CLOCK GATING
                                                          1��CLOCK GATING(Ĭ��)
                                                          (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_c     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                          0��0(Ĭ��)
                                                          1��2
                                                          2��4
                                                          3��6 */
        unsigned long  uddwa_dith_en_c : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                          0����ʹ��
                                                          1��ʹ�� */
        unsigned long  dem_dwa_en_c    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                          0��ʹ��CLAģʽ
                                                          1��ʹ��DWAģʽ (Ĭ��) */
        unsigned long  dem_lsb_bp_c    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                          0��DEM LSB ��(Ĭ��)
                                                          1��DEM LSB bypass */
        unsigned long  dem_msb_bp_c    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                          0��DEM MSB��(Ĭ��)
                                                          1��DEM MSB bypass */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_DIG_2_UNION;
#define ABB_TX_C_DIG_2_tx_q_pd_c_START        (0)
#define ABB_TX_C_DIG_2_tx_q_pd_c_END          (0)
#define ABB_TX_C_DIG_2_tx_i_pd_c_START        (1)
#define ABB_TX_C_DIG_2_tx_i_pd_c_END          (1)
#define ABB_TX_C_DIG_2_dem_const_c_START      (2)
#define ABB_TX_C_DIG_2_dem_const_c_END        (3)
#define ABB_TX_C_DIG_2_uddwa_dith_en_c_START  (4)
#define ABB_TX_C_DIG_2_uddwa_dith_en_c_END    (4)
#define ABB_TX_C_DIG_2_dem_dwa_en_c_START     (5)
#define ABB_TX_C_DIG_2_dem_dwa_en_c_END       (5)
#define ABB_TX_C_DIG_2_dem_lsb_bp_c_START     (6)
#define ABB_TX_C_DIG_2_dem_lsb_bp_c_END       (6)
#define ABB_TX_C_DIG_2_dem_msb_bp_c_START     (7)
#define ABB_TX_C_DIG_2_dem_msb_bp_c_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_C_DIG_3_UNION
 �ṹ˵��  : tx_c_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x404����ֵ:0x09�����:8
 �Ĵ���˵��: TX Cģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0    : 1;  /* bit[0]  : ���� */
        unsigned long  tx_flush_en_c : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                        0����ʹ��
                                                        1��ʹ�� */
        unsigned long  tx_comp_sel_c : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                        00���̶�ϵ��1��
                                                        01���̶�ϵ��2��
                                                        10���̶�ϵ��3��
                                                        11������ϵ���� */
        unsigned long  reserved_1    : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_DIG_3_UNION;
#define ABB_TX_C_DIG_3_tx_flush_en_c_START  (1)
#define ABB_TX_C_DIG_3_tx_flush_en_c_END    (1)
#define ABB_TX_C_DIG_3_tx_comp_sel_c_START  (2)
#define ABB_TX_C_DIG_3_tx_comp_sel_c_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_TX_COEF1_UNION
 �ṹ˵��  : tx_coef1 �Ĵ����ṹ���塣��ַƫ����:0x415����ֵ:0x3B�����:8
 �Ĵ���˵��: TXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_c0 : 6;  /* bit[0-5]: TX�����˲���ϵ��C0,6bit�з����� */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_COEF1_UNION;
#define ABB_TX_COEF1_tx_comp_c0_START  (0)
#define ABB_TX_COEF1_tx_comp_c0_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_TX_COEF4_UNION
 �ṹ˵��  : tx_coef4 �Ĵ����ṹ���塣��ַƫ����:0x418����ֵ:0x03�����:8
 �Ĵ���˵��: TXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_c2_msb : 2;  /* bit[0-1]: TX�����˲���ϵ��C2��2λ,10bit�з����� */
        unsigned long  reserved       : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_COEF4_UNION;
#define ABB_TX_COEF4_tx_comp_c2_msb_START  (0)
#define ABB_TX_COEF4_tx_comp_c2_msb_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_TX_COEF6_UNION
 �ṹ˵��  : tx_coef6 �Ĵ����ṹ���塣��ַƫ����:0x41A����ֵ:0x02�����:8
 �Ĵ���˵��: TXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_c3_msb : 2;  /* bit[0-1]: TX�����˲���ϵ��C3��2λ,10bit�޷����� */
        unsigned long  reserved       : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_COEF6_UNION;
#define ABB_TX_COEF6_tx_comp_c3_msb_START  (0)
#define ABB_TX_COEF6_tx_comp_c3_msb_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_BIST_DELAY_SEL_UNION
 �ṹ˵��  : bist_delay_sel �Ĵ����ṹ���塣��ַƫ����:0x500����ֵ:0x00�����:8
 �Ĵ���˵��: delay����ѡ���ź�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_delay1_sel : 2;  /* bit[0-1]: Delay1��ѡ���źţ�
                                                          00��50us��
                                                          01��100us��
                                                          10��200us��
                                                          11��500us�� */
        unsigned long  reserved_0      : 2;  /* bit[2-3]: ���� */
        unsigned long  bist_delay2_sel : 2;  /* bit[4-5]: Delay2��ѡ���źţ�
                                                          00��20us��
                                                          01��50us��
                                                          10��200us��
                                                          11��500us�� */
        unsigned long  reserved_1      : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_DELAY_SEL_UNION;
#define ABB_BIST_DELAY_SEL_bist_delay1_sel_START  (0)
#define ABB_BIST_DELAY_SEL_bist_delay1_sel_END    (1)
#define ABB_BIST_DELAY_SEL_bist_delay2_sel_START  (4)
#define ABB_BIST_DELAY_SEL_bist_delay2_sel_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_BIST_MODE_BYPASS_UNION
 �ṹ˵��  : bist_mode_bypass �Ĵ����ṹ���塣��ַƫ����:0x501����ֵ:0x00�����:8
 �Ĵ���˵��: ģʽbypass�ź�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_mode_bypass : 7;  /* bit[0-6]: ģʽbypass�źţ�ÿ��ģʽռһ��bit
                                                           [0]��1��ʾGģ��BIST��bypass��0��ʾGģ��BIST����������
                                                           [1]��1��ʾWCDMAģSC��BIST��bypass��0��ʾWCDMAģSC��BIST����������
                                                           [2]��1��ʾWCDMAģDC��BIST��bypass��0��ʾWCDMAģDC��BIST����������
                                                           [3]��1��ʾLTEģ��BIST��bypass��0��ʾLTEģ��BIST����������
                                                           [4]��1��ʾETģ��BIST��bypass��0��ʾETģ��BIST����������
                                                           [5]��1��ʾCAģ��BIST��bypass��0��ʾCAģ��BIST����������
                                                           [6]��1��ʾCDMAģ��BIST��bypass��0��ʾCDMAģ��BIST���������� */
        unsigned long  reserved         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_MODE_BYPASS_UNION;
#define ABB_BIST_MODE_BYPASS_bist_mode_bypass_START  (0)
#define ABB_BIST_MODE_BYPASS_bist_mode_bypass_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_BIST_RX_BYPASS_UNION
 �ṹ˵��  : bist_rx_bypass �Ĵ����ṹ���塣��ַƫ����:0x502����ֵ:0x00�����:8
 �Ĵ���˵��: Rx��bypass�ź�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_rx_bypass : 4;  /* bit[0-3]: Rx��bypass�źţ�
                                                         [0]��Rx_1��bypass�źţ�0��ʾ��Ҫ��Rx_1��BIST��1��ʾ������
                                                         [1]��Rx_2��bypass�źţ�0��ʾ��Ҫ��Rx_2��BIST��1��ʾ������
                                                         [2]��Rx_3��bypass�źţ�0��ʾ��Ҫ��Rx_3��BIST��1��ʾ������
                                                         [3]��Rx_4��bypass�źţ�0��ʾ��Ҫ��Rx_4��BIST��1��ʾ������ */
        unsigned long  reserved       : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_RX_BYPASS_UNION;
#define ABB_BIST_RX_BYPASS_bist_rx_bypass_START  (0)
#define ABB_BIST_RX_BYPASS_bist_rx_bypass_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_ABB_BIST_EN_UNION
 �ṹ˵��  : abb_bist_en �Ĵ����ṹ���塣��ַƫ����:0x503����ֵ:0x00�����:8
 �Ĵ���˵��: BIST����ʹ���ź�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_en      : 1;  /* bit[0]  : BIST����ʹ���źţ����ź�Ϊ��ƽ�źš� */
        unsigned long  bist_gate_bp : 1;  /* bit[1]  : BISTʱ���ſ�ʹ���źţ�0��ʾʱ���ſ���Ч��1��ʾʱ���ſ���·�� */
        unsigned long  reserved     : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_ABB_BIST_EN_UNION;
#define ABB_ABB_BIST_EN_bist_en_START       (0)
#define ABB_ABB_BIST_EN_bist_en_END         (0)
#define ABB_ABB_BIST_EN_bist_gate_bp_START  (1)
#define ABB_ABB_BIST_EN_bist_gate_bp_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_BIST_SNDR_CAL_DONE_UNION
 �ṹ˵��  : bist_sndr_cal_done �Ĵ����ṹ���塣��ַƫ����:0x504����ֵ:0x00�����:8
 �Ĵ���˵��: ����״̬
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sndr_cal_done : 1;  /* bit[0]  : 1�����Խ��� 0�����ڲ��ԣ�en��������0�� */
        unsigned long  reserved      : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_SNDR_CAL_DONE_UNION;
#define ABB_BIST_SNDR_CAL_DONE_sndr_cal_done_START  (0)
#define ABB_BIST_SNDR_CAL_DONE_sndr_cal_done_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_BIST_PARA_PASS_FLAG_UNION
 �ṹ˵��  : bist_para_pass_flag �Ĵ����ṹ���塣��ַƫ����:0x505����ֵ:0x00�����:8
 �Ĵ���˵��: �������6�������Ƿ�pass
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  para_pass_flag : 6;  /* bit[0-5]: ÿһ�μ������6�������Ƿ�pass��
                                                         [0]:1��ʾDC_Iָ��pass��0��ʾ��pass��
                                                         [1]:1��ʾDC_Qָ��pass��0��ʾ��pass��
                                                         [2]:1��ʾSNDR_Iָ��pass��0��ʾ��pass��
                                                         [3]:1��ʾSNDR_Qָ��pass��0��ʾ��pass��
                                                         [4]:1��ʾGAIN_MISMATCHָ��pass��0��ʾ��pass��
                                                         [5]:1��ʾGAIN_ERRORָ��pass��0��ʾ��pass�� */
        unsigned long  reserved       : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_PARA_PASS_FLAG_UNION;
#define ABB_BIST_PARA_PASS_FLAG_para_pass_flag_START  (0)
#define ABB_BIST_PARA_PASS_FLAG_para_pass_flag_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_ABB_BIST_PASS_FLAG_1_UNION
 �ṹ˵��  : abb_bist_pass_flag_1 �Ĵ����ṹ���塣��ַƫ����:0x506����ֵ:0x00�����:8
 �Ĵ���˵��: Rx_1��Bist������
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_pass_flag_1 : 7;  /* bit[0-6]: Rx_1��Bist��������ÿ��ģʽ1bit��
                                                           [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
                                                           [1]��1��ʾWCDMAģSC��BIST pass��0��ʾWCDMAģSC��BIST fail��
                                                           [2]��1��ʾWCDMAģDC��BIST pass��0��ʾWCDMAģDC��BIST fail��
                                                           [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
                                                           [4]��1��ʾETģ��BIST pass��0��ʾETģ��BIST fail��
                                                           [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
                                                           [6]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail�� */
        unsigned long  reserved         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ABB_BIST_PASS_FLAG_1_UNION;
#define ABB_ABB_BIST_PASS_FLAG_1_bist_pass_flag_1_START  (0)
#define ABB_ABB_BIST_PASS_FLAG_1_bist_pass_flag_1_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_ABB_BIST_PASS_FLAG_2_UNION
 �ṹ˵��  : abb_bist_pass_flag_2 �Ĵ����ṹ���塣��ַƫ����:0x507����ֵ:0x00�����:8
 �Ĵ���˵��: Rx_2��Bist������
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_pass_flag_2 : 7;  /* bit[0-6]: Rx_2��Bist��������ÿ��ģʽ1bit��
                                                           [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
                                                           [1]��1��ʾWCDMAģSC��BIST pass��0��ʾWCDMAģSC��BIST fail��
                                                           [2]��1��ʾWCDMAģDC��BIST pass��0��ʾWCDMAģDC��BIST fail��
                                                           [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
                                                           [4]��1��ʾETģ��BIST pass��0��ʾETģ��BIST fail��
                                                           [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
                                                           [6]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail�� */
        unsigned long  reserved         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ABB_BIST_PASS_FLAG_2_UNION;
#define ABB_ABB_BIST_PASS_FLAG_2_bist_pass_flag_2_START  (0)
#define ABB_ABB_BIST_PASS_FLAG_2_bist_pass_flag_2_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_ABB_BIST_PASS_FLAG_3_UNION
 �ṹ˵��  : abb_bist_pass_flag_3 �Ĵ����ṹ���塣��ַƫ����:0x508����ֵ:0x00�����:8
 �Ĵ���˵��: Rx_3��Bist������
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_pass_flag_3 : 7;  /* bit[0-6]: Rx_3��Bist��������ÿ��ģʽ1bit��
                                                           [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
                                                           [1]��1��ʾWCDMAģSC��BIST pass��0��ʾWCDMAģSC��BIST fail��
                                                           [2]��1��ʾWCDMAģDC��BIST pass��0��ʾWCDMAģDC��BIST fail��
                                                           [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
                                                           [4]��1��ʾETģ��BIST pass��0��ʾETģ��BIST fail��
                                                           [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
                                                           [6]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail�� */
        unsigned long  reserved         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ABB_BIST_PASS_FLAG_3_UNION;
#define ABB_ABB_BIST_PASS_FLAG_3_bist_pass_flag_3_START  (0)
#define ABB_ABB_BIST_PASS_FLAG_3_bist_pass_flag_3_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_ABB_BIST_PASS_FLAG_4_UNION
 �ṹ˵��  : abb_bist_pass_flag_4 �Ĵ����ṹ���塣��ַƫ����:0x509����ֵ:0x00�����:8
 �Ĵ���˵��: Rx_4��Bist������
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_pass_flag_4 : 7;  /* bit[0-6]: Rx_4��Bist��������ÿ��ģʽ1bit��
                                                           [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
                                                           [1]��1��ʾWCDMAģSC��BIST pass��0��ʾWCDMAģSC��BIST fail��
                                                           [2]��1��ʾWCDMAģDC��BIST pass��0��ʾWCDMAģDC��BIST fail��
                                                           [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
                                                           [4]��1��ʾETģ��BIST pass��0��ʾETģ��BIST fail��
                                                           [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
                                                           [6]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail�� */
        unsigned long  reserved         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ABB_BIST_PASS_FLAG_4_UNION;
#define ABB_ABB_BIST_PASS_FLAG_4_bist_pass_flag_4_START  (0)
#define ABB_ABB_BIST_PASS_FLAG_4_bist_pass_flag_4_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_BIST_DC_I_2_UNION
 �ṹ˵��  : BIST_DC_I_2 �Ĵ����ṹ���塣��ַƫ����:0x50B����ֵ:0x00�����:8
 �Ĵ���˵��: I·DC�ϱ���3λ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  dc_i_high : 3;  /* bit[0-2]: I·DC�ϱ���3λ��I·DC�ϱ�Ϊ11bit�з������� */
        unsigned long  reserved  : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_BIST_DC_I_2_UNION;
#define ABB_BIST_DC_I_2_dc_i_high_START  (0)
#define ABB_BIST_DC_I_2_dc_i_high_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_BIST_DC_Q_2_UNION
 �ṹ˵��  : BIST_DC_Q_2 �Ĵ����ṹ���塣��ַƫ����:0x50D����ֵ:0x00�����:8
 �Ĵ���˵��: Q·DC�ϱ���3λ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  dc_q_high : 3;  /* bit[0-2]: I·DC�ϱ���3λ��I·DC�ϱ�Ϊ11bit�з������� */
        unsigned long  reserved  : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_BIST_DC_Q_2_UNION;
#define ABB_BIST_DC_Q_2_dc_q_high_START  (0)
#define ABB_BIST_DC_Q_2_dc_q_high_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_GPLL_GATE_EN_UNION
 �ṹ˵��  : GPLL_GATE_EN �Ĵ����ṹ���塣��ַƫ����:0x602����ֵ:0x01�����:8
 �Ĵ���˵��: GPLL���ʱ���ſع���ʹ��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  gpll_gate_en : 1;  /* bit[0]  : GPLLʱ���ſع���ʹ�ܣ�
                                                       0��gpllʱ���ſع��ܹرգ�
                                                       1��gpllʱ���ſع��ܴ򿪡� */
        unsigned long  gpll_timeout : 1;  /* bit[1]  : GPLL�ȶ�ָʾ��0��ʾGPLLδ�ȶ���1��ʾGPLL�ȶ���GPLL�ȶ�����ʱ������� */
        unsigned long  ch1_gpll_sel : 1;  /* bit[2]  : Gģ����PLLѡ��
                                                       0��ѡ��GPLL������/˫ʱ�ӷ���Ĭ��ѡ��GPLL��
                                                       1��ѡ��SCPLL�� */
        unsigned long  ch0_gpll_sel : 1;  /* bit[3]  : Gģ����PLLѡ��
                                                       0��ѡ��GPLL������ʱ�ӷ���Ĭ��ѡ��GPLL��˫ʱ�ӷ���Ĭ��ѡ��SCPLL��
                                                       1��ѡ��SCPLL�� */
        unsigned long  reserved     : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_GPLL_GATE_EN_UNION;
#define ABB_GPLL_GATE_EN_gpll_gate_en_START  (0)
#define ABB_GPLL_GATE_EN_gpll_gate_en_END    (0)
#define ABB_GPLL_GATE_EN_gpll_timeout_START  (1)
#define ABB_GPLL_GATE_EN_gpll_timeout_END    (1)
#define ABB_GPLL_GATE_EN_ch1_gpll_sel_START  (2)
#define ABB_GPLL_GATE_EN_ch1_gpll_sel_END    (2)
#define ABB_GPLL_GATE_EN_ch0_gpll_sel_START  (3)
#define ABB_GPLL_GATE_EN_ch0_gpll_sel_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_GPLL_GATE_TIME_UNION
 �ṹ˵��  : GPLL_GATE_TIME �Ĵ����ṹ���塣��ַƫ����:0x603����ֵ:0x03�����:8
 �Ĵ���˵��: GPLL���ʱ���ſ�ʱ������
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  gpll_gate_time_sel : 2;  /* bit[0-1]: GPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
                                                             00��gpll����5us���ȶ���
                                                             01��gpll����10us���ȶ���
                                                             10��gpll����15us���ȶ���
                                                             11��gpll����20us���ȶ��� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_GPLL_GATE_TIME_UNION;
#define ABB_GPLL_GATE_TIME_gpll_gate_time_sel_START  (0)
#define ABB_GPLL_GATE_TIME_gpll_gate_time_sel_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_SCPLL_LOCK_CTRL_UNION
 �ṹ˵��  : SCPLL_LOCK_CTRL �Ĵ����ṹ���塣��ַƫ����:0x604����ֵ:0x0A�����:8
 �Ĵ���˵��: SC_PLL�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll_en      : 1;  /* bit[0]  : SCPLLʹ���źš�����ͨ��CFG�ӿ����ô�scpll�� */
        unsigned long  scpll_time    : 2;  /* bit[1-2]: SCPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
                                                        00��SCPLL����75us��ʱ���ȶ���
                                                        01��SCPLL����100us��ʱ���ȶ���
                                                        10��SCPLL����115us��ʱ���ȶ���
                                                        11��SCPLL����125us��ʱ���ȶ��� */
        unsigned long  scpll_gate_en : 1;  /* bit[3]  : SCPLL�ſ�ʹ���źš� */
        unsigned long  scpll_timeout : 1;  /* bit[4]  : SCPLL�ȶ�ָʾ��0��ʾSCPLLδ�ȶ���1��ʾSCPLL�ȶ���SCPLL�ȶ�����ʱ������� */
        unsigned long  scpll_lock    : 1;  /* bit[5]  : SCPLL����ָʾ�� */
        unsigned long  reserved      : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL_LOCK_CTRL_UNION;
#define ABB_SCPLL_LOCK_CTRL_scpll_en_START       (0)
#define ABB_SCPLL_LOCK_CTRL_scpll_en_END         (0)
#define ABB_SCPLL_LOCK_CTRL_scpll_time_START     (1)
#define ABB_SCPLL_LOCK_CTRL_scpll_time_END       (2)
#define ABB_SCPLL_LOCK_CTRL_scpll_gate_en_START  (3)
#define ABB_SCPLL_LOCK_CTRL_scpll_gate_en_END    (3)
#define ABB_SCPLL_LOCK_CTRL_scpll_timeout_START  (4)
#define ABB_SCPLL_LOCK_CTRL_scpll_timeout_END    (4)
#define ABB_SCPLL_LOCK_CTRL_scpll_lock_START     (5)
#define ABB_SCPLL_LOCK_CTRL_scpll_lock_END       (5)


/*****************************************************************************
 �ṹ��    : ABB_SCPLL_FBDIV_H_UNION
 �ṹ˵��  : SCPLL_FBDIV_H �Ĵ����ṹ���塣��ַƫ����:0x607����ֵ:0x00�����:8
 �Ĵ���˵��: SC_PLL��Ƶ���������üĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll_fbdiv_h : 4;  /* bit[0-3]: PLL������Ƶ����fbdiv[11:0]�ĸ�4bit�� */
        unsigned long  reserved      : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL_FBDIV_H_UNION;
#define ABB_SCPLL_FBDIV_H_scpll_fbdiv_h_START  (0)
#define ABB_SCPLL_FBDIV_H_scpll_fbdiv_h_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_SCPLL_REFDIV_UNION
 �ṹ˵��  : SCPLL_REFDIV �Ĵ����ṹ���塣��ַƫ����:0x608����ֵ:0x01�����:8
 �Ĵ���˵��: SC_PLL��Ƶ���������üĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll_refdiv : 6;  /* bit[0-5]: PLL�ο���Ƶ����refdiv[5:0]��Ĭ��ֵΪ1�� */
        unsigned long  reserved     : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL_REFDIV_UNION;
#define ABB_SCPLL_REFDIV_scpll_refdiv_START  (0)
#define ABB_SCPLL_REFDIV_scpll_refdiv_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_SCPLL_CFG_UPDATE_UNION
 �ṹ˵��  : SCPLL_CFG_UPDATE �Ĵ����ṹ���塣��ַƫ����:0x60D����ֵ:0x00�����:8
 �Ĵ���˵��: SC_PLL�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll_cfg_update : 1;  /* bit[0]  : SCPLL�������ø���ָʾ��
                                                           scpll_en�򿪺����������scpll_postdiv��scpll_fbdiv��scpll_frac������������scpll_sfg_update������ͬʱ���£�scpll_en����ʱ�����ò����������£�����Ҫ����scpll_sfg_update�� */
        unsigned long  reserved         : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL_CFG_UPDATE_UNION;
#define ABB_SCPLL_CFG_UPDATE_scpll_cfg_update_START  (0)
#define ABB_SCPLL_CFG_UPDATE_scpll_cfg_update_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_BBP_SLEEP_EN_UNION
 �ṹ˵��  : BBP_SLEEP_EN �Ĵ����ṹ���塣��ַƫ����:0x60E����ֵ:0x00�����:8
 �Ĵ���˵��: BBP��245D76Mʱ���ſؼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wbbp_sleep_en       : 1;  /* bit[0]  : ��BBP��WPLL 245D76Mʱ���ſ��źš�0�������ʱ�ӣ�ʱ������͵�ƽ��1�����ʱ�ӡ�Ĭ��ֵ0�������ʱ�ӣ��� */
        unsigned long  scbbp_245m_sleep_en : 1;  /* bit[1]  : ��BBP��SCPLL 245D76Mʱ���ſ��źš�0�������ʱ�ӣ�ʱ������͵�ƽ��1�����ʱ�ӡ�Ĭ��ֵ0�������ʱ�ӣ��� */
        unsigned long  scbbp_104m_sleep_en : 1;  /* bit[2]  : ��BBP��SCPLL 104Mʱ���ſ��źš�0�������ʱ�ӣ�ʱ������͵�ƽ��1�����ʱ�ӡ�Ĭ��ֵ0�������ʱ�ӣ��� */
        unsigned long  reserved            : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_BBP_SLEEP_EN_UNION;
#define ABB_BBP_SLEEP_EN_wbbp_sleep_en_START        (0)
#define ABB_BBP_SLEEP_EN_wbbp_sleep_en_END          (0)
#define ABB_BBP_SLEEP_EN_scbbp_245m_sleep_en_START  (1)
#define ABB_BBP_SLEEP_EN_scbbp_245m_sleep_en_END    (1)
#define ABB_BBP_SLEEP_EN_scbbp_104m_sleep_en_START  (2)
#define ABB_BBP_SLEEP_EN_scbbp_104m_sleep_en_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_WPLL_GATE_EN_UNION
 �ṹ˵��  : WPLL_GATE_EN �Ĵ����ṹ���塣��ַƫ����:0x60F����ֵ:0x01�����:8
 �Ĵ���˵��: WPLL���ʱ���ſع���ʹ��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_gate_en : 1;  /* bit[0]  : WPLLʱ���ſع���ʹ�ܣ�
                                                       0��wpllʱ���ſع��ܹرգ�
                                                       1��wpllʱ���ſع��ܴ򿪡� */
        unsigned long  wpll_timeout : 1;  /* bit[1]  : WPLL�ȶ�ָʾ��0��ʾWPLLδ�ȶ���1��ʾWPLL�ȶ���WPLL�ȶ�����ʱ������� */
        unsigned long  reserved     : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_WPLL_GATE_EN_UNION;
#define ABB_WPLL_GATE_EN_wpll_gate_en_START  (0)
#define ABB_WPLL_GATE_EN_wpll_gate_en_END    (0)
#define ABB_WPLL_GATE_EN_wpll_timeout_START  (1)
#define ABB_WPLL_GATE_EN_wpll_timeout_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_WPLL_GATE_TIME_UNION
 �ṹ˵��  : WPLL_GATE_TIME �Ĵ����ṹ���塣��ַƫ����:0x610����ֵ:0x03�����:8
 �Ĵ���˵��: WPLL���ʱ���ſ�ʱ������
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_gate_time_sel : 2;  /* bit[0-1]: WPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
                                                             00��wpll����5us���ȶ���
                                                             01��wpll����10us���ȶ���
                                                             10��wpll����15us���ȶ���
                                                             11��wpll����20us���ȶ��� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_WPLL_GATE_TIME_UNION;
#define ABB_WPLL_GATE_TIME_wpll_gate_time_sel_START  (0)
#define ABB_WPLL_GATE_TIME_wpll_gate_time_sel_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_PLL_FREF_SEL_UNION
 �ṹ˵��  : PLL_FREF_SEL �Ĵ����ṹ���塣��ַƫ����:0x611����ֵ:0x00�����:8
 �Ĵ���˵��: WPLL���ʱ���ſ�ʱ������
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll_fref_sel : 1;  /* bit[0]  : SC PLL FREFѡ��
                                                         0��ѡch0 TCXO������/˫ʱ�ӷ���Ĭ��ѡ0��
                                                         1��ѡch1 TCXO�� */
        unsigned long  wpll_fref_sel  : 1;  /* bit[1]  : W PLL FREFѡ��
                                                         0��ѡch0 TCXO������/˫ʱ�ӷ���Ĭ��ѡ0��
                                                         1��ѡch1 TCXO�� */
        unsigned long  gpll_fref_sel  : 1;  /* bit[2]  : G PLL FREFѡ��
                                                         0��ѡch0 TCXO������ʱ�ӷ���Ĭ��ѡ0��˫ʱ�ӷ���Ĭ��ѡ1��
                                                         1��ѡch1 TCXO�� */
        unsigned long  reserved       : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_PLL_FREF_SEL_UNION;
#define ABB_PLL_FREF_SEL_scpll_fref_sel_START  (0)
#define ABB_PLL_FREF_SEL_scpll_fref_sel_END    (0)
#define ABB_PLL_FREF_SEL_wpll_fref_sel_START   (1)
#define ABB_PLL_FREF_SEL_wpll_fref_sel_END     (1)
#define ABB_PLL_FREF_SEL_gpll_fref_sel_START   (2)
#define ABB_PLL_FREF_SEL_gpll_fref_sel_END     (2)


/*****************************************************************************
 �ṹ��    : ABB_SOC_PLL_SEL_UNION
 �ṹ˵��  : SOC_PLL_SEL �Ĵ����ṹ���塣��ַƫ����:0x612����ֵ:0x00�����:8
 �Ĵ���˵��: SOCʱ��ѡ���ź�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  soc_pll_sel : 1;  /* bit[0]  : SOC PLLѡ��
                                                      0��SOCʱ��ѡSCPLL����Ĭ��ѡSCPLL��
                                                      1��SOCʱ��ѡWPLL�� */
        unsigned long  reserved    : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SOC_PLL_SEL_UNION;
#define ABB_SOC_PLL_SEL_soc_pll_sel_START  (0)
#define ABB_SOC_PLL_SEL_soc_pll_sel_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXAI_HB_GAIN_2_UNION
 �ṹ˵��  : CH0_RXAI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x614����ֵ:0x02�����:8
 �Ĵ���˵��: CH0ͨ��RXA HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxai_hb_gain_h : 2;  /* bit[0-1]: CH0ͨ��RXA I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXAI_HB_GAIN_2_UNION;
#define ABB_CH0_RXAI_HB_GAIN_2_ch0_rxai_hb_gain_h_START  (0)
#define ABB_CH0_RXAI_HB_GAIN_2_ch0_rxai_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXAQ_HB_GAIN_2_UNION
 �ṹ˵��  : CH0_RXAQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x616����ֵ:0x02�����:8
 �Ĵ���˵��: CH0ͨ��RXA HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxaq_hb_gain_h : 2;  /* bit[0-1]: CH0ͨ��RXA Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXAQ_HB_GAIN_2_UNION;
#define ABB_CH0_RXAQ_HB_GAIN_2_ch0_rxaq_hb_gain_h_START  (0)
#define ABB_CH0_RXAQ_HB_GAIN_2_ch0_rxaq_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXBI_HB_GAIN_2_UNION
 �ṹ˵��  : CH0_RXBI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x618����ֵ:0x02�����:8
 �Ĵ���˵��: CH0ͨ��RXB HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxbi_hb_gain_h : 2;  /* bit[0-1]: CH0ͨ��RXB I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXBI_HB_GAIN_2_UNION;
#define ABB_CH0_RXBI_HB_GAIN_2_ch0_rxbi_hb_gain_h_START  (0)
#define ABB_CH0_RXBI_HB_GAIN_2_ch0_rxbi_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXBQ_HB_GAIN_2_UNION
 �ṹ˵��  : CH0_RXBQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x61A����ֵ:0x02�����:8
 �Ĵ���˵��: CH0ͨ��RXB HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxbq_hb_gain_h : 2;  /* bit[0-1]: CH0ͨ��RXB Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXBQ_HB_GAIN_2_UNION;
#define ABB_CH0_RXBQ_HB_GAIN_2_ch0_rxbq_hb_gain_h_START  (0)
#define ABB_CH0_RXBQ_HB_GAIN_2_ch0_rxbq_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXAI_HB_GAIN_2_UNION
 �ṹ˵��  : CH1_RXAI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x61C����ֵ:0x02�����:8
 �Ĵ���˵��: CH1ͨ��RXA HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxai_hb_gain_h : 2;  /* bit[0-1]: CH1ͨ��RXA I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXAI_HB_GAIN_2_UNION;
#define ABB_CH1_RXAI_HB_GAIN_2_ch1_rxai_hb_gain_h_START  (0)
#define ABB_CH1_RXAI_HB_GAIN_2_ch1_rxai_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXAQ_HB_GAIN_2_UNION
 �ṹ˵��  : CH1_RXAQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x61E����ֵ:0x02�����:8
 �Ĵ���˵��: CH1ͨ��RXA HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxaq_hb_gain_h : 2;  /* bit[0-1]: CH1ͨ��RXA Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXAQ_HB_GAIN_2_UNION;
#define ABB_CH1_RXAQ_HB_GAIN_2_ch1_rxaq_hb_gain_h_START  (0)
#define ABB_CH1_RXAQ_HB_GAIN_2_ch1_rxaq_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXBI_HB_GAIN_2_UNION
 �ṹ˵��  : CH1_RXBI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x620����ֵ:0x02�����:8
 �Ĵ���˵��: CH1ͨ��RXB HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxbi_hb_gain_h : 2;  /* bit[0-1]: CH1ͨ��RXB I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXBI_HB_GAIN_2_UNION;
#define ABB_CH1_RXBI_HB_GAIN_2_ch1_rxbi_hb_gain_h_START  (0)
#define ABB_CH1_RXBI_HB_GAIN_2_ch1_rxbi_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXBQ_HB_GAIN_2_UNION
 �ṹ˵��  : CH1_RXBQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x622����ֵ:0x02�����:8
 �Ĵ���˵��: CH1ͨ��RXB HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxbq_hb_gain_h : 2;  /* bit[0-1]: CH1ͨ��RXB Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXBQ_HB_GAIN_2_UNION;
#define ABB_CH1_RXBQ_HB_GAIN_2_ch1_rxbq_hb_gain_h_START  (0)
#define ABB_CH1_RXBQ_HB_GAIN_2_ch1_rxbq_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_EN_DELAY_UNION
 �ṹ˵��  : RX_EN_DELAY �Ĵ����ṹ���塣��ַƫ����:0x623����ֵ:0x01�����:8
 �Ĵ���˵��: RXʱ���ſ��ӳٹ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_en_dly_enable : 1;  /* bit[0]  : RXʱ���ſ��ӳٹ���ʹ�ܡ��ù��ܴ򿪺�RX����·�����ӱ�RX���ݺ�VLD�ź��ӳٹرա� */
        unsigned long  rx_en_dly_cycle  : 2;  /* bit[1-2]: RXʱ���ſ��ӳٵ�19.2MHzʱ�Ӹ�����
                                                               L/CA/Xģ   W/TDSģ  Gģ
                                                           00��  1          2      32��  (Ĭ��)
                                                           01��  2          4      64��
                                                           10��  4          8      128��
                                                           11��  reserved  */
        unsigned long  reserved         : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_EN_DELAY_UNION;
#define ABB_RX_EN_DELAY_rx_en_dly_enable_START  (0)
#define ABB_RX_EN_DELAY_rx_en_dly_enable_END    (0)
#define ABB_RX_EN_DELAY_rx_en_dly_cycle_START   (1)
#define ABB_RX_EN_DELAY_rx_en_dly_cycle_END     (2)


/*****************************************************************************
 �ṹ��    : ABB_TX_ET_DIG_1_UNION
 �ṹ˵��  : TX_ET_DIG_1 �Ĵ����ṹ���塣��ַƫ����:0x700����ֵ:0x00�����:8
 �Ĵ���˵��: TX ET�������üĴ���1��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_comp_bp    : 1;  /* bit[0]  : ETͨ�������˲���bypass���ƣ�
                                                        0����bypass(Ĭ��)
                                                        1��bypass */
        unsigned long  et_hb_bp      : 1;  /* bit[1]  : ETͨ������˲�����bypass�ź�
                                                        0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                        1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  et_sw_rst     : 1;  /* bit[2]  : ETͨ����λ�Ĵ�����
                                                        0������λ��
                                                        1����λ�� */
        unsigned long  et_cal_sw_rst : 1;  /* bit[3]  : ETУ׼ģ����λ�Ĵ�����
                                                        0������λ��
                                                        1����λ�� */
        unsigned long  reserved      : 2;  /* bit[4-5]: ���� */
        unsigned long  et_ds_bp      : 1;  /* bit[6]  : ETͨ��������bypass�ź�
                                                        0����bypass��2����������Ĭ�ϣ���
                                                        1��bypass�������н������� */
        unsigned long  et_ch_sel     : 1;  /* bit[7]  : ѡ��CH0����CH1֧��ET��
                                                        0��CH0��Ĭ�ϣ���
                                                        1��CH1�� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_1_UNION;
#define ABB_TX_ET_DIG_1_et_comp_bp_START     (0)
#define ABB_TX_ET_DIG_1_et_comp_bp_END       (0)
#define ABB_TX_ET_DIG_1_et_hb_bp_START       (1)
#define ABB_TX_ET_DIG_1_et_hb_bp_END         (1)
#define ABB_TX_ET_DIG_1_et_sw_rst_START      (2)
#define ABB_TX_ET_DIG_1_et_sw_rst_END        (2)
#define ABB_TX_ET_DIG_1_et_cal_sw_rst_START  (3)
#define ABB_TX_ET_DIG_1_et_cal_sw_rst_END    (3)
#define ABB_TX_ET_DIG_1_et_ds_bp_START       (6)
#define ABB_TX_ET_DIG_1_et_ds_bp_END         (6)
#define ABB_TX_ET_DIG_1_et_ch_sel_START      (7)
#define ABB_TX_ET_DIG_1_et_ch_sel_END        (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_ET_DIG_2_UNION
 �ṹ˵��  : TX_ET_DIG_2 �Ĵ����ṹ���塣��ַƫ����:0x701����ֵ:0x45�����:8
 �Ĵ���˵��: TX ET�������üĴ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_gating_en  : 1;  /* bit[0]  : ETͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!et_gating_en)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  et_con        : 2;  /* bit[1-2]: TXͨ��DEM constϵ����
                                                        0��0
                                                        1��2
                                                        2��4(Ĭ��)
                                                        3��6 */
        unsigned long  et_lsb_value  : 1;  /* bit[3]  : ET LSB���bit���ֵ���� */
        unsigned long  et_cal_dwa_en : 1;  /* bit[4]  : ET Calibrationͨ��demģʽ���ƣ�
                                                        0��ʹ��CLAģʽ(Ĭ��)
                                                        1��ʹ��DWAģʽ  */
        unsigned long  et_tx_dwa_en  : 1;  /* bit[5]  : ET TXͨ��DEMģʽ���ƣ�
                                                        0��ʹ��CLAģʽ(Ĭ��)
                                                        1��ʹ��DWAģʽ  */
        unsigned long  et_cal_dem_bp : 1;  /* bit[6]  : ET Calibrationͨ��dem bypass��
                                                        0��DEM��(Ĭ��)
                                                        1��DEM bypass */
        unsigned long  et_tx_dem_bp  : 1;  /* bit[7]  : ET TXͨ��dem bypass��
                                                        0��DEM��(Ĭ��)
                                                        1��DEM bypass */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_2_UNION;
#define ABB_TX_ET_DIG_2_et_gating_en_START   (0)
#define ABB_TX_ET_DIG_2_et_gating_en_END     (0)
#define ABB_TX_ET_DIG_2_et_con_START         (1)
#define ABB_TX_ET_DIG_2_et_con_END           (2)
#define ABB_TX_ET_DIG_2_et_lsb_value_START   (3)
#define ABB_TX_ET_DIG_2_et_lsb_value_END     (3)
#define ABB_TX_ET_DIG_2_et_cal_dwa_en_START  (4)
#define ABB_TX_ET_DIG_2_et_cal_dwa_en_END    (4)
#define ABB_TX_ET_DIG_2_et_tx_dwa_en_START   (5)
#define ABB_TX_ET_DIG_2_et_tx_dwa_en_END     (5)
#define ABB_TX_ET_DIG_2_et_cal_dem_bp_START  (6)
#define ABB_TX_ET_DIG_2_et_cal_dem_bp_END    (6)
#define ABB_TX_ET_DIG_2_et_tx_dem_bp_START   (7)
#define ABB_TX_ET_DIG_2_et_tx_dem_bp_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_ET_DIG_3_UNION
 �ṹ˵��  : TX_ET_DIG_3 �Ĵ����ṹ���塣��ַƫ����:0x702����ֵ:0x00�����:8
 �Ĵ���˵��: TX ET�������üĴ���3��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_cal_en   : 1;  /* bit[0]  : ETͨ��calibrationʹ�ܡ��������������calibration��ɺ󣬸�bit�Զ����㡣
                                                      0����ʹ�ܣ�
                                                      1��ʹ�ܡ� */
        unsigned long  et_flush_en : 1;  /* bit[1]  : ETͨ��FLUSHʹ�ܣ�
                                                      0����ʹ��
                                                      1��ʹ�� */
        unsigned long  delay_cnt   : 2;  /* bit[2-3]: ���е����Ƚ�ʱ����ʱ���ơ�Ĭ�ϲ���153.6MHzʱ�ӽ�����ʱ��
                                                      00��30��ʱ�����ڣ�
                                                      01��75��ʱ�����ڣ�
                                                      10��150��ʱ�����ڣ�
                                                      11��300��ʱ�����ڡ� */
        unsigned long  et_cal_type : 1;  /* bit[4]  : ETУ׼�������á�ET DAC��������ʱ�������ַ�����ET DAC�������У׼��
                                                      0����Calibration DAC��ͨ��Calibration DAC�����ET DAC�������У׼��
                                                      1���ر�Calibration DAC����IREG�Ĵ��������Ȩ��ET OUT�������У׼�� */
        unsigned long  reserved_0  : 1;  /* bit[5]  : ���� */
        unsigned long  et_crec_en  : 1;  /* bit[6]  : ET DAC��������ʱ���Ƿ�ʹ��calibration�������У׼��
                                                      0����ʹ�ܣ�
                                                      1��ʹ�ܡ� */
        unsigned long  reserved_1  : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_3_UNION;
#define ABB_TX_ET_DIG_3_et_cal_en_START    (0)
#define ABB_TX_ET_DIG_3_et_cal_en_END      (0)
#define ABB_TX_ET_DIG_3_et_flush_en_START  (1)
#define ABB_TX_ET_DIG_3_et_flush_en_END    (1)
#define ABB_TX_ET_DIG_3_delay_cnt_START    (2)
#define ABB_TX_ET_DIG_3_delay_cnt_END      (3)
#define ABB_TX_ET_DIG_3_et_cal_type_START  (4)
#define ABB_TX_ET_DIG_3_et_cal_type_END    (4)
#define ABB_TX_ET_DIG_3_et_crec_en_START   (6)
#define ABB_TX_ET_DIG_3_et_crec_en_END     (6)


/*****************************************************************************
 �ṹ��    : ABB_TX_ET_DIG_4_UNION
 �ṹ˵��  : TX_ET_DIG_4 �Ĵ����ṹ���塣��ַƫ����:0x703����ֵ:0x00�����:8
 �Ĵ���˵��: TX ET�������üĴ���4��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_tx_en_cfg : 1;  /* bit[0]: ET�߿�ǿ������ֵ�� */
        unsigned long  et_tx_en_sel : 1;  /* bit[1]: ET�߿�ǿ������ʹ�ܡ�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned long  et_apt_cfg   : 1;  /* bit[2]: ETģʽǿ������ֵ�� */
        unsigned long  et_apt_sel   : 1;  /* bit[3]: ETģʽǿ������ʹ�ܡ�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned long  et_div_bp    : 1;  /* bit[4]: ET��Ƶ��ʹ��bypass����
                                                     0����bypass
                                                     1��bypass */
        unsigned long  et_dig_loop  : 1;  /* bit[5]: ETͨ���ӿڻ���ģʽʹ�ܡ���ģʽʹ�ܣ���ET TX����ͨ��RXͨ�����ء�ͨ��et_ch_selѡ�񻷻ص�ch0ͨ������ch1ͨ����
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned long  et_alg_loop  : 1;  /* bit[6]: ETͨ���㷨����ģʽʹ�ܡ���ģʽʹ�ܣ���RXͨ�����ݻ��ص���ͨ��et_ch_selѡ�񻷻ص�ch0ͨ������ch1ͨ����
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned long  reserved     : 1;  /* bit[7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_4_UNION;
#define ABB_TX_ET_DIG_4_et_tx_en_cfg_START  (0)
#define ABB_TX_ET_DIG_4_et_tx_en_cfg_END    (0)
#define ABB_TX_ET_DIG_4_et_tx_en_sel_START  (1)
#define ABB_TX_ET_DIG_4_et_tx_en_sel_END    (1)
#define ABB_TX_ET_DIG_4_et_apt_cfg_START    (2)
#define ABB_TX_ET_DIG_4_et_apt_cfg_END      (2)
#define ABB_TX_ET_DIG_4_et_apt_sel_START    (3)
#define ABB_TX_ET_DIG_4_et_apt_sel_END      (3)
#define ABB_TX_ET_DIG_4_et_div_bp_START     (4)
#define ABB_TX_ET_DIG_4_et_div_bp_END       (4)
#define ABB_TX_ET_DIG_4_et_dig_loop_START   (5)
#define ABB_TX_ET_DIG_4_et_dig_loop_END     (5)
#define ABB_TX_ET_DIG_4_et_alg_loop_START   (6)
#define ABB_TX_ET_DIG_4_et_alg_loop_END     (6)


/*****************************************************************************
 �ṹ��    : ABB_ET_STATE_RPT_UNION
 �ṹ˵��  : ET_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x705����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��״̬�ϱ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_comp_overflow : 1;  /* bit[0]  : ET�����˲������ָʾ�� */
        unsigned long  et_cic6_overflow : 1;  /* bit[1]  : ET CIC6�˲������ָʾ�� */
        unsigned long  et_hb_overflow   : 1;  /* bit[2]  : ET HB�˲������ָʾ�� */
        unsigned long  reserved         : 4;  /* bit[3-6]: ���� */
        unsigned long  et_cal_done      : 1;  /* bit[7]  : ETͨ��У׼��ɡ� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ET_STATE_RPT_UNION;
#define ABB_ET_STATE_RPT_et_comp_overflow_START  (0)
#define ABB_ET_STATE_RPT_et_comp_overflow_END    (0)
#define ABB_ET_STATE_RPT_et_cic6_overflow_START  (1)
#define ABB_ET_STATE_RPT_et_cic6_overflow_END    (1)
#define ABB_ET_STATE_RPT_et_hb_overflow_START    (2)
#define ABB_ET_STATE_RPT_et_hb_overflow_END      (2)
#define ABB_ET_STATE_RPT_et_cal_done_START       (7)
#define ABB_ET_STATE_RPT_et_cal_done_END         (7)


/*****************************************************************************
 �ṹ��    : ABB_ET_ITEMP_REG_MSB_UNION
 �ṹ˵��  : ET_ITEMP_REG_MSB �Ĵ����ṹ���塣��ַƫ����:0x706����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ITEMPУ׼����Ĵ�����λ��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_itemp_reg_msb : 2;  /* bit[0-1]: ITEMPУ׼�����λ�� */
        unsigned long  reserved         : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ITEMP_REG_MSB_UNION;
#define ABB_ET_ITEMP_REG_MSB_et_itemp_reg_msb_START  (0)
#define ABB_ET_ITEMP_REG_MSB_et_itemp_reg_msb_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT1_UNION
 �ṹ˵��  : ET_ICELL_SORT1 �Ĵ����ṹ���塣��ַƫ����:0x727����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������1��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort1 : 5;  /* bit[0-4]: ICELL�������Ĵ���1�� */
        unsigned long  reserved       : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT1_UNION;
#define ABB_ET_ICELL_SORT1_et_icell_sort1_START  (0)
#define ABB_ET_ICELL_SORT1_et_icell_sort1_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT2_UNION
 �ṹ˵��  : ET_ICELL_SORT2 �Ĵ����ṹ���塣��ַƫ����:0x728����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort2 : 5;  /* bit[0-4]: ICELL�������Ĵ���2�� */
        unsigned long  reserved       : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT2_UNION;
#define ABB_ET_ICELL_SORT2_et_icell_sort2_START  (0)
#define ABB_ET_ICELL_SORT2_et_icell_sort2_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT3_UNION
 �ṹ˵��  : ET_ICELL_SORT3 �Ĵ����ṹ���塣��ַƫ����:0x729����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������3��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort3 : 5;  /* bit[0-4]: ICELL�������Ĵ���3�� */
        unsigned long  reserved       : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT3_UNION;
#define ABB_ET_ICELL_SORT3_et_icell_sort3_START  (0)
#define ABB_ET_ICELL_SORT3_et_icell_sort3_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT4_UNION
 �ṹ˵��  : ET_ICELL_SORT4 �Ĵ����ṹ���塣��ַƫ����:0x72A����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������4��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort4 : 5;  /* bit[0-4]: ICELL�������Ĵ���4�� */
        unsigned long  reserved       : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT4_UNION;
#define ABB_ET_ICELL_SORT4_et_icell_sort4_START  (0)
#define ABB_ET_ICELL_SORT4_et_icell_sort4_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT5_UNION
 �ṹ˵��  : ET_ICELL_SORT5 �Ĵ����ṹ���塣��ַƫ����:0x72B����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������5��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort5 : 5;  /* bit[0-4]: ICELL�������Ĵ���5�� */
        unsigned long  reserved       : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT5_UNION;
#define ABB_ET_ICELL_SORT5_et_icell_sort5_START  (0)
#define ABB_ET_ICELL_SORT5_et_icell_sort5_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT6_UNION
 �ṹ˵��  : ET_ICELL_SORT6 �Ĵ����ṹ���塣��ַƫ����:0x72C����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������6��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort6 : 5;  /* bit[0-4]: ICELL�������Ĵ���6�� */
        unsigned long  reserved       : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT6_UNION;
#define ABB_ET_ICELL_SORT6_et_icell_sort6_START  (0)
#define ABB_ET_ICELL_SORT6_et_icell_sort6_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT7_UNION
 �ṹ˵��  : ET_ICELL_SORT7 �Ĵ����ṹ���塣��ַƫ����:0x72D����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������7��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort7 : 5;  /* bit[0-4]: ICELL�������Ĵ���7�� */
        unsigned long  reserved       : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT7_UNION;
#define ABB_ET_ICELL_SORT7_et_icell_sort7_START  (0)
#define ABB_ET_ICELL_SORT7_et_icell_sort7_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT8_UNION
 �ṹ˵��  : ET_ICELL_SORT8 �Ĵ����ṹ���塣��ַƫ����:0x72E����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������8��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort8 : 5;  /* bit[0-4]: ICELL�������Ĵ���8�� */
        unsigned long  reserved       : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT8_UNION;
#define ABB_ET_ICELL_SORT8_et_icell_sort8_START  (0)
#define ABB_ET_ICELL_SORT8_et_icell_sort8_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT9_UNION
 �ṹ˵��  : ET_ICELL_SORT9 �Ĵ����ṹ���塣��ַƫ����:0x72F����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������9��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort9 : 5;  /* bit[0-4]: ICELL�������Ĵ���9�� */
        unsigned long  reserved       : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT9_UNION;
#define ABB_ET_ICELL_SORT9_et_icell_sort9_START  (0)
#define ABB_ET_ICELL_SORT9_et_icell_sort9_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT10_UNION
 �ṹ˵��  : ET_ICELL_SORT10 �Ĵ����ṹ���塣��ַƫ����:0x730����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������10��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort10 : 5;  /* bit[0-4]: ICELL�������Ĵ���10�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT10_UNION;
#define ABB_ET_ICELL_SORT10_et_icell_sort10_START  (0)
#define ABB_ET_ICELL_SORT10_et_icell_sort10_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT11_UNION
 �ṹ˵��  : ET_ICELL_SORT11 �Ĵ����ṹ���塣��ַƫ����:0x731����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������11��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort11 : 5;  /* bit[0-4]: ICELL�������Ĵ���11�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT11_UNION;
#define ABB_ET_ICELL_SORT11_et_icell_sort11_START  (0)
#define ABB_ET_ICELL_SORT11_et_icell_sort11_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT12_UNION
 �ṹ˵��  : ET_ICELL_SORT12 �Ĵ����ṹ���塣��ַƫ����:0x732����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������12��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort12 : 5;  /* bit[0-4]: ICELL�������Ĵ���12�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT12_UNION;
#define ABB_ET_ICELL_SORT12_et_icell_sort12_START  (0)
#define ABB_ET_ICELL_SORT12_et_icell_sort12_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT13_UNION
 �ṹ˵��  : ET_ICELL_SORT13 �Ĵ����ṹ���塣��ַƫ����:0x733����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������13��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort13 : 5;  /* bit[0-4]: ICELL�������Ĵ���13�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT13_UNION;
#define ABB_ET_ICELL_SORT13_et_icell_sort13_START  (0)
#define ABB_ET_ICELL_SORT13_et_icell_sort13_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT14_UNION
 �ṹ˵��  : ET_ICELL_SORT14 �Ĵ����ṹ���塣��ַƫ����:0x734����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������14��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort14 : 5;  /* bit[0-4]: ICELL�������Ĵ���14�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT14_UNION;
#define ABB_ET_ICELL_SORT14_et_icell_sort14_START  (0)
#define ABB_ET_ICELL_SORT14_et_icell_sort14_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT15_UNION
 �ṹ˵��  : ET_ICELL_SORT15 �Ĵ����ṹ���塣��ַƫ����:0x735����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������15��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort15 : 5;  /* bit[0-4]: ICELL�������Ĵ���15�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT15_UNION;
#define ABB_ET_ICELL_SORT15_et_icell_sort15_START  (0)
#define ABB_ET_ICELL_SORT15_et_icell_sort15_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT16_UNION
 �ṹ˵��  : ET_ICELL_SORT16 �Ĵ����ṹ���塣��ַƫ����:0x736����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������16��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort16 : 5;  /* bit[0-4]: ICELL�������Ĵ���16�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT16_UNION;
#define ABB_ET_ICELL_SORT16_et_icell_sort16_START  (0)
#define ABB_ET_ICELL_SORT16_et_icell_sort16_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT17_UNION
 �ṹ˵��  : ET_ICELL_SORT17 �Ĵ����ṹ���塣��ַƫ����:0x737����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������17��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort17 : 5;  /* bit[0-4]: ICELL�������Ĵ���17�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT17_UNION;
#define ABB_ET_ICELL_SORT17_et_icell_sort17_START  (0)
#define ABB_ET_ICELL_SORT17_et_icell_sort17_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT18_UNION
 �ṹ˵��  : ET_ICELL_SORT18 �Ĵ����ṹ���塣��ַƫ����:0x738����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������18��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort18 : 5;  /* bit[0-4]: ICELL�������Ĵ���18�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT18_UNION;
#define ABB_ET_ICELL_SORT18_et_icell_sort18_START  (0)
#define ABB_ET_ICELL_SORT18_et_icell_sort18_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT19_UNION
 �ṹ˵��  : ET_ICELL_SORT19 �Ĵ����ṹ���塣��ַƫ����:0x739����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������19��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort19 : 5;  /* bit[0-4]: ICELL�������Ĵ���19�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT19_UNION;
#define ABB_ET_ICELL_SORT19_et_icell_sort19_START  (0)
#define ABB_ET_ICELL_SORT19_et_icell_sort19_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT20_UNION
 �ṹ˵��  : ET_ICELL_SORT20 �Ĵ����ṹ���塣��ַƫ����:0x73A����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������20��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort20 : 5;  /* bit[0-4]: ICELL�������Ĵ���20�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT20_UNION;
#define ABB_ET_ICELL_SORT20_et_icell_sort20_START  (0)
#define ABB_ET_ICELL_SORT20_et_icell_sort20_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT21_UNION
 �ṹ˵��  : ET_ICELL_SORT21 �Ĵ����ṹ���塣��ַƫ����:0x73B����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������21��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort21 : 5;  /* bit[0-4]: ICELL�������Ĵ���21�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT21_UNION;
#define ABB_ET_ICELL_SORT21_et_icell_sort21_START  (0)
#define ABB_ET_ICELL_SORT21_et_icell_sort21_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT22_UNION
 �ṹ˵��  : ET_ICELL_SORT22 �Ĵ����ṹ���塣��ַƫ����:0x73C����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������22��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort22 : 5;  /* bit[0-4]: ICELL�������Ĵ���22�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT22_UNION;
#define ABB_ET_ICELL_SORT22_et_icell_sort22_START  (0)
#define ABB_ET_ICELL_SORT22_et_icell_sort22_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT23_UNION
 �ṹ˵��  : ET_ICELL_SORT23 �Ĵ����ṹ���塣��ַƫ����:0x73D����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������23��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort23 : 5;  /* bit[0-4]: ICELL�������Ĵ���23�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT23_UNION;
#define ABB_ET_ICELL_SORT23_et_icell_sort23_START  (0)
#define ABB_ET_ICELL_SORT23_et_icell_sort23_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT24_UNION
 �ṹ˵��  : ET_ICELL_SORT24 �Ĵ����ṹ���塣��ַƫ����:0x73E����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������24��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort24 : 5;  /* bit[0-4]: ICELL�������Ĵ���24�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT24_UNION;
#define ABB_ET_ICELL_SORT24_et_icell_sort24_START  (0)
#define ABB_ET_ICELL_SORT24_et_icell_sort24_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT25_UNION
 �ṹ˵��  : ET_ICELL_SORT25 �Ĵ����ṹ���塣��ַƫ����:0x73F����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������25��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort25 : 5;  /* bit[0-4]: ICELL�������Ĵ���25�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT25_UNION;
#define ABB_ET_ICELL_SORT25_et_icell_sort25_START  (0)
#define ABB_ET_ICELL_SORT25_et_icell_sort25_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT26_UNION
 �ṹ˵��  : ET_ICELL_SORT26 �Ĵ����ṹ���塣��ַƫ����:0x740����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������26��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort26 : 5;  /* bit[0-4]: ICELL�������Ĵ���26�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT26_UNION;
#define ABB_ET_ICELL_SORT26_et_icell_sort26_START  (0)
#define ABB_ET_ICELL_SORT26_et_icell_sort26_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT27_UNION
 �ṹ˵��  : ET_ICELL_SORT27 �Ĵ����ṹ���塣��ַƫ����:0x741����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������27��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort27 : 5;  /* bit[0-4]: ICELL�������Ĵ���27�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT27_UNION;
#define ABB_ET_ICELL_SORT27_et_icell_sort27_START  (0)
#define ABB_ET_ICELL_SORT27_et_icell_sort27_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT28_UNION
 �ṹ˵��  : ET_ICELL_SORT28 �Ĵ����ṹ���塣��ַƫ����:0x742����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������28��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort28 : 5;  /* bit[0-4]: ICELL�������Ĵ���28�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT28_UNION;
#define ABB_ET_ICELL_SORT28_et_icell_sort28_START  (0)
#define ABB_ET_ICELL_SORT28_et_icell_sort28_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT29_UNION
 �ṹ˵��  : ET_ICELL_SORT29 �Ĵ����ṹ���塣��ַƫ����:0x743����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������29��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort29 : 5;  /* bit[0-4]: ICELL�������Ĵ���29�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT29_UNION;
#define ABB_ET_ICELL_SORT29_et_icell_sort29_START  (0)
#define ABB_ET_ICELL_SORT29_et_icell_sort29_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT30_UNION
 �ṹ˵��  : ET_ICELL_SORT30 �Ĵ����ṹ���塣��ַƫ����:0x744����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������30��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort30 : 5;  /* bit[0-4]: ICELL�������Ĵ���30�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT30_UNION;
#define ABB_ET_ICELL_SORT30_et_icell_sort30_START  (0)
#define ABB_ET_ICELL_SORT30_et_icell_sort30_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_SORT31_UNION
 �ṹ˵��  : ET_ICELL_SORT31 �Ĵ����ṹ���塣��ַƫ����:0x745����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�����������31��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_sort31 : 5;  /* bit[0-4]: ICELL�������Ĵ���31�� */
        unsigned long  reserved        : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_SORT31_UNION;
#define ABB_ET_ICELL_SORT31_et_icell_sort31_START  (0)
#define ABB_ET_ICELL_SORT31_et_icell_sort31_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_ET_ICELL_UPDATE_UNION
 �ṹ˵��  : ET_ICELL_UPDATE �Ĵ����ṹ���塣��ַƫ����:0x746����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��ICELL�Ĵ�������
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_icell_update : 1;  /* bit[0]  : ���øüĴ��������¼Ĵ���ET_ICELL_REG1~ET_ICELL_SORT31���Ĵ����������֮����Ҫ����Ϊ0�� */
        unsigned long  reserved        : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_ET_ICELL_UPDATE_UNION;
#define ABB_ET_ICELL_UPDATE_et_icell_update_START  (0)
#define ABB_ET_ICELL_UPDATE_et_icell_update_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_ET_SINE_GENERATE_UNION
 �ṹ˵��  : ET_SINE_GENERATE �Ĵ����ṹ���塣��ַƫ����:0x74B����ֵ:0x10�����:8
 �Ĵ���˵��: SINE���ͼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_sine_enable : 1;  /* bit[0]  : etͨ�����Ҳ�����ʹ�ܡ���λʹ�ܣ���ETͨ���������Ҳ��źţ���ͨ��sine_sw_reqѡ��CH0����CH1�������Ҳ��źš�
                                                         0��������
                                                         1������ */
        unsigned long  reserved       : 1;  /* bit[1]  : ���� */
        unsigned long  et_sine_amp    : 2;  /* bit[2-3]: ���Ҳ����ͷ��ȿ���
                                                         00��������
                                                         01��3/4����
                                                         10��1/2����
                                                         11��1/4���� */
        unsigned long  et_sine_freq   : 4;  /* bit[4-7]: ���Ҳ�����Ƶ�ʿ��ƣ���λ(freq of tx_hb_clk)/32�����䷶ΧΪ1~f */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_SINE_GENERATE_UNION;
#define ABB_ET_SINE_GENERATE_et_sine_enable_START  (0)
#define ABB_ET_SINE_GENERATE_et_sine_enable_END    (0)
#define ABB_ET_SINE_GENERATE_et_sine_amp_START     (2)
#define ABB_ET_SINE_GENERATE_et_sine_amp_END       (3)
#define ABB_ET_SINE_GENERATE_et_sine_freq_START    (4)
#define ABB_ET_SINE_GENERATE_et_sine_freq_END      (7)

/*****************************************************************************
 �ṹ��    : ABB_CH0_LINE_RPT1_UNION
 �ṹ˵��  : CH0_LINE_RPT1 �Ĵ����ṹ���塣��ַƫ����:0x254����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_line_ctrl_mode_rpt : 3;  /* bit[0-2]: �߿��ź�LINE_CTRL_MODE״̬�ϱ�
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ
                                                                    others��IDLE */
        unsigned long  ch0_reserved_1            : 1;  /* bit[3]  : Reserved */
        unsigned long  ch0_rxa_blk_en_rpt        : 1;  /* bit[4]  : RXA_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch0_rxb_blk_en_rpt        : 1;  /* bit[5]  : RXB_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch0_reserved_0            : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_RPT1_UNION;

/*****************************************************************************
 �ṹ��    : ABB_CH1_LINE_RPT1_UNION
 �ṹ˵��  : CH1_LINE_RPT1 �Ĵ����ṹ���塣��ַƫ����:0x454����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_line_ctrl_mode_rpt : 3;  /* bit[0-2]: �߿��ź�LINE_CTRL_MODE״̬�ϱ�
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ
                                                                    others��IDLE */
        unsigned long  ch1_reserved_1            : 1;  /* bit[3]  : Reserved */
        unsigned long  ch1_rxa_blk_en_rpt        : 1;  /* bit[4]  : RXA_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch1_rxb_blk_en_rpt        : 1;  /* bit[5]  : RXB_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch1_reserved_0            : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_RPT1_UNION;

/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_3G_DIG_1_UNION
 �ṹ˵��  : CH0_RX_3G_DIG_1 �Ĵ����ṹ���塣��ַƫ����:0x206����ֵ:0x2C�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_comp_sel_3g : 3;  /* bit[0-2]: RXͨ�������˲�������ϵ���̶����ƣ�
                                                             000��ϵ�����̶����ɼĴ������ã�
                                                             001���̶�ϵ��1��
                                                             010���̶�ϵ��2��
                                                             011���̶�ϵ��3��
                                                             100���̶�ϵ��4��
                                                             101���̶�ϵ��5��
                                                             110���̶�ϵ��6��
                                                             111���̶�ϵ��7�� */
        unsigned long  ch0_rx_hb_bp_3g    : 1;  /* bit[3]  : RXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  ch0_rx_rate_3g     : 1;  /* bit[4]  : RXͨ��CIC�˲���������ʿ���(MHz)��
                                                                   2G,   3G_SC&amp;4G_5M, 4G_20M, 3G_DC&amp;TDS&amp;4G_10M,   CA,   CDMA
                                                             0�� 2.167,     15.36,    61.44,      30.72,       122.88, 4.9152
                                                             others��reserved */
        unsigned long  ch0_rx_mode_dig_3g : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                             000��2G
                                                             001��3G_SC&amp;4G_5M(Ĭ��)
                                                             010��4G_20M
                                                             011��3G_DC&amp;4G_10M
                                                             100��TDS
                                                             101��CA
                                                             Others��CDMA */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_3G_DIG_1_UNION;

/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_3G_DIG_1_UNION
 �ṹ˵��  : CH1_RX_3G_DIG_1 �Ĵ����ṹ���塣��ַƫ����:0x406����ֵ:0x2C�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_comp_sel_3g : 3;  /* bit[0-2]: RXͨ�������˲�������ϵ���̶����ƣ�
                                                             000��ϵ�����̶����ɼĴ������ã�
                                                             001���̶�ϵ��1��
                                                             010���̶�ϵ��2��
                                                             011���̶�ϵ��3��
                                                             100���̶�ϵ��4��
                                                             101���̶�ϵ��5��
                                                             110���̶�ϵ��6��
                                                             111���̶�ϵ��7�� */
        unsigned long  ch1_rx_hb_bp_3g    : 1;  /* bit[3]  : RXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  ch1_rx_rate_3g     : 1;  /* bit[4]  : RXͨ��CIC�˲���������ʿ���(MHz)��
                                                                   2G,   3G_SC&amp;4G_5M, 4G_20M, 3G_DC&amp;TDS&amp;4G_10M,   CA,   CDMA
                                                             0�� 2.167,     15.36,    61.44,      30.72,       122.88, 4.9152
                                                             others��reserved */
        unsigned long  ch1_rx_mode_dig_3g : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                             000��2G
                                                             001��3G_SC&amp;4G_5M(Ĭ��)
                                                             010��4G_20M
                                                             011��3G_DC&amp;4G_10M
                                                             100��TDS
                                                             101��CA
                                                             Others��CDMA */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_3G_DIG_1_UNION;

/*****************************************************************************
 �ṹ��    : ABB_CH0_LINE_RPT0_UNION
 �ṹ˵��  : CH0_LINE_RPT0 �Ĵ����ṹ���塣��ַƫ����:0x253����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_en_rpt            : 1;  /* bit[0]  : RXA_EN�߿�״̬�ϱ� */
        unsigned long  ch0_rxb_en_rpt            : 1;  /* bit[1]  : RXB_EN�߿�״̬�ϱ� */
        unsigned long  ch0_tx_en_rpt             : 1;  /* bit[2]  : TX_EN�߿�״̬�ϱ� */
        unsigned long  ch0_tx_line_ctrl_mode_rpt : 3;  /* bit[3-5]: �߿��ź�LINE_CTRL_MODE״̬�ϱ�
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ
                                                                    others��IDLE */
        unsigned long  ch0_reserved              : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_RPT0_UNION;

/*****************************************************************************
 �ṹ��    : ABB_CH1_LINE_RPT0_UNION
 �ṹ˵��  : CH1_LINE_RPT0 �Ĵ����ṹ���塣��ַƫ����:0x453����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_en_rpt            : 1;  /* bit[0]  : RXA_EN�߿�״̬�ϱ� */
        unsigned long  ch1_rxb_en_rpt            : 1;  /* bit[1]  : RXB_EN�߿�״̬�ϱ� */
        unsigned long  ch1_tx_en_rpt             : 1;  /* bit[2]  : TX_EN�߿�״̬�ϱ� */
        unsigned long  ch1_tx_line_ctrl_mode_rpt : 3;  /* bit[3-5]: �߿��ź�LINE_CTRL_MODE״̬�ϱ�
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ
                                                                    others��IDLE */
        unsigned long  ch1_reserved              : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_RPT0_UNION;

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

#endif /* end of phy_abb_interface.h */

