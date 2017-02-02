

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifndef BIG_ENDIAN
#define BIG_ENDIAN 1
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_COMM_FUNC_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "AtXpdsInterface.h"
#include "TafXpdsCtx.h"
#include "TafXpdsMntn.h"
#include "TafXpdsSndAt.h"
#include "TafSdcCtx.h"
#include "TafXpdsSndXsms.h"
#include "TafXpdsSndCas.h"
#include "TafXpdsCommFunc.h"



#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

const VOS_FLOAT g_sfPnPhaseMatchTable[64] =
{
    1   ,1.125   ,1.25   ,1.375   ,1.5   ,1.625   ,1.75   ,1.875   ,
    2   ,2.25    ,2.5    ,2.75    ,3     ,3.25    ,3.5    ,3.75    ,
    4   ,4.5     ,5      ,5.5     ,6     ,6.5     ,7      ,7.5     ,
    8   ,9       ,10     ,11      ,12    ,13      ,14     ,15      ,
    16  ,18      ,20     ,22      ,24    ,26      ,28     ,30      ,
    32  ,36      ,40     ,44      ,48    ,52      ,56     ,60      ,
    64  ,72      ,80     ,88      ,96    ,104     ,112    ,120     ,
    128 ,144     ,160    ,176     ,192   ,208     ,224    ,240
};

TAF_XPDS_RSLT_REASON_ITEM_STRU          g_astTafXpdsRlstReasonMapItem[] =
{
    {TAF_XPDS_PROC_RSLT_AT_STOP           , TAF_XPDS_CANCEL_REASON_USER_CANCEL           },
    {TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT , TAF_XPDS_CANCEL_REASON_PDE_DISCONNECT        },
    {TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT , TAF_XPDS_CANCEL_REASON_MPC_DISCONNECT        },
    {TAF_XPDS_PROC_RSLT_PDE_REJECT        , TAF_XPDS_CANCEL_REASON_PDE_REJ_POS_SESSION   },
    {TAF_XPDS_PROC_RSLT_IS801_TIMEOUT     , TAF_XPDS_CANCEL_REASON_IS801_SESSION_TIME_OUT},
    {TAF_XPDS_MPC_PROC_RSLT_TIMER_OUT     , TAF_XPDS_CANCEL_REASON_MPC_RSP_TIME_OUT      },
};

/*****************************************************************************
  3 Function Definitions
*****************************************************************************/

VOS_UINT32 TAF_XPDS_ConvertPrefRespQualValueToTimerLimitLen(
    VOS_UINT8                           ucPrefRespQual
)
{
    VOS_UINT32                          ulTimerLen;

    ulTimerLen = 0;

    switch (ucPrefRespQual)
    {
        case 0x00:
            ulTimerLen = 2 * 1000;
            break;

        case 0x01:
            ulTimerLen = 4 * 1000;
            break;

        case 0x02:
            ulTimerLen = 8 * 1000;
            break;

        case 0x03:
            ulTimerLen = 16 * 1000;
            break;

        case 0x04:
            ulTimerLen = 32 * 1000;
            break;

        case 0x05:
            ulTimerLen = 64 * 1000;
            break;

        case 0x06:
            ulTimerLen = 128 * 1000;
            break;

        case 0x07:
            ulTimerLen = 256 * 1000;
            break;

        default:
            break;
    }

    return ulTimerLen;
}


VOS_VOID TAF_XPDS_GetPnbyPhaseID(
    VOS_UINT16                          usPilotPN,
    TAF_XPDS_CAS_RPT_PILOT_BUFF_STRU   *pstCasRptPilotBuff
)
{
    VOS_UINT32                          ulLoopCount;

    for (ulLoopCount = 0; ulLoopCount < pstCasRptPilotBuff->ulPilotMeasNum; ulLoopCount++)
    {
        if (usPilotPN == pstCasRptPilotBuff->astPilotMeasInfo[ulLoopCount].usPilotPN)
        {
            pstCasRptPilotBuff->aulPnPhasebuff[pstCasRptPilotBuff->ulPnPhasebuffNum] = pstCasRptPilotBuff->astPilotMeasInfo[ulLoopCount].ulPnPhase;

            pstCasRptPilotBuff->ulPnPhasebuffNum++;

            if (TAF_XPDS_PILOT_PHASE_BUFF_MAX <= pstCasRptPilotBuff->ulPnPhasebuffNum)
            {
                return;
            }
        }
    }

    return;
}


