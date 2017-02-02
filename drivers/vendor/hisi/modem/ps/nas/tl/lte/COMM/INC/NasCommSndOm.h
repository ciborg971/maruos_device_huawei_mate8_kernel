

#ifndef __NASCOMMSNDOM_H__
#define __NASCOMMSNDOM_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "LPSCommon.h"
#include  "NasLmmPubMTimer.h"
#include  "NasEsmPublic.h"
#include  "NasERabmPublic.h"
/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_LMM_OM_TI_ENUM
 ö��˵��  : MM�����в���״̬����״̬������ʱ������
             BOUNDARY_START����ʶ��ģ�鶨ʱ���ڶ�ʱ�����е���ʼ�±�;
             BOUNDARY_END����ʶ��ģ�鶨ʱ���ڶ�ʱ�����еĽ����±�;
             ����ģ��Ķ�ʱ��������Ҫ�����ڸ�����Ӧ��������.
*****************************************************************************/
enum LNAS_OM_TI_MSG_ENUM
{
    /*****************************************************************
      EMMģ�鶨ʱ���ڴ˶���
    *****************************************************************/

    /*========== ������ʱ�� ===================*/
    TI_LNAS_EMM_STATE_NO_TIMER           = PS_MSG_ID_EMM_TO_EMM_OM_BASE,    /* �ȶ�״̬���޶�ʱ�� */
    TI_LNAS_EMM_STATE_T3440                      ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_STATE_DEL_FORB_TA_PROID          ,            /* ɾ����ֹ��TA */ /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    /*========== PUBģ�鶨ʱ�� ===================*/
    TI_LNAS_LMM_TIMER_WAIT_USIM_CNF               ,                              /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_LMM_TIMER_WAIT_USIM_READY_START       ,                              /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== MRRC ģ�鶨ʱ�� ==============*/
    TI_LNAS_EMM_STATE_MRRC_BOUNDARY_START        ,           /* MRRC ��ʱ����ʼ�߽� */
    TI_LNAS_EMM_MRRC_WAIT_RRC_CONN_CNF           ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_MRRC_WAIT_RRC_REL_CNF            ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== ATTACH ģ�鶨ʱ�� ============*/
    TI_LNAS_EMM_STATE_REG_BOUNDARY_START         ,           /* REG ��ʱ����ʼ�߽� */
    TI_LNAS_EMM_T3410                            ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_T3411                            ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
     /*TI_LNAS_EMM_T3402                          ,*/
    TI_LNAS_EMM_WAIT_ESM_PDN_RSP                 ,           /*�ȴ�ESM��PDN��Ӧ*//*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_WAIT_ESM_BEARER_CNF              ,           /*�ȴ�ESM�ĳ�����Ӧ*//*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_WAIT_RRC_DATA_CNF                ,           /*�ȴ�RRCֱ����Ϣ����ȷ��*//*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== DETACH ģ�鶨ʱ�� ============*/
    TI_LNAS_EMM_STATE_DEREG_BOUNDARY_START       ,           /* DEREG ��ʱ����ʼ�߽� *//*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_T3421                            ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== TAU ģ�鶨ʱ�� ===============*/
    TI_LNAS_EMM_STATE_TAU_BOUNDARY_START         ,           /* TAU ��ʱ����ʼ�߽� */
    TI_LNAS_EMM_STATE_TAU_T3430                  ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_STATE_TAU_T3411                  ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== SERVICE ģ�鶨ʱ�� ===========*/
    TI_LNAS_EMM_STATE_SERVICE_BOUNDARY_START     ,           /* SERVICE ��ʱ����ʼ�߽� */
    TI_LNAS_EMM_STATE_SERVICE_T3417              ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_STATE_SERVICE_T3417_EXT          ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_STATE_SERVICE_T3442              ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== PLMN ģ�鶨ʱ�� ==============*/
    TI_LNAS_EMM_STATE_PLMN_BOUNDARY_START        ,           /* PLMN ��ʱ����ʼ�߽� */
    TI_LNAS_EMM_WAIT_MMC_START_CNF_TIMER         ,
    TI_LNAS_EMM_WAIT_RRC_START_CNF_TIMER         ,
    TI_LNAS_EMM_WAIT_MMC_STOP_CNF_TIMER          ,
    TI_LNAS_EMM_WAIT_RRC_STOP_CNF_TIMER          ,

