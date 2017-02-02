

#ifndef __RCMPHYINTERFACE_H__
#define __RCMPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"

#ifndef LPS_RTT
#include "vos.h"
#include "phyoaminterface.h"
#include "PhyCodecInterface.h"

#else
#define VOS_MSG_HEADER
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*���֧�ֵ�RF��Ŀ*/
#define RCM_RF_SUPPORT_NUM                      ( RCM_RF_ID_BUTT )

/*���֧�ֵ�PHY mode��Ŀ*/
#define RCM_MODE_SUPPORT_NUM                    ( RCM_MODE_ID_BUTT )

/*���֧�ֵ�MODEM��Ŀ*/
#define RCM_MODEM_SUPPORT_NUM                   ( RCM_MODEM_ID_BUTT )

/*���֧�ֵ�MODEM��Ŀ*/
#define RCM_TAS_MODEM_SUPPORT_NUM               ( RCM_TAS_MODEM_ID_BUTT )

/* �����������size */
#define RCM_PHY_ASSIGN_BUF_SIZE                 ( 32 )

/* ������ʱ�������ڣ���32Kʱ��Ϊ��λ��������2��ָ�� */
#define RCM_CLOCK_PERIOD                        ( ((VOS_UINT32)0x1)<<31 )

/* ������ʱƵ�� */
#define RCM_CLOCK_FREQUENCY                     ( 32768 )

/* ��Ч��ʱ ͬʱ��Ϊ���ʱ�� */
#define RCM_CLOCK_INVALID_VALUE                 ( 0xffffffff )

/* ���κ��ۻ�����ռ����,��ռͳ��������Чֵ(��PSҵ��ͳһ���ֵ) */
#define RCM_PRMPT_TH_INVALID_VALUE              ( RCM_CLOCK_INVALID_VALUE )

/* ʱ��msת��Ϊ32K�ļ��� �������С��0x20000 ms*/
#define RCM_MsToClock( M_uhwTime )              ( (VOS_INT32)( ( ((VOS_UINT32)M_uhwTime) *RCM_CLOCK_FREQUENCY)/1000 ))

/* GPHY TASK ID ��ӦRCM TASK ID ��ʼö��ֵ */
#define RCM_GPHY_TASK_ID_BEGIN_NUM              ( 0 )

/* WPHY TASK ID ��ӦRCM TASK ID ��ʼö��ֵ */
#define RCM_WPHY_TASK_ID_BEGIN_NUM              ( 100 )

/* TPHY TASK ID ��ӦRCM TASK ID ��ʼö��ֵ */
#define RCM_TPHY_TASK_ID_BEGIN_NUM              ( 200 )

/* LPHY TASK ID ��ӦRCM TASK ID ��ʼö��ֵ */
#define RCM_LPHY_TASK_ID_BEGIN_NUM              ( 300 )

/* CPHY 1X TASK ID ��ӦRCM TASK ID ��ʼö��ֵ */
#define RCM_CPHY_1X_TASK_ID_BEGIN_NUM           ( 400 )

/* CPHY HRPD TASK ID ��ӦRCM TASK ID ��ʼö��ֵ */
#define RCM_CPHY_HRPD_TASK_ID_BEGIN_NUM         ( 500 )


/* һ��ɾ��������ID������ */
#define RCM_REL_TASK_ID_MAX_NUM                 ( 32 )

/* ��ģͳһѰ����������ڶ�̬���ȼ�������ʧ������
   Gģ��ѡ���������ȼ�Ϊ260��ÿ940msϣ���յ�һ��ϵͳ��Ϣ��Ѱ����������ȼ�Ϊ300������Ѱ������Ϊ470ms��
   �����ѡ��Ѱ����ͻʱ����ѡϣ���ܹ���һ��940ms֮���յ�һ��ϵͳ��Ϣ������Ѱ����������ȼ������ٶȽ���
   ��ÿʧ�����β��ܳ�����ѡ������Ѱ����������ȼ������㷨��������뽫ʧ����������Ϊ6 */
#define RCM_PHY_PAGING_FAIL_THD                 ( 6 )

/* Ϊ�������������ľ��ȣ�PHY����RCM������ֵ����ı��� */
#define EXTEND_PERIOD_TASK_TIMES                ( ((VOS_UINT32)0x1)<<7 )

/* ����������������λ */
#define RCM_GetTaskPeriod( M_uwPeriod )         ( (((VOS_UINT32)M_uwPeriod) & (~( EXTEND_PERIOD_TASK_TIMES - 1 )))>>7 )

/* ����������������λ */
#define RCM_GetTaskRemainder( M_uwPeriod )      ( ((VOS_UINT32)M_uwPeriod) & ( EXTEND_PERIOD_TASK_TIMES - 1 )  )

/* ������������ԣ������ȼ����Ƿ��ռ��: GPHY */
#define RCM_GPHY_TASK_PROPERTY_TABLE  \
    { RCM_GPHY_TASK_START,                      RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT   },\
    { RCM_GPHY_TASK_SEARCHING_MEA,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_SEARCHING_FBSB,             RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_SEARCHING_BCCH_PART,        RCM_TASK_PRIORITY_1_6,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_SEARCHING_BCCH_WHOLE,       RCM_TASK_PRIORITY_5_5,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_PAGE_NORMAL,           RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_IDLE_PAGE_EXT,              RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_IDLE_PAGE_REORG,            RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_SCELL_BCCH_PERIOD,     RCM_TASK_PRIORITY_7,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NCELL_BCCH_DECODE,     RCM_TASK_PRIORITY_3_7,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BASIC_CBCH,            RCM_TASK_PRIORITY_3_4,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_EXT_CBCH,              RCM_TASK_PRIORITY_3_4,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NCELL_FB,              RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NCELL_SB,              RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_IDLE_CELL_RESELECT,         RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BG_MEA,                RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BG_FBSB,               RCM_TASK_PRIORITY_5_9,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BG_BCCH,               RCM_TASK_PRIORITY_5_9,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_INTERRAT_WMEA,         RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_INTERRAT_TMEA,         RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_INTERRAT_LMEA,         RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BG_WMEA,               RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BG_TMEA,               RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_BG_LMEA,               RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_FULLLIST_MEA,          RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_TUNING_RACH,                RCM_TASK_PRIORITY_1,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_TUNING_PRACH,               RCM_TASK_PRIORITY_1,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_PBCCH,                      RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_PPCH,                       RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_TUNING_SINGLE_BLOCK,        RCM_TASK_PRIORITY_1,    RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_DCH_CS,                     RCM_TASK_PRIORITY_1,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_DCH_PS,                     RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_LOST_NET,                   RCM_TASK_PRIORITY_2_5,  RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_INACTIVE,                   RCM_TASK_PRIORITY_3_5,  RCM_TASK_PREEMPTIND_FLAG_INVALID},\
    { RCM_GPHY_TASK_IDLE_SCELL_BCCH_RESEL,      RCM_TASK_PRIORITY_1_6,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_SCELL_BCCH_ENH,        RCM_TASK_PRIORITY_3_5,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NCELL_BCCH_TYPE_RESEL, RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_NCELL_BCCH_TYPE_BG,    RCM_TASK_PRIORITY_5_9,  RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_IDLE_UNFIX_NCELL_SB,        RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID  },\
    { RCM_GPHY_TASK_END,                        RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT   }


/* ������������ԣ������ȼ����Ƿ��ռ��: WPHY */
#define RCM_WPHY_TASK_PROPERTY_TABLE  \
    { RCM_WPHY_TASK_LIST,                  RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT    },\
    { RCM_WPHY_TASK_FREE,                  RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_CPICH_PI,              RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_WPHY_TASK_CPICH_MEAS,            RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_CPICH_PCCPCH,          RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_CPICH_BG,              RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_CPICH_CBS,             RCM_TASK_PRIORITY_9,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_FACH_COMM,             RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_FACH_RA,               RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_FACH_PCCPCH,           RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_DPCH_COMM,             RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID   },\
    { RCM_WPHY_TASK_END,                   RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT    }

/* ������������ԣ������ȼ����Ƿ��ռ��: LPHY */
#define RCM_LPHY_TASK_PROPERTY_TABLE  \
    { RCM_LPHY_TASK_LIST,                   RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT },\
    { RCM_LPHY_TASK_INIT_SEARCHING,         RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_LPHY_TASK_INIT_PBCH_0,            RCM_TASK_PRIORITY_2_9,  RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_INIT_PBCH_1,            RCM_TASK_PRIORITY_2_9,  RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_INIT_SIB1,              RCM_TASK_PRIORITY_2_9,  RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_INIT_SI_0,              RCM_TASK_PRIORITY_2_9,  RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_INIT_SI_1,              RCM_TASK_PRIORITY_2_9,  RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_IDLE_PAGE,              RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_IDLE_MEA,               RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_LPHY_TASK_IDLE_BG_SEARCHING,      RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_LPHY_TASK_IDLE_PBCH_0,            RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_IDLE_PBCH_1,            RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_SIB1,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_SI_0,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_SI_1,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_NCELL_PBCH_0,      RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_NCELL_PBCH_1,      RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_NCELL_SIB1,        RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_NCELL_SI_0,        RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_IDLE_NCELL_SI_1,        RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_LPHY_TASK_CONN_TRAFFIC,           RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_LPHY_TASK_CONN_PMCH,              RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_LPHY_TASK_CONN_PBCH_0,            RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_CONN_PBCH_1,            RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_CONN_SIB1,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_CONN_SI_0,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_CONN_SI_1,              RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID }, \
    { RCM_LPHY_TASK_CONN_MEA,               RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID }, \
    { RCM_LPHY_TASK_CONN_PAGE,              RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID },   \
    { RCM_LPHY_TASK_ANR,                    RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID},   \
    { RCM_LPHY_TASK_PRESYNC,                RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_INVALID}, \
    { RCM_LPHY_TASK_CAMPON,                 RCM_TASK_PRIORITY_2_9,  RCM_TASK_PREEMPTIND_FLAG_INVALID}

