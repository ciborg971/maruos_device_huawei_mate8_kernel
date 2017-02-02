

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_IPF_INTERFACE_H__
#define __SOC_IPF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) IPF
 ****************************************************************************/
/* �Ĵ���˵����IPF��λ���ƼĴ���
   λ����UNION�ṹ:  SOC_IPF_SRST_UNION */
#define SOC_IPF_SRST_ADDR(base)                       ((base) + (0x0000))

/* �Ĵ���˵����IPF��λ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_SRST_STATE_UNION */
#define SOC_IPF_SRST_STATE_ADDR(base)                 ((base) + (0x0004))

/* �Ĵ���˵����IPF ͨ��ʹ�����üĴ���
   λ����UNION�ṹ:  SOC_IPF_CH_EN_UNION */
#define SOC_IPF_CH_EN_ADDR(base)                      ((base) + (0x0008))

/* �Ĵ���˵����IPF ͨ��ʹ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_EN_STATE_UNION */
#define SOC_IPF_EN_STATE_ADDR(base)                   ((base) + (0x000C))

/* �Ĵ���˵����IPFʱ���ſ����üĴ���
   λ����UNION�ṹ:  SOC_IPF_GATE_UNION */
#define SOC_IPF_GATE_ADDR(base)                       ((base) + (0x0010))

/* �Ĵ���˵����IPFȫ�ֿ������üĴ���
   λ����UNION�ṹ:  SOC_IPF_CTRL_UNION */
#define SOC_IPF_CTRL_ADDR(base)                       ((base) + (0x0014))

/* �Ĵ���˵����IPF DMA���ƼĴ���0
   λ����UNION�ṹ:  SOC_IPF_DMA_CTRL0_UNION */
#define SOC_IPF_DMA_CTRL0_ADDR(base)                  ((base) + (0x0018))

/* �Ĵ���˵����IPF DMA���ƼĴ���1
   λ����UNION�ṹ:  SOC_IPF_DMA_CTRL1_UNION */
#define SOC_IPF_DMA_CTRL1_ADDR(base)                  ((base) + (0x001C))

/* �Ĵ���˵�����ж��ϱ��Ĵ���0
   λ����UNION�ṹ:  SOC_IPF_INT0_UNION */
#define SOC_IPF_INT0_ADDR(base)                       ((base) + (0x0030))

/* �Ĵ���˵�����ж��ϱ��Ĵ���1
   λ����UNION�ṹ:  SOC_IPF_INT1_UNION */
#define SOC_IPF_INT1_ADDR(base)                       ((base) + (0x0034))

/* �Ĵ���˵�����ж����μĴ���0
   λ����UNION�ṹ:  SOC_IPF_INT_MASK0_UNION */
#define SOC_IPF_INT_MASK0_ADDR(base)                  ((base) + (0x0038))

/* �Ĵ���˵�����ж����μĴ���1
   λ����UNION�ṹ:  SOC_IPF_INT_MASK1_UNION */
#define SOC_IPF_INT_MASK1_ADDR(base)                  ((base) + (0x003C))

/* �Ĵ���˵�����ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_INT_STATE_UNION */
#define SOC_IPF_INT_STATE_ADDR(base)                  ((base) + (0x0040))

/* �Ĵ���˵������ʱ���üĴ���
   λ����UNION�ṹ:  SOC_IPF_TIME_OUT_UNION */
#define SOC_IPF_TIME_OUT_ADDR(base)                   ((base) + (0x0044))

/* �Ĵ���˵�����������üĴ���
   λ����UNION�ṹ:  SOC_IPF_PKT_LEN_UNION */
#define SOC_IPF_PKT_LEN_ADDR(base)                    ((base) + (0x0048))

/* �Ĵ���˵����IPF��������ʼ�������üĴ���
   λ����UNION�ṹ:  SOC_IPF_FILTER_ZERO_INDEX_UNION */
#define SOC_IPF_FILTER_ZERO_INDEX_ADDR(base)          ((base) + (0x0070))

/* �Ĵ���˵������չ����������ַ���üĴ���
   λ����UNION�ṹ:  SOC_IPF_EF_BADDR_UNION */
#define SOC_IPF_EF_BADDR_ADDR(base)                   ((base) + (0x0074))

/* �Ĵ���˵�����������˱���������
   λ����UNION�ṹ:  SOC_IPF_BFLT_INDEX_UNION */
#define SOC_IPF_BFLT_INDEX_ADDR(base)                 ((base) + (0x0078))

/* �Ĵ���˵���������������澯
   λ����UNION�ṹ:  SOC_IPF_FLT_CHAIN_LOOP_UNION */
#define SOC_IPF_FLT_CHAIN_LOOP_ADDR(base)             ((base) + (0x007C))

/* �Ĵ���˵����������local address���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_LOCAL_ADDR0_UNION */
#define SOC_IPF_FLT_LOCAL_ADDR0_ADDR(base)            ((base) + (0x0090))

/* �Ĵ���˵����������local address���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_LOCAL_ADDR1_UNION */
#define SOC_IPF_FLT_LOCAL_ADDR1_ADDR(base)            ((base) + (0x0094))

/* �Ĵ���˵����������local address���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_LOCAL_ADDR2_UNION */
#define SOC_IPF_FLT_LOCAL_ADDR2_ADDR(base)            ((base) + (0x0098))

/* �Ĵ���˵����������local address���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_LOCAL_ADDR3_UNION */
#define SOC_IPF_FLT_LOCAL_ADDR3_ADDR(base)            ((base) + (0x009C))

/* �Ĵ���˵����������remote address���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_REMOTE_ADDR0_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR0_ADDR(base)           ((base) + (0x00A0))

/* �Ĵ���˵����������remote address���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_REMOTE_ADDR1_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR1_ADDR(base)           ((base) + (0x00A4))

/* �Ĵ���˵����������remote address���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_REMOTE_ADDR2_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR2_ADDR(base)           ((base) + (0x00A8))

/* �Ĵ���˵����������remote address���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_REMOTE_ADDR3_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR3_ADDR(base)           ((base) + (0x00AC))

/* �Ĵ���˵����������remote address���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_REMOTE_ADDR0_MASK_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR0_MASK_ADDR(base)      ((base) + (0x00B0))

/* �Ĵ���˵����������remote address���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_REMOTE_ADDR1_MASK_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR1_MASK_ADDR(base)      ((base) + (0x00B4))

/* �Ĵ���˵����������remote address���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_REMOTE_ADDR2_MASK_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR2_MASK_ADDR(base)      ((base) + (0x00B8))

/* �Ĵ���˵����������remote address���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_REMOTE_ADDR3_MASK_UNION */
#define SOC_IPF_FLT_REMOTE_ADDR3_MASK_ADDR(base)      ((base) + (0x00BC))

/* �Ĵ���˵�������˱�LOCAL PORT�������üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_LOCAL_PORT_UNION */
#define SOC_IPF_FLT_LOCAL_PORT_ADDR(base)             ((base) + (0x00C0))

/* �Ĵ���˵�������˱�REMOTE PORT�������üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_REMOTE_PORT_UNION */
#define SOC_IPF_FLT_REMOTE_PORT_ADDR(base)            ((base) + (0x00C4))

/* �Ĵ���˵�������˱�ҵ��ȼ������üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_TRAFFIC_CLASS_UNION */
#define SOC_IPF_FLT_TRAFFIC_CLASS_ADDR(base)          ((base) + (0x00C8))

/* �Ĵ���˵����������local address mask�����üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_LADD_MASK_UNION */
#define SOC_IPF_FLT_LADD_MASK_ADDR(base)              ((base) + (0x00CC))

/* �Ĵ���˵����������Э�����������üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_NEXT_HEADER_UNION */
#define SOC_IPF_FLT_NEXT_HEADER_ADDR(base)            ((base) + (0x00D0))

/* �Ĵ���˵��������������ǩ�����üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_FLOW_LABEL_UNION */
#define SOC_IPF_FLT_FLOW_LABEL_ADDR(base)             ((base) + (0x00D4))

/* �Ĵ���˵����������ICMP���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_ICMP_UNION */
#define SOC_IPF_FLT_ICMP_ADDR(base)                   ((base) + (0x00D8))

/* �Ĵ���˵�������������������üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_CHAIN_UNION */
#define SOC_IPF_FLT_CHAIN_ADDR(base)                  ((base) + (0x00DC))

/* �Ĵ���˵����������SPI���üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_SPI_UNION */
#define SOC_IPF_FLT_SPI_ADDR(base)                    ((base) + (0x00E0))

/* �Ĵ���˵��������������������üĴ���
   λ����UNION�ṹ:  SOC_IPF_FLT_RULE_CTRL_UNION */
#define SOC_IPF_FLT_RULE_CTRL_ADDR(base)              ((base) + (0x00E4))

/* �Ĵ���˵��������ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_IPF_CH0_CTRL_UNION */
#define SOC_IPF_CH0_CTRL_ADDR(base)                   ((base) + (0x0100))

/* �Ĵ���˵��������ͨ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH0_STATE_UNION */
#define SOC_IPF_CH0_STATE_ADDR(base)                  ((base) + (0x0104))

/* �Ĵ���˵��������ͨ��BDQ��ʼ��ַ
   λ����UNION�ṹ:  SOC_IPF_CH0_BDQ_BADDR_UNION */
#define SOC_IPF_CH0_BDQ_BADDR_ADDR(base)              ((base) + (0x0108))

/* �Ĵ���˵��������ͨ��BDQ���
   λ����UNION�ṹ:  SOC_IPF_CH0_BDQ_SIZE_UNION */
#define SOC_IPF_CH0_BDQ_SIZE_ADDR(base)               ((base) + (0x010C))

/* �Ĵ���˵��������ͨ��BDQдָ��
   λ����UNION�ṹ:  SOC_IPF_CH0_BDQ_WPTR_UNION */
#define SOC_IPF_CH0_BDQ_WPTR_ADDR(base)               ((base) + (0x0110))

/* �Ĵ���˵��������ͨ��BDQ��ָ��
   λ����UNION�ṹ:  SOC_IPF_CH0_BDQ_RPTR_UNION */
#define SOC_IPF_CH0_BDQ_RPTR_ADDR(base)               ((base) + (0x0114))

/* �Ĵ���˵��������ͨ��BDQд��ַ
   λ����UNION�ṹ:  SOC_IPF_CH0_BDQ_WADDR_UNION */
#define SOC_IPF_CH0_BDQ_WADDR_ADDR(base)              ((base) + (0x0118))

/* �Ĵ���˵��������ͨ��BDQ����ַ
   λ����UNION�ṹ:  SOC_IPF_CH0_BDQ_RADDR_UNION */
#define SOC_IPF_CH0_BDQ_RADDR_ADDR(base)              ((base) + (0x011C))

/* �Ĵ���˵��������ͨ��RDQ��ʼ��ַ
   λ����UNION�ṹ:  SOC_IPF_CH0_RDQ_BADDR_UNION */
#define SOC_IPF_CH0_RDQ_BADDR_ADDR(base)              ((base) + (0x0120))

/* �Ĵ���˵��������ͨ��RDQ���
   λ����UNION�ṹ:  SOC_IPF_CH0_RDQ_SIZE_UNION */
#define SOC_IPF_CH0_RDQ_SIZE_ADDR(base)               ((base) + (0x0124))

/* �Ĵ���˵��������ͨ��RDQдָ��
   λ����UNION�ṹ:  SOC_IPF_CH0_RDQ_WPTR_UNION */
#define SOC_IPF_CH0_RDQ_WPTR_ADDR(base)               ((base) + (0x0128))

/* �Ĵ���˵��������ͨ��RDQ��ָ��
   λ����UNION�ṹ:  SOC_IPF_CH0_RDQ_RPTR_UNION */
#define SOC_IPF_CH0_RDQ_RPTR_ADDR(base)               ((base) + (0x012C))

/* �Ĵ���˵��������ͨ��RDQд��ַ
   λ����UNION�ṹ:  SOC_IPF_CH0_RDQ_WADDR_UNION */
#define SOC_IPF_CH0_RDQ_WADDR_ADDR(base)              ((base) + (0x0130))

/* �Ĵ���˵��������ͨ��RDQ����ַ
   λ����UNION�ṹ:  SOC_IPF_CH0_RDQ_RADDR_UNION */
#define SOC_IPF_CH0_RDQ_RADDR_ADDR(base)              ((base) + (0x0134))

/* �Ĵ���˵��������ͨ���������ָʾ�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH0_DQ_DEPTH_UNION */
#define SOC_IPF_CH0_DQ_DEPTH_ADDR(base)               ((base) + (0x0138))

/* �Ĵ���˵��������ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_IPF_CH1_CTRL_UNION */
#define SOC_IPF_CH1_CTRL_ADDR(base)                   ((base) + (0x0150))

/* �Ĵ���˵��������ͨ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH1_STATE_UNION */
#define SOC_IPF_CH1_STATE_ADDR(base)                  ((base) + (0x0154))

/* �Ĵ���˵��������ͨ��BDQ��ʼ��ַ
   λ����UNION�ṹ:  SOC_IPF_CH1_BDQ_BADDR_UNION */
#define SOC_IPF_CH1_BDQ_BADDR_ADDR(base)              ((base) + (0x0158))

/* �Ĵ���˵��������ͨ��BDQ���
   λ����UNION�ṹ:  SOC_IPF_CH1_BDQ_SIZE_UNION */
#define SOC_IPF_CH1_BDQ_SIZE_ADDR(base)               ((base) + (0x015C))

/* �Ĵ���˵��������ͨ��BDQдָ��
   λ����UNION�ṹ:  SOC_IPF_CH1_BDQ_WPTR_UNION */
#define SOC_IPF_CH1_BDQ_WPTR_ADDR(base)               ((base) + (0x0160))

/* �Ĵ���˵��������ͨ��BDQ��ָ��
   λ����UNION�ṹ:  SOC_IPF_CH1_BDQ_RPTR_UNION */
#define SOC_IPF_CH1_BDQ_RPTR_ADDR(base)               ((base) + (0x0164))

/* �Ĵ���˵��������ͨ��BDQд��ַ
   λ����UNION�ṹ:  SOC_IPF_CH1_BDQ_WADDR_UNION */
#define SOC_IPF_CH1_BDQ_WADDR_ADDR(base)              ((base) + (0x0168))

/* �Ĵ���˵��������ͨ��BDQ����ַ
   λ����UNION�ṹ:  SOC_IPF_CH1_BDQ_RADDR_UNION */
#define SOC_IPF_CH1_BDQ_RADDR_ADDR(base)              ((base) + (0x016C))

/* �Ĵ���˵��������ͨ��RDQ��ʼ��ַ
   λ����UNION�ṹ:  SOC_IPF_CH1_RDQ_BADDR_UNION */
#define SOC_IPF_CH1_RDQ_BADDR_ADDR(base)              ((base) + (0x0170))

/* �Ĵ���˵��������ͨ��RDQ���
   λ����UNION�ṹ:  SOC_IPF_CH1_RDQ_SIZE_UNION */
#define SOC_IPF_CH1_RDQ_SIZE_ADDR(base)               ((base) + (0x0174))

/* �Ĵ���˵��������ͨ��RDQдָ��
   λ����UNION�ṹ:  SOC_IPF_CH1_RDQ_WPTR_UNION */
#define SOC_IPF_CH1_RDQ_WPTR_ADDR(base)               ((base) + (0x0178))

/* �Ĵ���˵��������ͨ��RDQ��ָ��
   λ����UNION�ṹ:  SOC_IPF_CH1_RDQ_RPTR_UNION */
#define SOC_IPF_CH1_RDQ_RPTR_ADDR(base)               ((base) + (0x017C))

/* �Ĵ���˵��������ͨ��RDQд��ַ
   λ����UNION�ṹ:  SOC_IPF_CH1_RDQ_WADDR_UNION */
#define SOC_IPF_CH1_RDQ_WADDR_ADDR(base)              ((base) + (0x0180))

/* �Ĵ���˵��������ͨ��RDQ����ַ
   λ����UNION�ṹ:  SOC_IPF_CH1_RDQ_RADDR_UNION */
#define SOC_IPF_CH1_RDQ_RADDR_ADDR(base)              ((base) + (0x0184))

/* �Ĵ���˵��������ͨ���������ָʾ�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH1_DQ_DEPTH_UNION */
#define SOC_IPF_CH1_DQ_DEPTH_ADDR(base)               ((base) + (0x0188))

/* �Ĵ���˵��������ͨ��ADQ���ƼĴ���
   λ����UNION�ṹ:  SOC_IPF_CH0_ADQ_CTRL_UNION */
#define SOC_IPF_CH0_ADQ_CTRL_ADDR(base)               ((base) + (0x0204))

/* �Ĵ���˵��������ͨ��ADQ0��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH0_ADQ0_BASE_UNION */
#define SOC_IPF_CH0_ADQ0_BASE_ADDR(base)              ((base) + (0x0210))

/* �Ĵ���˵��������ͨ��ADQ0״̬�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH0_ADQ0_STAT_UNION */
#define SOC_IPF_CH0_ADQ0_STAT_ADDR(base)              ((base) + (0x0214))

/* �Ĵ���˵��������ͨ��ADQ0дָ��Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH0_ADQ0_WPTR_UNION */
#define SOC_IPF_CH0_ADQ0_WPTR_ADDR(base)              ((base) + (0x0218))

/* �Ĵ���˵��������ͨ��ADQ0��ָ��Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH0_ADQ0_RPTR_UNION */
#define SOC_IPF_CH0_ADQ0_RPTR_ADDR(base)              ((base) + (0x021C))

