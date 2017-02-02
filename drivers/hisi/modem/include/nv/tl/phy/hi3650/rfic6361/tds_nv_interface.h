/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : tds_nv_interface.h
  �� �� ��   : ����
  ��    ��   : baizhongjin
  ��������   : 2013��3��25��
  ����޸�   :
  ��������   : TDS nv ͷ�ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2013��3��25��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

/******************************************************************************/
#ifndef __TDS_NV_INTERFACE_H__
#define __TDS_NV_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif



//#include "type_define.h"
#include "lt_nv_common_interface.h"
#include "tds_dsp_equip_interface.h"

#define RFIC_VERSION_V210               (210)

#define TDS_RF_SUPPORT_BAND_NUM  	  		 2
#define TDS_MAX_ANT_MIPI_CMD_NUM  	  		 4/*mipi�ӿ����߿����л�ָ���������*/
#define TDS_MAX_PA_MIPI_CMD_NUM  	  		 4/*mipi�ӿ�pa�л�ָ���������*/
#define TDS_MAX_TURNER_MIPI_CMD_NUM  	  	 4/*mipi�ӿ�turner�л�ָ���������*/
#define TDS_MAX_MIPI_INIT_CMD_NUM  	  		 8/*mipi������ʼ����ĸ���*/
#define TDS_TUNER_SUPPORT_SENSOR_NUM  	  	 8
#define TDS_TUNER_DAC_MAX                    6
#define TDS_TUNER_CONTROL_MAX                4
#define TDS_TUNER_CMD_MAX      (TDS_TUNER_DAC_MAX + TDS_TUNER_CONTROL_MAX)
/*ǰ�����NV begin*/
/*���߿���bitmap*/
typedef enum
{
    TDS_ANTSEL_INDEX_RX0    = 0x0000000,
    TDS_ANTSEL_INDEX_RX1    = 0x1000000,
    TDS_ANTSEL_INDEX_TX     = 0x2000000,
    TDS_ANTSEL_INDEX_3      = 0x3000000
}TDS_ANTSEL_INDEX_ENUM;


typedef struct
{
    UINT16 usRxMainLnaSel; //��Ƶ��ͨ��LNAѡ��
    UINT16 usRxDvtyLnaSel;
    UINT16 usTxLnaSel;
    UINT16 usResv;
}TDS_RF_PRIVATE_CHANNEL_CFG_STRU;


typedef struct
{
    UINT32 ulAbb0RstBitMap;
    UINT32 ulAbb0RxAEnBitMap;
    UINT32 ulAbb0RxBEnBitMap;
    UINT32 ulAbb0TxEnBitMap;
    UINT32 ulRxABSwapBitMap;
    UINT32 ulRssiCalBitMap;
    UINT32 ulAdOn1BitMap;

}TDS_ABB_LINECTRL_BITMAP_STRU;


typedef struct
{
    UINT16 usCoreSel;    //����ͨ��Coreѡ��
    UINT16 usDivider;    //����ͨ����Ƶѡ��
    //UINT16 usTxCoreSel;
    //UINT16 usTxDivider;
}TDS_RF_PRIVATE_CORE_DIV_CFG_STRU;
typedef enum
{
    TDS_RF_CH0,
    TDS_RF_CH1,
}TDS_RF_CH_SEL_ENUM;
typedef UINT16 TDS_RF_CH_SEL_ENUM_UINT16;


typedef struct
{
    UINT16 usRfRxOnAdvanceTime;
    UINT16 usRfTxOnAdvanceTime;
    UINT16 usFreqSWAdvanceTime;
    UINT16 usFirRxEnAdvanceTime;
    UINT16 usFirTxEnAdvanceTime;
    UINT16 usMidAdvanceTime;
    UINT16 usABBAdOnAdvanceTime;
    UINT16 usABBDaOnAdvanceTime;
    UINT16 usPaEnAdvanceTime;
    UINT16 usTxEnAdvanceTime;
    UINT16 usAntSelAdvanceTime;
    TDS_RF_CH_SEL_ENUM_UINT16 enChannelSel;
}TDS_NV_RF_ADVANCE_TIME_STU;

typedef struct
{
    UINT32 ulAntSelCfg0;
    UINT32 ulAntSelCfg1;
    UINT32 ulAntSelCfg2;
    UINT32 ulAntSelCfg3;
}TDS_ANTSEL_ALLOT_STRU;

typedef struct
{

    UINT8  aucPaVal[4];/*֧�ֵ�pa��λ������ֵ Ĭ������0 1 2������е�*/
}TDS_PA_LEVEL_STRU;

/* tds mipi begin*/


