

#ifndef __RFILE_BALONG_H__
#define __RFILE_BALONG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifdef __KERNEL__

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/personality.h>
#include <linux/stat.h>
#include <linux/unistd.h>
#include <linux/types.h>
#include <linux/dirent.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/fs.h>
#include <linux/statfs.h>
#include <linux/rcupdate.h>
#include <linux/hrtimer.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#endif /* end of __KERNEL__ */

#include "product_config.h"
#include "osl_types.h"
#include "osl_sem.h"
#include "osl_list.h"
#include "osl_thread.h"
#include "osl_malloc.h"
#include "drv_comm.h"
#include "mdrv_memory.h"
#include "mdrv_timer.h"
#include "bsp_om.h"
#include "bsp_icc.h"
#include "bsp_rfile.h"


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define RFILE_TIMEOUT_MAX           (2000)           /* ��ȴ�2s */
#define RFILE_WAIT_FOREVER          (-1)

#define RFILE_MAX_SEND_TIMES        (10)                /* ����ʧ��ʱ������Դ��� */

#define RFILE_CCORE_ICC_RD_CHAN     (ICC_CHN_RFILE<<16 | RFILE_RECV_FUNC_ID)
#define RFILE_CCORE_ICC_WR_CHAN     (ICC_CHN_RFILE<<16 | RFILE_RECV_FUNC_ID)

#define RFILE_ICC_PACKET_HEAD_LEN   ICC_CHANNEL_PAYLOAD

#define RFILE_LEN_MAX               (0x00001000 - RFILE_ICC_PACKET_HEAD_LEN)

/* RFILEģ��д����������ICC����󳤶� */
#define RFILE_WR_LEN_MAX            (0x00001000 - RFILE_ICC_PACKET_HEAD_LEN - sizeof(struct bsp_rfile_write_req))

/* RFILEģ�������������ICC����󳤶� */
#define RFILE_RD_LEN_MAX            (0x00001000 - RFILE_ICC_PACKET_HEAD_LEN - sizeof(struct bsp_rfile_read_cnf))


#define RFILE_MNTN_INFO_NUM         (20)            /* ��¼20����ά�ɲ���Ϣ */

#define RFILE_MNTN_DATA_LEN         (32)            /* ��ά�ɲ���Ϣ���ݵ���󳤶� */


typedef  osl_sem_id             rfile_sem_id;

#define Rfile_Malloc(size)      osl_malloc(size)
#define Rfile_Free(ptr)         osl_free(ptr)
#define RFILE_SLEEP(msecs)      osl_task_delay(msecs)
#define RFILE_TASK_STACK_SIZE   (0x1000)        /* TODO: */
#ifdef __KERNEL__



#ifdef BSP_CONFIG_HI3650
#define RFILE_PATH              ""         /* RFILE��A�˵����·�� */
#else
#define RFILE_PATH              ""                  /* RFILE��A�˵����·�� */
#endif


#endif /* end of __KERNEL__ */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* �������� */
enum _BSP_RFILE_OP_EN
{
    EN_RFILE_OP_OPEN = 0,
    EN_RFILE_OP_CLOSE,
    EN_RFILE_OP_WRITE,
    EN_RFILE_OP_WRITE_SYNC,
    EN_RFILE_OP_READ,
    EN_RFILE_OP_SEEK,
    EN_RFILE_OP_TELL,
    EN_RFILE_OP_REMOVE,
    EN_RFILE_OP_MKDIR,
    EN_RFILE_OP_RMDIR,
    EN_RFILE_OP_OPENDIR,
    EN_RFILE_OP_READDIR,
    EN_RFILE_OP_CLOSEDIR,
    EN_RFILE_OP_STAT,
    EN_RFILE_OP_ACCESS,
    EN_RFILE_OP_MASSRD,
    EN_RFILE_OP_MASSWR,
    EN_RFILE_OP_RENAME,
    EN_RFILE_OP_BUTT
};

/* ����״̬ */
enum bsp_rfile_state_en
{
    EN_RFILE_IDLE = 0,      /* ������ */
    EN_RFILE_DOING,         /* ���ڴ��� */
    EN_RFILE_DONE           /* ������� */
};

