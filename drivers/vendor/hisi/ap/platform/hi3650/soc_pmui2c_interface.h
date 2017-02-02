/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_pmui2c_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:34
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_PMUI2C.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_PMUI2C_INTERFACE_H__
#define __SOC_PMUI2C_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_pmui2c
 ****************************************************************************/
/* �Ĵ���˵����I2C�豸�Ŀ��ƼĴ�����
            ��I2C�豸δʹ��ʱ��IC_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_CON_UNION */
#define SOC_PMUI2C_IC_CON_ADDR(base)                  ((base) + (0x000))

/* �Ĵ���˵����I2C�豸��Ŀ���ַ�Ĵ�����
            ��I2C�豸δʹ��ʱ��IC_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_TAR_UNION */
#define SOC_PMUI2C_IC_TAR_ADDR(base)                  ((base) + (0x004))

/* �Ĵ���˵����I2C����ģʽ�����ַ�Ĵ�����
            ��I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_HS_MADDR_UNION */
#define SOC_PMUI2C_IC_HS_MADDR_ADDR(base)             ((base) + (0x00C))

/* �Ĵ���˵����I2C�豸�����ݡ����ƼĴ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_DATA_CMD_UNION */
#define SOC_PMUI2C_IC_DATA_CMD_ADDR(base)             ((base) + (0x010))

/* �Ĵ���˵����I2C�豸�ķ�Ƶ��ֵ�Ĵ�����
            ����I2C�豸�����ڱ�׼�ٶ�ʱ�ߵ�ƽʱ���ɶ���ʱ��������ɡ���I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_SS_SCL_HCNT_UNION */
#define SOC_PMUI2C_IC_SS_SCL_HCNT_ADDR(base)          ((base) + (0x014))

/* �Ĵ���˵����I2C�豸�ķ�Ƶ��ֵ�Ĵ�����
            ����I2C�豸�����ڱ�׼�ٶ�ʱ�͵�ƽʱ���ɶ���ʱ��������ɡ���I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_SS_SCL_LCNT_UNION */
#define SOC_PMUI2C_IC_SS_SCL_LCNT_ADDR(base)          ((base) + (0x018))

/* �Ĵ���˵����I2C�豸�ķ�Ƶ��ֵ�Ĵ�����
            ����I2C�豸�����ڿ����ٶ�ʱ�ߵ�ƽʱ���ɶ���ʱ��������ɡ���I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_FS_SCL_HCNT_UNION */
#define SOC_PMUI2C_IC_FS_SCL_HCNT_ADDR(base)          ((base) + (0x01C))

/* �Ĵ���˵����I2C�豸�ķ�Ƶ��ֵ�Ĵ�����
            ����I2C�豸�����ڿ����ٶ�ʱ�͵�ƽʱ���ɶ���ʱ��������ɡ���I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_FS_SCL_LCNT_UNION */
#define SOC_PMUI2C_IC_FS_SCL_LCNT_ADDR(base)          ((base) + (0x020))

/* �Ĵ���˵����I2C�豸�ķ�Ƶ��ֵ�Ĵ�����
            ����I2C�豸�����ڸ����ٶ�ʱ�ߵ�ƽʱ���ɶ���ʱ��������ɡ���I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_HS_SCL_HCNT_UNION */
#define SOC_PMUI2C_IC_HS_SCL_HCNT_ADDR(base)          ((base) + (0x024))

/* �Ĵ���˵����I2C�豸�ķ�Ƶ��ֵ�Ĵ�����
            ����I2C�豸�����ڸ����ٶ�ʱ�͵�ƽʱ���ɶ���ʱ��������ɡ���I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_HS_SCL_LCNT_UNION */
#define SOC_PMUI2C_IC_HS_SCL_LCNT_ADDR(base)          ((base) + (0x028))

/* �Ĵ���˵�����ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_INTR_STAT_UNION */
#define SOC_PMUI2C_IC_INTR_STAT_ADDR(base)            ((base) + (0x02C))

/* �Ĵ���˵�����ж����μĴ�����
            ֵ��0����ʾ�����жϣ�ֵ��1����ʾ�����жϡ�
   λ����UNION�ṹ:  SOC_PMUI2C_IC_INTR_MASK_UNION */
#define SOC_PMUI2C_IC_INTR_MASK_ADDR(base)            ((base) + (0x030))

/* �Ĵ���˵����ԭʼ�ж�״̬�Ĵ�����
            ֵ��0����ʾδ�����жϣ�ֵ��1����ʾ�����жϡ�
   λ����UNION�ṹ:  SOC_PMUI2C_IC_RAW_INTR_STAT_UNION */
#define SOC_PMUI2C_IC_RAW_INTR_STAT_ADDR(base)        ((base) + (0x034))

/* �Ĵ���˵��������FIFO��ֵ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_RX_TL_UNION */
#define SOC_PMUI2C_IC_RX_TL_ADDR(base)                ((base) + (0x038))

/* �Ĵ���˵��������FIFO��ֵ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_TX_TL_UNION */
#define SOC_PMUI2C_IC_TX_TL_ADDR(base)                ((base) + (0x03C))

/* �Ĵ���˵������ϼ������ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_CLR_INTR_UNION */
#define SOC_PMUI2C_IC_CLR_INTR_ADDR(base)             ((base) + (0x040))

/* �Ĵ���˵����RX_UNDER�ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_CLR_RX_UNDER_UNION */
#define SOC_PMUI2C_IC_CLR_RX_UNDER_ADDR(base)         ((base) + (0x044))

/* �Ĵ���˵����RX_OVER�ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_CLR_RX_OVER_UNION */
#define SOC_PMUI2C_IC_CLR_RX_OVER_ADDR(base)          ((base) + (0x048))

/* �Ĵ���˵����TX_OVER�ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_CLR_TX_OVER_UNION */
#define SOC_PMUI2C_IC_CLR_TX_OVER_ADDR(base)          ((base) + (0x04C))

/* �Ĵ���˵����TX_ABRT�ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_CLR_TX_ABRT_UNION */
#define SOC_PMUI2C_IC_CLR_TX_ABRT_ADDR(base)          ((base) + (0x054))

/* �Ĵ���˵����ACTIVITY�ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_CLR_ACTIVITY_UNION */
#define SOC_PMUI2C_IC_CLR_ACTIVITY_ADDR(base)         ((base) + (0x5C))

/* �Ĵ���˵����STOP_DET�ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_CLR_STOP_DET_UNION */
#define SOC_PMUI2C_IC_CLR_STOP_DET_ADDR(base)         ((base) + (0x060))

/* �Ĵ���˵����START_DET�ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_CLR_SART_DET_UNION */
#define SOC_PMUI2C_IC_CLR_SART_DET_ADDR(base)         ((base) + (0x064))

/* �Ĵ���˵����GEN_CALL�ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_CLR_GEN_CALL_UNION */
#define SOC_PMUI2C_IC_CLR_GEN_CALL_ADDR(base)         ((base) + (0x068))

/* �Ĵ���˵����I2C�豸��ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_ENABLE_UNION */
#define SOC_PMUI2C_IC_ENABLE_ADDR(base)               ((base) + (0x06C))

/* �Ĵ���˵����I2C�豸��״̬�Ĵ�����
            ָʾ��ǰ����״̬��FIFO״̬��
   λ����UNION�ṹ:  SOC_PMUI2C_IC_STATUS_UNION */
#define SOC_PMUI2C_IC_STATUS_ADDR(base)               ((base) + (0x070))

/* �Ĵ���˵��������FIFO�е����ݸ����Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_TXFLR_UNION */
#define SOC_PMUI2C_IC_TXFLR_ADDR(base)                ((base) + (0x074))

/* �Ĵ���˵��������FIFO�е����ݸ����Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_RXFLR_UNION */
#define SOC_PMUI2C_IC_RXFLR_ADDR(base)                ((base) + (0x078))

/* �Ĵ���˵����I2C SDA HOLDʱ�䳤�ȼĴ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_SDA_HOLD_UNION */
#define SOC_PMUI2C_IC_SDA_HOLD_ADDR(base)             ((base) + (0x07C))

/* �Ĵ���˵����TX_ABRT�жϵ��ж�Դ�Ĵ�����
            bit[11]��bit[0]��ֵ��0����ʾ��λֵ��
   λ����UNION�ṹ:  SOC_PMUI2C_IC_TX_ABRT_SOURCE_UNION */
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_ADDR(base)       ((base) + (0x080))

/* �Ĵ���˵����DMA�ӿڿ��ƼĴ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_DMA_CR_UNION */
#define SOC_PMUI2C_IC_DMA_CR_ADDR(base)               ((base) + (0x088))

/* �Ĵ���˵��������FIFO����DMA����ʱ����ֵ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_DMA_TDLR_UNION */
#define SOC_PMUI2C_IC_DMA_TDLR_ADDR(base)             ((base) + (0x08C))

/* �Ĵ���˵��������FIFO����DMA����ʱ����ֵ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_DMA_RDLR_UNION */
#define SOC_PMUI2C_IC_DMA_RDLR_ADDR(base)             ((base) + (0x090))

/* �Ĵ���˵����I2C SDA SETUPʱ�䳤�ȼĴ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_SDA_SETUP_UNION */
#define SOC_PMUI2C_IC_SDA_SETUP_ADDR(base)            ((base) + (0x094))

/* �Ĵ���˵����I2C�ڽ���GENERAL CALLʱ��ӦACK��NACK�Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_IC_ACK_GENERAL_CALL_UNION */
#define SOC_PMUI2C_IC_ACK_GENERAL_CALL_ADDR(base)     ((base) + (0x098))

/* �Ĵ���˵����I2CӲ��״̬�Ĵ�������ӳi2c��IC_ENABLE[0]��1��0����ʱ��״̬����IC_ENABLE[0]Ϊ1ʱ��IC_ENABLE_STATUS[2:1]Ϊ0��IC_ENABLE_STATUS[0]Ϊ1��.
            IC_ENABLE[0]Ϊ0ʱ��IC_ENABLE_STATUS[2:1]��IC_ENABLE_STATUS[0]Ϊ0ʱ��Ч��
   λ����UNION�ṹ:  SOC_PMUI2C_IC_ENABLE_STATUS_UNION */
#define SOC_PMUI2C_IC_ENABLE_STATUS_ADDR(base)        ((base) + (0x09C))

