/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : tds_cqi_om_def.h
  �� �� ��   : ����
  ��    ��   : mah
  ��������   : 2012��11��12��
  ����޸�   :
  ��������   : TDS CQIģ��OM����ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��12��
    ��    ��   : mah
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __TDS_CQI_OM_DEF_H__
#define __TDS_CQI_OM_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "om_base_def.h"

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
#define TDS_MODE_BUTT  2 //added by humin, 2015/05/07
#define TPHY_REQ_SIR_OM_REP_SWITCH    OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_REQ, 0x0)
#define TPHY_REQ_SIR_ALGTH_PARA       OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_REQ, 0x1)
#define TPHY_REQ_SIR_STUB             OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_REQ, 0x2)

#define TPHY_REQ_CQI_OM_REP_SWITCH    OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_REQ, 0x0)
#define TPHY_REQ_CQI_ALGTH_PARA       OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_REQ, 0x1)
#define TPHY_REQ_CQI_STUB             OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_REQ, 0x2)

#define TPHY_REQ_VEL_ALGTH_PARA       OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_REQ, 0x4)
#define TPHY_REQ_VEL_STUB             OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_REQ, 0x5)

/*----------------------------------------------*
 * ö�ٶ���                                *
 *----------------------------------------------*/
typedef enum TDS_SIR_OM_RPT_IND
{
    TPHY_IND_SIR_DPCH    =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x0),
    TPHY_IND_SIR_HSSCCH  =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x1),
    TPHY_IND_SIR_EAGCH   =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x2),
    TPHY_IND_SIR_HSDSCH  =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x3),
    TPHY_IND_SIR_PCCPCH  =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x4),
    TPHY_IND_SIR_SCCPCH  =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x5),
    TPHY_IND_SIR_EHICH   =  OM_TCMD_ID(TPHY_CMU_MID, OM_TYPE_IND, 0x6),
}TDS_SIR_OM_RPT_IND_ENUM;

typedef enum TDS_CQI_OM_RPT_IND
{
    TPHY_IND_VEL_OUT         =  OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_IND, 0x0),
    TPHY_IND_CQI_OUT         =  OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_IND, 0x1),
    TPHY_IND_VEL_PROC_VAR    =  OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_IND, 0x2),
    TPHY_IND_CQI_PROC_VAR    =  OM_TCMD_ID(TPHY_CQI_MID, OM_TYPE_IND, 0x3),
}TDS_CQI_OM_RPT_IND_ENUM;
    
/*----------------------------------------------*
 * �ṹ����                                                    *
 *----------------------------------------------*/
typedef enum TDS_SWITCH_FALG
{
    TDS_DISABLE = 0,
    TDS_ENABLE ,        
}TDS_SWITCH_FALG_ENUM;
#define TDS_SWITCH_FALG_ENUM_UINT16 UINT16

 /*TDS SIR�����㷨��������ṹ����*/
typedef struct TDS_SIR_ALG_PARA
{
    UINT16 usMaxSirSoftSyblNum[TDS_MODE_BUTT];    /*QPSK/16QAM����ʱ��SIRƽ��ʹ�õ���������ֵ���ݳ���*/
    UINT16 usMaxSirCodeNum[TDS_MODE_BUTT];         /*QPSK/16QAM���Ʒ�ʽʱ��SIRƽ��ʹ�õ���������ֵ���ݳ���*/
    UINT16 usMaxSirSlotSmoothNum;      /*SIRƽ��ʱ������ƽ��ʱ϶��Ŀ,ȡֵ1-31*/
    UINT16 usMaxSirSfSmoothNum;        /*SIRƽ��ʱ������ƽ����֡��Ŀ,ȡֵ1-31*/      
}TDS_SIR_ALG_PARA_STRU;

/*TDS SIR �����׮�ṹ�嶨��*/
typedef struct TDS_SIR_STUB
{
    TDS_SWITCH_FALG_ENUM_UINT16 ulSirStubSwitch;     /*SIR��׮���ƿ���*/
	UINT16 usRsvd;
    INT32 lSir;            
}TDS_SIR_STUB_STRU;

 /*TDS �ٶȹ����㷨��������ṹ����*/
