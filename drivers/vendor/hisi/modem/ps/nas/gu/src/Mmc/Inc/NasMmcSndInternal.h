
#ifndef _NAS_MMC_SND_INTERNAL_H
#define _NAS_MMC_SND_INTERNAL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "NasMmcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : NAS_MMLAYER_INTERNAL_MSG_ID_ENUM
 �ṹ˵��  : �ڲ���ϢID
  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : MMC�ڲ���ϢIDö��
*****************************************************************************/
enum NAS_MMC_INTERNAL_MSG_ID_ENUM
{
    /* MMC�յ����ڲ���ϢID,MMC�ڲ��յ�����ϢID��0x000��0x199 */
    MMCMMC_QUIT_L2FSM_REQ                       ,
    MMCMMC_INTER_SRCH_NEXT_PLMN_REQ             ,                               /* �Զ����ֶ��ڲ���������������һ������ */
    MMCMMC_INTER_RESTART_SRCH_PLMN_REQ          ,                               /* �ڲ��������� ,���³�ʼ���������������� */
    MMCMMC_INTER_LIST_PLMN_REQ                  ,

    MMCMMC_SWITCH_ON_RSLT_CNF                ,
    MMCMMC_POWER_OFF_RSLT_CNF               ,
    MMCMMC_SRCH_PLMN_RSLT_CNF               ,
    MMCMMC_SUSPEND_RSLT_CNF                 ,

    MMCMMC_INTERNAL_MSG_ID_BUTT
};
typedef VOS_UINT32 NAS_MMC_INTERNAL_MSG_ID_ENUM_U32;

/*****************************************************************************
 ö����    : NAS_MMC_PLMNSRCH_RESULT_ENUM_UINT32
 �ṹ˵��  : plmnsrch״̬�������Ľ��
*****************************************************************************/
enum NAS_MMC_PLMNSRCH_RESULT_ENUM
{
    NAS_MMC_PLMN_SRCH_SUCCESS           = 0,
    NAS_MMC_PLMN_SRCH_ALL_FAIL          = 1,
    NAS_MMC_PLMN_SRCH_QUIT              = 2,
    NAS_MMC_PLMN_SRCH_BUTT
};
typedef VOS_UINT32 NAS_MMC_PLMNSRCH_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MMC_SUSPEND_RSLT_ENUM_UINT32
 �ṹ˵��  : SUSPEND״̬�������Ľ��
*****************************************************************************/
enum NAS_MMC_SUSPEND_RSLT_ENUM
{
    NAS_MMC_SUSPEND_SUCCESS            = 0,
    NAS_MMC_SUSPEND_FAIL               = 1,
    NAS_MMC_SUSPEND_QUIT               = 2,
    NAS_MMC_SUSPEND_BUTT
};
typedef VOS_UINT32 NAS_MMC_SUSPEND_RSLT_ENUM_UINT32;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : NAS_MMC_QUIT_FSM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC�����˳���Ϣ�Ľṹ

  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : �˳���Ϣ�Ľṹ
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT32                          ulTopState;
    VOS_UINT32                          enFsmId;
}NAS_MMC_QUIT_FSM_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMC_INTER_PLMN_SRCH_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:  MMC->MMC,�ڲ��������ͱ�ʶ

  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : �ڲ�������Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    NAS_MMC_PLMN_SRCH_INFO_STRU         stPlmnSrchInfo;
}NAS_MMC_INTER_PLMN_SRCH_REQ_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMC_SWITCHON_RLST_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:  MMC->MMC,�������

  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : ������Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                            MsgHeader;
    VOS_UINT32                                 ulResult;
} NAS_MMC_SWITCHON_RLST_STRU;


/*****************************************************************************
 �ṹ����: NAS_MMCMMC_PLMNSRCH_RLST_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:  MMC->MMC,�������

  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : ������Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    NAS_MMC_PLMNSRCH_RESULT_ENUM_UINT32 enResult;
} NAS_MMCMMC_PLMNSRCH_RLST_STRU;

/*****************************************************************************
 �ṹ����: NAS_MMCMMC_SUSPEND_RSLT_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:  MMC->MMC,������

  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : ������Ϣ�Ľṹ
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;

    /*SUSPEND��ɵĽ�� */
    NAS_MMC_SUSPEND_RSLT_ENUM_UINT32    enSuspendRslt;
}NAS_MMCMMC_SUSPEND_RSLT_STRU;

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT32                          ulRslt;
}NAS_MMCMMC_POWEROFF_RSLT_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID  NAS_MMC_SndQuitFsmMsg( VOS_VOID );

VOS_VOID  NAS_MMC_BuildInterPlmnSrchReq(
    VOS_UINT32                          ulMsgName,
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo,
    NAS_MMC_INTER_PLMN_SRCH_REQ_STRU   *pstPlmnSrchReq
);

VOS_UINT32  NAS_MMC_SndInterSrchNextPlmnReq(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);
VOS_UINT32  NAS_MMC_SndInterRestartPlmnSrchReq(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_SndSwitchOnRlst(VOS_UINT32 ulResult);


VOS_VOID NAS_MMC_SndPlmnSrchRlst(
    NAS_MMC_PLMNSRCH_RESULT_ENUM_UINT32 enResult
);

VOS_VOID NAS_MMC_SndSuspendRslt(
    NAS_MMC_SUSPEND_RSLT_ENUM_UINT32    enSuspendRslt
);

VOS_VOID NAS_MMC_SndPowerOffRslt(VOS_VOID);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

