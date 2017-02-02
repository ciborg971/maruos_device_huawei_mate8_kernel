/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : tds_timing_om_def.h
  �� �� ��   : ����
  ��    ��   : xuyoujiang
  ��������   : 2012��10��16��
  ����޸�   :
  ��������   : om�����ļ�
  �����б�   :
  �޸���ʷ   :

******************************************************************************/
#ifndef __TDS_TIMING_OM_DEF_H__
#define __TDS_TIMING_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* __cplusplus */

#include "om_base_def.h"

/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
enum __TDS_REQ_TIMING__
{
    TDS_REQ_TIMING_REPORT_TRACE_ENA                = OM_TCMD_ID(TPHY_TIMING_MID, OM_TYPE_REQ, 0x1),
    TDS_REQ_TIMING_REPORT_SG_ENA,
    TDS_REQ_TIMING_REPORT_DATA_ENA,
    TDS_REQ_TIMING_TREND_EST_ENA

};
typedef enum
{
    TIMING_OM_SWITCH_OFF = 0,
    TIMING_OM_SWITCH_ON
}TDS_TIMING_OM_SWITCH_ENUM;
typedef UINT16 TDS_TIMING_OM_SWITCH_ENUM_UINT16;

/*��ʱ���� trace�ϱ�ʹ��*/
typedef struct
{
   TDS_TIMING_OM_SWITCH_ENUM_UINT16    enTimingReportTraceEn;
}TDS_REQ_TIMING_REPORT_TRACE_ENA_STRU;

/*��ʱ���� sg�ϱ�ʹ��*/
typedef struct
{
   TDS_TIMING_OM_SWITCH_ENUM_UINT16    enTimingReportSgEn;
}TDS_REQ_TIMING_REPORT_SG_ENA_STRU;

/*��ʱ���� DATA�ϱ�ʹ��*/
typedef struct
{
   TDS_TIMING_OM_SWITCH_ENUM_UINT16    enTimingReportDataEn;
}TDS_REQ_TIMING_REPORT_DATA_ENA_STRU;

/*��ʱ���� debug�ϱ�ʹ��*/
typedef struct
{
   TDS_TIMING_OM_SWITCH_ENUM_UINT16    enTimingTrendEstEn;
}TDS_REQ_TIMING_TREND_EST_ENA_STRU;

/*����Ԥͬ�� trace�ϱ�ʹ��*/
typedef struct
{
   TDS_TIMING_OM_SWITCH_ENUM_UINT16    enTimingIdlFstTraceEn;
}TDS_REQ_TIMING_IDL_FST_TRACE_ENA_STRU;

/*����Ԥͬ�� debug�ϱ�ʹ��*/
typedef struct
{
   TDS_TIMING_OM_SWITCH_ENUM_UINT16    enTimingIdlFstDebugEn;
}TDS_REQ_TIMING_IDL_FST_DEBUG_ENA_STRU;
/*
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16                      usChipEst;
}TDS_REQ_TIMING_CHIP_EST_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEna;
    UINT16                      usAdjustPeriod;
}TDS_REQ_TIMING_ADJUST_PERIOD_ENA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM enCfgHarqSwitchEna;
}TDS_REQ_TIMING_CFG_HARQ_SWITCH_ENA_STRU;
*/

/************************************************************
                           2. CNF���ݽṹ����
************************************************************/
enum __TDS_CNF_TIMING__
{
    TDS_CNF_TIMING_CFG_HARQ_SWITCH_ENA          = OM_CMD_ID(TPHY_TIMING_MID, OM_TYPE_CNF, 0x1),

};

