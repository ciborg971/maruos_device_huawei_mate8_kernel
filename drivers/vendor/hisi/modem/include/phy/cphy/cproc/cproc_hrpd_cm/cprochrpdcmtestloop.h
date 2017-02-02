/** ****************************************************************************

                    Huawei Technologies Sweden AB (C), 2001-2015

 ********************************************************************************
 * @author    Automatically generated by DAISY
 * @version
 * @date      2015-06-08
 * @file
 * @brief
 * This interface provides CPROC_HRPD test loop interface towards CTTF_HRPD.
 * This includes:
 * -  Input: Statistics reset requests
 * -  Input: Test loop configuration requests
 * -  Input: Statistics read requests
 * -  Output: Confirms to requester
 * @copyright Huawei Technologies Sweden AB
 *******************************************************************************/
#ifndef CPROCHRPDCMTESTLOOP_H
#define CPROCHRPDCMTESTLOOP_H

/*******************************************************************************
 1. Other files included
*******************************************************************************/

#include "vos.h"
#include "cprochrpdcmactch.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)

/*******************************************************************************
 2. Macro definitions
*******************************************************************************/


/*******************************************************************************
 3. Enumerations declarations
*******************************************************************************/

/** ****************************************************************************
 * Name        : CPROCHRPDCMTESTLOOP_MSG_TYPE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CPROCHRPDCMTESTLOOP_MSG_TYPE_ENUM
{
    ID_CTTF_CPROC_HRPD_TL_CFG_REQ                           = 0x4700, /**< @sa CTTF_CPROC_HRPD_TL_CFG_REQ_STRU */
    ID_CTTF_CPROC_HRPD_TL_GET_STAT_REQ                      = 0x4701, /**< @sa CTTF_CPROC_HRPD_TL_GET_STAT_REQ_STRU */
    ID_CPROC_CTTF_HRPD_TL_GET_STAT_CNF                      = 0x4702, /**< @sa CPROC_CTTF_HRPD_TL_GET_STAT_CNF_STRU */
    ID_CTTF_CPROC_HRPD_TL_RESET_STAT_REQ                    = 0x4703, /**< @sa CTTF_CPROC_HRPD_TL_RESET_STAT_REQ_STRU */
    ID_CPROCHRPDCMTESTLOOP_MSG_TYPE_ENUM_BUTT               = 0xFFFF
};
typedef VOS_UINT16 CPROCHRPDCMTESTLOOP_MSG_TYPE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CPROC_HRPD_TL_ACKCH_FIXED_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CPROC_HRPD_TL_ACKCH_FIXED_ENUM
{
    CPROC_HRPD_TL_ACKCH_FIXED_0         = 0x0000,
    CPROC_HRPD_TL_ACKCH_FIXED_1         = 0x0001,
    CPROC_HRPD_TL_ACKCH_FIXED_DISABLED  = 0x0002,
    CPROC_HRPD_TL_ACKCH_FIXED_BUTT      = 0x0003
};
typedef VOS_UINT16 CPROC_HRPD_TL_ACKCH_FIXED_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CPROC_HRPD_TL_ACKCH_MOD_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CPROC_HRPD_TL_ACKCH_MOD_ENUM
{
    CPROC_HRPD_TL_ACKCH_MOD_DISABLED    = 0x0000, /**< Disabled */
    CPROC_HRPD_TL_ACKCH_MOD_BPSK        = 0x0001, /**< ACK Channel Mode BPSK */
    CPROC_HRPD_TL_ACKCH_MOD_OOK         = 0x0002, /**< ACK Channel Mode OOK */
    CPROC_HRPD_TL_ACKCH_MOD_BUTT        = 0x0003
};
typedef VOS_UINT16 CPROC_HRPD_TL_ACKCH_MOD_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CPROC_HRPD_TL_DRCCOVER_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CPROC_HRPD_TL_DRCCOVER_ENUM
{
    CPROC_HRPD_TL_DRCCOVER_0x0                    = 0x0000,
    CPROC_HRPD_TL_DRCCOVER_0x1                    = 0x0001,
    CPROC_HRPD_TL_DRCCOVER_0x2                    = 0x0002,
    CPROC_HRPD_TL_DRCCOVER_0x3                    = 0x0003,
    CPROC_HRPD_TL_DRCCOVER_0x4                    = 0x0004,
    CPROC_HRPD_TL_DRCCOVER_0x5                    = 0x0005,
    CPROC_HRPD_TL_DRCCOVER_0x6                    = 0x0006,
    CPROC_HRPD_TL_DRCCOVER_0x7                    = 0x0007,
    CPROC_HRPD_TL_DRCCOVER_VARIABLE               = 0x0008,
    CPROC_HRPD_TL_DRCCOVER_BUTT
};
typedef VOS_UINT16 CPROC_HRPD_TL_DRCCOVER_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CPROC_HRPD_TL_DRCVALUE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CPROC_HRPD_TL_DRCVALUE_ENUM
{
    CPROC_HRPD_TL_DRCVALUE_0x0                              = 0x0000,
    CPROC_HRPD_TL_DRCVALUE_0x1                              = 0x0001,
    CPROC_HRPD_TL_DRCVALUE_0x2                              = 0x0002,
    CPROC_HRPD_TL_DRCVALUE_0x3                              = 0x0003,
    CPROC_HRPD_TL_DRCVALUE_0x4                              = 0x0004,
    CPROC_HRPD_TL_DRCVALUE_0x5                              = 0x0005,
    CPROC_HRPD_TL_DRCVALUE_0x6                              = 0x0006,
    CPROC_HRPD_TL_DRCVALUE_0x7                              = 0x0007,
    CPROC_HRPD_TL_DRCVALUE_0x8                              = 0x0008,
    CPROC_HRPD_TL_DRCVALUE_0x9                              = 0x0009,
    CPROC_HRPD_TL_DRCVALUE_0xA                              = 0x000A,
    CPROC_HRPD_TL_DRCVALUE_0xB                              = 0x000B,
    CPROC_HRPD_TL_DRCVALUE_0xC                              = 0x000C,
    CPROC_HRPD_TL_DRCVALUE_0xD                              = 0x000D, /**< only valid for sub-type 2 */
    CPROC_HRPD_TL_DRCVALUE_0xE                              = 0x000E, /**< only valid for sub-type 2 */
    CPROC_HRPD_TL_DRCVALUE_FIXED_DISABLED                   = 0x000F,
    CPROC_HRPD_TL_DRCVALUE_BUTT                             = 0x0010
};
typedef VOS_UINT16 CPROC_HRPD_TL_DRCVALUE_ENUM_UINT16;

