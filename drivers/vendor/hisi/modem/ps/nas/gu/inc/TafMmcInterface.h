

#ifndef _TAF_MMC_INTERFACE_H_
#define _TAF_MMC_INTERFACE_H_

#include "PsTypeDef.h"
#include "NasCommDef.h"
#include "TafAppMma.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#pragma pack(4)

#define TAFMMC_CBS_NO_NETWORK_IND       (1)
#define TAFMMC_CBS_CURR_NET_MODE_IND    (2)

#define TAFMMC_APS_SERVICE_STATE_IND    (3)

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
}TAFMMC_CBS_NO_NETWORK_IND_STRU;


/* MMC���͸�MSGģ��ĵ�ǰ����ģʽ��Ϣ */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT8                           ucCurNetWork;                           /* ��ǰ����ģʽ */
    VOS_UINT8                           aucReserve[3];
}TAFMMC_CBS_CURR_NET_MODE_IND_STRU;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
