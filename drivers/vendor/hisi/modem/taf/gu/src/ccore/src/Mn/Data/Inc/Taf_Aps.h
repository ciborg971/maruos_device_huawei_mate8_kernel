

#ifndef _TAF_APS_H_
#define _TAF_APS_H_


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "Taf_Common.h"
#include "ExtAppCmInterface.h"
#include "NasGmmInterface.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#endif
#include "TafSmInterface.h"

#include "NVIM_Interface.h"
#include "Taf_Tafm_Remote.h"
#include "Taf_Tafm_Local.h"



#include "Taf_ApsForSndcp.h"
#include "Taf_ApsForRabm.h"      /*�������Taf_ApsForSndcp.h����֮��*/
#include "Taf_ApsForTafm.h"
#include "TafApsApi.h"

#include "TafClientApi.h"

#include "AdsInterface.h"

/* Added by zhuli for K3V3VSIM��Ŀ, 2014-10-16, begin */
#include "siapppih.h"
/* Added by zhuli for K3V3VSIM��Ŀ, 2014-10-16, end */

/* Added by wx270776 for OM�ں�, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, end */

#if (FEATURE_ON == FEATURE_LTE)
#include "ApsL4aInterface.h"
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "cttf_1x_rlp_bo_pif.h"
#include "ehsm_aps_pif.h"

#endif

#include "xcc_taf_pif.h"
#include "hsm_aps_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#pragma pack(4)

/*****************************************************************************
  2 �궨��
  #define
*****************************************************************************/
/* Modified by y00314741 for  CDMA Iteration 17, 2015-7-17, begin */
#define TAF_APS_1X_PACKET_DATA_INACTIVITY_TIME_LEN          ( 5 )
/* Modified by y00314741 for  CDMA Iteration 17, 2015-7-17, end */

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-2, begin */
#define TAF_APS_EVDO_PACKET_DATA_INACTIVITY_TIME_LEN        ( 20 )
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-2, end */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                  for  TAFϵ                           */
/*=======================================================*/

#define APS_TFT_FILTER_AMOUNT           8

#define APS_MAX_LENGTH_OF_APN           101


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                  for APS base                         */
/*=======================================================*/

/*��������ֵ*/
/* Modified by y00314741 for CDMA Iteration 11, 2015-4-7, begin */
#ifndef TAF_APS_SUCC
#define TAF_APS_SUCC                 0
#endif

#ifndef TAF_APS_FAIL
#define TAF_APS_FAIL                    1
#endif
/* Modified by y00314741 for CDMA Iteration 11, 2015-4-7, end */

/* ����PDPID����ķ���ֵ */
#define TAF_APS_ALLOC_PDPID_SUCCESS     (0)
#define TAF_APS_ALLOC_PDPID_FAIL        (1)

/*�жϲ����Ƿ�Ϸ��ķ���ֵ*/
#define APS_PARA_VALID                  0
#define APS_PARA_INVALID                1
#define APS_PDPID_INVALID               2
#define APS_NSAPI_INVALID               3
#define APS_PDPTYPE_INVALID             4

#define APS_SAPI_VALID                  1
#define APS_SAPI_INVALID                0

#define APS_INFO_LOG(String)            TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_INFO, String)
#define APS_NORM_LOG(String)            TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_NORMAL, String)
#define APS_WARN_LOG(String)            TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_WARNING, String)
#define APS_ERR_LOG(String)             TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_ERROR, String)
#define APS_LOG1(String, Para1)         TAF_LOG1(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_NORMAL, String, Para1 )
#define APS_LOG2(String, Para1, Para2)  TAF_LOG2(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_NORMAL, String, Para1, Para2)

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, end */

#define APS_PDP_MIN_CID                 1
#define APS_PDP_RESELECT_CID            (12)
#define APS_PDP_MAX_CID                 (20)

#define  UPCASE( c ) ( (((c) >= 'a') && ((c) <= 'z')) ? ((c) - 0x20) : (c) )
/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, end */

#define APS_MT_DIFF_VALU                120

#define MN_APS_QOS_CSPS_MAX_UL_KBITRATE         (5760)
#define MN_APS_QOS_CSPS_MAX_DL_KBITRATE         (14400)

/*---------------------------------------------------------
    AT����ʱ��ͨ�����µ�QOS����ȷ��AT�����޷�����Ĳ�����ֵ
---------------------------------------------------------*/
/*QOS_TRAFFIC_CLASS*/
#define APS_QOS_TRAFFIC_CLASS_SUBSCRIBE             0
#define APS_QOS_TRAFFIC_CLASS_CONVERSATIONAL        1
#define APS_QOS_TRAFFIC_CLASS_STREAMING             2
#define APS_QOS_TRAFFIC_CLASS_INTERACTIVE           3
#define APS_QOS_TRAFFIC_CLASS_BACKGROUND            4

/*QOS_SDU_ERR_RATIO*/
#define APS_QOS_SDU_ERR_RATIO_SUBSCRIBE             0
#define APS_QOS_SDU_ERR_RATIO_1EM2                  1
#define APS_QOS_SDU_ERR_RATIO_7EM3                  2
#define APS_QOS_SDU_ERR_RATIO_1EM3                  3
#define APS_QOS_SDU_ERR_RATIO_1EM4                  4
#define APS_QOS_SDU_ERR_RATIO_1EM5                  5
#define APS_QOS_SDU_ERR_RATIO_1EM6                  6
#define APS_QOS_SDU_ERR_RATIO_1EM10                 7
#define APS_QOS_SDU_ERR_RATIO_RESERVED              15

/*QOS_TRAFFFIC_HANDLING_PRI*/
#define APS_QOS_TRAFFF_HANDL_PRIOR_SUBSCRIBE        0
#define APS_QOS_TRAFFF_HANDL_PRIOR_1                1
#define APS_QOS_TRAFFF_HANDL_PRIOR_2                2
#define APS_QOS_TRAFFF_HANDL_PRIOR_3                3

/*QOS_RESIDUAL_BER*/
#define APS_QOS_RESIDUAL_BER_1EM3                   5
#define APS_QOS_RESIDUAL_BER_1EM4                   6

/*�±���Щǩ��ֵ������AT����Ϊ��׼��ȡֵ��Ҳ��APP��Ϊ��ǩ��ȡֵ������3GPP
��������Ϊ��ǩ��ֵ*/
#define APS_APPQOS_TRAFFCLASS_SUBSCRIB              4
#define APS_APPQOS_DELIVERORDER_SUBSCRIB            2
#define APS_APPQOS_DELIVEReRRSDU_SUBSCRIB           3
#define APS_APPQOS_MAXSDUSIZE_SUBSCRIB              0
#define APS_APPQOS_MAXBITUL_SUBSCRIB                0
#define APS_APPQOS_MAXBITDL_SUBSCRIB                0
#define APS_APPQOS_RESIDUALBER_SUBSCRIB             0
#define APS_APPQOS_SDUERRRATIO_SUBSCRIB             0
#define APS_APPQOS_TRANSDELAY_SUBSCRIB              0
#define APS_APPQOS_TRAFFHANDPRIOR_SUBSCRIB          0
#define APS_APPQOS_GUARANTBITUL_SUBSCRIB            0
#define APS_APPQOS_GUARANTBITDL_SUBSCRIB            0
/* Added by w00316404 for M project A characeristic AT part, 2015-4-7, Begin */
#define APS_APPQOS_SRCSTATISTICSDES_SUBSCRIB        0
#define APS_APPQOS_SIGNALINDICATION_SUBSCRIB        0
/* Added by w00316404 for M project A characeristic AT part, 2015-4-7, End */



/*QOS_MAX_BITRATE*/
#define APS_QOS_MAX_BITRATE_SUBSCRIBE               0
#define APS_QOS_MAX_BITRATE_16KBPS                  16
#define APS_QOS_MAX_BITRATE_32KBPS                  32
#define APS_QOS_MAX_BITRATE_64KBPS                  64
#define APS_QOS_MAX_BITRATE_128KBPS                 72
#define APS_QOS_MAX_BITRATE_256KBPS                 88
#define APS_QOS_MAX_BITRATE_512KBPS                 120
#define APS_QOS_MAX_BITRATE_1024KBPS                135
#define APS_QOS_MAX_BITRATE_2048KBPS                151
#define APS_QOS_MAX_BITRATE_0KBPS                   255


/*===========================*/
/*3GPP�й涨��QOS�ĸ�������ֵ*/
/*TRAFFIC_CLASS*/
#define APS_3GPP_QOS_TRAFFIC_CLASS_SUBSCRIBE                0
#define APS_3GPP_QOS_TRAFFIC_CLASS_CONVERSATIONAL           1
#define APS_3GPP_QOS_TRAFFIC_CLASS_STREAMING                2
#define APS_3GPP_QOS_TRAFFIC_CLASS_INTERACTIVE              3
#define APS_3GPP_QOS_TRAFFIC_CLASS_BACKGROUND               4

#define APS_3GPP_QOS_DELAYCLASS_TOP                         4
#define APS_3GPP_QOS_DELAYCLASS_4                           4
#define APS_3GPP_QOS_DELAYCLASS_3                           3
#define APS_3GPP_QOS_DELAYCLASS_2                           2
#define APS_3GPP_QOS_DELAYCLASS_1                           1
#define APS_3GPP_QOS_DELAYCLASS_BOT                         0

#define APS_3GPP_QOS_RELIABCLASS_TOP                        5
#define APS_3GPP_QOS_RELIABCLASS_UNKGTPLLCRLC_UNPDATA       5
#define APS_3GPP_QOS_RELIABCLASS_UNKGTPLLCRLC_PRODATA       4
#define APS_3GPP_QOS_RELIABCLASS_UNKGTPLLC_ACKRLC_PRODATA   3
#define APS_3GPP_QOS_RELIABCLASS_UNKGTP_ACKLLCRLC_PRODATA   2
#define APS_3GPP_QOS_RELIABCLASS_ACKGTPLLCRLC_PRODATA       1
#define APS_3GPP_QOS_RELIABCLASS_BOT                        0

#define APS_3GPP_QOS_PEAKTHROUGH_TOP                        9
#define APS_3GPP_QOS_PEAKTHROUGH_1000_OCTPS                 1
#define APS_3GPP_QOS_PEAKTHROUGH_BOT                        0

#define APS_3GPP_QOS_PRECEDENCECLASS_TOP                    3
#define APS_3GPP_QOS_PRECEDENCECLASS_NORMPRI                2
#define APS_3GPP_QOS_PRECEDENCECLASS_BOT                    0

#define APS_3GPP_QOS_MEANTHROUGH_TOP                        18
#define APS_3GPP_QOS_MEANTHROUGH_BESTEFFORT                 31
#define APS_3GPP_QOS_MEANTHROUGH_BOT                        0

#define APS_3GPP_QOS_TRAFFICCLASS_TOP                       4
#define APS_3GPP_QOS_TRAFFICCLASS_BOT                       0

#define APS_3GPP_QOS_DELIVERORDER_TOP                       3
#define APS_3GPP_QOS_DELIVERORDER_SUB                       0
#define APS_3GPP_QOS_DELIVERORDER_BOT                       0

#define APS_3GPP_QOS_DELIVER_ERRSDU_TOP                     3
#define APS_3GPP_QOS_DELIVER_ERRSDU_SUB                     0
#define APS_3GPP_QOS_DELIVER_ERRSDU_BOT                     0

/*usMaxSduSize*/
#define APS_3GPP_QOS_MAXSDUSIZE_TOP                         153
#define APS_3GPP_QOS_MAXSDUSIZE_1520OCTS                    153     /*1520 octets*/
#define APS_3GPP_QOS_MAXSDUSIZE_1510OCTS                    152     /*1510 octets*/
#define APS_3GPP_QOS_MAXSDUSIZE_1502OCTS                    151     /*1502 octets*/
#define APS_3GPP_QOS_MAXSDUSIZE_BOT                         0
#define APS_3GPP_QOS_MAXSDUSIZE_SUB                         0
#define APS_3GPP_QOS_MAXSDUSIZE_GRANUL_10                   10      /*granularity of 10 octets*/

#define APS_3GPP_QOS_RESIDUALBER_TOP                        9
#define APS_3GPP_QOS_RESIDUALBER_BOT                        0

#define APS_3GPP_QOS_SDUERRRATIO_TOP                        7
#define APS_3GPP_QOS_SDUERRRATIO_BOT                        0

/*usTransDelay*/

#define APS_3GPP_QOS_TRANSDELAY_TOP                         63
#define APS_3GPP_QOS_TRANSDELAY_1000MS                      32
#define APS_3GPP_QOS_TRANSDELAY_200MS                       16
#define APS_3GPP_QOS_TRANSDELAY_BOT                         0
#define APS_3GPP_QOS_TRANSDELAY_INC_100MS                   100
#define APS_3GPP_QOS_TRANSDELAY_INC_50MS                    50
#define APS_3GPP_QOS_TRANSDELAY_INC_10MS                    10

#define APS_3GPP_QOS_TRAFFHANDLPRIOR_TOP                    3
#define APS_3GPP_QOS_TRAFFHANDLPRIOR_BOT                    0


/*  In MS to network direction:
        0 0 0 0 0 0 0 0 Subscribed maximum bit rate for uplink
                        In network to MS direction:
        0 0 0 0 0 0 0 0 Reserved
        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 1 The maximum bit rate is binary coded in 8 bits, using a granularity of 1 kbps
        0 0 1 1 1 1 1 1 giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

        0 1 0 0 0 0 0 0 The maximum bit rate is 64 kbps + ((the binary coded value in 8 bits -01000000) * 8 kbps)
        0 1 1 1 1 1 1 1 giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

        1 0 0 0 0 0 0 0 The maximum bit rate is 576 kbps + ((the binary coded value in 8 bits -10000000) * 64 kbps)
        1 1 1 1 1 1 1 0 giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

        1 1 1 1 1 1 1 1 0kbps
*/
/*usMaxBitUl*/
#define APS_3GPP_QOS_BIT_64KBPS                             64
#define APS_3GPP_QOS_BIT_576KBPS                            128
#define APS_3GPP_QOS_BIT_8640KBPS                           254
#define APS_3GPP_QOS_BIT_0KBPS                              255
#define APS_3GPP_QOS_BIT_INC_8KBPS                          8
#define APS_3GPP_QOS_BIT_INC_64KBPS                         64

/*R7�汾�У�Maximum bit rate for downlink (extended)������ȡֵ
  In MS to network direction and in network to MS direction:
  0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9.

                  For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9
                      and use the following value:
  0 0 0 0 0 0 0 1 The maximum bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
  0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps
                  to 16000 kbps in 100 kbps increments.

  0 1 0 0 1 0 1 1 The maximum bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
  1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

  1 0 1 1 1 0 1 1 The maximum bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
  1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.
*/
#define APS_3GPP_QOS_BIT_16000KBPS                          74
#define APS_3GPP_QOS_BIT_128MBPS                            186
#define APS_3GPP_QOS_BIT_256MBPS                            250

#define APS_3GPP_QOS_BIT_INC_100KBPS                        100
#define APS_3GPP_QOS_BIT_INC_1MBPS                          1000
#define APS_3GPP_QOS_BIT_INC_2MBPS                          2000


#define APS_3GPP_QOS_BIT_500MBPS                            61
#define APS_3GPP_QOS_BIT_1500MBPS                           161
#define APS_3GPP_QOS_BIT_10GBPS                             246

#define APS_3GPP_QOS_BIT_INC_4MBPS                          4000
#define APS_3GPP_QOS_BIT_INC_10MBPS                         10000
#define APS_3GPP_QOS_BIT_INC_100MBPS                        100000


#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
#define APS_3GPP_QOS_SSD_TOP                                15
#define APS_3GPP_QOS_SSD_BOT                                0

#define APS_3GPP_QOS_SIG_IND_TOP                            1
#define APS_3GPP_QOS_SIG_IND_BOT                            0

/* SRC STATISTICS DESCRIPTOR */
#define APS_QOS_SRC_STATS_DESCRIPTOR_UNKNOWN                (0)
#define APS_QOS_SRC_STATS_DESCRIPTOR_SPEECH                 (1)

/* QOS_SIGNAL_IND */
#define APS_QOS_SIGNAL_IND_NOT_OPTIMISE                     (0)
#define APS_QOS_SIGNAL_IND_OPTIMISE                         (1)


/* 1.Ϊ�˹��PCCW���������õ�Maximum bit rate for downlink (extended)����R6�汾��֧�ֵ�74�����⣬
     ���Ըò����ļ�鷶Χ�ſ�R7�汾��250;
   2.Ϊ�˱���Guaranteed bit rate for downlink (extended)����Ҳ��ͬ�����⣬Ҳ���Ըò����ļ��
     ��Χ�ſ�R7�汾��250*/
#define APS_3GPP_MAX_BITRATE_DOWN_TOP                       250
#define APS_3GPP_MAX_BITRATE_DOWN_BOT                       0

#define APS_3GPP_GUARANT_BITRATE_DOWN_TOP                   250
#define APS_3GPP_GUARANT_BITRATE_DOWN_BOT                   0
#endif

/* R7Э����������չ��max bitrate uplink(extended) �� Guaranteed bit rate for uplink (extended)*/
#if(PS_UE_REL_VER >= PS_PTL_VER_R7)
#define APS_3GPP_MAX_BITRATE_UP_TOP                       250
#define APS_3GPP_MAX_BITRATE_UP_BOT                       0

#define APS_3GPP_GUARANT_BITRATE_UP_TOP                   250
#define APS_3GPP_GUARANT_BITRATE_UP_BOT                   0
#endif

/*===========================*/
/*APP/AT�й涨��QOS�ĸ�������ֵ*/
/*usMaxSduSize*/
#define APS_APP_QOS_MAXSDUSIZE_1520OCTS                     1520    /*1520 octets*/
#define APS_APP_QOS_MAXSDUSIZE_1510OCTS                     1510    /*1510 octets*/
#define APS_APP_QOS_MAXSDUSIZE_1502OCTS                     1502    /*1502 octets*/
#define APS_APP_QOS_MAXSDUSIZE_1500OCTS                     1500    /*1500 octets*/

/*usMaxBitUl*/
#define APS_APP_QOS_BIT_64KBPS                              64
#define APS_APP_QOS_BIT_576KBPS                             576
#define APS_APP_QOS_BIT_8640KBPS                            8640
#define APS_APP_QOS_BIT_8600KBPS                            8600
#define APS_APP_QOS_BIT_16MBPS                              16000
#define APS_APP_QOS_BIT_128MBPS                             128000
#define APS_APP_QOS_BIT_256MBPS                             256000
#define APS_APP_QOS_BIT_500MBPS                             500000
#define APS_APP_QOS_BIT_1500MBPS                            1500000
#define APS_APP_QOS_BIT_10GBPS                              10000000
#define APS_APP_QOS_BIT_0KBPS                               0

