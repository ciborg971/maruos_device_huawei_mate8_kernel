
#ifndef _AMON_BALONG_H_
#define _AMON_BALONG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "product_config.h"
#include "osl_types.h"
#include "osl_sem.h"
#include "mdrv_public.h"
#include "hi_amon.h"
#include "soc_interrupts.h"
#include "bsp_softtimer.h"
#include "bsp_amon.h"
#include "drv_amon.h"
#include "bsp_memmap.h"
#include "bsp_clk.h"
#include "bsp_edma.h"
#include "bsp_version.h"
#define amon_log_print printf

#if 0
#define AXI_PHYS_TO_VIRT(phy)           phys_to_virt((unsigned long)phy)
#define AXI_VITR_TO_PHYS(virt)          virt_to_phys((void*)virt)
#else
#define AXI_PHYS_TO_VIRT(phy)           phy
#define AXI_VITR_TO_PHYS(virt)          virt
#endif

/**************************************************************************
                                   �궨��
**************************************************************************/
#define AXI_INT_VECTOR                  INT_LVL_AMON                /* �ж����� */
#define AXI_WAIT_CNT                    1000                        /* �ȴ���λ������ͣ������ɳ��Դ��� */
#define AXI_MAX_PORT                    AXI_MAX_PORT_CNT            /* ����ض˿ڸ��� */
#define AXI_MAX_ID                      AXI_MAX_CONFIG_ID           /* �����ID��Ŀ */
#define AXI_CAPT_THRESHOLD              (50*1024)                   /* EDMA���䳤�� */
#define AXI_EDMA_BINDEX                 128                         /* EDMA��ά���䲽�� */
#define SOC_EDMA_REQUEST                EDMA_AMON_SOC               /* SOC EDMA��������� */
#define CPUFAST_EDMA_REQUEST            EDMA_AMON_CPUFAST           /* CPUFAST EDMA��������� */
#define AXI_SOCP_CHAN_ID                SOCP_CODER_SRC_GU_IND2 /* MONITORʹ�õ�SOCPԴͨ��ID */
#define SOCP_BD_PACKET_SIZE             8                           /* SOCP BD����С */
#define SOCP_BD_BUF_SIZE                (SOCP_BD_PACKET_SIZE*1024)  /* SOCP BD buffer��С */
#define SOCP_RD_PACKET_SIZE             8                           /* SOCP RD����С */
#define SOCP_RD_BUF_SIZE                (SOCP_RD_PACKET_SIZE*1024)  /* SOCP RD buffer��С */
#define AXI_SOCP_PACKET_SIZE            (2*1024)                    /* ÿ2k����SOCP��� */
#define AXI_SOCP_TRAN_WAIT_CNT          5                           /* �ɼ��������ȴ�SOCP������������� */
#define AXI_CAPT_TRAN_OVER_TIME         500                         /* �ɼ�����������ȴ�ʱ�� */
#define AXI_CAPT_CNF_REG_CNT            17                          /* �ɼ���������ظ���Ҫ�ϱ��Ĵ�������Ŀ */
#define AXI_MON_CNF_REG_CNT             35                          /* �����������ظ���Ҫ�ϱ��Ĵ�������Ŀ */
#define AXI_CAPT_CYCLE_DEFAULT          2000                        /* �ɼ�����Ĭ��ֵ */
#define AXI_SOFT_RESET                  0x2                         /* AXI monitor��λ */
#define AXI_RESET_TO_IDLE               0x1                         /* AXI monitorǿ�ƽ���IDLE̬ */
#define AXI_RUN_STATE_MASK              0xC                         /* AXI monitor����״̬ */
#define AXI_RESET_STATE_MASK            0x10                        /* AXI monitor��λ״̬ */
#define AXI_FIFO_DEPTH                  32                          /* Monitor FIFO��� */
#define AMON_MAIN_VERSION               1
#define AMON_MINOR_VERSION              1

/**************************************************************************
                                 �Ĵ�������
**************************************************************************/
/* ����ַ���� */
enum axi_base_addr_enum
{
    AXI_FAST_ADDR_ENUM,             /* cpu fast����ַ*/
    AXI_SOC_ADDR_ENUM,             /* cpu slow ����ַ */
    AXI_CTRL_ADDR_BUTT                   /* ��Чֵ */
};

/* AXI monitor���������÷���: CPUFAST, SOC */
extern u32 g_amon_base_addr[AXI_CTRL_ADDR_BUTT];
#define AXI_MON_CPUFAST_BASE_ADDR       (g_amon_base_addr[AXI_FAST_ADDR_ENUM]) /* AXI monitor CPUFAST����ַ */
#define AXI_MON_SOC_BASE_ADDR           (g_amon_base_addr[AXI_SOC_ADDR_ENUM])     /* AXI monitor SOC����ַ */

/* AXI�ڲ�buffer��ʼ��ַ */
#define CPUFAST_BUFF_BASE_ADDR          (AXI_MON_CPUFAST_BASE_ADDR + 0xA00)
#define SOC_BUFF_BASE_ADDR              (AXI_MON_SOC_BASE_ADDR + 0xA00)

