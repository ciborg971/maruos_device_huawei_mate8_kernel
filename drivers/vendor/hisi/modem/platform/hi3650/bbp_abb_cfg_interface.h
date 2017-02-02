

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __BBP_ABB_CFG_INTERFACE_H__
#define __BBP_ABB_CFG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_abb_cfg
 ***======================================================================***/
/* �Ĵ���˵������λ
 bit[31:1]   ����
 bit[0]      ��λ�Ĵ�����
             1'b0�������λ
             1'b1:���븴λ
             ����ʱ�̣�����
             ��Чʱ�̣�����
   UNION�ṹ:  ABB_CFG_SOFT_RST_UNION */
#define ABB_CFG_SOFT_RST_ADDR                         (SOC_BBP_ABB_CFG_BASE_ADDR + 0x0)

/* �Ĵ���˵����abb����ģʽ
 bit[31:2]   ����
 bit[1]      abb����ģʽ��
             1'b0:����������abb�Ĵ���
             1'b1:���ֱ������abb�Ĵ���
 bit[0]      �ٲ�ʹ�ܣ�
             1'b0:�����ٲù���
             1'b1:ʹ���ٲù���
   UNION�ṹ:  ABB_CFG_CFG_CTRL0_UNION */
#define ABB_CFG_CFG_CTRL0_ADDR                        (SOC_BBP_ABB_CFG_BASE_ADDR + 0x4)

/* �Ĵ���˵����abb����ģʽ
 bit[31:1]   ����
 bit[0]      �����д��־��
             1'b0:д
             1'b1:��
   UNION�ṹ:  ABB_CFG_CFG_CTRL1_UNION */
#define ABB_CFG_CFG_CTRL1_ADDR                        (SOC_BBP_ABB_CFG_BASE_ADDR + 0x8)

/* �Ĵ���˵����abb����ģʽ
 bit[31:6]   ����
 bit[5:3]    ����fifoˮ�ߣ�������fifo��ǰ�洢��ȴ��ڸ�ˮ��ʱ����������fifo�жϡ�
             3'b000:1
             3'b001:2
             3'b010:3
             3'b011:4
             3'b100:5
             3'b101:6
             3'b110:7
             3'b111:8
 bit[2:0]    ����fifoˮ�ߣ�������fifo��ǰ�洢���С�ڸ�ˮ��ʱ����������fifo�жϡ�
             3'b000:1
             3'b001:2
             3'b010:3
             3'b011:4
             3'b100:5
             3'b101:6
             3'b110:7
             3'b111:8
   UNION�ṹ:  ABB_CFG_CFG_CTRL2_UNION */
#define ABB_CFG_CFG_CTRL2_ADDR                        (SOC_BBP_ABB_CFG_BASE_ADDR + 0xC)

/* �Ĵ���˵�����Ƕ�ʱģʽ���������ABB������
   ��      �����Ƕ�ʱģʽ���������ABB�����ݣ�
            д��ʽ��
            bit[12:0]��д��ַ
            bit[20:13]:д����
            ���ౣ��
            ����ʽ��
            bit[12:0]������ַ
            bit[20:13]:�ض�����
            ���ౣ��
   UNION�ṹ ���� */
#define ABB_CFG_CFG_DATA_ADDR                         (SOC_BBP_ABB_CFG_BASE_ADDR + 0x10)

/* �Ĵ���˵�����ж����μĴ���
 bit[31:4]   ����
 bit[3]      ����fifo�ж�����λ
             1'b0:����
             1'b1:������
 bit[2]      ����fifo�ж�����λ
             1'b0:����
             1'b1:������
 bit[1]      ����
 bit[0]      ����fifo����ж�����λ
             1'b0:����
             1'b1:������
   UNION�ṹ:  ABB_CFG_CFG_INT_MASK_UNION */
#define ABB_CFG_CFG_INT_MASK_ADDR                     (SOC_BBP_ABB_CFG_BASE_ADDR + 0x30)

/* �Ĵ���˵�����ж�����Ĵ���
 bit[31:4]   ����
 bit[3]      ����fifo�ж����λ
             1'b0:�����
             1'b1:���
 bit[2]      ����fifo�ж����λ
             1'b0:�����
             1'b1:���
 bit[1]      ����
 bit[0]      ����fifo����ж����λ
             1'b0:�����
             1'b1:���
   UNION�ṹ:  ABB_CFG_CFG_INT_CLR_UNION */
#define ABB_CFG_CFG_INT_CLR_ADDR                      (SOC_BBP_ABB_CFG_BASE_ADDR + 0x34)

/* �Ĵ���˵�����жϸ澯�Ĵ���
 bit[31:4]   ����
 bit[3]      ����fifo�жϸ澯�Ĵ��������µ��ж�����ʱ���ϵ��жϻ�û������������˸澯�źţ�д1�����
 bit[2]      ����fifo�жϸ澯�Ĵ��������µ��ж�����ʱ���ϵ��жϻ�û������������˸澯�źţ�д1�����
 bit[1]      ����
 bit[0]      ����fifo����жϸ澯�Ĵ��������µ��ж�����ʱ���ϵ��жϻ�û������������˸澯�źţ�д1�����
             
   UNION�ṹ:  ABB_CFG_CFG_INT_ALM_UNION */
#define ABB_CFG_CFG_INT_ALM_ADDR                      (SOC_BBP_ABB_CFG_BASE_ADDR + 0x38)

