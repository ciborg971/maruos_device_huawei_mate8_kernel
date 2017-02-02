

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __PHY_ABB_INTERFACE_H__
#define __PHY_ABB_INTERFACE_H__

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
             001��3G_SCReserved
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
             Reserved
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
 bit[7:2]    Reserved
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
   UNION�ṹ:  ABB_TX_2G_DIG_3_UNION */
#define ABB_TX_2G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x4)

/* �Ĵ���˵����CH0 RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SCReserved
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
             Reserved
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
 bit[7:2]    Reserved
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
   UNION�ṹ:  ABB_TX_CH0_3G_DIG_3_UNION */
#define ABB_TX_CH0_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x9)

/* �Ĵ���˵����CH0 RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SCReserved
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
             Reserved
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
 bit[7:2]    Reserved
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_CH0_4G_DIG_3_UNION */
#define ABB_TX_CH0_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0xE)

/* �Ĵ���˵����RX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SCReserved
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
 bit[7:2]    Reserved
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
   UNION�ṹ:  ABB_TX_TDS_DIG_3_UNION */
#define ABB_TX_TDS_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x13)

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
             Reserved
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
 bit[7:2]    Reserved
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
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
 bit[1]      Reserved
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_2G_ANA_2_UNION */
#define ABB_RX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x25)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������reg_analog_wr48��
 bit[7:6]    TX filter��ֹƵ��ѡ��
             00��5MHz(Ĭ��)WSC&amp;GSM&amp;CDMA
             01��10MHz WDC
             10��Reserved
             11��20MHz LTE
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��3��Ƶ
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
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TBD
 bit[5:4]    LPF �˷�ƫ�õ�������
             �˷ŵ�����   op1   op2
             00��         10u   10u
             01��         5u    5u
             10��         2.5u  5u
             11��         2.5u  2.5u
             LTE:00
             Others:01
 bit[3:2]    LPF OP2 ����ģʽ����
             00 �������������
             01 ����������Ӵ�������5uAƫ�ã�
             10 ������ʹ��
             11 ����������ټӴ�������2.5uAƫ�ã�
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
 bit[1:0]    LPF OP1 ����ģʽ����
             bit0��
             0�� �������������
             1�� ����������Ӵ�������5uAƫ�ã�
             bit1��
             0�� miller������������
             1�� miller�������ݱ��������2.5uAƫ�ã�
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
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
 bit[1]      Reserved
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_CH0_3G_ANA_2_UNION */
#define ABB_RX_CH0_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x29)

/* �Ĵ���˵����CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr48��
 bit[7:6]    TX filter��ֹƵ��ѡ��
             00��5MHz(Ĭ��)WSC&amp;GSM&amp;CDMA
             01��10MHz WDC
             10��Reserved
             11��20MHz LTE
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��3��Ƶ
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
             000��4G &amp; ET &amp; APT
             001��3G &amp; TDS
   UNION�ṹ:  ABB_TX_CH0_3G_ANA_1_UNION */
#define ABB_TX_CH0_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2A)

/* �Ĵ���˵����CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TBD
 bit[5:4]    LPF �˷�ƫ�õ�������
             �˷ŵ�����   op1   op2
             00��         10u   10u
             01��         5u    5u
             10��         2.5u  5u
             11��         2.5u  2.5u
             LTE:00
             Others:01
 bit[3:2]    LPF OP2 ����ģʽ����
             00 �������������
             01 ����������Ӵ�������5uAƫ�ã�
             10 ������ʹ��
             11 ����������ټӴ�������2.5uAƫ�ã�
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
 bit[1:0]    LPF OP1 ����ģʽ����
             bit0��
             0�� �������������
             1�� ����������Ӵ�������5uAƫ�ã�
             bit1��
             0�� miller������������
             1�� miller�������ݱ��������2.5uAƫ�ã�
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
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
 bit[1]      Reserved
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_CH0_4G_ANA_2_UNION */
#define ABB_RX_CH0_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0x2D)

/* �Ĵ���˵����CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr48��
 bit[7:6]    TX filter��ֹƵ��ѡ��
             00��5MHz(Ĭ��)WSC&amp;GSM&amp;CDMA
             01��10MHz WDC
             10��Reserved
             11��20MHz LTE
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��3��Ƶ
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
             000��4G &amp; ET &amp; APT
             001��3G &amp; TDS
             010��CA
             011��2G(Ĭ��)
             1xx��CDMA
   UNION�ṹ:  ABB_TX_CH0_4G_ANA_1_UNION */
#define ABB_TX_CH0_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0x2E)

/* �Ĵ���˵����CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TBD
 bit[5:4]    LPF �˷�ƫ�õ�������
             �˷ŵ�����   op1   op2
             00��         10u   10u
             01��         5u    5u
             10��         2.5u  5u
             11��         2.5u  2.5u
             LTE:00
             Others:01
 bit[3:2]    LPF OP2 ����ģʽ����
             00 �������������
             01 ����������Ӵ�������5uAƫ�ã�
             10 ������ʹ��
             11 ����������ټӴ�������2.5uAƫ�ã�
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
 bit[1:0]    LPF OP1 ����ģʽ����
             bit0��
             0�� �������������
             1�� ����������Ӵ�������5uAƫ�ã�
             bit1��
             0�� miller������������
             1�� miller�������ݱ��������2.5uAƫ�ã�
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
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
 bit[1]      Reserved
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_TDS_ANA_2_UNION */
#define ABB_RX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x31)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������reg_analog_wr48��
 bit[7:6]    TX filter��ֹƵ��ѡ��
             00��5MHz(Ĭ��)WSC&amp;GSM&amp;CDMA
             01��10MHz WDC
             10��Reserved
             11��20MHz LTE
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��3��Ƶ
             11��4��Ƶ

 bit[3]      TX_I DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_I_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ���ƣ�
             000��4G
             001��3G &amp; TDS
             010��CA
             011��2G(Ĭ��)
             1xx��CDMA
   UNION�ṹ:  ABB_TX_TDS_ANA_1_UNION */
#define ABB_TX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x32)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TBD
 bit[5:4]    LPF �˷�ƫ�õ�������
             �˷ŵ�����   op1   op2
             00��         10u   10u
             01��         5u    5u
             10��         2.5u  5u
             11��         2.5u  2.5u
             LTE:00
             Others:01
 bit[3:2]    LPF OP2 ����ģʽ����
             00 �������������
             01 ����������Ӵ�������5uAƫ�ã�
             10 ������ʹ��
             11 ����������ټӴ�������2.5uAƫ�ã�
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
 bit[1:0]    LPF OP1 ����ģʽ����
             bit0��
             0�� �������������
             1�� ����������Ӵ�������5uAƫ�ã�
             bit1��
             0�� miller������������
             1�� miller�������ݱ��������2.5uAƫ�ã�
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
   UNION�ṹ:  ABB_TX_TDS_ANA_2_UNION */
#define ABB_TX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x33)

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
 bit[1]      Reserved
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_IDLE_ANA_2_UNION */
#define ABB_RX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3D)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr48��
 bit[7:6]    TX filter��ֹƵ��ѡ��
             00��5MHz(Ĭ��)WSC&amp;GSM&amp;CDMA
             01��10MHz WDC
             10��Reserved
             11��20MHz LTE
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��3��Ƶ
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
             000��4G &amp; ET &amp; APT
             001��3G &amp; TDS
             010��CA
             011��2G(Ĭ��)
             1xx��CDMA
   UNION�ṹ:  ABB_TX_IDLE_ANA_1_UNION */
#define ABB_TX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3E)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TBD
 bit[5:4]    LPF �˷�ƫ�õ�������
             �˷ŵ�����   op1   op2
             00��         10u   10u
             01��         5u    5u
             10��         2.5u  5u
             11��         2.5u  2.5u
             LTE:00
             Others:01
 bit[3:2]    LPF OP2 ����ģʽ����
             00 �������������
             01 ����������Ӵ�������5uAƫ�ã�
             10 ������ʹ��
             11 ����������ټӴ�������2.5uAƫ�ã�
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
 bit[1:0]    LPF OP1 ����ģʽ����
             bit0��
             0�� �������������
             1�� ����������Ӵ�������5uAƫ�ã�
             bit1��
             0�� miller������������
             1�� miller�������ݱ��������2.5uAƫ�ã�
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
   UNION�ṹ:  ABB_TX_IDLE_ANA_2_UNION */
#define ABB_TX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3F)

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
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_CTRL_ADDR                             (ABB_BASE_ADDR + 0xA2)

/* �Ĵ���˵����CFR��ֵ��ⴰ���Ĵ�����
 bit[7:4]    CFR��������
 bit[3]      Reserved
 bit[2]      CFR�˲���ѡ��
             0��bypass�˲���
             1����bypass�˲���
 bit[1:0]    CFR��ֵ��ⷽʽ��
             00���������
             01���������
             10���������
             11��ȫ����ֵ
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
 bit[7]      Reserved
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
 bit[7]      Reserved
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
 bit[7]      Reserved
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
 bit[7]      Reserved
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
 bit[7:2]    Reserved
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
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_RXA_DC_I_2_UNION */
#define ABB_CH0_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0xC4)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0xC5)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_RXA_DC_Q_2_UNION */
#define ABB_CH0_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0xC6)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0xC7)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_RXB_DC_I_2_UNION */
#define ABB_CH0_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0xC8)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0xC9)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_RXB_DC_Q_2_UNION */
#define ABB_CH0_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0xCA)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      Reserved
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
 bit[1]      RXC_I ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXA_I_PD)|(CH0_RXA_EN &amp; ch0_test_mode[5]) =1ʱ����������ر�
             ComstarV511_Reserved
 bit[0]      RXC_Q ADC Power Down����
             0��Power On
             1��Power Down(Ĭ��)
             (!RXA_Q_PD)|(CH0_RXA_EN &amp; ch0_test_mode[5]) =1ʱ����������ر�
             ComstarV511_Reserved
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR02_UNION */
#define ABB_CH0_REG_ANALOG_WR02_ADDR                  (ABB_BASE_ADDR + 0xD0)

/* �Ĵ���˵������ģ�ӿ�ʱ�ӿ��ƼĴ�����
 bit[7]      Reserved
 bit[6]      CLK_245M Power Down����
             0��Power On
             1��Power Down(Ĭ��)
 bit[5]      CLK_52M Power Down����
             0��Power On(Ĭ��)
             1��Power Down
 bit[4]      CLK_61D44M Power Down����
             0��Power On(Ĭ��)
             1��Power Down
 bit[3]      TX ����ʱ����ѡ��
             0������(Ĭ��)
             1������
 bit[2]      52M��104M���ѡ��
             0��104M
             1��52M
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
 bit[0]      Calibration enable(Ĭ��Ϊ0)
             ����������Calibration����
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR04_UNION */
#define ABB_CH0_REG_ANALOG_WR04_ADDR                  (ABB_BASE_ADDR + 0xD2)

/* �Ĵ���˵����ADC��һ������������tuning�Ĵ�����
 bit[7]      Reserved
 bit[6:0]    ADC��һ������������tuning
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR05_UNION */
#define ABB_CH0_REG_ANALOG_WR05_ADDR                  (ABB_BASE_ADDR + 0xD3)

/* �Ĵ���˵����ADC�ڶ�������������tuning�Ĵ�����
 bit[7]      Reserved
 bit[6:0]    ADC�ڶ�������������tuning
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR06_UNION */
#define ABB_CH0_REG_ANALOG_WR06_ADDR                  (ABB_BASE_ADDR + 0xD4)

/* �Ĵ���˵����ADC����������������tuning�Ĵ�����
 bit[7]      Reserved
 bit[6:0]    ADC����������������tuning
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR07_UNION */
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
 bit[7]      RX_ADC LDOʹ�ܿ���
             0��Power Down(Ĭ��)
             1��Power On
 bit[6]      ADC SYNC�źŲ����ؿ��ƣ�
             0������(Ĭ��)
             1������
 bit[5]      ADC�����ؿ��ƣ�
             0������(Ĭ��)
             1������
 bit[4:2]    Rx CK LDO��Դ��ѹ
             000��0.9V(Ĭ��)
 bit[1]      Rx CK LDO��Դ���ص���
             0��������(Ĭ��)
             1������
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
 bit[1]      TX I channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable
 bit[0]      TX Q channel  dummy logic control signal
             1��enable(Ĭ��)
             0��disable
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
 bit[5:4]    PLL��Ƶ����������
             x0����Ƶ������һֱ���Up�ź�
             01����Ƶ������һֱ���Down�ź�
             11����Ƶ��������������
 bit[3:1]    ����ʱ��ѡ��
             001��ѡ��������PLL��ʱ����Ϊ����ʱ��
             010��ѡ��������CLKIN_SYSTEM�����ʱ����Ϊ����ʱ��
             100��ѡ��������TCXO_IN��ʱ����Ϊ����ʱ��
 bit[0]      PLL�Ĳο�ʱ��ѡ��
             1��CLKIN_SYSTEM��ΪPLL�Ĳο�ʱ��
             0��TCXO Buffer�����ΪPLL�ο�ʱ��
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA0_UNION */
#define ABB_CH0_REG_DEBUG_ANA0_ADDR                   (ABB_BASE_ADDR + 0xE0)

/* �Ĵ���˵����PLL LOCK���ƼĴ�����
 bit[7:6]    WPLL VCO Current����
             00��X1.2
             01��X1.1(Ĭ��)
             10��X1.1
             11��X1.0
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
 bit[1:0]    PLL CP PowerDown���ƣ�������
             00����������
             01��PowerDown WPLL CP
             10��PowerDown GPLL CP
             11��PowerDown WPLL CP��GPLL CP
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA2_UNION */
#define ABB_CH0_REG_DEBUG_ANA2_ADDR                   (ABB_BASE_ADDR + 0xE2)

/* �Ĵ���˵����PLL���ƼĴ�����
 bit[7:4]    GPLL��ɱõ�������(����Ч)
             Basic��0.2*Icp
             Bit0�� 0.1*Icp
             Bit1�� 0.2*Icp
             Bit2�� 0.4*Icp
             Bit3�� 0.8*Icp
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA3_UNION */
#define ABB_CH0_REG_DEBUG_ANA3_ADDR                   (ABB_BASE_ADDR + 0xE3)

/* �Ĵ���˵����PLL���ƼĴ�����
 bit[7:4]    WPLL��ɱõ�������(����Ч)
             Basic��0.2*Icp
             Bit0�� 0.1*Icp
             Bit1�� 0.2*Icp
             Bit2�� 0.4*Icp
             Bit3�� 0.8*Icp
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
 bit[6]      TEST CLK INPUT�µ����
             0������
             1���ر�
 bit[5:4]    TCXO BUFFER��������
             00��1x
             01��2x
             10��3x(Ĭ��)
             11��4x
 bit[3:2]    WPLL����ʱ��Ƶ��ѡ��
             00��76.8M
             01��38.4M
             10��38.4M
             11��19.2M(Ĭ��)
 bit[1:0]    GPLL����ʱ��Ƶ��ѡ��
             00��26M
             01��19.2MM(Ĭ��)
             10��52M
             11��38.4M
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA6_UNION */
#define ABB_CH0_REG_DEBUG_ANA6_ADDR                   (ABB_BASE_ADDR + 0xE6)

/* �Ĵ���˵�����������ƼĴ�����
 bit[7:3]    Reserved
 bit[2:0]    L/W/G ����ADC ���Buffer�������ڿ���
             000��5u
             001��2u
             010��3u
             011��4u
             100��6u
             101��7u
             110��8u
             111��9u
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA7_UNION */
#define ABB_CH0_REG_DEBUG_ANA7_ADDR                   (ABB_BASE_ADDR + 0xE7)

/* �Ĵ���˵�����������ƼĴ�����
 bit[7:5]    Reserved
 bit[4:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA8_UNION */
#define ABB_CH0_REG_DEBUG_ANA8_ADDR                   (ABB_BASE_ADDR + 0xE8)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7:5]    Reserved
 bit[4]      LTE ADCģ��Tuning���ѡ��
             0��ѡ��Tuningģ��������ΪLTE ADC��Tuning��
             1��ѡ��Ĵ����������ΪLTE ADC��Tuning��
 bit[3]      LTE ADC DEM���ܹر��ź�
             0��DEMʹ��
             1��DEM��ʹ��
 bit[2]      Reserved
 bit[1]      LTE ADCģ������ģʽѡ��
             0���Զ�ģʽ
             1�����üĴ���ģʽ
 bit[0]      RX����sub_DAC Dummy��Ԫ���ƣ���һλ
             0������
             1���ر�
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA9_UNION */
#define ABB_CH0_REG_DEBUG_ANA9_ADDR                   (ABB_BASE_ADDR + 0xE9)

/* �Ĵ���˵����ADC��λ���ƼĴ�����
 bit[7]      LTE ADC��DACģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[6]      LTE ADC��OPģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[5]      LTE ADC��CKGENģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[4]      LTE ADC�е��������������ݸ�λ����
             0������λ
             1����λ
 bit[3]      LTE ADC�еڶ������������ݸ�λ����
             0������λ
             1����λ
 bit[2]      LTE ADC�е�һ�����������ݸ�λ����
             0������λ
             1����λ
 bit[1:0]    RX����sub_DAC Dummy��Ԫ���ƣ�����λ
             0������
             1���ر�
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA10_UNION */
#define ABB_CH0_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0xEA)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7]      0�� Reference turn off
             1�� BG_OPEN_EN is effective
 bit[6]      0�� Reference turn on
             1�� BG_OPEN_EN is not effective
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
 bit[7:6]    LTE SYNCʱ�����
             00��No delay
             01��250ps delay
             10��500ps delay
             11��1000ps delay
 bit[5:3]    Reserved
 bit[2:0]    LTE Overloadģ������
             00��16����������������С��
             01��8����������������С��
             10��4����������������С��
             11���ر�Overload���
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA14_UNION */
#define ABB_CH0_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0xEE)

