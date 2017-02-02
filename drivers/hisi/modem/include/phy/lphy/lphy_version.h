/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : lphy_version.h
  �� �� ��   : ����
  ��    ��   : tuzhiguo(52067)
  ��������   : 2011��11��08��
  ����޸�   :
  ��������   :

        һ. Ŀǰ���ڵ�оƬ��, ����:
            1) HI6920_ES: ��ӦMPW�汾
                1.1> HI6920ES_FPGA_P500: MPW FPGA��֤ƽ̨
                1.2> HI6920ES_ASIC:      MPW ASICоƬ
            2) HI6920_CS: ��ӦPILOT�汾
                2.1> HI6920CS_FPGA_P500: PILOT FPGA��֤ƽ̨
                2.2> HI6920CS_ASIC:      PILOT ASICоƬ

        ��. ��Ե�ǰ��ƽ̨����, �ֱ����LPHY��Ϊ�����İ汾����, ����:
            1) HI6920_ES: ��ӦMPW�汾
                1.1> LPHY_HI6920ES_FPGA_P500: MPW FPGA��֤ƽ̨
                1.2> LPHY_HI6920ES_ASIC:      MPW ASICоƬ
            2) HI6920_CS: ��ӦPILOT�汾
                2.1> LPHY_HI6930CS_FPGA_P500: PILOT FPGA��֤ƽ̨
                2.2> LPHY_HI6930CS_ASIC:      PILOT ASICоƬ

        ��. ���ļ��Ȱ����ⲿ��Ʒͷ�ļ�, ���ݲ�Ʒ�������ǰ�İ汾��

******************************************************************************/

#ifndef __LPHY_VERSION_H__
#define __LPHY_VERSION_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "TLPhyInterface.h"
/***********************************************************

һ. ��Ʒ�汾�궨��, Ŀǰ���ڵ�оƬ��, ����:
    1.1) HI6920_ES: ��ӦMPW�汾
        1.1.1> HI6920ES_FPGA_P500: MPW FPGA��֤ƽ̨
        1.1.2> HI6920ES_ASIC:      MPW ASICоƬ
    1.2) HI6920_CS: ��ӦPILOT�汾
        1.2.1> HI6920CS_FPGA_P500: PILOT FPGA��֤ƽ̨
        1.2.2> HI6920CS_ASIC:      PILOT ASICоƬ

��). ��Ե�ǰ�Ĳ�Ʒ�汾, �ֱ����LPHY��Ϊ�����İ汾����, ����:
    1) HI6920_ES: ��ӦMPW�汾
        1.1> LPHY_HI6920ES_FPGA_P500: MPW FPGA��֤ƽ̨
        1.2> LPHY_HI6920ES_ASIC:      MPW ASICоƬ
    2) HI6920_CS: ��ӦPILOT�汾
        2.1> LPHY_HI6930CS_FPGA_P500: PILOT FPGA��֤ƽ̨
        2.2> LPHY_HI6930CS_ASIC:      PILOT ASICоƬ

��). �����汾�汾�궨��
    �еĴ���ֻ����ES/CS, ����ֻ����FPGA_P500/ASIC Ҳ������Щ��صĺ깩����

    1) оƬ�ͺ�: ES or CS
        1.1> LPHY_HI6920ES           "HI6920ES"      //mpw
        1.2> LPHY_HI6930CS           "HI6930CS"      //pilot
    2) оƬƽ̨
        2.1> LPHY_FPGA_P500          "FPGA_P500"     //FPGA P500��֤ƽ̨
        2.2> LPHY_ASIC               "ASIC"          //ASIC��Ƭƽ̨

****************************************************************/


#define PHY_ON		(0x1)
#define PHY_OFF		(0x0)

/*-------------------------------------------------------------------------*
   ���汾�����һ��32λ��, ��Ҫ����������
    1)����ֱ�����ɰ汾�ŵĺ�:
        MAJOR   : LPHY_HI6920ES(0xE0) or LPHY_HI6930CS(0xC0)
        MINOR   : LPHY_FPGA_P500(0xF0) or LPHY_ASIC(0xA0)
        NUMBER  : B001,B002,.....,B060,.....
    2)����LPHY_HI6920_CS_FPGA_P500�����ֱ�ʾΪ:
        0xC0F0B001----> CS�汾FPGAƽ̨B001�汾
 *-------------------------------------------------------------------------*/
