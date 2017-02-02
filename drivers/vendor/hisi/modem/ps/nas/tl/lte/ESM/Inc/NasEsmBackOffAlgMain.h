

#ifndef __NASESMBACKOFFALGMAIN_H__
#define __NASESMBACKOFFALGMAIN_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LNvCommon.h"
#include "LNasNvInterface.h"
#include "AppEsmInterface.h"
#include "NasEsmPublic.h"
//#include "AppNasComm.h"


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
  2 Macro
*****************************************************************************/

/* ��Чֵ��غ궨�� */

#define NAS_ESM_NO                             0
#define NAS_ESM_YES                            1

#define NAS_BACKOFF_NULL                       0
#define NAS_BACKOFF_NULL_PTR                  (0L)

#define NAS_BACKOFF_SUCC                       0
#define NAS_BACKOFF_FAIL                       1

#define NAS_BACKOFF_NVIM_SUCC                  0
#define NAS_BACKOFF_NVIM_FAIL                  1

#define NAS_BACKOFF_ALG_INVALID                0
#define NAS_BACKOFF_ALG_VALID                  1

#define NAS_BACKOFF_BIT_NO_SILT                0
#define NAS_BACKOFF_BIT_SILT                   1

#define NAS_BACKOFF_APN_ENTITY_MAX_NUM         6

#define NAS_BACKOFF_FX_DIVIDE_MIN_VALUE        2

#define NAS_BACKOFF_FX_MIN_VALUE               4

#define NAS_BACKOFF_FORBID_TIMER_MAX_VALUE    (15*60*1000)
#define NAS_BACKOFF_1HOUR_VALUE               (60*60*1000)

#define NAS_BACKOFF_PDP_CAUSE_NULL             0

#define NAS_BACKOFF_PDP_PERM_CAUSE_DEFAULT_NUM 7
#define NAS_BACKOFF_PDP_TEMP_CAUSE_DEFAULT_NUM 8
/*��װ��ӡLOG�ĺ�*/
#ifdef PS_ITT_PC_TEST
#define NAS_BACKOFF_INFO_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String)
 */
#define NAS_BACKOFF_INFO_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1 )
 */
#define NAS_BACKOFF_INFO_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1, (long)Para2)
 */
#define NAS_BACKOFF_NORM_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String)
 */
#define NAS_BACKOFF_WARN_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String)
 */
#define NAS_BACKOFF_ERR_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String)
 */
#define NAS_BACKOFF_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1 )
 */
#define NAS_BACKOFF_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1, (long)Para2)
 */
#else
#define NAS_BACKOFF_INFO_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_INFO, String)
#define NAS_BACKOFF_INFO_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define NAS_BACKOFF_INFO_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define NAS_BACKOFF_NORM_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define NAS_BACKOFF_WARN_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_WARNING, String)
#define NAS_BACKOFF_ERR_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_ERROR, String)
#define NAS_BACKOFF_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define NAS_BACKOFF_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#endif



/*****************************************************************************
  3 Enum
*****************************************************************************/


/*****************************************************************************
�ṹ����    :NAS_BACKOFF_NETRAT_ENUM
ʹ��˵��    :Back-off�㷨֧�ֵĽ��뼼��
*****************************************************************************/
enum NAS_BACKOFF_NETRAT_ENUM
{
    NAS_BACKOFF_NETRAT_LTE  = 0x00,     /* LTE */
    NAS_BACKOFF_NETRAT_GU   = 0x01,     /* GU  */

    NAS_BACKOFF_NETRAT_ENUM_BUTT
};
typedef VOS_UINT32  NAS_BACKOFF_NETRAT_ENUM_UINT32;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_OPERATE_TYPE_ENUM
ʹ��˵��    :Back-off�㷨ʵ�������Ϣ����ö��
*****************************************************************************/
enum NAS_BACKOFF_OPERATE_TYPE_ENUM
{
    NAS_BACKOFF_OPERATE_TYPE_INIT       = 0,     /* ��ʼ�� */
    NAS_BACKOFF_OPERATE_TYPE_JUDGMENT   = 1,     /* �ж� */
    NAS_BACKOFF_OPERATE_TYPE_MAINTAIN   = 2,     /* ά�� */
    NAS_BACKOFF_OPERATE_TYPE_RESET      = 3,     /* ��λ */