/* AXI monitor�Ĵ���ƫ�Ƶ�ַ���� begin */
#define AXI_MON_CNT_RESET               HI_AMON_CNT_RESET_OFFSET                /* AXI monitorͳ�Ƽ�������λ�Ĵ���  */
#define AXI_MON_CNT_CTRL                HI_AMON_CNT_CTRL_OFFSET                 /* AXI monitorϵͳ���üĴ��� */
#define AXI_MON_CNT_STATE_INT           HI_AMON_CNT_STATE_INT_OFFSET            /* AXI monitorϵͳ״̬�Ĵ��� */
#define AXI_MON_WIN_COUNTER             HI_AMON_WIN_COUNTER_OFFSET              /* AXI monitorϵͳʱ�䴰������ */
#define AXI_MON_IDLE_COUNTER            HI_AMON_IDLE_COUNTER_OFFSET             /* AXI monitorϵͳidleͳ�Ƽ����� */
#define AXI_MON_PORT_SEL                HI_AMON_PORT_SEL_OFFSET                 /* AXI monitor���ID��AXI port���� */
#define AXI_MON_INT_CLR                 HI_AMON_INT_CLR_OFFSET                  /* AXI monitor�ж�����Ĵ��� */
#define AXI_ID_INT_SRC                  HI_AMON_ID_INT_SRC_OFFSET               /* ID��д����ж�ԭʼ�Ĵ��� */
#define AXI_ID_INT_MASK                 HI_AMON_ID_INT_MASK_OFFSET              /* ID��д����ж����μĴ��� */
#define AXI_ID_INT_STAT                 HI_AMON_ID_INT_STAT_OFFSET              /* ID��д����ж�״̬�Ĵ��� */

/* nΪport��ȡֵ��Χ0-7 */
#define AXI_MON_RD_WAIT_CYCLE_PORTS(n)  (HI_AMON_RD_WAIT_CYCLE_PORTS_0_OFFSET + n*0x10)   /* ���PORTsΪ��ȷ��λ���ȴ����������ĵ�ʱ�����ڼĴ��� */
#define AXI_MON_WR_WAIT_CYCLE_PORTS(n)  (HI_AMON_WR_WAIT_CYCLE_PORTS_0_OFFSET + n*0x10)   /* ���PORTsΪ��ȷ��λд�ȴ����������ĵ�ʱ�����ڼĴ��� */
/* nΪID, ȡֵ��Χ0-7 */
#define AXI_MON_CNT_TYPE(n)             (HI_AMON_CNT_TYPE_0_OFFSET + n*0x4)         /* ���ID�ļ������ѡ�� */
#define AXI_MON_CNT_ID(n)               (HI_AMON_CNT_ID_0_OFFSET + n*0x100)         /* AXI monitorϵͳID��Ϣ�Ĵ��� */
#define AXI_MON_ID_ADDR_DES(n)          (HI_AMON_ID_ADDR_DES_0_OFFSET + n*0x100)    /* ��ص�ַ�±߽� */
#define AXI_MON_ID_ADDR_DES_M(n)        (HI_AMON_ID_ADDR_DES_M_0_OFFSET + n*0x100)  /* ��ص�ַ�ϱ߽� */

/* ͳ�Ƽ����� begin */
#define AXI_MON_INCR1_ID(n)             (HI_AMON_INCR1_ID_0_OFFSET + n*0x100)               /* ���ID n����INCR1���������� */
#define AXI_MON_INCR2_ID(n)             (HI_AMON_INCR2_ID_0_OFFSET + n*0x100)               /* ���ID n����INCR2���������� */
#define AXI_MON_INCR4_ID(n)             (HI_AMON_INCR4_ID_0_OFFSET + n*0x100)               /* ���ID n����INCR4���������� */
#define AXI_MON_INCR8_ID(n)             (HI_AMON_INCR8_ID_0_OFFSET + n*0x100)               /* ���ID n����INCR8���������� */
#define AXI_MON_INCR16_ID(n)            (HI_AMON_INCR16_ID_0_OFFSET + n*0x100)              /* ���ID n����INCR16���������� */
#define AXI_MON_WRAP_ID(n)              (HI_AMON_WRAP_ID_0_OFFSET + n*0x100)                /* ���ID n����WRAP���������� */
#define AXI_MON_BURST_ID(n)             (HI_AMON_BURST_ID_0_OFFSET + n*0x100)               /* ���ID n����BURST���������� */
#define AXI_MON_FINISH_ID(n)            (HI_AMON_FINISH_ID_0_OFFSET + n*0x100)              /* ���ID n���BURST���������� */
#define AXI_MON_RD_WAIT_ID_LOW(n)       (HI_AMON_READ_WAIT_ID_0_OFFSET + n*0x100)           /* ���ID n���ȴ����ڼ���������32λ(64λ�Ĵ�����0~43��Ч) */
#define AXI_MON_RD_WAIT_ID_HIGH(n)      (HI_AMON_READ_WAIT_ID_0_OFFSET + 0x4 + n*0x100)     /* ���ID n���ȴ����ڼ���������32λ(64λ�Ĵ�����0~43��Ч) */
#define AXI_MON_WR_WAIT_ID_LOW(n)       (HI_AMON_WRITE_WAIT_ID_0_OFFSET + n*0x100)          /* ���ID nд�ȴ����ڼ���������32λ(64λ�Ĵ�����0~43��Ч) */
#define AXI_MON_WR_WAIT_ID_HIGH(n)      (HI_AMON_WRITE_WAIT_ID_0_OFFSET + 0x4 + n*0x100)    /* ���ID nд�ȴ����ڼ���������32λ(64λ�Ĵ�����0~43��Ч) */
#define AXI_MON_WR_WAIT_RESP_ID_LOW(n)  (HI_AMON_WRITE_WAIT_RESP_ID_0_OFFSET + n*0x100)     /* ���ID nд��Ӧ�ȴ����ڼ���������32λ(64λ�Ĵ�����0~43��Ч) */
#define AXI_MON_WR_WAIT_RESP_ID_HIGH(n) (HI_AMON_WRITE_WAIT_RESP_ID_0_OFFSET + 0x4 + n*0x100)/* ���ID nд��Ӧ�ȴ����ڼ���������32λ(64λ�Ĵ�����0~43��Ч) */
#define AXI_MON_RD_MAX_WAIT_ID(n)       (HI_AMON_READ_MAX_WAIT_ID_0_OFFSET + n*0x100)       /* ���ID n�����ȴ����ڼ����� */
#define AXI_MON_WR_MAX_WAIT_ID(n)       (HI_AMON_WRITE_MAX_WAIT_ID_0_OFFSET + n*0x100)      /* ���ID nд���ȴ����ڼ����� */
#define AXI_MON_WR_MAX_WAIT_RESP_ID(n)  (HI_AMON_WRITE_MAX_WAIT_RESP_ID_0_OFFSET + n*0x100) /* ���ID nд��Ӧ���ȴ����ڼ����� */
#define AXI_MON_RD_BYTES_ID_LOW(n)      (HI_AMON_READ_BYTES_ID_0_OFFSET + n*0x100)          /* ���ID n������������byteΪ��λ����32λ(64λ�Ĵ�����0~39��Ч) */
#define AXI_MON_RD_BYTES_ID_HIGH(n)     (HI_AMON_READ_BYTES_ID_0_OFFSET + 0x4 + n*0x100)    /* ���ID n������������byteΪ��λ����32λ(64λ�Ĵ�����0~39��Ч) */
#define AXI_MON_WR_BYTES_ID_LOW(n)      (HI_AMON_WRITE_BYTES_ID_0_OFFSET + n*0x100)         /* ���ID nд����������byteΪ��λ����32λ(64λ�Ĵ�����0~39��Ч) */
#define AXI_MON_WR_BYTES_ID_HIGH(n)     (HI_AMON_WRITE_BYTES_ID_0_OFFSET + 0x4 + n*0x100)   /* ���ID nд����������byteΪ��λ����32λ(64λ�Ĵ�����0~39��Ч) */
/* ͳ�Ƽ����� end */

