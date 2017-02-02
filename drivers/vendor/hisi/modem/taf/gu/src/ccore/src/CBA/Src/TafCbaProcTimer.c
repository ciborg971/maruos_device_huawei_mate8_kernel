

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaProcTimer.h"
#include  "TafCbaProcUsim.h"
#include  "TafCbaProcAs.h"
#include  "TafCbaComFunc.h"
#include  "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_TIMER_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/



VOS_VOID  TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired(
    VOS_UINT32                          ulParam
)
{
    TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired: Entered.");

    /* �����ȡ�ļ������б�� */
    /* TAF_CBA_ClearAllReadUsimFilesFlg */

}

#if ((FEATURE_ON == FEATURE_ETWS))

VOS_VOID TAF_CBA_RcvTiEtwsTempEnableCbsTimerExpired(
    VOS_UINT32                          ulParam
)
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetMode;
    VOS_UINT32                          ulIsActiveListEmpty;

    TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvTiEtwsTempEnableCbsTimerExpired: Entered.");

    enNetMode = TAF_CBA_GetNetRatType();

    /* Wģʱ����Ҫȥʹ��CBS���� */
    /* todo:���G֧��ETWS��������Ҫ�޸� */
    if (TAF_CBA_NET_RAT_TYPE_WCDMA  != enNetMode)
    {
        return;
    }

    /* ��ʱ�������������û��������ü����б�Ϊ���ˣ���ʱ�Ͳ���Ҫ��AS��DISABLE�� */
    ulIsActiveListEmpty = TAF_CBA_IsCbsActiveListEmpty();
    if ( VOS_TRUE != ulIsActiveListEmpty )
    {
        /* ��AS��CBS DISABLE��Ϣ */
        TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_DEACTIVE);
    }
}

/*lint -restore */

#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
