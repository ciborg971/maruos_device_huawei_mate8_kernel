

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_HDLC_INTERFACE_H__
#define __SOC_HDLC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) Register_define
 ****************************************************************************/
/* �Ĵ���˵����״̬��λ�Ĵ�����
   λ����UNION�ṹ:  SOC_HDLC_STATE_SW_RST_UNION */
#define SOC_HDLC_STATE_SW_RST_ADDR(base)              ((base) + (0x0000))

/* �Ĵ���˵����HDLC��װ�����װ���ȼ����ú�AXI���߶�д����ʱ�ж�ʹ�ܼ�timeoutֵ���üĴ�����
   λ����UNION�ṹ:  SOC_HDLC_PRIOR_TIMEOUT_CTRL_UNION */
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_ADDR(base)        ((base) + (0x0004))

/* �Ĵ���˵����AXI����������ʱ������ַ��
   λ����UNION�ṹ:  SOC_HDLC_RD_ERR_CURR_ADDR_UNION */
#define SOC_HDLC_RD_ERR_CURR_ADDR_ADDR(base)          ((base) + (0x0008))

/* �Ĵ���˵����AXIд��������ʱ��д��ַ��
   λ����UNION�ṹ:  SOC_HDLC_WR_ERR_CURR_ADDR_UNION */
#define SOC_HDLC_WR_ERR_CURR_ADDR_ADDR(base)          ((base) + (0x000C))

/* �Ĵ���˵����HDLC��װ���ʹ�ܼĴ�����������װʹ�ܡ���װ�������ô����ж�ʹ�ܡ�AXI��д�����ж�ʹ�ܡ�AXI��дtimeout�ж�ʹ�ܡ���װ�ⲿ����洢�ռ䲻���ж�ʹ�ܡ���װ�ⲿ��ȷ֡�����ϱ��ռ䲻���ж�ʹ�ܡ���װ�����ж�ʹ�ܣ�ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ��쳣�ж�ʹ�ܣ���
   λ����UNION�ṹ:  SOC_HDLC_FRM_EN_UNION */
#define SOC_HDLC_FRM_EN_ADDR(base)                    ((base) + (0x0010))

/* �Ĵ���˵����HDLC��װԭʼ�ж�״̬�Ĵ���������AXI��д����ԭʼ�жϡ�AXI��дtimeoutԭʼ�жϡ���װ�ⲿ����洢�ռ䲻��ԭʼ�жϡ���װ�ⲿ��ȷ֡�����ϱ��ռ䲻��ԭʼ�жϡ���װ����ԭʼ�жϣ�ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ�ԭʼ�жϣ���
   λ����UNION�ṹ:  SOC_HDLC_FRM_RAW_INT_UNION */
#define SOC_HDLC_FRM_RAW_INT_ADDR(base)               ((base) + (0x0014))

/* �Ĵ���˵����HDLC��װ���κ��ж�״̬�Ĵ���������AXI��д�������κ��жϡ�AXI��дtimeout���κ��жϡ���װ�ⲿ����洢�ռ䲻�����κ��ж�״̬����װ�ⲿ��ȷ֡�����ϱ��ռ䲻�����κ��ж�״̬����װ�������κ��ж�״̬��ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ����κ��ж�״̬����
   λ����UNION�ṹ:  SOC_HDLC_FRM_INT_STATUS_UNION */
#define SOC_HDLC_FRM_INT_STATUS_ADDR(base)            ((base) + (0x0018))

/* �Ĵ���˵����HDLC��װ�ж�����Ĵ���������AXI��д�����ж������AXI��дtimeout�ж��������װ�ⲿ����洢�ռ䲻���ж��������װ�ⲿ��ȷ֡�����ϱ��ռ䲻���ж��������װ�����ж������ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ��ж��������
   λ����UNION�ṹ:  SOC_HDLC_FRM_INT_CLR_UNION */
#define SOC_HDLC_FRM_INT_CLR_ADDR(base)               ((base) + (0x001C))

/* �Ĵ���˵������װ��ģ�����üĴ���
            (�����λ��Ϊ��װ����һά������λ����ѡ��ָʾfrm_in_lli_1dor2d)��
   λ����UNION�ṹ:  SOC_HDLC_FRM_CFG_UNION */
#define SOC_HDLC_FRM_CFG_ADDR(base)                   ((base) + (0x0020))

/* �Ĵ���˵������װ��ģ��ת��ʹ��(LCPЭ��üĴ�����Ч)��
   λ����UNION�ṹ:  SOC_HDLC_FRM_ACCM_UNION */
#define SOC_HDLC_FRM_ACCM_ADDR(base)                  ((base) + (0x0024))

/* �Ĵ���˵������װ��ģ��״̬�Ĵ�������frm_frm_lenɾ��������frm_out_seg_num����frm_valid_num����frm_blk_done��Ϊfrm_all_pkt_done����
   λ����UNION�ṹ:  SOC_HDLC_FRM_STATUS_UNION */
#define SOC_HDLC_FRM_STATUS_ADDR(base)                ((base) + (0x0028))

/* �Ĵ���˵������װ����������ʼ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_HDLC_FRM_IN_LLI_ADDR_UNION */
#define SOC_HDLC_FRM_IN_LLI_ADDR_ADDR(base)           ((base) + (0x0030))

/* �Ĵ���˵������frm_in_lii_1dor2dΪ0����ʾ����װ�������ݰ���ʼ��ַ�Ĵ�����
            ��frm_in_lii_1dor2dΪ1����ʾ��װ���븱���������ʼ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_HDLC_FRM_IN_SUBLLI_ADDR_UNION */
#define SOC_HDLC_FRM_IN_SUBLLI_ADDR_ADDR(base)        ((base) + (0x0034))

/* �Ĵ���˵������װ����������ڵ���ָ����װ�������ݰ����ȼĴ�����
   λ����UNION�ṹ:  SOC_HDLC_FRM_IN_PKT_LEN_UNION */
#define SOC_HDLC_FRM_IN_PKT_LEN_ADDR(base)            ((base) + (0x0038))

/* �Ĵ���˵������װ���븱����ڵ���ָ����װ�������ݷ�����ʼ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_HDLC_FRM_IN_BLK_ADDR_UNION */
#define SOC_HDLC_FRM_IN_BLK_ADDR_ADDR(base)           ((base) + (0x003C))

/* �Ĵ���˵������װ���븱����ڵ���ָ����װ�������ݷ��鳤�ȼĴ�����
   λ����UNION�ṹ:  SOC_HDLC_FRM_IN_BLK_LEN_UNION */
#define SOC_HDLC_FRM_IN_BLK_LEN_ADDR(base)            ((base) + (0x0040))

/* �Ĵ���˵������װ���������ʼ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_HDLC_FRM_OUT_LLI_ADDR_UNION */
#define SOC_HDLC_FRM_OUT_LLI_ADDR_ADDR(base)          ((base) + (0x0044))

/* �Ĵ���˵������װ�������ڵ���ָ�洢�ռ���ʼ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_HDLC_FRM_OUT_SPC_ADDR_UNION */
#define SOC_HDLC_FRM_OUT_SPC_ADDR_ADDR(base)          ((base) + (0x0048))

/* �Ĵ���˵������װ�������ڵ���ָ�洢�ռ���ȼĴ�����
   λ����UNION�ṹ:  SOC_HDLC_FRM_OUT_SPC_DEP_UNION */
#define SOC_HDLC_FRM_OUT_SPC_DEP_ADDR(base)           ((base) + (0x004C))

/* �Ĵ���˵������װ�������ȷ֡���ȴ洢�ռ���ʼ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_HDLC_FRM_RPT_ADDR_UNION */
#define SOC_HDLC_FRM_RPT_ADDR_ADDR(base)              ((base) + (0x0050))

/* �Ĵ���˵������װ�������ȷ֡���ȴ洢�ռ���ȼĴ�����
   λ����UNION�ṹ:  SOC_HDLC_FRM_RPT_DEP_UNION */
#define SOC_HDLC_FRM_RPT_DEP_ADDR(base)               ((base) + (0x0054))

/* �Ĵ���˵����HDLC���װ���ʹ�ܼĴ������������װʹ�ܡ����װ�������ô����ж�ʹ�ܡ�AXI��д�����ж�ʹ�ܡ�AXI��дtimeout�ж�ʹ�ܡ����װ�����ЧLCP֡��ͣ�ж�ʹ�ܡ����װ�ⲿ����洢�ռ������ͣ�ж�ʹ�ܡ����װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ�ж�ʹ�ܡ����װ�����ж�ʹ�ܣ�ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ��쳣�ж�ʹ�ܣ���
   λ����UNION�ṹ:  SOC_HDLC_DEF_EN_UNION */
#define SOC_HDLC_DEF_EN_ADDR(base)                    ((base) + (0x0060))

/* �Ĵ���˵����HDLCԭʼ�ж�״̬�Ĵ���������AXI��д����ԭʼ�жϡ�AXI��дtimeoutԭʼ�жϡ����װ�����ЧLCP֡ԭʼ��ͣ�жϡ����װ�ⲿ����洢�ռ������ͣԭʼ�жϡ����װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣԭʼ�жϡ����װ����ԭʼ�жϣ�ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ�ԭʼ�жϣ���
   λ����UNION�ṹ:  SOC_HDLC_DEF_RAW_INT_UNION */
#define SOC_HDLC_DEF_RAW_INT_ADDR(base)               ((base) + (0x0064))

/* �Ĵ���˵����HDLC���κ��ж�״̬�Ĵ���������AXI��д�������κ��ж�״̬��AXI��дtimeout���κ��ж�״̬�����װ�����ЧLCP֡��ͣ���κ��ж�״̬�����װ�ⲿ����洢�ռ������ͣ���κ��ж�״̬�����װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ���κ��ж�״̬�����װ�������κ��ж�״̬��ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ����κ��ж�״̬����
   λ����UNION�ṹ:  SOC_HDLC_DEF_INT_STATUS_UNION */
#define SOC_HDLC_DEF_INT_STATUS_ADDR(base)            ((base) + (0x0068))

/* �Ĵ���˵����HDLC�ж�����Ĵ���������AXI��д�����ж������AXI��дtimeout�ж���������װ�����ЧLCP֡��ͣ�ж���������װ�ⲿ����洢�ռ������ͣ�ж���������װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ�ж���������װ�����ж������ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ��ж��������
   λ����UNION�ṹ:  SOC_HDLC_DEF_INT_CLR_UNION */
#define SOC_HDLC_DEF_INT_CLR_ADDR(base)               ((base) + (0x006C))

/* �Ĵ���˵�������װ��ģ�����üĴ���
            (�����λ��Ϊdef_uncompleted_ago������ָʾ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ���������Ƿ��н��������֡��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã�0��û�У�1����)��
   λ����UNION�ṹ:  SOC_HDLC_DEF_CFG_UNION */
#define SOC_HDLC_DEF_CFG_ADDR(base)                   ((base) + (0x0070))

/* �Ĵ���˵������Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡�ĳ��ȣ�Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����á�
   λ����UNION�ṹ:  SOC_HDLC_DEF_UNCOMPLETED_LEN_UNION */
#define SOC_HDLC_DEF_UNCOMPLETED_LEN_ADDR(base)       ((base) + (0x0074))

/* �Ĵ���˵������Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡��Э�飬Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã��������е�0Byte��1Byte��2Byte��Ч����
   λ����UNION�ṹ:  SOC_HDLC_DEF_UNCOMPLETED_PRO_UNION */
#define SOC_HDLC_DEF_UNCOMPLETED_PRO_ADDR(base)       ((base) + (0x0078))

/* �Ĵ���˵������Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡���ⲿ�洢��ʼ��ַ��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã��õ�ַ��������ԭ���ϱ���ͬ���µ�ַ����
   λ����UNION�ṹ:  SOC_HDLC_DEF_UNCOMPLETED_ADDR_UNION */
#define SOC_HDLC_DEF_UNCOMPLETED_ADDR_ADDR(base)      ((base) + (0x007C))

/* �Ĵ���˵�����뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ������״̬����ǰ״̬��CRCУ��ֵ��
   λ����UNION�ṹ:  SOC_HDLC_DEF_UNCOMPLET_ST_AGO_UNION */
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_ADDR(base)      ((base) + (0x0080))

/* �Ĵ���˵������ͣ״̬����Ĵ��������һ���Ϸ�LCP֡���µĽ��װ��ģ����ͣ״̬��������װ�ⲿ����洢�ռ������ͣ��������װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ�������
   λ����UNION�ṹ:  SOC_HDLC_DEF_GO_ON_UNION */
#define SOC_HDLC_DEF_GO_ON_ADDR(base)                 ((base) + (0x0084))

/* �Ĵ���˵�������װ��ģ��״̬�Ĵ���������def_uncompleted_now������ָʾ��ǰ�����Ƿ��н��������֡��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã�0��û�У�1���У�����def_out_spc_ful��def_rpt_ful����def_blk_pro_stat��Ϊdef_all_pkt_pro_stat����
   λ����UNION�ṹ:  SOC_HDLC_DEF_STATUS_UNION */
#define SOC_HDLC_DEF_STATUS_ADDR(base)                ((base) + (0x0088))

/* �Ĵ���˵������ǰ���װ��������������������֡ʱ������״̬����ǰ״̬��CRCУ��ֵ��
   λ����UNION�ṹ:  SOC_HDLC_DEF_UNCOMPLET_ST_NOW_UNION */
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_ADDR(base)      ((base) + (0x008C))