/*usTransDelay*/
#define APS_APP_QOS_TRANSDELAY_1000MS                       1000
#define APS_APP_QOS_TRANSDELAY_200MS                        200

/*ucTrafficClass*/
#define APS_TRAFFICCLASS_APP3GPP_DIFF_VAL                   1

/*ucDeliverOrder*/
#define APS_DELIVERORDER_APP3GPP_DIFF_VAL                   2

/*ucDeliverOfErrSdu*/
#define APS_DELIVEROFERRSDU_APP3GPP_DIFF_VAL                3


/*AT�й涨��QOS�ĸ������ı߽�ֵ,��APP����ķ�Χ*/
#define APS_APP_QOS_DELAYCLASS_TOP                          4
#define APS_APP_QOS_DELAYCLASS_BOT                          0

#define APS_APP_QOS_RELIABCLASS_TOP                         5
#define APS_APP_QOS_RELIABCLASS_BOT                         0

#define APS_APP_QOS_PEAKTHROUGH_TOP                         9
#define APS_APP_QOS_PEAKTHROUGH_BOT                         0

#define APS_APP_QOS_PRECEDENCECLASS_TOP                     3
#define APS_APP_QOS_PRECEDENCECLASS_BOT                     0

#define APS_APP_QOS_MEANTHROUGH_TOP                         18
#define APS_APP_QOS_MEANTHROUGH_BOT                         0

#define APS_APP_QOS_TRAFFICCLASS_TOP                        4
#define APS_APP_QOS_TRAFFICCLASS_BOT                        0

#define APS_APP_QOS_DELIVERORDER_TOP                        2
#define APS_APP_QOS_DELIVERORDER_BOT                        0

#define APS_APP_QOS_DELIVER_ERRSDU_TOP                      3
#define APS_APP_QOS_DELIVER_ERRSDU_BOT                      0

#define APS_APP_QOS_MAXSDUSIZE_TOP                          1520
#define APS_APP_QOS_MAXSDUSIZE_BOT                          0

#define APS_APP_QOS_RESIDUALBER_TOP                         9
#define APS_APP_QOS_RESIDUALBER_BOT                         0

#define APS_APP_QOS_SDUERRRATIO_TOP                         7
#define APS_APP_QOS_SDUERRRATIO_BOT                         0

#define APS_APP_QOS_TRANSDELAY_TOP                          62
#define APS_APP_QOS_TRANSDELAY_BOT                          0

#define APS_APP_QOS_TRAFFHANDLPRIOR_TOP                     3
#define APS_APP_QOS_TRAFFHANDLPRIOR_BOT                     0


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                  for APS ����--APS�����              */
/*=======================================================*/
#define APS_NSAPI_MIN                   5

#ifndef APS_NSAPI_MAX
#define APS_NSAPI_MAX                   15
#endif

#define APS_FREE_ENTITY_NUM             7
#define APS_MIDDLE_TI                   7

#ifndef APS_MAX_PDP_NUM
#define APS_MAX_PDP_NUM                 11
#endif

/*VOS_UINT8     ucSNDCPActOrNot*/
#define APS_SNDCP_INACT                 0
#define APS_SNDCP_ACT                   1

/*VOS_UINT8     ucTeardown*/
#define APS_DEACT_NOTEARDOWN            0
#define APS_DEACT_TEARDOWN              1
#define APS_DEACT_BE_TEARDOWNED         2
#define APS_TEARDOWN_INVALID            255

/*VOS_UINT8     ucHowToInitAct*/
#define APS_APP_INIT_ACT                0                   /* APP�������𼤻� */
#define APS_APP_MANUL_ACT               1                   /*APP�ֶ�Ӧ���𼤻�*/
#define APS_TAF_AUTO_INIT_ACT           2                   /*APS�Զ�Ӧ���𼤻�*/
#define APS_SYSCHNG_ACT_SN              3                   /*3G��2G�л���APS�Զ�����SN*/
/*VOS_UINT8     ucHowToInitDeAct*/
#define APS_APP_INIT_DEACT              1
#define APS_APS_AUTO_INIT_DEACT         2
#define APS_NET_INIT_DEACT              3
#define APS_DEACT_DURING_ACTING         4

#define APS_PRI_ACT                     1                   /*���з�������緢��ļ���Ϊ������*/
#define APS_SEC_ACT                     2                   /*���з�������緢��ļ���Ϊ���μ���*/

#define APS_PPP_CODE_REQ                1
#define APS_PPP_CODE_ACK                2
#define APS_PPP_CODE_NAK                3
#define APS_PPP_CODE_REJ                4

#define APS_PPP_IP_ADDR_ID              0x03
#define APS_PPP_PRI_DNS_ID              0x81
#define APS_PPP_PRI_NBNS_ID             0x82
#define APS_PPP_SEC_DNS_ID              0x83
#define APS_PPP_SEC_NBNS_ID             0x84

#define APS_SYS_REL                     1

/*PCO���ֽ���ת���ĺ�*/
#ifndef VOS_NTOHL
#if VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define VOS_NTOHL(x)    (x)
#define VOS_HTONL(x)    (x)
#define VOS_NTOHS(x)    (x)
#define VOS_HTONS(x)    (x)
#else
#define VOS_NTOHL(x)    ((((x) & 0x000000ff) << 24) | \
                         (((x) & 0x0000ff00) <<  8) | \
                         (((x) & 0x00ff0000) >>  8) | \
                         (((x) & 0xff000000) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ff) << 24) | \
                         (((x) & 0x0000ff00) <<  8) | \
                         (((x) & 0x00ff0000) >>  8) | \
                         (((x) & 0xff000000) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
                         (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
                         (((x) & 0xff00) >> 8))

#endif  /* _BYTE_ORDER==_LITTLE_ENDIAN */

#endif

#define APS_EVT_PCO_SET_0(pEvtPPP)\
                        *pEvtPPP++     = 0x00;             /*AUTH�ĳ���2�ֽ���0*/\
                        *pEvtPPP++     = 0x00;                                   \
                        *pEvtPPP++     = 0x00;             /*IPCP�ĳ���2�ֽ���0*/\
                        *pEvtPPP++     = 0x00;


/*----------------------QOS���--------------------------*/
#define APS_SAPI_INIT                   3                   /*���𼤻�ʱ�����緢�͵�SAPI�������ȫ��Ϊ3*/
#define APS_SAPI_3                      3
#define APS_SAPI_5                      5
#define APS_SAPI_9                      9
#define APS_SAPI_11                     11


/*Refer to 24.008 10.5.7.2*/
#define APS_RADIOPRI_1                  1                   /*riority level 1 (highest)*/
#define APS_RADIOPRI_2                  2                   /*riority level 2          */
#define APS_RADIOPRI_3                  3                   /*riority level 3          */
#define APS_RADIOPRI_4                  4                   /*riority level 4 (lowest) */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, end */

#define APS_QOS_UP_TO_MIN               0                   /* ����MINQOS Ҫ�� */
#define APS_QOS_NOT_UP_TO_MIN           1                   /* ������MINQOS Ҫ�� */

/*7����Ĵ�SDU�����*/
#define SDU_ERR_RATIO_HIGHEST           7

/*----------------------TFT���--------------------------*/
#define APS_PACK_FLOW_ID_BIGGEST        127

#define APS_TFT_FILTERID_BOTTOM         0
#define APS_TFT_FILTERID_TOP            7

/*----------------------PCO���--------------------------*/
/*PAP��֤����ʱConfiguration protocol+ PROTOCAL ID +
PROTOCAL ID1 LEN = 3*/
#define APS_PAP_HEADER_LEN              4
#define APS_PAP_PIDOCTS_AND_LENOCT_LEN  3

#define APS_ADDR_DYNAMIC_IPV4           (0)
#define APS_ADDR_STATIC_IPV4            (1)
#define APS_ADDR_PPP                    (2)

#define MN_APS_ADDR_IPV6                (3)
#define MN_APS_ADDR_IPV4V6              (4)

#define APS_ADDR_ORGAN_IETF             1
#define APS_ADDR_ORGAN_ETSI             0
#define APS_ADDR_ORGAN_EMPTY_PDP_TYPE   15                  /*Empty PDP type*/

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, end */

#if (FEATURE_ON == FEATURE_IPV6)
#define MN_APS_SET_EVT_SM_CAUSE(PsAppEvt, ucPdpId)                              \
{                                                                               \
    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpCause)                            \
    {                                                                           \
        PsAppEvt->bitOpCause     = VOS_TRUE;                                     \
        PsAppEvt->enCause        = g_PdpEntity[ucPdpId].enCause;                 \
    }                                                                           \
}
#endif

#if 0
#define APS_NETDNS_2_STRDNS(StrDns, NetDns)                                     \
            StrDns.OP_Spare = VOS_FALSE;                                         \
            if ( VOS_TRUE == NetDns.OP_PriDns)                                  \
            {                                                                   \
                StrDns.OP_PriDns    = VOS_TRUE;                                 \
                Taf_Dns2Str( NetDns.aucPriDns, StrDns.aucPriDns );              \
            }                                                                   \
            else                                                                \
            {                                                                   \
                StrDns.OP_PriDns    = VOS_FALSE;                                 \
            }                                                                   \
            if ( VOS_TRUE == NetDns.OP_SecDns)                                  \
            {                                                                   \
                StrDns.OP_SecDns    = VOS_TRUE;                                 \
                Taf_Dns2Str( NetDns.aucSecDns, StrDns.aucSecDns );              \
            }                                                                   \
            else                                                                \
            {                                                                   \
                StrDns.OP_SecDns    = VOS_FALSE;                                 \
            }/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#endif

#define APS_SET_PDPENTITY_TEATDOWN(ucPdpId, ucTeardownPara)                             \
            g_PdpEntity[ucPdpId].PdpProcTrack.ucTeardown = ucTeardownPara;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                  for SM ��Ϣ                          */
/*=======================================================*/
#define APS_ADDR_SAME                               0
#define APS_ADDR_DIFF                               1

#define APS_APN_SAME                                0
#define APS_APN_DIFF                                1

#define APS_PDP_TYPE_NUM_IPV4                       (0x21)
#define APS_PDP_TYPE_NUM_PPP                        (0x01)
#define MN_APS_PDP_TYPE_NUM_IPV6                    (0x57)
#define MN_APS_PDP_TYPE_NUM_IPV4V6                  (0x8D)

#if (FEATURE_ON == FEATURE_IPV6)
#define MN_APS_IPV6_STR_MAX_TOKENS                  (16)    /* IPV6�ַ�����ʽʹ�õķָ������������ */

#define MN_APS_IPV4_STR_DELIMITER                   '.'     /* RFCЭ��ʹ�õ�IPV4�ı���﷽ʽʹ�õķָ��� */
#define MN_APS_IPV6_STR_DELIMITER                   ':'     /* RFC2373ʹ�õ�IPV6�ı���﷽ʽʹ�õķָ��� */
#endif


/*�����±���Щ����ȡ��SM�ϴ��������������еĸ�����ֵ��*/
#define APS_QOS_DELAY_CLASS                         0x38    /* 0011 1000*/
#define APS_QOS_RELIABILITY_CLASS                   0x07    /* 0000 0111*/
#define APS_QOS_PEAK_THROUGHPUT                     0xF0    /* 1111 0000*/
#define APS_QOS_PRECEDENCE_CLASS                    0x07    /* 0000 0111*/
#define APS_QOS_MEAN_THROUGHPUT                     0x1F    /* 0001 1111*/
#define APS_QOS_TRAFFIC_CLASS                       0xE0    /* 1110 0000*/
#define APS_QOS_DELIVERY_ORDER                      0x18    /* 0001 1000*/
#define APS_QOS_DELIVERY_ERRORNEOUS_SDU             0x07    /* 0000 0111*/
#define APS_QOS_RESIDUAL_BER                        0xF0    /* 1111 0000*/
#define APS_QOS_SDU_ERROR_RATIO                     0x0F    /* 0000 1111*/
#define APS_QOS_TRANSFER_DELAY                      0Xfc    /* 1111 1100*/
#define APS_QOS_TRAFFIC_HANDLING_PRIORITY           0x03    /* 0000 0011*/
#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
#define APS_QOS_SSD                                 0x0F    /* 0000 1111*/
#define APS_QOS_SIGNALLING_INDICATION               0x10    /* 0001 0000*/
#endif
/*----------------------------------------------------------
        TFT��ר��
----------------------------------------------------------*/
#define APS_TFT_CREAT_TFT                           0x20    /* 0010 0000*/

#define APS_TFT_REPLACE_TFT                         0x80    /* 1000 0000*/

#define APS_TFT_ONE_FILTER                          0x01
#define APS_TFT_IPV4_ADDR                           0x10
#define APS_TFT_PROTOCAL_ID                         0x30    /* 0011 0000*/
#define APS_TFT_DEST_PORT_RANG                      0x41    /* 0100 0001*/
#define APS_TFT_SOURCE_PORT_RANG                    0x51    /* 0101 0001*/
#define APS_TFT_SPI                                 0x60    /* 0110 0000 Security parameter index type*/
#define APS_TFT_TOS                                 0x70    /* 0111 0000 Type of service/Traffic class type*/
#define APS_TFT_FLOW_LABLE                          0x80    /* 1000 0000 Flow label type*/

/*��UINT16��������ֽ�������ȥʱ��Ҫ�ȷ��͵�λ�ֽ�*/
#define APS_UINT16_LOW_LOCATION_OCTET               0x00FF
#define APS_UINT16_HIGH_LOCATION_OCTET              0xFF00

#define APS_UINT32_RESERV_32_TO_25_OCTET            0xFF000000
#define APS_UINT32_RESERV_24_TO_17_OCTET            0x00FF0000
#define APS_UINT32_RESERV_16_TO_8_OCTET             0x0000FF00
#define APS_UINT32_RESERV_7_TO_0_OCTET              0x000000FF

/*TFT��filter1��length����SM�����е�λ��Ϊ3 */
#define APS_TFT_FILTER1_LENGTH_LOCATION             3

/*TFT��filter1��component����SM�����еĿ�ʼλ��Ϊ4 */
#define APS_TFT_FILTER1_COMPONENT_BEGIN             4

/*filter1�� Operation Code + filter ID+ Precedence + length
��4������ֽ���Ϊ4*/
#define APS_TFT_FILTER1_OP_ID_PRE_LEN_AMOUNT        4

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                  for SNDCP��Ϣ                        */
/*=======================================================*/
/*���ļ�Taf_ApsForSndcp.h*/
#define APS_MSGTYPELEN_PIDLEN                       4

#define APS_PACK_SN_MSG_HEADER(Msg,ApsSnIndMsg)\
                                        Msg.ulSenderCpuId   = VOS_LOCAL_CPUID;  \
                                        Msg.ulSenderPid     = WUEPS_PID_TAF;    \
                                        Msg.ulReceiverCpuId = VOS_LOCAL_CPUID;  \
                                        Msg.ulReceiverPid   = UEPS_PID_SN;      \
                                        Msg.ulLength        = sizeof(ApsSnIndMsg)\
                                                              + APS_MSGTYPELEN_PIDLEN;

#define APS_SN_P_CMP_VALID(ucPCmp)      (ucPCmp <= SN_ROHC_ALGRTH)
#define APS_SN_H_CMP_VALID(ucDCmp)      (ucDCmp <= SN_V44_ALGRTH)

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, end */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                  for APS ��������                     */
/*=======================================================*/
typedef VOS_VOID (*RABM_MSG_FUN_TYPE)( VOS_UINT8  ucPdpID);

/*TAF_PDP_TABLE_STRU�б��������Ƿ���Ч�ĺ�*/
#define APS_PDP_TABLE_PARA_INVALID                  0
#define APS_PDP_TABLE_PARA_VALID                    1

typedef VOS_UINT8   APS_NVIM_ACT_TYPE;
#define APS_NVIM_ADD                                0
#define APS_NVIM_CHNG                               1
#define APS_NVIM_DELETE                             2

/*****************************************************************************
  Maximum length of challenge used in authentication. The maximum length
  challenge name is the same as challenge.
*****************************************************************************/
#define TAF_APS_PPP_CHAP_CHALLNGE_LEN       (16)

/*****************************************************************************
  Maximum length of challenge name used in authentication.
*****************************************************************************/
#define TAF_APS_PPP_CHAP_CHALLNGE_NAME_LEN  (16)

/*****************************************************************************
  Maximum length of response used in authentication.
*****************************************************************************/
#define TAF_APS_PPP_CHAP_RESPONSE_LEN   (16)

/***************************************************************
AUTH_PAP (RFC 1334)
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     Code      |  Identifier   |            Length             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Peer-ID Length|  Peer-Id ...
+-+-+-+-+-+-+-+-+-+-+-+-+
| Passwd-Length |  Password ...
+-+-+-+-+-+-+-+-+-+-+-+-+-+
****************************************************************/
/* code(1B)+id(1B)+length(2B)+username_size(1B)+username+password_size(1B)+password */
#define TAF_APS_PPP_PAP_CODE_LEN                    1

#define TAF_APS_PPP_PAP_HEAD_OFFSET                 4

/* code(1B)+id(1B)+length(2B)+challenge_size(1B)+challenge+name */
/* code(1B)+id(1B)+length(2B)+response_size(1B)+response+name */
#define TAF_APS_PPP_CHAP_CODE_LEN                   1
#define TAF_APS_PPP_CHAP_ID_LEN                     1
#define TAF_APS_PPP_CHAP_LEN                        2
#define TAF_APS_PPP_CHAP_CHALLENGE_SIZE             1
#define TAF_APS_PPP_CHAP_RESPONSE_SIZE              1

#define TAF_APS_PPP_CHAP_HEAD_OFFSET                (TAF_APS_PPP_CHAP_CODE_LEN + TAF_APS_PPP_CHAP_ID_LEN + TAF_APS_PPP_CHAP_LEN)

#define TAF_APS_PPP_CHAP_CHALLENGE_HEAD_OFFSET      (TAF_APS_PPP_CHAP_HEAD_OFFSET + TAF_APS_PPP_CHAP_CHALLENGE_SIZE)
#define TAF_APS_PPP_CHAP_RESPONSE_HEAD_OFFSET       (TAF_APS_PPP_CHAP_HEAD_OFFSET + TAF_APS_PPP_CHAP_RESPONSE_SIZE)

/*--------------------------------------------------------------
   IPCP OPTION���ȱ������6
   OPTION TYPE(1 byte) + OPTION LEN(1 btye) + VALUE(4 bytes)
--------------------------------------------------------------*/
#define TAF_APS_PPP_IPCP_OPTION_TYPE_LEN            1
#define TAF_APS_PPP_IPCP_OPTION_LEN                 1

#define TAF_APS_PPP_IPCP_OPTION_HEAD_LEN            (TAF_APS_PPP_IPCP_OPTION_TYPE_LEN + TAF_APS_PPP_IPCP_OPTION_LEN)

