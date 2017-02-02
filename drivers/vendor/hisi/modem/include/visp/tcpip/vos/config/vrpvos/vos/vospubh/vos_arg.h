/************************************************************************
 *                                                                      *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/03/25                                      *
 *  Author:                                                             *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *                                                                      *
 ************************************************************************/
#ifndef _VOS_ARG_H_
#define _VOS_ARG_H_

#ifndef _VRPCFG_H_
#error "Please include vrpcfg.h before this file."
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#if (VRP_OS_WINDOWS == VRP_YES)
#include "vos/ansilib/win32/stdarg.h" /*All os should have this ANSI Head file.*/
#elif (VRP_OS_PSOS == VRP_YES)
#if ( VRP_CPU_mPPC == VRP_YES )
#include "vos/ansilib/psos/ppc/stdarg.h"
#else
#include "vos/ansilib/psos/stdarg.h"
#endif
#elif (VRP_OS_VXWORKS == VRP_YES)
/* edit by L00105073 for BC3D01411: ��TornadoĿ¼�а���������CPU��Ӧ��ͷ�ļ� */
#include "vos/ansilib/vxworks/stdarg.h"
#else
/*Linuxֱ�����ϵͳ��ͷ�ļ�*/
#include <stdarg.h>
#endif


#ifdef  __cplusplus
}
#endif

#endif



