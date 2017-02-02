

/******************************************************************************
 PROJECT   :
 SUBSYSTEM :
 MODULE    :
 OWNER     :
******************************************************************************/

#ifndef __FTM_CT_H__
#define __FTM_CT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "gen_msg.h"
#include "TafAppMma.h"

#define FTM_CT_NORMAL             (0) /* ����������û�ж��� */
#define FTM_CT_WAIT               (1) /* �����������еȴ�����������ֱ�ӷ��ش��� */

#define FTM_CT_OVER_TIME          3000 /* DSPԭ�ﷵ�س�ʱʱ��(ms) */
#define  TDS_DHI_BASE_DRR				 0x11000000
/* DDR base addr*//* UDP */
/* #define  TDS_DDR_BASE_ADDR			 0x3af00000 */
/*  D2 */
/* #define  TDS_DDR_BASE_ADDR             0x37d00000 */
#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
/*#define  TDS_DDR_BASE_ADDR               GLOBAL_MEM_TDS_LH2_ADDR*/
#endif
#define  TDS_RFADJUSTPARA_DRR_OFFSET     0x30400
/* ��ʼУ׼��ϢID */
#define  MBV_A2Z_RFADJUSTSTART           0x71
/* ����У׼��ϢID */
#define  MBV_A2Z_RFADJUSTSTOP            0x72
/* ����APCOFFSETУ׼״̬ */
#define  MBV_A2Z_APCOFFSETFLAGSET        0x74
/* ֪ͨDSP�ӹ����ڴ��ȡУ׼��Ϣ��ϢID */
#define  MBV_A2Z_RFADJUST                0x17

#define ATR_MC_ASCII_TO_HEX(asciiChar)      atr05_51transAsciiCharIntoHex(asciiChar);
#define ATR_MC_ASCII_TO_TPDU(asciiChar, tpduResult, asciiCharLength, maxOutputDataLen) \
        atr05_72translateAsciiCharIntoTpdu(asciiChar, tpduResult, asciiCharLength, maxOutputDataLen);
typedef struct
{
    VOS_UINT32 ulReqTimer;

    /* FTM_CT_NORMAL: mean normal; FTM_CT_WAIT: mean WAIT */
    VOS_UINT8 ucSta;
    VOS_UINT8 ucRsv1;
    VOS_UINT8 ucRsv2;
    VOS_UINT8 ucRsv3;
} FTM_CTCMD_CTRL_STRU;

typedef struct
{
    FTM_RD_FCHAN_CNF_STRU stCurFchan;    /* AT��ѯ�ӿ��������ŵ����þ��践�أ����ȫ�ֱ�������CNF�ṹ */
    FTM_TXON_SWT_ENUM enCurTxon;         /* �������״̬ */
    FTM_RXON_SWT_ENUM enCurRxon;         /* ���ջ���״̬ */
    FWAVE_TYPE_ENUM   enCurFwaveType;    /* ������� */
    VOS_UINT16             usCurFwavePower;   /* ������� ��λ0.01db */
    VOS_UINT16             usCurVctcxoVol;    /* VCTCXO��ѹֵ */
#if (FEATURE_LTE_4RX == FEATURE_ON)
    VOS_UINT16             usRssiVal1;
    VOS_UINT16             usRssiVal2;
    VOS_UINT16             usRssiVal3;
    VOS_UINT16             usRssiVal4;
#else
    VOS_INT16              sCurRssiVal;       /* �����źŲ���ֵ */
#endif
    VOS_UINT8              ucCurLnaLvl;       /* LNA��λ */
    VOS_UINT8              ucNoSigFlg;        /* ������ģʽ�Ƿ�� */
    VOS_UINT8              ucTselrfPath;      /* ��Ƶͨ·��� */
    VOS_UINT8              ucTselrfGroup;     /* ��ѡ���������ڵ�һ������<path>�޷�׼ȷ˵����ʱ��ʹ�� */
} FTM_CT_MANAGE_INFO_STRU;


enum FTM_CT_F_CMD_STEPS_FLAG_ENUM
{
	CT_F_STEPS_DONE_NULL      =  0x00000000,  /* ��ʼ״̬:��ǰû��ִ���κ����� */
	CT_F_STEPS_DONE_BANDSW    =  0x00000001,  /* �ѳɹ�ִ������AT^BANDSW */
	CT_F_STEPS_DONE_FCHANS    =  0x00000002,  /* �ѳɹ�ִ������AT^FCHANS */
	CT_F_STEPS_DONE_FSEGMENT  =  0x00000004,  /* �ѳɹ�ִ������AT^FSEGMENT */
	CT_F_STEPS_DONE_FPOWS     =  0x00000008,  /* �ѳɹ�ִ������AT^FPOWS */
	CT_F_STEPS_DONE_FPAS      =  0x00000010,  /* �ѳɹ�ִ������AT^FPAS */
	CT_F_STEPS_DONE_FLNAS     =  0x00000020,  /* �ѳɹ�ִ������AT^FLNAS */
	CT_F_STEPS_DONE_FTXWAVE   =  0x00000040,  /* �ѳɹ�ִ������AT^FTXWAVE */
	CT_F_STEPS_DONE_FSTART    =  0x00000080,  /* �ѳɹ�ִ������AT^FSTART */
	CT_F_STEPS_DONE_FRSSIS_IND=  0x00000100,  /* FSTART ִ�к�,RSSI�Ѿ��ɹ������ϱ�*/
	CT_F_STEPS_DONE_FCMTMS_IND=  0x00000200,  /* FSTART ִ�к�,оƬ�¶�ֵ�Ѿ��ɹ������ϱ�*/

    CT_F_STEPS_DONE_FBLK        = 0x00000400, /* �Ѿ��ɹ�ִ��AT^FBLK */
    CT_F_STEPS_DONE_FIPSTART   = 0x00000800,  /* �Ѿ��ɹ�ִ��AT^FIPSTART */
    CT_F_STEPS_DONE_FPAPOWER   = 0x00001000,  /* �Ѿ��ɹ�ִ��AT^FPAPOWER */
    CT_F_STEPS_DONE_FMAXPOWER   = 0x00002000, /* �Ѿ��ɹ�ִ��AT^FMAXPOWER */
    CT_F_STEPS_DONE_FPDMS      = 0X00004000,  /* �Ѿ��ɹ�ִ��AT^fpdms */
	CT_F_STEPS_DONE_FPDPOWS      = 0X00080000,  /* �Ѿ��ɹ�ִ��AT^fpdpows */