/* �ɼ��Ĵ��� begin */
#define AXI_CAPT_CTRL                   (HI_AMON_CAPT_CTRL_OFFSET)              /* �������ݲɼ���ʼ�ͽ��� */
#define AXI_CAPT_ID_EN                  (HI_AMON_CAPT_ID_EN_OFFSET)             /* ����ʹ�ܼĴ��� */
#define AXI_CAPT_TRAN_CONFIG            (HI_AMON_CAPT_CONFIG_OFFSET)            /* �ɼ��������üĴ��� */
#define AXI_CAPT_ID(id)                 (HI_AMON_CAPT_ID_0_OFFSET + id*0x4)     /* ID��Ϣ�Ĵ��� */
#define AXI_CAPT_INT_SRC                (HI_AMON_CAPT_INT_SRC_OFFSET)           /* �ɼ�ԭʼ�жϼĴ��� */
#define AXI_CAPT_INT_MASK               (HI_AMON_CAPT_INT_MASK_OFFSET)          /* �ɼ��ж����μĴ��� */
#define AXI_CAPT_INT_STATE              (HI_AMON_CAPT_INT_STATE_OFFSET)         /* �ɼ��ж�״̬�Ĵ��� */
#define AXI_CAPT_INT_CLR                (HI_AMON_CAPT_INT_CLR_OFFSET)           /* �ɼ��ж�����Ĵ��� */
#define AXI_CAPT_ERR_STATE              (HI_AMON_AXI_STATE_OFFSET)              /* ��д����ָʾ״̬�Ĵ��� */
#define AXI_CAPT_TRANS_WAIT_TIME        (HI_AMON_CAPT_TRANS_WAIT_TIME_OFFSET)   /* ���ݰ��������ж��ϱ��ȴ�ʱ���Ĵ��� */
#define AXI_CAPT_TRANS_DATA_CNT         (HI_AMON_TRANS_DATA_CNT_OFFSET)         /* ���ݰ�����ͳ�ƼĴ���, ��ŵ�11λ�Լ���λ��־ */
#define AXI_CAPT_TRANS_DATA_CNT_HIGH    (HI_AMON_TRANS_DATA_CNT_HIGH_OFFSET)    /* ���ݰ�����ͳ�ƼĴ���, ��Ÿ�20λ */
#define AXI_CAPT_TRANS_DATA_LEVEL       (HI_AMON_TRANS_DATA_LEVEL_OFFSET)       /* ���ݰ�����ֵ���üĴ��� */
#define AXI_CAPT_CMD_PKG_SIZE           (HI_AMON_CMD_PKG_SIZE_OFFSET)           /* ��������ȼĴ��� */
#define AXI_CAPT_DATA_PKG_SIZE          (HI_AMON_DATA1_PKG_SIZE_OFFSET)         /* ���ݰ����ȼĴ��� */
#define AXI_CAPT_EXT_PKG_SIZE           (HI_AMON_DATA2_PKG_SIZE_OFFSET)         /* ���Ӱ����ȼĴ��� */
#define AXI_CAPT_DMA_REQ_TYPE           (HI_AMON_DMA_REQ_EN_OFFSET)             /* DMA��������Ĵ��� */
#define AXI_CAPT_HEAD_FLAG              (0x960)                                 /* ��ͷ��־�Ĵ��� */
#define AXI_CAPT_FIFO_ADDR              (0xa00)                                 /* Monitor FIFO��ַ */
/* �ɼ��Ĵ��� end */

