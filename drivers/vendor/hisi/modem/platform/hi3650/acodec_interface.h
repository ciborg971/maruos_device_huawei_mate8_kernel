

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __AUDIO_CODEC_INTERFACE_H__
#define __AUDIO_CODEC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/


/****************************************************************************
                     (1/2) SoC CODEC
 ****************************************************************************/
/* �Ĵ���˵�����߼���·��λ�����Ĵ����⣬��λ���й����߼���CRG���Ĵ������⡣ */
#define HISSC_SW_RST_N_ADDR                           ((PAGE_SoCCODEC) + (0x00))
/* �����λCODEC�ڲ����й����߼���
0����λ��Ч��
1������������ */
#define    HISSC_SW_RST_N_BIT_START   (0)
#define    HISSC_SW_RST_N_BIT_END     (0)
/* reserved RO Registers */
#define    HISSC_DIG_RO_00_BIT_START  (1)
#define    HISSC_DIG_RO_00_BIT_END    (7)
/* �汾�Ĵ��� */
#define    HISSC_VERSION_BIT_START    (8)
#define    HISSC_VERSION_BIT_END      (15)

/* �Ĵ���˵����APB IF/DMIC IF/SIF/I2S�ӿ����ģ��ʱ��ʹ������ */
#define HISSC_IF_CLK_EN_CFG_ADDR                      ((PAGE_SoCCODEC) + (0x04))
/* STEREO������ͨ���첽FIFOʱ��ʹ��:
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_STEREO_UPLINK_L_EN_BIT_START  (0)
#define    HISSC_STEREO_UPLINK_L_EN_BIT_END    (0)
/* STEREO������ͨ���첽FIFOʱ��ʹ��:
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_STEREO_UPLINK_R_EN_BIT_START  (1)
#define    HISSC_STEREO_UPLINK_R_EN_BIT_END    (1)
/* VOICE������ͨ���첽FIFOʱ��ʹ��:
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_VOICE_UPLINK_L_EN_BIT_START   (2)
#define    HISSC_VOICE_UPLINK_L_EN_BIT_END     (2)
/* VOICE������ͨ���첽FIFOʱ��ʹ��:
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_VOICE_UPLINK_R_EN_BIT_START   (3)
#define    HISSC_VOICE_UPLINK_R_EN_BIT_END     (3)
/* STEREO������ͨ���첽FIFO��PGAʱ��ʹ��:
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_STEREO_DLINK_L_EN_BIT_START   (4)
#define    HISSC_STEREO_DLINK_L_EN_BIT_END     (4)
/* STEREO������ͨ���첽FIFO��PGAʱ��ʹ��:
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_STEREO_DLINK_R_EN_BIT_START   (5)
#define    HISSC_STEREO_DLINK_R_EN_BIT_END     (5)
/* VOICE����ͨ���첽FIFO��PGAʱ��ʹ��:
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_VOICE_DLINK_EN_BIT_START      (6)
#define    HISSC_VOICE_DLINK_EN_BIT_END        (6)
/* VOICE����ͨ��SRCʹ�ܣ�ͬʱ����src��bypass��
0���ر�ʱ�ӣ�src bypass��
1����ʱ�ӣ�src ���������� */
#define    HISSC_VOICE_DLINK_SRC_EN_BIT_START  (7)
#define    HISSC_VOICE_DLINK_SRC_EN_BIT_END    (7)
/* S1 I2S�ӿڲ���ʱ��ʹ�ܡ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_S1_IF_CLK_EN_BIT_START        (8)
#define    HISSC_S1_IF_CLK_EN_BIT_END          (8)
/* I2S S1�ӿڣ�Digital FM���ӿ�������ͨ��PGAʱ��ʹ�ܣ�
0���ر�ʱ��
1����ʱ�� */
#define    HISSC_S1_IL_PGA_EN_BIT_START        (9)
#define    HISSC_S1_IL_PGA_EN_BIT_END          (9)
/* I2S S1�ӿڣ�Digital FM���ӿ�������ͨ��PGAʱ��ʹ�ܣ�
0���ر�ʱ��
1����ʱ�� */
#define    HISSC_S1_IR_PGA_EN_BIT_START        (10)
#define    HISSC_S1_IR_PGA_EN_BIT_END          (10)
/* I2S S2�ӿڣ�BT���ӿ�������ͨ��PGAʱ��ʹ�ܣ�
0���ر�ʱ��
1����ʱ�� */
#define    HISSC_S2_IL_PGA_EN_BIT_START        (12)
#define    HISSC_S2_IL_PGA_EN_BIT_END          (12)
/* I2S S2�ӿڣ�BT���ӿ�������ͨ��PGAʱ��ʹ�ܣ�
0���ر�ʱ��
1����ʱ�� */
#define    HISSC_S2_IR_PGA_EN_BIT_START        (13)
#define    HISSC_S2_IR_PGA_EN_BIT_END          (13)
/* I2S S2�ӿڣ�BT���ӿ������ͨ��SRCʱ��ʹ�ܣ�
0���ر�ʱ��
1����ʱ�� */
#define    HISSC_S2_OL_SRC_EN_BIT_START        (14)
#define    HISSC_S2_OL_SRC_EN_BIT_END          (14)
/* I2S S2�ӿڣ�BT���ӿ������ͨ��MIXERʱ��ʹ�ܣ�
0���ر�ʱ��
1����ʱ�� */
#define    HISSC_S2_OL_MIXER_EN_BIT_START      (15)
#define    HISSC_S2_OL_MIXER_EN_BIT_END        (15)
/* S2 I2S�ӿڲ���ʱ��ʹ�ܡ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_S2_IF_CLK_EN_BIT_START        (16)
#define    HISSC_S2_IF_CLK_EN_BIT_END          (16)
/* S3 I2S�ӿڲ���ʱ��ʹ�ܡ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_S3_IF_CLK_EN_BIT_START        (20)
#define    HISSC_S3_IF_CLK_EN_BIT_END          (20)
/* ������MODEAM����ͨ���첽FIFO��PGAʱ��ʹ��:
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_THIRDMD_DLINK_EN_BIT_START    (24)
#define    HISSC_THIRDMD_DLINK_EN_BIT_END      (24)
/* ������MODEAM����ͨ���첽FIFOʱ��ʹ��:
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_THIRDMD_UPLINK_EN_BIT_START   (25)
#define    HISSC_THIRDMD_UPLINK_EN_BIT_END     (25)


/* �Ĵ���˵���������˲���ͨ�����ģ��ʱ��ʹ�����ã�����DACL/DACR/ ADCL/ADCRͨ�� */
#define HISSC_DIG_FILTER_CLK_EN_CFG_ADDR              ((PAGE_SoCCODEC) + (0x08))
/* ADCLͨ��PGAģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_ADCL_PGA_EN_BIT_START      (0)
#define    HISSC_ADCL_PGA_EN_BIT_END        (0)
/* ADCLͨ��HPFģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_ADCL_HPF_EN_BIT_START      (1)
#define    HISSC_ADCL_HPF_EN_BIT_END        (1)
/* ADCLͨ��HBFVDģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_ADCL_HBFVD_EN_BIT_START    (2)
#define    HISSC_ADCL_HBFVD_EN_BIT_END      (2)
/* ADCLͨ��HBF2Dģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_ADCL_HBF2D_EN_BIT_START    (3)
#define    HISSC_ADCL_HBF2D_EN_BIT_END      (3)
/* ADCLͨ��COMPDģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_ADCL_COMPD_EN_BIT_START    (4)
#define    HISSC_ADCL_COMPD_EN_BIT_END      (4)
/* ADCLͨ��CICģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_ADCL_CIC_EN_BIT_START      (5)
#define    HISSC_ADCL_CIC_EN_BIT_END        (5)
/* SIDETONE PGAģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_SIDETONE_PGA_EN_BIT_START  (6)
#define    HISSC_SIDETONE_PGA_EN_BIT_END    (6)
/* ADCRͨ��PGAģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_ADCR_PGA_EN_BIT_START      (8)
#define    HISSC_ADCR_PGA_EN_BIT_END        (8)
/* ADCRͨ��HPFģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_ADCR_HPF_EN_BIT_START      (9)
#define    HISSC_ADCR_HPF_EN_BIT_END        (9)
/* ADCRͨ��HBFVDģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_ADCR_HBFVD_EN_BIT_START    (10)
#define    HISSC_ADCR_HBFVD_EN_BIT_END      (10)
/* ADCRͨ��HBF2Dģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_ADCR_HBF2D_EN_BIT_START    (11)
#define    HISSC_ADCR_HBF2D_EN_BIT_END      (11)
/* ADCRͨ��COMPDģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_ADCR_COMPD_EN_BIT_START    (12)
#define    HISSC_ADCR_COMPD_EN_BIT_END      (12)
/* ADCRͨ��CICģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_ADCR_CIC_EN_BIT_START      (13)
#define    HISSC_ADCR_CIC_EN_BIT_END        (13)
/* DACLͨ��AGCģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_DACL_AGC_EN_BIT_START      (16)
#define    HISSC_DACL_AGC_EN_BIT_END        (16)
/* DACLͨ��MIXERģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_DACL_MIXER_EN_BIT_START    (17)
#define    HISSC_DACL_MIXER_EN_BIT_END      (17)
/* DACLͨ��DEEMPģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_DACL_DEEMP_EN_BIT_START    (18)
#define    HISSC_DACL_DEEMP_EN_BIT_END      (18)
/* DACLͨ��HBF1Iģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_DACL_HBF1I_EN_BIT_START    (19)
#define    HISSC_DACL_HBF1I_EN_BIT_END      (19)
/* DACLͨ��HBF2Iģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_DACL_HBF2I_EN_BIT_START    (20)
#define    HISSC_DACL_HBF2I_EN_BIT_END      (20)
/* DACLͨ��COMPIģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_DACL_COMPI_EN_BIT_START    (21)
#define    HISSC_DACL_COMPI_EN_BIT_END      (21)
/* DACLͨ��SDMģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_DACL_SDM_EN_BIT_START      (22)
#define    HISSC_DACL_SDM_EN_BIT_END        (22)
/* DACRͨ��AGCģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_DACR_AGC_EN_BIT_START      (24)
#define    HISSC_DACR_AGC_EN_BIT_END        (24)
/* DACRͨ��MIXERģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_DACR_MIXER_EN_BIT_START    (25)
#define    HISSC_DACR_MIXER_EN_BIT_END      (25)
/* DACRͨ��DEEMPģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_DACR_DEEMP_EN_BIT_START    (26)
#define    HISSC_DACR_DEEMP_EN_BIT_END      (26)
/* DACRͨ��HBF1Iģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_DACR_HBF1I_EN_BIT_START    (27)
#define    HISSC_DACR_HBF1I_EN_BIT_END      (27)
/* DACRͨ��HBF2Iģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_DACR_HBF2I_EN_BIT_START    (28)
#define    HISSC_DACR_HBF2I_EN_BIT_END      (28)
/* DACRͨ��COMPIģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�bypass��
1����ʱ�ӡ� */
#define    HISSC_DACR_COMPI_EN_BIT_START    (29)
#define    HISSC_DACR_COMPI_EN_BIT_END      (29)
/* DACRͨ��SDMģ��ʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_DACR_SDM_EN_BIT_START      (30)
#define    HISSC_DACR_SDM_EN_BIT_END        (30)


/* �Ĵ���˵�������������� */
#define HISSC_FS_CFG_ADDR                             ((PAGE_SoCCODEC) + (0x0C))
/* VOICE����ͨ������������
0��8KHz�� 1��16KHz��
2��32KHz�� 3������
4��48KHz�� 5��96KHz��
6��192KHz��7������ */
#define    HISSC_FS_VOICE_DLINK_BIT_START     (0)
#define    HISSC_FS_VOICE_DLINK_BIT_END       (2)
/* STEREO������ͨ������������
0��8KHz�� 1��16KHz��
2��32KHz�� 3������
4��48KHz�� 5��96KHz��
6��192KHz��7������ */
#define    HISSC_FS_STEREO_DLINK_L_BIT_START  (4)
#define    HISSC_FS_STEREO_DLINK_L_BIT_END    (6)
/* STEREO������ͨ������������
0��8KHz�� 1��16KHz��
2��32KHz�� 3������
4��48KHz�� 5��96KHz��
6��192KHz��7������ */
#define    HISSC_FS_STEREO_DLINK_R_BIT_START  (8)
#define    HISSC_FS_STEREO_DLINK_R_BIT_END    (10)
/* dacl��dacrͨ����������������
0��8KHz�� 1��16KHz��
2��32KHz�� 3������
4��48KHz�� 5��96KHz��
6��192KHz��7������ */
#define    HISSC_FS_DACLR_BIT_START           (16)
#define    HISSC_FS_DACLR_BIT_END             (18)
/* adcl��adcrͨ����������������
0��8KHz�� 1��16KHz��
2��32KHz�� 3������
4��48KHz�� 5��96KHz��
6��192KHz��7������ */
#define    HISSC_FS_ADCLR_BIT_START           (20)
#define    HISSC_FS_ADCLR_BIT_END             (22)
/* S1�ӿڲ���������
0��8KHz�� 1��16KHz��
2��32KHz�� 3������
4��48KHz�� 5��96KHz��
6��192KHz��7������ */
#define    HISSC_FS_S1_BIT_START              (24)
#define    HISSC_FS_S1_BIT_END                (26)
/* S2�ӿڲ���������
0��8KHz�� 1��16KHz��
2��32KHz�� 3������
4��48KHz�� 5��96KHz��
6��192KHz��7������ */
#define    HISSC_FS_S2_BIT_START              (28)
#define    HISSC_FS_S2_BIT_END                (30)


/* �Ĵ���˵����S1/S2�ӿ����üĴ��� */
#define HISSC_I2S_CFG_ADDR                            ((PAGE_SoCCODEC) + (0x10))
/* S1�ӿ�ģʽѡ��
3'b000:I2S
3'b010:PCM STD
3'b011:PCM USER Defined
3'b100:Left Justified
3'b101:Right Justified
���������� */
#define    HISSC_S1_FUNC_MODE_BIT_START            (0)
#define    HISSC_S1_FUNC_MODE_BIT_END              (2)
/* S1�ӿ�Codec ADC/DAC���ݸ�ʽѡ��
0����ʾ�����Ʋ��룻
1����ʾ�������루binary offset���� */
#define    HISSC_S1_CODEC_DATA_FORMAT_BIT_START    (3)
#define    HISSC_S1_CODEC_DATA_FORMAT_BIT_END      (3)
/* S1�ӿ�RX����ʱ��ѡ��
1'b0:BCLK�����ؽ�������
1'b1:BCLK�½��ؽ������� */
#define    HISSC_S1_RX_CLK_SEL_BIT_START           (4)
#define    HISSC_S1_RX_CLK_SEL_BIT_END             (4)
/* S1�ӿ�TX����ʱ��ѡ��
1'b0:BCLK�����ش������
1'b1:BCLK�½��ش������ */
#define    HISSC_S1_TX_CLK_SEL_BIT_START           (5)
#define    HISSC_S1_TX_CLK_SEL_BIT_END             (5)
/* S1 I2S�ӿڻ���ģʽѡ��
2'b00����������ģʽ��
2'b01��Sdin->Sdout��
2'b10: RX_DATA[23:0] -> TX_IN[23:0]
2'b11: ���� */
#define    HISSC_S1_DIRECT_LOOP_BIT_START          (6)
#define    HISSC_S1_DIRECT_LOOP_BIT_END            (7)
/* S1�ӿ�λ�����ơ�
00��16bit��
01��18bit��
10��20bit��
11��24bit�� */
#define    HISSC_S1_CODEC_IO_WORDLENGTH_BIT_START  (8)
#define    HISSC_S1_CODEC_IO_WORDLENGTH_BIT_END    (9)
/* S1�ӿ��������ã�
1'b0:��������ǰ
1'b1:��������ǰ */
#define    HISSC_S1_CHNNL_MODE_BIT_START           (10)
#define    HISSC_S1_CHNNL_MODE_BIT_END             (10)
/* S1�ӿ�֡ͬ���ź���������ѡ��
1'b0:low -> left channel
1'b1:low -> right channel */
#define    HISSC_S1_LRCLK_MODE_BIT_START           (11)
#define    HISSC_S1_LRCLK_MODE_BIT_END             (11)
/* S1�ӿ�Master/Slaveģʽѡ��
1'b0:Materģʽ����masterģʽ��BCLK/SYNC�ſ������
1'b1:Slaveģʽ */
#define    HISSC_S1_MST_SLV_BIT_START              (12)
#define    HISSC_S1_MST_SLV_BIT_END                (12)
/* S1�ӿ�I2Sģʽ��֡��ʽ���ã�
1'b0:I2Sģʽ��64bit frame��PCMģʽ��32bit frame
1'b1:I2Sģʽ��32bit frame��PCMģʽ��16bit frame */
#define    HISSC_S1_FRAME_MODE_BIT_START           (13)
#define    HISSC_S1_FRAME_MODE_BIT_END             (13)
/* S1�ӿ�RX����ʹ�ܣ�
1'b1:ʹ��
1'b0:�ر� */
#define    HISSC_S1_IF_RX_ENA_BIT_START            (14)
#define    HISSC_S1_IF_RX_ENA_BIT_END              (14)
/* S1�ӿ�TX����ʹ�ܣ�
1'b1:ʹ��
1'b0:�ر� */
#define    HISSC_S1_IF_TX_ENA_BIT_START            (15)
#define    HISSC_S1_IF_TX_ENA_BIT_END              (15)
/* S2�ӿ�ģʽѡ��
3'b000:I2S
3'b010:PCM STD
3'b011:PCM USER Defined
3'b100:Left Justified
3'b101:Right Justified
���������� */
#define    HISSC_S2_FUNC_MODE_BIT_START            (16)
#define    HISSC_S2_FUNC_MODE_BIT_END              (18)
/* S2�ӿ�Codec ADC/DAC���ݸ�ʽѡ��
0����ʾ�����Ʋ��룻
1����ʾ�������루binary offset���� */
#define    HISSC_S2_CODEC_DATA_FORMAT_BIT_START    (19)
#define    HISSC_S2_CODEC_DATA_FORMAT_BIT_END      (19)
/* S2�ӿ�RX����ʱ��ѡ��
1'b0:BCLK�����ؽ�������
1'b1:BCLK�½��ؽ������� */
#define    HISSC_S2_RX_CLK_SEL_BIT_START           (20)
#define    HISSC_S2_RX_CLK_SEL_BIT_END             (20)
/* S2�ӿ�TX����ʱ��ѡ��
1'b0:BCLK�����ش������
1'b1:BCLK�½��ش������ */
#define    HISSC_S2_TX_CLK_SEL_BIT_START           (21)
#define    HISSC_S2_TX_CLK_SEL_BIT_END             (21)
/* S2 I2S�ӿڻ���ģʽѡ��
2'b00����������ģʽ��
2'b01��Sdin->Sdout��
2'b10: RX_DATA[23:0] -> TX_IN[23:0]
2'b11: ���� */
#define    HISSC_S2_DIRECT_LOOP_BIT_START          (22)
#define    HISSC_S2_DIRECT_LOOP_BIT_END            (23)
/* S2�ӿ�λ�����ơ�
00��16bit��
01��18bit��
10��20bit��
11��24bit�� */
#define    HISSC_S2_CODEC_IO_WORDLENGTH_BIT_START  (24)
#define    HISSC_S2_CODEC_IO_WORDLENGTH_BIT_END    (25)
/* S2�ӿ��������ã�
1'b0:��������ǰ
1'b1:��������ǰ */
#define    HISSC_S2_CHNNL_MODE_BIT_START           (26)
#define    HISSC_S2_CHNNL_MODE_BIT_END             (26)
/* S2�ӿ�֡ͬ���ź���������ѡ��
1'b0:low -> left channel
1'b1:low -> right channel */
#define    HISSC_S2_LRCLK_MODE_BIT_START           (27)
#define    HISSC_S2_LRCLK_MODE_BIT_END             (27)
/* S2�ӿ�Master/Slaveģʽѡ��
1'b0:Materģʽ����masterģʽ��BCLK/SYNC�ſ������
1'b1:Slaveģʽ */
#define    HISSC_S2_MST_SLV_BIT_START              (28)
#define    HISSC_S2_MST_SLV_BIT_END                (28)
/* S2�ӿ�I2Sģʽ��֡��ʽ���ã�
1'b0:I2Sģʽ��64bit frame��PCMģʽ��32bit frame
1'b1:I2Sģʽ��32bit frame��PCMģʽ��16bit frame */
#define    HISSC_S2_FRAME_MODE_BIT_START           (29)
#define    HISSC_S2_FRAME_MODE_BIT_END             (29)
/* S2�ӿ�RX����ʹ�ܣ�
1'b1:ʹ��
1'b0:�ر� */
#define    HISSC_S2_IF_RX_ENA_BIT_START            (30)
#define    HISSC_S2_IF_RX_ENA_BIT_END              (30)
/* S2�ӿ�TX����ʹ�ܣ�
1'b1:ʹ��
1'b0:�ر� */
#define    HISSC_S2_IF_TX_ENA_BIT_START            (31)
#define    HISSC_S2_IF_TX_ENA_BIT_END              (31)