/* �Ĵ���˵�������װ�������������ʼ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_HDLC_DEF_IN_LLI_ADDR_UNION */
#define SOC_HDLC_DEF_IN_LLI_ADDR_ADDR(base)           ((base) + (0x0090))

/* �Ĵ���˵�������װ��������ڵ���ָ�����װ�������ݰ���ʼ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_HDLC_DEF_IN_PKT_ADDR_UNION */
#define SOC_HDLC_DEF_IN_PKT_ADDR_ADDR(base)           ((base) + (0x0094))

/* �Ĵ���˵�������װ��������ڵ���ָ�����װ�������ݰ����ȼĴ�����
   λ����UNION�ṹ:  SOC_HDLC_DEF_IN_PKT_LEN_UNION */
#define SOC_HDLC_DEF_IN_PKT_LEN_ADDR(base)            ((base) + (0x0098))

/* �Ĵ���˵����һ�����װ��������ڵ���ָ�����װ�������ݰ���������ȼĴ�����
   λ����UNION�ṹ:  SOC_HDLC_DEF_IN_PKT_LEN_MAX_UNION */
#define SOC_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(base)        ((base) + (0x009C))

/* �Ĵ���˵�������װ������ݴ洢�ռ���ʼ��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_HDLC_DEF_OUT_SPC_ADDR_UNION */
#define SOC_HDLC_DEF_OUT_SPC_ADDR_ADDR(base)          ((base) + (0x00A0))

/* �Ĵ���˵�������װ������ݴ洢�ռ���ȼĴ�����
   λ����UNION�ṹ:  SOC_HDLC_DEF_OUT_SPC_DEP_UNION */
#define SOC_HDLC_DEF_OUT_SPC_DEP_ADDR(base)           ((base) + (0x00A4))

/* �Ĵ���˵�������װ�����ȷ֡�ϱ���Ϣ�洢�ռ���ʼ��ַ��
   λ����UNION�ṹ:  SOC_HDLC_DEF_RPT_ADDR_UNION */
#define SOC_HDLC_DEF_RPT_ADDR_ADDR(base)              ((base) + (0x00A8))

/* �Ĵ���˵�������װ�����ȷ֡�ϱ���Ϣ�洢�ռ���ȡ�
   λ����UNION�ṹ:  SOC_HDLC_DEF_RPT_DEP_UNION */
#define SOC_HDLC_DEF_RPT_DEP_ADDR(base)               ((base) + (0x00AC))

/* �Ĵ���˵�������װ����֡��Ϣ�Ĵ�������0����
   λ����UNION�ṹ:  SOC_HDLC_DEF_ERR_INFO_0_UNION */
#define SOC_HDLC_DEF_ERR_INFO_0_ADDR(base)            ((base) + (0x00B0))

/* �Ĵ���˵�������װ����֡��Ϣ�Ĵ�������1����
   λ����UNION�ṹ:  SOC_HDLC_DEF_ERR_INFO_1_UNION */
#define SOC_HDLC_DEF_ERR_INFO_1_ADDR(base)            ((base) + (0x00B4))

/* �Ĵ���˵�������װ����֡��Ϣ�Ĵ�������2����
   λ����UNION�ṹ:  SOC_HDLC_DEF_ERR_INFO_2_UNION */
#define SOC_HDLC_DEF_ERR_INFO_2_ADDR(base)            ((base) + (0x00B8))

/* �Ĵ���˵�������װ����֡��Ϣ�Ĵ�������3����
   λ����UNION�ṹ:  SOC_HDLC_DEF_ERR_INFO_3_UNION */
#define SOC_HDLC_DEF_ERR_INFO_3_ADDR(base)            ((base) + (0x00BC))

/* �Ĵ���˵�����뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ����Ϣ���Ⱥ�֡���ȡ�
   λ����UNION�ṹ:  SOC_HDLC_DEF_INFO_FRL_CNT_AGO_UNION */
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(base)      ((base) + (0x00C0))

/* �Ĵ���˵������ǰ���װ��������������������֡ʱ����Ϣ���Ⱥ�֡���ȡ�
   λ����UNION�ṹ:  SOC_HDLC_DEF_INFO_FRL_CNT_NOW_UNION */
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(base)      ((base) + (0x00C4))





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
                     (1/1) Register_define
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_HDLC_STATE_SW_RST_UNION
 �ṹ˵��  : STATE_SW_RST �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ״̬��λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  state_sw_rst : 1;  /* bit[0]   : ״̬��λ��
                                                       0��״̬����λ��
                                                       1��״̬��λ */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_HDLC_STATE_SW_RST_UNION;
#endif
#define SOC_HDLC_STATE_SW_RST_state_sw_rst_START  (0)
#define SOC_HDLC_STATE_SW_RST_state_sw_rst_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_PRIOR_TIMEOUT_CTRL_UNION
 �ṹ˵��  : PRIOR_TIMEOUT_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: HDLC��װ�����װ���ȼ����ú�AXI���߶�д����ʱ�ж�ʹ�ܼ�timeoutֵ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hdlc_prior_ctrl      : 2;  /* bit[0-1]  : HDLC��װ�����װ���ȼ����üĴ�����
                                                                00��һ���ڹ����У���һ��Ҳ��ʹ������£��Ƚ��Ѵ��ڹ����е��Ǹ������꣬��˭�ȱ�ʹ�����Ƚ�˭�����ꣻ01�����з�װ���ȼ��ߣ�
                                                                10�����н��װ���ȼ��ߣ�
                                                                11����Ч��
                                                                (HDLC�ڲ����Ʊ���ͣ�ߵļ�����ʼ�����������װ����ͣ����װ��������������󣬽��װ�Ϳ�ʼ��������������װ����ͣ�����װ�������ݰ���������󣬷�װ�Ϳ�ʼ����������) */
        unsigned int  reserved_0           : 6;  /* bit[2-7]  : ���� */
        unsigned int  axireq_timeout_en    : 1;  /* bit[8]    : �Ƿ�����Ӳ���ж�AXI���߶�д����ʱ����������ã�
                                                                0������
                                                                1���� */
        unsigned int  reserved_1           : 7;  /* bit[9-15] : ���� */
        unsigned int  axireq_timeout_value : 8;  /* bit[16-23]: �������AXI���߶�д����ʱ���ж�ֵ */
        unsigned int  reserved_2           : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_HDLC_PRIOR_TIMEOUT_CTRL_UNION;
