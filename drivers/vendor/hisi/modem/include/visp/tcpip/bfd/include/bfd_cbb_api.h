/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_cbb_api.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD API
*  Date Created: 2007-01-06
*        Author: Wangchengyang
*   Description: BFD PAI ���������Լ��ꡢ�ṹ����ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-12-07   Wangchengyang    Create
*
*******************************************************************************/
#ifndef _BFD_CBB_API_H_
#define _BFD_CBB_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BFD_MAX_INTF_NAME_LEN   47
#define BFD_MAX_DESC_NAME_LEN   47
#define BFD_MAX_SESS_NAME_LEN   15
/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-12 */
#define BFD_MAX_VRF_NAME_LEN   31
#define BFD_VRFNAME_LEN          VRF_MAX_VRFNAME_LENGTH
/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-12 */
/* add for BC3D03299 at 2010-05-31 */
#define BFD_VRF_INVALIDINDEX 0xFFFFFFFF
/* END for BC3D03299 at 2010-05-31 */

/*BFD·������APP ID�ֶ�*/
#define BFD_FOR_OSPF_DETECT          0x00000001L
#define BFD_FOR_STATIC_ROUTE_DETECT  0x00000002L

/* BFDЭ��˳����,Ϊ������չ�Կ��ǣ�ÿһbit����һ��Э��һ�������� */
#define BFD_PROCOMPLIANCE_FOR_PF     0x00000001

#define BFD_PROCOMPLIANCE_FOR_RXZERO 0x00000002


/* BFD�����붨������ */
typedef enum tagBFD_ERR_E
{
    BFD_OK                         , /* 0 */
    BFD_ERR                        , /* 1 */
    BFD_ERR_DISABLE                , /* 2 BFDû��ʹ�� */
    BFD_ERR_SESSION_ID             , /* 3 BFD Session ID�Ƿ�,�Ϸ���ΧΪ[1,2000] */
    BFD_ERR_EXIST_SESSION          , /* 4 BFD�Ự�Ѿ����� */
    BFD_ERR_SESSION_FULL           , /* 5 BFD�Ự����,�Ự����Ϊ512 */
    BFD_ERR_SESSION_NOT_EXIST      , /* 6 ָ���Ự������ */
    BFD_ERR_NULL_POINTER           , /* 7 ����ָ��Ϊ�� */
    BFD_ERR_EVENT                  , /* 8 �¼��Ƿ� */
    BFD_ERR_TX_INTERVAL            , /* 9 BFD����ʱ�����Ƿ� */
    BFD_ERR_DETECT_MULT            , /* 10 BFD��ⱶ���Ƿ� */
    BFD_ERR_SESSION_NOT_UP         , /* 11 ��ǰBFD�Ự��Ϊup */
    BFD_ERR_DISABLE_PROCESSING     , /* 12 BFD����ȥʹ�� */
    BFD_ERR_CREATE_TASK            , /* 13 ��������ʧ�� */
    BFD_ERR_CREATE_QUEUE           , /* 14 ��������ʧ�� */
    BFD_ERR_CREATE_TIMER           , /* 15 ������ʱ��ʧ�� */
    BFD_ERR_MEM_ALLOC              , /* 16 �ڴ������� */
    BFD_ERR_INVALID_PARAMETER      , /* 17 ������Ч,һ������0��1���߼���ٵ�ʱ���0��1���� */
    BFD_ERR_NOTIFIER               , /* 18 �ظ�ע�ᣬ��ɾ�������� */
    BFD_ERR_INVALID_ADDR           , /* 19 ��ַ�Ƿ� */
    BFD_ERR_INTF_NOT_EXIST         , /* 20 ָ���ӿڲ����� */
    BFD_ERR_DISMATCH_IP_INDEX      , /* 21 ָ���ӿ������͵�ַ��ƥ�� */
    BFD_ERR_SRC_DST_IP_CONFLICT    , /* 22 �����ỰԴIP��Ϊ�������߶Զ�IPΪ���� */
    BFD_ERR_NP_MODE                , /* 23 ֧��NPģʽ�Ƿ� */
    BFD_ERR_TASK_PRI               , /* 24 BFD�������ȼ��Ƿ� */
    BFD_ERR_DETECT_MODE            , /* 25 ���ģʽ�Ƿ� */
    BFD_ERR_DECODE_BFD_CTRLPKT     , /* 26 ����BFD���ĳ��� */
    BFD_ERR_APP_ID                 , /* 27 BFDӦ��ID�Ƿ� */
    BFD_ERR_BFD_PACKET             , /* 28 BFD����ѡ����� */
    BFD_ERR_PACKET_LEN             , /* 29 ���ĳ��ȷǷ� */
    BFD_ERR_ONE_MULTI_HOP          , /* 30 ���ĵ������Ƿ� */
    BFD_ERR_BUILD_PKT              , /* 31 ��װBFD���Ʊ��ĳ��� */
    BFD_ERR_HA_CREATE_SESSION      , /* 32 ���崴���Ự�Ƿ� */
    BFD_ERR_DEBUG_SWITCH           , /* 33 debug���طǷ� */
    BFD_ERR_HA_IS_SMOOTHING        , /* 34 HA�����ֶ�������ƽ������ */
    BFD_ERR_NOT_INIT               , /* 35 BFD��δ��ʼ�� */
    BFD_ERR_QUE_BUSY               , /* 36 BFD������Ϣ����æ */
    BFD_ERR_WTR                    , /* 37 ���õ�WTR�Ƿ����Ϸ���ΧΪ[0,BFD_MAX_WTR_TIME] */
    BFD_ERR_WRITEQUE_FAIL          , /* 38 д����ʧ��*/
    BFD_ERR_CREATE_OTHERQUEUE      , /* 39 ����OTHER����ʧ�� */
    BFD_ERR_CHECK_PACKET           , /* 40 CHECK BFD���ĳ��� */
    BFD_ERR_ZERODISCR              , /* 41 BFD�����������0���� */
    BFD_ERR_HANDLEPACKET           , /* 42 �����ĳ��� */
    BFD_ERR_PORT                   , /* 43 ���ĵĶ˿ںŴ��� */
    BFD_ERR_CHECKCREATE            , /* 44 SH��鴴��BFD�Ự���� */
    BFD_ERR_CREATESESSION          , /* 45 ����BFD�Ựʧ�� */
    BFD_ERR_RX_INTERVAL            , /* 46 BFD����ʱ�����Ƿ� */
    BFD_ERR_DISMATCH_TRUNK_IP      , /* 47 ָ�����ӿ�Ϊ��Ա�˿ڣ������õı���IP��������trunk��IP */
    BFD_ERR_ONE_HOP_TTL            , /* 48 ��������TTL��Ϊ255 */
    BFD_ERR_GETTRUNK_BYPORT        , /* 49 ͨ����Ա�˿ڻ�ȡtrunk�ӿ�ʧ�� */
    BFD_ERR_TRUNK_MODE_NOMATCH     , /* 50 �û����õ�trunk bfd�Ựģʽ��ƥ�� */
    BFD_ERR_RECR_SESSION           , /* 51 �ظ�����ID��ͬ�ĻỰ */
    BFD_ERR_EXIST_SESSION_NAME     , /* 52 BFD�Ự���Ѿ�����*/
    BFD_ERR_SESSION_NAME_DESC      , /* 53 ���õ�BFD�Ự����������Ϣ�����쳣*/
    BFD_ERR_GET_ENTRY_END          , /* 54 �ѵ����һ������ */
    BFD_ERR_WAITLIST               , /* 55 WaitList���Ʒ����쳣*/
    BFD_ERR_INTF_NOT_L3ETH         , /* 56 ����˿ڲ�֧��BFD */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    BFD_ERR_VRFINDEX               , /* 57 VRF��ƥ�� */
    BFD_ERR_FILTER                 , /* 58 ���������Ƿ� */
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    BFD_ERR_MEM_RELEASE            , /* 59 �ͷ��ڴ����*/
    /*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01, 2009/4/8 */
    BFD_ERR_GET_IPV6VTABLE         , /* 60 ��ȡipv6������ʧ�� */
    BFD_ERR_IPVER_DISMATCH         , /* 61 BFD IP version��ƥ�� */
    BFD_ERR_SOCKET6                , /* 62 BFD6 ����socketʧ�� */
    /* End of Added by wangchengyang-xujun62830-57575, 2009/4/8 */

    /*Add by chenlong168670 for BC3D03565 start*/
    /*63��������ͬ��1.8C03�ģ�1.8C05��ʱδʹ��*/
    BFD_ERR_SESSION_FOR_OSPF_OR_STATIC  , /* 63 BFD�Ự��OSPF���߾�̬·������������ɾ�� */
    BFD_ERR_SESSION_NAME                , /* 64  ����ĻỰ����*/
    /*Add by chenlong168670 for BC3D03565 end*/

    /* BFD license���ܴ����� --- start */
    BFD_ERR_LICENSE_WRONG_PARA     , /* 65 �û������������ȷ */
    BFD_ERR_LICENSE_IS_OFF         , /* 66 BFD License��ͨ�� */
    BFD_ERR_LICENSE_CLOSE_MRCV     , /* 67 �������Ľ���socket�ر�ʧ�� */
    BFD_ERR_LICENSE_CLOSE_ORCV     , /* 68 �������Ľ���socket�ر�ʧ�� */
    BFD_ERR_LICENSE_CLOSE_SND      , /* 69 ���ķ���socket�ر�ʧ�� */
    BFD_ERR_LICENSE_GET_PRECFG     , /* 70 ��ȡBFD6Ԥ����ʧ�� */
    BFD_ERR_LICENSE_BFD6_DISABLE   , /* 71 BFD6����û��ʹ�� */
    BFD_ERR_LICENSE_DISABLE_PROC   , /* 72 BFD License���ڹر���*/
    BFD_ERR_LICENSE_NOT_ENABLE     , /* 73 BFD License���ڴ�״̬ */
    BFD_ERR_LICENSE_ENABLE         , /* 74 BFD License������ʹ���л���ʹ�� */
    BFD_ERR_LICENSE_PROCING        , /* 75 BFD License�����ڲ����� */
    /* BFD license���ܴ����� ---  end  */
    BFD_ERR_GR_STATE               , /* 76 BFD GR״̬���� */
    BFD_ERR_NO_NP                  , /* 77 û��ע��NP�·��Ĺ��Ӻ��� */
    /*Begin BC3D02903 liangjicheng 2010-04-19 */
    BFD_ERR_CREATE_EXTQUEUE        , /* 78 ����OTHER����ʧ�� */
    /*End   BC3D02903 liangjicheng 2010-04-19 */

    BFD_ERR_SESSION_CONFLICT,               /* 79 �����ľ�̬�Ự��̬�Ự��ͻ */

    BFD_ERR_DISABLE_WHEN_DELSES = 88,       /*88 BFDû��ʹ�� */
    BFD_ERR_HA_IS_SMOOTHING_WHEN_DELSES,    /*89 BFD����ƽ�������� */
    BFD_ERR_SESSION_ID_WHEN_DELSES,         /*90 BFD�ỰID���� */
    BFD_ERR_VRFINDEX_WHEN_DELSES,           /*91 VRF ID���� */
    BFD_ERR_SESSION_NOT_EXIST_WHEN_DELSES,  /*92 BFD�Ự������ */
    BFD_ERR_MEM_ALLOC_VRFSESSENTY_ININIT,   /*93 BFD��ʼ��ʱ����BFD�Ựȫ�ֱ�����ڴ�ʧ�� */
    BFD_ERR_MEM_ALLOC_GDBGSWTICH_ININIT,    /*94 BFD��ʼ��ʱ����ȫ��debug�����ڴ�ʧ�� */
    BFD_ERR_MEM_ALLOC_DISABLEONEVRF_ININIT, /*95 BFD��ʼ��ʱ����ȥʹ�����л򵥸�VRF��BFD�ı�־�ڴ�ʧ�� */
    BFD_ERR_PROTOCOL,                       /*96 BFD�Ự����ʱ�����Э�����ʹ��� */
    BFD_ERR_NOT_SUPORT_RFC_DEMANDMODE,      /*97 ������BFD����RFC�ĻỰĿǰ��֧�ֲ�ѯģʽ */
    BFD_ERR_MEM_ALLOC_SESSENTY_INIT,        /*98 BFD��ʼ��ʱ����BFD���ڴ�ʧ�� */
    BFD_ERR_NO_CREATE_PACKET,               /*99 �Ự���汨��û������ */
    BFD_ERR_DETECTTIME_ZORE,                /*100 ̽��ʱ��Ϊ0���г���Σ��*/

    BFD_ERR_NSR_WRONG_STATE,                /*101 NSR��ǰ״̬��������ز��� */
    BFD_ERR_NSR_NO_ENABLE,                  /*102 NSR����δʹ��*/
    BFD_ERR_NSR_NULL_PPI_HOOK,              /*103 NSR����δע��*/
    BFD_ERR_NSR_CREATE_NSRQUEUE,            /*104 ����OTHER����ʧ�� */
    BFD_ERR_NSR_UNFINISHED,                 /*105 NSR����û�н���*/
    BFD_ERR_NSR_SESSION_ACTIVE,             /*106 NSR�����м���Ự*/
    BFD_ERR_NSR_ALLOC_BAKCACHE,             /*107 BFD NSR��ʼ��ʱ�����ű������ݵ��ڴ�ʧ��*/
    BFD_ERR_NSR_ALLOC_SESSENTY_INIT,        /*108 BFD NSR��ʼ��ʱ���䱸�ݵ�BFD���ڴ�ʧ��*/
    BFD_ERR_NSR_ALLOC_VRFSESSENTY_ININIT,   /*109 BFD NSR��ʼ��ʱ���䱸�ݵ�BFD�Ựȫ�ֱ�����ڴ�ʧ��*/
    BFD_ERR_NSR_BAKDATA_OVERFLOW,           /*110 BFD NSR��Ʒ�ϱ��������ݳ������*/
    BFD_ERR_NSR_INVAILD_DSTPORT,            /*111 BFD NSR�ָ������У����Ŀ�Ķ˿ڴ���*/

    BFD_ERR_PORT_IS_OFF,                    /*112 BFD����Ҫ���Ⱪ¶�˿�3784��4784*/
    BFD_ERR_MAX                             /*���������ֵ,�Ժ���Ӵ������밴˳����ӵ���ǰ */
}BFD_ERR_E;