/* �Ĵ���˵����DAC/ADCͨ���ڲ�MIXER��ģ��BYPASSģʽ���üĴ����� */
#define HISSC_DIG_FILTER_MODULE_CFG_ADDR              ((PAGE_SoCCODEC) + (0x14))
/* ADCRͨ��CIC�˲������ػ�·�����ơ�
000��CIC����ΪADC·�����룻
001��CIC����ΪDACL·�����룻
010��CIC����ΪDACR·�����룻
011��reserved��
100��CIC����ΪDMIC PORT0·�����룻
101��reserved��
����ֵ��ADC·�����롣 */
#define    HISSC_RM_CODEC_DAC2ADC_BIT_START     (0)
#define    HISSC_RM_CODEC_DAC2ADC_BIT_END       (2)
/* ADCLͨ��CIC�˲������ػ�·�����ơ�
000��CIC����ΪADC·�����룻
001��CIC����ΪDACL·�����룻
010��CIC����ΪDACR·�����룻
011��reserved��
100��CIC����ΪDMIC PORT0·�����룻
101��reserved��
����ֵ��ADC·�����롣 */
#define    HISSC_LM_CODEC_DAC2ADC_BIT_START     (4)
#define    HISSC_LM_CODEC_DAC2ADC_BIT_END       (6)
/* DACL SDM dither���á�
1��dither��·��Ч��
0��dither��·��Ч�� */
#define    HISSC_SW_DACL_SDM_DITHER_BIT_START   (8)
#define    HISSC_SW_DACL_SDM_DITHER_BIT_END     (8)
/* DACR SDM dither���á�
1��dither��·��Ч��
0��dither��·��Ч�� */
#define    HISSC_SW_DACR_SDM_DITHER_BIT_START   (9)
#define    HISSC_SW_DACR_SDM_DITHER_BIT_END     (9)
/* DACLͨ��mixer��muteʹ�ܣ�
1'b1:voice dlink src���mute
1'b0:�������� */
#define    HISSC_DACL_MIXER_IN1_MUTE_BIT_START  (16)
#define    HISSC_DACL_MIXER_IN1_MUTE_BIT_END    (16)
/* DACLͨ��mixer��muteʹ�ܣ�
1'b1:stereo dlink��ͨ��pga���mute
1'b0:��������
master:dacl_mixer_en */
#define    HISSC_DACL_MIXER_IN2_MUTE_BIT_START  (17)
#define    HISSC_DACL_MIXER_IN2_MUTE_BIT_END    (17)
/* DACLͨ��mixer�� muteʹ�ܣ�
1'b1:s1������ͨ��pga���mute
1'b0:�������� */
#define    HISSC_DACL_MIXER_IN3_MUTE_BIT_START  (18)
#define    HISSC_DACL_MIXER_IN3_MUTE_BIT_END    (18)
/* DACLͨ��mixer muteʹ�ܣ�
1'b1:sidetone pga ���mute
1'b0:�������� */
#define    HISSC_DACL_MIXER_IN4_MUTE_BIT_START  (19)
#define    HISSC_DACL_MIXER_IN4_MUTE_BIT_END    (19)
/* DACLͨ��MIXER���������ã�
2'b00:1
2'b01:����1/2
2'b10:����1/4
2'b11:���� */
#define    HISSC_DACL_MIXER_GAIN_BIT_START      (20)
#define    HISSC_DACL_MIXER_GAIN_BIT_END        (21)
/* DACRͨ��mixer��muteʹ�ܣ�
1'b1:voice dlink src���mute
1'b0:�������� */
#define    HISSC_DACR_MIXER_IN1_MUTE_BIT_START  (24)
#define    HISSC_DACR_MIXER_IN1_MUTE_BIT_END    (24)
/* DACRͨ��mixer��muteʹ�ܣ�
1'b1:stereo dlink��ͨ��pga���mute
1'b0:�������� */
#define    HISSC_DACR_MIXER_IN2_MUTE_BIT_START  (25)
#define    HISSC_DACR_MIXER_IN2_MUTE_BIT_END    (25)
/* DACRͨ��mixer�� muteʹ�ܣ�
1'b1:s1������ͨ��pga���mute
1'b0:�������� */
#define    HISSC_DACR_MIXER_IN3_MUTE_BIT_START  (26)
#define    HISSC_DACR_MIXER_IN3_MUTE_BIT_END    (26)
/* DACRͨ��mixer muteʹ�ܣ�
1'b1:sidetone pga ���mutemute
1'b0:�������� */
#define    HISSC_DACR_MIXER_IN4_MUTE_BIT_START  (27)
#define    HISSC_DACR_MIXER_IN4_MUTE_BIT_END    (27)
/* DACRͨ��MIXER���������ã�
2'b00:1
2'b01:����1/2
2'b10:����1/4
2'b11:���� */
#define    HISSC_DACR_MIXER_GAIN_BIT_START      (28)
#define    HISSC_DACR_MIXER_GAIN_BIT_END        (29)


/* �Ĵ���˵����MUX_TOP�����ģ�����ü�״̬ */
#define HISSC_MUX_TOP_MODULE_CFG_ADDR                 ((PAGE_SoCCODEC) + (0x18))
/* VOICE����ͨ��SRC MODEѡ��
3'b001: 12 interpolation
3'b010: 6 interpolation
3'b011: 2 interpolation
3'b100: 3 interpolation
other: reserved, not work */
#define    HISSC_VOICE_DLINK_SRC_MODE_BIT_START        (0)
#define    HISSC_VOICE_DLINK_SRC_MODE_BIT_END          (2)
/* VOICE����ͨ��SRC READY�źţ�
1'b1:SRC RAM��ʼ�����
1'b0:SRC RAM��ʼ�������У���������ĸüĴ��������ඪʧһ�������㣩 */
#define    HISSC_VOICE_DLINK_SRC_RDY_BIT_START         (3)
#define    HISSC_VOICE_DLINK_SRC_RDY_BIT_END           (3)
/* S2 I2S�ӿ�SRC MODEѡ��
2'b00: 3��������
2'b01:12��������
2'b10:6��������
2'b11:2�������� */
#define    HISSC_S2_OL_SRC_MODE_BIT_START              (4)
#define    HISSC_S2_OL_SRC_MODE_BIT_END                (5)
/* S2 I2S�ӿ�������ͨ��SRC READY�źţ�
1'b1:SRC RAM��ʼ�����
1'b0:SRC RAM��ʼ�������У���������ĸüĴ��������ඪʧһ�������㣩 */
#define    HISSC_S2_OL_SRC_RDY_BIT_START               (6)
#define    HISSC_S2_OL_SRC_RDY_BIT_END                 (6)
/* S2�ӿ������ͨ��mixer���muteʹ�ܣ�
1'b1: DACL mixer ���mute
1'b0:�������� */
#define    HISSC_S2_OL_MIXER_IN1_MUTE_BIT_START        (8)
#define    HISSC_S2_OL_MIXER_IN1_MUTE_BIT_END          (8)
/* S2�ӿ������ͨ��mixer���muteʹ�ܣ�
1'b1:DACR mixer ���mute
1'b0:�������� */
#define    HISSC_S2_OL_MIXER_IN2_MUTE_BIT_START        (9)
#define    HISSC_S2_OL_MIXER_IN2_MUTE_BIT_END          (9)
/* S2�����ͨ��MIXER���������ã�
2'b00:1
2'b01:����1/2
2'b10:����
2'b11:���� */
#define    HISSC_S2_OL_MIXER_GAIN_BIT_START            (10)
#define    HISSC_S2_OL_MIXER_GAIN_BIT_END              (11)
/* voice downlink ͨ��mixer���muteʹ�ܣ�
1'b1: DACL mixer ���mute
1'b0:�������� */
#define    HISSC_VOICE_DLINK_MIXER_IN1_MUTE_BIT_START  (12)
#define    HISSC_VOICE_DLINK_MIXER_IN1_MUTE_BIT_END    (12)
/* voice downlink ͨ��mixer���muteʹ�ܣ�
1'b1:DACR mixer ���mute
1'b0:�������� */
#define    HISSC_VOICE_DLINK_MIXER_IN2_MUTE_BIT_START  (13)
#define    HISSC_VOICE_DLINK_MIXER_IN2_MUTE_BIT_END    (13)
/* voice downlink ͨ��MIXER���������ã�
2'b00:1
2'b01:����1/2
2'b10:����
2'b11:���� */
#define    HISSC_VOICE_DLINK_MIXER_GAIN_BIT_START      (14)
#define    HISSC_VOICE_DLINK_MIXER_GAIN_BIT_END        (15)


/* �Ĵ���˵����ADCͨ��PGAģ������ */
#define HISSC_ADC_PGA_CFG_ADDR                        ((PAGE_SoCCODEC) + (0x1C))
/* ADCL pga���������������:
Ĭ�ϣ�0dB
���淶Χ:-72dB~+36dB��
����
0010_0100:36dB
0010_0011:35dB
����
1011_1000��-72dB
����Ϊ1dB,�����ʾ��
�㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
#define    HISSC_ADCL_PGA_INTEGER_CONFIG_BIT_START  (0)
#define    HISSC_ADCL_PGA_INTEGER_CONFIG_BIT_END    (7)
/* ADCL pga��������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_ADCL_PGA_FRAC_CONFIG_BIT_START     (8)
#define    HISSC_ADCL_PGA_FRAC_CONFIG_BIT_END       (8)
/* ADCL pga muteʹ�ܣ�
1'b1: mute��Ч�����0
1'b0: �ر�mute */
#define    HISSC_ADCL_PGA_MUTE_BIT_START            (9)
#define    HISSC_ADCL_PGA_MUTE_BIT_END              (9)
/* ADCL pga������͵�ƽ�������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_ADCL_PGA_THR_CONFIG_BIT_START      (12)
#define    HISSC_ADCL_PGA_THR_CONFIG_BIT_END        (13)
/* ADCR pga���������������:
Ĭ�ϣ�0dB
���淶Χ:-72dB~+36dB��
����
0010_0100:36dB
0010_0011:35dB
����
1011_1000��-72dB
����Ϊ1dB,�����ʾ��
�㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
#define    HISSC_ADCR_PGA_INTEGER_CONFIG_BIT_START  (16)
#define    HISSC_ADCR_PGA_INTEGER_CONFIG_BIT_END    (23)
/* ADCR pga��������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_ADCR_PGA_FRAC_CONFIG_BIT_START     (24)
#define    HISSC_ADCR_PGA_FRAC_CONFIG_BIT_END       (24)
/* ADCR pga muteʹ�ܣ�
1'b1: mute��Ч�����0
1'b0: �ر�mute */
#define    HISSC_ADCR_PGA_MUTE_BIT_START            (25)
#define    HISSC_ADCR_PGA_MUTE_BIT_END              (25)
/* ADCR pga������͵�ƽ�������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_ADCR_PGA_THR_CONFIG_BIT_START      (28)
#define    HISSC_ADCR_PGA_THR_CONFIG_BIT_END        (29)


/* �Ĵ���˵����S1�ӿ�����ͨ��PGA���� */
#define HISSC_S1_INPUT_PGA_CFG_ADDR                   ((PAGE_SoCCODEC) + (0x20))
/* S1 I2S�ӿ�������ͨ��pga���������������:
Ĭ�ϣ�0dB
���淶Χ:-72dB~+36dB��
����
0010_0100:36dB
0010_0011:35dB
����
1011_1000��-72dB
����Ϊ1dB,�����ʾ��
�㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
#define    HISSC_S1_IL_PGA_INTEGER_CONFIG_BIT_START  (0)
#define    HISSC_S1_IL_PGA_INTEGER_CONFIG_BIT_END    (7)
/* S1�ӿ� ������ͨ��pga��������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_S1_IL_PGA_FRAC_CONFIG_BIT_START     (8)
#define    HISSC_S1_IL_PGA_FRAC_CONFIG_BIT_END       (8)
/* S1�ӿ�������ͨ��pga muteʹ�ܣ�
1'b1: mute��Ч�����0
1'b0: �ر�mute */
#define    HISSC_S1_IL_PGA_MUTE_BIT_START            (9)
#define    HISSC_S1_IL_PGA_MUTE_BIT_END              (9)
/* S1�ӿ�������ͨ��pga������͵�ƽ�������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_S1_IL_PGA_THR_CONFIG_BIT_START      (12)
#define    HISSC_S1_IL_PGA_THR_CONFIG_BIT_END        (13)
/* S1 I2S�ӿ�������ͨ��pga���������������:
Ĭ�ϣ�0dB
���淶Χ:-72dB~+36dB��
����
0010_0100:36dB
0010_0011:35dB
����
1011_1000��-72dB
����Ϊ1dB,�����ʾ��
�㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
#define    HISSC_S1_IR_PGA_INTEGER_CONFIG_BIT_START  (16)
#define    HISSC_S1_IR_PGA_INTEGER_CONFIG_BIT_END    (23)
/* S1�ӿ�������ͨ��pga��������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_S1_IR_PGA_FRAC_CONFIG_BIT_START     (24)
#define    HISSC_S1_IR_PGA_FRAC_CONFIG_BIT_END       (24)
/* S1�ӿ�������ͨ��pga muteʹ�ܣ�
1'b1: mute��Ч�����0
1'b0: �ر�mute */
#define    HISSC_S1_IR_PGA_MUTE_BIT_START            (25)
#define    HISSC_S1_IR_PGA_MUTE_BIT_END              (25)
/* S1�ӿ�������ͨ��pga������͵�ƽ�������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_S1_IR_PGA_THR_CONFIG_BIT_START      (28)
#define    HISSC_S1_IR_PGA_THR_CONFIG_BIT_END        (29)


/* �Ĵ���˵����S2�ӿ�����ͨ��PGA���� */
#define HISSC_S2_INPUT_PGA_CFG_ADDR                   ((PAGE_SoCCODEC) + (0x24))
/* S2 I2S�ӿ�������ͨ��pga���������������:
Ĭ�ϣ�0dB
���淶Χ:-72dB~+36dB��
����
0010_0100:36dB
0010_0011:35dB
����
1011_1000��-72dB
����Ϊ1dB,�����ʾ��
�㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
#define    HISSC_S2_IL_PGA_INTEGER_CONFIG_BIT_START  (0)
#define    HISSC_S2_IL_PGA_INTEGER_CONFIG_BIT_END    (7)
/* S2�ӿ� ������ͨ��pga��������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_S2_IL_PGA_FRAC_CONFIG_BIT_START     (8)
#define    HISSC_S2_IL_PGA_FRAC_CONFIG_BIT_END       (8)
/* S2�ӿ�������ͨ��pga muteʹ�ܣ�
1'b1: mute��Ч�����0
1'b0: �ر�mute */
#define    HISSC_S2_IL_PGA_MUTE_BIT_START            (9)
#define    HISSC_S2_IL_PGA_MUTE_BIT_END              (9)
/* S2�ӿ�������ͨ��pga������͵�ƽ�������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_S2_IL_PGA_THR_CONFIG_BIT_START      (12)
#define    HISSC_S2_IL_PGA_THR_CONFIG_BIT_END        (13)
/* S2 I2S�ӿ�������ͨ��pga���������������:
Ĭ�ϣ�0dB
���淶Χ:-72dB~+36dB��
����
0010_0100:36dB
0010_0011:35dB
����
1011_1000��-72dB
����Ϊ1dB,�����ʾ��
�㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
#define    HISSC_S2_IR_PGA_INTEGER_CONFIG_BIT_START  (16)
#define    HISSC_S2_IR_PGA_INTEGER_CONFIG_BIT_END    (23)
/* S2�ӿ�������ͨ��pga��������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_S2_IR_PGA_FRAC_CONFIG_BIT_START     (24)
#define    HISSC_S2_IR_PGA_FRAC_CONFIG_BIT_END       (24)
/* S2�ӿ�������ͨ��pga muteʹ�ܣ�
1'b1: mute��Ч�����0
1'b0: �ر�mute */
#define    HISSC_S2_IR_PGA_MUTE_BIT_START            (25)
#define    HISSC_S2_IR_PGA_MUTE_BIT_END              (25)
/* S2�ӿ�������ͨ��pga������͵�ƽ�������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_S2_IR_PGA_THR_CONFIG_BIT_START      (28)
#define    HISSC_S2_IR_PGA_THR_CONFIG_BIT_END        (29)


/* �Ĵ���˵����STEREO����ͨ��PGA���� */
#define HISSC_STEREO_DLINK_PGA_CFG_ADDR               ((PAGE_SoCCODEC) + (0x28))
/* stereo����������pga���������������:
Ĭ�ϣ�0dB
���淶Χ:-72dB~+36dB��
����
0010_0100:36dB
0010_0011:35dB
����
1011_1000��-72dB
����Ϊ1dB,�����ʾ��
�㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
#define    HISSC_STEREO_DLINK_L_PGA_INTEGER_CONFIG_BIT_START  (0)
#define    HISSC_STEREO_DLINK_L_PGA_INTEGER_CONFIG_BIT_END    (7)
/* stereo����������pga��������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_STEREO_DLINK_L_PGA_FRAC_CONFIG_BIT_START     (8)
#define    HISSC_STEREO_DLINK_L_PGA_FRAC_CONFIG_BIT_END       (8)
/* stereo����������pga muteʹ�ܣ�
1'b1: mute��Ч�����0
1'b0: �ر�mute */
#define    HISSC_STEREO_DLINK_L_PGA_MUTE_BIT_START            (9)
#define    HISSC_STEREO_DLINK_L_PGA_MUTE_BIT_END              (9)
/* stereo����������pga������͵�ƽ�������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_STEREO_DLINK_L_PGA_THR_CONFIG_BIT_START      (12)
#define    HISSC_STEREO_DLINK_L_PGA_THR_CONFIG_BIT_END        (13)
/* stereo����������pga���������������:
Ĭ�ϣ�0dB
���淶Χ:-72dB~+36dB��
����
0010_0100:36dB
0010_0011:35dB
����
1011_1000��-72dB
����Ϊ1dB,�����ʾ��
�㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
#define    HISSC_STEREO_DLINK_R_PGA_INTEGER_CONFIG_BIT_START  (16)
#define    HISSC_STEREO_DLINK_R_PGA_INTEGER_CONFIG_BIT_END    (23)
/* stereo����������pga��������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_STEREO_DLINK_R_PGA_FRAC_CONFIG_BIT_START     (24)
#define    HISSC_STEREO_DLINK_R_PGA_FRAC_CONFIG_BIT_END       (24)
/* stereo����������pga muteʹ�ܣ�
1'b1: mute��Ч�����0
1'b0: �ر�mute */
#define    HISSC_STEREO_DLINK_R_PGA_MUTE_BIT_START            (25)
#define    HISSC_STEREO_DLINK_R_PGA_MUTE_BIT_END              (25)
/* stereo����������pga������͵�ƽ�������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_STEREO_DLINK_R_PGA_THR_CONFIG_BIT_START      (28)
#define    HISSC_STEREO_DLINK_R_PGA_THR_CONFIG_BIT_END        (29)


/* �Ĵ���˵����VOICE����ͨ��PGA��SIDETONE PGA���� */
#define HISSC_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR       ((PAGE_SoCCODEC) + (0x2C))
/* VOICE����ͨ��pga�������������������:
Ĭ�ϣ�0dB
���淶Χ:-72dB~+36dB��
����
0010_0100:36dB
0010_0011:35dB
����
1011_1000��-72dB
����Ϊ1dB,�����ʾ�� */
#define    HISSC_VOICE_DLINK_PGA_INTEGER_CONFIG_BIT_START  (0)
#define    HISSC_VOICE_DLINK_PGA_INTEGER_CONFIG_BIT_END    (7)
/* VOICE����ͨ��pga��������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_VOICE_DLINK_PGA_FRAC_CONFIG_BIT_START     (8)
#define    HISSC_VOICE_DLINK_PGA_FRAC_CONFIG_BIT_END       (8)
/* voice��������pga muteʹ�ܣ�
1'b1: mute��Ч�����0
1'b0: �ر�mute */
#define    HISSC_VOICE_DLINK_PGA_MUTE_BIT_START            (9)
#define    HISSC_VOICE_DLINK_PGA_MUTE_BIT_END              (9)
/* voice dlinkͨ��pga������͵�ƽ�������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_VOICE_DLINK_PGA_THR_CONFIG_BIT_START      (12)
#define    HISSC_VOICE_DLINK_PGA_THR_CONFIG_BIT_END        (13)
/* SIDETONE pga�������������������:
Ĭ�ϣ�0dB
���淶Χ:-72dB~+36dB��
����
0010_0100:36dB
0010_0011:35dB
����
1011_1000��-72dB
����Ϊ1dB,�����ʾ�� */
#define    HISSC_SIDETONE_PGA_INTEGER_CONFIG_BIT_START     (16)
#define    HISSC_SIDETONE_PGA_INTEGER_CONFIG_BIT_END       (23)
/* SIDETONE pga��������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_SIDETONE_PGA_FRAC_CONFIG_BIT_START        (24)
#define    HISSC_SIDETONE_PGA_FRAC_CONFIG_BIT_END          (24)
/* SIDETONE pga muteʹ�ܣ�
1'b1: mute��Ч�����0
1'b0: �ر�mute */
#define    HISSC_SIDETONE_PGA_MUTE_BIT_START               (25)
#define    HISSC_SIDETONE_PGA_MUTE_BIT_END                 (25)
/* sidetone pga������͵�ƽ�������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_SIDETONE_PGA_THR_CONFIG_BIT_START         (28)
#define    HISSC_SIDETONE_PGA_THR_CONFIG_BIT_END           (29)


/* �Ĵ���˵����APB IF��AFIFO���ü�״̬�ź� */
#define HISSC_APB_AFIFO_CFG_1_ADDR                    ((PAGE_SoCCODEC) + (0x30))
/* STEREO UPLINK��ͨ��AFIFO������ã�
1'b1: clr��Ч�����FIFO����
1'b0: clr��Ч */
#define    HISSC_STEREO_UPLINK_L_FIFO_CLR_BIT_START     (0)
#define    HISSC_STEREO_UPLINK_L_FIFO_CLR_BIT_END       (0)
/* STEREO UPLINK��ͨ��AFIFO������ã�
1'b1: clr��Ч�����FIFO����
1'b0: clr��Ч */
#define    HISSC_STEREO_UPLINK_R_FIFO_CLR_BIT_START     (1)
#define    HISSC_STEREO_UPLINK_R_FIFO_CLR_BIT_END       (1)
/* VOICE UPLINK��ͨ��AFIFO������ã�
1'b1: clr��Ч�����FIFO����
1'b0: clr��Ч */
#define    HISSC_VOICE_UPLINK_L_FIFO_CLR_BIT_START      (2)
#define    HISSC_VOICE_UPLINK_L_FIFO_CLR_BIT_END        (2)
/* VOICE UPLINK��ͨ��AFIFO������ã�
1'b1: clr��Ч�����FIFO����
1'b0: clr��Ч */
#define    HISSC_VOICE_UPLINK_R_FIFO_CLR_BIT_START      (3)
#define    HISSC_VOICE_UPLINK_R_FIFO_CLR_BIT_END        (3)
/* STEREO DLINK��ͨ��AFIFO������ã�
1'b1: clr��Ч�����FIFO����
1'b0: clr��Ч */
#define    HISSC_STEREO_DLINK_L_FIFO_CLR_BIT_START      (4)
#define    HISSC_STEREO_DLINK_L_FIFO_CLR_BIT_END        (4)
/* STEREO DLINK��ͨ��AFIFO������ã�
1'b1: clr��Ч�����FIFO����
1'b0: clr��Ч */
#define    HISSC_STEREO_DLINK_R_FIFO_CLR_BIT_START      (5)
#define    HISSC_STEREO_DLINK_R_FIFO_CLR_BIT_END        (5)
/* VOICE DLINKͨ��AFIFO������ã�
1'b1:clr��Ч�����FIFO����
1'b0: clr��Ч */
#define    HISSC_VOICE_DLINK_FIFO_CLR_BIT_START         (6)
#define    HISSC_VOICE_DLINK_FIFO_CLR_BIT_END           (6)
/*  */
#define    HISSC_THIRDMD_DLINK_FIFO_CLR_BIT_START       (7)
#define    HISSC_THIRDMD_DLINK_FIFO_CLR_BIT_END         (7)
/*  */
#define    HISSC_THIRDMD_UPLINK_FIFO_CLR_BIT_START      (8)
#define    HISSC_THIRDMD_UPLINK_FIFO_CLR_BIT_END        (8)
/* STEREO UPLINK��ͨ��AFIFOдerror
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_STEREO_UPLINK_L_FIFO_WERROR_BIT_START  (16)
#define    HISSC_STEREO_UPLINK_L_FIFO_WERROR_BIT_END    (16)
/* STEREO UPLINK��ͨ��AFIFOдerror
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_STEREO_UPLINK_R_FIFO_WERROR_BIT_START  (17)
#define    HISSC_STEREO_UPLINK_R_FIFO_WERROR_BIT_END    (17)
/* VOICE UPLINK��ͨ��AFIFOдerror
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_VOICE_UPLINK_L_FIFO_WERROR_BIT_START   (18)
#define    HISSC_VOICE_UPLINK_L_FIFO_WERROR_BIT_END     (18)
/* VOICE UPLINK��ͨ��AFIFOдerror
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_VOICE_UPLINK_R_FIFO_WERROR_BIT_START   (19)
#define    HISSC_VOICE_UPLINK_R_FIFO_WERROR_BIT_END     (19)
/* STEREO DLINK��ͨ��AFIFOдerror
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_STEREO_DLINK_L_FIFO_WERROR_BIT_START   (20)
#define    HISSC_STEREO_DLINK_L_FIFO_WERROR_BIT_END     (20)
/* STEREO DLINK��ͨ��AFIFOдerror
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_STEREO_DLINK_R_FIFO_WERROR_BIT_START   (21)
#define    HISSC_STEREO_DLINK_R_FIFO_WERROR_BIT_END     (21)
/* VOICE DLINKͨ��AFIFOдerror
1'b1: FIFO��ʱд����
1'b0: ���� */
#define    HISSC_VOICE_DLINK_FIFO_WERROR_BIT_START      (22)
#define    HISSC_VOICE_DLINK_FIFO_WERROR_BIT_END        (22)
/* STEREO UPLINK��ͨ��AFIFO��error
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_STEREO_UPLINK_L_FIFO_RERROR_BIT_START  (24)
#define    HISSC_STEREO_UPLINK_L_FIFO_RERROR_BIT_END    (24)
/* STEREO UPLINK��ͨ��AFIFO��error
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_STEREO_UPLINK_R_FIFO_RERROR_BIT_START  (25)
#define    HISSC_STEREO_UPLINK_R_FIFO_RERROR_BIT_END    (25)
/* VOICE UPLINK��ͨ��AFIFO��error
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_VOICE_UPLINK_L_FIFO_RERROR_BIT_START   (26)
#define    HISSC_VOICE_UPLINK_L_FIFO_RERROR_BIT_END     (26)
/* VOICE UPLINK��ͨ��AFIFO��error
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_VOICE_UPLINK_R_FIFO_RERROR_BIT_START   (27)
#define    HISSC_VOICE_UPLINK_R_FIFO_RERROR_BIT_END     (27)
/* STEREO DLINK��ͨ��AFIFO��error
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_STEREO_DLINK_L_FIFO_RERROR_BIT_START   (28)
#define    HISSC_STEREO_DLINK_L_FIFO_RERROR_BIT_END     (28)
/* STEREO DLINK��ͨ��AFIFO��error
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_STEREO_DLINK_R_FIFO_RERROR_BIT_START   (29)
#define    HISSC_STEREO_DLINK_R_FIFO_RERROR_BIT_END     (29)
/* VOICE DLINKͨ��AFIFO��error
1'b1: FIFO��ʱ������
1'b0: ���� */
#define    HISSC_VOICE_DLINK_FIFO_RERROR_BIT_START      (30)
#define    HISSC_VOICE_DLINK_FIFO_RERROR_BIT_END        (30)


