/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              raw_ip_pub.h
*
*  Project Code: VISP1.5
*   Module Name: RawIP
*  Date Created: 2006-4-28
*        Author: luyao(60000758)
*   Description: ���ļ���rawip�����ݽṹ���� 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-4-28   luyao(60000758)  Creat the first version.
*  2006-04-27  luyao            ���ݱ�̹淶�����ļ����й淶������
*
*******************************************************************************/

#ifndef _RAW_IP_PUB_H_
#define _RAW_IP_PUB_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/rawip4/include/rawip_api.h"


typedef struct  tagRIP4_MOD_INFO
{
    ULONG ulModID; /* Module id */

    ULONG ulDoubleOSPFEnalbe;

} RIP4_MOD_INFO_S;

#define IP4_RIP_EXT_COMIF_CNT   8                   /*modified by a00900892 2014-08-13 */

#define RIPSNDQ     8192 /*Ĭ�ϵ�RawIP Socket���ͻ�������СΪ8K*/
#define RIPRCVQ     8192 /*Ĭ�ϵ�RawIP Socket���ջ�������СΪ8K*/


#ifdef __cplusplus
}
#endif

#endif  /* _RAW_IP_PUB_H_ */

