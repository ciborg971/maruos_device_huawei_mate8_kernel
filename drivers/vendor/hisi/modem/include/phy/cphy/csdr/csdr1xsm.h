
#ifndef CSDR1XSM_H
#define CSDR1XSM_H

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

/**
 * Used when no valid path information has been found.
 */
#define CSDR_1X_PATH_INVALID                                ( 0xffffffff )
/**
 * Used for shwRlsEcIo in measurement indications.
 */
#define CSDR_1X_MEAS_VALUE_NOT_INCLUDED                     ( 0x7fff )
/**
 * Max number of cell search results in one CSDR_CPROC_1X_CELL_SEARCH_IND. The
 * number of correlators is 4, and each correlator can give 16 results in one
 * run =>4*16 = 64.
 */
#define CSDR_1X_MAX_CELL_SEARCH_RESULTS_NUM                 ( 64 )
/**
 * Used when a new measurement round shall be stared when an ongoing round is
 * finished.
 */
#define CSDR_1X_START_AFTER_ONGOING                         ( 0xFFFE )
/**
 * The maximum number of results in one CSDR_CPROC_1X_PILOT_SEARCH_IND.
 */
#define CSDR_MAX_PILOT_SEARCH_RESULTS                       ( 32 )
/**
 * The maxiumum number of antennas used in an MT.
 */
#define CSDR_1X_MAX_ANTENNAS_NUM                            ( 2 )
/**
 * The maximum number of pilots in an MPS list.
 */
#define CSDR_1X_MAX_MPS_PN_LIST_NUM                         ( 6 )
/**
 * Maximum number of cells to search for in one CPROC_CSDR_1X_MEAS_START_REQ.
 */
#define CSDR_1X_MAX_CELL_SEARCH_NUM                         ( 96 )
/**
 * Maximum number of cells to measure in one CPROC_CSDR_1X_MEAS_START_REQ.
 */
#define CSDR_1X_MAX_MEAS_PN_LIST_NUM                        ( 20 )
/**
 * The maximum number of frequencies in one CPROC_CSDR_1X_SIGNAL_LEVEL_REQ and
 * CSDR_CPROC_1X_SIGNAL_LEVEL_IND
 */
#define CSDR_1X_MAX_FREQUENCIES_IN_LEVEL_SCAN               ( 50 )
/**
 * Indicates that the value is not valid.
 */
#define CSDR_1X_NOT_VALID                                   ( 0xFFFFFFFF )

/*******************************************************************************
 3. Enumerations declarations
*******************************************************************************/