/* �Ĵ���˵����APB IF��AFIFO���ü�״̬�ź� */
#define HISSC_APB_AFIFO_CFG_2_ADDR                    ((PAGE_SoCCODEC) + (0x34))
/* VOICE DLINKͨ��AFIFO������ֵ��fifo����Ч��ֵ�������ڸ�ֵʱ��FIFO almost full�ź���Ч */
#define    HISSC_VOICE_DLINK_FIFO_AFULL_TH_BIT_START     (0)
#define    HISSC_VOICE_DLINK_FIFO_AFULL_TH_BIT_END       (4)
/* VOICE DLINKͨ��AFIFO������ֵ��fifo����Ч��ֵ�������ڸ�ֵʱ��FIFO almost empty�ź���Ч */
#define    HISSC_VOICE_DLINK_FIFO_AEMPTY_TH_BIT_START    (8)
#define    HISSC_VOICE_DLINK_FIFO_AEMPTY_TH_BIT_END      (12)
/* STEREO UPLINK��ͨ��AFIFO��������ѡ��
1'b1:ADCLͨ���������
1'b0:S1�ӿ����������� */
#define    HISSC_STEREO_UPLINK_L_FIFO_DIN_SEL_BIT_START  (16)
#define    HISSC_STEREO_UPLINK_L_FIFO_DIN_SEL_BIT_END    (16)
/* STEREO UPLINK��ͨ��AFIFO��������ѡ��
1'b1:ADCRͨ���������
1'b0:S1�ӿ����������� */
#define    HISSC_STEREO_UPLINK_R_FIFO_DIN_SEL_BIT_START  (17)
#define    HISSC_STEREO_UPLINK_R_FIFO_DIN_SEL_BIT_END    (17)
/* VOICE UPLINK��ͨ��AFIFO��������ѡ��
1'b1:ADCLͨ���������
1'b0:S2�ӿ����������� */
#define    HISSC_VOICE_UPLINK_L_FIFO_DIN_SEL_BIT_START   (18)
#define    HISSC_VOICE_UPLINK_L_FIFO_DIN_SEL_BIT_END     (18)
/* VOICE UPLINK��ͨ��AFIFO��������ѡ��
1'b1:ADCRͨ���������
1'b0:S2�ӿ����������� */
#define    HISSC_VOICE_UPLINK_R_FIFO_DIN_SEL_BIT_START   (19)
#define    HISSC_VOICE_UPLINK_R_FIFO_DIN_SEL_BIT_END     (19)
/* ������MODEM UPLINKͨ��AFIFO��������ѡ��
1'b1:ADCRͨ���������
1'b0:S3�ӿ��������� */
#define    HISSC_THIRDMD_UPLINK_DIN_SEL_BIT_START        (20)
#define    HISSC_THIRDMD_UPLINK_DIN_SEL_BIT_END          (20)


/* �Ĵ���˵����STEREO����ͨ��AFIFO ����ˮ������ */
#define HISSC_STEREO_DLINK_FIFO_TH_CFG_ADDR           ((PAGE_SoCCODEC) + (0x38))
/* STEREO DLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_STEREO_DLINK_L_FIFO_AFULL_TH_BIT_START   (0)
#define    HISSC_STEREO_DLINK_L_FIFO_AFULL_TH_BIT_END     (4)
/* STEREO DLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_STEREO_DLINK_L_FIFO_AEMPTY_TH_BIT_START  (8)
#define    HISSC_STEREO_DLINK_L_FIFO_AEMPTY_TH_BIT_END    (12)
/* STEREO DLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_STEREO_DLINK_R_FIFO_AFULL_TH_BIT_START   (16)
#define    HISSC_STEREO_DLINK_R_FIFO_AFULL_TH_BIT_END     (20)
/* STEREO DLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_STEREO_DLINK_R_FIFO_AEMPTY_TH_BIT_START  (24)
#define    HISSC_STEREO_DLINK_R_FIFO_AEMPTY_TH_BIT_END    (28)


/* �Ĵ���˵����STEREO����ͨ��AFIFO ����ˮ������ */
#define HISSC_STEREO_UPLINK_FIFO_TH_CFG_ADDR          ((PAGE_SoCCODEC) + (0x3C))
/* STEREO UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_STEREO_UPLINK_L_FIFO_AFULL_TH_BIT_START   (0)
#define    HISSC_STEREO_UPLINK_L_FIFO_AFULL_TH_BIT_END     (4)
/* STEREO UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_STEREO_UPLINK_L_FIFO_AEMPTY_TH_BIT_START  (8)
#define    HISSC_STEREO_UPLINK_L_FIFO_AEMPTY_TH_BIT_END    (12)
/* STEREO UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_STEREO_UPLINK_R_FIFO_AFULL_TH_BIT_START   (16)
#define    HISSC_STEREO_UPLINK_R_FIFO_AFULL_TH_BIT_END     (20)
/* STEREO UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_STEREO_UPLINK_R_FIFO_AEMPTY_TH_BIT_START  (24)
#define    HISSC_STEREO_UPLINK_R_FIFO_AEMPTY_TH_BIT_END    (28)


/* �Ĵ���˵����VOICE����ͨ��AFIFO ����ˮ������ */
#define HISSC_VOICE_UPLINK_FIFO_TH_CFG_ADDR           ((PAGE_SoCCODEC) + (0x40))
/* VOICE UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_VOICE_UPLINK_L_FIFO_AFULL_TH_BIT_START   (0)
#define    HISSC_VOICE_UPLINK_L_FIFO_AFULL_TH_BIT_END     (4)
/* VOICE UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_VOICE_UPLINK_L_FIFO_AEMPTY_TH_BIT_START  (8)
#define    HISSC_VOICE_UPLINK_L_FIFO_AEMPTY_TH_BIT_END    (12)
/* reserved */
#define    HISSC___B1___RIGHT____BIT_START                (13)
#define    HISSC___B1___RIGHT____BIT_END                  (15)
/* VOICE UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC___B0___LEFT____BIT_START                 (16)
#define    HISSC___B0___LEFT____BIT_END                   (20)
/* VOICE UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_VOICE_UPLINK_R_FIFO_AEMPTY_TH_BIT_START  (24)
#define    HISSC_VOICE_UPLINK_R_FIFO_AEMPTY_TH_BIT_END    (28)


/* �Ĵ���˵�����ж����μĴ��� */
#define HISSC_CODEC_IRQ_MASK_ADDR                     ((PAGE_SoCCODEC) + (0x44))
/* �ж�����λ��
[5]: thirdmd uplink�ж�����
[4]: thirdmd dlink �ж�����
[3]: voice uplink�ж�����
[2]: stereo uplink�ж�����
[1]: stereo dlink�ж�����
[0]: voice dlink�ж����� */
#define    HISSC_CODEC_DATA_INTRP_MASK_BIT_START  (0)
#define    HISSC_CODEC_DATA_INTRP_MASK_BIT_END    (5)


/* �Ĵ���˵�����ж�״̬�Ĵ��� */
#define HISSC_CODEC_IRQ_ADDR                          ((PAGE_SoCCODEC) + (0x48))
/* �ж�״̬λ��
[5]: thirdmd uplink�жϣ�Ϊ1ʱ��ʾthirdmd uplink����Master������
[4]: thirdmd dlink �жϣ�Ϊ1ʱ��ʾthirdmd dlink ����Master������
[3]: voice uplink�жϣ�Ϊ1ʱ��ʾvoice uplink����Master������
[2]: stereo uplink�жϣ�Ϊ1ʱ��ʾvoice uplink����Master������
[1]: stereo dlink�жϣ�Ϊ1ʱ��ʾstereo dplink����Master������
[0]: voice dlink�жϣ�Ϊ1ʱ��ʾvoice uplink����Master������ */
#define    HISSC_CODEC_DATA_INTRP_BIT_START  (0)
#define    HISSC_CODEC_DATA_INTRP_BIT_END    (5)


/* �Ĵ���˵����DACL AGC (�Զ��������)���üĴ���1�� */
#define HISSC_DACL_AGC_CFG_1_ADDR                     ((PAGE_SoCCODEC) + (0x4C))
/* AGC�����µ���ƽ�����������á�
00��3.5dB��
01��5.5dB��
10��9dB��
11��15dB�� */
#define    HISSC_DACL_AGC_GWIN_CONFIG_BIT_START      (0)
#define    HISSC_DACL_AGC_GWIN_CONFIG_BIT_END        (1)
/* AGC�͵�ƽ�����������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_DACL_AGC_LEVELLOW_CONFIG_BIT_START  (2)
#define    HISSC_DACL_AGC_LEVELLOW_CONFIG_BIT_END    (3)
/* AGC�����µ��Ĳ����������á�
00��0.5dB��
01��1dB��
10��1.5dB��
11��2dB�� */
#define    HISSC_DACL_AGC_GSTEPD_CONFIG_BIT_START    (4)
#define    HISSC_DACL_AGC_GSTEPD_CONFIG_BIT_END      (5)
/* AGC�����ȴ�ʱ�����á�
����Ƶ��Ϊ48KHz��
00��187.5ms��
01��375ms��
10��750ms��
11��1.5s��
����Ƶ��Ϊ96KHz��
00��N/A��
01��187.5ms��
10��375ms��
11��750ms��  */
#define    HISSC_DACL_AGC_TIMEMUTE_CONFIG_BIT_START  (6)
#define    HISSC_DACL_AGC_TIMEMUTE_CONFIG_BIT_END    (7)
/* AGC�����жϳ������洰���á�
00��0dB��
01��1dB��
10��2dB��
11��4dB�� */
#define    HISSC_DACL_AGC_NGW_CONFIG_BIT_START       (8)
#define    HISSC_DACL_AGC_NGW_CONFIG_BIT_END         (9)
/* AGC����ź�Ŀ������������á�
000��-4dB��
001��-6dB��
010��-9dB��
011��-12dB��
100��-15dB��
101��-18dB��
110��-21dB��
111��-24dB�� */
#define    HISSC_DACL_AGC_YTARGET_CONFIG_BIT_START   (10)
#define    HISSC_DACL_AGC_YTARGET_CONFIG_BIT_END     (12)
/* AGC�����µ�����Сʱ�������á�
����Ƶ��Ϊ48KHz��
00��1/24ms��
01��0.125ms��
10��0.75ms��
11��1.5ms��
����Ƶ��Ϊ96KHz��
00��1/48ms��
01��0.0625ms��
10��0.375ms��
11��0.75ms�� */
#define    HISSC_DACL_AGC_T_AMIN_CONFIG_BIT_START    (13)
#define    HISSC_DACL_AGC_T_AMIN_CONFIG_BIT_END      (14)
/* AGC����ѹ��ʹ�ܱ�־���á�
0����ѹ����
1��ѹ���� */
#define    HISSC_DACL_AGC_GSUPPRESS_BIT_START        (15)
#define    HISSC_DACL_AGC_GSUPPRESS_BIT_END          (15)
/* AGC�а����������½�����ѡ��
00��ѡ��1/2^(10)���ʣ�
01��ѡ��1/2^(11)���ʣ�
10��ѡ��1/2^(12)���ʣ�
11��ѡ��1/2^(13)���ʡ� */
#define    HISSC_DACL_AGC_KFSLOW_BIT_START           (16)
#define    HISSC_DACL_AGC_KFSLOW_BIT_END             (17)
/* AGC�а���������½�����ѡ��
00��ѡ��1/2^(6)���ʣ�
01��ѡ��1/2^(7)���ʣ�
10��ѡ��1/2^(8)���ʣ�
11��ѡ��1/2^(9)���ʡ� */
#define    HISSC_DACL_AGC_KFRAPID_BIT_START          (18)
#define    HISSC_DACL_AGC_KFRAPID_BIT_END            (19)
/* AGC������ֵ���ֵ���á�
00������������ֵ��ʼֵ���ã�
01������������ֵ��ʼֵ���ü�ȥ6dB��
10������������ֵ��ʼֵ���ü�ȥ18dB��
11������-90dB�� */
#define    HISSC_DACL_AGC_NGL_CONFIG_BIT_START       (20)
#define    HISSC_DACL_AGC_NGL_CONFIG_BIT_END         (21)
/* AGC������ֵ���ֵ���á�
00������������ֵ��ʼֵ���ã�
01������������ֵ��ʼֵ���ü�12dB��
10������������ֵ��ʼֵ���ü�18dB��
11������-24dB�� */
#define    HISSC_DACL_AGC_NGH_CONFIG_BIT_START       (22)
#define    HISSC_DACL_AGC_NGH_CONFIG_BIT_END         (23)
/* AGCʱ��ѡ�����á�
����Ƶ��Ϊ48KHzʱ��
000��96���������ڣ�
001��192���������ڣ�
010��384���������ڣ�
b011��768���������ڣ�
100��1536���������ڣ�
101��3072���������ڣ�
110��6144���������ڣ�
111��12288���������ڡ�
����Ƶ��Ϊ96KHzʱ��
000��N/A��
001��96���������ڣ�
010��192���������ڣ�
011��384���������ڣ�
100��768���������ڣ�
101��1536���������ڣ�
110��3072���������ڣ�
111��6144���������ڡ� */
#define    HISSC_DACL_AGC_TIMER_BIT_START            (24)
#define    HISSC_DACL_AGC_TIMER_BIT_END              (26)
/* AGC������ֵ��ʼֵ�������á�
000��-72dB��
001��-66dB��
010��-60dB��
011��-54dB��
100��-51dB��
101��-48dB��
110��-42dB��
111��-36dB�� */
#define    HISSC_DACL_AGC_NGI_CONFIG_BIT_START       (27)
#define    HISSC_DACL_AGC_NGI_CONFIG_BIT_END         (29)
/* AGC������ֵ����ʱ�����á�
����Ƶ��Ϊ48KHz��
00��ʱ��ѡ�����õ�1.5����
01��ʱ��ѡ�����õ�2����
10��ʱ��ѡ�����õ�4����
11��ѡ��2�롣
����Ƶ��Ϊ96KHz��
00��ʱ��ѡ�����õ�1.5����
01��ʱ��ѡ�����õ�2����
10��ʱ��ѡ�����õ�4����
11��ѡ��1�� */
#define    HISSC_DACL_AGC_TIMENNG_CONFIG_BIT_START   (30)
#define    HISSC_DACL_AGC_TIMENNG_CONFIG_BIT_END     (31)


