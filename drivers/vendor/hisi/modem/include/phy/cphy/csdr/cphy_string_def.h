#ifndef cphy_string_def_h
#define cphy_string_def_h

/*****************************************************************************
  每个文件单独划分，格式:
  #define STRING_源文件名_自定义_ERROR "源文件名 error: 自定义字符串"
  #define STRING_源文件名_自定义_WARING "源文件名 waring: 自定义字符串"
  #define STRING_源文件名_自定义_INFO "源文件名 info: 自定义字符串"

 2015-5-19:
 根据最新版本，打印信息约束为:"模块名(6字节左对齐)|E/W/I/D|字符串信息，总长度小于1024字节"

我们约定如下规则：

1）  第一个字母，代表各模：
    G： G模。多卡时，由G模相关人确认；
    W： W模；
    L： LTE模；
    T： TD模；

    X：1X模；
    H：HRPD；
    C：CDMA，包含1X和HRPD公共的内容。如：csdr_edma, csdr_feitf；
2） 第2~6个字母，代码各模对应的模块，长度不足的用空格替换；
3） 第7~9个字母：
     |E|:  代表error信息；
     |W|:  代表warning信息；
     |I|:  代表inform信息，如流程；
     |D|:  代表debug信息；
4） 第10~1024byte：相应的打印内容。
上述总长度小于1024byte。

例如： GMEAS |W|Lost network for 10 minutes.
*****************************************************************************/

/*****************************************************************************
  csdr_memory.c
*****************************************************************************/
#define STRING_CSDR_MEMORY_REGISTER_MOD_ERROR   "CMEMRY|E| RegisterModMem uhwModMemId = %d, uhwType= %d, uwBlkNum = %d"
#define STRING_CSDR_MEMORY_REGISTER_INC_ERROR   "CMEMRY|E| RegisterIncMem uhwModMemId = %d, uwBlkNum = %d"
#define STRING_CSDR_MEMORY_REGISTER_TASK_ERROR  "CMEMRY|E| RegisterManageTask uhwModMemId = %d, uhwMaxModIdNum = %d"

#define STRING_CSDR_MEMORY_INC_MEM_ERROR        "CMEMRY|E| GetIncMemInfo uhwModMemId = %d, pstMemInfo = 0x%x"
#define STRING_CSDR_MEMORY_MOD_MEM_ERROR        "CMEMRY|E| GetModMemInfo uhwModMemId = %d, pstMemInfo = 0x%x"

#define STRING_CSDR_MEMORY_ASSIGN_FIX_ERROR     "CMEMRY|E| AssignFixMem uhwModMemId = %d, uwRegisterBlkNum = %d, uhwFixBlkNum = %d"
#define STRING_CSDR_MEMORY_ASSIGN_INC_ERROR     "CMEMRY|E| AssignIncMem uhwModMemId = %d, uwRegisterBlkNum = %d, uhwFixBlkNum = %d"


/*****************************************************************************
  csdr_hrpd_timing.c
*****************************************************************************/
#define STRING_CSDR_HRPD_TIMING_TIME_MODULE_STATE_IN_SLOW_INFO          "HTIMNG|I| CSDR_HRPD_TIMING_BeginTracingQuick  when in quick change,state in slow"
#define STRING_CSDR_HRPD_TIMING_CHANGE_CHIP_IN_1_4_CHIP_INFO            "HTIMNG|I| CSDR_HRPD_TIMING_BeginTracingSlow change chip in 1/4 in slow change state"
#define STRING_CSDR_HRPD_TIMING_SLOW_STATE_IN_SET_TIME_INFO             "HTIMNG|I| CSDR_HRPD_TIMING_ProcSetTimingReq state is slow in set time pstTimingCtx->enTimingStatus = %d"
#define STRING_CSDR_HRPD_TIMING_QUICK_PROCESS_TIME_NO_ARRIVE_INFO       "HTIMNG|I| CSDR_HRPD_TIMING_TracingQuickProcess quick process time is no arrive"
#define STRING_CSDR_HRPD_TIMING_SET_TIME_PROCESS_TIME_NO_ARRIVE_INFO    "HTIMNG|I| CSDR_HRPD_TIMING_SetTimingProcess set time process time is no arrive pstSwitchInfo->uhwCntQtrSlot = %d"
#define STRING_CSDR_HRPD_TIMING_TRACEING_SLOW_PROCESS_INFO              "HTIMNG|I| CSDR_HRPD_TIMING_TracingSlowProcess QtrSlotN is %d Direction is %d Adjust Cnt is %d"

#define STRING_CSDR_HRPD_TIMING_REFERENCE_CHANGE_TYPE_INFO              "HTIMNG|I| CSDR_HRPD_TIMING_ProcReferenceTimingReq reference msg change type info pstTimingCtx->stReferenceTiming.enUpdateSpeed = %d"
#define STRING_CSDR_HRPD_TIMING_TIME_STATE_IN_REFERENCE_TIME_INFO       "HTIMNG|I| CSDR_HRPD_TIMING_ProcReferenceTimingReq state in set time pstTimingCtx->enTimingStatus = %d"
#define STRING_CSDR_HRPD_TIMING_TIME_QUICK_SET_STATE_IN_SET_TIME_INFO   "HTIMNG|I| CSDR_HRPD_TIMING_ProcSetTimingReq quick and set state in set time pstTimingCtx->enTimingStatus = %d"

#define STRING_CSDR_HRPD_TIMING_ADJUST_TIMING_LTE_INFO1                 "HTIMNG|I| CSDR_HRPD_TIMING_AdjustTimingFromLteInfo uhwNumOfChip is %d, uhwNumOf26p67ms is %d, uhwNumOf80ms is %d, uwStoreCtuTiming is %d, uwStore32kTiming is %d"
#define STRING_CSDR_HRPD_TIMING_ADJUST_TIMING_LTE_INFO2                 "HTIMNG|I| CSDR_HRPD_TIMING_AdjustTimingFromLteInfo uwChip is %d, uwSlot is %d, uwSfn is %d, uwKValue is %d"
#define STRING_CSDR_HRPD_TIMING_ADJUST_TIMING_LTE_INFO3                 "HTIMNG|I| CSDR_HRPD_TIMING_AdjustTimingFromLteInfo ullHrpdChipNum high32 is %x, ullHrpdChipNum low32 is %x, uwDiffHrpdChip is %d, uwDiff32k is %d, uwNumOf10p24s is %d"
#define STRING_CSDR_HRPD_TIMING_ADJUST_TIMING_LTE_INFO4                 "HTIMNG|I| CSDR_HRPD_TIMING_AdjustTimingFromLteInfo uwSlaveBasecntDiff is %d, uwDiffHrpdChip is %d, uw32kTiming is %d "

#define STRING_CSDR_HRPD_TIMING_SAVE_LTE_SI8_TIMING_INFO                "HTIMNG|I| CSDR_HRPD_TIMING_SaveLteSi8Timing ullHrpdChipNum high32 is %x, ullHrpdChipNum low32 is %x, uwLteSi832kTiming is %d"

#define STRING_CSDR_HRPD_TIMING_STORE_TIMING_WAR                        "HTIMNG|W| CSDR_HRPD_TIMING_SlaveStoreTiming basecntstate is not valid, basecntstate is %d, basecntdiff is %d"
#define STRING_CSDR_HRPD_TIMING_STORE_TIMING_INFO1                      "HTIMNG|I| CSDR_HRPD_TIMING_SlaveStoreTiming uhwNumOfChip is %d, uhwNumOf26p67ms is %d, uhwNumOf80ms is %d, uwStoreCtuTiming is %d, uwStore32kTiming is %d"
#define STRING_CSDR_HRPD_TIMING_STORE_TIMING_INFO2                      "HTIMNG|I| CSDR_HRPD_TIMING_SlaveStoreTiming uwChip is %d, uwSlot is %d, uwSfn is %d, uwKValue is %d"

#define STRING_CSDR_HRPD_TIMING_RESUME_TIMING_WAR                       "HTIMNG|W| CSDR_HRPD_TIMING_SlaveResumeTiming basecntstate is not valid, basecntstate is %d, basecntdiff is %d"
#define STRING_CSDR_HRPD_TIMING_RESUME_TIMING_INFO1                     "HTIMNG|I| CSDR_HRPD_TIMING_SlaveResumeTiming uhwNumOfChip is %d, uhwNumOf26p67ms is %d, uhwNumOf80ms is %d, uwStoreCtuTiming is %d, uwStore32kTiming is %d"
#define STRING_CSDR_HRPD_TIMING_RESUME_TIMING_INFO2                     "HTIMNG|I| CSDR_HRPD_TIMING_SlaveResumeTiming uwChip is %d, uwSlot is %d, uwSfn is %d, uwKValue is %d"
#define STRING_CSDR_HRPD_TIMING_RESUME_TIMING_INFO3                     "HTIMNG|I| CSDR_HRPD_TIMING_SlaveResumeTiming uwDiff32k is %d, uwNumOf10p24s is %d, uwBasecntDiff is %d"

#define STRING_CSDR_HRPD_TIMING_ADJUST_TIME_QUICK_WRN                   "HTIMNG|W| CSDR_HRPD_TIMING_AdjustTimingQuick state is not invalid. State is:%d"

