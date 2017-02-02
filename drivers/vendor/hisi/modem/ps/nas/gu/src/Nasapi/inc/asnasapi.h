
#ifndef _AS_NAS_API_H_
#define _AS_NAS_API_H_

#include "product_config.h"
#include "Nasrrcinterface.h"
#include "TtfDrvInterface.h"
/* Added by wx270776 for OM�ں�, 2015-7-24, begin */
#include "NasMntn.h"
/* Added by wx270776 for OM�ں�, 2015-7-24, end */

/* Determine if a C++ compiler is being used.  If so, ensure that standard
   C is used to process the API information.  */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                                 /* __cpluscplus                              */
#endif                                                                                 /* __cpluscplus                              */

#pragma pack(4)


/* Define API return values */
#define AS_SUCCESS                      0                                              /* As����ɹ�                                */
#define AS_RB_NO_EXIST                  1                                              /* RbId������                                */
#define AS_DATA_LENGTH_ERR              2                                              /* ���ݵĳ��Ȳ�ƥ��                          */
#define AS_NO_MEMORY                    3                                              /* As�����ڴ�ʧ��                            */
#define AS_RB_MODE_ERR                  4                                              /* RBģʽ��ƥ��                              */
#define AS_RAB_INFO_ERR                 5                                              /* ���е�RB������ͬһ��RAB����U_CsDomainSync
                                                                                        * DataReq                                   */
#define AS_SEND_FAILED                  6                                              /* AS����ʧ��                                */
#define AS_GENERAL_ERR                  7                                              /* ��������                                  */
#define AS_PARA_MISMATCH                8                                              /* ������ƥ��                                */
#define AS_VOS_ERR                      9                                              /* ASʹ��VOSʱ�����쳣                       */


/* RR_DATA_IND_FUNC��ucICResult�ĺ궨�� */
#define IC_RSLT_BOTH_NO_START           0x00                                           /* ���ܺ������Ա�����δ����                  */
#define IC_RSLT_CIPH_START              0x01                                           /* ��������                                  */
#define IC_RSLT_INTRG_START             0x02                                           /* �����Ա�������                            */


/* As_RabInfoRsp������ulResult�ĺ궨�� */
#define AS_RAB_RSP_OK                   0                                              /* ���Խ���                                  */
#define AS_RAB_RSP_NG                   1                                              /* ���ܽ���                                  */


/* RLCʹ�õĺ궨�� */
#define NAS_DATA_SUCCESS                0                                              /* Used by parameter Err                     */
#define NAS_DATA_ERR                    1                                              /* Used by parameter Err                     */



typedef struct paging_info_stru
{
    VOS_UINT32                   ulCnDomainId;                                              /* CN Domain ID                              */
    VOS_UINT32                   ulPagingType;                                              /* Ѱ����Ϣ����                              */
    VOS_UINT32                   ulPagingCause;                                             /* ��Ϣ�е�Paging Cause                      */
    VOS_UINT32                   ulPagingRecordTypeId;                                      /* ��Ϣ�е�Paging Recorder Id                */
}PAGING_INFO_STRU;


typedef struct sys_info_stru
{
    VOS_UINT32                          bitOpPlmnId     : 1;
    VOS_UINT32                          bitOpCsDrx      : 1;
    VOS_UINT32                          bitOpPsDrx      : 1;
    VOS_UINT32                          bitSpare        : 29;
    RRC_PLMN_ID_STRU        PlmnId;                                                    /* ��С��PLMN ID                             */
    VOS_UINT32                   ulCsDrxLength;                                             /* CS��DRX����ϵ��                           */
    VOS_UINT32                   ulPsDrxLength;                                             /* PS��DRX����ϵ��                           */
    VOS_UINT8                           ucCnCommonSize;     /* CN Common��Ϣ���ֽڳ���    */
    VOS_UINT8                           aucCnCommonInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];
    VOS_UINT8                           ucCsInfoSize;       /* CS�������Ϣ���ֽڳ���     */
    VOS_UINT8                           aucCsInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];
    VOS_UINT8                           ucPsInfoSize;       /* PS�������Ϣ���ֽڳ���     */
    VOS_UINT8                           aucPsInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];
    VOS_UINT8                           aucReserve1[1];     /* ���� */
}SYSINFO_STRU;


typedef struct idnns_stru
{
    VOS_UINT8                   ucIdnnsType;                                               /* IDNNS����                                 */
    VOS_UINT8                   ucEnterPara;                                               /* ��������IDNNS�Ĳ���                       */
}IDNNS_STRU;


