

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_CICOM_INTERFACE_H__
#define __SOC_CICOM_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) CICOM
 ****************************************************************************/
/* �Ĵ���˵����[�ӽ��ܹ���]CICOM��λ�Ĵ�����
            �������CICOM�쳣ʱ����üĴ�����bit[0]д��1'b1����CICOMģ�������λ��
            ���üĴ�������ֵΪ0x0��
   λ����UNION�ṹ:  SOC_CICOM_STATE_RESET_UNION */
#define SOC_CICOM_STATE_RESET_ADDR(base)        ((base) + (0x0000))

/* �Ĵ���˵����[�ӽ��ܹ���]�ٲò���ѡ��Ĵ�����
            д�üĴ������ü������������������ٲò��ԡ�
            ע���ڼӽ��ܴ�������У���������ԸüĴ������и�д���Ը����ٲò��ԡ�����Ƶ���л��ٲò��Իᵼ�¼ӽ��ܷ���������С���˽��������ҪƵ�������ٲò��ԡ�
   λ����UNION�ṹ:  SOC_CICOM_PRIOR_SELECT_UNION */
#define SOC_CICOM_PRIOR_SELECT_ADDR(base)       ((base) + (0x0004))

/* �Ĵ���˵����[����]����������ʼ��ַ�Ĵ�����
            �üĴ����������ü���ʱ����һ��PDU����Ӧ�Ĳ����������ʼ��ַ��
            �ڼ��ܴ�������У��üĴ�����ֵ��Ӳ���Զ�����Ϊ��ǰ���ڼ��ܵ�PDU����Ӧ�Ĳ����������ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_LLI_PARAM_ADDR_UL_UNION */
#define SOC_CICOM_LLI_PARAM_ADDR_UL_ADDR(base)  ((base) + (0x0008))

/* �Ĵ���˵����[����]ȫ�ּ��ܲ������üĴ�����
            �üĴ�����������һ������ֻ������һ�Σ����谴��PDU�����ȸ��µļ��ܲ�����
   λ����UNION�ṹ:  SOC_CICOM_GLOBAL_CFG_UL_UNION */
#define SOC_CICOM_GLOBAL_CFG_UL_ADDR(base)      ((base) + (0x000C))

/* �Ĵ���˵����[����]���λ����ŵ��׵�ַ�Ĵ�����
            Wģ����ʱ��������ݵ�����������������ŵ�����CHL_FST_ADDR_UL��CHL_LST_ADDR_UL�Ĵ�����
            ����Ҫ��DST2��д�����Ŀ������ʱ��Ӳ������DST2Ŀ�����ݶ���ʼ��ַDST2_SEG_ADDR_UL�����ݶγ���DST2_SEG_LEN_UL�Լ����λ����ŵ��ס�ĩ��ַ�Զ��ж��Ƿ���Ҫ�ƻء�����Ҫ�ƻأ����ƻغ�Ӹ����õ�ַ��д��
   λ����UNION�ṹ:  SOC_CICOM_CHL_FST_ADDR_UL_UNION */
#define SOC_CICOM_CHL_FST_ADDR_UL_ADDR(base)    ((base) + (0x0010))

/* �Ĵ���˵����[����]���λ����ŵ�ĩ��ַ�Ĵ�����
            Wģ����ʱ��������ݵ�����������������ŵ�����CHL_FST_ADDR_UL��CHL_LST_ADDR_UL�Ĵ�����
            ����Ҫ��DST2��д�����Ŀ������ʱ��Ӳ������DST2Ŀ�����ݶ���ʼ��ַDST2_SEG_ADDR_UL�����ݶγ���DST2_SEG_LEN_UL�Լ����λ����ŵ��ס�ĩ��ַ�Զ��ж��Ƿ���Ҫ�ƻء�����Ҫ�ƻأ���д�������õ�ַʱ��ʼ�ƻء�
   λ����UNION�ṹ:  SOC_CICOM_CHL_LST_ADDR_UL_UNION */
#define SOC_CICOM_CHL_LST_ADDR_UL_ADDR(base)    ((base) + (0x0014))

/* �Ĵ���˵����[����]�ж�ʹ��/���μĴ�����
            д�üĴ������ø������ж�ʹ�ܻ����Ρ�
   λ����UNION�ṹ:  SOC_CICOM_INT_EN_UL_UNION */
#define SOC_CICOM_INT_EN_UL_ADDR(base)          ((base) + (0x0018))

/* �Ĵ���˵����[����]ԭʼ�ж�״̬�Ĵ�����
            ���üĴ������ظ��жϵ�ԭʼ�ж�״̬��
   λ����UNION�ṹ:  SOC_CICOM_INT_RAW_UL_UNION */
#define SOC_CICOM_INT_RAW_UL_ADDR(base)         ((base) + (0x001C))

/* �Ĵ���˵����[����]�ж�״̬����Ĵ�����
            ��üĴ�������Ӧbitд1'b1�����Ӧ�����жϣ�д1'b0��Ӱ�졣
            ���üĴ�������ֵΪ0x0��
   λ����UNION�ṹ:  SOC_CICOM_INT_CLR_UL_UNION */
#define SOC_CICOM_INT_CLR_UL_ADDR(base)         ((base) + (0x0020))

/* �Ĵ���˵����[����]���κ�ļ����ж�״̬�Ĵ�����
            ���üĴ������ظ������жϵ����κ��ж�״̬��
   λ����UNION�ṹ:  SOC_CICOM_INT_MSK_UL_UNION */
#define SOC_CICOM_INT_MSK_UL_ADDR(base)         ((base) + (0x0024))

/* �Ĵ���˵����[����]ʹ�ܼĴ�����
            ���׼�����������úü��ܲ����Ĵ���֮����üĴ�����bit[0]д��1'b1�������ܲ�����
            ���ܲ�����ɺ���Ӳ���Զ��ԸüĴ������㡣
            ���ܹ��̳���ʱ��Ӳ��Ҳ��ԸüĴ����Զ����㣬ʹ�ڲ�״̬������IDLE״̬��
            ���üĴ������ؼ��ܴ���״̬��
                ����ֵΪ0x0����ʾCICOMû�н��м��ܴ���
                ����ֵΪ0x1����ʾCICOM���ڽ��м��ܴ���
   λ����UNION�ṹ:  SOC_CICOM_EN_UL_UNION */
#define SOC_CICOM_EN_UL_ADDR(base)              ((base) + (0x0028))

/* �Ĵ���˵����[����]CK�������ⲿMemory�еĵ�ַ�Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ��CK����������ⲿMemory�е���ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_CK_ADDR_UL_UNION */
#define SOC_CICOM_CK_ADDR_UL_ADDR(base)         ((base) + (0x002C))

/* �Ĵ���˵����[����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ��CK������bit[31:0]��
   λ����UNION�ṹ:  SOC_CICOM_CK_31_0_UL_UNION */
#define SOC_CICOM_CK_31_0_UL_ADDR(base)         ((base) + (0x0030))

/* �Ĵ���˵����[����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ��CK������bit[63:32]��
   λ����UNION�ṹ:  SOC_CICOM_CK_63_32_UL_UNION */
#define SOC_CICOM_CK_63_32_UL_ADDR(base)        ((base) + (0x0034))

/* �Ĵ���˵����[����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ��CK������bit[95:64]��
   λ����UNION�ṹ:  SOC_CICOM_CK_95_64_UL_UNION */
#define SOC_CICOM_CK_95_64_UL_ADDR(base)        ((base) + (0x0038))

/* �Ĵ���˵����[����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ��CK������bit[127:96]��
   λ����UNION�ṹ:  SOC_CICOM_CK_127_96_UL_UNION */
#define SOC_CICOM_CK_127_96_UL_ADDR(base)       ((base) + (0x003C))

/* �Ĵ���˵����[����]CC�����Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ��CC������
   λ����UNION�ṹ:  SOC_CICOM_CC_UL_UNION */
#define SOC_CICOM_CC_UL_ADDR(base)              ((base) + (0x0040))

/* �Ĵ���˵����[����]PDU�������ܳ��ȼĴ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU���������ܳ��ȣ��Ա�����Ϊ��λ��
   λ����UNION�ṹ:  SOC_CICOM_PDU_TOTAL_LEN_UL_UNION */
#define SOC_CICOM_PDU_TOTAL_LEN_UL_ADDR(base)   ((base) + (0x0044))

/* �Ĵ���˵����[����]����ʽ�Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU�������ݴ���ʽ��������PDU����Դ�����Ƿ�ֶΡ�Ŀ�������Ƿ�ֶΡ��Ƿ������Կ���Ƿ񽫲�������Կ��Դ���������ȡ�
   λ����UNION�ṹ:  SOC_CICOM_CUSTOM_CFG_UL_UNION */
#define SOC_CICOM_CUSTOM_CFG_UL_ADDR(base)      ((base) + (0x0048))

/* �Ĵ���˵����[����]Դ���ݶ���ʼ��ַ�Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�Դ���ݶε���ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_SRC_SEG_ADDR_UL_UNION */
#define SOC_CICOM_SRC_SEG_ADDR_UL_ADDR(base)    ((base) + (0x004C))

/* �Ĵ���˵����[����]Դ���ݶγ��ȼĴ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�Դ���ݶεĳ��ȣ��Ա�����Ϊ��λ��
   λ����UNION�ṹ:  SOC_CICOM_SRC_SEG_LEN_UL_UNION */
#define SOC_CICOM_SRC_SEG_LEN_UL_ADDR(base)     ((base) + (0x0050))

/* �Ĵ���˵����[����]��һ��SRC������ʼ��ַ�Ĵ�����
            ���üĴ���������һ��SRC�������ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_LLI_SRC_SEG_ADDR_UL_UNION */
#define SOC_CICOM_LLI_SRC_SEG_ADDR_UL_ADDR(base) ((base) + (0x0054))

/* �Ĵ���˵����[����]Ŀ�����ݶδ����DST1 Memory����ʼ��ַ�Ĵ�����
            ���üĴ������ص�ǰ����д��DST1 Memory��Ŀ�����ݶε���ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_DST1_SEG_ADDR_UL_UNION */
#define SOC_CICOM_DST1_SEG_ADDR_UL_ADDR(base)   ((base) + (0x0058))

/* �Ĵ���˵����[����]�����DST1 Memory��Ŀ�����ݶγ��ȼĴ�����
            ���üĴ������ص�ǰ����д��DST1 Memory�е�Ŀ�����ݶεĳ��ȡ�
   λ����UNION�ṹ:  SOC_CICOM_DST1_SEG_LEN_UL_UNION */
#define SOC_CICOM_DST1_SEG_LEN_UL_ADDR(base)    ((base) + (0x005C))

/* �Ĵ���˵����[����]��һ��DST1������ʼ��ַ�Ĵ�����
            ���üĴ���������һ��DST1�������ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_LLI_DST1_SEG_ADDR_UL_UNION */
#define SOC_CICOM_LLI_DST1_SEG_ADDR_UL_ADDR(base) ((base) + (0x0060))

/* �Ĵ���˵����[����]Ŀ�����ݶδ����DST2�е���ʼ��ַ�Ĵ�����
            ���üĴ������ص�ǰ����д��DST2�е�Ŀ�����ݶε���ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_DST2_SEG_ADDR_UL_UNION */
#define SOC_CICOM_DST2_SEG_ADDR_UL_ADDR(base)   ((base) + (0x0064))

/* �Ĵ���˵����[����]�����DST2�е�Ŀ�����ݶγ��ȼĴ�����
            ���üĴ������ص�ǰ����д��DST2�е�Ŀ�����ݶεĳ��ȡ�
   λ����UNION�ṹ:  SOC_CICOM_DST2_SEG_LEN_UL_UNION */
#define SOC_CICOM_DST2_SEG_LEN_UL_ADDR(base)    ((base) + (0x0068))

/* �Ĵ���˵����[����]��һ��DST2������ʼ��ַ�Ĵ�����
            ���üĴ���������һ��DST2�������ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_LLI_DST2_SEG_ADDR_UL_UNION */
#define SOC_CICOM_LLI_DST2_SEG_ADDR_UL_ADDR(base) ((base) + (0x006C))

/* �Ĵ���˵����[����]�����ַ�Ĵ�����
            ���üĴ������ؼ��ܹ�����AXI SLAVE�෴��ERROR��Ӧʱ�ķ��ʵ�ַ��
   λ����UNION�ṹ:  SOC_CICOM_ERROR_ADDR_UL_UNION */
#define SOC_CICOM_ERROR_ADDR_UL_ADDR(base)      ((base) + (0x0070))

/* �Ĵ���˵����[����]Դ���ݶε�ǰ����ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_CICOM_SRC_SEG_RD_ADDR_UL_UNION */
#define SOC_CICOM_SRC_SEG_RD_ADDR_UL_ADDR(base) ((base) + (0x0074))

/* �Ĵ���˵����[����]��ǰԴ���ݶ���ʣ��δ��ȡ���ݳ��ȼĴ��������ֽڣ�Byte����Ϊ��λ��
   λ����UNION�ṹ:  SOC_CICOM_SRC_SEG_LEAVE_LEN_UL_UNION */
#define SOC_CICOM_SRC_SEG_LEAVE_LEN_UL_ADDR(base) ((base) + (0x0078))

/* �Ĵ���˵����[����]DST1Ŀ�����ݶε�ǰд��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_CICOM_DST1_SEG_WR_ADDR_UL_UNION */
#define SOC_CICOM_DST1_SEG_WR_ADDR_UL_ADDR(base) ((base) + (0x007C))

/* �Ĵ���˵����[����]��ǰDST1Ŀ�����ݶ���ʣ��δд���ݳ��ȼĴ��������ֽڣ�Byte����Ϊ��λ��
   λ����UNION�ṹ:  SOC_CICOM_DST1_SEG_LEAVE_LEN_UL_UNION */
