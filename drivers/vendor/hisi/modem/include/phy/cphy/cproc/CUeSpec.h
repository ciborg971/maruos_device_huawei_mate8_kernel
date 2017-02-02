

#ifndef __CUESPECT_H__
#define __CUESPECT_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define PS_CUE_IMSI_MAX_SIZE            (15)                  /* IMSI����󳤶� */

#define PS_CUE_BAND_CLASS_0             (0)                   /* Bandclass */
#define PS_CUE_BAND_CLASS_1             (1)
#define PS_CUE_BAND_CLASS_2             (2)
#define PS_CUE_BAND_CLASS_3             (3)
#define PS_CUE_BAND_CLASS_4             (4)
#define PS_CUE_BAND_CLASS_5             (5)
#define PS_CUE_BAND_CLASS_6             (6)

/* Э��汾 */
#define PS_CUE_1X_REV_7                 (7)                /* ��Ӧversion A*/
#define PS_CUE_1X_REV_6                 (6)
#define PS_CUE_1X_REV_5                 (5)
#define PS_CUE_1X_REV_4                 (4)
#define PS_CUE_1X_REV_3                 (3)
#define PS_CUE_1X_REV_2                 (2)
#define PS_CUE_1X_REV_1                 (1)
#define PS_CUE_1X_REV_UNKNOWN           (0)

/*EVDO protocol revision*/
#define PS_CUE_HRPD_REV_1                 (1)
#define PS_CUE_HRPD_REV_UNKNOWN           (0)


/*****************************Э�鶨��Ĺ��**********************************/
#define PS_CUE_1X_N6M                   (6)                     /* Supported Traffic Channel Active Set size */


#define PS_CUE_MAX_SUP_SO                (32)                   /* Max Num of Supported SO */
#define PS_CUE_MAX_ALT_SO                (8)                    /* Max Num of ALTERNATE SO */
#define PS_CUE_MAX_COMP_SO               (32)                   /* Max Num of COMPATILE SO */

#define PS_CUE_MAX_CONNECTION_NUM        (4)                    /* Max Num of CONNECTIONs */
#define PS_CUE_MAX_STORED_SERVICE_CFG_NUM  (4)                    /* Max Num of STORED SERVICE CFG */
#define PS_CUE_MAX_SERVICE_CFG_NUM       (PS_CUE_MAX_STORED_SERVICE_CFG_NUM +1 + 1)                    /* Max Num of SERVICE CFG */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



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

#endif /* end of CUeSpec.h */