	CT_F_STEPS_DONE_BUTT
};
typedef VOS_UINT32    FTM_CT_F_CMD_STEPS_FLAG_ENUM_UINT32;

#define FTM_F_CT_STORE_REQ_TEMP    (0)  /* ��������ͺ����̱����������ݵ���̬���� */
#define FTM_F_CT_STORE_REQ_GLOBAL  (1)  /* �յ���Ӧ��������ͳɹ��󣬽���̬�����е�ֵ���浽ȫ�ֽṹ */

typedef struct
{
	FTM_CT_F_CMD_STEPS_FLAG_ENUM_UINT32 ulCurCmdStepsFlag;	 /*��ǰ��ִ�в����־*/

	FCHAN_MODE_ENUM enCurMode;                               /* BANDSW MODE*/
	VOS_UINT8  ucCurBand;                                         /* BANDSW BAND*/
    VOS_UINT8  ucCurWaveType;                                     /* FTXWAVE:���䲨��*/
    VOS_UINT8  ucCurTriggerType;                                  /* FSTART:У׼���� */

    VOS_UINT8  ucPadding1;

	VOS_UINT16 usCurSegmentLen;                                   /* FSEGMENT:10,20���� */
    VOS_UINT16 usCurMeasOffset;                                   /* FSEGMENT:����ƫ�ưٷֱȣ�ȡֵ��Χ0~100 */
	VOS_UINT16 usCurMeasLen;                                      /* FSEGMENT:�������Ȱٷֱȣ�ȡֵ��Χ0~100 */

	VOS_UINT16 usCurUlListNum;                                    /* FAHSNS:�������õĸ�������ӦausUlFreqInfo�����16�� */
    VOS_UINT16 usCurDlListNum;                                    /* FAHSNS:�������õĸ�������ӦausDlFreqInfo�����16�� */

    VOS_UINT16 usCurTxPowerNum;                                   /* FPOWS:ָ����asTxPower�ĸ��� */
    VOS_UINT16 usCurPaLevelNum;                                   /* FPAS */
	VOS_UINT16 usCurAagcNum;                                      /* FLNAS */
    VOS_UINT16 usCmtmsNum; 					     				 /* �¶�ֵ������ȡֵ��ΧΪ0��16 */
    VOS_UINT16 usRsv;

    VOS_UINT16 ausCurUlFreqInfo[CT_F_FREQ_LIST_MAX_NUM];          /* FAHSNS:����Ƶ����Ϣ */
    VOS_UINT16 ausCurDlFreqInfo[CT_F_FREQ_LIST_MAX_NUM];          /* FAHSNS:����Ƶ����Ϣ */
    VOS_INT16 asCurTxPowerList[CT_F_TXPOW_SET_MAX_NUM];         /* FPOWS:���з��书��*/
    VOS_UINT8  aucCurPaLevelList[CT_F_PA_SET_MAX_NUM];            /* FPAS */
    VOS_UINT8  aucCurAagcList[CT_F_AAGC_SET_MAX_NUM];             /* FLNAS:AAGC����ֵ */

	/* У׼RSSI���� */
	VOS_UINT16 ausRxANT1RSSI[CT_F_FREQ_LIST_MAX_NUM][CT_F_TXPOW_SET_MAX_NUM]; /* FRSSIS:�����ŵ�����1��RSSI�Ĳ���ֵ����*/
	VOS_UINT16 ausRxANT2RSSI[CT_F_FREQ_LIST_MAX_NUM][CT_F_TXPOW_SET_MAX_NUM]; /* FRSSIS:�����ŵ�����2��RSSI�Ĳ���ֵ����*/

    VOS_UINT16 ausCmtms[CT_F_FREQ_LIST_MAX_NUM]; /* �¶�ֵ�б�ȡֵ��ΧΪ0��256�����¶�ֵ����Ϊ0��û���¶�ֵ�б� */

    VOS_UINT8 padding[2];

    VOS_UINT32 ulBlocking;

	VOS_UINT32 ulChannel;

	VOS_UINT32 ulFpapower_usPaLeverNum;/* ^fpapower */
	VOS_UINT16 usFpapower_list[CT_F_TXPOW_SET_MAX_NUM];
	VOS_UINT32 ulFmaxpower_usPaLevelNum;/* ^fmaxpower */
	VOS_UINT32 ulFmaxpower_usPaReduceGain;/* ^fmaxpower */

	VOS_UINT32 ulFpdmsSw;    /* at^fpdms */

    FTM_SET_FCALIIP2S_REQ_STRU stFCaliIp2sSetReq;
    FTM_RD_FCALIIP2S_CNF_STRU  stFCaliIp2sRdCnf;

    FTM_SET_FGAINSTATES_REQ_STRU stFGainStatesSetReq;

    FTM_SET_FCALIDCOCS_REQ_STRU stFCaliDcocsSetReq;
    FTM_RD_FCALIDCOCS_CNF_STRU  stFCaliDcocsRdCnf;

    FTM_SET_FCALIIP2SMRF_REQ_STRU stFCaliIp2sMrfSetReq;
    FTM_RD_FCALIIP2SMRF_CNF_STRU  stFCaliIp2sMrfRdCnf;

    FTM_SET_FCALIDCOCSMRF_REQ_STRU stFCaliDcocsMrfSetReq;
    FTM_RD_FCALIDCOCSMRF_CNF_STRU  stFCaliDcocsMrfRdCnf;

	FTM_SET_FDBBATTS_REQ_STRU stFDbbAttSetReq;

	FTM_SET_FBBATTS_REQ_STRU  stFBbAttSetReq;

	FTM_SET_FCALITXIQS_REQ_STRU  stFCaliTxiqSetReq;
    FTM_RD_FCALITXIQS_CNF_STRU  stFCaliTxiqRdCnf;
	FTM_SET_F_FCALPDDCS_REQ_STRU stFCalPDDCSSetReq;
	FTM_RD_F_FCALPDDCS_CNF_STRU stFCalPDDCSRdCnf;
	FTM_SET_F_FPDPOWS_REQ_STRU stFpdpowsSetReq;
	FTM_RD_FQPDDCRES_CNF_STRU stFQPDDCRESRdCnf;
} FTM_CT_F_MANAGE_INFO_STRU;