/* �Ự��Ϣ���ݽṹ */
typedef struct tagBFD_SESSION_INFO_S
{
    ULONG ulSessionID;        /* �ỰID */
    ULONG ulSessionState;     /* �Ự״̬ 0:AdminDown 1:Down 2:Init 3:Up  */
    ULONG ulCfgDetectMode;    /* �û����õı���̽��ģʽ��1:��ѯģʽ 2:�첽ģʽ */
    ULONG ulCfgMinTxInterval; /* �û����õı��˷��ͼ������λ:ms */
    ULONG ulCfgMinRxInterval; /* �û����õı��˽��ռ������λ:ms */
    ULONG ulCfgDetectMult;    /* �û����õı���̽�ⱶ����ȡֵ��Χ3~10 */
    ULONG ulActDetectMode;    /* Э����Ч��̽��ģʽ��1:��ѯģʽ 2:�첽ģʽ */
    ULONG ulActTxInterval;    /* Э����Ч�ı��˷��ͼ������λ:ms */
    ULONG ulActRxInterval;    /* Э����Ч�ı��˷��ͼ������λ:ms */
    ULONG ulDetectTime;       /* Э����Ч�ı���̽��ʱ�䣬��λ:ms */
    ULONG ulMyDiscriminator;  /* ���������� */
    ULONG ulYourDiscriminator;/* �Զ˶������� */
    ULONG ulDstIPAddress;     /* �Ự��Ŀ�ĵ�ַ�������� */
    ULONG ulSrcIPAddress;     /* �Ự��Դ��ַ�������� */
    ULONG ulIsMultiHop;       /* �Ự�Ƿ��Ƕ�����0:���� 1:�� */
    ULONG ulSentPakcets;      /* �Ự���͵ı����ܸ��� */
    ULONG ulRcvPackets;       /* �Ự���յı����ܸ��� */
    ULONG ulLastSentTime;     /* ��һ�����ķ��͵�ʱ�䣬ͨ��VOS_Tm_Now��ȡ�ĵ�32λ����λ:ms */
    ULONG ulAppId;            /* �Ự�趨��Ӧ����� */
    ULONG ulUpToDown;         /* �Ự�Դ���֮��״̬��Up��Down���ܴ��� */
    ULONG ulDiagnostic;       /* �Ự�������(0-9)�������9�������յ��˶Զ˵�AdminDown���ģ�0-8�μ�RFC�ݰ� */
    ULONG ulSessIfIndex;
    UCHAR ucTos;              /* bfd�Ựtos */
    UCHAR Padding[3];
    ULONG ulCurrentGRState;  /* ��BFD�Ự��ǰ��GR״̬, ȡֵ��enumBFD_GR_STATE */
    ULONG ulBfdProtocol;      /* bfd�ỰЭ������ */
    ULONG ulRemoteMri;        /* �Զ˱�����RequiredMinRxIntervalֵ */
    ULONG ulRemoteDemandMode; /* �Զ˱�����Demandֵ,1:��ѯģʽ��0:�ǲ�ѯģʽ(�첽ģʽ) */
}BFD_SESSION_INFO_S;

/* wangjiaqi modify for ipv6 bfd 20131114 begin */
typedef struct tagBFD6_SESSION_INFO_S
{
    ULONG ulSessionID;        /* �ỰID */
    ULONG ulSessionState;     /* �Ự״̬ 0:AdminDown 1:Down 2:Init 3:Up  */
    ULONG ulCfgDetectMode;    /* �û����õı���̽��ģʽ��1:��ѯģʽ 2:�첽ģʽ */
    ULONG ulCfgMinTxInterval; /* �û����õı��˷��ͼ������λ:ms */
    ULONG ulCfgMinRxInterval; /* �û����õı��˽��ռ������λ:ms */
    ULONG ulCfgDetectMult;    /* �û����õı���̽�ⱶ����ȡֵ��Χ3~10 */
    ULONG ulActDetectMode;    /* Э����Ч��̽��ģʽ��1:��ѯģʽ 2:�첽ģʽ */
    ULONG ulActTxInterval;    /* Э����Ч�ı��˷��ͼ������λ:ms */
    ULONG ulActRxInterval;    /* Э����Ч�ı��˷��ͼ������λ:ms */
    ULONG ulDetectTime;       /* Э����Ч�ı���̽��ʱ�䣬��λ:ms */
    ULONG ulMyDiscriminator;  /* ���������� */
    ULONG ulYourDiscriminator;/* �Զ˶������� */
    ULONG ulDstIPAddress[4];     /* �Ự��Ŀ�ĵ�ַ�������� */
    ULONG ulSrcIPAddress[4];     /* �Ự��Դ��ַ�������� */
    ULONG ulIsMultiHop;       /* �Ự�Ƿ��Ƕ�����0:���� 1:�� */
    ULONG ulSentPakcets;      /* �Ự���͵ı����ܸ��� */
    ULONG ulRcvPackets;       /* �Ự���յı����ܸ��� */
    ULONG ulLastSentTime;     /* ��һ�����ķ��͵�ʱ�䣬ͨ��VOS_Tm_Now��ȡ�ĵ�32λ����λ:ms */
    ULONG ulAppId;            /* �Ự�趨��Ӧ����� */
    ULONG ulUpToDown;         /* �Ự�Դ���֮��״̬��Up��Down���ܴ��� */
    ULONG ulDiagnostic;       /* �Ự�������(0-9)�������9�������յ��˶Զ˵�AdminDown���ģ�0-8�μ�RFC�ݰ� */
    ULONG ulSessIfIndex;
    UCHAR ucTos;              /* bfd�Ựtos */
    UCHAR Padding[3];
    ULONG ulCurrentGRState;  /* ��BFD�Ự��ǰ��GR״̬, ȡֵ��enumBFD_GR_STATE */
    ULONG ulBfdProtocol;      /* bfd�ỰЭ������ */
    ULONG ulRemoteMri;        /* �Զ˱�����RequiredMinRxIntervalֵ */
    ULONG ulRemoteDemandMode; /* �Զ˱�����Demandֵ,1:��ѯģʽ��0:�ǲ�ѯģʽ(�첽ģʽ) */
}BFD6_SESSION_INFO_S;
/* wangjiaqi modify for ipv6 bfd end */
/* ���ģʽ���� */
typedef enum tagBFD_API_DETECT_MODE_E
{
    BFD_DETECT_MODE_DEMAND = 0x1,          /* ��ѯģʽ */
    BFD_DETECT_MODE_ASYNC,                 /* �첽ģʽ*/
    BFD_DETECT_MODE_API_MAX
}BFD_API_DETECT_MODE_E;

/* BFD����ǿ�Ʋ������ݽṹ */
typedef struct tagBFD_PACKET_S
{
#if ( VRP_BIG_ENDIAN == VRP_YES )
    UCHAR   bVers                   : 3 ;       /* BFD�İ汾��Ϣ */
    UCHAR   bDiagnostic             : 5 ;       /* BFD�������Ϣ */
#else
    UCHAR   bDiagnostic             : 5 ;       /* BFD�������Ϣ */
    UCHAR   bVers                   : 3 ;       /* BFD�İ汾��Ϣ */
#endif
#if ( VRP_BIG_ENDIAN == VRP_YES )
    UCHAR   bState                  : 2 ;       /* BFD��״̬��Ϣ */
    UCHAR   bPollFlag               : 1 ;       /* BFD����ѯ��־ */
    UCHAR   bFinalFlag              : 1 ;       /* BFD����ѯ��Ӧ��־ */
    UCHAR   bControlPlanFlag        : 1 ;       /* BFD�Ϳ���ƽ�湲��ı�־ */
    UCHAR   bAuthenticationFlag     : 1 ;       /* BFD����֤��־ */
    UCHAR   bDemandModeFlag         : 1 ;       /* BFD�Ĳ�ѯ��ʽ��־ */
    UCHAR   bReserved               : 1 ;       /* BFD�ı���λ */
#else
    UCHAR   bReserved               : 1 ;       /* BFD�ı���λ */
    UCHAR   bDemandModeFlag         : 1 ;       /* BFD�Ĳ�ѯ��ʽ��־ */
    UCHAR   bAuthenticationFlag     : 1 ;       /* BFD����֤��־ */
    UCHAR   bControlPlanFlag        : 1 ;       /* BFD�Ϳ���ƽ�湲��ı�־ */
    UCHAR   bFinalFlag              : 1 ;       /* BFD����ѯ��Ӧ��־ */
    UCHAR   bPollFlag               : 1 ;       /* BFD����ѯ��־ */
    UCHAR   bState                  : 2 ;       /* BFD��״̬��Ϣ */
#endif
    UCHAR   ucDetectMult                ;       /* BFD�ļ�ⱶ�� */
    UCHAR   ucPacketLength              ;       /* BFD�ı��ĳ��� */
    ULONG   ulLocalDiscriminitor        ;       /* BFD�ı��ر�ʶ�� */
    ULONG   ulRemoteDiscriminitor       ;       /* BFD�ĶԶ˱�ʶ�� */
    ULONG   ulDesiredMinTxInterval      ;       /* BFD�����ķ��ͼ�� */
    ULONG   ulRequiredMinRxInterval     ;       /* BFD�ı��ؽ������� */
    ULONG   ulRequiredMinEchoRxInterval ;       /* BFD�������ܵķ��ͼ�� */
} BFD_PACKET_S;

