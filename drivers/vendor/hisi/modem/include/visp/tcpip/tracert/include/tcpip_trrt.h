

#ifndef _TCPIP_TRRT_H_
#define _TCPIP_TRRT_H_

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

/*trrtģ�����������������ͷ�ļ�*/
#include "tcpip/ip4/am4/include/tcpip_am4.h"
#include "tcpip/socket4/include/tcpip_socket4.h"    

/*trrtģ����⿪�ŵĺꡢ���ݽṹ���塢����ӿڶ���*/
#include "tracert/include/trrt_api.h"
#include "tracert/include/trrt_pub.h"
#include "tracert/include/itrrt_inc.h"
#include "tracert/include/trrt_ext.h"
#include "tracert/shell/include/trrt_sh_info.h"


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif  /* end of _TCPIP_TRRT_H_ */