/* �Ĵ���˵����ADC�ӳٿ��ƼĴ�����
   ��      ����LTE CLKGENʱ�����
            bit[4:0]��delayΪinput*40ps(Ĭ��480ps)
            bit[5]��  ��������ǰ�ض�
            bit[7:6]��DAC dealy input*40ps(Ĭ��0)
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0xEF)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7]      Reserved
 bit[6]      RX���PDM�������
             0��adder encoder
             1��de-bubble encoder
 bit[5:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA16_UNION */
#define ABB_CH0_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xF0)

/* �Ĵ���˵����PLL���ԼĴ�����
 bit[7:6]    PLL���Ƶ�ѹ����PAD�ź�ѡ��
             00�����Ƶ�ѹ����PAD����
             01��WPLL������Ƶ�ѹ��PAD
             10��GPLL������Ƶ�ѹ��PAD
 bit[5:4]    PLLʱ�Ӳ���PAD�ź�ѡ��
             00��ʱ�Ӳ���PAD����
             01��WPLL���ʱ�ӵ�PAD
             10��GPLL���ʱ�ӵ�PAD
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
 bit[4]      PLLģ��307.2MHzʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[3:2]    Reserved
 bit[1:0]    ���Թܽ����ʱ��Ƶ�ʿ���
             00��������ʱ��
             01��WPLL�������
             10��GPLL�������
             11��WPLL��GPLL�������
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA19_UNION */
#define ABB_CH0_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xF3)

/* �Ĵ���˵����ģ����ԼĴ�����
 bit[7]      Tuning��·����ѡ��
             0�������
             1��С����
 bit[6:5]    ADC���������ݱ���ϵ��
             00��X1(Ĭ��)
             01��X1.5
             10��X1.25
             11��X1.125
 bit[4:3]    Reserved
 bit[2]      PLLʱ�ӻ�׼ѡ���ź�
             0: CH0 ��TCXOʱ��
             1: CH1 ��TCXOʱ��
 bit[1]      CH0�͸�CH1��TCXOʱ�ӿ��ؿ���
             0���ر�
             1����
 bit[0]      TCXO Bufferѡ��
             0: ����TCXO Buffer
             1: ˫��TCXO Buffer
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA20_UNION */
#define ABB_CH0_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xF4)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xF5)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Tuning code����ֵ
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
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xFA)

/* �Ĵ���˵����ģ�����ֻ���Ĵ�����
   ��      ����������У���Ƿ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ARO0_ADDR                   (ABB_BASE_ADDR + 0xFB)

/* �Ĵ���˵����SINE���ͼĴ�����
 bit[7:4]    ���Ҳ�����Ƶ�ʿ��ƣ���λ(freq of tx_hb_clk)/32�����䷶ΧΪ1~f
 bit[3:2]    ���Ҳ����ͷ��ȿ���
             00��������
             01��3/4����
             10��1/2����
             11��1/4����
 bit[1]      ���Ҳ�����ͨ���л�
             0��CH1
             1��CH0
 bit[0]      ���Ҳ�����ʹ��
             0��������
             1������
   UNION�ṹ:  ABB_SINE_GENERATE_UNION */
#define ABB_SINE_GENERATE_ADDR                        (ABB_BASE_ADDR + 0xFF)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������reg_analog_wr50��
 bit[7]      TX ����ʱ����ѡ��
             0������(Ĭ��)
             1������
 bit[6:5]    Reserved


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
             101��7u
             110��6u
             111��5u
   UNION�ṹ:  ABB_TX_2G_ANA_3_UNION */
#define ABB_TX_2G_ANA_3_ADDR                          (ABB_BASE_ADDR + 0x100)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������reg_analog_wr51��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_2G_ANA_4_ADDR                          (ABB_BASE_ADDR + 0x101)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������reg_analog_wr52��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_2G_ANA_5_ADDR                          (ABB_BASE_ADDR + 0x102)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr53��
 bit[7:6]    Reserved
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
 bit[7:6]    Reserved
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
 bit[7:5]    Comstarv511_Reserved
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
 bit[6:5]    Reserved


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
             101��7u
             110��6u
             111��5u
   UNION�ṹ:  ABB_TX_CH0_3G_ANA_3_UNION */
#define ABB_TX_CH0_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x106)

/* �Ĵ���˵����CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr51��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_CH0_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x107)

/* �Ĵ���˵����CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr52��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_CH0_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x108)

/* �Ĵ���˵����CH0 RX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr53��
 bit[7:6]    Reserved
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
 bit[7:6]    Reserved
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
 bit[7:5]    Comstarv511_Reserved
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
 bit[6:5]    Reserved


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
             101��7u
             110��6u
             111��5u
   UNION�ṹ:  ABB_TX_CH0_4G_ANA_3_UNION */
#define ABB_TX_CH0_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x10C)

/* �Ĵ���˵����CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr51��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_CH0_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x10D)

/* �Ĵ���˵����CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr52��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_CH0_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x10E)

/* �Ĵ���˵����CH0 RX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr53��
 bit[7:6]    Reserved
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
 bit[7:6]    Reserved
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
 bit[7:5]    Comstarv511_Reserved
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
 bit[6:5]    Reserved


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
             101��7u
             110��6u
             111��5u
   UNION�ṹ:  ABB_TX_TDS_ANA_3_UNION */
#define ABB_TX_TDS_ANA_3_ADDR                         (ABB_BASE_ADDR + 0x112)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������reg_analog_wr51��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_TDS_ANA_4_ADDR                         (ABB_BASE_ADDR + 0x113)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������reg_analog_wr52��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_TDS_ANA_5_ADDR                         (ABB_BASE_ADDR + 0x114)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr53��
 bit[7:6]    Reserved
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
 bit[7:6]    Reserved
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
 bit[7:5]    Comstarv511_Reserved
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

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr50��
 bit[7]      TX ����ʱ����ѡ��
             0������(Ĭ��)
             1������
 bit[6:5]    Reserved


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
             101��7u
             110��6u
             111��5u
   UNION�ṹ:  ABB_TX_IDLE_ANA_3_UNION */
#define ABB_TX_IDLE_ANA_3_ADDR                        (ABB_BASE_ADDR + 0x12A)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr51��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_IDLE_ANA_4_ADDR                        (ABB_BASE_ADDR + 0x12B)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������reg_analog_wr52��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_IDLE_ANA_5_ADDR                        (ABB_BASE_ADDR + 0x12C)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr53��
 bit[7:6]    Reserved
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
 bit[7:6]    Reserved
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
 bit[7:5]    Comstarv511_Reserved
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
 bit[1:0]    Reserved
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
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_RX_2G_ANA_7_UNION */
#define ABB_RX_2G_ANA_7_ADDR                          (ABB_BASE_ADDR + 0x190)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      Reserved
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
   ��      ����Reserved
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
 bit[1:0]    Reserved
   UNION�ṹ:  ABB_RX_3G_ANA_6_UNION */
#define ABB_RX_3G_ANA_6_ADDR                          (ABB_BASE_ADDR + 0x195)

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
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_RX_3G_ANA_7_UNION */
#define ABB_RX_3G_ANA_7_ADDR                          (ABB_BASE_ADDR + 0x196)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      Reserved
 bit[6:5]    CK_CTRL_MODE
             00�� LTEģʽ
             01�� WDC &amp; X &amp; TDS_Aģʽ
             1x�� W &amp; G &amp; TDS_Bģʽ
 bit[4:0]    CK_CTRL_DATA
             00000 ����DACʱ����ǰ������
             11111 ����DACʱ����ǰ�����
   UNION�ṹ:  ABB_RX_3G_ANA_8_UNION */
#define ABB_RX_3G_ANA_8_ADDR                          (ABB_BASE_ADDR + 0x197)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr59��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_3G_ANA_9_ADDR                          (ABB_BASE_ADDR + 0x198)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr60��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_3G_ANA_10_ADDR                         (ABB_BASE_ADDR + 0x199)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������reg_analog_wr61��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_3G_ANA_11_ADDR                         (ABB_BASE_ADDR + 0x19A)

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
 bit[1:0]    Reserved
   UNION�ṹ:  ABB_RX_4G_ANA_6_UNION */
#define ABB_RX_4G_ANA_6_ADDR                          (ABB_BASE_ADDR + 0x19B)

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
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_RX_4G_ANA_7_UNION */
#define ABB_RX_4G_ANA_7_ADDR                          (ABB_BASE_ADDR + 0x19C)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      Reserved
 bit[6:5]    CK_CTRL_MODE
             00�� LTEģʽ
             01�� WDC &amp; X &amp; TDS_Aģʽ
             1x�� W &amp; G &amp; TDS_Bģʽ
 bit[4:0]    CK_CTRL_DATA
             00000 ����DACʱ����ǰ������
             11111 ����DACʱ����ǰ�����
   UNION�ṹ:  ABB_RX_4G_ANA_8_UNION */
#define ABB_RX_4G_ANA_8_ADDR                          (ABB_BASE_ADDR + 0x19D)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr59��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_4G_ANA_9_ADDR                          (ABB_BASE_ADDR + 0x19E)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr60��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_4G_ANA_10_ADDR                         (ABB_BASE_ADDR + 0x19F)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������reg_analog_wr61��
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_RX_4G_ANA_11_ADDR                         (ABB_BASE_ADDR + 0x1A0)

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
 bit[1:0]    Reserved
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
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_RX_TDS_ANA_7_UNION */
#define ABB_RX_TDS_ANA_7_ADDR                         (ABB_BASE_ADDR + 0x1A2)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      Reserved
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
   ��      ����Reserved
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
 bit[1:0]    Reserved
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
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_RX_IDLE_ANA_7_UNION */
#define ABB_RX_IDLE_ANA_7_ADDR                        (ABB_BASE_ADDR + 0x1A8)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      Reserved
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
   ��      ����Reserved
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

/* �Ĵ���˵�����߿�ǿ������ʹ�ܡ�
 bit[7:3]    Reserved
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
 bit[7]      �߿��ź�CH0_CFR_ENǿ������ʹ��
 bit[6]      �߿��ź�CH0_CFR_ENǿ������ֵ
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
 bit[7:3]    Reserved
 bit[2]      CFR�Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
 bit[1]      ���ż���Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
 bit[0]      BLOCKING�Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
   UNION�ṹ:  ABB_CH0_CLK_SEL_UNION */
#define ABB_CH0_CLK_SEL_ADDR                          (ABB_BASE_ADDR + 0x1D2)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7:3]    Reserved
 bit[2]      TX_EN�߿�״̬�ϱ�
 bit[1]      RXB_EN�߿�״̬�ϱ�
 bit[0]      RXA_EN�߿�״̬�ϱ�
   UNION�ṹ:  ABB_CH0_LINE_RPT0_UNION */
#define ABB_CH0_LINE_RPT0_ADDR                        (ABB_BASE_ADDR + 0x1F0)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7]      Reserved
 bit[6]      CFR_EN�߿�״̬�ϱ�
 bit[5]      RXB_BLK_EN�߿�״̬�ϱ�
 bit[4]      RXA_BLK_EN�߿�״̬�ϱ�
 bit[3]      Reserved
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
             001��3G_SCReserved
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
             Reserved
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
 bit[7:1]    ������
 bit[0]      RXBͨ��ѡ��
             0��ѡ��CH0��
             1��ѡ��CH1��.
   UNION�ṹ:  ABB_RXB_CH_SEL_UNION */
#define ABB_RXB_CH_SEL_ADDR                           (ABB_BASE_ADDR + 0x1F6)

/* �Ĵ���˵����ͨ��0 TDS���üĴ�����
 bit[7:3]    ������
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

/* �Ĵ���˵����ͨ��0 CFR���üĴ�����
   ��      ����ͨ��0 CFR��ֵ�������ֵ��bit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_CFR_PDET_THR0_ADDR                    (ABB_BASE_ADDR + 0x201)

/* �Ĵ���˵����ͨ��0 CFR���üĴ�����
   ��      ����ͨ��0 CFR��ֵ�������ֵ��bit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_CFR_PDET_THR1_ADDR                    (ABB_BASE_ADDR + 0x202)

/* �Ĵ���˵����ͨ��0 CFR���üĴ�����
 bit[7:2]    ������
 bit[1:0]    ͨ��0 CFR��ֵ�������ֵ��bit[17:16]��
   UNION�ṹ:  ABB_CH0_CFR_PDET_THR2_UNION */
#define ABB_CH0_CFR_PDET_THR2_ADDR                    (ABB_BASE_ADDR + 0x203)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�A����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EA0_ADDR                        (ABB_BASE_ADDR + 0x204)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�A����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EA1_ADDR                        (ABB_BASE_ADDR + 0x205)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�A����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EA2_ADDR                        (ABB_BASE_ADDR + 0x206)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
 bit[7:2]    ������
 bit[1:0]    ͨ��0���ż��RXAͨ��I·�ڵ�A����ͳ��ֵbit[25:24]��
   UNION�ṹ:  ABB_CH0_RXA_I_EA3_UNION */
#define ABB_CH0_RXA_I_EA3_ADDR                        (ABB_BASE_ADDR + 0x207)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�B����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EB0_ADDR                        (ABB_BASE_ADDR + 0x208)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�B����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EB1_ADDR                        (ABB_BASE_ADDR + 0x209)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�B����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EB2_ADDR                        (ABB_BASE_ADDR + 0x20A)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�B����ͳ��ֵbit[31:24]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EB3_ADDR                        (ABB_BASE_ADDR + 0x20B)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�B����ͳ��ֵbit[39:32]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EB4_ADDR                        (ABB_BASE_ADDR + 0x20C)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�C����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EC0_ADDR                        (ABB_BASE_ADDR + 0x20D)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�C����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EC1_ADDR                        (ABB_BASE_ADDR + 0x20E)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�C����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EC2_ADDR                        (ABB_BASE_ADDR + 0x20F)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�C����ͳ��ֵbit[31:24]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EC3_ADDR                        (ABB_BASE_ADDR + 0x210)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�C����ͳ��ֵbit[39:32]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EC4_ADDR                        (ABB_BASE_ADDR + 0x211)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�C����ͳ��ֵbit[47:40]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_EC5_ADDR                        (ABB_BASE_ADDR + 0x212)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
 bit[7:2]    ������
 bit[1:0]    ͨ��0���ż��RXAͨ��I·�ڵ�C����ͳ��ֵbit[49:48]��
   UNION�ṹ:  ABB_CH0_RXA_I_EC6_UNION */
#define ABB_CH0_RXA_I_EC6_ADDR                        (ABB_BASE_ADDR + 0x213)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�D����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_ED0_ADDR                        (ABB_BASE_ADDR + 0x214)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�D����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_ED1_ADDR                        (ABB_BASE_ADDR + 0x215)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�D����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_ED2_ADDR                        (ABB_BASE_ADDR + 0x216)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�D����ͳ��ֵbit[31:24]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_ED3_ADDR                        (ABB_BASE_ADDR + 0x217)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�D����ͳ��ֵbit[39:32]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_ED4_ADDR                        (ABB_BASE_ADDR + 0x218)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��I·�ڵ�D����ͳ��ֵbit[47:40]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_ED5_ADDR                        (ABB_BASE_ADDR + 0x219)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
 bit[7:2]    ������
 bit[1:0]    ͨ��0���ż��RXAͨ��I·�ڵ�D����ͳ��ֵbit[49:48]��
   UNION�ṹ:  ABB_CH0_RXA_I_ED6_UNION */
#define ABB_CH0_RXA_I_ED6_ADDR                        (ABB_BASE_ADDR + 0x21A)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�A����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EA0_ADDR                        (ABB_BASE_ADDR + 0x21B)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�A����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EA1_ADDR                        (ABB_BASE_ADDR + 0x21C)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�A����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EA2_ADDR                        (ABB_BASE_ADDR + 0x21D)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
 bit[7:2]    ������
 bit[1:0]    ͨ��0���ż��RXAͨ��Q·�ڵ�A����ͳ��ֵbit[25:24]��
   UNION�ṹ:  ABB_CH0_RXA_Q_EA3_UNION */
#define ABB_CH0_RXA_Q_EA3_ADDR                        (ABB_BASE_ADDR + 0x21E)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�B����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EB0_ADDR                        (ABB_BASE_ADDR + 0x21F)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�B����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EB1_ADDR                        (ABB_BASE_ADDR + 0x220)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�B����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EB2_ADDR                        (ABB_BASE_ADDR + 0x221)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�B����ͳ��ֵbit[31:24]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EB3_ADDR                        (ABB_BASE_ADDR + 0x222)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�B����ͳ��ֵbit[39:32]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EB4_ADDR                        (ABB_BASE_ADDR + 0x223)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�C����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EC0_ADDR                        (ABB_BASE_ADDR + 0x224)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�C����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EC1_ADDR                        (ABB_BASE_ADDR + 0x225)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�C����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EC2_ADDR                        (ABB_BASE_ADDR + 0x226)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�C����ͳ��ֵbit[31:24]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EC3_ADDR                        (ABB_BASE_ADDR + 0x227)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�C����ͳ��ֵbit[39:32]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EC4_ADDR                        (ABB_BASE_ADDR + 0x228)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�C����ͳ��ֵbit[47:40]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_EC5_ADDR                        (ABB_BASE_ADDR + 0x229)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
 bit[7:2]    ������
 bit[1:0]    ͨ��0���ż��RXAͨ��Q·�ڵ�C����ͳ��ֵbit[49:48]��
   UNION�ṹ:  ABB_CH0_RXA_Q_EC6_UNION */
