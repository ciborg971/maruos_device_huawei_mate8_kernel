
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasCcCtx.h"
#include "NasCcProcNvim.h"
#include "NVIM_Interface.h"
#include "NasCcCommon.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"

#include "NasUsimmApi.h"
#include "NasCcTimer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_CC_PROC_NIVM_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/


VOS_VOID  NAS_CC_ReadCcTimerLenNvim( VOS_VOID )
{
    NAS_CC_NVIM_TIMER_LEN_STRU          stNasCcTimerLen;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulTimerLength;

    ulLength = 0;

    ulTimerLength = 0;

    PS_MEM_SET(&stNasCcTimerLen, 0, sizeof(NAS_CC_NVIM_TIMER_LEN_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_CC_TimerLen, &ulLength);
    if (ulLength > sizeof(NAS_CC_NVIM_TIMER_LEN_STRU))
    {
        return;
    }

    if (VOS_OK != NV_Read(en_NV_Item_CC_TimerLen,
                         &stNasCcTimerLen, ulLength))
    {
        NAS_CC_WARN_LOG("NAS_CC_ReadCcTimerLenNvim():WARNING: en_NV_Item_CC_TimerLen Error");

        return;
    }

    /* ���NV�����õ�ֵΪ0���ߴ��ڵ���30s������Э��Ĭ��ֵ30s����������Ϊ��Чֵ����Ҫ�������� */
    if ((stNasCcTimerLen.ucT305Len > 0)
      &&(stNasCcTimerLen.ucT305Len < 30))
    {
        /* ����T305��ʱ�� */
        ulTimerLength = NAS_CC_ONE_THOUSAND_MILLISECOND * ((VOS_UINT32)stNasCcTimerLen.ucT305Len);
        NAS_CC_SetNvTimerLen(TI_NAS_CC_T305, ulTimerLength);
    }
    else
    {
        /* ����T305��ʱ�� */
        ulTimerLength = 30000;
        NAS_CC_SetNvTimerLen(TI_NAS_CC_T305, ulTimerLength);
    }

    if ((stNasCcTimerLen.ucT308Len > 0)
      &&(stNasCcTimerLen.ucT308Len < 30))
    {
        /* ����T308��ʱ�� */
        ulTimerLength = NAS_CC_ONE_THOUSAND_MILLISECOND * ((VOS_UINT32)stNasCcTimerLen.ucT308Len);
        NAS_CC_SetNvTimerLen(TI_NAS_CC_T308, ulTimerLength);
    }
    else
    {
        /* ����T308��ʱ�� */
        ulTimerLength = 30000;
        NAS_CC_SetNvTimerLen(TI_NAS_CC_T308, ulTimerLength);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_ReadCcT303LenNvim
 ��������  : ��ȡNVIM�е�en_NV_Item_CC_TimerLen������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��20��
    ��    ��   : wx270776
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_CC_ReadCcT303LenNvim( VOS_VOID )
{
    NAS_CC_NVIM_T303_LEN_CFG_STRU       stNasCcT303Len;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulTimerLength;

    ulLength                          = 0;
    ulTimerLength                     = 0;
    PS_MEM_SET(&stNasCcT303Len, 0, sizeof(NAS_CC_NVIM_T303_LEN_CFG_STRU));

    /* ��ȡNV��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_CC_T303_Len_Cfg, &ulLength);
    if (ulLength > sizeof(NAS_CC_NVIM_T303_LEN_CFG_STRU))
    {
        return;
    }

    /* ��ȡNV */
    if (VOS_OK != NV_Read(en_NV_Item_CC_T303_Len_Cfg, &stNasCcT303Len, ulLength))
    {
        NAS_CC_WARN_LOG("NAS_CC_ReadCcT303LenNvim():WARNING: en_NV_Item_CC_T303Len Error");

        return;
    }

    /* δ����T303��ʱ��ʱȡĬ��ʱ�� */
    if (VOS_TRUE != stNasCcT303Len.ucT303ActiveFlag)
    {
        return;
    }

    if (stNasCcT303Len.ucT303Len < TI_NAS_CC_T303_DEFAULT_LEN)
    {
        /* ʱ��С��30��ȡ30�� */
        ulTimerLength = NAS_CC_ONE_THOUSAND_MILLISECOND * TI_NAS_CC_T303_DEFAULT_LEN;
        NAS_CC_SetNvTimerLen(TI_NAS_CC_T303, ulTimerLength);
    }
    else
    {
        /* ����T303ʱ�� */
        ulTimerLength = NAS_CC_ONE_THOUSAND_MILLISECOND * ((VOS_UINT32)stNasCcT303Len.ucT303Len);
        NAS_CC_SetNvTimerLen(TI_NAS_CC_T303, ulTimerLength);
    }

    return;
}
VOS_VOID  NAS_CC_ReadCcbsNvim( VOS_VOID )
{
    NAS_NVIM_CCBS_SUPPORT_FLG_STRU   stCcbsSupportFlg;
    NAS_CC_CUSTOM_CFG_INFO_STRU        *pstCcbsSupportFlg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength = 0;


    stCcbsSupportFlg.ucCcbsSupportFlg = NAS_CC_NV_ITEM_DEACTIVE;

    pstCcbsSupportFlg = NAS_CC_GetCustomCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_CCBS_SUPPORT_FLG, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_CCBS_SUPPORT_FLG_STRU))
    {
        return;
    }

    if (VOS_OK != NV_Read(en_NV_Item_NVIM_CCBS_SUPPORT_FLG,
                         &stCcbsSupportFlg, ulLength))
    {
        NAS_CC_WARN_LOG("NAS_CC_ReadCcbsNvim():WARNING: en_NV_Item_NVIM_CCBS_SUPPORT_FLG Error");

        return;
    }


    if ((NAS_CC_NV_ITEM_ACTIVE != stCcbsSupportFlg.ucCcbsSupportFlg)
     && (NAS_CC_NV_ITEM_DEACTIVE != stCcbsSupportFlg.ucCcbsSupportFlg))
    {
        pstCcbsSupportFlg->ucCcbsSupportFlg = NAS_CC_NV_ITEM_DEACTIVE;
        NAS_CC_WARN_LOG("NAS_CC_ReadCcbsNvim():WARNING: NV parameter Error");
        return;
    }

    pstCcbsSupportFlg->ucCcbsSupportFlg = stCcbsSupportFlg.ucCcbsSupportFlg;

    return;
}

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID NAS_CC_ReadErrlogCtrlInfoNvim(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;
    NV_ID_ERR_LOG_CTRL_INFO_STRU        stErrorLogCtrlInfo;

    ulLength = 0;
    PS_MEM_SET(&stErrorLogCtrlInfo, 0x00, sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_ErrLogCtrlInfo, &ulLength);

    ulResult = NV_Read(en_NV_Item_ErrLogCtrlInfo,
                       &stErrorLogCtrlInfo,
                       ulLength);

    if (ulResult == NV_OK)
    {
        NAS_CC_SetErrlogCtrlFlag(stErrorLogCtrlInfo.ucAlmStatus);
        NAS_CC_SetErrlogAlmLevel(stErrorLogCtrlInfo.ucAlmLevel);
    }
    else
    {
        NAS_CC_SetErrlogCtrlFlag(VOS_FALSE);
        NAS_CC_SetErrlogAlmLevel(NAS_ERR_LOG_CTRL_LEVEL_CRITICAL);
    }

    return;
}
#endif

VOS_VOID NAS_CC_ReadNvimInfo(VOS_VOID)
{
    /* en_NV_Item_NVIM_CCBS_SUPPORT_FLG */
    NAS_CC_ReadCcbsNvim();

    /* en_NV_Item_CC_TimerLen */
    NAS_CC_ReadCcTimerLenNvim();

    NAS_CC_ReadCcT303LenNvim();

    NAS_CC_ReadProceedingStartT310Nvim();

    return;
}


VOS_VOID  NAS_CC_ReadProceedingStartT310Nvim( VOS_VOID )
{
    NAS_NVIM_PROGRESS_INDICATOR_START_T310_INFO_STRU    stProceedingT310;

    PS_MEM_SET(&stProceedingT310, 0, sizeof(NAS_NVIM_PROGRESS_INDICATOR_START_T310_INFO_STRU));

    /* ����Ĭ��ֵ */
    NAS_CC_SetProceedingStartT310Flag(VOS_FALSE);

    /* ��ȡNV */
    if (VOS_OK != NV_Read(en_NV_Item_PROGRESS_INDICATOR_START_T310_INFO, &stProceedingT310, sizeof(stProceedingT310)))
    {
        NAS_CC_WARN_LOG("NAS_CC_ReadProceedingStartT310Nvim():WARNING: en_NV_Item_PROGRESS_INDICATOR_START_T310_INFO Error");

        return;
    }

    if (VOS_TRUE  == stProceedingT310.ucIsStartT310AccordWith3GPP)
    {
        NAS_CC_SetProceedingStartT310Flag(VOS_TRUE);
    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