#endif
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_hdlc_prior_ctrl_START       (0)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_hdlc_prior_ctrl_END         (1)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_axireq_timeout_en_START     (8)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_axireq_timeout_en_END       (8)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_axireq_timeout_value_START  (16)
#define SOC_HDLC_PRIOR_TIMEOUT_CTRL_axireq_timeout_value_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_RD_ERR_CURR_ADDR_UNION
 �ṹ˵��  : RD_ERR_CURR_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXI����������ʱ������ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_err_curr_addr : 32; /* bit[0-31]: AXI����������ʱ������ַ */
    } reg;
} SOC_HDLC_RD_ERR_CURR_ADDR_UNION;
#endif
#define SOC_HDLC_RD_ERR_CURR_ADDR_rd_err_curr_addr_START  (0)
#define SOC_HDLC_RD_ERR_CURR_ADDR_rd_err_curr_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_WR_ERR_CURR_ADDR_UNION
 �ṹ˵��  : WR_ERR_CURR_ADDR �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXIд��������ʱ��д��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_err_curr_addr : 32; /* bit[0-31]: AXIд��������ʱ��д��ַ */
    } reg;
} SOC_HDLC_WR_ERR_CURR_ADDR_UNION;
#endif
#define SOC_HDLC_WR_ERR_CURR_ADDR_wr_err_curr_addr_START  (0)
#define SOC_HDLC_WR_ERR_CURR_ADDR_wr_err_curr_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_EN_UNION
 �ṹ˵��  : FRM_EN �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: HDLC��װ���ʹ�ܼĴ�����������װʹ�ܡ���װ�������ô����ж�ʹ�ܡ�AXI��д�����ж�ʹ�ܡ�AXI��дtimeout�ж�ʹ�ܡ���װ�ⲿ����洢�ռ䲻���ж�ʹ�ܡ���װ�ⲿ��ȷ֡�����ϱ��ռ䲻���ж�ʹ�ܡ���װ�����ж�ʹ�ܣ�ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ��쳣�ж�ʹ�ܣ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_en             : 1;  /* bit[0]    : һ�������װʹ�ܣ������frm_enд��1'b1������װ������
                                                              һ�������װ��ɺ���Ӳ���Զ���frm_en���㣻
                                                              ��װ���̳���ʱ��Ӳ��Ҳ���frm_en�Զ����㣬ʹ�ڲ�״̬������IDLE״̬��
                                                              ���üĴ������ط�װ����״̬��
                                                              дʱ����һ�������װʹ�ܣ�
                                                              0����ʹ�ܷ�װ����
                                                              1��ʹ�ܷ�װ����
                                                              ��ʱ����һ�������װ����״̬��
                                                              0��û�ڽ��з�װ����
                                                              1�����ڽ��з�װ���� */
        unsigned int  reserved_0         : 7;  /* bit[1-7]  : ���� */
        unsigned int  frm_rd_err_en      : 1;  /* bit[8]    : ��װʱAXI���߶����������ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  frm_wr_err_en      : 1;  /* bit[9]    : ��װʱAXI����д���������ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  frm_rd_timeout_en  : 1;  /* bit[10]   : ��װʱAXI���߶�����timeout�ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  frm_wr_timeout_en  : 1;  /* bit[11]   : ��װʱAXI����д����timeout�ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  frm_cfg_err_en     : 1;  /* bit[12]   : ��װģ���쳣�ж�(��ʾ�������ô���)ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  frm_in_prm_err_en  : 1;  /* bit[13]   : ��װ����������ز��������ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  frm_out_prm_err_en : 1;  /* bit[14]   : ��װ���������ز��������ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  frm_rpt_prm_err_en : 1;  /* bit[15]   : ��װ�ϱ��ռ���ز��������ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  frm_out_spc_err_en : 1;  /* bit[16]   : ��װ�ⲿ����洢�ռ䲻���ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  frm_rpt_dep_err_en : 1;  /* bit[17]   : ��װ�ⲿ��ȷ֡�����ϱ��ռ䲻���ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  reserved_1         : 6;  /* bit[18-23]: ���� */
        unsigned int  frm_over_int_en    : 1;  /* bit[24]   : һ�������װ�����ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  reserved_2         : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_HDLC_FRM_EN_UNION;
#endif
#define SOC_HDLC_FRM_EN_frm_en_START              (0)
#define SOC_HDLC_FRM_EN_frm_en_END                (0)
#define SOC_HDLC_FRM_EN_frm_rd_err_en_START       (8)
#define SOC_HDLC_FRM_EN_frm_rd_err_en_END         (8)
#define SOC_HDLC_FRM_EN_frm_wr_err_en_START       (9)
#define SOC_HDLC_FRM_EN_frm_wr_err_en_END         (9)
#define SOC_HDLC_FRM_EN_frm_rd_timeout_en_START   (10)
#define SOC_HDLC_FRM_EN_frm_rd_timeout_en_END     (10)
#define SOC_HDLC_FRM_EN_frm_wr_timeout_en_START   (11)
#define SOC_HDLC_FRM_EN_frm_wr_timeout_en_END     (11)
#define SOC_HDLC_FRM_EN_frm_cfg_err_en_START      (12)
#define SOC_HDLC_FRM_EN_frm_cfg_err_en_END        (12)
#define SOC_HDLC_FRM_EN_frm_in_prm_err_en_START   (13)
#define SOC_HDLC_FRM_EN_frm_in_prm_err_en_END     (13)
#define SOC_HDLC_FRM_EN_frm_out_prm_err_en_START  (14)
#define SOC_HDLC_FRM_EN_frm_out_prm_err_en_END    (14)
#define SOC_HDLC_FRM_EN_frm_rpt_prm_err_en_START  (15)
#define SOC_HDLC_FRM_EN_frm_rpt_prm_err_en_END    (15)
#define SOC_HDLC_FRM_EN_frm_out_spc_err_en_START  (16)
#define SOC_HDLC_FRM_EN_frm_out_spc_err_en_END    (16)
#define SOC_HDLC_FRM_EN_frm_rpt_dep_err_en_START  (17)
#define SOC_HDLC_FRM_EN_frm_rpt_dep_err_en_END    (17)
#define SOC_HDLC_FRM_EN_frm_over_int_en_START     (24)
#define SOC_HDLC_FRM_EN_frm_over_int_en_END       (24)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_RAW_INT_UNION
 �ṹ˵��  : FRM_RAW_INT �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: HDLC��װԭʼ�ж�״̬�Ĵ���������AXI��д����ԭʼ�жϡ�AXI��дtimeoutԭʼ�жϡ���װ�ⲿ����洢�ռ䲻��ԭʼ�жϡ���װ�ⲿ��ȷ֡�����ϱ��ռ䲻��ԭʼ�жϡ���װ����ԭʼ�жϣ�ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ�ԭʼ�жϣ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 8;  /* bit[0-7]  : ���� */
        unsigned int  frm_rd_err_raw      : 1;  /* bit[8]    : ��װʱAXI���߶���������ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  frm_wr_err_raw      : 1;  /* bit[9]    : ��װʱAXI����д��������ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  frm_rd_timeout_raw  : 1;  /* bit[10]   : ��װʱAXI���߶�����timeoutԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  frm_wr_timeout_raw  : 1;  /* bit[11]   : ��װʱAXI����д����timeoutԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  frm_cfg_err_raw     : 1;  /* bit[12]   : ��װЭ�鼰��ѹ��ָʾ���ô���ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  frm_in_prm_err_raw  : 1;  /* bit[13]   : ��װ����������ز�������ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  frm_out_prm_err_raw : 1;  /* bit[14]   : ��װ���������ز�������ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  frm_rpt_prm_err_raw : 1;  /* bit[15]   : ��װ�ϱ��ռ���ز�������ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  frm_out_spc_err_raw : 1;  /* bit[16]   : ��װ�ⲿ����洢�ռ䲻��ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  frm_rpt_dep_err_raw : 1;  /* bit[17]   : ��װ�ⲿ��ȷ֡�����ϱ��ռ䲻��ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  reserved_1          : 6;  /* bit[18-23]: ���� */
        unsigned int  frm_over_int_raw    : 1;  /* bit[24]   : һ�������װ����ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  reserved_2          : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_HDLC_FRM_RAW_INT_UNION;
#endif
#define SOC_HDLC_FRM_RAW_INT_frm_rd_err_raw_START       (8)
#define SOC_HDLC_FRM_RAW_INT_frm_rd_err_raw_END         (8)
#define SOC_HDLC_FRM_RAW_INT_frm_wr_err_raw_START       (9)
#define SOC_HDLC_FRM_RAW_INT_frm_wr_err_raw_END         (9)
#define SOC_HDLC_FRM_RAW_INT_frm_rd_timeout_raw_START   (10)
#define SOC_HDLC_FRM_RAW_INT_frm_rd_timeout_raw_END     (10)
#define SOC_HDLC_FRM_RAW_INT_frm_wr_timeout_raw_START   (11)
#define SOC_HDLC_FRM_RAW_INT_frm_wr_timeout_raw_END     (11)
#define SOC_HDLC_FRM_RAW_INT_frm_cfg_err_raw_START      (12)
#define SOC_HDLC_FRM_RAW_INT_frm_cfg_err_raw_END        (12)
#define SOC_HDLC_FRM_RAW_INT_frm_in_prm_err_raw_START   (13)
#define SOC_HDLC_FRM_RAW_INT_frm_in_prm_err_raw_END     (13)
#define SOC_HDLC_FRM_RAW_INT_frm_out_prm_err_raw_START  (14)
#define SOC_HDLC_FRM_RAW_INT_frm_out_prm_err_raw_END    (14)
#define SOC_HDLC_FRM_RAW_INT_frm_rpt_prm_err_raw_START  (15)
#define SOC_HDLC_FRM_RAW_INT_frm_rpt_prm_err_raw_END    (15)
#define SOC_HDLC_FRM_RAW_INT_frm_out_spc_err_raw_START  (16)
#define SOC_HDLC_FRM_RAW_INT_frm_out_spc_err_raw_END    (16)
#define SOC_HDLC_FRM_RAW_INT_frm_rpt_dep_err_raw_START  (17)
#define SOC_HDLC_FRM_RAW_INT_frm_rpt_dep_err_raw_END    (17)
#define SOC_HDLC_FRM_RAW_INT_frm_over_int_raw_START     (24)
#define SOC_HDLC_FRM_RAW_INT_frm_over_int_raw_END       (24)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_INT_STATUS_UNION
 �ṹ˵��  : FRM_INT_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: HDLC��װ���κ��ж�״̬�Ĵ���������AXI��д�������κ��жϡ�AXI��дtimeout���κ��жϡ���װ�ⲿ����洢�ռ䲻�����κ��ж�״̬����װ�ⲿ��ȷ֡�����ϱ��ռ䲻�����κ��ж�״̬����װ�������κ��ж�״̬��ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ����κ��ж�״̬����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 8;  /* bit[0-7]  : ���� */
        unsigned int  frm_rd_err_stat      : 1;  /* bit[8]    : ��װʱAXI���߶������������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  frm_wr_err_stat      : 1;  /* bit[9]    : ��װʱAXI����д�����������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  frm_rd_timeout_stat  : 1;  /* bit[10]   : ��װʱAXI���߶�����timeout���κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  frm_wr_timeout_stat  : 1;  /* bit[11]   : ��װʱAXI����д����timeout���κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  frm_cfg_err_stat     : 1;  /* bit[12]   : ��װЭ�鼰��ѹ��ָʾ���ô������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  frm_in_prm_err_stat  : 1;  /* bit[13]   : ��װ����������ز����������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  frm_out_prm_err_stat : 1;  /* bit[14]   : ��װ���������ز����������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  frm_rpt_prm_err_stat : 1;  /* bit[15]   : ��װ�ϱ��ռ���ز����������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  frm_out_spc_err_stat : 1;  /* bit[16]   : ��װ�ⲿ����洢�ռ䲻�����κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  frm_rpt_dep_err_stat : 1;  /* bit[17]   : ��װ�ⲿ��ȷ֡�����ϱ��ռ䲻�����κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  reserved_1           : 6;  /* bit[18-23]: ���� */
        unsigned int  frm_over_int_stat    : 1;  /* bit[24]   : һ�������װ�������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  reserved_2           : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_HDLC_FRM_INT_STATUS_UNION;
#endif
#define SOC_HDLC_FRM_INT_STATUS_frm_rd_err_stat_START       (8)
#define SOC_HDLC_FRM_INT_STATUS_frm_rd_err_stat_END         (8)
#define SOC_HDLC_FRM_INT_STATUS_frm_wr_err_stat_START       (9)
#define SOC_HDLC_FRM_INT_STATUS_frm_wr_err_stat_END         (9)
#define SOC_HDLC_FRM_INT_STATUS_frm_rd_timeout_stat_START   (10)
#define SOC_HDLC_FRM_INT_STATUS_frm_rd_timeout_stat_END     (10)
#define SOC_HDLC_FRM_INT_STATUS_frm_wr_timeout_stat_START   (11)
#define SOC_HDLC_FRM_INT_STATUS_frm_wr_timeout_stat_END     (11)
#define SOC_HDLC_FRM_INT_STATUS_frm_cfg_err_stat_START      (12)
#define SOC_HDLC_FRM_INT_STATUS_frm_cfg_err_stat_END        (12)
#define SOC_HDLC_FRM_INT_STATUS_frm_in_prm_err_stat_START   (13)
#define SOC_HDLC_FRM_INT_STATUS_frm_in_prm_err_stat_END     (13)
#define SOC_HDLC_FRM_INT_STATUS_frm_out_prm_err_stat_START  (14)
#define SOC_HDLC_FRM_INT_STATUS_frm_out_prm_err_stat_END    (14)
#define SOC_HDLC_FRM_INT_STATUS_frm_rpt_prm_err_stat_START  (15)
#define SOC_HDLC_FRM_INT_STATUS_frm_rpt_prm_err_stat_END    (15)
#define SOC_HDLC_FRM_INT_STATUS_frm_out_spc_err_stat_START  (16)
#define SOC_HDLC_FRM_INT_STATUS_frm_out_spc_err_stat_END    (16)
#define SOC_HDLC_FRM_INT_STATUS_frm_rpt_dep_err_stat_START  (17)
#define SOC_HDLC_FRM_INT_STATUS_frm_rpt_dep_err_stat_END    (17)
#define SOC_HDLC_FRM_INT_STATUS_frm_over_int_stat_START     (24)
#define SOC_HDLC_FRM_INT_STATUS_frm_over_int_stat_END       (24)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_INT_CLR_UNION
 �ṹ˵��  : FRM_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: HDLC��װ�ж�����Ĵ���������AXI��д�����ж������AXI��дtimeout�ж��������װ�ⲿ����洢�ռ䲻���ж��������װ�ⲿ��ȷ֡�����ϱ��ռ䲻���ж��������װ�����ж������ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ��ж��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 8;  /* bit[0-7]  : ���� */
        unsigned int  frm_rd_err_clr      : 1;  /* bit[8]    : frm_rd_err�ж������д1����жϣ� */
        unsigned int  frm_wr_err_clr      : 1;  /* bit[9]    : frm_wr_err�ж������д1����жϣ� */
        unsigned int  frm_rd_timeout_clr  : 1;  /* bit[10]   : frm_rd_timeout�ж������д1����жϣ� */
        unsigned int  frm_wr_timeout_clr  : 1;  /* bit[11]   : frm_wr_timeout�ж������д1����жϣ� */
        unsigned int  frm_cfg_err_clr     : 1;  /* bit[12]   : frm_cfg_err�ж������д1����жϣ� */
        unsigned int  frm_in_prm_err_clr  : 1;  /* bit[13]   : frm_in_prm_err�ж������д1����жϣ� */
        unsigned int  frm_out_prm_err_clr : 1;  /* bit[14]   : frm_out_prm_err�ж������д1����жϣ� */
        unsigned int  frm_rpt_prm_err_clr : 1;  /* bit[15]   : frm_rpt_prm_err�ж������д1����жϣ� */
        unsigned int  frm_out_spc_err_clr : 1;  /* bit[16]   : frm_out_spc_err �ж������д1����жϣ� */
        unsigned int  frm_rpt_dep_err_clr : 1;  /* bit[17]   : frm_rpt_dep_err �ж������д1����жϣ� */
        unsigned int  reserved_1          : 6;  /* bit[18-23]: ���� */
        unsigned int  frm_over_int_clr    : 1;  /* bit[24]   : frm_over_int �ж������д1����жϣ� */
        unsigned int  reserved_2          : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_HDLC_FRM_INT_CLR_UNION;
