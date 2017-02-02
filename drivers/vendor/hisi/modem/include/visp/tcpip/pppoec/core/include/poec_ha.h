/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poec_ha.h
*
*  Project Code: VISP V100R006
*   Module Name: POEC  
*  Date Created: 2006-12-13
*        Author: sunmo(44939)
*   Description: POECģ���HAͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2006-12-13  sunmo(44939)     Create the first version.
*
*******************************************************************************/

#ifndef _POEC_HA_H_
#define _POEC_HA_H_

#ifdef __cplusplus
extern "C"{
#endif

#define POEC_HA_OPER_SETBUNDLE 1
#define POEC_HA_OPER_DELBUNDLE 0

/* Added by Sunmo(44939) for A82D12574 */
#define POEC_HA_OPER_NEGUP   0
#define POEC_HA_OPER_NEGDOWN 1

/* PPPoEģ�鱸����Ϣ���� */
enum enumPoecMsgType
{
    POEC_BAK_BUNDLE,
    POEC_BAK_SESSION,
    POEC_BAK_SET_BUNDLE,
    POEC_BAK_CREATE_SESSION,
    POEC_BAK_MOVE_SESSION,
    POEC_BAK_NO_SESSION,
    POEC_BAK_CHANGE_SESSION_STATE
};

/*ÿ�������ݵ�Session���ƿ����*/
#define POEC_BAK_MAXSESSION_ITEM     50
/* PPPoEģ��HA������Ϣͷ���� */
#define POEC_BAK_HEAD_LEN            sizeof(POEC_BAK_S) + sizeof (HAMSGHEADER_S)
/* ����g_ulDialerBundleNumber�������Ϣ�ܳ��� */
#define POEC_BAK_BUNDLE_MSG_LEN      1280

/* PPPoEģ��HA���Կ��� */
extern ULONG g_ulPoecHaDebug;
/* PPPoEģ��HA��ϸ���ݵ��Կ��� */
extern ULONG g_ulPoecHaVerboseDebug;

/* PPPoEģ��HA��Ϣͷ */
typedef struct tagPOEC_BAK
{
    USHORT   usMsgType;      /* ��Ϣ���� */
    USHORT   usBakItems;     /* ��������� */
}POEC_BAK_S;

/* PPPoEģ��Session���ƿ�ı�����Ϣ�ṹ */
typedef struct tagPOEC_BAK_SESSION
{
    UCHAR szOurMacAddr[PPPOE_MAC_LEN];   /* Client physical��ַ */
    UCHAR szHisMacAddr[PPPOE_MAC_LEN];   /* Server physical��ַ */
    ULONG ulEthIfIndex;                  /* ��Ӧ��̫���ӿ����� */
    ULONG ulVAIfIndex;                   /* ��Ӧvirtual access�ӿ����� */
    ULONG ulDialerIfIndex;               /* ��Ӧ��dialer�ӿ����� */
    USHORT usBundleNumber;               /* ��Ӧ��dialer��bundle number */
    USHORT usSessionId;                  /* ��Session��ID */
    UCHAR ucSessionState;                /* PPPoE Client Session�����Ľ׶� */
    UCHAR ucPadding[3];                  /* �����ֶ� */
}POEC_BAK_SESSION_S;

/* PPPoEģ������/ɾ��Bundle Numberʵʱ������Ϣ�ṹ */
typedef struct tagPOEC_BAK_REAL_BUNDLE
{
    ULONG ulBundleNumber;
    ULONG ulDialerIfIndex;
}POEC_BAK_REAL_BUNDLE_S;

/* PPPoEģ��Session��Discovery�׶�״̬��Ǩʵʱ������Ϣ�ṹ */
typedef struct tagPOEC_BAK_REAL_CHANGESTATE
{
    ULONG ulBundleNumber;
}POEC_BAK_REAL_CHANGESTATE_S;

/* PPPoEģ��ɾ��Sessionʵʱ������Ϣ�ṹ */
typedef struct tagPOEC_BAK_REAL_NO_SESSION
{
    ULONG ulBundleNumber;
    ULONG ulEthIfIndex;
}POEC_BAK_REAL_NO_SESSION_S;


/* HA�������� */
ULONG POEC_HA_BatchBundle(VOID);
ULONG POEC_HA_BatchSession(VOID);
ULONG POEC_HA_BatchBackup(VOID);
ULONG POEC_HA_Input (UCHAR * pBuf, ULONG ulMsgLen);
ULONG POEC_HA_BundleInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG POEC_HA_SessionInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG POEC_HA_SetBundleInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG POEC_HA_CreateSessionInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG POEC_HA_MoveSessionInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG POEC_HA_NoSessionInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG POEC_HA_Smooth(VOID);
ULONG TCPIP_HA_SetPoecDbg (ULONG ulDbg);
ULONG POEC_HA_SessionStateInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG TCPIP_HA_GetPoecDbg(ULONG *pulRet);
VOID POEC_HA_DebugOutput(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);
ULONG POEC_HA_SetPoecVerboseDbg (ULONG ulDbg);
ULONG POEC_HA_GetPoecVerboseDbg(ULONG *pulRet);
ULONG POEC_HA_Clean(VOID);
/* End of HA�������� */

extern VOID VOS_T_Delay(ULONG ulMillisecond);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _POEC_HA_H_ */