/* �������۲� */
enum FTM_SYN_CMD_STEPS_FLAG_ENUM
{
	CT_S_STEPS_DONE_NULL      =  0x00000000,  /* ��ʼ״̬:��ǰû��ִ���κ����� */

	CT_S_STEPS_DONE_SSYNC           =  0x00000001,  /* �ѳɹ�ִ������AT^BANDSW */
	CT_S_STEPS_DONE_SSYNC_IND      = 0x00000002,
	CT_S_STEPS_DONE_STXBW           =  0x00000004,  /* �ѳɹ�ִ������AT^FCHANS */
	CT_S_STEPS_DONE_STXCHAN         =  0x00000008,  /* �ѳɹ�ִ������AT^FSEGMENT */
	CT_S_STEPS_DONE_SSUBFRAME       =  0x00000010,  /* �ѳɹ�ִ������AT^FPOWS */
	CT_S_STEPS_DONE_SPARA           =  0x00000020,  /* �ѳɹ�ִ������AT^FPAS */
	CT_S_STEPS_DONE_SSEGNUM         =  0x00000040,  /* �ѳɹ�ִ������AT^FLNAS */
	CT_S_STEPS_DONE_STXMODUS        =  0x00000080,  /* �ѳɹ�ִ������AT^FTXWAVE */
	CT_S_STEPS_DONE_STXRBNUMS       =  0x00000100,  /* �ѳɹ�ִ������AT^FSTART */
	CT_S_STEPS_DONE_STXRBPOSS       =  0x00000200,  /* FSTART ִ�к�,RSSI�Ѿ��ɹ������ϱ�*/
	CT_S_STEPS_DONE_STXPOWS         =  0x00000400,  /* FSTART ִ�к�,оƬ�¶�ֵ�Ѿ��ɹ������ϱ�*/

    CT_S_STEPS_DONE_STXCHANTYPES   = 0x00000800,  /* �Ѿ��ɹ�ִ��AT^FBLK */
    CT_S_STEPS_DONE_SSEGLEN         = 0x00001000, /* �Ѿ��ɹ�ִ��AT^FIPSTART */
	CT_S_STEPS_DONE_SRXPOW          = 0x00002000, /* �Ѿ��ɹ�ִ��AT^FIPSTART */
	CT_S_STEPS_DONE_SRXSUBFRA      = 0x00004000, /* �Ѿ��ɹ�ִ��AT^FIPSTART */
	CT_S_STEPS_DONE_SRXBLER        = 0x00008000, /* �Ѿ��ɹ�ִ��AT^FIPSTART */
	CT_S_STEPS_DONE_SRXBLER_IND    = 0x00010000,
	CT_S_STEPS_DONE_SSTART         = 0x00020000, /* �Ѿ��ɹ�ִ��AT^FIPSTART */
	CT_S_STEPS_DONE_SSTOP          = 0x00040000, /* �Ѿ��ɹ�ִ��AT^FIPSTART */
	CT_S_STEPS_DONE_SRXSET         = 0x00080000, /* �Ѿ��ɹ�ִ��AT^SRXSET */
	CT_S_STEPS_DONE_TMODE_7_REQ   = 0x00100000,

	CT_S_STEPS_DONE_SSYNC_CNF     = 0x00200000,
	CT_S_STEPS_DONE_SSTART_CNF    = 0x00400000,
	CT_S_STEPS_DONE_STCFGDPCH    = 0x00800000,   /* �Ѿ��ɹ�ִ�� AT^STCFGDPCH  */
	CT_S_STEPS_DONE_FPOW         = 0x01000000,    /* �Ѿ��ɹ�ִ�� AT^FPOW  */
	CT_S_STEPS_DONE_STRXBER_IND   = 0x02000000,    /* TDS ��DSP�����ϱ�BER ִ��*/
	CT_S_STEPS_DONE_BUTT
};

typedef VOS_UINT32    FTM_SYN_CMD_STEPS_FLAG_ENUM_UINT32;

#define FTM_SYN_STORE_REQ_TEMP    (0)  /* ��������ͺ����̱����������ݵ���̬���� */
#define FTM_SYN_STORE_REQ_GLOBAL  (1)  /* �յ���Ӧ��������ͳɹ��󣬽���̬�����е�ֵ���浽ȫ�ֽṹ */


typedef struct
{
	FTM_SYN_CMD_STEPS_FLAG_ENUM_UINT32 ulCurCmdStepsFlag;	 /*��ǰ��ִ�в����־*/

	FTM_RD_SSYNC_CNF_STRU     stSsyncRdCnf;
	FTM_RD_STXBW_CNF_STRU     stStxbwRdCnf;
	FTM_RD_STXCHAN_CNF_STRU   stStxchanRdCnf;
	FTM_RD_SSUBFRAME_CNF_STRU stSsubframeRdCnf;
    FTM_RD_SPARA_CNF_TOTAL_STRU stSparaRdCnf;
	FTM_RD_SSEGNUM_CNF_STRU   stSsegnumRdCnf;
	FTM_RD_STXMODUS_CNF_STRU  stStxmodusRdCnf;
	FTM_RD_STXRBNUMS_CNF_STRU stStxrbnumsRdCnf;
	FTM_RD_STXRBPOSS_CNF_STRU stStxrbpossRdCnf;
	FTM_RD_STXPOWS_CNF_STRU   stStxpowsRdCnf;
	FTM_RD_STXCHANTYPES_CNF_STRU stStxchantypesRdCnf;
	FTM_RD_SSEGLEN_CNF_STRU   stSseglenRdCnf;
	FTM_RD_SRXSET_CNF_STRU   stSrxsetRdCnf;
	FTM_RD_SRXPOW_CNF_STRU    stSrxpowRdCnf;
	FTM_RD_SRXSUBFRA_CNF_STRU stSrxsubfraRdCnf;
	FTM_RD_SRXBLER_CNF_STRU   stSrxblerRdCnf;
      FTM_SET_SPARA_REQ_STRU    stFtmSparaInfo;    /* BT save at^spara*/
	FTM_RD_STRXBER_CNF_STRU   stStrxBerRdCnf;          /*BT tds�۲�BER��� */
	FTM_RD_SSTART_CNF_STRU    stSstartRdCnf;

}FTM_SYN_INFO_STRU;

