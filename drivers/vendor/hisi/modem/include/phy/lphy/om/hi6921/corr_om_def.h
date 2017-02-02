/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : corr_om_def.h
  �� �� ��   : ����
  ��    ��   : tuzhiguo(52067)
  ��������   : 2010��12��29��
  ����޸�   :
  ��������   : �������ģ��OM��Ҫ�ϱ��Ľṹ��,���ļ����ջύ����HiStudioʹ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��12��29��
    ��    ��   : tuzhiguo(52067)
    �޸�����   : �����ļ�

  2.��    ��   : 2011��05��26��
    ��    ��   : tuzhiguo(52067)
    �޸�����   : CQI�������޸ĺ���

******************************************************************************/

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

#ifndef __CORR_OM_DEF_H__
#define __CORR_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum __LPHY_REQ_MSGID_CORR__
{
    LPHY_REQ_CORR_RESERVED            = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_CORR_WB_ALPHA,                              //�ǰ׻�����˲�����
    LPHY_REQ_CORR_SB_ALPHA,                              //�ǰ׻��Դ��˲�����
    LPHY_REQ_CORR_WHITE_ALPHA,                           //�׻����˲�����
	//LPHY_REQ_CORR_1T_OR_1R_NOISE_FACTOR,				   //����Լ���ʱ��1�������߻�1��������ʱ����������Ե���������
	//LPHY_REQ_CORR_2T2R_OR_4T2R_NOISE_FACTOR_2T,		   //2��2��ʱ����������Ե��������ӣ���4��2��ʱ���������Corr21,Corr22,Corr23ʱ���������� 
	//LPHY_REQ_CORR_4T2R_OR_8T2R_NOISE_FACTOR_4T,		   //4/8��2��ʱ�����������Corr1ʱ����������
	//LPHY_REQ_CORR_WHITE_1T_OR_1R_NOISE_FACTOR,		   //1�������߻�1��������ʱ�����������׻�����������������
	//LPHY_REQ_CORR_WHITE_2T2R_OR_4T2R_NOISE_FACTOR_2T,    //2��2��ʱ�����������׻����������������ӻ�4��2��ʱ���������Corr21,Corr22,Corr23����������
	//LPHY_REQ_CORR_WHITE_4T2R_NOISE_FACTOR_4T, 		   //4��2��ʱ�����������׻���������Corr1ʱ����������
	//LPHY_REQ_CORR_1T_OR_1R_THRESH,					   //1�������߻�1��������ʱ���ж�����Ե�����ֵ
	//LPHY_REQ_CORR_2T2R_OR_4T2R_THRESH,				   //2��2�ջ�4��2��ʱ���ж�����Ե�����ֵ
	//LPHY_REQ_CORR_FDD_CORRFLAG,						   //FDDģʽ�£������������֡�����ʱ��Flag
	//LPHY_REQ_CORR_TDD_CORRFLAG,						   //TDDģʽ�£������������֡�����ʱ��Flag
    //LPHY_REQ_CORR_HETNET_SNR_THRESH,                     //hetnet�������ж��Ƿ����Corr�����SNR����
}LPHY_REQ_MSGID_CORR_ENUM;

typedef struct __LPHY_REQ_CORR_1T_OR_1R_NOISE_FACTOR_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_1T_OR_1R_NOISE_FACTOR_STRU;

typedef struct __LPHY_REQ_CORR_2T2R_OR_4T2R_NOISE_FACTOR_2T_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_2T2R_OR_4T2R_NOISE_FACTOR_2T_STRU;

typedef struct __LPHY_REQ_CORR_4T2R_OR_8T2R_NOISE_FACTOR_4T_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_4T2R_OR_8T2R_NOISE_FACTOR_4T_STRU;

typedef struct __LPHY_REQ_CORR_WHITE_1T_OR_1R_NOISE_FACTOR_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_WHITE_1T_OR_1R_NOISE_FACTOR_STRU;