#define ABB_CH0_RXA_Q_EC6_ADDR                        (ABB_BASE_ADDR + 0x22A)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�D����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_ED0_ADDR                        (ABB_BASE_ADDR + 0x22B)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�D����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_ED1_ADDR                        (ABB_BASE_ADDR + 0x22C)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�D����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_ED2_ADDR                        (ABB_BASE_ADDR + 0x22D)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�D����ͳ��ֵbit[31:24]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_ED3_ADDR                        (ABB_BASE_ADDR + 0x22E)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�D����ͳ��ֵbit[39:32]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_ED4_ADDR                        (ABB_BASE_ADDR + 0x22F)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXAͨ��Q·�ڵ�D����ͳ��ֵbit[47:40]��
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_ED5_ADDR                        (ABB_BASE_ADDR + 0x230)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
 bit[7:2]    ������
 bit[1:0]    ͨ��0���ż��RXAͨ��Q·�ڵ�D����ͳ��ֵbit[49:48]��
   UNION�ṹ:  ABB_CH0_RXA_Q_ED6_UNION */
#define ABB_CH0_RXA_Q_ED6_ADDR                        (ABB_BASE_ADDR + 0x231)

/* �Ĵ���˵����ͨ��0���üĴ�����
   ��      ����ͨ��0 flush���[7:0]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ ���� */
#define ABB_CH0_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x232)

/* �Ĵ���˵����ͨ��0���üĴ�����
 bit[7:3]    ͨ��0 FLUSHֵ��Ĭ��Ϊ8��
 bit[2:0]    ͨ��0 flush���[10:8]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ:  ABB_CH0_FLUSH_CFG1_UNION */
#define ABB_CH0_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x233)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�A����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EA0_ADDR                        (ABB_BASE_ADDR + 0x234)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�A����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EA1_ADDR                        (ABB_BASE_ADDR + 0x235)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�A����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EA2_ADDR                        (ABB_BASE_ADDR + 0x236)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
 bit[7:2]    ������
 bit[1:0]    ͨ��0���ż��RXBͨ��I·�ڵ�A����ͳ��ֵbit[25:24]��
   UNION�ṹ:  ABB_CH0_RXB_I_EA3_UNION */
#define ABB_CH0_RXB_I_EA3_ADDR                        (ABB_BASE_ADDR + 0x237)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�B����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EB0_ADDR                        (ABB_BASE_ADDR + 0x238)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�B����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EB1_ADDR                        (ABB_BASE_ADDR + 0x239)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�B����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EB2_ADDR                        (ABB_BASE_ADDR + 0x23A)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�B����ͳ��ֵbit[31:24]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EB3_ADDR                        (ABB_BASE_ADDR + 0x23B)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�B����ͳ��ֵbit[39:32]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EB4_ADDR                        (ABB_BASE_ADDR + 0x23C)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�C����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EC0_ADDR                        (ABB_BASE_ADDR + 0x23D)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�C����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EC1_ADDR                        (ABB_BASE_ADDR + 0x23E)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�C����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EC2_ADDR                        (ABB_BASE_ADDR + 0x23F)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�C����ͳ��ֵbit[31:24]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EC3_ADDR                        (ABB_BASE_ADDR + 0x240)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�C����ͳ��ֵbit[39:32]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EC4_ADDR                        (ABB_BASE_ADDR + 0x241)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�C����ͳ��ֵbit[47:40]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_EC5_ADDR                        (ABB_BASE_ADDR + 0x242)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
 bit[7:2]    ������
 bit[1:0]    ͨ��0���ż��RXBͨ��I·�ڵ�C����ͳ��ֵbit[49:48]��
   UNION�ṹ:  ABB_CH0_RXB_I_EC6_UNION */
#define ABB_CH0_RXB_I_EC6_ADDR                        (ABB_BASE_ADDR + 0x243)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�D����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_ED0_ADDR                        (ABB_BASE_ADDR + 0x244)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�D����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_ED1_ADDR                        (ABB_BASE_ADDR + 0x245)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�D����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_ED2_ADDR                        (ABB_BASE_ADDR + 0x246)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�D����ͳ��ֵbit[31:24]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_ED3_ADDR                        (ABB_BASE_ADDR + 0x247)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�D����ͳ��ֵbit[39:32]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_ED4_ADDR                        (ABB_BASE_ADDR + 0x248)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��I·�ڵ�D����ͳ��ֵbit[47:40]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_ED5_ADDR                        (ABB_BASE_ADDR + 0x249)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
 bit[7:2]    ������
 bit[1:0]    ͨ��0���ż��RXBͨ��I·�ڵ�D����ͳ��ֵbit[49:48]��
   UNION�ṹ:  ABB_CH0_RXB_I_ED6_UNION */
#define ABB_CH0_RXB_I_ED6_ADDR                        (ABB_BASE_ADDR + 0x24A)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�A����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EA0_ADDR                        (ABB_BASE_ADDR + 0x24B)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�A����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EA1_ADDR                        (ABB_BASE_ADDR + 0x24C)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�A����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EA2_ADDR                        (ABB_BASE_ADDR + 0x24D)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
 bit[7:2]    ����
 bit[1:0]    ͨ��0���ż��RXBͨ��Q·�ڵ�A����ͳ��ֵbit[25:24]��
   UNION�ṹ:  ABB_CH0_RXB_Q_EA3_UNION */
#define ABB_CH0_RXB_Q_EA3_ADDR                        (ABB_BASE_ADDR + 0x24E)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�B����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EB0_ADDR                        (ABB_BASE_ADDR + 0x24F)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�B����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EB1_ADDR                        (ABB_BASE_ADDR + 0x250)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�B����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EB2_ADDR                        (ABB_BASE_ADDR + 0x251)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�B����ͳ��ֵbit[31:24]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EB3_ADDR                        (ABB_BASE_ADDR + 0x252)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�B����ͳ��ֵbit[39:32]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EB4_ADDR                        (ABB_BASE_ADDR + 0x253)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�C����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EC0_ADDR                        (ABB_BASE_ADDR + 0x254)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�C����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EC1_ADDR                        (ABB_BASE_ADDR + 0x255)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�C����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EC2_ADDR                        (ABB_BASE_ADDR + 0x256)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�C����ͳ��ֵbit[31:24]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EC3_ADDR                        (ABB_BASE_ADDR + 0x257)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�C����ͳ��ֵbit[39:32]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EC4_ADDR                        (ABB_BASE_ADDR + 0x258)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�C����ͳ��ֵbit[47:40]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_EC5_ADDR                        (ABB_BASE_ADDR + 0x259)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
 bit[7:2]    ����
 bit[1:0]    ͨ��0���ż��RXBͨ��Q·�ڵ�C����ͳ��ֵbit[49:48]��
   UNION�ṹ:  ABB_CH0_RXB_Q_EC6_UNION */
#define ABB_CH0_RXB_Q_EC6_ADDR                        (ABB_BASE_ADDR + 0x25A)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�D����ͳ��ֵbit[7:0]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_ED0_ADDR                        (ABB_BASE_ADDR + 0x25B)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�D����ͳ��ֵbit[15:8]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_ED1_ADDR                        (ABB_BASE_ADDR + 0x25C)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�D����ͳ��ֵbit[23:16]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_ED2_ADDR                        (ABB_BASE_ADDR + 0x25D)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�D����ͳ��ֵbit[31:24]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_ED3_ADDR                        (ABB_BASE_ADDR + 0x25E)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�D����ͳ��ֵbit[39:32]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_ED4_ADDR                        (ABB_BASE_ADDR + 0x25F)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
   ��      ����ͨ��0���ż��RXBͨ��Q·�ڵ�D����ͳ��ֵbit[47:40]��
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_ED5_ADDR                        (ABB_BASE_ADDR + 0x260)

/* �Ĵ���˵����ͨ��0���ż���ϱ��Ĵ�����
 bit[7:2]    ����
 bit[1:0]    ͨ��0���ż��RXBͨ��Q·�ڵ�D����ͳ��ֵbit[49:48]��
   UNION�ṹ:  ABB_CH0_RXB_Q_ED6_UNION */
#define ABB_CH0_RXB_Q_ED6_ADDR                        (ABB_BASE_ADDR + 0x261)

/* �Ĵ���˵����RX Cģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SCReserved
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
             Reserved
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
 bit[7:2]    Reserved
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
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
 bit[1]      Reserved
 bit[0]      Mode setting for ADC
             1�� CA mode
             0�� others
   UNION�ṹ:  ABB_RX_C_ANA_2_UNION */
#define ABB_RX_C_ANA_2_ADDR                           (ABB_BASE_ADDR + 0x406)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������reg_analog_wr53��
 bit[7:6]    Reserved
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
 bit[7:6]    Reserved
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
 bit[7:5]    Comstarv511_Reserved
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
 bit[1:0]    Reserved
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
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_RX_C_ANA_7_UNION */
#define ABB_RX_C_ANA_7_ADDR                           (ABB_BASE_ADDR + 0x40B)

/* �Ĵ���˵����RX C���üĴ����������߿��߼�������reg_analog_wr58��
 bit[7]      Reserved
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
   ��      ����Reserved
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
 bit[7:6]    TX filter��ֹƵ��ѡ��
             00��5MHz(Ĭ��)WSC&amp;GSM&amp;CDMA
             01��10MHz WDC
             10��Reserved
             11��20MHz LTE
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00��1��Ƶ
             01��2��Ƶ(Ĭ��)
             10��3��Ƶ
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
             000��4G &amp; ET &amp; APT
             001��3G &amp; TDS
             010��CA
             011��2G(Ĭ��)
             1xx��CDMA
   UNION�ṹ:  ABB_TX_C_ANA_1_UNION */
#define ABB_TX_C_ANA_1_ADDR                           (ABB_BASE_ADDR + 0x410)

/* �Ĵ���˵����TX C���üĴ����������߿��߼�������reg_analog_wr49��
 bit[7]      {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵����
 bit[6]      TBD
 bit[5:4]    LPF �˷�ƫ�õ�������
             �˷ŵ�����   op1   op2
             00��         10u   10u
             01��         5u    5u
             10��         2.5u  5u
             11��         2.5u  2.5u
             LTE:00
             Others:01
 bit[3:2]    LPF OP2 ����ģʽ����
             00 �������������
             01 ����������Ӵ�������5uAƫ�ã�
             10 ������ʹ��
             11 ����������ټӴ�������2.5uAƫ�ã�
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
 bit[1:0]    LPF OP1 ����ģʽ����
             bit0��
             0�� �������������
             1�� ����������Ӵ�������5uAƫ�ã�
             bit1��
             0�� miller������������
             1�� miller�������ݱ��������2.5uAƫ�ã�
             LTE:00
             WDC:01
             SC:01
             CDMA&amp;GSM:10
   UNION�ṹ:  ABB_TX_C_ANA_2_UNION */
#define ABB_TX_C_ANA_2_ADDR                           (ABB_BASE_ADDR + 0x411)

/* �Ĵ���˵����TX C���üĴ����������߿��߼�������reg_analog_wr50��
 bit[7]      TX ����ʱ����ѡ��
             0������(Ĭ��)
             1������
 bit[6:5]    Reserved


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
             101��7u
             110��6u
             111��5u
   UNION�ṹ:  ABB_TX_C_ANA_3_UNION */
#define ABB_TX_C_ANA_3_ADDR                           (ABB_BASE_ADDR + 0x412)

/* �Ĵ���˵����TX C���üĴ����������߿��߼�������reg_analog_wr51��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_C_ANA_4_ADDR                           (ABB_BASE_ADDR + 0x413)

/* �Ĵ���˵����TX C���üĴ����������߿��߼�������reg_analog_wr52��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_C_ANA_5_ADDR                           (ABB_BASE_ADDR + 0x414)





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
                                                            001��3G_SCReserved */
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
                                                         Reserved */
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
                                                         1��bypass(Ĭ��) */
        unsigned long  tx_flush_en_2g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                         0����ʹ��
                                                         1��ʹ�� */
        unsigned long  reserved       : 6;  /* bit[2-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_3_UNION;
#define ABB_TX_2G_DIG_3_tx_cfr_bp_2g_START    (0)
#define ABB_TX_2G_DIG_3_tx_cfr_bp_2g_END      (0)
#define ABB_TX_2G_DIG_3_tx_flush_en_2g_START  (1)
#define ABB_TX_2G_DIG_3_tx_flush_en_2g_END    (1)


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
        unsigned long  rx_comp_sel_b0_3g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                            00���̶�ϵ��1��
                                                            01���̶�ϵ��2��
                                                            10���̶�ϵ��3��
                                                            11��reserved�� */
        unsigned long  rx_comp_fix_3g    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                            0��ϵ�����̶����ɼĴ�������
                                                            1��ϵ���̶� */
        unsigned long  rx_hb_bp_3g       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                            0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                            1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_3g        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                      /TDS_B/4G_C,        /4G_B,
                                                            00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
                                                            others��reserved */
        unsigned long  rx_mode_dig_3g    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                            000��2G(Ĭ��)
                                                            001��3G_SCReserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_DIG_1_UNION;
#define ABB_RX_CH0_3G_DIG_1_rx_comp_sel_b0_3g_START  (0)
#define ABB_RX_CH0_3G_DIG_1_rx_comp_sel_b0_3g_END    (0)
#define ABB_RX_CH0_3G_DIG_1_rx_comp_fix_3g_START     (1)
#define ABB_RX_CH0_3G_DIG_1_rx_comp_fix_3g_END       (1)
#define ABB_RX_CH0_3G_DIG_1_rx_hb_bp_3g_START        (2)
#define ABB_RX_CH0_3G_DIG_1_rx_hb_bp_3g_END          (2)
#define ABB_RX_CH0_3G_DIG_1_rx_rate_3g_START         (3)
#define ABB_RX_CH0_3G_DIG_1_rx_rate_3g_END           (4)
#define ABB_RX_CH0_3G_DIG_1_rx_mode_dig_3g_START     (5)
#define ABB_RX_CH0_3G_DIG_1_rx_mode_dig_3g_END       (7)


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
        unsigned long  rxa_pd_3g         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_3g         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_3g       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                            00��gainΪ0.5(Ĭ��)
                                                            01��gainΪ0.75
                                                            10��gainΪ0.85
                                                            11��Reserved */
        unsigned long  rx_comp_bp_3g     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                            0����bypass(Ĭ��)
                                                            1��bypass */
        unsigned long  rx_clk_inv_3g     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                            0������
                                                            1������ */
        unsigned long  rx_flush_en_3g    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                            0����ʹ��
                                                            1��ʹ�� */
        unsigned long  rx_comp_sel_b1_3g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_3G_DIG_2_UNION;
