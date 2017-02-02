/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_dhcp4c.h
*
*  Project Code: VISPV100R006
*   Module Name: dhcp4c  
*  Date Created: 2007-06-14
*        Author: Jiangtao
*   Description: dhcp4cģ�����������ͷ�ļ�,���û�ʹ��dhcp4cģ�����ʹ��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-06-14   Jiangtao                Create
*
*******************************************************************************/

#ifndef _TCPIP_DHCP4C_H_
#define _TCPIP_DHCP4C_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_config.h"

/* ��VRPVOS��ͷ�ļ����� */
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/mbuf.h"
#include "vos/vospubh/vos_arg.h"
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/compbase.h"
#include "vos/vospubh/vos_task.h"

/*DHCP4Cģ�����������������ͷ�ļ�*/
#include "tcpip/ifnet/shell/include/if_ic.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ifnet/core/include/iifnet.h"


/*DHCP4Cģ����⿪�ŵĺꡢ���ݽṹ���塢����ӿڶ���*/
#include "tcpip/dhcp4c/include/dhcp4c_api.h"
#include "tcpip/dhcp4c/core/include/dhcp4c_def.h"
#include "tcpip/dhcp4c/core/include/dhcp4c_type.h"
#include "tcpip/dhcp4c/core/include/idhcp4c.h"
#include "tcpip/dhcp4c/include/idhcp4c_inc.h"
#include "tcpip/dhcp4c/shell/include/dhcp4c_sh_ic.h"
#include "tcpip/dhcp4c/core/include/dhcp4c_core.h"

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _TCPIP_DHCP4C_H_ */