/* �Ĵ���˵����DACL AGC (�Զ��������)���üĴ���2�� */
#define HISSC_DACL_AGC_CFG_2_ADDR                     ((PAGE_SoCCODEC) + (0x50))
/* AGCÿ���ϵ������ʱ�������á�
����Ƶ��Ϊ48KHz��
00��ʱ��ѡ�����õ�1/4��
01��ʱ��ѡ�����õ�1/8��
10��ʱ��ѡ�����õ�1/16��
11��0.25ms��
����Ƶ��Ϊ96KHz��
00��ʱ��ѡ�����õ�1/4��
01��ʱ��ѡ�����õ�1/8��
10��ʱ��ѡ�����õ�1/16��
11��0.125ms�� */
#define    HISSC_DACL_AGC_TIMEDECAY_CONFIG_BIT_START  (0)
#define    HISSC_DACL_AGC_TIMEDECAY_CONFIG_BIT_END    (1)
/* AGC�����ϵ�֮ǰ�ĵȴ�ʱ�����á�
00��ʱ��ѡ�����õ�1/8��
01��ʱ��ѡ�����õ�1/4��
10��ʱ��ѡ�����õ�1/2��
11��ʱ��ѡ�����õ�3/4�� */
#define    HISSC_DACL_AGC_TIMEGHOLD_CONFIG_BIT_START  (2)
#define    HISSC_DACL_AGC_TIMEGHOLD_CONFIG_BIT_END    (3)
/* AGC����״̬�µ��������á�
00��0dB��
01��-12dB��
10��-24dB��
11��-42dB�� */
#define    HISSC_DACL_AGC_GMUTE_CONFIG_BIT_START      (4)
#define    HISSC_DACL_AGC_GMUTE_CONFIG_BIT_END        (5)
/* AGC�������ܽ�ֹ��־���á�
0����ֹ��
1�������� */
#define    HISSC_DACL_AGC_MUTE_BYPASS_BIT_START       (6)
#define    HISSC_DACL_AGC_MUTE_BYPASS_BIT_END         (6)
/* AGC����bypassʹ���źš�
1��AGC���ܽ�ֹ��
0�������Զ�������ơ� */
#define    HISSC_DACL_AGC_BYPASS_BIT_START            (7)
#define    HISSC_DACL_AGC_BYPASS_BIT_END              (7)
/* AGC����bypassʱ���û�������������ϵ������dB�˷���һ����Ϊ����λ���á�
Ĭ�ϣ�0dB����ͨ�������ģ������淶Χ��-72dB��+36dB������
0010_0100��36dB��
0010_0011��35dB��
����
1011_1000��-72dB��
����Ϊ1dB�������ʾ�� */
#define    HISSC_DACL_AGC_USR_GDB_INTEGER_BIT_START   (8)
#define    HISSC_DACL_AGC_USR_GDB_INTEGER_BIT_END     (15)
/* DACL AGC�û���������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_DACL_AGC_USR_GDB_FRAC_BIT_START      (16)
#define    HISSC_DACL_AGC_USR_GDB_FRAC_BIT_END        (16)
/* DACLͨ��AGC��λ���á�
0����Ч��
1����λ�� */
#define    HISSC_DACL_AGC_SW_CLR_BIT_START            (17)
#define    HISSC_DACL_AGC_SW_CLR_BIT_END              (17)


/* �Ĵ���˵����DACR AGC (�Զ��������)���üĴ���1�� */
#define HISSC_DACR_AGC_CFG_1_ADDR                     ((PAGE_SoCCODEC) + (0x54))
/* AGC�����µ���ƽ�����������á�
00��3.5dB��
01��5.5dB��
10��9dB��
11��15dB�� */
#define    HISSC_DACR_AGC_GWIN_CONFIG_BIT_START      (0)
#define    HISSC_DACR_AGC_GWIN_CONFIG_BIT_END        (1)
/* AGC�͵�ƽ�����������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_DACR_AGC_LEVELLOW_CONFIG_BIT_START  (2)
#define    HISSC_DACR_AGC_LEVELLOW_CONFIG_BIT_END    (3)
/* AGC�����µ��Ĳ����������á�
00��0.5dB��
01��1dB��
10��1.5dB��
11��2dB�� */
#define    HISSC_DACR_AGC_GSTEPD_CONFIG_BIT_START    (4)
#define    HISSC_DACR_AGC_GSTEPD_CONFIG_BIT_END      (5)
/* AGC�����ȴ�ʱ�����á�
����Ƶ��Ϊ48KHz��
00��187.5ms��
01��375ms��
10��750ms��
11��1.5s��
����Ƶ��Ϊ96KHz��
00��N/A��
01��187.5ms��
10��375ms��
11��750ms��  */
#define    HISSC_DACR_AGC_TIMEMUTE_CONFIG_BIT_START  (6)
#define    HISSC_DACR_AGC_TIMEMUTE_CONFIG_BIT_END    (7)
/* AGC�����жϳ������洰���á�
���淶Χ:0dB~4dB��
����Ϊ1dB��
00��0dB��
01��1dB��
10��2dB��
11��4dB�� */
#define    HISSC_DACR_AGC_NGW_CONFIG_BIT_START       (8)
#define    HISSC_DACR_AGC_NGW_CONFIG_BIT_END         (9)
/* AGC����ź�Ŀ������������á�
���淶Χ:-24dB~-4dB��
����Ϊ2dB��
000��-4dB��
001��-6dB��
010��-9dB��
011��-12dB��
100��-15dB��
101��-18dB��
110��-21dB��
111��-24dB�� */
#define    HISSC_DACR_AGC_YTARGET_CONFIG_BIT_START   (10)
#define    HISSC_DACR_AGC_YTARGET_CONFIG_BIT_END     (12)
/* AGC�����µ�����Сʱ�������á�
����Ƶ��Ϊ48KHz��
00��1/24ms��
01��0.125ms��
10��0.75ms��
11��1.5ms��
����Ƶ��Ϊ96KHz��
00��1/48ms��
01��0.0625ms��
10��0.375ms��
11��0.75ms�� */
#define    HISSC_DACR_AGC_T_AMIN_CONFIG_BIT_START    (13)
#define    HISSC_DACR_AGC_T_AMIN_CONFIG_BIT_END      (14)
/* AGC����ѹ��ʹ�ܱ�־���á�
0����ѹ����
1��ѹ���� */
#define    HISSC_DACR_AGC_GSUPPRESS_BIT_START        (15)
#define    HISSC_DACR_AGC_GSUPPRESS_BIT_END          (15)
/* AGC�а����������½�����ѡ��
00��ѡ��1/2^(10)���ʣ�
01��ѡ��1/2^(11)���ʣ�
10��ѡ��1/2^(12)���ʣ�
11��ѡ��1/2^(13)���ʡ� */
#define    HISSC_DACR_AGC_KFSLOW_BIT_START           (16)
#define    HISSC_DACR_AGC_KFSLOW_BIT_END             (17)
/* AGC�а���������½�����ѡ��
00��ѡ��1/2^(6)���ʣ�
01��ѡ��1/2^(7)���ʣ�
10��ѡ��1/2^(8)���ʣ�
11��ѡ��1/2^(9)���ʡ� */
#define    HISSC_DACR_AGC_KFRAPID_BIT_START          (18)
#define    HISSC_DACR_AGC_KFRAPID_BIT_END            (19)
/* AGC������ֵ���ֵ���á�
00������������ֵ��ʼֵ���ã�
01������������ֵ��ʼֵ���ü�ȥ6dB��
10������������ֵ��ʼֵ���ü�ȥ18dB��
11������-90dB�� */
#define    HISSC_DACR_AGC_NGL_CONFIG_BIT_START       (20)
#define    HISSC_DACR_AGC_NGL_CONFIG_BIT_END         (21)
/* AGC������ֵ���ֵ���á�
00������������ֵ��ʼֵ���ã�
01������������ֵ��ʼֵ���ü�12dB��
10������������ֵ��ʼֵ���ü�18dB��
11������-24dB�� */
#define    HISSC_DACR_AGC_NGH_CONFIG_BIT_START       (22)
#define    HISSC_DACR_AGC_NGH_CONFIG_BIT_END         (23)
/* AGCʱ��ѡ�����á�
����Ƶ��Ϊ48KHzʱ��
000��96���������ڣ�
001��192���������ڣ�
010��384���������ڣ�
b011��768���������ڣ�
100��1536���������ڣ�
101��3072���������ڣ�
110��6144���������ڣ�
111��12288���������ڡ�
����Ƶ��Ϊ96KHzʱ��
000��N/A��
001��96���������ڣ�
010��192���������ڣ�
011��384���������ڣ�
100��768���������ڣ�
101��1536���������ڣ�
110��3072���������ڣ�
111��6144���������ڡ� */
#define    HISSC_DACR_AGC_TIMER_BIT_START            (24)
#define    HISSC_DACR_AGC_TIMER_BIT_END              (26)
/* AGC������ֵ��ʼֵ�������á�
���淶Χ:-72dB~-36dB��
����Ϊ6dB��
000��-72dB��
001��-66dB��
010��-60dB��
011��-54dB��
100��-51dB��
101��-48dB��
110��-42dB��
111��-36dB�� */
#define    HISSC_DACR_AGC_NGI_CONFIG_BIT_START       (27)
#define    HISSC_DACR_AGC_NGI_CONFIG_BIT_END         (29)
/* AGC������ֵ����ʱ�����á�
����Ƶ��Ϊ48KHz��
00��ʱ��ѡ�����õ�1.5����
01��ʱ��ѡ�����õ�2����
10��ʱ��ѡ�����õ�4����
11��ѡ��2�롣
����Ƶ��Ϊ96KHz��
00��ʱ��ѡ�����õ�1.5����
01��ʱ��ѡ�����õ�2����
10��ʱ��ѡ�����õ�4����
11��ѡ��1�� */
#define    HISSC_DACR_AGC_TIMENNG_CONFIG_BIT_START   (30)
#define    HISSC_DACR_AGC_TIMENNG_CONFIG_BIT_END     (31)


/* �Ĵ���˵����DACR AGC (�Զ��������)���üĴ���2�� */
#define HISSC_DACR_AGC_CFG_2_ADDR                     ((PAGE_SoCCODEC) + (0x58))
/* AGCÿ���ϵ������ʱ�������á�
����Ƶ��Ϊ48KHz��
00��ʱ��ѡ�����õ�1/4��
01��ʱ��ѡ�����õ�1/8��
10��ʱ��ѡ�����õ�1/16��
11��0.25ms��
����Ƶ��Ϊ96KHz��
00��ʱ��ѡ�����õ�1/4��
01��ʱ��ѡ�����õ�1/8��
10��ʱ��ѡ�����õ�1/16��
11��0.125ms�� */
#define    HISSC_DACR_AGC_TIMEDECAY_CONFIG_BIT_START  (0)
#define    HISSC_DACR_AGC_TIMEDECAY_CONFIG_BIT_END    (1)
/* AGC�����ϵ�֮ǰ�ĵȴ�ʱ�����á�
00��ʱ��ѡ�����õ�1/8��
01��ʱ��ѡ�����õ�1/4��
10��ʱ��ѡ�����õ�1/2��
11��ʱ��ѡ�����õ�3/4�� */
#define    HISSC_DACR_AGC_TIMEGHOLD_CONFIG_BIT_START  (2)
#define    HISSC_DACR_AGC_TIMEGHOLD_CONFIG_BIT_END    (3)
/* AGC����״̬�µ��������á�
00��0dB��
01��-12dB��
10��-24dB��
11��-42dB�� */
#define    HISSC_DACR_AGC_GMUTE_CONFIG_BIT_START      (4)
#define    HISSC_DACR_AGC_GMUTE_CONFIG_BIT_END        (5)
/* AGC�������ܽ�ֹ��־���á�
0����ֹ��
1�������� */
#define    HISSC_DACR_AGC_MUTE_BYPASS_BIT_START       (6)
#define    HISSC_DACR_AGC_MUTE_BYPASS_BIT_END         (6)
/* AGC����bypassʹ���źš�
1��AGC���ܽ�ֹ��
0�������Զ�������ơ� */
#define    HISSC_DACR_AGC_BYPASS_BIT_START            (7)
#define    HISSC_DACR_AGC_BYPASS_BIT_END              (7)
/* AGC����bypassʱ���û�������������ϵ������dB�˷���һ����Ϊ����λ���á�
Ĭ�ϣ�0dB����ͨ�������ģ������淶Χ��-72dB��+36dB������
0010_0100��36dB��
0010_0011��35dB��
����
1011_1000��-72dB��
����Ϊ1dB�������ʾ�� */
#define    HISSC_DACR_AGC_USR_GDB_INTEGER_BIT_START   (8)
#define    HISSC_DACR_AGC_USR_GDB_INTEGER_BIT_END     (15)
/* DACR AGC�û���������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_DACR_AGC_USR_GDB_FRAC_BIT_START      (16)
#define    HISSC_DACR_AGC_USR_GDB_FRAC_BIT_END        (16)
/* DACRͨ��AGC��λ���á�
0����Ч��
1����λ�� */
#define    HISSC_DACR_AGC_SW_CLR_BIT_START            (17)
#define    HISSC_DACR_AGC_SW_CLR_BIT_END              (17)


/* �Ĵ���˵����DMIC�ӿں�Serial�ӿ����� */
#define HISSC_DMIC_SIF_CFG_ADDR                       ((PAGE_SoCCODEC) + (0x5C))
/* SIF ADCL����ʹ�ܣ�
1�����մ��нӿ��ͽ�������
0������������ */
#define    HISSC_SIF_ADCL_EN_BIT_START       (0)
#define    HISSC_SIF_ADCL_EN_BIT_END         (0)
/* SIF ADCR����ʹ�ܣ�
1�����մ��нӿ��ͽ�������
0������������ */
#define    HISSC_SIF_ADCR_EN_BIT_START       (1)
#define    HISSC_SIF_ADCR_EN_BIT_END         (1)
/* SIF DACL����ʹ�ܣ�
1�����нӿڷ�������
0������������ */
#define    HISSC_SIF_DACL_EN_BIT_START       (2)
#define    HISSC_SIF_DACL_EN_BIT_END         (2)
/* SIF DACR����ʹ�ܣ�
1�����нӿڷ�������
0������������ */
#define    HISSC_SIF_DACR_EN_BIT_START       (3)
#define    HISSC_SIF_DACR_EN_BIT_END         (3)
/* SIF ���ݻ��أ�
1��ADC����������ص�DAC�Ĳ�������
0�������� */
#define    HISSC_DAC_P2S_LOOPBACK_BIT_START  (4)
#define    HISSC_DAC_P2S_LOOPBACK_BIT_END    (4)
/* SIF����������ݻ���ʹ�ܣ�
1��DAC����������ص�ADC��������
0�������� */
#define    HISSC_SIF_S2P_LOOPBACK_BIT_START  (5)
#define    HISSC_SIF_S2P_LOOPBACK_BIT_END    (5)
/* sifģ��ʱ����ѡ��
1'b1: SIFʱ���������49.152Mʱ�ӷ���
1'b0: SIFʱ���������49.152Mʱ��ͬ�� */
#define    HISSC_SIF_EDGE_SEL_BIT_START      (6)
#define    HISSC_SIF_EDGE_SEL_BIT_END        (6)
/* ��smartStar�ӿ�ʹ�ܣ�
0���ر�ʱ��
1����ʱ�� */
#define    HISSC_SIF_EN_BIT_START            (7)
#define    HISSC_SIF_EN_BIT_END              (7)
/* DMIC�������á�
0������������������
1���������������� */
#define    HISSC_SW_DMIC_MODE_BIT_START      (16)
#define    HISSC_SW_DMIC_MODE_BIT_END        (16)
/* DMIC����������á�
0��0 -> -4, 1 -> +4��
1��0 -> +4, 1 -> -4�� */
#define    HISSC_DMIC_REVERSE_BIT_START      (17)
#define    HISSC_DMIC_REVERSE_BIT_END        (17)
/* DMICʱ�����á�
2'b00���ر�ʱ�ӣ�
2'b01��2��Ƶ��
2'b10��3��Ƶ��
2'b11��4��Ƶ�� */
#define    HISSC_FS_DMIC_BIT_START           (18)
#define    HISSC_FS_DMIC_BIT_END             (19)
/* DMIC�ӿ�ʹ�ܣ�
0���ر�ʱ��
1����ʱ�� */
#define    HISSC_DMIC_EN_BIT_START           (20)
#define    HISSC_DMIC_EN_BIT_END             (20)


/* �Ĵ���˵����Misc Config */
#define HISSC_MISC_CFG_ADDR                           ((PAGE_SoCCODEC) + (0x60))
/* S2�ӿڣ�BT�ӿڣ������ͨ��������ݵ�һ��ѡ��MUX6��
1'b0: ѡ�񽵲���SRC3�����
1'b1: ѡ��voice dlinkͨ��pga����� */
#define    HISSC_S2_DOUT_LEFT_SEL_BIT_START                 (0)
#define    HISSC_S2_DOUT_LEFT_SEL_BIT_END                   (0)
/* S1���ͨ������ѡ������������������ƣ�MUX8/MUX9��
1'b0: ������ѡ��DACL MIXER�����������ѡ��DACR MIXER�����
1'b1: ������ѡ��adcl�����˲���ͨ�����;������ѡ��adcr�����˲���ͨ����� */
#define    HISSC_S1_DOUT_TEST_SEL_BIT_START                 (1)
#define    HISSC_S1_DOUT_TEST_SEL_BIT_END                   (1)
/* S2�ӿڣ�BT�ӿڣ����ͨ��������ݵڶ���ѡ�񣬸ı������������MUX7��
1'b0: ѡ����·�����ݣ�voice dlink pga����S2�������������
1'b1: ѡ��DACL MIXER����� */
#define    HISSC_S2_DOUT_TEST_SEL_BIT_START                 (2)
#define    HISSC_S2_DOUT_TEST_SEL_BIT_END                   (2)
/* STEREO DLINKͨ����������ѡ��MUX11/MUX12��
1'b0:������APB����
1'b1:S1�ӿ�����������stereo_dlink_l ,S1�ӿ�����������stereo_dlink_r */
#define    HISSC_STEREO_DLINK_TEST_SEL_BIT_START            (4)
#define    HISSC_STEREO_DLINK_TEST_SEL_BIT_END              (4)
/* VOICE DLINKͨ����������ѡ��
1'b0:������APB����
1'b1:S3�ӿ����������� */
#define    HISSC_VOICE_DLINK_DIN_SEL_BIT_START              (6)
#define    HISSC_VOICE_DLINK_DIN_SEL_BIT_END                (6)
/* VOICE DLINKͨ����������ѡ��MUX10
1'b0:������ǰ��ѡ��FrontSel���
1'b1:S2�ӿ����������� */
#define    HISSC_VOICE_DLINK_TEST_SEL_BIT_START             (7)
#define    HISSC_VOICE_DLINK_TEST_SEL_BIT_END               (7)
/* VOICE����ͨ��SRCģ�����������ѡ��
1'b0: ���Ϊ48kHz
1'b1: ���Ϊ96kHz */
#define    HISSC_VOICE_DLINK_SRC_UP_DOUT_VLD_SEL_BIT_START  (8)
#define    HISSC_VOICE_DLINK_SRC_UP_DOUT_VLD_SEL_BIT_END    (8)
/* s3����ѡ��
1'b0: ѡ��Left������
1'b1: ѡ��Right������ */
#define    HISSC_S3_DIN_TEST_SEL_BIT_START                  (12)
#define    HISSC_S3_DIN_TEST_SEL_BIT_END                    (12)
/* S3�ӿ������ͨ��ѡ���źţ�
1'b0: thirdmd dlink pga�����
1'b1: adclͨ��pga��� */
#define    HISSC_S3_DOUT_LEFT_SEL_BIT_START                 (13)
#define    HISSC_S3_DOUT_LEFT_SEL_BIT_END                   (13)
/* S3�ӿ������ͨ��ѡ���źţ�
2'b00: thirdmd dlink pga�����
2'b01: adcrͨ��pga���;
other: 0; */
#define    HISSC_S3_DOUT_RIGHT_SEL_BIT_START                (14)
#define    HISSC_S3_DOUT_RIGHT_SEL_BIT_END                  (15)
/* thirdmd_dlinkͨ����������ѡ�����룺
1'b0: APB thirdmd����ͨ��
1'b1: S2���������� */
#define    HISSC_THIRDMD_DLINK_DIN_SEL_BIT_START            (16)
#define    HISSC_THIRDMD_DLINK_DIN_SEL_BIT_END              (16)
/* thirdmd_dlinkͨ����������ѡ�����룺
1'b0: ��APB thirdmd����ͨ����S2������ѡ��
1'b1: S3���� */
#define    HISSC_THIRDMD_DLINK_TEST_SEL_BIT_START           (17)
#define    HISSC_THIRDMD_DLINK_TEST_SEL_BIT_END             (17)