/* �������ͣ�����RFILE�ڲ���ά�ɲ� */
enum bsp_rfile_err_en
{
    EN_RFILE_ERR_SUCCESS = 0,       /* success */
    EN_RFILE_ERR_PARA_INVALID,      /* invalid parameter */
    EN_RFILE_ERR_MALLOC,            /* malloc failed */
    EN_RFILE_ERR_TIMEOUT,           /* timeout */
    EN_RFILE_ERR_LEN,               /* length error */
    EN_RFILE_ERR_ICC,               /* icc process failed */
    EN_RFILE_ERR_BUTT               /* other failure */
};

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/* ������Ϣ */
struct bsp_rfile_op_stru
{
    u32                     optype;         /* ��ǰ�Ĵ������ͣ���enum _BSP_RFILE_OP_EN */
    s32                     fd;             /* �ļ������� */
    s32                     retlen;         /* ������ */
    u32                     datalen;        /* ���ݻ��泤�ȣ�����read,readdir,massread */
    s8                      *ptr;           /* ���ݻ���ָ�룬����read,readdir,massread */
    long                    offset;         /* ƫ�ƣ�����lseek */
    s32                     whence;         /* ƫ������ */
    s32                     dirhandle;      /* Ŀ¼��� */
    struct rfile_stat_stru  ststat;         /* �ļ�����Ϣ */
};


/* ����Ԫ�� */
struct bsp_rfile_que_stru
{
    enum bsp_rfile_state_en     enState;
    rfile_sem_id                semReq;     /* ���������ź��� */
    struct bsp_rfile_op_stru    stData;     /* ����������Ϣ */
    struct list_head            stlist;     /* ����ڵ� */
    void                        *pData;     /* ��Ҫͨ���˼�ͨ�ŷ���A�˵����� */
    u32                         ulLen;
    s32                         ret;
};/*lint !e959*/


/* ������Ϣ */
struct bsp_rfile_main_stru
{
    BSP_BOOL                bInitFlag;
    s32                     errorno;
    u32                     taskid;
    rfile_sem_id            semTask;    /* �����ź��� */
    rfile_sem_id            semList;    /* �����ź��� */
    struct list_head        stlist;     /* ����ڵ� */
    u8                      data[RFILE_LEN_MAX];    /* ����ICCͨ����ȡ������ */
};/*lint !e959*/


/* ��ά�ɲ���Ϣ */
struct rfile_mntn_info_stru
{
    enum _BSP_RFILE_OP_EN   enType;
    enum bsp_rfile_err_en   enErr;
    s32                     param1;
    s32                     param2;
    s32                     param3;
    u32                     slice;
    u8                      pData[RFILE_MNTN_DATA_LEN];
};

struct bsp_rfile_mntn_stru
{
    s32                             position;
    struct rfile_mntn_info_stru     stMntnInfo[RFILE_MNTN_INFO_NUM];    /* ��¼ÿ�ֲ���������20����¼ */
};

struct rfile_mntn_type_stru
{
    u32                     ptr;
    enum _BSP_RFILE_OP_EN   enType[RFILE_MNTN_INFO_NUM];
    u32                     slice[RFILE_MNTN_INFO_NUM];
};

struct rfile_mntn_stru
{
    struct rfile_mntn_type_stru     sttype;
};


struct bsp_rfile_common_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     ret;
};

/* open====================================================================*/
struct bsp_rfile_open_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     mode;
    s32                     flags;
    s32                     nameLen;
    u8                      aucData[0];/*lint !e43*/
};

struct bsp_rfile_open_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     ret;    /* ���ļ���������������� */
};

/* seek====================================================================*/
struct bsp_rfile_seek_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     fd;
    s32                     offset;
    s32                     whence;
};

/* read ====================================================================*/
struct bsp_rfile_read_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     fd;
    u32                     ulSize;
};

struct bsp_rfile_read_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     Size;
    u8                      aucData[0];/*lint !e43*/
};

/* write ====================================================================*/
struct bsp_rfile_write_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     fd;
    u32                     ulSize;
    u8                      aucData[0];/*lint !e43*/
};

/* close ====================================================================*/
struct bsp_rfile_close_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    u32                     fd;
};