typedef struct __LPHY_REQ_CORR_WHITE_2T2R_OR_4T2R_NOISE_FACTOR_2T_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_WHITE_2T2R_OR_4T2R_NOISE_FACTOR_2T_STRU;

typedef struct __LPHY_REQ_CORR_WHITE_4T2R_NOISE_FACTOR_4T_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_WHITE_4T2R_NOISE_FACTOR_4T_STRU;

typedef struct __LPHY_REQ_CORR_1T_OR_1R_THRESH_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usThresh;
}LPHY_REQ_CORR_1T_OR_1R_THRESH_STRU;

typedef struct __LPHY_REQ_CORR_2T2R_OR_4T2R_THRESH__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usThresh;
}LPHY_REQ_CORR_2T2R_OR_4T2R_THRESH_STRU;

typedef struct __LPHY_REQ_CORR_FDD_CORRFLAG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucCorrFlag[6];
}LPHY_REQ_CORR_FDD_CORRFLAG_STRU;

typedef struct __LPHY_REQ_CORR_TDD_CORRFLAG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucCorrFlag[6];
}LPHY_REQ_CORR_TDD_CORRFLAG_STRU;

typedef struct __LPHY_REQ_CORR_WB_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucAlpha[6][3];
}LPHY_REQ_CORR_WB_ALPHA_STRU;

typedef struct __LPHY_REQ_CORR_SB_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucAlpha[6][3];
}LPHY_REQ_CORR_SB_ALPHA_STRU;

typedef struct __LPHY_REQ_CORR_WHITE_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usAlpha;
    UINT16                      usLT5MAlpha;
	UINT16                      usRsv;
}LPHY_REQ_CORR_WHITE_ALPHA_STRU;

typedef struct __LPHY_REQ_CORR_HETNET_SNR_THRESH_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    INT16                 sSnrThresh;
}LPHY_REQ_CORR_HETNET_SNR_THRESH_STRU;

/************************************************************
                           2. CNF���ݽṹ����
************************************************************/
typedef enum __LPHY_CNF_MSGID_CORR__
{
    LPHY_CNF_CORR_RESERVED            = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_CNF, 0x0),
}LPHY_CNF_MSGID_CORR_ENUM;


/************************************************************
                           3. Ind���ݽṹ����
************************************************************/
typedef enum __LPHY_IND_MSGID_CORR__
{
    LPHY_IND_CORR_RESERVED            = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_IND, 0x0),
}LPHY_IND_MSGID_CORR_ENUM;


/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
typedef enum __LPHY_TRACE_CORR_
{
    LPHY_TRACE_CORR_RESERVED         = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_TRACE, 0x0),
}LPHY_TRACE_CORR_ENUM;


/************************************************************
                           5. SG���ݽṹ����
************************************************************/
typedef enum __LPHY_SG_CORR_
{
    LPHY_SG_CORR_RESERVED         = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_SG, 0x0),
	LPHY_SG_PCELL_CS0_NONWHTN_CORR_RESULT,
    LPHY_SG_PCELL_CS0_WHTN_CORR_RESULT,
    LPHY_SG_PCELL_CS0_CORR_STAT,
	LPHY_SG_PCELL_CS1_NONWHTN_CORR_RESULT,
	LPHY_SG_PCELL_CS1_WHTN_CORR_RESULT,
	LPHY_SG_PCELL_CS1_CORR_STAT,
	LPHY_SG_SCELL_NONWHTN_CORR_RESULT,
	LPHY_SG_SCELL_WHTN_CORR_RESULT,
	LPHY_SG_SCELL_CORR_STAT,
}LPHY_SG_CORR_ENUM;

typedef struct __LPHY_SG_WHTN_CORR_RESULT_STRU__
{
    LTE_CHAN_SPACE_CORR_ENUM_UINT8  ucWhtnRecCorr;      /*0,��ʾ����أ�1����ʾ����أ�2��ʾ�����*/
    LTE_CHAN_SPACE_CORR_ENUM_UINT8  ucWhtnCorr;         /*0,��ʾ����أ�1����ʾ����أ�2��ʾ�����*/
	UINT32                          ulTransRecCorrDev[16];  /*����ͽ���֮�������Եı�ֵ*/
	UINT16                          usRsv;
}LPHY_SG_WHTN_CORR_RESULT_STRU;

