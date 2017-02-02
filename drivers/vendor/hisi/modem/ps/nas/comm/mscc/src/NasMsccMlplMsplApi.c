


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMsccMlplMsplApi.h"
#include "NasMsccComFunc.h"
#include "NasMsccCtx.h"
#include "NasMsccMntn.h"
#include "PsCommonDef.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_MLPL_MSPL_API_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_UINT8 NAS_MSCC_GetHigherPriMsplSysListThan3gpp(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;

    PS_MEM_SET(pstOutSysList, 0, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    /* ���MLPL MSPL�����ã�ֱ�ӷ���VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_HIGH_PRI_SYS;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_3GPP;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstIn3gppInfo;
    stLogMatchRsltInput.pstMsplSysList = pstOutSysList;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* ��MLPL�����ҵ���ǰ3gppϵͳƥ���������ȼ�MLPL��¼�����ض�Ӧ��MLPL��¼��MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy3gppSys(pstIn3gppInfo, pstMlpl,
                                                    &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* �����MLPL�б����Ҳ���ƥ���MLPL��¼������Default MLPL���ã���ȡDefault MLPL��MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* ��MSPL�б����ҵ�MSPL_INDEX��Ӧ��MSPL��ָ�� */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* ��MSPL��¼�����ҵ�ƥ�䵱ǰϵͳ��MSPL��¼���±� */
    if (VOS_FALSE == NAS_MSCC_Get3gppMatchedMsplRecIndex(pstIn3gppInfo, pstMatchedMsplTable,
                                                         &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* ���ƥ�䵽MSPL���еĵ�һ����¼��˵����������ȼ������� */
    if (0 == ucMatchedMsplRecId)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }

    /* ��ȡMSPL���бȵ�ǰϵͳ���ȼ��ߵ���ѡϵͳ�б� */
    NAS_MSCC_GetHigherSysListThanSpecRecIndexSys(pstMatchedMsplTable, ucMatchedMsplRecId,
                                                 pstOutSysList);

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return VOS_TRUE;
}
VOS_UINT8 NAS_MSCC_GetHigherPriMsplSysListThan1x(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;

    PS_MEM_SET(pstOutSysList, 0, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    /* ���MLPL MSPL�����ã�ֱ�ӷ���VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_HIGH_PRI_SYS;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstIn1xInfo;
    stLogMatchRsltInput.pstMsplSysList = pstOutSysList;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* ��MLPL�����ҵ���ǰ1xϵͳƥ���MLPL��¼�����ض�Ӧ��MLPL��¼��MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy1xSys(pstIn1xInfo, pstMlpl,
                                                  &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* �����MLPL�б����Ҳ���ƥ���MLPL��¼������Default MLPL���ã���ȡDefault MLPL��MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* ��MSPL�б����ҵ�MSPL_INDEX��Ӧ��MSPL��ָ�� */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* ��MSPL��¼�����ҵ�ƥ�䵱ǰϵͳ��MSPL��¼���±� */
    if (VOS_FALSE == NAS_MSCC_Get1xMatchedMsplRecIndex(pstIn1xInfo, pstMatchedMsplTable,
                                                       &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    if (0 == ucMatchedMsplRecId)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }

    /* ��ȡMSPL���бȵ�ǰϵͳ���ȼ��ߵ���ѡϵͳ�б� */
    NAS_MSCC_GetHigherSysListThanSpecRecIndexSys(pstMatchedMsplTable, ucMatchedMsplRecId,
                                                 pstOutSysList);

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return VOS_TRUE;
}



VOS_UINT8 NAS_MSCC_GetHigherPriMsplSysListThanHrpd(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;

    PS_MEM_SET(pstOutSysList, 0, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    /* ���MLPL MSPL�����ã�ֱ�ӷ���VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_HIGH_PRI_SYS;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_HRPD;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstInHrpdInfo;
    stLogMatchRsltInput.pstMsplSysList = pstOutSysList;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* ��MLPL�����ҵ���ǰhrpdϵͳƥ���MLPL��¼�����ض�Ӧ��MLPL��¼��MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexByHrpdSys(pstInHrpdInfo, pstMlpl,
                                                    &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* �����MLPL�б����Ҳ���ƥ���MLPL��¼������Default MLPL���ã���ȡDefault MLPL��MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* ��MSPL�б����ҵ�MSPL_INDEX��Ӧ��MSPL��ָ�� */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }


    /* ��MSPL��¼�����ҵ�ƥ�䵱ǰϵͳ��MSPL��¼���±� */
    if (VOS_FALSE == NAS_MSCC_GetHrpdMatchedMsplRecIndex(pstInHrpdInfo, pstMatchedMsplTable,
                                                         &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    if (0 == ucMatchedMsplRecId)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }

    /* ��ȡMSPL���бȵ�ǰϵͳ���ȼ��ߵ���ѡϵͳ�б� */
    NAS_MSCC_GetHigherSysListThanSpecRecIndexSys(pstMatchedMsplTable,
                                                 ucMatchedMsplRecId, pstOutSysList);

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetHigherPriMsplSysListThanHrpdBy1xLoc
Description     :   When Mcc in overhead msg is invalid,use 1x sysinfo to get mspl prefer syslist
                    Then use HRPD info to get sys list prefered than hrpd
Input parameters:   NAS_MSCC_1X_SYS_INFO_STRU                              *pstIn1xInfo
                    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo

Output parameters:  NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-5-7
        Author  :   t00323010
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetHigherPriMsplSysListThanHrpdBy1xLoc(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;

    PS_MEM_SET(pstOutSysList, 0, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    /* ���MLPL MSPL�����ã�ֱ�ӷ���VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose     = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_MSPL_INDEX_OF_1X;
    stLogMatchRsltInput.enSysRat           = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X;
    stLogMatchRsltInput.pvSysInfo          = (VOS_VOID *)pstIn1xInfo;
    stLogMatchRsltInput.pstMsplSysList     = VOS_NULL_PTR;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
    stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* ��MLPL�����ҵ���ǰ1xϵͳƥ���MLPL��¼�����ض�Ӧ��MLPL��¼��MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy1xSys(pstIn1xInfo, pstMlpl,
                                                  &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* �����MLPL�б����Ҳ���ƥ���MLPL��¼������Default MLPL���ã���ȡDefault MLPL��MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose     = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_HIGH_PRI_SYS_THAN_HRPD_BY_1X_LOC;
    stLogMatchRsltInput.enSysRat           = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_HRPD;
    stLogMatchRsltInput.pvSysInfo          = (VOS_VOID *)pstInHrpdInfo;
    stLogMatchRsltInput.pstMsplSysList     = pstOutSysList;
    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;;
    stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_BUTT;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
    stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;

    /* ��MSPL�б����ҵ�MSPL_INDEX��Ӧ��MSPL��ָ�� */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* ��MSPL��¼�����ҵ�ƥ�䵱ǰϵͳ��MSPL��¼���±� */
    if (VOS_FALSE == NAS_MSCC_GetHrpdMatchedMsplRecIndex(pstInHrpdInfo, pstMatchedMsplTable,
                                                         &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    if (0 == ucMatchedMsplRecId)
    {
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_TRUE;
    }

    /* ��ȡMSPL���бȵ�ǰϵͳ���ȼ��ߵ���ѡϵͳ�б� */
    NAS_MSCC_GetHigherSysListThanSpecRecIndexSys(pstMatchedMsplTable,
                                                 ucMatchedMsplRecId, pstOutSysList);

    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return VOS_TRUE;
}


VOS_UINT8 NAS_MSCC_GetMsplSysListBy1xLoc(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucLoop;
    VOS_UINT8                                               ucMatchedMsplIndex;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;

    PS_MEM_SET(pstOutSysList, 0, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    /* ���MLPL MSPL�����ã�ֱ�ӷ���VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_ALL_SYS_OF_1X;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstIn1xInfo;
    stLogMatchRsltInput.pstMsplSysList = pstOutSysList;

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* ��MLPL�����ҵ���ǰ1xϵͳƥ���������ȼ�MLPL��¼�����ض�Ӧ��MLPL��¼��MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy1xSys(pstIn1xInfo, pstMlpl,
                                                  &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* �����MLPL�б����Ҳ���ƥ���MLPL��¼������Default MLPL���ã���ȡDefault MLPL��MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* ��MSPL�б����ҵ�MSPL_INDEX��Ӧ��MSPL��ָ�� */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* �����ǰMSPL�������е���ѡϵͳ */
    for (ucLoop = 0; ucLoop < pstMatchedMsplTable->ucNumMsplRec; ucLoop++)
    {
        if (VOS_FALSE == pstMatchedMsplTable->astMsplRec[ucLoop].ucIsValid)
        {
            continue;
        }

        pstOutSysList->astSysList[pstOutSysList->ucSysCount].enSysType  =
                                    pstMatchedMsplTable->astMsplRec[ucLoop].enSysType;

        pstOutSysList->astSysList[pstOutSysList->ucSysCount].enPriClass =
                                    pstMatchedMsplTable->astMsplRec[ucLoop].enPriClass;


        pstOutSysList->ucSysCount++;
    }

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
    stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return VOS_TRUE;
}
VOS_UINT8 NAS_MSCC_GetCurr3gppSysBsrTimerLen(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    VOS_UINT32                                             *pulOutBsrTimerLenMilliSec
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;
    VOS_UINT8                                               ucGetBsrTimerLenRslt;

    *pulOutBsrTimerLenMilliSec = 0;

    /* ���MLPL MSPL�����ã�ֱ�ӷ���VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_BSR_TIMER_LEN;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_3GPP;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstIn3gppInfo;
    stLogMatchRsltInput.pstMsplSysList = VOS_NULL_PTR;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* ��MLPL�����ҵ���ǰ3gppϵͳƥ���������ȼ�MLPL��¼�����ض�Ӧ��MLPL��¼��MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy3gppSys(pstIn3gppInfo, pstMlpl,
                                                    &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* �����MLPL�б����Ҳ���ƥ���MLPL��¼������Default MLPL���ã���ȡDefault MLPL��MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* ��MSPL�б����ҵ�MSPL_INDEX��Ӧ��MLPL��ָ�� */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* ��MSPL��¼�����ҵ�ƥ�䵱ǰϵͳ��MSPL��¼���±� */
    if (VOS_FALSE == NAS_MSCC_Get3gppMatchedMsplRecIndex(pstIn3gppInfo, pstMatchedMsplTable,
                                                         &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* ��ƥ�䵽��MSPL��¼�е�BSR��ʱ��ö��ת���ɺ��� */
    ucGetBsrTimerLenRslt = NAS_MSCC_ConvertMsplBsrTimerLenToMillisec(
                            pstMatchedMsplTable->astMsplRec[ucMatchedMsplRecId].enHigherPriSrchTime,
                            pulOutBsrTimerLenMilliSec);

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;
    stLogMatchRsltInput.ulBsrTimerLen      = *pulOutBsrTimerLenMilliSec;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return ucGetBsrTimerLenRslt;
}



VOS_UINT8 NAS_MSCC_GetCurr1xSysBsrTimerLen(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    VOS_UINT32                                             *pulOutBsrTimerLenMilliSec
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;
    VOS_UINT8                                               ucGetBsrTimerLenRslt;

    *pulOutBsrTimerLenMilliSec = 0;

    /* ���MLPL MSPL�����ã�ֱ�ӷ���VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_BSR_TIMER_LEN;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstIn1xInfo;
    stLogMatchRsltInput.pstMsplSysList = VOS_NULL_PTR;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* ��MLPL�����ҵ���ǰ1xϵͳƥ���������ȼ�MLPL��¼�����ض�Ӧ��MLPL��¼��MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy1xSys(pstIn1xInfo, pstMlpl,
                                                  &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* �����MLPL�б����Ҳ���ƥ���MLPL��¼������Default MLPL���ã���ȡDefault MLPL��MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* ��MSPL�б����ҵ�MSPL_INDEX��Ӧ��MLPL��ָ�� */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* ��MSPL��¼�����ҵ�ƥ�䵱ǰϵͳ��MSPL��¼���±� */
    if (VOS_FALSE == NAS_MSCC_Get1xMatchedMsplRecIndex(pstIn1xInfo, pstMatchedMsplTable,
                                                       &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* ��ƥ�䵽��MSPL��¼�е�BSR��ʱ��ö��ת���ɺ��� */
    ucGetBsrTimerLenRslt = NAS_MSCC_ConvertMsplBsrTimerLenToMillisec(
                            pstMatchedMsplTable->astMsplRec[ucMatchedMsplRecId].enHigherPriSrchTime,
                            pulOutBsrTimerLenMilliSec);

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;
    stLogMatchRsltInput.ulBsrTimerLen      = *pulOutBsrTimerLenMilliSec;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return ucGetBsrTimerLenRslt;
}



VOS_UINT8 NAS_MSCC_GetCurrHrpdSysBsrTimerLen(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    VOS_UINT32                                             *pulOutBsrTimerLenMilliSec
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;
    VOS_UINT8                                               ucGetBsrTimerLenRslt;

    *pulOutBsrTimerLenMilliSec = 0;

    /* ���MLPL MSPL�����ã�ֱ�ӷ���VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_BSR_TIMER_LEN;
    stLogMatchRsltInput.enSysRat       = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_HRPD;
    stLogMatchRsltInput.pvSysInfo      = (VOS_VOID *)pstInHrpdInfo;
    stLogMatchRsltInput.pstMsplSysList = VOS_NULL_PTR;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* ��MLPL�����ҵ���ǰhrpdϵͳƥ���������ȼ�MLPL��¼�����ض�Ӧ��MLPL��¼��MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexByHrpdSys(pstInHrpdInfo, pstMlpl,
                                                    &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* �����MLPL�б����Ҳ���ƥ���MLPL��¼������Default MLPL���ã���ȡDefault MLPL��MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;
            stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    /* ��MSPL�б����ҵ�MSPL_INDEX��Ӧ��MLPL��ָ�� */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* ��MSPL��¼�����ҵ�ƥ�䵱ǰϵͳ��MSPL��¼���±� */
    if (VOS_FALSE == NAS_MSCC_GetHrpdMatchedMsplRecIndex(pstInHrpdInfo, pstMatchedMsplTable,
                                                         &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
        stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
        stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
        stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* ��ƥ�䵽��MSPL��¼�е�BSR��ʱ��ö��ת���ɺ��� */
    ucGetBsrTimerLenRslt = NAS_MSCC_ConvertMsplBsrTimerLenToMillisec(
                            pstMatchedMsplTable->astMsplRec[ucMatchedMsplRecId].enHigherPriSrchTime,
                            pulOutBsrTimerLenMilliSec);

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;
    stLogMatchRsltInput.ulBsrTimerLen      = *pulOutBsrTimerLenMilliSec;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return ucGetBsrTimerLenRslt;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetCurrHrpdSysBsrTimerLenBy1xLoc
Description     :   When Mcc in overhead msg is invalid,use 1x sysinfo to get MSPL List
                    Then use Hrpd info to get curr hrpd sys BSR timer len
Input parameters:   NAS_MSCC_1X_SYS_INFO_STRU                              *pstIn1xInfo
                    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo

Output parameters:  VOS_UINT32                                             *pusOutBsrTimerLenMilliSec
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-5-7
        Author  :   t00323010
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetCurrHrpdSysBsrTimerLenBy1xLoc(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    VOS_UINT32                                             *pusOutBsrTimerLenMilliSec
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlpl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_STRU                                     *pstMspl             = VOS_NULL_PTR;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMatchedMsplRecId;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlplRec;
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU       stLogMatchRsltInput;
    VOS_UINT8                                               ucGetBsrTimerLenRslt;

    *pusOutBsrTimerLenMilliSec = 0;

    /* ���MLPL MSPL�����ã�ֱ�ӷ���VOS_FALSE */
    if (VOS_FALSE == NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose     = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_MSPL_INDEX_OF_1X;
    stLogMatchRsltInput.enSysRat           = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X;
    stLogMatchRsltInput.pvSysInfo          = (VOS_VOID *)pstIn1xInfo;
    stLogMatchRsltInput.pstMsplSysList     = VOS_NULL_PTR;
    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
    stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

    pstMlpl = NAS_MSCC_GetMlplInfoAddr();
    pstMspl = NAS_MSCC_GetMsplInfoAddr();

    enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucIsUseDfltMlplRec = VOS_FALSE;

    /* ��MLPL�����ҵ���ǰ1xϵͳƥ���������ȼ�MLPL��¼�����ض�Ӧ��MLPL��¼��MSPL_INDEX */
    if (VOS_FALSE == NAS_MSCC_GetMsplIndexBy1xSys(pstIn1xInfo, pstMlpl,
                                                  &ucMatchedMsplIndex, &enMlplMatchLvl))
    {
        /* �����MLPL�б����Ҳ���ƥ���MLPL��¼������Default MLPL���ã���ȡDefault MLPL��MSPL_INDEX */
        if (VOS_FALSE == pstMlpl->ucIsContainDefRec)
        {
            stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;
            stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
            stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
            stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;

            NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

            return VOS_FALSE;
        }
        else
        {
            ucMatchedMsplIndex = pstMlpl->ucMsplIdxInFirstDefRec;

            ucIsUseDfltMlplRec = VOS_TRUE;
        }
    }

    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.enMlplMatchLvl     = enMlplMatchLvl;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = ucIsUseDfltMlplRec;
    stLogMatchRsltInput.ucMatchedMsplIndex = ucMatchedMsplIndex;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    PS_MEM_SET(&stLogMatchRsltInput, 0, sizeof(NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU));

    stLogMatchRsltInput.enMatchPurpose     = NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_BSR_TIMER_LEN_OF_HRPD_BY_1X_LOC;
    stLogMatchRsltInput.enSysRat           = NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_HRPD;
    stLogMatchRsltInput.pvSysInfo          = (VOS_VOID *)pstInHrpdInfo;
    stLogMatchRsltInput.pstMsplSysList     = VOS_NULL_PTR;
    stLogMatchRsltInput.ucMlplMatchRslt    = VOS_FALSE;;
    stLogMatchRsltInput.enMlplMatchLvl     = NAS_MSCC_MLPL_MATCH_LVL_BUTT;
    stLogMatchRsltInput.ucIsUseDfltMlpLRec = VOS_FALSE;
    stLogMatchRsltInput.ucMatchedMsplIndex = NAS_MSCC_INVALID_MSPL_INDEX;

    /* ��MSPL�б����ҵ�MSPL_INDEX��Ӧ��MLPL��ָ�� */
    pstMatchedMsplTable = NAS_MSCC_GetMsplTableByMsplIndex(pstMspl, ucMatchedMsplIndex);

    if (VOS_NULL_PTR == pstMatchedMsplTable)
    {
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* ��MSPL��¼�����ҵ�ƥ�䵱ǰHRPDϵͳ��MSPL��¼���±� */
    if (VOS_FALSE == NAS_MSCC_GetHrpdMatchedMsplRecIndex(pstInHrpdInfo, pstMatchedMsplTable,
                                                         &ucMatchedMsplRecId))
    {
        stLogMatchRsltInput.ucMsplMatchRslt    = VOS_FALSE;
        stLogMatchRsltInput.ucMatchedMsplRecId = NAS_MSCC_INVALID_MSPL_REC_ID;

        NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

        return VOS_FALSE;
    }

    /* ��ƥ�䵽��MSPL��¼�е�BSR��ʱ��ö��ת���ɺ��� */
    ucGetBsrTimerLenRslt = NAS_MSCC_ConvertMsplBsrTimerLenToMillisec(
                            pstMatchedMsplTable->astMsplRec[ucMatchedMsplRecId].enHigherPriSrchTime,
                            pusOutBsrTimerLenMilliSec);

    stLogMatchRsltInput.ucMsplMatchRslt    = VOS_TRUE;
    stLogMatchRsltInput.ucMatchedMsplRecId = ucMatchedMsplRecId;
    stLogMatchRsltInput.ulBsrTimerLen      = *pusOutBsrTimerLenMilliSec;

    NAS_MSCC_MNTN_LogMlplMsplMatchRslt(&stLogMatchRsltInput);

    return ucGetBsrTimerLenRslt;
}


VOS_UINT8 NAS_MSCC_GetMsplIndexBy3gppSys(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    NAS_MSCC_MLPL_STRU                                     *pstInMlplInfo,
    VOS_UINT8                                              *pucOutMsplIndex,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
)
{
    VOS_UINT8                                               ucLoop;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enBestLvl;
    VOS_UINT8                                               ucBestLvlRecId;

    enBestLvl      = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucBestLvlRecId = 0;

    for (ucLoop = 0; ucLoop < pstInMlplInfo->stMlplHdr.ucNumMlplRec; ucLoop++)
    {
        enMlplMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        /* ��ǰϵͳ�͵���MLPL��¼�Ƚϣ���ȡƥ�伶�� */
        NAS_MSCC_Compare3gppSysWithMlplRec(pstIn3gppInfo, pstInMlplInfo->apstMlplRec[ucLoop],
                                           &enMlplMatchLvl);

        /* ���ƥ�䵽���ȼ���ߵ�MLPL��¼���˳�ѭ�� */
        if (NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC == enMlplMatchLvl)
        {
            enBestLvl      = NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC;
            ucBestLvlRecId = ucLoop;

            break;
        }

        if (enMlplMatchLvl > enBestLvl)
        {
            enBestLvl      = enMlplMatchLvl;
            ucBestLvlRecId = ucLoop;
        }
    }

    if (NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH != enBestLvl)
    {
        *pucOutMsplIndex = pstInMlplInfo->apstMlplRec[ucBestLvlRecId]->ucMsplIndex;
        *penOutMatchLvl  = enBestLvl;

        return VOS_TRUE;
    }

    *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_GetMsplIndexBy1xSys(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MLPL_STRU                                     *pstInMlplInfo,
    VOS_UINT8                                              *pucOutMsplIndex,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
)
{
    VOS_UINT8                                               ucLoop;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enBestLvl;
    VOS_UINT8                                               ucBestLvlRecId;

    enBestLvl      = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucBestLvlRecId = 0;

    for (ucLoop = 0; ucLoop < pstInMlplInfo->stMlplHdr.ucNumMlplRec; ucLoop++)
    {
        enMlplMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        /* ��ǰϵͳ�͵���MLPL��¼�Ƚϣ���ȡƥ�伶�� */
        NAS_MSCC_Compare1xSysWithMlplRec(pstIn1xInfo, pstInMlplInfo->apstMlplRec[ucLoop],
                                         &enMlplMatchLvl);

        /* ƥ�䵽���ȼ���ߵ�MLPL��¼���˳�ѭ�� */
        if (NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC_LOC == enMlplMatchLvl)
        {
            enBestLvl      = NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC_LOC;
            ucBestLvlRecId = ucLoop;

            break;
        }

        if (enMlplMatchLvl > enBestLvl)
        {
            enBestLvl      = enMlplMatchLvl;
            ucBestLvlRecId = ucLoop;
        }
    }

    if (NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH != enBestLvl)
    {
        *pucOutMsplIndex = pstInMlplInfo->apstMlplRec[ucBestLvlRecId]->ucMsplIndex;
        *penOutMatchLvl  = enBestLvl;

        return VOS_TRUE;
    }

    *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_GetMsplIndexByHrpdSys(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MLPL_STRU                                     *pstInMlplInfo,
    VOS_UINT8                                              *pucOutMsplIndex,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
)
{
    VOS_UINT8                                               ucLoop;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enBestLvl;
    VOS_UINT8                                               ucBestLvlRecId;

    enBestLvl      = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
    ucBestLvlRecId = 0;

    for (ucLoop = 0; ucLoop < pstInMlplInfo->stMlplHdr.ucNumMlplRec; ucLoop++)
    {
        enMlplMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        /* ��ǰϵͳ�͵���MLPL��¼�Ƚϣ���ȡƥ�伶�� */
        NAS_MSCC_CompareHrpdSysWithMlplRec(pstInHrpdInfo, pstInMlplInfo->apstMlplRec[ucLoop],
                                           &enMlplMatchLvl);

        /* ƥ�䵽���ȼ���ߵ�MLPL��¼���˳�ѭ�� */
        if (NAS_MSCC_MLPL_MATCH_LVL_MCC_LOC == enMlplMatchLvl)
        {
            enBestLvl      = NAS_MSCC_MLPL_MATCH_LVL_MCC_LOC;
            ucBestLvlRecId = ucLoop;

            break;
        }

        if (enMlplMatchLvl > enBestLvl)
        {
            enBestLvl      = enMlplMatchLvl;
            ucBestLvlRecId = ucLoop;
        }
    }

    if (NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH != enBestLvl)
    {
        *pucOutMsplIndex = pstInMlplInfo->apstMlplRec[ucBestLvlRecId]->ucMsplIndex;
        *penOutMatchLvl  = enBestLvl;

        return VOS_TRUE;
    }

    *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    return VOS_FALSE;
}



NAS_MSCC_MSPL_ID_STRU* NAS_MSCC_GetMsplTableByMsplIndex(
    NAS_MSCC_MSPL_STRU                                     *pstInMsplInfo,
    VOS_UINT8                                               ucInMsplIndex
)
{
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;
    VOS_UINT8                                               ucLoop;

    for (ucLoop = 0; ucLoop < pstInMsplInfo->stMsplHdr.ucNumMsplId; ucLoop++)
    {
        if ((VOS_TRUE      == pstInMsplInfo->apstMsplId[ucLoop]->ucIsMsplIdValid)
         && (ucInMsplIndex == pstInMsplInfo->apstMsplId[ucLoop]->ucMsplId))
        {
            pstMatchedMsplTable = (pstInMsplInfo->apstMsplId[ucLoop]);

            break;
        }
    }

    return pstMatchedMsplTable;
}



VOS_VOID NAS_MSCC_Compare3gppSysWithMlplRec(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstInMlplRec,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
)
{
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMatchLvl;
    VOS_UINT32                                              ulNasStyleMcc;
    VOS_UINT32                                              ulNasStyleMnc;


    /*
        3GPPƥ�����

        1�����TAG_MCC��FALSE������ƥ��TAG_LOC����TAG_LOC����PLMN�б����ƥ��ɹ�����ƥ�伶��ΪMCC_MNC������Ϊ��ƥ�䡣

        2��PLMN�б��죺���ж�TAG_LOC��¼�е���ʽ�Ƿ��פ����ʽƥ�䣬�����ƥ�䣬�������ü�¼
         �PPLMN_STARTֱ�Ӽ���PLMN�б����ж��Ƿ���PLMN Selector List�С�
           PLMN_RANGE��ʹ�ã�����PLMN Selector List��ƥ�䵽PLMN_START���±꣬
           Ȼ���PLMN_START�±꿪ʼ����PLMN Selector List��PLMN_RANGE�±귶Χ�ڵ�PLMN���뵽PLMN�б�

        3�����TAG_MCC��TRUE��MCC��ͬ��TAG_MCC��TAG_MNCΪ��ƥ�䣬����ƥ��TAG_LOC��
           ���TAG_LOCƥ�� ��ƥ�伶��ΪMCC_MNC������Ϊ��MLPL��¼��ƥ�䡣

        4�����TAG_MCC��TRUE��MCC��ͬ��TAG_MNC��TRUE��MNC��ͨ�������ͬ����ƥ�伶��ΪMCC_MNC��
           ���MNC����ͨ������Ҳ�ͬ��TAG_MCC��TAG_MNCΪ��ƥ�䣬����ƥ��TAG_LOC��

        5�����TAG_MCC��TRUE��MCC��ͬ��TAG_MNC��FALSE��ƥ�伶��ΪMCC������ƥ��TAG_LOC��
           ��TAG_LOC�Ƿ���ƥ�䵽���ȼ�ΪMCC_MNC�ļ�¼��

        6��ƥ�����ȼ���С��MCC_MNC > MCC

        ����ʵ����������߼�
     */

    if (VOS_FALSE == pstInMlplRec->ucIsRecValid)
    {
        *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        return;
    }

    enMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    if (NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC ==
            (NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC & pstInMlplRec->ucLocParamType))
    {
        ulNasStyleMcc = NAS_MSCC_ConvertMlplMccToNasStyleMcc(pstInMlplRec->stLocParamVal.usMcc);

        if (pstIn3gppInfo->stPlmnId.ulMcc == ulNasStyleMcc)
        {
            enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_MCC;

            if (NAS_MSCC_MLPL_LOC_PARAM_BIT_MNC ==
                    (NAS_MSCC_MLPL_LOC_PARAM_BIT_MNC & pstInMlplRec->ucLocParamType))
            {
                if (NAS_MSCC_MLPL_WILDCARD_MNC == pstInMlplRec->stLocParamVal.usMnc)
                {
                    enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_MNC;
                }
                else
                {
                    ulNasStyleMnc = NAS_MSCC_ConvertMlplMncToNasStyleMnc(
                                                                pstInMlplRec->stLocParamVal.usMnc);

                    if (pstIn3gppInfo->stPlmnId.ulMnc == ulNasStyleMnc)
                    {

                        enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_MNC;
                    }
                    else
                    {
                        enMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;
                    }
                }
            }
        }
    }

    /* TAG_MCC��TAG_MNCƥ�䵽������ȼ������� */
    if (NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC == enMatchLvl)
    {
        *penOutMatchLvl = enMatchLvl;

        return;
    }

    /* ����ƥ��TAG_LOC */
    if (NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG ==
            (NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG & pstInMlplRec->ucLocParamType))
    {
        if (VOS_TRUE == NAS_MSCC_Is3gppSysWithLocTagMatched(pstIn3gppInfo, pstInMlplRec))
        {
             enMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC;
        }
    }

    *penOutMatchLvl = enMatchLvl;

    return;
}



VOS_VOID NAS_MSCC_Compare1xSysWithMlplRec(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstInMlplRec,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
)
{
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMatchLvl;
    VOS_UINT32                                              ulNasStyleMcc;

    /*
     * 1xϵͳMLPLƥ�����:

     * ������粻��MCC�����ô��뱣֤��ʹ��1X��Ϣ���Ҹ���ϵͳ��ƥ����Ϊ��ƥ��

     * ��������·�MCC��MNC��ƥ������3gppһ�£��ο�NAS_MSCC_Compare3gppSysWithMlplRec()
       ��������ƥ��LOCʱ��1x�Ƚ�SID NID range

     * �������ֻ�·�MCC��ֻ�Ƚ�MCC��SID NID��ƥ�伶���ﲻ����MNC��ƥ������TAG_MNC������ʱһ��

     * ����ʵ����������߼�

     */

    if (VOS_FALSE == pstInMlplRec->ucIsRecValid)
    {
        *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        return;
    }

    if ((VOS_FALSE == pstIn1xInfo->ucIsMccValid) || (NAS_MSCC_INVALID_MCC == pstIn1xInfo->ulMcc))
    {
        *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        return;
    }

    enMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    if (NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC ==
            (NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC & pstInMlplRec->ucLocParamType))
    {
        ulNasStyleMcc = NAS_MSCC_ConvertMlplMccToNasStyleMcc(pstInMlplRec->stLocParamVal.usMcc);

        if (pstIn1xInfo->ulMcc == ulNasStyleMcc)
        {
            enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_MCC;
        }
        else
        {
            *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

            return;
        }

        if (VOS_TRUE == pstIn1xInfo->ucIsMncValid)
        {
            if (NAS_MSCC_MLPL_LOC_PARAM_BIT_MNC ==
                    (NAS_MSCC_MLPL_LOC_PARAM_BIT_MNC & pstInMlplRec->ucLocParamType))
            {
                if (VOS_TRUE == NAS_MSCC_Is1xMncWithMlplMncMatched(pstIn1xInfo->ulMnc,
                                                              pstInMlplRec->stLocParamVal.usMnc))
                {
                    enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_MNC;
                }
                else
                {
                    *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

                    return;
                }
            }
        }
    }

    if (NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG ==
            (NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG & pstInMlplRec->ucLocParamType))
    {
      if (VOS_TRUE == NAS_MSCC_Is1xSysWithLocTagMatched(pstIn1xInfo, pstInMlplRec))
      {
        enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_LOC;
      }
    }

    *penOutMatchLvl = enMatchLvl;

    return;
}



VOS_VOID NAS_MSCC_CompareHrpdSysWithMlplRec(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstInMlplRec,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
)
{
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMatchLvl;
    VOS_UINT32                                              ulNasStyleMcc;

    /*
     * HRPDϵͳMLPLƥ�����:

     * ������粻��MCC�����ô��뱣֤��ʹ��HRPD��Ϣ���Ҹ���ϵͳ��ƥ����Ϊ��ƥ��

     * ��������·�MCC��MNC��ƥ������3gppһ�£��ο�NAS_MSCC_Compare3gppSysWithMlplRec()
       ��������ƥ��LOCʱ��1x�Ƚ�SID NID range

     * �������ֻ�·�MCC��ֻ�Ƚ�MCC��SID NID��ƥ�伶���ﲻ����MNC��ƥ������TAG_MNC������ʱһ��

     * ����ʵ����������߼�

     */

    if (VOS_FALSE == pstInMlplRec->ucIsRecValid)
    {
        *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        return;
    }

    if ((VOS_FALSE == pstInHrpdInfo->ucIsMccValid)
     || (NAS_MSCC_INVALID_MCC == pstInHrpdInfo->ulMcc))
    {
        *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

        return;
    }

    enMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

    if (NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC ==
            (NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC & pstInMlplRec->ucLocParamType))
    {
        ulNasStyleMcc = NAS_MSCC_ConvertMlplMccToNasStyleMcc(pstInMlplRec->stLocParamVal.usMcc);

        if (pstInHrpdInfo->ulMcc == ulNasStyleMcc)
        {
            enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_MCC;
        }
        else
        {
            *penOutMatchLvl = NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH;

            return;
        }
    }

    if (NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG ==
            (NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG & pstInMlplRec->ucLocParamType))
    {
      if (VOS_TRUE == NAS_MSCC_IsHrpdSysWithLocTagMatched(pstInHrpdInfo, pstInMlplRec))
      {
        enMatchLvl |= NAS_MSCC_MLPL_MATCH_LVL_LOC;
      }
    }

    *penOutMatchLvl = enMatchLvl;

    return;
}



VOS_UINT8 NAS_MSCC_Is3gppSysWithLocTagMatched(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pst3gppInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstMlplRec
)
{
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU                         *pstLocTag     = VOS_NULL_PTR;
    NAS_MSCC_MLPL_SYS_LOC_TAG_3GPP_STRU                    *pstLocTag3gpp = VOS_NULL_PTR;
    VOS_UINT8                                               ucLoop;

    /* ѭ��ƥ��ÿ��LOC_TAG�����ϵͳ������3GPP_AI��LTE���ж�PLMN�Ƿ���PLMN_RANGE��Χ */
    for (ucLoop = 0; ucLoop < pstMlplRec->stLocParamVal.ucNumSysLocTag; ucLoop++)
    {
        pstLocTag = &(pstMlplRec->stLocParamVal.astSysLocTag[ucLoop]);

        if (VOS_FALSE == pstLocTag->ucIsLocTagValid)
        {
            continue;
        }

        /* Ŀǰֻ֧��LTEϵͳ */
        if (VOS_TRUE == NAS_MSCC_IsMlplMsplSysTypeSupportLte(pstLocTag->enSysType))
        {
            pstLocTag3gpp = &(pstLocTag->unSysLocTag.stSysLocTag3GPP);

            /* �жϵ�ǰϵͳ��PLMN�Ƿ���LOC TAG��PLMN��Χ�� */
            if (VOS_TRUE == NAS_MSCC_IsSysPlmnInLocTagPlmnRange(&(pst3gppInfo->stPlmnId),
                                                                pstLocTag3gpp->aucPlmnStart,
                                                                pstLocTag3gpp->ucPlmnRange))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}
VOS_UINT8  NAS_MSCC_Is1xSysWithLocTagMatched(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pst1xInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstMlplRec
)
{
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU                         *pstLocTag         = VOS_NULL_PTR;
    NAS_MSCC_MLPL_SYS_LOC_TAG_CDMA2000_STRU                *pstLocTagCdma2000 = VOS_NULL_PTR;
    VOS_UINT8                                               ucLoop;

    /* ѭ��ƥ��ÿ��LOC_TAG�����ϵͳ������CDMA2000_AI��CDMA2000_1X���ж�SID NID�Ƿ���SID NID��Χ */
    for (ucLoop = 0; ucLoop < pstMlplRec->stLocParamVal.ucNumSysLocTag; ucLoop++)
    {
        pstLocTag = &(pstMlplRec->stLocParamVal.astSysLocTag[ucLoop]);

        if (VOS_FALSE == pstLocTag->ucIsLocTagValid)
        {
            continue;
        }

        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI == pstLocTag->enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_1X == pstLocTag->enSysType))
        {
            pstLocTagCdma2000 = &(pstLocTag->unSysLocTag.stSysLocTagCdma2000);

            /* ���SID��ͬ������NID Start��ͨ�������NID��range��Χ�ڣ�����TRUE */
            if (pst1xInfo->usSid == pstLocTagCdma2000->usSid)
            {
                if (NAS_MSCC_MLPL_WILDCARD_NID_START == pstLocTagCdma2000->usNidStart)
                {
                    return VOS_TRUE;
                }

                if ((pst1xInfo->usNid >= pstLocTagCdma2000->usNidStart)
                 && (pst1xInfo->usNid <= pstLocTagCdma2000->usNidStart + pstLocTagCdma2000->ucNidRange))
                {
                    return VOS_TRUE;
                }
            }
        }
    }

    return VOS_FALSE;
}



VOS_UINT8  NAS_MSCC_IsHrpdSysWithLocTagMatched(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstMlplRec
)
{
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU                         *pstLocTag     = VOS_NULL_PTR;
    NAS_MSCC_MLPL_SYS_LOC_TAG_CDMA2000_HRPD_STRU           *pstLocTagHrpd = VOS_NULL_PTR;
    VOS_UINT8                                               ucLoop;

    /* ѭ��ƥ��ÿ��LOC_TAG�����ϵͳ������CDMA2000_HRPD���ж�SubnetID�Ƿ���ͬ */
    for (ucLoop = 0; ucLoop < pstMlplRec->stLocParamVal.ucNumSysLocTag; ucLoop++)
    {
        pstLocTag = &(pstMlplRec->stLocParamVal.astSysLocTag[ucLoop]);

        if (VOS_FALSE == pstLocTag->ucIsLocTagValid)
        {
            continue;
        }

        if (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstLocTag->enSysType)
        {
            pstLocTagHrpd = &(pstLocTag->unSysLocTag.stSysLocTagCdma2000Hrpd);

            if (VOS_TRUE == NAS_MSCC_IsSysSubnetIdWithLocTagMatched(pstInHrpdInfo, pstLocTagHrpd))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}
VOS_UINT8 NAS_MSCC_Get3gppMatchedMsplRecIndex(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable,
    VOS_UINT8                                              *pucOutMsplRecId
)
{
    VOS_UINT8                                               ucLoop;

    /* Get matched mspl record in MSPL table*/
    for (ucLoop = 0; ucLoop < pstInMsplTable->ucNumMsplRec; ucLoop++)
    {
        if (VOS_TRUE == NAS_MSCC_Is3gppSysWithMsplRecMatched(pstIn3gppInfo,
                                                    &(pstInMsplTable->astMsplRec[ucLoop])))
        {
            *pucOutMsplRecId = ucLoop;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT8 NAS_MSCC_Get1xMatchedMsplRecIndex(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable,
    VOS_UINT8                                              *pucOutMsplRecId
)
{
    VOS_UINT8                                               ucLoop;

    /* Get matched mspl record in MSPL table*/
    for (ucLoop = 0; ucLoop < pstInMsplTable->ucNumMsplRec; ucLoop++)
    {
        if (VOS_TRUE == NAS_MSCC_Is1xSysWithMsplRecMatched(pstIn1xInfo,
                                                &(pstInMsplTable->astMsplRec[ucLoop])))
        {
            *pucOutMsplRecId = ucLoop;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT8 NAS_MSCC_GetHrpdMatchedMsplRecIndex(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable,
    VOS_UINT8                                              *pucOutMsplRecId
)
{
    VOS_UINT8                                              ucLoop;

    /* Get matched mspl record in MSPL table*/
    for (ucLoop = 0; ucLoop < pstInMsplTable->ucNumMsplRec; ucLoop++)
    {
        if (VOS_TRUE == NAS_MSCC_IsHrpdSysWithMsplRecMatched(pstInHrpdInfo,
                                                 &(pstInMsplTable->astMsplRec[ucLoop])))
        {
            *pucOutMsplRecId = ucLoop;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT8 NAS_MSCC_Is3gppSysWithMsplRecMatched(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pst3gppInfo,
    NAS_MSCC_MSPL_REC_STRU                                 *pstMsplRec
)
{
    if (VOS_FALSE == pstMsplRec->ucIsValid)
    {
        return VOS_FALSE;
    }

    /* Ŀǰ��֧��LTE��ʽ */
    if (VOS_RATMODE_LTE != pst3gppInfo->enSysRat)
    {
        return VOS_FALSE;
    }

    if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI != pstMsplRec->enSysType)
     && (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE     != pstMsplRec->enSysType))
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_MSPL_SYS_PRI_CLASS_ANY == pstMsplRec->enPriClass)
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME_AND_PREF == pstMsplRec->enPriClass)
      && ((NAS_MSCC_SYS_PRI_CLASS_HOME == pst3gppInfo->enPriClass)
       || (NAS_MSCC_SYS_PRI_CLASS_PREF == pst3gppInfo->enPriClass)))
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME == pstMsplRec->enPriClass)
     && (NAS_MSCC_SYS_PRI_CLASS_HOME      == pst3gppInfo->enPriClass))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT8 NAS_MSCC_Is1xSysWithMsplRecMatched(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MSPL_REC_STRU                                 *pstMsplRec
)
{
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8                       en1xPriClass;

    if (VOS_FALSE == pstMsplRec->ucIsValid)
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI == pstMsplRec->enSysType)
    {
        en1xPriClass = pstIn1xInfo->enPriClassCdma2000Ai;
    }
    else if (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_1X == pstMsplRec->enSysType)
    {
        en1xPriClass = pstIn1xInfo->enPriClassCdma20001x;
    }
    else
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_MSPL_SYS_PRI_CLASS_ANY == pstMsplRec->enPriClass)
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME_AND_PREF == pstMsplRec->enPriClass)
      && ((NAS_MSCC_SYS_PRI_CLASS_HOME == en1xPriClass)
       || (NAS_MSCC_SYS_PRI_CLASS_PREF == en1xPriClass)))
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME == pstMsplRec->enPriClass)
     && (NAS_MSCC_SYS_PRI_CLASS_HOME      == en1xPriClass))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_IsHrpdSysWithMsplRecMatched(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstHrpdInfo,
    NAS_MSCC_MSPL_REC_STRU                                 *pstMsplRec
)
{
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8                       enHrpdPriClass;

    if (VOS_FALSE == pstMsplRec->ucIsValid)
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI == pstMsplRec->enSysType)
    {
        enHrpdPriClass = pstHrpdInfo->enPriClassCdma2000Ai;
    }
    else if (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstMsplRec->enSysType)
    {
        enHrpdPriClass = pstHrpdInfo->enPriClassCdma2000Hrpd;
    }
    else
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_MSPL_SYS_PRI_CLASS_ANY == pstMsplRec->enPriClass)
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME_AND_PREF == pstMsplRec->enPriClass)
     && ((NAS_MSCC_SYS_PRI_CLASS_HOME == enHrpdPriClass)
      || (NAS_MSCC_SYS_PRI_CLASS_PREF == enHrpdPriClass)))
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME == pstMsplRec->enPriClass)
     && (NAS_MSCC_SYS_PRI_CLASS_HOME      == enHrpdPriClass) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID NAS_MSCC_GetHigherSysListThanSpecRecIndexSys(
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable,
    VOS_UINT8                                               ucInCurrMsplRecId,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MSPL_SYS_INFO_STRU                            *pstMsplSys = VOS_NULL_PTR;
    VOS_UINT8                                               ucFoundPriMore;
    VOS_INT16                                               sPriMoreRecPos;
    VOS_INT16                                               sLoop;

    ucFoundPriMore = VOS_FALSE;
    sPriMoreRecPos = NAS_MSCC_INVALID_MSPL_REC_ID;

    PS_MEM_SET(pstOutSysList, 0, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    if ((ucInCurrMsplRecId < 1) || (ucInCurrMsplRecId >= NAS_MSCC_MAX_NUM_MSPL_REC))
    {
        return;
    }

    /* Find the first MORE priority above the matched record */
    /* �ӵ�ǰ��¼����һ����¼��ʼ�ҵ���һ�����ȼ�ΪMORE���±� */
    for (sLoop = (VOS_INT16)(ucInCurrMsplRecId - 1); sLoop >= 0; sLoop--)
    {
        if (VOS_FALSE == pstInMsplTable->astMsplRec[sLoop].ucIsValid)
        {
            continue;
        }

        if (NAS_MSCC_MSPL_SYS_PRI_MORE == pstInMsplTable->astMsplRec[sLoop].enSysPri)
        {
            ucFoundPriMore = VOS_TRUE;
            sPriMoreRecPos = sLoop;
            break;
        }
    }

    /* ���û���ҵ����ȼ�ΪMORE�ļ�¼��˵��û�и���ϵͳ������ */
    if (VOS_FALSE == ucFoundPriMore)
    {
        return;
    }

    /* ���±�0��ʼ��MORE�±���������м�¼�ȵ�ǰ��¼�ߣ� ���������б� */
    for (sLoop = 0; sLoop <= sPriMoreRecPos; sLoop++)
    {
        if (VOS_FALSE == pstInMsplTable->astMsplRec[sLoop].ucIsValid)
        {
            continue;
        }

        pstMsplSys              = &(pstOutSysList->astSysList[pstOutSysList->ucSysCount]);
        pstMsplSys->enSysType   = pstInMsplTable->astMsplRec[sLoop].enSysType;
        pstMsplSys->enPriClass  = pstInMsplTable->astMsplRec[sLoop].enPriClass;

        pstOutSysList->ucSysCount++;
    }
}



VOS_UINT8 NAS_MSCC_IsSysPlmnInLocTagPlmnRange(
    NAS_MSCC_PIF_PLMN_ID_STRU                              *pstSysPlmn,
    VOS_UINT8                                              *aucPlmnStart,
    VOS_UINT8                                               ucPlmnRange
)
{
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU                    *pstPrefPlmnList = VOS_NULL_PTR;
    NAS_MSCC_SIM_FORMAT_PLMN_ID_STRU                        stPlmnStartSimFmt;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnStart;
    VOS_UINT16                                              usPrefPlmnCnt;
    VOS_UINT16                                              usPrefPlmnIndex;
    VOS_UINT16                                              usPlmnRangeIndex;
    VOS_UINT16                                              usPlmnRangeIndexStart;
    VOS_UINT16                                              usPlmnRangeIndexEnd;

    PS_MEM_SET(&stPlmnStartSimFmt, 0, sizeof(NAS_MSCC_SIM_FORMAT_PLMN_ID_STRU));
    PS_MEM_CPY(stPlmnStartSimFmt.aucSimPlmn, aucPlmnStart, NAS_MSCC_SIM_FORMAT_PLMN_LEN);

    NAS_MSCC_ConvertSimPlmnToNasPlmn(&stPlmnStartSimFmt, &stPlmnStart);

    /* ���PLMN_START�е�MCC��ͨ�������PLMN_START��Ч��ֱ�ӷ���VOS_FALSE */
    if (NAS_MSCC_MLPL_WILDCARD_MCC == stPlmnStart.ulMcc)
    {
        return VOS_FALSE;
    }

    /* ���ж�PLMN_START�Ƿ�ƥ�䣬���ƥ�䣬ֱ�ӷ���ƥ��ɹ� */
    if (VOS_TRUE == NAS_MSCC_ComparePlmn(pstSysPlmn, &stPlmnStart))
    {
        return VOS_TRUE;
    }

    pstPrefPlmnList = (NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC,
                         NAS_MSCC_MAX_PREF_PLMN_NUM * sizeof(NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU));

    if (VOS_NULL_PTR == pstPrefPlmnList)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(pstPrefPlmnList, 0,
                    NAS_MSCC_MAX_PREF_PLMN_NUM * sizeof(NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU));

    usPrefPlmnCnt = 0;

    NAS_MSCC_GeneratePrefPlmnList(pstPrefPlmnList, &usPrefPlmnCnt);

    if (0 == usPrefPlmnCnt)
    {
        PS_MEM_FREE(UEPS_PID_MSCC, pstPrefPlmnList);

        return VOS_FALSE;
    }

    /* ���ҵ�PLMN_START��Ӧ���б��±꣬��ǰϵͳ��PLMNƥ��ļ�¼ */
    for (usPrefPlmnIndex = 0; usPrefPlmnIndex < usPrefPlmnCnt; usPrefPlmnIndex++)
    {
        if (VOS_TRUE == NAS_MSCC_ComparePlmn(&(pstPrefPlmnList[usPrefPlmnIndex].stPlmnId),
                                             &stPlmnStart))
        {
            break;
        }
    }

    /* ���û���ҵ�PLMN_START��Ӧ���б��±꣬פ����PLMN����PLMN Range��Χ������VOS_FALSE */
    if (usPrefPlmnIndex >= usPrefPlmnCnt)
    {
        PS_MEM_FREE(UEPS_PID_MSCC, pstPrefPlmnList);

        return VOS_FALSE;
    }

    usPlmnRangeIndexStart = usPrefPlmnIndex;
    usPlmnRangeIndexEnd   = usPrefPlmnIndex + ucPlmnRange;

    if (usPlmnRangeIndexEnd >= usPrefPlmnCnt)
    {
        usPlmnRangeIndexEnd = usPrefPlmnCnt -1;
    }

    /* �жϵ�ǰϵͳ��PLMN�Ƿ���PLMN_START��PLMN_RANGE��Χ�� */
    for (usPlmnRangeIndex  = usPlmnRangeIndexStart;
         usPlmnRangeIndex <= usPlmnRangeIndexEnd;
         usPlmnRangeIndex++)
    {
        if (VOS_TRUE == NAS_MSCC_ComparePlmn(&(pstPrefPlmnList[usPlmnRangeIndex].stPlmnId),
                                              pstSysPlmn))
        {
            PS_MEM_FREE(UEPS_PID_MSCC, pstPrefPlmnList);

            return VOS_TRUE;
        }
    }

    PS_MEM_FREE(UEPS_PID_MSCC, pstPrefPlmnList);

    return VOS_FALSE;
}
VOS_UINT8 NAS_MSCC_IsSysSubnetIdWithLocTagMatched(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstHrpdInfo,
    NAS_MSCC_MLPL_SYS_LOC_TAG_CDMA2000_HRPD_STRU           *pstLocTagHrpd
)
{
    VOS_UINT8                                               ucByteCnt;
    VOS_UINT8                                               ucRemainBitCnt;
    VOS_UINT8                                               ucSysSubnetIdRemainValue;

    /* TAG_LOC��SubnetID����Ϊ0������FALSE */
    if (0 == pstLocTagHrpd->ucSubnetLen)
    {
        return VOS_FALSE;
    }

    /* ϵͳSubnetID����С��Tag SubnetID���ȣ�����FALSE */
    if (pstHrpdInfo->ucSubNetMask < pstLocTagHrpd->ucSubnetLen)
    {
        return VOS_FALSE;
    }

    /* �ȱȽ����ֽڣ���TAG_LOC�еĳ��ȱȽ� */
    ucByteCnt = pstLocTagHrpd->ucSubnetLen / NAS_MSCC_BIT_LEN_ONE_BYTE;

    if (0 != VOS_MemCmp(pstHrpdInfo->aucSectorId, pstLocTagHrpd->aucSubnetId, ucByteCnt))
    {
        return VOS_FALSE;
    }

    ucRemainBitCnt = pstLocTagHrpd->ucSubnetLen % NAS_MSCC_BIT_LEN_ONE_BYTE;

    if (0 == ucRemainBitCnt)
    {
        return VOS_TRUE;
    }

    /* �ٱȽ�ʣ��bit */
    ucSysSubnetIdRemainValue = pstHrpdInfo->aucSectorId[ucByteCnt]
                               >> (NAS_MSCC_BIT_LEN_ONE_BYTE - ucRemainBitCnt);

    if (ucSysSubnetIdRemainValue == pstLocTagHrpd->aucSubnetId[ucByteCnt])
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_Is1xMncWithMlplMncMatched(
    VOS_UINT32                                              ul1xMnc,
    VOS_UINT16                                              usMlplMnc
)
{
    VOS_UINT32                                              ulNasStyleMnc;

    if (NAS_MSCC_MLPL_WILDCARD_MNC == usMlplMnc)
    {
        return VOS_TRUE;
    }

    ulNasStyleMnc = NAS_MSCC_ConvertMlplMncToNasStyleMnc(usMlplMnc);

    if (ul1xMnc == ulNasStyleMnc)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MSCC_IsMlplMsplSysTypeSupportLte(
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType
)
{
    switch (enSysType)
    {
        case NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI:
        case NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}



VOS_VOID NAS_MSCC_GeneratePrefPlmnList(
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU                    *pstOutPlmnList,
    VOS_UINT16                                             *pusOutPlmnCnt
)
{
    NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU                      *pstSimEhPlmnInfo     = VOS_NULL_PTR;
    NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU                    *pstUserPlmnInfo      = VOS_NULL_PTR;
    NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU                    *pstOperPlmnInfo      = VOS_NULL_PTR;
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU                    *pstPlmnListStartPos  = VOS_NULL_PTR;

    pstSimEhPlmnInfo = NAS_MSCC_GetEhPlmnInfoAddr();
    pstUserPlmnInfo  = NAS_MSCC_GetUserPlmnInfoAddr();
    pstOperPlmnInfo  = NAS_MSCC_GetOperPlmnInfoAddr();

    *pusOutPlmnCnt = pstSimEhPlmnInfo->ucEhPlmnNum + pstUserPlmnInfo->ucUserPlmnNum
                     + pstOperPlmnInfo->usOperPlmnNum;

    if (pstSimEhPlmnInfo->ucEhPlmnNum > 0)
    {
        PS_MEM_CPY(pstOutPlmnList, pstSimEhPlmnInfo->astEhPlmnInfo,
                   pstSimEhPlmnInfo->ucEhPlmnNum * sizeof(NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU));
    }

    if (pstUserPlmnInfo->ucUserPlmnNum > 0)
    {
        pstPlmnListStartPos = pstOutPlmnList + pstSimEhPlmnInfo->ucEhPlmnNum;

        PS_MEM_CPY(pstPlmnListStartPos, pstUserPlmnInfo->astUserPlmnInfo,
                   pstUserPlmnInfo->ucUserPlmnNum* sizeof(NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU));
    }

    if (pstOperPlmnInfo->usOperPlmnNum > 0)
    {
        pstPlmnListStartPos = pstOutPlmnList + pstSimEhPlmnInfo->ucEhPlmnNum
                              + pstUserPlmnInfo->ucUserPlmnNum;

        PS_MEM_CPY(pstPlmnListStartPos, pstOperPlmnInfo->astOperPlmnInfo,
                   pstOperPlmnInfo->usOperPlmnNum * sizeof(NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU));
    }

}



VOS_UINT32 NAS_MSCC_ConvertMlplMccToNasStyleMcc(
    VOS_UINT16                          usMlplMcc
)
{
    VOS_UINT32                          ulNasMcc;

    /* ���MLPL mcc�����4λ����0������FALSE */
    if (0 != (usMlplMcc & 0xF000))
    {
        return NAS_MSCC_INVALID_MCC;
    }

    ulNasMcc = ((VOS_UINT32)(usMlplMcc & 0x0F00)) >> 8;

    ulNasMcc += ((VOS_UINT32)(usMlplMcc & 0x00F0)) << 4;

    ulNasMcc += ((VOS_UINT32)(usMlplMcc & 0x000F)) << 16;

    return ulNasMcc;
}
VOS_UINT32 NAS_MSCC_ConvertMlplMncToNasStyleMnc(
    VOS_UINT16                          usMlplMnc
)
{
    VOS_UINT32                          ulNasMnc;

    /* ���MLPL mnc�����4λ����0������FALSE */
    if (0 != (usMlplMnc & 0xF000))
    {
        return NAS_MSCC_INVALID_MNC;
    }

    ulNasMnc = ((VOS_UINT32)(usMlplMnc & 0x0F00)) >> 8;

    ulNasMnc += ((VOS_UINT32)(usMlplMnc & 0x00F0)) << 4;

    ulNasMnc += ((VOS_UINT32)(usMlplMnc & 0x000F)) << 16;

    return ulNasMnc;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMlplInfo
Description     :   Parse and validate MLPL info.
Input parameters:   pucMlplBuff - MLPL buffer
                    ulBuffSize  - buff size in bytes
Outout parameters:  None
Return Value     :  NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32 NAS_MSCC_ParseMlplFile(
    VOS_UINT8                          *pucMlplBuff,
    VOS_UINT16                          usBuffSize
)
{
    NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32                     enParseRslt;

    if ((VOS_NULL_PTR == pucMlplBuff)
     || (NAS_MSCC_CONVERT_BYTES_TO_BITS(usBuffSize) < NAS_MSCC_MLPL_MIN_BIT_LEN))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ParseMlplInfo:Invalid buffer Len passed.");
        return NAS_MSCC_PARSE_MLPL_RSLT_FAIL;
    }

    enParseRslt = NAS_MSCC_ParseMlplBitStream(pucMlplBuff, usBuffSize);
    if (enParseRslt != NAS_MSCC_PARSE_MLPL_RSLT_SUCCESS)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMlplInfo:MLPL parse failed, reason:",
                       enParseRslt);
        return enParseRslt;
    }

    NAS_MSCC_MNTN_LogMlplInfo(NAS_MSCC_GetMlplInfoAddr());

    return NAS_MSCC_PARSE_MLPL_RSLT_SUCCESS;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMsplInfo
Description     :   Parse and validate MSPL info.
Input parameters:   pucMsplBuff - MSPL buffer
                    ulBuffSize  - buff size in bytes
Outout parameters:  None
Return Value     :  NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32 NAS_MSCC_ParseMsplFile(
    VOS_UINT8                          *pucMsplBuff,
    VOS_UINT16                          usBuffSize
)
{
    NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32                     enParseRslt;

    if ((VOS_NULL_PTR == pucMsplBuff)
     || (NAS_MSCC_CONVERT_BYTES_TO_BITS(usBuffSize) < NAS_MSCC_MSPL_MIN_BIT_LEN))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ParseMsplInfo:Invalid buffer Len passed.");
        return NAS_MSCC_PARSE_MSPL_RSLT_FAIL;
    }

    enParseRslt = NAS_MSCC_ParseMsplBitStream(pucMsplBuff, usBuffSize);
    if (enParseRslt != NAS_MSCC_PARSE_MSPL_RSLT_SUCCESS)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMsplInfo:MSPL parse failed, reason:",
                       enParseRslt);
        return enParseRslt;
    }

    NAS_MSCC_MNTN_LogMsplInfo(NAS_MSCC_GetMsplInfoAddr());

    return NAS_MSCC_PARSE_MSPL_RSLT_SUCCESS;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

