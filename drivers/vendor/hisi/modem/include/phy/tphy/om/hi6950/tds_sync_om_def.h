/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : tds_sync_om_def.h
  �� �� ��   : ����
  ��    ��   : mah
  ��������   : 2012��11��12��
  ����޸�   :
  ��������   : TDS CQIģ��OM����ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��12��
    ��    ��   : mah
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __TDS_SYNC_OM_DEF_H__
#define __TDS_SYNC_OM_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "om_base_def.h"

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
#define TPHY_REQ_SYNC_OM_REP_SWITCH    OM_TCMD_ID(TPHY_SYNC_MID, OM_TYPE_REQ, 0x0)
#define TPHY_REQ_SYNC_ALGTH_PARA       OM_TCMD_ID(TPHY_SYNC_MID, OM_TYPE_REQ, 0x1)
#define TPHY_REQ_SYNC_STUB             OM_TCMD_ID(TPHY_SYNC_MID, OM_TYPE_REQ, 0x2)

#define TPHY_IND_SYNC_STAT             OM_TCMD_ID(TPHY_SYNC_MID, OM_TYPE_IND, 0x0)

/*----------------------------------------------*
 * �ṹ����                                                    *
 *----------------------------------------------*/
 /*TDS SIR�����㷨��������ṹ����*/
typedef struct TDS_SYNC_ALG_PARA
{
     UINT16 usSyncThr0;
     UINT16 usSyncThr1;     
}TDS_SYNC_ALG_PARA_STRU;

typedef struct TDS_SYNC_STUB
{
     UINT16 usSyncStubSwitch;
     UINT16 usSyncStat;     /*0 -ͬ����1-ʧ��*/
}TDS_SYNC_STUB_STRU;

typedef struct TDS_OM_STAT_IND_REQ
{
    UINT16 usSyncStatOmSwitch;
    UINT16 usRsvd;
    
}TDS_OM_STAT_IND_REQ_STRU;

typedef struct TDS_SYNC_OM_STAT
{
    UINT16 usSyncStatOmSwitch;
    UINT16 usCurSbfn;
    UINT16 usDpchCrc;           /*��ǰDPCH CRC�����0��ȷ��1����*/   
    UINT16 usSbInd;             /*��ǰ����SB�о������0���ǣ�1��*/   
    UINT16 usDschCrc;           /*��ǰDSCH CRC�����0��ȷ��1����*/
    UINT16 usSyncFrmCnt;        //ͬʧ�����ÿ�ʼʱ��¼��ϵͳ��֡��
    UINT16 usOutSyncCnt;        //ʧ������1
    UINT16 usCdSBCnt;           //SB ����1
    UINT16 usCrcCorrectCnt;     //CRC ��ȷ����1
    UINT16 usDchSyncCtrlFlag;   //ͬ�����̿���ȫ�ֱ��������ܵȼ������ʴ�����DchCtrlFlag
    UINT16 usCurDpchValidFlag;  /*��ǰ��֡�Ƿ������DPCH*/
    UINT16 usCurSmothDpchSnr;
    UINT16 usNextDpchSnr;
    UINT16 usPrevDpchSnr;    
    UINT16 usSyncJudgeFlag;     /*��ǰ��֡ͬʧ���о����*/
    UINT16 usTtiIndFlag;        /*��ǰTTI �߽�ָʾ�о����*/
    UINT16 usHSDSCHSchled;      /*��ǰ��֡HSDSCH�Ƿ����ָʾ��1���ȣ�0������*/   
    UINT16 usCdSbfn;
    UINT16 usSnrTh0;
    UINT16 usSnrTh1;
    UINT16 usValidSyncFrmCnt;
    UINT16 usResv;
}TDS_SYNC_OM_STAT_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

