/*
 * audio soc rdr.
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __RDR_HISI_SOC_H__
#define __RDR_HISI_SOC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifndef RESET_CBFUNC_PRIO_LEVEL_LOWT
#define RESET_CBFUNC_PRIO_LEVEL_LOWT    (0)
#endif

#ifndef RESET_CBFUNC_PRIO_LEVEL_HIGH
#define RESET_CBFUNC_PRIO_LEVEL_HIGH    (49)
#endif

#define RESET_CBFUN_IGNORE_NAME         "NONAME"
#define BSP_RESET_OK                    0
#define BSP_RESET_ERROR                 (-1)
#define DRV_MODULE_NAME_LEN             9  /* exclude '\0' */
#define HIFI_SEC_DDR_MAX_NUM            (32)

struct drv_hifi_sec_info {
	unsigned int	type;
	unsigned int	src_addr;
	unsigned int	des_addr;
	unsigned int	size;
};

struct drv_hifi_sec_ddr_head {
	unsigned int sections_num;
	struct drv_hifi_sec_info sections[HIFI_SEC_DDR_MAX_NUM];
};

/*** for icc begin***/
#define ICC_CHN_ID_MAX 16
#define ICC_STAT_MSG_NUM   1000

#define ICC_DEBUG_PROTECT_WORD1 0xCDCDDCDC
#define ICC_DEBUG_PROTECT_WORD2 0xEFEFFEFE


struct icc_channel_fifo
{
	unsigned int magic;     /* fifoħ������ʶͨ��fifo��״̬ */
	unsigned int size;      /* fifo��С */
	unsigned int write;     /* fifo��ָ�� */
	unsigned int read;      /* fifoдָ�� */
	unsigned char data[4];  /* fifo��context */
};

struct icc_channel
{
	unsigned int              id;               /* ͨ��id */
	unsigned char             name[4];          /* ͨ������ */
	unsigned int              send_seq_num;     /* ��һ���������ݰ������к� */
	unsigned int              recv_seq_num;     /* ��һ���������ݰ������к� */
	unsigned int              ready_recv;       /* ����FIFO��״̬: ��ʶ��ǰFIFO�Ƿ���� */
	unsigned int              ipc_send_irq_id;  /* ͨ��˽�еķ�������ʹ�õ�ipc�ж� */
	unsigned int              ipc_recv_irq_id;  /* ͨ��˽�еĽ�������ʹ�õ�ipc�ж� */
	unsigned int              func_size;        /* ��������(��ͨ��)��С */
	unsigned int              fifo_recv;        /* ����fifo��ָ�� */
	unsigned int              fifo_send;        /* ����fifo��ָ�� */
};


struct icc_control
{
	unsigned int			  cpu_id;                      /* ��ǰ��cpu id */
	unsigned int			  channel_num;                 /* ͨ����Ŀ */
	unsigned char			  channels[ICC_CHN_ID_MAX*4];  /* icc_channel�Ľṹ��ָ������ */
};


struct icc_uni_msg_info
{
	unsigned short uhwChannelId;
	unsigned short uhwPacketlen;
	unsigned short uhwMsgId;
	unsigned short uhwDrop;
	unsigned short uhwFifoReadPos;
	unsigned short uhwFifoWritePos;
	unsigned int uwTime;
	unsigned int uwSenderPid;
	unsigned int uwReceiverPid;
};

struct icc_msg_fifo
{
	unsigned int front;
	unsigned int rear;
	unsigned int size;
	struct icc_uni_msg_info msg[ICC_STAT_MSG_NUM];
};

struct icc_msg_info
{
	struct icc_msg_fifo send;
	struct icc_msg_fifo recv;
};

struct icc_dbg
{
	unsigned int protectword1;
	unsigned int totalLength;
	unsigned int heap_base_offset;
	struct icc_control pstIccCtrl;
	struct icc_channel pstIccChannels[2];
	unsigned int state;
	unsigned int ipc_int_cnt;
	struct icc_msg_info msg_stat;
	unsigned int protectword2;
};
/*** for icc end***/

/*����������Modem/HIFI��λǰ���Ǹ�λ����ûص�����*/
typedef enum
{
	DRV_RESET_CALLCBFUN_RESET_BEFORE,   /*Modem/HIFI ��λǰ*/
	DRV_RESET_CALLCBFUN_RESET_AFTER,    /*Modem/HIFI ��λ��*/
	DRV_RESET_CALLCBFUN_RESETING,       /*Modem/HIFI ��λ��*/
	DRV_RESET_CALLCBFUN_MOEMENT_INVALID
} DRV_RESET_CALLCBFUN_MOMENT;

/*Record information of callback functions*/
typedef int (*pdrv_reset_cbfun)(DRV_RESET_CALLCBFUN_MOMENT eparam, int userdata);
typedef struct
{
    char name[DRV_MODULE_NAME_LEN + 1];
    int priolevel;
    pdrv_reset_cbfun cbfun;
    int userdata;
} sreset_mgr_callbackfunc;

/*Link list unit of managing all callback functions*/
typedef struct _sreset_mgr_LLI
{
    sreset_mgr_callbackfunc cbfuninfo;
    struct _sreset_mgr_LLI *pnext;
} sreset_mgr_LLI;


int  rdr_audio_soc_init(void);
void rdr_audio_soc_exit(void);

void rdr_audio_soc_dump(u32 modid, char* pathname, pfn_cb_dump_done pfb);
void rdr_audio_soc_reset( u32 modid, u32 etype, u64 coreid);

/*HIFI��λǰ��Ļص�ע�ắ��*/
int hifireset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
int hifireset_runcbfun (DRV_RESET_CALLCBFUN_MOMENT eparam);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