typedef struct
{
    FTM_RESET_CALLBACK_PFN pfnResetSymFunc;

    /* ��ͨУ׼Ĭ��ֵ������ʱ���ݱ���*/
    FTM_CT_MANAGE_INFO_STRU stFtmCtInfo;

	/* ����У׼Ĭ��ֵ������ʱ���ݱ���*/
	FTM_CT_F_MANAGE_INFO_STRU stFtmFastCtInfo;

	FTM_SYN_INFO_STRU stFtmSynInfo;

    /* ϵͳģʽ */
    SYM_TMODE_ENUM symMode;
	
    FTM_RD_LTCOMMCMD_CNF_STRU stRdLtCommCmdCnf;


} FTM_MAIN_INFO_STRU;

typedef struct
{
    VOS_UINT16 usDlLowFreq; /* ��Ƶ��������ʼƵ��, LTE 100KhzΪ��λ, TDS 200KhzΪ��λ */
    VOS_UINT16 usDlLowChan; /* ��Ƶ��������ʼƵ�� */
    VOS_UINT16 usDlHigChan; /* ��Ƶ�����н���Ƶ�� */
    VOS_UINT16 usUlLowFreq; /* ��Ƶ��������ʼƵ��, LTE 100KhzΪ��λ, TDS 200KhzΪ��λ */
    VOS_UINT16 usUlLowChan; /* ��Ƶ��������ʼƵ�� */
    VOS_UINT16 usUlHigChan; /* ��Ƶ�����н���Ƶ�� */
    VOS_UINT8  ucBandMode;  /* ��Ƶ��ģʽ */
    VOS_UINT8  ucBandSWID;  /* ��Ƶ��BandSwitch ID */
}FTM_BAND_INFO_STRU;

/* ��󱣴����Ϣ�� */
#define FTM_MNTN_MSG_MAXNUM 10

typedef struct
{
    VOS_UINT32     ulMsgId;            /* ��ϢID */
    VOS_UINT32     ulSlice;            /* ��ȡʱ�� */
}FTM_MNTN_MSG_STRU;

typedef struct
{
    VOS_UINT32 ulTotalCount;                       /* ���յ��ܵ���Ϣ����    */
    VOS_UINT32 ulPtr;                              /* ѭ��ָ��,����ѭ���洢 */
    FTM_MNTN_MSG_STRU astMsg[FTM_MNTN_MSG_MAXNUM]; /* ���10����Ϣ */
}FTM_MNTN_MSGINFO_STRU;

typedef struct
{
    VOS_BOOL              bdbg;            /* �Ƿ�򿪵�����Ϣ��ӡ */
    FTM_MNTN_MSGINFO_STRU stAcore2FtmMsg;  /* FTM�յ���A����Ϣ */
    FTM_MNTN_MSGINFO_STRU stFtm2AcoreMsg;  /* FTM���͵�A����Ϣ */
    FTM_MNTN_MSGINFO_STRU stFtm2RttMsg;    /* FTM���͵�RTT��Ϣ */
    FTM_MNTN_MSGINFO_STRU stRtt2FtmMsg;    /* FTM�յ���RTT��Ϣ */
    FTM_MNTN_MSGINFO_STRU stTimeOutMsg;    /* ��ʱδ������Ϣ   */
}FTM_MNTN_STRU;

extern FTM_MNTN_STRU g_stFtmMntn;

/* ���ACORE->FTM��Ϣ�� FTM MNTN��  */
#define FTM_MNTN_ACORE2FTM_MSG(id) \
{ \
    g_stFtmMntn.stAcore2FtmMsg.ulTotalCount++; \
    g_stFtmMntn.stAcore2FtmMsg.astMsg[g_stFtmMntn.stAcore2FtmMsg.ulPtr].ulMsgId = id; \
    g_stFtmMntn.stAcore2FtmMsg.astMsg[g_stFtmMntn.stAcore2FtmMsg.ulPtr].ulSlice = VOS_GetSlice(); \
    g_stFtmMntn.stAcore2FtmMsg.ulPtr = (g_stFtmMntn.stAcore2FtmMsg.ulPtr+1)%FTM_MNTN_MSG_MAXNUM; \
}

/* ���FTM->ACORE��Ϣ�� FTM MNTN�� */
#define FTM_MNTN_FTM2ACORE_MSG(id) \
{ \
    g_stFtmMntn.stFtm2AcoreMsg.ulTotalCount++; \
    g_stFtmMntn.stFtm2AcoreMsg.astMsg[g_stFtmMntn.stFtm2AcoreMsg.ulPtr].ulMsgId = id; \
    g_stFtmMntn.stFtm2AcoreMsg.astMsg[g_stFtmMntn.stFtm2AcoreMsg.ulPtr].ulSlice = VOS_GetSlice(); \
    g_stFtmMntn.stFtm2AcoreMsg.ulPtr = (g_stFtmMntn.stFtm2AcoreMsg.ulPtr+1)%FTM_MNTN_MSG_MAXNUM; \
}

/* ���FTM->RTT��Ϣ�� FTM MNTN��  */
#define FTM_MNTN_FTM2RTT_MSG(id) \
{ \
    g_stFtmMntn.stFtm2RttMsg.ulTotalCount++; \
    g_stFtmMntn.stFtm2RttMsg.astMsg[g_stFtmMntn.stFtm2RttMsg.ulPtr].ulMsgId = id; \
    g_stFtmMntn.stFtm2RttMsg.astMsg[g_stFtmMntn.stFtm2RttMsg.ulPtr].ulSlice = VOS_GetSlice(); \
    g_stFtmMntn.stFtm2RttMsg.ulPtr = (g_stFtmMntn.stFtm2RttMsg.ulPtr+1)%FTM_MNTN_MSG_MAXNUM; \
}

/* ���FTM->ACORE��Ϣ�� FTM MNTN�� */
#define FTM_MNTN_RTT2FTM_MSG(id) \
{ \
    g_stFtmMntn.stRtt2FtmMsg.ulTotalCount++; \
    g_stFtmMntn.stRtt2FtmMsg.astMsg[g_stFtmMntn.stRtt2FtmMsg.ulPtr].ulMsgId = id; \
    g_stFtmMntn.stRtt2FtmMsg.astMsg[g_stFtmMntn.stRtt2FtmMsg.ulPtr].ulSlice = VOS_GetSlice(); \
    g_stFtmMntn.stRtt2FtmMsg.ulPtr = (g_stFtmMntn.stRtt2FtmMsg.ulPtr+1)%FTM_MNTN_MSG_MAXNUM; \
}

