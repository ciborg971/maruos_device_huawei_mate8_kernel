/************************************************************************
 *                                                                      *
 *                             VOS_MEM.H                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/03/1                                       *
 *  Author:             Zhu Yingming                                    *
 *  Modify Date:                                                        *
 *  Document:  ��VRP3.0-VOS�ڴ������ϸ���˵���顷                     *
 *             ��VRP3.0-VOS�ڴ�����Ҫ���˵���顷                     *
 *  Function: VOS memory managment.                                     *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *             Copyright 2000 - 2002 HuaWei Tech, Inc.                  *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 ************************************************************************/


#ifndef _VOS_MEM_H_
#define _VOS_MEM_H_

#ifdef TCPIP_DOPRA_V2    /*���û���Ҫʹ��Doprav2,��VISP��Dopra�汾����ǿ������ϵ,��Ҫ����Dopraͷ�ļ�*/
#include "v_memory.h"
#else /* �;ɰ汾����һ�� */
#include "vrp_mem.h"   
#endif


#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif

#ifdef  __cplusplus
extern "C" {
#endif



#ifndef HIWORD
#define HIWORD(x)                      (x>>16)
#endif

#ifndef LOWORD
#define LOWORD(x)                      (x&0x0000FFFF)
#endif



/* added by guoxiaojun for the "guodiao" version of VRP3.0 */
#if ((VRP_PRODUCT_8040 == VRP_YES)  &&  (VRP_OS_VXWORKS == VRP_YES))
typedef struct tagMibMemInfo{
  ULONG ulBufSize;           /* 8040��buffer�Ĵ�С     */
  ULONG ulTotalCounts;       /* �������ڴ���ܹ�����   */
  ULONG ulInUseCounts;       /* ����ʹ�õ��ڴ����     */
  ULONG ulFreeCounts;        /* Ŀǰ���е��ڴ����     */
  ULONG ulDropCounts;        /* ����ʧ�ܵ��ڴ����     */
  ULONG ulFreeError2;        /* �߽�δ�����ͷŴ���     */
  ULONG ulFreeError3;        /* �ڴ��ظ��ͷŴ���       */
  ULONG ulCollectCounts;     /* �ڴ��ռ�����           */
}VOS_MIBMEMINFO_S;

VOID VOS_Mem_GetMIBInfo(VOS_MIBMEMINFO_S stMibMemInfo[]);
#endif
/* end of add by guoxiaojun */
extern VOID *TCPIP_Malloc(ULONG ulInfo, ULONG ulSize);
extern ULONG TCPIP_Free(VOID* pBuf);
#ifdef  __cplusplus
}
#endif

#endif
