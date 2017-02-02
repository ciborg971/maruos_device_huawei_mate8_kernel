/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXpdsFsmPdeProcTbl.h
  �� �� ��   : ����
  ��    ��   : x00314862
  ��������   : 2014��11��07��
  ��������   : TafXpdsFsmPdeProcTbl.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : x00314862
    �޸�����   : �����ļ�
******************************************************************************/

#ifndef _TAF_XPDS_CP_FSM_PDE_PROC_TBL_H_
#define _TAF_XPDS_CP_FSM_PDE_PROC_TBL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafFsm.h"
#include  "TafXpdsCtx.h"

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
 ö����    : TAF_XPDS_L2_PDE_PROC_STA_ENUM
 ö��˵��  : L2 PDE״̬��IDö�ٶ���
 1.��    ��   : 2015��08��21��
   ��    ��   : x00314862
   �޸�����   : �½�
*****************************************************************************/
enum TAF_XPDS_CP_L2_PDE_PROC_STA_ENUM
{

    TAF_XPDS_CP_L2_PDE_PROC_STA_INIT,                      /* control plane ��ʼ��״̬*/
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_CAS_CNF,          /* control plane MSB mode wait for CAS confirm for msg sent */
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_PDE_EPHI_ALM_RESP,         /* control plane MSB mode wait for PDE respone when both ALM and EPHI recieved full */
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_GPS_LOC_RESP,     /* control plane MSB mode wait for GPS location response */
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_AT_GPS_STOP,       /* control plane msb mode after receiving the loc resp wait for at gps stop */
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_PPM,       /* control plane MSA mode wait for CAS confirm  after sending Pilot Phase Measurement */
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP, /* control plane MSA mode wait for CAS confirm afer sending REQ LOC RSP */
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_GPS_PSEUDO_INFO,          /* control plane MSA mode wait for GPD Pseudo info */
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PDE_ASSIST_INFO,           /* control plane MSA mode wait for PDE Assist info */
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_MS_INFO,       /* control plane MSA mode wait for CAS confirm  after sending Pilot Phase Measurement */
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_PPM_NI,       /* control plane MSA mode NI wait for CAS confirm  after sending Pilot Phase Measurement */
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_AQUI_ASSIS_NI,
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PRM_REQ_NI,
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PPM_COMPLETE_NI,
    TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP,          /* control plane MSA mode wait for Location resp from PDE */


    TAF_XPDS_CP_L2_PDE_PROC_STA_BUTT
};
typedef VOS_UINT32 TAF_XPDS_CP_L2_PDE_PROC_STA_ENUM_UINT32;

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
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 TAF_XPDS_GetCpL2PdeProcStaTblSize( VOS_VOID );
TAF_STA_STRU* TAF_XPDS_GetCpL2PdeProcStaTblAddr( VOS_VOID );
TAF_FSM_DESC_STRU* TAF_XPDS_GetCpL2PdeProcFsmDescAddr( VOS_VOID );


extern TAF_FSM_DESC_STRU                       g_stTafXpdsCpL2PdeProcFsmDesc;

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

#endif /* end of TafXsmsMoFsmMainTbl.h */