/* ���TIMEOUT��Ϣ�� FTM MNTN�� */
#define FTM_MNTN_TIMEOUT_MSG(id) \
{ \
    g_stFtmMntn.stTimeOutMsg.ulTotalCount++; \
    g_stFtmMntn.stTimeOutMsg.astMsg[g_stFtmMntn.stTimeOutMsg.ulPtr].ulMsgId = id; \
    g_stFtmMntn.stTimeOutMsg.astMsg[g_stFtmMntn.stTimeOutMsg.ulPtr].ulSlice = VOS_GetSlice(); \
    g_stFtmMntn.stTimeOutMsg.ulPtr = (g_stFtmMntn.stTimeOutMsg.ulPtr+1)%FTM_MNTN_MSG_MAXNUM; \
}

extern VOS_VOID ftm_help(VOS_VOID);
extern VOS_VOID ftm_debug(VOS_BOOL bDebug);
extern VOS_VOID ftm_mntn_init(VOS_VOID);
extern VOS_VOID ftm_mntn_ftmmsginfo(VOS_VOID);
extern VOS_VOID ftm_mntn_rttmsginfo(VOS_VOID);
extern VOS_VOID ftm_mntn_timoutinfo(VOS_VOID);

extern FTM_MAIN_INFO_STRU * ftm_GetMainInfo(VOS_VOID);

/* ��ȡ�������ģʽ */
extern VOS_UINT8 ftm_GetNoneSig(VOS_VOID);
extern VOS_VOID ftm_SetNoneSig(VOS_UINT8 ucNoneSigNal);

/* ����У׼����������� */
extern FTM_SYN_INFO_STRU *ftm_GetSynMainInfo(VOS_VOID);

extern FTM_CT_F_MANAGE_INFO_STRU* ftm_GetFastCTMainInfo(VOS_VOID);
extern VOS_BOOL ftm_CheckCmdSteps(FTM_CT_F_CMD_STEPS_FLAG_ENUM_UINT32 enCmdSteps);
extern VOS_BOOL ftm_CheckSynCmdSteps(VOS_UINT32 enCmdSteps);
extern VOS_VOID ftm_SetDefault(VOS_VOID);


/**********************************************************************************/

extern VOS_VOID ftm_MainInfoInit(VOS_VOID);
extern VOS_VOID ftm_MainFunTableInit(VOS_VOID);

#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
#if 0
#endif
extern VOS_VOID tgl00_99getCurrentCellInfo(FTM_SCELLINFO_STRU * currentCellInfo);
extern VOS_VOID hl101_29writeReqtoDhiBuffer(VOS_VOID *pReq);
#endif

/******************************************************************************//* A��װ����Ϣ������ԭ�� */
typedef VOS_UINT32 (*PFN_AT_FTM_EQUIP_MSG_PROC)(VOS_VOID*);

/* DSPԭ����Ϣ������ԭ�� */
typedef VOS_UINT32 (*PFN_AT_FTM_DSP_MSP_PROC)(VOS_VOID*);
/* A��װ����Ϣ��ʱ������ԭ�� */
typedef VOS_UINT32 (*PFN_AT_FTM_TIMEOUT_PROC)(VOS_VOID);

/* MSP ��Ϣ������ԭ��*/
typedef VOS_UINT32 (*PFN_AT_FTM_PS_MSP_PROC)(VOS_VOID*);

/* PS ����MSP ��Ϣ������� */
typedef struct
{
    VOS_UINT32 ulMsgId;
    PFN_AT_FTM_PS_MSP_PROC pfnPsMsgProc;    
}FTM_PS_MSG_FUNTBL_STRU;
/* A��װ����Ϣ������� */typedef struct
{
    VOS_UINT32 ulMsgId;
    PFN_AT_FTM_EQUIP_MSG_PROC pfnEquipMsgProc;
    PFN_AT_FTM_TIMEOUT_PROC   pfnTimeoutProc;
}FTM_EQUIP_MSG_FUNTBL_STRU;

/* DSPԭ����Ϣ������� */
typedef struct
{
    VOS_UINT32 ulMsgId;
    PFN_AT_FTM_DSP_MSP_PROC pfnDspMsgProc;
}FTM_DSP_MSG_FUNTBL_STRU;

extern FTM_CTCMD_CTRL_STRU g_ct_cmd_ctrl;

extern VOS_VOID MMA_PhModeSet(VOS_UINT16 ClientId, VOS_UINT8 OpId, TAF_PH_OP_MODE_STRU *pstPhMode);

/*FTMģ��ͨ�ú��� */
extern VOS_UINT32 ftm_comm_starttimer(VOS_UINT32* pulTimer, VOS_UINT32 reqId);
extern VOS_UINT32 ftm_comm_stoptimer(VOS_UINT32* pulTimer);
extern VOS_UINT32 ftm_comm_send(VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);

/* FTMģ����������  */
extern VOS_UINT32 ftm_mailbox_init(VOS_VOID);
extern VOS_VOID ftm_mailbox_taskproc(VOS_UINT32 ulPara0,
                              VOS_UINT32 ulPara1,
                              VOS_UINT32 ulPara2,
                              VOS_UINT32 ulPara3);
extern VOS_UINT32 ftm_mailbox_ltect_write(VOS_VOID* param, VOS_UINT32 ulLen);
extern VOS_UINT32 ftm_mailbox_ltebt_write(VOS_VOID* param, VOS_UINT32 ulLen);
extern VOS_UINT32 ftm_mailbox_tdsct_write(VOS_VOID* param, VOS_UINT32 ulLen);
extern VOS_UINT32 ftm_mailbox_tdsbt_write(VOS_VOID* param, VOS_UINT32 ulLen);
extern VOS_UINT32 ftm_mailbox_ct_write(VOS_UINT32 mode, VOS_VOID* param,VOS_UINT32 ulLen);
extern VOS_UINT32 ftm_mailbox_bt_write(VOS_UINT32 mode, VOS_VOID* param,VOS_UINT32 ulLen);

