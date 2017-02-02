

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __BBP_COMM_INTERFACE_H__
#define __BBP_COMM_INTERFACE_H__

#include "bbp_common_interface.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/2) register_define_bbpmst
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��дͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_wr_ch0_mode����дͨ��0�Ĺ���ģʽ
             1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵�axi�ӿڲ��ٷ����µĶ�/д����������еĶ�дͨ����û���������ˣ���axi���Լ����߱��ͷţ��Ƿ��ͷŵ�״̬��cpu�ӿ����ϱ����������ϸ�״̬�������ſػ��������
             2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
             3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
             4��3'b100��ͨ�����ø�������ӿ�ʹ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH0_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH0_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA800)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��дͨ��������ʱ����ѡ��
             1��3��b001����дͨ��������ӿ�ʹ�õ�һ��ʱ����
             2��3��b010����дͨ��������ӿ�ʹ�õڶ���ʱ����
             3��3��b100����дͨ��������ӿ�ʹ�õ�����ʱ����
             ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
             ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
             ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ��
             
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH0_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH0_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA804)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH0_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA808)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH0_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA80C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA810)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ͨ����ѡ��ʹ�õ�master�ڣ�
             1'b0����ͨ��ʹ��master��1
             1'b1����ͨ��ʹ��master��2
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH0_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH0_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA814)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��дͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_wr_ch0_mode����дͨ��0�Ĺ���ģʽ
             1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵�axi�ӿڲ��ٷ����µĶ�/д����������еĶ�дͨ����û���������ˣ���axi���Լ����߱��ͷţ��Ƿ��ͷŵ�״̬��cpu�ӿ����ϱ����������ϸ�״̬�������ſػ��������
             2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
             3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
             4��3'b100��ͨ�����ø�������ӿ�ʹ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH1_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH1_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA820)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��дͨ��������ʱ����ѡ��
             1��3��b001����дͨ��������ӿ�ʹ�õ�һ��ʱ����
             2��3��b010����дͨ��������ӿ�ʹ�õڶ���ʱ����
             3��3��b100����дͨ��������ӿ�ʹ�õ�����ʱ����
             ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
             ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
             ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ��
             
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH1_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH1_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA824)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH1_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA828)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH1_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA82C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA830)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ͨ����ѡ��ʹ�õ�master�ڣ�
             1'b0����ͨ��ʹ��master��1
             1'b1����ͨ��ʹ��master��2
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH1_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH1_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA834)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��дͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_wr_ch0_mode����дͨ��0�Ĺ���ģʽ
             1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵�axi�ӿڲ��ٷ����µĶ�/д����������еĶ�дͨ����û���������ˣ���axi���Լ����߱��ͷţ��Ƿ��ͷŵ�״̬��cpu�ӿ����ϱ����������ϸ�״̬�������ſػ��������
             2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
             3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
             4��3'b100��ͨ�����ø�������ӿ�ʹ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH2_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH2_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA840)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��дͨ��������ʱ����ѡ��
             1��3��b001����дͨ��������ӿ�ʹ�õ�һ��ʱ����
             2��3��b010����дͨ��������ӿ�ʹ�õڶ���ʱ����
             3��3��b100����дͨ��������ӿ�ʹ�õ�����ʱ����
             ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
             ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
             ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ��
             
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH2_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH2_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA844)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH2_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA848)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH2_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA84C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA850)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ͨ����ѡ��ʹ�õ�master�ڣ�
             1'b0����ͨ��ʹ��master��1
             1'b1����ͨ��ʹ��master��2
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH2_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH2_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA854)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��дͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_wr_ch0_mode����дͨ��0�Ĺ���ģʽ
             1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵�axi�ӿڲ��ٷ����µĶ�/д����������еĶ�дͨ����û���������ˣ���axi���Լ����߱��ͷţ��Ƿ��ͷŵ�״̬��cpu�ӿ����ϱ����������ϸ�״̬�������ſػ��������
             2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
             3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
             4��3'b100��ͨ�����ø�������ӿ�ʹ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH3_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH3_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA860)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��дͨ��������ʱ����ѡ��
             1��3��b001����дͨ��������ӿ�ʹ�õ�һ��ʱ����
             2��3��b010����дͨ��������ӿ�ʹ�õڶ���ʱ����
             3��3��b100����дͨ��������ӿ�ʹ�õ�����ʱ����
             ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
             ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
             ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ��
             
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH3_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH3_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA864)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH3_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA868)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH3_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA86C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA870)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ͨ����ѡ��ʹ�õ�master�ڣ�
             1'b0����ͨ��ʹ��master��1
             1'b1����ͨ��ʹ��master��2
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH3_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH3_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA874)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��дͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_wr_ch0_mode����дͨ��0�Ĺ���ģʽ
             1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵�axi�ӿڲ��ٷ����µĶ�/д����������еĶ�дͨ����û���������ˣ���axi���Լ����߱��ͷţ��Ƿ��ͷŵ�״̬��cpu�ӿ����ϱ����������ϸ�״̬�������ſػ��������
             2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
             3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
             4��3'b100��ͨ�����ø�������ӿ�ʹ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH4_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH4_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA880)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��дͨ��������ʱ����ѡ��
             1��3��b001����дͨ��������ӿ�ʹ�õ�һ��ʱ����
             2��3��b010����дͨ��������ӿ�ʹ�õڶ���ʱ����
             3��3��b100����дͨ��������ӿ�ʹ�õ�����ʱ����
             ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
             ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
             ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ��
             
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH4_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH4_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA884)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH4_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA888)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH4_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA88C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA890)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ͨ����ѡ��ʹ�õ�master�ڣ�
             1'b0����ͨ��ʹ��master��1
             1'b1����ͨ��ʹ��master��2
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH4_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH4_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA894)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19]     ��ͨ��3�Ŀ���/æµ״̬��
             1'b0��ͨ�����ſգ����ڿ���̬
             1'b1��ͨ������æµ״̬
 bit[18]     ��ͨ��2�Ŀ���/æµ״̬��
             1'b0��ͨ�����ſգ����ڿ���̬
             1'b1��ͨ������æµ״̬
 bit[17]     ��ͨ��1�Ŀ���/æµ״̬��
             1'b0��ͨ�����ſգ����ڿ���̬
             1'b1��ͨ������æµ״̬
 bit[16]     ��ͨ��0�Ŀ���/æµ״̬��
             1'b0��ͨ�����ſգ����ڿ���̬
             1'b1��ͨ������æµ״̬
 bit[15:5]   ����
 bit[4]      дͨ��4�Ŀ���/æµ״̬��
             1'b0��ͨ�����ſգ����ڿ���̬
             1'b1��ͨ������æµ״̬
 bit[3]      дͨ��3�Ŀ���/æµ״̬��
             1'b0��ͨ�����ſգ����ڿ���̬
             1'b1��ͨ������æµ״̬
 bit[2]      дͨ��2�Ŀ���/æµ״̬��
             1'b0��ͨ�����ſգ����ڿ���̬
             1'b1��ͨ������æµ״̬
 bit[1]      дͨ��1�Ŀ���/æµ״̬��
             1'b0��ͨ�����ſգ����ڿ���̬
             1'b1��ͨ������æµ״̬
 bit[0]      дͨ��0�Ŀ���/æµ״̬��
             1'b0��ͨ�����ſգ����ڿ���̬
             1'b1��ͨ������æµ״̬
   UNION�ṹ:  BBPCOMM_BBPMST_CH_BUSY_UNION */