/* ������������ԣ������ȼ����Ƿ��ռ��: TPHY */
#define RCM_TPHY_TASK_PROPERTY_TABLE  \
    { RCM_TPHY_TASK_LIST,                   RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT },\
    { RCM_TPHY_TASK_ICS_CELL_SEARCH,        RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_ICS_SWEEP_FREQ,         RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_ICS_CELL_MEASUREMENT,   RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_ICS_PCCPCH,             RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_IDLE_PICH,              RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_TPHY_TASK_IDLE_PCH,               RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_TPHY_TASK_IDLE_MEASUREMENT,       RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_IDLE_CELL_SEARCH,       RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_IDLE_PCCPCH,            RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_TPHY_TASK_IDLE_FORCE_WAKE,        RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_INVALID },\
    { RCM_TPHY_TASK_ACC_FACH_TRAFFIC,       RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID }, \
    { RCM_TPHY_TASK_ACC_PCCPCH,             RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID }, \
    { RCM_TPHY_TASK_DCH_TRAFFIC,            RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID }

#define RCM_CPHY_1X_TASK_PROPERTY_TABLE  \
    { RCM_CPHY_1X_TASK_LIST,                RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT },\
    { RCM_CPHY_1X_TASK_NETWORK_SEARCH,      RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_1X_TASK_IDLE_DRX,            RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_1X_TASK_IDLE_DRX_MEAS,       RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_1X_TASK_IDLE_NON_DRX,        RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_1X_TASK_ACCESS_TCH,          RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_1X_TASK_BSR,                 RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_1X_TASK_AGPS,                RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID }


#define RCM_CPHY_HRPD_TASK_PROPERTY_TABLE  \
    { RCM_CPHY_HRPD_TASK_LIST,              RCM_TASK_PRIORITY_BUTT, RCM_TASK_PREEMPTIND_FLAG_BUTT },\
    { RCM_CPHY_HRPD_TASK_NETWORK_SEARCH,    RCM_TASK_PRIORITY_3,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_DRX,               RCM_TASK_PRIORITY_2,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_DRX_MEAS,          RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_CC_MON_NON_DRX,    RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_ACCESS_TCH,        RCM_TASK_PRIORITY_5,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_BSR,               RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_LTE,               RCM_TASK_PRIORITY_6,    RCM_TASK_PREEMPTIND_FLAG_VALID },\
    { RCM_CPHY_HRPD_TASK_AGPS,              RCM_TASK_PRIORITY_4,    RCM_TASK_PREEMPTIND_FLAG_VALID }


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : RCM_PHY_MSG_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : RCM <-> PHY �ӿ���ϢID
*****************************************************************************/
enum RCM_PHY_MSG_ID_ENUM
{
    ID_PHY_RCM_TASK_APPLY_REQ               = 0x1801,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_APPLY_REQ_STRU */
    ID_PHY_RCM_TASK_REL_REQ                 = 0x1802,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_REL_REQ_STRU */
    ID_PHY_RCM_TASK_RELALL_REQ              = 0x1803,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_RELALL_REQ_STRU */
    ID_PHY_RCM_TASK_PREEMPT_ACK             = 0x1804,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_PREEMPT_ACK_STRU */
    ID_PHY_RCM_TASK_RESUME_ACK              = 0x1805,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_RESUME_ACK_STRU */
    ID_PHY_RCM_AWAKE_REQ                    = 0x1807,                           /* _H2ASN_MsgChoice PHY_RCM_AWAKE_REQ_STRU */
    ID_PHY_RCM_SLEEP_REQ                    = 0x1808,                           /* _H2ASN_MsgChoice PHY_RCM_SLEEP_REQ_STRU */
    ID_PHY_RCM_ASSIGN_ACK                   = 0x1809,                           /* _H2ASN_MsgChoice PHY_RCM_ASSIGN_ACK_STRU */
    ID_PHY_RCM_CLOCK_CAL_ACK                = 0x180a,                           /* _H2ASN_MsgChoice PHY_RCM_CLOCK_CAL_ACK_STRU */
    ID_PHY_RCM_GET_MSGLISTADDR_REQ          = 0x180c,                           /* _H2ASN_MsgChoice PHY_RCM_GET_MSGLISTADDR_REQ_STRU */
    ID_PHY_RCM_PERIOD_TASK_COMPLETE_REQ     = 0x180d,                           /* _H2ASN_MsgChoice PHY_RCM_TASK_COMPLETE_REQ_STRU */
    ID_PHY_RCM_START_TAS_CNF                = 0x180e,                           /* _H2ASN_MsgChoice PHY_RCM_START_TAS_CNF_STRU */
    ID_PHY_RCM_STOP_TAS_CNF                 = 0x180f,                           /* _H2ASN_MsgChoice PHY_RCM_STOP_TAS_CNF_STRU */
    ID_PHY_RCM_SET_DPDT_CNF                 = 0x1810,                           /* _H2ASN_MsgChoice PHY_RCM_SET_DPDT_CNF_STRU */
    ID_PHY_RCM_TX_BLANKING_IND              = 0x1811,                           /* _H2ASN_MsgChoice PHY_RCM_TX_BLANKING_IND_STRU */
    ID_PHY_RCM_RATMODE_IND                  = 0x1812,                           /* _H2ASN_MsgChoice PHY_RCM_RATMODE_IND_STRU */
    ID_MSP_RCM_MAILBOX_READ_IND             = 0x1813,                           /* _H2ASN_MsgChoice RCM_PHY_MSG_HEADER_STRU */
    ID_PHY_RCM_ACCESS_STATE_IND             = 0x1814,                           /* _H2ASN_MsgChoice PHY_RCM_ACCESS_STATE_IND_STRU */
    ID_PHY_RCM_SEARCHING_STATE_IND          = 0x1815,                           /* _H2ASN_MsgChoice PHY_RCM_SEARCHING_STATE_IND_STRU */
    ID_PHY_RCM_SIGNAL_STATE_IND             = 0x1816,                           /* _H2ASN_MsgChoice PHY_RCM_SIGNAL_STATE_IND_STRU */
    ID_PHY_RCM_IDLE_HAPPY_IND               = 0x1817,                           /* _H2ASN_MsgChoice PHY_RCM_IDLE_HAPPY_IND_STRU */
                                                                                /* 0x1818�Ѿ������MTC -> RCM messageʹ�� */
    ID_PHY_RCM_VOICE_CALL_STATE_CNF         = 0x1819,                           /* _H2ASN_MsgChoice PHY_RCM_VOICE_CALL_STATE_CNF_STRU */
    ID_PHY_RCM_SEARCHING_STATE_REQ          = 0x181a,                           /* _H2ASN_MsgChoice PHY_RCM_SEARCHING_STATE_REQ_STRU */
                                                                                /* 0x181b,0x181c�Ѿ������CMMCA -> RCM messageʹ�� */
    ID_PHY_RCM_AGENT_SET_DPDT_CNF           = 0x181d,                           /* _H2ASN_MsgChoice PHY_RCM_AGENTC_SET_DPDT_CNF_STRU */
    ID_PHY_RCM_CPICH_STATE_IND              = 0x181e,                           /* _H2ASN_MsgChoice PHY_RCM_CPICH_STATE_IND_STRU */
                                                                                /* 0x181f�Ѿ������MTC -> RCM messageʹ�� */
                                                                                /* 0x1820�Ѿ������MTC -> RCM messageʹ�� */
    ID_PHY_RCM_ANT_SHARE_CNF                = 0x1821,                           /* _H2ASN_MsgChoice PHY_RCM_ANT_SHARE_CNF_STRU */