/* �Ĵ���˵����S2�ӿ�SRCģ������ */
#define HISSC_S2_SRC_CFG_ADDR                         ((PAGE_SoCCODEC) + (0x64))
/* S2�ӿ�������ͨ��SRC�������˲���ʱ���źţ�
1'b1��ʱ��ʹ�ܣ�
1'b0��bypass */
#define    HISSC_S2_IL_SRC_UP_EN_BIT_START         (0)
#define    HISSC_S2_IL_SRC_UP_EN_BIT_END           (0)
/* S2�ӿ�������ͨ��SRC�������˲���ʱ���źţ�
1'b1��ʱ��ʹ�ܣ�
1'b0��bypass */
#define    HISSC_S2_IL_SRC_DOWN_EN_BIT_START       (1)
#define    HISSC_S2_IL_SRC_DOWN_EN_BIT_END         (1)
/* S2�ӿ�������ͨ��SRC�������˲���ʱ���źţ�
1'b1��ʱ��ʹ�ܣ�
1'b0��bypass */
#define    HISSC_S2_IR_SRC_UP_EN_BIT_START         (2)
#define    HISSC_S2_IR_SRC_UP_EN_BIT_END           (2)
/* S2�ӿ�������ͨ��SRC�������˲���ʱ���źţ�
1'b1��ʱ��ʹ�ܣ�
1'b0��bypass */
#define    HISSC_S2_IR_SRC_DOWN_EN_BIT_START       (3)
#define    HISSC_S2_IR_SRC_DOWN_EN_BIT_END         (3)
/* S2 I2S�ӿ�������ͨ��SRC������ģ��READY�źţ�
1'b1:SRC RAM��ʼ�����
1'b0:SRC RAM��ʼ�������� */
#define    HISSC_S2_IL_SRC_UP_SRC_RDY_BIT_START    (4)
#define    HISSC_S2_IL_SRC_UP_SRC_RDY_BIT_END      (4)
/* S2 I2S�ӿ�������ͨ��SRC������ģ��READY�źţ�
1'b1:SRC RAM��ʼ�����
1'b0:SRC RAM��ʼ�������� */
#define    HISSC_S2_IL_SRC_DOWN_SRC_RDY_BIT_START  (5)
#define    HISSC_S2_IL_SRC_DOWN_SRC_RDY_BIT_END    (5)
/* S2 I2S�ӿ�������ͨ��SRC������ģ��READY�źţ�
1'b1:SRC RAM��ʼ�����
1'b0:SRC RAM��ʼ�������� */
#define    HISSC_S2_IR_SRC_UP_SRC_RDY_BIT_START    (6)
#define    HISSC_S2_IR_SRC_UP_SRC_RDY_BIT_END      (6)
/* S2 I2S�ӿ�������ͨ��SRC������ģ��READY�źţ�
1'b1:SRC RAM��ʼ�����
1'b0:SRC RAM��ʼ�������� */
#define    HISSC_S2_IR_SRC_DOWN_SRC_RDY_BIT_START  (7)
#define    HISSC_S2_IR_SRC_DOWN_SRC_RDY_BIT_END    (7)


/* �Ĵ���˵����memory�����ź� */
#define HISSC_MEM_CFG_ADDR                            ((PAGE_SoCCODEC) + (0x68))
/* SRC�е���memory�����ź� */
#define    HISSC_MEM_CTRL_S_BIT_START      (0)
#define    HISSC_MEM_CTRL_S_BIT_END        (15)
/* AFIFO��˫��memory�����ź� */
#define    HISSC_MEM_CTRL_D1W2R_BIT_START  (16)
#define    HISSC_MEM_CTRL_D1W2R_BIT_END    (31)


/* �Ĵ���˵����������modem��I2S */
#define HISSC_THIRDMD_PCM_PGA_CFG_ADDR                ((PAGE_SoCCODEC) + (0x6C))
/* S1�ӿ�ģʽѡ��
3'b000:I2S
3'b010:PCM STD
3'b011:PCM USER Defined
3'b100:Left Justified
3'b101:Right Justified
���������� */
#define    HISSC_S3_FUNC_MODE_BIT_START                      (0)
#define    HISSC_S3_FUNC_MODE_BIT_END                        (2)
/* S1�ӿ�Codec ADC/DAC���ݸ�ʽѡ��
0����ʾ�����Ʋ��룻
1����ʾ�������루binary offset���� */
#define    HISSC_S3_CODEC_DATA_FORMAT_BIT_START              (3)
#define    HISSC_S3_CODEC_DATA_FORMAT_BIT_END                (3)
/* S1�ӿ�RX����ʱ��ѡ��
1'b0:BCLK�����ؽ�������
1'b1:BCLK�½��ؽ������� */
#define    HISSC_S3_RX_CLK_SEL_BIT_START                     (4)
#define    HISSC_S3_RX_CLK_SEL_BIT_END                       (4)
/* S1�ӿ�TX����ʱ��ѡ��
1'b0:BCLK�����ش������
1'b1:BCLK�½��ش������ */
#define    HISSC_S3_TX_CLK_SEL_BIT_START                     (5)
#define    HISSC_S3_TX_CLK_SEL_BIT_END                       (5)
/* S1 I2S�ӿڻ���ģʽѡ��
2'b00����������ģʽ��
2'b01��Sdin->Sdout��
2'b10: RX_DATA[23:0] -> TX_IN[23:0]
2'b11: ���� */
#define    HISSC_S3_DIRECT_LOOP_BIT_START                    (6)
#define    HISSC_S3_DIRECT_LOOP_BIT_END                      (7)
/* S1�ӿ�λ�����ơ�
00��16bit��
01��18bit��
10��20bit��
11��24bit�� */
#define    HISSC_S3_CODEC_IO_WORDLENGTH_BIT_START            (8)
#define    HISSC_S3_CODEC_IO_WORDLENGTH_BIT_END              (9)
/* S1�ӿ��������ã�
1'b0:��������ǰ
1'b1:��������ǰ */
#define    HISSC_S3_CHNNL_MODE_BIT_START                     (10)
#define    HISSC_S3_CHNNL_MODE_BIT_END                       (10)
/* S1�ӿ�֡ͬ���ź���������ѡ��
1'b0:low -> left channel
1'b1:low -> right channel */
#define    HISSC_S3_LRCLK_MODE_BIT_START                     (11)
#define    HISSC_S3_LRCLK_MODE_BIT_END                       (11)
/* S1�ӿ�Master/Slaveģʽѡ��
1'b0:Materģʽ����masterģʽ��BCLK/SYNC�ſ������
1'b1:Slaveģʽ */
#define    HISSC_S3_MST_SLV_BIT_START                        (12)
#define    HISSC_S3_MST_SLV_BIT_END                          (12)
/* S1�ӿ�I2Sģʽ��֡��ʽ���ã�
1'b0:I2Sģʽ��64bit frame��PCMģʽ��32bit frame
1'b1:I2Sģʽ��32bit frame��PCMģʽ��16bit frame */
#define    HISSC_S3_FRAME_MODE_BIT_START                     (13)
#define    HISSC_S3_FRAME_MODE_BIT_END                       (13)
/* S1�ӿ�RX����ʹ�ܣ�
1'b1:ʹ��
1'b0:�ر� */
#define    HISSC_S3_IF_RX_ENA_BIT_START                      (14)
#define    HISSC_S3_IF_RX_ENA_BIT_END                        (14)
/* S1�ӿ�TX����ʹ�ܣ�
1'b1:ʹ��
1'b0:�ر� */
#define    HISSC_S3_IF_TX_ENA_BIT_START                      (15)
#define    HISSC_S3_IF_TX_ENA_BIT_END                        (15)
/* S1�ӿڲ���������
0��8KHz�� 1��16KHz��
2��32KHz�� 3������
4��48KHz�� 5��96KHz��
6��192KHz��7������ */
#define    HISSC_FS_S3_BIT_START                             (16)
#define    HISSC_FS_S3_BIT_END                               (18)
/* ������modem����ͨ�� pga���������������:
Ĭ�ϣ�0dB
���淶Χ:-72dB~+36dB��
����
0010_0100:36dB
0010_0011:35dB
����
1011_1000��-72dB
����Ϊ1dB,�����ʾ��
�㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
#define    HISSC_THIRDMD_DLINK_PGA_INTEGER_CONFIG_BIT_START  (20)
#define    HISSC_THIRDMD_DLINK_PGA_INTEGER_CONFIG_BIT_END    (27)
/* ������modem����ͨ�� pga��������С��λ���á�
0��0.0dB��
1��0.5dB�� */
#define    HISSC_THIRDMD_DLINK_PGA_FRAC_CONFIG_BIT_START     (28)
#define    HISSC_THIRDMD_DLINK_PGA_FRAC_CONFIG_BIT_END       (28)
/* ������modem����ͨ�� pga muteʹ�ܣ�
1'b1: mute��Ч�����0
1'b0: �ر�mute */
#define    HISSC_THIRDMD_DLINK_PGA_MUTE_BIT_START            (29)
#define    HISSC_THIRDMD_DLINK_PGA_MUTE_BIT_END              (29)
/* ������modem����ͨ�� pga������͵�ƽ�������á�
00��-60dB��
01��-72dB��
10��-90dB��
11��-120dB�� */
#define    HISSC_THIRDMD_DLINK_PGA_THR_CONFIG_BIT_START      (30)
#define    HISSC_THIRDMD_DLINK_PGA_THR_CONFIG_BIT_END        (31)


/* �Ĵ���˵����������Modem����ͨ��AFIFOˮ�� */
#define HISSC_THIRD_MODEM_FIFO_TH_ADDR                ((PAGE_SoCCODEC) + (0x70))
/* Third Modem DLINKͨ��AFIFO������ֵ��fifo����Ч��ֵ�������ڸ�ֵʱ��FIFO almost full�ź���Ч */
#define    HISSC_THIRDMD_DLINK_FIFO_AFULL_TH_BIT_START    (0)
#define    HISSC_THIRDMD_DLINK_FIFO_AFULL_TH_BIT_END      (4)
/* Third Modem DLINKͨ��AFIFO������ֵ��fifo����Ч��ֵ�������ڸ�ֵʱ��FIFO almost empty�ź���Ч */
#define    HISSC_THIRDMD_DLINK_FIFO_AEMPTY_TH_BIT_START   (8)
#define    HISSC_THIRDMD_DLINK_FIFO_AEMPTY_TH_BIT_END     (12)
/* Third Modem UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_THIRDMD_UPLINK_FIFO_AFULL_TH_BIT_START   (16)
#define    HISSC_THIRDMD_UPLINK_FIFO_AFULL_TH_BIT_END     (20)
/* Third Modem UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
#define    HISSC_THIRDMD_UPLINK_FIFO_AEMPTY_TH_BIT_START  (24)
#define    HISSC_THIRDMD_UPLINK_FIFO_AEMPTY_TH_BIT_END    (28)


/* �Ĵ���˵����S3�ӿڿ�Ƶƫģ��TX��������� */
#define HISSC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_ADDR     ((PAGE_SoCCODEC) + (0x74))
/* S3�ӿ�tx�����������������ȡ�����
�м���ʱ������S3�ӿ�TX���򻺴������ݸ���������ˮ�ߣ���ҪHiFi�������ݸ�������ζ���ⲿʱ�ӿ졣 */
#define    HISSC_S3_TX_INC_CNT_BIT_START  (0)
#define    HISSC_S3_TX_INC_CNT_BIT_END    (7)


/* �Ĵ���˵����S3�ӿڿ�Ƶƫģ��TX��������� */
#define HISSC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_ADDR     ((PAGE_SoCCODEC) + (0x78))
/* S3�ӿ�tx�����������������ȡ�����
�м���ʱ������S3�ӿ�TX���򻺴������ݸ���������ˮ�ߣ���ҪHiFi�������ݸ�������ζ���ⲿʱ������ */
#define    HISSC_S3_TX_DEC_CNT_BIT_START  (0)
#define    HISSC_S3_TX_DEC_CNT_BIT_END    (7)


/* �Ĵ���˵����S3�ӿڿ�Ƶƫģ��RX��������� */
#define HISSC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_ADDR     ((PAGE_SoCCODEC) + (0x7C))
/* S3�ӿ�rx�����������������ȡ�����
�м���ʱ������S3�ӿ�RX���򻺴������ݸ���������ˮ�ߣ���ҪHiFi�������ݸ�������ζ���ⲿʱ�ӿ졣 */
#define    HISSC_S3_RX_INC_CNT_BIT_START  (0)
#define    HISSC_S3_RX_INC_CNT_BIT_END    (7)


/* �Ĵ���˵����S3�ӿڿ�Ƶƫģ��RX��������� */
#define HISSC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_ADDR     ((PAGE_SoCCODEC) + (0x80))
/* S3�ӿ�rx�����������������ȡ�����
�м���ʱ������S3�ӿ�RX���򻺴������ݸ���������ˮ�ߣ���ҪHiFi�������ݸ�������ζ���ⲿʱ������ */
#define    HISSC_S3_RX_DEC_CNT_BIT_START  (0)
#define    HISSC_S3_RX_DEC_CNT_BIT_END    (7)


/* �Ĵ���˵������Ƶƫģ��ʹ��ʹ�� */
#define HISSC_ANTI_FREQ_JITTER_EN_ADDR                ((PAGE_SoCCODEC) + (0x84))
/* S3�ӿ�TX����ANTI_FREQ_JITTERģ��ʹ�� */
#define    HISSC_S3_TX_ANTI_FREQ_JITTER_EN_BIT_START  (0)
#define    HISSC_S3_TX_ANTI_FREQ_JITTER_EN_BIT_END    (0)
/* S3�ӿ�RX����ANTI_FREQ_JITTERģ��ʹ�� */
#define    HISSC_S3_RX_ANTI_FREQ_JITTER_EN_BIT_START  (1)
#define    HISSC_S3_RX_ANTI_FREQ_JITTER_EN_BIT_END    (1)


/* �Ĵ���˵����12.288Mʱ����Դѡ�� */
#define HISSC_CLK_SEL_ADDR                            ((PAGE_SoCCODEC) + (0x88))
/* �ⲿ12.288Mʱ��ѡ��
1'b1: ѡ��Ƭ������ģ�12.288Mʱ��
1'b0: ѡ���ڲ���Ƶ������12.288Mʱ�� */
#define    HISSC_EXTERNAL_12288K_SEL_BIT_START  (0)
#define    HISSC_EXTERNAL_12288K_SEL_BIT_END    (0)


/* �Ĵ���˵����������Modem����ͨ�� */
#define HISSC_THIRDMD_DLINK_CHANNEL_ADDR              ((PAGE_SoCCODEC) + (0xE8))
/*  */
#define    HISSC_THIRDMD_DLINK_WDATA_BIT_START  (0)
#define    HISSC_THIRDMD_DLINK_WDATA_BIT_END    (31)


/* �Ĵ���˵����������Modem����ͨ�� */
#define HISSC_THIRDMD_UPLINK_CHANNEL_ADDR             ((PAGE_SoCCODEC) + (0xEC))
/*  */
#define    HISSC_THIRDMD_UPLINK_RDATA_BIT_START  (0)
#define    HISSC_THIRDMD_UPLINK_RDATA_BIT_END    (31)


/* �Ĵ���˵����VOICE����ͨ�� */
#define HISSC_VOICE_DLINK_CHANNEL_ADDR                ((PAGE_SoCCODEC) + (0xF0))
/*  */
#define    HISSC_VOICE_DLINK_WDATA_BIT_START  (0)
#define    HISSC_VOICE_DLINK_WDATA_BIT_END    (31)


/* �Ĵ���˵������Ƶ����ͨ�� */
#define HISSC_STEREO_DLINK_CHANNEL_ADDR               ((PAGE_SoCCODEC) + (0xF4))
/* ��������������в��� */
#define    HISSC_STEREO_DLINK_WDATA_BIT_START  (0)
#define    HISSC_STEREO_DLINK_WDATA_BIT_END    (31)


/* �Ĵ���˵������Ƶ����ͨ�� */
#define HISSC_STEREO_UPLINK_CHANNEL_ADDR              ((PAGE_SoCCODEC) + (0xF8))
/* ��������������в��� */
#define    HISSC_STEREO_UPLINK_RDATA_BIT_START  (0)
#define    HISSC_STEREO_UPLINK_RDATA_BIT_END    (31)


/* �Ĵ���˵����VOICE����ͨ�� */
#define HISSC_VOICE_UPLINK_CHANNEL_ADDR               ((PAGE_SoCCODEC) + (0xFC))
/* ��������������в��� */
#define    HISSC_VOICE_UPLINK_RDATA_BIT_START  (0)
#define    HISSC_VOICE_UPLINK_RDATA_BIT_END    (31)




/****************************************************************************
                     (2/2) smartStar CODEC
 ****************************************************************************/
/* �Ĵ���˵�����汾�Ĵ��� */
#define HISSC_SMT_VERSION_ADDR                        ((PAGE_SmartStarCODEC) + (0x1B0))
/* �汾�Ĵ�������ʾ�汾Ϊ100 */
#define    HISSC_SMT_VERSION_BIT_START  (0)
#define    HISSC_SMT_VERSION_BIT_END    (7)


/* �Ĵ���˵����ʱ��ʹ�����üĴ��� */
#define HISSC_SMT_CLK_EN_CFG_ADDR                     ((PAGE_SmartStarCODEC) + (0x1B1))
/* DACLʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_SMT_DACL_EN_BIT_START   (0)
#define    HISSC_SMT_DACL_EN_BIT_END     (0)
/* DACRʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_SMT_DACR_EN_BIT_START   (1)
#define    HISSC_SMT_DACR_EN_BIT_END     (1)
/* ADCLʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_SMT_ADCL_EN_BIT_START   (2)
#define    HISSC_SMT_ADCL_EN_BIT_END     (2)
/* ADCRʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_SMT_ADCR_EN_BIT_START   (3)
#define    HISSC_SMT_ADCR_EN_BIT_END     (3)
/* SIFʱ��ʹ�ܣ�
0���ر�ʱ�ӣ�
1����ʱ�ӡ� */
#define    HISSC_SMT_SIF_EN_BIT_START    (4)
#define    HISSC_SMT_SIF_EN_BIT_END      (4)


/* �Ĵ���˵������ģ�ӿ�ʱ����ѡ�� */
#define HISSC_SMT_CLK_EDGE_CFG_ADDR                   ((PAGE_SmartStarCODEC) + (0x1B2))
/* DACLʱ����ѡ��
0�����أ�
1����ģ�ⲿ�ַ�Ƶʱ��ͬ�ء� */
#define    HISSC_SMT_DACL_CLK_EDGE_SEL_BIT_START  (0)
#define    HISSC_SMT_DACL_CLK_EDGE_SEL_BIT_END    (0)
/* DACRʱ����ѡ��
0�����أ�
1����ģ�ⲿ�ַ�Ƶʱ��ͬ�ء� */
#define    HISSC_SMT_DACR_CLK_EDGE_SEL_BIT_START  (1)
#define    HISSC_SMT_DACR_CLK_EDGE_SEL_BIT_END    (1)
/* ADCLʱ����ѡ��
0�����أ�
1����ģ�ⲿ�ַ�Ƶʱ��ͬ�ء� */
#define    HISSC_SMT_ADCL_CLK_EDGE_SEL_BIT_START  (2)
#define    HISSC_SMT_ADCL_CLK_EDGE_SEL_BIT_END    (2)
/* ADCRʱ����ѡ��
0�����أ�
1����ģ�ⲿ�ַ�Ƶʱ��ͬ�ء� */
#define    HISSC_SMT_ADCR_CLK_EDGE_SEL_BIT_START  (3)
#define    HISSC_SMT_ADCR_CLK_EDGE_SEL_BIT_END    (3)


/* �Ĵ���˵�������ؿ��� */
#define HISSC_SMT_LOOPBACK_CFG_ADDR                   ((PAGE_SmartStarCODEC) + (0x1B3))
/* DACͨ�����ݻ��ؿ��ƣ�
1'b0�����������ڴ��нӿڣ�
1'b1��DACL��������������ģ��ADCL�������룬DACR��������������ģ��ADCR�������� */
#define    HISSC_SMT_DAC_LOOPBACK_BIT_START      (0)
#define    HISSC_SMT_DAC_LOOPBACK_BIT_END        (0)
/* ADCͨ�����ݻ��ؿ��ƣ�
1'b0��adc��������������ģ�Ⲣ�����룻
1'b1��adc��������������dac�Ĳ������ */
#define    HISSC_SMT_ADC_LOOPBACK_BIT_START      (1)
#define    HISSC_SMT_ADC_LOOPBACK_BIT_END        (1)
/* SIF����������ݻ���ʹ�ܣ�
1��ADC����������ص�DAC��������
0�������� */
#define    HISSC_SMT_SIF_S2P_LOOPBACK_BIT_START  (2)
#define    HISSC_SMT_SIF_S2P_LOOPBACK_BIT_END    (2)