#define BBPCOMM_BBPMST_CH_BUSY_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xA898)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    �ö�ͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_rd_ch0_mode�����ͨ��0�Ĺ���ģʽ
             1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵Ķ�д���Ʋ��ٷ����µĶ�/д����������еĶ�дͨ����û����������master�ڱ��ͷţ�����״̬��cpu�ӿ��ϱ��������ϸ�״̬�������ſػ��������
             2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
             3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
             4��3'b100��ͨ�����ø�������ӿ�ʹ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH0_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH0_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA900)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    �ö�ͨ��������ʱ����ѡ��
             1��3��b001���ö�ͨ��������ӿ�ʹ�õ�һ��ʱ����
             2��3��b010���ö�ͨ��������ӿ�ʹ�õڶ���ʱ����
             3��3��b100���ö�ͨ��������ӿ�ʹ�õ�����ʱ����
             ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
             ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
             ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH0_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH0_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA904)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH0_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA908)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA90C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ͨ����ѡ��ʹ�õ�master�ڣ�
             1'b0����ͨ��ʹ��master��1
             1'b1����ͨ��ʹ��master��2
             
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH0_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH0_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA910)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    �ö�ͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_rd_ch0_mode�����ͨ��0�Ĺ���ģʽ
             1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵Ķ�д���Ʋ��ٷ����µĶ�/д����������еĶ�дͨ����û����������master�ڱ��ͷţ�����״̬��cpu�ӿ��ϱ��������ϸ�״̬�������ſػ��������
             2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
             3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
             4��3'b100��ͨ�����ø�������ӿ�ʹ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH1_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH1_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA920)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    �ö�ͨ��������ʱ����ѡ��
             1��3��b001���ö�ͨ��������ӿ�ʹ�õ�һ��ʱ����
             2��3��b010���ö�ͨ��������ӿ�ʹ�õڶ���ʱ����
             3��3��b100���ö�ͨ��������ӿ�ʹ�õ�����ʱ����
             ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
             ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
             ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH1_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH1_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA924)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH1_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA928)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA92C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ͨ����ѡ��ʹ�õ�master�ڣ�
             1'b0����ͨ��ʹ��master��1
             1'b1����ͨ��ʹ��master��2
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH1_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH1_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA930)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    �ö�ͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_rd_ch0_mode�����ͨ��0�Ĺ���ģʽ
             1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵Ķ�д���Ʋ��ٷ����µĶ�/д����������еĶ�дͨ����û����������master�ڱ��ͷţ�����״̬��cpu�ӿ��ϱ��������ϸ�״̬�������ſػ��������
             2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
             3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
             4��3'b100��ͨ�����ø�������ӿ�ʹ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH2_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH2_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA940)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    �ö�ͨ��������ʱ����ѡ��
             1��3��b001���ö�ͨ��������ӿ�ʹ�õ�һ��ʱ����
             2��3��b010���ö�ͨ��������ӿ�ʹ�õڶ���ʱ����
             3��3��b100���ö�ͨ��������ӿ�ʹ�õ�����ʱ����
             ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
             ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
             ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH2_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH2_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA944)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH2_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA948)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA94C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ͨ����ѡ��ʹ�õ�master�ڣ�
             1'b0����ͨ��ʹ��master��1
             1'b1����ͨ��ʹ��master��2
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH2_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH2_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA950)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    �ö�ͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_rd_ch0_mode�����ͨ��0�Ĺ���ģʽ
             1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵Ķ�д���Ʋ��ٷ����µĶ�/д����������еĶ�дͨ����û����������master�ڱ��ͷţ�����״̬��cpu�ӿ��ϱ��������ϸ�״̬�������ſػ��������
             2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
             3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
             4��3'b100��ͨ�����ø�������ӿ�ʹ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH3_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH3_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA960)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    �ö�ͨ��������ʱ����ѡ��
             1��3��b001���ö�ͨ��������ӿ�ʹ�õ�һ��ʱ����
             2��3��b010���ö�ͨ��������ӿ�ʹ�õڶ���ʱ����
             3��3��b100���ö�ͨ��������ӿ�ʹ�õ�����ʱ����
             ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
             ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
             ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ��
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH3_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH3_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA964)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH3_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA968)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA96C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ͨ����ѡ��ʹ�õ�master�ڣ�
             1'b0����ͨ��ʹ��master��1
             1'b1����ͨ��ʹ��master��2
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH3_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH3_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA970)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��0ÿ��64���ض�������Ч���ݸ���ָʾ��0����ʾÿ��64���ض����ݺ�10����Ч���ݣ�1����ʾÿ��64���ض����ݺ�16����Ч���ݣ�2����ʾÿ��64���ض����ݺ�1����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xA974)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��1ÿ��64���ض�������Ч���ݸ���ָʾ��0����ʾÿ��64���ض����ݺ�10����Ч���ݣ�1����ʾÿ��64���ض����ݺ�16����Ч���ݣ�2����ʾÿ��64���ض����ݺ�1����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xA978)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��2ÿ��64���ض�������Ч���ݸ���ָʾ��0����ʾÿ��64���ض����ݺ�10����Ч���ݣ�1����ʾÿ��64���ض����ݺ�16����Ч���ݣ�2����ʾÿ��64���ض����ݺ�16����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xA97C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��3ÿ��64���ض�������Ч���ݸ���ָʾ��0����ʾÿ��64���ض����ݺ�10����Ч���ݣ�1����ʾÿ��64���ض����ݺ�16����Ч���ݣ�2����ʾÿ��64���ض����ݺ�1����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xA980)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2]      axi��0дͨ���Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
             1��b0�����У������ѱ��ͷŵ�
             1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/����
             
 bit[1]      axi��0��ͨ���Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
             1��b0�����У������ѱ��ͷŵ�
             1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/����
             
 bit[0]      axi��0�Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
             1��b0�����У������ѱ��ͷŵ�
             1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/����
             
   UNION�ṹ:  BBPCOMM_BBPMST_AXI0_STATUS_UNION */
#define BBPCOMM_BBPMST_AXI0_STATUS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xAB00)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2]      axi��1��дͨ��״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
             1��b0�����У������ѱ��ͷŵ�
             1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/����
             
 bit[1]      axi��1�Ķ�ͨ��״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
             1��b0�����У������ѱ��ͷŵ�
             1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/����
             
 bit[0]      axi��1�Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
             1��b0�����У������ѱ��ͷŵ�
             1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/����
             
   UNION�ṹ:  BBPCOMM_BBPMST_AXI1_STATUS_UNION */
#define BBPCOMM_BBPMST_AXI1_STATUS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xAB04)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��bbpmstдerror����ʱ���ٽ���burst������0
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_BURST_BEAT0_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT0_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xAB08)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��bbpmstдerror����ʱ���ٽ���burst������1
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_BURST_BEAT1_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT1_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xAB0C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��bbpmstдerror����ʱ���ٽ���burst������2
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_BURST_BEAT2_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT2_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xAB10)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��bbpmstдerror����ʱ���ٽ���burst������3
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_BURST_BEAT3_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT3_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xAB14)

/* �Ĵ���˵����
   ��      ������bbpmstдerror����ʱ���ٽ���burst�Ļ���ַ0
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR0_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xAB18)

/* �Ĵ���˵����
   ��      ������bbpmstдerror����ʱ���ٽ���burst�Ļ���ַ1
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR1_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xAB1C)

/* �Ĵ���˵����
   ��      ������bbpmstдerror����ʱ���ٽ���burst�Ļ���ַ2
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR2_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xAB20)

/* �Ĵ���˵����
   ��      ������bbpmstдerror����ʱ���ٽ���burst�Ļ���ַ3
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR3_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xAB24)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      bbpmst��д�����ж�����Ĵ�������BBPMST��д��������ʱ��bbpmst_error_int��ֱ�����ɵ�ƽ�͸�BBE16\CCPU������յ��жϺ����øüĴ�������жϵ�ƽ��
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_INT_CLR_UNION */
#define BBPCOMM_BBPMST_ERROR_INT_CLR_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xAB28)

/* �Ĵ���˵����
 bit[31:16]  1w2r˫�˿�ram��ʱ���ơ�
 bit[15:0]   ���˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL0_BBPMST_UNION */
#define BBPCOMM_MEM_CTRL0_BBPMST_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xAB2C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  rom��ʱ���ơ�
 bit[15:0]   1rw2rw˫�˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL1_BBPMST_UNION */
#define BBPCOMM_MEM_CTRL1_BBPMST_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xAB30)

/* �Ĵ���˵����
   ��      ����AXI��0������BBPMSTдͨ��д�������Ӧ����ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_WR0_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xAB34)

/* �Ĵ���˵����
   ��      ����AXI��0������BBPMST��ͨ�����������Ӧ����ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_RD0_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xAB38)

/* �Ĵ���˵����
   ��      ����AXI��1������BBPMSTдͨ��д�������Ӧ����ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_WR1_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xAB3C)

/* �Ĵ���˵����
   ��      ����AXI��1������BBPMST��ͨ�����������Ӧ����ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_RD1_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xAB40)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:8]   AXI��0��ǰд��ӦID
 bit[7:5]    ����
 bit[4]      AXI��0��ǰд��Ӧ������Чָʾ
 bit[3:1]    ����
 bit[0]      AXI��0��ǰд��Ӧ�ɽ�������ָʾ
   UNION�ṹ:  BBPCOMM_AXI_WR0_STATE_UNION */
#define BBPCOMM_AXI_WR0_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xAB44)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:8]   AXI��0��ǰ����ӦID
 bit[7:5]    ����
 bit[4]      AXI��0��ǰ����Ӧ������Чָʾ
 bit[3:1]    ����
 bit[0]      AXI��0��ǰ����Ӧ�ɽ�������ָʾ
   UNION�ṹ:  BBPCOMM_AXI_RD0_STATE_UNION */
#define BBPCOMM_AXI_RD0_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xAB48)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:8]   AXI��1��ǰд��ӦID
 bit[7:5]    ����
 bit[4]      AXI��1��ǰд��Ӧ������Чָʾ
 bit[3:1]    ����
 bit[0]      AXI��1��ǰд��Ӧ�ɽ�������ָʾ
   UNION�ṹ:  BBPCOMM_AXI_WR1_STATE_UNION */