    ID_RCM_PHY_TASK_APPLY_CNF               = 0x1881,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_APPLY_CNF_STRU */
    ID_RCM_PHY_TASK_REL_CNF                 = 0x1882,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_REL_CNF_STRU */
    ID_RCM_PHY_TASK_RELALL_CNF              = 0x1883,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_RELALL_CNF_STRU */
    ID_RCM_PHY_TASK_PREEMPT_IND             = 0x1884,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_PREEMPT_IND_STRU */
    ID_RCM_PHY_TASK_RESUME_IND              = 0x1885,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_RESUME_IND_STRU */
    ID_RCM_PHY_ASSIGN_IND                   = 0x1889,                           /* _H2ASN_MsgChoice RCM_PHY_ASSIGN_IND_STRU */
    ID_RCM_PHY_CLOCK_CAL_IND                = 0x188a,                           /* _H2ASN_MsgChoice RCM_PHY_CLOCK_CAL_IND_STRU */
    ID_RCM_PHY_OVERTIME_IND                 = 0x188b,                           /* _H2ASN_MsgChoice RCM_PHY_OVERTIME_IND_STRU */
    ID_RCM_PHY_GET_MSGLISTADDR_CNF          = 0x188c,                           /* _H2ASN_MsgChoice RCM_PHY_GET_MSGLISTADDR_CNF_STRU */
    ID_RCM_PHY_PERIOD_TASK_COMPLETE_CNF     = 0x188d,                           /* _H2ASN_MsgChoice RCM_PHY_TASK_COMPLETE_CNF_STRU */
    ID_RCM_PHY_START_TAS_REQ                = 0x188e,                           /* _H2ASN_MsgChoice RCM_PHY_START_TAS_REQ_STRU */
    ID_RCM_PHY_STOP_TAS_REQ                 = 0x188f,                           /* _H2ASN_MsgChoice RCM_PHY_STOP_TAS_REQ_STRU */
    ID_RCM_PHY_SET_DPDT_REQ                 = 0x1890,                           /* _H2ASN_MsgChoice RCM_PHY_SET_DPDT_REQ_STRU */
    ID_RCM_PHY_TX_BLANKING_IND              = 0x1891,                           /* _H2ASN_MsgChoice RCM_PHY_TX_BLANKING_IND */
    ID_PAGING_TASK_RF_RESOURCE_APPLY_FAIL   = 0x1892,                           /* _H2ASN_MsgChoice PHY_RCM_PAGING_TASK_FAIL_STRU */
    ID_RCM_PHY_SEARCHING_STATE_CNF          = 0x1893,                           /* _H2ASN_MsgChoice RCM_PHY_SEARCHING_STATE_CNF_STRU */
    ID_RCM_PHY_AGENT_SET_DPDT_REQ           = 0x1894,                           /* _H2ASN_MsgChoice RCM_PHY_AGENTC_SET_DPDT_REQ_STRU */
    ID_RCM_PHY_VOICE_CALL_STATE_IND         = 0x1895,                           /* _H2ASN_MsgChoice RCM_PHY_VOICE_CALL_STATE_IND_STRU */
    ID_RCM_PHY_ANT_SHARE_REQ                = 0x1896,                           /* _H2ASN_MsgChoice RCM_PHY_ANT_SHARE_REQ_STRU */
    ID_RCM_PHY_CDMA_WORK_STATE_IND          = 0x1897,                           /* _H2ASN_MsgChoice PHY_RCM_CDMA_WORK_STATE_IND_STRU */
    ID_RCM_PHY_ANT_SHARE_TX_BLANKING_IND    = 0x1898,                           /* _H2ASN_MsgChoice RCM_PHY_ANT_SHARE_TX_BLANKING_IND_STRU */
    ID_RCM_PHY_NOTICE_DSDS_INIT_IND         = 0x1899,                           /* _H2ASN_MsgChoice RCM_PHY_NOTICE_DSDS_INIT_IND_STRU */
    ID_RCM_PHY_MSG_BUTT

};
typedef VOS_UINT16 RCM_PHY_MSG_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_PRIORITY_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : RCM���������ȼ� ������������ֵΪ���ȼ�1~8(200~900)�������ȼ���RCM�ڲ�ʹ��
*****************************************************************************/
enum RCM_TASK_PRIORITY_ENUM
{
    RCM_TASK_PRIORITY_HIGHEST           = 1 ,                                   /* ����������ȼ� 1~99���ڶ�ռ */
    RCM_TASK_PRIORITY_CALA_HIGHEST      = 100,                                  /* ���ȼ�100 �������ȼ��ܹ������������ֵ RCM����õ� */
    RCM_TASK_PRIORITY_1                 = 200,                                  /* ���ȼ�200 �������ȼ�����ֵ */
    RCM_TASK_PRIORITY_1_5               = 250,                                  /* ���ȼ�250 �������ȼ�����ֵ */
    RCM_TASK_PRIORITY_1_6               = 260,                                  /* ���ȼ�260 �������ȼ�����ֵ */
    RCM_TASK_PRIORITY_1_7               = 270,                                  /* ���ȼ�270 �������ȼ�����ֵ */
    RCM_TASK_PRIORITY_2                 = 300,                                  /* ���ȼ�300 */
    RCM_TASK_PRIORITY_2_5               = 350,                                  /* ���ȼ�350 */
    RCM_TASK_PRIORITY_2_9               = 390,                                  /* ���ȼ�390 */
    RCM_TASK_PRIORITY_3                 = 400,                                  /* ���ȼ�400 */
    RCM_TASK_PRIORITY_3_4               = 440,                                  /* ���ȼ�440 */
    RCM_TASK_PRIORITY_3_5               = 450,                                  /* ���ȼ�450 */
    RCM_TASK_PRIORITY_3_7               = 470,                                  /* ���ȼ�470 */
    RCM_TASK_PRIORITY_4                 = 500,                                  /* ���ȼ�500 */
    RCM_TASK_PRIORITY_4_5               = 550,                                  /* ���ȼ�550 */
    RCM_TASK_PRIORITY_5                 = 600,                                  /* ���ȼ�600 */
    RCM_TASK_PRIORITY_5_5               = 650,                                  /* ���ȼ�650 */
    RCM_TASK_PRIORITY_5_9               = 690,                                  /* ���ȼ�690 */
    RCM_TASK_PRIORITY_6                 = 700,                                  /* ���ȼ�700 */
    RCM_TASK_PRIORITY_7                 = 800,                                  /* ���ȼ�800 */
    RCM_TASK_PRIORITY_8                 = 900,                                  /* ���ȼ�900 */
    RCM_TASK_PRIORITY_9                 = 1000,                                 /* ���ȼ�1000 */
    RCM_TASK_PRIORITY_LOWEST            = 1100,                                 /* ����������ȼ� RCMʹ�� */
    RCM_TASK_PRIORITY_BUTT
};
typedef VOS_UINT16 RCM_TASK_PRIORITY_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_PHY_TASK_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : PHY ��RCM��ע�������ID
*****************************************************************************/
enum RCM_PHY_TASK_ID_ENUM
{
    RCM_GPHY_TASK_START                     = RCM_GPHY_TASK_ID_BEGIN_NUM,       /* ������������� */
    RCM_GPHY_TASK_SEARCHING_MEA             = 1,                                /* 1�������� */
    RCM_GPHY_TASK_SEARCHING_FBSB            = 2,                                /* 2����ͬ�� */
    RCM_GPHY_TASK_SEARCHING_BCCH_PART       = 3,                                /* 3������㲥�����ֶ� */
    RCM_GPHY_TASK_SEARCHING_BCCH_WHOLE      = 4,                                /* 4������㲥��ȫ�� */
    RCM_GPHY_TASK_IDLE_PAGE_NORMAL          = 5,                                /* 5��Ѱ������ */
    RCM_GPHY_TASK_IDLE_PAGE_EXT             = 6,                                /* 6����չѰ������ */
    RCM_GPHY_TASK_IDLE_PAGE_REORG           = 7,                                /* 7Reorg̬��Ѱ�� */
    RCM_GPHY_TASK_IDLE_SCELL_BCCH_PERIOD    = 8,                                /* 8������С��ϵͳ��Ϣ */
    RCM_GPHY_TASK_IDLE_NCELL_BCCH_DECODE    = 9,                                /* 9������ϵͳ��Ϣ */
    RCM_GPHY_TASK_IDLE_BASIC_CBCH           = 10,                               /* 10BASIC����CBSҵ�� */
    RCM_GPHY_TASK_IDLE_EXT_CBCH             = 11,                               /* 11EXT����CBSҵ�� */
    RCM_GPHY_TASK_IDLE_NCELL_FB             = 12,                               /* 12����FB */
    RCM_GPHY_TASK_IDLE_NCELL_SB             = 13,                               /* 13����SB */
    RCM_GPHY_TASK_IDLE_CELL_RESELECT        = 14,                               /* 14С����ѡ */
    RCM_GPHY_TASK_IDLE_BG_MEA               = 15,                               /* 15�����Ѳ��� */
    RCM_GPHY_TASK_IDLE_BG_FBSB              = 16,                               /* 16������ͬ�� */
    RCM_GPHY_TASK_IDLE_BG_BCCH              = 17,                               /* 17�����ѽ�㲥 */
    RCM_GPHY_TASK_IDLE_INTERRAT_WMEA        = 18,                               /* 18��ϵͳW���� */
    RCM_GPHY_TASK_IDLE_INTERRAT_TMEA        = 19,                               /* 19��ϵͳT���� */
    RCM_GPHY_TASK_IDLE_INTERRAT_LMEA        = 20,                               /* 20��ϵͳL���� */
    RCM_GPHY_TASK_IDLE_BG_WMEA              = 21,                               /* 21������W���� */
    RCM_GPHY_TASK_IDLE_BG_TMEA              = 22,                               /* 22������T���� */
    RCM_GPHY_TASK_IDLE_BG_LMEA              = 23,                               /* 23������L���� */
    RCM_GPHY_TASK_IDLE_FULLLIST_MEA         = 24,                               /* 24FULLIS���� */
    RCM_GPHY_TASK_TUNING_RACH               = 25,                               /* 25������� */
    RCM_GPHY_TASK_TUNING_PRACH              = 26,                               /* 26PACKET������� */
    RCM_GPHY_TASK_PBCCH                     = 27,                               /* 27PACKETϵͳ��Ϣ */
    RCM_GPHY_TASK_PPCH                      = 28,                               /* 28PACKETѰ�� */
    RCM_GPHY_TASK_TUNING_SINGLE_BLOCK       = 29,                               /* 29���͵���Ͷ�� */
    RCM_GPHY_TASK_DCH_CS                    = 30,                               /* 30CSר��̬ */
    RCM_GPHY_TASK_DCH_PS                    = 31,                               /* 31PSר��̬ */
    RCM_GPHY_TASK_LOST_NET                  = 32,                               /* 32������ */
    RCM_GPHY_TASK_INACTIVE                  = 33,                               /* 33ȥ���� */
    RCM_GPHY_TASK_IDLE_SCELL_BCCH_RESEL     = 34,                               /* 34��ѡ�����з���С��ϵͳ��Ϣ��ȡ, ��������ȼ�Ϊ260����Ѱ�������ʧ�������й� */
    RCM_GPHY_TASK_IDLE_SCELL_BCCH_ENH       = 35,                               /* 35��ǿ���չ�����ϵͳ��Ϣ��ȡ */
    RCM_GPHY_TASK_IDLE_NCELL_BCCH_TYPE_RESEL= 36,                               /* 36��ѡ������ϵͳ��Ϣ��ȡ */
    RCM_GPHY_TASK_IDLE_NCELL_BCCH_TYPE_BG   = 37,                               /* 37�����ѹ�����ϵͳ��Ϣ��ȡ */
    RCM_GPHY_TASK_IDLE_UNFIX_NCELL_SB       = 38,                               /* 38�����ǹ̶���SB */
    RCM_GPHY_TASK_END                       ,                                   /* ������������� */
    RCM_WPHY_TASK_LIST                      = RCM_WPHY_TASK_ID_BEGIN_NUM,
    RCM_WPHY_TASK_FREE                      = 101,                              /* Wphy free̬���� */
    RCM_WPHY_TASK_CPICH_PI                  = 102,                              /* Wphy cpich̬PI���� */
    RCM_WPHY_TASK_CPICH_MEAS                = 103,                              /* Wphy cpich̬�������� */
    RCM_WPHY_TASK_CPICH_PCCPCH              = 104,                              /* Wphy cpich̬ͬƵ��ѡ�����µĹ㲥���� */
    RCM_WPHY_TASK_CPICH_BG                  = 105,                              /* Wphy cpich̬���������� */
    RCM_WPHY_TASK_CPICH_CBS                 = 106,                              /* Wphy cpich̬CBS���� */
    RCM_WPHY_TASK_FACH_COMM                 = 107,                              /* Wphy fach̬���� */
    RCM_WPHY_TASK_FACH_RA                   = 108,                              /* Wphy fach̬����������� */
    RCM_WPHY_TASK_FACH_PCCPCH               = 109,                              /* Wphy fach̬ͬ��ѡ��ϵͳ��Ϣ������� */
    RCM_WPHY_TASK_DPCH_COMM                 = 110,                              /* Wphy dch̬���� */
    RCM_WPHY_TASK_END                       ,
    RCM_TPHY_TASK_LIST                      = RCM_TPHY_TASK_ID_BEGIN_NUM,
    RCM_TPHY_TASK_ICS_CELL_SEARCH           = 201,                              /*  1  */
    RCM_TPHY_TASK_ICS_SWEEP_FREQ            = 202,                              /*  2  */
    RCM_TPHY_TASK_ICS_CELL_MEASUREMENT      = 203,                              /*  3  */
    RCM_TPHY_TASK_ICS_PCCPCH                = 204,                              /*  4  */
    RCM_TPHY_TASK_IDLE_PICH                 = 205,                              /*  5  */
    RCM_TPHY_TASK_IDLE_PCH                  = 206,                              /*  6  */
    RCM_TPHY_TASK_IDLE_MEASUREMENT          = 207,                              /*  7  */
    RCM_TPHY_TASK_IDLE_CELL_SEARCH          = 208,                              /*  8  */
    RCM_TPHY_TASK_IDLE_PCCPCH               = 209,                              /*  9  */
    RCM_TPHY_TASK_IDLE_FORCE_WAKE           = 210,                              /*  10  */
    RCM_TPHY_TASK_ACC_FACH_TRAFFIC          = 211,                              /*  11  */
    RCM_TPHY_TASK_ACC_PCCPCH                = 212,                              /*  12  */
    RCM_TPHY_TASK_DCH_TRAFFIC               = 213,                              /*  13  */
    RCM_TPHY_TASK_BUTT                      ,
    RCM_LPHY_TASK_LIST                      = RCM_LPHY_TASK_ID_BEGIN_NUM,
    RCM_LPHY_TASK_INIT_SEARCHING            = 301,                              /*  1  */
    RCM_LPHY_TASK_INIT_PBCH_0               = 302,                              /*  2  */
    RCM_LPHY_TASK_INIT_PBCH_1               = 303,                              /*  3  */
    RCM_LPHY_TASK_INIT_SIB1                 = 304,                              /*  4  */
    RCM_LPHY_TASK_INIT_SI_0                 = 305,                              /*  5  */
    RCM_LPHY_TASK_INIT_SI_1                 = 306,                              /*  6  */
    RCM_LPHY_TASK_IDLE_PAGE                 = 307,                              /*  7  */
    RCM_LPHY_TASK_IDLE_MEA                  = 308,                              /*  8  */
    RCM_LPHY_TASK_IDLE_BG_SEARCHING         = 309,                              /*  9  */
    RCM_LPHY_TASK_IDLE_PBCH_0               = 310,                              /*  10  */
    RCM_LPHY_TASK_IDLE_PBCH_1               = 311,                              /*  11  */
    RCM_LPHY_TASK_IDLE_SIB1                 = 312,                              /*  12  */
    RCM_LPHY_TASK_IDLE_SI_0                 = 313,                              /*  13  */
    RCM_LPHY_TASK_IDLE_SI_1                 = 314,                              /*  14  */
    RCM_LPHY_TASK_IDLE_NCELL_PBCH_0         = 315,                              /*  15  */
    RCM_LPHY_TASK_IDLE_NCELL_PBCH_1         = 316,                              /*  16  */
    RCM_LPHY_TASK_IDLE_NCELL_SIB1           = 317,                              /*  17  */
    RCM_LPHY_TASK_IDLE_NCELL_SI_0           = 318,                              /*  18  */
    RCM_LPHY_TASK_IDLE_NCELL_SI_1           = 319,                              /*  19  */
    RCM_LPHY_TASK_CONN_TRAFFIC              = 320,                              /*  20  */
    RCM_LPHY_TASK_CONN_PMCH                 = 321,                              /*  21  */
    RCM_LPHY_TASK_CONN_PBCH_0               = 322,                              /*  22  */
    RCM_LPHY_TASK_CONN_PBCH_1               = 323,                              /*  23  */
    RCM_LPHY_TASK_CONN_SIB1                 = 324,                              /*  24  */
    RCM_LPHY_TASK_CONN_SI_0                 = 325,                              /*  25  */
    RCM_LPHY_TASK_CONN_SI_1                 = 326,                              /*  26  */
    RCM_LPHY_TASK_CONN_MEA                  = 327,                              /*  27  */
    RCM_LPHY_TASK_CONN_PAGE                 = 328,                              /*  28  */
    RCM_LPHY_TASK_ANR                       = 329,                              /*  29  */
    RCM_LPHY_TASK_PRESYNC                   = 330,                              /*  30  */
    RCM_LPHY_TASK_CAMPON                    = 331,                              /*  31  */
    RCM_LPHY_TASK_BUTT,
    RCM_CPHY_1X_TASK_LIST                   = RCM_CPHY_1X_TASK_ID_BEGIN_NUM,
    RCM_CPHY_1X_TASK_NETWORK_SEARCH         = 401,                              /*   1  */
    RCM_CPHY_1X_TASK_IDLE_DRX               = 402,                              /*   2  */
    RCM_CPHY_1X_TASK_IDLE_DRX_MEAS          = 403,                              /*   3  */
    RCM_CPHY_1X_TASK_IDLE_NON_DRX           = 404,                              /*   4  */
    RCM_CPHY_1X_TASK_ACCESS_TCH             = 405,                              /*   5  */
    RCM_CPHY_1X_TASK_BSR                    = 406,                              /*   6  */
    RCM_CPHY_1X_TASK_AGPS                   = 407,                              /*   7  */
    RCM_CPHY_1X_TASK_BUTT,
    RCM_CPHY_HRPD_TASK_LIST                 = RCM_CPHY_HRPD_TASK_ID_BEGIN_NUM,
    RCM_CPHY_HRPD_TASK_NETWORK_SEARCH       = 501,                              /*   1  */
    RCM_CPHY_HRPD_TASK_DRX                  = 502,                              /*   2  */
    RCM_CPHY_HRPD_TASK_DRX_MEAS             = 503,                              /*   3  */
    RCM_CPHY_HRPD_TASK_CC_MON_NON_DRX       = 504,                              /*   4  */
    RCM_CPHY_HRPD_TASK_ACCESS_TCH           = 505,                              /*   5  */
    RCM_CPHY_HRPD_TASK_BSR                  = 506,                              /*   6  */
    RCM_CPHY_HRPD_TASK_LTE                  = 507,                              /*   7  */
    RCM_CPHY_HRPD_TASK_AGPS                 = 508,                              /*   8  */
    RCM_PHY_TASK_BUTT                       ,
};
typedef VOS_UINT16 RCM_PHY_TASK_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_MODE_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �����ģʽ��ʾ ���д����У׼����һ��
*****************************************************************************/
enum RCM_MODE_ID_ENUM
{
    RCM_LTE                             = 0,                                    /* LTE */
    RCM_WCDMA                           = 1,                                    /* WCDMA */
    RCM_1X                              = 2,                                    /* 1X */
    RCM_HRPD                            = 3,                                    /* HRPD */
    RCM_TD                              = 4,                                    /* TD */
    RCM_G0                              = 5,                                    /* G0 */
    RCM_G1                              = 6,                                    /* G1 */
    RCM_G2                              = 7,                                    /* G2 */
    RCM_MODE_ID_BUTT
};
typedef VOS_UINT16  RCM_MODE_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_MODEM_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : MODEM ID
*****************************************************************************/
enum RCM_MODEM_ID_ENUM
{
    RCM_MODEM_1                         = 0,                                    /* MODEM0 */
    RCM_MODEM_2                         = 1,                                    /* MODEM1 */
    RCM_MODEM_3                         = 2,                                    /* MODEM2 */
    RCM_MODEM_1X                        = 3,                                    /* MODEM_1x */
    RCM_MODEM_OTHER                     = 4,                                    /* MODEM_OHTER */
    RCM_MODEM_ID_BUTT
};
typedef VOS_UINT16  RCM_MODEM_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_MODEM_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : TAS_MODEM ID
*****************************************************************************/
enum RCM_TAS_MODEM_ID_ENUM
{
    RCM_TAS_MODEM_1                     = 0,                                    /* MODEM0 */
    RCM_TAS_MODEM_2                     = 1,                                    /* MODEM1 */
    RCM_TAS_MODEM_3                     = 2,                                    /* MODEM1 */
    RCM_TAS_MODEM_ID_BUTT
};
typedef VOS_UINT16  RCM_TAS_MODEM_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_RF_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : RF ID
*****************************************************************************/
enum RCM_RF_ID_ENUM
{
    RCM_RF_0                            = 0,                                    /* RF0 */
    RCM_RF_1                            = 1,                                    /* RF1 */
    RCM_RF_ID_BUTT
};
typedef VOS_UINT16  RCM_RF_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_DSDS_FLG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RCM_DSDS_FLG_ENUM
*****************************************************************************/
enum RCM_DSDS_FLG_ENUM
{
    RCM_DSDS_CLOSE                       = 0,                                   /* DSDS CLOSE */
    RCM_DSDS_OPEN                        = 1,                                   /* DSDS OPEN  */
    RCM_DSDS_BUTT
};
typedef VOS_UINT16  RCM_DSDS_FLG_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_RTT_STA_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : RTT״̬,����ʱ��У׼ѡ��

*****************************************************************************/
enum RCM_RTT_STA_ENUM
{
    RCM_RTT_INITIAL                     = 0,                                    /* ��ʼ̬ ,û��פ�� */
    RCM_RTT_DRX                         = 1,                                    /* ������̬������̬ */
    RCM_RTT_CONTINUE                    = 2,                                    /* ����̬ ����绰����*/
    RCM_RTT_STA_BUTT
};
typedef VOS_UINT16  RCM_RTT_STA_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_RSLT_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �ӿ��е���Ч�Ա�ʶ
*****************************************************************************/
enum RCM_RSLT_ENUM
{
    RCM_SUCC                            = 0,                                    /* �ɹ� */
    RCM_FAIL_PARA                       = 1,                                    /* �������� */
    RCM_FAIL_OVERTIME                   = 2,                                    /* ������ǰ������ */
    RCM_FAIL_OTHER                      = 3,                                    /* �����ڵ�Ϊ�� */
    RCM_RSLT_BUTT
};
typedef VOS_UINT16  RCM_RSLT_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_DIRECTION_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �ӿ��еĵ��������ʶ
*****************************************************************************/
enum RCM_DIRECTION_ENUM
{
    RCM_DIRECTION_SLOWDOWN              = 0,                                    /* ����1������ */
    RCM_DIRECTION_SPEEDUP               = 1,                                    /* ����1������ */
    RCM_DIRECTION_KEEP                  = 2,                                    /* ������ */
    RCM_DIRECTION_BUTT
};
typedef VOS_UINT16 RCM_DIRECTION_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_PERIOD_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ����/�����������ʶ
*****************************************************************************/
enum RCM_TASK_PERIOD_FLAG_ENUM
{
    RCM_TASK_PERIOD_FLAG_INVALID        = 0,                                    /* ���������� */
    RCM_TASK_PERIOD_FLAG_VALID          = 1,                                    /* �������� */
    RCM_TASK_PERIOD_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_PERIOD_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_FIXPOS_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �̶�/�ǹ̶�����ʱ�̱�ʶ
*****************************************************************************/
enum RCM_TASK_FIXPOS_FLAG_ENUM
{
    RCM_TASK_FIXPOS_FLAG_INVALID        = 0,                                    /* �޹̶�����ʱ�� */
    RCM_TASK_FIXPOS_FLAG_VALID          = 1,                                    /* �й̶�����ʱ�� */
    RCM_TASK_FIXPOS_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_FIXPOS_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_LIMITLEN_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �̶�/�ǹ̶����ȱ�ʶ
*****************************************************************************/
enum RCM_TASK_LIMITLEN_FLAG_ENUM
{
    RCM_TASK_LIMITLEN_FLAG_INVALID      = 0,                                    /* ���޳����� */
    RCM_TASK_LIMITLEN_FLAG_VALID        = 1,                                    /* ���޳����� */
    RCM_TASK_LIMITLEN_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_LIMITLEN_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_IMMEDIATE_ASSIGN_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ����/���������������ʶ
*****************************************************************************/
enum RCM_TASK_IMMEDIATE_ASSIGN_FLAG_ENUM
{
    RCM_TASK_IMMEDIATE_ASSIGN_FLAG_INVALID  = 0,                                /* ����Ҫ������������ */
    RCM_TASK_IMMEDIATE_ASSIGN_FLAG_VALID    = 1,                                /* ��Ҫ������������ */
    RCM_TASK_IMMEDIATE_ASSIGN_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_IMMEDIATE_ASSIGN_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_PREEMPTIND_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �ɴ��/���ɴ�������ʶ
*****************************************************************************/
enum RCM_TASK_PREEMPTIND_FLAG_ENUM
{
    RCM_TASK_PREEMPTIND_FLAG_INVALID        = 0,                                /* ���ɴ������ */
    RCM_TASK_PREEMPTIND_FLAG_VALID          = 1,                                /* �ɴ������ */
    RCM_TASK_PREEMPTIND_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_PREEMPTIND_FLAG_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TASK_RELEASE_PRINCIPAL_FLAG_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �����/RCM �����ͷű�ʶ
*****************************************************************************/
enum RCM_TASK_RELEASE_PRINCIPAL_ENUM
{
    RCM_TASK_RELEASE_PRINCIPAL_PHY          = 0,                                /* ��������ͷ� */
    RCM_TASK_RELEASE_PRINCIPAL_RCM          = 1,                                /* ��RCM�ͷ� */
    RCM_TASK_RELEASE_PRINCIPAL_ONLYPHY      = 2,                                /* �̶�ʱ�����޳�����ϣ��RCM��Ҫ�ͷţ�ֻ��ͨ��PHY�ͷ� */
    RCM_TASK_RELEASE_PRINCIPAL_FLAG_BUTT
};
typedef VOS_UINT16  RCM_TASK_RELEASE_PRINCIPAL_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_CMD_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : ��Ϣ��������Ϣ����
*****************************************************************************/
enum RCM_CMD_ENUM
{
    RCM_CMD_TASK_ASSIGN_SUCC                = 0,                                /* �������ɹ� */
    RCM_CMD_TASK_ASSIGN_FAIL_OTHER          = 1,                                /* �����������ʧ�� */
    RCM_CMD_TASK_RECYCLE                    = 2,                                /* �ѷ�������û�������л��� */
    RCM_CMD_MSG_BUTT
};
typedef VOS_UINT16  RCM_CMD_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_CMODE_TYPE_ENUM_UINT16
 ö��˵��  : Cģ��ϵͳʱ������,00��1x��ʱ��01��evdo��ʱ��10�� base_cnt ��11����Ч��
*****************************************************************************/
enum RCM_CMODE_TYPE_ENUM
{
    RCM_CMODE_1X                        = 0,
    RCM_CMODE_EVDO                      = 1,
    RCM_CMODE_BASECNT                   = 2,
    RCM_CMODE_BUTT
};
typedef VOS_UINT16 RCM_CMODE_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_WMODE_TYPE_ENUM_UINT16
 ö��˵��  : Wģ��ϵͳʱ������
             00��sys_cnt��ʱ        01��base_cnt��ʱ
             10����Ч               11����Ч
*****************************************************************************/
enum RCM_WMODE_TYPE_ENUM
{
    RCM_WMODE_SYSCNT                    = 0,
    RCM_WMODE_BASECNT                   = 1,
    RCM_WMODE_BUTT
};
typedef VOS_UINT16 RCM_WMODE_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_PAGING_TASK_FAIL_REASON_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �����/RCM �����ͷ�ԭ��
*****************************************************************************/
enum RCM_PAGING_TASK_FAIL_REASON_ENUM
{
    RCM_PAGING_TASK_FAIL_FOR_PROTECT        = 0,                                /* ����һ�ſ������� */
    RCM_PAGING_TASK_FAIL_FOR_PREEMPTED      = 1,                                /* �����������ȼ��� */
    RCM_PAGING_TASK_FAIL_FOR_OTHER          = 2,                                /* ��Ҫ����log�ĳ��� */
    RCM_PAGING_TASK_FAIL_BUTT
};
typedef VOS_UINT16  RCM_PAGING_TASK_FAIL_REASON_ENUM_UINT16;


/*****************************************************************************
 ö����    : RCM_STOP_TAS_TYPE_ENUM_UINT16
 ö��˵��  : RCMȡ�������TAS��Ȩ��ʽ
             0:�ر�TAS���������л�PHYĬ��̬
             1:��ͣTAS�������߱����ڵ�ǰ״̬
*****************************************************************************/
enum RCM_STOP_TAS_TYPE_ENUM
{
    RCM_STOP_TAS_TYPE_STOP                = 0,
    RCM_STOP_TAS_TYPE_KEEP                = 1,
    RCM_STOP_TAS_TYPE_BUTT
};
typedef VOS_UINT16 RCM_STOP_TAS_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_CONNECT_STATE_ENUM_UINT16
 ö��˵��  : modemҵ������״̬
             0:������״̬
             1:����״̬
*****************************************************************************/
enum RCM_TAS_CONNECT_STATE_ENUM
{
    RCM_TAS_CONNECT_NO_EXIST             = 0,
    RCM_TAS_CONNECT_EXIST                = 1,
    RCM_TAS_CONNECT_BUTT
};
typedef VOS_UINT16 RCM_TAS_CONNECT_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_POWER_STATE_ENUM_UINT16
 ö��˵��  : modem_power���µ�״̬���Ƿ��ڷ���ģʽ
             0:�µ缴����ģʽ
             1:�ϵ缴�Ƿ���ģʽ
*****************************************************************************/
enum RCM_TAS_POWER_STATE_ENUM
{
    RCM_TAS_POWER_STATE_OFF           = 0,
    RCM_TAS_POWER_STATE_ON            = 1,
    RCM_TAS_POWER_STATE_BUTT
};
typedef VOS_UINT16 RCM_TAS_POWER_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_ACCESS_STATE_ENUM_UINT16
 ö��˵��  : modem����״̬
             0:�ǽ���״̬
             1:����״̬
*****************************************************************************/
enum RCM_ACCESS_STATE_ENUM
{
    RCM_ACCESS_STATE_NON_ACCESS   = 0,
    RCM_ACCESS_STATE_ACCESS       = 1,
    RCM_ACCESS_STATE_UNHAPPY      = 2,
    RCM_ACCESS_STATE_BUTT
};
typedef VOS_UINT16 RCM_ACCESS_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_CPICH_STATE_ENUM
 ö��˵��  : modemCPICH_STAT״̬
             0:��CPICH״̬
             1:CPICH״̬
*****************************************************************************/
enum RCM_CPICH_STATE_ENUM
{
    RCM_CPICH_STATE_NON         = 0,
    RCM_CPICH_STATE             = 1,
    RCM_CPICH_STATE_BUTT
};
typedef VOS_UINT16 RCM_CPICH_STATE_ENUM_UINT16;



/*****************************************************************************
 ö����    : RCM_SEARCHING_STATE_ENUM_UINT16
 ö��˵��  : modem��Ѱ״̬
             0:����Ѱ״̬
             1:��Ѱ״̬
*****************************************************************************/
enum RCM_SEARCHING_STATE_ENUM
{
    RCM_SEARCHING_STATE_NON_SEARCH    = 0,
    RCM_SEARCHING_STATE_SEARCH        = 1,
    RCM_SEARCHING_STATE_BUTT
};
typedef VOS_UINT16 RCM_SEARCHING_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_SIGNAL_STATE_ENUM_UINT16
 ö��˵��  : modemѶ��״̬
             0:Ѷ��POOR״̬
             1:Ѷ��GOOD״̬
*****************************************************************************/
enum RCM_SIGNAL_STATE_ENUM
{
    RCM_SIGNAL_STATE_POOR         = 0,
    RCM_SIGNAL_STATE_GOOD         = 1,
    RCM_SIGNAL_STATE_BUTT
};
typedef VOS_UINT16 RCM_SIGNAL_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_IDLE_HAPPY_ENUM_UINT16
 ö��˵��  : modem Idle Happy״̬
             0:Idle Unhappy״̬
             1:Idle Happy״̬
*****************************************************************************/
enum RCM_IDLE_HAPPY_ENUM
{
    RCM_IDLE_HAPPY_UNHAPPY        = 0,
    RCM_IDLE_HAPPY_HAPPY          = 1,
    RCM_IDLE_HAPPY_BUTT
};
typedef VOS_UINT16 RCM_IDLE_HAPPY_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_DPDT_CONTROL_ENUM_UINT16
 ö��˵��  : DPDT�����Ӧ����ģʽ
             0:ֱͨ
             1:����
*****************************************************************************/
enum RCM_TAS_DPDT_CONTROL_ENUM
{
    RCM_TAS_DPDT_PASS_THROUGH         = 0,
    RCM_TAS_DPDT_SWAP                 = 1,
    RCM_TAS_DPDT_BUTT
};
typedef VOS_UINT16 RCM_TAS_DPDT_CONTROL_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_SEARCH_METHOD_ENUM_UINT16
 ö��˵��  : ������������ʽ
             0:����ԭ����������
             1:TASר����������
*****************************************************************************/
enum RCM_TAS_SEARCH_METHOD_ENUM
{
    RCM_TAS_SEARCH_METHOD_ORIGINAL          = 0,
    RCM_TAS_SEARCH_METHOD_TAS               = 1,
    RCM_TAS_SEARCH_METHOD_BUTT
};
typedef VOS_UINT16 RCM_TAS_SEARCH_METHOD_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_AGENTC_DPDT_DELAY_CTRL_ENUM_UINT16
 ö��˵��  : DPDT�ӳ��л�����ָʾ:
             0:�յ�ȡ����Ȩ��Ϣ��ֹͣһ��dpdt����
             1:ȡ��DPDT�ӳ��л�
             2:����DPDT�ӳ��л�
             3:��������DPDTֵ
             4:ȡ��DPDT�����л�
             5:����DPDT�����л�
             6:��������̬���㷨�л�����
*****************************************************************************/
enum RCM_AGENTC_DPDT_CTRL_ENUM
{
    RCM_AGENTC_DPDT_CTRL_STOP                  = 0,
    RCM_AGENTC_DPDT_DELAY_CTRL_STOP            = 1,
    RCM_AGENTC_DPDT_DELAY_CTRL_START           = 2,
    RCM_AGENTC_DPDT_DELAY_CTRL_UPDATE          = 3,
    RCM_AGENTC_DPDT_DIRECT_CTRL_STOP           = 4,
    RCM_AGENTC_DPDT_DIRECT_CTRL_START          = 5,
    RCM_AGENTC_DPDT_DIRECT_CTRL_UPDATE         = 6,
    RCM_AGENTC_DPDT_CTRL_BUTT
};
typedef VOS_UINT16 RCM_AGENTC_DPDT_CTRL_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_INHERIT_STATE_ENUM_UINT16
 ö��˵��  : ����ģ����������
             0:������ģ�������
             1:����ģ�������
*****************************************************************************/
enum RCM_TAS_INHERIT_STATE_ENUM
{
    RCM_TAS_INHERIT_NONEXIST        = 0,
    RCM_TAS_INHERIT_EXIST           = 1,
    RCM_TAS_INHERIT_BUTT
};
typedef VOS_UINT16 RCM_TAS_INHERIT_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_AUTHORIZE_PHY_STATE_ENUM_UINT16
 ö��˵��  : ������Ƿ�����Ȩ
             0:����Ȩ
             1:����Ȩ
*****************************************************************************/
enum RCM_TAS_AUTHORIZE_PHY_STATE_ENUM
{
    RCM_TAS_AUTHORIZE_DISABLE        = 0,
    RCM_TAS_AUTHORIZE_ENABLE         = 1,
    RCM_TAS_AUTHORIZE_BUTT
};
typedef VOS_UINT16 RCM_TAS_AUTHORIZE_PHY_STATE_ENUM_UINT16;


/*****************************************************************************
 ö����    : RCM_PHY_CALL_STATE_ENUM_UINT16
 ö��˵��  : modem Background or Active Call״̬
             0:Active Call״̬
             1:Background Call״̬
 ע��      : ��������Լ��:����call��ö��ֵ����Ϊ1��ǰ��call��ö��ֵ����Ϊ0.
             ���������޸ġ�
*****************************************************************************/
enum RCM_PHY_CALL_STATE_ENUM
{
    RCM_PHY_CALL_ACTIVE           = 0,
    RCM_PHY_CALL_BACKGROUND       = 1,
    RCM_PHY_CALL_BUTT
};
typedef VOS_UINT16 RCM_PHY_CALL_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_PHY_CDMA_STATE_ENUM_UINT16
 ö��˵��  : CDMA���µ��ʶ
             0:CDMA Out Of Use
             1:CDMA In Use
*****************************************************************************/
enum RCM_PHY_CDMA_STATE_ENUM
{
    RCM_PHY_CDMA_OUT_OF_USE     = 0,
    RCM_PHY_CDMA_IN_USE         = 1,
    RCM_PHY_CDMA_STATE_BUTT
};
typedef VOS_UINT16 RCM_PHY_CDMA_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_PHY_ANT_SHARE_STATUS_ENUM_UINT16
 ö��˵��  : CL+G1������״̬��ʶ
             0:L������G1���������ߣ���S2����ֱͨ
             1:L������CDMA�����ߣ���S2���ؽ���
*****************************************************************************/
enum RCM_PHY_ANT_SHARE_STATUS
{
    RCM_PHY_ANT_SHARE_LTE_AND_G1PHY     = 0,
    RCM_PHY_ANT_SHARE_LTE_AND_CDMA      = 1,
    RCM_PHY_ANT_SHARE_BUTT
};
typedef VOS_UINT16 RCM_PHY_ANT_SHARE_STATUS_ENUM_UINT16;



#ifdef LPS_RTT
/*****************************************************************************
 ö����    :VOS_RATMODE_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  :˯�߻���ʱ,����ģʽ����
            ע�⣻˫��˫����ö��ֵ������Э��ջ��DRVЭ��ΪGULT;
            ��Ҫ��DrvInterface.h�е�PWC_COMM_MODE_E����һ��

*****************************************************************************/
enum VOS_RATMODE_ENUM
{
    VOS_RATMODE_GSM                         = 0,
    VOS_RATMODE_WCDMA                       = 1,
    VOS_RATMODE_LTE                         = 2,
    VOS_RATMODE_TDS                         = 3,
    VOS_RATMODE_1X                          = 4,
    VOS_RATMODE_HRPD                        = 5,
    VOS_RATMODE_BUTT
};
typedef VOS_UINT32 VOS_RATMODE_ENUM_UINT32;


#define VOS_VOID void
#endif
/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_REQ_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RF_ID_ENUM_UINT16                       enRFID;                         /* RF ID */
    VOS_UINT16                                  usPriority;                     /* �������ȼ� */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    RCM_RTT_STA_ENUM_UINT16                     enRttSta;                       /* RTT״̬ */
    RCM_TASK_FIXPOS_FLAG_ENUM_UINT16            enFixPosFlag;                   /* 0-�޹̶�����ʱ�� 1-�й̶�����ʱ�� */
    RCM_TASK_LIMITLEN_FLAG_ENUM_UINT16          enLimitedLenFlag;               /* 0-���޳� 1-���޳� */
    RCM_TASK_PERIOD_FLAG_ENUM_UINT16            enPeriodFlag;                   /* 0-���������� 1-�������� */
    RCM_TASK_PREEMPTIND_FLAG_ENUM_UINT16        enPreemptInd;                   /* 0-�������� 1-������ */
    RCM_TASK_RELEASE_PRINCIPAL_ENUM_UINT16      enReleasePrincipal;             /* 0-PHY�ͷ�  1-RCM�ͷ� 2-ֻ��ͨ��PHY�ͷŵĹ̶�ʱ�����޳����� */
    RCM_TASK_IMMEDIATE_ASSIGN_FLAG_ENUM_UINT16  enImmediateAssignFlag;          /* 0-������������ 1-���������� */
    VOS_UINT16                                  usFailCnt;                      /* ����ʧ�ܴ��� */
    VOS_UINT16                                  usFailThd;                      /* �������ʧ�ܴ�������,�����0��ʾ���Ե�ǰ����������ȼ����� */
    VOS_UINT32                                  ulStartPos;                     /* ��������ʱ�� ������д��Чֵ������޹̶�����ʱ����Ϊ�������ʱ�̣�*/
    VOS_UINT32                                  ulLen;                          /* ���񳤶�.���޳����������д��Чֵ,���ܳ���(RCM_CLOCK_PERIOD/4), */
    VOS_UINT32                                  ulMinLen;                       /* ���񵥴η������С����,���б�����д��Чֵ,���ܳ���(RCM_CLOCK_PERIOD/4),������޳�������Ե���ulLen */
    VOS_UINT32                                  ulPeriod;                       /* ������������ڣ�������������������д��Чֵ */
    VOS_UINT32                                  ulPrmptPeriod;                  /* ���޳��������ռͳ������ ��������޳����������д��Чֵ*/
    VOS_UINT32                                  ulPrmptTimeThd;                 /* ���޳����񵥴α���ռʱ������ ��������޳����������д��Чֵ*/
    VOS_UINT32                                  ulTotalPrmptTimeThd;            /* ���޳������������ۼƱ���ռʱ������ ��������޳����������д��Чֵ*/
    VOS_UINT16                                  usTaskSnNum;                    /* ����������ϢЯ����Sn���� */
    VOS_UINT16                                  usReserved;
}PHY_RCM_TASK_REQ_PARA_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_APPLY_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    PHY_RCM_TASK_REQ_PARA_STRU                  stTaskReqPara;                  /* ����������� */
}PHY_RCM_TASK_APPLY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TASK_APPLY_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����������Ӧ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ��32K ��ʱ */
}RCM_PHY_TASK_APPLY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_REL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ͷ�������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                          /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uwRelTaskIdNum;                 /* ��ɾ�������������Ӧ��ausRelTaskId���±� */
    VOS_UINT16                                  ausRelTaskId[RCM_REL_TASK_ID_MAX_NUM]; /* ��ɾ���������� */
}PHY_RCM_TASK_REL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TASK_REL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���������ͷ�������Ӧ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ��32K ��ʱ */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ��,RCMֻ���MODEM��MODEID����ȷ��  */
    VOS_UINT16                                  usRsv2;
}RCM_PHY_TASK_REL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_RELALL_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ȫ���ͷ�������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                          /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_TASK_RELALL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TASK_RELALL_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ȫ�������ͷ�������Ӧ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                          /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ��32K ��ʱ */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usRsv2;                         /* ������ */
}RCM_PHY_TASK_RELALL_CNF_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RCM_AWAKE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : wake������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_AWAKE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_SLEEP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : sleep������Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_SLEEP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TASK_PREEMPT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ռָʾ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    RCM_RF_ID_ENUM_UINT16                       enRfID;                         /* ����ռ��RFID */
    VOS_UINT32                                  ulPreemptPos;                   /* ������ռʱ��*/
    VOS_UINT32                                  ul32KSysTime;                   /* ��ǰ��32K ��ʱ */
}RCM_PHY_TASK_PREEMPT_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_PREEMPT_ACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������ռȷ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RF_ID_ENUM_UINT16                       enRfID;                         /* ����ռ��RFID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    VOS_UINT16                                  usReserved;                     /* ������ */
}PHY_RCM_TASK_PREEMPT_ACK_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TASK_RESUME_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ָ�ָʾ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  ulResumPos;                     /* ����ָ�ʱ��*/
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    VOS_UINT16                                  usRsv2;                         /* ������ */
    VOS_UINT32                                  ul32KSysTime;                   /* ��ǰ��32K ��ʱ */
}RCM_PHY_TASK_RESUME_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_RESUME_ACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ָ�ȷ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
}PHY_RCM_TASK_RESUME_ACK_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ�������ݽṹ
*****************************************************************************/
typedef struct
{
    RCM_CMD_ENUM_UINT16                         enCmdID;                        /* ��ϢCMD���� */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    VOS_UINT32                                  ulStartPos;                     /* ������������ʱ�� */
    VOS_UINT32                                  ulStopPos;                      /* �������Ľ���ʱ�� */
}RCM_PHY_MSG_STRU;


