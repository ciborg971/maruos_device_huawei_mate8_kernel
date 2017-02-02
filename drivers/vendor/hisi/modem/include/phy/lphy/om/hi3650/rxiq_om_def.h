/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

******************************************************************************
 �� �� ��   : rxiq_om_def.h
 �� �� ��   : ����
 ��    ��   : Shen Guang
 ��������   : 2011��06��23��
 ����޸�   :
 ��������   : RXIQ OM��ͷ�ļ�
 �����б�   :
 �޸���ʷ   :
 1.��    ��   : 2011��06��23��
   ��    ��   : Shen Guang
   �޸�����   : �����ļ�
******************************************************************************/


#ifndef __RXIQ_OM_DEF_H__
#define __RXIQ_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/

/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum
{
	LPHY_SG_RXIQ_REPORT_ENA 		= OM_CMD_ID(LPHY_RXIQ_MID, OM_TYPE_SG, 0x0),
}LPHY_SG_RXIQ_ENUM;

typedef enum
{
    LPHY_REQ_RXIQ_COMP_ENA          = OM_CMD_ID(LPHY_RXIQ_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_RXIQ_CALC_ENA,
    LPHY_REQ_RXIQ_FIXED_VALUE_ENA,
    LPHY_REQ_RXIQ_REPORT_ENA,
	LPHY_REQ_RXIQ_LIMIT_ENA,
	LPHY_REQ_RXIQ_FILT_COEF_ENA
}LPHY_REQ_RXIQ_ENUM;

typedef enum
{
    RXIQ_SWITCH_OFF = 0,
    RXIQ_SWITCH_ON,
    RXIQ_SWITCH_RESERVED,
}RXIQ_SWITCH_ENUM;

typedef struct
{
    RXIQ_SWITCH_ENUM    enEnable;
}LPHY_REQ_RXIQ_ENA_STRU;
typedef enum
{
    RXIQ_ON_AIR = 0,
    RXIQ_FIXED,
}RXIQ_FIX_ENABLE_ENUM;


typedef struct
{
    OM_REQ_ENABLE_ENUM    enEnable;
    RXIQ_FIX_ENABLE_ENUM  enFixedEn;
    UINT32                aulRxiqReg[2][2];//[ca][rx] om for ca
}LPHY_REQ_RXIQ_FIXED_VALUE_ENA_STRU;


typedef struct
{
    OM_REQ_ENABLE_ENUM    enEnable;
}LPHY_REQ_RXIQ_REPORT_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM    enEnable;
    UINT32                ulAPLimitReg;
}LPHY_REQ_RXIQ_LIMIT_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM    enEnable;
	struct {
		UINT8 ucWeight1;
		UINT8 ucWeight2;
		UINT8 ucThre;
		UINT8 uvRsv;
	} astCoef[2];
}LPHY_REQ_RXIQ_FILT_COEF_ENA_STRU;

typedef struct
{
	INT16 sA[2];
	INT16 sP[2];
	//alex tbd dc vs vga
}LPHY_AGC_OM_RXIQ_RPT_ONE_CC_STRU;

typedef struct
{
	LPHY_AGC_OM_RXIQ_RPT_ONE_CC_STRU astRxiq[2];//om for ca
}LPHY_SG_RXIQ_REPORT_ENA_STRU;


/************************************************************
                           3. Sg���ݽṹ����
************************************************************/


/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
/************************************************************
                           5. ERROR���ݽṹ����
************************************************************/

typedef enum
{
    LPHY_ERROR_RXIQ_ARRAY_INDEX         = OM_CMD_ID(LPHY_DCOC_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_RXIQ_CASE,
}LPHY_ERROR_RXIQ_ENUM;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulIncorrectValue;
}LPHY_ERROR_RXIQ_ARRAY_INDEX_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulCase;
}LPHY_ERROR_RXIQ_CASE_STRU;

typedef union
{
    LPHY_ERROR_RXIQ_ARRAY_INDEX_STRU   stRxiqArrayIndexError;
    LPHY_ERROR_RXIQ_CASE_STRU          stRxiqCaseError;
}RXIQ_OM_REPORT_UNION;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __RXIQ_OM_DEF_H__ */