typedef struct security_info_stru
{
    VOS_UINT32                  ulRptMode;                                                  /* ����ģʽ                                  */
    VOS_UINT32                  ulCsCipherStatus;                                           /* CS��ǰ��������״̬                      */
    VOS_UINT32                  ulPsCipherStatus;                                           /* PS��ǰ��������״̬                      */
    VOS_UINT32                  ulIntegCmd;                                                 /* �����Ա�����������                        */
    /* added by weijiantao 05-04-15 begin: Ϊ�˶�ӦMM/GMM��AGENT�ϱ������㷨 */
    VOS_UINT32                  ulCsCipherAlgor;                                            /* CS�����¼����㷨, ����CS�������������Ч  */
    VOS_UINT32                  ulPsCipherAlgor;                                            /* PS�����¼����㷨, ����PS�������������Ч  */
    /* added by weijiantao 05-04-15 end */
}SECURITY_INFO_STRU;


typedef struct attach_info_stru
{
    VOS_UINT32                   ulCnt;                                                     /* CN Domain����                             */
    struct
    {
        VOS_UINT32               ulCnDomainId;                                              /* ��������ָCN Domain                       */
        VOS_UINT32               ulAttach;                                                  /* Attach��Deattach��־                      */
    }aAttachInfo[RRC_NAS_MAX_CN_DOMAIN];
}ATTACH_INFO_STRU;


typedef struct usim_valid_info_stru
{
    VOS_UINT32                   ulCnt;                                                     /* CN Domain����                             */
    struct
    {
        VOS_UINT32               ulCnDomainId;                                              /* ��������ָCN Domain                       */
        VOS_UINT32               ulUsimValid;                                               /* USIM��Ч��־                              */
    }aUsimInfo[RRC_NAS_MAX_CN_DOMAIN];
}USIM_VALID_INFO_STRU;


typedef struct security_key_info_stru
{
    VOS_UINT32                   ulCnt;                                                     /* CN Domain����                             */
    struct
    {
        VOS_UINT32               ulCnDomainId;                                              /* ��������ָCN Domain                       */
        /* Modified by baizhihuai 2004.10.25 begin */
        /*VOS_UINT32             aulCk[4];*/
        /*VOS_UINT32             aulIk[4];*/
        VOS_UINT8               aucCk[16];                                                 /* Cipher Key                                */
        VOS_UINT8               aucIk[16];                                                 /* Integrity Key                             */
        /* Modified by baizhihuai 2004.10.25 end */
    }aKeyInfo[RRC_NAS_MAX_CN_DOMAIN];
}SECURITY_KEY_INFO_STRU;


typedef struct plmn_search_para_stru
{
    VOS_UINT32                   ulSearchType;                                              /* ��������                                  */
    VOS_UINT32                   ulPlmnIdNum;                                               /* PLMN ID����                               */
    RRC_PLMN_ID_STRU        aPlmnIdList[RRC_MAX_EQUPLMN_NUM+1];                        /* PlMN��ʶ                                  */
    VOS_UINT32                   ulForbLaNum;                                               /* ��ֹע�����ĸ���                          */
    RRC_FORB_LA_STRU        aForbLaList[RRC_MAX_FORBLA_NUM];                           /* ��ֹע�����б�                            */
}PLMN_SEARCH_PARA_STRU;


typedef struct plmn_list_stru
{
    VOS_UINT32                   ulHighPlmnNum;                                             /* ������PLMN�ĸ���                          */
    RRC_PLMN_ID_STRU        aHighPlmnList[RRC_MAX_HIGH_PLMN_NUM];                      /* ������PLMN�б�                            */
    VOS_UINT32                   ulLowPlmnNum;                                              /* ������PLMN�ĸ���                          */
    struct
    {
        RRC_PLMN_ID_STRU    PlmnId;                                                    /* PLMN ID                                   */
        VOS_INT32                lRscp;                                                     /* RSCP����ֵ                                */
    }aLowPlmnList[RRC_MAX_LOW_PLMN_NUM];                                               /* ������PLMN�б�                            */
}PLMN_LIST_STRU;


typedef struct plmn_search_result_stru
{
    VOS_UINT32                   ulSearchRlt;                                               /* �������                                  */
    PLMN_LIST_STRU          PlmnIdList;                                                /* �ϱ���PLMN ID�б�                         */
}PLMN_SEARCH_RESULT_STRU;


typedef struct equivalent_plmn_stru
{
    VOS_UINT32                   ulEquPlmnNum;                                              /* ��Ч��PLMN�ĸ���                          */
    RRC_PLMN_ID_STRU        aEquPlmnIdList[RRC_MAX_EQUPLMN_NUM + 1];                   /* ��Ч��PLMNID�б�                          */
} EQUIVALENT_PLMN_STRU;


typedef struct forbiden_la_list_stru
{
    VOS_UINT32                   ulForbLaNum;                                               /* ��ֹע�����ĸ���                          */
    struct
    {
        RRC_PLMN_ID_STRU    PlmnId;                                                    /* PlMN��ʶ                                  */
        VOS_UINT32               ulForbLac;                                                 /* ��ֹע������Ϣ                            */
    }aForbLaList[RRC_MAX_FORBLA_NUM];                                                  /* ��ֹע�����б�                            */
} FORBIDEN_LA_LIST_STRU;


