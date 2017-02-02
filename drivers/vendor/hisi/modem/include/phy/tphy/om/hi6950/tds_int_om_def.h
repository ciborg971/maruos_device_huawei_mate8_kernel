/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : tds_int_om_def.h
  �� �� ��   : ����
  ��    ��   : mah
  ��������   : 2012��9��18��
  ����޸�   :
  ��������   : TDS �ж�OM�ӿڶ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��18��
    ��    ��   : mah
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __TDS_INT_OM_DEF_H__
#define __TDS_INT_OM_DEF_H__


/*----------------------------------------------*
 * ö�ٶ���                                *
 *----------------------------------------------*/
typedef enum TDS_INT_OM_REQ_MSGID
{
    TPHY_REQ_INT_STAT_INFO_ID                    =  OM_TCMD_ID(TPHY_INT_MID, OM_TYPE_REQ, 0x0),
    TPHY_REQ_INT_SLOT_STAT_INFO_ID           =  OM_TCMD_ID(TPHY_INT_MID, OM_TYPE_REQ, 0x2),
}TDS_INT_OM_REQ_MSGID_ENUM;

typedef enum TDS_INT_STAT_RPT_IND
{
    TDS_INT_VEC_STAT_INFO_IND     =  OM_TCMD_ID(TPHY_INT_MID, OM_TYPE_IND, 0x0),     /*TDS�����ж�ͳ�Ƽ���*/
    TDS_INT_SLOT_STAT_INFO_IND    =  OM_TCMD_ID(TPHY_INT_MID, OM_TYPE_IND, 0x1),   /*TDS����ʱ϶�ж�ͳ�Ƽ���*/
           
}TDS_INT_STAT_RPT_IND_ENUM;

/*----------------------------------------------*
 * �ṹ�嶨��                                   *
 *----------------------------------------------*/
typedef struct TPHY_REQ_INT_INFO
{
    OM_REQ_ENABLE_ENUM_UINT16  enIntStatInfoEna; /*��ȡTDS �ж�ͳ����Ϣ���·�һ���ϱ�һ�Σ�����һֱ��Ч*/
    UINT16 usRsvd  ;  
}TDS_REQ_INT_INFO_STRU;

typedef struct TDS_INT_STAT_INFO
{
    UINT32 ulSbfnIntCnt;     /*��֡�жϼ���*/
    UINT32 ulSlotIntCnt;     /*ʱ϶�жϼ���*/
    UINT32 ulHsupaIntCnt;    /*HSUPA�жϼ���*/
    UINT32 ulViterbiIntCnt;  
    UINT32 ulTurboIntCnt;    
    UINT32 ulHarqIntCnt;    
    UINT32 ulTfpIntCnt; 
}TDS_INT_STAT_INFO_STRU;


typedef struct TDS_INT_STAT_SLOT_INFO
{
    UINT32 ulSlotIntCnt[TDS_SLOT_SCHDL_NUM_MAX]; /*TDS ʱ϶�ж�ͳ�Ƽ��� */
          
}TDS_INT_STAT_SLOT_INFO_STRU;

/*���ϱ���Ϣ������˳�����Ҫ��Ӧ���ϱ��ж���Ϣö��˳��(TDS_INT_STAT_RPT_ENUM)һ��*/
typedef struct TDS_INT_STAT_RPT_CTRL
{
    OM_REQ_ENABLE_ENUM_UINT16  enTdsIntRptSwitch;
    OM_REQ_ENABLE_ENUM_UINT16  enTdsSlotIntRptSwitch;          
}TDS_INT_STAT_RPT_CTRL_STRU;
/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/


/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/
extern TDS_INT_STAT_INFO_STRU gstTdsIntStatInfo;           /*TDS �����ж�ͳ�Ƽ��� */
extern TDS_INT_STAT_SLOT_INFO_STRU gstSlotIntCntInfo;      /*TDS ʱ϶�ж�ͳ�Ƽ��� */
//extern TDS_INT_STAT_RPT_CTRL_STRU gstTdsIntStatRptCtrl;
/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
#endif