/* �Ự���²������ݽṹ */
typedef struct tagBFD_SESSION_PARA_S
{
    ULONG ulDetectMode;      /* �Ự���ģʽ:1��ѯģʽ;2�첽ģʽ */
    ULONG ulMinTxInterval;   /* ms,��С����ʱ������10~1000ms */
    ULONG ulMinRxInterval;   /* ms,��С����ʱ������10~1000ms */
    ULONG ulDetectMult;      /* ��ⱶ����3~50 */
}BFD_SESSION_PARA_S;

/* BFDȫ����Ϣ */
typedef struct tagBFD_GLOBAL_INFO
{
    ULONG ulBfdGlobalCapability  ;   /* BFDȫ��ʹ��״̬ */
    ULONG ulWtrTimeInterval      ;   /* BFDȫ��WTRʱ��������λ:s */
    ULONG ulAdaptMultiHopPort    ;   /* �Ƿ�����BFD�����Զ������˿ں� */
    /*Added by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/4/8 */
    ULONG ulFirstNegoTimes       ;   /* �״�Э�̴��� */
    /* End of Added by wangchengyang-xujun62830-57575, 2009/4/8 */
    ULONG ulCurrentBFDGRState    ;   /* ��ǰ��BFD GR״̬, ȡֵ��enumBFD_GR_STATE */
    /*Modified by xujun57575 for sgsn Requirement  BC3D02728, 2010/2/25 */
    ULONG ulDetectTime           ;
    ULONG ulDetectFlag           ;
    /*End of Modified by xujun57575, 2010/2/25 */
    /* wangjiaqi modify for ipv6 bfd 20131119 begin */
    ULONG ulAutoDiscrGate        ;   /*�Զ�����ỰId������*/
    ULONG ulBfd6AutoDiscrGate    ;   /*�Զ�����ỰId������*/    
    ULONG ulBfd6WtrTimeInterval;      /*BFD DOWN����һ��Э�̵��ӳ�ʱ��*/
    ULONG ulBfd6GlobalCapability;    /*BFD6 ȫ�ֿ���*/
    ULONG ulBfd6AdaptMultiHopPort;   /*BFD6 �����Ƿ�ͶԶ�����Ӧ*/    
    /* wangjiaqi modify for ipv6 bfd end */    
} BFD_GLOBAL_INFO_S;

/* BFD�Ự��ѯ������Ϣ���ݽṹ */
typedef struct tagBFD_SESSION_FILTER_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    ULONG ulPeerAddr;
    ULONG ulLocalDiscr;
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    ULONG ulIsAllVRF;   /* Ϊ1��ʾ�����е�VRF�н��в���,Ϊ0��ʾ��ָ����VRF�н��в��� */
}BFD_SESSION_FILTER_S;

/* BFD�Ựͳ����Ϣ���ݽṹ */
typedef struct tagBFD_SESSION_COUNT_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulSessionId;
    ULONG ulLocalDiscr;
    ULONG ulRemoteDiscr;
    USHORT usSessState;
    USHORT usIsMultiHop;
    ULONG ulPktRcv;
    ULONG ulPktSend;
    ULONG ulPktRcvDrop;
    ULONG ulPktSendErr;
    ULONG ulSessionDownNum;
    ULONG ulSessionStateTime;
    ULONG ulLastDownTime;
    /* mody for BC3D03299 at 2010-05-31 */
    ULONG ulVrfIndex;
    ULONG ulPeerAddr[4];
    /* end mody for BC3D03299 at 2010-05-31 */
}BFD_SESSION_COUNT_S;

/* BFD�Ự������Ϣ���ݽṹ */
typedef struct tagBFD_SESSION_CONFIG_INFO_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr;
    ULONG ulPeerAddr;
    ULONG ulDetectMult;
    ULONG ulMinTxInterval;
    ULONG ulMinRxInterval;
    ULONG ulOutIndex;
    ULONG ulAppId;
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    UCHAR ucTos;              /* bfd�Ựtos */
    UCHAR Padding[3];
    ULONG ulRemoteDiscr;
}BFD_SESSION_CONFIG_INFO_S;

/* BFD�Ự��Ϣ���ݽṹ */
typedef struct tagBFD_SESSION_ALL_INFO_S {
    BFD_SESSION_CONFIG_INFO_S stConfigInfo;
    ULONG ulRemoteDiscr;
    ULONG ulSessionId;
    USHORT usSessState;
    USHORT usIsMultiHop;
    ULONG ulActTxInterval;
    ULONG ulActRxInterval;
    /*Add for BC3D00792,DR.177 ����Զ�ʵ�ʼ�ⱶ�� */
    ULONG ulActDetectMult;
    ULONG ulActDetectTime;
    USHORT usLocalDiag;
    USHORT usDstPort; /* �ỰĿ�Ķ˿ں�(������) */
    ULONG ulRemoteMinTxInterval; /* �Զ˵�MTI */
    ULONG ulRemoteMinRxInterval; /* �Զ˵�MRI */
    USHORT usRemoteDemandMode;   /* �Զ˵ļ��ģʽ */
    UCHAR  ucRemoteDetectMult;   /* �Զ˵ļ�ⱶ�� */
    UCHAR  ucRec;
}BFD_SESSION_ALL_INFO_S;

/*Added by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/4/8 */
/* BFD6�Ự��ѯ������Ϣ���ݽṹ */
typedef struct tagBFD6_SESSION_FILTER_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    ULONG ulPeerAddr[4];
    ULONG ulLocalDiscr;
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* wangjiaqi modify for ipv6 bfd 20131114 begin */
    ULONG ulIsAllVRF;   /* Ϊ1��ʾ�����е�VRF�н��в���,Ϊ0��ʾ��ָ����VRF�н��в��� */    
    /* wangjiaqi modify for ipv6 bfd end */    
}BFD6_SESSION_FILTER_S;

/* BFD6�Ự������Ϣ���ݽṹ */
typedef struct tagBFD6_SESSION_CONFIG_INFO_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr[4];
    ULONG ulPeerAddr[4];
    ULONG ulDetectMult;
    ULONG ulMinTxInterval;
    ULONG ulMinRxInterval;
    ULONG ulOutIndex;
    ULONG ulAppId;
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* wangjiaqi modify for ipv6 bfd 20131114 begin */
    UCHAR ucTos;          /* bfd�Ựtos���ݲ�֧��*/
    UCHAR Padding[3];     /*����ֶ�*/
    ULONG ulRemoteDiscr;     /*�Զ˵�������*/    
    /* wangjiaqi modify for ipv6 bfd end */    
}BFD6_SESSION_CONFIG_INFO_S;

/* BFD6�Ự��Ϣ���ݽṹ */
typedef struct tagBFD6_SESSION_ALL_INFO_S {
    BFD6_SESSION_CONFIG_INFO_S stConfigInfo;
    ULONG ulRemoteDiscr;
    ULONG ulSessionId;
    USHORT usSessState;
    USHORT usIsMultiHop;
    ULONG ulActTxInterval;
    ULONG ulActRxInterval;
    ULONG ulActDetectMult;
    ULONG ulActDetectTime;
    USHORT usLocalDiag;
    /* wangjiaqi modify for ipv6 bfd 20131114 begin */
    USHORT usRemoteDemandMode;   /* �Զ˵ļ��ģʽ */
    ULONG ulRemoteMinTxInterval; /* �Զ˵�MTI */
    ULONG ulRemoteMinRxInterval; /* �Զ˵�MRI */
    UCHAR  ucRemoteDetectMult;   /* �Զ˵ļ�ⱶ�� */
    UCHAR  ucReserve[1];         /* ����ֶ� */
    USHORT usDstPort;            /* �ỰĿ�Ķ˿ں�(������) */
    /* wangjiaqi modify for ipv6 bfd end */
}BFD6_SESSION_ALL_INFO_S;
/* End of Added by wangchengyang-xujun62830-57575, 2009/4/8 */

/* BFD�Ự��Ҫ��Ϣ���ݽṹ */
typedef struct tagBFD_SESSION_BRIEF_INFO_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulSessionId;
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
}BFD_SESSION_BRIEF_INFO_S;
/* wangjiaqi modify for ipv6 bfd 20131119 begin */
typedef struct tagBfdStatistic
{
    UCHAR ucIpVer;           /*IPv4 ����IPv6*/
    ULONG ulSrcAddr[4];      /*BFD�Ự��Դ��ַ��������*/
    ULONG ulPeerAddr[4];     /*BFD�Ự��Ŀ�ĵ�ַ��������*/
    /* Э��ͳ����Ϣ  ����*/
    ULONG ulBfdRcvDown;      /*���յ�DOWN����*/
    ULONG ulBfdRcvInit;      /*���յ�Init����*/
    ULONG ulBfdRcvUp;        /*���յ�Up����*/
    ULONG ulBfdRcvAdminDown; /*���յ�AdminDown����*/
    ULONG ulBfdRcvErr;       /*���յĴ�����*/
    ULONG ulBfdRcvP;         /*���յ�P����*/
    ULONG ulBfdRcvF;         /*���յ�F����*/

    /* Э��ͳ����Ϣ  ����*/
    ULONG ulBfdSndDown;      /*���͵�DOWN����*/
    ULONG ulBfdSndInit;      /*���͵�Init����*/
    ULONG ulBfdSndUp;        /*���͵�Up����*/
    ULONG ulBfdSndAdminDown; /*���͵�AdminDown����*/
    ULONG ulBfdSndErr;       /*���յĴ�����*/    
    ULONG ulBfdSndP;         /*���͵�P����*/
    ULONG ulBfdSndF;         /*���͵�F����*/
} BFD_STATISTIC_S;
/* wangjiaqi modify for ipv6 bfd end */

/* BFD����������ֶ� */
typedef enum tagBFD_DIAG_E
{
    BFD_DIAG_NONE      = 0               ,       /* ������� */
    BFD_DIAG_DETECT_DOWN                 ,       /* ���ʱ��DOWN */
    BFD_DIAG_ECHO_DOWN                   ,       /* �������DOWN */
    BFD_DIAG_NEIGHBOR_DOWN               ,       /* �ھ�ͨ��DOWN */
    BFD_DIAG_FORWARDING_RESET            ,       /* ת��ƽ������ */
    BFD_DIAG_PATH_DOWN                   ,       /* ·��DOWN */
    BFD_DIAG_CONCAT_PATH_DOWN            ,       /* ����·��DOWN */
    BFD_DIAG_ADMIN_DOWN                  ,       /* ����DOWN */
    BFD_DIAG_REVERSE_CONCAT_PATH_DOWN    ,       /* ������·��DOWN */
    BFD_DIAG_RECEIVE_ADMIN_DOWN          ,       /* Receive admindown packet ,note : not define in the protocol */
    BFD_DIAG_MAX                                 /* �����Чֵ */
} BFD_DIAG_E ;