#endif
#define SOC_HDLC_FRM_INT_CLR_frm_rd_err_clr_START       (8)
#define SOC_HDLC_FRM_INT_CLR_frm_rd_err_clr_END         (8)
#define SOC_HDLC_FRM_INT_CLR_frm_wr_err_clr_START       (9)
#define SOC_HDLC_FRM_INT_CLR_frm_wr_err_clr_END         (9)
#define SOC_HDLC_FRM_INT_CLR_frm_rd_timeout_clr_START   (10)
#define SOC_HDLC_FRM_INT_CLR_frm_rd_timeout_clr_END     (10)
#define SOC_HDLC_FRM_INT_CLR_frm_wr_timeout_clr_START   (11)
#define SOC_HDLC_FRM_INT_CLR_frm_wr_timeout_clr_END     (11)
#define SOC_HDLC_FRM_INT_CLR_frm_cfg_err_clr_START      (12)
#define SOC_HDLC_FRM_INT_CLR_frm_cfg_err_clr_END        (12)
#define SOC_HDLC_FRM_INT_CLR_frm_in_prm_err_clr_START   (13)
#define SOC_HDLC_FRM_INT_CLR_frm_in_prm_err_clr_END     (13)
#define SOC_HDLC_FRM_INT_CLR_frm_out_prm_err_clr_START  (14)
#define SOC_HDLC_FRM_INT_CLR_frm_out_prm_err_clr_END    (14)
#define SOC_HDLC_FRM_INT_CLR_frm_rpt_prm_err_clr_START  (15)
#define SOC_HDLC_FRM_INT_CLR_frm_rpt_prm_err_clr_END    (15)
#define SOC_HDLC_FRM_INT_CLR_frm_out_spc_err_clr_START  (16)
#define SOC_HDLC_FRM_INT_CLR_frm_out_spc_err_clr_END    (16)
#define SOC_HDLC_FRM_INT_CLR_frm_rpt_dep_err_clr_START  (17)
#define SOC_HDLC_FRM_INT_CLR_frm_rpt_dep_err_clr_END    (17)
#define SOC_HDLC_FRM_INT_CLR_frm_over_int_clr_START     (24)
#define SOC_HDLC_FRM_INT_CLR_frm_over_int_clr_END       (24)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_CFG_UNION
 �ṹ˵��  : FRM_CFG �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��װ��ģ�����üĴ���
            (�����λ��Ϊ��װ����һά������λ����ѡ��ָʾfrm_in_lli_1dor2d)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_in_lli_1dor2d : 1;  /* bit[0]    : ��װ����һά������λ����ѡ��ָʾ�Ĵ��� */
        unsigned int  frm_acfc          : 1;  /* bit[1]    : AC��ѹ��ָʾ��
                                                             l 0��AC����ѹ����
                                                             l 1����ʾAC��ѹ��������װ֡����AC�� */
        unsigned int  frm_pfc           : 2;  /* bit[2-3]  : P��ѹ��ָʾ��
                                                             l 00��Ӳ��ģ�����P��P����ѹ����
                                                             l 01��Ӳ��ģ�����P��P��ѹ����
                                                             l 11��Ӳ��ģ�鲻���P��
                                                             l ��������Ч�� */
        unsigned int  reserved          : 12; /* bit[4-15] : ���� */
        unsigned int  frm_protocol      : 16; /* bit[16-31]: ��װЭ��ֵ����ЧЭ��ֵ�涨�μ�����б� */
    } reg;
} SOC_HDLC_FRM_CFG_UNION;
#endif
#define SOC_HDLC_FRM_CFG_frm_in_lli_1dor2d_START  (0)
#define SOC_HDLC_FRM_CFG_frm_in_lli_1dor2d_END    (0)
#define SOC_HDLC_FRM_CFG_frm_acfc_START           (1)
#define SOC_HDLC_FRM_CFG_frm_acfc_END             (1)
#define SOC_HDLC_FRM_CFG_frm_pfc_START            (2)
#define SOC_HDLC_FRM_CFG_frm_pfc_END              (3)
#define SOC_HDLC_FRM_CFG_frm_protocol_START       (16)
#define SOC_HDLC_FRM_CFG_frm_protocol_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_ACCM_UNION
 �ṹ˵��  : FRM_ACCM �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��װ��ģ��ת��ʹ��(LCPЭ��üĴ�����Ч)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hdlc_frm_accm : 32; /* bit[0-31]: ת��ʹ�ܣ���bit 0�� bit 31 �ֱ��Ӧ0x00~0x1F 32���ַ���
                                                        0��ת���ֹ��
                                                        1��ת��ʹ�ܡ� */
    } reg;
} SOC_HDLC_FRM_ACCM_UNION;
#endif
#define SOC_HDLC_FRM_ACCM_hdlc_frm_accm_START  (0)
#define SOC_HDLC_FRM_ACCM_hdlc_frm_accm_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_STATUS_UNION
 �ṹ˵��  : FRM_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��װ��ģ��״̬�Ĵ�������frm_frm_lenɾ��������frm_out_seg_num����frm_valid_num����frm_blk_done��Ϊfrm_all_pkt_done����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_all_pkt_done : 1;  /* bit[0]    : ��װ��ɱ�־
                                                            0��δ���һ���������ݴ���
                                                            1�����һ���������ݴ��� */
        unsigned int  frm_error_index  : 1;  /* bit[1]    : ��װ��������ָʾ */
        unsigned int  reserved         : 6;  /* bit[2-7]  : ���� */
        unsigned int  frm_valid_num    : 8;  /* bit[8-15] : һ�������װ������Ч֡֡�� */
        unsigned int  frm_out_seg_num  : 16; /* bit[16-31]: һ�������װ������Ч֡���ռ��Ƭ�θ��� */
    } reg;
} SOC_HDLC_FRM_STATUS_UNION;
#endif
#define SOC_HDLC_FRM_STATUS_frm_all_pkt_done_START  (0)
#define SOC_HDLC_FRM_STATUS_frm_all_pkt_done_END    (0)
#define SOC_HDLC_FRM_STATUS_frm_error_index_START   (1)
#define SOC_HDLC_FRM_STATUS_frm_error_index_END     (1)
#define SOC_HDLC_FRM_STATUS_frm_valid_num_START     (8)
#define SOC_HDLC_FRM_STATUS_frm_valid_num_END       (15)
#define SOC_HDLC_FRM_STATUS_frm_out_seg_num_START   (16)
#define SOC_HDLC_FRM_STATUS_frm_out_seg_num_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_IN_LLI_ADDR_UNION
 �ṹ˵��  : FRM_IN_LLI_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��װ����������ʼ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_in_lli_addr : 32; /* bit[0-31]: ��װ������������ʼ��ַ�Ĵ���:
                                                          ������øüĴ���Ϊ�������һ���ڵ����ʼ��ַ��HDLC���ݸõ�ַ�����������һ���ڵ�Ĳ�������������һ��������ڵ���ʼ��ַ����¸üĴ������ڵ�ǰ������ڵ���ָ���ݰ��������HDLC���ݸüĴ���ֵ����һ��������ڵ���ʼ��ַ��������һ��������ڵ���������һ��������ڵ�����е���һ��������ڵ���ʼ��ַΪ0�� */
    } reg;
} SOC_HDLC_FRM_IN_LLI_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_IN_LLI_ADDR_frm_in_lli_addr_START  (0)
#define SOC_HDLC_FRM_IN_LLI_ADDR_frm_in_lli_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_IN_SUBLLI_ADDR_UNION
 �ṹ˵��  : FRM_IN_SUBLLI_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��frm_in_lii_1dor2dΪ0����ʾ����װ�������ݰ���ʼ��ַ�Ĵ�����
            ��frm_in_lii_1dor2dΪ1����ʾ��װ���븱���������ʼ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_in_sublli_addr : 32; /* bit[0-31]: ��frm_in_lii_1dor2dΪ0����ʾ����װ�������ݰ���ʼ��ַ�Ĵ�����
                                                             ��frm_in_lii_1dor2dΪ1����ʾ��װ���븱���������ʼ��ַ�Ĵ�����
                                                             ����������к��и������һ���ڵ����ʼ��ַ��HDLC���ݸõ�ַ���븱�����һ���ڵ�Ĳ�������������һ��������ڵ���ʼ��ַ����¸üĴ������ڵ�ǰ������ڵ�����Ӧ���ݰ��������HDLC���ݸüĴ���ֵ����һ��������ڵ���ʼ��ַ��������һ��������ڵ���������һ��������ڵ�����е���һ��������ڵ���ʼ��ַΪ0�� */
    } reg;
} SOC_HDLC_FRM_IN_SUBLLI_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_IN_SUBLLI_ADDR_frm_in_sublli_addr_START  (0)
#define SOC_HDLC_FRM_IN_SUBLLI_ADDR_frm_in_sublli_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_IN_PKT_LEN_UNION
 �ṹ˵��  : FRM_IN_PKT_LEN �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��װ����������ڵ���ָ����װ�������ݰ����ȼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_in_pkt_len : 16; /* bit[0-15] : ��װ����������ڵ���ָ����װ�������ݰ����ȼĴ�����
                                                          �涨���ó���1502B���ó���Ϊ0x001~0x5DE����0x1��ʾ����Ϊ1B��
                                                          ���ݶ���������ڵ�����еķ�װ�������ݰ����ȸ��¸üĴ��� */
        unsigned int  reserved       : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_HDLC_FRM_IN_PKT_LEN_UNION;
#endif
#define SOC_HDLC_FRM_IN_PKT_LEN_frm_in_pkt_len_START  (0)
#define SOC_HDLC_FRM_IN_PKT_LEN_frm_in_pkt_len_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_IN_BLK_ADDR_UNION
 �ṹ˵��  : FRM_IN_BLK_ADDR �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��װ���븱����ڵ���ָ����װ�������ݷ�����ʼ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_in_blk_addr : 32; /* bit[0-31]: ��װ���븱����ڵ���ָ����װ�������ݷ�����ʼ��ַ�Ĵ�����
                                                          ���ݶ��븱����ڵ�����еĴ���װ�������ݷ�����ʼ��ַ���¸üĴ��� */
    } reg;
} SOC_HDLC_FRM_IN_BLK_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_IN_BLK_ADDR_frm_in_blk_addr_START  (0)
#define SOC_HDLC_FRM_IN_BLK_ADDR_frm_in_blk_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_IN_BLK_LEN_UNION
 �ṹ˵��  : FRM_IN_BLK_LEN �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��װ���븱����ڵ���ָ����װ�������ݷ��鳤�ȼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_in_blk_len : 16; /* bit[0-15] : ��װ���븱����ڵ���ָ����װ�������ݷ��鳤�ȼĴ��� */
        unsigned int  reserved       : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_HDLC_FRM_IN_BLK_LEN_UNION;
#endif
#define SOC_HDLC_FRM_IN_BLK_LEN_frm_in_blk_len_START  (0)
#define SOC_HDLC_FRM_IN_BLK_LEN_frm_in_blk_len_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_OUT_LLI_ADDR_UNION
 �ṹ˵��  : FRM_OUT_LLI_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��װ���������ʼ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_out_lli_addr : 32; /* bit[0-31]: ��װ���������ʼ��ַ�Ĵ�����
                                                           ������øüĴ���Ϊ�����һ���ڵ����ʼ��ַ��HDLC���ݸõ�ַ���������һ���ڵ�Ĳ�������������һ������ڵ���ʼ��ַ����¸üĴ������ڵ�ǰ����ڵ���ָ���ݰ��������HDLC���ݸüĴ���ֵ����һ������ڵ���ʼ��ַ��������һ������ڵ���������һ������ڵ��������һ������ڵ���ʼ��ַΪ0�� */
    } reg;
} SOC_HDLC_FRM_OUT_LLI_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_OUT_LLI_ADDR_frm_out_lli_addr_START  (0)
#define SOC_HDLC_FRM_OUT_LLI_ADDR_frm_out_lli_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_OUT_SPC_ADDR_UNION
 �ṹ˵��  : FRM_OUT_SPC_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��װ�������ڵ���ָ�洢�ռ���ʼ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_out_spc_addr : 32; /* bit[0-31]: ��װ�������ڵ���ָ�洢�ռ���ʼ��ַ�Ĵ�����
                                                           ���ݶ�������ڵ�����еĴ洢�ռ���ʼ��ַ���¸üĴ��� */
    } reg;
} SOC_HDLC_FRM_OUT_SPC_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_OUT_SPC_ADDR_frm_out_spc_addr_START  (0)
#define SOC_HDLC_FRM_OUT_SPC_ADDR_frm_out_spc_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_OUT_SPC_DEP_UNION
 �ṹ˵��  : FRM_OUT_SPC_DEP �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��װ�������ڵ���ָ�洢�ռ���ȼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_out_spc_dep : 16; /* bit[0-15] : ��װ�������ڵ���ָ�洢�ռ���ȼĴ�����
                                                           ���ݶ�������ڵ�����еĴ洢�ռ���ȸ��¸üĴ��� */
        unsigned int  reserved        : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_HDLC_FRM_OUT_SPC_DEP_UNION;
#endif
#define SOC_HDLC_FRM_OUT_SPC_DEP_frm_out_spc_dep_START  (0)
#define SOC_HDLC_FRM_OUT_SPC_DEP_frm_out_spc_dep_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_RPT_ADDR_UNION
 �ṹ˵��  : FRM_RPT_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��װ�������ȷ֡���ȴ洢�ռ���ʼ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_rpt_addr : 32; /* bit[0-31]: ��װ�������ȷ֡���ȴ洢�ռ���ʼ��ַ�Ĵ�����
                                                       ��������� */
    } reg;
} SOC_HDLC_FRM_RPT_ADDR_UNION;
#endif
#define SOC_HDLC_FRM_RPT_ADDR_frm_rpt_addr_START  (0)
#define SOC_HDLC_FRM_RPT_ADDR_frm_rpt_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_FRM_RPT_DEP_UNION
 �ṹ˵��  : FRM_RPT_DEP �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��װ�������ȷ֡���ȴ洢�ռ���ȼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_rpt_dep : 16; /* bit[0-15] : ��װ�������ȷ֡���ȴ洢�ռ���ȼĴ�����
                                                       ��������� */
        unsigned int  reserved    : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_HDLC_FRM_RPT_DEP_UNION;
#endif
#define SOC_HDLC_FRM_RPT_DEP_frm_rpt_dep_START  (0)
#define SOC_HDLC_FRM_RPT_DEP_frm_rpt_dep_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_EN_UNION
 �ṹ˵��  : DEF_EN �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: HDLC���װ���ʹ�ܼĴ������������װʹ�ܡ����װ�������ô����ж�ʹ�ܡ�AXI��д�����ж�ʹ�ܡ�AXI��дtimeout�ж�ʹ�ܡ����װ�����ЧLCP֡��ͣ�ж�ʹ�ܡ����װ�ⲿ����洢�ռ������ͣ�ж�ʹ�ܡ����װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ�ж�ʹ�ܡ����װ�����ж�ʹ�ܣ�ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ��쳣�ж�ʹ�ܣ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_en             : 1;  /* bit[0]    : һ������������װʹ�ܣ������def_enд��1'b1�������װ������
                                                              һ������������װ��ɺ���Ӳ���Զ���def_en���㣻
                                                              ���װ���̳���ʱ��Ӳ��Ҳ���def_en�Զ����㣬ʹ�ڲ�״̬������IDLE״̬��
                                                              ���üĴ������ؽ��װ����״̬��
                                                              дʱ����һ������������װʹ�ܣ�
                                                              0����ʹ�ܽ��װ����
                                                              1��ʹ�ܽ��װ����
                                                              ��ʱ����һ������������װ����״̬��
                                                              0��û�ڽ��н��װ����
                                                              1�����ڽ��н��װ���� */
        unsigned int  reserved_0         : 7;  /* bit[1-7]  : ���� */
        unsigned int  def_rd_err_en      : 1;  /* bit[8]    : ���װʱAXI���߶����������ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  def_wr_err_en      : 1;  /* bit[9]    : ���װʱAXI����д���������ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  def_rd_timeout_en  : 1;  /* bit[10]   : ���װʱAXI���߶�����timeout�ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  def_wr_timeout_en  : 1;  /* bit[11]   : ���װʱAXI����д����timeout�ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  def_cfg_err_en     : 1;  /* bit[12]   : ���װЭ��ѹ��ָʾ���ô����ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  def_in_prm_err_en  : 1;  /* bit[13]   : ���װ����������ز��������ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  def_out_prm_err_en : 1;  /* bit[14]   : ���װ����ռ���ز��������ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  def_rpt_prm_err_en : 1;  /* bit[15]   : ���װ�ϱ��ռ���ز��������ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  def_lcp_int_en     : 1;  /* bit[16]   : ���װ���LCP֡�ж��ϱ�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  def_out_spc_ful_en : 1;  /* bit[17]   : ���װ�ⲿ����洢�ռ������ͣ�ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  def_rpt_ful_en     : 1;  /* bit[18]   : ���װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ�ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  reserved_1         : 5;  /* bit[19-23]: ���� */
        unsigned int  def_over_int_en    : 1;  /* bit[24]   : һ������������װ�����ж�ʹ�ܣ�
                                                              0���жϽ�ֹ��
                                                              1���ж�ʹ�ܣ� */
        unsigned int  reserved_2         : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_HDLC_DEF_EN_UNION;
