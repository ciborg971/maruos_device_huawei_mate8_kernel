/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ha.H
*
*  Project Code: VISPV100R006
*   Module Name: HA
*  Date Created: 2006-12-04
*        Author: xiehuaguo
*   Description: VISP HA ������ȴ���ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-12-04  xiehuaguo        Create
*
*******************************************************************************/

#ifndef _TCPIP_HA_H_
#define _TCPIP_HA_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/public/dopra_cbb/include/utldll.h"
#include "tcpip/public/tcpip_pub_api.h"
#include "tcpip/public/tcpip_pub.h"

/* �鿴��ǰ�Ƿ����ڽ����ֶ�������ƽ������ */
#define HA_IS_SMOOTH_OR_MANUAL   ((1 == g_ulHAManualOrSmooth))

/* HA д�����¼��궨�� */
#define HA_SchedHATask(ulEvent) \
{ \
    (VOID)VOS_Ev_Write( g_ulHATaskID, ulEvent ); \
}

/* HA д��Ϣ���к궨��*/
#define HA_WriteHAQueue(ulQueueId,ulMsg,ulRet) \
{ \
    ulRet = VOS_Que_Write (ulQueueId, ulMsg, VOS_NO_WAIT | VOS_NORMAL, 0);\
}

/* HA �¼�λ���� */
#define HA_EVENT_MANUALSW     0X00000001      /* �ֶ������¼� */
#define HA_EVENT_SMOOTH       0X00000002      /* ƽ�������¼� */
#define HA_EVENT_BAKRCV       0X00000004      /* ������Ϣ�����¼�(���������) */
#define HA_EVENT_BAKSND       0X00000008      /* ������Ϣ�����¼� (�������) */
#define HA_EVENT_SKTSND       0X00000010      /* ����㱸����Ϣ�����¼�  */
#define HA_EVENT_TIMER        VRP_EVENT_TIMERREQ /* HA���ʱ���¼� */

/* VISP ��ģ���������Ƿ���ɱ�Ƕ��� */
#define HA_ALL_BATCH_INIT     0X10000000      /* �����ݳ�ʼ���    */
#define HA_IFNET_BATCH_OVER   0X00000001      /* IFNET����������� */
#define HA_IP_BATCH_OVER      0X00000002      /* IP�����������    */
#define HA_ETH_BATCH_OVER     0X00000004      /* ETH�����������   */
#define HA_TRUNK_BATCH_OVER   0X00000008      /* TRUNK����������� */
#define HA_PPP_BATCH_OVER     0X00000010      /* PPP�����������   */
#define HA_PPPOE_BATCH_OVER   0X00000020      /* PPPOE����������� */
#define HA_DHCP4C_BATCH_OVER  0X00000040      /* DHCP4C�����������*/
#define HA_SFIB_BATCH_OVER    0X00000080      /* SFIB�����������  */
#define HA_SOCKET_BATCH_OVER  0X00000100      /* SOCKET�����������*/
#define HA_BFD_BATCH_OVER     0X00000200      /* BFD�����������   */
#define HA_DHCP4R_BATCH_OVER  0X00000400      /* DHCP4R�����������*/
#define HA_POES_BATCH_OVER    0X00000800      /* POES�����������  */
#define HA_PUBLIC_BATCH_OVER  0X00001000      /* PUBLIC ����������������� */
#define HA_OAM3AH_BATCH_OVER  0X00002000      /* OAM3AHģ����������� */
#define HA_OAM1AG_BATCH_OVER  0X00004000      /* 1AG�������������    */
#define HA_IGMP_BATCH_OVER    0x00008000      /* igmp�����������  */
#define HA_VRF_BATCH_OVER     0x00010000      /* VRF�����������  */
#define HA_TWAMP_BATCH_OVER     0x00020000      /* TWAMP has completed the Batch backUP */
#define HA_ALL_BATCH_OVER     0X20000000      /* ���������������  */

/* IPV4�����е�����������Ϣ������� */
#define HA_IPV4_BATCH_MSG_OVER   0X00000001

/* SOCKET�����е�����������Ϣ�������*/
#define HA_SOCKET_BATCH_MSG_OVER 0X00000002

/* IPV4���С�SOCKET�����е�����������Ϣ������� */
#define HA_BATCH_MSG_OVER  ( HA_IPV4_BATCH_MSG_OVER|HA_SOCKET_BATCH_MSG_OVER )