#define LPHY_MAJOR_VERSION(x)                (x)
#define LPHY_MINOR_VERSION(x)                (x)
#define LPHY_NUMBER_VERSION(x)               (x)
#define LPHY_VERSION(MAJOR, MINOR, NUMBER)   MAJOR MINOR NUMBER

#define LPHY_MAIN_VERSION      LPHY_VERSION(CHIP_BB_VERSION, LPHY_BOARD_VERSION, "C00B001")

/*-------------------------------------------------------------------------*
 *      оƬ����
 *-------------------------------------------------------------------------*/
#if defined(LPHY_CHIP_BB_6930CS)
    #define LPHY_HI6930CS             "DO_NOT_USE"
    #define CHIP_BB_VERSION           "HI6930CS"
#elif defined(LPHY_CHIP_BB_6950CS)
    #define CHIP_BB_VERSION           "HI6950CS"
#else
    #error "sorry, this is not a supported baseband version"
#endif



/*-------------------------------------------------------------------------*
 *      ����/оƬƽ̨����
 *-------------------------------------------------------------------------*/
#if defined(LPHY_FPGA)
	 #define LPHY_BOARD_VERSION      					LPHY_FPGA
#else
	 #define LPHY_BOARD_VERSION      					LPHY_ASIC
#endif


/*-------------------------------------------------------------------------*
 *    ����/оƬƽ̨&���Բ���                                               *
 *-------------------------------------------------------------------------*/
#if defined(LPHY_ASIC_B720)
	#define LPHY_FEATURE_LCS_SWITCH						PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH					PHY_ON
	#define LPHY_FEATURE_ONE_XO_SWITCH					PHY_OFF
	#define LPHY_FEATURE_WIFI_SWITCH		            PHY_ON
	#define LPHY_FEATURE_CL_SWITCH                      PHY_ON
	#define LPHY_FEATURE_LDSDS_SWITCH	    			PHY_OFF
	#define LPHY_FEATURE_TAS_SWITCH         			PHY_OFF
	#define LPHY_FEATURE_MAXPWR_FROM_NV_SWITCH  		PHY_OFF
	#define LPHY_FEATURE_MAX_CARRIER_NUM				2
    #define LPHY_FEATURE_MAX_INTER_EMU_NUM				6
	#define LPHY_CLK_RATE_IN_MHZ 						400

    #define SG_REPORT
	#define LPHY_IN_FACT_ASIC_BOARD
	#define BALONG_FEATURE_LTE_DT

#elif (defined(LPHY_ASIC_K3V3))

	#define LPHY_FEATURE_LCS_SWITCH						PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH					PHY_ON
	#define LPHY_FEATURE_ONE_XO_SWITCH					PHY_OFF
	#define LPHY_FEATURE_WIFI_SWITCH		            PHY_ON
	#define LPHY_FEATURE_CL_SWITCH                      PHY_ON
	#define LPHY_FEATURE_LDSDS_SWITCH	    			PHY_OFF
	#define LPHY_FEATURE_TAS_SWITCH         			PHY_OFF
	#define LPHY_FEATURE_MAXPWR_FROM_NV_SWITCH  		PHY_OFF
	#define LPHY_FEATURE_MAX_CARRIER_NUM				2
    #define LPHY_FEATURE_MAX_INTER_EMU_NUM				6
	#define LPHY_CLK_RATE_IN_MHZ 						400


    #define SG_REPORT
    #define LPHY_IN_FACT_ASIC_BOARD
	#define BALONG_FEATURE_LTE_DT

    /* austin_asic_chip_edit zhangning start */
    #define LPHY_FEATURE_MEM_REPAIR
    /* austin_asic_chip_edit zhangning end */
#elif (defined(LPHY_ASIC_V810))

	#define LPHY_FEATURE_LCS_SWITCH						PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH					PHY_OFF
	#define LPHY_FEATURE_ONE_XO_SWITCH					PHY_ON
	#define LPHY_FEATURE_WIFI_SWITCH		            PHY_OFF
	#define LPHY_FEATURE_CL_SWITCH                      PHY_OFF
    #define LPHY_FEATURE_LDSDS_SWITCH       			((FEATURE_DSDS == FEATURE_ON) ? PHY_ON : PHY_OFF)
	#define LPHY_FEATURE_TAS_SWITCH         			((FEATURE_TAS == FEATURE_ON) ? PHY_ON : PHY_OFF)
	#define LPHY_FEATURE_MAXPWR_FROM_NV_SWITCH  		PHY_OFF
	#define LPHY_FEATURE_MAX_CARRIER_NUM				1
    #define LPHY_FEATURE_MAX_INTER_EMU_NUM				6
	#define LPHY_CLK_RATE_IN_MHZ 						300


	#define SG_REPORT
	#define LPHY_IN_FACT_ASIC_BOARD
    /* austin_asic_chip_edit zhangning start */
    #define LPHY_FEATURE_WAKE_SLICE
    /* austin_asic_chip_edit zhangning end */


