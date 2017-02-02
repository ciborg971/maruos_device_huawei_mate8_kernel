/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��      : SCMSoftDecode.h
  �� �� ��      : ����
  ��    ��      : H59254
  ��������      : 2014��5��31��
  ����޸�      :
  ��������      : ��ͷ�ļ�ΪSOCP API��ͷ�ļ�����Ҫ�ṩ���ⲿ����ʹ��
  �����б�      :
  �޸���ʷ      :
  1.��    ��    : 2012��8��3��
    ��    ��    : zhuli
    �޸�����    : �����ļ�

******************************************************************************/
#ifndef _SCM_SOFTDECODE_H_
#define _SCM_SOFTDECODE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "omringbuffer.h"
#include "msp_debug.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/**************************************************************************
  2 �궨��
**************************************************************************/
#define SCM_DATA_RCV_BUFFER_SIZE    (100*1024)      /* SCM���ݽ���buffer��С */
#define SCM_DATA_RCV_PKT_SIZE       (8*1024)        /* SCM���ݽ���PKT��С */


/**************************************************************************
  3 ö�ٶ���
**************************************************************************/

/**************************************************************************
  4 �ṹ�嶨��
**************************************************************************/

/*****************************************************************************
�ṹ��    : SCM_DATE_RCV_CTRL_STRU
�ṹ˵��  : SCM���ݽ��յĿ��ƽṹ
*****************************************************************************/
typedef struct
{
    VOS_SEM                     SmID;
    OM_RING_ID                  rngOmRbufId;
    VOS_CHAR                   *pucBuffer;
}SCM_DATA_RCV_CTRL_STRU;

#if 0
/*****************************************************************************
�ṹ��    : SCM_DATA_RCV_HEADER_STRU
�ṹ˵��  : SCM���ݽ���ʱ���뻷�λ�����������ͷ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulLen;
}SCM_DATA_RCV_HEADER_STRU;
#endif

/*****************************************************************************
�ṹ��    : SCM_MAINTENANCE_INFO_STRU
�ṹ˵��  : SCM�����ģ���ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDataLen; /* ���ջ������ݳ��� */
    VOS_UINT32                          ulNum;     /* ���ջ������ݴ��� */
}SCM_MAINTENANCE_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulSemCreatErr;
    VOS_UINT32                          ulSemGiveErr;
    VOS_UINT32                          ulRingBufferCreatErr;
    VOS_UINT32                          ulTaskIdErr;
    VOS_UINT32                          ulBufferNotEnough;
    VOS_UINT32                          ulRingBufferFlush;
    VOS_UINT32                          ulRingBufferPutErr;
}SCM_SOFTDECODE_RB_INFO_STRU;


/*****************************************************************************
�ṹ��    : OM_ACPU_PC_UE_SUC_STRU
�ṹ˵��  : OMģ���������տ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    SCM_SOFTDECODE_RB_INFO_STRU         stRbInfo;
    SCM_MAINTENANCE_INFO_STRU           stPutInfo;
    SCM_MAINTENANCE_INFO_STRU           stGetInfo;
    SCM_MAINTENANCE_INFO_STRU           stHdlcDecapData;
    VOS_UINT32                          ulFrameDecapErr;
    VOS_UINT32                          ulHdlcInitErr;
    VOS_UINT32                          ulDataTypeErr;
    VOS_UINT32                          ulCpmRegLogicRcvSuc;
}SCM_SOFTDECODE_INFO_STRU;

/**************************************************************************
  6 ��������
**************************************************************************/

#if ((OSA_CPU_ACPU == VOS_OSA_CPU)|| (VOS_WIN32 == VOS_OS_VER))

VOS_UINT32 SCM_SoftDecodeCfgDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen);

VOS_UINT32 SCM_SoftDecodeDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen);

VOS_UINT32 SCM_SoftDecodeCfgRcvTaskInit(VOS_VOID);

VOS_UINT32 CBTSCM_SoftDecodeReqRcvTaskInit(VOS_VOID);

VOS_VOID   SCM_SoftDecodeCfgRcvSelfTask(
    VOS_UINT32                          ulPara1,
    VOS_UINT32                          ulPara2,
    VOS_UINT32                          ulPara3,
    VOS_UINT32                          ulPara4);

VOS_VOID   CBTSCM_SoftDecodeReqRcvSelfTask(
    VOS_UINT32                          ulPara1,
    VOS_UINT32                          ulPara2,
    VOS_UINT32                          ulPara3,
    VOS_UINT32                          ulPara4);



#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