/* �Ĵ���˵��������ͨ��ADQ1��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH0_ADQ1_BASE_UNION */
#define SOC_IPF_CH0_ADQ1_BASE_ADDR(base)              ((base) + (0x0220))

/* �Ĵ���˵��������ͨ��ADQ1״̬�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH0_ADQ1_STAT_UNION */
#define SOC_IPF_CH0_ADQ1_STAT_ADDR(base)              ((base) + (0x0224))

/* �Ĵ���˵��������ͨ��ADQ1дָ��Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH0_ADQ1_WPTR_UNION */
#define SOC_IPF_CH0_ADQ1_WPTR_ADDR(base)              ((base) + (0x0228))

/* �Ĵ���˵��������ͨ��ADQ1��ָ��Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH0_ADQ1_RPTR_UNION */
#define SOC_IPF_CH0_ADQ1_RPTR_ADDR(base)              ((base) + (0x022C))

/* �Ĵ���˵��������ͨ��ADQ���ƼĴ���
   λ����UNION�ṹ:  SOC_IPF_CH1_ADQ_CTRL_UNION */
#define SOC_IPF_CH1_ADQ_CTRL_ADDR(base)               ((base) + (0x0284))

/* �Ĵ���˵��������ͨ��ADQ0��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH1_ADQ0_BASE_UNION */
#define SOC_IPF_CH1_ADQ0_BASE_ADDR(base)              ((base) + (0x0290))

/* �Ĵ���˵��������ͨ��ADQ0״̬�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH1_ADQ0_STAT_UNION */
#define SOC_IPF_CH1_ADQ0_STAT_ADDR(base)              ((base) + (0x0294))

/* �Ĵ���˵��������ͨ��ADQ0дָ��Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH1_ADQ0_WPTR_UNION */
#define SOC_IPF_CH1_ADQ0_WPTR_ADDR(base)              ((base) + (0x0298))

/* �Ĵ���˵��������ͨ��ADQ0��ָ��Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH1_ADQ0_RPTR_UNION */
#define SOC_IPF_CH1_ADQ0_RPTR_ADDR(base)              ((base) + (0x029C))

/* �Ĵ���˵��������ͨ��ADQ1��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH1_ADQ1_BASE_UNION */
#define SOC_IPF_CH1_ADQ1_BASE_ADDR(base)              ((base) + (0x02A0))

/* �Ĵ���˵��������ͨ��ADQ1״̬�Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH1_ADQ1_STAT_UNION */
#define SOC_IPF_CH1_ADQ1_STAT_ADDR(base)              ((base) + (0x02A4))

/* �Ĵ���˵��������ͨ��ADQ1дָ��Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH1_ADQ1_WPTR_UNION */
#define SOC_IPF_CH1_ADQ1_WPTR_ADDR(base)              ((base) + (0x02A8))

/* �Ĵ���˵��������ͨ��ADQ1��ָ��Ĵ���
   λ����UNION�ṹ:  SOC_IPF_CH1_ADQ1_RPTR_UNION */
#define SOC_IPF_CH1_ADQ1_RPTR_ADDR(base)              ((base) + (0x02AC))





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
                     (1/1) IPF
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_IPF_SRST_UNION
 �ṹ˵��  : SRST �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: IPF��λ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipf_srst : 1;  /* bit[0]   : ȫ����λ�Ĵ�����
                                                   0������λ��
                                                   1����λ��
                                                   �ߵ�ƽ��Ч��ֻ��λ�߼�����λ���üĴ���.��λ���ܲ���������Ч���ɸ�λ״̬�Ĵ���ָʾ��λ�Ƿ�ɹ�����λ�ɹ���д0�����λ�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_IPF_SRST_UNION;
#endif
#define SOC_IPF_SRST_ipf_srst_START  (0)
#define SOC_IPF_SRST_ipf_srst_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IPF_SRST_STATE_UNION
 �ṹ˵��  : SRST_STATE �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: IPF��λ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipf_srst_state : 1;  /* bit[0]   : ��λ״ָ̬ʾ�Ĵ�����
                                                         0��δ���ڸ�λ״̬��
                                                         1�����ڸ�λ״̬����ʾ��λ�ɹ���
                                                         ���߼����ڸ�λ״̬����ɽ����λ�� */
        unsigned int  reserved       : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_IPF_SRST_STATE_UNION;
#endif
#define SOC_IPF_SRST_STATE_ipf_srst_state_START  (0)
#define SOC_IPF_SRST_STATE_ipf_srst_state_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH_EN_UNION
 �ṹ˵��  : CH_EN �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: IPF ͨ��ʹ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_en    : 1;  /* bit[0]   : ULͨ��ʹ�����üĴ���.
                                                   0:ͨ���ر�
                                                   1:ͨ��ʹ��
                                                   д1ʹ��ͨ����������Ч.д0�ر�ͨ��,����ʱͨ��busy�����������رգ�ֱ��ͨ��idle����ܹر�. */
        unsigned int  dl_en    : 1;  /* bit[1]   : DLͨ��ʹ�����üĴ���.
                                                   0:ͨ���ر�
                                                   1:ͨ��ʹ��
                                                   д1ʹ��ͨ����������Ч.д0�ر�ͨ��,����ʱͨ��busy�����������رգ�ֱ��ͨ��idle����ܹر�. */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IPF_CH_EN_UNION;
#endif
#define SOC_IPF_CH_EN_ul_en_START     (0)
#define SOC_IPF_CH_EN_ul_en_END       (0)
#define SOC_IPF_CH_EN_dl_en_START     (1)
#define SOC_IPF_CH_EN_dl_en_END       (1)


/*****************************************************************************
 �ṹ��    : SOC_IPF_EN_STATE_UNION
 �ṹ˵��  : EN_STATE �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: IPF ͨ��ʹ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_en_state : 1;  /* bit[0]   : ULͨ��ʹ��״̬�Ĵ���.
                                                      0:ͨ���ѹر�
                                                      1:ͨ���� */
        unsigned int  dl_en_state : 1;  /* bit[1]   : DLͨ��ʹ��״̬�Ĵ���.
                                                      0:ͨ���ѹر�
                                                      1:ͨ���� */
        unsigned int  reserved    : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IPF_EN_STATE_UNION;
#endif
#define SOC_IPF_EN_STATE_ul_en_state_START  (0)
#define SOC_IPF_EN_STATE_ul_en_state_END    (0)
#define SOC_IPF_EN_STATE_dl_en_state_START  (1)
#define SOC_IPF_EN_STATE_dl_en_state_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IPF_GATE_UNION
 �ṹ˵��  : GATE �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: IPFʱ���ſ����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipf_sysclk_sel0 : 1;  /* bit[0]    : ipfģ��ϵͳʱ���ſ�ʹ�ܡ�
                                                           0:ʱ�ӳ���
                                                           1:�Զ��ſ�  */
        unsigned int  ipf_sysclk_sel1 : 1;  /* bit[1]    : ipfģ��ϵͳʱ���ſ�ʹ�ܡ�
                                                           0:ʱ�ӳ���
                                                           1:�Զ��ſ�  */
        unsigned int  ipf_busclk_sel  : 1;  /* bit[2]    : ipfģ������ʱ���ſ�ʹ�ܡ�
                                                           0:ʱ�ӳ���
                                                           1:�Զ��ſ�  */
        unsigned int  reserved_0      : 5;  /* bit[3-7]  : ������ */
        unsigned int  ipf_ram0clk_sel : 1;  /* bit[8]    : ipfģ�鵥��RAMʱ���ſ�ʹ�ܡ�
                                                           0:ʱ�ӳ���
                                                           1:�Զ��ſ� */
        unsigned int  ipf_ram1clk_sel : 1;  /* bit[9]    : ipfģ��˫��RAMʱ���ſ�ʹ�ܡ�
                                                           0:ʱ�ӳ���
                                                           1:�Զ��ſ� */
        unsigned int  reserved_1      : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_IPF_GATE_UNION;
#endif
#define SOC_IPF_GATE_ipf_sysclk_sel0_START  (0)
#define SOC_IPF_GATE_ipf_sysclk_sel0_END    (0)
#define SOC_IPF_GATE_ipf_sysclk_sel1_START  (1)
#define SOC_IPF_GATE_ipf_sysclk_sel1_END    (1)
#define SOC_IPF_GATE_ipf_busclk_sel_START   (2)
#define SOC_IPF_GATE_ipf_busclk_sel_END     (2)
#define SOC_IPF_GATE_ipf_ram0clk_sel_START  (8)
#define SOC_IPF_GATE_ipf_ram0clk_sel_END    (8)
#define SOC_IPF_GATE_ipf_ram1clk_sel_START  (9)
#define SOC_IPF_GATE_ipf_ram1clk_sel_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CTRL_UNION
 �ṹ˵��  : CTRL �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: IPFȫ�ֿ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filter_seq       : 1;  /* bit[0]    : ����������˳��ָʾ�Ĵ���.
                                                            0:����������˳������
                                                            1:������������������ */
        unsigned int  flt_addr_reverse : 1;  /* bit[1]    : 0����ʾ�������еĵ�ַ�Ĵ������������
                                                            1����ʾ�������еĵ�ַ�Ĵ�����С������ */
        unsigned int  sp_cfg           : 1;  /* bit[2]    : 0:SPģʽ��DL���ȼ���
                                                            1;SPģʽ��UL���ȼ��� */
        unsigned int  sp_wrr_sel       : 1;  /* bit[3]    : 0:WRRģʽ����
                                                            1;SPģʽ���� */
        unsigned int  max_burst_len    : 2;  /* bit[4-5]  : BURST��󳤶����üĴ���
                                                            2'b00:BURST16
                                                            2'b01:BURST8
                                                            2'b10,2'b11:BURST4 */
        unsigned int  ipv6_nh_sel      : 1;  /* bit[6]    : IPV6 ����ƥ��NextNeaderѡ������ź�
                                                            0:�������ϲ㱨�Ķ�Ӧ��NextHeader��ʶ���NextHeader(ע��AH��ESP����ʱNextHeader��Ӧ��ʱѡ��֮���NextHeader)
                                                            1:����ͷ�е�NextNeader */
        unsigned int  ah_esp_sel       : 1;  /* bit[7]    : ���AH��ESPͬʱ�����Ҿ�����Ϊ����ƥ��,SPIѡ������ź�
                                                            0:ѡ��ESP��Ӧ��SPI����ƥ��
                                                            1:ѡ��AH��Ӧ��SPI����ƥ�� */
        unsigned int  ah_disable       : 1;  /* bit[8]    : AH SPI�Ƿ����ƥ������ź�
                                                            0:����ƥ��
                                                            1:������ƥ�� */
        unsigned int  esp_disable      : 1;  /* bit[9]    : ESP SPI�Ƿ����ƥ������ź�
                                                            0:����ƥ��
                                                            1:������ƥ�� */
        unsigned int  mfc_en           : 1;  /* bit[10]   : ��ͨ�����������ʹ��
                                                            0��ÿ��ͨ��ֻ��֧��һ����������������ͷ������̬���ã�
                                                            1��ÿ��ͨ�����֧��8����������������ͷ������BD��̬���ã� */
        unsigned int  mm_en            : 1;  /* bit[11]   : ��ͨ����̬ģʽʹ��
                                                            0��ÿ��ͨ��ģʽ��ͨ�����ƼĴ�����̬���ã�
                                                            1��ÿ��ͨ��ģʽ��BD��mode��־��̬���ã� */
        unsigned int  add_rep          : 1;  /* bit[12]   : ����ͨ��AD�ϱ�ѡ��
                                                            0����ʾRD�ϱ�Ŀ�ĵ�ַʹ��AD�ĵڶ����֣�
                                                            1����ʾRD�ϱ�Ŀ�ĵ�ַʹ��AD�ĵ�һ���֣� */
        unsigned int  reserved         : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_IPF_CTRL_UNION;
#endif
#define SOC_IPF_CTRL_filter_seq_START        (0)
#define SOC_IPF_CTRL_filter_seq_END          (0)
#define SOC_IPF_CTRL_flt_addr_reverse_START  (1)
#define SOC_IPF_CTRL_flt_addr_reverse_END    (1)
#define SOC_IPF_CTRL_sp_cfg_START            (2)
#define SOC_IPF_CTRL_sp_cfg_END              (2)
#define SOC_IPF_CTRL_sp_wrr_sel_START        (3)
#define SOC_IPF_CTRL_sp_wrr_sel_END          (3)
#define SOC_IPF_CTRL_max_burst_len_START     (4)
#define SOC_IPF_CTRL_max_burst_len_END       (5)
#define SOC_IPF_CTRL_ipv6_nh_sel_START       (6)
#define SOC_IPF_CTRL_ipv6_nh_sel_END         (6)
#define SOC_IPF_CTRL_ah_esp_sel_START        (7)
#define SOC_IPF_CTRL_ah_esp_sel_END          (7)
#define SOC_IPF_CTRL_ah_disable_START        (8)
#define SOC_IPF_CTRL_ah_disable_END          (8)
#define SOC_IPF_CTRL_esp_disable_START       (9)
#define SOC_IPF_CTRL_esp_disable_END         (9)
#define SOC_IPF_CTRL_mfc_en_START            (10)
#define SOC_IPF_CTRL_mfc_en_END              (10)
#define SOC_IPF_CTRL_mm_en_START             (11)
#define SOC_IPF_CTRL_mm_en_END               (11)
#define SOC_IPF_CTRL_add_rep_START           (12)
#define SOC_IPF_CTRL_add_rep_END             (12)


/*****************************************************************************
 �ṹ��    : SOC_IPF_DMA_CTRL0_UNION
 �ṹ˵��  : DMA_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x0FBE1010�����:32
 �Ĵ���˵��: IPF DMA���ƼĴ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ipf_wr_ch0_id  : 4;  /* bit[0-3]  : AXIдͨ��0 ID */
        unsigned int  ipf_wr_ch1_id  : 4;  /* bit[4-7]  : AXIдͨ��1 ID */
        unsigned int  ipf_rd_ch0_id  : 4;  /* bit[8-11] : AXI��ͨ��0 ID */
        unsigned int  ipf_rd_ch1_id  : 4;  /* bit[12-15]: AXI��ͨ��1 ID */
        unsigned int  ipf_wr_ch0_pri : 3;  /* bit[16-18]: AXIдͨ��0���ȼ� */
        unsigned int  reserved_0     : 1;  /* bit[19]   : ���� */
        unsigned int  ipf_wr_ch1_pri : 3;  /* bit[20-22]: AXIдͨ��1���ȼ� */
        unsigned int  reserved_1     : 1;  /* bit[23]   : ���� */
        unsigned int  ipf_rd_ch0_pri : 3;  /* bit[24-26]: AXI��ͨ��0���ȼ� */
        unsigned int  reserved_2     : 1;  /* bit[27]   : ���� */
        unsigned int  ipf_rd_ch1_pri : 3;  /* bit[28-30]: AXI��ͨ��1���ȼ� */
        unsigned int  reserved_3     : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_IPF_DMA_CTRL0_UNION;
#endif
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch0_id_START   (0)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch0_id_END     (3)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch1_id_START   (4)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch1_id_END     (7)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch0_id_START   (8)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch0_id_END     (11)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch1_id_START   (12)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch1_id_END     (15)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch0_pri_START  (16)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch0_pri_END    (18)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch1_pri_START  (20)
#define SOC_IPF_DMA_CTRL0_ipf_wr_ch1_pri_END    (22)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch0_pri_START  (24)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch0_pri_END    (26)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch1_pri_START  (28)
#define SOC_IPF_DMA_CTRL0_ipf_rd_ch1_pri_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_IPF_DMA_CTRL1_UNION
 �ṹ˵��  : DMA_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: IPF DMA���ƼĴ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  outstanding_w : 1;  /* bit[0]   : дͨ��outstandingʹ�ܡ�
                                                        0��AXI masterû��дoutstanding������
                                                        1��AXI master��дoutstanding������outstanding���Ϊ4�� */
        unsigned int  outstanding_r : 1;  /* bit[1]   : ��ͨ��outstandingʹ�ܡ�
                                                        0��AXI masterû�ж�outstanding������
                                                        1��AXI master�ж�outstanding������outstanding���Ϊ4�� */
        unsigned int  reserved      : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_IPF_DMA_CTRL1_UNION;