/** ****************************************************************************
 * Name        : CSDR1XSM_MSG_TYPE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CSDR1XSM_MSG_TYPE_ENUM
{
    ID_CPROC_CSDR_1X_CONTINUE_REQ                           = 0x00A0, /**< @sa CPROC_CSDR_1X_CONTINUE_REQ_STRU */
    ID_CPROC_CSDR_1X_START_MEAS_REQ                         = 0x00A1, /**< @sa CPROC_CSDR_1X_START_MEAS_REQ_STRU */
    ID_CSDR_CPROC_1X_MEAS_IND                               = 0x00A2, /**< @sa CSDR_CPROC_1X_MEAS_IND_STRU */
    ID_CPROC_CSDR_1X_STOP_MEAS_REQ                          = 0x00A3, /**< @sa CPROC_CSDR_1X_STOP_MEAS_REQ_STRU */
    ID_CPROC_CSDR_1X_START_MPS_REQ                          = 0x00A4, /**< @sa CPROC_CSDR_1X_START_MPS_REQ_STRU */
    ID_CSDR_CPROC_1X_MPS_IND                                = 0x00A5, /**< @sa CSDR_CPROC_1X_MPS_IND_STRU */
    ID_CPROC_CSDR_1X_BUFFER_REQ                             = 0x00A6, /**< @sa CPROC_CSDR_1X_BUFFER_REQ_STRU */
    ID_CSDR_CPROC_1X_BUFFER_IND                             = 0x00A7, /**< @sa CSDR_CPROC_1X_BUFFER_IND_STRU */
    ID_CPROC_CSDR_1X_STOP_MPS_REQ                           = 0x00A8, /**< @sa CPROC_CSDR_1X_STOP_MPS_REQ_STRU */
    ID_CPROC_CSDR_1X_UPDATE_MPS_REQ                         = 0x00A9, /**< @sa CPROC_CSDR_1X_UPDATE_MPS_REQ_STRU */
    ID_CSDR_CPROC_1X_CELL_SEARCH_IND                        = 0x00AA, /**< @sa CSDR_CPROC_1X_CELL_SEARCH_IND_STRU */
    ID_CPROC_CSDR_1X_SM_SET_WORK_MODE_REQ                   = 0x00AB, /**< @sa CPROC_CSDR_1X_SM_SET_WORK_MODE_REQ_STRU */
    ID_CSDR_CPROC_1X_SM_SET_WORK_MODE_CNF                   = 0x00AC, /**< @sa CSDR_CPROC_1X_SM_SET_WORK_MODE_CNF_STRU */
    ID_CPROC_CSDR_1X_SIGNAL_LEVEL_REQ                       = 0x00AD, /**< @sa CPROC_CSDR_1X_SIGNAL_LEVEL_REQ_STRU */
    ID_CSDR_CPROC_1X_SIGNAL_LEVEL_IND                       = 0x00AE, /**< @sa CSDR_CPROC_1X_SIGNAL_LEVEL_IND_STRU */
    ID_CPROC_CSDR_1X_PILOT_SEARCH_REQ                       = 0x00AF, /**< @sa CPROC_CSDR_1X_PILOT_SEARCH_REQ_STRU */
    ID_CSDR_CPROC_1X_PILOT_SEARCH_IND                       = 0x00B0, /**< @sa CSDR_CPROC_1X_PILOT_SEARCH_IND_STRU */
    ID_CPROC_CSDR_1X_SM_RELEASE_ALL_REQ                     = 0x00B1, /**< @sa CPROC_CSDR_1X_SM_RELEASE_ALL_REQ_STRU */
    ID_CSDR_CPROC_1X_SM_RELEASE_ALL_CNF                     = 0x00B2, /**< @sa CSDR_CPROC_1X_SM_RELEASE_ALL_CNF_STRU */
    ID_CSDR_CPROC_1X_MEAS_CAPABILITY_IND                    = 0x00B3, /**< @sa CSDR_CPROC_1X_MEAS_CAPABILITY_IND_STRU */
    ID_CPROC_CSDR_1X_TIME_SYNC_REQ                          = 0x00B4, /**< @sa CPROC_CSDR_1X_TIME_SYNC_REQ_STRU */
    ID_CSDR_CPROC_1X_TIME_SYNC_IND                          = 0x00B5, /**< @sa CSDR_CPROC_1X_TIME_SYNC_IND_STRU */
    ID_CSDR1XSM_MSG_TYPE_ENUM_BUTT                          = 0x00B6
};
typedef PHY_UINT16 CSDR1XSM_MSG_TYPE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CSDR_1X_MPS_TYPE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CSDR_1X_MPS_TYPE_ENUM
{
    CSDR_1X_MPS_TYPE_ONE_SHOT           = 0x0000,
    CSDR_1X_MPS_TYPE_CONTINUOUS         = 0x0001,
    CSDR_1X_MPS_TYPE_BUTT               = 0x0002
};
typedef PHY_UINT16 CSDR_1X_MPS_TYPE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CSDR_1X_CELL_TYPEIND_ENUM_UINT16
 *
 * Description : Cell type for MPS - Serving cell, active set or not, IC cell
 * or not, neighbor cell.
 *******************************************************************************/
enum CSDR_1X_CELL_TYPEIND_ENUM
{
    CSDR_1X_CELL_TYPEIND_SERV           = 0x0000,
    CSDR_1X_CELL_TYPEIND_ACTIVESET_NOIC = 0x0001,
    CSDR_1X_CELL_TYPEIND_ACTIVESET_IC   = 0x0002,
    CSDR_1X_CELL_TYPEIND_NOACTIVESET_IC = 0x0003,
    CSDR_1X_CELL_TYPEIND_NEIGBHOR       = 0x0004,
    CSDR_1X_CELL_TYPEIND_BUTT           = 0x0005
};
typedef PHY_UINT16 CSDR_1X_CELL_TYPEIND_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CSDR_1X_MEAS_FREQUENCY_MODE_ENUM_UINT16
 *
 * Description : Is the measurement for Candidate Frequency or Serving
 * Frequency.
 *******************************************************************************/
enum CSDR_1X_MEAS_FREQUENCY_MODE_ENUM
{
    CSDR_1X_MEAS_FREQUENCY_MODE_CANDIDATE_FREQUENCY         = 0x0000, /**< Measurement cfg is for candidate frequency */
    CSDR_1X_MEAS_FREQUENCY_MODE_SERVING_FREQUENCY           = 0x0001, /**< Measurement cfg is for serving frequency */
    CSDR_1X_MEAS_FREQUENCY_MODE_BUTT                        = 0x0002
};
typedef PHY_UINT16 CSDR_1X_MEAS_FREQUENCY_MODE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CSDR_1X_MEAS_MODE_ENUM_UINT16
 *
 * Description : Measurement mode: on-line or off-line.
 *******************************************************************************/
enum CSDR_1X_MEAS_MODE_ENUM
{
    CSDR_1X_MEAS_MODE_ONLINE            = 0x0000,
    CSDR_1X_MEAS_MODE_OFFLINE           = 0x0001,
    CSDR_1X_MEAS_MODE_BUTT              = 0x0002
};
typedef PHY_UINT16 CSDR_1X_MEAS_MODE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CSDR_1X_MEAS_FILTER_MODE_ENUM_UINT16
 *
 * Description : This enum tells CSDR whether it shall filter the measurements
 * or not.
 * Filtering is used in TCH only.
 *******************************************************************************/