/*****************************************************************************
 �ṹ��    : RCM_PHY_RPT_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ϣ�������ݽṹ
*****************************************************************************/

typedef struct
{
    VOS_UINT16                                  usIndex;                        /* ����ID */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_CMD_ENUM_UINT16                         enCmdID;                        /* ��ϢCMD���� */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    VOS_UINT32                                  ulStartPos;                     /* ������������ʱ�� */
    VOS_UINT32                                  ulStopPos;                      /* �������Ľ���ʱ�� */
}RCM_PHY_RPT_MSG_STRU;


/*****************************************************************************
 �ṹ��    : RCM_PHY_MSG_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����MODE����Ϣ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usRdIdx;                        /* ��ָ�� */
    VOS_UINT16                                  usWrIdx;                        /* дָ�� */
    RCM_PHY_MSG_STRU                            astMsgList[RCM_PHY_ASSIGN_BUF_SIZE];    /* ��Ϣ���� */
}RCM_PHY_MSG_LIST_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_ASSIGN_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ָʾ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ��32K ��ʱ */
    VOS_UINT16                                  usWrIdx;                        /* ��ǰ����assgin��Ϣ��ʱ��WrIdx��ֵ */
    VOS_UINT16                                  usRsv2;                         /* ������ */
}RCM_PHY_ASSIGN_IND_STRU;