typedef struct rab_status_info_stru
{
    VOS_UINT32                   ulOpId;
    VOS_UINT32                   ulRabChangeType;                                           /* RAB�Ĳ�������                             */
    VOS_UINT32                   ulRabCnt;                                                  /* ����RAB����������                         */
    struct
    {
        VOS_UINT32               ulRabId;                                                   /* RAB ID                                    */
        VOS_UINT32               ulCnDomainId;                                              /* ��RAB����CN Domain                        */
        VOS_UINT32               ulRbNum;                                                   /* ��RAB����RB����                           */
        VOS_UINT32               aulRbId[RRC_NAS_MAX_RB_PER_RAB];                           /* ��RAB����RB ID                            */
    }aRabInfo[RRC_NAS_MAX_RAB_SETUP];
}RAB_STATUS_INFO_STRU;


typedef struct rab_rsp_info_stru
{
    VOS_UINT32                   ulOpId;                                                    /* �뽨��RAB��INDԭ����ͬ                    */
    VOS_UINT32                   ulRabCnt;                                                  /* ����RAB����                               */
    struct
    {
        VOS_UINT32               ulCnDomainId ;                                             /* ����CN Domain                             */
        VOS_UINT32               ulRabId;                                                   /* RAB ID                                    */
        VOS_UINT32               ulPppValid;                                                /* �Ƿ����PPPЭ��                           */
        VOS_UINT32               ulDeliveryErrSdu;
    }aRabInfo[RRC_NAS_MAX_RAB_SETUP];
}RAB_RSP_INFO_STRU;


typedef struct sync_info_stru
{
    VOS_UINT32                   ulRabCnt;                                                  /* ��Ҫͬ��RAB����                           */
    struct
    {
        VOS_UINT32               ulRabId;                                                   /* RAB ID                                    */
        VOS_UINT32               ulCnDomainId;                                              /* ��RAB������                               */
        VOS_UINT32               ulRabSyncInfo;                                             /* ��RAB��ͬ��ָʾ                           */
    }NasSyncInfo[RRC_NAS_MAX_RAB_SETUP];
}SYNC_INFO_STRU;


typedef struct rab_sc_info_stru
{
    VOS_UINT32                   ulRabCnt;                                                  /* RAB����                                   */
    struct
    {
        VOS_UINT32               ulCnDomainId;                                              /* ����CN Domain                             */
        VOS_UINT32               ulRabId;                                                   /* RAB ID                                    */
    }aRab[RRC_NAS_MAX_RAB_SETUP];
    VOS_UINT32                   ulStatus;                                                  /* RAB��Ӧ��������                           */
}RAB_SC_INFO_STRU;


typedef struct qos_info_stru
{
    VOS_UINT32                   ulRabCnt;                                                  /* RAB����                                   */
    struct
    {
        VOS_UINT32               ulCnDomainId;                                              /* ����CN Domain                             */
        VOS_UINT32               ulRabId;                                                   /* RAB ID                                    */
        VOS_UINT32               ulPppValid;                                                /* �Ƿ����PPPЭ��                           */
        VOS_UINT32               ulDeliveryErrSdu;                                          /* �����SDU�Ĵ���ģʽ                       */
    }aRab[RRC_NAS_MAX_RAB_SETUP];
}QOS_INFO_STRU;

typedef struct avail_plmn_stru
{
    VOS_UINT32                  ulAvailPlmnNum;
    RRC_PLMN_ID_STRU            astAvailPlmnIdList[NAS_RRC_MAX_AVAILPLMN_NUM];       /* PlMN��ʶ */
}AVAIL_PLMN_STRU;


/* Define the function prototypes of the AS layer API */
VOS_INT32 NAS_CsDomainDataReq(VOS_INT8  cRbId,VOS_UINT32 ulDataLength,VOS_UINT8   *pucData);

VOS_INT32 NAS_PsDomainTcDataReq(VOS_UINT8 ucRbId, VOS_UINT32 ulDataBitLen, TTF_MEM_ST *pstDataMem);

VOS_INT32 As_RrRelReq(VOS_UINT8 ucCnDomain,RRC_CELL_BAR_ENUM_UINT32 enBarValidFlg);

VOS_INT32 As_RrDataReq(VOS_UINT8, VOS_UINT8, VOS_UINT32, VOS_INT8*);
VOS_INT32 As_RabInfoRsp(VOS_UINT32 ulResult,RAB_RSP_INFO_STRU* pRabInfo);
VOS_INT32 As_RabQosUpdate(QOS_INFO_STRU*);

