

#ifndef __RABM_INTERFACE_H__
#define __RABM_INTERFACE_H__



/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TTFMem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#ifndef RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN
#define RABM_RECV_N_PDU_NUM_LIST_IE_MAXLEN                  19
#endif

#ifndef RABM_MAX_ENT_NUM
#define RABM_MAX_ENT_NUM                                    11
#endif

#ifndef RABM_NSAPI_OFFSET
#define RABM_NSAPI_OFFSET                                   5
#endif

#define NAS_RABM_RAB_ID_MIN                                 (5)
#define NAS_RABM_RAB_ID_MAX                                 (15)

/*****************************************************************************
  3 ö�ٶ���
typedef enum
{
    ģ����_��������_ENUM
    MAPS_TEMPLATE_ENUM1 = 0,
    MAPS_TEMPLATE_ENUM2


    MAPS_TEMPLATE_BUTT,    �����ͳһ��BUTT����Ϊ���һ��ö��ֵ��

}MAPS_TEMPLATE_ENUM;   ģ����_ö����������_ENUM
*****************************************************************************/
typedef enum
{
    RABM_ABM_ENUM = 0,                  /*ȷ��ģʽ      */
    RABM_ADM_ENUM                       /*��ȷ��ģʽ    */

}RABM_TRANS_MODE_ENUM;




typedef enum
{
    RABM_FLOW_REPORT_ACCUMULATE = 1,           /*�ϱ�����RABID���ۼ�����*/
    RABM_FLOW_REPORT_WITH_RABID,               /*�ϱ�ָ��RABID������*/
    RABM_FLOW_REPORT_TOTAL,                    /*�ϱ�����RABID������*/

    RABM_FLOW_REPORT_BUTT
}RABM_FLOW_REPORT_MODE_ENUM;   /*�����ϱ�ģʽ*/
/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*---------------------------------------------------------
            Structs used between APS and RABM.
---------------------------------------------------------*/
typedef struct
{
    VOS_UINT8                           ucNsapi;
    RABM_TRANS_MODE_ENUM                TransMode;

}RABM_APS_SET_TRANS_MODE_ST;

/*---------------------------------------------------------
            Structs used between APP and RABM.
---------------------------------------------------------*/


/*----------------------------------------------------------
   SIGNAL PLANE Structs used between SNDCP and RABM.
----------------------------------------------------------*/
typedef struct
{
    /*In aucNPDUNumList[16][2], the items from[5] to [15] will be used
    for NSAPIs from NSAPI5 to NSAPI15. The position is the index of a NSAPI.

    aucNPDUNumList[i][0] == 0 : The NSAPI hasn't Received N-PDU Num;
                         == 1 : The NSAPI has Received N-PDU Number;

    aucNPDUNumList[i][1] == xx: The Receive N-PDU Number of NSAPI(i).
    "i" belongs to [5, 15]. */

    VOS_UINT8                          aucNPDUNumList[16][2];

}RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST;

typedef RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST   RABM_SNDCP_SEND_N_PDU_NUM_LIST_ST;
typedef RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST   RABM_PDCP_GET_N_PDU_NUM_LIST_ST;

typedef struct
{
    VOS_UINT32                          ulTLLI;
    RABM_SNDCP_RECV_N_PDU_NUM_LIST_ST   RecvNPduNumList;

}RABM_SNDCP_SEQUENCE_IND_ST;

typedef RABM_SNDCP_SEQUENCE_IND_ST      RABM_SNDCP_SEQUENCE_RSP_ST;

/*---------------------------------------------------------
   User Plane DATA Structs used between SNDCP and RABM.
---------------------------------------------------------*/
typedef struct
{
    VOS_UINT8        ucNsapi;
    VOS_UINT16       usDataLen;          /*byte numbers of the PDU*/
    VOS_VOID        *pPdu;               /*the head pointer of the PDU*/
}RABM_USER_PLANE_DATA_ST;

typedef RABM_USER_PLANE_DATA_ST             RABM_USER_PLANE_UNITDATA_ST;



/*---------------------------------------------------------
         Structs used for set DS Flow Report Mode.
---------------------------------------------------------*/

typedef struct
{
    /*�����ϱ�ģʽMode��ȡ��������ֵ:
            RABM_FLOW_REPORT_ACCUMULATE : �ϱ�����RABID���ۼ�����
            RABM_FLOW_REPORT_WITH_RABID : �ϱ�ָ��RABID������
            RABM_FLOW_REPORT_TOTAL      : �ϱ�����RABID������  */
    RABM_FLOW_REPORT_MODE_ENUM       Mode;

   /*ָ����RABID,��ģʽRABM_FLOW_REPORT_WITH_RABID������*/
    VOS_UINT8       ucRabId;

}RABM_SET_FLOW_REPORT_MODE_ST;          /*���������ϱ���ģʽ*/