typedef struct
{
    UINT32                            ucValidflg:1;         /*��ǰָ���Ƿ���Ч*/
    UINT32                            ucExWFlg:1;           /*�Ƿ������չд���ͷ�ʽ,1��*/
    UINT32                            ucWatTime:4;          /*������ȴ�ʱ��*/
    UINT32                            ucSlaveid:4;          /*�豸USID*/
    UINT32                            ucMipiAddr:8;         /*��MIPI�豸�е�ƫ�Ƶ�ַ*/
    UINT32                            ucByteCnt:3;          /*�������չָ�ָ��CNT*/
    UINT32                            usAdvanceTime:11;      /*��ָ����ǰ�ڽ�����������ʱ�� 1/8chip��λ*/
} TDS_NV_MIPI_CMD_CTRL_STRU;

typedef struct
{
    TDS_NV_MIPI_CMD_CTRL_STRU        stMipiCtrl;
    UINT8                            ucCmdByte0;
    UINT8                            ucCmdByte1;
    UINT8                            ucCmdByte2;
    UINT8                            ucCmdByte3;
}TDS_MIPI_CMD_STRU;


typedef struct
{
    UINT16             usAntMipiValidFlg; /*��band�����߿����Ƿ���Ҫmipiָ��֧��*/
    UINT16             usANtMipiCmdNum;
    TDS_MIPI_CMD_STRU  stAntMipiCmd[TDS_MAX_ANT_MIPI_CMD_NUM];
}TDS_ANT_MIPI_CMD_STRU;

/*���߿��ص���ǰ��Ҫ�޶���0-15chips*/
typedef struct
{
    TDS_ANT_MIPI_CMD_STRU stRxMipiCmd;
    TDS_ANT_MIPI_CMD_STRU stTxMipiCmd;
    TDS_ANT_MIPI_CMD_STRU stNotchTxMipiCmd;
}TDS_ANT_ALLOT_MIPI_CMD_STRU;

typedef struct
{
    UINT16             usPaMipiValidFlg; /*��band��pa�Ƿ���Ҫmipiָ��֧��*/
    UINT16             usPaMipiCmdNumPreLevel;/*ÿ��pa��λ��mipiָ����*/
    UINT16             usPaOffNum;
    UINT16             usRes;
    TDS_MIPI_CMD_STRU  stPaHighMipiCmd[TDS_MAX_PA_MIPI_CMD_NUM];
    TDS_MIPI_CMD_STRU  stPaMidMipiCmd[TDS_MAX_PA_MIPI_CMD_NUM];
    TDS_MIPI_CMD_STRU  stPaLowMipiCmd[TDS_MAX_PA_MIPI_CMD_NUM];
    TDS_MIPI_CMD_STRU  stPaOffMipiCmd[TDS_MAX_PA_MIPI_CMD_NUM];
}TDS_PA_MIPI_CMD_STRU;

/*���е�mipi�����ϵ��ʼ��*/
typedef struct
{
    UINT16             usMipiValidFlg; /*��band��pa�Ƿ���Ҫmipiָ��֧��*/
    UINT16             usMipiInitCmdNum;
    TDS_MIPI_CMD_STRU  astMipiInitCmd[TDS_MAX_MIPI_INIT_CMD_NUM];
}TDS_MIPI_INIT_CMD_STRU;

/*�߿���Ч����bitmap����map����Ӳ�����Ӷ�ȷ��*/
typedef struct
{
    TDS_MIPI_INIT_CMD_STRU stMipiInit;
    TDS_ANT_ALLOT_MIPI_CMD_STRU astAntMipiCmd[TDS_RF_SUPPORT_BAND_NUM];
    TDS_PA_MIPI_CMD_STRU astPaMipiCmd[TDS_RF_SUPPORT_BAND_NUM];
}TDS_NV_MIPI_CTRL_STRU;
typedef struct
{
    UINT32 aulCtuPaMaxConfig[8];
    UINT32 ulBandNumSupt;  //֧��band��Ŀ
    UINT32 aulBandList[TDS_RF_SUPPORT_BAND_NUM];     //֧��band�б�
    UINT32 aulPaEnAllot[TDS_RF_SUPPORT_BAND_NUM]; /*pa en ӳ���bitλ��*/
    UINT32 aulPaAtt0Allot[TDS_RF_SUPPORT_BAND_NUM];/*pa att0 ӳ���bitλ��*/
    UINT32 aulPaAtt1Allot[TDS_RF_SUPPORT_BAND_NUM];/*pa att1 ӳ���bitλ��*/
    TDS_PA_LEVEL_STRU astPaVal[TDS_RF_SUPPORT_BAND_NUM];/*��ͬ����䲻ͬ��λ����ֵ*/
    TDS_ANTSEL_ALLOT_STRU astAntSelAllot[TDS_RF_SUPPORT_BAND_NUM];
}TDS_NV_LINECTRL_ALLOT_BY_HARDWARE_STRU;

