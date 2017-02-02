


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "TafXCallProcUsim.h"
#include "TafXCallCtx.h"
#include "Taf_Common.h"
#include "NasUsimmApi.h"
#include "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_TAF_X_CALL_PROC_USIM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
   2 变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID  TAF_XCALL_SndCardReadFileReq(
    USIMM_DEF_FILEID_ENUM_UINT32        enFileId,
    VOS_UINT8                           ucRecordNum
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-3, begin */
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    /* Modified by h00313353 for iteration 9, 2015-2-3, end */
    VOS_UINT32                          ulRet;

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      /* Modified by h00313353 for iteration 9, 2015-2-5, begin */
                                      USIMM_CDMA_APP,
                                      /* Modified by h00313353 for iteration 9, 2015-2-5, end */
                                      (VOS_UINT16)enFileId,
                                      ucRecordNum);

    ulRet = NAS_USIMMAPI_GetFileReq(WUEPS_PID_TAF, 0, &stGetFileInfo);

    if (USIMM_API_SUCCESS != ulRet)
    {
        /* 打印卡文件读取失败 */
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_XCALL_SndCardReadFileReq: Get File Fail ", ulRet);
        return;
    }

    return;
}
VOS_VOID  TAF_XCALL_RcvUsimReadFileCnf(
    VOS_VOID                           *pMsg
)
{
    /* 6F47文件,存储到SDC中TAF_SDC_Set1xCallUcimEmccNumList */
    /* TO DO 后续USIMM模块提供API接口直接获取紧急呼叫号码,异步接口暂不实现 */
}


#endif

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




