/************************************************************************
 *                                                                      *
 *                             ccp_def.h                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        			                                    *
 *  Author:                         			                        *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP的CCP协议模块私有宏                          *
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

#ifdef		__cplusplus
extern		"C"{
#endif

#ifndef _CCP_DEF_H_
#define _CCP_DEF_H__
/********************************************************************/
#define CI_STAC_COMPRESS		17
#define CILEN_STAC_COMPRESS		5
#define PPP_STAC_SEQUENCE_NUMBER         0x03 /* Modified by liutao 38563 at 2005-07-04 PDSN9660V800R002C01B054 for BYHD06721 */
#define STAC_HISTORY_COUNT      1

/*Begin WGGSN_B03_L2TP_PPPC_COMP*/
#define STAC_HISTORY_COUNT0     0
#define CI_MPPC_COMPRESS        18
#define CILEN_MPPC_COMPRESS     6
#define PPP_MPPC_SUPPORTEDBITS  1
/*End WGGSN_B03_L2TP_PPPC_COMP*/

#define PPP_CCP_TIMEOUTTIME     20000  /* Added by heyajun kf1199 at 2004-08-05 V800R001C01B010 for BYHD03171 */

#define RESETREQ                 14
#define RESETACK                 15


/********************************************************************/
#endif /* #ifndef _CCP_DEF_H_*/

#ifdef		__cplusplus
}
#endif