/* �Ĵ���˵����ģ���ж�ԭʼ״̬�Ĵ��� */
#define HISSC_SMT_ANA_IRQ_SIG_STAT_ADDR               ((PAGE_SmartStarCODEC) + (0x1B4))
/* ����ģʽ�£����������ж�1������������½��ؾ���Ч��
1��������λʱ�������޶�������������
0��������λʱ���ж������������� */
#define    HISSC_SMT_HS_MIC_NOR1_IRQ_BIT_START  (0)
#define    HISSC_SMT_HS_MIC_NOR1_IRQ_BIT_END    (0)
/* ����ģʽ�£����������ж�2������������½��ؾ���Ч��
1��������λʱ�������޶�������������
0��������λʱ���ж������������� */
#define    HISSC_SMT_HS_MIC_NOR2_IRQ_BIT_START  (1)
#define    HISSC_SMT_HS_MIC_NOR2_IRQ_BIT_END    (1)
/* ECOģʽ�£����������жϣ�����������½��ؾ���Ч��
1��������λʱ�������޶�������������
0��������λʱ���ж������������� */
#define    HISSC_SMT_HS_MIC_ECO_IRQ_BIT_START   (2)
#define    HISSC_SMT_HS_MIC_ECO_IRQ_BIT_END     (2)
/* �����������жϣ�����������½��ؾ���Ч��
1����������غ��Ҷ�ֵΪ��1��ʱ����ʾ�ж������룻
0������½��غ��Ҷ�ֵΪ��0��ʱ����ʾ�����γ��� */
#define    HISSC_SMT_HS_DET_IRQ_BIT_START       (3)
#define    HISSC_SMT_HS_DET_IRQ_BIT_END         (3)


/* �Ĵ���˵����ANA_IRQ_REG�ж����μĴ��� */
#define HISSC_SMT_ANA_IRQM_REG0_ADDR                  ((PAGE_SmartStarCODEC) + (0x1B5))
/* [7]:�����γ�����ж�����λ��
[6]:�����������ж�����λ��
[5]:ECOģʽ�°��������ж�����λ��
[4]:ECOģʽ�°����ͷ��ж�����λ��
[3]:��������2�����ж�����λ��
[2]:��������2�ͷ��ж�����λ��
[1]:��������1�����ж�����λ��
[0]:��������1�ͷ��ж�����λ��
1�������жϣ�
0����������жϡ� */
#define    HISSC_SMT_ANA_IRQ_MASK_BIT_START  (0)
#define    HISSC_SMT_ANA_IRQ_MASK_BIT_END    (7)


/* �Ĵ���˵����ģ���жϼĴ���0��д1�壬���ϱ��ж���Ϣ */
#define HISSC_SMT_ANA_IRQ_REG0_ADDR                   ((PAGE_SmartStarCODEC) + (0x1B6))
/* ���������ͷ��жϣ����ߵ�ƽ��Ч��
1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
0����ѯʱ��ʾ�ж���Ч�� */
#define    HISSC_SMT_HS_MIC_NOR1_IRQ_POS_BIT_START  (0)
#define    HISSC_SMT_HS_MIC_NOR1_IRQ_POS_BIT_END    (0)
/* �������������жϣ����͵�ƽ��Ч��
1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
0����ѯʱ��ʾ�ж���Ч�� */
#define    HISSC_SMT_HS_MIC_NOR1_IRQ_NEG_BIT_START  (1)
#define    HISSC_SMT_HS_MIC_NOR1_IRQ_NEG_BIT_END    (1)
/* ���������ͷ��жϣ����ߵ�ƽ��Ч��
1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
0����ѯʱ��ʾ�ж���Ч�� */
#define    HISSC_SMT_HS_MIC_NOR2_IRQ_POS_BIT_START  (2)
#define    HISSC_SMT_HS_MIC_NOR2_IRQ_POS_BIT_END    (2)
/* �������������жϣ����͵�ƽ��Ч��
1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
0����ѯʱ��ʾ�ж���Ч�� */
#define    HISSC_SMT_HS_MIC_NOR2_IRQ_NEG_BIT_START  (3)
#define    HISSC_SMT_HS_MIC_NOR2_IRQ_NEG_BIT_END    (3)
/* ECOģʽ�°����ͷ��жϣ����ߵ�ƽ��Ч��
1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
0����ѯʱ��ʾ�ж���Ч�� */
#define    HISSC_SMT_HS_MIC_ECO_IRQ_POS_BIT_START   (4)
#define    HISSC_SMT_HS_MIC_ECO_IRQ_POS_BIT_END     (4)
/* ECOģʽ�°��������жϣ����͵�ƽ��Ч��
1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
0����ѯʱ��ʾ�ж���Ч�� */
#define    HISSC_SMT_HS_MIC_ECO_IRQ_NEG_BIT_START   (5)
#define    HISSC_SMT_HS_MIC_ECO_IRQ_NEG_BIT_END     (5)
/* �����������жϣ����ߵ�ƽ��Ч��
1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
0����ѯʱ��ʾ�ж���Ч�� */
#define    HISSC_SMT_HS_DET_IRQ_POS_BIT_START       (6)
#define    HISSC_SMT_HS_DET_IRQ_POS_BIT_END         (6)
/* �����γ�����жϣ����͵�ƽ��Ч��
1��д1ʱ����жϣ���ѯʱ��ʾ�ж���Ч��
0����ѯʱ��ʾ�ж���Ч�� */
#define    HISSC_SMT_HS_DET_IRQ_NEG_BIT_START       (7)
#define    HISSC_SMT_HS_DET_IRQ_NEG_BIT_END         (7)


/* �Ĵ���˵����hs_det_irqȥ������ */
#define HISSC_SMT_DEB_CNT_HS_DET_CFG_ADDR             ((PAGE_SmartStarCODEC) + (0x1B7))
/* ȥ�������ڼ���������32kʱ�Ӽ���
����Ϊ1ms*����ֵ��
Ĭ������Ϊ20*1ms = 20ms
��ʱ��Χ��0~32ms */
#define    HISSC_SMT_DEB_CNT_HS_DET_IRQ_BIT_START     (0)
#define    HISSC_SMT_DEB_CNT_HS_DET_IRQ_BIT_END       (4)
/* ��·hs_det_irq�ж�ȥ�������ܡ�
0��ȥ����������Ч��
1��ȥ����������Ч�� */
#define    HISSC_SMT_BYPASS_DEB_HS_DET_IRQ_BIT_START  (5)
#define    HISSC_SMT_BYPASS_DEB_HS_DET_IRQ_BIT_END    (5)


/* �Ĵ���˵����hs_mic_irqȥ������ */
#define HISSC_SMT_DEB_CNT_HS_MIC_CFG_ADDR             ((PAGE_SmartStarCODEC) + (0x1B8))
/* ȥ�������ڼ���������32kʱ�Ӽ���
����Ϊ1ms*����ֵ��
Ĭ������Ϊ10*1ms = 10ms
��ʱ��Χ��0~32ms */
#define    HISSC_SMT_DEB_CNT_HS_MIC_IRQ_BIT_START     (0)
#define    HISSC_SMT_DEB_CNT_HS_MIC_IRQ_BIT_END       (4)
/* ��·hs_mic_irq�ж�ȥ�������ܡ�
0��ȥ����������Ч��
1��ȥ����������Ч�� */
#define    HISSC_SMT_BYPASS_DEB_HS_MIC_IRQ_BIT_START  (5)
#define    HISSC_SMT_BYPASS_DEB_HS_MIC_IRQ_BIT_END    (5)


/* �Ĵ���˵����reserved */
#define HISSC_SMT_CODEC_DIG_RES02_ADDR                ((PAGE_SmartStarCODEC) + (0x1B9))


/* �Ĵ���˵����reserved */
#define HISSC_SMT_CODEC_DIG_RES03_ADDR                ((PAGE_SmartStarCODEC) + (0x1BA))


/* �Ĵ���˵����ADCͨ·PD�ź� */
#define HISSC_SMT_CODEC_ANA_RW01_ADDR                 ((PAGE_SmartStarCODEC) + (0x1BB))
/* LINEPGAR_PD�����ź�(LINEPGAR_PD):
0������������
1��PD */
#define    HISSC_SMT_LINEPGAR_PD_BIT_START  (0)
#define    HISSC_SMT_LINEPGAR_PD_BIT_END    (0)
/* LINEPGAL_PD�����ź�(LINEPGAL_PD):
0������������
1��PD */
#define    HISSC_SMT_LINEPGAL_PD_BIT_START  (1)
#define    HISSC_SMT_LINEPGAL_PD_BIT_END    (1)
/* AUXPGA_PD�����ź�(AUXPGAR_PD):
0������������
1��PD */
#define    HISSC_SMT_AUXPGA_PD_BIT_START    (2)
#define    HISSC_SMT_AUXPGA_PD_BIT_END      (2)
/* MAINPGA_PD�����ź�(MAINPGAR_PD):
0������������
1��PD */
#define    HISSC_SMT_MAINPGA_PD_BIT_START   (3)
#define    HISSC_SMT_MAINPGA_PD_BIT_END     (3)
/* ADCR PD�����ź�(ADCR_PD):
0������������
1��PD */
#define    HISSC_SMT_ADCR_PD_BIT_START      (4)
#define    HISSC_SMT_ADCR_PD_BIT_END        (4)
/* ADCL PD�����ź�(ADCL_PD):
0������������
1��PD */
#define    HISSC_SMT_ADCL_PD_BIT_START      (5)
#define    HISSC_SMT_ADCL_PD_BIT_END        (5)


/* �Ĵ���˵����MICBIAS,MBHD�ź� */
#define HISSC_SMT_CODEC_ANA_RW02_ADDR                 ((PAGE_SmartStarCODEC) + (0x1BC))
/* ����оƬ��Ibias���ϵ�����ź�(IBIAS_PD)��
0������������
1��PD�� */
#define    HISSC_SMT_IBIAS_PD_BIT_START      (0)
#define    HISSC_SMT_IBIAS_PD_BIT_END        (0)
/* MBHD buff�ϵ�����ź�(MBHD_BUFF_PD)��
0������������
1��PD */
#define    HISSC_SMT_MBHD_BUFF_PD_BIT_START  (4)
#define    HISSC_SMT_MBHD_BUFF_PD_BIT_END    (4)
/* MBHD comp�ϵ�����ź�(MBHD_COMP_PD)��
0������������
1��PD */
#define    HISSC_SMT_MBHD_COMP_PD_BIT_START  (5)
#define    HISSC_SMT_MBHD_COMP_PD_BIT_END    (5)
/* ����MICBIAS�ϵ�����ź�(HSMICB_PD)��
0������������
1��PD */
#define    HISSC_SMT_HSMICB_PD_BIT_START     (6)
#define    HISSC_SMT_HSMICB_PD_BIT_END       (6)
/* MICBIAS1�ϵ�����ź�(MICB1_PD)��
0������������
1��PD */
#define    HISSC_SMT_MICB1_PD_BIT_START      (7)
#define    HISSC_SMT_MICB1_PD_BIT_END        (7)


/* �Ĵ���˵����Headphone��MIXEROUT��PD�ź� */
#define HISSC_SMT_CODEC_ANA_RW03_ADDR                 ((PAGE_SmartStarCODEC) + (0x1BD))
/* HeadphoneR�ϵ�����ź�(HSR_PD)��
0������������
1��PD */
#define    HISSC_SMT_HSR_PD_BIT_START         (1)
#define    HISSC_SMT_HSR_PD_BIT_END           (1)
/* HeadphoneL�ϵ�����ź�(HSL_PD)��
0������������
1��PD */
#define    HISSC_SMT_HSL_PD_BIT_START         (2)
#define    HISSC_SMT_HSL_PD_BIT_END           (2)
/* MIXOUT_HSR�ϵ�����ź�(MIXOUT_HSR_PD)��
0������������
1��PD */
#define    HISSC_SMT_MIXOUT_HSR_PD_BIT_START  (4)
#define    HISSC_SMT_MIXOUT_HSR_PD_BIT_END    (4)
/* MIXOUT_HSL�ϵ�����ź�(MIXOUT_HSL_PD)��
0������������
1��PD */
#define    HISSC_SMT_MIXOUT_HSL_PD_BIT_START  (5)
#define    HISSC_SMT_MIXOUT_HSL_PD_BIT_END    (5)


/* �Ĵ���˵����VREF����ѡ���ź� */
#define HISSC_SMT_CODEC_ANA_RW04_ADDR                 ((PAGE_SmartStarCODEC) + (0x1BE))
/* VREF ����ѡ���źţ�VREFSEL<1:0>��;
00:��Ч��
01: 100kohm ��ѹ����
10: 500kohm ��ѹ����
11: 1kohm ��ѹ���� */
#define    HISSC_SMT_VREFSEL_BIT_START   (0)
#define    HISSC_SMT_VREFSEL_BIT_END     (1)


/* �Ĵ���˵����LINEPGALͨ·ѡ����������ź� */
#define HISSC_SMT_CODEC_ANA_RW05_ADDR                 ((PAGE_SmartStarCODEC) + (0x1BF))
/* LINEPGAL��ͨ·MUTE�ź�(LINEPGAL_MUTE)��
0:ͨ·����������
1��ͨ·MUTE; */
#define    HISSC_SMT_LINEPGAL_MUTE_BIT_START  (0)
#define    HISSC_SMT_LINEPGAL_MUTE_BIT_END    (0)
/* LINEPGAL��ͨ·�����ź�(LINEPGAL_GAIN<3:0>)��
���淶Χ:-14dB~16dB��
����Ϊ2dB��
0000:-14dB��
0001:-12dB��
0010��-10dB��
����
0111:0dB��
����
1110:14dB��
1111:16dB�� */
#define    HISSC_SMT_LINEPGAL_GAIN_BIT_START  (1)
#define    HISSC_SMT_LINEPGAL_GAIN_BIT_END    (4)
/* LINEPGAL��ͨ·ѡ���ź�(LINEPGAL_SEL<1:0>)��
01:LINEINL��LINEINR��ɲ�����룻
10:LINEINL��VCM��ɵ������룻
other����Ч��MUTE; */
#define    HISSC_SMT_LINEPGAL_SEL_BIT_START   (5)
#define    HISSC_SMT_LINEPGAL_SEL_BIT_END     (6)


/* �Ĵ���˵����LINEPGARͨ·ѡ��������ƿ����ź� */
#define HISSC_SMT_CODEC_ANA_RW06_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C0))
/* LINEPGAR��ͨ·MUTE�ź�(LINEPGAR_MUTE)��
0:ͨ·����������
1��ͨ·MUTE; */
#define    HISSC_SMT_LINEPGAR_MUTE_BIT_START  (0)
#define    HISSC_SMT_LINEPGAR_MUTE_BIT_END    (0)
/* LINEPGAR��ͨ·�����ź�(LINEPGAR_GAIN<3:0>)��
���淶Χ:-14dB~16dB��
����Ϊ2dB��
0000:-14dB��
0001:-12dB��
0010��-10dB��
����
0111:0dB��
����
1110:14dB��
1111:16dB�� */
#define    HISSC_SMT_LINEPGAR_GAIN_BIT_START  (1)
#define    HISSC_SMT_LINEPGAR_GAIN_BIT_END    (4)
/* LINEPGAR��ͨ·ѡ���ź�(LINEPGAR_SEL<1:0>)��
01:LINEINR��LINEINL��ɲ�����룻
10:LINEINR��VCM��ɵ������룻
other����Ч��MUTE; */
#define    HISSC_SMT_LINEPGAR_SEL_BIT_START   (5)
#define    HISSC_SMT_LINEPGAR_SEL_BIT_END     (6)


/* �Ĵ���˵����AUXPGARͨ·ѡ��������ƿ����ź� */
#define HISSC_SMT_CODEC_ANA_RW07_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C1))
/* AUXPGA��ͨ·ѡ���ź�(AUXPGA_SEL<1:0>)��
00:PD��Ч
01:AUXMIC����
10:ѡ��VCM���룻
11����Ч��MUTE�� */
#define    HISSC_SMT_AUXPGA_SEL_BIT_START         (0)
#define    HISSC_SMT_AUXPGA_SEL_BIT_END           (1)
/* AUXPGA��ͨ·MUTE�ź�(AUXPGA_MUTE)��
0:ͨ·����������
1��ͨ·MUTE; */
#define    HISSC_SMT_AUXPGA_MUTE_BIT_START        (2)
#define    HISSC_SMT_AUXPGA_MUTE_BIT_END          (2)
/* AUXPGA��ͨ·�����ź�(AUXPGA_GAIN<2:0>)��
���淶Χ:0dB~14dB��
����Ϊ2dB��
000: 0dB��
001: 2dB��
010: 4dB��
011: 6dB��
100: 8dB��
101: 10dB��
110: 12dB��
111: 14dB�� */
#define    HISSC_SMT_AUXPGA_GAIN_BIT_START        (3)
#define    HISSC_SMT_AUXPGA_GAIN_BIT_END          (5)
/* AUXPGA��BOOST�����ź�(AUXPGA_BOOST)��
0:�������棻
1:26dB���棻 */
#define    HISSC_SMT_AUXPGA_BOOST_BIT_START       (6)
#define    HISSC_SMT_AUXPGA_BOOST_BIT_END         (6)
/* MICPGA�����������źţ�MICPGA_UNLOCK_BPS����
0:��������Ч��
1:��������Ч�� */
#define    HISSC_SMT_MICPGA_UNLOCK_BPS_BIT_START  (7)
#define    HISSC_SMT_MICPGA_UNLOCK_BPS_BIT_END    (7)


/* �Ĵ���˵����MAINPGARͨ·ѡ��������ƿ����ź� */
#define HISSC_SMT_CODEC_ANA_RW08_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C2))
/* MAINPGA��ͨ·MUTE�ź�(MAINPGA_MUTE)��
0:ͨ·����������
1��ͨ·MUTE; */
#define    HISSC_SMT_MAINPGA_MUTE_BIT_START   (0)
#define    HISSC_SMT_MAINPGA_MUTE_BIT_END     (0)
/* MAINPGA��ͨ·�����ź�(MAINPGA_GAIN<2:0>)��
���淶Χ:0dB~14dB��
����Ϊ2dB��
000: 0dB��
001: 2dB��
010: 4dB��
011: 6dB��
100: 8dB��
101: 10dB��
110: 12dB��
111: 14dB�� */
#define    HISSC_SMT_MAINPGA_GAIN_BIT_START   (1)
#define    HISSC_SMT_MAINPGA_GAIN_BIT_END     (3)
/*  */
#define    HISSC_SMT_MAINPGA_BOOST_BIT_START  (4)
#define    HISSC_SMT_MAINPGA_BOOST_BIT_END    (4)
/* MAINPGA��ͨ·ѡ���ź�(MAINPGA_SEL)��
01��ѡ���ֻ�MIC���룻
10:ѡ�����HP MIC���룻
others����Ч��MUTE�� */
#define    HISSC_SMT_MAINPGA_SEL_BIT_START    (5)
#define    HISSC_SMT_MAINPGA_SEL_BIT_END      (6)


/* �Ĵ���˵����ADCR_MIXINͨ·ѡ���ź� */
#define HISSC_SMT_CODEC_ANA_RW09_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C3))
/* ADCR_MIXIN�������ź�ͨ·ѡ������ź�(ADCR_MIXIN<5:0>):
XXXXX1:AUXPGA������źţ�
XXXX1X:MAINPGA������źţ�
XXX1XX:LINEINR������źţ�
XX1XXX:LINEINL������źţ�
X1XXXX:DACR������źţ�
1XXXXX:DACL������źţ�
master:adcr_pd */
#define    HISSC_SMT_ADCR_MIXIN_BIT_START  (0)
#define    HISSC_SMT_ADCR_MIXIN_BIT_END    (5)


/* �Ĵ���˵����ADCL_MIXINͨ·ѡ���ź� */
#define HISSC_SMT_CODEC_ANA_RW10_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C4))
/* ADCL_MIXIN�������ź�ͨ·ѡ������ź�(ADCL_MIXIN<5:0>):
XXXXX1:AUXPGA������źţ�
XXXX1X:MAINPGA������źţ�
XXX1XX:LINEINR������źţ�
XX1XXX:LINEINL������źţ�
X1XXXX:DACR������źţ�
1XXXXX:DACL������źţ�
master:adcl_pd */
#define    HISSC_SMT_ADCL_MIXIN_BIT_START  (0)
#define    HISSC_SMT_ADCL_MIXIN_BIT_END    (5)