#define ABB_RX_CH0_3G_DIG_2_rxa_pd_3g_START          (0)
#define ABB_RX_CH0_3G_DIG_2_rxa_pd_3g_END            (0)
#define ABB_RX_CH0_3G_DIG_2_rxb_pd_3g_START          (1)
#define ABB_RX_CH0_3G_DIG_2_rxb_pd_3g_END            (1)
#define ABB_RX_CH0_3G_DIG_2_gain_sel_3g_START        (2)
#define ABB_RX_CH0_3G_DIG_2_gain_sel_3g_END          (3)
#define ABB_RX_CH0_3G_DIG_2_rx_comp_bp_3g_START      (4)
#define ABB_RX_CH0_3G_DIG_2_rx_comp_bp_3g_END        (4)
#define ABB_RX_CH0_3G_DIG_2_rx_clk_inv_3g_START      (5)
#define ABB_RX_CH0_3G_DIG_2_rx_clk_inv_3g_END        (5)
#define ABB_RX_CH0_3G_DIG_2_rx_flush_en_3g_START     (6)
#define ABB_RX_CH0_3G_DIG_2_rx_flush_en_3g_END       (6)
#define ABB_RX_CH0_3G_DIG_2_rx_comp_sel_b1_3g_START  (7)
#define ABB_RX_CH0_3G_DIG_2_rx_comp_sel_b1_3g_END    (7)


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
        unsigned long  tx_comp_bp_3g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                         0����bypass(Ĭ��)
                                                         1��bypass */
        unsigned long  tx_hb_bp_3g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_3g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                              2G,     3G,     4G,      TDS,      CDMA
                                                             (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                         0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
                                                         1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                         2��-------,--------,15.36MHz,--------,--------
                                                         Others��Reserved */
        unsigned long  tx_mode_dig_3g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                         000��2G(Ĭ��)
                                                         001��3G
                                                         010��4G
                                                         011��TDS
                                                         Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_1_UNION;
#define ABB_TX_CH0_3G_DIG_1_tx_comp_bp_3g_START   (0)
#define ABB_TX_CH0_3G_DIG_1_tx_comp_bp_3g_END     (0)
#define ABB_TX_CH0_3G_DIG_1_tx_hb_bp_3g_START     (1)
#define ABB_TX_CH0_3G_DIG_1_tx_hb_bp_3g_END       (1)
#define ABB_TX_CH0_3G_DIG_1_tx_rate_3g_START      (2)
#define ABB_TX_CH0_3G_DIG_1_tx_rate_3g_END        (4)
#define ABB_TX_CH0_3G_DIG_1_tx_mode_dig_3g_START  (5)
#define ABB_TX_CH0_3G_DIG_1_tx_mode_dig_3g_END    (7)


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
        unsigned long  tx_q_pd_3g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_3g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_3g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                           0��0(Ĭ��)
                                                           1��2
                                                           2��4
                                                           3��6 */
        unsigned long  uddwa_dith_en_3g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  dem_dwa_en_3g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                           0��ʹ��CLAģʽ
                                                           1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  dem_lsb_bp_3g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                           0��DEM LSB ��(Ĭ��)
                                                           1��DEM LSB bypass */
        unsigned long  dem_msb_bp_3g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                           0��DEM MSB��(Ĭ��)
                                                           1��DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_2_UNION;
#define ABB_TX_CH0_3G_DIG_2_tx_q_pd_3g_START        (0)
#define ABB_TX_CH0_3G_DIG_2_tx_q_pd_3g_END          (0)
#define ABB_TX_CH0_3G_DIG_2_tx_i_pd_3g_START        (1)
#define ABB_TX_CH0_3G_DIG_2_tx_i_pd_3g_END          (1)
#define ABB_TX_CH0_3G_DIG_2_dem_const_3g_START      (2)
#define ABB_TX_CH0_3G_DIG_2_dem_const_3g_END        (3)
#define ABB_TX_CH0_3G_DIG_2_uddwa_dith_en_3g_START  (4)
#define ABB_TX_CH0_3G_DIG_2_uddwa_dith_en_3g_END    (4)
#define ABB_TX_CH0_3G_DIG_2_dem_dwa_en_3g_START     (5)
#define ABB_TX_CH0_3G_DIG_2_dem_dwa_en_3g_END       (5)
#define ABB_TX_CH0_3G_DIG_2_dem_lsb_bp_3g_START     (6)
#define ABB_TX_CH0_3G_DIG_2_dem_lsb_bp_3g_END       (6)
#define ABB_TX_CH0_3G_DIG_2_dem_msb_bp_3g_START     (7)
#define ABB_TX_CH0_3G_DIG_2_dem_msb_bp_3g_END       (7)


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
        unsigned long  tx_cfr_bp_3g   : 1;  /* bit[0]  : TXͨ��CFR bypass���ƣ�
                                                         0����bypass
                                                         1��bypass(Ĭ��) */
        unsigned long  tx_flush_en_3g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                         0����ʹ��
                                                         1��ʹ�� */
        unsigned long  reserved       : 6;  /* bit[2-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_DIG_3_UNION;
#define ABB_TX_CH0_3G_DIG_3_tx_cfr_bp_3g_START    (0)
#define ABB_TX_CH0_3G_DIG_3_tx_cfr_bp_3g_END      (0)
#define ABB_TX_CH0_3G_DIG_3_tx_flush_en_3g_START  (1)
#define ABB_TX_CH0_3G_DIG_3_tx_flush_en_3g_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_CH0_4G_DIG_1_UNION
 �ṹ˵��  : rx_ch0_4g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0xA����ֵ:0x40�����:8
 �Ĵ���˵��: CH0 RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_4g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                            00���̶�ϵ��1��
                                                            01���̶�ϵ��2��
                                                            10���̶�ϵ��3��
                                                            11��reserved�� */
        unsigned long  rx_comp_fix_4g    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                            0��ϵ�����̶����ɼĴ�������
                                                            1��ϵ���̶� */
        unsigned long  rx_hb_bp_4g       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                            0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                            1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_4g        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                2G,     3G_SC      4G,    3G_DC    TDS,   CDMA
                                                                      /TDS_B/4G_C,        /4G_B,
                                                            00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��)
                                                            others��reserved */
        unsigned long  rx_mode_dig_4g    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                            000��2G(Ĭ��)
                                                            001��3G_SCReserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_DIG_1_UNION;
#define ABB_RX_CH0_4G_DIG_1_rx_comp_sel_b0_4g_START  (0)
#define ABB_RX_CH0_4G_DIG_1_rx_comp_sel_b0_4g_END    (0)
#define ABB_RX_CH0_4G_DIG_1_rx_comp_fix_4g_START     (1)
#define ABB_RX_CH0_4G_DIG_1_rx_comp_fix_4g_END       (1)
#define ABB_RX_CH0_4G_DIG_1_rx_hb_bp_4g_START        (2)
#define ABB_RX_CH0_4G_DIG_1_rx_hb_bp_4g_END          (2)
#define ABB_RX_CH0_4G_DIG_1_rx_rate_4g_START         (3)
#define ABB_RX_CH0_4G_DIG_1_rx_rate_4g_END           (4)
#define ABB_RX_CH0_4G_DIG_1_rx_mode_dig_4g_START     (5)
#define ABB_RX_CH0_4G_DIG_1_rx_mode_dig_4g_END       (7)


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
        unsigned long  rxa_pd_4g         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_4g         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_4g       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                            00��gainΪ0.5(Ĭ��)
                                                            01��gainΪ0.75
                                                            10��gainΪ0.85
                                                            11��Reserved */
        unsigned long  rx_comp_bp_4g     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                            0����bypass(Ĭ��)
                                                            1��bypass */
        unsigned long  rx_clk_inv_4g     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                            0������
                                                            1������ */
        unsigned long  rx_flush_en_4g    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                            0����ʹ��
                                                            1��ʹ�� */
        unsigned long  rx_comp_sel_b1_4g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CH0_4G_DIG_2_UNION;
#define ABB_RX_CH0_4G_DIG_2_rxa_pd_4g_START          (0)
#define ABB_RX_CH0_4G_DIG_2_rxa_pd_4g_END            (0)
#define ABB_RX_CH0_4G_DIG_2_rxb_pd_4g_START          (1)
#define ABB_RX_CH0_4G_DIG_2_rxb_pd_4g_END            (1)
#define ABB_RX_CH0_4G_DIG_2_gain_sel_4g_START        (2)
#define ABB_RX_CH0_4G_DIG_2_gain_sel_4g_END          (3)
#define ABB_RX_CH0_4G_DIG_2_rx_comp_bp_4g_START      (4)
#define ABB_RX_CH0_4G_DIG_2_rx_comp_bp_4g_END        (4)
#define ABB_RX_CH0_4G_DIG_2_rx_clk_inv_4g_START      (5)
#define ABB_RX_CH0_4G_DIG_2_rx_clk_inv_4g_END        (5)
#define ABB_RX_CH0_4G_DIG_2_rx_flush_en_4g_START     (6)
#define ABB_RX_CH0_4G_DIG_2_rx_flush_en_4g_END       (6)
#define ABB_RX_CH0_4G_DIG_2_rx_comp_sel_b1_4g_START  (7)
#define ABB_RX_CH0_4G_DIG_2_rx_comp_sel_b1_4g_END    (7)


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
        unsigned long  tx_comp_bp_4g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                         0����bypass(Ĭ��)
                                                         1��bypass */
        unsigned long  tx_hb_bp_4g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_4g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                              2G,     3G,     4G,      TDS,      CDMA
                                                             (78M) (153.6M) (307.2M) (153.6M) (122.88M)
                                                         0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz(Ĭ��)
                                                         1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                         2��-------,--------,15.36MHz,--------,--------
                                                         Others��Reserved */
        unsigned long  tx_mode_dig_4g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                         000��2G(Ĭ��)
                                                         001��3G
                                                         010��4G
                                                         011��TDS
                                                         Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_1_UNION;
#define ABB_TX_CH0_4G_DIG_1_tx_comp_bp_4g_START   (0)
#define ABB_TX_CH0_4G_DIG_1_tx_comp_bp_4g_END     (0)
#define ABB_TX_CH0_4G_DIG_1_tx_hb_bp_4g_START     (1)
#define ABB_TX_CH0_4G_DIG_1_tx_hb_bp_4g_END       (1)
#define ABB_TX_CH0_4G_DIG_1_tx_rate_4g_START      (2)
#define ABB_TX_CH0_4G_DIG_1_tx_rate_4g_END        (4)
#define ABB_TX_CH0_4G_DIG_1_tx_mode_dig_4g_START  (5)
#define ABB_TX_CH0_4G_DIG_1_tx_mode_dig_4g_END    (7)


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
        unsigned long  tx_q_pd_4g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_4g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_4g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                           0��0(Ĭ��)
                                                           1��2
                                                           2��4
                                                           3��6 */
        unsigned long  uddwa_dith_en_4g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  dem_dwa_en_4g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                           0��ʹ��CLAģʽ
                                                           1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  dem_lsb_bp_4g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                           0��DEM LSB ��(Ĭ��)
                                                           1��DEM LSB bypass */
        unsigned long  dem_msb_bp_4g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                           0��DEM MSB��(Ĭ��)
                                                           1��DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_2_UNION;
#define ABB_TX_CH0_4G_DIG_2_tx_q_pd_4g_START        (0)
#define ABB_TX_CH0_4G_DIG_2_tx_q_pd_4g_END          (0)
#define ABB_TX_CH0_4G_DIG_2_tx_i_pd_4g_START        (1)
#define ABB_TX_CH0_4G_DIG_2_tx_i_pd_4g_END          (1)
#define ABB_TX_CH0_4G_DIG_2_dem_const_4g_START      (2)
#define ABB_TX_CH0_4G_DIG_2_dem_const_4g_END        (3)
#define ABB_TX_CH0_4G_DIG_2_uddwa_dith_en_4g_START  (4)
#define ABB_TX_CH0_4G_DIG_2_uddwa_dith_en_4g_END    (4)
#define ABB_TX_CH0_4G_DIG_2_dem_dwa_en_4g_START     (5)
#define ABB_TX_CH0_4G_DIG_2_dem_dwa_en_4g_END       (5)
#define ABB_TX_CH0_4G_DIG_2_dem_lsb_bp_4g_START     (6)
#define ABB_TX_CH0_4G_DIG_2_dem_lsb_bp_4g_END       (6)
#define ABB_TX_CH0_4G_DIG_2_dem_msb_bp_4g_START     (7)
#define ABB_TX_CH0_4G_DIG_2_dem_msb_bp_4g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_4G_DIG_3_UNION
 �ṹ˵��  : tx_ch0_4g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0xE����ֵ:0x00�����:8
 �Ĵ���˵��: CH0 TX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_cfr_bp_4g   : 1;  /* bit[0]  : TXͨ��CFR bypass���ƣ�
                                                         0����bypass(Ĭ��)
                                                         1��bypass */
        unsigned long  tx_flush_en_4g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                         0����ʹ��
                                                         1��ʹ�� */
        unsigned long  reserved       : 6;  /* bit[2-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_DIG_3_UNION;
#define ABB_TX_CH0_4G_DIG_3_tx_cfr_bp_4g_START    (0)
#define ABB_TX_CH0_4G_DIG_3_tx_cfr_bp_4g_END      (0)
#define ABB_TX_CH0_4G_DIG_3_tx_flush_en_4g_START  (1)
#define ABB_TX_CH0_4G_DIG_3_tx_flush_en_4g_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_DIG_1_UNION
 �ṹ˵��  : rx_tds_dig_1 �Ĵ����ṹ���塣��ַƫ����:0xF����ֵ:0x24�����:8
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
                                                             001��3G_SCReserved */
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
 �ṹ˵��  : rx_tds_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x53�����:8
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
                                                          1��bypass(Ĭ��) */
        unsigned long  tx_flush_en_tds : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                          0����ʹ��
                                                          1��ʹ�� */
        unsigned long  reserved        : 6;  /* bit[2-7]: Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_3_UNION;
#define ABB_TX_TDS_DIG_3_tx_cfr_bp_tds_START    (0)
#define ABB_TX_TDS_DIG_3_tx_cfr_bp_tds_END      (0)
#define ABB_TX_TDS_DIG_3_tx_flush_en_tds_START  (1)
#define ABB_TX_TDS_DIG_3_tx_flush_en_tds_END    (1)


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
                                                           Reserved */
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
                                                           1��bypass(Ĭ��) */
        unsigned long  tx_flush_en_idle : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  reserved         : 6;  /* bit[2-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_3_UNION;
#define ABB_TX_IDLE_DIG_3_tx_cfr_bp_idle_START    (0)
#define ABB_TX_IDLE_DIG_3_tx_cfr_bp_idle_END      (0)
#define ABB_TX_IDLE_DIG_3_tx_flush_en_idle_START  (1)
#define ABB_TX_IDLE_DIG_3_tx_flush_en_idle_END    (1)


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
        unsigned long  reserved     : 1;  /* bit[1]  : Reserved */
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
                                                         10��3��Ƶ
                                                         11��4��Ƶ */
        unsigned long  FC             : 2;  /* bit[6-7]: TX filter��ֹƵ��ѡ��
                                                         00��5MHz(Ĭ��)WSC&amp;GSM&amp;CDMA
                                                         01��10MHz WDC
                                                         10��Reserved
                                                         11��20MHz LTE */
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
#define ABB_TX_2G_ANA_1_FC_START              (6)
#define ABB_TX_2G_ANA_1_FC_END                (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_2G_ANA_2_UNION
 �ṹ˵��  : tx_2g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x27����ֵ:0x1A�����:8
 �Ĵ���˵��: TX 2G���üĴ����������߿��߼�������reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP1_2G : 2;  /* bit[0-1]: LPF OP1 ����ģʽ����
                                                              bit0��
                                                              0�� �������������
                                                              1�� ����������Ӵ�������5uAƫ�ã�
                                                              bit1��
                                                              0�� miller������������
                                                              1�� miller�������ݱ��������2.5uAƫ�ã�
                                                              LTE:00
                                                              WDC:01
                                                              SC:01
                                                              CDMA&amp;GSM:10 */
        unsigned long  CURRENT_MODE_OP2_2G : 2;  /* bit[2-3]: LPF OP2 ����ģʽ����
                                                              00 �������������
                                                              01 ����������Ӵ�������5uAƫ�ã�
                                                              10 ������ʹ��
                                                              11 ����������ټӴ�������2.5uAƫ�ã�
                                                              LTE:00
                                                              WDC:01
                                                              SC:01
                                                              CDMA&amp;GSM:10 */
        unsigned long  LPF_MODE_CURRENT_2G : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                              �˷ŵ�����   op1   op2
                                                              00��         10u   10u
                                                              01��         5u    5u
                                                              10��         2.5u  5u
                                                              11��         2.5u  2.5u
                                                              LTE:00
                                                              Others:01 */
        unsigned long  reserved            : 1;  /* bit[6]  : TBD */
        unsigned long  TX_MODE_CLK_B3_2G   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_ANA_2_UNION;
#define ABB_TX_2G_ANA_2_CURRENT_MODE_OP1_2G_START  (0)
#define ABB_TX_2G_ANA_2_CURRENT_MODE_OP1_2G_END    (1)
#define ABB_TX_2G_ANA_2_CURRENT_MODE_OP2_2G_START  (2)
#define ABB_TX_2G_ANA_2_CURRENT_MODE_OP2_2G_END    (3)
#define ABB_TX_2G_ANA_2_LPF_MODE_CURRENT_2G_START  (4)
#define ABB_TX_2G_ANA_2_LPF_MODE_CURRENT_2G_END    (5)
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
 �ṹ˵��  : rx_ch0_3g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x29����ֵ:0x0�����:8
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
        unsigned long  reserved     : 1;  /* bit[1]  : Reserved */
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
        unsigned long  TX_MODE_CLK_3G : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ���ƣ�
                                                         000��4G &amp; ET &amp; APT
                                                         001��3G &amp; TDS */
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
                                                         10��3��Ƶ
                                                         11��4��Ƶ */
        unsigned long  FC_3G          : 2;  /* bit[6-7]: TX filter��ֹƵ��ѡ��
                                                         00��5MHz(Ĭ��)WSC&amp;GSM&amp;CDMA
                                                         01��10MHz WDC
                                                         10��Reserved
                                                         11��20MHz LTE */
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
#define ABB_TX_CH0_3G_ANA_1_FC_3G_START           (6)
#define ABB_TX_CH0_3G_ANA_1_FC_3G_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_3G_ANA_2_UNION
 �ṹ˵��  : tx_ch0_3g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x2B����ֵ:0x15�����:8
 �Ĵ���˵��: CH0 TX 3G���üĴ����������߿��߼�������ch0_reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP1_3G : 2;  /* bit[0-1]: LPF OP1 ����ģʽ����
                                                              bit0��
                                                              0�� �������������
                                                              1�� ����������Ӵ�������5uAƫ�ã�
                                                              bit1��
                                                              0�� miller������������
                                                              1�� miller�������ݱ��������2.5uAƫ�ã�
                                                              LTE:00
                                                              WDC:01
                                                              SC:01
                                                              CDMA&amp;GSM:10 */
        unsigned long  CURRENT_MODE_OP2_3G : 2;  /* bit[2-3]: LPF OP2 ����ģʽ����
                                                              00 �������������
                                                              01 ����������Ӵ�������5uAƫ�ã�
                                                              10 ������ʹ��
                                                              11 ����������ټӴ�������2.5uAƫ�ã�
                                                              LTE:00
                                                              WDC:01
                                                              SC:01
                                                              CDMA&amp;GSM:10 */
        unsigned long  LPF_MODE_CURRENT_3G : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                              �˷ŵ�����   op1   op2
                                                              00��         10u   10u
                                                              01��         5u    5u
                                                              10��         2.5u  5u
                                                              11��         2.5u  2.5u
                                                              LTE:00
                                                              Others:01 */
        unsigned long  reserved            : 1;  /* bit[6]  : TBD */
        unsigned long  TX_MODE_CLK_B3_3G   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_3G_ANA_2_UNION;