typedef struct TDS_VEL_ALG_PARA
{
    UINT16 usVp;        /*�źŹ���ͳ�����ڣ�����֡Ϊ��λ*/
    UINT8 ucVelFadThrd; /*�źŹ���������֡�źŹ�����˥����*/
    UINT8 ucVelAwgnThrd;/*�źŹ���������֡�źŹ�����˥����*/
    UINT8 ucVelPowThrd; /*����˥���ŵ�˥������*/
    UINT8 ucLrThrd;     /*����˥���ŵ�������������*/
    INT8  cVelSirThrd;  /*�ٶȹ��Ƶ�SIR��������*/   /*5*/   
    UINT8 ucMainPthPos; /*��ʱͬ��λ��*/                    /*MainPthPos �㷨��֤ȡֵ2-5��Χ��*/
    UINT16 usVarTh;     /*AWGN�ŵ�Var����*/
    UINT16 usLrTh0;     /*��˥���ŵ�������������*/
    UINT16 usLrTh1;     /*��˥���ŵ�������������*/
    UINT16 usLrTh2;     /*����˥���ŵ�������������*/  /*10*/

}TDS_VEL_ALG_PARA_STRU;

/*TDS  �ٶȹ��� �����׮�ṹ�嶨��*/
typedef struct TDS_VEL_STUB
{
    TDS_SWITCH_FALG_ENUM_UINT16 usVelStubSwitch;     /*�ٶȹ��� ��׮���ƿ���*/
    UINT16 usVar;
    UINT16 usVelStat;
    UINT16 usRsvd;        
}TDS_VEL_STUB_STRU;

/* TDS CQI �����㷨��������ṹ����*/
typedef struct TDS_CQI_NV_PARA
{
    UINT16 usUeCategory;/*UE�������ȼ�*/
    UINT16 usPunRateLimit;/*���޴����*/
}TDS_CQI_NV_PARA_STRU;

typedef struct TDS_CQI_ALG_PARA
{
    TDS_SWITCH_FALG_ENUM_UINT16 usOLASwitch;            /*ŷ�������㷨�Ŀ���                    */          /*0*/     
    UINT16 usOLAAdjStep;                                /*ŷ���㷨TBI��������                   */            
    TDS_SWITCH_FALG_ENUM_UINT16 usVelSwitch;            /*����Ӧ�ŵ������жϿ���                */            
    UINT16 usSirAvrPrd;                                 /*SIRƽ�����ڣ�VelocitySwitch�ر�ʱ��Ч */            
    TDS_SWITCH_FALG_ENUM_UINT16 usDynOLASwitch;         /*��̬ŷ�����أ�VelocitySwitch�ر�ʱ��Ч*/            
    UINT16 usTargetBlerOne;            /*ŷ��������Ŀ��ֵ          */    
    UINT16 usTargetBlerA;              /*ŷ������AWGNĿ��ֵ        */    
    UINT16 usTargetBlerS;              /*ŷ����������˥���ŵ�Ŀ��ֵ*/    
    UINT16 usTargetBlerH1;             /*��˥ŷ������SIR����1Ŀ��ֵ*/    
    UINT16 usTargetBlerH2;             /*��˥ŷ������SIR����2Ŀ��ֵ*/              
    UINT16 usTargetBlerH3;             /*��˥ŷ������SIR����3Ŀ��ֵ*/       /*10*/
    UINT16 usTargetBlerHH1;            /*��˥ŷ������SIR����1Ŀ��ֵ*/
    UINT16 usTargetBlerHH2;            /*��˥ŷ������SIR����2Ŀ��ֵ*/
    UINT16 usTargetBlerHH3;            /*��˥ŷ������SIR����3Ŀ��ֵ*/
    UINT16 usVarTh;                    /*�ٶȹ���Var����           */     
    UINT16 usLrTh0;                    /*��˥���ŵ�������������  */     
    UINT16 usLrTh1;                    /*��˥���ŵ�������������  */     
    UINT16 usLrTh2;                    /*��˥���ŵ�������������  */     
    INT32 lVelSirTh;                   /*�ŵ������о���ЧSIR����*/
    INT32 lCqiAvraFadTH;               /*��˥��SIR��������*/                           
    INT32 lSirRang1;                   /*SIR��������1*/                    /*20*/
    INT32 lSirRang2;                   /*SIR��������2*/
}TDS_CQI_ALG_PARA_STRU;