#define SOC_CICOM_DST1_SEG_LEAVE_LEN_UL_ADDR(base) ((base) + (0x0080))

/* �Ĵ���˵����[����]DST2Ŀ�����ݶε�ǰд��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_CICOM_DST2_SEG_WR_ADDR_UL_UNION */
#define SOC_CICOM_DST2_SEG_WR_ADDR_UL_ADDR(base) ((base) + (0x0084))

/* �Ĵ���˵����[����]��ǰDST2Ŀ�����ݶ���ʣ��δд���ݳ��ȼĴ��������ֽڣ�Byte����Ϊ��λ��
   λ����UNION�ṹ:  SOC_CICOM_DST2_SEG_LEAVE_LEN_UL_UNION */
#define SOC_CICOM_DST2_SEG_LEAVE_LEN_UL_ADDR(base) ((base) + (0x0088))

/* �Ĵ���˵����[����]����������ʼ��ַ�Ĵ�����
            �üĴ����������ý���ʱ����һ��PDU����Ӧ�Ĳ����������ʼ��ַ��
            �ڽ��ܴ�������У��üĴ�����ֵ��Ӳ���Զ�����Ϊ��ǰ���ڽ��ܵ�PDU����Ӧ�Ĳ����������ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_LLI_PARAM_ADDR_DL_UNION */
#define SOC_CICOM_LLI_PARAM_ADDR_DL_ADDR(base)  ((base) + (0x0108))

/* �Ĵ���˵����[����]ȫ�ֽ��ܲ������üĴ�����
            �üĴ�����������һ������ֻ������һ�Σ����谴��PDU�����ȸ��µĽ��ܲ�����
   λ����UNION�ṹ:  SOC_CICOM_GLOBAL_CFG_DL_UNION */
#define SOC_CICOM_GLOBAL_CFG_DL_ADDR(base)      ((base) + (0x010C))

/* �Ĵ���˵����[����]�ж�ʹ��/���μĴ�����
            д�üĴ������ø������ж�ʹ�ܻ����Ρ�
   λ����UNION�ṹ:  SOC_CICOM_INT_EN_DL_UNION */
#define SOC_CICOM_INT_EN_DL_ADDR(base)          ((base) + (0x0118))

/* �Ĵ���˵����[����]ԭʼ�ж�״̬�Ĵ�����
            ���üĴ������ظ��жϵ�ԭʼ�ж�״̬��
   λ����UNION�ṹ:  SOC_CICOM_INT_RAW_DL_UNION */
#define SOC_CICOM_INT_RAW_DL_ADDR(base)         ((base) + (0x011C))

/* �Ĵ���˵����[����]�ж�״̬����Ĵ�����
            ��üĴ�������Ӧbitд1'b1�����Ӧ�����жϣ�д1'b0��Ӱ�졣
            ���üĴ�������ֵΪ0x0��
   λ����UNION�ṹ:  SOC_CICOM_INT_CLR_DL_UNION */
#define SOC_CICOM_INT_CLR_DL_ADDR(base)         ((base) + (0x0120))

/* �Ĵ���˵����[����]���κ�Ľ����ж�״̬�Ĵ�����
            ���üĴ������ظ������жϵ����κ��ж�״̬��
   λ����UNION�ṹ:  SOC_CICOM_INT_MSK_DL_UNION */
#define SOC_CICOM_INT_MSK_DL_ADDR(base)         ((base) + (0x0124))

/* �Ĵ���˵����[����]ʹ�ܼĴ�����
            ���׼�����������úý��ܲ����Ĵ���֮����üĴ�����bit[0]д��1'b1�������ܲ�����
            ���ܲ�����ɺ���Ӳ���Զ��ԸüĴ������㡣
            ���ܹ��̳���ʱ��Ӳ��Ҳ��ԸüĴ����Զ����㣬ʹ�ڲ�״̬������IDLE״̬��
            ���üĴ������ؽ��ܴ���״̬��
                ����ֵΪ0x0����ʾCICOMû�н��н��ܴ���
                ����ֵΪ0x1����ʾCICOM���ڽ��н��ܴ���
   λ����UNION�ṹ:  SOC_CICOM_EN_DL_UNION */
#define SOC_CICOM_EN_DL_ADDR(base)              ((base) + (0x0128))

/* �Ĵ���˵����[����]CK�������ⲿMemory�еĵ�ַ�Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ��CK����������ⲿMemory�е���ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_CK_ADDR_DL_UNION */
#define SOC_CICOM_CK_ADDR_DL_ADDR(base)         ((base) + (0x012C))

/* �Ĵ���˵����[����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ��CK������bit[31:0]��
   λ����UNION�ṹ:  SOC_CICOM_CK_31_0_DL_UNION */
#define SOC_CICOM_CK_31_0_DL_ADDR(base)         ((base) + (0x0130))

/* �Ĵ���˵����[����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ��CK������bit[63:32]��
   λ����UNION�ṹ:  SOC_CICOM_CK_63_32_DL_UNION */
#define SOC_CICOM_CK_63_32_DL_ADDR(base)        ((base) + (0x0134))

/* �Ĵ���˵����[����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ��CK������bit[95:64]��
   λ����UNION�ṹ:  SOC_CICOM_CK_95_64_DL_UNION */
#define SOC_CICOM_CK_95_64_DL_ADDR(base)        ((base) + (0x0138))

/* �Ĵ���˵����[����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ��CK������bit[127:96]��
   λ����UNION�ṹ:  SOC_CICOM_CK_127_96_DL_UNION */
#define SOC_CICOM_CK_127_96_DL_ADDR(base)       ((base) + (0x013C))

/* �Ĵ���˵����[����]CC�����Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ��CC������
   λ����UNION�ṹ:  SOC_CICOM_CC_DL_UNION */
#define SOC_CICOM_CC_DL_ADDR(base)              ((base) + (0x0140))

/* �Ĵ���˵����[����]PDU�������ܳ��ȼĴ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU���������ܳ��ȣ��Ա�����Ϊ��λ��
   λ����UNION�ṹ:  SOC_CICOM_PDU_TOTAL_LEN_DL_UNION */
#define SOC_CICOM_PDU_TOTAL_LEN_DL_ADDR(base)   ((base) + (0x0144))

/* �Ĵ���˵����[����]����ʽ�Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU�������ݴ���ʽ��������PDU����Դ�����Ƿ�ֶΡ�Ŀ�������Ƿ�ֶΡ��Ƿ������Կ���Ƿ񽫲�������Կ��Դ���������ȡ�
   λ����UNION�ṹ:  SOC_CICOM_CUSTOM_CFG_DL_UNION */
#define SOC_CICOM_CUSTOM_CFG_DL_ADDR(base)      ((base) + (0x0148))

/* �Ĵ���˵����[����]Դ���ݶ���ʼ��ַ�Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�Դ���ݶε���ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_SRC_SEG_ADDR_DL_UNION */
#define SOC_CICOM_SRC_SEG_ADDR_DL_ADDR(base)    ((base) + (0x014C))

/* �Ĵ���˵����[����]Դ���ݶγ��ȼĴ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�Դ���ݶεĳ��ȣ��Ա�����Ϊ��λ��
   λ����UNION�ṹ:  SOC_CICOM_SRC_SEG_LEN_DL_UNION */
#define SOC_CICOM_SRC_SEG_LEN_DL_ADDR(base)     ((base) + (0x0150))

/* �Ĵ���˵����[����]��һ��SRC������ʼ��ַ�Ĵ�����
            ���üĴ���������һ��SRC�������ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_LLI_SRC_SEG_ADDR_DL_UNION */
#define SOC_CICOM_LLI_SRC_SEG_ADDR_DL_ADDR(base) ((base) + (0x0154))

/* �Ĵ���˵����[����]Ŀ�����ݶδ����DST1 Memory����ʼ��ַ�Ĵ�����
            ���üĴ������ص�ǰ����д��DST1 Memory��Ŀ�����ݶε���ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_DST1_SEG_ADDR_DL_UNION */
#define SOC_CICOM_DST1_SEG_ADDR_DL_ADDR(base)   ((base) + (0x0158))

/* �Ĵ���˵����[����]�����DST1 Memory��Ŀ�����ݶγ��ȼĴ�����
            ���üĴ������ص�ǰ����д��DST1 Memory�е�Ŀ�����ݶεĳ��ȡ�
   λ����UNION�ṹ:  SOC_CICOM_DST1_SEG_LEN_DL_UNION */
#define SOC_CICOM_DST1_SEG_LEN_DL_ADDR(base)    ((base) + (0x015C))

/* �Ĵ���˵����[����]��һ��DST1������ʼ��ַ�Ĵ�����
            ���üĴ���������һ��DST1�������ʼ��ַ��
   λ����UNION�ṹ:  SOC_CICOM_LLI_DST1_SEG_ADDR_DL_UNION */
#define SOC_CICOM_LLI_DST1_SEG_ADDR_DL_ADDR(base) ((base) + (0x0160))

/* �Ĵ���˵����[����]�����ַ�Ĵ�����
            ���üĴ������ؽ��ܹ�����AXI SLAVE�෴��ERROR��Ӧʱ�ķ��ʵ�ַ��
   λ����UNION�ṹ:  SOC_CICOM_ERROR_ADDR_DL_UNION */
#define SOC_CICOM_ERROR_ADDR_DL_ADDR(base)      ((base) + (0x0170))

/* �Ĵ���˵����[����]Դ���ݶε�ǰ����ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_CICOM_SRC_SEG_RD_ADDR_DL_UNION */
#define SOC_CICOM_SRC_SEG_RD_ADDR_DL_ADDR(base) ((base) + (0x0174))

/* �Ĵ���˵����[����]��ǰԴ���ݶ���ʣ��δ��ȡ���ݳ��ȼĴ��������ֽڣ�Byte����Ϊ��λ��
   λ����UNION�ṹ:  SOC_CICOM_SRC_SEG_LEAVE_LEN_DL_UNION */
#define SOC_CICOM_SRC_SEG_LEAVE_LEN_DL_ADDR(base) ((base) + (0x0178))

/* �Ĵ���˵����[����]DST1Ŀ�����ݶε�ǰд��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_CICOM_DST1_SEG_WR_ADDR_DL_UNION */
#define SOC_CICOM_DST1_SEG_WR_ADDR_DL_ADDR(base) ((base) + (0x017C))

/* �Ĵ���˵����[����]��ǰDST1Ŀ�����ݶ���ʣ��δд���ݳ��ȼĴ��������ֽڣ�Byte����Ϊ��λ��
   λ����UNION�ṹ:  SOC_CICOM_DST1_SEG_LEAVE_LEN_DL_UNION */
#define SOC_CICOM_DST1_SEG_LEAVE_LEN_DL_ADDR(base) ((base) + (0x0180))





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
                     (1/1) CICOM
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CICOM_STATE_RESET_UNION
 �ṹ˵��  : STATE_RESET �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: [�ӽ��ܹ���]CICOM��λ�Ĵ�����
            �������CICOM�쳣ʱ����üĴ�����bit[0]д��1'b1����CICOMģ�������λ��
            ���üĴ�������ֵΪ0x0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cicom_state_reset : 1;  /* bit[0]   : ���bitλд��1'b1ʵ�ֶ�CICOM����λ��д0��Ӱ�졣
                                                            ��ʱ����0�� */
        unsigned int  reserved          : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_CICOM_STATE_RESET_UNION;
#endif
#define SOC_CICOM_STATE_RESET_cicom_state_reset_START  (0)
#define SOC_CICOM_STATE_RESET_cicom_state_reset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_PRIOR_SELECT_UNION
 �ṹ˵��  : PRIOR_SELECT �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: [�ӽ��ܹ���]�ٲò���ѡ��Ĵ�����
            д�üĴ������ü������������������ٲò��ԡ�
            ע���ڼӽ��ܴ�������У���������ԸüĴ������и�д���Ը����ٲò��ԡ�����Ƶ���л��ٲò��Իᵼ�¼ӽ��ܷ���������С���˽��������ҪƵ�������ٲò��ԡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prior_select : 2;  /* bit[0-1] : �������������������ٲò���ѡ���źš�
                                                       2'b00���ȵ��ȷ��񡣼�������������Ч���ȴ�����ܣ�������������Ч�����ȴ�����ܡ����ڴ���ļ��ܴ���ͽ��ܹ��̶���������ϡ�������ʹ�ܵļ��ܻ��߽��ܱ����������ʹ�ܵļ��ܻ��߽��ܵĴ�����Ϻ󣬲��ܿ�ʼ����
                                                       2'b01���������ȡ����ܹ����������������ϡ�������ܽ��й����У�����������Ч���򽫵�ǰPDU��������ɺ��л������ܴ������ܴ����������������ϡ���ȵ��μ��ܵ�����PDU����������Ϻ󣬲����л������ܴ���
                                                       2'b10���������ȡ����ܹ����������������ϡ�������ܽ��й����У�����������Ч���򽫵�ǰPDU��������ɺ��л������ܴ������ܴ����������������ϡ���ȵ��ν��ܵ�����PDU����������Ϻ󣬲����л������ܴ���
                                                       2'b11���Ƿ����á� */
        unsigned int  reserved     : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_CICOM_PRIOR_SELECT_UNION;
