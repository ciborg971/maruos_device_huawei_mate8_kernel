/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

******************************************************************************
 �� �� ��   : tds_afc_om_def.h
 �� �� ��   : ����
 ��    ��   : xuyoujiang
 ��������   : 2012��12��29��
 ����޸�   :
 ��������   : TDS AFC om�Ķ����ļ�
 �����б�   :
 �޸���ʷ   :
 1.��    ��   : 2012��12��29��
   ��    ��   : xuyoujiang
   �޸�����   : �����ļ�
   
******************************************************************************/
#ifndef __TDS_AFC_OM_DEF_H__
#define __TDS_AFC_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/
#include "om_base_def.h"

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
{//TBD,LPHY?
    TDS_REQ_AFC_REPORT_TRACE_ENA   = OM_TCMD_ID(TPHY_AFC_MID, OM_TYPE_REQ, 0x1),
    TDS_REQ_AFC_REPORT_SG_ENA,
    TDS_REQ_AFC_REPORT_DATA_ENA,
    TDS_REQ_AFC_RF_STUB_ENA,
    TDS_REQ_AFC_INTER_LOOP_ENA,
    TDS_REQ_AFC_OUT_LOOP_ENA,
    TDS_REQ_AFC_CFG_PARA_ENA
}TDS_REQ_AFC_ENUM;

typedef enum
{
    TDS_AFC_OM_SWITCH_OFF = 0,
    TDS_AFC_OM_SWITCH_ON
}TDS_AFC_OM_SWITCH_ENUM;
typedef UINT16 TDS_AFC_OM_SWITCH_ENUM_UINT16;

/*AFC trace�ϱ�ʹ��*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcReportTraceEn;
}TDS_REQ_AFC_REPORT_TRACE_ENA_STRU;

/*AFC sg��ͼ�ϱ�ʹ��*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcReportSgEn;
}TDS_REQ_AFC_REPORT_SG_ENA_STRU;

/*AFC debug�ϱ�ʹ��*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcReportDataEn;
}TDS_REQ_AFC_REPORT_DATA_ENA_STRU;

/*AFC �ڻ�����ʹ��*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcInterLoopEn;
}TDS_REQ_AFC_INTER_LOOP_ENA_STRU;

/*AFC �⻷����ʹ��*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcOutLoopEn;
}TDS_REQ_AFC_OUT_LOOP_ENA_STRU;

/*AFC��Ƶ������׮�ϱ�ʹ��*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcRFStubEn;
   UINT16 usFrqOffset;
}TDS_REQ_AFC_RF_STUB_ENA_STRU;

/*���ò����ϱ�ʹ��*/
typedef struct
{
   TDS_AFC_OM_SWITCH_ENUM    enAfcCfgParaEn;
}TDS_REQ_AFC_CFG_PARA_ENA_STRU;

/************************************************************
                           2. CNF���ݽṹ����
************************************************************/



/************************************************************
                           3. TRACE���ݽṹ����
************************************************************/
typedef enum
{   //TBD LPHY?
    TDS_TRACE_AFC_FRQ_TR_PERIOD       = OM_TCMD_ID(TPHY_AFC_MID, OM_TYPE_TRACE, 0x1),
    TDS_TRACE_AFC_FRQ_CTH_PERIOD,
    TDS_TRACE_AFC_PRE_LOCK_IND_JUDGE,
    TDS_TRACE_AFC_LAST_LOCK_IND_JUDGE,
    TDS_TRACE_AFC_FILTER_MODULE,
    TDS_TRACE_AFC_RF_ADJUST,
    TDS_TRACE_AFC_INPUT_MEMORY,
    TDS_TRACE_TIMAFC_COMMON,
    TDS_TRACE_AFC_PRE_MID,
    TDS_TRACE_AFC_POS_MID,
    TDS_TRACE_AFC_MID_CHE,
    TDS_TRACE_AFC_DWPTS_CHE,
    TDS_TRACE_AFC_RECST,
    TDS_TRACE_AFC_CP_MODULE,
    TDS_TRACE_AFC_MD_MODULE,
    TDS_TRACE_AFC_CELLID_RECST,
    TDS_TRACE_AFC_DWPTS_FIR,
    TDS_TRACE_AFC_DWPTS_CHERESULT,
    TDS_TRACE_AFC_MID_CHE_PWR,
    TDS_TRACE_AFC_MID_DWPTS_PWR,
    TDS_TRACE_AFC_MID_FIR,
    TDS_TRACE_AFC_CP_FREQ_LIST,
    TDS_TRACE_AFC_MD_FREQ_LIST,
    TDS_TRACE_AFC_HIGH_SPEED_PARA,
    TDS_TRACE_AFC_HIGH_SPEED_DATA,
}TDS_TRACE_AFC_ENUM;