/*****************************************************************************
 �ṹ��    : RCM_PHY_ASSIGN_IND_FORTL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ָʾ��Ϣ���ݽṹ����TL
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usTaskSnNum;                    /* �����Sn���к� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ��32K ��ʱ */
    RCM_PHY_MSG_STRU                            stMsg;
}RCM_PHY_ASSIGN_IND_FORTL_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_ASSIGN_ACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������ȷ����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usRsv2;                         /* �����ֶ� */
}PHY_RCM_ASSIGN_ACK_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_CLOCK_CAL_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ʱ��У׼ָʾ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}RCM_PHY_CLOCK_CAL_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_CLOCK_CAL_ACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ʱ��У׼�ϱ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    RCM_DIRECTION_ENUM_UINT16                   enDirection;                    /* �������� */
    VOS_UINT32                                  ulAdjustValue;                  /* �������� */
}PHY_RCM_CLOCK_CAL_ACK_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_OVERTIME_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʱ�ϱ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    VOS_UINT16                                  usRsv2;                         /* ������ */
    VOS_UINT32                                  ulStartPos;                     /* ������������ʱ�� */
    VOS_UINT32                                  ulStopPos;                      /* �������Ľ���ʱ�� */
}RCM_PHY_OVERTIME_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_GET_MSGLISTADDR_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����ȡ��Ϣ���е�ַ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /*_H2ASN_Skip*/ /* ԭ������ */
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_GET_MSGLISTADDR_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_GET_MSGLISTADDR_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������Ϣ���е�ַ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /*_H2ASN_Skip*/ /* ԭ������ */
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usRsv2;                         /* ������ */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ��32K ��ʱ */
    RCM_PHY_MSG_LIST_STRU                      *pstMsgList;                     /* ��Ϣ�����׵�ַ */
}RCM_PHY_GET_MSGLISTADDR_CNF_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TASK_COMPLETE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM����ִ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    RCM_RF_ID_ENUM_UINT16                       enRfID;                         /* �������ڵ�RFID */
    VOS_UINT32                                  ulStartPos;                     /* ��ǰ��ɵ��������������ʱ�� */
}PHY_RCM_TASK_COMPLETE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TASK_COMPLETE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHY�յ�����ִ�����ָʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* ������ */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* ������ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT16                                  usTaskID;                       /* ����ID */
    RCM_RF_ID_ENUM_UINT16                       enRfID;                         /* �������ڵ�RFID */
    RCM_RSLT_ENUM_UINT16                        enResult;                       /* ȷ�Ͻ�� */
    VOS_UINT16                                  usRsv2;                         /* ������ */
    VOS_UINT32                                  uw32KSysTime;                   /* ��ǰ32kʱ�� */
}RCM_PHY_TASK_COMPLETE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RCM_WMODE_TIMING_STRU
 Э����  :
 �ṹ˵��  : Wģϵͳʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwSfnCnt;                              /* SFN��������Χ0~4095 */
    VOS_UINT16                          uhwSlotCnt;                             /* ʱ϶��������Χ0~14 */
    VOS_UINT16                          uhwChipCnt;                             /* chip��������Χ0~2559 */
    VOS_UINT16                          uhwClkCnt;                              /* chip��ʱ�Ӽ�������Χ0~15 */
    RCM_WMODE_TYPE_ENUM_UINT16          enWMode;                                /* Wģ��ʱ������ */
    VOS_UINT16                          uhwReserved;                            /* ����λ */
}RCM_WMODE_TIMING_STRU;