/* �Ĵ���˵������Fast Speedģʽ�£��ɹ���ë�̳������üĴ�������I2C�豸δʹ��ʱ��IC_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_FS_SPKLEN_UNION */
#define SOC_PMUI2C_IC_FS_SPKLEN_ADDR(base)            ((base) + (0x00A0))

/* �Ĵ���˵������High Speedģʽ�£��ɹ���ë�̳������üĴ�������I2C�豸δʹ��ʱ��IC_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
   λ����UNION�ṹ:  SOC_PMUI2C_IC_HS_SPKLEN_UNION */
#define SOC_PMUI2C_IC_HS_SPKLEN_ADDR(base)            ((base) + (0x00A4))

/* �Ĵ���˵�������������Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_IC_COMP_PARAM_1_UNION */
#define SOC_PMUI2C_IC_COMP_PARAM_1_ADDR(base)         ((base) + (0x00F4))

/* �Ĵ���˵���������汾�Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_IC_COMP_VERSION_UNION */
#define SOC_PMUI2C_IC_COMP_VERSION_ADDR(base)         ((base) + (0x00F8))

/* �Ĵ���˵����������żĴ���
   λ����UNION�ṹ:  SOC_PMUI2C_IC_COMP_TYPE_UNION */
#define SOC_PMUI2C_IC_COMP_TYPE_ADDR(base)            ((base) + (0x00FC))

/* �Ĵ���˵����CPU�ĵ����ַ�Ĵ���.
   λ����UNION�ṹ:  SOC_PMUI2C_CPU_PHS_ADDR_UNION */
#define SOC_PMUI2C_CPU_PHS_ADDR_ADDR(base)            ((base) + (0x0100))

/* �Ĵ���˵����CPU�ĵ�ѹ��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_CPU_VOL_ADDR_UNION */
#define SOC_PMUI2C_CPU_VOL_ADDR_ADDR(base)            ((base) + (0x0104))

/* �Ĵ���˵����CPU��ѹ/��������
   λ����UNION�ṹ:  SOC_PMUI2C_CPU_IDX_UNION */
#define SOC_PMUI2C_CPU_IDX_ADDR(base)                 ((base) + (0x0108))

/* �Ĵ���˵����GPU�ĵ����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_GPU_PHS_ADDR_UNION */
#define SOC_PMUI2C_GPU_PHS_ADDR_ADDR(base)            ((base) + (0x010C))

/* �Ĵ���˵����GPU�ĵ�ѹ��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_GPU_VOL_ADDR_UNION */
#define SOC_PMUI2C_GPU_VOL_ADDR_ADDR(base)            ((base) + (0x0110))

/* �Ĵ���˵����GPU��ѹ/��������
   λ����UNION�ṹ:  SOC_PMUI2C_GPU_IDX_UNION */
#define SOC_PMUI2C_GPU_IDX_ADDR(base)                 ((base) + (0x0114))

/* �Ĵ���˵������ӦCPU����PMU�ĵ�ַ
   λ����UNION�ṹ:  SOC_PMUI2C_CPU_SLAVE_ADDR_UNION */
#define SOC_PMUI2C_CPU_SLAVE_ADDR_ADDR(base)          ((base) + (0x0118))

/* �Ĵ���˵������ӦGPU����PMU�ĵ�ַ
   λ����UNION�ṹ:  SOC_PMUI2C_GPU_SLAVE_ADDR_UNION */
#define SOC_PMUI2C_GPU_SLAVE_ADDR_ADDR(base)          ((base) + (0x011C))

/* �Ĵ���˵����STOP�źų�ʱ��������PMUѡ��Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_STOPTIMEOUT_UNION */
#define SOC_PMUI2C_STOPTIMEOUT_ADDR(base)             ((base) + (0x0120))

/* �Ĵ���˵����ԭʼ�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_INTER_STAT_UNION */
#define SOC_PMUI2C_INTER_STAT_ADDR(base)              ((base) + (0x0124))

/* �Ĵ���˵�����ж����μĴ���
   λ����UNION�ṹ:  SOC_PMUI2C_INTER_MASK_UNION */
#define SOC_PMUI2C_INTER_MASK_ADDR(base)              ((base) + (0x0128))

/* �Ĵ���˵�����ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_INTER_UNION */
#define SOC_PMUI2C_INTER_ADDR(base)                   ((base) + (0x012C))

/* �Ĵ���˵��������ж�1�Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_CLR_OVERTIME_UNION */
#define SOC_PMUI2C_CLR_OVERTIME_ADDR(base)            ((base) + (0x0130))

/* �Ĵ���˵��������ж�0�Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_CLR_IMPACT_UNION */
#define SOC_PMUI2C_CLR_IMPACT_ADDR(base)              ((base) + (0x0134))

/* �Ĵ���˵����DEBUG��־�Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_DEBUG_UNION */
#define SOC_PMUI2C_DEBUG_ADDR(base)                   ((base) + (0x0138))

/* �Ĵ���˵����PMUI2C״̬�Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_PMUI2CSTATE_UNION */
#define SOC_PMUI2C_PMUI2CSTATE_ADDR(base)             ((base) + (0x013C))

/* �Ĵ���˵����PMUI2C hold/idleģʽѡ��Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_HOLD_IDLE_UNION */
#define SOC_PMUI2C_HOLD_IDLE_ADDR(base)               ((base) + (0x0140))

/* �Ĵ���˵����PMUI2C ��/˫Slaveѡ��Ĵ���
   λ����UNION�ṹ:  SOC_PMUI2C_SLAVE_CHOSE_UNION */