/*AFCƵ�ʸ���������������*/
typedef struct
{
    UINT16 usFrqTrAdjPeriod;        //Ƶ�ʸ��ٵ�������
    UINT16 usFreqTrAdjustCnt;       //Ƶ�ʸ������ڼ�����
    UINT16 usMidID;                  //midamble��id;
    INT16  sFrqTrEstOffset;         //Ƶ�ʸ���Ƶƫ���ƽ��
    INT32  lConjMultyISum;          //Ƶ�ʸ��ٸ��˽��I�ź��ۺ�
    INT32  lConjMultyQSum;          //Ƶ�ʸ��ٸ��˽��Q�ź��ۺ�
    UINT16 usTdsCurState;           //��ǰ״̬
    UINT16 usTdsSlotNum;
}TDS_TRACE_AFC_FRQ_TR_PERIOD_STRU;

/*AFC��Ƶƫ����������������*/
typedef struct
{
    UINT16 usSINRAvg;               //��ֵ���������ֵ
    UINT16 usFrqCthAdjPeriod;       //��Ƶƫ�����������
    UINT16 usFreqCthAdjustCnt;      //��Ƶƫ�������ڼ�����
    INT16  sFrqCthEstOffset;        //��Ƶƫ����Ƶƫ���ƽ��
    INT32  lFreqCthIsum;            //��Ƶƫ���񸴳˽��I�ź��ۺ�
    INT32  lFreqCthQsum;            //��Ƶƫ���񸴳˽��Q�ź��ۺ�
    INT16  asUserList[8];           //�����û�����
}TDS_TRACE_AFC_FRQ_CTH_PERIOD_STRU;
typedef struct
{
    UINT16 usSINRAvg;               //��ֵ���������ֵ
    UINT16 usFrqCthAdjPeriod;       //��Ƶƫ�����������
    UINT16 usFreqCthAdjustCnt;      //��Ƶƫ�������ڼ�����
    INT16  sFrqCthEstOffset;        //��Ƶƫ����Ƶƫ���ƽ��
    INT16  sFrqServEstOffset;
    INT16  sFrqNeighEstOffset;
    INT32  lServScaleSum;
    INT32  lFreqCthIsum;            //��Ƶƫ���񸴳˽��I�ź��ۺ�
    INT32  lFreqCthQsum;            //��Ƶƫ���񸴳˽��Q�ź��ۺ�
    UINT16 ausCellIdList[12];
}TDS_TRACE_AFC_CP_MODULE_STRU;
typedef struct
{
    INT32 alCorrRlst[49];
    INT8  acPCoefList[23];
    INT8  cRes;
    INT32 lSFctrISum;
    INT32 lSFctrQSum;
    INT32 lOutAngle;
    INT32 lMidNoise;
    INT32 lDwptsNoise;
    INT16 sFrqCthEstOffset;
    INT16 sFrqServEstOffset;
    INT32 lSFctrISum2;
    INT32 lSFctrQSum2;
    INT32 lOutAngle2;
}TDS_TRACE_AFC_MD_MODULE_STRU;

/*AFCδ�о�ǰ����ʧ��ָʾģ��OM�ϱ�*/
typedef struct
{
    UINT16 usInterLoopStatusFlag;   //�ڻ�״̬��ʶ
    UINT16 usOLLockInd;             //�⻷����ָʾ
    UINT16 usOLUnLockInd;           //�⻷ʧ��ָʾ
    UINT16 usILLockInd;             //�ڻ�����ָʾ
    UINT16 usFrqResultValid;        //Ƶƫ�����Ч��ʶ
    INT16  sUnLockCnt;              //ʧ������
//    UINT16 usReserved;
}TDS_TRACE_AFC_PRE_LOCK_IND_JUDGE_STRU;

/*AFC�о�������ʧ��ָʾģ��OM�ϱ�*/
typedef struct
{
    UINT16 usInterLoopStatusFlag;   //�ڻ�״̬��ʶ
    INT16  sFreqOffsetResult;       //����ڻ������⻷���
    UINT16 usFilterResetFlag;       //�˲�������ָʾ
    INT16  sUnLockCnt;              //ʧ������
    UINT16 usOLLockInd;             //�⻷����ָʾ
    UINT16 usOLUnLockInd;           //�⻷ʧ��ָʾ
    UINT16 usILLockInd;             //�ڻ�����ָʾ
    UINT16 usReserved;
}TDS_TRACE_AFC_LAST_LOCK_IND_JUDGE_STRU;