typedef struct
{
    UINT16      ulRficVersion;    //������̬ ����
    UINT16      ulBandNumSupt;  //֧��band��Ŀ
    UINT16      aulBandList[TDS_RF_SUPPORT_BAND_NUM];     //֧��band�б�
    TDS_RF_PRIVATE_CHANNEL_CFG_STRU  astRfChanCfg[TDS_RF_SUPPORT_BAND_NUM];//��Ƶͨ������
    TDS_RF_PRIVATE_CORE_DIV_CFG_STRU astRfCoreAndDivSel[TDS_RF_SUPPORT_BAND_NUM];
}TDS_NV_RFIC_CFG_STRU;
/*ǰ�����NV end*/


    /* rx tx  nv  start   */
typedef struct
{
    TDS_BAND_COMMON_PARA_STRU astCommon[TDS_RF_SUPPORT_BAND_NUM];
    TDS_BAND_RXPATH_PARA_STRU astRxPara[TDS_RF_SUPPORT_BAND_NUM];
    TDS_BAND_TXPATH_PARA_STRU astTxPara[TDS_RF_SUPPORT_BAND_NUM];
}TDS_NV_RXTX_PARA_STRU;

    /* rx tx nv end   */


 /*MIPIд�����ʽ����
31--29  001  ---->ָ������
28--25  0111 ---->SLAVE ADDRESS
24--22  010  ---->cmd
21--17         ---->addr ����0x1c,0x00��
16                ---->17--24��У��λ
15--8           ---->���õ�����
7                  ---->15---8��У��λ
6--0             ---->����λ
 aulControlCfgPara[i] �谴������BITλȫ��д��
 usDacCmd    15--0���ζ�Ӧ���� 31--16BITλд��
 ausDacData[j][k]15---0���ζ�Ӧ����15--0BITλд��
 */
 #if 0
typedef struct
{
    UINT16 usDacCmd;
    UINT16 usRev;
    UINT16 ausDacData[TDS_RF_SUPPORT_BAND_NUM][TDS_TUNER_SUPPORT_SENSOR_NUM];//BAND˳����BAND�б���ͬ
}TDS_TUNER_DAC_CFG_PARA_STRU;
typedef struct
{
    UINT16 usDacCfgNum;//������ox00�Ĵ�����DACʹ�ܵĸ���һ��
    UINT16 usRev;
    TDS_TUNER_DAC_CFG_PARA_STRU stDacCfgPara[TDS_TUNER_DAC_MAX];
}TDS_TUNER_DAC_CFG_STRU;
 typedef struct
 {
     UINT16 usControlCfgNum;//���ֵΪ4��SLEEP MODE ĿǰĬ������һ��(0x1c)��activeMODE Ĭ������3��
     UINT16 usRev;
     UINT32 aulControlCfgPara[TDS_TUNER_CONTROL_MAX];//����ʱ��0--5�������ã�0-->0x1c, 1-->0x10, 2-->0x0���������η���
 }TDS_TUNER_CONTROL_CFG_STRU;
typedef struct
{
    TDS_TUNER_CONTROL_CFG_STRU stControlCfg;
    TDS_TUNER_DAC_CFG_STRU stDacCfg;
}TDS_TUNER_MIPI_ACTIVE_MODE_CMD_STRU;
typedef struct
{
    TDS_TUNER_CONTROL_CFG_STRU stControlCfg;
}TDS_TUNER_MIPI_SLEEP_MODE_CMD_STRU;
#endif
typedef struct
{
    UINT16             usTurnerMipiValidFlg; /*��band��turner�Ƿ���Ҫmipiָ��֧��*/
    UINT16             usTurnerMipiCmdNum;
    TDS_MIPI_CMD_STRU  astMipiCmd[TDS_MAX_TURNER_MIPI_CMD_NUM];

}TDS_TUNER_MIPI_PARA_STRU;
typedef struct
{
    TDS_TUNER_MIPI_PARA_STRU stTurnerInitCmd;

    TDS_TUNER_MIPI_PARA_STRU astTurnerMipiCmd[TDS_RF_SUPPORT_BAND_NUM];
}TDS_NV_TUNER_PARA_STRU;