#define SOC_PMUI2C_SLAVE_CHOSE_ADDR(base)             ((base) + (0x0144))





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
                     (1/1) register_pmui2c
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_CON_UNION
 �ṹ˵��  : IC_CON �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x007F�����:16
 �Ĵ���˵��: I2C�豸�Ŀ��ƼĴ�����
            ��I2C�豸δʹ��ʱ��IC_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_master_mode      : 1;  /* bit[0]   : ���豸����ʹ�ܡ������bitΪ1����bit 6 Ҳ��ҪΪ1��
                                                                0����ʹ�ܣ�
                                                                1��ʹ�ܡ� */
        unsigned short  ic_max_speed_mode   : 2;  /* bit[1-2] : I2C�豸�Ĳ����ٶȡ�
                                                                00���Ƿ���д��00������Ϊ������Ϊ����ģʽ��
                                                                01����׼�ٶȣ�
                                                                10�������ٶȣ�
                                                                11�������ٶȡ� */
        unsigned short  reserved_0          : 1;  /* bit[3]   : ������ */
        unsigned short  ic_10bitaddr_master : 1;  /* bit[4]   : ��Ϊ���豸ʱ�����ĵ�ַλ����
                                                                0��7λ��ַ��
                                                                1��10λ��ַ�� */
        unsigned short  ic_restart_en       : 1;  /* bit[5]   : �Ƿ��������豸���������¿�ʼ��������
                                                                0��������
                                                                1������ */
        unsigned short  ic_slave_disable    : 1;  /* bit[6]   : ��λֻ����Ϊ��1���� */
        unsigned short  reserved_1          : 9;  /* bit[7-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_CON_UNION;
#endif
#define SOC_PMUI2C_IC_CON_ic_master_mode_START       (0)
#define SOC_PMUI2C_IC_CON_ic_master_mode_END         (0)
#define SOC_PMUI2C_IC_CON_ic_max_speed_mode_START    (1)
#define SOC_PMUI2C_IC_CON_ic_max_speed_mode_END      (2)
#define SOC_PMUI2C_IC_CON_ic_10bitaddr_master_START  (4)
#define SOC_PMUI2C_IC_CON_ic_10bitaddr_master_END    (4)
#define SOC_PMUI2C_IC_CON_ic_restart_en_START        (5)
#define SOC_PMUI2C_IC_CON_ic_restart_en_END          (5)
#define SOC_PMUI2C_IC_CON_ic_slave_disable_START     (6)
#define SOC_PMUI2C_IC_CON_ic_slave_disable_END       (6)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_TAR_UNION
 �ṹ˵��  : IC_TAR �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x0055�����:16
 �Ĵ���˵��: I2C�豸��Ŀ���ַ�Ĵ�����
            ��I2C�豸δʹ��ʱ��IC_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  i2c_tar     : 10; /* bit[0-9]  : ��Ϊ���豸ʱҪ���ʵĴ��豸��ַ�� */
        unsigned short  gc_or_start : 1;  /* bit[10]   : ��[special]Ϊ1ʱִ�еĹ��ܡ�
                                                         0��General call��
                                                         1��Start byte�� */
        unsigned short  special     : 1;  /* bit[11]   : �Ƿ�ִ��general call��start byte���ܡ�
                                                         0����ִ�У�
                                                         1��ִ�С� */
        unsigned short  reserved    : 4;  /* bit[12-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_TAR_UNION;
#endif
#define SOC_PMUI2C_IC_TAR_i2c_tar_START      (0)
#define SOC_PMUI2C_IC_TAR_i2c_tar_END        (9)
#define SOC_PMUI2C_IC_TAR_gc_or_start_START  (10)
#define SOC_PMUI2C_IC_TAR_gc_or_start_END    (10)
#define SOC_PMUI2C_IC_TAR_special_START      (11)
#define SOC_PMUI2C_IC_TAR_special_END        (11)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_HS_MADDR_UNION
 �ṹ˵��  : IC_HS_MADDR �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x0001�����:16
 �Ĵ���˵��: I2C����ģʽ�����ַ�Ĵ�����
            ��I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  i2_hs_mar : 3;  /* bit[0-2] : i2c HS Mater Mode Code Address�� */
        unsigned short  reserved  : 13; /* bit[3-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_HS_MADDR_UNION;
#endif
#define SOC_PMUI2C_IC_HS_MADDR_i2_hs_mar_START  (0)
#define SOC_PMUI2C_IC_HS_MADDR_i2_hs_mar_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_DATA_CMD_UNION
 �ṹ˵��  : IC_DATA_CMD �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x0000�����:16
 �Ĵ���˵��: I2C�豸�����ݡ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  dat      : 8;  /* bit[0-7]  : ��Ҫ��I2C�����Ϸ���/���յ����ݡ�
                                                      ��ʱ������I2C�����Ͻ��յ����ݡ�
                                                      дʱ��д������ݷ��͵�I2C������ȥ�� */
        unsigned short  cmd      : 1;  /* bit[8]    : ��/д����λ��
                                                      0��д����ʾI2C�豸��Ҫ��I2C���߷������ݡ���ʱ��8bit��I2C�豸Ҫ��I2C���߷��͵����ݣ�
                                                      1��������ʾI2C�豸��Ҫ��I2C���߶������ݡ� */
        unsigned short  stop     : 1;  /* bit[9]    : ��bit������1 byte���ݱ����ͻ���պ��Ƿ����stop��
                                                      0���ڸ�byte֮�󲻷���stop��
                                                      1���ڸ�byte֮����stop�� */
        unsigned short  restart  : 1;  /* bit[10]   : ��bit������1 byte���ݱ����ͻ����ǰ�Ƿ���restart��
                                                      0�����ic_restart_enΪ1����ֻ����ǰ������Ĵ��䷽�����ı��ʱ��ŷ���restart�źţ�������ic_restart_enΪ0����start֮����stop��
                                                      1�����ic_restart_enΪ1��������ǰ������Ĵ��䷽���Ƿ����ı䣬�������ݱ����ͻ����֮����restart�źţ�������ic_restart_enΪ0������start֮����stop�� */
        unsigned short  reserved : 5;  /* bit[11-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_DATA_CMD_UNION;
#endif
#define SOC_PMUI2C_IC_DATA_CMD_dat_START       (0)
#define SOC_PMUI2C_IC_DATA_CMD_dat_END         (7)
#define SOC_PMUI2C_IC_DATA_CMD_cmd_START       (8)
#define SOC_PMUI2C_IC_DATA_CMD_cmd_END         (8)
#define SOC_PMUI2C_IC_DATA_CMD_stop_START      (9)
#define SOC_PMUI2C_IC_DATA_CMD_stop_END        (9)
#define SOC_PMUI2C_IC_DATA_CMD_restart_START   (10)
#define SOC_PMUI2C_IC_DATA_CMD_restart_END     (10)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_SS_SCL_HCNT_UNION
 �ṹ˵��  : IC_SS_SCL_HCNT �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x0190�����:16
 �Ĵ���˵��: I2C�豸�ķ�Ƶ��ֵ�Ĵ�����
            ����I2C�豸�����ڱ�׼�ٶ�ʱ�ߵ�ƽʱ���ɶ���ʱ��������ɡ���I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_ss_scl_hcnt : 16; /* bit[0-15]: ��׼�ٶ��µ�SCL�źŸߵ�ƽ��ʱ����������ic_clk���ڣ���
                                                           �˼Ĵ�������СֵΪ6��д��С��6��ֵʱ�ᱻ��Ϊ��6�� */
    } reg;
} SOC_PMUI2C_IC_SS_SCL_HCNT_UNION;
#endif
#define SOC_PMUI2C_IC_SS_SCL_HCNT_ic_ss_scl_hcnt_START  (0)
#define SOC_PMUI2C_IC_SS_SCL_HCNT_ic_ss_scl_hcnt_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_SS_SCL_LCNT_UNION
 �ṹ˵��  : IC_SS_SCL_LCNT �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x01D6�����:16
 �Ĵ���˵��: I2C�豸�ķ�Ƶ��ֵ�Ĵ�����
            ����I2C�豸�����ڱ�׼�ٶ�ʱ�͵�ƽʱ���ɶ���ʱ��������ɡ���I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_ss_scl_lcnt : 16; /* bit[0-15]: ��׼�ٶ��µ�SCL�źŵ͵�ƽ��ʱ����������ic_clk���ڣ���
                                                           �˼Ĵ�������СֵΪ8��д��С��8��ֵʱ�ᱻ��Ϊ��8�� */
    } reg;
} SOC_PMUI2C_IC_SS_SCL_LCNT_UNION;
#endif
#define SOC_PMUI2C_IC_SS_SCL_LCNT_ic_ss_scl_lcnt_START  (0)
#define SOC_PMUI2C_IC_SS_SCL_LCNT_ic_ss_scl_lcnt_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_FS_SCL_HCNT_UNION
 �ṹ˵��  : IC_FS_SCL_HCNT �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x003C�����:16
 �Ĵ���˵��: I2C�豸�ķ�Ƶ��ֵ�Ĵ�����
            ����I2C�豸�����ڿ����ٶ�ʱ�ߵ�ƽʱ���ɶ���ʱ��������ɡ���I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_fs_scl_hcnt : 16; /* bit[0-15]: �����ٶ��µ�SCL�źŸߵ�ƽ��ʱ����������ic_clk���ڣ���
                                                           �˼Ĵ�������СֵΪ6��д��С��6��ֵʱ�ᱻ��Ϊ��6�� */
    } reg;
} SOC_PMUI2C_IC_FS_SCL_HCNT_UNION;
#endif
#define SOC_PMUI2C_IC_FS_SCL_HCNT_ic_fs_scl_hcnt_START  (0)
#define SOC_PMUI2C_IC_FS_SCL_HCNT_ic_fs_scl_hcnt_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_FS_SCL_LCNT_UNION
 �ṹ˵��  : IC_FS_SCL_LCNT �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x0082�����:16
 �Ĵ���˵��: I2C�豸�ķ�Ƶ��ֵ�Ĵ�����
            ����I2C�豸�����ڿ����ٶ�ʱ�͵�ƽʱ���ɶ���ʱ��������ɡ���I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_fs_scl_lcnt : 16; /* bit[0-15]: �����ٶ��µ�SCL�źŵ͵�ƽ��ʱ����������ic_clk���ڣ���
                                                           �˼Ĵ�������СֵΪ8��д��С��8��ֵʱ�ᱻ��Ϊ��8�� */
    } reg;
} SOC_PMUI2C_IC_FS_SCL_LCNT_UNION;
#endif
#define SOC_PMUI2C_IC_FS_SCL_LCNT_ic_fs_scl_lcnt_START  (0)
#define SOC_PMUI2C_IC_FS_SCL_LCNT_ic_fs_scl_lcnt_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_HS_SCL_HCNT_UNION
 �ṹ˵��  : IC_HS_SCL_HCNT �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x0006�����:16
 �Ĵ���˵��: I2C�豸�ķ�Ƶ��ֵ�Ĵ�����
            ����I2C�豸�����ڸ����ٶ�ʱ�ߵ�ƽʱ���ɶ���ʱ��������ɡ���I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_hs_scl_hcnt : 16; /* bit[0-15]: �����ٶ��µ�SCL�źŸߵ�ƽ��ʱ����������ic_clk���ڣ���
                                                           �˼Ĵ�������СֵΪ6��д��С��6��ֵʱ�ᱻ��Ϊ��6�� */
    } reg;
} SOC_PMUI2C_IC_HS_SCL_HCNT_UNION;
#endif
#define SOC_PMUI2C_IC_HS_SCL_HCNT_ic_hs_scl_hcnt_START  (0)
#define SOC_PMUI2C_IC_HS_SCL_HCNT_ic_hs_scl_hcnt_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_HS_SCL_LCNT_UNION
 �ṹ˵��  : IC_HS_SCL_LCNT �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x0010�����:16
 �Ĵ���˵��: I2C�豸�ķ�Ƶ��ֵ�Ĵ�����
            ����I2C�豸�����ڸ����ٶ�ʱ�͵�ƽʱ���ɶ���ʱ��������ɡ���I2C�豸δʹ��ʱ��I2C_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_hs_scl_lcnt : 16; /* bit[0-15]: �����ٶ��µ�SCL�źŵ͵�ƽ��ʱ����������ic_clk���ڣ���
                                                           �˼Ĵ�������СֵΪ8��д��С��8��ֵʱ�ᱻ��Ϊ��8�� */
    } reg;
} SOC_PMUI2C_IC_HS_SCL_LCNT_UNION;
#endif
#define SOC_PMUI2C_IC_HS_SCL_LCNT_ic_hs_scl_lcnt_START  (0)
#define SOC_PMUI2C_IC_HS_SCL_LCNT_ic_hs_scl_lcnt_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_INTR_STAT_UNION
 �ṹ˵��  : IC_INTR_STAT �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x0000�����:16
 �Ĵ���˵��: �ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  r_rx_under  : 1;  /* bit[0]    : ��CPU���յ�RX_FIFOʱ����λ������Ϊ1��
                                                         0��CPU��RX_FIFOʱRX_FIFOδ�գ�
                                                         1��CPU��RX_FIFOʱRX_FIFO�ѿգ� */
        unsigned short  r_rx_over   : 1;  /* bit[1]    : ����FIFO�����־��
                                                         0��δ�����
                                                         1������� */
        unsigned short  r_rx_full   : 1;  /* bit[2]    : ����FIFO�������Ƿ񵽴�������ֵ��
                                                         0��С����ֵ��
                                                         1�����ڻ������ֵ�� */
        unsigned short  r_tx_over   : 1;  /* bit[3]    : ����FIFO�����־��
                                                         0��δ�����
                                                         1������� */
        unsigned short  r_tx_empty  : 1;  /* bit[4]    : ����FIFO�������Ƿ񵽴�������ֵ��
                                                         0��������ֵ��
                                                         1�����ڻ������ֵ�� */
        unsigned short  reserved_0  : 1;  /* bit[5]    : ������ */
        unsigned short  r_tx_abrt   : 1;  /* bit[6]    : TX_ABRT�жϡ�
                                                         �ж�Դ��μ��Ĵ���I2C_TX_ABRT_SOURCE�� */
        unsigned short  reserved_1  : 1;  /* bit[7]    : ������ */
        unsigned short  r_activity  : 1;  /* bit[8]    : I2C��activity״̬��
                                                         0�����У�
                                                         1��æ�� */
        unsigned short  r_stop_det  : 1;  /* bit[9]    : ��I2C�������Ƿ�����ֹͣ������
                                                         0��δ������
                                                         1���ѷ����� */
        unsigned short  r_start_det : 1;  /* bit[10]   : ��I2C�������Ƿ�����start��restart������
                                                         0��δ������
                                                         1���ѷ����� */
        unsigned short  r_gen_call  : 1;  /* bit[11]   : һ��GENERAL CALL���󱻽���״̬��
                                                         0��δ���գ�
                                                         1���ѽ��ա�
                                                         I2C�����յ������ݷ��ڽ��ն˻������С� */
        unsigned short  reserved_2  : 4;  /* bit[12-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_INTR_STAT_UNION;
#endif
#define SOC_PMUI2C_IC_INTR_STAT_r_rx_under_START   (0)
#define SOC_PMUI2C_IC_INTR_STAT_r_rx_under_END     (0)
#define SOC_PMUI2C_IC_INTR_STAT_r_rx_over_START    (1)
#define SOC_PMUI2C_IC_INTR_STAT_r_rx_over_END      (1)
#define SOC_PMUI2C_IC_INTR_STAT_r_rx_full_START    (2)
#define SOC_PMUI2C_IC_INTR_STAT_r_rx_full_END      (2)
#define SOC_PMUI2C_IC_INTR_STAT_r_tx_over_START    (3)
#define SOC_PMUI2C_IC_INTR_STAT_r_tx_over_END      (3)
#define SOC_PMUI2C_IC_INTR_STAT_r_tx_empty_START   (4)
#define SOC_PMUI2C_IC_INTR_STAT_r_tx_empty_END     (4)
#define SOC_PMUI2C_IC_INTR_STAT_r_tx_abrt_START    (6)
#define SOC_PMUI2C_IC_INTR_STAT_r_tx_abrt_END      (6)
#define SOC_PMUI2C_IC_INTR_STAT_r_activity_START   (8)
#define SOC_PMUI2C_IC_INTR_STAT_r_activity_END     (8)
#define SOC_PMUI2C_IC_INTR_STAT_r_stop_det_START   (9)
#define SOC_PMUI2C_IC_INTR_STAT_r_stop_det_END     (9)
#define SOC_PMUI2C_IC_INTR_STAT_r_start_det_START  (10)
#define SOC_PMUI2C_IC_INTR_STAT_r_start_det_END    (10)
#define SOC_PMUI2C_IC_INTR_STAT_r_gen_call_START   (11)
#define SOC_PMUI2C_IC_INTR_STAT_r_gen_call_END     (11)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_INTR_MASK_UNION
 �ṹ˵��  : IC_INTR_MASK �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x08FF�����:16
 �Ĵ���˵��: �ж����μĴ�����
            ֵ��0����ʾ�����жϣ�ֵ��1����ʾ�����жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  m_rx_under  : 1;  /* bit[0]    : rx_under�ж����� */
        unsigned short  m_rx_over   : 1;  /* bit[1]    : rx_over�ж����� */
        unsigned short  m_rx_full   : 1;  /* bit[2]    : rx_full�ж����� */
        unsigned short  m_tx_over   : 1;  /* bit[3]    : tx_over�ж����� */
        unsigned short  m_tx_empty  : 1;  /* bit[4]    : tx_empty�ж����� */
        unsigned short  reserved_0  : 1;  /* bit[5]    : ������ */
        unsigned short  m_tx_abrt   : 1;  /* bit[6]    : tx_abrt�ж����� */
        unsigned short  reserved_1  : 1;  /* bit[7]    : ������ */
        unsigned short  m_activity  : 1;  /* bit[8]    : activity�ж����� */
        unsigned short  m_stop_det  : 1;  /* bit[9]    : stop_det�ж����� */
        unsigned short  m_start_det : 1;  /* bit[10]   : start_det�ж����� */
        unsigned short  m_gen_call  : 1;  /* bit[11]   : gen_call�ж����� */
        unsigned short  reserved_2  : 4;  /* bit[12-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_INTR_MASK_UNION;
#endif
#define SOC_PMUI2C_IC_INTR_MASK_m_rx_under_START   (0)
#define SOC_PMUI2C_IC_INTR_MASK_m_rx_under_END     (0)
#define SOC_PMUI2C_IC_INTR_MASK_m_rx_over_START    (1)
#define SOC_PMUI2C_IC_INTR_MASK_m_rx_over_END      (1)
#define SOC_PMUI2C_IC_INTR_MASK_m_rx_full_START    (2)
#define SOC_PMUI2C_IC_INTR_MASK_m_rx_full_END      (2)
#define SOC_PMUI2C_IC_INTR_MASK_m_tx_over_START    (3)
#define SOC_PMUI2C_IC_INTR_MASK_m_tx_over_END      (3)
#define SOC_PMUI2C_IC_INTR_MASK_m_tx_empty_START   (4)
#define SOC_PMUI2C_IC_INTR_MASK_m_tx_empty_END     (4)
#define SOC_PMUI2C_IC_INTR_MASK_m_tx_abrt_START    (6)
#define SOC_PMUI2C_IC_INTR_MASK_m_tx_abrt_END      (6)
#define SOC_PMUI2C_IC_INTR_MASK_m_activity_START   (8)
#define SOC_PMUI2C_IC_INTR_MASK_m_activity_END     (8)
#define SOC_PMUI2C_IC_INTR_MASK_m_stop_det_START   (9)
#define SOC_PMUI2C_IC_INTR_MASK_m_stop_det_END     (9)
#define SOC_PMUI2C_IC_INTR_MASK_m_start_det_START  (10)
#define SOC_PMUI2C_IC_INTR_MASK_m_start_det_END    (10)
#define SOC_PMUI2C_IC_INTR_MASK_m_gen_call_START   (11)
#define SOC_PMUI2C_IC_INTR_MASK_m_gen_call_END     (11)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_RAW_INTR_STAT_UNION
 �ṹ˵��  : IC_RAW_INTR_STAT �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x0000�����:16
 �Ĵ���˵��: ԭʼ�ж�״̬�Ĵ�����
            ֵ��0����ʾδ�����жϣ�ֵ��1����ʾ�����жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  r_rx_under  : 1;  /* bit[0]    : rx_underԭʼ�ж�״̬ */
        unsigned short  r_rx_over   : 1;  /* bit[1]    : rx_overԭʼ�ж�״̬ */
        unsigned short  r_rx_full   : 1;  /* bit[2]    : rx_fullԭʼ�ж�״̬ */
        unsigned short  r_tx_over   : 1;  /* bit[3]    : tx_overԭʼ�ж�״̬ */
        unsigned short  r_tx_empty  : 1;  /* bit[4]    : tx_emptyԭʼ�ж�״̬ */
        unsigned short  reserved_0  : 1;  /* bit[5]    : ������ */
        unsigned short  r_tx_abrt   : 1;  /* bit[6]    : tx_abrtԭʼ�ж�״̬ */
        unsigned short  reserved_1  : 1;  /* bit[7]    : ������ */
        unsigned short  r_activity  : 1;  /* bit[8]    : activityԭʼ�ж�״̬ */
        unsigned short  r_stop_det  : 1;  /* bit[9]    : stop_detԭʼ�ж�״̬ */
        unsigned short  r_start_det : 1;  /* bit[10]   : start_detԭʼ�ж�״̬ */
        unsigned short  r_gen_call  : 1;  /* bit[11]   : gen_callԭʼ�ж�״̬ */
        unsigned short  reserved_2  : 4;  /* bit[12-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_RAW_INTR_STAT_UNION;
#endif
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_rx_under_START   (0)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_rx_under_END     (0)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_rx_over_START    (1)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_rx_over_END      (1)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_rx_full_START    (2)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_rx_full_END      (2)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_tx_over_START    (3)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_tx_over_END      (3)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_tx_empty_START   (4)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_tx_empty_END     (4)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_tx_abrt_START    (6)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_tx_abrt_END      (6)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_activity_START   (8)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_activity_END     (8)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_stop_det_START   (9)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_stop_det_END     (9)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_start_det_START  (10)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_start_det_END    (10)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_gen_call_START   (11)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_gen_call_END     (11)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_RX_TL_UNION
 �ṹ˵��  : IC_RX_TL �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x0003�����:16
 �Ĵ���˵��: ����FIFO��ֵ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rx_tl    : 8;  /* bit[0-7] : ����FIFO��ֵ��ʵ��ֵ��������ֵ��1��������ֵ����FIFO��ȣ�64��ʱʵ��ֵ����Ϊ��64�� */
        unsigned short  reserved : 8;  /* bit[8-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_RX_TL_UNION;
#endif
#define SOC_PMUI2C_IC_RX_TL_rx_tl_START     (0)
#define SOC_PMUI2C_IC_RX_TL_rx_tl_END       (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_TX_TL_UNION
 �ṹ˵��  : IC_TX_TL �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x0003�����:16
 �Ĵ���˵��: ����FIFO��ֵ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  tx_tl    : 8;  /* bit[0-7] : ����FIFO��ֵ��ʵ��ֵ��������ֵ��1��������ֵ����FIFO��ȣ�64��ʱʵ��ֵ����Ϊ��64�� */
        unsigned short  reserved : 8;  /* bit[8-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_TX_TL_UNION;
#endif
#define SOC_PMUI2C_IC_TX_TL_tx_tl_START     (0)
#define SOC_PMUI2C_IC_TX_TL_tx_tl_END       (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_CLR_INTR_UNION
 �ṹ˵��  : IC_CLR_INTR �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x0000�����:16
 �Ĵ���˵��: ��ϼ������ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_intr : 1;  /* bit[0]   : ���˼Ĵ���������������жϺͶ����жϣ��Լ��Ĵ���I2C_TX_ABRT_SOURCE��
                                                     ע�⣺�Ĵ���I2C_TX_ABRT_SOURCE bit[9]��������������ж��޷�������� */
        unsigned short  reserved : 15; /* bit[1-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_CLR_INTR_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_INTR_clr_intr_START  (0)
#define SOC_PMUI2C_IC_CLR_INTR_clr_intr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_CLR_RX_UNDER_UNION
 �ṹ˵��  : IC_CLR_RX_UNDER �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x0000�����:16
 �Ĵ���˵��: RX_UNDER�ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_intr : 1;  /* bit[0]   : ���˼Ĵ�������RX_UNDER�жϡ� */
        unsigned short  reserved : 15; /* bit[1-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_CLR_RX_UNDER_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_RX_UNDER_clr_intr_START  (0)
#define SOC_PMUI2C_IC_CLR_RX_UNDER_clr_intr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_CLR_RX_OVER_UNION
 �ṹ˵��  : IC_CLR_RX_OVER �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x0000�����:16
 �Ĵ���˵��: RX_OVER�ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_rx_under : 1;  /* bit[0]   : ���˼Ĵ�������RX_OVER�жϡ� */
        unsigned short  reserved     : 15; /* bit[1-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_CLR_RX_OVER_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_RX_OVER_clr_rx_under_START  (0)
#define SOC_PMUI2C_IC_CLR_RX_OVER_clr_rx_under_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_CLR_TX_OVER_UNION
 �ṹ˵��  : IC_CLR_TX_OVER �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x0000�����:16
 �Ĵ���˵��: TX_OVER�ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_tx_over : 1;  /* bit[0]   : ���˼Ĵ�������TX_OVER�жϡ� */
        unsigned short  reserved    : 15; /* bit[1-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_CLR_TX_OVER_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_TX_OVER_clr_tx_over_START  (0)
#define SOC_PMUI2C_IC_CLR_TX_OVER_clr_tx_over_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_CLR_TX_ABRT_UNION
 �ṹ˵��  : IC_CLR_TX_ABRT �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x0000�����:16
 �Ĵ���˵��: TX_ABRT�ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_tx_abrt : 1;  /* bit[0]   : ���˼Ĵ�������TX_ABRT�жϺͼĴ���IC_TX_ABRT_SOURCE�� */
        unsigned short  reserved    : 15; /* bit[1-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_CLR_TX_ABRT_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_TX_ABRT_clr_tx_abrt_START  (0)
#define SOC_PMUI2C_IC_CLR_TX_ABRT_clr_tx_abrt_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_CLR_ACTIVITY_UNION
 �ṹ˵��  : IC_CLR_ACTIVITY �Ĵ����ṹ���塣��ַƫ����:0x5C����ֵ:0x0000�����:16
 �Ĵ���˵��: ACTIVITY�ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_activity : 1;  /* bit[0]   : ���˼Ĵ����ɻ��ACTIVITY�ж�״̬��Ӳ���Զ����㡣 */
        unsigned short  reserved     : 15; /* bit[1-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_CLR_ACTIVITY_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_ACTIVITY_clr_activity_START  (0)
#define SOC_PMUI2C_IC_CLR_ACTIVITY_clr_activity_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_CLR_STOP_DET_UNION
 �ṹ˵��  : IC_CLR_STOP_DET �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x0000�����:16
 �Ĵ���˵��: STOP_DET�ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_stop_det : 1;  /* bit[0]   : ���˼Ĵ�������STOP_DET�жϡ� */
        unsigned short  reserved     : 15; /* bit[1-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_CLR_STOP_DET_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_STOP_DET_clr_stop_det_START  (0)
#define SOC_PMUI2C_IC_CLR_STOP_DET_clr_stop_det_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_CLR_SART_DET_UNION
 �ṹ˵��  : IC_CLR_SART_DET �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x0000�����:16
 �Ĵ���˵��: START_DET�ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_start_det : 1;  /* bit[0]   : ���˼Ĵ�������START_DET�жϡ� */
        unsigned short  reserved      : 15; /* bit[1-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_CLR_SART_DET_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_SART_DET_clr_start_det_START  (0)
#define SOC_PMUI2C_IC_CLR_SART_DET_clr_start_det_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_CLR_GEN_CALL_UNION
 �ṹ˵��  : IC_CLR_GEN_CALL �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x0000�����:16
 �Ĵ���˵��: GEN_CALL�ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_gen_call : 1;  /* bit[0]   : ���˼Ĵ�������GEN_CALL�жϡ� */
        unsigned short  reserved     : 15; /* bit[1-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_CLR_GEN_CALL_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_GEN_CALL_clr_gen_call_START  (0)
#define SOC_PMUI2C_IC_CLR_GEN_CALL_clr_gen_call_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_ENABLE_UNION
 �ṹ˵��  : IC_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x0000�����:16
 �Ĵ���˵��: I2C�豸��ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  enable   : 1;  /* bit[0]   : ʹ��I2C�豸��
                                                     0�����������������
                                                     l ���ڷ���״̬ʱ������ɵ�ǰ�ֽڷ��ͺ�ֹͣ��ͬʱɾ������FIFO�����ݡ�
                                                     l ���ڽ���״̬ʱ���ڽ����굱ǰ�ֽں���Ӧ��δ��䡣
                                                     1��ʹI2C�豸���빤��״̬��д��0����ɶ���������á� */
        unsigned short  abort    : 1;  /* bit[1]   : abort I2C�豸��
                                                     0��abortδ�������ѽ�����
                                                     1������abort�� */
        unsigned short  reserved : 14; /* bit[2-15]: ������ */
    } reg;
} SOC_PMUI2C_IC_ENABLE_UNION;
#endif
#define SOC_PMUI2C_IC_ENABLE_enable_START    (0)
#define SOC_PMUI2C_IC_ENABLE_enable_END      (0)
#define SOC_PMUI2C_IC_ENABLE_abort_START     (1)
#define SOC_PMUI2C_IC_ENABLE_abort_END       (1)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_STATUS_UNION
 �ṹ˵��  : IC_STATUS �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000006�����:32
 �Ĵ���˵��: I2C�豸��״̬�Ĵ�����
            ָʾ��ǰ����״̬��FIFO״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  activity     : 1;  /* bit[0]   : I2C�豸��״̬��
                                                       0�����У�
                                                       1��æ�� */
        unsigned int  tfnf         : 1;  /* bit[1]   : ����FIFO�Ƿ�û����
                                                       0��������
                                                       1��û���� */
        unsigned int  tfe          : 1;  /* bit[2]   : ����FIFO�Ƿ��ѿա�
                                                       0��û�գ�
                                                       1���ѿա� */
        unsigned int  rfne         : 1;  /* bit[3]   : ����FIFO�Ƿ�ǿա�
                                                       0���ѿգ�
                                                       1���ǿա� */
        unsigned int  rff          : 1;  /* bit[4]   : ����FIFO�Ƿ�������
                                                       0��û����
                                                       1�������� */
        unsigned int  mst_activity : 1;  /* bit[5]   : master FSM activity״̬��
                                                       0��idle��
                                                       1����idle״̬�� */
        unsigned int  slv_activity : 1;  /* bit[6]   : slave FSM activity״̬��
                                                       0��idle��
                                                       1����idle״̬�� */
        unsigned int  reserved     : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_PMUI2C_IC_STATUS_UNION;