#define BBPCOMM_AXI_WR1_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xAB4C)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:8]   AXI��1��ǰ����ӦID
 bit[7:5]    ����
 bit[4]      AXI��1��ǰ����Ӧ������Чָʾ
 bit[3:1]    ����
 bit[0]      AXI��1��ǰ����Ӧ�ɽ�������ָʾ
   UNION�ṹ:  BBPCOMM_AXI_RD1_STATE_UNION */
#define BBPCOMM_AXI_RD1_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xAB50)

/* �Ĵ���˵����
   ��      ����AXI��0������BBPMSTдͨ�����ݴ������ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_WR0_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xAB54)

/* �Ĵ���˵����
   ��      ����AXI��0������BBPMST��ͨ�����ݴ������ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_RD0_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xAB58)

/* �Ĵ���˵����
   ��      ����AXI��1������BBPMSTдͨ�����ݴ������ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_WR1_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xAB5C)

/* �Ĵ���˵����
   ��      ����AXI��1������BBPMST��ͨ�����ݴ������ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_RD1_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xAB60)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BBPMST��д�����ж�ʹ��
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_INT_EN_UNION */
#define BBPCOMM_BBPMST_ERROR_INT_EN_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xAB64)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BBPMST��д�����ж������ź�
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_INT_MASK_UNION */
#define BBPCOMM_BBPMST_ERROR_INT_MASK_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xAB68)



/***======================================================================***
                     (2/2) register_define_irm_ps
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:0]    ����irm_ps����ģʽѡ��Ӱ��irm_ps�ڲ�ʱ���л���ģʽ�л���Ĭ�϶�Ϊ0��.
             6'b000001��GBBP1ģʽ��
             6'b000110��UMTSģʽ��
             6'b001000��LTEģʽ��
             6'b010000��TDS-CDMAģʽ��
             6'b100000��CDMAģʽ��
             ע��GBBP1�̶�Ϊ������G0/U/L/T����
   UNION�ṹ:  BBPCOMM_IRM_PS_RAM_CTRL_UNION */
#define BBPCOMM_IRM_PS_RAM_CTRL_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xB000)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      GBBP2��Ĭ��Ϊ0��1Ϊʹ�ܡ�
             ע��GBBP2�̶�Ϊ������
             V8R1��ʹ�á�
   UNION�ṹ:  BBPCOMM_IRM_PS_GSM2_CTRL_UNION */
#define BBPCOMM_IRM_PS_GSM2_CTRL_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xB004)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      irm_psģ��ʱ���ſ���·���ء�Ĭ��Ϊ0��������ʱ���ſء�����1������·���ܣ�ʱ���ſ�ʧЧ��
   UNION�ṹ:  BBPCOMM_IRM_PS_CLK_BYPASS_UNION */
#define BBPCOMM_IRM_PS_CLK_BYPASS_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xB008)

/* �Ĵ���˵����
 bit[31:16]  1w2r˫�˿�ram��ʱ���ơ�
 bit[15:0]   ���˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL0_TURBO_UNION */
#define BBPCOMM_MEM_CTRL0_TURBO_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xB010)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  rom��ʱ���ơ�
 bit[15:0]   1rw2rw˫�˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL1_TURBO_UNION */
#define BBPCOMM_MEM_CTRL1_TURBO_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xB014)

/* �Ĵ���˵����
 bit[31:16]  1w2r˫�˿�ram��ʱ���ơ�
 bit[15:0]   ���˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL0_PS_UNION */
#define BBPCOMM_MEM_CTRL0_PS_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xB020)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  rom��ʱ���ơ�
 bit[15:0]   1rw2rw˫�˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL1_PS_UNION */
#define BBPCOMM_MEM_CTRL1_PS_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xB024)

/* �Ĵ���˵����
 bit[31:16]  turbo������ģ�鼶�ſ���·ʹ�ܣ��ߵ�ƽ��Ч��
 bit[15:0]   turbo������ģ�鼶�ſ���·ʹ�ܣ��ߵ�ƽ��Ч��
   UNION�ṹ:  BBPCOMM_TUBO_CKG_UNION */
#define BBPCOMM_TUBO_CKG_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xB028)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      Turbo����ģʽѡ���źţ�Lģ����
             {U_C_TYPE, U_T_TYPE, U_L_TYPE}��������bitƴ����Ϻ������£�
             3'b000��Uģ��
             3'b001��Lģ��
             3'b010��Tģ��
             3'b100��Cģ��
             �����������塣
   UNION�ṹ:  BBPCOMM_U_L_TYPE_UNION */
#define BBPCOMM_U_L_TYPE_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xB02C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      Turbo����ģʽѡ���źţ�Tģ����
             {U_C_TYPE, U_T_TYPE, U_L_TYPE}��������bitƴ����Ϻ������£�
             3'b000��Uģ��
             3'b001��Lģ��
             3'b010��Tģ��
             3'b100��Cģ��
             �����������塣
   UNION�ṹ:  BBPCOMM_U_T_TYPE_UNION */
#define BBPCOMM_U_T_TYPE_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xB030)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      Turbo����ģʽѡ���źţ�Cģ����
             {U_C_TYPE, U_T_TYPE, U_L_TYPE}��������bitƴ����Ϻ������£�
             3'b000��Uģ��
             3'b001��Lģ��
             3'b010��Tģ��
             3'b100��Cģ��
             �����������塣
   UNION�ṹ:  BBPCOMM_U_C_TYPE_UNION */
#define BBPCOMM_U_C_TYPE_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xB034)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:14]  SOC AP���ø�ps ram��occupy�����źš�
 bit[13:12]  
 bit[11:10]  
 bit[9:8]    
 bit[7:6]    
 bit[5:4]    
 bit[3:2]    
 bit[1:0]    
   UNION�ṹ:  BBPCOMM_SOC_AP_OCCUPY_GRP_UNION */
#define BBPCOMM_SOC_AP_OCCUPY_GRP_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xB038)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1]      W SDRģʽ������ʱ��ѡ��0���������122mʱ�ӣ�1���������245mʱ�ӡ�
 bit[0]      W SDRģʽ����ʹ�ܡ�
   UNION�ṹ:  BBPCOMM_PS_W_SDR_EN_UNION */
