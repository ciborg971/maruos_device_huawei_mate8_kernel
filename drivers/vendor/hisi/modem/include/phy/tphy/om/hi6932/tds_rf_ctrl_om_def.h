/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : tds_datapath_om_def.h
  �� �� ��   : ����
  ��    ��   : mah
  ��������   : 2012��10��8��
  ����޸�   :
  ��������   : TDS  ����ͨ��OM�ӿڶ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��8��
    ��    ��   : mah
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __TDS_RF_CTRL_OM_DEF_H__
#define __TDS_RF_CTRL_OM_DEF_H__

#include "om_base_def.h"
/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ö�ٶ���                                       *
 *----------------------------------------------*/
 #if 1
typedef enum TDS_RF_OM_REQ_MSGID
{
    TPHY_DRV_INTERFACE_REQ      =  OM_TCMD_ID(TPHY_RFDRV_MID, OM_TYPE_REQ, 0x1),
    TPHY_SWITCH_FREQ_REQ        =  OM_TCMD_ID(TPHY_RFDRV_MID, OM_TYPE_REQ, 0x2),
    TPHY_REP_READBACK_REQ       =  OM_TCMD_ID(TPHY_RFDRV_MID, OM_TYPE_REQ, 0x3),
}TDS_RF_OM_REQ_MSGID_ENUM;

typedef enum TDS_RF_OM_RPT_IND
{
    TPHY_DRV_INTERFACE_IND     =  OM_TCMD_ID(TPHY_RFDRV_MID, OM_TYPE_IND, 0x0),
    TPHY_SWITCH_FREQ_IND       =  OM_TCMD_ID(TPHY_RFDRV_MID, OM_TYPE_IND, 0x1),
    TPHY_REP_READBACK_IND      =  OM_TCMD_ID(TPHY_RFDRV_MID, OM_TYPE_IND, 0x2),
}TDS_RF_OM_RPT_ENUM;

/*----------------------------------------------*
 * �ṹ�嶨��                                     *
 *----------------------------------------------*/
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16  enDatReqEna;
    UINT16 usRsvd;
}TPHY_DRV_INTERFACE_STRU;


typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16  enDatReqEna;
    UINT16 usRsvd  ;
}TPHY_SWITCH_FREQ_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16  aenSlot0Flg[8];
}TPHY_READ_BACK_REQ_STRU;

typedef struct
{
    UINT32 ulTdsFreq;
    INT32 lRfStartTime;
    INT32 lRfEndTime;  //RF��Чʱ������λchip
    UINT16 usTdsDataPathState;
    UINT16 usFourthFastFlg;//�ı��ٲ�����0xffffΪ1���٣�1Ϊ4����ʹ��
    INT16  usTdsPowerValue; //dBm��λ
    ABB_LPC_CONFIG_IND_ENUM_UINT16 usAbbState;
    UINT16 usCurChipNum;
    UINT16 usCurSlotNum;
}TPHY_DRV_INTERFACE_IND_STRU;

typedef struct
{
    UINT32 ulTdsFreq;
    UINT16 usBand;
    UINT16 usBandIndex;
    UINT32 ulIdlReg;
    UINT32 usC1Reg;
    UINT32 usC2Reg;
    UINT32 usC0Reg;
    UINT32 us14Reg;
    UINT32 us00Reg;
    UINT32 ul05Reg;
    UINT32 ul06Reg;
    UINT32 ul07Reg;
}TPHY_SWITCH_FREQ_IND_STRU;


typedef struct
{
    UINT16 usCurChipNum;
    UINT16 usCurSlotNum;
    UINT32 ul00Reg;
    UINT32 ul01Reg;
    UINT32 ul03Reg;
    UINT32 ul05Reg;
    UINT32 ul14Reg;
    UINT32 ulC0Reg;
    UINT32 ulC1Reg;
    UINT32 ulC2Reg;
    UINT32 ulSsiState;
    UINT32 ulLineState0;
    UINT32 ulLineState1;
    UINT32 ulLineState2;
  //  UINT32 ul05Reg;
    UINT32 ul06Reg;
    UINT32 ul07Reg;
    UINT32 ul09Reg;
    UINT32 ul0AReg;
    UINT32 ul0BReg;
    UINT32 ul0CReg;
    UINT32 ul40Reg;
    UINT32 ul41Reg;
    UINT32 ul42Reg;
}TPHY_REP_READBACK_IND_STRU;

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/
extern void TDS_RF_OmReq(UINT32 ulMsgId, UINT32 ulSessionId, void* pstMsg, UINT32 ulMsgSize);
extern void TDS_RF_DrvInterFaceInd( TPHY_DRV_INTERFACE_IND_STRU* pstMsg );
extern void TDS_RF_SwitchRep( TPHY_SWITCH_FREQ_IND_STRU* pstMsg );
extern void TDS_RF_ReadBackRep( TPHY_REP_READBACK_IND_STRU* pstMsg );
/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/
#endif

#endif

