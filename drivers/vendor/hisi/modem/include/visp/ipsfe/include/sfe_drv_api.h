

#ifndef _SFE_DRV_API_H_
#define _SFE_DRV_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif
/*ERRORCODE<数据面Driver模块错误码>*/
typedef enum enumSfeDrvErrCode
{
    SFE_DRV_OK = SFE_OK,                                    /* 操作成功 */
    SFE_DRV_ERR_BEGIN = SFE_DRV_BEGIN_RET_CODE,             /* 模块错误码起始值,建议内部不要使用该值 */
    SFE_DRV_ZCOPY_INIT_GET_SFE_VCPU_MAX_NUM_PRECFG_FAIL,    /* 1  零拷贝驱动初始化时,获取VCPU个数预配置失败 */
    SFE_DRV_INIT_MALLOC_ZFD_FAIL,                           /* 2  零拷贝驱动初始化时,分配存放零拷贝设备描述符的共享内存失败 */
    SFE_DRV_ZCOPY_INIT_OPEN_DEV_FAIL,                       /* 3  零拷贝驱动初始化时,打开字符设备失败 */
    SFE_DRV_ZCOPY_INIT_OPEN_BUFDEV_FAIL,                    /* 4  零拷贝驱动初始化时,打开专门用于获取报文接收发送队列的文件句柄字符设备失败 */
    SFE_DRV_ZCOPY_INIT_MMAP_FAIL,                           /* 5  零拷贝驱动初始化时,MMAP Zcopy报文接收发送队列内存用户态地址失败 */
    SFE_DRV_ZCOPY_INIT_GET_ZCOPY_KNLSTART_ADDR_FAIL,        /* 6  零拷贝驱动初始化时,获取Zcopy报文接收发送队列内存内核态起始地址失败 */
    SFE_DRV_INIT_ADD_ZFD_FAIL,                              /* 7  零拷贝驱动初始化时,将零拷贝设备描述符的共享内存添加到共享名字库失败 */
    SFE_DRV_INIT_MALLOC_RCV_MEM_USER_ADDR_FAIL,             /* 8  零拷贝驱动初始化时,分配存放报文接收消息队列用户态地址的共享内存失败 */
    SFE_DRV_INIT_GET_RCV_BUF_KNL_ADDR_FAIL,                 /* 9  零拷贝驱动初始化时,获取报文接收消息队列内存的内核态地址失败 */
    SFE_DRV_INIT_ADD_RCV_BUF_USER_ADDR_FAIL,                /* 10 零拷贝驱动初始化时,将存放报文接收消息队列用户态地址的共享内存加入共享名字库失败 */
    SFE_DRV_INIT_MALLOC_SND_MEM_KNL_ADDR_FAIL,              /* 11 零拷贝驱动初始化时,分配存放报文发送消息队列内核态地址的共享内存失败 */
    SFE_DRV_INIT_GET_SND_BUF_KNL_ADDR_FAIL,                 /* 12 零拷贝驱动初始化时,获取报文发送消息队列内存的内核态地址失败 */
    SFE_DRV_INIT_ADD_SND_BUF_KNL_ADDR_FAIL,                 /* 13 零拷贝驱动初始化时,将存放报文发送消息队列内核态地址的共享内存加入共享名字库失败 */
    SFE_DRV_INIT_MALLOC_SND_MEM_USER_ADDR_FAIL,             /* 14 零拷贝驱动初始化时,分配存放报文发送消息队列用户态地址的共享内存失败 */
    SFE_DRV_INIT_ADD_SND_BUF_USER_ADDR_FAIL,                /* 15 零拷贝驱动初始化时,将存放报文发送消息队列用户态地址的共享内存加入共享名字库失败 */

    SFE_DRV_INIT_MALLOC_VCPU_SM_MEM_FAIL,                   /* 16 零拷贝驱动初始化时,分配存放驱动信号量的共享内存失败 */
    SFE_DRV_INIT_CREATE_VCPU_SM_FAIL,                       /* 17 零拷贝驱动初始化时,创建驱动信号量失败 */
    SFE_DRV_INIT_ADD_NAMEDB_VCPU_SM_FAIL,                   /* 18 零拷贝驱动初始化时,将驱动信号量的共享内存加入共享名字库失败 */
    SFE_DRV_INIT_MALLOC_PKT_RCV_INFO_FAIL,                  /* 19 零拷贝驱动初始化时,分配存放报文接收信息的共享内存失败 */
    SFE_DRV_ZCOPY_INIT_GET_ONCE_RCV_PKT_MAX_NUM_PRECFG_FAIL,/* 20 零拷贝驱动初始化时,获取驱动期望一次从内核接收的最大报文个数的预配置失败 */
    SFE_DRV_INIT_ADD_PKT_RCV_INFO_FAIL,                     /* 21 零拷贝驱动初始化时,将存放报文接收信息的共享内存加入共享名字库失败 */
    SFE_DRV_INIT_MALLOC_PKT_SND_INFO_FAIL,                  /* 22 零拷贝驱动初始化时,分配存放报文发送信息的共享内存失败 */
    SFE_DRV_ZCOPY_INIT_GET_ONCE_SND_PKT_MAX_NUM_PRECFG_FAIL,/* 23 零拷贝驱动初始化时,获取驱动期望一次从内核发送的最大报文个数的预配置失败 */
    SFE_DRV_ZCOPY_INIT_GET_ONCE_SND_TIMEOUT_PRECFG_FAIL,    /* 24 零拷贝驱动初始化时,获取驱动期望一次从内核发送的超时时间预配置失败 */
    SFE_DRV_INIT_ADD_PKT_SND_INFO_FAIL,                     /* 25 零拷贝驱动初始化时,将存放报文发送信息的共享内存加入共享名字库失败 */
    SFE_DRV_MALLOC_VCPU_DRVTIMER_MEM_FAIL,                  /* 26 零拷贝定时器初始化时,分配存放定时器的共享内存失败 */
    SFE_DRV_CREATE_VCPU_DRV_TIMER_FAIL,                     /* 27 零拷贝定时器初始化时,创建200MS定时器失败 */
    SFE_DRV_ADD_NAMEDB_VCPU_DRV_FAIL,                       /* 28 零拷贝定时器初始化时,将存放定时器的共享内存加入共享名字库失败 */

    SFE_DRV_TASK_INIT_CREATETASK_FAIL,                      /* 29 零拷贝驱动初始化时,创建驱动线程失败 */
    SFE_DRV_TASK_INIT_BINDTASK_FAIL,                        /* 30 零拷贝驱动初始化时,绑定驱动线程到指定VCPU失败 */

    SFE_DRV_ERR_RCVPKT,                                     /* 31 驱动接收报文失败 */
    SFE_DRV_ERR_INTF_CREATESOCKET_INIT,                     /* 32 驱动初始化时,创建Socket失败 */

    SFE_DRV_ERR_INTF_OPERIF_INIT,                           /* 33 驱动初始化时,向数据面添加接口失败 */
    SFE_DRV_ERR_INTF_GETIFHWADDR_INIT,                      /* 34 驱动初始化时,向Liunx获取硬件physical地址失败 */

    SFE_DRV_INIT_GET_SFE_DRV_INTF_MNG_MAX_NUM_PRECFG_FAIL,  /* 35 驱动接口管理初始化时,获取驱动接口管理支持管理的最大接口数预配置值失败 */
    SFE_DRV_MALLOC_INTF_MNG_POOL_FAIL,                      /* 36 驱动接口管理初始化时,分配驱动接口管理表项缓冲池失败 */
    SFE_DRV_INIT_MALLOC_DRV_INFO_FAIL,                      /* 37 驱动接口管理初始化时,分配驱动管理信息的共享内存失败 */
    SFE_DRV_INIT_ADD_DRV_INFO_FAIL,                         /* 38 驱动接口管理初始化时,驱动管理信息的共享内存添加到共享名字库失败 */
    SFE_DRV_MALLOC_INTF_MNGINTF_FAIL,                       /* 39 驱动接口管理初始化时,向Linux获取接口信息,创建Linux接口对应的VISP数据面接口失败 */

    SFE_DRV_ADD_INTF_ALREADY_EXIST,                         /* 40 添加接口,接口已存在 */
    SFE_DRV_ADD_INTF_NUM_EXCEED_MAX,                        /* 41 添加接口,接口已达到最大规格 */
    SFE_DRV_ADD_ALL_PORT_ID_IS_USED,                        /* 42 添加接口,冲突次数大于最大端口个数,所有端口都已使用完 */
    SFE_DRV_ADD_POOL_ALLOC_UNIT_FAIL,                       /* 43 添加接口,申请新的POOL节点失败 */
    SFE_DRV_ADD_GET_POOL_NODE_FAIL,                         /* 44 添加接口,获取分配的POOL空闲节点地址失败 */

    SFE_DRV_DEL_INTF_NOT_EXIST,                             /* 45 删除接口,待删除的节点不存在 */

    SFE_DRV_INIT_GET_DEV_INFO_FAIL,                         /* 46 初始化添加接口,获取Linux接口信息失败 */
    SFE_DRV_INIT_GET_DEV_NUM_INVALID,                       /* 47 初始化添加接口,接口个数超过了当前支持的最大规格或者小于最小规格 */

    SFE_DRV_RCVPKT_INPUT_MBUF_POINTER_NULL,                 /* 48 零拷贝功能驱动报文接收,输入出参MBUF指针为NULL */
    SFE_DRV_RCVPKT_VCPUID_INVALID,                          /* 49 零拷贝功能驱动报文接收,VCPU ID非法 */
    SFE_DRV_RCVPKT_IOCTL_FAIL,                              /* 50 零拷贝功能驱动报文接收,获取实际接收报文个数失败 */
    SFE_DRV_RCVPKT_GET_IFID_FAIL,                           /* 51 零拷贝功能驱动报文接收,根据设备ID获取数据面接口ID失败 */

    SFE_DRV_GETIFID_MODULE_NOT_INIT,                        /* 52 根据设备ID获取数据面接口ID,共享变量指针为NULL,可能是模块没有初始化 */
    SFE_DRV_GETIFID_INPUT_POINTER_NULL,                     /* 53 根据设备ID获取数据面接口ID,输入的数据面接口ID指针为空 */
    SFE_DRV_GETIFID_DEVID_NOT_EXSIT,                        /* 54 根据设备ID获取数据面接口ID,节点不存在 */

    SFE_DRV_GETDEVID_INPUT_IFID_POINTER_NULL,               /* 55 根据数据面接口ID获取设备ID,输入的数据面接口ID为空 */
    SFE_DRV_GETDEVID_INPUT_DEVID_POINTER_NULL,              /* 56 根据数据面接口ID获取设备ID,输入的设备ID指针为空 */
    SFE_DRV_GETDEVID_IFID_NOT_EXSIT,                        /* 57 根据数据面接口ID获取设备ID,节点不存在 */

    SFE_DRV_SNDPKT_INPUT_MBUF_POINTER_NULL,                 /* 58 零拷贝功能驱动报文发送,输入MBUF指针为NULL */
    SFE_DRV_SNDPKT_VCPUID_INVALID,                          /* 59 零拷贝功能驱动报文发送,VCPU ID非法 */
    SFE_DRV_SNDPKT_GET_DEVID_FAIL,                          /* 60 零拷贝功能驱动报文发送,获取驱动接口设备ID失败 */
    SFE_DRV_SND_TO_KNL_FAIL,                                /* 61 将报文通过ioctl发送到内核态时失败 */

    SFE_DRV_SET_PKTRCVQUE_MODULE_NOT_INIT,                  /* 62 设置零拷贝驱动报文接收队列信息时,共享变量指针为NULL,可能是模块没有初始化 */
    SFE_DRV_SET_PKTRCVQUE_VCPUID_INVALID,                   /* 63 设置零拷贝驱动报文接收队列信息时,VCPU ID非法 */
    SFE_DRV_SET_PKTRCVQUE_LEN_INVALID,                      /* 64 设置零拷贝驱动报文接收队列信息时,输入的接收队列长度非法 */
    SFE_DRV_SET_PKTRCVQUE_WARMINGPARA_INVALID,              /* 65 设置零拷贝驱动报文接收队列信息时,输入的告警上限限参数非法 */
    SFE_DRV_SET_PKTRCVQUE_IOCTL_FAIL,                       /* 66 设置零拷贝驱动报文接收队列信息时,调用ioctl设置失败 */

    SFE_DRV_SET_DEVMTU_MODULE_NOT_INIT,                     /* 67 设置修改接口MTU时,共享变量指针为NULL,可能是模块没有初始化 */
    SFE_DRV_SET_DEVMTU_DEVID_NOT_EXSIT,                     /* 68 设置修改接口MTU时,接口不存在 */
    SFE_DRV_INPUT_MTU_INVALID,                              /* 69 设置修改接口MTU时,输入的mtu值不合法,不在合法范围 */

    SFE_DRV_INIT_MALLOC_DRVDEVMSG_FAIL,                     /* 70 初始化添加接口,申请DRVMSGINFO内存失败 */
    SFE_DRV_RCVPKT_MBUF_VERSION_NOT_CONSISTENT,             /* 71 零拷贝功能驱动报文接收,内核态和用户态使用的MBUF头文件版本不一致 */
    SFE_DRV_SETONCERCVSNDPKTNUM_MODULE_NOT_INIT,            /* 72 设置指定核上一次从驱动接收和发送报文个数,系统未启动不能调用 */
    SFE_DRV_SETONCERCVSNDPKTNUM_VCPUID_INVALID,             /* 73 设置指定核上一次从驱动接收和发送报文个数,输入核号非法 */
    SFE_DRV_SETONCERCVSNDPKTNUM_INPUTNUM_INVALID,           /* 74 设置指定核上一次从驱动接收和发送报文个数,输入的设置参数非法 */
}SFE_DRV_ERR_CODE_E;