/* remove====================================================================*/
struct bsp_rfile_remove_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     pathLen;
    u8                      aucData[0];/*lint !e43*/
};

/* tell  ====================================================================*/
struct bsp_rfile_tell_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     fd;
};

/* mkdir ====================================================================*/
struct bsp_rfile_mkdir_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     pathLen;
    s32                     mode;
    u8                      aucData[0];/*lint !e43*/
};

/* rmdir ====================================================================*/
struct bsp_rfile_rmdir_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     pathLen;
    u8                      aucData[0];/*lint !e43*/
};

/* opendir =================================================================*/
struct bsp_rfile_opendir_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     nameLen;
    u8                      aucData[0];/*lint !e43*/
};

struct bsp_rfile_opendir_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     dirhandle;
};

/* readdir==================================================================*/
struct bsp_rfile_readdir_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     dir;
    u32                     count;
};

struct bsp_rfile_readdir_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     Size;
    u8                      aucData[0];/*lint !e43*/
};

/* closedir==================================================================*/
struct bsp_rfile_closedir_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     dir;
};

/* stat======================================================================*/
struct bsp_rfile_stat_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     ulSize;
    u8                      aucData[0];/*lint !e43*/
};

struct bsp_rfile_stat_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     ret;
    struct rfile_stat_stru  ststat;
};

/* access=====================================================================*/
struct bsp_rfile_access_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     mode;
    s32                     pathlen;
    u8                      aucData[0];/*lint !e43*/
};


/* mass read==================================================================*/
struct bsp_rfile_massread_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     offset;
    u32                     size;
    u32                     datalen;        /* the length of partition string(include \0) */
    u8                      aucData[0];     /*lint !e43*//* partition */
};


/* mass write=================================================================*/
struct bsp_rfile_masswrite_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     offset;
    u32                     size;
    u32                     partitionlen;   /* the length of partition string(include \0) */
    u32                     datalen;        /* the size of all data */
    u8                      aucData[0];     /*lint !e43*//* partition + write buffer */
};

/* rename======================================================================*/
struct bsp_rfile_rename_req
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    u32                     ulSize;
    u8                      aucData[0];/*lint !e43*/
};

struct bsp_rfile_rename_cnf
{
    u32                     opType;
    u32                     pstlist;    /*struct list_head        *pstlist;*/
    s32                     errorno;
    s32                     ret;
};


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/

s32 rfile_HandleReq(struct bsp_rfile_que_stru *pstRfileQue);

void rfile_OpenCnf(struct bsp_rfile_que_stru *pstRfileQue, struct bsp_rfile_open_cnf *pstCnf);
void rfile_CloseCnf(struct bsp_rfile_que_stru *pstRfileQue, struct bsp_rfile_common_cnf *pstCnf);
void rfile_ReadCnf(struct bsp_rfile_que_stru *pstRfileQue, struct bsp_rfile_read_cnf *pstCnf);
void rfile_OpendirCnf(struct bsp_rfile_que_stru *pstRfileQue, struct bsp_rfile_opendir_cnf *pstCnf);
void rfile_ReaddirCnf(struct bsp_rfile_que_stru *pstRfileQue, struct bsp_rfile_readdir_cnf *pstCnf);
void rfile_StatCnf(struct bsp_rfile_que_stru *pstRfileQue, struct bsp_rfile_stat_cnf *pstCnf);
void rfile_MntnRecord(struct rfile_mntn_info_stru *pstmntn);
void rfile_MntnTypeIn(enum _BSP_RFILE_OP_EN entype);

s32 rfile_readdir(u32 fd, void *dirent, u32 count);
s32 rfile_CnfProc(struct list_head *plistcnf, u32 enOptype, void *pData);
s32 bsp_RfileCallback(u32 channel_id, u32 len, void *context);
struct bsp_rfile_que_stru *rfile_GetQueNode(void);
s32 rfile_RcvIccData(void);
void rfile_SendIccData(void);
void rfile_TaskProc(void* obj);
s32 rfile_AddNode(struct bsp_rfile_que_stru *pstNode);
s32 rfile_DelNode(struct bsp_rfile_que_stru *pstNode);

#pragma pack(0)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* end of rfile_balong.h */

