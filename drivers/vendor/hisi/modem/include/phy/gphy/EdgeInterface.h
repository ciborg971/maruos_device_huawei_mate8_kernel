

#ifndef __EDGEINTERFACE_H__
#define __EDGEINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define EDGE_CODE_SCHEME_MCS_MASK           0x1000      /* EGPRS���뷽ʽ���� */
#define EDGE_UL_TS_MAX_NUM                  4           /* �������ʱ϶���� */
#define EDGE_DL_TS_MAX_NUM                  5           /* �������ʱ϶���� */
#define GPRS_WITHOUT_START_TIME             0x80000000  /* START TIMEΪ������Ч�ĺ� */

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/*========================*/ /*������뷽ʽ��ö��*/
enum EDGE_CODE_SCHEME_ENUM
{
    EDGE_CODE_SCHEME_CS_1                   = 0x0000,
    EDGE_CODE_SCHEME_CS_2                   = 0x0001,
    EDGE_CODE_SCHEME_CS_3                   = 0x0002,
    EDGE_CODE_SCHEME_CS_4                   = 0x0003,
    EDGE_CODE_SCHEME_MCS_1                  = 0x1000,
    EDGE_CODE_SCHEME_MCS_2                  = 0x1001,
    EDGE_CODE_SCHEME_MCS_3                  = 0x1002,
    EDGE_CODE_SCHEME_MCS_4                  = 0x1003,
    EDGE_CODE_SCHEME_MCS_5                  = 0x1004,
    EDGE_CODE_SCHEME_MCS_6                  = 0x1005,
    EDGE_CODE_SCHEME_MCS_7                  = 0x1006,
    EDGE_CODE_SCHEME_MCS_8                  = 0x1007,
    EDGE_CODE_SCHEME_MCS_9                  = 0x1008,
    EDGE_CODE_SCHEME_MCS_5_7                = 0x1009,
    EDGE_CODE_SCHEME_MCS_6_9                = 0x100a,
    EDGE_CODE_SCHEME_BUTT
};

typedef VOS_UINT16 EDGE_CODE_SCHEME_ENUM_UINT16;

/*================*/ /* RRBP��Ϣ���ʽ����ö�� */
enum PHY_BURST_TPYE_ENUM
{
    PHY_ACCESS_BURST_8_BIT                  = 0,
    PHY_ACCESS_BURST_11_BIT                 = 1,
    PHY_NORMAL_BURST_23_BYTE                = 2
};

typedef VOS_UINT16 PHY_BURST_TPYE_ENUM_UINT16;

/*================*/ /* RRBP��Ϣ�ظ����͵�ö�� */
enum GRR_RRBP_CNF_ENUM
{
    GRR_RRBP_NO_CNF                         = 0,
    GRR_RRBP_UL_CNF                         = 1,
    GRR_RRBP_DL_CNF                         = 2
};

typedef VOS_UINT16 GRR_RRBP_CNF_ENUM_UINT16;

/*========================*/ /* GMACģʽ��ö�� */
enum GMAC_MODE_ENUM
{
    GMAC_MODE_SINGLE_BLOCK_ALLOC            = 0,
    GMAC_MODE_MULTI_BLOCK_ALLOC,
    GMAC_MODE_DYNAMIC_ALLOC,                        /* _H2ASN_MsgChoice  MPHP_DYNAMIC_ALLOCATION_ST*/
    GMAC_MODE_EXT_DYNAMIC_ALLOC,                    /* _H2ASN_MsgChoice  MPHP_DYNAMIC_ALLOCATION_ST*/
    GMAC_MODE_FIXED_ALLOC,                          /* _H2ASN_MsgChoice  MPHP_FIXED_ALLOCATION_ST*/
    GMAC_MODE_BUTT
};

typedef VOS_UINT16 GMAC_MODE_ENUM_UINT16;

/*========================*/ /* EDGE�ظ������ö�� */
enum EDGE_CNF_RESULT_ENUM
{
   EDGE_CNF_RESULT_SUCCESS                  = 0,
   EDGE_CNF_RESULT_FAIL
};

typedef VOS_UINT16 EDGE_CNF_RESULT_ENUM_UINT16;

/*========================*/ /* EDGE�ǡ����ö�� */
enum EDGE_YES_OR_NO_ENUM
{
   EDGE_YES                                 = 1,
   EDGE_NO                                  = 0
};

typedef VOS_UINT16 EDGE_YES_OR_NO_ENUM_UINT16;

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
#pragma pack(4)

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* EdgeInterface.h */