/* �Ĵ���˵����FIFOʱ���ſ�
 bit[31:1]   ����
 bit[0]      FIFOʱ���ſ�ʹ���ź�
             1'b0 : ������ʱ���ſ�
             1'b1 : ����ʱ���ſ�
   UNION�ṹ:  ABB_CFG_MEM_CTRL_UNION */
#define ABB_CFG_MEM_CTRL_ADDR                         (SOC_BBP_ABB_CFG_BASE_ADDR + 0x3C)

/* �Ĵ���˵����BBP����ʹ��
 bit[31:5]   ����
 bit[4:0]    ������θ�BBP����ABB�߿��źţ�
             5'b1_1110:����LTEģ��
             5'b1_1101:����Wģ��
             5'b1_1011:����TDSģ��
             5'b1_0111:����G1ģ��
             5'b0_1111:����G2ģ��
             5'b0_0000:ȫ����
             5'b1_1111:ȫ�����Σ�Ĭ�ϣ�
             
   UNION�ṹ:  ABB_CFG_BBP_CFG_EN_UNION */
#define ABB_CFG_BBP_CFG_EN_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0xFC)

/* �Ĵ���˵����LTEģʽ��ʱ�������ƼĴ���
 bit[31:4]   ����
 bit[3:1]    lteģʽ��ʱ������д�Ĵ���������
             0��1
             1��2
             ...
             7: 8
 bit[0]      lteģʽ��ʱ������д���ƣ�
             1'b0��д����
             1'b1��������
   UNION�ṹ:  ABB_CFG_L_CFG_CTRL_UNION */
#define ABB_CFG_L_CFG_CTRL_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x100)

/* �Ĵ���˵����TDSģʽ��ʱ�������ƼĴ���
 bit[31:4]   ����
 bit[3:1]    tdsģʽ��ʱ������д�Ĵ���������
             0��1
             1��2
             ...
             7: 8
 bit[0]      tdsģʽ��ʱ������д���ƣ�
             1'b0��д����
             1'b1��������
   UNION�ṹ:  ABB_CFG_T_CFG_CTRL_UNION */
#define ABB_CFG_T_CFG_CTRL_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x104)

/* �Ĵ���˵����Wģʽ��ʱ�������ƼĴ���
 bit[31:4]   ����
 bit[3:1]    wcdmaģʽ��ʱ������д�Ĵ���������
             0��1
             1��2
             ...
             7: 8
 bit[0]      wcdmaģʽ��ʱ������д���ƣ�
             1'b0��д����
             1'b1��������
   UNION�ṹ:  ABB_CFG_W_CFG_CTRL_UNION */
#define ABB_CFG_W_CFG_CTRL_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x108)

/* �Ĵ���˵����G1ģʽ��ʱ�������ƼĴ���
 bit[31:4]   ����
 bit[3:1]    gsm1ģʽ��ʱ������д�Ĵ���������
             0��1
             1��2
             ...
             7: 8
 bit[0]      gsm1ģʽ��ʱ������д���ƣ�
             1'b0��д����
             1'b1��������
   UNION�ṹ:  ABB_CFG_G1_CFG_CTRL_UNION */
#define ABB_CFG_G1_CFG_CTRL_ADDR                      (SOC_BBP_ABB_CFG_BASE_ADDR + 0x10C)

/* �Ĵ���˵����G2ģʽ��ʱ�������ƼĴ���
 bit[31:4]   ����
 bit[3:1]    gsm2ģʽ��ʱ������д�Ĵ���������
             0��1
             1��2
             ...
             7: 8
 bit[0]      gsm2ģʽ��ʱ������д���ƣ�
             1'b0��д����
             1'b1��������
   UNION�ṹ:  ABB_CFG_G2_CFG_CTRL_UNION */
#define ABB_CFG_G2_CFG_CTRL_ADDR                      (SOC_BBP_ABB_CFG_BASE_ADDR + 0x110)

/* �Ĵ���˵�������ǿ��LTEģ��ʱ����ʹ��
 bit[31:1]   ����
 bit[0:0]    ���ǿ��lteģ��ʱ����ʹ��
             1��ǿ�䷢����Ч
             0��ǿ�䷢����Ч
   UNION�ṹ:  ABB_CFG_L_MODE_VLD_EN_UNION */
#define ABB_CFG_L_MODE_VLD_EN_ADDR                    (SOC_BBP_ABB_CFG_BASE_ADDR + 0x130)

/* �Ĵ���˵�������ǿ��TDSģ��ʱ����ʹ��
 bit[31:1]   ����
 bit[0:0]    ���ǿ��tdsģ��ʱ����ʹ��
             1��ǿ�䷢����Ч
             0��ǿ�䷢����Ч
   UNION�ṹ:  ABB_CFG_T_MODE_VLD_EN_UNION */
#define ABB_CFG_T_MODE_VLD_EN_ADDR                    (SOC_BBP_ABB_CFG_BASE_ADDR + 0x134)

/* �Ĵ���˵�������ǿ��Wģ��ʱ����ʹ��
 bit[31:1]   ����
 bit[0:0]    ���ǿ��wģ��ʱ����ʹ��
             1��ǿ�䷢����Ч
             0��ǿ�䷢����Ч
   UNION�ṹ:  ABB_CFG_W_MODE_VLD_EN_UNION */
#define ABB_CFG_W_MODE_VLD_EN_ADDR                    (SOC_BBP_ABB_CFG_BASE_ADDR + 0x138)

/* �Ĵ���˵�������ǿ��G1ģ��ʱ����ʹ��
 bit[31:1]   ����
 bit[0:0]    ���ǿ��g1ģ��ʱ����ʹ��
             1��ǿ�䷢����Ч
             0��ǿ�䷢����Ч
   UNION�ṹ:  ABB_CFG_G1_MODE_VLD_EN_UNION */
