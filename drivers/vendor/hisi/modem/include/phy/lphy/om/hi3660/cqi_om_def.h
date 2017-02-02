/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : cqi_om_def.h
  �� �� ��   : ����
  ��    ��   : tuzhiguo(52067)
  ��������   : 2010��12��29��
  ����޸�   :
  ��������   : ���嶨ʱģ��OM��Ҫ�ϱ��Ľṹ��,���ļ����ջύ����HiStudioʹ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��12��29��
    ��    ��   : tuzhiguo(52067)
    �޸�����   : �����ļ�

  2.��    ��   : 2011��05��26��
    ��    ��   : tuzhiguo(52067)
    �޸�����   : CQI�������޸ĺ���

  3.��    ��   : 2011��05��26��
    ��    ��   : tuzhiguo(52067)
    �޸�����   : ���Ӳ��Բ���Ҫ��OM������ϱ����ںͷ����ڷ���ģʽ��
	            ����CQITrace����ӡ�յ���ԭ����Ϣ�����㶨λ
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

#ifndef __CQI_OM_DEF_H__
#define __CQI_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************/
#define	CQI_MAX_CA_NUM				4
#define	CQI_MAX_TM10_PROCESS_NUM	LPHY_FEATURE_MAX_CARRIER_NUM
/************************************************************/
typedef enum
{
	CQI_TYPE_A12 = 0,
	CQI_TYPE_A20,
	CQI_TYPE_A22,
	CQI_TYPE_A30,
	CQI_TYPE_A31,
	CQI_TYPE_A_BUTT
}CQI_RPT_TYPE_APERI_ENUM;
typedef UINT8 CQI_RPT_TYPE_APERI_ENUM_UINT8;

typedef enum
{
	CQI_TYPE_P1 = 0,
	CQI_TYPE_P1A,
	CQI_TYPE_P2,
	CQI_TYPE_P2A,
	CQI_TYPE_P2B,
	CQI_TYPE_P2C,
	CQI_TYPE_P3,
	CQI_TYPE_P4,
	CQI_TYPE_P5,
	CQI_TYPE_P6,
	CQI_TYPE_P_BUTT
}CQI_RPT_TYPE_PERI_ENUM;
typedef UINT8 CQI_RPT_TYPE_PERI_ENUM_UINT8;
/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum
{
	LPHY_REQ_CQI_RESERVED			 = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_REQ, 0x0),//0x30500000
	LPHY_REQ_CQI_CFG_OLLA				,
	LPHY_REQ_CQI_CFG_WHITEN 			,
	LPHY_REQ_CQI_CFG_CQI				,
	LPHY_REQ_CQI_CFG_PMI_SEL			,
	LPHY_REQ_CQI_CFG_RI 				,
	LPHY_REQ_CQI_DISP_RI_CQI_PMI_APERI	,	//��Э��涨������һ��
	LPHY_REQ_CQI_DISP_RI_CQI_PMI_PERI	,	//��Э��涨������һ��
	LPHY_REQ_CQI_DISP_ESINR_PCC_H0		,	//ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_ESINR_PCC_H1		,	//ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_ESINR_SCC1		,	//ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_ESINR_SCC2		,	//ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_ESINR_SCC3		,	//ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_WB_TSINR			,	//���cqi��Ŀ���Ÿ����,ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_WB_RBIR_PCC_H0	,	//���cqi��RBIR,ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_WB_RBIR_PCC_H1	,	//���cqi��RBIR,ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_WB_RBIR_SCC1		,	//���cqi��RBIR,ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_WB_RBIR_SCC2		,	//���cqi��RBIR,ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_WB_RBIR_SCC3		,	//���cqi��RBIR,ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_PERIOD_LEN        ,   //���cqi���Ӵ�cqi�ϱ�����,ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_RB_WHITEN_FLAG	,	//RB�İ׻�flag,ÿ����������ϱ�
	LPHY_REQ_CQI_DISP_RI_PERCENT		,	//RI=1,2,3,4��ͳ�ưٷֱ�,10s�ϱ�1��
	LPHY_REQ_CQI_DISP_SB_PMI_PERCENT	,	//�Ӵ�PMI=0~15��ͳ�ưٷֱ�,10s�ϱ�1��
	LPHY_REQ_CQI_DISP_WB_PMI_PERCENT	,	//���PMI=0~15��ͳ�ưٷֱ�,10s�ϱ�1��
	LPHY_REQ_CQI_DISP_SB_CQI_PERCENT	,	//�Ӵ�CQI0/1=0~15��ͳ�ưٷֱ�,10s�ϱ�1��
	LPHY_REQ_CQI_DISP_WB_CQI_PERCENT	,	//���CQI0/1=0~15��ͳ�ưٷֱ�,10s�ϱ�1��
	LPHY_REQ_CQI_DISP_WB_CQI_MEDIAN 	,	//���CQI0/1=0~15����λ����10s�ϱ�1��
	LPHY_REQ_CQI_DISP_PA_PC_DELTAOFSET  ,		//1s�ϱ�1��
	LPHY_DT_CQI_INFO_REQ            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_REQ, 0x100)
}LPHY_REQ_MSGID_CQI_ENUM;

typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	UINT8						ucCQIAdjSwitch;		//CQI�Ƿ������ʾ	0��������	1������
	UINT8						ucCQIAdjStepDown;	//CQI���µ�������
	UINT8						ucCQIAdjStepUp;		//CQI���ϵ�������
	UINT8						ucCQIAlpha;			//CQI�˲�����
	UINT8						ucCQISortFlag;		//CQI�˲�ʱ�Ƿ񰴴�С�����Flag	0��������С����	1������С����
	UINT8						ucRsv;
}LPHY_REQ_CQI_CFG_OLLA_STRU;

typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	UINT16						usRuuMode_CQI;		//Ĭ��ֵ1������ʱ1��ʾʹ��CRS��Ruu��0��ʾ����CMU;
	UINT16						usSNRThreshold;		//100,ʹ���������ɰ׻�������������
	UINT8   					ucCRSIC;			//0,v750�汾������CRSIC����
	UINT8   					ucTargetWidth_Ruu;	//16,
}LPHY_REQ_CQI_CFG_WHITEN_STRU;

typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	OM_REQ_ENABLE_ENUM_UINT16   usRbirAlpha_En;
	UINT16						usRbirAlpha;		//CQI��RBIR�˲�����֧�ִ�׮
	OM_REQ_ENABLE_ENUM_UINT16   sEsinrFactor5_En;
	INT16						sEsinrFactor5;		//��Ч����Ȳ�����3��ʱ����1������ֵ֧������
	OM_REQ_ENABLE_ENUM_UINT16   usUnevenThreshold_En;
	UINT16						usUnevenThreshold;	//512,���ż���Ų�ƽ���ж�����
	OM_REQ_ENABLE_ENUM_UINT16   sWbTsinr_En;
	INT16						sWbTsinr[15];		//���CQI��Ŀ���Ÿ����֧������
	OM_REQ_ENABLE_ENUM_UINT16   ucHextractInd_En;
	UINT8						ucHextractInd;		//0--��ȡż����ŵ�H����1--��ȡ������ŵ�H����
	UINT8						aucRsv;
	OM_REQ_ENABLE_ENUM_UINT16   ucFreqNoiseFactor_En;
	UINT8						ucFreqNoiseFactor;	//5
	UINT8						aucRsv1;
	OM_REQ_ENABLE_ENUM_UINT16   ucNoiseBitThres_En;
	UINT8						ucNoiseBitThres;	//14,NumLayers>=3��ʱ��������Сֵ,������3��4��
	UINT8						aucRsv2;
	OM_REQ_ENABLE_ENUM_UINT16   ucMinNoiseBit_En;
	UINT8						ucMinNoiseBit;		//5,��С��������,������3��4��
	UINT8						aucRsv3;
	OM_REQ_ENABLE_ENUM_UINT16   ucWbCqi_En;
	UINT8						ucWbCqi;			//�������õ��Ŀ��CQI�Ϳ��PMI��Ҫ���Դ�׮
	UINT8						aucRsv4;
	OM_REQ_ENABLE_ENUM_UINT16   ucWbPmi_En;
	UINT8						ucWbPmi;			//�������õ��Ŀ��CQI�Ϳ��PMI��Ҫ���Դ�׮
	UINT8						aucRsv5;
	OM_REQ_ENABLE_ENUM_UINT16   ucSbCqi_En;
	UINT8						ucSbCqi;			//�������õ����Ӵ�CQI���Ӵ�PMI��Ҫ���Դ�׮
	UINT8						aucRsv6;
	OM_REQ_ENABLE_ENUM_UINT16   ucSbPmi_En;
	UINT8						ucSbPmi;			//�������õ����Ӵ�CQI���Ӵ�PMI��Ҫ���Դ�׮
	UINT8						aucRsv7[3];
}LPHY_REQ_CQI_CFG_CQI_STRU;


typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	OM_REQ_ENABLE_ENUM_UINT16   ulFactorJump_En;
	UINT16						ulFactorJump;		//CQI��RBIR�˲�����֧�ִ�׮
	OM_REQ_ENABLE_ENUM_UINT16   ulFactorRi3_En;
	UINT16						ulFactorRi3;		//CQI��RBIR�˲�����֧�ִ�׮
	OM_REQ_ENABLE_ENUM_UINT16   ulFactorRi4_En;
	UINT16						ulFactorRi4;		//CQI��RBIR�˲�����֧�ִ�׮
	OM_REQ_ENABLE_ENUM_UINT16   usPtiBiasThd_En;
	UINT16						usPtiBiasThd;		//PTI��ƫ�������
	OM_REQ_ENABLE_ENUM_UINT16   usPtiVarThd_En;
	UINT16						usPtiVarThd;		//PTI�ķ��������
	OM_REQ_ENABLE_ENUM_UINT16   usPmi1Alpha_En;
	UINT16						usPmi1Alpha;		//����PTIʱ��FirstPMI���˲����ӿ�������
	OM_REQ_ENABLE_ENUM_UINT16   ucPmi1Pmi2AlgSel_En;
	UINT8						ucPmi1Pmi2AlgSel;	//TM9��8CSIRSPort��4�㣬W1��W2����ѡ���Ƿֿ�ѡ֧������,0--�ֿ�ѡ��1--����ѡ��
	UINT8						aucRsv;
	OM_REQ_ENABLE_ENUM_UINT16   ucPmi1_En;
	UINT8						ucPmi1;				//First PMI���˲����ӿ��Դ�׮
	UINT8						aucRsv1[3];
}LPHY_REQ_CQI_CFG_PMI_SEL_STRU;

typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	OM_REQ_ENABLE_ENUM_UINT16	ulLimitRbir_En;
	UINT32						ulLimitRbir[4];							//���ݻ���Ϣ����RIʱÿ��RI�Ļ���Ϣ�޷�ֵ
	UINT8						aucRsv0[2];
	OM_REQ_ENABLE_ENUM_UINT16	aul_Cqi_BbpReg_CHx_RI_R234_FACTOR_En;
	UINT32						aul_Cqi_BbpReg_CHx_RI_R234_FACTOR[3];	//����������RIFactor�����׻����������˼�����,Cqi_BbpReg_CHx_RI_Rx_FACTOR
	UINT32						aul_Cqi_BbpReg_CHx_RI_R234_WHITEN_FACTOR[3];
	OM_REQ_ENABLE_ENUM_UINT16	sRiThreshold_En;
	INT16						sRiThreshold;							//RI����ѡ��ʱ����ЧSNR����,gstCqi_AlgPara.sRiThreshold
	OM_REQ_ENABLE_ENUM_UINT16	ucRi_En;
	UINT8						ucRi;									//����õ���RI���Դ�׮
	UINT8						ucPti;
	//ͳ��RI�Ĵ����ʹ����ж�����
		/*�㷨�������������*/
	//����Trms������ԡ��׻�������ģʽ��˫��ģʽ���е���RI���޵��������ӿ�������,Cqi_BbpReg_CHx_RI_Rx_FACTOR
		/*nv��ʵ��*/
}LPHY_REQ_CQI_CFG_RI_STRU;

typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	UINT8						aucRsv[2];
}LPHY_REQ_CQI_DISP_EN_STRU;

typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_RI_CQI_PMI_APERI_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_RI_CQI_PMI_PERI_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_ESINR_PCC_H0_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_ESINR_PCC_H1_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_ESINR_SCC1_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_ESINR_SCC2_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_ESINR_SCC3_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_TSINR_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_RBIR_PCC_H0_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_RBIR_PCC_H1_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_RBIR_SCC1_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_RBIR_SCC2_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_RBIR_SCC3_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_PERIOD_LEN_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_RB_WHITEN_FLAG_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_RI_PERCENT_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_SB_PMI_PERCENT_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_PMI_PERCENT_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_SB_CQI_PERCENT_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_CQI_PERCENT_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_WB_CQI_MEDIAN_STRU;
typedef LPHY_REQ_CQI_DISP_EN_STRU	LPHY_REQ_CQI_DISP_PA_PC_DELTAOFSET_STRU;

/************************************************************
                           2. SG ���ݽṹ����, �㷨��Ҫ��ͼ��
************************************************************/
//OM_Report(OM_REPORT_LEVEL_INFO, OM_DEFAULT_SESSION_ID, LPHY_SG_CQI_DISP_RI_CQI_PMI,(UINT8*)&stRiCqiPmi, sizeof(LPHY_SG_CQI_DISP_RI_CQI_PMI_STRU));
typedef enum
{
    LPHY_SG_CQI_RESERVED            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_SG, 0x0),//0x30530000
	LPHY_SG_CQI_DISP_RI_CQI_PMI_APERI	,	//��Э��涨������һ��
	LPHY_SG_CQI_DISP_RI_CQI_PMI_PERI	,	//��Э��涨������һ��
	LPHY_SG_CQI_DISP_ESINR_PCC_H0		,	//ÿ����������ϱ�
	LPHY_SG_CQI_DISP_ESINR_PCC_H1		,	//ÿ����������ϱ�
	LPHY_SG_CQI_DISP_ESINR_SCC1			,	//ÿ����������ϱ�
	LPHY_SG_CQI_DISP_ESINR_SCC2			,	//ÿ����������ϱ�
	LPHY_SG_CQI_DISP_ESINR_SCC3			,	//ÿ����������ϱ�
	LPHY_SG_CQI_DISP_WB_TSINR			,	//���cqi��Ŀ���Ÿ����,ÿ����������ϱ�
	LPHY_SG_CQI_DISP_WB_RBIR_PCC_H0		,	//���cqi��RBIR,ÿ����������ϱ�
	LPHY_SG_CQI_DISP_WB_RBIR_PCC_H1 	,	//���cqi��RBIR,ÿ����������ϱ�
	LPHY_SG_CQI_DISP_WB_RBIR_SCC1	 	,	//���cqi��RBIR,ÿ����������ϱ�
	LPHY_SG_CQI_DISP_WB_RBIR_SCC2		,	//���cqi��RBIR,ÿ����������ϱ�
	LPHY_SG_CQI_DISP_WB_RBIR_SCC3		,	//���cqi��RBIR,ÿ����������ϱ�
	LPHY_SG_CQI_DISP_PERIOD_LEN         ,   //���cqi���Ӵ�cqi�ϱ�����,ÿ����������ϱ�
	LPHY_SG_CQI_DISP_RB_WHITEN_FLAG		,	//RB�İ׻�flag,ÿ����������ϱ�
	LPHY_SG_CQI_DISP_RI_PERCENT			,	//RI=1,2,3,4��ͳ�ưٷֱ�,10s�ϱ�1��
	LPHY_SG_CQI_DISP_SB_PMI_PERCENT		,	//�Ӵ�PMI=0~15��ͳ�ưٷֱ�,10s�ϱ�1��
	LPHY_SG_CQI_DISP_WB_PMI_PERCENT		,	//���PMI=0~15��ͳ�ưٷֱ�,10s�ϱ�1��
	LPHY_SG_CQI_DISP_SB_CQI_PERCENT		,	//�Ӵ�CQI0/1=0~15��ͳ�ưٷֱ�,10s�ϱ�1��
	LPHY_SG_CQI_DISP_WB_CQI_PERCENT		,	//���CQI0/1=0~15��ͳ�ưٷֱ�,10s�ϱ�1��
	LPHY_SG_CQI_DISP_WB_CQI_MEDIAN 		,	//���CQI0/1=0~15����λ����10s�ϱ�1��
	LPHY_SG_CQI_DISP_PA_PC_DELTAOFSET		//1s�ϱ�1��
}LPHY_SG_MSGID_CQI_ENUM;
/************************************/
typedef struct
{
	LRRC_LPHY_CQI_MODEA_PERIODIC_ENUM_UINT16	enRptType;
	LPHY_CA_CC_ENUM_UINT16 						enCc;
	UINT8										ucRptReq;	//�ϱ����󣬸�arbiter
	UINT8										ucCellIdx;
	//UINT8                                       ucProcId;	//tm10��process id��tm1-tm9��Ӧ�̶�Ϊ0��
	UINT8										ucHetnet;
	UINT8										ucCellIdx_Trigger;	//ͨ��dci0�����������ϱ���cc��Ӧ��cellindex
	/*********************************************/
	UINT8       ucRi;			//1,2,3,4
	/*********************************************/
	UINT8		ucWcqi0;
	UINT8		ucWcqi1;
	UINT8		ucWpmi;
	UINT8		ucWpmi1;
	UINT8		ucWpmi2;
	UINT8		aucRsv[2];
	/*********************************************/
	UINT8		ucSpmi[13];
	UINT8		ucSpmi2[13];
	UINT8		ucScqi0[13];
	UINT8		ucScqi1[13];
	/*********************************************/
	UINT32		ucMposSbidx[6];	//M�Ӵ�λ��
	UINT8		ucMcqi0;		//M�Ӵ�cqi0
	UINT8		ucMcqi1;		//M�Ӵ�cqi1
	UINT8		ucMpmi;			//M�Ӵ�pmi
	UINT8		ucMpmi2;		//M�Ӵ�pmi2
}CQI_OM_ACQI_RPT_STRU;