#endif
#define SOC_CICOM_PRIOR_SELECT_prior_select_START  (0)
#define SOC_CICOM_PRIOR_SELECT_prior_select_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_LLI_PARAM_ADDR_UL_UNION
 �ṹ˵��  : LLI_PARAM_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]����������ʼ��ַ�Ĵ�����
            �üĴ����������ü���ʱ����һ��PDU����Ӧ�Ĳ����������ʼ��ַ��
            �ڼ��ܴ�������У��üĴ�����ֵ��Ӳ���Զ�����Ϊ��ǰ���ڼ��ܵ�PDU����Ӧ�Ĳ����������ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_param_addr_ul : 32; /* bit[0-31]: д�üĴ������ü���ʱ��һ�������������ʼ��ַ��ע�⣺�õ�ַҪ��8�ֽڣ�64bit�����롣
                                                            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ�Ĳ���������ʼ��ַ��
                                                            �����������ʼ��ַ��Ӳ����ǰһ�������ж�ȡ�������µ��üĴ����й������ѯ�����ڵ���ʱ��֪��ǰ���ڼ��ܵ�PDU����Ӧ�Ĳ���������ʼ��ַ�� */
    } reg;
} SOC_CICOM_LLI_PARAM_ADDR_UL_UNION;
#endif
#define SOC_CICOM_LLI_PARAM_ADDR_UL_lli_param_addr_ul_START  (0)
#define SOC_CICOM_LLI_PARAM_ADDR_UL_lli_param_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_GLOBAL_CFG_UL_UNION
 �ṹ˵��  : GLOBAL_CFG_UL �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]ȫ�ּ��ܲ������üĴ�����
            �üĴ�����������һ������ֻ������һ�Σ����谴��PDU�����ȸ��µļ��ܲ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alg_sel_ul    : 2;  /* bit[0-1]  : �������ü����㷨��
                                                         2'b00��Wģ�²�ѡ���㷨��Gģ�²�ѡ���㷨��
                                                         2'b01��Wģ��ѡ��UEA1�㷨��Gģ��ѡ��GEA1�㷨��
                                                         2'b10��Wģ��ѡ��UEA2�㷨��Gģ��ѡ��GEA2�㷨��
                                                         2'b11��Wģ�²�ѡ���㷨��Gģ��ѡ��GEA3�㷨�� */
        unsigned int  reserved_0    : 6;  /* bit[2-7]  : ���� */
        unsigned int  offset_len_ul : 4;  /* bit[8-11] : �������ü���ʱ������ƫ�Ƴ��ȡ����ֽ���λ��λ��
                                                         �������ԣ�����������Ϊ4'b0011���򵱴μ��ܵĸ���PDU����ƫ��3���ֽڽ��м��ܴ���������PDU�������ȶ����3���ֽڲ����м��ܴ���ֱ��д��DDR�С���δƫ�ƵĲ����������Ӧ����Կ���֮����д��DDR�С� */
        unsigned int  reserved_1    : 4;  /* bit[12-15]: ���� */
        unsigned int  bearer_ul     : 5;  /* bit[16-20]: ��������Wģ���ܲ���CB��BAERER�� */
        unsigned int  reserved_2    : 11; /* bit[21-31]: ���� */
    } reg;
} SOC_CICOM_GLOBAL_CFG_UL_UNION;
#endif
#define SOC_CICOM_GLOBAL_CFG_UL_alg_sel_ul_START     (0)
#define SOC_CICOM_GLOBAL_CFG_UL_alg_sel_ul_END       (1)
#define SOC_CICOM_GLOBAL_CFG_UL_offset_len_ul_START  (8)
#define SOC_CICOM_GLOBAL_CFG_UL_offset_len_ul_END    (11)
#define SOC_CICOM_GLOBAL_CFG_UL_bearer_ul_START      (16)
#define SOC_CICOM_GLOBAL_CFG_UL_bearer_ul_END        (20)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CHL_FST_ADDR_UL_UNION
 �ṹ˵��  : CHL_FST_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]���λ����ŵ��׵�ַ�Ĵ�����
            Wģ����ʱ��������ݵ�����������������ŵ�����CHL_FST_ADDR_UL��CHL_LST_ADDR_UL�Ĵ�����
            ����Ҫ��DST2��д�����Ŀ������ʱ��Ӳ������DST2Ŀ�����ݶ���ʼ��ַDST2_SEG_ADDR_UL�����ݶγ���DST2_SEG_LEN_UL�Լ����λ����ŵ��ס�ĩ��ַ�Զ��ж��Ƿ���Ҫ�ƻء�����Ҫ�ƻأ����ƻغ�Ӹ����õ�ַ��д��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chl_fst_addr_ul : 32; /* bit[0-31]: ��������Wģ����ʱ���λ����ŵ����׵�ַ��
                                                          ע�⣺CHL_FST_ADDR_UL�ͣ�CHL_LST_ADDR_UL+32'h1��Ҫ��8�ֽڣ�64bit�����롣 */
    } reg;
} SOC_CICOM_CHL_FST_ADDR_UL_UNION;
#endif
#define SOC_CICOM_CHL_FST_ADDR_UL_chl_fst_addr_ul_START  (0)
#define SOC_CICOM_CHL_FST_ADDR_UL_chl_fst_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CHL_LST_ADDR_UL_UNION
 �ṹ˵��  : CHL_LST_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]���λ����ŵ�ĩ��ַ�Ĵ�����
            Wģ����ʱ��������ݵ�����������������ŵ�����CHL_FST_ADDR_UL��CHL_LST_ADDR_UL�Ĵ�����
            ����Ҫ��DST2��д�����Ŀ������ʱ��Ӳ������DST2Ŀ�����ݶ���ʼ��ַDST2_SEG_ADDR_UL�����ݶγ���DST2_SEG_LEN_UL�Լ����λ����ŵ��ס�ĩ��ַ�Զ��ж��Ƿ���Ҫ�ƻء�����Ҫ�ƻأ���д�������õ�ַʱ��ʼ�ƻء�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chl_lst_addr_ul : 32; /* bit[0-31]: ��������Wģ����ʱ���λ����ŵ���ĩ��ַ��
                                                          ע�⣺CHL_FST_ADDR_UL�ͣ�CHL_LST_ADDR_UL+32'h1��Ҫ��8�ֽڣ�64bit�����롣 */
    } reg;
} SOC_CICOM_CHL_LST_ADDR_UL_UNION;
#endif
#define SOC_CICOM_CHL_LST_ADDR_UL_chl_lst_addr_ul_START  (0)
#define SOC_CICOM_CHL_LST_ADDR_UL_chl_lst_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_INT_EN_UL_UNION
 �ṹ˵��  : INT_EN_UL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]�ж�ʹ��/���μĴ�����
            д�üĴ������ø������ж�ʹ�ܻ����Ρ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_en_ul                : 1;  /* bit[0]   : ��������ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  src_addr_error_en_ul     : 1;  /* bit[1]   : ����Դ���ݵ�ַ���ó����ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  axi_error_en_ul          : 1;  /* bit[2]   : ����AXI�����ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  chl_addr_error_en_ul     : 1;  /* bit[3]   : �����ŵ���ַ���ó����ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  src_seg_len_error_en_ul  : 1;  /* bit[4]   : ����Դ���ݶγ������ó����ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  dst1_seg_len_error_en_ul : 1;  /* bit[5]   : ����DST1Ŀ�����ݶγ������ó����ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  dst2_seg_len_error_en_ul : 1;  /* bit[6]   : ����DST2Ŀ�����ݶγ������ó����ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  ck_addr_error_en_ul      : 1;  /* bit[7]   : ����CK��ַ���ó����ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  reserved                 : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_CICOM_INT_EN_UL_UNION;
#endif
#define SOC_CICOM_INT_EN_UL_end_en_ul_START                 (0)
#define SOC_CICOM_INT_EN_UL_end_en_ul_END                   (0)
#define SOC_CICOM_INT_EN_UL_src_addr_error_en_ul_START      (1)
#define SOC_CICOM_INT_EN_UL_src_addr_error_en_ul_END        (1)
#define SOC_CICOM_INT_EN_UL_axi_error_en_ul_START           (2)
#define SOC_CICOM_INT_EN_UL_axi_error_en_ul_END             (2)
#define SOC_CICOM_INT_EN_UL_chl_addr_error_en_ul_START      (3)
#define SOC_CICOM_INT_EN_UL_chl_addr_error_en_ul_END        (3)
#define SOC_CICOM_INT_EN_UL_src_seg_len_error_en_ul_START   (4)
#define SOC_CICOM_INT_EN_UL_src_seg_len_error_en_ul_END     (4)
#define SOC_CICOM_INT_EN_UL_dst1_seg_len_error_en_ul_START  (5)
#define SOC_CICOM_INT_EN_UL_dst1_seg_len_error_en_ul_END    (5)
#define SOC_CICOM_INT_EN_UL_dst2_seg_len_error_en_ul_START  (6)
#define SOC_CICOM_INT_EN_UL_dst2_seg_len_error_en_ul_END    (6)
#define SOC_CICOM_INT_EN_UL_ck_addr_error_en_ul_START       (7)
#define SOC_CICOM_INT_EN_UL_ck_addr_error_en_ul_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_INT_RAW_UL_UNION
 �ṹ˵��  : INT_RAW_UL �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]ԭʼ�ж�״̬�Ĵ�����
            ���üĴ������ظ��жϵ�ԭʼ�ж�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_raw_ul                : 1;  /* bit[0]   : ԭʼ��������ж�״̬��
                                                                    ���μ������е�����PDU�����������ʱ�����ж���Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  src_addr_error_raw_ul     : 1;  /* bit[1]   : ԭʼ����Դ���ݵ�ַ���ó����ж�״̬��
                                                                    ����ʱ���������������õ�PDU���ܳ��ȴ���0������һ��SRC�����ַΪ0ʱ�����ж���Ч������SRC���������õ�Դ���ݶγ��ȴ���0���������ݶε�ַΪ0ʱ�����ж���Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  axi_error_raw_ul          : 1;  /* bit[2]   : ԭʼ����AXI�����ж�״̬��
                                                                    ����ʱ��AXI�෴��ERROR��Ӧʱ�����ж���Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  chl_addr_error_raw_ul     : 1;  /* bit[3]   : ԭʼ�����ŵ���ַ���ó����ж�״̬��
                                                                    ����ʱ�����������õ�DST2Ŀ�����ݶε�ַ���ڼĴ���CHL_FST_ADDR_UL��CHL_LST_ADDR_UL������ֵ��Χ��ʱ�����ж���Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  src_seg_len_error_raw_ul  : 1;  /* bit[4]   : ԭʼ����Դ���ݶγ������ó����ж�״̬��
                                                                    SRC���������õĸ�Դ���ݶγ���֮�Ͳ�����PDU���ܳ���ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  dst1_seg_len_error_raw_ul : 1;  /* bit[5]   : ԭʼ����DST1Ŀ�����ݶγ������ó����ж�״̬��
                                                                    ����ʱ��DST1���������õĸ�DST1Ŀ�����ݶγ���֮�Ͳ�����PDU���ܳ���ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  dst2_seg_len_error_raw_ul : 1;  /* bit[6]   : ԭʼ����DST2Ŀ�����ݶγ������ó����ж�״̬��
                                                                    ����ʱ��DST2���������õĸ�DST2Ŀ�����ݶγ���֮�Ͳ�����PDU���ܳ���ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  ck_addr_error_raw_ul      : 1;  /* bit[7]   : ԭʼ������Կ��ַ���ó����ж�״̬��
                                                                    ����ʱ���������������CUSTOM_CFG��bit[1:0]����Ϊ2'b01����2'b11���Ҳ��������һ��CK_ADDR����Ϊ32'h0�����߷�8�ֽڶ��뼴CK_ADDR��bit[2:0]������3'b000ʱ�����ж���Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  reserved                  : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_CICOM_INT_RAW_UL_UNION;
#endif
#define SOC_CICOM_INT_RAW_UL_end_raw_ul_START                 (0)
#define SOC_CICOM_INT_RAW_UL_end_raw_ul_END                   (0)
#define SOC_CICOM_INT_RAW_UL_src_addr_error_raw_ul_START      (1)
#define SOC_CICOM_INT_RAW_UL_src_addr_error_raw_ul_END        (1)
#define SOC_CICOM_INT_RAW_UL_axi_error_raw_ul_START           (2)
#define SOC_CICOM_INT_RAW_UL_axi_error_raw_ul_END             (2)
#define SOC_CICOM_INT_RAW_UL_chl_addr_error_raw_ul_START      (3)
#define SOC_CICOM_INT_RAW_UL_chl_addr_error_raw_ul_END        (3)
#define SOC_CICOM_INT_RAW_UL_src_seg_len_error_raw_ul_START   (4)
#define SOC_CICOM_INT_RAW_UL_src_seg_len_error_raw_ul_END     (4)
#define SOC_CICOM_INT_RAW_UL_dst1_seg_len_error_raw_ul_START  (5)
#define SOC_CICOM_INT_RAW_UL_dst1_seg_len_error_raw_ul_END    (5)
#define SOC_CICOM_INT_RAW_UL_dst2_seg_len_error_raw_ul_START  (6)
#define SOC_CICOM_INT_RAW_UL_dst2_seg_len_error_raw_ul_END    (6)
#define SOC_CICOM_INT_RAW_UL_ck_addr_error_raw_ul_START       (7)
#define SOC_CICOM_INT_RAW_UL_ck_addr_error_raw_ul_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_INT_CLR_UL_UNION
 �ṹ˵��  : INT_CLR_UL �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]�ж�״̬����Ĵ�����
            ��üĴ�������Ӧbitд1'b1�����Ӧ�����жϣ�д1'b0��Ӱ�졣
            ���üĴ�������ֵΪ0x0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_clr_ul                : 1;  /* bit[0]   : ��������ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  src_addr_error_clr_ul     : 1;  /* bit[1]   : ����Դ���ݵ�ַ���ó����ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  axi_error_clr_ul          : 1;  /* bit[2]   : ����AXI�����ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  chl_addr_error_clr_ul     : 1;  /* bit[3]   : �����ŵ���ַ���ó����ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  src_seg_len_error_clr_ul  : 1;  /* bit[4]   : ����Դ���ݶγ������ó����ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  dst1_seg_len_error_clr_ul : 1;  /* bit[5]   : ����DST1Ŀ�����ݶγ������ó����ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  dst2_seg_len_error_clr_ul : 1;  /* bit[6]   : ����DST2Ŀ�����ݶγ������ó����ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  ck_addr_error_clr_ul      : 1;  /* bit[7]   : ������Կ��ַ���ó����ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  reserved                  : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_CICOM_INT_CLR_UL_UNION;
#endif
#define SOC_CICOM_INT_CLR_UL_end_clr_ul_START                 (0)
#define SOC_CICOM_INT_CLR_UL_end_clr_ul_END                   (0)
#define SOC_CICOM_INT_CLR_UL_src_addr_error_clr_ul_START      (1)
#define SOC_CICOM_INT_CLR_UL_src_addr_error_clr_ul_END        (1)
#define SOC_CICOM_INT_CLR_UL_axi_error_clr_ul_START           (2)
#define SOC_CICOM_INT_CLR_UL_axi_error_clr_ul_END             (2)
#define SOC_CICOM_INT_CLR_UL_chl_addr_error_clr_ul_START      (3)
#define SOC_CICOM_INT_CLR_UL_chl_addr_error_clr_ul_END        (3)
#define SOC_CICOM_INT_CLR_UL_src_seg_len_error_clr_ul_START   (4)
#define SOC_CICOM_INT_CLR_UL_src_seg_len_error_clr_ul_END     (4)
#define SOC_CICOM_INT_CLR_UL_dst1_seg_len_error_clr_ul_START  (5)
#define SOC_CICOM_INT_CLR_UL_dst1_seg_len_error_clr_ul_END    (5)
#define SOC_CICOM_INT_CLR_UL_dst2_seg_len_error_clr_ul_START  (6)
#define SOC_CICOM_INT_CLR_UL_dst2_seg_len_error_clr_ul_END    (6)
#define SOC_CICOM_INT_CLR_UL_ck_addr_error_clr_ul_START       (7)
#define SOC_CICOM_INT_CLR_UL_ck_addr_error_clr_ul_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_INT_MSK_UL_UNION
 �ṹ˵��  : INT_MSK_UL �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]���κ�ļ����ж�״̬�Ĵ�����
            ���üĴ������ظ������жϵ����κ��ж�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_msk_ul                : 1;  /* bit[0]   : ���κ�ļ�������ж�״̬��
                                                                    ���μ������е�����PDU����������ϣ��Ҹ��ж�δ������ʱ��Ч����
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  src_addr_error_msk_ul     : 1;  /* bit[1]   : ���κ�ļ���Դ���ݵ�ַ���ó����ж�״̬��
                                                                    ����ʱ���������������õ�PDU���ܳ��ȴ���0������һ��SRC�����ַΪ0������SRC���������õ�Դ���ݶγ��ȴ���0���������ݶε�ַΪ0���Ҹ��ж�δ������ʱ��Ч����
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  axi_error_msk_ul          : 1;  /* bit[2]   : ���κ�ļ���AXI�����ж�״̬��
                                                                    ����ʱ��AXI�෴��ERROR��Ӧ���Ҹ��ж�δ������ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  chl_addr_error_msk_ul     : 1;  /* bit[3]   : ���κ�ļ����ŵ���ַ���ó����ж�״̬��
                                                                    ����ʱ�����������õ�DST2Ŀ�����ݶε�ַ���ڼĴ���CHL_FST_ADDR_UL��CHL_LST_ADDR_UL������ֵ��Χ�ڣ��Ҹ��ж�δ������ʱ�����ж���Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  src_seg_len_error_msk_ul  : 1;  /* bit[4]   : ���κ�ļ���Դ���ݶγ������ó����ж�״̬��
                                                                    SRC���������õĸ�Դ���ݶγ���֮�Ͳ�����PDU���ܳ��ȣ��Ҹ��ж�δ������ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  dst1_seg_len_error_msk_ul : 1;  /* bit[5]   : ���κ�ļ���DST1Ŀ�����ݶγ������ó����ж�״̬��
                                                                    ����ʱ��DST1���������õĸ�DST1Ŀ�����ݶγ���֮�Ͳ�����PDU���ܳ��ȣ��Ҹ��ж�δ������ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  dst2_seg_len_error_msk_ul : 1;  /* bit[6]   : ���κ�ļ���DST2Ŀ�����ݶγ������ó����ж�״̬��
                                                                    ����ʱ��DST2���������õĸ�DST2Ŀ�����ݶγ���֮�Ͳ�����PDU���ܳ��ȣ��Ҹ��ж�δ������ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  ck_addr_error_msk_ul      : 1;  /* bit[7]   : ���κ�ļ�����Կ��ַ���ó����ж�״̬��
                                                                    ����ʱ���������������CUSTOM_CFG��bit[1:0]����Ϊ2'b01����2'b11���Ҳ��������һ��CK_ADDR����Ϊ32'h0�����߷�8�ֽڶ��뼴CK_ADDR��bit[2:0]������3'b000���Ҹ��ж�δ������ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  reserved                  : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_CICOM_INT_MSK_UL_UNION;
#endif
#define SOC_CICOM_INT_MSK_UL_end_msk_ul_START                 (0)
#define SOC_CICOM_INT_MSK_UL_end_msk_ul_END                   (0)
#define SOC_CICOM_INT_MSK_UL_src_addr_error_msk_ul_START      (1)
#define SOC_CICOM_INT_MSK_UL_src_addr_error_msk_ul_END        (1)
#define SOC_CICOM_INT_MSK_UL_axi_error_msk_ul_START           (2)
#define SOC_CICOM_INT_MSK_UL_axi_error_msk_ul_END             (2)
#define SOC_CICOM_INT_MSK_UL_chl_addr_error_msk_ul_START      (3)
#define SOC_CICOM_INT_MSK_UL_chl_addr_error_msk_ul_END        (3)
#define SOC_CICOM_INT_MSK_UL_src_seg_len_error_msk_ul_START   (4)
#define SOC_CICOM_INT_MSK_UL_src_seg_len_error_msk_ul_END     (4)
#define SOC_CICOM_INT_MSK_UL_dst1_seg_len_error_msk_ul_START  (5)
#define SOC_CICOM_INT_MSK_UL_dst1_seg_len_error_msk_ul_END    (5)
#define SOC_CICOM_INT_MSK_UL_dst2_seg_len_error_msk_ul_START  (6)
#define SOC_CICOM_INT_MSK_UL_dst2_seg_len_error_msk_ul_END    (6)
#define SOC_CICOM_INT_MSK_UL_ck_addr_error_msk_ul_START       (7)
#define SOC_CICOM_INT_MSK_UL_ck_addr_error_msk_ul_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_EN_UL_UNION
 �ṹ˵��  : EN_UL �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]ʹ�ܼĴ�����
            ���׼�����������úü��ܲ����Ĵ���֮����üĴ�����bit[0]д��1'b1�������ܲ�����
            ���ܲ�����ɺ���Ӳ���Զ��ԸüĴ������㡣
            ���ܹ��̳���ʱ��Ӳ��Ҳ��ԸüĴ����Զ����㣬ʹ�ڲ�״̬������IDLE״̬��
            ���üĴ������ؼ��ܴ���״̬��
                ����ֵΪ0x0����ʾCICOMû�н��м��ܴ���
                ����ֵΪ0x1����ʾCICOM���ڽ��м��ܴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en_ul    : 1;  /* bit[0]   : дʱ���ü���ʹ�ܣ�
                                                   0����ʹ�ܼ��ܴ���
                                                   1��ʹ�ܼ��ܴ���
                                                   ��ʱ���ؼ��ܴ���״̬��
                                                   0��δ�ڽ��м��ܴ���
                                                   1�����ڽ��м��ܴ��� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_CICOM_EN_UL_UNION;
#endif
#define SOC_CICOM_EN_UL_en_ul_START     (0)
#define SOC_CICOM_EN_UL_en_ul_END       (0)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CK_ADDR_UL_UNION
 �ṹ˵��  : CK_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]CK�������ⲿMemory�еĵ�ַ�Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ��CK����������ⲿMemory�е���ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_addr_ul : 32; /* bit[0-31]: ��ǰ���ڼ��ܵ�PDU����Ӧ��CK�������ⲿMemory�д�ŵ���ʼ��ַ�� */
    } reg;
} SOC_CICOM_CK_ADDR_UL_UNION;
#endif
#define SOC_CICOM_CK_ADDR_UL_ck_addr_ul_START  (0)
#define SOC_CICOM_CK_ADDR_UL_ck_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CK_31_0_UL_UNION
 �ṹ˵��  : CK_31_0_UL �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ��CK������bit[31:0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_31_0_ul : 32; /* bit[0-31]: Wģʱ����ǰ���ڼ��ܵ�PDU����Ӧ��CK������CONF_KEY��bit[31:0]��
                                                     Gģʱ����ǰ���ڼ��ܵ�PDU����Ӧ��CK������KC_LOW�� */
    } reg;
} SOC_CICOM_CK_31_0_UL_UNION;
#endif
#define SOC_CICOM_CK_31_0_UL_ck_31_0_ul_START  (0)
#define SOC_CICOM_CK_31_0_UL_ck_31_0_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CK_63_32_UL_UNION
 �ṹ˵��  : CK_63_32_UL �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ��CK������bit[63:32]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_63_32_ul : 32; /* bit[0-31]: Wģʱ����ǰ���ڼ��ܵ�PDU����Ӧ��CK������CONF_KEY��bit[63:32]��
                                                      Gģʱ����ǰ���ڼ��ܵ�PDU����Ӧ��CK������KC_HIGH�� */
    } reg;
} SOC_CICOM_CK_63_32_UL_UNION;
#endif
#define SOC_CICOM_CK_63_32_UL_ck_63_32_ul_START  (0)
#define SOC_CICOM_CK_63_32_UL_ck_63_32_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CK_95_64_UL_UNION
 �ṹ˵��  : CK_95_64_UL �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ��CK������bit[95:64]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_95_64_ul : 32; /* bit[0-31]: Wģʱ����ǰ���ڼ��ܵ�PDU����Ӧ��CK������CONF_KEY��bit[95:64]��
                                                      Gģʱ������ֵΪ0x0�� */
    } reg;
} SOC_CICOM_CK_95_64_UL_UNION;
#endif
#define SOC_CICOM_CK_95_64_UL_ck_95_64_ul_START  (0)
#define SOC_CICOM_CK_95_64_UL_ck_95_64_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CK_127_96_UL_UNION
 �ṹ˵��  : CK_127_96_UL �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ��CK������bit[127:96]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_127_96_ul : 32; /* bit[0-31]: Wģʱ����ǰ���ڼ��ܵ�PDU����Ӧ��CK������CONF_KEY��bit[127:96]��
                                                       Gģʱ������ֵΪ0x0�� */
    } reg;
} SOC_CICOM_CK_127_96_UL_UNION;
#endif
#define SOC_CICOM_CK_127_96_UL_ck_127_96_ul_START  (0)
#define SOC_CICOM_CK_127_96_UL_ck_127_96_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CC_UL_UNION
 �ṹ˵��  : CC_UL �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]CC�����Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU����Ӧ��CC������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cc_ul : 32; /* bit[0-31]: Wģʱ����ǰ���ڼ��ܵ�PDU����Ӧ��CC������COUNT��
                                                Gģʱ����ǰ���ڼ��ܵ�PDU����Ӧ��CC������Message_key */
    } reg;
} SOC_CICOM_CC_UL_UNION;
#endif
#define SOC_CICOM_CC_UL_cc_ul_START  (0)
#define SOC_CICOM_CC_UL_cc_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_PDU_TOTAL_LEN_UL_UNION
 �ṹ˵��  : PDU_TOTAL_LEN_UL �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]PDU�������ܳ��ȼĴ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU���������ܳ��ȣ��Ա�����Ϊ��λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pdu_total_len_ul : 16; /* bit[0-15] : ��ǰ���ڼ��ܵ�PDU���������ܳ��ȡ�
                                                            ��λΪ��������bit���� */
        unsigned int  reserved         : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CICOM_PDU_TOTAL_LEN_UL_UNION;