/* BFD�Ự״̬ */
/* CAUTION: if modify state define, pls update g_aszSessionState */
typedef enum tagBFD_STATE_E
{
    BFD_STATE_ADMIN_DOWN  = 0            ,      /* ����DOWN״̬ */
    BFD_STATE_DOWN                       ,      /* DOWN״̬ */
    BFD_STATE_INIT                       ,      /* INIT״̬ */
    BFD_STATE_UP                         ,      /* UP״̬ */
    BFD_STATE_MAX                               /* �Ự����Ч״̬ */
} BFD_STATE_E ;

/* �ⲿ֪ͨ��ַ��ɾ�¼� ��BFD_IpAddrEventNotify��*/
typedef enum tagBFD_EVENT_E
{
    BFD_IPCHANGE_ADD_EVENT  = 0,                /* ���ӵ�ַ */
    BFD_IPCHANGE_DEL_EVENT,                     /* ɾ����ַ */
    BFD_TRUNKPORT_ADD_EVENT,                    /* �ӿڼ��뵽trunk�� */
    BFD_TRUNKPORT_REMOVE_EVENT,                 /* �ӿڴ�trunk���Ƴ� */
    BFD_EVENT_MAX
} BFD_EVENT_E ;

typedef enum tagBFD_NSR_MSG_E
{
    BFD_NSR_MSG_SESSINFO = 0    ,                 /* �ϱ�BFD4�Ự��Ϣ */
    BFD_NSR_MSG_RESUME_FINISH   ,                 /* �ײ��ϱ��Ự��� */
    BFD_NSR_MSG_ALLSESS_DELETE  ,                 /* ֪ͨ���������б�����Ϣɾ����� */
    BFD6_NSR_MSG_SESSINFO       ,                 /* �ϱ�BFD6�Ự��Ϣ */
    BFD_NSR_MSG_MAX             ,      
} BFD_NSR_MSG_E ;

typedef struct tagBFD_NSR_GLOBAL_INFO
{
    ULONG ulBfdNsrState;                    /* BFD NSR��ǰ״̬ */
    ULONG ulSessNumBeforeNSR;               /* ����NSR����ǰ��BFD�Ự����*/
    ULONG ulResumeSessNum;                  /* ת�����ϱ��ĻỰ����*/
    ULONG ulAddSessNum;                     /* NSR����������add�ĻỰ��*/
    ULONG ulDelSessNum;                     /* NSR����������delete�ĻỰ��*/
    ULONG ulPPICreateSessNum;               /* PPI�·� create �ĻỰ��*/
    ULONG ulPPIDelSessNum;                  /* PPI�·� delete �ĻỰ��*/
    ULONG ulPPIDownSessNum;                 /* PPI�·� down �ĻỰ��*/
    ULONG ulPPIUpSessNum;                   /* PPI�·� up �ĻỰ��*/
    ULONG ulRcvAdmindownNum;                /* NSR�������յ�admindown���ĵĻỰ��*/
    ULONG ulAdmindownNum;                   /* NSR����������admindown�ĻỰ��*/
    ULONG ulTimeOut;                        /* NSR�����Ƿ�ʱ*/
}BFD_NSR_GLOBAL_INFO_S;

typedef struct tagBFD_NSR_SESS_INFO
{
    ULONG   ulSessId;                                   /* �ỰID */
    ULONG   ulVrfIndex;                                 /* VRF���� */
    ULONG   ulBfdNsrNpDiag;                             /* NP�ϱ������ */
    USHORT  usBfdNsrNpSessState;                        /* NP�ϱ��Ự״̬ */
    USHORT  usStateResultInSmooth;                      /*ƽ����Ự״̬*/
    UCHAR   ucRcvAdmindown;                             /* nsr�������յ�admin down����*/
    UCHAR   ucCfgAdmindown;                             /* nsr����������admin down*/
    UCHAR   ucBfdNsrPPIFlag;                            /* nsr������PPI�·�*/
    UCHAR   ucPad[1];
}BFD_NSR_SESS_INFO_S;

typedef struct tagBFD6_NSR_SESS_INFO
{
    ULONG   ulSessId;                                   /* �ỰID */
    ULONG   ulVrfIndex;                                 /* VRF���� */
    ULONG   ulBfdNsrNpDiag;                             /* NP�ϱ������ */
    USHORT  usBfdNsrNpSessState;                        /* NP�ϱ��Ự״̬ */
    USHORT  usStateResultInSmooth;                      /*ƽ����Ự״̬*/
    UCHAR   ucRcvAdmindown;                             /* nsr�������յ�admin down����*/
    UCHAR   ucCfgAdmindown;                             /* nsr����������admin down*/
    UCHAR   ucBfdNsrPPIFlag;                            /* nsr������PPI�·�*/
    UCHAR   ucPad[1];
}BFD6_NSR_SESS_INFO_S;

/* ϵͳ�Ƿ�֧��NP */
#define BFD_NP_NOT_SUPPORT             0            /* ��֧��NP */
#define BFD_NP_HALF_SUPPORT            1            /* ֧����NP,�������,NP���� */
#define BFD_NP_SUPPROT                 2            /* ֧��ȫNP,NP���ͽ��� */

/* ���Կ������� */
#define BFD_DEBUG_STATE                0x1          /* BFD״̬��Ǩ���� */
#define BFD_DEBUG_INPUT                0x2          /* ���յ�BFD���ĵ��� */
#define BFD_DEBUG_OUTPUT               0x4          /* ���͵�BFD���ĵ��� */
#define BFD_DEBUG_GR                   0x8          /* GR���� */
#define BFD_DEBUG_NSR                  0x10         /* NSR����*/

#define BFD_DEBUG_BITSWITCH            5            /* BFD���Կ���ֻ�õ�λ */

/* �����е��� */
#define BFD_DEBUG_ALLTYPE              (BFD_DEBUG_STATE|BFD_DEBUG_INPUT|BFD_DEBUG_OUTPUT)

#define BFD_LEN_AUTH_NONE              24           /* �����κ���֤��BFD���Ʊ��ĳ��� */

/* ��NP�·��������ݽṹ */
typedef struct tagBFD_PPI_S
{
    CHAR szCtlPkt[BFD_LEN_AUTH_NONE]; /* �Ự��BFD���Ʊ���,������,ֵΪ�û�����ֵ */

    ULONG ulDetectMode;             /* ����ʵ�ʵļ��ģʽ */
    ULONG ulTxInterval;             /* ����ʵ�ʵķ���ʱ����,ms */
    ULONG ulDetectInterval;         /* ����ʵ�ʵļ����,ms */
    ULONG ulDetectMult;             /* ����ʵ�ʵļ�ⱶ�� */
    ULONG ulMyDiscriminator;        /* ���˱�ʶ�� */
    ULONG ulYourDiscriminator;      /* �Զ˱�ʶ�� */

    ULONG ulDstIPAddress;           /* �Զ˵�ַ,Big Endian */
    ULONG ulSrcIPAddress;           /* ���˵�ַ,Big Endian */
    ULONG ulTTL;                    /* TTL */
    ULONG ulDstUdpPort;             /* UDPĿ�Ķ˿ں�,����Ϊ3784,����Ϊ4784 */
    ULONG ulSrcUdpPort;             /* UDPԴ�˿ں�,ֵΪ49151+X(X>0) */
    ULONG ulTos;                    /* TOSֵ */
    ULONG ulIfIndex;                /* �Ự�ĳ��ӿ�����(����ʱΪ0) */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    ULONG ulVrfIndex;               /* �Ự���ڵ�VRF */
    /* ENd:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    ULONG ulIfType;                 /* ���ӿ�����, ȡֵ��enumIFTYPE */
    ULONG ulIfNum;                  /* ���ӿڵ�ͨ���� */
    USHORT usReserved;              /* �������� */
    USHORT usCksum;                 /* ����PPI�ṹ���У��� */
    ULONG ulDiagnostic;             /* �·���ǰ�Ự����� */
}BFD_PPI_S;

/*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01, 2009/4/8 */
typedef struct tagBFD6_PPI_S
{
    CHAR szCtlPkt[BFD_LEN_AUTH_NONE]; /* �Ự��BFD���Ʊ���,������,ֵΪ�û�����ֵ */

    ULONG ulDetectMode;             /* ʵ�ʵļ��ģʽ */
    ULONG ulTxInterval;             /* ����ʵ�ʵķ���ʱ����,ms */
    ULONG ulDetectInterval;         /* ����ʵ�ʵļ����,ms */
    ULONG ulDetectMult;             /* ����ʵ�ʵļ�ⱶ�� */
    ULONG ulMyDiscriminator;        /* ���˱�ʶ�� */
    ULONG ulYourDiscriminator;      /* �Զ˱�ʶ�� */

    ULONG ulDstIPAddress[4];        /* �Զ˵�ַ,������ */
    ULONG ulSrcIPAddress[4];        /* ���˵�ַ,������ */
    ULONG ulHopLimit;               /* Hop Limit */
    ULONG ulDstUdpPort;             /* UDPĿ�Ķ˿ں�,����Ϊ3784,����Ϊ4784 */
    ULONG ulSrcUdpPort;             /* UDPԴ�˿ں�,ֵΪ49151+X(X>0) */
    ULONG ulTclass;                 /* Traffic classֵ */
    ULONG ulIfIndex;                /* �Ự�ĳ��ӿ�����(����ʱΪ0) */
    ULONG ulVrfIndex;               /* �Ự���ڵ�VRF */
    ULONG ulSessionId;              /* �ỰID */
    ULONG ulDiagnostic;             /* �·���ǰ�Ự����� */
}BFD6_PPI_S;
/* End of Added by wangchengyang-xujun62830-57575, 2009/4/8 */

/* PPI Msg Type */
/* �޸ĸýṹʱ��ͬ���޸�bfd_ppi.c��BFD_PPI_OprType_En */
typedef enum tagPPI_MSG_TYPE_E
{
    BFD_PPI_SESSION_CREATE        = 1              ,         /* �����Ự */
    BFD_PPI_SESSION_REFRESH                        ,         /* ���»Ự */
    BFD_PPI_SESSION_DELETE                         ,         /* ɾ���Ự */
    BFD_PPI_START_SEND_SEQUENCE                    ,         /* ֪ͨ��ʼ���Ͳ�ѯ���� */
    BFD_PPI_STOP_SEND_SEQUENCE                     ,         /* ֹ֪ͨͣ���Ͳ�ѯ���� */
    BFD_PPI_USER_CREATE                            ,         /* API�����Ự */
    BFD_PPI_USER_DELETE                            ,         /* APIɾ���Ự */
    BFD_PPI_SESSION_GET                            ,         /* ��ȡ�ײ�NP�ĻỰ��Ϣ */
    /* SGSN BFD������:���ֻỰɾ����ԭ�� */
    BFD_PPI_SESSION_DELETE_ADMINDOWN               ,         /* ����Admin down���»Ựɾ�� */
    BFD_PPI_SESSION_DELETE_DOWN                    ,         /* ��������ԭ���»Ựɾ�� */
    BFD_PPI_SESSION_STOP_SEND_DETECT_PKT           ,         /* ֪ͨ���ٷ���������BFD���� */
    BFD_PPI_SESSION_START_SEND_DETECT_PKT          ,         /* ֪ͨ���·���������BFD���� */

    BFD_PPI_MSG_MAX
}PPI_MSG_TYPE_E;/* �޸ĸýṹʱ��ͬ���޸�bfd_ppi.c��BFD_PPI_OprType_En */