#define HA_BAK_MAXMSG_LEN           2048        /* HA������Ϣ��󳤶� */
#define HA_BAK_SCHQUE_NUM           0x00000100L /* HA���������ݵ��ȱ��ĸ��� */
#define HA_BAK_SCHQUE_MULTIPKT_NUM  8           /* HA���������ݣ����ȸ��ϰ��ĸ��� */
#define HA_BAK_DELAY_TIME           1           /* HA��������ʱ����ʱ�� */

#define HA_DEBUG_SEND   0   /* HA���ķ��� */
#define HA_DEBUG_RECV   1   /* HA���Ľ��� */

#define HA_SEQUENCE_DISORDER(a, b) \
   ((((a<b) && ((b-a) < (ULONG)0x80000000)) || ((a>b) && ((a-b) > (ULONG)0x80000000))) ? 1:0)

/*  HAģ��Ŷ��壬���ڱ�ʶHA������Ϣ����ģ�� */
typedef enum enumHAMID
{
    HA_MID_MIN,
    HA_MID_IFNET = 1,   /* 1 */
    HA_MID_IP,          /* 2 */
    HA_MID_ETHARP,      /* 3 */
    HA_MID_TRUNK,       /* 4 */
    HA_MID_PPP,         /* 5 */
    HA_MID_POES,        /* 6 */
    HA_MID_PPPOE,       /* 7 */
    HA_MID_DHCP4C,      /* 8 */
    HA_MID_DHCP4R,      /* 9 */
    HA_MID_SFIB,        /* 10*/
    HA_MID_SOCKET,      /* 11*/
    HA_MID_BFD,         /* 12*/
    HA_MID_PUBLIC,      /* 13*/
    HA_MID_TCP,         /* 14*/
    HA_MID_EOAM3AH,     /* 15*/
    HA_MID_OAM1AG,      /* 16*/
    HA_MID_IGMP,        /* 17*/
    HA_MID_VRF,         /* 18*/
    HA_MID_HADETECT = 0x7e,    /* ̽�ⱨ��ʹ�õ�ģ��ID */
    HA_MID_TWAMP = 0x7f,    /* ̽�ⱨ��ʹ�õ�ģ��ID */
    HA_MID_MAX, /* VISP�ڲ�ģ������ޣ�������ֵ��Ϊ�ⲿע���ģ��� */

    HA_MID_SLAVE_BOARD_ID = 255,    /* ������䷢����Ϣ��ģ��� */
}HAMID_E;

/* �������֪ͨVISP��HA�¼����� */
typedef enum tagTCPIP_HA_EVENT
{
    HA_EVENT_NOTIFY_SWITCH,         /* 0 ֪ͨ��������������� */
    HA_EVENT_NOTIFY_SMOOTH,         /* 1 ֪ͨ�������ƽ������ */
    HA_EVENT_NOTIFY_S_CLR,          /* 2 �����巢�ͱ��ݰ�֪ͨ������������ϵ�����VISP���� */
    HA_EVENT_NOTIFY_MAX,            /* ��Ϣ���͵����ֵ�������� */
}TCPIP_HA_EVENT_E;

/* HA ��Ϣ�ײ����� */
typedef struct tagHAMsgHeader
{
    /* HA������Ϣ���, ����ж����Ϣ�ϳ�һ����Ϣ������ֻ������������Ϣ�Ŵ��ڱ�� */
    ULONG         ulSeq ;

    /* HA�汾��, �ⲿģ���HA�汾�ź�VISPģ��İ汾�Ų���ͬ */
    ULONG         ulVer;

    /* ģ����, VISP HA����ͳһ����Ϣ��, ������ģ������������ѵ���ģ���� */
    UCHAR         ucModID;

    /* ����������, ���庬���ɸ�ģ����� */
    UCHAR         ucOperation;

    /* ������Ϣ����(����HA��Ϣ�ײ�) */
    USHORT        usMsgLen;

    /* У���, ȱʡΪ0 */
    ULONG         ulChksum;
}HAMSGHEADER_S;

/* HAͨ������̽�ⱨ�����ݽṹ */
typedef struct tagHA_DETECT_TLV
{
    USHORT usSubMsgType; /* ��������Ϣ���� */
    USHORT usSubMsgLen;  /* ��������Ϣ���� */
    ULONG  ulLstSeqNum;  /* �ϴη��͵ı������*/
}HA_DETECT_TLV_S;