#endif
#define SOC_CICOM_PDU_TOTAL_LEN_UL_pdu_total_len_ul_START  (0)
#define SOC_CICOM_PDU_TOTAL_LEN_UL_pdu_total_len_ul_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CUSTOM_CFG_UL_UNION
 �ṹ˵��  : CUSTOM_CFG_UL �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]����ʽ�Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�PDU�������ݴ���ʽ��������PDU����Դ�����Ƿ�ֶΡ�Ŀ�������Ƿ�ֶΡ��Ƿ������Կ���Ƿ񽫲�������Կ��Դ���������ȡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  key_xor_src_ul : 2;  /* bit[0-1]  : ��ǰ���ڼ��ܵ�PDU�������ݴ���ʽ��
                                                          2'b00:�����κβ�����
                                                          2'b01: ��������Կ�����ݲ�������������Կ��������Կ���˵�ָ��Ŀ�ĵ�ַ��
                                                          2'b10: ������Դ���ݣ���������Կ������Դ���ݰ��˵�ָ��Ŀ�ĵ�ַ��
                                                          2'b11: ���ܲ��������ݲ�������������Կ�������ɵ���Կ���Ӧ��Դ������򣬵õ��ӽ��ܵ�Ŀ�����ݣ�����Ŀ�����ݰ��˵�ָ��Ŀ�ĵ�ַ�� */
        unsigned int  reserved_0     : 6;  /* bit[2-7]  : ������ */
        unsigned int  src_seg_en_ul  : 1;  /* bit[8]    : ��ǰ���ڼ��ܵ�PDU�����ݵ�Դ�����Ƿ�ֶΣ�
                                                          0:���ֶΣ�
                                                          1:�ֶΣ� */
        unsigned int  reserved_1     : 7;  /* bit[9-15] : ������ */
        unsigned int  dst1_seg_en_ul : 1;  /* bit[16]   : ��ǰ���ڼ��ܵ�PDU�����˵�DST1 Memory�е�Ŀ�������Ƿ�ֶΣ�
                                                          0:���ֶΣ�
                                                          1:�ֶΣ� */
        unsigned int  reserved_2     : 7;  /* bit[17-23]: ������ */
        unsigned int  dst2_seg_en_ul : 1;  /* bit[24]   : ��ǰ���ڼ��ܵ�PDU�����˵�DST2�е�Ŀ�������Ƿ�ֶΣ�
                                                          0:���ֶΣ�
                                                          1:�ֶΣ� */
        unsigned int  reserved_3     : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_CICOM_CUSTOM_CFG_UL_UNION;