#define STRING_CSDR_HRPD_TIMING_MSG_NUM_ERROR                           "HTIMNG|E| CSDR_HRPD_TIMING_ReadAllTimeInfo SysCntRptInt1 is error, the SysCntRptInt1 is %d"
#define STRING_CSDR_HRPD_TIMING_INTSYSCNT_ERROR                         "HTIMNG|E| CSDR_HRPD_TIMING_CalcIntSysCnt IntSysCnt is error, the NumOfChip is %d the NumOf26p67ms is %d"
#define STRING_CSDR_HRPD_TIMING_READSYSCNT_ERROR                        "HTIMNG|E| CSDR_HRPD_TIMING_CalcIntSysCnt ReadSysCnt is error, the NumOf5p12sOr2s is %d the NumOf80ms is %d the NumOf26p67ms %d the NumOfChip is %d"
#define STRING_CSDR_HRPD_TIMING_STOP_GPS_SYNC_COUNT_INFO                "HTIMNG|I| When Gps Sync Signal is stopped, the count of qtr slot is %d"

/*****************************************************************************
  csdr_hrpd_eq.c
*****************************************************************************/
#define STRING_CSDR_HRPD_EQ_EQUALIER_ERROR              "HEQ   |E| CSDR_HRPD_EQ_EqualizerProcess AGC data error "

/*****************************************************************************
  csdr_hrpd_eq_memory.c
*****************************************************************************/
#define STRING_CSDR_HRPD_EQ_HALFSLOT_MEM_ERROR          "HEQ   |E|  CSDR_HRPD_EQ_MemManagement half slot memory error "
#define STRING_CSDR_HRPD_EQ_MOD_MEM_ERROR               "HEQ   |E|  CSDR_HRPD_EQ_MemManagement module memory error "
#define STRING_CSDR_HRPD_EQ_INC_MEM_ERROR               "HEQ   |E|  CSDR_HRPD_EQ_MemManagement inc memory error "
#define STRING_CSDR_HRPD_EQ_HALFSLOT_MEM_OVERFLOW_ERROR "HEQ   |E|  CSDR_HRPD_EQ_MemManagement half slot memory Overflow, uwMaxUsedBlkSize = %d, uwBlkNum = %d "
#define STRING_CSDR_HRPD_EQ_MOD_MEM_OVERFLOW_ERROR      "HEQ   |E|  CSDR_HRPD_EQ_MemManagement module memory Overflow, uwMaxUsedBlkSize = %d, uwBlkNum = %d "
#define STRING_CSDR_HRPD_EQ_INC_MEM_OVERFLOW_ERROR      "HEQ   |E|  CSDR_HRPD_EQ_MemManagement inc memory Overflow, uwMaxUsedBlkSize = %d, uwBlkNum = %d "

/*****************************************************************************
  csdr_hrpd_dec_layer_a_int.c
*****************************************************************************/

/*****************************************************************************
  csdr_hrpd_dec_memory.c
*****************************************************************************/
#define STRING_CSDR_HRPD_DEC_MEM_ALLOC_ERROR            "HDEC  |E| not enough memory for Fix memory allocation"
#define STRING_CSDR_HRPD_DEC_MEM_OVERFLOW_ERROR         "HDEC  |E| memory overflow,required memory %d is larger than avaiable memory %d"

/*****************************************************************************
  csdr_hrpd_dec_layer_a.c
*****************************************************************************/
#define STRING_CSDR_HRPD_DEC_DEINTERL_DEREPEAT_INFO     "HDEC  |I|  deinterleave-derepeat, w is 6144 !"
#define STRING_CSDR_HRPD_DEC_DMA_CFG_ERROR              "HDEC  |E| BbpDma Channel ID is invalid!"
#define STRING_CSDR_HRPD_DEC_BBPDECCFG_INPUTVAL_ERROR   "HDEC  |E| BbpDecCfgInputVal Error!"
/*****************************************************************************
  csdr_hrpd_dec_layer_b.c
*****************************************************************************/
#define STRING_CSDR_HRPD_DEC_FSM_TRANSITION_INFO        "HDEC  |I| enDecState %d, enDecEvent %d"
#define STRING_CSDR_HRPD_DEC_START_DECODING_ERROR       "HDEC  |E| DecFsmState %d is not null when start decoding,SDRState %d, , DecoderMode %d"
#define STRING_CSDR_HRPD_DEC_OVERTIME_ERROR             "HDEC  |E| overtime flag is set! harq id %d, tried times %d, TFIValue %d"
#define STRING_CSDR_HRPD_DEC_CRC_RESULT_INFO            "HDEC  |I| crc %d! harq id %d, tried times %d, TFIValue %d"
#define STRING_CSDR_HRPD_DEC_CHANNEL_TYPE_ERROR         "HDEC  |E| channel type %d"
#define STRING_CSDR_HRPD_DEC_ERROR_HANDLING_ERROR       "HDEC  |E| fsm error handling, FsmState %d, Event %d, TrafficType %d "
#define STRING_CSDR_HRPD_DEC_TF_ERROR                   "HDEC  |E| get TF error"
#define STRING_CSDR_HRPD_DEC_GET_NEXT_FORMAT_WAR        "HDEC  |W|CSDR_HRPD_DEC_GetNextDecFormat war, dec ctx packetsize is %d, tf num is %d"
#define STRING_CSDR_HRPD_DEC_DMA_ALLOC_ERROR            "HDEC  |E| Allocation for DMA (decoding) error!"

/*****************************************************************************
  csdr_hrpd_dec_process_cc_result.c
*****************************************************************************/
#define STRING_CSDR_HRPD_DEC_CC_BUFF_FULL_ERROR         "HDEC  |E| ulHeadIndex %d, ulTailIndex %d"
#define STRING_CSDR_HRPD_DEC_CC_HEADER_INFO_BYTE        "HDEC  |I| cc header bytes %d"
#define STRING_CSDR_HRPD_DEC_CC_HEADER_INFO             "HDEC  |I| cc header, enSynchronousCapsule %d, enFirstPacket %d, enLastPacket %d, uhwOffset %d, enSleepStateCapsuleDone %d "

/*****************************************************************************
  csdr_hrpd_dec_process_ftc_result.c
*****************************************************************************/
#define STRING_CSDR_HRPD_DEC_SDRAM_BUF_OVERFLOW_ERROR   "HDEC  |E| sdram buffer overflow"
#define STRING_CSDR_HRPD_DEC_MAC_INDEX_INFO             "HDEC  |I| mac index = %d"
#define STRING_CSDR_HRPD_DEC_MU_MAC_PACKET_LEN_ERROR    "HDEC  |E| MU mac layer packet len error"
/*****************************************************************************
  csdr_hrpd_cm.c
*****************************************************************************/
#define STRING_CSDR_HRPD_CM_ACCESS_RX_SETUP_INFO            "HCM   |I| CSDR_HRPD_CM_SetupServ, access to rx setup, ActiveTime: 0x%x, BandClass: %d, Freq: %d"
#define STRING_CSDR_HRPD_CM_QTR_ENTRY_INFO                  "HCM   |I| CSDR_HRPD_CM_QtrSlotEntry, uwNumOfQtrChip: %d, uwNumOf26p67ms: %d"
#define STRING_CSDR_HRPD_CM_ACCESS_RX_RELASE_INFO           "HCM   |I| CSDR_HRPD_CM_RelaseServ, access to rx off, ActiveTime: 0x%x"
#define STRING_CSDR_HRPD_CM_CC_START_PARA_WRN               "HCM   |W| CSDR_HRPD_CM_StartCtrlChannel, cc start status err, State: %d"
#define STRING_CSDR_HRPD_CM_FWD_STATUS_ERR                  "HCM   |E| CSDR_HRPD_CM_ForwardChannelCtrl, cm status err, State: %d"
#define STRING_CSDR_HRPD_CM_CC_START_RCV_INFO               "HCM   |I| CSDR_HRPD_CM_CCStartReqHandle, rcv cc start req"
#define STRING_CSDR_HRPD_CM_CC_STOP_RCV_INFO                "HCM   |I| CSDR_HRPD_CM_CCStopReqHandle, rcv cc stop req"
#define STRING_CSDR_HRPD_CM_ACCESS_SETMODE_INFO             "HCM   |I| CSDR_HRPD_CM_SetModeCtrl, cm setmode, mode: %d"
#define STRING_CSDR_HRPD_CM_ACCESS_RELALL_INFO              "HCM   |I| CSDR_HRPD_CM_RelAllCtrl, cm soft reset"
#define STRING_CSDR_HRPD_CM_ACCESS_RX_ON_INFO               "HCM   |I| CSDR_HRPD_CM_RxOnConfig, rx on process, ActiveTime: 0x%x"
#define STRING_CSDR_HRPD_CM_ACCESS_RX_OFF_INFO              "HCM   |I| CSDR_HRPD_CM_RxOffConfig, rx off process, ActiveTime: 0x%x"
#define STRING_CSDR_HRPD_CM_ACCESS_CTRL_WRN                 "HCM   |W| CSDR_HRPD_CM_DummyHandle, call dummy func"
#define STRING_CSDR_HRPD_CM_REVESE_AC_CTRL_WRN              "HCM   |W| CSDR_HRPD_CM_ReverseChannelCtrl, cm state can't operate ac channel, state: %d"
#define STRING_CSDR_HRPD_CM_TCH_CHANNEL_TYPE_ERR            "HCM   |E| CSDR_HRPD_CM_TchStartReqHandle, tch channel type error, type: %d"
#define STRING_CSDR_HRPD_CM_TCH_RCV_START_INFO              "HCM   |I| CSDR_HRPD_CM_TchStartReqHandle, rcv tch start msg, subtype: %d"
#define STRING_CSDR_HRPD_CM_TCH_RCV_RECONFIG_INFO           "HCM   |I| CSDR_HRPD_CM_TchReconfigReqHandle, rcv tch reconfig msg, purpose: %d"
#define STRING_CSDR_HRPD_CM_TCH_RCV_STOP_INFO               "HCM   |I| CSDR_HRPD_CM_TchStopReqHandle, rcv tch stop msg"
#define STRING_CSDR_HRPD_CM_SET_FORWARD_IND_INFO            "HCM   |I| CSDR_HRPD_CM_DistinguishForwardMsg, cc_start: %d, cc_stop: %d, tch_start: %d, tch_reconfig: %d, tch_stop: %d"
#define STRING_CSDR_HRPD_CM_DELTABASECNT_INVALID_INFO       "HCM   [I] CSDR_HRPD_CM_Int0Proc uwDeltaBaseCnt invalid"
#define STRING_CSDR_HRPD_CM_SLAVE_CONFIG_FE_INFO            "HCM   [I] CSDR_HRPD_CM_ConfigFeForSlave enLteOverCMode: %d, uhwBandClass: %d, uhwFreq: %d, swSlaveAfcPpm: %d"