#endif
#define SOC_PMUI2C_IC_STATUS_activity_START      (0)
#define SOC_PMUI2C_IC_STATUS_activity_END        (0)
#define SOC_PMUI2C_IC_STATUS_tfnf_START          (1)
#define SOC_PMUI2C_IC_STATUS_tfnf_END            (1)
#define SOC_PMUI2C_IC_STATUS_tfe_START           (2)
#define SOC_PMUI2C_IC_STATUS_tfe_END             (2)
#define SOC_PMUI2C_IC_STATUS_rfne_START          (3)
#define SOC_PMUI2C_IC_STATUS_rfne_END            (3)
#define SOC_PMUI2C_IC_STATUS_rff_START           (4)
#define SOC_PMUI2C_IC_STATUS_rff_END             (4)
#define SOC_PMUI2C_IC_STATUS_mst_activity_START  (5)
#define SOC_PMUI2C_IC_STATUS_mst_activity_END    (5)
#define SOC_PMUI2C_IC_STATUS_slv_activity_START  (6)
#define SOC_PMUI2C_IC_STATUS_slv_activity_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_TXFLR_UNION
 �ṹ˵��  : IC_TXFLR �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����FIFO�е����ݸ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  txflr    : 7;  /* bit[0-6] : ����FIFO�е����ݸ����� */
        unsigned int  reserved : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_PMUI2C_IC_TXFLR_UNION;