#endif
#define SOC_CICOM_CUSTOM_CFG_UL_key_xor_src_ul_START  (0)
#define SOC_CICOM_CUSTOM_CFG_UL_key_xor_src_ul_END    (1)
#define SOC_CICOM_CUSTOM_CFG_UL_src_seg_en_ul_START   (8)
#define SOC_CICOM_CUSTOM_CFG_UL_src_seg_en_ul_END     (8)
#define SOC_CICOM_CUSTOM_CFG_UL_dst1_seg_en_ul_START  (16)
#define SOC_CICOM_CUSTOM_CFG_UL_dst1_seg_en_ul_END    (16)
#define SOC_CICOM_CUSTOM_CFG_UL_dst2_seg_en_ul_START  (24)
#define SOC_CICOM_CUSTOM_CFG_UL_dst2_seg_en_ul_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_SRC_SEG_ADDR_UL_UNION
 �ṹ˵��  : SRC_SEG_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]Դ���ݶ���ʼ��ַ�Ĵ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�Դ���ݶε���ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_addr_ul : 32; /* bit[0-31]: ��ǰ���ڼ��ܵ�Դ���ݶε���ʼ��ַ�� */
    } reg;
} SOC_CICOM_SRC_SEG_ADDR_UL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_ADDR_UL_src_seg_addr_ul_START  (0)
#define SOC_CICOM_SRC_SEG_ADDR_UL_src_seg_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_SRC_SEG_LEN_UL_UNION
 �ṹ˵��  : SRC_SEG_LEN_UL �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]Դ���ݶγ��ȼĴ�����
            ���üĴ������ص�ǰ���ڼ��ܵ�Դ���ݶεĳ��ȣ��Ա�����Ϊ��λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_len_ul : 16; /* bit[0-15] : ��ǰ���ڼ��ܵ�Դ���ݶεĳ��ȡ�
                                                          ��λΪ��������bit���� */
        unsigned int  reserved       : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CICOM_SRC_SEG_LEN_UL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_LEN_UL_src_seg_len_ul_START  (0)
#define SOC_CICOM_SRC_SEG_LEN_UL_src_seg_len_ul_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_LLI_SRC_SEG_ADDR_UL_UNION
 �ṹ˵��  : LLI_SRC_SEG_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]��һ��SRC������ʼ��ַ�Ĵ�����
            ���üĴ���������һ��SRC�������ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_src_seg_addr_ul : 32; /* bit[0-31]: ��һ��SRC�������ʼ��ַ�� */
    } reg;
} SOC_CICOM_LLI_SRC_SEG_ADDR_UL_UNION;
#endif
#define SOC_CICOM_LLI_SRC_SEG_ADDR_UL_lli_src_seg_addr_ul_START  (0)
#define SOC_CICOM_LLI_SRC_SEG_ADDR_UL_lli_src_seg_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_DST1_SEG_ADDR_UL_UNION
 �ṹ˵��  : DST1_SEG_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]Ŀ�����ݶδ����DST1 Memory����ʼ��ַ�Ĵ�����
            ���üĴ������ص�ǰ����д��DST1 Memory��Ŀ�����ݶε���ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_addr_ul : 32; /* bit[0-31]: ��ǰ���ڼ�д��DST1 Memory�е�Ŀ�����ݶε���ʼ��ַ�� */
    } reg;
} SOC_CICOM_DST1_SEG_ADDR_UL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_ADDR_UL_dst1_seg_addr_ul_START  (0)
#define SOC_CICOM_DST1_SEG_ADDR_UL_dst1_seg_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_DST1_SEG_LEN_UL_UNION
 �ṹ˵��  : DST1_SEG_LEN_UL �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]�����DST1 Memory��Ŀ�����ݶγ��ȼĴ�����
            ���üĴ������ص�ǰ����д��DST1 Memory�е�Ŀ�����ݶεĳ��ȡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_len_ul : 16; /* bit[0-15] : ��ǰ����д��DST1 Memory�е�Ŀ�����ݶεĳ��ȡ�
                                                           ��λΪ��������bit���� */
        unsigned int  reserved        : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CICOM_DST1_SEG_LEN_UL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_LEN_UL_dst1_seg_len_ul_START  (0)
#define SOC_CICOM_DST1_SEG_LEN_UL_dst1_seg_len_ul_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_LLI_DST1_SEG_ADDR_UL_UNION
 �ṹ˵��  : LLI_DST1_SEG_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]��һ��DST1������ʼ��ַ�Ĵ�����
            ���üĴ���������һ��DST1�������ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_dst1_seg_addr_ul : 32; /* bit[0-31]: ��һ��DST1�������ʼ��ַ�� */
    } reg;
} SOC_CICOM_LLI_DST1_SEG_ADDR_UL_UNION;
#endif
#define SOC_CICOM_LLI_DST1_SEG_ADDR_UL_lli_dst1_seg_addr_ul_START  (0)
#define SOC_CICOM_LLI_DST1_SEG_ADDR_UL_lli_dst1_seg_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_DST2_SEG_ADDR_UL_UNION
 �ṹ˵��  : DST2_SEG_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]Ŀ�����ݶδ����DST2�е���ʼ��ַ�Ĵ�����
            ���üĴ������ص�ǰ����д��DST2�е�Ŀ�����ݶε���ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst2_seg_addr_ul : 32; /* bit[0-31]: ��ǰ����д��DST2��Ŀ�����ݶε���ʼ��ַ�� */
    } reg;
} SOC_CICOM_DST2_SEG_ADDR_UL_UNION;
#endif
#define SOC_CICOM_DST2_SEG_ADDR_UL_dst2_seg_addr_ul_START  (0)
#define SOC_CICOM_DST2_SEG_ADDR_UL_dst2_seg_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_DST2_SEG_LEN_UL_UNION
 �ṹ˵��  : DST2_SEG_LEN_UL �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]�����DST2�е�Ŀ�����ݶγ��ȼĴ�����
            ���üĴ������ص�ǰ����д��DST2�е�Ŀ�����ݶεĳ��ȡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst2_seg_len_ul : 16; /* bit[0-15] : ��ǰ����д��DST2��Ŀ�����ݶεĳ��ȡ�
                                                           ��λΪ��������bit���� */
        unsigned int  reserved        : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CICOM_DST2_SEG_LEN_UL_UNION;
#endif
#define SOC_CICOM_DST2_SEG_LEN_UL_dst2_seg_len_ul_START  (0)
#define SOC_CICOM_DST2_SEG_LEN_UL_dst2_seg_len_ul_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_LLI_DST2_SEG_ADDR_UL_UNION
 �ṹ˵��  : LLI_DST2_SEG_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]��һ��DST2������ʼ��ַ�Ĵ�����
            ���üĴ���������һ��DST2�������ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_dst2_seg_addr_ul : 32; /* bit[0-31]: ��һ��DST2�������ʼ��ַ�� */
    } reg;
} SOC_CICOM_LLI_DST2_SEG_ADDR_UL_UNION;
#endif
#define SOC_CICOM_LLI_DST2_SEG_ADDR_UL_lli_dst2_seg_addr_ul_START  (0)
#define SOC_CICOM_LLI_DST2_SEG_ADDR_UL_lli_dst2_seg_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_ERROR_ADDR_UL_UNION
 �ṹ˵��  : ERROR_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]�����ַ�Ĵ�����
            ���üĴ������ؼ��ܹ�����AXI SLAVE�෴��ERROR��Ӧʱ�ķ��ʵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  error_addr_ul : 32; /* bit[0-31]: ���ܹ����з�������ʱ�ķ��ʵ�ַ�� */
    } reg;
} SOC_CICOM_ERROR_ADDR_UL_UNION;
#endif
#define SOC_CICOM_ERROR_ADDR_UL_error_addr_ul_START  (0)
#define SOC_CICOM_ERROR_ADDR_UL_error_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_SRC_SEG_RD_ADDR_UL_UNION
 �ṹ˵��  : SRC_SEG_RD_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]Դ���ݶε�ǰ����ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_rd_addr_ul : 32; /* bit[0-31]: ���ܹ�����Դ���ݶεĵ�ǰ����ַ�� */
    } reg;
} SOC_CICOM_SRC_SEG_RD_ADDR_UL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_RD_ADDR_UL_src_seg_rd_addr_ul_START  (0)
#define SOC_CICOM_SRC_SEG_RD_ADDR_UL_src_seg_rd_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_SRC_SEG_LEAVE_LEN_UL_UNION
 �ṹ˵��  : SRC_SEG_LEAVE_LEN_UL �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]��ǰԴ���ݶ���ʣ��δ��ȡ���ݳ��ȼĴ��������ֽڣ�Byte����Ϊ��λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_leave_len_ul : 14; /* bit[0-13] : ���ܹ����е�ǰԴ���ݶ���ʣ��δ��ȡ�����ֽڸ����� */
        unsigned int  reserved             : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_CICOM_SRC_SEG_LEAVE_LEN_UL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_LEAVE_LEN_UL_src_seg_leave_len_ul_START  (0)
#define SOC_CICOM_SRC_SEG_LEAVE_LEN_UL_src_seg_leave_len_ul_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_DST1_SEG_WR_ADDR_UL_UNION
 �ṹ˵��  : DST1_SEG_WR_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]DST1Ŀ�����ݶε�ǰд��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_wr_addr_ul : 32; /* bit[0-31]: ���ܹ�����DST1Ŀ�����ݶε�ǰд��ַ�� */
    } reg;
} SOC_CICOM_DST1_SEG_WR_ADDR_UL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_WR_ADDR_UL_dst1_seg_wr_addr_ul_START  (0)
#define SOC_CICOM_DST1_SEG_WR_ADDR_UL_dst1_seg_wr_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_DST1_SEG_LEAVE_LEN_UL_UNION
 �ṹ˵��  : DST1_SEG_LEAVE_LEN_UL �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]��ǰDST1Ŀ�����ݶ���ʣ��δд���ݳ��ȼĴ��������ֽڣ�Byte����Ϊ��λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_leave_len_ul : 14; /* bit[0-13] : ���ܹ����е�ǰDST1Ŀ�����ݶ���ʣ��δд�����ֽڸ����� */
        unsigned int  reserved              : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_CICOM_DST1_SEG_LEAVE_LEN_UL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_LEAVE_LEN_UL_dst1_seg_leave_len_ul_START  (0)
#define SOC_CICOM_DST1_SEG_LEAVE_LEN_UL_dst1_seg_leave_len_ul_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_DST2_SEG_WR_ADDR_UL_UNION
 �ṹ˵��  : DST2_SEG_WR_ADDR_UL �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]DST2Ŀ�����ݶε�ǰд��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst2_seg_wr_addr_ul : 32; /* bit[0-31]: ���ܹ�����DST2Ŀ�����ݶε�ǰд��ַ�� */
    } reg;
} SOC_CICOM_DST2_SEG_WR_ADDR_UL_UNION;
#endif
#define SOC_CICOM_DST2_SEG_WR_ADDR_UL_dst2_seg_wr_addr_ul_START  (0)
#define SOC_CICOM_DST2_SEG_WR_ADDR_UL_dst2_seg_wr_addr_ul_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_DST2_SEG_LEAVE_LEN_UL_UNION
 �ṹ˵��  : DST2_SEG_LEAVE_LEN_UL �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]��ǰDST2Ŀ�����ݶ���ʣ��δд���ݳ��ȼĴ��������ֽڣ�Byte����Ϊ��λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst2_seg_leave_len_ul : 14; /* bit[0-13] : ���ܹ����е�ǰDST2Ŀ�����ݶ���ʣ��δд�����ֽڸ����� */
        unsigned int  reserved              : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_CICOM_DST2_SEG_LEAVE_LEN_UL_UNION;