    NAS_BACKOFF_OPERATE_TYPE_ENUM_BUTT
};
typedef VOS_UINT32  NAS_BACKOFF_OPERATE_TYPE_ENUM_UINT32;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_RESET_TYPE_ENUM
ʹ��˵��    :Back-off�㷨ʵ������ԭ��ö��
*****************************************************************************/
enum NAS_BACKOFF_RESET_CAUSE_ENUM
{
    NAS_BACKOFF_RESET_CAUSE_SWITCH_OFF    = 0,     /* �ػ� */
    NAS_BACKOFF_RESET_CAUSE_PLMN_CHANGE   = 1,     /* PLMN��� */

    NAS_BACKOFF_RESET_CAUSE_ENUM_BUTT
};
typedef VOS_UINT32  NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM
ʹ��˵��    :PDP������
*****************************************************************************/
enum NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM
{
    NAS_BACKOFF_PDP_ACTIVE_RESULT_SUCC       = 0X00,     /* �ɹ�     */
    NAS_BACKOFF_PDP_ACTIVE_RESULT_TIMER_EXP  = 0X01,     /* ��ʱ     */
    NAS_BACKOFF_PDP_ACTIVE_RESULT_CN_REJ     = 0X02,     /* ����ܾ� */

    NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM_BUTT
};
typedef VOS_UINT8  NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_APN_ENTITY_FLAG_ENUM
ʹ��˵��    :Back-off�㷨APNʵ���ʶ
*****************************************************************************/
enum NAS_BACKOFF_APN_ENTITY_FLAG_ENUM
{
    NAS_BACKOFF_APN_ENTITY_FLAG_INVALID = 0x00,     /* APNʵ�崦����Ч̬ */
    NAS_BACKOFF_APN_ENTITY_FLAG_VALID   = 0x01,     /* APNʵ�崦����Ч̬ */

    NAS_BACKOFF_APN_ENTITY_FLAG_BUTT
};
typedef VOS_UINT8  NAS_BACKOFF_APN_ENTITY_FLAG_ENUM_UINT8;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_STATE_ENUM
ʹ��˵��    :Back-off�㷨״̬ö��
*****************************************************************************/
enum NAS_BACKOFF_STATE_ENUM
{
    NAS_BACKOFF_STATE_INACTIVE = 0x00,     /* �㷨����δ����̬ */
    NAS_BACKOFF_STATE_ACTIVE   = 0x01,     /* �㷨���ڼ���̬ */

    NAS_BACKOFF_STATE_BUTT
};
typedef VOS_UINT8  NAS_BACKOFF_STATE_ENUM_UINT8;

/*****************************************************************************
�ṹ����    :NAS_ESM_BACKOFF_FOBID_TIMER_STATE_ENUM
ʹ��˵��    :�ͷ���ʱ��״̬ö��
*****************************************************************************/
enum NAS_BACKOFF_FOBID_TIMER_STATE_ENUM
{
    NAS_BACKOFF_FOBID_TIMER_STATE_STOP     = 0x00,  /* �ͷ���ʱ��δ���� */
    NAS_BACKOFF_FOBID_TIMER_STATE_RUNNING  = 0x01,  /* �ͷ���ʱ�������� */