/* BFD HA �ص������ṹ���� */
typedef struct tagHA_BFDCALLBACK
{
    /* BFD�����ݴ����� */
    ULONG (*pfBFD_BATCH_HOOK_FUNC)(VOID);

    /* BFDƽ�������� */
    ULONG (*pfBFD_SMOOTH_HOOK_FUNC)(VOID);

    /* BFD���ݻָ������� */
    ULONG (*pfBFD_RESOTRE_HOOK_FUNC)(UCHAR *pBuf, ULONG ulMsgLen);

    /* BFD���Կ������ýӿ� */
    ULONG (*pfBFD_SETDBG_HOOK_FUNC)(ULONG ulDBG);

    /* BFD���Կ��ػ�ȡ�ӿ� */
    ULONG (*pfBFD_GETDBG_HOOK_FUNC)(ULONG *pulDBG);

    /* BFD HA���ĵ������ÿ��� */
    ULONG (*pfBFD_GETVERBOSEDBG_HOOK_FUNC)(ULONG *pulDBG);

    /* BFD HA���ĵ��Կ������ú��� */
    ULONG (*pfBFD_SETVERBOSETDBG_HOOK_FUNC)(ULONG pulDBG);

    /* BFD HA���Ĵ�ӡ���� */
    VOID (*pfBFD_HA_DBGOUTPUT_HOOK_FUNC)(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);

    ULONG (*pfBFD_HA_CLEAN_HOOK_FUNC)(VOID);

}HA_BFDCALLBACK_S ;


/* TWAMP HA callback function structure definition */
typedef struct tagHA_TWAMPCALLBACK
{
    /* Twamp Ha Batch backup hook function */
    ULONG (*pfTWAMP_BATCH_HOOK_FUNC)(VOID);

    /* Twamp Ha Smoothing hook function */
    ULONG (*pfTWAMP_SMOOTH_HOOK_FUNC)(VOID);

    /* TWAMP HA Input*/
    ULONG (*pfTWAMP_RESOTRE_HOOK_FUNC)(UCHAR *pBuf, ULONG ulMsgLen);

    /*TWAMP HA Clean Function*/
     ULONG (*pfTWAMP_HA_CLEAN_HOOK_FUNC)(VOID);


}HA_TWAMPCALLBACK_S ;


/*
   32λHA���������汾����֯��ʽ, ���ڴ�ͷ��, ����Ǹ�λ, �ұ��ǵ�λ

   |---4bit---|---4bit---|--------12bit--------|--- 4bit---|-------8bit------|
      R�汾��    C�汾��         B�汾��           ������    ���ݰ汾���޶���
*/
typedef struct tagHAVERSION
{
#if (VRP_BIG_ENDIAN == VRP_YES)
    ULONG ulRVersion: 4,    /* R�汾�� */
          ulCVersion: 4,    /* C�汾�� */
          ulBVersion: 12,   /* B�汾�� */
          ulSPVersion:4,    /* SP������ */
          ulHAUpdate: 8;    /* HA�޶��� */
#else
    ULONG ulHAUpdate: 8,    /* HA�޶��� */
          ulSPVersion:4,    /* SP������ */
          ulBVersion: 12,   /* B�汾�� */
          ulCVersion: 4,    /* C�汾�� */
          ulRVersion: 4;    /* R�汾�� */
#endif
}HAVERSION_S;

/* Begin of HA UPGRADE modification, 2010 December to 2011 January */
/* ��������ṹ����Ϊ�˽��VR6C02��VR6C05�汾�ϣ�HAVERSION_S���ڴ���ֽ����ʹ�ò���ȷ������ */
typedef struct tagHAVERSION_LD
{
    ULONG ulHAUpdate: 8,    /* HA�޶��� */
          ulSPVersion:4,    /* SP������ */
          ulBVersion: 12,   /* B�汾�� */
          ulCVersion: 4,    /* C�汾�� */
          ulRVersion: 4;    /* R�汾�� */
}HAVERSION_LD_S;
/* End of HA UPGRADE modification, 2010 December to 2011 January */

