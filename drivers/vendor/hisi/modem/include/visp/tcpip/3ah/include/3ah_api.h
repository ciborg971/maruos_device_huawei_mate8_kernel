/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_api.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH  
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AHģ���û�apiͷ�ļ��������û���Ҫʹ�õ����ݽṹ�����apiԭ��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_API_H_
#define _3AH_API_H_

#ifdef __cplusplus
extern "C"{
#endif

/* 3AH����������,�������������,��Ӻ���������� */
typedef enum enumOam3ahErrCode
{
    OAM3AH_OK = VOS_OK,                 /* 0  OK                                */
    OAM3AH_ERR,                         /* 1  ERROR                             */
    OAM3AH_ERR_HA_IS_SMOOTHING,         /* 2  3AH��ƽ��������ֶ���������       */
    OAM3AH_ERR_PARA,                    /* 3  ������Ч�Դ���                    */
    OAM3AH_ERR_NULL_POINTER,            /* 4  ָ���������                      */ 
    OAM3AH_ERR_IF_NULL,                 /* 5  �ӿڲ�����                        */
    OAM3AH_ERR_IF_INVALID,              /* 6  �ӿ����ʹ���                      */
    OAM3AH_ERR_MEMORY,                  /* 7  �ڴ�ռ䲻��                      */
    OAM3AH_ERR_ENABLED,                 /* 8  3AH��ʹ��                         */
    OAM3AH_ERR_DISABLED,                /* 9  3AHδʹ��                         */
    OAM3AH_ERR_NOTINACTIVE,             /* 10 ��3AH������                       */
    OAM3AH_ERR_NOTINLBREMOTE,           /* 11 3AHδ���ڻ��ط�����̬             */
    OAM3AH_ERR_CB_NOTEXIST,             /* 12 3AH���ÿ��ƿ鲻����               */
    OAM3AH_ERR_EVENT_WIN,               /* 13 ��·�¼����ڷǷ�(������������)    */
    OAM3AH_ERR_EVENT_THRESH,            /* 14 ��·�¼�����ֵ�Ƿ�                */
    OAM3AH_ERR_WIN_THRESH_CONFLICT,     /* 15 3AH����ֵ������ֵ��ͻ             */
    OAM3AH_ERR_NP_NOT_SUPPORT,          /* 16 NPģʽ��֧��                      */
    OAM3AH_ERR_WRONG_STATE,             /* 17 3AH���ڴ����״̬��               */
    OAM3AH_ERR_WRONG_MODE,              /* 18 3AHʹ��ȥʹ�ܻ���ģʽ����         */ 
    OAM3AH_ERR_LINKEV_DISABLE,          /* 19 �¼�֪ͨȥʹ��                    */
    OAM3AH_ERR_EVENT_NOT_SATISFY,       /* 20 �¼���������������                */
    OAM3AH_ERR_INLB,                    /* 21 3AH���ڻ���ģʽ                   */
    OAM3AH_ERR_LB_TEST_NP,              /* 22 NPʵ�ֻ���ģʽ                    */
    OAM3AH_ERR_NO_REGISTER,             /* 23 3AHģ��δע��                     */
    OAM3AH_ERR_PORT_IS_VIRTUAL,         /* 24 �ӿڷǱ���ӿ�                    */
    OAM3AH_ERR_MBUF_PREPEND,            /* 25 MBUFָ��ǰ�ƴ���                  */
    OAM3AH_ERR_FRAME_ACT,               /* 26 ��֡/��֡��ʵ�ַ�ʽ���ò�֧��     */
    OAM3AH_ERR_WIN_THRESH_CONFLICT_NUMMODE,     /* 27 3AH��֡�����¼�����ģʽΪ֡��Ŀģʽʱ����ֵ������ֵ��ͻ */
    OAM3AH_ERR_HA_IS_SMB,               /* 28 3AH���岻����������             */
    OAM3AH_ERR_WIN_THRESH_CONFLICT_SYMMODE,     /* 29 3AH������������¼�����ģʽΪ������ģʽʱ����ֵ������ֵ��ͻ */
    OAM3AH_ERR_VIRTUA_ENABLED,          /* 30 3ah�Ѿ���ʹ����                   */
    OAM3AH_ERR_NOT_SUPPORT_IF,          /* 31 3ah��ʹ��ֻ֧�ֶ���Eth�ںͶ���TrunkPort�� */
    OAM3AH_ERR_NEG_TIME_REACHMAX,       /* 32 3AH�״�Э�̲�ͨ���澯ʱ�䳬�����ֵ */
    OAM3AH_ERR_CREATE_TIMER_FAIL,       /* 33 3AH�״�Э�̲�ͨ������ʱ�ڲ�������ʱ��ʧ�� */
    OAM3AH_ERR_DELETE_TIMER_FAIL,       /* 34 3AH�״�Э�̲�ͨ����ʱ��ɾ��ʧ�� */
    OAM3AH_ERR_RMT_NOTSPPT_LB,          /* 35 �Զ˲�֧�ֻ��أ�����ʹ�ܻ��ز���ʧ�ܣ�VISPV100R007C01ά����Ŀ�����Ĵ����� */
    OAM3AH_ERR_INVALID_MAIN_FSMSTATE,   /* 36 �ӿ�3AH״̬��״̬�Ƿ� */
        
    OAM3AH_ERR_MAXCODE                  /* 3AH���������ֵ,�Ժ���Ӵ������밴˳����ӵ���ǰ */
}OAM3AH_ERRCODE_E;

/* 8�ֽ����ݱ�ʾ */
typedef struct tagDULONG_S
{
    ULONG ulDulHi;
    ULONG ulDulLo;
}DULONG_S;

/* �������3AH������Ϣ�ṹ�� */
typedef struct tag3ahCfgInfo
{
    ULONG  ul3AHEnable;                     /* �Ƿ���ʹ��                       */
    ULONG  ul3AHMode;                       /* ����ģʽ 0~����ģʽ��1~����ģʽ  */
    ULONG  ulDetectInteval;                 /* ̽������                         */
    ULONG  ulPDUSize;                       /* ���PDUSize                      */
    ULONG  ulLbTestMode;                    /* ���ز���ģʽ 0~visp�������ģʽ��1~NP����ģʽ    */
    ULONG  ulIsEnableEvent;                 /* �Ƿ�ʹ����·�¼�����λ������ӵ͵�����λ�ֱ��ʾ�����¼���ʹ��״̬��
                                               ������������¼��� ��֡�¼�������֡�����¼�����֡���¼� */

    ULONG  ulSymbolPeriodWindow;            /* ������������¼�����     */
    ULONG  ulSymbolPeriodThreshold;         /* ������������¼�����     */
    ULONG  ulFrameWindow;                   /* ����֡�¼�����           */
    ULONG  ulFrameThreshold;                /* ����֡�¼�����           */
    ULONG  ulFramePeriodWindow;             /* ����֡�����¼�����       */
    ULONG  ulFramelPeriodThreshold;         /* ����֡�����¼�����       */
    ULONG  ulFrameSecondSummaryWindow;      /* ����֡���ۼ��¼�����     */
    ULONG  ulFrameSecondSummaryThreshold;   /* ����֡���ۼ��¼�����     */
                                            
    ULONG  ulIsEnableFault;                 /* �Ƿ�ʹ�ܽ�����·�¼�����λ��� ���ӵ͵�����λ�ֱ��ʾ���½����¼���
                                               ʹ��״̬����·���ϡ��������ϡ������¼� */
    ULONG  ulLocalBoardState;               /* �������õĽӿ�������Ϣ */
    ULONG  ulRemoteBoardState;              /* �����ԶԶ˵Ľӿ�������Ϣ */
                                               
}OAM3AH_CFG_INFO_S;

/*Added by wangtong207740, HIU 3AH�����չ, 2012/6/14 */
/* �������3AH������Ϣ�ṹ�� */
typedef struct tag3ahCfgInfoEx
{
    ULONG  ul3AHEnable;                     /* �Ƿ���ʹ��                       */
    ULONG  ul3AHMode;                       /* ����ģʽ 0~����ģʽ��1~����ģʽ  */
    ULONG  ulDetectInteval;                 /* ̽������                         */
    ULONG  ulPDUSize;                       /* ���PDUSize                      */
    ULONG  ulLbTestMode;                    /* ���ز���ģʽ 0~visp�������ģʽ��1~NP����ģʽ    */
    ULONG  ulIsEnableEvent;                 /* �Ƿ�ʹ����·�¼�����λ������ӵ͵�����λ�ֱ��ʾ�����¼���ʹ��״̬��
                                               ������������¼��� ��֡�¼�������֡�����¼�����֡���¼� */

    DULONG_S  stSymbolPeriodWindow;            /* ������������¼�����     */
    DULONG_S  stSymbolPeriodThreshold;         /* ������������¼�����     */
    USHORT  usFrameWindow;                   /* ����֡�¼�����           */
    UCHAR szReserve[2];                      /* �ֽڶ��� */
    ULONG  ulFrameThreshold;                /* ����֡�¼�����           */
    ULONG  ulFramePeriodWindow;             /* ����֡�����¼�����       */
    ULONG  ulFramelPeriodThreshold;         /* ����֡�����¼�����       */
    USHORT  usFrameSecondSummaryWindow;      /* ����֡���ۼ��¼�����     */
    USHORT  usFrameSecondSummaryThreshold;   /* ����֡���ۼ��¼�����     */
                                            
    ULONG  ulIsEnableFault;                 /* �Ƿ�ʹ�ܽ�����·�¼�����λ��� ���ӵ͵�����λ�ֱ��ʾ���½����¼���
                                               ʹ��״̬����·���ϡ��������ϡ������¼� */
    ULONG  ulLocalBoardState;               /* �������õĽӿ�������Ϣ */
    ULONG  ulRemoteBoardState;              /* �����ԶԶ˵Ľӿ�������Ϣ */
                                               
}OAM3AH_CFG_INFO_EX_S;
/* End of Added by wangtong207740, 2012/6/14 */

/*�ӿ�OAMPDU����ͳ��*/
typedef struct tagOam3ahPduStat
{
    ULONG ulSndTotalOampdu;                 /* �ӿڷ����ܵ�OAMPDU����        */
    ULONG ulSndDropOampdu;                  /* �ӿڷ���ʱ�ܵĶ���OAMPDU����  */
    ULONG ulSndInfoOampdu;                  /* �ӿڷ�����ϢOAMPDU����        */
    ULONG ulSndEventOampdu;                 /* �ӿڷ����¼�OAMPDU����        */
    ULONG ulSndFaultOampdu;                 /* �ӿڷ��͹���OAMPDU����        */
    ULONG ulSndLbOampdu;                    /* �ӿڷ��ͻ��ؿ���OAMPDU����    */
    
    ULONG ulRcvTotalOampdu;                 /* �ӿڽ����ܵ�OAMPDU����        */
    ULONG ulRcvDropOampdu;                  /* �ӿڽ����ܵĶ���OAMPDU����    */
    ULONG ulRcvInfoOampdu;                  /* �ӿڽ�����ϢOAMPDU����        */
    ULONG ulRcvEventOampdu;                 /* �ӿڽ����¼�OAMPDU����        */
    ULONG ulRcvFaultOampdu;                 /* �ӿڽ��չ���OAMPDU����        */
    ULONG ulRcvLbOampdu;                    /* �ӿڽ��ջ��ؿ���OAMPDU����    */
}OAM3AH_PDUSTAT_S;



/* ��ȡ�ײ��֡���亯��ԭ��     */
typedef ULONG (*GET_PHY_ERROR_FRAME_HOOK_FUNC)(ULONG ulIfIndex, DULONG_S *pstdulNum);

/* �·������¼��������亯��ԭ�� */
typedef ULONG (*SET_LINK_EVENT_WINTHRSH_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulEventType, ULONG ulEnabled,
                                                   ULONG ulErrorWindow, ULONG ulErroredThreshold);

typedef ULONG (*SET_LINK_EVENT_WINTHRSH_EX_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulEventType, ULONG ulEnabled,DULONG_S dulErrorWindow, DULONG_S dulErroredThreshold);

typedef ULONG (*LBINPUT_HOOK_FUNC) (struct tagMBuf *pstMBuf, ULONG ulIfIndex);

#define OAM3AH_LB_REMOTE_INPUT  0       /* ���ط����ע����պ���   */
#define OAM3AH_LB_LOCAL_INPUT   1       /* ������Ӧ��ע����պ���   */

/* ��֯�Զ���TLV����֪ͨ���亯��ԭ�� */
typedef ULONG (*OAM3AH_ORG_SPEC_NOTIFY_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulOrgSpecType, VOID* OrgSpecInfo);

/* �Զ���TLV����֪ͨ����: ������Ϣ���� */
#define OAM3AH_ORGSPEC_BOARDSTATE_TYPE 0x01

/* �Զ���TLV����֪ͨ����: ������Ϣ���Ͷ�Ӧ������ */
typedef struct tagOam3ahOrgSpecBoardState
{
    /* 0-�Զ���������Ϣ֪ͨ; 1-������Ϣ; 2-������Ϣ */
    ULONG ulOldState;
    ULONG ulNewState;
}OAM3AH_ORGSPEC_BOARDSTATE_S;


/* �¼�/����ʹ�ܽӿ�ʹ�ܲ�����BITλö��  */  
typedef enum enOam3ahEnableBit
{
    OAM3AH_BIT_ERR_SYMPRD = 0,
    OAM3AH_BIT_ERR_FRAME,
    OAM3AH_BIT_ERR_FRMPRD,
    OAM3AH_BIT_ERR_FRMSECSUM,

    OAM3AH_BIT_LINKFAULT,
    OAM3AH_BIT_DYINGGASP,
    OAM3AH_BIT_CRITICALEVT,
    OAM3AH_BIT_MAX,
}OAM3AH_ENABLE_BIT_E;

/* max event enable value */
#define OAM3AH_EVENT_MAX_ENABLE   ((0x1 << OAM3AH_BIT_MAX) - 1)

/* �û��ӿ��¼����Ͳ���ö�ٶ���  */
typedef enum
{
    OAM3AH_API_LINKEVENT_SYMPRD = 1,
    OAM3AH_API_LINKEVENT_FRAME,
    OAM3AH_API_LINKEVENT_FRMPRD,
    OAM3AH_API_LINKEVENT_FRMSECSUM,
}OAM3AH_API_LINKEVENT_E;

/* �û��ӿڹ������Ͳ���ö�ٶ���  */
typedef enum
{
    OAM3AH_API_FAULT_LINKFAULT = 0,
    OAM3AH_API_FAULT_DYINGGASP,
    OAM3AH_API_FAULT_CRITICALEVT,
}OAM3AH_API_FAULT_E;

/* ��ȡ3AH״̬��״̬ */
typedef enum tagOam3ahStateInfo
{
    OAM3AH_SESSION_IDLE,               /* δʹ��3AH��״̬������IDLE״̬    */
    OAM3AH_SESSION_DISCOVER,           /* ���ڷ��ֽ׶�                     */
    OAM3AH_SESSION_DETECT,             /* ��ɷ��֣���ʱ̽��׶�           */
    OAM3AH_SESSION_LB_LOCAL,           /* ���˴��ڻ�����Ӧ��̬             */
    OAM3AH_SESSION_LB_REMOTE,          /* ���˴��ڻ��ط�����̬             */
}OAM3AH_STATE_INFO_E;

/* �¼�/���Ϸ���λ��:����/�Զ�  */
typedef enum enEventLocation
{
    OAM3AH_EVENT_LCL,               /* �����¼�/����    */
    OAM3AH_EVENT_RMT                /* �Զ��¼�/����    */
}OAM3AH_EVENT_LOCATION_E;

/* ����״̬ */
typedef enum enFaultState
{
    OAM3AH_FAULT_END,           /* ����״̬��־,������ʧ     */
    OAM3AH_FAULT_BEGIN,         /* ����״̬��־,���Ͽ�ʼ     */
}OAM3AH_FAULT_STATE_E;

/* 3ah HAͳ����Ϣ���ݽṹ */
typedef struct tag3ahHaStat
{
    ULONG ul3ahHaOutSucsPkt;    /* ����ɹ����͵�3AH���ݱ�����  */
    ULONG ul3ahHaOutFailPkt;    /* ���巢�ͱ��ݱ���ʧ����       */
    ULONG ul3ahHaInSucsPkt;     /* ������յĻָ��ɹ���HA������ */
    ULONG ul3ahHaInFailPkt;     /* ������յĻָ�ʧ�ܵ�HA������(�����Ƿ�����) */ 
}OAM3AH_HASTAT_S;


/* 3AH����澯״̬ */
typedef struct tagOam3ahWarnState
{ 
    ULONG ulLclLinkFaultWarn;     /* ������·���ϸ澯 */
    ULONG ulRmtLinkFaultWarn;     /* Զ����·���ϸ澯 */
    ULONG ulLclDyingGaspWarn;     /* �����������ϸ澯 */
    ULONG ulRmtDyingGaspWarn;     /* Զ���������ϸ澯 */
    ULONG ulLclCriticalEvtWarn;   /* ���˽����¼��澯 */
    ULONG ulRmtCriticalEvtWarn;   /* Զ�˽����¼��澯 */                                                                 
}OAM3AH_WARN_STATE_S;                          

/* lb test mode */
#define OAM3AH_LB_TEST_VISP     0   /* visp���ʵ�ֻ��ع��� */
#define OMM3AH_LB_TEST_NP       1   /* npʵ�ֻ��ع���       */

/* 3ah work mode */
#define OAM3AH_PASSIVE_MODE     0   /*����ģʽΪ����ģʽ*/
#define OAM3AH_ACTIVE_MODE      1   /*����ģʽΪ����ģʽ*/

/* define 3ah enable & disable */
#define OAM3AH_DISABLE          0
#define OAM3AH_ENABLE           1
#define OAM3AH_VIRTUAL_ENABLE   2

/* board state */
#define OAM3AH_BOARD_STATE_NULL     0 /* ȡ����Զ�ͨ�汾������״̬ */
#define OAM3AH_BOARD_STATE_MASTER   1
#define OAM3AH_BOARD_STATE_SLAVE    2

/* DULONG_S(˫�ֽ�)�ṹ����� ---- BEGIN */
#define DULONG_S_COMPARE(dulFirst,dulSecond) \
    (((dulFirst).ulDulHi<(dulSecond).ulDulHi)?-1: \
        (((dulFirst).ulDulHi>(dulSecond).ulDulHi)?1: \
            (((dulFirst).ulDulLo<(dulSecond).ulDulLo)?-1: \
                (((dulFirst).ulDulLo>(dulSecond).ulDulLo)?1:0))))

#define DULONG_S_ADD(dulSum,dulFirst,dulSecond)    \
{ \
    DULONG_S dulSum_temp; \
    \
    (dulSum_temp).ulDulLo = (dulFirst).ulDulLo+(dulSecond).ulDulLo; \
    (dulSum_temp).ulDulHi = (dulFirst).ulDulHi+(dulSecond).ulDulHi+(ULONG)((dulSum_temp).ulDulLo<(dulFirst).ulDulLo); \
    (dulSum).ulDulLo = (dulSum_temp).ulDulLo;\
    (dulSum).ulDulHi = (dulSum_temp).ulDulHi;\
}

#define DULONG_S_SUB(dulResult,dulFirst,dulSecond) \
{ \
    DULONG_S dulRst_temp; \
    \
    (dulRst_temp).ulDulLo = (dulFirst).ulDulLo-(dulSecond).ulDulLo; \
    (dulRst_temp).ulDulHi = (dulFirst).ulDulHi-(dulSecond).ulDulHi-(ULONG)((dulRst_temp).ulDulLo>(dulFirst).ulDulLo); \
    (dulResult).ulDulLo = (dulRst_temp).ulDulLo;\
    (dulResult).ulDulHi= (dulRst_temp).ulDulHi;\
}

#define DULONG_S_SELFADD(dulResult)\
{\
    (dulResult).ulDulLo++;\
    if((dulResult).ulDulLo == 0)\
        (dulResult).ulDulHi++; \
}

#define DULONG_S_COPY(dulTo, dulFrom)\
{\
    (dulTo).ulDulHi = (dulFrom).ulDulHi;\
    (dulTo).ulDulLo = (dulFrom).ulDulLo;\
}

#define DULONG_S_COMPARE_ULONG(dulFirst,ulSecond)\
(((dulFirst).ulDulHi>0)?1: \
        (((dulFirst).ulDulLo>ulSecond)?1: \
            (((dulFirst).ulDulLo<ulSecond)?-1:0)))

/* DULONG_S(˫�ֽ�)�ṹ����� ---- END */

/* ------------------------------------------------------------------------------------ */
/* 3ah_api.c */
/*******************************************************************************
*    Func Name: TCPIP_3AH_Enable
*  Description: ʹ��/ȥʹ�ܽӿڵ�3AH����
*        Input: ULONG ulIfIndex:                �ӿ�����
*               ULONG ul3AHEnable:              ʹ��/ȥʹ�� 3AH ���ܣ�0 ȥʹ�ܣ�1 ʹ�ܣ�2��ʹ��
*       Output: 
*       Return: OAM3AH_OK                       �����ɹ�
*               OAM3AH_ERR_HA_IS_SMOOTHING      ����ƽ��
*               OAM3AH_ERR_PARA                 ��������
*               OAM3AH_ERR_IF_NULL              �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID           �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL      �ӿڷǱ���ӿ�
*               OAM3AH_ERR_MEMORY               �ڴ����ʧ��
*               OAM3AH_ERR_ENABLED              �ӿ���ʹ��3AH
*               OAM3AH_ERR_CB_NOTEXIST          3AH���ƿ鲻����
*               OAM3AH_ERR_DISABLED             �ӿ��Ѿ�ȥʹ��
*               OAM3AH_ERR_NO_REGISTER          3AHģ��δע�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   chenfutian69112         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_Enable(ULONG ulIfIndex, ULONG ul3AHEnable);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetDetect
*  Description: ����3AH��̽������
*        Input: ULONG ulIfIndex:                �ӿ�����
*               ULONG ulDetectInterval:         ̽������
*       Output: 
*       Return: OAM3AH_OK                       �����ɹ�
*               OAM3AH_ERR_HA_IS_SMOOTHING      ����ƽ��
*               OAM3AH_ERR_PARA                 ̽�����ڲ�������
*               OAM3AH_ERR_NP_NOT_SUPPORT       ���õ�̽������NP��֧��
*               OAM3AH_ERR_IF_NULL              �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID           �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL      �ӿڷǱ���ӿ�
*               OAM3AH_ERR_MEMORY               �ڴ����ʧ��
*               OAM3AH_ERR_NO_REGISTER          3AHģ��δע�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   LY(57500)               Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetDetect(ULONG ulIfIndex, ULONG ulDetectInteval);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetLoopback
*  Description: ʹ��/ȥʹ��Զ�˻���
*        Input: ULONG ulIfIndex:                �ӿ�����
*               ULONG ulLoopbackCmd:            ʹ��/ȥʹ�����0ȥʹ�ܣ�1ʹ�ܡ�
*       Output: 
*       Return: OAM3AH_OK                       �����ɹ�
*               OAM3AH_ERR_HA_IS_SMOOTHING      ����ƽ��
*               OAM3AH_ERR_PARA                 ��������
*               OAM3AH_ERR_IF_NULL              �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID           �ӿ����ʹ���
*               OAM3AH_ERR_CB_NOTEXIST          3AH���ƿ鲻����
*               OAM3AH_ERR_DISABLED             δʹ��3AH
*               OAM3AH_ERR_WRONG_MODE           �ӿڹ���ģʽ����
*               OAM3AH_ERR_PORT_IS_VIRTUAL      �ӿڷǱ���ӿ�
*               OAM3AH_ERR_WRONG_STATE          ״̬�����ڴ����״̬
*               OAM3AH_ERR_NO_REGISTER          3AHģ��δע�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   chenfutian69112         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetLoopback(ULONG ulIfIndex, ULONG ulLoopbackCmd);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetLbTestMode
*  Description: ���û��ز���ģʽ
*        Input: ULONG ulIfIndex:                �ӿ�����
*               ULONG ulLbTestMode:             ���ز���ģʽ,0 VISP���ʵ�ֻ���,1 NPʵ�ֻ���
*       Output: 
*       Return: OAM3AH_OK                       �����ɹ�
*               OAM3AH_ERR_HA_IS_SMOOTHING      ����ƽ��
*               OAM3AH_ERR_PARA                 ��������
*               OAM3AH_ERR_IF_NULL              �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID           �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL      �ӿڷǱ���ӿ�
*               OAM3AH_ERR_MEMORY               �ڴ����ʧ��
*               OAM3AH_ERR_INLB                 ���ڻ��ش���״̬
*               OAM3AH_ERR_NO_REGISTER          3AHģ��δע�� 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   chenfutian69112         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetLbTestMode (ULONG ulIfIndex, ULONG ulLbTestMode);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GlobalDisable
*  Description: ȫ��ȥʹ��3AH����
*        Input: VOID
*       Output: 
*       Return: OAM3AH_ERR_HA_IS_SMOOTHING  ����ƽ��
*               OAM3AH_ERR_NO_REGISTER      �ӿ�δע��
*               OAM3AH_OK                   �ɹ�
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GlobalDisable(VOID);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetMode
*  Description: ���ӿ���������3AH����ģʽ
*        Input: ULONG ulIfIndex:            �ӿ�����
*               ULONG ul3AHMode:            ����ģʽ��0-����ģʽ��1-����ģʽ��
*       Output: 
*       Return: OAM3AH_ERR_HA_IS_SMOOTHING: ����ƽ��
*               OAM3AH_ERR_IF_NULL:         �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID:      �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL  �ӿڷǱ���ӿ�
*               OAM3AH_ERR_CB_NOTEXIT:      3AH���ƿ鲻����
*               OAM3AH_ERR_ENABLED:         3AH�Ѿ�ʹ��
*               OAM3AH_ERR_NO_REGISTER:     �ӿ�δע��
*               OAM3AH_OK:                  ���óɹ�
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetMode(ULONG ulIfIndex, ULONG ul3AHMode);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetPduSize
*  Description: ���ӿ�����OAMPDU��󳤶�
*        Input: ULONG ulIfIndex:            �ӿ�����
*               ULONG ulPduSize:            ���OAMPDU����ֵ
*       Output: 
*       Return: OAM3AH_ERR_HA_IS_SMOOTHING: ����ƽ��
*               OAM3AH_ERR_IF_NULL:         �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID:      �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL  �ӿڷǱ���ӿ�
*               OAM3AH_ERR_MEMORY:          �ڴ����ʧ��
*               OAM3AH_ERR_PARA:            ��������
*               OAM3AH_ERR_NO_REGISTER:     �ӿ�δע��
*               OAM3AH_OK:                  ���óɹ�
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetPduSize(ULONG ulIfIndex, ULONG ulPduSize);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetCfgInfo
*  Description: ���ӿڻ�ȡ3AH������Ϣ
*        Input: ULONG ulIfIndex:                    �ӿ�����
*       Output: OAM_3AH_CFG_INFO_S* pst3AHCfgInfo:  �������������Ϣ���ڴ�ָ��
*       Return: OAM3AH_ERR_NULL_POINTER:            ָ�����Ϊ��
*               OAM3AH_ERR_IF_NULL:                 �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID:              �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL          �ӿڷǱ���ӿ�
*               OAM3AH_ERR_CB_NOTEXIST:             ��ȡ3AH���ƿ�ʧ��
*               OAM3AH_ERR_NO_REGISTER:             �齨δע��
*               OAM3AH_OK:                          ��ȡ������Ϣ�ɹ�
*      Caution: �û����������ͷ�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GetCfgInfo(ULONG ulIfIndex, OAM3AH_CFG_INFO_S* pst3AHCfgInfo);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetCfgInfoEx
* Date Created: 2012-06-14
*       Author: wangtong207740
*  Description: ���ӿڻ�ȡ3AH������Ϣ
*        Input: ULONG ulIfIndex:                    �ӿ�����
*       Output: OAM_3AH_CFG_INFO_S* pst3AHCfgInfo:  �������������Ϣ���ڴ�ָ��
*       Return: OAM3AH_ERR_NULL_POINTER:            ָ�����Ϊ��
*               OAM3AH_ERR_IF_NULL:                 �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID:              �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL          �ӿڷǱ���ӿ�
*               OAM3AH_ERR_CB_NOTEXIST:             ��ȡ3AH���ƿ�ʧ��
*               OAM3AH_ERR_NO_REGISTER:             �齨δע��
*               OAM3AH_OK:                          ��ȡ������Ϣ�ɹ�
*      Caution: �û����������ͷ�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-06-14   wangtong207740          Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GetCfgInfoEx(ULONG ulIfIndex, OAM3AH_CFG_INFO_EX_S* pst3AHCfgInfo);
/*******************************************************************************
*    Func Name: TCPIP_3AH_ShowInfo
*  Description: ���ӿ���ʾ3AH��Ҫ��Ϣ
*        Input: char *szIfName:�ӿ���
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
VOID  TCPIP_3AH_ShowInfo(char *szIfName);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetFSMInfo
*  Description: ���ӿڻ�ȡ״̬����Ϣ
*        Input: ULONG ulIfIndex:                �ӿ�����
*       Output: ULONG* pulState:                ����״̬��״̬�ڴ�ָ��
*       Return: OAM3AH_ERR_HA_IS_SMOOTHING:     ����ƽ��
*               OAM3AH_ERR_NULL_POINTER:        ����״̬��״̬�ڴ�ָ��Ϊ��
*               OAM3AH_ERR_IF_NULL:             �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID:          �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL      �ӿڷǱ���ӿ�
*               OAM3AH_ERR_CB_NOTEXIST:         ��ȡ�ӿڿ��ƿ�ʧ��
*               OAM3AH_ERR_NO_REGISTER:         �ӿ�δע��
*               OAM3AH_OK:                      ��ȡ�ɹ�
*      Caution: �û����������ͷ�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GetFSMInfo(ULONG ulIfIndex, ULONG* pulState);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetPacketStat
*  Description: ���ӿڻ�ȡOAMͳ�Ʊ�����Ϣ
*        Input: ULONG ulIfIndex:                    �ӿ�����
*       Output: OAM_3AH_PDUSTAT_S * pstOampduStat:  ����ͳ����������ݽṹָ��
*       Return: OAM3AH_ERR_NULL_POINTER:            ָ��Ϊ��
*               OAM3AH_ERR_IF_NULL:                 �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID:              �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL          �ӿڷǱ���ӿ�
*               OAM3AH_ERR_CB_NOTEXIST:             ��ȡ�ӿڿ��ƿ�ʧ��
*               OAM3AH_ERR_NO_REGISTER:             �ӿ�δע��
*               OAM3AH_OK:                          ��ȡ�ɹ�
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GetPacketStat(ULONG ulIfIndex, OAM3AH_PDUSTAT_S * pstOampduStat);
/*******************************************************************************
*    Func Name: TCPIP_3AH_ShowPacketStat
*  Description: ���ӿ���ʾOAMͳ�Ʊ�����Ϣ
*        Input: char *szIfName:     �ӿ���
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
VOID  TCPIP_3AH_ShowPacketStat(CHAR* szIfName);
/*******************************************************************************
*    Func Name: TCPIP_3AH_ClearPacketStat
*  Description: ���ӿ�����OAM����ͳ����Ϣ
*        Input: ULONG ulIfIndex:                �ӿ�����
*       Output: 
*       Return: OAM3AH_ERR_IF_NULL:             �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID:          �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL      �ӿڷǱ���ӿ�
*               OAM3AH_ERR_CB_NOTEXIST:         ��ȡ�ӿڿ��ƿ�ʧ��
*               OAM3AH_ERR_NO_REGISTER:         �ӿ�δע��
*               OAM3AH_OK:                      �ɹ�
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_ClearPacketStat(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetDbgSwitch
*  Description: ���ӿ����õ��Կ��ؼ���
*        Input: ULONG ulIfIndex:            �ӿ�����
*               ULONG ulDebugSwitche:       ���Կ��ؼ���,���Լ����Ϊ4����
*                                           OAM���ĵ��Կ���(0x1),״̬��Ǩ�Ƶ��Կ���(0x2),
*                                           ���ز��Ա��ĵ��Կ���(0x4),�����ĵ��Կ���(0x8)
*       Output: 
*       Return: OAM3AH_ERR_PARA:            �����������
*               OAM3AH_ERR_IF_NULL:         �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID:      �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL  �ӿڷǱ���ӿ�
*               OAM3AH_ERR_CB_NOTEXIST:     ��ȡ�ӿڿ��ƿ�ʧ��
*               OAM3AH_ERR_NO_REGISTER:     �齨δע��
*               OAM3AH_OK:                  �ɹ�
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetDbgSwitch(ULONG ulIfIndex, ULONG ulDebugSwitche);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetDbgSwitch
*  Description: ���ӿڻ�ȡ���Կ��ؼ���
*        Input: ULONG ulIfIndex:            �ӿ�����
*       Output: ULONG * pulDugInfo:         ������Կ����ڴ�ָ��
*       Return: OAM3AH_ERR_PARA:            �����������
*               OAM3AH_ERR_IF_NULL:         �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID:      �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL  �ӿڷǱ���ӿ�
*               OAM3AH_ERR_CB_NOTEXIST:     ��ȡ�ӿڿ��ƿ�ʧ��
*               OAM3AH_ERR_NO_REGISTER:     �ӿ�δע��
*               OAM3AH_OK:                  �ɹ�
*      Caution: �û����������ͷ�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   GeXianJun121208         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_GetDbgSwitch(ULONG ulIfIndex, ULONG *pulDugInfo);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetPhyErrorFrameNumHook
*  Description: ע���ȡ�ײ��֡�����亯��
*        Input: GET_PHY_ERROR_FRAME_HOOK_FUNC pfGetPhyErrorFrame: Ҫע��ĺ���ָ��
*       Output: 
*       Return: OAM3AH_OK:                  ע��ɹ�
*               OAM3AH_ERR_NULL_POINTER     ע��ʧ��(ע�ắ��ΪNULL)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-11    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncGetPhyErrorFrameNumHook(GET_PHY_ERROR_FRAME_HOOK_FUNC pfGetPhyErrorFrame);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncSetLinkEventWinThrshHook
*  Description: ע���·������¼����ں����޲��������亯��
*        Input: SET_LINK_EVENT_WINTHRSH_HOOK_FUNC pfSetEventWinThrsh: Ҫע��ĺ���ָ��
*       Output: 
*       Return: OAM3AH_OK:                  ע��ɹ�
*               OAM3AH_ERR_NULL_POINTER     ע��ʧ��(ע�ắ��ΪNULL)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-11    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncSetLinkEventWinThrshHook(SET_LINK_EVENT_WINTHRSH_HOOK_FUNC pfSetEventWinThrsh);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncLBInputHook
*  Description: ע�ỷ�ر��Ľ��մ�����
*        Input: LBINPUT_HOOK_FUNC pfLBInput:    ע����պ�����ָ��
*               ULONG ulLbLclRmt:               ������Ӧ��/Ӧ��˽��պ���ע��
*                                               0�����ط���˱��Ľ��մ����ӡ�
*                                               1��������Ӧ�˱��Ľ��մ�����
*       Output: 
*       Return: OAM3AH_OK                       �����ɹ�
*               OAM3AH_ERR_PARA                 ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-14    LY(57500)        Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncLBInputHook(LBINPUT_HOOK_FUNC pfLBInput, ULONG ulLbLclRmt);
/*******************************************************************************
*    Func Name: TCPIP_3AH_NotifyCriticalLinkEvent
*  Description: �û�֪ͨ��3AHģ��ͨ���������ϻ�����¼�����ʼ/��ֹ
*        Input: ULONG ulIfIndex:                �ӿ�����
*               ULONG ulCriticalLinkEventType:  ��������;1-��������;2-�����¼�
*               ULONG ulState:                  ����״̬;0-������ֹ;1-���Ϸ���
*       Output: 
*       Return: OAM3AH_OK                       ����ɹ�
*               OAM3AH_ERR_HA_IS_SMOOTHING      ϵͳ����ƽ�����ֶ������׶�
*               3AH_ERR_PARA                    ��������
*               OAM3AH_ERR_IF_NULL              �ӿ�Ϊ��
*               OAM3AH_ERR_IF_INVALID           �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL      �ӿڷǱ���ӿ�
*               OAM3AH_ERR_CB_NOTEXIST          ���ƿ鲻����
*               OAM3AH_ERR_DISABLED             3AHδʹ��
*               OAM3AH_ERR_NO_REGISTER          3AHģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-11    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_NotifyCriticalLinkEvent(ULONG ulIfIndex, ULONG ulCriticalLinkEventType, ULONG ulState);
/*******************************************************************************
*    Func Name: TCPIP_3AH_OccurErroredPeriodEvent
*  Description: ������֡�����¼��������������¼�ʱ��Ʒ���˺���֪ͨVISP
*        Input: ULONG ulIfIndex:                �ӿ�����
*               ULONG ulErroredType:            �¼�����;1=������������¼�;3=��֡�����¼� 
*               DULONG_S stdulWindows:          �¼�����ֵ
*               DULONG_S stdulThreshold:        �¼�����ֵ
*               DULONG_S stdulErrorNum:         ���δ�֡����������
*               DULONG_S stdulErrRunTotal:      �ܴ�֡����������
*       Output: 
*       Return: OAM3AH_OK                       ����ɹ�
*               OAM3AH_ERR_MEMORY               ϵͳ�ڴ治��
*               OAM3AH_ERR                      �����¼������ʧ��
*               OAM3AH_ERR_NO_REGISTER          3AHģ��δע��
*               OAM3AH_ERR_PARA                 ��·�¼���������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-11    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_OccurErroredPeriodEvent(ULONG ulIfIndex, ULONG ulErroredType, DULONG_S stdulWindows,
                                  DULONG_S stdulThreshold, DULONG_S stdulErrorNum, DULONG_S stdulErrRunTotal);
/*******************************************************************************
*    Func Name: TCPIP_3AH_OccurErroredFrameEvent
*  Description: ������֡�¼����֡���¼�ʱ��Ʒ���˺���֪ͨVISP
*        Input: ULONG ulIfIndex:                �ӿ�����
*               ULONG ulErroredType:            �¼�����;2=��֡�¼�;4=��֡���¼� 
*               DULONG_S stdulWindows:          �¼�����ֵ
*               DULONG_S stdulThreshold:        �¼�����ֵ
*               DULONG_S stdulErrorNum:         ���δ�֡���֡����
*               DULONG_S stdulErrRunTotal:      �ܴ�֡���֡����
*       Output: 
*       Return: OAM3AH_OK                       ����ɹ�
*               OAM3AH_ERR_MEMORY               ϵͳ�ڴ治��
*               OAM3AH_ERR                      �����¼������ʧ��
*               OAM3AH_ERR_NO_REGISTER          3AHģ��δע��
*               OAM3AH_ERR_PARA                 ��·�¼���������
*               OAM3AH_ERR_FRAME_ACT            ��֡/��֡��ʵ�ַ�ʽ���ò�֧��
*      Caution: ��֡�ʹ�֡���¼�������VISPʵ��Ҳ�����ɲ�Ʒʵ�֣�����ǲ�Ʒʵ������ô˽ӿ�֪ͨVISP
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-7-26    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_OccurErroredFrameEvent(ULONG ulIfIndex, ULONG ulErroredType, DULONG_S stdulWindows,
                                       DULONG_S stdulThreshold, DULONG_S stdulErrorNum, DULONG_S stdulErrRunTotal);
/*******************************************************************************
*    Func Name: TCPIP_3AH_EventEnable
*  Description: ʹ��ȥʹ��3AH��·�¼������ͨ�湦��
*        Input: ULONG ulIfIndex:        �ӿ�����
*               ULONG ulEventEnable:    �¼�ʹ�ܲ���, 0~127��ʹ�õ���λ�ֱ��ʾ������·�¼������ֹ��ϼ���ʹ��״̬��
*                                       ��Ӧ�¼�λ��1��ʾʹ�ܣ���0��ʾȥʹ�ܡ�
*                                       ��1λ���������������¼���
*                                       ��2λ�����֡�¼���
*                                       ��3λ�����֡�����¼���
*                                       ��4λ�����֡���ۼ��¼���
*                                       ��5λ������·���ϣ�
*                                       ��6λ�����������ϣ�
*                                       ��7λ��������¼�
*       Output: 
*       Return: OAM3AH_OK                       ����ɹ�
*               OAM3AH_ERR_HA_IS_SMOOTHING      3AH��ƽ��������ֶ���������
*               OAM3AH_ERR_PARA                 ������Ч�Դ��� 
*               OAM3AH_ERR_IF_NULL              �ӿ�Ϊ��
*               OAM3AH_ERR_IF_INVALID           �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL      �ӿڷǱ���ӿ�
*               OAM3AH_ERR_MEMORY               �ڴ�ռ䲻��
*               OAM3AH_ERR_NO_REGISTER          3AHģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-11    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_EventEnable(ULONG ulIfIndex, ULONG ulEventEnable);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetErroredWinThres
*  Description: ���� 3AH ����·�¼����ں�����
*        Input: ULONG ulIfIndex:                �ӿ�����
*               ULONG ulLinkEventType:          ��·�¼�����
*                                               1���������������¼�
*                                               2�������֡�¼�
*                                               3�������֡�����¼�
*                                               4����������ۼ��¼�
*               ULONG ulErrWindow:              ���ڣ���λ100ms��
*               ULONG ulErrThres:               ���ޣ���λ������
*       Output: 
*       Return: OAM3AH_OK                       �����ɹ�
*               OAM3AH_ERR_HA_IS_SMOOTHING      ����ƽ��
*               OAM3AH_ERR_PARA                 ��������
*               OAM3AH_ERR_EVENT_WIN            ����ֵ���Ϸ�
*               OAM3AH_ERR_EVENT_THRESH         ����ֵ���Ϸ�
*               OAM3AH_ERR_WIN_THRESH_CONFLICT  ����ֵ������ֵ��ͻ
*               OAM3AH_ERR_IF_NULL              �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID           �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL      �ӿڷǱ���ӿ�
*               OAM3AH_ERR_MEMORY               �ڴ����ʧ��
*               OAM3AH_ERR_NO_REGISTER          3AHģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-11   chenfutian69112         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_SetErroredWinThres(ULONG ulIfIndex, ULONG ulLinkEventType, ULONG ulErrWindow, ULONG ulErrThres);
/*******************************************************************************
*    Func Name: TCPIP_3AH_NpLostLink
*  Description: NP��⵽��·DOWN��֪ͨVISP
*        Input: ULONG ulIfIndex:    �ӿ�����
*       Output: 
*       Return: OAM3AH_OK:              ֪ͨ�ɹ�
*               OAM3AH_ERR_NO_REGISTER  ���δע��
*               OAM3AH_ERR              ��ײ������Ϣ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-15    LY(57500)        Create the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_NpLostLink(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetHaDbg
*  Description: ����HA���Կ���
*        Input: ULONG ulDbg: ���Կ���.1��/0�ر�
*       Output: 
*       Return: VOS_OK/VOS_ERR:���óɹ�/����ʧ��
*               OAM3AH_ERR_NO_REGISTER: ���δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-4-25    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_SetHaDbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetHaDbg
*  Description: ��ȡHA���Կ���
*        Input: ULONG *pulDbg: ������Կ��ص�ULONG����ָ��
*       Output: 
*       Return: VOS_OK/VOS_ERR:��ȡ�ɹ�/��ȡʧ��
*               OAM3AH_ERR_NO_REGISTER: ���δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-4-25    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_GetHaDbg(ULONG *pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_3AH_GetHaStat
*  Description: ��ȡ3AH HAͳ����Ϣ
*        Input: OAM3AH_HASTAT_S *pst3AHHaStat:  �������ͳ����Ϣ���ڴ�ָ��
*       Output: 
*       Return: OAM3AH_OK                       ��ȡ�ɹ�
*               OAM3AH_ERR_NULL_POINTER         ָ���������
*               OAM3AH_ERR_NO_REGISTER          3AHģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-12    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_GetHaStat(OAM3AH_HASTAT_S *pst3AHHaStat);
/*******************************************************************************
*    Func Name: TCPIP_3AH_ClearHaStat
*  Description: ����3AH HAͳ����Ϣ
*        Input: VOID
*       Output: 
*       Return: OAM3AH_OK                       ����ɹ�
*               OAM3AH_ERR_NO_REGISTER          3AHģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-12    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_ClearHaStat(VOID);
/*******************************************************************************
*    Func Name: TCPIP_3AH_StartLbTest
*  Description: ���� 3AH ���ز���
*        Input: ULONG ulIfIndex:            �ӿ�����
*               VOID* pBuffer:              ����ָ��
*               ULONG ulBufLen:             ���ĳ���
*       Output: 
*       Return: OAM3AH_OK                   �ɹ�
*               OAM3AH_ERR_NO_REGISTER      3AHģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   chenfutian69112         Create
*
*******************************************************************************/
ULONG TCPIP_3AH_StartLbTest(ULONG ulIfIndex, VOID* pBuffer, ULONG ulBufLen);
/*******************************************************************************
*    Func Name: TCPIP_3AH_SetBoardState
*  Description: ���ñ��˵�����״̬������ͨ��ORG TLV��Զ�ͨ�汾��״̬
*        Input: ULONG ulIfIndex: �ӿ�����
*               ULONG ulState: 0-ȡ���Զ�ͨ��,1-����Ϊ���ð�,2-����Ϊ���ð�
*       Output: 
*       Return: OAM3AH_OK:                      ���óɹ�
*               OAM3AH_ERR_HA_IS_SMOOTHING      3AH��ƽ��������ֶ���������
*               OAM3AH_ERR_PARA                 ������Ч�Դ���
*               OAM3AH_ERR_IF_NULL              �ӿڲ�����
*               OAM3AH_ERR_IF_INVALID           �ӿ����ʹ���
*               OAM3AH_ERR_PORT_IS_VIRTUAL      �ӿڷǱ���ӿ�
*               OAM3AH_ERR_CB_NOTEXIST          3AH���ÿ��ƿ鲻����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-7-26    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_3AH_SetBoardState(ULONG ulIfIndex, ULONG ulState);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncOrgSpecNotifyHook
*  Description: ��Ʒע�ᴦ����֯�Զ���TLV�����亯��
*        Input: OAM3AH_ORG_SPEC_NOTIFY_HOOK_FUNC pfOrgSpecNotify: ��Ʒ������֯�Զ���TLV�����亯��ָ��
*       Output: 
*       Return: OAM3AH_OK:                  ע��ɹ�
*               OAM3AH_ERR_NULL_POINTER     ע��ʧ��(ע�ắ��ΪNULL)
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-7-28    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncOrgSpecNotifyHook(OAM3AH_ORG_SPEC_NOTIFY_HOOK_FUNC pfOrgSpecNotify);


/*******************************************************************************
*    Func Name: TCPIP_3AH_IoBoardSyncMainBoard
* Date Created: 2008-11-15
*       Author: luowentong105073
*  Description: �ӿڰ�״̬ͬ�������ذ�
*        Input: OAM3AH_WARN_PARAM_S* pstWarn:
*       Output: 
*       Return: OAM3AH_OK:  �ɹ� 
*               ����: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-15   luowentong105073        Create
*
*******************************************************************************/
ULONG TCPIP_3AH_IoBoardSyncMainBoard(OAM3AH_WARN_PARAM_S* pstWarn);


ULONG TCPIP_3AH_Set_NegTimeoutWaring (ULONG ulTime);


ULONG TCPIP_3AH_Get_NegTimeoutWaring (ULONG *pulTime);


ULONG TCPIP_3AH_GetFaultWarnState(ULONG ulIfIndex, OAM3AH_WARN_STATE_S* pst3ahWarnState);


ULONG TCPIP_3AH_SetErroredWinThresEx(ULONG ulIfIndex, ULONG ulLinkEventType, DULONG_S stdulErrWindow, DULONG_S stdulErrThres);


ULONG TCPIP_RegFuncSetLinkEventWinThrshExHook(SET_LINK_EVENT_WINTHRSH_EX_HOOK_FUNC pfSetEventWinThrsh);

/*******************************************************************************
*    Func Name: TCPIP_SetDealPacketWithVlanSwitch
* Date Created: 2012-10-22
*       Author: wangtong207740
*  Description: 
*        Input: ULONG ulSwitch:��VRP_YES ��VRP_NO
*       Output: VOS_OK���óɹ�             
*       Return: ���󷵻ش�����
*      Caution: �������Դ����VLAN��OAMPDU���رղ��ܴ���Ĭ��Ϊ����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-10-22   wangtong207740          Create
*
*******************************************************************************/
ULONG TCPIP_SetDealPacketWithVlanSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetDealPacketWithVlanSwitch
* Date Created: 2012-10-22
*       Author: wangtong207740
*  Description: 
*        Input: 
*       Output: ULONG *pulSwitch:
*       Return: 
*      Caution: ��ȡ����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-10-22   wangtong207740          Create
*
*******************************************************************************/
ULONG TCPIP_GetDealPacketWithVlanSwitch(ULONG *pulSwitch);


#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _3AH_API_H_   */

