

#ifndef _SFE_ETH_API_H_
#define _SFE_ETH_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 数据面ETH模块错误码 */
typedef enum enumSFE_ETH_ERRCODE
{
    SFE_ETH_OK  = SFE_OK,                           /* 操作成功 */    
    SFE_ETH_ERR_BEGIN = SFE_ETH_BEGIN_RET_CODE,     /* 模块错误码起始值,建议内部不要使用该值 */
    SFE_ETH_NULL_POINTER_INPUTPARA,                 /* 1  输入参数为空指针 */    
    SFE_ETH_OPERERR,                                /* 2  操作命令字错误 */

    SFE_ETH_MALLOC_FAIL_ETHPOOL,                    /* 3  分配Eth Pool资源池失败 */
    SFE_ETH_MALLOC_FAIL_ETHUNIT,                    /* 4  从Eth Pool中获取Eth单元信息失败 */
    
    SFE_ETH_NULL_ETHINFO,                           /* 5  获取Eth信息为空 */
    SFE_ETH_NULL_POINTER_TYPEINFO,                  /* 6  接口类型数组为空 */
    SFE_ETH_NULL_POINTER_FULLINFO,                  /* 7  以太全部信息数组为空 */
    SFE_ETH_ISNOTEXIST,                             /* 8  以太接口未创建 */
    SFE_ETH_SWITCH_INVALID_SETARPMISSSWITCH,        /* 9 设置ARP MISS开关,输入开关值非法 */
    SFE_ETH_PORTTYPE_NOTETH_SETARPMISSSWITCH,       /* 10 设置ARP MISS开关,接口类型不是以太类型 */

    SFE_ETH_NULL_POINTER_INPUTPARA_UPDATE,          /* 11 输入参数为空指针 */
    SFE_ETH_NULL_POINTER_INPUTPARA_GETCFG,          /* 12 输入参数为空指针 */
    SFE_ETH_NULL_POINTER_INPUTPARA_GETETH,          /* 13 输入参数为空指针 */

    SFE_ETH_MALLOC_FAIL_ETHUNIT_UPDATE,             /* 14 从Eth Pool中获取Eth单元信息失败 */
    SFE_ETH_NULL_ETHINFO_UPDATE_OLD,                /* 15 获取Eth信息为空 */
    SFE_ETH_NULL_ETHINFO_UPDATE_NEW,                /* 16 获取Eth信息为空 */
    SFE_ETH_NULL_ETHINFO_GET,                       /* 17 获取Eth信息为空 */
    
}SFE_ETH_ERRCODE_E;


#ifdef  __cplusplus
}
#endif

#endif