#elif (defined(LPHY_ASIC_K3V5))

	#define SG_REPORT
	#define LPHY_IN_FACT_ASIC_BOARD

	#define LPHY_FEATURE_LCS_SWITCH						PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH					PHY_OFF
	#define LPHY_FEATURE_ONE_XO_SWITCH					PHY_ON
	#define LPHY_FEATURE_WIFI_SWITCH		            PHY_ON
	#define LPHY_FEATURE_CL_SWITCH                      PHY_OFF
    #define LPHY_FEATURE_LDSDS_SWITCH       			((FEATURE_DSDS == FEATURE_ON) ? PHY_ON : PHY_OFF)
	#define LPHY_FEATURE_TAS_SWITCH         			((FEATURE_TAS == FEATURE_ON) ? PHY_ON : PHY_OFF)
	#define LPHY_FEATURE_MAXPWR_FROM_NV_SWITCH  		PHY_ON
	#define LPHY_FEATURE_MAX_CARRIER_NUM				2
    #define LPHY_FEATURE_MAX_INTER_EMU_NUM				10

#if defined(LPHY_IN_FACT_ASIC_BOARD)
	#define LPHY_CLK_RATE_IN_MHZ 						400
#else
	#define LPHY_CLK_RATE_IN_MHZ 						38
#endif

    /* austin_asic_chip_edit zhangning start */
    #define LPHY_FEATURE_WAKE_SLICE
    /* austin_asic_chip_edit zhangning end */

	#define LPHY_MBX_RTT_CBT_SWITCH                     PHY_ON
    #define LPHY_FEATURE_MEM_REPAIR

#elif (defined(LPHY_ASIC_V711))

	#define LPHY_FEATURE_LCS_SWITCH						PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH					PHY_OFF
	#define LPHY_FEATURE_ONE_XO_SWITCH					PHY_OFF
	#define LPHY_FEATURE_WIFI_SWITCH		            PHY_ON
	#define LPHY_FEATURE_CL_SWITCH                      PHY_ON
	#define LPHY_FEATURE_LDSDS_SWITCH	    			PHY_OFF
	#define LPHY_FEATURE_TAS_SWITCH         			PHY_OFF
	#define LPHY_FEATURE_MAXPWR_FROM_NV_SWITCH  		PHY_ON
	#define LPHY_FEATURE_MAX_CARRIER_NUM				1
    #define LPHY_FEATURE_MAX_INTER_EMU_NUM			    6
	#define LPHY_CLK_RATE_IN_MHZ 						300


	#define SG_REPORT
	#define LPHY_IN_FACT_ASIC_BOARD

#elif (defined(LPHY_FPGA_V750) || defined(LPHY_ASIC_V750))

	#define SG_REPORT

	#define LPHY_FEATURE_LCS_SWITCH			      		PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH					PHY_ON
	#define LPHY_FEATURE_ONE_XO_SWITCH					PHY_ON
	#define LPHY_FEATURE_WIFI_SWITCH		           	PHY_OFF
	#define LPHY_FEATURE_CL_SWITCH                    	PHY_OFF
	#define LPHY_FEATURE_LDSDS_SWITCH       			PHY_OFF
	#define LPHY_FEATURE_TAS_SWITCH         			PHY_OFF
	#define LPHY_FEATURE_MAXPWR_FROM_NV_SWITCH  		PHY_ON
	#define LPHY_FEATURE_TM9_SWITCH                     PHY_ON
	#define LPHY_FEATURE_4X4_MIMO_SWITCH                PHY_ON
	#define LPHY_FEATURE_MAX_RX_ANTENA_NUM				4
	#define LPHY_FEATURE_MAX_INTER_EMU_NUM				9
	#define LPHY_MAX_UL_CARRIER_NUM 					2
	#define LPHY_MAX_RFIC_NUM                           2
	#define LPHY_MBX_RTT_CBT_SWITCH                     PHY_ON
	#define LPHY_MAX_DL_CH_NUM                          (2 * LPHY_MAX_RFIC_NUM)
	#define LPHY_MAX_UL_CH_NUM                          (LPHY_MAX_RFIC_NUM)

