
#ifndef _SFE_UDP_API_H_
#define _SFE_UDP_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/*ERRORCODE<������UDPģ�������>*/
typedef enum enumSfeUdpErrCode
{
    SFE_UDP_OK = SFE_OK,                             /* �����ɹ� */
    SFE_UDP_ERR_BEGIN = SFE_UDP_BEGIN_RET_CODE,      /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */

    SFE_UDP_MALLOC_SOCKTRANS_VCPU_FAIL,              /* 1  ��ȡVCPU����ʧ�� */
    SFE_UDP_MALLOC_SOCKTRANS_VRF_FAIL,               /* 2  ��ȡVRF����ʧ�� */
    SFE_UDP_MALLOC_SOCKTRANS_HASH_FIRESTLEVEL_FAIL,  /* 3  ��ȡһ��HASH����ʧ�� */
    SFE_UDP_MALLOC_SOCKTRANS_HASH_SECONDLEVEL_FAIL,  /* 4  ��ȡ����HASHA����ʧ�� */
    SFE_UDP_ADD_NAMEDB_SOCKTRANS_VCPU_FAIL,          /* 5  ���VCPU���������ֿ�ʧ�� */
    SFE_UDP_LEN_NOTCONSISTENT_IPDATALEN,             /* 6  UDP����С��IP���ݳ��� */
    SFE_UDP_CHECKSUM_FAIL,                           /* 7  UDPУ��ͼ��ʱ���� */
    SFE_UDP_REORDEROUT_MBUFBACKWARD_FAIL,            /* 8  UDP�������ʱMBUFָ��ָ�ʧ�� */

    SFE_UDP_REORDER_SEND_NULL_POINTER,               /* 9  UDP�������ʱMBUFָ��Ϊ�� */
    SFE_UDP_REORDER_SEND_DATALEN_INVALID,            /* 10 UDP�������ʱMBUF������Ч */
    SFE_UDP_REORDER_SEND_VCPUID_INVALID,             /* 11 UDP�������ʱ��ȡ��VCPUID�Ƿ� */
    SFE_UDP_REORDER_SEND_SOCKTYPE_INVALID,           /* 12 UDP�������ʱsocket���ͷǷ� */

    SFE_UDP_MBUFFORWARD_FAIL,                        /* 13 UDPƫ�Ƶ�UDPIPͷʱ����  */
    SFE_UDP_DROP_TAIL_DATA_FAILED,                   /* 14 IP���ݳ���С��mbuf�ܳ��� */
    SFE_UDP_REORDER_SEND_MODULE_NOT_INIT,            /* 15 ����UDP�����������ͱ��Ľӿ�ʱϵͳδ��ʼ�� */
    SFE_UDP_GET_CHSUM_FLAG_PRECFG_FAIL,              /* 16 ��ȡUDPУ��͵�Ԥ����ʧ��*/
    SFE_UDP_PREPROCESS_MBUF_CONTINUOUS_FAIL,         /* 17 UDP�ײ�����ʱ,���DB�ڴ�����ʧ��*/
    SFE_UDP_INPUT_SOCK_RCV_NOT_MATCH_POLICY_PKT,     /* 18 UDP�յ����ĺ�socket�м�¼�Ĳ��Բ�ƥ�� */
    SFE_UDP_REORDEROUT_MBUFNOTCPHDR_FAIL,            /* 19 UDP���ŷ���,����mbuf�������Ž��յ���(�������õ����Ĳ�ͷΪ��) */
    SFE_UDP_MALLOC_SOCKTRANS_HASH_EXACT_FAIL,        /* 20 ��ȡHASH����ʧ�ܣ��ñ��˶˿ڡ�����IP��Զ�˶˿ڡ�Զ��IP��VRF���������� */
    SFE_UDP_MALLOC_SOCKTRANS_HASH_LPORT_FAIL,        /* 21 ��ȡHASH����ʧ�ܣ��ñ��˶˿����������� */

}SFE_UDP_ERR_CODE_E;


UINT32 SFE_UDP_ReorderActiveSendPkt(INT32 i32Fd, SFE_MBUF_S *pstMBuf);


#ifdef  __cplusplus
}
#endif

#endif