/* �Ĵ���˵����ADCLʱ������ź� */
#define HISSC_SMT_CODEC_ANA_RW11_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C5))
/* ADCLͨ·DWA Baypass�����ź�(ADCL_DWA_BPS):
0:��DWA��
1:Baypass DWA���ܣ� */
#define    HISSC_SMT_ADCL_DWA_BPS_BIT_START      (0)
#define    HISSC_SMT_ADCL_DWA_BPS_BIT_END        (0)
/* ADCL��FlashADC�Ĳο���ѹѡ���ź�(ADCL_FLSTN<1:0>):
00:�ο���ѹΪ1.05����
01:�ο���ѹΪ1����
10:�ο���ѹΪ0.95����
11:�ο���ѹΪ0.9���� */
#define    HISSC_SMT_ADCL_FLSTN_BIT_START        (1)
#define    HISSC_SMT_ADCL_FLSTN_BIT_END          (2)
/* ADCL�ķ���DAC��ƫ��ѡ���ź�(ADCL_DAC_BIAS<1:0>):
00:ƫ�õ�ѹΪ0.9����
01:ƫ�õ�ѹΪ0.95����
10:ƫ�õ�ѹΪ1����
11:ƫ�õ�ѹΪ1.1���� */
#define    HISSC_SMT_ADCL_DAC_BIAS_BIT_START     (3)
#define    HISSC_SMT_ADCL_DAC_BIAS_BIT_END       (4)
/* ADCL_CLK_DELAY<0>:ADCL�ڲ�CLKʱ��(CLK_TIMING_SEL)��
0: Ĭ����ʱ
1: ������ʱ */
#define    HISSC_SMT_ADCL_CLK_DELAY_0_BIT_START  (5)
#define    HISSC_SMT_ADCL_CLK_DELAY_0_BIT_END    (5)
/* ADCL_CLK_DELAY<1>:ADCL�ڲ�CLK��ʱ(CLK_DELAY_SEL)��
0: Ĭ����ʱ
1: ������ʱ */
#define    HISSC_SMT_ADCL_CLK_DELAY_1_BIT_START  (6)
#define    HISSC_SMT_ADCL_CLK_DELAY_1_BIT_END    (6)
/* ADCL_CLK_DELAY<2>:ADCL��������ݵ�ʱ(DOUT_TIMING_SEL)��
0: Ĭ����ʱ
1: ������ʱ */
#define    HISSC_SMT_ADCL_CLK_DELAY_2_BIT_START  (7)
#define    HISSC_SMT_ADCL_CLK_DELAY_2_BIT_END    (7)


/* �Ĵ���˵����ADCRʱ������ź� */
#define HISSC_SMT_CODEC_ANA_RW12_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C6))
/* ADCRͨ·DWA Baypass�����ź�(ADCR_DWA_BPS):
0:��DWA��
1:Baypass DWA���ܣ� */
#define    HISSC_SMT_ADCR_DWA_BPS_BIT_START      (0)
#define    HISSC_SMT_ADCR_DWA_BPS_BIT_END        (0)
/* ADCR��FlashADC�Ĳο���ѹѡ���ź�(ADCR_FLSTN<1:0>):
00:�ο���ѹΪ1.05����
01:�ο���ѹΪ1����
10:�ο���ѹΪ0.95����
11:�ο���ѹΪ0.9���� */
#define    HISSC_SMT_ADCR_FLSTN_BIT_START        (1)
#define    HISSC_SMT_ADCR_FLSTN_BIT_END          (2)
/* ADCR�ķ���DAC��ƫ��ѡ���ź�(ADCR_DAC_BIAS<1:0>):
00:ƫ�õ�ѹΪ0.9����
01:ƫ�õ�ѹΪ0.95����
10:ƫ�õ�ѹΪ1����
11:ƫ�õ�ѹΪ1.1���� */
#define    HISSC_SMT_ADCR_DAC_BIAS_BIT_START     (3)
#define    HISSC_SMT_ADCR_DAC_BIAS_BIT_END       (4)
/* ADCR_CLK_DELAY<0>:ADCR�ڲ�CLKʱ��(CLK_TIMING_SEL)��
0: Ĭ����ʱ
1: ������ʱ */
#define    HISSC_SMT_ADCR_CLK_DELAY_0_BIT_START  (5)
#define    HISSC_SMT_ADCR_CLK_DELAY_0_BIT_END    (5)
/* ADCR_CLK_DELAY<1>:ADCR�ڲ�CLK��ʱ(CLK_DELAY_SEL)��
0: Ĭ����ʱ
1: ������ʱ */
#define    HISSC_SMT_ADCR_CLK_DELAY_1_BIT_START  (6)
#define    HISSC_SMT_ADCR_CLK_DELAY_1_BIT_END    (6)
/*
ADCR_CLK_DELAY<2>:ADCR��������ݵ�ʱ��(DOUT_TIMING_SEL)��
0: Ĭ����ʱ
1: ������ʱ */
#define    HISSC_SMT_ADCR_CLK_DELAY_2_BIT_START  (7)
#define    HISSC_SMT_ADCR_CLK_DELAY_2_BIT_END    (7)


/* �Ĵ���˵����MIXOUT_HSL��MIXOUT_HSRͨ·ѡ���ź� */
#define HISSC_SMT_CODEC_ANA_RW13_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C7))
/* MIXOUT_HSR�������ź�ͨ·ѡ������ź�(MIXOUT_HSR<3:0>):
XXX1:LINEINR������źţ�
XX1X:LINEINL������źţ�
X1XX:DACR������źţ�
1XXX:DACL������źţ�
master:mixout_hsr_pd */
#define    HISSC_SMT_MIXOUT_HSR_BIT_START  (0)
#define    HISSC_SMT_MIXOUT_HSR_BIT_END    (3)
/* MIXOUT_HSL�������ź�ͨ·ѡ������ź�(MIXOUT_HSL<3:0>):
XXX1:LINEINR������źţ�
XX1X:LINEINL������źţ�
X1XX:DACR������źţ�
1XXX:DACL������źţ�
master:mixout_hsl_pd */
#define    HISSC_SMT_MIXOUT_HSL_BIT_START  (4)
#define    HISSC_SMT_MIXOUT_HSL_BIT_END    (7)


/* �Ĵ���˵����MIXOUT_EARͨ·ѡ���źţ�����ѡ���ź� */
#define HISSC_SMT_CODEC_ANA_RW14_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C8))
/* MIXOUT_EAR��0dB,-6dBѡ������ź�(CR_MIXF<3:0>):
XXX1:LINEINR֧·0dB��XXX0:LINEINR֧·-6dB
XX1X:LINEINL֧·0dB��XX0X:LINEINL֧·-6dB
X1XX:DACR֧·0dB��X0XX:DACR֧·-6dB
1XXX:DACL֧·0dB��0XXX:DACL֧·-6dB�� */
#define    HISSC_SMT_CR_MIXF_BIT_START     (0)
#define    HISSC_SMT_CR_MIXF_BIT_END       (3)
/* MIXOUT_EAR�������ź�ͨ·ѡ������ź�(MIXOUT_EAR<3:0>):
XXX1:LINEINR������źţ�
XX1X:LINEINL������źţ�
X1XX:DACR������źţ�
1XXX:DACL������źţ�
master:mixout_ear_pd */
#define    HISSC_SMT_MIXOUT_EAR_BIT_START  (4)
#define    HISSC_SMT_MIXOUT_EAR_BIT_END    (7)


/* �Ĵ���˵����DACICELL���������źţ�ChargePump����ʱ������ź� */
#define HISSC_SMT_CODEC_ANA_RW15_ADDR                 ((PAGE_SmartStarCODEC) + (0x1C9))
/* Charge Pump����ʱ������ʱ������źţ�CP_DTC_3<1:0>)��
00:10ns��Ĭ�ϣ�
01:20ns
10:30ns
11:50ns */
#define    HISSC_SMT_CP_DTC_3_BIT_START    (0)
#define    HISSC_SMT_CP_DTC_3_BIT_END      (1)
/* Charge Pump����ʱ������ʱ������źţ�CP_DTC_2<1:0>)��
00:10ns��Ĭ�ϣ�
01:20ns
10:30ns
11:50ns */
#define    HISSC_SMT_CP_DTC_2_BIT_START    (2)
#define    HISSC_SMT_CP_DTC_2_BIT_END      (3)
/* DACR ICELLS�ĵ��������ź�(DACR_ICTRL<1:0>):
00:������Ϊ0.9����
01:����������
10:������Ϊ1.1����
11:������Ϊ1.2���� */
#define    HISSC_SMT_DACR_ICTRL_BIT_START  (4)
#define    HISSC_SMT_DACR_ICTRL_BIT_END    (5)
/* DACL ICELLS�ĵ��������ź�(DACL_ICTRL<1:0>):
00:������Ϊ0.9����
01:����������
10:������Ϊ1.1����
11:������Ϊ1.2���� */
#define    HISSC_SMT_DACL_ICTRL_BIT_START  (6)
#define    HISSC_SMT_DACL_ICTRL_BIT_END    (7)


/* �Ĵ���˵����Headphonesoftʹ���źţ�ChargePump�����ź� */
#define HISSC_SMT_CODEC_ANA_RW16_ADDR                 ((PAGE_SmartStarCODEC) + (0x1CA))
/* Change Pump ��ͨ������������ѡ��CP_DR_CTRL<1:0>);
00: ��С������Ĭ�ϣ�
01: ��С����
10: �ϴ�����
11:������� */
#define    HISSC_SMT_CP_DR_CTRL_BIT_START  (0)
#define    HISSC_SMT_CP_DR_CTRL_BIT_END    (1)
/* CLASSGģʽ��������ȵĲο�ѡ���ź�(CLASSG_REF<1:0>):
00: VREFΪ200mV��
01: VREFΪ400mV��
10: VREFΪ300mV��
11: VREFΪ500mV�� */
#define    HISSC_SMT_CLASSG_REF_BIT_START  (2)
#define    HISSC_SMT_CLASSG_REF_BIT_END    (3)
/* Charge Pump�������ѹ��ģʽ�����ź�(CP_MODE<1:0>):
00:�̶��������1.8V�ĵ�Դ��
01:�̶��������0.9V�ĵ�Դ��
10:CLASSGģʽ�������ѹ�������źſɵ���
11:CLASSGģʽ�������ѹ�������źſɵ��� */
#define    HISSC_SMT_CP_MODE_BIT_START     (4)
#define    HISSC_SMT_CP_MODE_BIT_END       (5)
/* Headphone����ģʽ��CLASSGģʽƫ�ùܵ����źţ�EN_CP_MODE��:
0: ƫ�ùܱ�׼ģʽ��
1: ƫ�ùܵ���ģʽ�� */
#define    HISSC_SMT_EN_CP_MODE_BIT_START  (6)
#define    HISSC_SMT_EN_CP_MODE_BIT_END    (6)
/* Headphone softʹ�ܿ����ź�(HP_SOFT_EN):
0: ����ʹ�ܣ�
1: softʹ�ܣ� */
#define    HISSC_SMT_HP_SOFT_EN_BIT_START  (7)
#define    HISSC_SMT_HP_SOFT_EN_BIT_END    (7)


/* �Ĵ���˵����HeadphoneL��������ź� */
#define HISSC_SMT_CODEC_ANA_RW17_ADDR                 ((PAGE_SmartStarCODEC) + (0x1CB))
/* HeadphoneL��ͨ·��С����ѡ���ź�(HSL_MIN_GAIN)��
0:��С����(-26dB)��Ч��
1����С����(-26dB)��Ч; */
#define    HISSC_SMT_HSL_MIN_GAIN_BIT_START  (0)
#define    HISSC_SMT_HSL_MIN_GAIN_BIT_END    (0)
/* HeadphoneL��ͨ·�����ź�(HSL_GAIN<3:0>)��
���淶Χ:-20dB~-0dB��
����Ϊ1.5dB��
0000:-20dB��
0001:-18dB��
0010��-16.5dB��
0011: -15dB;
0100:-13.5dB;
0101:-12dB;
0110:-10.5dB;
0111:-9.5dB;
1000:-8.5dB;
1001:-7.5dB;
1010:-6.5dB;
1011:-5.5dB;
1100:-4.5dB;
1101:-3dB;
1110:-1.5dB;
1111:0dB; */
#define    HISSC_SMT_HSL_GAIN_BIT_START      (1)
#define    HISSC_SMT_HSL_GAIN_BIT_END        (4)
/* HeadphoneL��ͨ·MUTE�ź�(HSL_MUTE)��
0:ͨ·����������
1��ͨ·MUTE; */
#define    HISSC_SMT_HSL_MUTE_BIT_START      (5)
#define    HISSC_SMT_HSL_MUTE_BIT_END        (5)
/* HeadphoneL��POPС��·MUTE�ź�(HS_LIT_LP_L)��
0��С��·MUTE��ʹ�� ����ʱС��·��mute��hsl_mute���ƣ�
1��С��·MUTEʹ��; */
#define    HISSC_SMT_HS_LIT_LP_L_BIT_START   (6)
#define    HISSC_SMT_HS_LIT_LP_L_BIT_END     (6)


/* �Ĵ���˵����HeadphonR��������ź� */
#define HISSC_SMT_CODEC_ANA_RW18_ADDR                 ((PAGE_SmartStarCODEC) + (0x1CC))
/* HeadphoneR��ͨ·��С����ѡ���ź�(HSR_MIN_GAIN)��
0:��С����(-26dB)��Ч��
1����С����(-26dB)��Ч; */
#define    HISSC_SMT_HSR_MIN_GAIN_BIT_START  (0)
#define    HISSC_SMT_HSR_MIN_GAIN_BIT_END    (0)
/* HeadphoneR��ͨ·�����ź�(HSR_GAIN<3:0>)��
���淶Χ:-20dB~-0dB��
����Ϊ1.5dB��
0000:-20dB��
0001:-18dB��
0010��-16.5dB��
0011: -15dB;
0100:-13.5dB;
0101:-12dB;
0110:-10.5dB;
0111:-9.5dB;
1000:-8.5dB;
1001:-7.5dB;
1010:-6.5dB;
1011:-5.5dB;
1100:-4.5dB;
1101:-3dB;
1110:-1.5dB;
1111:0dB; */
#define    HISSC_SMT_HSR_GAIN_BIT_START      (1)
#define    HISSC_SMT_HSR_GAIN_BIT_END        (4)
/* HeadphoneR��ͨ·MUTE�ź�(HSR_MUTE)��
0:ͨ·����������
1��ͨ·MUTE; */
#define    HISSC_SMT_HSR_MUTE_BIT_START      (5)
#define    HISSC_SMT_HSR_MUTE_BIT_END        (5)
/* HeadphoneR��POPС��·MUTE�ź�(HS_LIT_LP_R)��
0��С��·MUTE��ʹ�� ����ʱС��·��mute��hsl_mute���ƣ�
1��С��·MUTEʹ��; */
#define    HISSC_SMT_HS_LIT_LP_R_BIT_START   (6)
#define    HISSC_SMT_HS_LIT_LP_R_BIT_END     (6)


/* �Ĵ���˵����Earphone��������ź� */
#define HISSC_SMT_CODEC_ANA_RW19_ADDR                 ((PAGE_SmartStarCODEC) + (0x1CD))
/* EAR�Ĺ�ģ�����ź�(EAR_CM_CTRL):
0:�������500ŷķ���赽VCM��
1:�������30Kŷķ���赽VCM�� */
#define    HISSC_SMT_EAR_CM_CTRL_BIT_START  (0)
#define    HISSC_SMT_EAR_CM_CTRL_BIT_END    (0)
/* EAR��ͨ·�����ź�(EAR_GAIN<5:0>)��
���淶Χ:-20dB~-6dB��
����Ϊ2dB��
0000:-20dB��
0001:-18dB��
0010��-16dB��
0011: -14dB;
0100:-12dB;
0101:-10dB;
0110:-8dB;
0111:-6dB;
1000:-4dB;
1001:-2dB;
1010:-0dB;
1011:2dB;
1100:4dB;
1101:6dB;
orther: mute */
#define    HISSC_SMT_EAR_GAIN_BIT_START     (1)
#define    HISSC_SMT_EAR_GAIN_BIT_END       (4)
/* EAR��ͨ·MUTE�ź�(EAR_MUTE)��
0:ͨ·����������
1��ͨ·MUTE; */
#define    HISSC_SMT_EAR_MUTE_BIT_START     (5)
#define    HISSC_SMT_EAR_MUTE_BIT_END       (5)


/* �Ĵ���˵����POP����ʱ�����źţ�ramp������·�����ź� */
#define HISSC_SMT_CODEC_ANA_RW20_ADDR                 ((PAGE_SmartStarCODEC) + (0x1CE))
/* ramp������·,����clkѡ��(POP_RAMP_CT<2:0>��
000��48k
001��48k/2
010��48k/4
011��48k/8
1*0��48k/16
1*1��48k/32 */
#define    HISSC_SMT_POP_RAMP_CT_2_0_BIT_START  (0)
#define    HISSC_SMT_POP_RAMP_CT_2_0_BIT_END    (2)
/* ramp������·,�������(POP_RAMP_CT<3>)��
0��normal��������ʹ�ã�
1��mormal*1.5 */
#define    HISSC_SMT_POP_RAMP_CT_3_BIT_START    (3)
#define    HISSC_SMT_POP_RAMP_CT_3_BIT_END      (3)
/* ramp������·,capѡ��(POP_RAMP_CT<4>)��
0��normal��������ʹ�ã�
1��mormal*1.5 */
#define    HISSC_SMT_POP_RAMP_CT_4_BIT_START    (4)
#define    HISSC_SMT_POP_RAMP_CT_4_BIT_END      (4)
/* POP���ϵ���ʱ����(CLK_DL)��(clk_sel=0��������Ϊclk_sel=1)

000��7.98m (15.96m )
001��13.34m (26.68m)
010��18.68m (37.36m)
011��23.98m (47.96m)
100��29.28m (58.56m)
101��34.58m (69.16m)
110��39.88m (79.96m)
111��45.18m (90.36m) */
#define    HISSC_SMT_CLK_DL_BIT_START           (5)
#define    HISSC_SMT_CLK_DL_BIT_END             (7)


/* �Ĵ���˵������POP��·�����ź� */
#define HISSC_SMT_CODEC_ANA_RW21_ADDR                 ((PAGE_SmartStarCODEC) + (0x1CF))
/* RST HP��ͨ· POP������ģ��(RST_N_R)��
0��RST ��Ч
1��Normal�� */
#define    HISSC_SMT_RST_N_R_BIT_START   (0)
#define    HISSC_SMT_RST_N_R_BIT_END     (0)
/* RST HP��ͨ· POP������ģ��(RST_N_L)��
0��RST ��Ч
1��Normal�� */
#define    HISSC_SMT_RST_N_L_BIT_START   (1)
#define    HISSC_SMT_RST_N_L_BIT_END     (1)
/* POP������ģ��byassѡ��(POP_DIS)��
0��enable POP�����Ƶ�·��
1��bypass POP�����Ƶ�·�� */
#define    HISSC_SMT_POP_DIS_BIT_START   (2)
#define    HISSC_SMT_POP_DIS_BIT_END     (2)
/* POP����ʱ���Ƶ�·,clkѡ��(CLK_SEL)������1E7<7:5>���ʹ�ã�
0:188Hz��
1:94Hz�� */
#define    HISSC_SMT_CLK_SEL_BIT_START   (3)
#define    HISSC_SMT_CLK_SEL_BIT_END     (3)
/* HP PD�ź�delay ����(PDD_EN)��
0��PD�ź�ֱ�������HPģ�飻
1��PD�źž���delay�����HPģ�飻������ģʽ�� */
#define    HISSC_SMT_PDD_EN_BIT_START    (4)
#define    HISSC_SMT_PDD_EN_BIT_END      (4)

#define    HISSC_SMT_POP_NEW_BYPASS_BIT_START    (5)
#define    HISSC_SMT_POP_NEW_BYPASS_BIT_END      (5)

/* �Ĵ���˵����HSMICBIAS��MICBIAS1���ƫ�õ�ѹ�����ź� */
#define HISSC_SMT_CODEC_ANA_RW22_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D0))
/* MICBIAS1���ƫ�õ�ѹ�����ź�(MICB1_ADJ<2:0>):
000: 2.1V��
001: 2.2V��
010: 2.3V��
011: 2.4V��
100: 2.5V��
101: 2.6V��
110: 2.7V��
111: 2.8V�� */
#define    HISSC_SMT_MICB1_ADJ_BIT_START   (0)
#define    HISSC_SMT_MICB1_ADJ_BIT_END     (2)
/* HSMICBIAS���ƫ�õ�ѹ�����ź�(HSMICB_ADJ<2:0>):
000: 2.1V��
001: 2.2V��
010: 2.3V��
011: 2.4V��
100: 2.5V��
101: 2.6V��
110: 2.7V��
111: 2.8V�� */
#define    HISSC_SMT_HSMICB_ADJ_BIT_START  (3)
#define    HISSC_SMT_HSMICB_ADJ_BIT_END    (5)


/* �Ĵ���˵����HSD_CTRL<2:0>,HSMICBIAS,MICBIAS1�ŵ�ʹ���źţ�MBHDʹ���ź� */
#define HISSC_SMT_CODEC_ANA_RW23_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D1))
/* ECOģʽ�£�MBHDʹ���ź�(MBHD_ECO_EN):
0:��ʹ�ܣ�
1:ʹ�ܣ� */
#define    HISSC_SMT_MBHD_ECO_EN_BIT_START   (0)
#define    HISSC_SMT_MBHD_ECO_EN_BIT_END     (0)
/* MICBIAS1�ŵ�ʹ���ź�(MICB1_DSCHG):
0:��ʹ�ܣ�
1:ʹ�ܣ� */
#define    HISSC_SMT_MICB1_DSCHG_BIT_START   (1)
#define    HISSC_SMT_MICB1_DSCHG_BIT_END     (1)
/* HSMICBIAS�ŵ�ʹ���ź�(HSMICB_DSCHG):
0:��ʹ�ܣ�
1:ʹ�ܣ� */
#define    HISSC_SMT_HSMICB_DSCHG_BIT_START  (2)
#define    HISSC_SMT_HSMICB_DSCHG_BIT_END    (2)
/* HSD EN ����(HSD_CTRL<0>)��
0: HS ģ�鲻ʹ�ܣ�
1��HS ģ��ʹ�ܣ�������ģʽ�� */
#define    HISSC_SMT_HSD_CTRL_0_BIT_START    (3)
#define    HISSC_SMT_HSD_CTRL_0_BIT_END      (3)
/* HSD INV ����(HSD_CTRL<1>)��
0: HS ������򣻣�����ģʽ��
1��HS ��������� */
#define    HISSC_SMT_HSD_CTRL_1_BIT_START    (4)
#define    HISSC_SMT_HSD_CTRL_1_BIT_END      (4)
/* HSD POLLDOWN ���ƣ�HSD_CTRL<2>)��
0: Headset ģ������������������ģʽ��
1��HSD ���������� */
#define    HISSC_SMT_HSD_CTRL_2_BIT_START    (5)
#define    HISSC_SMT_HSD_CTRL_2_BIT_END      (5)


