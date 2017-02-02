/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : lpc_om_def.h
  �� �� ��   : ����
  ��    ��   : Hong Huiyong
  ��������   : 2013��6��15��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.	��    ��   : 2013��6��215
     	��    ��   : Hong Huiyong
    	�޸�����   : �����ļ�
******************************************************************************/
#include "balong_lte_dsp.h"

#ifndef __LPC_OM_DEF_H__
#define __LPC_OM_DEF_H__

#define MAX_LPC_CMD_CONTEXT_LENGTH		(120)

typedef enum   __HSO_SMP_CMD_OPID_ENUM__
{
	LPC_SMP_START,
	LPC_SMP_QUERY,
	LPC_SMP_STOP,
	LPC_SMP_CLEAR,
	LPC_SMP_START_ONE_ROUND,
}HSO_SMP_CMD_OPID_ENUM;
typedef UINT16 HSO_SMP_CMD_OPID_ENUM_UINT16;

typedef enum   __HSO_SMP_CMD_REG_CFG_TYPE_ENUM__
{
	LPC_SMP_REG_FULL_REG_CFG,
	LPC_SMP_REG_PART_REG_CFG,
}HSO_SMP_CMD_REG_CFG_TYPE_ENUM;
typedef UINT8	HSO_SMP_CMD_REG_CFG_TYPE_ENUM_UINT8;


typedef	struct __LPHY_LPC_HSO_SMP_CMD_STRU__
{
	UINT32							ulMsgID;
	HSO_SMP_CMD_OPID_ENUM_UINT16	enOpID;
	UINT16							usPDMap;
	UINT32							aulPayload[0];
}LPHY_LPC_HSO_SMP_CMD_STRU;

typedef	struct __LPHY_LPC_HSO_SMP_RPT_STRU__
{
	UINT32							ulMsgID;
	HSO_SMP_CMD_OPID_ENUM_UINT16	enOpID;
	UINT16							usValid;
	UINT32							aulPayload[0];
}LPHY_LPC_HSO_SMP_RPT_STRU;

typedef	struct __LPHY_LPC_HSO_CFG_REG_STRU__
{
	UINT32	ulAddr;
	UINT32	ulBitMask;
	UINT32  ulValue;
}LPHY_LPC_HSO_CFG_REG_STRU;

typedef	struct __LPHY_LPC_HSO_RPT_REG_STRU__
{
	UINT32	ulAddr;
	UINT32	ulValue;
}LPHY_LPC_HSO_RPT_REG_STRU;

/*****************************************************************************
 ���ݽṹ˵��  : LPHY_CSU_OM_REQ_���Ͷ���
*****************************************************************************/
typedef enum __LPHY_OM_REQ_LPC_ID_ENUM__
{
	LPHY_LPC_OM_REQ_RESERVED 	= OM_CMD_ID(LPHY_LPC_MID, OM_TYPE_REQ, 	0x0),
	LPHY_LPC_OM_REQ_HSO_SMP,
}LPHY_OM_REQ_LPC_ID_ENUM;

typedef enum __LPHY_SG_MSGID_LPC_SG_ENUM__
{
    LPHY_SG_LPC_RESERVED        = OM_CMD_ID(LPHY_LPC_MID,OM_TYPE_SG,	0x0),
    LPHY_SG_LPC_HSO_SMP_RPT,
	LPHY_SG_LPC_RPT_BUTT,
}LPHY_SG_MSGID_LPC_SG_ENUM;

#endif
