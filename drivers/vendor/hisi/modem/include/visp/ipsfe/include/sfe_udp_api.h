
#ifndef _SFE_UDP_API_H_
#define _SFE_UDP_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/*ERRORCODE<数据面UDP模块错误码>*/
typedef enum enumSfeUdpErrCode
{
    SFE_UDP_OK = SFE_OK,                             /* 操作成功 */
    SFE_UDP_ERR_BEGIN = SFE_UDP_BEGIN_RET_CODE,      /* 模块错误码起始值,建议内部不要使用该值 */

    SFE_UDP_MALLOC_SOCKTRANS_VCPU_FAIL,              /* 1  获取VCPU数组失败 */
    SFE_UDP_MALLOC_SOCKTRANS_VRF_FAIL,               /* 2  获取VRF数组失败 */
    SFE_UDP_MALLOC_SOCKTRANS_HASH_FIRESTLEVEL_FAIL,  /* 3  获取一级HASH数组失败 */
    SFE_UDP_MALLOC_SOCKTRANS_HASH_SECONDLEVEL_FAIL,  /* 4  获取二级HASHA数组失败 */
    SFE_UDP_ADD_NAMEDB_SOCKTRANS_VCPU_FAIL,          /* 5  添加VCPU到共享名字库失败 */
    SFE_UDP_LEN_NOTCONSISTENT_IPDATALEN,             /* 6  UDP长度小于IP数据长度 */
    SFE_UDP_CHECKSUM_FAIL,                           /* 7  UDP校验和检查时出错 */
    SFE_UDP_REORDEROUT_MBUFBACKWARD_FAIL,            /* 8  UDP重排输出时MBUF指针恢复失败 */

    SFE_UDP_REORDER_SEND_NULL_POINTER,               /* 9  UDP重排输出时MBUF指针为空 */
    SFE_UDP_REORDER_SEND_DATALEN_INVALID,            /* 10 UDP重排输出时MBUF长度无效 */
    SFE_UDP_REORDER_SEND_VCPUID_INVALID,             /* 11 UDP重排输出时获取的VCPUID非法 */
    SFE_UDP_REORDER_SEND_SOCKTYPE_INVALID,           /* 12 UDP重排输出时socket类型非法 */

    SFE_UDP_MBUFFORWARD_FAIL,                        /* 13 UDP偏移掉UDPIP头时出错  */
    SFE_UDP_DROP_TAIL_DATA_FAILED,                   /* 14 IP数据长度小于mbuf总长度 */
    SFE_UDP_REORDER_SEND_MODULE_NOT_INIT,            /* 15 调用UDP重排主动发送报文接口时系统未初始化 */
    SFE_UDP_GET_CHSUM_FLAG_PRECFG_FAIL,              /* 16 获取UDP校验和的预配置失败*/
    SFE_UDP_PREPROCESS_MBUF_CONTINUOUS_FAIL,         /* 17 UDP首部处理时,多个DB内存连续失败*/
    SFE_UDP_INPUT_SOCK_RCV_NOT_MATCH_POLICY_PKT,     /* 18 UDP收到报文和socket中记录的策略不匹配 */
    SFE_UDP_REORDEROUT_MBUFNOTCPHDR_FAIL,            /* 19 UDP重排发送,发现mbuf不是重排接收到的(接收设置的三四层头为空) */
    SFE_UDP_MALLOC_SOCKTRANS_HASH_EXACT_FAIL,        /* 20 获取HASH数组失败，用本端端口、本端IP、远端端口、远端IP、VRF来计算索引 */
    SFE_UDP_MALLOC_SOCKTRANS_HASH_LPORT_FAIL,        /* 21 获取HASH数组失败，用本端端口来计算索引 */

}SFE_UDP_ERR_CODE_E;


UINT32 SFE_UDP_ReorderActiveSendPkt(INT32 i32Fd, SFE_MBUF_S *pstMBuf);


#ifdef  __cplusplus
}
#endif

#endif