#if defined(LPHY_FPGA)
	#define LPHY_FEATURE_MAX_CARRIER_NUM				4
	#define LPHY_CLK_RATE_IN_MHZ 						(400)
	#define LPHY_FEATURE_IMAGE_SFT_SMALL_SWITCH         PHY_OFF
#elif defined(LPHY_SFT)
	#define LPHY_FEATURE_MAX_CARRIER_NUM				1
	#define LPHY_CLK_RATE_IN_MHZ 						(38)
	#define LPHY_FEATURE_IMAGE_SFT_SMALL_SWITCH         PHY_ON
#else	/*LPHY_ASIC*/
	#define LPHY_FEATURE_MAX_CARRIER_NUM				4
	#define LPHY_CLK_RATE_IN_MHZ 						(450)
	#define LPHY_FEATURE_IMAGE_SFT_SMALL_SWITCH         PHY_OFF
	#define LPHY_IN_FACT_ASIC_BOARD
#endif

#elif (defined(LPHY_ASIC_V850) || defined(LPHY_FPGA_V850))

	#define LPHY_FEATURE_LCS_SWITCH			      		PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH					PHY_OFF
	#define LPHY_FEATURE_ONE_XO_SWITCH					PHY_ON
	#define LPHY_FEATURE_WIFI_SWITCH		            PHY_ON
	#define LPHY_FEATURE_CL_SWITCH                      PHY_ON
	#define LPHY_FEATURE_LDSDS_SWITCH       			PHY_OFF//((FEATURE_DSDS  == FEATURE_ON) ? PHY_ON : PHY_OFF)
	#define LPHY_FEATURE_TAS_SWITCH         			((FEATURE_TAS  == FEATURE_ON) ? PHY_ON : PHY_OFF)
	#define LPHY_FEATURE_MAXPWR_FROM_NV_SWITCH  		PHY_ON
	#define LPHY_FEATURE_TM9_SWITCH                     PHY_ON
	#define LPHY_FEATURE_4X4_MIMO_SWITCH                PHY_OFF
	#define LPHY_FEATURE_MAX_RX_ANTENA_NUM				2
	#define LPHY_FEATURE_MAX_CARRIER_NUM				2
    #define LPHY_FEATURE_MAX_INTER_EMU_NUM				6
	#define LPHY_MAX_UL_CARRIER_NUM 					2
	#define LPHY_MAX_RFIC_NUM                           1
	#define LPHY_MBX_RTT_CBT_SWITCH                     PHY_ON
	#define SG_REPORT
    #define TLPHY_DSDS_SCHED_ENABLE
	#define TLPHY_FEATURE_TWO_RF_DSDS
	#define LPHY_FEATURE_VRAMP_PA_SWITCH			    PHY_ON

	#define LPHY_MAX_DL_CH_NUM                          (2 * LPHY_MAX_RFIC_NUM)
	#define LPHY_MAX_UL_CH_NUM                          (LPHY_MAX_RFIC_NUM)
    #if     defined(LPHY_FPGA)
    	#define LPHY_CLK_RATE_IN_MHZ 					450
    #elif   defined(LPHY_SFT)
    	#define LPHY_CLK_RATE_IN_MHZ 					38
    #else
    	#define LPHY_CLK_RATE_IN_MHZ 					350
    	#define LPHY_IN_FACT_ASIC_BOARD
    #endif