    NAS_BACKOFF_FOBID_TIMER_STATE_BUTT
};
typedef VOS_UINT8  NAS_BACKOFF_FOBID_TIMER_STATE_ENUM_UINT8;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_PDP_REJ_TYPE_ENUM
ʹ��˵��    :Back-off�㷨ʵ��PDP�������ܾ�������
*****************************************************************************/
enum NAS_BACKOFF_PDP_REJ_TYPE_ENUM
{
    NAS_BACKOFF_PDP_REJ_TYPE_PERM_REJ  = 0X00,     /* ���þܾ� */
    NAS_BACKOFF_PDP_REJ_TYPE_TEMP_REJ  = 0X01,     /* ��ʱ�ܾ� */
    NAS_BACKOFF_PDP_REJ_TYPE_OTHER     = 0X02,     /* ����     */

    NAS_BACKOFF_PDP_REJ_TYPE_ENUM_BUTT
};
typedef VOS_UINT8  NAS_BACKOFF_PDP_REJ_TYPE_ENUM8;

/*****************************************************************************
  4 STRUCT
*****************************************************************************/

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_INIT_INFO_STRU
ʹ��˵��    :Back-off�㷨��ʼ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32   bitOpSimFxFlag   :1;  /* SIM���в����Ƿ���Ч                  */
    VOS_UINT32   bitOpRsv         :31; /* ����                                 */

    VOS_UINT8    ucSimFxIgnore;        /* Ignore��������ʧ�ܼ���USIM�е��޶�ֵ */
    VOS_UINT8    ucSimFxPerm;          /* Perm��������ʧ�ܼ���USIM�е��޶�ֵ   */
    VOS_UINT8    ucSimFxTemp;          /* Temp��������ʧ�ܼ���USIM�е��޶�ֵ   */
    VOS_UINT8    ucRsv;
} NAS_BACKOFF_INIT_INFO_STRU;

