

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasComm.h"
#include "NVIM_Interface.h"
#include "SysNvId.h"
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlProcNvim.h"
#include "NasUtranCtrlInterface.h"
#include "NasMmlLib.h"
#include "NasUtranCtrlMntn.h"
#include "NasUtranCtrlCommFunc.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_PROC_NVIM_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/




/*****************************************************************************
  5 ��������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 ��������

*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)


VOS_VOID NAS_UTRANCTRL_ReadUtranModeAutoSwitchNvim( VOS_VOID )
{
    NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU         *pstNvimUtranModeAutoSwitch;
    NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU              *pstUtranModeAutoSwitch;
    VOS_UINT32                                              i;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stSimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stPlmn;

    pstUtranModeAutoSwitch = NAS_UTRANCTRL_GetUtranModeAutoSwtich();

    pstNvimUtranModeAutoSwitch = (NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU *)
                                 PS_MEM_ALLOC(WUEPS_PID_MMC,
                                              sizeof(NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU));

    /* �ڴ�����ʧ��ֱ���˳� */
    if ( VOS_NULL_PTR == pstNvimUtranModeAutoSwitch )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ReadUtranModeAutoSwitchNvim():ERROR: Mem alloc fail ! ");
        return;
    }

    if ( NV_OK != NV_Read( en_NV_Item_Utran_Mode_Auto_Switch,
                           pstNvimUtranModeAutoSwitch,
                           sizeof(NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU)) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ReadUtranModeAutoSwitchNvim():ERROR: en_NV_Item_Utran_Mode_Auto_Switch read Error");

        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimUtranModeAutoSwitch);

        return;
    }

    /* ��NV�е�UTRAN SWITCH MODE���ݿ������ڴ��б��� */
    pstUtranModeAutoSwitch->ucUtranSwitchMode = pstNvimUtranModeAutoSwitch->ucUtranSwitchMode;


    /* �����ǰ��TD��MCC�ĸ������������ֵ����ȡ���ֵ���˴����й����������Ч�Ա��� */
    if ( pstNvimUtranModeAutoSwitch->ucTdMccListNum > NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM )
    {
        pstNvimUtranModeAutoSwitch->ucTdMccListNum  = NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM;
    }

    for (i = 0 ; i < pstNvimUtranModeAutoSwitch->ucTdMccListNum; i++)
    {
        /* �����ǰ��MCC��Ч����NV�е�MCC LIST���ݿ������ڴ��б��� */
        if ( VOS_TRUE == NAS_MML_IsMccValid(pstNvimUtranModeAutoSwitch->aulTdMccList[i]) )
        {
            pstUtranModeAutoSwitch->aulTdMccList[pstUtranModeAutoSwitch->ucTdMccListNum] = pstNvimUtranModeAutoSwitch->aulTdMccList[i];

            pstUtranModeAutoSwitch->ucTdMccListNum++;
        }
    }

    /* IMSI PLMN����Ϊ����IMSI��ֱ�ӷ��� */
    if (NAS_UTRANCTRL_SUPPORT_ALL_SIM_AUTO_SWITCH_UTRAN_NUM == pstNvimUtranModeAutoSwitch->ucImsiPlmnListNum)
    {
        pstUtranModeAutoSwitch->ucImsiPlmnListNum = NAS_UTRANCTRL_SUPPORT_ALL_SIM_AUTO_SWITCH_UTRAN_NUM;

        /* ��ά�ɲ�UTRANģʽ�Զ��л���Ϣ��ӡ */
        NAS_UTRANCTRL_SndOmUtranModeAutoSwitchInfo();

        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimUtranModeAutoSwitch);

        return;
    }

    /* �����ǰ��TD��Plmn�ĸ������������ֵ����ȡ���ֵ��������ǰ��PLMN ID������� */
    if ( pstNvimUtranModeAutoSwitch->ucImsiPlmnListNum > NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM )
    {
        pstNvimUtranModeAutoSwitch->ucImsiPlmnListNum = NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM;
    }

    for (i = 0 ; i < pstNvimUtranModeAutoSwitch->ucImsiPlmnListNum; i++)
    {
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstNvimUtranModeAutoSwitch->astImsiPlmnList[i].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
        NAS_UTRANCTRL_ConvertSimPlmnToNasPlmn(&stSimPlmn, &stPlmn);

        /* �жϵ�ǰ��PLMN ID�Ƿ���Ч������Ч�򿽱����ڴ��� */
        if ( VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn) )
        {
            pstUtranModeAutoSwitch->astImsiPlmnList[pstUtranModeAutoSwitch->ucImsiPlmnListNum] = stPlmn;

            pstUtranModeAutoSwitch->ucImsiPlmnListNum++;
        }
    }

    /* ��ά�ɲ�UTRANģʽ�Զ��л���Ϣ��ӡ */
    NAS_UTRANCTRL_SndOmUtranModeAutoSwitchInfo();

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimUtranModeAutoSwitch);

    return;
}