#elif (defined(LPHY_ASIC_V722) || defined(LPHY_FPGA_V722))

	#define LPHY_FEATURE_LCS_SWITCH			      		PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH					PHY_OFF
	#define LPHY_FEATURE_ONE_XO_SWITCH					PHY_ON
	#define LPHY_FEATURE_WIFI_SWITCH		            PHY_ON
	#define LPHY_FEATURE_CL_SWITCH                      PHY_ON
	#define LPHY_FEATURE_LDSDS_SWITCH       			((FEATURE_DSDS == FEATURE_ON) ? PHY_ON : PHY_OFF)
	#define LPHY_FEATURE_TAS_SWITCH         			((FEATURE_TAS  == FEATURE_ON) ? PHY_ON : PHY_OFF)
	#define LPHY_FEATURE_MAXPWR_FROM_NV_SWITCH  		PHY_ON
	#define LPHY_FEATURE_TM9_SWITCH                     PHY_ON
	#define LPHY_FEATURE_4X4_MIMO_SWITCH                PHY_OFF
	#define LPHY_FEATURE_MAX_RX_ANTENA_NUM				2
	#define LPHY_FEATURE_MAX_CARRIER_NUM				2
    #define LPHY_FEATURE_MAX_INTER_EMU_NUM				6
	#define LPHY_MAX_UL_CARRIER_NUM 					2
	#define LPHY_MAX_RFIC_NUM                           2
	#define LPHY_MBX_RTT_CBT_SWITCH                     PHY_ON
	#define SG_REPORT
	#define LPHY_MAX_DL_CH_NUM                          (LPHY_MAX_RFIC_NUM)
	#define LPHY_MAX_UL_CH_NUM                          (LPHY_MAX_RFIC_NUM)
    #define LPHY_FEM_CHAN_COMB                          (PHY_ON)                       /*ǰ��ͨ������*/

	#define LPHY_FEATURE_VRAMP_PA_SWITCH			    PHY_ON
    #if     defined(LPHY_FPGA)
    	#define LPHY_CLK_RATE_IN_MHZ 					450
    #elif   defined(LPHY_SFT)
    	#define LPHY_CLK_RATE_IN_MHZ 					38
    #else
    	#define LPHY_CLK_RATE_IN_MHZ 					350
    	#define LPHY_IN_FACT_ASIC_BOARD
    #endif
#elif (defined(LPHY_ASIC_K3V6) || defined(LPHY_FPGA_K3V6))

	#define LPHY_FEATURE_LCS_SWITCH			      		PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH					PHY_OFF
	#define LPHY_FEATURE_ONE_XO_SWITCH					PHY_ON
	#define LPHY_FEATURE_WIFI_SWITCH		            PHY_ON
	#define LPHY_FEATURE_CL_SWITCH                      PHY_ON
	#define LPHY_FEATURE_LDSDS_SWITCH       			((FEATURE_DSDS == FEATURE_ON) ? PHY_ON : PHY_OFF)
	#define LPHY_FEATURE_TAS_SWITCH         			((FEATURE_TAS  == FEATURE_ON) ? PHY_ON : PHY_OFF)
	#define LPHY_FEATURE_MAXPWR_FROM_NV_SWITCH  		PHY_ON
	#define LPHY_FEATURE_TM9_SWITCH                     PHY_ON
	#define LPHY_FEATURE_4X4_MIMO_SWITCH                PHY_OFF
	#define LPHY_FEATURE_MAX_RX_ANTENA_NUM				2
	#define LPHY_FEATURE_MAX_CARRIER_NUM				2
    #define LPHY_FEATURE_MAX_INTER_EMU_NUM				6
	#define LPHY_MAX_UL_CARRIER_NUM 					2
	#define LPHY_MAX_RFIC_NUM                           1
	#define LPHY_MBX_RTT_CBT_SWITCH                     PHY_ON
	#define SG_REPORT
	#define LPHY_MAX_DL_CH_NUM                          (2 * LPHY_MAX_RFIC_NUM)
	#define LPHY_MAX_UL_CH_NUM                          (LPHY_MAX_RFIC_NUM)

    #if     defined(LPHY_FPGA)
    	#define LPHY_CLK_RATE_IN_MHZ 					450
    #elif   defined(LPHY_SFT)
    	#define LPHY_CLK_RATE_IN_MHZ 					38
    #else
    	#define LPHY_CLK_RATE_IN_MHZ 					350
    	#define LPHY_IN_FACT_ASIC_BOARD
    #endif

#else
    #error "sorry, this is not a supported asic version, please include product_config.h"
#endif


#if (PHY_ON == LPHY_FEATURE_IMAGE_SFT_SMALL_SWITCH)

	#define LPHY_FEATURE_IMAGE_SFT_SMALL_ENABLE
	#define LPHY_FEATURE_IMAGE_SFT_SMALL
#else
	#define LPHY_FEATURE_IMAGE_SFT_SMALL_DISABLE
#endif


#if (PHY_ON == LPHY_FEATURE_TM9_SWITCH)
	#define BALONGV7_FEATURE_TM9_ENABLE
	#define BALONGV7_FEATURE_TM9
#else
	#define BALONGV7_FEATURE_TM9_DISABLE
#endif

#if (PHY_ON == LPHY_FEATURE_LCS_SWITCH)
	#define BALONGV7_FEATURE_LCS_ENABLE
	#define BALONGV7_FEATURE_LCS