/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
typedef enum __TDS_TRACE_TIMING_ENUM__
{
    TDS_TRACE_TIMING_IDLE_FAST_SYNC                              = OM_TCMD_ID(TPHY_TIMING_MID, OM_TYPE_TRACE, 0x1),
    TDS_TRACE_TIMING_CAL_PAR,                               //����PAR
    TDS_TRACE_TIMING_TREND_ESTIMATE,                        //������
    TDS_TRACE_TIMING_CHIP_ESTIMATE,                         //chip������
    TDS_TRACE_TIMING_UNCHIP_ESTIMATE,                       //unchip������
    TDS_TRACE_TIMING_OFFSET_ADJUST,
    TDS_TRACE_TIMING_CS_UNCHIP_DWPTS,                       //С������chip�����¶�ʱdwptsʱ������
    TDS_TRACE_TIMING_CS_UNCHIP_PARA,                        //С������chip�����¶�ʱ�м���
    TDS_TRACE_TIMING_PDP_MODULE,
    TDS_TRACE_TIMING_IDLE_FAST_SYNC1,
    TDS_TRACE_TIMING_IDLE_FAST_SYNC2,
    TDS_TRACE_TIMING_IDLE_FAST_SYNC3,
    TDS_TRACE_TIMING_IDLE_FAST_SYNC4,
    TDS_TRACE_TIMING_JD_4X_PWR,
    TDS_TRACE_TIMING_DWPTS_1X_CHE,                         
    TDS_TRACE_TIMING_MID_1X_CHE,                         
    TDS_TRACE_TIMING_DWPTS_1X_FIR,   
    TDS_TRACE_TIMING_MID_1X_FIR,
    TDS_TRACE_TIMING_JD_1X_PWR,
    TDS_TRACE_TIMING_IDLE_CELL,
}TDS_TRACE_TIMING_ENUM;
typedef UINT16 TDS_TRACE_TIMING_ENUM_UINT16;
typedef struct
{
    INT32 lChannelPulsePwr[128];                 //  128�㾶����
}TDS_TRACE_TIMING_PDP_MODULE_STRU;
typedef struct
{
    UINT16 usAdjustCnt;	                         //��ʱ������������
    UINT16 usAdjustPeriod;	                     //��������
    UINT16 usTdsCurState;                        //��ǰ״̬
    UINT16 usSubFrmNum;                           /*��֡��*/
    UINT16 usTdsSlotNum;                         //��ǰʱ϶��
    UINT16 usMsn;                                 /*Ŀ���ŵ������λ��*/
    UINT16 usSF;                                  /*��Ƶ����*/
    INT16  sPAR;
    INT32  lElevenPathPwr[11];                    //����ǰ����干ʮһ������
}TDS_TRACE_TIMING_CAL_PAR_STRU;

typedef struct
{
    UINT16 usTdsCurSumFrm;                  //IDLE̬��ǰ��֡��
    UINT16 usTdsPreSumFrm;                  //IDLE̬��һ��֡��
    UINT16 usPichSlotNum;                   //IDLE̬PICHʱ϶��
    UINT16 usPchSlotNum;                    //IDLE̬PCHʱ϶��
    UINT16 usPichChnFlag;                   //IDLE̬PICH�ŵ���ʶ
    UINT16 usPchChnFlag;                    //IDLE̬PCH�ŵ���ʶ
    UINT16 usForceAwakeFlag;                //ǿ�ƻ��ѱ�ʶ
    UINT16 usTdsTaskRfokFlag;               //RF������ɱ�ʶ
    INT16  sCellID;                         //С��ID
    INT16  sDwptsFirstPath;
    UINT16 usSyncActiveFlag;                //ͬ�������ʶ
    INT16  sJdFirstPath;                  //����1x�׾�
    INT32  lJd1xPosMaxPwr;
    INT32  lJd1xNoisePwrSum;                //���������ۺ�
    INT16  sJd4xPosMax;
    INT16  sPosMax;
    INT16  sKLength;
    INT16  sPreFrameOffSet;                 //1/4chip����
}TDS_TRACE_TIMING_IDLE_FAST_SYNC_STRU;
typedef struct
{
    INT32  al4xRfData[1024];
}TDS_TRACE_TIMING_IDLE_FAST_SYNC_STRU1;
typedef struct
{
    INT32  al4xRfData[1024];
}TDS_TRACE_TIMING_IDLE_FAST_SYNC_STRU2;
typedef struct
{
    INT32  al4xRfData[1024];
}TDS_TRACE_TIMING_IDLE_FAST_SYNC_STRU3;
typedef struct
{
    INT32  al4xRfData[1024];
}TDS_TRACE_TIMING_IDLE_FAST_SYNC_STRU4;
typedef struct
{
    INT32  alJd4xPwr[512];
}TDS_TRACE_TIMING_JD_4X_PWR_STRU;
typedef struct
{
    INT16  alDwpts1xChe[256];
}TDS_TRACE_TIMING_DWPTS_1X_CHE_STRU;
typedef struct
{
    INT16  alMid1xChe[256];
}TDS_TRACE_TIMING_MID_1X_CHE_STRU;
typedef struct
{
    INT16  alDwpts1xFir[256];
}TDS_TRACE_TIMING_DWPTS_1X_FIR_STRU;
typedef struct
{
    INT16  alMid1xFir[256];
}TDS_TRACE_TIMING_MID_1X_FIR_STRU;
typedef struct
{
    INT32  alJd1xPwr[16];
}TDS_TRACE_TIMING_JD_1X_PWR_STRU;
typedef struct
{
    INT16 sCellNum;
    INT16 sCellPos;
    INT16 asCellId[6];
}TDS_TRACE_TIMING_IDLE_CELL_STRU;