#endif
#define SOC_PMUI2C_IC_TXFLR_txflr_START     (0)
#define SOC_PMUI2C_IC_TXFLR_txflr_END       (6)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_RXFLR_UNION
 �ṹ˵��  : IC_RXFLR �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����FIFO�е����ݸ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rxflr    : 7;  /* bit[0-6] : ����FIFO�е����ݸ����� */
        unsigned int  reserved : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_PMUI2C_IC_RXFLR_UNION;
#endif
#define SOC_PMUI2C_IC_RXFLR_rxflr_START     (0)
#define SOC_PMUI2C_IC_RXFLR_rxflr_END       (6)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_SDA_HOLD_UNION
 �ṹ˵��  : IC_SDA_HOLD �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000001�����:32
 �Ĵ���˵��: I2C SDA HOLDʱ�䳤�ȼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ic_sda_hold : 16; /* bit[0-15] : ����SDA hold ʱ�䣬��ic_clk����Ϊ��λ�� */
        unsigned int  reserved    : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_PMUI2C_IC_SDA_HOLD_UNION;
#endif
#define SOC_PMUI2C_IC_SDA_HOLD_ic_sda_hold_START  (0)
#define SOC_PMUI2C_IC_SDA_HOLD_ic_sda_hold_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_TX_ABRT_SOURCE_UNION
 �ṹ˵��  : IC_TX_ABRT_SOURCE �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00000000�����:32
 �Ĵ���˵��: TX_ABRT�жϵ��ж�Դ�Ĵ�����
            bit[11]��bit[0]��ֵ��0����ʾ��λֵ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  abrt_7b_addr_noack   : 1;  /* bit[0]    : 1����Ϊ���豸ʱ���͵�7λ��ַû����Ӧ�� */
        unsigned int  abrt_10addr1_noack   : 1;  /* bit[1]    : 1����Ϊ���豸ʱ���͵�10λ��ַ�ĵ�1�ֽ�û����Ӧ�� */
        unsigned int  abrt_10addr2_noack   : 1;  /* bit[2]    : 1����Ϊ���豸ʱ���͵�10λ��ַ�ĵ�1�ֽ�û����Ӧ�� */
        unsigned int  abrt_txdata_nocack   : 1;  /* bit[3]    : 1����Ϊ���豸ʱ���͵ĵ�ַ�����豸��Ӧ�������͵�����û����Ӧ�� */
        unsigned int  abrt_gcall_noack     : 1;  /* bit[4]    : 1����Ϊ���豸ʱ����general call����û����Ӧ�� */
        unsigned int  abrt_gcall_read      : 1;  /* bit[5]    : 1����Ϊ���豸ʱ����general call����CPU��I2C��������� */
        unsigned int  abrt_hs_ack_det      : 1;  /* bit[6]    : 1����Ϊ���豸���и��ٴ���ʱ�����������뱻��Ӧ�� */
        unsigned int  abrt_sbyte_ackdet    : 1;  /* bit[7]    : 1����Ϊ���豸ʱ����start byte������Ӧ�� */
        unsigned int  abrt_hs_norstrt      : 1;  /* bit[8]    : 1����Ϊ���豸��֧��restart����ʱ�����и��ٲ����� */
        unsigned int  abrt_sbyte_norstrt   : 1;  /* bit[9]    : 1����Ϊ���豸��֧��restart����ʱ������start byte�� */
        unsigned int  abrt_10b_rd_norestrt : 1;  /* bit[10]   : 1����Ϊ���豸��֧��restart����ʱ����10λ��ַ�Ĵ��豸�����˶���� */
        unsigned int  abrt_master_dis      : 1;  /* bit[11]   : 1��Master���ܽ���ʱ������Master������ */
        unsigned int  arb_lost             : 1;  /* bit[12]   : 1��Masterʧȥ�����ٲã���������I2C_TX_ABRT_SOURCE[14]����Ϊ1�� */
        unsigned int  abrt_slvflush_txfifo : 1;  /* bit[13]   : 1:Slave���յ�������ʱTX_FIFO�������ݣ���ʱSlave����һ��TX_ABRT�ж�ȥflush TX_FIFO�еľ����ݡ� */
        unsigned int  abrt_slv_arblost     : 1;  /* bit[14]   : 1:Slave�ڷ������ݸ�Զ��Masterʱʧȥ�����ٲã���ʱI2C_TX_ABRT_SOURCE[12]ͬʱ����Ϊ1�� */
        unsigned int  abrt_slvrd_intx      : 1;  /* bit[15]   : 1��Slave�ڷ������ݸ�Զ��Masterʱ��IC_DATA_CMD�Ĵ���bit8д��1�� */
        unsigned int  abrt_user_abrt       : 1;  /* bit[16]   : 1:master transmitter��⵽����abort�� */
        unsigned int  reserved             : 7;  /* bit[17-23]: ������ */
        unsigned int  tx_flush_cnt         : 8;  /* bit[24-31]: ��ֵ����txflr��ֵ����������tx_abrt�¼�����I2C disabled��ʱ���ֵ������� */
    } reg;
} SOC_PMUI2C_IC_TX_ABRT_SOURCE_UNION;
#endif
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_7b_addr_noack_START    (0)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_7b_addr_noack_END      (0)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_10addr1_noack_START    (1)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_10addr1_noack_END      (1)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_10addr2_noack_START    (2)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_10addr2_noack_END      (2)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_txdata_nocack_START    (3)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_txdata_nocack_END      (3)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_gcall_noack_START      (4)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_gcall_noack_END        (4)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_gcall_read_START       (5)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_gcall_read_END         (5)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_hs_ack_det_START       (6)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_hs_ack_det_END         (6)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_sbyte_ackdet_START     (7)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_sbyte_ackdet_END       (7)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_hs_norstrt_START       (8)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_hs_norstrt_END         (8)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_sbyte_norstrt_START    (9)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_sbyte_norstrt_END      (9)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_10b_rd_norestrt_START  (10)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_10b_rd_norestrt_END    (10)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_master_dis_START       (11)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_master_dis_END         (11)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_arb_lost_START              (12)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_arb_lost_END                (12)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_slvflush_txfifo_START  (13)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_slvflush_txfifo_END    (13)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_slv_arblost_START      (14)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_slv_arblost_END        (14)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_slvrd_intx_START       (15)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_slvrd_intx_END         (15)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_user_abrt_START        (16)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_user_abrt_END          (16)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_tx_flush_cnt_START          (24)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_tx_flush_cnt_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_DMA_CR_UNION
 �ṹ˵��  : IC_DMA_CR �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA�ӿڿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdmae    : 1;  /* bit[0]   : �Ƿ�򿪽���FIFO��DMAͨ����
                                                   0�����򿪣�
                                                   1���򿪡� */
        unsigned int  tdmae    : 1;  /* bit[1]   : �Ƿ�򿪷���FIFO��DMAͨ����
                                                   0�����򿪣�
                                                   1���򿪡� */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMUI2C_IC_DMA_CR_UNION;