#define ABB_CFG_G1_MODE_VLD_EN_ADDR                   (SOC_BBP_ABB_CFG_BASE_ADDR + 0x13C)

/* �Ĵ���˵�������ǿ��G2ģ��ʱ����ʹ��
 bit[31:1]   ����
 bit[0:0]    ���ǿ��g2ģ��ʱ����ʹ��
             1��ǿ�䷢����Ч
             0��ǿ�䷢����Ч
   UNION�ṹ:  ABB_CFG_G2_MODE_VLD_EN_UNION */
#define ABB_CFG_G2_MODE_VLD_EN_ADDR                   (SOC_BBP_ABB_CFG_BASE_ADDR + 0x140)

/* �Ĵ���˵������ʱģʽ��lte bbp����ABB������
   ��      ������ʱģʽ��lte bbp����ABB�����ݣ�
            д��ʽ��
            bit[12:0]��д��ַ
            bit[20:13]:д����
            ���ౣ��
            ����ʽ��
            bit[12:0]������ַ
            bit[20:13]:�ض�����
            ���ౣ��
   UNION�ṹ ���� */
#define ABB_CFG_L_CFG_DATA_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x160)

/* �Ĵ���˵������ʱģʽ��tds bbp����ABB������
   ��      ������ʱģʽ��tds bbp����ABB�����ݣ�
            д��ʽ��
            bit[12:0]��д��ַ
            bit[20:13]:д����
            ���ౣ��
            ����ʽ��
            bit[12:0]������ַ
            bit[20:13]:�ض�����
            ���ౣ��
   UNION�ṹ ���� */
#define ABB_CFG_T_CFG_DATA_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x180)

/* �Ĵ���˵������ʱģʽ��w bbp����ABB������
   ��      ������ʱģʽ��wcdma bbp����ABB�����ݣ�
            д��ʽ��
            bit[12:0]��д��ַ
            bit[20:13]:д����
            ���ౣ��
            ����ʽ��
            bit[12:0]������ַ
            bit[20:13]:�ض�����
            ���ౣ��
   UNION�ṹ ���� */
#define ABB_CFG_W_CFG_DATA_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x1A0)

/* �Ĵ���˵������ʱģʽ��gsm1 bbp����ABB������
   ��      ������ʱģʽ��gsm1 bbp����ABB�����ݣ�
            д��ʽ��
            bit[12:0]��д��ַ
            bit[20:13]:д����
            ���ౣ��
            ����ʽ��
            bit[12:0]������ַ
            bit[20:13]:�ض�����
            ���ౣ��
   UNION�ṹ ���� */
#define ABB_CFG_G1_CFG_DATA_ADDR                      (SOC_BBP_ABB_CFG_BASE_ADDR + 0x1C0)

/* �Ĵ���˵������ʱģʽ��gsm2 bbp����ABB������
   ��      ������ʱģʽ��gsm2 bbp����ABB�����ݣ�
            д��ʽ��
            bit[12:0]��д��ַ
            bit[20:13]:д����
            ���ౣ��
            ����ʽ��
            bit[12:0]������ַ
            bit[20:13]:�ض�����
            ���ౣ��
   UNION�ṹ ���� */
#define ABB_CFG_G2_CFG_DATA_ADDR                      (SOC_BBP_ABB_CFG_BASE_ADDR + 0x1E0)

/* �Ĵ���˵�����ж�״̬����
 bit[31:4]   ����
 bit[3]      ����fifo�жϱ�־��
             1'b0:���ж�
             1'b1:���ж�
 bit[2]      ����fifo�жϱ�־��
             1'b0:���ж�
             1'b1:���ж�
 bit[1]      ����
 bit[0]      ����fifo����жϱ�־��
             1'b0:���ж�
             1'b1:���ж�
   UNION�ṹ:  ABB_CFG_CFG_INT_STATE_UNION */
#define ABB_CFG_CFG_INT_STATE_ADDR                    (SOC_BBP_ABB_CFG_BASE_ADDR + 0x200)

/* �Ĵ���˵����FIFO״̬����
 bit[31:12]  ����
 bit[11:8]   rxfifo�����ݸ���
 bit[7:4]    txfifo�����ݸ���
 bit[3]      ����fifo����־��
             1'b0:����
             1'b1:��
 bit[2]      ����fifo�ձ�־��
             1'b0:�ǿ�
             1'b1:��
 bit[1]      ����fifo����־��
             1'b0:����
             1'b1:��
 bit[0]      ����fifo�ձ�־��
             1'b0:�ǿ�
             1'b1:��
   UNION�ṹ:  ABB_CFG_FIFO_STATE_UNION */
#define ABB_CFG_FIFO_STATE_ADDR                       (SOC_BBP_ABB_CFG_BASE_ADDR + 0x204)

/* �Ĵ���˵����BBP��ǰ����״ָ̬ʾ
 bit[31:5]   ����
 bit[4]      g2ģ��ǰ����ABB״ָ̬ʾ��
             0����ǰû�����ã����������µ�����
             1����ǰ�������ã����������µ�����
 bit[3]      g1ģ��ǰ����ABB״ָ̬ʾ��
             0����ǰû�����ã����������µ�����
             1����ǰ�������ã����������µ�����
 bit[2]      tģ��ǰ����ABB״ָ̬ʾ��
             0����ǰû�����ã����������µ�����
             1����ǰ�������ã����������µ�����
 bit[1]      wģ��ǰ����ABB״ָ̬ʾ��
             0����ǰû�����ã����������µ�����
             1����ǰ�������ã����������µ�����
 bit[0]      lģ��ǰ����ABB״ָ̬ʾ��
             0����ǰû�����ã����������µ�����
             1����ǰ�������ã����������µ�����
   UNION�ṹ:  ABB_CFG_BBP_RW_STATE_UNION */