#define STRING_CSDR_HRPD_CM_RXON_REQ_HANDLE_WRN0            "HCM   [W] CSDR_HRPD_CM_RxOnReqHandle master mode rxon time is int1, mode: %d"
#define STRING_CSDR_HRPD_CM_RXON_REQ_HANDLE_WRN1            "HCM   [W] CSDR_HRPD_CM_RxOnReqHandle slave mode rxon time is not int1, mode: %d"
#define STRING_CSDR_HRPD_CM_TCH_START_ERROR                 "HCM   |E| CSDR_HRPD_CM_TchStartReqHandle, DRCLockLength error, DRCLockLength: %d"
#define STRING_CSDR_HRPD_CM_RXON_CONFLICT_ERR               "HCM   |E| CSDR_HRPD_CM_RxOnConfig, current RF belong to 1X, currentTime: %d, activeTime: %d"
#define STRING_CSDR_HRPD_CM_FWD_HARQ_FINISH_IN_SUSPEND      "HCM   |I| Downlink Harq finished during suspend, CurHalfSlot:%d PreambleStartHalfSlot:%d MacIndex is:%d ProcessHarqNum:%d uhwMaxSlotNum:%d"
#define STRING_CSDR_HRPD_CM_SUSPEND_REQ_IN_IDLE_ERROR       "HCM   |E| cproc cannot send suspend_req in idle if not with tch_start_req"

#define STRING_CSDR_HRPD_SYS_LoadDynamicCodeType            "HSYS  |I| CSDR_COMM_DynLoad_MsgProc, load code type: %d"
#define STRING_CSDR_HRPD_CM_GPS_SYNC_REQ_HANDLE_ERROR       "HCM   |E| CSDR_HRPD_CM_GpsSyncReqHandle, the value of CBBP gps_sync_1x_evdo is %d"


/*****************************************************************************
  csdr_hrpd_ftc.c
*****************************************************************************/
#define STRING_CSDR_HRPD_FTC_ACTIVE_CCH_INFO            "HFTC  |I|  CSDR_HRPD_FTC_ActiveCCh Qtrslot:%d"
#define STRING_CSDR_HRPD_FTC_ACTIVE_FEITF_INFO          "HFTC  |I|  CSDR_HRPD_FTC_ActiveFeItf ant:%d already active "
#define STRING_CSDR_HRPD_FTC_DEACTIVE_FEITF_INFO        "HFTC  |I|  CSDR_HRPD_FTC_DeactiveFeItf ant:%d already deactive "
#define STRING_CSDR_HRPD_FTC_JUDGE_CE_START_INFO        "HFTC  |I|  CSDR_HRPD_FTC_JudgeCeStart Qtrslot:%d "
#define STRING_CSDR_HRPD_FTC_JUDGE_CE_START_STATE_INFO  "HFTC  |I|  CSDR_HRPD_FTC_JudgeCeStart State Info Qtrslot:%d RF STATE:%d MPS STATE%d "
#define STRING_CSDR_HRPD_FTC_JUDGE_EQ_START_INFO        "HFTC  |I|  CSDR_HRPD_FTC_JudgeEqStart Qtrslot:%d CE STATE:%d DIFF SLOT%d "
#define STRING_CSDR_HRPD_FTC_JUDGE_PRE_DEC_START_INFO   "HFTC  |I|  CSDR_HRPD_FTC_JudgePreDecodeStart Qtrslot:%d EQ STATE:%d DIFF SLOT%d "
#define STRING_CSDR_HRPD_FTC_PROCESS_PREAMBLE_RSLT_1    "HFTC  |I|  CSDR_HRPD_FTC_ProcessPreambleRslt 1 HarqBum:%d Energy:%d"
#define STRING_CSDR_HRPD_FTC_PROCESS_PREAMBLE_RSLT_2    "HFTC  |I|  CSDR_HRPD_FTC_ProcessPreambleRslt 2 HarqBum:%d Energy:%d"
#define STRING_CSDR_HRPD_FTC_PROCESS_PREAMBLE_RSLT_3    "HFTC  |I|  CSDR_HRPD_FTC_ProcessPreambleRslt 3 HarqBum:%d Energy:%d"
#define STRING_CSDR_HRPD_FTC_JUDGE_HARQ_FINISH_1        "HFTC  |I|  CSDR_HRPD_FTC_JudgeHarqFinish CRC OK CurHalfSlot:%d PreambleStartHalfSlot:%d HarqNum:%d ProcessHarqNum:%d MacIndex is %d"
#define STRING_CSDR_HRPD_FTC_JUDGE_HARQ_FINISH_2        "HFTC  |I|  CSDR_HRPD_FTC_JudgeHarqFinish CRC ERROR CurHalfSlot:%d PreambleStartHalfSlot:%d MacIndex is:%d ProcessHarqNum:%d uhwMaxSlotNum:%d"
#define STRING_CSDR_HRPD_FTC_DETECT_HARQ_PREAMBLE       "HFTC  |I|  CSDR_HRPD_FTC_DetectHarqPreamble CurHalfSlot:%d HarqNum:%d MacIndex:%d PreambleEnergy:%d ChannelType[%d]"
#define STRING_CSDR_HRPD_FTC_UPDATE_SCELL_PNOFFSET      "HFTC  |I|  CSDR_HRPD_FTC_UpdateScellPnOffset CC PNOFFSET is %d, ACTIVESET PNOFFSET is %d scell index is %d"
#define STRING_CSDR_HRPD_FTC_DRC_UPDATE_2               "HFTC  |I|  CSDR_HRPD_FTC_DRCMaintain DRC Update R. SlotCount[%d], R_DRC[%d], DRCLength[%d],enDRCGatingEnabled[%d]"

#define STRING_CSDR_HRPD_FTC_PROCESS_HARQ_NUM_ERROR     "HFTC  |E| CSDR_HRPD_FTC_ProcessHarqNum HarqBum:%d, Halfslot:%d "
#define STRING_CSDR_HRPD_FTC_ACTIVE_CCH_TYPE_ERROR      "HFTC  |E| CSDR_HRPD_FTC_ActiveCCh Type Error Qtrslot:%d "
#define STRING_CSDR_HRPD_FTC_ACTIVE_CCH_STATE_ERROR     "HFTC  |E| CSDR_HRPD_FTC_ActiveCCh State Error Qtrslot:%d "
#define STRING_CSDR_HRPD_FTC_PROCESS_DESPREAD_ERROR     "HFTC  |E| CSDR_HRPD_FTC_ProcessDespread HarqBum:%d, Halfslot:%d "
#define STRING_CSDR_HRPD_FTC_PREAMBLE_ERROR_1           "HFTC  |E| CSDR_HRPD_FTC_DetectPreambleByMacIndex fail to get transmition format!! enDRCValue[%d],uhwMacindex[%d],uhwMacIndexPreamble[%d],uhwCCShortPacketsMACIndex[%d],enMultiUserPacketsEnabled[%d]"

#define STRING_CSDR_HRPD_FTC_ACTIVE_TCH_INFO            "HFTC  |I| CSDR_HRPD_FTC_ActiveTCH, setup tch, subtype: %d"
#define STRING_CSDR_HRPD_FTC_DEACTIVE_TCH_INFO          "HFTC  |I| CSDR_HRPD_FTC_DeactiveTCH, stop tch"
#define STRING_CSDR_HRPD_FTC_SLOT_BUFF_FULL_ERROR       "HFTC  |E| CSDR_HRPD_FTC_SlotBuffUpdate, slot buff is full"
#define STRING_CSDR_HRPD_FTC_TCH_START_NO_DRCCOVER_ERR  "HFTC  |E| CSDR_HRPD_FTC_ActiveTCH, Can't find serving cell"
#define STRING_CSDR_HRPD_FTC_ACTIVE_TCH_ERR_2           "HFTC  |E| CSDR_HRPD_FTC_ActiveTCH, FTC status error, CC not active"
#define STRING_CSDR_HRPD_FTC_ACTIVE_TCH_ERR_3           "HFTC  |E| CSDR_HRPD_FTC_ActiveTCH, FTC status error, CC Subtype not match with TCH Subtype! CCSubtype[%d], TCHSubtype[%d]"
#define STRING_CSDR_HRPD_FTC_RECONFIG_NO_DRCCOVER_ERR   "HFTC  |E| CSDR_HRPD_FTC_ReconfigTCH, don't find serving cell"
#define STRING_CSDR_HRPD_FTC_MAINTAIN_ERR_1             "HFTC  |E| CSDR_HRPD_FTC_MaintainTCH, TCH not Active! FTC Status[%d]"
#define STRING_CSDR_HRPD_FTC_MAINTAIN_NO_SC_ERR_2       "HFTC  |E| CSDR_HRPD_FTC_MaintainTCH, can't find target DrcCover in active set! TargetDrcCover[%d]"
#define STRING_CSDR_HRPD_FTC_DRCCOVER_UPDATE_STATE_ERR  "HFTC  |E| CSDR_HRPD_FTC_DRCCoverUpdate, DrcCover state error! enDrcCoverState[%d]"
#define STRING_CSDR_HRPD_FTC_DRCCOVER_UPDATE_NO_SC_ERR  "HFTC  |E| CSDR_HRPD_FTC_DRCCoverUpdate, Can't find serving cell! DrcCover change fail!  ,TargetDrcCover[%d]"
#define STRING_CSDR_HRPD_FTC_DEACTIVE_TCH_WAR           "HFTC  |W| CSDR_HRPD_FTC_DeactiveTCH, TCH not active!  ,TCHStatus[%d]"
#define STRING_CSDR_HRPD_FTC_DRCCOVER_INITIAL_ERR       "HFTC  |E| CSDR_HRPD_FTC_ActiveTCH, the SC indicated by cc_start %d and tch_start %d are different. cproc error!"
#define STRING_CSDR_HRPD_FTC_CC_START_PNOFFSET_WAR      "HFTC  |W| PNOffset %d in CC_Start is differnt from the selected 1st AS or AS_IC cell %d. It is normal. Don't get panic."