/*----------------------HAע�������ӵĺ�--------------------------------*/
/* ����������,��������������ɱ�� */
#define HA_MODULE_CANNOT_BACKUP  0
#define HA_MODULE_CAN_BACKUP     1

/* �������IPV4ģ�����ݵ���Ϣ */
#define HA_SLAVE_IP4_CLEAN         1

/* �������socketģ�����ݵ���Ϣ */
#define HA_SLAVE_SOCKET4_CLEAN     2

#define IS_EXTERN_HA_MID(MID) ((MID > HA_EXTERN_MID_MIN) && (MID < HA_EXTERN_MID_MAX))

#define IS_VISP_HA_MID(MID) (((MID > HA_MID_MIN) && (MID < HA_MID_MAX)) || (HA_MID_SLAVE_BOARD_ID == MID))

/* ����HA����̽�⹦��ʹ�õ�̽�ⱶ�������С��Χ�궨�� */
#define HA_KEEPALIVETHR_MAX 20
#define HA_KEEPALIVETHR_MIN 1
#define HA_KEEPALIVETHR_DEF 5

/*HA���ֶ�������ƽ������ʱ����ֹ�û����ò���,���򷵻ش�����*/
#define MODULE_CONFIGURE_DISABLE \
(\
    (TCPIP_HA_AMB == TCPIP_HA_GetBoardType()) && HA_IS_SMOOTH_OR_MANUAL && (!g_ulHABeforeSmooth) && g_ulHAInit\
)

/* Begin of HA UPGRADE modification, 2010 December to 2011 January */
#define VER_VISPV1R6C02 0x62
#define VER_VISPV1R6C05 0x65
#define VER_VISPV1R7C01 0x71
#define VER_VISPV1R8C01 0x81
#define VER_VISPV1R8C03 0x83
#define VER_VISPV1R8C05 0x85
#define VER_VISPV1R8C06 0x86
/* End of HA UPGRADE modification, 2010 December to 2011 January */

/* HA ע��ڵ� */
typedef struct tagHAREGISTERNODE
{
   DLL_NODE_S          stDLLNode;               /* List node,must be in first position in the struct */
   UCHAR               ucModuleId;              /* ע��ģ���ģ���(HA�ڲ�Ϊ�����) */
   UCHAR               szMoudleName[HA_MOUDLE_NAME_LEN]; /* ע��ģ������� */
   ULONG               ulPriority;              /* ģ�����ȼ� */
   ULONG               ulPriorMoudleBatchOver;  /* ǰһģ���Ƿ������������,���1,δ���0 */
   TCPIP_HA_MODULE_CALLBACK_S stCallBackSet;    /* ע��Ļص��������� */
} HAREGISTERNODE_S;


/*֧��HA��������ƽ������ʱ�ӿɲ���,����HAƽ��ʱ�����TICK�ṹ*/
typedef struct tagHA_SMOOTH_TICK
{
    TCPIP_CPUTICK_S stStartTick;
    TCPIP_CPUTICK_S stEndTick;
}HA_SMOOTH_TICK_S;

extern ULONG HA_GetVISPCompVtbl(VOID);
extern ULONG TCPIP_HA_MainTaskEntry (ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);
extern ULONG TCPIP_HA_RegisterBFDVtbl (HA_BFDCALLBACK_S * pfBFDCallBack);
extern ULONG TCPIP_HA_RegisterTWAMPVtbl (HA_TWAMPCALLBACK_S * pfTWAMPCallBack);
extern ULONG HA_RestoreByMoudleId(UCHAR * pucBuf,ULONG ulMsglen);
extern VOID  HA_Smooth_InSequence(VOID);
extern LONG  TCPIP_HA_ModuleCmp(VOID * val, DLL_NODE_S * pNode);

/* ��ȡ���嵱ǰ�������ͽӿ� */
extern ULONG TCPIP_HA_GetBoardType(VOID);
/* �����Ƿ�׼��������ѯ�ӿ�*/
extern ULONG TCPIP_HA_SlaveIsReady(VOID);

/* ������Ϣ���ͽӿ�,�������سɹ�ʱ��TCPIP_HA_SendMsg�ӿ��ڲ��ͷ��ڴ棬�������ⲿ�ͷ��ڴ�*/
extern ULONG TCPIP_HA_SendMsg(UCHAR *pMsgBuf, ULONG ulMsgLen);
/* HA�ڴ����뺯�� */
extern VOID *TCPIP_HA_Malloc(ULONG ulModID, ULONG ulLength);
/* HA�ڴ��ͷź��� */
extern ULONG TCPIP_HA_Free (VOID *pBuf);