typedef enum tagNSR_PPI_MSG_TYPE_E
{
    BFD_PPI_NSR_READY                              ,         /* ֪ͨת������������ */                            
    BFD_PPI_NSR_FAILED                             ,         /* ֪ͨת���������NSRʧ�� */
    BFD_PPI_NSR_SESSCREATE                         ,         /* ֪ͨת���洴���Ự */
    BFD_PPI_NSR_SESSUPDATE                         ,         /* ֪ͨת������»Ự */
    BFD_PPI_NSR_SESSDOWN                           ,         /* ֪ͨת����Ự״̬��UP��Ϊdown */
    BFD_PPI_NSR_SESSDELETE                         ,         /* ֪ͨת����ɾ���Ự */
    BFD_PPI_NSR_FINISH                             ,         /* ֪ͨת����NSR������� */
    BFD_PPI_NSR_MAX                                ,
}NSR_PPI_MSG_TYPE_E;

/* SGSN������: BFD�Ựɾ��ʱֻ�·�BFD_PPI_USER_DELETE,���·�BFD_PPI_SESSION_DELETE zengshaoyang */
typedef enum tagPPI_DEL_BFDSESSION_MODE_E
{
    BFD_PPI_SESSION_DEL_MODE_DEF = 0,      /* ȱʡģʽ,�·�BFD_PPI_USER_DELETE��BFD_PPI_SESSION_DELETE*/
    BFD_PPI_SESSION_DEL_MODE_SGSN          /* SGSNģ��,ֻ�·�BFD_PPI_USER_DELETE */
}PPI_DEL_BFDSESSION_MODE_E;


/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
/* BFD���ÿ��ƿ� */
typedef struct tagBFD_CREATEDEL_BYVRF_S
{
    ULONG  ulAction;
    ULONG  ulDstIP;
    ULONG  ulSrcIP;
    ULONG  ulOutIfIndex;
    ULONG  ulVrfIndex;               /* VRF ����*/
    ULONG  ulBfdProtocol;            /* �ỰЭ������*/
}BFD_CREATEDEL_BYVRF_S;

typedef struct tagBFD_NOTIFY_BYVRF_S
{
    ULONG ulVrfInex;
    ULONG ulSessionID;
    ULONG ulState;
    ULONG ulDstIP;
    ULONG ulSrcIP;
    ULONG ulInIfIndex;
    ULONG ulAppGroup;
}BFD_NOTIFY_BYVRF_S;
/* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */

typedef ULONG(*BFD_PPI_HOOK_FUNC)(ULONG ulBfdPpiMsgType, ULONG ulSessionID, BFD_PPI_S* pBfdPpiInfo);

typedef ULONG(*BFD_NOTIFY_HOOK_FUNC)(ULONG ulSessionID, ULONG ulState,ULONG ulDstIP, ULONG ulSrcIP,
                                     ULONG ulInIfIndex, ULONG ulAppGroup);

/* RPU������: BFD״̬��Ǩʱ����ͨ�� */
typedef ULONG(*BFD_STATECHG_NOTIFY_HOOK_FUNC)(
            ULONG ulSessionID,   /* Session ID */
            ULONG ulOldState,    /* BFD�Ự�ϵ�״̬ */
            ULONG ulNewState,    /* BFD�Ự�µ�״̬ */
            ULONG ulDstIP,       /* Ŀ��IP ������*/
            ULONG ulSrcIP,       /* ԴIP ������*/
            ULONG ulInIfIndex,   /* ���ӿ� */
            ULONG ulAppGroup,    /* �ỰӦ���� */
            ULONG ulVrfIndex);  /* VRF���� */

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
typedef ULONG(*BFD_NOTIFY_BYVRF_HOOK_FUNC)(BFD_NOTIFY_BYVRF_S *pstBfdNotify);

typedef struct tagBfdNotifyByVrf {
    BFD_NOTIFY_BYVRF_HOOK_FUNC pfBfdNotifyByVrfHookFunc;  /* The Registered Function Pointer */
    struct tagBfdNotifyByVrf *pstNext;
} BFD_NOTIFY_BYVRF_HOOK_S;

/* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */

typedef struct tagBfdNotify {
    BFD_NOTIFY_HOOK_FUNC pfBfdNotifyHookFunc;  /* The Registered Function Pointer */
    struct tagBfdNotify *pstNext;
} BFD_NOTIFY_HOOK_S;

/*Added by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/4/8 */

typedef ULONG(*BFD6_PPI_HOOK_FUNC)(ULONG ulBfdPpiMsgType, BFD6_PPI_S* pBfdPpiInfo);

/* ��ȡBFD License���ܿ����Ƿ��
#define BFD_LICENSE_ON   0x01 :BFD License���ܴ�
#define BFD_LICENSE_OFF  0x00 :BFD License���ܹر�*/
typedef ULONG(*BFD_GET_LICENSE_STATE_FUNC)(ULONG *pulState);


typedef struct tagBFD6_NOTIFY_S
{
    ULONG ulVrfInex;
    ULONG ulSessionID;
    ULONG ulState;
    ULONG ulDstIP[4];
    ULONG ulSrcIP[4];
    ULONG ulInIfIndex;
    ULONG ulAppGroup;
}BFD6_NOTIFY_S;

typedef ULONG(*BFD6_NOTIFY_HOOK_FUNC)(BFD6_NOTIFY_S *pstBfd6Notify);

typedef struct tagBfd6Notify {
    BFD6_NOTIFY_HOOK_FUNC pfBfd6NotifyHookFunc;  /* The Registered Function Pointer */
    struct tagBfd6Notify *pstNext;
} BFD6_NOTIFY_HOOK_S;
/* End of Added by wangchengyang-xujun62830-57575, 2009/4/8 */

/* Added by likaikun00213099 at 20140718 */
#define VISP_BFD_FOR_IPV4      0
#define VISP_BFD_FOR_IPV6      1
#define VISP_BFD_FOR_ALL       2
typedef struct tagBFD_SESSION_FILTER_EX_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    ULONG ulPeerAddr4;   /* IPv4��ַ  ����˳�� */                                                               
    UCHAR ucPeerAddr6[16]; 
    ULONG ulLocalDiscr;  /* ָ������������ */
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    USHORT usIsAllVRF;   /* Ϊ1��ʾ�����е�VRF�н��в���,Ϊ0��ʾ��ָ����VRF�н��в��� */
    UCHAR  ucIpVer;      /*Ϊ2������IPv4��IPv6*/
    UCHAR  ucPad;
}BFD_SESSION_FILTER_EX_S;

typedef struct tagBFD_SESSION_CONFIG_INFO_EX_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulLocalDiscr;
    ULONG ulSrcAddr4;       /* IPv4 Դ��ַ������˳�� */
    UCHAR ucSrcAddr6[16];   /* IPv6��ַ              */

    ULONG ulPeerAddr4;      /* IPv4 �Զ˵�ַ������˳�� */
    UCHAR ucPeerAddr6[16];   /* IPv6��ַ                */
    ULONG ulDetectMult;
    ULONG ulMinTxInterval;
    ULONG ulMinRxInterval;
    ULONG ulOutIndex;
    ULONG ulAppId;
    CHAR  szVrfName[BFD_MAX_VRF_NAME_LEN + 1];
    ULONG ulRemoteDiscr;
    UCHAR ucTos;            /* bfd�Ựtos */
    UCHAR ucIpVer;
    UCHAR Padding[2];
}BFD_SESSION_CONFIG_INFO_EX_S;

typedef struct tagBFD_SESSION_COUNT_EX_S {
    UCHAR szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    ULONG ulSessionId;
    ULONG ulLocalDiscr;
    ULONG ulRemoteDiscr;
    USHORT usSessState;
    USHORT usIsMultiHop;
    ULONG ulPktRcv;
    ULONG ulPktSend;
    ULONG ulPktRcvDrop;
    ULONG ulPktSendErr;
    ULONG ulSessionDownNum;
    ULONG ulSessionStateTime;
    ULONG ulLastDownTime;
    ULONG ulVrfIndex;
    ULONG ulPeerAddr4;          /* IPv4��ַ */
    UCHAR ucPeerAddr6[16];      /* IPv6��ַ */
    UCHAR ucIpVer;
    UCHAR Padding[3];
}BFD_SESSION_COUNT_EX_S;

typedef struct tagBFD_SESSION_ALL_INFO_EX_S {
    BFD_SESSION_CONFIG_INFO_EX_S stConfigInfo;
    ULONG  ulRemoteDiscr;
    ULONG  ulSessionId;
    USHORT usSessState;
    USHORT usIsMultiHop;
    ULONG  ulActTxInterval;
    ULONG  ulActRxInterval;
    ULONG  ulActDetectMult;
    ULONG  ulActDetectTime;
    USHORT usLocalDiag;
    USHORT usDstPort;               /* �ỰĿ�Ķ˿ں�(������) */
    ULONG  ulRemoteMinTxInterval;   /* �Զ˵�MTI */
    ULONG  ulRemoteMinRxInterval;   /* �Զ˵�MRI */
    USHORT usRemoteDemandMode;      /* �Զ˵ļ��ģʽ */
    UCHAR  ucRemoteDetectMult;      /* �Զ˵ļ�ⱶ�� */
}BFD_SESSION_ALL_INFO_EX_S;
/* Added by likaikun00213099 at 20140718 */