#endif
#define SOC_IPF_DMA_CTRL1_outstanding_w_START  (0)
#define SOC_IPF_DMA_CTRL1_outstanding_w_END    (0)
#define SOC_IPF_DMA_CTRL1_outstanding_r_START  (1)
#define SOC_IPF_DMA_CTRL1_outstanding_r_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IPF_INT0_UNION
 �ṹ˵��  : INT0 �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж��ϱ��Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rpt_int0              : 1;  /* bit[0]    : ���н���ϱ��ж�0 */
        unsigned int  ul_timeout_int0          : 1;  /* bit[1]    : ���н���ϱ���ʱ�ж�0 */
        unsigned int  ul_disable_end_int0      : 1;  /* bit[2]    : ����ͨ���ر�����ж�0 */
        unsigned int  ul_idle_cfg_bd_int0      : 1;  /* bit[3]    : ����ͨ��IDLE�ڼ��������BDָʾ�ж�0 */
        unsigned int  ul_trail_cfg_bd_int0     : 1;  /* bit[4]    : ����ͨ���رյ�BDû�д������ڼ������������BDָʾ�ж�0 */
        unsigned int  ul_noidle_clrptr_int0    : 1;  /* bit[5]    : ���з�IDLE̬��ָ��ָʾ�ж�0 */
        unsigned int  ul_rdq_downoverflow_int0 : 1;  /* bit[6]    : ����RDQ�����ж�0 */
        unsigned int  ul_bdq_upoverflow_int0   : 1;  /* bit[7]    : ����BDQ�����ж�0 */
        unsigned int  ul_rdq_full_int0         : 1;  /* bit[8]    : ����RDQ���ж�0 */
        unsigned int  ul_bdq_epty_int0         : 1;  /* bit[9]    : ����BDQ���ж�0 */
        unsigned int  ul_adq0_epty_int0        : 1;  /* bit[10]   : ����ADQ0���ж�0 */
        unsigned int  ul_adq1_epty_int0        : 1;  /* bit[11]   : ����ADQ1���ж�0 */
        unsigned int  reserved_0               : 4;  /* bit[12-15]: ���� */
        unsigned int  dl_rpt_int0              : 1;  /* bit[16]   : ���н���ϱ��ж�0 */
        unsigned int  dl_timeout_int0          : 1;  /* bit[17]   : ���н���ϱ���ʱ�ж�0 */
        unsigned int  dl_disable_end_int0      : 1;  /* bit[18]   : ����ͨ���ر�����ж�0 */
        unsigned int  dl_idle_cfg_bd_int0      : 1;  /* bit[19]   : ����ͨ��IDLE�ڼ��������BDָʾ�ж�0 */
        unsigned int  dl_trail_cfg_bd_int0     : 1;  /* bit[20]   : ����ͨ���رյ�BDû�д������ڼ������������BDָʾ�ж�0 */
        unsigned int  dl_noidle_clrptr_int0    : 1;  /* bit[21]   : ���з�IDLE̬��ָ��ָʾ�ж�0 */
        unsigned int  dl_rdq_downoverflow_int0 : 1;  /* bit[22]   : ����RDQ�����ж�0 */
        unsigned int  dl_bdq_upoverflow_int0   : 1;  /* bit[23]   : ����BDQ�����ж�0 */
        unsigned int  dl_rdq_full_int0         : 1;  /* bit[24]   : ����RDQ���ж�0 */
        unsigned int  dl_bdq_epty_int0         : 1;  /* bit[25]   : ����BDQ���ж�0 */
        unsigned int  dl_adq0_epty_int0        : 1;  /* bit[26]   : ����ADQ0���ж�0 */
        unsigned int  dl_adq1_epty_int0        : 1;  /* bit[27]   : ����ADQ1���ж�0 */
        unsigned int  reserved_1               : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_IPF_INT0_UNION;
#endif
#define SOC_IPF_INT0_ul_rpt_int0_START               (0)
#define SOC_IPF_INT0_ul_rpt_int0_END                 (0)
#define SOC_IPF_INT0_ul_timeout_int0_START           (1)
#define SOC_IPF_INT0_ul_timeout_int0_END             (1)
#define SOC_IPF_INT0_ul_disable_end_int0_START       (2)
#define SOC_IPF_INT0_ul_disable_end_int0_END         (2)
#define SOC_IPF_INT0_ul_idle_cfg_bd_int0_START       (3)
#define SOC_IPF_INT0_ul_idle_cfg_bd_int0_END         (3)
#define SOC_IPF_INT0_ul_trail_cfg_bd_int0_START      (4)
#define SOC_IPF_INT0_ul_trail_cfg_bd_int0_END        (4)
#define SOC_IPF_INT0_ul_noidle_clrptr_int0_START     (5)
#define SOC_IPF_INT0_ul_noidle_clrptr_int0_END       (5)
#define SOC_IPF_INT0_ul_rdq_downoverflow_int0_START  (6)
#define SOC_IPF_INT0_ul_rdq_downoverflow_int0_END    (6)
#define SOC_IPF_INT0_ul_bdq_upoverflow_int0_START    (7)
#define SOC_IPF_INT0_ul_bdq_upoverflow_int0_END      (7)
#define SOC_IPF_INT0_ul_rdq_full_int0_START          (8)
#define SOC_IPF_INT0_ul_rdq_full_int0_END            (8)
#define SOC_IPF_INT0_ul_bdq_epty_int0_START          (9)
#define SOC_IPF_INT0_ul_bdq_epty_int0_END            (9)
#define SOC_IPF_INT0_ul_adq0_epty_int0_START         (10)
#define SOC_IPF_INT0_ul_adq0_epty_int0_END           (10)
#define SOC_IPF_INT0_ul_adq1_epty_int0_START         (11)
#define SOC_IPF_INT0_ul_adq1_epty_int0_END           (11)
#define SOC_IPF_INT0_dl_rpt_int0_START               (16)
#define SOC_IPF_INT0_dl_rpt_int0_END                 (16)
#define SOC_IPF_INT0_dl_timeout_int0_START           (17)
#define SOC_IPF_INT0_dl_timeout_int0_END             (17)
#define SOC_IPF_INT0_dl_disable_end_int0_START       (18)
#define SOC_IPF_INT0_dl_disable_end_int0_END         (18)
#define SOC_IPF_INT0_dl_idle_cfg_bd_int0_START       (19)
#define SOC_IPF_INT0_dl_idle_cfg_bd_int0_END         (19)
#define SOC_IPF_INT0_dl_trail_cfg_bd_int0_START      (20)
#define SOC_IPF_INT0_dl_trail_cfg_bd_int0_END        (20)
#define SOC_IPF_INT0_dl_noidle_clrptr_int0_START     (21)
#define SOC_IPF_INT0_dl_noidle_clrptr_int0_END       (21)
#define SOC_IPF_INT0_dl_rdq_downoverflow_int0_START  (22)
#define SOC_IPF_INT0_dl_rdq_downoverflow_int0_END    (22)
#define SOC_IPF_INT0_dl_bdq_upoverflow_int0_START    (23)
#define SOC_IPF_INT0_dl_bdq_upoverflow_int0_END      (23)
#define SOC_IPF_INT0_dl_rdq_full_int0_START          (24)
#define SOC_IPF_INT0_dl_rdq_full_int0_END            (24)
#define SOC_IPF_INT0_dl_bdq_epty_int0_START          (25)
#define SOC_IPF_INT0_dl_bdq_epty_int0_END            (25)
#define SOC_IPF_INT0_dl_adq0_epty_int0_START         (26)
#define SOC_IPF_INT0_dl_adq0_epty_int0_END           (26)
#define SOC_IPF_INT0_dl_adq1_epty_int0_START         (27)
#define SOC_IPF_INT0_dl_adq1_epty_int0_END           (27)


/*****************************************************************************
 �ṹ��    : SOC_IPF_INT1_UNION
 �ṹ˵��  : INT1 �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж��ϱ��Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rpt_int1              : 1;  /* bit[0]    : ���н���ϱ��ж�1 */
        unsigned int  ul_timeout_int1          : 1;  /* bit[1]    : ���н���ϱ���ʱ�ж�1 */
        unsigned int  ul_disable_end_int1      : 1;  /* bit[2]    : ����ͨ���ر�����ж�1 */
        unsigned int  ul_idle_cfg_bd_int1      : 1;  /* bit[3]    : ����ͨ��IDLE�ڼ��������BDָʾ�ж�1 */
        unsigned int  ul_trail_cfg_bd_int1     : 1;  /* bit[4]    : ����ͨ���رյ�BDû�д������ڼ������������BDָʾ�ж�1 */
        unsigned int  ul_noidle_clrptr_int1    : 1;  /* bit[5]    : ���з�IDLE̬��ָ��ָʾ�ж�1 */
        unsigned int  ul_rdq_downoverflow_int1 : 1;  /* bit[6]    : ����RDQ�����ж�1 */
        unsigned int  ul_bdq_upoverflow_int1   : 1;  /* bit[7]    : ����BDQ�����ж�1 */
        unsigned int  ul_rdq_full_int1         : 1;  /* bit[8]    : ����RDQ���ж�1 */
        unsigned int  ul_bdq_epty_int1         : 1;  /* bit[9]    : ����BDQ���ж�1 */
        unsigned int  ul_adq0_epty_int1        : 1;  /* bit[10]   : ����ADQ0���ж�1 */
        unsigned int  ul_adq1_epty_int1        : 1;  /* bit[11]   : ����ADQ1���ж�1 */
        unsigned int  reserved_0               : 4;  /* bit[12-15]: ���� */
        unsigned int  dl_rpt_int1              : 1;  /* bit[16]   : ���н���ϱ��ж�1 */
        unsigned int  dl_timeout_int1          : 1;  /* bit[17]   : ���н���ϱ���ʱ�ж�1 */
        unsigned int  dl_disable_end_int1      : 1;  /* bit[18]   : ����ͨ���ر�����ж�1 */
        unsigned int  dl_idle_cfg_bd_int1      : 1;  /* bit[19]   : ����ͨ��IDLE�ڼ��������BDָʾ�ж�1 */
        unsigned int  dl_trail_cfg_bd_int1     : 1;  /* bit[20]   : ����ͨ���رյ�BDû�д������ڼ������������BDָʾ�ж�1 */
        unsigned int  dl_noidle_clrptr_int1    : 1;  /* bit[21]   : ���з�IDLE̬��ָ��ָʾ�ж�1 */
        unsigned int  dl_rdq_downoverflow_int1 : 1;  /* bit[22]   : ����RDQ�����ж�1 */
        unsigned int  dl_bdq_upoverflow_int1   : 1;  /* bit[23]   : ����BDQ�����ж�1 */
        unsigned int  dl_rdq_full_int1         : 1;  /* bit[24]   : ����RDQ���ж�1 */
        unsigned int  dl_bdq_epty_int1         : 1;  /* bit[25]   : ����BDQ���ж�1 */
        unsigned int  dl_adq0_epty_int1        : 1;  /* bit[26]   : ����ADQ0���ж�1 */
        unsigned int  dl_adq1_epty_int1        : 1;  /* bit[27]   : ����ADQ1���ж�1 */
        unsigned int  reserved_1               : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_IPF_INT1_UNION;
#endif
#define SOC_IPF_INT1_ul_rpt_int1_START               (0)
#define SOC_IPF_INT1_ul_rpt_int1_END                 (0)
#define SOC_IPF_INT1_ul_timeout_int1_START           (1)
#define SOC_IPF_INT1_ul_timeout_int1_END             (1)
#define SOC_IPF_INT1_ul_disable_end_int1_START       (2)
#define SOC_IPF_INT1_ul_disable_end_int1_END         (2)
#define SOC_IPF_INT1_ul_idle_cfg_bd_int1_START       (3)
#define SOC_IPF_INT1_ul_idle_cfg_bd_int1_END         (3)
#define SOC_IPF_INT1_ul_trail_cfg_bd_int1_START      (4)
#define SOC_IPF_INT1_ul_trail_cfg_bd_int1_END        (4)
#define SOC_IPF_INT1_ul_noidle_clrptr_int1_START     (5)
#define SOC_IPF_INT1_ul_noidle_clrptr_int1_END       (5)
#define SOC_IPF_INT1_ul_rdq_downoverflow_int1_START  (6)
#define SOC_IPF_INT1_ul_rdq_downoverflow_int1_END    (6)
#define SOC_IPF_INT1_ul_bdq_upoverflow_int1_START    (7)
#define SOC_IPF_INT1_ul_bdq_upoverflow_int1_END      (7)
#define SOC_IPF_INT1_ul_rdq_full_int1_START          (8)
#define SOC_IPF_INT1_ul_rdq_full_int1_END            (8)
#define SOC_IPF_INT1_ul_bdq_epty_int1_START          (9)
#define SOC_IPF_INT1_ul_bdq_epty_int1_END            (9)
#define SOC_IPF_INT1_ul_adq0_epty_int1_START         (10)
#define SOC_IPF_INT1_ul_adq0_epty_int1_END           (10)
#define SOC_IPF_INT1_ul_adq1_epty_int1_START         (11)
#define SOC_IPF_INT1_ul_adq1_epty_int1_END           (11)
#define SOC_IPF_INT1_dl_rpt_int1_START               (16)
#define SOC_IPF_INT1_dl_rpt_int1_END                 (16)
#define SOC_IPF_INT1_dl_timeout_int1_START           (17)
#define SOC_IPF_INT1_dl_timeout_int1_END             (17)
#define SOC_IPF_INT1_dl_disable_end_int1_START       (18)
#define SOC_IPF_INT1_dl_disable_end_int1_END         (18)
#define SOC_IPF_INT1_dl_idle_cfg_bd_int1_START       (19)
#define SOC_IPF_INT1_dl_idle_cfg_bd_int1_END         (19)
#define SOC_IPF_INT1_dl_trail_cfg_bd_int1_START      (20)
#define SOC_IPF_INT1_dl_trail_cfg_bd_int1_END        (20)
#define SOC_IPF_INT1_dl_noidle_clrptr_int1_START     (21)
#define SOC_IPF_INT1_dl_noidle_clrptr_int1_END       (21)
#define SOC_IPF_INT1_dl_rdq_downoverflow_int1_START  (22)
#define SOC_IPF_INT1_dl_rdq_downoverflow_int1_END    (22)
#define SOC_IPF_INT1_dl_bdq_upoverflow_int1_START    (23)
#define SOC_IPF_INT1_dl_bdq_upoverflow_int1_END      (23)
#define SOC_IPF_INT1_dl_rdq_full_int1_START          (24)
#define SOC_IPF_INT1_dl_rdq_full_int1_END            (24)
#define SOC_IPF_INT1_dl_bdq_epty_int1_START          (25)
#define SOC_IPF_INT1_dl_bdq_epty_int1_END            (25)
#define SOC_IPF_INT1_dl_adq0_epty_int1_START         (26)
#define SOC_IPF_INT1_dl_adq0_epty_int1_END           (26)
#define SOC_IPF_INT1_dl_adq1_epty_int1_START         (27)
#define SOC_IPF_INT1_dl_adq1_epty_int1_END           (27)


/*****************************************************************************
 �ṹ��    : SOC_IPF_INT_MASK0_UNION
 �ṹ˵��  : INT_MASK0 �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж����μĴ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rpt_mask0              : 1;  /* bit[0]    : ���н���ϱ��ж����μĴ���0 */
        unsigned int  ul_timeout_mask0          : 1;  /* bit[1]    : ���н���ϱ���ʱ�ж����μĴ���0 */
        unsigned int  ul_disable_end_mask0      : 1;  /* bit[2]    : ����ͨ���ر�����ж����μĴ���0 */
        unsigned int  ul_idle_cfg_bd_mask0      : 1;  /* bit[3]    : ����ͨ��IDLE�ڼ��������BDָʾ�ж����μĴ���0 */
        unsigned int  ul_trail_cfg_bd_mask0     : 1;  /* bit[4]    : ����ͨ���رյ�BDû�д������ڼ������������BDָʾ�ж����μĴ���0 */
        unsigned int  ul_noidle_clrptr_mask0    : 1;  /* bit[5]    : ���з�IDLE̬��ָ��ָʾ�ж����μĴ���0 */
        unsigned int  ul_rdq_downoverflow_mask0 : 1;  /* bit[6]    : ����RDQ�����ж����μĴ���0 */
        unsigned int  ul_bdq_upoverflow_mask0   : 1;  /* bit[7]    : ����BDQ�����ж����μĴ���0 */
        unsigned int  ul_rdq_full_mask0         : 1;  /* bit[8]    : ����RDQ���ж����μĴ���0 */
        unsigned int  ul_bdq_epty_mask0         : 1;  /* bit[9]    : ����BDQ���ж����μĴ���0 */
        unsigned int  ul_adq0_epty_mask0        : 1;  /* bit[10]   : ����ADQ0���ж����μĴ���0 */
        unsigned int  ul_adq1_epty_mask0        : 1;  /* bit[11]   : ����ADQ1���ж����μĴ���0 */
        unsigned int  reserved_0                : 4;  /* bit[12-15]: ���� */
        unsigned int  dl_rpt_mask0              : 1;  /* bit[16]   : ���н���ϱ��ж����μĴ���0 */
        unsigned int  dl_timeout_mask0          : 1;  /* bit[17]   : ���н���ϱ���ʱ�ж����μĴ���0 */
        unsigned int  dl_disable_end_mask0      : 1;  /* bit[18]   : ����ͨ���ر�����ж����μĴ���0 */
        unsigned int  dl_idle_cfg_bd_mask0      : 1;  /* bit[19]   : ����ͨ��IDLE�ڼ��������BDָʾ�ж����μĴ���0 */
        unsigned int  dl_trail_cfg_bd_mask0     : 1;  /* bit[20]   : ����ͨ���رյ�BDû�д������ڼ������������BDָʾ�ж����μĴ���0 */
        unsigned int  dl_noidle_clrptr_mask0    : 1;  /* bit[21]   : ���з�IDLE̬��ָ��ָʾ�ж����μĴ���0 */
        unsigned int  dl_rdq_downoverflow_mask0 : 1;  /* bit[22]   : ����RDQ�����ж����μĴ���0 */
        unsigned int  dl_bdq_upoverflow_mask0   : 1;  /* bit[23]   : ����BDQ�����ж����μĴ���0 */
        unsigned int  dl_rdq_full_mask0         : 1;  /* bit[24]   : ����RDQ���ж����μĴ���0 */
        unsigned int  dl_bdq_epty_mask0         : 1;  /* bit[25]   : ����BDQ���ж����μĴ���0 */
        unsigned int  dl_adq0_epty_mask0        : 1;  /* bit[26]   : ����ADQ0���ж����μĴ���0 */
        unsigned int  dl_adq1_epty_mask0        : 1;  /* bit[27]   : ����ADQ1���ж����μĴ���0��
                                                                     0 */
        unsigned int  reserved_1                : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_IPF_INT_MASK0_UNION;
