

/*****************************************************************************
 PROJECT   :
 SUBSYSTEM :
 MODULE    :
 OWNER     :
*****************************************************************************/


#ifndef __FTM_H__
#define __FTM_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "osm.h"
#include <msp_ftm.h>

#define FTM_NONESIG_RTT_OPEN        (1)
#define FTM_NONESIG_RTT_CLOSE       (0)

#define MSP_IMEI_LEN       (15)

#undef UINT32
#define  UINT32 unsigned long
#undef INT32
#define  INT32 long
#undef INT16
#define   INT16 short
#undef UINT16
#define UINT16 unsigned short
#undef UINT8
#define UINT8 unsigned char
#undef INT8
#define INT8 unsigned char

/* ���ϲ���SYMע��*/
typedef VOS_VOID (*FTM_RESET_CALLBACK_PFN)( VOS_VOID);



extern VOS_UINT32 ftm_TaskMsg(OS_MSG_STRU * pMsg);
/*****************************************************************************
 ��������: ftm_SymResetCallBackReg
 ��������: ��SYMģ�����ע��ص��ӿڣ�����SYM��س�ʼ��

 ����˵��:
   pfun [in]��SYM����ĺ����ӿ�

 �� �� ֵ:

 ����Ҫ��: SYM�ڳ�ʼ��ʱ����
 ���þ���: TODO: ...
*****************************************************************************/
extern VOS_VOID ftm_SymResetCallBackReg(FTM_RESET_CALLBACK_PFN pfun);
extern VOS_UINT8 ftm_GetNoneSigNV(VOS_VOID);

extern VOS_UINT32 ftm_OnlineUpgradeSetFun(VOS_VOID);

extern VOS_UINT32 FTM_MsgConvert(MsgBlock* pMsg, OS_MSG_STRU* pstFtmMsg);
extern VOS_UINT32 ftm_SendDataMsg(VOS_UINT32 ulSenderId, VOS_UINT32 ulRecverId, VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);

extern VOS_BOOL pom_GetDspInitFlg(VOS_VOID);

#ifdef __cplusplus
}
#endif

#endif /*__FTM_H__*/