/*****************************************************************************
  8 UNION����
typedef union
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];

} MAPS_TEMPLATE_UNION;
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
extern VOS_UINT8* pgucMapsTemplateBuffer;ָ�룫ȫ�ֱ�ʶ�����ͣ�ģ��������������
*****************************************************************************/

/*���������ϱ�ģʽ*/
extern RABM_SET_FLOW_REPORT_MODE_ST     gstRabmFlowReportMode;


/*****************************************************************************
  5 ��Ϣͷ����
ģ���������士HEADER
*****************************************************************************/



/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
/*---------------------------------------------------------
            MSG used between SNDCP and RABM.
---------------------------------------------------------*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*��Ϣ����*/
    VOS_UINT16                          usPId;              /*SNDCPʹ�õ��ӽ��̱�ʶ����5����*/
    RABM_SNDCP_SEQUENCE_IND_ST          RabmSnSequenceInd;
}RABM_SN_SEQUENCE_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;         /*SNDCP�Ļظ���Ϣʹ��V100R001����Ϣͷ*/
    RABM_SNDCP_SEQUENCE_RSP_ST          RabmSnSequenceRsp;

}RABM_SN_SEQUENCE_RSP_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;         /*SNDCP�Ļظ���Ϣʹ��V100R001����Ϣͷ*/
    RABM_USER_PLANE_DATA_ST             RabmSnDataInd;

}RABM_SN_DATA_IND_MSG;                          /*SNDCP������ȷ��������Ϣ�ṹ��*/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;         /*SNDCP�Ļظ���Ϣʹ��V100R001����Ϣͷ*/
    RABM_USER_PLANE_UNITDATA_ST         RabmSnUnitDataInd;

}RABM_SN_UNITDATA_IND_MSG;                    /*SNDCP�����з�ȷ��������Ϣ�ṹ��*/

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;
    VOS_UINT16                          usPId;              /*SNDCPʹ�õ��ӽ��̱�ʶ����5����*/
}RABM_SNDCP_SAVE_DATA_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32                          ulMsgName;         /*SNDCP�Ļظ���Ϣʹ��V100R001����Ϣͷ*/
}RABM_SNDCP_SAVE_DATA_RSP_MSG;

typedef  struct
{
    VOS_UINT8                           ucFlag;             /*VOS_YES, ��ǰNSAPI��Ч; VOS_NO, ��Ч*/
    VOS_UINT8                           ucRbId;             /*NSAPI��Ӧ��RbId*/
    VOS_UINT8                           ucReserve[2];       /*����*/
}SNDCP_NSAPI_MAP_RB_INFO;


#define   SNDCP_RABM_MAX_NSAPI_NUM   16
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;
    VOS_UINT16                          usPId;
    SNDCP_NSAPI_MAP_RB_INFO             astNsapiMapRb[SNDCP_RABM_MAX_NSAPI_NUM]; /* ��������ֵΪNSAPI */
}RABM_SNDCP_RESUME_DATA_IND_MSG;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;         /*SNDCP�Ļظ���Ϣʹ��V100R001����Ϣͷ*/
}RABM_SNDCP_RESUME_DATA_RSP_MSG;

/*---------------------------------------------------------
            MSG used between APS and RABM.
---------------------------------------------------------*/
#define RABM_APS_SET_TRANSMODE_MSG_TYPE                 4    /*����TAF ==> RABM��ԭ��ID��RabmTafInterface.h�ж���*/


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*��Ϣ����*/
    RABM_APS_SET_TRANS_MODE_ST          RabmApsSetTransMode;
}RABM_APS_SET_TRANSMODE_MSG;


/*****************************************************************************
  9 FUNCTIONS ����
*****************************************************************************/
/*----------------------------------------------------------------------------
            FUNCTIONS used by APS and provided by RABM.
----------------------------------------------------------------------------*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Function            : Rabm_setTransMode()
Description         : This function is used by APS to set translation mode in RABM.
Calls               :
Called By           :
Date Accessed       :
Date Update         :
Input               : pSetTransMode        ����ģʽ�ṹ��ָ��
Output              :
Return Value        : VOID
Others              :
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
extern VOS_VOID  NAS_RabmSetTransMode( RABM_APS_SET_TRANS_MODE_ST   *pSetTransMode );



extern VOS_VOID RABM_SendUlData(VOS_UINT8 ucRabId, TTF_MEM_ST *pData);


extern VOS_UINT32 RABM_SendDlData(VOS_UINT8 ucRbId, TTF_MEM_ST *pData);



extern VOS_VOID NAS_RABM_SetTcFlowCtrl(VOS_VOID);



extern VOS_VOID NAS_RABM_ClearTcFlowCtrl(VOS_VOID);

VOS_VOID NAS_RABM_GetCurrFluxRate(
    VOS_UINT32                             *pulCurrSndFluxRate,
    VOS_UINT32                             *pulCurrRcvFluxRate
);

/*****************************************************************************
 10 OTHERS����
*****************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of RabmInterface.h*/