#endif
#define SOC_IPF_INT_MASK0_ul_rpt_mask0_START               (0)
#define SOC_IPF_INT_MASK0_ul_rpt_mask0_END                 (0)
#define SOC_IPF_INT_MASK0_ul_timeout_mask0_START           (1)
#define SOC_IPF_INT_MASK0_ul_timeout_mask0_END             (1)
#define SOC_IPF_INT_MASK0_ul_disable_end_mask0_START       (2)
#define SOC_IPF_INT_MASK0_ul_disable_end_mask0_END         (2)
#define SOC_IPF_INT_MASK0_ul_idle_cfg_bd_mask0_START       (3)
#define SOC_IPF_INT_MASK0_ul_idle_cfg_bd_mask0_END         (3)
#define SOC_IPF_INT_MASK0_ul_trail_cfg_bd_mask0_START      (4)
#define SOC_IPF_INT_MASK0_ul_trail_cfg_bd_mask0_END        (4)
#define SOC_IPF_INT_MASK0_ul_noidle_clrptr_mask0_START     (5)
#define SOC_IPF_INT_MASK0_ul_noidle_clrptr_mask0_END       (5)
#define SOC_IPF_INT_MASK0_ul_rdq_downoverflow_mask0_START  (6)
#define SOC_IPF_INT_MASK0_ul_rdq_downoverflow_mask0_END    (6)
#define SOC_IPF_INT_MASK0_ul_bdq_upoverflow_mask0_START    (7)
#define SOC_IPF_INT_MASK0_ul_bdq_upoverflow_mask0_END      (7)
#define SOC_IPF_INT_MASK0_ul_rdq_full_mask0_START          (8)
#define SOC_IPF_INT_MASK0_ul_rdq_full_mask0_END            (8)
#define SOC_IPF_INT_MASK0_ul_bdq_epty_mask0_START          (9)
#define SOC_IPF_INT_MASK0_ul_bdq_epty_mask0_END            (9)
#define SOC_IPF_INT_MASK0_ul_adq0_epty_mask0_START         (10)
#define SOC_IPF_INT_MASK0_ul_adq0_epty_mask0_END           (10)
#define SOC_IPF_INT_MASK0_ul_adq1_epty_mask0_START         (11)
#define SOC_IPF_INT_MASK0_ul_adq1_epty_mask0_END           (11)
#define SOC_IPF_INT_MASK0_dl_rpt_mask0_START               (16)
#define SOC_IPF_INT_MASK0_dl_rpt_mask0_END                 (16)
#define SOC_IPF_INT_MASK0_dl_timeout_mask0_START           (17)
#define SOC_IPF_INT_MASK0_dl_timeout_mask0_END             (17)
#define SOC_IPF_INT_MASK0_dl_disable_end_mask0_START       (18)
#define SOC_IPF_INT_MASK0_dl_disable_end_mask0_END         (18)
#define SOC_IPF_INT_MASK0_dl_idle_cfg_bd_mask0_START       (19)
#define SOC_IPF_INT_MASK0_dl_idle_cfg_bd_mask0_END         (19)
#define SOC_IPF_INT_MASK0_dl_trail_cfg_bd_mask0_START      (20)
#define SOC_IPF_INT_MASK0_dl_trail_cfg_bd_mask0_END        (20)
#define SOC_IPF_INT_MASK0_dl_noidle_clrptr_mask0_START     (21)
#define SOC_IPF_INT_MASK0_dl_noidle_clrptr_mask0_END       (21)
#define SOC_IPF_INT_MASK0_dl_rdq_downoverflow_mask0_START  (22)
#define SOC_IPF_INT_MASK0_dl_rdq_downoverflow_mask0_END    (22)
#define SOC_IPF_INT_MASK0_dl_bdq_upoverflow_mask0_START    (23)
#define SOC_IPF_INT_MASK0_dl_bdq_upoverflow_mask0_END      (23)
#define SOC_IPF_INT_MASK0_dl_rdq_full_mask0_START          (24)
#define SOC_IPF_INT_MASK0_dl_rdq_full_mask0_END            (24)
#define SOC_IPF_INT_MASK0_dl_bdq_epty_mask0_START          (25)
#define SOC_IPF_INT_MASK0_dl_bdq_epty_mask0_END            (25)
#define SOC_IPF_INT_MASK0_dl_adq0_epty_mask0_START         (26)
#define SOC_IPF_INT_MASK0_dl_adq0_epty_mask0_END           (26)
#define SOC_IPF_INT_MASK0_dl_adq1_epty_mask0_START         (27)
#define SOC_IPF_INT_MASK0_dl_adq1_epty_mask0_END           (27)


/*****************************************************************************
 �ṹ��    : SOC_IPF_INT_MASK1_UNION
 �ṹ˵��  : INT_MASK1 �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж����μĴ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rpt_mask1              : 1;  /* bit[0]    : ���н���ϱ��ж����μĴ���1 */
        unsigned int  ul_timeout_mask1          : 1;  /* bit[1]    : ���н���ϱ���ʱ�ж����μĴ���1 */
        unsigned int  ul_disable_end_mask1      : 1;  /* bit[2]    : ����ͨ���ر�����ж����μĴ���1 */
        unsigned int  ul_idle_cfg_bd_mask1      : 1;  /* bit[3]    : ����ͨ��IDLE�ڼ��������BDָʾ�ж����μĴ���1 */
        unsigned int  ul_trail_cfg_bd_mask1     : 1;  /* bit[4]    : ����ͨ���رյ�BDû�д������ڼ������������BDָʾ�ж����μĴ���1 */
        unsigned int  ul_noidle_clrptr_mask1    : 1;  /* bit[5]    : ���з�IDLE̬��ָ��ָʾ�ж����μĴ���1 */
        unsigned int  ul_rdq_downoverflow_mask1 : 1;  /* bit[6]    : ����RDQ�����ж����μĴ���1 */
        unsigned int  ul_bdq_upoverflow_mask1   : 1;  /* bit[7]    : ����BDQ�����ж����μĴ���1 */
        unsigned int  ul_rdq_full_mask1         : 1;  /* bit[8]    : ����RDQ���ж����μĴ���1 */
        unsigned int  ul_bdq_epty_mask1         : 1;  /* bit[9]    : ����BDQ���ж����μĴ���1 */
        unsigned int  ul_adq0_epty_mask1        : 1;  /* bit[10]   : ����ADQ0���ж����μĴ���1 */
        unsigned int  ul_adq1_epty_mask1        : 1;  /* bit[11]   : ����ADQ1���ж����μĴ���1 */
        unsigned int  reserved_0                : 4;  /* bit[12-15]: ���� */
        unsigned int  dl_rpt_mask1              : 1;  /* bit[16]   : ���н���ϱ��ж����μĴ���1 */
        unsigned int  dl_timeout_mask1          : 1;  /* bit[17]   : ���н���ϱ���ʱ�ж����μĴ���1 */
        unsigned int  dl_disable_end_mask1      : 1;  /* bit[18]   : ����ͨ���ر�����ж����μĴ���1 */
        unsigned int  dl_idle_cfg_bd_mask1      : 1;  /* bit[19]   : ����ͨ��IDLE�ڼ��������BDָʾ�ж����μĴ���1 */
        unsigned int  dl_trail_cfg_bd_mask1     : 1;  /* bit[20]   : ����ͨ���رյ�BDû�д������ڼ������������BDָʾ�ж����μĴ���1 */
        unsigned int  dl_noidle_clrptr_mask1    : 1;  /* bit[21]   : ���з�IDLE̬��ָ��ָʾ�ж����μĴ���1 */
        unsigned int  dl_rdq_downoverflow_mask1 : 1;  /* bit[22]   : ����RDQ�����ж����μĴ���1 */
        unsigned int  dl_bdq_upoverflow_mask1   : 1;  /* bit[23]   : ����BDQ�����ж����μĴ���1 */
        unsigned int  dl_rdq_full_mask1         : 1;  /* bit[24]   : ����RDQ���ж����μĴ���1 */
        unsigned int  dl_bdq_epty_mask1         : 1;  /* bit[25]   : ����BDQ���ж����μĴ���1 */
        unsigned int  dl_adq0_epty_mask1        : 1;  /* bit[26]   : ����ADQ0���ж����μĴ���1 */
        unsigned int  dl_adq1_epty_mask1        : 1;  /* bit[27]   : ����ADQ1���ж����μĴ���1 */
        unsigned int  reserved_1                : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_IPF_INT_MASK1_UNION;
#endif
#define SOC_IPF_INT_MASK1_ul_rpt_mask1_START               (0)
#define SOC_IPF_INT_MASK1_ul_rpt_mask1_END                 (0)
#define SOC_IPF_INT_MASK1_ul_timeout_mask1_START           (1)
#define SOC_IPF_INT_MASK1_ul_timeout_mask1_END             (1)
#define SOC_IPF_INT_MASK1_ul_disable_end_mask1_START       (2)
#define SOC_IPF_INT_MASK1_ul_disable_end_mask1_END         (2)
#define SOC_IPF_INT_MASK1_ul_idle_cfg_bd_mask1_START       (3)
#define SOC_IPF_INT_MASK1_ul_idle_cfg_bd_mask1_END         (3)
#define SOC_IPF_INT_MASK1_ul_trail_cfg_bd_mask1_START      (4)
#define SOC_IPF_INT_MASK1_ul_trail_cfg_bd_mask1_END        (4)
#define SOC_IPF_INT_MASK1_ul_noidle_clrptr_mask1_START     (5)
#define SOC_IPF_INT_MASK1_ul_noidle_clrptr_mask1_END       (5)
#define SOC_IPF_INT_MASK1_ul_rdq_downoverflow_mask1_START  (6)
#define SOC_IPF_INT_MASK1_ul_rdq_downoverflow_mask1_END    (6)
#define SOC_IPF_INT_MASK1_ul_bdq_upoverflow_mask1_START    (7)
#define SOC_IPF_INT_MASK1_ul_bdq_upoverflow_mask1_END      (7)
#define SOC_IPF_INT_MASK1_ul_rdq_full_mask1_START          (8)
#define SOC_IPF_INT_MASK1_ul_rdq_full_mask1_END            (8)
#define SOC_IPF_INT_MASK1_ul_bdq_epty_mask1_START          (9)
#define SOC_IPF_INT_MASK1_ul_bdq_epty_mask1_END            (9)
#define SOC_IPF_INT_MASK1_ul_adq0_epty_mask1_START         (10)
#define SOC_IPF_INT_MASK1_ul_adq0_epty_mask1_END           (10)
#define SOC_IPF_INT_MASK1_ul_adq1_epty_mask1_START         (11)
#define SOC_IPF_INT_MASK1_ul_adq1_epty_mask1_END           (11)
#define SOC_IPF_INT_MASK1_dl_rpt_mask1_START               (16)
#define SOC_IPF_INT_MASK1_dl_rpt_mask1_END                 (16)
#define SOC_IPF_INT_MASK1_dl_timeout_mask1_START           (17)
#define SOC_IPF_INT_MASK1_dl_timeout_mask1_END             (17)
#define SOC_IPF_INT_MASK1_dl_disable_end_mask1_START       (18)
#define SOC_IPF_INT_MASK1_dl_disable_end_mask1_END         (18)
#define SOC_IPF_INT_MASK1_dl_idle_cfg_bd_mask1_START       (19)
#define SOC_IPF_INT_MASK1_dl_idle_cfg_bd_mask1_END         (19)
#define SOC_IPF_INT_MASK1_dl_trail_cfg_bd_mask1_START      (20)
#define SOC_IPF_INT_MASK1_dl_trail_cfg_bd_mask1_END        (20)
#define SOC_IPF_INT_MASK1_dl_noidle_clrptr_mask1_START     (21)
#define SOC_IPF_INT_MASK1_dl_noidle_clrptr_mask1_END       (21)
#define SOC_IPF_INT_MASK1_dl_rdq_downoverflow_mask1_START  (22)
#define SOC_IPF_INT_MASK1_dl_rdq_downoverflow_mask1_END    (22)
#define SOC_IPF_INT_MASK1_dl_bdq_upoverflow_mask1_START    (23)
#define SOC_IPF_INT_MASK1_dl_bdq_upoverflow_mask1_END      (23)
#define SOC_IPF_INT_MASK1_dl_rdq_full_mask1_START          (24)
#define SOC_IPF_INT_MASK1_dl_rdq_full_mask1_END            (24)
#define SOC_IPF_INT_MASK1_dl_bdq_epty_mask1_START          (25)
#define SOC_IPF_INT_MASK1_dl_bdq_epty_mask1_END            (25)
#define SOC_IPF_INT_MASK1_dl_adq0_epty_mask1_START         (26)
#define SOC_IPF_INT_MASK1_dl_adq0_epty_mask1_END           (26)
#define SOC_IPF_INT_MASK1_dl_adq1_epty_mask1_START         (27)
#define SOC_IPF_INT_MASK1_dl_adq1_epty_mask1_END           (27)


/*****************************************************************************
 �ṹ��    : SOC_IPF_INT_STATE_UNION
 �ṹ˵��  : INT_STATE �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rpt              : 1;  /* bit[0]    : ���н���ϱ�ָʾ */
        unsigned int  ul_timeout          : 1;  /* bit[1]    : ���н���ϱ���ʱָʾ */
        unsigned int  ul_disable_end      : 1;  /* bit[2]    : ����ͨ���ر����ָʾ */
        unsigned int  ul_idle_cfg_bd      : 1;  /* bit[3]    : ����ͨ��IDLE�ڼ��������BDָʾ */
        unsigned int  ul_trail_cfg_bd     : 1;  /* bit[4]    : ����ͨ���رյ�BDû�д������ڼ������������BDָʾ */
        unsigned int  ul_noidle_clrptr    : 1;  /* bit[5]    : ���з�IDLE̬��ָ��ָʾ */
        unsigned int  ul_rdq_downoverflow : 1;  /* bit[6]    : ����RDQ����ָʾ */
        unsigned int  ul_bdq_upoverflow   : 1;  /* bit[7]    : ����BDQ����ָʾ */
        unsigned int  ul_rdq_full         : 1;  /* bit[8]    : ����RDQ��ָʾ */
        unsigned int  ul_bdq_epty         : 1;  /* bit[9]    : ����ͨ��BDQ��ָʾ */
        unsigned int  ul_adq0_epty        : 1;  /* bit[10]   : ����ͨ��ADQ0��ָʾ */
        unsigned int  ul_adq1_epty        : 1;  /* bit[11]   : ����ͨ��ADQ1��ָʾ */
        unsigned int  reserved_0          : 4;  /* bit[12-15]: ���� */
        unsigned int  dl_rpt              : 1;  /* bit[16]   : ���н���ϱ�ָʾ */
        unsigned int  dl_timeout          : 1;  /* bit[17]   : ���н���ϱ���ʱָʾ */
        unsigned int  dl_disable_end      : 1;  /* bit[18]   : ����ͨ���ر����ָʾ */
        unsigned int  dl_idle_cfg_bd      : 1;  /* bit[19]   : ����ͨ��IDLE�ڼ��������BDָʾ */
        unsigned int  dl_trail_cfg_bd     : 1;  /* bit[20]   : ����ͨ���رյ�BDû�д������ڼ������������BDָʾ */
        unsigned int  dl_noidle_clrptr    : 1;  /* bit[21]   : ���з�IDLE̬��ָ��ָʾ */
        unsigned int  dl_rdq_downoverflow : 1;  /* bit[22]   : ����RDQ����ָʾ */
        unsigned int  dl_bdq_upoverflow   : 1;  /* bit[23]   : ����BDQ����ָʾ */
        unsigned int  dl_rdq_full         : 1;  /* bit[24]   : ����RDQ��ָʾ */
        unsigned int  dl_bdq_epty         : 1;  /* bit[25]   : ����ͨ��BDQ��ָʾ */
        unsigned int  dl_adq0_epty        : 1;  /* bit[26]   : ����ͨ��ADQ0��ָʾ */
        unsigned int  dl_adq1_epty        : 1;  /* bit[27]   : ����ͨ��ADQ1��ָʾ */
        unsigned int  reserved_1          : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_IPF_INT_STATE_UNION;
