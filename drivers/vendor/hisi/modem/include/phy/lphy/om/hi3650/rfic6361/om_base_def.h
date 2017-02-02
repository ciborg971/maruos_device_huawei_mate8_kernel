

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/

/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

#ifndef __OM_BASEDEF_H__
#define __OM_BASEDEF_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "type_define.h"

/*
    ����LPHY��ϵͳID
*/
#define SUBSYSTEM_LPHY  (0x3)

/*
    ����LTE ��ģ��ID, ��5���ر�ʾ
*/
#define LPHY_RSV_MID        (0x0)
#define LPHY_RFE_MID        (0x1)
#define LPHY_AGC_MID        (0x2)
#define LPHY_AFC_MID        (0x3)
#define LPHY_CSU_MID        (0x4)
#define LPHY_CMU_MID        (0x5)
#define LPHY_EMU_MID        (0x6)
#define LPHY_CHE_MID        (0x7)
#define LPHY_DEM_MID        (0x8)
#define LPHY_LPC_MID        (0x9)
#define LPHY_CQI_MID        (0xA)
#define LPHY_CORR_MID       (0xB)
#define LPHY_SYNC_MID       (0xC)
#define LPHY_TIMING_MID     (0xD)
#define LPHY_DRX_MID        (0xE)
#define LPHY_SERV_MID       (0xF)
#define LPHY_UL_MID         (0x10)
#define LPHY_CHANCTRL_MID   (0x11)
#define LPHY_OM_MID         (0x12)
#define LPHY_DMA_MID        (0x13)
#define LPHY_VITERBI_MID    (0x14)
#define LPHY_TURBO_MID      (0x15)
#define LPHY_SCHED_MID      (0x16)
#define LPHY_INTERRUPT_MID  (0x17)
#define LPHY_DCOC_MID       (0x18)
#define LPHY_RXIQ_MID       (0x19)
#define LPHY_CT_MID         (0x1a)
#define LPHY_BT_MID         (0x1B)
#define LPHY_NCIT_MID   	(0x1C)
#define LPHY_EMBMS_MID      (0x1D)
#define LPHY_RFD_MID        (0x1E)
#define LPHY_LS_MID         (0x1F)
#define LPHY_LWCOEX_MID     LPHY_RSV_MID /*MID�Ѿ�û�п��࣬���ñ���λ*/
#define LPHY_MAX_MID        (32)

/*
    ����TPHY��ϵͳID
*/
#define SUBSYSTEM_TPHY  (0x7)
/*
    ����TDS ��ģ��ID, ��5���ر�ʾ
*/
#define TPHY_TRACE_INFO     (0x0)
#define TPHY_RFDRV_MID      (0x1)
#define TPHY_AGC_MID        (0x2)
#define TPHY_AFC_MID        (0x3)
#define TPHY_CS_MID         (0x4)
#define TPHY_CMU_MID        (0x5)
#define TPHY_MEAS_MID       (0x6)
#define TPHY_CHE_MID        (0x7)
#define TPHY_DATA_MID       (0x8)
#define TPHY_CORR_MID       (0x9)       /*δ����*/
#define TPHY_CQI_MID        (0xA)
#define TPHY_PC_MID         (0xB)
#define TPHY_SYNC_MID       (0xC)
#define TPHY_TIMING_MID     (0xD)
#define TPHY_DRX_MID        (0xE)
#define TPHY_SERV_MID       (0xF)
#define TPHY_UL_MID         (0x10)
#define TPHY_CHANCTRL_MID   (0x11)
#define TPHY_OM_MID         (0x12)
#define TPHY_DMA_MID        (0x13)
#define TPHY_CD_MID         (0x14)
#define TPHY_VIT_TURBO_MID  (0x15)
#define TPHY_SCHED_MID      (0x16)
#define TPHY_INT_MID        (0x17)
#define TPHY_JD_MID         (0x18)
#define TPHY_DCOC_MID       (0x19)
#define TPHY_RXIQ_MID       (0x1a)
#define TPHY_CT_MID         (0x1B)
#define TPHY_BT_MID         (0x1C)
#define TPHY_NCIT_MID       (0x1D)
#define TPHY_MAX_MID        (32)


/*
    ������Ϣ���͵ĺ꣬ռ3����
*/
#define OM_TYPE_REQ         (0x0)           /*HiStudio�·���ԭ����������*/
#define OM_TYPE_CNF         (0x1)           /*�յ�HiStudio��ԭ��������ظ���ȷ��*/
#define OM_TYPE_DT          (0x2)           /*�ظ��ֳ�����ԭ�������ͻ�*/
#define OM_TYPE_SG          (0x3)           /*�ظ��㷨ͼ�������ڲ��۲���*/
#define OM_TYPE_TRACE       (0x4)           /*�����ϱ�������ģ���������ʷ�켣*/
#define OM_TYPE_DEBUG       (0x5)           /*�����ϱ���DEBUG��Ϣ*/
#define OM_TYPE_ERROR       (0x6)           /*�����ϱ���״̬������Ϣ*/
#define OM_TYPE_IND         (0x7)           /*�����ϱ�������*/

/*
    ������ϢID������ɷ���
    ����ϵͳID, ��ģ��ID, ���ͣ�������ģ���ڲ�����Ϣid�ϳ�һ����ϢID
*/
#define OM_CMD_ID(mid, type, msg_id)  ((SUBSYSTEM_LPHY<<28)|(mid<<19)|(type<<16)|(msg_id))
#define OM_LCMD_ID(mid, type, msg_id) ((SUBSYSTEM_LPHY<<28)|(mid<<19)|(type<<16)|(msg_id))
#define OM_TCMD_ID(mid, type, msg_id) ((SUBSYSTEM_TPHY<<28)|(mid<<19)|(type<<16)|(msg_id))


#define OM_GET_SYS(om_msg_id) 	((om_msg_id >> 28) & 0x0007)
#define OM_GET_MID(om_msg_id) 	((om_msg_id >> 19) & 0x001f)
#define OM_GET_TYPE(om_msg_id) 	((om_msg_id >> 16) & 0x0007)
#define OM_GET_ID(om_msg_id)  	((om_msg_id >> 00) & 0xffff)


/*OM���幫��ʹ�ܿ���*/
typedef enum __OM_REQ_ENABLE__
{
    OM_REQ_DISABLE = 0,
    OM_REQ_ENABLE = 1
}OM_REQ_ENABLE_ENUM;
typedef UINT16 OM_REQ_ENABLE_ENUM_UINT16;

/*OM����ģ��*/
typedef enum __OM_REQ_TYPE__
{
    OM_REQ_TYPE_L1MSG = 0,
    OM_REQ_TYPE_PRINT = 1,
    OM_REQ_TYPE_BUTT
}OM_REQ_TYPE_ENUM;
typedef UINT16 OM_REQ_TYPE_ENUM_UINT16;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OM_BASEDEF_H__ */