#define ABB_TX_CH0_3G_ANA_2_CURRENT_MODE_OP1_3G_START  (0)
#define ABB_TX_CH0_3G_ANA_2_CURRENT_MODE_OP1_3G_END    (1)
#define ABB_TX_CH0_3G_ANA_2_CURRENT_MODE_OP2_3G_START  (2)
#define ABB_TX_CH0_3G_ANA_2_CURRENT_MODE_OP2_3G_END    (3)
#define ABB_TX_CH0_3G_ANA_2_LPF_MODE_CURRENT_3G_START  (4)
#define ABB_TX_CH0_3G_ANA_2_LPF_MODE_CURRENT_3G_END    (5)
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
        unsigned long  reserved     : 1;  /* bit[1]  : Reserved */
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
 �ṹ˵��  : tx_ch0_4g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x2E����ֵ:0xCC�����:8
 �Ĵ���˵��: CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_4G : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ���ƣ�
                                                         000��4G &amp; ET &amp; APT
                                                         001��3G &amp; TDS
                                                         010��CA
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
                                                         10��3��Ƶ
                                                         11��4��Ƶ */
        unsigned long  FC_4G          : 2;  /* bit[6-7]: TX filter��ֹƵ��ѡ��
                                                         00��5MHz(Ĭ��)WSC&amp;GSM&amp;CDMA
                                                         01��10MHz WDC
                                                         10��Reserved
                                                         11��20MHz LTE */
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
#define ABB_TX_CH0_4G_ANA_1_FC_4G_START           (6)
#define ABB_TX_CH0_4G_ANA_1_FC_4G_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CH0_4G_ANA_2_UNION
 �ṹ˵��  : tx_ch0_4g_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x2F����ֵ:0x0�����:8
 �Ĵ���˵��: CH0 TX 4G���üĴ����������߿��߼�������ch0_reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP1_4G : 2;  /* bit[0-1]: LPF OP1 ����ģʽ����
                                                              bit0��
                                                              0�� �������������
                                                              1�� ����������Ӵ�������5uAƫ�ã�
                                                              bit1��
                                                              0�� miller������������
                                                              1�� miller�������ݱ��������2.5uAƫ�ã�
                                                              LTE:00
                                                              WDC:01
                                                              SC:01
                                                              CDMA&amp;GSM:10 */
        unsigned long  CURRENT_MODE_OP2_4G : 2;  /* bit[2-3]: LPF OP2 ����ģʽ����
                                                              00 �������������
                                                              01 ����������Ӵ�������5uAƫ�ã�
                                                              10 ������ʹ��
                                                              11 ����������ټӴ�������2.5uAƫ�ã�
                                                              LTE:00
                                                              WDC:01
                                                              SC:01
                                                              CDMA&amp;GSM:10 */
        unsigned long  LPF_MODE_CURRENT_4G : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                              �˷ŵ�����   op1   op2
                                                              00��         10u   10u
                                                              01��         5u    5u
                                                              10��         2.5u  5u
                                                              11��         2.5u  2.5u
                                                              LTE:00
                                                              Others:01 */
        unsigned long  reserved            : 1;  /* bit[6]  : TBD */
        unsigned long  TX_MODE_CLK_B3_4G   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CH0_4G_ANA_2_UNION;