/*~~~~~~~~~~~~~~~~~~~~~~~~PDP_PRI����������Ҫ�õĺ� ~~~~~~~~~~~~~~~~~~~~~~~~*/
#define APS_PDPPRI_DELETE(pPdpPara) ((0 == pPdpPara->bitOpApn)        \
                                 &&  (0 == pPdpPara->bitOpPdpAddr)    \
                                 &&  (0 == pPdpPara->bitOpPdpType)    \
                                 &&  (0 == pPdpPara->bitOpPdpDcomp)   \
                                 &&  (0 == pPdpPara->bitOpPdpHcomp))

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-7, end */

/*~~~~~~~~~~~~~~~~~~~~~~~~NVIM������Ҫ�õĺ�  ~~~~~~~~~~~~~~~~~~~~~~~~*/
#define APS_NVIM_DELETE_ITEM(ucCid)    ((0 == g_TafCidTab[ucCid].ucUsed)        \
                                    &&  (0 == g_TafCidTab[ucCid].ucEpsQosInfoFlg)  \
                                    &&  (0 == g_TafCidTab[ucCid].ucQosTabFlag)  \
                                    &&  (0 == g_TafCidTab[ucCid].ucMinQosFlag)  \
                                    &&  (0 == g_TafCidTab[ucCid].ucPfTabFlag)  \
                                    &&  (0 == g_TafCidTab[ucCid].ucAuthFlag)    \
                                    &&  (0 == g_TafCidTab[ucCid].ucDnsFlag)     \
                                    &&  (0 == g_TafCidTab[ucCid].ucPriCidFlag))

#define APS_NVIM_UPDATE_ITEM           ((1 == g_TmpPdpTab.ucUsed)        \
                                    ||  (1 == g_TmpPdpTab.ucEpsQosInfoFlg)  \
                                    ||  (1 == g_TmpPdpTab.ucQosTabFlag)  \
                                    ||  (1 == g_TmpPdpTab.ucMinQosFlag)  \
                                    ||  (1 == g_TmpPdpTab.ucPfTabFlag)  \
                                    ||  (1 == g_TmpPdpTab.ucAuthFlag)    \
                                    ||  (1 == g_TmpPdpTab.ucDnsFlag)     \
                                    ||  (1 == g_TmpPdpTab.ucPriCidFlag))

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS ����                        */
/*=======================================================*/
/*�ж�SAPI�Ƿ�����Ч��Χ�ĺ�,�������Ч��Χ,��ú�Ϊ 1*/

#define APS_JUDGE_SAPI_VALID(ucSapi) Aps_JudgeSapiValid(ucSapi)

/*�ж�RadioPriority�Ƿ�����Ч��Χ�ĺ�,�������Ч��Χ,��ú�Ϊ 1*/
#define APS_JUDGE_RADIOPRI_VALID(ucRadioPri)                                    \
                                       ((APS_RADIOPRI_1         == ucRadioPri)  \
                                    ||  (APS_RADIOPRI_2         == ucRadioPri)  \
                                    ||  (APS_RADIOPRI_3         == ucRadioPri)  \
                                    ||  (APS_RADIOPRI_4         == ucRadioPri))

/*�ж�ucTearDown�Ƿ�����Ч��Χ�ĺ�,�������Ч��Χ,��ú�Ϊ 1*/
#define APS_JUDEG_TEARDOWN_VALID(ucTearDown)                                    \
                                       ((TAF_PDP_TEAR_DOWN      == ucTearDown)  \
                                    ||  (TAF_PDP_NOT_TEAR_DOWN  == ucTearDown))

/*�ж�NSAPI�Ƿ�����Ч��Χ�ĺ�,�������Ч��Χ,��ú�Ϊ 1*/
#define APS_JUDGE_NSAPI_VALID(ucNsapi) ((APS_NSAPI_MIN          <= ucNsapi)     \
                                    &&  (APS_NSAPI_MAX          >= ucNsapi))

/*�ж�PDPID�Ƿ�����Ч��Χ�ĺ�,�������Ч��Χ,��ú�Ϊ 1*/
#define APS_JUDEG_PDPID_VALID(ucPdpId) ((TAF_APS_MAX_PDPID      >  ucPdpId)     \
                                    &&  (APS_FREE_ENTITY_NUM    != ucPdpId))

#define APS_MEM_FREE(pBuffer)   VOS_MemFree(WUEPS_PID_TAF, (pBuffer))

#define APS_MEM_SET(pBuffer, chDstChar, ulCount)   VOS_MemSet((pBuffer), (chDstChar), (ulCount))

#define TAF_APS_R7_SUPP_UL16QAM_OR_DCUPA(ue_revision, stUECapa)   (((ue_revision) >= PS_PTL_VER_R7)\
                    &&( ((PS_TRUE == stUECapa.enSuppUl16QAM) && (7 == stUECapa.ucEDCHPhyCategoryExt))\
                      ||((PS_TRUE == stUECapa.enDcUpaSupport) && (9 == stUECapa.ucEDCHPhyCategoryExt2))))

#define TAF_APS_MAX_PDPID               (11)

#define TAF_CID_NUMS_VALID              (1)
#define TAF_CID_NUMS_INVALID            (0)

#define TAF_MAX_IPV4_ADDR_LEN           (15)

/*���û�ж��壬˵���κ�Qos����APP���ܽ���*/
#define  TAF_PDP_MIN_QOS_DEFINED        (0)
#define  TAF_PDP_MIN_QOS_NOT_DEFINED    (1)

#define TAF_PPP_CODE_REQ                (1)
#define TAF_PPP_CODE_ACK                (2)
#define TAF_PPP_DEF_ID                  (1)

#define TAF_AP_PPP_CHAP_CHALLENGE_LEN   (16)
#define TAF_AP_PPP_CHAP_RESPONSE_LEN    (16)

#define TAF_AP_PPP_CODE_CHALLENGE       (1)
#define TAF_AP_PPP_CODE_RESPONSE        (2)

typedef TAF_UINT8 TAF_PCO_AUTH_TYPE;
#define TAF_PCO_NOT_AUTH                (0)                                     /*PDP����ʱ��PCO�в���Ҫ��д��Ȩ��Ϣ*/
#define TAF_PCO_AUTH_PAP                (1)                                     /*PDP����ʱ��PCO��Ҫ��дPAP��ʽ�ļ�Ȩ��Ϣ*/
#define TAF_PCO_AUTH_CHAP               (2)                                     /*PDP����ʱ��PCO��Ҫ��дCHAP��ʽ�ļ�Ȩ��Ϣ*/

#define TAF_PCO_AUTH_CHAP_RESPONSE_HEAD_LEN     (21)                            /*PDP����ʱ��PCO��Ȩ��ʽΪCHAPʱ��RESPONSE��ͷ�̶�Ϊ21���ַ�*/
#define TAF_PCO_AUTH_CHAP_RESPONSE_CONTENT_LEN  (106)                           /*PDP����ʱ��PCO��Ȩ��ʽΪCHAPʱ��RESPONSE�������Ϊ106���ַ�������һ��*/

#define TAF_PCO_CONTENT_MAX_LEN         (255)                                   /*PCO�е�ÿ��content�ĳ��ȶ�����һ�ֽڵ�length�ֶξ����ģ����Ϊ255���ֽ�*/



#define TAF_APS_CFG_EVT_CTRL_HDR(pstCtrlHdr, ModuleId, ClientId, OpId)\
            (pstCtrlHdr)->ulModuleId = WUEPS_PID_AT;\
            (pstCtrlHdr)->usClientId = ClientId;\
            (pstCtrlHdr)->ucOpId = OpId

#define TAF_APS_CFG_AT_EVT_CTRL_HDR(pstCtrlHdr, ClientId, OpId)\
            TAF_APS_CFG_EVT_CTRL_HDR(pstCtrlHdr, WUEPS_PID_AT, ClientId, OpId)

#define TAF_APS_INVALID_MODULEID                            (WUEPS_PID_AT)

#define TAF_APS_GET_MODULEID_FORM_CTRL_HDR(pstCtrl)         ((pstCtrl)->ulModuleId)
#define TAF_APS_GET_CLIENTID_FORM_CTRL_HDR(pstCtrl)         ((pstCtrl)->usClientId)

/*ʹ��PPP���ţ�������������Ҫʹ��AT�����޸�QOS��
  Ŀǰ����ʽ�������ǲ��������������ģ���Ϊ��������Բ�
  ��ĳЩ��������Ĳ���������Ҫ��׮ʵ�ָ�����
  ��������������Ҳ��Ҫʹ�øó�Ա */

typedef TAF_CTRL_STRU   TAF_APS_PDP_MOD_DIAL_STRU;

#define TAF_APS_DEFAULT_CDATA_RAB_ID       (5)

#define TAF_APS_DEFAULT_CDATA_PDN_ID       (1)

#define TAF_MAX_CALLID                  (11)
#define TAF_MIN_CALLID                  (1)


/*****************************************************************************
 �ṹ����   : MN_APS_IPV6_STR_TYPE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IPV6 String��ʽö��
              HEXΪRFC2373Ҫ��ʹ��':'��Ϊ�ָ���
              DEXΪRFCҪ��ʹ��'.'��Ϊ�ָ���
*****************************************************************************/
enum TAF_APS_ORIG_TYPE_ENUM
{
    TAF_APS_ORIG_TYPE_PS_CALL            = 0,
    TAF_APS_ORIG_TYPE_PPP_DIAL           = 1,

    TAF_APS_DIAL_TYPE_BUTT
};
typedef VOS_UINT8 TAF_APS_ORIG_TYPE_ENUM_UINT8;


typedef struct
{
    VOS_UINT8                           ucUsed;                                 /*0��δʹ�ã�1��ʹ��*/
    VOS_UINT8                           ucCid;                                  /*Cidȡֵ*/
    VOS_UINT8                           ucPriCidFlag;                           /*0: ucPriCid��Ч,��PDPΪ��PDP; 1: ucPriCid��Ч,��PDPΪ����PDP*/
    VOS_UINT8                           ucPriCid;                               /*ָ����PDP������*/
    TAF_PDP_PRIM_CONTEXT_STRU           CidTab;                                 /*Cid��*/

    VOS_UINT8                           ucEpsQosInfoFlg;                        /*0��EQos����Ч��1��EQos����Ч*/
    VOS_UINT8                           aucRsv1[3];
    TAF_EPS_QOS_STRU                    stEpsQosInfo;                           /*EQos������*/

    VOS_UINT8                           ucQosTabFlag;                           /*0��Qos����Ч��1��Qos����Ч*/
    VOS_UINT8                           aucRsv2[3];
    TAF_UMTS_QOS_STRU                   QosTab;                                 /*Qos��*/

    VOS_UINT8                           ucMinQosFlag;                           /*0:��������С�ɽ���Qos,1:û����С�ɽ���Qos*/
    VOS_UINT8                           aucRsv3[3];
    TAF_UMTS_QOS_STRU                   MinQosTab;                              /*MINQos��*/

    VOS_UINT8                           ucPfTabFlag;                            /*0��pf����Ч��1��pf����Ч*/
    VOS_UINT8                           aucRsv4[2];
    VOS_UINT8                           ucPfNum;                                /* pf���� */
    TAF_PDP_PF_STRU                     astPfTab[TAF_MAX_SDF_PF_NUM];           /* pf�� */

    VOS_UINT8                           ucAuthFlag;                             /*0��Auth����Ч��1��Auth����Ч*/
    VOS_UINT8                           aucRsv5[3];
    TAF_PDP_AUTH_STRU                   AuthTab;                                /*��Ȩ������*/

    VOS_UINT8                           ucDnsFlag;                              /*0��DNS����Ч��1��DNS����Ч*/
    VOS_UINT8                           aucRsv6[3];
    TAF_PDP_DNS_STRU                    DnsTab;                                 /*DNS��*/

    VOS_UINT16                          usNvFlag;                               /*��CID����Ӧ��NV Table�����Ƿ����ù�: 0-δ����,1-������*/
    VOS_UINT8                           aucRsv7[26];                            /* �����24�������ֽڣ�Ŀ����Ϊ�˺�NV����� */

}TAF_PDP_TABLE_STRU;

/*****************************************************************************
 �ṹ����: TAF_NV_PDP_PRIM_CONTEXT_STRU
 �ṹ˵��: Primary PDP�����Ľṹ(NV)
*****************************************************************************/
typedef struct
{
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;                              /*PDP����*/
    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    VOS_UINT8                           aucReserved[1];
    TAF_PDP_APN_STRU                    stApn;
    VOS_UINT8                           aucPdpAddr[TAF_MAX_IPV4_ADDR_STR_LEN];          /*PDP IPv4��ַ*/
    TAF_PDP_D_COMP_ENUM_UINT8           enPdpDcomp;
    TAF_PDP_H_COMP_ENUM_UINT8           enPdpHcomp;

    /* 0 - IPv4 Address Allocation through NAS Signaling (default if omitted)
       1 - IPv4 Address Allocated through DHCP */
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAlloc;

    /* 0 - PDP context is not for emergency bearer services
       1 - PDP context is for emergency bearer services */
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
} TAF_NV_PDP_PRIM_CONTEXT_STRU;

/*****************************************************************************
 �ṹ����: TAF_NV_PDP_DNS_STRU
 �ṹ˵��: IPv4 DNS��ַ�ṹ(NV)
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimDnsAddr    : 1;
    VOS_UINT32                          bitOpSecDnsAddr     : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimDnsStr[TAF_MAX_IPV4_ADDR_STR_LEN];
    VOS_UINT8                           aucSecDnsStr[TAF_MAX_IPV4_ADDR_STR_LEN];
} TAF_NV_PDP_DNS_STRU;

/*****************************************************************************
 �ṹ����: TAF_NV_PDP_TABLE_STRU
 �ṹ˵��: PDP�ṹ�����ڱ���PDP�������Ĳ�����Ϣ����NV���Ľṹһ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsed;                                 /*0��δʹ�ã�1��ʹ��*/
    VOS_UINT8                           ucCid;                                  /*Cidȡֵ*/
    VOS_UINT8                           ucPriCidFlag;                           /*0: ucPriCid��Ч,��PDPΪ��PDP; 1: ucPriCid��Ч,��PDPΪ����PDP*/
    VOS_UINT8                           ucPriCid;                               /*ָ����PDP������*/
    TAF_NV_PDP_PRIM_CONTEXT_STRU        CidTab;                                 /*Cid��*/

    VOS_UINT8                           ucEpsQosInfoFlg;                        /*0��EQos����Ч��1��EQos����Ч*/
    VOS_UINT8                           aucRsv1[3];
    TAF_EPS_QOS_STRU                    stEpsQosInfo;                           /*EQos������*/

    VOS_UINT8                           ucQosTabFlag;                           /*0��Qos����Ч��1��Qos����Ч*/
    VOS_UINT8                           aucRsv2[3];
    TAF_UMTS_QOS_STRU                   QosTab;                                 /*Qos��*/

    VOS_UINT8                           ucMinQosFlag;                           /*0:��������С�ɽ���Qos,1:û����С�ɽ���Qos*/
    VOS_UINT8                           aucRsv3[3];
    TAF_UMTS_QOS_STRU                   MinQosTab;                              /*MINQos��*/

    VOS_UINT8                           ucPfTabFlag;                            /* 0��pf����Ч��1��pf����Ч */
    VOS_UINT8                           aucRsv4[2];
    VOS_UINT8                           ucPfNum;                                /* pf���� */
    TAF_PDP_PF_STRU                     astPfTab[TAF_MAX_SDF_PF_NUM];           /* pf�� */

    VOS_UINT8                           ucAuthFlag;                             /*0��Auth����Ч��1��Auth����Ч*/
    VOS_UINT8                           aucRsv5[3];
    TAF_PDP_AUTH_STRU                   AuthTab;                                /*��Ȩ������*/

    VOS_UINT8                           ucDnsFlag;                              /*0��DNS����Ч��1��DNS����Ч*/
    VOS_UINT8                           aucRsv6[3];
    TAF_NV_PDP_DNS_STRU                 DnsTab;                                 /*DNS��*/

    VOS_UINT16                          usNvFlag;                               /*��CID����Ӧ��NV Table�����Ƿ����ù�: 0-δ����,1-������*/
    VOS_UINT8                           aucRsv7[10];
}TAF_NV_PDP_TABLE_STRU;

typedef struct
{
    TAF_UINT8   aucUserName[TAF_MAX_USERNAME_LEN + 1];                          /*aucUserName[0]�����û�������*/
    TAF_UINT8   aucPassword[TAF_MAX_PASSCODE_LEN + 1];                          /*aucPassword[0]�������볤��*/
} TAF_PDP_PCO_AUTH_PAP_STRU;


typedef struct
{
    TAF_UINT8   aucChallenge[TAF_PCO_CONTENT_MAX_LEN + 1];                      /*aucChallenge[0]����Challenge����*/
    TAF_UINT8   aucResponse[TAF_PCO_CONTENT_MAX_LEN + 1];                       /*aucResponse[0]����Response����*/
}TAF_PDP_PCO_AUTH_CHAP_STRU;

typedef struct
{
    TAF_PCO_AUTH_TYPE           AuthType;
    TAF_UINT8                   aucResverd[3];
    union
    {
        TAF_PDP_PCO_AUTH_PAP_STRU  stPap;
        TAF_PDP_PCO_AUTH_CHAP_STRU stChap;
    }AuthContent;
} TAF_PDP_PCO_AUTH_STRU;

typedef struct
{
    TAF_UINT32              OP_Auth             : 1;
    TAF_UINT32              OP_Dns              : 1;
    TAF_UINT32              OP_Nbns             : 1;
    TAF_UINT32              OP_Spare            : 29;

    TAF_UINT8               ucCid;
    TAF_PDP_TYPE_ENUM_UINT8 PdpType;

    TAF_UINT8               aucResverd[2];
    TAF_PDP_APN_STRU        stApn;
    TAF_UINT8               aucPdpAddr[TAF_IPV4_ADDR_LEN];
    TAF_PDP_PCO_AUTH_STRU   AuthPara;
    TAF_PDP_DNS_STRU        Dns;
    TAF_PDP_NBNS_STRU       Nbns;
} TAF_PSCALL_FOR_DIAL_EXT_STRU;




/*******************************************************************************
  3 ö�ٶ���
  typedef enum
{
    ģ����_��������_ENUM
    MAPS_TEMPLATE_ENUM1 = 0,
    MAPS_TEMPLATE_ENUM2
    MAPS_TEMPLATE_BUTT,     �����ͳһ��BUTT����Ϊ���һ��ö��ֵ��
}MAPS_TEMPLATE_ENUM;        ģ����_ö����������_ENUM
*******************************************************************************/

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �ṹ����   : MN_APS_IPV6_STR_TYPE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IPV6 String��ʽö��
              HEXΪRFC2373Ҫ��ʹ��':'��Ϊ�ָ���
              DEXΪRFCҪ��ʹ��'.'��Ϊ�ָ���
*****************************************************************************/
enum MN_APS_IPV6_STR_TYPE_ENUM
{
    MN_APS_IPV6_STR_TYPE_HEX       ,
    MN_APS_IPV6_STR_TYPE_DEC       ,

    MN_APS_IPV6_STR_TYPE_BUTT
};
typedef VOS_UINT8 MN_APS_IPV6_STR_TYPE_ENUM_UINT8;
#endif


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for  APP���                        */
/*=======================================================*/
typedef enum
{
    APS_CID_PPP                         = 1,
    APS_CID_IP,
    APS_CID_EMPTY,
    APS_CID_BUTT                        = 0xFF
} TAF_CID_TYPE_EN;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS SELF                        */
/*=======================================================*/
/*���ʽ*/
typedef enum
{
    APS_PDP_ACT_PRI                     = 0,
    APS_PDP_ACT_SEC,
    APS_PDP_ACT_BUTT                    = 0xFF
}APS_PDP_ACT_TYPE_ENUM;

typedef VOS_UINT8 APS_PDP_ACT_TYPE_ENUM_UINT8;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS SM���                      */
/*=======================================================*/
typedef enum
{
    APS_ACT_CNF                         = 0,
    APS_SEC_ACT_CNF,
    APS_MDF_CNF,
    APS_MDF_IND,
    APS_BUTT                            = 0xFF
} APS_QOS_NOT_SATISFY_MSGTYPE_ENUM;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS RABM���                    */
/*=======================================================*/

typedef enum
{
    MN_PS_MSG_PROC_MODE_GU,
    MN_PS_MSG_PROC_MODE_LTE,
    MN_PS_MSG_PROC_MODE_BUTT
} MN_PS_MSG_PROC_MODE_ENUM;
typedef VOS_UINT8 MN_PS_MSG_PROC_MODE_ENUM_UINT8;
enum TAF_TEAR_DOWN_ENUM
{
    TAF_PDP_NOT_TEAR_DOWN               = 0x00,                                 /*PDPȥ����ʱ�������*/
    TAF_PDP_TEAR_DOWN                   = 0x01,                                 /*PDPȥ����ʱ��Ҫ���*/

    TAF_PDP_TEAR_DOWN_BUTT              = 0xFF
};
typedef VOS_UINT8 TAF_TEAR_DOWN_ENUM_UINT8;


enum TAF_APS_RAT_TYPE_ENUM
{
    TAF_APS_RAT_TYPE_NULL,          /* ��ǰδ���κ�������פ�� */
    TAF_APS_RAT_TYPE_GSM,           /* GSM���뼼�� */
    TAF_APS_RAT_TYPE_WCDMA,         /* WCDMA���뼼�� */
    TAF_APS_RAT_TYPE_LTE,           /* LTE���뼼�� */
    TAF_APS_RAT_TYPE_1X,            /* CDMA-1X���뼼�� */
    TAF_APS_RAT_TYPE_HRPD,          /* CDMA-HRPD���뼼�� */
    TAF_APS_RAT_TYPE_EHRPD,         /* CDMA-EHRPD���뼼�� */
    TAF_APS_RAT_TYPE_BUTT           /* ��Ч�Ľ��뼼�� */
};
typedef VOS_UINT32 TAF_APS_RAT_TYPE_ENUM_UINT32;

/** ****************************************************************************
 * Name        : TAF_APS_CDATA_PPP_STATE_ENUM
 *
 * Description : PPP��ǰ�ļ���״̬
 *******************************************************************************/
enum TAF_APS_CDATA_PPP_STATE_ENUM
{
    TAF_APS_CDATA_PPP_STATE_INACTIVE            = 0x00,             /* PPPδ���ڼ���̬ */
    TAF_APS_CDATA_PPP_STATE_ACTIVATING          = 0x01,             /* PPP���ڼ���Э�̹����� */
    TAF_APS_CDATA_PPP_STATE_ACTIVE              = 0x02,             /* PPP���ڼ���̬ */
    TAF_APS_CDATA_PPP_STATE_DEACTIVATING        = 0x03,             /* PPP����ȥ����Э�̹����� */
    TAF_APS_CDATA_PPP_STATE_BUTT                = 0x04
};
typedef VOS_UINT8 TAF_APS_CDATA_PPP_STATE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_APS_CDATA_SO_TYPE_ENUM_UINT16
 * Description :
 *******************************************************************************/
enum TAF_APS_CDATA_SO_TYPE_ENUM
{
    TAF_APS_CDATA_SO_2_LOOPBACK              = 0x0002,
    TAF_APS_CDATA_SO_3_EVRC                  = 0x0003,
    TAF_APS_CDATA_SO_6_SMS                   = 0x0006,
    TAF_APS_CDATA_SO_7_PPP_PKT_DATA_PRE707   = 0x0007,
    TAF_APS_CDATA_SO_14_RS2_SMS              = 0x000E,
    TAF_APS_CDATA_SO_33_PPP_PKT_DATA         = 0x0021,
    TAF_APS_CDATA_SO_68_EVRC_B               = 0x0044,
    TAF_APS_CDATA_SO_73_EVRC_NW              = 0x0049,
    TAF_APS_CDATA_SO_BUTT                    = 0x004A
};
typedef VOS_UINT16 TAF_APS_CDATA_SO_TYPE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : TAF_APS_CDATA_PS_STATE_ENUM_UINT8
 * Description :
 *******************************************************************************/
enum TAF_APS_CDATA_PS_STATE_ENUM
{
    TAF_APS_CDATA_PS_STATE_INACTIVE,
    TAF_APS_CDATA_PS_STATE_ACTIVATING,
    TAF_APS_CDATA_PS_STATE_DEACTIVATING,
    TAF_APS_CDATA_PS_STATE_ACTIVE,

    TAF_APS_CDATA_PS_STATE_BUTT
};
typedef VOS_UINT8 TAF_APS_CDATA_PS_STATE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : TAF_APS_CDATA_PS_STATE_ENUM_UINT8
 * Description :
 *******************************************************************************/
enum TAF_APS_CDATA_REDIAL_TYPE_ENUM
{
    TAF_APS_CDATA_REDIAL_TYPE_NONE,
    TAF_APS_CDATA_REDIAL_TYPE_DRS_TRUE,
    TAF_APS_CDATA_REDIAL_TYPE_DRS_FALSE,

    TAF_APS_CDATA_REDIAL_TYPE_BUTT
};
typedef VOS_UINT8 TAF_APS_CDATA_REDIAL_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 STRUCT����
  typedef struct
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];
} MAPS_TEMPLATE_ST;
*****************************************************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS BASE                        */
/*=======================================================*/
typedef struct                                              /*���TS24008 10.5.6.4 */
{
    VOS_UINT8                           ucPdpTypeNum;       /*APS_ADDR_DYNAMIC_IPV4
                                                              APS_ADDR_STATIC_IPV4
                                                              APS_ADDR_PPP
                                                              MN_APS_ADDR_DYNAMIC_IPV6
                                                              MN_APS_ADDR_IPV6
                                                              MN_APS_ADDR_IPV4V6
                                                            */
    VOS_UINT8                           ucPdpTypeOrgan;     /*0 - ETSI allocated address
                                                              1 - IETF allocated address
                                                              15- Empty PDP type
                                                            */
    VOS_UINT8                           aucReserved[2];     /* ���ֽڶ���  */

    VOS_UINT8                           aucIpAddr[TAF_IPV4_ADDR_LEN];
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           aucIpV6Addr[TAF_IPV6_ADDR_LEN];
#endif

} APS_PDP_ADDR_ST;