/*****************************************************************************
  csdr_hrpd_rtc.c
*****************************************************************************/
#define STRING_CSDR_HRPD_RTC_ACTIVE_ACH_INFO            "HRTC  |I| CSDR_HRPD_RTC_ActiveAch success Qtrslot:%d"
#define STRING_CSDR_HRPD_RTC_JUDGE_ACH_PREAMBLE_INFO    "HRTC  |I| CSDR_HRPD_RTC_JudgePreambleStart success! Preamble slot:%d"
#define STRING_CSDR_HRPD_RTC_JUDGE_ACH_ENC_START_INFO   "HRTC  |I| CSDR_HRPD_RTC_JudgeCapsuleFrameEncStartStop enc start! start slot:%d"
#define STRING_CSDR_HRPD_RTC_JUDGE_ACH_ENC_STOP_INFO    "HRTC  |I| CSDR_HRPD_RTC_JudgeCapsuleFrameEncStartStop enc stop! stop slot:%d"
#define STRING_CSDR_HRPD_RTC_JUDGE_ACH_MOD_START_INFO   "HRTC  |I| CSDR_HRPD_RTC_JudgeCapsuleFrameModStartStop mod start! start slot:%d"
#define STRING_CSDR_HRPD_RTC_JUDGE_ACH_MOD_STOP_1_INFO  "HRTC  |I| CSDR_HRPD_RTC_JudgeCapsuleFrameModStartStop close fe! close slot:%d"
#define STRING_CSDR_HRPD_RTC_JUDGE_ACH_MOD_STOP_2_INFO  "HRTC  |I| CSDR_HRPD_RTC_JudgeCapsuleFrameModStartStop mod stop! stop slot:%d"
#define STRING_CSDR_HRPD_RTC_SET_ACH_STATIC_INFO        "HRTC  |I| CSDR_HRPD_RTC_SetAchStaticParaForAmod qtr slot:%d"
#define STRING_CSDR_HRPD_RTC_SET_TCH_STATIC_01_INFO     "HRTC  |I| CSDR_HRPD_RTC_SetTchStaticParaForAmod set subtype01 static para, Qtrslot:%d"
#define STRING_CSDR_HRPD_RTC_ACTIVE_TCH_INFO            "HRTC  |I| CSDR_HRPD_RTC_ActiveTch success Qtrslot:%d"
#define STRING_CSDR_HRPD_RTC_RECONFIG_TCH_INFO          "HRTC  |I| CSDR_HRPD_RTC_ReconfigTch success Qtrslot:%d"
#define STRING_CSDR_HRPD_RTC_STOP_RTC_INFO              "HRTC  |I| CSDR_HRPD_RTC_StopRtc success Qtrslot:%d"
#define STRING_CSDR_HRPD_RTC_UPDATE_TCH_PARA_ENC_1_INFO "HRTC  |I| CSDR_HRPD_RTC_UpdateParameter enc enter silence Qtrslot:%d"
#define STRING_CSDR_HRPD_RTC_UPDATE_TCH_PARA_ENC_2_INFO "HRTC  |I| CSDR_HRPD_RTC_UpdateParameter enc quit silence Qtrslot:%d"
#define STRING_CSDR_HRPD_RTC_UPDATE_TCH_PARA_RF_1_INFO  "HRTC  |I| CSDR_HRPD_RTC_UpdateParameter rf enter silence Qtrslot:%d"
#define STRING_CSDR_HRPD_RTC_UPDATE_TCH_PARA_RF_2_INFO  "HRTC  |I| CSDR_HRPD_RTC_UpdateParameter rf quit silence Qtrslot:%d"
#define STRING_CSDR_HRPD_RTC_JUDGE_PILOT_START_INFO     "HRTC  |I| CSDR_HRPD_RTC_JudgePilotRriStart success Qtrslot:%d"
#define STRING_CSDR_HRPD_RTC_JUDGE_DRC_START_INFO       "HRTC  |I| CSDR_HRPD_RTC_JudgeDrcStart success Qtrslot:%d"
#define STRING_CSDR_HRPD_RTC_UPDATE_DRC_VALUE_INFO      "HRTC  |I| CSDR_HRPD_RTC_UpdateDrcValueAndDrcCover drc value:%d Qtrslot:%d"
#define STRING_CSDR_HRPD_RTC_UPDATE_DRC_COVER_INFO      "HRTC  |I| CSDR_HRPD_RTC_UpdateDrcValueAndDrcCover drc cover:%d Qtrslot:%d"

#define STRING_CSDR_HRPD_RTC_ACTIVE_ACH_WAR             "HRTC  |W| CSDR_HRPD_RTC_ActiveAch war Qtrslot:%d rtc state:%d"
#define STRING_CSDR_HRPD_RTC_SET_TCH_STATIC_WAR         "HRTC  |W| CSDR_HRPD_RTC_SetTchStaticParaForAmod set static para subtype war, Qtrslot:%d Subtype:%d"
#define STRING_CSDR_HRPD_RTC_ACTIVE_TCH_WAR             "HRTC  |W| CSDR_HRPD_RTC_ActiveTch war Qtrslot:%d rtc state:%d"
#define STRING_CSDR_HRPD_RTC_RECONFIG_TCH_WAR           "HRTC  |W| CSDR_HRPD_RTC_ReconfigTch war Qtrslot:%d rtc state:%d"
#define STRING_CSDR_HRPD_RTC_STOP_RTC_WAR               "HRTC  |W| CSDR_HRPD_RTC_Stop war Qtrslot:%d rtc state:%d"
#define STRING_CSDR_HRPD_RTC_UPDATE_ACK_WAR             "HRTC  |W| CSDR_HRPD_RTC_UpdateAckPara war! packet type:%d, crc:%d, qtr slot:%d"

#define STRING_CSDR_HRPD_RTC_SUBTYPE2_SCHE_ENC_INFO     "HRTC  |I| SUBTYPE2 ENC INFO: uhwHarqId %d, uhwSubPacketIndex %d, enSilenceFlagForEnc %d"
#define STRING_CSDR_HRPD_RTC_SUBTYPE2_MOD_INFO          "HRTC  |I| SUBTYPE2 ENC INFO: uhwHarqId %d, uhwCurHarqSlotIndex %d, uhwQtrSlotIndexInOneSlot %d"

/*****************************************************************************
  csdr_hrpd_rtc_static.c
*****************************************************************************/
#define STRING_CSDR_HRPD_RTC_SUBTYPE2_SCHE_HARQ_INFO        "HRTC  |I| CSDR_HRPD_RTC_Subtype2ScheduleHarq: uhwQtrSlotCntMod4 %d"
#define STRING_CSDR_HRPD_RTC_SUBTYPE2_SCHE_ARQ_CONFIG_INFO  "HRTC  |I| CSDR_HRPD_RTC_Subtype2ScheduleArqConfig: uhwQtrSlotCntMod4 %d"
#define STRING_CSDR_HRPD_RTC_SUBTYPE2_HARQ_INFO             "HRTC  |I| SUBTYPE2 HARQ INFO: uhwHarqId %d, uhwRtcStartSlotCnt %d, uhwSubPacketIndex %d, enDataType %d, usArqPacketID %d"
#define STRING_CSDR_HRPD_RTC_SUBTYPE2_H_L_ARQ_CONFIG_INFO   "HRTC  |I| SUBTYPE2 H/L-ARQ INFO: uhwHarqId %d, uhwFtcSlotCnt %d, enHLArqFlag %d, enAckRslt %d"

#define STRING_CSDR_HRPD_RTC_SUBTYPE2_SUBPACKETINDEX_ERROR  "HRTC  |E| uhwSubPacketIndex error: uhwHarqId %d, uhwRtcStartSlotCnt %d, uhwSubPacketIndex %d, enDataType %d, usArqPacketID %d"

#define STRING_CSDR_HRPD_RTC_SUBTYPE2_MAX_SUBPACKET_WARNING "HRTC  |W| uhwHarqId %d, uhwMaxSubPacketNum %d"

/*****************************************************************************
  csdr_feitf.c
*****************************************************************************/
#define STRING_CSDR_FEITF_ERROR                         "CFEITF|E| Start BBP master uwRet = %d"


/*****************************************************************************
  csdr_hrpd_demod.c
*****************************************************************************/