typedef struct
{
	CQI_OM_ACQI_RPT_STRU	astCqiOmAcqiRpt[CQI_MAX_CA_NUM+1];//CQI_MAX_CA_NUM = 4
}LPHY_SG_CQI_DISP_RI_CQI_PMI_APERI_STRU;
/************************************/
typedef enum{
	PCQI_RPT_MODE_P10	= 0,
	PCQI_RPT_MODE_P11,
	PCQI_RPT_MODE_P20,
	PCQI_RPT_MODE_P21,
	PCQI_RPT_MODE_BUTT
}CQI_PCQI_RPT_MODE_ENUM;
typedef UINT8  CQI_PCQI_RPT_MODE_ENUM_UINT8;

/************************************/
typedef enum {
	CQI_PUCCH_RPT_TYPE_1 = 0,
	CQI_PUCCH_RPT_TYPE_1A,
	CQI_PUCCH_RPT_TYPE_2,
	CQI_PUCCH_RPT_TYPE_2A,
	CQI_PUCCH_RPT_TYPE_2B,
	CQI_PUCCH_RPT_TYPE_2C,
	CQI_PUCCH_RPT_TYPE_3,
	CQI_PUCCH_RPT_TYPE_4,
	CQI_PUCCH_RPT_TYPE_5,
	CQI_PUCCH_RPT_TYPE_6,
	CQI_PUCCH_RPT_TYPE_BUTT
}CQI_PUCCH_RPT_TYPE_ENUM;
typedef UINT8 CQI_PUCCH_RPT_TYPE_ENUM_UINT8;
/************************************/
typedef struct
{
	UINT8       								ucRptReq;	//�ϱ����󣬸�arbiter
	CQI_PCQI_RPT_MODE_ENUM_UINT8				enPcqiType;
	CQI_PUCCH_RPT_TYPE_ENUM_UINT8 				enRptType;
	UINT8										ucCellIdx;
	LPHY_CA_CC_ENUM_UINT16 						enCc;
	UINT8										ucHetnet;
	/*********************************************/
	UINT8       ucRi;			//��ǰ�������ri--1,2,3,4
	UINT8       ucPti;
	UINT8       ucWcqi0;
	UINT8       ucWcqi1;
	UINT8       ucWpmi;
	UINT8       ucWpmi1;
	UINT8       ucWpmi2;
	UINT8       ucBestSbid;		//BP����õ��Ӵ�
	UINT8       ucScqi0;		//�Ӵ�Cqi
	UINT8       ucScqi1;		//�Ӵ�Cqi
	UINT8       ucSpmi2;
	UINT8		aucRsv[2];
	/*********************************************/
	UINT8       aucWpmi1[4];	//����Pmi1
}CQI_OM_PCQI_RPT_STRU;
typedef struct
{
	CQI_OM_PCQI_RPT_STRU	astCqiOmPcqiRpt[CQI_MAX_CA_NUM+1];//CQI_MAX_CA_NUM = 4
}LPHY_SG_CQI_DISP_RI_CQI_PMI_PERI_STRU;
/************************************/
typedef struct
{
	LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];

	INT16					sAmodRank1WbEsinr;
	INT16					sAmodRank2WbEsinr[2];
	INT16					sAmodRank3WbEsinr[2];
	INT16					sAmodRank4WbEsinr[2];

	INT16					sAmodRank1SbEsinr[13];
	INT16					sAmodRank2SbEsinr[26];
	INT16					sAmodRank3SbEsinr[26];
	INT16					sAmodRank4SbEsinr[26];

	INT16					sPmodRank1WbEsinr;
	INT16					sPmodRank2WbEsinr[2];
	INT16					sPmodRank3WbEsinr[2];
	INT16					sPmodRank4WbEsinr[2];

	INT16					sPmodBp0Esinr[2];
	INT16					sPmodBp1Esinr[2];
	INT16					sPmodBp2Esinr[2];
	INT16					sPmodBp3Esinr[2];
	INT16					asRsv[1];

}LPHY_SG_CQI_DISP_ESINR_STRU;//CQI_OM_CQI_ESINR_STRU;
/************************************/
typedef struct
{
	LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
	INT16					sWbTsinrR1[15];
	INT16					sWbTsinrR2[15];
	INT16					sWbTsinrR3[15];
	INT16					sWbTsinrR4[15];
}CQI_OM_WB_TSINR_STRU;