#endif
#define SOC_CICOM_DST2_SEG_LEAVE_LEN_UL_dst2_seg_leave_len_ul_START  (0)
#define SOC_CICOM_DST2_SEG_LEAVE_LEN_UL_dst2_seg_leave_len_ul_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_LLI_PARAM_ADDR_DL_UNION
 �ṹ˵��  : LLI_PARAM_ADDR_DL �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]����������ʼ��ַ�Ĵ�����
            �üĴ����������ý���ʱ����һ��PDU����Ӧ�Ĳ����������ʼ��ַ��
            �ڽ��ܴ�������У��üĴ�����ֵ��Ӳ���Զ�����Ϊ��ǰ���ڽ��ܵ�PDU����Ӧ�Ĳ����������ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_param_addr_dl : 32; /* bit[0-31]: д�üĴ������ý���ʱ��һ�������������ʼ��ַ��ע�⣺�õ�ַҪ��8�ֽڣ�64bit�����롣
                                                            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ�Ĳ���������ʼ��ַ��
                                                            �����������ʼ��ַ��Ӳ����ǰһ�������ж�ȡ�������µ��üĴ����й������ѯ�����ڵ���ʱ��֪��ǰ���ڽ��ܵ�PDU����Ӧ�Ĳ���������ʼ��ַ�� */
    } reg;
} SOC_CICOM_LLI_PARAM_ADDR_DL_UNION;
#endif
#define SOC_CICOM_LLI_PARAM_ADDR_DL_lli_param_addr_dl_START  (0)
#define SOC_CICOM_LLI_PARAM_ADDR_DL_lli_param_addr_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_GLOBAL_CFG_DL_UNION
 �ṹ˵��  : GLOBAL_CFG_DL �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]ȫ�ֽ��ܲ������üĴ�����
            �üĴ�����������һ������ֻ������һ�Σ����谴��PDU�����ȸ��µĽ��ܲ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alg_sel_dl    : 2;  /* bit[0-1]  : �������ý����㷨��
                                                         2'b00��Wģ�²�ѡ���㷨��Gģ�²�ѡ���㷨��
                                                         2'b01��Wģ��ѡ��UEA1�㷨��Gģ��ѡ��GEA1�㷨��
                                                         2'b10��Wģ��ѡ��UEA2�㷨��Gģ��ѡ��GEA2�㷨��
                                                         2'b11��Wģ�²�ѡ���㷨��Gģ��ѡ��GEA3�㷨�� */
        unsigned int  reserved_0    : 6;  /* bit[2-7]  : ���� */
        unsigned int  offset_len_dl : 4;  /* bit[8-11] : �������ý���ʱ������ƫ�Ƴ��ȡ����ֽ���λ��λ��
                                                         �������ԣ�����������Ϊ4'b0011���򵱴ν��ܵĸ���PDU����ƫ��3���ֽڽ��н��ܴ���������PDU�������ȶ����3���ֽڲ����н��ܴ���ֱ��д��DDR�С���δƫ�ƵĲ����������Ӧ����Կ���֮����д��DDR�С� */
        unsigned int  reserved_1    : 4;  /* bit[12-15]: ���� */
        unsigned int  bearer_dl     : 5;  /* bit[16-20]: ��������Wģ���ܲ���CB��BAERER�� */
        unsigned int  reserved_2    : 11; /* bit[21-31]: ���� */
    } reg;
} SOC_CICOM_GLOBAL_CFG_DL_UNION;
#endif
#define SOC_CICOM_GLOBAL_CFG_DL_alg_sel_dl_START     (0)
#define SOC_CICOM_GLOBAL_CFG_DL_alg_sel_dl_END       (1)
#define SOC_CICOM_GLOBAL_CFG_DL_offset_len_dl_START  (8)
#define SOC_CICOM_GLOBAL_CFG_DL_offset_len_dl_END    (11)
#define SOC_CICOM_GLOBAL_CFG_DL_bearer_dl_START      (16)
#define SOC_CICOM_GLOBAL_CFG_DL_bearer_dl_END        (20)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_INT_EN_DL_UNION
 �ṹ˵��  : INT_EN_DL �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]�ж�ʹ��/���μĴ�����
            д�üĴ������ø������ж�ʹ�ܻ����Ρ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_en_dl                : 1;  /* bit[0]   : ��������ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  src_addr_error_en_dl     : 1;  /* bit[1]   : ����Դ���ݵ�ַ���ó����ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  axi_error_en_dl          : 1;  /* bit[2]   : ����AXI�����ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  reserved_0               : 1;  /* bit[3]   : ������ */
        unsigned int  src_seg_len_error_en_dl  : 1;  /* bit[4]   : ����Դ���ݶγ������ó����ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  dst1_seg_len_error_en_dl : 1;  /* bit[5]   : ����DST1Ŀ�����ݶγ������ó����ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  reserved_1               : 1;  /* bit[6]   : ������ */
        unsigned int  ck_addr_error_en_dl      : 1;  /* bit[7]   : ����CK��ַ���ó����ж�ʹ��/���Ρ�
                                                                   0���ж����Σ�
                                                                   1���ж�ʹ�ܣ� */
        unsigned int  reserved_2               : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_CICOM_INT_EN_DL_UNION;
#endif
#define SOC_CICOM_INT_EN_DL_end_en_dl_START                 (0)
#define SOC_CICOM_INT_EN_DL_end_en_dl_END                   (0)
#define SOC_CICOM_INT_EN_DL_src_addr_error_en_dl_START      (1)
#define SOC_CICOM_INT_EN_DL_src_addr_error_en_dl_END        (1)
#define SOC_CICOM_INT_EN_DL_axi_error_en_dl_START           (2)
#define SOC_CICOM_INT_EN_DL_axi_error_en_dl_END             (2)
#define SOC_CICOM_INT_EN_DL_src_seg_len_error_en_dl_START   (4)
#define SOC_CICOM_INT_EN_DL_src_seg_len_error_en_dl_END     (4)
#define SOC_CICOM_INT_EN_DL_dst1_seg_len_error_en_dl_START  (5)
#define SOC_CICOM_INT_EN_DL_dst1_seg_len_error_en_dl_END    (5)
#define SOC_CICOM_INT_EN_DL_ck_addr_error_en_dl_START       (7)
#define SOC_CICOM_INT_EN_DL_ck_addr_error_en_dl_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_INT_RAW_DL_UNION
 �ṹ˵��  : INT_RAW_DL �Ĵ����ṹ���塣��ַƫ����:0x011C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]ԭʼ�ж�״̬�Ĵ�����
            ���üĴ������ظ��жϵ�ԭʼ�ж�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_raw_dl                : 1;  /* bit[0]   : ԭʼ��������ж�״̬��
                                                                    ���ν������е�����PDU�����������ʱ�����ж���Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  src_addr_error_raw_dl     : 1;  /* bit[1]   : ԭʼ����Դ���ݵ�ַ���ó����ж�״̬��
                                                                    ����ʱ���������������õ�PDU���ܳ��ȴ���0������һ��SRC�����ַΪ0ʱ�����ж���Ч������SRC���������õ�Դ���ݶγ��ȴ���0���������ݶε�ַΪ0ʱ�����ж���Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  axi_error_raw_dl          : 1;  /* bit[2]   : ԭʼ����AXI�����ж�״̬��
                                                                    ���ܹ����У�AXI�෴��ERROR��Ӧʱ�����ж���Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  reserved_0                : 1;  /* bit[3]   : ������ */
        unsigned int  src_seg_len_error_raw_dl  : 1;  /* bit[4]   : ԭʼ����Դ���ݶγ������ó����ж�״̬��
                                                                    ����ʱ��SRC���������õĸ�Դ���ݶγ���֮�Ͳ�����PDU���ܳ���ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  dst1_seg_len_error_raw_dl : 1;  /* bit[5]   : ԭʼ����DST1Ŀ�����ݶγ������ó����ж�״̬��
                                                                    ����ʱ��DST1���������õĸ�DST1Ŀ�����ݶγ���֮�Ͳ�����PDU���ܳ���ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  reserved_1                : 1;  /* bit[6]   : ������ */
        unsigned int  ck_addr_error_raw_dl      : 1;  /* bit[7]   : ԭʼ������Կ��ַ���ó����ж�״̬��
                                                                    ����ʱ���������������CUSTOM_CFG��bit[1:0]����Ϊ2'b01����2'b11���Ҳ��������һ��CK_ADDR����Ϊ32'h0�����߷�8�ֽڶ��뼴CK_ADDR��bit[2:0]������3'b000ʱ�����ж���Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  reserved_2                : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_CICOM_INT_RAW_DL_UNION;
#endif
#define SOC_CICOM_INT_RAW_DL_end_raw_dl_START                 (0)
#define SOC_CICOM_INT_RAW_DL_end_raw_dl_END                   (0)
#define SOC_CICOM_INT_RAW_DL_src_addr_error_raw_dl_START      (1)
#define SOC_CICOM_INT_RAW_DL_src_addr_error_raw_dl_END        (1)
#define SOC_CICOM_INT_RAW_DL_axi_error_raw_dl_START           (2)
#define SOC_CICOM_INT_RAW_DL_axi_error_raw_dl_END             (2)
#define SOC_CICOM_INT_RAW_DL_src_seg_len_error_raw_dl_START   (4)
#define SOC_CICOM_INT_RAW_DL_src_seg_len_error_raw_dl_END     (4)
#define SOC_CICOM_INT_RAW_DL_dst1_seg_len_error_raw_dl_START  (5)
#define SOC_CICOM_INT_RAW_DL_dst1_seg_len_error_raw_dl_END    (5)
#define SOC_CICOM_INT_RAW_DL_ck_addr_error_raw_dl_START       (7)
#define SOC_CICOM_INT_RAW_DL_ck_addr_error_raw_dl_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_INT_CLR_DL_UNION
 �ṹ˵��  : INT_CLR_DL �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]�ж�״̬����Ĵ�����
            ��üĴ�������Ӧbitд1'b1�����Ӧ�����жϣ�д1'b0��Ӱ�졣
            ���üĴ�������ֵΪ0x0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_clr_dl                : 1;  /* bit[0]   : ��������ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  src_addr_error_clr_dl     : 1;  /* bit[1]   : ����Դ���ݵ�ַ���ó����ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  axi_error_clr_dl          : 1;  /* bit[2]   : ����AXI�����ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  reserved_0                : 1;  /* bit[3]   : ������ */
        unsigned int  src_seg_len_error_clr_dl  : 1;  /* bit[4]   : ����Դ���ݶγ������ó����ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  dst1_seg_len_error_clr_dl : 1;  /* bit[5]   : ����DST1Ŀ�����ݶγ������ó����ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  reserved_1                : 1;  /* bit[6]   : ������ */
        unsigned int  ck_addr_error_clr_dl      : 1;  /* bit[7]   : ������Կ��ַ���ó����ж�״̬�����
                                                                    д1'b1����жϣ�д1'b0��Ӱ�졣 */
        unsigned int  reserved_2                : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_CICOM_INT_CLR_DL_UNION;
#endif
#define SOC_CICOM_INT_CLR_DL_end_clr_dl_START                 (0)
#define SOC_CICOM_INT_CLR_DL_end_clr_dl_END                   (0)
#define SOC_CICOM_INT_CLR_DL_src_addr_error_clr_dl_START      (1)
#define SOC_CICOM_INT_CLR_DL_src_addr_error_clr_dl_END        (1)
#define SOC_CICOM_INT_CLR_DL_axi_error_clr_dl_START           (2)
#define SOC_CICOM_INT_CLR_DL_axi_error_clr_dl_END             (2)
#define SOC_CICOM_INT_CLR_DL_src_seg_len_error_clr_dl_START   (4)
#define SOC_CICOM_INT_CLR_DL_src_seg_len_error_clr_dl_END     (4)
#define SOC_CICOM_INT_CLR_DL_dst1_seg_len_error_clr_dl_START  (5)
#define SOC_CICOM_INT_CLR_DL_dst1_seg_len_error_clr_dl_END    (5)
#define SOC_CICOM_INT_CLR_DL_ck_addr_error_clr_dl_START       (7)
#define SOC_CICOM_INT_CLR_DL_ck_addr_error_clr_dl_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_INT_MSK_DL_UNION
 �ṹ˵��  : INT_MSK_DL �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]���κ�Ľ����ж�״̬�Ĵ�����
            ���üĴ������ظ������жϵ����κ��ж�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_msk_dl                : 1;  /* bit[0]   : ���κ�Ľ�������ж�״̬��
                                                                    ���ν������е�����PDU����������ϣ��Ҹ��ж�δ������ʱ��Ч����
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  src_addr_error_msk_dl     : 1;  /* bit[1]   : ���κ�Ľ���Դ���ݵ�ַ���ó����ж�״̬��
                                                                    ����ʱ���������������õ�PDU���ܳ��ȴ���0������һ��SRC�����ַΪ0������SRC���������õ�Դ���ݶγ��ȴ���0���������ݶε�ַΪ0���Ҹ��ж�δ������ʱ��Ч����
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  axi_error_msk_dl          : 1;  /* bit[2]   : ���κ�Ľ���AXI�����ж�״̬��
                                                                    ����ʱ��AXI�෴��ERROR��Ӧ���Ҹ��ж�δ������ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  reserved_0                : 1;  /* bit[3]   : ������ */
        unsigned int  src_seg_len_error_msk_dl  : 1;  /* bit[4]   : ���κ�Ľ���Դ���ݶγ������ó����ж�״̬��
                                                                    ����ʱ��SRC���������õĸ�Դ���ݶγ���֮�Ͳ�����PDU���ܳ��ȣ��Ҹ��ж�δ������ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  dst1_seg_len_error_msk_dl : 1;  /* bit[5]   : ���κ�Ľ���DST1Ŀ�����ݶγ������ó����ж�״̬��
                                                                    ����ʱ��DST1���������õĸ�DST1Ŀ�����ݶγ���֮�Ͳ�����PDU���ܳ��ȣ��Ҹ��ж�δ������ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  reserved_1                : 1;  /* bit[6]   : ������ */
        unsigned int  ck_addr_error_msk_dl      : 1;  /* bit[7]   : ���κ�Ľ�����Կ��ַ���ó����ж�״̬��
                                                                    ����ʱ���������������CUSTOM_CFG��bit[1:0]����Ϊ2'b01����2'b11���Ҳ��������һ��CK_ADDR����Ϊ32'h0�����߷�8�ֽڶ��뼴CK_ADDR��bit[2:0]������3'b000���Ҹ��ж�δ������ʱ��Ч��
                                                                    0���ж���Ч��
                                                                    1���ж���Ч�� */
        unsigned int  reserved_2                : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_CICOM_INT_MSK_DL_UNION;