/* AXI monitor�Ĵ���ƫ�Ƶ�ַ���� end */

/**************************************************************************
                               ���ݽṹ����
**************************************************************************/


/* ʱ�䴰���� */
enum axi_win_config_enum
{
    AXI_WIN_DISABLE,            /* ʱ�䴰��ʹ�� */
    AXI_WIN_ENABLE,             /* ʱ�䴰ʹ�� */
    AXI_WIN_BUTT
};
typedef unsigned char axi_win_config_enum_uint8;

/* ��ȡAXI monitor״̬���� */
enum axi_get_state_req_enum
{
    AXI_GET_RUN_STATE_REQ,      /* ��ȡ����״̬ */
    AXI_GET_RESET_STATE_REQ,    /* ��ȡ��λ״̬ */
    AXI_GET_STATE_REQ_BUTT
};
typedef unsigned int axi_get_state_req_enum_uint32;

/* AXI monitor״̬ */
enum axi_state_enum
{
    AXI_IDLE            = 0x0,  /* IDLE״̬ */
    AXI_WIN_RUNNING     = 0x4,  /* ��ʱ�䴰�ļ��״̬ */
    AXI_UNWIN_RUNNING   = 0x8,  /* ����ʱ�䴰�ļ��״̬ */
    AXI_STOP            = 0xC,  /* STOP״̬ */
    AXI_RESET_FINISH    = 0x10, /* ��λ��� */
    AXI_STATE_BUTT      = 0xFFFFFFFF
};
typedef unsigned int axi_state_enum_uint32;

/* �ɼ�״̬�л� */
enum axi_capt_full_state_enum
{
    AXI_CAPT_NORMAL             = 0x1,      /* ����״̬ */
    AXI_CAPT_FULL               = 0x2,      /* buffer�� */
    AXI_CAPT_FINISHING          = 0x4,      /* �ȴ�������� */
    AXI_CAPT_STOP_REQ           = 0x8,      /* stop���� */
    AXI_CAPT_PERIOD_STOP_REQ    = 0x10,     /* ���ڲɼ�stop���� */
    AXI_CAPT_BUTT                           /* ��Чֵ */
};
typedef unsigned int axi_capt_state_enum_uint32;

/* �ɼ�ID���� */
typedef struct
{
	u32 	id_en;				/* ʹ�� */
	u32 	id_value;			/* ID */
	u32 	mask;				/* ���� */
} axi_capt_id_config_t;

/* �ɼ��������� ����ģʽ */
typedef struct
{
    u32 	mode;			    /* ����Monitor����ģʽ��0:CPUFAST 1:SOC */
	u32 	port;	    		/* ��ض˿� */
	u32 	op_type;			/* �������ͣ�0:������ 1:д���� */
	u32 	dma_req_level;	    /* DMA���󷢳����� */
	u32 	cmd_pkg_len;		/* ��������� */
	u32 	data_pkg_len;		/* ���ݰ����� */
	u32 	ext_pkg_len;		/* ���Ӱ����� */
	u32 	data_trans_thr;		/* ���ݴ�����ֵ */
	u32 	dma_req_type;		/* DMA�������� */
    u32 	capt_cycle;         /* �ɼ����� */
	axi_capt_id_config_t id_cfg[AXI_MAX_ID];	/* �ɼ�ID���� */
} axi_capt_config_t;

/* �Ĵ������� */
typedef struct
{
	u32 	reg_offset;		    /* �Ĵ���ƫ�� */
	u32 	reg_value;			/* �Ĵ���ֵ */
} reg_config_t;

/* �ɼ�������������󣬼Ĵ�������ģʽ */
typedef struct
{
	u32 	        mode;	    /* ����Monitor����ģʽ��0:CPUFAST 1:SOC */
    u32             capt_cycle; /* �ɼ����� */
	u32 	        reg_cnt;	/* �Ĵ���������Ŀ */
	reg_config_t    reg_cfg[];  /* �Ĵ������� */
} axi_reg_config_t;

/* ������������ */
enum axi_ctrl_type_enum
{
    AXI_CTRL_START,             /* ���� */
    AXI_CTRL_STOP,              /* ֹͣ */
    AXI_CTRL_EXPORT,            /* ���� */
    AXI_CTRL_BUTT               /* ��Чֵ */
};
typedef unsigned int   axi_ctrl_type_enum_uint32;



/* ������������������ֹͣ������ */
typedef struct
{
	u32 	                    mode;		/* ����Monitor����ģʽ��0:CPUFAST 1:SOC */
	axi_ctrl_type_enum_uint32 	ctrl_type;	/* �����������ͣ�0:���� 1:ֹͣ 2:���� */
} axi_ctrl_t;

