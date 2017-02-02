

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMsccCtx.h"
#include "PsCommonDef.h"
#include "NasMsccMntn.h"

/* Added by t00323010 for CDMA Iteration 10 2015-4-7 begin */
#include "NasMsccMlplMsplApi.h"
#include "NasMsccComFunc.h"
#include "NasMsccSysAcqStrategy.h"
#include "NasComm.h"
/* Added by t00323010 for CDMA Iteration 10 2015-4-7 end */


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_COM_FUNC_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
Function Name   :   NAS_MSCC_IsNeedPerformCLSysAcq
Description     :   The function is used to judge whether should enter CL system Acquire
                    or not
Input parameters:   None
Output parameters:  None.
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2015-04-04
        Author  :   m00312079
        Modify content :    Create
*****************************************************************************/

VOS_UINT32 NAS_MSCC_IsNeedPerformCLSysAcq(VOS_VOID)
{
    VOS_UINT32                                              ulIsHrpdAndLteBothSupported;
    VOS_UINT8                                               ucMlplMsplValidFlg;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enUsimCardStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimCardStatus;

    enUsimCardStatus                = NAS_MSCC_GetUsimCardStatus();
    enCsimCardStatus                = NAS_MSCC_GetCsimCardStatus();
    ulIsHrpdAndLteBothSupported     = NAS_MSCC_IsHrpdAndLteBothSupported();
    ucMlplMsplValidFlg              = NAS_MSCC_GetMlplMsplValidFlag();

    if ((VOS_TRUE                              == ulIsHrpdAndLteBothSupported)
     && (VOS_TRUE                              == ucMlplMsplValidFlg)
     && (NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT == enUsimCardStatus)
     && (NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_IsBgSearchHighPriSysAllowed
Description     :   This function is used to check whether BG search high priority system is allowed
Input parameters:   None
Output parameters:  None
Return Value    :   VOS_TRUE:Y
                    VOS_FALSE:N
Modify History:
    1)  Date    :   2014-4-2
        Author  :   t00323010
        Modify content :    Create for Iteration 10
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsBgSearchHighPriSysAllowed(VOS_VOID)
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimCardStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enCsimCardStatus;
    VOS_UINT8                           ucMlplMsplValidFlag;
    VOS_UINT32                          uc3gppNormalSrvFlg;
    VOS_UINT32                          ucHrpdNormalSrvFlg;

    enUsimCardStatus        = NAS_MSCC_GetUsimCardStatus();
    enCsimCardStatus        = NAS_MSCC_GetCsimCardStatus();
    ucMlplMsplValidFlag     = NAS_MSCC_GetMlplMsplValidFlag();

    if ((VOS_TRUE != NAS_MSCC_IsHrpdAndLteBothSupported())
     || (VOS_TRUE != ucMlplMsplValidFlag)
     || (NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT != enUsimCardStatus)
     || (NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT != enCsimCardStatus))
    {
        return VOS_FALSE;
    }

    /* ��LTE����ע���Ƿ�invalid for lte serviceԭ��ֵ�ܾ��� */
    if (VOS_FALSE == NAS_MSCC_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    uc3gppNormalSrvFlg  = NAS_MSCC_Is3gppNormalService();
    ucHrpdNormalSrvFlg  = NAS_MSCC_IsHrpdNormalService();

    /* LTE��HRPD��������������ֱ�ӷ��� */
    if ((VOS_FALSE == uc3gppNormalSrvFlg)
     && (VOS_FALSE == ucHrpdNormalSrvFlg))
    {
        return VOS_FALSE;
    }

    /* ��ǰ�����Ƿ��Ѿ���������ȼ����� */
    if (VOS_TRUE == NAS_MSCC_IsCampOnHighestPrioritySystem())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_IsCampOnHighestPrioritySystem
Description     :   This function is used to check whether current system have the highest priority
Input parameters:   None
Output parameters:  None
Return Value    :   VOS_TRUE:Y
                    VOS_FALSE:N
Modify History:
    1)  Date    :   2014-4-2
        Author  :   t00323010
        Modify content :    Create for Iteration 10
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsCampOnHighestPrioritySystem(VOS_VOID)
{
    NAS_MSCC_3GPP_SYS_INFO_STRU                            *pst3gppSysInfo  = VOS_NULL_PTR;
    NAS_MSCC_HRPD_SYS_INFO_STRU                            *pstHrpdSysInfo  = VOS_NULL_PTR;
    NAS_MSCC_1X_SYS_INFO_STRU                              *pst1xSysInfo    = VOS_NULL_PTR;
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                        stOutSysList;
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU                st3gppInfo;
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU                stHrpdInfo;
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                  st1xInfo;
    VOS_UINT32                                              ulReturnValue;
    VOS_UINT32                                              ulGetMsplListRslt;

    ulReturnValue       = VOS_TRUE;
    ulGetMsplListRslt   = VOS_FALSE;

    PS_MEM_SET(&stOutSysList, 0x00, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    if (VOS_TRUE == NAS_MSCC_GetHrpdCampOnFlag())
    {
        pstHrpdSysInfo = NAS_MSCC_GetHrpdSysInfoAddr();

        stHrpdInfo.enPriClassCdma2000Hrpd = pstHrpdSysInfo->enHrpdPrioClass;
        stHrpdInfo.enPriClassCdma2000Ai   = pstHrpdSysInfo->enAIPrioClass;
        stHrpdInfo.ucIsMccValid           = VOS_TRUE;
        stHrpdInfo.ulMcc                  = pstHrpdSysInfo->ulMcc;
        stHrpdInfo.ucSubNetMask           = pstHrpdSysInfo->ucSubNetMask;

        PS_MEM_CPY(stHrpdInfo.aucSectorId,
                   pstHrpdSysInfo->aucSectorId,
                   NAS_MSCC_BYTES_IN_SUBNET);

        /* ��HRPD����û���·�MCCʱ, ʹ��1X��Ϣ��ѯMLPL/MSPL��,
           ��ʹ��HRPD��Ϣ�ж��Ƿ���LTE�������ȼ����ڵ�ǰHRPD���� */
        if (NAS_MSCC_INVALID_MCC == pstHrpdSysInfo->ulMcc)
        {
            if (VOS_TRUE == NAS_MSCC_Get1xCampOnFlag())
            {
                stHrpdInfo.ucIsMccValid       = VOS_FALSE;

                pst1xSysInfo = NAS_MSCC_Get1xSysInfoAddr();

                st1xInfo.enPriClassCdma20001x = pst1xSysInfo->en1xPrioClass;
                st1xInfo.enPriClassCdma2000Ai = pst1xSysInfo->enAIPrioClass;
                st1xInfo.ulMcc                = pst1xSysInfo->ulMcc;
                st1xInfo.ulMnc                = pst1xSysInfo->ulMnc;
                st1xInfo.ucIsMccValid         = VOS_TRUE;
                st1xInfo.ucIsMncValid         = VOS_TRUE;
                st1xInfo.usNid                = pst1xSysInfo->usNid;
                st1xInfo.usSid                = pst1xSysInfo->usSid;

                ulGetMsplListRslt = NAS_MSCC_GetHigherPriMsplSysListThanHrpdBy1xLoc(&st1xInfo,
                                                        &stHrpdInfo, &stOutSysList);
            }

        }
        else
        {
            ulGetMsplListRslt = NAS_MSCC_GetHigherPriMsplSysListThanHrpd(&stHrpdInfo, &stOutSysList);
        }

        if (VOS_TRUE == ulGetMsplListRslt)
        {
            if (VOS_TRUE == NAS_MSCC_IsLteSysTypeExistInSysList(&stOutSysList))
            {
                ulReturnValue = VOS_FALSE;
            }
        }

        return ulReturnValue;
    }

    if (VOS_TRUE == NAS_MSCC_GetLteCampOnFlag())
    {
        pst3gppSysInfo = NAS_MSCC_Get3gppSysInfoAddr();

        st3gppInfo.stPlmnId.ulMcc = pst3gppSysInfo->stPlmnId.ulMcc;
        st3gppInfo.stPlmnId.ulMnc = pst3gppSysInfo->stPlmnId.ulMnc;
        st3gppInfo.enPriClass     = pst3gppSysInfo->enPrioClass;
        st3gppInfo.enSysRat       = VOS_RATMODE_LTE;

        ulGetMsplListRslt = NAS_MSCC_GetHigherPriMsplSysListThan3gpp(&st3gppInfo, &stOutSysList);

        if (VOS_TRUE == ulGetMsplListRslt)
        {
            if (VOS_TRUE == NAS_MSCC_IsHrpdSysTypeExistInSysList(&stOutSysList))
            {
                ulReturnValue = VOS_FALSE;
            }
        }

        return ulReturnValue;
    }

    return ulReturnValue;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetBsrTimerLen
Description     :   This function is used to get BSR Timer len
Input parameters:   None
Output parameters:  None
Return Value    :   VOS_UINT32:BSR Timer length

Modify History:
    1)  Date    :   2014-4-2
        Author  :   t00323010
        Modify content :    Create for Iteration 10
*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetBsrTimerLen(VOS_VOID)
{
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU                st3gppInfo;
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU                stHrpdInfo;
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                  st1xInfo;
    VOS_UINT32                                              ulBsrTimerLen;
    VOS_UINT32                                              ulGetBsrTimerLenRslt;
    NAS_MSCC_HRPD_SYS_INFO_STRU                            *pstHrpdSysInfo = VOS_NULL_PTR;
    NAS_MSCC_3GPP_SYS_INFO_STRU                            *pstLteSysInfo  = VOS_NULL_PTR;
    NAS_MSCC_1X_SYS_INFO_STRU                              *pst1xSysInfo   = VOS_NULL_PTR;

    if (VOS_TRUE == NAS_MSCC_GetBsrTimerNvimActiveFlag())
    {
        return NAS_MSCC_GetSysAcqTimerCfgAddr()->ulBsrTimerLen;
    }

    ulBsrTimerLen           = 0;
    ulGetBsrTimerLenRslt    = VOS_FALSE;

    if (VOS_TRUE == NAS_MSCC_GetLteCampOnFlag())
    {
        pstLteSysInfo  = NAS_MSCC_Get3gppSysInfoAddr();

        st3gppInfo.enPriClass     = pstLteSysInfo->enPrioClass;
        st3gppInfo.stPlmnId.ulMcc = pstLteSysInfo->stPlmnId.ulMcc;
        st3gppInfo.stPlmnId.ulMnc = pstLteSysInfo->stPlmnId.ulMnc;
        st3gppInfo.enSysRat       = VOS_RATMODE_LTE;

        ulGetBsrTimerLenRslt = NAS_MSCC_GetCurr3gppSysBsrTimerLen(&st3gppInfo, &ulBsrTimerLen);
    }
    else if (VOS_TRUE == NAS_MSCC_GetHrpdCampOnFlag())
    {
        pstHrpdSysInfo = NAS_MSCC_GetHrpdSysInfoAddr();

        stHrpdInfo.enPriClassCdma2000Hrpd = pstHrpdSysInfo->enHrpdPrioClass;
        stHrpdInfo.enPriClassCdma2000Ai   = pstHrpdSysInfo->enAIPrioClass;
        stHrpdInfo.ucIsMccValid           = VOS_TRUE;
        stHrpdInfo.ulMcc                  = pstHrpdSysInfo->ulMcc;
        stHrpdInfo.ucSubNetMask           = pstHrpdSysInfo->ucSubNetMask;

        PS_MEM_CPY(stHrpdInfo.aucSectorId,
                   pstHrpdSysInfo->aucSectorId,
                   NAS_MSCC_BYTES_IN_SUBNET);

        /* ��HRPD����û���·�MCCʱ, ��ʹ��1X��Ϣ��ѯMLPL/MSPL��,
           ��ʹ��HRPD SysInfo��ȡ BSR��ʱ��ʱ��*/
        if (NAS_MSCC_INVALID_MCC == pstHrpdSysInfo->ulMcc)
        {
            if (VOS_TRUE == NAS_MSCC_Get1xCampOnFlag())
            {
                stHrpdInfo.ucIsMccValid       = VOS_FALSE;

                pst1xSysInfo   = NAS_MSCC_Get1xSysInfoAddr();

                st1xInfo.enPriClassCdma20001x = pst1xSysInfo->en1xPrioClass;
                st1xInfo.enPriClassCdma2000Ai = pst1xSysInfo->enAIPrioClass;
                st1xInfo.ulMcc                = pst1xSysInfo->ulMcc;
                st1xInfo.ulMnc                = pst1xSysInfo->ulMnc;
                st1xInfo.ucIsMccValid         = VOS_TRUE;
                st1xInfo.ucIsMncValid         = VOS_TRUE;
                st1xInfo.usNid                = pst1xSysInfo->usNid;
                st1xInfo.usSid                = pst1xSysInfo->usSid;

                ulGetBsrTimerLenRslt = NAS_MSCC_GetCurrHrpdSysBsrTimerLenBy1xLoc(&st1xInfo,
                                                                    &stHrpdInfo, &ulBsrTimerLen);
            }
        }
        else
        {
            ulGetBsrTimerLenRslt = NAS_MSCC_GetCurrHrpdSysBsrTimerLen(&stHrpdInfo, &ulBsrTimerLen);
        }
    }
    else
    {
        pst1xSysInfo   = NAS_MSCC_Get1xSysInfoAddr();

        st1xInfo.enPriClassCdma20001x = pst1xSysInfo->en1xPrioClass;
        st1xInfo.enPriClassCdma2000Ai = pst1xSysInfo->enAIPrioClass;
        st1xInfo.ulMcc                = pst1xSysInfo->ulMcc;
        st1xInfo.ulMnc                = pst1xSysInfo->ulMnc;
        st1xInfo.ucIsMccValid         = VOS_TRUE;
        st1xInfo.ucIsMncValid         = VOS_TRUE;
        st1xInfo.usNid                = pst1xSysInfo->usNid;
        st1xInfo.usSid                = pst1xSysInfo->usSid;

        ulGetBsrTimerLenRslt = NAS_MSCC_GetCurr1xSysBsrTimerLen(&st1xInfo, &ulBsrTimerLen);
    }

    if (VOS_FALSE == ulGetBsrTimerLenRslt)
    {
        ulBsrTimerLen   = 0;
    }

    return ulBsrTimerLen;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_StartBsrTimer
Description     :   start BSR Timer
Input parameters:   None
Output parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2014-4-13
        Author  :   t00323010
        Modify content :Create for Iteration 10
*****************************************************************************/
VOS_VOID NAS_MSCC_StartBsrTimer()
{
    VOS_UINT32                          ulBsrTimerLen;

    ulBsrTimerLen = NAS_MSCC_GetBsrTimerLen();

    if (0 == ulBsrTimerLen)
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_StartBsrTimer():NAS MSCC BSR Timer length is zero!");

        return;
    }

    NAS_MSCC_StartTimer(TI_NAS_MSCC_BSR_TIMER, ulBsrTimerLen);

    NAS_MSCC_SetCurrBsrTimerLen(ulBsrTimerLen);

    NAS_MSCC_SetOrigBsrTimerStartRat();

    return;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_IsNeedStartBsrTimer
Description     :   This function is used to check whether need to start Bsr Timer
Input parameters:   None
Output parameters:  None
Return Value    :   VOS_TRUE:Y
                    VOS_FALSE:N
Modify History:
    1)  Date    :   2014-4-2
        Author  :   t00323010
        Modify content :    Create for Iteration 10
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsNeedStartBsrTimer(VOS_VOID)
{
    /* ����״̬��������BSR��ʱ�������˳���״̬�������ж��Ƿ���Ҫ����BSR��ʱ�� */
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_TIMER_STATUS_RUNING == NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH))
    {
        return VOS_FALSE;
    }

    return NAS_MSCC_IsBgSearchHighPriSysAllowed();
}

/*****************************************************************************
Function Name   :   NAS_MSCC_IsNeedRestartBsrTimer
Description     :   This function is used to check whether need to restart Bsr Timer
Input parameters:   None
Output parameters:  None
Return Value    :   VOS_TRUE:Y
                    VOS_FALSE:N
Modify History:
    1)  Date    :   2014-5-5
        Author  :   t00323010
        Modify content :    Create for Iteration 10
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsNeedRestartBsrTimer(VOS_VOID)
{
    VOS_UINT32                                              ulOldBsrTimerLen;
    VOS_UINT32                                              ulNewBsrTimerLen;

    ulOldBsrTimerLen = NAS_MSCC_GetCurrBsrTimerLen();
    ulNewBsrTimerLen = NAS_MSCC_GetBsrTimerLen();

    if (NAS_MSCC_TIMER_STATUS_RUNING != NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_BSR_TIMER))
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MSCC_GetHrpdCampOnFlag())
    {
        /* �����ʱ�����ȷ����仯,���� */
        /* �����ǰ��ʽ��������ʱ��ʱ����ʽ�Ѿ���ͬ,���� */
        if ((VOS_RATMODE_HRPD != NAS_MSCC_GetOrigBsrTimerStartRat())
         || (ulOldBsrTimerLen != ulNewBsrTimerLen))
        {
            return VOS_TRUE;
        }
    }

    if (VOS_TRUE == NAS_MSCC_Get3gppCampOnFlag())
    {
        if ((VOS_RATMODE_LTE  != NAS_MSCC_GetOrigBsrTimerStartRat())
         || (ulOldBsrTimerLen != ulNewBsrTimerLen))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_Convert1xServiceStatusToMsccFormat
 ��������  : ��MMC��PS����״̬ת��ΪMSCC�ڲ���ʽ
 �������  : ��

 �������  : ��
 �� �� ֵ  : ���ص�ǰPSҵ��״̬:
             NAS_MSCC_NORMAL_SERVICE  PSҵ���������
             NAS_MSCC_LIMITED_SERVICE PSҵ���������
             NAS_MSCC_NO_SERVICE      PSҵ���޷���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��13��
   ��    ��   : t00323010
   �޸�����   : add for Iteration 10 �޸�
*****************************************************************************/
NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_Convert1xServiceStatusToMsccFormat(
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 en1xPsServiceStatus
)
{
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enPsSrvStatus;

    switch (en1xPsServiceStatus)
    {
        case NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE:

            enPsSrvStatus = NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE;
            break;

        case NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE:
        case NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION:
        case NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI:

            enPsSrvStatus = NAS_MSCC_SERVICE_STATUS_LIMITED_SERVICE;
            break;

        case NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE:
        case NAS_MSCC_PIF_SERVICE_STATUS_DEEP_SLEEP:
        case NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE:

            enPsSrvStatus = NAS_MSCC_SERVICE_STATUS_NO_SERVICE;
            break;

        default:

            enPsSrvStatus =  NAS_MSCC_SERVICE_STATUS_BUTT;
            break;
    }

    return enPsSrvStatus;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_ConvertHsdSysPriClassToMsccFormat
 ��������  : ��HSD��MMC�ϱ����������ȼ�ת��ΪMSCC���������ȼ�
 �������  : MSCC_HSD_PRI_CLASS_ENUM_UINT8:Hsd�������ȼ�
 �������  : None
 �� �� ֵ  : NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8:Mscc�������ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��12��
   ��    ��   : t00323010
   �޸�����   : �����ɺ���,for Iteration 10

*****************************************************************************/
NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8 NAS_MSCC_ConvertHsdSysPriClassToMsccFormat(
    MSCC_HSD_PRI_CLASS_ENUM_UINT8       enPriClass
)
{
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8   enMsccSysPriClass;
    switch (enPriClass)
    {
        case MSCC_HSD_PRI_CLASS_HOME:

            enMsccSysPriClass = NAS_MSCC_SYS_PRI_CLASS_HOME;
            break;

        case MSCC_HSD_PRI_CLASS_PREF:

            enMsccSysPriClass = NAS_MSCC_SYS_PRI_CLASS_PREF;
            break;

        case MSCC_HSD_PRI_CLASS_ANY :

            enMsccSysPriClass = NAS_MSCC_SYS_PRI_CLASS_ANY;
            break;

        default:

            enMsccSysPriClass = NAS_MSCC_SYS_PRI_CLASS_BUTT;
            break;
    }

    return enMsccSysPriClass;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_Convert1xSysPriClassToMsccFormat
 ��������  : ��HSD��MMC�ϱ����������ȼ�ת��ΪMSCC���������ȼ�
 �������  : NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8: Mmc�������ȼ�
 �������  : None
 �� �� ֵ  : NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8: Mscc�������ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��12��
   ��    ��   : t00323010
   �޸�����   : �����ɺ���,for Iteration 10

*****************************************************************************/
NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8 NAS_MSCC_Convert1xSysPriClassToMsccFormat(
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8   enPriClass
)
{
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8   enMsccSysPriClass;
    switch (enPriClass)
    {
        case NAS_MSCC_PIF_PRI_CLASS_HOME:

            enMsccSysPriClass = NAS_MSCC_SYS_PRI_CLASS_HOME;
            break;

        case NAS_MSCC_PIF_PRI_CLASS_PREF:

            enMsccSysPriClass = NAS_MSCC_SYS_PRI_CLASS_PREF;
            break;

        case NAS_MSCC_PIF_PRI_CLASS_ANY :

            enMsccSysPriClass = NAS_MSCC_SYS_PRI_CLASS_ANY;
            break;

        default:

            enMsccSysPriClass = NAS_MSCC_SYS_PRI_CLASS_BUTT;
            break;
    }

    return enMsccSysPriClass;
}




VOS_VOID NAS_MSCC_Update1xSysInfo(
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU               *pst1xSrvInfoInd
)
{
    NAS_MSCC_1X_SYS_INFO_STRU          *pst1xSysInfo;

    pst1xSysInfo = NAS_MSCC_Get1xSysInfoAddr();

    if ((NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pst1xSrvInfoInd->stSysSrvInfo.enServiceStatus)
     || (NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE == pst1xSrvInfoInd->stSysSrvInfo.enServiceStatus))
    {
        pst1xSysInfo->ucCampOnFlg   = VOS_TRUE;

        pst1xSysInfo->en1xPrioClass =
                    NAS_MSCC_Convert1xSysPriClassToMsccFormat(pst1xSrvInfoInd->stSysSrvInfo.en1xPriClass);

        pst1xSysInfo->enAIPrioClass =
                    NAS_MSCC_Convert1xSysPriClassToMsccFormat(pst1xSrvInfoInd->stSysSrvInfo.enAIPriClass);

        /* Update the location info in the Camped Location Info global variable */
        pst1xSysInfo->ulMcc = pst1xSrvInfoInd->stSysSrvInfo.stServiceInfo.ulMcc;
        pst1xSysInfo->ulMnc = pst1xSrvInfoInd->stSysSrvInfo.stServiceInfo.usMnc;
        pst1xSysInfo->usSid = pst1xSrvInfoInd->stSysSrvInfo.usSid;
        pst1xSysInfo->usNid = pst1xSrvInfoInd->stSysSrvInfo.usNid;
    }
    else
    {
        pst1xSysInfo->ucCampOnFlg  = VOS_FALSE;
    }

    return;
}

VOS_VOID NAS_MSCC_UpdateHrpdSysInfo(
    HSD_MSCC_OVERHEAD_MSG_IND_STRU     *pstHsdOverHeadInd
)
{
    NAS_MSCC_HRPD_SYS_INFO_STRU        *pstHrpdSysInfo;

    pstHrpdSysInfo = NAS_MSCC_GetHrpdSysInfoAddr();

    pstHrpdSysInfo->ucCampOnFlg     = VOS_TRUE;
    pstHrpdSysInfo->ulMcc           = pstHsdOverHeadInd->ulMcc;
    pstHrpdSysInfo->ucSubNetMask    = pstHsdOverHeadInd->ucSubNetMask;
    pstHrpdSysInfo->enAIPrioClass   = NAS_MSCC_ConvertHsdSysPriClassToMsccFormat(pstHsdOverHeadInd->ucPriClass_AI);
    pstHrpdSysInfo->enHrpdPrioClass = NAS_MSCC_ConvertHsdSysPriClassToMsccFormat(pstHsdOverHeadInd->ucPriClass_HRPD);

    PS_MEM_CPY(pstHrpdSysInfo->aucSectorId, pstHsdOverHeadInd->aucSectorId, NAS_MSCC_BYTES_IN_SUBNET);

    return;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetHighPriSysInfoInHrpdSysInfoListWithPriClass
Description     :   In hrpd sys info pri class list, using specify sys pri class to get hrpd sys info list
Input parameters:   ucHrpdSysNum                     VOS_UINT8
                    pstHrpdSysInfoList               MSCC_HSD_HRPD_SYS_INFO_STRU
                    enSysPriClass                    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8
Output parameters:  pstHighPriSysInfo                NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU

Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-5-4
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_GetHighPriSysInfoInHrpdSysInfoListWithPriClass(
    VOS_UINT8                                               ucHrpdSysNum,
    MSCC_HSD_HRPD_SYS_INFO_STRU                            *pstHrpdSysInfoList,
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enSysPriClass,
    NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU                *pstHighPriSysInfo
)
{
    VOS_UINT8                           ucPriClassMatched;
    VOS_UINT8                           i;
    VOS_UINT8                           j;

    ucPriClassMatched = VOS_FALSE;

    ucHrpdSysNum = NAS_COMM_MIN(MSCC_HSD_BG_HRPD_MAX_SYS_NUM, ucHrpdSysNum);

    for (i = 0, j = 0; i < ucHrpdSysNum; i++)
    {
        if ((NAS_MSCC_PIF_PREF_NEG_SYS_NEG == pstHrpdSysInfoList[i].enPrefNegSys)
         || (VOS_TRUE == pstHrpdSysInfoList[i].ucIsAvoided)
         || (VOS_FALSE == pstHrpdSysInfoList[i].ucIsExistedInPrl))
        {
            continue;
        }

        if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME == enSysPriClass)
         && (MSCC_HSD_PRI_CLASS_HOME == pstHrpdSysInfoList[i].enPriClass))
        {
            ucPriClassMatched = VOS_TRUE;
        }

        if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME_AND_PREF == enSysPriClass)
         && ((MSCC_HSD_PRI_CLASS_HOME == pstHrpdSysInfoList[i].enPriClass)
          || (MSCC_HSD_PRI_CLASS_PREF == pstHrpdSysInfoList[i].enPriClass)))
        {
            ucPriClassMatched = VOS_TRUE;
        }

        if (NAS_MSCC_MSPL_SYS_PRI_CLASS_ANY == enSysPriClass)
        {
            ucPriClassMatched = VOS_TRUE;
        }

        if (VOS_TRUE == ucPriClassMatched)
        {
            /* save high pri sys info */
            pstHighPriSysInfo->astFreqInfo[j].stFreq.enBandClass         = pstHrpdSysInfoList[i].stHrpdSysList.usBandClass;
            pstHighPriSysInfo->astFreqInfo[j].stFreq.usChannel           = pstHrpdSysInfoList[i].stHrpdSysList.usFreq;

            pstHighPriSysInfo->astFreqInfo[j].stHrpdSysItem.usSysIndex   = pstHrpdSysInfoList[i].stHrpdSysItem.usSysIndex;
            pstHighPriSysInfo->astFreqInfo[j].stHrpdSysItem.usAcqIndex   = pstHrpdSysInfoList[i].stHrpdSysItem.usAcqIndex;
            pstHighPriSysInfo->astFreqInfo[j].stHrpdSysItem.ucPrioLevel  = pstHrpdSysInfoList[i].stHrpdSysItem.ucPrioLevel;
            pstHighPriSysInfo->astFreqInfo[j].stHrpdSysItem.enPrefNegSys = pstHrpdSysInfoList[i].stHrpdSysItem.enPrefNegSys;

            j++;
            pstHighPriSysInfo->ucFreqNum = j;

            ucPriClassMatched = VOS_FALSE;
        }

    }

}
VOS_UINT32 NAS_MSCC_GetCurrentCampedSysMsplIndex(
    VOS_UINT8                          *pucMatchedMsplIndex
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU                stIn3gppInfo;
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU                stInHrpdInfo;
    NAS_MSCC_HRPD_SYS_INFO_STRU                            *pstHrpdSysInfo;
    NAS_MSCC_3GPP_SYS_INFO_STRU                            *pst3gppSysInfo;

    /* ���MLPL MSPL�����ã�ֱ�ӷ���VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    enMlplMatchLvl       = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    *pucMatchedMsplIndex = 0;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();

    if (VOS_TRUE == NAS_MSCC_Get3gppCampOnFlag())
    {
        pst3gppSysInfo = NAS_MSCC_Get3gppSysInfoAddr();

        PS_MEM_SET(&stIn3gppInfo, 0x00 , sizeof(NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU));

        stIn3gppInfo.stPlmnId.ulMcc = pst3gppSysInfo->stPlmnId.ulMcc;
        stIn3gppInfo.stPlmnId.ulMnc = pst3gppSysInfo->stPlmnId.ulMnc;
        stIn3gppInfo.enPriClass     = pst3gppSysInfo->enPrioClass;
        stIn3gppInfo.enSysRat       = VOS_RATMODE_LTE;

        if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy3gppSys(&stIn3gppInfo, pstMlpl,
                                                        pucMatchedMsplIndex, &enMlplMatchLvl))
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MSCC_GetHrpdCampOnFlag())
    {
        pstHrpdSysInfo = NAS_MSCC_GetHrpdSysInfoAddr();

        PS_MEM_SET(&stInHrpdInfo, 0x00 , sizeof(NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU));

        stInHrpdInfo.enPriClassCdma2000Hrpd = pstHrpdSysInfo->enHrpdPrioClass;
        stInHrpdInfo.enPriClassCdma2000Ai   = pstHrpdSysInfo->enAIPrioClass;
        stInHrpdInfo.ucIsMccValid           = VOS_TRUE;
        stInHrpdInfo.ulMcc                  = pstHrpdSysInfo->ulMcc;
        stInHrpdInfo.ucSubNetMask           = pstHrpdSysInfo->ucSubNetMask;

        PS_MEM_CPY(stInHrpdInfo.aucSectorId,
                   pstHrpdSysInfo->aucSectorId,
                   NAS_MSCC_BYTES_IN_SUBNET);

        if (VOS_FALSE == NAS_MSCC_GetMsplIndexByHrpdSys(&stInHrpdInfo, pstMlpl,
                                                        pucMatchedMsplIndex, &enMlplMatchLvl))
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID NAS_MSCC_GetPlmnListAccordingtoSpecMsplIndex(
    VOS_UINT8                                               ucOrigSysMsplIndex,
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstSrcPlmnList,
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstDestPlmnList
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU                stIn3gppInfo;
    VOS_UINT8                                               i;
    VOS_UINT8                                               j;
    VOS_UINT8                                               ucCurSysMsplIndex;

    /* ���MLPL MSPL�����ã�ֱ�ӷ���VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        PS_MEM_CPY(pstDestPlmnList, pstSrcPlmnList, sizeof(NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU));

        return;
    }

    enMlplMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();

    for (i = 0,j = 0; i < pstSrcPlmnList->ucHighPlmnNum; i++)
    {
        PS_MEM_SET(&stIn3gppInfo, 0x00 , sizeof(NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU));

        stIn3gppInfo.stPlmnId.ulMcc = pstSrcPlmnList->astHighPlmnID[i].ulMcc;
        stIn3gppInfo.stPlmnId.ulMnc = pstSrcPlmnList->astHighPlmnID[i].ulMnc;
        stIn3gppInfo.enPriClass     = NAS_MSCC_SYS_PRI_CLASS_ANY;
        stIn3gppInfo.enSysRat       = VOS_RATMODE_LTE;

        ucCurSysMsplIndex = 0;

        if (VOS_TRUE == NAS_MSCC_GetMsplIndexBy3gppSys(&stIn3gppInfo, pstMlpl,
                                                        &ucCurSysMsplIndex, &enMlplMatchLvl))
        {
            if (ucCurSysMsplIndex == ucOrigSysMsplIndex)
            {
                pstDestPlmnList->astHighPlmnID[j] = pstSrcPlmnList->astHighPlmnID[i];
                j++;
            }
        }
    }

    pstDestPlmnList->ucHighPlmnNum = j;

    for (i = 0,j = 0; i < pstSrcPlmnList->ucLowPlmnNum; i++)
    {
        PS_MEM_SET(&stIn3gppInfo, 0x00 , sizeof(NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU));

        stIn3gppInfo.stPlmnId.ulMcc = pstSrcPlmnList->astLowPlmnID[i].ulMcc;
        stIn3gppInfo.stPlmnId.ulMnc = pstSrcPlmnList->astLowPlmnID[i].ulMnc;
        stIn3gppInfo.enPriClass     = NAS_MSCC_SYS_PRI_CLASS_ANY;
        stIn3gppInfo.enSysRat       = VOS_RATMODE_LTE;

        ucCurSysMsplIndex = 0;

        if (VOS_TRUE == NAS_MSCC_GetMsplIndexBy3gppSys(&stIn3gppInfo, pstMlpl,
                                                        &ucCurSysMsplIndex, &enMlplMatchLvl))
        {
            if (ucCurSysMsplIndex == ucOrigSysMsplIndex)
            {
                pstDestPlmnList->astLowPlmnID[j] = pstSrcPlmnList->astLowPlmnID[i];
                j++;
            }
        }
    }

    pstDestPlmnList->ucLowPlmnNum = j;

    pstDestPlmnList->enRat        = pstSrcPlmnList->enRat;
}

VOS_UINT32 NAS_MSCC_IsNeedAcqLteFrist(VOS_VOID)
{
    /* LTE not supported by syscfg,could not acquire */
    if (VOS_FALSE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
    {
        return VOS_FALSE;
    }

    /* hrpd not supported by syscfg,acquire lte frist */
    if (VOS_FALSE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        /* sim ps invalid,could not acquire lte */
        if (VOS_FALSE == NAS_MSCC_GetSimPsRegStatus())
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    /* csim card is absent,acqurie lte frist */
    if (NAS_MSCC_PIF_CARD_STATUS_ABSENT == NAS_MSCC_GetCsimCardStatus())
    {
        return VOS_TRUE;
    }

    /* usim card is absent,could not acquire lte */
    if (NAS_MSCC_PIF_CARD_STATUS_ABSENT == NAS_MSCC_GetUsimCardStatus())
    {
        return VOS_FALSE;
    }

    /* sim ps invalid,could not acquire lte */
    if (VOS_FALSE == NAS_MSCC_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

VOS_UINT32 NAS_MSCC_IsNeedStartScanTimerUponSyscfg(VOS_VOID)
{
    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MSCC_Is3gppNormalService())
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MSCC_IsHrpdNormalService())
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MSCC_Is1xNormalService())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#endif



VOS_UINT32 NAS_MSCC_IsHrpdAndLteBothSupported(VOS_VOID)
{
    /* syscfg set both support HRPD and LTE, we consider it's CL mode */
    VOS_UINT32                          ulLteSupport;

    ulLteSupport = NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE);

    if ((VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
     && (VOS_TRUE == ulLteSupport))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

VOS_UINT32 NAS_MSCC_IsGULModeConfigured(VOS_VOID)
{
    /* syscfg set not support HRPD and 1X, we consider it's GUL mode */
    VOS_UINT32                          ulSupport1x;
    VOS_UINT32                          ulSupportHrpd;

    ulSupport1x   = NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X);
    ulSupportHrpd = NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD);

    if ((VOS_FALSE == ulSupportHrpd)
     && (VOS_FALSE == ulSupport1x))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID  NAS_MSCC_ConvertSimPlmnToNasPlmn(
    NAS_MSCC_SIM_FORMAT_PLMN_ID_STRU   *pstInSimPlmn,
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstOutNasPlmn
)
{
    VOS_UINT32                          ulTempData;
    NAS_MSCC_PIF_PLMN_ID_STRU           stPlmn;

    /*
       PLMN BCD ���� ��ʽ

       MCC digit 2,  MCC digit 1, ----OCTET 1
       MNC digit 3,  MCC digit 3, ----OCTET 2
       MNC digit 2,  MNC digit 1, ----OCTET 3
    */
    ulTempData = NAS_MSCC_OCTET_LOW_FOUR_BITS & (pstInSimPlmn->aucSimPlmn[0]);
    stPlmn.ulMcc = ulTempData;
    ulTempData = (NAS_MSCC_OCTET_HIGH_FOUR_BITS & (pstInSimPlmn->aucSimPlmn[0])) >> NAS_MSCC_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMcc |= ulTempData << NAS_MSCC_OCTET_MOVE_EIGHT_BITS;

    ulTempData = NAS_MSCC_OCTET_LOW_FOUR_BITS & (pstInSimPlmn->aucSimPlmn[1]);
    stPlmn.ulMcc |= ulTempData << NAS_MSCC_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = (NAS_MSCC_OCTET_HIGH_FOUR_BITS & (pstInSimPlmn->aucSimPlmn[1])) >> NAS_MSCC_OCTET_MOVE_FOUR_BITS;

    stPlmn.ulMnc = ulTempData << NAS_MSCC_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = NAS_MSCC_OCTET_LOW_FOUR_BITS & (pstInSimPlmn->aucSimPlmn[2]);
    stPlmn.ulMnc |= ulTempData;
    ulTempData = (NAS_MSCC_OCTET_HIGH_FOUR_BITS & (pstInSimPlmn->aucSimPlmn[2])) >> NAS_MSCC_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMnc |= ulTempData << NAS_MSCC_OCTET_MOVE_EIGHT_BITS;

    pstOutNasPlmn->ulMcc = stPlmn.ulMcc;
    pstOutNasPlmn->ulMnc = stPlmn.ulMnc;
}



VOS_UINT8 NAS_MSCC_ComparePlmn(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstSrcPlmn,
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstDesPlmn
)
{
    if (pstSrcPlmn->ulMcc != pstDesPlmn->ulMcc)
    {
        return VOS_FALSE;
    }

    if ((NAS_MSCC_NAS_STYLE_WILDCARD_MNC == pstSrcPlmn->ulMnc)
     || (NAS_MSCC_NAS_STYLE_WILDCARD_MNC == pstDesPlmn->ulMnc))
    {
        return VOS_TRUE;
    }

    if (pstSrcPlmn->ulMnc == pstDesPlmn->ulMnc)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 NAS_MSCC_IsPlmnIdValid(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
)
{
    VOS_UINT8                                               ucResult;

    /*
    The coding of this field is the responsibility of each administration but
    BCD coding shall be used. The MNC shall consist of 2 or 3 digits.
    If a network operator decides to use only two digits in the MNC,
    bits 5 to 8 of octet 7 shall be coded as "1111".
    MCC digit 2     MCC digit 1
    MNC digit 3     MCC digit 3
    MNC digit 2     MNC digit 1
    */

    ucResult = VOS_TRUE;

    if ( ((pstPlmnId->ulMcc & NAS_MSCC_BYTE_MASK) > NAS_MSCC_MAX_DIGIT_VALUE)
      || (((pstPlmnId->ulMcc >> 8) & NAS_MSCC_BYTE_MASK) > NAS_MSCC_MAX_DIGIT_VALUE)
      || (((pstPlmnId->ulMcc >> 16) & NAS_MSCC_BYTE_MASK) > NAS_MSCC_MAX_DIGIT_VALUE))
    {
        ucResult = VOS_FALSE;
    }

    if ((((pstPlmnId->ulMnc) & NAS_MSCC_BYTE_MASK) > NAS_MSCC_MAX_DIGIT_VALUE)
     || (((pstPlmnId->ulMnc >> 8) & NAS_MSCC_BYTE_MASK) > NAS_MSCC_MAX_DIGIT_VALUE))
    {
        ucResult = VOS_FALSE;
    }

    if ((((pstPlmnId->ulMnc >> 16) & NAS_MSCC_BYTE_MASK) > NAS_MSCC_MAX_DIGIT_VALUE)
     && (((pstPlmnId->ulMnc >> 16) & NAS_MSCC_BYTE_MASK) != NAS_MSCC_LOW_BYTE_INVALID))
    {
        ucResult = VOS_FALSE;
    }

    return ucResult;
}



NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_ConvertMmcServiceStatusToMsccFormat(
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enMmcPsServiceStatus
)
{
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enPsSrvStatus;

    switch ((VOS_UINT8)enMmcPsServiceStatus)
    {
        case NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE:

            enPsSrvStatus = NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE;
            break;

        case NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE:
        case NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION:
        case NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI:

            enPsSrvStatus = NAS_MSCC_SERVICE_STATUS_LIMITED_SERVICE;
            break;

        case NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE:
        case NAS_MSCC_PIF_SERVICE_STATUS_DEEP_SLEEP:
        case NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE:

            enPsSrvStatus = NAS_MSCC_SERVICE_STATUS_NO_SERVICE;
            break;

        default:

            enPsSrvStatus =  NAS_MSCC_SERVICE_STATUS_BUTT;
            break;
    }

    return enPsSrvStatus;
}



/*****************************************************************************
 �� �� ��  : NAS_MSCC_ConvertMmcSysPriClassToMsccFormat
 ��������  : ��HSD��MMC�ϱ����������ȼ�ת��ΪMSCC���������ȼ�
 �������  : NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8: Mmc�������ȼ�
 �������  : None
 �� �� ֵ  : NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8:           Mscc�������ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��12��
   ��    ��   : t00323010
   �޸�����   : �����ɺ���,for Iteration 10

*****************************************************************************/
NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8 NAS_MSCC_ConvertMmcSysPriClassToMsccFormat(
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPriClass
)
{
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8   enMsccSysPriClass;
    switch (enPriClass)
    {
        case NAS_MSCC_PIF_PLMN_PRIORITY_HOME:

            enMsccSysPriClass = NAS_MSCC_SYS_PRI_CLASS_HOME;
            break;

        case NAS_MSCC_PIF_PLMN_PRIORITY_PREF:

            enMsccSysPriClass = NAS_MSCC_SYS_PRI_CLASS_PREF;
            break;

        case NAS_MSCC_PIF_PLMN_PRIORITY_ANY :

            enMsccSysPriClass = NAS_MSCC_SYS_PRI_CLASS_ANY;
            break;

        default:

            enMsccSysPriClass = NAS_MSCC_SYS_PRI_CLASS_BUTT;
            break;
    }

    return enMsccSysPriClass;
}



VOS_RATMODE_ENUM_UINT32 NAS_MSCC_ConvertNvPlatformRatToMsccType(
    PLATFORM_RAT_TYPE_ENUM_UINT16       enNvPlatformRatCap
)
{
    VOS_RATMODE_ENUM_UINT32             enNasMsccPlatformRat;

    switch (enNvPlatformRatCap)
    {
        case PLATFORM_RAT_GSM:
            enNasMsccPlatformRat = VOS_RATMODE_GSM;
            break;

        case PLATFORM_RAT_WCDMA:
            enNasMsccPlatformRat = VOS_RATMODE_WCDMA;
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        case PLATFORM_RAT_TDS:
            enNasMsccPlatformRat = VOS_RATMODE_TDS;
            break;
#endif

#if   (FEATURE_ON == FEATURE_LTE)
        case PLATFORM_RAT_LTE:
            enNasMsccPlatformRat = VOS_RATMODE_LTE;
            break;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case PLATFORM_RAT_1X:
            enNasMsccPlatformRat = VOS_RATMODE_1X;
            break;

        case PLATFORM_RAT_HRPD:
            enNasMsccPlatformRat = VOS_RATMODE_HRPD;
            break;

#endif

        default:
            enNasMsccPlatformRat = VOS_RATMODE_BUTT;
            break;
    }

    return enNasMsccPlatformRat;
}
/* Added by y00307564 for CDMA Iteration 10 2015-4-13 end */


VOS_UINT32 NAS_MSCC_IsLtePlmnIdChanged(VOS_VOID)
{
    NAS_MSCC_3GPP_SYS_INFO_STRU        *pst3gppSysInfo          = VOS_NULL_PTR;
    NAS_MSCC_MMSS_LOCATION_INFO_STRU   *pstMmssLastLocationInfo = VOS_NULL_PTR;

    /* Get the current camped 3GPP Sys Info address */
    pst3gppSysInfo = NAS_MSCC_Get3gppSysInfoAddr();

    if (NAS_MSCC_SYS_MODE_LTE == pst3gppSysInfo->enSysMode)
    {
        /* Get the MMSS Location info address which stores the MCC And MNC of the last used LTE system */
        pstMmssLastLocationInfo = NAS_MSCC_GetMmssLastLocationInfoAddr();

        if (VOS_FALSE == pstMmssLastLocationInfo->ucLteActiveFlag)
        {
            /* If LTE Active Flag is false previously, then return VOS_TRUE */
            return VOS_TRUE;
        }

        if ((pst3gppSysInfo->stPlmnId.ulMcc != pstMmssLastLocationInfo->stLteLocationInfo.ulMcc)
         || (pst3gppSysInfo->stPlmnId.ulMnc != pstMmssLastLocationInfo->stLteLocationInfo.ulMnc))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    return VOS_FALSE;
}

VOS_VOID NAS_MSCC_SaveSysAcqTimerCfg(
    NAS_NVIM_MSCC_SYS_ACQ_TIMER_CFG_STRU                   *pstNvimSysAcqTimerCfg,
    NAS_MSCC_SYSACQ_TIMER_CFG_STRU                         *pstSysAcqTimerCfgInfo
)
{

    if (0 != pstNvimSysAcqTimerCfg->ulFirstSearchAvailTimerCount)
    {
        /* Read the NVIM Value if the count is not zero */
        pstSysAcqTimerCfgInfo->ulAvailableTimerCountFirstSearch = pstNvimSysAcqTimerCfg->ulFirstSearchAvailTimerCount;
    }

    if (0 != pstNvimSysAcqTimerCfg->ulFirstSearchAvailTimerLen)
    {
        /* Read the NVIM Value if the timer length is not zero */
        pstSysAcqTimerCfgInfo->ulAvailableTimerLengthFirstSearch = pstNvimSysAcqTimerCfg->ulFirstSearchAvailTimerLen
                                                                                  * NAS_MSCC_THOUSAND_MILLISECOND_UNIT;
    }

    if (0 != pstNvimSysAcqTimerCfg->ulDeepSearchAvailTimerLen)
    {
        /* Read the NVIM Value if the timer length is not zero */
        pstSysAcqTimerCfgInfo->ulAvailableTimerLengthDeepSearch = pstNvimSysAcqTimerCfg->ulDeepSearchAvailTimerLen
                                                                                  * NAS_MSCC_THOUSAND_MILLISECOND_UNIT;
    }

    if (0 != pstNvimSysAcqTimerCfg->ulScanTimerLen)
    {
        /* Read the NVIM Value if the timer length is not zero */
        pstSysAcqTimerCfgInfo->ulScanTimerLen                   = pstNvimSysAcqTimerCfg->ulScanTimerLen * NAS_MSCC_THOUSAND_MILLISECOND_UNIT;
    }

    if (0 != pstNvimSysAcqTimerCfg->ulSleepTimerLen)
    {
        /* Read the NVIM Value if the timer length is not zero */
        pstSysAcqTimerCfgInfo->ulSleepTimerLen                  = pstNvimSysAcqTimerCfg->ulSleepTimerLen * NAS_MSCC_THOUSAND_MILLISECOND_UNIT;;
    }



    /* Read the Timer length value from NVIM if the NVIM Active flag is true */
    if ((VOS_TRUE == pstNvimSysAcqTimerCfg->ucBsrTimerActiveFlag)
      &&(0 != pstNvimSysAcqTimerCfg->ulBsrTimerLen))
    {
        pstSysAcqTimerCfgInfo->ulBsrTimerLen                    = pstNvimSysAcqTimerCfg->ulBsrTimerLen * NAS_MSCC_THOUSAND_MILLISECOND_UNIT;

        /* Set the NVIM Active Flag in the MMSS Config */
        NAS_MSCC_SetBsrTimerNvimActiveFlag(VOS_TRUE);
    }

    /* If BSR Active flag is neither TRUE nor FALSE, make an error log. BSR timer length contains the default value */
    else
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SaveSysAcqTimerCfg: BSR NVIM Active flag is invalid!");

        /* Set the NVIM Active Flag in the MMSS Config */
        NAS_MSCC_SetBsrTimerNvimActiveFlag(VOS_FALSE);
    }

    return;
}

VOS_VOID NAS_MSCC_UpdateLocationInfoToNvim(VOS_VOID)
{
    NAS_MSCC_MMSS_LOCATION_INFO_STRU                       *pstMmssLocationInfo = VOS_NULL_PTR;
    NAS_MSCC_1X_SYS_INFO_STRU                              *pst1xSysInfo = VOS_NULL_PTR;
    NAS_MSCC_3GPP_SYS_INFO_STRU                            *pst3gppSysInfo = VOS_NULL_PTR;

    /* Get 1x Current camped Sys info global variable address */
    pst1xSysInfo = NAS_MSCC_Get1xSysInfoAddr();

    /* Get 3gpp Current camped sys info global variable address */
    pst3gppSysInfo = NAS_MSCC_Get3gppSysInfoAddr();

    /* Get the MMSS Location Info Global variable address */
    pstMmssLocationInfo = NAS_MSCC_GetMmssLastLocationInfoAddr();

    /* If CL Mode is active, update to NV */
    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
        /* Update the Last Location info as Valid and Sys Acq mode as GUL */
        pstMmssLocationInfo->ucIsLocInfoUsedInSwitchOn = VOS_TRUE;
        pstMmssLocationInfo->enSysAcqMode              = NAS_MSCC_LC_RAT_COMBINED_GUL;

        /* Update the MMSS LOcation info with active flags as FALSE and Clear the 1x and LTE location info */
        pstMmssLocationInfo->ucCdma1xActiveFlag = VOS_FALSE;
        pstMmssLocationInfo->ucLteActiveFlag    = VOS_FALSE;
        PS_MEM_SET(&(pstMmssLocationInfo->st1xLocationInfo), 0x00, sizeof(NAS_MSCC_1X_LOC_INFO_STRU));
        PS_MEM_SET(&(pstMmssLocationInfo->stLteLocationInfo), 0x00, sizeof(NAS_MSCC_LTE_LOC_INFO_STRU));
    }
    else
    {
        /* Update the Last Location info as Invalid and Sys Acq mode as GUL */
        pstMmssLocationInfo->ucIsLocInfoUsedInSwitchOn = VOS_TRUE;
        pstMmssLocationInfo->enSysAcqMode              = NAS_MSCC_LC_RAT_COMBINED_CL;

        /* Update the 1x location info */
        if (VOS_TRUE == pst1xSysInfo->ucCampOnFlg)
        {
            pstMmssLocationInfo->ucCdma1xActiveFlag = VOS_TRUE;
            pstMmssLocationInfo->st1xLocationInfo.ulMcc = pst1xSysInfo->ulMcc;
            pstMmssLocationInfo->st1xLocationInfo.ulMnc = pst1xSysInfo->ulMnc;
            pstMmssLocationInfo->st1xLocationInfo.usSid = pst1xSysInfo->usSid;
            pstMmssLocationInfo->st1xLocationInfo.usNid = pst1xSysInfo->usNid;

            pstMmssLocationInfo->st1xLocationInfo.en1xPrioClass = pst1xSysInfo->en1xPrioClass;
            pstMmssLocationInfo->st1xLocationInfo.enAIPrioClass = pst1xSysInfo->enAIPrioClass;
        }
        else
        {
            /* If 1x system is not camped on, Set 1x active flag to FALSE and clear the 1x location info */
            pstMmssLocationInfo->ucCdma1xActiveFlag = VOS_FALSE;
            PS_MEM_SET(&(pstMmssLocationInfo->st1xLocationInfo), 0x00, sizeof(NAS_MSCC_1X_LOC_INFO_STRU));
        }

        /* Update LTE Location info */
        if ((NAS_MSCC_SYS_MODE_LTE == pst3gppSysInfo->enSysMode)
         && (VOS_TRUE              == pst3gppSysInfo->ucCampOnFlg))
        {
            pstMmssLocationInfo->ucLteActiveFlag = VOS_TRUE;
            pstMmssLocationInfo->stLteLocationInfo.ulMcc = pst3gppSysInfo->stPlmnId.ulMcc;
            pstMmssLocationInfo->stLteLocationInfo.ulMnc = pst3gppSysInfo->stPlmnId.ulMnc;

            pstMmssLocationInfo->stLteLocationInfo.enPrioClass = pst3gppSysInfo->enPrioClass;
        }
        else
        {
            pstMmssLocationInfo->ucLteActiveFlag = VOS_FALSE;
            PS_MEM_SET(&(pstMmssLocationInfo->stLteLocationInfo), 0x00, sizeof(NAS_MSCC_LTE_LOC_INFO_STRU));
        }
    }

    /* Write the location info to NVIM */
    NAS_MSCC_WriteMmssLocationInfoNvim(pstMmssLocationInfo);
}



MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32 NAS_MSCC_ConvertMmcPlmnSelRsltToMmaSysAcqRlst(
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM_UINT32          enMmcPlmnSelRslt
)
{
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enMmaSysAcqRlst;

    switch (enMmcPlmnSelRslt)
    {
        case NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NORMAL_SERVICE :
            enMmaSysAcqRlst = MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE;
            break;

        case NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE :
            enMmaSysAcqRlst = MSCC_MMA_SYSTEM_ACQUIRE_RESULT_LIMITED_SERVICE;
            break;

        case NAS_MSCC_PIF_PLMN_SELECTION_RESULT_INTERRUPT :
            enMmaSysAcqRlst = MSCC_MMA_SYSTEM_ACQUIRE_RESULT_INTERRUPT;
            break;

        case NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE :
            enMmaSysAcqRlst = MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE;
            break;

        case NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_RF :
            enMmaSysAcqRlst = MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_RF;
            break;

        default:
            enMmaSysAcqRlst = MSCC_MMA_SYSTEM_ACQUIRE_RESULT_BUTT;
            NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_ConvertMmcPlmnSelRsltToMmaSysAcqRlst: unknown PlmnSelRslt!");
            break;
    }

    return enMmaSysAcqRlst;
}



VOS_VOID NAS_MSCC_Update3gppSysInfo(
    MMC_MSCC_SYS_INFO_IND_STRU         *pstMmcSysInfo
)
{
    NAS_MSCC_3GPP_SYS_INFO_STRU        *pst3gppSysInfo = VOS_NULL_PTR;

    pst3gppSysInfo = NAS_MSCC_Get3gppSysInfoAddr();

    /* ���µ�ǰ��ϵͳ��Ϣ */
    pst3gppSysInfo->enSysMode       = pstMmcSysInfo->enCurNetWork;
    pst3gppSysInfo->enLmmAccessType = pstMmcSysInfo->enLmmAccessType;
    pst3gppSysInfo->stPlmnId.ulMcc  = pstMmcSysInfo->stPlmnId.ulMcc;
    pst3gppSysInfo->stPlmnId.ulMnc  = pstMmcSysInfo->stPlmnId.ulMnc;
    pst3gppSysInfo->usLac           = pstMmcSysInfo->usLac;
    pst3gppSysInfo->ucRac           = pstMmcSysInfo->ucRac;
    pst3gppSysInfo->ulCellId        = pstMmcSysInfo->stCellId.aulCellId[0];
    pst3gppSysInfo->ucRoamFlag      = pstMmcSysInfo->ucRoamFlag;
    pst3gppSysInfo->ucCampOnFlg     = VOS_TRUE;

    if (NAS_MSCC_PIF_NET_RAT_TYPE_LTE == pstMmcSysInfo->enCurNetWork)
    {
        pst3gppSysInfo->enPrioClass = NAS_MSCC_ConvertMmcSysPriClassToMsccFormat(pstMmcSysInfo->enPrioClass);
    }

    return;
}
VOS_VOID NAS_MSCC_GetPlmnListInPlmnPriClassListWithPriClass(
    NAS_MSCC_PIF_PLMN_PRI_CLASS_LIST_INFO_STRU             *pstPlmnPriClassListInfo,
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enSysPriClass,
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstDestPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT8                           ucPriClassMatched;
    VOS_UINT8                           ucPlmnNum;

    ucPriClassMatched = VOS_FALSE;
    ucPlmnNum         = NAS_COMM_MIN(NAS_MSCC_PIF_MAX_HIGH_QUALITY_PLMN_NUM, pstPlmnPriClassListInfo->ucHighPlmnNum);

    for (i = 0, j = 0; i < ucPlmnNum; i++)
    {
        /* for forbidden plmn, we should skip */
        if (VOS_TRUE == pstPlmnPriClassListInfo->astHighPlmnPriClassInfo[i].ucIsForbidden)
        {
            continue;
        }

        if (VOS_TRUE == NAS_MSCC_IsPlmnPriClassMatchMsplSysPriClass(pstPlmnPriClassListInfo->astHighPlmnPriClassInfo[i].enPriClass,
                                                                    enSysPriClass))
        {
            ucPriClassMatched = VOS_TRUE;
        }

        if (VOS_TRUE == ucPriClassMatched)
        {
            pstDestPlmnList->astHighPlmnID[j] = pstPlmnPriClassListInfo->astHighPlmnPriClassInfo[i].stPlmnId;
            j++;

            ucPriClassMatched = VOS_FALSE;
        }
    }

    pstDestPlmnList->ucHighPlmnNum = j;

    ucPriClassMatched = VOS_FALSE;
    ucPlmnNum         = NAS_COMM_MIN(NAS_MSCC_PIF_MAX_LOW_QUALITY_PLMN_NUM, pstPlmnPriClassListInfo->ucLowPlmnNum);

    for (i = 0, j = 0; i < ucPlmnNum; i++)
    {
        /* for forbidden plmn, we should skip */
        if (VOS_TRUE == pstPlmnPriClassListInfo->astLowPlmnPriClassInfo[i].ucIsForbidden)
        {
            continue;
        }

        if (VOS_TRUE == NAS_MSCC_IsPlmnPriClassMatchMsplSysPriClass(pstPlmnPriClassListInfo->astLowPlmnPriClassInfo[i].enPriClass,
                                                                    enSysPriClass))
        {
            ucPriClassMatched = VOS_TRUE;
        }

        if (VOS_TRUE == ucPriClassMatched)
        {
            pstDestPlmnList->astLowPlmnID[j] = pstPlmnPriClassListInfo->astLowPlmnPriClassInfo[i].stPlmnId;
            j++;

            ucPriClassMatched = VOS_FALSE;
        }
    }

    pstDestPlmnList->ucLowPlmnNum = j;

    pstDestPlmnList->enRat = pstPlmnPriClassListInfo->enRat;

    return;
}


VOS_RATMODE_ENUM_UINT32 NAS_MSCC_TransferMsccToVosRat(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8         enRatType
)
{
    switch (enRatType)
    {
        case NAS_MSCC_PIF_NET_RAT_TYPE_GSM:
            return VOS_RATMODE_GSM;

        case NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA:
            return VOS_RATMODE_WCDMA;

        case NAS_MSCC_PIF_NET_RAT_TYPE_LTE:
            return VOS_RATMODE_LTE;

        case NAS_MSCC_PIF_NET_RAT_TYPE_1X:
            return VOS_RATMODE_1X;

        case NAS_MSCC_PIF_NET_RAT_TYPE_HRPD:
            return VOS_RATMODE_HRPD;

        default:
            return VOS_RATMODE_BUTT;
    }
}




VOS_UINT32 NAS_MSCC_Is3gppNormalService(VOS_VOID)
{
    if (VOS_FALSE == NAS_MSCC_Get3gppCampOnFlag())
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == NAS_MSCC_GetCurr3gppPsServiceStatus())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_IsHrpdNormalService(VOS_VOID)
{
    if (VOS_FALSE == NAS_MSCC_GetHrpdCampOnFlag())
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == NAS_MSCC_GetCurrHrpdServiceStatus())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_Is1xNormalService(VOS_VOID)
{
    if (VOS_FALSE == NAS_MSCC_Get1xCampOnFlag())
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == NAS_MSCC_GetCurr1xServiceStatus())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_IsPlmnPriClassMatchMsplSysPriClass(
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPriClass,
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enSysPriClass
)
{
    if (NAS_MSCC_MSPL_SYS_PRI_CLASS_ANY == enSysPriClass)
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME_AND_PREF == enSysPriClass)
     && ((NAS_MSCC_PIF_PLMN_PRIORITY_HOME          == enPriClass)
      || (NAS_MSCC_PIF_PLMN_PRIORITY_PREF          == enPriClass)))
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME == enSysPriClass)
     && (NAS_MSCC_PIF_PLMN_PRIORITY_HOME  == enPriClass))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