typedef struct
{
	CQI_OM_WB_TSINR_STRU	astCqiOmTsinr[CQI_MAX_CA_NUM+1];
	UINT8						aucRsv[2];
}LPHY_SG_CQI_DISP_WB_TSINR_STRU;
/************************************/
typedef struct
{
	UINT32	ulR1RbirSum;
	UINT32	ulR2RbirSum;
	UINT32	ulR3RbirSum;
	UINT32	ulR4RbirSum;
}LPHY_SG_CQI_DISP_WB_RBIR_STRU;
/************************************/
typedef struct
{
	UINT16					usNpd[CQI_MAX_CA_NUM+1];			//��hetnet0/hetnet1
	UINT16					usMri[CQI_MAX_CA_NUM+1];			//��hetnet0/hetnet1
	UINT16	                usH[CQI_MAX_CA_NUM+1];			//��hetnet0/hetnet1;
	UINT16	                usH1[CQI_MAX_CA_NUM+1];			//��hetnet0/hetnet1;
	UINT16                  usWblen[CQI_MAX_CA_NUM+1];			//��hetnet0/hetnet1;
	UINT16                  usSblen[CQI_MAX_CA_NUM+1];			//��hetnet0/hetnet1;
	UINT16                  usRilen[CQI_MAX_CA_NUM+1];			//��hetnet0/hetnet1;
} LPHY_SG_CQI_DISP_PERIOD_LEN_STRU;