enum CSDR_1X_MEAS_FILTER_MODE_ENUM
{
    CSDR_1X_MEAS_FILTER_MODE_NOT_USE    = 0x0000, /**< Do not use filter */
    CSDR_1X_MEAS_FILTER_MODE_USE        = 0x0001, /**< Use filter */
    CSDR_1X_MEAS_FILTER_MODE_BUTT       = 0x0002
};
typedef PHY_UINT16 CSDR_1X_MEAS_FILTER_MODE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CSDR_1X_STOP_ACTION_ENUM_UINT16
 *
 * Description : This tells what to do on the stop request: release (and clear
 * variables) or halt in order to restart later.
 *******************************************************************************/
enum CSDR_1X_STOP_ACTION_ENUM
{
    CSDR_1X_STOP_ACTION_RELEASE         = 0x0000, /**< Release, clear variables */
    CSDR_1X_STOP_ACTION_HALT            = 0x0001, /**< Halt, expect later to resume */
    CSDR_1X_STOP_ACTION_BUTT            = 0x0002
};
typedef PHY_UINT16 CSDR_1X_STOP_ACTION_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CSDR_1X_SCAN_ACTION_ENUM_UINT16
 *
 * Description : Used to start and stop signal level scans.
 *******************************************************************************/
enum CSDR_1X_SCAN_ACTION_ENUM
{
    CSDR_1X_SCAN_ACTION_START_SCAN      = 0x0000, /**< Start a new scan */
    CSDR_1X_SCAN_ACTION_STOP            = 0x0001, /**< Stop ongoing scan and send report on finished results */
    CSDR_1X_SCAN_ACTION_BUTT            = 0x0002
};
typedef PHY_UINT16 CSDR_1X_SCAN_ACTION_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CSDR_1X_SEARCH_ACTION_ENUM_UINT16
 *
 * Description : Used to start and stop pilot searches. Also used to indicate
 * reason of the Pilot Search indication.
 *******************************************************************************/
enum CSDR_1X_SEARCH_ACTION_ENUM
{
    CSDR_1X_SEARCH_ACTION_START         = 0x0000, /**< Start a pilot search */
    CSDR_1X_SEARCH_ACTION_STOP          = 0x0001, /**< Stop an ongoing pilot search. */
    CSDR_1X_SEARCH_ACTION_BUTT          = 0x0002
};
typedef PHY_UINT16 CSDR_1X_SEARCH_ACTION_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CSDR_1X_BUFFER_USE_ENUM_UINT16
 *
 * Description : This enum tells how to use the buffer for off-line
 * measurements. EXISTING is used when an explicit buffer request has sent
 * (i.e. for SF measurements in slotted mode). NEW is used when CSDR is to fill
 * the buffer by itself before the measurements are performed (i.e. for CF
 * measurements both in slotted mode and in TCH).
 *******************************************************************************/
enum CSDR_1X_BUFFER_USE_ENUM
{
    CSDR_1X_BUFFER_USE_EXISTING         = 0x0000, /**< Use samples already in buffer */
    CSDR_1X_BUFFER_USE_NEW              = 0x0001, /**< Fill buffer before use */
    CSDR_1X_BUFFER_USE_BUTT             = 0x0002
};
typedef PHY_UINT16 CSDR_1X_BUFFER_USE_ENUM_UINT16;

/*******************************************************************************
 4. Message Header declaration
*******************************************************************************/

/*******************************************************************************
 5. Message declaration
*******************************************************************************/

/*******************************************************************************
 6. STRUCT and UNION declaration
*******************************************************************************/

/** ****************************************************************************
 * Name        : CSDR_1X_CS_INFO_STRU
 *
 * Description : PN info
 *******************************************************************************/
typedef struct
{
    PHY_UINT16                          uhwPNIndex;  /**< Range: 0--511, PILOT_PN */
    PHY_UINT16                          uhwReserved; /**< 32 bit alignment */
    PHY_UINT32                          uwPNPhase;   /**< Tail of the search window, in 1/4 chips */
} CSDR_1X_CS_INFO_STRU;

/** ****************************************************************************
 * Name        : CSDR_1X_PROC_MEASUREMENT_STRU
 *
 * Description : This struct carries the measurement result for one cell/pilot.
 * In MPS for F-SYNC read after initial pilot search, PNOffset is set to
 * CSDR_1X_PN_INDEX_NOT_KNOWN.
 * shwRlsEcN0 is set to CSDR_1X_MEAS_VALUE_NOT_INCLUDED in measurement reports
 * and in MPS reports when not all pilots in the radio link set have results
 * (e.g. in the first report after an MPS_START).
 * uwDelaySpreadRMS, uwFirstPathOffset and uwLastPathOffset use
 * CSDR_1X_PATH_INVALID if no relaible paths have been found.
 *******************************************************************************/