#endif
#define SOC_CICOM_INT_MSK_DL_end_msk_dl_START                 (0)
#define SOC_CICOM_INT_MSK_DL_end_msk_dl_END                   (0)
#define SOC_CICOM_INT_MSK_DL_src_addr_error_msk_dl_START      (1)
#define SOC_CICOM_INT_MSK_DL_src_addr_error_msk_dl_END        (1)
#define SOC_CICOM_INT_MSK_DL_axi_error_msk_dl_START           (2)
#define SOC_CICOM_INT_MSK_DL_axi_error_msk_dl_END             (2)
#define SOC_CICOM_INT_MSK_DL_src_seg_len_error_msk_dl_START   (4)
#define SOC_CICOM_INT_MSK_DL_src_seg_len_error_msk_dl_END     (4)
#define SOC_CICOM_INT_MSK_DL_dst1_seg_len_error_msk_dl_START  (5)
#define SOC_CICOM_INT_MSK_DL_dst1_seg_len_error_msk_dl_END    (5)
#define SOC_CICOM_INT_MSK_DL_ck_addr_error_msk_dl_START       (7)
#define SOC_CICOM_INT_MSK_DL_ck_addr_error_msk_dl_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_EN_DL_UNION
 �ṹ˵��  : EN_DL �Ĵ����ṹ���塣��ַƫ����:0x0128����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]ʹ�ܼĴ�����
            ���׼�����������úý��ܲ����Ĵ���֮����üĴ�����bit[0]д��1'b1�������ܲ�����
            ���ܲ�����ɺ���Ӳ���Զ��ԸüĴ������㡣
            ���ܹ��̳���ʱ��Ӳ��Ҳ��ԸüĴ����Զ����㣬ʹ�ڲ�״̬������IDLE״̬��
            ���üĴ������ؽ��ܴ���״̬��
                ����ֵΪ0x0����ʾCICOMû�н��н��ܴ���
                ����ֵΪ0x1����ʾCICOM���ڽ��н��ܴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en_dl    : 1;  /* bit[0]   : дʱ���ý���ʹ�ܣ�
                                                   0����ʹ�ܽ��ܴ���
                                                   1��ʹ�ܽ��ܴ���
                                                   ��ʱ���ؽ��ܴ���״̬��
                                                   0��δ�ڽ��н��ܴ���
                                                   1�����ڽ��н��ܴ��� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_CICOM_EN_DL_UNION;
#endif
#define SOC_CICOM_EN_DL_en_dl_START     (0)
#define SOC_CICOM_EN_DL_en_dl_END       (0)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CK_ADDR_DL_UNION
 �ṹ˵��  : CK_ADDR_DL �Ĵ����ṹ���塣��ַƫ����:0x012C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]CK�������ⲿMemory�еĵ�ַ�Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ��CK����������ⲿMemory�е���ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_addr_dl : 32; /* bit[0-31]: ��ǰ���ڽ��ܵ�PDU����Ӧ��CK�������ⲿMemory�д�ŵ���ʼ��ַ�� */
    } reg;
} SOC_CICOM_CK_ADDR_DL_UNION;
#endif
#define SOC_CICOM_CK_ADDR_DL_ck_addr_dl_START  (0)
#define SOC_CICOM_CK_ADDR_DL_ck_addr_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CK_31_0_DL_UNION
 �ṹ˵��  : CK_31_0_DL �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ��CK������bit[31:0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_31_0_dl : 32; /* bit[0-31]: Wģʱ����ǰ���ڽ��ܵ�PDU����Ӧ��CK������CONF_KEY��bit[31:0]��
                                                     Gģʱ����ǰ���ڽ��ܵ�PDU����Ӧ��CK������KC_LOW�� */
    } reg;
} SOC_CICOM_CK_31_0_DL_UNION;
#endif
#define SOC_CICOM_CK_31_0_DL_ck_31_0_dl_START  (0)
#define SOC_CICOM_CK_31_0_DL_ck_31_0_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CK_63_32_DL_UNION
 �ṹ˵��  : CK_63_32_DL �Ĵ����ṹ���塣��ַƫ����:0x0134����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ��CK������bit[63:32]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_63_32_dl : 32; /* bit[0-31]: Wģʱ����ǰ���ڽ��ܵ�PDU����Ӧ��CK������CONF_KEY��bit[63:32]��
                                                      Gģʱ����ǰ���ڽ��ܵ�PDU����Ӧ��CK������KC_HIGH�� */
    } reg;
} SOC_CICOM_CK_63_32_DL_UNION;
#endif
#define SOC_CICOM_CK_63_32_DL_ck_63_32_dl_START  (0)
#define SOC_CICOM_CK_63_32_DL_ck_63_32_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CK_95_64_DL_UNION
 �ṹ˵��  : CK_95_64_DL �Ĵ����ṹ���塣��ַƫ����:0x0138����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ��CK������bit[95:64]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_95_64_dl : 32; /* bit[0-31]: Wģʱ����ǰ���ڽ��ܵ�PDU����Ӧ��CK������CONF_KEY��bit[95:64]��
                                                      Gģʱ������ֵΪ0x0�� */
    } reg;
} SOC_CICOM_CK_95_64_DL_UNION;
#endif
#define SOC_CICOM_CK_95_64_DL_ck_95_64_dl_START  (0)
#define SOC_CICOM_CK_95_64_DL_ck_95_64_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CK_127_96_DL_UNION
 �ṹ˵��  : CK_127_96_DL �Ĵ����ṹ���塣��ַƫ����:0x013C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]CK�����Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ��CK������bit[127:96]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_127_96_dl : 32; /* bit[0-31]: Wģʱ����ǰ���ڽ��ܵ�PDU����Ӧ��CK������CONF_KEY��bit[127:96]��
                                                       Gģʱ������ֵΪ0x0�� */
    } reg;
} SOC_CICOM_CK_127_96_DL_UNION;
#endif
#define SOC_CICOM_CK_127_96_DL_ck_127_96_dl_START  (0)
#define SOC_CICOM_CK_127_96_DL_ck_127_96_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CC_DL_UNION
 �ṹ˵��  : CC_DL �Ĵ����ṹ���塣��ַƫ����:0x0140����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]CC�����Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU����Ӧ��CC������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cc_dl : 32; /* bit[0-31]: Wģʱ����ǰ���ڽ��ܵ�PDU����Ӧ��CC������COUNT��
                                                Gģʱ����ǰ���ڽ��ܵ�PDU����Ӧ��CC������Message_key */
    } reg;
} SOC_CICOM_CC_DL_UNION;
#endif
#define SOC_CICOM_CC_DL_cc_dl_START  (0)
#define SOC_CICOM_CC_DL_cc_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_PDU_TOTAL_LEN_DL_UNION
 �ṹ˵��  : PDU_TOTAL_LEN_DL �Ĵ����ṹ���塣��ַƫ����:0x0144����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]PDU�������ܳ��ȼĴ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU���������ܳ��ȣ��Ա�����Ϊ��λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pdu_total_len_dl : 16; /* bit[0-15] : ��ǰ���ڽ��ܵ�PDU���������ܳ��ȡ�
                                                            ��λΪ��������bit���� */
        unsigned int  reserved         : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CICOM_PDU_TOTAL_LEN_DL_UNION;
#endif
#define SOC_CICOM_PDU_TOTAL_LEN_DL_pdu_total_len_dl_START  (0)
#define SOC_CICOM_PDU_TOTAL_LEN_DL_pdu_total_len_dl_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_CUSTOM_CFG_DL_UNION
 �ṹ˵��  : CUSTOM_CFG_DL �Ĵ����ṹ���塣��ַƫ����:0x0148����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]����ʽ�Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�PDU�������ݴ���ʽ��������PDU����Դ�����Ƿ�ֶΡ�Ŀ�������Ƿ�ֶΡ��Ƿ������Կ���Ƿ񽫲�������Կ��Դ���������ȡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  key_xor_src_dl : 2;  /* bit[0-1]  : ��ǰ���ڽ��ܵ�PDU�������ݴ���ʽ��
                                                          2'b00:�����κβ�����
                                                          2'b01: ��������Կ�����ݲ�������������Կ��������Կ���˵�ָ��Ŀ�ĵ�ַ��
                                                          2'b10: ������Դ���ݣ���������Կ������Դ���ݰ��˵�ָ��Ŀ�ĵ�ַ��
                                                          2'b11: ���ܲ��������ݲ�������������Կ�������ɵ���Կ���Ӧ��Դ������򣬵õ��ӽ��ܵ�Ŀ�����ݣ�����Ŀ�����ݰ��˵�ָ��Ŀ�ĵ�ַ�� */
        unsigned int  reserved_0     : 6;  /* bit[2-7]  : ������ */
        unsigned int  src_seg_en_dl  : 1;  /* bit[8]    : ��ǰ���ڽ��ܵ�PDU�����ݵ�Դ�����Ƿ�ֶΣ�
                                                          0:���ֶΣ�
                                                          1:�ֶΣ� */
        unsigned int  reserved_1     : 7;  /* bit[9-15] : ������ */
        unsigned int  dst1_seg_en_dl : 1;  /* bit[16]   : ��ǰ���ڽ��ܵ�PDU�����˵�DST1 Memory�е�Ŀ�������Ƿ�ֶΣ�
                                                          0:���ֶΣ�
                                                          1:�ֶΣ� */
        unsigned int  reserved_2     : 7;  /* bit[17-23]: ������ */
        unsigned int  reserved_3     : 1;  /* bit[24]   : ������ */
        unsigned int  reserved_4     : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_CICOM_CUSTOM_CFG_DL_UNION;
#endif
#define SOC_CICOM_CUSTOM_CFG_DL_key_xor_src_dl_START  (0)
#define SOC_CICOM_CUSTOM_CFG_DL_key_xor_src_dl_END    (1)
#define SOC_CICOM_CUSTOM_CFG_DL_src_seg_en_dl_START   (8)
#define SOC_CICOM_CUSTOM_CFG_DL_src_seg_en_dl_END     (8)
#define SOC_CICOM_CUSTOM_CFG_DL_dst1_seg_en_dl_START  (16)
#define SOC_CICOM_CUSTOM_CFG_DL_dst1_seg_en_dl_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_SRC_SEG_ADDR_DL_UNION
 �ṹ˵��  : SRC_SEG_ADDR_DL �Ĵ����ṹ���塣��ַƫ����:0x014C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]Դ���ݶ���ʼ��ַ�Ĵ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�Դ���ݶε���ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_addr_dl : 32; /* bit[0-31]: ��ǰ���ڽ��ܵ�Դ���ݶε���ʼ��ַ�� */
    } reg;
} SOC_CICOM_SRC_SEG_ADDR_DL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_ADDR_DL_src_seg_addr_dl_START  (0)
#define SOC_CICOM_SRC_SEG_ADDR_DL_src_seg_addr_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_SRC_SEG_LEN_DL_UNION
 �ṹ˵��  : SRC_SEG_LEN_DL �Ĵ����ṹ���塣��ַƫ����:0x0150����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]Դ���ݶγ��ȼĴ�����
            ���üĴ������ص�ǰ���ڽ��ܵ�Դ���ݶεĳ��ȣ��Ա�����Ϊ��λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_len_dl : 16; /* bit[0-15] : ��ǰ���ڽ��ܵ�Դ���ݶεĳ��ȡ�
                                                          ��λΪ��������bit���� */
        unsigned int  reserved       : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CICOM_SRC_SEG_LEN_DL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_LEN_DL_src_seg_len_dl_START  (0)
#define SOC_CICOM_SRC_SEG_LEN_DL_src_seg_len_dl_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_LLI_SRC_SEG_ADDR_DL_UNION
 �ṹ˵��  : LLI_SRC_SEG_ADDR_DL �Ĵ����ṹ���塣��ַƫ����:0x0154����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]��һ��SRC������ʼ��ַ�Ĵ�����
            ���üĴ���������һ��SRC�������ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_src_seg_addr_dl : 32; /* bit[0-31]: ��һ��SRC�������ʼ��ַ�� */
    } reg;
} SOC_CICOM_LLI_SRC_SEG_ADDR_DL_UNION;
#endif
#define SOC_CICOM_LLI_SRC_SEG_ADDR_DL_lli_src_seg_addr_dl_START  (0)
#define SOC_CICOM_LLI_SRC_SEG_ADDR_DL_lli_src_seg_addr_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_DST1_SEG_ADDR_DL_UNION
 �ṹ˵��  : DST1_SEG_ADDR_DL �Ĵ����ṹ���塣��ַƫ����:0x0158����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]Ŀ�����ݶδ����DST1 Memory����ʼ��ַ�Ĵ�����
            ���üĴ������ص�ǰ����д��DST1 Memory��Ŀ�����ݶε���ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_addr_dl : 32; /* bit[0-31]: ��ǰ���ڼ�д��DST1 Memory�е�Ŀ�����ݶε���ʼ��ַ�� */
    } reg;
} SOC_CICOM_DST1_SEG_ADDR_DL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_ADDR_DL_dst1_seg_addr_dl_START  (0)
#define SOC_CICOM_DST1_SEG_ADDR_DL_dst1_seg_addr_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_DST1_SEG_LEN_DL_UNION
 �ṹ˵��  : DST1_SEG_LEN_DL �Ĵ����ṹ���塣��ַƫ����:0x015C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]�����DST1 Memory��Ŀ�����ݶγ��ȼĴ�����
            ���üĴ������ص�ǰ����д��DST1 Memory�е�Ŀ�����ݶεĳ��ȡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_len_dl : 16; /* bit[0-15] : ��ǰ����д��DST1 Memory�е�Ŀ�����ݶεĳ��ȡ�
                                                           ��λΪ��������bit���� */
        unsigned int  reserved        : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CICOM_DST1_SEG_LEN_DL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_LEN_DL_dst1_seg_len_dl_START  (0)