typedef struct
{
    VOS_UINT32                          OP_PriDns   : 1;
    VOS_UINT32                          OP_SecDns   : 1;
    VOS_UINT32                          OP_Spare    : 30;

    VOS_UINT8                           aucPriDns[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDns[TAF_IPV4_ADDR_LEN];
}APS_PDP_DNS_ST;

typedef struct
{
    VOS_UINT32                          OP_PriNbns   : 1;
    VOS_UINT32                          OP_SecNbns   : 1;
    VOS_UINT32                          OP_Spare    : 30;

    VOS_UINT8                           aucPriNbns[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecNbns[TAF_IPV4_ADDR_LEN];
}APS_PDP_NBNS_ST;

/*****************************************************************************
 �ṹ����   : MN_APS_PDP_GATEWAY_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IPCP�����е�GATEWAY��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpGateWay    : 1;
    VOS_UINT32                          bitOpSpare      : 31;

    VOS_UINT8                           aucGateWay[TAF_IPV4_ADDR_LEN];
} MN_APS_PDP_GATEWAY_STRU;

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �ṹ����   : MN_APS_PDP_IPV6_DNS_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IPCP�����е�IPv6 DNS��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPriDns     : 1;
    VOS_UINT32                          bitOpSecDns     : 1;
    VOS_UINT32                          bitOpSpare      : 30;

    VOS_UINT8                           aucPriDns[TAF_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecDns[TAF_IPV6_ADDR_LEN];
} MN_APS_PDP_IPV6_DNS_STRU;


#endif


typedef struct                                              /*���TS24008 10.5.6.1*/
{
    VOS_UINT8                           ucLength;           /*aucValue[MAX_LENGTH_OF_APN]
                                                              ����Ч���ݵĳ���*/
    VOS_UINT8                           aucValue[APS_MAX_LENGTH_OF_APN];
                                                            /*24008�ж����APN�����г���
                                                              �ֽں���ֽ�*/
    VOS_UINT8                           aucRsv[2];         /* 4�ֽڶ��� */
}APS_PDP_APN_ST ;

/* ����PDPʵ���е�TFT�ṹ�� */
typedef struct
{
    VOS_UINT32                          OP_SourcePort           : 1;
    VOS_UINT32                          OP_DestPort             : 1;
    VOS_UINT32                          OP_SourceIpAddrAndMask  : 1;
    VOS_UINT32                          OP_ProtocolId           : 1;
    VOS_UINT32                          OP_ulSecuParaIndex      : 1;

    VOS_UINT32                          OP_ucTypeOfService      : 1;
    VOS_UINT32                          OP_Spare                : 26;


    VOS_UINT8                           ucPacketFilterId;
    VOS_UINT8                           ucPrecedence;       /*packet filter evaluation precedence*/
    VOS_UINT8                           aucRsv[2];         /* 4�ֽڶ��� */
    VOS_UINT16                          usSrcPortHighLimit;
    VOS_UINT16                          usSrcPortLowLimit;
    VOS_UINT16                          usDstPortHighLimit;
    VOS_UINT16                          usDstPortLowLimit;
    VOS_UINT8                           aucSrcIpAddress[TAF_IPV4_ADDR_LEN];
                                                            /*ucSourceIpAddress[0]ΪIP��ַ���ֽ�λ
                                                              ucSourceIpAddress[3]Ϊ���ֽ�λ*/
    VOS_UINT8                           aucSrcIpMask[TAF_IPV4_ADDR_LEN];
                                                            /*ucSourceIpMask[0]ΪIP��ַ���ֽ�λ ,
                                                              ucSourceIpMask[3]Ϊ���ֽ�λ*/
    VOS_UINT32                          ulSecuParaIndex;    /*SPI*/
    VOS_UINT8                           ucProtocolId;       /*Э���*/
    VOS_UINT8                           ucTypeOfService;    /*TOS*/
    VOS_UINT8                           ucTypeOfServiceMask;/*TOS Mask*/
    VOS_UINT8                           ucRsv;              /* 4�ֽڶ��� */
}APS_PDP_TFT_ST;

typedef struct
{
    VOS_UINT8                           ucDelayClass;
    VOS_UINT8                           ucReliabClass;
    VOS_UINT8                           ucPeakThrough;
    VOS_UINT8                           ucPrecedenceClass;
    VOS_UINT8                           ucMeanThrough;
    VOS_UINT8                           ucTrafficClass;
    VOS_UINT8                           ucDeliverOrder;
    VOS_UINT8                           ucDeliverOfErrSdu;
    VOS_UINT8                           ucMaximSduSize;
    VOS_UINT8                           ucMaxBitRateForUp;
    VOS_UINT8                           ucMaxBitRateForDown;
    VOS_UINT8                           ucResidualBer;
    VOS_UINT8                           ucSduErrRatio;
    VOS_UINT8                           ucTransDelay;
    VOS_UINT8                           ucTraffHandlPrior;
    VOS_UINT8                           ucGuarantBitRateForUp;
    VOS_UINT8                           ucGuarantBitRateForDown;
    VOS_UINT8                           ucSrcStatisticsDescriptor;
    VOS_UINT8                           ucSignallingIndication;
    VOS_UINT8                           ucMaxBitRateForDownExt;
    VOS_UINT8                           ucGuarantBitRateForDownExt;
    VOS_UINT8                           ucMaxBitRateForUpExt;
    VOS_UINT8                           ucGuarantBitRateForUpExt;
    VOS_UINT8                           ucMaxBitRateForDownExt_2;
    VOS_UINT8                           ucGuarantBitRateForDownExt_2;
    VOS_UINT8                           ucMaxBitRateForUpExt_2;
    VOS_UINT8                           ucGuarantBitRateForUpExt_2;
    VOS_UINT8                           aucRsv[1];         /* 4�ֽڶ��� */
} APS_PDP_QOS_ST;
typedef APS_PDP_QOS_ST          APS_PDP_QOS_STRU;

typedef struct
{
    VOS_UINT32                          Op_Sapi             : 1;
    VOS_UINT32                          Op_RadioPriority    : 1;
    VOS_UINT32                          Op_Xid_PCmp         : 1;
    VOS_UINT32                          Op_Xid_DCmp         : 1;
    VOS_UINT32                          Op_TransMode        : 1;

    VOS_UINT32                          OP_PacketFlowId     : 1;
    VOS_UINT32                          Op_Spare            : 26;

    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;    /*Refer to 24.008 10.5.7.2
                                                              1: riority level 1 (highest)
                                                              2: riority level 2
                                                              3: riority level 3
                                                              4: riority level 4 (lowest) */

    VOS_UINT8                           ucPCmprAlgrth;      /*#define SN_1144_ALGRTH    0
                                                              #define SN_2507_ALGRTH    1
                                                              #define SN_ROHC_ALGRTH    2 */

    VOS_UINT8                           ucDCmprAlgrth;      /*#define SN_V42_ALGRTH     0
                                                              #define SN_V44_ALGRTH     1 */
    VOS_UINT8                           ucPacketFlowId;
    VOS_UINT8                           aucReserved[3];
    RABM_TRANS_MODE_ENUM                TransMode;
} APS_GPRS_PARA_ST;

/*API���ָ�APP����ĸ���PDP������Ҫ�����������Щ����֮��Ķ�Ӧ��ϵ��PDP״̬
���б��档*/
typedef struct
{
    VOS_UINT32                          aulModuleId[TAF_MAX_CID + 1];
    VOS_UINT16                          ausClientId[TAF_MAX_CID + 1];
    VOS_UINT8                           aucId[TAF_MAX_CID + 1];                 /* CallId, Smi, OpId */
    TAF_PDP_TYPE_ENUM_UINT8             aenPdpType[TAF_MAX_CID + 1];            /* ��¼���𼤻��PDP���� */
    VOS_UINT32                          ulBitCidMask;                               /* PS����ʱ���ڼ�¼��������Ӧcid����,�����뷽ʽ��¼ */
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_APS_CLIENT_INFO_STRU;


typedef struct
{
    /*SNDCP�Ƿ��Ѿ�����
      #define                           APS_SNDCP_INACT             0
      #define                           APS_SNDCP_ACT               1*/
    VOS_UINT8                           ucSNDCPActOrNot;

    /*��������ļ���:APP����,APP�ֶ�,APS�Զ�
      #define                           APS_APP_INIT_ACT            1
      #define                           APS_APP_MANUL_ACT           2
      #define                           APS_TAF_AUTO_INIT_ACT       3 */
    VOS_UINT8                           ucHowToInitAct;

    /*���������ȥ����:APP����,APS�Զ�,���緢���ȥ����,��������е�ȥ����,
      #define                           APS_APP_INIT_DEACT          1
      #define                           APS_APS_AUTO_INIT_DEACT     2
      #define                           APS_NET_INIT_DEACT          3
      #define                           APS_DEACT_DURING_ACTING     4 */
    VOS_UINT8                           ucHowToInitDeAct;

    /*UE�յ������MDF_IND��ACT_CNFʱ���ܻ��޸�ADDR,���յ�SNDCP����Ӧ��,���ݴ˱�ʶ��
      ���Ƿ���APP�ϱ�ADDR��Ϣ.
      �յ�MDF_IND��ACT_CNF,����յ���ADDR��ԭ����ADDR��ͬ,��˱�ʶ����ΪAPS_NETIND_ADDR_DIFF,
      ������û�з���ADDR������ADDR��ԭ������ͬ,������ΪAPS_NETIND_ADDR_SAME
      #define                           APS_NETIND_ADDR_SAME        0
      #define                           APS_NETIND_ADDR_DIFF        1 */
    VOS_UINT8                           ucMdfIndAddrDiffOrNot;

    /*�˴�ȥ�����TEARSOWN����
      #define                           APS_DEACT_NOTEARDOWN        0
      #define                           APS_DEACT_TEARDOWN          1
      #define                           APS_DEACT_BE_TEARDOWNED     2
      #define                           APS_TEARDOWN_INVALID        255 */
    VOS_UINT8                           ucTeardown;

    VOS_UINT8                           aucRsv[3];
} APS_PDP_PROC_TRACK_ST;

typedef struct
{

    /* Added by y00314741 for CDMA Iteration 15, 2015-5-18, begin */
    VOS_UINT8                           ucPdnId;
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-18, end */
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucSrId;


    VOS_UINT8                           ucConnectId;
    VOS_UINT8                           ucConRef;
    TAF_APS_CDATA_SO_TYPE_ENUM_UINT16   enSo;

    VOS_UINT8                           ucIsDormDataCall;
    VOS_UINT8                           ucDrsFlg;           /**<  data ready to send */
    VOS_UINT8                           ucIsL2ErrReOrig;    /**<  reason of re orig is L2 error */
    VOS_UINT8                           ucReOrigCount;      /**<  coutinous count */
    TAF_APS_CDATA_PS_STATE_ENUM_UINT8   enPsState;
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enLastReOrigErr;
    VOS_UINT8                           aucReserved[2];
}TAF_APS_CDATA_CONTEXT_ENTITY_STRU;

/*�ṹ��APS_PDP_CONTEXT_ENTITY_ST��������PDPʵ��,ÿһ��PDP������,��Ӧһ����
�ṹ���ʵ�塣*/
typedef struct
{
    VOS_UINT32                          PdpNsapiFlag        :   1;
    VOS_UINT32                          PdpAddrFlag         :   1;
    VOS_UINT32                          PdpApnFlag          :   1;
    VOS_UINT32                          PdpDnsFlag          :   1;
    VOS_UINT32                          PdpTftFlag          :   1;

    VOS_UINT32                          PdpQosFlag          :   1;
    VOS_UINT32                          PdpAuthFlag         :   1;
    VOS_UINT32                          PdpGprsParaFlag     :   1;
    VOS_UINT32                          PdpProcTrackFlag    :   1;

    VOS_UINT32                          bitOpPdpNbns        :   1;
    VOS_UINT32                          bitOpPdpGateWay     :   1;
    VOS_UINT32                          bitOpTransId        :   1;
    VOS_UINT32                          bitOpIpv6RaInfo     :   1;
    VOS_UINT32                          bitOpCause          :   1;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          bitOpPf             :   1;
    VOS_UINT32                          bitOpEpsQos         :   1;
#endif

    VOS_UINT32                          bitOpImCnSigalFlag  :   1;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          bitOpSpare          :   15;
#else
    VOS_UINT32                          bitOpSpare          :   17;
#endif /* (FEATURE_ON == FEATURE_LTE) */

    VOS_UINT32                          ulUsedFlg;          /* ��ǰʵ���Ƿ�ʹ�õı�ʾ��VOS_TRUE:�Ѿ�ʹ�ã�VOS_FALSE:û��ʹ�� */

    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucLinkedNsapi;      /*�������NSAPI,������������
                                                              ���μ���,��˳�Ա��Ч*/
    APS_PDP_ACT_TYPE_ENUM_UINT8         ActType;            /*��������*/

    APS_PDP_ADDR_ST                     PdpAddr;
    APS_PDP_APN_ST                      PdpApn;
    APS_PDP_DNS_ST                      PdpDns;
    APS_PDP_NBNS_ST                     stPdpNbns;
    MN_APS_PDP_GATEWAY_STRU             stPdpGateWay;

    TAF_PDP_PCSCF_STRU                  stPdpPcscf;

    APS_PDP_TFT_ST                      PdpTft[APS_TFT_FILTER_AMOUNT + 1];

    APS_PDP_QOS_ST                      PdpQos;

    TAF_EPS_QOS_STRU                    stEpsQos;

    TAF_PDP_PCO_AUTH_STRU               AuthTab;

    APS_GPRS_PARA_ST                    GprsPara;           /*˫ģ����ʹ�õĲ���,��ģ����*/

    TAF_APS_CLIENT_INFO_STRU            stClientInfo;

    APS_PDP_PROC_TRACK_ST               PdpProcTrack;       /*PDP������¼*/

    VOS_UINT32                          ulNdClientActiveFlg;
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-24, begin */
    /* �յ�dhcp IPv4, IPv6 Э����ɱ�־���Ӷ��ж��յ���Ϣ����  */
    VOS_UINT8                           ucRcvDhcpDnsFlgIpv4;
    VOS_UINT8                           ucRcvDhcpDnsFlgIpv6;
    /* ��ΪЭ�̿�ʼ��־λ���������� */
    VOS_UINT8                           ucNeedGetDnsFlg;
    VOS_UINT8                           ucRcvNdClientNtyFlg;

    /* Added by y00314741 for CDMA Iteration 15, 2015-5-24, end */
    MN_APS_PDP_IPV6_DNS_STRU            stPdpIpV6Dns;       /* IPv6 DNS */
    TAF_PDP_IPV6_PCSCF_STRU             stPdpIpv6Pcscf;     /* IPv6 P-CSCF */
    TAF_PDP_IPV6_RA_INFO_STRU           stIpv6RaInfo;       /* IPv6 RA������Ϣ */
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    SM_TAF_TRANS_ID_STRU                stTransId;

#if (FEATURE_ON == FEATURE_LTE)
    SM_ESM_TFT_STRU                     stTft;              /* Packet Filter */
#endif
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyFlg;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    /* �����ڲ�ȥ�����, �Ƿ��ϱ�PDP_DEACTIVATE_IND�¼���ʶ  */
    VOS_UINT8                           ucInterDeactNotifyFlg;

    /* Ĭ�ϳ��صı�־ */
    VOS_UINT8                           ucDefaultBearerFlag;

    TAF_APS_PDP_MOD_DIAL_STRU           stModDial;

    TAF_APS_CDATA_CONTEXT_ENTITY_STRU   stCdataInfo;

}APS_PDP_CONTEXT_ENTITY_ST;

typedef APS_PDP_CONTEXT_ENTITY_ST TAF_APS_PDN_CONTEXT_STRU;


/*���TI��¼����Ч����Ϊ1-7*/
typedef struct
{
    VOS_UINT8   ucIncomCallNum;
    VOS_UINT8   ucTi[APS_MIDDLE_TI + 1];
}APS_INCOM_CALL_TI_TABLE;

/*����������緵�ص�CPO*/
typedef struct
{
    VOS_UINT32                          ulFlg;              /*VOS_TRUE:��Ч
                                                              VOS_FALSE:��Ч*/
    SM_TAF_PROT_CFG_OPT_STRU            ApsNetPco;
} APS_NET_PCO_ST;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS �������                    */
/*=======================================================*/
typedef struct
{
    VOS_UINT32                          OP_APN      : 1;
    VOS_UINT32                          OP_AUTH     : 1;
    VOS_UINT32                          OP_DNS      : 1;
    VOS_UINT32                          OP_NBNS     : 1;
    VOS_UINT32                          OP_Sapi     : 1;
    VOS_UINT32                          Op_Xid_PCmp : 1;
    VOS_UINT32                          Op_Xid_DCmp : 1;

    VOS_UINT32                          OP_SPARE    : 25;


    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucSapi;         /*Add SAPI for 2G
                                                          0 0 0 0  LLC SAPI not assigned
                                                          0 0 1 1  SAPI 3
                                                          0 1 0 1  SAPI 5
                                                          1 0 0 1  SAPI 9
                                                          1 0 1 1  SAPI 11*/

    VOS_UINT8                           ucPdpType;      /*#define APS_ADDR_DYNAMIC_IPV4 0
                                                          #define APS_ADDR_STATIC_IPV4  1
                                                          #define APS_ADDR_PPP          2 */

    VOS_UINT8                           ucPCmprAlgrth;  /*#define SN_1144_ALGRTH        0
                                                          #define SN_2507_ALGRTH        1
                                                          #define SN_ROHC_ALGRTH        2 */

    VOS_UINT8                           ucDCmprAlgrth;  /*#define SN_V42_ALGRTH         0
                                                          #define SN_V44_ALGRTH         1 */

    VOS_UINT8                           aucApn[APS_MAX_LENGTH_OF_APN];
                                                        /*24008�й涨��APN���Ⱥ�����*/
    VOS_UINT8                           aucReserved[2];

    VOS_UINT8                           aucIpAddr[TAF_IPV4_ADDR_LEN];

    APS_PDP_QOS_ST                      ReqQos;
    TAF_PDP_PCO_AUTH_STRU               PdpAuth;
    TAF_PDP_DNS_STRU                    PdpDns;
    TAF_PDP_NBNS_STRU                   PdpNbns;
}APS_PDP_ACT_REQ_ST;


typedef struct
{
    VOS_UINT32                          OP_Sapi     : 1;    /*Add SAPI for 2G*/
    VOS_UINT32                          Op_Tft      : 1;
    VOS_UINT32                          Op_Xid_PCmp : 1;
    VOS_UINT32                          Op_Xid_DCmp : 1;
    VOS_UINT32                          Op_Spare    : 28;

    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucPriPdpId;
    VOS_UINT8                           ucSapi;             /*Add SAPI for 2G*/
    VOS_UINT8                           ucPCmprAlgrth;      /*#define SN_1144_ALGRTH        0
                                                              #define SN_2507_ALGRTH        1
                                                              #define SN_ROHC_ALGRTH        2 */

    VOS_UINT8                           ucDCmprAlgrth;      /*#define SN_V42_ALGRTH         0
                                                              #define SN_V44_ALGRTH         1*/
    VOS_UINT8                           aucRsv[3];
    APS_PDP_QOS_ST                      Qos;
    APS_PDP_TFT_ST                      Tft;
} APS_PDP_SEC_ACT_REQ_ST;

typedef struct
{
    VOS_UINT32                          Op_Qos      :1;
    VOS_UINT32                          Op_Tft      :1;

    /*Add SAPI for ˫ģ*/
    VOS_UINT32                          OP_Sapi     :1;
    VOS_UINT32                          Op_Spare    :29;

    /*Add SAPI for ˫ģ*/
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucRsv[2];
    APS_PDP_QOS_ST                      Qos;
    APS_PDP_TFT_ST                      Tft;
} APS_PDP_MDF_REQ_ST;

typedef struct
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucTearDown;
    SM_TAF_CAUSE_ENUM_UINT16            enCause;
} APS_PDP_DEACT_REQ_ST;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS SM���ز���                  */
/*=======================================================*/
typedef struct {
    VOS_UINT32                          OP_PdpAddr          : 1;
    VOS_UINT32                          OP_ProtCfgOpt       : 1;
    VOS_UINT32                          OP_Sapi             : 1;
    VOS_UINT32                          OP_RadioPriority    : 1;
    VOS_UINT32                          OP_PacketFlowId     : 1;

    VOS_UINT32                          OP_Spare            : 27;

    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;    /*Refer to 24.008 10.5.7.2*/
    VOS_UINT8                           ucPacketFlowId;
    APS_PDP_QOS_ST                      PdpQos;
    APS_PDP_ADDR_ST                     PdpAddr;
    APS_PDP_DNS_ST                      PcoDns;
    APS_PDP_NBNS_ST                     PcoNbns;
    MN_APS_PDP_GATEWAY_STRU             stPcoGateWay;
#if (FEATURE_ON == FEATURE_LTE)
    SM_TAF_TRANS_ID_STRU                stTransId;
#endif
} APS_ACTCNF_PARA_ST;

typedef struct
{
    VOS_UINT32                               OP_Sapi             : 1;
    VOS_UINT32                               OP_RadioPriority    : 1;
    VOS_UINT32                               OP_PacketFlowId     : 1;
    VOS_UINT32                               OP_Spare            : 29;

    APS_PDP_QOS_ST                      PdpQos;
    VOS_UINT8                           ucNsapi;

    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;
    VOS_UINT8                           ucPacketFlowId;
#if (FEATURE_ON == FEATURE_LTE)
    SM_TAF_TRANS_ID_STRU                stTransId;
#endif
} APS_ACTSECCNF_PARA_ST;




typedef struct
{
    VOS_UINT32                          OP_QOS              : 1;
    VOS_UINT32                          OP_SAPI             : 1;
    VOS_UINT32                          OP_RadioPri         : 1;
    VOS_UINT32                          OP_PFI              : 1;
    VOS_UINT32                          OP_SPARE            : 28;

    APS_PDP_QOS_ST                      PdpQos;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;    /*Refer to 24.008 10.5.7.2
                                                            1: riority level 1 (highest)
                                                            2: riority level 2
                                                            3: riority level 3
                                                            4: riority level 4 (lowest)*/
    VOS_UINT8                           ucPacketFlowId;

    VOS_UINT8                           aucReserved[1];
} APS_MDFCNF_PARA_ST;

typedef struct
{
    VOS_UINT32                          OP_PdpAddr          : 1;
    VOS_UINT32                          OP_Nsapi            : 1;

    /*Add SAPI��RadioPriority for 2G */
    VOS_UINT32                          OP_Sapi             : 1;
    VOS_UINT32                          OP_RadioPriority    : 1;
    VOS_UINT32                          OP_PacketFlowId     : 1;
    VOS_UINT32                          OP_Spare            : 27;

    APS_PDP_QOS_ST                      NewQos;
    APS_PDP_ADDR_ST                     PdpAddr;
    VOS_UINT8                           ucNsapi;

    /*Add SAPI��RadioPriority for 2G */
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;
    VOS_UINT8                           ucPacketFlowId;
} APS_MDFIND_PARA_ST;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS ����SNDCP�Ĳ���             */
/*=======================================================*/

typedef struct
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[3];
    SM_TAF_QOS_STRU                    *pQos;
} APS_INNER_SN_ACT_ST;

typedef struct
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[3];
    SM_TAF_QOS_STRU                    *pQos;
} APS_INNER_SN_MDF_ST;



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS SNDCP����APS�Ĳ���          */
/*=======================================================*/
/*�� Taf_ApsForSndcp.h*/


typedef struct
{
    VOS_UINT32                          ulTLLI;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           aucReserved[3];
    APS_SNDCP_XID_REQ_TAB_ST            XidReqTab[APS_NSAPI_MAX + 1];
                                                            /*�������λ��ΪNSAPI������*/
}APS_SNDCP_ACT_REQ_ST;


typedef struct{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*��Ϣ����*/

    /*��ucNsapi;��Χ�������SN_DATA_REQ_ST�е�˵�����ֶ�����Ϣ�����ӽ��̱�ʾ*/
    VOS_UINT16                          usPId;

    VOS_VOID                           *pSnMsg;
} APS_SNDCP_COMMON_MSG;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS MONITOR �ȱ������                    */
/*=======================================================*/
typedef struct
{
    VOS_UINT32  ulModPdpFlg;      /* 0 - �ȱ���ģ��δ����MODIFY PDP����;  1 - �ȱ���ģ�鷢����MODIFY PDP���� */
    VOS_UINT8   ucPdpId;
    VOS_UINT8   ucCid;
    VOS_UINT8   aucRsv[2];
}APS_MONITOR_MOD_PDP_INFO_STRU;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   �ն˿������������ӵĽṹ��          */
/*=======================================================*/

/* �ն˿���������: Mean throughput ���� */
typedef struct
{
    VOS_UINT8   ucStatus;       /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8   ucMeanThrough;
}APS_MEAN_THROUGH_CUSTOMIZE_STRU;
typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32            enPsCuase;
    SM_TAF_CAUSE_ENUM_UINT16            enSmCause;
    VOS_UINT8                           aucRsv[2];

} TAF_APS_SM_ERR_CODE_MAP_STRU;


typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32            enPsCause;
    VOS_UINT32                          ulL4aCause;

} TAF_APS_L4A_ERR_CODE_MAP_STRU;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32            enPsCause;
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause;

} TAF_APS_XCC_ERR_CODE_MAP_STRU;


typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32            enPsCause;
    HSM_APS_CAUSE_ENUM_UINT32           enHsmCause;

} TAF_APS_HSM_ERR_CODE_MAP_STRU;


/* Added by y00314741 for CDMA Iteration 15, 2015-5-15, begin */
/*****************************************************************************
 �ṹ��  : TAF_APS_EHSM_ERR_CODE_MAP_STRU
 �ṹ˵��: TAF��������EHSM������ӳ��ṹ

 �޸���ʷ      :
  1.��    ��   : 2015��05��15��
    ��    ��   : y00314741
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32            enPsCause;
    EHSM_APS_CAUSE_ENUM_UINT32          enEhsmCause;

} TAF_APS_EHSM_ERR_CODE_MAP_STRU;
/* Added by y00314741 for CDMA Iteration 15, 2015-5-15, end */

#endif

typedef VOS_UINT32 (*MN_PS_MSG_FUNC)(VOS_VOID *pMsgData);

/*****************************************************************************
 �ṹ����: ID_MN_PS_EVT_ID_ENUM
 �ṹ˵��: MN��APP֮����¼�ԭ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;
    MN_PS_MSG_FUNC                      pMsgFunc;
} MN_PS_MSG_FUNC_TBL_STRU;

typedef struct
{
    const MN_PS_MSG_FUNC_TBL_STRU      *pstMsgFuncTbl;
    const VOS_UINT32                    ulMsgTblSize;
} MN_PS_MSG_TBL_ENTRY_STRU;


typedef struct
{
    VOS_UINT32                          ulChallengeLen;
    VOS_UINT8                           aucChallenge[TAF_APS_PPP_CHAP_CHALLNGE_LEN];
    VOS_UINT32                          ulChallengeNameLen;
    VOS_UINT8                           aucChallengeName[TAF_APS_PPP_CHAP_CHALLNGE_NAME_LEN];
    VOS_UINT32                          ulResponseLen;
    VOS_UINT8                           aucResponse[TAF_APS_PPP_CHAP_RESPONSE_LEN];
    VOS_UINT8                           ucResponseNameLen;
    VOS_UINT8                           aucResponseName[TAF_MAX_USERNAME_LEN];

} TAF_APS_CHAP_PARAM_STRU;


typedef struct
{
    VOS_UINT8                           ucUsernameLen;
    VOS_UINT8                           aucUsername[TAF_MAX_USERNAME_LEN];
    VOS_UINT8                           ucPasswordLen;
    VOS_UINT8                           aucPassword[TAF_MAX_PASSCODE_LEN];

} TAF_APS_PAP_PARAM_STRU;


typedef struct
{
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enAuthType;
    VOS_UINT8                           ucAuthId;
    VOS_UINT8                           aucRsv[2];

    union
    {
        TAF_APS_CHAP_PARAM_STRU         stChapParam;
        TAF_APS_PAP_PARAM_STRU          stPapParam;
    } unAuthParam;

} TAF_APS_AUTH_INFO_STRU;



typedef struct
{
    VOS_UINT32                          bitOpIpAddr         :1;
    VOS_UINT32                          bitOpPrimDns        :1;
    VOS_UINT32                          bitOpSecDns         :1;
    VOS_UINT32                          bitOpPrimNbns       :1;
    VOS_UINT32                          bitOpSecNbns        :1;
    VOS_UINT32                          bitOpSpare          :27;

    VOS_UINT8                           aucIpAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucPrimDns[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDns[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucPrimNbns[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecNbns[TAF_IPV4_ADDR_LEN];

} TAF_APS_IPCP_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucCode;                                 /* Request code */
    VOS_UINT8                           ucId;                                   /* Identification */
    VOS_UINT16                          usLength;                               /* Length of packet */
} TAF_PPP_FRAME_HEAD_STRU;
typedef struct
{
    VOS_UINT8                           ucUsed;                                 /*0��δʹ�ã�1��ʹ��*/
    VOS_UINT8                           aucReserved[3];
    TAF_PDP_AUTHDATA_STRU               stAuthData;                             /*��Ȩ����*/

} TAF_NDIS_AUTHDATA_TABLE_STRU;


typedef struct
{
    TAF_PDP_ANSWER_MODE_ENUM_UINT8      enAnsMode;
    TAF_PDP_ANSWER_TYPE_ENUM_UINT8      enAnsType;
    VOS_UINT16                          usClientId;
}TAF_PS_ANSWER_MODE_STRU;


typedef struct
{
    VOS_UINT32                          ulNum;
    VOS_UINT8                           aucCid[TAF_MAX_CID + 1];
}TAF_APS_BITCID_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucPrimaryPdpFlg;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
    VOS_UINT8                           aucReserved[1];
    TAF_PDP_APN_STRU                    stApn;
} TAF_APS_MATCH_PARAM_STRU;

