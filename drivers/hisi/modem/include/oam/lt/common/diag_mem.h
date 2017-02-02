

#ifndef __DIAG_MEM_H__
#define __DIAG_MEM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#ifdef CHIP_BB_HI6210
#include  "socp_lfix_chan.h"
#endif


#pragma pack(4)

/*****************************************************************************
  2 Macro
*****************************************************************************/


/********************* BBP DS内存配置 **************************
* BBP LOG 0:  64K
* BBP LOG 1:   8K
* BBP LOG 2:   8K
* BBP LOG 3:   8K
* BBP LOG 4:   8K
* BBP LOG 5:   8K
* BBP LOG 6:   8K
* BBP LOG 7:   8K
* BBP DS   :  随机
* TOTAL SIZE: BBPDS + 120K
****************************************************************/
/*BBP 数采要求内存必须为2K对齐的*/
#define BBP_DS_MEM_UNIT_SIZE                        (2*1024)


/* TODO: 先用数字偏移，后期调整 */
#define BBP_MEM_ADDR_BASE                         	(DDR_SOCP_ADDR + (1024*64) + (1024*640) + (1024*32) + (1024*160))

#define BBP_LOG0_MEM_ADDR                        	(BBP_MEM_ADDR_BASE)
#define BBP_LOG0_MEM_SIZE                        	(64*1024)

#define BBP_LOG1_MEM_ADDR                        	(BBP_LOG0_MEM_ADDR + BBP_LOG0_MEM_SIZE)
#define BBP_LOG1_MEM_SIZE                        	(8*1024)

#define BBP_LOG2_MEM_ADDR                        	(BBP_LOG1_MEM_ADDR + BBP_LOG1_MEM_SIZE)
#define BBP_LOG2_MEM_SIZE                        	(8*1024)

#define BBP_LOG3_MEM_ADDR                        	(BBP_LOG2_MEM_ADDR + BBP_LOG2_MEM_SIZE)
#define BBP_LOG3_MEM_SIZE                        	(8*1024)

#define BBP_LOG4_MEM_ADDR                        	(BBP_LOG3_MEM_ADDR + BBP_LOG3_MEM_SIZE)
#define BBP_LOG4_MEM_SIZE                        	(8*1024)

#define BBP_LOG5_MEM_ADDR                        	(BBP_LOG4_MEM_ADDR + BBP_LOG4_MEM_SIZE)
#define BBP_LOG5_MEM_SIZE                        	(8*1024)

#define BBP_LOG6_MEM_ADDR                        	(BBP_LOG5_MEM_ADDR + BBP_LOG5_MEM_SIZE)
#define BBP_LOG6_MEM_SIZE                        	(8*1024)

#define BBP_LOG7_MEM_ADDR                        	(BBP_LOG6_MEM_ADDR + BBP_LOG6_MEM_SIZE)
#define BBP_LOG7_MEM_SIZE                        	(8*1024)

#define BBP_DS_MEM_ADDR                         	(BBP_LOG7_MEM_ADDR + BBP_LOG7_MEM_SIZE)
#define BBP_DS_ORIGIAL_MEM_SIZE                     (DDR_SOCP_ADDR+DDR_SOCP_SIZE -BBP_DS_MEM_ADDR)
#define BBP_DS_MEM_SIZE                             (BBP_DS_ORIGIAL_MEM_SIZE - BBP_DS_ORIGIAL_MEM_SIZE%BBP_DS_MEM_UNIT_SIZE)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of diag_mem.h */
