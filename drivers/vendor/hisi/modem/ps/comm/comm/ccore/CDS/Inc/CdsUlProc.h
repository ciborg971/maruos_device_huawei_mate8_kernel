

#ifndef __CDS_ULPROC_H__
#define __CDS_ULPROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*��RD�е�FilterResult/ModemId/RabId���浽TTF��ulForCds[0]��*/
/*lint -emacro({717}, CDS_UL_SAVE_RD_INFO_TO_TTF)*/
/*lint -emacro({701}, CDS_UL_SAVE_RD_INFO_TO_TTF)*/
#define CDS_UL_SAVE_RD_INFO_TO_TTF(pstIpPkt,pstRd)      \
                            do\
                            {\
                                (pstIpPkt)->ulForCds[0] = 0;\
                                (pstIpPkt)->ulForCds[0] = (((pstRd)->u16Result)<<16) | ((pstRd)->u16UsrField1);\
                            }while(0)


/*���н�IPF RESULT/ModemId/RabId���ֵ�TTF�ı�������*/
/*lint -emacro({717}, CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF)*/
/*lint -emacro({701}, CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF)*/
#define CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF(pstIpPkt,usIpfRslt,usModemId,ucRabId) \
                            do\
                            {\
                                (pstIpPkt)->ulForCds[0] = 0;\
                                (pstIpPkt)->ulForCds[0] = ((usModemId) << 8) | ucRabId;\
                                (pstIpPkt)->ulForCds[0] = ((usIpfRslt) << 16) | ((pstIpPkt)->ulForCds[0]);\
                            }while(0)


/*���н�IPF RESULT���浽TTF�ı�������,���ڶ��ι���*/
/*lint -emacro({717}, CDS_UL_SAVE_IPFRSLT_TO_TTF)*/
/*lint -emacro({701}, CDS_UL_SAVE_IPFRSLT_TO_TTF)*/
#define CDS_UL_SAVE_IPFRSLT_TO_TTF(pstIpPkt,usIpfRslt) \
                            do\
                            {\
                                (pstIpPkt)->ulForCds[0] = ((pstIpPkt)->ulForCds[0]) & 0x0000FFFF;\
                                (pstIpPkt)->ulForCds[0] = ((usIpfRslt) << 16) | ((pstIpPkt)->ulForCds[0]);\
                            }while(0)

/*��TTF�л�ȡ���˽��*/
#define CDS_UL_GET_IPF_RESULT_FORM_TTF(pstIpPkt)        ((VOS_UINT16)((((pstIpPkt)->ulForCds[0]) & 0xFFFF0000) >> 16))

/*��TTF�л�ȡModemId*/
#define CDS_UL_GET_MODEMID_FROM_TTF(pstIpPkt)           ((VOS_UINT16)((((pstIpPkt)->ulForCds[0]) & 0x0000FF00) >> 8))

/*��TTF�л�ȡRabId*/
#define CDS_UL_GET_RABID_FROM_TTF(pstIpPkt)             ((VOS_UINT8)(((pstIpPkt)->ulForCds[0]) & 0x0000000F))

/*��TTF�л�ȡPktType*/
#define CDS_UL_GET_PKT_TYPE_FROM_TTF(pstIpPkt)          ((VOS_UINT8)((((pstIpPkt)->ulForCds[0]) & 0x000000F0) >> 4))

/*IPF����б�ʶ�����λ��*/
#define CDS_UL_IPF_RESULT_PKT_ERROR_MASK                (0x7C00)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
   5 STRUCT����
*****************************************************************************/



/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

extern VOS_VOID CDS_UlProcIpfResult(VOS_VOID);
extern VOS_VOID CDS_SendUlBuffData(CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID CDS_ClearUlBuffData(CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_VOID CDS_UlDispatchDataByRanMode(CDS_ENTITY_STRU *pstCdsEntity, TTF_MEM_ST *pstIpPkt);

extern VOS_VOID CDS_TriggerUlProcOnFinalRD(VOS_VOID);
/*end*/

extern VOS_VOID CDS_UlGUClearBuffData(CDS_ENTITY_STRU *pstCdsEntity,VOS_UINT8 ucRabId);
extern VOS_VOID CDS_SendUlBuffDataToRabm(CDS_ENTITY_STRU *pstCdsEntity,VOS_UINT8 ucSendRabId);
extern VOS_VOID CDS_CDMASendUlBuffData(CDS_ENTITY_STRU *pstCdsEntity, VOS_UINT8 ucSendRabId);

/*****************************************************************************
  8 ��������
*****************************************************************************/
RABM_RAB_STATUS_ENUM_UINT32 I1_NAS_RABM_GetRabIdStatus(VOS_UINT8 ucRabId);
VOS_VOID I1_NAS_RABM_UL_DataReq(CDS_RABM_TRANS_DATA_STRU *pstUlData);
RABM_RAB_STATUS_ENUM_UINT32 I2_NAS_RABM_GetRabIdStatus(VOS_UINT8 ucRabId);
VOS_VOID I2_NAS_RABM_UL_DataReq(CDS_RABM_TRANS_DATA_STRU *pstUlData);

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