/*****************************************************************************
 �ṹ��    : RCM_GMODE_TIMING_STRU
 Э����  :
 �ṹ˵��  : Gģϵͳʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwFnCnt;                                /* FN���� */
    VOS_UINT16                          uhwQbCnt;                               /* ϵͳ��ʱ֡��Qb��������Χ0~4999 */
    VOS_UINT16                          uhwReserved;                            /* ����λ */
}RCM_GMODE_TIMING_STRU;

/*****************************************************************************
 �ṹ��    : RCM_LTEMODE_TIMING_STRU
 Э����  :
 �ṹ˵��  : LTEģϵͳʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uwSfnCnt;                               /* SFN��������Χ0~1023 */
    VOS_UINT16                          uhwsubfrm_cnt;                          /* ��֡���� */
    VOS_UINT16                          uhwTsCnt;                               /* ��֡�ڼ��� */
    VOS_UINT16                          uhwReserved;                            /* ����λ */
}RCM_LTEMODE_TIMING_STRU;

/*****************************************************************************
 �ṹ��    : RCM_TDMODE_TIMING_STRU
 Э����  :
 �ṹ˵��  : TDģϵͳʱ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          uwSfnCnt;                               /* tcfsrϵͳ��֡��0~65535ѭ��������TDSʵ����Ч��֡��ΧΪ0~8191 */
    VOS_UINT32                          uwSubFrmcnt;                            /* framc֡���� */
}RCM_TDMODE_TIMING_STRU;

/*****************************************************************************
 �ṹ��    : RCM_TIMING_STRU
 Э����  :
 �ṹ˵��  : ��ģϵͳʱ���32K��ʱ
*****************************************************************************/
typedef struct
{
    RCM_WMODE_TIMING_STRU               stWTime;                                /* Wģϵͳʱ�� */
    VOS_UINT32                          uwCTime;                                /* Cģϵͳʱ�� */
    RCM_GMODE_TIMING_STRU               stGmTime;                               /* Gmģϵͳʱ�� */
    RCM_GMODE_TIMING_STRU               stGsTime;                               /* Gsģϵͳʱ�� */
    RCM_LTEMODE_TIMING_STRU             stLTETime;                              /* LTEģϵͳʱ�� */
    RCM_TDMODE_TIMING_STRU              stTDSTime;                              /* TDģϵͳʱ�� */
    VOS_UINT32                          uw32KSysTime;                           /* 32Kϵͳ��ʱ */
}RCM_TIMING_STRU;