typedef struct
{
    PHY_UINT16                          uhwPNIndex;          /**< 0..511, CSDR_1X_PN_INDEX_NOT_KNOWN, The PN Offset of the measured cell/pilot */
    PHY_INT16                           shwRscp;             /**< -1080..-8, resolution 1/8dB Measured RSCP of the pilot */
    PHY_INT16                           shwEcN0;             /**< -200..-8, resolution 1/8dB. Measured Ec/No of the pilot */
    PHY_INT16                           shwRlsEcIo;          /**< -200..-8, resolution 1/8dB., CSDR_1X_MEAS_VALUE_NOT_INCLUDED Total Ec/Io of the RLS the pilot belongs to. */
    PHY_UINT16                          uhwTimeStamp;        /**< 0xGGHH, where GG (0..63) is the 80ms system time and HH is the PCG number (0..63) within the 80ms frame. */
    PHY_INT16                           shwRelativeStrength; /**< -200..-8, resolution 1/8dB., CSDR_1X_MEAS_VALUE_NOT_INCLUDED. Relative strength of the pilot, 10*Log10(SumEc), see c:s0005Av6.0, 2.6.6.2.3. */
    PHY_UINT32                          uwDelaySpreadRMS;    /**< The RMS of the delay spread. Used for window placement. In 1/4 chips */
    PHY_UINT32                          uwFirstPathOffset;
    PHY_UINT32                          uwLastPathOffset;    /**< Offset to the last used path. Used for window placement. In 1/4 chips */
    PHY_UINT32                          uwNoiseEnergy;       /**< The sum energy of noise */
} CSDR_1X_PROC_MEASUREMENT_STRU;

/** ****************************************************************************
 * Name        : CSDR_1X_CELL_SEARCH_STRU
 *
 * Description : Cell Search result
 *******************************************************************************/
typedef struct
{
    PHY_UINT16                          uhwPNIndex; /**< Range: 0--511, PILOT_PN */
    PHY_UINT16                          uhwEnergy;  /**< 0..65535, correlation energy */
    PHY_UINT32                          uwPNPhase;  /**< the phase of the found path, unit: 1/4 chip */
} CSDR_1X_CELL_SEARCH_STRU;

/** ****************************************************************************
 * Name        : CSDR_1X_FREQ_RESP_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    CSDR_1X_FREQ_INFO_STRU              stFreqInfo;   /**< The measured frequency */
    PHY_INT16                           shwFreqRssi;  /**< -880..0, resolution 0.125dBm. Measured RSSI on the frequency */
    PHY_UINT16                          uhwReserved1; /**< 32 bit alignment */
} CSDR_1X_FREQ_RESP_STRU;

/** ****************************************************************************
 * Name        : CSDR_1X_MEAS_INFO_STRU
 *
 * Description : PN info
 *******************************************************************************/
typedef struct
{
    PHY_UINT16                                              uhwPNIndex;    /**< Range: 0--511, PILOT_PN */
    CSDR_1X_MEAS_FILTER_MODE_ENUM_UINT16                    enFilterMode;  /**< use filter or not. Filter used in TCH only */
    PHY_UINT32                                              uwPNPhase;     /**< Tail of the measurement window, in 1/4 chips */
    PHY_UINT32                                              uwNoiseEnergy; /**< The sum energy of noise, provided to CSDR for filtering */
} CSDR_1X_MEAS_INFO_STRU;

/** ****************************************************************************
 * Name        : CSDR_1X_CS_PN_LIST_STRU
 *
 * Description : This struct carries a list of requested cell searches to be
 * performed.
 * There is one list for both neighbour/candidate set and remaining set
 * searches.
 * Results shall be sent to CPROC every time
 * CSDR_1X_MAX_CELL_SEARCH_RESULTS_NUM cells have been searched.
 *******************************************************************************/
typedef struct
{
    PHY_UINT16                          uhwPnNum;                                   /**< Number of PN offsets to search */
    PHY_UINT16                          uhwReserved;                                /**< 32 bit alignment */
    CSDR_1X_CS_INFO_STRU                astCsInfoList[CSDR_1X_MAX_CELL_SEARCH_NUM]; /**< List of the PN offsets to search */
} CSDR_1X_CS_PN_LIST_STRU;

/** ****************************************************************************
 * Name        : CSDR_1X_MPS_RSLT_STRU
 *
 * Description : This struct carries the MPS result per antenna.
 *******************************************************************************/
typedef struct
{
    CSDR_1X_PROC_MEASUREMENT_STRU       astAntMpsRslt[CSDR_1X_MAX_ANTENNAS_NUM];
} CSDR_1X_MPS_RSLT_STRU;

/** ****************************************************************************
 * Name        : CSDR_1X_MPS_INFO_STRU
 *
 * Description : This struct carries configuration information for each pilot
 * on which to do MPS.
 * For reading F-SYNC after initial pilot search. PNOffset is set to
 * CSDR_1X_PN_INDEX_NOT_KNOWN.
 * In auwWindowPosition[ and auwMPSMeasNoiseEnergy[ position 0 is for main
 * antenna, and position 1 for the diversity antenna.
 *******************************************************************************/