/* ��ز����������� */
typedef struct
{
    u32    incr_1:1;   /* INCR����ͳ������: \
                          0 - INCR1��������������\
                          1 - INCR1д������������*/
    u32    incr_2:1;   /* INCR����ͳ������: \
                          0 - INCR2��������������\
                          1 - INCR2д������������*/
    u32    incr_4:1;   /* INCR����ͳ������: \
                          0 - INCR4��������������\
                          1 - INCR4д������������*/
    u32    incr_8:1;   /* INCR����ͳ������: \
                          0 - INCR8��������������\
                          1 - INCR8д������������*/
    u32    incr_16:1;  /* INCR����ͳ������: \
                          0 - INCR16��������������\
                          1 - INCR16д������������*/
    u32    wrap:2;     /* WRAP����ͳ������: \
                          00 - WRAP4��������������\
                          01 - WRAP4д������������\
                          10 - WRAP8��������������\
                          11 - WRAP8д������������*/
    u32    bur_send:1; /* burst����ͳ������: \
                          0 - ͳ��burst��������������\
                          1 - ͳ��burstд������������*/
    u32    but_fin:1;  /* burst���ͳ������: \
                          0 - ͳ��burst�������������\
                          1 - ͳ��burstд�����������*/
    u32    wr_wait:1;  /* д�ȴ���������: \
                          0 - ͳ��д������д��һ�����ݵ��ӳ�\
                          1 - ͳ��д������д���һ�����ݵ��ӳ�*/
    u32    reserved:22;
} axi_opt_type_t;

/* ���ID���� */
typedef struct
{
	u32             id_en;			/* IDʹ�� */
	u32 	        port;			/* ��ض˿� */
    u32             id_mon_en;      /* ���master IDʹ�� */
	u32 	        id_value;		/* ID */
	u32 	        mask;			/* ���� */
	u32 	        addr_en;		/* ��ַ���ʹ�� */
	u32 	        addr_start;	    /* ��ʼ��ַ */
	u32 	        addr_end;		/* ������ַ */
	axi_opt_type_t	opt_type;		/* �������� */
} axi_mon_id_config_t;

/* ����������� ����ģʽ */
typedef struct
{
    u32 			    mode;			        /* ����Monitor����ģʽ��0:CPUFAST 1:SOC */
	u32 			    win_en;			        /* ʱ�䴰ʹ�� 0:��ʹ�� 1:ʹ�� */
	axi_mon_id_config_t id_config[AXI_MAX_ID];  /* �ɼ�ID���� */
} axi_mon_config_t;

/* �ж�ͳ�� */
typedef struct
{
    u32     win_over;               /* ʱ�䴰�����ж� */
    u32     tran_thresh;            /* ������ֵ�ж� */
    u32     tran_req;               /* ���������ж� */
    u32     tran_over;              /* ��������ж� */
    u32     buff_over;              /* ����buffer���ж� */
    u32     edma_tran_over;         /* edma��������ж� */
} axi_int_stat_t;

/* �ɼ�ȫ�ּ�¼ */
typedef struct
{
    axi_int_stat_t          int_stat;       /* �ж�ͳ�� */
    axi_config_enum_uint32  capt_mode;      /* �ɼ�ģʽ */
    axi_config_enum_uint32  mon_mode;       /* ���ģʽ */
    struct softtimer_list   axi_timer;      /* timer, �������ڲɼ� */
    osl_sem_id              capt_sem;       /* �ɼ��ź��� */
    u32                     capt_cycle;     /* �ɼ����� */
    u32                     tran_over_flag; /* ���������־ */
    u32                     capt_edma_len;  /* edma���䳤�� */
    u32                     edma_bindex;    /* ��άEDMA���䲽�� */
    u32                     axi_buf_full;   /* ���ػ��������� */
    u32                     edma_tran_fail; /* edma����ʧ�ܴ��� */
    u32                     socp_buf_full;  /* socp����ʧ�ܴ��� */
    u32                     socp_tran_fail; /* socp����ʧ�ܴ��� */
    u32                     mon_ind_cnt;    /* ����ϱ�����ͳ�� */
    u32                     mon_ind_fail_cnt; /* ����ϱ�ʧ�ܴ��� */
} axi_global_stat_t;

/* ʱ�ӿ��� */
typedef struct
{
    u32                     is_clk_enable[AXI_CONFIG_BUTT]; /* ʱ���Ƿ�ʹ�� */
    struct clk *            sc_clk[AXI_CONFIG_BUTT];        /* Monitorϵͳʱ�� */
} axi_clk_ctrl_t;

/* ѭ��buffer */
typedef struct
{
    u8 *    start;     /* ѭ��bufferͷָ�� */
    u8 *    end;       /* ѭ��bufferβָ�� */
    u8 *    read;      /* ѭ��buffer��ָ�� */
    u8 *    write;     /* ѭ��bufferдָ�� */
} ring_buf_info_t;

/* ѭ��buffer����������Ϣ */
typedef struct
{
   u8 *     p_buf_1;    /* ����bufferָ�� */
   u32      size_1;     /* ����buffer��С */
   u8 *     p_buf_2;    /* �ؾ����bufferָ�� */
   u32      size_2;     /* �ؾ����buffer��С */
} ring_idle_buf_t;

/* ѭ��buffer����������Ϣ */
typedef ring_idle_buf_t ring_data_buf_t;

/******************amon_addr_balong.c********************************/



typedef struct
{
    u32 soc_rd_cnt[AXI_MAX_CONFIG_ID];
    u32 soc_wr_cnt[AXI_MAX_CONFIG_ID];
    u32 cpufast_rd_cnt[AXI_MAX_CONFIG_ID];
    u32 cpufast_wr_cnt[AXI_MAX_CONFIG_ID];
} amon_stat_t;

