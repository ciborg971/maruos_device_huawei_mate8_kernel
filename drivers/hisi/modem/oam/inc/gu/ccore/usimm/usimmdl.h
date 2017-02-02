

#ifndef __USIMM_DL_H__
#define __USIMM_DL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "UsimPsInterface.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define SCI_SUCCESS_USIMM           (0)    /*����ִ�гɹ�*/
#define SCI_ERROR_USIMM             (1)    /*����ִ��ʧ��*/

#define USIMM_P3ERROR_MAXTIME       (100)

/*USIMMģ��֧�ֵ����APDU�����*/
#define USIMM_APDU_MAXLEN           (256)
/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
enum USIMMDL_DRV_API_NUM_ENUM
{
    USIMMDL_DRV_USIMMSCI_RST            = 0xF0,
    USIMMDL_DRV_USIMMSCI_CLASS_SWITCH   = 0xF1,
    USIMMDL_DRV_USIMMSCI_GET_CARD_STAU  = 0xF2,
    USIMMDL_DRV_USIMMSCI_SND_DATA1      = 0xF3,
    USIMMDL_DRV_USIMMSCI_RCV1           = 0xF4,
    USIMMDL_DRV_USIMMSCI_SND_DATA2      = 0xF5,
    USIMMDL_DRV_USIMMSCI_SND_DATA3      = 0xF6,
    USIMMDL_DRV_USIMMSCI_SND_DATA4      = 0xF7,
    USIMMDL_DRV_USIMMSCI_RCV2           = 0xF8,
    USIMMDL_DRV_USIMMSCI_RCV3           = 0xF9,
    USIMMDL_DRV_USIMMSCI_RCV4           = 0xFA,
    USIMMDL_DRV_USIMMSCI_DEACT          = 0xFB,

    USIMMDL_DRV_USIMMSCI_T1_SND_R_BLOCK = 0x01F0,
    USIMMDL_DRV_USIMMSCI_T1_SND_I_BLOCK = 0x01F1,
    USIMMDL_DRV_USIMMSCI_T1_SND_S_BLOCK = 0x01F2,
    USIMMDL_DRV_USIMMSCI_T1_RST         = 0x01F3,
    USIMMDL_DRV_USIMMSCI_T1_SET_BWT_1   = 0x01F4,
    USIMMDL_DRV_USIMMSCI_T1_RST_BWT_2   = 0x01F5,
    USIMMDL_DRV_USIMMSCI_T1_RCV         = 0x01F6,
    USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_1 = 0x01F7,
    USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_2 = 0x01F8,

    USIMMDL_DRV_USIMMSCI_BUTT
};

enum USIMMDL_STATE_ENUM
{
    USIMMDL_STATE_IDLE          = 0,
    USIMMDL_STATE_SENDAPDU      = 1,
    USIMMDL_STATE_SENDDATA      = 2,
    USIMMDL_STATE_WAITACK       = 3,
    USIMMDL_STATE_WAITDATA      = 4,
    USIMMDL_STATE_WAITSW        = 5,
    USIMMDL_STATE_GETRESPONSE   = 6,
    USIMMDL_STATE_BUTT
};
typedef VOS_UINT32      USIMMDL_STATE_ENUM_UINT32;

enum USIMM_CASE_TYPE_ENUM
{
    USIMM_CMD_CASE1             = 1,
    USIMM_CMD_CASE2             = 2,
    USIMM_CMD_CASE3             = 3,
    USIMM_CMD_CASE4             = 4,
    USIMM_CMD_CASE_BUTT
};
typedef VOS_UINT32      USIMM_CASE_TYPE_ENUM_UINT32;

enum USIMMDL_ERROR_ENUM
{
    USIMMDL_NOERROR             = 0,
    USIMMDL_SCISENDAPDU_ERROR   = 1,
    USIMMDL_SCISENDLC_ERROR     = 2,
    USIMMDL_SCIRECEIVEACK_ERROR = 3,
    USIMMDL_SCIRECEIVELE_ERROR  = 4,
    USIMMDL_SCIRECEIVESW_ERROR  = 5,
    USIMMDL_STATE_ERROR         = 6,
    USIMMDL_ERROR_BUTT
};
typedef VOS_UINT32      USIMMDL_ERROR_ENUM_UINT32;

/*Usimm DL���÷���ֵ*/
enum USIMM_DLHANDLE_RESULT_ENUM
{
    USIMM_DL_SUCESS             = VOS_OK,
    USIMM_DL_SEND_ERROR,
    USIMM_DL_RECEIVE_ERROR,
};