/*****************************************************************************
 �ṹ����: TAF_APS_CID_IMS_CFG_TBL_STRU
 �ṹ˵��: CID IMS���ñ�

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : z00301431
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8            aucImsFlag[TAF_MAX_CID + 1];
}TAF_APS_CID_IMS_CFG_TBL_STRU;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS RABM���                    */
/*=======================================================*/

/*****************************************************************************
  5 UNION����
  typedef union
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];
} MAPS_TEMPLATE_UNION;
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣͷ����
    ģ���������士HEADER
#define MAPS_TEMPLATE_HEADER    VOS_UINT16    usTotalsMsgLen;\
                                VOS_UINT32    ulSendModuleId;\
                                VOS_UINT32    ulRecvModuleId;
*****************************************************************************/

/*****************************************************************************
  7 ��Ϣ����
  typedef struct
{
    MAPS_TEMPLATE_HEADER
    VOS_UINT8    aucData[2];     ��Ϣ��
} MAPS_TEMPLATE_MSG;
*****************************************************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS RABM���                    */
/*=======================================================*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS SNDCP���                   */
/*=======================================================*/

/*****************************************************************************
  8 ȫ�ֱ�������
extern VOS_UINT8* pgucMapsTemplateBuffer;ָ�룫ȫ�ֱ�ʶ�����ͣ�ģ��������������
*****************************************************************************/
extern  VOS_UINT8                       g_ucApsInitFlg;

/*----------------------------------------------------------------------------
variable name   : g_PdpModifyReqTable
type            :
description     : ȫ�ֱ���,UEҪ���޸Ĳ���,��Ҫ�޸�Ϊ��ֵ������ڸñ���,�������
                  ������Ϣ��,������Ϣ����ȷ�����ô˴��Ĳ����޸������ı��еĲ���,
                  ���������緵�ص���Ϣ�޸������ı��еĲ���.

                  APS_PDP_MDF_REQ_ST�еĳ�ԱOP_SPARE����Ϊһ�����õı�ʶ��ʹ��:
                  OP_SPARE������Ϊ0,��Ϊ��Ч״̬;
                  ��APS�����޸�ʱ,����������QOS����,OP_SPARE������Ϊ0;
                  ��APS�����޸�ʱ,��������QOS,���������QOS��������ʱ,OP_SPARE������Ϊ1;
                  ��SM����MDF_CNF��Ϣ��,��״̬���и���QOS,�򽫴˱�ʶ����Ϊ2;
                  ��SM����MDF_CNF��Ϣ��,��״̬���в�����QOS,�򽫴˱�ʶ����Ϊ0;

                  APS_PDP_MDF_REQ_ST    g_PdpModifyReqTable[APS_MAX_PDP_NUM + 1 ]
value range     : APS_MAX_PDP_NUM�궨��Ϊ14��g_PdpModifyReqTable[i]��i��ȡֵ��Χ
                  Ϊ������[0,6]��[8,14],ע�ⲻ�ܵ���7.
used by         :
----------------------------------------------------------------------------*/
extern  APS_PDP_MDF_REQ_ST             *g_PdpModifyReqTable;
#define APS_MDF_NO_QOS                  0
#define APS_MDF_HAS_QOS                 1
#define APS_MDF_CNF_RENEW_QOS           2

/*----------------------------------------------------------------------------
variable name   : g_TafCidTab
type            : TAF_PDP_TABLE_STRU
description     : PDPȫ�����ݱ���CIDΪ��������FLASH��PDP���ݱ����ڴ��е�ӳ��.
                  ����0�ڲ��ż���ʱ��ʹ��,��CGACTʱ����ʹ��.

                  TAF_PDP_TABLE_STRU    g_TafCidTab[TAF_MAX_CID + 1]
value range     :
used by         :
----------------------------------------------------------------------------*/
extern  TAF_PDP_TABLE_STRU             *g_TafCidTab;

/*----------------------------------------------------------------------------
variable name   : g_PdpEntity
type            : VOS_UINT8
description     : APS��״̬��,��֧��11��PDP.��ϵͳ��ʼ��1ʱ�����ڴ�ռ䣬��ϵͳ
                  ��ʼ��2ʱ���г�ʼ��.

                  APS_PDP_CONTEXT_ENTITY_ST g_PdpEntity[APS_MAX_PDP_NUM +1]
value range     :
used by         : APSģ��������漰��״̬�������ĺ���.
----------------------------------------------------------------------------*/
extern  APS_PDP_CONTEXT_ENTITY_ST      *g_PdpEntity;

/*TAFͨ�Ų�����-PS*/
extern  TAF_PS_ANSWER_MODE_STRU         g_PsAnsMode;    /*PSӦ��ģʽ�洢��*/

extern VOS_UINT16                       g_PsRabToClientId[TAF_MAX_RABID + 1];

/*�����ӿ�RabId��ClientId��Ӧ��*/
extern VOS_UINT16                       g_CsRabToClientId[TAF_MAX_RABID + 1];


/*----------------------------------------------------------------------------
Varible Name    : g_TimerTable
type            : STRUCT ����
description     : APS_MAX_PDP_NUM ����������������е�APS_MAX_PDP_NUM ��TIMERһ
                  һ��Ӧ������ĳ��PENDING״̬, ��Ҫ������Ӧ��PdpId��TIMER;����
                  ĳ��PENDING״̬,ҲҪֹͣ��Ӧ��PdpId��TIMER;ĳPdpId�� TIMER��
                  ʱ,����PdpId�͵�ǰ�����ĵ�״̬����time expired ����,ͬʱClean
                  �� TIMER ��
value range     : APS_MAX_PDP_NUM�궨��Ϊ14��g_TimerTable[i]��i��ȡֵ��Χ
                  Ϊ������[0, 6]��[8, 14], ע�ⲻ�ܵ���7��
usage           : ��DOPRA�ṩ TIMER �����ĺ�����ʵ�ֶ� TIMER �Ĳ�����
----------------------------------------------------------------------------*/
extern  HTIMER                          g_TimerTable[TAF_APS_MAX_PDPID];

/*�ݴ潫��������PDP���������������������PDP�����Ƚϣ��Ծ�����Ҫ��NVIM��
�����ݽ����������޸�*/
extern  TAF_PDP_TABLE_STRU              g_TmpPdpTab;

/*������ѯ�Ƿ�����ı�ʶ*/
extern  VOS_UINT32                      g_AllRateTmpList[TAF_MAX_CID][3];

extern  const RABM_MSG_FUN_TYPE         g_RabmMsgFunMatrix[2][8];

/* �ն˿���������:2G���������ֹSpare_bit3�Ȳ��� */
#define APS_2G_BIT3_DISABLE              0    /*2G����ʱPDP������ϢЯ��Spare_bit3�Ȳ���  */
#define APS_2G_BIT3_ENABLE               1    /*2G����ʱPDP����������Ϣ��Я��bit3�Ȳ���  */
extern  VOS_UINT8   g_ucDisable2GR5QosExt;

/*Mean throughput���� */
extern  VOS_UINT8   g_ucMeanThrough;

/* WINS���������� */
extern  VOS_UINT8   g_ApsWins;

/*WIN7 NDIS��������:���ڱ���^AUTHDATA����ļ�Ȩ����*/
extern  TAF_NDIS_AUTHDATA_TABLE_STRU    *g_ApsNdisAuthdataTab;

extern  TAF_APS_CID_IMS_CFG_TBL_STRU   g_stCidImsCfgTable;

/*****************************************************************************
  9 FUNCTIONS����
*****************************************************************************/
/*APS��ȡ�Զ����𼤻�ʱPDP��Ϣ�ӿ�*/

/*-------------------------------------------------------*/
/*      APS-API(APS��TAFM�ṩ�Ĳ������ò�ѯ�����ӿ�)     */
/*-------------------------------------------------------*/

/*���塢�޸ġ�ɾ��PDP context��*/
VOS_VOID Aps_DefPsPdpContext (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pPara,
    VOS_UINT32                         *pulErrCode
);

/*���塢�޸ġ�ɾ��PDP�ļ�Ȩ��Ϣ��AT�޴������Ҫ�����Զ����*/
VOS_VOID Aps_DefPsPdpAuth(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_AUTH_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode
);

/*���塢�޸ġ�ɾ��Secondary PDP Context*/
VOS_VOID Aps_DefPsSecPdpContext (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_SEC_CONTEXT_EXT_STRU       *pPara,
    VOS_UINT32                         *pulErrCode
);


/*���塢�޸ġ�ɾ��PDP Context�е�DNS����*/
VOS_VOID Aps_DefPsDns(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_DNS_EXT_STRU               *pDnsPara,
    VOS_UINT32                         *pulErrCode
);

/*���塢�޸ġ�ɾ��PDP Context�е�3G QOS����*/
VOS_VOID Aps_DefPs3gReqQos(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_UMTS_QOS_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode
);

/*���塢�޸ġ�ɾ��PDP Context�е�3G��С�ɽ���QOS����*/
VOS_VOID Aps_DefPs3gMinAcceptQos(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_UMTS_QOS_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode
);

VOS_VOID    Aps_DefNdisAuthdata (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_AUTHDATA_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode);

VOS_UINT32  Aps_ChngAuthdata( TAF_AUTHDATA_EXT_STRU *pAuthdataPara,
                                      VOS_UINT8                   ucCid   );

VOS_VOID  Aps_DefAuthdata( TAF_AUTHDATA_EXT_STRU *pAuthdataPara,
                                  VOS_UINT8               ucCid   );


/*-------------------------------------------------------*/
/*      APS-API(APS��TAFM�ṩ�����̲��������ӿ�)         */
/*-------------------------------------------------------*/
/*PDP����*/
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_PsCallOrig(VOS_UINT8 ucPdpId);

/*������PDP����*/
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_PsCallForDial(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_ADDR_STRU                  *pstPdpAddr,
    TAF_PDP_APN_STRU                   *pstApn,
    PPP_REQ_CONFIG_INFO_STRU           *pstPppConfigInfo
);

/*PDP�޸�*/
VOS_VOID Aps_PsCallModify(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucError
);

/*PDPȥ����*/
VOS_VOID Aps_PsCallEnd(
    SM_TAF_CAUSE_ENUM_UINT16            enCause,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucError
);

/*�ṩ��ATC�Բ�ѯCID��PDP����*/
TAF_PDP_TYPE_ENUM_UINT8 Taf_GetCidType(VOS_UINT8 ucCid);

/*-------------------------------------------------------*/
/*               for   Aps_Assistant.c                   */
/*-------------------------------------------------------*/

VOS_VOID    Aps_PdpTabInit(             VOS_VOID    );
VOS_VOID    Aps_AuthdataTabInit(VOS_VOID);
VOS_VOID    Aps_PdpEntityInit(          VOS_VOID    );

VOS_VOID    Aps_RelSmLocResource(       VOS_UINT8                   ucPdpId );

VOS_VOID    Aps_ReleaseSndcpResource(   VOS_UINT8                   ucPdpId );


VOS_VOID    Aps_ReleaseApsResource  (   VOS_UINT8                   ucPdpId );


VOS_VOID    Taf_IpAddr2LenStr(CONST     VOS_UINT8                      *pucIpAddr,
                                        VOS_UINT8                      *pucStr);
VOS_VOID    Taf_Apn2Lenstr(             VOS_UINT8                      *pucApn,
                                        VOS_UINT8                      *pucStr);
VOS_VOID    Aps_LenStr2Str(             VOS_UINT8                   ucMaxLen,
                                        VOS_UINT8                  *pLenStr,
                                        VOS_UINT8                  *pStr );

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : MN_APS_Itoa
 ��������  : ����ת������(10��16), ������ת��ΪASCII��, �����������ַ���
 �������  : usValue    - ��ת��ΪASCII�������
             pcStr      - ���������ַ���
             usRadix    - ת������
 �������  : ��
 �� �� ֵ  : VOS_CHAR*
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_CHAR* MN_APS_Itoa(
    VOS_UINT16                          usValue,
    VOS_CHAR                           *pcStr,
    VOS_UINT16                          usRadix
);


/*****************************************************************************
 �� �� ��  : MN_APS_ConvertIpv6AddrToStr
 ��������  : ��IPV6��ַ��ʽת��Ϊ�ַ�����ʽ
 �������  : aucIpAddr[]    - IPV6��ַ(Э���ʽ)
             enIpStrType    - IPV6�ַ�����ʽ�������
 �������  : aucAddrStr[]   - IPV6��ַ(�ַ�����ʽ)
 �� �� ֵ  : VOS_OK         - ת���ɹ�
             VOS_ERR        - ת��ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 MN_APS_ConvertIpv6AddrToStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    MN_APS_IPV6_STR_TYPE_ENUM_UINT8     enIpStrType
);
#endif

VOS_VOID    Aps_3GQos2AppQos(           APS_PDP_QOS_STRU           *pApsQos,
                                        TAF_UMTS_QOS_STRU           *pTafQos);


VOS_VOID  Taf_PsParaSetResult(              VOS_UINT16               ClientId,
                                        VOS_UINT8                      OpId,
                                        TAF_PARA_SET_RESULT         Result,
                                        TAF_PARA_TYPE               ParaType,
                                        VOS_VOID                       *pPara );

VOS_UINT32 Taf_CheckActCid(                 VOS_UINT8                       ucCid);

VOS_UINT32  Aps_ChngDns(                TAF_PDP_DNS_EXT_STRU       *pDnsPara,
                                        VOS_UINT8                   ucCid  );


VOS_UINT32    Aps_SetEvtAddr(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_ADDR_STRU                  *pstPdpAddr
);
VOS_UINT32    Aps_SetEvtApn(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_APN_STRU                   *pstPdpApn
);

VOS_VOID    Aps_SetEvtCmp(              VOS_UINT8                    ucPdpId,
                                        TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *pPsAppEvt);

VOS_VOID    Aps_SetEvtDns(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_DNS_STRU                   *pstDns,
    TAF_PDP_IPV6_DNS_STRU              *pstIpv6Dns
);



/*****************************************************************************
 �� �� ��  : MN_APS_SetEvtNbns
 ��������  : ��дNBNS���¼�
 �������  : VOS_UINT8                           ucPdpId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPsCallEvt
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_SetEvtNbns(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_NBNS_STRU                  *pstNbns
);

/*****************************************************************************
 �� �� ��  : MN_APS_SetEvtGateWay
 ��������  : ��дGATE WAY���¼�
 �������  : VOS_UINT8                           ucPdpId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPsCallEvt
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_SetEvtGateWay(
    VOS_UINT8                           ucPdpId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPsCallEvt
);





/*****************************************************************************
 �� �� ��  : TAF_APS_SetEvtPcscf
 ��������  : ��дP-CSCF��Ϣ��PS�����¼�
 �������  : ucPdpId                    - PDP ID
             pstPsCallEvt               - PS�����¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID TAF_APS_SetEvtPcscf(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_PCSCF_STRU                 *pstPcscf,
    TAF_PDP_IPV6_PCSCF_STRU            *pstIpv6Pcscf
);


VOS_VOID    Aps_GlobVarFree(            VOS_VOID);
VOS_UINT32  Aps_JudgeSapiValid(         VOS_UINT8                   ucSapi);

/*-------------------------------------------------------*/
/*          APS�ڲ��ṩ�Ĳ������庯���ӿ�                */
/*-------------------------------------------------------*/
VOS_UINT32  Aps_ChngPdpPri(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pPdpPriPara,
    VOS_UINT8                           ucCid
);

VOS_VOID Aps_DefPdpPri(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pPdpPriPara,
    VOS_UINT8                           ucCid
);


VOS_UINT32  Aps_ChngAuth(               TAF_PDP_AUTH_EXT_STRU      *pAuthPara,
                                        VOS_UINT8                   ucCid   );


VOS_VOID    Aps_ChngSecPara(            TAF_PDP_SEC_CONTEXT_EXT_STRU       *pSecPara );
VOS_VOID    Aps_DefSecPara(             TAF_PDP_SEC_CONTEXT_EXT_STRU       *pSecPara );


VOS_VOID    Aps_ChngQos(                TAF_UMTS_QOS_EXT_STRU       *pQosPara,
                                        VOS_UINT8                   ucCid   );

VOS_VOID    Aps_DefQos(                 TAF_UMTS_QOS_EXT_STRU       *pQosPara,
                                        VOS_UINT8                   ucCid   );

VOS_VOID    Aps_ChngMinQos(             TAF_UMTS_QOS_EXT_STRU       *pQosPara,
                                        VOS_UINT8                   ucCid   );
VOS_VOID    Aps_DefMinQos(              TAF_UMTS_QOS_EXT_STRU       *pQosPara,
                                        VOS_UINT8                   ucCid   );