VOS_FLOAT TAF_XPDS_CalcDataVar
(
    VOS_UINT32                          ulDataNum,
    VOS_UINT32                         *pulData
)
{
    VOS_FLOAT                           sfAvrg      = 0.0F;
    VOS_UINT32                          ulIndex     = 0;
    VOS_UINT32                          ulSum       = 0;
    VOS_FLOAT                           sfVarSum    = 0.0F;

    if (0 == ulDataNum)
    {
        return 0.0F;
    }

    /* ����ƽ��ֵ */
    for (ulIndex = 0; ulIndex < ulDataNum; ulIndex++)
    {
        ulSum += pulData[ulIndex];
    }

    sfAvrg = (VOS_FLOAT)ulSum / ulDataNum;

    /* ���㷽�� */
    for (ulIndex = 0; ulIndex < ulDataNum; ulIndex++)
    {
        sfVarSum += ((pulData[ulIndex] - sfAvrg) * (pulData[ulIndex] - sfAvrg));
    }

    return (sfVarSum / ulDataNum);

}


VOS_FLOAT TAF_XPDS_SquareRoot(VOS_FLOAT sfNumber)
{
    VOS_UINT32                      ulMagic = 0;
    VOS_FLOAT                       sfSqrt;
    VOS_FLOAT                       sfOffset;
    const VOS_FLOAT                 sfThreeHalf = 1.5F;

    sfOffset    = 0.5F * sfNumber;
    sfSqrt      = sfNumber;
    ulMagic     = *(VOS_UINT32*)&sfSqrt;
    ulMagic     = 0x5F3759DF - (ulMagic >> 1);
    sfSqrt      = *(VOS_FLOAT*)&ulMagic;

    /* ����1 */
    sfSqrt      = sfSqrt * (sfThreeHalf - (sfOffset * sfSqrt * sfSqrt));

    /* ����2 */
    sfSqrt      = sfSqrt * (sfThreeHalf - (sfOffset * sfSqrt * sfSqrt));

    return (sfSqrt * sfNumber);

}


VOS_UINT8 TAF_XPDS_CalcRmsErrPhase(
    VOS_FLOAT                           sfSqrt
)
{
    VOS_UINT8                           ucLoop = 0;

    if (1.0 > sfSqrt)
    {
        return 0;
    }

    for (ucLoop = 0; ucLoop < 64; ucLoop++)
    {
        if (g_sfPnPhaseMatchTable[ucLoop] > sfSqrt)
        {
            return ucLoop;
        }
    }

    return 63;
}


VOS_UINT8 TAF_XPDS_CalcPnPhaseSqrt(
    VOS_UINT32                         *pulData,
    VOS_UINT32                          ulDataLen
)
{
    VOS_FLOAT                           sfVar       = 0.0F;
    VOS_FLOAT                           sfChipSqrt  = 0.0F;
    VOS_FLOAT                           sfMeterSqrt = 0.0F;

    sfVar   = TAF_XPDS_CalcDataVar(ulDataLen, pulData);

    sfChipSqrt  = TAF_XPDS_SquareRoot(sfVar);

    /* ��SQRT(CHIP ת���� METER) */
    sfMeterSqrt = sfChipSqrt * 300 / 1.2288F;

    /* ���õ�RMS_ERR_PHASE */
    return TAF_XPDS_CalcRmsErrPhase(sfMeterSqrt / 16.0F);

}