typedef struct
{
    UINT16 usTdsDrxIdleEnableFlag;
    UINT16 usTdsDrxSwitch32kTime;
    UINT16 usTdsClkMeasParaIndex;
    UINT16 usTdsPresyncStartGate;
    UINT16 usTdsDrxIdleWaitTaskTime;
    UINT16 usTdsDrxIdleClkMeasStubFlag;
    UINT16 usTdsDrxIdleSleepStubFlag;
    UINT16 usTdsDrxSlaveEnableFlag;
    UINT16 usRsvd[4];
}TDS_NV_DRX_PARA_STRU;

typedef struct
{
    UINT16 usVrampFlag;
    UINT16 usTdsBand34Vol;
    UINT16 usTdsBand39Vol;
    UINT16 usResv;
}TDS_NV_VRAMP_PARA_STRU;

typedef struct _TDS_TAS_ASU_NV_SUB_STRU_{
	UINT32         NV_ID_TDS_PrachFailNum; // 2
	UINT16         NV_ID_TDS_NGI; // 1
	UINT16         NV_ID_TDS_NPI; // 1
	INT16          NV_ID_TDS_GOOD_RSRP_THR;// -60
	INT16          NV_ID_TDS_POOR_RSRP_THR;// -95
    UINT32         NV_ID_TDS_GOOD_SCALE_THR;// 500
	UINT32         NV_ID_TDS_POOR_SCALE_THR;// 20
	UINT16         NV_ID_TDS_IDLE_HAPPY_THR;// 2
	UINT16         NV_ID_TDS_IDLE_UNHAPPY_THR;// 2
}TDS_TAS_ASU_NV_SUB_STRU;

typedef struct _TDS_TAS_ALG_NV_SUB_STRU_{
    UINT32 NV_ID_TDS_AS_ALG_PARA0; //Byte0��alpha �˲��������ӣ���������16������Ĭ��ֵΪ2��
	UINT32 NV_ID_TDS_AS_ALG_PARA1; //Byte1��N1 Ĭ��ֵ 1
	UINT32 NV_ID_TDS_AS_ALG_PARA2; //Byte2��N2 Ĭ��ֵ 5
	UINT32 NV_ID_TDS_AS_ALG_PARA3; //Byte3��N3 Ĭ��ֵ 7
	UINT32 NV_ID_TDS_AS_ALG_PARA4; //Byte4��SW_THR1 Ĭ��ֵ 9dB
	UINT32 NV_ID_TDS_AS_ALG_PARA5; //Byte5��SW_THR2 Ĭ��ֵ 6dB
	UINT32 NV_ID_TDS_AS_ALG_PARA6; //Byte6��SW_THR3 Ĭ��ֵ 3dB
	UINT32 NV_ID_TDS_AS_ALG_PARA7; //Byte7��SW_HYST Ĭ��ֵ 2s
}TDS_TAS_ASU_ALG_SUB_STRU;

typedef struct
{
	UINT32 NV_ID_TDS_AS_CTRL;
    TDS_TAS_ASU_ALG_SUB_STRU stTasTdsAsuPara;
    TDS_TAS_ASU_NV_SUB_STRU  stTasTdsThrPara;

	UINT32         NV_ID_TDS_TAS250_ENA;// 0
	//+tas250 end
}TDS_NV_TAS_PARA_STRU;

typedef struct
{
    UINT32 ulTdsDpdtDefault0;
    UINT32 ulTdsSwitchMap0;

    UINT32 ulTdsTasDpdtEna;
}TDS_NV_TAS_RF_PARA_STRU;
typedef struct
{
    INT16          ssHappyRscpThr;// -60
	INT16          ssUnhappyRscpThr;// -95
}TDS_NV_TAS_HAPPY_PARA_STRU;
typedef struct
{
    UINT32 ulTdsTasSFThr;
    UINT32 ulTdsTasCSThr;
	UINT32 ulTdsTasCSMThr;

    UINT32 ulTdsTasSearchEna;
}TDS_NV_TAS_SEARCH_PARA_STRU;


/*���modem��Ӧ��GPIO ȱʡΪ0*/
typedef struct
{
    UINT32 ulTasExtraModemGpio;
}NV_TAS_EXTRA_MODEM_GPIO_CFG;

typedef struct
{
    INT32  slTasBlindThr;   //DCH̬ä������
    INT32  slTasRsvThr;     //����NV
    UINT32 ulTasEna;        //ä������ʹ�ܱ�־��ֻ��ʹ��ʱä�����޲�����Ч
}TDS_NV_TAS_BLIND_CFG;

/*dpdt�л�ǰ��ı���ʱ��*/
typedef struct
{
    UINT32          ulProtectPre;
	UINT32          ulProtectPost;
}NV_TAS_DPDT_PROTECT_STRU;


