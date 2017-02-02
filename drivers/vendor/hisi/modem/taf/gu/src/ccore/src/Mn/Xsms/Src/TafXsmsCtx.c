/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsXXXX.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��10��31��
  ��������   : 1X SMS(Short Message Service)�����ʼ����������ں�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafXsmsCtx.h"
#include "TafFsm.h"
#include "TafXsmsTimer.h"
#include "NVIM_Interface.h"
#include "TafXsmsMsgProc.h"
#include "TafCdmaPlusTranslate.h"
#include "UsimPsInterface.h"
#include "TafStdlib.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_CTX_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* MT ��ȫ�ֱ������� */
TAF_XSMS_MSG_MT_REC_STRU                g_stTafXsmsMtRec;
TAF_XSMS_MT_CTX_STRU                    g_stTafXsmsMtCtx;

/* MO ��ȫ�ֱ������� */
TAF_XSMS_MSG_MO_REC_STRU                g_stTafXsmsMoRec;
TAF_XSMS_MO_CTX_STRU                    g_stTafXsmsMoCtx;

/* AP ����Ŵ洢����FLAG */
TAF_XSMS_CCF_AP_MEM_FULL_ENUM8          g_enCcfMemFullFlag = TAF_XSMS_CCF_AP_MEM_NOT_FULL;

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : TAF_XSMS_XXXXX
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE -- ע��ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XSMS_MSG_MO_REC_STRU* TAF_XSMS_MoGetRecAddr(VOS_VOID)
{
    return &g_stTafXsmsMoRec;
}


TAF_XSMS_MSG_MT_REC_STRU* TAF_XSMS_MtGetRecAddr(VOS_VOID)
{
    return &g_stTafXsmsMtRec;
}




TAF_XSMS_MO_CTX_STRU* TAF_XSMS_MoGetCtxAddr(VOS_VOID)
{
    return &(g_stTafXsmsMoCtx);
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_MtGetCtxAddr
 ��������  : ��ȡ״̬�������ĵ�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ״̬����ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��1��
    ��    ��   : l00208516s
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XSMS_MT_CTX_STRU* TAF_XSMS_MtGetCtxAddr(VOS_VOID)
{
    return &(g_stTafXsmsMtCtx);
}


TAF_XSMS_MT_FSM_CTX_STRU* TAF_XSMS_MtGetCurFsmAddr(VOS_VOID)
{
    return &(TAF_XSMS_MtGetCtxAddr()->stCurFsm);
}


TAF_XSMS_MO_FSM_CTX_STRU* TAF_XSMS_MoGetCurFsmAddr(VOS_VOID)
{
    return &(TAF_XSMS_MoGetCtxAddr()->stCurFsm);
}


VOS_VOID TAF_XSMS_MtSetCurrFsmState(VOS_UINT32 ulCurrState)
{
    TAF_XSMS_MT_FSM_CTX_STRU           *pstCurFsm;

    /* ��ȡ��ǰ��״̬��Ϣ */
    pstCurFsm               = TAF_XSMS_MtGetCurFsmAddr();

    /* ���õ�ǰ״̬ */
    pstCurFsm->enFsmId      = ulCurrState;

    TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_MT_FSM, (VOS_UINT8*)&ulCurrState, sizeof(TAF_XSMS_MT_FSM_ID_ENUM_UINT32));

    return;
}


VOS_VOID TAF_XSMS_MoSetCurrFsmState(VOS_UINT32 ulCurrState)
{
    TAF_XSMS_MO_FSM_CTX_STRU                *pstCurFsm;

    /* ��ȡ��ǰ��״̬��Ϣ */
    pstCurFsm           = TAF_XSMS_MoGetCurFsmAddr();

    /* ���õ�ǰ״̬ */
    pstCurFsm->enFsmId  = ulCurrState;

    TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_MO_FSM, (VOS_UINT8*)&ulCurrState, sizeof(TAF_XSMS_MO_FSM_ID_ENUM_UINT32));

    return;
}


TAF_XSMS_MO_FSM_ID_ENUM_UINT32 TAF_XSMS_MoGetCurrFsmId(VOS_VOID)
{
    return (TAF_XSMS_MoGetCtxAddr()->stCurFsm.enFsmId);
}