#define SOC_CICOM_DST1_SEG_LEN_DL_dst1_seg_len_dl_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_LLI_DST1_SEG_ADDR_DL_UNION
 �ṹ˵��  : LLI_DST1_SEG_ADDR_DL �Ĵ����ṹ���塣��ַƫ����:0x0160����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]��һ��DST1������ʼ��ַ�Ĵ�����
            ���üĴ���������һ��DST1�������ʼ��ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_dst1_seg_addr_dl : 32; /* bit[0-31]: ��һ��DST1�������ʼ��ַ�� */
    } reg;
} SOC_CICOM_LLI_DST1_SEG_ADDR_DL_UNION;
#endif
#define SOC_CICOM_LLI_DST1_SEG_ADDR_DL_lli_dst1_seg_addr_dl_START  (0)
#define SOC_CICOM_LLI_DST1_SEG_ADDR_DL_lli_dst1_seg_addr_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_ERROR_ADDR_DL_UNION
 �ṹ˵��  : ERROR_ADDR_DL �Ĵ����ṹ���塣��ַƫ����:0x0170����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]�����ַ�Ĵ�����
            ���üĴ������ؽ��ܹ�����AXI SLAVE�෴��ERROR��Ӧʱ�ķ��ʵ�ַ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  error_addr_dl : 32; /* bit[0-31]: ���ܹ����з�������ʱ�ķ��ʵ�ַ�� */
    } reg;
} SOC_CICOM_ERROR_ADDR_DL_UNION;
#endif
#define SOC_CICOM_ERROR_ADDR_DL_error_addr_dl_START  (0)
#define SOC_CICOM_ERROR_ADDR_DL_error_addr_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_SRC_SEG_RD_ADDR_DL_UNION
 �ṹ˵��  : SRC_SEG_RD_ADDR_DL �Ĵ����ṹ���塣��ַƫ����:0x0174����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]Դ���ݶε�ǰ����ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_rd_addr_dl : 32; /* bit[0-31]: ���ܹ�����Դ���ݶεĵ�ǰ����ַ�� */
    } reg;
} SOC_CICOM_SRC_SEG_RD_ADDR_DL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_RD_ADDR_DL_src_seg_rd_addr_dl_START  (0)
#define SOC_CICOM_SRC_SEG_RD_ADDR_DL_src_seg_rd_addr_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_SRC_SEG_LEAVE_LEN_DL_UNION
 �ṹ˵��  : SRC_SEG_LEAVE_LEN_DL �Ĵ����ṹ���塣��ַƫ����:0x0178����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]��ǰԴ���ݶ���ʣ��δ��ȡ���ݳ��ȼĴ��������ֽڣ�Byte����Ϊ��λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_leave_len_dl : 14; /* bit[0-13] : ���ܹ����е�ǰԴ���ݶ���ʣ��δ��ȡ�����ֽڸ����� */
        unsigned int  reserved             : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_CICOM_SRC_SEG_LEAVE_LEN_DL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_LEAVE_LEN_DL_src_seg_leave_len_dl_START  (0)
#define SOC_CICOM_SRC_SEG_LEAVE_LEN_DL_src_seg_leave_len_dl_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_DST1_SEG_WR_ADDR_DL_UNION
 �ṹ˵��  : DST1_SEG_WR_ADDR_DL �Ĵ����ṹ���塣��ַƫ����:0x017C����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]DST1Ŀ�����ݶε�ǰд��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_wr_addr_dl : 32; /* bit[0-31]: ���ܹ�����DST1Ŀ�����ݶε�ǰд��ַ�� */
    } reg;
} SOC_CICOM_DST1_SEG_WR_ADDR_DL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_WR_ADDR_DL_dst1_seg_wr_addr_dl_START  (0)
#define SOC_CICOM_DST1_SEG_WR_ADDR_DL_dst1_seg_wr_addr_dl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CICOM_DST1_SEG_LEAVE_LEN_DL_UNION
 �ṹ˵��  : DST1_SEG_LEAVE_LEN_DL �Ĵ����ṹ���塣��ַƫ����:0x0180����ֵ:0x00000000�����:32
 �Ĵ���˵��: [����]��ǰDST1Ŀ�����ݶ���ʣ��δд���ݳ��ȼĴ��������ֽڣ�Byte����Ϊ��λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_leave_len_dl : 14; /* bit[0-13] : ���ܹ����е�ǰDST1Ŀ�����ݶ���ʣ��δд�����ֽڸ����� */
        unsigned int  reserved              : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_CICOM_DST1_SEG_LEAVE_LEN_DL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_LEAVE_LEN_DL_dst1_seg_leave_len_dl_START  (0)
#define SOC_CICOM_DST1_SEG_LEAVE_LEN_DL_dst1_seg_leave_len_dl_END    (13)

/* ����Ϊת����Ĵ��������Զ����� */
#define SOC_CIPHER_REG_ADDR(base, offset) ((base)+(offset))
#define SOC_CIPHER_CICOM_STATE_RESET(BaseAddr)                     SOC_CICOM_STATE_RESET_ADDR(BaseAddr)
#define SOC_CIPHER_PRIOR_SELECT(BaseAddr)                          SOC_CICOM_PRIOR_SELECT_ADDR(BaseAddr)
#define SOC_CIPHER_LLI_PARAM_ADDR_UL(BaseAddr)                     SOC_CICOM_LLI_PARAM_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_GLOBAL_CFG_UL(BaseAddr)                         SOC_CICOM_GLOBAL_CFG_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CHL_FST_ADDR_UL(BaseAddr)                       SOC_CICOM_CHL_FST_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CHL_LST_ADDR_UL(BaseAddr)                       SOC_CICOM_CHL_LST_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_INT_EN_UL(BaseAddr)                             SOC_CICOM_INT_EN_UL_ADDR(BaseAddr)
#define SOC_CIPHER_INT_RAW_UL(BaseAddr)                            SOC_CICOM_INT_RAW_UL_ADDR(BaseAddr)
#define SOC_CIPHER_INT_CLR_UL(BaseAddr)                            SOC_CICOM_INT_CLR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_INT_MSK_UL(BaseAddr)                            SOC_CICOM_INT_MSK_UL_ADDR(BaseAddr)
#define SOC_CIPHER_EN_UL(BaseAddr)                                 SOC_CICOM_EN_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CK_ADDR_UL(BaseAddr)                            SOC_CICOM_CK_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CK_31_0_UL(BaseAddr)                            SOC_CICOM_CK_31_0_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CK_63_32_UL(BaseAddr)                           SOC_CICOM_CK_63_32_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CK_95_64_UL(BaseAddr)                           SOC_CICOM_CK_95_64_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CK_127_96_UL(BaseAddr)                          SOC_CICOM_CK_127_96_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CC_UL(BaseAddr)                                 SOC_CICOM_CC_UL_ADDR(BaseAddr)
#define SOC_CIPHER_SRC_PDU_TOTAL_LEN_UL(BaseAddr)                  SOC_CICOM_PDU_TOTAL_LEN_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CUSTOM_CFG_UL(BaseAddr)                         SOC_CICOM_CUSTOM_CFG_UL_ADDR(BaseAddr)
#define SOC_CIPHER_SRC_PDU_SEG_ADDR_UL(BaseAddr)                   SOC_CICOM_SRC_SEG_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_SRC_PDU_SEG_LEN_UL(BaseAddr)                    SOC_CICOM_SRC_SEG_LEN_UL_ADDR(BaseAddr)
#define SOC_CIPHER_LLI_SRC_PDU_SEG_ADDR_UL(BaseAddr)               SOC_CICOM_LLI_SRC_SEG_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_DST_TTF_SEG_ADDR_UL(BaseAddr)                   SOC_CICOM_DST1_SEG_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_DST_TTF_SEG_LEN_UL(BaseAddr)                    SOC_CICOM_DST1_SEG_LEN_UL_ADDR(BaseAddr)
#define SOC_CIPHER_LLI_DST_TTF_SEG_ADDR_UL(BaseAddr)               SOC_CICOM_LLI_DST1_SEG_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_DST_MBX_SEG_ADDR_UL(BaseAddr)                   SOC_CICOM_DST2_SEG_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_DST_MBX_SEG_LEN_UL(BaseAddr)                    SOC_CICOM_DST2_SEG_LEN_UL_ADDR(BaseAddr)
#define SOC_CIPHER_LLI_DST_MBX_SEG_ADDR_UL(BaseAddr)               SOC_CICOM_LLI_DST2_SEG_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_ERROR_ADDR_UL(BaseAddr)                         SOC_CICOM_ERROR_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_SRC_SEG_RD_ADDR_UL(BaseAddr)                    SOC_CIPHER_REG_ADDR(BaseAddr,0x0074)
#define SOC_CIPHER_SRC_SEG_LEAVE_LEN_UL(BaseAddr)                  SOC_CIPHER_REG_ADDR(BaseAddr,0x0078)
#define SOC_CIPHER_DST1_SEG_WR_ADDR_UL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x007c)
#define SOC_CIPHER_DST1_SEG_LEAVE_LEN_UL(BaseAddr)                 SOC_CIPHER_REG_ADDR(BaseAddr,0x0080)
#define SOC_CIPHER_DST2_SEG_WR_ADDR_UL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x0084)
#define SOC_CIPHER_DST2_SEG_LEAVE_LEN_UL(BaseAddr)                 SOC_CIPHER_REG_ADDR(BaseAddr,0x0088)


#define SOC_CIPHER_LLI_PARAM_ADDR_DL(BaseAddr)                     SOC_CIPHER_REG_ADDR(BaseAddr,0x0108)
#define SOC_CIPHER_GLOBAL_CFG_DL(BaseAddr)                         SOC_CIPHER_REG_ADDR(BaseAddr,0x010C)
#define SOC_CIPHER_CHL_FST_ADDR_DL(BaseAddr)                       SOC_CIPHER_REG_ADDR(BaseAddr,0x0110)
#define SOC_CIPHER_CHL_LST_ADDR_DL(BaseAddr)                       SOC_CIPHER_REG_ADDR(BaseAddr,0x0114)
#define SOC_CIPHER_INT_EN_DL(BaseAddr)                             SOC_CIPHER_REG_ADDR(BaseAddr,0x0118)
#define SOC_CIPHER_INT_RAW_DL(BaseAddr)                            SOC_CIPHER_REG_ADDR(BaseAddr,0x011C)
#define SOC_CIPHER_INT_CLR_DL(BaseAddr)                            SOC_CIPHER_REG_ADDR(BaseAddr,0x0120)
#define SOC_CIPHER_INT_MSK_DL(BaseAddr)                            SOC_CIPHER_REG_ADDR(BaseAddr,0x0124)
#define SOC_CIPHER_EN_DL(BaseAddr)                                 SOC_CIPHER_REG_ADDR(BaseAddr,0x0128)
#define SOC_CIPHER_CK_ADDR_DL(BaseAddr)                            SOC_CIPHER_REG_ADDR(BaseAddr,0x012C)
#define SOC_CIPHER_CK_31_0_DL(BaseAddr)                            SOC_CIPHER_REG_ADDR(BaseAddr,0x0130)
#define SOC_CIPHER_CK_63_32_DL(BaseAddr)                           SOC_CIPHER_REG_ADDR(BaseAddr,0x0134)
#define SOC_CIPHER_CK_95_64_DL(BaseAddr)                           SOC_CIPHER_REG_ADDR(BaseAddr,0x0138)
#define SOC_CIPHER_CK_127_96_DL(BaseAddr)                          SOC_CIPHER_REG_ADDR(BaseAddr,0x013c)
#define SOC_CIPHER_CC_DL(BaseAddr)                                 SOC_CIPHER_REG_ADDR(BaseAddr,0x0140)
#define SOC_CIPHER_SRC_PDU_TOTAL_LEN_DL(BaseAddr)                  SOC_CIPHER_REG_ADDR(BaseAddr,0x0144)
#define SOC_CIPHER_CUSTOM_CFG_DL(BaseAddr)                         SOC_CIPHER_REG_ADDR(BaseAddr,0x0148)
#define SOC_CIPHER_SRC_PDU_SEG_ADDR_DL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x014c)
#define SOC_CIPHER_SRC_PDU_SEG_LEN_DL(BaseAddr)                    SOC_CIPHER_REG_ADDR(BaseAddr,0x0150)
#define SOC_CIPHER_LLI_SRC_PDU_SEG_ADDR_DL(BaseAddr)               SOC_CIPHER_REG_ADDR(BaseAddr,0x0154)
#define SOC_CIPHER_DST_TTF_SEG_ADDR_DL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x0158)
#define SOC_CIPHER_DST_TTF_SEG_LEN_DL(BaseAddr)                    SOC_CIPHER_REG_ADDR(BaseAddr,0x015c)
#define SOC_CIPHER_LLI_DST_TTF_SEG_ADDR_DL(BaseAddr)               SOC_CIPHER_REG_ADDR(BaseAddr,0x0160)
#define SOC_CIPHER_DST_MBX_SEG_ADDR_DL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x0164)
#define SOC_CIPHER_DST_MBX_SEG_LEN_DL(BaseAddr)                    SOC_CIPHER_REG_ADDR(BaseAddr,0x0168)
#define SOC_CIPHER_LLI_DST_MBX_SEG_ADDR_DL(BaseAddr)               SOC_CIPHER_REG_ADDR(BaseAddr,0x016C)
#define SOC_CIPHER_ERROR_ADDR_DL(BaseAddr)                         SOC_CIPHER_REG_ADDR(BaseAddr,0x0170)
#define SOC_CIPHER_SRC_RD_ADDR_DL(BaseAddr)                        SOC_CIPHER_REG_ADDR(BaseAddr,0x0174)
#define SOC_CIPHER_SRC_SEG_LEFT_LEN_DL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x0178)
#define SOC_CIPHER_DST1_SEG_WR_ADDR_DL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x017C)
#define SOC_CIPHER_DST1_SEG_LEFT_LEN_DL(BaseAddr)                  SOC_CIPHER_REG_ADDR(BaseAddr,0x0180)



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

#endif /* end of soc_cicom_interface.h */