#endif
#define SOC_HDLC_DEF_EN_def_en_START              (0)
#define SOC_HDLC_DEF_EN_def_en_END                (0)
#define SOC_HDLC_DEF_EN_def_rd_err_en_START       (8)
#define SOC_HDLC_DEF_EN_def_rd_err_en_END         (8)
#define SOC_HDLC_DEF_EN_def_wr_err_en_START       (9)
#define SOC_HDLC_DEF_EN_def_wr_err_en_END         (9)
#define SOC_HDLC_DEF_EN_def_rd_timeout_en_START   (10)
#define SOC_HDLC_DEF_EN_def_rd_timeout_en_END     (10)
#define SOC_HDLC_DEF_EN_def_wr_timeout_en_START   (11)
#define SOC_HDLC_DEF_EN_def_wr_timeout_en_END     (11)
#define SOC_HDLC_DEF_EN_def_cfg_err_en_START      (12)
#define SOC_HDLC_DEF_EN_def_cfg_err_en_END        (12)
#define SOC_HDLC_DEF_EN_def_in_prm_err_en_START   (13)
#define SOC_HDLC_DEF_EN_def_in_prm_err_en_END     (13)
#define SOC_HDLC_DEF_EN_def_out_prm_err_en_START  (14)
#define SOC_HDLC_DEF_EN_def_out_prm_err_en_END    (14)
#define SOC_HDLC_DEF_EN_def_rpt_prm_err_en_START  (15)
#define SOC_HDLC_DEF_EN_def_rpt_prm_err_en_END    (15)
#define SOC_HDLC_DEF_EN_def_lcp_int_en_START      (16)
#define SOC_HDLC_DEF_EN_def_lcp_int_en_END        (16)
#define SOC_HDLC_DEF_EN_def_out_spc_ful_en_START  (17)
#define SOC_HDLC_DEF_EN_def_out_spc_ful_en_END    (17)
#define SOC_HDLC_DEF_EN_def_rpt_ful_en_START      (18)
#define SOC_HDLC_DEF_EN_def_rpt_ful_en_END        (18)
#define SOC_HDLC_DEF_EN_def_over_int_en_START     (24)
#define SOC_HDLC_DEF_EN_def_over_int_en_END       (24)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_RAW_INT_UNION
 �ṹ˵��  : DEF_RAW_INT �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: HDLCԭʼ�ж�״̬�Ĵ���������AXI��д����ԭʼ�жϡ�AXI��дtimeoutԭʼ�жϡ����װ�����ЧLCP֡ԭʼ��ͣ�жϡ����װ�ⲿ����洢�ռ������ͣԭʼ�жϡ����װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣԭʼ�жϡ����װ����ԭʼ�жϣ�ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ�ԭʼ�жϣ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 8;  /* bit[0-7]  : ���� */
        unsigned int  def_rd_err_raw      : 1;  /* bit[8]    : ���װʱAXI���߶���������ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  def_wr_err_raw      : 1;  /* bit[9]    : ���װʱAXI����д��������ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  def_rd_timeoutraw   : 1;  /* bit[10]   : ���װʱAXI���߶�����timeoutԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  def_wr_timeout_raw  : 1;  /* bit[11]   : ���װʱAXI����д����timeoutԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  def_cfg_err_raw     : 1;  /* bit[12]   : ���װģ���쳣ԭʼ�жϣ���ʾ�������ô���
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  def_in_prm_err_raw  : 1;  /* bit[13]   : ���װ����������ز�������ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  def_out_prm_err_raw : 1;  /* bit[14]   : ���װ����ռ���ز�������ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  def_rpt_prm_err_raw : 1;  /* bit[15]   : ���װ�ϱ��ռ���ز�������ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  def_lcp_int_raw     : 1;  /* bit[16]   : ���װ���LCP֡ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  def_out_spc_ful_raw : 1;  /* bit[17]   : ���װ�ⲿ����洢�ռ������ͣԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  def_rpt_ful_raw     : 1;  /* bit[18]   : ���װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  reserved_1          : 5;  /* bit[19-23]: ���� */
        unsigned int  def_over_int_raw    : 1;  /* bit[24]   : һ������������װ����ԭʼ�жϣ�
                                                               0�����жϣ�
                                                               1�����жϣ� */
        unsigned int  reserved_2          : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_HDLC_DEF_RAW_INT_UNION;
#endif
#define SOC_HDLC_DEF_RAW_INT_def_rd_err_raw_START       (8)
#define SOC_HDLC_DEF_RAW_INT_def_rd_err_raw_END         (8)
#define SOC_HDLC_DEF_RAW_INT_def_wr_err_raw_START       (9)
#define SOC_HDLC_DEF_RAW_INT_def_wr_err_raw_END         (9)
#define SOC_HDLC_DEF_RAW_INT_def_rd_timeoutraw_START    (10)
#define SOC_HDLC_DEF_RAW_INT_def_rd_timeoutraw_END      (10)
#define SOC_HDLC_DEF_RAW_INT_def_wr_timeout_raw_START   (11)
#define SOC_HDLC_DEF_RAW_INT_def_wr_timeout_raw_END     (11)
#define SOC_HDLC_DEF_RAW_INT_def_cfg_err_raw_START      (12)
#define SOC_HDLC_DEF_RAW_INT_def_cfg_err_raw_END        (12)
#define SOC_HDLC_DEF_RAW_INT_def_in_prm_err_raw_START   (13)
#define SOC_HDLC_DEF_RAW_INT_def_in_prm_err_raw_END     (13)
#define SOC_HDLC_DEF_RAW_INT_def_out_prm_err_raw_START  (14)
#define SOC_HDLC_DEF_RAW_INT_def_out_prm_err_raw_END    (14)
#define SOC_HDLC_DEF_RAW_INT_def_rpt_prm_err_raw_START  (15)
#define SOC_HDLC_DEF_RAW_INT_def_rpt_prm_err_raw_END    (15)
#define SOC_HDLC_DEF_RAW_INT_def_lcp_int_raw_START      (16)
#define SOC_HDLC_DEF_RAW_INT_def_lcp_int_raw_END        (16)
#define SOC_HDLC_DEF_RAW_INT_def_out_spc_ful_raw_START  (17)
#define SOC_HDLC_DEF_RAW_INT_def_out_spc_ful_raw_END    (17)
#define SOC_HDLC_DEF_RAW_INT_def_rpt_ful_raw_START      (18)
#define SOC_HDLC_DEF_RAW_INT_def_rpt_ful_raw_END        (18)
#define SOC_HDLC_DEF_RAW_INT_def_over_int_raw_START     (24)
#define SOC_HDLC_DEF_RAW_INT_def_over_int_raw_END       (24)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_INT_STATUS_UNION
 �ṹ˵��  : DEF_INT_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: HDLC���κ��ж�״̬�Ĵ���������AXI��д�������κ��ж�״̬��AXI��дtimeout���κ��ж�״̬�����װ�����ЧLCP֡��ͣ���κ��ж�״̬�����װ�ⲿ����洢�ռ������ͣ���κ��ж�״̬�����װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ���κ��ж�״̬�����װ�������κ��ж�״̬��ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ����κ��ж�״̬����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 8;  /* bit[0-7]  : ���� */
        unsigned int  def_rd_err_stat      : 1;  /* bit[8]    : ���װʱAXI���߶������������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  def_wr_err_stat      : 1;  /* bit[9]    : ���װʱAXI����д�����������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  def_rd_timeoutstat   : 1;  /* bit[10]   : ���װʱAXI���߶�����timeout���κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  def_wr_timeout_stat  : 1;  /* bit[11]   : ���װʱAXI����д����timeout���κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  def_cfg_err_stat     : 1;  /* bit[12]   : ���װģ�����κ��ж�״̬����ʾ�������ô����жϣ�
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  def_in_prm_err_stat  : 1;  /* bit[13]   : ���װ����������ز����������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  def_out_prm_err_stat : 1;  /* bit[14]   : ���װ����ռ���ز����������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  def_rpt_prm_err_stat : 1;  /* bit[15]   : ���װ�ϱ��ռ���ز����������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  def_lcp_int_stat     : 1;  /* bit[16]   : ���װ���LCP֡���κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  def_out_spc_ful_stat : 1;  /* bit[17]   : ���װ�ⲿ����洢�ռ������ͣ���κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  def_rpt_ful_stat     : 1;  /* bit[18]   : ���װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ���κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  reserved_1           : 5;  /* bit[19-23]: ���� */
        unsigned int  def_over_int_stat    : 1;  /* bit[24]   : һ������������װ�������κ��ж�״̬��
                                                                0�����жϣ�
                                                                1�����жϣ� */
        unsigned int  reserved_2           : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_HDLC_DEF_INT_STATUS_UNION;
#endif
#define SOC_HDLC_DEF_INT_STATUS_def_rd_err_stat_START       (8)
#define SOC_HDLC_DEF_INT_STATUS_def_rd_err_stat_END         (8)
#define SOC_HDLC_DEF_INT_STATUS_def_wr_err_stat_START       (9)
#define SOC_HDLC_DEF_INT_STATUS_def_wr_err_stat_END         (9)
#define SOC_HDLC_DEF_INT_STATUS_def_rd_timeoutstat_START    (10)
#define SOC_HDLC_DEF_INT_STATUS_def_rd_timeoutstat_END      (10)
#define SOC_HDLC_DEF_INT_STATUS_def_wr_timeout_stat_START   (11)
#define SOC_HDLC_DEF_INT_STATUS_def_wr_timeout_stat_END     (11)
#define SOC_HDLC_DEF_INT_STATUS_def_cfg_err_stat_START      (12)
#define SOC_HDLC_DEF_INT_STATUS_def_cfg_err_stat_END        (12)
#define SOC_HDLC_DEF_INT_STATUS_def_in_prm_err_stat_START   (13)
#define SOC_HDLC_DEF_INT_STATUS_def_in_prm_err_stat_END     (13)
#define SOC_HDLC_DEF_INT_STATUS_def_out_prm_err_stat_START  (14)
#define SOC_HDLC_DEF_INT_STATUS_def_out_prm_err_stat_END    (14)
#define SOC_HDLC_DEF_INT_STATUS_def_rpt_prm_err_stat_START  (15)
#define SOC_HDLC_DEF_INT_STATUS_def_rpt_prm_err_stat_END    (15)
#define SOC_HDLC_DEF_INT_STATUS_def_lcp_int_stat_START      (16)
#define SOC_HDLC_DEF_INT_STATUS_def_lcp_int_stat_END        (16)
#define SOC_HDLC_DEF_INT_STATUS_def_out_spc_ful_stat_START  (17)
#define SOC_HDLC_DEF_INT_STATUS_def_out_spc_ful_stat_END    (17)
#define SOC_HDLC_DEF_INT_STATUS_def_rpt_ful_stat_START      (18)
#define SOC_HDLC_DEF_INT_STATUS_def_rpt_ful_stat_END        (18)
#define SOC_HDLC_DEF_INT_STATUS_def_over_int_stat_START     (24)
#define SOC_HDLC_DEF_INT_STATUS_def_over_int_stat_END       (24)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_INT_CLR_UNION
 �ṹ˵��  : DEF_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: HDLC�ж�����Ĵ���������AXI��д�����ж������AXI��дtimeout�ж���������װ�����ЧLCP֡��ͣ�ж���������װ�ⲿ����洢�ռ������ͣ�ж���������װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ�ж���������װ�����ж������ɾ��ʵ���·����ݶ��ڡ��������ó��ȵ��ж��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 8;  /* bit[0-7]  : ���� */
        unsigned int  def_rd_err_clr      : 1;  /* bit[8]    : def_rd_err�ж������д1����жϣ� */
        unsigned int  def_wr_err_clr      : 1;  /* bit[9]    : def_wr_err�ж������д1����жϣ� */
        unsigned int  def_rd_timeoutclr   : 1;  /* bit[10]   : def_rd_timeout�ж������д1����жϣ� */
        unsigned int  def_wr_timeout_clr  : 1;  /* bit[11]   : def_wr_timeout�ж������д1����жϣ� */
        unsigned int  def_cfg_err_clr     : 1;  /* bit[12]   : def_cfg_err�ж������д1����жϣ� */
        unsigned int  def_in_prm_err_clr  : 1;  /* bit[13]   : def_in_prm_err�ж������д1����жϣ� */
        unsigned int  def_out_prm_err_clr : 1;  /* bit[14]   : def_out_prm_err�ж������д1����жϣ� */
        unsigned int  def_rpt_prm_err_clr : 1;  /* bit[15]   : def_rpt_prm_err�ж������д1����жϣ� */
        unsigned int  def_lcp_int_clr     : 1;  /* bit[16]   : def_lcp_int �ж������д1����жϣ� */
        unsigned int  def_out_spc_ful_clr : 1;  /* bit[17]   : def_out_spc_ful �ж������д1����жϣ� */
        unsigned int  def_rpt_ful_clr     : 1;  /* bit[18]   : def_rpt_ful �ж������д1����жϣ� */
        unsigned int  reserved_1          : 5;  /* bit[19-23]: ���� */
        unsigned int  def_over_int_clr    : 1;  /* bit[24]   : def_over_int �ж������д1����жϣ� */
        unsigned int  reserved_2          : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_HDLC_DEF_INT_CLR_UNION;