#define BBPCOMM_PS_W_SDR_EN_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xB03C)





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
                     (1/2) register_define_bbpmst
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH0_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH0_MODE �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch0_mode_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch0_mode : 3;  /* bit[0-2] : ��дͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_wr_ch0_mode����дͨ��0�Ĺ���ģʽ
                                                              1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵�axi�ӿڲ��ٷ����µĶ�/д����������еĶ�дͨ����û���������ˣ���axi���Լ����߱��ͷţ��Ƿ��ͷŵ�״̬��cpu�ӿ����ϱ����������ϸ�״̬�������ſػ��������
                                                              2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
                                                              3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
                                                              4��3'b100��ͨ�����ø�������ӿ�ʹ�� */
        unsigned long  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_mode_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_mode_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH0_CLK_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH0_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch0_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch0_clk_sel : 3;  /* bit[0-2] : ��дͨ��������ʱ����ѡ��
                                                                 1��3��b001����дͨ��������ӿ�ʹ�õ�һ��ʱ����
                                                                 2��3��b010����дͨ��������ӿ�ʹ�õڶ���ʱ����
                                                                 3��3��b100����дͨ��������ӿ�ʹ�õ�����ʱ����
                                                                 ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
                                                                 ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
                                                                 ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH0_CLK_SEL_bbpmst_wr_ch0_clk_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_CLK_SEL_bbpmst_wr_ch0_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH0_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000008�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch0_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch0_burst_beat : 4;  /* bit[0-3] : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_burst_beat_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH0_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH0_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch0_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch0_axi_sel : 1;  /* bit[0]   : ��ͨ����ѡ��ʹ�õ�master�ڣ�
                                                                 1'b0����ͨ��ʹ��master��1
                                                                 1'b1����ͨ��ʹ��master��2 */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH0_AXI_SEL_bbpmst_wr_ch0_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_AXI_SEL_bbpmst_wr_ch0_axi_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH1_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH1_MODE �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch1_mode_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch1_mode : 3;  /* bit[0-2] : ��дͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_wr_ch0_mode����дͨ��0�Ĺ���ģʽ
                                                              1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵�axi�ӿڲ��ٷ����µĶ�/д����������еĶ�дͨ����û���������ˣ���axi���Լ����߱��ͷţ��Ƿ��ͷŵ�״̬��cpu�ӿ����ϱ����������ϸ�״̬�������ſػ��������
                                                              2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
                                                              3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
                                                              4��3'b100��ͨ�����ø�������ӿ�ʹ�� */
        unsigned long  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_mode_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_mode_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH1_CLK_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH1_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch1_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch1_clk_sel : 3;  /* bit[0-2] : ��дͨ��������ʱ����ѡ��
                                                                 1��3��b001����дͨ��������ӿ�ʹ�õ�һ��ʱ����
                                                                 2��3��b010����дͨ��������ӿ�ʹ�õڶ���ʱ����
                                                                 3��3��b100����дͨ��������ӿ�ʹ�õ�����ʱ����
                                                                 ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
                                                                 ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
                                                                 ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH1_CLK_SEL_bbpmst_wr_ch1_clk_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_CLK_SEL_bbpmst_wr_ch1_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH1_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000008�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch1_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch1_burst_beat : 4;  /* bit[0-3] : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_burst_beat_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH1_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH1_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch1_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch1_axi_sel : 1;  /* bit[0]   : ��ͨ����ѡ��ʹ�õ�master�ڣ�
                                                                 1'b0����ͨ��ʹ��master��1
                                                                 1'b1����ͨ��ʹ��master��2 */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH1_AXI_SEL_bbpmst_wr_ch1_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_AXI_SEL_bbpmst_wr_ch1_axi_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH2_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH2_MODE �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch2_mode_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch2_mode : 3;  /* bit[0-2] : ��дͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_wr_ch0_mode����дͨ��0�Ĺ���ģʽ
                                                              1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵�axi�ӿڲ��ٷ����µĶ�/д����������еĶ�дͨ����û���������ˣ���axi���Լ����߱��ͷţ��Ƿ��ͷŵ�״̬��cpu�ӿ����ϱ����������ϸ�״̬�������ſػ��������
                                                              2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
                                                              3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
                                                              4��3'b100��ͨ�����ø�������ӿ�ʹ�� */
        unsigned long  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_mode_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_mode_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH2_CLK_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH2_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch2_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch2_clk_sel : 3;  /* bit[0-2] : ��дͨ��������ʱ����ѡ��
                                                                 1��3��b001����дͨ��������ӿ�ʹ�õ�һ��ʱ����
                                                                 2��3��b010����дͨ��������ӿ�ʹ�õڶ���ʱ����
                                                                 3��3��b100����дͨ��������ӿ�ʹ�õ�����ʱ����
                                                                 ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
                                                                 ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
                                                                 ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH2_CLK_SEL_bbpmst_wr_ch2_clk_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_CLK_SEL_bbpmst_wr_ch2_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH2_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000008�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch2_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch2_burst_beat : 4;  /* bit[0-3] : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_burst_beat_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH2_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH2_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch2_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch2_axi_sel : 1;  /* bit[0]   : ��ͨ����ѡ��ʹ�õ�master�ڣ�
                                                                 1'b0����ͨ��ʹ��master��1
                                                                 1'b1����ͨ��ʹ��master��2 */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH2_AXI_SEL_bbpmst_wr_ch2_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_AXI_SEL_bbpmst_wr_ch2_axi_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH3_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH3_MODE �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch3_mode_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch3_mode : 3;  /* bit[0-2] : ��дͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_wr_ch0_mode����дͨ��0�Ĺ���ģʽ
                                                              1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵�axi�ӿڲ��ٷ����µĶ�/д����������еĶ�дͨ����û���������ˣ���axi���Լ����߱��ͷţ��Ƿ��ͷŵ�״̬��cpu�ӿ����ϱ����������ϸ�״̬�������ſػ��������
                                                              2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
                                                              3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
                                                              4��3'b100��ͨ�����ø�������ӿ�ʹ�� */
        unsigned long  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_mode_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_mode_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH3_CLK_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH3_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch3_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch3_clk_sel : 3;  /* bit[0-2] : ��дͨ��������ʱ����ѡ��
                                                                 1��3��b001����дͨ��������ӿ�ʹ�õ�һ��ʱ����
                                                                 2��3��b010����дͨ��������ӿ�ʹ�õڶ���ʱ����
                                                                 3��3��b100����дͨ��������ӿ�ʹ�õ�����ʱ����
                                                                 ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
                                                                 ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
                                                                 ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH3_CLK_SEL_bbpmst_wr_ch3_clk_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_CLK_SEL_bbpmst_wr_ch3_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH3_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000008�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch3_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch3_burst_beat : 4;  /* bit[0-3] : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_burst_beat_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH3_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH3_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch3_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch3_axi_sel : 1;  /* bit[0]   : ��ͨ����ѡ��ʹ�õ�master�ڣ�
                                                                 1'b0����ͨ��ʹ��master��1
                                                                 1'b1����ͨ��ʹ��master��2 */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH3_AXI_SEL_bbpmst_wr_ch3_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_AXI_SEL_bbpmst_wr_ch3_axi_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH4_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH4_MODE �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch4_mode_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch4_mode : 3;  /* bit[0-2] : ��дͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_wr_ch0_mode����дͨ��0�Ĺ���ģʽ
                                                              1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵�axi�ӿڲ��ٷ����µĶ�/д����������еĶ�дͨ����û���������ˣ���axi���Լ����߱��ͷţ��Ƿ��ͷŵ�״̬��cpu�ӿ����ϱ����������ϸ�״̬�������ſػ��������
                                                              2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
                                                              3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
                                                              4��3'b100��ͨ�����ø�������ӿ�ʹ�� */
        unsigned long  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_mode_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_mode_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH4_CLK_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH4_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch4_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch4_clk_sel : 3;  /* bit[0-2] : ��дͨ��������ʱ����ѡ��
                                                                 1��3��b001����дͨ��������ӿ�ʹ�õ�һ��ʱ����
                                                                 2��3��b010����дͨ��������ӿ�ʹ�õڶ���ʱ����
                                                                 3��3��b100����дͨ��������ӿ�ʹ�õ�����ʱ����
                                                                 ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
                                                                 ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
                                                                 ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH4_CLK_SEL_bbpmst_wr_ch4_clk_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_CLK_SEL_bbpmst_wr_ch4_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH4_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000008�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch4_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch4_burst_beat : 4;  /* bit[0-3] : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_burst_beat_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH4_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH4_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch4_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch4_axi_sel : 1;  /* bit[0]   : ��ͨ����ѡ��ʹ�õ�master�ڣ�
                                                                 1'b0����ͨ��ʹ��master��1
                                                                 1'b1����ͨ��ʹ��master��2 */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH4_AXI_SEL_bbpmst_wr_ch4_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_AXI_SEL_bbpmst_wr_ch4_axi_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_CH_BUSY_UNION
 �ṹ˵��  : BBPMST_CH_BUSY �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_ch_busy_reg;
    struct
    {
        unsigned long  wr_ch0_busy : 1;  /* bit[0]    : дͨ��0�Ŀ���/æµ״̬��
                                                        1'b0��ͨ�����ſգ����ڿ���̬
                                                        1'b1��ͨ������æµ״̬ */
        unsigned long  wr_ch1_busy : 1;  /* bit[1]    : дͨ��1�Ŀ���/æµ״̬��
                                                        1'b0��ͨ�����ſգ����ڿ���̬
                                                        1'b1��ͨ������æµ״̬ */
        unsigned long  wr_ch2_busy : 1;  /* bit[2]    : дͨ��2�Ŀ���/æµ״̬��
                                                        1'b0��ͨ�����ſգ����ڿ���̬
                                                        1'b1��ͨ������æµ״̬ */
        unsigned long  wr_ch3_busy : 1;  /* bit[3]    : дͨ��3�Ŀ���/æµ״̬��
                                                        1'b0��ͨ�����ſգ����ڿ���̬
                                                        1'b1��ͨ������æµ״̬ */
        unsigned long  wr_ch4_busy : 1;  /* bit[4]    : дͨ��4�Ŀ���/æµ״̬��
                                                        1'b0��ͨ�����ſգ����ڿ���̬
                                                        1'b1��ͨ������æµ״̬ */
        unsigned long  reserved_0  : 11; /* bit[5-15] : ���� */
        unsigned long  rd_ch0_busy : 1;  /* bit[16]   : ��ͨ��0�Ŀ���/æµ״̬��
                                                        1'b0��ͨ�����ſգ����ڿ���̬
                                                        1'b1��ͨ������æµ״̬ */
        unsigned long  rd_ch1_busy : 1;  /* bit[17]   : ��ͨ��1�Ŀ���/æµ״̬��
                                                        1'b0��ͨ�����ſգ����ڿ���̬
                                                        1'b1��ͨ������æµ״̬ */
        unsigned long  rd_ch2_busy : 1;  /* bit[18]   : ��ͨ��2�Ŀ���/æµ״̬��
                                                        1'b0��ͨ�����ſգ����ڿ���̬
                                                        1'b1��ͨ������æµ״̬ */
        unsigned long  rd_ch3_busy : 1;  /* bit[19]   : ��ͨ��3�Ŀ���/æµ״̬��
                                                        1'b0��ͨ�����ſգ����ڿ���̬
                                                        1'b1��ͨ������æµ״̬ */
        unsigned long  reserved_1  : 12; /* bit[20-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_CH_BUSY_UNION;
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch0_busy_START  (0)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch0_busy_END    (0)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch1_busy_START  (1)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch1_busy_END    (1)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch2_busy_START  (2)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch2_busy_END    (2)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch3_busy_START  (3)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch3_busy_END    (3)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch4_busy_START  (4)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch4_busy_END    (4)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch0_busy_START  (16)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch0_busy_END    (16)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch1_busy_START  (17)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch1_busy_END    (17)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch2_busy_START  (18)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch2_busy_END    (18)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch3_busy_START  (19)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch3_busy_END    (19)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH0_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH0_MODE �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch0_mode_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch0_mode : 3;  /* bit[0-2] : �ö�ͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_rd_ch0_mode�����ͨ��0�Ĺ���ģʽ
                                                              1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵Ķ�д���Ʋ��ٷ����µĶ�/д����������еĶ�дͨ����û����������master�ڱ��ͷţ�����״̬��cpu�ӿ��ϱ��������ϸ�״̬�������ſػ��������
                                                              2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
                                                              3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
                                                              4��3'b100��ͨ�����ø�������ӿ�ʹ�� */
        unsigned long  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_mode_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_mode_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH0_CLK_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH0_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch0_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch0_clk_sel : 3;  /* bit[0-2] : �ö�ͨ��������ʱ����ѡ��
                                                                 1��3��b001���ö�ͨ��������ӿ�ʹ�õ�һ��ʱ����
                                                                 2��3��b010���ö�ͨ��������ӿ�ʹ�õڶ���ʱ����
                                                                 3��3��b100���ö�ͨ��������ӿ�ʹ�õ�����ʱ����
                                                                 ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
                                                                 ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
                                                                 ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH0_CLK_SEL_bbpmst_rd_ch0_clk_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_CLK_SEL_bbpmst_rd_ch0_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH0_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000008�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch0_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch0_burst_beat : 4;  /* bit[0-3] : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_burst_beat_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH0_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH0_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch0_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch0_axi_sel : 1;  /* bit[0]   : ��ͨ����ѡ��ʹ�õ�master�ڣ�
                                                                 1'b0����ͨ��ʹ��master��1
                                                                 1'b1����ͨ��ʹ��master��2 */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH0_AXI_SEL_bbpmst_rd_ch0_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_AXI_SEL_bbpmst_rd_ch0_axi_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH1_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH1_MODE �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch1_mode_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch1_mode : 3;  /* bit[0-2] : �ö�ͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_rd_ch0_mode�����ͨ��0�Ĺ���ģʽ
                                                              1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵Ķ�д���Ʋ��ٷ����µĶ�/д����������еĶ�дͨ����û����������master�ڱ��ͷţ�����״̬��cpu�ӿ��ϱ��������ϸ�״̬�������ſػ��������
                                                              2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
                                                              3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
                                                              4��3'b100��ͨ�����ø�������ӿ�ʹ�� */
        unsigned long  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_mode_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_mode_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH1_CLK_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH1_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch1_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch1_clk_sel : 3;  /* bit[0-2] : �ö�ͨ��������ʱ����ѡ��
                                                                 1��3��b001���ö�ͨ��������ӿ�ʹ�õ�һ��ʱ����
                                                                 2��3��b010���ö�ͨ��������ӿ�ʹ�õڶ���ʱ����
                                                                 3��3��b100���ö�ͨ��������ӿ�ʹ�õ�����ʱ����
                                                                 ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
                                                                 ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
                                                                 ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH1_CLK_SEL_bbpmst_rd_ch1_clk_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_CLK_SEL_bbpmst_rd_ch1_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH1_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x012C����ֵ:0x00000008�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch1_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch1_burst_beat : 4;  /* bit[0-3] : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_burst_beat_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH1_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH1_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch1_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch1_axi_sel : 1;  /* bit[0]   : ��ͨ����ѡ��ʹ�õ�master�ڣ�
                                                                 1'b0����ͨ��ʹ��master��1
                                                                 1'b1����ͨ��ʹ��master��2 */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH1_AXI_SEL_bbpmst_rd_ch1_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_AXI_SEL_bbpmst_rd_ch1_axi_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH2_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH2_MODE �Ĵ����ṹ���塣��ַƫ����:0x0140����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch2_mode_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch2_mode : 3;  /* bit[0-2] : �ö�ͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_rd_ch0_mode�����ͨ��0�Ĺ���ģʽ
                                                              1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵Ķ�д���Ʋ��ٷ����µĶ�/д����������еĶ�дͨ����û����������master�ڱ��ͷţ�����״̬��cpu�ӿ��ϱ��������ϸ�״̬�������ſػ��������
                                                              2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
                                                              3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
                                                              4��3'b100��ͨ�����ø�������ӿ�ʹ�� */
        unsigned long  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_mode_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_mode_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH2_CLK_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH2_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0144����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch2_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch2_clk_sel : 3;  /* bit[0-2] : �ö�ͨ��������ʱ����ѡ��
                                                                 1��3��b001���ö�ͨ��������ӿ�ʹ�õ�һ��ʱ����
                                                                 2��3��b010���ö�ͨ��������ӿ�ʹ�õڶ���ʱ����
                                                                 3��3��b100���ö�ͨ��������ӿ�ʹ�õ�����ʱ����
                                                                 ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
                                                                 ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
                                                                 ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH2_CLK_SEL_bbpmst_rd_ch2_clk_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_CLK_SEL_bbpmst_rd_ch2_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH2_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x014C����ֵ:0x00000008�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch2_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch2_burst_beat : 4;  /* bit[0-3] : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_burst_beat_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH2_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH2_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0150����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch2_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch2_axi_sel : 1;  /* bit[0]   : ��ͨ����ѡ��ʹ�õ�master�ڣ�
                                                                 1'b0����ͨ��ʹ��master��1
                                                                 1'b1����ͨ��ʹ��master��2 */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH2_AXI_SEL_bbpmst_rd_ch2_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_AXI_SEL_bbpmst_rd_ch2_axi_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH3_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH3_MODE �Ĵ����ṹ���塣��ַƫ����:0x0160����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch3_mode_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch3_mode : 3;  /* bit[0-2] : �ö�ͨ���Ĺ���ģʽ��ÿ��ͨ�����������3����ͬʱ���������������ã�bbpmst_rd_ch0_mode�����ͨ��0�Ĺ���ģʽ
                                                              1��3'b000 ��ͨ����ʹ�ܣ���ʱ��ͨ����ǰ����BBP���valid/readyΪ0����󼶵Ķ�д���Ʋ��ٷ����µĶ�/д����������еĶ�дͨ����û����������master�ڱ��ͷţ�����״̬��cpu�ӿ��ϱ��������ϸ�״̬�������ſػ��������
                                                              2��3'b001��ͨ�����ø���һ��ӿ�ʹ��
                                                              3��3'b010��ͨ�����ø��ڶ���ӿ�ʹ��
                                                              4��3'b100��ͨ�����ø�������ӿ�ʹ�� */
        unsigned long  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_mode_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_mode_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH3_CLK_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH3_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0164����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch3_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch3_clk_sel : 3;  /* bit[0-2] : �ö�ͨ��������ʱ����ѡ��
                                                                 1��3��b001���ö�ͨ��������ӿ�ʹ�õ�һ��ʱ����
                                                                 2��3��b010���ö�ͨ��������ӿ�ʹ�õڶ���ʱ����
                                                                 3��3��b100���ö�ͨ��������ӿ�ʹ�õ�����ʱ����
                                                                 ��v8r1�еĵ�һ�ֽӿ�ʱ��Ϊ��104MHz��Ϊgģ�Ĺ���ʱ��
                                                                 ��v8r1�еĵڶ��ֽӿ�ʱ��Ϊ��122.88MHz��ΪCģ�Լ�Uģ�г���������߼��Ĺ���ʱ�ӣ��Ҹ�ģ��cpu�ӿ�Ҳʹ�ø�ʱ����
                                                                 ��v8r1�еĵ����ֽӿ�ʱ��Ϊ��245.76MHz��ΪUģ������Ĺ���ʱ�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH3_CLK_SEL_bbpmst_rd_ch3_clk_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_CLK_SEL_bbpmst_rd_ch3_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH3_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x016C����ֵ:0x00000008�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch3_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch3_burst_beat : 4;  /* bit[0-3] : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_burst_beat_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH3_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH3_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0170����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch3_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch3_axi_sel : 1;  /* bit[0]   : ��ͨ����ѡ��ʹ�õ�master�ڣ�
                                                                 1'b0����ͨ��ʹ��master��1
                                                                 1'b1����ͨ��ʹ��master��2 */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH3_AXI_SEL_bbpmst_rd_ch3_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_AXI_SEL_bbpmst_rd_ch3_axi_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH0_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x0174����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch0_bit_width_ind_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch0_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��0ÿ��64���ض�������Ч���ݸ���ָʾ��0����ʾÿ��64���ض����ݺ�10����Ч���ݣ�1����ʾÿ��64���ض����ݺ�16����Ч���ݣ�2����ʾÿ��64���ض����ݺ�1����Ч���ݣ� */
        unsigned long  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_bbpmst_rd_ch0_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_bbpmst_rd_ch0_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH1_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x0178����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch1_bit_width_ind_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch1_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��1ÿ��64���ض�������Ч���ݸ���ָʾ��0����ʾÿ��64���ض����ݺ�10����Ч���ݣ�1����ʾÿ��64���ض����ݺ�16����Ч���ݣ�2����ʾÿ��64���ض����ݺ�1����Ч���ݣ� */
        unsigned long  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_bbpmst_rd_ch1_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_bbpmst_rd_ch1_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH2_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x017C����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch2_bit_width_ind_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch2_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��2ÿ��64���ض�������Ч���ݸ���ָʾ��0����ʾÿ��64���ض����ݺ�10����Ч���ݣ�1����ʾÿ��64���ض����ݺ�16����Ч���ݣ�2����ʾÿ��64���ض����ݺ�16����Ч���ݣ� */
        unsigned long  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_bbpmst_rd_ch2_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_bbpmst_rd_ch2_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH3_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x0180����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch3_bit_width_ind_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch3_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��3ÿ��64���ض�������Ч���ݸ���ָʾ��0����ʾÿ��64���ض����ݺ�10����Ч���ݣ�1����ʾÿ��64���ض����ݺ�16����Ч���ݣ�2����ʾÿ��64���ض����ݺ�1����Ч���ݣ� */
        unsigned long  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_bbpmst_rd_ch3_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_bbpmst_rd_ch3_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_AXI0_STATUS_UNION
 �ṹ˵��  : BBPMST_AXI0_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0300����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_axi0_status_reg;
    struct
    {
        unsigned long  bbpmst_axi0_status    : 1;  /* bit[0]   : axi��0�Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
                                                                 1��b0�����У������ѱ��ͷŵ�
                                                                 1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/���� */
        unsigned long  bbpmst_axi0_rd_status : 1;  /* bit[1]   : axi��0��ͨ���Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
                                                                 1��b0�����У������ѱ��ͷŵ�
                                                                 1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/���� */
        unsigned long  bbpmst_axi0_wr_status : 1;  /* bit[2]   : axi��0дͨ���Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
                                                                 1��b0�����У������ѱ��ͷŵ�
                                                                 1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/���� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_AXI0_STATUS_UNION;
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_status_START     (0)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_status_END       (0)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_rd_status_START  (1)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_rd_status_END    (1)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_wr_status_START  (2)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_wr_status_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_AXI1_STATUS_UNION
 �ṹ˵��  : BBPMST_AXI1_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0304����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_axi1_status_reg;
    struct
    {
        unsigned long  bbpmst_axi1_status    : 1;  /* bit[0]   : axi��1�Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
                                                                 1��b0�����У������ѱ��ͷŵ�
                                                                 1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/���� */
        unsigned long  bbpmst_axi1_rd_status : 1;  /* bit[1]   : axi��1�Ķ�ͨ��״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
                                                                 1��b0�����У������ѱ��ͷŵ�
                                                                 1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/���� */
        unsigned long  bbpmst_axi1_wr_status : 1;  /* bit[2]   : axi��1��дͨ��״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
                                                                 1��b0�����У������ѱ��ͷŵ�
                                                                 1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/���� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_AXI1_STATUS_UNION;
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_status_START     (0)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_status_END       (0)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_rd_status_START  (1)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_rd_status_END    (1)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_wr_status_START  (2)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_wr_status_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_BURST_BEAT0_UNION
 �ṹ˵��  : BBPMST_ERROR_BURST_BEAT0 �Ĵ����ṹ���塣��ַƫ����:0x0308����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_burst_beat0_reg;
    struct
    {
        unsigned long  bbpmst_error_burst_beat0 : 4;  /* bit[0-3] : ��bbpmstдerror����ʱ���ٽ���burst������0 */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_BURST_BEAT0_UNION;
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT0_bbpmst_error_burst_beat0_START  (0)
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT0_bbpmst_error_burst_beat0_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_BURST_BEAT1_UNION
 �ṹ˵��  : BBPMST_ERROR_BURST_BEAT1 �Ĵ����ṹ���塣��ַƫ����:0x030C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_burst_beat1_reg;
    struct
    {
        unsigned long  bbpmst_error_burst_beat1 : 4;  /* bit[0-3] : ��bbpmstдerror����ʱ���ٽ���burst������1 */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_BURST_BEAT1_UNION;
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT1_bbpmst_error_burst_beat1_START  (0)
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT1_bbpmst_error_burst_beat1_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_BURST_BEAT2_UNION
 �ṹ˵��  : BBPMST_ERROR_BURST_BEAT2 �Ĵ����ṹ���塣��ַƫ����:0x0310����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_burst_beat2_reg;
    struct
    {
        unsigned long  bbpmst_error_burst_beat2 : 4;  /* bit[0-3] : ��bbpmstдerror����ʱ���ٽ���burst������2 */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_BURST_BEAT2_UNION;
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT2_bbpmst_error_burst_beat2_START  (0)
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT2_bbpmst_error_burst_beat2_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_BURST_BEAT3_UNION
 �ṹ˵��  : BBPMST_ERROR_BURST_BEAT3 �Ĵ����ṹ���塣��ַƫ����:0x0314����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_burst_beat3_reg;
    struct
    {
        unsigned long  bbpmst_error_burst_beat3 : 4;  /* bit[0-3] : ��bbpmstдerror����ʱ���ٽ���burst������3 */
        unsigned long  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_BURST_BEAT3_UNION;
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT3_bbpmst_error_burst_beat3_START  (0)
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT3_bbpmst_error_burst_beat3_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_INT_CLR_UNION
 �ṹ˵��  : BBPMST_ERROR_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x0328����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_int_clr_reg;
    struct
    {
        unsigned long  bbpmst_error_int_clr : 1;  /* bit[0]   : bbpmst��д�����ж�����Ĵ�������BBPMST��д��������ʱ��bbpmst_error_int��ֱ�����ɵ�ƽ�͸�BBE16\CCPU������յ��жϺ����øüĴ�������жϵ�ƽ�� */
        unsigned long  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_INT_CLR_UNION;
#define BBPCOMM_BBPMST_ERROR_INT_CLR_bbpmst_error_int_clr_START  (0)
#define BBPCOMM_BBPMST_ERROR_INT_CLR_bbpmst_error_int_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL0_BBPMST_UNION
 �ṹ˵��  : MEM_CTRL0_BBPMST �Ĵ����ṹ���塣��ַƫ����:0x032C����ֵ:0x03501050�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl0_bbpmst_reg;
    struct
    {
        unsigned long  mem_ctrl_s_bbpmst      : 16; /* bit[0-15] : ���˿�ram��ʱ���ơ� */
        unsigned long  mem_ctrl_d_1w2r_bbpmst : 16; /* bit[16-31]: 1w2r˫�˿�ram��ʱ���ơ� */
    } reg;
} BBPCOMM_MEM_CTRL0_BBPMST_UNION;
#define BBPCOMM_MEM_CTRL0_BBPMST_mem_ctrl_s_bbpmst_START       (0)
#define BBPCOMM_MEM_CTRL0_BBPMST_mem_ctrl_s_bbpmst_END         (15)
#define BBPCOMM_MEM_CTRL0_BBPMST_mem_ctrl_d_1w2r_bbpmst_START  (16)
#define BBPCOMM_MEM_CTRL0_BBPMST_mem_ctrl_d_1w2r_bbpmst_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL1_BBPMST_UNION
 �ṹ˵��  : MEM_CTRL1_BBPMST �Ĵ����ṹ���塣��ַƫ����:0x0330����ֵ:0x00700057�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl1_bbpmst_reg;
    struct
    {
        unsigned long  mem_ctrl_d_1rw2rw_bbpmst : 16; /* bit[0-15] : 1rw2rw˫�˿�ram��ʱ���ơ� */
        unsigned long  rom_ctrl_bbpmst          : 8;  /* bit[16-23]: rom��ʱ���ơ� */
        unsigned long  reserved                 : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_MEM_CTRL1_BBPMST_UNION;
#define BBPCOMM_MEM_CTRL1_BBPMST_mem_ctrl_d_1rw2rw_bbpmst_START  (0)
#define BBPCOMM_MEM_CTRL1_BBPMST_mem_ctrl_d_1rw2rw_bbpmst_END    (15)
#define BBPCOMM_MEM_CTRL1_BBPMST_rom_ctrl_bbpmst_START           (16)
#define BBPCOMM_MEM_CTRL1_BBPMST_rom_ctrl_bbpmst_END             (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AXI_WR0_STATE_UNION
 �ṹ˵��  : AXI_WR0_STATE �Ĵ����ṹ���塣��ַƫ����:0x0344����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      axi_wr0_state_reg;
    struct
    {
        unsigned long  axi_wr0_ready  : 1;  /* bit[0]    : AXI��0��ǰд��Ӧ�ɽ�������ָʾ */
        unsigned long  reserved_0     : 3;  /* bit[1-3]  : ���� */
        unsigned long  axi_wr0_valid  : 1;  /* bit[4]    : AXI��0��ǰд��Ӧ������Чָʾ */
        unsigned long  reserved_1     : 3;  /* bit[5-7]  : ���� */
        unsigned long  axi_wr0_cur_id : 3;  /* bit[8-10] : AXI��0��ǰд��ӦID */
        unsigned long  reserved_2     : 21; /* bit[11-31]: ���� */
    } reg;
} BBPCOMM_AXI_WR0_STATE_UNION;
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_ready_START   (0)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_ready_END     (0)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_valid_START   (4)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_valid_END     (4)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_cur_id_START  (8)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_cur_id_END    (10)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AXI_RD0_STATE_UNION
 �ṹ˵��  : AXI_RD0_STATE �Ĵ����ṹ���塣��ַƫ����:0x0348����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      axi_rd0_state_reg;
    struct
    {
        unsigned long  axi_rd0_ready  : 1;  /* bit[0]    : AXI��0��ǰ����Ӧ�ɽ�������ָʾ */
        unsigned long  reserved_0     : 3;  /* bit[1-3]  : ���� */
        unsigned long  axi_rd0_valid  : 1;  /* bit[4]    : AXI��0��ǰ����Ӧ������Чָʾ */
        unsigned long  reserved_1     : 3;  /* bit[5-7]  : ���� */
        unsigned long  axi_rd0_cur_id : 3;  /* bit[8-10] : AXI��0��ǰ����ӦID */
        unsigned long  reserved_2     : 21; /* bit[11-31]: ���� */
    } reg;
} BBPCOMM_AXI_RD0_STATE_UNION;
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_ready_START   (0)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_ready_END     (0)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_valid_START   (4)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_valid_END     (4)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_cur_id_START  (8)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_cur_id_END    (10)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AXI_WR1_STATE_UNION
 �ṹ˵��  : AXI_WR1_STATE �Ĵ����ṹ���塣��ַƫ����:0x034C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      axi_wr1_state_reg;
    struct
    {
        unsigned long  axi_wr1_ready  : 1;  /* bit[0]    : AXI��1��ǰд��Ӧ�ɽ�������ָʾ */
        unsigned long  reserved_0     : 3;  /* bit[1-3]  : ���� */
        unsigned long  axi_wr1_valid  : 1;  /* bit[4]    : AXI��1��ǰд��Ӧ������Чָʾ */
        unsigned long  reserved_1     : 3;  /* bit[5-7]  : ���� */
        unsigned long  axi_wr1_cur_id : 3;  /* bit[8-10] : AXI��1��ǰд��ӦID */
        unsigned long  reserved_2     : 21; /* bit[11-31]: ���� */
    } reg;
} BBPCOMM_AXI_WR1_STATE_UNION;
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_ready_START   (0)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_ready_END     (0)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_valid_START   (4)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_valid_END     (4)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_cur_id_START  (8)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_cur_id_END    (10)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AXI_RD1_STATE_UNION
 �ṹ˵��  : AXI_RD1_STATE �Ĵ����ṹ���塣��ַƫ����:0x0350����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      axi_rd1_state_reg;
    struct
    {
        unsigned long  axi_rd1_ready  : 1;  /* bit[0]    : AXI��1��ǰ����Ӧ�ɽ�������ָʾ */
        unsigned long  reserved_0     : 3;  /* bit[1-3]  : ���� */
        unsigned long  axi_rd1_valid  : 1;  /* bit[4]    : AXI��1��ǰ����Ӧ������Чָʾ */
        unsigned long  reserved_1     : 3;  /* bit[5-7]  : ���� */
        unsigned long  axi_rd1_cur_id : 3;  /* bit[8-10] : AXI��1��ǰ����ӦID */
        unsigned long  reserved_2     : 21; /* bit[11-31]: ���� */
    } reg;
} BBPCOMM_AXI_RD1_STATE_UNION;
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_ready_START   (0)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_ready_END     (0)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_valid_START   (4)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_valid_END     (4)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_cur_id_START  (8)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_cur_id_END    (10)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_INT_EN_UNION
 �ṹ˵��  : BBPMST_ERROR_INT_EN �Ĵ����ṹ���塣��ַƫ����:0x0364����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_int_en_reg;
    struct
    {
        unsigned long  bbpmst_error_int_en : 1;  /* bit[0]   : BBPMST��д�����ж�ʹ�� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_INT_EN_UNION;
#define BBPCOMM_BBPMST_ERROR_INT_EN_bbpmst_error_int_en_START  (0)
#define BBPCOMM_BBPMST_ERROR_INT_EN_bbpmst_error_int_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_INT_MASK_UNION
 �ṹ˵��  : BBPMST_ERROR_INT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0368����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_int_mask_reg;
    struct
    {
        unsigned long  bbpmst_error_int_mask : 1;  /* bit[0]   : BBPMST��д�����ж������ź� */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_INT_MASK_UNION;
#define BBPCOMM_BBPMST_ERROR_INT_MASK_bbpmst_error_int_mask_START  (0)
#define BBPCOMM_BBPMST_ERROR_INT_MASK_bbpmst_error_int_mask_END    (0)


/***======================================================================***
                     (2/2) register_define_irm_ps
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : BBPCOMM_IRM_PS_RAM_CTRL_UNION
 �ṹ˵��  : IRM_PS_RAM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      irm_ps_ram_ctrl_reg;
    struct
    {
        unsigned long  irm_ps_ram_ctrl : 6;  /* bit[0-5] : ����irm_ps����ģʽѡ��Ӱ��irm_ps�ڲ�ʱ���л���ģʽ�л���Ĭ�϶�Ϊ0��.
                                                           6'b000001��GBBP1ģʽ��
                                                           6'b000110��UMTSģʽ��
                                                           6'b001000��LTEģʽ��
                                                           6'b010000��TDS-CDMAģʽ��
                                                           6'b100000��CDMAģʽ��
                                                           ע��GBBP1�̶�Ϊ������G0/U/L/T���� */
        unsigned long  reserved        : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_IRM_PS_RAM_CTRL_UNION;
#define BBPCOMM_IRM_PS_RAM_CTRL_irm_ps_ram_ctrl_START  (0)
#define BBPCOMM_IRM_PS_RAM_CTRL_irm_ps_ram_ctrl_END    (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_IRM_PS_GSM2_CTRL_UNION
 �ṹ˵��  : IRM_PS_GSM2_CTRL �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      irm_ps_gsm2_ctrl_reg;
    struct
    {
        unsigned long  irm_ps_gsm2_ctrl : 1;  /* bit[0]   : GBBP2��Ĭ��Ϊ0��1Ϊʹ�ܡ�
                                                            ע��GBBP2�̶�Ϊ������
                                                            V8R1��ʹ�á� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_IRM_PS_GSM2_CTRL_UNION;
#define BBPCOMM_IRM_PS_GSM2_CTRL_irm_ps_gsm2_ctrl_START  (0)
#define BBPCOMM_IRM_PS_GSM2_CTRL_irm_ps_gsm2_ctrl_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_IRM_PS_CLK_BYPASS_UNION
 �ṹ˵��  : IRM_PS_CLK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      irm_ps_clk_bypass_reg;
    struct
    {
        unsigned long  irm_ps_clk_bypass : 1;  /* bit[0]   : irm_psģ��ʱ���ſ���·���ء�Ĭ��Ϊ0��������ʱ���ſء�����1������·���ܣ�ʱ���ſ�ʧЧ�� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_IRM_PS_CLK_BYPASS_UNION;
#define BBPCOMM_IRM_PS_CLK_BYPASS_irm_ps_clk_bypass_START  (0)
#define BBPCOMM_IRM_PS_CLK_BYPASS_irm_ps_clk_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL0_TURBO_UNION
 �ṹ˵��  : MEM_CTRL0_TURBO �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x03501050�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl0_turbo_reg;
    struct
    {
        unsigned long  mem_ctrl_s_turbo      : 16; /* bit[0-15] : ���˿�ram��ʱ���ơ� */
        unsigned long  mem_ctrl_d_1w2r_turbo : 16; /* bit[16-31]: 1w2r˫�˿�ram��ʱ���ơ� */
    } reg;
} BBPCOMM_MEM_CTRL0_TURBO_UNION;
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_s_turbo_START       (0)
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_s_turbo_END         (15)
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_d_1w2r_turbo_START  (16)
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_d_1w2r_turbo_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL1_TURBO_UNION
 �ṹ˵��  : MEM_CTRL1_TURBO �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00700057�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl1_turbo_reg;
    struct
    {
        unsigned long  mem_ctrl_d_1rw2rw_turbo : 16; /* bit[0-15] : 1rw2rw˫�˿�ram��ʱ���ơ� */
        unsigned long  rom_ctrl_turbo          : 8;  /* bit[16-23]: rom��ʱ���ơ� */
        unsigned long  reserved                : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_MEM_CTRL1_TURBO_UNION;
#define BBPCOMM_MEM_CTRL1_TURBO_mem_ctrl_d_1rw2rw_turbo_START  (0)
#define BBPCOMM_MEM_CTRL1_TURBO_mem_ctrl_d_1rw2rw_turbo_END    (15)
#define BBPCOMM_MEM_CTRL1_TURBO_rom_ctrl_turbo_START           (16)
#define BBPCOMM_MEM_CTRL1_TURBO_rom_ctrl_turbo_END             (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL0_PS_UNION
 �ṹ˵��  : MEM_CTRL0_PS �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x03501050�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl0_ps_reg;
    struct
    {
        unsigned long  mem_ctrl_s_ps      : 16; /* bit[0-15] : ���˿�ram��ʱ���ơ� */
        unsigned long  mem_ctrl_d_1w2r_ps : 16; /* bit[16-31]: 1w2r˫�˿�ram��ʱ���ơ� */
    } reg;
} BBPCOMM_MEM_CTRL0_PS_UNION;
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_s_ps_START       (0)
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_s_ps_END         (15)
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_d_1w2r_ps_START  (16)
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_d_1w2r_ps_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL1_PS_UNION
 �ṹ˵��  : MEM_CTRL1_PS �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00700057�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl1_ps_reg;
    struct
    {
        unsigned long  mem_ctrl_d_1rw2rw_ps : 16; /* bit[0-15] : 1rw2rw˫�˿�ram��ʱ���ơ� */
        unsigned long  rom_ctrl_ps          : 8;  /* bit[16-23]: rom��ʱ���ơ� */
        unsigned long  reserved             : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_MEM_CTRL1_PS_UNION;
#define BBPCOMM_MEM_CTRL1_PS_mem_ctrl_d_1rw2rw_ps_START  (0)
#define BBPCOMM_MEM_CTRL1_PS_mem_ctrl_d_1rw2rw_ps_END    (15)
#define BBPCOMM_MEM_CTRL1_PS_rom_ctrl_ps_START           (16)
#define BBPCOMM_MEM_CTRL1_PS_rom_ctrl_ps_END             (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TUBO_CKG_UNION
 �ṹ˵��  : TUBO_CKG �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      tubo_ckg_reg;
    struct
    {
        unsigned long  tubo_ram_ckg_en : 16; /* bit[0-15] : turbo������ģ�鼶�ſ���·ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  tubo_mod_ckg_en : 16; /* bit[16-31]: turbo������ģ�鼶�ſ���·ʹ�ܣ��ߵ�ƽ��Ч�� */
    } reg;
} BBPCOMM_TUBO_CKG_UNION;
#define BBPCOMM_TUBO_CKG_tubo_ram_ckg_en_START  (0)
#define BBPCOMM_TUBO_CKG_tubo_ram_ckg_en_END    (15)
#define BBPCOMM_TUBO_CKG_tubo_mod_ckg_en_START  (16)
#define BBPCOMM_TUBO_CKG_tubo_mod_ckg_en_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_U_L_TYPE_UNION
 �ṹ˵��  : U_L_TYPE �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      u_l_type_reg;
    struct
    {
        unsigned long  u_l_type : 1;  /* bit[0]   : Turbo����ģʽѡ���źţ�Lģ����
                                                    {U_C_TYPE, U_T_TYPE, U_L_TYPE}��������bitƴ����Ϻ������£�
                                                    3'b000��Uģ��
                                                    3'b001��Lģ��
                                                    3'b010��Tģ��
                                                    3'b100��Cģ��
                                                    �����������塣 */
        unsigned long  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_U_L_TYPE_UNION;
#define BBPCOMM_U_L_TYPE_u_l_type_START  (0)
#define BBPCOMM_U_L_TYPE_u_l_type_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_U_T_TYPE_UNION
 �ṹ˵��  : U_T_TYPE �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      u_t_type_reg;
    struct
    {
        unsigned long  u_t_type : 1;  /* bit[0]   : Turbo����ģʽѡ���źţ�Tģ����
                                                    {U_C_TYPE, U_T_TYPE, U_L_TYPE}��������bitƴ����Ϻ������£�
                                                    3'b000��Uģ��
                                                    3'b001��Lģ��
                                                    3'b010��Tģ��
                                                    3'b100��Cģ��
                                                    �����������塣 */
        unsigned long  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_U_T_TYPE_UNION;
#define BBPCOMM_U_T_TYPE_u_t_type_START  (0)
#define BBPCOMM_U_T_TYPE_u_t_type_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_U_C_TYPE_UNION
 �ṹ˵��  : U_C_TYPE �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      u_c_type_reg;
    struct
    {
        unsigned long  u_c_type : 1;  /* bit[0]   : Turbo����ģʽѡ���źţ�Cģ����
                                                    {U_C_TYPE, U_T_TYPE, U_L_TYPE}��������bitƴ����Ϻ������£�
                                                    3'b000��Uģ��
                                                    3'b001��Lģ��
                                                    3'b010��Tģ��
                                                    3'b100��Cģ��
                                                    �����������塣 */
        unsigned long  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_U_C_TYPE_UNION;
#define BBPCOMM_U_C_TYPE_u_c_type_START  (0)
#define BBPCOMM_U_C_TYPE_u_c_type_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_SOC_AP_OCCUPY_GRP_UNION
 �ṹ˵��  : SOC_AP_OCCUPY_GRP �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      soc_ap_occupy_grp_reg;
    struct
    {
        unsigned long  soc_ap_occupy_grp1 : 2;  /* bit[0-1]  :  */
        unsigned long  soc_ap_occupy_grp2 : 2;  /* bit[2-3]  :  */
        unsigned long  soc_ap_occupy_grp3 : 2;  /* bit[4-5]  :  */
        unsigned long  soc_ap_occupy_grp4 : 2;  /* bit[6-7]  :  */
        unsigned long  soc_ap_occupy_grp5 : 2;  /* bit[8-9]  :  */
        unsigned long  soc_ap_occupy_grp6 : 2;  /* bit[10-11]:  */
        unsigned long  soc_ap_occupy_grp7 : 2;  /* bit[12-13]:  */
        unsigned long  soc_ap_occupy_grp8 : 2;  /* bit[14-15]: SOC AP���ø�ps ram��occupy�����źš� */
        unsigned long  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_SOC_AP_OCCUPY_GRP_UNION;
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp1_START  (0)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp1_END    (1)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp2_START  (2)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp2_END    (3)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp3_START  (4)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp3_END    (5)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp4_START  (6)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp4_END    (7)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp5_START  (8)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp5_END    (9)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp6_START  (10)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp6_END    (11)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp7_START  (12)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp7_END    (13)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp8_START  (14)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp8_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_PS_W_SDR_EN_UNION
 �ṹ˵��  : PS_W_SDR_EN �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ps_w_sdr_en_reg;
    struct
    {
        unsigned long  ps_w_sdr_en          : 1;  /* bit[0]   : W SDRģʽ����ʹ�ܡ� */
        unsigned long  ps_w_sdr_dec_clk_sel : 1;  /* bit[1]   : W SDRģʽ������ʱ��ѡ��0���������122mʱ�ӣ�1���������245mʱ�ӡ� */
        unsigned long  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_PS_W_SDR_EN_UNION;
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_en_START           (0)
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_en_END             (0)
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_dec_clk_sel_START  (1)
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_dec_clk_sel_END    (1)




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

#endif /* end of bbp_comm_interface.h */
