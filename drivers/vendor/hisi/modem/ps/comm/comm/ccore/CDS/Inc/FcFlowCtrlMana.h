

#ifndef __FC_FLOWCTRL_MANA_H__
#define __FC_FLOWCTRL_MANA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define QOS_FC_ENABLED_MASK                     0x01
#define QOS_FC_HIGHEST_FC_ENABLED_MASK          0x02
#define FC_CDS_DL_ENABLED_MASK                  0x04
#define QOS_FC_HIGHEST_NOTDISCARD_ENABLED_MASK  0x08

#define EN_NV_ITEM_CDS_FC_CONFIG            9042

#define FC_UL_DOWNGRADE_GAP                 100
#define FC_UL_ENTRY_THROUGHPUT_INIT         1875000    /* 150Mbps */

#define FC_UL_THROUGHPUT_THRES_CNT          13          /* FC_UL_THROUGHPUT_THRES_CNT_NV+1 */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
   5 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : FC_LTE_CPU_CONTROL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����LTE CPU���ؿ��ƽṹ
*****************************************************************************/
typedef struct FC_LTE_CPU_CONTROL
{
    VOS_UINT32          ulFirstDelay;           /* �ӳٽ�������״̬�������������ڸ�����ֵ�Ž������� */
    VOS_UINT32          ulUlDownRate;           /* ���н��ٲ����ٷֱ� */
    VOS_UINT32          ulUlUpRate;             /* �������ٲ����ٷֱ� */
    VOS_UINT32          ulUlMinBsr;             /* ���н������� Bsr */
    VOS_UINT32          ulHqDownRate;           /* HARQ���ٲ����ٷֱ� */
    VOS_UINT32          ulHqUpRate;             /* HARQ���ٲ����ٷֱ� */
    VOS_UINT32          ulHqMaxDiscardRate;     /* HARQ�������� */
    VOS_UINT32          ulDowngradeThres;       /* ������ֵ��CPUռ���ʸ��ڸ�ֵʱ��MAC�������з������� */
    VOS_UINT32          ulUpgradeThres;         /* ������ֵ��CPUռ���ʵ��ڸ�ֵʱ��MAC�������з������� */
} FC_LTE_CPU_CONTROL_STRU;

/*****************************************************************************
 �ṹ��    : FC_LTE_TEMPERATURE_CONTROL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����LTE �¿ؿ��ƽṹ
*****************************************************************************/
typedef struct FC_LTE_TEMPERATURE_CONTROL
{
    VOS_UINT8           ucInitialPos;           /* ���ٿ�ʼλ��0~11, Ĭ��4 */
    VOS_UINT8           ucAvailCnt;
    VOS_UINT8           ucBsrThresCnt;          /* ��ڿ��Ƶ���ʼλ�� */
    VOS_UINT8           ucCurrPos;
    VOS_UINT32          ulTemperSteps[FC_UL_THROUGHPUT_THRES_CNT];      /* �¿����ʵ�λkbps -> BSR */
    VOS_UINT32          ulBsrTimerLen;          /* BSR�ϱ����� */
} FC_LTE_TEMPERATURE_CONTROL_STRU;

/*****************************************************************************
 �ṹ��    : FC_CDS_DL_CONTROL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����CDS���ж������ؿ��ƽṹ
*****************************************************************************/
typedef struct FC_CDS_DL_CONTROL
{
    VOS_BOOL            bDlCdsFcEnable;         /* CDS���������Ƿ�ʹ�� */
    VOS_UINT32          ulDiscardThres;         /* CDS���ж��ж������� */
    VOS_UINT32          ulDiscardRate;          /* ������ */
} FC_CDS_DL_CONTROL_STRU;