#endif
#define SOC_HDLC_DEF_INT_CLR_def_rd_err_clr_START       (8)
#define SOC_HDLC_DEF_INT_CLR_def_rd_err_clr_END         (8)
#define SOC_HDLC_DEF_INT_CLR_def_wr_err_clr_START       (9)
#define SOC_HDLC_DEF_INT_CLR_def_wr_err_clr_END         (9)
#define SOC_HDLC_DEF_INT_CLR_def_rd_timeoutclr_START    (10)
#define SOC_HDLC_DEF_INT_CLR_def_rd_timeoutclr_END      (10)
#define SOC_HDLC_DEF_INT_CLR_def_wr_timeout_clr_START   (11)
#define SOC_HDLC_DEF_INT_CLR_def_wr_timeout_clr_END     (11)
#define SOC_HDLC_DEF_INT_CLR_def_cfg_err_clr_START      (12)
#define SOC_HDLC_DEF_INT_CLR_def_cfg_err_clr_END        (12)
#define SOC_HDLC_DEF_INT_CLR_def_in_prm_err_clr_START   (13)
#define SOC_HDLC_DEF_INT_CLR_def_in_prm_err_clr_END     (13)
#define SOC_HDLC_DEF_INT_CLR_def_out_prm_err_clr_START  (14)
#define SOC_HDLC_DEF_INT_CLR_def_out_prm_err_clr_END    (14)
#define SOC_HDLC_DEF_INT_CLR_def_rpt_prm_err_clr_START  (15)
#define SOC_HDLC_DEF_INT_CLR_def_rpt_prm_err_clr_END    (15)
#define SOC_HDLC_DEF_INT_CLR_def_lcp_int_clr_START      (16)
#define SOC_HDLC_DEF_INT_CLR_def_lcp_int_clr_END        (16)
#define SOC_HDLC_DEF_INT_CLR_def_out_spc_ful_clr_START  (17)
#define SOC_HDLC_DEF_INT_CLR_def_out_spc_ful_clr_END    (17)
#define SOC_HDLC_DEF_INT_CLR_def_rpt_ful_clr_START      (18)
#define SOC_HDLC_DEF_INT_CLR_def_rpt_ful_clr_END        (18)
#define SOC_HDLC_DEF_INT_CLR_def_over_int_clr_START     (24)
#define SOC_HDLC_DEF_INT_CLR_def_over_int_clr_END       (24)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_CFG_UNION
 �ṹ˵��  : DEF_CFG �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ��ģ�����üĴ���
            (�����λ��Ϊdef_uncompleted_ago������ָʾ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ���������Ƿ��н��������֡��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã�0��û�У�1����)��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_uncompleted_ago : 1;  /* bit[0]   : ����ָʾ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ���������Ƿ��н��������֡��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã�0��û�У�1���� */
        unsigned int  def_acfc            : 1;  /* bit[1]   : AC��ѹ��ָʾ��
                                                              0��AC����ѹ����
                                                              1����ʾAC��ѹ���� */
        unsigned int  def_pfc             : 2;  /* bit[2-3] : P��ѹ��ָʾ��
                                                              l 00��P����ѹ��������룻 
                                                              l 01��P��ѹ��������룻
                                                              l 11��P�򲻰��룻
                                                              l ��������Ч�� */
        unsigned int  reserved            : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_HDLC_DEF_CFG_UNION;
#endif
#define SOC_HDLC_DEF_CFG_def_uncompleted_ago_START  (0)
#define SOC_HDLC_DEF_CFG_def_uncompleted_ago_END    (0)
#define SOC_HDLC_DEF_CFG_def_acfc_START             (1)
#define SOC_HDLC_DEF_CFG_def_acfc_END               (1)
#define SOC_HDLC_DEF_CFG_def_pfc_START              (2)
#define SOC_HDLC_DEF_CFG_def_pfc_END                (3)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_UNCOMPLETED_LEN_UNION
 �ṹ˵��  : DEF_UNCOMPLETED_LEN �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡�ĳ��ȣ�Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_uncompleted_len : 16; /* bit[0-15] : ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡�ĳ��ȣ�Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����� */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_HDLC_DEF_UNCOMPLETED_LEN_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLETED_LEN_def_uncompleted_len_START  (0)
#define SOC_HDLC_DEF_UNCOMPLETED_LEN_def_uncompleted_len_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_UNCOMPLETED_PRO_UNION
 �ṹ˵��  : DEF_UNCOMPLETED_PRO �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡��Э�飬Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã��������е�0Byte��1Byte��2Byte��Ч����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_uncompleted_pro : 16; /* bit[0-15] : ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡��Э�飬Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã��������е�0Byte��1Byte��2Byte��Ч�� */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_HDLC_DEF_UNCOMPLETED_PRO_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLETED_PRO_def_uncompleted_pro_START  (0)
#define SOC_HDLC_DEF_UNCOMPLETED_PRO_def_uncompleted_pro_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_UNCOMPLETED_ADDR_UNION
 �ṹ˵��  : DEF_UNCOMPLETED_ADDR �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡���ⲿ�洢��ʼ��ַ��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã��õ�ַ��������ԭ���ϱ���ͬ���µ�ַ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_uncompleted_addr : 32; /* bit[0-31]: ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡���ⲿ�洢��ʼ��ַ��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã��õ�ַ��������ԭ���ϱ���ͬ���µ�ַ�� */
    } reg;
} SOC_HDLC_DEF_UNCOMPLETED_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLETED_ADDR_def_uncompleted_addr_START  (0)
#define SOC_HDLC_DEF_UNCOMPLETED_ADDR_def_uncompleted_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_UNCOMPLET_ST_AGO_UNION
 �ṹ˵��  : DEF_UNCOMPLET_ST_AGO �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ������״̬����ǰ״̬��CRCУ��ֵ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_data_st_curr_ago : 5;  /* bit[0-4]  : �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ������������������״̬����һ״̬ */
        unsigned int  reserved             : 11; /* bit[5-15] : ���� */
        unsigned int  crc16_result_ago     : 16; /* bit[16-31]: �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ��CRCУ��ֵ */
    } reg;
} SOC_HDLC_DEF_UNCOMPLET_ST_AGO_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_def_data_st_curr_ago_START  (0)
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_def_data_st_curr_ago_END    (4)
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_crc16_result_ago_START      (16)
#define SOC_HDLC_DEF_UNCOMPLET_ST_AGO_crc16_result_ago_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_GO_ON_UNION
 �ṹ˵��  : DEF_GO_ON �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͣ״̬����Ĵ��������һ���Ϸ�LCP֡���µĽ��װ��ģ����ͣ״̬��������װ�ⲿ����洢�ռ������ͣ��������װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ�������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_lcp_goon        : 1;  /* bit[0]    : ���һ���Ϸ�LCP֡���µ�Ӳ����ͣ״̬����������װģ��δ������һ������װ�����ݣ�<=2KB(def_in_pkt_len_max)�������һ���Ϸ�LCP֡�������ͣ��֡���ȴ��������˼Ĵ���д��1�����ټ�������ʣ������ݡ� */
        unsigned int  reserved_0          : 7;  /* bit[1-7]  : ���� */
        unsigned int  def_outspc_ful_goon : 1;  /* bit[8]    : �ⲿ���װ������ݴ洢�ռ������ͣ״̬��� */
        unsigned int  reserved_1          : 7;  /* bit[9-15] : ���� */
        unsigned int  def_rpt_ful_goon    : 1;  /* bit[16]   : �ⲿ���װ��Ч֡��Ϣ�ϱ��ռ������ͣ��� */
        unsigned int  reserved_2          : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_HDLC_DEF_GO_ON_UNION;
#endif
#define SOC_HDLC_DEF_GO_ON_def_lcp_goon_START         (0)
#define SOC_HDLC_DEF_GO_ON_def_lcp_goon_END           (0)
#define SOC_HDLC_DEF_GO_ON_def_outspc_ful_goon_START  (8)
#define SOC_HDLC_DEF_GO_ON_def_outspc_ful_goon_END    (8)
#define SOC_HDLC_DEF_GO_ON_def_rpt_ful_goon_START     (16)
#define SOC_HDLC_DEF_GO_ON_def_rpt_ful_goon_END       (16)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_STATUS_UNION
 �ṹ˵��  : DEF_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ��ģ��״̬�Ĵ���������def_uncompleted_now������ָʾ��ǰ�����Ƿ��н��������֡��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã�0��û�У�1���У�����def_out_spc_ful��def_rpt_ful����def_blk_pro_stat��Ϊdef_all_pkt_pro_stat����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_all_pkt_pro_stat : 2;  /* bit[0-1]  : һ������������״̬��
                                                                l 00��δ���һ������������
                                                                l 01��δ���һ�������������ѽ��LCP֡��Ӳ��������ͣ״̬��
                                                                l 10�����һ����������������֡�ϱ���
                                                                l 11: ���һ����������������֡�ϱ��� */
        unsigned int  def_uncompleted_now  : 1;  /* bit[2]    : ����ָʾ��ǰ�����Ƿ��н��������֡��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã�0��û�У�1���� */
        unsigned int  def_out_spc_ful      : 1;  /* bit[3]    : ���װ�ⲿ����洢�ռ������ָͣʾ */
        unsigned int  def_rpt_ful          : 1;  /* bit[4]    : ���װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ָͣʾ */
        unsigned int  def_error_index      : 1;  /* bit[5]    : ���װ��������ָʾ */
        unsigned int  reserved_0           : 2;  /* bit[6-7]  : ���� */
        unsigned int  def_valid_num        : 16; /* bit[8-23] : ��֡�ϱ�ʱ����Ч֡��Ŀ�������������һ�����ܵķ�����֡�� */
        unsigned int  def_err_type         : 7;  /* bit[24-30]: ��֡�ϱ�ʱ������֡���ͣ���Ӧ��bitλΪ1���������������ʹ���
                                                                l bit 30����������6��ת���ַ�0x7D�����һ��Flag��
                                                                l bit 29����������5����AC����ѹ��ʱ��Address��ֵ��0xFF��
                                                                l bit 28����������4����AC����ѹ��ʱ��Control��ֵ��0x03��
                                                                l bit 27����������3����P�������ʱ���յ��Ƿ���Protocol��ֵ��
                                                                l bit 26����������2�����װ��֡�ֽ���С��4bites��
                                                                l bit 25����������1�����װ��֡�ֽ�������1502bytes��PPP֡��Information�򲻳���1500Bytes������Э���򲻳���1502Bytes����
                                                                l bit 24����������0�� CRCУ����� */
        unsigned int  reserved_1           : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_HDLC_DEF_STATUS_UNION;
#endif
#define SOC_HDLC_DEF_STATUS_def_all_pkt_pro_stat_START  (0)
#define SOC_HDLC_DEF_STATUS_def_all_pkt_pro_stat_END    (1)
#define SOC_HDLC_DEF_STATUS_def_uncompleted_now_START   (2)
#define SOC_HDLC_DEF_STATUS_def_uncompleted_now_END     (2)
#define SOC_HDLC_DEF_STATUS_def_out_spc_ful_START       (3)
#define SOC_HDLC_DEF_STATUS_def_out_spc_ful_END         (3)
#define SOC_HDLC_DEF_STATUS_def_rpt_ful_START           (4)
#define SOC_HDLC_DEF_STATUS_def_rpt_ful_END             (4)
#define SOC_HDLC_DEF_STATUS_def_error_index_START       (5)
#define SOC_HDLC_DEF_STATUS_def_error_index_END         (5)
#define SOC_HDLC_DEF_STATUS_def_valid_num_START         (8)
#define SOC_HDLC_DEF_STATUS_def_valid_num_END           (23)
#define SOC_HDLC_DEF_STATUS_def_err_type_START          (24)
#define SOC_HDLC_DEF_STATUS_def_err_type_END            (30)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_UNCOMPLET_ST_NOW_UNION
 �ṹ˵��  : DEF_UNCOMPLET_ST_NOW �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ǰ���װ��������������������֡ʱ������״̬����ǰ״̬��CRCУ��ֵ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_data_st_curr_now : 5;  /* bit[0-4]  : ��ǰ���װ��������������������֡ʱ������״̬����ǰ״̬ */
        unsigned int  reserved             : 11; /* bit[5-15] : ���� */
        unsigned int  crc16_result_now     : 16; /* bit[16-31]: ��ǰ���װ��������������������֡ʱ��CRCУ��ֵ */
    } reg;
} SOC_HDLC_DEF_UNCOMPLET_ST_NOW_UNION;
#endif
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_def_data_st_curr_now_START  (0)
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_def_data_st_curr_now_END    (4)
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_crc16_result_now_START      (16)
#define SOC_HDLC_DEF_UNCOMPLET_ST_NOW_crc16_result_now_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_IN_LLI_ADDR_UNION
 �ṹ˵��  : DEF_IN_LLI_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ�������������ʼ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_in_lli_addr : 32; /* bit[0-31]: ���װ�������������ʼ��ַ�Ĵ��� */
    } reg;
} SOC_HDLC_DEF_IN_LLI_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_IN_LLI_ADDR_def_in_lli_addr_START  (0)
#define SOC_HDLC_DEF_IN_LLI_ADDR_def_in_lli_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_IN_PKT_ADDR_UNION
 �ṹ˵��  : DEF_IN_PKT_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ��������ڵ���ָ�����װ�������ݰ���ʼ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_in_pkt_addr : 32; /* bit[0-31]: ���װ������������д����װ�������ݰ���ʼ��ַ�Ĵ����� */
    } reg;
} SOC_HDLC_DEF_IN_PKT_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_IN_PKT_ADDR_def_in_pkt_addr_START  (0)
#define SOC_HDLC_DEF_IN_PKT_ADDR_def_in_pkt_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_IN_PKT_LEN_UNION
 �ṹ˵��  : DEF_IN_PKT_LEN �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ��������ڵ���ָ�����װ�������ݰ����ȼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_in_pkt_len : 16; /* bit[0-15] : ���װ������������д����װ�������ݰ����ȼĴ����� */
        unsigned int  reserved       : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_HDLC_DEF_IN_PKT_LEN_UNION;
