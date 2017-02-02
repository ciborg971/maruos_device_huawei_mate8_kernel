/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_report.h
*
*  Project Code: VISPV100R007
*   Module Name: igmp  
*  Date Created: 2008-04-11
*        Author: zengshaoyang62531
*   Description: igmp reportͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-11   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_REPORT_H_
#define _IGMPV3_REPORT_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

typedef VOID (*IGMP_HOOK_FOR_SEND)();

    
/*��ʱ����ʱ��Ļص��������������*/
typedef struct tagIGMPCALLBACK
{
    ULONG ulIfIndex;             /* �ӿ����� */
    ULONG ulGrpAddr;             /* ���ַ */
    ULONG ulTimerType;           /* ��ʱ������ */
}IGMPCALLBACK_S;

/*igmp���Ĵ���mbufʱ,����·��Ԥ���ĳ���*/
#define IGMP_MBUF_LINKHDR 40

#define IGMP_REPORT_MODE_IN 1         /*is_in*/
#define IGMP_REPORT_MODE_EX 2         /*is_ex*/
#define IGMP_REPORT_TO_IN   3         /*to_in*/
#define IGMP_REPORT_TO_EX   4         /*to_ex*/
#define IGMP_REPORT_ALLOW_NEW 5       /*allow_new*/
#define IGMP_REPORT_BLOCK_OLD 6       /*block_old*/

#define IGMP_TIMERTYPE_IF       1       /*��ʱ�����ͣ��ӿڶ�ʱ��*/
#define IGMP_TIMERTYPE_GRP      2       /*��ʱ�����ͣ��鶨ʱ��1*/
#define IGMP_TIMERTYPE_GRPSRC   3       /*��ʱ�����ͣ��鶨ʱ��2*/
#define IGMP_TIMERTYPE_STATACHG 4       /*��ʱ�����ͣ�״̬�ı䶨ʱ��*/
#define IGMP_TIMERTYPE_VER1     5       /*��ʱ�����ͣ�IGMPV1�汾��ʱ��*/
#define IGMP_TIMERTYPE_VER2     6       /*��ʱ�����ͣ�IGMPV2�汾��ʱ��*/

#define IGMP_MASK_NULL         0x0     /* �ձ�� */
#define IGMP_MASK_CUR_STATE    0x01    /* report current-state */
#define IGMP_MASK_ALLOW_NEW    0x02    /* report source as allow-new */
#define IGMP_MASK_BLOCK_OLD    0x04    /* report source as block-old */
#define IGMP_MASK_TO_IN        0x08    /* report source as to_in */
#define IGMP_MASK_TO_EX        0x10    /* report source as to_ex */
#define IGMP_MASK_STATE_TAG1   0x20    /* TAG1��ǣ�״̬�ı�ʱ�����ڱ�Ƕಥ��EX��IN�б����TAG2״̬�����ͳ�
                                        * Ա���棬�����IncludeList�����Դ��ַA�ȴ���TAG1�ִ���TAG2����Դ��ַ
                                        * A���÷��ͳ�Ա���棬���ֻ����TAG1����Ҫ��A����BLOCK_OLD���棬���ֻ
                                        * ����TAG2����Ҫ����ALLOW_NEW���棬����ExcludeList�����������෴�����
                                        */
#define IGMP_MASK_STATE_TAG2   0x40    /* TAG2��� */

#define IGMP_MASK_IF_STATE     0x80    /* report current-state per interface */
#define IGMP_MASK_SNDRPT_IMMEDIATELY    0x100   /* �������ͱ����� */

#define IGMP_MASK_STATE_TX   (IGMP_MASK_STATE_TAG1 | IGMP_MASK_STATE_TAG2)
#define IGMP_MASK_PENDING    (IGMP_MASK_CUR_STATE | IGMP_MASK_ALLOW_NEW | IGMP_MASK_BLOCK_OLD)

/*֪���ಥ��ַ*/
#define IGMP_ALL_HOSTS      0xE0000001L  /*224.0.0.1*/
#define IGMP_ALL_ROUTER     0xE0000002L /*224.0.0.2*/
#define IGMPV3_ALL_ROUTER   0xe0000016L /*224.0.0.22*/

#define IGMP_HDRLEN        8      /*igmp��Ա�������С��ͷ���ȣ�����IGMPv3�����������¼*/
#define IGMP_GRPREC_HDRLEN 8      /*igmpv3��С�����¼���ȣ�������Դ��ַ*/