#else
	#define BALONGV7_FEATURE_LCS_DISABLE
#endif

#if (PHY_ON == LPHY_FEATURE_EMBMS_SWITCH)
	#define BALONGV7_FEATURE_EMBMS_ENABLE
	#define BALONGV7_FEATURE_EMBMS
#else
	#define BALONGV7_FEATURE_EMBMS_DISABLE
#endif


#if (PHY_ON == LPHY_FEATURE_ONE_XO_SWITCH)
	#define LPHY_FEATURE_ONE_XO_ENABLE
	#define LPHY_FEATURE_ONE_XO
#else
	#define LPHY_FEATURE_ONE_XO_DISABLE
#endif

#if (PHY_ON == LPHY_FEATURE_LDSDS_SWITCH)
    #define LPHY_FEATURE_LDSDS_ENABLE
	#define LPHY_FEATURE_DSDS
    #define TPHY_FEATURE_DSDS
	#define TLPHY_FEATURE_DSDS
#else
	#define LPHY_FEATURE_LDSDS_DISABLE
#endif

#if (PHY_ON == LPHY_FEATURE_WIFI_SWITCH)
	#define LPHY_FEATURE_WIFI_ENABLE
	#define TLPHY_FEATURE_WIFI
#else
	#define LPHY_FEATURE_WIFI_DISABLE
#endif
/*CDMA��LTE��ģ����*/
#if (PHY_ON == LPHY_FEATURE_CL_SWITCH)
	#define LPHY_FEATURE_CL_ENABLE
	#define TLPHY_FEATURE_CL
#else
	#define LPHY_FEATURE_CL_DISABLE
#endif

#if (PHY_ON == LPHY_FEATURE_TAS_SWITCH)
	#define LPHY_FEATURE_TS_ENABLE
	#define LPHY_FEATURE_TAS
#else
	#define LPHY_FEATURE_TAS_DISABLE
#endif

#if   (1 == LPHY_FEATURE_MAX_CARRIER_NUM)
	#define LPHY_FEATURE_CA_DISABLE
#elif (2 <= LPHY_FEATURE_MAX_CARRIER_NUM)
	#define LPHY_FEATURE_CA_ENABLE
#else
	#error "Error: unsupported carrier number"
#endif

#if (PHY_ON == LPHY_FEATURE_MAXPWR_FROM_NV_SWITCH)
	#define LPHY_FEATURE_MAXPWR_FROM_NV_ENABLE
	#define LPHY_FEATURE_MAXPWR_FROM_NV
#else
	#define LPHY_FEATURE_MAXPWR_FROM_NV_DISABLE
#endif

#if (PHY_ON == LPHY_MBX_RTT_CBT_SWITCH)
    #define MBX_RTT_CBT_ENABLE
    #define MBX_RTT_CBT
#else
    #define MBX_RTT_CBT_DISABLE
#endif

#if (PHY_ON == LPHY_FEATURE_4X4_MIMO_SWITCH)
	#define LPHY_FEATURE_4X4_MIMO_ENABLE
	#define LPHY_FEATURE_4X4_MIMO
#else
	#define LPHY_FEATURE_4X4_MIMO_DISABLE
#endif

#if (PHY_ON == LPHY_FEATURE_VRAMP_PA_SWITCH)
	#define LPHY_FEATURE_VRAMP_PA_ENABLE
#else
	#define LPHY_FEATURE_VRAMP_PA_DISABLE
#endif


/*RF���Ͷ���*/

/*����CHIP_BB_6920CS porting�汾�ںа��Ĳ���ȫ���������Ҫ���쳣�����ų�һ���ּĴ���������*/
#if (defined(CHIP_BB_6920CS) && defined(BOARD_SFT))
    #define LPHY_HI6930CS_PORTING
#endif


/*
    LPHY�ڲ�ǿ�ƽ�ֹʹ�ö�����Ĳ�Ʒ��
*/
#undef BOARD_FPGA_P500
#undef BOARD_ASIC
#undef BOARD_ASIC_BIGPACK
#undef BOARD_SFT
#undef CHIP_BB_6920CS
#undef CHIP_BB_6920ES
#undef CHIP_RFIC_6360V200
#undef CHIP_RFIC_6360V210
#undef CHIP_RFIC_9361


/*�汾�����ַ���*/
#define LPHY_TIP "Hisilicon balongV7R2 GUTL lphy develop group!"


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LPHY_VERSION_H__ */
