
#ifndef __R_ITF_FLOWCTRL_H__
#define __R_ITF_FLOWCTRL_H__

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "vos.h"

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/


/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/* R�ӿ��������� */
#define R_ITF_FLOW_CTRL_MASK_MEM_CNT        (0x00000001)
#define R_ITF_FLOW_CTRL_MASK_MEM_SIZE       (0x00000002)
#define R_ITF_FLOW_CTRL_MASK_CPU_LOAD       (0x00000004)

/*
  ��Э��ջ(��Ҫ��NAS)��������������û�����������ͳһ������
  ��������ΪR_ITF_FLOW_CTRL_TYPE_PS_CMD�����أ�����������ˮ��ֵ��1��
  ��������Ҫ����ʱ���������ؽӿڣ�������R_ITF_FLOW_CTRL_MASK_PS_CMD��
  ��ˮ����R_ITF_FLOW_PS_CMD_START������������ƣ���ˮ����R_ITF_FLOW_PS_CMD_START��
  */
#define R_ITF_FLOW_CTRL_MASK_PS_CMD         (0x00000008)

#define R_ITF_FLOW_PS_CMD_STOP              (0)
#define R_ITF_FLOW_PS_CMD_START             (2)
/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/

/******************************************************************************
   5 ö�ٱ�������
******************************************************************************/

/* R�ӿ��������Ͷ��� */
enum R_ITF_FLOW_CTRL_TYPE_ENUM
{
    R_ITF_FLOW_CTRL_TYPE_MEM_CNT        = 0,    /*�ڴ�����*/
    R_ITF_FLOW_CTRL_TYPE_MEM_SIZE,              /*�ڴ���ʹ����*/
    R_ITF_FLOW_CTRL_TYPE_BUTT
};
typedef VOS_UINT32 R_ITF_FLOW_CTRL_TYPE_ENUM_UINT32;

/* ����ָʾ����ö�� */
enum R_ITF_FLOW_CTR_CMD_ENUM
{
    R_ITF_FLOW_CTRL_START,               /*��������ָʾ*/
    R_ITF_FLOW_CTRL_STOP,                /*����ָֹͣʾ*/

    R_ITF_FLOW_CTRL_CMD_BUTT
};
typedef VOS_UINT32 R_ITF_FLOW_CTRL_CMD_ENUM_UINT32;

/* R�ӿ��������ݽṹ���� */
typedef struct
{
    VOS_UINT32              ulMask;         /* ������Ҫ�ص�����ֵ */
    VOS_UINT32              ulCurrLev;
    VOS_UINT32              ulNormalLev;    /* ������ط�ֵ */
    VOS_UINT32              ulWarningLev;   /* �������ط�ֵ */
    VOS_UINT32              ulMaxLev;       /* ������������ɼ�����ȷ����ֵʹ�� */
} R_ITF_FLOW_LEV_STRU;

typedef struct
{
    VOS_UINT32              ulCtrlMask;
    VOS_UINT32              ulLastOptTick;
    VOS_UINT32              ulCtrlFlag;
    VOS_RATMODE_ENUM_UINT32 enRateMode;
    R_ITF_FLOW_LEV_STRU     astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_BUTT]; /* 0:MemCnt,1:MemSize,2:PppMsgCnt */
} R_ITF_FLOW_CTRL_STRU;

/*��ά�ɲ���Ϣ*/
typedef struct
{
    VOS_MSG_HEADER                                                               /* ��Ϣͷ */        /* _H2ASN_Skip */
    R_ITF_FLOW_CTRL_TYPE_ENUM_UINT32            enFlowCtrlType;                  /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT32                                  ulNewLevel;
    R_ITF_FLOW_CTRL_CMD_ENUM_UINT32             enFlowCtrlCmd;
    VOS_UINT32                                  ulResult;
}R_ITF_FLOW_CTRL_MNTN_INFO_STRU;


extern R_ITF_FLOW_CTRL_STRU             g_stRItfFlowCtrl;

extern VOS_UINT32 R_ITF_SetFlowCtrl
(
    VOS_UINT32                                  ulFlowCtrlType,
    VOS_UINT32                                  ulNewLev
);
extern VOS_UINT32 R_ITF_ClearFlowCtrl(VOS_UINT32 ulFlowCtrlType, VOS_UINT32 ulNewLev);
extern VOS_UINT32 R_ITF_RateDismatchUsbEnable(VOS_VOID);
extern VOS_UINT32 R_ITF_RateDismatchWifiEnable(VOS_VOID);
extern VOS_VOID   R_ITF_ResetFlowCtrl(VOS_VOID);
extern VOS_VOID   R_ITF_SetLFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode);
extern VOS_VOID   R_ITF_Set1XFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode);
extern VOS_VOID   R_ITF_SetHrpdFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode);
extern VOS_VOID   R_ITF_InitFlowCtrl(VOS_VOID);
extern VOS_UINT32 R_ITF_StartFlowCtrl(VOS_RATMODE_ENUM_UINT32 enRateMode);
extern VOS_UINT32 R_ITF_StopFlowCtrl(VOS_RATMODE_ENUM_UINT32 enRateMode);

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


#endif
