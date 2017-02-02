

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __ABB_INTERFACE_TV101_H__
#define __ABB_INTERFACE_TV101_H__

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
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
             ��V8R1���漰��
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
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
             ��V8R1���漰��
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
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
             ��V8R1���漰��
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
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
             ��V8R1���漰��
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
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
             ��V8R1���漰��
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
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
             ��V8R1���漰��
   UNION�ṹ:  ABB_TX_IDLE_DIG_3_UNION */
#define ABB_TX_IDLE_DIG_3_ADDR                        (ABB_BASE_ADDR + 0x23)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      RX DEM Mode Selection,bit 1
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G
             010��3G_DC &amp; TDS
             011��2G(Ĭ��)
             100��reserved
             101��CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
   UNION�ṹ:  ABB_RX_2G_ANA_1_UNION */
#define ABB_RX_2G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x24)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������ch0_reg_analog_wr01��
 bit[7:6]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[1]      ����
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_2G_ANA_2_UNION */
#define ABB_RX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x25)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������reg_analog_wr48��
 bit[7:6]    TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
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
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��8��Ƶ
             11��4��Ƶ
 bit[3]      TX_I DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G &amp; TDS
             010��reserved
             011��2G(Ĭ��)
             1xx��CDMA
   UNION�ṹ:  ABB_TX_2G_ANA_1_UNION */
#define ABB_TX_2G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x26)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_2G��˵����
 bit[5:4]    LPF �˷�ƫ�õ�������
             00��   10u
             01��    5u
             10��    5u
             11��    3u
             Ĭ�����÷�����
             LTE:00   GSM:11   Others:01
 bit[3:2]    ����
 bit[1:0]    LPF OP����ģʽ����
             00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
             01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
             10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
             11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

             Ĭ�����÷�����
             LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11
   UNION�ṹ:  ABB_TX_2G_ANA_2_UNION */
#define ABB_TX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x27)

/* �Ĵ���˵����CH0 RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      RX DEM Mode Selection,bit 1
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G
             010��3G_DC &amp; TDS
             011��2G(Ĭ��)
             100��reserved
             101��CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
   UNION�ṹ:  ABB_RX_CH0_3G_ANA_1_UNION */
#define ABB_RX_CH0_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x28)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr01��
 bit[7:6]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[1]      ����
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_CH0_3G_ANA_2_UNION */
#define ABB_RX_CH0_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x29)

/* �Ĵ���˵����CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr48��
 bit[7:6]    TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
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
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��8��Ƶ
             11��4��Ƶ
 bit[3]      TX_I DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G &amp; TDS
             010��reserved
             011��2G(Ĭ��)
             1xx��CDMA
   UNION�ṹ:  ABB_TX_CH0_3G_ANA_1_UNION */
#define ABB_TX_CH0_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2A)

/* �Ĵ���˵����CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_3G��˵����
 bit[5:4]    LPF �˷�ƫ�õ�������
             00��   10u
             01��    5u
             10��    5u
             11��    3u
             Ĭ�����÷�����
             LTE:00   GSM:11   Others:01
 bit[3:2]    ����
 bit[1:0]    LPF OP����ģʽ����
             00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
             01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
             10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
             11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

             Ĭ�����÷�����
             LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11
   UNION�ṹ:  ABB_TX_CH0_3G_ANA_2_UNION */
#define ABB_TX_CH0_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2B)

/* �Ĵ���˵����CH0 RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      RX DEM Mode Selection,bit 1
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G
             010��3G_DC &amp; TDS
             011��2G(Ĭ��)
             100��reserved
             101��CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
   UNION�ṹ:  ABB_RX_CH0_4G_ANA_1_UNION */
#define ABB_RX_CH0_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2C)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr01��
 bit[7:6]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[1]      ����
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_CH0_4G_ANA_2_UNION */
#define ABB_RX_CH0_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2D)

/* �Ĵ���˵����CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr48��
 bit[7:6]    TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
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
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��8��Ƶ
             11��4��Ƶ
 bit[3]      TX_I DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G &amp; TDS
             010��reserved
             011��2G(Ĭ��)
             1xx��CDMA
   UNION�ṹ:  ABB_TX_CH0_4G_ANA_1_UNION */
#define ABB_TX_CH0_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2E)

/* �Ĵ���˵����CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_4G��˵����
 bit[5:4]    LPF �˷�ƫ�õ�������
             00��   10u
             01��    5u
             10��    5u
             11��    3u
             Ĭ�����÷�����
             LTE:00   GSM:11   Others:01
 bit[3:2]    ����
 bit[1:0]    LPF OP����ģʽ����
             00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
             01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
             10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
             11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

             Ĭ�����÷�����
             LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11
   UNION�ṹ:  ABB_TX_CH0_4G_ANA_2_UNION */
#define ABB_TX_CH0_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2F)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      RX DEM Mode Selection,bit 1
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G
             010��3G_DC &amp; TDS
             011��2G(Ĭ��)
             100��reserved
             101��CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
   UNION�ṹ:  ABB_RX_TDS_ANA_1_UNION */
#define ABB_RX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x30)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������ch0_reg_analog_wr01��
 bit[7:6]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[1]      ����
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_TDS_ANA_2_UNION */
#define ABB_RX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x31)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������reg_analog_wr48��
 bit[7:6]    TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
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
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��8��Ƶ
             11��4��Ƶ
 bit[3]      TX_I DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G &amp; TDS
             010��reserved
             011��2G(Ĭ��)
             1xx��CDMA
   UNION�ṹ:  ABB_TX_TDS_ANA_1_UNION */
#define ABB_TX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x32)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_TDS��˵����
 bit[5:4]    LPF �˷�ƫ�õ�������
             00��   10u
             01��    5u
             10��    5u
             11��    3u
             Ĭ�����÷�����
             LTE:00   GSM:11   Others:01
 bit[3:2]    ����
 bit[1:0]    LPF OP����ģʽ����
             00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
             01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
             10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
             11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

             Ĭ�����÷�����
             LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11
   UNION�ṹ:  ABB_TX_TDS_ANA_2_UNION */
#define ABB_TX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x33)

/* �Ĵ���˵����CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      RX DEM Mode Selection,bit 1
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G
             010��3G_DC &amp; TDS
             011��2G(Ĭ��)
             100��reserved
             101��CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
   UNION�ṹ:  ABB_RX_CH1_4G_ANA_1_UNION */
#define ABB_RX_CH1_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x38)

/* �Ĵ���˵����CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr01��
 bit[7:6]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[1]      ����
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_CH1_4G_ANA_2_UNION */
#define ABB_RX_CH1_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x39)

/* �Ĵ���˵����CH1 TX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr48��
 bit[7:6]    TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
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
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��8��Ƶ
             11��4��Ƶ
 bit[3]      TX_I DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G &amp; TDS
             010��reserved
             011��2G(Ĭ��)
             1xx��CDMA
   UNION�ṹ:  ABB_TX_CH1_4G_ANA_1_UNION */
#define ABB_TX_CH1_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x3A)

/* �Ĵ���˵����CH1 TX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_4G��˵����
 bit[5:4]    LPF �˷�ƫ�õ�������
             00��   10u
             01��    5u
             10��    5u
             11��    3u
             Ĭ�����÷�����
             LTE:00   GSM:11   Others:01
 bit[3:2]    ����
 bit[1:0]    LPF OP����ģʽ����
             00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
             01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
             10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
             11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

             Ĭ�����÷�����
             LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11
   UNION�ṹ:  ABB_TX_CH1_4G_ANA_2_UNION */
#define ABB_TX_CH1_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x3B)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      RX DEM Mode Selection,bit 1
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G
             010��3G_DC &amp; TDS
             011��2G(Ĭ��)
             100��reserved
             101��CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
   UNION�ṹ:  ABB_RX_IDLE_ANA_1_UNION */
#define ABB_RX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3C)

/* �Ĵ���˵����IDLE���üĴ����������߿��߼�������reg_analog_wr01��
 bit[7:6]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[1]      ����
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_IDLE_ANA_2_UNION */
#define ABB_RX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3D)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr48��
 bit[7:6]    TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
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
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��8��Ƶ
             11��4��Ƶ
 bit[3]      TX_I DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G &amp; TDS
             010��reserved
             011��2G(Ĭ��)
             1xx��CDMA
   UNION�ṹ:  ABB_TX_IDLE_ANA_1_UNION */
#define ABB_TX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3E)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_IDLE��˵����
 bit[5:4]    LPF �˷�ƫ�õ�������
             00��   10u
             01��    5u
             10��    5u
             11��    3u
             Ĭ�����÷�����
             LTE:00   GSM:11   Others:01
 bit[3:2]    ����
 bit[1:0]    LPF OP����ģʽ����
             00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
             01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
             10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
             11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

             Ĭ�����÷�����
             LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11
   UNION�ṹ:  ABB_TX_IDLE_ANA_2_UNION */
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

/* �Ĵ���˵����CFR��ֵ��ⴰ���Ĵ�����
 bit[7:4]    CFR��������
             ��V8R1���漰��
 bit[3]      ����
 bit[2]      CFR�˲���ѡ��
             0��bypass�˲���
             1����bypass�˲���
             ��V8R1���漰��
 bit[1:0]    CFR��ֵ��ⷽʽ��
             00���������
             01���������
             10���������
             11��ȫ����ֵ
             ��V8R1���漰��
   UNION�ṹ:  ABB_CH1_CFR_CTRL_UNION */
#define ABB_CH1_CFR_CTRL_ADDR                         (ABB_BASE_ADDR + 0x43)

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
 bit[7:6]    ����
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
 bit[7:4]    Reserved
 bit[3]      RX ADC�Զ�tuning����
             0���ֶ�tuning��tuningѡ��RX_TUNE1,RX_TUNE2,RX_TUNE3��ֵ(Ĭ��)
             1���Զ�tuning��RXͨ����calibrationֵΪCAL_VALUE
 bit[2]      TX ADC�Զ�tuning����
             0���ֶ�tuning��tuningѡ��TX_TUNE1,TX_TUNE2,TX_TUNE3��ֵ(Ĭ��)
             1���Զ�tuning��TXͨ����calibrationֵΪCAL_VALUE
 bit[1]      Reserved
 bit[0]      RC TUNE����
             ����������RC У׼����
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR04_UNION */
#define ABB_CH1_REG_ANALOG_WR04_ADDR                  (ABB_BASE_ADDR + 0x72)

/* �Ĵ���˵����ADC��һ������������tuning�Ĵ�����
 bit[7]      Reserved
 bit[6:0]    ADC��һ������������tuning
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR05_UNION */
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
 bit[7]      Reserved
 bit[6:0]    TX_TUNE1�����ź�
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR08_UNION */
#define ABB_CH1_REG_ANALOG_WR08_ADDR                  (ABB_BASE_ADDR + 0x76)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
 bit[7]      Reserved
 bit[6:0]    TX_TUNE2�����ź�
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR09_UNION */
#define ABB_CH1_REG_ANALOG_WR09_ADDR                  (ABB_BASE_ADDR + 0x77)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
 bit[7]      Reserved
 bit[6:0]    TX_TUNE3�����ź�
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR10_UNION */
#define ABB_CH1_REG_ANALOG_WR10_ADDR                  (ABB_BASE_ADDR + 0x78)

/* �Ĵ���˵����ʱ�ӷ��ؿ��ƼĴ�����
 bit[7]      Reserved
 bit[6]      ADC SYNC�źŲ����ؿ��ƣ�
             0������(Ĭ��)
             1������
 bit[5]      ADC�����ؿ��ƣ�
             0������(Ĭ��)
             1������
 bit[4:1]    Reserved
 bit[0]      ADC������У׼ʹ�ܣ�
             0��Not Cal(Ĭ��)
             1��Cal
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR38_UNION */
#define ABB_CH1_REG_ANALOG_WR38_ADDR                  (ABB_BASE_ADDR + 0x79)

/* �Ĵ���˵����DUM���ƼĴ�����
 bit[7]      RX DEM Mode Selection,bit 2,��ch0_reg_analog_wr00��bit3��bit0��ϳ�3bit��ʵ������9����ϣ�
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
 bit[6:2]    Reserved
 bit[1]      Reserved
 bit[0]      Reserved
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR39_UNION */
#define ABB_CH1_REG_ANALOG_WR39_ADDR                  (ABB_BASE_ADDR + 0x7A)

/* �Ĵ���˵������־λֻ���Ĵ�����
 bit[7]      Reserved
 bit[6]      Reserved��
 bit[5]      RC Calibration Done�ź�
 bit[4:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_ANALOG_RO0_UNION */
#define ABB_CH1_REG_ANALOG_RO0_ADDR                   (ABB_BASE_ADDR + 0x7B)

/* �Ĵ���˵����RCУ׼ֻ���Ĵ�����
 bit[7]      Reserved
 bit[6:0]    RC У׼ֵ
   UNION�ṹ:  ABB_CH1_REG_ANALOG_RO1_UNION */
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
 bit[7:4]    ����
 bit[3:1]    ����ʱ��ѡ��
             000: PLL ����� CLK��
             001��ѡ��������PLL��ʱ����Ϊ����ʱ��
             010��ѡ��������CLKIN_SYSTEM�����ʱ����Ϊ����ʱ��
             100��ѡ��������TCXO_IN��ʱ����Ϊ����ʱ��
 bit[0]      ����
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA0_UNION */
#define ABB_CH1_REG_DEBUG_ANA0_ADDR                   (ABB_BASE_ADDR + 0x80)

/* �Ĵ���˵����PLL LOCK���ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA1_ADDR                   (ABB_BASE_ADDR + 0x81)

/* �Ĵ���˵����PLL���ƼĴ�����
 bit[7]      ����ʱ�ӿ���
             1������ʱ�Ӵ�
             0������ʱ�ӹر�
 bit[6:2]    ����
 bit[1]      ����
 bit[0]      ����
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA2_UNION */
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
 bit[7]      ABB_REF_Fast_UP����
             0���ر�(Ĭ��)
             1������
 bit[6:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA5_UNION */
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
 bit[7:5]    Reserved
 bit[4]      ADCģ��Tuning���ѡ��
             0��ѡ��Tuningģ��������ΪLTE ADC��Tuning��
             1��ѡ��Ĵ����������ΪLTE ADC��Tuning��
 bit[3]      ADC DEM���ܹر��ź�
             0��DEMʹ��
             1��DEM��ʹ��
 bit[2]      Reserved
 bit[1]      LTE ADCģ������ģʽѡ��
             0���Զ�ģʽ
             1�����üĴ���ģʽ
 bit[0]      Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA9_UNION */
#define ABB_CH1_REG_DEBUG_ANA9_ADDR                   (ABB_BASE_ADDR + 0x89)

/* �Ĵ���˵����ADC��λ���ƼĴ�����
 bit[7]      ADC��RST_CAP����
             0��Reset CAP123
             1����Reset CAP123
 bit[6]      ADC��OP1ģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[5]      ADC��OP1 OffsetУ׼������̽ӿ��ؿ���
             0������̽ӿ��ضϿ�����������ģʽ��
             1������̽ӿ��رպϣ����˷�����˶̽ӵ���ģ��ѹ��
 bit[4]      ADC��QUģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[3]      ADC��CKGEN_QUģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[2]      ADC��OP1 OffsetУ׼�����ź�
             0��У׼������
             1������OP1 OffsetУ׼
 bit[1]      ADC��OP23ģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[0]      ADC��DACģ��Powerup����
             0��Powerdown
             1��Powerup
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA10_UNION */
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
 bit[7:6]    Reserved
 bit[5:3]    Reserved
 bit[2:0]    ADC Overloadģ������
             00��16����������������С��
             01��8����������������С��
             10��4����������������С��
             11���ر�Overload���
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA14_UNION */
#define ABB_CH1_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0x8E)

/* �Ĵ���˵����ADC�ӳٿ��ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0x8F)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7]      RX���PDM�������
             0��adder encoder���ӷ��������
             1��de-bubble encoder���������������
 bit[6]      Reserved
 bit[5:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA16_UNION */
#define ABB_CH1_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0x90)

/* �Ĵ���˵����PLL���ԼĴ�����
 bit[7:6]    Reserved
 bit[5:4]    Reserved
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA17_UNION */
#define ABB_CH1_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0x91)

/* �Ĵ���˵����TX�ֹ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0x92)

/* �Ĵ���˵����ʱ��ʹ�ܿ��ƼĴ�����
 bit[7:6]    ����
 bit[5]      PLLģ��307.2MHzʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[4]      PLLģ��312MHzʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA19_UNION */
#define ABB_CH1_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0x93)

/* �Ĵ���˵����ģ����ԼĴ�����
 bit[7]      Reserved
 bit[6:5]    ADC���������ݱ���ϵ��
             00��X1(Ĭ��)
             01��X1.5
             10��X1.25
             11��X1.125
 bit[4:3]    Reserved
 bit[2]      ����
 bit[1]      ����
 bit[0]      ����
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA20_UNION */
#define ABB_CH1_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0x94)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0x95)

/* �Ĵ���˵����ģ����ԼĴ�����
 bit[7]      ����
 bit[6:0]    RXģ���Զ�Tuning code����ֵ
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA22_UNION */
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
 bit[7]      Reserved
 bit[6]      ADC Pupģ���Ƶʱ����Pup������ɺ���Ƿ������ת�Ŀ���λ
             0������ת
             1��������ת
 bit[5]      ADC��OP3���뼶β�����ܼӴ�ߴ���ƣ�debug��
             0��Ĭ����Ŀ
             1������β��������Ŀ
 bit[4:3]    ADC��OP1 DC OffsetУ׼ʱ��Ƶ�ʿ���
             00��6.4MHz
             01��3.2MHz
             10��9.6MHz
             11��4.8MHz
 bit[2]      ADC��OP1 DC OffsetУ׼ϵͳ��������
             0��������ϵͳ���
             1������ϵͳ���
 bit[1]      ADC��OP1 DC OffsetУ׼ʹ���ź�
             0����ʹ��У׼
             1��ʹ��У׼
 bit[0]      ADC��OP1 DC OffsetУ׼��ƫ�õ���ѡ��
             0��5uA��Ĭ��У׼��Χ
             1��10uA��У׼��Χ�ӱ�

   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA25_UNION */
#define ABB_CH1_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0x99)

/* �Ĵ���˵����ģ����ԼĴ�����
 bit[7:5]    ADC������1���ݿ����룬ΪFF Corner׼���Ķ��ⲹ����
 bit[4:2]    ADC������2���ݿ����룬ΪFF Corner׼���Ķ��ⲹ����
 bit[1:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA26_UNION */
#define ABB_CH1_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0x9A)

/* �Ĵ���˵����ģ�����ֻ���Ĵ�����
 bit[7]      RXA Iͨ��OP1 OffsetУ���Ƿ������־λ
             0��δ���
             1��У׼���
 bit[6]      RXA Qͨ��OP1 OffsetУ���Ƿ������־λ
             0��δ���
             1��У׼���
 bit[5:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ARO0_UNION */
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

/* �Ĵ���˵����CFR��ֵ��ⴰ���Ĵ�����
 bit[7:4]    CFR�������ӣ�V8R1���漰��
 bit[3]      ����
 bit[2]      CFR�˲���ѡ��
             0��bypass�˲���
             1����bypass�˲���
             ��V8R1���漰��
 bit[1:0]    CFR��ֵ��ⷽʽ��
             00���������
             01���������
             10���������
             11��ȫ����ֵ
             ��V8R1���漰��
   UNION�ṹ:  ABB_CH0_CFR_CTRL_UNION */
#define ABB_CH0_CFR_CTRL_ADDR                         (ABB_BASE_ADDR + 0xA3)

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
 bit[6]      TXͨ��������ѡ��comstarV520 Reserved
             0��5�׵�����(for V510)
             1��1�׵�����(for V511)
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
 bit[7:4]    Reserved
 bit[3]      WPLL Power Down����
             0��Power On(Ĭ��)
             1��Power Down
 bit[2]      GPLL Power Down����
             0��Power On
             1��Power Down(Ĭ��)
 bit[1:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR02_UNION */
#define ABB_CH0_REG_ANALOG_WR02_ADDR                  (ABB_BASE_ADDR + 0xD0)

/* �Ĵ���˵������ģ�ӿ�ʱ�ӿ��ƼĴ�����
 bit[7]      Reserved
 bit[6]      CLK_122M Power Down����
             0��Power On(Ĭ��)
             1��Power Down
 bit[5]      CLK_104M Power Down����
             0��Power On(Ĭ��)
             1��Power Down
 bit[4]      LDO BYPASS
             0����������
             1��BYPASS
 bit[3]      ����
 bit[2]      ����
 bit[1:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR03_UNION */
#define ABB_CH0_REG_ANALOG_WR03_ADDR                  (ABB_BASE_ADDR + 0xD1)

/* �Ĵ���˵����Other���ƼĴ�����
 bit[7:4]    Reserved
 bit[3]      RX ADC�Զ�tuning����
             0���ֶ�tuning��tuningѡ��RX_TUNE1,RX_TUNE2,RX_TUNE3��ֵ(Ĭ��)
             1���Զ�tuning��RXͨ����calibrationֵΪCAL_VALUE
 bit[2]      TX ADC�Զ�tuning����
             0���ֶ�tuning��tuningѡ��TX_TUNE1,TX_TUNE2,TX_TUNE3��ֵ(Ĭ��)
             1���Զ�tuning��TXͨ����calibrationֵΪCAL_VALUE
 bit[1]      Reserved
 bit[0]      RC TUNE����
             ����������RC У׼����
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR04_UNION */
#define ABB_CH0_REG_ANALOG_WR04_ADDR                  (ABB_BASE_ADDR + 0xD2)

/* �Ĵ���˵����ADC��һ������������tuning�Ĵ�����
 bit[7]      Reserved
 bit[6:0]    ADC��һ������������tuning
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR05_UNION */
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
 bit[7]      Reserved
 bit[6:0]    TX_TUNE1�����ź�
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR08_UNION */
#define ABB_CH0_REG_ANALOG_WR08_ADDR                  (ABB_BASE_ADDR + 0xD6)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
 bit[7]      Reserved
 bit[6:0]    TX_TUNE2�����ź�
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR09_UNION */
#define ABB_CH0_REG_ANALOG_WR09_ADDR                  (ABB_BASE_ADDR + 0xD7)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
 bit[7]      Reserved
 bit[6:0]    TX_TUNE3�����ź�
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR10_UNION */
#define ABB_CH0_REG_ANALOG_WR10_ADDR                  (ABB_BASE_ADDR + 0xD8)

/* �Ĵ���˵����ʱ�ӷ��ؿ��ƼĴ�����
 bit[7]      Reserved
 bit[6]      ADC SYNC�źŲ����ؿ��ƣ�
             0������(Ĭ��)
             1������
 bit[5]      ADC�����ؿ��ƣ�
             0������(Ĭ��)
             1������
 bit[4:2]    Reserved
 bit[1]      Reserved
 bit[0]      ADC������У׼ʹ�ܣ�
             0��Not Cal(Ĭ��)
             1��Cal
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR38_UNION */
#define ABB_CH0_REG_ANALOG_WR38_ADDR                  (ABB_BASE_ADDR + 0xD9)

/* �Ĵ���˵����DUM���ƼĴ�����
 bit[7]      RX DEM Mode Selection,bit 2,��ch0_reg_analog_wr00��bit3��bit0��ϳ�3bit��ʵ������9����ϣ�
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
 bit[6:2]    Reserved
 bit[1]      Reserved
 bit[0]      Reserved
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR39_UNION */
#define ABB_CH0_REG_ANALOG_WR39_ADDR                  (ABB_BASE_ADDR + 0xDA)

/* �Ĵ���˵������־λֻ���Ĵ�����
 bit[7]      WPLL��LOCK�ź�
 bit[6]      GPLL��LOCK�ź�
 bit[5]      RC Calibration Done�ź�
 bit[4:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_ANALOG_RO0_UNION */
#define ABB_CH0_REG_ANALOG_RO0_ADDR                   (ABB_BASE_ADDR + 0xDB)

/* �Ĵ���˵����RCУ׼ֻ���Ĵ�����
 bit[7]      Reserved
 bit[6:0]    RC CalibrationУ׼ֵ
   UNION�ṹ:  ABB_CH0_REG_ANALOG_RO1_UNION */
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
 bit[7:6]    GPLL VCO Current����
             00��X1.2
             01��X1.1(Ĭ��)
             10��X1.1
             11��X1.0
 bit[5]      PLL��Ƶ����������
             0����Ƶ��������������
             1����Ƶ������һֱ���UP�ź�
 bit[4]      PLL��Ƶ����������
             0����Ƶ��������������
             1����Ƶ������һֱ���Down�ź�
 bit[3:1]    ����ʱ��ѡ��
             000: PLL ����� CLK��
             001��ѡ��������PLL��ʱ����Ϊ����ʱ��
             010��ѡ��������CLKIN_SYSTEM�����ʱ����Ϊ����ʱ��
             100��ѡ��������TCXO_IN��ʱ����Ϊ����ʱ��
 bit[0]      PLL�Ĳο�ʱ��ѡ��
             1��TCXO_INP��ΪPLL�Ĳο�ʱ��
             0��TCXO Buffer�����ΪPLL�ο�ʱ��
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA0_UNION */
#define ABB_CH0_REG_DEBUG_ANA0_ADDR                   (ABB_BASE_ADDR + 0xE0)

/* �Ĵ���˵����PLL LOCK���ƼĴ�����
 bit[7:6]    WPLL VCO Current����
             00��X0.7
             01��X1(Ĭ��)
             10��X1
             11��X1.3
 bit[5]      WPLL�������ʹ��
             0�����������ź�
             1���������ź�
 bit[4]      GPLL�������ʹ��
             0�����������ź�
             1���������ź�
 bit[3:2]    WPLL����Cycle����
             00��4
             01��8
             10��16(Ĭ��)
             11��32
 bit[1:0]    GPLL����Cycle����
             00��4
             01��8
             10��16(Ĭ��)
             11��32
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA1_UNION */
#define ABB_CH0_REG_DEBUG_ANA1_ADDR                   (ABB_BASE_ADDR + 0xE1)

/* �Ĵ���˵����PLL���ƼĴ�����
 bit[7]      ����ʱ�ӿ���
             1������ʱ�Ӵ�
             0������ʱ�ӹر�
 bit[6:2]    Reserved
 bit[1]      WPLL CP PowerDown���ƣ�������
             0����������
             1��PowerDown WPLL CP
 bit[0]      GPLL CP PowerDown���ƣ�������
             0����������
             1��PowerDown GPLL CP
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA2_UNION */
#define ABB_CH0_REG_DEBUG_ANA2_ADDR                   (ABB_BASE_ADDR + 0xE2)

/* �Ĵ���˵����PLL���ƼĴ�����
 bit[7:4]    GPLL��ɱõ�������(����Ч)
             0000��4u
             0001��6u
             0010��8u
             0011��10u(Ĭ��)
             0100��12u
             0101��14u
             0110��16u
             0111��18u
             ����
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA3_UNION */
#define ABB_CH0_REG_DEBUG_ANA3_ADDR                   (ABB_BASE_ADDR + 0xE3)

/* �Ĵ���˵����PLL���ƼĴ�����
 bit[7:4]    WPLL��ɱõ�������(����Ч)
             0000��4u
             0001��6u
             0010��8u
             0011��10u(Ĭ��)
             0100��12u
             0101��14u
             0110��16u
             0111��18u
             ����
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA4_UNION */
#define ABB_CH0_REG_DEBUG_ANA4_ADDR                   (ABB_BASE_ADDR + 0xE4)

/* �Ĵ���˵���������������ƼĴ�����
 bit[7]      ABB_REF_Fast_UP����
             0���ر�(Ĭ��)
             1������
 bit[6:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA5_UNION */
#define ABB_CH0_REG_DEBUG_ANA5_ADDR                   (ABB_BASE_ADDR + 0xE5)

/* �Ĵ���˵����Bandgap��TCXO���ƼĴ�����
 bit[7]      reserved
 bit[6]      TEST EX_CLK INPUT PD����
             0������
             1���ر�
 bit[5:4]    TCXO BUFFER��������
             00��1x
             01��2x
             10��3x(Ĭ��)
             11��4x
 bit[3:2]    WPLL����ʱ��Ƶ��ѡ��
             00��38.4M
             01��76.8M
             10��19.2M(Ĭ��)
             11��38.4M
 bit[1:0]    GPLL����ʱ��Ƶ��ѡ��
             00��19.2M(Ĭ��)
             01��26M
             10��38.4M
             11��52M
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA6_UNION */
#define ABB_CH0_REG_DEBUG_ANA6_ADDR                   (ABB_BASE_ADDR + 0xE6)

/* �Ĵ���˵�����������ƼĴ�����
 bit[7:6]    reserved
 bit[5:3]    L/W/G ����ADC ���buffer�������ڿ���
             000��5u
             001��4u
             010��3u
             011��2u
             100��9u
             101��8u
             110��7u
             111��6u

 bit[2:0]    L/W/G ����ADC ���buffer�������ڿ���
             000��5u
             001��4u
             010��3u
             011��2u
             100��9u
             101��8u
             110��7u
             111��6u

   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA7_UNION */
#define ABB_CH0_REG_DEBUG_ANA7_ADDR                   (ABB_BASE_ADDR + 0xE7)

/* �Ĵ���˵�����������ƼĴ�����
 bit[7:5]    Reserved
 bit[4:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA8_UNION */
#define ABB_CH0_REG_DEBUG_ANA8_ADDR                   (ABB_BASE_ADDR + 0xE8)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7:5]    Reserved
 bit[4]      ADCģ��Tuning���ѡ��
             0��ѡ��Tuningģ��������ΪLTE ADC��Tuning��
             1��ѡ��Ĵ����������ΪLTE ADC��Tuning��
 bit[3]      ADC DEM���ܹر��ź�
             0��DEMʹ��
             1��DEM��ʹ��
 bit[2]      Reserved
 bit[1]      LTE ADCģ������ģʽѡ��
             0���Զ�ģʽ
             1�����üĴ���ģʽ
 bit[0]      Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA9_UNION */
#define ABB_CH0_REG_DEBUG_ANA9_ADDR                   (ABB_BASE_ADDR + 0xE9)

/* �Ĵ���˵����ADC��λ���ƼĴ�����
 bit[7]      ADC��RST_CAP����
             0��Reset CAP123
             1����Reset CAP123
 bit[6]      ADC��OP1ģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[5]      ADC��OP1 OffsetУ׼������̽ӿ��ؿ���
             0������̽ӿ��ضϿ�����������ģʽ��
             1������̽ӿ��رպϣ����˷�����˶̽ӵ���ģ��ѹ��
 bit[4]      ADC��QUģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[3]      ADC��CKGEN_QUģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[2]      ADC��OP1 OffsetУ׼�����ź�
             0��У׼������
             1������OP1 OffsetУ׼
 bit[1]      ADC��OP23ģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[0]      ADC��DACģ��Powerup����
             0��Powerdown
             1��Powerup
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA10_UNION */
#define ABB_CH0_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0xEA)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7]      Refence��ѹģ��ǿ��PD�ź�
             0�� Reference��ѹģ��״̬��BG_EN�źż�����ģ��PD�ź��Զ�����
             1�� Reference��ѹģ��ǿ��Power Down
 bit[6]      Refence��ѹģ��ǿ��EN�ź�
             0�� Reference��ѹģ��״̬��BG_PD�źż�����ģ��PD�ź��Զ�����
             1�� ��BG_PD�ź�Ϊ0ʱ��Reference��ѹģ��ǿ������
 bit[5:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA11_UNION */
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
 bit[7:6]    Reserved
 bit[5:3]    Reserved
 bit[2:0]    ADC Overloadģ������
             00��16����������������С��
             01��8����������������С��
             10��4����������������С��
             11���ر�Overload���
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA14_UNION */
#define ABB_CH0_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0xEE)

/* �Ĵ���˵����ADC�ӳٿ��ƼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0xEF)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7]      RX���PDM�������
             0��adder encoder���ӷ��������
             1��de-bubble encoder���������������
 bit[6]      Reserved
 bit[5:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA16_UNION */
#define ABB_CH0_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xF0)

/* �Ĵ���˵����PLL���ԼĴ�����
 bit[7:6]    PLL���Ƶ�ѹ����PAD�ź�ѡ��
             00/11�����Ƶ�ѹ����PAD����
             01��GPLL������Ƶ�ѹ��PAD
             10��WPLL������Ƶ�ѹ��PAD
 bit[5:4]    PLLʱ�Ӳ���PAD�ź�ѡ��
             00/11��ʱ�Ӳ���PAD����
             01��GPLL���ʱ�ӵ�PAD
             10��WPLL���ʱ�ӵ�PAD
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA17_UNION */
#define ABB_CH0_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xF1)

/* �Ĵ���˵����TX�ֹ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xF2)

/* �Ĵ���˵����ʱ��ʹ�ܿ��ƼĴ�����
 bit[7:6]    Reserved
 bit[5]      PLLģ��307.2MHzʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[4]      PLLģ��312MHzʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[3:2]    Reserved
 bit[1]      WPLL���Թܽ����ʱ��Ƶ�ʿ���
             0��������ʱ��
             1���������
 bit[0]      Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA19_UNION */
#define ABB_CH0_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xF3)

/* �Ĵ���˵����ģ����ԼĴ�����
 bit[7]      Reserved
 bit[6:5]    ADC���������ݱ���ϵ��
             00��X1(Ĭ��)
             01��X1.5
             10��X1.25
             11��X1.125
 bit[4:3]    Reserved
 bit[2]      ����
 bit[1]      ����
 bit[0]      ����
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA20_UNION */
#define ABB_CH0_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xF4)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xF5)

/* �Ĵ���˵����ģ����ԼĴ�����
 bit[7]      ����
 bit[6:0]    RXģ���Զ�Tuning code����ֵ
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA22_UNION */
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
 bit[7]      Reserved
 bit[6]      ADC Pupģ���Ƶʱ����Pup������ɺ���Ƿ������ת�Ŀ���λ
             0������ת
             1��������ת
 bit[5]      ADC��OP3���뼶β�����ܼӴ�ߴ���ƣ�debug��
             0��Ĭ����Ŀ
             1������β��������Ŀ
 bit[4:3]    ADC��OP1 DC OffsetУ׼ʱ��Ƶ�ʿ���
             00��6.4MHz
             01��3.2MHz
             10��9.6MHz
             11��4.8MHz
 bit[2]      ADC��OP1 DC OffsetУ׼ϵͳ��������
             0��������ϵͳ���
             1������ϵͳ���
 bit[1]      ADC��OP1 DC OffsetУ׼ʹ���ź�
             0����ʹ��У׼
             1��ʹ��У׼
 bit[0]      ADC��OP1 DC OffsetУ׼��ƫ�õ���ѡ��
             0��5uA��Ĭ��У׼��Χ
             1��10uA��У׼��Χ�ӱ�

   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA25_UNION */
#define ABB_CH0_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xF9)

/* �Ĵ���˵����ģ����ԼĴ�����
 bit[7:5]    ADC������1���ݿ����룬ΪFF Corner׼���Ķ��ⲹ����
 bit[4:2]    ADC������2���ݿ����룬ΪFF Corner׼���Ķ��ⲹ����
 bit[1:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA26_UNION */
#define ABB_CH0_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xFA)

/* �Ĵ���˵����ģ�����ֻ���Ĵ�����
 bit[7]      RXA Iͨ��OP1 OffsetУ���Ƿ������־λ
             0��δ���
             1��У׼���
 bit[6]      RXA Qͨ��OP1 OffsetУ���Ƿ������־λ
             0��δ���
             1��У׼���
 bit[5]      RXB Iͨ��OP1 OffsetУ���Ƿ������־λ
             0��δ���
             1��У׼���
 bit[4]      RXB Qͨ��OP1 OffsetУ���Ƿ������־λ
             0��δ���
             1��У׼���
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ARO0_UNION */
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
 bit[7]      TX ����ʱ����ѡ��
             0������(Ĭ��)
             1������
 bit[6:5]    ����
 bit[4]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable


 bit[3]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable
 bit[2:0]    LPF OP ����ģʽ����
             000��5u
             001��4u
             010��3u
             011��2u
             100��9u
             101��8u
             110��7u
             111��6u
   UNION�ṹ:  ABB_TX_2G_ANA_3_UNION */
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
 bit[7:6]    ����
 bit[5:3]    RX ADC OP3��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC OP1��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_2G_ANA_3_UNION */
#define ABB_RX_2G_ANA_3_ADDR                          (ABB_BASE_ADDR + 0x103)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr54��
 bit[7:6]    ����
 bit[5:3]    RX ADC ����DAC�˷ŵ�������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC QT��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_2G_ANA_4_UNION */
#define ABB_RX_2G_ANA_4_ADDR                          (ABB_BASE_ADDR + 0x104)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr55��
 bit[7:5]    ����
 bit[4:3]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[2:0]    RX ADC OP2��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_2G_ANA_5_UNION */
#define ABB_RX_2G_ANA_5_ADDR                          (ABB_BASE_ADDR + 0x105)

/* �Ĵ���˵����CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr50��
 bit[7]      TX ����ʱ����ѡ��
             0������(Ĭ��)
             1������
 bit[6:5]    ����
 bit[4]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable


 bit[3]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable
 bit[2:0]    LPF OP����ģʽ����
             000��5u
             001��4u
             010��3u
             011��2u
             100��9u
             101��8u
             110��7u
             111��6u
   UNION�ṹ:  ABB_TX_CH0_3G_ANA_3_UNION */
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
 bit[7:6]    ����
 bit[5:3]    RX ADC OP3��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC OP1��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_CH0_3G_ANA_3_UNION */
#define ABB_RX_CH0_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x109)

/* �Ĵ���˵����CH0 RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr54��
 bit[7:6]    ����
 bit[5:3]    RX ADC ����DAC�˷ŵ�������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC QT��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_CH0_3G_ANA_4_UNION */
#define ABB_RX_CH0_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x10A)

/* �Ĵ���˵����CH0 RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr55��
 bit[7:5]    ����
 bit[4:3]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[2:0]    RX ADC OP2��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_CH0_3G_ANA_5_UNION */
#define ABB_RX_CH0_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x10B)

/* �Ĵ���˵����CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr50��
 bit[7]      TX ����ʱ����ѡ��
             0������(Ĭ��)
             1������
 bit[6:5]    ����
 bit[4]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable


 bit[3]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable
 bit[2:0]    LPF OP����ģʽ����
             000��5u
             001��4u
             010��3u
             011��2u
             100��9u
             101��8u
             110��7u
             111��6u
   UNION�ṹ:  ABB_TX_CH0_4G_ANA_3_UNION */
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
 bit[7:6]    ����
 bit[5:3]    RX ADC OP3��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC OP1��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_CH0_4G_ANA_3_UNION */
#define ABB_RX_CH0_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x10F)

/* �Ĵ���˵����CH0 RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr54��
 bit[7:6]    ����
 bit[5:3]    RX ADC ����DAC�˷ŵ�������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC QT��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_CH0_4G_ANA_4_UNION */
#define ABB_RX_CH0_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x110)

/* �Ĵ���˵����CH0 RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr55��
 bit[7:5]    ����
 bit[4:3]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[2:0]    RX ADC OP2��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_CH0_4G_ANA_5_UNION */
#define ABB_RX_CH0_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x111)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������reg_analog_wr50��
 bit[7]      TX ����ʱ����ѡ��
             0������(Ĭ��)
             1������
 bit[6:5]    ����
 bit[4]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable


 bit[3]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable
 bit[2:0]    LPF OP����ģʽ����
             000��5u
             001��4u
             010��3u
             011��2u
             100��9u
             101��8u
             110��7u
             111��6u
   UNION�ṹ:  ABB_TX_TDS_ANA_3_UNION */
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
 bit[7:6]    ����
 bit[5:3]    RX ADC OP3��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC OP1��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_TDS_ANA_3_UNION */
#define ABB_RX_TDS_ANA_3_ADDR                         (ABB_BASE_ADDR + 0x115)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr54��
 bit[7:6]    ����
 bit[5:3]    RX ADC ����DAC�˷ŵ�������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC QT��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_TDS_ANA_4_UNION */
#define ABB_RX_TDS_ANA_4_ADDR                         (ABB_BASE_ADDR + 0x116)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr55��
 bit[7:5]    ����
 bit[4:3]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[2:0]    RX ADC OP2��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_TDS_ANA_5_UNION */
#define ABB_RX_TDS_ANA_5_ADDR                         (ABB_BASE_ADDR + 0x117)

/* �Ĵ���˵����CH1 TX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr50��
 bit[7]      TX ����ʱ����ѡ��
             0������(Ĭ��)
             1������
 bit[6:5]    ����
 bit[4]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable


 bit[3]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable
 bit[2:0]    LPF OP����ģʽ����
             000��5u
             001��4u
             010��3u
             011��2u
             100��9u
             101��8u
             110��7u
             111��6u
   UNION�ṹ:  ABB_TX_CH1_4G_ANA_3_UNION */
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
 bit[7:6]    ����
 bit[5:3]    RX ADC OP3��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC OP1��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_CH1_4G_ANA_3_UNION */
#define ABB_RX_CH1_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x11B)

/* �Ĵ���˵����CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr54��
 bit[7:6]    ����
 bit[5:3]    RX ADC ����DAC�˷ŵ�������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC QT��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_CH1_4G_ANA_4_UNION */
#define ABB_RX_CH1_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x11C)

/* �Ĵ���˵����CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr55��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH1_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x11D)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr50��
 bit[7]      TX ����ʱ����ѡ��
             0������(Ĭ��)
             1������
 bit[6:5]    ����
 bit[4]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable


 bit[3]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable
 bit[2:0]    LPF OP1 ����ģʽ����
             000��5u
             001��4u
             010��3u
             011��2u
             100��9u
             101��8u
             110��7u
             111��6u
   UNION�ṹ:  ABB_TX_IDLE_ANA_3_UNION */
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
 bit[7:6]    ����
 bit[5:3]    RX ADC OP3��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC OP1��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_IDLE_ANA_3_UNION */
#define ABB_RX_IDLE_ANA_3_ADDR                        (ABB_BASE_ADDR + 0x12D)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr54��
 bit[7:6]    ����
 bit[5:3]    RX ADC ����DAC�˷ŵ�������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC QT��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_IDLE_ANA_4_UNION */
#define ABB_RX_IDLE_ANA_4_ADDR                        (ABB_BASE_ADDR + 0x12E)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr55��
 bit[7:5]    ����
 bit[4:3]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[2:0]    RX ADC OP2��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_IDLE_ANA_5_UNION */
#define ABB_RX_IDLE_ANA_5_ADDR                        (ABB_BASE_ADDR + 0x12F)

/* �Ĵ���˵����ģ����ԼĴ�����
 bit[7]      Reserved
 bit[6:4]    Reserved
             ComstarV511_Reserved
 bit[3:2]    Reserved
             ComstarV511_Reserved
 bit[1:0]    Reserved
             ComstarV511_Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA27_UNION */
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
 bit[7]      Reserved
 bit[6:4]    TBD
 bit[3:2]    TBD
 bit[1:0]    TBD
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA27_UNION */
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
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
             ��V8R1���漰��
   UNION�ṹ:  ABB_TX_CH1_3G_DIG_3_UNION */
#define ABB_TX_CH1_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x184)

/* �Ĵ���˵����CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      RX DEM Mode Selection,bit 1
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G
             010��3G_DC &amp; TDS
             011��2G(Ĭ��)
             100��reserved
             101��CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
   UNION�ṹ:  ABB_RX_CH1_3G_ANA_1_UNION */
#define ABB_RX_CH1_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x185)

/* �Ĵ���˵����CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr01��
 bit[7:6]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[1]      ����
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_CH1_3G_ANA_2_UNION */
#define ABB_RX_CH1_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x186)

/* �Ĵ���˵����CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr53��
 bit[7:6]    ����
 bit[5:3]    RX ADC OP3��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC OP1��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_CH1_3G_ANA_3_UNION */
#define ABB_RX_CH1_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x187)

/* �Ĵ���˵����CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr54��
 bit[7:6]    ����
 bit[5:3]    RX ADC ����DAC�˷ŵ�������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC QT��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_CH1_3G_ANA_4_UNION */
#define ABB_RX_CH1_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x188)

/* �Ĵ���˵����CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr55��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_RX_CH1_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x189)

/* �Ĵ���˵����CH1 TX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr48��
 bit[7:6]    TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
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
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��8��Ƶ
             11��4��Ƶ
 bit[3]      TX_I DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G &amp; TDS
             010��reserved
             011��2G(Ĭ��)
             1xx��CDMA
   UNION�ṹ:  ABB_TX_CH1_3G_ANA_1_UNION */
#define ABB_TX_CH1_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x18A)

/* �Ĵ���˵����CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_3G��˵����
 bit[5:4]    LPF �˷�ƫ�õ�������
             00��   10u
             01��    5u
             10��    5u
             11��    3u
             Ĭ�����÷�����
             LTE:00   GSM:11   Others:01
 bit[3:2]    ����
 bit[1:0]    LPF OP����ģʽ����
             00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
             01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
             10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
             11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

             Ĭ�����÷�����
             LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11
   UNION�ṹ:  ABB_TX_CH1_3G_ANA_2_UNION */
#define ABB_TX_CH1_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x18B)

/* �Ĵ���˵����CH1 TX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr50��
 bit[7]      TX ����ʱ����ѡ��
             0������(Ĭ��)
             1������
 bit[6:5]    ����
 bit[4]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable


 bit[3]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable
 bit[2:0]    LPF OP1 ����ģʽ����
             000��5u
             001��4u
             010��3u
             011��2u
             100��9u
             101��8u
             110��7u
             111��6u
   UNION�ṹ:  ABB_TX_CH1_3G_ANA_3_UNION */
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
 bit[7:6]    BWCT_OP1 OP1�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[5:4]    BWCT_OP2 OP2�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[3:2]    BWCT_OP3 OP3�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[1:0]    ����
   UNION�ṹ:  ABB_RX_2G_ANA_6_UNION */
#define ABB_RX_2G_ANA_6_ADDR                          (ABB_BASE_ADDR + 0x18F)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr57��
 bit[7]      ������DACƫ�õ�������
             0 ��������������ܺ�
             1 С�������������ܲ�
 bit[6]      ������DAC������ȿ���
             0 �������0.5
             1 �������0.75
 bit[5]      OP3�Ƿ�ʹ��Gm_biasƫ��
             0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
             1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ��
 bit[4]      �������ο���ѹѡ��
             0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
             1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ
 bit[3:0]    ����
   UNION�ṹ:  ABB_RX_2G_ANA_7_UNION */
#define ABB_RX_2G_ANA_7_ADDR                          (ABB_BASE_ADDR + 0x190)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      ����
 bit[6:5]    CK_CTRL_MODE
             00�� LTEģʽ
             01�� WDC &amp; X &amp; TDS_Aģʽ
             1x�� W &amp; G &amp; TDS_Bģʽ
 bit[4:0]    CK_CTRL_DATA
             00000 ����DACʱ����ǰ������
             11111 ����DACʱ����ǰ�����
   UNION�ṹ:  ABB_RX_2G_ANA_8_UNION */
#define ABB_RX_2G_ANA_8_ADDR                          (ABB_BASE_ADDR + 0x191)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr59��
 bit[7:6]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
 bit[5:1]    ����
 bit[0]      AD&amp;DA��WPLL��SCPLLѡ���źš�
             0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
             1��ѡ��WPLL����3g��xĬ��ѡ��WPLL��
   UNION�ṹ:  ABB_RX_2G_ANA_9_UNION */
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
 bit[7:6]    BWCT_OP1 OP1�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[5:4]    BWCT_OP2 OP2�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[3:2]    BWCT_OP3 OP3�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[1:0]    ����
   UNION�ṹ:  ABB_RX_CH0_3G_ANA_6_UNION */
#define ABB_RX_CH0_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0x195)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr57��
 bit[7]      ������DACƫ�õ�������
             0 ��������������ܺ�
             1 С�������������ܲ�
 bit[6]      ������DAC������ȿ���
             0 �������0.5
             1 �������0.75
 bit[5]      OP3�Ƿ�ʹ��Gm_biasƫ��
             0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
             1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ��
 bit[4]      �������ο���ѹѡ��
             0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
             1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ
 bit[3:0]    ����
   UNION�ṹ:  ABB_RX_CH0_3G_ANA_7_UNION */
#define ABB_RX_CH0_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0x196)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      ����
 bit[6:5]    CK_CTRL_MODE
             00�� LTEģʽ
             01�� WDC &amp; X &amp; TDS_Aģʽ
             1x�� W &amp; G &amp; TDS_Bģʽ
 bit[4:0]    CK_CTRL_DATA
             00000 ����DACʱ����ǰ������
             11111 ����DACʱ����ǰ�����
   UNION�ṹ:  ABB_RX_CH0_3G_ANA_8_UNION */
#define ABB_RX_CH0_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0x197)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr59��
 bit[7:6]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
 bit[5:1]    ����
 bit[0]      AD&amp;DA��WPLL��SCPLLѡ���źš�
             0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
             1��ѡ��WPLL����3g��xĬ��ѡ��WPLL��
   UNION�ṹ:  ABB_RX_CH0_3G_ANA_9_UNION */
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
 bit[7:6]    BWCT_OP1 OP1�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[5:4]    BWCT_OP2 OP2�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[3:2]    BWCT_OP3 OP3�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[1:0]    ����
   UNION�ṹ:  ABB_RX_CH0_4G_ANA_6_UNION */
#define ABB_RX_CH0_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0x19B)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr57��
 bit[7]      ������DACƫ�õ�������
             0 ��������������ܺ�
             1 С�������������ܲ�
 bit[6]      ������DAC������ȿ���
             0 �������0.5
             1 �������0.75
 bit[5]      OP3�Ƿ�ʹ��Gm_biasƫ��
             0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
             1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ��
 bit[4]      �������ο���ѹѡ��
             0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
             1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ
 bit[3:0]    ����
   UNION�ṹ:  ABB_RX_CH0_4G_ANA_7_UNION */
#define ABB_RX_CH0_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0x19C)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      ����
 bit[6:5]    CK_CTRL_MODE
             00�� LTEģʽ
             01�� WDC &amp; X &amp; TDS_Aģʽ
             1x�� W &amp; G &amp; TDS_Bģʽ
 bit[4:0]    CK_CTRL_DATA
             00000 ����DACʱ����ǰ������
             11111 ����DACʱ����ǰ�����
   UNION�ṹ:  ABB_RX_CH0_4G_ANA_8_UNION */
#define ABB_RX_CH0_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0x19D)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr59��
 bit[7:6]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
 bit[5:1]    ����
 bit[0]      AD&amp;DA��WPLL��SCPLLѡ���źš�
             0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
             1��ѡ��WPLL����3g��xĬ��ѡ��WPLL��
   UNION�ṹ:  ABB_RX_CH0_4G_ANA_9_UNION */
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
 bit[7:6]    BWCT_OP1 OP1�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[5:4]    BWCT_OP2 OP2�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[3:2]    BWCT_OP3 OP3�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[1:0]    ����
   UNION�ṹ:  ABB_RX_TDS_ANA_6_UNION */
#define ABB_RX_TDS_ANA_6_ADDR                         (ABB_BASE_ADDR + 0x1A1)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr57��
 bit[7]      ������DACƫ�õ�������
             0 ��������������ܺ�
             1 С�������������ܲ�
 bit[6]      ������DAC������ȿ���
             0 �������0.5
             1 �������0.75
 bit[5]      OP3�Ƿ�ʹ��Gm_biasƫ��
             0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
             1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ��
 bit[4]      �������ο���ѹѡ��
             0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
             1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ
 bit[3:0]    ����
   UNION�ṹ:  ABB_RX_TDS_ANA_7_UNION */
#define ABB_RX_TDS_ANA_7_ADDR                         (ABB_BASE_ADDR + 0x1A2)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      ����
 bit[6:5]    CK_CTRL_MODE
             00�� LTEģʽ
             01�� WDC &amp; X &amp; TDS_Aģʽ
             1x�� W &amp; G &amp; TDS_Bģʽ
 bit[4:0]    CK_CTRL_DATA
             00000 ����DACʱ����ǰ������
             11111 ����DACʱ����ǰ�����
   UNION�ṹ:  ABB_RX_TDS_ANA_8_UNION */
#define ABB_RX_TDS_ANA_8_ADDR                         (ABB_BASE_ADDR + 0x1A3)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr59��
 bit[7:6]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
 bit[5:1]    ����
 bit[0]      AD&amp;DA��WPLL��SCPLLѡ���źš�
             0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
             1��ѡ��WPLL����3g��xĬ��ѡ��WPLL��
   UNION�ṹ:  ABB_RX_TDS_ANA_9_UNION */
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
 bit[7:6]    BWCT_OP1 OP1�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[5:4]    BWCT_OP2 OP2�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[3:2]    BWCT_OP3 OP3�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[1:0]    ����
   UNION�ṹ:  ABB_RX_IDLE_ANA_6_UNION */
#define ABB_RX_IDLE_ANA_6_ADDR                        (ABB_BASE_ADDR + 0x1A7)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr57��
 bit[7]      ������DACƫ�õ�������
             0 ��������������ܺ�
             1 С�������������ܲ�
 bit[6]      ������DAC������ȿ���
             0 �������0.5
             1 �������0.75
 bit[5]      OP3�Ƿ�ʹ��Gm_biasƫ��
             0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
             1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ��
 bit[4]      �������ο���ѹѡ��
             0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
             1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ
 bit[3:0]    ����
   UNION�ṹ:  ABB_RX_IDLE_ANA_7_UNION */
#define ABB_RX_IDLE_ANA_7_ADDR                        (ABB_BASE_ADDR + 0x1A8)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      ����
 bit[6:5]    CK_CTRL_MODE
             00�� LTEģʽ
             01�� WDC &amp; X &amp; TDS_Aģʽ
             1x�� W &amp; G &amp; TDS_Bģʽ
 bit[4:0]    CK_CTRL_DATA
             00000 ����DACʱ����ǰ������
             11111 ����DACʱ����ǰ�����
   UNION�ṹ:  ABB_RX_IDLE_ANA_8_UNION */
#define ABB_RX_IDLE_ANA_8_ADDR                        (ABB_BASE_ADDR + 0x1A9)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr59��
 bit[7:6]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
 bit[5:1]    ����
 bit[0]      AD&amp;DA��WPLL��SCPLLѡ���źš�
             0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
             1��ѡ��WPLL����3g��xĬ��ѡ��WPLL��
   UNION�ṹ:  ABB_RX_IDLE_ANA_9_UNION */
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
 bit[7:6]    BWCT_OP1 OP1�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[5:4]    BWCT_OP2 OP2�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[3:2]    BWCT_OP3 OP3�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[1:0]    ����
   UNION�ṹ:  ABB_RX_CH1_3G_ANA_6_UNION */
#define ABB_RX_CH1_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0x1AD)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr57��
 bit[7]      ������DACƫ�õ�������
             0 ��������������ܺ�
             1 С�������������ܲ�
 bit[6]      ������DAC������ȿ���
             0 �������0.5
             1 �������0.75
 bit[5]      OP3�Ƿ�ʹ��Gm_biasƫ��
             0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
             1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ��
 bit[4]      �������ο���ѹѡ��
             0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
             1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ
 bit[3:0]    ����
   UNION�ṹ:  ABB_RX_CH1_3G_ANA_7_UNION */
#define ABB_RX_CH1_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0x1AE)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      ����
 bit[6:5]    CK_CTRL_MODE
             00�� LTEģʽ
             01�� WDC &amp; X &amp; TDS_Aģʽ
             1x�� W &amp; G &amp; TDS_Bģʽ
 bit[4:0]    CK_CTRL_DATA
             00000 ����DACʱ����ǰ������
             11111 ����DACʱ����ǰ�����
   UNION�ṹ:  ABB_RX_CH1_3G_ANA_8_UNION */
#define ABB_RX_CH1_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0x1AF)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr59��
 bit[7:6]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
 bit[5:1]    ����
 bit[0]      AD&amp;DA��WPLL��SCPLLѡ���źš�
             0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
             1��ѡ��WPLL����3g��xĬ��ѡ��WPLL��
   UNION�ṹ:  ABB_RX_CH1_3G_ANA_9_UNION */
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
 bit[7:6]    BWCT_OP1 OP1�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[5:4]    BWCT_OP2 OP2�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[3:2]    BWCT_OP3 OP3�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[1:0]    ����
   UNION�ṹ:  ABB_RX_CH1_4G_ANA_6_UNION */
#define ABB_RX_CH1_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0x1B4)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr57��
 bit[7]      ������DACƫ�õ�������
             0 ��������������ܺ�
             1 С�������������ܲ�
 bit[6]      ������DAC������ȿ���
             0 �������0.5
             1 �������0.75
 bit[5]      OP3�Ƿ�ʹ��Gm_biasƫ��
             0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
             1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ��
 bit[4]      �������ο���ѹѡ��
             0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
             1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ
 bit[3:0]    ����
   UNION�ṹ:  ABB_RX_CH1_4G_ANA_7_UNION */
#define ABB_RX_CH1_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0x1B5)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      ����
 bit[6:5]    CK_CTRL_MODE
             00�� LTEģʽ
             01�� WDC &amp; X &amp; TDS_Aģʽ
             1x�� W &amp; G &amp; TDS_Bģʽ
 bit[4:0]    CK_CTRL_DATA
             00000 ����DACʱ����ǰ������
             11111 ����DACʱ����ǰ�����
   UNION�ṹ:  ABB_RX_CH1_4G_ANA_8_UNION */
#define ABB_RX_CH1_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0x1B6)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr59��
 bit[7:6]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
 bit[5:1]    ����
 bit[0]      AD&amp;DA��WPLL��SCPLLѡ���źš�
             0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
             1��ѡ��WPLL����3g��xĬ��ѡ��WPLL��
   UNION�ṹ:  ABB_RX_CH1_4G_ANA_9_UNION */
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
 bit[7:3]    ����
 bit[2]      TXͨ���߿�ѡ��
             0��tie to 0
             1��from line ctrl
 bit[1]      RXBͨ���߿�ѡ��
             0��tie to 0
             1��from line ctrl
 bit[0]      RXAͨ���߿�ѡ��
             0��tie to 0
             1��from line ctrl
   UNION�ṹ:  ABB_CH1_LINE_SEL_UNION */
#define ABB_CH1_LINE_SEL_ADDR                         (ABB_BASE_ADDR + 0x1C0)

/* �Ĵ���˵�����߿�ǿ������ֵ��
 bit[7]      �߿��ź�CH1_CFR_ENǿ������ʹ�ܣ�V8R1���漰��
 bit[6]      �߿��ź�CH1_CFR_ENǿ������ֵ��V8R1���漰��
 bit[5]      �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ��
 bit[4]      �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ
 bit[3]      �߿��ź�CH1_LINE_CTRL_MODEǿ������ʹ��
 bit[2:0]    �߿��ź�CH1_LINE_CTRL_MODEǿ������ֵ
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
 bit[2]      CFR�Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
             ��V8R1���漰��
 bit[1]      ���ż���Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
             ��V8R1���漰��
 bit[0]      BLOCKING�Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
   UNION�ṹ:  ABB_CH1_CLK_SEL_UNION */
#define ABB_CH1_CLK_SEL_ADDR                          (ABB_BASE_ADDR + 0x1C2)

/* �Ĵ���˵�����߿�ǿ������ʹ�ܡ�
 bit[7:3]    ����
 bit[2]      TXͨ���߿�ѡ��
             0��tie to 0
             1��from line ctrl
 bit[1]      RXBͨ���߿�ѡ��
             0��tie to 0
             1��from line ctrl
 bit[0]      RXAͨ���߿�ѡ��
             0��tie to 0
             1��from line ctrl
   UNION�ṹ:  ABB_CH0_LINE_SEL_UNION */
#define ABB_CH0_LINE_SEL_ADDR                         (ABB_BASE_ADDR + 0x1D0)

/* �Ĵ���˵�����߿�ǿ������ֵ��
 bit[7]      �߿��ź�CH0_CFR_ENǿ������ʹ�ܣ�V8R1���漰��
 bit[6]      �߿��ź�CH0_CFR_ENǿ������ֵ��V8R1���漰��
 bit[5]      �߿��ź�CH0_RXA_BLK_EN, CH0_RXB_BLK_ENǿ������ʹ��
 bit[4]      �߿��ź�CH0_RXA_BLK_EN, CH0_RXB_BLK_ENǿ������ֵ
 bit[3]      �߿��ź�CH0_LINE_CTRL_MODEǿ������ʹ��
 bit[2:0]    �߿��ź�CH0_LINE_CTRL_MODEǿ������ֵ
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
 bit[2]      CFR�Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
             ��V8R1���漰��
 bit[1]      ���ż���Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
             ��V8R1���漰��
 bit[0]      BLOCKING�Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
   UNION�ṹ:  ABB_CH0_CLK_SEL_UNION */
#define ABB_CH0_CLK_SEL_ADDR                          (ABB_BASE_ADDR + 0x1D2)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7:3]    ����
 bit[2]      TX_EN�߿�״̬�ϱ�
 bit[1]      RXB_EN�߿�״̬�ϱ�
 bit[0]      RXA_EN�߿�״̬�ϱ�
   UNION�ṹ:  ABB_CH1_LINE_RPT0_UNION */
#define ABB_CH1_LINE_RPT0_ADDR                        (ABB_BASE_ADDR + 0x1E0)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7]      ����
 bit[6]      CFR_EN�߿�״̬�ϱ���V8R1���漰��
 bit[5]      RXB_BLK_EN�߿�״̬�ϱ�
 bit[4]      RXA_BLK_EN�߿�״̬�ϱ�
 bit[3]      ����
 bit[2:0]    �߿��ź�CH1_LINE_CTRL_MODE״̬�ϱ�
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��ETģʽ
             6��APTģʽ
             7��CAģʽ
   UNION�ṹ:  ABB_CH1_LINE_RPT1_UNION */
#define ABB_CH1_LINE_RPT1_ADDR                        (ABB_BASE_ADDR + 0x1E1)

/* �Ĵ���˵����RX���ֹ���ģʽ�ϱ��Ĵ�����
 bit[7:5]    RXͨ��ģʽ�����ϱ���
             000��2G(Ĭ��)
             001��3G_SC
             010��4G &amp; ET &amp; APT
             011��3G_DC
             100��TDS
             Others��CA
 bit[4:3]    RXͨ��CIC�˲���������ʿ����ϱ�(Hz)��
                 2G,   3G_SC,  4G,  3G_DC,   TDS,   CA
             00��2.167M,15.36M,61.44M,30.72M,30.72M,122.88M(Ĭ��)
             01��------,------,30.72M,15.36M,10.24M,------
             10��------,------,15.36M,------,------,------
             11��------,------, 7.68M,------,------,------
 bit[2]      RXͨ������˲���bypass�����ϱ���
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶������ϱ���
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      ����
   UNION�ṹ:  ABB_CH1_RX_MODE_RPT_UNION */
#define ABB_CH1_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1E2)

/* �Ĵ���˵����TX���ֹ���ģʽ�ϱ��Ĵ�����
 bit[7:5]    TXͨ��ģʽ�����ϱ���
             000��2G(Ĭ��)
             001��3G
             010��4G &amp; ET &amp; APT
             011��TDS
             Others��CA
 bit[4:2]    TXͨ��CIC�˲���������ʿ����ϱ���
                  2G,     3G,     4G,      TDS,      CA
                 (78M) (153.6M) (307.2M) (153.6M) (614.4M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2��-------,--------,15.36MHz,--------,--------
             3��-------,--------, 7.68MHz,--------,--------
             4��-------,--------, 3.84MHz,--------,--------
             Others��Reserved
 bit[1]      TXͨ������˲���bypass�����ϱ���
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��)
 bit[0]      TXͨ�������˲���bypass�����ϱ���
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_CH1_TX_MODE_RPT_UNION */
#define ABB_CH1_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1E3)

/* �Ĵ���˵����RX���ֹ���״̬�ϱ��Ĵ�����
 bit[7]      Reserved
 bit[6]      RXBͨ����������ָʾ�ź�
 bit[5]      RXBͨ��������ݷ�תָʾ�ź�
 bit[4]      RXAͨ����������ָʾ�ź�
 bit[3]      RXAͨ��������ݷ�תָʾ�ź�
 bit[2]      RXͨ�����������Чָʾ�ź�
 bit[1]      RXͨ�����������·ʱ��
 bit[0]      RXͨ��ģ����·ʱ��
   UNION�ṹ:  ABB_CH1_RX_STATE_RPT_UNION */
#define ABB_CH1_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1E4)

/* �Ĵ���˵����TX���ֹ���״̬�ϱ��Ĵ�����
 bit[7]      TXͨ��FIFO����״̬
 bit[6]      TXͨ��FIFOд��״̬
 bit[5]      TXͨ����������ָʾ�ź�
 bit[4]      TXͨ�����ݷ�תָʾ�ź�
 bit[3]      TXͨ������������ʱ��
 bit[2]      TXͨ����������Чָʾ�ź�
 bit[1]      TXͨ������������·ʱ��
 bit[0]      TXͨ��ģ����·ʱ��
   UNION�ṹ:  ABB_CH1_TX_STATE_RPT_UNION */
#define ABB_CH1_TX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1E5)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7:3]    ����
 bit[2]      TX_EN�߿�״̬�ϱ�
 bit[1]      RXB_EN�߿�״̬�ϱ�
 bit[0]      RXA_EN�߿�״̬�ϱ�
   UNION�ṹ:  ABB_CH0_LINE_RPT0_UNION */
#define ABB_CH0_LINE_RPT0_ADDR                        (ABB_BASE_ADDR + 0x1F0)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7]      ����
 bit[6]      CFR_EN�߿�״̬�ϱ���V8R1���漰��
 bit[5]      RXB_BLK_EN�߿�״̬�ϱ�
 bit[4]      RXA_BLK_EN�߿�״̬�ϱ�
 bit[3]      ����
 bit[2:0]    �߿��ź�ch0_LINE_CTRL_MODE״̬�ϱ�
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��ETģʽ
             6��APTģʽ
             7��CAģʽ
   UNION�ṹ:  ABB_CH0_LINE_RPT1_UNION */
#define ABB_CH0_LINE_RPT1_ADDR                        (ABB_BASE_ADDR + 0x1F1)

/* �Ĵ���˵����RX���ֹ���ģʽ�ϱ��Ĵ�����
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
 bit[2]      RXͨ������˲���bypass�����ϱ���
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶������ϱ���
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      RXͨ�������˲��������̶�ϵ��ѡ���ϱ���
             0���̶�ϵ��1
             1���̶�ϵ��2
   UNION�ṹ:  ABB_CH0_RX_MODE_RPT_UNION */
#define ABB_CH0_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1F2)

/* �Ĵ���˵����TX���ֹ���ģʽ�ϱ��Ĵ�����
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲���������ʿ����ϱ���
                  2G,     3G,     4G,      TDS,      CA
                 (78M) (153.6M) (307.2M) (153.6M) (614.4M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2��-------,--------,15.36MHz,--------,--------
             3��-------,--------, 7.68MHz,--------,--------
             4��-------,--------, 3.84MHz,--------,--------
             Others��Reserved
 bit[1]      TXͨ������˲���bypass�����ϱ���
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��)
 bit[0]      TXͨ�������˲���bypass�����ϱ���
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_CH0_TX_MODE_RPT_UNION */
#define ABB_CH0_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x1F3)

/* �Ĵ���˵����RX���ֹ���״̬�ϱ��Ĵ�����
 bit[7]      Reserved
 bit[6]      RXBͨ����������ָʾ�ź�
 bit[5]      RXBͨ��������ݷ�תָʾ�ź�
 bit[4]      RXAͨ����������ָʾ�ź�
 bit[3]      RXAͨ��������ݷ�תָʾ�ź�
 bit[2]      RXͨ�����������Чָʾ�ź�
 bit[1]      RXͨ�����������·ʱ��
 bit[0]      RXͨ��ģ����·ʱ��
   UNION�ṹ:  ABB_CH0_RX_STATE_RPT_UNION */
#define ABB_CH0_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x1F4)

/* �Ĵ���˵����TX���ֹ���״̬�ϱ��Ĵ�����
 bit[7]      TXͨ��FIFO����״̬
 bit[6]      TXͨ��FIFOд��״̬
 bit[5]      TXͨ����������ָʾ�ź�
 bit[4]      TXͨ�����ݷ�תָʾ�ź�
 bit[3]      TXͨ������������ʱ��
 bit[2]      TXͨ����������Чָʾ�ź�
 bit[1]      TXͨ������������·ʱ��
 bit[0]      TXͨ��ģ����·ʱ��
   UNION�ṹ:  ABB_CH0_TX_STATE_RPT_UNION */
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
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
             ��V8R1���漰��
   UNION�ṹ:  ABB_TX_C_DIG_3_UNION */
#define ABB_TX_C_DIG_3_ADDR                           (ABB_BASE_ADDR + 0x404)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      RX DEM Mode Selection,bit 1
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
 bit[2:1]    {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G
             010��3G_DC &amp; TDS
             011��2G(Ĭ��)
             100��reserved
             101��CDMA
 bit[0]      RX DEM Mode Selection,bit 0
             000��DWA
             001��CLA1
             010��CLA2
             011��CLA3
             100��CLA4
             101��CLA5
             110��CLA6
             111��CLA7
   UNION�ṹ:  ABB_RX_C_ANA_1_UNION */
#define ABB_RX_C_ANA_1_ADDR                           (ABB_BASE_ADDR + 0x405)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr01��
 bit[7:6]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[5:4]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[3:2]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[1]      ����
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_C_ANA_2_UNION */
#define ABB_RX_C_ANA_2_ADDR                           (ABB_BASE_ADDR + 0x406)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr53��
 bit[7:6]    ����
 bit[5:3]    RX ADC OP3��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC OP1��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_C_ANA_3_UNION */
#define ABB_RX_C_ANA_3_ADDR                           (ABB_BASE_ADDR + 0x407)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr54��
 bit[7:6]    ����
 bit[5:3]    RX ADC ����DAC�˷ŵ�������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
 bit[2:0]    RX ADC QT��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_C_ANA_4_UNION */
#define ABB_RX_C_ANA_4_ADDR                           (ABB_BASE_ADDR + 0x408)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr55��
 bit[7:5]    ����
 bit[4:3]    Current Seting For Mode
             1x��LTE mode Current
             01��3G_DC &amp; X mode Current
             00��3G &amp; 2G mode Current
 bit[2:0]    RX ADC OP2��������
             000�� 1.0x
             001�� 0.8x
             010�� 0.6x
             011�� 0.4x
             100�� 1.8x
             101�� 1.6x
             110�� 1.4x
             111�� 1.2x
   UNION�ṹ:  ABB_RX_C_ANA_5_UNION */
#define ABB_RX_C_ANA_5_ADDR                           (ABB_BASE_ADDR + 0x409)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr56��
 bit[7:6]    BWCT_OP1 OP1�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[5:4]    BWCT_OP2 OP2�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[3:2]    BWCT_OP3 OP3�������
             1x�� LTEģʽ
             01�� WDC &amp; X ģʽ
             00�� W &amp; Gģʽ
 bit[1:0]    ����
   UNION�ṹ:  ABB_RX_C_ANA_6_UNION */
#define ABB_RX_C_ANA_6_ADDR                           (ABB_BASE_ADDR + 0x40A)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr57��
 bit[7]      ������DACƫ�õ�������
             0 ��������������ܺ�
             1 С�������������ܲ�
 bit[6]      ������DAC������ȿ���
             0 �������0.5
             1 �������0.75
 bit[5]      OP3�Ƿ�ʹ��Gm_biasƫ��
             0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
             1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ��
 bit[4]      �������ο���ѹѡ��
             0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
             1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ
 bit[3:0]    ����
   UNION�ṹ:  ABB_RX_C_ANA_7_UNION */
#define ABB_RX_C_ANA_7_ADDR                           (ABB_BASE_ADDR + 0x40B)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      ����
 bit[6:5]    CK_CTRL_MODE
             00�� LTEģʽ
             01�� WDC &amp; X &amp; TDS_Aģʽ
             1x�� W &amp; G &amp; TDS_Bģʽ
 bit[4:0]    CK_CTRL_DATA
             00000 ����DACʱ����ǰ������
             11111 ����DACʱ����ǰ�����
   UNION�ṹ:  ABB_RX_C_ANA_8_UNION */
#define ABB_RX_C_ANA_8_ADDR                           (ABB_BASE_ADDR + 0x40C)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr59��
 bit[7:6]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
 bit[5:1]    ����
 bit[0]      AD&amp;DA��WPLL��SCPLLѡ���źš�
             0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
             1��ѡ��WPLL����3g��xĬ��ѡ��WPLL��
   UNION�ṹ:  ABB_RX_C_ANA_9_UNION */
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
 bit[7:6]    TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
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
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��8��Ƶ
             11��4��Ƶ
 bit[3]      TX_I DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G &amp; TDS
             010��reserved
             011��2G(Ĭ��)
             1xx��CDMA
   UNION�ṹ:  ABB_TX_C_ANA_1_UNION */
#define ABB_TX_C_ANA_1_ADDR                           (ABB_BASE_ADDR + 0x410)

/* �Ĵ���˵����TX C���üĴ����������߿��߼�������reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_C��˵����
 bit[5:4]    LPF �˷�ƫ�õ�������
             00��   10u
             01��    5u
             10��    5u
             11��    3u
             Ĭ�����÷�����
             LTE:00   GSM:11   Others:01
 bit[3:2]    ����
 bit[1:0]    LPF OP����ģʽ����
             00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
             01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
             10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
             11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

             Ĭ�����÷�����
             LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11
   UNION�ṹ:  ABB_TX_C_ANA_2_UNION */
#define ABB_TX_C_ANA_2_ADDR                           (ABB_BASE_ADDR + 0x411)

/* �Ĵ���˵����TX C���üĴ����������߿��߼�������reg_analog_wr50��
 bit[7]      TX ����ʱ����ѡ��
             0������(Ĭ��)
             1������
 bit[6:5]    ����
 bit[4]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable


 bit[3]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable
 bit[2:0]    LPF OP1 ����ģʽ����
             000��5u
             001��4u
             010��3u
             011��2u
             100��9u
             101��8u
             110��7u
             111��6u
   UNION�ṹ:  ABB_TX_C_ANA_3_UNION */
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

/* �Ĵ���˵����rxbͨ�����⹦��ʹ��
 bit[7:1]    ����
 bit[0]      ch0��ch1 rxbͨ��ʹ�ܻ��⹦��ʹ�ܣ�
             0��rxb���⹦�ܹرգ�
             1��rxb���⹦�ܴ򿪡�
   UNION�ṹ:  ABB_RXB_SEP_EN_UNION */
#define ABB_RXB_SEP_EN_ADDR                           (ABB_BASE_ADDR + 0x600)

/* �Ĵ���˵����rxbͨ������ʱ�������
   ��      ����rxbͨ��ʹ�ܻ���ʱ���������������λ��50ns��һ��19.2MHz���ڣ���
   UNION�ṹ ���� */
#define ABB_RXB_SEP_CNT_NUM_ADDR                      (ABB_BASE_ADDR + 0x601)

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
        unsigned long  tx_cfr_bp_2g   : 1;  /* bit[0]  : TXͨ��CFR bypass���ƣ�
                                                         0����bypass
                                                         1��bypass(Ĭ��)
                                                         ��V8R1���漰�� */
        unsigned long  tx_flush_en_2g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                         0����ʹ��
                                                         1��ʹ�� */
        unsigned long  tx_comp_sel_2g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                         00���̶�ϵ��1��
                                                         01���̶�ϵ��2��
                                                         10���̶�ϵ��3��
                                                         11������ϵ���� */
        unsigned long  reserved       : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_3_UNION;
#define ABB_TX_2G_DIG_3_tx_cfr_bp_2g_START    (0)
#define ABB_TX_2G_DIG_3_tx_cfr_bp_2g_END      (0)
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
        unsigned long  ch0_tx_cfr_bp_3g   : 1;  /* bit[0]  : TXͨ��CFR bypass���ƣ�
                                                             0����bypass
                                                             1��bypass(Ĭ��)
                                                             ��V8R1���漰�� */
        unsigned long  ch0_tx_flush_en_3g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  ch0_tx_comp_sel_3g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11������ϵ���� */
        unsigned long  reserved           : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_3_UNION;
#define ABB_TX_CH0_3G_DIG_3_ch0_tx_cfr_bp_3g_START    (0)
#define ABB_TX_CH0_3G_DIG_3_ch0_tx_cfr_bp_3g_END      (0)
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
        unsigned long  ch0_tx_cfr_bp_4g   : 1;  /* bit[0]  : TXͨ��CFR bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass
                                                             ��V8R1���漰�� */
        unsigned long  ch0_tx_flush_en_4g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  ch0_tx_comp_sel_4g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11������ϵ���� */
        unsigned long  reserved           : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_3_UNION;
#define ABB_TX_CH0_4G_DIG_3_ch0_tx_cfr_bp_4g_START    (0)
#define ABB_TX_CH0_4G_DIG_3_ch0_tx_cfr_bp_4g_END      (0)
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
        unsigned long  tx_cfr_bp_tds   : 1;  /* bit[0]  : TXͨ��CFR bypass���ƣ�
                                                          0����bypass
                                                          1��bypass(Ĭ��)
                                                          ��V8R1���漰�� */
        unsigned long  tx_flush_en_tds : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                          0����ʹ��
                                                          1��ʹ�� */
        unsigned long  tx_comp_sel_tds : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                          00���̶�ϵ��1��
                                                          01���̶�ϵ��2��
                                                          10���̶�ϵ��3��
                                                          11������ϵ���� */
        unsigned long  reserved        : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_3_UNION;
#define ABB_TX_TDS_DIG_3_tx_cfr_bp_tds_START    (0)
#define ABB_TX_TDS_DIG_3_tx_cfr_bp_tds_END      (0)
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
        unsigned long  ch1_tx_cfr_bp_4g   : 1;  /* bit[0]  : TXͨ��CFR bypass���ƣ�
                                                             0����bypass
                                                             1��bypass(Ĭ��)
                                                             ��V8R1���漰�� */
        unsigned long  ch1_tx_flush_en_4g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  ch1_tx_comp_sel_4g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11������ϵ���� */
        unsigned long  reserved           : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_4G_DIG_3_UNION;
#define ABB_TX_CH1_4G_DIG_3_ch1_tx_cfr_bp_4g_START    (0)
#define ABB_TX_CH1_4G_DIG_3_ch1_tx_cfr_bp_4g_END      (0)
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
        unsigned long  tx_cfr_bp_idle   : 1;  /* bit[0]  : TXͨ��CFR bypass���ƣ�
                                                           0����bypass
                                                           1��bypass(Ĭ��)
                                                           ��V8R1���漰�� */
        unsigned long  tx_flush_en_idle : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  tx_comp_sel_idle : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                           00���̶�ϵ��1��
                                                           01���̶�ϵ��2��
                                                           10���̶�ϵ��3��
                                                           11������ϵ���� */
        unsigned long  reserved         : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_3_UNION;
#define ABB_TX_IDLE_DIG_3_tx_cfr_bp_idle_START    (0)
#define ABB_TX_IDLE_DIG_3_tx_cfr_bp_idle_END      (0)
#define ABB_TX_IDLE_DIG_3_tx_flush_en_idle_START  (1)
#define ABB_TX_IDLE_DIG_3_tx_flush_en_idle_END    (1)
#define ABB_TX_IDLE_DIG_3_tx_comp_sel_idle_START  (2)
#define ABB_TX_IDLE_DIG_3_tx_comp_sel_idle_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_ANA_1_UNION
 �ṹ˵��  : rx_2g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x24����ֵ:0xF6�����:8
 �Ĵ���˵��: RX 2G���üĴ����������߿��߼�������reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_2G  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                         000��DWA
                                                         001��CLA1
                                                         010��CLA2
                                                         011��CLA3
                                                         100��CLA4
                                                         101��CLA5
                                                         110��CLA6
                                                         111��CLA7 */
        unsigned long  RX_MODE_CLK_2G : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
                                                         000��4G
                                                         001��3G
                                                         010��3G_DC &amp; TDS
                                                         011��2G(Ĭ��)
                                                         100��reserved
                                                         101��CDMA */
        unsigned long  DEM_MOD_B1_2G  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                         000��DWA
                                                         001��CLA1
                                                         010��CLA2
                                                         011��CLA3
                                                         100��CLA4
                                                         101��CLA5
                                                         110��CLA6
                                                         111��CLA7 */
        unsigned long  RXB_Q_PD_2G    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_2G    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_2G    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_2G    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_1_UNION;
#define ABB_RX_2G_ANA_1_DEM_MOD_B0_2G_START   (0)
#define ABB_RX_2G_ANA_1_DEM_MOD_B0_2G_END     (0)
#define ABB_RX_2G_ANA_1_RX_MODE_CLK_2G_START  (1)
#define ABB_RX_2G_ANA_1_RX_MODE_CLK_2G_END    (2)
#define ABB_RX_2G_ANA_1_DEM_MOD_B1_2G_START   (3)
#define ABB_RX_2G_ANA_1_DEM_MOD_B1_2G_END     (3)
#define ABB_RX_2G_ANA_1_RXB_Q_PD_2G_START     (4)
#define ABB_RX_2G_ANA_1_RXB_Q_PD_2G_END       (4)
#define ABB_RX_2G_ANA_1_RXB_I_PD_2G_START     (5)
#define ABB_RX_2G_ANA_1_RXB_I_PD_2G_END       (5)
#define ABB_RX_2G_ANA_1_RXA_Q_PD_2G_START     (6)
#define ABB_RX_2G_ANA_1_RXA_Q_PD_2G_END       (6)
#define ABB_RX_2G_ANA_1_RXA_I_PD_2G_START     (7)
#define ABB_RX_2G_ANA_1_RXA_I_PD_2G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_ANA_2_UNION
 �ṹ˵��  : rx_2g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x25����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2G���üĴ����������߿��߼�������ch0_reg_analog_wr01��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C_2G : 1;  /* bit[0]  : Mode setting for ADC
                                                       1�� CA mode
                                                       0�� others */
        unsigned long  reserved     : 1;  /* bit[1]  : ���� */
        unsigned long  IBCT_QT_2G   : 2;  /* bit[2-3]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3_2G  : 2;  /* bit[4-5]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1_2G  : 2;  /* bit[6-7]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_2_UNION;
#define ABB_RX_2G_ANA_2_RX_MODE_C_2G_START  (0)
#define ABB_RX_2G_ANA_2_RX_MODE_C_2G_END    (0)
#define ABB_RX_2G_ANA_2_IBCT_QT_2G_START    (2)
#define ABB_RX_2G_ANA_2_IBCT_QT_2G_END      (3)
#define ABB_RX_2G_ANA_2_IBCT_OP3_2G_START   (4)
#define ABB_RX_2G_ANA_2_IBCT_OP3_2G_END     (5)
#define ABB_RX_2G_ANA_2_IBCT_OP1_2G_START   (6)
#define ABB_RX_2G_ANA_2_IBCT_OP1_2G_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_2G_ANA_1_UNION
 �ṹ˵��  : tx_2g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x26����ֵ:0x1F�����:8
 �Ĵ���˵��: TX 2G���üĴ����������߿��߼�������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_2G : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ���ƣ�
                                                         000��4G
                                                         001��3G &amp; TDS
                                                         010��reserved
                                                         011��2G(Ĭ��)
                                                         1xx��CDMA */
        unsigned long  TX_Q_PD_A_2G   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_2G   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_2G : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                         00��1��Ƶ
                                                         01��2��Ƶ(Ĭ��)
                                                         10��8��Ƶ
                                                         11��4��Ƶ */
        unsigned long  FC_B1_B0_2G    : 2;  /* bit[6-7]: TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
                                                         000��14MHz
                                                         001��28MHz
                                                         010��9.3MHz
                                                         011��18.7MHz
                                                         100��7MHz(Ĭ��)
                                                         101��14MHz
                                                         110��28MHz
                                                         111��56MHz
                                                         Ĭ�����÷�����
                                                         4G:001   2G:100   Others:000 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_ANA_1_UNION;
#define ABB_TX_2G_ANA_1_TX_MODE_CLK_2G_START  (0)
#define ABB_TX_2G_ANA_1_TX_MODE_CLK_2G_END    (1)
#define ABB_TX_2G_ANA_1_TX_Q_PD_A_2G_START    (2)
#define ABB_TX_2G_ANA_1_TX_Q_PD_A_2G_END      (2)
#define ABB_TX_2G_ANA_1_TX_I_PD_A_2G_START    (3)
#define ABB_TX_2G_ANA_1_TX_I_PD_A_2G_END      (3)
#define ABB_TX_2G_ANA_1_TX_DIV_MODE_2G_START  (4)
#define ABB_TX_2G_ANA_1_TX_DIV_MODE_2G_END    (5)
#define ABB_TX_2G_ANA_1_FC_B1_B0_2G_START     (6)
#define ABB_TX_2G_ANA_1_FC_B1_B0_2G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_2G_ANA_2_UNION
 �ṹ˵��  : tx_2g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x27����ֵ:0x73�����:8
 �Ĵ���˵��: TX 2G���üĴ����������߿��߼�������reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP_2G  : 2;  /* bit[0-1]: LPF OP����ģʽ����
                                                              00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
                                                              01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
                                                              10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
                                                              11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

                                                              Ĭ�����÷�����
                                                              LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11 */
        unsigned long  reserved            : 2;  /* bit[2-3]: ���� */
        unsigned long  LPF_MODE_CURRENT_2G : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                              00��   10u
                                                              01��    5u
                                                              10��    5u
                                                              11��    3u
                                                              Ĭ�����÷�����
                                                              LTE:00   GSM:11   Others:01 */
        unsigned long  FC_B2_2G            : 1;  /* bit[6]  : TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_2G��˵���� */
        unsigned long  TX_MODE_CLK_B3_2G   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_ANA_2_UNION;
#define ABB_TX_2G_ANA_2_CURRENT_MODE_OP_2G_START   (0)
#define ABB_TX_2G_ANA_2_CURRENT_MODE_OP_2G_END     (1)
#define ABB_TX_2G_ANA_2_LPF_MODE_CURRENT_2G_START  (4)
#define ABB_TX_2G_ANA_2_LPF_MODE_CURRENT_2G_END    (5)
#define ABB_TX_2G_ANA_2_FC_B2_2G_START             (6)
#define ABB_TX_2G_ANA_2_FC_B2_2G_END               (6)
#define ABB_TX_2G_ANA_2_TX_MODE_CLK_B3_2G_START    (7)
#define ABB_TX_2G_ANA_2_TX_MODE_CLK_B3_2G_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_3G_ANA_1_UNION
 �ṹ˵��  : rx_ch0_3g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x28����ֵ:0xF2�����:8
 �Ĵ���˵��: CH0 RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_3G  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                         000��DWA
                                                         001��CLA1
                                                         010��CLA2
                                                         011��CLA3
                                                         100��CLA4
                                                         101��CLA5
                                                         110��CLA6
                                                         111��CLA7 */
        unsigned long  RX_MODE_CLK_3G : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
                                                         000��4G
                                                         001��3G
                                                         010��3G_DC &amp; TDS
                                                         011��2G(Ĭ��)
                                                         100��reserved
                                                         101��CDMA */
        unsigned long  DEM_MOD_B1_3G  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                         000��DWA
                                                         001��CLA1
                                                         010��CLA2
                                                         011��CLA3
                                                         100��CLA4
                                                         101��CLA5
                                                         110��CLA6
                                                         111��CLA7 */
        unsigned long  RXB_Q_PD_3G    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_3G    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_3G    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_3G    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_1_UNION;
#define ABB_RX_CH0_3G_ANA_1_DEM_MOD_B0_3G_START   (0)
#define ABB_RX_CH0_3G_ANA_1_DEM_MOD_B0_3G_END     (0)
#define ABB_RX_CH0_3G_ANA_1_RX_MODE_CLK_3G_START  (1)
#define ABB_RX_CH0_3G_ANA_1_RX_MODE_CLK_3G_END    (2)
#define ABB_RX_CH0_3G_ANA_1_DEM_MOD_B1_3G_START   (3)
#define ABB_RX_CH0_3G_ANA_1_DEM_MOD_B1_3G_END     (3)
#define ABB_RX_CH0_3G_ANA_1_RXB_Q_PD_3G_START     (4)
#define ABB_RX_CH0_3G_ANA_1_RXB_Q_PD_3G_END       (4)
#define ABB_RX_CH0_3G_ANA_1_RXB_I_PD_3G_START     (5)
#define ABB_RX_CH0_3G_ANA_1_RXB_I_PD_3G_END       (5)
#define ABB_RX_CH0_3G_ANA_1_RXA_Q_PD_3G_START     (6)
#define ABB_RX_CH0_3G_ANA_1_RXA_Q_PD_3G_END       (6)
#define ABB_RX_CH0_3G_ANA_1_RXA_I_PD_3G_START     (7)
#define ABB_RX_CH0_3G_ANA_1_RXA_I_PD_3G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_3G_ANA_2_UNION
 �ṹ˵��  : rx_ch0_3g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x29����ֵ:0x00�����:8
 �Ĵ���˵��: RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr01��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C_3G : 1;  /* bit[0]  : Mode setting for ADC
                                                       1�� CA mode
                                                       0�� others */
        unsigned long  reserved     : 1;  /* bit[1]  : ���� */
        unsigned long  IBCT_QT_3G   : 2;  /* bit[2-3]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3_3G  : 2;  /* bit[4-5]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1_3G  : 2;  /* bit[6-7]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_2_UNION;
#define ABB_RX_CH0_3G_ANA_2_RX_MODE_C_3G_START  (0)
#define ABB_RX_CH0_3G_ANA_2_RX_MODE_C_3G_END    (0)
#define ABB_RX_CH0_3G_ANA_2_IBCT_QT_3G_START    (2)
#define ABB_RX_CH0_3G_ANA_2_IBCT_QT_3G_END      (3)
#define ABB_RX_CH0_3G_ANA_2_IBCT_OP3_3G_START   (4)
#define ABB_RX_CH0_3G_ANA_2_IBCT_OP3_3G_END     (5)
#define ABB_RX_CH0_3G_ANA_2_IBCT_OP1_3G_START   (6)
#define ABB_RX_CH0_3G_ANA_2_IBCT_OP1_3G_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_3G_ANA_1_UNION
 �ṹ˵��  : tx_ch0_3g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x2A����ֵ:0x1D�����:8
 �Ĵ���˵��: CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_3G : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
                                                         000��4G
                                                         001��3G &amp; TDS
                                                         010��reserved
                                                         011��2G(Ĭ��)
                                                         1xx��CDMA */
        unsigned long  TX_Q_PD_A_3G   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_3G   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_3G : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                         00��1��Ƶ
                                                         01��2��Ƶ(Ĭ��)
                                                         10��8��Ƶ
                                                         11��4��Ƶ */
        unsigned long  FC_B1_B0_3G    : 2;  /* bit[6-7]: TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
                                                         000��14MHz(Ĭ��)
                                                         001��28MHz
                                                         010��9.3MHz
                                                         011��18.7MHz
                                                         100��7MHz
                                                         101��14MHz
                                                         110��28MHz
                                                         111��56MHz
                                                         Ĭ�����÷�����
                                                         4G:001   2G:100   Others:000 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_ANA_1_UNION;
#define ABB_TX_CH0_3G_ANA_1_TX_MODE_CLK_3G_START  (0)
#define ABB_TX_CH0_3G_ANA_1_TX_MODE_CLK_3G_END    (1)
#define ABB_TX_CH0_3G_ANA_1_TX_Q_PD_A_3G_START    (2)
#define ABB_TX_CH0_3G_ANA_1_TX_Q_PD_A_3G_END      (2)
#define ABB_TX_CH0_3G_ANA_1_TX_I_PD_A_3G_START    (3)
#define ABB_TX_CH0_3G_ANA_1_TX_I_PD_A_3G_END      (3)
#define ABB_TX_CH0_3G_ANA_1_TX_DIV_MODE_3G_START  (4)
#define ABB_TX_CH0_3G_ANA_1_TX_DIV_MODE_3G_END    (5)
#define ABB_TX_CH0_3G_ANA_1_FC_B1_B0_3G_START     (6)
#define ABB_TX_CH0_3G_ANA_1_FC_B1_B0_3G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_3G_ANA_2_UNION
 �ṹ˵��  : tx_ch0_3g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x2B����ֵ:0x11�����:8
 �Ĵ���˵��: CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP_3G  : 2;  /* bit[0-1]: LPF OP����ģʽ����
                                                              00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
                                                              01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
                                                              10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
                                                              11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

                                                              Ĭ�����÷�����
                                                              LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11 */
        unsigned long  reserved            : 2;  /* bit[2-3]: ���� */
        unsigned long  LPF_MODE_CURRENT_3G : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                              00��   10u
                                                              01��    5u
                                                              10��    5u
                                                              11��    3u
                                                              Ĭ�����÷�����
                                                              LTE:00   GSM:11   Others:01 */
        unsigned long  FC_B2_3G            : 1;  /* bit[6]  : TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_3G��˵���� */
        unsigned long  TX_MODE_CLK_B3_3G   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_ANA_2_UNION;
#define ABB_TX_CH0_3G_ANA_2_CURRENT_MODE_OP_3G_START   (0)
#define ABB_TX_CH0_3G_ANA_2_CURRENT_MODE_OP_3G_END     (1)
#define ABB_TX_CH0_3G_ANA_2_LPF_MODE_CURRENT_3G_START  (4)
#define ABB_TX_CH0_3G_ANA_2_LPF_MODE_CURRENT_3G_END    (5)
#define ABB_TX_CH0_3G_ANA_2_FC_B2_3G_START             (6)
#define ABB_TX_CH0_3G_ANA_2_FC_B2_3G_END               (6)
#define ABB_TX_CH0_3G_ANA_2_TX_MODE_CLK_B3_3G_START    (7)
#define ABB_TX_CH0_3G_ANA_2_TX_MODE_CLK_B3_3G_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_4G_ANA_1_UNION
 �ṹ˵��  : rx_ch0_4g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x2C����ֵ:0xF0�����:8
 �Ĵ���˵��: CH0 RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_4G  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                         000��DWA
                                                         001��CLA1
                                                         010��CLA2
                                                         011��CLA3
                                                         100��CLA4
                                                         101��CLA5
                                                         110��CLA6
                                                         111��CLA7 */
        unsigned long  RX_MODE_CLK_4G : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
                                                         000��4G
                                                         001��3G
                                                         010��3G_DC &amp; TDS
                                                         011��2G(Ĭ��)
                                                         100��reserved
                                                         101��CDMA */
        unsigned long  DEM_MOD_B1_4G  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                         000��DWA
                                                         001��CLA1
                                                         010��CLA2
                                                         011��CLA3
                                                         100��CLA4
                                                         101��CLA5
                                                         110��CLA6
                                                         111��CLA7 */
        unsigned long  RXB_Q_PD_4G    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_4G    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_4G    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_4G    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_1_UNION;
#define ABB_RX_CH0_4G_ANA_1_DEM_MOD_B0_4G_START   (0)
#define ABB_RX_CH0_4G_ANA_1_DEM_MOD_B0_4G_END     (0)
#define ABB_RX_CH0_4G_ANA_1_RX_MODE_CLK_4G_START  (1)
#define ABB_RX_CH0_4G_ANA_1_RX_MODE_CLK_4G_END    (2)
#define ABB_RX_CH0_4G_ANA_1_DEM_MOD_B1_4G_START   (3)
#define ABB_RX_CH0_4G_ANA_1_DEM_MOD_B1_4G_END     (3)
#define ABB_RX_CH0_4G_ANA_1_RXB_Q_PD_4G_START     (4)
#define ABB_RX_CH0_4G_ANA_1_RXB_Q_PD_4G_END       (4)
#define ABB_RX_CH0_4G_ANA_1_RXB_I_PD_4G_START     (5)
#define ABB_RX_CH0_4G_ANA_1_RXB_I_PD_4G_END       (5)
#define ABB_RX_CH0_4G_ANA_1_RXA_Q_PD_4G_START     (6)
#define ABB_RX_CH0_4G_ANA_1_RXA_Q_PD_4G_END       (6)
#define ABB_RX_CH0_4G_ANA_1_RXA_I_PD_4G_START     (7)
#define ABB_RX_CH0_4G_ANA_1_RXA_I_PD_4G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_4G_ANA_2_UNION
 �ṹ˵��  : rx_ch0_4g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x2D����ֵ:0xA8�����:8
 �Ĵ���˵��: RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr01��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C_4G : 1;  /* bit[0]  : Mode setting for ADC
                                                       1�� CA mode
                                                       0�� others */
        unsigned long  reserved     : 1;  /* bit[1]  : ���� */
        unsigned long  IBCT_QT_4G   : 2;  /* bit[2-3]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3_4G  : 2;  /* bit[4-5]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1_4G  : 2;  /* bit[6-7]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_2_UNION;
#define ABB_RX_CH0_4G_ANA_2_RX_MODE_C_4G_START  (0)
#define ABB_RX_CH0_4G_ANA_2_RX_MODE_C_4G_END    (0)
#define ABB_RX_CH0_4G_ANA_2_IBCT_QT_4G_START    (2)
#define ABB_RX_CH0_4G_ANA_2_IBCT_QT_4G_END      (3)
#define ABB_RX_CH0_4G_ANA_2_IBCT_OP3_4G_START   (4)
#define ABB_RX_CH0_4G_ANA_2_IBCT_OP3_4G_END     (5)
#define ABB_RX_CH0_4G_ANA_2_IBCT_OP1_4G_START   (6)
#define ABB_RX_CH0_4G_ANA_2_IBCT_OP1_4G_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_4G_ANA_1_UNION
 �ṹ˵��  : tx_ch0_4g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x2E����ֵ:0x5C�����:8
 �Ĵ���˵��: CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_4G : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
                                                         000��4G
                                                         001��3G &amp; TDS
                                                         010��reserved
                                                         011��2G(Ĭ��)
                                                         1xx��CDMA */
        unsigned long  TX_Q_PD_A_4G   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_4G   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_4G : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                         00��1��Ƶ
                                                         01��2��Ƶ(Ĭ��)
                                                         10��8��Ƶ
                                                         11��4��Ƶ */
        unsigned long  FC_B1_B0_4G    : 2;  /* bit[6-7]: TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
                                                         000��14MHz
                                                         001��28MHz(Ĭ��)
                                                         010��9.3MHz
                                                         011��18.7MHz
                                                         100��7MHz
                                                         101��14MHz
                                                         110��28MHz
                                                         111��56MHz
                                                         Ĭ�����÷�����
                                                         4G:001   2G:100   Others:000 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_ANA_1_UNION;
#define ABB_TX_CH0_4G_ANA_1_TX_MODE_CLK_4G_START  (0)
#define ABB_TX_CH0_4G_ANA_1_TX_MODE_CLK_4G_END    (1)
#define ABB_TX_CH0_4G_ANA_1_TX_Q_PD_A_4G_START    (2)
#define ABB_TX_CH0_4G_ANA_1_TX_Q_PD_A_4G_END      (2)
#define ABB_TX_CH0_4G_ANA_1_TX_I_PD_A_4G_START    (3)
#define ABB_TX_CH0_4G_ANA_1_TX_I_PD_A_4G_END      (3)
#define ABB_TX_CH0_4G_ANA_1_TX_DIV_MODE_4G_START  (4)
#define ABB_TX_CH0_4G_ANA_1_TX_DIV_MODE_4G_END    (5)
#define ABB_TX_CH0_4G_ANA_1_FC_B1_B0_4G_START     (6)
#define ABB_TX_CH0_4G_ANA_1_FC_B1_B0_4G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_4G_ANA_2_UNION
 �ṹ˵��  : tx_ch0_4g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x2F����ֵ:0x00�����:8
 �Ĵ���˵��: CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP_4G  : 2;  /* bit[0-1]: LPF OP����ģʽ����
                                                              00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
                                                              01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
                                                              10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
                                                              11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

                                                              Ĭ�����÷�����
                                                              LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11 */
        unsigned long  reserved            : 2;  /* bit[2-3]: ���� */
        unsigned long  LPF_MODE_CURRENT_4G : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                              00��   10u
                                                              01��    5u
                                                              10��    5u
                                                              11��    3u
                                                              Ĭ�����÷�����
                                                              LTE:00   GSM:11   Others:01 */
        unsigned long  FC_B2_4G            : 1;  /* bit[6]  : TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_4G��˵���� */
        unsigned long  TX_MODE_CLK_B3_4G   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_ANA_2_UNION;
#define ABB_TX_CH0_4G_ANA_2_CURRENT_MODE_OP_4G_START   (0)
#define ABB_TX_CH0_4G_ANA_2_CURRENT_MODE_OP_4G_END     (1)
#define ABB_TX_CH0_4G_ANA_2_LPF_MODE_CURRENT_4G_START  (4)
#define ABB_TX_CH0_4G_ANA_2_LPF_MODE_CURRENT_4G_END    (5)
#define ABB_TX_CH0_4G_ANA_2_FC_B2_4G_START             (6)
#define ABB_TX_CH0_4G_ANA_2_FC_B2_4G_END               (6)
#define ABB_TX_CH0_4G_ANA_2_TX_MODE_CLK_B3_4G_START    (7)
#define ABB_TX_CH0_4G_ANA_2_TX_MODE_CLK_B3_4G_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_ANA_1_UNION
 �ṹ˵��  : rx_tds_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0xF2�����:8
 �Ĵ���˵��: RX TDS���üĴ����������߿��߼�������reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_TDS  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                          000��DWA
                                                          001��CLA1
                                                          010��CLA2
                                                          011��CLA3
                                                          100��CLA4
                                                          101��CLA5
                                                          110��CLA6
                                                          111��CLA7 */
        unsigned long  RX_MODE_CLK_TDS : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
                                                          000��4G
                                                          001��3G
                                                          010��3G_DC &amp; TDS
                                                          011��2G(Ĭ��)
                                                          100��reserved
                                                          101��CDMA */
        unsigned long  DEM_MOD_B1_TDS  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                          000��DWA
                                                          001��CLA1
                                                          010��CLA2
                                                          011��CLA3
                                                          100��CLA4
                                                          101��CLA5
                                                          110��CLA6
                                                          111��CLA7 */
        unsigned long  RXB_Q_PD_TDS    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                          0��Power On
                                                          1��Power Down(Ĭ��)
                                                          (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_TDS    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                          0��Power On
                                                          1��Power Down(Ĭ��)
                                                          (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_TDS    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                          0��Power On
                                                          1��Power Down(Ĭ��)
                                                          (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_TDS    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                          0��Power On
                                                          1��Power Down(Ĭ��)
                                                          (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_1_UNION;
#define ABB_RX_TDS_ANA_1_DEM_MOD_B0_TDS_START   (0)
#define ABB_RX_TDS_ANA_1_DEM_MOD_B0_TDS_END     (0)
#define ABB_RX_TDS_ANA_1_RX_MODE_CLK_TDS_START  (1)
#define ABB_RX_TDS_ANA_1_RX_MODE_CLK_TDS_END    (2)
#define ABB_RX_TDS_ANA_1_DEM_MOD_B1_TDS_START   (3)
#define ABB_RX_TDS_ANA_1_DEM_MOD_B1_TDS_END     (3)
#define ABB_RX_TDS_ANA_1_RXB_Q_PD_TDS_START     (4)
#define ABB_RX_TDS_ANA_1_RXB_Q_PD_TDS_END       (4)
#define ABB_RX_TDS_ANA_1_RXB_I_PD_TDS_START     (5)
#define ABB_RX_TDS_ANA_1_RXB_I_PD_TDS_END       (5)
#define ABB_RX_TDS_ANA_1_RXA_Q_PD_TDS_START     (6)
#define ABB_RX_TDS_ANA_1_RXA_Q_PD_TDS_END       (6)
#define ABB_RX_TDS_ANA_1_RXA_I_PD_TDS_START     (7)
#define ABB_RX_TDS_ANA_1_RXA_I_PD_TDS_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_ANA_2_UNION
 �ṹ˵��  : rx_tds_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x31����ֵ:0x00�����:8
 �Ĵ���˵��: RX TDS���üĴ����������߿��߼�������ch0_reg_analog_wr01��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C_TDS : 1;  /* bit[0]  : Mode setting for ADC
                                                        1�� CA mode
                                                        0�� others */
        unsigned long  reserved      : 1;  /* bit[1]  : ���� */
        unsigned long  IBCT_QT_TDS   : 2;  /* bit[2-3]: Current Seting For Mode
                                                        1x��LTE mode Current
                                                        01��3G_DC &amp; X mode Current
                                                        00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3_TDS  : 2;  /* bit[4-5]: Current Seting For Mode
                                                        1x��LTE mode Current
                                                        01��3G_DC &amp; X mode Current
                                                        00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1_TDS  : 2;  /* bit[6-7]: Current Seting For Mode
                                                        1x��LTE mode Current
                                                        01��3G_DC &amp; X mode Current
                                                        00��3G &amp; 2G mode Current */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_2_UNION;
#define ABB_RX_TDS_ANA_2_RX_MODE_C_TDS_START  (0)
#define ABB_RX_TDS_ANA_2_RX_MODE_C_TDS_END    (0)
#define ABB_RX_TDS_ANA_2_IBCT_QT_TDS_START    (2)
#define ABB_RX_TDS_ANA_2_IBCT_QT_TDS_END      (3)
#define ABB_RX_TDS_ANA_2_IBCT_OP3_TDS_START   (4)
#define ABB_RX_TDS_ANA_2_IBCT_OP3_TDS_END     (5)
#define ABB_RX_TDS_ANA_2_IBCT_OP1_TDS_START   (6)
#define ABB_RX_TDS_ANA_2_IBCT_OP1_TDS_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_ANA_1_UNION
 �ṹ˵��  : tx_tds_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x32����ֵ:0x1D�����:8
 �Ĵ���˵��: TX TDS���üĴ����������߿��߼�������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_TDS : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
                                                          000��4G
                                                          001��3G &amp; TDS
                                                          010��reserved
                                                          011��2G(Ĭ��)
                                                          1xx��CDMA */
        unsigned long  TX_Q_PD_A_TDS   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                          0��Power On
                                                          1��Power Down(Ĭ��)
                                                          (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_TDS   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                          0��Power On
                                                          1��Power Down(Ĭ��)
                                                          (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_TDS : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                          00��1��Ƶ
                                                          01��2��Ƶ(Ĭ��)
                                                          10��8��Ƶ
                                                          11��4��Ƶ */
        unsigned long  FC_B1_B0_TDS    : 2;  /* bit[6-7]: TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
                                                          000��14MHz(Ĭ��)
                                                          001��28MHz
                                                          010��9.3MHz
                                                          011��18.7MHz
                                                          100��7MHz
                                                          101��14MHz
                                                          110��28MHz
                                                          111��56MHz
                                                          Ĭ�����÷�����
                                                          4G:001   2G:100   Others:000 */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_ANA_1_UNION;
#define ABB_TX_TDS_ANA_1_TX_MODE_CLK_TDS_START  (0)
#define ABB_TX_TDS_ANA_1_TX_MODE_CLK_TDS_END    (1)
#define ABB_TX_TDS_ANA_1_TX_Q_PD_A_TDS_START    (2)
#define ABB_TX_TDS_ANA_1_TX_Q_PD_A_TDS_END      (2)
#define ABB_TX_TDS_ANA_1_TX_I_PD_A_TDS_START    (3)
#define ABB_TX_TDS_ANA_1_TX_I_PD_A_TDS_END      (3)
#define ABB_TX_TDS_ANA_1_TX_DIV_MODE_TDS_START  (4)
#define ABB_TX_TDS_ANA_1_TX_DIV_MODE_TDS_END    (5)
#define ABB_TX_TDS_ANA_1_FC_B1_B0_TDS_START     (6)
#define ABB_TX_TDS_ANA_1_FC_B1_B0_TDS_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_ANA_2_UNION
 �ṹ˵��  : tx_tds_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x33����ֵ:0x11�����:8
 �Ĵ���˵��: TX TDS���üĴ����������߿��߼�������reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP_TDS : 2;  /* bit[0-1]: LPF OP����ģʽ����
                                                              00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
                                                              01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
                                                              10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
                                                              11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

                                                              Ĭ�����÷�����
                                                              LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11 */
        unsigned long  reserved            : 2;  /* bit[2-3]: ���� */
        unsigned long  LPF_MODE_TDS        : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                              00��   10u
                                                              01��    5u
                                                              10��    5u
                                                              11��    3u
                                                              Ĭ�����÷�����
                                                              LTE:00   GSM:11   Others:01 */
        unsigned long  FC_B2_TDS           : 1;  /* bit[6]  : TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_TDS��˵���� */
        unsigned long  TX_MODE_CLK_B3_TDS  : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_ANA_2_UNION;
#define ABB_TX_TDS_ANA_2_CURRENT_MODE_OP_TDS_START  (0)
#define ABB_TX_TDS_ANA_2_CURRENT_MODE_OP_TDS_END    (1)
#define ABB_TX_TDS_ANA_2_LPF_MODE_TDS_START         (4)
#define ABB_TX_TDS_ANA_2_LPF_MODE_TDS_END           (5)
#define ABB_TX_TDS_ANA_2_FC_B2_TDS_START            (6)
#define ABB_TX_TDS_ANA_2_FC_B2_TDS_END              (6)
#define ABB_TX_TDS_ANA_2_TX_MODE_CLK_B3_TDS_START   (7)
#define ABB_TX_TDS_ANA_2_TX_MODE_CLK_B3_TDS_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_4G_ANA_1_UNION
 �ṹ˵��  : rx_ch1_4g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0xF0�����:8
 �Ĵ���˵��: CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_4G  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                         000��DWA
                                                         001��CLA1
                                                         010��CLA2
                                                         011��CLA3
                                                         100��CLA4
                                                         101��CLA5
                                                         110��CLA6
                                                         111��CLA7 */
        unsigned long  RX_MODE_CLK_4G : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
                                                         000��4G
                                                         001��3G
                                                         010��3G_DC &amp; TDS
                                                         011��2G(Ĭ��)
                                                         100��reserved
                                                         101��CDMA */
        unsigned long  DEM_MOD_B1_4G  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                         000��DWA
                                                         001��CLA1
                                                         010��CLA2
                                                         011��CLA3
                                                         100��CLA4
                                                         101��CLA5
                                                         110��CLA6
                                                         111��CLA7 */
        unsigned long  RXB_Q_PD_4G    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_4G    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_4G    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_4G    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_4G_ANA_1_UNION;
#define ABB_RX_CH1_4G_ANA_1_DEM_MOD_B0_4G_START   (0)
#define ABB_RX_CH1_4G_ANA_1_DEM_MOD_B0_4G_END     (0)
#define ABB_RX_CH1_4G_ANA_1_RX_MODE_CLK_4G_START  (1)
#define ABB_RX_CH1_4G_ANA_1_RX_MODE_CLK_4G_END    (2)
#define ABB_RX_CH1_4G_ANA_1_DEM_MOD_B1_4G_START   (3)
#define ABB_RX_CH1_4G_ANA_1_DEM_MOD_B1_4G_END     (3)
#define ABB_RX_CH1_4G_ANA_1_RXB_Q_PD_4G_START     (4)
#define ABB_RX_CH1_4G_ANA_1_RXB_Q_PD_4G_END       (4)
#define ABB_RX_CH1_4G_ANA_1_RXB_I_PD_4G_START     (5)
#define ABB_RX_CH1_4G_ANA_1_RXB_I_PD_4G_END       (5)
#define ABB_RX_CH1_4G_ANA_1_RXA_Q_PD_4G_START     (6)
#define ABB_RX_CH1_4G_ANA_1_RXA_Q_PD_4G_END       (6)
#define ABB_RX_CH1_4G_ANA_1_RXA_I_PD_4G_START     (7)
#define ABB_RX_CH1_4G_ANA_1_RXA_I_PD_4G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_4G_ANA_2_UNION
 �ṹ˵��  : rx_ch1_4g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x39����ֵ:0xA8�����:8
 �Ĵ���˵��: CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr01��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C_4G : 1;  /* bit[0]  : Mode setting for ADC
                                                       1�� CA mode
                                                       0�� others */
        unsigned long  reserved     : 1;  /* bit[1]  : ���� */
        unsigned long  IBCT_QT_4G   : 2;  /* bit[2-3]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3_4G  : 2;  /* bit[4-5]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1_4G  : 2;  /* bit[6-7]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_4G_ANA_2_UNION;
#define ABB_RX_CH1_4G_ANA_2_RX_MODE_C_4G_START  (0)
#define ABB_RX_CH1_4G_ANA_2_RX_MODE_C_4G_END    (0)
#define ABB_RX_CH1_4G_ANA_2_IBCT_QT_4G_START    (2)
#define ABB_RX_CH1_4G_ANA_2_IBCT_QT_4G_END      (3)
#define ABB_RX_CH1_4G_ANA_2_IBCT_OP3_4G_START   (4)
#define ABB_RX_CH1_4G_ANA_2_IBCT_OP3_4G_END     (5)
#define ABB_RX_CH1_4G_ANA_2_IBCT_OP1_4G_START   (6)
#define ABB_RX_CH1_4G_ANA_2_IBCT_OP1_4G_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH1_4G_ANA_1_UNION
 �ṹ˵��  : tx_ch1_4g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x3A����ֵ:0x5C�����:8
 �Ĵ���˵��: CH1 TX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_4G : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
                                                         000��4G
                                                         001��3G &amp; TDS
                                                         010��reserved
                                                         011��2G(Ĭ��)
                                                         1xx��CDMA */
        unsigned long  TX_Q_PD_A_4G   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_4G   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_4G : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                         00��1��Ƶ
                                                         01��2��Ƶ(Ĭ��)
                                                         10��8��Ƶ
                                                         11��4��Ƶ */
        unsigned long  FC_B1_B0_4G    : 2;  /* bit[6-7]: TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
                                                         000��14MHz
                                                         001��28MHz(Ĭ��)
                                                         010��9.3MHz
                                                         011��18.7MHz
                                                         100��7MHz
                                                         101��14MHz
                                                         110��28MHz
                                                         111��56MHz
                                                         Ĭ�����÷�����
                                                         4G:001   2G:100   Others:000 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_4G_ANA_1_UNION;
#define ABB_TX_CH1_4G_ANA_1_TX_MODE_CLK_4G_START  (0)
#define ABB_TX_CH1_4G_ANA_1_TX_MODE_CLK_4G_END    (1)
#define ABB_TX_CH1_4G_ANA_1_TX_Q_PD_A_4G_START    (2)
#define ABB_TX_CH1_4G_ANA_1_TX_Q_PD_A_4G_END      (2)
#define ABB_TX_CH1_4G_ANA_1_TX_I_PD_A_4G_START    (3)
#define ABB_TX_CH1_4G_ANA_1_TX_I_PD_A_4G_END      (3)
#define ABB_TX_CH1_4G_ANA_1_TX_DIV_MODE_4G_START  (4)
#define ABB_TX_CH1_4G_ANA_1_TX_DIV_MODE_4G_END    (5)
#define ABB_TX_CH1_4G_ANA_1_FC_B1_B0_4G_START     (6)
#define ABB_TX_CH1_4G_ANA_1_FC_B1_B0_4G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH1_4G_ANA_2_UNION
 �ṹ˵��  : tx_ch1_4g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x3B����ֵ:0x00�����:8
 �Ĵ���˵��: CH1 TX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP_4G  : 2;  /* bit[0-1]: LPF OP����ģʽ����
                                                              00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
                                                              01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
                                                              10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
                                                              11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

                                                              Ĭ�����÷�����
                                                              LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11 */
        unsigned long  reserved            : 2;  /* bit[2-3]: ���� */
        unsigned long  LPF_MODE_CURRENT_4G : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                              00��   10u
                                                              01��    5u
                                                              10��    5u
                                                              11��    3u
                                                              Ĭ�����÷�����
                                                              LTE:00   GSM:11   Others:01 */
        unsigned long  FC_B2_4G            : 1;  /* bit[6]  : TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_4G��˵���� */
        unsigned long  TX_MODE_CLK_B3_4G   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_4G_ANA_2_UNION;
#define ABB_TX_CH1_4G_ANA_2_CURRENT_MODE_OP_4G_START   (0)
#define ABB_TX_CH1_4G_ANA_2_CURRENT_MODE_OP_4G_END     (1)
#define ABB_TX_CH1_4G_ANA_2_LPF_MODE_CURRENT_4G_START  (4)
#define ABB_TX_CH1_4G_ANA_2_LPF_MODE_CURRENT_4G_END    (5)
#define ABB_TX_CH1_4G_ANA_2_FC_B2_4G_START             (6)
#define ABB_TX_CH1_4G_ANA_2_FC_B2_4G_END               (6)
#define ABB_TX_CH1_4G_ANA_2_TX_MODE_CLK_B3_4G_START    (7)
#define ABB_TX_CH1_4G_ANA_2_TX_MODE_CLK_B3_4G_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_ANA_1_UNION
 �ṹ˵��  : rx_idle_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0xF6�����:8
 �Ĵ���˵��: RX IDLE���üĴ����������߿��߼�������reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_IDLE  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                           000��DWA
                                                           001��CLA1
                                                           010��CLA2
                                                           011��CLA3
                                                           100��CLA4
                                                           101��CLA5
                                                           110��CLA6
                                                           111��CLA7 */
        unsigned long  RX_MODE_CLK_IDLE : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
                                                           000��4G
                                                           001��3G
                                                           010��3G_DC &amp; TDS
                                                           011��2G(Ĭ��)
                                                           100��reserved
                                                           101��CDMA */
        unsigned long  DEM_MOD_B1_IDLE  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                           000��DWA
                                                           001��CLA1
                                                           010��CLA2
                                                           011��CLA3
                                                           100��CLA4
                                                           101��CLA5
                                                           110��CLA6
                                                           111��CLA7 */
        unsigned long  RXB_Q_PD_IDLE    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                           0��Power On
                                                           1��Power Down(Ĭ��)
                                                           (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_IDLE    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                           0��Power On
                                                           1��Power Down(Ĭ��)
                                                           (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_IDLE    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                           0��Power On
                                                           1��Power Down(Ĭ��)
                                                           (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_IDLE    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                           0��Power On
                                                           1��Power Down(Ĭ��)
                                                           (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_1_UNION;
#define ABB_RX_IDLE_ANA_1_DEM_MOD_B0_IDLE_START   (0)
#define ABB_RX_IDLE_ANA_1_DEM_MOD_B0_IDLE_END     (0)
#define ABB_RX_IDLE_ANA_1_RX_MODE_CLK_IDLE_START  (1)
#define ABB_RX_IDLE_ANA_1_RX_MODE_CLK_IDLE_END    (2)
#define ABB_RX_IDLE_ANA_1_DEM_MOD_B1_IDLE_START   (3)
#define ABB_RX_IDLE_ANA_1_DEM_MOD_B1_IDLE_END     (3)
#define ABB_RX_IDLE_ANA_1_RXB_Q_PD_IDLE_START     (4)
#define ABB_RX_IDLE_ANA_1_RXB_Q_PD_IDLE_END       (4)
#define ABB_RX_IDLE_ANA_1_RXB_I_PD_IDLE_START     (5)
#define ABB_RX_IDLE_ANA_1_RXB_I_PD_IDLE_END       (5)
#define ABB_RX_IDLE_ANA_1_RXA_Q_PD_IDLE_START     (6)
#define ABB_RX_IDLE_ANA_1_RXA_Q_PD_IDLE_END       (6)
#define ABB_RX_IDLE_ANA_1_RXA_I_PD_IDLE_START     (7)
#define ABB_RX_IDLE_ANA_1_RXA_I_PD_IDLE_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_ANA_2_UNION
 �ṹ˵��  : rx_idle_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x3D����ֵ:0x00�����:8
 �Ĵ���˵��: IDLE���üĴ����������߿��߼�������reg_analog_wr01��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C_IDLE : 1;  /* bit[0]  : Mode setting for ADC
                                                         1�� CA mode
                                                         0�� others */
        unsigned long  reserved       : 1;  /* bit[1]  : ���� */
        unsigned long  IBCT_QT_IDLE   : 2;  /* bit[2-3]: Current Seting For Mode
                                                         1x��LTE mode Current
                                                         01��3G_DC &amp; X mode Current
                                                         00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3_IDLE  : 2;  /* bit[4-5]: Current Seting For Mode
                                                         1x��LTE mode Current
                                                         01��3G_DC &amp; X mode Current
                                                         00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1_IDLE  : 2;  /* bit[6-7]: Current Seting For Mode
                                                         1x��LTE mode Current
                                                         01��3G_DC &amp; X mode Current
                                                         00��3G &amp; 2G mode Current */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_2_UNION;
#define ABB_RX_IDLE_ANA_2_RX_MODE_C_IDLE_START  (0)
#define ABB_RX_IDLE_ANA_2_RX_MODE_C_IDLE_END    (0)
#define ABB_RX_IDLE_ANA_2_IBCT_QT_IDLE_START    (2)
#define ABB_RX_IDLE_ANA_2_IBCT_QT_IDLE_END      (3)
#define ABB_RX_IDLE_ANA_2_IBCT_OP3_IDLE_START   (4)
#define ABB_RX_IDLE_ANA_2_IBCT_OP3_IDLE_END     (5)
#define ABB_RX_IDLE_ANA_2_IBCT_OP1_IDLE_START   (6)
#define ABB_RX_IDLE_ANA_2_IBCT_OP1_IDLE_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_ANA_1_UNION
 �ṹ˵��  : tx_idle_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x3E����ֵ:0x1F�����:8
 �Ĵ���˵��: TX IDLE���üĴ����������߿��߼�������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_IDLE : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
                                                           000��4G
                                                           001��3G &amp; TDS
                                                           010��reserved
                                                           011��2G(Ĭ��)
                                                           1xx��CDMA */
        unsigned long  TX_Q_PD_A_IDLE   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                           0��Power On
                                                           1��Power Down(Ĭ��)
                                                           (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_IDLE   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                           0��Power On
                                                           1��Power Down(Ĭ��)
                                                           (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_IDLE : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                           00��1��Ƶ
                                                           01��2��Ƶ(Ĭ��)
                                                           10��8��Ƶ
                                                           11��4��Ƶ */
        unsigned long  FC_B1_B0_IDLE    : 2;  /* bit[6-7]: TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
                                                           000��14MHz
                                                           001��28MHz
                                                           010��9.3MHz
                                                           011��18.7MHz
                                                           100��7MHz(Ĭ��)
                                                           101��14MHz
                                                           110��28MHz
                                                           111��56MHz
                                                           Ĭ�����÷�����
                                                           4G:001   2G:100   Others:000 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_ANA_1_UNION;
#define ABB_TX_IDLE_ANA_1_TX_MODE_CLK_IDLE_START  (0)
#define ABB_TX_IDLE_ANA_1_TX_MODE_CLK_IDLE_END    (1)
#define ABB_TX_IDLE_ANA_1_TX_Q_PD_A_IDLE_START    (2)
#define ABB_TX_IDLE_ANA_1_TX_Q_PD_A_IDLE_END      (2)
#define ABB_TX_IDLE_ANA_1_TX_I_PD_A_IDLE_START    (3)
#define ABB_TX_IDLE_ANA_1_TX_I_PD_A_IDLE_END      (3)
#define ABB_TX_IDLE_ANA_1_TX_DIV_MODE_IDLE_START  (4)
#define ABB_TX_IDLE_ANA_1_TX_DIV_MODE_IDLE_END    (5)
#define ABB_TX_IDLE_ANA_1_FC_B1_B0_IDLE_START     (6)
#define ABB_TX_IDLE_ANA_1_FC_B1_B0_IDLE_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_ANA_2_UNION
 �ṹ˵��  : tx_idle_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x3F����ֵ:0x73�����:8
 �Ĵ���˵��: TX IDLE���üĴ����������߿��߼�������reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP_IDLE  : 2;  /* bit[0-1]: LPF OP����ģʽ����
                                                                00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
                                                                01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
                                                                10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
                                                                11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

                                                                Ĭ�����÷�����
                                                                LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11 */
        unsigned long  reserved              : 2;  /* bit[2-3]: ���� */
        unsigned long  LPF_MODE_CURRENT_IDLE : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                                00��   10u
                                                                01��    5u
                                                                10��    5u
                                                                11��    3u
                                                                Ĭ�����÷�����
                                                                LTE:00   GSM:11   Others:01 */
        unsigned long  FC_B2_IDLE            : 1;  /* bit[6]  : TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_IDLE��˵���� */
        unsigned long  TX_MODE_CLK_B3_IDLE   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_ANA_2_UNION;
#define ABB_TX_IDLE_ANA_2_CURRENT_MODE_OP_IDLE_START   (0)
#define ABB_TX_IDLE_ANA_2_CURRENT_MODE_OP_IDLE_END     (1)
#define ABB_TX_IDLE_ANA_2_LPF_MODE_CURRENT_IDLE_START  (4)
#define ABB_TX_IDLE_ANA_2_LPF_MODE_CURRENT_IDLE_END    (5)
#define ABB_TX_IDLE_ANA_2_FC_B2_IDLE_START             (6)
#define ABB_TX_IDLE_ANA_2_FC_B2_IDLE_END               (6)
#define ABB_TX_IDLE_ANA_2_TX_MODE_CLK_B3_IDLE_START    (7)
#define ABB_TX_IDLE_ANA_2_TX_MODE_CLK_B3_IDLE_END      (7)


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
 �ṹ��    : ABB_CH1_CFR_CTRL_UNION
 �ṹ˵��  : ch1_cfr_ctrl �Ĵ����ṹ���塣��ַƫ����:0x43����ֵ:0x44�����:8
 �Ĵ���˵��: CFR��ֵ��ⴰ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_cfr_pdet_sel : 2;  /* bit[0-1]: CFR��ֵ��ⷽʽ��
                                                           00���������
                                                           01���������
                                                           10���������
                                                           11��ȫ����ֵ
                                                           ��V8R1���漰�� */
        unsigned long  ch1_cfr_fir_sel  : 1;  /* bit[2]  : CFR�˲���ѡ��
                                                           0��bypass�˲���
                                                           1����bypass�˲���
                                                           ��V8R1���漰�� */
        unsigned long  reserved         : 1;  /* bit[3]  : ���� */
        unsigned long  ch1_cfr_fir_fac  : 4;  /* bit[4-7]: CFR��������
                                                           ��V8R1���漰�� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_CFR_CTRL_UNION;
#define ABB_CH1_CFR_CTRL_ch1_cfr_pdet_sel_START  (0)
#define ABB_CH1_CFR_CTRL_ch1_cfr_pdet_sel_END    (1)
#define ABB_CH1_CFR_CTRL_ch1_cfr_fir_sel_START   (2)
#define ABB_CH1_CFR_CTRL_ch1_cfr_fir_sel_END     (2)
#define ABB_CH1_CFR_CTRL_ch1_cfr_fir_fac_START   (4)
#define ABB_CH1_CFR_CTRL_ch1_cfr_fir_fac_END     (7)


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
 �ṹ˵��  : ch1_reg_debug_dig0 �Ĵ����ṹ���塣��ַƫ����:0x6B����ֵ:0x24�����:8
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
        unsigned long  reserved          : 2;  /* bit[6-7]: ���� */
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


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR04_UNION
 �ṹ˵��  : ch1_reg_analog_wr04 �Ĵ����ṹ���塣��ַƫ����:0x72����ֵ:0x0C�����:8
 �Ĵ���˵��: Other���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH1_START_RC_TUNE : 1;  /* bit[0]  : RC TUNE����
                                                            ����������RC У׼���� */
        unsigned long  reserved_0        : 1;  /* bit[1]  : Reserved */
        unsigned long  CH1_TX_AUTO_TUNE  : 1;  /* bit[2]  : TX ADC�Զ�tuning����
                                                            0���ֶ�tuning��tuningѡ��TX_TUNE1,TX_TUNE2,TX_TUNE3��ֵ(Ĭ��)
                                                            1���Զ�tuning��TXͨ����calibrationֵΪCAL_VALUE */
        unsigned long  CH1_RX_AUTO_TUNE  : 1;  /* bit[3]  : RX ADC�Զ�tuning����
                                                            0���ֶ�tuning��tuningѡ��RX_TUNE1,RX_TUNE2,RX_TUNE3��ֵ(Ĭ��)
                                                            1���Զ�tuning��RXͨ����calibrationֵΪCAL_VALUE */
        unsigned long  reserved_1        : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR04_UNION;
#define ABB_CH1_REG_ANALOG_WR04_CH1_START_RC_TUNE_START  (0)
#define ABB_CH1_REG_ANALOG_WR04_CH1_START_RC_TUNE_END    (0)
#define ABB_CH1_REG_ANALOG_WR04_CH1_TX_AUTO_TUNE_START   (2)
#define ABB_CH1_REG_ANALOG_WR04_CH1_TX_AUTO_TUNE_END     (2)
#define ABB_CH1_REG_ANALOG_WR04_CH1_RX_AUTO_TUNE_START   (3)
#define ABB_CH1_REG_ANALOG_WR04_CH1_RX_AUTO_TUNE_END     (3)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR05_UNION
 �ṹ˵��  : ch1_reg_analog_wr05 �Ĵ����ṹ���塣��ַƫ����:0x73����ֵ:0x40�����:8
 �Ĵ���˵��: ADC��һ������������tuning�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH1_REG_CAP1 : 7;  /* bit[0-6]: ADC��һ������������tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR05_UNION;
#define ABB_CH1_REG_ANALOG_WR05_CH1_REG_CAP1_START  (0)
#define ABB_CH1_REG_ANALOG_WR05_CH1_REG_CAP1_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR08_UNION
 �ṹ˵��  : ch1_reg_analog_wr08 �Ĵ����ṹ���塣��ַƫ����:0x76����ֵ:0x40�����:8
 �Ĵ���˵��: DAC Tuning���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH1_TX_TUNE_D1 : 7;  /* bit[0-6]: TX_TUNE1�����ź� */
        unsigned long  reserved       : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR08_UNION;
#define ABB_CH1_REG_ANALOG_WR08_CH1_TX_TUNE_D1_START  (0)
#define ABB_CH1_REG_ANALOG_WR08_CH1_TX_TUNE_D1_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR09_UNION
 �ṹ˵��  : ch1_reg_analog_wr09 �Ĵ����ṹ���塣��ַƫ����:0x77����ֵ:0x40�����:8
 �Ĵ���˵��: DAC Tuning���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH1_TX_TUNE_D2 : 7;  /* bit[0-6]: TX_TUNE2�����ź� */
        unsigned long  reserved       : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR09_UNION;
#define ABB_CH1_REG_ANALOG_WR09_CH1_TX_TUNE_D2_START  (0)
#define ABB_CH1_REG_ANALOG_WR09_CH1_TX_TUNE_D2_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR10_UNION
 �ṹ˵��  : ch1_reg_analog_wr10 �Ĵ����ṹ���塣��ַƫ����:0x78����ֵ:0x40�����:8
 �Ĵ���˵��: DAC Tuning���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0  : 7;  /* bit[0-6]: TX_TUNE3�����ź� */
        unsigned long  reserved_1  : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR10_UNION;


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR38_UNION
 �ṹ˵��  : ch1_reg_analog_wr38 �Ĵ����ṹ���塣��ַƫ����:0x79����ֵ:0x01�����:8
 �Ĵ���˵��: ʱ�ӷ��ؿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH1_CAL_QT_EN     : 1;  /* bit[0]  : ADC������У׼ʹ�ܣ�
                                                            0��Not Cal(Ĭ��)
                                                            1��Cal */
        unsigned long  reserved_0        : 4;  /* bit[1-4]: Reserved */
        unsigned long  CH1_DCLK_INV_RX   : 1;  /* bit[5]  : ADC�����ؿ��ƣ�
                                                            0������(Ĭ��)
                                                            1������ */
        unsigned long  CH1_RX_SYN2D_CTRL : 1;  /* bit[6]  : ADC SYNC�źŲ����ؿ��ƣ�
                                                            0������(Ĭ��)
                                                            1������ */
        unsigned long  reserved_1        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR38_UNION;
#define ABB_CH1_REG_ANALOG_WR38_CH1_CAL_QT_EN_START      (0)
#define ABB_CH1_REG_ANALOG_WR38_CH1_CAL_QT_EN_END        (0)
#define ABB_CH1_REG_ANALOG_WR38_CH1_DCLK_INV_RX_START    (5)
#define ABB_CH1_REG_ANALOG_WR38_CH1_DCLK_INV_RX_END      (5)
#define ABB_CH1_REG_ANALOG_WR38_CH1_RX_SYN2D_CTRL_START  (6)
#define ABB_CH1_REG_ANALOG_WR38_CH1_RX_SYN2D_CTRL_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR39_UNION
 �ṹ˵��  : ch1_reg_analog_wr39 �Ĵ����ṹ���塣��ַƫ����:0x7A����ֵ:0x03�����:8
 �Ĵ���˵��: DUM���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0  : 1;  /* bit[0]  : Reserved */
        unsigned long  reserved_1  : 1;  /* bit[1]  : Reserved */
        unsigned long  reserved_2  : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH1_DEM_MOD : 1;  /* bit[7]  : RX DEM Mode Selection,bit 2,��ch0_reg_analog_wr00��bit3��bit0��ϳ�3bit��ʵ������9����ϣ�
                                                      000��DWA
                                                      001��CLA1
                                                      010��CLA2
                                                      011��CLA3
                                                      100��CLA4
                                                      101��CLA5
                                                      110��CLA6
                                                      111��CLA7 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR39_UNION;
#define ABB_CH1_REG_ANALOG_WR39_CH1_DEM_MOD_START  (7)
#define ABB_CH1_REG_ANALOG_WR39_CH1_DEM_MOD_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_RO0_UNION
 �ṹ˵��  : ch1_reg_analog_ro0 �Ĵ����ṹ���塣��ַƫ����:0x7B����ֵ:0x00�����:8
 �Ĵ���˵��: ��־λֻ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0   : 5;  /* bit[0-4]: Reserved */
        unsigned long  CH1_CAL_DONE : 1;  /* bit[5]  : RC Calibration Done�ź� */
        unsigned long  reserved_1   : 1;  /* bit[6]  : Reserved�� */
        unsigned long  reserved_2   : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_RO0_UNION;
#define ABB_CH1_REG_ANALOG_RO0_CH1_CAL_DONE_START  (5)
#define ABB_CH1_REG_ANALOG_RO0_CH1_CAL_DONE_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_RO1_UNION
 �ṹ˵��  : ch1_reg_analog_ro1 �Ĵ����ṹ���塣��ַƫ����:0x7C����ֵ:0x00�����:8
 �Ĵ���˵��: RCУ׼ֻ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH1_RC_TUNE_DOUT : 7;  /* bit[0-6]: RC У׼ֵ */
        unsigned long  reserved         : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_RO1_UNION;
#define ABB_CH1_REG_ANALOG_RO1_CH1_RC_TUNE_DOUT_START  (0)
#define ABB_CH1_REG_ANALOG_RO1_CH1_RC_TUNE_DOUT_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA0_UNION
 �ṹ˵��  : ch1_reg_debug_ana0 �Ĵ����ṹ���塣��ַƫ����:0x80����ֵ:0x02�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0   : 1;  /* bit[0]  : ���� */
        unsigned long  CH1_OCLK_SEL : 3;  /* bit[1-3]: ����ʱ��ѡ��
                                                       000: PLL ����� CLK��
                                                       001��ѡ��������PLL��ʱ����Ϊ����ʱ��
                                                       010��ѡ��������CLKIN_SYSTEM�����ʱ����Ϊ����ʱ��
                                                       100��ѡ��������TCXO_IN��ʱ����Ϊ����ʱ�� */
        unsigned long  reserved_1   : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA0_UNION;
#define ABB_CH1_REG_DEBUG_ANA0_CH1_OCLK_SEL_START  (1)
#define ABB_CH1_REG_DEBUG_ANA0_CH1_OCLK_SEL_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA2_UNION
 �ṹ˵��  : ch1_reg_debug_ana2 �Ĵ����ṹ���塣��ַƫ����:0x82����ֵ:0x00�����:8
 �Ĵ���˵��: PLL���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0  : 1;  /* bit[0]  : ���� */
        unsigned long  reserved_1  : 1;  /* bit[1]  : ���� */
        unsigned long  reserved_2  : 5;  /* bit[2-6]: ���� */
        unsigned long  CH1_CLKN_EN : 1;  /* bit[7]  : ����ʱ�ӿ���
                                                      1������ʱ�Ӵ�
                                                      0������ʱ�ӹر� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA2_UNION;
#define ABB_CH1_REG_DEBUG_ANA2_CH1_CLKN_EN_START  (7)
#define ABB_CH1_REG_DEBUG_ANA2_CH1_CLKN_EN_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA5_UNION
 �ṹ˵��  : ch1_reg_debug_ana5 �Ĵ����ṹ���塣��ַƫ����:0x85����ֵ:0x00�����:8
 �Ĵ���˵��: �����������ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 7;  /* bit[0-6]: Reserved */
        unsigned long  CH1_ABB_REF_FS : 1;  /* bit[7]  : ABB_REF_Fast_UP����
                                                         0���ر�(Ĭ��)
                                                         1������ */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA5_UNION;
#define ABB_CH1_REG_DEBUG_ANA5_CH1_ABB_REF_FS_START  (7)
#define ABB_CH1_REG_DEBUG_ANA5_CH1_ABB_REF_FS_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA9_UNION
 �ṹ˵��  : ch1_reg_debug_ana9 �Ĵ����ṹ���塣��ַƫ����:0x89����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0      : 1;  /* bit[0]  : Reserved */
        unsigned long  CH1_PUP_MODE    : 1;  /* bit[1]  : LTE ADCģ������ģʽѡ��
                                                          0���Զ�ģʽ
                                                          1�����üĴ���ģʽ */
        unsigned long  reserved_1      : 1;  /* bit[2]  : Reserved */
        unsigned long  CH1_DEM_ENB     : 1;  /* bit[3]  : ADC DEM���ܹر��ź�
                                                          0��DEMʹ��
                                                          1��DEM��ʹ�� */
        unsigned long  CH1_CT_TUNE_SEL : 1;  /* bit[4]  : ADCģ��Tuning���ѡ��
                                                          0��ѡ��Tuningģ��������ΪLTE ADC��Tuning��
                                                          1��ѡ��Ĵ����������ΪLTE ADC��Tuning�� */
        unsigned long  reserved_2      : 3;  /* bit[5-7]: Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA9_UNION;
#define ABB_CH1_REG_DEBUG_ANA9_CH1_PUP_MODE_START     (1)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_PUP_MODE_END       (1)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_DEM_ENB_START      (3)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_DEM_ENB_END        (3)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_CT_TUNE_SEL_START  (4)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_CT_TUNE_SEL_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA10_UNION
 �ṹ˵��  : ch1_reg_debug_ana10 �Ĵ����ṹ���塣��ַƫ����:0x8A����ֵ:0x00�����:8
 �Ĵ���˵��: ADC��λ���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH1_PUP_CTRL0 : 1;  /* bit[0]: ADC��DACģ��Powerup����
                                                      0��Powerdown
                                                      1��Powerup */
        unsigned long  CH1_PUP_CTRL1 : 1;  /* bit[1]: ADC��OP23ģ��Powerup����
                                                      0��Powerdown
                                                      1��Powerup */
        unsigned long  CH1_PUP_CTRL2 : 1;  /* bit[2]: ADC��OP1 OffsetУ׼�����ź�
                                                      0��У׼������
                                                      1������OP1 OffsetУ׼ */
        unsigned long  CH1_PUP_CTRL3 : 1;  /* bit[3]: ADC��CKGEN_QUģ��Powerup����
                                                      0��Powerdown
                                                      1��Powerup */
        unsigned long  CH1_PUP_CTRL4 : 1;  /* bit[4]: ADC��QUģ��Powerup����
                                                      0��Powerdown
                                                      1��Powerup */
        unsigned long  CH1_PUP_CTRL5 : 1;  /* bit[5]: ADC��OP1 OffsetУ׼������̽ӿ��ؿ���
                                                      0������̽ӿ��ضϿ�����������ģʽ��
                                                      1������̽ӿ��رպϣ����˷�����˶̽ӵ���ģ��ѹ�� */
        unsigned long  CH1_PUP_CTRL6 : 1;  /* bit[6]: ADC��OP1ģ��Powerup����
                                                      0��Powerdown
                                                      1��Powerup */
        unsigned long  CH1_PUP_CTRL7 : 1;  /* bit[7]: ADC��RST_CAP����
                                                      0��Reset CAP123
                                                      1����Reset CAP123 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA10_UNION;
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL0_START  (0)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL0_END    (0)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL1_START  (1)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL1_END    (1)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL2_START  (2)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL2_END    (2)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL3_START  (3)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL3_END    (3)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL4_START  (4)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL4_END    (4)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL5_START  (5)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL5_END    (5)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL6_START  (6)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL6_END    (6)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL7_START  (7)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_PUP_CTRL7_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA14_UNION
 �ṹ˵��  : ch1_reg_debug_ana14 �Ĵ����ṹ���塣��ַƫ����:0x8E����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH1_OL_CT   : 3;  /* bit[0-2]: ADC Overloadģ������
                                                      00��16����������������С��
                                                      01��8����������������С��
                                                      10��4����������������С��
                                                      11���ر�Overload��� */
        unsigned long  reserved_0  : 3;  /* bit[3-5]: Reserved */
        unsigned long  reserved_1  : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA14_UNION;
#define ABB_CH1_REG_DEBUG_ANA14_CH1_OL_CT_START    (0)
#define ABB_CH1_REG_DEBUG_ANA14_CH1_OL_CT_END      (2)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA16_UNION
 �ṹ˵��  : ch1_reg_debug_ana16 �Ĵ����ṹ���塣��ַƫ����:0x90����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0   : 6;  /* bit[0-5]: Reserved */
        unsigned long  reserved_1   : 1;  /* bit[6]  : Reserved */
        unsigned long  CH1_PDM_CTRL : 1;  /* bit[7]  : RX���PDM�������
                                                       0��adder encoder���ӷ��������
                                                       1��de-bubble encoder��������������� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA16_UNION;
#define ABB_CH1_REG_DEBUG_ANA16_CH1_PDM_CTRL_START  (7)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_PDM_CTRL_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA17_UNION
 �ṹ˵��  : ch1_reg_debug_ana17 �Ĵ����ṹ���塣��ַƫ����:0x91����ֵ:0x00�����:8
 �Ĵ���˵��: PLL���ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0  : 4;  /* bit[0-3]: Reserved */
        unsigned long  reserved_1  : 2;  /* bit[4-5]: Reserved */
        unsigned long  reserved_2  : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA17_UNION;


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA19_UNION
 �ṹ˵��  : ch1_reg_debug_ana19 �Ĵ����ṹ���塣��ַƫ����:0x93����ֵ:0x33�����:8
 �Ĵ���˵��: ʱ��ʹ�ܿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 4;  /* bit[0-3]: ���� */
        unsigned long  CH1_DAC_CLK_EN : 1;  /* bit[4]  : PLLģ��312MHzʱ��ʹ���ź�
                                                         0��ʱ�ӹر�
                                                         1��ʱ��ʹ�� */
        unsigned long  CH1_ADC_CLK_EN : 1;  /* bit[5]  : PLLģ��307.2MHzʱ��ʹ���ź�
                                                         0��ʱ�ӹر�
                                                         1��ʱ��ʹ�� */
        unsigned long  reserved_1     : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA19_UNION;
#define ABB_CH1_REG_DEBUG_ANA19_CH1_DAC_CLK_EN_START  (4)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_DAC_CLK_EN_END    (4)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_ADC_CLK_EN_START  (5)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_ADC_CLK_EN_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA20_UNION
 �ṹ˵��  : ch1_reg_debug_ana20 �Ĵ����ṹ���塣��ַƫ����:0x94����ֵ:0x40�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : ���� */
        unsigned long  reserved_1     : 1;  /* bit[1]  : ���� */
        unsigned long  reserved_2     : 1;  /* bit[2]  : ���� */
        unsigned long  reserved_3     : 2;  /* bit[3-4]: Reserved */
        unsigned long  CH1_CAP3_MULTI : 2;  /* bit[5-6]: ADC���������ݱ���ϵ��
                                                         00��X1(Ĭ��)
                                                         01��X1.5
                                                         10��X1.25
                                                         11��X1.125 */
        unsigned long  reserved_4     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA20_UNION;
#define ABB_CH1_REG_DEBUG_ANA20_CH1_CAP3_MULTI_START  (5)
#define ABB_CH1_REG_DEBUG_ANA20_CH1_CAP3_MULTI_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA22_UNION
 �ṹ˵��  : ch1_reg_debug_ana22 �Ĵ����ṹ���塣��ַƫ����:0x96����ֵ:0x40�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH1_RX_TUNE : 7;  /* bit[0-6]: RXģ���Զ�Tuning code����ֵ */
        unsigned long  reserved    : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA22_UNION;
#define ABB_CH1_REG_DEBUG_ANA22_CH1_RX_TUNE_START  (0)
#define ABB_CH1_REG_DEBUG_ANA22_CH1_RX_TUNE_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA25_UNION
 �ṹ˵��  : ch1_reg_debug_ana25 �Ĵ����ṹ���塣��ַƫ����:0x99����ֵ:0x06�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH1_CALOP1_IB_CTRL : 1;  /* bit[0]  : ADC��OP1 DC OffsetУ׼��ƫ�õ���ѡ��
                                                             0��5uA��Ĭ��У׼��Χ
                                                             1��10uA��У׼��Χ�ӱ� */
        unsigned long  CH1_CAL_OP1_EN     : 1;  /* bit[1]  : ADC��OP1 DC OffsetУ׼ʹ���ź�
                                                             0����ʹ��У׼
                                                             1��ʹ��У׼ */
        unsigned long  CH1_CALOP1_TRIM_SW : 1;  /* bit[2]  : ADC��OP1 DC OffsetУ׼ϵͳ��������
                                                             0��������ϵͳ���
                                                             1������ϵͳ��� */
        unsigned long  CH1_OP1CAL_CKCTR   : 2;  /* bit[3-4]: ADC��OP1 DC OffsetУ׼ʱ��Ƶ�ʿ���
                                                             00��6.4MHz
                                                             01��3.2MHz
                                                             10��9.6MHz
                                                             11��4.8MHz */
        unsigned long  CH1_OP3_IB_SW      : 1;  /* bit[5]  : ADC��OP3���뼶β�����ܼӴ�ߴ���ƣ�debug��
                                                             0��Ĭ����Ŀ
                                                             1������β��������Ŀ */
        unsigned long  CH1_PUP_CK_CTRL    : 1;  /* bit[6]  : ADC Pupģ���Ƶʱ����Pup������ɺ���Ƿ������ת�Ŀ���λ
                                                             0������ת
                                                             1��������ת */
        unsigned long  reserved           : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA25_UNION;
#define ABB_CH1_REG_DEBUG_ANA25_CH1_CALOP1_IB_CTRL_START  (0)
#define ABB_CH1_REG_DEBUG_ANA25_CH1_CALOP1_IB_CTRL_END    (0)
#define ABB_CH1_REG_DEBUG_ANA25_CH1_CAL_OP1_EN_START      (1)
#define ABB_CH1_REG_DEBUG_ANA25_CH1_CAL_OP1_EN_END        (1)
#define ABB_CH1_REG_DEBUG_ANA25_CH1_CALOP1_TRIM_SW_START  (2)
#define ABB_CH1_REG_DEBUG_ANA25_CH1_CALOP1_TRIM_SW_END    (2)
#define ABB_CH1_REG_DEBUG_ANA25_CH1_OP1CAL_CKCTR_START    (3)
#define ABB_CH1_REG_DEBUG_ANA25_CH1_OP1CAL_CKCTR_END      (4)
#define ABB_CH1_REG_DEBUG_ANA25_CH1_OP3_IB_SW_START       (5)
#define ABB_CH1_REG_DEBUG_ANA25_CH1_OP3_IB_SW_END         (5)
#define ABB_CH1_REG_DEBUG_ANA25_CH1_PUP_CK_CTRL_START     (6)
#define ABB_CH1_REG_DEBUG_ANA25_CH1_PUP_CK_CTRL_END       (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA26_UNION
 �ṹ˵��  : ch1_reg_debug_ana26 �Ĵ����ṹ���塣��ַƫ����:0x9A����ֵ:0x00�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved     : 2;  /* bit[0-1]: Reserved */
        unsigned long  CH1_REG_EXT2 : 3;  /* bit[2-4]: ADC������2���ݿ����룬ΪFF Corner׼���Ķ��ⲹ���� */
        unsigned long  CH1_REG_EXT1 : 3;  /* bit[5-7]: ADC������1���ݿ����룬ΪFF Corner׼���Ķ��ⲹ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA26_UNION;
#define ABB_CH1_REG_DEBUG_ANA26_CH1_REG_EXT2_START  (2)
#define ABB_CH1_REG_DEBUG_ANA26_CH1_REG_EXT2_END    (4)
#define ABB_CH1_REG_DEBUG_ANA26_CH1_REG_EXT1_START  (5)
#define ABB_CH1_REG_DEBUG_ANA26_CH1_REG_EXT1_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ARO0_UNION
 �ṹ˵��  : ch1_reg_debug_aro0 �Ĵ����ṹ���塣��ַƫ����:0x9B����ֵ:0x00�����:8
 �Ĵ���˵��: ģ�����ֻ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved            : 6;  /* bit[0-5]: Reserved */
        unsigned long  CH1_RXA_OP1_CALOK_Q : 1;  /* bit[6]  : RXA Qͨ��OP1 OffsetУ���Ƿ������־λ
                                                              0��δ���
                                                              1��У׼��� */
        unsigned long  CH1_RXA_OP1_CALOK_I : 1;  /* bit[7]  : RXA Iͨ��OP1 OffsetУ���Ƿ������־λ
                                                              0��δ���
                                                              1��У׼��� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ARO0_UNION;
#define ABB_CH1_REG_DEBUG_ARO0_CH1_RXA_OP1_CALOK_Q_START  (6)
#define ABB_CH1_REG_DEBUG_ARO0_CH1_RXA_OP1_CALOK_Q_END    (6)
#define ABB_CH1_REG_DEBUG_ARO0_CH1_RXA_OP1_CALOK_I_START  (7)
#define ABB_CH1_REG_DEBUG_ARO0_CH1_RXA_OP1_CALOK_I_END    (7)


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
 �ṹ��    : ABB_CH0_CFR_CTRL_UNION
 �ṹ˵��  : ch0_cfr_ctrl �Ĵ����ṹ���塣��ַƫ����:0xA3����ֵ:0x44�����:8
 �Ĵ���˵��: CFR��ֵ��ⴰ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_cfr_pdet_sel : 2;  /* bit[0-1]: CFR��ֵ��ⷽʽ��
                                                           00���������
                                                           01���������
                                                           10���������
                                                           11��ȫ����ֵ
                                                           ��V8R1���漰�� */
        unsigned long  ch0_cfr_fir_sel  : 1;  /* bit[2]  : CFR�˲���ѡ��
                                                           0��bypass�˲���
                                                           1����bypass�˲���
                                                           ��V8R1���漰�� */
        unsigned long  reserved         : 1;  /* bit[3]  : ���� */
        unsigned long  ch0_cfr_fir_fac  : 4;  /* bit[4-7]: CFR�������ӣ�V8R1���漰�� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CFR_CTRL_UNION;
#define ABB_CH0_CFR_CTRL_ch0_cfr_pdet_sel_START  (0)
#define ABB_CH0_CFR_CTRL_ch0_cfr_pdet_sel_END    (1)
#define ABB_CH0_CFR_CTRL_ch0_cfr_fir_sel_START   (2)
#define ABB_CH0_CFR_CTRL_ch0_cfr_fir_sel_END     (2)
#define ABB_CH0_CFR_CTRL_ch0_cfr_fir_fac_START   (4)
#define ABB_CH0_CFR_CTRL_ch0_cfr_fir_fac_END     (7)


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
 �ṹ˵��  : ch0_reg_debug_dig0 �Ĵ����ṹ���塣��ַƫ����:0xCB����ֵ:0x24�����:8
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
        unsigned long  ch0_sdm_sel       : 1;  /* bit[6]  : TXͨ��������ѡ��comstarV520 Reserved
                                                            0��5�׵�����(for V510)
                                                            1��1�׵�����(for V511) */
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
#define ABB_CH0_REG_DEBUG_DIG0_ch0_sdm_sel_START        (6)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_sdm_sel_END          (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR02_UNION
 �ṹ˵��  : ch0_reg_analog_wr02 �Ĵ����ṹ���塣��ַƫ����:0xD0����ֵ:0x0F�����:8
 �Ĵ���˵��: Power Down���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 2;  /* bit[0-1]: Reserved */
        unsigned long  CH0_PLL624_PD  : 1;  /* bit[2]  : GPLL Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��) */
        unsigned long  CH0_PLL6144_PD : 1;  /* bit[3]  : WPLL Power Down����
                                                         0��Power On(Ĭ��)
                                                         1��Power Down */
        unsigned long  reserved_1     : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR02_UNION;
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL624_PD_START   (2)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL624_PD_END     (2)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL6144_PD_START  (3)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL6144_PD_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR03_UNION
 �ṹ˵��  : ch0_reg_analog_wr03 �Ĵ����ṹ���塣��ַƫ����:0xD1����ֵ:0x00�����:8
 �Ĵ���˵��: ��ģ�ӿ�ʱ�ӿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 2;  /* bit[0-1]: Reserved */
        unsigned long  reserved_1     : 1;  /* bit[2]  : ���� */
        unsigned long  reserved_2     : 1;  /* bit[3]  : ���� */
        unsigned long  LDO_BP         : 1;  /* bit[4]  : LDO BYPASS
                                                         0����������
                                                         1��BYPASS */
        unsigned long  CH0_CLK104M_PD : 1;  /* bit[5]  : CLK_104M Power Down����
                                                         0��Power On(Ĭ��)
                                                         1��Power Down */
        unsigned long  CH0_CLK122M_PD : 1;  /* bit[6]  : CLK_122M Power Down����
                                                         0��Power On(Ĭ��)
                                                         1��Power Down */
        unsigned long  reserved_3     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR03_UNION;
#define ABB_CH0_REG_ANALOG_WR03_LDO_BP_START          (4)
#define ABB_CH0_REG_ANALOG_WR03_LDO_BP_END            (4)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK104M_PD_START  (5)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK104M_PD_END    (5)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK122M_PD_START  (6)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK122M_PD_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR04_UNION
 �ṹ˵��  : ch0_reg_analog_wr04 �Ĵ����ṹ���塣��ַƫ����:0xD2����ֵ:0x0C�����:8
 �Ĵ���˵��: Other���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  START_RC_TUNE    : 1;  /* bit[0]  : RC TUNE����
                                                           ����������RC У׼���� */
        unsigned long  reserved_0       : 1;  /* bit[1]  : Reserved */
        unsigned long  CH0_TX_AUTO_TUNE : 1;  /* bit[2]  : TX ADC�Զ�tuning����
                                                           0���ֶ�tuning��tuningѡ��TX_TUNE1,TX_TUNE2,TX_TUNE3��ֵ(Ĭ��)
                                                           1���Զ�tuning��TXͨ����calibrationֵΪCAL_VALUE */
        unsigned long  CH0_RX_AUTO_TUNE : 1;  /* bit[3]  : RX ADC�Զ�tuning����
                                                           0���ֶ�tuning��tuningѡ��RX_TUNE1,RX_TUNE2,RX_TUNE3��ֵ(Ĭ��)
                                                           1���Զ�tuning��RXͨ����calibrationֵΪCAL_VALUE */
        unsigned long  reserved_1       : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR04_UNION;
#define ABB_CH0_REG_ANALOG_WR04_START_RC_TUNE_START     (0)
#define ABB_CH0_REG_ANALOG_WR04_START_RC_TUNE_END       (0)
#define ABB_CH0_REG_ANALOG_WR04_CH0_TX_AUTO_TUNE_START  (2)
#define ABB_CH0_REG_ANALOG_WR04_CH0_TX_AUTO_TUNE_END    (2)
#define ABB_CH0_REG_ANALOG_WR04_CH0_RX_AUTO_TUNE_START  (3)
#define ABB_CH0_REG_ANALOG_WR04_CH0_RX_AUTO_TUNE_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR05_UNION
 �ṹ˵��  : ch0_reg_analog_wr05 �Ĵ����ṹ���塣��ַƫ����:0xD3����ֵ:0x40�����:8
 �Ĵ���˵��: ADC��һ������������tuning�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_REG_CAP1 : 7;  /* bit[0-6]: ADC��һ������������tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR05_UNION;
#define ABB_CH0_REG_ANALOG_WR05_CH0_REG_CAP1_START  (0)
#define ABB_CH0_REG_ANALOG_WR05_CH0_REG_CAP1_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR08_UNION
 �ṹ˵��  : ch0_reg_analog_wr08 �Ĵ����ṹ���塣��ַƫ����:0xD6����ֵ:0x40�����:8
 �Ĵ���˵��: DAC Tuning���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_TX_TUNE_D1 : 7;  /* bit[0-6]: TX_TUNE1�����ź� */
        unsigned long  reserved       : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR08_UNION;
#define ABB_CH0_REG_ANALOG_WR08_CH0_TX_TUNE_D1_START  (0)
#define ABB_CH0_REG_ANALOG_WR08_CH0_TX_TUNE_D1_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR09_UNION
 �ṹ˵��  : ch0_reg_analog_wr09 �Ĵ����ṹ���塣��ַƫ����:0xD7����ֵ:0x40�����:8
 �Ĵ���˵��: DAC Tuning���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_TX_TUNE_D2 : 7;  /* bit[0-6]: TX_TUNE2�����ź� */
        unsigned long  reserved       : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR09_UNION;
#define ABB_CH0_REG_ANALOG_WR09_CH0_TX_TUNE_D2_START  (0)
#define ABB_CH0_REG_ANALOG_WR09_CH0_TX_TUNE_D2_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR10_UNION
 �ṹ˵��  : ch0_reg_analog_wr10 �Ĵ����ṹ���塣��ַƫ����:0xD8����ֵ:0x40�����:8
 �Ĵ���˵��: DAC Tuning���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_TX_TUNE3 : 7;  /* bit[0-6]: TX_TUNE3�����ź� */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR10_UNION;
#define ABB_CH0_REG_ANALOG_WR10_CH0_TX_TUNE3_START  (0)
#define ABB_CH0_REG_ANALOG_WR10_CH0_TX_TUNE3_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR38_UNION
 �ṹ˵��  : ch0_reg_analog_wr38 �Ĵ����ṹ���塣��ַƫ����:0xD9����ֵ:0x01�����:8
 �Ĵ���˵��: ʱ�ӷ��ؿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CAL_QT_EN         : 1;  /* bit[0]  : ADC������У׼ʹ�ܣ�
                                                            0��Not Cal(Ĭ��)
                                                            1��Cal */
        unsigned long  reserved_0        : 1;  /* bit[1]  : Reserved */
        unsigned long  reserved_1        : 3;  /* bit[2-4]: Reserved */
        unsigned long  DCLK_INV_RX       : 1;  /* bit[5]  : ADC�����ؿ��ƣ�
                                                            0������(Ĭ��)
                                                            1������ */
        unsigned long  CH0_RX_SYN2D_CTRL : 1;  /* bit[6]  : ADC SYNC�źŲ����ؿ��ƣ�
                                                            0������(Ĭ��)
                                                            1������ */
        unsigned long  reserved_2        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR38_UNION;
#define ABB_CH0_REG_ANALOG_WR38_CAL_QT_EN_START          (0)
#define ABB_CH0_REG_ANALOG_WR38_CAL_QT_EN_END            (0)
#define ABB_CH0_REG_ANALOG_WR38_DCLK_INV_RX_START        (5)
#define ABB_CH0_REG_ANALOG_WR38_DCLK_INV_RX_END          (5)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_SYN2D_CTRL_START  (6)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_SYN2D_CTRL_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR39_UNION
 �ṹ˵��  : ch0_reg_analog_wr39 �Ĵ����ṹ���塣��ַƫ����:0xDA����ֵ:0x03�����:8
 �Ĵ���˵��: DUM���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0  : 1;  /* bit[0]  : Reserved */
        unsigned long  reserved_1  : 1;  /* bit[1]  : Reserved */
        unsigned long  reserved_2  : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH0_DEM_MOD : 1;  /* bit[7]  : RX DEM Mode Selection,bit 2,��ch0_reg_analog_wr00��bit3��bit0��ϳ�3bit��ʵ������9����ϣ�
                                                      000��DWA
                                                      001��CLA1
                                                      010��CLA2
                                                      011��CLA3
                                                      100��CLA4
                                                      101��CLA5
                                                      110��CLA6
                                                      111��CLA7 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR39_UNION;
#define ABB_CH0_REG_ANALOG_WR39_CH0_DEM_MOD_START  (7)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DEM_MOD_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_RO0_UNION
 �ṹ˵��  : ch0_reg_analog_ro0 �Ĵ����ṹ���塣��ַƫ����:0xDB����ֵ:0x00�����:8
 �Ĵ���˵��: ��־λֻ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved     : 5;  /* bit[0-4]: Reserved */
        unsigned long  CH0_CAL_DONE : 1;  /* bit[5]  : RC Calibration Done�ź� */
        unsigned long  CH0_LOCK2    : 1;  /* bit[6]  : GPLL��LOCK�ź� */
        unsigned long  CH0_LOCK1    : 1;  /* bit[7]  : WPLL��LOCK�ź� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_RO0_UNION;
#define ABB_CH0_REG_ANALOG_RO0_CH0_CAL_DONE_START  (5)
#define ABB_CH0_REG_ANALOG_RO0_CH0_CAL_DONE_END    (5)
#define ABB_CH0_REG_ANALOG_RO0_CH0_LOCK2_START     (6)
#define ABB_CH0_REG_ANALOG_RO0_CH0_LOCK2_END       (6)
#define ABB_CH0_REG_ANALOG_RO0_CH0_LOCK1_START     (7)
#define ABB_CH0_REG_ANALOG_RO0_CH0_LOCK1_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_RO1_UNION
 �ṹ˵��  : ch0_reg_analog_ro1 �Ĵ����ṹ���塣��ַƫ����:0xDC����ֵ:0x00�����:8
 �Ĵ���˵��: RCУ׼ֻ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RX_CAL_VALUE : 7;  /* bit[0-6]: RC CalibrationУ׼ֵ */
        unsigned long  reserved         : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_RO1_UNION;
#define ABB_CH0_REG_ANALOG_RO1_CH0_RX_CAL_VALUE_START  (0)
#define ABB_CH0_REG_ANALOG_RO1_CH0_RX_CAL_VALUE_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA0_UNION
 �ṹ˵��  : ch0_reg_debug_ana0 �Ĵ����ṹ���塣��ַƫ����:0xE0����ֵ:0x42�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_FREF_SEL : 1;  /* bit[0]  : PLL�Ĳο�ʱ��ѡ��
                                                       1��TCXO_INP��ΪPLL�Ĳο�ʱ��
                                                       0��TCXO Buffer�����ΪPLL�ο�ʱ�� */
        unsigned long  CH0_OCLK_SEL : 3;  /* bit[1-3]: ����ʱ��ѡ��
                                                       000: PLL ����� CLK��
                                                       001��ѡ��������PLL��ʱ����Ϊ����ʱ��
                                                       010��ѡ��������CLKIN_SYSTEM�����ʱ����Ϊ����ʱ��
                                                       100��ѡ��������TCXO_IN��ʱ����Ϊ����ʱ�� */
        unsigned long  CP_ADN       : 1;  /* bit[4]  : PLL��Ƶ����������
                                                       0����Ƶ��������������
                                                       1����Ƶ������һֱ���Down�ź� */
        unsigned long  CP_AUP       : 1;  /* bit[5]  : PLL��Ƶ����������
                                                       0����Ƶ��������������
                                                       1����Ƶ������һֱ���UP�ź� */
        unsigned long  CH0_GVCO_CR  : 2;  /* bit[6-7]: GPLL VCO Current����
                                                       00��X1.2
                                                       01��X1.1(Ĭ��)
                                                       10��X1.1
                                                       11��X1.0 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA0_UNION;
#define ABB_CH0_REG_DEBUG_ANA0_CH0_FREF_SEL_START  (0)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_FREF_SEL_END    (0)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_OCLK_SEL_START  (1)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_OCLK_SEL_END    (3)
#define ABB_CH0_REG_DEBUG_ANA0_CP_ADN_START        (4)
#define ABB_CH0_REG_DEBUG_ANA0_CP_ADN_END          (4)
#define ABB_CH0_REG_DEBUG_ANA0_CP_AUP_START        (5)
#define ABB_CH0_REG_DEBUG_ANA0_CP_AUP_END          (5)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_GVCO_CR_START   (6)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_GVCO_CR_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA1_UNION
 �ṹ˵��  : ch0_reg_debug_ana1 �Ĵ����ṹ���塣��ַƫ����:0xE1����ֵ:0x7A�����:8
 �Ĵ���˵��: PLL LOCK���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_GLK_CTRL : 2;  /* bit[0-1]: GPLL����Cycle����
                                                       00��4
                                                       01��8
                                                       10��16(Ĭ��)
                                                       11��32 */
        unsigned long  CH0_WLK_CTRL : 2;  /* bit[2-3]: WPLL����Cycle����
                                                       00��4
                                                       01��8
                                                       10��16(Ĭ��)
                                                       11��32 */
        unsigned long  CH0_GLK_EN   : 1;  /* bit[4]  : GPLL�������ʹ��
                                                       0�����������ź�
                                                       1���������ź� */
        unsigned long  CH0_WLK_EN   : 1;  /* bit[5]  : WPLL�������ʹ��
                                                       0�����������ź�
                                                       1���������ź� */
        unsigned long  CH0_WVCO_CR  : 2;  /* bit[6-7]: WPLL VCO Current����
                                                       00��X0.7
                                                       01��X1(Ĭ��)
                                                       10��X1
                                                       11��X1.3 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA1_UNION;
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GLK_CTRL_START  (0)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GLK_CTRL_END    (1)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WLK_CTRL_START  (2)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WLK_CTRL_END    (3)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GLK_EN_START    (4)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GLK_EN_END      (4)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WLK_EN_START    (5)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WLK_EN_END      (5)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WVCO_CR_START   (6)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WVCO_CR_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA2_UNION
 �ṹ˵��  : ch0_reg_debug_ana2 �Ĵ����ṹ���塣��ַƫ����:0xE2����ֵ:0x00�����:8
 �Ĵ���˵��: PLL���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_GCP_PD  : 1;  /* bit[0]  : GPLL CP PowerDown���ƣ�������
                                                      0����������
                                                      1��PowerDown GPLL CP  */
        unsigned long  CH1_WCP_PD  : 1;  /* bit[1]  : WPLL CP PowerDown���ƣ�������
                                                      0����������
                                                      1��PowerDown WPLL CP  */
        unsigned long  reserved    : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH0_CLKN_EN : 1;  /* bit[7]  : ����ʱ�ӿ���
                                                      1������ʱ�Ӵ�
                                                      0������ʱ�ӹر� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA2_UNION;
#define ABB_CH0_REG_DEBUG_ANA2_CH0_GCP_PD_START   (0)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_GCP_PD_END     (0)
#define ABB_CH0_REG_DEBUG_ANA2_CH1_WCP_PD_START   (1)
#define ABB_CH0_REG_DEBUG_ANA2_CH1_WCP_PD_END     (1)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_CLKN_EN_START  (7)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_CLKN_EN_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA3_UNION
 �ṹ˵��  : ch0_reg_debug_ana3 �Ĵ����ṹ���塣��ַƫ����:0xE3����ֵ:0x30�����:8
 �Ĵ���˵��: PLL���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved     : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_GIB_CTRL : 4;  /* bit[4-7]: GPLL��ɱõ�������(����Ч)
                                                       0000��4u
                                                       0001��6u
                                                       0010��8u
                                                       0011��10u(Ĭ��)
                                                       0100��12u
                                                       0101��14u
                                                       0110��16u
                                                       0111��18u
                                                       ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA3_UNION;
#define ABB_CH0_REG_DEBUG_ANA3_CH0_GIB_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA3_CH0_GIB_CTRL_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA4_UNION
 �ṹ˵��  : ch0_reg_debug_ana4 �Ĵ����ṹ���塣��ַƫ����:0xE4����ֵ:0x30�����:8
 �Ĵ���˵��: PLL���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved     : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_WIB_CTRL : 4;  /* bit[4-7]: WPLL��ɱõ�������(����Ч)
                                                       0000��4u
                                                       0001��6u
                                                       0010��8u
                                                       0011��10u(Ĭ��)
                                                       0100��12u
                                                       0101��14u
                                                       0110��16u
                                                       0111��18u
                                                       ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA4_UNION;
#define ABB_CH0_REG_DEBUG_ANA4_CH0_WIB_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA4_CH0_WIB_CTRL_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA5_UNION
 �ṹ˵��  : ch0_reg_debug_ana5 �Ĵ����ṹ���塣��ַƫ����:0xE5����ֵ:0x00�����:8
 �Ĵ���˵��: �����������ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved     : 7;  /* bit[0-6]: Reserved */
        unsigned long  CH0_BG_FS_EN : 1;  /* bit[7]  : ABB_REF_Fast_UP����
                                                       0���ر�(Ĭ��)
                                                       1������ */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA5_UNION;
#define ABB_CH0_REG_DEBUG_ANA5_CH0_BG_FS_EN_START  (7)
#define ABB_CH0_REG_DEBUG_ANA5_CH0_BG_FS_EN_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA6_UNION
 �ṹ˵��  : ch0_reg_debug_ana6 �Ĵ����ṹ���塣��ַƫ����:0xE6����ֵ:0x68�����:8
 �Ĵ���˵��: Bandgap��TCXO���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_GFREF_SEL : 2;  /* bit[0-1]: GPLL����ʱ��Ƶ��ѡ��
                                                        00��19.2M(Ĭ��)
                                                        01��26M
                                                        10��38.4M
                                                        11��52M */
        unsigned long  CH0_WFREF_SEL : 2;  /* bit[2-3]: WPLL����ʱ��Ƶ��ѡ��
                                                        00��38.4M
                                                        01��76.8M
                                                        10��19.2M(Ĭ��)
                                                        11��38.4M */
        unsigned long  CH0_TCXO_DRV  : 2;  /* bit[4-5]: TCXO BUFFER��������
                                                        00��1x
                                                        01��2x
                                                        10��3x(Ĭ��)
                                                        11��4x */
        unsigned long  CH0_EXCLK_PD  : 1;  /* bit[6]  : TEST EX_CLK INPUT PD����
                                                        0������
                                                        1���ر� */
        unsigned long  reserved      : 1;  /* bit[7]  : reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA6_UNION;
#define ABB_CH0_REG_DEBUG_ANA6_CH0_GFREF_SEL_START  (0)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_GFREF_SEL_END    (1)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_WFREF_SEL_START  (2)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_WFREF_SEL_END    (3)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_TCXO_DRV_START   (4)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_TCXO_DRV_END     (5)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_EXCLK_PD_START   (6)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_EXCLK_PD_END     (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA7_UNION
 �ṹ˵��  : ch0_reg_debug_ana7 �Ĵ����ṹ���塣��ַƫ����:0xE7����ֵ:0x00�����:8
 �Ĵ���˵��: �������ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_ITR_ADC_BUF : 3;  /* bit[0-2]: L/W/G ����ADC ���buffer�������ڿ���
                                                          000��5u
                                                          001��4u
                                                          010��3u
                                                          011��2u
                                                          100��9u
                                                          101��8u
                                                          110��7u
                                                          111��6u */
        unsigned long  ITR_VCM_BIAS    : 3;  /* bit[3-5]: L/W/G ����ADC ���buffer�������ڿ���
                                                          000��5u
                                                          001��4u
                                                          010��3u
                                                          011��2u
                                                          100��9u
                                                          101��8u
                                                          110��7u
                                                          111��6u */
        unsigned long  reserved        : 2;  /* bit[6-7]: reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA7_UNION;
#define ABB_CH0_REG_DEBUG_ANA7_CH0_ITR_ADC_BUF_START  (0)
#define ABB_CH0_REG_DEBUG_ANA7_CH0_ITR_ADC_BUF_END    (2)
#define ABB_CH0_REG_DEBUG_ANA7_ITR_VCM_BIAS_START     (3)
#define ABB_CH0_REG_DEBUG_ANA7_ITR_VCM_BIAS_END       (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA8_UNION
 �ṹ˵��  : ch0_reg_debug_ana8 �Ĵ����ṹ���塣��ַƫ����:0xE8����ֵ:0x00�����:8
 �Ĵ���˵��: �������ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0   : 5;  /* bit[0-4]: Reserved */
        unsigned long  reserved_1   : 3;  /* bit[5-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA8_UNION;


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA9_UNION
 �ṹ˵��  : ch0_reg_debug_ana9 �Ĵ����ṹ���塣��ַƫ����:0xE9����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0      : 1;  /* bit[0]  : Reserved */
        unsigned long  CH0_PUP_MODE    : 1;  /* bit[1]  : LTE ADCģ������ģʽѡ��
                                                          0���Զ�ģʽ
                                                          1�����üĴ���ģʽ */
        unsigned long  reserved_1      : 1;  /* bit[2]  : Reserved */
        unsigned long  CH0_DEM_ENB     : 1;  /* bit[3]  : ADC DEM���ܹر��ź�
                                                          0��DEMʹ��
                                                          1��DEM��ʹ�� */
        unsigned long  CH0_CT_TUNE_SEL : 1;  /* bit[4]  : ADCģ��Tuning���ѡ��
                                                          0��ѡ��Tuningģ��������ΪLTE ADC��Tuning��
                                                          1��ѡ��Ĵ����������ΪLTE ADC��Tuning�� */
        unsigned long  reserved_2      : 3;  /* bit[5-7]: Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA9_UNION;
#define ABB_CH0_REG_DEBUG_ANA9_CH0_PUP_MODE_START     (1)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_PUP_MODE_END       (1)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_DEM_ENB_START      (3)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_DEM_ENB_END        (3)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_CT_TUNE_SEL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_CT_TUNE_SEL_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA10_UNION
 �ṹ˵��  : ch0_reg_debug_ana10 �Ĵ����ṹ���塣��ַƫ����:0xEA����ֵ:0x00�����:8
 �Ĵ���˵��: ADC��λ���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_PUP_CTRL0 : 1;  /* bit[0]: ADC��DACģ��Powerup����
                                                      0��Powerdown
                                                      1��Powerup */
        unsigned long  CH0_PUP_CTRL1 : 1;  /* bit[1]: ADC��OP23ģ��Powerup����
                                                      0��Powerdown
                                                      1��Powerup */
        unsigned long  CH0_PUP_CTRL2 : 1;  /* bit[2]: ADC��OP1 OffsetУ׼�����ź�
                                                      0��У׼������
                                                      1������OP1 OffsetУ׼ */
        unsigned long  CH0_PUP_CTRL3 : 1;  /* bit[3]: ADC��CKGEN_QUģ��Powerup����
                                                      0��Powerdown
                                                      1��Powerup */
        unsigned long  CH0_PUP_CTRL4 : 1;  /* bit[4]: ADC��QUģ��Powerup����
                                                      0��Powerdown
                                                      1��Powerup */
        unsigned long  CH0_PUP_CTRL5 : 1;  /* bit[5]: ADC��OP1 OffsetУ׼������̽ӿ��ؿ���
                                                      0������̽ӿ��ضϿ�����������ģʽ��
                                                      1������̽ӿ��رպϣ����˷�����˶̽ӵ���ģ��ѹ�� */
        unsigned long  CH0_PUP_CTRL6 : 1;  /* bit[6]: ADC��OP1ģ��Powerup����
                                                      0��Powerdown
                                                      1��Powerup */
        unsigned long  CH0_PUP_CTRL7 : 1;  /* bit[7]: ADC��RST_CAP����
                                                      0��Reset CAP123
                                                      1����Reset CAP123 */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA10_UNION;
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL0_START  (0)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL0_END    (0)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL1_START  (1)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL1_END    (1)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL2_START  (2)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL2_END    (2)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL3_START  (3)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL3_END    (3)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL4_START  (4)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL4_END    (4)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL5_START  (5)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL5_END    (5)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL6_START  (6)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL6_END    (6)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL7_START  (7)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_PUP_CTRL7_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA11_UNION
 �ṹ˵��  : ch0_reg_debug_ana11 �Ĵ����ṹ���塣��ַƫ����:0xEB����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved    : 6;  /* bit[0-5]: Reserved */
        unsigned long  CH0_BG_EN   : 1;  /* bit[6]  : Refence��ѹģ��ǿ��EN�ź�
                                                      0�� Reference��ѹģ��״̬��BG_PD�źż�����ģ��PD�ź��Զ�����
                                                      1�� ��BG_PD�ź�Ϊ0ʱ��Reference��ѹģ��ǿ������ */
        unsigned long  CH0_BG_PD   : 1;  /* bit[7]  : Refence��ѹģ��ǿ��PD�ź�
                                                      0�� Reference��ѹģ��״̬��BG_EN�źż�����ģ��PD�ź��Զ�����
                                                      1�� Reference��ѹģ��ǿ��Power Down */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA11_UNION;
#define ABB_CH0_REG_DEBUG_ANA11_CH0_BG_EN_START    (6)
#define ABB_CH0_REG_DEBUG_ANA11_CH0_BG_EN_END      (6)
#define ABB_CH0_REG_DEBUG_ANA11_CH0_BG_PD_START    (7)
#define ABB_CH0_REG_DEBUG_ANA11_CH0_BG_PD_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA14_UNION
 �ṹ˵��  : ch0_reg_debug_ana14 �Ĵ����ṹ���塣��ַƫ����:0xEE����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_OL_CT   : 3;  /* bit[0-2]: ADC Overloadģ������
                                                      00��16����������������С��
                                                      01��8����������������С��
                                                      10��4����������������С��
                                                      11���ر�Overload��� */
        unsigned long  reserved_0  : 3;  /* bit[3-5]: Reserved */
        unsigned long  reserved_1  : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA14_UNION;
#define ABB_CH0_REG_DEBUG_ANA14_CH0_OL_CT_START    (0)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_OL_CT_END      (2)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA16_UNION
 �ṹ˵��  : ch0_reg_debug_ana16 �Ĵ����ṹ���塣��ַƫ����:0xF0����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0   : 6;  /* bit[0-5]: Reserved */
        unsigned long  reserved_1   : 1;  /* bit[6]  : Reserved */
        unsigned long  CH0_PDM_CTRL : 1;  /* bit[7]  : RX���PDM�������
                                                       0��adder encoder���ӷ��������
                                                       1��de-bubble encoder��������������� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA16_UNION;
#define ABB_CH0_REG_DEBUG_ANA16_CH0_PDM_CTRL_START  (7)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_PDM_CTRL_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA17_UNION
 �ṹ˵��  : ch0_reg_debug_ana17 �Ĵ����ṹ���塣��ַƫ����:0xF1����ֵ:0x00�����:8
 �Ĵ���˵��: PLL���ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_WG_CLK_SEL : 2;  /* bit[4-5]: PLLʱ�Ӳ���PAD�ź�ѡ��
                                                         00/11��ʱ�Ӳ���PAD����
                                                         01��GPLL���ʱ�ӵ�PAD
                                                         10��WPLL���ʱ�ӵ�PAD */
        unsigned long  CH0_WG_VCSEL   : 2;  /* bit[6-7]: PLL���Ƶ�ѹ����PAD�ź�ѡ��
                                                         00/11�����Ƶ�ѹ����PAD����
                                                         01��GPLL������Ƶ�ѹ��PAD
                                                         10��WPLL������Ƶ�ѹ��PAD */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA17_UNION;
#define ABB_CH0_REG_DEBUG_ANA17_CH0_WG_CLK_SEL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA17_CH0_WG_CLK_SEL_END    (5)
#define ABB_CH0_REG_DEBUG_ANA17_CH0_WG_VCSEL_START    (6)
#define ABB_CH0_REG_DEBUG_ANA17_CH0_WG_VCSEL_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA19_UNION
 �ṹ˵��  : ch0_reg_debug_ana19 �Ĵ����ṹ���塣��ַƫ����:0xF3����ֵ:0x33�����:8
 �Ĵ���˵��: ʱ��ʹ�ܿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : Reserved */
        unsigned long  CH0_WPADF_SEL  : 1;  /* bit[1]  : WPLL���Թܽ����ʱ��Ƶ�ʿ���
                                                         0��������ʱ��
                                                         1��������� */
        unsigned long  reserved_1     : 2;  /* bit[2-3]: Reserved */
        unsigned long  CH0_DAC_CLK_EN : 1;  /* bit[4]  : PLLģ��312MHzʱ��ʹ���ź�
                                                         0��ʱ�ӹر�
                                                         1��ʱ��ʹ�� */
        unsigned long  CH0_ADC_CLK_EN : 1;  /* bit[5]  : PLLģ��307.2MHzʱ��ʹ���ź�
                                                         0��ʱ�ӹر�
                                                         1��ʱ��ʹ�� */
        unsigned long  reserved_2     : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA19_UNION;
#define ABB_CH0_REG_DEBUG_ANA19_CH0_WPADF_SEL_START   (1)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_WPADF_SEL_END     (1)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_DAC_CLK_EN_START  (4)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_DAC_CLK_EN_END    (4)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_ADC_CLK_EN_START  (5)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_ADC_CLK_EN_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA20_UNION
 �ṹ˵��  : ch0_reg_debug_ana20 �Ĵ����ṹ���塣��ַƫ����:0xF4����ֵ:0x40�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : ���� */
        unsigned long  reserved_1     : 1;  /* bit[1]  : ���� */
        unsigned long  reserved_2     : 1;  /* bit[2]  : ���� */
        unsigned long  reserved_3     : 2;  /* bit[3-4]: Reserved */
        unsigned long  CH0_CAP3_MULTI : 2;  /* bit[5-6]: ADC���������ݱ���ϵ��
                                                         00��X1(Ĭ��)
                                                         01��X1.5
                                                         10��X1.25
                                                         11��X1.125 */
        unsigned long  reserved_4     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA20_UNION;
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP3_MULTI_START  (5)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP3_MULTI_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA22_UNION
 �ṹ˵��  : ch0_reg_debug_ana22 �Ĵ����ṹ���塣��ַƫ����:0xF6����ֵ:0x40�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RX_TUNE : 7;  /* bit[0-6]: RXģ���Զ�Tuning code����ֵ */
        unsigned long  reserved    : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA22_UNION;
#define ABB_CH0_REG_DEBUG_ANA22_CH0_RX_TUNE_START  (0)
#define ABB_CH0_REG_DEBUG_ANA22_CH0_RX_TUNE_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA25_UNION
 �ṹ˵��  : ch0_reg_debug_ana25 �Ĵ����ṹ���塣��ַƫ����:0xF9����ֵ:0x06�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CALOP1_IB_CTRL : 1;  /* bit[0]  : ADC��OP1 DC OffsetУ׼��ƫ�õ���ѡ��
                                                         0��5uA��Ĭ��У׼��Χ
                                                         1��10uA��У׼��Χ�ӱ� */
        unsigned long  CAL_OP1_EN     : 1;  /* bit[1]  : ADC��OP1 DC OffsetУ׼ʹ���ź�
                                                         0����ʹ��У׼
                                                         1��ʹ��У׼ */
        unsigned long  CALOP1_TRIM_SW : 1;  /* bit[2]  : ADC��OP1 DC OffsetУ׼ϵͳ��������
                                                         0��������ϵͳ���
                                                         1������ϵͳ��� */
        unsigned long  OP1CAL_CKCTR   : 2;  /* bit[3-4]: ADC��OP1 DC OffsetУ׼ʱ��Ƶ�ʿ���
                                                         00��6.4MHz
                                                         01��3.2MHz
                                                         10��9.6MHz
                                                         11��4.8MHz */
        unsigned long  OP3_IB_SW      : 1;  /* bit[5]  : ADC��OP3���뼶β�����ܼӴ�ߴ���ƣ�debug��
                                                         0��Ĭ����Ŀ
                                                         1������β��������Ŀ */
        unsigned long  PUP_CK_CTRL    : 1;  /* bit[6]  : ADC Pupģ���Ƶʱ����Pup������ɺ���Ƿ������ת�Ŀ���λ
                                                         0������ת
                                                         1��������ת */
        unsigned long  reserved       : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA25_UNION;
#define ABB_CH0_REG_DEBUG_ANA25_CALOP1_IB_CTRL_START  (0)
#define ABB_CH0_REG_DEBUG_ANA25_CALOP1_IB_CTRL_END    (0)
#define ABB_CH0_REG_DEBUG_ANA25_CAL_OP1_EN_START      (1)
#define ABB_CH0_REG_DEBUG_ANA25_CAL_OP1_EN_END        (1)
#define ABB_CH0_REG_DEBUG_ANA25_CALOP1_TRIM_SW_START  (2)
#define ABB_CH0_REG_DEBUG_ANA25_CALOP1_TRIM_SW_END    (2)
#define ABB_CH0_REG_DEBUG_ANA25_OP1CAL_CKCTR_START    (3)
#define ABB_CH0_REG_DEBUG_ANA25_OP1CAL_CKCTR_END      (4)
#define ABB_CH0_REG_DEBUG_ANA25_OP3_IB_SW_START       (5)
#define ABB_CH0_REG_DEBUG_ANA25_OP3_IB_SW_END         (5)
#define ABB_CH0_REG_DEBUG_ANA25_PUP_CK_CTRL_START     (6)
#define ABB_CH0_REG_DEBUG_ANA25_PUP_CK_CTRL_END       (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA26_UNION
 �ṹ˵��  : ch0_reg_debug_ana26 �Ĵ����ṹ���塣��ַƫ����:0xFA����ֵ:0x00�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved     : 2;  /* bit[0-1]: Reserved */
        unsigned long  CH0_REG_EXT2 : 3;  /* bit[2-4]: ADC������2���ݿ����룬ΪFF Corner׼���Ķ��ⲹ���� */
        unsigned long  CH0_REG_EXT1 : 3;  /* bit[5-7]: ADC������1���ݿ����룬ΪFF Corner׼���Ķ��ⲹ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA26_UNION;
#define ABB_CH0_REG_DEBUG_ANA26_CH0_REG_EXT2_START  (2)
#define ABB_CH0_REG_DEBUG_ANA26_CH0_REG_EXT2_END    (4)
#define ABB_CH0_REG_DEBUG_ANA26_CH0_REG_EXT1_START  (5)
#define ABB_CH0_REG_DEBUG_ANA26_CH0_REG_EXT1_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ARO0_UNION
 �ṹ˵��  : ch0_reg_debug_aro0 �Ĵ����ṹ���塣��ַƫ����:0xFB����ֵ:0x00�����:8
 �Ĵ���˵��: ģ�����ֻ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved            : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_RXB_OP1_CALOK_Q : 1;  /* bit[4]  : RXB Qͨ��OP1 OffsetУ���Ƿ������־λ
                                                              0��δ���
                                                              1��У׼��� */
        unsigned long  CH0_RXB_OP1_CALOK_I : 1;  /* bit[5]  : RXB Iͨ��OP1 OffsetУ���Ƿ������־λ
                                                              0��δ���
                                                              1��У׼��� */
        unsigned long  CH0_RXA_OP1_CALOK_Q : 1;  /* bit[6]  : RXA Qͨ��OP1 OffsetУ���Ƿ������־λ
                                                              0��δ���
                                                              1��У׼��� */
        unsigned long  CH0_RXA_OP1_CALOK_I : 1;  /* bit[7]  : RXA Iͨ��OP1 OffsetУ���Ƿ������־λ
                                                              0��δ���
                                                              1��У׼��� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ARO0_UNION;
#define ABB_CH0_REG_DEBUG_ARO0_CH0_RXB_OP1_CALOK_Q_START  (4)
#define ABB_CH0_REG_DEBUG_ARO0_CH0_RXB_OP1_CALOK_Q_END    (4)
#define ABB_CH0_REG_DEBUG_ARO0_CH0_RXB_OP1_CALOK_I_START  (5)
#define ABB_CH0_REG_DEBUG_ARO0_CH0_RXB_OP1_CALOK_I_END    (5)
#define ABB_CH0_REG_DEBUG_ARO0_CH0_RXA_OP1_CALOK_Q_START  (6)
#define ABB_CH0_REG_DEBUG_ARO0_CH0_RXA_OP1_CALOK_Q_END    (6)
#define ABB_CH0_REG_DEBUG_ARO0_CH0_RXA_OP1_CALOK_I_START  (7)
#define ABB_CH0_REG_DEBUG_ARO0_CH0_RXA_OP1_CALOK_I_END    (7)


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
 �ṹ��    : ABB_TX_2G_ANA_3_UNION
 �ṹ˵��  : tx_2g_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x18�����:8
 �Ĵ���˵��: TX 2G���üĴ����������߿��߼�������reg_analog_wr50��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT_2G     : 3;  /* bit[0-2]: LPF OP ����ģʽ����
                                                          000��5u
                                                          001��4u
                                                          010��3u
                                                          011��2u
                                                          100��9u
                                                          101��8u
                                                          110��7u
                                                          111��6u */
        unsigned long  DUM_EN_Q_2G     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  DUM_EN_I_2G     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  reserved        : 2;  /* bit[5-6]: ���� */
        unsigned long  TX_CLKD_CTRL_2G : 1;  /* bit[7]  : TX ����ʱ����ѡ��
                                                          0������(Ĭ��)
                                                          1������ */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_ANA_3_UNION;
#define ABB_TX_2G_ANA_3_TXLPF_CT_2G_START      (0)
#define ABB_TX_2G_ANA_3_TXLPF_CT_2G_END        (2)
#define ABB_TX_2G_ANA_3_DUM_EN_Q_2G_START      (3)
#define ABB_TX_2G_ANA_3_DUM_EN_Q_2G_END        (3)
#define ABB_TX_2G_ANA_3_DUM_EN_I_2G_START      (4)
#define ABB_TX_2G_ANA_3_DUM_EN_I_2G_END        (4)
#define ABB_TX_2G_ANA_3_TX_CLKD_CTRL_2G_START  (7)
#define ABB_TX_2G_ANA_3_TX_CLKD_CTRL_2G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_ANA_3_UNION
 �ṹ˵��  : rx_2g_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x103����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2G���üĴ����������߿��߼�������reg_analog_wr53��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1_2G : 3;  /* bit[0-2]: RX ADC OP1��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  ITR_OP3_2G : 3;  /* bit[3-5]: RX ADC OP3��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_3_UNION;
#define ABB_RX_2G_ANA_3_ITR_OP1_2G_START  (0)
#define ABB_RX_2G_ANA_3_ITR_OP1_2G_END    (2)
#define ABB_RX_2G_ANA_3_ITR_OP3_2G_START  (3)
#define ABB_RX_2G_ANA_3_ITR_OP3_2G_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_ANA_4_UNION
 �ṹ˵��  : rx_2g_ana_4 �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2G���üĴ����������߿��߼�������reg_analog_wr54��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT_2G  : 3;  /* bit[0-2]: RX ADC QT��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  ITR_DAC_2G : 3;  /* bit[3-5]: RX ADC ����DAC�˷ŵ�������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_4_UNION;
#define ABB_RX_2G_ANA_4_ITR_QT_2G_START   (0)
#define ABB_RX_2G_ANA_4_ITR_QT_2G_END     (2)
#define ABB_RX_2G_ANA_4_ITR_DAC_2G_START  (3)
#define ABB_RX_2G_ANA_4_ITR_DAC_2G_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_ANA_5_UNION
 �ṹ˵��  : rx_2g_ana_5 �Ĵ����ṹ���塣��ַƫ����:0x105����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2G���üĴ����������߿��߼�������reg_analog_wr55��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP2_2G  : 3;  /* bit[0-2]: RX ADC OP2��������
                                                      000�� 1.0x
                                                      001�� 0.8x
                                                      010�� 0.6x
                                                      011�� 0.4x
                                                      100�� 1.8x
                                                      101�� 1.6x
                                                      110�� 1.4x
                                                      111�� 1.2x */
        unsigned long  IBCT_OP2_2G : 2;  /* bit[3-4]: Current Seting For Mode
                                                      1x��LTE mode Current
                                                      01��3G_DC &amp; X mode Current
                                                      00��3G &amp; 2G mode Current */
        unsigned long  reserved    : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_5_UNION;
#define ABB_RX_2G_ANA_5_ITR_OP2_2G_START   (0)
#define ABB_RX_2G_ANA_5_ITR_OP2_2G_END     (2)
#define ABB_RX_2G_ANA_5_IBCT_OP2_2G_START  (3)
#define ABB_RX_2G_ANA_5_IBCT_OP2_2G_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_3G_ANA_3_UNION
 �ṹ˵��  : tx_ch0_3g_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x106����ֵ:0x18�����:8
 �Ĵ���˵��: CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr50��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT_3G     : 3;  /* bit[0-2]: LPF OP����ģʽ����
                                                          000��5u
                                                          001��4u
                                                          010��3u
                                                          011��2u
                                                          100��9u
                                                          101��8u
                                                          110��7u
                                                          111��6u */
        unsigned long  DUM_EN_Q_3G     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  DUM_EN_I_3G     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  reserved        : 2;  /* bit[5-6]: ���� */
        unsigned long  TX_CLKD_CTRL_3G : 1;  /* bit[7]  : TX ����ʱ����ѡ��
                                                          0������(Ĭ��)
                                                          1������ */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_ANA_3_UNION;
#define ABB_TX_CH0_3G_ANA_3_TXLPF_CT_3G_START      (0)
#define ABB_TX_CH0_3G_ANA_3_TXLPF_CT_3G_END        (2)
#define ABB_TX_CH0_3G_ANA_3_DUM_EN_Q_3G_START      (3)
#define ABB_TX_CH0_3G_ANA_3_DUM_EN_Q_3G_END        (3)
#define ABB_TX_CH0_3G_ANA_3_DUM_EN_I_3G_START      (4)
#define ABB_TX_CH0_3G_ANA_3_DUM_EN_I_3G_END        (4)
#define ABB_TX_CH0_3G_ANA_3_TX_CLKD_CTRL_3G_START  (7)
#define ABB_TX_CH0_3G_ANA_3_TX_CLKD_CTRL_3G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_3G_ANA_3_UNION
 �ṹ˵��  : rx_ch0_3g_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x109����ֵ:0x00�����:8
 �Ĵ���˵��: CH0 RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr53��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1_3G : 3;  /* bit[0-2]: RX ADC OP1��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  ITR_OP3_3G : 3;  /* bit[3-5]: RX ADC OP3��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_3_UNION;
#define ABB_RX_CH0_3G_ANA_3_ITR_OP1_3G_START  (0)
#define ABB_RX_CH0_3G_ANA_3_ITR_OP1_3G_END    (2)
#define ABB_RX_CH0_3G_ANA_3_ITR_OP3_3G_START  (3)
#define ABB_RX_CH0_3G_ANA_3_ITR_OP3_3G_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_3G_ANA_4_UNION
 �ṹ˵��  : rx_ch0_3g_ana_4 �Ĵ����ṹ���塣��ַƫ����:0x10A����ֵ:0x00�����:8
 �Ĵ���˵��: CH0 RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr54��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT_3G  : 3;  /* bit[0-2]: RX ADC QT��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  ITR_DAC_3G : 3;  /* bit[3-5]: RX ADC ����DAC�˷ŵ�������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_4_UNION;
#define ABB_RX_CH0_3G_ANA_4_ITR_QT_3G_START   (0)
#define ABB_RX_CH0_3G_ANA_4_ITR_QT_3G_END     (2)
#define ABB_RX_CH0_3G_ANA_4_ITR_DAC_3G_START  (3)
#define ABB_RX_CH0_3G_ANA_4_ITR_DAC_3G_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_3G_ANA_5_UNION
 �ṹ˵��  : rx_ch0_3g_ana_5 �Ĵ����ṹ���塣��ַƫ����:0x10B����ֵ:0x00�����:8
 �Ĵ���˵��: CH0 RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr55��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP2_3G  : 3;  /* bit[0-2]: RX ADC OP2��������
                                                      000�� 1.0x
                                                      001�� 0.8x
                                                      010�� 0.6x
                                                      011�� 0.4x
                                                      100�� 1.8x
                                                      101�� 1.6x
                                                      110�� 1.4x
                                                      111�� 1.2x */
        unsigned long  IBCT_OP2_3G : 2;  /* bit[3-4]: Current Seting For Mode
                                                      1x��LTE mode Current
                                                      01��3G_DC &amp; X mode Current
                                                      00��3G &amp; 2G mode Current */
        unsigned long  reserved    : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_5_UNION;
#define ABB_RX_CH0_3G_ANA_5_ITR_OP2_3G_START   (0)
#define ABB_RX_CH0_3G_ANA_5_ITR_OP2_3G_END     (2)
#define ABB_RX_CH0_3G_ANA_5_IBCT_OP2_3G_START  (3)
#define ABB_RX_CH0_3G_ANA_5_IBCT_OP2_3G_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_4G_ANA_3_UNION
 �ṹ˵��  : tx_ch0_4g_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x18�����:8
 �Ĵ���˵��: CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr50��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT_4G     : 3;  /* bit[0-2]: LPF OP����ģʽ����
                                                          000��5u
                                                          001��4u
                                                          010��3u
                                                          011��2u
                                                          100��9u
                                                          101��8u
                                                          110��7u
                                                          111��6u */
        unsigned long  DUM_EN_Q_4G     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  DUM_EN_I_4G     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  reserved        : 2;  /* bit[5-6]: ���� */
        unsigned long  TX_CLKD_CTRL_4G : 1;  /* bit[7]  : TX ����ʱ����ѡ��
                                                          0������(Ĭ��)
                                                          1������ */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_ANA_3_UNION;
#define ABB_TX_CH0_4G_ANA_3_TXLPF_CT_4G_START      (0)
#define ABB_TX_CH0_4G_ANA_3_TXLPF_CT_4G_END        (2)
#define ABB_TX_CH0_4G_ANA_3_DUM_EN_Q_4G_START      (3)
#define ABB_TX_CH0_4G_ANA_3_DUM_EN_Q_4G_END        (3)
#define ABB_TX_CH0_4G_ANA_3_DUM_EN_I_4G_START      (4)
#define ABB_TX_CH0_4G_ANA_3_DUM_EN_I_4G_END        (4)
#define ABB_TX_CH0_4G_ANA_3_TX_CLKD_CTRL_4G_START  (7)
#define ABB_TX_CH0_4G_ANA_3_TX_CLKD_CTRL_4G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_4G_ANA_3_UNION
 �ṹ˵��  : rx_ch0_4g_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x10F����ֵ:0x00�����:8
 �Ĵ���˵��: CH0 RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr53��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1_4G : 3;  /* bit[0-2]: RX ADC OP1��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  ITR_OP3_4G : 3;  /* bit[3-5]: RX ADC OP3��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_3_UNION;
#define ABB_RX_CH0_4G_ANA_3_ITR_OP1_4G_START  (0)
#define ABB_RX_CH0_4G_ANA_3_ITR_OP1_4G_END    (2)
#define ABB_RX_CH0_4G_ANA_3_ITR_OP3_4G_START  (3)
#define ABB_RX_CH0_4G_ANA_3_ITR_OP3_4G_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_4G_ANA_4_UNION
 �ṹ˵��  : rx_ch0_4g_ana_4 �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00�����:8
 �Ĵ���˵��: CH0 RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr54��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT_4G  : 3;  /* bit[0-2]: RX ADC QT��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  ITR_DAC_4G : 3;  /* bit[3-5]: RX ADC ����DAC�˷ŵ�������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_4_UNION;
#define ABB_RX_CH0_4G_ANA_4_ITR_QT_4G_START   (0)
#define ABB_RX_CH0_4G_ANA_4_ITR_QT_4G_END     (2)
#define ABB_RX_CH0_4G_ANA_4_ITR_DAC_4G_START  (3)
#define ABB_RX_CH0_4G_ANA_4_ITR_DAC_4G_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_4G_ANA_5_UNION
 �ṹ˵��  : rx_ch0_4g_ana_5 �Ĵ����ṹ���塣��ַƫ����:0x111����ֵ:0x10�����:8
 �Ĵ���˵��: CH0 RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr55��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP2_4G  : 3;  /* bit[0-2]: RX ADC OP2��������
                                                      000�� 1.0x
                                                      001�� 0.8x
                                                      010�� 0.6x
                                                      011�� 0.4x
                                                      100�� 1.8x
                                                      101�� 1.6x
                                                      110�� 1.4x
                                                      111�� 1.2x */
        unsigned long  IBCT_OP2_4G : 2;  /* bit[3-4]: Current Seting For Mode
                                                      1x��LTE mode Current
                                                      01��3G_DC &amp; X mode Current
                                                      00��3G &amp; 2G mode Current */
        unsigned long  reserved    : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_5_UNION;
#define ABB_RX_CH0_4G_ANA_5_ITR_OP2_4G_START   (0)
#define ABB_RX_CH0_4G_ANA_5_ITR_OP2_4G_END     (2)
#define ABB_RX_CH0_4G_ANA_5_IBCT_OP2_4G_START  (3)
#define ABB_RX_CH0_4G_ANA_5_IBCT_OP2_4G_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_ANA_3_UNION
 �ṹ˵��  : tx_tds_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x112����ֵ:0x18�����:8
 �Ĵ���˵��: TX TDS���üĴ����������߿��߼�������reg_analog_wr50��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT_TDS     : 3;  /* bit[0-2]: LPF OP����ģʽ����
                                                           000��5u
                                                           001��4u
                                                           010��3u
                                                           011��2u
                                                           100��9u
                                                           101��8u
                                                           110��7u
                                                           111��6u */
        unsigned long  DUM_EN_Q_TDS     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                           1��enable(Ĭ��)
                                                           0��disable */
        unsigned long  DUM_EN_I_TDS     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                           1��enable(Ĭ��)
                                                           0��disable */
        unsigned long  reserved         : 2;  /* bit[5-6]: ���� */
        unsigned long  TX_CLKD_CTRL_TDS : 1;  /* bit[7]  : TX ����ʱ����ѡ��
                                                           0������(Ĭ��)
                                                           1������ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_ANA_3_UNION;
#define ABB_TX_TDS_ANA_3_TXLPF_CT_TDS_START      (0)
#define ABB_TX_TDS_ANA_3_TXLPF_CT_TDS_END        (2)
#define ABB_TX_TDS_ANA_3_DUM_EN_Q_TDS_START      (3)
#define ABB_TX_TDS_ANA_3_DUM_EN_Q_TDS_END        (3)
#define ABB_TX_TDS_ANA_3_DUM_EN_I_TDS_START      (4)
#define ABB_TX_TDS_ANA_3_DUM_EN_I_TDS_END        (4)
#define ABB_TX_TDS_ANA_3_TX_CLKD_CTRL_TDS_START  (7)
#define ABB_TX_TDS_ANA_3_TX_CLKD_CTRL_TDS_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_ANA_3_UNION
 �ṹ˵��  : rx_tds_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x115����ֵ:0x00�����:8
 �Ĵ���˵��: RX TDS���üĴ����������߿��߼�������reg_analog_wr53��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1_TDS : 3;  /* bit[0-2]: RX ADC OP1��������
                                                      000�� 1.0x
                                                      001�� 0.8x
                                                      010�� 0.6x
                                                      011�� 0.4x
                                                      100�� 1.8x
                                                      101�� 1.6x
                                                      110�� 1.4x
                                                      111�� 1.2x */
        unsigned long  ITR_OP3_TDS : 3;  /* bit[3-5]: RX ADC OP3��������
                                                      000�� 1.0x
                                                      001�� 0.8x
                                                      010�� 0.6x
                                                      011�� 0.4x
                                                      100�� 1.8x
                                                      101�� 1.6x
                                                      110�� 1.4x
                                                      111�� 1.2x */
        unsigned long  reserved    : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_3_UNION;
#define ABB_RX_TDS_ANA_3_ITR_OP1_TDS_START  (0)
#define ABB_RX_TDS_ANA_3_ITR_OP1_TDS_END    (2)
#define ABB_RX_TDS_ANA_3_ITR_OP3_TDS_START  (3)
#define ABB_RX_TDS_ANA_3_ITR_OP3_TDS_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_ANA_4_UNION
 �ṹ˵��  : rx_tds_ana_4 �Ĵ����ṹ���塣��ַƫ����:0x116����ֵ:0x00�����:8
 �Ĵ���˵��: RX TDS���üĴ����������߿��߼�������reg_analog_wr54��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT_TDS  : 3;  /* bit[0-2]: RX ADC QT��������
                                                      000�� 1.0x
                                                      001�� 0.8x
                                                      010�� 0.6x
                                                      011�� 0.4x
                                                      100�� 1.8x
                                                      101�� 1.6x
                                                      110�� 1.4x
                                                      111�� 1.2x */
        unsigned long  ITR_DAC_TDS : 3;  /* bit[3-5]: RX ADC ����DAC�˷ŵ�������
                                                      000�� 1.0x
                                                      001�� 0.8x
                                                      010�� 0.6x
                                                      011�� 0.4x
                                                      100�� 1.8x
                                                      101�� 1.6x
                                                      110�� 1.4x
                                                      111�� 1.2x */
        unsigned long  reserved    : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_4_UNION;
#define ABB_RX_TDS_ANA_4_ITR_QT_TDS_START   (0)
#define ABB_RX_TDS_ANA_4_ITR_QT_TDS_END     (2)
#define ABB_RX_TDS_ANA_4_ITR_DAC_TDS_START  (3)
#define ABB_RX_TDS_ANA_4_ITR_DAC_TDS_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_ANA_5_UNION
 �ṹ˵��  : rx_tds_ana_5 �Ĵ����ṹ���塣��ַƫ����:0x117����ֵ:0x00�����:8
 �Ĵ���˵��: RX TDS���üĴ����������߿��߼�������reg_analog_wr55��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP2_TDS  : 3;  /* bit[0-2]: RX ADC OP2��������
                                                       000�� 1.0x
                                                       001�� 0.8x
                                                       010�� 0.6x
                                                       011�� 0.4x
                                                       100�� 1.8x
                                                       101�� 1.6x
                                                       110�� 1.4x
                                                       111�� 1.2x */
        unsigned long  IBCT_OP2_TDS : 2;  /* bit[3-4]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  reserved     : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_5_UNION;
#define ABB_RX_TDS_ANA_5_ITR_OP2_TDS_START   (0)
#define ABB_RX_TDS_ANA_5_ITR_OP2_TDS_END     (2)
#define ABB_RX_TDS_ANA_5_IBCT_OP2_TDS_START  (3)
#define ABB_RX_TDS_ANA_5_IBCT_OP2_TDS_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH1_4G_ANA_3_UNION
 �ṹ˵��  : tx_ch1_4g_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x118����ֵ:0x18�����:8
 �Ĵ���˵��: CH1 TX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr50��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT_4G     : 3;  /* bit[0-2]: LPF OP����ģʽ����
                                                          000��5u
                                                          001��4u
                                                          010��3u
                                                          011��2u
                                                          100��9u
                                                          101��8u
                                                          110��7u
                                                          111��6u */
        unsigned long  DUM_EN_Q_4G     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  DUM_EN_I_4G     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  reserved        : 2;  /* bit[5-6]: ���� */
        unsigned long  TX_CLKD_CTRL_4G : 1;  /* bit[7]  : TX ����ʱ����ѡ��
                                                          0������(Ĭ��)
                                                          1������ */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_4G_ANA_3_UNION;
#define ABB_TX_CH1_4G_ANA_3_TXLPF_CT_4G_START      (0)
#define ABB_TX_CH1_4G_ANA_3_TXLPF_CT_4G_END        (2)
#define ABB_TX_CH1_4G_ANA_3_DUM_EN_Q_4G_START      (3)
#define ABB_TX_CH1_4G_ANA_3_DUM_EN_Q_4G_END        (3)
#define ABB_TX_CH1_4G_ANA_3_DUM_EN_I_4G_START      (4)
#define ABB_TX_CH1_4G_ANA_3_DUM_EN_I_4G_END        (4)
#define ABB_TX_CH1_4G_ANA_3_TX_CLKD_CTRL_4G_START  (7)
#define ABB_TX_CH1_4G_ANA_3_TX_CLKD_CTRL_4G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_4G_ANA_3_UNION
 �ṹ˵��  : rx_ch1_4g_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x11B����ֵ:0x00�����:8
 �Ĵ���˵��: CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr53��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1_4G : 3;  /* bit[0-2]: RX ADC OP1��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  ITR_OP3_4G : 3;  /* bit[3-5]: RX ADC OP3��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_4G_ANA_3_UNION;
#define ABB_RX_CH1_4G_ANA_3_ITR_OP1_4G_START  (0)
#define ABB_RX_CH1_4G_ANA_3_ITR_OP1_4G_END    (2)
#define ABB_RX_CH1_4G_ANA_3_ITR_OP3_4G_START  (3)
#define ABB_RX_CH1_4G_ANA_3_ITR_OP3_4G_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_4G_ANA_4_UNION
 �ṹ˵��  : rx_ch1_4g_ana_4 �Ĵ����ṹ���塣��ַƫ����:0x11C����ֵ:0x00�����:8
 �Ĵ���˵��: CH1 RX 4G���üĴ����������߿��߼�������ch1_reg_analog_wr54��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT_4G  : 3;  /* bit[0-2]: RX ADC QT��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  ITR_DAC_4G : 3;  /* bit[3-5]: RX ADC ����DAC�˷ŵ�������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_4G_ANA_4_UNION;
#define ABB_RX_CH1_4G_ANA_4_ITR_QT_4G_START   (0)
#define ABB_RX_CH1_4G_ANA_4_ITR_QT_4G_END     (2)
#define ABB_RX_CH1_4G_ANA_4_ITR_DAC_4G_START  (3)
#define ABB_RX_CH1_4G_ANA_4_ITR_DAC_4G_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_ANA_3_UNION
 �ṹ˵��  : tx_idle_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x12A����ֵ:0x18�����:8
 �Ĵ���˵��: TX IDLE���üĴ����������߿��߼�������reg_analog_wr50��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT_IDLE     : 3;  /* bit[0-2]: LPF OP1 ����ģʽ����
                                                            000��5u
                                                            001��4u
                                                            010��3u
                                                            011��2u
                                                            100��9u
                                                            101��8u
                                                            110��7u
                                                            111��6u */
        unsigned long  DUM_EN_Q_IDLE     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                            1��enable(Ĭ��)
                                                            0��disable */
        unsigned long  DUM_EN_I_IDLE     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                            1��enable(Ĭ��)
                                                            0��disable */
        unsigned long  reserved          : 2;  /* bit[5-6]: ���� */
        unsigned long  TX_CLKD_CTRL_IDLE : 1;  /* bit[7]  : TX ����ʱ����ѡ��
                                                            0������(Ĭ��)
                                                            1������ */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_ANA_3_UNION;
#define ABB_TX_IDLE_ANA_3_TXLPF_CT_IDLE_START      (0)
#define ABB_TX_IDLE_ANA_3_TXLPF_CT_IDLE_END        (2)
#define ABB_TX_IDLE_ANA_3_DUM_EN_Q_IDLE_START      (3)
#define ABB_TX_IDLE_ANA_3_DUM_EN_Q_IDLE_END        (3)
#define ABB_TX_IDLE_ANA_3_DUM_EN_I_IDLE_START      (4)
#define ABB_TX_IDLE_ANA_3_DUM_EN_I_IDLE_END        (4)
#define ABB_TX_IDLE_ANA_3_TX_CLKD_CTRL_IDLE_START  (7)
#define ABB_TX_IDLE_ANA_3_TX_CLKD_CTRL_IDLE_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_ANA_3_UNION
 �ṹ˵��  : rx_idle_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x12D����ֵ:0x00�����:8
 �Ĵ���˵��: RX IDLE���üĴ����������߿��߼�������reg_analog_wr53��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1_IDLE : 3;  /* bit[0-2]: RX ADC OP1��������
                                                       000�� 1.0x
                                                       001�� 0.8x
                                                       010�� 0.6x
                                                       011�� 0.4x
                                                       100�� 1.8x
                                                       101�� 1.6x
                                                       110�� 1.4x
                                                       111�� 1.2x */
        unsigned long  ITR_OP3_IDLE : 3;  /* bit[3-5]: RX ADC OP3��������
                                                       000�� 1.0x
                                                       001�� 0.8x
                                                       010�� 0.6x
                                                       011�� 0.4x
                                                       100�� 1.8x
                                                       101�� 1.6x
                                                       110�� 1.4x
                                                       111�� 1.2x */
        unsigned long  reserved     : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_3_UNION;
#define ABB_RX_IDLE_ANA_3_ITR_OP1_IDLE_START  (0)
#define ABB_RX_IDLE_ANA_3_ITR_OP1_IDLE_END    (2)
#define ABB_RX_IDLE_ANA_3_ITR_OP3_IDLE_START  (3)
#define ABB_RX_IDLE_ANA_3_ITR_OP3_IDLE_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_ANA_4_UNION
 �ṹ˵��  : rx_idle_ana_4 �Ĵ����ṹ���塣��ַƫ����:0x12E����ֵ:0x00�����:8
 �Ĵ���˵��: RX IDLE���üĴ����������߿��߼�������reg_analog_wr54��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT_IDLE  : 3;  /* bit[0-2]: RX ADC QT��������
                                                       000�� 1.0x
                                                       001�� 0.8x
                                                       010�� 0.6x
                                                       011�� 0.4x
                                                       100�� 1.8x
                                                       101�� 1.6x
                                                       110�� 1.4x
                                                       111�� 1.2x */
        unsigned long  ITR_DAC_IDLE : 3;  /* bit[3-5]: RX ADC ����DAC�˷ŵ�������
                                                       000�� 1.0x
                                                       001�� 0.8x
                                                       010�� 0.6x
                                                       011�� 0.4x
                                                       100�� 1.8x
                                                       101�� 1.6x
                                                       110�� 1.4x
                                                       111�� 1.2x */
        unsigned long  reserved     : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_4_UNION;
#define ABB_RX_IDLE_ANA_4_ITR_QT_IDLE_START   (0)
#define ABB_RX_IDLE_ANA_4_ITR_QT_IDLE_END     (2)
#define ABB_RX_IDLE_ANA_4_ITR_DAC_IDLE_START  (3)
#define ABB_RX_IDLE_ANA_4_ITR_DAC_IDLE_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_ANA_5_UNION
 �ṹ˵��  : rx_idle_ana_5 �Ĵ����ṹ���塣��ַƫ����:0x12F����ֵ:0x00�����:8
 �Ĵ���˵��: RX IDLE���üĴ����������߿��߼�������reg_analog_wr55��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP2_IDLE  : 3;  /* bit[0-2]: RX ADC OP2��������
                                                        000�� 1.0x
                                                        001�� 0.8x
                                                        010�� 0.6x
                                                        011�� 0.4x
                                                        100�� 1.8x
                                                        101�� 1.6x
                                                        110�� 1.4x
                                                        111�� 1.2x */
        unsigned long  IBCT_OP2_IDLE : 2;  /* bit[3-4]: Current Seting For Mode
                                                        1x��LTE mode Current
                                                        01��3G_DC &amp; X mode Current
                                                        00��3G &amp; 2G mode Current */
        unsigned long  reserved      : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_5_UNION;
#define ABB_RX_IDLE_ANA_5_ITR_OP2_IDLE_START   (0)
#define ABB_RX_IDLE_ANA_5_ITR_OP2_IDLE_END     (2)
#define ABB_RX_IDLE_ANA_5_IBCT_OP2_IDLE_START  (3)
#define ABB_RX_IDLE_ANA_5_IBCT_OP2_IDLE_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA27_UNION
 �ṹ˵��  : ch1_reg_debug_ana27 �Ĵ����ṹ���塣��ַƫ����:0x130����ֵ:0x00�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH1_RXC_IBCT2 : 2;  /* bit[0-1]: Reserved
                                                        ComstarV511_Reserved */
        unsigned long  CH1_RXC_IBCT1 : 2;  /* bit[2-3]: Reserved
                                                        ComstarV511_Reserved */
        unsigned long  CH1_RXC_MODE  : 3;  /* bit[4-6]: Reserved
                                                        ComstarV511_Reserved */
        unsigned long  reserved      : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA27_UNION;
#define ABB_CH1_REG_DEBUG_ANA27_CH1_RXC_IBCT2_START  (0)
#define ABB_CH1_REG_DEBUG_ANA27_CH1_RXC_IBCT2_END    (1)
#define ABB_CH1_REG_DEBUG_ANA27_CH1_RXC_IBCT1_START  (2)
#define ABB_CH1_REG_DEBUG_ANA27_CH1_RXC_IBCT1_END    (3)
#define ABB_CH1_REG_DEBUG_ANA27_CH1_RXC_MODE_START   (4)
#define ABB_CH1_REG_DEBUG_ANA27_CH1_RXC_MODE_END     (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA27_UNION
 �ṹ˵��  : ch0_reg_debug_ana27 �Ĵ����ṹ���塣��ַƫ����:0x140����ֵ:0x00�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RXC_IBCT2 : 2;  /* bit[0-1]: TBD */
        unsigned long  CH0_RXC_IBCT1 : 2;  /* bit[2-3]: TBD */
        unsigned long  CH0_RXC_MODE  : 3;  /* bit[4-6]: TBD */
        unsigned long  reserved      : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA27_UNION;
#define ABB_CH0_REG_DEBUG_ANA27_CH0_RXC_IBCT2_START  (0)
#define ABB_CH0_REG_DEBUG_ANA27_CH0_RXC_IBCT2_END    (1)
#define ABB_CH0_REG_DEBUG_ANA27_CH0_RXC_IBCT1_START  (2)
#define ABB_CH0_REG_DEBUG_ANA27_CH0_RXC_IBCT1_END    (3)
#define ABB_CH0_REG_DEBUG_ANA27_CH0_RXC_MODE_START   (4)
#define ABB_CH0_REG_DEBUG_ANA27_CH0_RXC_MODE_END     (6)


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
        unsigned long  ch1_tx_cfr_bp_3g   : 1;  /* bit[0]  : TXͨ��CFR bypass���ƣ�
                                                             0����bypass
                                                             1��bypass(Ĭ��)
                                                             ��V8R1���漰�� */
        unsigned long  ch1_tx_flush_en_3g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  ch1_tx_comp_sel_3g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11������ϵ���� */
        unsigned long  reserved           : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_3G_DIG_3_UNION;
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_cfr_bp_3g_START    (0)
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_cfr_bp_3g_END      (0)
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_flush_en_3g_START  (1)
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_flush_en_3g_END    (1)
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_comp_sel_3g_START  (2)
#define ABB_TX_CH1_3G_DIG_3_ch1_tx_comp_sel_3g_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_3G_ANA_1_UNION
 �ṹ˵��  : rx_ch1_3g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x185����ֵ:0xF2�����:8
 �Ĵ���˵��: CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_3G  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                         000��DWA
                                                         001��CLA1
                                                         010��CLA2
                                                         011��CLA3
                                                         100��CLA4
                                                         101��CLA5
                                                         110��CLA6
                                                         111��CLA7 */
        unsigned long  RX_MODE_CLK_3G : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
                                                         000��4G
                                                         001��3G
                                                         010��3G_DC &amp; TDS
                                                         011��2G(Ĭ��)
                                                         100��reserved
                                                         101��CDMA */
        unsigned long  DEM_MOD_B1_3G  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                         000��DWA
                                                         001��CLA1
                                                         010��CLA2
                                                         011��CLA3
                                                         100��CLA4
                                                         101��CLA5
                                                         110��CLA6
                                                         111��CLA7 */
        unsigned long  RXB_Q_PD_3G    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_3G    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_3G    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_3G    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_3G_ANA_1_UNION;
#define ABB_RX_CH1_3G_ANA_1_DEM_MOD_B0_3G_START   (0)
#define ABB_RX_CH1_3G_ANA_1_DEM_MOD_B0_3G_END     (0)
#define ABB_RX_CH1_3G_ANA_1_RX_MODE_CLK_3G_START  (1)
#define ABB_RX_CH1_3G_ANA_1_RX_MODE_CLK_3G_END    (2)
#define ABB_RX_CH1_3G_ANA_1_DEM_MOD_B1_3G_START   (3)
#define ABB_RX_CH1_3G_ANA_1_DEM_MOD_B1_3G_END     (3)
#define ABB_RX_CH1_3G_ANA_1_RXB_Q_PD_3G_START     (4)
#define ABB_RX_CH1_3G_ANA_1_RXB_Q_PD_3G_END       (4)
#define ABB_RX_CH1_3G_ANA_1_RXB_I_PD_3G_START     (5)
#define ABB_RX_CH1_3G_ANA_1_RXB_I_PD_3G_END       (5)
#define ABB_RX_CH1_3G_ANA_1_RXA_Q_PD_3G_START     (6)
#define ABB_RX_CH1_3G_ANA_1_RXA_Q_PD_3G_END       (6)
#define ABB_RX_CH1_3G_ANA_1_RXA_I_PD_3G_START     (7)
#define ABB_RX_CH1_3G_ANA_1_RXA_I_PD_3G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_3G_ANA_2_UNION
 �ṹ˵��  : rx_ch1_3g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x186����ֵ:0x00�����:8
 �Ĵ���˵��: CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr01��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C_3G : 1;  /* bit[0]  : Mode setting for ADC
                                                       1�� CA mode
                                                       0�� others */
        unsigned long  reserved     : 1;  /* bit[1]  : ���� */
        unsigned long  IBCT_QT_3G   : 2;  /* bit[2-3]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3_3G  : 2;  /* bit[4-5]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1_3G  : 2;  /* bit[6-7]: Current Seting For Mode
                                                       1x��LTE mode Current
                                                       01��3G_DC &amp; X mode Current
                                                       00��3G &amp; 2G mode Current */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_3G_ANA_2_UNION;
#define ABB_RX_CH1_3G_ANA_2_RX_MODE_C_3G_START  (0)
#define ABB_RX_CH1_3G_ANA_2_RX_MODE_C_3G_END    (0)
#define ABB_RX_CH1_3G_ANA_2_IBCT_QT_3G_START    (2)
#define ABB_RX_CH1_3G_ANA_2_IBCT_QT_3G_END      (3)
#define ABB_RX_CH1_3G_ANA_2_IBCT_OP3_3G_START   (4)
#define ABB_RX_CH1_3G_ANA_2_IBCT_OP3_3G_END     (5)
#define ABB_RX_CH1_3G_ANA_2_IBCT_OP1_3G_START   (6)
#define ABB_RX_CH1_3G_ANA_2_IBCT_OP1_3G_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_3G_ANA_3_UNION
 �ṹ˵��  : rx_ch1_3g_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x187����ֵ:0x00�����:8
 �Ĵ���˵��: CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr53��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1_3G : 3;  /* bit[0-2]: RX ADC OP1��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  ITR_OP3_3G : 3;  /* bit[3-5]: RX ADC OP3��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_3G_ANA_3_UNION;
#define ABB_RX_CH1_3G_ANA_3_ITR_OP1_3G_START  (0)
#define ABB_RX_CH1_3G_ANA_3_ITR_OP1_3G_END    (2)
#define ABB_RX_CH1_3G_ANA_3_ITR_OP3_3G_START  (3)
#define ABB_RX_CH1_3G_ANA_3_ITR_OP3_3G_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_3G_ANA_4_UNION
 �ṹ˵��  : rx_ch1_3g_ana_4 �Ĵ����ṹ���塣��ַƫ����:0x188����ֵ:0x00�����:8
 �Ĵ���˵��: CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr54��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT_3G  : 3;  /* bit[0-2]: RX ADC QT��������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  ITR_DAC_3G : 3;  /* bit[3-5]: RX ADC ����DAC�˷ŵ�������
                                                     000�� 1.0x
                                                     001�� 0.8x
                                                     010�� 0.6x
                                                     011�� 0.4x
                                                     100�� 1.8x
                                                     101�� 1.6x
                                                     110�� 1.4x
                                                     111�� 1.2x */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_3G_ANA_4_UNION;
#define ABB_RX_CH1_3G_ANA_4_ITR_QT_3G_START   (0)
#define ABB_RX_CH1_3G_ANA_4_ITR_QT_3G_END     (2)
#define ABB_RX_CH1_3G_ANA_4_ITR_DAC_3G_START  (3)
#define ABB_RX_CH1_3G_ANA_4_ITR_DAC_3G_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH1_3G_ANA_1_UNION
 �ṹ˵��  : tx_ch1_3g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x18A����ֵ:0x1D�����:8
 �Ĵ���˵��: CH1 TX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_3G : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
                                                         000��4G
                                                         001��3G &amp; TDS
                                                         010��reserved
                                                         011��2G(Ĭ��)
                                                         1xx��CDMA */
        unsigned long  TX_Q_PD_A_3G   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_3G   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_3G : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                         00��1��Ƶ
                                                         01��2��Ƶ(Ĭ��)
                                                         10��8��Ƶ
                                                         11��4��Ƶ */
        unsigned long  FC_B1_B0_3G    : 2;  /* bit[6-7]: TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
                                                         000��14MHz(Ĭ��)
                                                         001��28MHz
                                                         010��9.3MHz
                                                         011��18.7MHz
                                                         100��7MHz
                                                         101��14MHz
                                                         110��28MHz
                                                         111��56MHz
                                                         Ĭ�����÷�����
                                                         4G:001   2G:100   Others:000 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_3G_ANA_1_UNION;
#define ABB_TX_CH1_3G_ANA_1_TX_MODE_CLK_3G_START  (0)
#define ABB_TX_CH1_3G_ANA_1_TX_MODE_CLK_3G_END    (1)
#define ABB_TX_CH1_3G_ANA_1_TX_Q_PD_A_3G_START    (2)
#define ABB_TX_CH1_3G_ANA_1_TX_Q_PD_A_3G_END      (2)
#define ABB_TX_CH1_3G_ANA_1_TX_I_PD_A_3G_START    (3)
#define ABB_TX_CH1_3G_ANA_1_TX_I_PD_A_3G_END      (3)
#define ABB_TX_CH1_3G_ANA_1_TX_DIV_MODE_3G_START  (4)
#define ABB_TX_CH1_3G_ANA_1_TX_DIV_MODE_3G_END    (5)
#define ABB_TX_CH1_3G_ANA_1_FC_B1_B0_3G_START     (6)
#define ABB_TX_CH1_3G_ANA_1_FC_B1_B0_3G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH1_3G_ANA_2_UNION
 �ṹ˵��  : tx_ch1_3g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x18B����ֵ:0x11�����:8
 �Ĵ���˵��: CH1 RX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP_3G  : 2;  /* bit[0-1]: LPF OP����ģʽ����
                                                              00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
                                                              01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
                                                              10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
                                                              11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

                                                              Ĭ�����÷�����
                                                              LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11 */
        unsigned long  reserved            : 2;  /* bit[2-3]: ���� */
        unsigned long  LPF_MODE_CURRENT_3G : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                              00��   10u
                                                              01��    5u
                                                              10��    5u
                                                              11��    3u
                                                              Ĭ�����÷�����
                                                              LTE:00   GSM:11   Others:01 */
        unsigned long  FC_B2_3G            : 1;  /* bit[6]  : TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_3G��˵���� */
        unsigned long  TX_MODE_CLK_B3_3G   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_3G_ANA_2_UNION;
#define ABB_TX_CH1_3G_ANA_2_CURRENT_MODE_OP_3G_START   (0)
#define ABB_TX_CH1_3G_ANA_2_CURRENT_MODE_OP_3G_END     (1)
#define ABB_TX_CH1_3G_ANA_2_LPF_MODE_CURRENT_3G_START  (4)
#define ABB_TX_CH1_3G_ANA_2_LPF_MODE_CURRENT_3G_END    (5)
#define ABB_TX_CH1_3G_ANA_2_FC_B2_3G_START             (6)
#define ABB_TX_CH1_3G_ANA_2_FC_B2_3G_END               (6)
#define ABB_TX_CH1_3G_ANA_2_TX_MODE_CLK_B3_3G_START    (7)
#define ABB_TX_CH1_3G_ANA_2_TX_MODE_CLK_B3_3G_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH1_3G_ANA_3_UNION
 �ṹ˵��  : tx_ch1_3g_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x18C����ֵ:0x18�����:8
 �Ĵ���˵��: CH1 TX 3G���üĴ����������߿��߼�������ch1_reg_analog_wr50��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT_3G     : 3;  /* bit[0-2]: LPF OP1 ����ģʽ����
                                                          000��5u
                                                          001��4u
                                                          010��3u
                                                          011��2u
                                                          100��9u
                                                          101��8u
                                                          110��7u
                                                          111��6u */
        unsigned long  DUM_EN_Q_3G     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  DUM_EN_I_3G     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  reserved        : 2;  /* bit[5-6]: ���� */
        unsigned long  TX_CLKD_CTRL_3G : 1;  /* bit[7]  : TX ����ʱ����ѡ��
                                                          0������(Ĭ��)
                                                          1������ */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH1_3G_ANA_3_UNION;
#define ABB_TX_CH1_3G_ANA_3_TXLPF_CT_3G_START      (0)
#define ABB_TX_CH1_3G_ANA_3_TXLPF_CT_3G_END        (2)
#define ABB_TX_CH1_3G_ANA_3_DUM_EN_Q_3G_START      (3)
#define ABB_TX_CH1_3G_ANA_3_DUM_EN_Q_3G_END        (3)
#define ABB_TX_CH1_3G_ANA_3_DUM_EN_I_3G_START      (4)
#define ABB_TX_CH1_3G_ANA_3_DUM_EN_I_3G_END        (4)
#define ABB_TX_CH1_3G_ANA_3_TX_CLKD_CTRL_3G_START  (7)
#define ABB_TX_CH1_3G_ANA_3_TX_CLKD_CTRL_3G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_ANA_6_UNION
 �ṹ˵��  : rx_2g_ana_6 �Ĵ����ṹ���塣��ַƫ����:0x18F����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2G���üĴ����������߿��߼�������reg_analog_wr56��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved    : 2;  /* bit[0-1]: ���� */
        unsigned long  BWCT_OP3_2G : 2;  /* bit[2-3]: BWCT_OP3 OP3�������
                                                      1x�� LTEģʽ
                                                      01�� WDC &amp; X ģʽ
                                                      00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP2_2G : 2;  /* bit[4-5]: BWCT_OP2 OP2�������
                                                      1x�� LTEģʽ
                                                      01�� WDC &amp; X ģʽ
                                                      00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP1_2G : 2;  /* bit[6-7]: BWCT_OP1 OP1�������
                                                      1x�� LTEģʽ
                                                      01�� WDC &amp; X ģʽ
                                                      00�� W &amp; Gģʽ */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_6_UNION;
#define ABB_RX_2G_ANA_6_BWCT_OP3_2G_START  (2)
#define ABB_RX_2G_ANA_6_BWCT_OP3_2G_END    (3)
#define ABB_RX_2G_ANA_6_BWCT_OP2_2G_START  (4)
#define ABB_RX_2G_ANA_6_BWCT_OP2_2G_END    (5)
#define ABB_RX_2G_ANA_6_BWCT_OP1_2G_START  (6)
#define ABB_RX_2G_ANA_6_BWCT_OP1_2G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_ANA_7_UNION
 �ṹ˵��  : rx_2g_ana_7 �Ĵ����ṹ���塣��ַƫ����:0x190����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2G���üĴ����������߿��߼�������reg_analog_wr57��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved           : 4;  /* bit[0-3]: ���� */
        unsigned long  QT_REF_SEL_2G      : 1;  /* bit[4]  : �������ο���ѹѡ��
                                                             0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
                                                             1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ */
        unsigned long  GMBIAS_EN_2G       : 1;  /* bit[5]  : OP3�Ƿ�ʹ��Gm_biasƫ��
                                                             0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
                                                             1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ�� */
        unsigned long  MODU_DEPTH_CTRL_2G : 1;  /* bit[6]  : ������DAC������ȿ���
                                                             0 �������0.5
                                                             1 �������0.75 */
        unsigned long  RX_DAC_LP_CTRL_2G  : 1;  /* bit[7]  : ������DACƫ�õ�������
                                                             0 ��������������ܺ�
                                                             1 С�������������ܲ� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_7_UNION;
#define ABB_RX_2G_ANA_7_QT_REF_SEL_2G_START       (4)
#define ABB_RX_2G_ANA_7_QT_REF_SEL_2G_END         (4)
#define ABB_RX_2G_ANA_7_GMBIAS_EN_2G_START        (5)
#define ABB_RX_2G_ANA_7_GMBIAS_EN_2G_END          (5)
#define ABB_RX_2G_ANA_7_MODU_DEPTH_CTRL_2G_START  (6)
#define ABB_RX_2G_ANA_7_MODU_DEPTH_CTRL_2G_END    (6)
#define ABB_RX_2G_ANA_7_RX_DAC_LP_CTRL_2G_START   (7)
#define ABB_RX_2G_ANA_7_RX_DAC_LP_CTRL_2G_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_ANA_8_UNION
 �ṹ˵��  : rx_2g_ana_8 �Ĵ����ṹ���塣��ַƫ����:0x191����ֵ:0x50�����:8
 �Ĵ���˵��: RX 2G���üĴ����������߿��߼�������reg_analog_wr58��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA_2G : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                          00000 ����DACʱ����ǰ������
                                                          11111 ����DACʱ����ǰ����� */
        unsigned long  CK_CTRL_MODE_2G : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                          00�� LTEģʽ
                                                          01�� WDC &amp; X &amp; TDS_Aģʽ
                                                          1x�� W &amp; G &amp; TDS_Bģʽ */
        unsigned long  reserved        : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_8_UNION;
#define ABB_RX_2G_ANA_8_CK_CTRL_DATA_2G_START  (0)
#define ABB_RX_2G_ANA_8_CK_CTRL_DATA_2G_END    (4)
#define ABB_RX_2G_ANA_8_CK_CTRL_MODE_2G_START  (5)
#define ABB_RX_2G_ANA_8_CK_CTRL_MODE_2G_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_ANA_9_UNION
 �ṹ˵��  : rx_2g_ana_9 �Ĵ����ṹ���塣��ַƫ����:0x192����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2G���üĴ����������߿��߼�������reg_analog_wr59��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_sel_2g    : 1;  /* bit[0]  : AD&amp;DA��WPLL��SCPLLѡ���źš�
                                                         0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
                                                         1��ѡ��WPLL����3g��xĬ��ѡ��WPLL�� */
        unsigned long  reserved       : 5;  /* bit[1-5]: ���� */
        unsigned long  blk_len_sel_2g : 2;  /* bit[6-7]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                         2'b00��2560chip��(WģĬ��)
                                                         2'b01��512chip��
                                                         2'b10��1024chip��(XģĬ��)
                                                         2'b11��2048chip�� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_9_UNION;
#define ABB_RX_2G_ANA_9_wpll_sel_2g_START     (0)
#define ABB_RX_2G_ANA_9_wpll_sel_2g_END       (0)
#define ABB_RX_2G_ANA_9_blk_len_sel_2g_START  (6)
#define ABB_RX_2G_ANA_9_blk_len_sel_2g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_3G_ANA_6_UNION
 �ṹ˵��  : rx_ch0_3g_ana_6 �Ĵ����ṹ���塣��ַƫ����:0x195����ֵ:0x00�����:8
 �Ĵ���˵��: RX 3G���üĴ����������߿��߼�������reg_analog_wr56��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved        : 2;  /* bit[0-1]: ���� */
        unsigned long  BWCT_OP3_3G     : 2;  /* bit[2-3]: BWCT_OP3 OP3�������
                                                          1x�� LTEģʽ
                                                          01�� WDC &amp; X ģʽ
                                                          00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP2_3G     : 2;  /* bit[4-5]: BWCT_OP2 OP2�������
                                                          1x�� LTEģʽ
                                                          01�� WDC &amp; X ģʽ
                                                          00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP1_CH0_3G : 2;  /* bit[6-7]: BWCT_OP1 OP1�������
                                                          1x�� LTEģʽ
                                                          01�� WDC &amp; X ģʽ
                                                          00�� W &amp; Gģʽ */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_6_UNION;
#define ABB_RX_CH0_3G_ANA_6_BWCT_OP3_3G_START      (2)
#define ABB_RX_CH0_3G_ANA_6_BWCT_OP3_3G_END        (3)
#define ABB_RX_CH0_3G_ANA_6_BWCT_OP2_3G_START      (4)
#define ABB_RX_CH0_3G_ANA_6_BWCT_OP2_3G_END        (5)
#define ABB_RX_CH0_3G_ANA_6_BWCT_OP1_CH0_3G_START  (6)
#define ABB_RX_CH0_3G_ANA_6_BWCT_OP1_CH0_3G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_3G_ANA_7_UNION
 �ṹ˵��  : rx_ch0_3g_ana_7 �Ĵ����ṹ���塣��ַƫ����:0x196����ֵ:0x00�����:8
 �Ĵ���˵��: RX 3G���üĴ����������߿��߼�������reg_analog_wr57��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved              : 4;  /* bit[0-3]: ���� */
        unsigned long  QT_REF_SEL_3G         : 1;  /* bit[4]  : �������ο���ѹѡ��
                                                                0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
                                                                1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ */
        unsigned long  GMBIAS_EN_3G          : 1;  /* bit[5]  : OP3�Ƿ�ʹ��Gm_biasƫ��
                                                                0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
                                                                1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ�� */
        unsigned long  MODU_DEPTH_CTRL_3G    : 1;  /* bit[6]  : ������DAC������ȿ���
                                                                0 �������0.5
                                                                1 �������0.75 */
        unsigned long  RX_DAC_LP_CTRL_CH0_3G : 1;  /* bit[7]  : ������DACƫ�õ�������
                                                                0 ��������������ܺ�
                                                                1 С�������������ܲ� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_7_UNION;
#define ABB_RX_CH0_3G_ANA_7_QT_REF_SEL_3G_START          (4)
#define ABB_RX_CH0_3G_ANA_7_QT_REF_SEL_3G_END            (4)
#define ABB_RX_CH0_3G_ANA_7_GMBIAS_EN_3G_START           (5)
#define ABB_RX_CH0_3G_ANA_7_GMBIAS_EN_3G_END             (5)
#define ABB_RX_CH0_3G_ANA_7_MODU_DEPTH_CTRL_3G_START     (6)
#define ABB_RX_CH0_3G_ANA_7_MODU_DEPTH_CTRL_3G_END       (6)
#define ABB_RX_CH0_3G_ANA_7_RX_DAC_LP_CTRL_CH0_3G_START  (7)
#define ABB_RX_CH0_3G_ANA_7_RX_DAC_LP_CTRL_CH0_3G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_3G_ANA_8_UNION
 �ṹ˵��  : rx_ch0_3g_ana_8 �Ĵ����ṹ���塣��ַƫ����:0x197����ֵ:0x50�����:8
 �Ĵ���˵��: RX 3G���üĴ����������߿��߼�������reg_analog_wr58��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA_3G : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                          00000 ����DACʱ����ǰ������
                                                          11111 ����DACʱ����ǰ����� */
        unsigned long  CK_CTRL_MODE_3G : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                          00�� LTEģʽ
                                                          01�� WDC &amp; X &amp; TDS_Aģʽ
                                                          1x�� W &amp; G &amp; TDS_Bģʽ */
        unsigned long  reserved        : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_8_UNION;
#define ABB_RX_CH0_3G_ANA_8_CK_CTRL_DATA_3G_START  (0)
#define ABB_RX_CH0_3G_ANA_8_CK_CTRL_DATA_3G_END    (4)
#define ABB_RX_CH0_3G_ANA_8_CK_CTRL_MODE_3G_START  (5)
#define ABB_RX_CH0_3G_ANA_8_CK_CTRL_MODE_3G_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_3G_ANA_9_UNION
 �ṹ˵��  : rx_ch0_3g_ana_9 �Ĵ����ṹ���塣��ַƫ����:0x198����ֵ:0x01�����:8
 �Ĵ���˵��: RX 3G���üĴ����������߿��߼�������reg_analog_wr59��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_sel_ch0_3g    : 1;  /* bit[0]  : AD&amp;DA��WPLL��SCPLLѡ���źš�
                                                             0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
                                                             1��ѡ��WPLL����3g��xĬ��ѡ��WPLL�� */
        unsigned long  reserved           : 5;  /* bit[1-5]: ���� */
        unsigned long  blk_len_sel_ch0_3g : 2;  /* bit[6-7]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                             2'b00��2560chip��(WģĬ��)
                                                             2'b01��512chip��
                                                             2'b10��1024chip��(XģĬ��)
                                                             2'b11��2048chip�� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_ANA_9_UNION;
#define ABB_RX_CH0_3G_ANA_9_wpll_sel_ch0_3g_START     (0)
#define ABB_RX_CH0_3G_ANA_9_wpll_sel_ch0_3g_END       (0)
#define ABB_RX_CH0_3G_ANA_9_blk_len_sel_ch0_3g_START  (6)
#define ABB_RX_CH0_3G_ANA_9_blk_len_sel_ch0_3g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_4G_ANA_6_UNION
 �ṹ˵��  : rx_ch0_4g_ana_6 �Ĵ����ṹ���塣��ַƫ����:0x19B����ֵ:0xA8�����:8
 �Ĵ���˵��: RX 4G���üĴ����������߿��߼�������reg_analog_wr56��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved        : 2;  /* bit[0-1]: ���� */
        unsigned long  BWCT_OP3_4G     : 2;  /* bit[2-3]: BWCT_OP3 OP3�������
                                                          1x�� LTEģʽ
                                                          01�� WDC &amp; X ģʽ
                                                          00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP2_4G     : 2;  /* bit[4-5]: BWCT_OP2 OP2�������
                                                          1x�� LTEģʽ
                                                          01�� WDC &amp; X ģʽ
                                                          00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP1_CH0_4G : 2;  /* bit[6-7]: BWCT_OP1 OP1�������
                                                          1x�� LTEģʽ
                                                          01�� WDC &amp; X ģʽ
                                                          00�� W &amp; Gģʽ */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_6_UNION;
#define ABB_RX_CH0_4G_ANA_6_BWCT_OP3_4G_START      (2)
#define ABB_RX_CH0_4G_ANA_6_BWCT_OP3_4G_END        (3)
#define ABB_RX_CH0_4G_ANA_6_BWCT_OP2_4G_START      (4)
#define ABB_RX_CH0_4G_ANA_6_BWCT_OP2_4G_END        (5)
#define ABB_RX_CH0_4G_ANA_6_BWCT_OP1_CH0_4G_START  (6)
#define ABB_RX_CH0_4G_ANA_6_BWCT_OP1_CH0_4G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_4G_ANA_7_UNION
 �ṹ˵��  : rx_ch0_4g_ana_7 �Ĵ����ṹ���塣��ַƫ����:0x19C����ֵ:0x00�����:8
 �Ĵ���˵��: RX 4G���üĴ����������߿��߼�������reg_analog_wr57��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved              : 4;  /* bit[0-3]: ���� */
        unsigned long  QT_REF_SEL_4G         : 1;  /* bit[4]  : �������ο���ѹѡ��
                                                                0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
                                                                1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ */
        unsigned long  GMBIAS_EN_4G          : 1;  /* bit[5]  : OP3�Ƿ�ʹ��Gm_biasƫ��
                                                                0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
                                                                1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ�� */
        unsigned long  MODU_DEPTH_CTRL_4G    : 1;  /* bit[6]  : ������DAC������ȿ���
                                                                0 �������0.5
                                                                1 �������0.75 */
        unsigned long  RX_DAC_LP_CTRL_CH0_4G : 1;  /* bit[7]  : ������DACƫ�õ�������
                                                                0 ��������������ܺ�
                                                                1 С�������������ܲ� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_7_UNION;
#define ABB_RX_CH0_4G_ANA_7_QT_REF_SEL_4G_START          (4)
#define ABB_RX_CH0_4G_ANA_7_QT_REF_SEL_4G_END            (4)
#define ABB_RX_CH0_4G_ANA_7_GMBIAS_EN_4G_START           (5)
#define ABB_RX_CH0_4G_ANA_7_GMBIAS_EN_4G_END             (5)
#define ABB_RX_CH0_4G_ANA_7_MODU_DEPTH_CTRL_4G_START     (6)
#define ABB_RX_CH0_4G_ANA_7_MODU_DEPTH_CTRL_4G_END       (6)
#define ABB_RX_CH0_4G_ANA_7_RX_DAC_LP_CTRL_CH0_4G_START  (7)
#define ABB_RX_CH0_4G_ANA_7_RX_DAC_LP_CTRL_CH0_4G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_4G_ANA_8_UNION
 �ṹ˵��  : rx_ch0_4g_ana_8 �Ĵ����ṹ���塣��ַƫ����:0x19D����ֵ:0x10�����:8
 �Ĵ���˵��: RX 4G���üĴ����������߿��߼�������reg_analog_wr58��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA_4G : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                          00000 ����DACʱ����ǰ������
                                                          11111 ����DACʱ����ǰ����� */
        unsigned long  CK_CTRL_MODE_4G : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                          00�� LTEģʽ
                                                          01�� WDC &amp; X &amp; TDS_Aģʽ
                                                          1x�� W &amp; G &amp; TDS_Bģʽ */
        unsigned long  reserved        : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_8_UNION;
#define ABB_RX_CH0_4G_ANA_8_CK_CTRL_DATA_4G_START  (0)
#define ABB_RX_CH0_4G_ANA_8_CK_CTRL_DATA_4G_END    (4)
#define ABB_RX_CH0_4G_ANA_8_CK_CTRL_MODE_4G_START  (5)
#define ABB_RX_CH0_4G_ANA_8_CK_CTRL_MODE_4G_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_4G_ANA_9_UNION
 �ṹ˵��  : rx_ch0_4g_ana_9 �Ĵ����ṹ���塣��ַƫ����:0x19E����ֵ:0x00�����:8
 �Ĵ���˵��: RX 4G���üĴ����������߿��߼�������reg_analog_wr59��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_sel_ch0_4g    : 1;  /* bit[0]  : AD&amp;DA��WPLL��SCPLLѡ���źš�
                                                             0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
                                                             1��ѡ��WPLL����3g��xĬ��ѡ��WPLL�� */
        unsigned long  reserved           : 5;  /* bit[1-5]: ���� */
        unsigned long  blk_len_sel_ch0_4g : 2;  /* bit[6-7]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                             2'b00��2560chip��(WģĬ��)
                                                             2'b01��512chip��
                                                             2'b10��1024chip��(XģĬ��)
                                                             2'b11��2048chip�� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_ANA_9_UNION;
#define ABB_RX_CH0_4G_ANA_9_wpll_sel_ch0_4g_START     (0)
#define ABB_RX_CH0_4G_ANA_9_wpll_sel_ch0_4g_END       (0)
#define ABB_RX_CH0_4G_ANA_9_blk_len_sel_ch0_4g_START  (6)
#define ABB_RX_CH0_4G_ANA_9_blk_len_sel_ch0_4g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_ANA_6_UNION
 �ṹ˵��  : rx_tds_ana_6 �Ĵ����ṹ���塣��ַƫ����:0x1A1����ֵ:0x00�����:8
 �Ĵ���˵��: RX TDS���üĴ����������߿��߼�������reg_analog_wr56��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved     : 2;  /* bit[0-1]: ���� */
        unsigned long  BWCT_OP3_TDS : 2;  /* bit[2-3]: BWCT_OP3 OP3�������
                                                       1x�� LTEģʽ
                                                       01�� WDC &amp; X ģʽ
                                                       00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP2_TDS : 2;  /* bit[4-5]: BWCT_OP2 OP2�������
                                                       1x�� LTEģʽ
                                                       01�� WDC &amp; X ģʽ
                                                       00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP1_TDS : 2;  /* bit[6-7]: BWCT_OP1 OP1�������
                                                       1x�� LTEģʽ
                                                       01�� WDC &amp; X ģʽ
                                                       00�� W &amp; Gģʽ */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_6_UNION;
#define ABB_RX_TDS_ANA_6_BWCT_OP3_TDS_START  (2)
#define ABB_RX_TDS_ANA_6_BWCT_OP3_TDS_END    (3)
#define ABB_RX_TDS_ANA_6_BWCT_OP2_TDS_START  (4)
#define ABB_RX_TDS_ANA_6_BWCT_OP2_TDS_END    (5)
#define ABB_RX_TDS_ANA_6_BWCT_OP1_TDS_START  (6)
#define ABB_RX_TDS_ANA_6_BWCT_OP1_TDS_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_ANA_7_UNION
 �ṹ˵��  : rx_tds_ana_7 �Ĵ����ṹ���塣��ַƫ����:0x1A2����ֵ:0x00�����:8
 �Ĵ���˵��: RX TDS���üĴ����������߿��߼�������reg_analog_wr57��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved            : 4;  /* bit[0-3]: ���� */
        unsigned long  QT_REF_SEL_TDS      : 1;  /* bit[4]  : �������ο���ѹѡ��
                                                              0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
                                                              1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ */
        unsigned long  GMBIAS_EN_TDS       : 1;  /* bit[5]  : OP3�Ƿ�ʹ��Gm_biasƫ��
                                                              0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
                                                              1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ�� */
        unsigned long  MODU_DEPTH_CTRL_TDS : 1;  /* bit[6]  : ������DAC������ȿ���
                                                              0 �������0.5
                                                              1 �������0.75 */
        unsigned long  RX_DAC_LP_CTRL_TDS  : 1;  /* bit[7]  : ������DACƫ�õ�������
                                                              0 ��������������ܺ�
                                                              1 С�������������ܲ� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_7_UNION;
#define ABB_RX_TDS_ANA_7_QT_REF_SEL_TDS_START       (4)
#define ABB_RX_TDS_ANA_7_QT_REF_SEL_TDS_END         (4)
#define ABB_RX_TDS_ANA_7_GMBIAS_EN_TDS_START        (5)
#define ABB_RX_TDS_ANA_7_GMBIAS_EN_TDS_END          (5)
#define ABB_RX_TDS_ANA_7_MODU_DEPTH_CTRL_TDS_START  (6)
#define ABB_RX_TDS_ANA_7_MODU_DEPTH_CTRL_TDS_END    (6)
#define ABB_RX_TDS_ANA_7_RX_DAC_LP_CTRL_TDS_START   (7)
#define ABB_RX_TDS_ANA_7_RX_DAC_LP_CTRL_TDS_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_ANA_8_UNION
 �ṹ˵��  : rx_tds_ana_8 �Ĵ����ṹ���塣��ַƫ����:0x1A3����ֵ:0x50�����:8
 �Ĵ���˵��: RX TDS���üĴ����������߿��߼�������reg_analog_wr58��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA_TDS : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                           00000 ����DACʱ����ǰ������
                                                           11111 ����DACʱ����ǰ����� */
        unsigned long  CK_CTRL_MODE_TDS : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                           00�� LTEģʽ
                                                           01�� WDC &amp; X &amp; TDS_Aģʽ
                                                           1x�� W &amp; G &amp; TDS_Bģʽ */
        unsigned long  reserved         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_8_UNION;
#define ABB_RX_TDS_ANA_8_CK_CTRL_DATA_TDS_START  (0)
#define ABB_RX_TDS_ANA_8_CK_CTRL_DATA_TDS_END    (4)
#define ABB_RX_TDS_ANA_8_CK_CTRL_MODE_TDS_START  (5)
#define ABB_RX_TDS_ANA_8_CK_CTRL_MODE_TDS_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_ANA_9_UNION
 �ṹ˵��  : rx_tds_ana_9 �Ĵ����ṹ���塣��ַƫ����:0x1A4����ֵ:0x00�����:8
 �Ĵ���˵��: RX TDS���üĴ����������߿��߼�������reg_analog_wr59��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_sel_tds    : 1;  /* bit[0]  : AD&amp;DA��WPLL��SCPLLѡ���źš�
                                                          0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
                                                          1��ѡ��WPLL����3g��xĬ��ѡ��WPLL�� */
        unsigned long  reserved        : 5;  /* bit[1-5]: ���� */
        unsigned long  blk_len_sel_tds : 2;  /* bit[6-7]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                          2'b00��2560chip��(WģĬ��)
                                                          2'b01��512chip��
                                                          2'b10��1024chip��(XģĬ��)
                                                          2'b11��2048chip�� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_9_UNION;
#define ABB_RX_TDS_ANA_9_wpll_sel_tds_START     (0)
#define ABB_RX_TDS_ANA_9_wpll_sel_tds_END       (0)
#define ABB_RX_TDS_ANA_9_blk_len_sel_tds_START  (6)
#define ABB_RX_TDS_ANA_9_blk_len_sel_tds_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_ANA_6_UNION
 �ṹ˵��  : rx_idle_ana_6 �Ĵ����ṹ���塣��ַƫ����:0x1A7����ֵ:0x00�����:8
 �Ĵ���˵��: RX IDLE���üĴ����������߿��߼�������reg_analog_wr56��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved      : 2;  /* bit[0-1]: ���� */
        unsigned long  BWCT_OP3_IDLE : 2;  /* bit[2-3]: BWCT_OP3 OP3�������
                                                        1x�� LTEģʽ
                                                        01�� WDC &amp; X ģʽ
                                                        00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP2_IDLE : 2;  /* bit[4-5]: BWCT_OP2 OP2�������
                                                        1x�� LTEģʽ
                                                        01�� WDC &amp; X ģʽ
                                                        00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP1_IDLE : 2;  /* bit[6-7]: BWCT_OP1 OP1�������
                                                        1x�� LTEģʽ
                                                        01�� WDC &amp; X ģʽ
                                                        00�� W &amp; Gģʽ */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_6_UNION;
#define ABB_RX_IDLE_ANA_6_BWCT_OP3_IDLE_START  (2)
#define ABB_RX_IDLE_ANA_6_BWCT_OP3_IDLE_END    (3)
#define ABB_RX_IDLE_ANA_6_BWCT_OP2_IDLE_START  (4)
#define ABB_RX_IDLE_ANA_6_BWCT_OP2_IDLE_END    (5)
#define ABB_RX_IDLE_ANA_6_BWCT_OP1_IDLE_START  (6)
#define ABB_RX_IDLE_ANA_6_BWCT_OP1_IDLE_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_ANA_7_UNION
 �ṹ˵��  : rx_idle_ana_7 �Ĵ����ṹ���塣��ַƫ����:0x1A8����ֵ:0x00�����:8
 �Ĵ���˵��: RX IDLE���üĴ����������߿��߼�������reg_analog_wr57��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved             : 4;  /* bit[0-3]: ���� */
        unsigned long  QT_REF_SEL_IDLE      : 1;  /* bit[4]  : �������ο���ѹѡ��
                                                               0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
                                                               1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ */
        unsigned long  GMBIAS_EN_IDLE       : 1;  /* bit[5]  : OP3�Ƿ�ʹ��Gm_biasƫ��
                                                               0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
                                                               1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ�� */
        unsigned long  MODU_DEPTH_CTRL_IDLE : 1;  /* bit[6]  : ������DAC������ȿ���
                                                               0 �������0.5
                                                               1 �������0.75 */
        unsigned long  RX_DAC_LP_CTRL_IDLE  : 1;  /* bit[7]  : ������DACƫ�õ�������
                                                               0 ��������������ܺ�
                                                               1 С�������������ܲ� */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_7_UNION;
#define ABB_RX_IDLE_ANA_7_QT_REF_SEL_IDLE_START       (4)
#define ABB_RX_IDLE_ANA_7_QT_REF_SEL_IDLE_END         (4)
#define ABB_RX_IDLE_ANA_7_GMBIAS_EN_IDLE_START        (5)
#define ABB_RX_IDLE_ANA_7_GMBIAS_EN_IDLE_END          (5)
#define ABB_RX_IDLE_ANA_7_MODU_DEPTH_CTRL_IDLE_START  (6)
#define ABB_RX_IDLE_ANA_7_MODU_DEPTH_CTRL_IDLE_END    (6)
#define ABB_RX_IDLE_ANA_7_RX_DAC_LP_CTRL_IDLE_START   (7)
#define ABB_RX_IDLE_ANA_7_RX_DAC_LP_CTRL_IDLE_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_ANA_8_UNION
 �ṹ˵��  : rx_idle_ana_8 �Ĵ����ṹ���塣��ַƫ����:0x1A9����ֵ:0x50�����:8
 �Ĵ���˵��: RX IDLE���üĴ����������߿��߼�������reg_analog_wr58��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA_IDLE : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                            00000 ����DACʱ����ǰ������
                                                            11111 ����DACʱ����ǰ����� */
        unsigned long  CK_CTRL_MODE_IDLE : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                            00�� LTEģʽ
                                                            01�� WDC &amp; X &amp; TDS_Aģʽ
                                                            1x�� W &amp; G &amp; TDS_Bģʽ */
        unsigned long  reserved          : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_8_UNION;
#define ABB_RX_IDLE_ANA_8_CK_CTRL_DATA_IDLE_START  (0)
#define ABB_RX_IDLE_ANA_8_CK_CTRL_DATA_IDLE_END    (4)
#define ABB_RX_IDLE_ANA_8_CK_CTRL_MODE_IDLE_START  (5)
#define ABB_RX_IDLE_ANA_8_CK_CTRL_MODE_IDLE_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_ANA_9_UNION
 �ṹ˵��  : rx_idle_ana_9 �Ĵ����ṹ���塣��ַƫ����:0x1AA����ֵ:0x00�����:8
 �Ĵ���˵��: RX IDLE���üĴ����������߿��߼�������reg_analog_wr59��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_sel_idle    : 1;  /* bit[0]  : AD&amp;DA��WPLL��SCPLLѡ���źš�
                                                           0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
                                                           1��ѡ��WPLL����3g��xĬ��ѡ��WPLL�� */
        unsigned long  reserved         : 5;  /* bit[1-5]: ���� */
        unsigned long  blk_len_sel_idle : 2;  /* bit[6-7]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                           2'b00��2560chip��(WģĬ��)
                                                           2'b01��512chip��
                                                           2'b10��1024chip��(XģĬ��)
                                                           2'b11��2048chip�� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_9_UNION;
#define ABB_RX_IDLE_ANA_9_wpll_sel_idle_START     (0)
#define ABB_RX_IDLE_ANA_9_wpll_sel_idle_END       (0)
#define ABB_RX_IDLE_ANA_9_blk_len_sel_idle_START  (6)
#define ABB_RX_IDLE_ANA_9_blk_len_sel_idle_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_3G_ANA_6_UNION
 �ṹ˵��  : rx_ch1_3g_ana_6 �Ĵ����ṹ���塣��ַƫ����:0x1AD����ֵ:0x00�����:8
 �Ĵ���˵��: RX 3G���üĴ����������߿��߼�������reg_analog_wr56��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved        : 2;  /* bit[0-1]: ���� */
        unsigned long  BWCT_OP3_3G     : 2;  /* bit[2-3]: BWCT_OP3 OP3�������
                                                          1x�� LTEģʽ
                                                          01�� WDC &amp; X ģʽ
                                                          00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP2_3G     : 2;  /* bit[4-5]: BWCT_OP2 OP2�������
                                                          1x�� LTEģʽ
                                                          01�� WDC &amp; X ģʽ
                                                          00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP1_CH1_3G : 2;  /* bit[6-7]: BWCT_OP1 OP1�������
                                                          1x�� LTEģʽ
                                                          01�� WDC &amp; X ģʽ
                                                          00�� W &amp; Gģʽ */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_3G_ANA_6_UNION;
#define ABB_RX_CH1_3G_ANA_6_BWCT_OP3_3G_START      (2)
#define ABB_RX_CH1_3G_ANA_6_BWCT_OP3_3G_END        (3)
#define ABB_RX_CH1_3G_ANA_6_BWCT_OP2_3G_START      (4)
#define ABB_RX_CH1_3G_ANA_6_BWCT_OP2_3G_END        (5)
#define ABB_RX_CH1_3G_ANA_6_BWCT_OP1_CH1_3G_START  (6)
#define ABB_RX_CH1_3G_ANA_6_BWCT_OP1_CH1_3G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_3G_ANA_7_UNION
 �ṹ˵��  : rx_ch1_3g_ana_7 �Ĵ����ṹ���塣��ַƫ����:0x1AE����ֵ:0x00�����:8
 �Ĵ���˵��: RX 3G���üĴ����������߿��߼�������reg_analog_wr57��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved              : 4;  /* bit[0-3]: ���� */
        unsigned long  QT_REF_SEL_3G         : 1;  /* bit[4]  : �������ο���ѹѡ��
                                                                0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
                                                                1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ */
        unsigned long  GMBIAS_EN_3G          : 1;  /* bit[5]  : OP3�Ƿ�ʹ��Gm_biasƫ��
                                                                0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
                                                                1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ�� */
        unsigned long  MODU_DEPTH_CTRL_3G    : 1;  /* bit[6]  : ������DAC������ȿ���
                                                                0 �������0.5
                                                                1 �������0.75 */
        unsigned long  RX_DAC_LP_CTRL_CH1_3G : 1;  /* bit[7]  : ������DACƫ�õ�������
                                                                0 ��������������ܺ�
                                                                1 С�������������ܲ� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_3G_ANA_7_UNION;
#define ABB_RX_CH1_3G_ANA_7_QT_REF_SEL_3G_START          (4)
#define ABB_RX_CH1_3G_ANA_7_QT_REF_SEL_3G_END            (4)
#define ABB_RX_CH1_3G_ANA_7_GMBIAS_EN_3G_START           (5)
#define ABB_RX_CH1_3G_ANA_7_GMBIAS_EN_3G_END             (5)
#define ABB_RX_CH1_3G_ANA_7_MODU_DEPTH_CTRL_3G_START     (6)
#define ABB_RX_CH1_3G_ANA_7_MODU_DEPTH_CTRL_3G_END       (6)
#define ABB_RX_CH1_3G_ANA_7_RX_DAC_LP_CTRL_CH1_3G_START  (7)
#define ABB_RX_CH1_3G_ANA_7_RX_DAC_LP_CTRL_CH1_3G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_3G_ANA_8_UNION
 �ṹ˵��  : rx_ch1_3g_ana_8 �Ĵ����ṹ���塣��ַƫ����:0x1AF����ֵ:0x50�����:8
 �Ĵ���˵��: RX 3G���üĴ����������߿��߼�������reg_analog_wr58��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA_3G : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                          00000 ����DACʱ����ǰ������
                                                          11111 ����DACʱ����ǰ����� */
        unsigned long  CK_CTRL_MODE_3G : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                          00�� LTEģʽ
                                                          01�� WDC &amp; X &amp; TDS_Aģʽ
                                                          1x�� W &amp; G &amp; TDS_Bģʽ */
        unsigned long  reserved        : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_3G_ANA_8_UNION;
#define ABB_RX_CH1_3G_ANA_8_CK_CTRL_DATA_3G_START  (0)
#define ABB_RX_CH1_3G_ANA_8_CK_CTRL_DATA_3G_END    (4)
#define ABB_RX_CH1_3G_ANA_8_CK_CTRL_MODE_3G_START  (5)
#define ABB_RX_CH1_3G_ANA_8_CK_CTRL_MODE_3G_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_3G_ANA_9_UNION
 �ṹ˵��  : rx_ch1_3g_ana_9 �Ĵ����ṹ���塣��ַƫ����:0x1B1����ֵ:0x01�����:8
 �Ĵ���˵��: RX 3G���üĴ����������߿��߼�������reg_analog_wr59��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_sel_ch1_3g    : 1;  /* bit[0]  : AD&amp;DA��WPLL��SCPLLѡ���źš�
                                                             0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
                                                             1��ѡ��WPLL����3g��xĬ��ѡ��WPLL�� */
        unsigned long  reserved           : 5;  /* bit[1-5]: ���� */
        unsigned long  blk_len_sel_ch1_3g : 2;  /* bit[6-7]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                             2'b00��2560chip��(WģĬ��)
                                                             2'b01��512chip��
                                                             2'b10��1024chip��(XģĬ��)
                                                             2'b11��2048chip�� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_3G_ANA_9_UNION;
#define ABB_RX_CH1_3G_ANA_9_wpll_sel_ch1_3g_START     (0)
#define ABB_RX_CH1_3G_ANA_9_wpll_sel_ch1_3g_END       (0)
#define ABB_RX_CH1_3G_ANA_9_blk_len_sel_ch1_3g_START  (6)
#define ABB_RX_CH1_3G_ANA_9_blk_len_sel_ch1_3g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_4G_ANA_6_UNION
 �ṹ˵��  : rx_ch1_4g_ana_6 �Ĵ����ṹ���塣��ַƫ����:0x1B4����ֵ:0xA8�����:8
 �Ĵ���˵��: RX 4G���üĴ����������߿��߼�������reg_analog_wr56��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved        : 2;  /* bit[0-1]: ���� */
        unsigned long  BWCT_OP3_4G     : 2;  /* bit[2-3]: BWCT_OP3 OP3�������
                                                          1x�� LTEģʽ
                                                          01�� WDC &amp; X ģʽ
                                                          00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP2_4G     : 2;  /* bit[4-5]: BWCT_OP2 OP2�������
                                                          1x�� LTEģʽ
                                                          01�� WDC &amp; X ģʽ
                                                          00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP1_CH1_4G : 2;  /* bit[6-7]: BWCT_OP1 OP1�������
                                                          1x�� LTEģʽ
                                                          01�� WDC &amp; X ģʽ
                                                          00�� W &amp; Gģʽ */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_4G_ANA_6_UNION;
#define ABB_RX_CH1_4G_ANA_6_BWCT_OP3_4G_START      (2)
#define ABB_RX_CH1_4G_ANA_6_BWCT_OP3_4G_END        (3)
#define ABB_RX_CH1_4G_ANA_6_BWCT_OP2_4G_START      (4)
#define ABB_RX_CH1_4G_ANA_6_BWCT_OP2_4G_END        (5)
#define ABB_RX_CH1_4G_ANA_6_BWCT_OP1_CH1_4G_START  (6)
#define ABB_RX_CH1_4G_ANA_6_BWCT_OP1_CH1_4G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_4G_ANA_7_UNION
 �ṹ˵��  : rx_ch1_4g_ana_7 �Ĵ����ṹ���塣��ַƫ����:0x1B5����ֵ:0x00�����:8
 �Ĵ���˵��: RX 4G���üĴ����������߿��߼�������reg_analog_wr57��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved              : 4;  /* bit[0-3]: ���� */
        unsigned long  QT_REF_SEL_4G         : 1;  /* bit[4]  : �������ο���ѹѡ��
                                                                0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
                                                                1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ */
        unsigned long  GMBIAS_EN_4G          : 1;  /* bit[5]  : OP3�Ƿ�ʹ��Gm_biasƫ��
                                                                0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
                                                                1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ�� */
        unsigned long  MODU_DEPTH_CTRL_4G    : 1;  /* bit[6]  : ������DAC������ȿ���
                                                                0 �������0.5
                                                                1 �������0.75 */
        unsigned long  RX_DAC_LP_CTRL_CH1_4G : 1;  /* bit[7]  : ������DACƫ�õ�������
                                                                0 ��������������ܺ�
                                                                1 С�������������ܲ� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_4G_ANA_7_UNION;
#define ABB_RX_CH1_4G_ANA_7_QT_REF_SEL_4G_START          (4)
#define ABB_RX_CH1_4G_ANA_7_QT_REF_SEL_4G_END            (4)
#define ABB_RX_CH1_4G_ANA_7_GMBIAS_EN_4G_START           (5)
#define ABB_RX_CH1_4G_ANA_7_GMBIAS_EN_4G_END             (5)
#define ABB_RX_CH1_4G_ANA_7_MODU_DEPTH_CTRL_4G_START     (6)
#define ABB_RX_CH1_4G_ANA_7_MODU_DEPTH_CTRL_4G_END       (6)
#define ABB_RX_CH1_4G_ANA_7_RX_DAC_LP_CTRL_CH1_4G_START  (7)
#define ABB_RX_CH1_4G_ANA_7_RX_DAC_LP_CTRL_CH1_4G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_4G_ANA_8_UNION
 �ṹ˵��  : rx_ch1_4g_ana_8 �Ĵ����ṹ���塣��ַƫ����:0x1B6����ֵ:0x10�����:8
 �Ĵ���˵��: RX 4G���üĴ����������߿��߼�������reg_analog_wr58��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA_4G : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                          00000 ����DACʱ����ǰ������
                                                          11111 ����DACʱ����ǰ����� */
        unsigned long  CK_CTRL_MODE_4G : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                          00�� LTEģʽ
                                                          01�� WDC &amp; X &amp; TDS_Aģʽ
                                                          1x�� W &amp; G &amp; TDS_Bģʽ */
        unsigned long  reserved        : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_4G_ANA_8_UNION;
#define ABB_RX_CH1_4G_ANA_8_CK_CTRL_DATA_4G_START  (0)
#define ABB_RX_CH1_4G_ANA_8_CK_CTRL_DATA_4G_END    (4)
#define ABB_RX_CH1_4G_ANA_8_CK_CTRL_MODE_4G_START  (5)
#define ABB_RX_CH1_4G_ANA_8_CK_CTRL_MODE_4G_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH1_4G_ANA_9_UNION
 �ṹ˵��  : rx_ch1_4g_ana_9 �Ĵ����ṹ���塣��ַƫ����:0x1B7����ֵ:0x00�����:8
 �Ĵ���˵��: RX 4G���üĴ����������߿��߼�������reg_analog_wr59��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_sel_ch1_4g    : 1;  /* bit[0]  : AD&amp;DA��WPLL��SCPLLѡ���źš�
                                                             0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
                                                             1��ѡ��WPLL����3g��xĬ��ѡ��WPLL�� */
        unsigned long  reserved           : 5;  /* bit[1-5]: ���� */
        unsigned long  blk_len_sel_ch1_4g : 2;  /* bit[6-7]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                             2'b00��2560chip��(WģĬ��)
                                                             2'b01��512chip��
                                                             2'b10��1024chip��(XģĬ��)
                                                             2'b11��2048chip�� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH1_4G_ANA_9_UNION;
#define ABB_RX_CH1_4G_ANA_9_wpll_sel_ch1_4g_START     (0)
#define ABB_RX_CH1_4G_ANA_9_wpll_sel_ch1_4g_END       (0)
#define ABB_RX_CH1_4G_ANA_9_blk_len_sel_ch1_4g_START  (6)
#define ABB_RX_CH1_4G_ANA_9_blk_len_sel_ch1_4g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_LINE_SEL_UNION
 �ṹ˵��  : ch1_line_sel �Ĵ����ṹ���塣��ַƫ����:0x1C0����ֵ:0x07�����:8
 �Ĵ���˵��: �߿�ǿ������ʹ�ܡ�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_en_sel : 1;  /* bit[0]  : RXAͨ���߿�ѡ��
                                                         0��tie to 0
                                                         1��from line ctrl */
        unsigned long  ch1_rxb_en_sel : 1;  /* bit[1]  : RXBͨ���߿�ѡ��
                                                         0��tie to 0
                                                         1��from line ctrl */
        unsigned long  ch1_tx_en_sel  : 1;  /* bit[2]  : TXͨ���߿�ѡ��
                                                         0��tie to 0
                                                         1��from line ctrl */
        unsigned long  reserved       : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_SEL_UNION;
#define ABB_CH1_LINE_SEL_ch1_rxa_en_sel_START  (0)
#define ABB_CH1_LINE_SEL_ch1_rxa_en_sel_END    (0)
#define ABB_CH1_LINE_SEL_ch1_rxb_en_sel_START  (1)
#define ABB_CH1_LINE_SEL_ch1_rxb_en_sel_END    (1)
#define ABB_CH1_LINE_SEL_ch1_tx_en_sel_START   (2)
#define ABB_CH1_LINE_SEL_ch1_tx_en_sel_END     (2)


/*****************************************************************************
 �ṹ��    : ABB_CH1_LINE_CFG_UNION
 �ṹ˵��  : ch1_line_cfg �Ĵ����ṹ���塣��ַƫ����:0x1C1����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�ǿ������ֵ��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_line_ctrl_mode_cfg : 3;  /* bit[0-2]: �߿��ź�CH1_LINE_CTRL_MODEǿ������ֵ
                                                                 0��IDLE
                                                                 1��Gģ
                                                                 2��Wģ
                                                                 3��LTEģ
                                                                 4��TDSģ
                                                                 5��ETģʽ
                                                                 6��APTģʽ
                                                                 7��CAģʽ */
        unsigned long  ch1_line_ctrl_mode_sel : 1;  /* bit[3]  : �߿��ź�CH1_LINE_CTRL_MODEǿ������ʹ�� */
        unsigned long  ch1_blk_en_cfg         : 1;  /* bit[4]  : �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ */
        unsigned long  ch1_blk_en_sel         : 1;  /* bit[5]  : �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ�� */
        unsigned long  ch1_cfr_en_cfg         : 1;  /* bit[6]  : �߿��ź�CH1_CFR_ENǿ������ֵ��V8R1���漰�� */
        unsigned long  ch1_cfr_en_sel         : 1;  /* bit[7]  : �߿��ź�CH1_CFR_ENǿ������ʹ�ܣ�V8R1���漰�� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_CFG_UNION;
#define ABB_CH1_LINE_CFG_ch1_line_ctrl_mode_cfg_START  (0)
#define ABB_CH1_LINE_CFG_ch1_line_ctrl_mode_cfg_END    (2)
#define ABB_CH1_LINE_CFG_ch1_line_ctrl_mode_sel_START  (3)
#define ABB_CH1_LINE_CFG_ch1_line_ctrl_mode_sel_END    (3)
#define ABB_CH1_LINE_CFG_ch1_blk_en_cfg_START          (4)
#define ABB_CH1_LINE_CFG_ch1_blk_en_cfg_END            (4)
#define ABB_CH1_LINE_CFG_ch1_blk_en_sel_START          (5)
#define ABB_CH1_LINE_CFG_ch1_blk_en_sel_END            (5)
#define ABB_CH1_LINE_CFG_ch1_cfr_en_cfg_START          (6)
#define ABB_CH1_LINE_CFG_ch1_cfr_en_cfg_END            (6)
#define ABB_CH1_LINE_CFG_ch1_cfr_en_sel_START          (7)
#define ABB_CH1_LINE_CFG_ch1_cfr_en_sel_END            (7)


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
        unsigned long  ch1_ee_clk_sel  : 1;  /* bit[1]  : ���ż���Զ��ſ�ʹ�ܣ�
                                                          0��ʹ��
                                                          1����ʹ��
                                                          ��V8R1���漰�� */
        unsigned long  ch1_cfr_clk_sel : 1;  /* bit[2]  : CFR�Զ��ſ�ʹ�ܣ�
                                                          0��ʹ��
                                                          1����ʹ��
                                                          ��V8R1���漰�� */
        unsigned long  reserved        : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_CLK_SEL_UNION;
#define ABB_CH1_CLK_SEL_ch1_blk_clk_sel_START  (0)
#define ABB_CH1_CLK_SEL_ch1_blk_clk_sel_END    (0)
#define ABB_CH1_CLK_SEL_ch1_ee_clk_sel_START   (1)
#define ABB_CH1_CLK_SEL_ch1_ee_clk_sel_END     (1)
#define ABB_CH1_CLK_SEL_ch1_cfr_clk_sel_START  (2)
#define ABB_CH1_CLK_SEL_ch1_cfr_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_CH0_LINE_SEL_UNION
 �ṹ˵��  : ch0_line_sel �Ĵ����ṹ���塣��ַƫ����:0x1D0����ֵ:0x07�����:8
 �Ĵ���˵��: �߿�ǿ������ʹ�ܡ�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_en_sel : 1;  /* bit[0]  : RXAͨ���߿�ѡ��
                                                         0��tie to 0
                                                         1��from line ctrl */
        unsigned long  ch0_rxb_en_sel : 1;  /* bit[1]  : RXBͨ���߿�ѡ��
                                                         0��tie to 0
                                                         1��from line ctrl */
        unsigned long  ch0_tx_en_sel  : 1;  /* bit[2]  : TXͨ���߿�ѡ��
                                                         0��tie to 0
                                                         1��from line ctrl */
        unsigned long  reserved       : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_SEL_UNION;
#define ABB_CH0_LINE_SEL_ch0_rxa_en_sel_START  (0)
#define ABB_CH0_LINE_SEL_ch0_rxa_en_sel_END    (0)
#define ABB_CH0_LINE_SEL_ch0_rxb_en_sel_START  (1)
#define ABB_CH0_LINE_SEL_ch0_rxb_en_sel_END    (1)
#define ABB_CH0_LINE_SEL_ch0_tx_en_sel_START   (2)
#define ABB_CH0_LINE_SEL_ch0_tx_en_sel_END     (2)


/*****************************************************************************
 �ṹ��    : ABB_CH0_LINE_CFG_UNION
 �ṹ˵��  : ch0_line_cfg �Ĵ����ṹ���塣��ַƫ����:0x1D1����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�ǿ������ֵ��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_line_ctrl_mode_cfg : 3;  /* bit[0-2]: �߿��ź�CH0_LINE_CTRL_MODEǿ������ֵ
                                                                 0��IDLE
                                                                 1��Gģ
                                                                 2��Wģ
                                                                 3��LTEģ
                                                                 4��TDSģ
                                                                 5��ETģʽ
                                                                 6��APTģʽ
                                                                 7��CAģʽ */
        unsigned long  ch0_line_ctrl_mode_sel : 1;  /* bit[3]  : �߿��ź�CH0_LINE_CTRL_MODEǿ������ʹ�� */
        unsigned long  ch0_blk_en_cfg         : 1;  /* bit[4]  : �߿��ź�CH0_RXA_BLK_EN, CH0_RXB_BLK_ENǿ������ֵ */
        unsigned long  ch0_blk_en_sel         : 1;  /* bit[5]  : �߿��ź�CH0_RXA_BLK_EN, CH0_RXB_BLK_ENǿ������ʹ�� */
        unsigned long  ch0_cfr_en_cfg         : 1;  /* bit[6]  : �߿��ź�CH0_CFR_ENǿ������ֵ��V8R1���漰�� */
        unsigned long  ch0_cfr_en_sel         : 1;  /* bit[7]  : �߿��ź�CH0_CFR_ENǿ������ʹ�ܣ�V8R1���漰�� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_CFG_UNION;
#define ABB_CH0_LINE_CFG_ch0_line_ctrl_mode_cfg_START  (0)
#define ABB_CH0_LINE_CFG_ch0_line_ctrl_mode_cfg_END    (2)
#define ABB_CH0_LINE_CFG_ch0_line_ctrl_mode_sel_START  (3)
#define ABB_CH0_LINE_CFG_ch0_line_ctrl_mode_sel_END    (3)
#define ABB_CH0_LINE_CFG_ch0_blk_en_cfg_START          (4)
#define ABB_CH0_LINE_CFG_ch0_blk_en_cfg_END            (4)
#define ABB_CH0_LINE_CFG_ch0_blk_en_sel_START          (5)
#define ABB_CH0_LINE_CFG_ch0_blk_en_sel_END            (5)
#define ABB_CH0_LINE_CFG_ch0_cfr_en_cfg_START          (6)
#define ABB_CH0_LINE_CFG_ch0_cfr_en_cfg_END            (6)
#define ABB_CH0_LINE_CFG_ch0_cfr_en_sel_START          (7)
#define ABB_CH0_LINE_CFG_ch0_cfr_en_sel_END            (7)


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
        unsigned long  ch0_ee_clk_sel  : 1;  /* bit[1]  : ���ż���Զ��ſ�ʹ�ܣ�
                                                          0��ʹ��
                                                          1����ʹ��
                                                          ��V8R1���漰�� */
        unsigned long  ch0_cfr_clk_sel : 1;  /* bit[2]  : CFR�Զ��ſ�ʹ�ܣ�
                                                          0��ʹ��
                                                          1����ʹ��
                                                          ��V8R1���漰�� */
        unsigned long  reserved        : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CLK_SEL_UNION;
#define ABB_CH0_CLK_SEL_ch0_blk_clk_sel_START  (0)
#define ABB_CH0_CLK_SEL_ch0_blk_clk_sel_END    (0)
#define ABB_CH0_CLK_SEL_ch0_ee_clk_sel_START   (1)
#define ABB_CH0_CLK_SEL_ch0_ee_clk_sel_END     (1)
#define ABB_CH0_CLK_SEL_ch0_cfr_clk_sel_START  (2)
#define ABB_CH0_CLK_SEL_ch0_cfr_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_CH1_LINE_RPT0_UNION
 �ṹ˵��  : ch1_line_rpt0 �Ĵ����ṹ���塣��ַƫ����:0x1E0����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_en_rpt : 1;  /* bit[0]  : RXA_EN�߿�״̬�ϱ� */
        unsigned long  ch1_rxb_en_rpt : 1;  /* bit[1]  : RXB_EN�߿�״̬�ϱ� */
        unsigned long  ch1_tx_en_rpt  : 1;  /* bit[2]  : TX_EN�߿�״̬�ϱ� */
        unsigned long  reserved       : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_RPT0_UNION;
#define ABB_CH1_LINE_RPT0_ch1_rxa_en_rpt_START  (0)
#define ABB_CH1_LINE_RPT0_ch1_rxa_en_rpt_END    (0)
#define ABB_CH1_LINE_RPT0_ch1_rxb_en_rpt_START  (1)
#define ABB_CH1_LINE_RPT0_ch1_rxb_en_rpt_END    (1)
#define ABB_CH1_LINE_RPT0_ch1_tx_en_rpt_START   (2)
#define ABB_CH1_LINE_RPT0_ch1_tx_en_rpt_END     (2)


/*****************************************************************************
 �ṹ��    : ABB_CH1_LINE_RPT1_UNION
 �ṹ˵��  : ch1_line_rpt1 �Ĵ����ṹ���塣��ַƫ����:0x1E1����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_line_ctrl_mode_rpt : 3;  /* bit[0-2]: �߿��ź�CH1_LINE_CTRL_MODE״̬�ϱ�
                                                                 0��IDLE
                                                                 1��Gģ
                                                                 2��Wģ
                                                                 3��LTEģ
                                                                 4��TDSģ
                                                                 5��ETģʽ
                                                                 6��APTģʽ
                                                                 7��CAģʽ */
        unsigned long  reserved_0             : 1;  /* bit[3]  : ���� */
        unsigned long  ch1_rxa_blk_en_rpt     : 1;  /* bit[4]  : RXA_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch1_rxb_blk_en_rpt     : 1;  /* bit[5]  : RXB_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch1_cfr_en_rpt         : 1;  /* bit[6]  : CFR_EN�߿�״̬�ϱ���V8R1���漰�� */
        unsigned long  reserved_1             : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_RPT1_UNION;
#define ABB_CH1_LINE_RPT1_ch1_line_ctrl_mode_rpt_START  (0)
#define ABB_CH1_LINE_RPT1_ch1_line_ctrl_mode_rpt_END    (2)
#define ABB_CH1_LINE_RPT1_ch1_rxa_blk_en_rpt_START      (4)
#define ABB_CH1_LINE_RPT1_ch1_rxa_blk_en_rpt_END        (4)
#define ABB_CH1_LINE_RPT1_ch1_rxb_blk_en_rpt_START      (5)
#define ABB_CH1_LINE_RPT1_ch1_rxb_blk_en_rpt_END        (5)
#define ABB_CH1_LINE_RPT1_ch1_cfr_en_rpt_START          (6)
#define ABB_CH1_LINE_RPT1_ch1_cfr_en_rpt_END            (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_MODE_RPT_UNION
 �ṹ˵��  : ch1_rx_mode_rpt �Ĵ����ṹ���塣��ַƫ����:0x1E2����ֵ:0x00�����:8
 �Ĵ���˵��: RX���ֹ���ģʽ�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved            : 1;  /* bit[0]  : ���� */
        unsigned long  ch1_rx_comp_fix_rpt : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶������ϱ���
                                                              0��ϵ�����̶����ɼĴ�������
                                                              1��ϵ���̶� */
        unsigned long  ch1_rx_hb_bp_rpt    : 1;  /* bit[2]  : RXͨ������˲���bypass�����ϱ���
                                                              0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                              1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  ch1_rx_rate_rpt     : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ����ϱ�(Hz)��
                                                                  2G,   3G_SC,  4G,  3G_DC,   TDS,   CA
                                                              00��2.167M,15.36M,61.44M,30.72M,30.72M,122.88M(Ĭ��)
                                                              01��------,------,30.72M,15.36M,10.24M,------
                                                              10��------,------,15.36M,------,------,------
                                                              11��------,------, 7.68M,------,------,------ */
        unsigned long  ch1_rx_mode_dig_rpt : 3;  /* bit[5-7]: RXͨ��ģʽ�����ϱ���
                                                              000��2G(Ĭ��)
                                                              001��3G_SC
                                                              010��4G &amp; ET &amp; APT
                                                              011��3G_DC
                                                              100��TDS
                                                              Others��CA */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_MODE_RPT_UNION;
#define ABB_CH1_RX_MODE_RPT_ch1_rx_comp_fix_rpt_START  (1)
#define ABB_CH1_RX_MODE_RPT_ch1_rx_comp_fix_rpt_END    (1)
#define ABB_CH1_RX_MODE_RPT_ch1_rx_hb_bp_rpt_START     (2)
#define ABB_CH1_RX_MODE_RPT_ch1_rx_hb_bp_rpt_END       (2)
#define ABB_CH1_RX_MODE_RPT_ch1_rx_rate_rpt_START      (3)
#define ABB_CH1_RX_MODE_RPT_ch1_rx_rate_rpt_END        (4)
#define ABB_CH1_RX_MODE_RPT_ch1_rx_mode_dig_rpt_START  (5)
#define ABB_CH1_RX_MODE_RPT_ch1_rx_mode_dig_rpt_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_MODE_RPT_UNION
 �ṹ˵��  : ch1_tx_mode_rpt �Ĵ����ṹ���塣��ַƫ����:0x1E3����ֵ:0x02�����:8
 �Ĵ���˵��: TX���ֹ���ģʽ�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_bp_rpt  : 1;  /* bit[0]  : TXͨ�������˲���bypass�����ϱ���
                                                              0����bypass(Ĭ��)
                                                              1��bypass */
        unsigned long  ch1_tx_hb_bp_rpt    : 1;  /* bit[1]  : TXͨ������˲���bypass�����ϱ���
                                                              0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
                                                              1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��) */
        unsigned long  ch1_tx_rate_rpt     : 3;  /* bit[2-4]: TXͨ��CIC�˲���������ʿ����ϱ���
                                                                   2G,     3G,     4G,      TDS,      CA
                                                                  (78M) (153.6M) (307.2M) (153.6M) (614.4M)
                                                              0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(Ĭ��)
                                                              1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                              2��-------,--------,15.36MHz,--------,--------
                                                              3��-------,--------, 7.68MHz,--------,--------
                                                              4��-------,--------, 3.84MHz,--------,--------
                                                              Others��Reserved */
        unsigned long  ch1_tx_mode_dig_rpt : 3;  /* bit[5-7]: TXͨ��ģʽ�����ϱ���
                                                              000��2G(Ĭ��)
                                                              001��3G
                                                              010��4G &amp; ET &amp; APT
                                                              011��TDS
                                                              Others��CA */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_MODE_RPT_UNION;
#define ABB_CH1_TX_MODE_RPT_ch1_tx_comp_bp_rpt_START   (0)
#define ABB_CH1_TX_MODE_RPT_ch1_tx_comp_bp_rpt_END     (0)
#define ABB_CH1_TX_MODE_RPT_ch1_tx_hb_bp_rpt_START     (1)
#define ABB_CH1_TX_MODE_RPT_ch1_tx_hb_bp_rpt_END       (1)
#define ABB_CH1_TX_MODE_RPT_ch1_tx_rate_rpt_START      (2)
#define ABB_CH1_TX_MODE_RPT_ch1_tx_rate_rpt_END        (4)
#define ABB_CH1_TX_MODE_RPT_ch1_tx_mode_dig_rpt_START  (5)
#define ABB_CH1_TX_MODE_RPT_ch1_tx_mode_dig_rpt_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_STATE_RPT_UNION
 �ṹ˵��  : ch1_rx_state_rpt �Ĵ����ṹ���塣��ַƫ����:0x1E4����ֵ:0x00�����:8
 �Ĵ���˵��: RX���ֹ���״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_aclk_rpt      : 1;  /* bit[0]: RXͨ��ģ����·ʱ�� */
        unsigned long  ch1_rx_clk_rpt       : 1;  /* bit[1]: RXͨ�����������·ʱ�� */
        unsigned long  ch1_rx_vld_rpt       : 1;  /* bit[2]: RXͨ�����������Чָʾ�ź� */
        unsigned long  ch1_rxa_data_rpt     : 1;  /* bit[3]: RXAͨ��������ݷ�תָʾ�ź� */
        unsigned long  ch1_rxa_overflow_rpt : 1;  /* bit[4]: RXAͨ����������ָʾ�ź� */
        unsigned long  ch1_rxb_data_rpt     : 1;  /* bit[5]: RXBͨ��������ݷ�תָʾ�ź� */
        unsigned long  ch1_rxb_overflow_rpt : 1;  /* bit[6]: RXBͨ����������ָʾ�ź� */
        unsigned long  reserved             : 1;  /* bit[7]: Reserved */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_STATE_RPT_UNION;
#define ABB_CH1_RX_STATE_RPT_ch1_rx_aclk_rpt_START       (0)
#define ABB_CH1_RX_STATE_RPT_ch1_rx_aclk_rpt_END         (0)
#define ABB_CH1_RX_STATE_RPT_ch1_rx_clk_rpt_START        (1)
#define ABB_CH1_RX_STATE_RPT_ch1_rx_clk_rpt_END          (1)
#define ABB_CH1_RX_STATE_RPT_ch1_rx_vld_rpt_START        (2)
#define ABB_CH1_RX_STATE_RPT_ch1_rx_vld_rpt_END          (2)
#define ABB_CH1_RX_STATE_RPT_ch1_rxa_data_rpt_START      (3)
#define ABB_CH1_RX_STATE_RPT_ch1_rxa_data_rpt_END        (3)
#define ABB_CH1_RX_STATE_RPT_ch1_rxa_overflow_rpt_START  (4)
#define ABB_CH1_RX_STATE_RPT_ch1_rxa_overflow_rpt_END    (4)
#define ABB_CH1_RX_STATE_RPT_ch1_rxb_data_rpt_START      (5)
#define ABB_CH1_RX_STATE_RPT_ch1_rxb_data_rpt_END        (5)
#define ABB_CH1_RX_STATE_RPT_ch1_rxb_overflow_rpt_START  (6)
#define ABB_CH1_RX_STATE_RPT_ch1_rxb_overflow_rpt_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_STATE_RPT_UNION
 �ṹ˵��  : ch1_tx_state_rpt �Ĵ����ṹ���塣��ַƫ����:0x1E5����ֵ:0x00�����:8
 �Ĵ���˵��: TX���ֹ���״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_aclk_rpt     : 1;  /* bit[0]: TXͨ��ģ����·ʱ�� */
        unsigned long  ch1_tx_dclk_rpt     : 1;  /* bit[1]: TXͨ������������·ʱ�� */
        unsigned long  ch1_tx_vld_rpt      : 1;  /* bit[2]: TXͨ����������Чָʾ�ź� */
        unsigned long  ch1_tx_clk_rpt      : 1;  /* bit[3]: TXͨ������������ʱ�� */
        unsigned long  ch1_tx_data_rpt     : 1;  /* bit[4]: TXͨ�����ݷ�תָʾ�ź� */
        unsigned long  ch1_tx_overflow_rpt : 1;  /* bit[5]: TXͨ����������ָʾ�ź� */
        unsigned long  ch1_tx_fifo_wfull   : 1;  /* bit[6]: TXͨ��FIFOд��״̬ */
        unsigned long  ch1_tx_fifo_rempty  : 1;  /* bit[7]: TXͨ��FIFO����״̬ */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_STATE_RPT_UNION;
#define ABB_CH1_TX_STATE_RPT_ch1_tx_aclk_rpt_START      (0)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_aclk_rpt_END        (0)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_dclk_rpt_START      (1)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_dclk_rpt_END        (1)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_vld_rpt_START       (2)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_vld_rpt_END         (2)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_clk_rpt_START       (3)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_clk_rpt_END         (3)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_data_rpt_START      (4)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_data_rpt_END        (4)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_overflow_rpt_START  (5)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_overflow_rpt_END    (5)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_fifo_wfull_START    (6)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_fifo_wfull_END      (6)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_fifo_rempty_START   (7)
#define ABB_CH1_TX_STATE_RPT_ch1_tx_fifo_rempty_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_LINE_RPT0_UNION
 �ṹ˵��  : ch0_line_rpt0 �Ĵ����ṹ���塣��ַƫ����:0x1F0����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_en_rpt : 1;  /* bit[0]  : RXA_EN�߿�״̬�ϱ� */
        unsigned long  ch0_rxb_en_rpt : 1;  /* bit[1]  : RXB_EN�߿�״̬�ϱ� */
        unsigned long  ch0_tx_en_rpt  : 1;  /* bit[2]  : TX_EN�߿�״̬�ϱ� */
        unsigned long  reserved       : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_RPT0_UNION;
#define ABB_CH0_LINE_RPT0_ch0_rxa_en_rpt_START  (0)
#define ABB_CH0_LINE_RPT0_ch0_rxa_en_rpt_END    (0)
#define ABB_CH0_LINE_RPT0_ch0_rxb_en_rpt_START  (1)
#define ABB_CH0_LINE_RPT0_ch0_rxb_en_rpt_END    (1)
#define ABB_CH0_LINE_RPT0_ch0_tx_en_rpt_START   (2)
#define ABB_CH0_LINE_RPT0_ch0_tx_en_rpt_END     (2)


/*****************************************************************************
 �ṹ��    : ABB_CH0_LINE_RPT1_UNION
 �ṹ˵��  : ch0_line_rpt1 �Ĵ����ṹ���塣��ַƫ����:0x1F1����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_line_ctrl_mode_rpt : 3;  /* bit[0-2]: �߿��ź�ch0_LINE_CTRL_MODE״̬�ϱ�
                                                                 0��IDLE
                                                                 1��Gģ
                                                                 2��Wģ
                                                                 3��LTEģ
                                                                 4��TDSģ
                                                                 5��ETģʽ
                                                                 6��APTģʽ
                                                                 7��CAģʽ */
        unsigned long  reserved_0             : 1;  /* bit[3]  : ���� */
        unsigned long  ch0_rxa_blk_en_rpt     : 1;  /* bit[4]  : RXA_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch0_rxb_blk_en_rpt     : 1;  /* bit[5]  : RXB_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch0_cfr_en_rpt         : 1;  /* bit[6]  : CFR_EN�߿�״̬�ϱ���V8R1���漰�� */
        unsigned long  reserved_1             : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_RPT1_UNION;
#define ABB_CH0_LINE_RPT1_ch0_line_ctrl_mode_rpt_START  (0)
#define ABB_CH0_LINE_RPT1_ch0_line_ctrl_mode_rpt_END    (2)
#define ABB_CH0_LINE_RPT1_ch0_rxa_blk_en_rpt_START      (4)
#define ABB_CH0_LINE_RPT1_ch0_rxa_blk_en_rpt_END        (4)
#define ABB_CH0_LINE_RPT1_ch0_rxb_blk_en_rpt_START      (5)
#define ABB_CH0_LINE_RPT1_ch0_rxb_blk_en_rpt_END        (5)
#define ABB_CH0_LINE_RPT1_ch0_cfr_en_rpt_START          (6)
#define ABB_CH0_LINE_RPT1_ch0_cfr_en_rpt_END            (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_MODE_RPT_UNION
 �ṹ˵��  : ch0_rx_mode_rpt �Ĵ����ṹ���塣��ַƫ����:0x1F2����ֵ:0x00�����:8
 �Ĵ���˵��: RX���ֹ���ģʽ�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_comp_sel_rpt : 1;  /* bit[0]  : RXͨ�������˲��������̶�ϵ��ѡ���ϱ���
                                                              0���̶�ϵ��1
                                                              1���̶�ϵ��2 */
        unsigned long  ch0_rx_comp_fix_rpt : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶������ϱ���
                                                              0��ϵ�����̶����ɼĴ�������
                                                              1��ϵ���̶� */
        unsigned long  ch0_rx_hb_bp_rpt    : 1;  /* bit[2]  : RXͨ������˲���bypass�����ϱ���
                                                              0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                              1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  ch0_rx_rate_rpt     : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                  2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                        /TDS_B/4G_C,        /4G_B,
                                                              00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
                                                              others��reserved */
        unsigned long  ch0_rx_mode_dig_rpt : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                              000��2G(Ĭ��)
                                                              001��3G_SC/TDS_B/4G_C
                                                              010��4G
                                                              011��3G_DC/4G_B
                                                              100��TDS
                                                              101��CDMA
                                                              Others��Reserved */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_MODE_RPT_UNION;
#define ABB_CH0_RX_MODE_RPT_ch0_rx_comp_sel_rpt_START  (0)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_comp_sel_rpt_END    (0)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_comp_fix_rpt_START  (1)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_comp_fix_rpt_END    (1)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_hb_bp_rpt_START     (2)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_hb_bp_rpt_END       (2)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_rate_rpt_START      (3)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_rate_rpt_END        (4)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_mode_dig_rpt_START  (5)
#define ABB_CH0_RX_MODE_RPT_ch0_rx_mode_dig_rpt_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_MODE_RPT_UNION
 �ṹ˵��  : ch0_tx_mode_rpt �Ĵ����ṹ���塣��ַƫ����:0x1F3����ֵ:0x02�����:8
 �Ĵ���˵��: TX���ֹ���ģʽ�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_bp_rpt  : 1;  /* bit[0]  : TXͨ�������˲���bypass�����ϱ���
                                                              0����bypass(Ĭ��)
                                                              1��bypass */
        unsigned long  ch0_tx_hb_bp_rpt    : 1;  /* bit[1]  : TXͨ������˲���bypass�����ϱ���
                                                              0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
                                                              1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��) */
        unsigned long  ch0_tx_rate_rpt     : 3;  /* bit[2-4]: TXͨ��CIC�˲���������ʿ����ϱ���
                                                                   2G,     3G,     4G,      TDS,      CA
                                                                  (78M) (153.6M) (307.2M) (153.6M) (614.4M)
                                                              0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(Ĭ��)
                                                              1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                              2��-------,--------,15.36MHz,--------,--------
                                                              3��-------,--------, 7.68MHz,--------,--------
                                                              4��-------,--------, 3.84MHz,--------,--------
                                                              Others��Reserved */
        unsigned long  ch0_tx_mode_dig_rpt : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                              000��2G(Ĭ��)
                                                              001��3G
                                                              010��4G
                                                              011��TDS
                                                              100��CDMA
                                                              Others��Reserved */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_MODE_RPT_UNION;
#define ABB_CH0_TX_MODE_RPT_ch0_tx_comp_bp_rpt_START   (0)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_comp_bp_rpt_END     (0)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_hb_bp_rpt_START     (1)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_hb_bp_rpt_END       (1)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_rate_rpt_START      (2)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_rate_rpt_END        (4)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_mode_dig_rpt_START  (5)
#define ABB_CH0_TX_MODE_RPT_ch0_tx_mode_dig_rpt_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_STATE_RPT_UNION
 �ṹ˵��  : ch0_rx_state_rpt �Ĵ����ṹ���塣��ַƫ����:0x1F4����ֵ:0x00�����:8
 �Ĵ���˵��: RX���ֹ���״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_aclk_rpt      : 1;  /* bit[0]: RXͨ��ģ����·ʱ�� */
        unsigned long  ch0_rx_clk_rpt       : 1;  /* bit[1]: RXͨ�����������·ʱ�� */
        unsigned long  ch0_rx_vld_rpt       : 1;  /* bit[2]: RXͨ�����������Чָʾ�ź� */
        unsigned long  ch0_rxa_data_rpt     : 1;  /* bit[3]: RXAͨ��������ݷ�תָʾ�ź� */
        unsigned long  ch0_rxa_overflow_rpt : 1;  /* bit[4]: RXAͨ����������ָʾ�ź� */
        unsigned long  ch0_rxb_data_rpt     : 1;  /* bit[5]: RXBͨ��������ݷ�תָʾ�ź� */
        unsigned long  ch0_rxb_overflow_rpt : 1;  /* bit[6]: RXBͨ����������ָʾ�ź� */
        unsigned long  reserved             : 1;  /* bit[7]: Reserved */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_STATE_RPT_UNION;
#define ABB_CH0_RX_STATE_RPT_ch0_rx_aclk_rpt_START       (0)
#define ABB_CH0_RX_STATE_RPT_ch0_rx_aclk_rpt_END         (0)
#define ABB_CH0_RX_STATE_RPT_ch0_rx_clk_rpt_START        (1)
#define ABB_CH0_RX_STATE_RPT_ch0_rx_clk_rpt_END          (1)
#define ABB_CH0_RX_STATE_RPT_ch0_rx_vld_rpt_START        (2)
#define ABB_CH0_RX_STATE_RPT_ch0_rx_vld_rpt_END          (2)
#define ABB_CH0_RX_STATE_RPT_ch0_rxa_data_rpt_START      (3)
#define ABB_CH0_RX_STATE_RPT_ch0_rxa_data_rpt_END        (3)
#define ABB_CH0_RX_STATE_RPT_ch0_rxa_overflow_rpt_START  (4)
#define ABB_CH0_RX_STATE_RPT_ch0_rxa_overflow_rpt_END    (4)
#define ABB_CH0_RX_STATE_RPT_ch0_rxb_data_rpt_START      (5)
#define ABB_CH0_RX_STATE_RPT_ch0_rxb_data_rpt_END        (5)
#define ABB_CH0_RX_STATE_RPT_ch0_rxb_overflow_rpt_START  (6)
#define ABB_CH0_RX_STATE_RPT_ch0_rxb_overflow_rpt_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_STATE_RPT_UNION
 �ṹ˵��  : ch0_tx_state_rpt �Ĵ����ṹ���塣��ַƫ����:0x1F5����ֵ:0x00�����:8
 �Ĵ���˵��: TX���ֹ���״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_aclk_rpt     : 1;  /* bit[0]: TXͨ��ģ����·ʱ�� */
        unsigned long  ch0_tx_dclk_rpt     : 1;  /* bit[1]: TXͨ������������·ʱ�� */
        unsigned long  ch0_tx_vld_rpt      : 1;  /* bit[2]: TXͨ����������Чָʾ�ź� */
        unsigned long  ch0_tx_clk_rpt      : 1;  /* bit[3]: TXͨ������������ʱ�� */
        unsigned long  ch0_tx_data_rpt     : 1;  /* bit[4]: TXͨ�����ݷ�תָʾ�ź� */
        unsigned long  ch0_tx_overflow_rpt : 1;  /* bit[5]: TXͨ����������ָʾ�ź� */
        unsigned long  ch0_tx_fifo_wfull   : 1;  /* bit[6]: TXͨ��FIFOд��״̬ */
        unsigned long  ch0_tx_fifo_rempty  : 1;  /* bit[7]: TXͨ��FIFO����״̬ */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_STATE_RPT_UNION;
#define ABB_CH0_TX_STATE_RPT_ch0_tx_aclk_rpt_START      (0)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_aclk_rpt_END        (0)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_dclk_rpt_START      (1)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_dclk_rpt_END        (1)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_vld_rpt_START       (2)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_vld_rpt_END         (2)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_clk_rpt_START       (3)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_clk_rpt_END         (3)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_data_rpt_START      (4)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_data_rpt_END        (4)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_overflow_rpt_START  (5)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_overflow_rpt_END    (5)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_fifo_wfull_START    (6)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_fifo_wfull_END      (6)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_fifo_rempty_START   (7)
#define ABB_CH0_TX_STATE_RPT_ch0_tx_fifo_rempty_END     (7)


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
        unsigned long  tx_cfr_bp_c   : 1;  /* bit[0]  : TXͨ��CFR bypass���ƣ�
                                                        0����bypass
                                                        1��bypass(Ĭ��)
                                                        ��V8R1���漰�� */
        unsigned long  tx_flush_en_c : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                        0����ʹ��
                                                        1��ʹ�� */
        unsigned long  tx_comp_sel_c : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                        00���̶�ϵ��1��
                                                        01���̶�ϵ��2��
                                                        10���̶�ϵ��3��
                                                        11������ϵ���� */
        unsigned long  reserved      : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_DIG_3_UNION;
#define ABB_TX_C_DIG_3_tx_cfr_bp_c_START    (0)
#define ABB_TX_C_DIG_3_tx_cfr_bp_c_END      (0)
#define ABB_TX_C_DIG_3_tx_flush_en_c_START  (1)
#define ABB_TX_C_DIG_3_tx_flush_en_c_END    (1)
#define ABB_TX_C_DIG_3_tx_comp_sel_c_START  (2)
#define ABB_TX_C_DIG_3_tx_comp_sel_c_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_ANA_1_UNION
 �ṹ˵��  : rx_c_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x405����ֵ:0xF2�����:8
 �Ĵ���˵��: RX C���üĴ����������߿��߼�������reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  DEM_MOD_B0_C  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                        000��DWA
                                                        001��CLA1
                                                        010��CLA2
                                                        011��CLA3
                                                        100��CLA4
                                                        101��CLA5
                                                        110��CLA6
                                                        111��CLA7 */
        unsigned long  RX_MODE_CLK_C : 2;  /* bit[1-2]: {rx_XX_ana_2[0],rx_XX_ana1[2:1]}������ϵ�ģʽ���ƣ�
                                                        000��4G
                                                        001��3G
                                                        010��3G_DC &amp; TDS
                                                        011��2G(Ĭ��)
                                                        100��reserved
                                                        101��CDMA */
        unsigned long  DEM_MOD_B1_C  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                        000��DWA
                                                        001��CLA1
                                                        010��CLA2
                                                        011��CLA3
                                                        100��CLA4
                                                        101��CLA5
                                                        110��CLA6
                                                        111��CLA7 */
        unsigned long  RXB_Q_PD_C    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                        0��Power On
                                                        1��Power Down(Ĭ��)
                                                        (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_C    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                        0��Power On
                                                        1��Power Down(Ĭ��)
                                                        (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_C    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                        0��Power On
                                                        1��Power Down(Ĭ��)
                                                        (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_C    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                        0��Power On
                                                        1��Power Down(Ĭ��)
                                                        (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_1_UNION;
#define ABB_RX_C_ANA_1_DEM_MOD_B0_C_START   (0)
#define ABB_RX_C_ANA_1_DEM_MOD_B0_C_END     (0)
#define ABB_RX_C_ANA_1_RX_MODE_CLK_C_START  (1)
#define ABB_RX_C_ANA_1_RX_MODE_CLK_C_END    (2)
#define ABB_RX_C_ANA_1_DEM_MOD_B1_C_START   (3)
#define ABB_RX_C_ANA_1_DEM_MOD_B1_C_END     (3)
#define ABB_RX_C_ANA_1_RXB_Q_PD_C_START     (4)
#define ABB_RX_C_ANA_1_RXB_Q_PD_C_END       (4)
#define ABB_RX_C_ANA_1_RXB_I_PD_C_START     (5)
#define ABB_RX_C_ANA_1_RXB_I_PD_C_END       (5)
#define ABB_RX_C_ANA_1_RXA_Q_PD_C_START     (6)
#define ABB_RX_C_ANA_1_RXA_Q_PD_C_END       (6)
#define ABB_RX_C_ANA_1_RXA_I_PD_C_START     (7)
#define ABB_RX_C_ANA_1_RXA_I_PD_C_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_ANA_2_UNION
 �ṹ˵��  : rx_c_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x406����ֵ:0x55�����:8
 �Ĵ���˵��: RX C���üĴ����������߿��߼�������reg_analog_wr01��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  RX_MODE_C : 1;  /* bit[0]  : Mode setting for ADC
                                                    1�� CA mode
                                                    0�� others */
        unsigned long  reserved  : 1;  /* bit[1]  : ���� */
        unsigned long  IBCT_QT   : 2;  /* bit[2-3]: Current Seting For Mode
                                                    1x��LTE mode Current
                                                    01��3G_DC &amp; X mode Current
                                                    00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP3  : 2;  /* bit[4-5]: Current Seting For Mode
                                                    1x��LTE mode Current
                                                    01��3G_DC &amp; X mode Current
                                                    00��3G &amp; 2G mode Current */
        unsigned long  IBCT_OP1  : 2;  /* bit[6-7]: Current Seting For Mode
                                                    1x��LTE mode Current
                                                    01��3G_DC &amp; X mode Current
                                                    00��3G &amp; 2G mode Current */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_2_UNION;
#define ABB_RX_C_ANA_2_RX_MODE_C_START  (0)
#define ABB_RX_C_ANA_2_RX_MODE_C_END    (0)
#define ABB_RX_C_ANA_2_IBCT_QT_START    (2)
#define ABB_RX_C_ANA_2_IBCT_QT_END      (3)
#define ABB_RX_C_ANA_2_IBCT_OP3_START   (4)
#define ABB_RX_C_ANA_2_IBCT_OP3_END     (5)
#define ABB_RX_C_ANA_2_IBCT_OP1_START   (6)
#define ABB_RX_C_ANA_2_IBCT_OP1_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_ANA_3_UNION
 �ṹ˵��  : rx_c_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x407����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2G���üĴ����������߿��߼�������reg_analog_wr53��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP1  : 3;  /* bit[0-2]: RX ADC OP1��������
                                                   000�� 1.0x
                                                   001�� 0.8x
                                                   010�� 0.6x
                                                   011�� 0.4x
                                                   100�� 1.8x
                                                   101�� 1.6x
                                                   110�� 1.4x
                                                   111�� 1.2x */
        unsigned long  ITR_OP3  : 3;  /* bit[3-5]: RX ADC OP3��������
                                                   000�� 1.0x
                                                   001�� 0.8x
                                                   010�� 0.6x
                                                   011�� 0.4x
                                                   100�� 1.8x
                                                   101�� 1.6x
                                                   110�� 1.4x
                                                   111�� 1.2x */
        unsigned long  reserved : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_3_UNION;
#define ABB_RX_C_ANA_3_ITR_OP1_START   (0)
#define ABB_RX_C_ANA_3_ITR_OP1_END     (2)
#define ABB_RX_C_ANA_3_ITR_OP3_START   (3)
#define ABB_RX_C_ANA_3_ITR_OP3_END     (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_ANA_4_UNION
 �ṹ˵��  : rx_c_ana_4 �Ĵ����ṹ���塣��ַƫ����:0x408����ֵ:0x00�����:8
 �Ĵ���˵��: RX C���üĴ����������߿��߼�������reg_analog_wr54��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_QT   : 3;  /* bit[0-2]: RX ADC QT��������
                                                   000�� 1.0x
                                                   001�� 0.8x
                                                   010�� 0.6x
                                                   011�� 0.4x
                                                   100�� 1.8x
                                                   101�� 1.6x
                                                   110�� 1.4x
                                                   111�� 1.2x */
        unsigned long  ITR_DAC  : 3;  /* bit[3-5]: RX ADC ����DAC�˷ŵ�������
                                                   000�� 1.0x
                                                   001�� 0.8x
                                                   010�� 0.6x
                                                   011�� 0.4x
                                                   100�� 1.8x
                                                   101�� 1.6x
                                                   110�� 1.4x
                                                   111�� 1.2x */
        unsigned long  reserved : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_4_UNION;
#define ABB_RX_C_ANA_4_ITR_QT_START    (0)
#define ABB_RX_C_ANA_4_ITR_QT_END      (2)
#define ABB_RX_C_ANA_4_ITR_DAC_START   (3)
#define ABB_RX_C_ANA_4_ITR_DAC_END     (5)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_ANA_5_UNION
 �ṹ˵��  : rx_c_ana_5 �Ĵ����ṹ���塣��ַƫ����:0x409����ֵ:0x00�����:8
 �Ĵ���˵��: RX C���üĴ����������߿��߼�������reg_analog_wr55��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ITR_OP2  : 3;  /* bit[0-2]: RX ADC OP2��������
                                                   000�� 1.0x
                                                   001�� 0.8x
                                                   010�� 0.6x
                                                   011�� 0.4x
                                                   100�� 1.8x
                                                   101�� 1.6x
                                                   110�� 1.4x
                                                   111�� 1.2x */
        unsigned long  IBCT_OP2 : 2;  /* bit[3-4]: Current Seting For Mode
                                                   1x��LTE mode Current
                                                   01��3G_DC &amp; X mode Current
                                                   00��3G &amp; 2G mode Current */
        unsigned long  reserved : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_5_UNION;
#define ABB_RX_C_ANA_5_ITR_OP2_START   (0)
#define ABB_RX_C_ANA_5_ITR_OP2_END     (2)
#define ABB_RX_C_ANA_5_IBCT_OP2_START  (3)
#define ABB_RX_C_ANA_5_IBCT_OP2_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_ANA_6_UNION
 �ṹ˵��  : rx_c_ana_6 �Ĵ����ṹ���塣��ַƫ����:0x40A����ֵ:0x44�����:8
 �Ĵ���˵��: RX C���üĴ����������߿��߼�������reg_analog_wr56��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved : 2;  /* bit[0-1]: ���� */
        unsigned long  BWCT_OP3 : 2;  /* bit[2-3]: BWCT_OP3 OP3�������
                                                   1x�� LTEģʽ
                                                   01�� WDC &amp; X ģʽ
                                                   00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP2 : 2;  /* bit[4-5]: BWCT_OP2 OP2�������
                                                   1x�� LTEģʽ
                                                   01�� WDC &amp; X ģʽ
                                                   00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP1 : 2;  /* bit[6-7]: BWCT_OP1 OP1�������
                                                   1x�� LTEģʽ
                                                   01�� WDC &amp; X ģʽ
                                                   00�� W &amp; Gģʽ */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_6_UNION;
#define ABB_RX_C_ANA_6_BWCT_OP3_START  (2)
#define ABB_RX_C_ANA_6_BWCT_OP3_END    (3)
#define ABB_RX_C_ANA_6_BWCT_OP2_START  (4)
#define ABB_RX_C_ANA_6_BWCT_OP2_END    (5)
#define ABB_RX_C_ANA_6_BWCT_OP1_START  (6)
#define ABB_RX_C_ANA_6_BWCT_OP1_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_ANA_7_UNION
 �ṹ˵��  : rx_c_ana_7 �Ĵ����ṹ���塣��ַƫ����:0x40B����ֵ:0x00�����:8
 �Ĵ���˵��: RX C���üĴ����������߿��߼�������reg_analog_wr57��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved        : 4;  /* bit[0-3]: ���� */
        unsigned long  QT_REF_SEL      : 1;  /* bit[4]  : �������ο���ѹѡ��
                                                          0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
                                                          1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ */
        unsigned long  GMBIAS_EN       : 1;  /* bit[5]  : OP3�Ƿ�ʹ��Gm_biasƫ��
                                                          0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
                                                          1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ�� */
        unsigned long  MODU_DEPTH_CTRL : 1;  /* bit[6]  : ������DAC������ȿ���
                                                          0 �������0.5
                                                          1 �������0.75 */
        unsigned long  RX_DAC_LP_CTRL  : 1;  /* bit[7]  : ������DACƫ�õ�������
                                                          0 ��������������ܺ�
                                                          1 С�������������ܲ� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_7_UNION;
#define ABB_RX_C_ANA_7_QT_REF_SEL_START       (4)
#define ABB_RX_C_ANA_7_QT_REF_SEL_END         (4)
#define ABB_RX_C_ANA_7_GMBIAS_EN_START        (5)
#define ABB_RX_C_ANA_7_GMBIAS_EN_END          (5)
#define ABB_RX_C_ANA_7_MODU_DEPTH_CTRL_START  (6)
#define ABB_RX_C_ANA_7_MODU_DEPTH_CTRL_END    (6)
#define ABB_RX_C_ANA_7_RX_DAC_LP_CTRL_START   (7)
#define ABB_RX_C_ANA_7_RX_DAC_LP_CTRL_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_ANA_8_UNION
 �ṹ˵��  : rx_c_ana_8 �Ĵ����ṹ���塣��ַƫ����:0x40C����ֵ:0x30�����:8
 �Ĵ���˵��: RX C���üĴ����������߿��߼�������reg_analog_wr58��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CK_CTRL_DATA : 5;  /* bit[0-4]: CK_CTRL_DATA
                                                       00000 ����DACʱ����ǰ������
                                                       11111 ����DACʱ����ǰ����� */
        unsigned long  CK_CTRL_MODE : 2;  /* bit[5-6]: CK_CTRL_MODE
                                                       00�� LTEģʽ
                                                       01�� WDC &amp; X &amp; TDS_Aģʽ
                                                       1x�� W &amp; G &amp; TDS_Bģʽ */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_8_UNION;
#define ABB_RX_C_ANA_8_CK_CTRL_DATA_START  (0)
#define ABB_RX_C_ANA_8_CK_CTRL_DATA_END    (4)
#define ABB_RX_C_ANA_8_CK_CTRL_MODE_START  (5)
#define ABB_RX_C_ANA_8_CK_CTRL_MODE_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_ANA_9_UNION
 �ṹ˵��  : rx_c_ana_9 �Ĵ����ṹ���塣��ַƫ����:0x40D����ֵ:0x81�����:8
 �Ĵ���˵��: RX C���üĴ����������߿��߼�������reg_analog_wr59��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_sel_c    : 1;  /* bit[0]  : AD&amp;DA��WPLL��SCPLLѡ���źš�
                                                        0��ѡ��SCPLL����4g��tdsĬ��ѡ��SCPLL��
                                                        1��ѡ��WPLL����3g��xĬ��ѡ��WPLL�� */
        unsigned long  reserved      : 5;  /* bit[1-5]: ���� */
        unsigned long  blk_len_sel_c : 2;  /* bit[6-7]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                        2'b00��2560chip��(WģĬ��)
                                                        2'b01��512chip��
                                                        2'b10��1024chip��(XģĬ��)
                                                        2'b11��2048chip�� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_9_UNION;
#define ABB_RX_C_ANA_9_wpll_sel_c_START     (0)
#define ABB_RX_C_ANA_9_wpll_sel_c_END       (0)
#define ABB_RX_C_ANA_9_blk_len_sel_c_START  (6)
#define ABB_RX_C_ANA_9_blk_len_sel_c_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_C_ANA_1_UNION
 �ṹ˵��  : tx_c_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x410����ֵ:0x1C�����:8
 �Ĵ���˵��: TX C���üĴ����������߿��߼�������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ���ƣ�
                                                      000��4G
                                                      001��3G &amp; TDS
                                                      010��reserved
                                                      011��2G(Ĭ��)
                                                      1xx��CDMA */
        unsigned long  TX_Q_PD_A   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                      0��Power On
                                                      1��Power Down(Ĭ��)
                                                      (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                      0��Power On
                                                      1��Power Down(Ĭ��)
                                                      (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                      00��1��Ƶ
                                                      01��2��Ƶ(Ĭ��)
                                                      10��8��Ƶ
                                                      11��4��Ƶ */
        unsigned long  FC_B1_B0_C  : 2;  /* bit[6-7]: TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���)��
                                                      000��14MHz(Ĭ��)
                                                      001��28MHz
                                                      010��9.3MHz
                                                      011��18.7MHz
                                                      100��7MHz
                                                      101��14MHz
                                                      110��28MHz
                                                      111��56MHz
                                                      Ĭ�����÷�����
                                                      4G:001   2G:100   Others:000 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_ANA_1_UNION;
#define ABB_TX_C_ANA_1_TX_MODE_CLK_START  (0)
#define ABB_TX_C_ANA_1_TX_MODE_CLK_END    (1)
#define ABB_TX_C_ANA_1_TX_Q_PD_A_START    (2)
#define ABB_TX_C_ANA_1_TX_Q_PD_A_END      (2)
#define ABB_TX_C_ANA_1_TX_I_PD_A_START    (3)
#define ABB_TX_C_ANA_1_TX_I_PD_A_END      (3)
#define ABB_TX_C_ANA_1_TX_DIV_MODE_START  (4)
#define ABB_TX_C_ANA_1_TX_DIV_MODE_END    (5)
#define ABB_TX_C_ANA_1_FC_B1_B0_C_START   (6)
#define ABB_TX_C_ANA_1_FC_B1_B0_C_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_C_ANA_2_UNION
 �ṹ˵��  : tx_c_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x411����ֵ:0x92�����:8
 �Ĵ���˵��: TX C���üĴ����������߿��߼�������reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP_C  : 2;  /* bit[0-1]: LPF OP����ģʽ����
                                                             00�����������Ϊ����ֵ��miller����Ϊ����ֵ���������˷�ƫ�õ���Ϊ10uA�������
                                                             01��������������ӵ�����ֵ��1.3����miller�������ӵ�����ֵ��7/6���������˷�ƫ�õ���Ϊ5uA�������
                                                             10��������������ӵ�����ֵ��1.2����miller�������ӵ�����ֵ��8/6���������˷�ƫ�õ���Ϊ5uA�������
                                                             11��������������ӵ�����ֵ��1.5����miller�������ӵ�����ֵ��9/6���������˷�ƫ�õ���Ϊ3uA�������

                                                             Ĭ�����÷�����
                                                             LTE:00   WDC/TDS:01   WSC/CDMA:10   GSM:11 */
        unsigned long  reserved           : 2;  /* bit[2-3]: ���� */
        unsigned long  LPF_MODE_CURRENT_C : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                             00��   10u
                                                             01��    5u
                                                             10��    5u
                                                             11��    3u
                                                             Ĭ�����÷�����
                                                             LTE:00   GSM:11   Others:01 */
        unsigned long  FC_B2_C            : 1;  /* bit[6]  : TX LPF��ֹƵ��ѡ��(��tx_XX_ana_2<6>,tx_XX_ana_1<7:6>���),����μ�FC_B1_B0_C��˵���� */
        unsigned long  TX_MODE_CLK_B3     : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana_1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_ANA_2_UNION;
#define ABB_TX_C_ANA_2_CURRENT_MODE_OP_C_START   (0)
#define ABB_TX_C_ANA_2_CURRENT_MODE_OP_C_END     (1)
#define ABB_TX_C_ANA_2_LPF_MODE_CURRENT_C_START  (4)
#define ABB_TX_C_ANA_2_LPF_MODE_CURRENT_C_END    (5)
#define ABB_TX_C_ANA_2_FC_B2_C_START             (6)
#define ABB_TX_C_ANA_2_FC_B2_C_END               (6)
#define ABB_TX_C_ANA_2_TX_MODE_CLK_B3_START      (7)
#define ABB_TX_C_ANA_2_TX_MODE_CLK_B3_END        (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_C_ANA_3_UNION
 �ṹ˵��  : tx_c_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x412����ֵ:0x18�����:8
 �Ĵ���˵��: TX C���üĴ����������߿��߼�������reg_analog_wr50��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TXLPF_CT     : 3;  /* bit[0-2]: LPF OP1 ����ģʽ����
                                                       000��5u
                                                       001��4u
                                                       010��3u
                                                       011��2u
                                                       100��9u
                                                       101��8u
                                                       110��7u
                                                       111��6u */
        unsigned long  DUM_EN_Q     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                       1��enable(Ĭ��)
                                                       0��disable */
        unsigned long  DUM_EN_I     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                       1��enable(Ĭ��)
                                                       0��disable */
        unsigned long  reserved     : 2;  /* bit[5-6]: ���� */
        unsigned long  TX_CLKD_CTRL : 1;  /* bit[7]  : TX ����ʱ����ѡ��
                                                       0������(Ĭ��)
                                                       1������ */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_ANA_3_UNION;
#define ABB_TX_C_ANA_3_TXLPF_CT_START      (0)
#define ABB_TX_C_ANA_3_TXLPF_CT_END        (2)
#define ABB_TX_C_ANA_3_DUM_EN_Q_START      (3)
#define ABB_TX_C_ANA_3_DUM_EN_Q_END        (3)
#define ABB_TX_C_ANA_3_DUM_EN_I_START      (4)
#define ABB_TX_C_ANA_3_DUM_EN_I_END        (4)
#define ABB_TX_C_ANA_3_TX_CLKD_CTRL_START  (7)
#define ABB_TX_C_ANA_3_TX_CLKD_CTRL_END    (7)


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
 �ṹ��    : ABB_RXB_SEP_EN_UNION
 �ṹ˵��  : RXB_SEP_EN �Ĵ����ṹ���塣��ַƫ����:0x600����ֵ:0x01�����:8
 �Ĵ���˵��: rxbͨ�����⹦��ʹ��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxb_sep_en : 1;  /* bit[0]  : ch0��ch1 rxbͨ��ʹ�ܻ��⹦��ʹ�ܣ�
                                                     0��rxb���⹦�ܹرգ�
                                                     1��rxb���⹦�ܴ򿪡� */
        unsigned long  reserved   : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RXB_SEP_EN_UNION;
#define ABB_RXB_SEP_EN_rxb_sep_en_START  (0)
#define ABB_RXB_SEP_EN_rxb_sep_en_END    (0)


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

#endif /* end of abb_interface_tv101.h */
