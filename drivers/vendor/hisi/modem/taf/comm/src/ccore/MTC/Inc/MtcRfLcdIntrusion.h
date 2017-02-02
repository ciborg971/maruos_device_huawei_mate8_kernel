/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MtcRfLcdIntrusion.h
  �� �� ��   : ����
  ��    ��   : ��־��/Y00213812
  ��������   : 2014��03��05��
  ����޸�   :
  ��������   : MtcRfLcdIntrusion.c�ļ�ʹ�õ����ݽṹ�ͺ�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��04��05��
    ��    ��   : ��־��/Y00213812
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __MTCRFLCDINTRUSION_H__
#define __MTCRFLCDINTRUSION_H__

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 �궨��
****************************************************************************/
#define  MTC_MODEM_MAX_NUM              (3)                                     /* UE���ʹ��3��modem */
#define  MTC_RF_FREQ_MAX_NUM            MTC_RRC_GSM_MA_ARFCN_MAX_NUM            /* UE���ʹ��64����Ƶ������ */
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*******************************************************************************
 �ṹ��    : MTC_RF_SCELL_FREQ_LIST_STRU
 �ṹ˵��  : GSM�£���Ƶ�������ṹ

 1.��    ��   : 2014��03��05��
   ��    ��   : Y00213812
   �޸�����   : ������
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFreqNum;
    VOS_UINT16                          ausFreq[MTC_RF_FREQ_MAX_NUM];
}MTC_RF_FREQ_LIST_STRU;


/*******************************************************************************
 �ṹ��    : MTC_RF_USING_FREQ_LIST_STRU
 �ṹ˵��  : UE���еķ���С���б�

 1.��    ��   : 2014��03��05��
   ��    ��   : Y00213812
   �޸�����   : ������
*******************************************************************************/
typedef struct
{
    MTC_RF_FREQ_LIST_STRU               stGsmFreq;
    MTC_RF_FREQ_LIST_STRU               stGsmHoppingFreq;
    MTC_RF_FREQ_LIST_STRU               stWcdmaFreq;
    MTC_RF_FREQ_LIST_STRU               stLteFreq;
    MTC_RF_FREQ_LIST_STRU               stTdsFreq;
}MTC_RF_USING_FREQ_LIST_STRU;

/*******************************************************************************
 �ṹ��    : MTC_MODEM_FREQ_LIST_STRU
 �ṹ˵��  : UE���еķ���С���б�

 1.��    ��   : 2014��03��05��
   ��    ��   : Y00213812
   �޸�����   : ������
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulScellFreq;
    MTC_RF_FREQ_LIST_STRU               stGsmHoppingFreq;
    MTC_RF_FREQ_LIST_STRU               stNcellFreq;
}MTC_MODEM_FREQ_LIST_STRU;

/*******************************************************************************
 �ṹ��    : MTC_MODEM_MIPI_CLK_PRI_STRU
 �ṹ˵��  : MODEM��MIPICLKλͼ���ȼ�

 1.��    ��   : 2014��03��05��
   ��    ��   : Y00213812
   �޸�����   : ������
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usPriScellMipiClkBitMap;
    VOS_UINT16                          usPriHoppingMipiClkBitMap;
    VOS_UINT16                          usPriNcellMipiClkBitMap;
    VOS_UINT16                          usSecScellMipiClkBitMap;
    VOS_UINT16                          usSecHoppingMipiClkBitMap;
    VOS_UINT16                          usSecNcellMipiClkBitMap;

}MTC_MODEM_MIPI_CLK_PRI_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID MTC_VerdictModemBitMapPri(
    MTC_MODEM_MIPI_CLK_PRI_STRU        *pstMomdemPri
);

VOS_VOID MTC_SndMtaMipiClkInfoInd(
    VOS_UINT16                          usMipiClk
);

VOS_VOID MTC_RcvRrcUsingFreqInd(VOS_VOID *pMsg);

VOS_UINT16 MTC_GetInterBitMap(
    VOS_UINT32                          ulFreq
);

VOS_UINT16 MTC_ProcScellClkBitMap(
    VOS_UINT32                          ulScellFreq
);

VOS_UINT16 MTC_ProcHoppingClkBitMap(
    MTC_RF_FREQ_LIST_STRU              *pstFreq
);

VOS_UINT16 MTC_ProcNcellClkBitMap(
    MTC_RF_FREQ_LIST_STRU              *pstFreq
);

VOS_UINT16 MTC_ProcLcdMipiClkBitMap(
    MTC_MODEM_MIPI_CLK_PRI_STRU        *pstMomdemPri
);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