typedef struct __LPHY_SG_NONWHTN_CORR_RESULT_STRU__
{
    LTE_CHAN_SPACE_CORR_ENUM_UINT8  ucNonWhtnRecCorr;   /*0,��ʾ����أ�1����ʾ����أ�2��ʾ�����*/
    LTE_CHAN_SPACE_CORR_ENUM_UINT8  ucNonWhtnCorr;      /*0,��ʾ����أ�1����ʾ����أ�2��ʾ�����*/
	UINT32                          ulTransRecCorrDev[16];  /*����ͽ���֮�������Եı�ֵ*/
	UINT16                          usRsv;
}LPHY_SG_NONWHTN_CORR_RESULT_STRU;

typedef struct __LPHY_SG_CORR_OM_STAT_STRU__
{
    UINT32      ulSubFrmCnt;                     /*��֡����*/
    UINT16      ulWhtnRecCorr[3];                /*���е������ռ�ٷֱ�*/
    UINT16      ulWhtnCorr[3];                   /*���е������ռ�ٷֱ�*/
    UINT16      ulNonWhtnRecCorr[3];             /*���е������ռ�ٷֱ�*/
    UINT16      ulNonWhtnCorr[3];                /*���е������ռ�ٷֱ�*/
	UINT32      ulTransRecCorrDev[16];           /*����ͽ���֮�������Ա�ֵ*/
	UINT8       ucWhtnIdx;                       /*����ͽ���֮�������Ա�ֵ��index*/
	UINT8       ucNonWhtnIdx;                    /*����ͽ���֮�������Ա�ֵ��index*/
	UINT16      usRsv;
}LPHY_SG_CORR_OM_STAT_STRU;

/************************************************************
                           6. DT���ݽṹ����
************************************************************/


typedef struct __LPHY_DT_NONWHTN_CORR_RESULT_STRU__
{
    UINT16      usSysFrmNum;            /*�ϱ�ʱ��ϵͳ֡��*/
	UINT16      usSubFrmNum;            /*�ϱ�ʱ����֡��*/
	LTE_CHAN_SPACE_CORR_ENUM_UINT8  ucNonWhtnRecCorr;   /*0,��ʾ����أ�1����ʾ����أ�2��ʾ�����*/
	UINT8                          usRsv[3];
}LPHY_DT_NONWHTN_CORR_RESULT_STRU;


typedef struct __LPHY_DT_WHTN_CORR_RESULT_STRU__
{
    UINT16      usSysFrmNum;            /*�ϱ�ʱ��ϵͳ֡��*/
	UINT16      usSubFrmNum;            /*�ϱ�ʱ����֡��*/
	LTE_CHAN_SPACE_CORR_ENUM_UINT8  ucWhtnRecCorr;   /*0,��ʾ����أ�1����ʾ����أ�2��ʾ�����*/
	UINT8                          usRsv[3];
}LPHY_DT_WHTN_CORR_RESULT_STRU;





typedef enum __LPHY_DT_CORR_
{
    LPHY_DT_CORR_RESERVED         = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_DT, 0x0),
	LPHY_DT_PCELL_CS0_NONWHTN_CORR_RESULT,
    LPHY_DT_PCELL_CS0_WHTN_CORR_RESULT,
    LPHY_DT_PCELL_CS0_CORR_STAT,
	LPHY_DT_PCELL_CS1_NONWHTN_CORR_RESULT,
	LPHY_DT_PCELL_CS1_WHTN_CORR_RESULT,
	LPHY_DT_PCELL_CS1_CORR_STAT,
	LPHY_DT_SCELL_NONWHTN_CORR_RESULT,
	LPHY_DT_SCELL_WHTN_CORR_RESULT,
	LPHY_DT_SCELL_CORR_STAT,
}LPHY_DT_CORR_ENUM;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CORR_OM_DEF_H__ */