typedef struct
{
    UINT16 usPointNum;            //������
    UINT16 usPointDistance;       //����ʱ����(����֡Ϊ��λ)
    UINT16 usTempThr;             //�����С�¶Ȳ�ֵ����
    INT16  sScaleThr;             //ƽ��scaleֵ����
    UINT32 ulPpmVarianceThr;      //��������Ppm��������
    UINT32 ulHs2NHsTimeDistance;  //����ģʽת��Ϊ�Ǹ���ģʽ��ʱ����(��֡Ϊ��λ)
} TDS_HIGH_SPEED_NV_PARA;
typedef struct
{
    TDS_HIGH_SPEED_NV_PARA stNvPara[2];
} TDS_NV_HIGH_SPEED_PARA_STRU;

typedef struct
{
    TDS_NV_RFIC_CFG_STRU stRficCfg;
    TDS_NV_LINECTRL_ALLOT_BY_HARDWARE_STRU stLineCtrlMapped;
    TDS_NV_MIPI_CTRL_STRU  stLineMipi;
    TDS_NV_RF_ADVANCE_TIME_STU stTdsTimer;
    TDS_NV_RXTX_PARA_STRU stRxTxPara;
    TDS_NV_TUNER_PARA_STRU stTunerPara;
    TDS_NV_DRX_PARA_STRU stTdsDrxPara;

    TDS_NV_TAS_PARA_STRU stTdsTasPara;
    TDS_NV_TAS_RF_PARA_STRU stTdsTasRfPara;
    UINT16 stTasCtrlEna;
    UINT16 usRsv;
	

    UINT16 usVctcxoInit;
    UINT16 usResv;
    TDS_NV_VRAMP_PARA_STRU stTdsVrampPara;
	TDS_NV_TAS_SEARCH_PARA_STRU stTdsTasSearchPara;
    TDS_NV_TAS_HAPPY_PARA_STRU  stTdsTasHappyPara;
    NV_TAS_EXTRA_MODEM_GPIO_CFG stExtraModemGpio;
    NV_TAS_DPDT_PROTECT_STRU    stDpdtProtect;
    TDS_NV_TAS_BLIND_CFG        stTdsTasBlindCfg;
    TDS_NV_HIGH_SPEED_PARA_STRU       stTdsHighSpeedPara;
}TDS_NV_STRU;

/*˽��nv*/
typedef struct
{
    UINT32 ulRes;
}TDS_NV_PRIVATE_STRU;

typedef struct
{
    UINT16      usCurrBand;
    UINT16      usLineCfgIndex;    //������̬ ����
    UINT16      usRfCfgIndex;  //֧��band��Ŀ
    UINT16      usResv;
}TDS_NV_INDEX_STRU;


extern TDS_NV_STRU * gpstTdsV9NvPara;
extern TDS_NV_INDEX_STRU            gstNvCfgInd;

TDS_BAND_TXPATH_PARA_STRU * TDS_GetTxNv(void);
TDS_PA_LEVEL_THRE_STRU * TDS_GetPaTreNv(void);
TDS_BAND_RXPATH_PARA_STRU * TDS_GetRxNv(void);
TDS_TEMPERATURE_SENSOR_STRU * TDS_GetSensorNv(void);
TDS_AGC_BAND_PARA_STRU * TDS_GetAgcBandNv(void);
UINT16  TDS_GetRxMainLnaSel(UINT32 ulBandIdx);
UINT16  TDS_GetRxDvtyLnaSel(UINT32 ulBandIdx);
UINT16  TDS_GetTxLnaSel(UINT32 ulBandIdx);
TDS_RF_PRIVATE_CORE_DIV_CFG_STRU*  TDS_GetCoreDivCfg(UINT32 ulBandIdx);
TDS_RF_TXIQ_CAL_STRU* TDS_GetTxiqFromNv(void);
UINT16 TDS_GetDcocComFromNv(UINT16 usGainCode);
TDS_NV_TUNER_PARA_STRU * TDS_GetTunerNv(void);
TDS_NV_DRX_PARA_STRU * TDS_GetTdsDrxNv(void);
UINT16 TDS_GetCTBandIndex(UINT16 usBand);
UINT16 gusTdsEquipBandIndex;
static inline TDS_RF_CH_SEL_ENUM_UINT16 TDS_MEAS_GetTdsCtuChNum(void)
{
    return gpstTdsV9NvPara->stTdsTimer.enChannelSel;
}
void TDS_NV_BtInit(void);

#ifdef __cplusplus
}/*end of extern C*/
#endif
#endif

