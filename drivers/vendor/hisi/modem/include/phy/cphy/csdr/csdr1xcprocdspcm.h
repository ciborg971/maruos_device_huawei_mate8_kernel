/** ****************************************************************************

                    Huawei Technologies Sweden AB (C), 2001-2015

 ********************************************************************************
 * @author    Automatically generated by DAISY
 * @version
 * @date      2015-05-25
 * @file
 * @brief
 *
 * @copyright Huawei Technologies Sweden AB
 *******************************************************************************/
#ifndef CSDR1XCPROCDSPCM_H
#define CSDR1XCPROCDSPCM_H

/*******************************************************************************
 1. Other files included
*******************************************************************************/

#include "uphy_type_define.h"
#include "csdr1x.h"

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
 * Name        : CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CSDR1XCPROCDSPCM_MSG_TYPE_ENUM
{
    ID_CPROC_CSDR_1X_RXOFF_REQ                              = 0x0100, /**< @sa CPROC_CSDR_1X_RXOFF_REQ_STRU */
    ID_CSDR_CPROC_1X_RXOFF_CNF                              = 0x0101, /**< @sa CSDR_CPROC_1X_RXOFF_CNF_STRU */
    ID_CPROC_CSDR_1X_RXON_REQ                               = 0x0102, /**< @sa CPROC_CSDR_1X_RXON_REQ_STRU */
    ID_CSDR_CPROC_1X_RXON_CNF                               = 0x0103, /**< @sa CSDR_CPROC_1X_RXON_CNF_STRU */
    ID_CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_BUTT                  = 0xFFFF
};
typedef PHY_UINT16 CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CSDR_1X_RXON_TYPE_ENUM_UINT16
 *
 * Description : This enum tells the type of RxOn - store or use RF related
 * parameters.
 *******************************************************************************/
enum CSDR_1X_RXON_TYPE_ENUM
{
    CSDR_1X_RXON_TYPE_SF                = 0x0000, /**< Go to requested frequency without using stored parameters */
    CSDR_1X_RXON_TYPE_SF_TO_CF          = 0x0001, /**< Go to requested frequency, store current parameters */
    CSDR_1X_RXON_TYPE_CF_TO_SF          = 0x0002, /**< Go to requested frequency, use stored parameters */
    CSDR_1X_RXON_TYPE_SF_SLOTTED_WAKEUP = 0x0003,
    CSDR_1X_RXON_TYPE_BUTT              = 0x0004
};
typedef PHY_UINT16 CSDR_1X_RXON_TYPE_ENUM_UINT16;

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
 * Name        : CPROC_CSDR_1X_RXOFF_REQ_STRU
 *
 * Description : This signal is used to request Rx Off at a specific time (or
 * NOW).
 * If a specific point in time is given, it points out the first chip that
 * shall not be received (i.e. at the beginning of this PCG, the radio shall
 * be switched off).
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16                   enMsgId;
    PHY_UINT16                                              uhwOpId;
    PHY_ACTION_TIME_CHIP_32                                 uwRxOffTime; /**< 0..98304. Time in chip in one 80ms frame, or CSDR_1X_ACTION_TIME_NOW_32=0xFFFFFFFF */
} CPROC_CSDR_1X_RXOFF_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_RXOFF_CNF_STRU
 *
 * Description : This signal is sent when CSDR has turned the radio off after
 * an RXOFF request.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16                   enMsgId;
    PHY_UINT16                                              uhwOpId;
} CSDR_CPROC_1X_RXOFF_CNF_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_RXON_REQ_STRU
 *
 * Description : This signal is used to request RxOn on a certain frequency at
 * a specific time (or NOW).
 * The signal is also used to change frequency if the radio was already on.
 * If a specific point in time is given, it points out the first q-chip to be
 * completely received.
 * enStoreParams points out if RF related parameters (e.g. AGC setting) shall
 * be stored before a change of frequency.
 * enUseStoredParams points out if RF related parameters (e.g. AGC setting)
 * shall be initialized or if previously stored parameters shall be used.
 * Previously stored parameters are used e.g. when going back to serving
 * frequency after a candidate frequency measurement.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16                   enMsgId;
    PHY_UINT16                                              uhwOpId;
    PHY_ACTION_TIME_CHIP_32                                 uwRxOnTime;   /**< 0..98304. Time in chip in one 80ms frame, or CSDR_1X_ACTION_TIME_NOW_32=0xFFFFFFFF */
    CSDR_1X_ANTENNA_IND_ENUM_UINT16                         enUseAntenna; /**< In TCH Main and diversity antenna may be used. in other states Main antenna only */
    CSDR_1X_RXON_TYPE_ENUM_UINT16                           enRxOnType;
    CSDR_1X_FREQ_INFO_STRU                                  stFreqInfo;   /**< Frequency and Band Class */
} CPROC_CSDR_1X_RXON_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_RXON_CNF_STRU
 *
 * Description : This signal is sent when CSDR has turned the radio on after
 * an RXON request, or has changed frequency if the radio was already on.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XCPROCDSPCM_MSG_TYPE_ENUM_UINT16                   enMsgId;
    PHY_UINT16                                              uhwOpId;
} CSDR_CPROC_1X_RXON_CNF_STRU;

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
