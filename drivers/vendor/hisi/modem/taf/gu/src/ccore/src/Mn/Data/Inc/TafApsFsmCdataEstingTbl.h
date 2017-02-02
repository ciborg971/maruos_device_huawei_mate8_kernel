

#ifndef __TAFAPSFSMCDATAESTINGTBL_H__
#define __TAFAPSFSMCDATAESTINGTBL_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern TAF_STA_STRU                             g_astTafApsCdataEstingStaTbl[];
#define TAF_APS_GetCdataEstingStaTbl()          (g_astTafApsCdataEstingStaTbl)

#endif


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum TAF_APS_CDATA_ESTING_SUBSTA_ENUM
{
    TAF_APS_CDATA_ESTING_SUBSTA_INIT                          = 0x00,    /* CDATA ESTING״̬���ĳ�ʼ״̬ */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF        = 0x01,    /* CDMAģʽ������ʱ�������ݷ������ӡ����ȴ�XCC�ظ�����������״̬ */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED         = 0x02,    /* CDMAģʽ������ʱ�������ݷ������ӡ����ȴ�XCC�ϱ�SO��״̬ */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF         = 0x03,    /* CDMAģʽ�±���ʱ�������ݷ������ӡ����ȴ�XCC�ظ�Ӧ����״̬ */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND   = 0x04,    /* CDMAģʽ�±���ʱ�������ݷ������ӡ����ȴ�XCC�ϱ�CONNECTED��״̬ */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL          = 0x05,    /* CDMAģʽ������ʱ�������ӽ��������ȴ��ز���״̬ */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF        = 0x06,    /* CDMAģʽ������ʱ�������ݷ������ӡ����ȴ�HSM�ظ�����������״̬ */
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
    TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF    = 0x07,    /* CDMAģʽ������ʱ�������ݷ������ӡ����ȴ�EHSM�ظ�����������״̬ */
    TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND                       = 0x08,    /* CDMA ESTING״̬���Ĺ���״̬ */
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */
    TAF_APS_CDATA_ESTING_SUBSTA_BUTT                          = 0xFF
} ;
typedef VOS_UINT32 TAF_APS_CDATA_ESTING_SUBSTA_ENUM_UINT32;



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
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 TAF_APS_GetCdataEstingStaTblSize( VOS_VOID );
TAF_FSM_DESC_STRU * TAF_APS_GetCdataEstingFsmDescAddr( VOS_VOID );

#endif







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

#endif /* end of TafApsFsmCdataEstingTbl.h */
