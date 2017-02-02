

#ifndef _TDS_CHCTRL_OM_DEF_H_
#define _TDS_CHCTRL_OM_DEF_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/
#include "balong_lte_dsp.h"


/************************************************************
                               �궨��
************************************************************/



/************************************************************
                             ���ݽṹ����
************************************************************/

	typedef struct
	{
	    UINT16      usSysSfn;        /*ϵͳ��֡��*/
	    UINT16      usSysTs;         /*ϵͳʱ϶��*/
	    UINT16      usChipTime;      /*��ǰchipλ��*/
	    UINT16      usReserved;
	    UINT32      ulData1;
	    UINT32      ulData2;
	    UINT32      ulData3;
	    UINT32      ulData4;
	}TPHY_OM_TRACE_CHANCTRL_STRU;

/************************************************************
                    TRACE���ݽṹ����
************************************************************/

typedef enum
{
	/*ԭ�ﴦ��*/
    TPHY_TRACE_CHCTRL_PCCPCH_READ_REQ           = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x1),
    TPHY_TRACE_CHCTRL_SCCPCH_READ_REQ           = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x2),
    TPHY_TRACE_CHCTRL_IDEL_TASK_READ_REQ        = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x3),
    TPHY_TRACE_CHCTRL_PRACH_SEND_REQ            = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x4),
    TPHY_TRACE_CHCTRL_DPCH_CONFIG_REQ           = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x5),
    TPHY_TRACE_CHCTRL_HSPDSCH_CONFIG_REQ        = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x6),
    TPHY_TRACE_CHCTRL_EPUCH_CONFIG_REQ          = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x7),
    TPHY_TRACE_CHCTRL_EPUCH_SEND_REQ            = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x8),
    TPHY_TRACE_CHCTRL_HO_SYNC_SEND_REQ          = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x9),
    TPHY_TRACE_CHCTRL_FPACH_READ_CNF            = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0xa),
    
    /*R99�ŵ�״̬ά��*/
    TPHY_TRACE_CHCTRL_R99_CHCTRL_START          = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0xb),
    TPHY_TRACE_CHCTRL_PCCPCH_SETUP              = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0xc),
    TPHY_TRACE_CHCTRL_PCCPCH_RELEASE            = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0xd),
    TPHY_TRACE_CHCTRL_PCCPCH_SYNCSUC            = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0xe),
    TPHY_TRACE_CHCTRL_PCCPCH_SYNCFAIL           = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0xf),
    TPHY_TRACE_CHCTRL_SCCPCH_SETUP              = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x10),
    TPHY_TRACE_CHCTRL_SCCPCH_RELEASE            = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x11),
    TPHY_TRACE_CHCTRL_FPACH_SETUP               = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x12),
    TPHY_TRACE_CHCTRL_PICH_SETUP                = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x13),
    TPHY_TRACE_CHCTRL_R99_CHCTRL_END            = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x14),
    
    /*HSDPA�ŵ�״̬ά��*/
    TPHY_TRACE_CHCTRL_SCCH_SETUP                = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x15),
    TPHY_TRACE_CHCTRL_SCCH_SEARCH               = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x16),    
    
    /*HSUPA�ŵ�״̬ά��*/
    TPHY_TRACE_CHCTRL_AGCH_SETUP                = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x17),
    
    TPHY_CHCTRL_OM_FTTA_IND                     = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0xa0),
}TPHY_CHCTRL_TRACE_ENUM;
typedef UINT16 TPHY_CHANCTRL_TRACE_ENUM_UINT16;

/************************************************************
                     ERROR���ݽṹ����
************************************************************/
typedef enum
{
	/*ԭ���������*/
    TPHY_ERROR_CHCTRL_PCCPCH_CHPARA_ERROR         = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x1),
    TPHY_ERROR_CHCTRL_PCCPCH_JDPARA_ERROR         = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x2),
    TPHY_ERROR_CHCTRL_SCCPCH_CHPARA_ERROR         = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x3),
    TPHY_ERROR_CHCTRL_SCCPCH_JDPARA_ERROR         = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x4),
    TPHY_ERROR_CHCTRL_IDELTASK_CHPARA_ERROR       = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x5),
    TPHY_ERROR_CHCTRL_IDELTASK_JDPARA_ERROR       = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x6),
    TPHY_ERROR_CHCTRL_PRACH_CHPARA_ERROR          = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x7),
    TPHY_ERROR_CHCTRL_PRACH_JDPARA_ERROR          = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x8),
    TPHY_ERROR_CHCTRL_DPCH_CHPARA_ERROR           = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x9),
    TPHY_ERROR_CHCTRL_DPCH_JDPARA_ERROR           = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0xa),
    TPHY_ERROR_CHCTRL_HSPDSCH_CHPARA_ERROR        = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0xb),
    TPHY_ERROR_CHCTRL_HSPDSCH_JDPARA_ERROR        = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0xc),
    TPHY_ERROR_CHCTRL_EPUCHCFG_CHPARA_ERROR       = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0xd),
    TPHY_ERROR_CHCTRL_EPUCHCFG_JDPARA_ERROR       = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0xe),
    TPHY_ERROR_CHCTRL_EPUCHSEND_CHPARA_ERROR      = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0xf),
    TPHY_ERROR_CHCTRL_HOSYNC_CHPARA_ERROR         = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x10),
    TPHY_ERROR_CHCTRL_HOSYNC_JDPARA_ERROR         = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x11),
    
    TPHY_ERROR_CHCTRL_DIV_ZREO                    = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x12),
    TPHY_ERROR_CHCTRL_MOD_ZREO                    = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x13),
    TPHY_ERROR_CHCTRL_RFDRIVE_FAILD               = OM_TCMD_ID(TPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x14),

}TPHY_CHCTRL_ERROR_ENUM;

//typedef UINT16 TPHY_CHANCTRL_ERROR_ENUM_UINT16;

/************************************************************
                             ��������
************************************************************/







#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TDS_CHCTRL_OM_DEF_H__ */