typedef struct
{
    char *  buff;           /* buffer��ַ */
    u32     buff_size;      /* buffer��С */
    u32     write_offset;   /* дָ��λ�� */
} amon_buff_info_t;

/* �͹���: �Ĵ������ݡ��ָ� */
typedef struct
{ 
    u32     ctrl_reg;                           /* ���ƼĴ��� begin */
    u32     port_reg;
    u32     int_mask;
    u32     id_reg[AXI_MAX_CONFIG_ID];
    u32     addr_start_reg[AXI_MAX_CONFIG_ID];
    u32     addr_end_reg[AXI_MAX_CONFIG_ID];   /* ���ƼĴ��� end */
    u32     incr1_reg[AXI_MAX_CONFIG_ID];      /* ͳ�ƼĴ��� begin */
    u32     incr2_reg[AXI_MAX_CONFIG_ID]; 
    u32     incr4_reg[AXI_MAX_CONFIG_ID];
    u32     incr8_reg[AXI_MAX_CONFIG_ID]; 
    u32     incr16_reg[AXI_MAX_CONFIG_ID]; 
    u32     wrap_reg[AXI_MAX_CONFIG_ID]; 
    u32     burst_send_reg[AXI_MAX_CONFIG_ID]; 
    u32     burst_fin_reg[AXI_MAX_CONFIG_ID]; 
    u32     rd_cnt_low_reg[AXI_MAX_CONFIG_ID];
    u32     rd_cnt_high_reg[AXI_MAX_CONFIG_ID];
    u32     wr_cnt_low_reg[AXI_MAX_CONFIG_ID];
    u32     wr_cnt_high_reg[AXI_MAX_CONFIG_ID];/* ͳ�ƼĴ��� end */   
} axi_reg_bak_t;

typedef enum{
    amon_cpufast_srst_en = 0,
    amon_cpufast_srst_dis = 1,
    amon_cpufast_monitor_start = 2,
    amon_cpufast_dts_butt
}AMON_CPUFAST_DTS_SYSCTRL;

typedef enum{
    amon_soc_srst_en = 0,
    amon_soc_srst_dis = 1,
    amon_soc_monitor_start = 2,
    amon_soc_dts_butt
}AMON_SOC_DTS_SYSCTRL;
typedef enum{
    AMON_BASE_ADDR = 0,
    AMON_START_BIT,
    AMON_END_BIT,
    AMON_ADDR_BUTT
}AMON_DTS_SYSCTRL_ADDR;

struct amon_sysctrl{
    u32 base_addr;
    u32 start_bit;
    u32 end_bit;
};

struct amon_sysctrl_struct
{
    struct amon_sysctrl amon_sysctrl_soc[amon_soc_dts_butt];
    struct amon_sysctrl amon_sysctrl_fast[amon_cpufast_dts_butt];
};

typedef enum{
    AMON_START_TIME = 0,
    AMON_END_TIME = 1,
    AMON_TIME_BUTT
}AMON_BUS_STRESS_TIME;

struct amon_ctrl_struct
{
    u32 busStressTime[AXI_CONFIG_BUTT][AMON_TIME_BUTT];
    struct clk * soc_clk;
    struct clk * cpufast_clk;
    u32          chip_version;
};
/*bus streess start*/
#define STRESS_TIME_FREQ     (1920000)/*1.92Mʱ��*/

#ifdef BSP_CONFIG_HI3650 
#define MODEM_BUS_FREQ      (50)/*����Ƶ��,50MHZ*/
#define MODEM_PORT_WITH     (MODEM_BUS_FREQ * 8 * 1024 * 1024)/*ÿ��port���ܴ�����λbytes/s*/
#else
/*ÿ��port���ܴ���*/
#define MODEM_BUS_FREQ      (50)/*����Ƶ��,50MHZ*/
#define MODEM_PORT_WITH     (MODEM_BUS_FREQ * 8 * 1024 * 1024)/*bytes/s*/
#endif

/*bus streess end*/




#define AMON_IS_VALID_ADDR(addr) ((addr != 0x0) ? true:false)


#define amon_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR,   BSP_MODU_AMON, "[amon] %s:"fmt, __FUNCTION__, ##__VA_ARGS__))
#define amon_debug(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_FATAL,   BSP_MODU_AMON, fmt, ##__VA_ARGS__))


/********************************************************************************/
/*    �����ࡢamon ϵͳ����������ģ�飨sc_ģ����_����)   */
/********************************************************************************/
extern struct amon_sysctrl_struct g_amon_sysctrl;
extern struct amon_ctrl_struct g_amon_ctrl;
static inline void hi_amon_set_reg(unsigned int value,unsigned int base,unsigned int offset,unsigned int lowbit,unsigned highbit)
{
    unsigned int reg    = base + offset;
    unsigned int temp   = 0;
    unsigned int mask   = 0;

    temp   = readl(reg);
    /*lint -save -e701*/
    mask   = ((1 << (highbit - lowbit + 1)) - 1) << lowbit;
    /*lint -restore*/
    value  = (temp & (~mask)) | ((value <<lowbit) & mask);
    writel(value  ,reg);

}
static inline u32 hi_amon_get_reg(unsigned int base,unsigned int offset,unsigned int lowbit,unsigned int highbit)
{
    unsigned int mask = 0;
    unsigned int temp = 0;
    unsigned int reg    = base + offset;
    u32 value = 0;

    temp   = readl(reg);
    /*lint -save -e701*/
    mask   = ((1 << (highbit - lowbit + 1)) -1) << lowbit;
    /*lint -restore*/
    value = temp & mask;
    value = (value) >> lowbit; 

    return value;
}