/*MACRO<驱动报文接收队列最小值>*/
#define SFE_DRV_PKTRCVQUE_MIN_LEN   100
/*MACRO<驱动报文接收队列最大值>*/
#define SFE_DRV_PKTRCVQUE_MAX_LEN   20000

/*MACRO<驱动接口mtu最小值>*/
#define SFE_DRV_IF_MTU_MIN_LEN   46
/*MACRO<驱动接口mtu最大值>*/
#define SFE_DRV_IF_MTU_MAX_LEN   1800
UINT32 SFE_ZEROCOPY_Init(VOID);


UINT32 SFE_DRV_Init(VOID);


UINT32 SFE_DRV_SetPktRcvQueueInfo(UINT32 u32VcpuId, UINT32 u32RcvQueLen, UINT32 u32WarningUpLimit, UINT32 u32WarningLowLimit);


UINT32 SFE_DRV_SetOnceRcvSndPktNum(UINT32 u32VcpuId, UINT32 u32OnceRcvPktNum, UINT32 u32OnceSndPktNum);


UINT32 SFE_DRV_SetDevMtu(UINT32 u32DevId, UINT32 u32Mtu);


UINT32 SFE_GetIfIdByDevId(UINT32 u32DevId, SFE_MBUF_IFID_S *pstIfId);


VOID SFE_ShowAllDrvIntf(VOID);


VOID SFE_ShowOneDrvIntf(UINT8 *pucDevName);


VOID SFE_ShowAllDrvInfo(VOID);


VOID SFE_ShowDrvInfoByVcpu(UINT32 u32VcpuId);


#ifdef  __cplusplus
}
#endif

#endif


