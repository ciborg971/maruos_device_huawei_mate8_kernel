
#ifndef _NAS_SM_COMM_H_
#define _NAS_SM_COMM_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define NAS_SM_TRANS_SM_NW_CAUSE(SmCause)       ((SmCause) + SM_TAF_SM_NW_CAUSE_OFFSET)
#define NAS_SM_TRANS_TAF_CAUSE(TafCause)        (VOS_UINT8)((TafCause) - SM_TAF_SM_NW_CAUSE_OFFSET)

#define NAS_SM_GET_GMM_ERR_CODE_MAP_TBL_PTR()   (g_astNasSmGmmErrCodeMapTbl)
#define NAS_SM_GET_GMM_ERR_CODE_MAP_TBL_SIZE()  (sizeof(g_astNasSmGmmErrCodeMapTbl)/sizeof(NAS_SM_GMM_ERR_CODE_MAP_STRU))

/* ��ȡָ��INDEX(ȡֵ��Χ[0, 10])��PDP CONTEXT���� */
#define NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex) (&g_SmEntity.aPdpCntxtList[ucPdpCtxIndex])
#define NAS_SM_GetPdpTiFlg(ucPdpCtxIndex)       (NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex)->ucTiFlg)
#define NAS_SM_GetPdpTiValue(ucPdpCtxIndex)     (NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex)->ucTi)
#define NAS_SM_GetPdpAddrIndex(ucPdpCtxIndex)   (NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex)->ucAddrIndex)
#define NAS_SM_GET_REGISTER_FLG()               (g_SmEntity.ucRegisterFlg)
#define NAS_SM_SET_REGISTER_FLG(ucFlg)          (g_SmEntity.ucRegisterFlg = (ucFlg))

#define NAS_SM_GET_PDP_STATE(index)             (NAS_SM_GetPdpCtxInfoAddr(index)->ucState)

/* ��ȡָ��PDP ADDRESS INDEX��PDP ADDRESS���� */
#define NAS_SM_GetPdpAddrInfoAddr(ucAddrIndex)  (&g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex])
#define NAS_SM_GetPdpLinkedNsapi(ucAddrIndex)   (g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[0] + SM_NSAPI_OFFSET)

/* ����PDP ADDRESS FLAG��־λ(bit) */
#define NAS_SM_SetPdpAddrFlg(ucAddrIndex)       (g_SmPdpAddrApn.usPdpAddrFlg |= (VOS_UINT16)((VOS_UINT32)0x0001 << (ucAddrIndex)))

/* ��ȡָ��TI��Ӧ��PDP CONTEXT���� */
#define NAS_SM_GetNsapiFromTiMap(ucTi)          (g_TiMapToNsapi[ucTi])

/* ����TI��PDP INDEX��ӳ���ϵ */
#define NAS_SM_SetNsapiToTiMap(ucTi, ucNsapi)   (g_TiMapToNsapi[ucTi] = (ucNsapi))
#define NAS_SM_ClearNsapiToTiMap(ucTi)          (g_TiMapToNsapi[ucTi] = 0xFF )

/* ��ȡָ��CR��Ӧ��PDP CONTEXT���� */
#define NAS_SM_GetNsapiFromCrMap(ucCr)          (g_CrMapToNsapi[ucCr])

/* ����CR��PDP INDEX��ӳ��ϵ*/
#define NAS_SM_SetNsapiToCrMap(ucCr, ucNsapi)   (g_CrMapToNsapi[ucCr] = (ucNsapi))
#define NAS_SM_ClearNsapiToCrMap(ucCr)          (g_CrMapToNsapi[ucCr] = 0xFF )


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/




#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