/* api declare */
/*******************************************************************************
*    Func Name: BFD_DemandQueryByApp
*  Description: ����ָ���Ự�Ĳ�ѯ���еķ���
*        Input: ULONG  ulSessionID ָ���Ự�ı�ʶID��
*                                  ��Чȡֵ��Χ1-�û�����BFD����ұ���Ϊ�Ѵ����ỰID
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_ID
*                              BFD_ERR_SESSION_NOT_UP
*                              BFD_ERR_DETECT_MODE
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_QUE_BUSY
*                              BFD_ERR_WRITEQUE_FAIL
*                              BFD_ERR_HA_IS_SMOOTHING
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_DemandQueryByApp(ULONG ulSessionID);
/*******************************************************************************
*    Func Name: BFD_GetNextSessionID
*  Description: ��ȡָ���Ự����һ���Ự�ı�ʶID���Ự����ʶID�������У�
*        Input: ULONG  ulSessionID ָ���ĻỰID
*                      ���������Ϊ0ʱ�����ص�ǰ���ڵĵ�һ���Ự�ı�ʶIDֵ��
*                      ���������С���û����õ�BFD���ʱ�����ظ�ID֮��ĵ�һ���Ự�ı�ʶIDֵ
*                      ������������ڵ����û����õ�BFD��� ʱֱ�ӷ���0;
*       Output: 
*       Return: �ɹ�����       �Ự��ʶID����0��
*               ʧ�ܷ���       0����ǰ�޻Ự����BFDδʹ�ܣ���������ID���ڵ��� BFD_MAX_SESSION_ID��
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_GetNextSessionID(ULONG ulSessionID);
/*******************************************************************************
*    Func Name: BFD_GetSessionInfo
*  Description: ��ȡָ���Ự�ĵ�ǰ��Ϣ
*        Input: ULONG  ulSessionID ָ���Ự�ı�ʶID��ȡֵ��ΧΪ1���û����õ�BFD���
*
*       Output: BFD_SESSION_INFO_S* pSess ���ڴ洢�Ự�����Ļ�������ַָ��
*                                         �������ݶ������������
*       Return: �ɹ�����   BFD_OK
*               ʧ�ܷ���   BFD_ERR_SESSION_ID��      �ỰID�Ƿ�
*                          BFD_ERR_SESSION_NOT_EXIST ָ���Ự������
*                          BFD_ERR_NULL_POINTER
*                          BFD_ERR_DISABLE
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_GetSessionInfo(ULONG ulSessionID, BFD_SESSION_INFO_S *pSess);
/*******************************************************************************
*    Func Name: BFD_GetVersion
*  Description: ��ȡBFD CBB�İ汾�źͱ���ʱ��
*        Input: CHAR *szVerInfo: BFD CBB�İ汾��Ϣ�ͱ���ʱ���ַ���
*                                ���û�����256�ֽڿռ䡣
*       Output:
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_NULL_POINTER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-4-8    LY(57500)        Create the first version.
*
*******************************************************************************/
extern ULONG BFD_GetVersion(CHAR *szVerInfo);
/*******************************************************************************
*    Func Name: BFD_Init
*  Description: BFD��ʼ�����������ڻ���VISPʵ��
*               ��˷���VISPЭ��ջ������SystemEntry��
*        Input: ULONG ulNpMode��
*                     0    ��ʹ��NP
*                     1    NP���ͣ����̽��
*                     2    NP���͡�̽��
*                     ���� �Ƿ�
*               ULONG ulBFDTaskPri��BFD����������ȼ�(0��255)
*                                   visp��Ҫ�����SOCKRUN��������ȼ�
*               ULONG ulBFDTaskStackSize��BFD������ջ��С
*                                   visp��Ҫ�����SOCKRUN�����ջ��С��Ĭ����16K*
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR
*                              BFD_ERR_CREATE_TASK��
*                              BFD_ERR_CREATE_QUEUE��
*                              BFD_ERR_NP_MODE
*                              BFD_ERR_TASK_PRI
*                              BFD_ERR_CREATE_OTHERQUEUE
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-08      Wangchengyang    Create
*  2007-03-22      lijing 52889     modify for Defect A82D13061
*  2007-12-7       zhangchunyu      modify for Defect A82D21512
*******************************************************************************/
extern ULONG BFD_Init(ULONG ulNpMode,ULONG ulBFDTaskPri, ULONG ulBFDTaskStackSize);
/*******************************************************************************
*    Func Name: BFD_IpAddrEventNotify
*  Description: ���ⲿ��ӡ�ɾ����һ����ַʱ��֪ͨBFDģ�������Ӧ�������磺
*               һ���Ự��Դ��ַ��ɾ���ˣ���ûỰ��ֹͣ��
*               ��һ���Ự��Ŀ�ĵ�ַ������Ϊ�˱��ص�ַ����ûỰ��ֹͣ��
*               ֱ��д��Ϣ���¼�֪ͨBFD������;
*
*        Input: ulIpEvent  ��ַ�¼�����ӡ�ɾ��;0 ��ʾ����1 ��ʾɾ��
*               ulIpAddr   ��ӻ�ɾ���ĵ�ֵַ��������
*               ulIfIndex  ��ַ�仯�����ӿڵ�����ֵ��
*
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_DISABLE;
*                              BFD_ERR_EVENT
*
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-07     Wangchengyang    Create
*  2007-5-17  wujie(61195)         Modified for A82D15480����ε�ַ��Ϊ������
*******************************************************************************/
extern ULONG BFD_IpAddrEventNotify(ULONG ulIpEvent, ULONG ulIpAddr, ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: BFD6_IpAddrEventNotify
* Date Created: 2013-12-12
*       Author: Wangchengyang
*  Description: ���ⲿ��ӡ�ɾ����һ����ַʱ��֪ͨBFDģ�������Ӧ�������磺
*               һ���Ự��Դ��ַ��ɾ���ˣ���ûỰ��ֹͣ��
*               ��һ���Ự��Ŀ�ĵ�ַ������Ϊ�˱��ص�ַ����ûỰ��ֹͣ��
*               ֱ��д��Ϣ���¼�֪ͨBFD������;
*
*        Input: ulIpEvent  IPv6��ַ�¼�����ӡ�ɾ��;0 ��ʾ����1 ��ʾɾ��
*               pulIpAddr   ��ӻ�ɾ���ĵ�ֵַ��������
*               ulIfIndex  ��ַ�仯�����ӿڵ�����ֵ��
*
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_DISABLE;
*                              BFD_ERR_EVENT
*
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-12     wangjiaqi         Create
*******************************************************************************/
ULONG BFD6_IpAddrEventNotify(ULONG ulIpEvent, ULONG *pulIpAddr, ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: BFD_TrunkPortEventNotify
* Date Created: 2007-8-29
*       Author: LY(57500)
*  Description: ���eth�ӿڼ��뵽trunk���trunk���Ƴ�,����Ҫ֪ͨbfd,�����Ƿ��г��ӿ�����Ϊ�ýӿ�,������澯
*        Input: ULONG ulPortEvent: BFD_TRUNKPORT_ADD_EVENT �ӿڼ��뵽trunk
*                                  BFD_TRUNKPORT_REMOVE_EVENT �ӿڴ�trunk���Ƴ�
*               ULONG ulPortIfIndex: �ӿ�(trunk��Ա�˿�)����
*       Output: 
*       Return: BFD_OK ֪ͨ�ɹ�
*               ����   ֪ͨʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-8-29    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_TrunkPortEventNotify(ULONG ulPortEvent, ULONG ulPortIfIndex);
/*******************************************************************************
*    Func Name: BFD_RecvPacket
* Date Created: 2006-12-6
*       Author: wujie(61195)
*  Description: ���մ���һ��BFD���Ʊ���
*               ��������Э��ջ��UDP���봦���д���ʱ��������UDP socket���մ�����ʹ�ô˽��սӿڡ�
*        Input: CHAR *pBFDPacket: ���յ�BFD����
*               ULONG ulPktLenth: BFD�����ܳ���
*               ULONG ulDstIP: ���ձ��ĵ�Ŀ�ĵ�ַ��������
*               ULONG ulSrcIP: ���ձ��ĵ�Դ��ַ��������
*               ULONG InIfIndex: ������ӿ�����
*       Output:
*       Return:
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-6   wujie(61195)         Creat the first version.
*  2009-02-01  wangchengyang        modified for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_RecvPacket(CHAR *pBFDPacket, ULONG ulPktLenth, ULONG ulDstIP, ULONG ulSrcIP, ULONG InIfIndex);


extern ULONG BFD_RecvPacketByVrf(CHAR *pBFDPacket, ULONG ulPktLenth, ULONG ulDstIP, ULONG ulSrcIP, ULONG InIfIndex,ULONG
ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_RecvPacketWithIP
*  Description: ���մ���һ��UDP����ΪBFD���Ʊ��ĵ�IP���ģ�
*               ��Э��ջ֧����UDP���봦���д���ʱ��������VISP��Ӧ��ʱ����ʹ�ô˽��սӿڡ�
*        Input: CHAR* pIpPacket:���յ�BFD���ģ����ĸ�ʽΪIP�����ײ���UDP�����ײ���BFD����
*               ULONG ulInIfIndex:������ӿ�����
*       Output: 
*       Return: �ɹ��������
*      Caution: VISPЭ��ջ��IP���Ľ��մ����ʱ�򣬻ὫIP�ײ��ĳ����ֶ�ת��Ϊ������
*               Ȼ���ȥIP�ײ��ĳ��ȣ��������ﴫ���IP�����ײ������ֶ�ֱ�Ӽ�ȥUDP�ײ�����
*               ���õ�BFD���ĳ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-5  wujie(61195)         Creat the first version.
*  2007-7-24  wujie(61195)         Modified for A82D18150����VRP�ɰ汾��BFD�����Խ�
*
*******************************************************************************/
extern ULONG BFD_RecvPacketWithIP( CHAR* pIpPacket, ULONG ulInIfIndex);
/*******************************************************************************
*    Func Name: BFD_RecvPacketWithIP
* Date Created: 2006-12-5
*       Author: wujie(61195)
*  Description: ���մ���һ��UDP����ΪBFD���Ʊ��ĵ�IP���ģ�
*               ��Э��ջ֧����UDP���봦���д���ʱ��������VISP��Ӧ��ʱ����ʹ�ô˽��սӿڡ�
*        Input: CHAR* pIpPacket:���յ�BFD���ģ����ĸ�ʽΪIP�����ײ���UDP�����ײ���BFD����
*               ULONG ulInIfIndex:������ӿ�����
*               ULONG ulVrfIndex :VRF����
*       Output: 
*       Return: �ɹ��������
*      Caution: VISPЭ��ջ��IP���Ľ��մ����ʱ�򣬻ὫIP�ײ��ĳ����ֶ�ת��Ϊ������
*               Ȼ���ȥIP�ײ��ĳ��ȣ��������ﴫ���IP�����ײ������ֶ�ֱ�Ӽ�ȥUDP�ײ�����
*               ���õ�BFD���ĳ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-5   wujie(61195)         Creat the first version.
*  2007-7-24   wujie(61195)         Modified for A82D18150����VRP�ɰ汾��BFD�����Խ�
*  2009-02-01  wangchengyang        modified for VISP1.7C03 VRF
*******************************************************************************/
extern ULONG BFD_RecvPacketWithIPByVrf(CHAR* pIpPacket, ULONG ulInIfIndex,ULONG ulVrfIndex);
/*******************************************************************************
*    Func Name: BFD_SessionAdminister
*  Description: �Ự���û�����Admindown��undo Admindown
*        Input: ULONG  ulSessionID ָ���Ự�ı�ʶID��ȡֵ��ΧΪ1���û����õ�BFD���
*               BOOL_T bShutdown   TRUE���رջỰ��FALSE���򿪻Ự
*
*       Output: 
*       Return: �ɹ�����   BFD_OK
*               ʧ�ܷ���   BFD_ERR_SESSION_ID��      �ỰID�Ƿ�
*                          BFD_ERR_SESSION_NOT_EXIST ָ���Ự������
*                          BFD_ERR_INVALID_PARAMETER
*                          BFD_ERR_DISABLE
*                          BFD_ERR_HA_IS_SMOOTHING
*                          BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SessionAdminister(ULONG ulSessionID, BOOL_T bShutdown);
/*******************************************************************************
*    Func Name: BFD_SessionCreate
*  Description: �趨һ��BFD�Ự�Ļ�������������ʼ�����Ự
*        Input: ULONG ulDstIP      ָ���Ự��Ŀ�ĵ�ַ��������
*               ULONG ulSrcIP      ָ���Ự��Դ��ַ��������
*               ULONG ulOutIfIndex   �����ỰʱΪ���ӿ�����������ʱֵΪ0��
*                                    �ɵ����߱�֤���ϲ����ĺ�����
*               ULONG *pulSessionID  ȡֵ��ΧΪ[0,512]�������0����VISP�Զ�����ỰID��
*                                    �������ָ����ID�����Ự
*
*       Output: ULONG *pulSessionID  �Ự�ı�ʶID
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_EXIST_SESSION
*                              BFD_ERR_SESSION_FULL
*                              BFD_ERR_NULL_POINTER
*                              BFD_ERR_MEM_ALLOC
*                              BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_DISABLE
*                              BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-05      Wangchengyang    Create
*  2007-5-17       wujie(61195)     Modified for A82D15480����ε�ַ��Ϊ������
*******************************************************************************/
extern ULONG BFD_SessionCreate(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulOutIfIndex, ULONG* pulSessionID);
/*******************************************************************************
*    Func Name: BFD_SessionDeleteDontSendDDPkt
*  Description: ɾ��BFD�Ựʱ������Admin Down����
*        Input: ULONG ulSessionID:�ỰID
*
*       Output: 
*       Return: �ɹ�����       VOS_OK
*               ʧ�ܷ���       Error Code
*      Caution: ��CBSC/MBSC��Ʒʹ�ã���ɾ��BFD�Ựʱ������Admin Down����
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-10-08      chenlong168670   Create
*
*******************************************************************************/
extern ULONG BFD_SessionDeleteDontSendDDPkt(ULONG ulSessionID);
/*******************************************************************************
*    Func Name: BFD_SessionDelete
*  Description: ɾ��ָ���Ự
*        Input: ulSessionID �Ự��ʶID��ȡֵ��ΧΪ1���û����õ�BFD���
*
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_HA_IS_SMOOTHING
*                              BFD_ERR_SESSION_ID
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SessionDelete(ULONG ulSessionID);
/*******************************************************************************
*    Func Name: BFD_DeleteSingleAppFromSession
*  Description: ɾ��ָ���Ự�ĵ���Ӧ��
*        Input: ulSessionID �Ự��ʶID��ȡֵ��ΧΪ1���û����õ�BFD���
*               ulAppID     Ӧ��ID      ȡֵ:2��N����,һ��bitλ��ʾһ��Ӧ��
*
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_ID
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_APP_ID;
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_DeleteSingleAppFromSession(ULONG ulSessionID, ULONG ulAppID);
/*******************************************************************************
*    Func Name: BFD_SessionParaUpdate
*  Description: ����һ���Ự�Ĳ�����������MTI��MRI��Detect Mult��Detect Mode��
*               �����������º�Ĳ���Ӧ�õ��Ự�С�
*        Input: ULONG ulSessionID �Ự��ʶID��ȡֵ��ΧΪ1���û����õ�BFD���
*               BFD_SESSION_PARA_S *pSessPara ���²����ṹָ��
*
*       Output: 
*       Return: �ɹ�����    BFD_OK
*               ʧ�ܷ���    BFD_ERR_SESSION_ID��      �ỰID�Ƿ�
*                           BFD_ERR_TX_INTERVAL;      ����ʱ�����Ƿ�
*                           BFD_ERR_RX_INTERVAL;      ����ʱ�����Ƿ�
*                           BFD_ERR_DETECT_MULT;      ��ⱶ���Ƿ�
*                           BFD_ERR_SESSION_NOT_EXIST ָ���Ự������
*                           BFD_ERR_DETECT_MODE       ���ģʽ�Ƿ�
*                           BFD_ERR_NULL_POINTER      ����ָ��Ϊ�գ�
*                           BFD_ERR_DISABLE           BFDδʹ��
*                           BFD_ERR_HA_IS_SMOOTHING
*                           BFD_ERR_QUE_BUSY
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SessionParaUpdate( ULONG ulSessionID, BFD_SESSION_PARA_S *pSessPara);
/*******************************************************************************
*    Func Name: BFD_SetAppsToSession
*  Description: �趨ĳһ�Ự��Ӧ��ģ��(Ӧ����,��������ЩӦ�ù�ϵ����Ự��״̬�仯)
*        Input: ULONG ulSessionID   �ỰID 1~�û�����BFD���
*               ULONG ulAppGroup    �Ự��Ӧ��ģ����ϣ�
*                                   ÿһ��Bit��ʶ�ŸûỰ��һ��Ӧ��ģ�飻
*                                   �����һ������Ϊ׼��
*                                   Ϊ0��ʾȡ������ģ��ԸûỰ��Ӧ�ã�
*                                   ���֧��32���ⲿӦ��ģ�顣
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_ID;
*                              BFD_ERR_APP_ID;
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution: �ο����Ự״̬�仯ʱ���ⲿ֪ͨ�����ӿڣ�
*               �Ǳ�Ҫ�ӿڣ����κλỰ��״̬�仯ʱ��
*               ��Ʒ����ġ��Ự״̬�仯ʱ���ⲿ֪ͨ�����ӿڲ���ͳһ����ʱ
*               ����Ʒ��BFDӦ��ģ����٣����������ô˽ӿڣ�
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SetAppsToSession(ULONG ulSessionID, ULONG ulAppGroup);
/*******************************************************************************
*    Func Name: BFD_SetBfdCapability
*  Description: ʹ�ܻ�ȥʹ��BFD����
*
*        Input: BOOL_T bBfdCapability TRUE��ʹ�ܣ�FALSE��ȥʹ�ܣ�
*
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_DISABLE_PROCESSING
*                              BFD_ERR_INVALID_PARAMETER
*
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-07      Wangchengyang    Create
*  2007-03-29      jiangtao(51916)  Modify for A82D13299
*******************************************************************************/
extern ULONG BFD_SetBfdCapability(BOOL_T bBfdCapability);
/*******************************************************************************
*    Func Name: BFD_SetDebugSwitch
*  Description: �򿪻�ر�BFD���Կ���
*        Input: ULONG ulSessionID ָ���ỰID�Ϸ���Ϊ1~�û����õ�BFD���
*                                 ������Ϊ0���ʶ��/�ر����лỰ�ĵ��Կ���
*               ULONG ulDebug  ���õ��Ա��,��(�ر�)����Ӧ��־��λ(����)
*                              BFD_DEBUG_STATE    0x1  BFD״̬��Ǩ����
*                              BFD_DEBUG_INPUT    0x2  ���յ�BFD���ĵ���
*                              BFD_DEBUG_OUTPUT   0x4  ���͵�BFD���ĵ���
*                              ����Ҫ�򿪶�����,���λ��
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_INVALID_PARAMETER
*                              BFD_ERR_SESSION_ID
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*                              BFD_ERR_HA_IS_SMOOTHING
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SetDebugSwitch(ULONG ulSessionID, ULONG ulDebug);
/*******************************************************************************
*    Func Name: BFD_GetDebugSwitch
*  Description: ��ȡBFD�ĵ��Կ��أ����ulSessionIDΪ0����ȡȫ��Debug���ء������ȡ
*                                  ָ���ӿڵ��Կ��ء�
*        Input: ULONG ulSessionID: �ỰID(0-�û�����BFD���)
*               ULONG *pulDebug: ��ȡ����ָ��
*       Output: pulDebug
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_NULL_POINTER
*                              BFD_ERR_SESSION_ID
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_DISABLE
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-7-31    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetDebugSwitch(ULONG ulSessionID, ULONG *pulDebug);
/*******************************************************************************
*    Func Name: BFD_SetSingleAppToSession
*  Description: �趨ĳһ���Ự�ľ���Ӧ��
*        Input: ULONG ulSessionID   �ỰID 1~�û�����BFD���
*               ULONG ulAppID       Ӧ��ID 2��N����,һ��bitλ��ʾһ��Ӧ��
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_SESSION_ID;
*                              BFD_ERR_APP_ID;
*                              BFD_ERR_DISABLE
*                              BFD_ERR_SESSION_NOT_EXIST
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution: �ο����Ự״̬�仯ʱ���ⲿ֪ͨ�����ӿڣ�
*               �Ǳ�Ҫ�ӿڣ����κλỰ��״̬�仯ʱ��
*               ��Ʒ����ġ��Ự״̬�仯ʱ���ⲿ֪ͨ�����ӿڲ���ͳһ����ʱ
*               ����Ʒ��BFDӦ��ģ����٣����������ô˽ӿڣ�
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SetSingleAppToSession(ULONG ulSessionID, ULONG ulAppID);
/*******************************************************************************
*    Func Name: BFD_SetWtrTime
*  Description: �趨�ỰDown֮�����½����ĵȴ�ʱ�䡣WTR -- Waiting To Restart
*        Input: ULONG ulSeconds �ȴ�ʱ�䣨s������ΧΪ0��0xFFFFFFFF��
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_DISABLE;
*                              BFD_ERR_WTR
*                              BFD_ERR_HA_IS_SMOOTHING
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-06      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_SetWtrTime(ULONG ulSeconds);
/*******************************************************************************
*    Func Name: BFD_GetGlobalInfo
*  Description: ��ȡBFDȫ����Ϣ
*        Input: BFD_GLOBAL_INFO_S *pstBfdGlobalInfo: BFDȫ����Ϣ�ṹ��ָ��
*       Output: BFDȫ����Ϣ
*       Return: BFD_OK
*               BFD_ERR_NULL_POINTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-5-16  wujie(61195)         Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetGlobalInfo(BFD_GLOBAL_INFO_S *pstBfdGlobalInfo);
/*******************************************************************************
*    Func Name: BFD_SetAdaptMultiHopPort
*  Description: �����Ƿ��Զ����������Ự��UDPĿ�Ķ˿ںš�VRP�ɰ�BFD�Ķ����˿ں�
*               �뵥���˿ں�һ������3784��VISPΪ����������Ự�Խ�����һЩ�޸ġ����A82D18150��
*        Input: ULONG ulSwitch: BFD_ON/�� BFD_OFF/�ر�
*       Output: 
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_HA_IS_SMOOTHING;
*                              BFD_ERR_INVALID_PARAMETER;
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-7-24  wujie(61195)         Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_SetAdaptMultiHopPort(ULONG ulSwitch);
/*******************************************************************************
*    Func Name:   BFD_PPI_HookRegister
*    Description: ����ƷӦ��NP��������BFD CBBע��PPI֪ͨ������ע��֮��BFD CBB
*                 ����ע��ĺ�����NP֪ͨ�Ự��Ϣ��
*    Input:       BFD_PPI_HOOK_FUNC* pfBfdPpiHook: NP  ���Ӻ���
*    Output:      ��
*    Return:      �ɹ�����       BFD_OK
*                 ʧ�ܷ���       BFD_ERR_NULL_POINTER
*                                BFD_ERR_DISABLE
*    Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-6    qinyun(62011)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_PPI_HookRegister(BFD_PPI_HOOK_FUNC pfBfdPpiHook);
extern ULONG BFD_DetectDownWithDiagByPrdt(ULONG ulSessionID,ULONG ulDiag);
/*******************************************************************************
*    Func Name:   BFD_DetectDownByPrdt
*    Description: ��Ʒ��NP̽�⵽�ỰDownʱ����Ʋ����֪ͨ�ӿ�
*    Input:       ULONG ulSessionID: �ỰID
*    Output:      ��
*    Return:      �ɹ�����       BFD_OK
*                 ʧ�ܷ���       BFD_ERR_SESSION_ID
*                                BFD_ERR_SESSION_NOT_EXIST
*    Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-12-6    qinyun(62011)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_DetectDownByPrdt(ULONG ulSessionID);
/*******************************************************************************
*    Func Name: BFD_GetSessionId
*  Description: ͨ��ԴĿ��IP�ͳ��ӿ���������ѯBFD �Ựid
*        Input: ulDstIP   Ŀ��IP��������
*               ulSrcIP   ԴIP��������
*               ulIfIndex ���ӿ�����
*
*       Output: 
*       Return: �Ựid,���������ָ���ĻỰ�򷵻�0xFFFFFFFF
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-03-26      Wangchengyang    Create
*******************************************************************************/
extern ULONG BFD_GetSessionId(ULONG ulDstIP, ULONG ulSrcIP, ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: BFD_GetBfdTotalNumber
*  Description: ��ȡ�ܵ�BFD�Ự����
*        Input: ULONG *pulBfdSessionCnt:  �Ự����
*       Output:
*       Return: BFD_OK:�ɹ�;
*               BFD_ERR:ָ�������
*               BFD_ERR_DISABLE:bfdδʹ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD_GetBfdTotalNumber(ULONG *pulBfdSessionCnt);
/*******************************************************************************
*    Func Name: TCPIP_BfdNotifyRegister
*  Description: BFD֪ͨע�ắ��
*        Input: BFD_NOTIFY_HOOK_FUNC pBfdNotifyHookFunc: ���Ӻ���ָ��
*       Output:
*       Return: �ɹ�BFD_OK��ʧ��BFD_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_BfdNotifyRegister(BFD_NOTIFY_HOOK_FUNC pBfdNotifyHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_Bfd_StateChg_Notify_Hook_Register
* Date Created: 2010-06-08
*       Author: zengshaoyang62531
*  Description: BFD�Ự��״̬��Ǩʱ,����ͨ��
*        Input: BFD_STATECHG_NOTIFY_HOOK_FUNC pfFunc:ע�ṳ��
*       Output: 
*       Return: VOS_OK;
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_Bfd_StateChg_Notify_Hook_Register(
                        BFD_STATECHG_NOTIFY_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_BfdNotifyUnRegister
* Date Created: 2008-8-4
*       Author: qinyun(62011)
*  Description: BFD֪ͨȥע�ắ��
*        Input: BFD_NOTIFY_HOOK_FUNC pBfdNotifyHookFunc: ���Ӻ���ָ��
*       Output:
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       BFD_ERR_MEM_ALLOC
*                              BFD_ERR_NOTIFIER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4    qinyun(62011)     Creat the first version.
*******************************************************************************/
extern ULONG TCPIP_BfdNotifyUnRegister(BFD_NOTIFY_HOOK_FUNC pBfdNotifyHookFunc);

/*******************************************************************************
*    Func Name: BFD_ShowGlobalInfo
*  Description: ��ʾBFD������Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern VOID  BFD_ShowGlobalInfo(VOID);
/*******************************************************************************
*    Func Name: BFD_ShowVersion
*  Description: ��ʾBFD�汾�źͱ���ʱ��
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern VOID  BFD_ShowVersion(VOID);
/*******************************************************************************
*    Func Name: BFD_ShowSessionInfo
*  Description: ��ʾBFD���лỰ��Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern VOID  BFD_ShowSessionInfo(VOID);

/*******************************************************************************
*    Func Name: BFD_GetSessionState
* Date Created: 2009-02-05
*       Author: wuhailan/gexianjun
*  Description: ��ȡBFD�Ự״̬,�����ṩ��VRRPģ��ļ�������ʹ��
*        Input: ULONG ulSessionID:�ỰID
*               ULONG ulVrfIndex: vrf����
*       Output: ULONG *pstState:���صĻỰ״̬
*       Return: �ɹ�BFD_OK,�������ش�����
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-05   wuhailan/gexianjun      Create
*
*******************************************************************************/
extern ULONG BFD_GetSessionState(ULONG ulSessionID, ULONG ulVrfIndex, ULONG *pstState);

/*******************************************************************************
*    Func Name: BFD_ShowSessionInfoByVrf
* Date Created: 2009-02-01
*       Author: wangchengyang
*  Description: ��ʾָ��VRF��BFD���лỰ��Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01   wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern VOID BFD_ShowSessionInfoByVrf(CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: BFD_ShowSessionCountByVrf
* Date Created: 2009-02-01
*       Author: wangchengyang
*  Description: ��ʾָ��VRF������BFD���лỰͳ����Ϣ
*        Input: pszVrfName VRF ��
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01   wangchengyang    Create for VISP1.7C03 VRF
*******************************************************************************/
extern VOID BFD_ShowSessionCountByVrf(CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: BFD_ShowSessionInfo
* Date Created: 2008-8-4
*       Author: qinyun
*  Description: ��ʾBFD���лỰͳ����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-4  qinyun(62011)     Creat the first version.
*  2009-02-01  wangchengyang modified for VISP1.7C03 VRF
*******************************************************************************/
extern VOID BFD_ShowSessionCount(VOID);

/*Added by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/4/8 */
/*******************************************************************************
*    Func Name: BFD_SetFirstNegoTimes
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: BFD�״�֪ͨdownЭ��ʧ�ܴ���
*        Input: ulFirsNegoTimes    �������
*       Output:
*       Return: �ɹ�����       BFD_OK
*               ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*******************************************************************************/
extern ULONG BFD_SetFirstNegoTimes(ULONG ulFirsNegoTimes);

/*******************************************************************************
*    Func Name:   BFD6_PPI_HookRegister
* Date Created: 2009-4-8
*       Author: wangchengyang-xujun62830-57575
*  Description: ����ƷӦ��BFD6 NP��������BFD CBBע��PPI֪ͨ������ע��֮��BFD CBB
*                 ����ע��ĺ�����NP֪ͨ�Ự��Ϣ��
*        Input:       BFD6_PPI_HOOK_FUNC* pfBfdPpiHook: NP  ���Ӻ���
*       Output:      ��
*       Return:      �ɹ�����       BFD_OK
*                    ʧ�ܷ���       ������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-4-8  wangchengyang-xujun62830-57575     Creat the first version.
*
*******************************************************************************/
extern ULONG BFD6_PPI_HookRegister(BFD6_PPI_HOOK_FUNC pfBfdPpiHook);

/* End of Added by wangchengyang-xujun62830-57575, 2009/4/8 */

/*******************************************************************************
*    Func Name: BFD_SetSessionTos
* Date Created: 2009-8-12
*       Author: LY(57500)
*  Description: ����bfd�Ự��tosֵ
*        Input: ULONG ulSessionID:�Ựid
*               UCHAR ucTos: tosֵ��ֵ����Ч�����õ�ֵ��ֱ�����õ�bfd����ipͷ���tos�ֶ��
*       Output:
*       Return: BFD_OK: �ɹ�
*               ����:   ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-12    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG BFD_SetSessionTos(ULONG ulSessionID, UCHAR ucTos);

/*******************************************************************************
*    Func Name: BFD_SetSessionTosByVrf
* Date Created: 2009-8-12
*       Author: LY(57500)
*  Description: ����bfd�Ự��tosֵ
*        Input: ULONG ulSessionID:�Ựid
*               ULONG ulVrfIndex: vrf����
*               UCHAR ucTos: tosֵ��ֵ����Ч�����õ�ֵ��ֱ�����õ�bfd����ipͷ���tos�ֶ��
*       Output:
*       Return: BFD_OK: �ɹ�
*               ����:   ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-12    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG BFD_SetSessionTosByVrf(ULONG ulSessionID, ULONG ulVrfIndex, UCHAR ucTos);

/****************************************************************************
*    Func Name: BFD_DelSessionByVrf
* Date Created: 2008-08-26
*       Author: wuhailan
*  Description: ����VRF����ɾ������BFD�Ự��Ϣ
*        Input: ULONG ulVrfIndex:VRF����
*       Output: 
*       Return: VOS_OK:�ɹ� ��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-26   wuhailan         Create
*
*******************************************************************************/
extern ULONG BFD_DelSessionByVrf(ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: BFD_SetPollRetranSwitch
* Date Created: 2013-01-17
*       Author: luogaowei
*  Description: BFD P/F �ش���������
*        Input: ULONG usSwitch: ���ÿ��أ�Ĭ�Ϲر�(VRP_YES: 1Ϊ��, VRP_NO: 0Ϊ�ر�)
*               ULONG ulPeriod: ���õĶ�ʱ������(ʵ�ʻ����-2 ��2֮��ƫ��,Ĭ��10�룬��Χ3-20)
*               ULONG ulMaxNum: ���õ��ش�����(Ĭ��5�Σ���Χ1-10)
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-01-17   luogaowei              Create for MBSC   
*
*******************************************************************************/
ULONG BFD_SetPollRetranSwitch(ULONG usSwitch, ULONG ulPeriod, ULONG ulMaxNum);


/*******************************************************************************
*    Func Name: BFD_GetPollRetranSwitch
* Date Created: 2013-01-17
*       Author: luogaowei
*  Description: BFD P/F �ش���������
*        Input: 
*       Output: ULONG *pusPFMode: ����ģʽ��Ĭ�Ϲر�(0:�·�P��Ǹ�NP�ش�  1:���ش��� 2:�����������ش�����)
*               ULONG *pulPeriod: ���õĶ�ʱ������(ʵ�ʻ����-2 ��2֮��ƫ��,Ĭ��10�룬��Χ3-20)
*               ULONG *pulMaxNum: ���õ��ش�����(Ĭ��5�Σ���Χ1-10)
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-01-17   luogaowei              Create for MBSC   
*
*******************************************************************************/
ULONG BFD_GetPollRetranSwitch(ULONG *pusReTranMode, ULONG *pulPeriod, ULONG *pulMaxNum);

/*******************************************************************************
*    Func Name: BFD_SetBfdPollClearSwitch
* Date Created: 2014-05-15
*       Author: wangbin
*  Description: ����BFD P���������ƿ���
*        Input: ulPollClearSwitch .0-  �ر�, 1-��
*       Output:  
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-15   wangbin               
*
*******************************************************************************/
ULONG BFD_SetBfdPollClearSwitch(ULONG ulPollClearSwitch);

/*******************************************************************************
*    Func Name: BFD_GetBfdPollClearSwitch
* Date Created: 2014-05-15
*       Author: wangbin
*  Description: ��ȡBFD P���������ƿ���ֵ
*        Input:    
*       Output:  pulPollClearSwitch 0-  �ر�, 1-��
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-15   wangbin               
*
*******************************************************************************/
ULONG BFD_GetBfdPollClearSwitch(ULONG *pulPollClearSwitch);

/*******************************************************************************
*    Func Name: BFD_SetBfdProtocolCompliance
* Date Created: 2014-09-01
*       Author: likaikun213099
*  Description: ����BFDЭ��˳���Կ��أ�ÿһbit����һ��Э��һ��������
*        Input: ULONG ulBfdComplianceBit:
*               ULONG ulSwitch:
*       Output: 
*       Return: 
*      Caution: ulSwitchΪBFD_ON ʱ������ulBfdComplianceBitλΪ1��Э��һ��������.
*               ulSwitchΪBFD_OFFʱ���ر�ulBfdComplianceBitλΪ1��Э��һ��������.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-01   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_SetBfdProtocolCompliance(ULONG ulBfdComplianceBit, ULONG ulSwitch);

/*******************************************************************************
*    Func Name: BFD_GetBfdProtocolCompliance
* Date Created: 2014-09-28
*       Author: likaikun213099
*  Description: 
*        Input: ULONG *pulSwitch:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-28   likaikun213099          Create
*
*******************************************************************************/
ULONG BFD_GetBfdProtocolCompliance(ULONG *pulSwitch);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

#endif   /* end of _BFD_CBB_API_H_ */


