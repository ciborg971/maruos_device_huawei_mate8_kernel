/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipoa_err.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2008-07-30
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-07-30   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _IPOA_ERR_H_
#define _IPOA_ERR_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


typedef enum tagATM_ERR_CODE
{
    ATM_OK = 0,                 /* = VOS_OK  */
    ATM_ERR,                    /* = VOS_ERR */
    ATM_ERR_MEM_ALLOC_FAIL,     /* �ڴ����ʧ�� */
    ATM_ERR_MBUF_ALLOC_FAIL,    /* MBUF�ڴ����ʧ�� */
    ATM_ERR_BAD_PARAM,          /*  */
    ATM_ERR_SERVICE_UNSUPPORT = 5,
    ATM_ERR_OAM_UNSUPPORT,
    ATM_ERR_MAP_NOT_FOUND,      /*  */
    ATM_ERR_NO_INARP_MAP,       /* PVCû��InARP MAP */
    ATM_ERR_CREATE_TIMER_FAIL,  /* PVCû��InARP MAP */
    ATM_ERR_CREATE_VA_FAIL,     /* ����VAʧ�� */
    ATM_ERR_CANNOT_GET_INTF,
    ATM_ERR_PHY_CREATE_PVC_FAIL,        /* �ײ�оƬ����PVCʧ�� */
    ATM_ERR_BAD_PACKET_TYPE,
    ATM_ERR_OAM_NOT_ENABLED,
    ATM_ERR_BAD_COMMAND,
    ATM_ERR_RPC_SYNC_SEND_FAIL,  /* RPCͬ��ȡʧ�� */
    ATM_ERR_CREATE_INTF_FAIL,
    ATM_ERR_MBUF_DATA_NULL,             /* MBUF�������� */
    ATM_ERR_PACKET_LEN_ERR,             /* ���ĳ��ȴ� */
    ATM_ERR_INARP_INTERVAL_ZERO,        /* INARP��ʱ����Ϊ0 */
    ATM_ERR_INARP_PAC_BAD_FIELD,        /* �Ƿ���IANRP���ģ��ֶδ� */
    ATM_ERR_INARP_PAC_NO_SOURCE_IP,     /* �Ƿ���IANRP���ģ�û��ԴIP */
    ATM_ERR_MBUF_PREPEND_FAIL,          /* ��չMBUF�� */
    ATM_ERR_MBUF_MAKECONT_FAIL,         /* MBUF�������� */
    ATM_ERR_INARP_PAC_SEND_FAIL,

    ATM_ERR_LOW_LAYER_SEND_FAIL,        /* �Ƿ���INARP�� */
    
    ATM_ERR_VC_SEARCH_NAME_ERR,             /* VC���ҷ���ֵ */
    ATM_ERR_VC_SEARCH_VPIVCI_ERR,
    ATM_ERR_VC_SEARCH_NAME_OK_VPIVCI_ERR,
    ATM_ERR_VC_SEARCH_NAME_ERR_VPIVCI_OK,
    ATM_ERR_VC_SEARCH_NAME_ERR_VPIVCI_ERR,
    ATM_ERR_VC_SEARCH_NAME_OK_VPIVCI_OK,

    ATM_ERR_PVC_NO_PROTOCOL,
	ATM_ERR_PAC_TYPE_UNSUPPORTED,
	ATM_ERR_INARP_NOT_SNAP,         /* ��SNAP��װ����INARP���� */
    ATM_ERR_VLINK_ALREADY_EXIST,
    ATM_ERR_INVALID_MAP_TYPE,
    ATM_ERR_VLINK_NOT_EXIST,
    ATM_ERR_EXCEED_VC_MAX_NUM_OF_CB,        /* sunshengtao 2001/04/12 */
    ATM_ERR_EXCEED_VC_MAX_NUM_OF_SUBIF,     /* sunshengtao 2001/04/12 */
	ATM_ERR_EXCEED_MAX_MAP_LIMIT_OF_PVC,    /* sunshengtao 2001/04/12 */
	ATM_ERR_EXCEED_MAX_MAP_LIMIT_OF_SUBIF,  /* sunshengtao 2001/04/12 */

    /* Add API of debug configration for SGSN by w60007312,2006-05-24*/
    ATM_ERR_SGSN_DEBUG_DEBUGSET,           /* ���ÿ��طǷ� */
    ATM_ERR_SGSN_DEBUG_DEBUGTYPE,          /* debug���ͷǷ� */
    ATM_ERR_SGSN_DEBUG_NULL_BUFFER,        /* ����洢��Ϣָ��Ƿ�*/
    ATM_ERR_SGSN_DEBUG_MAX_BUFFER_LEN,     /* ����洢��Ϣ����ȷǷ� */
    ATM_ERR_SGSN_DEBUG_IFNET_NOT_EXIST,    /* ifnetָ�벻���� */
    ATM_ERR_SGSN_DEBUG_INTF_NOT_EXIST,     /* ATM ���ӿ�ָ�벻����*/
    ATM_ERR_SGSN_DEBUG_INTF_IS_NOT_ATM,    /* �˽ӿڲ���ATM�� */
    ATM_ERR_SGSN_DEBUG_BUFFER_NOT_ENOUGH,  /* ��Ϣ���������������Ȳ���*/
    ATM_ERR_SGSN_DEBUG_PVC_INVALIDE,       /* PVC������VPI/VCI�Ƿ� */
    ATM_ERR_SGSN_DEBUG_NO_PVC,             /* û����������ƥ���PVC */
    ATM_ERR_SGSN_DEBUG_PVCNAME_VPIVCI,     /* ͬʱ����pvc����vpi/vci*/
    ATM_ERR_SGSN_DEBUG_CANT_OFF_PVC,       /* �ӿڼ������Ѿ���,������ر�pvc������ */
    ATM_ERR_SGSN_DEBUG_CANT_OFF_INTER,     /* ȫ�ֿ����Ѿ���,������ر��ýӿڼ����� */

	ATM_ERR_EXCEED_MAX_MAP_LIMIT_OF_PORT,   /* suishaoshuai 2001/06/16 */
	
    ATM_ERR_ONE_PVC_ONLY_ON_P2P,
    ATM_ERR_PVC_STATE_DOWN,     /* PVC���ͱ���ʧ�� */
    ATM_ERR_VC_SEND_FAIL,       	/* PVC���ͱ���ʧ�� */
    ATM_ERR_INTF_SEND_FAIL,     	/* INTF���ͱ���ʧ�� */
    ATM_ERR_NO_LOCAL_IPADDR,    	/* ����û�е�ַ */
    ATM_ERR_IN_PKT_PVC_NOT_EXIST,	/* PVC���յ����ģ���PVC������ */
    ATM_ERR_IN_PKT_PVC_DOWN,		/* PVC���յ����ģ���PVC״̬DOWN */
    ATM_ERR_OUT_PKT_NO_MAP,			/* �ӿ��Ϸ��ͱ��ģ�û��ָ��VLINK����MAP������ */
    ATM_ERR_OUT_PKT_VLINK_NO_MAP,	/* �ӿ��Ϸ��ͱ��ģ���ͨ��VLINK�Ҳ���MAP */
    
    ATM_ERR_OAMSTATE_PVC_NOT_FOUND, /* �ײ����OAM PVC��PVC������ */
    ATM_ERR_EXCEED_VC_MAX_NUM_OF_GROUP,
    
    ATM_ERR_PARA_NOT_EXIST,  /* ���������� */
    ATM_ERR_LAST_ONE_NO_COMMA,
    /*added by fanying 2001/08/31 D11963*/
    /*#if( VRP_MODULE_ATM_CELL_TRANSPORT == VRP_YES )*/
    ATM_ERR_L2VPN_LEN_ERR,
    ATM_ERR_L2VPN_IN_PVP_NOT_EXIST,
    ATM_ERR_L2VPN_OUT_PVP_NOT_EXIST,
    ATM_ERR_L2VPN_PVC_NOT_EXIST,
    ATM_ERR_L2VPN_L2VPN_NOT_START,
    ATM_ERR_L2VPN_NULL_PTR,
    ATM_ERR_L2VPN_QOS_TRANSMIT_FAIL,
    /*#endif*/
    ATM_ERR_NO_ENOUGH_BANDWIDTH,
    ATM_ERR_PHY_SET_SERVICE_FAIL,
    ATM_ERR_ILLOGICAL_SERVICE_PARAMETER,
    /*end add*/
    ATM_ERR_VPI_0_VCI_0,

    ATM_ERR_VCI_3_VCI_4,

    ATM_ERR_SERVICE_PARA_NOT_REASONABLE

}ATM_ERR_CODE_EN;





#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IPOA_ERR_H_ */


