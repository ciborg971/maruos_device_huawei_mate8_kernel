/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_pp.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To include IPOS / VISP specific PPMNG Map file
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for including relevant PPMNG Map file
*                               based on IPOS or VISP compilation
************************************************************************/

#ifndef _IPBIR_PP_H_
#define _IPBIR_PP_H_



#if (VRP_YES == TCPIP_IN_VRP)
#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_pp_map.h"       /* for IPOS map*/
#else
#include "ipbircommon/ipbirmap/visp/ipbir_visp_pp_map.h"       /* for VISP map*/
#endif

#endif  /* end of _IPBIR_PP_H_ */