/*******************************************************************************
 4. Message Header declaration
*******************************************************************************/

/*******************************************************************************
 5. Message declaration
*******************************************************************************/

/*******************************************************************************
 6. STRUCT and UNION declaration
*******************************************************************************/

/*******************************************************************************
 7. OTHER declarations
*******************************************************************************/

/** ****************************************************************************
 * Name        : CTTF_CPROC_HRPD_TL_CFG_REQ_STRU
 *
 * Description : CTTF_CPROC_HRPD_TL_CFG_REQ configures test loop functionality
 * such as fixed DRC rate, fixed DRC cover and Fixed Ack.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CPROCHRPDCMTESTLOOP_MSG_TYPE_ENUM_UINT16                enMsgId;
    VOS_UINT16                                              usOpId;
    CPROC_HRPD_TL_DRCCOVER_ENUM_UINT16                      enDrcCover;
    CPROC_HRPD_TL_DRCVALUE_ENUM_UINT16                      enDrcValue;
    CPROC_HRPD_TL_ACKCH_FIXED_ENUM_UINT16                   enAckChFixed;
    CPROC_HRPD_TL_ACKCH_MOD_ENUM_UINT16                     enAckChannelModType; /**< BPSK or OOK (only subtype 2) */
} CTTF_CPROC_HRPD_TL_CFG_REQ_STRU;

/** ****************************************************************************
 * Name        : CTTF_CPROC_HRPD_TL_GET_STAT_REQ_STRU
 *
 * Description : CTTF_CPROC_HRPD_TL_GET_STAT_REQ request test loop statistics.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CPROCHRPDCMTESTLOOP_MSG_TYPE_ENUM_UINT16                enMsgId;
    VOS_UINT16                                              usOpId;
} CTTF_CPROC_HRPD_TL_GET_STAT_REQ_STRU;

/** ****************************************************************************
 * Name        : CPROC_CTTF_HRPD_TL_GET_STAT_CNF_STRU
 *
 * Description : Provides test loop statistics to CTTF_HRPD upon request.
 * Parameters are documented in C.S0029-B v1.0.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CPROCHRPDCMTESTLOOP_MSG_TYPE_ENUM_UINT16                enMsgId;
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucIdleASPChangeOverflow;     /**< 0: No Overflow, 1: Overflow */
    VOS_UINT8                                               ucConnectedSSChangeOverflow; /**< 0: No Overflow, 1: Overflow */
    VOS_UINT8                                               ucIdleTimeOverflow;          /**< 0: No Overflow, 1: Overflow */
    VOS_UINT8                                               ucConnectedTimeOverflow;     /**< 0: No Overflow, 1: Overflow */
    VOS_UINT16                                              usConnectedSSChange;         /**< Valid range [0..32767] */
    VOS_UINT16                                              usIdleASPChange;             /**< Valid range [0..32767] */
    VOS_UINT32                                              ulIdleTime;                  /**< Valid range [0..8388607] */
    VOS_UINT32                                              ulConnectedTime;             /**< Valid range [0..8388607] */
} CPROC_CTTF_HRPD_TL_GET_STAT_CNF_STRU;

/** ****************************************************************************
 * Name        : CTTF_CPROC_HRPD_TL_RESET_STAT_REQ_STRU
 *
 * Description : This signal request reset of statistics counters.
 * If parameter enResetIdleASP_ChangeStat is set, then both IdleASPChange and
 * IdleTime shall be reset.
 * If parameter enResetSS_ChangeStat is set, then both ConnectedSSChange and
 * ConnectedTime shall be reset.
 * Note that also the associated overflow parameter needs to be reset.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CPROCHRPDCMTESTLOOP_MSG_TYPE_ENUM_UINT16                enMsgId;
    VOS_UINT16                                              usOpId;
    CPROC_HRPD_TL_IDLE_ASP_ENUM_UINT16                      enResetIdleASP_ChangeStat; /**< IdleASPChange stats */
    CPROC_HRPD_TL_SS_ENUM_UINT16                            enResetSS_ChangeStat;      /**< SSChange stats */
} CTTF_CPROC_HRPD_TL_RESET_STAT_REQ_STRU;

/*******************************************************************************
 8. Global  declaration
*******************************************************************************/

/*******************************************************************************
 9. Function declarations
*******************************************************************************/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