#endif
#define SOC_HDLC_DEF_IN_PKT_LEN_def_in_pkt_len_START  (0)
#define SOC_HDLC_DEF_IN_PKT_LEN_def_in_pkt_len_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_IN_PKT_LEN_MAX_UNION
 �ṹ˵��  : DEF_IN_PKT_LEN_MAX �Ĵ����ṹ���塣��ַƫ����:0x009C����ֵ:0x00000000�����:32
 �Ĵ���˵��: һ�����װ��������ڵ���ָ�����װ�������ݰ���������ȼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_in_pkt_len_max : 16; /* bit[0-15] : �����װ�������ݰ���������ȼĴ�����
                                                              ��������� */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_HDLC_DEF_IN_PKT_LEN_MAX_UNION;
#endif
#define SOC_HDLC_DEF_IN_PKT_LEN_MAX_def_in_pkt_len_max_START  (0)
#define SOC_HDLC_DEF_IN_PKT_LEN_MAX_def_in_pkt_len_max_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_OUT_SPC_ADDR_UNION
 �ṹ˵��  : DEF_OUT_SPC_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ������ݴ洢�ռ���ʼ��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_out_spc_addr : 32; /* bit[0-31]: ���װ������ݴ洢�ռ���ʼ��ַ�Ĵ�����
                                                           ��������� */
    } reg;
} SOC_HDLC_DEF_OUT_SPC_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_OUT_SPC_ADDR_def_out_spc_addr_START  (0)
#define SOC_HDLC_DEF_OUT_SPC_ADDR_def_out_spc_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_OUT_SPC_DEP_UNION
 �ṹ˵��  : DEF_OUT_SPC_DEP �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ������ݴ洢�ռ���ȼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_out_spc_dep : 16; /* bit[0-15] : ���װ������ݴ洢�ռ���ȼĴ�����
                                                           ��������� */
        unsigned int  reserved        : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_HDLC_DEF_OUT_SPC_DEP_UNION;
#endif
#define SOC_HDLC_DEF_OUT_SPC_DEP_def_out_spc_dep_START  (0)
#define SOC_HDLC_DEF_OUT_SPC_DEP_def_out_spc_dep_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_RPT_ADDR_UNION
 �ṹ˵��  : DEF_RPT_ADDR �Ĵ����ṹ���塣��ַƫ����:0x00A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ�����ȷ֡�ϱ���Ϣ�洢�ռ���ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_rpt_addr : 32; /* bit[0-31]: ���װ�����ȷ֡�ϱ���Ϣ�洢�ռ���ʼ��ַ��
                                                       ��������� */
    } reg;
} SOC_HDLC_DEF_RPT_ADDR_UNION;
#endif
#define SOC_HDLC_DEF_RPT_ADDR_def_rpt_addr_START  (0)
#define SOC_HDLC_DEF_RPT_ADDR_def_rpt_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_RPT_DEP_UNION
 �ṹ˵��  : DEF_RPT_DEP �Ĵ����ṹ���塣��ַƫ����:0x00AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ�����ȷ֡�ϱ���Ϣ�洢�ռ���ȡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_out_result_dep : 16; /* bit[0-15] : ���װ�����ȷ֡�ϱ���Ϣ�洢�ռ���ȣ�
                                                              ��������� */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_HDLC_DEF_RPT_DEP_UNION;
#endif
#define SOC_HDLC_DEF_RPT_DEP_def_out_result_dep_START  (0)
#define SOC_HDLC_DEF_RPT_DEP_def_out_result_dep_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_ERR_INFO_0_UNION
 �ṹ˵��  : DEF_ERR_INFO_0 �Ĵ����ṹ���塣��ַƫ����:0x00B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ����֡��Ϣ�Ĵ�������0����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_err0_num : 16; /* bit[0-15] : ����֡�ϱ�ʱ������0�Ĵ���֡�� */
        unsigned int  def_err1_num : 16; /* bit[16-31]: ����֡�ϱ�ʱ������1�Ĵ���֡�� */
    } reg;
} SOC_HDLC_DEF_ERR_INFO_0_UNION;
#endif
#define SOC_HDLC_DEF_ERR_INFO_0_def_err0_num_START  (0)
#define SOC_HDLC_DEF_ERR_INFO_0_def_err0_num_END    (15)
#define SOC_HDLC_DEF_ERR_INFO_0_def_err1_num_START  (16)
#define SOC_HDLC_DEF_ERR_INFO_0_def_err1_num_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_ERR_INFO_1_UNION
 �ṹ˵��  : DEF_ERR_INFO_1 �Ĵ����ṹ���塣��ַƫ����:0x00B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ����֡��Ϣ�Ĵ�������1����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_err2_num : 16; /* bit[0-15] : ����֡�ϱ�ʱ������2�Ĵ���֡�� */
        unsigned int  def_err3_num : 16; /* bit[16-31]: ����֡�ϱ�ʱ������3�Ĵ���֡�� */
    } reg;
} SOC_HDLC_DEF_ERR_INFO_1_UNION;
#endif
#define SOC_HDLC_DEF_ERR_INFO_1_def_err2_num_START  (0)
#define SOC_HDLC_DEF_ERR_INFO_1_def_err2_num_END    (15)
#define SOC_HDLC_DEF_ERR_INFO_1_def_err3_num_START  (16)
#define SOC_HDLC_DEF_ERR_INFO_1_def_err3_num_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_ERR_INFO_2_UNION
 �ṹ˵��  : DEF_ERR_INFO_2 �Ĵ����ṹ���塣��ַƫ����:0x00B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ����֡��Ϣ�Ĵ�������2����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_err4_num : 16; /* bit[0-15] : ����֡�ϱ�ʱ������4�Ĵ���֡�� */
        unsigned int  def_err5_num : 16; /* bit[16-31]: ����֡�ϱ�ʱ������5�Ĵ���֡�� */
    } reg;
} SOC_HDLC_DEF_ERR_INFO_2_UNION;
#endif
#define SOC_HDLC_DEF_ERR_INFO_2_def_err4_num_START  (0)
#define SOC_HDLC_DEF_ERR_INFO_2_def_err4_num_END    (15)
#define SOC_HDLC_DEF_ERR_INFO_2_def_err5_num_START  (16)
#define SOC_HDLC_DEF_ERR_INFO_2_def_err5_num_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_ERR_INFO_3_UNION
 �ṹ˵��  : DEF_ERR_INFO_3 �Ĵ����ṹ���塣��ַƫ����:0x00BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���װ����֡��Ϣ�Ĵ�������3����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_err6_num : 16; /* bit[0-15] : ����֡�ϱ�ʱ������6�Ĵ���֡�� */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_HDLC_DEF_ERR_INFO_3_UNION;
#endif
#define SOC_HDLC_DEF_ERR_INFO_3_def_err6_num_START  (0)
#define SOC_HDLC_DEF_ERR_INFO_3_def_err6_num_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_INFO_FRL_CNT_AGO_UNION
 �ṹ˵��  : DEF_INFO_FRL_CNT_AGO �Ĵ����ṹ���塣��ַƫ����:0x00C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ����Ϣ���Ⱥ�֡���ȡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_info_cnt_ago   : 11; /* bit[0-10] : �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ����Ϣ���� */
        unsigned int  reserved_0         : 5;  /* bit[11-15]: ���� */
        unsigned int  def_framel_cnt_ago : 11; /* bit[16-26]: �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ��֡���� */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_HDLC_DEF_INFO_FRL_CNT_AGO_UNION;
#endif
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_def_info_cnt_ago_START    (0)
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_def_info_cnt_ago_END      (10)
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_def_framel_cnt_ago_START  (16)
#define SOC_HDLC_DEF_INFO_FRL_CNT_AGO_def_framel_cnt_ago_END    (26)


/*****************************************************************************
 �ṹ��    : SOC_HDLC_DEF_INFO_FRL_CNT_NOW_UNION
 �ṹ˵��  : DEF_INFO_FRL_CNT_NOW �Ĵ����ṹ���塣��ַƫ����:0x00C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ǰ���װ��������������������֡ʱ����Ϣ���Ⱥ�֡���ȡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  def_info_cnt_now   : 11; /* bit[0-10] : ��ǰ���װ��������������������֡ʱ����Ϣ���� */
        unsigned int  reserved_0         : 5;  /* bit[11-15]: ���� */
        unsigned int  def_framel_cnt_now : 11; /* bit[16-26]: ��ǰ���װ��������������������֡ʱ��֡���� */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_HDLC_DEF_INFO_FRL_CNT_NOW_UNION;
#endif
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_def_info_cnt_now_START    (0)
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_def_info_cnt_now_END      (10)
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_def_framel_cnt_now_START  (16)
#define SOC_HDLC_DEF_INFO_FRL_CNT_NOW_def_framel_cnt_now_END    (26)

/* ����Ϊת����Ĵ��������Զ����� */

#define    SOC_HDLC_REG_ACTUAL_ADDR(base, offset) ((base)+(offset))

#define    FEATURE_HDLC_MASTER

#ifdef FEATURE_HDLC_MASTER
/*==================================================================================*/
/*===============PPP(HDLC)Ӳ�����ٹ�����صļĴ����Լ��ڴ��ַ�궨��==============*/
/* ͨ�üĴ��� */
#define     SOC_ARM_HDLC_STATE_SW_RST_ADDR(BaseAddr)                    SOC_HDLC_STATE_SW_RST_ADDR(BaseAddr)        /* ״̬��λ�Ĵ�����ַ */
#define     SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(BaseAddr)             SOC_HDLC_PRIOR_TIMEOUT_CTRL_ADDR(BaseAddr)  /* ��װ���װ���ȼ����õ�ַ */
#define     SOC_ARM_HDLC_RD_ERR_CURR_ADDR(BaseAddr)                     SOC_HDLC_RD_ERR_CURR_ADDR_ADDR(BaseAddr)    /* AXI����������ʱ������ַ */
#define     SOC_ARM_HDLC_WR_ERR_CURR_ADDR(BaseAddr)                     SOC_HDLC_WR_ERR_CURR_ADDR_ADDR(BaseAddr)    /* AXIд��������ʱ��д��ַ */

/* ��װ��ģ��Ĵ��� */
#define     SOC_ARM_HDLC_FRM_EN_ADDR(BaseAddr)                          SOC_HDLC_FRM_EN_ADDR(BaseAddr)              /* ��װʹ�ܼĴ�����ַ */
#define     SOC_ARM_HDLC_FRM_RAW_INT_ADDR(BaseAddr)                     SOC_HDLC_FRM_RAW_INT_ADDR(BaseAddr)         /* HDLCģ���ж�ʹ�ܼĴ�����ַ */
#define     SOC_ARM_HDLC_FRM_INT_STATUS_ADDR(BaseAddr)                  SOC_HDLC_FRM_INT_STATUS_ADDR(BaseAddr)      /* ��װ״̬�Ĵ�����ַ */
#define     SOC_ARM_HDLC_FRM_INT_CLR_ADDR(BaseAddr)                     SOC_HDLC_FRM_INT_CLR_ADDR(BaseAddr)         /* ��װ״̬����Ĵ�����ַ */
#define     SOC_ARM_HDLC_FRM_CFG_ADDR(BaseAddr)                         SOC_HDLC_FRM_CFG_ADDR(BaseAddr)             /* ��װģ�����üĴ�����ַ */
#define     SOC_ARM_HDLC_FRM_ACCM_ADDR(BaseAddr)                        SOC_HDLC_FRM_ACCM_ADDR(BaseAddr)            /* ��װģ��ת��ʹ�ܼĴ�����ַ */
#define     SOC_ARM_HDLC_FRM_STATUS_ADDR(BaseAddr)                      SOC_HDLC_FRM_STATUS_ADDR(BaseAddr)          /* ��װ���״̬�Ĵ�����ַ */
#define     SOC_ARM_HDLC_FRM_IN_LLI_ADDR(BaseAddr)                      SOC_HDLC_FRM_IN_LLI_ADDR_ADDR(BaseAddr)     /* ��װ������������ʼ��ַ�Ĵ�����ַ */
#define     SOC_ARM_HDLC_FRM_IN_SUBLLI_ADDR(BaseAddr)                   SOC_HDLC_FRM_IN_SUBLLI_ADDR_ADDR(BaseAddr)  /* ����װ�������ݰ��������븱������ʼ��ַ�Ĵ����ĵ�ַ */
#define     SOC_ARM_HDLC_FRM_IN_PKT_LEN_ADDR(BaseAddr)                  SOC_HDLC_FRM_IN_PKT_LEN_ADDR(BaseAddr)      /* ��װ����������ڵ���ָ����װ�������ݰ����ȼĴ�����ַ */
#define     SOC_ARM_HDLC_FRM_IN_BLK_ADDR(BaseAddr)                      SOC_HDLC_FRM_IN_BLK_ADDR_ADDR(BaseAddr)     /* ��װ���븱����ڵ���ָ����װ�������ݷ�����ʼ��ַ�Ĵ�����ַ */
#define     SOC_ARM_HDLC_FRM_IN_BLK_LEN_ADDR(BaseAddr)                  SOC_HDLC_FRM_IN_BLK_LEN_ADDR(BaseAddr)      /* ��װ���븱����ڵ���ָ����װ�������ݷ��鳤�ȼĴ�����ַ */
#define     SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(BaseAddr)                     SOC_HDLC_FRM_OUT_LLI_ADDR_ADDR(BaseAddr)    /* ��װ���������ʼ��ַ�Ĵ�����ַ */
#define     SOC_ARM_HDLC_FRM_OUT_SPACE_ADDR(BaseAddr)                   SOC_HDLC_FRM_OUT_SPC_ADDR_ADDR(BaseAddr)    /* ��װ�������ڵ���ָ�洢�ռ���ʼ��ַ�Ĵ�����ַ */
#define     SOC_ARM_HDLC_FRM_OUT_SPACE_DEP_ADDR(BaseAddr)               SOC_HDLC_FRM_OUT_SPC_DEP_ADDR(BaseAddr)     /* ��װ�������ڵ���ָ�洢�ռ���ȼĴ�����ַ */
#define     SOC_ARM_HDLC_FRM_RPT_ADDR(BaseAddr)                         SOC_HDLC_FRM_RPT_ADDR_ADDR(BaseAddr)        /* ��װ�������ȷ֡���ȴ洢�ռ���ʼ��ַ�Ĵ�����ַ */
#define     SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(BaseAddr)                     SOC_HDLC_FRM_RPT_DEP_ADDR(BaseAddr)         /* ��װ�������ȷ֡���ȴ洢�ռ���ȼĴ�����ַ */

