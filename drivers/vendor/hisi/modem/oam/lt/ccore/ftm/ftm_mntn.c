#ifdef __cplusplus
extern "C"
{
#endif

#include "v_IO.h"
#include "mdrv_om.h"
#include "msp_diag.h"
#include "ftm_mntn.h"

#define THIS_FILE_ID           MSP_FILE_ID_FTM_MNTN_C

VOS_UINT8 *g_ftm_dump_mntn = VOS_NULL;

extern VOS_MSG_HOOK_FUNC    vos_MsgHook;
extern VOS_PRINT_HOOK g_pfnPrintHook;

/*****************************************************************************
 函 数 名  : ftm_mntn_dump_init
 功能描述  : 获取并初始化ftm mntn缓冲区
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0-成功，其他-失败
*****************************************************************************/
VOS_INT32 ftm_mntn_dump_init(VOS_VOID)
{
    /* get buffer */
    g_ftm_dump_mntn = mdrv_om_register_field(OM_CP_FTM_MNTN, "ftm_mntn", NULL, NULL, 
                                                    FTM_DUMP_SIZE_12K, FTM_PARSE_VERSION);
    if (!g_ftm_dump_mntn)
    {
        (VOS_VOID)vos_printf("%s get buffer failed\n", __FUNCTION__);
        return -1;
    }

    if (0 != ftm_mntn_queue_init()){
        (VOS_VOID)vos_printf("%s queue init failed\n", __FUNCTION__);
        return -2;
    }
    (VOS_VOID)vos_printf("%s succeed, addr %p\n", __FUNCTION__, g_ftm_dump_mntn);
    return 0;
}

/*****************************************************************************
 函 数 名  : ftm_mntn_queue_init
 功能描述  : 初始化三段缓冲区
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0-成功，其他-失败
*****************************************************************************/
VOS_INT32  ftm_mntn_queue_init(VOS_VOID)
{
    VOS_INT32 res1 = -1;
    VOS_INT32 res2 = -1;
    VOS_INT32 res3 = -1;
    res1 = ftm_queue_t_init((ftm_queue_t *)g_ftm_dump_mntn, FTM_DUMP_SIZE_4K);
    res2 = ftm_queue_t_init((ftm_queue_t *)(g_ftm_dump_mntn + FTM_DUMP_SIZE_4K),
                                                            FTM_DUMP_SIZE_4K);
    res3 = ftm_queue_t_init((ftm_queue_t *)(g_ftm_dump_mntn + FTM_DUMP_SIZE_4K + FTM_DUMP_SIZE_4K), 
                                                            FTM_DUMP_SIZE_4K);
    if (!res1 && !res2 && !res3) 
        return 0;
    else
        return -1;
}

/*****************************************************************************
 函 数 名  : ftm_queue_t_init
 功能描述  : 初始化队列
 输入参数  : Q-要初始化区域首地址，size-要初始化区域大小
 输出参数  : 无
 返 回 值  : 0-成功，其他-失败
*****************************************************************************/
VOS_INT32 ftm_queue_t_init(ftm_queue_t *Q, VOS_UINT32 size)
{
    if (!Q){
        (VOS_VOID)ftm_mntn_printf("[%s]invalid input\n",__FUNCTION__);
        return -1;
    }

    (VOS_VOID)VOS_MemSet(Q, 0, sizeof(ftm_queue_t));
    Q->size = size - sizeof(ftm_queue_t);
    return 0;
}

/*****************************************************************************
 函 数 名  : ftm_queue_t_in
 功能描述  : 数据入队列
 输入参数  : Q-队列首地址，data-要入队的数据首地址，length-要入队数据长度
 输出参数  : 无
 返 回 值  : 0-成功，其他-失败
*****************************************************************************/
VOS_INT32 ftm_queue_t_in(ftm_queue_t *Q, VOS_VOID *data, VOS_UINT32 length)
{
    VOS_UINT32 len1 = 0;
    VOS_UINT32 len2 = 0;
    if ((Q == VOS_NULL) || (data == VOS_NULL)){
        return -1;
    }

    if (Q->size - Q->rear >= length){
        (VOS_VOID)VOS_MemCpy((VOS_VOID *)&Q->data[Q->rear], data, length);
        Q->rear = (Q->rear + length) % Q->size;
    }else{
        len1 = Q->size - Q->rear;
        len2 = length - (Q->size - Q->rear);
        (VOS_VOID)VOS_MemCpy((VOS_VOID *)&Q->data[Q->rear], data, len1);
        (VOS_VOID)VOS_MemCpy((VOS_VOID *)&Q->data[0], data, len2);
        Q->rear = len2;
    }
    //Q->num = Q->num + length > Q->size ? Q->size : Q->num + length;
    return 0;
}

/*****************************************************************************
 函 数 名  : ftm_mntn_at2ftm_save
 功能描述  : 存储at发往ftm的数据
 输入参数  : ulMsgId-消息id，payload-数据起始地址，ulLen-数据长度
 输出参数  : 无
 返 回 值  : 0-成功，其他-失败
*****************************************************************************/
VOS_INT32 ftm_mntn_at2ftm_save(VOS_UINT32 ulMsgId, VOS_UINT8 *payload, VOS_UINT32 ulLen)
{
    return ftm_mntn_msg_save(g_ftm_dump_mntn,ulMsgId,payload, ulLen);
}

/*****************************************************************************
 函 数 名  : ftm_mntn_ftm2at_save
 功能描述  : 存储ftm发往at的数据
 输入参数  : ulMsgId-消息id，payload-数据起始地址，ulLen-数据长度
 输出参数  : 无
 返 回 值  : 0-成功，其他-失败
*****************************************************************************/
VOS_INT32 ftm_mntn_ftm2at_save(VOS_UINT32 ulMsgId, VOS_UINT8 *payload, VOS_UINT32 ulLen)
{
    return ftm_mntn_msg_save(g_ftm_dump_mntn,ulMsgId, payload, ulLen);
}

/*****************************************************************************
 函 数 名  : ftm_mntn_ftm2mb_save
 功能描述  : 存储ftm发往mailbox的数据
 输入参数  : payload-数据起始地址，ulLen-数据长度
 输出参数  : 无
 返 回 值  : 0-成功，其他-失败
*****************************************************************************/
VOS_INT32 ftm_mntn_ftm2mb_save(VOS_UINT8 *payload, VOS_UINT32 ulLen)
{
    VOS_UINT32 msgid = 0;
    VOS_INT res = -1;
    if (!payload){
        (VOS_VOID)ftm_mntn_printf("[%s]input invalid\n",__FUNCTION__);
        return res;
    }
    (VOS_VOID)VOS_MemCpy(&msgid, payload, 4);
    if (!g_ftm_dump_mntn){
        return res;
    }
    res = ftm_mntn_msg_save(g_ftm_dump_mntn + FTM_DUMP_SIZE_4K,msgid,payload, ulLen);
    return res;
}

/*****************************************************************************
 函 数 名  : ftm_mntn_mb2ftm_save
 功能描述  : 存储mailbox发往ftm的数据
 输入参数  : ulMsgId-消息id，payload-数据起始地址，ulLen-数据长度
 输出参数  : 无
 返 回 值  : 0-成功，其他-失败
*****************************************************************************/
VOS_INT32 ftm_mntn_mb2ftm_save(VOS_UINT32 ulMsgId, VOS_UINT8 *payload, VOS_UINT32 ulLen)
{
    VOS_INT32 res = -1;
    if (!g_ftm_dump_mntn){
        return res;
    }
    res = ftm_mntn_msg_save(g_ftm_dump_mntn + FTM_DUMP_SIZE_4K,ulMsgId, payload, ulLen);
    return res;
}

VOS_INT32 ftm_mntn_msg_save(VOS_VOID *dest, VOS_UINT32 ulMsgId, VOS_UINT8 *payload, VOS_UINT32 ulLen)
{
    FTM_Mntn_Msg_Stru msgInfo;
    VOS_INT32 res = -1;

    if((!dest) || (!payload)){
        (VOS_VOID)ftm_mntn_printf("[%s]invalid input\n",__FUNCTION__);
        return -1;
    }

    /* 填充结构体 */
    msgInfo.msgId = ulMsgId;
    msgInfo.length = ulLen < FTM_MNTN_PAYLOAD_LEN ? ulLen : FTM_MNTN_PAYLOAD_LEN;
    msgInfo.stamp = VOS_GetSlice();

    if (msgInfo.length !=  FTM_MNTN_PAYLOAD_LEN){
        (VOS_VOID)VOS_MemCpy(msgInfo.payload, payload, msgInfo.length);
        (VOS_VOID)VOS_MemSet(msgInfo.payload + msgInfo.length, 0, FTM_MNTN_PAYLOAD_LEN - msgInfo.length);
    }else{
        (VOS_VOID)VOS_MemCpy(msgInfo.payload, payload, FTM_MNTN_PAYLOAD_LEN);
    }
    /* 保存结构体 */
    res = ftm_queue_t_in((ftm_queue_t *)dest, &msgInfo, sizeof(msgInfo));
    return res;
}

/*****************************************************************************
 函 数 名  : ftm_mntn_printf
 功能描述  : 将打印信息存到buffer，上传到hids并打印输出到屏幕
 输入参数  : fmt-要打印的信息
 输出参数  : 无
 返 回 值  : 0-成功，其他-失败
*****************************************************************************/
VOS_INT32 ftm_mntn_printf(const VOS_CHAR * fmt, ... )
{
    VOS_INT32  rc;
    VOS_UINT32 ulReturn = VOS_OK;
    /*lint -save -e530*/
    va_list    argument;
    /*lint -restore +e530*/
    VOS_CHAR   output_info[VOS_MAX_PRINT_LEN + 4];
    /*lint -save -e586*/
    /*lint -save -e830*/
    va_start(argument, fmt);
    /*lint -restore +e830*/
    rc = VOS_nvsprintf( output_info, VOS_MAX_PRINT_LEN, fmt, argument);
    /* 上报 */
    (VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(0, 0, 2), MSP_SYS_FTM_PID, __FILE__, __LINE__, (VOS_CHAR *)fmt, argument);

    va_end(argument);
    /*lint -restore*/

    /* 打印 */
    output_info[VOS_MAX_PRINT_LEN - 1] = '\0';

    if( rc >= VOS_MAX_PRINT_LEN - 1 )
    {
        VOS_UINT32  ulTempLen;
        VOS_CHAR *  pcWarning = " [!!!Warning: Print too long!!!]\r\n";
        ulTempLen = VOS_StrLen( pcWarning );
        (VOS_VOID)VOS_StrNCpy( output_info + ( VOS_MAX_PRINT_LEN - ulTempLen - 1 ), pcWarning, ulTempLen );
        rc = VOS_MAX_PRINT_LEN - 1; /* [false alarm]: 屏蔽Fortify错误 */

        (VOS_VOID)VOS_SetErrorNo( VOS_ERRNO_LIB_PRINTF_INPUTFORMATTOOLONG );
        ulReturn = VOS_ERRNO_LIB_PRINTF_INPUTFORMATTOOLONG;
    }
    else if( rc < 0 )
    {
        VOS_CHAR *  pcWarning = "\r\n### vos printf error: unknown internal error. ###\r\n";
        (VOS_VOID)VOS_StrCpy( output_info, pcWarning );
        rc = (VOS_INT32)VOS_StrLen( pcWarning ); /* [false alarm]: 屏蔽Fortify错误 */

        (VOS_VOID)VOS_SetErrorNo( VOS_ERRNO_LIB_PRINTF_UNKNOWNINTERERROR );
        ulReturn = VOS_ERRNO_LIB_PRINTF_UNKNOWNINTERERROR;
    }

    if( g_pfnPrintHook != VOS_NULL_PTR )
    {
        ulReturn = (VOS_UINT32)(*g_pfnPrintHook)( output_info );
        if( ulReturn != (VOS_UINT32)VOS_ERROR )
        {
            return (VOS_INT32)VOS_OK;
        }
    }

#if ((VOS_VXWORKS == VOS_OS_VER)  || (VOS_NUCLEUS == VOS_OS_VER) )
    printf( "%s",output_info );
#endif

#if (VOS_WIN32 == VOS_OS_VER)
    zprint(output_info );
#endif

#if (VOS_LINUX == VOS_OS_VER)
    printk( "%s",output_info );
#endif

#if (VOS_RTOSCK == VOS_OS_VER)
    (VOS_VOID)SRE_Printf( "%s",output_info );
#endif

    /* 保存 */
    if (!g_ftm_dump_mntn){
        return -1;
    }
    (VOS_VOID)ftm_queue_t_in((ftm_queue_t *)(g_ftm_dump_mntn + FTM_DUMP_SIZE_4K + FTM_DUMP_SIZE_4K), output_info, (VOS_UINT32)rc);

    return (VOS_INT32)ulReturn;
}

/*****************************************************************************
 函 数 名  : ftm_mntn_datahook
 功能描述  : 数据上报hids
 输入参数  : ulSendPid-发送模块id，ulRecvPid-接收模块id，ulLength-数据长度，pucData-数据起始地址
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID ftm_mntn_datahook(VOS_UINT32 ulSendPid, VOS_UINT32 ulRecvPid,VOS_UINT32 ulLength, VOS_UINT8 *pucData)
{
    MsgBlock                           *pstMsg;
    VOS_UINT32                          ulResult;

    if (VOS_NULL_PTR == vos_MsgHook)
    {
        (VOS_VOID)ftm_mntn_printf("[%s]:WARNING:vos_MsgHook is Null.\n",__FUNCTION__);
        return;
    }

    pstMsg = (MsgBlock*)VOS_AllocMsg(ulSendPid, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        (VOS_VOID)ftm_mntn_printf("[%s]:WARNING:alloc msg failed\n",__FUNCTION__);
        return;
    }

    pstMsg->ulReceiverPid   = ulRecvPid;
    pstMsg->ulLength        = ulLength;
    (VOS_VOID)VOS_MemCpy(pstMsg->aucValue, pucData, ulLength);

    ulResult = (vos_MsgHook)((VOS_VOID *)(pstMsg));
    if (VOS_OK != ulResult)
    {
        (VOS_VOID)ftm_mntn_printf("[%s]: vos_MsgHook is Failed\n",__FUNCTION__);
    }

    (VOS_VOID)VOS_FreeMsg(ulSendPid, pstMsg);
    return;
}

#ifdef __cplusplus
}
#endif