#define IPADDRSPACE 2
#define IGMPPKTSPACE(ulCount) ((ulCount) << 2)

#define IGMP_CLEARTAG(start,srclist,mask)\
{\
    for ((srclist) = (start);(srclist) != NULL;(srclist) = (srclist)->pstNextSourceAddr)\
    {\
        (srclist)->ulReportTag &= ~(mask);\
    }\
}

/*IGMPV3�������¼*/
typedef struct tagIgmpv3_Report_GrpRec
{
    UCHAR ucType;                     /*type*/
    UCHAR ucAux_data_len;             /*�������ݳ���*/
    USHORT usNum_srcs;                /*Դ��ַ��Ŀ*/ 
    ULONG ulGrp_addr;                 /*���ַ*/
    ULONG ulSrcs[1];                  /*Դ��ַ,�������Ϳ��Զ���0��Ԫ�ص����飬ʵ�ֱ䳤����*/
}Igmpv3_Report_GrpRec_S;

/*IGMPV3�����ײ�*/
typedef struct tagIgmpv3_Report_Hdr
{
    UCHAR ucType;                      /*����*/
    UCHAR ucResv;                      /*reserved*/
    USHORT usChkSum;                   /*checksum*/
    USHORT usReserved;                 /*reserved*/
    USHORT usNum_Grp_rec;              /*numbers of group records*/
    Igmpv3_Report_GrpRec_S stGrpRec[1];/*��װ����ʱ����֤�ڴ��������˴�����һ��Ԫ�ؼ���*/
}Igmpv3_Report_Hdr_S;

typedef struct tagROUTEALERTOPTION
{
    ULONG ulIpAddr;              /*ȡΪ��ֵ*/
    UCHAR ucOptName;             /*ѡ����*/
    UCHAR ucOptLen;              /*ѡ���*/
    USHORT usOptVar;             /*ѡ������*/
}ROUTEALERTOPTION_S;

#define IGMP_ROUTE_ALERT 148

extern ULONG IGMPV1V2_Send_Report(IPMULTI_S *pstIPM, UCHAR ucType);
extern ULONG IGMPV3_Send_CurrentStateReport(IPMULTI_S *pstIPM,ULONG ulUseRecord);
extern ULONG IGMPV3_Send_Report(IPMULTI_S *pstIPM, IPMULTI_SOURCELIST_S *pstTagList,
            ULONG ulCount, ULONG ulMask, ULONG ulType, ULONG ulIpAddr);
extern VOID IGMPV3_Send_StateChgReport(IPMULTI_S *pstIPM,ULONG *pulRet);
extern VOID IGMP_Cancel_All_Reports(IPIFNET_S *pstIPCtl,ULONG ulCancel_StaChg);
extern VOID Igmp_Clean_Recorded_Sources(IPMULTI_S *pstIPM);
extern ULONG IGMP_Compute_Chksum(UCHAR *pucBuff,LONG llength,USHORT *usChksum);
extern VOID IGMP_FillInIPHead(IP_S *pstIPHead,ULONG ulDst,ULONG ulSrc,USHORT usTotLen);
extern IPMULTI_SOURCELIST_S* Igmp_Get_Sources(Igmpv3_Report_GrpRec_S *pstGrp, 
            IPMULTI_SOURCELIST_S *pstSrcList, ULONG ulMask, ULONG ulMax, ULONG ulStart, 
            ULONG *ulCnt);
extern IPMULTI_S* IGMP_SearchGroupOnIpIfnet(IPIFNET_S *pstIpCtl,ULONG ulGrpAddr);
extern VOID IGMP_Send_SrcListChg_Report(IPMULTI_S *pstIPMulti, ULONG ulPlusTag);
extern ULONG IGMP_SourceListIsEmpty(IPMULTI_SOURCELIST_S *pstSrcList);
extern VOID IGMP_TimeOutCallBack(VOID *pstTimerArg,ULONG *ulReTransFlg);
extern VOID IGMP_Delete_MultiGrp(IPMULTI_S *pstGrp);
extern VOID IGMP_Free_MultiList(IPMULTI_LIST_S *pstMultiList,IPIFNET_S *pstIpctl);

#ifdef __cplusplus
}
#endif /* __cplusplus */
    
#endif /* _IGMPV3_REPORT_H_ */