#endif
#define SOC_PMUI2C_IC_DMA_CR_rdmae_START     (0)
#define SOC_PMUI2C_IC_DMA_CR_rdmae_END       (0)
#define SOC_PMUI2C_IC_DMA_CR_tdmae_START     (1)
#define SOC_PMUI2C_IC_DMA_CR_tdmae_END       (1)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_DMA_TDLR_UNION
 �ṹ˵��  : IC_DMA_TDLR �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����FIFO����DMA����ʱ����ֵ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmatdl   : 6;  /* bit[0-5] : ����FIFO DMA����ʱ����ֵ�� */
        unsigned int  reserved : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMUI2C_IC_DMA_TDLR_UNION;
#endif
#define SOC_PMUI2C_IC_DMA_TDLR_dmatdl_START    (0)
#define SOC_PMUI2C_IC_DMA_TDLR_dmatdl_END      (5)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_DMA_RDLR_UNION
 �ṹ˵��  : IC_DMA_RDLR �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����FIFO����DMA����ʱ����ֵ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmardl   : 6;  /* bit[0-5] : ����FIFO DMA����ʱ����ֵ��ʵ��ֵ��������ֵ+1�� */
        unsigned int  reserved : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMUI2C_IC_DMA_RDLR_UNION;
#endif
#define SOC_PMUI2C_IC_DMA_RDLR_dmardl_START    (0)
#define SOC_PMUI2C_IC_DMA_RDLR_dmardl_END      (5)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_SDA_SETUP_UNION
 �ṹ˵��  : IC_SDA_SETUP �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x00000064�����:32
 �Ĵ���˵��: I2C SDA SETUPʱ�䳤�ȼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ic_sda_setup : 8;  /* bit[0-7] : ����SDA setup ʱ�䣬��ic_clk����Ϊ��λ�� */
        unsigned int  reserved     : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_PMUI2C_IC_SDA_SETUP_UNION;
#endif
#define SOC_PMUI2C_IC_SDA_SETUP_ic_sda_setup_START  (0)
#define SOC_PMUI2C_IC_SDA_SETUP_ic_sda_setup_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_ACK_GENERAL_CALL_UNION
 �ṹ˵��  : IC_ACK_GENERAL_CALL �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x00000001�����:32
 �Ĵ���˵��: I2C�ڽ���GENERAL CALLʱ��ӦACK��NACK�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ack_gen_call : 1;  /* bit[0]   : i2c�ڽ���GENERAL CALLʱ�Ƿ���ӦACK��NACK�Ĵ���
                                                       1����Ӧ
                                                       0������Ӧ���Ҳ�����General Call�ж� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMUI2C_IC_ACK_GENERAL_CALL_UNION;
#endif
#define SOC_PMUI2C_IC_ACK_GENERAL_CALL_ack_gen_call_START  (0)
#define SOC_PMUI2C_IC_ACK_GENERAL_CALL_ack_gen_call_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_ENABLE_STATUS_UNION
 �ṹ˵��  : IC_ENABLE_STATUS �Ĵ����ṹ���塣��ַƫ����:0x09C����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2CӲ��״̬�Ĵ�������ӳi2c��IC_ENABLE[0]��1��0����ʱ��״̬����IC_ENABLE[0]Ϊ1ʱ��IC_ENABLE_STATUS[2:1]Ϊ0��IC_ENABLE_STATUS[0]Ϊ1��.
            IC_ENABLE[0]Ϊ0ʱ��IC_ENABLE_STATUS[2:1]��IC_ENABLE_STATUS[0]Ϊ0ʱ��Ч��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ic_en                   : 1;  /* bit[0]   : 1��i2c��enable״̬��
                                                                  0��i2c��inactive״̬�� */
        unsigned int  slv_disabled_while_busy : 1;  /* bit[1]   : 1����IC_ENABLE[0]��1��0����ʱ��I2C��ΪMaster���ݻ��ڴ����ַ�Ĺ����С�
                                                                  0����IC_ENABLE[0]��1��0����ʱ��I2C��ΪMaster����û���ڴ������� */
        unsigned int  slv_rx_data_lost        : 1;  /* bit[2]   : 1����IC_ENABLE[0]��1��0����ʱ��I2C��ΪMaster������Ȼ�ڴ��䣨�Ѿ����䵽�˵�ַ����������NACK����
                                                                  0����IC_ENABLE[0]��1��0����ʱ��I2C��ΪMaster����û���ڴ������� */
        unsigned int  reserved                : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_PMUI2C_IC_ENABLE_STATUS_UNION;
#endif
#define SOC_PMUI2C_IC_ENABLE_STATUS_ic_en_START                    (0)
#define SOC_PMUI2C_IC_ENABLE_STATUS_ic_en_END                      (0)
#define SOC_PMUI2C_IC_ENABLE_STATUS_slv_disabled_while_busy_START  (1)
#define SOC_PMUI2C_IC_ENABLE_STATUS_slv_disabled_while_busy_END    (1)
#define SOC_PMUI2C_IC_ENABLE_STATUS_slv_rx_data_lost_START         (2)
#define SOC_PMUI2C_IC_ENABLE_STATUS_slv_rx_data_lost_END           (2)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_FS_SPKLEN_UNION
 �ṹ˵��  : IC_FS_SPKLEN �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00000005�����:32
 �Ĵ���˵��: ��Fast Speedģʽ�£��ɹ���ë�̳������üĴ�������I2C�豸δʹ��ʱ��IC_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ic_fs_spklen : 8;  /* bit[0-7] : ��ic_clk��cycleΪ׼��Fast Speedģʽ������SCL��SDA�пɱ�����ë�̵�����ȣ���СֵΪ1����С��1����1���� */
        unsigned int  reserved     : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_PMUI2C_IC_FS_SPKLEN_UNION;
