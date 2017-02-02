
#ifndef __SYS_SOCP_H__
#define __SYS_SOCP_H__


#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <bsp_sram.h>
#include <bsp_socp.h>
#include <sys_bus_pressure.h>
#include <mdrv_socp_common.h>

struct socp_press_case_s{
    u32                             bDstSet;
    u32                             SrcCh;
    u32                             DstCh;
    u32		                        u32BypassEn;
    SOCP_DATA_TYPE_ENUM_UIN32       eDataType;
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32  eMode;
    SOCP_CHAN_PRIORITY_ENUM_UIN32   ePriority;
    u32                             u32Reseve1;
    u8*                             u32InputStart;
    u32                             u32InputSize;
    u32                             u32Reseve2;
    u8*                             u32RDStart;
    u32                             u32RDSize;
    u32                             u32Reseve3;
    u32                             u32RDThreshold;
    u32                             u32OutputStart;
    u32                             u32OutputSize;
    u32                             u32Threshold;
    socp_event_cb                   EventCb;
    socp_read_cb                    ReadCb;
    socp_rd_cb                      RdCb;
    u32                             TaskId;
    u32                             u32DataLen;
    u32                             u32DataCnt;
    SOCP_DATA_TYPE_EN_ENUM_UIN32    eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32    eEncDebugEn;
    u32                             u32EncDstThrh;
};


void sys_socp_init(struct master* master);

void sys_socp_stop(struct master* master);
void sys_socp_start(struct master* master);


void sys_socp_report(struct master* master);

void sys_socp_record(struct master* master);



#endif /* __SYS_SOCP_H__ */