#endif
#define SOC_IPF_INT_STATE_ul_rpt_START               (0)
#define SOC_IPF_INT_STATE_ul_rpt_END                 (0)
#define SOC_IPF_INT_STATE_ul_timeout_START           (1)
#define SOC_IPF_INT_STATE_ul_timeout_END             (1)
#define SOC_IPF_INT_STATE_ul_disable_end_START       (2)
#define SOC_IPF_INT_STATE_ul_disable_end_END         (2)
#define SOC_IPF_INT_STATE_ul_idle_cfg_bd_START       (3)
#define SOC_IPF_INT_STATE_ul_idle_cfg_bd_END         (3)
#define SOC_IPF_INT_STATE_ul_trail_cfg_bd_START      (4)
#define SOC_IPF_INT_STATE_ul_trail_cfg_bd_END        (4)
#define SOC_IPF_INT_STATE_ul_noidle_clrptr_START     (5)
#define SOC_IPF_INT_STATE_ul_noidle_clrptr_END       (5)
#define SOC_IPF_INT_STATE_ul_rdq_downoverflow_START  (6)
#define SOC_IPF_INT_STATE_ul_rdq_downoverflow_END    (6)
#define SOC_IPF_INT_STATE_ul_bdq_upoverflow_START    (7)
#define SOC_IPF_INT_STATE_ul_bdq_upoverflow_END      (7)
#define SOC_IPF_INT_STATE_ul_rdq_full_START          (8)
#define SOC_IPF_INT_STATE_ul_rdq_full_END            (8)
#define SOC_IPF_INT_STATE_ul_bdq_epty_START          (9)
#define SOC_IPF_INT_STATE_ul_bdq_epty_END            (9)
#define SOC_IPF_INT_STATE_ul_adq0_epty_START         (10)
#define SOC_IPF_INT_STATE_ul_adq0_epty_END           (10)
#define SOC_IPF_INT_STATE_ul_adq1_epty_START         (11)
#define SOC_IPF_INT_STATE_ul_adq1_epty_END           (11)
#define SOC_IPF_INT_STATE_dl_rpt_START               (16)
#define SOC_IPF_INT_STATE_dl_rpt_END                 (16)
#define SOC_IPF_INT_STATE_dl_timeout_START           (17)
#define SOC_IPF_INT_STATE_dl_timeout_END             (17)
#define SOC_IPF_INT_STATE_dl_disable_end_START       (18)
#define SOC_IPF_INT_STATE_dl_disable_end_END         (18)
#define SOC_IPF_INT_STATE_dl_idle_cfg_bd_START       (19)
#define SOC_IPF_INT_STATE_dl_idle_cfg_bd_END         (19)
#define SOC_IPF_INT_STATE_dl_trail_cfg_bd_START      (20)
#define SOC_IPF_INT_STATE_dl_trail_cfg_bd_END        (20)
#define SOC_IPF_INT_STATE_dl_noidle_clrptr_START     (21)
#define SOC_IPF_INT_STATE_dl_noidle_clrptr_END       (21)
#define SOC_IPF_INT_STATE_dl_rdq_downoverflow_START  (22)
#define SOC_IPF_INT_STATE_dl_rdq_downoverflow_END    (22)
#define SOC_IPF_INT_STATE_dl_bdq_upoverflow_START    (23)
#define SOC_IPF_INT_STATE_dl_bdq_upoverflow_END      (23)
#define SOC_IPF_INT_STATE_dl_rdq_full_START          (24)
#define SOC_IPF_INT_STATE_dl_rdq_full_END            (24)
#define SOC_IPF_INT_STATE_dl_bdq_epty_START          (25)
#define SOC_IPF_INT_STATE_dl_bdq_epty_END            (25)
#define SOC_IPF_INT_STATE_dl_adq0_epty_START         (26)
#define SOC_IPF_INT_STATE_dl_adq0_epty_END           (26)
#define SOC_IPF_INT_STATE_dl_adq1_epty_START         (27)
#define SOC_IPF_INT_STATE_dl_adq1_epty_END           (27)


/*****************************************************************************
 �ṹ��    : SOC_IPF_TIME_OUT_UNION
 �ṹ˵��  : TIME_OUT �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʱ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  time_out_cfg   : 16; /* bit[0-15] : ��ʱ���ã��������RD�����ʱ���ϱ��жϣ�����Ϊ256��ʱ�����ڡ�������ͨ��ͬʱ��Ч�� */
        unsigned int  time_out_valid : 1;  /* bit[16]   : ��ʱ�ж�ʹ�� */
        unsigned int  reserved       : 15; /* bit[17-31]: ������ */
    } reg;
} SOC_IPF_TIME_OUT_UNION;
#endif
#define SOC_IPF_TIME_OUT_time_out_cfg_START    (0)
#define SOC_IPF_TIME_OUT_time_out_cfg_END      (15)
#define SOC_IPF_TIME_OUT_time_out_valid_START  (16)
#define SOC_IPF_TIME_OUT_time_out_valid_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_IPF_PKT_LEN_UNION
 �ṹ˵��  : PKT_LEN �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x05DC0028�����:32
 �Ĵ���˵��: �������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  min_pkt_len : 14; /* bit[0-13] : ��С�������üĴ�����Ĭ��ֵΪ40�ֽڣ�0x28�� */
        unsigned int  reserved_0  : 2;  /* bit[14-15]: ������ */
        unsigned int  max_pkt_len : 14; /* bit[16-29]: ���������üĴ�����Ĭ��ֵΪ1500�ֽڣ�0x5DC�� */
        unsigned int  reserved_1  : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_IPF_PKT_LEN_UNION;
#endif
#define SOC_IPF_PKT_LEN_min_pkt_len_START  (0)
#define SOC_IPF_PKT_LEN_min_pkt_len_END    (13)
#define SOC_IPF_PKT_LEN_max_pkt_len_START  (16)
#define SOC_IPF_PKT_LEN_max_pkt_len_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FILTER_ZERO_INDEX_UNION
 �ṹ˵��  : FILTER_ZERO_INDEX �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x01FF01FF�����:32
 �Ĵ���˵��: IPF��������ʼ�������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_filter_zero_index : 9;  /* bit[0-8]  : ul������������ʼ������ul������������ʼ��ַ���÷�ΧΪ0��63����չ��������ַ��Χ��64~510���������Ϊ511��ʾ����ͨ���޹�������Ĭ��ֵΪ511��0x1FF����
                                                                ��mfc_en����λ��Чʱ���������Ч�� */
        unsigned int  reserved_0           : 7;  /* bit[9-15] : ������ */
        unsigned int  dl_filter_zero_index : 9;  /* bit[16-24]: dl������������ʼ������dl������������ʼ��ַ���÷�ΧΪ0��63,��չ��������ַ��Χ��64~510���������Ϊ511��ʾ����ͨ���޹�������Ĭ��ֵΪ511��0x1FF����
                                                                ��mfc_en����λ��Чʱ���������Ч�� */
        unsigned int  reserved_1           : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_IPF_FILTER_ZERO_INDEX_UNION;
#endif
#define SOC_IPF_FILTER_ZERO_INDEX_ul_filter_zero_index_START  (0)
#define SOC_IPF_FILTER_ZERO_INDEX_ul_filter_zero_index_END    (8)
#define SOC_IPF_FILTER_ZERO_INDEX_dl_filter_zero_index_START  (16)
#define SOC_IPF_FILTER_ZERO_INDEX_dl_filter_zero_index_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_IPF_EF_BADDR_UNION
 �ṹ˵��  : EF_BADDR �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��չ����������ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ef_baddr : 32; /* bit[0-31]: ��չ��������ʼ��ַ��8�ֽڶ��� */
    } reg;
} SOC_IPF_EF_BADDR_UNION;
#endif
#define SOC_IPF_EF_BADDR_ef_baddr_START  (0)
#define SOC_IPF_EF_BADDR_ef_baddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_BFLT_INDEX_UNION
 �ṹ˵��  : BFLT_INDEX �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������˱���������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bf_index : 8;  /* bit[0-7] : �������˱��д��ַ����ΧΪ0��63�� */
        unsigned int  reserved : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_BFLT_INDEX_UNION;
#endif
#define SOC_IPF_BFLT_INDEX_bf_index_START  (0)
#define SOC_IPF_BFLT_INDEX_bf_index_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_CHAIN_LOOP_UNION
 �ṹ˵��  : FLT_CHAIN_LOOP �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x0000�����:32
 �Ĵ���˵��: �����������澯
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_chain_loop : 1;  /* bit[0]   : ��ʾ�����������γɻ��쳣�澯 */
        unsigned int                 : 31; /* bit[1-31]:  */
    } reg;
} SOC_IPF_FLT_CHAIN_LOOP_UNION;
#endif
#define SOC_IPF_FLT_CHAIN_LOOP_flt_chain_loop_START  (0)
#define SOC_IPF_FLT_CHAIN_LOOP_flt_chain_loop_END    (0)
#define SOC_IPF_FLT_CHAIN_LOOP__START                (1)
#define SOC_IPF_FLT_CHAIN_LOOP__END                  (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_LOCAL_ADDR0_UNION
 �ṹ˵��  : FLT_LOCAL_ADDR0 �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������local address���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_laddr0 : 32; /* bit[0-31]: flt_addr_reverse����0ʱ�����ֽڴ�����У�IPV6��ʾLOCAL ADDRESS {[103:96],[111:104],[119:112],[127:120]}��IPV4��ʾLOCAL ADDRESS {[7:0],[15:8],[23:16],[31:24]}
                                                     flt_addr_reverse����1ʱ�����ֽ�С�����У�IPV6��ʾLOCAL ADDRESS [127:96]��
                                                     IPV4��ʾLOCAL ADDRESS [31:0] */
    } reg;
} SOC_IPF_FLT_LOCAL_ADDR0_UNION;
#endif
#define SOC_IPF_FLT_LOCAL_ADDR0_flt_laddr0_START  (0)
#define SOC_IPF_FLT_LOCAL_ADDR0_flt_laddr0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_LOCAL_ADDR1_UNION
 �ṹ˵��  : FLT_LOCAL_ADDR1 �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������local address���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_laddr1 : 32; /* bit[0-31]: flt_addr_reverse����0ʱ�����ֽڴ�����У�IPV6��ʾLOCAL ADDRESS {[71:64],[79:72],[87:80],[95:88]}
                                                     flt_addr_reverse����1ʱ�����ֽ�С�����У�IPV6��ʾLOCAL ADDRESS[95:64]
                                                     IPV4���� */
    } reg;
} SOC_IPF_FLT_LOCAL_ADDR1_UNION;
#endif
#define SOC_IPF_FLT_LOCAL_ADDR1_flt_laddr1_START  (0)
#define SOC_IPF_FLT_LOCAL_ADDR1_flt_laddr1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_LOCAL_ADDR2_UNION
 �ṹ˵��  : FLT_LOCAL_ADDR2 �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������local address���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_laddr2 : 32; /* bit[0-31]: flt_addr_reverse����0ʱ�����ֽڴ�����У�IPV6��ʾLOCAL ADDRESS {[39:32],[47:40],[55:48],[63:56]}
                                                     flt_addr_reverse����1ʱ�����ֽ�С�����У�IPV6��ʾLOCAL ADDRESS[63:32]
                                                     IPV4���� */
    } reg;
} SOC_IPF_FLT_LOCAL_ADDR2_UNION;
#endif
#define SOC_IPF_FLT_LOCAL_ADDR2_flt_laddr2_START  (0)
#define SOC_IPF_FLT_LOCAL_ADDR2_flt_laddr2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_LOCAL_ADDR3_UNION
 �ṹ˵��  : FLT_LOCAL_ADDR3 �Ĵ����ṹ���塣��ַƫ����:0x009C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������local address���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_laddr3 : 32; /* bit[0-31]: flt_addr_reverse����0ʱ�����ֽڴ�����У�IPV6��ʾLOCAL ADDRESS {[7:0],[15:8],[23:16],[31:24]}
                                                     flt_addr_reverse����1ʱ�����ֽ�С�����У�IPV6��ʾLOCAL ADDRESS[31:0]
                                                     IPV4���� */
    } reg;
} SOC_IPF_FLT_LOCAL_ADDR3_UNION;
#endif
#define SOC_IPF_FLT_LOCAL_ADDR3_flt_laddr3_START  (0)
#define SOC_IPF_FLT_LOCAL_ADDR3_flt_laddr3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_REMOTE_ADDR0_UNION
 �ṹ˵��  : FLT_REMOTE_ADDR0 �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������remote address���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr0 : 32; /* bit[0-31]: flt_addr_reverse����0ʱ�����ֽڴ�����У�IPV6��ʾREMOTE ADDRESS {[103:96],[111:104],[119:112],[127:120]}��
                                                     IPV4��ʾREMOTE ADDRESS {[7:0],[15:8],[23:16],[31:24]}
                                                     flt_addr_reverse����1ʱ�����ֽ�С�����У�IPV6��ʾREMOTE ADDRESS[127:96]��
                                                     IPV4��ʾREMOTE ADDRESS[31:0] */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR0_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR0_flt_raddr0_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR0_flt_raddr0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_REMOTE_ADDR1_UNION
 �ṹ˵��  : FLT_REMOTE_ADDR1 �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������remote address���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr1 : 32; /* bit[0-31]: flt_addr_reverse����0ʱ�����ֽڴ�����У�IPV6��ʾREMOTE ADDRESS {[71:64],[79:72],[87:80],[95:88]}
                                                     flt_addr_reverse����1ʱ�����ֽ�С�����У�IPV6��ʾREMOTE ADDRESS[95:64]
                                                     IPV4���� */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR1_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR1_flt_raddr1_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR1_flt_raddr1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_REMOTE_ADDR2_UNION
 �ṹ˵��  : FLT_REMOTE_ADDR2 �Ĵ����ṹ���塣��ַƫ����:0x00A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������remote address���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr2 : 32; /* bit[0-31]: flt_addr_reverse����0ʱ�����ֽڴ�����У�IPV6��ʾREMOTE ADDRESS {[39:32],[47:40],[55:48],[63:56]}
                                                     flt_addr_reverse����1ʱ�����ֽ�С�����У�IPV6��ʾREMOTE ADDRESS[63:32]
                                                     IPV4���� */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR2_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR2_flt_raddr2_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR2_flt_raddr2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_REMOTE_ADDR3_UNION
 �ṹ˵��  : FLT_REMOTE_ADDR3 �Ĵ����ṹ���塣��ַƫ����:0x00AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������remote address���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr3 : 32; /* bit[0-31]: flt_addr_reverse����0ʱ�����ֽڴ�����У�IPV6��ʾREMOTE ADDRESS {[7:0],[15:8],[23:16],[31:24]}
                                                     flt_addr_reverse����1ʱ�����ֽ�С�����У�IPV6��ʾREMOTE ADDRESS[31:0]
                                                     IPV4���� */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR3_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR3_flt_raddr3_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR3_flt_raddr3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_REMOTE_ADDR0_MASK_UNION
 �ṹ˵��  : FLT_REMOTE_ADDR0_MASK �Ĵ����ṹ���塣��ַƫ����:0x00B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������remote address���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr0_mask : 32; /* bit[0-31]: flt_addr_reverse����0ʱ�����ֽڴ�����У�IPV6��ʾREMOTE ADDRESS_MASK {[103:96],[111:104],[119:112],[127:120]}
                                                          IPV4��ʾREMOTE ADDRESS_MASK {[7:0],[15:8],[23:16],[31:24]}
                                                          flt_addr_reverse����1ʱ�����ֽ�С�����У�IPV6��ʾREMOTE ADDRESS_MASK[127:96]
                                                          IPV4��ʾREMOTE ADDRESS_MASK[31:0] */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR0_MASK_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR0_MASK_flt_raddr0_mask_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR0_MASK_flt_raddr0_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_REMOTE_ADDR1_MASK_UNION
 �ṹ˵��  : FLT_REMOTE_ADDR1_MASK �Ĵ����ṹ���塣��ַƫ����:0x00B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������remote address���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr1_mask : 32; /* bit[0-31]: flt_addr_reverse����0ʱ�����ֽڴ�����У�IPV6��ʾREMOTE ADDRESS_MASK {[71:64],[79:72],[87:80],[95:88]}
                                                          flt_addr_reverse����1ʱ�����ֽ�С�����У�IPV6��ʾREMOTE ADDRESS_MASK[95:64]
                                                          IPV4���� */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR1_MASK_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR1_MASK_flt_raddr1_mask_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR1_MASK_flt_raddr1_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_REMOTE_ADDR2_MASK_UNION
 �ṹ˵��  : FLT_REMOTE_ADDR2_MASK �Ĵ����ṹ���塣��ַƫ����:0x00B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������remote address���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr2_mask : 32; /* bit[0-31]: flt_addr_reverse����0ʱ�����ֽڴ�����У�IPV6��ʾREMOTE ADDRESS_MASK {[39:32],[47:40],[55:48],[63:56]}
                                                          flt_addr_reverse����1ʱ�����ֽ�С�����У�IPV6��ʾREMOTE ADDRESS_MASK[63:32]
                                                          IPV4���� */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR2_MASK_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR2_MASK_flt_raddr2_mask_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR2_MASK_flt_raddr2_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_REMOTE_ADDR3_MASK_UNION
 �ṹ˵��  : FLT_REMOTE_ADDR3_MASK �Ĵ����ṹ���塣��ַƫ����:0x00BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������remote address���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_raddr3_mask : 32; /* bit[0-31]: flt_addr_reverse����0ʱ�����ֽڴ�����У�IPV6��ʾREMOTE ADDRESS {[7:0],[15:8],[23:16],[31:24]}
                                                          flt_addr_reverse����1ʱ�����ֽ�С�����У�IPV6��ʾREMOTE ADDRESS[31:0]
                                                          IPV4���� */
    } reg;
} SOC_IPF_FLT_REMOTE_ADDR3_MASK_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_ADDR3_MASK_flt_raddr3_mask_START  (0)
#define SOC_IPF_FLT_REMOTE_ADDR3_MASK_flt_raddr3_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_LOCAL_PORT_UNION
 �ṹ˵��  : FLT_LOCAL_PORT �Ĵ����ṹ���塣��ַƫ����:0x00C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���˱�LOCAL PORT�������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_local_port_low  : 16; /* bit[0-15] : ���˱�LOCAL PORT�����ޣ��ֽ�С������ */
        unsigned int  flt_local_port_high : 16; /* bit[16-31]: ���˱�LOCAL PORT�����ޣ��ֽ�С������ */
    } reg;
} SOC_IPF_FLT_LOCAL_PORT_UNION;
#endif
#define SOC_IPF_FLT_LOCAL_PORT_flt_local_port_low_START   (0)
#define SOC_IPF_FLT_LOCAL_PORT_flt_local_port_low_END     (15)
#define SOC_IPF_FLT_LOCAL_PORT_flt_local_port_high_START  (16)
#define SOC_IPF_FLT_LOCAL_PORT_flt_local_port_high_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_REMOTE_PORT_UNION
 �ṹ˵��  : FLT_REMOTE_PORT �Ĵ����ṹ���塣��ַƫ����:0x00C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���˱�REMOTE PORT�������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_remote_port_low  : 16; /* bit[0-15] : ���˱�REMOTE PORT�����ޣ��ֽ�С������ */
        unsigned int  flt_remote_port_high : 16; /* bit[16-31]: ���˱�REMOTE PORT�����ޣ��ֽ�С������ */
    } reg;
} SOC_IPF_FLT_REMOTE_PORT_UNION;
#endif
#define SOC_IPF_FLT_REMOTE_PORT_flt_remote_port_low_START   (0)
#define SOC_IPF_FLT_REMOTE_PORT_flt_remote_port_low_END     (15)
#define SOC_IPF_FLT_REMOTE_PORT_flt_remote_port_high_START  (16)
#define SOC_IPF_FLT_REMOTE_PORT_flt_remote_port_high_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_TRAFFIC_CLASS_UNION
 �ṹ˵��  : FLT_TRAFFIC_CLASS �Ĵ����ṹ���塣��ַƫ����:0x00C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���˱�ҵ��ȼ������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_traffic_class      : 8;  /* bit[0-7]  : ������ҵ��ȼ�������ֵ
                                                                  IPV4Ϊtype of service��
                                                                  IPV6Ϊtraffic class�� */
        unsigned int  flt_traffic_class_mask : 8;  /* bit[8-15] : ������ҵ��ȼ�����������ֵ */
        unsigned int  reserved               : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_IPF_FLT_TRAFFIC_CLASS_UNION;