    /*========== AUTH ģ�鶨ʱ�� ==============*/
    TI_LNAS_EMM_STATE_AUTH_BOUNDARY_START        ,           /* AUTH ��ʱ����ʼ�߽� */
    TI_LNAS_EMM_T3418                            ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_T3420                            ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== SUSPEND��ʱ�� ================*/
    TI_LNAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER   ,                          /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_WAIT_SUSPEND_END_TIMER           ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER   ,                          /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER   ,                       /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/


    /*========== RESEUME��ʱ�� ================*/
    TI_LNAS_EMM_RRCRSM_WAIT_OTHER_RESUME_RSP_TIMER     ,                         /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_WAIT_SYS_INFO_IND_TIMER         ,                                /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_SYSCFGRSM_WAIT_OTHER_RESUME_RSP_TIMER,                           /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== SYSCFG�Ķ�ʱ�� ============================*/
    TI_LNAS_EMM_STATE_WAIT_SYSCFG_CNF_TIMER,                                     /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    TI_LNAS_EMM_STATE_TI_BUTT                    ,

    /*========== MMC�Ķ�ʱ�� ============================*/
    /*========== PLMN_SRCH�Ķ�ʱ�� ============================*/
    TI_LNAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER,                                 /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    TI_LNAS_EMMC_STATE_TI_BUTT                    ,

    /*========== END ====================================*/
    LNAS_LMM_STATE_TI_BUTT,

    /*=================== EMM�Ķ�ʱ�� ===================*/

    /*========== ATTACH ģ�鶨ʱ�� ============*/
    /*========== DETACH ģ�鶨ʱ�� ============*/
    /*========== TAU ģ�鶨ʱ�� ===============*/
    TI_LNAS_EMM_PTL_T3412                        ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_PTL_T3402                        ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/
    TI_LNAS_EMM_PTL_T3423                        ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== AUTH ģ�鶨ʱ�� ===============*/
    TI_LNAS_EMM_PTL_T3416                        ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    /*========== �ػ���ʱ�� ===================*/
    TI_LNAS_EMM_PTL_SWITCH_OFF_TIMER             ,                               /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/


    TI_LNAS_EMM_PTL_TI_BUTT                      ,

    /*========== MMC�Ķ�ʱ�� ==================*/
    LNAS_LMM_PTL_TI_BUTT,

    /*****************************************************************
      ESMģ�鶨ʱ���ڴ˶���
    *****************************************************************/



    /* �Ƶ�pubmom.h�� */
};
typedef VOS_UINT32 LNAS_OM_TI_MSG_ENUM_UINT32;

/*****************************************************************************
 ö����    : LNAS_OM_DEBUG_MSG_ENUM_UINT32
 ö��˵��  : LNAS��ģ���ά�ɲ���ϢID, NAS���п�ά�ɲ���ϢID�ڴ˶���
*****************************************************************************/
enum LNAS_OM_DEBUG_MSG_ENUM
{
    ID_NAS_LMM_OM_LOG_SET_REG_DOMAIN = TL_DBG_MSG_ID_LTE_NAS_BASE + 0x00,       /*_H2ASN_MsgChoice  NAS_EMM_TIMER_INFO_STRU*/

    LNAS_OM_DEBUG_MSG                = TL_DBG_MSG_ID_LTE_NAS_BASE + 0x80
};
typedef VOS_UINT32 LNAS_OM_DEBUG_MSG_ENUM_UINT32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/


typedef struct
{
    LNAS_OM_TI_MSG_ENUM_UINT32          enMsgId;            /*_H2ASN_MsgChoice_Export LNAS_OM_TI_MSG_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LNAS_OM_TI_MSG_ENUM_UINT32
    ****************************************************************************/
}LNAS_OM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    LNAS_OM_INTERFACE_MSG_DATA           stMsgData;
} NasCommSndOm_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/




#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasCommPrint.h */
