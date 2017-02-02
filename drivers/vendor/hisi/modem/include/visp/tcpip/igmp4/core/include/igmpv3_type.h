/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_type.h
*
*  Project Code: VISPV100R007
*   Module Name: IGMP  
*  Date Created: 2008-03-11
*        Author: zengshaoyang62531
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-11   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_TYPE_H
#define _IGMPV3_TYPE_H

#include "tcpip/public/tcpip_config.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define IGMP_MEMBERSHIP_QUERY          0x11    /* membership query */
#define IGMPV1_MEMBERSHIP_REPORT       0x12    /* Ver. 1 membership report */
#define IGMPV2_MEMBERSHIP_REPORT       0x16    /* Ver. 2 membership report */
#define IGMPV2_LEAVE_GROUP             0x17    /* Ver. 2 Leave-group message */
#define IGMPV3_MEMBERSHIP_REPORT       0x22    /* Ver. 3 membership report */

#define IGMP_EXCLUDE                   IGMP_REPORT_MODE_EX  /*EXCLUDE����ģʽ���ڲ�ʹ��*/
#define IGMP_INCLUDE                   IGMP_REPORT_MODE_IN  /*INCLUDE����ģʽ���ڲ�ʹ��*/

#define IGMP_RECIEVE                   0       /* ���շ����IGMP����*/
#define IGMP_SEND                      1       /* ���ͷ����IGMP����*/

/*struct id,�������ڴ�ʱʹ��*/
#define SID_IGMPTIMERNODE_S            1
#define SID_IGMPCALLBACK_S             2
#define SID_IPMULTI_SOURCELIST_S       3
#define SID_IPMULTI_S                  4
#define SID_IPMULTI_LIST_S             5
#define SID_IGMPSTAT_S                 6

/*�����������ڵ�ȡֵ��Χ[1 - 5s]*/
#define UNS_REPORT_INTERVAL_MIN 1         /*unsolicited report interval,min: 1s*/
#define UNS_REPORT_INTERVAL_MAX 5         /*unsolicited report interval,max: 5s*/

typedef enum tagIGMP_ERRCODE_INC
{
    IGMP_ERR_MAXSOURCE = 1,                    /*socket�϶ಥ���Դ��ַ�Ѵﵽ���ֵ*/
    IGMP_ERR_NOTEXISTINLIST,                   /*Դ��ַ��������Դ�б���*/
    IGMP_ERR_MEMORYFAULT,                      /*�ڴ����*/
    IGMP_ERR_MULTINOTEXIST,                    /*�ಥ�鲻����*/
    IGMP_ERR_SOURCEEXISTINSOCK,                /*Դ��ַ�Ѿ�������socket�ಥ���Դ�б���*/
    IGMP_ERR_SOURCELISTNULL,                   /*Դ�б�Ϊ��*/
    IGMP_ERR_PARAM,                            /*��������*/
    IGMP_ERR_IF_INVALIDTYPE,                   /*�ӿ�������Ч*/
    IGMP_ERR_IF_NULL,                          /*�ӿ�Ϊ��*/
    IGMP_ERR_MULTIADDR_INVALID,                /*�ಥ��ַ��Ч*/
    IGMP_ERR_CFGINFO_INVALID,                  /*������Ϣ��Ч*/
    IGMP_ERR_MULTIADDR_FORBID,                 /*��ֹ���øöಥ��ַ*/
    IGMP_ERR_INVALIDOPT,                       /*��Ч�Ĳ���*/

    IGMP_ERR_END                               /*�������룬���ڴ��ֶ�֮ǰ��Ӵ�����*/
}IGMP_ERRCODE_INC_E;

extern ULONG gulURptPeriod;                /*������������*/

typedef struct tagIGMP_DEBUG
{
    ULONG ulDstAddr;                        /*IGMP���淢�͵�Ŀ�ĵ�ַ*/
    ULONG ulReportType;                     /*IGMP���������*/
    ULONG ulGroupCount;                     /*IGMP�������������Ŀ*/
    Igmpv3_Report_GrpRec_S groupRecord;     /*���¼*/
    IPMULTI_SOURCELIST_S pstSourceList;     /*���¼�е�Դ��ַ*/
}IGMP_DEBUG_S;

enum enumIGMPDiscardType
{
    IGMP_DISCARD_INTERFACE_VALID = 0,       /*0���ӿ���Ч*/
    IGMP_DISCARD_WRONG_TYPE,                /*1���������͵�IGMP����*/
    IGMP_DISCARD_MBUF_LENGTH_WRONG,         /*2�����ĳ��Ȳ��Ϸ�*/
    IGMP_DISCARD_MULTIADDR_INVALID,   /*3��IGMP�����еĶಥ��ַ���Ϸ�*/
    IGMP_DISCARD_CREATE_TIMER_FAIL,         /*4  ������ʱ��ʧ��*/

    /*Ҫ�������ʱ������IGMP_DISCARD_UNKNOW_ERRORǰ���*/
    IGMP_DISCARD_UNKNOW_ERROR               /*δ֪�Ĵ�������*/
};

enum enumIGMPEventType
{   
    IGMP_JOINGROUP,
    IGMP_LEAVEGROUP,
    IGMP_ALLOW_NEW,
    IGMP_BLOCK_OLD,
    IGMP_SETMULTIIF,
    IGMP_SETMULTITTL,
    IGMP_SETMULTILOOP,
    IGMP_ERR_JOINGROUP,
    IGMP_ERR_LEAVEGROUP,
    IGMP_ERR_WRONGPARAM,
    IGMP_ERR_UNKNOWERROR,
    IGMP_ERR_MEMORY,
    IGMP_WARNING_VERSION_CHANGE,
    IGMP_WARNING_MSGTYPE_INVALID,
    IGMP_WARNING_IF_INVALID
};

typedef struct tagIGMP_SHELLCALLBACK
{
    VOID(*pfIGMP_DebugOutput)(CHAR *pszInfo);
}IGMP_SHELLCALLBACK_S;

/* IGMP������Ϣ����ص����� */
extern IGMP_SHELLCALLBACK_S g_stIGMPShellCallbackFunc;


/* IGMP src ip callback function. */
extern IGMP_GET_SRC_IP_HOOK g_stIGMPSrcIPCallbackFunc;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