typedef struct
{
    INT16  asDwptsRf[256];
}TDS_TRACE_TIMING_CS_UNCHIP_DWPTS_STRU;
typedef struct
{
    INT16  sDwptsId;
    INT16  sRshift;
    INT16  sDwptsAdjustCnt;
    INT16  sDwptsPeriod;
    UINT16 usPar;
    INT16  sDwptsSs;
}TDS_TRACE_TIMING_CS_UNCHIP_PARA_STRU;

typedef struct
{
    INT16 sDemoTimeOffset;                       //�����ʱƫ����
    INT16 sADInterOffset;                        //AD������ʱ��������
    INT16 sADFracOffset;                         //AD������ʱС������
    UINT16 usTrendEstAdjustCnt;                 //�����ŵ�������
    UINT16 usTrendEstAdjustPeriod;              //�����ŵ�������
    INT16  sSamplingTimeOffset;
}TDS_TRACE_TIMING_TREND_ESTIMATE_STRU;

typedef struct
{
    INT32 lMeanPAR;                           //�ۺͷ���Ⱦ�ֵ
    INT32 lAlphaPAR;
    INT32 lNoisePowerLimit;                   //������������
    INT32 lLeakingTh;
    INT16 sFirstPath;                           //�׾�
    INT16 sChipEstSs;                           //chip��ƫ����
    INT16 sCurrentAGC;
    INT16  sRes;
    INT32 alChipEstPDPSum[16];
}TDS_TRACE_TIMING_CHIP_ESTIMATE_STRU;

typedef struct
{
    UINT16 usCompensateFlag;                     //unchip��������־
    INT16 sPreUnChipEstSs;                         //unchip��ƫ����ƽ��
    INT16 sFiltUnChipEstSs;                         //unchip��ƫ����ƽ��,�˲���s
    UINT16 usFilterSumCnt;                       //�˲�����
}TDS_TRACE_TIMING_UNCHIP_ESTIMATE_STRU;

/*��ʱ���ٵ�����ʶ�ṹ��*/
typedef struct
{
    INT32  lTimingAdjOffset;
    INT16  sUnChipEstSs;
    INT16  sDemoTimeOffset;
    INT16  sADFracOffset;
    UINT16 usTimingAdjFlag;
    UINT16 usTimingAdjCompleteFlag;
    UINT16 usTimingStateFlag;
    UINT16 usTimingSampleFilterAdjFlag;
    INT16  sTrendEstInvalidFlag;
}TIMING_OFFSET_ADJUST_FLAG;