/* LTEЭ�鴦���� */
extern VOS_UINT32 at_ftm_getBandID(FCHAN_MODE_ENUM emMode, VOS_UINT8 ucBandSwitchID, VOS_UINT8 * pucBandID);
extern VOS_UINT32 at_ftm_getLteBandswId(VOS_UINT8 ucBandID, VOS_UINT8 * pucBandSwitchID, FCHAN_MODE_ENUM * pemBandMode);
extern VOS_UINT16 at_ftm_get_dlchan(FCHAN_MODE_ENUM emMode, VOS_UINT16 usChan);
extern VOS_UINT16 at_ftm_get_ulchan(FCHAN_MODE_ENUM emMode, VOS_UINT16 usChan);
extern VOS_UINT16 at_ftm_get_freq(FCHAN_MODE_ENUM emMode, VOS_UINT16 usChan);

/* AT^TMODE */
extern VOS_UINT32 at_ftm_tmode_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_tmode_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_tmode_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_tmode_dspcnf(VOS_VOID * pParam);

/* AT^BANDSW */
extern VOS_UINT32 at_ftm_bandsw_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_bandsw_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_bandsw_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_bandsw_dspcnf(VOS_VOID * pParam);

/* AT^TSELRF */
extern VOS_UINT32 at_ftm_tselrf_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_tselrf_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_tselrf_dspcnf(VOS_VOID * pParam);

/* AT^FCHAN */
extern VOS_UINT32 at_ftm_fchan_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fchan_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fchan_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fchan_dspcnf(VOS_VOID * pParam);

/* AT^FLNA */
extern VOS_UINT32 at_ftm_flna_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_flna_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_flna_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_flna_dspcnf(VOS_VOID * pParam);

/* AT^FWAVE */
extern VOS_UINT32 at_ftm_fwave_set(VOS_VOID * pParamq);
extern VOS_UINT32 at_ftm_fwave_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fwave_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fwave_dspcnf(VOS_VOID * pParam);

/* AT^FTXON */
extern VOS_UINT32 at_ftm_ftxon_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ftxon_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_ftxon_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ftxon_dspcnf(VOS_VOID * pParam);

/* AT^FRXON */
extern VOS_UINT32 at_ftm_frxon_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_frxon_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_frxon_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_frxon_dspcnf(VOS_VOID * pParam);