/*AFC�˲�ģ��OM�ϱ�*/
typedef struct
{
    INT32  lFilterResult;           //�˲����
    INT16  sFilterInitIndex;        //�˲���ʼ����
    INT16  sFilterCnt;              //�˲�����    
    UINT16 usFilterCoefKLow;        //����˲�ϵ��
    UINT16 usReserved;
}TDS_TRACE_AFC_FILTER_MODULE_STRU;

/*AFC��Ƶ����ģ��OM�ϱ�*/
typedef struct
{
    UINT32 ulConvCoefppm;           //��������
    UINT16 usSysFreq;               //��ƵƵ��
    UINT16 usPDMInitial;            //PDM������׼ֵ
    UINT16 usRFFrqOffset;           //��ƵƵ�ʵ�����
    UINT16 usReserved;
}TDS_TRACE_AFC_RF_ADJUST_STRU;
typedef struct
{
    INT16 asChEstMidamble[256];        /*��ȡ�ŵ����ƽ�����붨ʱ����*/
    INT16 asJDRxData[88];             //JD��ֵ����������ϼ�⴫��
//    INT16 asExtendMidamble[308];       //���ҿ���5chip midamble��
}TDS_TRACE_AFC_INPUT_MEMORY_STRU;
typedef struct
{
    UINT16 usSubFrmNum;                           /*��֡��*/
    UINT16 usPreSubFrmNum;                        /*��һ����֡��*/
    UINT16 usAFCSubFrmNum;                        /*AFC��֡��*/
    UINT16 usAFCPreSubFrmNum;                     /*AFC��һ����֡��*/
    UINT16 usK;                                   /*�û���*/
    UINT16 usMsn;                                 /*Ŀ���ŵ������λ��*/
    UINT16 usSF;                                  /*��Ƶ����*/
    UINT16 usTdsSlotNum;                          /*��ǰʱ϶��*/
    INT32 *plFirAddr;                             /*Firʱ������*/
    INT32 lMidNoise;
    INT32 lDwptsNoise;
    INT16 sServScale;
    INT16 sRes;                            /*Firʱ������*/
}TDS_TRACE_TIMAFC_COMMON_STRU;

typedef struct
{
    INT32  alServNeighPow;   /*����������*/
    INT16* psReCst[4];
    UINT16 usCellId;
    INT16  sServNeighSs;
    INT16  sCnt;
    INT16  sRes;
}TDS_AFC_CELLID_RECST_STRU;

typedef struct
{
    INT16 sIndex[3];
    INT16 sRes;
    TDS_AFC_CELLID_RECST_STRU astCellIdReCst[3];
}TDS_TRACE_AFC_CELLID_RECST_STRU;

typedef struct
{
    INT16 asPreMidFir[128];        
}TDS_TRACE_AFC_PRE_MID_STRU;

typedef struct
{
    INT16 asPosMidFir[128];        
}TDS_TRACE_AFC_POS_MID_STRU;

typedef struct
{
    INT16 asMidChEst[12];        
}TDS_TRACE_AFC_MID_CHE_STRU;

typedef struct
{
    INT16 asDwptsChEst[12];        
}TDS_TRACE_AFC_DWPTS_CHE_STRU;

typedef struct
{
    INT32 galReConstructData[192];      
}TDS_TRACE_AFC_RECST_STRU;

typedef struct
{
    INT16 asDwptsFir[256];      
}TDS_TRACE_AFC_DWPTS_FIR_STRU;

typedef struct
{
    INT16 asDwptsChe[256];      
}TDS_TRACE_AFC_DWPTS_CHERESULT_STRU;

typedef struct
{
    INT32 asMidChePwr[6];        
}TDS_TRACE_AFC_MID_CHE_PWR_STRU;

typedef struct
{
    INT32 asDwptsChePwr[6];        
}TDS_TRACE_AFC_MID_DWPTS_PWR_STRU;

typedef struct
{
    INT16 asMidFir[308];      
}TDS_TRACE_AFC_MID_FIR_STRU;

typedef struct
{
    INT16 asCpFreqList[50];      
}TDS_TRACE_AFC_CP_FREQ_LIST_STRU;

typedef struct
{
    INT16 asMdFreqList[50];      
}TDS_TRACE_AFC_MD_FREQ_LIST_STRU;

/************************************************************
                           4. Debug���ݽṹ����
************************************************************/
typedef enum
{
    TDS_DEBUG_AFC_FRQ_TR_PERIOD        = OM_TCMD_ID(TPHY_AFC_MID, OM_TYPE_DEBUG, 0x1),
    TDS_DEBUG_AFC_FRQ_CTH_PERIOD,
    TDS_DEBUG_AFC_PRE_LOCK_IND_JUDGE,
    TDS_DEBUG_AFC_LAST_LOCK_IND_JUDGE
}TDS_DEBUG_AFC_ENUM;


