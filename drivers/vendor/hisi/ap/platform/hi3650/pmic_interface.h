

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __PMIC_INTERFACE_H__
#define __PMIC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/5) PMU_CTRL
 ****************************************************************************/
/* �Ĵ���˵�����汾�Ĵ���0��
   λ����UNION�ṹ:  PMIC_VERSION0_UNION */
#define PMIC_VERSION0_ADDR(base)                  ((base) + (0x000))

/* �Ĵ���˵�����汾�Ĵ���1��
   λ����UNION�ṹ:  PMIC_VERSION1_UNION */
#define PMIC_VERSION1_ADDR(base)                  ((base) + (0x001))

/* �Ĵ���˵�����汾�Ĵ���2��
   λ����UNION�ṹ:  PMIC_VERSION2_UNION */
#define PMIC_VERSION2_ADDR(base)                  ((base) + (0x002))

/* �Ĵ���˵�����汾�Ĵ���3��
   λ����UNION�ṹ:  PMIC_VERSION3_UNION */
#define PMIC_VERSION3_ADDR(base)                  ((base) + (0x003))

/* �Ĵ���˵�����汾�Ĵ���4��
   λ����UNION�ṹ:  PMIC_VERSION4_UNION */
#define PMIC_VERSION4_ADDR(base)                  ((base) + (0x004))

/* �Ĵ���˵�����汾�Ĵ���5��
   λ����UNION�ṹ:  PMIC_VERSION5_UNION */
#define PMIC_VERSION5_ADDR(base)                  ((base) + (0x005))

/* �Ĵ���˵����״̬��־�Ĵ���0��
   λ����UNION�ṹ:  PMIC_STATUS0_UNION */
#define PMIC_STATUS0_ADDR(base)                   ((base) + (0x006))

/* �Ĵ���˵����״̬��־�Ĵ���1��
   λ����UNION�ṹ:  PMIC_STATUS1_UNION */
#define PMIC_STATUS1_ADDR(base)                   ((base) + (0x007))

/* �Ĵ���˵������ģ�ӿڱ����Ĵ���0��
   λ����UNION�ṹ:  PMIC_D2A_RES0_UNION */
#define PMIC_D2A_RES0_ADDR(base)                  ((base) + (0x008))

/* �Ĵ���˵������ģ�ӿڱ����Ĵ���1��
   λ����UNION�ṹ:  PMIC_D2A_RES1_UNION */
#define PMIC_D2A_RES1_ADDR(base)                  ((base) + (0x009))

/* �Ĵ���˵����xo_cali_thresold[15:8]ӳ��Ĵ���
   λ����UNION�ṹ:  PMIC_D2A_RES2_UNION */
#define PMIC_D2A_RES2_ADDR(base)                  ((base) + (0x00A))

/* �Ĵ���˵������ģ�ӿڱ����Ĵ���3��
   λ����UNION�ṹ:  PMIC_A2D_RES0_UNION */
#define PMIC_A2D_RES0_ADDR(base)                  ((base) + (0x00B))

/* �Ĵ���˵������ģ�ӿڱ����Ĵ���4��
   λ����UNION�ṹ:  PMIC_A2D_RES1_UNION */
#define PMIC_A2D_RES1_ADDR(base)                  ((base) + (0x00C))

/* �Ĵ���˵����BUCK0���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL0_UNION */
#define PMIC_BUCK0_CTRL0_ADDR(base)               ((base) + (0x00D))

/* �Ĵ���˵����BUCK0���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL1_UNION */
#define PMIC_BUCK0_CTRL1_ADDR(base)               ((base) + (0x00E))

/* �Ĵ���˵����BUCK0���ƼĴ���2��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL2_UNION */
#define PMIC_BUCK0_CTRL2_ADDR(base)               ((base) + (0x00F))

/* �Ĵ���˵����BUCK0���ƼĴ���3��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL3_UNION */
#define PMIC_BUCK0_CTRL3_ADDR(base)               ((base) + (0x010))

/* �Ĵ���˵����BUCK0���ƼĴ���4��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL4_UNION */
#define PMIC_BUCK0_CTRL4_ADDR(base)               ((base) + (0x011))

/* �Ĵ���˵����BUCK0���ƼĴ���5��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL5_UNION */
#define PMIC_BUCK0_CTRL5_ADDR(base)               ((base) + (0x012))

/* �Ĵ���˵����BUCK0���ƼĴ���6��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL6_UNION */
#define PMIC_BUCK0_CTRL6_ADDR(base)               ((base) + (0x013))

/* �Ĵ���˵����BUCK0���ƼĴ���7��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL7_UNION */
#define PMIC_BUCK0_CTRL7_ADDR(base)               ((base) + (0x014))

/* �Ĵ���˵����BUCK0���ƼĴ���8��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL8_UNION */
#define PMIC_BUCK0_CTRL8_ADDR(base)               ((base) + (0x015))

/* �Ĵ���˵����BUCK0���ƼĴ���9��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL9_UNION */
#define PMIC_BUCK0_CTRL9_ADDR(base)               ((base) + (0x016))

/* �Ĵ���˵����BUCK0���ƼĴ���10��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL10_UNION */
#define PMIC_BUCK0_CTRL10_ADDR(base)              ((base) + (0x017))

/* �Ĵ���˵����BUCK0���ƼĴ���11��
   λ����UNION�ṹ:  PMIC_BUCK0_CTRL11_UNION */
#define PMIC_BUCK0_CTRL11_ADDR(base)              ((base) + (0x018))

/* �Ĵ���˵����BUCK1���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL0_UNION */
#define PMIC_BUCK1_CTRL0_ADDR(base)               ((base) + (0x019))

/* �Ĵ���˵����BUCK1���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL1_UNION */
#define PMIC_BUCK1_CTRL1_ADDR(base)               ((base) + (0x01A))

/* �Ĵ���˵����BUCK1���ƼĴ���2��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL2_UNION */
#define PMIC_BUCK1_CTRL2_ADDR(base)               ((base) + (0x01B))

/* �Ĵ���˵����BUCK1���ƼĴ���3��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL3_UNION */
#define PMIC_BUCK1_CTRL3_ADDR(base)               ((base) + (0x01C))

/* �Ĵ���˵����BUCK1���ƼĴ���4��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL4_UNION */
#define PMIC_BUCK1_CTRL4_ADDR(base)               ((base) + (0x01D))

/* �Ĵ���˵����BUCK1���ƼĴ���5��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL5_UNION */
#define PMIC_BUCK1_CTRL5_ADDR(base)               ((base) + (0x01E))

/* �Ĵ���˵����BUCK1���ƼĴ���6��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL6_UNION */
#define PMIC_BUCK1_CTRL6_ADDR(base)               ((base) + (0x01F))

/* �Ĵ���˵����BUCK1���ƼĴ���7��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL7_UNION */
#define PMIC_BUCK1_CTRL7_ADDR(base)               ((base) + (0x020))

/* �Ĵ���˵����BUCK1���ƼĴ���8��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL8_UNION */
#define PMIC_BUCK1_CTRL8_ADDR(base)               ((base) + (0x021))

/* �Ĵ���˵����BUCK1���ƼĴ���9��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL9_UNION */
#define PMIC_BUCK1_CTRL9_ADDR(base)               ((base) + (0x022))

/* �Ĵ���˵����BUCK1���ƼĴ���10��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL10_UNION */
#define PMIC_BUCK1_CTRL10_ADDR(base)              ((base) + (0x023))

/* �Ĵ���˵����BUCK1���ƼĴ���11��
   λ����UNION�ṹ:  PMIC_BUCK1_CTRL11_UNION */
#define PMIC_BUCK1_CTRL11_ADDR(base)              ((base) + (0x024))

/* �Ĵ���˵����BUCK2���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL0_UNION */
#define PMIC_BUCK2_CTRL0_ADDR(base)               ((base) + (0x025))

/* �Ĵ���˵����BUCK2���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL1_UNION */
#define PMIC_BUCK2_CTRL1_ADDR(base)               ((base) + (0x026))

/* �Ĵ���˵����BUCK2���ƼĴ���2��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL2_UNION */
#define PMIC_BUCK2_CTRL2_ADDR(base)               ((base) + (0x027))

/* �Ĵ���˵����BUCK2���ƼĴ���3��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL3_UNION */
#define PMIC_BUCK2_CTRL3_ADDR(base)               ((base) + (0x028))

/* �Ĵ���˵����BUCK2���ƼĴ���4��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL4_UNION */
#define PMIC_BUCK2_CTRL4_ADDR(base)               ((base) + (0x029))

/* �Ĵ���˵����BUCK2���ƼĴ���5��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL5_UNION */
#define PMIC_BUCK2_CTRL5_ADDR(base)               ((base) + (0x02A))

/* �Ĵ���˵����BUCK2���ƼĴ���6��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL6_UNION */
#define PMIC_BUCK2_CTRL6_ADDR(base)               ((base) + (0x02B))

/* �Ĵ���˵����BUCK2���ƼĴ���7��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL7_UNION */
#define PMIC_BUCK2_CTRL7_ADDR(base)               ((base) + (0x02C))

/* �Ĵ���˵����BUCK2���ƼĴ���8��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL8_UNION */
#define PMIC_BUCK2_CTRL8_ADDR(base)               ((base) + (0x02D))

/* �Ĵ���˵����BUCK2���ƼĴ���9��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL9_UNION */
#define PMIC_BUCK2_CTRL9_ADDR(base)               ((base) + (0x02E))

/* �Ĵ���˵����BUCK2���ƼĴ���10��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL10_UNION */
#define PMIC_BUCK2_CTRL10_ADDR(base)              ((base) + (0x02F))

/* �Ĵ���˵����BUCK2���ƼĴ���11��
   λ����UNION�ṹ:  PMIC_BUCK2_CTRL11_UNION */
#define PMIC_BUCK2_CTRL11_ADDR(base)              ((base) + (0x030))

/* �Ĵ���˵����BUCK3���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL0_UNION */
#define PMIC_BUCK3_CTRL0_ADDR(base)               ((base) + (0x031))

/* �Ĵ���˵����BUCK3���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL1_UNION */
#define PMIC_BUCK3_CTRL1_ADDR(base)               ((base) + (0x032))

/* �Ĵ���˵����BUCK3���ƼĴ���2��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL2_UNION */
#define PMIC_BUCK3_CTRL2_ADDR(base)               ((base) + (0x033))

/* �Ĵ���˵����BUCK3���ƼĴ���3��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL3_UNION */
#define PMIC_BUCK3_CTRL3_ADDR(base)               ((base) + (0x034))

/* �Ĵ���˵����BUCK3���ƼĴ���4��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL4_UNION */
#define PMIC_BUCK3_CTRL4_ADDR(base)               ((base) + (0x035))

/* �Ĵ���˵����BUCK3���ƼĴ���5��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL5_UNION */
#define PMIC_BUCK3_CTRL5_ADDR(base)               ((base) + (0x036))

/* �Ĵ���˵����BUCK3���ƼĴ���6��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL6_UNION */
#define PMIC_BUCK3_CTRL6_ADDR(base)               ((base) + (0x037))

/* �Ĵ���˵����BUCK3���ƼĴ���7��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL7_UNION */
#define PMIC_BUCK3_CTRL7_ADDR(base)               ((base) + (0x038))

/* �Ĵ���˵����BUCK3���ƼĴ���8��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL8_UNION */
#define PMIC_BUCK3_CTRL8_ADDR(base)               ((base) + (0x039))

/* �Ĵ���˵����BUCK3���ƼĴ���9��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL9_UNION */
#define PMIC_BUCK3_CTRL9_ADDR(base)               ((base) + (0x03A))

/* �Ĵ���˵����BUCK3���ƼĴ���10��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL10_UNION */
#define PMIC_BUCK3_CTRL10_ADDR(base)              ((base) + (0x03B))

/* �Ĵ���˵����BUCK3���ƼĴ���11��
   λ����UNION�ṹ:  PMIC_BUCK3_CTRL11_UNION */
#define PMIC_BUCK3_CTRL11_ADDR(base)              ((base) + (0x03C))

/* �Ĵ���˵����BUCK4���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_BUCK4_CTRL0_UNION */
#define PMIC_BUCK4_CTRL0_ADDR(base)               ((base) + (0x03D))

/* �Ĵ���˵����BUCK4���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_BUCK4_CTRL1_UNION */
#define PMIC_BUCK4_CTRL1_ADDR(base)               ((base) + (0x03E))

/* �Ĵ���˵����BUCK4���ƼĴ���2��
   λ����UNION�ṹ:  PMIC_BUCK4_CTRL2_UNION */
#define PMIC_BUCK4_CTRL2_ADDR(base)               ((base) + (0x03F))

/* �Ĵ���˵����BUCK4���ƼĴ���3��
   λ����UNION�ṹ:  PMIC_BUCK4_CTRL3_UNION */
#define PMIC_BUCK4_CTRL3_ADDR(base)               ((base) + (0x040))

/* �Ĵ���˵����BUCK4���ƼĴ���4��
   λ����UNION�ṹ:  PMIC_BUCK4_CTRL4_UNION */
#define PMIC_BUCK4_CTRL4_ADDR(base)               ((base) + (0x041))

/* �Ĵ���˵����BUCK4���ƼĴ���5��
   λ����UNION�ṹ:  PMIC_BUCK4_CTRL5_UNION */
#define PMIC_BUCK4_CTRL5_ADDR(base)               ((base) + (0x042))

/* �Ĵ���˵����BUCK4���ƼĴ���6��
   λ����UNION�ṹ:  PMIC_BUCK4_CTRL6_UNION */
#define PMIC_BUCK4_CTRL6_ADDR(base)               ((base) + (0x043))

/* �Ĵ���˵����BUCK4���ƼĴ���7��
   λ����UNION�ṹ:  PMIC_BUCK4_CTRL7_UNION */
#define PMIC_BUCK4_CTRL7_ADDR(base)               ((base) + (0x044))

/* �Ĵ���˵����BUCK4���ƼĴ���8��
   λ����UNION�ṹ:  PMIC_BUCK4_CTRL8_UNION */
#define PMIC_BUCK4_CTRL8_ADDR(base)               ((base) + (0x045))

/* �Ĵ���˵����BUCK4���ƼĴ���9��
   λ����UNION�ṹ:  PMIC_BUCK4_CTRL9_UNION */
#define PMIC_BUCK4_CTRL9_ADDR(base)               ((base) + (0x046))

/* �Ĵ���˵����BUCK4���ƼĴ���10��
   λ����UNION�ṹ:  PMIC_BUCK4_CTRL10_UNION */
#define PMIC_BUCK4_CTRL10_ADDR(base)              ((base) + (0x047))

/* �Ĵ���˵����BUCK4���ƼĴ���11��
   λ����UNION�ṹ:  PMIC_BUCK4_CTRL11_UNION */
#define PMIC_BUCK4_CTRL11_ADDR(base)              ((base) + (0x048))

/* �Ĵ���˵����LDO0_2/LDO1���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO_1_CTRL_UNION */
#define PMIC_LDO_1_CTRL_ADDR(base)                ((base) + (0x049))

/* �Ĵ���˵����LDO2/LDO3���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LD2_3_CTRL_UNION */
#define PMIC_LD2_3_CTRL_ADDR(base)                ((base) + (0x04A))

/* �Ĵ���˵����LDO4/LDO5���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO4_5_CTRL_UNION */
#define PMIC_LDO4_5_CTRL_ADDR(base)               ((base) + (0x04B))

/* �Ĵ���˵����LDO7/LDO8���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO7_8_CTRL_UNION */
#define PMIC_LDO7_8_CTRL_ADDR(base)               ((base) + (0x04C))

/* �Ĵ���˵����LDO9/LDO10���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO9_10_CTRL_UNION */
#define PMIC_LDO9_10_CTRL_ADDR(base)              ((base) + (0x04D))

/* �Ĵ���˵����LDO11/LDO12���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LD11_12_CTRL_UNION */
#define PMIC_LD11_12_CTRL_ADDR(base)              ((base) + (0x04E))

/* �Ĵ���˵����LDO13/LDO14���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO13_14_CTRL_UNION */
#define PMIC_LDO13_14_CTRL_ADDR(base)             ((base) + (0x04F))

/* �Ĵ���˵����LDO15/LDO16���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO15_16_CTRL_UNION */
#define PMIC_LDO15_16_CTRL_ADDR(base)             ((base) + (0x050))

/* �Ĵ���˵����LDO17/LDO19���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO17_19_CTRL_UNION */
#define PMIC_LDO17_19_CTRL_ADDR(base)             ((base) + (0x051))

/* �Ĵ���˵����LDO20/LDO21���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO20_21_CTRL_UNION */
#define PMIC_LDO20_21_CTRL_ADDR(base)             ((base) + (0x052))

/* �Ĵ���˵����LDO22/LDO23���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO22_23_CTRL_UNION */
#define PMIC_LDO22_23_CTRL_ADDR(base)             ((base) + (0x053))

/* �Ĵ���˵����LDO24/LDO25���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO24_25_CTRL_UNION */
#define PMIC_LDO24_25_CTRL_ADDR(base)             ((base) + (0x054))

/* �Ĵ���˵����LDO26/LDO27���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO26_27_CTRL_UNION */
#define PMIC_LDO26_27_CTRL_ADDR(base)             ((base) + (0x055))

/* �Ĵ���˵����LDO28/LDO29���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO28_29_CTRL_UNION */
#define PMIC_LDO28_29_CTRL_ADDR(base)             ((base) + (0x056))

/* �Ĵ���˵����LDO30/LDO31���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO30_31_CTRL_UNION */
#define PMIC_LDO30_31_CTRL_ADDR(base)             ((base) + (0x057))

/* �Ĵ���˵����LDO32���ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO32_CTRL_UNION */
#define PMIC_LDO32_CTRL_ADDR(base)                ((base) + (0x058))

/* �Ĵ���˵����LDO0_1����ʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO0_1_ONOFF_UNION */
#define PMIC_LDO0_1_ONOFF_ADDR(base)              ((base) + (0x059))

/* �Ĵ���˵����LDO0_2���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO0_2_ONOFF_ECO_UNION */
#define PMIC_LDO0_2_ONOFF_ECO_ADDR(base)          ((base) + (0x05A))

/* �Ĵ���˵����LDO0_2��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO0_2_VSET_UNION */
#define PMIC_LDO0_2_VSET_ADDR(base)               ((base) + (0x05B))

/* �Ĵ���˵����LDO1���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO1_ONOFF_ECO_UNION */
#define PMIC_LDO1_ONOFF_ECO_ADDR(base)            ((base) + (0x05C))

/* �Ĵ���˵����LDO1��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO1_VSET_UNION */
#define PMIC_LDO1_VSET_ADDR(base)                 ((base) + (0x05D))

/* �Ĵ���˵����LDO2���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO2_ONOFF_ECO_UNION */
#define PMIC_LDO2_ONOFF_ECO_ADDR(base)            ((base) + (0x05E))

/* �Ĵ���˵����LDO2��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO2_VSET_UNION */
#define PMIC_LDO2_VSET_ADDR(base)                 ((base) + (0x05F))

/* �Ĵ���˵����LDO3���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO3_ONOFF_ECO_UNION */
#define PMIC_LDO3_ONOFF_ECO_ADDR(base)            ((base) + (0x060))

/* �Ĵ���˵����LDO3��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO3_VSET_UNION */
#define PMIC_LDO3_VSET_ADDR(base)                 ((base) + (0x061))

/* �Ĵ���˵����LDO4���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO4_ONOFF_ECO_UNION */
#define PMIC_LDO4_ONOFF_ECO_ADDR(base)            ((base) + (0x062))

/* �Ĵ���˵����LDO4��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO4_VSET_UNION */
#define PMIC_LDO4_VSET_ADDR(base)                 ((base) + (0x063))

/* �Ĵ���˵����LDO5���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO5_ONOFF_ECO_UNION */
#define PMIC_LDO5_ONOFF_ECO_ADDR(base)            ((base) + (0x064))

/* �Ĵ���˵����LDO5��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO5_VSET_UNION */
#define PMIC_LDO5_VSET_ADDR(base)                 ((base) + (0x065))

/* �Ĵ���˵����LDO7���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO7_ONOFF_ECO_UNION */
#define PMIC_LDO7_ONOFF_ECO_ADDR(base)            ((base) + (0x066))

/* �Ĵ���˵����LDO7��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO7_VSET_UNION */
#define PMIC_LDO7_VSET_ADDR(base)                 ((base) + (0x067))

/* �Ĵ���˵����LDO8���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO8_ONOFF_ECO_UNION */
#define PMIC_LDO8_ONOFF_ECO_ADDR(base)            ((base) + (0x068))

/* �Ĵ���˵����LDO8��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO8_VSET_UNION */
#define PMIC_LDO8_VSET_ADDR(base)                 ((base) + (0x069))

/* �Ĵ���˵����LDO9���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO9_ONOFF_ECO_UNION */
#define PMIC_LDO9_ONOFF_ECO_ADDR(base)            ((base) + (0x06A))

/* �Ĵ���˵����LDO9��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO9_VSET_UNION */
#define PMIC_LDO9_VSET_ADDR(base)                 ((base) + (0x06B))

/* �Ĵ���˵����LDO10���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO10_ONOFF_ECO_UNION */
#define PMIC_LDO10_ONOFF_ECO_ADDR(base)           ((base) + (0x06C))

/* �Ĵ���˵����LDO10��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO10_VSET_UNION */
#define PMIC_LDO10_VSET_ADDR(base)                ((base) + (0x06D))

/* �Ĵ���˵����LDO11���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO11_ONOFF_ECO_UNION */
#define PMIC_LDO11_ONOFF_ECO_ADDR(base)           ((base) + (0x06E))

/* �Ĵ���˵����LDO11��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO11_VSET_UNION */
#define PMIC_LDO11_VSET_ADDR(base)                ((base) + (0x06F))

/* �Ĵ���˵����LDO12���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO12_ONOFF_ECO_UNION */
#define PMIC_LDO12_ONOFF_ECO_ADDR(base)           ((base) + (0x070))

/* �Ĵ���˵����LDO12��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO12_VSET_UNION */
#define PMIC_LDO12_VSET_ADDR(base)                ((base) + (0x071))

/* �Ĵ���˵����LDO13���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO13_ONOFF_ECO_UNION */
#define PMIC_LDO13_ONOFF_ECO_ADDR(base)           ((base) + (0x072))

/* �Ĵ���˵����LDO13��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO13_VSET_UNION */
#define PMIC_LDO13_VSET_ADDR(base)                ((base) + (0x073))

/* �Ĵ���˵����LDO14���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO14_ONOFF_ECO_UNION */
#define PMIC_LDO14_ONOFF_ECO_ADDR(base)           ((base) + (0x074))

/* �Ĵ���˵����LDO14��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO14_VSET_UNION */
#define PMIC_LDO14_VSET_ADDR(base)                ((base) + (0x075))

/* �Ĵ���˵����LDO15���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO15_ONOFF_ECO_UNION */
#define PMIC_LDO15_ONOFF_ECO_ADDR(base)           ((base) + (0x076))

/* �Ĵ���˵����LDO15��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO15_VSET_UNION */
#define PMIC_LDO15_VSET_ADDR(base)                ((base) + (0x077))

/* �Ĵ���˵����LDO16���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO16_ONOFF_ECO_UNION */
#define PMIC_LDO16_ONOFF_ECO_ADDR(base)           ((base) + (0x078))

/* �Ĵ���˵����LDO16��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO16_VSET_UNION */
#define PMIC_LDO16_VSET_ADDR(base)                ((base) + (0x079))

/* �Ĵ���˵����LDO17���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO17_ONOFF_ECO_UNION */
#define PMIC_LDO17_ONOFF_ECO_ADDR(base)           ((base) + (0x07A))

/* �Ĵ���˵����LDO17��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO17_VSET_UNION */
#define PMIC_LDO17_VSET_ADDR(base)                ((base) + (0x07B))

/* �Ĵ���˵����LDO19���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO19_ONOFF_ECO_UNION */
#define PMIC_LDO19_ONOFF_ECO_ADDR(base)           ((base) + (0x07C))

/* �Ĵ���˵����LDO19��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO19_VSET1_UNION */
#define PMIC_LDO19_VSET1_ADDR(base)               ((base) + (0x07D))

/* �Ĵ���˵����LDO20���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO20_ONOFF_ECO_UNION */
#define PMIC_LDO20_ONOFF_ECO_ADDR(base)           ((base) + (0x07E))

/* �Ĵ���˵����LDO20��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO20_VSET_UNION */
#define PMIC_LDO20_VSET_ADDR(base)                ((base) + (0x07F))

/* �Ĵ���˵����LDO21���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO21_ONOFF_ECO_UNION */
#define PMIC_LDO21_ONOFF_ECO_ADDR(base)           ((base) + (0x080))

/* �Ĵ���˵����LDO21��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO21_VSET_UNION */
#define PMIC_LDO21_VSET_ADDR(base)                ((base) + (0x081))

/* �Ĵ���˵����LDO22���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO22_ONOFF_ECO_UNION */
#define PMIC_LDO22_ONOFF_ECO_ADDR(base)           ((base) + (0x082))

/* �Ĵ���˵����LDO22��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO22_VSET_UNION */
#define PMIC_LDO22_VSET_ADDR(base)                ((base) + (0x083))

/* �Ĵ���˵����LDO23���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO23_ONOFF_ECO_UNION */
#define PMIC_LDO23_ONOFF_ECO_ADDR(base)           ((base) + (0x084))

/* �Ĵ���˵����LDO23��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO23_VSET_UNION */
#define PMIC_LDO23_VSET_ADDR(base)                ((base) + (0x085))

/* �Ĵ���˵����LDO24���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO24_ONOFF_ECO_UNION */
#define PMIC_LDO24_ONOFF_ECO_ADDR(base)           ((base) + (0x086))

/* �Ĵ���˵����LDO24��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO24_VSET_UNION */
#define PMIC_LDO24_VSET_ADDR(base)                ((base) + (0x087))

/* �Ĵ���˵����LDO25���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO25_ONOFF_ECO_UNION */
#define PMIC_LDO25_ONOFF_ECO_ADDR(base)           ((base) + (0x088))

/* �Ĵ���˵����LDO25��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO25_VSET_UNION */
#define PMIC_LDO25_VSET_ADDR(base)                ((base) + (0x089))

/* �Ĵ���˵����LDO26���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO26_ONOFF_ECO_UNION */
#define PMIC_LDO26_ONOFF_ECO_ADDR(base)           ((base) + (0x08A))

/* �Ĵ���˵����LDO26��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO26_VSET_UNION */
#define PMIC_LDO26_VSET_ADDR(base)                ((base) + (0x08B))

/* �Ĵ���˵����LDO27���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO27_ONOFF_ECO_UNION */
#define PMIC_LDO27_ONOFF_ECO_ADDR(base)           ((base) + (0x08C))

/* �Ĵ���˵����LDO27��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO27_VSET_UNION */
#define PMIC_LDO27_VSET_ADDR(base)                ((base) + (0x08D))

/* �Ĵ���˵����LDO28���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO28_ONOFF_ECO_UNION */
#define PMIC_LDO28_ONOFF_ECO_ADDR(base)           ((base) + (0x08E))

/* �Ĵ���˵����LDO28��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO28_VSET_UNION */
#define PMIC_LDO28_VSET_ADDR(base)                ((base) + (0x08F))

/* �Ĵ���˵����LDO29���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO29_ONOFF_ECO_UNION */
#define PMIC_LDO29_ONOFF_ECO_ADDR(base)           ((base) + (0x090))

/* �Ĵ���˵����LDO29��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO29_VSET_UNION */
#define PMIC_LDO29_VSET_ADDR(base)                ((base) + (0x091))

/* �Ĵ���˵����LDO���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO30_ONOFF_ECO_UNION */
#define PMIC_LDO30_ONOFF_ECO_ADDR(base)           ((base) + (0x092))

/* �Ĵ���˵����LDO30��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO30_VSET_UNION */
#define PMIC_LDO30_VSET_ADDR(base)                ((base) + (0x093))

/* �Ĵ���˵����LDO31���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO31_ONOFF_ECO_UNION */
#define PMIC_LDO31_ONOFF_ECO_ADDR(base)           ((base) + (0x094))

/* �Ĵ���˵����LDO31��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO31_VSET_UNION */
#define PMIC_LDO31_VSET_ADDR(base)                ((base) + (0x095))

/* �Ĵ���˵����LDO32���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO32_ONOFF_ECO_UNION */
#define PMIC_LDO32_ONOFF_ECO_ADDR(base)           ((base) + (0x096))

/* �Ĵ���˵����LDO32��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO32_VSET_UNION */
#define PMIC_LDO32_VSET_ADDR(base)                ((base) + (0x097))

/* �Ĵ���˵����BUCK0���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK0_ONOFF_ECO_UNION */
#define PMIC_BUCK0_ONOFF_ECO_ADDR(base)           ((base) + (0x098))

/* �Ĵ���˵����BUCK0��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_BUCK0_VSET_UNION */
#define PMIC_BUCK0_VSET_ADDR(base)                ((base) + (0x099))

/* �Ĵ���˵����BUCK1���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK1_ONOFF_ECO_UNION */
#define PMIC_BUCK1_ONOFF_ECO_ADDR(base)           ((base) + (0x09A))

/* �Ĵ���˵����BUCK1��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_BUCK1_VSET_UNION */
#define PMIC_BUCK1_VSET_ADDR(base)                ((base) + (0x09B))

/* �Ĵ���˵����BUCK2���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK2_ONOFF_ECO_UNION */
#define PMIC_BUCK2_ONOFF_ECO_ADDR(base)           ((base) + (0x09C))

/* �Ĵ���˵����BUCK2��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_BUCK2_VSET_UNION */
#define PMIC_BUCK2_VSET_ADDR(base)                ((base) + (0x09D))

/* �Ĵ���˵����BUCK3���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK3_ONOFF_ECO_UNION */
#define PMIC_BUCK3_ONOFF_ECO_ADDR(base)           ((base) + (0x09E))

/* �Ĵ���˵����BUCK3��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_BUCK3_VSET_UNION */
#define PMIC_BUCK3_VSET_ADDR(base)                ((base) + (0x09F))

/* �Ĵ���˵����BUCK4���غ�ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK4_ONOFF_ECO_UNION */
#define PMIC_BUCK4_ONOFF_ECO_ADDR(base)           ((base) + (0x0A0))

/* �Ĵ���˵����BUCK4��ѹ���ƼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK4_VSET_UNION */
#define PMIC_BUCK4_VSET_ADDR(base)                ((base) + (0x0A1))

/* �Ĵ���˵����LDO_PMUA ECOʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_LDO_PMUA_ECO_UNION */
#define PMIC_LDO_PMUA_ECO_ADDR(base)              ((base) + (0x0A2))

/* �Ĵ���˵����LDO_PMUA��ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_LDO_PMUA_VSET_UNION */
#define PMIC_LDO_PMUA_VSET_ADDR(base)             ((base) + (0x0A3))

/* �Ĵ���˵����BSTʹ�ܿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_BST_MODE_EN_UNION */
#define PMIC_BST_MODE_EN_ADDR(base)               ((base) + (0x0A4))

/* �Ĵ���˵����NOPWRT���ƼĴ�����
   λ����UNION�ṹ:  PMIC_NOPWR_CTRL_UNION */
#define PMIC_NOPWR_CTRL_ADDR(base)                ((base) + (0x0A5))

/* �Ĵ���˵����classd���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_CLASSD_CTRL0_UNION */
#define PMIC_CLASSD_CTRL0_ADDR(base)              ((base) + (0x0A6))

/* �Ĵ���˵����classd���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_CLASSD_CTRL1_UNION */
#define PMIC_CLASSD_CTRL1_ADDR(base)              ((base) + (0x0A7))

/* �Ĵ���˵����classd���ƼĴ���2��
   λ����UNION�ṹ:  PMIC_CLASSD_CTRL2_UNION */
#define PMIC_CLASSD_CTRL2_ADDR(base)              ((base) + (0x0A8))

/* �Ĵ���˵����classd���ƼĴ���3��
   λ����UNION�ṹ:  PMIC_CLASSD_CTRL3_UNION */
#define PMIC_CLASSD_CTRL3_ADDR(base)              ((base) + (0x0A9))

/* �Ĵ���˵������ѹ�¶ȿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_TH_CTRL_UNION */
#define PMIC_TH_CTRL_ADDR(base)                   ((base) + (0x0AA))

/* �Ĵ���˵����bg���ԼĴ�����
   λ����UNION�ṹ:  PMIC_BG_TEST_UNION */
#define PMIC_BG_TEST_ADDR(base)                   ((base) + (0x0AB))

/* �Ĵ���˵����DR345��˸ģʽʹ�ܺ�ģʽ�Ĵ�����
   λ����UNION�ṹ:  PMIC_DR_EN_MODE_345_UNION */
#define PMIC_DR_EN_MODE_345_ADDR(base)            ((base) + (0x0AC))

/* �Ĵ���˵����DR12��˸ģʽʹ�ܺ�ģʽ�Ĵ�����
   λ����UNION�ṹ:  PMIC_DR_EN_MODE_12_UNION */
#define PMIC_DR_EN_MODE_12_ADDR(base)             ((base) + (0x0AD))

/* �Ĵ���˵����DR12��˸ģʽ���ڵ���0�Ĵ�����
   λ����UNION�ṹ:  PMIC_FLASH_PERIOD_DR12_UNION */
#define PMIC_FLASH_PERIOD_DR12_ADDR(base)         ((base) + (0x0AE))

/* �Ĵ���˵����DR12��˸ģʽ����ʱ�����0�Ĵ�����
   λ����UNION�ṹ:  PMIC_FLASH_ON_DR12_UNION */
#define PMIC_FLASH_ON_DR12_ADDR(base)             ((base) + (0x0AF))

/* �Ĵ���˵����DR345��˸ģʽ���ڵ���1�Ĵ�����
   λ����UNION�ṹ:  PMIC_FLASH_PERIOD_DR345_UNION */
#define PMIC_FLASH_PERIOD_DR345_ADDR(base)        ((base) + (0x0B0))

/* �Ĵ���˵����DR345��˸ģʽ����ʱ�����1�Ĵ�����
   λ����UNION�ṹ:  PMIC_FLASH_ON_DR345_UNION */
#define PMIC_FLASH_ON_DR345_ADDR(base)            ((base) + (0x0B1))

/* �Ĵ���˵����DR��ģʽѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DR_MODE_SEL_UNION */
#define PMIC_DR_MODE_SEL_ADDR(base)               ((base) + (0x0B2))

/* �Ĵ���˵����DR1/2����ģʽ���ƼĴ�����
   λ����UNION�ṹ:  PMIC_DR_BRE_CTRL_UNION */
#define PMIC_DR_BRE_CTRL_ADDR(base)               ((base) + (0x0B3))

/* �Ĵ���˵����DR1��DR2��������ʱ�����üĴ�����
   λ����UNION�ṹ:  PMIC_DR12_TIM_CONF0_UNION */
#define PMIC_DR12_TIM_CONF0_ADDR(base)            ((base) + (0x0B4))

/* �Ĵ���˵����DR1��DR2��������ʱ�����üĴ�����
   λ����UNION�ṹ:  PMIC_DR12_TIM_CONF1_UNION */
#define PMIC_DR12_TIM_CONF1_ADDR(base)            ((base) + (0x0B5))

/* �Ĵ���˵����DR1����ѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DR1_ISET_UNION */
#define PMIC_DR1_ISET_ADDR(base)                  ((base) + (0x0B6))

/* �Ĵ���˵����DR2����ѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DR2_ISET_UNION */
#define PMIC_DR2_ISET_ADDR(base)                  ((base) + (0x0B7))

/* �Ĵ���˵����DR3/4/5���ƼĴ�����
   λ����UNION�ṹ:  PMIC_DR_LED_CTRL_UNION */
#define PMIC_DR_LED_CTRL_ADDR(base)               ((base) + (0x0B8))

/* �Ĵ���˵����DR3/4/5������ƼĴ�����
   λ����UNION�ṹ:  PMIC_DR_OUT_CTRL_UNION */
#define PMIC_DR_OUT_CTRL_ADDR(base)               ((base) + (0x0B9))

/* �Ĵ���˵����DR3����ѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DR3_ISET_UNION */
#define PMIC_DR3_ISET_ADDR(base)                  ((base) + (0x0BA))

/* �Ĵ���˵����DR3������ʱ���üĴ�����
   λ����UNION�ṹ:  PMIC_DR3_START_DEL_UNION */
#define PMIC_DR3_START_DEL_ADDR(base)             ((base) + (0x0BB))

/* �Ĵ���˵����DR4����ѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DR4_ISET_UNION */
#define PMIC_DR4_ISET_ADDR(base)                  ((base) + (0x0BC))

/* �Ĵ���˵����DR4������ʱ���üĴ�����
   λ����UNION�ṹ:  PMIC_DR4_START_DEL_UNION */
#define PMIC_DR4_START_DEL_ADDR(base)             ((base) + (0x0BD))

/* �Ĵ���˵����DR5����ѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DR5_ISET_UNION */
#define PMIC_DR5_ISET_ADDR(base)                  ((base) + (0x0BE))

/* �Ĵ���˵����DR5������ʱ���üĴ�����
   λ����UNION�ṹ:  PMIC_DR5_START_DEL_UNION */
#define PMIC_DR5_START_DEL_ADDR(base)             ((base) + (0x0BF))

/* �Ĵ���˵����DR345��������ʱ�����üĴ�����
   λ����UNION�ṹ:  PMIC_DR334_TIM_CONF0_UNION */
#define PMIC_DR334_TIM_CONF0_ADDR(base)           ((base) + (0x0C0))

/* �Ĵ���˵����DR345��������ʱ�����üĴ�����
   λ����UNION�ṹ:  PMIC_DR345_TIM_CONF1_UNION */
#define PMIC_DR345_TIM_CONF1_ADDR(base)           ((base) + (0x0C1))

/* �Ĵ���˵����IN�˵�ѹ��ֵ�����Ĵ���0��
   λ����UNION�ṹ:  PMIC_VSYS_LOW_SET0_UNION */
#define PMIC_VSYS_LOW_SET0_ADDR(base)             ((base) + (0x0C2))

/* �Ĵ���˵����IN�˵�ѹ��ֵ�����Ĵ���1��
   λ����UNION�ṹ:  PMIC_VSYS_LOW_SET1_UNION */
#define PMIC_VSYS_LOW_SET1_ADDR(base)             ((base) + (0x0C3))

/* �Ĵ���˵����ϵͳ����Ԥ���Ĵ�����
   λ����UNION�ṹ:  PMIC_SYS_CTRL_RESERVE_UNION */
#define PMIC_SYS_CTRL_RESERVE_ADDR(base)          ((base) + (0x0C4))

/* �Ĵ���˵����Ӳ�����ο��ƼĴ���0��
   λ����UNION�ṹ:  PMIC_HARDWIRE_CTRL0_UNION */
#define PMIC_HARDWIRE_CTRL0_ADDR(base)            ((base) + (0x0C5))

/* �Ĵ���˵����Ӳ�����ο��ƼĴ���1��
   λ����UNION�ṹ:  PMIC_HARDWIRE_CTRL1_UNION */
#define PMIC_HARDWIRE_CTRL1_ADDR(base)            ((base) + (0x0C6))

/* �Ĵ���˵����periӲ�߿��ƼĴ���0��
   λ����UNION�ṹ:  PMIC_PERI_CTRL0_UNION */
#define PMIC_PERI_CTRL0_ADDR(base)                ((base) + (0x0C7))

/* �Ĵ���˵����periӲ�߿��ƼĴ���1��
   λ����UNION�ṹ:  PMIC_PERI_CTRL1_UNION */
#define PMIC_PERI_CTRL1_ADDR(base)                ((base) + (0x0C8))

/* �Ĵ���˵����periӲ�ߵ�ѹ�Ĵ�����
   λ����UNION�ṹ:  PMIC_PERI_VSET_CTRL_UNION */
#define PMIC_PERI_VSET_CTRL_ADDR(base)            ((base) + (0x0C9))

/* �Ĵ���˵����periӲ��ʱ�������ƼĴ�����
   λ����UNION�ṹ:  PMIC_PERI_TIME__CTRL_UNION */
#define PMIC_PERI_TIME__CTRL_ADDR(base)           ((base) + (0x0CA))

/* �Ĵ���˵�����ȸ�λ�µ���ƼĴ�����
   λ����UNION�ṹ:  PMIC_HRESET_PWRDOWN_CTRL_UNION */
#define PMIC_HRESET_PWRDOWN_CTRL_ADDR(base)       ((base) + (0x0CB))

/* �Ĵ���˵����32kHzʱ�����ʹ�ܿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_OSC32K_ONOFF_CTRL_UNION */
#define PMIC_OSC32K_ONOFF_CTRL_ADDR(base)         ((base) + (0x0CC))

/* �Ĵ���˵����OCP��SPC�˲�ʱ����ƼĴ�����
   λ����UNION�ṹ:  PMIC_OCP_DEB_CTRL_UNION */
#define PMIC_OCP_DEB_CTRL_ADDR(base)              ((base) + (0x0CD))

/* �Ĵ���˵����OCP��DOCP�˲����ؼĴ�����
   λ����UNION�ṹ:  PMIC_OCP_SCP_ONOFF_UNION */
#define PMIC_OCP_SCP_ONOFF_ADDR(base)             ((base) + (0x0CE))

/* �Ĵ���˵����Ƿѹ�澯��Ƿѹ�ػ��˲�ʱ��ѡ��Ĵ�����
   λ����UNION�ṹ:  PMIC_UV_VSYS_DEB_CTRL_UNION */
#define PMIC_UV_VSYS_DEB_CTRL_ADDR(base)          ((base) + (0x0CF))

/* �Ĵ���˵����BUCK0/1/2/3 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK0_3_OCP_CTRL_UNION */
#define PMIC_BUCK0_3_OCP_CTRL_ADDR(base)          ((base) + (0x0D0))

/* �Ĵ���˵����BUCK4/LDO0/1/2 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK4_LDO0_1_OCP_CTRL_UNION */
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ADDR(base)     ((base) + (0x0D1))

/* �Ĵ���˵����LCO3/4/5/7 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO3_7_OCP_CTRL_UNION */
#define PMIC_LDO3_7_OCP_CTRL_ADDR(base)           ((base) + (0x0D2))

/* �Ĵ���˵����LDO8/9/10/11 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO8_11_OCP_CTRL_UNION */
#define PMIC_LDO8_11_OCP_CTRL_ADDR(base)          ((base) + (0x0D3))

/* �Ĵ���˵����LDO12/13/14/15 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO12_15_OCP_CTRL_UNION */
#define PMIC_LDO12_15_OCP_CTRL_ADDR(base)         ((base) + (0x0D4))

/* �Ĵ���˵����LDO16/17/19/20 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO16_20_OCP_CTRL_UNION */
#define PMIC_LDO16_20_OCP_CTRL_ADDR(base)         ((base) + (0x0D5))

/* �Ĵ���˵����LDO21/22/23/24 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO21_24_OCP_CTRL_UNION */
#define PMIC_LDO21_24_OCP_CTRL_ADDR(base)         ((base) + (0x0D6))

/* �Ĵ���˵����LDO25/26/27/28 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO25_28_OCP_CTRL_UNION */
#define PMIC_LDO25_28_OCP_CTRL_ADDR(base)         ((base) + (0x0D7))

/* �Ĵ���˵����LDO29/30/31/32 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_LDO29_32_OCP_CTRL_UNION */
#define PMIC_LDO29_32_OCP_CTRL_ADDR(base)         ((base) + (0x0D8))

/* �Ĵ���˵����CLASS/BUCK0 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_CLASS_BUCK0_SCP_CTRL_UNION */
#define PMIC_CLASS_BUCK0_SCP_CTRL_ADDR(base)      ((base) + (0x0D9))

/* �Ĵ���˵����BUCK1/2/3/4 OCP�Զ��ضϿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_BUCK1_4_SCP_CTRL_UNION */
#define PMIC_BUCK1_4_SCP_CTRL_ADDR(base)          ((base) + (0x0DA))

/* �Ĵ���˵����ϵͳ���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_SYS_CTRL0_UNION */
#define PMIC_SYS_CTRL0_ADDR(base)                 ((base) + (0x0DB))

/* �Ĵ���˵����ϵͳ���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_SYS_CTRL1_UNION */
#define PMIC_SYS_CTRL1_ADDR(base)                 ((base) + (0x0DC))

/* �Ĵ���˵�������ؼ�ECOʹ�ܿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_COUL_ECO_MASK_UNION */
#define PMIC_COUL_ECO_MASK_ADDR(base)             ((base) + (0x0DD))

/* �Ĵ���˵����SIM���ƼĴ�����
   λ����UNION�ṹ:  PMIC_SIM_CTRL_UNION */
#define PMIC_SIM_CTRL_ADDR(base)                  ((base) + (0x0DE))

/* �Ĵ���˵����SIM�˲����ƼĴ�����
   λ����UNION�ṹ:  PMIC_SIM_DEB_CTRL_UNION */
#define PMIC_SIM_DEB_CTRL_ADDR(base)              ((base) + (0x0DF))

/* �Ĵ���˵����DAC IBIAS���üĴ�����
   λ����UNION�ṹ:  PMIC_AUX_IBIAS_CFG_UNION */
#define PMIC_AUX_IBIAS_CFG_ADDR(base)             ((base) + (0x0E0))

/* �Ĵ���˵����IRQ_MASK0���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_0_UNION */
#define PMIC_IRQ_MASK_0_ADDR(base)                ((base) + (0x0E1))

/* �Ĵ���˵����IRQ_MASK1���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_1_UNION */
#define PMIC_IRQ_MASK_1_ADDR(base)                ((base) + (0x0E2))

/* �Ĵ���˵����IRQ_MASK2���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_2_UNION */
#define PMIC_IRQ_MASK_2_ADDR(base)                ((base) + (0x0E3))

/* �Ĵ���˵����IRQ_MASK3���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_3_UNION */
#define PMIC_IRQ_MASK_3_ADDR(base)                ((base) + (0x0E4))

/* �Ĵ���˵����IRQ_MASK4���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_4_UNION */
#define PMIC_IRQ_MASK_4_ADDR(base)                ((base) + (0x0E5))

/* �Ĵ���˵����IRQ_MASK5���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_5_UNION */
#define PMIC_IRQ_MASK_5_ADDR(base)                ((base) + (0x0E6))

/* �Ĵ���˵����IRQ_MASK6���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_6_UNION */
#define PMIC_IRQ_MASK_6_ADDR(base)                ((base) + (0x0E7))

/* �Ĵ���˵����IRQ_MASK7���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_7_UNION */
#define PMIC_IRQ_MASK_7_ADDR(base)                ((base) + (0x0E8))

/* �Ĵ���˵����IRQ_MASK8���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_8_UNION */
#define PMIC_IRQ_MASK_8_ADDR(base)                ((base) + (0x0E9))

/* �Ĵ���˵����IRQ_MASK9���ƼĴ�����
   λ����UNION�ṹ:  PMIC_IRQ_MASK_9_UNION */
#define PMIC_IRQ_MASK_9_ADDR(base)                ((base) + (0x0EA))

/* �Ĵ���˵����OTP0�ض��Ĵ���0��
   λ����UNION�ṹ:  PMIC_OTP0_0_UNION */
#define PMIC_OTP0_0_ADDR(base)                    ((base) + (0x0EB))

/* �Ĵ���˵����OTP0�ض��Ĵ���1��
   λ����UNION�ṹ:  PMIC_OTP0_1_UNION */
#define PMIC_OTP0_1_ADDR(base)                    ((base) + (0x0EC))

/* �Ĵ���˵����OTP0�ض��Ĵ���2��
   λ����UNION�ṹ:  PMIC_OTP0_2_UNION */
#define PMIC_OTP0_2_ADDR(base)                    ((base) + (0x0ED))

/* �Ĵ���˵����OTP0�ض��Ĵ���3��
   λ����UNION�ṹ:  PMIC_OTP0_3_UNION */
#define PMIC_OTP0_3_ADDR(base)                    ((base) + (0x0EE))

/* �Ĵ���˵����OTP0���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_OTP0_CTRL_0_UNION */
#define PMIC_OTP0_CTRL_0_ADDR(base)               ((base) + (0x0EF))

/* �Ĵ���˵����OTP0���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_OTP0_CTRL_1_UNION */
#define PMIC_OTP0_CTRL_1_ADDR(base)               ((base) + (0x0F0))

/* �Ĵ���˵����OTP0д�������ݼĴ�����
   λ����UNION�ṹ:  PMIC_OTP0_WDATA_UNION */
#define PMIC_OTP0_WDATA_ADDR(base)                ((base) + (0x0F1))

/* �Ĵ���˵����OTP0������Ĵ���0
   λ����UNION�ṹ:  PMIC_OTP0_0_W_UNION */
#define PMIC_OTP0_0_W_ADDR(base)                  ((base) + (0x0F2))

/* �Ĵ���˵����OTP0������Ĵ���1
   λ����UNION�ṹ:  PMIC_OTP0_1_W_UNION */
#define PMIC_OTP0_1_W_ADDR(base)                  ((base) + (0x0F3))

/* �Ĵ���˵����OTP0������Ĵ���2
   λ����UNION�ṹ:  PMIC_OTP0_2_W_UNION */
#define PMIC_OTP0_2_W_ADDR(base)                  ((base) + (0x0F4))

/* �Ĵ���˵����OTP0������Ĵ���3
   λ����UNION�ṹ:  PMIC_OTP0_3_W_UNION */
#define PMIC_OTP0_3_W_ADDR(base)                  ((base) + (0x0F5))

/* �Ĵ���˵����OTP1�ض��Ĵ���0��
   λ����UNION�ṹ:  PMIC_OTP1_0_UNION */
#define PMIC_OTP1_0_ADDR(base)                    ((base) + (0x0F6))

/* �Ĵ���˵����OTP1�ض��Ĵ���1��
   λ����UNION�ṹ:  PMIC_OTP1_1_UNION */
#define PMIC_OTP1_1_ADDR(base)                    ((base) + (0x0F7))

/* �Ĵ���˵����OTP1�ض��Ĵ���2��
   λ����UNION�ṹ:  PMIC_OTP1_2_UNION */
#define PMIC_OTP1_2_ADDR(base)                    ((base) + (0x0F8))

/* �Ĵ���˵����OTP1�ض��Ĵ���3��
   λ����UNION�ṹ:  PMIC_OTP1_3_UNION */
#define PMIC_OTP1_3_ADDR(base)                    ((base) + (0x0F9))

/* �Ĵ���˵����OTP1���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_OTP1_CTRL_0_UNION */
#define PMIC_OTP1_CTRL_0_ADDR(base)               ((base) + (0x0FA))

/* �Ĵ���˵����OTP1���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_OTP1_CTRL_1_UNION */
#define PMIC_OTP1_CTRL_1_ADDR(base)               ((base) + (0x0FB))

/* �Ĵ���˵����OTP0д�������ݼĴ�����
   λ����UNION�ṹ:  PMIC_OTP1_WDATA_UNION */
#define PMIC_OTP1_WDATA_ADDR(base)                ((base) + (0x0FC))

/* �Ĵ���˵����OTP1������Ĵ���0��
   λ����UNION�ṹ:  PMIC_OTP1_0_W_UNION */
#define PMIC_OTP1_0_W_ADDR(base)                  ((base) + (0x0FD))

/* �Ĵ���˵����OTP1������Ĵ���1��
   λ����UNION�ṹ:  PMIC_OTP1_1_W_UNION */
#define PMIC_OTP1_1_W_ADDR(base)                  ((base) + (0x0FE))

/* �Ĵ���˵����OTP1������Ĵ���2��
   λ����UNION�ṹ:  PMIC_OTP1_2_W_UNION */
#define PMIC_OTP1_2_W_ADDR(base)                  ((base) + (0x0FF))

/* �Ĵ���˵����OTP1������Ĵ���3��
   λ����UNION�ṹ:  PMIC_OTP1_3_W_UNION */
#define PMIC_OTP1_3_W_ADDR(base)                  ((base) + (0x100))

/* �Ĵ���˵����RESETIN_N��λ��Ϣ�Ĵ���0��
   λ����UNION�ṹ:  PMIC_HRST_REG0_UNION */
#define PMIC_HRST_REG0_ADDR(base)                 ((base) + (0x101))

/* �Ĵ���˵����RESETIN_N��λ��Ϣ�Ĵ���1��
   λ����UNION�ṹ:  PMIC_HRST_REG1_UNION */
#define PMIC_HRST_REG1_ADDR(base)                 ((base) + (0x102))

/* �Ĵ���˵����RESETIN_N��λ��Ϣ�Ĵ���2��
   λ����UNION�ṹ:  PMIC_HRST_REG2_UNION */
#define PMIC_HRST_REG2_ADDR(base)                 ((base) + (0x103))

/* �Ĵ���˵����SOFT��λ��Ϣ�Ĵ�����
   λ����UNION�ṹ:  PMIC_SOFT_RST_REG_UNION */
#define PMIC_SOFT_RST_REG_ADDR(base)              ((base) + (0x104))

/* �Ĵ���˵����ʱ�ӿ��ƼĴ���0��
   λ����UNION�ṹ:  PMIC_CLK_TOP_CTRL0_UNION */
#define PMIC_CLK_TOP_CTRL0_ADDR(base)             ((base) + (0x105))

/* �Ĵ���˵����ʱ�ӿ��ƼĴ���1��
   λ����UNION�ṹ:  PMIC_CLK_TOP_CTRL1_UNION */
#define PMIC_CLK_TOP_CTRL1_ADDR(base)             ((base) + (0x106))

/* �Ĵ���˵����ʱ�ӿ��ƼĴ���2��
   λ����UNION�ṹ:  PMIC_CLK_TOP_CTRL2_UNION */
#define PMIC_CLK_TOP_CTRL2_ADDR(base)             ((base) + (0x107))

/* �Ĵ���˵����ʱ�ӿ��ƼĴ���3��
   λ����UNION�ṹ:  PMIC_CLK_TOP_CTRL3_UNION */
#define PMIC_CLK_TOP_CTRL3_ADDR(base)             ((base) + (0x108))

/* �Ĵ���˵����ʱ�ӿ��ƼĴ���4��
   λ����UNION�ṹ:  PMIC_CLK_TOP_CTRL4_UNION */
#define PMIC_CLK_TOP_CTRL4_ADDR(base)             ((base) + (0x109))

/* �Ĵ���˵����ʱ�ӿ��ƼĴ���5��
   λ����UNION�ṹ:  PMIC_CLK_TOP_CTRL5_UNION */
#define PMIC_CLK_TOP_CTRL5_ADDR(base)             ((base) + (0x10A))

/* �Ĵ���˵����ʱ�ӿ��ƼĴ���6��
   λ����UNION�ṹ:  PMIC_CLK_TOP_CTRL6_UNION */
#define PMIC_CLK_TOP_CTRL6_ADDR(base)             ((base) + (0x10B))

/* �Ĵ���˵����ʱ�ӿ��ƼĴ���7��
   λ����UNION�ṹ:  PMIC_CLK_TOP_CTRL7_UNION */
#define PMIC_CLK_TOP_CTRL7_ADDR(base)             ((base) + (0x10C))

/* �Ĵ���˵����256K RC���ƼĴ���0��
   λ����UNION�ṹ:  PMIC_CLK_256K_CTRL0_UNION */
#define PMIC_CLK_256K_CTRL0_ADDR(base)            ((base) + (0x10D))

/* �Ĵ���˵����256K RC���ƼĴ���1��
   λ����UNION�ṹ:  PMIC_CLK_256K_CTRL1_UNION */
#define PMIC_CLK_256K_CTRL1_ADDR(base)            ((base) + (0x10E))

/* �Ĵ���˵����ʱ�ӿ���Ԥ���Ĵ���0��
   λ����UNION�ṹ:  PMIC_CLK_TOP_RESERVE0_UNION */
#define PMIC_CLK_TOP_RESERVE0_ADDR(base)          ((base) + (0x10F))

/* �Ĵ���˵����ʱ�ӿ���Ԥ���Ĵ���1��
   λ����UNION�ṹ:  PMIC_CLK_TOP_RESERVE1_UNION */
#define PMIC_CLK_TOP_RESERVE1_ADDR(base)          ((base) + (0x110))

/* �Ĵ���˵��������ϵͳdebugԤ���Ĵ���0��
   λ����UNION�ṹ:  PMIC_SYS_DEBUG0_UNION */
#define PMIC_SYS_DEBUG0_ADDR(base)                ((base) + (0x111))

/* �Ĵ���˵��������ϵͳdebugԤ���Ĵ���1��
   λ����UNION�ṹ:  PMIC_SYS_DEBUG1_UNION */
#define PMIC_SYS_DEBUG1_ADDR(base)                ((base) + (0x112))

/* �Ĵ���˵����DAC0 din��λӳ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DAC0_DIN_MSB_UNION */
#define PMIC_DAC0_DIN_MSB_ADDR(base)              ((base) + (0x113))

/* �Ĵ���˵����DAC0 din��λӳ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DAC0_DIN_LSB_UNION */
#define PMIC_DAC0_DIN_LSB_ADDR(base)              ((base) + (0x114))

/* �Ĵ���˵����DAC1 din��λӳ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DAC1_DIN_MSB_UNION */
#define PMIC_DAC1_DIN_MSB_ADDR(base)              ((base) + (0x115))

/* �Ĵ���˵����DAC1 din��λӳ��Ĵ�����
   λ����UNION�ṹ:  PMIC_DAC1_DIN_LSB_UNION */
#define PMIC_DAC1_DIN_LSB_ADDR(base)              ((base) + (0x116))

/* �Ĵ���˵����xo_core_en,xo_ldo_en,eco_in_n�Ĵ���д���ο��ƼĴ�����
   λ����UNION�ṹ:  PMIC_CORE_LDO_ECO_LOCK_UNION */
#define PMIC_CORE_LDO_ECO_LOCK_ADDR(base)         ((base) + (0x117))



/****************************************************************************
                     (2/5) PMU_IRQ
 ****************************************************************************/
/* �Ĵ���˵����BUKC0-4��LDO0-2 OCP�¼���¼�Ĵ�����
   λ����UNION�ṹ:  PMIC_NP_OCP0_UNION */
#define PMIC_NP_OCP0_ADDR(base)                   ((base) + (0x11A))

/* �Ĵ���˵����LDO3-11 OCP�¼���¼�Ĵ�����
   λ����UNION�ṹ:  PMIC_NP_OCP1_UNION */
#define PMIC_NP_OCP1_ADDR(base)                   ((base) + (0x11B))

/* �Ĵ���˵����LDO12-20 OCP�¼���¼�Ĵ�����
   λ����UNION�ṹ:  PMIC_NP_OCP2_UNION */
#define PMIC_NP_OCP2_ADDR(base)                   ((base) + (0x11C))

/* �Ĵ���˵����LDO21-28 OCP�¼���¼�Ĵ�����
   λ����UNION�ṹ:  PMIC_NP_OCP3_UNION */
#define PMIC_NP_OCP3_ADDR(base)                   ((base) + (0x11D))

/* �Ĵ���˵����LDO29-32 CLASSD OCP�¼���¼�Ĵ�����
   λ����UNION�ṹ:  PMIC_NP_OCP4_UNION */
#define PMIC_NP_OCP4_ADDR(base)                   ((base) + (0x11E))

/* �Ĵ���˵����BUCK0-4 SCP�¼���¼�Ĵ�����
   λ����UNION�ṹ:  PMIC_NP_SCP_UNION */
#define PMIC_NP_SCP_ADDR(base)                    ((base) + (0x11F))

/* �Ĵ���˵�����жϼĴ���0��
   λ����UNION�ṹ:  PMIC_IRQ0_UNION */
#define PMIC_IRQ0_ADDR(base)                      ((base) + (0x120))

/* �Ĵ���˵�����жϼĴ���1��
   λ����UNION�ṹ:  PMIC_IRQ1_UNION */
#define PMIC_IRQ1_ADDR(base)                      ((base) + (0x121))

/* �Ĵ���˵�����жϼĴ���2��
   λ����UNION�ṹ:  PMIC_IRQ2_UNION */
#define PMIC_IRQ2_ADDR(base)                      ((base) + (0x122))

/* �Ĵ���˵�����жϼĴ���3��
   λ����UNION�ṹ:  PMIC_IRQ3_UNION */
#define PMIC_IRQ3_ADDR(base)                      ((base) + (0x123))

/* �Ĵ���˵����OCP�жϼĴ���0��
   λ����UNION�ṹ:  PMIC_OCP_IRQ0_UNION */
#define PMIC_OCP_IRQ0_ADDR(base)                  ((base) + (0x124))

/* �Ĵ���˵����OCP�жϼĴ���1��
   λ����UNION�ṹ:  PMIC_OCP_IRQ1_UNION */
#define PMIC_OCP_IRQ1_ADDR(base)                  ((base) + (0x125))

/* �Ĵ���˵����OCP�жϼĴ���3��
   λ����UNION�ṹ:  PMIC_OCP_IRQ2_UNION */
#define PMIC_OCP_IRQ2_ADDR(base)                  ((base) + (0x126))

/* �Ĵ���˵����OCP�жϼĴ���4��
   λ����UNION�ṹ:  PMIC_OCP_IRQ3_UNION */
#define PMIC_OCP_IRQ3_ADDR(base)                  ((base) + (0x127))

/* �Ĵ���˵����OCP�жϼĴ���5��
   λ����UNION�ṹ:  PMIC_OCP_IRQ4_UNION */
#define PMIC_OCP_IRQ4_ADDR(base)                  ((base) + (0x128))

/* �Ĵ���˵����OCP�жϼĴ���6��
   λ����UNION�ṹ:  PMIC_OCP_IRQ5_UNION */
#define PMIC_OCP_IRQ5_ADDR(base)                  ((base) + (0x129))

/* �Ĵ���˵�����¼���¼�Ĵ���0��
   λ����UNION�ṹ:  PMIC_NP_RECORD0_UNION */
#define PMIC_NP_RECORD0_ADDR(base)                ((base) + (0x12A))

/* �Ĵ���˵�����¼���¼�Ĵ���1��
   λ����UNION�ṹ:  PMIC_NP_RECORD1_UNION */
#define PMIC_NP_RECORD1_ADDR(base)                ((base) + (0x12B))



/****************************************************************************
                     (3/5) PMU_RTC
 ****************************************************************************/
/* �Ĵ���˵����RTC��ǰʱ��Ĵ���bit[7:0]��
   λ����UNION�ṹ:  PMIC_RTCDR0_UNION */
#define PMIC_RTCDR0_ADDR(base)                    ((base) + (0x12C))

/* �Ĵ���˵����RTC��ǰʱ��Ĵ���bit[15:8]��
   λ����UNION�ṹ:  PMIC_RTCDR1_UNION */
#define PMIC_RTCDR1_ADDR(base)                    ((base) + (0x12D))

/* �Ĵ���˵����RTC��ǰʱ��Ĵ���bit[23:16]��
   λ����UNION�ṹ:  PMIC_RTCDR2_UNION */
#define PMIC_RTCDR2_ADDR(base)                    ((base) + (0x12E))

/* �Ĵ���˵����RTC��ǰʱ��Ĵ���bit[31:24]��
   λ����UNION�ṹ:  PMIC_RTCDR3_UNION */
#define PMIC_RTCDR3_ADDR(base)                    ((base) + (0x12F))

/* �Ĵ���˵����RTC�ȽϼĴ���bit[7:0]��
   λ����UNION�ṹ:  PMIC_RTCMR0_UNION */
#define PMIC_RTCMR0_ADDR(base)                    ((base) + (0x130))

/* �Ĵ���˵����RTC�ȽϼĴ���bit[15:8]��
   λ����UNION�ṹ:  PMIC_RTCMR1_UNION */
#define PMIC_RTCMR1_ADDR(base)                    ((base) + (0x131))

/* �Ĵ���˵����RTC�ȽϼĴ���bit[23:16]��
   λ����UNION�ṹ:  PMIC_RTCMR2_UNION */
#define PMIC_RTCMR2_ADDR(base)                    ((base) + (0x132))

/* �Ĵ���˵����RTC�ȽϼĴ���bit[31:24]��
   λ����UNION�ṹ:  PMIC_RTCMR3_UNION */
#define PMIC_RTCMR3_ADDR(base)                    ((base) + (0x133))

/* �Ĵ���˵����RTC���ؼĴ���bit[7:0]��
   λ����UNION�ṹ:  PMIC_RTCLR0_UNION */
#define PMIC_RTCLR0_ADDR(base)                    ((base) + (0x134))

/* �Ĵ���˵����RTC���ؼĴ���bit[15:8]��
   λ����UNION�ṹ:  PMIC_RTCLR1_UNION */
#define PMIC_RTCLR1_ADDR(base)                    ((base) + (0x135))

/* �Ĵ���˵����RTC���ؼĴ���bit[23:16]��
   λ����UNION�ṹ:  PMIC_RTCLR2_UNION */
#define PMIC_RTCLR2_ADDR(base)                    ((base) + (0x136))

/* �Ĵ���˵����RTC���ؼĴ���bit[31:24]��
   λ����UNION�ṹ:  PMIC_RTCLR3_UNION */
#define PMIC_RTCLR3_ADDR(base)                    ((base) + (0x137))

/* �Ĵ���˵����RTC���ƼĴ�����
   λ����UNION�ṹ:  PMIC_RTCCTRL_UNION */
#define PMIC_RTCCTRL_ADDR(base)                   ((base) + (0x138))

/* �Ĵ���˵����XO_THRESOLD[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_XO_THRESOLD0_UNION */
#define PMIC_XO_THRESOLD0_ADDR(base)              ((base) + (0x139))

/* �Ĵ���˵����XO_THRESOLD[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_XO_THRESOLD1_UNION */
#define PMIC_XO_THRESOLD1_ADDR(base)              ((base) + (0x13A))

/* �Ĵ���˵����CRC_VALUE[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CRC_VAULE0_UNION */
#define PMIC_CRC_VAULE0_ADDR(base)                ((base) + (0x13B))

/* �Ĵ���˵����CRC_VALUE[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CRC_VAULE1_UNION */
#define PMIC_CRC_VAULE1_ADDR(base)                ((base) + (0x13C))

/* �Ĵ���˵����CRC_VALUE[20:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CRC_VAULE2_UNION */
#define PMIC_CRC_VAULE2_ADDR(base)                ((base) + (0x13D))

/* �Ĵ���˵����RTC�ϵ�����[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRUP_TIMER0_UNION */
#define PMIC_RTC_PWRUP_TIMER0_ADDR(base)          ((base) + (0x13E))

/* �Ĵ���˵����RTC�ϵ�����[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRUP_TIMER1_UNION */
#define PMIC_RTC_PWRUP_TIMER1_ADDR(base)          ((base) + (0x13F))

/* �Ĵ���˵����RTC�ϵ�����[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRUP_TIMER2_UNION */
#define PMIC_RTC_PWRUP_TIMER2_ADDR(base)          ((base) + (0x140))

/* �Ĵ���˵����RTC�ϵ�����[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRUP_TIMER3_UNION */
#define PMIC_RTC_PWRUP_TIMER3_ADDR(base)          ((base) + (0x141))

/* �Ĵ���˵����RTC�µ�����[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRDOWN_TIMER0_UNION */
#define PMIC_RTC_PWRDOWN_TIMER0_ADDR(base)        ((base) + (0x142))

/* �Ĵ���˵����RTC�µ�����[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRDOWN_TIMER1_UNION */
#define PMIC_RTC_PWRDOWN_TIMER1_ADDR(base)        ((base) + (0x143))

/* �Ĵ���˵����RTC�µ�����[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRDOWN_TIMER2_UNION */
#define PMIC_RTC_PWRDOWN_TIMER2_ADDR(base)        ((base) + (0x144))

/* �Ĵ���˵����RTC�µ�����[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_RTC_PWRDOWN_TIMER3_UNION */
#define PMIC_RTC_PWRDOWN_TIMER3_ADDR(base)        ((base) + (0x145))



/****************************************************************************
                     (4/5) PMU_COUL
 ****************************************************************************/
/* �Ĵ���˵�������ؼ��жϼĴ�����
   λ����UNION�ṹ:  PMIC_COUL_IRQ_UNION */
#define PMIC_COUL_IRQ_ADDR(base)                  ((base) + (0x14B))

/* �Ĵ���˵�������ؼ��ж����μĴ�����
   λ����UNION�ṹ:  PMIC_COUL_IRQ_MASK_UNION */
#define PMIC_COUL_IRQ_MASK_ADDR(base)             ((base) + (0x14C))

/* �Ĵ���˵������ǰ����[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT_0_UNION */
#define PMIC_CURRENT_0_ADDR(base)                 ((base) + (0x14D))

/* �Ĵ���˵������ǰ����[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT_1_UNION */
#define PMIC_CURRENT_1_ADDR(base)                 ((base) + (0x14E))

/* �Ĵ���˵������ǰ��ѹ[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT_0_UNION */
#define PMIC_V_OUT_0_ADDR(base)                   ((base) + (0x14F))

/* �Ĵ���˵������ǰ��ѹ[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT_1_UNION */
#define PMIC_V_OUT_1_ADDR(base)                   ((base) + (0x150))

/* �Ĵ���˵�������ؼƿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_CLJ_CTRL_REG_UNION */
#define PMIC_CLJ_CTRL_REG_ADDR(base)              ((base) + (0x151))

/* �Ĵ���˵����ECO_REFLASH����ʱ��Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_REFALSH_TIME_UNION */
#define PMIC_ECO_REFALSH_TIME_ADDR(base)          ((base) + (0x152))

/* �Ĵ���˵����cl_out[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_OUT0_UNION */
#define PMIC_CL_OUT0_ADDR(base)                   ((base) + (0x153))

/* �Ĵ���˵����cl_out[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_OUT1_UNION */
#define PMIC_CL_OUT1_ADDR(base)                   ((base) + (0x154))

/* �Ĵ���˵����cl_out[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_OUT2_UNION */
#define PMIC_CL_OUT2_ADDR(base)                   ((base) + (0x155))

/* �Ĵ���˵����cl_out[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_OUT3_UNION */
#define PMIC_CL_OUT3_ADDR(base)                   ((base) + (0x156))

/* �Ĵ���˵����cl_in[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_IN0_UNION */
#define PMIC_CL_IN0_ADDR(base)                    ((base) + (0x157))

/* �Ĵ���˵����cl_in[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_IN1_UNION */
#define PMIC_CL_IN1_ADDR(base)                    ((base) + (0x158))

/* �Ĵ���˵����cl_in[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_IN2_UNION */
#define PMIC_CL_IN2_ADDR(base)                    ((base) + (0x159))

/* �Ĵ���˵����cl_in[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_IN3_UNION */
#define PMIC_CL_IN3_ADDR(base)                    ((base) + (0x15A))

/* �Ĵ���˵����chg_timer[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CHG_TIMER0_UNION */
#define PMIC_CHG_TIMER0_ADDR(base)                ((base) + (0x15B))

/* �Ĵ���˵����chg_timer[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CHG_TIMER1_UNION */
#define PMIC_CHG_TIMER1_ADDR(base)                ((base) + (0x15C))

/* �Ĵ���˵����chg_timer[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CHG_TIMER2_UNION */
#define PMIC_CHG_TIMER2_ADDR(base)                ((base) + (0x15D))

/* �Ĵ���˵����chg_timer[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CHG_TIMER3_UNION */
#define PMIC_CHG_TIMER3_ADDR(base)                ((base) + (0x15E))

/* �Ĵ���˵����load_timer[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_LOAD_TIMER0_UNION */
#define PMIC_LOAD_TIMER0_ADDR(base)               ((base) + (0x15F))

/* �Ĵ���˵����load_timer[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_LOAD_TIMER1_UNION */
#define PMIC_LOAD_TIMER1_ADDR(base)               ((base) + (0x160))

/* �Ĵ���˵����load_timer[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_LOAD_TIMER2_UNION */
#define PMIC_LOAD_TIMER2_ADDR(base)               ((base) + (0x161))

/* �Ĵ���˵����load_timer[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_LOAD_TIMER3_UNION */
#define PMIC_LOAD_TIMER3_ADDR(base)               ((base) + (0x162))

/* �Ĵ���˵����cl_int[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_INT0_UNION */
#define PMIC_CL_INT0_ADDR(base)                   ((base) + (0x163))

/* �Ĵ���˵����cl_int[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_INT1_UNION */
#define PMIC_CL_INT1_ADDR(base)                   ((base) + (0x164))

/* �Ĵ���˵����cl_int[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_INT2_UNION */
#define PMIC_CL_INT2_ADDR(base)                   ((base) + (0x165))

/* �Ĵ���˵����cl_int[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CL_INT3_UNION */
#define PMIC_CL_INT3_ADDR(base)                   ((base) + (0x166))

/* �Ĵ���˵����v_int[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_INT0_UNION */
#define PMIC_V_INT0_ADDR(base)                    ((base) + (0x167))

/* �Ĵ���˵����v_int[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_INT1_UNION */
#define PMIC_V_INT1_ADDR(base)                    ((base) + (0x168))

/* �Ĵ���˵����offset_current[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_CURRENT0_UNION */
#define PMIC_OFFSET_CURRENT0_ADDR(base)           ((base) + (0x169))

/* �Ĵ���˵����offset_current[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_CURRENT1_UNION */
#define PMIC_OFFSET_CURRENT1_ADDR(base)           ((base) + (0x16A))

/* �Ĵ���˵����offset_voltage[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_VOLTAGE0_UNION */
#define PMIC_OFFSET_VOLTAGE0_ADDR(base)           ((base) + (0x16B))

/* �Ĵ���˵����offset_voltage[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_VOLTAGE1_UNION */
#define PMIC_OFFSET_VOLTAGE1_ADDR(base)           ((base) + (0x16C))

/* �Ĵ���˵����v_ocv_data[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OCV_VOLTAGE0_UNION */
#define PMIC_OCV_VOLTAGE0_ADDR(base)              ((base) + (0x16D))

/* �Ĵ���˵����v_ocv_data[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OCV_VOLTAGE1_UNION */
#define PMIC_OCV_VOLTAGE1_ADDR(base)              ((base) + (0x16E))

/* �Ĵ���˵����i_ocv_data[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OCV_CURRENT0_UNION */
#define PMIC_OCV_CURRENT0_ADDR(base)              ((base) + (0x16F))

/* �Ĵ���˵����i_ocv_data[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OCV_CURRENT1_UNION */
#define PMIC_OCV_CURRENT1_ADDR(base)              ((base) + (0x170))

/* �Ĵ���˵����eco_out_clin[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLIN_0_UNION */
#define PMIC_ECO_OUT_CLIN_0_ADDR(base)            ((base) + (0x171))

/* �Ĵ���˵����eco_out_clin[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLIN_1_UNION */
#define PMIC_ECO_OUT_CLIN_1_ADDR(base)            ((base) + (0x172))

/* �Ĵ���˵����eco_out_clin[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLIN_2_UNION */
#define PMIC_ECO_OUT_CLIN_2_ADDR(base)            ((base) + (0x173))

/* �Ĵ���˵����eco_out_clin[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLIN_3_UNION */
#define PMIC_ECO_OUT_CLIN_3_ADDR(base)            ((base) + (0x174))

/* �Ĵ���˵����eco_out_clout[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLOUT_0_UNION */
#define PMIC_ECO_OUT_CLOUT_0_ADDR(base)           ((base) + (0x175))

/* �Ĵ���˵����eco_out_clout[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLOUT_1_UNION */
#define PMIC_ECO_OUT_CLOUT_1_ADDR(base)           ((base) + (0x176))

/* �Ĵ���˵����eco_out_clout[23:16]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLOUT_2_UNION */
#define PMIC_ECO_OUT_CLOUT_2_ADDR(base)           ((base) + (0x177))

/* �Ĵ���˵����eco_out_clout[31:24]�Ĵ�����
   λ����UNION�ṹ:  PMIC_ECO_OUT_CLOUT_3_UNION */
#define PMIC_ECO_OUT_CLOUT_3_ADDR(base)           ((base) + (0x178))

/* �Ĵ���˵����v_out_pre0[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE0_UNION */
#define PMIC_V_OUT0_PRE0_ADDR(base)               ((base) + (0x179))

/* �Ĵ���˵����v_out_pre0[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE0_UNION */
#define PMIC_V_OUT1_PRE0_ADDR(base)               ((base) + (0x17A))

/* �Ĵ���˵����v_out_pre1[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE1_UNION */
#define PMIC_V_OUT0_PRE1_ADDR(base)               ((base) + (0x17B))

/* �Ĵ���˵����v_out_pre1[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE1_UNION */
#define PMIC_V_OUT1_PRE1_ADDR(base)               ((base) + (0x17C))

/* �Ĵ���˵����v_out_pre2[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE2_UNION */
#define PMIC_V_OUT0_PRE2_ADDR(base)               ((base) + (0x17D))

/* �Ĵ���˵����v_out_pre2[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE2_UNION */
#define PMIC_V_OUT1_PRE2_ADDR(base)               ((base) + (0x17E))

/* �Ĵ���˵����v_out_pre3[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE3_UNION */
#define PMIC_V_OUT0_PRE3_ADDR(base)               ((base) + (0x17F))

/* �Ĵ���˵����v_out_pre3[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE3_UNION */
#define PMIC_V_OUT1_PRE3_ADDR(base)               ((base) + (0x180))

/* �Ĵ���˵����v_out_pre4[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE4_UNION */
#define PMIC_V_OUT0_PRE4_ADDR(base)               ((base) + (0x181))

/* �Ĵ���˵����v_out_pre4[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE4_UNION */
#define PMIC_V_OUT1_PRE4_ADDR(base)               ((base) + (0x182))

/* �Ĵ���˵����v_out_pre5[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE5_UNION */
#define PMIC_V_OUT0_PRE5_ADDR(base)               ((base) + (0x183))

/* �Ĵ���˵����v_out_pre5[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE5_UNION */
#define PMIC_V_OUT1_PRE5_ADDR(base)               ((base) + (0x184))

/* �Ĵ���˵����v_out_pre6[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE6_UNION */
#define PMIC_V_OUT0_PRE6_ADDR(base)               ((base) + (0x185))

/* �Ĵ���˵����v_out_pre6[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE6_UNION */
#define PMIC_V_OUT1_PRE6_ADDR(base)               ((base) + (0x186))

/* �Ĵ���˵����v_out_pre7[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE7_UNION */
#define PMIC_V_OUT0_PRE7_ADDR(base)               ((base) + (0x187))

/* �Ĵ���˵����v_out_pre7[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE7_UNION */
#define PMIC_V_OUT1_PRE7_ADDR(base)               ((base) + (0x188))

/* �Ĵ���˵����v_out_pre8[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE8_UNION */
#define PMIC_V_OUT0_PRE8_ADDR(base)               ((base) + (0x189))

/* �Ĵ���˵����v_out_pre8[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE8_UNION */
#define PMIC_V_OUT1_PRE8_ADDR(base)               ((base) + (0x18A))

/* �Ĵ���˵����v_out_pre9[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT0_PRE9_UNION */
#define PMIC_V_OUT0_PRE9_ADDR(base)               ((base) + (0x18B))

/* �Ĵ���˵����v_out_pre9[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_V_OUT1_PRE9_UNION */
#define PMIC_V_OUT1_PRE9_ADDR(base)               ((base) + (0x18C))

/* �Ĵ���˵����current_pre0[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE0_UNION */
#define PMIC_CURRENT0_PRE0_ADDR(base)             ((base) + (0x18D))

/* �Ĵ���˵����current_pre0[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE0_UNION */
#define PMIC_CURRENT1_PRE0_ADDR(base)             ((base) + (0x18E))

/* �Ĵ���˵����current_pre1[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE1_UNION */
#define PMIC_CURRENT0_PRE1_ADDR(base)             ((base) + (0x18F))

/* �Ĵ���˵����current_pre1[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE1_UNION */
#define PMIC_CURRENT1_PRE1_ADDR(base)             ((base) + (0x190))

/* �Ĵ���˵����current_pre2[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE2_UNION */
#define PMIC_CURRENT0_PRE2_ADDR(base)             ((base) + (0x191))

/* �Ĵ���˵����current_pre2[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE2_UNION */
#define PMIC_CURRENT1_PRE2_ADDR(base)             ((base) + (0x192))

/* �Ĵ���˵����current_pre3[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE3_UNION */
#define PMIC_CURRENT0_PRE3_ADDR(base)             ((base) + (0x193))

/* �Ĵ���˵����current_pre3[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE3_UNION */
#define PMIC_CURRENT1_PRE3_ADDR(base)             ((base) + (0x194))

/* �Ĵ���˵����current_pre4[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE4_UNION */
#define PMIC_CURRENT0_PRE4_ADDR(base)             ((base) + (0x195))

/* �Ĵ���˵����current_pre4[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE4_UNION */
#define PMIC_CURRENT1_PRE4_ADDR(base)             ((base) + (0x196))

/* �Ĵ���˵����current_pre5[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE5_UNION */
#define PMIC_CURRENT0_PRE5_ADDR(base)             ((base) + (0x197))

/* �Ĵ���˵����current_pre5[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE5_UNION */
#define PMIC_CURRENT1_PRE5_ADDR(base)             ((base) + (0x198))

/* �Ĵ���˵����current_pre6[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE6_UNION */
#define PMIC_CURRENT0_PRE6_ADDR(base)             ((base) + (0x199))

/* �Ĵ���˵����current_pre6[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE6_UNION */
#define PMIC_CURRENT1_PRE6_ADDR(base)             ((base) + (0x19A))

/* �Ĵ���˵����current_pre7[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE7_UNION */
#define PMIC_CURRENT0_PRE7_ADDR(base)             ((base) + (0x19B))

/* �Ĵ���˵����current_pre7[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE7_UNION */
#define PMIC_CURRENT1_PRE7_ADDR(base)             ((base) + (0x19C))

/* �Ĵ���˵����current_pre8[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE8_UNION */
#define PMIC_CURRENT0_PRE8_ADDR(base)             ((base) + (0x19D))

/* �Ĵ���˵����current_pre8[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE8_UNION */
#define PMIC_CURRENT1_PRE8_ADDR(base)             ((base) + (0x19E))

/* �Ĵ���˵����current_pre9[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT0_PRE9_UNION */
#define PMIC_CURRENT0_PRE9_ADDR(base)             ((base) + (0x19F))

/* �Ĵ���˵����current_pre9[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_CURRENT1_PRE9_UNION */
#define PMIC_CURRENT1_PRE9_ADDR(base)             ((base) + (0x1A0))

/* �Ĵ���˵��������ƫ�õ���[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_CURRENT_MOD_0_UNION */
#define PMIC_OFFSET_CURRENT_MOD_0_ADDR(base)      ((base) + (0x1A1))

/* �Ĵ���˵��������ƫ�õ���[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_CURRENT_MOD_1_UNION */
#define PMIC_OFFSET_CURRENT_MOD_1_ADDR(base)      ((base) + (0x1A2))

/* �Ĵ���˵������ѹƫ�õ���[7:0]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_VOLTAGE_MOD_0_UNION */
#define PMIC_OFFSET_VOLTAGE_MOD_0_ADDR(base)      ((base) + (0x1A3))

/* �Ĵ���˵������ѹƫ�õ���[15:8]�Ĵ�����
   λ����UNION�ṹ:  PMIC_OFFSET_VOLTAGE_MOD_1_UNION */
#define PMIC_OFFSET_VOLTAGE_MOD_1_ADDR(base)      ((base) + (0x1A4))

/* �Ĵ���˵�������ؼƱ���1�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_RESERVED1_UNION */
#define PMIC_CLJ_RESERVED1_ADDR(base)             ((base) + (0x1A5))

/* �Ĵ���˵�������ؼƱ���2�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_RESERVED2_UNION */
#define PMIC_CLJ_RESERVED2_ADDR(base)             ((base) + (0x1A6))

/* �Ĵ���˵�������ؼƱ���3�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_RESERVED3_UNION */
#define PMIC_CLJ_RESERVED3_ADDR(base)             ((base) + (0x1A7))

/* �Ĵ���˵�������ؼƱ���4�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_RESERVED4_UNION */
#define PMIC_CLJ_RESERVED4_ADDR(base)             ((base) + (0x1A8))

/* �Ĵ���˵�������ؼƱ���5�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_RESERVED5_UNION */
#define PMIC_CLJ_RESERVED5_ADDR(base)             ((base) + (0x1A9))

/* �Ĵ���˵�������ؼƱ���6�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_RESERVED6_UNION */
#define PMIC_CLJ_RESERVED6_ADDR(base)             ((base) + (0x1AA))

/* �Ĵ���˵�������ؼƱ���7�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_RESERVED7_UNION */
#define PMIC_CLJ_RESERVED7_ADDR(base)             ((base) + (0x1AB))

/* �Ĵ���˵����PMU��λ�Ĵ�����
   λ����UNION�ṹ:  PMIC_PMU_SOFT_RST_UNION */
#define PMIC_PMU_SOFT_RST_ADDR(base)              ((base) + (0x1AC))

/* �Ĵ���˵�������ؼ�DEBUGר��1�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_DEBUG_UNION */
#define PMIC_CLJ_DEBUG_ADDR(base)                 ((base) + (0x1AD))

/* �Ĵ���˵�������ؼ�DEBUGר��2�Ĵ�����
   λ����UNION�ṹ:  PMIC_CLJ_DEBUG_2_UNION */
#define PMIC_CLJ_DEBUG_2_ADDR(base)               ((base) + (0x1AE))

/* �Ĵ���˵�������ؼ�DEBUGר��3�Ĵ�����
   λ����UNION�ṹ:  PMIC_STATE_TEST_UNION */
#define PMIC_STATE_TEST_ADDR(base)                ((base) + (0x1AF))

/* �Ĵ���˵�������ؼ���ģ�ӿ�Ԥ���Ĵ�����
   λ����UNION�ṹ:  PMIC_COUL_RESERVE_UNION */
#define PMIC_COUL_RESERVE_ADDR(base)              ((base) + (0x1B0))

/* �Ĵ���˵�������Ԥ���Ĵ���0��
   λ����UNION�ṹ:  PMIC_SOFT_RESERE0_UNION */
#define PMIC_SOFT_RESERE0_ADDR(base)              ((base) + (0x1B1))

/* �Ĵ���˵�������Ԥ���Ĵ���1��
   λ����UNION�ṹ:  PMIC_SOFT_RESERE1_UNION */
#define PMIC_SOFT_RESERE1_ADDR(base)              ((base) + (0x1B2))

/* �Ĵ���˵�������Ԥ���Ĵ���2��
   λ����UNION�ṹ:  PMIC_SOFT_RESERE2_UNION */
#define PMIC_SOFT_RESERE2_ADDR(base)              ((base) + (0x1B3))

/* �Ĵ���˵�������Ԥ���Ĵ���3��
   λ����UNION�ṹ:  PMIC_SOFT_RESERE3_UNION */
#define PMIC_SOFT_RESERE3_ADDR(base)              ((base) + (0x1B4))

/* �Ĵ���˵�������Ԥ���Ĵ���4��
   λ����UNION�ṹ:  PMIC_SOFT_RESERE4_UNION */
#define PMIC_SOFT_RESERE4_ADDR(base)              ((base) + (0x1B5))

/* �Ĵ���˵�������Ԥ���Ĵ���5��
   λ����UNION�ṹ:  PMIC_SOFT_RESERE5_UNION */
#define PMIC_SOFT_RESERE5_ADDR(base)              ((base) + (0x1B6))

/* �Ĵ���˵�������Ԥ���Ĵ���6��
   λ����UNION�ṹ:  PMIC_SOFT_RESERE6_UNION */
#define PMIC_SOFT_RESERE6_ADDR(base)              ((base) + (0x1B7))

/* �Ĵ���˵�������Ԥ���Ĵ���7��
   λ����UNION�ṹ:  PMIC_SOFT_RESERE7_UNION */
#define PMIC_SOFT_RESERE7_ADDR(base)              ((base) + (0x1B8))



/****************************************************************************
                     (5/5) HKADC
 ****************************************************************************/
/* �Ĵ���˵����ADC���ƼĴ�����
   λ����UNION�ṹ:  PMIC_ADC_CTRL_UNION */
#define PMIC_ADC_CTRL_ADDR(base)                  ((base) + (0x00))

/* �Ĵ���˵����ADCת����ʼ�Ĵ�����
   λ����UNION�ṹ:  PMIC_ADC_START_UNION */
#define PMIC_ADC_START_ADDR(base)                 ((base) + (0x01))

/* �Ĵ���˵����ADCת��״ָ̬ʾ�Ĵ�����
   λ����UNION�ṹ:  PMIC_CONV_STATUS_UNION */
#define PMIC_CONV_STATUS_ADDR(base)               ((base) + (0x02))

/* �Ĵ���˵����ADC�����λ�Ĵ�����
   λ����UNION�ṹ:  PMIC_ADC_DATA1_UNION */
#define PMIC_ADC_DATA1_ADDR(base)                 ((base) + (0x03))

/* �Ĵ���˵����ADC�����λ�Ĵ�����
   λ����UNION�ṹ:  PMIC_ADC_DATA0_UNION */
#define PMIC_ADC_DATA0_ADDR(base)                 ((base) + (0x04))

/* �Ĵ���˵����ADCת��ʹ�ܼĴ�����
   λ����UNION�ṹ:  PMIC_ADC_CONV_UNION */
#define PMIC_ADC_CONV_ADDR(base)                  ((base) + (0x05))

/* �Ĵ���˵����ADCibas�������üĴ�����
   λ����UNION�ṹ:  PMIC_ADC_CURRENT_UNION */
#define PMIC_ADC_CURRENT_ADDR(base)               ((base) + (0x06))

/* �Ĵ���˵����ADCУ׼���ÿ��ƼĴ�����
   λ����UNION�ṹ:  PMIC_ADC_CALI_CTRL_UNION */
#define PMIC_ADC_CALI_CTRL_ADDR(base)             ((base) + (0x07))

/* �Ĵ���˵����ADCУ׼ֵ�Ĵ�����
   λ����UNION�ṹ:  PMIC_ADC_CALI_VALUE_UNION */
#define PMIC_ADC_CALI_VALUE_ADDR(base)            ((base) + (0x08))

/* �Ĵ���˵����ADCУ׼����ֵ�Ĵ�����
   λ����UNION�ṹ:  PMIC_ADC_CALI_CFG_UNION */
#define PMIC_ADC_CALI_CFG_ADDR(base)              ((base) + (0x09))

/* �Ĵ���˵����HKADCԤ���Ĵ�����
   λ����UNION�ṹ:  PMIC_ADC_RSV0_UNION */
#define PMIC_ADC_RSV0_ADDR(base)                  ((base) + (0x0A))

/* �Ĵ���˵����HKADCԤ���Ĵ�����
   λ����UNION�ṹ:  PMIC_ADC_RSV1_UNION */
#define PMIC_ADC_RSV1_ADDR(base)                  ((base) + (0x0B))





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
                     (1/5) PMU_CTRL
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : PMIC_VERSION0_UNION
 �ṹ˵��  : VERSION0 �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x36�����:8
 �Ĵ���˵��: �汾�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num0 : 8;  /* bit[0-7]: ASIC��36��ʾ��Ŀ���6�� */
    } reg;
} PMIC_VERSION0_UNION;
#endif
#define PMIC_VERSION0_project_num0_START  (0)
#define PMIC_VERSION0_project_num0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_VERSION1_UNION
 �ṹ˵��  : VERSION1 �Ĵ����ṹ���塣��ַƫ����:0x001����ֵ:0x34�����:8
 �Ĵ���˵��: �汾�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num1 : 8;  /* bit[0-7]: ASIC��34��ʾ��Ŀ���4�� */
    } reg;
} PMIC_VERSION1_UNION;
#endif
#define PMIC_VERSION1_project_num1_START  (0)
#define PMIC_VERSION1_project_num1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_VERSION2_UNION
 �ṹ˵��  : VERSION2 �Ĵ����ṹ���塣��ַƫ����:0x002����ֵ:0x32�����:8
 �Ĵ���˵��: �汾�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num2 : 8;  /* bit[0-7]: ASIC��32��ʾ��Ŀ���2�� */
    } reg;
} PMIC_VERSION2_UNION;
#endif
#define PMIC_VERSION2_project_num2_START  (0)
#define PMIC_VERSION2_project_num2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_VERSION3_UNION
 �ṹ˵��  : VERSION3 �Ĵ����ṹ���塣��ַƫ����:0x003����ֵ:0x31�����:8
 �Ĵ���˵��: �汾�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num3 : 8;  /* bit[0-7]: ASIC��31��ʾ��Ŀ���1�� */
    } reg;
} PMIC_VERSION3_UNION;
#endif
#define PMIC_VERSION3_project_num3_START  (0)
#define PMIC_VERSION3_project_num3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_VERSION4_UNION
 �ṹ˵��  : VERSION4 �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x05�����:8
 �Ĵ���˵��: �汾�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  version0 : 8;  /* bit[0-7]: ��ʾ�汾ΪV510��5�� */
    } reg;
} PMIC_VERSION4_UNION;
#endif
#define PMIC_VERSION4_version0_START  (0)
#define PMIC_VERSION4_version0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_VERSION5_UNION
 �ṹ˵��  : VERSION5 �Ĵ����ṹ���塣��ַƫ����:0x005����ֵ:0x00�����:8
 �Ĵ���˵��: �汾�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id : 8;  /* bit[0-7]: ��ʾ�汾ΪV510��10�� */
    } reg;
} PMIC_VERSION5_UNION;
#endif
#define PMIC_VERSION5_chip_id_START  (0)
#define PMIC_VERSION5_chip_id_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_STATUS0_UNION
 �ṹ˵��  : STATUS0 �Ĵ����ṹ���塣��ַƫ����:0x006����ֵ:0x00�����:8
 �Ĵ���˵��: ״̬��־�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vsys_ov_d200ur        : 1;  /* bit[0]: ��ѹ״ָ̬ʾλ(������ȥ��200us)��
                                                              0��VSYS��ѹС��6V��
                                                              1��VSYS��ѹ����6V�� */
        unsigned char  vsys_uv_d10mr         : 1;  /* bit[1]: �͵�ѹ�澯״ָ̬ʾλ(������ȥ��10ms��ʱ�����)��
                                                              0��VSYS��ѹ����3.65V(�ɼĴ�������Ϊ������ѹ��λ)��
                                                              1��VSYS��ѹС��3.65V(�ɼĴ�������Ϊ������ѹ��λ)�� */
        unsigned char  vsys_pwroff_abs       : 1;  /* bit[2]: ���Թػ���ѹ״̬λָʾλ��û��ͬ������
                                                              0��VSYS��ѹ����2.3V��
                                                              1��VSYS��ѹС��2.3V�� */
        unsigned char  vsys_pwroff_deb_d80mr : 1;  /* bit[3]: ȥ���ػ���ѹ״ָ̬ʾλ��������ȥ��80ms��ʱ����䣩��
                                                              0��VSYS����2.6V(�ɼĴ�������Ϊ3.0V)��
                                                              1��VSYSС��2.6V(�ɼĴ�������Ϊ3.0V)��
                                                              ���üĴ����ڷ��µ����� */
        unsigned char  vsys_pwron_d60ur      : 1;  /* bit[4]: ������ѹ״ָ̬ʾλ��������ȥ��60us����
                                                              0��VSYS����2.8V(�ɼĴ�������Ϊ3.2V)��
                                                              1��VSYSС��2.8V(�ɼĴ�������Ϊ3.2V)��
                                                              ���üĴ����ڷ��µ����� */
        unsigned char  thsd_otmp140_d1mr     : 1;  /* bit[5]: ����״̬λ(������ȥ��1ms)��
                                                              0���¶�С��140�棻
                                                              1�� �¶ȴ���140�档 */
        unsigned char  thsd_otmp125_d1mr     : 1;  /* bit[6]: ����״ָ̬ʾλ(������ȥ��1ms)��
                                                              0���¶�С������ֵ��
                                                              1���¶ȴ�������ֵ(��140�ػ�����)��
                                                              �¶�����ֵ�μ�TH_CTRL[thsd_tmp_set]��Ĭ��125�档 */
        unsigned char  pwron_d20m            : 1;  /* bit[7]: ����״ָ̬ʾλ(˫��ȥ��20ms)��
                                                              0������δ�����£�
                                                              1�����������¡� */
    } reg;
} PMIC_STATUS0_UNION;
#endif
#define PMIC_STATUS0_vsys_ov_d200ur_START         (0)
#define PMIC_STATUS0_vsys_ov_d200ur_END           (0)
#define PMIC_STATUS0_vsys_uv_d10mr_START          (1)
#define PMIC_STATUS0_vsys_uv_d10mr_END            (1)
#define PMIC_STATUS0_vsys_pwroff_abs_START        (2)
#define PMIC_STATUS0_vsys_pwroff_abs_END          (2)
#define PMIC_STATUS0_vsys_pwroff_deb_d80mr_START  (3)
#define PMIC_STATUS0_vsys_pwroff_deb_d80mr_END    (3)
#define PMIC_STATUS0_vsys_pwron_d60ur_START       (4)
#define PMIC_STATUS0_vsys_pwron_d60ur_END         (4)
#define PMIC_STATUS0_thsd_otmp140_d1mr_START      (5)
#define PMIC_STATUS0_thsd_otmp140_d1mr_END        (5)
#define PMIC_STATUS0_thsd_otmp125_d1mr_START      (6)
#define PMIC_STATUS0_thsd_otmp125_d1mr_END        (6)
#define PMIC_STATUS0_pwron_d20m_START             (7)
#define PMIC_STATUS0_pwron_d20m_END               (7)


/*****************************************************************************
 �ṹ��    : PMIC_STATUS1_UNION
 �ṹ˵��  : STATUS1 �Ĵ����ṹ���塣��ַƫ����:0x007����ֵ:0x00�����:8
 �Ĵ���˵��: ״̬��־�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dcxo_clk_sel         : 1;  /* bit[0]: DCXOģʽ��ǰ����ʱ��Դ��
                                                             0��32K RC��
                                                             1��19.2MHz 586��Ƶʱ�ӡ� */
        unsigned char  tcxo_clk_sel         : 1;  /* bit[1]: TCXOģʽ��ǰ����ʱ��Դ��
                                                             0��32K RC��
                                                             1��32K Crystal OSC�� */
        unsigned char  xo32k_mode_otp       : 1;  /* bit[2]: XO 32K��Դ 
                                                             0����32K���壻
                                                             1����32K���塣 */
        unsigned char  buck1_vol_sel        : 1;  /* bit[3]: BUCK1�Ŀ�����ѹѡ���źš�
                                                             0��1.2V��
                                                             1��1.1V�� */
        unsigned char  sim0_hpd_d540u       : 1;  /* bit[4]: SIM0_HPD״ָ̬ʾλ(˫��ȥ��540us��ʱ�����)��
                                                             0��SIM0_HPD����͵�ƽ��
                                                             1��SIM0_HPD����ߵ�ƽ�� */
        unsigned char  sim1_hpd_d540u       : 1;  /* bit[5]: SIM1_HPD״ָ̬ʾλ(˫��ȥ��540us��ʱ�����)��
                                                             0��SIM1_HPD����͵�ƽ��
                                                             1��SIM1_HPD����ߵ�ƽ�� */
        unsigned char  alarm_on             : 1;  /* bit[6]: ����״ָ̬ʾλ��
                                                             0��������Ч��
                                                             1�� ������Ч������1s�ߵ�ƽ�� */
        unsigned char  vbus_det_insert_d20m : 1;  /* bit[7]: USB״ָ̬ʾλ(˫��ȥ��20ms)��
                                                             0��USB���ڰγ�״̬��
                                                             1��USB���ڲ���״̬�� */
    } reg;
} PMIC_STATUS1_UNION;
#endif
#define PMIC_STATUS1_dcxo_clk_sel_START          (0)
#define PMIC_STATUS1_dcxo_clk_sel_END            (0)
#define PMIC_STATUS1_tcxo_clk_sel_START          (1)
#define PMIC_STATUS1_tcxo_clk_sel_END            (1)
#define PMIC_STATUS1_xo32k_mode_otp_START        (2)
#define PMIC_STATUS1_xo32k_mode_otp_END          (2)
#define PMIC_STATUS1_buck1_vol_sel_START         (3)
#define PMIC_STATUS1_buck1_vol_sel_END           (3)
#define PMIC_STATUS1_sim0_hpd_d540u_START        (4)
#define PMIC_STATUS1_sim0_hpd_d540u_END          (4)
#define PMIC_STATUS1_sim1_hpd_d540u_START        (5)
#define PMIC_STATUS1_sim1_hpd_d540u_END          (5)
#define PMIC_STATUS1_alarm_on_START              (6)
#define PMIC_STATUS1_alarm_on_END                (6)
#define PMIC_STATUS1_vbus_det_insert_d20m_START  (7)
#define PMIC_STATUS1_vbus_det_insert_d20m_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_D2A_RES0_UNION
 �ṹ˵��  : D2A_RES0 �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00�����:8
 �Ĵ���˵��: ��ģ�ӿڱ����Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold_0_3 : 4;  /* bit[0-3]: xo_cali_thresold[3:0]ӳ��Ĵ��� */
        unsigned char  d2a_reserve0         : 4;  /* bit[4-7]: ���ֵ�ģ��ı����źš� */
    } reg;
} PMIC_D2A_RES0_UNION;
#endif
#define PMIC_D2A_RES0_xo_cali_thresold_0_3_START  (0)
#define PMIC_D2A_RES0_xo_cali_thresold_0_3_END    (3)
#define PMIC_D2A_RES0_d2a_reserve0_START          (4)
#define PMIC_D2A_RES0_d2a_reserve0_END            (7)


/*****************************************************************************
 �ṹ��    : PMIC_D2A_RES1_UNION
 �ṹ˵��  : D2A_RES1 �Ĵ����ṹ���塣��ַƫ����:0x009����ֵ:0x00�����:8
 �Ĵ���˵��: ��ģ�ӿڱ����Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold_4_7 : 4;  /* bit[0-3]: xo_cali_thresold[7:4]ӳ��Ĵ��� */
        unsigned char  d2a_reserve1         : 4;  /* bit[4-7]: ���ֵ�ģ��ı����źš� */
    } reg;
} PMIC_D2A_RES1_UNION;
#endif
#define PMIC_D2A_RES1_xo_cali_thresold_4_7_START  (0)
#define PMIC_D2A_RES1_xo_cali_thresold_4_7_END    (3)
#define PMIC_D2A_RES1_d2a_reserve1_START          (4)
#define PMIC_D2A_RES1_d2a_reserve1_END            (7)


/*****************************************************************************
 �ṹ��    : PMIC_D2A_RES2_UNION
 �ṹ˵��  : D2A_RES2 �Ĵ����ṹ���塣��ַƫ����:0x00A����ֵ:0x00�����:8
 �Ĵ���˵��: xo_cali_thresold[15:8]ӳ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold_8_15 : 8;  /* bit[0-7]: xo_cali_thresold[15:8]ӳ��Ĵ��� */
    } reg;
} PMIC_D2A_RES2_UNION;
#endif
#define PMIC_D2A_RES2_xo_cali_thresold_8_15_START  (0)
#define PMIC_D2A_RES2_xo_cali_thresold_8_15_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_A2D_RES0_UNION
 �ṹ˵��  : A2D_RES0 �Ĵ����ṹ���塣��ַƫ����:0x00B����ֵ:0x00�����:8
 �Ĵ���˵��: ��ģ�ӿڱ����Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_19m2_sel     : 1;  /* bit[0]  : XO 19.2M��Դ��
                                                          0��38.4M���壻
                                                          1��19.2M���� */
        unsigned char  xo_19m2_abnor_n : 1;  /* bit[1]  : XO 19.2Mʱ���쳣ָʾ�źš�
                                                          0��19.2M�쳣(19.2Mʱ����ʧ)��
                                                          1: 19.2Mʱ�������� */
        unsigned char  a2d_reserve0    : 6;  /* bit[2-7]: ģ�⵽���ֵı����źš� */
    } reg;
} PMIC_A2D_RES0_UNION;
#endif
#define PMIC_A2D_RES0_xo_19m2_sel_START      (0)
#define PMIC_A2D_RES0_xo_19m2_sel_END        (0)
#define PMIC_A2D_RES0_xo_19m2_abnor_n_START  (1)
#define PMIC_A2D_RES0_xo_19m2_abnor_n_END    (1)
#define PMIC_A2D_RES0_a2d_reserve0_START     (2)
#define PMIC_A2D_RES0_a2d_reserve0_END       (7)


/*****************************************************************************
 �ṹ��    : PMIC_A2D_RES1_UNION
 �ṹ˵��  : A2D_RES1 �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00�����:8
 �Ĵ���˵��: ��ģ�ӿڱ����Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  a2d_reserve1 : 8;  /* bit[0-7]: ģ�⵽���ֵı����źš� */
    } reg;
} PMIC_A2D_RES1_UNION;
#endif
#define PMIC_A2D_RES1_a2d_reserve1_START  (0)
#define PMIC_A2D_RES1_a2d_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL0_UNION
 �ṹ˵��  : BUCK0_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x00D����ֵ:0x83�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_adj_clx : 4;  /* bit[0-3]: bit[3]������DMDʱ���رղ��ֹ��ʹܡ�
                                                        0�����رգ�
                                                        1���رա�
                                                        bit[2��0]��LX�����˲����ݵ��ڡ�
                                                        000��10pF��
                                                        001��20pF��
                                                        010��30pF��
                                                        011��40pF��
                                                        100��30pF��
                                                        101��40pF��
                                                        110��50pF��
                                                        111��60pF�� */
        unsigned char  buck0_adj_rlx : 4;  /* bit[4-7]: BUCK0 LX�����˲�������ڡ�
                                                        0000��3.4M����
                                                        0001��3.2M����
                                                        0010��2.8M����
                                                        0011��2.6M����
                                                        0100��2.4M����
                                                        0101��2.2M����
                                                        0110��2.0M����
                                                        0111��1.8M����
                                                        1000��1.6M����
                                                        1001��1.4M����
                                                        1010��1.2M����
                                                        1011��1.0M����
                                                        1100��0.8M����
                                                        1101��0.6M����
                                                        1110��0.4M����
                                                        1111��0.2M���� */
    } reg;
} PMIC_BUCK0_CTRL0_UNION;
#endif
#define PMIC_BUCK0_CTRL0_buck0_adj_clx_START  (0)
#define PMIC_BUCK0_CTRL0_buck0_adj_clx_END    (3)
#define PMIC_BUCK0_CTRL0_buck0_adj_rlx_START  (4)
#define PMIC_BUCK0_CTRL0_buck0_adj_rlx_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL1_UNION
 �ṹ˵��  : BUCK0_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x00E����ֵ:0x40�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_ng_dt_sel : 1;  /* bit[0]  : BUCK0 P�ܵ�N������ģʽѡ��
                                                          0������������������ģʽ��
                                                          1����������������ģʽ�� */
        unsigned char  buck0_pg_dt_sel : 1;  /* bit[1]  : BUCK0 N�ܵ�P������ģʽѡ��
                                                          0������������������ģʽ��
                                                          1����������������ģʽ�� */
        unsigned char  buck0_sft_sel   : 1;  /* bit[2]  : BUCK0��������ʽѡ��
                                                          0��������ʱ��Ϊ200��s���ң�
                                                          1��������ʱ��Ϊ100��s���ҡ� */
        unsigned char  reserved        : 1;  /* bit[3]  : ������ */
        unsigned char  buck0_dt_sel    : 2;  /* bit[4-5]: ����ʱ����ڡ�
                                                          0���������ӳ�5ns��
                                                          1�������ӳ�5ns�� */
        unsigned char  buck0_ocp_sel   : 2;  /* bit[6-7]: BUCK0 OCP�������
                                                          00��3.24A��
                                                          01��3.69A��
                                                          10��4.13A��
                                                          11��4.57A�� */
    } reg;
} PMIC_BUCK0_CTRL1_UNION;
#endif
#define PMIC_BUCK0_CTRL1_buck0_ng_dt_sel_START  (0)
#define PMIC_BUCK0_CTRL1_buck0_ng_dt_sel_END    (0)
#define PMIC_BUCK0_CTRL1_buck0_pg_dt_sel_START  (1)
#define PMIC_BUCK0_CTRL1_buck0_pg_dt_sel_END    (1)
#define PMIC_BUCK0_CTRL1_buck0_sft_sel_START    (2)
#define PMIC_BUCK0_CTRL1_buck0_sft_sel_END      (2)
#define PMIC_BUCK0_CTRL1_buck0_dt_sel_START     (4)
#define PMIC_BUCK0_CTRL1_buck0_dt_sel_END       (5)
#define PMIC_BUCK0_CTRL1_buck0_ocp_sel_START    (6)
#define PMIC_BUCK0_CTRL1_buck0_ocp_sel_END      (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL2_UNION
 �ṹ˵��  : BUCK0_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x00F����ֵ:0x3C�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_ng_n_sel : 2;  /* bit[0-1]: BUCK0 N power��������ӦNMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
        unsigned char  buck0_ng_p_sel : 2;  /* bit[2-3]: BUCK0 N power��������ӦPMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck0_pg_n_sel : 2;  /* bit[4-5]: BUCK0 P power��������ӦNMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck0_pg_p_sel : 2;  /* bit[6-7]: BUCK0 P power��������ӦPMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
    } reg;
} PMIC_BUCK0_CTRL2_UNION;
#endif
#define PMIC_BUCK0_CTRL2_buck0_ng_n_sel_START  (0)
#define PMIC_BUCK0_CTRL2_buck0_ng_n_sel_END    (1)
#define PMIC_BUCK0_CTRL2_buck0_ng_p_sel_START  (2)
#define PMIC_BUCK0_CTRL2_buck0_ng_p_sel_END    (3)
#define PMIC_BUCK0_CTRL2_buck0_pg_n_sel_START  (4)
#define PMIC_BUCK0_CTRL2_buck0_pg_n_sel_END    (5)
#define PMIC_BUCK0_CTRL2_buck0_pg_p_sel_START  (6)
#define PMIC_BUCK0_CTRL2_buck0_pg_p_sel_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL3_UNION
 �ṹ˵��  : BUCK0_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x20�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_reg_r  : 2;  /* bit[0-1]: BUCK0�ڲ�regulator���裬���ڵ���regulator����
                                                       00��2.8kHz��
                                                       01��45kHz��
                                                       10��85kHz��
                                                       11��152kHz�� */
        unsigned char  reserved     : 2;  /* bit[2-3]: ������ */
        unsigned char  buck0_reg_en : 1;  /* bit[4]  : BUCK0�ڲ����ȵ�����ʹ���źš�
                                                       0��ʹ�ܣ�
                                                       1����ʹ�ܡ� */
        unsigned char  buck0_dbias  : 2;  /* bit[5-6]: BUCK0�Ƚ���ƫ�õ������ڡ�
                                                       00��2uA��
                                                       01��1uA��
                                                       10��4uA��
                                                       11��3uA�� */
        unsigned char  buck0_ocp_d  : 1;  /* bit[7]  : BUCK0 �ڲ�OCP��·�����źš�
                                                       0�������Σ�
                                                       1�����Ρ� */
    } reg;
} PMIC_BUCK0_CTRL3_UNION;
#endif
#define PMIC_BUCK0_CTRL3_buck0_reg_r_START   (0)
#define PMIC_BUCK0_CTRL3_buck0_reg_r_END     (1)
#define PMIC_BUCK0_CTRL3_buck0_reg_en_START  (4)
#define PMIC_BUCK0_CTRL3_buck0_reg_en_END    (4)
#define PMIC_BUCK0_CTRL3_buck0_dbias_START   (5)
#define PMIC_BUCK0_CTRL3_buck0_dbias_END     (6)
#define PMIC_BUCK0_CTRL3_buck0_ocp_d_START   (7)
#define PMIC_BUCK0_CTRL3_buck0_ocp_d_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL4_UNION
 �ṹ˵��  : BUCK0_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x011����ֵ:0x20�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_short_pdp : 1;  /* bit[0]  : ��·�������μĴ�����
                                                          0��ʹ�ܶ�·������0.4V���ޣ�
                                                          1����ʹ�ܶ�·������0V���ޡ� */
        unsigned char  buck0_reg_ss_d  : 1;  /* bit[1]  : BUCK0������ʱ�ڲ�regulator״̬��
                                                          0������״̬��
                                                          1����λ���淴���� */
        unsigned char  buck0_regop_c   : 1;  /* bit[2]  : BUCK0�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate��
                                                          0��slew-rate����
                                                          1��slew-rate�졣 */
        unsigned char  buck0_reg_idr   : 2;  /* bit[3-4]: BUCK0�ڲ�regulator���������ڵ���regulator�������ȷ�Χ��
                                                          00��4uA��
                                                          01��6uA��
                                                          10��8uA��
                                                          11��10uA�� */
        unsigned char  buck0_reg_dr    : 3;  /* bit[5-7]: BUCK0�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ��
                                                          000��+/-6mV��
                                                          001��+/-12mV��
                                                          010��+/-18mV��
                                                          011��+/-24mV��
                                                          100��+/-30mV��
                                                          101��+/-36mV��
                                                          110��+/-42mV��
                                                          111��+/-48mV�� */
    } reg;
} PMIC_BUCK0_CTRL4_UNION;
#endif
#define PMIC_BUCK0_CTRL4_buck0_short_pdp_START  (0)
#define PMIC_BUCK0_CTRL4_buck0_short_pdp_END    (0)
#define PMIC_BUCK0_CTRL4_buck0_reg_ss_d_START   (1)
#define PMIC_BUCK0_CTRL4_buck0_reg_ss_d_END     (1)
#define PMIC_BUCK0_CTRL4_buck0_regop_c_START    (2)
#define PMIC_BUCK0_CTRL4_buck0_regop_c_END      (2)
#define PMIC_BUCK0_CTRL4_buck0_reg_idr_START    (3)
#define PMIC_BUCK0_CTRL4_buck0_reg_idr_END      (4)
#define PMIC_BUCK0_CTRL4_buck0_reg_dr_START     (5)
#define PMIC_BUCK0_CTRL4_buck0_reg_dr_END       (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL5_UNION
 �ṹ˵��  : BUCK0_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x012����ֵ:0x04�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_ton      : 2;  /* bit[0-1]: BUCK0��С��ͨʱ�䡣
                                                         00��100ns��
                                                         01��200ns��
                                                         10��300ns��
                                                         11��400ns�� */
        unsigned char  buck0_nmos_off : 1;  /* bit[2]  : BUCK0���ڹر�NMOS power�ܡ�
                                                         0��ǿ�ƹرգ�
                                                         1����ǿ�ƹرա� */
        unsigned char  buck0_reg_c    : 1;  /* bit[3]  : BUCK0�ڲ�regulator���ݣ����ڵ���regulator����
                                                         0������С��
                                                         1�����ݴ� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_BUCK0_CTRL5_UNION;
#endif
#define PMIC_BUCK0_CTRL5_buck0_ton_START       (0)
#define PMIC_BUCK0_CTRL5_buck0_ton_END         (1)
#define PMIC_BUCK0_CTRL5_buck0_nmos_off_START  (2)
#define PMIC_BUCK0_CTRL5_buck0_nmos_off_END    (2)
#define PMIC_BUCK0_CTRL5_buck0_reg_c_START     (3)
#define PMIC_BUCK0_CTRL5_buck0_reg_c_END       (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL6_UNION
 �ṹ˵��  : BUCK0_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x013����ֵ:0x41�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_shield_i    : 2;  /* bit[0-1]: DMD�����źŶ�Ӧ�������ڡ�
                                                            00��0.84A��
                                                            01��1.25A��
                                                            10��1.66A��
                                                            11��2.07A�� */
        unsigned char  buck0_new_dmd_sel : 5;  /* bit[2-6]: bit[6] DMDƫ�õ���ѡ��
                                                            0��2uA��
                                                            1��1uA��
                                                            bit[5] DMD��ʽѡ��
                                                            0����DMD��
                                                            1����DMD��
                                                            bit[4��2] ��DMD�ṹDMD�������ڡ�
                                                            000��28mA��
                                                            001��-75mA��
                                                            010��-40mA��
                                                            011��-12mA��
                                                            100��70mA��
                                                            101��120mA��
                                                            110��162mA��
                                                            111��205mA�� */
        unsigned char  reserved          : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_BUCK0_CTRL6_UNION;
#endif
#define PMIC_BUCK0_CTRL6_buck0_shield_i_START     (0)
#define PMIC_BUCK0_CTRL6_buck0_shield_i_END       (1)
#define PMIC_BUCK0_CTRL6_buck0_new_dmd_sel_START  (2)
#define PMIC_BUCK0_CTRL6_buck0_new_dmd_sel_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL7_UNION
 �ṹ˵��  : BUCK0_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x1B�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_dmd_sel : 3;  /* bit[0-2]: BUCK0 ��DMD�ṹDMD�������ڡ�
                                                        000��-45mA��
                                                        001��-5mA��
                                                        010��27mA��
                                                        011��70mA��
                                                        100��105mA��
                                                        101��144mA��
                                                        110��185mA��
                                                        111��228mA�� */
        unsigned char  buck0_mos_sel : 2;  /* bit[3-4]: BUCK0 �Ƚ����ڲ��������ڡ�
                                                        00������0uA��
                                                        01������1uA��
                                                        10������2uA��
                                                        11������3uA�� */
        unsigned char  reserved      : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_BUCK0_CTRL7_UNION;
#endif
#define PMIC_BUCK0_CTRL7_buck0_dmd_sel_START  (0)
#define PMIC_BUCK0_CTRL7_buck0_dmd_sel_END    (2)
#define PMIC_BUCK0_CTRL7_buck0_mos_sel_START  (3)
#define PMIC_BUCK0_CTRL7_buck0_mos_sel_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL8_UNION
 �ṹ˵��  : BUCK0_CTRL8 �Ĵ����ṹ���塣��ַƫ����:0x015����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_reserve0 : 8;  /* bit[0-7]: BUCK0���üĴ����� */
    } reg;
} PMIC_BUCK0_CTRL8_UNION;
#endif
#define PMIC_BUCK0_CTRL8_buck0_reserve0_START  (0)
#define PMIC_BUCK0_CTRL8_buck0_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL9_UNION
 �ṹ˵��  : BUCK0_CTRL9 �Ĵ����ṹ���塣��ַƫ����:0x016����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���9��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_reserve1 : 8;  /* bit[0-7]: BUCK0���üĴ����� */
    } reg;
} PMIC_BUCK0_CTRL9_UNION;
#endif
#define PMIC_BUCK0_CTRL9_buck0_reserve1_START  (0)
#define PMIC_BUCK0_CTRL9_buck0_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL10_UNION
 �ṹ˵��  : BUCK0_CTRL10 �Ĵ����ṹ���塣��ַƫ����:0x017����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���10��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_reserve2 : 8;  /* bit[0-7]: BUCK0���üĴ����� */
    } reg;
} PMIC_BUCK0_CTRL10_UNION;
#endif
#define PMIC_BUCK0_CTRL10_buck0_reserve2_START  (0)
#define PMIC_BUCK0_CTRL10_buck0_reserve2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_CTRL11_UNION
 �ṹ˵��  : BUCK0_CTRL11 �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK0���ƼĴ���11��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_pdn_lx_det     : 1;  /* bit[0]: BUCK0 �Ƚ�����ǿ����ѡ��
                                                             0�������ӳ�������
                                                             1�����ӳ������� */
        unsigned char  buck0_eco_dmd        : 1;  /* bit[1]: ������ģʽ��ǿ��NMOS�ܹرա�
                                                             0����ǿ�ƣ�
                                                             1��ǿ�ơ� */
        unsigned char  buck0_dmd_shield_n   : 1;  /* bit[2]: �������DMD�����źš�
                                                             0�����Σ�
                                                             1�������Ρ� */
        unsigned char  buck0_ocp_delay_sel  : 1;  /* bit[3]: OCP����ʱ���ӳ�15ns�źš�
                                                             0�����ӳ���
                                                             1���ӳ��� */
        unsigned char  buck0_dmd_clamp      : 1;  /* bit[4]: ��DMDǶλʹ���źš�
                                                             0�����ϣ�
                                                             1�������ϡ� */
        unsigned char  buck0_en_regop_clamp : 1;  /* bit[5]: regulator Ƕλ��·ʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned char  buck0_en_ss_sel      : 1;  /* bit[6]: ѡ����������źš�
                                                             0��ģ�������
                                                             1�����ָ����� */
        unsigned char  reserved             : 1;  /* bit[7]: ������ */
    } reg;
} PMIC_BUCK0_CTRL11_UNION;
#endif
#define PMIC_BUCK0_CTRL11_buck0_pdn_lx_det_START      (0)
#define PMIC_BUCK0_CTRL11_buck0_pdn_lx_det_END        (0)
#define PMIC_BUCK0_CTRL11_buck0_eco_dmd_START         (1)
#define PMIC_BUCK0_CTRL11_buck0_eco_dmd_END           (1)
#define PMIC_BUCK0_CTRL11_buck0_dmd_shield_n_START    (2)
#define PMIC_BUCK0_CTRL11_buck0_dmd_shield_n_END      (2)
#define PMIC_BUCK0_CTRL11_buck0_ocp_delay_sel_START   (3)
#define PMIC_BUCK0_CTRL11_buck0_ocp_delay_sel_END     (3)
#define PMIC_BUCK0_CTRL11_buck0_dmd_clamp_START       (4)
#define PMIC_BUCK0_CTRL11_buck0_dmd_clamp_END         (4)
#define PMIC_BUCK0_CTRL11_buck0_en_regop_clamp_START  (5)
#define PMIC_BUCK0_CTRL11_buck0_en_regop_clamp_END    (5)
#define PMIC_BUCK0_CTRL11_buck0_en_ss_sel_START       (6)
#define PMIC_BUCK0_CTRL11_buck0_en_ss_sel_END         (6)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL0_UNION
 �ṹ˵��  : BUCK1_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x019����ֵ:0x83�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_adj_clx : 4;  /* bit[0-3]: bit[3]������DMDʱ���رղ��ֹ��ʹܡ�
                                                        0�����رգ�
                                                        1���رա�
                                                        bit[2:0]��LX�����˲����ݵ��ڡ�
                                                        000��10pF��
                                                        001��20pF��
                                                        010��30pF��
                                                        011��40pF��
                                                        100��30pF��
                                                        101��40pF��
                                                        110��50pF��
                                                        111��60pF�� */
        unsigned char  buck1_adj_rlx : 4;  /* bit[4-7]: BUCK1 LX�����˲�������ڡ�
                                                        0000��3.4M����
                                                        0001��3.2M����
                                                        0010��2.8M����
                                                        0011��2.6M����
                                                        0100��2.4M����
                                                        0101��2.2M����
                                                        0110��2.0M����
                                                        0111��1.8M����
                                                        1000��1.6M����
                                                        1001��1.4M����
                                                        1010��1.2M����
                                                        1011��1.0M����
                                                        1100��0.8M����
                                                        1101��0.6M����
                                                        1110��0.4M����
                                                        1111��0.2M���� */
    } reg;
} PMIC_BUCK1_CTRL0_UNION;
#endif
#define PMIC_BUCK1_CTRL0_buck1_adj_clx_START  (0)
#define PMIC_BUCK1_CTRL0_buck1_adj_clx_END    (3)
#define PMIC_BUCK1_CTRL0_buck1_adj_rlx_START  (4)
#define PMIC_BUCK1_CTRL0_buck1_adj_rlx_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL1_UNION
 �ṹ˵��  : BUCK1_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x01A����ֵ:0x40�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_ng_dt_sel : 1;  /* bit[0]  : BUCK1 P�ܵ�N������ģʽѡ��
                                                          0������������������ģʽ��
                                                          1����������������ģʽ�� */
        unsigned char  buck1_pg_dt_sel : 1;  /* bit[1]  : BUCK1 N�ܵ�P������ģʽѡ��
                                                          0������������������ģʽ��
                                                          1����������������ģʽ�� */
        unsigned char  buck1_sft_sel   : 1;  /* bit[2]  : BUCK1��������ʽѡ��
                                                          0��������ʱ��Ϊ200��s���ң�
                                                          1��������ʱ��Ϊ100��s���ҡ� */
        unsigned char  reserved        : 1;  /* bit[3]  : ������ */
        unsigned char  buck1_dt_sel    : 2;  /* bit[4-5]: ����ʱ����ڡ�
                                                          0���������ӳ�5ns��
                                                          1�������ӳ�5ns�� */
        unsigned char  buck1_ocp_sel   : 2;  /* bit[6-7]: BUCK1 OCP�������
                                                          00��3.70A��
                                                          01��4.14A��
                                                          10��4.59A��
                                                          11��5.03A�� */
    } reg;
} PMIC_BUCK1_CTRL1_UNION;
#endif
#define PMIC_BUCK1_CTRL1_buck1_ng_dt_sel_START  (0)
#define PMIC_BUCK1_CTRL1_buck1_ng_dt_sel_END    (0)
#define PMIC_BUCK1_CTRL1_buck1_pg_dt_sel_START  (1)
#define PMIC_BUCK1_CTRL1_buck1_pg_dt_sel_END    (1)
#define PMIC_BUCK1_CTRL1_buck1_sft_sel_START    (2)
#define PMIC_BUCK1_CTRL1_buck1_sft_sel_END      (2)
#define PMIC_BUCK1_CTRL1_buck1_dt_sel_START     (4)
#define PMIC_BUCK1_CTRL1_buck1_dt_sel_END       (5)
#define PMIC_BUCK1_CTRL1_buck1_ocp_sel_START    (6)
#define PMIC_BUCK1_CTRL1_buck1_ocp_sel_END      (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL2_UNION
 �ṹ˵��  : BUCK1_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x01B����ֵ:0x3C�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_ng_n_sel : 2;  /* bit[0-1]: BUCK1 N power��������ӦNMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
        unsigned char  buck1_ng_p_sel : 2;  /* bit[2-3]: BUCK1 N power��������ӦPMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck1_pg_n_sel : 2;  /* bit[4-5]: BUCK1 P power��������ӦNMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck1_pg_p_sel : 2;  /* bit[6-7]: BUCK1 P power��������ӦPMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
    } reg;
} PMIC_BUCK1_CTRL2_UNION;
#endif
#define PMIC_BUCK1_CTRL2_buck1_ng_n_sel_START  (0)
#define PMIC_BUCK1_CTRL2_buck1_ng_n_sel_END    (1)
#define PMIC_BUCK1_CTRL2_buck1_ng_p_sel_START  (2)
#define PMIC_BUCK1_CTRL2_buck1_ng_p_sel_END    (3)
#define PMIC_BUCK1_CTRL2_buck1_pg_n_sel_START  (4)
#define PMIC_BUCK1_CTRL2_buck1_pg_n_sel_END    (5)
#define PMIC_BUCK1_CTRL2_buck1_pg_p_sel_START  (6)
#define PMIC_BUCK1_CTRL2_buck1_pg_p_sel_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL3_UNION
 �ṹ˵��  : BUCK1_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x20�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_reg_r  : 2;  /* bit[0-1]: BUCK1�ڲ�regulator���裬���ڵ���regulator����
                                                       00��2.8kHz��
                                                       01��45kHz��
                                                       10��85kHz��
                                                       11��152kHz�� */
        unsigned char  reserved     : 2;  /* bit[2-3]: ������ */
        unsigned char  buck1_reg_en : 1;  /* bit[4]  : BUCK1�ڲ����ȵ�����ʹ���źš�
                                                       0��ʹ�ܣ�
                                                       1����ʹ�ܡ� */
        unsigned char  buck1_dbias  : 2;  /* bit[5-6]: BUCK1�Ƚ���ƫ�õ������ڡ�
                                                       00��2uA��
                                                       01��1uA��
                                                       10��4uA��
                                                       11��3uA�� */
        unsigned char  buck1_ocp_d  : 1;  /* bit[7]  : BUCK1 �ڲ�OCP��·�����źš�
                                                       0�������Σ�
                                                       1�����Ρ� */
    } reg;
} PMIC_BUCK1_CTRL3_UNION;
#endif
#define PMIC_BUCK1_CTRL3_buck1_reg_r_START   (0)
#define PMIC_BUCK1_CTRL3_buck1_reg_r_END     (1)
#define PMIC_BUCK1_CTRL3_buck1_reg_en_START  (4)
#define PMIC_BUCK1_CTRL3_buck1_reg_en_END    (4)
#define PMIC_BUCK1_CTRL3_buck1_dbias_START   (5)
#define PMIC_BUCK1_CTRL3_buck1_dbias_END     (6)
#define PMIC_BUCK1_CTRL3_buck1_ocp_d_START   (7)
#define PMIC_BUCK1_CTRL3_buck1_ocp_d_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL4_UNION
 �ṹ˵��  : BUCK1_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x01D����ֵ:0x20�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_short_pdp : 1;  /* bit[0]  : ��·�������μĴ�����
                                                          0��ʹ�ܶ�·������0.4V���ޣ�
                                                          1����ʹ�ܶ�·������0V���ޡ� */
        unsigned char  buck1_reg_ss_d  : 1;  /* bit[1]  : BUCK1������ʱ�ڲ�regulator״̬��
                                                          0������״̬��
                                                          1����λ���淴���� */
        unsigned char  buck1_regop_c   : 1;  /* bit[2]  : BUCK1�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate��
                                                          0��slew-rate����
                                                          1��slew-rate�졣 */
        unsigned char  buck1_reg_idr   : 2;  /* bit[3-4]: BUCK1�ڲ�regulator���������ڵ���regulator�������ȷ�Χ��
                                                          00��4uA��
                                                          01��6uA��
                                                          10��8uA��
                                                          11��10uA�� */
        unsigned char  buck1_reg_dr    : 3;  /* bit[5-7]: BUCK1�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ��
                                                          000��+/-6mV��
                                                          001��+/-12mV��
                                                          010��+/-18mV��
                                                          011��+/-24mV��
                                                          100��+/-30mV��
                                                          101��+/-36mV��
                                                          110��+/-42mV��
                                                          111��+/-48mV�� */
    } reg;
} PMIC_BUCK1_CTRL4_UNION;
#endif
#define PMIC_BUCK1_CTRL4_buck1_short_pdp_START  (0)
#define PMIC_BUCK1_CTRL4_buck1_short_pdp_END    (0)
#define PMIC_BUCK1_CTRL4_buck1_reg_ss_d_START   (1)
#define PMIC_BUCK1_CTRL4_buck1_reg_ss_d_END     (1)
#define PMIC_BUCK1_CTRL4_buck1_regop_c_START    (2)
#define PMIC_BUCK1_CTRL4_buck1_regop_c_END      (2)
#define PMIC_BUCK1_CTRL4_buck1_reg_idr_START    (3)
#define PMIC_BUCK1_CTRL4_buck1_reg_idr_END      (4)
#define PMIC_BUCK1_CTRL4_buck1_reg_dr_START     (5)
#define PMIC_BUCK1_CTRL4_buck1_reg_dr_END       (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL5_UNION
 �ṹ˵��  : BUCK1_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x01E����ֵ:0x04�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_ton      : 2;  /* bit[0-1]: BUCK1��С��ͨʱ�䡣
                                                         00��100ns��
                                                         01��200ns��
                                                         10��300ns��
                                                         11��400ns�� */
        unsigned char  buck1_nmos_off : 1;  /* bit[2]  : BUCK1���ڹر�NMOS power�ܡ�
                                                         0��ǿ�ƹرգ�
                                                         1����ǿ�ƹرա� */
        unsigned char  buck1_reg_c    : 1;  /* bit[3]  : BUCK1�ڲ�regulator���ݣ����ڵ���regulator����
                                                         0������С��
                                                         1�����ݴ� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_BUCK1_CTRL5_UNION;
#endif
#define PMIC_BUCK1_CTRL5_buck1_ton_START       (0)
#define PMIC_BUCK1_CTRL5_buck1_ton_END         (1)
#define PMIC_BUCK1_CTRL5_buck1_nmos_off_START  (2)
#define PMIC_BUCK1_CTRL5_buck1_nmos_off_END    (2)
#define PMIC_BUCK1_CTRL5_buck1_reg_c_START     (3)
#define PMIC_BUCK1_CTRL5_buck1_reg_c_END       (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL6_UNION
 �ṹ˵��  : BUCK1_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x01F����ֵ:0x41�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_shield_i    : 2;  /* bit[0-1]: DMD�����źŶ�Ӧ�������ڡ�
                                                            00��0.84A��
                                                            01��1.25A��
                                                            10��1.66A��
                                                            11��2.07A�� */
        unsigned char  buck1_new_dmd_sel : 5;  /* bit[2-6]: bit[6] DMDƫ�õ���ѡ��
                                                            0��2uA��
                                                            1��1uA��
                                                            bit[3] DMD��ʽѡ��
                                                            0����DMD��
                                                            1����DMD��
                                                            bit[4:2] ��DMD�ṹDMD�������ڡ�
                                                            000��28mA��
                                                            001��-70mA��
                                                            010��-40mA��
                                                            011��-12mA��
                                                            100��70mA��
                                                            101��120mA��
                                                            110��162mA��
                                                            111��205mA�� */
        unsigned char  reserved          : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_BUCK1_CTRL6_UNION;
#endif
#define PMIC_BUCK1_CTRL6_buck1_shield_i_START     (0)
#define PMIC_BUCK1_CTRL6_buck1_shield_i_END       (1)
#define PMIC_BUCK1_CTRL6_buck1_new_dmd_sel_START  (2)
#define PMIC_BUCK1_CTRL6_buck1_new_dmd_sel_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL7_UNION
 �ṹ˵��  : BUCK1_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x1B�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_dmd_sel : 3;  /* bit[0-2]: BUCK1 ��DMD�ṹDMD�������ڡ�
                                                        000��-60mA��
                                                        001��-24mA��
                                                        010��12mA��
                                                        011��50mA��
                                                        100��92mA��
                                                        101��132mA��
                                                        110��173mA��
                                                        111��214mA�� */
        unsigned char  buck1_mos_sel : 2;  /* bit[3-4]: BUCK1 �Ƚ����ڲ��������ڡ�
                                                        00������0uA��
                                                        01������1uA��
                                                        10������2uA��
                                                        11������3uA�� */
        unsigned char  reserved      : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_BUCK1_CTRL7_UNION;
#endif
#define PMIC_BUCK1_CTRL7_buck1_dmd_sel_START  (0)
#define PMIC_BUCK1_CTRL7_buck1_dmd_sel_END    (2)
#define PMIC_BUCK1_CTRL7_buck1_mos_sel_START  (3)
#define PMIC_BUCK1_CTRL7_buck1_mos_sel_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL8_UNION
 �ṹ˵��  : BUCK1_CTRL8 �Ĵ����ṹ���塣��ַƫ����:0x021����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_reserve0 : 8;  /* bit[0-7]: BUCK1���üĴ����� */
    } reg;
} PMIC_BUCK1_CTRL8_UNION;
#endif
#define PMIC_BUCK1_CTRL8_buck1_reserve0_START  (0)
#define PMIC_BUCK1_CTRL8_buck1_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL9_UNION
 �ṹ˵��  : BUCK1_CTRL9 �Ĵ����ṹ���塣��ַƫ����:0x022����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���9��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_reserve1 : 8;  /* bit[0-7]: BUCK1���üĴ����� */
    } reg;
} PMIC_BUCK1_CTRL9_UNION;
#endif
#define PMIC_BUCK1_CTRL9_buck1_reserve1_START  (0)
#define PMIC_BUCK1_CTRL9_buck1_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL10_UNION
 �ṹ˵��  : BUCK1_CTRL10 �Ĵ����ṹ���塣��ַƫ����:0x023����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���10��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_reserve2 : 8;  /* bit[0-7]: BUCK1���üĴ����� */
    } reg;
} PMIC_BUCK1_CTRL10_UNION;
#endif
#define PMIC_BUCK1_CTRL10_buck1_reserve2_START  (0)
#define PMIC_BUCK1_CTRL10_buck1_reserve2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_CTRL11_UNION
 �ṹ˵��  : BUCK1_CTRL11 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK1���ƼĴ���11��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_pdn_lx_det     : 1;  /* bit[0]: BUCK1 �Ƚ�����ǿ����ѡ��
                                                             0�������ӳ�������
                                                             1�����ӳ������� */
        unsigned char  buck1_eco_dmd        : 1;  /* bit[1]: ������ģʽ��ǿ��NMOS�ܹرա�
                                                             0����ǿ�ƣ�
                                                             1��ǿ�ơ� */
        unsigned char  buck1_dmd_shield_n   : 1;  /* bit[2]: �������DMD�����źš�
                                                             0�����Σ�
                                                             1�������Ρ� */
        unsigned char  buck1_ocp_delay_sel  : 1;  /* bit[3]: OCP����ʱ���ӳ�15ns�źš�
                                                             0�����ӳ���
                                                             1���ӳ��� */
        unsigned char  buck1_dmd_clamp      : 1;  /* bit[4]: ��DMDǶλʹ���źš�
                                                             0�����ϣ�
                                                             1�������ϡ� */
        unsigned char  buck1_en_regop_clamp : 1;  /* bit[5]: regulator Ƕλ��·ʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned char  buck1_en_ss_sel      : 1;  /* bit[6]: ѡ����������źš�
                                                             0��ģ�������
                                                             1�����ָ����� */
        unsigned char  reserved             : 1;  /* bit[7]: ������ */
    } reg;
} PMIC_BUCK1_CTRL11_UNION;
#endif
#define PMIC_BUCK1_CTRL11_buck1_pdn_lx_det_START      (0)
#define PMIC_BUCK1_CTRL11_buck1_pdn_lx_det_END        (0)
#define PMIC_BUCK1_CTRL11_buck1_eco_dmd_START         (1)
#define PMIC_BUCK1_CTRL11_buck1_eco_dmd_END           (1)
#define PMIC_BUCK1_CTRL11_buck1_dmd_shield_n_START    (2)
#define PMIC_BUCK1_CTRL11_buck1_dmd_shield_n_END      (2)
#define PMIC_BUCK1_CTRL11_buck1_ocp_delay_sel_START   (3)
#define PMIC_BUCK1_CTRL11_buck1_ocp_delay_sel_END     (3)
#define PMIC_BUCK1_CTRL11_buck1_dmd_clamp_START       (4)
#define PMIC_BUCK1_CTRL11_buck1_dmd_clamp_END         (4)
#define PMIC_BUCK1_CTRL11_buck1_en_regop_clamp_START  (5)
#define PMIC_BUCK1_CTRL11_buck1_en_regop_clamp_END    (5)
#define PMIC_BUCK1_CTRL11_buck1_en_ss_sel_START       (6)
#define PMIC_BUCK1_CTRL11_buck1_en_ss_sel_END         (6)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL0_UNION
 �ṹ˵��  : BUCK2_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x025����ֵ:0x83�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_adj_clx : 4;  /* bit[0-3]: bit[3]������DMDʱ���رղ��ֹ��ʹܡ�
                                                        0�����رգ�
                                                        1���رա�
                                                        bit[2:0]��LX�����˲����ݵ��ڡ�
                                                        000��10pF��
                                                        001��20pF��
                                                        010��30pF��
                                                        011��40pF��
                                                        100��30pF��
                                                        101��40pF��
                                                        110��50pF��
                                                        111��60pF�� */
        unsigned char  buck2_adj_rlx : 4;  /* bit[4-7]: BUCK2 LX�����˲�������ڡ�
                                                        0000��3.4M����
                                                        0001��3.2M����
                                                        0010��2.8M����
                                                        0011��2.6M����
                                                        0100��2.4M����
                                                        0101��2.2M����
                                                        0110��2.0M����
                                                        0111��1.8M����
                                                        1000��1.6M����
                                                        1001��1.4M����
                                                        1010��1.2M����
                                                        1011��1.0M����
                                                        1100��0.8M����
                                                        1101��0.6M����
                                                        1110��0.4M����
                                                        1111��0.2M���� */
    } reg;
} PMIC_BUCK2_CTRL0_UNION;
#endif
#define PMIC_BUCK2_CTRL0_buck2_adj_clx_START  (0)
#define PMIC_BUCK2_CTRL0_buck2_adj_clx_END    (3)
#define PMIC_BUCK2_CTRL0_buck2_adj_rlx_START  (4)
#define PMIC_BUCK2_CTRL0_buck2_adj_rlx_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL1_UNION
 �ṹ˵��  : BUCK2_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x026����ֵ:0x40�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_ng_dt_sel : 1;  /* bit[0]  : BUCK2 P�ܵ�N������ģʽѡ��
                                                          0������������������ģʽ��
                                                          1����������������ģʽ�� */
        unsigned char  buck2_pg_dt_sel : 1;  /* bit[1]  : BUCK2 N�ܵ�P������ģʽѡ��
                                                          0������������������ģʽ��
                                                          1����������������ģʽ�� */
        unsigned char  buck2_sft_sel   : 1;  /* bit[2]  : BUCK2��������ʽѡ��
                                                          0��������ʱ��Ϊ200��s���ң�
                                                          1��������ʱ��Ϊ100��s���ҡ� */
        unsigned char  reserved        : 1;  /* bit[3]  : ������ */
        unsigned char  buck2_dt_sel    : 2;  /* bit[4-5]: ����ʱ����ڡ�
                                                          0���������ӳ�5ns��
                                                          1�������ӳ�5ns�� */
        unsigned char  buck2_ocp_sel   : 2;  /* bit[6-7]: BUCK2 OCP�������
                                                          00��3.24A��
                                                          01��3.69A��
                                                          10��4.13A��
                                                          11��4.57A�� */
    } reg;
} PMIC_BUCK2_CTRL1_UNION;
#endif
#define PMIC_BUCK2_CTRL1_buck2_ng_dt_sel_START  (0)
#define PMIC_BUCK2_CTRL1_buck2_ng_dt_sel_END    (0)
#define PMIC_BUCK2_CTRL1_buck2_pg_dt_sel_START  (1)
#define PMIC_BUCK2_CTRL1_buck2_pg_dt_sel_END    (1)
#define PMIC_BUCK2_CTRL1_buck2_sft_sel_START    (2)
#define PMIC_BUCK2_CTRL1_buck2_sft_sel_END      (2)
#define PMIC_BUCK2_CTRL1_buck2_dt_sel_START     (4)
#define PMIC_BUCK2_CTRL1_buck2_dt_sel_END       (5)
#define PMIC_BUCK2_CTRL1_buck2_ocp_sel_START    (6)
#define PMIC_BUCK2_CTRL1_buck2_ocp_sel_END      (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL2_UNION
 �ṹ˵��  : BUCK2_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x027����ֵ:0x3C�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_ng_n_sel : 2;  /* bit[0-1]: BUCK2 N power��������ӦNMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
        unsigned char  buck2_ng_p_sel : 2;  /* bit[2-3]: BUCK2 N power��������ӦPMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck2_pg_n_sel : 2;  /* bit[4-5]: BUCK2 P power��������ӦNMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck2_pg_p_sel : 2;  /* bit[6-7]: BUCK2 P power��������ӦPMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
    } reg;
} PMIC_BUCK2_CTRL2_UNION;
#endif
#define PMIC_BUCK2_CTRL2_buck2_ng_n_sel_START  (0)
#define PMIC_BUCK2_CTRL2_buck2_ng_n_sel_END    (1)
#define PMIC_BUCK2_CTRL2_buck2_ng_p_sel_START  (2)
#define PMIC_BUCK2_CTRL2_buck2_ng_p_sel_END    (3)
#define PMIC_BUCK2_CTRL2_buck2_pg_n_sel_START  (4)
#define PMIC_BUCK2_CTRL2_buck2_pg_n_sel_END    (5)
#define PMIC_BUCK2_CTRL2_buck2_pg_p_sel_START  (6)
#define PMIC_BUCK2_CTRL2_buck2_pg_p_sel_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL3_UNION
 �ṹ˵��  : BUCK2_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x20�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_reg_r  : 2;  /* bit[0-1]: BUCK2�ڲ�regulator���裬���ڵ���regulator����
                                                       00��2.8kHz��
                                                       01��45kHz��
                                                       10��85kHz��
                                                       11��152kHz�� */
        unsigned char  reserved     : 2;  /* bit[2-3]: ������ */
        unsigned char  buck2_reg_en : 1;  /* bit[4]  : BUCK2�ڲ����ȵ�����ʹ���źš�
                                                       0��ʹ�ܣ�
                                                       1����ʹ�ܡ� */
        unsigned char  buck2_dbias  : 2;  /* bit[5-6]: BUCK2�Ƚ���ƫ�õ������ڡ�
                                                       00��2uA��
                                                       01��1uA��
                                                       10��4uA��
                                                       11��3uA�� */
        unsigned char  buck2_ocp_d  : 1;  /* bit[7]  : BUCK2 �ڲ�OCP��·�����źš�
                                                       0�������Σ�
                                                       1�����Ρ� */
    } reg;
} PMIC_BUCK2_CTRL3_UNION;
#endif
#define PMIC_BUCK2_CTRL3_buck2_reg_r_START   (0)
#define PMIC_BUCK2_CTRL3_buck2_reg_r_END     (1)
#define PMIC_BUCK2_CTRL3_buck2_reg_en_START  (4)
#define PMIC_BUCK2_CTRL3_buck2_reg_en_END    (4)
#define PMIC_BUCK2_CTRL3_buck2_dbias_START   (5)
#define PMIC_BUCK2_CTRL3_buck2_dbias_END     (6)
#define PMIC_BUCK2_CTRL3_buck2_ocp_d_START   (7)
#define PMIC_BUCK2_CTRL3_buck2_ocp_d_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL4_UNION
 �ṹ˵��  : BUCK2_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x029����ֵ:0x20�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_short_pdp : 1;  /* bit[0]  : ��·�������μĴ�����
                                                          0��ʹ�ܶ�·������0.4V���ޣ�
                                                          1����ʹ�ܶ�·������0V���ޡ� */
        unsigned char  buck2_reg_ss_d  : 1;  /* bit[1]  : BUCK2������ʱ�ڲ�regulator״̬��
                                                          0������״̬��
                                                          1����λ���淴���� */
        unsigned char  buck2_regop_c   : 1;  /* bit[2]  : BUCK2�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate��
                                                          0��slew-rate����
                                                          1��slew-rate�졣 */
        unsigned char  buck2_reg_idr   : 2;  /* bit[3-4]: BUCK2�ڲ�regulator���������ڵ���regulator�������ȷ�Χ��
                                                          00��4uA��
                                                          01��6uA��
                                                          10��8uA��
                                                          11��10uA�� */
        unsigned char  buck2_reg_dr    : 3;  /* bit[5-7]: BUCK2�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ��
                                                          000��+/-6mV��
                                                          001��+/-12mV��
                                                          010��+/-18mV��
                                                          011��+/-24mV��
                                                          100��+/-30mV��
                                                          101��+/-36mV��
                                                          110��+/-42mV��
                                                          111��+/-48mV�� */
    } reg;
} PMIC_BUCK2_CTRL4_UNION;
#endif
#define PMIC_BUCK2_CTRL4_buck2_short_pdp_START  (0)
#define PMIC_BUCK2_CTRL4_buck2_short_pdp_END    (0)
#define PMIC_BUCK2_CTRL4_buck2_reg_ss_d_START   (1)
#define PMIC_BUCK2_CTRL4_buck2_reg_ss_d_END     (1)
#define PMIC_BUCK2_CTRL4_buck2_regop_c_START    (2)
#define PMIC_BUCK2_CTRL4_buck2_regop_c_END      (2)
#define PMIC_BUCK2_CTRL4_buck2_reg_idr_START    (3)
#define PMIC_BUCK2_CTRL4_buck2_reg_idr_END      (4)
#define PMIC_BUCK2_CTRL4_buck2_reg_dr_START     (5)
#define PMIC_BUCK2_CTRL4_buck2_reg_dr_END       (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL5_UNION
 �ṹ˵��  : BUCK2_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x02A����ֵ:0x04�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_ton      : 2;  /* bit[0-1]: BUCK2��С��ͨʱ�䡣
                                                         00��100ns��
                                                         01��200ns��
                                                         10��300ns��
                                                         11��400ns�� */
        unsigned char  buck2_nmos_off : 1;  /* bit[2]  : BUCK2���ڹر�NMOS power�ܡ�
                                                         0��ǿ�ƹرգ�
                                                         1����ǿ�ƹرա� */
        unsigned char  buck2_reg_c    : 1;  /* bit[3]  : BUCK2�ڲ�regulator���ݣ����ڵ���regulator����
                                                         0������С��
                                                         1�����ݴ� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_BUCK2_CTRL5_UNION;
#endif
#define PMIC_BUCK2_CTRL5_buck2_ton_START       (0)
#define PMIC_BUCK2_CTRL5_buck2_ton_END         (1)
#define PMIC_BUCK2_CTRL5_buck2_nmos_off_START  (2)
#define PMIC_BUCK2_CTRL5_buck2_nmos_off_END    (2)
#define PMIC_BUCK2_CTRL5_buck2_reg_c_START     (3)
#define PMIC_BUCK2_CTRL5_buck2_reg_c_END       (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL6_UNION
 �ṹ˵��  : BUCK2_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x02B����ֵ:0x41�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_shield_i    : 2;  /* bit[0-1]: DMD�����źŶ�Ӧ�������ڡ�
                                                            00��0.84A��
                                                            01��1.25A��
                                                            10��1.66A��
                                                            11��2.07A�� */
        unsigned char  buck2_new_dmd_sel : 5;  /* bit[2-6]: bit[6] DMDƫ�õ���ѡ��
                                                            0��2uA��
                                                            1��1uA��
                                                            bit[5] DMD��ʽѡ��
                                                            0����DMD��
                                                            1����DMD��
                                                            bit[4:2] ��DMD�ṹDMD�������ڡ�
                                                            000��-60mA��
                                                            001��-24mA��
                                                            010��12mA��
                                                            011��50mA��
                                                            100��92mA��
                                                            101��132mA��
                                                            110��173mA��
                                                            111��214mA�� */
        unsigned char  reserved          : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_BUCK2_CTRL6_UNION;
#endif
#define PMIC_BUCK2_CTRL6_buck2_shield_i_START     (0)
#define PMIC_BUCK2_CTRL6_buck2_shield_i_END       (1)
#define PMIC_BUCK2_CTRL6_buck2_new_dmd_sel_START  (2)
#define PMIC_BUCK2_CTRL6_buck2_new_dmd_sel_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL7_UNION
 �ṹ˵��  : BUCK2_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x1B�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_dmd_sel : 3;  /* bit[0-2]: BUCK2 ��DMD�ṹDMD�������ڡ�
                                                        000��-80mA��
                                                        001��-45mA��
                                                        010��-10mA��
                                                        011��27mA��
                                                        100��70mA��
                                                        101��111mA��
                                                        110��150mA��
                                                        111��182mA�� */
        unsigned char  buck2_mos_sel : 2;  /* bit[3-4]: BUCK2 �Ƚ����ڲ��������ڡ�
                                                        00������0uA��
                                                        01������1uA��
                                                        10������2uA��
                                                        11������3uA�� */
        unsigned char  reserved      : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_BUCK2_CTRL7_UNION;
#endif
#define PMIC_BUCK2_CTRL7_buck2_dmd_sel_START  (0)
#define PMIC_BUCK2_CTRL7_buck2_dmd_sel_END    (2)
#define PMIC_BUCK2_CTRL7_buck2_mos_sel_START  (3)
#define PMIC_BUCK2_CTRL7_buck2_mos_sel_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL8_UNION
 �ṹ˵��  : BUCK2_CTRL8 �Ĵ����ṹ���塣��ַƫ����:0x02D����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_reserve0 : 8;  /* bit[0-7]: BUCK2���üĴ����� */
    } reg;
} PMIC_BUCK2_CTRL8_UNION;
#endif
#define PMIC_BUCK2_CTRL8_buck2_reserve0_START  (0)
#define PMIC_BUCK2_CTRL8_buck2_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL9_UNION
 �ṹ˵��  : BUCK2_CTRL9 �Ĵ����ṹ���塣��ַƫ����:0x02E����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���9��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_reserve1 : 8;  /* bit[0-7]: BUCK2���üĴ����� */
    } reg;
} PMIC_BUCK2_CTRL9_UNION;
#endif
#define PMIC_BUCK2_CTRL9_buck2_reserve1_START  (0)
#define PMIC_BUCK2_CTRL9_buck2_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL10_UNION
 �ṹ˵��  : BUCK2_CTRL10 �Ĵ����ṹ���塣��ַƫ����:0x02F����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���10��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_reserve2 : 8;  /* bit[0-7]: BUCK2���üĴ����� */
    } reg;
} PMIC_BUCK2_CTRL10_UNION;
#endif
#define PMIC_BUCK2_CTRL10_buck2_reserve2_START  (0)
#define PMIC_BUCK2_CTRL10_buck2_reserve2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_CTRL11_UNION
 �ṹ˵��  : BUCK2_CTRL11 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK2���ƼĴ���11��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_pdn_lx_det     : 1;  /* bit[0]: BUCK1 �Ƚ�����ǿ����ѡ��
                                                             0�������ӳ�������
                                                             1�����ӳ������� */
        unsigned char  buck2_eco_dmd        : 1;  /* bit[1]: ������ģʽ��ǿ��NMOS�ܹرա�
                                                             0����ǿ�ƣ�
                                                             1��ǿ�ơ� */
        unsigned char  buck2_dmd_shield_n   : 1;  /* bit[2]: �������DMD�����źš�
                                                             0�����Σ�
                                                             1�������Ρ� */
        unsigned char  buck2_ocp_delay_sel  : 1;  /* bit[3]: OCP����ʱ���ӳ�15ns�źš�
                                                             0�����ӳ���
                                                             1���ӳ��� */
        unsigned char  buck2_dmd_clamp      : 1;  /* bit[4]: ��DMDǶλʹ���źš�
                                                             0�����ϣ�
                                                             1�������ϡ� */
        unsigned char  buck2_en_regop_clamp : 1;  /* bit[5]: regulator Ƕλ��·ʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned char  buck2_en_ss_sel      : 1;  /* bit[6]: ѡ����������źš�
                                                             0��ģ�������
                                                             1�����ָ����� */
        unsigned char  reserved             : 1;  /* bit[7]: ������ */
    } reg;
} PMIC_BUCK2_CTRL11_UNION;
#endif
#define PMIC_BUCK2_CTRL11_buck2_pdn_lx_det_START      (0)
#define PMIC_BUCK2_CTRL11_buck2_pdn_lx_det_END        (0)
#define PMIC_BUCK2_CTRL11_buck2_eco_dmd_START         (1)
#define PMIC_BUCK2_CTRL11_buck2_eco_dmd_END           (1)
#define PMIC_BUCK2_CTRL11_buck2_dmd_shield_n_START    (2)
#define PMIC_BUCK2_CTRL11_buck2_dmd_shield_n_END      (2)
#define PMIC_BUCK2_CTRL11_buck2_ocp_delay_sel_START   (3)
#define PMIC_BUCK2_CTRL11_buck2_ocp_delay_sel_END     (3)
#define PMIC_BUCK2_CTRL11_buck2_dmd_clamp_START       (4)
#define PMIC_BUCK2_CTRL11_buck2_dmd_clamp_END         (4)
#define PMIC_BUCK2_CTRL11_buck2_en_regop_clamp_START  (5)
#define PMIC_BUCK2_CTRL11_buck2_en_regop_clamp_END    (5)
#define PMIC_BUCK2_CTRL11_buck2_en_ss_sel_START       (6)
#define PMIC_BUCK2_CTRL11_buck2_en_ss_sel_END         (6)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL0_UNION
 �ṹ˵��  : BUCK3_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x031����ֵ:0x83�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_adj_clx : 4;  /* bit[0-3]: bit[3]������DMDʱ�رղ��ֹ��ʹܡ�
                                                        0�����رգ�
                                                        1���رա�
                                                        bit[2:0]��LX�����˲����ݵ��ڡ�
                                                        000��10pF��
                                                        001��20pF��
                                                        010��30pF��
                                                        011��40pF��
                                                        100��30pF��
                                                        101��40pF��
                                                        110��50pF��
                                                        111��60pF�� */
        unsigned char  buck3_adj_rlx : 4;  /* bit[4-7]: BUCK3 LX�����˲�������ڡ�
                                                        0000��3.4M����
                                                        0001��3.2M����
                                                        0010��2.8M����
                                                        0011��2.6M����
                                                        0100��2.4M����
                                                        0101��2.2M����
                                                        0110��2.0M����
                                                        0111��1.8M����
                                                        1000��1.6M����
                                                        1001��1.4M����
                                                        1010��1.2M����
                                                        1011��1.0M����
                                                        1100��0.8M����
                                                        1101��0.6M����
                                                        1110��0.4M����
                                                        1111��0.2M���� */
    } reg;
} PMIC_BUCK3_CTRL0_UNION;
#endif
#define PMIC_BUCK3_CTRL0_buck3_adj_clx_START  (0)
#define PMIC_BUCK3_CTRL0_buck3_adj_clx_END    (3)
#define PMIC_BUCK3_CTRL0_buck3_adj_rlx_START  (4)
#define PMIC_BUCK3_CTRL0_buck3_adj_rlx_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL1_UNION
 �ṹ˵��  : BUCK3_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x032����ֵ:0x40�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ng_dt_sel : 1;  /* bit[0]  : BUCK3 P�ܵ�N������ģʽѡ��
                                                          0������������������ģʽ��
                                                          1����������������ģʽ�� */
        unsigned char  buck3_pg_dt_sel : 1;  /* bit[1]  : BUCK3 N�ܵ�P������ģʽѡ��
                                                          0������������������ģʽ��
                                                          1����������������ģʽ�� */
        unsigned char  buck3_sft_sel   : 1;  /* bit[2]  : BUCK3��������ʽѡ��
                                                          0��������ʱ��Ϊ200us���ң�
                                                          1��������ʱ��Ϊ100us���ҡ� */
        unsigned char  reserved        : 1;  /* bit[3]  : ������ */
        unsigned char  buck3_dt_sel    : 2;  /* bit[4-5]: ����ʱ����ڡ�
                                                          0���������ӳ�5ns��
                                                          1�������ӳ�5ns�� */
        unsigned char  buck3_ocp_sel   : 2;  /* bit[6-7]: BUCK3 OCP�������
                                                          00��3.24A��
                                                          01��3.69A��
                                                          10��4.13A��
                                                          11��4.57A�� */
    } reg;
} PMIC_BUCK3_CTRL1_UNION;
#endif
#define PMIC_BUCK3_CTRL1_buck3_ng_dt_sel_START  (0)
#define PMIC_BUCK3_CTRL1_buck3_ng_dt_sel_END    (0)
#define PMIC_BUCK3_CTRL1_buck3_pg_dt_sel_START  (1)
#define PMIC_BUCK3_CTRL1_buck3_pg_dt_sel_END    (1)
#define PMIC_BUCK3_CTRL1_buck3_sft_sel_START    (2)
#define PMIC_BUCK3_CTRL1_buck3_sft_sel_END      (2)
#define PMIC_BUCK3_CTRL1_buck3_dt_sel_START     (4)
#define PMIC_BUCK3_CTRL1_buck3_dt_sel_END       (5)
#define PMIC_BUCK3_CTRL1_buck3_ocp_sel_START    (6)
#define PMIC_BUCK3_CTRL1_buck3_ocp_sel_END      (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL2_UNION
 �ṹ˵��  : BUCK3_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x033����ֵ:0x3C�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ng_n_sel : 2;  /* bit[0-1]: BUCK3 N power��������ӦNMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
        unsigned char  buck3_ng_p_sel : 2;  /* bit[2-3]: BUCK3 N power��������ӦPMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck3_pg_n_sel : 2;  /* bit[4-5]: BUCK3 P power��������ӦNMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck3_pg_p_sel : 2;  /* bit[6-7]: BUCK3 P power��������ӦPMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
    } reg;
} PMIC_BUCK3_CTRL2_UNION;
#endif
#define PMIC_BUCK3_CTRL2_buck3_ng_n_sel_START  (0)
#define PMIC_BUCK3_CTRL2_buck3_ng_n_sel_END    (1)
#define PMIC_BUCK3_CTRL2_buck3_ng_p_sel_START  (2)
#define PMIC_BUCK3_CTRL2_buck3_ng_p_sel_END    (3)
#define PMIC_BUCK3_CTRL2_buck3_pg_n_sel_START  (4)
#define PMIC_BUCK3_CTRL2_buck3_pg_n_sel_END    (5)
#define PMIC_BUCK3_CTRL2_buck3_pg_p_sel_START  (6)
#define PMIC_BUCK3_CTRL2_buck3_pg_p_sel_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL3_UNION
 �ṹ˵��  : BUCK3_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x20�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_reg_r  : 2;  /* bit[0-1]: BUCK3�ڲ�regulator���裬���ڵ���regulator����
                                                       00��2.8kHz��
                                                       01��45kHz��
                                                       10��85kHz��
                                                       11��152kHz�� */
        unsigned char  reserved     : 2;  /* bit[2-3]: ������ */
        unsigned char  buck3_reg_en : 1;  /* bit[4]  : BUCK3�ڲ����ȵ�����ʹ���źš�
                                                       0��ʹ�ܣ�
                                                       1����ʹ�ܡ� */
        unsigned char  buck3_dbias  : 2;  /* bit[5-6]: BUCK3 �Ƚ���ƫ�õ������ڡ�
                                                       00��2uA��
                                                       01��1uA��
                                                       10��4uA��
                                                       11��3uA�� */
        unsigned char  buck3_ocp_d  : 1;  /* bit[7]  : BUCK3 �ڲ�OCP��·�����źš�
                                                       0�������Σ�
                                                       1�����Ρ� */
    } reg;
} PMIC_BUCK3_CTRL3_UNION;
#endif
#define PMIC_BUCK3_CTRL3_buck3_reg_r_START   (0)
#define PMIC_BUCK3_CTRL3_buck3_reg_r_END     (1)
#define PMIC_BUCK3_CTRL3_buck3_reg_en_START  (4)
#define PMIC_BUCK3_CTRL3_buck3_reg_en_END    (4)
#define PMIC_BUCK3_CTRL3_buck3_dbias_START   (5)
#define PMIC_BUCK3_CTRL3_buck3_dbias_END     (6)
#define PMIC_BUCK3_CTRL3_buck3_ocp_d_START   (7)
#define PMIC_BUCK3_CTRL3_buck3_ocp_d_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL4_UNION
 �ṹ˵��  : BUCK3_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x035����ֵ:0x20�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_short_pdp : 1;  /* bit[0]  : ��·�������μĴ�����
                                                          0��ʹ�ܶ�·������0.4V���ޣ�
                                                          1����ʹ�ܶ�·������0V���ޡ� */
        unsigned char  buck3_reg_ss_d  : 1;  /* bit[1]  : BUCK3������ʱ�ڲ�regulator״̬��
                                                          0������״̬��
                                                          1����λ���淴���� */
        unsigned char  buck3_regop_c   : 1;  /* bit[2]  : BUCK3�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate��
                                                          0��slew-rate����
                                                          1��slew-rate�졣 */
        unsigned char  buck3_reg_idr   : 2;  /* bit[3-4]: BUCK3�ڲ�regulator���������ڵ���regulator�������ȷ�Χ��
                                                          00��4uA��
                                                          01��6uA��
                                                          10��8uA��
                                                          11��10uA�� */
        unsigned char  buck3_reg_dr    : 3;  /* bit[5-7]: BUCK3�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ��
                                                          000��+/-6mV��
                                                          001��+/-12mV��
                                                          010��+/-18mV��
                                                          011��+/-24mV��
                                                          100��+/-30mV��
                                                          101��+/-36mV��
                                                          110��+/-42mV��
                                                          111��+/-48mV�� */
    } reg;
} PMIC_BUCK3_CTRL4_UNION;
#endif
#define PMIC_BUCK3_CTRL4_buck3_short_pdp_START  (0)
#define PMIC_BUCK3_CTRL4_buck3_short_pdp_END    (0)
#define PMIC_BUCK3_CTRL4_buck3_reg_ss_d_START   (1)
#define PMIC_BUCK3_CTRL4_buck3_reg_ss_d_END     (1)
#define PMIC_BUCK3_CTRL4_buck3_regop_c_START    (2)
#define PMIC_BUCK3_CTRL4_buck3_regop_c_END      (2)
#define PMIC_BUCK3_CTRL4_buck3_reg_idr_START    (3)
#define PMIC_BUCK3_CTRL4_buck3_reg_idr_END      (4)
#define PMIC_BUCK3_CTRL4_buck3_reg_dr_START     (5)
#define PMIC_BUCK3_CTRL4_buck3_reg_dr_END       (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL5_UNION
 �ṹ˵��  : BUCK3_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x036����ֵ:0x04�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ton      : 2;  /* bit[0-1]: BUCK3��С��ͨʱ�䡣
                                                         00��100ns��
                                                         01��200ns��
                                                         10��300ns��
                                                         11��400ns�� */
        unsigned char  buck3_nmos_off : 1;  /* bit[2]  : BUCK3���ڹر�NMOS power�ܡ�
                                                         0��ǿ�ƹرգ�
                                                         1����ǿ�ƹرա� */
        unsigned char  buck3_reg_c    : 1;  /* bit[3]  : BUCK3�ڲ�regulator���ݣ����ڵ���regulator����
                                                         0������С��
                                                         1�����ݴ� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_BUCK3_CTRL5_UNION;
#endif
#define PMIC_BUCK3_CTRL5_buck3_ton_START       (0)
#define PMIC_BUCK3_CTRL5_buck3_ton_END         (1)
#define PMIC_BUCK3_CTRL5_buck3_nmos_off_START  (2)
#define PMIC_BUCK3_CTRL5_buck3_nmos_off_END    (2)
#define PMIC_BUCK3_CTRL5_buck3_reg_c_START     (3)
#define PMIC_BUCK3_CTRL5_buck3_reg_c_END       (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL6_UNION
 �ṹ˵��  : BUCK3_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x037����ֵ:0x41�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_shield_i    : 2;  /* bit[0-1]: DMD�����źŶ�Ӧ�������ڡ�
                                                            00��0.84A��
                                                            01��1.25A��
                                                            10��1.66A��
                                                            11��2.07A�� */
        unsigned char  buck3_new_dmd_sel : 5;  /* bit[2-6]: bit[6]��DMDƫ�õ���ѡ��
                                                            0��2uA��
                                                            1��1uA��
                                                            bit[5]��DMD��ʽѡ��
                                                            0����DMD��
                                                            1����DMD��
                                                            Bit[4:2]����DMD�ṹDMD�������ڡ�
                                                            000��38mA��
                                                            001��-92mA��
                                                            010��-45mA��
                                                            011��3mA��
                                                            100��82mA��
                                                            101��130mA��
                                                            110��173mA��
                                                            111��219mA�� */
        unsigned char  reserved          : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_BUCK3_CTRL6_UNION;
#endif
#define PMIC_BUCK3_CTRL6_buck3_shield_i_START     (0)
#define PMIC_BUCK3_CTRL6_buck3_shield_i_END       (1)
#define PMIC_BUCK3_CTRL6_buck3_new_dmd_sel_START  (2)
#define PMIC_BUCK3_CTRL6_buck3_new_dmd_sel_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL7_UNION
 �ṹ˵��  : BUCK3_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x1B�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_dmd_sel : 3;  /* bit[0-2]: BUCK3 ��DMD�ṹDMD�������ڡ�
                                                        000��-74mA��
                                                        001��-35mA��
                                                        010��-3mA��
                                                        011��35mA��
                                                        100��78mA��
                                                        101��122mA��
                                                        110��167mA��
                                                        111��210mA�� */
        unsigned char  buck3_mos_sel : 2;  /* bit[3-4]: BUCK3 �Ƚ����ڲ��������ڡ�
                                                        00������0uA��
                                                        01������1uA��
                                                        10������2uA��
                                                        11������3uA�� */
        unsigned char  reserved      : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_BUCK3_CTRL7_UNION;
#endif
#define PMIC_BUCK3_CTRL7_buck3_dmd_sel_START  (0)
#define PMIC_BUCK3_CTRL7_buck3_dmd_sel_END    (2)
#define PMIC_BUCK3_CTRL7_buck3_mos_sel_START  (3)
#define PMIC_BUCK3_CTRL7_buck3_mos_sel_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL8_UNION
 �ṹ˵��  : BUCK3_CTRL8 �Ĵ����ṹ���塣��ַƫ����:0x039����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_reserve0 : 8;  /* bit[0-7]: BUCK3���üĴ����� */
    } reg;
} PMIC_BUCK3_CTRL8_UNION;
#endif
#define PMIC_BUCK3_CTRL8_buck3_reserve0_START  (0)
#define PMIC_BUCK3_CTRL8_buck3_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL9_UNION
 �ṹ˵��  : BUCK3_CTRL9 �Ĵ����ṹ���塣��ַƫ����:0x03A����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���9��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_reserve1 : 8;  /* bit[0-7]: BUCK3���üĴ����� */
    } reg;
} PMIC_BUCK3_CTRL9_UNION;
#endif
#define PMIC_BUCK3_CTRL9_buck3_reserve1_START  (0)
#define PMIC_BUCK3_CTRL9_buck3_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL10_UNION
 �ṹ˵��  : BUCK3_CTRL10 �Ĵ����ṹ���塣��ַƫ����:0x03B����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���10��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_reserve2 : 8;  /* bit[0-7]: BUCK3���üĴ����� */
    } reg;
} PMIC_BUCK3_CTRL10_UNION;
#endif
#define PMIC_BUCK3_CTRL10_buck3_reserve2_START  (0)
#define PMIC_BUCK3_CTRL10_buck3_reserve2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_CTRL11_UNION
 �ṹ˵��  : BUCK3_CTRL11 �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK3���ƼĴ���11��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_pdn_lx_det     : 1;  /* bit[0]: BUCK3 �Ƚ�����ǿ����ѡ��
                                                             0�������ӳ�������
                                                             1�����ӳ������� */
        unsigned char  buck3_eco_dmd        : 1;  /* bit[1]: ������ģʽ��ǿ��NMOS�ܹرա�
                                                             0����ǿ�ƣ�
                                                             1��ǿ�ơ� */
        unsigned char  buck3_dmd_shield_n   : 1;  /* bit[2]: �������DMD�����źš�
                                                             0�����Σ�
                                                             1�������Ρ� */
        unsigned char  buck3_ocp_delay_sel  : 1;  /* bit[3]: OCP����ʱ���ӳ�15ns�źš�
                                                             0�����ӳ���
                                                             1���ӳ��� */
        unsigned char  buck3_dmd_clamp      : 1;  /* bit[4]: ��DMDǶλʹ���źš�
                                                             0�����ϣ�
                                                             1�������ϡ� */
        unsigned char  buck3_en_regop_clamp : 1;  /* bit[5]: regulator Ƕλ��·ʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned char  buck3_en_ss_sel      : 1;  /* bit[6]: ѡ����������źš�
                                                             0��ģ�������
                                                             1�����ָ����� */
        unsigned char  reserved             : 1;  /* bit[7]: ������ */
    } reg;
} PMIC_BUCK3_CTRL11_UNION;
#endif
#define PMIC_BUCK3_CTRL11_buck3_pdn_lx_det_START      (0)
#define PMIC_BUCK3_CTRL11_buck3_pdn_lx_det_END        (0)
#define PMIC_BUCK3_CTRL11_buck3_eco_dmd_START         (1)
#define PMIC_BUCK3_CTRL11_buck3_eco_dmd_END           (1)
#define PMIC_BUCK3_CTRL11_buck3_dmd_shield_n_START    (2)
#define PMIC_BUCK3_CTRL11_buck3_dmd_shield_n_END      (2)
#define PMIC_BUCK3_CTRL11_buck3_ocp_delay_sel_START   (3)
#define PMIC_BUCK3_CTRL11_buck3_ocp_delay_sel_END     (3)
#define PMIC_BUCK3_CTRL11_buck3_dmd_clamp_START       (4)
#define PMIC_BUCK3_CTRL11_buck3_dmd_clamp_END         (4)
#define PMIC_BUCK3_CTRL11_buck3_en_regop_clamp_START  (5)
#define PMIC_BUCK3_CTRL11_buck3_en_regop_clamp_END    (5)
#define PMIC_BUCK3_CTRL11_buck3_en_ss_sel_START       (6)
#define PMIC_BUCK3_CTRL11_buck3_en_ss_sel_END         (6)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_CTRL0_UNION
 �ṹ˵��  : BUCK4_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x03D����ֵ:0x83�����:8
 �Ĵ���˵��: BUCK4���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_adj_clx : 4;  /* bit[0-3]: bit[3]������DMDʱ�رղ��ֹ��ʹܡ�
                                                        0�����رգ�
                                                        1���رա�
                                                        bit[2:0]��LX�����˲����ݵ��ڡ�
                                                        000��10pF��
                                                        001��20pF��
                                                        010��30pF��
                                                        011��40pF��
                                                        100��30pF��
                                                        101��40pF��
                                                        110��50pF��
                                                        111��60pF�� */
        unsigned char  buck4_adj_rlx : 4;  /* bit[4-7]: BUCK4 LX�����˲�������ڡ�
                                                        0000��3.4M����
                                                        0001��3.2M����
                                                        0010��2.8M����
                                                        0011��2.6M����
                                                        0100��2.4M����
                                                        0101��2.2M����
                                                        0110��2.0M����
                                                        0111��1.8M����
                                                        1000��1.6M����
                                                        1001��1.4M����
                                                        1010��1.2M����
                                                        1011��1.0M����
                                                        1100��0.8M����
                                                        1101��0.6M����
                                                        1110��0.4M����
                                                        1111��0.2M���� */
    } reg;
} PMIC_BUCK4_CTRL0_UNION;
#endif
#define PMIC_BUCK4_CTRL0_buck4_adj_clx_START  (0)
#define PMIC_BUCK4_CTRL0_buck4_adj_clx_END    (3)
#define PMIC_BUCK4_CTRL0_buck4_adj_rlx_START  (4)
#define PMIC_BUCK4_CTRL0_buck4_adj_rlx_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_CTRL1_UNION
 �ṹ˵��  : BUCK4_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x03E����ֵ:0x40�����:8
 �Ĵ���˵��: BUCK4���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_ng_dt_sel : 1;  /* bit[0]  : BUCK4 P�ܵ�N������ģʽѡ��
                                                          0������������������ģʽ��
                                                          1����������������ģʽ�� */
        unsigned char  buck4_pg_dt_sel : 1;  /* bit[1]  : BUCK4 N�ܵ�P������ģʽѡ��
                                                          0������������������ģʽ��
                                                          1����������������ģʽ�� */
        unsigned char  buck4_sft_sel   : 1;  /* bit[2]  : BUCK4��������ʽѡ��
                                                          0��������ʱ��Ϊ200us���ң�
                                                          1��������ʱ��Ϊ100us���ҡ� */
        unsigned char  reserved        : 1;  /* bit[3]  : ������ */
        unsigned char  buck4_dt_sel    : 2;  /* bit[4-5]: ����ʱ����ڡ�
                                                          0���������ӳ�5ns��
                                                          1�������ӳ�5ns�� */
        unsigned char  buck4_ocp_sel   : 2;  /* bit[6-7]: BUCK4 OCP�������
                                                          00��3.24A��
                                                          01��3.69A��
                                                          10��4.13A��
                                                          11��4.57A�� */
    } reg;
} PMIC_BUCK4_CTRL1_UNION;
#endif
#define PMIC_BUCK4_CTRL1_buck4_ng_dt_sel_START  (0)
#define PMIC_BUCK4_CTRL1_buck4_ng_dt_sel_END    (0)
#define PMIC_BUCK4_CTRL1_buck4_pg_dt_sel_START  (1)
#define PMIC_BUCK4_CTRL1_buck4_pg_dt_sel_END    (1)
#define PMIC_BUCK4_CTRL1_buck4_sft_sel_START    (2)
#define PMIC_BUCK4_CTRL1_buck4_sft_sel_END      (2)
#define PMIC_BUCK4_CTRL1_buck4_dt_sel_START     (4)
#define PMIC_BUCK4_CTRL1_buck4_dt_sel_END       (5)
#define PMIC_BUCK4_CTRL1_buck4_ocp_sel_START    (6)
#define PMIC_BUCK4_CTRL1_buck4_ocp_sel_END      (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_CTRL2_UNION
 �ṹ˵��  : BUCK4_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x03F����ֵ:0x3C�����:8
 �Ĵ���˵��: BUCK4���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_ng_n_sel : 2;  /* bit[0-1]: BUCK4 N power��������ӦNMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
        unsigned char  buck4_ng_p_sel : 2;  /* bit[2-3]: BUCK4 N power��������ӦPMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck4_pg_n_sel : 2;  /* bit[4-5]: BUCK4 P power��������ӦNMOS�����������ڡ�
                                                         00��4��������
                                                         01��3��������
                                                         10��2��������
                                                         11��1�������� */
        unsigned char  buck4_pg_p_sel : 2;  /* bit[6-7]: BUCK4 P power��������ӦPMOS�����������ڡ�
                                                         00��1��������
                                                         01��2��������
                                                         10��3��������
                                                         11��4�������� */
    } reg;
} PMIC_BUCK4_CTRL2_UNION;
#endif
#define PMIC_BUCK4_CTRL2_buck4_ng_n_sel_START  (0)
#define PMIC_BUCK4_CTRL2_buck4_ng_n_sel_END    (1)
#define PMIC_BUCK4_CTRL2_buck4_ng_p_sel_START  (2)
#define PMIC_BUCK4_CTRL2_buck4_ng_p_sel_END    (3)
#define PMIC_BUCK4_CTRL2_buck4_pg_n_sel_START  (4)
#define PMIC_BUCK4_CTRL2_buck4_pg_n_sel_END    (5)
#define PMIC_BUCK4_CTRL2_buck4_pg_p_sel_START  (6)
#define PMIC_BUCK4_CTRL2_buck4_pg_p_sel_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_CTRL3_UNION
 �ṹ˵��  : BUCK4_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x20�����:8
 �Ĵ���˵��: BUCK4���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_reg_r  : 2;  /* bit[0-1]: BUCK4�ڲ�regulator���裬���ڵ���regulator����
                                                       00��2.8kHz��
                                                       01��45kHz��
                                                       10��85kHz��
                                                       11��152kHz�� */
        unsigned char  reserved     : 2;  /* bit[2-3]: ������ */
        unsigned char  buck4_reg_en : 1;  /* bit[4]  : BUCK4�ڲ����ȵ�����ʹ���źš�
                                                       0��ʹ�ܣ�
                                                       1����ʹ�ܡ� */
        unsigned char  buck4_dbias  : 2;  /* bit[5-6]: BUCK4 �Ƚ���ƫ�õ������ڡ�
                                                       00��2uA��
                                                       01��1uA��
                                                       10��4uA��
                                                       11��3uA�� */
        unsigned char  buck4_ocp_d  : 1;  /* bit[7]  : BUCK4 �ڲ�OCP��·�����źš�
                                                       0�������Σ�
                                                       1�����Ρ� */
    } reg;
} PMIC_BUCK4_CTRL3_UNION;
#endif
#define PMIC_BUCK4_CTRL3_buck4_reg_r_START   (0)
#define PMIC_BUCK4_CTRL3_buck4_reg_r_END     (1)
#define PMIC_BUCK4_CTRL3_buck4_reg_en_START  (4)
#define PMIC_BUCK4_CTRL3_buck4_reg_en_END    (4)
#define PMIC_BUCK4_CTRL3_buck4_dbias_START   (5)
#define PMIC_BUCK4_CTRL3_buck4_dbias_END     (6)
#define PMIC_BUCK4_CTRL3_buck4_ocp_d_START   (7)
#define PMIC_BUCK4_CTRL3_buck4_ocp_d_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_CTRL4_UNION
 �ṹ˵��  : BUCK4_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x041����ֵ:0x20�����:8
 �Ĵ���˵��: BUCK4���ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_short_pdp : 1;  /* bit[0]  : ��·�������μĴ�����
                                                          0��ʹ�ܶ�·������0.4V���ޣ�
                                                          1����ʹ�ܶ�·������0V���ޡ� */
        unsigned char  buck4_reg_ss_d  : 1;  /* bit[1]  : BUCK4������ʱ�ڲ�regulator״̬��
                                                          0������״̬��
                                                          1����λ���淴���� */
        unsigned char  buck4_regop_c   : 1;  /* bit[2]  : BUCK4�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate��
                                                          0��slew-rate����
                                                          1��slew-rate�졣 */
        unsigned char  buck4_reg_idr   : 2;  /* bit[3-4]: BUCK4�ڲ�regulator���������ڵ���regulator�������ȷ�Χ��
                                                          00��4uA��
                                                          01��6uA��
                                                          10��8uA��
                                                          11��10uA�� */
        unsigned char  buck4_reg_dr    : 3;  /* bit[5-7]: BUCK4�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ��
                                                          000��+/-6mV��
                                                          001��+/-12mV��
                                                          010��+/-18mV��
                                                          011��+/-24mV��
                                                          100��+/-30mV��
                                                          101��+/-36mV��
                                                          110��+/-42mV��
                                                          111��+/-48mV�� */
    } reg;
} PMIC_BUCK4_CTRL4_UNION;
#endif
#define PMIC_BUCK4_CTRL4_buck4_short_pdp_START  (0)
#define PMIC_BUCK4_CTRL4_buck4_short_pdp_END    (0)
#define PMIC_BUCK4_CTRL4_buck4_reg_ss_d_START   (1)
#define PMIC_BUCK4_CTRL4_buck4_reg_ss_d_END     (1)
#define PMIC_BUCK4_CTRL4_buck4_regop_c_START    (2)
#define PMIC_BUCK4_CTRL4_buck4_regop_c_END      (2)
#define PMIC_BUCK4_CTRL4_buck4_reg_idr_START    (3)
#define PMIC_BUCK4_CTRL4_buck4_reg_idr_END      (4)
#define PMIC_BUCK4_CTRL4_buck4_reg_dr_START     (5)
#define PMIC_BUCK4_CTRL4_buck4_reg_dr_END       (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_CTRL5_UNION
 �ṹ˵��  : BUCK4_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x042����ֵ:0x04�����:8
 �Ĵ���˵��: BUCK4���ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_ton      : 2;  /* bit[0-1]: BUCK4��С��ͨʱ�䡣
                                                         00��100ns��
                                                         01��200ns��
                                                         10��300ns��
                                                         11��400ns�� */
        unsigned char  buck4_nmos_off : 1;  /* bit[2]  : BUCK4���ڹر�NMOS power�ܡ�
                                                         0��ǿ�ƹرգ�
                                                         1����ǿ�ƹرա� */
        unsigned char  buck4_reg_c    : 1;  /* bit[3]  : BUCK4�ڲ�regulator���ݣ����ڵ���regulator����
                                                         0������С��
                                                         1�����ݴ� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_BUCK4_CTRL5_UNION;
#endif
#define PMIC_BUCK4_CTRL5_buck4_ton_START       (0)
#define PMIC_BUCK4_CTRL5_buck4_ton_END         (1)
#define PMIC_BUCK4_CTRL5_buck4_nmos_off_START  (2)
#define PMIC_BUCK4_CTRL5_buck4_nmos_off_END    (2)
#define PMIC_BUCK4_CTRL5_buck4_reg_c_START     (3)
#define PMIC_BUCK4_CTRL5_buck4_reg_c_END       (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_CTRL6_UNION
 �ṹ˵��  : BUCK4_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x043����ֵ:0x41�����:8
 �Ĵ���˵��: BUCK4���ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_shield_i    : 2;  /* bit[0-1]: DMD�����źŶ�Ӧ�������ڡ�
                                                            00��0.84A��
                                                            01��1.25A��
                                                            10��1.66A��
                                                            11��2.07A�� */
        unsigned char  buck4_new_dmd_sel : 5;  /* bit[2-6]: bit[6]��DMDƫ�õ���ѡ��
                                                            0��2uA��
                                                            1��1uA��
                                                            bit[5]��DMD��ʽѡ��
                                                            0����DMD��
                                                            1����DMD��
                                                            Bit[4:2]����DMD�ṹDMD�������ڡ�
                                                            000��28mA��
                                                            001��-75mA��
                                                            010��-40mA��
                                                            011��-12mA��
                                                            100��70mA��
                                                            101��120mA��
                                                            110��162mA��
                                                            111��205mA�� */
        unsigned char  reserved          : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_BUCK4_CTRL6_UNION;
#endif
#define PMIC_BUCK4_CTRL6_buck4_shield_i_START     (0)
#define PMIC_BUCK4_CTRL6_buck4_shield_i_END       (1)
#define PMIC_BUCK4_CTRL6_buck4_new_dmd_sel_START  (2)
#define PMIC_BUCK4_CTRL6_buck4_new_dmd_sel_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_CTRL7_UNION
 �ṹ˵��  : BUCK4_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x1B�����:8
 �Ĵ���˵��: BUCK4���ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_dmd_sel : 3;  /* bit[0-2]: BUCK4 ��DMD�ṹDMD�������ڡ�
                                                        000��-45mA��
                                                        001��-5mA��
                                                        010��27mA��
                                                        011��70mA��
                                                        100��105mA��
                                                        101��144mA��
                                                        110��185mA��
                                                        111��228mA�� */
        unsigned char  buck4_mos_sel : 2;  /* bit[3-4]: BUCK4 �Ƚ����ڲ��������ڡ�
                                                        00������0uA��
                                                        01������1uA��
                                                        10������2uA��
                                                        11������3uA�� */
        unsigned char  reserved      : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_BUCK4_CTRL7_UNION;
#endif
#define PMIC_BUCK4_CTRL7_buck4_dmd_sel_START  (0)
#define PMIC_BUCK4_CTRL7_buck4_dmd_sel_END    (2)
#define PMIC_BUCK4_CTRL7_buck4_mos_sel_START  (3)
#define PMIC_BUCK4_CTRL7_buck4_mos_sel_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_CTRL8_UNION
 �ṹ˵��  : BUCK4_CTRL8 �Ĵ����ṹ���塣��ַƫ����:0x045����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK4���ƼĴ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_reserve0 : 8;  /* bit[0-7]: BUCK4���üĴ����� */
    } reg;
} PMIC_BUCK4_CTRL8_UNION;
#endif
#define PMIC_BUCK4_CTRL8_buck4_reserve0_START  (0)
#define PMIC_BUCK4_CTRL8_buck4_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_CTRL9_UNION
 �ṹ˵��  : BUCK4_CTRL9 �Ĵ����ṹ���塣��ַƫ����:0x046����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK4���ƼĴ���9��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_reserve1 : 8;  /* bit[0-7]: BUCK4���üĴ����� */
    } reg;
} PMIC_BUCK4_CTRL9_UNION;
#endif
#define PMIC_BUCK4_CTRL9_buck4_reserve1_START  (0)
#define PMIC_BUCK4_CTRL9_buck4_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_CTRL10_UNION
 �ṹ˵��  : BUCK4_CTRL10 �Ĵ����ṹ���塣��ַƫ����:0x047����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK4���ƼĴ���10��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_reserve2 : 8;  /* bit[0-7]: BUCK4���üĴ����� */
    } reg;
} PMIC_BUCK4_CTRL10_UNION;
#endif
#define PMIC_BUCK4_CTRL10_buck4_reserve2_START  (0)
#define PMIC_BUCK4_CTRL10_buck4_reserve2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_CTRL11_UNION
 �ṹ˵��  : BUCK4_CTRL11 �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK4���ƼĴ���11��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_pdn_lx_det     : 1;  /* bit[0]: BUCK3 �Ƚ�����ǿ����ѡ��
                                                             0�������ӳ�������
                                                             1�����ӳ������� */
        unsigned char  buck4_eco_dmd        : 1;  /* bit[1]: ������ģʽ��ǿ��NMOS�ܹرա�
                                                             0����ǿ�ƣ�
                                                             1��ǿ�ơ� */
        unsigned char  buck4_dmd_shield_n   : 1;  /* bit[2]: �������DMD�����źš�
                                                             0�����Σ�
                                                             1�������Ρ� */
        unsigned char  buck4_ocp_delay_sel  : 1;  /* bit[3]: OCP����ʱ���ӳ�15ns�źš�
                                                             0�����ӳ���
                                                             1���ӳ��� */
        unsigned char  buck4_dmd_clamp      : 1;  /* bit[4]: ��DMDǶλʹ���źš�
                                                             0�����ϣ�
                                                             1�������ϡ� */
        unsigned char  buck4_en_regop_clamp : 1;  /* bit[5]: regulator Ƕλ��·ʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned char  buck4_en_ss_sel      : 1;  /* bit[6]: ѡ����������źš�
                                                             0��ģ�������
                                                             1�����ָ����� */
        unsigned char  reserved             : 1;  /* bit[7]: ������ */
    } reg;
} PMIC_BUCK4_CTRL11_UNION;
#endif
#define PMIC_BUCK4_CTRL11_buck4_pdn_lx_det_START      (0)
#define PMIC_BUCK4_CTRL11_buck4_pdn_lx_det_END        (0)
#define PMIC_BUCK4_CTRL11_buck4_eco_dmd_START         (1)
#define PMIC_BUCK4_CTRL11_buck4_eco_dmd_END           (1)
#define PMIC_BUCK4_CTRL11_buck4_dmd_shield_n_START    (2)
#define PMIC_BUCK4_CTRL11_buck4_dmd_shield_n_END      (2)
#define PMIC_BUCK4_CTRL11_buck4_ocp_delay_sel_START   (3)
#define PMIC_BUCK4_CTRL11_buck4_ocp_delay_sel_END     (3)
#define PMIC_BUCK4_CTRL11_buck4_dmd_clamp_START       (4)
#define PMIC_BUCK4_CTRL11_buck4_dmd_clamp_END         (4)
#define PMIC_BUCK4_CTRL11_buck4_en_regop_clamp_START  (5)
#define PMIC_BUCK4_CTRL11_buck4_en_regop_clamp_END    (5)
#define PMIC_BUCK4_CTRL11_buck4_en_ss_sel_START       (6)
#define PMIC_BUCK4_CTRL11_buck4_en_ss_sel_END         (6)


/*****************************************************************************
 �ṹ��    : PMIC_LDO_1_CTRL_UNION
 �ṹ˵��  : LDO_1_CTRL �Ĵ����ṹ���塣��ַƫ����:0x049����ֵ:0x11�����:8
 �Ĵ���˵��: LDO0_2/LDO1���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo1_vrset     : 3;  /* bit[0-2]: LDO1���ص����ʲ���������
                                                         000����������
                                                         001������5mV��
                                                         010������10mV��
                                                         011������15mV��
                                                         100������20mV��
                                                         101������25mV��
                                                         110������30mV��
                                                         111������35mV�� */
        unsigned char  ldo1_ocp_enn   : 1;  /* bit[3]  : LDO1����ģʽѡ���źš�
                                                         0����ʾ�澯������
                                                         1����ʾ�澯�������� */
        unsigned char  ldo0_2_vrset   : 3;  /* bit[4-6]: LDO0���ص����ʲ���������
                                                         000����������
                                                         001������5mV��
                                                         010������10mV��
                                                         011������15mV��
                                                         100������20mV��
                                                         101������25mV��
                                                         110������30mV��
                                                         111������35mV�� */
        unsigned char  ldo0_2_ocp_enn : 1;  /* bit[7]  : LDO0����ģʽѡ���źš�
                                                         0����ʾ�澯������
                                                         1����ʾ�澯�������� */
    } reg;
} PMIC_LDO_1_CTRL_UNION;
#endif
#define PMIC_LDO_1_CTRL_ldo1_vrset_START      (0)
#define PMIC_LDO_1_CTRL_ldo1_vrset_END        (2)
#define PMIC_LDO_1_CTRL_ldo1_ocp_enn_START    (3)
#define PMIC_LDO_1_CTRL_ldo1_ocp_enn_END      (3)
#define PMIC_LDO_1_CTRL_ldo0_2_vrset_START    (4)
#define PMIC_LDO_1_CTRL_ldo0_2_vrset_END      (6)
#define PMIC_LDO_1_CTRL_ldo0_2_ocp_enn_START  (7)
#define PMIC_LDO_1_CTRL_ldo0_2_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LD2_3_CTRL_UNION
 �ṹ˵��  : LD2_3_CTRL �Ĵ����ṹ���塣��ַƫ����:0x04A����ֵ:0x11�����:8
 �Ĵ���˵��: LDO2/LDO3���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo3_vrset   : 3;  /* bit[0-2]: LDO3���ص����ʲ���������
                                                       000����������
                                                       001������5mV��
                                                       010������10mV��
                                                       011������15mV��
                                                       100������20mV��
                                                       101������25mV��
                                                       110������30mV��
                                                       111������35mV�� */
        unsigned char  ldo3_ocp_enn : 1;  /* bit[3]  : LDO3����ģʽѡ���źš�
                                                       0����ʾ�澯������
                                                       1����ʾ�澯�������� */
        unsigned char  ldo2_vrset   : 3;  /* bit[4-6]: LDO2���ص����ʲ���������
                                                       000����������
                                                       001������5mV��
                                                       010������10mV��
                                                       011������15mV��
                                                       100������20mV��
                                                       101������25mV��
                                                       110������30mV��
                                                       111������35mV�� */
        unsigned char  ldo2_ocp_enn : 1;  /* bit[7]  : LDO2����ģʽѡ���źš�
                                                       0����ʾ�澯������
                                                       1����ʾ�澯�������� */
    } reg;
} PMIC_LD2_3_CTRL_UNION;
#endif
#define PMIC_LD2_3_CTRL_ldo3_vrset_START    (0)
#define PMIC_LD2_3_CTRL_ldo3_vrset_END      (2)
#define PMIC_LD2_3_CTRL_ldo3_ocp_enn_START  (3)
#define PMIC_LD2_3_CTRL_ldo3_ocp_enn_END    (3)
#define PMIC_LD2_3_CTRL_ldo2_vrset_START    (4)
#define PMIC_LD2_3_CTRL_ldo2_vrset_END      (6)
#define PMIC_LD2_3_CTRL_ldo2_ocp_enn_START  (7)
#define PMIC_LD2_3_CTRL_ldo2_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO4_5_CTRL_UNION
 �ṹ˵��  : LDO4_5_CTRL �Ĵ����ṹ���塣��ַƫ����:0x04B����ֵ:0x11�����:8
 �Ĵ���˵��: LDO4/LDO5���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo5_vrset   : 3;  /* bit[0-2]: LDO5���ص����ʲ���������
                                                       000����������
                                                       001������5mV��
                                                       010������10mV��
                                                       011������15mV��
                                                       100������20mV��
                                                       101������25mV��
                                                       110������30mV��
                                                       111������35mV�� */
        unsigned char  ldo5_ocp_enn : 1;  /* bit[3]  : LDO5����ģʽѡ���źš�
                                                       0����ʾ�澯������
                                                       1����ʾ�澯�������� */
        unsigned char  ldo4_vrset   : 3;  /* bit[4-6]: LDO4���ص����ʲ���������
                                                       000����������
                                                       001������5mV��
                                                       010������10mV��
                                                       011������15mV��
                                                       100������20mV��
                                                       101������25mV��
                                                       110������30mV��
                                                       111������35mV�� */
        unsigned char  ldo4_ocp_enn : 1;  /* bit[7]  : LDO4����ģʽѡ���źš�
                                                       0����ʾ�澯������
                                                       1����ʾ�澯�������� */
    } reg;
} PMIC_LDO4_5_CTRL_UNION;
#endif
#define PMIC_LDO4_5_CTRL_ldo5_vrset_START    (0)
#define PMIC_LDO4_5_CTRL_ldo5_vrset_END      (2)
#define PMIC_LDO4_5_CTRL_ldo5_ocp_enn_START  (3)
#define PMIC_LDO4_5_CTRL_ldo5_ocp_enn_END    (3)
#define PMIC_LDO4_5_CTRL_ldo4_vrset_START    (4)
#define PMIC_LDO4_5_CTRL_ldo4_vrset_END      (6)
#define PMIC_LDO4_5_CTRL_ldo4_ocp_enn_START  (7)
#define PMIC_LDO4_5_CTRL_ldo4_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO7_8_CTRL_UNION
 �ṹ˵��  : LDO7_8_CTRL �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x11�����:8
 �Ĵ���˵��: LDO7/LDO8���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo8_vrset   : 3;  /* bit[0-2]: LDO8���ص����ʲ���������
                                                       000����������
                                                       001������5mV��
                                                       010������10mV��
                                                       011������15mV��
                                                       100������20mV��
                                                       101������25mV��
                                                       110������30mV��
                                                       111������35mV�� */
        unsigned char  ldo8_ocp_enn : 1;  /* bit[3]  : LDO8����ģʽѡ���źš�
                                                       0����ʾ�澯������
                                                       1����ʾ�澯�������� */
        unsigned char  ldo7_vrset   : 3;  /* bit[4-6]: LDO7���ص����ʲ���������
                                                       000����������
                                                       001������5mV��
                                                       010������10mV��
                                                       011������15mV��
                                                       100������20mV��
                                                       101������25mV��
                                                       110������30mV��
                                                       111������35mV�� */
        unsigned char  ldo7_ocp_enn : 1;  /* bit[7]  : LDO7����ģʽѡ���źš�
                                                       0����ʾ�澯������
                                                       1����ʾ�澯�������� */
    } reg;
} PMIC_LDO7_8_CTRL_UNION;
#endif
#define PMIC_LDO7_8_CTRL_ldo8_vrset_START    (0)
#define PMIC_LDO7_8_CTRL_ldo8_vrset_END      (2)
#define PMIC_LDO7_8_CTRL_ldo8_ocp_enn_START  (3)
#define PMIC_LDO7_8_CTRL_ldo8_ocp_enn_END    (3)
#define PMIC_LDO7_8_CTRL_ldo7_vrset_START    (4)
#define PMIC_LDO7_8_CTRL_ldo7_vrset_END      (6)
#define PMIC_LDO7_8_CTRL_ldo7_ocp_enn_START  (7)
#define PMIC_LDO7_8_CTRL_ldo7_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO9_10_CTRL_UNION
 �ṹ˵��  : LDO9_10_CTRL �Ĵ����ṹ���塣��ַƫ����:0x04D����ֵ:0x11�����:8
 �Ĵ���˵��: LDO9/LDO10���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo10_vrset   : 3;  /* bit[0-2]: LDO10���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo10_ocp_enn : 1;  /* bit[3]  : LDO10����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo9_vrset    : 3;  /* bit[4-6]: LDO9���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo9_ocp_enn  : 1;  /* bit[7]  : LDO9����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO9_10_CTRL_UNION;
#endif
#define PMIC_LDO9_10_CTRL_ldo10_vrset_START    (0)
#define PMIC_LDO9_10_CTRL_ldo10_vrset_END      (2)
#define PMIC_LDO9_10_CTRL_ldo10_ocp_enn_START  (3)
#define PMIC_LDO9_10_CTRL_ldo10_ocp_enn_END    (3)
#define PMIC_LDO9_10_CTRL_ldo9_vrset_START     (4)
#define PMIC_LDO9_10_CTRL_ldo9_vrset_END       (6)
#define PMIC_LDO9_10_CTRL_ldo9_ocp_enn_START   (7)
#define PMIC_LDO9_10_CTRL_ldo9_ocp_enn_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_LD11_12_CTRL_UNION
 �ṹ˵��  : LD11_12_CTRL �Ĵ����ṹ���塣��ַƫ����:0x04E����ֵ:0x11�����:8
 �Ĵ���˵��: LDO11/LDO12���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo12_vrset   : 3;  /* bit[0-2]: LDO12���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo12_ocp_enn : 1;  /* bit[3]  : LDO12����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo11_vrset   : 3;  /* bit[4-6]: LDO11���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo11_ocp_enn : 1;  /* bit[7]  : LDO11����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LD11_12_CTRL_UNION;
#endif
#define PMIC_LD11_12_CTRL_ldo12_vrset_START    (0)
#define PMIC_LD11_12_CTRL_ldo12_vrset_END      (2)
#define PMIC_LD11_12_CTRL_ldo12_ocp_enn_START  (3)
#define PMIC_LD11_12_CTRL_ldo12_ocp_enn_END    (3)
#define PMIC_LD11_12_CTRL_ldo11_vrset_START    (4)
#define PMIC_LD11_12_CTRL_ldo11_vrset_END      (6)
#define PMIC_LD11_12_CTRL_ldo11_ocp_enn_START  (7)
#define PMIC_LD11_12_CTRL_ldo11_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO13_14_CTRL_UNION
 �ṹ˵��  : LDO13_14_CTRL �Ĵ����ṹ���塣��ַƫ����:0x04F����ֵ:0x11�����:8
 �Ĵ���˵��: LDO13/LDO14���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo14_vrset   : 3;  /* bit[0-2]: LDO14���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo14_ocp_enn : 1;  /* bit[3]  : LDO14����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo13_vrset   : 3;  /* bit[4-6]: LDO13���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo13_ocp_enn : 1;  /* bit[7]  : LDO13����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO13_14_CTRL_UNION;
#endif
#define PMIC_LDO13_14_CTRL_ldo14_vrset_START    (0)
#define PMIC_LDO13_14_CTRL_ldo14_vrset_END      (2)
#define PMIC_LDO13_14_CTRL_ldo14_ocp_enn_START  (3)
#define PMIC_LDO13_14_CTRL_ldo14_ocp_enn_END    (3)
#define PMIC_LDO13_14_CTRL_ldo13_vrset_START    (4)
#define PMIC_LDO13_14_CTRL_ldo13_vrset_END      (6)
#define PMIC_LDO13_14_CTRL_ldo13_ocp_enn_START  (7)
#define PMIC_LDO13_14_CTRL_ldo13_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO15_16_CTRL_UNION
 �ṹ˵��  : LDO15_16_CTRL �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x11�����:8
 �Ĵ���˵��: LDO15/LDO16���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo16_vrset   : 3;  /* bit[0-2]: LDO16���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo16_ocp_enn : 1;  /* bit[3]  : LDO16����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo15_vrset   : 3;  /* bit[4-6]: LDO15���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo15_ocp_enn : 1;  /* bit[7]  : LDO15����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO15_16_CTRL_UNION;
#endif
#define PMIC_LDO15_16_CTRL_ldo16_vrset_START    (0)
#define PMIC_LDO15_16_CTRL_ldo16_vrset_END      (2)
#define PMIC_LDO15_16_CTRL_ldo16_ocp_enn_START  (3)
#define PMIC_LDO15_16_CTRL_ldo16_ocp_enn_END    (3)
#define PMIC_LDO15_16_CTRL_ldo15_vrset_START    (4)
#define PMIC_LDO15_16_CTRL_ldo15_vrset_END      (6)
#define PMIC_LDO15_16_CTRL_ldo15_ocp_enn_START  (7)
#define PMIC_LDO15_16_CTRL_ldo15_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO17_19_CTRL_UNION
 �ṹ˵��  : LDO17_19_CTRL �Ĵ����ṹ���塣��ַƫ����:0x051����ֵ:0x11�����:8
 �Ĵ���˵��: LDO17/LDO19���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo19_vrset   : 3;  /* bit[0-2]: LDO19���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo19_ocp_enn : 1;  /* bit[3]  : LDO19����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo17_vrset   : 3;  /* bit[4-6]: LDO17���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo17_ocp_enn : 1;  /* bit[7]  : LDO17����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO17_19_CTRL_UNION;
#endif
#define PMIC_LDO17_19_CTRL_ldo19_vrset_START    (0)
#define PMIC_LDO17_19_CTRL_ldo19_vrset_END      (2)
#define PMIC_LDO17_19_CTRL_ldo19_ocp_enn_START  (3)
#define PMIC_LDO17_19_CTRL_ldo19_ocp_enn_END    (3)
#define PMIC_LDO17_19_CTRL_ldo17_vrset_START    (4)
#define PMIC_LDO17_19_CTRL_ldo17_vrset_END      (6)
#define PMIC_LDO17_19_CTRL_ldo17_ocp_enn_START  (7)
#define PMIC_LDO17_19_CTRL_ldo17_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO20_21_CTRL_UNION
 �ṹ˵��  : LDO20_21_CTRL �Ĵ����ṹ���塣��ַƫ����:0x052����ֵ:0x11�����:8
 �Ĵ���˵��: LDO20/LDO21���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo21_vrset   : 3;  /* bit[0-2]: LDO21���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo21_ocp_enn : 1;  /* bit[3]  : LDO21����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo20_vrset   : 3;  /* bit[4-6]: LDO20���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo20_ocp_enn : 1;  /* bit[7]  : LDO20����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO20_21_CTRL_UNION;
#endif
#define PMIC_LDO20_21_CTRL_ldo21_vrset_START    (0)
#define PMIC_LDO20_21_CTRL_ldo21_vrset_END      (2)
#define PMIC_LDO20_21_CTRL_ldo21_ocp_enn_START  (3)
#define PMIC_LDO20_21_CTRL_ldo21_ocp_enn_END    (3)
#define PMIC_LDO20_21_CTRL_ldo20_vrset_START    (4)
#define PMIC_LDO20_21_CTRL_ldo20_vrset_END      (6)
#define PMIC_LDO20_21_CTRL_ldo20_ocp_enn_START  (7)
#define PMIC_LDO20_21_CTRL_ldo20_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO22_23_CTRL_UNION
 �ṹ˵��  : LDO22_23_CTRL �Ĵ����ṹ���塣��ַƫ����:0x053����ֵ:0x11�����:8
 �Ĵ���˵��: LDO22/LDO23���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo23_vrset   : 3;  /* bit[0-2]: LDO23���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo23_ocp_enn : 1;  /* bit[3]  : LDO23����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo22_vrset   : 3;  /* bit[4-6]: LDO22���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo22_ocp_enn : 1;  /* bit[7]  : LDO22����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO22_23_CTRL_UNION;
#endif
#define PMIC_LDO22_23_CTRL_ldo23_vrset_START    (0)
#define PMIC_LDO22_23_CTRL_ldo23_vrset_END      (2)
#define PMIC_LDO22_23_CTRL_ldo23_ocp_enn_START  (3)
#define PMIC_LDO22_23_CTRL_ldo23_ocp_enn_END    (3)
#define PMIC_LDO22_23_CTRL_ldo22_vrset_START    (4)
#define PMIC_LDO22_23_CTRL_ldo22_vrset_END      (6)
#define PMIC_LDO22_23_CTRL_ldo22_ocp_enn_START  (7)
#define PMIC_LDO22_23_CTRL_ldo22_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO24_25_CTRL_UNION
 �ṹ˵��  : LDO24_25_CTRL �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x11�����:8
 �Ĵ���˵��: LDO24/LDO25���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo25_vrset   : 3;  /* bit[0-2]: LDO25���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo25_ocp_enn : 1;  /* bit[3]  : LDO25����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo24_vrset   : 3;  /* bit[4-6]: LDO24���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo24_ocp_enn : 1;  /* bit[7]  : LDO24����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO24_25_CTRL_UNION;
#endif
#define PMIC_LDO24_25_CTRL_ldo25_vrset_START    (0)
#define PMIC_LDO24_25_CTRL_ldo25_vrset_END      (2)
#define PMIC_LDO24_25_CTRL_ldo25_ocp_enn_START  (3)
#define PMIC_LDO24_25_CTRL_ldo25_ocp_enn_END    (3)
#define PMIC_LDO24_25_CTRL_ldo24_vrset_START    (4)
#define PMIC_LDO24_25_CTRL_ldo24_vrset_END      (6)
#define PMIC_LDO24_25_CTRL_ldo24_ocp_enn_START  (7)
#define PMIC_LDO24_25_CTRL_ldo24_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO26_27_CTRL_UNION
 �ṹ˵��  : LDO26_27_CTRL �Ĵ����ṹ���塣��ַƫ����:0x055����ֵ:0x11�����:8
 �Ĵ���˵��: LDO26/LDO27���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo27_vrset   : 3;  /* bit[0-2]: LDO27���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo27_ocp_enn : 1;  /* bit[3]  : LDO27����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo26_vrset   : 3;  /* bit[4-6]: LDO26���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo26_ocp_enn : 1;  /* bit[7]  : LDO26����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO26_27_CTRL_UNION;
#endif
#define PMIC_LDO26_27_CTRL_ldo27_vrset_START    (0)
#define PMIC_LDO26_27_CTRL_ldo27_vrset_END      (2)
#define PMIC_LDO26_27_CTRL_ldo27_ocp_enn_START  (3)
#define PMIC_LDO26_27_CTRL_ldo27_ocp_enn_END    (3)
#define PMIC_LDO26_27_CTRL_ldo26_vrset_START    (4)
#define PMIC_LDO26_27_CTRL_ldo26_vrset_END      (6)
#define PMIC_LDO26_27_CTRL_ldo26_ocp_enn_START  (7)
#define PMIC_LDO26_27_CTRL_ldo26_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO28_29_CTRL_UNION
 �ṹ˵��  : LDO28_29_CTRL �Ĵ����ṹ���塣��ַƫ����:0x056����ֵ:0x11�����:8
 �Ĵ���˵��: LDO28/LDO29���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo29_vrset   : 3;  /* bit[0-2]: LDO29���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo29_ocp_enn : 1;  /* bit[3]  : LDO29����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo28_vrset   : 3;  /* bit[4-6]: LDO28���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo28_ocp_enn : 1;  /* bit[7]  : LDO28����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO28_29_CTRL_UNION;
#endif
#define PMIC_LDO28_29_CTRL_ldo29_vrset_START    (0)
#define PMIC_LDO28_29_CTRL_ldo29_vrset_END      (2)
#define PMIC_LDO28_29_CTRL_ldo29_ocp_enn_START  (3)
#define PMIC_LDO28_29_CTRL_ldo29_ocp_enn_END    (3)
#define PMIC_LDO28_29_CTRL_ldo28_vrset_START    (4)
#define PMIC_LDO28_29_CTRL_ldo28_vrset_END      (6)
#define PMIC_LDO28_29_CTRL_ldo28_ocp_enn_START  (7)
#define PMIC_LDO28_29_CTRL_ldo28_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO30_31_CTRL_UNION
 �ṹ˵��  : LDO30_31_CTRL �Ĵ����ṹ���塣��ַƫ����:0x057����ֵ:0x11�����:8
 �Ĵ���˵��: LDO30/LDO31���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo31_vrset   : 3;  /* bit[0-2]: LDO31���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo31_ocp_enn : 1;  /* bit[3]  : LDO31����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  ldo30_vrset   : 3;  /* bit[4-6]: LDO30���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo30_ocp_enn : 1;  /* bit[7]  : LDO30����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
    } reg;
} PMIC_LDO30_31_CTRL_UNION;
#endif
#define PMIC_LDO30_31_CTRL_ldo31_vrset_START    (0)
#define PMIC_LDO30_31_CTRL_ldo31_vrset_END      (2)
#define PMIC_LDO30_31_CTRL_ldo31_ocp_enn_START  (3)
#define PMIC_LDO30_31_CTRL_ldo31_ocp_enn_END    (3)
#define PMIC_LDO30_31_CTRL_ldo30_vrset_START    (4)
#define PMIC_LDO30_31_CTRL_ldo30_vrset_END      (6)
#define PMIC_LDO30_31_CTRL_ldo30_ocp_enn_START  (7)
#define PMIC_LDO30_31_CTRL_ldo30_ocp_enn_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO32_CTRL_UNION
 �ṹ˵��  : LDO32_CTRL �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x01�����:8
 �Ĵ���˵��: LDO32���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo32_vrset   : 3;  /* bit[0-2]: LDO32���ص����ʲ���������
                                                        000����������
                                                        001������5mV��
                                                        010������10mV��
                                                        011������15mV��
                                                        100������20mV��
                                                        101������25mV��
                                                        110������30mV��
                                                        111������35mV�� */
        unsigned char  ldo32_ocp_enn : 1;  /* bit[3]  : LDO32����ģʽѡ���źš�
                                                        0����ʾ�澯������
                                                        1����ʾ�澯�������� */
        unsigned char  reserved      : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO32_CTRL_UNION;
#endif
#define PMIC_LDO32_CTRL_ldo32_vrset_START    (0)
#define PMIC_LDO32_CTRL_ldo32_vrset_END      (2)
#define PMIC_LDO32_CTRL_ldo32_ocp_enn_START  (3)
#define PMIC_LDO32_CTRL_ldo32_ocp_enn_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO0_1_ONOFF_UNION
 �ṹ˵��  : LDO0_1_ONOFF �Ĵ����ṹ���塣��ַƫ����:0x059����ֵ:0x00�����:8
 �Ĵ���˵��: LDO0_1����ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0    : 4;  /* bit[0-3]: ������ */
        unsigned char  reg_ldo0_1_en : 1;  /* bit[4]  : LDO0_1ʹ���źš�
                                                        0���رգ�
                                                        1��ʹ�ܡ� */
        unsigned char  reserved_1    : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_LDO0_1_ONOFF_UNION;
#endif
#define PMIC_LDO0_1_ONOFF_reg_ldo0_1_en_START  (4)
#define PMIC_LDO0_1_ONOFF_reg_ldo0_1_en_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_LDO0_2_ONOFF_ECO_UNION
 �ṹ˵��  : LDO0_2_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x05A����ֵ:0x02�����:8
 �Ĵ���˵��: LDO0_2���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo0_2_eco_en : 1;  /* bit[0]  : LDO0_2����͹���ECOģʽ�����źš�
                                                            0��normalģʽ��
                                                            1��ECOģʽ�� */
        unsigned char  reg_ldo0_2_en     : 1;  /* bit[1]  : LDO0_2ʹ���źš�
                                                            0���رգ�
                                                            1��ʹ�ܡ� */
        unsigned char  reserved          : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO0_2_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_eco_en_START  (0)
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_eco_en_END    (0)
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_en_START      (1)
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO0_2_VSET_UNION
 �ṹ˵��  : LDO0_2_VSET �Ĵ����ṹ���塣��ַƫ����:0x05B����ֵ:0x55�����:8
 �Ĵ���˵��: LDO0_2��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo0_2_vset     : 3;  /* bit[0-2]: LDO0_2�����ѹ���á�
                                                          000��0.600V��
                                                          001��0.650V��
                                                          010��0.700V��
                                                          011��0.750V��
                                                          100��0.775V��
                                                          101��0.800V��
                                                          110��0.825V��
                                                          111��0.850V�� */
        unsigned char  reserved_0      : 1;  /* bit[3]  : ���� */
        unsigned char  ldo0_2_vset_adj : 3;  /* bit[4-6]: LDO0_2�����ѹֵ��PERI_EN��Чʱ�����óɲ�ͬ��λ��ֵ��
                                                          000��0.600V��
                                                          001��0.650V��
                                                          010��0.700V��
                                                          011��0.750V��
                                                          100��0.775V��
                                                          101��0.800V��
                                                          110��0.825V��
                                                          111��0.850V�� */
        unsigned char  reserved_1      : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_LDO0_2_VSET_UNION;
#endif
#define PMIC_LDO0_2_VSET_ldo0_2_vset_START      (0)
#define PMIC_LDO0_2_VSET_ldo0_2_vset_END        (2)
#define PMIC_LDO0_2_VSET_ldo0_2_vset_adj_START  (4)
#define PMIC_LDO0_2_VSET_ldo0_2_vset_adj_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_LDO1_ONOFF_ECO_UNION
 �ṹ˵��  : LDO1_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00�����:8
 �Ĵ���˵��: LDO1���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo1_eco_en : 1;  /* bit[0]  : LDO1����͹���ECOģʽ�����źš�
                                                          0��normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reg_ldo1_en     : 1;  /* bit[1]  : LDO1ʹ���źš�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  reserved        : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO1_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO1_ONOFF_ECO_reg_ldo1_eco_en_START  (0)
#define PMIC_LDO1_ONOFF_ECO_reg_ldo1_eco_en_END    (0)
#define PMIC_LDO1_ONOFF_ECO_reg_ldo1_en_START      (1)
#define PMIC_LDO1_ONOFF_ECO_reg_ldo1_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO1_VSET_UNION
 �ṹ˵��  : LDO1_VSET �Ĵ����ṹ���塣��ַƫ����:0x05D����ֵ:0x00�����:8
 �Ĵ���˵��: LDO1��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo1_vset : 4;  /* bit[0-3]: LDO1�����ѹ���ã�Ĭ�ϵ�ѹ1.0V��
                                                    0000��1.00V��
                                                    0001��1.05V��
                                                    0010��1.10V��
                                                    0011��1.15V��
                                                    0100��1.20V��
                                                    0101��1.25V��
                                                    0110��1.26V��
                                                    0111��1.27V��
                                                    1000��1.28V��
                                                    1001��1.29V��
                                                    1010��1.30V��
                                                    1011��1.31V��
                                                    1100��1.32V��
                                                    1101��1.33V��
                                                    1110��1.34V��
                                                    1111��1.50V�� */
        unsigned char  reserved  : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO1_VSET_UNION;
#endif
#define PMIC_LDO1_VSET_ldo1_vset_START  (0)
#define PMIC_LDO1_VSET_ldo1_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO2_ONOFF_ECO_UNION
 �ṹ˵��  : LDO2_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x05E����ֵ:0x02�����:8
 �Ĵ���˵��: LDO2���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo2_eco_en : 1;  /* bit[0]  : LDO2����͹���ECOģʽ�����źš�
                                                          0��normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reg_ldo2_en     : 1;  /* bit[1]  : LDO2ʹ���źš�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  reserved        : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO2_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_eco_en_START  (0)
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_eco_en_END    (0)
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_en_START      (1)
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO2_VSET_UNION
 �ṹ˵��  : LDO2_VSET �Ĵ����ṹ���塣��ַƫ����:0x05F����ֵ:0x33�����:8
 �Ĵ���˵��: LDO2��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo2_vset     : 3;  /* bit[0-2]: LDO2�����ѹ���á�
                                                        000��1.700V��
                                                        001��1.750V��
                                                        010��1.775V��
                                                        011��1.800V��
                                                        100��1.825V��
                                                        101��1.850V��
                                                        110��1.875V��
                                                        111��1.900V�� */
        unsigned char  reserved_0    : 1;  /* bit[3]  : ������ */
        unsigned char  ldo2_vset_adj : 3;  /* bit[4-6]: LDO2�����ѹֵ��PERI_EN��Чʱ�����óɲ�ͬ��λ��ֵ��
                                                        000��1.700V��
                                                        001��1.750V��
                                                        010��1.775V��
                                                        011��1.800V��
                                                        100��1.825V��
                                                        101��1.850V��
                                                        110��1.875V��
                                                        111��1.900V�� */
        unsigned char  reserved_1    : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_LDO2_VSET_UNION;
#endif
#define PMIC_LDO2_VSET_ldo2_vset_START      (0)
#define PMIC_LDO2_VSET_ldo2_vset_END        (2)
#define PMIC_LDO2_VSET_ldo2_vset_adj_START  (4)
#define PMIC_LDO2_VSET_ldo2_vset_adj_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_LDO3_ONOFF_ECO_UNION
 �ṹ˵��  : LDO3_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00�����:8
 �Ĵ���˵��: LDO3���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo3_eco_en : 1;  /* bit[0]  : LDO3����͹���ECOģʽ�����źš�
                                                          0��normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reg_ldo3_en     : 1;  /* bit[1]  : LDO3ʹ���źš�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  reserved        : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO3_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO3_ONOFF_ECO_reg_ldo3_eco_en_START  (0)
#define PMIC_LDO3_ONOFF_ECO_reg_ldo3_eco_en_END    (0)
#define PMIC_LDO3_ONOFF_ECO_reg_ldo3_en_START      (1)
#define PMIC_LDO3_ONOFF_ECO_reg_ldo3_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO3_VSET_UNION
 �ṹ˵��  : LDO3_VSET �Ĵ����ṹ���塣��ַƫ����:0x061����ֵ:0x00�����:8
 �Ĵ���˵��: LDO3��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo3_vset : 4;  /* bit[0-3]: LDO3�����ѹ���á�
                                                    0000��1.800V��
                                                    0001��1.825V��
                                                    0010��1.850V��
                                                    0011��1.875V��
                                                    0100��1.900V��
                                                    0101��1.925V��
                                                    0110��1.950V��
                                                    0111��1.975V��
                                                    1000��2.000V��
                                                    1001��2.025V��
                                                    1010��2.050V��
                                                    1011��2.075V��
                                                    1100��2.100V��
                                                    1101��2.125V��
                                                    1110��2.150V��
                                                    1111��2.200V�� */
        unsigned char  reserved  : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO3_VSET_UNION;
#endif
#define PMIC_LDO3_VSET_ldo3_vset_START  (0)
#define PMIC_LDO3_VSET_ldo3_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO4_ONOFF_ECO_UNION
 �ṹ˵��  : LDO4_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x062����ֵ:0x00�����:8
 �Ĵ���˵��: LDO4���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo4_eco_en : 1;  /* bit[0]  : LDO4����͹���ECOģʽ�����źš�
                                                          0��normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reg_ldo4_en     : 1;  /* bit[1]  : LDO4ʹ���źš�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  reserved        : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO4_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_eco_en_START  (0)
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_eco_en_END    (0)
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_en_START      (1)
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO4_VSET_UNION
 �ṹ˵��  : LDO4_VSET �Ĵ����ṹ���塣��ַƫ����:0x063����ֵ:0x00�����:8
 �Ĵ���˵��: LDO4��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo4_vset : 3;  /* bit[0-2]: LDO4�����ѹ���á�
                                                    000��1.700V��
                                                    001��1.750V��
                                                    010��1.775V��
                                                    011��1.800V��
                                                    100��1.825V��
                                                    101��1.850V��
                                                    110��1.875V��
                                                    111��1.900V�� */
        unsigned char  reserved  : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO4_VSET_UNION;
#endif
#define PMIC_LDO4_VSET_ldo4_vset_START  (0)
#define PMIC_LDO4_VSET_ldo4_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO5_ONOFF_ECO_UNION
 �ṹ˵��  : LDO5_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x02�����:8
 �Ĵ���˵��: LDO5���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo5_eco_en : 1;  /* bit[0]  : LDO5����͹���ECOģʽ�����źš�
                                                          0��normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reg_ldo5_en     : 1;  /* bit[1]  : LDO5ʹ���źš�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  reserved        : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO5_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO5_ONOFF_ECO_reg_ldo5_eco_en_START  (0)
#define PMIC_LDO5_ONOFF_ECO_reg_ldo5_eco_en_END    (0)
#define PMIC_LDO5_ONOFF_ECO_reg_ldo5_en_START      (1)
#define PMIC_LDO5_ONOFF_ECO_reg_ldo5_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO5_VSET_UNION
 �ṹ˵��  : LDO5_VSET �Ĵ����ṹ���塣��ַƫ����:0x065����ֵ:0x03�����:8
 �Ĵ���˵��: LDO5��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo5_vset : 3;  /* bit[0-2]: LDO5�����ѹ���á�
                                                    000��1.7V��
                                                    001��1.75V��
                                                    010��1.775V��
                                                    011��1.8V��
                                                    100��1.825V��
                                                    101��1.85V��
                                                    110��1.9V��
                                                    111��1.95V�� */
        unsigned char  reserved  : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO5_VSET_UNION;
#endif
#define PMIC_LDO5_VSET_ldo5_vset_START  (0)
#define PMIC_LDO5_VSET_ldo5_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO7_ONOFF_ECO_UNION
 �ṹ˵��  : LDO7_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x066����ֵ:0x02�����:8
 �Ĵ���˵��: LDO7���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo7_eco_en : 1;  /* bit[0]  : LDO7����͹���ECOģʽ�����źš�
                                                          0��normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reg_ldo7_en     : 1;  /* bit[1]  : LDO7ʹ���źš�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  reserved        : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO7_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO7_ONOFF_ECO_reg_ldo7_eco_en_START  (0)
#define PMIC_LDO7_ONOFF_ECO_reg_ldo7_eco_en_END    (0)
#define PMIC_LDO7_ONOFF_ECO_reg_ldo7_en_START      (1)
#define PMIC_LDO7_ONOFF_ECO_reg_ldo7_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO7_VSET_UNION
 �ṹ˵��  : LDO7_VSET �Ĵ����ṹ���塣��ַƫ����:0x067����ֵ:0x03�����:8
 �Ĵ���˵��: LDO7��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo7_vset : 3;  /* bit[0-2]: LDO7�����ѹ���á�
                                                    000��1.7V��
                                                    001��1.75V��
                                                    010��1.775V��
                                                    011��1.8V��
                                                    100��1.825V��
                                                    101��1.85V��
                                                    110��1.9V��
                                                    111��1.95V�� */
        unsigned char  reserved  : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO7_VSET_UNION;
#endif
#define PMIC_LDO7_VSET_ldo7_vset_START  (0)
#define PMIC_LDO7_VSET_ldo7_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO8_ONOFF_ECO_UNION
 �ṹ˵��  : LDO8_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x02�����:8
 �Ĵ���˵��: LDO8���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo8_eco_en : 1;  /* bit[0]  : LDO8����͹���ECOģʽ�����źš�
                                                          0��normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reg_ldo8_en     : 1;  /* bit[1]  : LDO8ʹ���źš�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  reserved        : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO8_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_eco_en_START  (0)
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_eco_en_END    (0)
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_en_START      (1)
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO8_VSET_UNION
 �ṹ˵��  : LDO8_VSET �Ĵ����ṹ���塣��ַƫ����:0x069����ֵ:0x03�����:8
 �Ĵ���˵��: LDO8��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo8_vset : 4;  /* bit[0-3]: LDO8�����ѹ���ã�ldo8_vset[3]��ʹ�á�
                                                    000��1.7V��
                                                    001��1.75V��
                                                    010��1.775V��
                                                    011��1.8V��
                                                    100��1.825V��
                                                    101��1.850V��
                                                    110��1.900V��
                                                    111��1.950V�� */
        unsigned char  reserved  : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO8_VSET_UNION;
#endif
#define PMIC_LDO8_VSET_ldo8_vset_START  (0)
#define PMIC_LDO8_VSET_ldo8_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO9_ONOFF_ECO_UNION
 �ṹ˵��  : LDO9_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x06A����ֵ:0x00�����:8
 �Ĵ���˵��: LDO9���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo9_eco_en : 1;  /* bit[0]  : LDO9����͹���ECOģʽ�����źš�
                                                          0��normalģʽ��
                                                          1��ECOģʽ�� */
        unsigned char  reg_ldo9_en     : 1;  /* bit[1]  : LDO9ʹ���źš�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  reserved        : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO9_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_eco_en_START  (0)
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_eco_en_END    (0)
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_en_START      (1)
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO9_VSET_UNION
 �ṹ˵��  : LDO9_VSET �Ĵ����ṹ���塣��ַƫ����:0x06B����ֵ:0x00�����:8
 �Ĵ���˵��: LDO9��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo9_vset : 3;  /* bit[0-2]: LDO9�����ѹ���á�
                                                    000��1.75V��
                                                    001��1.8V��
                                                    010��1.825V��
                                                    011��2.8V��
                                                    100��2.85V��
                                                    101��2.95V��
                                                    110��3.0V��
                                                    111��3.3V�� */
        unsigned char  reserved  : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO9_VSET_UNION;
#endif
#define PMIC_LDO9_VSET_ldo9_vset_START  (0)
#define PMIC_LDO9_VSET_ldo9_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO10_ONOFF_ECO_UNION
 �ṹ˵��  : LDO10_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x02�����:8
 �Ĵ���˵��: LDO10���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo10_eco_en : 1;  /* bit[0]  : LDO10����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo10_en     : 1;  /* bit[1]  : LDO10ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO10_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_eco_en_START  (0)
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_eco_en_END    (0)
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_en_START      (1)
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO10_VSET_UNION
 �ṹ˵��  : LDO10_VSET �Ĵ����ṹ���塣��ַƫ����:0x06D����ֵ:0x02�����:8
 �Ĵ���˵��: LDO10��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo10_vset : 3;  /* bit[0-2]: LDO10�����ѹ���á�
                                                     000��3.1V��
                                                     001��3.15V��
                                                     010��3.2V��
                                                     011��3.3V��
                                                     ������3.3V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO10_VSET_UNION;
#endif
#define PMIC_LDO10_VSET_ldo10_vset_START  (0)
#define PMIC_LDO10_VSET_ldo10_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO11_ONOFF_ECO_UNION
 �ṹ˵��  : LDO11_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x06E����ֵ:0x00�����:8
 �Ĵ���˵��: LDO11���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo11_eco_en : 1;  /* bit[0]  : LDO11����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo11_en     : 1;  /* bit[1]  : LDO11ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO11_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_eco_en_START  (0)
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_eco_en_END    (0)
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_en_START      (1)
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO11_VSET_UNION
 �ṹ˵��  : LDO11_VSET �Ĵ����ṹ���塣��ַƫ����:0x06F����ֵ:0x00�����:8
 �Ĵ���˵��: LDO11��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo11_vset : 3;  /* bit[0-2]: LDO11�����ѹ���á�
                                                     000��1.75V��
                                                     001��1.8V��
                                                     010��1.825V��
                                                     011��2.8V��
                                                     100��2.85V��
                                                     101��2.95V��
                                                     110��3.0V��
                                                     111��3.3V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO11_VSET_UNION;
#endif
#define PMIC_LDO11_VSET_ldo11_vset_START  (0)
#define PMIC_LDO11_VSET_ldo11_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO12_ONOFF_ECO_UNION
 �ṹ˵��  : LDO12_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00�����:8
 �Ĵ���˵��: LDO12���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo12_eco_en : 1;  /* bit[0]  : LDO12����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo12_en     : 1;  /* bit[1]  : LDO12ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO12_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_eco_en_START  (0)
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_eco_en_END    (0)
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_en_START      (1)
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO12_VSET_UNION
 �ṹ˵��  : LDO12_VSET �Ĵ����ṹ���塣��ַƫ����:0x071����ֵ:0x00�����:8
 �Ĵ���˵��: LDO12��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo12_vset : 3;  /* bit[0-2]: LDO12�����ѹ���á�
                                                     000��1.75V��
                                                     001��1.8V��
                                                     010��1.825V��
                                                     011��2.8V��
                                                     100��2.85V��
                                                     101��2.95V��
                                                     110��3.0V��
                                                     111��3.3V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO12_VSET_UNION;
#endif
#define PMIC_LDO12_VSET_ldo12_vset_START  (0)
#define PMIC_LDO12_VSET_ldo12_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO13_ONOFF_ECO_UNION
 �ṹ˵��  : LDO13_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x072����ֵ:0x00�����:8
 �Ĵ���˵��: LDO13���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo13_eco_en : 1;  /* bit[0]  : LDO13����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo13_en     : 1;  /* bit[1]  : LDO13ʹ���ź�(Ĭ�ϲ���������ͨ��OTP����Ĭ�Ͽ�����Ĭ��ֵΪ1��)��
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO13_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO13_ONOFF_ECO_reg_ldo13_eco_en_START  (0)
#define PMIC_LDO13_ONOFF_ECO_reg_ldo13_eco_en_END    (0)
#define PMIC_LDO13_ONOFF_ECO_reg_ldo13_en_START      (1)
#define PMIC_LDO13_ONOFF_ECO_reg_ldo13_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO13_VSET_UNION
 �ṹ˵��  : LDO13_VSET �Ĵ����ṹ���塣��ַƫ����:0x073����ֵ:0x04�����:8
 �Ĵ���˵��: LDO13��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo13_vset : 3;  /* bit[0-2]: LDO13�����ѹ���á�
                                                     000��1.75V��
                                                     001��1.8V��
                                                     010��1.825V��
                                                     011��2.8V��
                                                     100��2.85V��
                                                     101��2.95V��
                                                     110��3.0V��
                                                     111��3.3V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO13_VSET_UNION;
#endif
#define PMIC_LDO13_VSET_ldo13_vset_START  (0)
#define PMIC_LDO13_VSET_ldo13_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO14_ONOFF_ECO_UNION
 �ṹ˵��  : LDO14_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00�����:8
 �Ĵ���˵��: LDO14���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo14_eco_en : 1;  /* bit[0]  : LDO14����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo14_en     : 1;  /* bit[1]  : LDO14ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO14_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO14_ONOFF_ECO_reg_ldo14_eco_en_START  (0)
#define PMIC_LDO14_ONOFF_ECO_reg_ldo14_eco_en_END    (0)
#define PMIC_LDO14_ONOFF_ECO_reg_ldo14_en_START      (1)
#define PMIC_LDO14_ONOFF_ECO_reg_ldo14_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO14_VSET_UNION
 �ṹ˵��  : LDO14_VSET �Ĵ����ṹ���塣��ַƫ����:0x075����ֵ:0x00�����:8
 �Ĵ���˵��: LDO14��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo14_vset : 3;  /* bit[0-2]: LDO14�����ѹ���á�
                                                     000��1.75V��
                                                     001��1.8V��
                                                     010��1.825V��
                                                     011��2.8V��
                                                     100��2.85V��
                                                     101��2.95V��
                                                     110��3.0V��
                                                     111��3.3V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO14_VSET_UNION;
#endif
#define PMIC_LDO14_VSET_ldo14_vset_START  (0)
#define PMIC_LDO14_VSET_ldo14_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO15_ONOFF_ECO_UNION
 �ṹ˵��  : LDO15_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x076����ֵ:0x02�����:8
 �Ĵ���˵��: LDO15���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo15_eco_en : 1;  /* bit[0]  : LDO15����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo15_en     : 1;  /* bit[1]  : LDO15ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO15_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_eco_en_START  (0)
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_eco_en_END    (0)
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_en_START      (1)
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO15_VSET_UNION
 �ṹ˵��  : LDO15_VSET �Ĵ����ṹ���塣��ַƫ����:0x077����ֵ:0x07�����:8
 �Ĵ���˵��: LDO15��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo15_vset : 3;  /* bit[0-2]: LDO15�����ѹ���á�
                                                     000��1.75V��
                                                     001��1.8V��
                                                     010��2.4V��
                                                     011��2.6V��
                                                     100��2.7V��
                                                     101��2.85V��
                                                     110��2.95V��
                                                     111��3.0V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO15_VSET_UNION;
#endif
#define PMIC_LDO15_VSET_ldo15_vset_START  (0)
#define PMIC_LDO15_VSET_ldo15_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO16_ONOFF_ECO_UNION
 �ṹ˵��  : LDO16_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00�����:8
 �Ĵ���˵��: LDO16���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo16_eco_en : 1;  /* bit[0]  : LDO16����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo16_en     : 1;  /* bit[1]  : LDO16ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO16_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_eco_en_START  (0)
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_eco_en_END    (0)
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_en_START      (1)
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO16_VSET_UNION
 �ṹ˵��  : LDO16_VSET �Ĵ����ṹ���塣��ַƫ����:0x079����ֵ:0x00�����:8
 �Ĵ���˵��: LDO16��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo16_vset : 3;  /* bit[0-2]: LDO16�����ѹ���á�
                                                     000��1.75V��
                                                     001��1.8V��
                                                     010��2.4V��
                                                     011��2.6V��
                                                     100��2.7V��
                                                     101��2.85V��
                                                     110��2.95V��
                                                     111��3.0V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO16_VSET_UNION;
#endif
#define PMIC_LDO16_VSET_ldo16_vset_START  (0)
#define PMIC_LDO16_VSET_ldo16_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO17_ONOFF_ECO_UNION
 �ṹ˵��  : LDO17_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x07A����ֵ:0x00�����:8
 �Ĵ���˵��: LDO17���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo17_eco_en : 1;  /* bit[0]  : LDO17����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo17_en     : 1;  /* bit[1]  : LDO17ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO17_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_eco_en_START  (0)
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_eco_en_END    (0)
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_en_START      (1)
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO17_VSET_UNION
 �ṹ˵��  : LDO17_VSET �Ĵ����ṹ���塣��ַƫ����:0x07B����ֵ:0x00�����:8
 �Ĵ���˵��: LDO17��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo17_vset : 3;  /* bit[0-2]: LDO17�����ѹ���á�
                                                     000��2.6V��
                                                     001��2.7V��
                                                     010��2.8V��
                                                     011��2.85V��
                                                     100��3.0V��
                                                     101��3.1V��
                                                     110��3.2V��
                                                     111��3.3V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO17_VSET_UNION;
#endif
#define PMIC_LDO17_VSET_ldo17_vset_START  (0)
#define PMIC_LDO17_VSET_ldo17_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO19_ONOFF_ECO_UNION
 �ṹ˵��  : LDO19_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00�����:8
 �Ĵ���˵��: LDO19���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo19_eco_en : 1;  /* bit[0]  : LDO19����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo19_en     : 1;  /* bit[1]  : LDO19ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO19_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO19_ONOFF_ECO_reg_ldo19_eco_en_START  (0)
#define PMIC_LDO19_ONOFF_ECO_reg_ldo19_eco_en_END    (0)
#define PMIC_LDO19_ONOFF_ECO_reg_ldo19_en_START      (1)
#define PMIC_LDO19_ONOFF_ECO_reg_ldo19_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO19_VSET1_UNION
 �ṹ˵��  : LDO19_VSET1 �Ĵ����ṹ���塣��ַƫ����:0x07D����ֵ:0x00�����:8
 �Ĵ���˵��: LDO19��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo19_vset : 3;  /* bit[0-2]: LDO19�����ѹ���á�
                                                     000��1.8V��
                                                     001��2.6V��
                                                     010��2.7V��
                                                     011��2.75V��
                                                     100��2.8V��
                                                     101��2.85V��
                                                     110��2.9V��
                                                     111��3.0V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO19_VSET1_UNION;
#endif
#define PMIC_LDO19_VSET1_ldo19_vset_START  (0)
#define PMIC_LDO19_VSET1_ldo19_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO20_ONOFF_ECO_UNION
 �ṹ˵��  : LDO20_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x07E����ֵ:0x00�����:8
 �Ĵ���˵��: LDO20���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo20_eco_en : 1;  /* bit[0]  : LDO20����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo20_en     : 1;  /* bit[1]  : LDO20ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO20_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO20_ONOFF_ECO_reg_ldo20_eco_en_START  (0)
#define PMIC_LDO20_ONOFF_ECO_reg_ldo20_eco_en_END    (0)
#define PMIC_LDO20_ONOFF_ECO_reg_ldo20_en_START      (1)
#define PMIC_LDO20_ONOFF_ECO_reg_ldo20_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO20_VSET_UNION
 �ṹ˵��  : LDO20_VSET �Ĵ����ṹ���塣��ַƫ����:0x07F����ֵ:0x00�����:8
 �Ĵ���˵��: LDO20��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo20_vset : 4;  /* bit[0-3]: LDO20�����ѹ���á�
                                                     0000��0.80V��
                                                     0001��0.85V��
                                                     0010��0.90V��
                                                     0011��0.95V��
                                                     0100��1.00V��
                                                     0101��1.05V��
                                                     0110��1.10V��
                                                     0111��1.20V��
                                                     1000��1.25V��
                                                     1001��1.26V��
                                                     1010��1.27V��
                                                     1011��1.28V��
                                                     1100��1.29V��
                                                     1101��1.30V��
                                                     1110��1.31V��
                                                     1111��1.32V�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO20_VSET_UNION;
#endif
#define PMIC_LDO20_VSET_ldo20_vset_START  (0)
#define PMIC_LDO20_VSET_ldo20_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO21_ONOFF_ECO_UNION
 �ṹ˵��  : LDO21_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00�����:8
 �Ĵ���˵��: LDO21���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo21_eco_en : 1;  /* bit[0]  : LDO21����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo21_en     : 1;  /* bit[1]  : LDO21ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO21_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO21_ONOFF_ECO_reg_ldo21_eco_en_START  (0)
#define PMIC_LDO21_ONOFF_ECO_reg_ldo21_eco_en_END    (0)
#define PMIC_LDO21_ONOFF_ECO_reg_ldo21_en_START      (1)
#define PMIC_LDO21_ONOFF_ECO_reg_ldo21_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO21_VSET_UNION
 �ṹ˵��  : LDO21_VSET �Ĵ����ṹ���塣��ַƫ����:0x081����ֵ:0x00�����:8
 �Ĵ���˵��: LDO21��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo21_vset : 3;  /* bit[0-2]: LDO21�����ѹ���á�
                                                     000��1.700V��
                                                     001��1.750V��
                                                     010��1.775V��
                                                     011��1.800V��
                                                     100��1.825V��
                                                     101��1.850V��
                                                     110��1.875V��
                                                     111��1.900V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO21_VSET_UNION;
#endif
#define PMIC_LDO21_VSET_ldo21_vset_START  (0)
#define PMIC_LDO21_VSET_ldo21_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO22_ONOFF_ECO_UNION
 �ṹ˵��  : LDO22_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x082����ֵ:0x00�����:8
 �Ĵ���˵��: LDO22���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo22_eco_en : 1;  /* bit[0]  : LDO22����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo22_en     : 1;  /* bit[1]  : LDO22ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO22_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO22_ONOFF_ECO_reg_ldo22_eco_en_START  (0)
#define PMIC_LDO22_ONOFF_ECO_reg_ldo22_eco_en_END    (0)
#define PMIC_LDO22_ONOFF_ECO_reg_ldo22_en_START      (1)
#define PMIC_LDO22_ONOFF_ECO_reg_ldo22_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO22_VSET_UNION
 �ṹ˵��  : LDO22_VSET �Ĵ����ṹ���塣��ַƫ����:0x083����ֵ:0x00�����:8
 �Ĵ���˵��: LDO22��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo22_vset : 4;  /* bit[0-3]: LDO22�����ѹ���á�
                                                     0000��1.0V��
                                                     0001��1.05V��
                                                     0010��1.10V��
                                                     0011��1.15V��
                                                     0100��1.20V��
                                                     0101��1.25V��
                                                     0110��1.26V��
                                                     0111��1.27V��
                                                     1000��1.28V��
                                                     1001��1.29V��
                                                     1010��1.30V��
                                                     1011��1.31V��
                                                     1100��1.32V��
                                                     1101��1.33V��
                                                     1110��1.34V��
                                                     1111��1.50V�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO22_VSET_UNION;
#endif
#define PMIC_LDO22_VSET_ldo22_vset_START  (0)
#define PMIC_LDO22_VSET_ldo22_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO23_ONOFF_ECO_UNION
 �ṹ˵��  : LDO23_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x02�����:8
 �Ĵ���˵��: LDO23���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo23_eco_en : 1;  /* bit[0]  : LDO23����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo23_en     : 1;  /* bit[1]  : LDO23ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO23_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO23_ONOFF_ECO_reg_ldo23_eco_en_START  (0)
#define PMIC_LDO23_ONOFF_ECO_reg_ldo23_eco_en_END    (0)
#define PMIC_LDO23_ONOFF_ECO_reg_ldo23_en_START      (1)
#define PMIC_LDO23_ONOFF_ECO_reg_ldo23_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO23_VSET_UNION
 �ṹ˵��  : LDO23_VSET �Ĵ����ṹ���塣��ַƫ����:0x085����ֵ:0x07�����:8
 �Ĵ���˵��: LDO23��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo23_vset : 3;  /* bit[0-2]: LDO23�����ѹ���á�
                                                     000��2.6V��
                                                     001��2.7V��
                                                     010��2.8V��
                                                     011��2.9V��
                                                     100��3.0V��
                                                     101��3.1V��
                                                     110��3.2V��
                                                     111��3.3V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO23_VSET_UNION;
#endif
#define PMIC_LDO23_VSET_ldo23_vset_START  (0)
#define PMIC_LDO23_VSET_ldo23_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO24_ONOFF_ECO_UNION
 �ṹ˵��  : LDO24_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x086����ֵ:0x02�����:8
 �Ĵ���˵��: LDO24���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo24_eco_en : 1;  /* bit[0]  : LDO24����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo24_en     : 1;  /* bit[1]  : LDO24ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO24_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_eco_en_START  (0)
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_eco_en_END    (0)
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_en_START      (1)
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO24_VSET_UNION
 �ṹ˵��  : LDO24_VSET �Ĵ����ṹ���塣��ַƫ����:0x087����ֵ:0x02�����:8
 �Ĵ���˵��: LDO24��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo24_vset : 3;  /* bit[0-2]: LDO24�����ѹ���á�
                                                     000��2.6V��
                                                     001��2.7V��
                                                     010��2.8V��
                                                     011��2.85V��
                                                     100��3.0V��
                                                     101��3.1V��
                                                     110��3.2V��
                                                     111��3.3V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO24_VSET_UNION;
#endif
#define PMIC_LDO24_VSET_ldo24_vset_START  (0)
#define PMIC_LDO24_VSET_ldo24_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO25_ONOFF_ECO_UNION
 �ṹ˵��  : LDO25_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00�����:8
 �Ĵ���˵��: LDO25���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo25_eco_en : 1;  /* bit[0]  : LDO25����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo25_en     : 1;  /* bit[1]  : LDO25ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO25_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO25_ONOFF_ECO_reg_ldo25_eco_en_START  (0)
#define PMIC_LDO25_ONOFF_ECO_reg_ldo25_eco_en_END    (0)
#define PMIC_LDO25_ONOFF_ECO_reg_ldo25_en_START      (1)
#define PMIC_LDO25_ONOFF_ECO_reg_ldo25_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO25_VSET_UNION
 �ṹ˵��  : LDO25_VSET �Ĵ����ṹ���塣��ַƫ����:0x089����ֵ:0x00�����:8
 �Ĵ���˵��: LDO25��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo25_vset : 3;  /* bit[0-2]: LDO25�����ѹ���á�
                                                     000��1.5V��
                                                     001��1.8V��
                                                     010��2.4V��
                                                     011��2.5V��
                                                     100��2.6V��
                                                     101��2.7V��
                                                     110��2.85V��
                                                     111��3.0V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO25_VSET_UNION;
#endif
#define PMIC_LDO25_VSET_ldo25_vset_START  (0)
#define PMIC_LDO25_VSET_ldo25_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO26_ONOFF_ECO_UNION
 �ṹ˵��  : LDO26_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x08A����ֵ:0x02�����:8
 �Ĵ���˵��: LDO26���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo26_eco_en : 1;  /* bit[0]  : LDO26����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo26_en     : 1;  /* bit[1]  : LDO26ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO26_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_eco_en_START  (0)
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_eco_en_END    (0)
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_en_START      (1)
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO26_VSET_UNION
 �ṹ˵��  : LDO26_VSET �Ĵ����ṹ���塣��ַƫ����:0x08B����ֵ:0x06�����:8
 �Ĵ���˵��: LDO26��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo26_vset : 3;  /* bit[0-2]: LDO26�����ѹ���á�
                                                     000��1.500V��
                                                     001��1.550V��
                                                     010��1.600V��
                                                     011��1.650V��
                                                     100��1.700V��
                                                     101��1.750V��
                                                     110��1.800V��
                                                     111��1.850V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO26_VSET_UNION;
#endif
#define PMIC_LDO26_VSET_ldo26_vset_START  (0)
#define PMIC_LDO26_VSET_ldo26_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO27_ONOFF_ECO_UNION
 �ṹ˵��  : LDO27_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x02�����:8
 �Ĵ���˵��: LDO27���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo27_eco_en : 1;  /* bit[0]  : LDO27����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo27_en     : 1;  /* bit[1]  : LDO27ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO27_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO27_ONOFF_ECO_reg_ldo27_eco_en_START  (0)
#define PMIC_LDO27_ONOFF_ECO_reg_ldo27_eco_en_END    (0)
#define PMIC_LDO27_ONOFF_ECO_reg_ldo27_en_START      (1)
#define PMIC_LDO27_ONOFF_ECO_reg_ldo27_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO27_VSET_UNION
 �ṹ˵��  : LDO27_VSET �Ĵ����ṹ���塣��ַƫ����:0x08D����ֵ:0x05�����:8
 �Ĵ���˵��: LDO27��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo27_vset : 4;  /* bit[0-3]: LDO27�����ѹ���á�
                                                     0000��2.200V��
                                                     0001��2.250V��
                                                     0010��2.300V��
                                                     0011��2.350V��
                                                     0100��2.375V��
                                                     0101��2.400V��
                                                     0110��2.425V��
                                                     0111��2.450V��
                                                     1000��2.475V��
                                                     1001��2.500V��
                                                     1010��2.550V��
                                                     1011��2.600V��
                                                     1100��2.650V��
                                                     1101��2.700V��
                                                     1110��2.800V��
                                                     1111��2.850V�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO27_VSET_UNION;
#endif
#define PMIC_LDO27_VSET_ldo27_vset_START  (0)
#define PMIC_LDO27_VSET_ldo27_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO28_ONOFF_ECO_UNION
 �ṹ˵��  : LDO28_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x08E����ֵ:0x00�����:8
 �Ĵ���˵��: LDO28���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo28_eco_en : 1;  /* bit[0]  : LDO28����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo28_en     : 1;  /* bit[1]  : LDO28ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO28_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO28_ONOFF_ECO_reg_ldo28_eco_en_START  (0)
#define PMIC_LDO28_ONOFF_ECO_reg_ldo28_eco_en_END    (0)
#define PMIC_LDO28_ONOFF_ECO_reg_ldo28_en_START      (1)
#define PMIC_LDO28_ONOFF_ECO_reg_ldo28_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO28_VSET_UNION
 �ṹ˵��  : LDO28_VSET �Ĵ����ṹ���塣��ַƫ����:0x08F����ֵ:0x00�����:8
 �Ĵ���˵��: LDO28��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo28_vset : 3;  /* bit[0-2]: LDO28�����ѹ���á�
                                                     000��1.700V��
                                                     001��1.750V��
                                                     010��1.775V��
                                                     011��1.800V��
                                                     100��1.825V��
                                                     101��1.850V��
                                                     110��1.875V��
                                                     111��1.900V�� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO28_VSET_UNION;
#endif
#define PMIC_LDO28_VSET_ldo28_vset_START  (0)
#define PMIC_LDO28_VSET_ldo28_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_LDO29_ONOFF_ECO_UNION
 �ṹ˵��  : LDO29_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x02�����:8
 �Ĵ���˵��: LDO29���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo29_eco_en : 1;  /* bit[0]  : LDO29����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo29_en     : 1;  /* bit[1]  : LDO29ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO29_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_eco_en_START  (0)
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_eco_en_END    (0)
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_en_START      (1)
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO29_VSET_UNION
 �ṹ˵��  : LDO29_VSET �Ĵ����ṹ���塣��ַƫ����:0x091����ֵ:0x33�����:8
 �Ĵ���˵��: LDO29��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo29_vset     : 3;  /* bit[0-2]: LDO29�����ѹ���á�
                                                         000��1.000V��
                                                         001��1.050V��
                                                         010��1.100V��
                                                         011��1.200V��
                                                         100��1.250V��
                                                         101��1.300V��
                                                         110��1.500V��
                                                         111��1.550V�� */
        unsigned char  reserved_0     : 1;  /* bit[3]  : ������ */
        unsigned char  ldo29_vset_adj : 3;  /* bit[4-6]: LDO29���Ŀ���ѹ��PERI_EN��Чʱ�����õĵ�λ��
                                                         000��1.000V��
                                                         001��1.050V��
                                                         010��1.100V��
                                                         011��1.200V��
                                                         100��1.250V��
                                                         101��1.300V��
                                                         110��1.500V��
                                                         111��1.550V�� */
        unsigned char  reserved_1     : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_LDO29_VSET_UNION;
#endif
#define PMIC_LDO29_VSET_ldo29_vset_START      (0)
#define PMIC_LDO29_VSET_ldo29_vset_END        (2)
#define PMIC_LDO29_VSET_ldo29_vset_adj_START  (4)
#define PMIC_LDO29_VSET_ldo29_vset_adj_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_LDO30_ONOFF_ECO_UNION
 �ṹ˵��  : LDO30_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x092����ֵ:0x02�����:8
 �Ĵ���˵��: LDO���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo30_eco_en : 1;  /* bit[0]  : LDO30����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo30_en     : 1;  /* bit[1]  : LDO30ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO30_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO30_ONOFF_ECO_reg_ldo30_eco_en_START  (0)
#define PMIC_LDO30_ONOFF_ECO_reg_ldo30_eco_en_END    (0)
#define PMIC_LDO30_ONOFF_ECO_reg_ldo30_en_START      (1)
#define PMIC_LDO30_ONOFF_ECO_reg_ldo30_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO30_VSET_UNION
 �ṹ˵��  : LDO30_VSET �Ĵ����ṹ���塣��ַƫ����:0x093����ֵ:0x05�����:8
 �Ĵ���˵��: LDO30��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo30_vset : 4;  /* bit[0-3]: LDO30�����ѹ���á�
                                                     0000��0.700V��
                                                     0001��0.725V��
                                                     0010��0.750V��
                                                     0011��0.775V��
                                                     0100��0.790V��
                                                     0101��0.800V��
                                                     0110��0.810V��
                                                     0111��0.825V��
                                                     1000��0.830V��
                                                     1001��0.850V��
                                                     1010��0.875V��
                                                     1011��0.900V��
                                                     1100��0.925V��
                                                     1101��0.950V��
                                                     1110��0.975V��
                                                     1111��1.000V�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO30_VSET_UNION;
#endif
#define PMIC_LDO30_VSET_ldo30_vset_START  (0)
#define PMIC_LDO30_VSET_ldo30_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO31_ONOFF_ECO_UNION
 �ṹ˵��  : LDO31_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x00�����:8
 �Ĵ���˵��: LDO31���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo31_eco_en : 1;  /* bit[0]  : LDO31����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo31_en     : 1;  /* bit[1]  : LDO31ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO31_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO31_ONOFF_ECO_reg_ldo31_eco_en_START  (0)
#define PMIC_LDO31_ONOFF_ECO_reg_ldo31_eco_en_END    (0)
#define PMIC_LDO31_ONOFF_ECO_reg_ldo31_en_START      (1)
#define PMIC_LDO31_ONOFF_ECO_reg_ldo31_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO31_VSET_UNION
 �ṹ˵��  : LDO31_VSET �Ĵ����ṹ���塣��ַƫ����:0x095����ֵ:0x00�����:8
 �Ĵ���˵��: LDO31��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo31_vset  : 3;  /* bit[0-2]: LDO31�����ѹ���á�
                                                      000��2.50V��
                                                      001��2.60V��
                                                      010��2.70V��
                                                      011��2.80V��
                                                      100��2.90V��
                                                      101��3.00V��
                                                      110��3.10V��
                                                      111��3.20V�� */
        unsigned char  ldo_reserve : 5;  /* bit[3-7]: ldo�����Ĵ��� */
    } reg;
} PMIC_LDO31_VSET_UNION;
#endif
#define PMIC_LDO31_VSET_ldo31_vset_START   (0)
#define PMIC_LDO31_VSET_ldo31_vset_END     (2)
#define PMIC_LDO31_VSET_ldo_reserve_START  (3)
#define PMIC_LDO31_VSET_ldo_reserve_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO32_ONOFF_ECO_UNION
 �ṹ˵��  : LDO32_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x096����ֵ:0x00�����:8
 �Ĵ���˵��: LDO32���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo32_eco_en : 1;  /* bit[0]  : LDO32����͹���ECOģʽ�����źš�
                                                           0��normalģʽ��
                                                           1��ECOģʽ�� */
        unsigned char  reg_ldo32_en     : 1;  /* bit[1]  : LDO32ʹ���źš�
                                                           0���رգ�
                                                           1��ʹ�ܡ� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_LDO32_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO32_ONOFF_ECO_reg_ldo32_eco_en_START  (0)
#define PMIC_LDO32_ONOFF_ECO_reg_ldo32_eco_en_END    (0)
#define PMIC_LDO32_ONOFF_ECO_reg_ldo32_en_START      (1)
#define PMIC_LDO32_ONOFF_ECO_reg_ldo32_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_LDO32_VSET_UNION
 �ṹ˵��  : LDO32_VSET �Ĵ����ṹ���塣��ַƫ����:0x097����ֵ:0x00�����:8
 �Ĵ���˵��: LDO32��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo32_vset : 4;  /* bit[0-3]: LDO32�����ѹ���á�
                                                     0000��0.80V��
                                                     0001��0.85V��
                                                     0010��0.90V��
                                                     0011��0.95V��
                                                     0100��1.00V��
                                                     0101��1.05V��
                                                     0110��1.10V��
                                                     0111��1.20V��
                                                     1000��1.25V��
                                                     1001��1.26V��
                                                     1010��1.27V��
                                                     1011��1.28V��
                                                     1100��1.29V��
                                                     1101��1.30V��
                                                     1110��1.31V��
                                                     1111��1.32V�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_LDO32_VSET_UNION;
#endif
#define PMIC_LDO32_VSET_ldo32_vset_START  (0)
#define PMIC_LDO32_VSET_ldo32_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_ONOFF_ECO_UNION
 �ṹ˵��  : BUCK0_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x02�����:8
 �Ĵ���˵��: BUCK0���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck0_eco_en : 1;  /* bit[0]  : BUCK0 ecoģʽѡ��
                                                           0��������
                                                           1��ECOģʽ�� */
        unsigned char  reg_buck0_en     : 1;  /* bit[1]  : BUCK0ʹ���źš�
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_BUCK0_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_eco_en_START  (0)
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_eco_en_END    (0)
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_en_START      (1)
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_VSET_UNION
 �ṹ˵��  : BUCK0_VSET �Ĵ����ṹ���塣��ַƫ����:0x099����ֵ:0x05�����:8
 �Ĵ���˵��: BUCK0��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_vset : 4;  /* bit[0-3]: BUCK0�����ѹ���ڡ�
                                                     0000��0.700V��
                                                     0001��0.725V��
                                                     0010��0.750V��
                                                     0011��0.775V��
                                                     0100��0.790V��
                                                     0101��0.800V��
                                                     0110��0.810V��
                                                     0111��0.825V��
                                                     1000��0.830V��
                                                     1001��0.850V��
                                                     1010��0.875V��
                                                     1011��0.900V��
                                                     1100��0.925V��
                                                     1101��0.950V��
                                                     1110��0.975V��
                                                     1111��1.000V�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ���� */
    } reg;
} PMIC_BUCK0_VSET_UNION;
#endif
#define PMIC_BUCK0_VSET_buck0_vset_START  (0)
#define PMIC_BUCK0_VSET_buck0_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_ONOFF_ECO_UNION
 �ṹ˵��  : BUCK1_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x09A����ֵ:0x02�����:8
 �Ĵ���˵��: BUCK1���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck1_eco_en : 1;  /* bit[0]  : BUCK1 ecoģʽѡ��
                                                           0��������
                                                           1��ECOģʽ�� */
        unsigned char  reg_buck1_en     : 1;  /* bit[1]  : BUCK1ʹ���źš�
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_BUCK1_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_eco_en_START  (0)
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_eco_en_END    (0)
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_en_START      (1)
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_VSET_UNION
 �ṹ˵��  : BUCK1_VSET �Ĵ����ṹ���塣��ַƫ����:0x09B����ֵ:0xBB�����:8
 �Ĵ���˵��: BUCK1��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_vset     : 4;  /* bit[0-3]: BUCK1�����ѹ���ڣ�Ĭ�Ͽ�����ѹ1.2V, buck1_vol_sel����Ĭ��ֵ��0��1.2V��1��1.1V��
                                                         0000��0.925V��
                                                         0001��0.950V��
                                                         0010��0.975V��
                                                         0011��1.000V��
                                                         0100��1.025V��
                                                         0101��1.050V��
                                                         0110��1.075V��
                                                         0111��1.100V��
                                                         1000��1.125V��
                                                         1001��1.150V��
                                                         1010��1.175V��
                                                         1011��1.200V��
                                                         1100��1.225V��
                                                         1101��1.250V��
                                                         1110��1.275V��
                                                         1111��1.300V�� */
        unsigned char  buck1_vset_adj : 4;  /* bit[4-7]: BUCK1�����ѹֵ��PERI_EN��Чʱ�����óɲ�ͬ��λ��ֵ,buck1_vol_sel����Ĭ��ֵ��0��1.2V��1��1.1V��
                                                         0000��0.925V��
                                                         0001��0.950V��
                                                         0010��0.975V��
                                                         0011��1.000V��
                                                         0100��1.025V��
                                                         0101��1.050V��
                                                         0110��1.075V��
                                                         0111��1.100V��
                                                         1000��1.125V��
                                                         1001��1.150V��
                                                         1010��1.175V��
                                                         1011��1.200V��
                                                         1100��1.225V��
                                                         1101��1.250V��
                                                         1110��1.275V��
                                                         1111��1.300V�� */
    } reg;
} PMIC_BUCK1_VSET_UNION;
#endif
#define PMIC_BUCK1_VSET_buck1_vset_START      (0)
#define PMIC_BUCK1_VSET_buck1_vset_END        (3)
#define PMIC_BUCK1_VSET_buck1_vset_adj_START  (4)
#define PMIC_BUCK1_VSET_buck1_vset_adj_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_ONOFF_ECO_UNION
 �ṹ˵��  : BUCK2_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x09C����ֵ:0x02�����:8
 �Ĵ���˵��: BUCK2���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck2_eco_en : 1;  /* bit[0]  : BUCK2 ecoģʽѡ��
                                                           0��������
                                                           1��ECOģʽ�� */
        unsigned char  reg_buck2_en     : 1;  /* bit[1]  : BUCK2ʹ���źš�
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_BUCK2_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_eco_en_START  (0)
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_eco_en_END    (0)
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_en_START      (1)
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK2_VSET_UNION
 �ṹ˵��  : BUCK2_VSET �Ĵ����ṹ���塣��ַƫ����:0x09D����ֵ:0x44�����:8
 �Ĵ���˵��: BUCK2��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_vset     : 4;  /* bit[0-3]: BUCK2�����ѹ���ڡ�
                                                         0000��1.350V��
                                                         0001��1.375V��
                                                         0010��1.400V��
                                                         0011��1.425V��
                                                         0100��1.450V��
                                                         0101��1.475V��
                                                         0110��1.500V��
                                                         0111��1.525V��
                                                         1000��1.550V��
                                                         1001��1.575V��
                                                         1010��1.600V��
                                                         1011��1.625V��
                                                         1100��1.650V��
                                                         1101��1.675V��
                                                         1110��1.700V��
                                                         1111��1.725V�� */
        unsigned char  buck2_vset_adj : 4;  /* bit[4-7]: BUCK2���Ŀ���ѹ��PERI_EN��Чʱ�����õĵ�λ��
                                                         0000��1.350V��
                                                         0001��1.375V��
                                                         0010��1.400V��
                                                         0011��1.425V��
                                                         0100��1.450V��
                                                         0101��1.475V��
                                                         0110��1.500V��
                                                         0111��1.525V��
                                                         1000��1.550V��
                                                         1001��1.575V��
                                                         1010��1.600V��
                                                         1011��1.625V��
                                                         1100��1.650V��
                                                         1101��1.675V��
                                                         1110��1.700V��
                                                         1111��1.725V�� */
    } reg;
} PMIC_BUCK2_VSET_UNION;
#endif
#define PMIC_BUCK2_VSET_buck2_vset_START      (0)
#define PMIC_BUCK2_VSET_buck2_vset_END        (3)
#define PMIC_BUCK2_VSET_buck2_vset_adj_START  (4)
#define PMIC_BUCK2_VSET_buck2_vset_adj_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_ONOFF_ECO_UNION
 �ṹ˵��  : BUCK3_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x09E����ֵ:0x02�����:8
 �Ĵ���˵��: BUCK3���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck3_eco_en : 1;  /* bit[0]  : BUCK3 ecoģʽѡ��
                                                           0��������
                                                           1��ECOģʽ�� */
        unsigned char  reg_buck3_en     : 1;  /* bit[1]  : BUCK3ʹ���źš�
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_BUCK3_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_eco_en_START  (0)
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_eco_en_END    (0)
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_en_START      (1)
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK3_VSET_UNION
 �ṹ˵��  : BUCK3_VSET �Ĵ����ṹ���塣��ַƫ����:0x09F����ֵ:0x77�����:8
 �Ĵ���˵��: BUCK3��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_vset     : 4;  /* bit[0-3]: BUCK3�����ѹ���ڡ�
                                                         1.8/1.85/1.9/1.95/2.0/2.05/2.1/2.15/2.2/2.25/2.3/2.35/2.4/2.45/2.5/2.55��Ĭ�ϵ�ѹ2.15V
                                                         0000��1.800V��
                                                         0001��1.850V��
                                                         0010��1.900V��
                                                         0011��1.950V��
                                                         0100��2.000V��
                                                         0101��2.050V��
                                                         0110��2.100V��
                                                         0111��2.150V��
                                                         1000��2.200V��
                                                         1001��2.250V��
                                                         1010��2.300V��
                                                         1011��2.350V��
                                                         1100��2.400V��
                                                         1101��2.450V��
                                                         1110��2.500V��
                                                         1111��2.550V�� */
        unsigned char  buck3_vset_adj : 4;  /* bit[4-7]: BUCK3���Ŀ���ѹ��PERI_EN��Чʱ�����õĵ�λ��
                                                         1.8/1.85/1.9/1.95/2.0/2.05/2.1/2.15/2.2/2.25/2.3/2.35/2.4/2.45/2.5/2.55��Ĭ�ϵ�ѹ2.15V
                                                         0000��1.800V��
                                                         0001��1.850V��
                                                         0010��1.900V��
                                                         0011��1.950V��
                                                         0100��2.000V��
                                                         0101��2.050V��
                                                         0110��2.100V��
                                                         0111��2.150V��
                                                         1000��2.200V��
                                                         1001��2.250V��
                                                         1010��2.300V��
                                                         1011��2.350V��
                                                         1100��2.400V��
                                                         1101��2.450V��
                                                         1110��2.500V��
                                                         1111��2.550V�� */
    } reg;
} PMIC_BUCK3_VSET_UNION;
#endif
#define PMIC_BUCK3_VSET_buck3_vset_START      (0)
#define PMIC_BUCK3_VSET_buck3_vset_END        (3)
#define PMIC_BUCK3_VSET_buck3_vset_adj_START  (4)
#define PMIC_BUCK3_VSET_buck3_vset_adj_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_ONOFF_ECO_UNION
 �ṹ˵��  : BUCK4_ONOFF_ECO �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x02�����:8
 �Ĵ���˵��: BUCK4���غ�ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck4_eco_en : 1;  /* bit[0]  : BUCK4 ecoģʽѡ��
                                                           0��������
                                                           1��ECOģʽ�� */
        unsigned char  reg_buck4_en     : 1;  /* bit[1]  : BUCK4ʹ���źš�
                                                           0���رգ�
                                                           1�������� */
        unsigned char  reserved         : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_BUCK4_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK4_ONOFF_ECO_reg_buck4_eco_en_START  (0)
#define PMIC_BUCK4_ONOFF_ECO_reg_buck4_eco_en_END    (0)
#define PMIC_BUCK4_ONOFF_ECO_reg_buck4_en_START      (1)
#define PMIC_BUCK4_ONOFF_ECO_reg_buck4_en_END        (1)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_VSET_UNION
 �ṹ˵��  : BUCK4_VSET �Ĵ����ṹ���塣��ַƫ����:0x0A1����ֵ:0x05�����:8
 �Ĵ���˵��: BUCK4��ѹ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_vset : 4;  /* bit[0-3]: BUCK4�����ѹ���ڡ�
                                                     0000��0.700V��
                                                     0001��0.725V��
                                                     0010��0.750V��
                                                     0011��0.775V��
                                                     0100��0.790V��
                                                     0101��0.800V��
                                                     0110��0.810V��
                                                     0111��0.825V��
                                                     1000��0.830V��
                                                     1001��0.850V��
                                                     1010��0.875V��
                                                     1011��0.900V��
                                                     1100��0.925V��
                                                     1101��0.950V��
                                                     1110��0.975V��
                                                     1111��1.000V�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_BUCK4_VSET_UNION;
#endif
#define PMIC_BUCK4_VSET_buck4_vset_START  (0)
#define PMIC_BUCK4_VSET_buck4_vset_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_LDO_PMUA_ECO_UNION
 �ṹ˵��  : LDO_PMUA_ECO �Ĵ����ṹ���塣��ַƫ����:0x0A2����ֵ:0x00�����:8
 �Ĵ���˵��: LDO_PMUA ECOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  pmua_eco_en : 1;  /* bit[0]  : PMUA����ECOģʽ�����źš�
                                                      0��0����normalģʽ��
                                                      1��ECOģʽ�� */
        unsigned char  reserved    : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_LDO_PMUA_ECO_UNION;
#endif
#define PMIC_LDO_PMUA_ECO_pmua_eco_en_START  (0)
#define PMIC_LDO_PMUA_ECO_pmua_eco_en_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_LDO_PMUA_VSET_UNION
 �ṹ˵��  : LDO_PMUA_VSET �Ĵ����ṹ���塣��ַƫ����:0x0A3����ֵ:0x05�����:8
 �Ĵ���˵��: LDO_PMUA��ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  pmua_vset : 3;  /* bit[0-2]: LDO_PMUA�����ѹ���á�
                                                    000��2.5��
                                                    001��2.6��
                                                    010��2.7��
                                                    011��2.8��
                                                    100��2.9��
                                                    101��3.0��
                                                    110��3.1��
                                                    111��3.2�� */
        unsigned char  reserved  : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_LDO_PMUA_VSET_UNION;
#endif
#define PMIC_LDO_PMUA_VSET_pmua_vset_START  (0)
#define PMIC_LDO_PMUA_VSET_pmua_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_BST_MODE_EN_UNION
 �ṹ˵��  : BST_MODE_EN �Ĵ����ṹ���塣��ַƫ����:0x0A4����ֵ:0x03�����:8
 �Ĵ���˵��: BSTʹ�ܿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck_boost_en_d : 1;  /* bit[0]  : ����BUCK_BOOSTоƬ��ʹ���źţ�ͨ��ģ��PMUD��1.8V�� IO�����
                                                              0���رգ�
                                                              1�������� */
        unsigned char  buck_boost_en_mode  : 1;  /* bit[1]  : BUCK_BOOST���ֳ���ʹ���źš�
                                                              0����ʾ�����µ磻
                                                              1����ʾ������ */
        unsigned char  reserved            : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_BST_MODE_EN_UNION;
#endif
#define PMIC_BST_MODE_EN_reg_buck_boost_en_d_START  (0)
#define PMIC_BST_MODE_EN_reg_buck_boost_en_d_END    (0)
#define PMIC_BST_MODE_EN_buck_boost_en_mode_START   (1)
#define PMIC_BST_MODE_EN_buck_boost_en_mode_END     (1)


/*****************************************************************************
 �ṹ��    : PMIC_NOPWR_CTRL_UNION
 �ṹ˵��  : NOPWR_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0A5����ֵ:0x01�����:8
 �Ĵ���˵��: NOPWRT���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_chg_en   : 1;  /* bit[0]  : ���õ�س��ʹ�ܡ�
                                                      0����ʹ�ܣ�
                                                      1��ʹ�ܡ� */
        unsigned char  np_chg_vset : 2;  /* bit[1-2]: ���õ�س���ѹѡ��
                                                      00��2.5V(Ĭ��ֵ����
                                                      01��3.0V��
                                                      1X��3.3V��
                                                      ע�⣺Austinʵ��Ϊ2����ѹ��2.5VĬ�ϣ�3.0V��Ϊ����smartstar���ݣ���߼Ĵ�����2λ��ʵ��ʹ��ʱֻ��2���� */
        unsigned char  reserved    : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_NOPWR_CTRL_UNION;
#endif
#define PMIC_NOPWR_CTRL_np_chg_en_START    (0)
#define PMIC_NOPWR_CTRL_np_chg_en_END      (0)
#define PMIC_NOPWR_CTRL_np_chg_vset_START  (1)
#define PMIC_NOPWR_CTRL_np_chg_vset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_CLASSD_CTRL0_UNION
 �ṹ˵��  : CLASSD_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0A6����ֵ:0x00�����:8
 �Ĵ���˵��: classd���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_classd_en   : 1;  /* bit[0]  : classDʹ�ܿ��ơ�
                                                          1��������
                                                          0���رա� */
        unsigned char  classd_mute     : 1;  /* bit[1]  : classd_mute���ơ� 
                                                          0������������
                                                          1��Mute�� */
        unsigned char  classd_mute_sel : 1;  /* bit[2]  : classd_mute_sel���ơ� 
                                                          0����ʱmuteģʽ��muteʱ����mute,���muteʱ����ʱ8ms,�����������ٽ������ 
                                                          1������muteģʽ����8ms��ʱ���� */
        unsigned char  classd_drv_en   : 1;  /* bit[3]  : ������·ʹ�ܡ�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  classd_i_ocp    : 2;  /* bit[4-5]: classD������ֵ���ڡ�
                                                          00��1.2A��
                                                          01��1.59A��
                                                          10��2.0A��
                                                          11��2.39A�� */
        unsigned char  classd_gain     : 2;  /* bit[6-7]: classD������ơ� 
                                                          00��12db��
                                                          01��15db��
                                                          10��18db��
                                                          11��21db�� */
    } reg;
} PMIC_CLASSD_CTRL0_UNION;
#endif
#define PMIC_CLASSD_CTRL0_reg_classd_en_START    (0)
#define PMIC_CLASSD_CTRL0_reg_classd_en_END      (0)
#define PMIC_CLASSD_CTRL0_classd_mute_START      (1)
#define PMIC_CLASSD_CTRL0_classd_mute_END        (1)
#define PMIC_CLASSD_CTRL0_classd_mute_sel_START  (2)
#define PMIC_CLASSD_CTRL0_classd_mute_sel_END    (2)
#define PMIC_CLASSD_CTRL0_classd_drv_en_START    (3)
#define PMIC_CLASSD_CTRL0_classd_drv_en_END      (3)
#define PMIC_CLASSD_CTRL0_classd_i_ocp_START     (4)
#define PMIC_CLASSD_CTRL0_classd_i_ocp_END       (5)
#define PMIC_CLASSD_CTRL0_classd_gain_START      (6)
#define PMIC_CLASSD_CTRL0_classd_gain_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLASSD_CTRL1_UNION
 �ṹ˵��  : CLASSD_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x0A7����ֵ:0x00�����:8
 �Ĵ���˵��: classd���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_i_pump : 2;  /* bit[0-1]: Ramp���У�pump�������ơ�
                                                        00��6��A��
                                                        01��7��A��
                                                        10��7��A��
                                                        11��8��A�� */
        unsigned char  classd_i_ramp : 2;  /* bit[2-3]: Ramp���У��Ƚ����������ơ�
                                                        00��1��A��
                                                        01��3��A��
                                                        10��4��A��
                                                        11��5��A�� */
        unsigned char  classd_p_sel  : 2;  /* bit[4-5]: ������pmos���ơ�
                                                        00����һ·pmos��
                                                        01������·pmos��
                                                        10������·pmos��
                                                        11������·pmos�� */
        unsigned char  classd_n_sel  : 2;  /* bit[6-7]: ������nmos���ơ�
                                                        00����һ·nmos��
                                                        01������·nmos��
                                                        10������·nmos��
                                                        11������·nmos�� */
    } reg;
} PMIC_CLASSD_CTRL1_UNION;
#endif
#define PMIC_CLASSD_CTRL1_classd_i_pump_START  (0)
#define PMIC_CLASSD_CTRL1_classd_i_pump_END    (1)
#define PMIC_CLASSD_CTRL1_classd_i_ramp_START  (2)
#define PMIC_CLASSD_CTRL1_classd_i_ramp_END    (3)
#define PMIC_CLASSD_CTRL1_classd_p_sel_START   (4)
#define PMIC_CLASSD_CTRL1_classd_p_sel_END     (5)
#define PMIC_CLASSD_CTRL1_classd_n_sel_START   (6)
#define PMIC_CLASSD_CTRL1_classd_n_sel_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLASSD_CTRL2_UNION
 �ṹ˵��  : CLASSD_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x0A8����ֵ:0x00�����:8
 �Ĵ���˵��: classd���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_pls_byp  : 1;  /* bit[0]  : ��С�������ޡ�
                                                          0������������
                                                          1��bypass��С�������ơ� */
        unsigned char  classd_dt_sel   : 1;  /* bit[1]  : dead time���ơ�
                                                          0��2ns��
                                                          1��7ns�� */
        unsigned char  classd_fx_bps   : 1;  /* bit[2]  : ��Ƶģʽ���ơ�
                                                          0��������Ƶģʽ��
                                                          1��bypass��Ƶģʽ���̶�Ƶ�ʣ��� */
        unsigned char  classd_ocp_bps  : 1;  /* bit[3]  : �����������ơ�
                                                          0����������������
                                                          1��bypass����������·��OCP�źŲ��ϱ����� */
        unsigned char  classd_reserve0 : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_CLASSD_CTRL2_UNION;
#endif
#define PMIC_CLASSD_CTRL2_classd_pls_byp_START   (0)
#define PMIC_CLASSD_CTRL2_classd_pls_byp_END     (0)
#define PMIC_CLASSD_CTRL2_classd_dt_sel_START    (1)
#define PMIC_CLASSD_CTRL2_classd_dt_sel_END      (1)
#define PMIC_CLASSD_CTRL2_classd_fx_bps_START    (2)
#define PMIC_CLASSD_CTRL2_classd_fx_bps_END      (2)
#define PMIC_CLASSD_CTRL2_classd_ocp_bps_START   (3)
#define PMIC_CLASSD_CTRL2_classd_ocp_bps_END     (3)
#define PMIC_CLASSD_CTRL2_classd_reserve0_START  (4)
#define PMIC_CLASSD_CTRL2_classd_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLASSD_CTRL3_UNION
 �ṹ˵��  : CLASSD_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x0A9����ֵ:0x00�����:8
 �Ĵ���˵��: classd���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_reserve1 : 8;  /* bit[0-7]: ������ */
    } reg;
} PMIC_CLASSD_CTRL3_UNION;
#endif
#define PMIC_CLASSD_CTRL3_classd_reserve1_START  (0)
#define PMIC_CLASSD_CTRL3_classd_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_TH_CTRL_UNION
 �ṹ˵��  : TH_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0AA����ֵ:0x32�����:8
 �Ĵ���˵��: ��ѹ�¶ȿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ref_eco_en   : 1;  /* bit[0]  : ref_topģʽѡ��λ��
                                                       0��ref_top����������
                                                       1��ref_top����ecoģʽ�� */
        unsigned char  reg_thsd_en  : 1;  /* bit[1]  : THSD���±���ģ��رտ��ؿ���λ��
                                                       0���ر�THSD���±���ģ�飻
                                                       1������THSD���±���ģ�顣 */
        unsigned char  thsd_eco_en  : 1;  /* bit[2]  : THSD���±���ECOģʽ���ؿ���λ��
                                                       0���ر�THSD���±���ECOģʽ��
                                                       1������THSD���±���ECOģʽ�� */
        unsigned char  reserved_0   : 1;  /* bit[3]  : ������ */
        unsigned char  thsd_tmp_set : 2;  /* bit[4-5]: �¶ȱ���ģ�鱨���¶����á�
                                                       00��95�棻
                                                       01��105�棻
                                                       10��115�棻
                                                       11��125�档 */
        unsigned char  reserved_1   : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_TH_CTRL_UNION;
#endif
#define PMIC_TH_CTRL_ref_eco_en_START    (0)
#define PMIC_TH_CTRL_ref_eco_en_END      (0)
#define PMIC_TH_CTRL_reg_thsd_en_START   (1)
#define PMIC_TH_CTRL_reg_thsd_en_END     (1)
#define PMIC_TH_CTRL_thsd_eco_en_START   (2)
#define PMIC_TH_CTRL_thsd_eco_en_END     (2)
#define PMIC_TH_CTRL_thsd_tmp_set_START  (4)
#define PMIC_TH_CTRL_thsd_tmp_set_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_BG_TEST_UNION
 �ṹ˵��  : BG_TEST �Ĵ����ṹ���塣��ַƫ����:0x0AB����ֵ:0x00�����:8
 �Ĵ���˵��: bg���ԼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ref_test : 8;  /* bit[0-7]: ��׼����ģʽԤ���� */
    } reg;
} PMIC_BG_TEST_UNION;
#endif
#define PMIC_BG_TEST_ref_test_START  (0)
#define PMIC_BG_TEST_ref_test_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DR_EN_MODE_345_UNION
 �ṹ˵��  : DR_EN_MODE_345 �Ĵ����ṹ���塣��ַƫ����:0x0AC����ֵ:0x00�����:8
 �Ĵ���˵��: DR345��˸ģʽʹ�ܺ�ģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_dr3_int : 1;  /* bit[0]  : DR3��������˸ģʽ�£�dr3_mode_sel=1�����ؿ��ơ�
                                                     0���ر�DR3��
                                                     1������DR3��  */
        unsigned char  dr3_mode   : 1;  /* bit[1]  : DR3����ģʽ���ؿ��ơ�
                                                     0���ر�����ģʽ(��ʱ����Ϊ�������)��
                                                     1������DR3����ģʽ��  */
        unsigned char  en_dr4_int : 1;  /* bit[2]  : DR4��������˸ģʽ�£�dr4_mode_sel=1�����ؿ��ơ�
                                                     0���ر�DR4��
                                                     1������DR4��  */
        unsigned char  dr4_mode   : 1;  /* bit[3]  : DR4����ģʽ���ؿ��ơ�
                                                     0���ر�����ģʽ(��ʱ����Ϊ�������)��
                                                     1������DR4����ģʽ��  */
        unsigned char  en_dr5_int : 1;  /* bit[4]  : DR5��������˸ģʽ�£�dr5_mode_sel=1�����ؿ��ơ�
                                                     0���ر�DR5��
                                                     1������DR5��  */
        unsigned char  dr5_mode   : 1;  /* bit[5]  : DR5����ģʽ���ؿ��ơ�
                                                     0���ر�����ģʽ(��ʱ����Ϊ�������)��
                                                     1������DR5����ģʽ��  */
        unsigned char  reserved   : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_DR_EN_MODE_345_UNION;
#endif
#define PMIC_DR_EN_MODE_345_en_dr3_int_START  (0)
#define PMIC_DR_EN_MODE_345_en_dr3_int_END    (0)
#define PMIC_DR_EN_MODE_345_dr3_mode_START    (1)
#define PMIC_DR_EN_MODE_345_dr3_mode_END      (1)
#define PMIC_DR_EN_MODE_345_en_dr4_int_START  (2)
#define PMIC_DR_EN_MODE_345_en_dr4_int_END    (2)
#define PMIC_DR_EN_MODE_345_dr4_mode_START    (3)
#define PMIC_DR_EN_MODE_345_dr4_mode_END      (3)
#define PMIC_DR_EN_MODE_345_en_dr5_int_START  (4)
#define PMIC_DR_EN_MODE_345_en_dr5_int_END    (4)
#define PMIC_DR_EN_MODE_345_dr5_mode_START    (5)
#define PMIC_DR_EN_MODE_345_dr5_mode_END      (5)


/*****************************************************************************
 �ṹ��    : PMIC_DR_EN_MODE_12_UNION
 �ṹ˵��  : DR_EN_MODE_12 �Ĵ����ṹ���塣��ַƫ����:0x0AD����ֵ:0x00�����:8
 �Ĵ���˵��: DR12��˸ģʽʹ�ܺ�ģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_dr1_int : 1;  /* bit[0]  : DR1��������˸ģʽ�£�dr1_mode_sel=1�����ؿ��ơ�
                                                     0���ر�DR1��
                                                     1������DR1 ��  */
        unsigned char  dr1_mode   : 1;  /* bit[1]  : DR1����ģʽ���ؿ��ơ�
                                                     0���ر�����ģʽ(��ʱ����Ϊ�������)��
                                                     1������DR1����ģʽ��  */
        unsigned char  en_dr2_int : 1;  /* bit[2]  : DR2��������˸ģʽ�£�dr2_mode_sel=1�����ؿ��ơ�
                                                     0���ر�DR2��
                                                     1������DR2��  */
        unsigned char  dr2_mode   : 1;  /* bit[3]  : DR2����ģʽ���ؿ��ơ�
                                                     0���ر�����ģʽ(��ʱ����Ϊ�������)��
                                                     1������DR2����ģʽ��  */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_DR_EN_MODE_12_UNION;
#endif
#define PMIC_DR_EN_MODE_12_en_dr1_int_START  (0)
#define PMIC_DR_EN_MODE_12_en_dr1_int_END    (0)
#define PMIC_DR_EN_MODE_12_dr1_mode_START    (1)
#define PMIC_DR_EN_MODE_12_dr1_mode_END      (1)
#define PMIC_DR_EN_MODE_12_en_dr2_int_START  (2)
#define PMIC_DR_EN_MODE_12_en_dr2_int_END    (2)
#define PMIC_DR_EN_MODE_12_dr2_mode_START    (3)
#define PMIC_DR_EN_MODE_12_dr2_mode_END      (3)


/*****************************************************************************
 �ṹ��    : PMIC_FLASH_PERIOD_DR12_UNION
 �ṹ˵��  : FLASH_PERIOD_DR12 �Ĵ����ṹ���塣��ַƫ����:0x0AE����ֵ:0x3F�����:8
 �Ĵ���˵��: DR12��˸ģʽ���ڵ���0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_period_dr12 : 8;  /* bit[0-7]: ��˸����T = ����ֵ *31.25ms�� */
    } reg;
} PMIC_FLASH_PERIOD_DR12_UNION;
#endif
#define PMIC_FLASH_PERIOD_DR12_flash_period_dr12_START  (0)
#define PMIC_FLASH_PERIOD_DR12_flash_period_dr12_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_FLASH_ON_DR12_UNION
 �ṹ˵��  : FLASH_ON_DR12 �Ĵ����ṹ���塣��ַƫ����:0x0AF����ֵ:0x1F�����:8
 �Ĵ���˵��: DR12��˸ģʽ����ʱ�����0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_on_dr12 : 8;  /* bit[0-7]: ����ʱ��t =����ֵ *7.8125ms�� */
    } reg;
} PMIC_FLASH_ON_DR12_UNION;
#endif
#define PMIC_FLASH_ON_DR12_flash_on_dr12_START  (0)
#define PMIC_FLASH_ON_DR12_flash_on_dr12_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_FLASH_PERIOD_DR345_UNION
 �ṹ˵��  : FLASH_PERIOD_DR345 �Ĵ����ṹ���塣��ַƫ����:0x0B0����ֵ:0x3F�����:8
 �Ĵ���˵��: DR345��˸ģʽ���ڵ���1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_period_dr345 : 8;  /* bit[0-7]: ��˸����T = ����ֵ *31.25ms�� */
    } reg;
} PMIC_FLASH_PERIOD_DR345_UNION;
#endif
#define PMIC_FLASH_PERIOD_DR345_flash_period_dr345_START  (0)
#define PMIC_FLASH_PERIOD_DR345_flash_period_dr345_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_FLASH_ON_DR345_UNION
 �ṹ˵��  : FLASH_ON_DR345 �Ĵ����ṹ���塣��ַƫ����:0x0B1����ֵ:0x1F�����:8
 �Ĵ���˵��: DR345��˸ģʽ����ʱ�����1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_on_dr345 : 8;  /* bit[0-7]: ����ʱ��t =����ֵ *7.8125ms�� */
    } reg;
} PMIC_FLASH_ON_DR345_UNION;
#endif
#define PMIC_FLASH_ON_DR345_flash_on_dr345_START  (0)
#define PMIC_FLASH_ON_DR345_flash_on_dr345_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DR_MODE_SEL_UNION
 �ṹ˵��  : DR_MODE_SEL �Ĵ����ṹ���塣��ַƫ����:0x0B2����ֵ:0x00�����:8
 �Ĵ���˵��: DR��ģʽѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr1_mode_sel : 1;  /* bit[0]  : DR1����ģʽѡ��
                                                       0�� DR1�����ں�������ģʽ��
                                                       1��DR1��������˸ģʽ�� */
        unsigned char  dr2_mode_sel : 1;  /* bit[1]  : DR2����ģʽѡ��
                                                       0�� DR2�����ں�������ģʽ��
                                                       1��DR2��������˸ģʽ�� */
        unsigned char  dr3_mode_sel : 1;  /* bit[2]  : DR3����ģʽѡ��
                                                       0�� DR3�����ں�������ģʽ��
                                                       1��DR3��������˸ģʽ�� */
        unsigned char  dr4_mode_sel : 1;  /* bit[3]  : DR4����ģʽѡ��
                                                       0�� DR4�����ں�������ģʽ��
                                                       1��DR4��������˸ģʽ�� */
        unsigned char  dr5_mode_sel : 1;  /* bit[4]  : DR5����ģʽѡ��
                                                       0�� DR5�����ں�������ģʽ��
                                                       1��DR5��������˸ģʽ�� */
        unsigned char  reserved     : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_DR_MODE_SEL_UNION;
#endif
#define PMIC_DR_MODE_SEL_dr1_mode_sel_START  (0)
#define PMIC_DR_MODE_SEL_dr1_mode_sel_END    (0)
#define PMIC_DR_MODE_SEL_dr2_mode_sel_START  (1)
#define PMIC_DR_MODE_SEL_dr2_mode_sel_END    (1)
#define PMIC_DR_MODE_SEL_dr3_mode_sel_START  (2)
#define PMIC_DR_MODE_SEL_dr3_mode_sel_END    (2)
#define PMIC_DR_MODE_SEL_dr4_mode_sel_START  (3)
#define PMIC_DR_MODE_SEL_dr4_mode_sel_END    (3)
#define PMIC_DR_MODE_SEL_dr5_mode_sel_START  (4)
#define PMIC_DR_MODE_SEL_dr5_mode_sel_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_DR_BRE_CTRL_UNION
 �ṹ˵��  : DR_BRE_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0B3����ֵ:0x00�����:8
 �Ĵ���˵��: DR1/2����ģʽ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_dr1_en   : 1;  /* bit[0]  : DR1�����ں�����dr1_mode_sel=0��ģʽʹ�ܡ�
                                                       0��dr1�ر� �� 
                                                       1��dr1ʹ�ܡ�
                                                       dr1_flash_en = 1,���� ��
                                                       dr1_flash_en = 0,���� �� */
        unsigned char  dr1_flash_en : 1;  /* bit[1]  : DR1����ʹ�ܡ�
                                                       0����ʹ��dr1����ģʽ��
                                                       1��ʹ��dr1����ģʽ�� */
        unsigned char  reserved_0   : 2;  /* bit[2-3]: ������ */
        unsigned char  reg_dr2_en   : 1;  /* bit[4]  : DR2�����ں�����dr2_mode_sel=0��ģʽʹ�ܡ�
                                                       0��dr2�ر� �� 
                                                       1��dr2ʹ�ܡ�
                                                       dr2_flash_en = 1,���� ��
                                                       dr2_flash_en = 0,���� �� */
        unsigned char  dr2_flash_en : 1;  /* bit[5]  : DR2����ʹ�ܡ�
                                                       0����ʹ��dr2����ģʽ��
                                                       1��ʹ��dr2����ģʽ�� */
        unsigned char  reserved_1   : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_DR_BRE_CTRL_UNION;
#endif
#define PMIC_DR_BRE_CTRL_reg_dr1_en_START    (0)
#define PMIC_DR_BRE_CTRL_reg_dr1_en_END      (0)
#define PMIC_DR_BRE_CTRL_dr1_flash_en_START  (1)
#define PMIC_DR_BRE_CTRL_dr1_flash_en_END    (1)
#define PMIC_DR_BRE_CTRL_reg_dr2_en_START    (4)
#define PMIC_DR_BRE_CTRL_reg_dr2_en_END      (4)
#define PMIC_DR_BRE_CTRL_dr2_flash_en_START  (5)
#define PMIC_DR_BRE_CTRL_dr2_flash_en_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_DR12_TIM_CONF0_UNION
 �ṹ˵��  : DR12_TIM_CONF0 �Ĵ����ṹ���塣��ַƫ����:0x0B4����ֵ:0x33�����:8
 �Ĵ���˵��: DR1��DR2��������ʱ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr12_t_off : 3;  /* bit[0-2]: DR12����ģʽ�³���ʱ�䡣
                                                     000��1ms��
                                                     001��0.25s��
                                                     010��0.5s��
                                                     011��1s��
                                                     100��2s��
                                                     101��4s��
                                                     110��4s��
                                                     111�������� */
        unsigned char  reserved_0 : 1;  /* bit[3]  : ������ */
        unsigned char  dr12_t_on  : 3;  /* bit[4-6]: DR12����ģʽ�³���ʱ�����á�
                                                     000��1ms��
                                                     001��0.25s��
                                                     010��0.5s��
                                                     011��1s��
                                                     100��2s��
                                                     101��4s��
                                                     110��4s��
                                                     111�������� */
        unsigned char  reserved_1 : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_DR12_TIM_CONF0_UNION;
#endif
#define PMIC_DR12_TIM_CONF0_dr12_t_off_START  (0)
#define PMIC_DR12_TIM_CONF0_dr12_t_off_END    (2)
#define PMIC_DR12_TIM_CONF0_dr12_t_on_START   (4)
#define PMIC_DR12_TIM_CONF0_dr12_t_on_END     (6)


/*****************************************************************************
 �ṹ��    : PMIC_DR12_TIM_CONF1_UNION
 �ṹ˵��  : DR12_TIM_CONF1 �Ĵ����ṹ���塣��ַƫ����:0x0B5����ֵ:0x33�����:8
 �Ĵ���˵��: DR1��DR2��������ʱ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr12_t_rise : 3;  /* bit[0-2]: DR12����ģʽ�½���ʱ�䡣
                                                      000��0s��
                                                      001��0.25s��
                                                      010��0.5s��
                                                      011��1s��
                                                      100��2s��
                                                      101��2.5s��
                                                      110��3s��
                                                      111��4s�� */
        unsigned char  reserved_0  : 1;  /* bit[3]  : ������ */
        unsigned char  dr12_t_fall : 3;  /* bit[4-6]: DR12����ģʽ�½���ʱ�䡣
                                                      000��0s��
                                                      001��0.25s��
                                                      010��0.5s��
                                                      011��1s��
                                                      100��2s��
                                                      101��2.5s��
                                                      110��3s��
                                                      111��4s�� */
        unsigned char  reserved_1  : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_DR12_TIM_CONF1_UNION;
#endif
#define PMIC_DR12_TIM_CONF1_dr12_t_rise_START  (0)
#define PMIC_DR12_TIM_CONF1_dr12_t_rise_END    (2)
#define PMIC_DR12_TIM_CONF1_dr12_t_fall_START  (4)
#define PMIC_DR12_TIM_CONF1_dr12_t_fall_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_DR1_ISET_UNION
 �ṹ˵��  : DR1_ISET �Ĵ����ṹ���塣��ַƫ����:0x0B6����ֵ:0x00�����:8
 �Ĵ���˵��: DR1����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr1_iset : 3;  /* bit[0-2]: DR1�������ڡ� 000��3 mA��
                                                   001��6 mA��
                                                   010��9 mA��
                                                   011��12 mA��
                                                   100��15 mA��
                                                   101��18 mA��
                                                   110��21 mA��
                                                   111��24 mA�� */
        unsigned char  reserved : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_DR1_ISET_UNION;
#endif
#define PMIC_DR1_ISET_dr1_iset_START  (0)
#define PMIC_DR1_ISET_dr1_iset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_DR2_ISET_UNION
 �ṹ˵��  : DR2_ISET �Ĵ����ṹ���塣��ַƫ����:0x0B7����ֵ:0x00�����:8
 �Ĵ���˵��: DR2����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr2_iset : 3;  /* bit[0-2]: DR2�������ڡ� 000��3 mA��
                                                   001��6 mA��
                                                   010��9 mA��
                                                   011��12 mA��
                                                   100��15 mA��
                                                   101��18 mA��
                                                   110��21 mA��
                                                   111��24 mA�� */
        unsigned char  reserved : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_DR2_ISET_UNION;
#endif
#define PMIC_DR2_ISET_dr2_iset_START  (0)
#define PMIC_DR2_ISET_dr2_iset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_DR_LED_CTRL_UNION
 �ṹ˵��  : DR_LED_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0B8����ֵ:0x00�����:8
 �Ĵ���˵��: DR3/4/5���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_dr3_en : 1;  /* bit[0]  : ����ģʽ��DR3ʹ�ܡ�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned char  reg_dr4_en : 1;  /* bit[1]  : ����ģʽ��DR4ʹ�ܡ�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned char  reg_dr5_en : 1;  /* bit[2]  : ����ģʽ��DR5ʹ�ܡ�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_DR_LED_CTRL_UNION;
#endif
#define PMIC_DR_LED_CTRL_reg_dr3_en_START  (0)
#define PMIC_DR_LED_CTRL_reg_dr3_en_END    (0)
#define PMIC_DR_LED_CTRL_reg_dr4_en_START  (1)
#define PMIC_DR_LED_CTRL_reg_dr4_en_END    (1)
#define PMIC_DR_LED_CTRL_reg_dr5_en_START  (2)
#define PMIC_DR_LED_CTRL_reg_dr5_en_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_DR_OUT_CTRL_UNION
 �ṹ˵��  : DR_OUT_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0B9����ֵ:0x00�����:8
 �Ĵ���˵��: DR3/4/5������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr3_out_ctrl : 2;  /* bit[0-1]: DR3������ơ�
                                                       00��DR3�������������DR3�ܽţ�
                                                       01��DR3��DR4����������������DR3�ܽţ�
                                                       10��DR3��DR4��DR5����������������DR3�ܽţ�
                                                       11��DR4��DR5����������������DR3�ܽš� */
        unsigned char  dr4_out_ctrl : 2;  /* bit[2-3]: DR4������ơ�
                                                       00��DR4�������������DR4�ܽţ�
                                                       01��DR3��DR4����������������DR4�ܽţ�
                                                       10��DR3��DR4��DR5����������������DR4�ܽţ�
                                                       11��DR4��DR5����������������DR4�ܽš� */
        unsigned char  dr5_out_ctrl : 2;  /* bit[4-5]: DR5������ơ�
                                                       00��DR5�������������DR5�ܽţ�
                                                       01��DR3��DR4����������������DR5�ܽţ�
                                                       10��DR3��DR4��DR5����������������DR5�ܽţ�
                                                       11��DR4��DR5����������������DR5�ܽš� */
        unsigned char  reserved     : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_DR_OUT_CTRL_UNION;
#endif
#define PMIC_DR_OUT_CTRL_dr3_out_ctrl_START  (0)
#define PMIC_DR_OUT_CTRL_dr3_out_ctrl_END    (1)
#define PMIC_DR_OUT_CTRL_dr4_out_ctrl_START  (2)
#define PMIC_DR_OUT_CTRL_dr4_out_ctrl_END    (3)
#define PMIC_DR_OUT_CTRL_dr5_out_ctrl_START  (4)
#define PMIC_DR_OUT_CTRL_dr5_out_ctrl_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_DR3_ISET_UNION
 �ṹ˵��  : DR3_ISET �Ĵ����ṹ���塣��ַƫ����:0x0BA����ֵ:0x00�����:8
 �Ĵ���˵��: DR3����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr3_iset : 3;  /* bit[0-2]: DR3����������ڣ�mA����
                                                   0x0 ��1.0��
                                                   0x1 ��1.5��
                                                   0x2 ��2.0��
                                                   0x3 ��2.5��
                                                   0x4 ��3.0��
                                                   0x5 ��3.5��
                                                   0x6 ��4.0��
                                                   0x7 ��4.5�� */
        unsigned char  reserved : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_DR3_ISET_UNION;
#endif
#define PMIC_DR3_ISET_dr3_iset_START  (0)
#define PMIC_DR3_ISET_dr3_iset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_DR3_START_DEL_UNION
 �ṹ˵��  : DR3_START_DEL �Ĵ����ṹ���塣��ַƫ����:0x0BB����ֵ:0x10�����:8
 �Ĵ���˵��: DR3������ʱ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr3_start_delay : 8;  /* bit[0-7]: DR3������ʱ��Χ��0��32768 ms��step��125ms�� */
    } reg;
} PMIC_DR3_START_DEL_UNION;
#endif
#define PMIC_DR3_START_DEL_dr3_start_delay_START  (0)
#define PMIC_DR3_START_DEL_dr3_start_delay_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DR4_ISET_UNION
 �ṹ˵��  : DR4_ISET �Ĵ����ṹ���塣��ַƫ����:0x0BC����ֵ:0x00�����:8
 �Ĵ���˵��: DR4����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr4_iset : 3;  /* bit[0-2]: DR4����������ڣ�mA����
                                                   0x0 ��1.0��
                                                   0x1 ��1.5��
                                                   0x2 ��2.0��
                                                   0x3 ��2.5��
                                                   0x4 ��3.0��
                                                   0x5 ��3.5��
                                                   0x6 ��4.0��
                                                   0x7 ��4.5�� */
        unsigned char  reserved : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_DR4_ISET_UNION;
#endif
#define PMIC_DR4_ISET_dr4_iset_START  (0)
#define PMIC_DR4_ISET_dr4_iset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_DR4_START_DEL_UNION
 �ṹ˵��  : DR4_START_DEL �Ĵ����ṹ���塣��ַƫ����:0x0BD����ֵ:0x10�����:8
 �Ĵ���˵��: DR4������ʱ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr4_start_delay : 8;  /* bit[0-7]: DR4������ʱ��Χ��0��32768 ms��step��125ms�� */
    } reg;
} PMIC_DR4_START_DEL_UNION;
#endif
#define PMIC_DR4_START_DEL_dr4_start_delay_START  (0)
#define PMIC_DR4_START_DEL_dr4_start_delay_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DR5_ISET_UNION
 �ṹ˵��  : DR5_ISET �Ĵ����ṹ���塣��ַƫ����:0x0BE����ֵ:0x00�����:8
 �Ĵ���˵��: DR5����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr5_iset : 3;  /* bit[0-2]: DR5����������ڣ�mA����
                                                   0x0 ��1.0��
                                                   0x1 ��1.5��
                                                   0x2 ��2.0��
                                                   0x3 ��2.5��
                                                   0x4 ��3.0��
                                                   0x5 ��3.5��
                                                   0x6 ��4.0��
                                                   0x7 ��4.5�� */
        unsigned char  reserved : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_DR5_ISET_UNION;
#endif
#define PMIC_DR5_ISET_dr5_iset_START  (0)
#define PMIC_DR5_ISET_dr5_iset_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_DR5_START_DEL_UNION
 �ṹ˵��  : DR5_START_DEL �Ĵ����ṹ���塣��ַƫ����:0x0BF����ֵ:0x10�����:8
 �Ĵ���˵��: DR5������ʱ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr5_start_delay : 8;  /* bit[0-7]: DR5������ʱ��Χ��0��32768 ms��step��125ms�� */
    } reg;
} PMIC_DR5_START_DEL_UNION;
#endif
#define PMIC_DR5_START_DEL_dr5_start_delay_START  (0)
#define PMIC_DR5_START_DEL_dr5_start_delay_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DR334_TIM_CONF0_UNION
 �ṹ˵��  : DR334_TIM_CONF0 �Ĵ����ṹ���塣��ַƫ����:0x0C0����ֵ:0x44�����:8
 �Ĵ���˵��: DR345��������ʱ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr345_t_off : 4;  /* bit[0-3]: DR345����ʱ�����á�
                                                      000��0s��
                                                      001��0.5s��
                                                      010��1s��
                                                      011��2s��
                                                      100��4s��
                                                      101��6s��
                                                      110��8s��
                                                      111��12s��
                                                      1000��14��
                                                      1001��16��
                                                      ������������ */
        unsigned char  dr345_t_on  : 4;  /* bit[4-7]: DR345����ʱ�����á�
                                                      0000��0s��
                                                      0001��0.5s��
                                                      0010��1s��
                                                      0011��2s��
                                                      0100��4s��
                                                      0101��6s��
                                                      0110��8s��
                                                      0111��12s��
                                                      1000��14��
                                                      1001��16��
                                                      ������������ */
    } reg;
} PMIC_DR334_TIM_CONF0_UNION;
#endif
#define PMIC_DR334_TIM_CONF0_dr345_t_off_START  (0)
#define PMIC_DR334_TIM_CONF0_dr345_t_off_END    (3)
#define PMIC_DR334_TIM_CONF0_dr345_t_on_START   (4)
#define PMIC_DR334_TIM_CONF0_dr345_t_on_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_DR345_TIM_CONF1_UNION
 �ṹ˵��  : DR345_TIM_CONF1 �Ĵ����ṹ���塣��ַƫ����:0x0C1����ֵ:0x33�����:8
 �Ĵ���˵��: DR345��������ʱ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr345_t_rise : 3;  /* bit[0-2]: DR345����ʱ�����á�
                                                       000��0s��
                                                       001��0.25s��
                                                       010��0.5s��
                                                       011��1s��
                                                       100��2s��
                                                       101��2.5s��
                                                       110��3s��
                                                       111��4s�� */
        unsigned char  reserved_0   : 1;  /* bit[3]  : ������ */
        unsigned char  dr345_t_fall : 3;  /* bit[4-6]: DR345����ʱ�����á�
                                                       000��0s��
                                                       001��0.25s��
                                                       010��0.5s��
                                                       011��1s��
                                                       100��2s��
                                                       101��2.5s��
                                                       110��3s��
                                                       111��4s�� */
        unsigned char  reserved_1   : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_DR345_TIM_CONF1_UNION;
#endif
#define PMIC_DR345_TIM_CONF1_dr345_t_rise_START  (0)
#define PMIC_DR345_TIM_CONF1_dr345_t_rise_END    (2)
#define PMIC_DR345_TIM_CONF1_dr345_t_fall_START  (4)
#define PMIC_DR345_TIM_CONF1_dr345_t_fall_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_VSYS_LOW_SET0_UNION
 �ṹ˵��  : VSYS_LOW_SET0 �Ĵ����ṹ���塣��ַƫ����:0x0C2����ֵ:0x1E�����:8
 �Ĵ���˵��: IN�˵�ѹ��ֵ�����Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vsys_uv_set         : 4;  /* bit[0-3]: vsys������͵�ѹ�ж���ֵ��ѹ���ڣ����ڴ˵�ѹ�ϱ��жϡ�
                                                              0000�� 2.60V��
                                                              0001�� 2.70V��
                                                              0010��2.80V��
                                                              0011��2.90V��
                                                              0100��3.00V��
                                                              0101��3.10V��
                                                              0110��3.20V��
                                                              0111��3.30V��
                                                              1000��3.35V��
                                                              1001��3.40V��
                                                              1010��3.45V��
                                                              1011��3.50V��
                                                              1100��3.55V��
                                                              1101��3.60V��
                                                              1110��3.65V��
                                                              1111��3.70V��
                                                              �˲�ʱ��μ�UV_VSYS__DEB_CTRL[vsys_uv_deb_sel]�� */
        unsigned char  vsys_pwroff_deb_set : 3;  /* bit[4-6]: �ػ���ѹ��ֵ���ڣ����ڴ˵�ѹPMU�ػ���
                                                              000�� 2.5V��
                                                              001�� 2.6V��
                                                              010�� 2.7V��
                                                              011��2.8V��
                                                              100��2.9V��
                                                              101��3.0V��
                                                              110��3.1V��
                                                              111��3.2V��
                                                              �˲�ʱ��μ�UV_VSYS_DEB_CTRL[vsys_pwroff_deb_sel]�� */
        unsigned char  vsys_pwroff_abs_set : 1;  /* bit[7]  : vsys�˵͵�ѹ�ж���ֵ��ѹ���������ڴ˵�ѹ���̹ػ������˲���
                                                              0��2.3V��
                                                              1��2.4V�� */
    } reg;
} PMIC_VSYS_LOW_SET0_UNION;
#endif
#define PMIC_VSYS_LOW_SET0_vsys_uv_set_START          (0)
#define PMIC_VSYS_LOW_SET0_vsys_uv_set_END            (3)
#define PMIC_VSYS_LOW_SET0_vsys_pwroff_deb_set_START  (4)
#define PMIC_VSYS_LOW_SET0_vsys_pwroff_deb_set_END    (6)
#define PMIC_VSYS_LOW_SET0_vsys_pwroff_abs_set_START  (7)
#define PMIC_VSYS_LOW_SET0_vsys_pwroff_abs_set_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_VSYS_LOW_SET1_UNION
 �ṹ˵��  : VSYS_LOW_SET1 �Ĵ����ṹ���塣��ַƫ����:0x0C3����ֵ:0x02�����:8
 �Ĵ���˵��: IN�˵�ѹ��ֵ�����Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vsys_pwron_set : 3;  /* bit[0-2]: ������ѹ��ֵ���ڣ����ڴ˵�ѹPMU������
                                                         000��2.6V��
                                                         001��2.7V��
                                                         010��2.8V��
                                                         011��2.9V��
                                                         100��3.0V��
                                                         101��3.1V��
                                                         110��3.2V��
                                                         111��3.3V�� */
        unsigned char  reserved_0     : 1;  /* bit[3]  : ������ */
        unsigned char  nfc_on_d2a     : 1;  /* bit[4]  : NFC_ON����ܽţ��ǵ���Ĵ���������PMUD�����档
                                                         0��NFC_ON�ܽ����0��ƽ��
                                                         1��NFC_ON�ܽ����1.8V�� */
        unsigned char  reserved_1     : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_VSYS_LOW_SET1_UNION;
#endif
#define PMIC_VSYS_LOW_SET1_vsys_pwron_set_START  (0)
#define PMIC_VSYS_LOW_SET1_vsys_pwron_set_END    (2)
#define PMIC_VSYS_LOW_SET1_nfc_on_d2a_START      (4)
#define PMIC_VSYS_LOW_SET1_nfc_on_d2a_END        (4)


/*****************************************************************************
 �ṹ��    : PMIC_SYS_CTRL_RESERVE_UNION
 �ṹ˵��  : SYS_CTRL_RESERVE �Ĵ����ṹ���塣��ַƫ����:0x0C4����ֵ:0x00�����:8
 �Ĵ���˵��: ϵͳ����Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_ctrl_reserve : 8;  /* bit[0-7]: ϵͳ����ģ��Ԥ���Ĵ����� */
    } reg;
} PMIC_SYS_CTRL_RESERVE_UNION;
#endif
#define PMIC_SYS_CTRL_RESERVE_sys_ctrl_reserve_START  (0)
#define PMIC_SYS_CTRL_RESERVE_sys_ctrl_reserve_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HARDWIRE_CTRL0_UNION
 �ṹ˵��  : HARDWIRE_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0C5����ֵ:0x3F�����:8
 �Ĵ���˵��: Ӳ�����ο��ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_eco_in_hd_mask   : 1;  /* bit[0]  : �Ƿ����Ρ�SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en�Ĵ���������߼���eco_in_n������/���߿������á�
                                                               0�������Σ�
                                                               1�����Ρ� */
        unsigned char  reg_xo_core_hd_mask  : 1;  /* bit[1]  : �Ƿ����Ρ�SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en�Ĵ���������߼���xo_core_en������/���߿������á�
                                                               0�������Σ�
                                                               1�����Ρ� */
        unsigned char  reg_xo_ldo_hd_mask   : 1;  /* bit[2]  : �Ƿ����Ρ�SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en�Ĵ���������߼���xo_ldo_en������/���߿������á�
                                                               0�������Σ�
                                                               1�����Ρ� */
        unsigned char  reg_sys_clk_hd_mask  : 1;  /* bit[3]  : �Ƿ�����Ӳ��SYS_CLK_EN��sys_clk�Ŀ�/�ؿ������á�
                                                               0�������Σ�
                                                               1�����Ρ� */
        unsigned char  reg_abb_clk_hd_mask  : 1;  /* bit[4]  : �Ƿ�����Ӳ��SYS_CLK_EN��abb_clk�Ŀ�/�ؿ������á�
                                                               0�������Σ�
                                                               1�����Ρ� */
        unsigned char  reg_wifi_clk_hd_mask : 1;  /* bit[5]  : �Ƿ�����Ӳ��WIFIBT_CLK_EN��wifibt_clk�Ŀ�/�ؿ������á�
                                                               0�������Σ�
                                                               1�����Ρ� */
        unsigned char  reserved             : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_HARDWIRE_CTRL0_UNION;
#endif
#define PMIC_HARDWIRE_CTRL0_reg_eco_in_hd_mask_START    (0)
#define PMIC_HARDWIRE_CTRL0_reg_eco_in_hd_mask_END      (0)
#define PMIC_HARDWIRE_CTRL0_reg_xo_core_hd_mask_START   (1)
#define PMIC_HARDWIRE_CTRL0_reg_xo_core_hd_mask_END     (1)
#define PMIC_HARDWIRE_CTRL0_reg_xo_ldo_hd_mask_START    (2)
#define PMIC_HARDWIRE_CTRL0_reg_xo_ldo_hd_mask_END      (2)
#define PMIC_HARDWIRE_CTRL0_reg_sys_clk_hd_mask_START   (3)
#define PMIC_HARDWIRE_CTRL0_reg_sys_clk_hd_mask_END     (3)
#define PMIC_HARDWIRE_CTRL0_reg_abb_clk_hd_mask_START   (4)
#define PMIC_HARDWIRE_CTRL0_reg_abb_clk_hd_mask_END     (4)
#define PMIC_HARDWIRE_CTRL0_reg_wifi_clk_hd_mask_START  (5)
#define PMIC_HARDWIRE_CTRL0_reg_wifi_clk_hd_mask_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_HARDWIRE_CTRL1_UNION
 �ṹ˵��  : HARDWIRE_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x0C6����ֵ:0x1F�����:8
 �Ĵ���˵��: Ӳ�����ο��ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo27_hd_mask : 1;  /* bit[0]  : �Ƿ����Ρ�SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en�Ĵ���������߼���ldo27�Ŀ�/�ؿ������á�
                                                            0�������Σ�
                                                            1�����Ρ� */
        unsigned char  reg_ldo26_hd_mask : 2;  /* bit[1-2]: �Ƿ����Ρ�SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en�Ĵ���������߼���ld26�Ŀ�/�ؼ���/��eco�������á�
                                                            00��������
                                                            01����������߼���ldo26�Ŀ�/�ؿ��ƣ�����������߼���LDO26�Ľ�/��eco���ƣ����������£�ldo26��ʹ�ܼĴ�������Ϊ1��ldo26��ecoʹ�ܼĴ�������Ϊ0��ldo26�ſ����ܿ�������߼�����/��ecoģʽ����
                                                            10������������߼���LDO26�Ŀ�/�ؿ��ƣ���������߼���ldo26�Ľ�/��eco���ƣ����������£�ldo26��ʹ�ܼĴ�������Ϊ0��ldo26���п����ܿ�������߼�����/�أ���
                                                            11����������߼���ldo26�Ŀ�/�غͽ�/��eco���ƣ����������£�ldo26�Ŀ�/��ֻ�ܿ�������ʹ�ܼĴ�����ldo26�Ľ�/��eco����ֻ�ܿ��������ecoʹ�ܼĴ�������Ȼ��ʹ�ܼĴ�������Ϊ1���п�����������ecoģʽ���� */
        unsigned char  reg_ldo14_hd_mask : 1;  /* bit[3]  : �Ƿ����Ρ�SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en�Ĵ���������߼���ldo14�Ŀ�/�ؿ������á�
                                                            0�������Σ�
                                                            1�����Ρ� */
        unsigned char  reg_ldo13_hd_mask : 1;  /* bit[4]  : �Ƿ����Ρ�SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en�Ĵ���������߼���ldo13�Ŀ�/�ؿ������á�
                                                            0�������Σ�
                                                            1�����Ρ� */
        unsigned char  reserved          : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_HARDWIRE_CTRL1_UNION;
#endif
#define PMIC_HARDWIRE_CTRL1_reg_ldo27_hd_mask_START  (0)
#define PMIC_HARDWIRE_CTRL1_reg_ldo27_hd_mask_END    (0)
#define PMIC_HARDWIRE_CTRL1_reg_ldo26_hd_mask_START  (1)
#define PMIC_HARDWIRE_CTRL1_reg_ldo26_hd_mask_END    (2)
#define PMIC_HARDWIRE_CTRL1_reg_ldo14_hd_mask_START  (3)
#define PMIC_HARDWIRE_CTRL1_reg_ldo14_hd_mask_END    (3)
#define PMIC_HARDWIRE_CTRL1_reg_ldo13_hd_mask_START  (4)
#define PMIC_HARDWIRE_CTRL1_reg_ldo13_hd_mask_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_PERI_CTRL0_UNION
 �ṹ˵��  : PERI_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0C7����ֵ:0x00�����:8
 �Ĵ���˵��: periӲ�߿��ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_ldo5_on    : 1;  /* bit[0]: LDO5�Ƿ��ܿ���peri_en����λ��
                                                           0������peri_en���ƶ���/�أ�
                                                           1����peri_en���ƶ���/�ء� */
        unsigned char  peri_en_ldo2_eco   : 1;  /* bit[1]: LDO2�Ƿ��ܿ���peri_en����λ��
                                                           0������peri_en���ƶ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo0_2_eco : 1;  /* bit[2]: LDO0_2�Ƿ��ܿ���peri_en����λ��
                                                           0������peri_en���ƶ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_buck4_on   : 1;  /* bit[3]: BUCK4�Ƿ��ܿ���peri_en����λ��
                                                           0������peri_en���ƶ���/�أ�
                                                           1����peri_en���ƶ���/�ء� */
        unsigned char  peri_en_buck3_eco  : 1;  /* bit[4]: BUCK3�Ƿ��ܿ���peri_en����λ��
                                                           0������peri_en���ƶ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_buck2_eco  : 1;  /* bit[5]: BUCK2�Ƿ��ܿ���peri_en����λ��
                                                           0������peri_en���ƶ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_buck1_eco  : 1;  /* bit[6]: BUCK1�Ƿ��ܿ���peri_en����λ��
                                                           0������peri_en���ƶ���/��ECO��
                                                           1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_buck0_on   : 1;  /* bit[7]: BUCK0�Ƿ��ܿ���peri_en����λ��
                                                           0������peri_en���ƶ���/�أ�
                                                           1����peri_en���ƶ���/�ء� */
    } reg;
} PMIC_PERI_CTRL0_UNION;
#endif
#define PMIC_PERI_CTRL0_peri_en_ldo5_on_START     (0)
#define PMIC_PERI_CTRL0_peri_en_ldo5_on_END       (0)
#define PMIC_PERI_CTRL0_peri_en_ldo2_eco_START    (1)
#define PMIC_PERI_CTRL0_peri_en_ldo2_eco_END      (1)
#define PMIC_PERI_CTRL0_peri_en_ldo0_2_eco_START  (2)
#define PMIC_PERI_CTRL0_peri_en_ldo0_2_eco_END    (2)
#define PMIC_PERI_CTRL0_peri_en_buck4_on_START    (3)
#define PMIC_PERI_CTRL0_peri_en_buck4_on_END      (3)
#define PMIC_PERI_CTRL0_peri_en_buck3_eco_START   (4)
#define PMIC_PERI_CTRL0_peri_en_buck3_eco_END     (4)
#define PMIC_PERI_CTRL0_peri_en_buck2_eco_START   (5)
#define PMIC_PERI_CTRL0_peri_en_buck2_eco_END     (5)
#define PMIC_PERI_CTRL0_peri_en_buck1_eco_START   (6)
#define PMIC_PERI_CTRL0_peri_en_buck1_eco_END     (6)
#define PMIC_PERI_CTRL0_peri_en_buck0_on_START    (7)
#define PMIC_PERI_CTRL0_peri_en_buck0_on_END      (7)


/*****************************************************************************
 �ṹ��    : PMIC_PERI_CTRL1_UNION
 �ṹ˵��  : PERI_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x0C8����ֵ:0x00�����:8
 �Ĵ���˵��: periӲ�߿��ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_ldo30_on  : 1;  /* bit[0]: LDO30�Ƿ��ܿ���peri_en����λ��
                                                          0������peri_en���ƶ���/�أ�
                                                          1����peri_en���ƶ���/�ء� */
        unsigned char  peri_en_ldo29_eco : 1;  /* bit[1]: LDO29�Ƿ��ܿ���peri_en����λ��
                                                          0������peri_en���ƶ���/��ECO��
                                                          1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo23_on  : 1;  /* bit[2]: LDO23�Ƿ��ܿ���peri_en����λ��
                                                          0������peri_en���ƶ���/�أ�
                                                          1����peri_en���ƶ���/�ء� */
        unsigned char  peri_en_ldo12_eco : 1;  /* bit[3]: LDO12�Ƿ��ܿ���peri_en����λ��
                                                          0������peri_en���ƶ���/��ECO��
                                                          1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo11_eco : 1;  /* bit[4]: LDO11�Ƿ��ܿ���peri_en����λ��
                                                          0������peri_en���ƶ���/��ECO��
                                                          1����peri_en���ƶ���/��ECO�� */
        unsigned char  peri_en_ldo10_on  : 1;  /* bit[5]: LDO10�Ƿ��ܿ���peri_en����λ��
                                                          0������peri_en���ƶ���/�أ�
                                                          1����peri_en���ƶ���/�ء� */
        unsigned char  peri_en_ldo8_on   : 1;  /* bit[6]: LDO8�Ƿ��ܿ���peri_en����λ��
                                                          0������peri_en���ƶ���/�أ�
                                                          1����peri_en���ƶ���/�ء� */
        unsigned char  peri_en_ldo7_on   : 1;  /* bit[7]: LDO7�Ƿ��ܿ���peri_en����λ��
                                                          0������peri_en���ƶ���/�أ�
                                                          1����peri_en���ƶ���/�ء� */
    } reg;
} PMIC_PERI_CTRL1_UNION;
#endif
#define PMIC_PERI_CTRL1_peri_en_ldo30_on_START   (0)
#define PMIC_PERI_CTRL1_peri_en_ldo30_on_END     (0)
#define PMIC_PERI_CTRL1_peri_en_ldo29_eco_START  (1)
#define PMIC_PERI_CTRL1_peri_en_ldo29_eco_END    (1)
#define PMIC_PERI_CTRL1_peri_en_ldo23_on_START   (2)
#define PMIC_PERI_CTRL1_peri_en_ldo23_on_END     (2)
#define PMIC_PERI_CTRL1_peri_en_ldo12_eco_START  (3)
#define PMIC_PERI_CTRL1_peri_en_ldo12_eco_END    (3)
#define PMIC_PERI_CTRL1_peri_en_ldo11_eco_START  (4)
#define PMIC_PERI_CTRL1_peri_en_ldo11_eco_END    (4)
#define PMIC_PERI_CTRL1_peri_en_ldo10_on_START   (5)
#define PMIC_PERI_CTRL1_peri_en_ldo10_on_END     (5)
#define PMIC_PERI_CTRL1_peri_en_ldo8_on_START    (6)
#define PMIC_PERI_CTRL1_peri_en_ldo8_on_END      (6)
#define PMIC_PERI_CTRL1_peri_en_ldo7_on_START    (7)
#define PMIC_PERI_CTRL1_peri_en_ldo7_on_END      (7)


/*****************************************************************************
 �ṹ��    : PMIC_PERI_VSET_CTRL_UNION
 �ṹ˵��  : PERI_VSET_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0C9����ֵ:0x00�����:8
 �Ĵ���˵��: periӲ�ߵ�ѹ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_buck3_vset  : 1;  /* bit[0]  : BUCK3��ѹ�Ƿ��ܿ���peri_en����λ����Ŀ���ѹ��
                                                              0������peri_en���ƶ����룻
                                                              1����peri_en���ƶ����롣 */
        unsigned char  peri_en_buck2_vset  : 1;  /* bit[1]  : BUCK2��ѹ�Ƿ��ܿ���peri_en����λ����Ŀ���ѹ��
                                                              0������peri_en���ƶ����룻
                                                              1����peri_en���ƶ����롣 */
        unsigned char  peri_en_buck1_vset  : 1;  /* bit[2]  : BUCK1��ѹ�Ƿ��ܿ���peri_en����λ����Ŀ���ѹ��
                                                              0������peri_en���ƶ����룻
                                                              1����peri_en���ƶ����롣 */
        unsigned char  peri_en_ldo29_vset  : 1;  /* bit[3]  : LDO29��ѹ�Ƿ��ܿ���peri_en����λ����Ŀ���ѹ��
                                                              0������peri_en���ƶ����룻
                                                              1����peri_en���ƶ����롣 */
        unsigned char  peri_en_ldo2_vset   : 1;  /* bit[4]  : LDO2��ѹ�Ƿ��ܿ���peri_en����λ����Ŀ���ѹ��
                                                              0������peri_en���ƶ����룻
                                                              1����peri_en���ƶ����롣 */
        unsigned char  peri_en_ldo0_2_vset : 1;  /* bit[5]  : LDO0_2��ѹ�Ƿ��ܿ���peri_en����λ����Ŀ���ѹ��
                                                              0������peri_en���ƶ����룻
                                                              1����peri_en���ƶ����롣 */
        unsigned char  reserved            : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_PERI_VSET_CTRL_UNION;
#endif
#define PMIC_PERI_VSET_CTRL_peri_en_buck3_vset_START   (0)
#define PMIC_PERI_VSET_CTRL_peri_en_buck3_vset_END     (0)
#define PMIC_PERI_VSET_CTRL_peri_en_buck2_vset_START   (1)
#define PMIC_PERI_VSET_CTRL_peri_en_buck2_vset_END     (1)
#define PMIC_PERI_VSET_CTRL_peri_en_buck1_vset_START   (2)
#define PMIC_PERI_VSET_CTRL_peri_en_buck1_vset_END     (2)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo29_vset_START   (3)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo29_vset_END     (3)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo2_vset_START    (4)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo2_vset_END      (4)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo0_2_vset_START  (5)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo0_2_vset_END    (5)


/*****************************************************************************
 �ṹ��    : PMIC_PERI_TIME__CTRL_UNION
 �ṹ˵��  : PERI_TIME__CTRL �Ĵ����ṹ���塣��ַƫ����:0x0CA����ֵ:0x00�����:8
 �Ĵ���˵��: periӲ��ʱ�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0   : 1;  /* bit[0]  : Ԥ���Ĵ��� */
        unsigned char  ldo8_on_sel  : 1;  /* bit[1]  : LDO5��LDO8�ϵ�������λ��
                                                       0��peri_en����ʱLDO5��LDO8�ϵ���Ϊ120us��
                                                       1��peri_en����ʱLDO5��LDO8�ϵ���Ϊ60us��
                                                       LDO8��LDO10�ϵ�������λ��
                                                       0��peri_en����ʱLDO8��LDO10�ϵ���Ϊ120us��
                                                       1��peri_en����ʱLDO8��LDO10�ϵ���Ϊ60us�� */
        unsigned char  ldo5_on_sel  : 1;  /* bit[2]  : LDO7��LDO5�ϵ�������λ��
                                                       0��peri_en����ʱLDO7��LDO5�ϵ���Ϊ120us��
                                                       1��peri_en����ʱLDO7��LDO5�ϵ���Ϊ60us�� */
        unsigned char  ldo7_on_sel  : 1;  /* bit[3]  : BUCK4��LDO7�ϵ�������λ��
                                                       0��peri_en����ʱBUCK4��LDO7�ϵ���Ϊ240us��
                                                       1��peri_en����ʱBUCK4��LDO7�ϵ���Ϊ120us�� */
        unsigned char  buck4_on_sel : 1;  /* bit[4]  : BUCK0��BUCK4�ϵ�������λ��
                                                       0��peri_en����ʱBUCK0��BUCK4�ϵ���Ϊ240us��
                                                       1��peri_en����ʱBUCK0��BUCK4�ϵ���Ϊ120us�� */
        unsigned char  reserved_1   : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_PERI_TIME__CTRL_UNION;
#endif
#define PMIC_PERI_TIME__CTRL_ldo8_on_sel_START   (1)
#define PMIC_PERI_TIME__CTRL_ldo8_on_sel_END     (1)
#define PMIC_PERI_TIME__CTRL_ldo5_on_sel_START   (2)
#define PMIC_PERI_TIME__CTRL_ldo5_on_sel_END     (2)
#define PMIC_PERI_TIME__CTRL_ldo7_on_sel_START   (3)
#define PMIC_PERI_TIME__CTRL_ldo7_on_sel_END     (3)
#define PMIC_PERI_TIME__CTRL_buck4_on_sel_START  (4)
#define PMIC_PERI_TIME__CTRL_buck4_on_sel_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_HRESET_PWRDOWN_CTRL_UNION
 �ṹ˵��  : HRESET_PWRDOWN_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0CB����ֵ:0x01�����:8
 �Ĵ���˵��: �ȸ�λ�µ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hreset_mode : 1;  /* bit[0]  : HRESET_N����ģʽѡ��λ��
                                                      0��hreset�µ�������
                                                      1��hreset�ȸ�λ������ */
        unsigned char  reserved    : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_HRESET_PWRDOWN_CTRL_UNION;
#endif
#define PMIC_HRESET_PWRDOWN_CTRL_hreset_mode_START  (0)
#define PMIC_HRESET_PWRDOWN_CTRL_hreset_mode_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_OSC32K_ONOFF_CTRL_UNION
 �ṹ˵��  : OSC32K_ONOFF_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0CC����ֵ:0x01�����:8
 �Ĵ���˵��: 32kHzʱ�����ʹ�ܿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_32k_sys : 1;  /* bit[0]  : CLK32_SYS ���ʹ��λ��
                                                     0���������
                                                     1��32kHzʱ������� */
        unsigned char  en_32k_bt  : 1;  /* bit[1]  : CLK32_BT ���ʹ��λ��
                                                     0���������
                                                     1��32kHzʱ������� */
        unsigned char  en_32k_gps : 1;  /* bit[2]  : CLK32_GPS ���ʹ��λ��
                                                     0���������
                                                     1��32kHzʱ������� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_OSC32K_ONOFF_CTRL_UNION;
#endif
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_sys_START  (0)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_sys_END    (0)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_bt_START   (1)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_bt_END     (1)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_gps_START  (2)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_gps_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_DEB_CTRL_UNION
 �ṹ˵��  : OCP_DEB_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0CD����ֵ:0x02�����:8
 �Ĵ���˵��: OCP��SPC�˲�ʱ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  scp_ocp_deb_sel2 : 3;  /* bit[0-2]: LDO��OCP�˲�ʱ�䡣
                                                           000��150us���Ǿ���150us��������180us��210us�Ƚ�Сֵ����
                                                           001��0.5ms��
                                                           010��1ms��
                                                           011��2ms��
                                                           100��4ms��
                                                           101��20ms��
                                                           110��40ms��
                                                           111��80ms��
                                                           ע��LDOû���˲�ʹ�ܣ�Ĭ�Ͼ�ʹ���˲��� */
        unsigned char  reserved_0       : 1;  /* bit[3]  : ������ */
        unsigned char  scp_ocp_deb_sel1 : 3;  /* bit[4-6]: BUCK��OCP��SCP��classd��OCP���˲�ʱ��ѡ��
                                                           000��60us���Ǿ���60us��������90us��120us�Ƚ�Сֵ����
                                                           001��0.5ms��
                                                           010��1ms��
                                                           011��2ms��
                                                           100��4ms��
                                                           101��20ms��
                                                           110��40ms��
                                                           111��80ms��
                                                           ע��classdû���˲�ʹ���źţ����Ĭ��Ϊ000����£���classd�˲�60us����BUCK ��Ҫ����ʹ���źŲ����˲�������ʹ������£��˲�Ϊ0us�� */
        unsigned char  reserved_1       : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_OCP_DEB_CTRL_UNION;
#endif
#define PMIC_OCP_DEB_CTRL_scp_ocp_deb_sel2_START  (0)
#define PMIC_OCP_DEB_CTRL_scp_ocp_deb_sel2_END    (2)
#define PMIC_OCP_DEB_CTRL_scp_ocp_deb_sel1_START  (4)
#define PMIC_OCP_DEB_CTRL_scp_ocp_deb_sel1_END    (6)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_SCP_ONOFF_UNION
 �ṹ˵��  : OCP_SCP_ONOFF �Ĵ����ṹ���塣��ַƫ����:0x0CE����ֵ:0x03�����:8
 �Ĵ���˵��: OCP��DOCP�˲����ؼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_buck_scp_deb : 1;  /* bit[0]  : BUCK scp�˲�����ʹ��λ��
                                                          0��BUCK scp �˲���ʹ�ܣ�
                                                          1��BUCK scp �˲�ʹ�ܡ� */
        unsigned char  en_buck_ocp_deb : 1;  /* bit[1]  : BUCK OCP�˲�����ʹ��λ��
                                                          0��BUCK OCP �˲���ʹ�ܣ�
                                                          1��BUCK OCP �˲�ʹ�ܡ� */
        unsigned char  reserved        : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_OCP_SCP_ONOFF_UNION;
#endif
#define PMIC_OCP_SCP_ONOFF_en_buck_scp_deb_START  (0)
#define PMIC_OCP_SCP_ONOFF_en_buck_scp_deb_END    (0)
#define PMIC_OCP_SCP_ONOFF_en_buck_ocp_deb_START  (1)
#define PMIC_OCP_SCP_ONOFF_en_buck_ocp_deb_END    (1)


/*****************************************************************************
 �ṹ��    : PMIC_UV_VSYS_DEB_CTRL_UNION
 �ṹ˵��  : UV_VSYS_DEB_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0CF����ֵ:0xA7�����:8
 �Ĵ���˵��: Ƿѹ�澯��Ƿѹ�ػ��˲�ʱ��ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vsys_pwroff_deb_sel : 3;  /* bit[0-2]: vsysС��2.6Vָʾ�ź�ȥ��ʱ�䡣
                                                              000��0ms���Ǿ���0������30us��60us�Ƚ�Сֵ����
                                                              001��0.45ms��
                                                              010��0.9ms��
                                                              011��1.8ms��
                                                              100��3.6ms��
                                                              101��20ms��
                                                              110��40ms��
                                                              111��80ms�� */
        unsigned char  reserved            : 1;  /* bit[3]  : ������ */
        unsigned char  vsys_uv_deb_sel     : 4;  /* bit[4-7]: vsys_uv�˲�ʱ��ѡ��
                                                              0000��0.25ms��
                                                              0001��0.5ms��
                                                              0010��1ms��
                                                              0011��2ms��
                                                              0100��3ms��
                                                              0101��4ms��
                                                              0110��5ms��
                                                              0111��6ms��
                                                              1000��7ms��
                                                              1001��8ms��
                                                              1010��10ms��
                                                              1011��20ms��
                                                              1100��30ms��
                                                              1101��40ms��
                                                              1110��60ms��
                                                              1111��80ms�� */
    } reg;
} PMIC_UV_VSYS_DEB_CTRL_UNION;
#endif
#define PMIC_UV_VSYS_DEB_CTRL_vsys_pwroff_deb_sel_START  (0)
#define PMIC_UV_VSYS_DEB_CTRL_vsys_pwroff_deb_sel_END    (2)
#define PMIC_UV_VSYS_DEB_CTRL_vsys_uv_deb_sel_START      (4)
#define PMIC_UV_VSYS_DEB_CTRL_vsys_uv_deb_sel_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK0_3_OCP_CTRL_UNION
 �ṹ˵��  : BUCK0_3_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0D0����ֵ:0xFF�����:8
 �Ĵ���˵��: BUCK0/1/2/3 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ocp_auto_stop : 2;  /* bit[0-1]: BUCK3�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck2_ocp_auto_stop : 2;  /* bit[2-3]: BUCK2�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck1_ocp_auto_stop : 2;  /* bit[4-5]: BUCK1�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck0_ocp_auto_stop : 2;  /* bit[6-7]: BUCK0�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_BUCK0_3_OCP_CTRL_UNION;
#endif
#define PMIC_BUCK0_3_OCP_CTRL_buck3_ocp_auto_stop_START  (0)
#define PMIC_BUCK0_3_OCP_CTRL_buck3_ocp_auto_stop_END    (1)
#define PMIC_BUCK0_3_OCP_CTRL_buck2_ocp_auto_stop_START  (2)
#define PMIC_BUCK0_3_OCP_CTRL_buck2_ocp_auto_stop_END    (3)
#define PMIC_BUCK0_3_OCP_CTRL_buck1_ocp_auto_stop_START  (4)
#define PMIC_BUCK0_3_OCP_CTRL_buck1_ocp_auto_stop_END    (5)
#define PMIC_BUCK0_3_OCP_CTRL_buck0_ocp_auto_stop_START  (6)
#define PMIC_BUCK0_3_OCP_CTRL_buck0_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK4_LDO0_1_OCP_CTRL_UNION
 �ṹ˵��  : BUCK4_LDO0_1_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0D1����ֵ:0xF7�����:8
 �Ĵ���˵��: BUCK4/LDO0/1/2 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo2_ocp_auto_stop  : 2;  /* bit[0-1]: LDO2�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo1_ocp_auto_stop  : 2;  /* bit[2-3]: LDO1�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo0_ocp_auto_stop  : 2;  /* bit[4-5]: LDO0�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck4_ocp_auto_stop : 2;  /* bit[6-7]: BUCK4�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_BUCK4_LDO0_1_OCP_CTRL_UNION;
#endif
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ldo2_ocp_auto_stop_START   (0)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ldo2_ocp_auto_stop_END     (1)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ldo1_ocp_auto_stop_START   (2)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ldo1_ocp_auto_stop_END     (3)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ldo0_ocp_auto_stop_START   (4)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ldo0_ocp_auto_stop_END     (5)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_buck4_ocp_auto_stop_START  (6)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_buck4_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO3_7_OCP_CTRL_UNION
 �ṹ˵��  : LDO3_7_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0D2����ֵ:0x5F�����:8
 �Ĵ���˵��: LCO3/4/5/7 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo7_ocp_auto_stop : 2;  /* bit[0-1]: LDO7�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                             X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                             01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                             11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo5_ocp_auto_stop : 2;  /* bit[2-3]: LDO5�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                             X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                             01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                             11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo4_ocp_auto_stop : 2;  /* bit[4-5]: LDO4�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                             X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                             01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                             11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo3_ocp_auto_stop : 2;  /* bit[6-7]: LDO3�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                             X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                             01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                             11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO3_7_OCP_CTRL_UNION;
#endif
#define PMIC_LDO3_7_OCP_CTRL_ldo7_ocp_auto_stop_START  (0)
#define PMIC_LDO3_7_OCP_CTRL_ldo7_ocp_auto_stop_END    (1)
#define PMIC_LDO3_7_OCP_CTRL_ldo5_ocp_auto_stop_START  (2)
#define PMIC_LDO3_7_OCP_CTRL_ldo5_ocp_auto_stop_END    (3)
#define PMIC_LDO3_7_OCP_CTRL_ldo4_ocp_auto_stop_START  (4)
#define PMIC_LDO3_7_OCP_CTRL_ldo4_ocp_auto_stop_END    (5)
#define PMIC_LDO3_7_OCP_CTRL_ldo3_ocp_auto_stop_START  (6)
#define PMIC_LDO3_7_OCP_CTRL_ldo3_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO8_11_OCP_CTRL_UNION
 �ṹ˵��  : LDO8_11_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0D3����ֵ:0x5D�����:8
 �Ĵ���˵��: LDO8/9/10/11 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo11_ocp_auto_stop : 2;  /* bit[0-1]: LDO11�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo10_ocp_auto_stop : 2;  /* bit[2-3]: LDO10�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo9_ocp_auto_stop  : 2;  /* bit[4-5]: LDO9�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo8_ocp_auto_stop  : 2;  /* bit[6-7]: LDO8�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO8_11_OCP_CTRL_UNION;
#endif
#define PMIC_LDO8_11_OCP_CTRL_ldo11_ocp_auto_stop_START  (0)
#define PMIC_LDO8_11_OCP_CTRL_ldo11_ocp_auto_stop_END    (1)
#define PMIC_LDO8_11_OCP_CTRL_ldo10_ocp_auto_stop_START  (2)
#define PMIC_LDO8_11_OCP_CTRL_ldo10_ocp_auto_stop_END    (3)
#define PMIC_LDO8_11_OCP_CTRL_ldo9_ocp_auto_stop_START   (4)
#define PMIC_LDO8_11_OCP_CTRL_ldo9_ocp_auto_stop_END     (5)
#define PMIC_LDO8_11_OCP_CTRL_ldo8_ocp_auto_stop_START   (6)
#define PMIC_LDO8_11_OCP_CTRL_ldo8_ocp_auto_stop_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO12_15_OCP_CTRL_UNION
 �ṹ˵��  : LDO12_15_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0D4����ֵ:0x55�����:8
 �Ĵ���˵��: LDO12/13/14/15 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo15_ocp_auto_stop : 2;  /* bit[0-1]: LDO15�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo14_ocp_auto_stop : 2;  /* bit[2-3]: LDO14�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo13_ocp_auto_stop : 2;  /* bit[4-5]: LDO13�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo12_ocp_auto_stop : 2;  /* bit[6-7]: LDO12�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO12_15_OCP_CTRL_UNION;
#endif
#define PMIC_LDO12_15_OCP_CTRL_ldo15_ocp_auto_stop_START  (0)
#define PMIC_LDO12_15_OCP_CTRL_ldo15_ocp_auto_stop_END    (1)
#define PMIC_LDO12_15_OCP_CTRL_ldo14_ocp_auto_stop_START  (2)
#define PMIC_LDO12_15_OCP_CTRL_ldo14_ocp_auto_stop_END    (3)
#define PMIC_LDO12_15_OCP_CTRL_ldo13_ocp_auto_stop_START  (4)
#define PMIC_LDO12_15_OCP_CTRL_ldo13_ocp_auto_stop_END    (5)
#define PMIC_LDO12_15_OCP_CTRL_ldo12_ocp_auto_stop_START  (6)
#define PMIC_LDO12_15_OCP_CTRL_ldo12_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO16_20_OCP_CTRL_UNION
 �ṹ˵��  : LDO16_20_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0D5����ֵ:0x55�����:8
 �Ĵ���˵��: LDO16/17/19/20 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo20_ocp_auto_stop : 2;  /* bit[0-1]: LDO20�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo19_ocp_auto_stop : 2;  /* bit[2-3]: LDO19�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo17_ocp_auto_stop : 2;  /* bit[4-5]: LDO17�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo16_ocp_auto_stop : 2;  /* bit[6-7]: LDO16�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO16_20_OCP_CTRL_UNION;
#endif
#define PMIC_LDO16_20_OCP_CTRL_ldo20_ocp_auto_stop_START  (0)
#define PMIC_LDO16_20_OCP_CTRL_ldo20_ocp_auto_stop_END    (1)
#define PMIC_LDO16_20_OCP_CTRL_ldo19_ocp_auto_stop_START  (2)
#define PMIC_LDO16_20_OCP_CTRL_ldo19_ocp_auto_stop_END    (3)
#define PMIC_LDO16_20_OCP_CTRL_ldo17_ocp_auto_stop_START  (4)
#define PMIC_LDO16_20_OCP_CTRL_ldo17_ocp_auto_stop_END    (5)
#define PMIC_LDO16_20_OCP_CTRL_ldo16_ocp_auto_stop_START  (6)
#define PMIC_LDO16_20_OCP_CTRL_ldo16_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO21_24_OCP_CTRL_UNION
 �ṹ˵��  : LDO21_24_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0D6����ֵ:0x5D�����:8
 �Ĵ���˵��: LDO21/22/23/24 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo24_ocp_auto_stop : 2;  /* bit[0-1]: LDO24�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo23_ocp_auto_stop : 2;  /* bit[2-3]: LDO23�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo22_ocp_auto_stop : 2;  /* bit[4-5]: LDO22�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo21_ocp_auto_stop : 2;  /* bit[6-7]: LDO21�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO21_24_OCP_CTRL_UNION;
#endif
#define PMIC_LDO21_24_OCP_CTRL_ldo24_ocp_auto_stop_START  (0)
#define PMIC_LDO21_24_OCP_CTRL_ldo24_ocp_auto_stop_END    (1)
#define PMIC_LDO21_24_OCP_CTRL_ldo23_ocp_auto_stop_START  (2)
#define PMIC_LDO21_24_OCP_CTRL_ldo23_ocp_auto_stop_END    (3)
#define PMIC_LDO21_24_OCP_CTRL_ldo22_ocp_auto_stop_START  (4)
#define PMIC_LDO21_24_OCP_CTRL_ldo22_ocp_auto_stop_END    (5)
#define PMIC_LDO21_24_OCP_CTRL_ldo21_ocp_auto_stop_START  (6)
#define PMIC_LDO21_24_OCP_CTRL_ldo21_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO25_28_OCP_CTRL_UNION
 �ṹ˵��  : LDO25_28_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0D7����ֵ:0x7D�����:8
 �Ĵ���˵��: LDO25/26/27/28 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo28_ocp_auto_stop : 2;  /* bit[0-1]: LDO28�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo27_ocp_auto_stop : 2;  /* bit[2-3]: LDO27�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo26_ocp_auto_stop : 2;  /* bit[4-5]: LDO26�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo25_ocp_auto_stop : 2;  /* bit[6-7]: LDO25�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO25_28_OCP_CTRL_UNION;
#endif
#define PMIC_LDO25_28_OCP_CTRL_ldo28_ocp_auto_stop_START  (0)
#define PMIC_LDO25_28_OCP_CTRL_ldo28_ocp_auto_stop_END    (1)
#define PMIC_LDO25_28_OCP_CTRL_ldo27_ocp_auto_stop_START  (2)
#define PMIC_LDO25_28_OCP_CTRL_ldo27_ocp_auto_stop_END    (3)
#define PMIC_LDO25_28_OCP_CTRL_ldo26_ocp_auto_stop_START  (4)
#define PMIC_LDO25_28_OCP_CTRL_ldo26_ocp_auto_stop_END    (5)
#define PMIC_LDO25_28_OCP_CTRL_ldo25_ocp_auto_stop_START  (6)
#define PMIC_LDO25_28_OCP_CTRL_ldo25_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LDO29_32_OCP_CTRL_UNION
 �ṹ˵��  : LDO29_32_OCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0D8����ֵ:0x75�����:8
 �Ĵ���˵��: LDO29/30/31/32 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo32_ocp_auto_stop : 2;  /* bit[0-1]: LDO32�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11����֧�֡� */
        unsigned char  ldo31_ocp_auto_stop : 2;  /* bit[2-3]: LDO31�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo30_ocp_auto_stop : 2;  /* bit[4-5]: LDO30�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  ldo29_ocp_auto_stop : 2;  /* bit[6-7]: LDO29�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_LDO29_32_OCP_CTRL_UNION;
#endif
#define PMIC_LDO29_32_OCP_CTRL_ldo32_ocp_auto_stop_START  (0)
#define PMIC_LDO29_32_OCP_CTRL_ldo32_ocp_auto_stop_END    (1)
#define PMIC_LDO29_32_OCP_CTRL_ldo31_ocp_auto_stop_START  (2)
#define PMIC_LDO29_32_OCP_CTRL_ldo31_ocp_auto_stop_END    (3)
#define PMIC_LDO29_32_OCP_CTRL_ldo30_ocp_auto_stop_START  (4)
#define PMIC_LDO29_32_OCP_CTRL_ldo30_ocp_auto_stop_END    (5)
#define PMIC_LDO29_32_OCP_CTRL_ldo29_ocp_auto_stop_START  (6)
#define PMIC_LDO29_32_OCP_CTRL_ldo29_ocp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLASS_BUCK0_SCP_CTRL_UNION
 �ṹ˵��  : CLASS_BUCK0_SCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0D9����ֵ:0x0F�����:8
 �Ĵ���˵��: CLASS/BUCK0 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_scp_auto_stop  : 2;  /* bit[0-1]: BUCK0�ڷ���SCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                               X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                               01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                               11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  classd_ocp_auto_stop : 2;  /* bit[2-3]: class�ڷ���OCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                               X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                               01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                               11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  reserved             : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_CLASS_BUCK0_SCP_CTRL_UNION;
#endif
#define PMIC_CLASS_BUCK0_SCP_CTRL_buck0_scp_auto_stop_START   (0)
#define PMIC_CLASS_BUCK0_SCP_CTRL_buck0_scp_auto_stop_END     (1)
#define PMIC_CLASS_BUCK0_SCP_CTRL_classd_ocp_auto_stop_START  (2)
#define PMIC_CLASS_BUCK0_SCP_CTRL_classd_ocp_auto_stop_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_BUCK1_4_SCP_CTRL_UNION
 �ṹ˵��  : BUCK1_4_SCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0DA����ֵ:0xFF�����:8
 �Ĵ���˵��: BUCK1/2/3/4 OCP�Զ��ضϿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_scp_auto_stop : 2;  /* bit[0-1]: BUCK4�ڷ���SCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck3_scp_auto_stop : 2;  /* bit[2-3]: BUCK3�ڷ���SCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck2_scp_auto_stop : 2;  /* bit[4-5]: BUCK2�ڷ���SCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
        unsigned char  buck1_scp_auto_stop : 2;  /* bit[6-7]: BUCK1�ڷ���SCPʱ�Ƿ��Զ��رչ���ѡ��λ��
                                                              X0�� ���ϱ��жϣ����Զ��رգ�PMU���µ磻
                                                              01�� �ϱ��жϣ��Զ��رգ�PMU���µ磻
                                                              11���ϱ��жϣ��Զ��رգ�PMU�µ硣 */
    } reg;
} PMIC_BUCK1_4_SCP_CTRL_UNION;
#endif
#define PMIC_BUCK1_4_SCP_CTRL_buck4_scp_auto_stop_START  (0)
#define PMIC_BUCK1_4_SCP_CTRL_buck4_scp_auto_stop_END    (1)
#define PMIC_BUCK1_4_SCP_CTRL_buck3_scp_auto_stop_START  (2)
#define PMIC_BUCK1_4_SCP_CTRL_buck3_scp_auto_stop_END    (3)
#define PMIC_BUCK1_4_SCP_CTRL_buck2_scp_auto_stop_START  (4)
#define PMIC_BUCK1_4_SCP_CTRL_buck2_scp_auto_stop_END    (5)
#define PMIC_BUCK1_4_SCP_CTRL_buck1_scp_auto_stop_START  (6)
#define PMIC_BUCK1_4_SCP_CTRL_buck1_scp_auto_stop_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SYS_CTRL0_UNION
 �ṹ˵��  : SYS_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0DB����ֵ:0x00�����:8
 �Ĵ���˵��: ϵͳ���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vsys_pwroff_abs_pd_mask : 1;  /* bit[0]  : vsysС��2.3vʱ�Ƿ��Զ��ػ�����λ��
                                                                  0���Զ��ػ�(����2.3vʱ�䳬��35us���ϲ��ܱ�֤�ػ��ɹ�)��
                                                                  1�����Զ��ػ��� */
        unsigned char  vsys_pwroff_deb_pd_mask : 1;  /* bit[1]  : vsysС��2.6vʱ�Ƿ��Զ��ػ�����λ��
                                                                  0���Զ��ػ���
                                                                  1�����Զ��ػ��� */
        unsigned char  thsd_otmp140_pd_mask    : 1;  /* bit[2]  : �¶ȳ���140��ʱ�Ƿ��Զ��ػ�����λ��
                                                                  0���Զ��ػ���
                                                                  1�����Զ��ػ��� */
        unsigned char  vsys_ov_pd_mask         : 1;  /* bit[3]  : vsys��ѹʱ�Ƿ��Զ��ػ�����λ��
                                                                  0���Զ��ػ���
                                                                  1�����Զ��ػ��� */
        unsigned char  reserved                : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_SYS_CTRL0_UNION;
#endif
#define PMIC_SYS_CTRL0_vsys_pwroff_abs_pd_mask_START  (0)
#define PMIC_SYS_CTRL0_vsys_pwroff_abs_pd_mask_END    (0)
#define PMIC_SYS_CTRL0_vsys_pwroff_deb_pd_mask_START  (1)
#define PMIC_SYS_CTRL0_vsys_pwroff_deb_pd_mask_END    (1)
#define PMIC_SYS_CTRL0_thsd_otmp140_pd_mask_START     (2)
#define PMIC_SYS_CTRL0_thsd_otmp140_pd_mask_END       (2)
#define PMIC_SYS_CTRL0_vsys_ov_pd_mask_START          (3)
#define PMIC_SYS_CTRL0_vsys_ov_pd_mask_END            (3)


/*****************************************************************************
 �ṹ��    : PMIC_SYS_CTRL1_UNION
 �ṹ˵��  : SYS_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x0DC����ֵ:0x00�����:8
 �Ĵ���˵��: ϵͳ���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_smpl_open_en  : 1;  /* bit[0]  : SMPL����ʹ��λ��
                                                           0����֧�ֵ�ص�����������
                                                           1��֧�ֵ�ص����������� */
        unsigned char  np_smpl_time_sel : 2;  /* bit[1-2]: ��ص����ٲ���������ʱ��ѡ��
                                                           00��0.5s��
                                                           01��1s��
                                                           10��1.5s��
                                                           11��2s�� */
        unsigned char  reserved_0       : 1;  /* bit[3]  : ������ */
        unsigned char  np_pwron_8s_sel  : 1;  /* bit[4]  : ����״̬�°���pwron_n����8s�ػ���������ѡ��
                                                           0��������������
                                                           1���������ػ��� */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_SYS_CTRL1_UNION;
#endif
#define PMIC_SYS_CTRL1_np_smpl_open_en_START   (0)
#define PMIC_SYS_CTRL1_np_smpl_open_en_END     (0)
#define PMIC_SYS_CTRL1_np_smpl_time_sel_START  (1)
#define PMIC_SYS_CTRL1_np_smpl_time_sel_END    (2)
#define PMIC_SYS_CTRL1_np_pwron_8s_sel_START   (4)
#define PMIC_SYS_CTRL1_np_pwron_8s_sel_END     (4)


/*****************************************************************************
 �ṹ��    : PMIC_COUL_ECO_MASK_UNION
 �ṹ˵��  : COUL_ECO_MASK �Ĵ����ṹ���塣��ַƫ����:0x0DD����ֵ:0x07�����:8
 �Ĵ���˵��: ���ؼ�ECOʹ�ܿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  coul_codec_clk_en_mask : 1;  /* bit[0]  : CODEC_CLK_EN���ƿ��ؼƽ���ECOģʽ����λ��
                                                                 0�������Σ�
                                                                 1�����Ρ� */
        unsigned char  coul_wifi_clk_en_mask  : 1;  /* bit[1]  : WIFI_BT_CLK_EN���ƿ��ؼƽ���ECOģʽ����λ��
                                                                 0�������Σ�
                                                                 1�����Ρ� */
        unsigned char  coul_sys_clk_en_mask   : 1;  /* bit[2]  : SYS_CLK_EN���ƿ��ؼƽ���ECOģʽ����λ��
                                                                 0�������Σ�
                                                                 1�����Ρ� */
        unsigned char  reserved               : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_COUL_ECO_MASK_UNION;
#endif
#define PMIC_COUL_ECO_MASK_coul_codec_clk_en_mask_START  (0)
#define PMIC_COUL_ECO_MASK_coul_codec_clk_en_mask_END    (0)
#define PMIC_COUL_ECO_MASK_coul_wifi_clk_en_mask_START   (1)
#define PMIC_COUL_ECO_MASK_coul_wifi_clk_en_mask_END     (1)
#define PMIC_COUL_ECO_MASK_coul_sys_clk_en_mask_START    (2)
#define PMIC_COUL_ECO_MASK_coul_sys_clk_en_mask_END      (2)


/*****************************************************************************
 �ṹ��    : PMIC_SIM_CTRL_UNION
 �ṹ˵��  : SIM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0DE����ֵ:0x00�����:8
 �Ĵ���˵��: SIM���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sim0_hpd_r_pd_en : 1;  /* bit[0]: ����sim0_hpd�������ж�ʱ�Ƿ�ر�LDO11����λ��
                                                         0�����ر�LDO11��
                                                         1���ر�LDO11�� */
        unsigned char  sim0_hpd_f_pd_en : 1;  /* bit[1]: ����sim0_hpd�½����ж�ʱ�Ƿ�ر�LDO11����λ��
                                                         0�����ر�LDO11��
                                                         1���ر�LDO11�� */
        unsigned char  sim0_hpd_h_pd_en : 1;  /* bit[2]: ����sim0_hpd�ߵ�ƽ�ж�ʱ�Ƿ�ر�LDO11����λ��
                                                         0�����ر�LDO11��
                                                         1���ر�LDO11�� */
        unsigned char  sim0_hpd_l_pd_en : 1;  /* bit[3]: ����sim0_hpd�͵�ƽ�ж�ʱ�Ƿ�ر�LDO11����λ��
                                                         0�����ر�LDO11��
                                                         1���ر�LDO11�� */
        unsigned char  sim1_hpd_r_pd_en : 1;  /* bit[4]: ����sim1_hpd�������ж�ʱ�Ƿ�ر�LDO12����λ��
                                                         0�����ر�LDO12��
                                                         1���ر�LDO12�� */
        unsigned char  sim1_hpd_f_pd_en : 1;  /* bit[5]: ����sim1_hpd�½����ж�ʱ�Ƿ�ر�LDO12����λ��
                                                         0�����ر�LDO12��
                                                         1���ر�LDO12�� */
        unsigned char  sim1_hpd_h_pd_en : 1;  /* bit[6]: ����sim1_hpd�ߵ�ƽ�ж�ʱ�Ƿ�ر�LDO12����λ��
                                                         0�����ر�LDO12��
                                                         1���ر�LDO12�� */
        unsigned char  sim1_hpd_l_pd_en : 1;  /* bit[7]: ����sim1_hpd�͵�ƽ�ж�ʱ�Ƿ�ر�LDO12����λ��
                                                         0�����ر�LDO12��
                                                         1���ر�LDO12�� */
    } reg;
} PMIC_SIM_CTRL_UNION;
#endif
#define PMIC_SIM_CTRL_sim0_hpd_r_pd_en_START  (0)
#define PMIC_SIM_CTRL_sim0_hpd_r_pd_en_END    (0)
#define PMIC_SIM_CTRL_sim0_hpd_f_pd_en_START  (1)
#define PMIC_SIM_CTRL_sim0_hpd_f_pd_en_END    (1)
#define PMIC_SIM_CTRL_sim0_hpd_h_pd_en_START  (2)
#define PMIC_SIM_CTRL_sim0_hpd_h_pd_en_END    (2)
#define PMIC_SIM_CTRL_sim0_hpd_l_pd_en_START  (3)
#define PMIC_SIM_CTRL_sim0_hpd_l_pd_en_END    (3)
#define PMIC_SIM_CTRL_sim1_hpd_r_pd_en_START  (4)
#define PMIC_SIM_CTRL_sim1_hpd_r_pd_en_END    (4)
#define PMIC_SIM_CTRL_sim1_hpd_f_pd_en_START  (5)
#define PMIC_SIM_CTRL_sim1_hpd_f_pd_en_END    (5)
#define PMIC_SIM_CTRL_sim1_hpd_h_pd_en_START  (6)
#define PMIC_SIM_CTRL_sim1_hpd_h_pd_en_END    (6)
#define PMIC_SIM_CTRL_sim1_hpd_l_pd_en_START  (7)
#define PMIC_SIM_CTRL_sim1_hpd_l_pd_en_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SIM_DEB_CTRL_UNION
 �ṹ˵��  : SIM_DEB_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0DF����ֵ:0x27�����:8
 �Ĵ���˵��: SIM�˲����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sim_hpd_deb_sel : 5;  /* bit[0-4]: sim_hpd�����ط�����ʵ�ʲ��������жϵ�ʱ��������������ټ�90us����
                                                          0x0 �� 120us��0x1 ��180us��
                                                          0x2 ��240us��0x3 �� 300us��
                                                          0x4 �� 360us��0x5 �� 420us��
                                                          0x6 �� 480us��0x7 �� 540us��
                                                          0x8 �� 600us��0x9 �� 740us��
                                                          0xa �� 1ms��0xb �� 1.25ms��
                                                          0xc �� 1.5ms��0xd �� 1.75ms��
                                                          0xe �� 2ms��0xf �� 2.25ms��
                                                          0x10�� 2.5ms��0x11�� 2.75ms��
                                                          0x12�� 3ms��0x13�� 4ms��
                                                          0x14�� 5ms��0x15�� 6ms��
                                                          0x16�� 7ms��0x17�� 8ms��
                                                          0x18�� 9ms��0x19�� 10ms��
                                                          0x1a�� 11ms��0x1b�� 12ms��
                                                          0x1c�� 13ms��0x1d�� 14ms��
                                                          0x1e�� 15ms��0x1f�� 16ms��
                                                          ��0x0-0x8����60us���ҵ�ƫ�0x9-0x12����250us���ҵ�ƫ�0x13-0x1f����2ms���ҵ�ƫ� */
        unsigned char  sim_del_sel     : 3;  /* bit[5-7]: SIM0/1_HPD�����жϵ��Զ��رյ�Դ�ӳ�ʱ��ѡ��
                                                          000��60us��
                                                          001��120us��
                                                          010��180us��
                                                          011��240us��
                                                          100��360us��
                                                          101��480us��
                                                          110��540us��
                                                          111��600us�� */
    } reg;
} PMIC_SIM_DEB_CTRL_UNION;
#endif
#define PMIC_SIM_DEB_CTRL_sim_hpd_deb_sel_START  (0)
#define PMIC_SIM_DEB_CTRL_sim_hpd_deb_sel_END    (4)
#define PMIC_SIM_DEB_CTRL_sim_del_sel_START      (5)
#define PMIC_SIM_DEB_CTRL_sim_del_sel_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_AUX_IBIAS_CFG_UNION
 �ṹ˵��  : AUX_IBIAS_CFG �Ĵ����ṹ���塣��ַƫ����:0x0E0����ֵ:0x0A�����:8
 �Ĵ���˵��: DAC IBIAS���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  aux_offset_cfg : 2;  /* bit[0-1]: AUXDAC OFFSET���ڡ�
                                                         00��+10mV��
                                                         01��0mV��
                                                         10��0mV��
                                                         11��-10mV�� */
        unsigned char  aux_ibias_cfg  : 2;  /* bit[2-3]: AUXDACƫ�õ������ڡ�
                                                         00��2.5uA��
                                                         01��5.0uA��
                                                         10��5.0uA��
                                                         11��7.5uA�� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_AUX_IBIAS_CFG_UNION;
#endif
#define PMIC_AUX_IBIAS_CFG_aux_offset_cfg_START  (0)
#define PMIC_AUX_IBIAS_CFG_aux_offset_cfg_END    (1)
#define PMIC_AUX_IBIAS_CFG_aux_ibias_cfg_START   (2)
#define PMIC_AUX_IBIAS_CFG_aux_ibias_cfg_END     (3)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_0_UNION
 �ṹ˵��  : IRQ_MASK_0 �Ĵ����ṹ���塣��ַƫ����:0x0E1����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK0���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_0 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]�����������ж����Σ�
                                                     bit[6]�������ͷ��ж����Σ�
                                                     bit[5]������1s�ж����Σ�
                                                     bit[4]������6s�ж����Σ�
                                                     bit[3]�������ж����Σ�
                                                     bit[2]��vbus�γ��ж����Σ�
                                                     bit[1]��vbus�����ж����Σ�
                                                     bit[0]��por�ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_0_UNION;
#endif
#define PMIC_IRQ_MASK_0_irq_mask_0_START  (0)
#define PMIC_IRQ_MASK_0_irq_mask_0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_1_UNION
 �ṹ˵��  : IRQ_MASK_1 �Ĵ����ṹ���塣��ַƫ����:0x0E2����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK1���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_1 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]������125���ж����Σ�
                                                     bit[6]������140���ж����Σ�
                                                     bit[5]��ȥ��Ƿѹ�ػ��ж����Σ�
                                                     bit[4]������Ƿѹ�ػ��ж����Σ�
                                                     bit[3]��Ƿѹ�����ж����Σ�
                                                     bit[2]����ѹ�����ж����Σ�
                                                     bit[1]�����ؼ��ж������Σ�
                                                     bit[0]��OCP�ж������Ρ� */
    } reg;
} PMIC_IRQ_MASK_1_UNION;
#endif
#define PMIC_IRQ_MASK_1_irq_mask_1_START  (0)
#define PMIC_IRQ_MASK_1_irq_mask_1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_2_UNION
 �ṹ˵��  : IRQ_MASK_2 �Ĵ����ṹ���塣��ַƫ����:0x0E3����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK2���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_2 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7��1]��������
                                                     bit[0]���ȸ�λ�ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_2_UNION;
#endif
#define PMIC_IRQ_MASK_2_irq_mask_2_START  (0)
#define PMIC_IRQ_MASK_2_irq_mask_2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_3_UNION
 �ṹ˵��  : IRQ_MASK_3 �Ĵ����ṹ���塣��ַƫ����:0x0E4����ֵ:0xCC�����:8
 �Ĵ���˵��: IRQ_MASK3���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_3 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]��sim_hpd1�͵�ƽ�ж����Σ�
                                                     bit[6]��sim_hpd1�ߵ�ƽ�ж����Σ�
                                                     bit[5]��sim_hpd1�½����ж����Σ�
                                                     bit[4]��sim_hpd1�������ж����Σ�
                                                     bit[3]��sim_hpd0�͵�ƽ�ж����Σ�
                                                     bit[2]��sim_hpd0�ߵ�ƽ�ж����Σ�
                                                     bit[1]��sim_hpd0�½����ж����Σ�
                                                     bit[0]��sim_hpd0�������ж����Σ�
                                                     bit[7]��bit[6]��bit[3]��bit[2]Ĭ�����Ρ� */
    } reg;
} PMIC_IRQ_MASK_3_UNION;
#endif
#define PMIC_IRQ_MASK_3_irq_mask_3_START  (0)
#define PMIC_IRQ_MASK_3_irq_mask_3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_4_UNION
 �ṹ˵��  : IRQ_MASK_4 �Ĵ����ṹ���塣��ַƫ����:0x0E5����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK4���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_4 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]��BUCK0��������ж����Σ�
                                                     bit[6]��BUCK1��������ж����Σ�
                                                     bit[5]��BUCK2��������ж����Σ�
                                                     bit[4]��BUCK3��������ж����Σ�
                                                     bit[3]��BUCK4��������ж����Σ�
                                                     bit[2]��LDO0_2��������ж����Σ�
                                                     bit[1]��LDO1��������ж����Σ�
                                                     bit[0]��LDO2��������ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_4_UNION;
#endif
#define PMIC_IRQ_MASK_4_irq_mask_4_START  (0)
#define PMIC_IRQ_MASK_4_irq_mask_4_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_5_UNION
 �ṹ˵��  : IRQ_MASK_5 �Ĵ����ṹ���塣��ַƫ����:0x0E6����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK5���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_5 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]��LDO3��������ж����Σ�
                                                     bit[6]��LDO4��������ж����Σ�
                                                     bit[5]��LDO5��������ж����Σ�
                                                     bit[4]��LDO7��������ж����Σ�
                                                     bit[3]��LDO8��������ж����Σ�
                                                     bit[2]��LDO9��������ж����Σ�
                                                     bit[1]��LDO10��������ж����Σ�
                                                     bit[0]��LDO11��������ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_5_UNION;
#endif
#define PMIC_IRQ_MASK_5_irq_mask_5_START  (0)
#define PMIC_IRQ_MASK_5_irq_mask_5_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_6_UNION
 �ṹ˵��  : IRQ_MASK_6 �Ĵ����ṹ���塣��ַƫ����:0x0E7����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK6���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_6 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]��LDO12��������ж����Σ�
                                                     bit[6]��LDO13��������ж����Σ�
                                                     bit[5]��LDO14��������ж����Σ�
                                                     bit[4]��LDO15��������ж����Σ�
                                                     bit[3]��LDO16��������ж����Σ�
                                                     bit[2]��LDO17��������ж����Σ�
                                                     bit[1]��LDO19��������ж����Σ�
                                                     bit[0]��LDO20��������ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_6_UNION;
#endif
#define PMIC_IRQ_MASK_6_irq_mask_6_START  (0)
#define PMIC_IRQ_MASK_6_irq_mask_6_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_7_UNION
 �ṹ˵��  : IRQ_MASK_7 �Ĵ����ṹ���塣��ַƫ����:0x0E8����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK7���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_7 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]��LDO21��������ж����Σ�
                                                     bit[6]��LDO22��������ж����Σ�
                                                     bit[5]��LDO23��������ж����Σ�
                                                     bit[4]��LDO24��������ж����Σ�
                                                     bit[3]��LDO25��������ж����Σ�
                                                     bit[2]��LDO26��������ж����Σ�
                                                     bit[1]��LDO27��������ж����Σ�
                                                     bit[0]��LDO28��������ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_7_UNION;
#endif
#define PMIC_IRQ_MASK_7_irq_mask_7_START  (0)
#define PMIC_IRQ_MASK_7_irq_mask_7_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_8_UNION
 �ṹ˵��  : IRQ_MASK_8 �Ĵ����ṹ���塣��ַƫ����:0x0E9����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK8���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_8 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7]��LDO29��������ж����Σ�
                                                     bit[6]��LDO30��������ж����Σ�
                                                     bit[5]��LDO31��������ж����Σ�
                                                     bit[4]��LDO32��������ж����Σ�
                                                     bit[3��1]��������
                                                     bit[0]��class��������ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_8_UNION;
#endif
#define PMIC_IRQ_MASK_8_irq_mask_8_START  (0)
#define PMIC_IRQ_MASK_8_irq_mask_8_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ_MASK_9_UNION
 �ṹ˵��  : IRQ_MASK_9 �Ĵ����ṹ���塣��ַƫ����:0x0EA����ֵ:0x00�����:8
 �Ĵ���˵��: IRQ_MASK9���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_9 : 8;  /* bit[0-7]: �ж�mask��д1���Ρ�
                                                     bit[7��5]��������
                                                     bit[4]��BUCK0�����·�ж����Σ�
                                                     bit[3]��BUCK1�����·�ж����Σ�
                                                     bit[2]��BUCK2�����·�ж����Σ�
                                                     bit[1]��BUCK3�����·�ж����Σ�
                                                     bit[0]��BUCK4�����·�ж����Ρ� */
    } reg;
} PMIC_IRQ_MASK_9_UNION;
#endif
#define PMIC_IRQ_MASK_9_irq_mask_9_START  (0)
#define PMIC_IRQ_MASK_9_irq_mask_9_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_0_UNION
 �ṹ˵��  : OTP0_0 �Ĵ����ṹ���塣��ַƫ����:0x0EB����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0�ض��Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob0 : 8;  /* bit[0-7]: OTP0�ض�ֵbit[7:0]�� */
    } reg;
} PMIC_OTP0_0_UNION;
#endif
#define PMIC_OTP0_0_otp0_pdob0_START  (0)
#define PMIC_OTP0_0_otp0_pdob0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_1_UNION
 �ṹ˵��  : OTP0_1 �Ĵ����ṹ���塣��ַƫ����:0x0EC����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0�ض��Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob1 : 8;  /* bit[0-7]: OTP0�ض�ֵbit[15:8]�� */
    } reg;
} PMIC_OTP0_1_UNION;
#endif
#define PMIC_OTP0_1_otp0_pdob1_START  (0)
#define PMIC_OTP0_1_otp0_pdob1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_2_UNION
 �ṹ˵��  : OTP0_2 �Ĵ����ṹ���塣��ַƫ����:0x0ED����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0�ض��Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob2 : 8;  /* bit[0-7]: OTP0�ض�ֵbit[23:16]�� */
    } reg;
} PMIC_OTP0_2_UNION;
#endif
#define PMIC_OTP0_2_otp0_pdob2_START  (0)
#define PMIC_OTP0_2_otp0_pdob2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_3_UNION
 �ṹ˵��  : OTP0_3 �Ĵ����ṹ���塣��ַƫ����:0x0EE����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0�ض��Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob3 : 8;  /* bit[0-7]: OTP0�ض�ֵbit[31:24]�� */
    } reg;
} PMIC_OTP0_3_UNION;
#endif
#define PMIC_OTP0_3_otp0_pdob3_START  (0)
#define PMIC_OTP0_3_otp0_pdob3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_CTRL_0_UNION
 �ṹ˵��  : OTP0_CTRL_0 �Ĵ����ṹ���塣��ַƫ����:0x0EF����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pwe_int   : 1;  /* bit[0]  : OTP0д�����źš�
                                                         0������otp_pwe������д������
                                                         1������otp_pwe������д������
                                                         �豣֤otp_pwe�ĸߵ�ƽ����ʱ������otp������Ҫ�� */
        unsigned char  otp0_pwe_pulse : 1;  /* bit[1]  : OTP0д������ơ�
                                                         0�����������壻
                                                         1������һ��310us�ĸߵ�ƽ���塣 */
        unsigned char  otp0_por_int   : 1;  /* bit[2]  : OTP0�������źš�
                                                         0������otp_por��������������
                                                         1������otp_por�������������
                                                         �豣֤otp_por�ĸߵ�ƽ����ʱ������otp������Ҫ�� */
        unsigned char  otp0_por_pulse : 1;  /* bit[3]  : OTP0��ʼ�������źš�
                                                         0�� ���������壻
                                                         1������һ��30us��por�ߵ�ƽ���塣 */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_OTP0_CTRL_0_UNION;
#endif
#define PMIC_OTP0_CTRL_0_otp0_pwe_int_START    (0)
#define PMIC_OTP0_CTRL_0_otp0_pwe_int_END      (0)
#define PMIC_OTP0_CTRL_0_otp0_pwe_pulse_START  (1)
#define PMIC_OTP0_CTRL_0_otp0_pwe_pulse_END    (1)
#define PMIC_OTP0_CTRL_0_otp0_por_int_START    (2)
#define PMIC_OTP0_CTRL_0_otp0_por_int_END      (2)
#define PMIC_OTP0_CTRL_0_otp0_por_pulse_START  (3)
#define PMIC_OTP0_CTRL_0_otp0_por_pulse_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_CTRL_1_UNION
 �ṹ˵��  : OTP0_CTRL_1 �Ĵ����ṹ���塣��ַƫ����:0x0F0����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pa     : 2;  /* bit[0-1]: OTP0�ĵ�ַ�źš�
                                                      00��ѡ��otp0������bit[7:0]���ж�/д������
                                                      01��ѡ��otp0������bit[15:8]���ж�/д������
                                                      10��ѡ��otp0������bit[23:16]���ж�/д������
                                                      11��ѡ��otp0������bit[31:24]���ж�/д������ */
        unsigned char  otp0_ptm    : 2;  /* bit[2-3]: OTP0����ģʽʹ���źš�
                                                      00���û�ģʽ��
                                                      01��margin-2��ģʽ��
                                                      10��margin-1��ģʽ��
                                                      11��δ���塣 */
        unsigned char  otp01_pprog : 1;  /* bit[4]  : OTP01���ģʽʹ���źš�
                                                      0���ر�otp��̣�
                                                      1��ʹ��otp��̡� */
        unsigned char  reserved    : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_OTP0_CTRL_1_UNION;
#endif
#define PMIC_OTP0_CTRL_1_otp0_pa_START      (0)
#define PMIC_OTP0_CTRL_1_otp0_pa_END        (1)
#define PMIC_OTP0_CTRL_1_otp0_ptm_START     (2)
#define PMIC_OTP0_CTRL_1_otp0_ptm_END       (3)
#define PMIC_OTP0_CTRL_1_otp01_pprog_START  (4)
#define PMIC_OTP0_CTRL_1_otp01_pprog_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_WDATA_UNION
 �ṹ˵��  : OTP0_WDATA �Ĵ����ṹ���塣��ַƫ����:0x0F1����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0д�������ݼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdin : 8;  /* bit[0-7]: OTP0������ֵ�Ĵ����� */
    } reg;
} PMIC_OTP0_WDATA_UNION;
#endif
#define PMIC_OTP0_WDATA_otp0_pdin_START  (0)
#define PMIC_OTP0_WDATA_otp0_pdin_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_0_W_UNION
 �ṹ˵��  : OTP0_0_W �Ĵ����ṹ���塣��ַƫ����:0x0F2����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0������Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob0_w : 8;  /* bit[0-7]: ��OTP0_0�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP0_0_W_UNION;
#endif
#define PMIC_OTP0_0_W_otp0_pdob0_w_START  (0)
#define PMIC_OTP0_0_W_otp0_pdob0_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_1_W_UNION
 �ṹ˵��  : OTP0_1_W �Ĵ����ṹ���塣��ַƫ����:0x0F3����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0������Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob1_w : 8;  /* bit[0-7]: ��OTP0_1�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP0_1_W_UNION;
#endif
#define PMIC_OTP0_1_W_otp0_pdob1_w_START  (0)
#define PMIC_OTP0_1_W_otp0_pdob1_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_2_W_UNION
 �ṹ˵��  : OTP0_2_W �Ĵ����ṹ���塣��ַƫ����:0x0F4����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0������Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob2_w : 8;  /* bit[0-7]: ��OTP0_2�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP0_2_W_UNION;
#endif
#define PMIC_OTP0_2_W_otp0_pdob2_w_START  (0)
#define PMIC_OTP0_2_W_otp0_pdob2_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP0_3_W_UNION
 �ṹ˵��  : OTP0_3_W �Ĵ����ṹ���塣��ַƫ����:0x0F5����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0������Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob3_w : 8;  /* bit[0-7]: ��OTP0_3�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP0_3_W_UNION;
#endif
#define PMIC_OTP0_3_W_otp0_pdob3_w_START  (0)
#define PMIC_OTP0_3_W_otp0_pdob3_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_0_UNION
 �ṹ˵��  : OTP1_0 �Ĵ����ṹ���塣��ַƫ����:0x0F6����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1�ض��Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob0 : 8;  /* bit[0-7]: OTP1�ض�ֵbit[7:0]�� */
    } reg;
} PMIC_OTP1_0_UNION;
#endif
#define PMIC_OTP1_0_otp1_pdob0_START  (0)
#define PMIC_OTP1_0_otp1_pdob0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_1_UNION
 �ṹ˵��  : OTP1_1 �Ĵ����ṹ���塣��ַƫ����:0x0F7����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1�ض��Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob1 : 8;  /* bit[0-7]: OTP1�ض�ֵbit[15:8]�� */
    } reg;
} PMIC_OTP1_1_UNION;
#endif
#define PMIC_OTP1_1_otp1_pdob1_START  (0)
#define PMIC_OTP1_1_otp1_pdob1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_2_UNION
 �ṹ˵��  : OTP1_2 �Ĵ����ṹ���塣��ַƫ����:0x0F8����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1�ض��Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob2 : 8;  /* bit[0-7]: OTP1�ض�ֵbit[23:16]�� */
    } reg;
} PMIC_OTP1_2_UNION;
#endif
#define PMIC_OTP1_2_otp1_pdob2_START  (0)
#define PMIC_OTP1_2_otp1_pdob2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_3_UNION
 �ṹ˵��  : OTP1_3 �Ĵ����ṹ���塣��ַƫ����:0x0F9����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1�ض��Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob3 : 8;  /* bit[0-7]: OTP1�ض�ֵbit[31:24]�� */
    } reg;
} PMIC_OTP1_3_UNION;
#endif
#define PMIC_OTP1_3_otp1_pdob3_START  (0)
#define PMIC_OTP1_3_otp1_pdob3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_CTRL_0_UNION
 �ṹ˵��  : OTP1_CTRL_0 �Ĵ����ṹ���塣��ַƫ����:0x0FA����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pwe_int   : 1;  /* bit[0]  : OTP1д�����źš�
                                                         0������otp_pwe������д������
                                                         1������otp_pwe������д������
                                                         �豣֤otp_pwe�ĸߵ�ƽ����ʱ������otp������Ҫ�� */
        unsigned char  otp1_pwe_pulse : 1;  /* bit[1]  : OTP1д������ơ�
                                                         0�����������壻
                                                         1������һ��310us�ĸߵ�ƽ���塣 */
        unsigned char  otp1_por_int   : 1;  /* bit[2]  : OTP1�������źš�
                                                         0������otp_por��������������
                                                         1������otp_por�������������
                                                         �豣֤otp_por�ĸߵ�ƽ����ʱ������otp������Ҫ�� */
        unsigned char  otp1_por_pulse : 1;  /* bit[3]  : OTP1��ʼ�������źš�
                                                         0�� ���������壻
                                                         1������һ��30us��por�ߵ�ƽ���塣 */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_OTP1_CTRL_0_UNION;
#endif
#define PMIC_OTP1_CTRL_0_otp1_pwe_int_START    (0)
#define PMIC_OTP1_CTRL_0_otp1_pwe_int_END      (0)
#define PMIC_OTP1_CTRL_0_otp1_pwe_pulse_START  (1)
#define PMIC_OTP1_CTRL_0_otp1_pwe_pulse_END    (1)
#define PMIC_OTP1_CTRL_0_otp1_por_int_START    (2)
#define PMIC_OTP1_CTRL_0_otp1_por_int_END      (2)
#define PMIC_OTP1_CTRL_0_otp1_por_pulse_START  (3)
#define PMIC_OTP1_CTRL_0_otp1_por_pulse_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_CTRL_1_UNION
 �ṹ˵��  : OTP1_CTRL_1 �Ĵ����ṹ���塣��ַƫ����:0x0FB����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pa  : 2;  /* bit[0-1]: OTP1�ĵ�ַ�źš�
                                                   00��ѡ��otp1������bit[7��0]���ж�/д������
                                                   01��ѡ��otp1������bit[15��8]���ж�/д������
                                                   10��ѡ��otp1������bit[23��16]���ж�/д������
                                                   11��ѡ��otp1������bit[31��24]���ж�/д������ */
        unsigned char  otp1_ptm : 2;  /* bit[2-3]: OTP1����ģʽʹ���źš�
                                                   00���û�ģʽ��
                                                   01��margin-2��ģʽ��
                                                   10��margin-1��ģʽ��
                                                   11��δ���塣 */
        unsigned char  reserved : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_OTP1_CTRL_1_UNION;
#endif
#define PMIC_OTP1_CTRL_1_otp1_pa_START   (0)
#define PMIC_OTP1_CTRL_1_otp1_pa_END     (1)
#define PMIC_OTP1_CTRL_1_otp1_ptm_START  (2)
#define PMIC_OTP1_CTRL_1_otp1_ptm_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_WDATA_UNION
 �ṹ˵��  : OTP1_WDATA �Ĵ����ṹ���塣��ַƫ����:0x0FC����ֵ:0x00�����:8
 �Ĵ���˵��: OTP0д�������ݼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdin : 8;  /* bit[0-7]: OTP1������ֵ�Ĵ����� */
    } reg;
} PMIC_OTP1_WDATA_UNION;
#endif
#define PMIC_OTP1_WDATA_otp1_pdin_START  (0)
#define PMIC_OTP1_WDATA_otp1_pdin_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_0_W_UNION
 �ṹ˵��  : OTP1_0_W �Ĵ����ṹ���塣��ַƫ����:0x0FD����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1������Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob0_w : 8;  /* bit[0-7]: ��OTP1_0�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP1_0_W_UNION;
#endif
#define PMIC_OTP1_0_W_otp1_pdob0_w_START  (0)
#define PMIC_OTP1_0_W_otp1_pdob0_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_1_W_UNION
 �ṹ˵��  : OTP1_1_W �Ĵ����ṹ���塣��ַƫ����:0x0FE����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1������Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob1_w : 8;  /* bit[0-7]: ��OTP1_1�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP1_1_W_UNION;
#endif
#define PMIC_OTP1_1_W_otp1_pdob1_w_START  (0)
#define PMIC_OTP1_1_W_otp1_pdob1_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_2_W_UNION
 �ṹ˵��  : OTP1_2_W �Ĵ����ṹ���塣��ַƫ����:0x0FF����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1������Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob2_w : 8;  /* bit[0-7]: ��OTP1_2�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP1_2_W_UNION;
#endif
#define PMIC_OTP1_2_W_otp1_pdob2_w_START  (0)
#define PMIC_OTP1_2_W_otp1_pdob2_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OTP1_3_W_UNION
 �ṹ˵��  : OTP1_3_W �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00�����:8
 �Ĵ���˵��: OTP1������Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob3_w : 8;  /* bit[0-7]: ��OTP1_3�����͸�ģ�⡣ */
    } reg;
} PMIC_OTP1_3_W_UNION;
#endif
#define PMIC_OTP1_3_W_otp1_pdob3_w_START  (0)
#define PMIC_OTP1_3_W_otp1_pdob3_w_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG0_UNION
 �ṹ˵��  : HRST_REG0 �Ĵ����ṹ���塣��ַƫ����:0x101����ֵ:0x00�����:8
 �Ĵ���˵��: RESETIN_N��λ��Ϣ�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hrst_reg0 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG0_UNION;
#endif
#define PMIC_HRST_REG0_hrst_reg0_START  (0)
#define PMIC_HRST_REG0_hrst_reg0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG1_UNION
 �ṹ˵��  : HRST_REG1 �Ĵ����ṹ���塣��ַƫ����:0x102����ֵ:0x00�����:8
 �Ĵ���˵��: RESETIN_N��λ��Ϣ�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hrst_reg1 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG1_UNION;
#endif
#define PMIC_HRST_REG1_hrst_reg1_START  (0)
#define PMIC_HRST_REG1_hrst_reg1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_HRST_REG2_UNION
 �ṹ˵��  : HRST_REG2 �Ĵ����ṹ���塣��ַƫ����:0x103����ֵ:0x00�����:8
 �Ĵ���˵��: RESETIN_N��λ��Ϣ�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hrst_reg2 : 8;  /* bit[0-7]: д��ֵ�����ᱻ�µ�״̬����λ���������ϴ�д��ֵ����Ϊ�ȸ�λǰ��Ϣ��¼�Ĵ����� */
    } reg;
} PMIC_HRST_REG2_UNION;
#endif
#define PMIC_HRST_REG2_hrst_reg2_START  (0)
#define PMIC_HRST_REG2_hrst_reg2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SOFT_RST_REG_UNION
 �ṹ˵��  : SOFT_RST_REG �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00�����:8
 �Ĵ���˵��: SOFT��λ��Ϣ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_rst_cfg : 8;  /* bit[0-7]: AUSTIN��ʹ�ã�����V7R5ʹ�ã�����Ϊ8'h11��rtcģ�鴦�ڸ�λ״̬�Խ��͹��ģ�д8'h22���rtcģ��ĸ�λ����
                                                       11��rtc��λ���ͣ�
                                                       22��rtc��λ���ߣ�
                                                       55���ر�����PMU��
                                                       DD�����²���һ���ϵ���̣�
                                                       EE������һ���ȸ�λ��
                                                       ������Ч��ֻ���������ڲ�debug�����������á� */
    } reg;
} PMIC_SOFT_RST_REG_UNION;
#endif
#define PMIC_SOFT_RST_REG_soft_rst_cfg_START  (0)
#define PMIC_SOFT_RST_REG_soft_rst_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_CTRL0_UNION
 �ṹ˵��  : CLK_TOP_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x105����ֵ:0x00�����:8
 �Ĵ���˵��: ʱ�ӿ��ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_reg_otp     : 2;  /* bit[0-1]: XO core�����������á�
                                                         00������1mA����������
                                                         01������2mA����������
                                                         10������3mA����������
                                                         11������4mA���������� */
        unsigned char  xo_ldo_curr    : 2;  /* bit[2-3]: XO_LDOƫ�õ�����λѡ��
                                                         00��ѡ��5uA��λ��
                                                         01��ѡ��2.5uA��λ��
                                                         10��ѡ��2.5uA��λ��
                                                         11��ѡ��1.7uA��λ�� */
        unsigned char  xo_ldo_res     : 3;  /* bit[4-6]: �ڲ�LDO�ķ������衣
                                                         000��1.8V��
                                                         001��1.5V��
                                                         010��1.6V��
                                                         011��1.7V��
                                                         100��1.9V��
                                                         101: 2.0V��
                                                         110: 2.1V��
                                                         �������������á� */
        unsigned char  xo_ldo_reg_res : 1;  /* bit[7]  : �ڲ������������ѡ��
                                                         0����ʾ�ڲ�����������OTP���ƣ�
                                                         1����ʾ�ڲ�����������Trim������ơ� */
    } reg;
} PMIC_CLK_TOP_CTRL0_UNION;
#endif
#define PMIC_CLK_TOP_CTRL0_xo_reg_otp_START      (0)
#define PMIC_CLK_TOP_CTRL0_xo_reg_otp_END        (1)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_curr_START     (2)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_curr_END       (3)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_res_START      (4)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_res_END        (6)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_reg_res_START  (7)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_reg_res_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_CTRL1_UNION
 �ṹ˵��  : CLK_TOP_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x106����ֵ:0x50�����:8
 �Ĵ���˵��: ʱ�ӿ��ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_xo_c1fix : 8;  /* bit[0-7]: ʱ��Ƶ�ʾ���trim�Ĵ���1����CLK_TOP_CTRL2[np_xo_c2fix]һ��ʹ�ã��� */
    } reg;
} PMIC_CLK_TOP_CTRL1_UNION;
#endif
#define PMIC_CLK_TOP_CTRL1_np_xo_c1fix_START  (0)
#define PMIC_CLK_TOP_CTRL1_np_xo_c1fix_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_CTRL2_UNION
 �ṹ˵��  : CLK_TOP_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x107����ֵ:0x05�����:8
 �Ĵ���˵��: ʱ�ӿ��ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_xo_c2fix      : 4;  /* bit[0-3]: ʱ��Ƶ�ʾ���trim�Ĵ���2����CLK_TOP_CTRL1[np_xo_c1fix]һ��ʹ�ã��� */
        unsigned char  xo_buff_reg_curr : 1;  /* bit[4]  : ʱ���ڲ���һ��buffer����ѡ��
                                                           0�����Ҳ�ͨ������������Ϊ������
                                                           1�����Ҳ�ͨ��ʩ���ش���������Ϊ������ */
        unsigned char  xo_otp_reg_sel1  : 1;  /* bit[5]  : XO core input buffer�ĵ�������ѡ�� 
                                                           0��OTP���ƣ�
                                                           1���Ĵ������ơ� */
        unsigned char  xo_otp_reg_sel0  : 1;  /* bit[6]  : XO core�ĵ�������ѡ��
                                                           0��OTP���� ��
                                                           1���Ĵ������ơ� */
        unsigned char  xo_c1_cap        : 1;  /* bit[7]  : �����żĴ�����ģ�����ʹ�á� */
    } reg;
} PMIC_CLK_TOP_CTRL2_UNION;
#endif
#define PMIC_CLK_TOP_CTRL2_np_xo_c2fix_START       (0)
#define PMIC_CLK_TOP_CTRL2_np_xo_c2fix_END         (3)
#define PMIC_CLK_TOP_CTRL2_xo_buff_reg_curr_START  (4)
#define PMIC_CLK_TOP_CTRL2_xo_buff_reg_curr_END    (4)
#define PMIC_CLK_TOP_CTRL2_xo_otp_reg_sel1_START   (5)
#define PMIC_CLK_TOP_CTRL2_xo_otp_reg_sel1_END     (5)
#define PMIC_CLK_TOP_CTRL2_xo_otp_reg_sel0_START   (6)
#define PMIC_CLK_TOP_CTRL2_xo_otp_reg_sel0_END     (6)
#define PMIC_CLK_TOP_CTRL2_xo_c1_cap_START         (7)
#define PMIC_CLK_TOP_CTRL2_xo_c1_cap_END           (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_CTRL3_UNION
 �ṹ˵��  : CLK_TOP_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x05�����:8
 �Ĵ���˵��: ʱ�ӿ��ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_freq_rf1  : 2;  /* bit[0-1]: RF1ʱ��buffer�����������ƣ�
                                                       00����ʾ����Ϊ3pF//100K��
                                                       01����ʾ����Ϊ10pF//100K��
                                                       10����ʾ����Ϊ16pF//100K��
                                                       11����ʾ����Ϊ25pF//100K�� */
        unsigned char  xo_freq_rf0  : 2;  /* bit[2-3]: RF0ʱ��buffer�����������ƣ�
                                                       00����ʾ����Ϊ3pF//100K��
                                                       01����ʾ����Ϊ10pF//100K��
                                                       10����ʾ����Ϊ16pF//100K��
                                                       11����ʾ����Ϊ25pF//100K�� */
        unsigned char  xo_sys_phase : 1;  /* bit[4]  : ABBʱ����RF0/RF1ʱ����λ���ơ�
                                                       0��ABBʱ����RF0/RF1ʱ�ӷ��ࣻ
                                                       1��ABBʱ����RF0/RF1ʱ��ͬ�ࡣ */
        unsigned char  xo_tri_cap   : 3;  /* bit[5-7]: ʱ����������ǲ��������ص��ڡ�
                                                       000��Ĭ��0.8pF���أ�
                                                       001����Ĭ�ϻ���������1.2pF���أ�
                                                       010����Ĭ�ϻ���������0.8pF���أ�
                                                       011����Ĭ�ϻ���������2pF���أ�
                                                       100����Ĭ�ϻ���������1.6pF���أ�
                                                       101����Ĭ�ϻ���������2.8pF���أ�
                                                       110����Ĭ�ϻ���������2.4pF���أ�
                                                       111����Ĭ�ϻ���������3.6pF���ء� */
    } reg;
} PMIC_CLK_TOP_CTRL3_UNION;
#endif
#define PMIC_CLK_TOP_CTRL3_xo_freq_rf1_START   (0)
#define PMIC_CLK_TOP_CTRL3_xo_freq_rf1_END     (1)
#define PMIC_CLK_TOP_CTRL3_xo_freq_rf0_START   (2)
#define PMIC_CLK_TOP_CTRL3_xo_freq_rf0_END     (3)
#define PMIC_CLK_TOP_CTRL3_xo_sys_phase_START  (4)
#define PMIC_CLK_TOP_CTRL3_xo_sys_phase_END    (4)
#define PMIC_CLK_TOP_CTRL3_xo_tri_cap_START    (5)
#define PMIC_CLK_TOP_CTRL3_xo_tri_cap_END      (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_CTRL4_UNION
 �ṹ˵��  : CLK_TOP_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x109����ֵ:0xD5�����:8
 �Ĵ���˵��: ʱ�ӿ��ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_freq_codec  : 2;  /* bit[0-1]: CODECʱ��buffer�����������ƣ�
                                                         00����ʾ����Ϊ7.5pF��
                                                         01����ʾ����Ϊ12.75pF��
                                                         10����ʾ����Ϊ3.75pF��
                                                         11����ʾ����Ϊ7.5pF�� */
        unsigned char  xo_freq_sys    : 2;  /* bit[2-3]: SYSʱ��buffer�����������ƣ�
                                                         00����ʾ����Ϊ7.5pF��
                                                         01����ʾ����Ϊ12.75pF��
                                                         10����ʾ����Ϊ3.75pF��
                                                         11����ʾ����Ϊ7.5pF�� */
        unsigned char  xo_freq_wifibt : 2;  /* bit[4-5]: WIFIBTʱ��buffer�����������ƣ�
                                                         00����ʾ����Ϊ3pF//100K��
                                                         01����ʾ����Ϊ10pF//100K��
                                                         10����ʾ����Ϊ16pF//100K��
                                                         11����ʾ����Ϊ25pF//100K�� */
        unsigned char  xo_freq_abb    : 2;  /* bit[6-7]: ABBʱ��buffer�����������ƣ�
                                                         00����ʾ����Ϊ3pF//100K��
                                                         01����ʾ����Ϊ10pF//100K��
                                                         10����ʾ����Ϊ16pF//100K��
                                                         11����ʾ����Ϊ25pF//100K�� */
    } reg;
} PMIC_CLK_TOP_CTRL4_UNION;
#endif
#define PMIC_CLK_TOP_CTRL4_xo_freq_codec_START   (0)
#define PMIC_CLK_TOP_CTRL4_xo_freq_codec_END     (1)
#define PMIC_CLK_TOP_CTRL4_xo_freq_sys_START     (2)
#define PMIC_CLK_TOP_CTRL4_xo_freq_sys_END       (3)
#define PMIC_CLK_TOP_CTRL4_xo_freq_wifibt_START  (4)
#define PMIC_CLK_TOP_CTRL4_xo_freq_wifibt_END    (5)
#define PMIC_CLK_TOP_CTRL4_xo_freq_abb_START     (6)
#define PMIC_CLK_TOP_CTRL4_xo_freq_abb_END       (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_CTRL5_UNION
 �ṹ˵��  : CLK_TOP_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x10A����ֵ:0x0A�����:8
 �Ĵ���˵��: ʱ�ӿ��ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_xo_codec_en : 1;  /* bit[0]  : clk_buff_codecʹ���źţ�CODEC buf����
                                                          0���رգ�
                                                          1�������� */
        unsigned char  reg_xo_sys_en   : 1;  /* bit[1]  : clk_buff_sysʹ���źţ�SYS buf����
                                                          0���رգ�
                                                          1�������� */
        unsigned char  reg_xo_wifi_en  : 1;  /* bit[2]  : clk_buff_wifibtʹ���źţ�WIFIBT buf����
                                                          0���رգ�
                                                          1�������� */
        unsigned char  reg_xo_abb_en   : 1;  /* bit[3]  : clk_buff_abbʹ���źţ�ABB buf����
                                                          0���رգ�
                                                          1�������� */
        unsigned char  xo_rf1_en       : 1;  /* bit[4]  : clk_buff_rf1ʹ���źţ�RF1 buf����
                                                          0���رգ�
                                                          1�������� */
        unsigned char  xo_rf0_en       : 1;  /* bit[5]  : clk_buff_rf0ʹ���źţ�RF0 buf����
                                                          0���رգ�
                                                          1�������� */
        unsigned char  reserved        : 2;  /* bit[6-7]: ������ */
    } reg;
} PMIC_CLK_TOP_CTRL5_UNION;
#endif
#define PMIC_CLK_TOP_CTRL5_reg_xo_codec_en_START  (0)
#define PMIC_CLK_TOP_CTRL5_reg_xo_codec_en_END    (0)
#define PMIC_CLK_TOP_CTRL5_reg_xo_sys_en_START    (1)
#define PMIC_CLK_TOP_CTRL5_reg_xo_sys_en_END      (1)
#define PMIC_CLK_TOP_CTRL5_reg_xo_wifi_en_START   (2)
#define PMIC_CLK_TOP_CTRL5_reg_xo_wifi_en_END     (2)
#define PMIC_CLK_TOP_CTRL5_reg_xo_abb_en_START    (3)
#define PMIC_CLK_TOP_CTRL5_reg_xo_abb_en_END      (3)
#define PMIC_CLK_TOP_CTRL5_xo_rf1_en_START        (4)
#define PMIC_CLK_TOP_CTRL5_xo_rf1_en_END          (4)
#define PMIC_CLK_TOP_CTRL5_xo_rf0_en_START        (5)
#define PMIC_CLK_TOP_CTRL5_xo_rf0_en_END          (5)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_CTRL6_UNION
 �ṹ˵��  : CLK_TOP_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x10B����ֵ:0x07�����:8
 �Ĵ���˵��: ʱ�ӿ��ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_eco_in_n   : 1;  /* bit[0]  : ʱ�ӽ���͹���ʹ���źš�
                                                         0�����ͣ�
                                                         1�����ߡ�
                                                         ע���Ĵ�����Ҫ���Ĵ���CORE_LDO_ECO_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  reg_xo_ldo_en  : 1;  /* bit[1]  : xo_ldo_enʹ���źš�
                                                         0�����ͣ�
                                                         1�����ߡ�
                                                         ע���Ĵ�����Ҫ���Ĵ���CORE_LDO_ECO_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  reg_xo_core_en : 1;  /* bit[2]  : xo_core_en��ʹ���źš�
                                                         0�� ���ͣ�
                                                         1�����ߡ�
                                                         ��DCXO��αTCXOģʽ�£�PDOB<26>=0����xo_core_enĬ��ֵΪ1
                                                         ��TCXOģʽ�£�PDOB<26>=1����xo_core_enĬ��Ϊ0
                                                         ע���Ĵ�����Ҫ���Ĵ���CORE_LDO_ECO_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  reg_rc_debug   : 1;  /* bit[3]  : RCʱ��debugʹ���źš�
                                                         0������ʹ�ã�
                                                         1����256Kʱ��������
                                                         ע���Ĵ�����Ҫ���Ĵ���CORE_LDO_ECO_LOCK����Ϊ8'h6C���˼Ĵ�������������Ч���������ޡ� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_CLK_TOP_CTRL6_UNION;
#endif
#define PMIC_CLK_TOP_CTRL6_reg_eco_in_n_START    (0)
#define PMIC_CLK_TOP_CTRL6_reg_eco_in_n_END      (0)
#define PMIC_CLK_TOP_CTRL6_reg_xo_ldo_en_START   (1)
#define PMIC_CLK_TOP_CTRL6_reg_xo_ldo_en_END     (1)
#define PMIC_CLK_TOP_CTRL6_reg_xo_core_en_START  (2)
#define PMIC_CLK_TOP_CTRL6_reg_xo_core_en_END    (2)
#define PMIC_CLK_TOP_CTRL6_reg_rc_debug_START    (3)
#define PMIC_CLK_TOP_CTRL6_reg_rc_debug_END      (3)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_CTRL7_UNION
 �ṹ˵��  : CLK_TOP_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x02�����:8
 �Ĵ���˵��: ʱ�ӿ��ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_xo_wifibt_dig : 1;  /* bit[0]  : clk_wifibt bufferѡ���źţ�ģ���ڲ������ź���1bit OTP(RF0/RF1/WIFI����OTP)�źŹ�ͬ�����Ƿ�����BUF��
                                                           0��ģ��BUF(���Ҳ�)��
                                                           1������BUF(����)��
                                                           (OTP=1, np_xo_rf0_dig=1�����������һbitΪ0������Ҳ�)�� */
        unsigned char  np_xo_abb_dig    : 1;  /* bit[1]  : clk_abb bufferѡ���źţ�ģ���ڲ������ź���1bit OTP(����OTP)�źŹ�ͬ�����Ƿ�����BUF��
                                                           0��ģ��BUF(���Ҳ�)��
                                                           1������BUF(����)��
                                                           (OTP=1, np_xo_rf0_dig=1�����������һbitΪ0������Ҳ�)�� */
        unsigned char  np_xo_rf1_dig    : 1;  /* bit[2]  : clk_rf1 bufferѡ���źţ�ģ���ڲ������ź���1bit OTP��(RF0/RF1/WIFI����OTP)�Ź�ͬ�����Ƿ�����BUF��
                                                           0��ģ��BUF(���Ҳ�)��
                                                           1������BUF(����)��
                                                           (OTP=1, np_xo_rf0_dig=1�����������һbitΪ0������Ҳ�)�� */
        unsigned char  np_xo_rf0_dig    : 1;  /* bit[3]  : clk_rf0 bufferѡ���źţ�ģ���ڲ������ź���1bit OTP(RF0/RF1/WIFI����OTP)�źŹ�ͬ�����Ƿ�����BUF��
                                                           0��ģ��BUF(���Ҳ�)��
                                                           1������BUF(����)��
                                                           (OTP=1, np_xo_rf0_dig=1�����������һbitΪ0������Ҳ�)�� */
        unsigned char  reserved         : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_CLK_TOP_CTRL7_UNION;
#endif
#define PMIC_CLK_TOP_CTRL7_np_xo_wifibt_dig_START  (0)
#define PMIC_CLK_TOP_CTRL7_np_xo_wifibt_dig_END    (0)
#define PMIC_CLK_TOP_CTRL7_np_xo_abb_dig_START     (1)
#define PMIC_CLK_TOP_CTRL7_np_xo_abb_dig_END       (1)
#define PMIC_CLK_TOP_CTRL7_np_xo_rf1_dig_START     (2)
#define PMIC_CLK_TOP_CTRL7_np_xo_rf1_dig_END       (2)
#define PMIC_CLK_TOP_CTRL7_np_xo_rf0_dig_START     (3)
#define PMIC_CLK_TOP_CTRL7_np_xo_rf0_dig_END       (3)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_256K_CTRL0_UNION
 �ṹ˵��  : CLK_256K_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x10D����ֵ:0x00�����:8
 �Ĵ���˵��: 256K RC���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_256k_en0 : 8;  /* bit[0-7]: RC256K�رտ��ơ�
                                                       0x5A���ر�256Kʱ�ӣ�ͬʱreg_256k_en1Ϊ0xF0����
                                                       ������������ */
    } reg;
} PMIC_CLK_256K_CTRL0_UNION;
#endif
#define PMIC_CLK_256K_CTRL0_reg_256k_en0_START  (0)
#define PMIC_CLK_256K_CTRL0_reg_256k_en0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_256K_CTRL1_UNION
 �ṹ˵��  : CLK_256K_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x10E����ֵ:0x00�����:8
 �Ĵ���˵��: 256K RC���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_256k_en1 : 8;  /* bit[0-7]: RC256K�رտ��ơ�
                                                       0xF0���ر�256Kʱ�ӣ�ͬʱreg_256k_en0Ϊ0x5A����
                                                       ������������ */
    } reg;
} PMIC_CLK_256K_CTRL1_UNION;
#endif
#define PMIC_CLK_256K_CTRL1_reg_256k_en1_START  (0)
#define PMIC_CLK_256K_CTRL1_reg_256k_en1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_RESERVE0_UNION
 �ṹ˵��  : CLK_TOP_RESERVE0 �Ĵ����ṹ���塣��ַƫ����:0x10F����ֵ:0x00�����:8
 �Ĵ���˵��: ʱ�ӿ���Ԥ���Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_reserve0 : 8;  /* bit[0-7]: xoԤ���Ĵ����� */
    } reg;
} PMIC_CLK_TOP_RESERVE0_UNION;
#endif
#define PMIC_CLK_TOP_RESERVE0_xo_reserve0_START  (0)
#define PMIC_CLK_TOP_RESERVE0_xo_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLK_TOP_RESERVE1_UNION
 �ṹ˵��  : CLK_TOP_RESERVE1 �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00�����:8
 �Ĵ���˵��: ʱ�ӿ���Ԥ���Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_reserve1 : 8;  /* bit[0-7]: xoԤ���Ĵ����� */
    } reg;
} PMIC_CLK_TOP_RESERVE1_UNION;
#endif
#define PMIC_CLK_TOP_RESERVE1_xo_reserve1_START  (0)
#define PMIC_CLK_TOP_RESERVE1_xo_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SYS_DEBUG0_UNION
 �ṹ˵��  : SYS_DEBUG0 �Ĵ����ṹ���塣��ַƫ����:0x111����ֵ:0x00�����:8
 �Ĵ���˵��: ����ϵͳdebugԤ���Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_debug0 : 8;  /* bit[0-7]: ����ϵͳdebugԤ���Ĵ����� */
    } reg;
} PMIC_SYS_DEBUG0_UNION;
#endif
#define PMIC_SYS_DEBUG0_sys_debug0_START  (0)
#define PMIC_SYS_DEBUG0_sys_debug0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SYS_DEBUG1_UNION
 �ṹ˵��  : SYS_DEBUG1 �Ĵ����ṹ���塣��ַƫ����:0x112����ֵ:0xFF�����:8
 �Ĵ���˵��: ����ϵͳdebugԤ���Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_debug1 : 8;  /* bit[0-7]: ����ϵͳdebugԤ���Ĵ����� */
    } reg;
} PMIC_SYS_DEBUG1_UNION;
#endif
#define PMIC_SYS_DEBUG1_sys_debug1_START  (0)
#define PMIC_SYS_DEBUG1_sys_debug1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DAC0_DIN_MSB_UNION
 �ṹ˵��  : DAC0_DIN_MSB �Ĵ����ṹ���塣��ַƫ����:0x113����ֵ:0x00�����:8
 �Ĵ���˵��: DAC0 din��λӳ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac0_din_msb : 2;  /* bit[0-1]: dac0 din[9��8]ӳ��Ĵ����� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_DAC0_DIN_MSB_UNION;
#endif
#define PMIC_DAC0_DIN_MSB_dac0_din_msb_START  (0)
#define PMIC_DAC0_DIN_MSB_dac0_din_msb_END    (1)


/*****************************************************************************
 �ṹ��    : PMIC_DAC0_DIN_LSB_UNION
 �ṹ˵��  : DAC0_DIN_LSB �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x00�����:8
 �Ĵ���˵��: DAC0 din��λӳ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac0_din_lsb : 8;  /* bit[0-7]: dac0 din[7:0]ӳ��Ĵ����� */
    } reg;
} PMIC_DAC0_DIN_LSB_UNION;
#endif
#define PMIC_DAC0_DIN_LSB_dac0_din_lsb_START  (0)
#define PMIC_DAC0_DIN_LSB_dac0_din_lsb_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_DAC1_DIN_MSB_UNION
 �ṹ˵��  : DAC1_DIN_MSB �Ĵ����ṹ���塣��ַƫ����:0x115����ֵ:0x00�����:8
 �Ĵ���˵��: DAC1 din��λӳ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac1_din_msb : 2;  /* bit[0-1]: dac1 din[9��8]ӳ��Ĵ����� */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_DAC1_DIN_MSB_UNION;
#endif
#define PMIC_DAC1_DIN_MSB_dac1_din_msb_START  (0)
#define PMIC_DAC1_DIN_MSB_dac1_din_msb_END    (1)


/*****************************************************************************
 �ṹ��    : PMIC_DAC1_DIN_LSB_UNION
 �ṹ˵��  : DAC1_DIN_LSB �Ĵ����ṹ���塣��ַƫ����:0x116����ֵ:0x00�����:8
 �Ĵ���˵��: DAC1 din��λӳ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac1_din_lsb : 8;  /* bit[0-7]: dac1 din[7:0]ӳ��Ĵ����� */
    } reg;
} PMIC_DAC1_DIN_LSB_UNION;
#endif
#define PMIC_DAC1_DIN_LSB_dac1_din_lsb_START  (0)
#define PMIC_DAC1_DIN_LSB_dac1_din_lsb_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CORE_LDO_ECO_LOCK_UNION
 �ṹ˵��  : CORE_LDO_ECO_LOCK �Ĵ����ṹ���塣��ַƫ����:0x117����ֵ:0x00�����:8
 �Ĵ���˵��: xo_core_en,xo_ldo_en,eco_in_n�Ĵ���д���ο��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  core_ldo_eco_lock : 8;  /* bit[0-7]: Ϊ��ֹ�����дCLK_TOP_CTRL6������ϵͳ����ֻ�е�core_ldo_eco_lockдΪ8'h6C��ʱ��CLK_TOP_CTRL6�Ĵ���������һֱд�롣 */
    } reg;
} PMIC_CORE_LDO_ECO_LOCK_UNION;
#endif
#define PMIC_CORE_LDO_ECO_LOCK_core_ldo_eco_lock_START  (0)
#define PMIC_CORE_LDO_ECO_LOCK_core_ldo_eco_lock_END    (7)




/****************************************************************************
                     (2/5) PMU_IRQ
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : PMIC_NP_OCP0_UNION
 �ṹ˵��  : NP_OCP0 �Ĵ����ṹ���塣��ַƫ����:0x11A����ֵ:0x00�����:8
 �Ĵ���˵��: BUKC0-4��LDO0-2 OCP�¼���¼�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo2   : 1;  /* bit[0]: LDO2��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpldo1   : 1;  /* bit[1]: LDO1��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpldo0_2 : 1;  /* bit[2]: LDO0_2��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpbuck4  : 1;  /* bit[3]: BUCK4��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpbuck3  : 1;  /* bit[4]: BUCK3��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpbuck2  : 1;  /* bit[5]: BUCK2��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpbuck1  : 1;  /* bit[6]: BUCK1��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
        unsigned char  np_ocpbuck0  : 1;  /* bit[7]: BUCK0��������¼���¼�Ĵ�����
                                                     0��û�з��������¼���
                                                     1�����������¼��� */
    } reg;
} PMIC_NP_OCP0_UNION;
#endif
#define PMIC_NP_OCP0_np_ocpldo2_START    (0)
#define PMIC_NP_OCP0_np_ocpldo2_END      (0)
#define PMIC_NP_OCP0_np_ocpldo1_START    (1)
#define PMIC_NP_OCP0_np_ocpldo1_END      (1)
#define PMIC_NP_OCP0_np_ocpldo0_2_START  (2)
#define PMIC_NP_OCP0_np_ocpldo0_2_END    (2)
#define PMIC_NP_OCP0_np_ocpbuck4_START   (3)
#define PMIC_NP_OCP0_np_ocpbuck4_END     (3)
#define PMIC_NP_OCP0_np_ocpbuck3_START   (4)
#define PMIC_NP_OCP0_np_ocpbuck3_END     (4)
#define PMIC_NP_OCP0_np_ocpbuck2_START   (5)
#define PMIC_NP_OCP0_np_ocpbuck2_END     (5)
#define PMIC_NP_OCP0_np_ocpbuck1_START   (6)
#define PMIC_NP_OCP0_np_ocpbuck1_END     (6)
#define PMIC_NP_OCP0_np_ocpbuck0_START   (7)
#define PMIC_NP_OCP0_np_ocpbuck0_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_OCP1_UNION
 �ṹ˵��  : NP_OCP1 �Ĵ����ṹ���塣��ַƫ����:0x11B����ֵ:0x00�����:8
 �Ĵ���˵��: LDO3-11 OCP�¼���¼�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo11 : 1;  /* bit[0]: LDO11��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo10 : 1;  /* bit[1]: LDO10��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo9  : 1;  /* bit[2]: LDO9��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo8  : 1;  /* bit[3]: LDO8��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo7  : 1;  /* bit[4]: LDO7��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo5  : 1;  /* bit[5]: LDO5��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo4  : 1;  /* bit[6]: LDO4��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo3  : 1;  /* bit[7]: LDO3��������¼���¼�Ĵ�����
                                                    0�����жϣ�
                                                    1�����жϡ� */
    } reg;
} PMIC_NP_OCP1_UNION;
#endif
#define PMIC_NP_OCP1_np_ocpldo11_START  (0)
#define PMIC_NP_OCP1_np_ocpldo11_END    (0)
#define PMIC_NP_OCP1_np_ocpldo10_START  (1)
#define PMIC_NP_OCP1_np_ocpldo10_END    (1)
#define PMIC_NP_OCP1_np_ocpldo9_START   (2)
#define PMIC_NP_OCP1_np_ocpldo9_END     (2)
#define PMIC_NP_OCP1_np_ocpldo8_START   (3)
#define PMIC_NP_OCP1_np_ocpldo8_END     (3)
#define PMIC_NP_OCP1_np_ocpldo7_START   (4)
#define PMIC_NP_OCP1_np_ocpldo7_END     (4)
#define PMIC_NP_OCP1_np_ocpldo5_START   (5)
#define PMIC_NP_OCP1_np_ocpldo5_END     (5)
#define PMIC_NP_OCP1_np_ocpldo4_START   (6)
#define PMIC_NP_OCP1_np_ocpldo4_END     (6)
#define PMIC_NP_OCP1_np_ocpldo3_START   (7)
#define PMIC_NP_OCP1_np_ocpldo3_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_OCP2_UNION
 �ṹ˵��  : NP_OCP2 �Ĵ����ṹ���塣��ַƫ����:0x11C����ֵ:0x00�����:8
 �Ĵ���˵��: LDO12-20 OCP�¼���¼�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo20 : 1;  /* bit[0]: LDO20��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo19 : 1;  /* bit[1]: LDO19��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo17 : 1;  /* bit[2]: LDO17��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo16 : 1;  /* bit[3]: LDO16��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo15 : 1;  /* bit[4]: LDO15��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo14 : 1;  /* bit[5]: LDO14��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo13 : 1;  /* bit[6]: LDO13��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo12 : 1;  /* bit[7]: LDO12��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
    } reg;
} PMIC_NP_OCP2_UNION;
#endif
#define PMIC_NP_OCP2_np_ocpldo20_START  (0)
#define PMIC_NP_OCP2_np_ocpldo20_END    (0)
#define PMIC_NP_OCP2_np_ocpldo19_START  (1)
#define PMIC_NP_OCP2_np_ocpldo19_END    (1)
#define PMIC_NP_OCP2_np_ocpldo17_START  (2)
#define PMIC_NP_OCP2_np_ocpldo17_END    (2)
#define PMIC_NP_OCP2_np_ocpldo16_START  (3)
#define PMIC_NP_OCP2_np_ocpldo16_END    (3)
#define PMIC_NP_OCP2_np_ocpldo15_START  (4)
#define PMIC_NP_OCP2_np_ocpldo15_END    (4)
#define PMIC_NP_OCP2_np_ocpldo14_START  (5)
#define PMIC_NP_OCP2_np_ocpldo14_END    (5)
#define PMIC_NP_OCP2_np_ocpldo13_START  (6)
#define PMIC_NP_OCP2_np_ocpldo13_END    (6)
#define PMIC_NP_OCP2_np_ocpldo12_START  (7)
#define PMIC_NP_OCP2_np_ocpldo12_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_OCP3_UNION
 �ṹ˵��  : NP_OCP3 �Ĵ����ṹ���塣��ַƫ����:0x11D����ֵ:0x00�����:8
 �Ĵ���˵��: LDO21-28 OCP�¼���¼�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo28 : 1;  /* bit[0]: LDO28��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo27 : 1;  /* bit[1]: LDO27��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo26 : 1;  /* bit[2]: LDO26��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo25 : 1;  /* bit[3]: LDO25��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo24 : 1;  /* bit[4]: LDO24��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo23 : 1;  /* bit[5]: LDO23��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo22 : 1;  /* bit[6]: LDO22��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
        unsigned char  np_ocpldo21 : 1;  /* bit[7]: LDO21��������¼���¼�Ĵ�����
                                                    0��û�з��������¼���
                                                    1�����������¼��� */
    } reg;
} PMIC_NP_OCP3_UNION;
#endif
#define PMIC_NP_OCP3_np_ocpldo28_START  (0)
#define PMIC_NP_OCP3_np_ocpldo28_END    (0)
#define PMIC_NP_OCP3_np_ocpldo27_START  (1)
#define PMIC_NP_OCP3_np_ocpldo27_END    (1)
#define PMIC_NP_OCP3_np_ocpldo26_START  (2)
#define PMIC_NP_OCP3_np_ocpldo26_END    (2)
#define PMIC_NP_OCP3_np_ocpldo25_START  (3)
#define PMIC_NP_OCP3_np_ocpldo25_END    (3)
#define PMIC_NP_OCP3_np_ocpldo24_START  (4)
#define PMIC_NP_OCP3_np_ocpldo24_END    (4)
#define PMIC_NP_OCP3_np_ocpldo23_START  (5)
#define PMIC_NP_OCP3_np_ocpldo23_END    (5)
#define PMIC_NP_OCP3_np_ocpldo22_START  (6)
#define PMIC_NP_OCP3_np_ocpldo22_END    (6)
#define PMIC_NP_OCP3_np_ocpldo21_START  (7)
#define PMIC_NP_OCP3_np_ocpldo21_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_OCP4_UNION
 �ṹ˵��  : NP_OCP4 �Ĵ����ṹ���塣��ַƫ����:0x11E����ֵ:0x00�����:8
 �Ĵ���˵��: LDO29-32 CLASSD OCP�¼���¼�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_classd_ocp : 1;  /* bit[0]  : classd��������¼���¼�Ĵ�����
                                                        0��û�з��������¼���
                                                        1�����������¼��� */
        unsigned char  reserved      : 3;  /* bit[1-3]: ������ */
        unsigned char  np_ocpldo32   : 1;  /* bit[4]  : LDO32��������¼���¼�Ĵ�����
                                                        0��û�з��������¼���
                                                        1�����������¼��� */
        unsigned char  np_ocpldo31   : 1;  /* bit[5]  : LDO31��������¼���¼�Ĵ�����
                                                        0��û�з��������¼���
                                                        1�����������¼��� */
        unsigned char  np_ocpldo30   : 1;  /* bit[6]  : LDO30��������¼���¼�Ĵ�����
                                                        0��û�з��������¼���
                                                        1�����������¼��� */
        unsigned char  np_ocpldo29   : 1;  /* bit[7]  : LDO29��������¼���¼�Ĵ�����
                                                        0��û�з��������¼���
                                                        1�����������¼��� */
    } reg;
} PMIC_NP_OCP4_UNION;
#endif
#define PMIC_NP_OCP4_np_classd_ocp_START  (0)
#define PMIC_NP_OCP4_np_classd_ocp_END    (0)
#define PMIC_NP_OCP4_np_ocpldo32_START    (4)
#define PMIC_NP_OCP4_np_ocpldo32_END      (4)
#define PMIC_NP_OCP4_np_ocpldo31_START    (5)
#define PMIC_NP_OCP4_np_ocpldo31_END      (5)
#define PMIC_NP_OCP4_np_ocpldo30_START    (6)
#define PMIC_NP_OCP4_np_ocpldo30_END      (6)
#define PMIC_NP_OCP4_np_ocpldo29_START    (7)
#define PMIC_NP_OCP4_np_ocpldo29_END      (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_SCP_UNION
 �ṹ˵��  : NP_SCP �Ĵ����ṹ���塣��ַƫ����:0x11F����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK0-4 SCP�¼���¼�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_buck4_scp : 1;  /* bit[0]  : BUCK4�����·�¼���¼�Ĵ�����
                                                       0��û�з��������¼���
                                                       1�����������¼��� */
        unsigned char  np_buck3_scp : 1;  /* bit[1]  : BUCK3�����·�¼���¼�Ĵ�����
                                                       0��û�з��������¼���
                                                       1�����������¼��� */
        unsigned char  np_buck2_scp : 1;  /* bit[2]  : BUCK2�����·�¼���¼�Ĵ�����
                                                       0��û�з��������¼���
                                                       1�����������¼��� */
        unsigned char  np_buck1_scp : 1;  /* bit[3]  : BUCK1�����·�¼���¼�Ĵ�����
                                                       0��û�з��������¼���
                                                       1�����������¼��� */
        unsigned char  np_buck0_scp : 1;  /* bit[4]  : BUCK0�����·�¼���¼�Ĵ�����
                                                       0��û�з��������¼���
                                                       1�����������¼��� */
        unsigned char  reserved     : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_NP_SCP_UNION;
#endif
#define PMIC_NP_SCP_np_buck4_scp_START  (0)
#define PMIC_NP_SCP_np_buck4_scp_END    (0)
#define PMIC_NP_SCP_np_buck3_scp_START  (1)
#define PMIC_NP_SCP_np_buck3_scp_END    (1)
#define PMIC_NP_SCP_np_buck2_scp_START  (2)
#define PMIC_NP_SCP_np_buck2_scp_END    (2)
#define PMIC_NP_SCP_np_buck1_scp_START  (3)
#define PMIC_NP_SCP_np_buck1_scp_END    (3)
#define PMIC_NP_SCP_np_buck0_scp_START  (4)
#define PMIC_NP_SCP_np_buck0_scp_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ0_UNION
 �ṹ˵��  : IRQ0 �Ĵ����ṹ���塣��ַƫ����:0x120����ֵ:0x00�����:8
 �Ĵ���˵��: �жϼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  por_d45mr             : 1;  /* bit[0]: por�¼��жϣ�pwr_rst_n���ߺ�Լ45ms���ϱ�����
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  vbus_det_insert_d20mr : 1;  /* bit[1]: ����������ж�(������ȥ��20ms)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  vbus_det_insert_d20mf : 1;  /* bit[2]: ������γ��ж�(�½���ȥ��20ms)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  alarmon_r             : 1;  /* bit[3]: �����жϡ�
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  pwronn_d6sf           : 1;  /* bit[4]: �������³���6s�¼��ж�(�½���ȥ��6s)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  pwronn_d1sf           : 1;  /* bit[5]: �������³���1s�¼��ж�(�½���ȥ��1s)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  pwronn_d20mr          : 1;  /* bit[6]: �����ͷ��¼��ж�(������ȥ��20ms)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  pwronn_d20mf          : 1;  /* bit[7]: ���������¼��ж�(�½���ȥ��20ms)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
    } reg;
} PMIC_IRQ0_UNION;
#endif
#define PMIC_IRQ0_por_d45mr_START              (0)
#define PMIC_IRQ0_por_d45mr_END                (0)
#define PMIC_IRQ0_vbus_det_insert_d20mr_START  (1)
#define PMIC_IRQ0_vbus_det_insert_d20mr_END    (1)
#define PMIC_IRQ0_vbus_det_insert_d20mf_START  (2)
#define PMIC_IRQ0_vbus_det_insert_d20mf_END    (2)
#define PMIC_IRQ0_alarmon_r_START              (3)
#define PMIC_IRQ0_alarmon_r_END                (3)
#define PMIC_IRQ0_pwronn_d6sf_START            (4)
#define PMIC_IRQ0_pwronn_d6sf_END              (4)
#define PMIC_IRQ0_pwronn_d1sf_START            (5)
#define PMIC_IRQ0_pwronn_d1sf_END              (5)
#define PMIC_IRQ0_pwronn_d20mr_START           (6)
#define PMIC_IRQ0_pwronn_d20mr_END             (6)
#define PMIC_IRQ0_pwronn_d20mf_START           (7)
#define PMIC_IRQ0_pwronn_d20mf_END             (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ1_UNION
 �ṹ˵��  : IRQ1 �Ĵ����ṹ���塣��ַƫ����:0x121����ֵ:0x00�����:8
 �Ĵ���˵��: �жϼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocp_r                 : 1;  /* bit[0]: OCP�¼��жϡ�
                                                              0�����жϣ�
                                                              1�����жϡ���ʾ������һ��BUCK����LDO���أ�CPU�ӵ��Ժ�Ҫȥ�鿴OCP�жϼĴ�����������һ�����ء� */
        unsigned char  coul_r                : 1;  /* bit[1]: ���ؼ��¼��жϡ�
                                                              0�����жϣ�
                                                              1�����жϡ�PMU�ӵ��Ժ�Ҫȥ�鿴����Ŀ��ؼ��жϼĴ���ȷ������һ���жϡ� */
        unsigned char  vsys_ov_d200ur        : 1;  /* bit[2]: ��ѹ�¼��ж�(������ȥ��200us)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  vsys_uv_d10mr         : 1;  /* bit[3]: Ƿѹ�澯�¼��ж�(������ȥ��10ms��ʱ�����)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  vsys_pwroff_abs_2d    : 1;  /* bit[4]: ����Ƿѹ�ػ��¼��жϣ�ͬ�����ģ���
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  vsys_pwroff_deb_d80mr : 1;  /* bit[5]: ȥ��Ƿѹ�ػ��¼��ж�(������ȥ��80ms��ʱ�����)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  thsd_otmp140_d1mr     : 1;  /* bit[6]: ����140���¼��ж�(������ȥ��1ms)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned char  thsd_otmp125_d1mr     : 1;  /* bit[7]: ���£�оƬ�¶ȳ����趨�ı����¶ȣ��¼��ж�(������ȥ��1ms)��
                                                              0�����жϣ�
                                                              1�����жϡ� */
    } reg;
} PMIC_IRQ1_UNION;
#endif
#define PMIC_IRQ1_ocp_r_START                  (0)
#define PMIC_IRQ1_ocp_r_END                    (0)
#define PMIC_IRQ1_coul_r_START                 (1)
#define PMIC_IRQ1_coul_r_END                   (1)
#define PMIC_IRQ1_vsys_ov_d200ur_START         (2)
#define PMIC_IRQ1_vsys_ov_d200ur_END           (2)
#define PMIC_IRQ1_vsys_uv_d10mr_START          (3)
#define PMIC_IRQ1_vsys_uv_d10mr_END            (3)
#define PMIC_IRQ1_vsys_pwroff_abs_2d_START     (4)
#define PMIC_IRQ1_vsys_pwroff_abs_2d_END       (4)
#define PMIC_IRQ1_vsys_pwroff_deb_d80mr_START  (5)
#define PMIC_IRQ1_vsys_pwroff_deb_d80mr_END    (5)
#define PMIC_IRQ1_thsd_otmp140_d1mr_START      (6)
#define PMIC_IRQ1_thsd_otmp140_d1mr_END        (6)
#define PMIC_IRQ1_thsd_otmp125_d1mr_START      (7)
#define PMIC_IRQ1_thsd_otmp125_d1mr_END        (7)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ2_UNION
 �ṹ˵��  : IRQ2 �Ĵ����ṹ���塣��ַƫ����:0x122����ֵ:0x00�����:8
 �Ĵ���˵��: �жϼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hresetn_d90uf : 1;  /* bit[0]  : �ȸ�λ��������RSTIN_N��λ���¼��жϡ�
                                                        0�����жϣ�
                                                        1�����жϡ� */
        unsigned char  reserved      : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_IRQ2_UNION;
#endif
#define PMIC_IRQ2_hresetn_d90uf_START  (0)
#define PMIC_IRQ2_hresetn_d90uf_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_IRQ3_UNION
 �ṹ˵��  : IRQ3 �Ĵ����ṹ���塣��ַƫ����:0x123����ֵ:0x00�����:8
 �Ĵ���˵��: �жϼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sim0_hpd_r : 1;  /* bit[0]: sim0_hpd�������жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned char  sim0_hpd_f : 1;  /* bit[1]: sim0_hpd�½����жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned char  sim0_hpd_h : 1;  /* bit[2]: sim0_hpd�ߵ�ƽ�жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned char  sim0_hpd_l : 1;  /* bit[3]: sim0_hpd�͵�ƽ�жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned char  sim1_hpd_r : 1;  /* bit[4]: sim1_hpd�������жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned char  sim1_hpd_f : 1;  /* bit[5]: sim1_hpd�½����жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned char  sim1_hpd_h : 1;  /* bit[6]: sim1_hpd�ߵ�ƽ�жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned char  sim1_hpd_l : 1;  /* bit[7]: sim1_hpd�͵�ƽ�жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
    } reg;
} PMIC_IRQ3_UNION;
#endif
#define PMIC_IRQ3_sim0_hpd_r_START  (0)
#define PMIC_IRQ3_sim0_hpd_r_END    (0)
#define PMIC_IRQ3_sim0_hpd_f_START  (1)
#define PMIC_IRQ3_sim0_hpd_f_END    (1)
#define PMIC_IRQ3_sim0_hpd_h_START  (2)
#define PMIC_IRQ3_sim0_hpd_h_END    (2)
#define PMIC_IRQ3_sim0_hpd_l_START  (3)
#define PMIC_IRQ3_sim0_hpd_l_END    (3)
#define PMIC_IRQ3_sim1_hpd_r_START  (4)
#define PMIC_IRQ3_sim1_hpd_r_END    (4)
#define PMIC_IRQ3_sim1_hpd_f_START  (5)
#define PMIC_IRQ3_sim1_hpd_f_END    (5)
#define PMIC_IRQ3_sim1_hpd_h_START  (6)
#define PMIC_IRQ3_sim1_hpd_h_END    (6)
#define PMIC_IRQ3_sim1_hpd_l_START  (7)
#define PMIC_IRQ3_sim1_hpd_l_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_IRQ0_UNION
 �ṹ˵��  : OCP_IRQ0 �Ĵ����ṹ���塣��ַƫ����:0x124����ֵ:0x00�����:8
 �Ĵ���˵��: OCP�жϼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo2   : 1;  /* bit[0]: LDO2��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpldo1   : 1;  /* bit[1]: LDO1��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpldo0_2 : 1;  /* bit[2]: LDO0_2��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpbuck4  : 1;  /* bit[3]: BUCK4��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpbuck3  : 1;  /* bit[4]: BUCK3��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpbuck2  : 1;  /* bit[5]: BUCK2��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpbuck1  : 1;  /* bit[6]: BUCK1��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
        unsigned char  ocpbuck0  : 1;  /* bit[7]: BUCK0��������жϡ�
                                                  0�����жϣ�
                                                  1�����жϡ� */
    } reg;
} PMIC_OCP_IRQ0_UNION;
#endif
#define PMIC_OCP_IRQ0_ocpldo2_START    (0)
#define PMIC_OCP_IRQ0_ocpldo2_END      (0)
#define PMIC_OCP_IRQ0_ocpldo1_START    (1)
#define PMIC_OCP_IRQ0_ocpldo1_END      (1)
#define PMIC_OCP_IRQ0_ocpldo0_2_START  (2)
#define PMIC_OCP_IRQ0_ocpldo0_2_END    (2)
#define PMIC_OCP_IRQ0_ocpbuck4_START   (3)
#define PMIC_OCP_IRQ0_ocpbuck4_END     (3)
#define PMIC_OCP_IRQ0_ocpbuck3_START   (4)
#define PMIC_OCP_IRQ0_ocpbuck3_END     (4)
#define PMIC_OCP_IRQ0_ocpbuck2_START   (5)
#define PMIC_OCP_IRQ0_ocpbuck2_END     (5)
#define PMIC_OCP_IRQ0_ocpbuck1_START   (6)
#define PMIC_OCP_IRQ0_ocpbuck1_END     (6)
#define PMIC_OCP_IRQ0_ocpbuck0_START   (7)
#define PMIC_OCP_IRQ0_ocpbuck0_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_IRQ1_UNION
 �ṹ˵��  : OCP_IRQ1 �Ĵ����ṹ���塣��ַƫ����:0x125����ֵ:0x00�����:8
 �Ĵ���˵��: OCP�жϼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo11 : 1;  /* bit[0]: LDO11��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo10 : 1;  /* bit[1]: LDO10��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo9  : 1;  /* bit[2]: LDO9��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo8  : 1;  /* bit[3]: LDO8��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo7  : 1;  /* bit[4]: LDO7��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo5  : 1;  /* bit[5]: LDO5��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo4  : 1;  /* bit[6]: LDO4��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo3  : 1;  /* bit[7]: LDO3��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
    } reg;
} PMIC_OCP_IRQ1_UNION;
#endif
#define PMIC_OCP_IRQ1_ocpldo11_START  (0)
#define PMIC_OCP_IRQ1_ocpldo11_END    (0)
#define PMIC_OCP_IRQ1_ocpldo10_START  (1)
#define PMIC_OCP_IRQ1_ocpldo10_END    (1)
#define PMIC_OCP_IRQ1_ocpldo9_START   (2)
#define PMIC_OCP_IRQ1_ocpldo9_END     (2)
#define PMIC_OCP_IRQ1_ocpldo8_START   (3)
#define PMIC_OCP_IRQ1_ocpldo8_END     (3)
#define PMIC_OCP_IRQ1_ocpldo7_START   (4)
#define PMIC_OCP_IRQ1_ocpldo7_END     (4)
#define PMIC_OCP_IRQ1_ocpldo5_START   (5)
#define PMIC_OCP_IRQ1_ocpldo5_END     (5)
#define PMIC_OCP_IRQ1_ocpldo4_START   (6)
#define PMIC_OCP_IRQ1_ocpldo4_END     (6)
#define PMIC_OCP_IRQ1_ocpldo3_START   (7)
#define PMIC_OCP_IRQ1_ocpldo3_END     (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_IRQ2_UNION
 �ṹ˵��  : OCP_IRQ2 �Ĵ����ṹ���塣��ַƫ����:0x126����ֵ:0x00�����:8
 �Ĵ���˵��: OCP�жϼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo20 : 1;  /* bit[0]: LDO20��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo19 : 1;  /* bit[1]: LDO19��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo17 : 1;  /* bit[2]: LDO17��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo16 : 1;  /* bit[3]: LDO16��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo15 : 1;  /* bit[4]: LDO15��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo14 : 1;  /* bit[5]: LDO14��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo13 : 1;  /* bit[6]: LDO13��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo12 : 1;  /* bit[7]: LDO12��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
    } reg;
} PMIC_OCP_IRQ2_UNION;
#endif
#define PMIC_OCP_IRQ2_ocpldo20_START  (0)
#define PMIC_OCP_IRQ2_ocpldo20_END    (0)
#define PMIC_OCP_IRQ2_ocpldo19_START  (1)
#define PMIC_OCP_IRQ2_ocpldo19_END    (1)
#define PMIC_OCP_IRQ2_ocpldo17_START  (2)
#define PMIC_OCP_IRQ2_ocpldo17_END    (2)
#define PMIC_OCP_IRQ2_ocpldo16_START  (3)
#define PMIC_OCP_IRQ2_ocpldo16_END    (3)
#define PMIC_OCP_IRQ2_ocpldo15_START  (4)
#define PMIC_OCP_IRQ2_ocpldo15_END    (4)
#define PMIC_OCP_IRQ2_ocpldo14_START  (5)
#define PMIC_OCP_IRQ2_ocpldo14_END    (5)
#define PMIC_OCP_IRQ2_ocpldo13_START  (6)
#define PMIC_OCP_IRQ2_ocpldo13_END    (6)
#define PMIC_OCP_IRQ2_ocpldo12_START  (7)
#define PMIC_OCP_IRQ2_ocpldo12_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_IRQ3_UNION
 �ṹ˵��  : OCP_IRQ3 �Ĵ����ṹ���塣��ַƫ����:0x127����ֵ:0x00�����:8
 �Ĵ���˵��: OCP�жϼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo28 : 1;  /* bit[0]: LDO28��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo27 : 1;  /* bit[1]: LDO27��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo26 : 1;  /* bit[2]: LDO26��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo25 : 1;  /* bit[3]: LDO25��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo24 : 1;  /* bit[4]: LDO24��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo23 : 1;  /* bit[5]: LDO23��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo22 : 1;  /* bit[6]: LDO22��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
        unsigned char  ocpldo21 : 1;  /* bit[7]: LDO21��������жϡ�
                                                 0�����жϣ�
                                                 1�����жϡ� */
    } reg;
} PMIC_OCP_IRQ3_UNION;
#endif
#define PMIC_OCP_IRQ3_ocpldo28_START  (0)
#define PMIC_OCP_IRQ3_ocpldo28_END    (0)
#define PMIC_OCP_IRQ3_ocpldo27_START  (1)
#define PMIC_OCP_IRQ3_ocpldo27_END    (1)
#define PMIC_OCP_IRQ3_ocpldo26_START  (2)
#define PMIC_OCP_IRQ3_ocpldo26_END    (2)
#define PMIC_OCP_IRQ3_ocpldo25_START  (3)
#define PMIC_OCP_IRQ3_ocpldo25_END    (3)
#define PMIC_OCP_IRQ3_ocpldo24_START  (4)
#define PMIC_OCP_IRQ3_ocpldo24_END    (4)
#define PMIC_OCP_IRQ3_ocpldo23_START  (5)
#define PMIC_OCP_IRQ3_ocpldo23_END    (5)
#define PMIC_OCP_IRQ3_ocpldo22_START  (6)
#define PMIC_OCP_IRQ3_ocpldo22_END    (6)
#define PMIC_OCP_IRQ3_ocpldo21_START  (7)
#define PMIC_OCP_IRQ3_ocpldo21_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_IRQ4_UNION
 �ṹ˵��  : OCP_IRQ4 �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x00�����:8
 �Ĵ���˵��: OCP�жϼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_ocp : 1;  /* bit[0]  : classd��������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  reserved   : 3;  /* bit[1-3]: ������ */
        unsigned char  ocpldo32   : 1;  /* bit[4]  : LDO32��������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  ocpldo31   : 1;  /* bit[5]  : LDO31��������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  ocpldo30   : 1;  /* bit[6]  : LDO30��������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned char  ocpldo29   : 1;  /* bit[7]  : LDO29��������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
    } reg;
} PMIC_OCP_IRQ4_UNION;
#endif
#define PMIC_OCP_IRQ4_classd_ocp_START  (0)
#define PMIC_OCP_IRQ4_classd_ocp_END    (0)
#define PMIC_OCP_IRQ4_ocpldo32_START    (4)
#define PMIC_OCP_IRQ4_ocpldo32_END      (4)
#define PMIC_OCP_IRQ4_ocpldo31_START    (5)
#define PMIC_OCP_IRQ4_ocpldo31_END      (5)
#define PMIC_OCP_IRQ4_ocpldo30_START    (6)
#define PMIC_OCP_IRQ4_ocpldo30_END      (6)
#define PMIC_OCP_IRQ4_ocpldo29_START    (7)
#define PMIC_OCP_IRQ4_ocpldo29_END      (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCP_IRQ5_UNION
 �ṹ˵��  : OCP_IRQ5 �Ĵ����ṹ���塣��ַƫ����:0x129����ֵ:0x00�����:8
 �Ĵ���˵��: OCP�жϼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_scp : 1;  /* bit[0]  : BUCK4�����·�жϡ�
                                                    0�����жϣ�
                                                    1�����жϡ� */
        unsigned char  buck3_scp : 1;  /* bit[1]  : BUCK3�����·�жϡ�
                                                    0�����жϣ�
                                                    1�����жϡ� */
        unsigned char  buck2_scp : 1;  /* bit[2]  : BUCK2�����·�жϡ�
                                                    0�����жϣ�
                                                    1�����жϡ� */
        unsigned char  buck1_scp : 1;  /* bit[3]  : BUCK1�����·�жϡ�
                                                    0�����жϣ�
                                                    1�����жϡ� */
        unsigned char  buck0_scp : 1;  /* bit[4]  : BUCK0�����·�жϡ�
                                                    0�����жϣ�
                                                    1�����жϡ� */
        unsigned char  reserved  : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_OCP_IRQ5_UNION;
#endif
#define PMIC_OCP_IRQ5_buck4_scp_START  (0)
#define PMIC_OCP_IRQ5_buck4_scp_END    (0)
#define PMIC_OCP_IRQ5_buck3_scp_START  (1)
#define PMIC_OCP_IRQ5_buck3_scp_END    (1)
#define PMIC_OCP_IRQ5_buck2_scp_START  (2)
#define PMIC_OCP_IRQ5_buck2_scp_END    (2)
#define PMIC_OCP_IRQ5_buck1_scp_START  (3)
#define PMIC_OCP_IRQ5_buck1_scp_END    (3)
#define PMIC_OCP_IRQ5_buck0_scp_START  (4)
#define PMIC_OCP_IRQ5_buck0_scp_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_NP_RECORD0_UNION
 �ṹ˵��  : NP_RECORD0 �Ĵ����ṹ���塣��ַƫ����:0x12A����ֵ:0x00�����:8
 �Ĵ���˵��: �¼���¼�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_pwronn_restart   : 1;  /* bit[0]: ����״̬�°�������8s����������
                                                            0��û�з��������¼���
                                                            1�����������¼��� */
        unsigned char  np_pwrhold_shutdown : 1;  /* bit[1]: pwr_hold���ʹ����ػ���
                                                            0��û�з��������¼���
                                                            1�����������¼���  */
        unsigned char  np_pwronn_shutdown  : 1;  /* bit[2]: ����״̬�°�������8s�����ػ���
                                                            0��û�з��������¼���
                                                            1�����������¼��� */
        unsigned char  np_pwrhold_pwrup    : 1;  /* bit[3]: pwr_hold����������
                                                            0��û�з��������¼���
                                                            1�����������¼���  */
        unsigned char  np_alarmon_pwrup    : 1;  /* bit[4]: �ػ�״̬�����Ӵ�������(����״̬�µ�alarm_on����¼)��
                                                            0��û�з��������¼���
                                                            1�����������¼���  */
        unsigned char  np_vbus_pwrup       : 1;  /* bit[5]: �ػ�״̬�³��������200ms���������� 
                                                            0��û�з��������¼���
                                                            1�����������¼���  */
        unsigned char  np_pwronn_pwrup     : 1;  /* bit[6]: �ػ�״̬�°�������500ms����������
                                                            0��û�з��������¼���
                                                            1�����������¼��� */
        unsigned char  np_fast_pwrup       : 1;  /* bit[7]: ���߿��ٿ�����
                                                            0��û�з��������¼���
                                                            1�����������¼��� */
    } reg;
} PMIC_NP_RECORD0_UNION;
#endif
#define PMIC_NP_RECORD0_np_pwronn_restart_START    (0)
#define PMIC_NP_RECORD0_np_pwronn_restart_END      (0)
#define PMIC_NP_RECORD0_np_pwrhold_shutdown_START  (1)
#define PMIC_NP_RECORD0_np_pwrhold_shutdown_END    (1)
#define PMIC_NP_RECORD0_np_pwronn_shutdown_START   (2)
#define PMIC_NP_RECORD0_np_pwronn_shutdown_END     (2)
#define PMIC_NP_RECORD0_np_pwrhold_pwrup_START     (3)
#define PMIC_NP_RECORD0_np_pwrhold_pwrup_END       (3)
#define PMIC_NP_RECORD0_np_alarmon_pwrup_START     (4)
#define PMIC_NP_RECORD0_np_alarmon_pwrup_END       (4)
#define PMIC_NP_RECORD0_np_vbus_pwrup_START        (5)
#define PMIC_NP_RECORD0_np_vbus_pwrup_END          (5)
#define PMIC_NP_RECORD0_np_pwronn_pwrup_START      (6)
#define PMIC_NP_RECORD0_np_pwronn_pwrup_END        (6)
#define PMIC_NP_RECORD0_np_fast_pwrup_START        (7)
#define PMIC_NP_RECORD0_np_fast_pwrup_END          (7)


/*****************************************************************************
 �ṹ��    : PMIC_NP_RECORD1_UNION
 �ṹ˵��  : NP_RECORD1 �Ĵ����ṹ���塣��ַƫ����:0x12B����ֵ:0x08�����:8
 �Ĵ���˵��: �¼���¼�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_tcxo_clk_sel_r : 1;  /* bit[0]: 32k RC�л���32K Crystal OSC ʱ�ӡ�
                                                          0��û�з��������¼���
                                                          1�����������¼���  */
        unsigned char  np_dcxo_clk_sel_r : 1;  /* bit[1]: 32K RC �л��� 19.2MHz/586 ʱ�ӡ�
                                                          0��û�з��������¼���
                                                          1�����������¼���  */
        unsigned char  np_dcxo_clk_sel_f : 1;  /* bit[2]: 19.2MHz/586 �л��� 32K RCʱ�ӡ�
                                                          0��û�з��������¼���
                                                          1�����������¼���  */
        unsigned char  np_vsys_vcoin_sel : 1;  /* bit[3]: VSYS��VCION�л��źš�
                                                          0��û�з��������¼���
                                                          1�����������¼��� */
        unsigned char  np_smpl           : 1;  /* bit[4]: SMPL������¼
                                                          0��û�з���SMPL��
                                                          1������SMPL�� */
        unsigned char  np_core_io_vld_f  : 1;  /* bit[5]: core_io_vld�쳣�µ��¼���¼��VDD_IO�Ƿ����ͣ���
                                                          0��û�з��������¼���
                                                          1���з��������¼��� */
        unsigned char  reserved          : 1;  /* bit[6]: ����Ԥ���۲��źš� */
        unsigned char  np_pwrhold_1s     : 1;  /* bit[7]: SYS_RST_N���ߺ�1sʱ�̣�VBUS����λ������pwr_holdΪ�ʹ����ػ���
                                                          0��û�з��������¼���
                                                          1�����������¼���  */
    } reg;
} PMIC_NP_RECORD1_UNION;
#endif
#define PMIC_NP_RECORD1_np_tcxo_clk_sel_r_START  (0)
#define PMIC_NP_RECORD1_np_tcxo_clk_sel_r_END    (0)
#define PMIC_NP_RECORD1_np_dcxo_clk_sel_r_START  (1)
#define PMIC_NP_RECORD1_np_dcxo_clk_sel_r_END    (1)
#define PMIC_NP_RECORD1_np_dcxo_clk_sel_f_START  (2)
#define PMIC_NP_RECORD1_np_dcxo_clk_sel_f_END    (2)
#define PMIC_NP_RECORD1_np_vsys_vcoin_sel_START  (3)
#define PMIC_NP_RECORD1_np_vsys_vcoin_sel_END    (3)
#define PMIC_NP_RECORD1_np_smpl_START            (4)
#define PMIC_NP_RECORD1_np_smpl_END              (4)
#define PMIC_NP_RECORD1_np_core_io_vld_f_START   (5)
#define PMIC_NP_RECORD1_np_core_io_vld_f_END     (5)
#define PMIC_NP_RECORD1_np_pwrhold_1s_START      (7)
#define PMIC_NP_RECORD1_np_pwrhold_1s_END        (7)




/****************************************************************************
                     (3/5) PMU_RTC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : PMIC_RTCDR0_UNION
 �ṹ˵��  : RTCDR0 �Ĵ����ṹ���塣��ַƫ����:0x12C����ֵ:0x00�����:8
 �Ĵ���˵��: RTC��ǰʱ��Ĵ���bit[7:0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcdr0 : 8;  /* bit[0-7]: 32 bits,RTC Data Register,�����ص�ǰRTCֵ�� */
    } reg;
} PMIC_RTCDR0_UNION;
#endif
#define PMIC_RTCDR0_rtcdr0_START  (0)
#define PMIC_RTCDR0_rtcdr0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCDR1_UNION
 �ṹ˵��  : RTCDR1 �Ĵ����ṹ���塣��ַƫ����:0x12D����ֵ:0x00�����:8
 �Ĵ���˵��: RTC��ǰʱ��Ĵ���bit[15:8]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcdr1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCDR1_UNION;
#endif
#define PMIC_RTCDR1_rtcdr1_START  (0)
#define PMIC_RTCDR1_rtcdr1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCDR2_UNION
 �ṹ˵��  : RTCDR2 �Ĵ����ṹ���塣��ַƫ����:0x12E����ֵ:0x00�����:8
 �Ĵ���˵��: RTC��ǰʱ��Ĵ���bit[23:16]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcdr2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCDR2_UNION;
#endif
#define PMIC_RTCDR2_rtcdr2_START  (0)
#define PMIC_RTCDR2_rtcdr2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCDR3_UNION
 �ṹ˵��  : RTCDR3 �Ĵ����ṹ���塣��ַƫ����:0x12F����ֵ:0x00�����:8
 �Ĵ���˵��: RTC��ǰʱ��Ĵ���bit[31:24]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcdr3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCDR3_UNION;
#endif
#define PMIC_RTCDR3_rtcdr3_START  (0)
#define PMIC_RTCDR3_rtcdr3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCMR0_UNION
 �ṹ˵��  : RTCMR0 �Ĵ����ṹ���塣��ַƫ����:0x130����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ȽϼĴ���bit[7:0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcmr0 : 8;  /* bit[0-7]: 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ��������˳��Ҫ�������õ�λ������������λ����û��Ҫ��˳��д�����һ��Ĵ�����Ҫ�ȴ�3��32K cycle�����ٴβ����˼Ĵ����� */
    } reg;
} PMIC_RTCMR0_UNION;
#endif
#define PMIC_RTCMR0_rtcmr0_START  (0)
#define PMIC_RTCMR0_rtcmr0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCMR1_UNION
 �ṹ˵��  : RTCMR1 �Ĵ����ṹ���塣��ַƫ����:0x131����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ȽϼĴ���bit[15:8]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcmr1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCMR1_UNION;
#endif
#define PMIC_RTCMR1_rtcmr1_START  (0)
#define PMIC_RTCMR1_rtcmr1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCMR2_UNION
 �ṹ˵��  : RTCMR2 �Ĵ����ṹ���塣��ַƫ����:0x132����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ȽϼĴ���bit[23:16]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcmr2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCMR2_UNION;
#endif
#define PMIC_RTCMR2_rtcmr2_START  (0)
#define PMIC_RTCMR2_rtcmr2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCMR3_UNION
 �ṹ˵��  : RTCMR3 �Ĵ����ṹ���塣��ַƫ����:0x133����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ȽϼĴ���bit[31:24]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcmr3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCMR3_UNION;
#endif
#define PMIC_RTCMR3_rtcmr3_START  (0)
#define PMIC_RTCMR3_rtcmr3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCLR0_UNION
 �ṹ˵��  : RTCLR0 �Ĵ����ṹ���塣��ַƫ����:0x134����ֵ:0x00�����:8
 �Ĵ���˵��: RTC���ؼĴ���bit[7:0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcclr0 : 8;  /* bit[0-7]: 32 bits RTC load register ���ؼĴ��������õ�ǰʱ�䣩�������������趨ֵ��������˳��Ҫ�������õ�λ������������λ����û��Ҫ��˳��д�����һ��Ĵ�����Ҫ�ȴ�3��32K cycle�����ٴβ����˼Ĵ����� */
    } reg;
} PMIC_RTCLR0_UNION;
#endif
#define PMIC_RTCLR0_rtcclr0_START  (0)
#define PMIC_RTCLR0_rtcclr0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCLR1_UNION
 �ṹ˵��  : RTCLR1 �Ĵ����ṹ���塣��ַƫ����:0x135����ֵ:0x00�����:8
 �Ĵ���˵��: RTC���ؼĴ���bit[15:8]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcclr1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCLR1_UNION;
#endif
#define PMIC_RTCLR1_rtcclr1_START  (0)
#define PMIC_RTCLR1_rtcclr1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCLR2_UNION
 �ṹ˵��  : RTCLR2 �Ĵ����ṹ���塣��ַƫ����:0x136����ֵ:0x00�����:8
 �Ĵ���˵��: RTC���ؼĴ���bit[23:16]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcclr2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCLR2_UNION;
#endif
#define PMIC_RTCLR2_rtcclr2_START  (0)
#define PMIC_RTCLR2_rtcclr2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCLR3_UNION
 �ṹ˵��  : RTCLR3 �Ĵ����ṹ���塣��ַƫ����:0x137����ֵ:0x00�����:8
 �Ĵ���˵��: RTC���ؼĴ���bit[31:24]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcclr3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCLR3_UNION;
#endif
#define PMIC_RTCLR3_rtcclr3_START  (0)
#define PMIC_RTCLR3_rtcclr3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTCCTRL_UNION
 �ṹ˵��  : RTCCTRL �Ĵ����ṹ���塣��ַƫ����:0x138����ֵ:0x03�����:8
 �Ĵ���˵��: RTC���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtccr           : 1;  /* bit[0]  : ��RTC����λ��
                                                          0����RTC��ǰֵ������ֵȫ��Ϊ0��
                                                          1����RTC��ǰֵ������ֵΪʵ�ʵ�ǰֵ��
                                                          ���˼Ĵ���д���Ҫ�ȴ�3��32K cycle�����ٴβ����˼Ĵ����� */
        unsigned char  ref_res_sel_int : 1;  /* bit[1]  : ��׼VREF�ܽ��˲�����ѡ�� �� */
        unsigned char  reserved        : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_RTCCTRL_UNION;
#endif
#define PMIC_RTCCTRL_rtccr_START            (0)
#define PMIC_RTCCTRL_rtccr_END              (0)
#define PMIC_RTCCTRL_ref_res_sel_int_START  (1)
#define PMIC_RTCCTRL_ref_res_sel_int_END    (1)


/*****************************************************************************
 �ṹ��    : PMIC_XO_THRESOLD0_UNION
 �ṹ˵��  : XO_THRESOLD0 �Ĵ����ṹ���塣��ַƫ����:0x139����ֵ:0xB8�����:8
 �Ĵ���˵��: XO_THRESOLD[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold_low : 8;  /* bit[0-7]: У׼ƫ����ֵ���üĴ�����
                                                               ���˼Ĵ�������ͨ��ӳ��Ĵ���D2A_RES0��D2A_RES1������ */
    } reg;
} PMIC_XO_THRESOLD0_UNION;
#endif
#define PMIC_XO_THRESOLD0_xo_cali_thresold_low_START  (0)
#define PMIC_XO_THRESOLD0_xo_cali_thresold_low_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_XO_THRESOLD1_UNION
 �ṹ˵��  : XO_THRESOLD1 �Ĵ����ṹ���塣��ַƫ����:0x13A����ֵ:0x00�����:8
 �Ĵ���˵��: XO_THRESOLD[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold1_high : 8;  /* bit[0-7]: У׼ƫ����ֵ���üĴ�����
                                                                 ���˼Ĵ�������ͨ��ӳ��Ĵ���D2A_RES2������ */
    } reg;
} PMIC_XO_THRESOLD1_UNION;
#endif
#define PMIC_XO_THRESOLD1_xo_cali_thresold1_high_START  (0)
#define PMIC_XO_THRESOLD1_xo_cali_thresold1_high_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CRC_VAULE0_UNION
 �ṹ˵��  : CRC_VAULE0 �Ĵ����ṹ���塣��ַƫ����:0x13B����ֵ:0x00�����:8
 �Ĵ���˵��: CRC_VALUE[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_value0 : 8;  /* bit[0-7]: DCXOģʽ�£���RTCʱ��У׼״̬�µõ���RCʱ��У׼ֵ[7:0]�� */
    } reg;
} PMIC_CRC_VAULE0_UNION;
#endif
#define PMIC_CRC_VAULE0_crc_value0_START  (0)
#define PMIC_CRC_VAULE0_crc_value0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CRC_VAULE1_UNION
 �ṹ˵��  : CRC_VAULE1 �Ĵ����ṹ���塣��ַƫ����:0x13C����ֵ:0x27�����:8
 �Ĵ���˵��: CRC_VALUE[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_value1 : 8;  /* bit[0-7]: DCXOģʽ�£���RTCʱ��У׼״̬�µõ���RCʱ��У׼ֵ[15:8]�� */
    } reg;
} PMIC_CRC_VAULE1_UNION;
#endif
#define PMIC_CRC_VAULE1_crc_value1_START  (0)
#define PMIC_CRC_VAULE1_crc_value1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CRC_VAULE2_UNION
 �ṹ˵��  : CRC_VAULE2 �Ĵ����ṹ���塣��ַƫ����:0x13D����ֵ:0x09�����:8
 �Ĵ���˵��: CRC_VALUE[20:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_value2 : 5;  /* bit[0-4]: DCXOģʽ�£���RTCʱ��У׼״̬�µõ���RCʱ��У׼ֵ[20:16]�� */
        unsigned char  reserved   : 3;  /* bit[5-7]: ������ */
    } reg;
} PMIC_CRC_VAULE2_UNION;
#endif
#define PMIC_CRC_VAULE2_crc_value2_START  (0)
#define PMIC_CRC_VAULE2_crc_value2_END    (4)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRUP_TIMER0_UNION
 �ṹ˵��  : RTC_PWRUP_TIMER0 �Ĵ����ṹ���塣��ַƫ����:0x13E����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ϵ�����[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrup_timer0 : 8;  /* bit[0-7]: PMU�ϵ�ʱ��RTC��������ֵ[7:0]�� */
    } reg;
} PMIC_RTC_PWRUP_TIMER0_UNION;
#endif
#define PMIC_RTC_PWRUP_TIMER0_rtc_pwrup_timer0_START  (0)
#define PMIC_RTC_PWRUP_TIMER0_rtc_pwrup_timer0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRUP_TIMER1_UNION
 �ṹ˵��  : RTC_PWRUP_TIMER1 �Ĵ����ṹ���塣��ַƫ����:0x13F����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ϵ�����[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrup_timer1 : 8;  /* bit[0-7]: PMU�ϵ�ʱ��RTC��������ֵ[15:8]�� */
    } reg;
} PMIC_RTC_PWRUP_TIMER1_UNION;
#endif
#define PMIC_RTC_PWRUP_TIMER1_rtc_pwrup_timer1_START  (0)
#define PMIC_RTC_PWRUP_TIMER1_rtc_pwrup_timer1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRUP_TIMER2_UNION
 �ṹ˵��  : RTC_PWRUP_TIMER2 �Ĵ����ṹ���塣��ַƫ����:0x140����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ϵ�����[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrup_timer2 : 8;  /* bit[0-7]: PMU�ϵ�ʱ��RTC��������ֵ[23:16]�� */
    } reg;
} PMIC_RTC_PWRUP_TIMER2_UNION;
#endif
#define PMIC_RTC_PWRUP_TIMER2_rtc_pwrup_timer2_START  (0)
#define PMIC_RTC_PWRUP_TIMER2_rtc_pwrup_timer2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRUP_TIMER3_UNION
 �ṹ˵��  : RTC_PWRUP_TIMER3 �Ĵ����ṹ���塣��ַƫ����:0x141����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�ϵ�����[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrup_timer3 : 8;  /* bit[0-7]: PMU�ϵ�ʱ��RTC��������ֵ[31:24]�� */
    } reg;
} PMIC_RTC_PWRUP_TIMER3_UNION;
#endif
#define PMIC_RTC_PWRUP_TIMER3_rtc_pwrup_timer3_START  (0)
#define PMIC_RTC_PWRUP_TIMER3_rtc_pwrup_timer3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRDOWN_TIMER0_UNION
 �ṹ˵��  : RTC_PWRDOWN_TIMER0 �Ĵ����ṹ���塣��ַƫ����:0x142����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�µ�����[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrdown_timer0 : 8;  /* bit[0-7]: PMU�µ�ʱ��RTC��������ֵ[7:0]�� */
    } reg;
} PMIC_RTC_PWRDOWN_TIMER0_UNION;
#endif
#define PMIC_RTC_PWRDOWN_TIMER0_rtc_pwrdown_timer0_START  (0)
#define PMIC_RTC_PWRDOWN_TIMER0_rtc_pwrdown_timer0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRDOWN_TIMER1_UNION
 �ṹ˵��  : RTC_PWRDOWN_TIMER1 �Ĵ����ṹ���塣��ַƫ����:0x143����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�µ�����[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrdown_timer1 : 8;  /* bit[0-7]: PMU�µ�ʱ��RTC��������ֵ[15:8]�� */
    } reg;
} PMIC_RTC_PWRDOWN_TIMER1_UNION;
#endif
#define PMIC_RTC_PWRDOWN_TIMER1_rtc_pwrdown_timer1_START  (0)
#define PMIC_RTC_PWRDOWN_TIMER1_rtc_pwrdown_timer1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRDOWN_TIMER2_UNION
 �ṹ˵��  : RTC_PWRDOWN_TIMER2 �Ĵ����ṹ���塣��ַƫ����:0x144����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�µ�����[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrdown_timer2 : 8;  /* bit[0-7]: PMU�µ�ʱ��RTC��������ֵ[23:16]�� */
    } reg;
} PMIC_RTC_PWRDOWN_TIMER2_UNION;
#endif
#define PMIC_RTC_PWRDOWN_TIMER2_rtc_pwrdown_timer2_START  (0)
#define PMIC_RTC_PWRDOWN_TIMER2_rtc_pwrdown_timer2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_RTC_PWRDOWN_TIMER3_UNION
 �ṹ˵��  : RTC_PWRDOWN_TIMER3 �Ĵ����ṹ���塣��ַƫ����:0x145����ֵ:0x00�����:8
 �Ĵ���˵��: RTC�µ�����[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrdown_timer3 : 8;  /* bit[0-7]: PMU�µ�ʱ��RTC��������ֵ[31:24]�� */
    } reg;
} PMIC_RTC_PWRDOWN_TIMER3_UNION;
#endif
#define PMIC_RTC_PWRDOWN_TIMER3_rtc_pwrdown_timer3_START  (0)
#define PMIC_RTC_PWRDOWN_TIMER3_rtc_pwrdown_timer3_END    (7)




/****************************************************************************
                     (4/5) PMU_COUL
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : PMIC_COUL_IRQ_UNION
 �ṹ˵��  : COUL_IRQ �Ĵ����ṹ���塣��ַƫ����:0x14B����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼ��жϼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int_i   : 1;  /* bit[0]  : cl_out>cl_intʱ�ϱ��жϡ�
                                                     0���޴��жϣ�
                                                     1���ϱ��жϡ� */
        unsigned char  cl_out_i   : 1;  /* bit[1]  : cl_out������81%�ϱ��жϡ�
                                                     0���޴��жϣ�
                                                     1���ϱ��жϡ� */
        unsigned char  cl_in_i    : 1;  /* bit[2]  : cl_in������81%�ϱ��жϡ�
                                                     0���޴��жϣ�
                                                     1���ϱ��жϡ� */
        unsigned char  vbat_int_i : 1;  /* bit[3]  : vbat��ѹ<�趨��vbat_intֵ��
                                                     0���޴��жϣ�
                                                     1���ϱ��жϡ� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_COUL_IRQ_UNION;
#endif
#define PMIC_COUL_IRQ_cl_int_i_START    (0)
#define PMIC_COUL_IRQ_cl_int_i_END      (0)
#define PMIC_COUL_IRQ_cl_out_i_START    (1)
#define PMIC_COUL_IRQ_cl_out_i_END      (1)
#define PMIC_COUL_IRQ_cl_in_i_START     (2)
#define PMIC_COUL_IRQ_cl_in_i_END       (2)
#define PMIC_COUL_IRQ_vbat_int_i_START  (3)
#define PMIC_COUL_IRQ_vbat_int_i_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_COUL_IRQ_MASK_UNION
 �ṹ˵��  : COUL_IRQ_MASK �Ĵ����ṹ���塣��ַƫ����:0x14C����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼ��ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int_i_mk   : 1;  /* bit[0]  : cl_int_i�ж�����λ��
                                                        0�������Σ�
                                                        1��cl_int_i�ж����Ρ� */
        unsigned char  cl_out_i_mk   : 1;  /* bit[1]  : cl_out_i�ж�����λ��
                                                        0�������Σ�
                                                        1��cl_out_i�ж����Ρ� */
        unsigned char  cl_in_i_mk    : 1;  /* bit[2]  : cl_in_i�ж�����λ��
                                                        0�������Σ�
                                                        1��cl_in_i�ж����Ρ� */
        unsigned char  vbat_int_i_mk : 1;  /* bit[3]  : vbat_int_i�ж�����λ��
                                                        0�������Σ�
                                                        1��vbat_int_i�ж����Ρ� */
        unsigned char  reserved      : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_COUL_IRQ_MASK_UNION;
#endif
#define PMIC_COUL_IRQ_MASK_cl_int_i_mk_START    (0)
#define PMIC_COUL_IRQ_MASK_cl_int_i_mk_END      (0)
#define PMIC_COUL_IRQ_MASK_cl_out_i_mk_START    (1)
#define PMIC_COUL_IRQ_MASK_cl_out_i_mk_END      (1)
#define PMIC_COUL_IRQ_MASK_cl_in_i_mk_START     (2)
#define PMIC_COUL_IRQ_MASK_cl_in_i_mk_END       (2)
#define PMIC_COUL_IRQ_MASK_vbat_int_i_mk_START  (3)
#define PMIC_COUL_IRQ_MASK_vbat_int_i_mk_END    (3)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT_0_UNION
 �ṹ˵��  : CURRENT_0 �Ĵ����ṹ���塣��ַƫ����:0x14D����ֵ:0x00�����:8
 �Ĵ���˵��: ��ǰ����[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_0 : 8;  /* bit[0-7]: ��ǰ����ֵ����ֵ�Ǿ���У׼���ֵ��
                                                    ��������������Ĵ����洢�����ݣ������ȡʱ�����ȶ���8bit������������λ��ȡ������ȡ���8bit�����ζ�ȡ֮��û��ʱ��Լ�����������ж���8bit�ļĴ����Ķ�д��ʽ��Ҫ���մ˲������� */
    } reg;
} PMIC_CURRENT_0_UNION;
#endif
#define PMIC_CURRENT_0_current_0_START  (0)
#define PMIC_CURRENT_0_current_0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT_1_UNION
 �ṹ˵��  : CURRENT_1 �Ĵ����ṹ���塣��ַƫ����:0x14E����ֵ:0x00�����:8
 �Ĵ���˵��: ��ǰ����[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT_1_UNION;
#endif
#define PMIC_CURRENT_1_current_1_START  (0)
#define PMIC_CURRENT_1_current_1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT_0_UNION
 �ṹ˵��  : V_OUT_0 �Ĵ����ṹ���塣��ַƫ����:0x14F����ֵ:0xFF�����:8
 �Ĵ���˵��: ��ǰ��ѹ[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_0 : 8;  /* bit[0-7]: ��ǰ��ѹֵ����ֵ�Ǿ���У׼���ֵ�� */
    } reg;
} PMIC_V_OUT_0_UNION;
#endif
#define PMIC_V_OUT_0_v_out_0_START  (0)
#define PMIC_V_OUT_0_v_out_0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT_1_UNION
 �ṹ˵��  : V_OUT_1 �Ĵ����ṹ���塣��ַƫ����:0x150����ֵ:0xFF�����:8
 �Ĵ���˵��: ��ǰ��ѹ[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT_1_UNION;
#endif
#define PMIC_V_OUT_1_v_out_1_START  (0)
#define PMIC_V_OUT_1_v_out_1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_CTRL_REG_UNION
 �ṹ˵��  : CLJ_CTRL_REG �Ĵ����ṹ���塣��ַƫ����:0x151����ֵ:0x80�����:8
 �Ĵ���˵��: ���ؼƿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_ctrl            : 3;  /* bit[0-2]: bit[2]���Ƿ�ǿ�ƽ���ECOģʽ���ơ�
                                                              0����ǿ�ƽ���ECOģʽ��
                                                              1��ǿ�ƽ���ECOģʽ��
                                                              
                                                              bit[1]�����ؼ��Ƿ����PMU����ECOģʽ���ơ�
                                                              0�����ؼƲ�����PMU����ECOģʽ��
                                                              1�����ؼƸ���PMU����ECOģʽ��
                                                              ��������bit[2] == 0 ʱ��Ч����Ҫ�����PMU��ͬʱ��Ҫ��0x0DD�Ĵ������㣩
                                                              
                                                              bit[0]������ECOģʽʱ��ʹ���ź��Ƿ�ȥ�����ơ�
                                                              0������ECOģʽʹ���źŲ�ȥ����
                                                              1������ECOģʽʹ���ź�ȥ����
                                                              ��������bit[1] ==1 ʱ��Ч��
                                                              ע��eco_ctrl�üĴ����ȸ�λ�����㡣 */
        unsigned char  reflash_value_ctrl  : 1;  /* bit[3]  : ���ؼƸ������ݷ�ʽѡ��
                                                              0������״̬���������ݣ�
                                                              1����ECOģʽ�������ݡ� */
        unsigned char  eco_filter_time     : 2;  /* bit[4-5]: ���ؼ��˳�ECOģʽʹ���ź�ȥ��ʱ��ѡ��
                                                              00��100ms��
                                                              01��200ms��
                                                              10��300ms��
                                                              11��400ms��
                                                              ��������en_eco_modeȥ��ʱ����Ĭ��Ϊ00�� */
        unsigned char  calibration_ctrl    : 1;  /* bit[6]  : ���ؼ�ǿ��У׼����λ��
                                                              0����У׼��
                                                              1��ǿ�ƽ���У׼״̬�� */
        unsigned char  coul_ctrl_onoff_reg : 1;  /* bit[7]  : ���ؼƿ��ؿ��ƼĴ�����
                                                              0�����ؼƹرգ�
                                                              1�����ؼƿ�����
                                                              ����������д֮ǰ���ټ��3��32kHzϵͳʱ�����ڣ� */
    } reg;
} PMIC_CLJ_CTRL_REG_UNION;
#endif
#define PMIC_CLJ_CTRL_REG_eco_ctrl_START             (0)
#define PMIC_CLJ_CTRL_REG_eco_ctrl_END               (2)
#define PMIC_CLJ_CTRL_REG_reflash_value_ctrl_START   (3)
#define PMIC_CLJ_CTRL_REG_reflash_value_ctrl_END     (3)
#define PMIC_CLJ_CTRL_REG_eco_filter_time_START      (4)
#define PMIC_CLJ_CTRL_REG_eco_filter_time_END        (5)
#define PMIC_CLJ_CTRL_REG_calibration_ctrl_START     (6)
#define PMIC_CLJ_CTRL_REG_calibration_ctrl_END       (6)
#define PMIC_CLJ_CTRL_REG_coul_ctrl_onoff_reg_START  (7)
#define PMIC_CLJ_CTRL_REG_coul_ctrl_onoff_reg_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_REFALSH_TIME_UNION
 �ṹ˵��  : ECO_REFALSH_TIME �Ĵ����ṹ���塣��ַƫ����:0x152����ֵ:0x01�����:8
 �Ĵ���˵��: ECO_REFLASH����ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_reflash_time : 8;  /* bit[0-7]: �˹���ʱ����һ����λ����110ms��ΪECO_REFLASHʱ�䣻��Ч����ֵΪ1~255������ֵ����255ʱ��Ӳ��ֱ�ӱ��͵�255��Ĭ��Ϊ1������������д֮ǰ���ټ��3��32kHzϵͳʱ�����ڣ� */
    } reg;
} PMIC_ECO_REFALSH_TIME_UNION;
#endif
#define PMIC_ECO_REFALSH_TIME_eco_reflash_time_START  (0)
#define PMIC_ECO_REFALSH_TIME_eco_reflash_time_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_OUT0_UNION
 �ṹ˵��  : CL_OUT0 �Ĵ����ṹ���塣��ַƫ����:0x153����ֵ:0x00�����:8
 �Ĵ���˵��: cl_out[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out0 : 8;  /* bit[0-7]: ��������������[31:0]��
                                                  ���ӵ�8bit����������λд�룬���д�����8bit��һ������д������������һ�����ݵ�8bitд�����������������8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_CL_OUT0_UNION;
#endif
#define PMIC_CL_OUT0_cl_out0_START  (0)
#define PMIC_CL_OUT0_cl_out0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_OUT1_UNION
 �ṹ˵��  : CL_OUT1 �Ĵ����ṹ���塣��ַƫ����:0x154����ֵ:0x00�����:8
 �Ĵ���˵��: cl_out[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_OUT1_UNION;
#endif
#define PMIC_CL_OUT1_cl_out1_START  (0)
#define PMIC_CL_OUT1_cl_out1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_OUT2_UNION
 �ṹ˵��  : CL_OUT2 �Ĵ����ṹ���塣��ַƫ����:0x155����ֵ:0x00�����:8
 �Ĵ���˵��: cl_out[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_OUT2_UNION;
#endif
#define PMIC_CL_OUT2_cl_out2_START  (0)
#define PMIC_CL_OUT2_cl_out2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_OUT3_UNION
 �ṹ˵��  : CL_OUT3 �Ĵ����ṹ���塣��ַƫ����:0x156����ֵ:0x00�����:8
 �Ĵ���˵��: cl_out[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_OUT3_UNION;
#endif
#define PMIC_CL_OUT3_cl_out3_START  (0)
#define PMIC_CL_OUT3_cl_out3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_IN0_UNION
 �ṹ˵��  : CL_IN0 �Ĵ����ṹ���塣��ַƫ����:0x157����ֵ:0x00�����:8
 �Ĵ���˵��: cl_in[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in0 : 8;  /* bit[0-7]: �������������[31:0]��
                                                 ���ӵ�8bit����������λд�룬���д�����8bit��һ������д������������һ�����ݵ�8bitд�����������������8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_CL_IN0_UNION;
#endif
#define PMIC_CL_IN0_cl_in0_START  (0)
#define PMIC_CL_IN0_cl_in0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_IN1_UNION
 �ṹ˵��  : CL_IN1 �Ĵ����ṹ���塣��ַƫ����:0x158����ֵ:0x00�����:8
 �Ĵ���˵��: cl_in[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_IN1_UNION;
#endif
#define PMIC_CL_IN1_cl_in1_START  (0)
#define PMIC_CL_IN1_cl_in1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_IN2_UNION
 �ṹ˵��  : CL_IN2 �Ĵ����ṹ���塣��ַƫ����:0x159����ֵ:0x00�����:8
 �Ĵ���˵��: cl_in[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_IN2_UNION;
#endif
#define PMIC_CL_IN2_cl_in2_START  (0)
#define PMIC_CL_IN2_cl_in2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_IN3_UNION
 �ṹ˵��  : CL_IN3 �Ĵ����ṹ���塣��ַƫ����:0x15A����ֵ:0x00�����:8
 �Ĵ���˵��: cl_in[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_IN3_UNION;
#endif
#define PMIC_CL_IN3_cl_in3_START  (0)
#define PMIC_CL_IN3_cl_in3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CHG_TIMER0_UNION
 �ṹ˵��  : CHG_TIMER0 �Ĵ����ṹ���塣��ַƫ����:0x15B����ֵ:0x00�����:8
 �Ĵ���˵��: chg_timer[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer0 : 8;  /* bit[0-7]: ���ʱ�������[31:0]��
                                                     ���ӵ�8bit����������λд�룬���д�����8bit��һ������д������������һ�����ݵ�8bitд�����������������8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_CHG_TIMER0_UNION;
#endif
#define PMIC_CHG_TIMER0_chg_timer0_START  (0)
#define PMIC_CHG_TIMER0_chg_timer0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CHG_TIMER1_UNION
 �ṹ˵��  : CHG_TIMER1 �Ĵ����ṹ���塣��ַƫ����:0x15C����ֵ:0x00�����:8
 �Ĵ���˵��: chg_timer[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CHG_TIMER1_UNION;
#endif
#define PMIC_CHG_TIMER1_chg_timer1_START  (0)
#define PMIC_CHG_TIMER1_chg_timer1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CHG_TIMER2_UNION
 �ṹ˵��  : CHG_TIMER2 �Ĵ����ṹ���塣��ַƫ����:0x15D����ֵ:0x00�����:8
 �Ĵ���˵��: chg_timer[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CHG_TIMER2_UNION;
#endif
#define PMIC_CHG_TIMER2_chg_timer2_START  (0)
#define PMIC_CHG_TIMER2_chg_timer2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CHG_TIMER3_UNION
 �ṹ˵��  : CHG_TIMER3 �Ĵ����ṹ���塣��ַƫ����:0x15E����ֵ:0x00�����:8
 �Ĵ���˵��: chg_timer[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CHG_TIMER3_UNION;
#endif
#define PMIC_CHG_TIMER3_chg_timer3_START  (0)
#define PMIC_CHG_TIMER3_chg_timer3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LOAD_TIMER0_UNION
 �ṹ˵��  : LOAD_TIMER0 �Ĵ����ṹ���塣��ַƫ����:0x15F����ֵ:0x00�����:8
 �Ĵ���˵��: load_timer[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer0 : 8;  /* bit[0-7]: �ŵ�ʱ�������[31:0]��
                                                      ���ӵ�8bit����������λд�룬���д�����8bit��һ������д������������һ�����ݵ�8bitд�����������������8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_LOAD_TIMER0_UNION;
#endif
#define PMIC_LOAD_TIMER0_load_timer0_START  (0)
#define PMIC_LOAD_TIMER0_load_timer0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LOAD_TIMER1_UNION
 �ṹ˵��  : LOAD_TIMER1 �Ĵ����ṹ���塣��ַƫ����:0x160����ֵ:0x00�����:8
 �Ĵ���˵��: load_timer[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_LOAD_TIMER1_UNION;
#endif
#define PMIC_LOAD_TIMER1_load_timer1_START  (0)
#define PMIC_LOAD_TIMER1_load_timer1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LOAD_TIMER2_UNION
 �ṹ˵��  : LOAD_TIMER2 �Ĵ����ṹ���塣��ַƫ����:0x161����ֵ:0x00�����:8
 �Ĵ���˵��: load_timer[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_LOAD_TIMER2_UNION;
#endif
#define PMIC_LOAD_TIMER2_load_timer2_START  (0)
#define PMIC_LOAD_TIMER2_load_timer2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_LOAD_TIMER3_UNION
 �ṹ˵��  : LOAD_TIMER3 �Ĵ����ṹ���塣��ַƫ����:0x162����ֵ:0x00�����:8
 �Ĵ���˵��: load_timer[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_LOAD_TIMER3_UNION;
#endif
#define PMIC_LOAD_TIMER3_load_timer3_START  (0)
#define PMIC_LOAD_TIMER3_load_timer3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_INT0_UNION
 �ṹ˵��  : CL_INT0 �Ĵ����ṹ���塣��ַƫ����:0x163����ֵ:0x00�����:8
 �Ĵ���˵��: cl_int[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int0 : 8;  /* bit[0-7]: ���������жϱȽϼĴ���[31:0]��
                                                  ��cl_inout>cl_intʱ�ϱ��жϡ�
                                                  ���ӵ�8bit����������λд�룬���д�����8bit��һ������д������������һ�����ݵ�8bitд�����������������8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_CL_INT0_UNION;
#endif
#define PMIC_CL_INT0_cl_int0_START  (0)
#define PMIC_CL_INT0_cl_int0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_INT1_UNION
 �ṹ˵��  : CL_INT1 �Ĵ����ṹ���塣��ַƫ����:0x164����ֵ:0x00�����:8
 �Ĵ���˵��: cl_int[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_INT1_UNION;
#endif
#define PMIC_CL_INT1_cl_int1_START  (0)
#define PMIC_CL_INT1_cl_int1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_INT2_UNION
 �ṹ˵��  : CL_INT2 �Ĵ����ṹ���塣��ַƫ����:0x165����ֵ:0x00�����:8
 �Ĵ���˵��: cl_int[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_INT2_UNION;
#endif
#define PMIC_CL_INT2_cl_int2_START  (0)
#define PMIC_CL_INT2_cl_int2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CL_INT3_UNION
 �ṹ˵��  : CL_INT3 �Ĵ����ṹ���塣��ַƫ����:0x166����ֵ:0x80�����:8
 �Ĵ���˵��: cl_int[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_INT3_UNION;
#endif
#define PMIC_CL_INT3_cl_int3_START  (0)
#define PMIC_CL_INT3_cl_int3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_INT0_UNION
 �ṹ˵��  : V_INT0 �Ĵ����ṹ���塣��ַƫ����:0x167����ֵ:0x00�����:8
 �Ĵ���˵��: v_int[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_int0 : 8;  /* bit[0-7]: ��ѹ�жϱȽ�ֵ�Ĵ���[15:0]��
                                                 ����д��8bit����д��8bit��һ������д������������һ�����ݵ�8bitд�������������ݸ�8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_V_INT0_UNION;
#endif
#define PMIC_V_INT0_v_int0_START  (0)
#define PMIC_V_INT0_v_int0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_INT1_UNION
 �ṹ˵��  : V_INT1 �Ĵ����ṹ���塣��ַƫ����:0x168����ֵ:0x00�����:8
 �Ĵ���˵��: v_int[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_int1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_INT1_UNION;
#endif
#define PMIC_V_INT1_v_int1_START  (0)
#define PMIC_V_INT1_v_int1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_CURRENT0_UNION
 �ṹ˵��  : OFFSET_CURRENT0 �Ĵ����ṹ���塣��ַƫ����:0x169����ֵ:0x00�����:8
 �Ĵ���˵��: offset_current[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current0 : 8;  /* bit[0-7]: ����У׼ֵ[15:0]�� */
    } reg;
} PMIC_OFFSET_CURRENT0_UNION;
#endif
#define PMIC_OFFSET_CURRENT0_offset_current0_START  (0)
#define PMIC_OFFSET_CURRENT0_offset_current0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_CURRENT1_UNION
 �ṹ˵��  : OFFSET_CURRENT1 �Ĵ����ṹ���塣��ַƫ����:0x16A����ֵ:0x00�����:8
 �Ĵ���˵��: offset_current[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_CURRENT1_UNION;
#endif
#define PMIC_OFFSET_CURRENT1_offset_current1_START  (0)
#define PMIC_OFFSET_CURRENT1_offset_current1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_VOLTAGE0_UNION
 �ṹ˵��  : OFFSET_VOLTAGE0 �Ĵ����ṹ���塣��ַƫ����:0x16B����ֵ:0x00�����:8
 �Ĵ���˵��: offset_voltage[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage0 : 8;  /* bit[0-7]: ��ѹУ׼ֵ[15:0]�� */
    } reg;
} PMIC_OFFSET_VOLTAGE0_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE0_offset_voltage0_START  (0)
#define PMIC_OFFSET_VOLTAGE0_offset_voltage0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_VOLTAGE1_UNION
 �ṹ˵��  : OFFSET_VOLTAGE1 �Ĵ����ṹ���塣��ַƫ����:0x16C����ֵ:0x00�����:8
 �Ĵ���˵��: offset_voltage[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_VOLTAGE1_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE1_offset_voltage1_START  (0)
#define PMIC_OFFSET_VOLTAGE1_offset_voltage1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCV_VOLTAGE0_UNION
 �ṹ˵��  : OCV_VOLTAGE0 �Ĵ����ṹ���塣��ַƫ����:0x16D����ֵ:0x00�����:8
 �Ĵ���˵��: v_ocv_data[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_ocv_data0 : 8;  /* bit[0-7]: ����ʱOCV��ѹ����ֵ[15:0]����ֵ��ԭʼֵ��δ����У׼�� */
    } reg;
} PMIC_OCV_VOLTAGE0_UNION;
#endif
#define PMIC_OCV_VOLTAGE0_v_ocv_data0_START  (0)
#define PMIC_OCV_VOLTAGE0_v_ocv_data0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCV_VOLTAGE1_UNION
 �ṹ˵��  : OCV_VOLTAGE1 �Ĵ����ṹ���塣��ַƫ����:0x16E����ֵ:0x00�����:8
 �Ĵ���˵��: v_ocv_data[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_ocv_data1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OCV_VOLTAGE1_UNION;
#endif
#define PMIC_OCV_VOLTAGE1_v_ocv_data1_START  (0)
#define PMIC_OCV_VOLTAGE1_v_ocv_data1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCV_CURRENT0_UNION
 �ṹ˵��  : OCV_CURRENT0 �Ĵ����ṹ���塣��ַƫ����:0x16F����ֵ:0x00�����:8
 �Ĵ���˵��: i_ocv_data[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_ocv_data0 : 8;  /* bit[0-7]: ����ʱOCV��������ֵ[15:0]����ֵ��ԭʼֵ��δ����У׼�� */
    } reg;
} PMIC_OCV_CURRENT0_UNION;
#endif
#define PMIC_OCV_CURRENT0_i_ocv_data0_START  (0)
#define PMIC_OCV_CURRENT0_i_ocv_data0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OCV_CURRENT1_UNION
 �ṹ˵��  : OCV_CURRENT1 �Ĵ����ṹ���塣��ַƫ����:0x170����ֵ:0x00�����:8
 �Ĵ���˵��: i_ocv_data[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_ocv_data1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OCV_CURRENT1_UNION;
#endif
#define PMIC_OCV_CURRENT1_i_ocv_data1_START  (0)
#define PMIC_OCV_CURRENT1_i_ocv_data1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLIN_0_UNION
 �ṹ˵��  : ECO_OUT_CLIN_0 �Ĵ����ṹ���塣��ַƫ����:0x171����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clin[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin0 : 8;  /* bit[0-7]: �˳�ECOģʽ�������������[13:0]��ÿ���˳�ECOģʽ�Զ���¼��ǰ�������������ʱ�̱��֡� */
    } reg;
} PMIC_ECO_OUT_CLIN_0_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_0_eco_out_clin0_START  (0)
#define PMIC_ECO_OUT_CLIN_0_eco_out_clin0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLIN_1_UNION
 �ṹ˵��  : ECO_OUT_CLIN_1 �Ĵ����ṹ���塣��ַƫ����:0x172����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clin[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLIN_1_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_1_eco_out_clin1_START  (0)
#define PMIC_ECO_OUT_CLIN_1_eco_out_clin1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLIN_2_UNION
 �ṹ˵��  : ECO_OUT_CLIN_2 �Ĵ����ṹ���塣��ַƫ����:0x173����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clin[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLIN_2_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_2_eco_out_clin2_START  (0)
#define PMIC_ECO_OUT_CLIN_2_eco_out_clin2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLIN_3_UNION
 �ṹ˵��  : ECO_OUT_CLIN_3 �Ĵ����ṹ���塣��ַƫ����:0x174����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clin[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLIN_3_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_3_eco_out_clin3_START  (0)
#define PMIC_ECO_OUT_CLIN_3_eco_out_clin3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLOUT_0_UNION
 �ṹ˵��  : ECO_OUT_CLOUT_0 �Ĵ����ṹ���塣��ַƫ����:0x175����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clout[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout0 : 8;  /* bit[0-7]: �˳�ECOģʽ��������������[31:0]��ÿ���˳�ECOģʽ�Զ���¼��ǰ��������������ʱ�̱��֡� */
    } reg;
} PMIC_ECO_OUT_CLOUT_0_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_0_eco_out_clout0_START  (0)
#define PMIC_ECO_OUT_CLOUT_0_eco_out_clout0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLOUT_1_UNION
 �ṹ˵��  : ECO_OUT_CLOUT_1 �Ĵ����ṹ���塣��ַƫ����:0x176����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clout[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLOUT_1_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_1_eco_out_clout1_START  (0)
#define PMIC_ECO_OUT_CLOUT_1_eco_out_clout1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLOUT_2_UNION
 �ṹ˵��  : ECO_OUT_CLOUT_2 �Ĵ����ṹ���塣��ַƫ����:0x177����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clout[23:16]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLOUT_2_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_2_eco_out_clout2_START  (0)
#define PMIC_ECO_OUT_CLOUT_2_eco_out_clout2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ECO_OUT_CLOUT_3_UNION
 �ṹ˵��  : ECO_OUT_CLOUT_3 �Ĵ����ṹ���塣��ַƫ����:0x178����ֵ:0x00�����:8
 �Ĵ���˵��: eco_out_clout[31:24]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLOUT_3_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_3_eco_out_clout3_START  (0)
#define PMIC_ECO_OUT_CLOUT_3_eco_out_clout3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE0_UNION
 �ṹ˵��  : V_OUT0_PRE0 �Ĵ����ṹ���塣��ַƫ����:0x179����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre0[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre0 : 8;  /* bit[0-7]: ��ǰ��ص�ѹָʾ[15:0]�����λ�������λ�� */
    } reg;
} PMIC_V_OUT0_PRE0_UNION;
#endif
#define PMIC_V_OUT0_PRE0_v_out0_pre0_START  (0)
#define PMIC_V_OUT0_PRE0_v_out0_pre0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE0_UNION
 �ṹ˵��  : V_OUT1_PRE0 �Ĵ����ṹ���塣��ַƫ����:0x17A����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre0[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre0 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE0_UNION;
#endif
#define PMIC_V_OUT1_PRE0_v_out1_pre0_START  (0)
#define PMIC_V_OUT1_PRE0_v_out1_pre0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE1_UNION
 �ṹ˵��  : V_OUT0_PRE1 �Ĵ����ṹ���塣��ַƫ����:0x17B����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre1[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre1 : 8;  /* bit[0-7]: ��ǰ��ѹǰһ��ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE1_UNION;
#endif
#define PMIC_V_OUT0_PRE1_v_out0_pre1_START  (0)
#define PMIC_V_OUT0_PRE1_v_out0_pre1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE1_UNION
 �ṹ˵��  : V_OUT1_PRE1 �Ĵ����ṹ���塣��ַƫ����:0x17C����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre1[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE1_UNION;
#endif
#define PMIC_V_OUT1_PRE1_v_out1_pre1_START  (0)
#define PMIC_V_OUT1_PRE1_v_out1_pre1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE2_UNION
 �ṹ˵��  : V_OUT0_PRE2 �Ĵ����ṹ���塣��ַƫ����:0x17D����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre2[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre2 : 8;  /* bit[0-7]: ��ǰ��ѹǰ����ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE2_UNION;
#endif
#define PMIC_V_OUT0_PRE2_v_out0_pre2_START  (0)
#define PMIC_V_OUT0_PRE2_v_out0_pre2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE2_UNION
 �ṹ˵��  : V_OUT1_PRE2 �Ĵ����ṹ���塣��ַƫ����:0x17E����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre2[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE2_UNION;
#endif
#define PMIC_V_OUT1_PRE2_v_out1_pre2_START  (0)
#define PMIC_V_OUT1_PRE2_v_out1_pre2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE3_UNION
 �ṹ˵��  : V_OUT0_PRE3 �Ĵ����ṹ���塣��ַƫ����:0x17F����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre3[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre3 : 8;  /* bit[0-7]: ��ǰ��ѹǰ����ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE3_UNION;
#endif
#define PMIC_V_OUT0_PRE3_v_out0_pre3_START  (0)
#define PMIC_V_OUT0_PRE3_v_out0_pre3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE3_UNION
 �ṹ˵��  : V_OUT1_PRE3 �Ĵ����ṹ���塣��ַƫ����:0x180����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre3[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE3_UNION;
#endif
#define PMIC_V_OUT1_PRE3_v_out1_pre3_START  (0)
#define PMIC_V_OUT1_PRE3_v_out1_pre3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE4_UNION
 �ṹ˵��  : V_OUT0_PRE4 �Ĵ����ṹ���塣��ַƫ����:0x181����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre4[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre4 : 8;  /* bit[0-7]: ��ǰ��ѹǰ�Ĵ�ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE4_UNION;
#endif
#define PMIC_V_OUT0_PRE4_v_out0_pre4_START  (0)
#define PMIC_V_OUT0_PRE4_v_out0_pre4_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE4_UNION
 �ṹ˵��  : V_OUT1_PRE4 �Ĵ����ṹ���塣��ַƫ����:0x182����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre4[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre4 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE4_UNION;
#endif
#define PMIC_V_OUT1_PRE4_v_out1_pre4_START  (0)
#define PMIC_V_OUT1_PRE4_v_out1_pre4_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE5_UNION
 �ṹ˵��  : V_OUT0_PRE5 �Ĵ����ṹ���塣��ַƫ����:0x183����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre5[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre5 : 8;  /* bit[0-7]: ��ǰ��ѹǰ���ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE5_UNION;
#endif
#define PMIC_V_OUT0_PRE5_v_out0_pre5_START  (0)
#define PMIC_V_OUT0_PRE5_v_out0_pre5_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE5_UNION
 �ṹ˵��  : V_OUT1_PRE5 �Ĵ����ṹ���塣��ַƫ����:0x184����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre5[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre5 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE5_UNION;
#endif
#define PMIC_V_OUT1_PRE5_v_out1_pre5_START  (0)
#define PMIC_V_OUT1_PRE5_v_out1_pre5_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE6_UNION
 �ṹ˵��  : V_OUT0_PRE6 �Ĵ����ṹ���塣��ַƫ����:0x185����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre6[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre6 : 8;  /* bit[0-7]: ��ǰ��ѹǰ����ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE6_UNION;
#endif
#define PMIC_V_OUT0_PRE6_v_out0_pre6_START  (0)
#define PMIC_V_OUT0_PRE6_v_out0_pre6_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE6_UNION
 �ṹ˵��  : V_OUT1_PRE6 �Ĵ����ṹ���塣��ַƫ����:0x186����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre6[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre6 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE6_UNION;
#endif
#define PMIC_V_OUT1_PRE6_v_out1_pre6_START  (0)
#define PMIC_V_OUT1_PRE6_v_out1_pre6_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE7_UNION
 �ṹ˵��  : V_OUT0_PRE7 �Ĵ����ṹ���塣��ַƫ����:0x187����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre7[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre7 : 8;  /* bit[0-7]: ��ǰ��ѹǰ�ߴ�ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE7_UNION;
#endif
#define PMIC_V_OUT0_PRE7_v_out0_pre7_START  (0)
#define PMIC_V_OUT0_PRE7_v_out0_pre7_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE7_UNION
 �ṹ˵��  : V_OUT1_PRE7 �Ĵ����ṹ���塣��ַƫ����:0x188����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre7[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre7 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE7_UNION;
#endif
#define PMIC_V_OUT1_PRE7_v_out1_pre7_START  (0)
#define PMIC_V_OUT1_PRE7_v_out1_pre7_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE8_UNION
 �ṹ˵��  : V_OUT0_PRE8 �Ĵ����ṹ���塣��ַƫ����:0x189����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre8[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre8 : 8;  /* bit[0-7]: ��ǰ��ѹǰ�˴�ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE8_UNION;
#endif
#define PMIC_V_OUT0_PRE8_v_out0_pre8_START  (0)
#define PMIC_V_OUT0_PRE8_v_out0_pre8_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE8_UNION
 �ṹ˵��  : V_OUT1_PRE8 �Ĵ����ṹ���塣��ַƫ����:0x18A����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre8[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre8 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE8_UNION;
#endif
#define PMIC_V_OUT1_PRE8_v_out1_pre8_START  (0)
#define PMIC_V_OUT1_PRE8_v_out1_pre8_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT0_PRE9_UNION
 �ṹ˵��  : V_OUT0_PRE9 �Ĵ����ṹ���塣��ַƫ����:0x18B����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre9[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre9 : 8;  /* bit[0-7]: ��ǰ��ѹǰ�Ŵ�ֵ[15:0]�� */
    } reg;
} PMIC_V_OUT0_PRE9_UNION;
#endif
#define PMIC_V_OUT0_PRE9_v_out0_pre9_START  (0)
#define PMIC_V_OUT0_PRE9_v_out0_pre9_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_V_OUT1_PRE9_UNION
 �ṹ˵��  : V_OUT1_PRE9 �Ĵ����ṹ���塣��ַƫ����:0x18C����ֵ:0xFF�����:8
 �Ĵ���˵��: v_out_pre9[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre9 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE9_UNION;
#endif
#define PMIC_V_OUT1_PRE9_v_out1_pre9_START  (0)
#define PMIC_V_OUT1_PRE9_v_out1_pre9_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE0_UNION
 �ṹ˵��  : CURRENT0_PRE0 �Ĵ����ṹ���塣��ַƫ����:0x18D����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre0[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre0 : 8;  /* bit[0-7]: ��ǰ����ָʾ[15:0]�����λ�������λ�� */
    } reg;
} PMIC_CURRENT0_PRE0_UNION;
#endif
#define PMIC_CURRENT0_PRE0_current0_pre0_START  (0)
#define PMIC_CURRENT0_PRE0_current0_pre0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE0_UNION
 �ṹ˵��  : CURRENT1_PRE0 �Ĵ����ṹ���塣��ַƫ����:0x18E����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre0[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre0 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE0_UNION;
#endif
#define PMIC_CURRENT1_PRE0_current1_pre0_START  (0)
#define PMIC_CURRENT1_PRE0_current1_pre0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE1_UNION
 �ṹ˵��  : CURRENT0_PRE1 �Ĵ����ṹ���塣��ַƫ����:0x18F����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre1[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre1 : 8;  /* bit[0-7]: ��ǰ����ǰһ��ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE1_UNION;
#endif
#define PMIC_CURRENT0_PRE1_current0_pre1_START  (0)
#define PMIC_CURRENT0_PRE1_current0_pre1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE1_UNION
 �ṹ˵��  : CURRENT1_PRE1 �Ĵ����ṹ���塣��ַƫ����:0x190����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre1[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE1_UNION;
#endif
#define PMIC_CURRENT1_PRE1_current1_pre1_START  (0)
#define PMIC_CURRENT1_PRE1_current1_pre1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE2_UNION
 �ṹ˵��  : CURRENT0_PRE2 �Ĵ����ṹ���塣��ַƫ����:0x191����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre2[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre2 : 8;  /* bit[0-7]: ��ǰ����ǰ����ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE2_UNION;
#endif
#define PMIC_CURRENT0_PRE2_current0_pre2_START  (0)
#define PMIC_CURRENT0_PRE2_current0_pre2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE2_UNION
 �ṹ˵��  : CURRENT1_PRE2 �Ĵ����ṹ���塣��ַƫ����:0x192����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre2[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE2_UNION;
#endif
#define PMIC_CURRENT1_PRE2_current1_pre2_START  (0)
#define PMIC_CURRENT1_PRE2_current1_pre2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE3_UNION
 �ṹ˵��  : CURRENT0_PRE3 �Ĵ����ṹ���塣��ַƫ����:0x193����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre3[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre3 : 8;  /* bit[0-7]: ��ǰ����ǰ����ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE3_UNION;
#endif
#define PMIC_CURRENT0_PRE3_current0_pre3_START  (0)
#define PMIC_CURRENT0_PRE3_current0_pre3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE3_UNION
 �ṹ˵��  : CURRENT1_PRE3 �Ĵ����ṹ���塣��ַƫ����:0x194����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre3[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE3_UNION;
#endif
#define PMIC_CURRENT1_PRE3_current1_pre3_START  (0)
#define PMIC_CURRENT1_PRE3_current1_pre3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE4_UNION
 �ṹ˵��  : CURRENT0_PRE4 �Ĵ����ṹ���塣��ַƫ����:0x195����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre4[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre4 : 8;  /* bit[0-7]: ��ǰ����ǰ�Ĵ�ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE4_UNION;
#endif
#define PMIC_CURRENT0_PRE4_current0_pre4_START  (0)
#define PMIC_CURRENT0_PRE4_current0_pre4_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE4_UNION
 �ṹ˵��  : CURRENT1_PRE4 �Ĵ����ṹ���塣��ַƫ����:0x196����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre4[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre4 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE4_UNION;
#endif
#define PMIC_CURRENT1_PRE4_current1_pre4_START  (0)
#define PMIC_CURRENT1_PRE4_current1_pre4_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE5_UNION
 �ṹ˵��  : CURRENT0_PRE5 �Ĵ����ṹ���塣��ַƫ����:0x197����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre5[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre5 : 8;  /* bit[0-7]: ��ǰ����ǰ���ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE5_UNION;
#endif
#define PMIC_CURRENT0_PRE5_current0_pre5_START  (0)
#define PMIC_CURRENT0_PRE5_current0_pre5_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE5_UNION
 �ṹ˵��  : CURRENT1_PRE5 �Ĵ����ṹ���塣��ַƫ����:0x198����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre5[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre5 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE5_UNION;
#endif
#define PMIC_CURRENT1_PRE5_current1_pre5_START  (0)
#define PMIC_CURRENT1_PRE5_current1_pre5_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE6_UNION
 �ṹ˵��  : CURRENT0_PRE6 �Ĵ����ṹ���塣��ַƫ����:0x199����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre6[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre6 : 8;  /* bit[0-7]: ��ǰ����ǰ����ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE6_UNION;
#endif
#define PMIC_CURRENT0_PRE6_current0_pre6_START  (0)
#define PMIC_CURRENT0_PRE6_current0_pre6_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE6_UNION
 �ṹ˵��  : CURRENT1_PRE6 �Ĵ����ṹ���塣��ַƫ����:0x19A����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre6[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre6 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE6_UNION;
#endif
#define PMIC_CURRENT1_PRE6_current1_pre6_START  (0)
#define PMIC_CURRENT1_PRE6_current1_pre6_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE7_UNION
 �ṹ˵��  : CURRENT0_PRE7 �Ĵ����ṹ���塣��ַƫ����:0x19B����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre7[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre7 : 8;  /* bit[0-7]: ��ǰ����ǰ�ߴ�ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE7_UNION;
#endif
#define PMIC_CURRENT0_PRE7_current0_pre7_START  (0)
#define PMIC_CURRENT0_PRE7_current0_pre7_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE7_UNION
 �ṹ˵��  : CURRENT1_PRE7 �Ĵ����ṹ���塣��ַƫ����:0x19C����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre7[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre7 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE7_UNION;
#endif
#define PMIC_CURRENT1_PRE7_current1_pre7_START  (0)
#define PMIC_CURRENT1_PRE7_current1_pre7_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE8_UNION
 �ṹ˵��  : CURRENT0_PRE8 �Ĵ����ṹ���塣��ַƫ����:0x19D����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre8[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre8 : 8;  /* bit[0-7]: ��ǰ����ǰ�˴�ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE8_UNION;
#endif
#define PMIC_CURRENT0_PRE8_current0_pre8_START  (0)
#define PMIC_CURRENT0_PRE8_current0_pre8_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE8_UNION
 �ṹ˵��  : CURRENT1_PRE8 �Ĵ����ṹ���塣��ַƫ����:0x19E����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre8[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre8 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE8_UNION;
#endif
#define PMIC_CURRENT1_PRE8_current1_pre8_START  (0)
#define PMIC_CURRENT1_PRE8_current1_pre8_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT0_PRE9_UNION
 �ṹ˵��  : CURRENT0_PRE9 �Ĵ����ṹ���塣��ַƫ����:0x19F����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre9[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre9 : 8;  /* bit[0-7]: ��ǰ����ǰ�Ŵ�ֵ[15:0]�� */
    } reg;
} PMIC_CURRENT0_PRE9_UNION;
#endif
#define PMIC_CURRENT0_PRE9_current0_pre9_START  (0)
#define PMIC_CURRENT0_PRE9_current0_pre9_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CURRENT1_PRE9_UNION
 �ṹ˵��  : CURRENT1_PRE9 �Ĵ����ṹ���塣��ַƫ����:0x1A0����ֵ:0x00�����:8
 �Ĵ���˵��: current_pre9[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre9 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE9_UNION;
#endif
#define PMIC_CURRENT1_PRE9_current1_pre9_START  (0)
#define PMIC_CURRENT1_PRE9_current1_pre9_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_CURRENT_MOD_0_UNION
 �ṹ˵��  : OFFSET_CURRENT_MOD_0 �Ĵ����ṹ���塣��ַƫ����:0x1A1����ֵ:0x00�����:8
 �Ĵ���˵��: ����ƫ�õ���[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current_mod_0 : 8;  /* bit[0-7]: ����ƫ�õ�����
                                                               ����д��8bit����д��8bit��һ������д������������һ�����ݵ�8bitд�������������ݸ�8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_OFFSET_CURRENT_MOD_0_UNION;
#endif
#define PMIC_OFFSET_CURRENT_MOD_0_offset_current_mod_0_START  (0)
#define PMIC_OFFSET_CURRENT_MOD_0_offset_current_mod_0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_CURRENT_MOD_1_UNION
 �ṹ˵��  : OFFSET_CURRENT_MOD_1 �Ĵ����ṹ���塣��ַƫ����:0x1A2����ֵ:0x00�����:8
 �Ĵ���˵��: ����ƫ�õ���[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current_mod_1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_CURRENT_MOD_1_UNION;
#endif
#define PMIC_OFFSET_CURRENT_MOD_1_offset_current_mod_1_START  (0)
#define PMIC_OFFSET_CURRENT_MOD_1_offset_current_mod_1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_VOLTAGE_MOD_0_UNION
 �ṹ˵��  : OFFSET_VOLTAGE_MOD_0 �Ĵ����ṹ���塣��ַƫ����:0x1A3����ֵ:0x00�����:8
 �Ĵ���˵��: ��ѹƫ�õ���[7:0]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage_mod_0 : 8;  /* bit[0-7]: ��ѹƫ�õ�����
                                                               ����д��8bit����д��8bit��һ������д������������һ�����ݵ�8bitд�������������ݸ�8bitд�������ټ��3��32kHzϵͳʱ�����ڡ��� */
    } reg;
} PMIC_OFFSET_VOLTAGE_MOD_0_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE_MOD_0_offset_voltage_mod_0_START  (0)
#define PMIC_OFFSET_VOLTAGE_MOD_0_offset_voltage_mod_0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_OFFSET_VOLTAGE_MOD_1_UNION
 �ṹ˵��  : OFFSET_VOLTAGE_MOD_1 �Ĵ����ṹ���塣��ַƫ����:0x1A4����ֵ:0x00�����:8
 �Ĵ���˵��: ��ѹƫ�õ���[15:8]�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage_mod_1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_VOLTAGE_MOD_1_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE_MOD_1_offset_voltage_mod_1_START  (0)
#define PMIC_OFFSET_VOLTAGE_MOD_1_offset_voltage_mod_1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_RESERVED1_UNION
 �ṹ˵��  : CLJ_RESERVED1 �Ĵ����ṹ���塣��ַƫ����:0x1A5����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼƱ���1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  clj_rw_inf1 : 8;  /* bit[0-7]: ��Ʒ���ר�ã��Կ��ؼƿ�ά�ɲ⣬�����ڼ�¼���ݣ����Կ��ؼ�״̬�����κ����á� */
    } reg;
} PMIC_CLJ_RESERVED1_UNION;
#endif
#define PMIC_CLJ_RESERVED1_clj_rw_inf1_START  (0)
#define PMIC_CLJ_RESERVED1_clj_rw_inf1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_RESERVED2_UNION
 �ṹ˵��  : CLJ_RESERVED2 �Ĵ����ṹ���塣��ַƫ����:0x1A6����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼƱ���2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  clj_rw_inf2 : 8;  /* bit[0-7]: ��Ʒ���ר�ã��Կ��ؼƿ�ά�ɲ⣬�����ڼ�¼���ݣ����Կ��ؼ�״̬�����κ����á� */
    } reg;
} PMIC_CLJ_RESERVED2_UNION;
#endif
#define PMIC_CLJ_RESERVED2_clj_rw_inf2_START  (0)
#define PMIC_CLJ_RESERVED2_clj_rw_inf2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_RESERVED3_UNION
 �ṹ˵��  : CLJ_RESERVED3 �Ĵ����ṹ���塣��ַƫ����:0x1A7����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼƱ���3�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  clj_rw_inf3 : 8;  /* bit[0-7]: ��Ʒ���ר�ã��Կ��ؼƿ�ά�ɲ⣬�����ڼ�¼���ݣ����Կ��ؼ�״̬�����κ����á� */
    } reg;
} PMIC_CLJ_RESERVED3_UNION;
#endif
#define PMIC_CLJ_RESERVED3_clj_rw_inf3_START  (0)
#define PMIC_CLJ_RESERVED3_clj_rw_inf3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_RESERVED4_UNION
 �ṹ˵��  : CLJ_RESERVED4 �Ĵ����ṹ���塣��ַƫ����:0x1A8����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼƱ���4�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  clj_rw_inf4 : 8;  /* bit[0-7]: ��Ʒ���ר�ã��Կ��ؼƿ�ά�ɲ⣬�����ڼ�¼���ݣ����Կ��ؼ�״̬�����κ����á� */
    } reg;
} PMIC_CLJ_RESERVED4_UNION;
#endif
#define PMIC_CLJ_RESERVED4_clj_rw_inf4_START  (0)
#define PMIC_CLJ_RESERVED4_clj_rw_inf4_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_RESERVED5_UNION
 �ṹ˵��  : CLJ_RESERVED5 �Ĵ����ṹ���塣��ַƫ����:0x1A9����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼƱ���5�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_reserve_1 : 8;  /* bit[0-7]: ���ؼ�ģ��Ĵ��������� */
    } reg;
} PMIC_CLJ_RESERVED5_UNION;
#endif
#define PMIC_CLJ_RESERVED5_i_reserve_1_START  (0)
#define PMIC_CLJ_RESERVED5_i_reserve_1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_RESERVED6_UNION
 �ṹ˵��  : CLJ_RESERVED6 �Ĵ����ṹ���塣��ַƫ����:0x1AA����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼƱ���6�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_reserve_2 : 8;  /* bit[0-7]: ���ؼ�ģ��Ĵ��������� */
    } reg;
} PMIC_CLJ_RESERVED6_UNION;
#endif
#define PMIC_CLJ_RESERVED6_i_reserve_2_START  (0)
#define PMIC_CLJ_RESERVED6_i_reserve_2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_RESERVED7_UNION
 �ṹ˵��  : CLJ_RESERVED7 �Ĵ����ṹ���塣��ַƫ����:0x1AB����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼƱ���7�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_reserve_1 : 8;  /* bit[0-7]: ���ؼ�ģ��Ĵ��������� */
    } reg;
} PMIC_CLJ_RESERVED7_UNION;
#endif
#define PMIC_CLJ_RESERVED7_v_reserve_1_START  (0)
#define PMIC_CLJ_RESERVED7_v_reserve_1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_PMU_SOFT_RST_UNION
 �ṹ˵��  : PMU_SOFT_RST �Ĵ����ṹ���塣��ַƫ����:0x1AC����ֵ:0x00�����:8
 �Ĵ���˵��: PMU��λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_rst_n : 8;  /* bit[0-7]: ���ؼ���λ��
                                                     0x11:��λ���ؼ�ģ�飻
                                                     0x1F:������ؼ�ģ�鸴λ��
                                                     д��������Ч��
                                                     
                                                     CODECģ����λ��
                                                     0x22:��λCODECģ�飻
                                                     0x2F:���CODECģ�鸴λ��
                                                     д��������Ч��
                                                     
                                                     DCXOģʽʱ��У׼��λ��
                                                     0x33:��λDCXOģʽ��
                                                     0x3F:���DCXOģʽ��λ��
                                                     д��������Ч�� */
    } reg;
} PMIC_PMU_SOFT_RST_UNION;
#endif
#define PMIC_PMU_SOFT_RST_soft_rst_n_START  (0)
#define PMIC_PMU_SOFT_RST_soft_rst_n_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_DEBUG_UNION
 �ṹ˵��  : CLJ_DEBUG �Ĵ����ṹ���塣��ַƫ����:0x1AD����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼ�DEBUGר��1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cic_clk_inv_i    : 1;  /* bit[0]: ���ƿ��ؼƵ����˲���·��һ��ȡ��ʱ�ӡ�
                                                         0����Ч��
                                                         1����Ч�� */
        unsigned char  cic_clk_inv_v    : 1;  /* bit[1]: ���ƿ��ؼƵ�ѹ�˲���·��һ��ȡ��ʱ�ӡ�
                                                         0����Ч��
                                                         1����Ч�� */
        unsigned char  adc_ana_v_output : 1;  /* bit[2]: ����CK32_BT�ܽţ���ѹADCģ������� */
        unsigned char  adc_ana_i_output : 1;  /* bit[3]: ����CK32_GPS�ܽţ�����ADCģ������� */
        unsigned char  cali_en_i        : 1;  /* bit[4]: ��������Ƿ�У׼ѡ��
                                                         0������������
                                                         1������ʼ�ղ����м��У׼�� */
        unsigned char  cali_en_i_force  : 1;  /* bit[5]: ����У׼ѡ��
                                                         0��������ǿ��У׼��
                                                         1������ǿ��У׼��
                                                         ���Ϲ��ܾ���clj_debug[4]=0ʱ�����á� */
        unsigned char  cali_en_v_force  : 1;  /* bit[6]: ��ѹУ׼ѡ��
                                                         0����ѹ��ǿ��У׼��
                                                         1����ѹǿ��У׼��
                                                         ���Ϲ��ܾ���clj_debug[7]=0ʱ�����á� */
        unsigned char  cali_en_v        : 1;  /* bit[7]: ��ѹ����Ƿ�У׼ѡ��
                                                         0������������
                                                         1����ѹ���ʼ�ղ�����У׼�� */
    } reg;
} PMIC_CLJ_DEBUG_UNION;
#endif
#define PMIC_CLJ_DEBUG_cic_clk_inv_i_START     (0)
#define PMIC_CLJ_DEBUG_cic_clk_inv_i_END       (0)
#define PMIC_CLJ_DEBUG_cic_clk_inv_v_START     (1)
#define PMIC_CLJ_DEBUG_cic_clk_inv_v_END       (1)
#define PMIC_CLJ_DEBUG_adc_ana_v_output_START  (2)
#define PMIC_CLJ_DEBUG_adc_ana_v_output_END    (2)
#define PMIC_CLJ_DEBUG_adc_ana_i_output_START  (3)
#define PMIC_CLJ_DEBUG_adc_ana_i_output_END    (3)
#define PMIC_CLJ_DEBUG_cali_en_i_START         (4)
#define PMIC_CLJ_DEBUG_cali_en_i_END           (4)
#define PMIC_CLJ_DEBUG_cali_en_i_force_START   (5)
#define PMIC_CLJ_DEBUG_cali_en_i_force_END     (5)
#define PMIC_CLJ_DEBUG_cali_en_v_force_START   (6)
#define PMIC_CLJ_DEBUG_cali_en_v_force_END     (6)
#define PMIC_CLJ_DEBUG_cali_en_v_START         (7)
#define PMIC_CLJ_DEBUG_cali_en_v_END           (7)


/*****************************************************************************
 �ṹ��    : PMIC_CLJ_DEBUG_2_UNION
 �ṹ˵��  : CLJ_DEBUG_2 �Ĵ����ṹ���塣��ַƫ����:0x1AE����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼ�DEBUGר��2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_coul_always_off : 1;  /* bit[0]  : �����Ƴ��ؿ��ơ�
                                                                  0���������ܣ�
                                                                  1�������Ƴ��ء�
                                                                  Ĭ��Ϊ1'b0�� */
        unsigned char  voltage_coul_always_off : 1;  /* bit[1]  : ��ѹ�Ƴ��ؿ��ơ�
                                                                  0���������ܣ�
                                                                  1����ѹ�Ƴ��ء�
                                                                  Ĭ��Ϊ1'b0�� */
        unsigned char  coul_gate_clk_en        : 1;  /* bit[2]  : ���ؼ��ſ�ʱ��ʹ�ܡ�
                                                                  0�������ſ�ʹ�ܣ�
                                                                  1���ر��ſ�ʹ�ܡ�
                                                                  Ĭ��Ϊ1'b0�� */
        unsigned char  reg_data_clr            : 1;  /* bit[3]  : 20��Ĵ�������������ѹ�����ֵ�ָ���ʼֵ���á�
                                                                  0�����ָ���ʼֵ��
                                                                  1���ָ���ʼֵ��(д1�Զ�����) */
        unsigned char  reserved                : 4;  /* bit[4-7]: ������ */
    } reg;
} PMIC_CLJ_DEBUG_2_UNION;
#endif
#define PMIC_CLJ_DEBUG_2_current_coul_always_off_START  (0)
#define PMIC_CLJ_DEBUG_2_current_coul_always_off_END    (0)
#define PMIC_CLJ_DEBUG_2_voltage_coul_always_off_START  (1)
#define PMIC_CLJ_DEBUG_2_voltage_coul_always_off_END    (1)
#define PMIC_CLJ_DEBUG_2_coul_gate_clk_en_START         (2)
#define PMIC_CLJ_DEBUG_2_coul_gate_clk_en_END           (2)
#define PMIC_CLJ_DEBUG_2_reg_data_clr_START             (3)
#define PMIC_CLJ_DEBUG_2_reg_data_clr_END               (3)


/*****************************************************************************
 �ṹ��    : PMIC_STATE_TEST_UNION
 �ṹ˵��  : STATE_TEST �Ĵ����ṹ���塣��ַƫ����:0x1AF����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼ�DEBUGר��3�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  state_test : 3;  /* bit[0-2]: bit[2:0]��ʾ��ѹ������ת״̬��
                                                     000��CLJ_OFF(���ؼƹر�״̬)��
                                                     001��CLJ_ON(���ؼƿ���״̬)��
                                                     010��OCV_DETE(���ؼ�ocv��ѹ����״̬)��
                                                     011��CALIBRATION(���ؼ��Զ�У׼״̬)��
                                                     100��NORMAL_FUNC(���ؼ���������״̬)��
                                                     101��ECO_REFLASH(���ؼƽ���͹���ǰһ��״̬)��
                                                     110��ECO_POWER_OFF(���ؼƽ���͹���״̬)��
                                                     111��WAITTING(���ؼ��˳��͹��ĺ�һ��״̬)���� */
        unsigned char  reserved   : 5;  /* bit[3-7]: ������ */
    } reg;
} PMIC_STATE_TEST_UNION;
#endif
#define PMIC_STATE_TEST_state_test_START  (0)
#define PMIC_STATE_TEST_state_test_END    (2)


/*****************************************************************************
 �ṹ��    : PMIC_COUL_RESERVE_UNION
 �ṹ˵��  : COUL_RESERVE �Ĵ����ṹ���塣��ַƫ����:0x1B0����ֵ:0x00�����:8
 �Ĵ���˵��: ���ؼ���ģ�ӿ�Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  coul_reserve : 8;  /* bit[0-7]: ��ģ�ӿ�Ԥ���Ĵ����� */
    } reg;
} PMIC_COUL_RESERVE_UNION;
#endif
#define PMIC_COUL_RESERVE_coul_reserve_START  (0)
#define PMIC_COUL_RESERVE_coul_reserve_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SOFT_RESERE0_UNION
 �ṹ˵��  : SOFT_RESERE0 �Ĵ����ṹ���塣��ַƫ����:0x1B1����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve0 : 8;  /* bit[0-7]: �������ԼĴ����� */
    } reg;
} PMIC_SOFT_RESERE0_UNION;
#endif
#define PMIC_SOFT_RESERE0_soft_reserve0_START  (0)
#define PMIC_SOFT_RESERE0_soft_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SOFT_RESERE1_UNION
 �ṹ˵��  : SOFT_RESERE1 �Ĵ����ṹ���塣��ַƫ����:0x1B2����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve1 : 8;  /* bit[0-7]: �������ԼĴ����� */
    } reg;
} PMIC_SOFT_RESERE1_UNION;
#endif
#define PMIC_SOFT_RESERE1_soft_reserve1_START  (0)
#define PMIC_SOFT_RESERE1_soft_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SOFT_RESERE2_UNION
 �ṹ˵��  : SOFT_RESERE2 �Ĵ����ṹ���塣��ַƫ����:0x1B3����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve2 : 8;  /* bit[0-7]: �������ԼĴ����� */
    } reg;
} PMIC_SOFT_RESERE2_UNION;
#endif
#define PMIC_SOFT_RESERE2_soft_reserve2_START  (0)
#define PMIC_SOFT_RESERE2_soft_reserve2_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SOFT_RESERE3_UNION
 �ṹ˵��  : SOFT_RESERE3 �Ĵ����ṹ���塣��ַƫ����:0x1B4����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve3 : 8;  /* bit[0-7]: �������ԼĴ����� */
    } reg;
} PMIC_SOFT_RESERE3_UNION;
#endif
#define PMIC_SOFT_RESERE3_soft_reserve3_START  (0)
#define PMIC_SOFT_RESERE3_soft_reserve3_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SOFT_RESERE4_UNION
 �ṹ˵��  : SOFT_RESERE4 �Ĵ����ṹ���塣��ַƫ����:0x1B5����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve4 : 8;  /* bit[0-7]: �������ԼĴ����� */
    } reg;
} PMIC_SOFT_RESERE4_UNION;
#endif
#define PMIC_SOFT_RESERE4_soft_reserve4_START  (0)
#define PMIC_SOFT_RESERE4_soft_reserve4_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SOFT_RESERE5_UNION
 �ṹ˵��  : SOFT_RESERE5 �Ĵ����ṹ���塣��ַƫ����:0x1B6����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve5 : 8;  /* bit[0-7]: �������ԼĴ����� */
    } reg;
} PMIC_SOFT_RESERE5_UNION;
#endif
#define PMIC_SOFT_RESERE5_soft_reserve5_START  (0)
#define PMIC_SOFT_RESERE5_soft_reserve5_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SOFT_RESERE6_UNION
 �ṹ˵��  : SOFT_RESERE6 �Ĵ����ṹ���塣��ַƫ����:0x1B7����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve6 : 8;  /* bit[0-7]: �������ԼĴ����� */
    } reg;
} PMIC_SOFT_RESERE6_UNION;
#endif
#define PMIC_SOFT_RESERE6_soft_reserve6_START  (0)
#define PMIC_SOFT_RESERE6_soft_reserve6_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_SOFT_RESERE7_UNION
 �ṹ˵��  : SOFT_RESERE7 �Ĵ����ṹ���塣��ַƫ����:0x1B8����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ԥ���Ĵ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve7 : 8;  /* bit[0-7]: �������ԼĴ����� */
    } reg;
} PMIC_SOFT_RESERE7_UNION;
#endif
#define PMIC_SOFT_RESERE7_soft_reserve7_START  (0)
#define PMIC_SOFT_RESERE7_soft_reserve7_END    (7)




/****************************************************************************
                     (5/5) HKADC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : PMIC_ADC_CTRL_UNION
 �ṹ˵��  : ADC_CTRL �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x80�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_chanl_sel : 5;  /* bit[0-4]: HKADC����ͨ��ѡ��Ĵ�����
                                                          00000��HKADC_IN0��
                                                          00001��HKADC_IN1��
                                                          00010��HKADC_IN2��
                                                          00011��HKADC_IN3��
                                                          ����
                                                          01100��HKADC_IN12��
                                                          01101��HKADC_IN13��
                                                          01110��HKADC_IN14��VSYS�ڲ�ͨ������
                                                          01111��HKADC_IN15��hkadc���ڲ�У׼ͨ����0.125v��255����룩��
                                                          10000��HKADC_IN16��hkadc�ڲ�У׼ͨ����������)
                                                          10001��HKADC_IN17��hkadc�ڲ�У׼ͨ���������ã�
                                                          10010��������
                                                          ����
                                                          11111�������� */
        unsigned char  hkadc_fre_sel   : 2;  /* bit[5-6]: HKADCת������ѡ��Ĵ�����
                                                          00��100kHz��
                                                          01��50kHz��
                                                          10��20kHz��
                                                          11��10kHz�� */
        unsigned char  hkadc_bapass    : 1;  /* bit[7]  : HKADC Bypass�Ĵ�����
                                                          0��HKADC����������
                                                          1��HKADC�رա� */
    } reg;
} PMIC_ADC_CTRL_UNION;
#endif
#define PMIC_ADC_CTRL_hkadc_chanl_sel_START  (0)
#define PMIC_ADC_CTRL_hkadc_chanl_sel_END    (4)
#define PMIC_ADC_CTRL_hkadc_fre_sel_START    (5)
#define PMIC_ADC_CTRL_hkadc_fre_sel_END      (6)
#define PMIC_ADC_CTRL_hkadc_bapass_START     (7)
#define PMIC_ADC_CTRL_hkadc_bapass_END       (7)


/*****************************************************************************
 �ṹ��    : PMIC_ADC_START_UNION
 �ṹ˵��  : ADC_START �Ĵ����ṹ���塣��ַƫ����:0x01����ֵ:0x00�����:8
 �Ĵ���˵��: ADCת����ʼ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_start : 1;  /* bit[0]  : �����ش���һ������ת��������ת����ɺ�HKADC�Զ�����üĴ�����  */
        unsigned char  reserved    : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_ADC_START_UNION;
#endif
#define PMIC_ADC_START_hkadc_start_START  (0)
#define PMIC_ADC_START_hkadc_start_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_CONV_STATUS_UNION
 �ṹ˵��  : CONV_STATUS �Ĵ����ṹ���塣��ַƫ����:0x02����ֵ:0x00�����:8
 �Ĵ���˵��: ADCת��״ָ̬ʾ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_valid : 1;  /* bit[0]  : HKADC״̬λ��
                                                      0��ת�������У�
                                                      1��ת����ϡ�
                                                      (ע����bit��ת����ʼʱ�������ͣ���ת�������󣬱�ɡ�1�������ҡ�1��һֱ��������һ��ת����ʼ)�� */
        unsigned char  reserved    : 7;  /* bit[1-7]: ������ */
    } reg;
} PMIC_CONV_STATUS_UNION;
#endif
#define PMIC_CONV_STATUS_hkadc_valid_START  (0)
#define PMIC_CONV_STATUS_hkadc_valid_END    (0)


/*****************************************************************************
 �ṹ��    : PMIC_ADC_DATA1_UNION
 �ṹ˵��  : ADC_DATA1 �Ĵ����ṹ���塣��ַƫ����:0x03����ֵ:0x00�����:8
 �Ĵ���˵��: ADC�����λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_data11_4 : 8;  /* bit[0-7]: ת������ĸ�8λbit[11:4]�� */
    } reg;
} PMIC_ADC_DATA1_UNION;
#endif
#define PMIC_ADC_DATA1_hkadc_data11_4_START  (0)
#define PMIC_ADC_DATA1_hkadc_data11_4_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ADC_DATA0_UNION
 �ṹ˵��  : ADC_DATA0 �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x00�����:8
 �Ĵ���˵��: ADC�����λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved      : 4;  /* bit[0-3]: ������ */
        unsigned char  hkadc_data3_0 : 4;  /* bit[4-7]: ת������ĵ�4λbit[3:0]�� */
    } reg;
} PMIC_ADC_DATA0_UNION;
#endif
#define PMIC_ADC_DATA0_hkadc_data3_0_START  (4)
#define PMIC_ADC_DATA0_hkadc_data3_0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ADC_CONV_UNION
 �ṹ˵��  : ADC_CONV �Ĵ����ṹ���塣��ַƫ����:0x05����ֵ:0x00�����:8
 �Ĵ���˵��: ADCת��ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_buffer_sel : 1;  /* bit[0]  : HKADC����ͨ��bufferѡͨ�Ĵ�����
                                                           0��ѡ��ͨ��bufferѡͨ״̬��
                                                           1��������ͨ��buffer�� */
        unsigned char  hkadc_config     : 6;  /* bit[1-6]: ������ */
        unsigned char  reserved         : 1;  /* bit[7]  : ������ */
    } reg;
} PMIC_ADC_CONV_UNION;
#endif
#define PMIC_ADC_CONV_hkadc_buffer_sel_START  (0)
#define PMIC_ADC_CONV_hkadc_buffer_sel_END    (0)
#define PMIC_ADC_CONV_hkadc_config_START      (1)
#define PMIC_ADC_CONV_hkadc_config_END        (6)


/*****************************************************************************
 �ṹ��    : PMIC_ADC_CURRENT_UNION
 �ṹ˵��  : ADC_CURRENT �Ĵ����ṹ���塣��ַƫ����:0x06����ֵ:0x00�����:8
 �Ĵ���˵��: ADCibas�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_ibias_sel : 8;  /* bit[0-7]: bit[7:6]��hkadc_comp biasѡ��Ĵ�����
                                                          00��4uA��
                                                          01��3uA��
                                                          10��2uA��
                                                          11��1uA��
                                                          bit[5:3]�����á�
                                                          bit[2:0]��hkadc_input buffer biasѡ��Ĵ�����
                                                          000��1.25u
                                                          001��1.75u��
                                                          010��0.75u��
                                                          011��1.25u��
                                                          100��1.00u��
                                                          101��1.50u��
                                                          110��0.50u��
                                                          111��1.00u�� */
    } reg;
} PMIC_ADC_CURRENT_UNION;
#endif
#define PMIC_ADC_CURRENT_hkadc_ibias_sel_START  (0)
#define PMIC_ADC_CURRENT_hkadc_ibias_sel_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ADC_CALI_CTRL_UNION
 �ṹ˵��  : ADC_CALI_CTRL �Ĵ����ṹ���塣��ַƫ����:0x07����ֵ:0x00�����:8
 �Ĵ���˵��: ADCУ׼���ÿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_cali_en  : 1;  /* bit[0]  : HKADC У׼ʹ�ܡ�
                                                         0��HKADCУ׼�رգ�
                                                         1��HKADCУ׼������
                                                         Ĭ��Ϊ0�� */
        unsigned char  hkadc_cali_sel : 1;  /* bit[1]  : HKADCУ׼ֵѡ��ʹ�ܡ�
                                                         0��У׼��·У׼ֵ��
                                                         1���������У׼ֵ�� */
        unsigned char  reserved       : 6;  /* bit[2-7]: ������ */
    } reg;
} PMIC_ADC_CALI_CTRL_UNION;
#endif
#define PMIC_ADC_CALI_CTRL_hkadc_cali_en_START   (0)
#define PMIC_ADC_CALI_CTRL_hkadc_cali_en_END     (0)
#define PMIC_ADC_CALI_CTRL_hkadc_cali_sel_START  (1)
#define PMIC_ADC_CALI_CTRL_hkadc_cali_sel_END    (1)


/*****************************************************************************
 �ṹ��    : PMIC_ADC_CALI_VALUE_UNION
 �ṹ˵��  : ADC_CALI_VALUE �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x00�����:8
 �Ĵ���˵��: ADCУ׼ֵ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_cali_data : 8;  /* bit[0-7]: HKADC��·У׼ֵ�� */
    } reg;
} PMIC_ADC_CALI_VALUE_UNION;
#endif
#define PMIC_ADC_CALI_VALUE_hkadc_cali_data_START  (0)
#define PMIC_ADC_CALI_VALUE_hkadc_cali_data_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ADC_CALI_CFG_UNION
 �ṹ˵��  : ADC_CALI_CFG �Ĵ����ṹ���塣��ַƫ����:0x09����ֵ:0x00�����:8
 �Ĵ���˵��: ADCУ׼����ֵ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_cali_cfg : 8;  /* bit[0-7]: HKADC�������У׼ֵ�� */
    } reg;
} PMIC_ADC_CALI_CFG_UNION;
#endif
#define PMIC_ADC_CALI_CFG_hkadc_cali_cfg_START  (0)
#define PMIC_ADC_CALI_CFG_hkadc_cali_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ADC_RSV0_UNION
 �ṹ˵��  : ADC_RSV0 �Ĵ����ṹ���塣��ַƫ����:0x0A����ֵ:0x00�����:8
 �Ĵ���˵��: HKADCԤ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_reserve0 : 8;  /* bit[0-7]: ������ */
    } reg;
} PMIC_ADC_RSV0_UNION;
#endif
#define PMIC_ADC_RSV0_hkadc_reserve0_START  (0)
#define PMIC_ADC_RSV0_hkadc_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : PMIC_ADC_RSV1_UNION
 �ṹ˵��  : ADC_RSV1 �Ĵ����ṹ���塣��ַƫ����:0x0B����ֵ:0x00�����:8
 �Ĵ���˵��: HKADCԤ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_reserve1 : 8;  /* bit[0-7]: ������ */
    } reg;
} PMIC_ADC_RSV1_UNION;
#endif
#define PMIC_ADC_RSV1_hkadc_reserve1_START  (0)
#define PMIC_ADC_RSV1_hkadc_reserve1_END    (7)






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

#endif /* end of pmic_interface.h */