#define ABB_TX_CH0_4G_ANA_2_CURRENT_MODE_OP1_4G_START  (0)
#define ABB_TX_CH0_4G_ANA_2_CURRENT_MODE_OP1_4G_END    (1)
#define ABB_TX_CH0_4G_ANA_2_CURRENT_MODE_OP2_4G_START  (2)
#define ABB_TX_CH0_4G_ANA_2_CURRENT_MODE_OP2_4G_END    (3)
#define ABB_TX_CH0_4G_ANA_2_LPF_MODE_CURRENT_4G_START  (4)
#define ABB_TX_CH0_4G_ANA_2_LPF_MODE_CURRENT_4G_END    (5)
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
        unsigned long  reserved      : 1;  /* bit[1]  : Reserved */
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
 �ṹ˵��  : tx_tds_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x32����ֵ:0x5D�����:8
 �Ĵ���˵��: TX TDS���üĴ����������߿��߼�������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_MODE_CLK_TDS : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ���ƣ�
                                                          000��4G
                                                          001��3G &amp; TDS
                                                          010��CA
                                                          011��2G(Ĭ��)
                                                          1xx��CDMA */
        unsigned long  TX_Q_PD_A_TDS   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                          0��Power On
                                                          1��Power Down(Ĭ��)
                                                          (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_TDS   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                          0��Power On
                                                          1��Power Down(Ĭ��)
                                                          (!TX_I_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_TDS : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                          00��1��Ƶ
                                                          01��2��Ƶ(Ĭ��)
                                                          10��3��Ƶ
                                                          11��4��Ƶ */
        unsigned long  FC_TDS          : 2;  /* bit[6-7]: TX filter��ֹƵ��ѡ��
                                                          00��5MHz(Ĭ��)WSC&amp;GSM&amp;CDMA
                                                          01��10MHz WDC
                                                          10��Reserved
                                                          11��20MHz LTE */
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
#define ABB_TX_TDS_ANA_1_FC_TDS_START           (6)
#define ABB_TX_TDS_ANA_1_FC_TDS_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_ANA_2_UNION
 �ṹ˵��  : tx_tds_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x33����ֵ:0x15�����:8
 �Ĵ���˵��: TX TDS���üĴ����������߿��߼�������reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP1_TDS : 2;  /* bit[0-1]: LPF OP1 ����ģʽ����
                                                               bit0��
                                                               0�� �������������
                                                               1�� ����������Ӵ�������5uAƫ�ã�
                                                               bit1��
                                                               0�� miller������������
                                                               1�� miller�������ݱ��������2.5uAƫ�ã�
                                                               LTE:00
                                                               WDC:01
                                                               SC:01
                                                               CDMA&amp;GSM:10 */
        unsigned long  CURRENT_MODE_OP2_TDS : 2;  /* bit[2-3]: LPF OP2 ����ģʽ����
                                                               00 �������������
                                                               01 ����������Ӵ�������5uAƫ�ã�
                                                               10 ������ʹ��
                                                               11 ����������ټӴ�������2.5uAƫ�ã�
                                                               LTE:00
                                                               WDC:01
                                                               SC:01
                                                               CDMA&amp;GSM:10 */
        unsigned long  LPF_MODE_TDS         : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                               �˷ŵ�����   op1   op2
                                                               00��         10u   10u
                                                               01��         5u    5u
                                                               10��         2.5u  5u
                                                               11��         2.5u  2.5u
                                                               LTE:00
                                                               Others:01 */
        unsigned long  reserved             : 1;  /* bit[6]  : TBD */
        unsigned long  TX_MODE_CLK_B3_TDS   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_ANA_2_UNION;
#define ABB_TX_TDS_ANA_2_CURRENT_MODE_OP1_TDS_START  (0)
#define ABB_TX_TDS_ANA_2_CURRENT_MODE_OP1_TDS_END    (1)
#define ABB_TX_TDS_ANA_2_CURRENT_MODE_OP2_TDS_START  (2)
#define ABB_TX_TDS_ANA_2_CURRENT_MODE_OP2_TDS_END    (3)
#define ABB_TX_TDS_ANA_2_LPF_MODE_TDS_START          (4)
#define ABB_TX_TDS_ANA_2_LPF_MODE_TDS_END            (5)
#define ABB_TX_TDS_ANA_2_TX_MODE_CLK_B3_TDS_START    (7)
#define ABB_TX_TDS_ANA_2_TX_MODE_CLK_B3_TDS_END      (7)


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
        unsigned long  reserved       : 1;  /* bit[1]  : Reserved */
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
        unsigned long  TX_MODE_CLK_IDLE : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ���ƣ�
                                                           000��4G &amp; ET &amp; APT
                                                           001��3G &amp; TDS
                                                           010��CA
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
                                                           10��3��Ƶ
                                                           11��4��Ƶ */
        unsigned long  FC_IDLE          : 2;  /* bit[6-7]: TX filter��ֹƵ��ѡ��
                                                           00��5MHz(Ĭ��)WSC&amp;GSM&amp;CDMA
                                                           01��10MHz WDC
                                                           10��Reserved
                                                           11��20MHz LTE */
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
#define ABB_TX_IDLE_ANA_1_FC_IDLE_START           (6)
#define ABB_TX_IDLE_ANA_1_FC_IDLE_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_ANA_2_UNION
 �ṹ˵��  : tx_idle_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x3F����ֵ:0x1A�����:8
 �Ĵ���˵��: TX IDLE���üĴ����������߿��߼�������reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP1_IDLE : 2;  /* bit[0-1]: LPF OP1 ����ģʽ����
                                                                bit0��
                                                                0�� �������������
                                                                1�� ����������Ӵ�������5uAƫ�ã�
                                                                bit1��
                                                                0�� miller������������
                                                                1�� miller�������ݱ��������2.5uAƫ�ã�
                                                                LTE:00
                                                                WDC:01
                                                                SC:01
                                                                CDMA&amp;GSM:10 */
        unsigned long  CURRENT_MODE_OP2_IDLE : 2;  /* bit[2-3]: LPF OP2 ����ģʽ����
                                                                00 �������������
                                                                01 ����������Ӵ�������5uAƫ�ã�
                                                                10 ������ʹ��
                                                                11 ����������ټӴ�������2.5uAƫ�ã�
                                                                LTE:00
                                                                WDC:01
                                                                SC:01
                                                                CDMA&amp;GSM:10 */
        unsigned long  LPF_MODE_CURRENT_IDLE : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                                �˷ŵ�����   op1   op2
                                                                00��         10u   10u
                                                                01��         5u    5u
                                                                10��         2.5u  5u
                                                                11��         2.5u  2.5u
                                                                LTE:00
                                                                Others:01 */
        unsigned long  reserved              : 1;  /* bit[6]  : TBD */
        unsigned long  TX_MODE_CLK_B3_IDLE   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_ANA_2_UNION;
#define ABB_TX_IDLE_ANA_2_CURRENT_MODE_OP1_IDLE_START  (0)
#define ABB_TX_IDLE_ANA_2_CURRENT_MODE_OP1_IDLE_END    (1)
#define ABB_TX_IDLE_ANA_2_CURRENT_MODE_OP2_IDLE_START  (2)
#define ABB_TX_IDLE_ANA_2_CURRENT_MODE_OP2_IDLE_END    (3)
#define ABB_TX_IDLE_ANA_2_LPF_MODE_CURRENT_IDLE_START  (4)
#define ABB_TX_IDLE_ANA_2_LPF_MODE_CURRENT_IDLE_END    (5)
#define ABB_TX_IDLE_ANA_2_TX_MODE_CLK_B3_IDLE_START    (7)
#define ABB_TX_IDLE_ANA_2_TX_MODE_CLK_B3_IDLE_END      (7)


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
                                                           11��ȫ����ֵ */
        unsigned long  ch0_cfr_fir_sel  : 1;  /* bit[2]  : CFR�˲���ѡ��
                                                           0��bypass�˲���
                                                           1����bypass�˲��� */
        unsigned long  reserved         : 1;  /* bit[3]  : Reserved */
        unsigned long  ch0_cfr_fir_fac  : 4;  /* bit[4-7]: CFR�������� */
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
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
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
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
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
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
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
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
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
        unsigned long  reserved               : 6;  /* bit[2-7]: Reserved */
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
        unsigned long  reserved       : 4;  /* bit[0-3]: Reserved */
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
        unsigned long  reserved       : 4;  /* bit[0-3]: Reserved */
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
        unsigned long  reserved       : 4;  /* bit[0-3]: Reserved */
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
        unsigned long  reserved       : 4;  /* bit[0-3]: Reserved */
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
        unsigned long  reserved          : 1;  /* bit[7]  : Reserved */
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
        unsigned long  CH0_RXC_Q_PD   : 1;  /* bit[0]  : RXC_Q ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXA_Q_PD)|(CH0_RXA_EN &amp; ch0_test_mode[5]) =1ʱ����������ر�
                                                         ComstarV511_Reserved */
        unsigned long  CH0_RXC_I_PD   : 1;  /* bit[1]  : RXC_I ADC Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��)
                                                         (!RXA_I_PD)|(CH0_RXA_EN &amp; ch0_test_mode[5]) =1ʱ����������ر�
                                                         ComstarV511_Reserved */
        unsigned long  CH0_PLL624_PD  : 1;  /* bit[2]  : GPLL Power Down����
                                                         0��Power On
                                                         1��Power Down(Ĭ��) */
        unsigned long  CH0_PLL6144_PD : 1;  /* bit[3]  : WPLL Power Down����
                                                         0��Power On(Ĭ��)
                                                         1��Power Down */
        unsigned long  reserved       : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR02_UNION;
#define ABB_CH0_REG_ANALOG_WR02_CH0_RXC_Q_PD_START    (0)
#define ABB_CH0_REG_ANALOG_WR02_CH0_RXC_Q_PD_END      (0)
#define ABB_CH0_REG_ANALOG_WR02_CH0_RXC_I_PD_START    (1)
#define ABB_CH0_REG_ANALOG_WR02_CH0_RXC_I_PD_END      (1)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL624_PD_START   (2)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL624_PD_END     (2)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL6144_PD_START  (3)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL6144_PD_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR03_UNION
 �ṹ˵��  : ch0_reg_analog_wr03 �Ĵ����ṹ���塣��ַƫ����:0xD1����ֵ:0x40�����:8
 �Ĵ���˵��: ��ģ�ӿ�ʱ�ӿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0        : 2;  /* bit[0-1]: Reserved */
        unsigned long  CH0_104M_52M_SEL  : 1;  /* bit[2]  : 52M��104M���ѡ��
                                                            0��104M
                                                            1��52M */
        unsigned long  CH0_TX_CLKD_CTRL  : 1;  /* bit[3]  : TX ����ʱ����ѡ��
                                                            0������(Ĭ��)
                                                            1������ */
        unsigned long  CH0_CLK_61D44M_PD : 1;  /* bit[4]  : CLK_61D44M Power Down����
                                                            0��Power On(Ĭ��)
                                                            1��Power Down */
        unsigned long  CH0_CLK_52M_PD    : 1;  /* bit[5]  : CLK_52M Power Down����
                                                            0��Power On(Ĭ��)
                                                            1��Power Down */
        unsigned long  CH0_CLK_245M_PD   : 1;  /* bit[6]  : CLK_245M Power Down����
                                                            0��Power On
                                                            1��Power Down(Ĭ��) */
        unsigned long  reserved_1        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR03_UNION;
#define ABB_CH0_REG_ANALOG_WR03_CH0_104M_52M_SEL_START   (2)
#define ABB_CH0_REG_ANALOG_WR03_CH0_104M_52M_SEL_END     (2)
#define ABB_CH0_REG_ANALOG_WR03_CH0_TX_CLKD_CTRL_START   (3)
#define ABB_CH0_REG_ANALOG_WR03_CH0_TX_CLKD_CTRL_END     (3)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_61D44M_PD_START  (4)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_61D44M_PD_END    (4)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_52M_PD_START     (5)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_52M_PD_END       (5)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_245M_PD_START    (6)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_245M_PD_END      (6)


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
        unsigned long  CH0_EN_CAL       : 1;  /* bit[0]  : Calibration enable(Ĭ��Ϊ0)
                                                           ����������Calibration���� */
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
#define ABB_CH0_REG_ANALOG_WR04_CH0_EN_CAL_START        (0)
#define ABB_CH0_REG_ANALOG_WR04_CH0_EN_CAL_END          (0)
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
        unsigned long  CH0_RX_TUNE1 : 7;  /* bit[0-6]: ADC��һ������������tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR05_UNION;
#define ABB_CH0_REG_ANALOG_WR05_CH0_RX_TUNE1_START  (0)
#define ABB_CH0_REG_ANALOG_WR05_CH0_RX_TUNE1_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR06_UNION
 �ṹ˵��  : ch0_reg_analog_wr06 �Ĵ����ṹ���塣��ַƫ����:0xD4����ֵ:0x40�����:8
 �Ĵ���˵��: ADC�ڶ�������������tuning�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RX_TUNE2 : 7;  /* bit[0-6]: ADC�ڶ�������������tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR06_UNION;
#define ABB_CH0_REG_ANALOG_WR06_CH0_RX_TUNE2_START  (0)
#define ABB_CH0_REG_ANALOG_WR06_CH0_RX_TUNE2_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR07_UNION
 �ṹ˵��  : ch0_reg_analog_wr07 �Ĵ����ṹ���塣��ַƫ����:0xD5����ֵ:0x40�����:8
 �Ĵ���˵��: ADC����������������tuning�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RX_TUNE3 : 7;  /* bit[0-6]: ADC����������������tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR07_UNION;
#define ABB_CH0_REG_ANALOG_WR07_CH0_RX_TUNE3_START  (0)
#define ABB_CH0_REG_ANALOG_WR07_CH0_RX_TUNE3_END    (6)


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
        unsigned long  CH0_TX_TUNE1 : 7;  /* bit[0-6]: TX_TUNE1�����ź� */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR08_UNION;
#define ABB_CH0_REG_ANALOG_WR08_CH0_TX_TUNE1_START  (0)
#define ABB_CH0_REG_ANALOG_WR08_CH0_TX_TUNE1_END    (6)


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
        unsigned long  CH0_TX_TUNE2 : 7;  /* bit[0-6]: TX_TUNE2�����ź� */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR09_UNION;
#define ABB_CH0_REG_ANALOG_WR09_CH0_TX_TUNE2_START  (0)
#define ABB_CH0_REG_ANALOG_WR09_CH0_TX_TUNE2_END    (6)


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
 �ṹ˵��  : ch0_reg_analog_wr38 �Ĵ����ṹ���塣��ַƫ����:0xD9����ֵ:0x00�����:8
 �Ĵ���˵��: ʱ�ӷ��ؿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_RX_ADC_QUANTIZER_CAL_CTRL : 1;  /* bit[0]  : ADC������У׼ʹ�ܣ�
                                                                        0��Not Cal(Ĭ��)
                                                                        1��Cal */
        unsigned long  CH0_RX_LDO_LOAD               : 1;  /* bit[1]  : Rx CK LDO��Դ���ص���
                                                                        0��������(Ĭ��)
                                                                        1������ */
        unsigned long  CH0_RX_LDO_VDD                : 3;  /* bit[2-4]: Rx CK LDO��Դ��ѹ
                                                                        000��0.9V(Ĭ��) */
        unsigned long  CH0_RX_CLK2D_CTRL             : 1;  /* bit[5]  : ADC�����ؿ��ƣ�
                                                                        0������(Ĭ��)
                                                                        1������ */
        unsigned long  CH0_RX_SYN2D_CTRL             : 1;  /* bit[6]  : ADC SYNC�źŲ����ؿ��ƣ�
                                                                        0������(Ĭ��)
                                                                        1������ */
        unsigned long  CH0_RX_ADC_LDO_CTRL           : 1;  /* bit[7]  : RX_ADC LDOʹ�ܿ���
                                                                        0��Power Down(Ĭ��)
                                                                        1��Power On */
        unsigned long  reserved_butt                 : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR38_UNION;
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_ADC_QUANTIZER_CAL_CTRL_START  (0)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_ADC_QUANTIZER_CAL_CTRL_END    (0)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_LDO_LOAD_START                (1)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_LDO_LOAD_END                  (1)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_LDO_VDD_START                 (2)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_LDO_VDD_END                   (4)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_CLK2D_CTRL_START              (5)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_CLK2D_CTRL_END                (5)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_SYN2D_CTRL_START              (6)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_SYN2D_CTRL_END                (6)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_ADC_LDO_CTRL_START            (7)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_ADC_LDO_CTRL_END              (7)


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
        unsigned long  CH0_DUM_EN_Q : 1;  /* bit[0]  : TX Q channel  dummy logic control signal
                                                       1��enable(Ĭ��)
                                                       0��disable */
        unsigned long  CH0_DUM_EN_I : 1;  /* bit[1]  : TX I channel  dummy logic control signal
                                                       1��enable(Ĭ��)
                                                       0��disable */
        unsigned long  reserved     : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH0_DEM_MOD  : 1;  /* bit[7]  : RX DEM Mode Selection,bit 2,��ch0_reg_analog_wr00��bit3��bit0��ϳ�3bit��ʵ������9����ϣ�
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
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_Q_START  (0)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_Q_END    (0)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_I_START  (1)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_I_END    (1)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DEM_MOD_START   (7)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DEM_MOD_END     (7)


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
 �ṹ˵��  : ch0_reg_debug_ana0 �Ĵ����ṹ���塣��ַƫ����:0xE0����ֵ:0x72�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_CLK_REF_SEL  : 1;  /* bit[0]  : PLL�Ĳο�ʱ��ѡ��
                                                           1��CLKIN_SYSTEM��ΪPLL�Ĳο�ʱ��
                                                           0��TCXO Buffer�����ΪPLL�ο�ʱ�� */
        unsigned long  CH0_PLL_OCLK_SEL : 3;  /* bit[1-3]: ����ʱ��ѡ��
                                                           001��ѡ��������PLL��ʱ����Ϊ����ʱ��
                                                           010��ѡ��������CLKIN_SYSTEM�����ʱ����Ϊ����ʱ��
                                                           100��ѡ��������TCXO_IN��ʱ����Ϊ����ʱ�� */
        unsigned long  CH0_PLL_PFD_CTRL : 2;  /* bit[4-5]: PLL��Ƶ����������
                                                           x0����Ƶ������һֱ���Up�ź�
                                                           01����Ƶ������һֱ���Down�ź�
                                                           11����Ƶ�������������� */
        unsigned long  CH0_GVCO_CR      : 2;  /* bit[6-7]: GPLL VCO Current����
                                                           00��X1.2
                                                           01��X1.1(Ĭ��)
                                                           10��X1.1
                                                           11��X1.0 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA0_UNION;
#define ABB_CH0_REG_DEBUG_ANA0_CH0_CLK_REF_SEL_START   (0)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_CLK_REF_SEL_END     (0)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_OCLK_SEL_START  (1)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_OCLK_SEL_END    (3)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_PFD_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_PFD_CTRL_END    (5)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_GVCO_CR_START       (6)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_GVCO_CR_END         (7)


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
        unsigned long  CH0_GPLL_LK_CTRL : 2;  /* bit[0-1]: GPLL����Cycle����
                                                           00��4
                                                           01��8
                                                           10��16(Ĭ��)
                                                           11��32 */
        unsigned long  CH0_WPLL_LK_CTRL : 2;  /* bit[2-3]: WPLL����Cycle����
                                                           00��4
                                                           01��8
                                                           10��16(Ĭ��)
                                                           11��32 */
        unsigned long  CH0_GPLL_LK_EN   : 1;  /* bit[4]  : GPLL�������ʹ��
                                                           0�����������ź�
                                                           1���������ź� */
        unsigned long  CH0_WPLL_LK_EN   : 1;  /* bit[5]  : WPLL�������ʹ��
                                                           0�����������ź�
                                                           1���������ź� */
        unsigned long  CH0_WVCO_CR      : 2;  /* bit[6-7]: WPLL VCO Current����
                                                           00��X1.2
                                                           01��X1.1(Ĭ��)
                                                           10��X1.1
                                                           11��X1.0 */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA1_UNION;
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GPLL_LK_CTRL_START  (0)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GPLL_LK_CTRL_END    (1)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WPLL_LK_CTRL_START  (2)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WPLL_LK_CTRL_END    (3)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GPLL_LK_EN_START    (4)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GPLL_LK_EN_END      (4)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WPLL_LK_EN_START    (5)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WPLL_LK_EN_END      (5)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WVCO_CR_START       (6)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WVCO_CR_END         (7)


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
        unsigned long  CH0_PLL_CP_PD : 2;  /* bit[0-1]: PLL CP PowerDown���ƣ�������
                                                        00����������
                                                        01��PowerDown WPLL CP
                                                        10��PowerDown GPLL CP
                                                        11��PowerDown WPLL CP��GPLL CP */
        unsigned long  reserved      : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH0_CLKN_EN   : 1;  /* bit[7]  : ����ʱ�ӿ���
                                                        1������ʱ�Ӵ�
                                                        0������ʱ�ӹر� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA2_UNION;
#define ABB_CH0_REG_DEBUG_ANA2_CH0_PLL_CP_PD_START  (0)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_PLL_CP_PD_END    (1)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_CLKN_EN_START    (7)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_CLKN_EN_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA3_UNION
 �ṹ˵��  : ch0_reg_debug_ana3 �Ĵ����ṹ���塣��ַƫ����:0xE3����ֵ:0x70�����:8
 �Ĵ���˵��: PLL���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved         : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_GPLL_CP_CTRL : 4;  /* bit[4-7]: GPLL��ɱõ�������(����Ч)
                                                           Basic��0.2*Icp
                                                           Bit0�� 0.1*Icp
                                                           Bit1�� 0.2*Icp
                                                           Bit2�� 0.4*Icp
                                                           Bit3�� 0.8*Icp */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA3_UNION;
#define ABB_CH0_REG_DEBUG_ANA3_CH0_GPLL_CP_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA3_CH0_GPLL_CP_CTRL_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA4_UNION
 �ṹ˵��  : ch0_reg_debug_ana4 �Ĵ����ṹ���塣��ַƫ����:0xE4����ֵ:0x70�����:8
 �Ĵ���˵��: PLL���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved         : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_WPLL_CP_CTRL : 4;  /* bit[4-7]: WPLL��ɱõ�������(����Ч)
                                                           Basic��0.2*Icp
                                                           Bit0�� 0.1*Icp
                                                           Bit1�� 0.2*Icp
                                                           Bit2�� 0.4*Icp
                                                           Bit3�� 0.8*Icp */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA4_UNION;
#define ABB_CH0_REG_DEBUG_ANA4_CH0_WPLL_CP_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA4_CH0_WPLL_CP_CTRL_END    (7)


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
        unsigned long  reserved       : 7;  /* bit[0-6]: Reserved */
        unsigned long  CH0_ABB_REF_FS : 1;  /* bit[7]  : ABB_REF_Fast_UP����
                                                         0���ر�(Ĭ��)
                                                         1������ */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA5_UNION;
#define ABB_CH0_REG_DEBUG_ANA5_CH0_ABB_REF_FS_START  (7)
#define ABB_CH0_REG_DEBUG_ANA5_CH0_ABB_REF_FS_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA6_UNION
 �ṹ˵��  : ch0_reg_debug_ana6 �Ĵ����ṹ���塣��ַƫ����:0xE6����ֵ:0x6D�����:8
 �Ĵ���˵��: Bandgap��TCXO���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_GLLFREQ_SEL  : 2;  /* bit[0-1]: GPLL����ʱ��Ƶ��ѡ��
                                                           00��26M
                                                           01��19.2MM(Ĭ��)
                                                           10��52M
                                                           11��38.4M */
        unsigned long  CH0_WPLLFREQ_SEL : 2;  /* bit[2-3]: WPLL����ʱ��Ƶ��ѡ��
                                                           00��76.8M
                                                           01��38.4M
                                                           10��38.4M
                                                           11��19.2M(Ĭ��) */
        unsigned long  CH0_TCXO_DRV     : 2;  /* bit[4-5]: TCXO BUFFER��������
                                                           00��1x
                                                           01��2x
                                                           10��3x(Ĭ��)
                                                           11��4x */
        unsigned long  CH0_CLKIN_PD     : 1;  /* bit[6]  : TEST CLK INPUT�µ����
                                                           0������
                                                           1���ر� */
        unsigned long  reserved         : 1;  /* bit[7]  : reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA6_UNION;
#define ABB_CH0_REG_DEBUG_ANA6_CH0_GLLFREQ_SEL_START   (0)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_GLLFREQ_SEL_END     (1)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_WPLLFREQ_SEL_START  (2)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_WPLLFREQ_SEL_END    (3)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_TCXO_DRV_START      (4)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_TCXO_DRV_END        (5)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_CLKIN_PD_START      (6)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_CLKIN_PD_END        (6)


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
        unsigned long  CH0_DRVBUF_CT : 3;  /* bit[0-2]: L/W/G ����ADC ���Buffer�������ڿ���
                                                        000��5u
                                                        001��2u
                                                        010��3u
                                                        011��4u
                                                        100��6u
                                                        101��7u
                                                        110��8u
                                                        111��9u */
        unsigned long  reserved      : 5;  /* bit[3-7]: Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA7_UNION;
#define ABB_CH0_REG_DEBUG_ANA7_CH0_DRVBUF_CT_START  (0)
#define ABB_CH0_REG_DEBUG_ANA7_CH0_DRVBUF_CT_END    (2)


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
        unsigned long  CH0_DAC_DUM_B0   : 1;  /* bit[0]  : RX����sub_DAC Dummy��Ԫ���ƣ���һλ
                                                           0������
                                                           1���ر� */
        unsigned long  CH0_L_PUP_MODE   : 1;  /* bit[1]  : LTE ADCģ������ģʽѡ��
                                                           0���Զ�ģʽ
                                                           1�����üĴ���ģʽ */
        unsigned long  reserved_0       : 1;  /* bit[2]  : Reserved */
        unsigned long  CH0_L_DEM_PD     : 1;  /* bit[3]  : LTE ADC DEM���ܹر��ź�
                                                           0��DEMʹ��
                                                           1��DEM��ʹ�� */
        unsigned long  CH0_L_TUNING_SEL : 1;  /* bit[4]  : LTE ADCģ��Tuning���ѡ��
                                                           0��ѡ��Tuningģ��������ΪLTE ADC��Tuning��
                                                           1��ѡ��Ĵ����������ΪLTE ADC��Tuning�� */
        unsigned long  reserved_1       : 3;  /* bit[5-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA9_UNION;
#define ABB_CH0_REG_DEBUG_ANA9_CH0_DAC_DUM_B0_START    (0)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_DAC_DUM_B0_END      (0)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_PUP_MODE_START    (1)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_PUP_MODE_END      (1)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_DEM_PD_START      (3)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_DEM_PD_END        (3)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_TUNING_SEL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_TUNING_SEL_END    (4)


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
        unsigned long  CH0_DAC_DUM_B2B1 : 2;  /* bit[0-1]: RX����sub_DAC Dummy��Ԫ���ƣ�����λ
                                                           0������
                                                           1���ر� */
        unsigned long  CH0_L_PUP_CTRL0  : 1;  /* bit[2]  : LTE ADC�е�һ�����������ݸ�λ����
                                                           0������λ
                                                           1����λ */
        unsigned long  CH0_L_PUP_CTRL1  : 1;  /* bit[3]  : LTE ADC�еڶ������������ݸ�λ����
                                                           0������λ
                                                           1����λ */
        unsigned long  CH0_L_PUP_CTRL2  : 1;  /* bit[4]  : LTE ADC�е��������������ݸ�λ����
                                                           0������λ
                                                           1����λ */
        unsigned long  CH0_L_PUP_CTRL3  : 1;  /* bit[5]  : LTE ADC��CKGENģ��Powerup����
                                                           0��Powerdown
                                                           1��Powerup */
        unsigned long  CH0_L_PUP_CTRL4  : 1;  /* bit[6]  : LTE ADC��OPģ��Powerup����
                                                           0��Powerdown
                                                           1��Powerup */
        unsigned long  CH0_L_PUP_CTRL5  : 1;  /* bit[7]  : LTE ADC��DACģ��Powerup����
                                                           0��Powerdown
                                                           1��Powerup */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA10_UNION;
#define ABB_CH0_REG_DEBUG_ANA10_CH0_DAC_DUM_B2B1_START  (0)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_DAC_DUM_B2B1_END    (1)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL0_START   (2)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL0_END     (2)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL1_START   (3)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL1_END     (3)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL2_START   (4)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL2_END     (4)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL3_START   (5)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL3_END     (5)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL4_START   (6)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL4_END     (6)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL5_START   (7)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL5_END     (7)


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
        unsigned long  reserved       : 6;  /* bit[0-5]: Reserved */
        unsigned long  CH0_BG_OPEN_EN : 1;  /* bit[6]  : 0�� Reference turn on
                                                         1�� BG_OPEN_EN is not effective */
        unsigned long  CH0_BG_DOWN_PD : 1;  /* bit[7]  : 0�� Reference turn off
                                                         1�� BG_OPEN_EN is effective */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA11_UNION;
#define ABB_CH0_REG_DEBUG_ANA11_CH0_BG_OPEN_EN_START  (6)
#define ABB_CH0_REG_DEBUG_ANA11_CH0_BG_OPEN_EN_END    (6)
#define ABB_CH0_REG_DEBUG_ANA11_CH0_BG_DOWN_PD_START  (7)
#define ABB_CH0_REG_DEBUG_ANA11_CH0_BG_DOWN_PD_END    (7)


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
        unsigned long  CH0_L_OL_CT : 3;  /* bit[0-2]: LTE Overloadģ������
                                                      00��16����������������С��
                                                      01��8����������������С��
                                                      10��4����������������С��
                                                      11���ر�Overload��� */
        unsigned long  reserved    : 3;  /* bit[3-5]: Reserved */
        unsigned long  CH0_L_CK_CT : 2;  /* bit[6-7]: LTE SYNCʱ�����
                                                      00��No delay
                                                      01��250ps delay
                                                      10��500ps delay
                                                      11��1000ps delay */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA14_UNION;
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_OL_CT_START  (0)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_OL_CT_END    (2)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_CK_CT_START  (6)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_CK_CT_END    (7)


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
        unsigned long  CH0_PDM_CTRL : 1;  /* bit[6]  : RX���PDM�������
                                                       0��adder encoder
                                                       1��de-bubble encoder */
        unsigned long  reserved_1   : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA16_UNION;
#define ABB_CH0_REG_DEBUG_ANA16_CH0_PDM_CTRL_START  (6)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_PDM_CTRL_END    (6)


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
        unsigned long  reserved          : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_PLL1_CLK_TEST : 2;  /* bit[4-5]: PLLʱ�Ӳ���PAD�ź�ѡ��
                                                            00��ʱ�Ӳ���PAD����
                                                            01��WPLL���ʱ�ӵ�PAD
                                                            10��GPLL���ʱ�ӵ�PAD */
        unsigned long  CH0_PLL1_ANA_TEST : 2;  /* bit[6-7]: PLL���Ƶ�ѹ����PAD�ź�ѡ��
                                                            00�����Ƶ�ѹ����PAD����
                                                            01��WPLL������Ƶ�ѹ��PAD
                                                            10��GPLL������Ƶ�ѹ��PAD */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA17_UNION;
#define ABB_CH0_REG_DEBUG_ANA17_CH0_PLL1_CLK_TEST_START  (4)
#define ABB_CH0_REG_DEBUG_ANA17_CH0_PLL1_CLK_TEST_END    (5)
#define ABB_CH0_REG_DEBUG_ANA17_CH0_PLL1_ANA_TEST_START  (6)
#define ABB_CH0_REG_DEBUG_ANA17_CH0_PLL1_ANA_TEST_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA19_UNION
 �ṹ˵��  : ch0_reg_debug_ana19 �Ĵ����ṹ���塣��ַƫ����:0xF3����ֵ:0x30�����:8
 �Ĵ���˵��: ʱ��ʹ�ܿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CH0_CLK_PADF_SEL : 2;  /* bit[0-1]: ���Թܽ����ʱ��Ƶ�ʿ���
                                                           00��������ʱ��
                                                           01��WPLL�������
                                                           10��GPLL�������
                                                           11��WPLL��GPLL������� */
        unsigned long  reserved_0       : 2;  /* bit[2-3]: Reserved */
        unsigned long  CH0_DAC_CLK_EN   : 1;  /* bit[4]  : PLLģ��307.2MHzʱ��ʹ���ź�
                                                           0��ʱ�ӹر�
                                                           1��ʱ��ʹ�� */
        unsigned long  CH0_ADC_CLK_EN   : 1;  /* bit[5]  : PLLģ��307.2MHzʱ��ʹ���ź�
                                                           0��ʱ�ӹر�
                                                           1��ʱ��ʹ�� */
        unsigned long  reserved_1       : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA19_UNION;
#define ABB_CH0_REG_DEBUG_ANA19_CH0_CLK_PADF_SEL_START  (0)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_CLK_PADF_SEL_END    (1)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_DAC_CLK_EN_START    (4)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_DAC_CLK_EN_END      (4)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_ADC_CLK_EN_START    (5)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_ADC_CLK_EN_END      (5)


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
        unsigned long  CH0_TCXO_BUF_SEL      : 1;  /* bit[0]  : TCXO Bufferѡ��
                                                                0: ����TCXO Buffer
                                                                1: ˫��TCXO Buffer */
        unsigned long  CH0_TCXO_OUT_CTRL     : 1;  /* bit[1]  : CH0�͸�CH1��TCXOʱ�ӿ��ؿ���
                                                                0���ر�
                                                                1���� */
        unsigned long  CH0_TCXO_SEL          : 1;  /* bit[2]  : PLLʱ�ӻ�׼ѡ���ź�
                                                                0: CH0 ��TCXOʱ��
                                                                1: CH1 ��TCXOʱ�� */
        unsigned long  reserved              : 2;  /* bit[3-4]: Reserved */
        unsigned long  CH0_ADC_ST3_CAP_MULTI : 2;  /* bit[5-6]: ADC���������ݱ���ϵ��
                                                                00��X1(Ĭ��)
                                                                01��X1.5
                                                                10��X1.25
                                                                11��X1.125 */
        unsigned long  CH0_CAP_SEL           : 1;  /* bit[7]  : Tuning��·����ѡ��
                                                                0�������
                                                                1��С���� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA20_UNION;
#define ABB_CH0_REG_DEBUG_ANA20_CH0_TCXO_BUF_SEL_START       (0)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_TCXO_BUF_SEL_END         (0)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_TCXO_OUT_CTRL_START      (1)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_TCXO_OUT_CTRL_END        (1)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_TCXO_SEL_START           (2)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_TCXO_SEL_END             (2)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_ADC_ST3_CAP_MULTI_START  (5)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_ADC_ST3_CAP_MULTI_END    (6)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP_SEL_START            (7)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP_SEL_END              (7)


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
        unsigned long  sine_enable : 1;  /* bit[0]  : ���Ҳ�����ʹ��
                                                      0��������
                                                      1������ */
        unsigned long  sine_sw_req : 1;  /* bit[1]  : ���Ҳ�����ͨ���л�
                                                      0��CH1
                                                      1��CH0 */
        unsigned long  sine_amp    : 2;  /* bit[2-3]: ���Ҳ����ͷ��ȿ���
                                                      00��������
                                                      01��3/4����
                                                      10��1/2����
                                                      11��1/4���� */
        unsigned long  sine_freq   : 4;  /* bit[4-7]: ���Ҳ�����Ƶ�ʿ��ƣ���λ(freq of tx_hb_clk)/32�����䷶ΧΪ1~f */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SINE_GENERATE_UNION;
#define ABB_SINE_GENERATE_sine_enable_START  (0)
#define ABB_SINE_GENERATE_sine_enable_END    (0)
#define ABB_SINE_GENERATE_sine_sw_req_START  (1)
#define ABB_SINE_GENERATE_sine_sw_req_END    (1)
#define ABB_SINE_GENERATE_sine_amp_START     (2)
#define ABB_SINE_GENERATE_sine_amp_END       (3)
#define ABB_SINE_GENERATE_sine_freq_START    (4)
#define ABB_SINE_GENERATE_sine_freq_END      (7)


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
        unsigned long  TXLPF_CT_2G     : 3;  /* bit[0-2]: LPF OP1 ����ģʽ����
                                                          000��5u
                                                          001��4u
                                                          010��3u
                                                          011��2u
                                                          100��9u
                                                          101��7u
                                                          110��6u
                                                          111��5u */
        unsigned long  DUM_EN_Q_2G     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  DUM_EN_I_2G     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  reserved        : 2;  /* bit[5-6]: Reserved */
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
        unsigned long  reserved   : 2;  /* bit[6-7]: Reserved */
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
        unsigned long  reserved   : 2;  /* bit[6-7]: Reserved */
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
        unsigned long  reserved    : 3;  /* bit[5-7]: Comstarv511_Reserved */
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
        unsigned long  TXLPF_CT_3G     : 3;  /* bit[0-2]: LPF OP1 ����ģʽ����
                                                          000��5u
                                                          001��4u
                                                          010��3u
                                                          011��2u
                                                          100��9u
                                                          101��7u
                                                          110��6u
                                                          111��5u */
        unsigned long  DUM_EN_Q_3G     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  DUM_EN_I_3G     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  reserved        : 2;  /* bit[5-6]: Reserved */
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
        unsigned long  reserved   : 2;  /* bit[6-7]: Reserved */
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
        unsigned long  reserved   : 2;  /* bit[6-7]: Reserved */
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
        unsigned long  reserved    : 3;  /* bit[5-7]: Comstarv511_Reserved */
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
        unsigned long  TXLPF_CT_4G     : 3;  /* bit[0-2]: LPF OP1 ����ģʽ����
                                                          000��5u
                                                          001��4u
                                                          010��3u
                                                          011��2u
                                                          100��9u
                                                          101��7u
                                                          110��6u
                                                          111��5u */
        unsigned long  DUM_EN_Q_4G     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  DUM_EN_I_4G     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                          1��enable(Ĭ��)
                                                          0��disable */
        unsigned long  reserved        : 2;  /* bit[5-6]: Reserved */
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
        unsigned long  reserved   : 2;  /* bit[6-7]: Reserved */
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
        unsigned long  reserved   : 2;  /* bit[6-7]: Reserved */
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
        unsigned long  reserved    : 3;  /* bit[5-7]: Comstarv511_Reserved */
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
        unsigned long  TXLPF_CT_TDS     : 3;  /* bit[0-2]: LPF OP1 ����ģʽ����
                                                           000��5u
                                                           001��4u
                                                           010��3u
                                                           011��2u
                                                           100��9u
                                                           101��7u
                                                           110��6u
                                                           111��5u */
        unsigned long  DUM_EN_Q_TDS     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                           1��enable(Ĭ��)
                                                           0��disable */
        unsigned long  DUM_EN_I_TDS     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                           1��enable(Ĭ��)
                                                           0��disable */
        unsigned long  reserved         : 2;  /* bit[5-6]: Reserved */
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
        unsigned long  reserved    : 2;  /* bit[6-7]: Reserved */
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
        unsigned long  reserved    : 2;  /* bit[6-7]: Reserved */
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
        unsigned long  reserved     : 3;  /* bit[5-7]: Comstarv511_Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_5_UNION;
#define ABB_RX_TDS_ANA_5_ITR_OP2_TDS_START   (0)
#define ABB_RX_TDS_ANA_5_ITR_OP2_TDS_END     (2)
#define ABB_RX_TDS_ANA_5_IBCT_OP2_TDS_START  (3)
#define ABB_RX_TDS_ANA_5_IBCT_OP2_TDS_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_ANA_3_UNION
 �ṹ˵��  : tx_idle_ana_3 �Ĵ����ṹ���塣��ַƫ����:0x12A����ֵ:0x00�����:8
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
                                                            101��7u
                                                            110��6u
                                                            111��5u */
        unsigned long  DUM_EN_Q_IDLE     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                            1��enable(Ĭ��)
                                                            0��disable */
        unsigned long  DUM_EN_I_IDLE     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                            1��enable(Ĭ��)
                                                            0��disable */
        unsigned long  reserved          : 2;  /* bit[5-6]: Reserved */
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
        unsigned long  reserved     : 2;  /* bit[6-7]: Reserved */
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
        unsigned long  reserved     : 2;  /* bit[6-7]: Reserved */
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
        unsigned long  reserved      : 3;  /* bit[5-7]: Comstarv511_Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_5_UNION;
#define ABB_RX_IDLE_ANA_5_ITR_OP2_IDLE_START   (0)
#define ABB_RX_IDLE_ANA_5_ITR_OP2_IDLE_END     (2)
#define ABB_RX_IDLE_ANA_5_IBCT_OP2_IDLE_START  (3)
#define ABB_RX_IDLE_ANA_5_IBCT_OP2_IDLE_END    (4)


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
 �ṹ��    : ABB_RX_2G_ANA_6_UNION
 �ṹ˵��  : rx_2g_ana_6 �Ĵ����ṹ���塣��ַƫ����:0x18F����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2G���üĴ����������߿��߼�������reg_analog_wr56��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved    : 2;  /* bit[0-1]: Reserved */
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
        unsigned long  reserved           : 4;  /* bit[0-3]: Reserved */
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
        unsigned long  reserved        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_8_UNION;
#define ABB_RX_2G_ANA_8_CK_CTRL_DATA_2G_START  (0)
#define ABB_RX_2G_ANA_8_CK_CTRL_DATA_2G_END    (4)
#define ABB_RX_2G_ANA_8_CK_CTRL_MODE_2G_START  (5)
#define ABB_RX_2G_ANA_8_CK_CTRL_MODE_2G_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_3G_ANA_6_UNION
 �ṹ˵��  : rx_3g_ana_6 �Ĵ����ṹ���塣��ַƫ����:0x195����ֵ:0x00�����:8
 �Ĵ���˵��: RX 3G���üĴ����������߿��߼�������reg_analog_wr56��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved    : 2;  /* bit[0-1]: Reserved */
        unsigned long  BWCT_OP3_3G : 2;  /* bit[2-3]: BWCT_OP3 OP3�������
                                                      1x�� LTEģʽ
                                                      01�� WDC &amp; X ģʽ
                                                      00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP2_3G : 2;  /* bit[4-5]: BWCT_OP2 OP2�������
                                                      1x�� LTEģʽ
                                                      01�� WDC &amp; X ģʽ
                                                      00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP1_3G : 2;  /* bit[6-7]: BWCT_OP1 OP1�������
                                                      1x�� LTEģʽ
                                                      01�� WDC &amp; X ģʽ
                                                      00�� W &amp; Gģʽ */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_ANA_6_UNION;
#define ABB_RX_3G_ANA_6_BWCT_OP3_3G_START  (2)
#define ABB_RX_3G_ANA_6_BWCT_OP3_3G_END    (3)
#define ABB_RX_3G_ANA_6_BWCT_OP2_3G_START  (4)
#define ABB_RX_3G_ANA_6_BWCT_OP2_3G_END    (5)
#define ABB_RX_3G_ANA_6_BWCT_OP1_3G_START  (6)
#define ABB_RX_3G_ANA_6_BWCT_OP1_3G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_3G_ANA_7_UNION
 �ṹ˵��  : rx_3g_ana_7 �Ĵ����ṹ���塣��ַƫ����:0x196����ֵ:0x00�����:8
 �Ĵ���˵��: RX 3G���üĴ����������߿��߼�������reg_analog_wr57��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved           : 4;  /* bit[0-3]: Reserved */
        unsigned long  QT_REF_SEL_3G      : 1;  /* bit[4]  : �������ο���ѹѡ��
                                                             0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
                                                             1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ */
        unsigned long  GMBIAS_EN_3G       : 1;  /* bit[5]  : OP3�Ƿ�ʹ��Gm_biasƫ��
                                                             0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
                                                             1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ�� */
        unsigned long  MODU_DEPTH_CTRL_3G : 1;  /* bit[6]  : ������DAC������ȿ���
                                                             0 �������0.5
                                                             1 �������0.75 */
        unsigned long  RX_DAC_LP_CTRL_3G  : 1;  /* bit[7]  : ������DACƫ�õ�������
                                                             0 ��������������ܺ�
                                                             1 С�������������ܲ� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_ANA_7_UNION;
#define ABB_RX_3G_ANA_7_QT_REF_SEL_3G_START       (4)
#define ABB_RX_3G_ANA_7_QT_REF_SEL_3G_END         (4)
#define ABB_RX_3G_ANA_7_GMBIAS_EN_3G_START        (5)
#define ABB_RX_3G_ANA_7_GMBIAS_EN_3G_END          (5)
#define ABB_RX_3G_ANA_7_MODU_DEPTH_CTRL_3G_START  (6)
#define ABB_RX_3G_ANA_7_MODU_DEPTH_CTRL_3G_END    (6)
#define ABB_RX_3G_ANA_7_RX_DAC_LP_CTRL_3G_START   (7)
#define ABB_RX_3G_ANA_7_RX_DAC_LP_CTRL_3G_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_3G_ANA_8_UNION
 �ṹ˵��  : rx_3g_ana_8 �Ĵ����ṹ���塣��ַƫ����:0x197����ֵ:0x50�����:8
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
        unsigned long  reserved        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_ANA_8_UNION;
#define ABB_RX_3G_ANA_8_CK_CTRL_DATA_3G_START  (0)
#define ABB_RX_3G_ANA_8_CK_CTRL_DATA_3G_END    (4)
#define ABB_RX_3G_ANA_8_CK_CTRL_MODE_3G_START  (5)
#define ABB_RX_3G_ANA_8_CK_CTRL_MODE_3G_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_4G_ANA_6_UNION
 �ṹ˵��  : rx_4g_ana_6 �Ĵ����ṹ���塣��ַƫ����:0x19B����ֵ:0xA8�����:8
 �Ĵ���˵��: RX 4G���üĴ����������߿��߼�������reg_analog_wr56��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved    : 2;  /* bit[0-1]: Reserved */
        unsigned long  BWCT_OP3_4G : 2;  /* bit[2-3]: BWCT_OP3 OP3�������
                                                      1x�� LTEģʽ
                                                      01�� WDC &amp; X ģʽ
                                                      00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP2_4G : 2;  /* bit[4-5]: BWCT_OP2 OP2�������
                                                      1x�� LTEģʽ
                                                      01�� WDC &amp; X ģʽ
                                                      00�� W &amp; Gģʽ */
        unsigned long  BWCT_OP1_4G : 2;  /* bit[6-7]: BWCT_OP1 OP1�������
                                                      1x�� LTEģʽ
                                                      01�� WDC &amp; X ģʽ
                                                      00�� W &amp; Gģʽ */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_ANA_6_UNION;
#define ABB_RX_4G_ANA_6_BWCT_OP3_4G_START  (2)
#define ABB_RX_4G_ANA_6_BWCT_OP3_4G_END    (3)
#define ABB_RX_4G_ANA_6_BWCT_OP2_4G_START  (4)
#define ABB_RX_4G_ANA_6_BWCT_OP2_4G_END    (5)
#define ABB_RX_4G_ANA_6_BWCT_OP1_4G_START  (6)
#define ABB_RX_4G_ANA_6_BWCT_OP1_4G_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_4G_ANA_7_UNION
 �ṹ˵��  : rx_4g_ana_7 �Ĵ����ṹ���塣��ַƫ����:0x19C����ֵ:0x00�����:8
 �Ĵ���˵��: RX 4G���üĴ����������߿��߼�������reg_analog_wr57��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved           : 4;  /* bit[0-3]: Reserved */
        unsigned long  QT_REF_SEL_4G      : 1;  /* bit[4]  : �������ο���ѹѡ��
                                                             0 ѡ��ADC Buffer��Ϊ�������Ĳο���ѹԴ
                                                             1 ѡ������ѹ��Ϊ�������Ĳο���ѹԴ */
        unsigned long  GMBIAS_EN_4G       : 1;  /* bit[5]  : OP3�Ƿ�ʹ��Gm_biasƫ��
                                                             0 gmbiasģ�鲻ʹ�ܣ�OP3ʹ�õ�����ƫ��
                                                             1 gmbiasģ��ʹ�ܣ�OP3ʹ��gmbiasƫ�� */
        unsigned long  MODU_DEPTH_CTRL_4G : 1;  /* bit[6]  : ������DAC������ȿ���
                                                             0 �������0.5
                                                             1 �������0.75 */
        unsigned long  RX_DAC_LP_CTRL_4G  : 1;  /* bit[7]  : ������DACƫ�õ�������
                                                             0 ��������������ܺ�
                                                             1 С�������������ܲ� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_ANA_7_UNION;
#define ABB_RX_4G_ANA_7_QT_REF_SEL_4G_START       (4)
#define ABB_RX_4G_ANA_7_QT_REF_SEL_4G_END         (4)
#define ABB_RX_4G_ANA_7_GMBIAS_EN_4G_START        (5)
#define ABB_RX_4G_ANA_7_GMBIAS_EN_4G_END          (5)
#define ABB_RX_4G_ANA_7_MODU_DEPTH_CTRL_4G_START  (6)
#define ABB_RX_4G_ANA_7_MODU_DEPTH_CTRL_4G_END    (6)
#define ABB_RX_4G_ANA_7_RX_DAC_LP_CTRL_4G_START   (7)
#define ABB_RX_4G_ANA_7_RX_DAC_LP_CTRL_4G_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_4G_ANA_8_UNION
 �ṹ˵��  : rx_4g_ana_8 �Ĵ����ṹ���塣��ַƫ����:0x19D����ֵ:0x10�����:8
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
        unsigned long  reserved        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_ANA_8_UNION;
#define ABB_RX_4G_ANA_8_CK_CTRL_DATA_4G_START  (0)
#define ABB_RX_4G_ANA_8_CK_CTRL_DATA_4G_END    (4)
#define ABB_RX_4G_ANA_8_CK_CTRL_MODE_4G_START  (5)
#define ABB_RX_4G_ANA_8_CK_CTRL_MODE_4G_END    (6)


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
        unsigned long  reserved     : 2;  /* bit[0-1]: Reserved */
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
        unsigned long  reserved            : 4;  /* bit[0-3]: Reserved */
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
        unsigned long  reserved         : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_8_UNION;
#define ABB_RX_TDS_ANA_8_CK_CTRL_DATA_TDS_START  (0)
#define ABB_RX_TDS_ANA_8_CK_CTRL_DATA_TDS_END    (4)
#define ABB_RX_TDS_ANA_8_CK_CTRL_MODE_TDS_START  (5)
#define ABB_RX_TDS_ANA_8_CK_CTRL_MODE_TDS_END    (6)


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
        unsigned long  reserved      : 2;  /* bit[0-1]: Reserved */
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
        unsigned long  reserved             : 4;  /* bit[0-3]: Reserved */
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
        unsigned long  reserved          : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_8_UNION;
#define ABB_RX_IDLE_ANA_8_CK_CTRL_DATA_IDLE_START  (0)
#define ABB_RX_IDLE_ANA_8_CK_CTRL_DATA_IDLE_END    (4)
#define ABB_RX_IDLE_ANA_8_CK_CTRL_MODE_IDLE_START  (5)
#define ABB_RX_IDLE_ANA_8_CK_CTRL_MODE_IDLE_END    (6)


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
        unsigned long  reserved       : 5;  /* bit[3-7]: Reserved */
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
        unsigned long  ch0_cfr_en_cfg         : 1;  /* bit[6]  : �߿��ź�CH0_CFR_ENǿ������ֵ */
        unsigned long  ch0_cfr_en_sel         : 1;  /* bit[7]  : �߿��ź�CH0_CFR_ENǿ������ʹ�� */
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
                                                          1����ʹ�� */
        unsigned long  ch0_cfr_clk_sel : 1;  /* bit[2]  : CFR�Զ��ſ�ʹ�ܣ�
                                                          0��ʹ��
                                                          1����ʹ�� */
        unsigned long  reserved        : 5;  /* bit[3-7]: Reserved */
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
        unsigned long  reserved       : 5;  /* bit[3-7]: Reserved */
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
        unsigned long  reserved_0             : 1;  /* bit[3]  : Reserved */
        unsigned long  ch0_rxa_blk_en_rpt     : 1;  /* bit[4]  : RXA_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch0_rxb_blk_en_rpt     : 1;  /* bit[5]  : RXB_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch0_cfr_en_rpt         : 1;  /* bit[6]  : CFR_EN�߿�״̬�ϱ� */
        unsigned long  reserved_1             : 1;  /* bit[7]  : Reserved */
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
                                                              001��3G_SCReserved */
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
                                                              Reserved */
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
 �ṹ��    : ABB_RXB_CH_SEL_UNION
 �ṹ˵��  : RXB_CH_SEL �Ĵ����ṹ���塣��ַƫ����:0x1F6����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��ѡ��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxb_ch_sel : 1;  /* bit[0]  : RXBͨ��ѡ��
                                                     0��ѡ��CH0��
                                                     1��ѡ��CH1��. */
        unsigned long  reserved   : 7;  /* bit[1-7]: ������ */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RXB_CH_SEL_UNION;
#define ABB_RXB_CH_SEL_rxb_ch_sel_START  (0)
#define ABB_RXB_CH_SEL_rxb_ch_sel_END    (0)


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
        unsigned long  reserved       : 5;  /* bit[3-7]: ������ */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TDS_RX_DLY_UNION;
#define ABB_CH0_TDS_RX_DLY_ch0_tds_rx_dly_START  (0)
#define ABB_CH0_TDS_RX_DLY_ch0_tds_rx_dly_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_CH0_CFR_PDET_THR2_UNION
 �ṹ˵��  : CH0_CFR_PDET_THR2 �Ĵ����ṹ���塣��ַƫ����:0x203����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0 CFR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_cfr_pdet_thr2 : 2;  /* bit[0-1]: ͨ��0 CFR��ֵ�������ֵ��bit[17:16]�� */
        unsigned long  reserved          : 6;  /* bit[2-7]: ������ */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CFR_PDET_THR2_UNION;
#define ABB_CH0_CFR_PDET_THR2_ch0_cfr_pdet_thr2_START  (0)
#define ABB_CH0_CFR_PDET_THR2_ch0_cfr_pdet_thr2_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_I_EA3_UNION
 �ṹ˵��  : CH0_RXA_I_EA3 �Ĵ����ṹ���塣��ַƫ����:0x207����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0���ż���ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_i_ea3 : 2;  /* bit[0-1]: ͨ��0���ż��RXAͨ��I·�ڵ�A����ͳ��ֵbit[25:24]�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ������ */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_EA3_UNION;
#define ABB_CH0_RXA_I_EA3_ch0_rxa_i_ea3_START  (0)
#define ABB_CH0_RXA_I_EA3_ch0_rxa_i_ea3_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_I_EC6_UNION
 �ṹ˵��  : CH0_RXA_I_EC6 �Ĵ����ṹ���塣��ַƫ����:0x213����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0���ż���ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_i_ec6 : 2;  /* bit[0-1]: ͨ��0���ż��RXAͨ��I·�ڵ�C����ͳ��ֵbit[49:48]�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ������ */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_EC6_UNION;
#define ABB_CH0_RXA_I_EC6_ch0_rxa_i_ec6_START  (0)
#define ABB_CH0_RXA_I_EC6_ch0_rxa_i_ec6_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_I_ED6_UNION
 �ṹ˵��  : CH0_RXA_I_ED6 �Ĵ����ṹ���塣��ַƫ����:0x21A����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0���ż���ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_i_ed6 : 2;  /* bit[0-1]: ͨ��0���ż��RXAͨ��I·�ڵ�D����ͳ��ֵbit[49:48]�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ������ */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_ED6_UNION;
#define ABB_CH0_RXA_I_ED6_ch0_rxa_i_ed6_START  (0)
#define ABB_CH0_RXA_I_ED6_ch0_rxa_i_ed6_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_Q_EA3_UNION
 �ṹ˵��  : CH0_RXA_Q_EA3 �Ĵ����ṹ���塣��ַƫ����:0x21E����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0���ż���ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_q_ea3 : 2;  /* bit[0-1]: ͨ��0���ż��RXAͨ��Q·�ڵ�A����ͳ��ֵbit[25:24]�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ������ */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_EA3_UNION;
#define ABB_CH0_RXA_Q_EA3_ch0_rxa_q_ea3_START  (0)
#define ABB_CH0_RXA_Q_EA3_ch0_rxa_q_ea3_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_Q_EC6_UNION
 �ṹ˵��  : CH0_RXA_Q_EC6 �Ĵ����ṹ���塣��ַƫ����:0x22A����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0���ż���ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_q_ec6 : 2;  /* bit[0-1]: ͨ��0���ż��RXAͨ��Q·�ڵ�C����ͳ��ֵbit[49:48]�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ������ */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_EC6_UNION;
#define ABB_CH0_RXA_Q_EC6_ch0_rxa_q_ec6_START  (0)
#define ABB_CH0_RXA_Q_EC6_ch0_rxa_q_ec6_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_Q_ED6_UNION
 �ṹ˵��  : CH0_RXA_Q_ED6 �Ĵ����ṹ���塣��ַƫ����:0x231����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0���ż���ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_q_ed6 : 2;  /* bit[0-1]: ͨ��0���ż��RXAͨ��Q·�ڵ�D����ͳ��ֵbit[49:48]�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ������ */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_ED6_UNION;
#define ABB_CH0_RXA_Q_ED6_ch0_rxa_q_ed6_START  (0)
#define ABB_CH0_RXA_Q_ED6_ch0_rxa_q_ed6_END    (1)


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
 �ṹ��    : ABB_CH0_RXB_I_EA3_UNION
 �ṹ˵��  : CH0_RXB_I_EA3 �Ĵ����ṹ���塣��ַƫ����:0x237����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0���ż���ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_i_ea3 : 2;  /* bit[0-1]: ͨ��0���ż��RXBͨ��I·�ڵ�A����ͳ��ֵbit[25:24]�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ������ */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_EA3_UNION;
#define ABB_CH0_RXB_I_EA3_ch0_rxb_i_ea3_START  (0)
#define ABB_CH0_RXB_I_EA3_ch0_rxb_i_ea3_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_I_EC6_UNION
 �ṹ˵��  : CH0_RXB_I_EC6 �Ĵ����ṹ���塣��ַƫ����:0x243����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0���ż���ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_i_ec6 : 2;  /* bit[0-1]: ͨ��0���ż��RXBͨ��I·�ڵ�C����ͳ��ֵbit[49:48]�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ������ */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_EC6_UNION;
#define ABB_CH0_RXB_I_EC6_ch0_rxb_i_ec6_START  (0)
#define ABB_CH0_RXB_I_EC6_ch0_rxb_i_ec6_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_I_ED6_UNION
 �ṹ˵��  : CH0_RXB_I_ED6 �Ĵ����ṹ���塣��ַƫ����:0x24A����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0���ż���ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_i_ed6 : 2;  /* bit[0-1]: ͨ��0���ż��RXBͨ��I·�ڵ�D����ͳ��ֵbit[49:48]�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ������ */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_ED6_UNION;
#define ABB_CH0_RXB_I_ED6_ch0_rxb_i_ed6_START  (0)
#define ABB_CH0_RXB_I_ED6_ch0_rxb_i_ed6_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_Q_EA3_UNION
 �ṹ˵��  : CH0_RXB_Q_EA3 �Ĵ����ṹ���塣��ַƫ����:0x24E����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0���ż���ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_q_ea3 : 2;  /* bit[0-1]: ͨ��0���ż��RXBͨ��Q·�ڵ�A����ͳ��ֵbit[25:24]�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_EA3_UNION;
#define ABB_CH0_RXB_Q_EA3_ch0_rxb_q_ea3_START  (0)
#define ABB_CH0_RXB_Q_EA3_ch0_rxb_q_ea3_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_Q_EC6_UNION
 �ṹ˵��  : CH0_RXB_Q_EC6 �Ĵ����ṹ���塣��ַƫ����:0x25A����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0���ż���ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_q_ec6 : 2;  /* bit[0-1]: ͨ��0���ż��RXBͨ��Q·�ڵ�C����ͳ��ֵbit[49:48]�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_EC6_UNION;
#define ABB_CH0_RXB_Q_EC6_ch0_rxb_q_ec6_START  (0)
#define ABB_CH0_RXB_Q_EC6_ch0_rxb_q_ec6_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_Q_ED6_UNION
 �ṹ˵��  : CH0_RXB_Q_ED6 �Ĵ����ṹ���塣��ַƫ����:0x261����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ��0���ż���ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_q_ed6 : 2;  /* bit[0-1]: ͨ��0���ż��RXBͨ��Q·�ڵ�D����ͳ��ֵbit[49:48]�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_ED6_UNION;
#define ABB_CH0_RXB_Q_ED6_ch0_rxb_q_ed6_START  (0)
#define ABB_CH0_RXB_Q_ED6_ch0_rxb_q_ed6_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_DIG_1_UNION
 �ṹ˵��  : rx_c_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x400����ֵ:0x04�����:8
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
                                                           000��2G(Ĭ��)
                                                           001��3G_SCReserved */
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
 �ṹ˵��  : rx_c_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x401����ֵ:0x13�����:8
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
 �ṹ˵��  : tx_c_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x402����ֵ:0x02�����:8
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
                                                        Reserved */
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
 �ṹ˵��  : tx_c_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x404����ֵ:0x01�����:8
 �Ĵ���˵��: TX Cģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_cfr_bp_c   : 1;  /* bit[0]  : TXͨ��CFR bypass���ƣ�
                                                        0����bypass
                                                        1��bypass(Ĭ��) */
        unsigned long  tx_flush_en_c : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                        0����ʹ��
                                                        1��ʹ�� */
        unsigned long  reserved      : 6;  /* bit[2-7]: Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_DIG_3_UNION;
#define ABB_TX_C_DIG_3_tx_cfr_bp_c_START    (0)
#define ABB_TX_C_DIG_3_tx_cfr_bp_c_END      (0)
#define ABB_TX_C_DIG_3_tx_flush_en_c_START  (1)
#define ABB_TX_C_DIG_3_tx_flush_en_c_END    (1)


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
 �ṹ˵��  : rx_c_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x406����ֵ:0xA9�����:8
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
        unsigned long  reserved  : 1;  /* bit[1]  : Reserved */
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
        unsigned long  reserved : 2;  /* bit[6-7]: Reserved */
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
        unsigned long  reserved : 2;  /* bit[6-7]: Reserved */
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
        unsigned long  reserved : 3;  /* bit[5-7]: Comstarv511_Reserved */
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
        unsigned long  reserved : 2;  /* bit[0-1]: Reserved */
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
        unsigned long  reserved        : 4;  /* bit[0-3]: Reserved */
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
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_ANA_8_UNION;
#define ABB_RX_C_ANA_8_CK_CTRL_DATA_START  (0)
#define ABB_RX_C_ANA_8_CK_CTRL_DATA_END    (4)
#define ABB_RX_C_ANA_8_CK_CTRL_MODE_START  (5)
#define ABB_RX_C_ANA_8_CK_CTRL_MODE_END    (6)


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
        unsigned long  TX_MODE_CLK : 2;  /* bit[0-1]: {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ���ƣ�
                                                      000��4G &amp; ET &amp; APT
                                                      001��3G &amp; TDS
                                                      010��CA
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
                                                      10��3��Ƶ
                                                      11��4��Ƶ */
        unsigned long  FC          : 2;  /* bit[6-7]: TX filter��ֹƵ��ѡ��
                                                      00��5MHz(Ĭ��)WSC&amp;GSM&amp;CDMA
                                                      01��10MHz WDC
                                                      10��Reserved
                                                      11��20MHz LTE */
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
#define ABB_TX_C_ANA_1_FC_START           (6)
#define ABB_TX_C_ANA_1_FC_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_C_ANA_2_UNION
 �ṹ˵��  : tx_c_ana_2 �Ĵ����ṹ���塣��ַƫ����:0x411����ֵ:0x9A�����:8
 �Ĵ���˵��: TX C���üĴ����������߿��߼�������reg_analog_wr49��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  CURRENT_MODE_OP1 : 2;  /* bit[0-1]: LPF OP1 ����ģʽ����
                                                           bit0��
                                                           0�� �������������
                                                           1�� ����������Ӵ�������5uAƫ�ã�
                                                           bit1��
                                                           0�� miller������������
                                                           1�� miller�������ݱ��������2.5uAƫ�ã�
                                                           LTE:00
                                                           WDC:01
                                                           SC:01
                                                           CDMA&amp;GSM:10 */
        unsigned long  CURRENT_MODE_OP2 : 2;  /* bit[2-3]: LPF OP2 ����ģʽ����
                                                           00 �������������
                                                           01 ����������Ӵ�������5uAƫ�ã�
                                                           10 ������ʹ��
                                                           11 ����������ټӴ�������2.5uAƫ�ã�
                                                           LTE:00
                                                           WDC:01
                                                           SC:01
                                                           CDMA&amp;GSM:10 */
        unsigned long  LPF_MODE_CURRENT : 2;  /* bit[4-5]: LPF �˷�ƫ�õ�������
                                                           �˷ŵ�����   op1   op2
                                                           00��         10u   10u
                                                           01��         5u    5u
                                                           10��         2.5u  5u
                                                           11��         2.5u  2.5u
                                                           LTE:00
                                                           Others:01 */
        unsigned long  reserved         : 1;  /* bit[6]  : TBD */
        unsigned long  TX_MODE_CLK_B3   : 1;  /* bit[7]  : {tx_XX_ana_2[7],tx_XX_ana1[1:0]}������ϵ�ģʽ����,�μ�TX_MODE_CLK˵���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_ANA_2_UNION;
#define ABB_TX_C_ANA_2_CURRENT_MODE_OP1_START  (0)
#define ABB_TX_C_ANA_2_CURRENT_MODE_OP1_END    (1)
#define ABB_TX_C_ANA_2_CURRENT_MODE_OP2_START  (2)
#define ABB_TX_C_ANA_2_CURRENT_MODE_OP2_END    (3)
#define ABB_TX_C_ANA_2_LPF_MODE_CURRENT_START  (4)
#define ABB_TX_C_ANA_2_LPF_MODE_CURRENT_END    (5)
#define ABB_TX_C_ANA_2_TX_MODE_CLK_B3_START    (7)
#define ABB_TX_C_ANA_2_TX_MODE_CLK_B3_END      (7)


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
                                                       101��7u
                                                       110��6u
                                                       111��5u */
        unsigned long  DUM_EN_Q     : 1;  /* bit[3]  : TX I channel  dummy logic control signal
                                                       1��enable(Ĭ��)
                                                       0��disable */
        unsigned long  DUM_EN_I     : 1;  /* bit[4]  : TX I channel  dummy logic control signal
                                                       1��enable(Ĭ��)
                                                       0��disable */
        unsigned long  reserved     : 2;  /* bit[5-6]: Reserved */
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