TAF_XSMS_MT_FSM_ID_ENUM_UINT32 TAF_XSMS_MtGetCurrFsmId(VOS_VOID)
{
    return (TAF_XSMS_MtGetCtxAddr()->stCurFsm.enFsmId);
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MtGetStaTblAddr
 ��������  : ����MT״̬����ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MT״̬����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_STA_STRU* TAF_XSMS_MoGetStaTblAddr(VOS_VOID)
{
    return g_astTafXsmsMoStaTbl;
}


VOS_VOID TAF_XSMS_MoIdleInit(VOS_VOID)
{
    TAF_XSMS_MO_CTX_STRU               *pstXsmsMoCtx = VOS_NULL_PTR;

    pstXsmsMoCtx = TAF_XSMS_MoGetCtxAddr();

    /* ��XSMS��·��־λ��ΪFALSE */
    TAF_SDC_SetXsmsCallExistFlg(VOS_FALSE);

    /* ��ʼ��MOȫ�ֱ��� */
    TAF_XSMS_MoInitGobal();

    /* ��ʼ��MO״̬��ACT�� */
    pstXsmsMoCtx->stCurFsm.pstFsmDesc   = TAF_XSMS_MoGetStaTblAddr();

    /* ��ʼ��MO״̬ */
    TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_IDLE_STATE);

    /* ֹͣMO���ж�ʱ�� */
    TAF_XSMS_MoStopAllTimer();

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MtGetStaTblAddr
 ��������  : ����MT״̬����ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MT״̬����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_STA_STRU* TAF_XSMS_MtGetStaTblAddr(VOS_VOID)
{
    return g_astTafXsmsMtStaTbl;
}


VOS_VOID TAF_XSMS_MtIdleInit(VOS_VOID)
{
    TAF_XSMS_MT_CTX_STRU               *pstXsmsMtCtx = VOS_NULL_PTR;

    pstXsmsMtCtx = TAF_XSMS_MtGetCtxAddr();

    /* �����ǰ����·ʱXSMS�������ñ�־λ */
    TAF_SDC_SetXsmsCallExistFlg(VOS_FALSE);

    /* ��ʼMT��ȫ�ֱ��� */
    TAF_XSMS_MtInitGobal();

    /* ��ʼ��MT״̬��ACT�� */
    pstXsmsMtCtx->stCurFsm.pstFsmDesc = TAF_XSMS_MtGetStaTblAddr();

    /* ��ʼ�� MT״̬ */
    TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_IDLE_STATE);

    /* ֹͣMT���ж�ʱ�� */
    TAF_XSMS_MtStopAllTimer();

    return;
}
VOS_VOID TAF_XSMS_MoStopAllTimer(VOS_VOID)
{
    VOS_UINT32                          ulMoTimerId;

    for (ulMoTimerId = TI_TAF_XSMS_TIMER_MO_IDLE;
         ulMoTimerId < TI_TAF_XSMS_TIMER_BUTT;
         ulMoTimerId++)
    {
        if (VOS_NULL_PTR != g_astXsmsTimer[ulMoTimerId])
        {
            TAF_XSMS_StopTimer(ulMoTimerId);
        }
    }

    return;
}



VOS_VOID TAF_XSMS_MtStopAllTimer(VOS_VOID)
{
    VOS_UINT32                              ulMtTimerId;

    for (ulMtTimerId = TI_TAF_XSMS_TIMER_MT_IDLE;
         ulMtTimerId < TI_TAF_XSMS_TIMER_MT_END_LINK_PROTECT;
         ulMtTimerId++)
    {
        if (VOS_NULL_PTR != g_astXsmsTimer[ulMtTimerId])
        {
            TAF_XSMS_StopTimer(ulMtTimerId);
        }
    }

    return;
}