/************************************/

typedef struct
{
	LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
	UINT32					ulRbWhitenFlag[5];	//CC0_SHIFT_WHTN_FLG0��ʼ�ļĴ���
}CQI_OM_RB_WHITEN_STRU;
typedef struct
{
	CQI_OM_RB_WHITEN_STRU	astCqiOmRbWhitenFlag[CQI_MAX_CA_NUM+1];
}LPHY_SG_CQI_DISP_RB_WHITEN_FLAG_STRU;
/************************************/
typedef struct
{
	UINT32	aulPercent[CQI_MAX_CA_NUM+1];
}LPHY_SG_CQI_DISP_RI_PERCENT_STRU;
/************************************/
typedef struct
{
    LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
}LPHY_SG_CQI_DISP_SB_PMI_PERCENT_STRU;
/************************************/
typedef struct
{
    LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
}LPHY_SG_CQI_DISP_WB_PMI_PERCENT_STRU;
/************************************/
typedef struct
{
    LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
}LPHY_SG_CQI_DISP_SB_CQI_PERCENT_STRU;
/************************************/
typedef struct
{
    LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
}LPHY_SG_CQI_DISP_WB_CQI_PERCENT_STRU;
/************************************/
typedef struct
{
    LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
}LPHY_SG_CQI_DISP_WB_CQI_MEDIAN_STRU;
/************************************/
typedef struct
{
    LPHY_CA_CC_ENUM_UINT16 	enCc;
	UINT8					ucHetnet;
	UINT8					aucRsv[1];
}LPHY_SG_CQI_DISP_PA_PC_DELTAOFSET_STRU;
/************************************/


/************************************************************
                           3. CNF���ݽṹ����
************************************************************/
typedef enum __LPHY_CNF_MSGID_CQI__
{
    LPHY_CNF_CQI_RESERVED            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_CNF, 0x0),
}LPHY_CNF_MSGID_CQI_ENUM;


/************************************************************
                           4. Ind���ݽṹ����
************************************************************/
typedef enum __LPHY_IND_MSGID_CQI__
{
    LPHY_IND_CQI_RESERVED            = OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_IND, 0x0),
}LPHY_IND_MSGID_CQI_ENUM;

/************************************************************
                           5. TRACE���ݽṹ����
************************************************************/
typedef enum __LPHY_TRACE_CQI__
{
    LPHY_TRACE_CQI_RESERVED         =  OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_CQI_TRACE_BINARY,
    LPHY_TRACE_CQI_CONFIG,
    LPHY_TRACE_CQI_INVALID_PARA
}LPHY_TRACE_CQI_ENUM;

typedef struct __LPHY_TRACE_CQI_INVALID_PARA_STRU__
{
    INT32       lErrNo;             /*��ʾ������Ч��*/
}LPHY_TRACE_CQI_INVALID_PARA_STRU;

/************************************************************
                           6. Error���ݽṹ����
************************************************************/
typedef enum __LPHY_ERROR_CQI__
{
    LPHY_ERROR_CQI_RESERVED         =  OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_ERROR, 0x0),
    LPHY_ERROR_CQI_STAT
}LPHY_ERROR_CQI_ENUM;

/************************************************************
                           7. DT·�����ݽṹ����
************************************************************/
	typedef enum __LPHY_DT_MSGID_CQI__
	{
		LPHY_DT_CQI_RESERVED			= OM_CMD_ID(LPHY_CQI_MID, OM_TYPE_DT, 0x0),

	}LPHY_DT_MSGID_CQI_ENUM;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CQI_OM_DEF_H__ */
