/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : RabmEncap.h
  Description : ������װ
  History     :
      1.  ��־��      2003.12.04   �°�����
*******************************************************************************/

#ifndef _RABM_ENCAP_H_
#define _RABM_ENCAP_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
/*
#define RABM_Malloc(length)         WuepsMalloc(VOS_MEMPOOL_INDEX_NAS,length,WUEPS_MEM_WAIT)
#define RABM_Free(p)                WuepsFree(VOS_MEMPOOL_INDEX_NAS,p)
#define RABM_GmmFree(p)             WuepsFree(VOS_MEMPOOL_INDEX_NAS,p)
#define RABM_SmFree(p)              WuepsFree(VOS_MEMPOOL_INDEX_NAS,p)
#define RABM_RrcFree(p)             WuepsFree(VOS_MEMPOOL_INDEX_NAS,p)
#define RABM_RlcFree(p)             WuepsFree(VOS_MEMPOOL_INDEX_NAS,p)
*/
#define RABM_Malloc(length)         PS_RABM_MEM_ALLOC(length)
#define RABM_Free(p)                PS_RABM_MEM_FREE(p)
#define RABM_GmmFree(p)             PS_RABM_MEM_FREE(p)
#define RABM_SmFree(p)              PS_RABM_MEM_FREE(p)
#define RABM_RrcFree(p)             PS_RABM_MEM_FREE(p)
#define RABM_RlcFree(p)             PS_RABM_MEM_FREE(p)

/* deleted by xiaolinlin for RABM_PG 2005-1-10 begin */
/* #define RABM_MacFree(p)             WuepsFree(VOS_MEMPOOL_INDEX_NAS,p) */
/* deleted by xiaolinlin for RABM_PG 2005-1-10 end */

/*modify by luoxiaofeng 20060607 for A32D04205 begin*/
/*#define RABM_PdcpFree(p)            WuepsFree(VOS_MEMPOOL_INDEX_NAS,p)*/
#define RABM_PdcpFree(p)            PS_RABM_MEM_FREE(p)
/*modify by luoxiaofeng 20060607 for A32D04205 end*/

#define RABM_TafFree(p)             PS_RABM_MEM_FREE(p)
#define RABM_Memcpy(p1,p2,length)   PS_NAS_MEM_CPY(p1,p2,length)
#define RABM_Memset(p, value,length)  PS_NAS_MEM_SET(p, value,length)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