#endif
#define SOC_IPF_FLT_TRAFFIC_CLASS_flt_traffic_class_START       (0)
#define SOC_IPF_FLT_TRAFFIC_CLASS_flt_traffic_class_END         (7)
#define SOC_IPF_FLT_TRAFFIC_CLASS_flt_traffic_class_mask_START  (8)
#define SOC_IPF_FLT_TRAFFIC_CLASS_flt_traffic_class_mask_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_LADD_MASK_UNION
 �ṹ˵��  : FLT_LADD_MASK �Ĵ����ṹ���塣��ַƫ����:0x00CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������local address mask�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_local_addr_mask : 7;  /* bit[0-6] : ������local address����������ֵ��IPV4��������ʾ32λ��ַ����ӵ�λ����λ0�ĸ�����
                                                              ����
                                                              flt_local_addr_mask=7'b0��ʾ�������0xffffffff��
                                                              flt_local_addr_mask=7'h4��ʾ�������0xfffffff0��
                                                              flt_local_addr_mask=7'h8��ʾ�������0xffffff00��
                                                              IPV6��������ʾ128λ��ַ����ӵ�λ����λ0�ĸ����� */
        unsigned int  reserved            : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_IPF_FLT_LADD_MASK_UNION;
#endif
#define SOC_IPF_FLT_LADD_MASK_flt_local_addr_mask_START  (0)
#define SOC_IPF_FLT_LADD_MASK_flt_local_addr_mask_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_NEXT_HEADER_UNION
 �ṹ˵��  : FLT_NEXT_HEADER �Ĵ����ṹ���塣��ַƫ����:0x00D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������Э�����������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_next_header : 8;  /* bit[0-7] : ������Э������������ֵ
                                                          IPV4Ϊprotocol��
                                                          IPV6Ϊnext header�� */
        unsigned int  reserved        : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_FLT_NEXT_HEADER_UNION;
#endif
#define SOC_IPF_FLT_NEXT_HEADER_flt_next_header_START  (0)
#define SOC_IPF_FLT_NEXT_HEADER_flt_next_header_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_FLOW_LABEL_UNION
 �ṹ˵��  : FLT_FLOW_LABEL �Ĵ����ṹ���塣��ַƫ����:0x00D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����������ǩ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_fow_lable : 20; /* bit[0-19] : ���˱�����ǩ���üĴ������ֽ�С������ */
        unsigned int  reserved      : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_IPF_FLT_FLOW_LABEL_UNION;
#endif
#define SOC_IPF_FLT_FLOW_LABEL_flt_fow_lable_START  (0)
#define SOC_IPF_FLT_FLOW_LABEL_flt_fow_lable_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_ICMP_UNION
 �ṹ˵��  : FLT_ICMP �Ĵ����ṹ���塣��ַƫ����:0x00D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ICMP���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_type : 8;  /* bit[0-7]  : ������type������ֵ */
        unsigned int  reserved_0: 8;  /* bit[8-15] : ������ */
        unsigned int  flt_code : 8;  /* bit[16-23]: ������code������ֵ */
        unsigned int  reserved_1: 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_IPF_FLT_ICMP_UNION;
#endif
#define SOC_IPF_FLT_ICMP_flt_type_START  (0)
#define SOC_IPF_FLT_ICMP_flt_type_END    (7)
#define SOC_IPF_FLT_ICMP_flt_code_START  (16)
#define SOC_IPF_FLT_ICMP_flt_code_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_CHAIN_UNION
 �ṹ˵��  : FLT_CHAIN �Ĵ����ṹ���塣��ַƫ����:0x00DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���������������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_next_index : 9;  /* bit[0-8]  : ��һ����������Ӧ��index */
        unsigned int  reserved_0     : 7;  /* bit[9-15] : ������ */
        unsigned int  flt_pri        : 9;  /* bit[16-24]: ���������ȼ���flt_pri��ֵԽС���ȼ�Խ�� */
        unsigned int  reserved_1     : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_IPF_FLT_CHAIN_UNION;
#endif
#define SOC_IPF_FLT_CHAIN_flt_next_index_START  (0)
#define SOC_IPF_FLT_CHAIN_flt_next_index_END    (8)
#define SOC_IPF_FLT_CHAIN_flt_pri_START         (16)
#define SOC_IPF_FLT_CHAIN_flt_pri_END           (24)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_SPI_UNION
 �ṹ˵��  : FLT_SPI �Ĵ����ṹ���塣��ַƫ����:0x00E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������SPI���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_spi : 32; /* bit[0-31]: ������SPI������ֵ���ֽ�С������ */
    } reg;
} SOC_IPF_FLT_SPI_UNION;
#endif
#define SOC_IPF_FLT_SPI_flt_spi_START  (0)
#define SOC_IPF_FLT_SPI_flt_spi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_FLT_RULE_CTRL_UNION
 �ṹ˵��  : FLT_RULE_CTRL �Ĵ����ṹ���塣��ַƫ����:0x00E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����������������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_en       : 1;  /* bit[0]    : ������ʹ�� */
        unsigned int  flt_type     : 1;  /* bit[1]    : ����������
                                                        0��IPV4
                                                        1��IPV6 */
        unsigned int  reserved_0   : 2;  /* bit[2-3]  : ������ */
        unsigned int  flt_spi_en   : 1;  /* bit[4]    : ������SPI��ʹ�� */
        unsigned int  flt_code_en  : 1;  /* bit[5]    : ������ICMP CODE��ʹ�� */
        unsigned int  flt_type_en  : 1;  /* bit[6]    : ������ICMP TYPE��ʹ�� */
        unsigned int  flt_fl_en    : 1;  /* bit[7]    : ������IPV6 FLOW LABLE��ʹ�ܡ�IPV4��������λ���� */
        unsigned int  flt_nh_en    : 1;  /* bit[8]    : ������NEXT HEADER��ʹ��
                                                        IPV4Ϊprotocol��ʹ��
                                                        IPV6Ϊnext header��ʹ�� */
        unsigned int  flt_tos_en   : 1;  /* bit[9]    : ������TRAFFIC CLASS��ʹ��
                                                        IPV4Ϊtype of service��ʹ��
                                                        IPV6Ϊtraffic class��ʹ�� */
        unsigned int  flt_rport_en : 1;  /* bit[10]   : ������remote port��ʹ�� */
        unsigned int  flt_lport_en : 1;  /* bit[11]   : ������local port��ʹ�� */
        unsigned int  flt_raddr_en : 1;  /* bit[12]   : ������remote address��ʹ�� */
        unsigned int  flt_laddr_en : 1;  /* bit[13]   : ������local address��ʹ�� */
        unsigned int  reserved_1   : 2;  /* bit[14-15]: ������ */
        unsigned int  flt_bear_id  : 6;  /* bit[16-21]: ��������Ӧ�ĳ��غ� */
        unsigned int  reserved_2   : 10; /* bit[22-31]: ������ */
    } reg;
} SOC_IPF_FLT_RULE_CTRL_UNION;
#endif
#define SOC_IPF_FLT_RULE_CTRL_flt_en_START        (0)
#define SOC_IPF_FLT_RULE_CTRL_flt_en_END          (0)
#define SOC_IPF_FLT_RULE_CTRL_flt_type_START      (1)
#define SOC_IPF_FLT_RULE_CTRL_flt_type_END        (1)
#define SOC_IPF_FLT_RULE_CTRL_flt_spi_en_START    (4)
#define SOC_IPF_FLT_RULE_CTRL_flt_spi_en_END      (4)
#define SOC_IPF_FLT_RULE_CTRL_flt_code_en_START   (5)
#define SOC_IPF_FLT_RULE_CTRL_flt_code_en_END     (5)
#define SOC_IPF_FLT_RULE_CTRL_flt_type_en_START   (6)
#define SOC_IPF_FLT_RULE_CTRL_flt_type_en_END     (6)
#define SOC_IPF_FLT_RULE_CTRL_flt_fl_en_START     (7)
#define SOC_IPF_FLT_RULE_CTRL_flt_fl_en_END       (7)
#define SOC_IPF_FLT_RULE_CTRL_flt_nh_en_START     (8)
#define SOC_IPF_FLT_RULE_CTRL_flt_nh_en_END       (8)
#define SOC_IPF_FLT_RULE_CTRL_flt_tos_en_START    (9)
#define SOC_IPF_FLT_RULE_CTRL_flt_tos_en_END      (9)
#define SOC_IPF_FLT_RULE_CTRL_flt_rport_en_START  (10)
#define SOC_IPF_FLT_RULE_CTRL_flt_rport_en_END    (10)
#define SOC_IPF_FLT_RULE_CTRL_flt_lport_en_START  (11)
#define SOC_IPF_FLT_RULE_CTRL_flt_lport_en_END    (11)
#define SOC_IPF_FLT_RULE_CTRL_flt_raddr_en_START  (12)
#define SOC_IPF_FLT_RULE_CTRL_flt_raddr_en_END    (12)
#define SOC_IPF_FLT_RULE_CTRL_flt_laddr_en_START  (13)
#define SOC_IPF_FLT_RULE_CTRL_flt_laddr_en_END    (13)
#define SOC_IPF_FLT_RULE_CTRL_flt_bear_id_START   (16)
#define SOC_IPF_FLT_RULE_CTRL_flt_bear_id_END     (21)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_CTRL_UNION
 �ṹ˵��  : CH0_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_mod        : 2;  /* bit[0-1]  : ģʽ���ƼĴ���
                                                         00����������
                                                         01��ֻ����
                                                         10 or 11��ֻ����
                                                         ��mm_en����λ��Чʱ���������Ч�� */
        unsigned int  ul_endian     : 1;  /* bit[2]    : �������ݴ�С��ָʾ
                                                         0��big endian
                                                         1��little endian */
        unsigned int  ul_data_chain : 1;  /* bit[3]    : �����Ƿ�Ϊ���� */
        unsigned int  ul_bdq_clr    : 1;  /* bit[4]    : ���ж�����������ź�,
                                                         �������Ϊ1��BD,��дָ������.�˼Ĵ����߼����� */
        unsigned int  ul_rdq_clr    : 1;  /* bit[5]    : ���ж�����������ź�,
                                                         �������Ϊ1��RD��дָ������.�˼Ĵ����߼����� */
        unsigned int  reserved      : 10; /* bit[6-15] : ���� */
        unsigned int  ul_wrr_value  : 16; /* bit[16-31]: WRRֵ����λ�ֽڡ�
                                                         �������������ΪWRR����ģʽ�������üĴ�������Ϊ���з����Ȩ�ء���������������ul_wrr_value�ں����Ӧ���С���������û������������������е����С� */
    } reg;
} SOC_IPF_CH0_CTRL_UNION;
#endif
#define SOC_IPF_CH0_CTRL_ul_mod_START         (0)
#define SOC_IPF_CH0_CTRL_ul_mod_END           (1)
#define SOC_IPF_CH0_CTRL_ul_endian_START      (2)
#define SOC_IPF_CH0_CTRL_ul_endian_END        (2)
#define SOC_IPF_CH0_CTRL_ul_data_chain_START  (3)
#define SOC_IPF_CH0_CTRL_ul_data_chain_END    (3)
#define SOC_IPF_CH0_CTRL_ul_bdq_clr_START     (4)
#define SOC_IPF_CH0_CTRL_ul_bdq_clr_END       (4)
#define SOC_IPF_CH0_CTRL_ul_rdq_clr_START     (5)
#define SOC_IPF_CH0_CTRL_ul_rdq_clr_END       (5)
#define SOC_IPF_CH0_CTRL_ul_wrr_value_START   (16)
#define SOC_IPF_CH0_CTRL_ul_wrr_value_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_STATE_UNION
 �ṹ˵��  : CH0_STATE �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000014�����:32
 �Ĵ���˵��: ����ͨ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_busy             : 1;  /* bit[0]    : ����busy״ָ̬ʾ�Ĵ��� */
        unsigned int  ul_rdq_full         : 1;  /* bit[1]    : ����RDQ��״ָ̬ʾ�Ĵ��� */
        unsigned int  ul_rdq_empty        : 1;  /* bit[2]    : ����RDQ��״ָ̬ʾ�Ĵ��� */
        unsigned int  ul_bdq_full         : 1;  /* bit[3]    : ����BDQ��״ָ̬ʾ�Ĵ��� */
        unsigned int  ul_bdq_empty        : 1;  /* bit[4]    : ����BDQ��״ָ̬ʾ�Ĵ��� */
        unsigned int  reserved_0          : 3;  /* bit[5-7]  : ���� */
        unsigned int  ul_rdq_rptr_invalid : 1;  /* bit[8]    : ����RDQ��ָ����Ч����ʾ������õ�RDQ��ָ�����RDQ SIZE */
        unsigned int  ul_bdq_wptr_invalid : 1;  /* bit[9]    : ����BDQдָ����Ч����ʾ������õ�BDQдָ�����BDQ SIZE */
        unsigned int  reserved_1          : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_IPF_CH0_STATE_UNION;