/*****************************************************************************
�ṹ����    :NAS_ESM_BACKOFF_OPERATION_TYPE_MSG_STRU
ʹ��˵��    :Back-off�㷨�ж���Ϣ���
*****************************************************************************/
typedef APP_ESM_APN_INFO_STRU  NAS_BACKOFF_JUDGMENT_PARA_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_OPERATION_TYPE_MSG_STRU
ʹ��˵��    :Back-off�㷨ά����Ϣ���
*****************************************************************************/
typedef struct
{
    APP_ESM_APN_INFO_STRU                    stApnInfo;      /* APN            */
    NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8      enPdpResult;    /* PDP������    */
    VOS_UINT8                                ucCnCause;      /* ����ܾ�ԭ��ֵ */
    VOS_UINT8                                ucRsv[2];       /* ����           */
} NAS_BACKOFF_MAINTAIN_PARA_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_QUERY_RESULT_STRU
ʹ��˵��    :Back-off�㷨��ѯ���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                ulIndex;     /* ��ѯ����APN���㷨ʵ���е����� */
    NAS_BACKOFF_STATE_ENUM_UINT8              enState;     /* ��ѯ����Back-off�㷨״̬ */
    NAS_BACKOFF_FOBID_TIMER_STATE_ENUM_UINT8  enTimeStatus;/* ��ѯ�����Ƿ��гͷ���ʱ�������еĽ�� */
} NAS_BACKOFF_QUERY_RESULT_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_TIMER_INFO_STRU
ʹ��˵��    :Back-off�㷨�ͷ���ʱ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32   ulTminLen; /* �ͷ���ʱ������ */
    VOS_UINT32   ulTmaxLen; /* �ͷ���ʱ������ */
} NAS_BACKOFF_TIMER_INFO_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACK_OFF_ALGORITHM_ENTITY_STRU
ʹ��˵��    :Back-off�㷨��������
*****************************************************************************/
typedef struct
{
    VOS_UINT8   ucFxIgnore; /* NV��USIM�����õĶ�Ӧignore������Fx */
    VOS_UINT8   ucFxPerm;   /* NV��USIM�����õĶ�Ӧperm������Fx   */
    VOS_UINT8   ucFxTemp;   /* NV��USIM�����õĶ�ӦTemp������Fx   */
    VOS_UINT8   ucRsv;

    VOS_UINT8   ucFbIgnore; /* ignore��������ֵFb */
    VOS_UINT8   ucFbPerm;   /* perm��������ֵFb   */
    VOS_UINT8   ucFbTemp;   /* temp��������ֵFb   */
    VOS_UINT8   ucRsv1;

    NAS_BACKOFF_TIMER_INFO_STRU   stFxIgnoreTimerInfo; /* Ignore�����µĶ�ʱ����Ϣ */
    NAS_BACKOFF_TIMER_INFO_STRU   stFxPermTimerInfo;   /* Perm�����µĶ�ʱ����Ϣ   */
    NAS_BACKOFF_TIMER_INFO_STRU   stFxTempTimerInfo;   /* Temp�����µĶ�ʱ����Ϣ   */
} NAS_BACKOFF_COMM_PARA_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_TIMER_STRU
ʹ��˵��    :Back-off�㷨�ͷ���ʱ��
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;      /* vos�����Timer Id   */
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enPara;      /* Timer����   */
    VOS_UINT8                           ucRsv[3];    /* ����   */
} NAS_BACKOFF_TIMER_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_INACTIVE_INFO_STRU
ʹ��˵��    :Back-off�㷨δ����̬ʵ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulFnIgnore;       /* �Ǽ���̬��Ignore��������ʧ�ܼ��� */
    VOS_UINT32  ulFnPerm;         /* �Ǽ���̬��Perm��������ʧ�ܼ��� */
    VOS_UINT32  ulFnTemp;         /* �Ǽ���̬��Temp��������ʧ�ܼ��� */
} NAS_BACKOFF_INACTIVE_INFO_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_ACTIVE_INFO_STRU
ʹ��˵��    :Back-off�㷨����̬ʵ��
*****************************************************************************/
typedef struct
{
    NAS_BACKOFF_TIMER_STRU    stBackoffTimer;  /* ����̬�³ͷ���ʱ����Ϣ */
} NAS_BACKOFF_ACTIVE_INFO_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_APN_ENTITY_STRU
ʹ��˵��    :Back-off�㷨APNʵ��
*****************************************************************************/
typedef struct
{
    APP_ESM_APN_INFO_STRU                   stApnInfo;      /* APN */
    NAS_BACKOFF_APN_ENTITY_FLAG_ENUM_UINT8  enValidFlag;    /* ��ǰʵ���Ƿ���Ч */
    NAS_BACKOFF_STATE_ENUM_UINT8            enState;        /* Back-off�㷨״̬: �����δ���� */
    VOS_UINT8                               ucRsv[2];       /* ���� */

    NAS_BACKOFF_INACTIVE_INFO_STRU          stInactiveInfo; /* �㷨δ����̬��ά������Ϣ */
    NAS_BACKOFF_ACTIVE_INFO_STRU            stActiveInfo;   /* �㷨����̬��ά������Ϣ   */
} NAS_BACKOFF_APN_ENTITY_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_NETRAT_ENTITY_STRU
ʹ��˵��    :Back-off�㷨���뼼��ʵ��
*****************************************************************************/
typedef struct
{
    NAS_BACKOFF_APN_ENTITY_STRU   stApnEntity[NAS_BACKOFF_APN_ENTITY_MAX_NUM]; /* APN���ʵ�� */
} NAS_BACKOFF_NETRAT_ENTITY_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACK_OFF_ALGORITHM_ENTITY_STRU
ʹ��˵��    :Back-off�㷨ʵ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucBackOffAlgFlag;  /* �㷨NV���ܿ��أ�0 �رգ�1 ���� */
    VOS_UINT8                       ucRsv[3];          /* ���� */

    NAS_BACKOFF_COMM_PARA_STRU      stCommPara;        /* �㷨�������� */
    NAS_CONFIG_PDP_PERM_CAUSE_STRU  stPdpPermCause;    /* ���þܾ�ԭ��ֵ�б� */
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU  stPdpTempCause;    /* ��ʱ�ܾ�ԭ��ֵ�б� */
    NAS_BACKOFF_NETRAT_ENTITY_STRU  stNetRatEntity[NAS_BACKOFF_NETRAT_ENUM_BUTT]; /* ���뼼�����ʵ�� */
} NAS_BACKOFF_ALGORITHM_ENTITY_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_OPERATE_TYPE_MSG_STRU
ʹ��˵��    :Back-off�㷨������Ϣ���
*****************************************************************************/
typedef struct
{
    union
    {
        NAS_BACKOFF_INIT_INFO_STRU           stInitPara;       /* ��ʼ��������� */
        NAS_BACKOFF_JUDGMENT_PARA_STRU       stJudgmentPara;   /* �ж��������   */
        NAS_BACKOFF_MAINTAIN_PARA_STRU       stMaintainPara;   /* ά���������   */
        NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  enResetCause;     /* ���ò������   */
    }u;
} NAS_BACKOFF_OPERATE_PARA_STRU;
/*****************************************************************************
  5 Massage Declare
*****************************************************************************/


