


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "TafMmaSndUphy.h"
#include "MmaUphyInterface.h"

#include "PsTypeDef.h"
#include "TafLog.h"



#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_SND_UPHY_C

/*****************************************************************************
   2 ȫ�ֱ�������ͺ�
****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

VOS_VOID TAF_MMA_SndUphyPowerOnReq(VOS_VOID)
{
    VOS_UINT16                          ulLenth;
    MMA_UPHY_POWER_ON_REQ_STRU         *pstPowerOn = VOS_NULL_PTR;

    ulLenth     = sizeof(MMA_UPHY_POWER_ON_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstPowerOn  = (MMA_UPHY_POWER_ON_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);
    if (VOS_NULL_PTR == pstPowerOn)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndUphyPowerOnReq: Alloc Msg Failed!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstPowerOn + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstPowerOn->ulReceiverPid           = DSP_PID_STARTUP;
    pstPowerOn->usMsgID                 = ID_MMA_UPHY_POWER_ON_REQ;
    pstPowerOn->enModemId               = VOS_GetModemIDFromPid(WUEPS_PID_MMA);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstPowerOn))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndUphyPowerOnReq: Snd Msg Failed!");
    }

    return;

}


VOS_VOID TAF_MMA_SndUphyPowerOffReq(VOS_VOID)
{
    VOS_UINT16                          ulLenth;
    MMA_UPHY_POWER_OFF_REQ_STRU        *pstPowerOff = VOS_NULL_PTR;

    ulLenth     = sizeof(MMA_UPHY_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstPowerOff  = (MMA_UPHY_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);
    if (VOS_NULL_PTR == pstPowerOff)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndUphyPowerOffReq: Alloc Msg Failed!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstPowerOff + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstPowerOff->ulReceiverPid           = DSP_PID_STARTUP;
    pstPowerOff->usMsgID                 = ID_MMA_UPHY_POWER_OFF_REQ;
    pstPowerOff->enModemId               = VOS_GetModemIDFromPid(WUEPS_PID_MMA);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstPowerOff))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndUphyPowerOffReq: Snd Msg Failed!");
    }

    return;

}





#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif







