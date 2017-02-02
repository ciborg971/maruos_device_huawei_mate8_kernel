

#ifndef __LPS_SOFTDEBUG_H__
#define __LPS_SOFTDEBUG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "LUPAppItf.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define LPS_OM_IPV6_ADDR_LEN    16
#define LPS_OM_IPV4_ADDR_LEN     4
#define LPS_NAS_ESM_MAX_EPSB_NUM            (11)                /*��������*/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : LPS_LNAS_STA_ENUM
 ö��˵��  : NAS״̬
*****************************************************************************/
enum LPS_LNAS_STA_ENUM
{
    LPS_LNAS_STA_ATTACHED                 = 0,    /*NAS����ע��̬*/
    LPS_LNAS_STA_DETACHED                 = 1,    /*NAS����ȥע��̬*/
    LPS_LNAS_STA_NO_SERVICE               = 2,    /*NAS���ڸ�������ʧ״̬*/
    LPS_LNAS_STA_OTHER                    = 3,    /*����״̬*/

    LPS_LNAS_STA_BUTT
};
typedef VOS_UINT32  LPS_LNAS_STA_ENUM_UINT32;


/*****************************************************************************
 ö����    : LPS_NAS_IP_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : IP����ö��
*****************************************************************************/
enum LPS_NAS_IP_TYPE_ENUM
{
    LPS_NAS_IP_TYPE_IPV4                 = 0x01,
    LPS_NAS_IP_TYPE_IPV6                 = 0x02,
    LPS_NAS_IP_TYPE_IPV4_IPV6            = 0x03,

    LPS_NAS_IP_TYPE_BUTT
};
typedef VOS_UINT8 LPS_NAS_IP_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : LPS_LRRC_PROTOCOL_STATE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC��Э��״̬
*****************************************************************************/
enum LPS_LRRC_PROTOCOL_STATE_ENUM
{
    LPS_LRRC_PROTOCOL_IDLE                   = 0,
    LPS_LRRC_PROTOCOL_CONNECTED              = 1,
    LPS_LRRC_PROTOCOL_STATE_BUTT
};
typedef VOS_UINT8 LPS_LRRC_PROTOCOL_STATE_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
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
 �ṹ��    : LPS_LRRC_S_TMSI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : S-TMSI���ݽṹ
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enIsExisted;           /* ����ָʾS-TMSI�Ƿ����, PS_TRUE:����, PS_FALSE:������ */
    VOS_UINT8                           ucMmec;
    VOS_UINT8                           aucReserved[2];
    VOS_UINT32                          ulMTmsi;
}LPS_LRRC_S_TMSI_STRU;

/*****************************************************************************
 �ṹ��    : LPS_LRRC_DEBUG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    LPS_LRRC_PROTOCOL_STATE_ENUM_UINT8          enRrcPtlState;   /* RRCЭ��״̬ */
    VOS_UINT8                                   aucReserved[3];
    LPS_LRRC_S_TMSI_STRU                        stStmsi;         /* S-TMSI��Ϣ */
}LPS_LRRC_DEBUG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LPS_LNAS_IP_ADDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE IP��ַ��PDN ID��Ϣ
*****************************************************************************/
typedef struct
{
    LPS_NAS_IP_TYPE_ENUM_UINT8          enIpType;   /*IP��ַ����*/
    VOS_UINT8                           ucPndId;    /*ȱʡ���غ�*/
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucIpv4Addr[LPS_OM_IPV4_ADDR_LEN]; /*IPV4��ַ*/
    VOS_UINT8                           aucIpv6Addr[LPS_OM_IPV6_ADDR_LEN]; /*IPV6��ַ*/
}LPS_LNAS_IP_ADDR_STRU;


/*****************************************************************************
 �ṹ��    : LPS_LNAS_UE_IP_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE IP��ַ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                       ulPdnNum; /*��Чȱʡ������Ŀ*/
    LPS_LNAS_IP_ADDR_STRU            astUeIpInfo[LPS_NAS_ESM_MAX_EPSB_NUM]; /*ȱʡ���ص�IP��ַ*/
}LPS_LNAS_UE_IP_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LPS_AUTOTEST_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PSΪ�Զ��������ϱ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    L2_THROUGHPUT_ULDL_STAT_STRU                    stAppThoughputInfo;  /*APP���͸�PDCP/APP���յ�PDCP��ͳ����Ϣ*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stPdcpThoughputInfo; /*PDCP���͸�RLC/PDCP���յ�RLC��ͳ����Ϣ*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stRlcThoughputInfo;  /*RLC���͸�MAC/RLC���յ�MAC��ͳ����Ϣ*/
    L2_THROUGHPUT_ULDL_STAT_STRU                    stMacThoughputInfo;  /*MAC���͸�RTT/MAC���յ�RTT��ͳ����Ϣ*/
    LPS_LNAS_UE_IP_INFO_STRU                        stUeIpInfo;
    VOS_UINT32                                      ulNasStatus;
    VOS_UINT8                                       ucRrcStatus;
    VOS_UINT8                                       enIsExisted;
    VOS_UINT8                                       ucMmec;
    VOS_UINT8                                       aucReserved[1];
    VOS_UINT32                                      ulTmsi;
    /*VOS_UINT8                                       aucUeIP[4];
 */
    VOS_UINT32                                      ulIdleMemRes;

}LPS_AUTOTEST_INFO_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern LPS_LNAS_STA_ENUM_UINT32 LNAS_DEBUG_GetEmmSta(VOS_VOID);
extern VOS_VOID LNAS_DEBUG_GetUeIpInfo(LPS_LNAS_UE_IP_INFO_STRU* pstUeIpInfo);
extern  VOS_UINT32  LPS_LRRC_GetRrcSoftDebugInfo( LPS_LRRC_DEBUG_INFO_STRU *pstPsRrcSoftDebugInfo );
extern  VOS_VOID PrintLPsInfo(const LPS_AUTOTEST_INFO_STRU *pstAutoTestInfo);
extern  VOS_VOID GetLPsInfo(VOS_VOID);

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

#endif /* end of LPsSoftDebug.h */