VOS_VOID Aps_QuePri(
    VOS_UINT8                           ucCid,
    TAF_PRI_PDP_QUERY_INFO_STRU        *pPdpPriPara,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID Aps_QueSec(
    VOS_UINT8                           ucCid,
    TAF_PDP_SEC_CONTEXT_STRU           *pPdpSecPara,
    VOS_UINT32                         *pulErrorCode
);


VOS_VOID Aps_QueQosNeg(
    VOS_UINT8                           ucCid,
    TAF_UMTS_QOS_QUERY_INFO_STRU       *pQosNeg,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID Aps_QueState(
    VOS_UINT8                           ucCid,
    TAF_CID_STATE_STRU                 *pPsState,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID Aps_QueRealIpAddr(
    VOS_UINT8                           ucCid,
    TAF_PDP_ADDR_QUERY_INFO_STRU       *paucIpAddr,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID Aps_QueAuthdata(
    VOS_UINT8                           ucCid,
    TAF_AUTHDATA_QUERY_INFO_STRU       *pAuthDataPara,
    VOS_UINT32                         *pulErrorCode
);

VOS_UINT32  Aps_NvimAct (               VOS_UINT8                   ucCid   );

APS_NVIM_ACT_TYPE Aps_JudegNvimActType( VOS_UINT8                   ucCid   );

VOS_VOID Aps_SetPsAnsMode(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_ANSWER_MODE_ENUM_UINT8      ucAnsMode,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID Aps_QueDns(
    VOS_UINT8                           ucCid,
    TAF_DNS_QUERY_INFO_STRU            *paucDns,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID    TAF_APS_SndCidInactiveEvt(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid
);


VOS_UINT8   *Aps_GetParaPointer(       TAF_PARA_TYPE       ParaType,
                                        VOS_UINT8            *pPrePtr);
VOS_VOID Aps_QueAuth(
    VOS_UINT8                           ucCid,
    TAF_AUTH_QUERY_INFO_STRU           *pAuthQuePara,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID MN_APS_GetUtmsQosInfo(
    VOS_UINT8                           ucCid,
    TAF_UMTS_QOS_QUERY_INFO_STRU       *pstUmtsQosQueryInfo,
    VOS_UINT32                         *pulErrCode
);

VOS_VOID MN_APS_GetUtmsQosMinInfo(
    VOS_UINT8                           ucCid,
    TAF_UMTS_QOS_QUERY_INFO_STRU       *pstUmtsQosQueryInfo,
    VOS_UINT32                         *pulErrCode
);


VOS_VOID TAF_APS_SetTftInfo(
    TAF_TFT_EXT_STRU                   *pstTftInfo,
    VOS_UINT32                         *pulErrCode
);

VOS_VOID TAF_APS_FillTftQryParam(
    VOS_UINT8                           ucCid,
    TAF_TFT_QUREY_INFO_STRU            *pPdpTftPara
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_SetEpsQosInfo(
    TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo,
    VOS_UINT32                         *pulErrCode
);

VOS_VOID TAF_APS_QueEpsQosInfo(
    VOS_UINT8                           ucCid,
    TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo,
    VOS_UINT32                         *pulErrCode
);
#endif

VOS_VOID Aps_DeleteLinkedCidSecPdpContext(
    VOS_UINT8                           ucCid
);


/*-------------------------------------------------------*/
/*          APS�ڲ��ṩ�����̲����ຯ���ӿ�              */
/*-------------------------------------------------------*/
/*=======================��������========================*/
VOS_VOID  Aps_ActJudgePriOrSecAct (     VOS_UINT8                   ucCid,
                                        VOS_UINT8                  *pucResult );


VOS_UINT32  Aps_PackApsActReqPara (     VOS_UINT8                   ucCid,
                                        VOS_UINT8                   ucPdpId,
                                        APS_PDP_ACT_REQ_ST         *pApsActReq  );

VOS_VOID  Aps_CopyAuthToActReqPara(
    CONST TAF_PDP_PCO_AUTH_STRU    *pAuthTab,
    TAF_PDP_PCO_AUTH_STRU          *pActReqParaAuth
);

VOS_VOID  Aps_CopyAddrToActReqPara(
    CONST  VOS_UINT8               *pucIpAddr,
    APS_PDP_ACT_REQ_ST             *pApsActReq
);

TAF_PS_CAUSE_ENUM_UINT32 Aps_PsCallOrigNormCid(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId
);

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-14, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-14, end */
VOS_UINT32  Aps_PackDialActReqPara(     VOS_UINT8                   ucPdpId,
                                        TAF_PSCALL_FOR_DIAL_EXT_STRU *pPsCallDialPara,
                                        APS_PDP_ACT_REQ_ST         *pApsActReq  );

VOS_VOID  Taf_FillQos(                      TAF_PDP_TABLE_STRU         *pTafPdp,
                                        APS_PDP_QOS_STRU           *pApsQos   );

VOS_VOID  Taf_FillMinQos(                   TAF_PDP_TABLE_STRU         *pTafPdp,
                                        APS_PDP_QOS_STRU           *pApsQos   );

VOS_VOID Taf_LenStr2Apn(
    CONST TAF_PDP_APN_STRU              *pstApn,
    VOS_UINT8                           *pucApn
);

VOS_VOID  Taf_LenStr2IpAddr(CONST VOS_UINT8* pucStr, VOS_UINT8 *pucIpAddr);

VOS_UINT32  Aps_PackApsSecActReqPara (  VOS_UINT8                   ucCid,
                                        VOS_UINT8                   ucPdpId,
                                        APS_PDP_SEC_ACT_REQ_ST     *pApsSecActReq );

VOS_UINT32  Aps_FillTft(                TAF_PDP_TABLE_STRU         *pTafPdp,
                                        APS_PDP_TFT_ST             *pApsTft );

VOS_VOID    Aps_FillXid(                TAF_PDP_TABLE_STRU         *pTafPdp,
                                        APS_PDP_ACT_REQ_ST         *pApsActReq  );

VOS_VOID    Aps_FillDns(                TAF_PDP_TABLE_STRU         *pTafPdp,
                                        APS_PDP_ACT_REQ_ST         *pApsActReq  );

VOS_VOID    Aps_FillSecXid(             TAF_PDP_TABLE_STRU         *pTafPdp,
                                        APS_PDP_SEC_ACT_REQ_ST     *pApsSecActReq  );

VOS_VOID    Aps_GetIpcpInfo(            PPP_REQ_CONFIG_INFO_STRU   *pPsDialPara,
                                        TAF_PSCALL_FOR_DIAL_EXT_STRU *pApsDialReqPara);

VOS_UINT32  Aps_GetAuthInfo(            PPP_REQ_CONFIG_INFO_STRU   *pPsDialPara,
                                        TAF_PSCALL_FOR_DIAL_EXT_STRU *pApsDialReqPara);

VOS_VOID    Aps_PPPAddr2ApsAddr(        APS_PCO_PPP_ST             *pOneIpcp,
                                        VOS_UINT8                  *pIpAddr);

VOS_UINT32  Aps_CheckOutOneIpcpOneId(   APS_PCO_IPCP_PPP_ST        *pOneIpcp,
                                        VOS_UINT8                   ucIpcpId,
                                        APS_PPP_ID_ST              *pPppId);

/*=======================�޸�����========================*/


/*-------------------------------------------------------*/
/*       Aps_DealApiFlowMsgSmAct.c ģ��ĺ����ӿ�        */
/*-------------------------------------------------------*/
/*=======================��������========================*/
VOS_UINT32  Aps_PdpActReq(              APS_PDP_ACT_REQ_ST         *pActReq );
VOS_UINT32  Aps_PackSmActReqMsg (       APS_PDP_ACT_REQ_ST         *pActReq,
                                        SMREG_PDP_ACTIVATE_REQ_STRU        *pStPdpActReq);

VOS_VOID    Aps_ActReqFillState(        APS_PDP_ACT_REQ_ST         *pActReq);
VOS_VOID    TAF_APS_SndPdpActivateRej   (        VOS_UINT8                   ucPdpId,
                                        TAF_PS_CAUSE_ENUM_UINT32    enCause );

VOS_UINT32  Aps_PdpSecActReq(           APS_PDP_SEC_ACT_REQ_ST     *pSecActReq);

VOS_VOID    Aps_SecActReqFillState(     APS_PDP_SEC_ACT_REQ_ST     *pSecActReq);

VOS_UINT32  Aps_PdpSecActReqParaCheck ( APS_PDP_SEC_ACT_REQ_ST     *pSecActReq);
VOS_VOID    Aps_PackSmSecActReqMsg(     APS_PDP_SEC_ACT_REQ_ST     *pSecActReq,
                                                    SMREG_PDP_ACTIVATE_SEC_REQ_STRU    *pStSecActReq );

/*=======================�޸�����========================*/
VOS_UINT32  Aps_PdpMdfReq(              APS_PDP_MDF_REQ_ST         *pMdfReq);

VOS_VOID    Aps_PackSmMdfReqMsg(        APS_PDP_MDF_REQ_ST         *pMdfReq,
                                            SMREG_PDP_MODIFY_REQ_STRU       *pStPdpMdfReq   );

VOS_UINT32  Aps_PackApsMdfReqPara (     VOS_UINT8                   ucCid,
                                        VOS_UINT8                   ucPdpId,
                                        APS_PDP_MDF_REQ_ST*         pApsMdfReq  );
VOS_VOID    TAF_APS_SndPdpModifyRej   (        VOS_UINT8                   ucPdpId,
                                        TAF_PS_CAUSE_ENUM_UINT32    enCause );
VOS_VOID    Aps_PdpMdfRsp(              VOS_UINT8                   ucPdpId);

/*=======================ȥ��������======================*/
VOS_UINT32 Aps_AppDeactReq(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
);

VOS_UINT32 Aps_PdpDeActReq(
    APS_PDP_DEACT_REQ_ST               *pDeActReq
);
VOS_VOID    Aps_PdpDeActOneReq(         APS_PDP_DEACT_REQ_ST       *pDeActReq,
                                        VOS_UINT8                   ucRelSmType);
VOS_UINT32  Aps_PdpDeActReqParaCheck(   APS_PDP_DEACT_REQ_ST       *pDeActReq );

/*=======================���̹���ʹ��======================*/
/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-15, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-15, end */

VOS_VOID    Aps_PackSmQos   (           APS_PDP_QOS_ST             *pApsQos,
                                        SM_TAF_QOS_STRU                   *pSmQos  );

VOS_VOID  Aps_PackSmTft   (             VOS_UINT8                   ucPdpId,
                                        APS_PDP_TFT_ST*             pApsTft,
                                        SM_TAF_TFT_STRU*            pSmTft  );

VOS_UINT32  Aps_PackSmAddr  (           VOS_UINT8*                  pucPdpType,
                                        VOS_UINT8*                  pucAppAddr,
                                        SM_TAF_PDP_ADDR_STRU*       pSmAddr );

VOS_VOID    Aps_PackSmApn(              VOS_UINT8                  *pucAppApn,
                                        SM_TAF_APN_STRU                    *pSmApn      );

VOS_UINT32      Aps_QosValidOrNot(          APS_PDP_QOS_STRU           *psQos);

VOS_UINT32  Aps_PackSmPco(              APS_PDP_ACT_REQ_ST         *pActReq,
                                        SM_TAF_PROT_CFG_OPT_STRU           *pSmPco );

VOS_UINT8  *Aps_PackPcoAuth(            APS_PDP_ACT_REQ_ST         *pActReq,
                                        VOS_UINT8                  *pPcoAuthBegin);

VOS_UINT8  *Aps_PackPcoIpcp(            APS_PDP_ACT_REQ_ST         *pActReq,
                                        VOS_UINT8                  *pPcoIpcpBegin);

#if (FEATURE_ON == FEATURE_IPV6)
VOS_UINT8* MN_APS_FillPcoIpV6DnsPara(
    VOS_UINT8                          *pucPcoPkt
);
#endif


/*-------------------------------------------------------*/
/*          Aps_DealSmMsg.c ģ��ĺ����ӿ�               */
/*-------------------------------------------------------*/
/*=======================��������========================*/
VOS_UINT32  Aps_UnpackSmQos (  SM_TAF_QOS_STRU*            pSmQos,
                                        VOS_UINT8*                  pucQosLen,
                                        APS_PDP_QOS_ST*             pApsQos );

/*****************************************************************************
 �� �� ��  : MN_APS_DecodeIpcpConfigReqPkt
 ��������  : ����IPCP���е�CONFIG_REQ
 �������  : pstPdpEntity       - PDPʵ��
             pucProtocolPacket  - �������CONFIG_REQ��Packet��ַ
             usPktLen           - ���CONFIG_REQ��Packet����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 MN_APS_DecodeIpcpConfigReqPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usPktLen
);


/*****************************************************************************
 �� �� ��  : MN_APS_DecodeIpcpConfigNakAckRejPkt
 ��������  : ����IPCP���е�CONFIG_NAK/CONFIG_ACK/CONFIG_REJ
 �������  : pstPdpEntity       - PDPʵ��
             pucProtocolPacket  - �������CONFIG_NAK/CONFIG_ACK/CONFIG_REJ��Packet��ַ
             usPktLen           - ���CONFIG_NAK/CONFIG_ACK/CONFIG_REJ��Packet����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 MN_APS_DecodeIpcpConfigNakAckRejPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usPktLen
);


/*****************************************************************************
 �� �� ��  : MN_APS_DecodeIpcpProtocolPkt
 ��������  : ����IPCP��
 �������  : pstPdpEntity       - PDPʵ��
             pucProtocolPkt     - �������IPCP��Packet��ַ
             usProtocolPktLen   - ���IPCP��Packet����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 MN_APS_DecodeIpcpProtocolPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucProtocolPkt,
    VOS_UINT16                          usProtocolPktLen
);


/*****************************************************************************
 �� �� ��  : TAF_APS_DecodeIpv4PcscfProtocolPkt
 ��������  : ����IPv4 P-CSCF Container
 �������  : pstPdpEntity           - PDPʵ��
             pucIpv6PcscfNum        - �ѽ����IPv6 P-CSCF������
             pucProtocolPacket      - �������IPv6 P-CSCF��Packet��ַ
             usProtocolPacketLen    - ���IPv6 P-CSCF��Packet����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID TAF_APS_DecodeIpv4PcscfProtocolPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucIpv4PcscfNum,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usProtocolPacketLen
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : MN_APS_DecodeIpV6DnsProtocolPkt
 ��������  : ����IPV6 DNS Container
 �������  : pstPdpEntity           - PDPʵ��
             pucIpV6DnsNum          - �ѽ����IPV6 DNS������
             pucProtocolPacket      - �������IPV6 DNS��Packet��ַ
             usProtocolPacketLen    - ���IPV6 DNS��Packet����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_DecodeIpV6DnsProtocolPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucIpV6DnsNum,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usProtocolPacketLen
);


/*****************************************************************************
 �� �� ��  : TAF_APS_DecodeIpv6PcscfProtocolPkt
 ��������  : ����IPV6 P-CSCF Container
 �������  : pstPdpEntity           - PDPʵ��
             pucIpv6PcscfNum        - �ѽ����IPv6 P-CSCF������
             pucProtocolPacket      - �������IPv6 P-CSCF��Packet��ַ
             usProtocolPacketLen    - ���IPv6 P-CSCF��Packet����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID TAF_APS_DecodeIpv6PcscfProtocolPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucIpv6PcscfNum,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usProtocolPacketLen
);
#endif


/*****************************************************************************
 �� �� ��  : MN_APS_DecodeProtocolConfigPara
 ��������  : ����PCO�Ĳ���
 �������  : pstPdpEntity       - PDPʵ��
             pstProtoCfgOptions - PCO��������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 MN_APS_DecodeProtocolConfigPara(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    MN_APS_PROTOCOL_CFG_OPTIONS_STRU   *pstProtoCfgOptions
);


/*****************************************************************************
 �� �� ��  : MN_APS_UnpackProtocolOptionsList
 ��������  : ����Protocol ID���PCO�Ĳ����б�
 �������  : pstProtoCfgOptions - PCO��������
             pstSmPco           - PCOԭʼ����(OTA����)
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 MN_APS_UnpackProtocolOptionsList(
    MN_APS_PROTOCOL_CFG_OPTIONS_STRU   *pstProtoCfgOptions,
    SM_TAF_PROT_CFG_OPT_STRU           *pstSmPco
);


/*****************************************************************************
 �� �� ��  : MN_APS_UnpackPco
 ��������  : ���PCO��DNS/NBNS����Ϣ
 �������  : pstPdpEntity   - PDPʵ��
             pstSmPco       - PCOԭʼ����(OTA����)
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 MN_APS_UnpackPco(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_TAF_PROT_CFG_OPT_STRU           *pstSmPco
);

VOS_UINT32  Aps_CheckOutPcoAuth(        SM_TAF_PROT_CFG_OPT_STRU            *pSmPco,
                                        APS_PCO_AUTH_PPP_ST        *pAuthPcoPPP);

VOS_UINT32  Aps_CheckOutPcoOneIpcp(     APS_PCO_IPCP_PPP_ST        *pIpcpPcpPPP,
                                        VOS_UINT8                   ucPcoCode,
                                        APS_PCO_PPP_ST             *pOneIpcp);

VOS_VOID    Aps_PPPDns2ApsDns(          APS_PCO_PPP_ST             *pOneIpcp,
                                        APS_PDP_DNS_ST             *pPdpDns);
VOS_VOID    Aps_PPPNbns2ApsNbns(          APS_PCO_PPP_ST     *pOneIpcp,
                                        APS_PDP_NBNS_ST     *pPdpNbns);
VOS_VOID    Aps_FillEvtPcoIpcpInfo(VOS_UINT8 *pucIpcpInfo, SM_TAF_PROT_CFG_OPT_STRU *pSmPco);

VOS_UINT32      Aps_DetachSmAddrStru (      SM_TAF_PDP_ADDR_STRU*         pSmAddr,
                                        APS_PDP_ADDR_ST*            pApsAddr  );

VOS_VOID    Aps_DetachSmApn  (          SM_TAF_APN_STRU*   pSmApn,
                                        APS_PDP_APN_ST*             pApsApn );
VOS_UINT32      Aps_CompareQos   (          APS_PDP_QOS_STRU*           pNetNegotQos,
                                        APS_PDP_QOS_STRU*           pUeMinQos,
                                        VOS_UINT8*                      pucQosOkOrNot   );
VOS_VOID    Aps_DecideTransMode(        VOS_UINT8                   ucPdpId,
                                        RABM_TRANS_MODE_ENUM       *pTransMode   );
VOS_UINT32  Aps_CheckPdpType(VOS_UINT8 ucPdpId, SM_TAF_PDP_ADDR_STRU *pSmAddr);
VOS_VOID    Aps_ValidPacketFlowId(VOS_UINT8 *pucPacketFlowId);

/*=======================��������========================*/
VOS_UINT32  Aps_PdpActCnfParaCheck  (   SMREG_PDP_ACTIVATE_CNF_STRU         *pSmActCnfMsg,
                                        APS_ACTCNF_PARA_ST         *pActCnfPara );

VOS_UINT32  Aps_CheckQosSatisify (      VOS_UINT8                   ucPdpId,
                                        APS_PDP_QOS_STRU*           pNetNegotQos);

VOS_UINT32      Aps_GetPsMinQos(            VOS_UINT8                   ucPdpId,
                                        VOS_UINT8                      *pDefinedOrNot,
                                        APS_PDP_QOS_STRU           *pQos );
VOS_VOID    Aps_PdpActCnfQosSatisfy (   VOS_UINT8          ucPdpId,
                                        APS_ACTCNF_PARA_ST          *pActCnfPara,
                                        SMREG_PDP_ACTIVATE_CNF_STRU *pStCnf   );
VOS_VOID    TAF_APS_SndPdpActivateCnf(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);
VOS_VOID TAF_APS_SndPdpActivateInd(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_VOID    Aps_PdpQosNotSatisfy (      VOS_UINT8                   ucPdpId,
                                        APS_QOS_NOT_SATISFY_MSGTYPE_ENUM  QosMsgType );

VOS_UINT32 TAF_APS_SndPdpManageInd(
    VOS_UINT8                           ucPdpId,
    SMREG_PDP_ACTIVATE_IND_STRU        *pStActInd
);
VOS_UINT32 Aps_ActIndAutoAns(
    TAF_PDP_ANSWER_TYPE_ENUM_UINT8                     AnswerType,
    VOS_UINT8                           ucPdpId,
    SMREG_PDP_ACTIVATE_IND_STRU        *pStActInd,
    APS_PDP_ACT_REQ_ST                 *pstApsPdpActReq
);
VOS_UINT32      TAF_APS_GetPsReqPdp(            APS_PDP_ACT_REQ_ST         *pReqPdp);
VOS_VOID    Aps_ActIndRejRsp(           VOS_UINT8                   ucPdpId );

VOS_UINT32  Aps_PdpActSecCnfParaCheck(  SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pStSecCnf,
                                        APS_ACTSECCNF_PARA_ST      *pActSecCnfPara );

VOS_VOID    Aps_PdpActSecCnfQosSatisfy( VOS_UINT8                   ucPdpId,
                                        APS_ACTSECCNF_PARA_ST      *pSecCnfPara,
                                        SMREG_PDP_ACTIVATE_SEC_CNF_STRU   *pStSecCnf   );

VOS_VOID  Aps_GetPsAnswerMode  (
    TAF_PDP_ANSWER_MODE_ENUM_UINT8            *pAnswerMode,
    TAF_PDP_ANSWER_TYPE_ENUM_UINT8            *pAnswerType);
VOS_UINT32  Taf_ComparePdp(             APS_PDP_ACT_REQ_ST         *pApsPdp,
                                        TAF_PDP_PRIM_CONTEXT_STRU           *pTafCidPdp);

VOS_VOID    Aps_CheckAddrWithActPdp(    VOS_UINT8           ucPdpId,
                                        VOS_UINT8          *pucIpAddr);

/*=======================�޸�����========================*/
VOS_UINT32  Aps_PdpMdfCnfParaCheck (    SMREG_PDP_MODIFY_CNF_STRU    *pStMdfCnf,
                                        APS_MDFCNF_PARA_ST         *pMdfCnfPara );
VOS_VOID    Aps_PdpMdfCnfQosSatisfy (   VOS_UINT8                   ucPdpId,
                                        APS_MDFCNF_PARA_ST         *pMdfCnfPara,
                                        SMREG_PDP_MODIFY_CNF_STRU  *pMdfCnf);

VOS_VOID    TAF_APS_SndPdpModifyCnf( VOS_UINT8                   ucPdpId );


VOS_UINT32  Aps_PdpMdfIndParaCheck (    SMREG_PDP_MODIFY_IND_STRU     *pStMdfInd,
                                        APS_MDFIND_PARA_ST         *pMdfIndPara );
VOS_VOID    Aps_PdpMdfIndQosSatisfy (   VOS_UINT8                   ucPdpId,
                                        APS_MDFIND_PARA_ST         *pMdfIndPara,
                                        SMREG_PDP_MODIFY_IND_STRU  *pStMdfInd  );
VOS_VOID    TAF_APS_SndPdpModifyInd( VOS_UINT8                   ucPdpId );

/*=======================ȥ��������======================*/
VOS_VOID    TAF_APS_SndPdpDeActivateCnf(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_VOID    TAF_APS_SndPdpDeActivateInd(
   VOS_UINT8                           ucPdpId,
   TAF_PS_CAUSE_ENUM_UINT32            enCause
);

/*=======================ָʾSNDCP����========================*/
VOS_VOID  Aps_SmMsgModSnActInd  (     APS_INNER_SN_ACT_ST        *pInnerSnActInd,
                                        VOS_UINT8                   ucActCause);
VOS_VOID    Aps_SmMsgModSnActIndParaPack
                            (           APS_INNER_SN_ACT_ST        *pInnerSnActInd,
                                        APS_SNDCP_ACTIVATE_IND_ST  *pSnActIndPara  );

VOS_VOID    Aps_SetSnXidPara(           VOS_UINT8                   ucPdpId,
                                        SN_XID_REQ_ST              *pSnXid  );

VOS_VOID  Aps_SmMsgModSnMdfInd  (     APS_INNER_SN_MDF_ST        *pInnerSnMdfInd );

VOS_VOID    Aps_SmMsgModSnMdfIndParaPack
                            (           APS_INNER_SN_MDF_ST        *pInnerSnMdfInd,
                                        APS_SNDCP_MODIFY_IND_ST    *pSnMdfIndPara   );
VOS_UINT32  Aps_SmMsgModSnDeActInd (    VOS_UINT8                   ucPdpId );

VOS_VOID    Aps_SmMsgModSnDeActIndParaPack
                            (           VOS_UINT8                   ucPdpId,
                                        APS_SNDCP_DEACTIVATE_IND_ST *pSnDeActIndPara );

/*-------------------------------------------------------*/
/*          Aps_DealSNDCPMsg.c ģ��ĺ����ӿ�            */
/*-------------------------------------------------------*/
VOS_VOID    Aps_SnMsgModSnActRsp   (    APS_SNDCP_ACTIVATE_RSP_ST*  pSnActRsp );

VOS_UINT32  Aps_SnMsgModSnActRspParaCheck
                                   (    APS_SNDCP_ACTIVATE_RSP_ST*  pSnActRsp);
VOS_VOID    Aps_SnMsgModSnMdfRsp   (    APS_SNDCP_MODIFY_RSP_ST*    pSnMdfRsp );

VOS_UINT32  Aps_SnMsgModSnMdfRspParaCheck
                                   (    APS_SNDCP_MODIFY_RSP_ST*    pSnActRsp);

VOS_UINT32  Aps_SnMsgModSnDeActRspParaCheck
                                   (    APS_SNDCP_DEACTIVATE_RSP_ST *pSnActRsp);

VOS_VOID    Aps_SnMsgModSnStatusReq(    APS_SNDCP_STATUS_REQ_ST    *pSnStatusReq );

VOS_UINT32  Aps_SnMsgModSnStatusReqParaCheck
                                   (    APS_SNDCP_STATUS_REQ_ST    *pSnActRsp);
VOS_VOID    Aps_FindSapiPdp(            VOS_UINT8                   ucSapi);
VOS_VOID    Aps_FindSapiTransModePdp(   VOS_UINT8                   ucSapi);

VOS_VOID    Aps_SnMsgModSnXidReq(       APS_SN_XID_REQ_MSG         *pSnXidReqMsg );

VOS_UINT32  Aps_SnMsgModSnXidReqParaCheck(
                                        APS_SN_XID_REQ_MSG         *pSnXidReqMsg);

VOS_VOID    Aps_SnMsgModSnXidCnf(       VOS_UINT8                   ucNsapi,
                                        SN_XID_REQ_ST              *pXid );

VOS_VOID    Aps_XidReqEvt(              VOS_UINT8                   ucPdpId );
VOS_VOID    Aps_SnMsgModSnXidRsp(       APS_SN_XID_RSP_MSG         *pSnXidRspMsg );

VOS_VOID    Aps_SnActRspChngEntity(     APS_SNDCP_ACTIVATE_RSP_ST  *pSnActRsp,
                                        VOS_UINT8                   ucPdpId);
VOS_VOID    Aps_SnMdfRspChngEntity(     APS_SNDCP_MODIFY_RSP_ST    *pSnMdfRsp,
                                        VOS_UINT8                   ucPdpId);
VOS_UINT32  Aps_SetRabmTransMode(       RABM_APS_SET_TRANS_MODE_ST *pApsRabmSetTRansMod);

/*-------------------------------------------------------*/
/*          Aps_DealRABMMsg.c ģ��ĺ����ӿ�             */
/*-------------------------------------------------------*/
VOS_VOID    Aps_RabmMsgModStateCheck (  VOS_UINT8                   ucPdpId,
                                        VOS_UINT8                  *pucMatrixRow);

VOS_VOID    Aps_Nop  (                  VOS_UINT8                   ucPdpId );
VOS_VOID    Aps_G2WOnActPending  ( VOS_UINT8    ucPdpId );
VOS_VOID    Aps_RabmMsgDeAct (          VOS_UINT8                   ucPdpId );
VOS_VOID    Aps_RabmMsgDeActSndcp (     VOS_UINT8                   ucPdpId );

VOS_VOID    Aps_RabmMsgActSndcp (       VOS_UINT8                   ucPdpId );
/*
VOS_UINT32  Aps_GetAllNegoRate  (       APS_RABM_ALL_RATE_ST       *pAllRate);

VOS_VOID    Aps_GetOneNegoRate  (       VOS_UINT8                   ucPdpId,
                                        APS_RABM_ONE_RATE_ST       *pOneRate    );
*/
VOS_UINT32  Aps_ChngQosRate2UserRate(
        VOS_UINT8                           ucQosRateExt,
        VOS_UINT8                           ucQosRate
);

VOS_VOID    Aps_DeactAllPdp( VOS_VOID );
VOS_VOID    Aps_Init( VOS_VOID );
VOS_VOID    Aps_DbInit( VOS_VOID );
VOS_VOID    Aps_LoadDefault(VOS_VOID);
VOS_VOID    Aps_PowerOff(VOS_VOID);


/*****************************************************************************
 �� �� ��  : MN_APS_GetPdpCidPara
 ��������  : ��ȡPDP CID����Ϣ
 �������  : TAF_PDP_PRIM_CONTEXT_STRU                   *pstPdpCidInfo
             VOS_UINT8                           ucCid
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_GetPdpCidPara(
    TAF_PDP_PRIM_CONTEXT_STRU                   *pstPdpCidInfo,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 �� �� ��  : TAF_APS_FindCidForDial
 ��������  : ���ҿ��е�CID, ���ڲ���
 �������  : entityState --- PDPʵ��״̬
 �������  : ��
 �� �� ֵ  : VOS_UINT8
*****************************************************************************/
VOS_UINT8 TAF_APS_FindCidForDial(VOS_UINT32  ulAppPid);

/*****************************************************************************
 �� �� ��  : MN_APS_SetPdpCidPara
 ��������  : ����PDP������
 �������  : VOS_UINT16                          usClientId
             TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_SetPdpCidPara(
    VOS_UINT16                          usClientId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
);


/* ����ģ���ṩ��API�ӿ� */

VOS_VOID Aps_UpdateWinsConfig(VOS_UINT8 ucWins);

VOS_UINT8   Taf_PsCallForDialParaCheck( PPP_REQ_CONFIG_INFO_STRU *pPsDialPara);


/*****************************************************************************
 �� �� ��  : TAF_APS_SndPsEvt
 ��������  : ����PS���¼�
 �������  : ulEvtId                    - �¼�ID
             pData                      - �¼���������(��������Ϣͷ)
             ulLength                   - �¼����ݳ���
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
*****************************************************************************/
VOS_UINT32 TAF_APS_SndPsEvt(
    VOS_UINT32                          ulEvtId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvCallOrigReq
 ��������  : ����ID_MN_PS_CALL_ORIG_REQ��Ϣ
 �������  : ucPdpId      --- APSʵ������
             pstDialParam --- ���Ų���
 �������  : ��
 �� �� ֵ  : TAF_PS_CAUSE_ENUM
*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 MN_APS_RcvCallOrigReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_DIAL_PARA_STRU              *pstDialParam
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvCallModifyReq
 ��������  :
 �������  : ucPdpId                    - APSʵ������
             pstCallOrigReq             - �޸�PDP����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvCallModifyReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq,
    VOS_UINT8                          *pucErrCode
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetPdpCtxStateReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPdpCtxStateReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvSetPrimPdpCtxInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID MN_APS_RcvSetPrimPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetPrimPdpCtxInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPrimPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvSetSecPdpCtxInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID MN_APS_RcvSetSecPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetSecPdpCtxInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_VOID MN_APS_RcvGetSecPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvSetTftInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID MN_APS_RcvSetTftInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetTftInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetTftInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvSetUmtsQosInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID MN_APS_RcvSetUmtsQosInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetUmtsQosInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID MN_APS_RcvGetUmtsQosInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvSetUmtsQosMinInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID MN_APS_RcvSetUmtsQosMinInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetUmtsQosMinInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID MN_APS_RcvGetUmtsQosMinInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetDynamicUmtsQosInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID MN_APS_RcvGetDynamicUmtsQosInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetPdpIpAddrInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPdpIpAddrInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvSetAnsModeInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID MN_APS_RcvSetAnsModeInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetAnsModeInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID MN_APS_RcvGetAnsModeInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetDynamicPrimPdpCtxInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetDynamicPrimPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetDynamicSecPdpCtxInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetDynamicSecPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetDynamicTftInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetDynamicTftInfoReq(
    VOS_VOID                           *pMsgData
);


/*****************************************************************************
 �� �� ��  : MN_APS_RcvSetPdpAuthInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvSetPdpAuthInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetPdpAuthInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPdpAuthInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvSetPdpDnsInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvSetPdpDnsInfoReq(
    VOS_VOID                           *pMsgData
);
/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetPdpDnsInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPdpDnsInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvTrigGprsDataReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvTrigGprsDataReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvConfigNbnsFunctionReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID MN_APS_RcvConfigNbnsFunctionReq(
    VOS_VOID                           *pMsgData
);


/*****************************************************************************
 �� �� ��  : MN_APS_RcvSetAuthDataInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_VOID MN_APS_RcvSetAuthDataInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetAuthDataInfoReq
 ��������  :
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID MN_APS_RcvGetAuthDataInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvGetGprsActiveTypeReq
 ��������  : ����ID_MSG_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ��Ϣ
 �������  : pMsgData                   - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : VOS_OK                     - �ɹ�
             VOS_ERR                    - ʧ��
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetGprsActiveTypeReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 �� �� ��  : MN_APS_RcvPppDialOrigReq
 ��������  : ����ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ
 �������  : ucPdpId            --- APSʵ������
             pstPppDialParaInfo --- PPP���Ų���
 �������  : ��
 �� �� ֵ  : TAF_PS_CAUSE_ENUM
*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 MN_APS_RcvPppDialOrigReq(
    VOS_UINT8                           ucPdpId,
    TAF_PPP_DIAL_PARA_STRU             *pstPppDialParaInfo
);

VOS_VOID TAF_APS_SndCallOrigCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_APS_SndCallEndCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_APS_SndCallModifyCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_APS_SndSetPdpCtxStateCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_APS_SndCallAnswerCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucErrCode
);

VOS_VOID TAF_APS_SndCallHangupCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT8                           ucErrCode
);
VOS_VOID TAF_APS_SndPppDialOrigCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

/* Added by y00314741 for CDMA Iteration 11, 2015-4-2, begin */
VOS_UINT32  TAF_APS_SndSetDialModeCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          enCause
);
/* Added by y00314741 for CDMA Iteration 11, 2015-4-2, end */

VOS_UINT32  TAF_APS_SndGetCgmtuValueCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulMtuValue
);

VOS_UINT32  TAF_APS_SndCgmtuValueChangeInd(
    VOS_UINT32                          ulMtuValue
);

VOS_UINT32  TAF_APS_SndGetGprsActiveTypeCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode,
    TAF_CID_GPRS_ACTIVE_TYPE_STRU      *pstCidGprsActiveType
);

#if (FEATURE_ON == FEATURE_IPV6)
VOS_VOID TAF_APS_SndIpv6RaInfoNotifyInd(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucRabId,
    TAF_PDP_IPV6_RA_INFO_STRU           *pstIpv6RaInfo
);
#endif

VOS_UINT32 TAF_APS_ValidatePdpForSnStatusReq(
    VOS_UINT8                           ucPdpId,
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq
);


#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_FillCallEvtPdpAvtivateIndFromL4a(
    TAF_PS_CALL_PDP_MANAGE_IND_STRU    *pstCallEvt,
    APS_L4A_PDP_ACTIVATE_IND_STRU      *pstL4aPdpActivateInd
);
#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_FillEvtPdpType
 ��������  : ��дPS������¼���PDP����
 �������  : pstCallEvtInfo - PS������¼�
             ucPdpId        - ʵ������
 �������  : penPdpType
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID TAF_APS_FillEvtPdpType(
    TAF_PDP_TYPE_ENUM_UINT8            *penPdpType,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);



#if(FEATURE_ON == FEATURE_LTE)


VOS_VOID    Aps_DefPsPdprofmod (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_PROFILE_EXT_STRU           *pPara,
    VOS_UINT32                         *pulErrCode
);


#endif

VOS_VOID TAF_APS_RcvSetCidPara_PdpActLimit(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
);
VOS_VOID TAF_APS_RcvSetPrimPdpCtxInfoReq_PdpActLimit(
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU    *pstSetPdpCtxInfoReq
);

/* Deleted by wx270776 for OM�ں�, 2015-7-1, begin */

/* Deleted by wx270776 for OM�ں�, 2015-7-1, end */


VOS_VOID TAF_APS_SndDsFlowOMRptInd(
    TAF_DSFLOW_REPORT_STRU             *pstDsFlowRptInfo
);

VOS_UINT8 TAF_APS_FindCidForAns(VOS_VOID);

VOS_VOID TAF_APS_MakeIpTypeAnsExtActReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq,
    APS_PDP_ACT_REQ_ST                 *pApsActReq
);

VOS_UINT32 TAF_APS_GetPdpCidQosPara(
    TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosPara,
    VOS_UINT8                           ucCid
);
VOS_UINT32 TAF_APS_SetPdpCidQosPara(
    TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosPara
);


/*****************************************************************************
 �� �� ��  : TAF_APS_GetSdfParaInfo
 ��������  : ��ȡ����NV��SDF����
 �������  : ucCid                      - CID
 �������  : pstSdfParaInfo             - CID��Ӧ��SDF����
 �� �� ֵ  : VOS_OK                     - CID��Ӧ��SDF������Ч, ��ȡ�ɹ�
             VOS_ERR                    - CID��Ӧ��SDF������Ч, ��ȡʧ��
*****************************************************************************/
VOS_UINT32 TAF_APS_GetSdfParaInfo(
    VOS_UINT8                           ucCid,
    TAF_SDF_PARA_STRU                  *pstSdfParaInfo
);

VOS_VOID  Aps_MakeAnsActReq (
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    APS_PDP_ACT_REQ_ST                 *pApsActReq
);


/*****************************************************************************
 �� �� ��  : TAF_APS_ConvertLocalPdpTab2NvPdpTab
 ��������  : LOCAL PDP��ṹת����NV PDP��ṹ
 �������  : pstLocalPdpTab --- LOCAL PDP TABLE
 �������  : pstNvPdpTab    --- NV PDP TABLE
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID TAF_APS_ConvertLocalPdpTab2NvPdpTab(
    CONST TAF_PDP_TABLE_STRU           *pstLocalPdpTab,
    TAF_NV_PDP_TABLE_STRU              *pstNvPdpTab
);

/*****************************************************************************
 �� �� ��  : TAF_APS_ConvertNvPdpTab2LocalPdpTab
 ��������  : NV PDPPDP��ṹת����LOCAL PDP��ṹ
 �������  : pstNvPdpTab    --- NV PDP TABLE
 �������  : pstLocalPdpTab --- LOCAL PDP TABLE
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID TAF_APS_ConvertNvPdpTab2LocalPdpTab(
    CONST TAF_NV_PDP_TABLE_STRU        *pstNvPdpTab,
    TAF_PDP_TABLE_STRU                 *pstLocalPdpTab
);

VOS_UINT32  TAF_APS_SndSetUmtsQosInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
);

VOS_UINT32  TAF_APS_SndSetUmtsQosMinInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_SetEvtTftInfo(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_TFT_STRU                   *pstTft
);
#endif

VOS_VOID TAF_APS_ProcUsimMsg(
    struct MsgCB                       *pstMsg
);

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

#endif /* end of Taf_Aps.h*/