VOS_VOID TAF_XSMS_MoInitGobal(VOS_VOID)
{
    VOS_UINT32                          ulTmp;

    ulTmp = (VOS_UINT32)&g_stTafXsmsMoRec.st1xSms;

    /* ���NV��֮�������ȫ�ֱ��� */
    PS_MEM_SET((VOS_VOID *)ulTmp, 0, sizeof(TAF_XSMS_MSG_MO_REC_STRU) - sizeof(TAF_NVIM_1X_XSMS_CFG_STRU) - 4*sizeof(VOS_UINT8));

    PS_MEM_SET(&g_stTafXsmsMoCtx, 0, sizeof(g_stTafXsmsMoCtx));

    return;
}
VOS_VOID TAF_XSMS_MtInitGobal(VOS_VOID)
{
    VOS_UINT32                          ulTmp;

    ulTmp = (VOS_UINT32)&g_stTafXsmsMtRec.stTlAck;

    /* ���NV��֮�������ȫ�ֱ��� */
    PS_MEM_SET((VOS_VOID *)ulTmp, 0, sizeof(TAF_XSMS_MSG_MT_REC_STRU) - sizeof(TAF_NVIM_1X_XSMS_CFG_STRU));

    PS_MEM_SET(&g_stTafXsmsMtCtx, 0, sizeof(g_stTafXsmsMtCtx));

    return;
}

/*****************************************************************************
 �� �� ��  :TAF_XSMS_GetReqCtrlInfoAddr
 ��������  :��ȡXSMS AT���������Ϣ
 �������  :��
 �������  :��
 �� �� ֵ  :����XSMS AT���������Ϣ�ĵ�ַ
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_XSMS_CTRL_INFO_STRU * TAF_XSMS_GetReqCtrlInfoAddr(VOS_VOID)
{
    return &g_stTafXsmsReqCtrlInfo;
}

/*****************************************************************************
 �� �� ��  :TAF_XSMS_GetReqCtrlInfoAddr
 ��������  :��ȡXSMS��ʼ�����������Ϣ
 �������  :��
 �������  :��
 �� �� ֵ  :����XSMS ��ʼ��������Ϣ�ĵ�ַ
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_XSMS_INIT_CTRL_INFO_STRU * TAF_XSMS_GetInitCtrlInfoAddr(VOS_VOID)
{
    return &g_stTafXsmsInitCtrlInfo;
}

/*****************************************************************************
 �� �� ��  :TAF_XSMS_ReqCtrlInfoClear
 ��������  :���XSMS AT���������Ϣ
 �������  :��
 �������  :��
 �� �� ֵ  :����XSMS AT���������Ϣ�ĵ�ַ
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_ReqCtrlInfoClear(VOS_VOID)
{
    PS_MEM_SET(TAF_XSMS_GetReqCtrlInfoAddr(), 0, sizeof(TAF_XSMS_CTRL_INFO_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  :TAF_XSMS_InitCtrlInfoClear
 ��������  :���XSMS��ʼ�����������Ϣ
 �������  :��
 �������  :��
 �� �� ֵ  :����XSMS ��ʼ��������Ϣ�ĵ�ַ
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_InitCtrlInfoClear(VOS_VOID)
{
    PS_MEM_SET(TAF_XSMS_GetInitCtrlInfoAddr(), 0, sizeof(TAF_XSMS_INIT_CTRL_INFO_STRU));

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_MoGetBearSeqNum
 ��������  : ��ȡREPLY SEQ NUM��ֵ
 �������  : pstMoRec:MO�Ŀ��ƽṹ��
 �������  : ��
 �� �� ֵ  : REPLY SEQ NUM��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_XSMS_MoGetBearSeqNum(TAF_XSMS_MSG_MO_REC_STRU *pstMoRec)
{
    VOS_UINT8 ucBearReqNum;

    ucBearReqNum            = pstMoRec->ucReplySeq % TAF_XSMS_BEAER_SEQ_NUM_MAX;

    pstMoRec->ucReplySeq    = ucBearReqNum + 1;

    TAF_XSMS_INFO_LOG1(" THE CURRENT SEQ NUM IS", ucBearReqNum);

    return ucBearReqNum;
}


VOS_VOID TAF_XSMS_InitFsmCtx_Main(VOS_VOID)
{
    return;
}

VOS_VOID TAF_XSMS_RegMoFsm(VOS_VOID)
{
    g_stTafXsmsMoFsmDesc.pStaTable          = g_astTafXsmsMoStaTbl;
    g_stTafXsmsMoFsmDesc.ulSize             = TAF_XSMS_GetMoFsmTblNum();

    /* ������״̬��ע�� */
    TAF_FSM_RegisterFsm(&g_stTafXsmsMoFsmDesc,
                         "TAF_XSMS:FSM:MainProcess",
                         g_stTafXsmsMoFsmDesc.ulSize,
                         g_astTafXsmsMoStaTbl,
                         VOS_NULL_PTR,
                         TAF_XSMS_InitFsmCtx_Main);

    return;
}
VOS_VOID TAF_XSMS_RegMtFsm(VOS_VOID)
{
    g_stTafXsmsMtFsmDesc.pStaTable          = g_astTafXsmsMtStaTbl;
    g_stTafXsmsMtFsmDesc.ulSize             = TAF_XSMS_GetMtFsmTblNum();

    /* ������״̬��ע�� */
    TAF_FSM_RegisterFsm(&g_stTafXsmsMtFsmDesc,
                         "TAF_XSMS:FSM:MainProcess",
                         g_stTafXsmsMtFsmDesc.ulSize,
                         g_astTafXsmsMtStaTbl,
                         VOS_NULL_PTR,
                         TAF_XSMS_InitFsmCtx_Main);

    return;
}
VOS_VOID TAF_XSMS_SetApMemFullFlag(
    TAF_XSMS_AP_MEM_FULL_ENUM_UINT8     enAPMemFullFlag
)
{
    if (TAF_XSMS_AP_MEM_BUTT <= enAPMemFullFlag)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_SetApMemFullFlag: WRONG enAPMemFullFlag");
        return;
    }

    if (TAF_XSMS_AP_MEM_FULL == enAPMemFullFlag)
    {
        g_enCcfMemFullFlag = TAF_XSMS_CCF_AP_MEM_FULL;
    }
    else
    {

        g_enCcfMemFullFlag = TAF_XSMS_CCF_AP_MEM_NOT_FULL;
    }

    return;
}