/* AXI Monitor CPUFAST ��λ */
static __inline__ void amon_cpufast_soft_reset(void)
{

    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_srst_en].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_srst_en].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_srst_en].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        hi_amon_set_reg(1, base_addr, 0, start_bit, end_bit);
    }
}

/********************************************************************************/
/*    ��λ���⸴λ�ࣨsc_ģ����_����)   */
/********************************************************************************/

/* AXI Monitor SOC ��λ */
static __inline__ void amon_soc_soft_reset(void)
{

    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_srst_en].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_srst_en].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_srst_en].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
	{
        hi_amon_set_reg(1, base_addr, 0, start_bit, end_bit);
    }
}

/* AXI Monitor CPUFAST �⸴λ */
static __inline__ void amon_cpufast_rls_reset(void)
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_srst_dis].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_srst_dis].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_srst_dis].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        hi_amon_set_reg(1, base_addr, 0, start_bit, end_bit);
    }
}

/* AXI Monitor SOC �⸴λ */
static __inline__ void amon_soc_rls_reset(void)
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_srst_dis].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_srst_dis].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_srst_dis].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        hi_amon_set_reg(1, base_addr, 0, start_bit, end_bit);
    }
}
/********************************************************************************/
/*    syssc ������AXI Monitorģ�飬������ֹͣ)                                  */
/********************************************************************************/
/* ����CPUFAST, ���������λΪ1����Ҫ��д0����д1 */
/*lint -save -e528*/
static __inline__ void amon_cpufast_start(void)/*lint !e528*/
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        if(hi_amon_get_reg(base_addr, 0, start_bit, end_bit))
        {
            hi_amon_set_reg(0, base_addr, 0, start_bit, end_bit);
        }
        hi_amon_set_reg(1, base_addr, 0, start_bit, end_bit);
    }
}



/* ����SOC, ���������λΪ1����Ҫ��д0����д1 */
static __inline__ void amon_soc_start(void)/*lint !e528*/
{

    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        if(hi_amon_get_reg(base_addr, 0, start_bit, end_bit))
        {
            hi_amon_set_reg(0, base_addr, 0, start_bit, end_bit);
        }
        hi_amon_set_reg(1, base_addr, 0, start_bit, end_bit);
    }
}


/* ֹͣCPUFAST */
static __inline__ void amon_cpufast_stop(void)/*lint !e528*/
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        hi_amon_set_reg(0, base_addr, 0, start_bit, end_bit);
    }
}


/* ֹͣSOC */
static __inline__ void amon_soc_stop(void)/*lint !e528*/
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
	{
        hi_amon_set_reg(0, base_addr, 0, start_bit, end_bit);
    }
}
/* ��ȡCPUFAST �Ƿ�ʹ��*/
static __inline__ u32 amon_cpufast_state(void)/*lint !e528*/
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
    {
        return hi_amon_get_reg(base_addr, 0, start_bit, end_bit);
    }
    else
    {
        return 0;
    }
}


/* ��ȡCPUFAST �Ƿ�ʹ��*/
static __inline__ u32 amon_soc_state(void)/*lint !e528*/
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].end_bit;

    if(AMON_IS_VALID_ADDR(base_addr))
	{
        return hi_amon_get_reg(base_addr, 0, start_bit, end_bit);
    }
    else
    {
        return 0;
    }

}

/* AXI Monitor CPUFAST ʱ��ʹ�� */
static __inline__ void amon_cpufast_clk_enable(void)/*lint !e528*/
{
    if(clk_enable(g_amon_ctrl.cpufast_clk))
    {
        amon_error("enable fast clk fail\n");
    }
}

/* AXI Monitor SOC ʱ��ʹ�� */
static __inline__ void amon_soc_clk_enable(void)/*lint !e528*/
{
    if(clk_enable(g_amon_ctrl.soc_clk))
    {
        amon_error("enable soc clk fail\n");
    }
}
/* AXI Monitor CPUFAST ʱ��ȥʹ�� */
static __inline__ void amon_cpufast_clk_disable(void)/*lint !e528*/
{
    clk_disable(g_amon_ctrl.cpufast_clk);
}

/* AXI Monitor SOC ʱ��ȥʹ�� */
static __inline__ void amon_soc_clk_disable(void)/*lint !e528*/
{
    clk_disable(g_amon_ctrl.soc_clk);
}

/*lint -restore*/       


/**************************************************************************
                                ��������
**************************************************************************/
/* AXI�Ĵ��������� */
void axi_reg_read(axi_config_enum_uint32 config, u32 reg, u32 * value);
#define AXI_REG_READ(config, reg, value)                axi_reg_read(config, reg, value)
/* AXI�Ĵ���д���� */

