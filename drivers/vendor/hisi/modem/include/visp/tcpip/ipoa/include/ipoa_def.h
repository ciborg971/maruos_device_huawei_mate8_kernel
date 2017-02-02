
/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipoa_def.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2008-07-24
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-07-24   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _IPOA_DEF_H_
#define _IPOA_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
#include"tcpip/ipoa/include/ipoa_api.h"
#define     IPOA_UP         1           /* ��ʾ�ӿڡ�Э�顢VC��״̬UP */
#define     IPOA_DOWN       0           /* ��ʾ�ӿڡ�Э�顢VC��״̬DOWN */
#define     IPOA_PAC_IN     1           /* �յ����� */
#define     IPOA_PAC_OUT    2           /* ���ͱ��� */


#define IPOA_VC_VPI_MAX              255
#define IPOA_VC_VCI_MAX              2048
#define IPOA_DEFAULT_VPIVCI          0xFFFF    /* Ĭ��vpi��vciֵ */
#define IPOA_LEN_256                 256       /* 256�ֽ�,�������������ڴ�*/
#define IPOA_PVC_FLAG                1         /* PVC�����Կ��� */
#define IPOA_NO_PVC_FLAG             0         /* �ӿڼ����Կ��� */
#define IPOA_BUFFER_MIN_LEN          1024      /* API��������ڴ���С����*/

#define IPOA_HASH_SEED               1379
#define IPOA_MAX_QUE_LEN             150
#define IPOA_QUE_MAX_DEAL_NUMBER         200     /* һ�δ���������� */

#define IPOA_MAX_PVC_NUM_ON_SUBIF    256
#define IPOA_MAX_PVC_NUM_PER_PORT    2048

#define IPOA_MAX_MAP_NUM_ON_PVC      32     /* ����PVC���������õ�MAP�������� */
#define IPOA_MAX_MAP_NUM_ON_SUBIF    1024    /* �����ӽӿ����������õ�MAP��Ŀ���� */
#define IPOA_MAX_MAP_NUM_ON_PORT     2048

#define  IPOA_DEFAULT_INARP_INTERVAL    1      /* ���� */


#define IPOA_INARP_CMD_START             0x01    
#define IPOA_INARP_CMD_STOP              0x02    
#define IPOA_INARP_CMD_INTERVAL_CHANGE   0x04    

#define IPOA_INARP_INITIAL               0x00
#define IPOA_INARP_REQUEST_SENT          0x01
#define IPOA_INARP_REPLY_RECEIVED        0x02
#define IPOA_INARP_REQUEST_REVEIVED      0x04
#define IPOA_INARP_REPLY_SENT            0x08
#define IPOA_INARP_START                 0x10

#define IPOA_INARP_TYPE_REQUEST           0x08    /* INARP OP CODE���������Ͷ��� */
#define IPOA_INARP_TYPE_REPLY             0x09    /* INARP OP CODE���������Ͷ��� */





#define IPOA_INARP_SEND_PAC_MAX_LEN          20     /* ��Ŀ���ַʱ20�ֽ� */
#define IPOA_INARP_SEND_PAC_LEN_WITH_DST_IP  20     /* ��Ŀ���ַʱ20�ֽ� */
#define IPOA_INARP_SEND_PAC_LEN_NO_DST_IP    16     /* ����Ŀ���ַʱ16�ֽ� */

#define IPOA_PKT_RESERVED_HEAD_LEN           48
#define IPOA_PKT_RESERVED_TAIL_LEN           48


#define IPOA_MAX_PACKET_HEADER_LEN       10      /* ��ı���ͷ��10���ֽڣ����Ա�֤���������� */


#define IPOA_DROP_PAKET_OF_CB        1
#define IPOA_DROP_PAKET_OF_INTF      2
#define IPOA_DROP_PAKET_OF_PVC       3

/*******************************************************************************
IPOA����Drop�����ֶ���
*******************************************************************************/
#define IPOA_QUE_DROP_PAC_OF_PVC         1
#define IPOA_QUE_DROP_PAC_OF_INTF        2
#define IPOA_QUE_DROP_PAC_OF_CB          3


#define IPOA_INARP_HARD_TYPE                 0x0013
#define IPOA_INARP_IP_PROT_TYPE              0x0800



#define IPOA_CFG_SETDBGFLAG(ulTargetFlag, ulFlagToSet, bSetFlag) ((ulTargetFlag) = (bSetFlag)?((ulTargetFlag) | (ulFlagToSet)):((ulTargetFlag) & ~(ulFlagToSet)))

#define IPOA_INTF_STATE(pstIpoaIntf) (((pstIpoaIntf->ucPhyState == IPOA_UP) \
                                        && (pstIpoaIntf->bShutdown == BOOL_FALSE)) \
                                        ? IPOA_UP : IPOA_DOWN \
                                      )


#define IPOA_PVC_STATE(pstPVC) (((pstPVC->ucPhyState == IPOA_UP) \
                                  && (pstPVC->bShutdown == BOOL_FALSE)) \
                                  ? IPOA_UP : IPOA_DOWN \
                                )


#define IPOA_DBG_PKT_HEAD_SNAPSHOT_LEN    64

typedef struct tagIPOA_DBG_PKT_INFO
{
    UCHAR           ucInOut;        /* �������ջ��Ƿ� */
    UCHAR           ucPacType;      /* �������� */
    UCHAR           ucEncType;      /* ���ķ�װ���� */
    UCHAR           ucInARPType;    /* INARP���ͣ�����ATM_INARP_TYPE_REQUEST, Ӧ��ATM_INARP_TYPE_REPLY */
    USHORT          usLen;          /* ���ĳ��� */
    USHORT          usHeaderLen;    /* ����ͷ���� */
    ULONG           ulSrcIP;   /* INARP����Դ��ַ */
    ULONG           ulDstIP;   /* INARP����Ŀ�ĵ�ַ */
    ULONG           ulErrCode;      /* ���Ĵ����� */
    UCHAR           ucHeader_a[IPOA_DBG_PKT_HEAD_SNAPSHOT_LEN];      /* ����ͷ�ֽ����� */
}IPOA_DBG_PKT_INFO_S;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IPOA_DEF_H_ */