TAF_XSMS_CCF_AP_MEM_FULL_ENUM8 TAF_XSMS_GetApMemFullFlag(VOS_VOID)
{
    return g_enCcfMemFullFlag;
}


VOS_VOID TAF_XSMS_TranslatePlusToNum(
    TAF_XSMS_ADDR_STRU                 *pstXsmsAddr
)
{

    VOS_UINT16                                              usCurMcc;
    VOS_UINT16                                              usHomeMcc;
    TAF_SDC_1X_SYS_INFO_STRU                               *pstSdc1xSysInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucCurDigitsLen  = 0;
    TAF_PLUS_TRANSLATE_NUM_TYPE_ENUM_U8                     enNumType;

    ucCurDigitsLen    = (VOS_UINT8)pstXsmsAddr->ulNumberOfDigits;

    /*��ȡmcc */
    pstSdc1xSysInfo   = TAF_SDC_Get1xSysInfo();

    usCurMcc          = TAF_STD_TransformBcdMccToDeciDigit(pstSdc1xSysInfo->stServiceInfo.ulMcc);

    /* �����ǰ�����ǹ��ʺ��������8BITS ASCII,ת����DTMF  */
    /* Used only when digitMode is 8-bit.
     * To specify an international address, use the following:
     * digitMode = TAF_XSMS_DIGIT_MODE_8_BIT
     * numberMode = TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK
     * numberType = TAF_XSMS_NUMBER_TYPE_INTERNATIONAL_OR_DATA_IP
     * numberPlan = TAF_XSMS_NUMBER_PLAN_TELEPHONY
     * numberOfDigits = number of digits
     * digits = ASCII digits, e.g. '1', '2', '3'3, '4', and '5'
     */
    if ((TAF_XSMS_DIGIT_MODE_8_BIT                     == pstXsmsAddr->enDigitMode)
     && (TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK         == pstXsmsAddr->enNumberMode)
     && (TAF_XSMS_NUMBER_PLAN_TELEPHONY                == pstXsmsAddr->enNumberPlan)
     && (TAF_XSMS_NUMBER_TYPE_INTERNATIONAL_OR_DATA_IP == pstXsmsAddr->enNumberType))
    {
        if (TAF_XSMS_ADDRESS_MAX < pstXsmsAddr->ulNumberOfDigits)
        {
            TAF_XSMS_ERROR_LOG1("TAF_XSMS_TranslatePlusToNum: num is too many", pstXsmsAddr->ulNumberOfDigits);
            return;
        }
        /* ��ǰ�Ķ���Ĭ��ֻ֧���ڴ�½�Ͱ��ŷ��ͣ�Xģ�ֻ��ڹ��������ط��г�GUģʽ */
        /* ��½ ���� ����*/
        /* ��ȡHOME MCC */
        usHomeMcc = (VOS_UINT16)TAF_XSMS_GetHomeMcc();

        if ((460 != usCurMcc)
         && (455 != usCurMcc))
        {
            /* �ڷ��й��Ͱ��ţ���ӡ��������ת�� */
            TAF_XSMS_ERROR_LOG("TAF_XSMS_TranslatePlusToNum : home mcc is not China/Macao");
        }

        enNumType = TAF_PLUS_TRANSLATE_NUM_INTERNATIONAL;

        TAF_TranslatePlusToNum(usHomeMcc,
                               TAF_PLUS_TRANSLATE_DIAL_TYPE_SMS,
                               &enNumType,
                               pstXsmsAddr->aucDigits,
                               &ucCurDigitsLen);

        pstXsmsAddr->ulNumberOfDigits   = ucCurDigitsLen;

        /* ��ASCII ת����DTMF */
        TAF_XSMS_TransAsciiToDtmf(pstXsmsAddr->aucDigits,
                                  pstXsmsAddr->aucDigits,
                                  ucCurDigitsLen);

        pstXsmsAddr->enDigitMode    = TAF_XSMS_DIGIT_MODE_4_BIT;
        pstXsmsAddr->enNumberMode   = TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK;
        pstXsmsAddr->enNumberPlan   = TAF_XSMS_NUMBER_PLAN_UNKNOWN;
        pstXsmsAddr->enNumberType   = TAF_XSMS_NUMBER_TYPE_UNKNOWN;

    }
    return ;
}
VOS_UINT32 TAF_XSMS_GetHomeMcc(
    VOS_VOID
)
{
    VOS_UINT8                           aucImsiData[10] = {0};
    VOS_UINT16                          usMcc           = 460;
    VOS_UINT32                          ulDataLen       = 0;
    VOS_UINT8                          *pucImsiData    = VOS_NULL_PTR;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType;

    /* �õ����ļ��е�IMSI */
    enCsimType =  TAF_SDC_GetCsimType();

    if (TAF_SDC_SIM_TYPE_CSIM == enCsimType)
    {
        if (VOS_OK != USIMM_GetCachedFile(USIMM_CSIM_EFIMSIM_STR, &ulDataLen, &pucImsiData, USIMM_CDMA_APP))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_GetHomeMcc: USIMM_GetCachedFile ERR");
            return usMcc;
        }
    }
    else if (TAF_SDC_SIM_TYPE_UIM == enCsimType)
    {
        if (VOS_OK != USIMM_GetCachedFile(USIMM_CDMA_EFIMSIM_STR, &ulDataLen, &pucImsiData, USIMM_CDMA_APP))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_GetHomeMcc: USIMM_GetCachedFile ERR");
            return usMcc;
        }
    }
    else
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_GetHomeMcc: WRONG CARD TYPE");
        return usMcc;
    }

    if (VOS_NULL_PTR == pucImsiData)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_GetHomeMcc: pucImsiData null");
        return usMcc;
    }

    PS_MEM_CPY(aucImsiData, pucImsiData, 10);

    usMcc       = ((aucImsiData[9] & 0x03) << 8) + aucImsiData[8];

    usMcc       = TAF_XSMS_GET_MCC(usMcc);

    return usMcc;
}
VOS_VOID TAF_XSMS_TransAsciiToDtmf(
    VOS_UINT8                          *pucSrcData,
    VOS_UINT8                          *pucDestData,
    VOS_UINT8                           ucLen
)
{
    VOS_UINT16                          usIndex = 0;

    for (; usIndex < ucLen; usIndex++)
    {

        if ((0x30 > pucSrcData[usIndex])
        ||  (0x39 < pucSrcData[usIndex]))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_TransAsciiToDtmf : address is not num");

            return;
        }

        if (0 == (pucSrcData[usIndex] % 16))
        {
            pucDestData[usIndex] = 0x0a;
        }
        else
        {
            pucDestData[usIndex] = pucSrcData[usIndex] % 16;
        }
    }

    return;
}


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