#define STRING_CSDR_HRPD_DEMOD_EARLIEST_FINGER_PHASE    "HDEMOD|I| CSDR_HRPD_DEMOD_CalcEarliestFinger Earliest Finger Phase:%d"
#define STRING_CSDR_HRPD_DEMOD_MAC_BASE_CNT             "HDEMOD|I| CSDR_HRPD_DEMOD_BaseCntCalc MAC Feith Base cnt:%d"
#define STRING_CSDR_HRPD_DEMOD_LSRC_CELL_INFO           "HDEMOD|I| CSDR_HRPD_DEMOD_PickLsrcPara LSRC SC Index:%d, IC1 Index: %d,IC2 Index: %d,IC Num: %d"
#define STRING_CSDR_HRPD_DEMOD_LSRC_CELL_INFO_LAST      "HDEMOD|I| CSDR_HRPD_DEMOD_PickLsrcPara Last LSRC SC Index:%d, IC1 Index: %d,IC2 Index: %d,IC Num: %d"
#define STRING_CSDR_HRPD_DEMOD_IC_INFO                  "HDEMOD|I| CSDR_HRPD_DEMOD_ScIcInfoConfirm IC2 Index:%d, New IC index: %d"
#define STRING_CSDR_HRPD_DEMOD_INTERP_VALID_FINGER_NUM  "HDEMOD|I| CSDR_HRPD_DEMOD_Interp2FingerDataAddrCalc Valid Finger Num:%d"
#define STRING_CSDR_HRPD_DEMOD_PN_POSITION              "HDEMOD|I| CSDR_HRPD_DEMOD_CalcPnCode Pn Position:%d"
#define STRING_CSDR_HRPD_DEMOD_ALPHA_FILTER_INFO        "HDEMOD|I| CSDR_HRPD_DEMOD_CE NoiseAnt1:%d,NoiseAnt2:%d,Fist Filter:%d"

#define STRING_CSDR_HRPD_DEMOD_GET_FEITF_DATA_ERROR     "HDEMOD|E| CSDR_HRPD_DEMOD_GetFeItfDataAddr Get Feitf Data Failure"
#define STRING_CSDR_HRPD_DEMOD_ANT1_PN_INDEX_ERROR      "HDEMOD|E| CSDR_HRPD_DEMOD_Ant1LsrcPara Ant1 PN Index Error: %d"
#define STRING_CSDR_HRPD_DEMOD_ANT2_PN_INDEX_ERROR      "HDEMOD|E| CSDR_HRPD_DEMOD_Ant2LsrcPara Ant2 PN Index Error: %d"
#define STRING_CSDR_HRPD_DEMOD_EALIEST_FINGER_ERROR     "HDEMOD|E| CSDR_HRPD_DEMOD_BaseCntCalc Earliest Finger Position Invalid"
#define STRING_CSDR_HRPD_DEMOD_NO_VALID_FINGER_FOUND_ERROR  "HDEMOD|E| CSDR_HRPD_DEMOD_FingerIndexCalc No Valid Finger Found"
#define STRING_CSDR_HRPD_DEMOD_PN_NUM_OVERFLOW_ERROR    "HDEMOD|E| CSDR_HRPD_DEMOD_RelateFinger2PnCode Pn Code Num Overflow"

/*****************************************************************************
  csdr_hrpd_demod_memory.c
*****************************************************************************/
#define STRING_CSDR_HRPD_DEMOD_HALFSLOT_MEM_ERROR          "HDEMOD|E| CSDR_HRPD_DEMOD_MemManagement half slot memory error "
#define STRING_CSDR_HRPD_DEMOD_MOD_MEM_ERROR               "HDEMOD|E| CSDR_HRPD_DEMOD_MemManagement module memory error "
#define STRING_CSDR_HRPD_DEMOD_INC_MEM_ERROR               "HDEMOD|E| CSDR_HRPD_DEMOD_MemManagement inc memory error "
#define STRING_CSDR_HRPD_DEMOD_HALFSLOT_MEM_OVERFLOW_ERROR "HDEMOD|E| CSDR_HRPD_DEMOD_MemManagement half slot memory Overflow, uwMaxUsedBlkSize = %d, uwBlkNum = %d "
#define STRING_CSDR_HRPD_DEMOD_MOD_MEM_OVERFLOW_ERROR      "HDEMOD|E| CSDR_HRPD_DEMOD_MemManagement module memory Overflow, uwMaxUsedBlkSize = %d, uwBlkNum = %d "
#define STRING_CSDR_HRPD_DEMOD_INC_MEM_OVERFLOW_ERROR      "HDEMOD|E| CSDR_HRPD_DEMOD_MemManagement inc memory Overflow, uwMaxUsedBlkSize = %d, uwBlkNum = %d "

/*****************************************************************************
  csdr_hrpd_ave.c
*****************************************************************************/
#define STRING_CSDR_HRPD_AVE_RESULT_ERROR               "HAVE  |E| CSDR_HRPD_AVE_MapVeIndToCeWinLen Invalid AVE Result: %d"

/*****************************************************************************
  csdr_hrpd_tx_pwrctrl.c
*****************************************************************************/
#define STRING_CSDR_HRPD_APC_SET_ACH_STATIC_PARA        "HAPC |E| CSDR_HRPD_APC_SetAchStaticPara, enSubtype = %d, shwPowerAdjust = %d, shw9k6GaindB = %d"
#define STRING_CSDR_HRPD_APC_SET_TCH_STATIC_PARA        "HAPC |E| CSDR_HRPD_APC_SetTchStaticPara, enSubtype = %d, uhwRpcStep = %d"
#define STRING_CSDR_HRPD_APC_ACH                        "HAPC |E| CSDR_HRPD_APC_Ach, uhwGd = %d, shwRfPwr = %d"
/* #define STRING_CSDR_HRPD_APC_CALC_ACH_POWER             "HAPC |E| CSDR_HRPD_APC_CalcAchPower, shwPilotPower = %d, shwRssi = %d" */
#define STRING_CSDR_HRPD_APC_TCH                        "HAPC |E| CSDR_HRPD_APC_Tch, shwPilotPower = %d, shwPowerHeadroom = %d, uhwGd = %d, shwRfPwr = %d"
#define STRING_CSDR_HRPD_APC_BACKOFF_CHAN               "HAPC |E| CSDR_HRPD_APC_BackoffChan, uwDeltaPowSum = %d"
#define STRING_CSDR_HRPD_APC_BACKOFF_DATA_DOWN          "HAPC |E| CSDR_HRPD_APC_BackoffDataDown, warning: uwDataPow = %d, uwMinPow = %d"
#define STRING_CSDR_HRPD_APC_UPDATE_TCH_CHAN_INFO       "HAPC |E| CSDR_HRPD_APC_UpdateTchChanInfo, error: uhwChanNum = %d, uhwActChanNum = %d"

/*****************************************************************************
  csdr_hrpd_amod.c
*****************************************************************************/
#define STRING_CSDR_HRPD_AMOD_ACH_DATA_ERROR            "HAMOD |E| CSDR_HRPD_AMOD_GetSubType01EncData valid flag of Buffer Being used is INVALID "


#define STRING_CSDR_HRPD_AMOD_DATA_VALID_FLAG_ERROR     "HAMOD |E| CSDR_HRPD_AMOD_GetEncData valid flag of Buffer Being used is INVALID "
#define STRING_CSDR_HRPD_AMOD_MOD_FLAG_ERROR            "HAMOD |E| CSDR_HRPD_AMOD_GetEncData Mod flag is INVALID "

/*****************************************************************************
  csdr_hrpd_amod_memory.c
*****************************************************************************/
#define STRING_CSDR_HRPD_AMOD_QTRSLOT_MEM_ERROR         "HAMOD |E|  CSDR_HRPD_AMOD_MemManagement Qtr Slot memory error "
#define STRING_CSDR_HRPD_AMOD_INC_MEM_ERROR             "HAMOD |E|  CSDR_HRPD_AMOD_MemManagement inc memory error "
#define STRING_CSDR_HRPD_AMOD_QTRSLOT_MEM_OVERFLOW_ERROR "HAMOD |E| CSDR_HRPD_AMOD_MemManagement Qtr Slot memory Overflow, uwMaxUsedBlkSize = %d, uwBlkNum = %d "
#define STRING_CSDR_HRPD_AMOD_INC_MEM_OVERFLOW_ERROR    "HAMOD |E|  CSDR_HRPD_AMOD_MemManagement Inc memory Overflow, uwMaxUsedBlkSize = %d, uwBlkNum = %d "

/*****************************************************************************
  csdr_hrpd_aenc_memory.c
*****************************************************************************/
#define STRING_CSDR_HRPD_AENC_MEM_ALLOC_ERROR           "HAENC |E| not enough memory for inc memory allocation"
#define STRING_CSDR_HRPD_AENC_MEM_OVERFLOW_ERROR        "HAENC |E| memory overflow,required memory %d is larger than avaiable memory %d"

/*****************************************************************************
  csdr_hrpd_aenc.c
*****************************************************************************/
#define STRING_CSDR_HRPD_AENC_FSM_TRANSITION_INFO       "HAENC |I| enEncState %d, enEncEvent %d"
#define STRING_CSDR_HRPD_AENC_ERROR_HANDLING_ERROR      "HAENC |E| fsm error handling, FsmState %d, Event %d, TrafficType %d"
#define STRING_CSDR_HRPD_AENC_ENC_FLAG_ERROR            "HAENC |E| enc_flag is IDLE when processing start event"
#define STRING_CSDR_HRPD_AENC_DATA_VALID_FLAG_ERROR     "HAENC |E| valid flag of PingPong Flag %d is VALID when enc try to write VALID into it"
#define STRING_CSDR_HRPD_AENC_DMA_ALLOC_ERROR           "HAENC |E| Allocation for DMA (encoding) error!"
#define STRING_CSDR_HRPD_AENC_DMA_CFG_ERROR             "HAENC |E| DMA cfg error!"

