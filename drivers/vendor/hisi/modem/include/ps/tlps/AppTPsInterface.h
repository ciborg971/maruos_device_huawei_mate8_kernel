

#ifndef __APPTPSINTERFACE_H__
#define __APPTPSINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "OmCommon.h"
#include  "PsTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
/*****************************************************************************
 ö����    : APP_TRRC_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC <-> APP �ӿ���ϢID
*****************************************************************************/
enum APP_TPS_MSG_ID_ENUM
{
    /* TRRC����APP��ԭ�� */
    ID_APP_TRRC_DT_BASIC_INFO_REQ        = (PS_MSG_ID_APP_TO_TRRC_BASE + 0x00),   /* _H2ASN_MsgChoice TRRC_DT_SERVING_BASIC_INFO_REQ_STRU */

    /* APP����TRRC��ԭ�� */
    ID_TRRC_APP_DT_BASIC_INFO_CNF        = (PS_MSG_ID_TRRC_TO_APP_BASE + 0x01),   /* _H2ASN_MsgChoice TRRC_DT_SERVING_BASIC_INFO_CNF_STRU */

    ID_TRRC_APP_DT_BASIC_INFO_IND        = (PS_MSG_ID_TRRC_TO_APP_BASE + 0x02),   /* _H2ASN_MsgChoice TRRC_DT_SERVING_BASIC_INFO_IND_STRU */

    /* TDS CMCC Begin */
    ID_APP_TL2_DT_3A_INFO_IND            = (PS_MSG_ID_TRRC_TO_APP_BASE + 0x03),    /* _H2ASN_MsgChoice TRRC_MEAS_3A_INFO_IND_STRU */
    ID_APP_TL2_DT_MEAS_GSM_IND           = (PS_MSG_ID_TRRC_TO_APP_BASE + 0x04),    /* _H2ASN_MsgChoice TRRC_MEAS_IRAT_CELL_INFO_IND_STRU */
    /* TDS CMCC End */

    /* TRRC����APP��ԭ�� */
    ID_APP_TL2_DT_THR_INFO_REQ           = (PS_MSG_ID_APP_TO_TDSL2_BASE + 0x00),     /* _H2ASN_MsgChoice TRRC_DT_THROUGHPUT_INFO_REQ_STRU */
    ID_APP_TL2_DT_TRACE_PKT_REQ          = (PS_MSG_ID_APP_TO_TDSL2_BASE + 0x01),     /* _H2ASN_MsgChoice TDS_L2_DT_TRACE_PKT_REQ_STRU */
    ID_APP_TL2_OM_THR_INFO_REQ           = (PS_MSG_ID_APP_TO_TDSL2_BASE + 0x02),     /* _H2ASN_MsgChoice TRRC_DT_THROUGHPUT_INFO_REQ_STRU */

    /* APP����TRRC��ԭ�� */
    ID_TL2_APP_DT_THR_INFO_CNF           = (PS_MSG_ID_TDSL2_TO_APP_BASE + 0x01),     /* _H2ASN_MsgChoice TRRC_DT_THROUGHPUT_INFO_CNF_STRU */
    ID_TL2_APP_DT_THR_INFO_IND           = (PS_MSG_ID_TDSL2_TO_APP_BASE + 0x02),     /* _H2ASN_MsgChoice TRRC_DT_THROUGHPUT_INFO_IND_STRU */
    ID_TL2_APP_DT_TRACE_PKT_CNF          = (PS_MSG_ID_TDSL2_TO_APP_BASE + 0x03),     /* _H2ASN_MsgChoice TDS_L2_DT_TRACE_PKT_CNF_STRU */
    ID_TL2_APP_OM_THR_INFO_CNF           = (PS_MSG_ID_TDSL2_TO_APP_BASE + 0x04),     /* _H2ASN_MsgChoice TRRC_DT_THROUGHPUT_INFO_CNF_STRU */
    ID_TL2_APP_OM_THR_INFO_IND           = (PS_MSG_ID_TDSL2_TO_APP_BASE + 0x05),     /* _H2ASN_MsgChoice TRRC_DT_THROUGHPUT_INFO_IND_STRU */

    ID_TL2_APP_DT_RB_INFO_IND            = (PS_MSG_ID_TDSL2_TO_APP_BASE + 0x06),  /* _H2ASN_MsgChoice TL2_DT_RB_INFO_IND_STRU */
    ID_TL2_APP_DT_HSDPA_INFO_IND         = (PS_MSG_ID_TDSL2_TO_APP_BASE + 0x07),  /* _H2ASN_MsgChoice TL2_DT_HSDPA_INFO_IND_STRU */

    ID_APP_TL2_MSG_ID_BUTT
};
typedef VOS_UINT32  APP_TPS_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 Enum
*****************************************************************************/



/*****************************************************************************
   5 STRUCT
*****************************************************************************/



/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
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

#endif /* end of AppRrcInterface.h */