VOS_VOID TAF_XPDS_UpdatePpmInGlobal(VOS_VOID)
{
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU        *pstPilotInfo;
    TAF_XPDS_CAS_RPT_PILOT_BUFF_STRU                  *pstCasRptPilotBuff;
    VOS_UINT8                                          ucPilotCalcValue;
    VOS_UINT32                                         ulLoopCount;

    pstPilotInfo = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);

    pstCasRptPilotBuff = &pstPilotInfo->stCasRptPilotBuff;

    if (TAF_XPDS_PILOT_MEAS_BUFF_MAX < pstCasRptPilotBuff->ulPilotMeasNum)
    {
        pstCasRptPilotBuff->ulPilotMeasNum = TAF_XPDS_PILOT_MEAS_BUFF_MAX;
    }

    if (pstPilotInfo->ucNumOfPilotP > TAF_XPDS_RL_PHASE_PILREC_MAX)
    {
        pstPilotInfo->ucNumOfPilotP = TAF_XPDS_RL_PHASE_PILREC_MAX;
    }

    /* ��������pilot phase������ */
    /* ����pn offsetȡ������ph phase ���㷽�� */
    for (ulLoopCount = 0; ulLoopCount < pstPilotInfo->ucNumOfPilotP; ulLoopCount++)
    {
        /* ����pn phase IDȡ��ȫ��pn phase*/
        pstCasRptPilotBuff->ulPnPhasebuffNum = 0;

        TAF_XPDS_GetPnbyPhaseID(pstPilotInfo->astPilotRec[ulLoopCount].usPilotPN,
                                     pstCasRptPilotBuff);

        ucPilotCalcValue = TAF_XPDS_CalcPnPhaseSqrt(pstCasRptPilotBuff->aulPnPhasebuff,
                                                         pstCasRptPilotBuff->ulPnPhasebuffNum);

        pstPilotInfo->astPilotRec[ulLoopCount].ucRmsErrPhase = ucPilotCalcValue;
    }

    /* Hook Pilot Phase Info Got From CAS */
    TAF_XPDS_MNTN_TracePilotPhaseInfoCtxIndMsg();

    return;
}


VOS_UINT8 TAF_XPDS_FormatPnStrength(
    VOS_INT16                           sRefPnStrength
)
{
    VOS_INT16                           sPnStrengthTemp;


    sPnStrengthTemp = (sRefPnStrength / -4);

    if (TAF_XPDS_MIN_PILOT_STRENGTH_VALUE > sPnStrengthTemp)
    {
        sPnStrengthTemp = TAF_XPDS_MIN_PILOT_STRENGTH_VALUE;
    }
    else if (TAF_XPDS_MAX_PILOT_STRENGTH_VALUE < sPnStrengthTemp)
    {
        sPnStrengthTemp = TAF_XPDS_MAX_PILOT_STRENGTH_VALUE;
    }
    else
    {
    }

    return (VOS_UINT8)sPnStrengthTemp;
}


VOS_UINT8 TAF_XPDS_FormatServFreqRssi(
    VOS_INT16                           sServFreqRssi
)
{
    VOS_INT16                           sServFreqRssiTemp;

/* The mobile station shall set this field to max (0, min(31,��(total_received_power + 110)/2))
    where total_received_power is the mean input power
    received by the mobile station on frequency CDMA_FREQ, in dB m/1. 23 MH z.
    Note that this de finition is taken from the SF_TOTAL_RX_PWR(se rving frequency total received
    power) defined in TIA/EIA-95 -B Section 6.7.2.3.2.20 :Candidate Frequency Search Report Message.
*/
    sServFreqRssiTemp = ((sServFreqRssi / 8) + 110);

    /* �� 2 ȡ���� */
    sServFreqRssiTemp = ((sServFreqRssiTemp + 1) / 2);

    if (31 < sServFreqRssiTemp)
    {
        sServFreqRssiTemp = 31;
    }

    if (0 > sServFreqRssiTemp)
    {
        sServFreqRssiTemp = 0;
    }

    return (VOS_UINT8)sServFreqRssiTemp;
}
TAF_XPDS_CANCEL_REASON_ENUM_UINT8 TAF_XPDS_FindCancelReasonByRslt(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enProcRslt
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulArraySize;

    ulArraySize = sizeof(g_astTafXpdsRlstReasonMapItem)/sizeof(g_astTafXpdsRlstReasonMapItem[0]);

    for (ulIndex = 0; ulIndex < ulArraySize; ulIndex++)
    {
        if (enProcRslt == g_astTafXpdsRlstReasonMapItem[ulIndex].enProcRslt)
        {
            return (TAF_XPDS_CANCEL_REASON_ENUM_UINT8)g_astTafXpdsRlstReasonMapItem[ulIndex].ulCancelReason;
        }
    }

    return TAF_XPDS_CANCEL_REASON_BUTT;
}

#endif

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