/*****************************************************************************
  csdr_hrpd_aafc.c
*****************************************************************************/
#define STRING_CSDR_HRPD_AFC_RX_DIV_CHANGE_WARNING      "HAFC  |W| prev enRxDivFlag %d, current enRxDivFlag %d"

/*****************************************************************************
  csdr_hrpd_aafc_mn.c
*****************************************************************************/
#define STRING_CSDR_HRPD_AFC_FREQ_OFFSET_INFO           "HAFC  |I| CSDR_HRPD_AAFC_MN_RptAfcMemInfo FreqOffset %d"
#define STRING_CSDR_HRPD_AFC_LOCK_IND_INFO              "HAFC  |I| CSDR_HRPD_AAFC_MN_RptAfcMemInfo LockInd %d"

/*****************************************************************************
  csdr_edma.c
*****************************************************************************/
#define STRING_CSDR_EDMA_ALLOC_MEM_ERROR                "CEDMA |E| CSDR_EDMA_ConfigEntry allocate memory error on channel NO. : %d"
#define STRING_CSDR_EDMA_LLI_FAIL_ERROR                 "CEDMA |E| CSDR_EDMA_ConfigEntry get lli config add error on channel NO. : %d"
#define STRING_CSDR_EDMA_WRONG_ID_ERROR                 "CEDMA |E| CSDR_EDMA_Enable wrong channel ID"
#define STRING_CSDR_EDMA_DISABLE_WRONG_ID_ERROR         "CEDMA |E| CSDR_EDMA_Disable wrong channel ID"
#define STRING_CSDR_EDMA_CHAN_ID_REQ_ID_ERROR           "CEDMA |E| CSDR_1X_EDMA_ConfigEntry wrong channel ID %d or req ID %d"
#define STRING_CSDR_EDMA_CFG_EDMA_ERROR                 "CEDMA |E| CSDR_1X_EDMA_ConfigEntry config edma fail"
#define STRING_CSDR_EDMA_CFG_START_CHAN_ID_REQ_ID_ERROR "CEDMA |E| CSDR_EDMA_ConfigAndStart wrong channel ID %d or req ID %d"
#define STRING_CSDR_EDMA_CFG_START_CFG_EDMA_ERROR       "CEDMA |E| CSDR_EDMA_ConfigAndStart config edma fail"

/*****************************************************************************
　csdr_feitf.c
*****************************************************************************/
#define STRING_CSDR_FEITF_BUFFER_EMPTY_ERROR                "CFEITF|E| CSDR_FEITF_CalcAntDataAddr buffer is empty"
#define STRING_CSDR_FEITF_BUFF_HEAD_ERROR                   "CFEITF|E| CSDR_FEITF_CalcAntDataAddr head buffer head is bigger than buffer size. head chippos is %d chip is %d basecnt is %d maxchipnum is %d"
#define STRING_CSDR_FEITF_TAIL_BUFF_HEAD_ERROR              "CFEITF|E| CSDR_FEITF_CalcAntDataAddr tail buffer head is bigger than buffer size. head chip is %d basecnt is %d chippos is %d maxchipnum is %d"
#define STRING_CSDR_FEITF_NULL_PTR_ERROR                    "CFEITF|E| CSDR_FEITF_CalcDataAddr is null pointer"

/*****************************************************************************
 csdr_feitf_memory.c
*****************************************************************************/
#define STRING_CSDR_FEITF_MEM_ASSIGN_ERROR              "CFEITF|E| CSDR_FEITF_MemManagement AssignMemFail, BlkNum is %d"
#define STRING_CSDR_FEITF_MEM_BLKSIZE_ERROR             "CFEITF|E| CSDR_FEITF_MemManagement MaxUsedBlkSize error, BlkSize is %d"

/*****************************************************************************
 csdr_hrpd_ave_memory.c
*****************************************************************************/
#define STRING_CSDR_HRPD_AVE_MEM_ASSIGN_ERROR           "HAVE  |E| CSDR_HRPD_AVE_MemManagement AssignMemFail, BlkNum is %d"
#define STRING_CSDR_HRPD_AVE_MEM_BLKSIZE_ERROR          "HAVE  |E| CSDR_HRPD_AVE_MemManagement MaxUsedBlkSize error, BlkSize is %d"

/*****************************************************************************
 csdr_hrpd_cs.c
*****************************************************************************/
#define STRING_CSDR_HRPD_CS_NOISE_NUM_ERROR             "HCS   |E| CSDR_HRPD_CS_CorrRsltProcNo1XTiming NoiseNum is zero"
#define STRING_CSDR_HRPD_CS_NOISE_NUM_WITH1X_ERROR      "HCS   |E| CSDR_HRPD_CS_CorrRsltProcWith1XTiming noise num is zero"

/*****************************************************************************
 csdr_hrpd_demod.c
*****************************************************************************/
#define STRING_CSDR_HRPD_DEMOD_CELL_TYPE_ERROR          "HDEMOD|E| CSDR_HRPD_DEMOD_FingerIndexCalc CellType is error, CellTypeInd is %d"

/*****************************************************************************
 csdr_hrpd_demod_memory.c
*****************************************************************************/
#define STRING_CSDR_HRPD_DEMOD_MEM_ASSIGN_ERROR         "HDEMOD|E| CSDR_HRPD_DEMOD_MemManagement AssignMemFail, BlkNum is %d FirstAddr is $d"
#define STRING_CSDR_HRPD_DEMOD_MEM_BLKSIZE_ERROR        "HDEMOD|E| CSDR_HRPD_DEMOD_MemManagement MaxUsedBlkSize error, BlkSize is %d"
#define STRING_CSDR_HRPD_DEMOD_POOL_MEM_ASSIGN_ERROR    "HDEMOD|E| CSDR_HRPD_DEMOD_MemManagement MemPool AssignMemFail, BlkNum is %d FirstAddr is $d"
#define STRING_CSDR_HRPD_DEMOD_POOL_MEM_BLKSIZE_ERROR   "HDEMOD|E| CSDR_HRPD_DEMOD_MemManagement MemPool MaxUsedBlkSize error, BlkSize is %d"
#define STRING_CSDR_HRPD_DEMOD_INC_MEM_ASSIGN_ERROR     "HDEMOD|E| CSDR_HRPD_DEMOD_MemManagement MemInc AssignMemFail, BlkNum is %d FirstAddr is $d"
#define STRING_CSDR_HRPD_DEMOD_INC_MEM_BLKSIZE_ERROR    "HDEMOD|E| CSDR_HRPD_DEMOD_MemManagement MemInc MaxUsedBlkSize error, BlkNum is %d"


/*****************************************************************************
 csdr_hrpd_ftc.c
*****************************************************************************/
#define STRING_CSDR_HRPD_FTC_NO_DATA_ERROR          "HFTC  |E| CSDR_HRPD_FTC_ScheduleCeAndAfc no data from FE_ITF!"

/*****************************************************************************
 csdr_hrpd_mps.c
*****************************************************************************/
#define STRING_CSDR_HRPD_MPS_ANT_NUM_ERROR          "HMPS  |E| CSDR_HRPD_MPS_ProcessValidPathRslt AntNum is error! AntNum is %d"
#define STRING_CSDR_HRPD_MPS_TED_STEP_INFO          "HTED  |I| CSDR_HRPD_MPS_TedCtrl TedStep %d"
#define STRING_CSDR_HRPD_MPS_PN_SEQ_INDX_WHEN_SUSPEND_INFO  "HMPS  |I| when suspend mps, PnOffset %d, SeqIdx %d"
#define STRING_CSDR_HRPD_MPS_PN_SEQ_INDX_WHEN_RESUME_INFO   "HMPS  |I| when resume mps, PnOffset %d, SeqIdx %d"

/*****************************************************************************
 csdr_hrpd_searchmeas_layer_a_int.c
*****************************************************************************/
#define STRING_CSDR_HRPD_SEARCHMEAS_INTERRUPT_ERROR "HSRCHM|E| CSDR_HRPD_SMC_InterruptProcessEntry Interrupt is error!"

/*****************************************************************************
 csdr_hrpd_smc.c
*****************************************************************************/
#define STRING_CSDR_HRPD_SMC_MSG_NUM_ERROR          "HSMC  |E| CSDR_HRPD_SMC_AddMsgBlock the MsgNum of MsgBlkList is error, the MsgID is %d"
#define STRING_CSDR_HRPD_SMC_MPS_STATE_ERROR        "HSMC  |E| CSDR_HRPD_SMC_MpsErrorProtect MPS error. The MpsState is %d, the MpsType is %d"
#define STRING_CSDR_HRPD_SMC_CS_FSM_ERROR           "HSMC  |E| CSDR_HRPD_SMC_ProcessCsFsm the CS FSM is error!"
#define STRING_CSDR_HRPD_SMC_CS_UNITNUM_ERROR       "HSMC  |E| CSDR_HRPD_SMC_InitCsFsmNull the CS UnitNum is not satisfied! The UnitNum is %d"
#define STRING_CSDR_HRPD_SMC_SCAN_FSM_ERROR         "HSMC  |E| CSDR_HRPD_SMC_ProcessScanFsm the Scan FSM is error!"
#define STRING_CSDR_HRPD_SMC_CS_FSM_MONITOR_ERROR   "HSMC  |E| CSDR_HRPD_SMC_CsFsmMonitor the CsFsmStateCnt is zero, the FsmState is %d"