typedef struct
{
    PHY_UINT16                          uhwPNIndex;                                      /**< 0..511, CSDR_1X_PN_INDEX_NOT_KNOWN. PN Offset of the pilot */
    CSDR_1X_CELL_TYPEIND_ENUM_UINT16    enCellType;
    PHY_UINT32                          auwWindowPosition[CSDR_1X_MAX_ANTENNAS_NUM];     /**< Tail of the search window to be used for main antenna. Unit: 1/4 chip. */
    PHY_UINT32                          auwMPSMeasNoiseEnergy[CSDR_1X_MAX_ANTENNAS_NUM]; /**< For MPS meas */
    CSDR_1X_BOOL_ENUM_UINT16            enPwrCombinInd;                                  /**< Does this pilot belong to the same RLS as previous pilot? PWR_COMB_IND */
    PHY_UINT16                          uhwReserved;                                     /**< 32 bit alignment */
} CSDR_1X_MPS_INFO_STRU;

/** ****************************************************************************
 * Name        : CSDR_1X_FREQ_INFO_LIST_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    PHY_UINT16                          uhwNbrOfFrequencies;                                /**< 1..CSDR_1X_MAX_FREQUENCIES_IL_LEVEL_REQ */
    PHY_UINT16                          uhwReserved;                                        /**< 32 bit alignment */
    CSDR_1X_FREQ_INFO_STRU              astFreqInfo[CSDR_1X_MAX_FREQUENCIES_IN_LEVEL_SCAN];
} CSDR_1X_FREQ_INFO_LIST_STRU;

/** ****************************************************************************
 * Name        : CSDR_1X_FREQ_RESP_LIST_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    PHY_UINT16                          uhwNbrOfFrequencies;                                /**< 0..CSDR_1X_MAX_FREQUENCIES_IN_LEVEL_REQ */
    PHY_UINT16                          uhwReserved;                                        /**< 32 bit alignment */
    CSDR_1X_FREQ_RESP_STRU              astFreqResp[CSDR_1X_MAX_FREQUENCIES_IN_LEVEL_SCAN];
} CSDR_1X_FREQ_RESP_LIST_STRU;

/** ****************************************************************************
 * Name        : CSDR_1X_MEAS_PN_LIST_STRU
 *
 * Description : PN list
 *******************************************************************************/
typedef struct
{
    PHY_UINT16                          uhwPnNum;                                      /**< Number of PN offsets in the list */
    PHY_UINT16                          uhwReserved;                                   /**< 32 bit alignment */
    CSDR_1X_MEAS_INFO_STRU              astMeasInfoList[CSDR_1X_MAX_MEAS_PN_LIST_NUM]; /**< List of the PN offsets to measure */
} CSDR_1X_MEAS_PN_LIST_STRU;

/** ****************************************************************************
 * Name        : CSDR_1X_MPS_PN_LIST_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    PHY_UINT16                          uhwPnNum;                                    /**< Number of pilot in the list */
    PHY_UINT16                          uhwReserved;                                 /**< 32 bit alignment */
    CSDR_1X_MPS_INFO_STRU               astMpsInfoList[CSDR_1X_MAX_MPS_PN_LIST_NUM];
} CSDR_1X_MPS_PN_LIST_STRU;

