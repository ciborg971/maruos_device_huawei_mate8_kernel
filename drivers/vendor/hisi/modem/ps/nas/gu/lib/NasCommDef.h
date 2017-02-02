/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

******************************************************************************
  �� �� ��   : NasCommDef.h
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2006��8��25��
  ����޸�   :
  ��������   : NAS�������ݶ���͹����ӿ�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��8��28��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __NAS_COMM_DEFS_H__
#define __NAS_COMM_DEFS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#pragma pack(4)


/*****************************************************************************
  2 ��������
*****************************************************************************/

/* ����IMSI���ȶ��� */

#define   NAS_MAX_IMSI_LENGTH                       (9)

/* ����IE��ƫ�� */

#define IE_OFFSET(s,m)                              ((VOS_UINT32)((VOS_VOID *)(&(((s *)0)->m))))

/* network capability���� */
#define NAS_GMM_NETWORK_EMM_COMB_CAPABILITY_POS     (0x20)
#define NAS_GMM_NETWORK_EMM_ISR_POS                 (0x10)
#define NAS_GMM_NETWORK_EMM_EPC_CAPABILITY_POS      (0x08)


#define NAS_SET_GMM_NETWORK_EMM_COMB_CAPABILITY(ucFo, ucCapabFlag) ((ucFo) |= (ucCapabFlag))
#define NAS_SET_GMM_NETWORK_EMM_ISR_SUPPORT(ucFo, ucCapabFlag)     ((ucFo) |= (ucCapabFlag))
#define NAS_SET_GMM_NETWORK_EMM_EPC_CAPABILITY(ucFo, ucCapabFlag)  ((ucFo) |= (ucCapabFlag))




/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/
/* NASЭ����صĴ����붨�塣�ο�3GPP 24.008 - 8 */
enum NAS_PROTOCOL_ERR_ENUM
{
    NAS_PROT_ERR_NO_ERROR,
    NAS_PROT_ERR_MSG_TOO_SHORT,
    NAS_PROT_ERR_TI_UNKNOWN,
    NAS_PROT_ERR_MSG_TYPE_UNKNOWN,
    NAS_PROT_ERR_INCOMPATIBLE_STATE,
    NAS_PROT_ERR_MANDATORY_IE_ERR,
    NAS_PROT_ERR_NON_SEM_IE_ERR,
    NAS_PROT_ERR_OPTIONAL_IE_ERR,
    NAS_PROT_ERR_CONDITIONAL_IE_ERR,
    NAS_PROT_ERR_INCORRECT_CONTENT,
    NAS_PROT_ERR_INCOMPATIBLE_DESTINATION,
    NAS_PROT_ERR_NOT_SPECIFIED
};
typedef VOS_UINT8 NAS_PROTOCOL_ERR_ENUM_U8;


/*****************************************************************************
 ö����    : NAS_MM_COM_SERVICE_STATUS_ENUM
 �ṹ˵��  : MM����״̬
*****************************************************************************/
enum NAS_MM_COM_SERVICE_STATUS_ENUM
{
    MM_COM_SRVST_NORMAL_SERVICE         = 0 ,
    MM_COM_SRVST_LIMITED_SERVICE,
    MM_COM_SRVST_LIMITED_SERVICE_REGION,
    MM_COM_SRVST_NO_IMSI,
    MM_COM_SRVST_NO_SERVICE,
    MM_COM_SRVST_NO_CHANGE,
    MM_COM_SRVST_DEEP_SLEEP,
    MM_COM_SRVST_BUTT
};
typedef VOS_UINT8   NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MM_COM_SERVICE_STATUS_ENUM
 �ṹ˵��  : MM������
*****************************************************************************/
enum NAS_MM_COM_SERVICE_DOMAIN_ENUM
{
    MM_COM_SRVDOMAIN_NO_DOMAIN          = 0 ,
    MM_COM_SRVDOMAIN_CS,
    MM_COM_SRVDOMAIN_PS,
    MM_COM_SRVDOMAIN_CS_PS,
    MM_COM_SRVDOMAIN_NO_CHANGE,
    MM_COM_SRVDOMAIN_Not_Reg_PLMN_Searching,
    MM_COM_SRVDOMAIN_BUTT
};
typedef VOS_UINT8   NAS_MM_COM_SERVICE_DOMAIN_ENUM_UINT8;



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

#endif /* __NAS_COMM_DEFS_H__ */