/*****************************************************************************
  4 STRUCT����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLeValue;                          /* �������ݳ��� */
    VOS_UINT32                          ulLcValue;                          /* �������ݳ��� */
    VOS_UINT32                          ulRecDataLen;
    VOS_UINT8                           ucResult;
    VOS_UINT8                           ucACK;                              /*���յ�ACK*/
    VOS_UINT8                           ucSW1;                              /*����������SW1*/
    VOS_UINT8                           ucSW2;                              /*����������SW2*/
    VOS_UINT8                           ucApduSW1;                          /*�����һ�η��͵�SW1*/
    VOS_UINT8                           ucApduSW2;                          /*�����һ�η��͵�SW2*/
    VOS_UINT8                           aucAPDU[USIMM_APDU_HEADLEN];        /*�����APDU*/
    VOS_UINT8                           aucGetRepAPDU[USIMM_APDU_HEADLEN];  /*Get Response�����APDU*/
    VOS_UINT8                           aucRecvBuf[USIMM_APDU_MAXLEN];      /* ������������*/
    VOS_UINT8                           aucSendBuf[USIMM_APDU_MAXLEN];      /* ������������*/
}USIMM_APDU_ST;

typedef struct
{
    VOS_UINT32                  ulSendDataLen;      /* ��ǰ�������ݳ��� */
    VOS_UINT32                  ulRecDataLen;       /* ��ǰ�������ݳ��� */
    USIMMDL_STATE_ENUM_UINT32   enDLState;          /* ��ǰ��·��״̬ */
    USIMMDL_ERROR_ENUM_UINT32   enDLError;          /* ��ǰ��·�������Ϣ*/
    USIMM_CASE_TYPE_ENUM_UINT32 enCMDCase;          /* ��ǰ��������*/
    VOS_UINT32                  ulSendAPDUTime;     /* ��ǰ��������ͷ�Ĵ��� */
    VOS_BOOL                    bSendRep;           /* 1Ϊ��Ҫ����Get Response*/
    VOS_UINT32                  ulP3ErrorTime;      /* ����P3����Ĵ��� */
}USIMMDL_CONTROL_ST;

typedef VOS_UINT32 (*PUSIMMDLPROC)(USIMM_APDU_ST *pstAPDUData);

typedef struct
{
    USIMMDL_STATE_ENUM_UINT32   enStateId;        /* ״̬ID */
    PUSIMMDLPROC                pProcFun;        /* ������ */
}USIMMDL_FUNC_STATUS;


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
extern USIMMDL_CONTROL_ST   gstUSIMMDLControl;


/*****************************************************************************
  6 OTHERS����
*****************************************************************************/
extern VOS_UINT32 USIMM_DLHandle(
    USIMM_APDU_ST                       *pstAPDUData);

extern VOS_UINT32 USIMM_DLResetCard(
    VOS_UINT32                          ulResetType, 
    VOS_INT32                           *plVoltageSwitchRst);

extern VOS_UINT32 USIMM_DLReceiveSW(
    USIMM_APDU_ST                       *pstAPDUData);

extern VOS_UINT32 USIMM_CglaDLHandle(
    USIMM_APDU_ST                       *pstAPDUData);

extern VOS_UINT32 USIMM_DLCglaReceiveSW(
    USIMM_APDU_ST                       *pstAPDUData);

extern VOS_UINT32 USIMM_DLCglaGetResponse(
    USIMM_APDU_ST                       *pstAPDUData);

extern VOS_VOID USIMM_DLJudgeCmdCase(
    USIMM_APDU_ST                       *pstAPDUData);

/*�ⲿ�ӿ�*/
extern VOS_VOID HPA_USIMLowPowerLock( VOS_UINT32 ulPid );

extern VOS_VOID HPA_USIMLowPowerUnLock( VOS_UINT32 ulPid );

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#else

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "usimmapdu.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define SCI_SUCCESS_USIMM   0    /*����ִ�гɹ�*/
#define SCI_ERROR_USIMM     1    /*����ִ��ʧ��*/

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
enum USIMMDL_DRV_API_NUM_ENUM
{
    USIMMDL_DRV_USIMMSCI_RST            = 0xF0,
    USIMMDL_DRV_USIMMSCI_CLASS_SWITCH   = 0xF1,
    USIMMDL_DRV_USIMMSCI_GET_CARD_STAU  = 0xF2,
    USIMMDL_DRV_USIMMSCI_SND_DATA1      = 0xF3,
    USIMMDL_DRV_USIMMSCI_RCV1           = 0xF4,
    USIMMDL_DRV_USIMMSCI_SND_DATA2      = 0xF5,
    USIMMDL_DRV_USIMMSCI_SND_DATA3      = 0xF6,
    USIMMDL_DRV_USIMMSCI_SND_DATA4      = 0xF7,
    USIMMDL_DRV_USIMMSCI_RCV2           = 0xF8,
    USIMMDL_DRV_USIMMSCI_RCV3           = 0xF9,
    USIMMDL_DRV_USIMMSCI_RCV4           = 0xFA,
    USIMMDL_DRV_USIMMSCI_DEACT          = 0xFB,

