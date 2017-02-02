/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_udp4.h
*
*  Project Code: VISPV100R006C02
*   Module Name: udp4 
*  Date Created: 2007-07-31
*        Author: zhanghuihui(55157)
*   Description: udp4ģ�����������ͷ�ļ�,���û�ʹ��udp4ģ�����ʹ��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-31   zhanghuihui(55157)      Create
*
*******************************************************************************/

#ifndef _TCPIP_UDP4_H_
#define _TCPIP_UDP4_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h" 

/* ��VRPVOS��ͷ�ļ����� */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/compbase.h"


/*UDP4ģ�����������������ͷ�ļ�*/
#include "tcpip/ip4/am4/include/am4_pub.h"


/*UDP4ģ����⿪�ŵĺꡢ���ݽṹ���塢����ӿڶ���*/
#include "tcpip/udp4/core/include/udp.h"
#include "tcpip/udp4/core/include/udp_cmd.h"
#include "tcpip/udp4/core/include/iudp.h"
#include "tcpip/udp4/include/udp_api.h"

#include "tcpip/public/tcpip_debug.h"

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _TCPIP_UDP4_H_ */