/*AFCƵ�ʸ���������������*/
typedef struct
{
    INT16  asOmJDRxData[88];        //���ϼ��JD��ֵ��������
    UINT16 usSINRThresh0;           //������ȱ�������0��
    INT16  sFrqTrRShift;            //Ƶ�ʸ��ٸ��˽����������Ĭ��Ϊ2;
    UINT16 usFrqTrConvFactor;       //Ƶ�ʸ���Ƶƫ�������ӣ�
}TDS_DEBUG_AFC_FRQ_TR_PERIOD_STRU;

/*AFC��Ƶƫ����������������*/
typedef struct
{
    INT32  alExtendMidamble[154];   //�ŵ�����ʱ���ź�
    INT32  alChEstMidamble[128];    //�ŵ�����������
    INT16  asPluralMidSeqIQ[288];
    INT16  asUserList[8];           //�����û�����
    INT16  sMultiPathNum;           //�ྶ����
    UINT16 usMainPathDelay;         //����ƫ�ƣ�
    UINT16 usFrqCthConvFactor;      //��Ƶƫ����Ƶƫ�������ӣ�
    UINT16 usMultPathCompensate;    //�ྶ��������
    UINT16 usFOLimit;               //Ƶƫ�����޷�ֵ��
}TDS_DEBUG_AFC_FRQ_CTH_PERIOD_STRU;

/*AFCδ�о�ǰ����ʧ��ָʾģ��OM�ϱ�*/
typedef struct
{
    INT16  asFreqTrResList[127];    //Ƶ�ʸ��ټ�Ƶ�����
    INT16  asFreqCthResList[127];   //��Ƶƫ�����Ƶ�����
    INT16  sFrqTrSlipWinCnt;        //Ƶ�ʸ��ٻ�������
    INT16  sFrqCthSlipWinCnt;      //��Ƶƫ���񻬴�����
//    UINT16 usReserved;
}TDS_DEBUG_AFC_PRE_LOCK_IND_JUDGE_STRU;

/*AFC�о�������ʧ��ָʾģ��OM�ϱ�*/
typedef struct
{
    INT16  asFreqTrResList[127];    //Ƶ�ʸ��ټ�Ƶ�����
    INT16  asFreqCthResList[127];   //��Ƶƫ�����Ƶ�����
    INT16  sFrqTrSlipWinCnt;        //Ƶ�ʸ��ٻ�������
    INT16  sFrqCthSlipWinCnt;      //��Ƶƫ���񻬴�����
//    UINT16 usReserved;
}TDS_DEBUG_AFC_LAST_LOCK_IND_JUDGE_STRU;

//�����������
typedef struct
{
    UINT16 usSfn;
    UINT16 usTempStudyFlag;
    UINT16 usHighSpeedFlag;
    UINT16 usResv;
    TDS_HIGH_SPEED_NV_PARA stNvPara;
} TDS_AFC_OM_HIGH_SPEED_PARA_STRU;



/*AFC om�ϱ��ṹ��*/
extern TDS_TRACE_AFC_FRQ_TR_PERIOD_STRU       gstTraceAFCFrqTr;
extern TDS_TRACE_AFC_FRQ_CTH_PERIOD_STRU      gstTraceAFCFrqCth;
extern TDS_TRACE_AFC_PRE_LOCK_IND_JUDGE_STRU  gstTraceAFCPreLockInd;
extern TDS_TRACE_AFC_LAST_LOCK_IND_JUDGE_STRU gstTraceAFCLastLockInd;
extern TDS_TRACE_AFC_FILTER_MODULE_STRU       gstTraceAFCFilterModule;
extern TDS_TRACE_AFC_RF_ADJUST_STRU           gstTraceAFCRfAdjust;
extern TDS_TRACE_AFC_CP_MODULE_STRU           gstTraceAFCCpModule;
extern TDS_TRACE_AFC_MD_MODULE_STRU           gstTraceAFCMdModule;
extern TDS_REQ_AFC_INTER_LOOP_ENA_STRU        gstReqAfcInterLoopEna;
extern TDS_REQ_AFC_OUT_LOOP_ENA_STRU          gstReqAfcOutLoopEna;

extern void TDS_AFC_OmReq(UINT32 ulMsgId, UINT32 ulSessionId, void* pstMsg, UINT32 ulMsgSize);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __AFC_OM_DEF_H__ */











//