/*****************************************************************************
�ṹ����    :NAS_BACKOFF_LOG_OPERATE_INFO_STRU
ʹ��˵��    :Back-off�㷨������LOG��Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_BACKOFF_NETRAT_ENUM_UINT32       enNetRat;
    NAS_BACKOFF_OPERATE_PARA_STRU        stOperatePara;
} NAS_BACKOFF_LOG_OPERATE_INFO_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_LOG_NV_INFO_STRU
ʹ��˵��    :Back-off�㷨NV����������LOG��Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;         /*_H2ASN_Skip*/
    NAS_CONFIG_BACKOFF_FX_PARA_STRU      stBackOffFx;         /* Fx����                                */
    NAS_CONFIG_PDP_PERM_CAUSE_STRU       stPdpPermCause;      /* ���þܾ�ԭ��ֵ�б�                    */
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU       stPdpTempCause;      /* ��ʱ�ܾ�ԭ��ֵ�б�                    */
    NAS_MM_DAM_PLMN_LIST_STRU            stDamPlmnList;       /* DAM������Ч��PLMN�б�                 */
} NAS_BACKOFF_LOG_NV_INFO_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_LOG_COMM_INFO_STRU
ʹ��˵��    :Back-off�㷨������ǰʵ��״̬LOG��Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/

    NAS_BACKOFF_COMM_PARA_STRU           stCommPara;      /* �㷨�������� */
    NAS_CONFIG_PDP_PERM_CAUSE_STRU       stPdpPermCause;  /* ���þܾ�ԭ��ֵ�б� */
    NAS_CONFIG_PDP_TEMP_CAUSE_STRU       stPdpTempCause;  /* ��ʱ�ܾ�ԭ��ֵ�б� */

} NAS_BACKOFF_LOG_COMM_INFO_STRU;