typedef struct TDS_SIR_OM_RPT_CTRL
{
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirDpchRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirHsscchhRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirEagchRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirHsdschRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirPccpchRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirSccpcbRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsSirEhichRptEbl;
    UINT16 usRsvd;        
}TDS_SIR_OM_REQ_CTRL_STRU;

typedef struct TDS_CQI_OM_RPT_CTRL
{
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsVelRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usTdsCqiRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usVelVarRptEbl;
    TDS_SWITCH_FALG_ENUM_UINT16 usCqiVarRptEbl;
}TDS_CQI_OM_REQ_CTRL_STRU;

typedef struct TDS_SIR_OUT
{
    UINT16 usSbfn;      /*��ǰ��֡��*/
    UINT16 usRsvd;        
    INT32  lSir;        /*��ǰ��֡SIR���*/
}TDS_SIR_OUT_STRU;

/*TDS  CQI �����׮�ṹ�嶨��*/
typedef struct TDS_CQI_STUB
{
    TDS_SWITCH_FALG_ENUM_UINT16 usCqiStubSwitch;     /*CQI ��� ��׮���ƿ���*/
    UINT16 usModuFormat;
    UINT16 usTbiOut;
    UINT16 usRsvd;        
}TDS_CQI_STUB_STRU;

/*�ٶȹ��ƽṹ����*/
typedef struct TDS_VEL_2HALF_MAX
{
    INT16 sMax0;
    INT16 sMin0;
    INT16 sMax1;
    INT16 sMin1;
}TDS_VEL_2HALF_MAX_STRU;

typedef struct TDS_VEL_PROC_VAR
{
    UINT16 usVelTaskFalg; /*Vel�����־����ʱ϶�ж��д�������֤һ����ִ֡��һ��*/
    UINT16 usSfn;         /*��ǰ�ٶȹ��ƴ������ݶ�Ӧ��֡��*/
    UINT16 usAgc;         /*��ǰAGC����*/
    UINT16 usCurVelFrmCnt;/*��ǰ�ٶȹ��ƴ�����������֡������ȡֵ0-127*/
    TDS_VEL_2HALF_MAX_STRU stVelCurPeak;
    INT32 lAccu;           /*�����ۼ�ֵAccu*/    
    INT32 lSirSum;         /*SIR�ۼ�ֵSIRSum*/              
}TDS_VEL_PROC_VAR_STRU;

typedef struct TDS_VEL_OUT
{
    UINT16 usVar;
    UINT16 usLr0;
    UINT16 usLr1;
    UINT16 usLr;
    UINT16 usVelStat;
    UINT16 usTmpVelStat;
}TDS_VEL_OUT_STRU;

/*CQI������̱�������ṹ*/
typedef struct TDS_CQI_PROC_VAR
{
    UINT16 usVelStat;      
    UINT16 usSirIdx;
    UINT16 usCycleFlag;
    UINT16 usSnrAvrPrdRl;
    UINT16 usStaChaged;
    INT16 sCQI_DInitialTx;//16s
    UINT16 usCqiStubFlag;
    UINT16 usNewDataInd;
    UINT16 usCrcResult;
    INT16 sDCqi_InitialTx;
    INT32 lSirHold;
    INT32 lSirSum;
    INT32 lSirMear;
    INT32 lSirAverage;
}TDS_CQI_PROC_VAR_STRU;

typedef struct TDS_CQI_OUT
{
    UINT16 usPuncRate;
    UINT16 usModuFormat;
    UINT16 usTbiOut;
    UINT16 usTbiOrg;
    UINT16 usMaxTbi;
    UINT16 usMinTbi;
    INT16 sOutOlaOffset;
    UINT16 usRsvd;    
}TDS_CQI_OUT_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