#endif
#define SOC_PMUI2C_IC_FS_SPKLEN_ic_fs_spklen_START  (0)
#define SOC_PMUI2C_IC_FS_SPKLEN_ic_fs_spklen_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_HS_SPKLEN_UNION
 �ṹ˵��  : IC_HS_SPKLEN �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00000101�����:32
 �Ĵ���˵��: ��High Speedģʽ�£��ɹ���ë�̳������üĴ�������I2C�豸δʹ��ʱ��IC_ENABLE bit[0]Ϊ0�����ſ����ô˼Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ic_hs_spklen : 8;  /* bit[0-7] : ��ic_clk��cycleΪ׼��High Speedģʽ������SCL��SDA�пɱ�����ë�̵�����ȣ���СֵΪ1����С��1����1���� */
        unsigned int  reserved     : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_PMUI2C_IC_HS_SPKLEN_UNION;
#endif
#define SOC_PMUI2C_IC_HS_SPKLEN_ic_hs_spklen_START  (0)
#define SOC_PMUI2C_IC_HS_SPKLEN_ic_hs_spklen_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_COMP_PARAM_1_UNION
 �ṹ˵��  : IC_COMP_PARAM_1 �Ĵ����ṹ���塣��ַƫ����:0x00F4����ֵ:0x003F3FEE�����:32
 �Ĵ���˵��: ���������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apb_data_width     : 2;  /* bit[0-1]  : APB�����ݿ������
                                                              ��ѡ0x00=8,
                                                              0x01=16,
                                                              0x02=32,
                                                              0x03=reserved */
        unsigned int  max_speed_mode     : 2;  /* bit[2-3]  : ����I2C���ٶ�ģʽ
                                                              0x00��reserved
                                                              0x01��Standard
                                                              0x02��Fast
                                                              0x03��High */
        unsigned int  hc_count_values    : 1;  /* bit[4]    : ���е�*CNT�Ĵ����Ƿ�ɶ�д
                                                              1��ֻ��
                                                              0���ɶ�д */
        unsigned int  intr_io            : 1;  /* bit[5]    : ÿ���ж��Ƿ��ж��������
                                                              1�������ж�Դ����һ�����
                                                              0��ÿ���ж�Դ�и��Զ�������� */
        unsigned int  has_dma            : 1;  /* bit[6]    : �Ƿ��ڶ������DMA���ֽӿ��ź�
                                                              1�����
                                                              0������� */
        unsigned int  add_encoded_params : 1;  /* bit[7]    : �Ƿ�ͨ��������encoded����
                                                              1�����
                                                              0������� */
        unsigned int  rx_buffer_depth    : 8;  /* bit[8-15] : ����RX_BUFFER����� */
        unsigned int  tx_buffer_depth    : 8;  /* bit[16-23]: ����TX_BUFFER����� */
        unsigned int  reserved           : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_PMUI2C_IC_COMP_PARAM_1_UNION;
#endif
#define SOC_PMUI2C_IC_COMP_PARAM_1_apb_data_width_START      (0)
#define SOC_PMUI2C_IC_COMP_PARAM_1_apb_data_width_END        (1)
#define SOC_PMUI2C_IC_COMP_PARAM_1_max_speed_mode_START      (2)
#define SOC_PMUI2C_IC_COMP_PARAM_1_max_speed_mode_END        (3)
#define SOC_PMUI2C_IC_COMP_PARAM_1_hc_count_values_START     (4)
#define SOC_PMUI2C_IC_COMP_PARAM_1_hc_count_values_END       (4)
#define SOC_PMUI2C_IC_COMP_PARAM_1_intr_io_START             (5)
#define SOC_PMUI2C_IC_COMP_PARAM_1_intr_io_END               (5)
#define SOC_PMUI2C_IC_COMP_PARAM_1_has_dma_START             (6)
#define SOC_PMUI2C_IC_COMP_PARAM_1_has_dma_END               (6)
#define SOC_PMUI2C_IC_COMP_PARAM_1_add_encoded_params_START  (7)
#define SOC_PMUI2C_IC_COMP_PARAM_1_add_encoded_params_END    (7)
#define SOC_PMUI2C_IC_COMP_PARAM_1_rx_buffer_depth_START     (8)
#define SOC_PMUI2C_IC_COMP_PARAM_1_rx_buffer_depth_END       (15)
#define SOC_PMUI2C_IC_COMP_PARAM_1_tx_buffer_depth_START     (16)
#define SOC_PMUI2C_IC_COMP_PARAM_1_tx_buffer_depth_END       (23)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_COMP_VERSION_UNION
 �ṹ˵��  : IC_COMP_VERSION �Ĵ����ṹ���塣��ַƫ����:0x00F8����ֵ:0x3132302A�����:32
 �Ĵ���˵��: �����汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ����I2C�����İ汾��Ϣ */
    } reg;
} SOC_PMUI2C_IC_COMP_VERSION_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_IC_COMP_TYPE_UNION
 �ṹ˵��  : IC_COMP_TYPE �Ĵ����ṹ���塣��ַƫ����:0x00FC����ֵ:0x44570140�����:32
 �Ĵ���˵��: ������żĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ����I2CԪ����TYPE NUMBER */
    } reg;
} SOC_PMUI2C_IC_COMP_TYPE_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_CPU_PHS_ADDR_UNION
 �ṹ˵��  : CPU_PHS_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0xD2�����:8
 �Ĵ���˵��: CPU�ĵ����ַ�Ĵ���.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cpu_phs_addr : 8;  /* bit[0-7]: PMU����Ĵ�����ַ����ӦCPU�� */
    } reg;
} SOC_PMUI2C_CPU_PHS_ADDR_UNION;
#endif
#define SOC_PMUI2C_CPU_PHS_ADDR_cpu_phs_addr_START  (0)
#define SOC_PMUI2C_CPU_PHS_ADDR_cpu_phs_addr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_CPU_VOL_ADDR_UNION
 �ṹ˵��  : CPU_VOL_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0xD8�����:8
 �Ĵ���˵��: CPU�ĵ�ѹ��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cpu_vol_addr : 8;  /* bit[0-7]: PMU��ѹ�Ĵ�����ַ����ӦCPU�� */
    } reg;
} SOC_PMUI2C_CPU_VOL_ADDR_UNION;
#endif
#define SOC_PMUI2C_CPU_VOL_ADDR_cpu_vol_addr_START  (0)
#define SOC_PMUI2C_CPU_VOL_ADDR_cpu_vol_addr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_CPU_IDX_UNION
 �ṹ˵��  : CPU_IDX �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00�����:8
 �Ĵ���˵��: CPU��ѹ/��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cpu_idx : 8;  /* bit[0-7]: CPU��ѹ����Ĵ������� */
    } reg;
} SOC_PMUI2C_CPU_IDX_UNION;
#endif
#define SOC_PMUI2C_CPU_IDX_cpu_idx_START  (0)
#define SOC_PMUI2C_CPU_IDX_cpu_idx_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_GPU_PHS_ADDR_UNION
 �ṹ˵��  : GPU_PHS_ADDR �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0xD2�����:8
 �Ĵ���˵��: GPU�ĵ����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  gpu_phs_addr : 8;  /* bit[0-7]: PMU����Ĵ�����ַ����ӦGPU�� */
    } reg;
} SOC_PMUI2C_GPU_PHS_ADDR_UNION;
#endif
#define SOC_PMUI2C_GPU_PHS_ADDR_gpu_phs_addr_START  (0)
#define SOC_PMUI2C_GPU_PHS_ADDR_gpu_phs_addr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_GPU_VOL_ADDR_UNION
 �ṹ˵��  : GPU_VOL_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0xD8�����:8
 �Ĵ���˵��: GPU�ĵ�ѹ��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  gpu_vol_addr : 8;  /* bit[0-7]: PMU��ѹ�Ĵ�����ַ����ӦGPU�� */
    } reg;
} SOC_PMUI2C_GPU_VOL_ADDR_UNION;
#endif
#define SOC_PMUI2C_GPU_VOL_ADDR_gpu_vol_addr_START  (0)
#define SOC_PMUI2C_GPU_VOL_ADDR_gpu_vol_addr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_GPU_IDX_UNION
 �ṹ˵��  : GPU_IDX �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x00�����:8
 �Ĵ���˵��: GPU��ѹ/��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  gpu_idx : 8;  /* bit[0-7]: GPU��ѹ����Ĵ������� */
    } reg;
} SOC_PMUI2C_GPU_IDX_UNION;
#endif
#define SOC_PMUI2C_GPU_IDX_gpu_idx_START  (0)
#define SOC_PMUI2C_GPU_IDX_gpu_idx_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_CPU_SLAVE_ADDR_UNION
 �ṹ˵��  : CPU_SLAVE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x68�����:8
 �Ĵ���˵��: ��ӦCPU����PMU�ĵ�ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cpu_slave_addr : 8;  /* bit[0-7]: PMU�ĵ�ַ����ӦCPU�� */
    } reg;
} SOC_PMUI2C_CPU_SLAVE_ADDR_UNION;
#endif
#define SOC_PMUI2C_CPU_SLAVE_ADDR_cpu_slave_addr_START  (0)
#define SOC_PMUI2C_CPU_SLAVE_ADDR_cpu_slave_addr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_GPU_SLAVE_ADDR_UNION
 �ṹ˵��  : GPU_SLAVE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x011C����ֵ:0x58�����:8
 �Ĵ���˵��: ��ӦGPU����PMU�ĵ�ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  gpu_slave_addr : 8;  /* bit[0-7]: PMU�ĵ�ַ����ӦGPU�� */
    } reg;
} SOC_PMUI2C_GPU_SLAVE_ADDR_UNION;
#endif
#define SOC_PMUI2C_GPU_SLAVE_ADDR_gpu_slave_addr_START  (0)
#define SOC_PMUI2C_GPU_SLAVE_ADDR_gpu_slave_addr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_STOPTIMEOUT_UNION
 �ṹ˵��  : STOPTIMEOUT �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: STOP�źų�ʱ��������PMUѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stop_time_out : 32; /* bit[0-31]: PMUI2C��ʱ���� */
    } reg;
} SOC_PMUI2C_STOPTIMEOUT_UNION;
#endif
#define SOC_PMUI2C_STOPTIMEOUT_stop_time_out_START  (0)
#define SOC_PMUI2C_STOPTIMEOUT_stop_time_out_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_INTER_STAT_UNION
 �ṹ˵��  : INTER_STAT �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x0�����:32
 �Ĵ���˵��: ԭʼ�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmui2c_impact_inter_state  : 1;  /* bit[0]   : APBģʽ����AVS�����ԭʼ�ж� */
        unsigned int  pmui2c_overtime_inter_stat : 1;  /* bit[1-1] : AVSģʽ��Stop��ʱԭʼ�ж� */
        unsigned int  reserved                   : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_PMUI2C_INTER_STAT_UNION;