VOS_VOID NAS_UTRANCTRL_ReadUtranModeNvim( VOS_VOID )
{
    NAS_UTRANCTRL_NVIM_UTRAN_MODE_STRU  stUtranMode;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stUtranMode, 0x00, sizeof(NAS_UTRANCTRL_NVIM_UTRAN_MODE_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Utran_Mode, &ulLength);
    if (ulLength > sizeof(stUtranMode))
    {
        return;
    }

    if ( NV_OK != NV_Read(en_NV_Item_Utran_Mode, &stUtranMode, ulLength) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ReadUtranModeNvim():WARNING: en_NV_Item_Utran_Mode Error");

        return;
    }

    /* ��NVIM�ж�ȡ��UTRANģʽ���浽NASUTRANCTRL�е�ȫ�ֱ����� */
    NAS_UTRANCTRL_SetCurrUtranMode(stUtranMode.ucUtranMode);

    return;
}




VOS_VOID NAS_UTRANCTRL_ReadSmcCtrlFlgNvim( VOS_VOID )
{
    NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU                   stSmcCtrlFlg;

    PS_MEM_SET(&stSmcCtrlFlg, 0x00, sizeof(NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU));

    if ( NV_OK != NV_Read(en_NV_Item_SMC_Ctrl_Flg, &stSmcCtrlFlg, sizeof(NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU)) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ReadSmcCtrlFlgNvim():WARNING: en_NV_Item_SMC_Ctrl_Flg Error");

        return;
    }

    /* NV�е��쳣ԭ��ֵת�� */
    if ( (VOS_FALSE != stSmcCtrlFlg.ucIsUtranTddCsSmcNeeded)
      && (VOS_TRUE  != stSmcCtrlFlg.ucIsUtranTddCsSmcNeeded))
    {
        stSmcCtrlFlg.ucIsUtranTddCsSmcNeeded = VOS_TRUE;
    }

    if ( (VOS_FALSE != stSmcCtrlFlg.ucIsUtranTddPsSmcNeeded)
      && (VOS_TRUE  != stSmcCtrlFlg.ucIsUtranTddPsSmcNeeded))
    {
        stSmcCtrlFlg.ucIsUtranTddPsSmcNeeded = VOS_TRUE;
    }

    /* ����NVIM�е�UTRAN TDDģʽ���Ƿ���Ҫ���SMC����ֵ */
    NAS_UTRANCTRL_SetUtranTddCsSmcNeededFlg(stSmcCtrlFlg.ucIsUtranTddCsSmcNeeded);
    NAS_UTRANCTRL_SetUtranTddPsSmcNeededFlg(stSmcCtrlFlg.ucIsUtranTddPsSmcNeeded);

    return;
}


VOS_VOID NAS_UTRANCTRL_WriteUtranModeNvim(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8  enCurrentUtranMode
)
{
    NAS_UTRANCTRL_NVIM_UTRAN_MODE_STRU  stUtranMode;
    VOS_UINT32                          ulNvLength;

    stUtranMode.ucReserve   = 0;
    stUtranMode.ucUtranMode = enCurrentUtranMode;
    ulNvLength              = 0;

    /* ��NV�л�ȡen_NV_Item_Utran_Mode NV������ */
    (VOS_VOID)NV_GetLength(en_NV_Item_Utran_Mode, &ulNvLength);
    if ( NV_OK != NV_Write(en_NV_Item_Utran_Mode, &stUtranMode, ulNvLength) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_WriteUtranModeNvim:ERROR: NV_Write Error");

        return;
    }

    return;
}

#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