/*****************************************************************************
�ṹ����    :NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU
ʹ��˵��    :Back-off�㷨����ĳ���뼼���µĵ�ǰʵ����Ϣ�б�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_BACKOFF_NETRAT_ENUM_UINT32       enNetRat;        /* ���뼼��                */
    NAS_BACKOFF_NETRAT_ENTITY_STRU       stNetRatEntity;  /* ���뼼���µ�APNʵ���б� */

} NAS_BACKOFF_LOG_APN_ENTITY_LIST_STRU;
/*****************************************************************************
�ṹ����    :NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU
ʹ��˵��    :Back-off�㷨Init������LOG��Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_BACKOFF_NETRAT_ENUM_UINT32       enNetRat;
    NAS_BACKOFF_INIT_INFO_STRU           stInitInfo;
} NAS_BACKOFF_LOG_INIT_OPERATE_INFO_STRU;
/*****************************************************************************
�ṹ����    :NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU
ʹ��˵��    :Back-off�㷨Judgment������LOG��Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_BACKOFF_NETRAT_ENUM_UINT32       enNetRat;
    NAS_BACKOFF_JUDGMENT_PARA_STRU       stJudgmentPara;
} NAS_BACKOFF_JUDGMENT_OPERATE_INFO_STRU;
/*****************************************************************************
�ṹ����    :NAS_BACKOFF_Maintain_OPERATE_INFO_STRU
ʹ��˵��    :Back-off�㷨Maintain������LOG��Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_BACKOFF_NETRAT_ENUM_UINT32       enNetRat;
    NAS_BACKOFF_MAINTAIN_PARA_STRU       stMaintainPara;
} NAS_BACKOFF_Maintain_OPERATE_INFO_STRU;
/*****************************************************************************
�ṹ����    :NAS_BACKOFF_RESET_OPERATE_INFO_STRU
ʹ��˵��    :Back-off�㷨Reset������LOG��Ϣ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    NAS_BACKOFF_NETRAT_ENUM_UINT32       enNetRat;
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  enResetCause;
} NAS_BACKOFF_RESET_OPERATE_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_BACKOFF_ALGORITHM_ENTITY_STRU  g_stBackOffEntity;


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/* �ⲿ���ܵ��ô˽ӿں��� */
VOS_VOID NAS_BACKOFF_OperateInit
(
    NAS_BACKOFF_INIT_INFO_STRU            *pstInitPara
);
VOS_UINT32 NAS_BACKOFF_OperateJudgment
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_JUDGMENT_PARA_STRU    *pstJudgmentPara
);
VOS_VOID NAS_BACKOFF_OperateMaintain
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
);
VOS_VOID NAS_BACKOFF_OperateReset
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32        enNetRat,
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  *penResetCause
);