#define STRING_CSDR_HRPD_SMC_MPS_CFG_WRN            "HSMC  |W| CSDR_HRPD_SMC_MpsCfgReqHandle MpsCfg warning! the MpsPnNum is %d the MpsType is %d"
#define STRING_CSDR_HRPD_SMC_MPS_UNIT_WRN           "HSMC  |W| CSDR_HRPD_SMC_MpsUnitCfg MpsUnit warning! apply rslt is %d"
#define STRING_CSDR_HRPD_SMC_MPS_DMA_WRN            "HSMC  |W| CSDR_HRPD_SMC_MpsUnitCfg MpsDma warning!  apply rslt is %d"
#define STRING_CSDR_HRPD_SMC_MPS_START_WRN          "HSMC  |W| CSDR_HRPD_SMC_MpsStart MpsType warning! the MpsType is %d"
#define STRING_CSDR_HRPD_SMC_MPS_RECFG_WRN          "HSMC  |W| CSDR_HRPD_SMC_MpsReconfig MpsReCfg UnitNum is warning! the UnitNum is %d"
#define STRING_CSDR_HRPD_SMC_MPS_MEAS_WRN           "HSMC  |W| CSDR_HRPD_SMC_MpsMeasCalcTask MpsType is warning! the MpsType is %d"

#define STRING_CSDR_HRPD_SMC_MPS_HANDLE_ERROR       "HSMC  |E| CSDR_HRPD_SMC_MpsErrorHandling the Mps is error! the MpsState is %d the MpsEvent is %d"
#define STRING_CSDR_HRPD_SMC_MPS_PNNUM_ERROR        "HSMC  |E| CSDR_HRPD_SMC_MpsStart the MpsPnNum is error! the MpsPnNum is %d"
#define STRING_CSDR_HRPD_SMC_MSGID_ERROR            "HSMC  |E| CSDR_HRPD_SMC_ProcessMsg the MsgId is error! the MsgId is %d"

#define STRING_CSDR_HRPD_SMC_MPS_CELLTYPE_ERROR     "HSMC  |E| mps message cell type error, cellType: %d"
#define STRING_CSDR_HRPD_SMC_MPS_SERVINGCELL_ERROR  "HSMC  |E| mps message find two more serving cell, num: %d"
#define STRING_CSDR_HRPD_SMC_MPS_NOSERVING_ERROR    "HSMC  |E| mps can't find serving cell."
#define STRING_CSDR_HRPD_SMC_MPS_MPSTYPE_ERROR      "HSMC  |E| mps type is wrong, type: %d"
#define STRING_CSDR_HRPD_SMC_MPS_DIV_TYPE_ERROR     "HSMC  |E| mps div type is wrong, DivEnable: %d, DivUse: %d"

#define STRING_CSDR_HRPD_MPS_MEAS_LTE_INTERRUPT_ERR "HSMC  |E| CSDR_HRPD_SMC_INTER_SYS_IntReqHandle interrupt type error! InterruptType is %d"
#define STRING_CSDR_HRPD_SMC_MPS_SC_ERROR           "HSMC  |E| Number of SC %d is not correct! Check MPS_REQ and SC indicated by CC_Start, Tch_Start or Tch_Maintain."

/*****************************************************************************
 csdr_hrpd_inter_rat.c
*****************************************************************************/
#define STRING_CSDR_HRPD_INTERRAT_START_GAP_NOT_ENOUGH_WRN          "HSMC  |W| CSDR_HRPD_INTERRAT_GetInt0Int1Int2 Gap not enough! GapLength is %d hrpd chip"
#define STRING_CSDR_HRPD_INTERRAT_START_REJECT_NEW_MEAS_REQ_WRN     "HSMC  |W| CSDR_HRPD_INTERRAT_Start Inter rat Meas is runing, can't handle new request! MeasStatus is %d "
#define STRING_CSDR_HRPD_INTERRAT_STOP_GAP_STATUS_WAR               "HSMC  |W| CSDR_HRPD_INTERRAT_ResetGapEnd Inter rat Status error! Status is %d"

#define STRING_CSDR_HRPD_INTERRAT_START_MULTI_MODE_ERR              "HSMC  |E| CSDR_HRPD_INTERRAT_Start multi-mode type error! MultiMode is %d"
#define STRING_CSDR_HRPD_INTERRAT_START_SETUP_ERR                   "HSMC  |E| CSDR_HRPD_INTERRAT_Start fail to get systime! ErrorCode %d"
#define STRING_CSDR_HRPD_INTERRAT_START_INT1_ERR                    "HSMC  |E| CSDR_HRPD_INTERRAT_GetInt0Int1Int2 Error! int1-now should < 80ms! DiffInt1ToNow %d"
#define STRING_CSDR_HRPD_INTERRAT_INT_REQ_INTERRUPT_ERR             "HSMC  |E| CSDR_HRPD_INTERRAT_IntReqHandle INTERRUPT_ERR! InterruptType %d"
#define STRING_CSDR_HRPD_INTERRAT_GAPEND_MULTI_MODE_ERR             "HSMC  |E| CSDR_HRPD_INTERRAT_ResetGapEnd multi-mode type error! MultiMode is %d"
#define STRING_CSDR_HRPD_INTERRAT_INT_REQ_PURPOSE_ERR               "HSMC  |E| CSDR_HRPD_INTERRAT_IntReqHandle enPurpose error! enPurpose is %d"

/*****************************************************************************
 csdr_interrupt.c
*****************************************************************************/
#define STRING_CSDR_INTERRUPT_ISR_ERROR             "CINTER|E| CSDR_COMM_ISR_ModifyIsr ISR is error, the IntNo is %d the IntBitNo is %d"
#define STRING_CSDR_INTERRUPT_INT_INDEX_ERROR       "CINTER|E| CSDR_COMM_ISR_ModifyIsr IntIndex is error!"
#define STRING_CSDR_INTERRUPT_INT_NO_BIT_ERROR      "CINTER|E| CSDR_COMM_ISR_ModifyIsr interrupt has relevant bit!"


/*****************************************************************************
 csdr_mailbox.c
*****************************************************************************/
#define STRING_CSDR_MAILBOX_MSG_LEN_ERROR           "CMAILB|E| CSDR_COMM_SendExternalMsg MsgLen is two big! the MsgLen is %d the SendMsg is %d"

/*****************************************************************************
 csdr_mntn.c
*****************************************************************************/
#define STRING_CSDR_MNTN_REGISTER_PARA_ERROR        "CMNTN |E| CSDR_MNTN_RegisterPeriodLog Register Para is error. The ModId is %d the Info is %d"
#define STRING_CSDR_MNTN_NEWPERIODLOG_ERROR         "CMNTN |E| CSDR_MNTN_RegisterPeriodLog NewPeriodLog is error. The ModId is %d"
#define STRING_CSDR_MNTN_DEREGISTER_PARA_ERROR      "CMNTN |E| CSDR_MNTN_DeRegisterPeriodLog DeRegister Para is error. The ModId is %d"
#define STRING_CSDR_MNTN_REGMNTNCFG_ERROR           "CMNTN |E| CSDR_MNTN_RegisterMntnConfigInfo para is error. The ModId is %d"
#define STRING_CSDR_MNTN_SAMPLE_RPT_ERROR           "CMNTN |E| CSDR_MNTN_SampleDataMsgReport MsgId is error. The ModId is %d"

#define STRING_CSDR_MNTN_NEWPERIODLOG_EXIST_INFO    "CMNTN |I| CSDR_MNTN_RegisterPeriodLog NewPeriodLog is exist. The ModId is %d the Msg is %d"
#define STRING_CSDR_MNTN_RPTPERIODLOG_INFO          "CMNTN |I| CSDR_MNTN_ReportPeriodLog CycleCntEnd subtract CycleCntBegin is %d"

/*****************************************************************************
  csdr_hrpd_mac_memory.c
*****************************************************************************/
#define STRING_CSDR_HRPD_MAC_MEM_ALLOC_ERROR            "HMAC |E| not enough memory for memory allocation"
#define STRING_CSDR_HRPD_MAC_MEM_OVERFLOW_ERROR         "HMAC |E| memory overflow,required memory %d is larger than avaiable memory %d"

/*****************************************************************************
  csdr_hrpd_mac_layer_b.c
*****************************************************************************/
#define STRING_CSDR_HRPD_MAC_DRCLOCKLENGTH_INFO         "HMAC |I| drclocklength is %d and drclock move bit is %d"
#define STRING_CSDR_HRPD_MAC_PARAMETER_ERR              "HMAC |E| CSDR_HRPD_MAC_DropDrcLockOnce, parameter error, DrcLockPeriod:%d, DrcLockLength: %d"

