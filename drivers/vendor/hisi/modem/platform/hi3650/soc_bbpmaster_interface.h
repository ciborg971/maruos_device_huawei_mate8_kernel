#ifndef __SOC_BBP_MASTER_INTERFACE_H__
#define __SOC_BBP_MASTER_INTERFACE_H__

#define SOC_BBPMASTER_REG_ADDR(base, offset)                ((base)+(offset))

/* ��������д������ļĴ��� */
#define W_BBP_MASTER_RPT_CLR_HIGH_VALUE                     (0x00000001)

/* �����жϼĴ���ֵ */
#define W_BBP_MASTER_ISR_SHIELD_VALUE                       (0x00000001)

/* �������жϼĴ���ֵ */
#define W_BBP_MASTER_ISR_UNSHIELD_VALUE                     (0x0)

/* ˮ���жϼĴ���MASK */
#define W_BBP_MASTER_ISR_WL_MASK_VALUE                      (0x00000001)

/* �����жϼĴ���MASK */
#define W_BBP_MASTER_ISR_YL_MASK_VALUE                      (0x00000002)

/* ��ʱ���жϼĴ���MASK */
#define W_BBP_MASTER_ISR_TIMER_MASK_VALUE                   (0x00000004)

/* BBPMST���߷��ش����жϼĴ���MASK */
#define W_BBP_MASTER_ISR_BUS_ERROR_MASK_VALUE               (0x00000008)

/* BBPMST���ز����볬ʱ�жϼĴ���MASK */
#define W_BBP_MASTER_ISR_MAIN_STEM_OVETIME_MASK_VALUE       (0x00000010)

/* BBPMST���ز����볬ʱ�жϼĴ���MASK */
#define W_BBP_MASTER_ISR_SUB_STEM_OVETIME_MASK_VALUE        (0x00000020)

/* ���ز�����HSDPA�����ϱ�������CRCУ���������ݲ��ϱ��жϼĴ���MASK */
#define W_BBP_MASTER_ISR_MAIN_HSDPA_MASK_VALUE              (0x00000040)

/* ���ز�����HSDPA�����ϱ�������CRCУ���������ݲ��ϱ��жϼĴ���MASK */
#define W_BBP_MASTER_ISR_SUB_HSDPA_MASK_VALUE               (0x00000080)

/* �Ĵ���W_BBP_MASTER_HEAD_BUFFER_SIZE_REG(0x940C)�Ĵ�С������V9R1оƬ���TB Head��С��256�ֽڲü�Ϊ128�ֽ� */
#define W_BBP_MASTER_TB_HEAD_SIZE_VALUE                     (0x10000000)

/* ˮ��ֵ */
#define W_BBP_MASTER_RPT_WATER_LINE_VALUE                   (0xFFFFFFFF)

/* �����ϱ���ʱ��Ĭ��ʱ��ֵ */
#define W_BBP_MASTER_RPT_OVERTIME_DEFAULT_VALUE             (0x00001C80)

/* BBP MASTER�Ĵ�����ַ */
#define W_BBP_MASTER_MODE_FG_REG(BaseAddr)                  SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9400)

/* �ڶ�0x9408~0x9414��0x94A0~0x94A4���úú����øüĴ���������д������ʹ����Ч */
#define W_BBP_MASTER_RPT_CLR_REG(BaseAddr)                  SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9404)

/* �洢TB��ͷ����DDR�ռ���׵�ַ���������ַ */
#define W_BBP_MASTER_HEAD_BUFFER_BASE_ADDR_REG(BaseAddr)    SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9408)

/*  [31:24]TB��ͷ�Ĵ洢����С��64words��256byte����С��λ��8byte
    [23:0]�洢TB��ͷ��DDR�������ܴ洢��TB��ͷ�������� */
#define W_BBP_MASTER_HEAD_BUFFER_SIZE_REG(BaseAddr)         SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x940C)

/* �洢TB�����ݵ�DDR�ռ���׵�ַ���������ַ */
#define W_BBP_MASTER_DATA_BUFFER_BASE_ADDR_REG(BaseAddr)    SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9410)

