
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "CssInterface.h"
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"
#include "NasMmcSndCss.h"
#include "PsCommonDef.h"
#include "NasComm.h"
#include "NasMmcComFunc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_CSS_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_VOID  NAS_MMC_SndCssMultiBandScanReq(
    NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU        *pstMultiBandScanReq
)
{
    CSS_MULTI_BAND_SCAN_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    pstMsg = (CSS_MULTI_BAND_SCAN_REQ_STRU *)NAS_MMC_ALLOC_MSG_WITH_HDR(sizeof(CSS_MULTI_BAND_SCAN_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndCssMultiBandScanReq: memery alloc failed.");
        return;
    }

    /* �����Ϣ���� */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* ��д��Ϣͷ */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        PS_PID_CSS,
                        ID_CSS_MULTI_BAND_SCAN_REQ,
                        sizeof(CSS_MULTI_BAND_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ���� */
    pstMsg->ulOpid                      = 0;
    pstMsg->enBandScanType              = pstMultiBandScanReq->enBandScanType;

    if (VOS_TRUE == pstMultiBandScanReq->bitOpMcc)
    {
        pstMsg->bitOpMcc                = VOS_TRUE;
        pstMsg->aucMcc[0]               = pstMultiBandScanReq->aucMcc[0];
        pstMsg->aucMcc[1]               = pstMultiBandScanReq->aucMcc[1];
    }

    pstMsg->bitOpHighRssi               = pstMultiBandScanReq->bitOpHighRssi;

    PS_MEM_CPY(&pstMsg->stRatList, &pstMultiBandScanReq->stRatList, sizeof(CSS_RAT_LIST));

    NAS_MMC_SEND_MSG(pstMsg);

    return;
}
VOS_VOID  NAS_MMC_SndCssStopBandScanReq(VOS_VOID)
{
    CSS_STOP_BAND_SCAN_REQ_STRU       *pstMsg = VOS_NULL_PTR;

    pstMsg = (CSS_STOP_BAND_SCAN_REQ_STRU *)NAS_MMC_ALLOC_MSG_WITH_HDR(sizeof(CSS_STOP_BAND_SCAN_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndCssStopBandScanReq: memery alloc failed.");
        return;
    }

    /* �����Ϣ���� */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* ��д��Ϣͷ */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        PS_PID_CSS,
                        ID_CSS_STOP_BAND_SCAN_REQ,
                        sizeof(CSS_STOP_BAND_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣ���� */

    NAS_MMC_SEND_MSG(pstMsg);

    return;
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