void axi_reg_write(axi_config_enum_uint32 config, u32 reg, u32 value);
#define AXI_REG_WRITE(config, reg, value)               axi_reg_write(config, reg, value)
/* AXI�Ĵ�����λ���� */
void axi_reg_getbits(axi_config_enum_uint32 config, u32 reg, u32 pos, u32 bits, u32 * value);
#define AXI_REG_GETBITS(config, reg, pos, bits, value)  axi_reg_getbits(config, reg, pos, bits, value)
/* AXI�Ĵ���дλ���� */
void axi_reg_setbits(axi_config_enum_uint32 config, u32 reg, u32 pos, u32 bits, u32 value);
#define AXI_REG_SETBITS(config, reg, pos, bits, value)  axi_reg_setbits(config, reg, pos, bits, value)
#ifdef ENABLE_BUILD_AMON
void axi_sc_clk_open(axi_config_enum_uint32 config);
void axi_sc_clk_close(axi_config_enum_uint32 config);
void axi_sc_mon_start(axi_config_enum_uint32 config);
void axi_sc_mon_stop(axi_config_enum_uint32 config);
void axi_sc_reset(void);
void axi_reset_pkg_buf(axi_config_enum_uint32 config);
void axi_get_data_buf(ring_data_buf_t * data_buf, ring_buf_info_t * ring_buf);
void axi_get_idle_buf(ring_idle_buf_t * idle_buf, ring_buf_info_t * ring_buf);
s32 axi_socp_src_chan_init(void);
s32 axi_gen_bd_packet(ring_data_buf_t * data_buf, u32 * tran_len);
s32 axi_data_buf_update(ring_buf_info_t * ring_buf);
s32 axi_edma_get_tran_len(ring_buf_info_t * ring_buf);
u32 axi_get_edma_cnt(u32 channel_id);
void axi_socp_timer_handler(u32 param);
s32 axi_socp_start_timer(u32 time_out);
void axi_edma_int_handler(u32 param, u32 int_status);
s32 axi_edma_config_init(axi_config_enum_uint32 config, u32 bindex);
s32 axi_edma_free(axi_config_enum_uint32 config);
axi_state_enum_uint32 axi_get_state(axi_config_enum_uint32 config, axi_get_state_req_enum_uint32 state_req);
s32 axi_state_check(axi_config_enum_uint32 config);
void axi_win_over_int_handler(void);
void axi_tran_int_handler(void);
void axi_tran_int_handler_k3(void);
void axi_int_handler(void);
void axi_int_handler_k3(void);
s32 axi_reset(axi_config_enum_uint32 config);
s32 axi_init(void);
s32 axi_mon_start(axi_config_enum_uint32 config);
s32 axi_mon_stop(axi_config_enum_uint32 config);
s32 axi_capt_start(axi_config_enum_uint32 axi_mode);
s32 axi_capt_stop(axi_config_enum_uint32 config);
void axi_stop_timer(void);
void axi_timer_handler(u32 param);
s32 axi_start_timer(u32 time_out);
void axi_capt_config(axi_capt_config_t * capt_config);
void axi_mon_config(axi_mon_config_t * mon_config);
AXI_DATA_CONFIG_CNF_STRU * axi_capt_set_cnf(axi_config_enum_uint32 mode, u32 * out_len);
AXI_MON_CONFIG_CNF_STRU * axi_mon_set_cnf(axi_config_enum_uint32 mode, u32 * out_len);
void axi_mon_get_reg_value(axi_config_enum_uint32 mode, AXI_MON_TERMINATE_CNF_STRU * ter_cnf);
AXI_MON_TERMINATE_CNF_STRU * axi_mon_set_statistic_data(axi_config_enum_uint32 mode, u32 * out_len);
s32 axi_mon_info_gen_packet(axi_config_enum_uint32 mode);
s32 axi_capt_ctrl_start(axi_config_enum_uint32 mode);
s32 axi_capt_ctrl_stop(axi_config_enum_uint32 mode);
s32 axi_capt_ctrl_export(axi_config_enum_uint32 mode);
void axi_print_debug_info(axi_config_enum_uint32 config);
void axi_print_int_cnt(void);
void axi_print_ring_buf_info(void);
s32 amon_addr_is_enable(void);
s32 axi_get_irq_and_iomap(void);
/* �ɼ����ýӿ� */
AXI_DATA_CONFIG_CNF_STRU * bsp_axi_capt_config(u8 * data, u32 * out_len);
/* �ɼ�����ؼĴ������ýӿ� */
s32 bsp_axi_reg_config(u8 * data);
/* �ɼ���������ӿ� */
s32 bsp_axi_capt_ctrl(u8 * data);
/* ������ýӿ� */
AXI_MON_CONFIG_CNF_STRU * bsp_axi_mon_config(u8 * data, u32 * out_len);
/* ��������ӿ� */
s32 bsp_axi_mon_start(u8 * data);
/* �����ֹ�ӿ� */
AXI_MON_TERMINATE_CNF_STRU * bsp_axi_mon_terminate(u8 * data, u32 * out_len);
void axi_capt_test_config(u32 port, u32 mask, u32 value);
s32 amon_soft_enable(void);
void SRE_SetMonitor(void);

#else
static inline s32 bsp_axi_mon_start(u8 * data){return 0;}
static inline AXI_MON_TERMINATE_CNF_STRU * bsp_axi_mon_terminate(u8 * data, u32 * out_len){return NULL;}
static inline AXI_MON_CONFIG_CNF_STRU * bsp_axi_mon_config(u8 * data, u32 * out_len){return NULL;}
static inline AXI_DATA_CONFIG_CNF_STRU * bsp_axi_capt_config(u8 * data, u32 * out_len){return NULL;}
#endif
#ifdef __cplusplus
}
#endif

#endif /* _AMON_BALONG_H_ */