/* ���ݽӿ����ͻ�ȡ�ײ��ʼ�������Ľӿ�*/
extern ULONG TCPIP_HA_GetPhyInitByType(ULONG ulType, UCHAR * szIfName, UINTPTR *pfPhyInitial);

/* �ӿڵײ�״̬�Ĳ�ѯ�ӿ�*/
extern ULONG TCPIP_HA_GetIfPhyState (ULONG ulIfIndex);

/* ��ǰ�Ƿ���Խ��б��ݵ��жϽӿ�*/
extern ULONG TCPIP_HA_IsCanSndBakMsg (ULONG ulMid);

/* HA������ؽӿ� */
extern VOID  TCPIP_HA_DbgOutPut(UCHAR *pucBuf,ULONG ulMsglen,ULONG ulCmd);

extern ULONG g_ulHAManualOrSmooth ;
extern ULONG g_ulHABeforeSmooth ;
extern ULONG g_ulHARcvSmoothEvent ;
extern ULONG g_ulHAMsgSeq ;
extern ULONG g_ulHAIPv4QueID;
extern ULONG g_ulHASocketQueID;
extern ULONG g_ulHATaskID ;
extern ULONG g_ulHASm  ;
extern HASTAT_S  g_stBakStat;
extern ULONG g_ulHAInit ;
extern ULONG g_ulSRMInit ;
extern ULONG g_ulHABfdExist ;
extern ULONG g_ulHABatchflag  ;
extern ULONG g_ulHABatchMsgOver ;
extern ULONG g_ulHASockRunPri ;
extern ULONG g_ulEnableHAUpdate;
extern ULONG g_ulHAVersion;
extern ULONG g_ulNeedHACksum;
extern ULONG g_ulHaVersion_Old;

extern TCPIP_HA_CALLBACK_S    g_stHACallBack ;
extern HA_BFDCALLBACK_S       g_stBFDHACallBack ;

extern ULONG HA_RestoreByMoudleId(UCHAR * pucBuf, ULONG ulMsglen);
extern ULONG TCPIP_HA_Clean(VOID);

extern HA_GETBOARDTYPE_FUNC     g_pfHAGetBoardType;
extern HA_MALLOC_FUNC           g_pfHAMalloc;
extern HA_FREE_FUNC             g_pfHAFree;
extern HA_GETPHYINITBYTYPE_FUNC g_pfHAGetPhyInitByType;
extern HA_GETIFPHYSTATE_FUNC    g_pfHAGetIfPhyState;
extern HA_SENDMSG_FUNC          g_pfHASendMsg;
extern HA_SLAVEISREADY_FUNC     g_pfHASlaveIsReady;
extern HA_BADVERNOTIFY_FUNC     g_pfHABadVerNotify;

extern VOID   TCPIP_HA_ResolveVersion(const CHAR *szTCPIPVersion, const ULONG ulHAUpdate, ULONG *pulHAVersion);
extern ULONG  TCPIP_HA_GetVersion(UCHAR ucModID, ULONG *pulVersion);
extern ULONG  TCPIP_HA_IsInvalidVersion(UCHAR ucModID, ULONG ulVersion);
extern USHORT TCPIP_HA_GetChecksum(USHORT *pusCalcFrom, LONG lTotalLen);
extern USHORT TCPIP_HA_CalcCksum(USHORT *pusCalcFrom, LONG lTotalLen);
extern ULONG  TCPIP_HA_IsSpecRcVer(UCHAR ucVer);
/* ֧��MBSC��ƷHA��ǿ��������ӵĺ��� */
extern ULONG TCPIP_HA_SendDetectPkt(VOID);
extern VOID TCPIP_HA_DetectTimer(VOID *pPara);
extern ULONG TCPIP_HA_CreateDetectTimer(ULONG ulTime);

/* trunkģ��ƽ����ɱ�־. �����ʼ��Ϊ0; �����ʼ��Ϊ1,��ƽ����ɺ���λ0 */
extern ULONG g_ulTrunkBeforeSmooth;

#ifdef  __cplusplus
}
#endif

#endif /* _TCPIP_HA_H_ */