/************************************************************
                           5. ERROR���ݽṹ����
************************************************************/
typedef enum __TDS_ERROR_TIMING_ENUM__
{
    TDS_ERROR_TIMING_INPUT_CHANNEL_ESTIMATE           = OM_TCMD_ID(TPHY_TIMING_MID, OM_TYPE_ERROR, 0x1),
    TDS_ERROR_TIMING_CHIP_ESTIMATE_RESULT,
    TDS_ERROR_TIMING_UNCHIP_ESTIMATE_RESULT,
    TDS_ERROR_TIMING_SAMPLING_TREND_ESTIMATE_RESULT,
    TDS_ERROR_TIMING_PARA_RANGE                                         //������Χ
}TDS_ERROR_TIMING_ENUM;
typedef UINT16 TDS_ERROR_TIMING_ENUM_UINT16;

typedef struct __TDS_TIMING_CB_NUM_ZERO_OM_ERROR__
{
    UINT16 usSysFn;
    UINT16 usSubFn;
    UINT16 usCplus;
    UINT16 usCminus;
}TDS_ERROR_TIMING_CB_NUM_ZERO_STRU;

/************************************************************
                           6. DEBUG���ݽṹ����
************************************************************/
#define     OM_TIMING_MAX_CFG_REG_IMG_LEN       ((0xA0 - 0x20) / 4 + 1)       /*Turbo���õ����ݳ���, DW, ע����Ҫ��Ӳ���ӿ�ͬ��*/

typedef enum __TDS_DEBUG_TIMING_ENUM__
{
    TDS_DEBUG_TIMING_IDLE_FAST_SYNC                   = OM_TCMD_ID(TPHY_TIMING_MID, OM_TYPE_DEBUG, 0x1),
    TDS_DEBUG_TIMING_TREND_ESTIMATE,                        //������
    TDS_DEBUG_TIMING_PDP_MODULE,                            //PDPģ��
    TDS_DEBUG_TIMING_CAL_PAR,                               //����PAR
    TDS_DEBUG_TIMING_INTER_MODULE,                          //��ֵ����ģ��
    TDS_DEBUG_TIMING_INTER_COMP_MODULE,                     //��ֵ���ܱȽ�ģ��
    TDS_DEBUG_TIMING_CHIP_ESTIMATE,                         //CHIP������
    TDS_DEBUG_TIMING_UNCHIP_ESTIMATE,                       //unchip������

}TDS_DEBUG_TIMING_ENUM;
typedef UINT16 TDS_DEBUG_TIMING_ENUM_UINT16;


typedef struct __TDS_DEBUG_TIMING_CFG_PARA__
{
    INT32 alDwPTSChannelPulsePwr[128];
    INT32 alIdleDwPTSChEst[128];
    INT32 alIdleMidambleChEst[128];
}TDS_DEBUG_TIMING_IDLE_FAST_SYNC_STRU;

typedef struct
{
    INT16 asChInter[256];                       //�ŵ����Ʋ�ֵ����
    INT32 alInterPwr[128];                      //�����Ų�ֵ�����ۺ�����
    INT32 alChEstSum[256];
    INT32 alChInterSum[256];
    INT32 alChEstPwrSum[128];
    INT32 alInterPwrSum[128];
    INT32 lMpyRealImagAdd;
    INT32 lAddRealImag;
    INT32 lMaxChannelPulsePwr;                  //���ֵ����
    INT16 sTEDIntegraph;                        //�����Ż�����
    INT16  sReserved;
}TDS_DEBUG_TIMING_TREND_ESTIMATE_STRU;

typedef struct
{
    INT32 lChannelPulsePwr[128];                 //  128�㾶����
    INT32 lMaxChannelPulsePwr;
    INT32 lPAR;                                  //�����
    INT16 *pInChannelEst;                        //�����ŵ����ƽ��
    INT16 sRShift;                               //������
}TDS_DEBUG_TIMING_PDP_MODULE_STRU;