/* �洢TB����������DDR�ռ�Ĵ�С����С��λ��8byte������data_buffer_size����Ϊ100����TB����������DDR�ռ��СΪ800byte */
#define W_BBP_MASTER_DATA_BUFFER_SIZE_REG(BaseAddr)         SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9414)

/* �����ж��ϱ���ˮ�� */
#define W_BBP_MASTER_HSD_RPT_WATERLINE_REG(BaseAddr)        SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9418)

/* �澯�ж��ϱ���ˮ��--���� */
#define W_BBP_MASTER_HSD_RPT_ALARMLINE_REG(BaseAddr)        SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x941C)

/*  ����趨�ĵȴ���ʱ�ж��ϱ�ʱ����
    ��ʱ��ʱ�� = Hsd_rpt_overtime_value * 32 * Tclk����ʼֵΪ10ms����10ms*245.76MHz/32 */
#define W_BBP_MASTER_HSD_RPT_OVERTIME_VALUE_REG(BaseAddr)   SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9420)

/* �����ú�0x9418~0x9420�Լ�0x9428�����߸üĴ���������һ��д������ʹ����Ч */
#define W_BBP_MASTER_HSD_RPT_SUB_PULSE_REG(BaseAddr)        SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9424)

/* һ�����ݰ��ƹ�����ȡ�ߵ�TB�������Ϊ�����û�а����κ����ݣ���ֵ��Ӧ�ô������������HSD_RPT_TB_CNTֵ */
#define W_BBP_MASTER_HSD_RPT_SUB_REG(BaseAddr)              SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9428)

/* ���ϱ�������û��������ߵ�TB����� */
#define W_BBP_MASTER_HSD_RPT_TB_CNT_REG(BaseAddr)           SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x942C)

/* ���ϱ�����HEAD���е�д��ַָ�룬Ϊ�����ַ */
#define W_BBP_MASTER_HEAD_BUFFER_WR_INDEX_REG(BaseAddr)     SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9430)

/* TB_CNT��ʼֵ */
#define W_BBP_MASTER_HSD_RPT_TB_CNT_INIT_REG(BaseAddr)      SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x9460)

/* �����ú�0x9460�����߸üĴ���������һ��д������ʹ����Ч */
#define W_BBP_MASTER_HSD_RPT_TB_CNT_CLR_REG(BaseAddr)       SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x94A8)

/* TBͷ������ַƫ��ֵ */
#define W_BBP_MASTER_HEAD_BUFFER_OFFSET_ADDR_REG(BaseAddr)  SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x94A0)

/* ��������ַƫ��ֵ */
#define W_BBP_MASTER_DATA_BUFFER_OFFSET_ADDR_REG(BaseAddr)  SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x94A4)

/* Dallas��ʼ�������á�
   ÿ��TB���������DDR����ռ�Ŀռ��С����λ:8byte����DDR����������ѭ���洢����С����Ϊ��ֵ����������
   ��Ҫ��data_buffer_size=tb_data_fix_size*N��N��������� */
#define W_BBP_MASTER_TB_DATA_SIZE_REG(BaseAddr)             SOC_BBPMASTER_REG_ADDR(BaseAddr, 0x94AC)

/* =====BBPMSTER�жϼĴ������===== */
/* BBPMSTER�ж�״̬�Ĵ��� */
#define W_BBP_MASTER_ISR_STATE_REG(BaseAddr)                SOC_BBPMASTER_REG_ADDR(BaseAddr, 0xC0)

/* BBPMSTER�ж�����MASK�Ĵ��� */
#define W_BBP_MASTER_ISR_MASK_REG(BaseAddr)                 SOC_BBPMASTER_REG_ADDR(BaseAddr, 0xC4)

/* BBPMSTER�ж�ʹ�ܼĴ��� */
#define W_BBP_MASTER_ISR_ENABLE_REG(BaseAddr)               SOC_BBPMASTER_REG_ADDR(BaseAddr, 0xC8)

/* BBPMSTER�ж�����Ĵ��� */
#define W_BBP_MASTER_ISR_CLR_REG(BaseAddr)                  SOC_BBPMASTER_REG_ADDR(BaseAddr, 0xCC)

#endif