#endif
#define SOC_PMUI2C_INTER_STAT_pmui2c_impact_inter_state_START   (0)
#define SOC_PMUI2C_INTER_STAT_pmui2c_impact_inter_state_END     (0)
#define SOC_PMUI2C_INTER_STAT_pmui2c_overtime_inter_stat_START  (1)
#define SOC_PMUI2C_INTER_STAT_pmui2c_overtime_inter_stat_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_INTER_MASK_UNION
 �ṹ˵��  : INTER_MASK �Ĵ����ṹ���塣��ַƫ����:0x0128����ֵ:0x3�����:32
 �Ĵ���˵��: �ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmui2c_impact_inter_mask   : 1;  /* bit[0]   : APBģʽ����AVS������ж����Σ�0�������Σ�1���������Ρ� */
        unsigned int  pmui2c_overtime_inter_mask : 1;  /* bit[1-1] : AVSģʽ��Stop��ʱ�ж����Σ�0�������Σ�1���������Ρ� */
        unsigned int  reserved                   : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_PMUI2C_INTER_MASK_UNION;
#endif
#define SOC_PMUI2C_INTER_MASK_pmui2c_impact_inter_mask_START    (0)
#define SOC_PMUI2C_INTER_MASK_pmui2c_impact_inter_mask_END      (0)
#define SOC_PMUI2C_INTER_MASK_pmui2c_overtime_inter_mask_START  (1)
#define SOC_PMUI2C_INTER_MASK_pmui2c_overtime_inter_mask_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_INTER_UNION
 �ṹ˵��  : INTER �Ĵ����ṹ���塣��ַƫ����:0x012C����ֵ:0x0�����:32
 �Ĵ���˵��: �ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmui2c_impact_inter   : 1;  /* bit[0]   : APBģʽ����AVS������жϣ������Σ� */
        unsigned int  pmui2c_overtime_inter : 1;  /* bit[1-1] : AVSģʽ��Stop��ʱ�жϣ������Σ� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_PMUI2C_INTER_UNION;
#endif
#define SOC_PMUI2C_INTER_pmui2c_impact_inter_START    (0)
#define SOC_PMUI2C_INTER_pmui2c_impact_inter_END      (0)
#define SOC_PMUI2C_INTER_pmui2c_overtime_inter_START  (1)
#define SOC_PMUI2C_INTER_pmui2c_overtime_inter_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_CLR_OVERTIME_UNION
 �ṹ˵��  : CLR_OVERTIME �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x0�����:32
 �Ĵ���˵��: ����ж�1�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0-0] : ����AVSģʽ��Stop��ʱԭʼ�ж� */
        unsigned int  reserved_1: 31; /* bit[1-31]: ���� */
    } reg;
} SOC_PMUI2C_CLR_OVERTIME_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_CLR_IMPACT_UNION
 �ṹ˵��  : CLR_IMPACT �Ĵ����ṹ���塣��ַƫ����:0x0134����ֵ:0x0�����:32
 �Ĵ���˵��: ����ж�0�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0-0] : ����APBģʽ����AVS������ж� */
        unsigned int  reserved_1: 31; /* bit[1-31]: ���� */
    } reg;
} SOC_PMUI2C_CLR_IMPACT_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_DEBUG_UNION
 �ṹ˵��  : DEBUG �Ĵ����ṹ���塣��ַƫ����:0x0138����ֵ:0x00000�����:32
 �Ĵ���˵��: DEBUG��־�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmui2c_debug_err     : 1;  /* bit[0]    : PMUI2C��AVS���ڴ���Ĺ������Ƿ���APB������ */
        unsigned int  i2c_debug_slv_cstate : 3;  /* bit[1-3]  : ��ӦI2C�ڲ���debug�ź� */
        unsigned int  i2c_debug_mst_cstate : 5;  /* bit[4-8]  : ��ӦI2C�ڲ���debug�ź� */
        unsigned int  i2c_debug_slave_act  : 1;  /* bit[9]    : ��ӦI2C�ڲ���debug�ź� */
        unsigned int  i2c_debug_master_act : 1;  /* bit[10]   : ��ӦI2C�ڲ���debug�ź� */
        unsigned int  i2c_debug_hs         : 1;  /* bit[11]   : ��ӦI2C�ڲ���debug�ź� */
        unsigned int  i2c_debug_wr         : 1;  /* bit[12]   : ��ӦI2C�ڲ���debug�ź� */
        unsigned int  i2c_debug_rd         : 1;  /* bit[13]   : ��ӦI2C�ڲ���debug�ź� */
        unsigned int  i2c_debug_addr_10bit : 1;  /* bit[14]   : ��ӦI2C�ڲ���debug�ź� */
        unsigned int  i2c_debug_addr       : 1;  /* bit[15]   : ��ӦI2C�ڲ���debug�ź� */
        unsigned int  i2c_debug_data       : 1;  /* bit[16]   : ��ӦI2C�ڲ���debug�ź� */
        unsigned int  i2c_debug_p_gen      : 1;  /* bit[17]   : ��ӦI2C�ڲ���debug�ź� */
        unsigned int  i2c_debug_s_gen      : 1;  /* bit[18]   : ��ӦI2C�ڲ���debug�ź� */
        unsigned int  reserved             : 13; /* bit[19-31]: ���� */
    } reg;
} SOC_PMUI2C_DEBUG_UNION;
#endif
#define SOC_PMUI2C_DEBUG_pmui2c_debug_err_START      (0)
#define SOC_PMUI2C_DEBUG_pmui2c_debug_err_END        (0)
#define SOC_PMUI2C_DEBUG_i2c_debug_slv_cstate_START  (1)
#define SOC_PMUI2C_DEBUG_i2c_debug_slv_cstate_END    (3)
#define SOC_PMUI2C_DEBUG_i2c_debug_mst_cstate_START  (4)
#define SOC_PMUI2C_DEBUG_i2c_debug_mst_cstate_END    (8)
#define SOC_PMUI2C_DEBUG_i2c_debug_slave_act_START   (9)
#define SOC_PMUI2C_DEBUG_i2c_debug_slave_act_END     (9)
#define SOC_PMUI2C_DEBUG_i2c_debug_master_act_START  (10)
#define SOC_PMUI2C_DEBUG_i2c_debug_master_act_END    (10)
#define SOC_PMUI2C_DEBUG_i2c_debug_hs_START          (11)
#define SOC_PMUI2C_DEBUG_i2c_debug_hs_END            (11)
#define SOC_PMUI2C_DEBUG_i2c_debug_wr_START          (12)
#define SOC_PMUI2C_DEBUG_i2c_debug_wr_END            (12)
#define SOC_PMUI2C_DEBUG_i2c_debug_rd_START          (13)
#define SOC_PMUI2C_DEBUG_i2c_debug_rd_END            (13)
#define SOC_PMUI2C_DEBUG_i2c_debug_addr_10bit_START  (14)
#define SOC_PMUI2C_DEBUG_i2c_debug_addr_10bit_END    (14)
#define SOC_PMUI2C_DEBUG_i2c_debug_addr_START        (15)
#define SOC_PMUI2C_DEBUG_i2c_debug_addr_END          (15)
#define SOC_PMUI2C_DEBUG_i2c_debug_data_START        (16)
#define SOC_PMUI2C_DEBUG_i2c_debug_data_END          (16)
#define SOC_PMUI2C_DEBUG_i2c_debug_p_gen_START       (17)
#define SOC_PMUI2C_DEBUG_i2c_debug_p_gen_END         (17)
#define SOC_PMUI2C_DEBUG_i2c_debug_s_gen_START       (18)
#define SOC_PMUI2C_DEBUG_i2c_debug_s_gen_END         (18)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_PMUI2CSTATE_UNION
 �ṹ˵��  : PMUI2CSTATE �Ĵ����ṹ���塣��ַƫ����:0x013C����ֵ:0x0�����:32
 �Ĵ���˵��: PMUI2C״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmui2c_cur_state : 1;  /* bit[0]   : PMUI2C�л���ɺ��ģʽ */
        unsigned int  pmui2c_pre_state : 1;  /* bit[1]   : PMUI2CԤ��Ҫ�л���ģʽ */
        unsigned int  reserved         : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_PMUI2C_PMUI2CSTATE_UNION;
#endif
#define SOC_PMUI2C_PMUI2CSTATE_pmui2c_cur_state_START  (0)
#define SOC_PMUI2C_PMUI2CSTATE_pmui2c_cur_state_END    (0)
#define SOC_PMUI2C_PMUI2CSTATE_pmui2c_pre_state_START  (1)
#define SOC_PMUI2C_PMUI2CSTATE_pmui2c_pre_state_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_HOLD_IDLE_UNION
 �ṹ˵��  : HOLD_IDLE �Ĵ����ṹ���塣��ַƫ����:0x0140����ֵ:0x1�����:32
 �Ĵ���˵��: PMUI2C hold/idleģʽѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hold_idle : 1;  /* bit[0-0] : 0��Ӧholdģʽ
                                                    1��Ӧidleģʽ */
        unsigned int  reserved  : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_PMUI2C_HOLD_IDLE_UNION;
#endif
#define SOC_PMUI2C_HOLD_IDLE_hold_idle_START  (0)
#define SOC_PMUI2C_HOLD_IDLE_hold_idle_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMUI2C_SLAVE_CHOSE_UNION
 �ṹ˵��  : SLAVE_CHOSE �Ĵ����ṹ���塣��ַƫ����:0x0144����ֵ:0x0�����:32
 �Ĵ���˵��: PMUI2C ��/˫Slaveѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slave_chose : 1;  /* bit[0-0] : 0��Ӧһ��slave
                                                      1��Ӧ����slave */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_PMUI2C_SLAVE_CHOSE_UNION;
#endif
#define SOC_PMUI2C_SLAVE_CHOSE_slave_chose_START  (0)
#define SOC_PMUI2C_SLAVE_CHOSE_slave_chose_END    (0)






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

#endif /* end of soc_pmui2c_interface.h */