#endif
#define SOC_IPF_CH0_STATE_ul_busy_START              (0)
#define SOC_IPF_CH0_STATE_ul_busy_END                (0)
#define SOC_IPF_CH0_STATE_ul_rdq_full_START          (1)
#define SOC_IPF_CH0_STATE_ul_rdq_full_END            (1)
#define SOC_IPF_CH0_STATE_ul_rdq_empty_START         (2)
#define SOC_IPF_CH0_STATE_ul_rdq_empty_END           (2)
#define SOC_IPF_CH0_STATE_ul_bdq_full_START          (3)
#define SOC_IPF_CH0_STATE_ul_bdq_full_END            (3)
#define SOC_IPF_CH0_STATE_ul_bdq_empty_START         (4)
#define SOC_IPF_CH0_STATE_ul_bdq_empty_END           (4)
#define SOC_IPF_CH0_STATE_ul_rdq_rptr_invalid_START  (8)
#define SOC_IPF_CH0_STATE_ul_rdq_rptr_invalid_END    (8)
#define SOC_IPF_CH0_STATE_ul_bdq_wptr_invalid_START  (9)
#define SOC_IPF_CH0_STATE_ul_bdq_wptr_invalid_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_BDQ_BADDR_UNION
 �ṹ˵��  : CH0_BDQ_BADDR �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��BDQ��ʼ��ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_baddr : 32; /* bit[0-31]: ����ͨ��BDQ��ʼ��ַ,8�ֽڶ��� */
    } reg;
} SOC_IPF_CH0_BDQ_BADDR_UNION;
#endif
#define SOC_IPF_CH0_BDQ_BADDR_ul_bdq_baddr_START  (0)
#define SOC_IPF_CH0_BDQ_BADDR_ul_bdq_baddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_BDQ_SIZE_UNION
 �ṹ˵��  : CH0_BDQ_SIZE �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��BDQ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_size : 8;  /* bit[0-7] : ����ͨ��BDQ��� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_CH0_BDQ_SIZE_UNION;
#endif
#define SOC_IPF_CH0_BDQ_SIZE_ul_bdq_size_START  (0)
#define SOC_IPF_CH0_BDQ_SIZE_ul_bdq_size_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_BDQ_WPTR_UNION
 �ṹ˵��  : CH0_BDQ_WPTR �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��BDQдָ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_wptr : 8;  /* bit[0-7] : ����ͨ��BDQдָ�룬���ܴ�������BDQ��� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_CH0_BDQ_WPTR_UNION;
#endif
#define SOC_IPF_CH0_BDQ_WPTR_ul_bdq_wptr_START  (0)
#define SOC_IPF_CH0_BDQ_WPTR_ul_bdq_wptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_BDQ_RPTR_UNION
 �ṹ˵��  : CH0_BDQ_RPTR �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��BDQ��ָ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_rptr : 8;  /* bit[0-7] : ����ͨ��BDQ��ָ�� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_CH0_BDQ_RPTR_UNION;
#endif
#define SOC_IPF_CH0_BDQ_RPTR_ul_bdq_rptr_START  (0)
#define SOC_IPF_CH0_BDQ_RPTR_ul_bdq_rptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_BDQ_WADDR_UNION
 �ṹ˵��  : CH0_BDQ_WADDR �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��BDQд��ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_waddr : 32; /* bit[0-31]: ����ͨ��BDQд��ַ */
    } reg;
} SOC_IPF_CH0_BDQ_WADDR_UNION;
#endif
#define SOC_IPF_CH0_BDQ_WADDR_ul_bdq_waddr_START  (0)
#define SOC_IPF_CH0_BDQ_WADDR_ul_bdq_waddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_BDQ_RADDR_UNION
 �ṹ˵��  : CH0_BDQ_RADDR �Ĵ����ṹ���塣��ַƫ����:0x011C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��BDQ����ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_raddr : 32; /* bit[0-31]: ����ͨ��BDQ����ַ */
    } reg;
} SOC_IPF_CH0_BDQ_RADDR_UNION;
#endif
#define SOC_IPF_CH0_BDQ_RADDR_ul_bdq_raddr_START  (0)
#define SOC_IPF_CH0_BDQ_RADDR_ul_bdq_raddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_RDQ_BADDR_UNION
 �ṹ˵��  : CH0_RDQ_BADDR �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDQ��ʼ��ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rdq_baddr : 32; /* bit[0-31]: ����ͨ��RDQ��ʼ��ַ,8�ֽڶ��� */
    } reg;
} SOC_IPF_CH0_RDQ_BADDR_UNION;
#endif
#define SOC_IPF_CH0_RDQ_BADDR_ul_rdq_baddr_START  (0)
#define SOC_IPF_CH0_RDQ_BADDR_ul_rdq_baddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_RDQ_SIZE_UNION
 �ṹ˵��  : CH0_RDQ_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDQ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rdq_size : 8;  /* bit[0-7] : ����ͨ��RDQ��� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_CH0_RDQ_SIZE_UNION;
#endif
#define SOC_IPF_CH0_RDQ_SIZE_ul_rdq_size_START  (0)
#define SOC_IPF_CH0_RDQ_SIZE_ul_rdq_size_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_RDQ_WPTR_UNION
 �ṹ˵��  : CH0_RDQ_WPTR �Ĵ����ṹ���塣��ַƫ����:0x0128����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDQдָ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rdq_wptr : 8;  /* bit[0-7] : ����ͨ��RDQдָ�� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_CH0_RDQ_WPTR_UNION;
#endif
#define SOC_IPF_CH0_RDQ_WPTR_ul_rdq_wptr_START  (0)
#define SOC_IPF_CH0_RDQ_WPTR_ul_rdq_wptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_RDQ_RPTR_UNION
 �ṹ˵��  : CH0_RDQ_RPTR �Ĵ����ṹ���塣��ַƫ����:0x012C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDQ��ָ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rdq_rptr : 8;  /* bit[0-7] : ����ͨ��RDQ��ָ�룬���ܴ�������RDQ��� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_CH0_RDQ_RPTR_UNION;
#endif
#define SOC_IPF_CH0_RDQ_RPTR_ul_rdq_rptr_START  (0)
#define SOC_IPF_CH0_RDQ_RPTR_ul_rdq_rptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_RDQ_WADDR_UNION
 �ṹ˵��  : CH0_RDQ_WADDR �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDQд��ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rdq_waddr : 32; /* bit[0-31]: ����ͨ��RDQд��ַ */
    } reg;
} SOC_IPF_CH0_RDQ_WADDR_UNION;
#endif
#define SOC_IPF_CH0_RDQ_WADDR_ul_rdq_waddr_START  (0)
#define SOC_IPF_CH0_RDQ_WADDR_ul_rdq_waddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_RDQ_RADDR_UNION
 �ṹ˵��  : CH0_RDQ_RADDR �Ĵ����ṹ���塣��ַƫ����:0x0134����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDQ����ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_rdq_raddr : 32; /* bit[0-31]: ����ͨ��RDQ����ַ */
    } reg;
} SOC_IPF_CH0_RDQ_RADDR_UNION;
#endif
#define SOC_IPF_CH0_RDQ_RADDR_ul_rdq_raddr_START  (0)
#define SOC_IPF_CH0_RDQ_RADDR_ul_rdq_raddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_DQ_DEPTH_UNION
 �ṹ˵��  : CH0_DQ_DEPTH �Ĵ����ṹ���塣��ַƫ����:0x0138����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ���������ָʾ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_bdq_depth : 9;  /* bit[0-8]  : ����BDQ��ǰ��ȼĴ���,��ʾBDQ��BD�ĸ���.����0��ʾ��,����(ul_bdq_size+1)��ʾ�� */
        unsigned int  reserved_0   : 7;  /* bit[9-15] : ����. */
        unsigned int  ul_rdq_depth : 9;  /* bit[16-24]: ����RDQ��ǰ��ȼĴ���,��ʾRDQ��RD�ĸ���.����0��ʾ��,����(ul_rdq_size+1)��ʾ�� */
        unsigned int  reserved_1   : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_IPF_CH0_DQ_DEPTH_UNION;
#endif
#define SOC_IPF_CH0_DQ_DEPTH_ul_bdq_depth_START  (0)
#define SOC_IPF_CH0_DQ_DEPTH_ul_bdq_depth_END    (8)
#define SOC_IPF_CH0_DQ_DEPTH_ul_rdq_depth_START  (16)
#define SOC_IPF_CH0_DQ_DEPTH_ul_rdq_depth_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_CTRL_UNION
 �ṹ˵��  : CH1_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0150����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_mod        : 2;  /* bit[0-1]  : ģʽ���ƼĴ���
                                                         00����������
                                                         01��ֻ����
                                                         10 or 11��ֻ������
                                                         ��mm_en����λ��Чʱ���������Ч�� */
        unsigned int  dl_endian     : 1;  /* bit[2]    : �������ݴ�С��ָʾ
                                                         0��big endian
                                                         1��little endian */
        unsigned int  dl_data_chain : 1;  /* bit[3]    : �����Ƿ�Ϊ���� */
        unsigned int  dl_bdq_clr    : 1;  /* bit[4]    : ���ж�����������ź�,
                                                         �������Ϊ1��BD��дָ������.�˼Ĵ����߼����� */
        unsigned int  dl_rdq_clr    : 1;  /* bit[5]    : ���ж�����������ź�,
                                                         �������Ϊ1��RD��дָ������.�˼Ĵ����߼����� */
        unsigned int  reserved      : 10; /* bit[6-15] : ���� */
        unsigned int  dl_wrr_value  : 16; /* bit[16-31]: WRRֵ����λ�ֽڡ�
                                                         �������������ΪWRR����ģʽ�������üĴ�������Ϊ���з����Ȩ�ء���������������dl_wrr_value�ں����Ӧ���С���������û������������������е����С� */
    } reg;
} SOC_IPF_CH1_CTRL_UNION;
#endif
#define SOC_IPF_CH1_CTRL_dl_mod_START         (0)
#define SOC_IPF_CH1_CTRL_dl_mod_END           (1)
#define SOC_IPF_CH1_CTRL_dl_endian_START      (2)
#define SOC_IPF_CH1_CTRL_dl_endian_END        (2)
#define SOC_IPF_CH1_CTRL_dl_data_chain_START  (3)
#define SOC_IPF_CH1_CTRL_dl_data_chain_END    (3)
#define SOC_IPF_CH1_CTRL_dl_bdq_clr_START     (4)
#define SOC_IPF_CH1_CTRL_dl_bdq_clr_END       (4)
#define SOC_IPF_CH1_CTRL_dl_rdq_clr_START     (5)
#define SOC_IPF_CH1_CTRL_dl_rdq_clr_END       (5)
#define SOC_IPF_CH1_CTRL_dl_wrr_value_START   (16)
#define SOC_IPF_CH1_CTRL_dl_wrr_value_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_STATE_UNION
 �ṹ˵��  : CH1_STATE �Ĵ����ṹ���塣��ַƫ����:0x0154����ֵ:0x00000014�����:32
 �Ĵ���˵��: ����ͨ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_busy             : 1;  /* bit[0]    : ����busy״ָ̬ʾ�Ĵ��� */
        unsigned int  dl_rdq_full         : 1;  /* bit[1]    : ����RDQ��״ָ̬ʾ�Ĵ��� */
        unsigned int  dl_rdq_empty        : 1;  /* bit[2]    : ����RDQ��״ָ̬ʾ�Ĵ��� */
        unsigned int  dl_bdq_full         : 1;  /* bit[3]    : ����BDQ��״ָ̬ʾ�Ĵ��� */
        unsigned int  dl_bdq_empty        : 1;  /* bit[4]    : ����BDQ��״ָ̬ʾ�Ĵ��� */
        unsigned int  reserved_0          : 3;  /* bit[5-7]  : ���� */
        unsigned int  dl_rdq_rptr_invalid : 1;  /* bit[8]    : ����RDQ��ָ����Ч����ʾ������õ�RDQ��ָ�����RDQ SIZE */
        unsigned int  dl_bdq_wptr_invalid : 1;  /* bit[9]    : ����BDQдָ����Ч����ʾ������õ�BDQдָ�����BDQ SIZE */
        unsigned int  reserved_1          : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_IPF_CH1_STATE_UNION;
#endif
#define SOC_IPF_CH1_STATE_dl_busy_START              (0)
#define SOC_IPF_CH1_STATE_dl_busy_END                (0)
#define SOC_IPF_CH1_STATE_dl_rdq_full_START          (1)
#define SOC_IPF_CH1_STATE_dl_rdq_full_END            (1)
#define SOC_IPF_CH1_STATE_dl_rdq_empty_START         (2)
#define SOC_IPF_CH1_STATE_dl_rdq_empty_END           (2)
#define SOC_IPF_CH1_STATE_dl_bdq_full_START          (3)
#define SOC_IPF_CH1_STATE_dl_bdq_full_END            (3)
#define SOC_IPF_CH1_STATE_dl_bdq_empty_START         (4)
#define SOC_IPF_CH1_STATE_dl_bdq_empty_END           (4)
#define SOC_IPF_CH1_STATE_dl_rdq_rptr_invalid_START  (8)
#define SOC_IPF_CH1_STATE_dl_rdq_rptr_invalid_END    (8)
#define SOC_IPF_CH1_STATE_dl_bdq_wptr_invalid_START  (9)
#define SOC_IPF_CH1_STATE_dl_bdq_wptr_invalid_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_BDQ_BADDR_UNION
 �ṹ˵��  : CH1_BDQ_BADDR �Ĵ����ṹ���塣��ַƫ����:0x0158����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��BDQ��ʼ��ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_baddr : 32; /* bit[0-31]: ����ͨ��BDQ��ʼ��ַ,8�ֽڶ��� */
    } reg;
} SOC_IPF_CH1_BDQ_BADDR_UNION;
#endif
#define SOC_IPF_CH1_BDQ_BADDR_dl_bdq_baddr_START  (0)
#define SOC_IPF_CH1_BDQ_BADDR_dl_bdq_baddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_BDQ_SIZE_UNION
 �ṹ˵��  : CH1_BDQ_SIZE �Ĵ����ṹ���塣��ַƫ����:0x015C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��BDQ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_size : 8;  /* bit[0-7] : ����ͨ��BDQ��� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_CH1_BDQ_SIZE_UNION;
#endif
#define SOC_IPF_CH1_BDQ_SIZE_dl_bdq_size_START  (0)
#define SOC_IPF_CH1_BDQ_SIZE_dl_bdq_size_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_BDQ_WPTR_UNION
 �ṹ˵��  : CH1_BDQ_WPTR �Ĵ����ṹ���塣��ַƫ����:0x0160����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��BDQдָ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_wptr : 8;  /* bit[0-7] : ����ͨ��BDQдָ�룬���ܴ�������BDQ��� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_CH1_BDQ_WPTR_UNION;
#endif
#define SOC_IPF_CH1_BDQ_WPTR_dl_bdq_wptr_START  (0)
#define SOC_IPF_CH1_BDQ_WPTR_dl_bdq_wptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_BDQ_RPTR_UNION
 �ṹ˵��  : CH1_BDQ_RPTR �Ĵ����ṹ���塣��ַƫ����:0x0164����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��BDQ��ָ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_rptr : 8;  /* bit[0-7] : ����ͨ��BDQ��ָ�� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_CH1_BDQ_RPTR_UNION;
#endif
#define SOC_IPF_CH1_BDQ_RPTR_dl_bdq_rptr_START  (0)
#define SOC_IPF_CH1_BDQ_RPTR_dl_bdq_rptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_BDQ_WADDR_UNION
 �ṹ˵��  : CH1_BDQ_WADDR �Ĵ����ṹ���塣��ַƫ����:0x0168����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��BDQд��ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_waddr : 32; /* bit[0-31]: ����ͨ��BDQд��ַ */
    } reg;
} SOC_IPF_CH1_BDQ_WADDR_UNION;
#endif
#define SOC_IPF_CH1_BDQ_WADDR_dl_bdq_waddr_START  (0)
#define SOC_IPF_CH1_BDQ_WADDR_dl_bdq_waddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_BDQ_RADDR_UNION
 �ṹ˵��  : CH1_BDQ_RADDR �Ĵ����ṹ���塣��ַƫ����:0x016C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��BDQ����ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_raddr : 32; /* bit[0-31]: ����ͨ��BDQ����ַ */
    } reg;
} SOC_IPF_CH1_BDQ_RADDR_UNION;
#endif
#define SOC_IPF_CH1_BDQ_RADDR_dl_bdq_raddr_START  (0)
#define SOC_IPF_CH1_BDQ_RADDR_dl_bdq_raddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_RDQ_BADDR_UNION
 �ṹ˵��  : CH1_RDQ_BADDR �Ĵ����ṹ���塣��ַƫ����:0x0170����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDQ��ʼ��ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_rdq_baddr : 32; /* bit[0-31]: ����ͨ��RDQ��ʼ��ַ,8�ֽڶ��� */
    } reg;
} SOC_IPF_CH1_RDQ_BADDR_UNION;
#endif
#define SOC_IPF_CH1_RDQ_BADDR_dl_rdq_baddr_START  (0)
#define SOC_IPF_CH1_RDQ_BADDR_dl_rdq_baddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_RDQ_SIZE_UNION
 �ṹ˵��  : CH1_RDQ_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0174����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDQ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_rdq_size : 8;  /* bit[0-7] : ����ͨ��RDQ��� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_CH1_RDQ_SIZE_UNION;
#endif
#define SOC_IPF_CH1_RDQ_SIZE_dl_rdq_size_START  (0)
#define SOC_IPF_CH1_RDQ_SIZE_dl_rdq_size_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_RDQ_WPTR_UNION
 �ṹ˵��  : CH1_RDQ_WPTR �Ĵ����ṹ���塣��ַƫ����:0x0178����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDQдָ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_rdq_wptr : 8;  /* bit[0-7] : ����ͨ��RDQдָ�� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_CH1_RDQ_WPTR_UNION;
#endif
#define SOC_IPF_CH1_RDQ_WPTR_dl_rdq_wptr_START  (0)
#define SOC_IPF_CH1_RDQ_WPTR_dl_rdq_wptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_RDQ_RPTR_UNION
 �ṹ˵��  : CH1_RDQ_RPTR �Ĵ����ṹ���塣��ַƫ����:0x017C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDQ��ָ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_rdq_rptr : 8;  /* bit[0-7] : ����ͨ��RDQ��ָ�룬���ܴ�������RDQ��� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IPF_CH1_RDQ_RPTR_UNION;
#endif
#define SOC_IPF_CH1_RDQ_RPTR_dl_rdq_rptr_START  (0)
#define SOC_IPF_CH1_RDQ_RPTR_dl_rdq_rptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_RDQ_WADDR_UNION
 �ṹ˵��  : CH1_RDQ_WADDR �Ĵ����ṹ���塣��ַƫ����:0x0180����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDQд��ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_rdq_waddr : 32; /* bit[0-31]: ����ͨ��RDQд��ַ */
    } reg;
} SOC_IPF_CH1_RDQ_WADDR_UNION;
#endif
#define SOC_IPF_CH1_RDQ_WADDR_dl_rdq_waddr_START  (0)
#define SOC_IPF_CH1_RDQ_WADDR_dl_rdq_waddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_RDQ_RADDR_UNION
 �ṹ˵��  : CH1_RDQ_RADDR �Ĵ����ṹ���塣��ַƫ����:0x0184����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDQ����ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_rdq_raddr : 32; /* bit[0-31]: ����ͨ��RDQ����ַ */
    } reg;
} SOC_IPF_CH1_RDQ_RADDR_UNION;
#endif
#define SOC_IPF_CH1_RDQ_RADDR_dl_rdq_raddr_START  (0)
#define SOC_IPF_CH1_RDQ_RADDR_dl_rdq_raddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_DQ_DEPTH_UNION
 �ṹ˵��  : CH1_DQ_DEPTH �Ĵ����ṹ���塣��ַƫ����:0x0188����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ���������ָʾ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_bdq_depth : 9;  /* bit[0-8]  : ����BDQ��ǰ��ȼĴ���,��ʾBDQ��BD�ĸ���.����0��ʾ��,����(dl_bdq_size+1)��ʾ�� */
        unsigned int  reserved_0   : 7;  /* bit[9-15] : ����. */
        unsigned int  dl_rdq_depth : 9;  /* bit[16-24]: ����RDQ��ǰ��ȼĴ���,��ʾRDQ��RD�ĸ���.����0��ʾ��,����(dl_rdq_size+1)��ʾ�� */
        unsigned int  reserved_1   : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_IPF_CH1_DQ_DEPTH_UNION;