/*****************************************************************************
 �ṹ��    : RCM_PHY_START_TAS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHY��ȨTAS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_TAS_DPDT_CONTROL_ENUM_UINT16            enMasterDpdt;                   /* ԭ��ģdpdt״̬ */
    RCM_TAS_INHERIT_STATE_ENUM_UINT16           enInheritCtrl;                  /* ����ģ����������� */
}RCM_PHY_START_TAS_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_START_TAS_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM��Ȩ���ָʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_TAS_DPDT_CONTROL_ENUM_UINT16            enMasterDpdt;                   /* ԭ��ģdpdt״̬ */
    RCM_TAS_INHERIT_STATE_ENUM_UINT16           enInheritCtrl;                  /* ����ģ����������� */
}PHY_RCM_START_TAS_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_STOP_TAS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHYȡ����ȨTAS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_STOP_TAS_TYPE_ENUM_UINT16               enStopTasType;                  /* ȡ��TAS��Ȩ��ʽ */
    VOS_UINT16                                  usRsv2;                         /* �����ֶ� */
}RCM_PHY_STOP_TAS_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_STOP_TAS_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCMȡ����Ȩ���ָʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_STOP_TAS_TYPE_ENUM_UINT16               enStopTasType;                  /* ȡ��TAS��Ȩ��ʽ */
}PHY_RCM_STOP_TAS_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_SET_DPDT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHY����DPDT������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_TAS_DPDT_CONTROL_ENUM_UINT16            enDpdtValue;                    /* DPDT�����֣�0:ֱͨ��1:���� */
    VOS_UINT16                                  usRsv2;                         /* �����ֶ� */
}RCM_PHY_SET_DPDT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_SET_DPDT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM����DPDT���������ָʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_SET_DPDT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TX_BLANKING_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨ����modem TX_BLANKING��ʼʱ�����ֹʱ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  ulStartSlice;                   /* ��ʼslice */
    VOS_UINT32                                  ulStopSlice;                    /* ��ֹslice */
}RCM_PHY_TX_BLANKING_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TX_BLANKING_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM����modem TX_BLANKING��ʼʱ�����ֹʱ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  ulStartSlice;                   /* ��ʼslice */
    VOS_UINT32                                  ulStopSlice;                    /* ��ֹslice */
    VOS_UINT16                                  usDpdtStatus;                   /* �л���dpdt��״̬ */
    VOS_UINT16                                  usRsv2;                         /* �����ֶ� */
}PHY_RCM_TX_BLANKING_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_RATMODE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHY֪ͨRCM��ǰmodem������ģģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_RATMODE_ENUM_UINT32                     enMasterMode;                   /* ��ģģʽ */
    VOS_RATMODE_ENUM_UINT32                     enSlaveMode;                    /* ��ģģʽ */
    RCM_TAS_DPDT_CONTROL_ENUM_UINT16            enMasterDpdt;                   /* ԭ��ģdpdt״̬ */
    RCM_TAS_AUTHORIZE_PHY_STATE_ENUM_UINT16     enPhyAuthorizeFlg;              /* ԭ��ģ��Ȩ״̬ */
}PHY_RCM_RATMODE_IND_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_MSG_HEADER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RCM������㽻����Ϣ�ṹͷ���壬����ȷ��rcm����phy����Ϣ�ṹ���¶��壬
             ��ֵʱӦ��usRsv��Ϊ0����Ϊmsp����Ĵ洢����Ϣ����һ�����ֽ�Ϊ��Ϣid��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}RCM_PHY_MSG_HEADER_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_ACCESS_STATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM PHY Access ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_ACCESS_STATE_ENUM_UINT16                enAccessState;                  /* Access State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_ACCESS_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_CPICH_STATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM PHY CPICH ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_CPICH_STATE_ENUM_UINT16                 enCPICHState;                   /* Access State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_CPICH_STATE_IND_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RCM_SEARCHING_STATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM PHY Searching ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_SEARCHING_STATE_ENUM_UINT16             enSearchingState;               /* Searching State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_SEARCHING_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_SIGNAL_STATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM PHY Signal ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_SIGNAL_STATE_ENUM_UINT16                enSignalState;                  /* Signal State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_SIGNAL_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_IDLE_HAPPY_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM PHY Signal ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_IDLE_HAPPY_ENUM_UINT16                  enIdleHappy;                    /* Idle Happy State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_IDLE_HAPPY_IND_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_VOICE_CALL_STATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RCMת��֪ͨPHY BACKGROUND Call ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_PHY_CALL_STATE_ENUM_UINT16              enVoiceCallState;               /* Voice Call State */
    VOS_UINT16                                  usRsv2;
}RCM_PHY_VOICE_CALL_STATE_IND_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RCM_PAGING_TASK_FAIL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ͳ��PAGINGʧ�ܵ�ԭ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_PAGING_TASK_FAIL_REASON_ENUM_UINT16     enFailReason;
    VOS_UINT16                                  usTaskID;                       /* taskid Ϊ0��ʱ���ʾ��ǰ��֪��taskid�Ƕ��٣���Ҫ����LOG */
}PHY_RCM_PAGING_TASK_FAIL_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_VOICE_CALL_STATE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RCMת��֪ͨPHY BACKGROUND Call ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_PHY_CALL_STATE_ENUM_UINT16              enVoiceCallState;               /* Voice Call State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_VOICE_CALL_STATE_CNF_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RCM_SEARCHING_STATE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM PHY Searching ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_SEARCHING_STATE_ENUM_UINT16             enSearchingState;               /* Searching State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_SEARCHING_STATE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_SEARCHING_STATE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHY����ִ��Searching���ú��ַ�ʽ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_TAS_SEARCH_METHOD_ENUM_UINT16           enSearchMethod;                 /* PHY Search Method */
    VOS_UINT16                                  usRsv2;
}RCM_PHY_SEARCHING_STATE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_AGENTC_SET_DPDT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨ����PHY�л�DPDT���������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_AGENTC_DPDT_CTRL_ENUM_UINT16            enTaskCtrl;                     /* DPDT�л�������� */
    RCM_TAS_DPDT_CONTROL_ENUM_UINT16            enDpdtValue;                    /* DPDT�����֣�0:ֱͨ��1:���� */
}RCM_PHY_AGENTC_SET_DPDT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_AGENTC_SET_DPDT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PHY���л�DPDT�������������Ϣ�Ļظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_AGENTC_DPDT_CTRL_ENUM_UINT16            enTaskCtrl;                     /* DPDT�л�������� */
    RCM_TAS_DPDT_CONTROL_ENUM_UINT16            enDpdtValue;                    /* DPDT�����֣�0:ֱͨ��1:���� */
}PHY_RCM_AGENTC_SET_DPDT_CNF_STRU;


/*****************************************************************************
 �ṹ��    : PHY_RCM_CDMA_WORK_STATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CUse״̬�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    RCM_PHY_MSG_HEADER_STRU                     stMsgHeader;
    RCM_PHY_CDMA_STATE_ENUM_UINT16              enCUseStatus;                   /* CDMA���µ�״̬ */
    VOS_UINT16                                  uhwReserved;                    /* �����ֶ� */
}PHY_RCM_CDMA_WORK_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_ANT_SHARE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������״̬����ṹ��
*****************************************************************************/
typedef struct
{
    RCM_PHY_MSG_HEADER_STRU                     stMsgHeader;
    RCM_PHY_ANT_SHARE_STATUS_ENUM_UINT16        enAntShareState;                /* ������״̬��0:L������G1ģ��1:L������Cģ */
    VOS_UINT16                                  uhwVoLteState;                  /* ����֧��VoLTE״̬��0:��֧�֣�1:֧�� */
}RCM_PHY_ANT_SHARE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_ANT_SHARE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������״̬����ظ��ṹ��
*****************************************************************************/
typedef struct
{
    RCM_PHY_MSG_HEADER_STRU                     stMsgHeader;
    RCM_PHY_ANT_SHARE_STATUS_ENUM_UINT16        enAntShareState;                /* ������״̬��0:L������G1ģ��1:L������Cģ */
    VOS_UINT16                                  uhwVoLteState;                  /* ����֧��VoLTE״̬��0:��֧�֣�1:֧�� */
}PHY_RCM_ANT_SHARE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_ANT_SHARE_TX_BLANKING_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : S3����״̬�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    RCM_PHY_MSG_HEADER_STRU                     stMsgHeader;
    RCM_PHY_ANT_SHARE_STATUS_ENUM_UINT16        enAntShareState;                /* ������״̬��0:L������G1ģ��1:L������Cģ */
    VOS_UINT16                                  uhwTxBlanking;                  /* 0--NoTxBlanking����S3���ش򿪣�1--TxBlanking����S3���ؽӵ� */
}RCM_PHY_ANT_SHARE_TX_BLANKING_IND_STRU;
/*******************************************************************************
 �ṹ��    : RCM_MODE_ID_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽ����Ϣ
*******************************************************************************/
typedef struct
{
    RCM_MODE_ID_ENUM_UINT16                     enModeID;
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* Modem Id */
    RCM_RF_ID_ENUM_UINT16                       enRFId;                         /* Resource Id */
    RCM_DSDS_FLG_ENUM_UINT16                    enDsdsFlg;
} RCM_MODE_ID_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_GET_MODE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHY��RCM��ѯ����ģʽ��������Ϣ���ؽ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usModeIdNum;                    /* ģʽ���� */
    VOS_UINT16                                  usRsv2;                         /* �����ֶ� */
    RCM_MODE_ID_PARA_STRU                       astModeIdPara[RCM_MODE_ID_BUTT];/* ģʽ��Ϣ */
}RCM_PHY_GET_MODE_INFO_STRU;


/*****************************************************************************
 �ṹ��    : RCM_PHY_NOTICE_DSDS_INIT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RCM֪ͨGU����㣬RCM�Ѿ���ɳ�ʼ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usDsdsInitFlag;                 /* 1��ʾ�Ѿ���ɳ�ʼ�� */
}RCM_PHY_NOTICE_DSDS_INIT_IND_STRU;
/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#ifndef LPS_RTT
extern VOS_VOID RCM_DRV_SetWTimeMode( RCM_WMODE_TYPE_ENUM_UINT16 enWModeType );
extern VOS_UINT32 RCM_DRV_32KSysTimeInquire( VOS_VOID );
extern VOS_UINT32 RCM_DRV_TimingInquire( RCM_CMODE_TYPE_ENUM_UINT16 enCModemType,
                                                 RCM_TIMING_STRU* pstTiming );
extern VOS_INT32 RCM_SCHDL_CalcDistance( VOS_UINT32 uwTimeX,
                                                 VOS_UINT32 uwTimeY );
extern VOS_INT32 RCM_SCHDL_GetProtectState(RCM_MODEM_ID_ENUM_UINT16 enModemID);
extern RCM_PHY_GET_MODE_INFO_STRU * RCM_SCHDL_GetModeInfoAddr( VOS_VOID);
#endif

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

#endif /* end of RcmPhyInterface.h */