/*****************************************************************************
  csdr_hrpd_smc.c
*****************************************************************************/
#define STRING_CSDR_HRPD_SMC_MEAS_WITHOUT_BUFFER_ERROR      "HMEAS |E| enHaveBuffered %d, enBufferMeas %d"
#define STRING_CSDR_HRPD_SMC_MEAS_STATE_ERROR               "HMEAS |E| enSmcMeasState %d go to wrong branch"
#define STRING_CSDR_HRPD_SMC_MEAS_REQ_ERROR                 "HMEAS |E| CSDR_HRPD_SMC_InterruptProcessEntry enSmcMeasState %d enCurrentMeasEvent %d throw away wrong req"
#define STRING_CSDR_HRPD_SMC_MEAS_FSM_INFO              "HMEAS |I| trigger meas fsm enSmcMeasState %d enCurrentMeasEvent %d"
#define STRING_CSDR_HRPD_SMC_MEAS_ERROR_HDL_WARNING     "HMEAS |W| meas error handling enSmcMeasState %d enCurrentMeasEvent %d"
#define STRING_CSDR_HRPD_SMC_MEAS_REQ_HANDLE_ERROR          "HMEAS |E| CSDR_HRPD_SMC_MeasErrorHandling enSmcMeasState %d enCurrentMeasEvent %d throw away wrong req"
#define STRING_CSDR_HRPD_SMC_INFO                           "HMEAS |I| enSmcMeasState %d enCurrentMeasEvent %d"
#define STRING_CSDR_HRPD_SMC_UNIT_ERROR                     "HMEAS |E| unit error uhwIdleUnitNum %d pstMeasUnitCfg->uhwUnitNum %d"
#define STRING_CSDR_HRPD_SMC_SLAVE_MEAS_TYPE_ERROR          "HMEAS [E] CSDR_HRPD_SMC_NullStateMeasStart error: enMeasType %d"
#define STRING_CSDR_HRPD_SMC_INT2_HANDLE_ERROR              "HMEAS [E] CSDR_HRPD_SLAVE_MEAS_Int2EventHandle error: enMeasFsmState %d"
#define STRING_CSDR_HRPD_SMC_INT4_HANDLE_ERROR              "HMEAS [E] CSDR_HRPD_SLAVE_MEAS_Int4EventHandle error: enMeasFsmState %d"
#define STRING_CSDR_HRPD_SMC_1X_CONFLICT_HANDLE_ERROR       "HMEAS [E] CSDR_HRPD_SLAVE_MEAS_1xCorrelatorConflictEventHandle error: enMeasFsmState %d"
#define STRING_CSDR_HRPD_SMC_INT_REQ_PURPOSE_ERROR          "HMEAS [E] CSDR_HRPD_SMC_IntReqHandle enPurpose error! enPurpose %d"
#define STRING_CSDR_HRPD_SMC_INT_WARNING                    "HMEAS [W] redundant int warning enEventID %d"
#define STRING_CSDR_HRPD_SMC_DELTABASECNT_INVALID_INFO      "HMEAS [I] CSDR_HRPD_SMC_Int0Proc uwDeltaBaseCnt invalid"
#define STRING_CSDR_HRPD_SMC_MEAS_BUFFER_INFO           "HMEAS [I] meas buffer start current basecnt %d datastorepos %d curqtrslot %d"
#define STRING_CSDR_HRPD_SMC_MEAS_BUFFER_INT_INFO       "HMEAS [I] meas buffer end curqtrslot %d"
#define STRING_CSDR_HRPD_SMC_SLAVE_MEAS_REQ_HANDLE_ERROR    "HMEAS |E| CSDR_HRPD_SMC_MeasErrorHandling SLAVE enSmcMeasState %d enCurrentMeasEvent %d throw away wrong req"
#define STRING_CSDR_HRPD_SMC_MPS_NUM_OF_UNIT_WHEN_RESUMW_INFO   "HMPS |I| number of correlators for MPS when resumed %d"
#define STRING_CSDR_HRPD_SMC_MPS_WRONG_MPS_REQ_ERROR            "HMPS |E| cproc cannot send mps_req during suspend"
#define STRING_CSDR_HRPD_SMC_MPS_WRONG_SUSPEND_REQ_ERROR        "HMPS |E| cproc cannot send suspend_req during mps state %d"
#define STRING_CSDR_HRPD_SMC_MPS_WRONG_INT_DURING_SUSPEND_ERROR "HMPS |E| receive interrupt during suspend, event %d"
#define STRING_CSDR_HRPD_SMC_MPS_WRONG_RESUME_REQ_ERROR         "HMPS |E| cproc cannot send resume_req during mps state %d"
#define STRING_CSDR_HRPD_SMC_CS_INT_ERROR                       "HCS [E] unexpected CS int enInterruptType %d,uwReturnVal %d"
#define STRING_CSDR_HRPD_SMC_FIND_RSCP_ERROR                    "HMPS |E| CSDR_HRPD_SMC_FindRscp find RSCP error"
/*****************************************************************************
csdr_hrpd_searchmeas_layer_a_int.c
*****************************************************************************/
#define STRING_CSDR_HRPD_SEARCHMEAS_LAYRA_INT_ERROR     "HMEAS |E| enInterruptType %d uwReturnVal %d"

/*****************************************************************************
  csdr_hrpd_meas.c
*****************************************************************************/
#define STRING_CSDR_HRPD_MEAS_CELL_NUM_INCORRECT_WARNING    "HMEAS |W| cell num is %d"
#define STRING_CSDR_HRPD_MEAS_CELL_INDEX_OUT_RANGE_WARNING  "HMEAS |W| cell num is %d, cell index is %d"


/*****************************************************************************
  csdr_cal.c 校准模块打印
*****************************************************************************/
#define STRING_CSDR_CAL_DCR_MNTN_ANT1_ERROR                 "CCAL |E| DCR Error Ant1 iteration 4 times dciq is %d, %d, %d, %d"
#define STRING_CSDR_CAL_DCR_MNTN_ANT2_ERROR                 "CCAL |E| DCR Error Ant2 iteration 4 times dciq is %d, %d, %d, %d"
#define STRING_CSDR_CAL_IP2_MNTN_WARNING                    "CCAL |W| IP2 Freq is %d, IMD2 is %d, I code is %d, Q code is %d"
#define STRING_CSDR_CAL_LO_LEAKAGE_MNTN_WARNING             "CCAL |W| LOLEAKAGE DcI is %d, DcQ is %d"
#define STRING_CSDR_CAL_IQ_MISMATCH_MNTN_CORR_WARNING       "CCAL |W| IQMISMATCH corrconj real is %d, img is %d, corr real is %d, img is %d"
#define STRING_CSDR_CAL_IQ_MISMATCH_ERROR_TXMC              "CCAL |E| IQMISMATCH TxMc Error,check corr_ab and corr_cd print before"
#define STRING_CSDR_CAL_IQ_MISMATCH_ERROR_TXAP              "CCAL |E| IQMISMATCH TxAP Error,TxMc real is %d, img is %d, Last A is %d, P is %d"
#define STRING_CSDR_CAL_IQ_MISMATCH_ERROR_IR                "CCAL |E| IQMISMATCH IR Error,Corrabs is %d, CorrConj real is %d, img is %d, Corr real is %d, img is %d"
#define STRING_CSDR_CAL_ERROR_SAMPLE_DATA                   "CCAL |E| This is self cal Sample data report at last sample. Type is %d, U32Len is %d"



/*****************************************************************************
  csdr_hrpd_slave_meas.c
*****************************************************************************/
#define STRING_CSDR_HRPD_SLAVE_MEAS_1X_CORRELATOR_CONFLICT_INFO "HMEAS |I| CSDR_HRPD_SLAVE_MEAS_CorrelatorValidJudge: Waiting for correlator valid"
#define STRING_CSDR_HRPD_SLAVE_MEAS_JUDGE_1X_RUNING_INFO        "HMEAS |I| CSDR_HRPD_SLAVE_MEAS_1xTimingJudge: 1x Vaild:%d"
#define STRING_CSDR_HRPD_SLAVE_MEAS_LTE_PPM_INFO                "HMEAS |I| CSDR_HRPD_SLAVE_MEAS_SetLtePpm: ppm:%d, AfcLock:%d, PPM Valid:%d"
#define STRING_CSDR_HRPD_SLAVE_MEAS_GET_PPM_INFO                "HMEAS |I| CSDR_HRPD_SLAVE_MEAS_GetPpmFromLte, send int10 to LPHY "
#define STRING_CSDR_HRPD_SLAVE_MEAS_LTE_PPM_ERR                 "HMEAS |E| CSDR_HRPD_SLAVE_MEAS_SetLtePpm: PPM Invalid! ppm:%d, AfcLock:%d, PPM Valid:%d"

/*****************************************************************************
  xsys_startup.c
*****************************************************************************/
#define STRING_CSDR_1X_ACTIVE   "CSDR_1X_ActiveCfgReqHandle Enter "

#define STRING_CSDR_1X_SETWORKMODE  "CSDR_1X_SetWorkModeCfgReqHandle Enter, Lines  %d, Mode  %d "

/*****************************************************************************
  x_sched.c
*****************************************************************************/
#define STRING_CSDR_PRIMITIVE_ABNORMAL_EXIT_INFO "Primitive Proc Abnormal Exit!  %d"

/* uphy_csdr_loader.c */
#define STRING_CSDR_LOAD_SECT_LEN_ERROR_INFO 		"LOADER|E| Section Length less than 0,[Target=%d,type=%d,uwStartAddr=0x%08x,uwEndAddr=0x%08x]"
#define STRING_CSDR_LOAD_ERROR_MSG 					"LOADER|E| Error code(cause)=0x%08x,extra data=%08x"

#define STRING_CSDR_LOAD_SECT_INFO 					"LOADER|I| Section index=%d,type=%d,uwLoadStartAddr=0x%08x,uwLoadEndAddr=0x%08x"
#define STRING_CSDR_LOAD_DMA_FAIL_INFO 				"LOADER|I| Dma fail,source=%d,target=%d,bufcnt=%d"
#define STRING_CSDR_LOAD_INFO 						"LOADER|I| Info data[0x%08x,0x%08x,0x%08x,0x%08x]"
#define STRING_CSDR_LOAD_SAVE_BSS_INFO 				"LOADER|I| Save bss ,from=0x%08x,to=0x%08x,len=0x%08x"
#define STRING_CSDR_LOAD_SAVE_DATA_INFO 			"LOADER|I| Save data,from=0x%08x,to=0x%08x,len=0x%08x"
#define STRING_CSDR_LOAD_LOAD_INFO 					"LOADER|I| Load [%d],from=0x%08x,to=0x%08x,len=0x%08x"
#define STRING_CSDR_LOAD_INFO_MSG 					"LOADER|I| Info data=0x%08x,extra data=%08x"
#define STRING_CSDR_LOAD_INITIALIZE_MSG 			"LOADER|I| Loader initialized,uwBinAddr=0x%08x,uwInitialized=0x%08x"

#endif