typedef struct
{
    INT16 sPosMax;
    INT16 sReserved;
    INT32 lNoisePwr;                             //�ۺ���������
    INT32 lMaxNoisePwr;                          //�����������
    INT32 lPAR;
    INT32 lElevenPathPwr[11];                    //����ǰ����干ʮһ������
    INT32 alChEstMidamble[128];
}TDS_DEBUG_TIMING_CAL_PAR_STRU;

typedef struct
{
//    INT32 lThreePathOutInter[96];               //ǰ������ֵ���飬��Ҫ��ʼ��
//    INT32 lTwoPathOutInter[96];                 //ǰ������ֵ����
    INT32 lThreePathOutInterPwrSum[96];         //ǰ������ֵ�����ۺ�����
    INT32 lTwoPathOutInterPwrSum[96];           //ǰ������ֵ�����ۺ�����
}TDS_DEBUG_TIMING_INTER_MODULE_STRU;

typedef struct
{
    INT32 sChipEstPDPSum[19];                   //chip�������ۺ�PDP
    INT32 sOutInterPower[96];                   //32���ٲ�ֵ��������
    UINT16 usCompensateFlag;                     //��ʱ������Ч��ʶ
    INT16  sReserved;
}TDS_DEBUG_TIMING_INTER_COMP_MODULE_STRU;

typedef struct
{
    INT16 sPosMax;
    INT16 sFirstPath;                           //�׾�
    INT16 sFirstPathSuccFlag;                    //�׾������ɹ���ʶ
    UINT16  usFPNoiseFactor;                    //�׾����������о�����
    INT32 lNoisePowerLimit;                     //������������
    INT32 lPosMaxPwr;

}TDS_DEBUG_TIMING_CHIP_ESTIMATE_STRU;

typedef struct
{
    INT32 lPosMaxPwr;
    INT16 sPosMax;
    INT16 sUnChipEstSs;                         //unchip��ƫ����ƽ��
    UINT16 usFilterSumCnt;								 //unchip�������˲��ۺͼ���
    UINT16 usRes;
}TDS_DEBUG_TIMING_UNCHIP_ESTIMATE_STRU;

/* ȫ�ֱ�������*/

extern TDS_REQ_TIMING_REPORT_TRACE_ENA_STRU          gstReqTimingReportTraceEna;
extern TDS_REQ_TIMING_REPORT_DATA_ENA_STRU           gstReqTimingReportDataEna;
extern TDS_REQ_TIMING_REPORT_SG_ENA_STRU             gstReqTimingReportSgEna;
extern TDS_REQ_TIMING_TREND_EST_ENA_STRU             gstReqTimingTrendEstEna;
extern TDS_REQ_TIMING_IDL_FST_TRACE_ENA_STRU         gstReqTimingIdlFstTraceEna;
extern TDS_REQ_TIMING_IDL_FST_DEBUG_ENA_STRU         gstReqTimingIdlFstDebugEna;

/*trace�ṹ��*/
extern TDS_TRACE_TIMING_TREND_ESTIMATE_STRU          gstTdsTraceTimingTrendEstimate;
extern TDS_TRACE_TIMING_CHIP_ESTIMATE_STRU           gstTdsTraceTimingChipEstimate;
extern TDS_TRACE_TIMING_UNCHIP_ESTIMATE_STRU         gstTdsTraceTimingUnchipEstimate;
//extern TDS_TRACE_TIMING_IDLE_FAST_SYNC_STRU          gstTdsTraceTimingIdleFastSync;
extern TDS_TRACE_TIMING_CS_UNCHIP_PARA_STRU          gstTdsTraceTimingCsUnchip;
extern TDS_TRACE_TIMING_CAL_PAR_STRU                 gstTdsTraceTimingCalPar;

extern void TDS_TIMING_OmReq(UINT32 ulMsgId, UINT32 ulSessionId, void* pstMsg, UINT32 ulMsgSize);
#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif /* __cplusplus */


#endif /* __TIMING_OM_H__ */