    USIMMDL_DRV_USIMMSCI_T1_SND_R_BLOCK = 0x01F0,
    USIMMDL_DRV_USIMMSCI_T1_SND_I_BLOCK = 0x01F1,
    USIMMDL_DRV_USIMMSCI_T1_SND_S_BLOCK = 0x01F2,
    USIMMDL_DRV_USIMMSCI_T1_RST         = 0x01F3,
    USIMMDL_DRV_USIMMSCI_T1_SET_BWT_1   = 0x01F4,
    USIMMDL_DRV_USIMMSCI_T1_RST_BWT_2   = 0x01F5,
    USIMMDL_DRV_USIMMSCI_T1_RCV         = 0x01F6,
    USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_1 = 0x01F7,
    USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_2 = 0x01F8,

    USIMMDL_DRV_USIMMSCI_BUTT
};

enum USIMMDL_STATE_ENUM
{
    USIMMDL_STATE_IDLE          = 0,
    USIMMDL_STATE_SENDAPDU      = 1,
    USIMMDL_STATE_SENDDATA      = 2,
    USIMMDL_STATE_WAITACK       = 3,
    USIMMDL_STATE_WAITDATA      = 4,
    USIMMDL_STATE_WAITSW        = 5,
    USIMMDL_STATE_GETRESPONSE   = 6,
    USIMMDL_STATE_BUTT
};
typedef VOS_UINT32      USIMMDL_STATE_ENUM_UINT32;

enum USIMM_CASE_TYPE_ENUM
{
    USIMM_CMD_CASE1             = 1,
    USIMM_CMD_CASE2             = 2,
    USIMM_CMD_CASE3             = 3,
    USIMM_CMD_CASE4             = 4,
    USIMM_CMD_CASE_BUTT
};
typedef VOS_UINT32      USIMM_CASE_TYPE_ENUM_UINT32;


enum USIMMDL_ERROR_ENUM
{
    USIMMDL_NOERROR             = 0,
    USIMMDL_SCISENDAPDU_ERROR   = 1,
    USIMMDL_SCISENDLC_ERROR     = 2,
    USIMMDL_SCIRECEIVEACK_ERROR = 3,
    USIMMDL_SCIRECEIVELE_ERROR  = 4,
    USIMMDL_SCIRECEIVESW_ERROR  = 5,
    USIMMDL_STATE_ERROR         = 6,
    USIMMDL_ERROR_BUTT
};
typedef VOS_UINT32      USIMMDL_ERROR_ENUM_UINT32;

/*****************************************************************************
  4 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_UINT32                  ulSendDataLen;      /* ��ǰ�������ݳ��� */
    VOS_UINT32                  ulRecDataLen;       /* ��ǰ�������ݳ��� */
    USIMMDL_STATE_ENUM_UINT32   enDLState;          /* ��ǰ��·��״̬ */
    USIMMDL_ERROR_ENUM_UINT32   enDLError;          /* ��ǰ��·�������Ϣ*/
    USIMM_CASE_TYPE_ENUM_UINT32 enCMDCase;          /* ��ǰ��������*/
    VOS_UINT32                  ulSendAPDUTime;     /* ��ǰ��������ͷ�Ĵ��� */
    VOS_BOOL                    bSendRep;           /* 1Ϊ��Ҫ����Get Response*/
}USIMMDL_CONTROL_ST;

typedef VOS_UINT32 (*PUSIMMDLPROC)(USIMM_APDU_ST *pstAPDUData);

typedef struct
{
    USIMMDL_STATE_ENUM_UINT32   enStateId;        /* ״̬ID */
    PUSIMMDLPROC                pProcFun;        /* ������ */
}USIMMDL_FUNC_STATUS;


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
extern USIMMDL_CONTROL_ST   gstUSIMMDLControl;

/*****************************************************************************
  6 OTHERS����
*****************************************************************************/
extern VOS_UINT32 USIMM_DLHandle(USIMM_APDU_ST *pstAPDUData);

extern VOS_UINT32 USIMM_DLResetCard(VOS_UINT32 ulResetType, VOS_INT32 *plVoltageSwitchRst);

extern VOS_UINT32 USIMM_DLReceiveSW(USIMM_APDU_ST *pstAPDUData);

extern VOS_UINT32 USIMM_CglaDLHandle(USIMM_APDU_ST* pstAPDUData);

extern VOS_UINT32 USIMM_DLCglaReceiveSW(USIMM_APDU_ST *pstAPDUData);

extern VOS_UINT32 USIMM_DLCglaGetResponse(USIMM_APDU_ST* pstAPDUData);

extern VOS_VOID USIMM_DLJudgeCmdCase(USIMM_APDU_ST* pstAPDUData);

/*�ⲿ�ӿ�*/
extern VOS_VOID HPA_USIMLowPowerLock( VOS_UINT32 ulPid );

extern VOS_VOID HPA_USIMLowPowerUnLock( VOS_UINT32 ulPid );

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of UsimmDL.h*/