#endif
#define SOC_IPF_CH1_DQ_DEPTH_dl_bdq_depth_START  (0)
#define SOC_IPF_CH1_DQ_DEPTH_dl_bdq_depth_END    (8)
#define SOC_IPF_CH1_DQ_DEPTH_dl_rdq_depth_START  (16)
#define SOC_IPF_CH1_DQ_DEPTH_dl_rdq_depth_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_ADQ_CTRL_UNION
 �ṹ˵��  : CH0_ADQ_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0204����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq_en        : 2;  /* bit[0-1]  : ����ͨ��ADQ0ʹ�ܡ�
                                                            00����ʾ����ͨ����ʹ��ADQ��
                                                            01����ʾ����ͨ��ʹ��ADQ0��
                                                            1x����ʾ����ͨ��ʹ��ADQ0��ADQ1�� */
        unsigned int  ul_adq0_size_sel : 2;  /* bit[2-3]  : ����ADQ0��С(ul_adq0_size)ѡ��Ĵ�����
                                                            00����ʾADQ0�Ĵ�СΪ32��
                                                            01����ʾADQ0�Ĵ�СΪ64��
                                                            10����ʾADQ0�Ĵ�СΪ128��
                                                            11����ʾADQ0�Ĵ�СΪ256�� */
        unsigned int  ul_adq1_size_sel : 2;  /* bit[4-5]  : ����ADQ1��С(ul_adq1_size)ѡ��Ĵ�����
                                                            00����ʾADQ1�Ĵ�СΪ32��
                                                            01����ʾADQ1�Ĵ�СΪ64��
                                                            10����ʾADQ1�Ĵ�СΪ128��
                                                            11����ʾADQ1�Ĵ�СΪ256�� */
        unsigned int  reserved         : 10; /* bit[6-15] : ���� */
        unsigned int  ul_adq_plen_th   : 16; /* bit[16-31]: ����ͨ�����ݰ�����ֵ��������ͨ������adq������ʱ�������ǰ���ݰ���С����ֵ��ʹ��adq0��AD������ʹ��adq1��AD */
    } reg;
} SOC_IPF_CH0_ADQ_CTRL_UNION;
#endif
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq_en_START         (0)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq_en_END           (1)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq0_size_sel_START  (2)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq0_size_sel_END    (3)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq1_size_sel_START  (4)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq1_size_sel_END    (5)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq_plen_th_START    (16)
#define SOC_IPF_CH0_ADQ_CTRL_ul_adq_plen_th_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_ADQ0_BASE_UNION
 �ṹ˵��  : CH0_ADQ0_BASE �Ĵ����ṹ���塣��ַƫ����:0x0210����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ0��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq0_base : 32; /* bit[0-31]: ����ͨ��Ŀ�ĵ�ַ���������л�ַ */
    } reg;
} SOC_IPF_CH0_ADQ0_BASE_UNION;
#endif
#define SOC_IPF_CH0_ADQ0_BASE_ul_adq0_base_START  (0)
#define SOC_IPF_CH0_ADQ0_BASE_ul_adq0_base_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_ADQ0_STAT_UNION
 �ṹ˵��  : CH0_ADQ0_STAT �Ĵ����ṹ���塣��ַƫ����:0x0214����ֵ:0x0200�����:32
 �Ĵ���˵��: ����ͨ��ADQ0״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq0_empty        : 1;  /* bit[0]   : ����ADQ0��״ָ̬ʾ�Ĵ��� */
        unsigned int  reserved_0           : 3;  /* bit[1-3] : ����. */
        unsigned int  ul_adq0_rptr_invalid : 1;  /* bit[4]   : ����ADQ0��ָ����Ч����ʾ������õ�ADQ0��ָ�����ADQ0 SIZE */
        unsigned int  ul_adq0_wptr_invalid : 1;  /* bit[5]   : ����ADQ0дָ����Ч����ʾ������õ�ADQ0дָ�����ADQ0 SIZE */
        unsigned int  reserved_1           : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_IPF_CH0_ADQ0_STAT_UNION;
#endif
#define SOC_IPF_CH0_ADQ0_STAT_ul_adq0_empty_START         (0)
#define SOC_IPF_CH0_ADQ0_STAT_ul_adq0_empty_END           (0)
#define SOC_IPF_CH0_ADQ0_STAT_ul_adq0_rptr_invalid_START  (4)
#define SOC_IPF_CH0_ADQ0_STAT_ul_adq0_rptr_invalid_END    (4)
#define SOC_IPF_CH0_ADQ0_STAT_ul_adq0_wptr_invalid_START  (5)
#define SOC_IPF_CH0_ADQ0_STAT_ul_adq0_wptr_invalid_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_ADQ0_WPTR_UNION
 �ṹ˵��  : CH0_ADQ0_WPTR �Ĵ����ṹ���塣��ַƫ����:0x0218����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ0дָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq0_wptr : 8;  /* bit[0-7] : ����ͨ��ADQ0дָ�룬��������ʱдָ����Ҫ���ά���� */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_IPF_CH0_ADQ0_WPTR_UNION;
#endif
#define SOC_IPF_CH0_ADQ0_WPTR_ul_adq0_wptr_START  (0)
#define SOC_IPF_CH0_ADQ0_WPTR_ul_adq0_wptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_ADQ0_RPTR_UNION
 �ṹ˵��  : CH0_ADQ0_RPTR �Ĵ����ṹ���塣��ַƫ����:0x021C����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ0��ָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq0_rptr : 8;  /* bit[0-7] : ����ͨ��ADQ0��ָ�룬��������ʱ��ָ����Ӳ��ά���� */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_IPF_CH0_ADQ0_RPTR_UNION;
#endif
#define SOC_IPF_CH0_ADQ0_RPTR_ul_adq0_rptr_START  (0)
#define SOC_IPF_CH0_ADQ0_RPTR_ul_adq0_rptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_ADQ1_BASE_UNION
 �ṹ˵��  : CH0_ADQ1_BASE �Ĵ����ṹ���塣��ַƫ����:0x0220����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ1��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq1_base : 32; /* bit[0-31]: ����ͨ��Ŀ�ĵ�ַ���������л�ַ */
    } reg;
} SOC_IPF_CH0_ADQ1_BASE_UNION;
#endif
#define SOC_IPF_CH0_ADQ1_BASE_ul_adq1_base_START  (0)
#define SOC_IPF_CH0_ADQ1_BASE_ul_adq1_base_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_ADQ1_STAT_UNION
 �ṹ˵��  : CH0_ADQ1_STAT �Ĵ����ṹ���塣��ַƫ����:0x0224����ֵ:0x0200�����:32
 �Ĵ���˵��: ����ͨ��ADQ1״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq1_empty        : 1;  /* bit[0]   : ����ADQ1��״ָ̬ʾ�Ĵ��� */
        unsigned int  reserved_0           : 3;  /* bit[1-3] : ����. */
        unsigned int  ul_adq1_rptr_invalid : 1;  /* bit[4]   : ����ADQ1��ָ����Ч����ʾ������õ�ADQ1��ָ�����ADQ1 SIZE */
        unsigned int  ul_adq1_wptr_invalid : 1;  /* bit[5]   : ����ADQ1дָ����Ч����ʾ������õ�ADQ1дָ�����ADQ1 SIZE */
        unsigned int  reserved_1           : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_IPF_CH0_ADQ1_STAT_UNION;
#endif
#define SOC_IPF_CH0_ADQ1_STAT_ul_adq1_empty_START         (0)
#define SOC_IPF_CH0_ADQ1_STAT_ul_adq1_empty_END           (0)
#define SOC_IPF_CH0_ADQ1_STAT_ul_adq1_rptr_invalid_START  (4)
#define SOC_IPF_CH0_ADQ1_STAT_ul_adq1_rptr_invalid_END    (4)
#define SOC_IPF_CH0_ADQ1_STAT_ul_adq1_wptr_invalid_START  (5)
#define SOC_IPF_CH0_ADQ1_STAT_ul_adq1_wptr_invalid_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_ADQ1_WPTR_UNION
 �ṹ˵��  : CH0_ADQ1_WPTR �Ĵ����ṹ���塣��ַƫ����:0x0228����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ1дָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq1_wptr : 8;  /* bit[0-7] : ����ͨ��ADQ1дָ�룬��������ʱдָ����Ҫ���ά���� */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_IPF_CH0_ADQ1_WPTR_UNION;
#endif
#define SOC_IPF_CH0_ADQ1_WPTR_ul_adq1_wptr_START  (0)
#define SOC_IPF_CH0_ADQ1_WPTR_ul_adq1_wptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH0_ADQ1_RPTR_UNION
 �ṹ˵��  : CH0_ADQ1_RPTR �Ĵ����ṹ���塣��ַƫ����:0x022C����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ1��ָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ul_adq1_rptr : 8;  /* bit[0-7] : ����ͨ��ADQ1��ָ�룬��������ʱ��ָ����Ӳ��ά���� */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_IPF_CH0_ADQ1_RPTR_UNION;
#endif
#define SOC_IPF_CH0_ADQ1_RPTR_ul_adq1_rptr_START  (0)
#define SOC_IPF_CH0_ADQ1_RPTR_ul_adq1_rptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_ADQ_CTRL_UNION
 �ṹ˵��  : CH1_ADQ_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0284����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq_en        : 2;  /* bit[0-1]  : ����ͨ��ADQ0ʹ�ܡ�
                                                            00����ʾ����ͨ����ʹ��ADQ��
                                                            01����ʾ����ͨ��ʹ��ADQ0��
                                                            1x����ʾ����ͨ��ʹ��ADQ0��ADQ1�� */
        unsigned int  dl_adq0_size_sel : 2;  /* bit[2-3]  : ����ADQ0��С(dl_adq0_size)ѡ��Ĵ�����
                                                            00����ʾADQ0�Ĵ�СΪ32��
                                                            01����ʾADQ0�Ĵ�СΪ64��
                                                            10����ʾADQ0�Ĵ�СΪ128��
                                                            11����ʾADQ0�Ĵ�СΪ256�� */
        unsigned int  dl_adq1_size_sel : 2;  /* bit[4-5]  : ����ADQ1��С(dl_adq1_size)ѡ��Ĵ�����
                                                            00����ʾADQ1�Ĵ�СΪ32��
                                                            01����ʾADQ1�Ĵ�СΪ64��
                                                            10����ʾADQ1�Ĵ�СΪ128��
                                                            11����ʾADQ1�Ĵ�СΪ256�� */
        unsigned int  reserved         : 10; /* bit[6-15] : ���� */
        unsigned int  dl_adq_plen_th   : 16; /* bit[16-31]: ����ͨ�����ݰ�����ֵ��������ͨ������adq������ʱ�������ǰ���ݰ���С����ֵ��ʹ��adq0��AD������ʹ��adq1��AD */
    } reg;
} SOC_IPF_CH1_ADQ_CTRL_UNION;
#endif
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq_en_START         (0)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq_en_END           (1)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq0_size_sel_START  (2)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq0_size_sel_END    (3)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq1_size_sel_START  (4)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq1_size_sel_END    (5)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq_plen_th_START    (16)
#define SOC_IPF_CH1_ADQ_CTRL_dl_adq_plen_th_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_ADQ0_BASE_UNION
 �ṹ˵��  : CH1_ADQ0_BASE �Ĵ����ṹ���塣��ַƫ����:0x0290����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ0��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq0_base : 32; /* bit[0-31]: ����ͨ��Ŀ�ĵ�ַ���������л�ַ */
    } reg;
} SOC_IPF_CH1_ADQ0_BASE_UNION;
#endif
#define SOC_IPF_CH1_ADQ0_BASE_dl_adq0_base_START  (0)
#define SOC_IPF_CH1_ADQ0_BASE_dl_adq0_base_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_ADQ0_STAT_UNION
 �ṹ˵��  : CH1_ADQ0_STAT �Ĵ����ṹ���塣��ַƫ����:0x0294����ֵ:0x0200�����:32
 �Ĵ���˵��: ����ͨ��ADQ0״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq0_empty        : 1;  /* bit[0]   : ����ADQ0��״ָ̬ʾ�Ĵ��� */
        unsigned int  reserved_0           : 3;  /* bit[1-3] : ����. */
        unsigned int  dl_adq0_rptr_invalid : 1;  /* bit[4]   : ����ADQ0��ָ����Ч����ʾ������õ�ADQ0��ָ�����dl_adq0_size */
        unsigned int  dl_adq0_wptr_invalid : 1;  /* bit[5]   : ����ADQ0дָ����Ч����ʾ������õ�ADQ0дָ�����dl_adq0_size */
        unsigned int  reserved_1           : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_IPF_CH1_ADQ0_STAT_UNION;
#endif
#define SOC_IPF_CH1_ADQ0_STAT_dl_adq0_empty_START         (0)
#define SOC_IPF_CH1_ADQ0_STAT_dl_adq0_empty_END           (0)
#define SOC_IPF_CH1_ADQ0_STAT_dl_adq0_rptr_invalid_START  (4)
#define SOC_IPF_CH1_ADQ0_STAT_dl_adq0_rptr_invalid_END    (4)
#define SOC_IPF_CH1_ADQ0_STAT_dl_adq0_wptr_invalid_START  (5)
#define SOC_IPF_CH1_ADQ0_STAT_dl_adq0_wptr_invalid_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_ADQ0_WPTR_UNION
 �ṹ˵��  : CH1_ADQ0_WPTR �Ĵ����ṹ���塣��ַƫ����:0x0298����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ0дָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq0_wptr : 8;  /* bit[0-7] : ����ͨ��ADQ0дָ�룬��������ʱдָ����Ҫ���ά���� */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_IPF_CH1_ADQ0_WPTR_UNION;
#endif
#define SOC_IPF_CH1_ADQ0_WPTR_dl_adq0_wptr_START  (0)
#define SOC_IPF_CH1_ADQ0_WPTR_dl_adq0_wptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_ADQ0_RPTR_UNION
 �ṹ˵��  : CH1_ADQ0_RPTR �Ĵ����ṹ���塣��ַƫ����:0x029C����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ0��ָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq0_rptr : 8;  /* bit[0-7] : ����ͨ��ADQ0��ָ�룬��������ʱ��ָ����Ӳ��ά���� */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_IPF_CH1_ADQ0_RPTR_UNION;
#endif
#define SOC_IPF_CH1_ADQ0_RPTR_dl_adq0_rptr_START  (0)
#define SOC_IPF_CH1_ADQ0_RPTR_dl_adq0_rptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_ADQ1_BASE_UNION
 �ṹ˵��  : CH1_ADQ1_BASE �Ĵ����ṹ���塣��ַƫ����:0x02A0����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ1��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq1_base : 32; /* bit[0-31]: ����ͨ��Ŀ�ĵ�ַ���������л�ַ */
    } reg;
} SOC_IPF_CH1_ADQ1_BASE_UNION;
#endif
#define SOC_IPF_CH1_ADQ1_BASE_dl_adq1_base_START  (0)
#define SOC_IPF_CH1_ADQ1_BASE_dl_adq1_base_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_ADQ1_STAT_UNION
 �ṹ˵��  : CH1_ADQ1_STAT �Ĵ����ṹ���塣��ַƫ����:0x02A4����ֵ:0x0200�����:32
 �Ĵ���˵��: ����ͨ��ADQ1״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq1_empty        : 1;  /* bit[0]   : ����ADQ1��״ָ̬ʾ�Ĵ��� */
        unsigned int  reserved_0           : 3;  /* bit[1-3] : ����. */
        unsigned int  dl_adq1_rptr_invalid : 1;  /* bit[4]   : ����ADQ1��ָ����Ч����ʾ������õ�ADQ1��ָ�����dl_adq1_size */
        unsigned int  dl_adq1_wptr_invalid : 1;  /* bit[5]   : ����ADQ1дָ����Ч����ʾ������õ�ADQ1дָ�����dl_adq1_size */
        unsigned int  reserved_1           : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_IPF_CH1_ADQ1_STAT_UNION;
#endif
#define SOC_IPF_CH1_ADQ1_STAT_dl_adq1_empty_START         (0)
#define SOC_IPF_CH1_ADQ1_STAT_dl_adq1_empty_END           (0)
#define SOC_IPF_CH1_ADQ1_STAT_dl_adq1_rptr_invalid_START  (4)
#define SOC_IPF_CH1_ADQ1_STAT_dl_adq1_rptr_invalid_END    (4)
#define SOC_IPF_CH1_ADQ1_STAT_dl_adq1_wptr_invalid_START  (5)
#define SOC_IPF_CH1_ADQ1_STAT_dl_adq1_wptr_invalid_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_ADQ1_WPTR_UNION
 �ṹ˵��  : CH1_ADQ1_WPTR �Ĵ����ṹ���塣��ַƫ����:0x02A8����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ1дָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq1_wptr : 8;  /* bit[0-7] : ����ͨ��ADQ1дָ�룬��������ʱдָ����Ҫ���ά���� */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_IPF_CH1_ADQ1_WPTR_UNION;
#endif
#define SOC_IPF_CH1_ADQ1_WPTR_dl_adq1_wptr_START  (0)
#define SOC_IPF_CH1_ADQ1_WPTR_dl_adq1_wptr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_IPF_CH1_ADQ1_RPTR_UNION
 �ṹ˵��  : CH1_ADQ1_RPTR �Ĵ����ṹ���塣��ַƫ����:0x02AC����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ��ADQ1��ָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dl_adq1_rptr : 8;  /* bit[0-7] : ����ͨ��ADQ1��ָ�룬��������ʱ��ָ����Ӳ��ά���� */
        unsigned int  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_IPF_CH1_ADQ1_RPTR_UNION;
#endif
#define SOC_IPF_CH1_ADQ1_RPTR_dl_adq1_rptr_START  (0)
#define SOC_IPF_CH1_ADQ1_RPTR_dl_adq1_rptr_END    (7)






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

#endif /* end of soc_ipf_interface.h */