/*******************************************************************************
 7. OTHER declarations
*******************************************************************************/

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_CONTINUE_REQ_STRU
 *
 * Description : This signal is sent from CPROC to CSDR to request CSDR to
 * continue MPS.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    PHY_UINT16                          uhwActionTime; /**< In PCG or CSDR_1X_ACTIVATE_AT_ONCE */
    PHY_UINT16                          uhwReserved1;  /**< 32 bit alignment */
} CPROC_CSDR_1X_CONTINUE_REQ_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_START_MEAS_REQ_STRU
 *
 * Description : This signal requests measurements and cell/pilot search.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16                           enMsgId;
    PHY_UINT16                                              uhwOpId;
    CSDR_1X_MEAS_MODE_ENUM_UINT16                           enOffline;      /**< 0:Online, measure online,  1:Offline, use buffered data for measurements */
    PHY_UINT16                                              uhwUnitNum;
    PHY_UINT16                                              uhwActionTime;  /**< In PCG, CSDR_1X_ACTIVATE_AT_ONCE or CSDR_1X_START_AFTER_ONGOING */
    CSDR_1X_BUFFER_USE_ENUM_UINT16                          enBufferUse;    /**< Use existing buffer, or fill before measurement. */
    PHY_UINT16                                              uhwReserved1;   /**< 32 bit alignment */
    CSDR_1X_MEAS_FREQUENCY_MODE_ENUM_UINT16                 enSF;
    CSDR_1X_MEAS_PN_LIST_STRU                               stMeasPNList;   /**< PN List for measurements */
    CSDR_1X_CS_PN_LIST_STRU                                 stCSList;       /**< PN List for cell search */
                                                                            /**< These parameters are not valid when enSFFlag=1 */
    CSDR_1X_FREQ_INFO_STRU                                  stFreqInfo;
    PHY_UINT16                                              uhwCFGapLength; /**< In PCG, i.e. 1.25ms increments */
    PHY_UINT16                                              uhwCfTAdd;      /**< 0..63, threshold for including pilots in the calculation of shwCfTotalEcIo CF_T_ADD */
} CPROC_CSDR_1X_START_MEAS_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_MEAS_IND_STRU
 *
 * Description : This signal is sent from CSDR to CPROC
 * - For measurements when All measurements requested in a
 * CPROC_CSDR_1X_MEAS_START_REQ have been finished
 * - When measurements have been stopped by a CPROC_CSDR_1X_MEAS_STOP_REQ. The
 * signal then contains the results of measurements that were finished before
 * the stop.
 * The OpID shall be set to the OpID received in the corresponding
 * CPROC_CSDR_1X_MEAS_START_REQ.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    PHY_INT16                           shwFreqRssi;                                  /**< -880..0, resolution 0.125dBm. Measured RSSI on the frequency */
    PHY_INT16                           shwCfTotalEcIo;                               /**< -200..0, resolution 0.125dB Total EcIo of all cells on the candidate frequency above CF_T_ADD. Valid only for CF meas reports. */
    PHY_UINT16                          uhwPNNum;                                     /**< 0..CSDR_1X_MAX_MEAS_PN_LIST_NUM, number of Pilots in the list */
    PHY_UINT16                          uhwReserved;                                  /**< 32 bit alignment */
    CSDR_1X_PROC_MEASUREMENT_STRU       astMeasurement[CSDR_1X_MAX_MEAS_PN_LIST_NUM];
} CSDR_CPROC_1X_MEAS_IND_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_STOP_MEAS_REQ_STRU
 *
 * Description : This signal is sent from CPROC to CSDR to request CSDR to stop
 * any ongoing measurements or searches.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    PHY_UINT16                          uhwActionTime; /**< In PCG or CSDR_1X_ACTIVATE_AT_ONCE */
    PHY_UINT16                          uhwReserved1;  /**< 32 bit alignment */
} CPROC_CSDR_1X_STOP_MEAS_REQ_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_START_MPS_REQ_STRU
 *
 * Description : This signal requests CSDR to perform MPS. The signal always
 * carries the complete list of MPS to perform.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    PHY_UINT16                          uhwActionTime; /**< In PCG or CSDR_1X_ACTIVATE_AT_ONCE */
    PHY_UINT16                          uhwUnitNum;    /**< 1 or 2 */
    PHY_UINT16                          uhwWindowSize; /**< 96: after sleep. 48: otherwise */
    CSDR_1X_MPS_TYPE_ENUM_UINT16        enMPSType;     /**< one shot or continuous */
    CSDR_1X_ANTENNA_IND_ENUM_UINT16     enUseAntenna;
    PHY_UINT16                          uhwReserved;   /**< 32 bit alignment */
    CSDR_1X_MPS_PN_LIST_STRU            stMpsPNList;
} CPROC_CSDR_1X_START_MPS_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_MPS_IND_STRU
 *
 * Description : This signal is sent from CSDR to CPROC
 * 1) When one shot MPS have been finished
 * 2) When MPS is performed continuously, every 30ms, containing the measured
 * results for the MPS cells.
 * 3) When MPS has been requested to stop, the signal shall contain any
 * finished, not yet reported results.
 * The OpID shall be set to the OpID received in the
 * CPROC_CSDR_1X_MPS_START_REQ, CPROC_CSDR_1X_UPDATE_MPS_REQ or
 * CPROC_CSDR_1X_CONTINUE_REQ that started/restarted the MPS.
 * shwAsTotalEcIo and shwAsTotalEc are set to CSDR_1X_MEAS_VALUE_NOT_INCLUDED
 * in when not all pilots in the active set have results (e.g. in the first
 * report after an MPS_START).
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    PHY_INT16                           shwFreqRssi;                                 /**< -880..0, resolution 0.125dBm. Measured RSSI on the frequency */
    PHY_INT16                           shwAsTotalEcIo;                              /**< -200..0, CSDR_1X_MEAS_VALUE_NOT_INCLUDED resolution 0.125dB. Total EcIo of the Active set, from main antenna */
    PHY_INT16                           shwAsTotalEc;                                /**< -1080..-8, resolution 1/8dB, CSDR_1X_MEAS_VALUE_NOT_INCLUDED. Total Ec of the Active set */
    PHY_UINT16                          uhwPNNum;                                    /**< 0..CSDR_1X_MAX_MPS_PN_LIST_NUM, number of Pilots in the list */
    CSDR_1X_MPS_RSLT_STRU               astCellMpsRslt[CSDR_1X_MAX_MPS_PN_LIST_NUM];
    PHY_UINT32                          uwFramePos;                                  /**< the base cnt of Frame head  0..512*64*16-1 resolution 1/16chip */
    PHY_INT16                           shwAverageRscpT1;                            /**< -1080..-8, resolution 1/8dB Average RSCP for TAS, filtered over T1 */
    PHY_INT16                           shwAverageRscpT2;                            /**< -1080..-8, resolution 1/8dB Average RSCP for TAS, filtered over T2 */
} CSDR_CPROC_1X_MPS_IND_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_BUFFER_REQ_STRU
 *
 * Description : This signal is sent from CPROC to CSDR to request CSDR to fill
 * the correlator buffer. The signal is used for buffering for serving
 * frequency after wakeup in slotted mode only.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    PHY_UINT16                          uhwActionTime; /**< 0..63 Start time of recording, in PCG. Does not use CSDR_1X_ACTIVATE_AT_ONCE */
    PHY_UINT16                          uhwReserved;   /**< 32 bit alignment */
} CPROC_CSDR_1X_BUFFER_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_BUFFER_IND_STRU
 *
 * Description : This signal is sent from CSDR when the buffer has been filled
 * as per the request from CPROC. The OpID shall be the OpID received in the
 * request.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    PHY_UINT16                          uhwEndPCG;    /**< The PCG in which buffering ended, for debug purposes */
    PHY_UINT16                          uhwReserved1; /**< 32 bit alignment */
} CSDR_CPROC_1X_BUFFER_IND_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_STOP_MPS_REQ_STRU
 *
 * Description : This signal is sent from PROC when MPS shall be stopped. The
 * stop shall be performed at the activation time, and any finished results
 * shall be sent to PROC.
 * The request shall be sent >5ms in advance.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    PHY_UINT16                          uhwActionTime; /**< In PCG or CSDR_1X_ACTIVATE_AT_ONCE */
    CSDR_1X_STOP_ACTION_ENUM_UINT16     enStopAction;  /**< Halt or stop/release */
} CPROC_CSDR_1X_STOP_MPS_REQ_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_UPDATE_MPS_REQ_STRU
 *
 * Description : This signal carries the complete new list of cells on which to
 * do MPS. No action time is given, since the request always shall be performed
 * immediately.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    CSDR_1X_MPS_PN_LIST_STRU            stMpsPNList;
} CPROC_CSDR_1X_UPDATE_MPS_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_CELL_SEARCH_IND_STRU
 *
 * Description : This signal is sent from CSDR to CPROC
 * 1) Every time CSDR_1X_MAX_CELL_SEARCH_RESULTS_NUM cells have been searched.
 * The OpID shall be set to the OpID received in the corresponding
 * CPROC_CSDR_1X_MEAS_START_REQ.
 * 2) When measurements have been stopped by a CPROC_CSDR_1X_MEAS_STOP_REQ. The
 * signal then contains the results of cell searches that were finished before
 * the stop. The OpID shall be set to the OpID received in the
 * CPROC_CSDR_1X_MEAS_STOP_REQ.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    PHY_INT16                           shwFreqRssi;                                        /**< -880..0, resolution 0.125dBm. Measured RSSI on the frequency */
    PHY_UINT16                          uhwCellNum;                                         /**< 0..CSDR_1X_MAX_CELL_SEARCH_RESULTS_NUM. nbr of pilots in the list. */
    CSDR_1X_CELL_SEARCH_STRU            astCellSearch[CSDR_1X_MAX_CELL_SEARCH_RESULTS_NUM]; /**< the result of CS */
} CSDR_CPROC_1X_CELL_SEARCH_IND_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_SM_SET_WORK_MODE_REQ_STRU
 *
 * Description : This signal is sent from CPROC SearchMeasurer to CSDR
 * SearchMeasurer to prepare for a either Master or Slave Mode.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    CSDR_1X_WORK_MODE_ENUM_UINT16       enWorkMode;
    PHY_UINT16                          uhwReserved1; /**< 32 bit alignment */
} CPROC_CSDR_1X_SM_SET_WORK_MODE_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_SM_SET_WORK_MODE_CNF_STRU
 *
 * Description : This signal is sent from CSDR to CPROC to confirm that the
 * requested mode setting has been performed. The OpID shall be set to the OpID
 * received in the corresponding CPROC_CSDR_1X_SET_WORK_MODE_REQ.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
} CSDR_CPROC_1X_SM_SET_WORK_MODE_CNF_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_SIGNAL_LEVEL_REQ_STRU
 *
 * Description : CPROC_CSDR_1X_SIGNAL_LEVEL_REQ is sent to CSDR to request the
 * RSSI of the current frequency. It is the responisbility of CPROC to send the
 * signal when the RF is stable. The signal carries no parameters.
 * The result is returned by CSDR_CPROC_1X_SIGNAL_LEVEL_IND.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
} CPROC_CSDR_1X_SIGNAL_LEVEL_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_SIGNAL_LEVEL_IND_STRU
 *
 * Description : CSDR_CPROC_1X_SIGNAL_LEVEL_IND returns the RSSI of the current
 * frequncy on request by a CPROC_CSDR_1X_SIGNAL_LEVEL_REQ.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    PHY_INT16                           shwFreqRssi;  /**< -880..0, resolution 0.125dBm. Measured RSSI on the frequency */
    PHY_UINT16                          uhwReserved1; /**< 32 bit alignment */
} CSDR_CPROC_1X_SIGNAL_LEVEL_IND_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_PILOT_SEARCH_REQ_STRU
 *
 * Description : If uhwSearchAction == START_SEARCH: Request to search for new
 * pilots. The result is returned by CSDR_CPROC_1X_PILOT_SEARCH_IND.
 * If uhwSearchAction == STOP_SEARCH: Stop ongoing search.
 * CSDR_CPROC_1X_PILOT_SEARCH_IND is returned when the search is stopped. If no
 * search is ongoing CSDR_CPROC_1X_PILOT_SEARCH_CNF is returned immediately.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    CSDR_1X_SEARCH_ACTION_ENUM_UINT16   enSearchAction;
    PHY_UINT16                          uhwReserved1;   /**< 32 bit alignment */
} CPROC_CSDR_1X_PILOT_SEARCH_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_PILOT_SEARCH_IND_STRU
 *
 * Description : Returns the result of a pilot search started by
 * CPROC_CSDR_1X_PILOT_SEARCH_REQ.
 * uhwSearchAction == START_SEARCH indicates that the search finished, and the
 * result fields are valid.
 * uhwSearchAction == STOP_SEARCH indicates that pilot search has been stopped,
 * and the result fields are not valid.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    CSDR_1X_SEARCH_ACTION_ENUM_UINT16   enSearchAction;
    PHY_UINT16                          uhwNumResults;                           /**< 0..32, Number of valid results in the stResult */
    CSDR_1X_CELL_SEARCH_STRU            stResult[CSDR_MAX_PILOT_SEARCH_RESULTS]; /**< In strength order, strongest in pos 0 */
} CSDR_CPROC_1X_PILOT_SEARCH_IND_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_SM_RELEASE_ALL_REQ_STRU
 *
 * Description : CPROC_CSDR_1X_SM_RELEASE_ALL_REQ is used to trigger a soft
 * reset. It contains no parameters.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
} CPROC_CSDR_1X_SM_RELEASE_ALL_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_SM_RELEASE_ALL_CNF_STRU
 *
 * Description : CSDR_CPROC_1X_SM_RELEASE_ALL_CNF is sent when a soft reset has
 * been performed as requested by a CPROC_CSDR_1X_SM_RELEASE_ALL_REQ. It
 * contains no parameters.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
} CSDR_CPROC_1X_SM_RELEASE_ALL_CNF_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_MEAS_CAPABILITY_IND_STRU
 *
 * Description : CSDR_CPROC_1X_MEAS_CAPABILITY_IND is sent from CSDR to CPROC
 * as a response to a CPROC_CSDR_1X_SM_SET_WORK_MODE_REQ and on change of the
 * measurement capability.
 * It carries parameters describing the time it takes for CSDR to perform
 * buffering, measurements and cell search.
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    PHY_UINT16                          uhwBufferTimeSlotted;         /**< 0..65535, in chips, time CSDR needs to buffer samples for offline measurements in slotted */
    PHY_UINT16                          uhwMeasTimeSlottedOffline;    /**< 0..65535, in chips, time CSDR needs to perform offline measurement for one pilot and one unit in slotted */
    PHY_UINT16                          uhwMeasTimeSlottedOnline;     /**< 0..65535, in chips, time CSDR needs to perform online measurement for one pilot and one unit in slotted */
    PHY_UINT16                          uhwCsTimeSlottedOffline;      /**< 0..65535, in chips, time CSDR needs to perform offline cell search for one pilot and one unit in slotted */
    PHY_UINT16                          uhwBufferTimeContinuous;      /**< 0..65535, in chips, time CSDR needs to buffer samples for offline measurements in Continuous modes */
    PHY_UINT16                          uhwMeasTimeContinuousOffline; /**< 0..65535, in chips, time CSDR needs to perform offline measurement for one pilot and one unit in Continuous modes */
    PHY_UINT16                          uhwMeasTimeContinuousOnline;  /**< 0..65535, in chips, time CSDR needs to perform online measurement for one pilot and one unit in Continuous modes */
    PHY_UINT16                          uhwCsTimeContinuousOffline;   /**< 0..65535, in chips, time CSDR needs to perform offline cell search for one pilot and one unit in Continuous modes */
} CSDR_CPROC_1X_MEAS_CAPABILITY_IND_STRU;

/** ****************************************************************************
 * Name        : CPROC_CSDR_1X_TIME_SYNC_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
} CPROC_CSDR_1X_TIME_SYNC_REQ_STRU;

/** ****************************************************************************
 * Name        : CSDR_CPROC_1X_TIME_SYNC_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSDR1XSM_MSG_TYPE_ENUM_UINT16       enMsgId;
    PHY_UINT16                          uhwOpId;
    CSDR_1X_SUCCESS_ENUM_UINT16         enTimeResult;    /**< the time get success or fail */
    PHY_UINT16                          uhwReserved;     /**< 32-bit alignment */
    PHY_UINT32                          auwPulseTime[2]; /**< System time in 1/16chip */
} CSDR_CPROC_1X_TIME_SYNC_IND_STRU;

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