/* �Ĵ���˵����MBHD_VREF_CTRL<7:0> */
#define HISSC_SMT_CODEC_ANA_RW24_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D2))
/* Normalģʽ�£�COMPL�Ƚ�����ѹ��ֵ����λ����(mbhd_vref_ctrl<1:0>��
00: 600mV
01: 700mV
10: 800mV
11: 900mV */
#define    HISSC_SMT_MBHD_VREF_CTRL_1_0_BIT_START  (0)
#define    HISSC_SMT_MBHD_VREF_CTRL_1_0_BIT_END    (1)
/* Normalģʽ�£�COMPH�Ƚ�����ѹ��ֵ����λ����(mbhd_vref_ctrl<3:2>)��
00:80%*Vmicbias;
01:85%*Vmicbias;
10:90%Vmicbias;
11:95%*Vmicbias */
#define    HISSC_SMT_MBHD_VREF_CTRL_3_2_BIT_START  (2)
#define    HISSC_SMT_MBHD_VREF_CTRL_3_2_BIT_END    (3)
/* ECOģʽ�£�ECO_COMP�Ƚ�����ѹ��ֵ����λ����(mbhd_vref_ctrl<6:4>)��
000��100mV
001��125mV
010: 150mV
011: 175mV
100: 200mV
101: 225mV
110: 250mV
111��275mV */
#define    HISSC_SMT_MBHD_VREF_CTRL_6_4_BIT_START  (4)
#define    HISSC_SMT_MBHD_VREF_CTRL_6_4_BIT_END    (6)
/* �������ģ��Ƚ�����ѹ����PD�ź�(mbhd_vref_pd)��
0��VREF���Ƚ�������������
1��VREF���Ƚ���PD�������޶�����λ״̬�£�����PD=1�� */
#define    HISSC_SMT_MBHD_VREF_PD_BIT_START        (7)
#define    HISSC_SMT_MBHD_VREF_PD_BIT_END          (7)


/* �Ĵ���˵����CP_CLK_CTRL<7:0> */
#define HISSC_SMT_CODEC_ANA_RW25_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D3))
/* ChargePump�����Դ���л���ʱ�����ź�(CP_DET_SEL<1:0>):
00: 375Hz��
01: 187.5Hz��
10: 94Hz��
11: 47Hz�� */
#define    HISSC_SMT_CP_DET_SEL_BIT_START     (0)
#define    HISSC_SMT_CP_DET_SEL_BIT_END       (1)
/* ChargePump�����Դ���л���ʱ�����ź�PD��CP_DET_CLK_PD��:
0���������ʱ�ӣ�
1��PD */
#define    HISSC_SMT_CP_DET_CLK_PD_BIT_START  (2)
#define    HISSC_SMT_CP_DET_CLK_PD_BIT_END    (2)
/* ChargePump����ʱ�ӿ����źţ�CP_CLK_PD��:
0���������ʱ�ӣ�
1��PD */
#define    HISSC_SMT_CP_CLK_PD_BIT_START      (3)
#define    HISSC_SMT_CP_CLK_PD_BIT_END        (3)
/* ChargePump����Ƶ��ѡ���ź�(CP_SEL<2:0>):
000: 6.144MHz��
001: 3.072MHz��
010: 1.536MHz��
011: 768KHz��
100: 384KHz��
101: 192KHz��
110: 96KHz��
111: 48KHz�� */
#define    HISSC_SMT_CP_SEL_BIT_START         (4)
#define    HISSC_SMT_CP_SEL_BIT_END           (6)
/* Headphone ϵͳʱ��PD�źţ�HS_SYS_CLK_PD��
0���������ʱ�ӣ�
1��PD */
#define    HISSC_SMT_HS_SYS_CLK_PD_BIT_START  (7)
#define    HISSC_SMT_HS_SYS_CLK_PD_BIT_END    (7)


/* �Ĵ���˵����ADC��DACʱ����ѡ���źţ�ADC��DACchopperʱ��ѡ���ź� */
#define HISSC_SMT_CODEC_ANA_RW26_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D4))
/* DAC��chopperʱ��ѡ���ź�(DAC_CHOP_CLK_SEL<1:0>):
00: 3MHz��
01: 1.5MHz��
10: 750KHz��
11: 375KHz�� */
#define    HISSC_SMT_DAC_CHOP_CLK_SEL_BIT_START    (0)
#define    HISSC_SMT_DAC_CHOP_CLK_SEL_BIT_END      (1)
/* ADC��chopperʱ��ѡ���ź�(ADC_CHOP_CLK_SEL<1:0>):
00: 384KHz��
01: 192KHz��
10: 96KHz��
11: 48KHz�� */
#define    HISSC_SMT_ADC_CHOP_CLK_SEL_BIT_START    (2)
#define    HISSC_SMT_ADC_CHOP_CLK_SEL_BIT_END      (3)
/* DACʱ����λѡ���ź�(DAC_CLK_SYS_EDG_0):
0:DACʱ��ѡ�����Ƶ��ͬ��ʱ��
1:DACʱ��ѡ�����Ƶ����ʱ�� */
#define    HISSC_SMT_DAC_CLK_SYS_EDGE_0_BIT_START  (4)
#define    HISSC_SMT_DAC_CLK_SYS_EDGE_0_BIT_END    (4)
/* DACʱ����ѡ���ź�(DAC_CLK_SYS_EDG_1):
0:DACʱ����ͬ����12.288MHzʱ���ط��أ�
1:DACʱ����ͬ����12.288MHzʱ����ͬ�أ� */
#define    HISSC_SMT_DAC_CLK_SYS_EDGE_1_BIT_START  (5)
#define    HISSC_SMT_DAC_CLK_SYS_EDGE_1_BIT_END    (5)
/* ADCʱ����λѡ���ź�(ADC_CLK_SYS_EDG_0):
0:ADCʱ��ѡ�����Ƶ��ͬ��ʱ��
1:ADCʱ��ѡ�����Ƶ����ʱ�� */
#define    HISSC_SMT_ADC_CLK_SYS_EDGE_0_BIT_START  (6)
#define    HISSC_SMT_ADC_CLK_SYS_EDGE_0_BIT_END    (6)
/* ADCʱ����ѡ���ź�(ADC_CLK_SYS_EDG_1):
0:ADCʱ����ͬ����12.288MHzʱ���ط��أ�
1:ADCʱ����ͬ����12.288MHzʱ����ͬ�أ� */
#define    HISSC_SMT_ADC_CLK_SYS_EDGE_1_BIT_START  (7)
#define    HISSC_SMT_ADC_CLK_SYS_EDGE_1_BIT_END    (7)


/* �Ĵ���˵����RX��ADC_SDM,LINEIN,MICPGA,CTCM��chopperbaypass�ź� */
#define HISSC_SMT_CODEC_ANA_RW27_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D5))
/* CTCM Chopper Baypass�����ź�(CTCM_CHOP_BPS):
0:��Chopper���ܣ�
1:Baypass Chopper���ܣ� */
#define    HISSC_SMT_CTCM_CHOP_BPS_BIT_START     (0)
#define    HISSC_SMT_CTCM_CHOP_BPS_BIT_END       (0)
/* MICPGA Chopper Baypass�����ź�(MICPGA_CHOP_BPS):
0:��Chopper���ܣ�
1:Baypass Chopper���ܣ� */
#define    HISSC_SMT_MICPGA_CHOP_BPS_BIT_START   (1)
#define    HISSC_SMT_MICPGA_CHOP_BPS_BIT_END     (1)
/* LINEIN Chopper Baypass�����ź�(LINEIN_CHOP_BPS):
0:��Chopper���ܣ�
1:Baypass Chopper���ܣ� */
#define    HISSC_SMT_LINEIN_CHOP_BPS_BIT_START   (2)
#define    HISSC_SMT_LINEIN_CHOP_BPS_BIT_END     (2)
/* ADC_SDM Chopper Baypass�����ź�(ADC_SDM_CHOP_BPS):
0:��Chopper���ܣ�
1:Baypass Chopper���ܣ� */
#define    HISSC_SMT_ADC_SDM_CHOP_BPS_BIT_START  (3)
#define    HISSC_SMT_ADC_SDM_CHOP_BPS_BIT_END    (3)
/* RX Chopper Baypass�����ź�(RX_CHOP_BPS):
0:��Chopper���ܣ�
1:Baypass Chopper���ܣ� */
#define    HISSC_SMT_RX_CHOP_BPS_BIT_START       (4)
#define    HISSC_SMT_RX_CHOP_BPS_BIT_END         (4)


/* �Ĵ���˵����TX��DAC��MIXER_EAR,MIXER_HP��chopperbaypass�ź� */
#define HISSC_SMT_CODEC_ANA_RW28_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D6))
/* MIXER FOR Headphone Chopper Baypass�����ź�(HS_CHOP_BPS):
0:��Chopper���ܣ�
1:Baypass Chopper���ܣ� */
#define    HISSC_SMT_HS_CHOP_BPS_BIT_START       (0)
#define    HISSC_SMT_HS_CHOP_BPS_BIT_END         (0)
/* MIXER FOR Earphone and Classd Chopper Baypass�����ź�(EAR_CLD_CHOP_BPS):
0:��Chopper���ܣ�
1:Baypass Chopper���ܣ� */
#define    HISSC_SMT_EAR_CLD_CHOP_BPS_BIT_START  (1)
#define    HISSC_SMT_EAR_CLD_CHOP_BPS_BIT_END    (1)
/* DAC Chopper Baypass�����ź�(DAC_CHOP_BPS):
0:��Chopper���ܣ�
1:Baypass Chopper���ܣ� */
#define    HISSC_SMT_DAC_CHOP_BPS_BIT_START      (2)
#define    HISSC_SMT_DAC_CHOP_BPS_BIT_END        (2)
/* TX Chopper Baypass�����ź�(TX_CHOP_BPS):
0:��Chopper���ܣ�
1:Baypass Chopper���ܣ� */
#define    HISSC_SMT_TX_CHOP_BPS_BIT_START       (3)
#define    HISSC_SMT_TX_CHOP_BPS_BIT_END         (3)


/* �Ĵ���˵����CODEC_IBIAS_ADJ1��HeadphoneMIXER_HP���������źţ� */
#define HISSC_SMT_CODEC_ANA_RW29_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D7))
/* MIXER_HP�ĵ��������ź�:
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_MIXER_HP_BIT_START  (0)
#define    HISSC_SMT_IB05_MIXER_HP_BIT_END    (2)
/* Headphone_amp�ĵ��������ź�:
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_HP_BIT_START        (3)
#define    HISSC_SMT_IB05_HP_BIT_END          (5)


/* �Ĵ���˵����CODEC_IBIAS_ADJ2��DAC��ADC_OPA1���������źţ� */
#define HISSC_SMT_CODEC_ANA_RW30_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D8))
/* IB05_ADC_OPA1�ĵ��������ź�(IB05_ADC_OPA1):
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_ADC_OPA1_BIT_START  (0)
#define    HISSC_SMT_IB05_ADC_OPA1_BIT_END    (2)
/* DAC�ĵ��������ź�(IB05_DAC):
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_DAC_BIT_START       (3)
#define    HISSC_SMT_IB05_DAC_BIT_END         (5)


/* �Ĵ���˵����CODEC_IBIAS_ADJ3��ADC_OPA2��ADC_COMP���������źţ� */
#define HISSC_SMT_CODEC_ANA_RW31_ADDR                 ((PAGE_SmartStarCODEC) + (0x1D9))
/* IB05_ADC_COMP�ĵ��������ź�(IB05_ADC_COMP):
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_ADC_COMP_BIT_START  (0)
#define    HISSC_SMT_IB05_ADC_COMP_BIT_END    (2)
/* IB05_ADC_OPA2�ĵ��������ź�(IB05_ADC_OPA2):
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_ADC_OPA2_BIT_START  (3)
#define    HISSC_SMT_IB05_ADC_OPA2_BIT_END    (5)


/* �Ĵ���˵����CODEC_IBIAS_ADJ4��LINEIN��MICBIAS���������źţ� */
#define HISSC_SMT_CODEC_ANA_RW32_ADDR                 ((PAGE_SmartStarCODEC) + (0x1DA))
/* IB05_MICBIAS�ĵ��������ź�(IB05_MICBIAS):
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_MICBIAS_BIT_START     (0)
#define    HISSC_SMT_IB05_MICBIAS_BIT_END       (2)
/* IB05_ADC_LINEIN�ĵ��������ź�(IB05_ADC_LINEIN):
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_ADC_LINEIN_BIT_START  (3)
#define    HISSC_SMT_IB05_ADC_LINEIN_BIT_END    (5)


/* �Ĵ���˵����CODEC_IBIAS_ADJ5��reserved��AUXMIC���������źţ� */
#define HISSC_SMT_CODEC_ANA_RW33_ADDR                 ((PAGE_SmartStarCODEC) + (0x1DB))
/* IB05_AUXMIC�ĵ��������ź�(IB05_AUXMIC):
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_AUXMIC_BIT_START  (0)
#define    HISSC_SMT_IB05_AUXMIC_BIT_END    (2)
/* IB05_CTCM�ĵ��������ź�(IB05_CTCM):
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_REV_BIT_START     (3)
#define    HISSC_SMT_IB05_REV_BIT_END       (5)


/* �Ĵ���˵����CODEC_IBIAS_ADJ6��MAINMIC��MIXER_EAR���������źţ� */
#define HISSC_SMT_CODEC_ANA_RW34_ADDR                 ((PAGE_SmartStarCODEC) + (0x1DC))
/* IB05_MIXER_EAR�ĵ��������ź�(IB05_MIXER_EAR):
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_MIXER_EAR_BIT_START  (0)
#define    HISSC_SMT_IB05_MIXER_EAR_BIT_END    (2)
/* IB05_MAINMIC�ĵ��������ź�(IB05_MAINMIC):
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_MAINMIC_BIT_START    (3)
#define    HISSC_SMT_IB05_MAINMIC_BIT_END      (5)


/* �Ĵ���˵����CODEC_IBIAS_ADJ7��EAR��CODECȫ�ֵ��������źţ� */
#define HISSC_SMT_CODEC_ANA_RW35_ADDR                 ((PAGE_SmartStarCODEC) + (0x1DD))
/* CODEC��ȫ�ֵ��������ź�(CODEC_IBIAS_ADJ):
0:5uA��
1:7.5uA�� */
#define    HISSC_SMT_CODEC_BIAS_ADJ_BIT_START  (0)
#define    HISSC_SMT_CODEC_BIAS_ADJ_BIT_END    (0)
/* IB05_EAR�ĵ��������ź�(IB05_EAR):
000: 2.5uA��
001: 3uA��
010: 3.5uA��
011: 4uA��
100: 4.5uA��
101: 5uA��
110: 7uA��
111: 9uA�� */
#define    HISSC_SMT_IB05_EAR_BIT_START        (1)
#define    HISSC_SMT_IB05_EAR_BIT_END          (3)


/* �Ĵ���˵����ADC_DACģ�⻷�ؿ����ź� */
#define HISSC_SMT_CODEC_ANA_RW36_ADDR                 ((PAGE_SmartStarCODEC) + (0x1DE))
/* CODECģ��ADC_DAC���ؿ����ź�(ANALOG_LOOP):
0:�����أ�
1:���أ�(ADCL_DACL,ADCR_DACR) */
#define    HISSC_SMT_ANALOG_LOOP_BIT_START  (0)
#define    HISSC_SMT_ANALOG_LOOP_BIT_END    (0)

/* �Ĵ���˵����HP_BIAS_PD ��CP_PD��CP_DET_PD�����ź� */
#define HISSC_SMT_CODEC_ANA_RW37_ADDR                 ((PAGE_SmartStarCODEC) + (0x1DF))
/* ChargePump Detect�ϵ�����ź�(CP_DET_PD)��
0��PD��
1����������; */
#define    HISSC_SMT_CP_DET_PU_BIT_START   (0)
#define    HISSC_SMT_CP_DET_PU_BIT_END     (0)
/* ChargePump�ϵ�����ź�(CP_PD)��
0��PD��
1����������; */
#define    HISSC_SMT_CP_PU_BIT_START       (1)
#define    HISSC_SMT_CP_PU_BIT_END         (1)
/* Headphone ibias�ϵ�����źţ�HP_BIAS_PD��
0��PD��
1����������; */
#define    HISSC_SMT_HP_BIAS_PU_BIT_START  (2)
#define    HISSC_SMT_HP_BIAS_PU_BIT_END    (2)

/* �Ĵ���˵����DACL_PD��DACR_PD */
#define HISSC_SMT_CODEC_ANA_RW38_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E0))
/* DACR�ϵ�����ź�(DACR_PD)��
0��PD��
1����������; */
#define    HISSC_SMT_DACR_PU_BIT_START   (0)
#define    HISSC_SMT_DACR_PU_BIT_END     (0)
/* DACL�ϵ�����ź�(DACL_PD)��
0��PD��
1����������; */
#define    HISSC_SMT_DACL_PU_BIT_START   (1)
#define    HISSC_SMT_DACL_PU_BIT_END     (1)


/* �Ĵ���˵����MIXOUT_EAR_PD��EAR_PD */
#define HISSC_SMT_CODEC_ANA_RW39_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E1))
/* EAR�ϵ�����ź�(EAR_PD)��
0��PD��
1����������; */
#define    HISSC_SMT_EAR_PU_BIT_START         (0)
#define    HISSC_SMT_EAR_PU_BIT_END           (0)
/* MIXOUT_EAR�ϵ�����ź�(MIXOUT_EAR_PD)��
0��PD��
1����������; */
#define    HISSC_SMT_MIXOUT_EAR_PU_BIT_START  (1)
#define    HISSC_SMT_MIXOUT_EAR_PU_BIT_END    (1)

/* �Ĵ���˵����CODEC_ANA_RW40 */
#define HISSC_SMT_CODEC_ANA_RW40_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E2))
/*  */
#define    HISSC_SMT_CODEC_ANA_REG40_BIT_START  (0)
#define    HISSC_SMT_CODEC_ANA_REG40_BIT_END    (7)


/* �Ĵ���˵����CODEC_ANA_RO01 */
#define HISSC_SMT_CODEC_ANA_RO01_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E3))
/*  */
#define    HISSC_SMT_CODEC_ANA_RO01_BIT_START  (0)
#define    HISSC_SMT_CODEC_ANA_RO01_BIT_END    (7)


/* �Ĵ���˵����CODEC_ANA_RO02 */
#define HISSC_SMT_CODEC_ANA_RO02_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E4))
/*  */
#define    HISSC_SMT_CODEC_ANA_RO02_BIT_START  (0)
#define    HISSC_SMT_CODEC_ANA_RO02_BIT_END    (7)

/* �Ĵ���˵����CODEC_ANA_RW41 */
#define HISSC_SMT_CODEC_ANA_RW41_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E5))

/* �Ĵ���˵����CODEC_ANA_RW42 */
#define HISSC_SMT_CODEC_ANA_RW42_ADDR                 ((PAGE_SmartStarCODEC) + (0x1E6))

/* �Ĵ���˵����CODEC_CLASSD_CTRL3 */
#define HISSC_PMU_CODEC_CLASSD_CTRL3_ADDR             ((PAGE_PMCTRL) + (0x6B))
#define    HISSC_PMU_CODEC_CLASSD_DRV_EN_BIT  (4)
#define    HISSC_PMU_CODEC_EN_CLASSD_INT_BIT  (3)

/* �Ĵ���˵����CODEC_CLASSD_CTRL1 */
#define HISSC_PMU_CODEC_CLASSD_CTRL1_ADDR             ((PAGE_PMCTRL) + (0x69))
#define    HISSC_PMU_CODEC_CLASSD_GAIN_BIT_START  (0)
#define    HISSC_PMU_CODEC_CLASSD_GAIN_BIT_END    (1)
#define    HISSC_PMU_CODEC_CLASSD_I_OCP_BIT_START (2)
#define    HISSC_PMU_CODEC_CLASSD_I_OCP_BIT_END   (3)
#define    HISSC_PMU_CODEC_CLASSD_MUTE_SEL_BIT    (4)
#define    HISSC_PMU_CODEC_CLASSD_MUTE_BIT        (5)
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

#endif /* end of __AUDIO_CODEC_INTERFACE_H__ */