/*****************************************************************************
 �ṹ��    : FC_CL_STATS_INFO
 Э����  :
 ASN.1���� :
 �ṹ˵��  : C��LTE����ͳ����
*****************************************************************************/
typedef struct FC_CL_STATS_INFO
{
    VOS_UINT32              ulToLteNum;                 /* ��ΪLTEģ���� */
    VOS_UINT32              ulToGUNum;                  /* ��ΪGUģ���� */
    VOS_UINT32              ulToNullNum;                /* ����NULL������� */
    VOS_UINT32              ulToLBNum;                  /* ����LOOPBACK������� */
    VOS_UINT32              ulTemperatureDownNum;       /* �¿ؽ��ٴ��� */
    VOS_UINT32              ulTemperatureUpNum;         /* �¿����ٴ��� */
    VOS_UINT32              ulTemperatureRecoverNum;    /* �¿�ֱ�ӻָ����� */
    VOS_UINT32              ulTemperatureToLimitNum;    /* �¿ؽ��ٵ����޴��� */
    VOS_UINT32              ulTemperatureToNormalNum;   /* �¿ػָ����������� */
    VOS_UINT32              ulCpuDownNum;               /* CPU���ؽ��ٴ��� */
    VOS_UINT32              ulCpuUpNum;                 /* CPU�ָ����ٴ��� */
    VOS_UINT32              ulCpuToDownNum;             /* CPU���뽵��״̬�� */
    VOS_UINT32              ulCpuToNormalNum;           /* CPU�ָ����������� */
    VOS_UINT32              ulHqDownNum;                /* HARQ���ؽ��ٴ��� */
    VOS_UINT32              ulHqUpNum;                  /* HARQ�ָ����ٴ��� */
    VOS_UINT32              ulHqToDownNum;              /* HARQ���뽵��״̬�� */
    VOS_UINT32              ulHqToNormalNum;            /* HARQ�ָ����������� */
    VOS_UINT32              ulBelowMinBsr;              /* �ϱ������������ */
}FC_CL_STATS_INFO_STRU;


/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/
extern FC_CL_STATS_INFO_STRU    g_stFcCLStats;

/* C��LTE����ͳ�� */
#define  FC_CL_TO_LTE_STAT(n)               (g_stFcCLStats.ulToLteNum += (n))
#define  FC_CL_TO_GU_STAT(n)                (g_stFcCLStats.ulToGUNum += (n))
#define  FC_CL_TO_NULL_STAT(n)              (g_stFcCLStats.ulToNullNum += (n))
#define  FC_CL_TO_LB_STAT(n)                (g_stFcCLStats.ulToLBNum += (n))

#define  FC_CL_TEMPERATURE_DOWN_STAT(n)     (g_stFcCLStats.ulTemperatureDownNum += (n))
#define  FC_CL_TEMPERATURE_UP_STAT(n)       (g_stFcCLStats.ulTemperatureUpNum += (n))
#define  FC_CL_TEMPERATURE_RECOVER_STAT(n)  (g_stFcCLStats.ulTemperatureRecoverNum += (n))
#define  FC_CL_TEMPERATURE_TO_LIMIT_STAT(n) (g_stFcCLStats.ulTemperatureToLimitNum += (n))
#define  FC_CL_TEMPERATURE_TO_NORMAL_STAT(n)     (g_stFcCLStats.ulTemperatureToNormalNum += (n))

#define  FC_CL_CPU_DOWN_STAT(n)             (g_stFcCLStats.ulCpuDownNum += (n))
#define  FC_CL_CPU_UP_STAT(n)               (g_stFcCLStats.ulCpuUpNum += (n))
#define  FC_CL_CPU_TO_DOWN_STAT(n)          (g_stFcCLStats.ulCpuToDownNum += (n))
#define  FC_CL_CPU_TO_NORMAL_STAT(n)        (g_stFcCLStats.ulCpuToNormalNum += (n))
#define  FC_CL_HQ_DOWN_STAT(n)             (g_stFcCLStats.ulHqDownNum += (n))
#define  FC_CL_HQ_UP_STAT(n)               (g_stFcCLStats.ulHqUpNum += (n))
#define  FC_CL_HQ_TO_DOWN_STAT(n)          (g_stFcCLStats.ulHqToDownNum += (n))
#define  FC_CL_HQ_TO_NORMAL_STAT(n)        (g_stFcCLStats.ulHqToNormalNum += (n))
#define  FC_CL_BSR_BELOW_MIN_STAT(n)        (g_stFcCLStats.ulBelowMinBsr += (n))

/*****************************************************************************
  8 ��������
*****************************************************************************/
extern VOS_VOID Fc_SwitchToGu(VOS_VOID);
extern VOS_VOID Fc_SwitchToLte(VOS_VOID);
extern VOS_VOID Fc_SwitchToNull(VOS_VOID);
extern VOS_UINT32 Fc_BufferReportDiscount( VOS_UINT32 ulBufferSize );
extern VOS_VOID LUP_RelDataReq(VOS_VOID);



/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

