/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dma_om_define.h
  �� �� ��   : ����
  ��    ��   : honghuiyong;
  ��������   : 2011��1��14��
  ����޸�   :
  ��������   : DMA OM��ض����ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��1��14��
    ��    ��   : honghuiyong;
    �޸�����   : �����ļ�

******************************************************************************/


#ifndef __DMA_OM_DEFINE_H__
#define __DMA_OM_DEFINE_H__



/************************************************************
                             �궨��
************************************************************/

#define DMA_OM_MAX_PAYLOAD_LENGTH	10
#define DMA_OM_MSG_HEADER_LENGTH	12
#define DMA_OM_EXTRA_MSG_HEADER_LEN 4

#define DMA_REPORT_OM_TRACE_TYPE	((SUBSYSTEM_LPHY<<12) + (LPHY_DMA_MID<<3) + OM_TYPE_TRACE)        
#define DMA_REPORT_OM_DEBUG_TYPE	((SUBSYSTEM_LPHY<<12) + (LPHY_DMA_MID<<3) + OM_TYPE_DEBUG)        
#define DMA_REPORT_OM_ERROR_TYPE	((SUBSYSTEM_LPHY<<12) + (LPHY_DMA_MID<<3) + OM_TYPE_ERROR)        



/************************************************************
                             ���ݽṹ����
************************************************************/
//---------------------------------------------------------
//  1.  DMA error info �ṹ�嶨�������[�����ϱ��ṹ��]
//---------------------------------------------------------

/* Error Message Report Format */
typedef enum __LPHY_ERR_MSGID_DMA_ERROR_ENUM__
{
    LPHY_ERR_DMA_RESERVED = OM_CMD_ID(LPHY_DMA_MID,OM_TYPE_ERROR,0),
    LPHY_ERR_DMA_ILLEGAL_CHANNEL_INDEX,
    LPHY_ERR_DMA_ILLEGAL_DATA_LENGTH,
    LPHY_ERR_DMA_BUFFER_OVERFLOW,
    LPHY_ERR_DMA_NULL_DESCRIPTOR,        
    LPHY_ERR_DMA_TIMEOUT,        
}LPHY_ERR_MSGID_DMA_ERROR_ENUM;
typedef UINT32 LPHY_ERR_MSGID_DMA_ERROR_ENUM_UINT32;


typedef struct __LPHY_DMA_ERROR_REPORT_OM_IND__
{
    UINT16      usSysFN;        /*�ϱ�ϵͳ֡��*/
    UINT16      usSubFN;        /*�ϱ���֡��*/    
    UINT32      ulPaylod[DMA_OM_MAX_PAYLOAD_LENGTH];
}LPHY_DMA_ERROR_REPORT_OM_IND;


/************************************************************
                             �ӿں�������
 ************************************************************/

UINT32 DMA_OM_ErrMsgReport(LPHY_ERR_MSGID_DMA_ERROR_ENUM_UINT32 enErrorType,UINT32 ulPayloadLen ,UINT32* pulPayload);

#endif