/* ���װ��ģ��Ĵ��� */
#define     SOC_ARM_HDLC_DEF_EN_ADDR(BaseAddr)                          SOC_HDLC_DEF_EN_ADDR(BaseAddr)              /* ���װʹ�ܼĴ�����ַ */
#define     SOC_ARM_HDLC_DEF_RAW_INT_ADDR(BaseAddr)                     SOC_HDLC_DEF_RAW_INT_ADDR(BaseAddr)         /* HDLCģ���ж�ʹ�ܼĴ�����ַ */
#define     SOC_ARM_HDLC_DEF_INT_STATUS_ADDR(BaseAddr)                  SOC_HDLC_DEF_INT_STATUS_ADDR(BaseAddr)      /* ���װ״̬�Ĵ�����ַ */
#define     SOC_ARM_HDLC_DEF_INT_CLR_ADDR(BaseAddr)                     SOC_HDLC_DEF_INT_CLR_ADDR(BaseAddr)         /* ���װ״̬����Ĵ�����ַ */
#define     SOC_ARM_HDLC_DEF_CFG_ADDR(BaseAddr)                         SOC_HDLC_DEF_CFG_ADDR(BaseAddr)             /* ���װģ�����üĴ�����ַ */
#define     SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(BaseAddr)             SOC_HDLC_DEF_UNCOMPLETED_LEN_ADDR(BaseAddr) /* ������װ����������������֡�ĳ��ȼĴ�����ַ */
#define     SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(BaseAddr)             SOC_HDLC_DEF_UNCOMPLETED_PRO_ADDR(BaseAddr) /* ������װ����������������֡��Э��Ĵ�����ַ */
#define     SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(BaseAddr)                 SOC_HDLC_DEF_UNCOMPLETED_ADDR_ADDR(BaseAddr)/* ������װ����������������֡���ⲿ�洢��ʼ��ַ�ļĴ�����ַ */
#define     SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(BaseAddr)          SOC_HDLC_DEF_UNCOMPLET_ST_AGO_ADDR(BaseAddr)/* ������׽��װ��������������������֡ʱ��CRCУ��ֵ�Լ�����״̬����ǰ״ֵ̬�ļĴ�����ַ */
#define     SOC_ARM_HDLC_DEF_GO_ON_ADDR(BaseAddr)                       SOC_HDLC_DEF_GO_ON_ADDR(BaseAddr)           /* �������װָʾ�Ĵ�����ַ */
#define     SOC_ARM_HDLC_DEF_STATUS_ADDR(BaseAddr)                      SOC_HDLC_DEF_STATUS_ADDR(BaseAddr)          /* ���װ���״̬�Ĵ�����ַ */
#define     SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(BaseAddr)          SOC_HDLC_DEF_UNCOMPLET_ST_NOW_ADDR(BaseAddr)/* ��ǰ���װ��������������������֡ʱ��CRCУ��ֵ�Լ�����״̬����ǰ״ֵ̬�ļĴ�����ַ */
#define     SOC_ARM_HDLC_DEF_IN_LLI_ADDR(BaseAddr)                      SOC_HDLC_DEF_IN_LLI_ADDR_ADDR(BaseAddr)     /* ���װ�������������ʼ��ַ�Ĵ�����ַ */
#define     SOC_ARM_HDLC_DEF_IN_PKT_ADDR(BaseAddr)                      SOC_HDLC_DEF_IN_PKT_ADDR_ADDR(BaseAddr)     /* ���װ������������д����װ�������ݰ���ʼ��ַ�Ĵ�����ַ */
#define     SOC_ARM_HDLC_DEF_IN_PKT_LEN_ADDR(BaseAddr)                  SOC_HDLC_DEF_IN_PKT_LEN_ADDR(BaseAddr)      /* ���װ������������д����װ�������ݰ����ȼĴ�����ַ */
#define     SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(BaseAddr)              SOC_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(BaseAddr)  /* �����װ�������ݰ���������ȼĴ�����ַ */
#define     SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(BaseAddr)                     SOC_HDLC_DEF_OUT_SPC_ADDR_ADDR(BaseAddr)    /* ���װ������ݴ洢�ռ���ʼ��ַ�Ĵ�����ַ */
#define     SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(BaseAddr)               SOC_HDLC_DEF_OUT_SPC_DEP_ADDR(BaseAddr)     /* ���װ������ݴ洢�ռ���ȼĴ�����ַ */
#define     SOC_ARM_HDLC_DEF_RPT_ADDR(BaseAddr)                         SOC_HDLC_DEF_RPT_ADDR_ADDR(BaseAddr)        /* ���װ�����ȷ֡�ϱ���Ϣ�洢�ռ���ʼ��ַ�Ĵ�����ַ */
#define     SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(BaseAddr)                     SOC_HDLC_DEF_RPT_DEP_ADDR(BaseAddr)         /* ���װ�����ȷ֡�ϱ���Ϣ�洢�ռ���ȼĴ�����ַ */
#define     SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(BaseAddr)                  SOC_HDLC_DEF_ERR_INFO_0_ADDR(BaseAddr)      /* ���װ����֡ͳ�ƼĴ�����0�� */
#define     SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(BaseAddr)                  SOC_HDLC_DEF_ERR_INFO_1_ADDR(BaseAddr)      /* ���װ����֡ͳ�ƼĴ�����1�� */
#define     SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(BaseAddr)                  SOC_HDLC_DEF_ERR_INFO_2_ADDR(BaseAddr)      /* ���װ����֡ͳ�ƼĴ�����2�� */
#define     SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(BaseAddr)                  SOC_HDLC_DEF_ERR_INFO_3_ADDR(BaseAddr)      /* ���װ����֡ͳ�ƼĴ�����3�� */
#define     SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(BaseAddr)            SOC_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(BaseAddr)/* ������׽��װ��������������������֡ʱ��֡�����Լ���Ϣ���ȼĴ�����ַ */
#define     SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(BaseAddr)            SOC_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(BaseAddr)/* ��ǰ���װ��������������������֡ʱ��֡�����Լ���Ϣ���ȼĴ�����ַ */
#else

/*==================================================================================*/
/*===============PPP(HDLC)Ӳ�����ٹ�����صļĴ����Լ��ڴ��ַ�궨��==============*/

/*HDLC ���µ�궨��*/
#define    SOC_ARM_HDLC_ENABLE_REG_ADDR                    SOC_HDLC_REG_ACTUAL_ADDR(SOC_ARM_SYSTEM_CONTROL_BASE_ADDR, 0x0038) /*HDLC�ϵ�Ĵ�����ַ*/
#define    SOC_ARM_HDLC_DISABLE_REG_ADDR                   SOC_HDLC_REG_ACTUAL_ADDR(SOC_ARM_SYSTEM_CONTROL_BASE_ADDR, 0x003C) /*HDLC�µ�Ĵ�����ַ*/
#define    SOC_ARM_HDLC_REG_BIT                            (9) /*HDLC���µ�Ĵ�������λ*/

/*
FPGA��Դ���ޣ�HDLC�޵���ʱ�ӣ�ASIC�汾��Ҫ�޸�PPP_HDLC_BY_HARDWAREʹ��
#define    SOC_AMR_HDLC_ENABLE()                           {*(volatile VOS_UINT32 *)SOC_ARM_HDLC_ENABLE_REG_ADDR    |= (1 << SOC_ARM_HDLC_REG_BIT);}
#define    SOC_AMR_HDLC_DISABLE()                          {*(volatile VOS_UINT32 *)SOC_ARM_HDLC_DISABLE_REG_ADDR   |= (1 << SOC_ARM_HDLC_REG_BIT);}

#else
*/
#define    SOC_AMR_HDLC_ENABLE()
#define    SOC_AMR_HDLC_DISABLE()

/* definition of input&output buffer address */
#define     SOC_ARM_HDLC_FRAMER_IN_DATA_ADDR(BaseAddr)                SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x1000)  /* ��װģ�������д���ַ: ÿ��д�벻����256�ֽ����ݵ���ʼ��ַ */
#define     SOC_ARM_HDLC_FRAMER_OUT_DATA_ADDR(BaseAddr)               SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x2000)  /* ��װģ������ݶ�����ַ: ��װ���ʱ���ݴ�ŵ���ʼ��ַ */
#define     SOC_ARM_HDLC_DEFRAMER_IN_DATA_ADDR(BaseAddr)              SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x3000)  /* ���װģ�������д���ַ: ÿ��д�벻����256�ֽ����ݵ���ʼ��ַ */
#define     SOC_ARM_HDLC_DEFRAMER_OUT_DATA_BASE_ADDR(BaseAddr)        SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x4000)  /* ���װģ������ݴ�ŵĻ���ַ: ���װ�����֡�����ݴ�����ݵĻ���ַ */
#define     SOC_ARM_HDLC_DEFRAMER_OUT_LIST_ADDR(BaseAddr)             SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x6000)  /* ���װģ���ϱ��б��ַ: ���װ���������֡��Ϣ����ʼ��ַ */
/* definition of registers' address */
#define     SOC_ARM_HDLC_INTERRUPT_ENABLE_ADDR(BaseAddr)              SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0004)   /* HDLCģ���ж�ʹ�ܼĴ�����ַ: ���ƫ�Ƶ�ַ��0x04 */
#define     SOC_ARM_HDLC_INTERRUPT_FRAMER_RAW_INT_ADDR(BaseAddr)      SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0008)   /* HDLCģ���ж�ʹ�ܼĴ�����ַ: ���ƫ�Ƶ�ַ��0x08 */
#define     SOC_ARM_HDLC_INTERRUPT_INT_STATUS_ADDR(BaseAddr)          SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x000C)   /* HDLCģ���ж�ʹ�ܼĴ�����ַ: ���ƫ�Ƶ�ַ��0x0C */
#define     SOC_ARM_HDLC_FRAMER_INTERRUPT_CLEAR_ADDR(BaseAddr)        SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0010)   /* HDLCģ���ж�����Ĵ�����ַ: ���ƫ�Ƶ�ַ��0x10 */
#define     SOC_ARM_HDLC_FRAMER_CFG_ADDR(BaseAddr)                    SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0020)   /* ��װģ�����üĴ�����ַ: ���ƫ�Ƶ�ַ��0x20 */
#define     SOC_ARM_HDLC_FRAMER_ACCM_ADDR(BaseAddr)                   SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0024)   /* ��װģ��ת��ʹ�ܼĴ�����ַ: ���ƫ�Ƶ�ַ��0x24 */
#define     SOC_ARM_HDLC_FRAMER_CTRL_ADDR(BaseAddr)                   SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0028)   /* ��װģ����ƼĴ�����ַ: ���ƫ�Ƶ�ַ��0x28 */
#define     SOC_ARM_HDLC_FRAMER_STATUS_ADDR(BaseAddr)                 SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x002C)   /* ��װģ��״̬�Ĵ�����ַ: ���ƫ�Ƶ�ַ��0x2C */
#define     SOC_ARM_HDLC_DEFRAMER_CFG_ADDR(BaseAddr)                  SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0040)   /* hdlc_def_cfg (0x40) */
#define     SOC_ARM_HDLC_DEFRAMER_CTRL_ADDR(BaseAddr)                 SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0044)   /* hdlc_def_ctrl (0x44) */
#define     SOC_ARM_HDLC_DEFRAMER_GO_ON_ADDR(BaseAddr)                SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0048)   /* hdlc_def_go_on(0x48) */
#define     SOC_ARM_HDLC_DEFRAMER_STATUS_ADDR(BaseAddr)               SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x004C)   /* ���װ״̬�Ĵ�����ַ: ���ƫ�Ƶ�ַ��0x4C */
#define     SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_0_ADDR(BaseAddr)         SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0050)   /* ���װ����֡ͳ�ƼĴ�����0�� */
#define     SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_1_ADDR(BaseAddr)         SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0054)   /* ���װ����֡ͳ�ƼĴ�����1�� */
#define     SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_2_ADDR(BaseAddr)         SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x0058)   /* ���װ����֡ͳ�ƼĴ�����2�� */
#define     SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_3_ADDR(BaseAddr)         SOC_HDLC_REG_ACTUAL_ADDR(BaseAddr,0x005C)   /* ���װ����֡ͳ�ƼĴ�����3�� */
#endif




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

#endif /* end of soc_hdlc_interface.h */