/* AT^FRSSI */
extern VOS_UINT32 at_ftm_frssi_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_frssi_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_frssi_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_frssi_dspind(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_frssi_readcnf(VOS_UINT32 ulErrCode);

/* AT^FVCTCXO */
extern VOS_UINT32 at_ftm_fvctcxo_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fvctcxo_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fvctcxo_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fvctcxo_dspcnf(VOS_VOID * pParam);

/* AT^FBLK */
extern VOS_UINT32 at_ftm_fblk_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fblk_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fblk_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fblk_dspcnf(VOS_VOID * pParam);

/* AT^FCHANS */
extern VOS_UINT32 at_ftm_fchans_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fchans_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fchans_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fchans_dspcnf(VOS_VOID * pParam);

/* AT^FSEGMENT */
extern VOS_UINT32 at_ftm_fsegment_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fsegment_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fsegment_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fsegment_dspcnf(VOS_VOID * pParam);

/* AT^FPOWS */
extern VOS_UINT32 at_ftm_fpows_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fpows_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fpows_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fpows_dspcnf(VOS_VOID * pParam);

/* AT^FPAS */
extern VOS_UINT32 at_ftm_fpas_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fpas_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fpas_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fpas_dspcnf(VOS_VOID * pParam);

/* AT^FLNAS */
extern VOS_UINT32 at_ftm_flnas_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_flnas_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_flnas_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_flnas_dspcnf(VOS_VOID * pParam);

/* AT^FPDMS */
extern VOS_UINT32 at_ftm_fpdms_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fpdms_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fpdms_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fpdms_dspcnf(VOS_VOID* pParam);

/* AT^FTXWAVE */
extern VOS_UINT32 at_ftm_ftxwave_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ftxwave_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_ftxwave_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ftxwave_dspcnf(VOS_VOID * pParam);

/* AT^FSTART */
extern VOS_UINT32 at_ftm_fstart_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fstart_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fstart_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fstart_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fstart_read_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fstart_read_dspcnf(VOS_VOID * pParam);

/* AT^FRSSIS */
extern VOS_UINT32 at_ftm_frssis_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_frssis_dspind(VOS_VOID * pParam);

/* AT^FCMTMS */
extern VOS_UINT32 at_ftm_fcmtms_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcmtms_dspind(VOS_VOID * pParam);

/* AT^FMAXPOWER */
extern VOS_UINT32 at_ftm_fmaxpower_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fmaxpower_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fmaxpower_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fmaxpower_read(VOS_VOID * pParam);

/* AT^FPAPOWER */
extern VOS_UINT32 at_ftm_fpapower_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fpapower_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fpapower_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fpapower_dspcnf(VOS_VOID * pParam);

/* AT^FCALIIP2S */
extern VOS_UINT32 at_ftm_fcaliip2s_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcaliip2s_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fcaliip2s_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcaliip2s_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcaliip2s_dspind(VOS_VOID * pParam);

/* AT^FCALIDCOCS */
extern VOS_UINT32 at_ftm_fcalidcocs_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcalidcocs_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fcalidcocs_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcalidcocs_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcalidcocs_dspind(VOS_VOID * pParam);

/* AT^FCALIIP2SMRF */
extern VOS_UINT32 at_ftm_fcaliip2sMrf_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcaliip2sMrf_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fcaliip2sMrf_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcaliip2sMrf_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcaliip2sMrf_dspind(VOS_VOID * pParam);

/* AT^FCALIDCOCSMRF */
extern VOS_UINT32 at_ftm_fcalidcocsMrf_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcalidcocsMrf_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fcalidcocsMrf_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcalidcocsMrf_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcalidcocsMrf_dspind(VOS_VOID * pParam);

/* AT^FGAINSTATES */
extern VOS_UINT32 at_ftm_fgainstates_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fgainstates_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fgainstates_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fgainstates_dspcnf(VOS_VOID * pParam);

/* AT^FDBBATTS */
extern VOS_UINT32 at_ftm_fdbbatts_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fdbbatts_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fdbbatts_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fdbbatts_dspcnf(VOS_VOID * pParam);

/* AT^FBBATTS */
extern VOS_UINT32 at_ftm_fbbatts_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fbbatts_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fbbatts_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fbbatts_dspcnf(VOS_VOID * pParam);

/* AT^FCALITXIQS */
extern VOS_UINT32 at_ftm_fcalitxiqs_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcalitxiqs_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fcalitxiqs_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcalitxiqs_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fcalitxiqs_dspind(VOS_VOID * pParam);

/* AT^FIPSTART */
extern VOS_UINT32 at_ftm_fipstart_set(VOS_VOID* pParam);
extern VOS_UINT32 at_ftm_fipstart_dspind(VOS_VOID * pParam);

/* AT^CMTM */
extern VOS_UINT32 at_ftm_cmtm_read(VOS_VOID * pParam);

/* LTE�������۲�AT���� */
/* AT^SSYNC */
extern VOS_UINT32 at_ftm_ssync_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ssync_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_ssync_read(VOID * pParam);
extern VOS_UINT32 at_ftm_ssync_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ssync_dspind(VOS_VOID * pParam);

/* AT^STXBW */
extern VOS_UINT32 at_ftm_stxbw_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_stxbw_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_stxbw_read(VOID * pParam);
extern VOS_UINT32 at_ftm_stxbw_dspcnf(VOS_VOID * pParam);

/* AT^STXCHAN */
extern VOS_UINT32 at_ftm_stxchan_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_stxchan_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_stxchan_read(VOID * pParam);
extern VOS_UINT32 at_ftm_stxchan_dspcnf(VOS_VOID * pParam);

/* AT^SSUBFRAME */
extern VOS_UINT32 at_ftm_ssubframe_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ssubframe_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_ssubframe_read(VOID * pParam);
extern VOS_UINT32 at_ftm_ssubframe_dspcnf(VOS_VOID * pParam);

/* AT^SPARA */
extern VOS_UINT32 at_ftm_spara_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_spara_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_spara_read(VOID * pParam);
extern VOS_UINT32 at_ftm_spara_dspcnf(VOS_VOID * pParam);

/* AT^SSEGNUM */
extern VOS_UINT32 at_ftm_ssegnum_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ssegnum_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_ssegnum_read(VOID * pParam);
extern VOS_UINT32 at_ftm_ssegnum_dspcnf(VOS_VOID * pParam);

/* AT^STXMODUS */
extern VOS_UINT32 at_ftm_stxmodus_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_stxmodus_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_stxmodus_read(VOID * pParam);
extern VOS_UINT32 at_ftm_stxmodus_dspcnf(VOS_VOID * pParam);

/* AT^STXRBNUMS */
extern VOS_UINT32 at_ftm_stxrbnums_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_stxrbnums_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_stxrbnums_read(VOID * pParam);
extern VOS_UINT32 at_ftm_stxrbnums_dspcnf(VOS_VOID * pParam);

/* AT^STXRBPOSS */
extern VOS_UINT32 at_ftm_stxrbposs_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_stxrbposs_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_stxrbposs_read(VOID * pParam);
extern VOS_UINT32 at_ftm_stxrbposs_dspcnf(VOS_VOID * pParam);

/* AT^STXPOWS */
extern VOS_UINT32 at_ftm_stxpows_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_stxpows_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_stxpows_read(VOID * pParam);
extern VOS_UINT32 at_ftm_stxpows_dspcnf(VOS_VOID * pParam);

/* AT^STXCHANTYPES */
extern VOS_UINT32 at_ftm_stxchantypes_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_stxchantypes_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_stxchantypes_read(VOID * pParam);
extern VOS_UINT32 at_ftm_stxchantypes_dspcnf(VOS_VOID * pParam);

/* AT^SSEGLEN */
extern VOS_UINT32 at_ftm_sseglen_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_sseglen_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_sseglen_read(VOID * pParam);
extern VOS_UINT32 at_ftm_sseglen_dspcnf(VOS_VOID * pParam);

/* AT^SRXSET */
extern VOS_UINT32 at_ftm_srxset_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_srxset_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_srxset_read(VOID * pParam);
extern VOS_UINT32 at_ftm_srxset_dspcnf(VOS_VOID * pParam);

/* AT^SRXSUBFRA */
extern VOS_UINT32 at_ftm_srxsubfra_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_srxsubfra_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_srxsubfra_read(VOID * pParam);
extern VOS_UINT32 at_ftm_srxsubfra_dspcnf(VOS_VOID * pParam);

/* AT^SRXMEAS */
extern VOS_UINT32 at_ftm_srxmeas_read(VOID * pParam);
extern VOS_UINT32 at_ftm_srxmeas_dspind(VOS_VOID * pParam);

/* AT^SSTART */
extern VOS_UINT32 at_ftm_sstart_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_sstart_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_sstart_read(VOID * pParam);
extern VOS_UINT32 at_ftm_sstart_dspcnf(VOS_VOID * pParam);

/* AT^SSTOP */
extern VOS_UINT32 at_ftm_sstop_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_sstop_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_sstop_dspcnf(VOS_VOID * pParam);

/* TDSװ��AT���� */
#if(FEATURE_ON == FEATURE_UE_MODE_TDS)

/* AT^SCALIB */
extern VOS_UINT32 at_ftm_scalibRdFun(VOS_VOID* pParam);
extern VOS_UINT32 at_ftm_scalibSetFun(VOS_VOID * pParam);/* AT^SCELLINFO */
extern VOS_UINT32 at_ftm_scellinfoRdFun(VOS_VOID * pParam);

#endif

extern SYM_TMODE_ENUM* ftm_GetTmodeMainInfo(VOS_VOID);

EXTERN VOS_UINT32 at_ftm_fcalpddcs_set(VOID* pParam);
EXTERN VOS_UINT32 at_ftm_fcalpddcs_dspind(VOID* pParam);
EXTERN VOS_UINT32 at_ftm_fcalpddcs_read(VOS_VOID* pParam);
EXTERN VOS_UINT32 at_ftm_fcalpddcs_dspcnf(VOID* pParam);
EXTERN VOS_UINT32 at_ftm_fcalpddcs_timeout(VOS_VOID);
EXTERN VOS_UINT32 at_ftm_fpdpows_set(VOID* pParam);
EXTERN VOS_UINT32 at_ftm_fpdpows_timeout(VOS_VOID);
EXTERN VOS_UINT32 at_ftm_fpdpows_dspcnf(VOID* pParam);
EXTERN VOS_UINT32 at_ftm_fpdpows_dspind(VOID* pParam);
EXTERN VOS_UINT32 at_ftm_fqpddcres_set(VOID* pParam);
extern VOS_UINT32 at_ftm_ssync_pscnf(VOS_VOID* pParam);
extern VOS_UINT32 at_ftm_stcfgdpch_set(VOS_VOID* pParam);
extern VOS_UINT32 at_ftm_fpow_set(VOS_VOID* pParam);
extern VOS_UINT32 at_ftm_fpow_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_fpow_dspcnf(VOS_VOID* pParam);
extern VOS_UINT32 at_ftm_stcfgdpch_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_stcfgdpch_pscnf(VOS_VOID* pParam);
extern VOS_UINT32 at_ftm_strxmeas_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_strxmeas_dspind(VOS_VOID * pParam);
extern VOS_UINT32 atFTMSendVosMsg(VOS_UINT32 TaskId, IN VOS_VOID* pData, VOS_UINT32 uLen);


extern VOS_UINT32 at_ftm_ltcommcmd_set(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ltcommcmd_read(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ltcommcmd_timeout(VOS_VOID);
extern VOS_UINT32 at_ftm_ltcommcmd_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_ltcommcmd_dspind(VOS_VOID * pParam);

extern VOS_UINT32 at_ftm_fpllstatus_read(VOS_VOID* pParam);
extern VOS_UINT32 at_ftm_fpllstatus_readcnf(VOS_UINT16 txStatus, VOS_UINT16 rxStatus,VOS_UINT32 ulErrCode);
extern VOS_UINT32 at_ftm_fpllstatus_dspcnf(VOS_VOID * pParam);
extern VOS_UINT32 at_ftm_fpllstatus_timeout(VOS_VOID);

extern VOS_UINT32 at_ftm_ftxon_setcnf(VOS_UINT32 ulErrCode);
extern VOS_VOID at_ftm_tmode_store(VOS_UINT8 ucStoreType, SYM_SET_TMODE_REQ_STRU* pstReq);
extern VOS_VOID at_ftm_frxon_store(VOS_UINT8 ucStoreType, FTM_SET_RXON_REQ_STRU* pstReq);
extern VOS_UINT32 at_ftm_frxon_setcnf(VOS_UINT32 ulErrCode);
extern VOS_VOID at_ftm_frssi_store(VOS_INT16 sRssiVal);
extern VOS_VOID at_ftm_fwave_store(VOS_UINT8 ucStoreType, FTM_SET_FWAVE_REQ_STRU* pstReq);
extern VOS_UINT32 at_ftm_fwave_setcnf(VOS_UINT32 ulErrCode);
extern VOS_VOID at_ftm_flna_store(VOS_UINT8 ucStoreType, FTM_SET_AAGC_REQ_STRU* pstReq);
extern VOS_UINT32 at_ftm_flna_setcnf(VOS_UINT32 ulErrCode);
extern VOS_VOID at_ftm_fvctcxo_store(VOS_UINT8 ucStoreType, FTM_SET_FVCTCXO_REQ_STRU* pstReq);
extern VOS_UINT32 at_ftm_fvctcxo_setcnf(VOS_UINT32 ulErrCode);
extern VOS_VOID at_ftm_bandsw_store(VOS_UINT8 ucStoreType, FTM_SET_BANDSW_REQ_STRU* pstReq);
extern VOS_UINT32 at_ftm_fchan_setcnf(VOS_UINT32 ulErrCode);
extern VOS_VOID at_ftm_ftxon_store(VOS_UINT8 ucStoreType, FTM_SET_TXON_REQ_STRU* pstReq);


extern VOS_UINT32 ftm_MsgProcInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_VOID ftm_MsgProc(MsgBlock *pMsgBlock);
extern VOS_UINT32 ftm_RttMsgProc(OS_MSG_STRU* pMsg);
extern VOS_UINT32 ftm_TimeoutMsgProc(OS_MSG_STRU* pMsg);
extern VOS_UINT32 ftm_CmdMsgProc(OS_MSG_STRU* pMsg);
extern VOS_UINT32 at_ftm_fipstart_timeout(VOS_VOID);
extern VOS_VOID ftm_mailbox_ltect_cb(MAILBOX_INT_TYPE_E enIntType);
extern VOS_VOID ftm_mailbox_ltebt_cb(MAILBOX_INT_TYPE_E enIntType);
extern VOS_VOID ftm_mailbox_tdsct_cb(MAILBOX_INT_TYPE_E enIntType);
extern VOS_VOID ftm_mailbox_tdsbt_cb(MAILBOX_INT_TYPE_E enIntType);
extern VOS_UINT32 ftm_mailbox_msgproc(MAILBOX_SERVICE_TYPE_E enMbxType);

extern VOS_UINT32 SystemDataTdRead(FTM_SCALIB_SYSTEM_SETTING_STRU * pstSystemInfo);
extern VOS_UINT32 SystemDataTdWrite(FTM_SCALIB_SYSTEM_SETTING_STRU * pstSystemInfo);
extern VOS_UINT32 SystemDataTd2Dsp(FTM_SCALIB_SYSTEM_SETTING_STRU * pstSystemInfo);
extern VOS_UINT32 SetApcflagTd2Dsp(FTM_SCALIB_APCOFFSET_SETTING_STRU * pstSystemInfo);
extern VOS_UINT32 SystemDataInit(VOS_UINT32 bandType, VOS_UINT32 dataType);
extern VOS_UINT32 DHI_getCurrentCellInfo(FTM_SCELLINFO_STRU * currentCellInfo);
extern VOS_VOID StartRFAdjust(VOS_VOID);
extern VOS_VOID FinishRFAdjust(VOS_VOID);
extern VOS_UINT32 SetApcoffsetFlag(VOS_CHAR * calibData);
extern VOS_UINT32 SetCalibParamInBuffer(VOS_UINT32 bandType, VOS_UINT32 dataType, VOS_CHAR * calibData, VOS_UINT16 dataLen);
extern VOS_UINT8 atr05_51transAsciiCharIntoHex(VOS_CHAR asciiChar);
extern VOS_UINT32 SetScalibPara(FTM_SET_SCALIB_REQ_STRU * pstFtmReq, FTM_SET_SCALIB_CNF_STRU * pstCnf);
extern VOS_VOID atr05_72translateAsciiCharIntoTpdu(VOS_CHAR * asciiChar, VOS_UINT8 * tpduResult,
                                           VOS_UINT16 asciiCharLength, VOS_UINT16 maxOutputDataLen);


#ifdef __cplusplus
}
#endif

#endif /* __FTM_CT_H__ */