#define ABB_CFG_BBP_RW_STATE_ADDR                     (SOC_BBP_ABB_CFG_BASE_ADDR + 0x208)





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
                     (1/1) register_define_abb_cfg
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : ABB_CFG_SOFT_RST_UNION
 �ṹ˵��  : SOFT_RST �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��λ
*****************************************************************************/
typedef union
{
    unsigned long      soft_rst_reg;
    struct
    {
        unsigned long  soft_rst : 1;  /* bit[0]   : ��λ�Ĵ�����
                                                    1'b0�������λ
                                                    1'b1:���븴λ
                                                    ����ʱ�̣�����
                                                    ��Чʱ�̣����� */
        unsigned long  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} ABB_CFG_SOFT_RST_UNION;
#define ABB_CFG_SOFT_RST_soft_rst_START  (0)
#define ABB_CFG_SOFT_RST_soft_rst_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CFG_CFG_CTRL0_UNION
 �ṹ˵��  : CFG_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000003�����:32
 �Ĵ���˵��: abb����ģʽ
*****************************************************************************/
typedef union
{
    unsigned long      cfg_ctrl0_reg;
    struct
    {
        unsigned long  abt_en   : 1;  /* bit[0]   : �ٲ�ʹ�ܣ�
                                                    1'b0:�����ٲù���
                                                    1'b1:ʹ���ٲù��� */
        unsigned long  cfg_mode : 1;  /* bit[1]   : abb����ģʽ��
                                                    1'b0:����������abb�Ĵ���
                                                    1'b1:���ֱ������abb�Ĵ��� */
        unsigned long  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} ABB_CFG_CFG_CTRL0_UNION;
#define ABB_CFG_CFG_CTRL0_abt_en_START    (0)
#define ABB_CFG_CFG_CTRL0_abt_en_END      (0)
#define ABB_CFG_CFG_CTRL0_cfg_mode_START  (1)
#define ABB_CFG_CFG_CTRL0_cfg_mode_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CFG_CFG_CTRL1_UNION
 �ṹ˵��  : CFG_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: abb����ģʽ
*****************************************************************************/
typedef union
{
    unsigned long      cfg_ctrl1_reg;
    struct
    {
        unsigned long  cfg_rw   : 1;  /* bit[0]   : �����д��־��
                                                    1'b0:д
                                                    1'b1:�� */
        unsigned long  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} ABB_CFG_CFG_CTRL1_UNION;
#define ABB_CFG_CFG_CTRL1_cfg_rw_START    (0)
#define ABB_CFG_CFG_CTRL1_cfg_rw_END      (0)


/*****************************************************************************
 �ṹ��    : ABB_CFG_CFG_CTRL2_UNION
 �ṹ˵��  : CFG_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: abb����ģʽ
*****************************************************************************/
typedef union
{
    unsigned long      cfg_ctrl2_reg;
    struct
    {
        unsigned long  txfifo_wl : 3;  /* bit[0-2] : ����fifoˮ�ߣ�������fifo��ǰ�洢���С�ڸ�ˮ��ʱ����������fifo�жϡ�
                                                     3'b000:1
                                                     3'b001:2
                                                     3'b010:3
                                                     3'b011:4
                                                     3'b100:5
                                                     3'b101:6
                                                     3'b110:7
                                                     3'b111:8 */
        unsigned long  rxfifo_wl : 3;  /* bit[3-5] : ����fifoˮ�ߣ�������fifo��ǰ�洢��ȴ��ڸ�ˮ��ʱ����������fifo�жϡ�
                                                     3'b000:1
                                                     3'b001:2
                                                     3'b010:3
                                                     3'b011:4
                                                     3'b100:5
                                                     3'b101:6
                                                     3'b110:7
                                                     3'b111:8 */
        unsigned long  reserved  : 26; /* bit[6-31]: ���� */
    } reg;
} ABB_CFG_CFG_CTRL2_UNION;
#define ABB_CFG_CFG_CTRL2_txfifo_wl_START  (0)
#define ABB_CFG_CFG_CTRL2_txfifo_wl_END    (2)
#define ABB_CFG_CFG_CTRL2_rxfifo_wl_START  (3)
#define ABB_CFG_CFG_CTRL2_rxfifo_wl_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CFG_CFG_INT_MASK_UNION
 �ṹ˵��  : CFG_INT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж����μĴ���
*****************************************************************************/
typedef union
{
    unsigned long      cfg_int_mask_reg;
    struct
    {
        unsigned long  rorim    : 1;  /* bit[0]   : ����fifo����ж�����λ
                                                    1'b0:����
                                                    1'b1:������ */
        unsigned long  reserved_0: 1;  /* bit[1]   : ���� */
        unsigned long  rxim     : 1;  /* bit[2]   : ����fifo�ж�����λ
                                                    1'b0:����
                                                    1'b1:������ */
        unsigned long  txim     : 1;  /* bit[3]   : ����fifo�ж�����λ
                                                    1'b0:����
                                                    1'b1:������ */
        unsigned long  reserved_1: 28; /* bit[4-31]: ���� */
    } reg;
} ABB_CFG_CFG_INT_MASK_UNION;
#define ABB_CFG_CFG_INT_MASK_rorim_START     (0)
#define ABB_CFG_CFG_INT_MASK_rorim_END       (0)
#define ABB_CFG_CFG_INT_MASK_rxim_START      (2)
#define ABB_CFG_CFG_INT_MASK_rxim_END        (2)
#define ABB_CFG_CFG_INT_MASK_txim_START      (3)
#define ABB_CFG_CFG_INT_MASK_txim_END        (3)


/*****************************************************************************
 �ṹ��    : ABB_CFG_CFG_INT_CLR_UNION
 �ṹ˵��  : CFG_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      cfg_int_clr_reg;
    struct
    {
        unsigned long  roric    : 1;  /* bit[0]   : ����fifo����ж����λ
                                                    1'b0:�����
                                                    1'b1:��� */
        unsigned long  reserved_0: 1;  /* bit[1]   : ���� */
        unsigned long  rxic     : 1;  /* bit[2]   : ����fifo�ж����λ
                                                    1'b0:�����
                                                    1'b1:��� */
        unsigned long  txic     : 1;  /* bit[3]   : ����fifo�ж����λ
                                                    1'b0:�����
                                                    1'b1:��� */
        unsigned long  reserved_1: 28; /* bit[4-31]: ���� */
    } reg;
} ABB_CFG_CFG_INT_CLR_UNION;
#define ABB_CFG_CFG_INT_CLR_roric_START     (0)
#define ABB_CFG_CFG_INT_CLR_roric_END       (0)
#define ABB_CFG_CFG_INT_CLR_rxic_START      (2)
#define ABB_CFG_CFG_INT_CLR_rxic_END        (2)
#define ABB_CFG_CFG_INT_CLR_txic_START      (3)
#define ABB_CFG_CFG_INT_CLR_txic_END        (3)


/*****************************************************************************
 �ṹ��    : ABB_CFG_CFG_INT_ALM_UNION
 �ṹ˵��  : CFG_INT_ALM �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: �жϸ澯�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      cfg_int_alm_reg;
    struct
    {
        unsigned long  roria    : 1;  /* bit[0]   : ����fifo����жϸ澯�Ĵ��������µ��ж�����ʱ���ϵ��жϻ�û������������˸澯�źţ�д1����� */
        unsigned long  reserved_0: 1;  /* bit[1]   : ���� */
        unsigned long  rxia     : 1;  /* bit[2]   : ����fifo�жϸ澯�Ĵ��������µ��ж�����ʱ���ϵ��жϻ�û������������˸澯�źţ�д1����� */
        unsigned long  txia     : 1;  /* bit[3]   : ����fifo�жϸ澯�Ĵ��������µ��ж�����ʱ���ϵ��жϻ�û������������˸澯�źţ�д1����� */
        unsigned long  reserved_1: 28; /* bit[4-31]: ���� */
    } reg;
} ABB_CFG_CFG_INT_ALM_UNION;
#define ABB_CFG_CFG_INT_ALM_roria_START     (0)
#define ABB_CFG_CFG_INT_ALM_roria_END       (0)
#define ABB_CFG_CFG_INT_ALM_rxia_START      (2)
#define ABB_CFG_CFG_INT_ALM_rxia_END        (2)
#define ABB_CFG_CFG_INT_ALM_txia_START      (3)
#define ABB_CFG_CFG_INT_ALM_txia_END        (3)