/* ���º���������Back-off�㷨�ڲ�ʹ�� */
VOS_UINT8* NAS_BACKOFF_GetAlgFlagAddr(VOS_VOID);
NAS_BACKOFF_APN_ENTITY_STRU* NAS_BACKOFF_GetApnEntityAddr
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32  enNetRat,
    VOS_UINT32                      ulIndex
);
NAS_BACKOFF_COMM_PARA_STRU* NAS_BACKOFF_GetCommParaAddr(VOS_VOID);
NAS_CONFIG_PDP_PERM_CAUSE_STRU* NAS_BACKOFF_GetPdpPermCauseListAddr(VOS_VOID);
NAS_CONFIG_PDP_TEMP_CAUSE_STRU* NAS_BACKOFF_GetPdpTempCauseListAddr(VOS_VOID);
VOS_VOID NAS_BACKOFF_SetBackOffState
(
    NAS_BACKOFF_STATE_ENUM_UINT8     enDestState,
    NAS_BACKOFF_APN_ENTITY_STRU     *pstApnEntity
);
VOS_UINT32 NAS_BACKOFF_MainTaskEntry
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32             enNetRat,
    NAS_BACKOFF_OPERATE_TYPE_ENUM_UINT32       enOpType,
    NAS_BACKOFF_OPERATE_PARA_STRU             *pstOpPara
);
VOS_VOID NAS_BACKOFF_Init
(
    NAS_BACKOFF_INIT_INFO_STRU  *pstInitInfo
);
VOS_UINT32 NAS_BACKOFF_Judgment
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_JUDGMENT_PARA_STRU    *pstJudgmentPara
);
VOS_VOID NAS_BACKOFF_Maintain
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
);
VOS_VOID NAS_BACKOFF_Reset
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32        enNetRat,
    NAS_BACKOFF_RESET_CAUSE_ENUM_UINT32  *penResetCause
);
VOS_UINT32 NAS_BACKOFF_QueryInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    APP_ESM_APN_INFO_STRU              *pstApn,
    NAS_BACKOFF_QUERY_RESULT_STRU      *pstQueryResult
);
VOS_VOID NAS_BACKOFF_PdpActiveSuccProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
);
VOS_VOID NAS_BACKOFF_PdpActiveFailProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32     enNetRat,
    NAS_BACKOFF_MAINTAIN_PARA_STRU    *pstMaintainPara
);
VOS_VOID NAS_BACKOFF_InactiveProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32           enNetRat,
    VOS_UINT32                               ulIndex,
    NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8      enPdpResult,
    VOS_UINT8                                ucCnCause
);
VOS_VOID NAS_BACKOFF_ActiveProc
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32           enNetRat,
    VOS_UINT32                               ulIndex,
    NAS_BACKOFF_PDP_ACTIVE_RESULT_ENUM8      enPdpResult,
    VOS_UINT8                                ucCnCause
);
VOS_UINT32  NAS_BACKOFF_ReadNvDamBackOffPara
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU        *pstNvDamPara
);
VOS_VOID  NAS_BACKOFF_InitPdpRejCauseList
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU           *pstNvDamPara
);
VOS_VOID  NAS_BACKOFF_InitCommParaFx
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU *pstNvDamPara,
    NAS_BACKOFF_INIT_INFO_STRU           *pstInitInfo
);
VOS_VOID NAS_BACKOFF_InitCommParaFb
(
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara
);
VOS_VOID NAS_BACKOFF_InitCommParaTimerPara
(
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara
);
VOS_VOID NAS_BACKOFF_CheckFx
(
    NAS_BACKOFF_COMM_PARA_STRU     *pstCommPara
);
VOS_UINT8 NAS_BACKOFF_SelectFb(VOS_UINT8 ucFx);
VOS_VOID NAS_BACKOFF_CalcTimerLenMinAndMax
(
    VOS_UINT8                           ucFx,
    VOS_UINT8                           ucFb,
    NAS_BACKOFF_TIMER_INFO_STRU        *pstTimerInfo
);
VOS_UINT32 NAS_BACKOFF_AllocApnEntity
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                         *pulIndex
);
VOS_UINT8 NAS_BACKOFF_GetPdpCnRejType(VOS_UINT8  ucCnCause);
VOS_VOID NAS_BACKOFF_ClearApnEntity
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                          ulIndex
);
VOS_UINT32 NAS_BACKOFF_TimerLenRandom
(
    NAS_BACKOFF_TIMER_INFO_STRU       *pstTimerInfo
);
VOS_UINT32 NAS_BACKOFF_ForbidTimerLenCalc
(
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
);
VOS_VOID NAS_BACKOFF_ForbidTimerStart
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
);
VOS_VOID NAS_BACKOFF_ForbidTimerStop
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32      enNetRat,
    VOS_UINT32                          ulIndex,
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
);
VOS_UINT8 NAS_BACKOFF_GetForbidTimerState
(
    NAS_BACKOFF_APN_ENTITY_STRU    *pstApnEntity
);
VOS_VOID  NAS_BACKOFF_SndOmLogOperateInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_TYPE_ENUM_UINT32   enOpType,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
);
VOS_VOID  NAS_BACKOFF_SndOmLogNvPara
(
    LNAS_ESM_NV_BACKOFF_CONFIG_PARA_STRU         *pstNvDamPara
);
VOS_VOID  NAS_BACKOFF_SndOmLogCommInfo(VOS_VOID);
VOS_VOID  NAS_BACKOFF_SndOmLogApnEntityList(NAS_BACKOFF_NETRAT_ENUM_UINT32 enNetRat);
VOS_VOID  NAS_BACKOFF_SndOmLog(NAS_BACKOFF_NETRAT_ENUM_UINT32 enNetRat);
VOS_VOID  NAS_BACKOFF_SndOmLogInitInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
);
VOS_VOID  NAS_BACKOFF_SndOmLogJudgmentInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
);
VOS_VOID  NAS_BACKOFF_SndOmLogMaintainInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
);
VOS_VOID  NAS_BACKOFF_SndOmLogResetInfo
(
    NAS_BACKOFF_NETRAT_ENUM_UINT32         enNetRat,
    NAS_BACKOFF_OPERATE_PARA_STRU         *pstOpPara
);

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

#endif /* end of NasEsmPublic.h */