VOS_INT32 As_RrEstReq(
    VOS_UINT32                          ulOpId,
    VOS_UINT8                           ucCnDomain,
    VOS_UINT32                          ulEstCause,
    VOS_UINT32                          ulCallType,
    IDNNS_STRU                          *pIdnnsInfo,
    RRC_PLMN_ID_STRU                    *pstPlmnId,
    VOS_UINT32                          ulSize,
    VOS_INT8                            *pFisrstMsg
);

/* Define the callback function prototypes of the NAS layer API */
typedef VOS_VOID    NAS_CALLBACK_TYPE;

typedef NAS_CALLBACK_TYPE (*EXT_MemFreeFunc)( VOS_UINT32 ulLabel, VOS_VOID *p );
typedef NAS_CALLBACK_TYPE (*RR_DATA_IND_FUNC)(VOS_UINT8 ucCnDomain, VOS_UINT32 ulSize, VOS_UINT8 *pData);
typedef NAS_CALLBACK_TYPE (*PAGING_IND_FUNC)(PAGING_INFO_STRU *pPagingInfo);
typedef NAS_CALLBACK_TYPE (*SYSTEM_INFO_IND_FUNC)(SYSINFO_STRU *pSysInfo);
typedef NAS_CALLBACK_TYPE (*RR_EST_CNF_FUNC)(VOS_UINT32 ulOpId, VOS_UINT32 ulResult,VOS_UINT32 ulCnDomainId);
typedef NAS_CALLBACK_TYPE (*RR_REL_IND_FUNC)(VOS_UINT8 ucCnDomain, VOS_UINT32 ulRelCause, VOS_UINT32 ulRrcConnStatus);
typedef NAS_CALLBACK_TYPE (*SECURITY_IND_FUNC)(VOS_UINT8);
typedef NAS_CALLBACK_TYPE (*PLMN_SEARCH_CNF_FUNC)(PLMN_SEARCH_RESULT_STRU *pSearchResult);
typedef NAS_CALLBACK_TYPE (*PLMN_LIST_IND_FUNC)(PLMN_LIST_STRU *pPlmnList);
typedef NAS_CALLBACK_TYPE (*COVERAGE_LOST_IND_FUNC)( VOS_UINT32 ulRptMode );
typedef NAS_CALLBACK_TYPE (*RAB_STATUS_INFO_IND_FUNC)(RAB_STATUS_INFO_STRU *pRabInfo);
typedef NAS_CALLBACK_TYPE (*RR_SYNC_IND_FUNC)(SYNC_INFO_STRU *pSyncInfo);
typedef NAS_CALLBACK_TYPE (*RAB_SC_IND_FUNC)(RAB_SC_INFO_STRU *pScInfo);
typedef NAS_CALLBACK_TYPE (*RR_POWER_OFF_CNF_FUNC)(VOS_VOID);
typedef NAS_CALLBACK_TYPE (*RR_START_CNF_FUNC)(VOS_VOID);
typedef NAS_CALLBACK_TYPE (*RRMM_AC_INFO_CHANGE_IND_FUNC)( VOS_UINT32  ulAcChangeInd );


typedef struct imported_func_list_stru
{

    struct
    {
        RR_DATA_IND_FUNC                RrDataIndFunc;
        PAGING_IND_FUNC                 RrPagingIndFunc;
        SYSTEM_INFO_IND_FUNC            RrSysInfoIndFunc;
    }SigDataTransfer;

    struct
    {
        RR_EST_CNF_FUNC                 RrEstCnfFunc;
        RR_REL_IND_FUNC                 RrRelIndFunc;
        SECURITY_IND_FUNC               RrSecurityIndFunc;
        RR_POWER_OFF_CNF_FUNC           RrPowerOffCnfFunc;
        RR_START_CNF_FUNC               RrStartCnfFunc;
    }SigConnCtrl;

    struct
    {
        PLMN_SEARCH_CNF_FUNC            PlmnSearchCnfFunc;
        PLMN_LIST_IND_FUNC              PlmnListIndFunc;
        COVERAGE_LOST_IND_FUNC          CoverageLostIndFunc;
    }PlmnSearch;

    struct
    {
        RAB_STATUS_INFO_IND_FUNC        RabStatusIndFunc;
        RR_SYNC_IND_FUNC                RrSyncIndFunc;
        RAB_SC_IND_FUNC                 RabScIndFunc;
    }RbMng;

    struct
    {
        RRMM_AC_INFO_CHANGE_IND_FUNC    RrAcInfoChangeIndFunc;
    }RrcInfoInd;

    struct{
        EXT_MemFreeFunc                 ExtMemFree;
    }ext_memfree_api;

}IMPORTED_FUNC_LIST_STRU;

extern IMPORTED_FUNC_LIST_STRU          ImportFunc;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                                 /* __cpluscplus                              */

#endif