/*****************************************************************************
 �ṹ��    : ABB_CFG_MEM_CTRL_UNION
 �ṹ˵��  : MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: FIFOʱ���ſ�
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl_reg;
    struct
    {
        unsigned long  clk_sel  : 1;  /* bit[0]   : FIFOʱ���ſ�ʹ���ź�
                                                    1'b0 : ������ʱ���ſ�
                                                    1'b1 : ����ʱ���ſ� */
        unsigned long  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} ABB_CFG_MEM_CTRL_UNION;
#define ABB_CFG_MEM_CTRL_clk_sel_START   (0)
#define ABB_CFG_MEM_CTRL_clk_sel_END     (0)


/*****************************************************************************
 �ṹ��    : ABB_CFG_BBP_CFG_EN_UNION
 �ṹ˵��  : BBP_CFG_EN �Ĵ����ṹ���塣��ַƫ����:0x00FC����ֵ:0x0000001F�����:32
 �Ĵ���˵��: BBP����ʹ��
*****************************************************************************/
typedef union
{
    unsigned long      bbp_cfg_en_reg;
    struct
    {
        unsigned long  bbp_cfg_en : 5;  /* bit[0-4] : ������θ�BBP����ABB�߿��źţ�
                                                      5'b1_1110:����LTEģ��
                                                      5'b1_1101:����Wģ��
                                                      5'b1_1011:����TDSģ��
                                                      5'b1_0111:����G1ģ��
                                                      5'b0_1111:����G2ģ��
                                                      5'b0_0000:ȫ����
                                                      5'b1_1111:ȫ�����Σ�Ĭ�ϣ� */
        unsigned long  reserved   : 27; /* bit[5-31]: ���� */
    } reg;
} ABB_CFG_BBP_CFG_EN_UNION;
#define ABB_CFG_BBP_CFG_EN_bbp_cfg_en_START  (0)
#define ABB_CFG_BBP_CFG_EN_bbp_cfg_en_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_CFG_L_CFG_CTRL_UNION
 �ṹ˵��  : L_CFG_CTRL �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00000000�����:32
 �Ĵ���˵��: LTEģʽ��ʱ�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      l_cfg_ctrl_reg;
    struct
    {
        unsigned long  l_cfg_rw  : 1;  /* bit[0]   : lteģʽ��ʱ������д���ƣ�
                                                     1'b0��д����
                                                     1'b1�������� */
        unsigned long  l_cfg_num : 3;  /* bit[1-3] : lteģʽ��ʱ������д�Ĵ���������
                                                     0��1
                                                     1��2
                                                     ...
                                                     7: 8 */
        unsigned long  reserved  : 28; /* bit[4-31]: ���� */
    } reg;
} ABB_CFG_L_CFG_CTRL_UNION;
#define ABB_CFG_L_CFG_CTRL_l_cfg_rw_START   (0)
#define ABB_CFG_L_CFG_CTRL_l_cfg_rw_END     (0)
#define ABB_CFG_L_CFG_CTRL_l_cfg_num_START  (1)
#define ABB_CFG_L_CFG_CTRL_l_cfg_num_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CFG_T_CFG_CTRL_UNION
 �ṹ˵��  : T_CFG_CTRL �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000000�����:32
 �Ĵ���˵��: TDSģʽ��ʱ�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      t_cfg_ctrl_reg;
    struct
    {
        unsigned long  t_cfg_rw  : 1;  /* bit[0]   : tdsģʽ��ʱ������д���ƣ�
                                                     1'b0��д����
                                                     1'b1�������� */
        unsigned long  t_cfg_num : 3;  /* bit[1-3] : tdsģʽ��ʱ������д�Ĵ���������
                                                     0��1
                                                     1��2
                                                     ...
                                                     7: 8 */
        unsigned long  reserved  : 28; /* bit[4-31]: ���� */
    } reg;
} ABB_CFG_T_CFG_CTRL_UNION;
#define ABB_CFG_T_CFG_CTRL_t_cfg_rw_START   (0)
#define ABB_CFG_T_CFG_CTRL_t_cfg_rw_END     (0)
#define ABB_CFG_T_CFG_CTRL_t_cfg_num_START  (1)
#define ABB_CFG_T_CFG_CTRL_t_cfg_num_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CFG_W_CFG_CTRL_UNION
 �ṹ˵��  : W_CFG_CTRL �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000000�����:32
 �Ĵ���˵��: Wģʽ��ʱ�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      w_cfg_ctrl_reg;
    struct
    {
        unsigned long  w_cfg_rw  : 1;  /* bit[0]   : wcdmaģʽ��ʱ������д���ƣ�
                                                     1'b0��д����
                                                     1'b1�������� */
        unsigned long  w_cfg_num : 3;  /* bit[1-3] : wcdmaģʽ��ʱ������д�Ĵ���������
                                                     0��1
                                                     1��2
                                                     ...
                                                     7: 8 */
        unsigned long  reserved  : 28; /* bit[4-31]: ���� */
    } reg;
} ABB_CFG_W_CFG_CTRL_UNION;
#define ABB_CFG_W_CFG_CTRL_w_cfg_rw_START   (0)
#define ABB_CFG_W_CFG_CTRL_w_cfg_rw_END     (0)
#define ABB_CFG_W_CFG_CTRL_w_cfg_num_START  (1)
#define ABB_CFG_W_CFG_CTRL_w_cfg_num_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CFG_G1_CFG_CTRL_UNION
 �ṹ˵��  : G1_CFG_CTRL �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00000000�����:32
 �Ĵ���˵��: G1ģʽ��ʱ�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      g1_cfg_ctrl_reg;
    struct
    {
        unsigned long  g1_cfg_rw  : 1;  /* bit[0]   : gsm1ģʽ��ʱ������д���ƣ�
                                                      1'b0��д����
                                                      1'b1�������� */
        unsigned long  g1_cfg_num : 3;  /* bit[1-3] : gsm1ģʽ��ʱ������д�Ĵ���������
                                                      0��1
                                                      1��2
                                                      ...
                                                      7: 8 */
        unsigned long  reserved   : 28; /* bit[4-31]: ���� */
    } reg;
} ABB_CFG_G1_CFG_CTRL_UNION;
#define ABB_CFG_G1_CFG_CTRL_g1_cfg_rw_START   (0)
#define ABB_CFG_G1_CFG_CTRL_g1_cfg_rw_END     (0)
#define ABB_CFG_G1_CFG_CTRL_g1_cfg_num_START  (1)
#define ABB_CFG_G1_CFG_CTRL_g1_cfg_num_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CFG_G2_CFG_CTRL_UNION
 �ṹ˵��  : G2_CFG_CTRL �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00000000�����:32
 �Ĵ���˵��: G2ģʽ��ʱ�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      g2_cfg_ctrl_reg;
    struct
    {
        unsigned long  g2_cfg_rw  : 1;  /* bit[0]   : gsm2ģʽ��ʱ������д���ƣ�
                                                      1'b0��д����
                                                      1'b1�������� */
        unsigned long  g2_cfg_num : 3;  /* bit[1-3] : gsm2ģʽ��ʱ������д�Ĵ���������
                                                      0��1
                                                      1��2
                                                      ...
                                                      7: 8 */
        unsigned long  reserved   : 28; /* bit[4-31]: ���� */
    } reg;
} ABB_CFG_G2_CFG_CTRL_UNION;
#define ABB_CFG_G2_CFG_CTRL_g2_cfg_rw_START   (0)
#define ABB_CFG_G2_CFG_CTRL_g2_cfg_rw_END     (0)
#define ABB_CFG_G2_CFG_CTRL_g2_cfg_num_START  (1)
#define ABB_CFG_G2_CFG_CTRL_g2_cfg_num_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CFG_L_MODE_VLD_EN_UNION
 �ṹ˵��  : L_MODE_VLD_EN �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ǿ��LTEģ��ʱ����ʹ��
*****************************************************************************/
typedef union
{
    unsigned long      l_mode_vld_en_reg;
    struct
    {
        unsigned long  l_mode_vld_en : 1;  /* bit[0-0] : ���ǿ��lteģ��ʱ����ʹ��
                                                         1��ǿ�䷢����Ч
                                                         0��ǿ�䷢����Ч */
        unsigned long  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} ABB_CFG_L_MODE_VLD_EN_UNION;
#define ABB_CFG_L_MODE_VLD_EN_l_mode_vld_en_START  (0)
#define ABB_CFG_L_MODE_VLD_EN_l_mode_vld_en_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CFG_T_MODE_VLD_EN_UNION
 �ṹ˵��  : T_MODE_VLD_EN �Ĵ����ṹ���塣��ַƫ����:0x0134����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ǿ��TDSģ��ʱ����ʹ��
*****************************************************************************/
typedef union
{
    unsigned long      t_mode_vld_en_reg;
    struct
    {
        unsigned long  t_mode_vld_en : 1;  /* bit[0-0] : ���ǿ��tdsģ��ʱ����ʹ��
                                                         1��ǿ�䷢����Ч
                                                         0��ǿ�䷢����Ч */
        unsigned long  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} ABB_CFG_T_MODE_VLD_EN_UNION;
#define ABB_CFG_T_MODE_VLD_EN_t_mode_vld_en_START  (0)
#define ABB_CFG_T_MODE_VLD_EN_t_mode_vld_en_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CFG_W_MODE_VLD_EN_UNION
 �ṹ˵��  : W_MODE_VLD_EN �Ĵ����ṹ���塣��ַƫ����:0x0138����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ǿ��Wģ��ʱ����ʹ��
*****************************************************************************/
typedef union
{
    unsigned long      w_mode_vld_en_reg;
    struct
    {
        unsigned long  w_mode_vld_en : 1;  /* bit[0-0] : ���ǿ��wģ��ʱ����ʹ��
                                                         1��ǿ�䷢����Ч
                                                         0��ǿ�䷢����Ч */
        unsigned long  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} ABB_CFG_W_MODE_VLD_EN_UNION;
#define ABB_CFG_W_MODE_VLD_EN_w_mode_vld_en_START  (0)
#define ABB_CFG_W_MODE_VLD_EN_w_mode_vld_en_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CFG_G1_MODE_VLD_EN_UNION
 �ṹ˵��  : G1_MODE_VLD_EN �Ĵ����ṹ���塣��ַƫ����:0x013C����ֵ:0x00000001�����:32
 �Ĵ���˵��: ���ǿ��G1ģ��ʱ����ʹ��
*****************************************************************************/
typedef union
{
    unsigned long      g1_mode_vld_en_reg;
    struct
    {
        unsigned long  g1_mode_vld_en : 1;  /* bit[0-0] : ���ǿ��g1ģ��ʱ����ʹ��
                                                          1��ǿ�䷢����Ч
                                                          0��ǿ�䷢����Ч */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} ABB_CFG_G1_MODE_VLD_EN_UNION;
#define ABB_CFG_G1_MODE_VLD_EN_g1_mode_vld_en_START  (0)
#define ABB_CFG_G1_MODE_VLD_EN_g1_mode_vld_en_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CFG_G2_MODE_VLD_EN_UNION
 �ṹ˵��  : G2_MODE_VLD_EN �Ĵ����ṹ���塣��ַƫ����:0x0140����ֵ:0x00000001�����:32
 �Ĵ���˵��: ���ǿ��G2ģ��ʱ����ʹ��
*****************************************************************************/
typedef union
{
    unsigned long      g2_mode_vld_en_reg;
    struct
    {
        unsigned long  g2_mode_vld_en : 1;  /* bit[0-0] : ���ǿ��g2ģ��ʱ����ʹ��
                                                          1��ǿ�䷢����Ч
                                                          0��ǿ�䷢����Ч */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} ABB_CFG_G2_MODE_VLD_EN_UNION;
#define ABB_CFG_G2_MODE_VLD_EN_g2_mode_vld_en_START  (0)
#define ABB_CFG_G2_MODE_VLD_EN_g2_mode_vld_en_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CFG_CFG_INT_STATE_UNION
 �ṹ˵��  : CFG_INT_STATE �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�״̬����
*****************************************************************************/
typedef union
{
    unsigned long      cfg_int_state_reg;
    struct
    {
        unsigned long  roris    : 1;  /* bit[0]   : ����fifo����жϱ�־��
                                                    1'b0:���ж�
                                                    1'b1:���ж� */
        unsigned long  reserved_0: 1;  /* bit[1]   : ���� */
        unsigned long  rxis     : 1;  /* bit[2]   : ����fifo�жϱ�־��
                                                    1'b0:���ж�
                                                    1'b1:���ж� */
        unsigned long  txis     : 1;  /* bit[3]   : ����fifo�жϱ�־��
                                                    1'b0:���ж�
                                                    1'b1:���ж� */
        unsigned long  reserved_1: 28; /* bit[4-31]: ���� */
    } reg;
} ABB_CFG_CFG_INT_STATE_UNION;
#define ABB_CFG_CFG_INT_STATE_roris_START     (0)
#define ABB_CFG_CFG_INT_STATE_roris_END       (0)
#define ABB_CFG_CFG_INT_STATE_rxis_START      (2)
#define ABB_CFG_CFG_INT_STATE_rxis_END        (2)
#define ABB_CFG_CFG_INT_STATE_txis_START      (3)
#define ABB_CFG_CFG_INT_STATE_txis_END        (3)


/*****************************************************************************
 �ṹ��    : ABB_CFG_FIFO_STATE_UNION
 �ṹ˵��  : FIFO_STATE �Ĵ����ṹ���塣��ַƫ����:0x0204����ֵ:0x00000000�����:32
 �Ĵ���˵��: FIFO״̬����
*****************************************************************************/
typedef union
{
    unsigned long      fifo_state_reg;
    struct
    {
        unsigned long  txfifo_empty : 1;  /* bit[0]    : ����fifo�ձ�־��
                                                         1'b0:�ǿ�
                                                         1'b1:�� */
        unsigned long  txfifo_full  : 1;  /* bit[1]    : ����fifo����־��
                                                         1'b0:����
                                                         1'b1:�� */
        unsigned long  rxfifo_empty : 1;  /* bit[2]    : ����fifo�ձ�־��
                                                         1'b0:�ǿ�
                                                         1'b1:�� */
        unsigned long  rxfifo_full  : 1;  /* bit[3]    : ����fifo����־��
                                                         1'b0:����
                                                         1'b1:�� */
        unsigned long  txfifo_cnt   : 4;  /* bit[4-7]  : txfifo�����ݸ��� */
        unsigned long  rxfifo_cnt   : 4;  /* bit[8-11] : rxfifo�����ݸ��� */
        unsigned long  reserved     : 20; /* bit[12-31]: ���� */
    } reg;
} ABB_CFG_FIFO_STATE_UNION;
#define ABB_CFG_FIFO_STATE_txfifo_empty_START  (0)
#define ABB_CFG_FIFO_STATE_txfifo_empty_END    (0)
#define ABB_CFG_FIFO_STATE_txfifo_full_START   (1)
#define ABB_CFG_FIFO_STATE_txfifo_full_END     (1)
#define ABB_CFG_FIFO_STATE_rxfifo_empty_START  (2)
#define ABB_CFG_FIFO_STATE_rxfifo_empty_END    (2)
#define ABB_CFG_FIFO_STATE_rxfifo_full_START   (3)
#define ABB_CFG_FIFO_STATE_rxfifo_full_END     (3)
#define ABB_CFG_FIFO_STATE_txfifo_cnt_START    (4)
#define ABB_CFG_FIFO_STATE_txfifo_cnt_END      (7)
#define ABB_CFG_FIFO_STATE_rxfifo_cnt_START    (8)
#define ABB_CFG_FIFO_STATE_rxfifo_cnt_END      (11)


/*****************************************************************************
 �ṹ��    : ABB_CFG_BBP_RW_STATE_UNION
 �ṹ˵��  : BBP_RW_STATE �Ĵ����ṹ���塣��ַƫ����:0x0208����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��ǰ����״ָ̬ʾ
*****************************************************************************/
typedef union
{
    unsigned long      bbp_rw_state_reg;
    struct
    {
        unsigned long  l_rw_state  : 1;  /* bit[0]   : lģ��ǰ����ABB״ָ̬ʾ��
                                                       0����ǰû�����ã����������µ�����
                                                       1����ǰ�������ã����������µ����� */
        unsigned long  w_rw_state  : 1;  /* bit[1]   : wģ��ǰ����ABB״ָ̬ʾ��
                                                       0����ǰû�����ã����������µ�����
                                                       1����ǰ�������ã����������µ����� */
        unsigned long  t_rw_state  : 1;  /* bit[2]   : tģ��ǰ����ABB״ָ̬ʾ��
                                                       0����ǰû�����ã����������µ�����
                                                       1����ǰ�������ã����������µ����� */
        unsigned long  g1_rw_state : 1;  /* bit[3]   : g1ģ��ǰ����ABB״ָ̬ʾ��
                                                       0����ǰû�����ã����������µ�����
                                                       1����ǰ�������ã����������µ����� */
        unsigned long  g2_rw_state : 1;  /* bit[4]   : g2ģ��ǰ����ABB״ָ̬ʾ��
                                                       0����ǰû�����ã����������µ�����
                                                       1����ǰ�������ã����������µ����� */
        unsigned long  reserved    : 27; /* bit[5-31]: ���� */
    } reg;
} ABB_CFG_BBP_RW_STATE_UNION;
#define ABB_CFG_BBP_RW_STATE_l_rw_state_START   (0)
#define ABB_CFG_BBP_RW_STATE_l_rw_state_END     (0)
#define ABB_CFG_BBP_RW_STATE_w_rw_state_START   (1)
#define ABB_CFG_BBP_RW_STATE_w_rw_state_END     (1)
#define ABB_CFG_BBP_RW_STATE_t_rw_state_START   (2)
#define ABB_CFG_BBP_RW_STATE_t_rw_state_END     (2)
#define ABB_CFG_BBP_RW_STATE_g1_rw_state_START  (3)
#define ABB_CFG_BBP_RW_STATE_g1_rw_state_END    (3)
#define ABB_CFG_BBP_RW_STATE_g2_rw_state_START  (4)
#define ABB_CFG_BBP_RW_STATE_g2_rw_state_END    (4)




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

#endif /* end of bbp_abb_cfg_interface.h */
