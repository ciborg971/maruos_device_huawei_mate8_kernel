/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pppc_uim.c
  版 本 号   : 初稿
  作    者   : w00316385
  生成日期   : 2015年08月08日
  最近修改   :
  功能描述   : 读取和更新UIM卡信息
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "pppc_uim.h"
#include "ppp_inc.h"
#include "pppc_ctrl.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_PPPC_UIM_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 固定数据集合 */
PPPC_HRPD_FIXED_DATA_STRU               g_stPppcFixedData;
PPPC_HRPD_FIXED_DATA_STRU              *pg_stPppcFixedData     = &g_stPppcFixedData;


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : PPPC_UIM_SndMsg
 功能描述  : 向UIM发送的消息
 输入参数  : VOS_UINT32              ulSenderPid,
             VOS_UINT32              ulReceiverPid,
             VOS_VOID               *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  PPPC_UIM_SndMsg
(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulReceiverPid,
    VOS_VOID                           *pMsg
)
{
    MsgBlock                           *pstMsg;
    VOS_UINT32                          ulRslt;


    pstMsg                              = (MsgBlock *)pMsg;

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulSenderPid;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = ulReceiverPid;

    /*消息发送*/
    ulRslt   = PS_SEND_MSG(ulSenderPid, pstMsg);

    if (VOS_OK != ulRslt)
    {
        PPPC_WARNING_LOG1(" PPPC_UIM_SndMsg ulRslt", ulRslt);
        return ulRslt;
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  :PPPC_UIM_ReadFileReq
功能描述  :读取文件请求
输入参数  :ulSenderPid:发送请求的PID
           pstGetFileInfo 文件信息

输出参数  :无
返 回 值  :VOS_ERR
           VOS_OK
调用函数  :

修改历史      :
 1.日    期   : 2015年08月08日
   作    者   : w00316385
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  PPPC_UIM_ReadFileReq
(
    VOS_UINT32                          ulSenderPid,
    PPPC_GET_FILE_INFO_STRU            *pstGetFileInfo
)
{
    USIMM_READFILE_REQ_STRU            *pstMsg;
    VOS_INT8                           *pucFilePathStr ;
    VOS_UINT32                          ulResult;

    pstMsg          = VOS_NULL_PTR;
    pucFilePathStr  = VOS_NULL_PTR;

    /* 参数检查 */
    if (VOS_NULL_PTR == pstGetFileInfo)
    {
        PPPC_WARNING_LOG("PPPC_UIM_ReadFileReq: pstGetFileInfo Is NULL.");
        return VOS_ERR;
    }

    /* 文件Id转文件路径 */
    if (VOS_OK != USIMM_ChangeDefFileToPath(pstGetFileInfo->usEfId, &pucFilePathStr))
    {
        PPPC_WARNING_LOG("PPPC_UIM_ReadFileReq: USIMM_ChangeDefFileToPath fail.");
        return VOS_ERR;
    }

    /* 分配消息内存并初始化 */
    /* 申请消息内存 */
    pstMsg = (USIMM_READFILE_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_READFILE_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_WARNING_LOG("PPPC_UIM_ReadFileReq: Allocate Msg Failed.");
        return VOS_ERR;
    }

    /* 填写消息头 */
    pstMsg->stMsgHeader.enMsgName       = USIMM_READFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = pstGetFileInfo->enAppType;
    pstMsg->stMsgHeader.ulSendPara      = 0;

    /* 填写消息体 */
    pstMsg->stFilePath.ulPathLen        = VOS_StrLen(pucFilePathStr);
    pstMsg->bNeedReadCache              = VOS_TRUE;
    pstMsg->ucRecordNum                 = pstGetFileInfo->ucRecordNum;
    PS_MEM_CPY(pstMsg->stFilePath.acPath, pucFilePathStr, pstMsg->stFilePath.ulPathLen);

    ulResult =  PPPC_UIM_SndMsg(MSPS_PID_PPPC, WUEPS_PID_USIM, pstMsg);

    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG1("PPPC_UIM_ReadFileReq: PPPC_UIM_SndMsg ulRslt", ulResult);
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : PPPC_INIT_SndUimReadReq
 功能描述  : 向UIM发送读取指定文件请求的接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32   是否发送成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_INIT_SndUimReadReq(VOS_VOID)
{
    PPPC_USIM_READ_REQ_STRU             stUsimReadReq;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucFileNum;
    PPPC_GET_FILE_INFO_STRU             stGetFileInfo;

    /* 清除所有的文件读取标志位 */
    PPPC_HRPD_SetUsimFileMask(0);
    PS_MEM_SET(&stUsimReadReq, 0x00, sizeof(PPPC_USIM_READ_REQ_STRU));

    /* 填充需要读的卡文件标示 */
    PPPC_HRPD_AddUsimFileMask(PPPC_INIT_USIM_ELEMENT_RUIMID_MASK);
    PPPC_HRPD_AddUsimFileMask(PPPC_INIT_USIM_ELEMENT_CST_MASK);
    PPPC_HRPD_AddUsimFileMask(PPPC_INIT_USIM_ELEMENT_ESNMEIDME_MASK);
    PPPC_HRPD_AddUsimFileMask(PPPC_INIT_USIM_ELEMENT_USGIND_MASK);
    PPPC_HRPD_AddUsimFileMask(PPPC_INIT_USIM_ELEMENT_HRPDUPP_MASK);

    /* 根据卡的类型赋值 */
    if( PPPC_HRPD_CARD_STATUS_CSIM_PRESENT == PPPC_HRPD_GetUimStatus())
    {
        stUsimReadReq.ucFileNum             = PPPC_MAX_USIM_FILE_NUM;
        stUsimReadReq.ausEfId[0]            = USIMM_CSIM_EFRUIMID_ID;
        stUsimReadReq.ausEfId[1]            = USIMM_CSIM_EFCSIMST_ID;
        stUsimReadReq.ausEfId[2]            = USIMM_CSIM_EFESNMEID_ID;
        stUsimReadReq.ausEfId[3]            = USIMM_CSIM_EFUSGIND_ID;
        stUsimReadReq.ausEfId[4]            = USIMM_CSIM_EFHRPDUPP_ID;
    }

    if( PPPC_HRPD_CARD_STATUS_UIM_PRESENT == PPPC_HRPD_GetUimStatus())
    {
        stUsimReadReq.ucFileNum             = PPPC_MAX_USIM_FILE_NUM;
        stUsimReadReq.ausEfId[0]            = USIMM_CDMA_EFRUIMID_ID;
        stUsimReadReq.ausEfId[1]            = USIMM_CDMA_EFCST_ID;
        stUsimReadReq.ausEfId[2]            = USIMM_CDMA_EFESNMEIDME_ID;
        stUsimReadReq.ausEfId[3]            = USIMM_CDMA_EFUSGIND_ID;
        stUsimReadReq.ausEfId[4]            = USIMM_CDMA_EFHRPDUPP_ID;
    }

    ucFileNum = stUsimReadReq.ucFileNum;

    if (ucFileNum > PPPC_MAX_USIM_FILE_NUM)
    {
        PPPC_WARNING_LOG1("PPPC_INIT_SndUimReadReq,ucFileNum error", stUsimReadReq.ucFileNum);

        ucFileNum = PPPC_MAX_USIM_FILE_NUM;
    }

    /* 发送读取命令 */
    for (ulLoop = 0; ulLoop < ucFileNum; ulLoop++)
    {
        stGetFileInfo.enAppType     = USIMM_CDMA_APP;
        stGetFileInfo.usEfId        = stUsimReadReq.ausEfId[ulLoop];
        stGetFileInfo.ucRecordNum   = 0;

        /* 读取 */
        ulRslt = PPPC_UIM_ReadFileReq(MSPS_PID_PPPC, &stGetFileInfo);

        /* 检查文件读取命令发送是否成功 */
        if (USIMM_API_SUCCESS != ulRslt)
        {
            PPPC_WARNING_LOG1("PPPC_INIT_SndUimReadReq,GetFileReq fail,ulEfId",
                                stUsimReadReq.ausEfId[ulLoop]);
        }

    }

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveCst
 功能描述  : 保存USIM卡文件的信息
 输入参数  : USIMM_READFILE_CNF_STRU  *pstUsimRead  消息码流
             PPPC_HRPD_CST_STRU *pstCst
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveCst(USIMM_READFILE_CNF_STRU *pstUsimRead, PPPC_HRPD_CST_STRU *pstCst)
{
    if (PPPC_INIT_USIM_ELEMENT_CST_FILE_SIZE < pstUsimRead->usEfLen)
    {
        pstCst->ucCstLen = (VOS_UINT8)PPPC_INIT_USIM_ELEMENT_CST_FILE_SIZE;
    }
    else
    {
        pstCst->ucCstLen = (VOS_UINT8)pstUsimRead->usEfLen;
    }

    PS_MEM_CPY(pstCst->aucCst, pstUsimRead->aucEf, pstCst->ucCstLen);

    return;
}

/*lint -e415*/
/*lint -e416*/
/*lint -e661*/
/*lint -e662*/
/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveHrpdupp
 功能描述  : 保存USIM卡文件的信息
 输入参数  : USIMM_READFILE_CNF_STRU  *pstUsimRead  消息码流
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveHrpdupp
(
    USIMM_READFILE_CNF_STRU            *pstUsimRead,
    PPPC_HRPD_UPP_STRU                 *pstHrpdUpp
)
{
    VOS_UINT8                           ucFileLen;
    VOS_UINT8                          *pucFileData;


    ucFileLen = *(pstUsimRead->aucEf);

    if (ucFileLen >= pstUsimRead->usEfLen)
    {
        PPPC_WARNING_LOG2("The length is different. filelen:%d, Eflen:%d.\n", ucFileLen, pstUsimRead->usEfLen);
        return;
    }

    /* 当文件是全0或全F时 */
    pucFileData = pstUsimRead->aucEf + 1;
    while ((ucFileLen > 0) && (0 == *pucFileData))
    {
        --ucFileLen;
        ++pucFileData;
    }

    if (0 == ucFileLen)
    {
        PPPC_WARNING_LOG1("The file data is 0, TotalLen:%d.\n", *(pstUsimRead->aucEf));
        return;
    }

    ucFileLen   = *(pstUsimRead->aucEf);
    pucFileData = pstUsimRead->aucEf + 1;
    while ((ucFileLen > 0) && (0xFF == *pucFileData))
    {
        --ucFileLen;
        ++pucFileData;
    }

    if (0 == ucFileLen)
    {
        PPPC_WARNING_LOG1("The file data is 0xFF, TotalLen:%d.\n", *(pstUsimRead->aucEf));
        return;
    }

    pstHrpdUpp->ucHrpdUppLen = *(pstUsimRead->aucEf);
    PS_MEM_SET(pstHrpdUpp->aucHrpdUpp, 0, PPPC_INIT_USIM_ELEMENT_HRPDUPP_FILE_SIZE);
    PS_MEM_CPY(pstHrpdUpp->aucHrpdUpp, pstUsimRead->aucEf + 1, pstHrpdUpp->ucHrpdUppLen);

    /* 保存NAI信息 */
    PPPC_SaveAccessAuthUserNameInfo(pstUsimRead->aucEf);

    return;
}
/*lint +e415*/
/*lint +e416*/
/*lint +e661*/
/*lint +e662*/

/*lint -e415*/
/*lint -e416*/
/*lint -e661*/
/*lint -e662*/
/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveEsnMeid
 功能描述  : 保存USIM卡文件的信息
 输入参数  : USIMM_READFILE_CNF_STRU  *pstUsimRead
             PPPC_HRPD_ESN_MEID_STRU  *pstEsnMeid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveEsnMeid
(
    USIMM_READFILE_CNF_STRU            *pstUsimRead,
    PPPC_HRPD_ESN_MEID_STRU            *pstEsnMeid
)
{
    VOS_UINT8                           ucCount;

    /* C.S0065 5.2.24 */
    /*
    Bytes                   Description                         M/O         Length
    1       Number of bytes for ESN_ME or MEID_ME               M           1 byte
    2       Lowest-order byteLeast significant byte M 1 byte
    3                       :                                   M           1 byte
    4                       :                                   M           1 byte
    5                       :                                   M           1 byte
    6                       :                                   M           1 byte
    7                       :                                   M           1 byte
    8       Highest-order byteMost significant byte             M           1 byte
    */

    ucCount  = pstUsimRead->aucEf[0];

    if (4 == ucCount)
    {
        pstEsnMeid->enEsnMeidType       = PPPC_HRPD_ESN_MEID_TYPE_ESN;

        pstEsnMeid->u.ulEsn             = (((VOS_UINT32)pstUsimRead->aucEf[4]) << (24))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[3]) << (16))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[2]) << (8))
                                        | (pstUsimRead->aucEf[1]);
    }
    else
    {
        pstEsnMeid->enEsnMeidType       = PPPC_HRPD_ESN_MEID_TYPE_MEID;

        /* 如果是MEID读低32bit */
        pstEsnMeid->u.stMeid.ulMeidLow  = (((VOS_UINT32)pstUsimRead->aucEf[4]) << (24))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[3]) << (16))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[2]) << (8))
                                        | (pstUsimRead->aucEf[1]);

        /* 如果是MEID读高24bit */
        pstEsnMeid->u.stMeid.ulMeidHigh = (((VOS_UINT32)pstUsimRead->aucEf[7]) << (16))
                                        | (((VOS_UINT32)pstUsimRead->aucEf[6]) << (8))
                                        | (pstUsimRead->aucEf[5]);
    }

    return;
}
/*lint +e415*/
/*lint +e416*/
/*lint +e661*/
/*lint +e662*/


/*lint -e415*/
/*lint -e416*/
/*lint -e661*/
/*lint -e662*/
/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveRuimid
 功能描述  : 保存USIM卡文件的信息
 输入参数  : USIMM_READFILE_CNF_STRU  *pstUsimRead
             PPPC_HRPD_RUIMID_STRU    *pstRuimid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveRuimid(USIMM_READFILE_CNF_STRU *pstUsimRead, PPPC_HRPD_RUIMID_STRU *pstRuimid)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucCount;

    /* C.S0065 5.2.17 */
    /*
    Bytes                   Description                         M/O         Length
    1                   Number of bytes                          M          1 byte
    2                   Lowest-order byte                        M          1 byte
    3                           :                                M          1 byte
    4                           :                                M          1 byte
    5                           :                                M          1 byte
    6                           :                                O          1 byte
    7                           :                                O          1 byte
    8                   Highest-order byte                       O          1 byte
    */

    ucCount                          = pstUsimRead->aucEf[0];

    pstRuimid->ucNumbytes            = ucCount;

    if (ucCount <= 4)
    {
        for (ulLoop = 0; ulLoop < ucCount; ulLoop++)
        {
            pstRuimid->ulRUIMIDLow  |= (((VOS_UINT32)pstUsimRead->aucEf[ulLoop + 1]) << (8 * ulLoop));
        }
    }
    else
    {
        pstRuimid->ulRUIMIDLow       = (((VOS_UINT32)pstUsimRead->aucEf[4]) << (24))
                                      | (((VOS_UINT32)pstUsimRead->aucEf[3]) << (16))
                                      | (((VOS_UINT32)pstUsimRead->aucEf[2]) << (8))
                                      | (pstUsimRead->aucEf[1]);

        /* 填充高字节 */
        for (ulLoop = 0; ulLoop < (VOS_UINT8)(ucCount - 4); ulLoop++)
        {
            pstRuimid->ulRUIMIDHigh |= (((VOS_UINT32)pstUsimRead->aucEf[ulLoop + 5]) << (8 * ulLoop));
        }
    }

    return;
}
/*lint +e415*/
/*lint +e416*/
/*lint +e661*/
/*lint +e662*/

/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveUsgInd
 功能描述  : 保存USIM卡文件的信息
 输入参数  : USIMM_READFILE_CNF_STRU  *pstUsimRead  消息码流
             VOS_UINT8 *pucSlotCycleIndex             SlotCycleIndex
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveUsgInd(USIMM_READFILE_CNF_STRU *pstUsimRead, PPPC_HRPD_USGIND_STRU *pstUsgind)
{
    /* C.S0065 5.2.14 */
    /*
    Byte 1:     b8 b7 b6 b5 b4 b3 b2 b1
                                     *  b1=0: ESN_ME is used for CAVE Authentication and MS Identification.
                                        b1=1: UIM_ID is used for CAVE Authentication and MS Identification.
                                  *     b2=0: MEID MEID_ME is used for MS Identification.
                                        b2=1: SF_EUIMID is used for MS Identification.
                *  *  *  *  *  *        RFU
    */

    pstUsgind->ucUsgInd       = pstUsimRead->aucEf[0] & 0x03;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_INIT_SaveUsimInfo
 功能描述  : 保存USIM卡文件的信息
 输入参数  : USIMM_READFILE_CNF_STRU  *pstUsimRead  消息码流
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_INIT_SaveUsimInfo(USIMM_READFILE_CNF_STRU  *pstUsimRead)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    VOS_UINT32                          ulRslt;
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileID;


    stFilePath                          = pstUsimRead->stFilePath;

    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr();

    ulRslt  = USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, stFilePath.ulPathLen, stFilePath.acPath, &enDefFileID);

    /* 将文件路径转化为ID */
    if (VOS_OK != ulRslt)
    {
        PPPC_WARNING_LOG("PPPC_INIT_SaveUsimInfo: USIMM_ChangePathToDefFileID fail.");
        return;
    }

    /* 根据需要读取的文件ID,清除对应的读卡标志位 */
    switch(enDefFileID)
    {
        case USIMM_CSIM_EFRUIMID_ID :
        case USIMM_CDMA_EFRUIMID_ID :

            /* 保存参数 */
            PPPC_INIT_SaveRuimid(pstUsimRead, &(pstUimInfo->stRuimid));

            /* 清除标记位 */
            PPPC_HRPD_RmvUsimFileMask(PPPC_INIT_USIM_ELEMENT_RUIMID_MASK);
            break;

        case USIMM_CSIM_EFCSIMST_ID :
        case USIMM_CDMA_EFCST_ID :

            /* 保存参数 */
            PPPC_INIT_SaveCst(pstUsimRead, &(pstUimInfo->stEfCst));

            /* 清除标记位 */
            PPPC_HRPD_RmvUsimFileMask(PPPC_INIT_USIM_ELEMENT_CST_MASK);
            break;

        case USIMM_CSIM_EFESNMEID_ID :
        case USIMM_CDMA_EFESNMEIDME_ID :

            /* 保存参数 */
            PPPC_INIT_SaveEsnMeid(pstUsimRead, &(pstUimInfo->stEsnMeid));

            /* 清除标记位 */
            PPPC_HRPD_RmvUsimFileMask(PPPC_INIT_USIM_ELEMENT_ESNMEIDME_MASK);
            break;

        case USIMM_CSIM_EFUSGIND_ID :
        case USIMM_CDMA_EFUSGIND_ID :

            /* 保存参数 */
            PPPC_INIT_SaveUsgInd(pstUsimRead, &(pstUimInfo->stUsgind));

            /* 清除标记位 */
            PPPC_HRPD_RmvUsimFileMask(PPPC_INIT_USIM_ELEMENT_USGIND_MASK);
            break;

        case USIMM_CSIM_EFHRPDUPP_ID :
        case USIMM_CDMA_EFHRPDUPP_ID :

            /* 保存参数 */
            PPPC_INIT_SaveHrpdupp(pstUsimRead, &(pstUimInfo->stHrpdUpp));

            /* 清除标记位 */
            PPPC_HRPD_RmvUsimFileMask(PPPC_INIT_USIM_ELEMENT_HRPDUPP_MASK);
            break;

        default:
            PPPC_WARNING_LOG1("PPPC_INIT_SaveUsimInfo, pstUsimRead->usEfId error, File:0x%x\n", enDefFileID);
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPPC_SHA1_Init
 功能描述  : 根据SHA-1算法初始化函数
 输入参数  : PPPC_HRPD_SHA1_STRU* pstSha1
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  PPPC_SHA1_Init(PPPC_HRPD_SHA1_STRU* pstSha1)
{
    /* SHA1 initialization constants */
    pstSha1->aulState[0] = 0x67452301;
    pstSha1->aulState[1] = 0xEFCDAB89;
    pstSha1->aulState[2] = 0x98BADCFE;
    pstSha1->aulState[3] = 0x10325476;
    pstSha1->aulState[4] = 0xC3D2E1F0;

    pstSha1->aulCount[0] = 0;
    pstSha1->aulCount[1] = 0;

    return ;
}

/*****************************************************************************
 函 数 名  : PPPC_SHA1_Transform
 功能描述  : SHA-1算法函数
 输入参数  : VOS_UINT32 aulState[5]
             VOS_UINT8  aucBuf[64]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_SHA1_Transform(VOS_UINT32 aulState[5], VOS_UINT8 aucBuf[64])
{
    VOS_UINT32                              ulAlph;
    VOS_UINT32                              ulBeta;
    VOS_UINT32                              ulGamm;
    VOS_UINT32                              ulDelt;
    VOS_UINT32                              ulEpsi;
    VOS_CHAR64_TO_LONG16                   *pStr;
    static VOS_UINT8                        aucArray[64];


    pStr    = (VOS_CHAR64_TO_LONG16 *)aucArray;
    PS_MEM_CPY(pStr, aucBuf, 64);

    ulAlph  = aulState[0];
    ulBeta  = aulState[1];
    ulGamm  = aulState[2];
    ulDelt  = aulState[3];
    ulEpsi  = aulState[4];

    /*lint -save -e778*/
    OPERA0(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi, 0);
    OPERA0(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt, 1);
    OPERA0(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm, 2);
    OPERA0(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta, 3);
    OPERA0(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph, 4);
    OPERA0(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi, 5);
    OPERA0(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt, 6);
    OPERA0(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm, 7);
    OPERA0(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta, 8);
    OPERA0(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph, 9);
    OPERA0(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,10);
    OPERA0(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,11);
    OPERA0(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,12);
    OPERA0(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,13);
    OPERA0(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,14);
    OPERA0(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,15);
    OPERA1(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,16);
    OPERA1(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,17);
    OPERA1(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,18);
    OPERA1(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,19);
    OPERA2(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,20);
    OPERA2(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,21);
    OPERA2(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,22);
    OPERA2(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,23);
    OPERA2(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,24);
    OPERA2(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,25);
    OPERA2(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,26);
    OPERA2(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,27);
    OPERA2(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,28);
    OPERA2(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,29);
    OPERA2(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,30);
    OPERA2(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,31);
    OPERA2(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,32);
    OPERA2(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,33);
    OPERA2(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,34);
    OPERA2(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,35);
    OPERA2(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,36);
    OPERA2(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,37);
    OPERA2(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,38);
    OPERA2(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,39);
    OPERA3(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,40);
    OPERA3(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,41);
    OPERA3(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,42);
    OPERA3(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,43);
    OPERA3(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,44);
    OPERA3(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,45);
    OPERA3(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,46);
    OPERA3(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,47);
    OPERA3(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,48);
    OPERA3(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,49);
    OPERA3(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,50);
    OPERA3(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,51);
    OPERA3(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,52);
    OPERA3(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,53);
    OPERA3(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,54);
    OPERA3(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,55);
    OPERA3(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,56);
    OPERA3(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,57);
    OPERA3(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,58);
    OPERA3(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,59);
    OPERA4(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,60);
    OPERA4(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,61);
    OPERA4(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,62);
    OPERA4(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,63);
    OPERA4(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,64);
    OPERA4(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,65);
    OPERA4(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,66);
    OPERA4(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,67);
    OPERA4(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,68);
    OPERA4(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,69);
    OPERA4(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,70);
    OPERA4(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,71);
    OPERA4(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,72);
    OPERA4(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,73);
    OPERA4(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,74);
    OPERA4(ulAlph,ulBeta,ulGamm,ulDelt,ulEpsi,75);
    OPERA4(ulEpsi,ulAlph,ulBeta,ulGamm,ulDelt,76);
    OPERA4(ulDelt,ulEpsi,ulAlph,ulBeta,ulGamm,77);
    OPERA4(ulGamm,ulDelt,ulEpsi,ulAlph,ulBeta,78);
    OPERA4(ulBeta,ulGamm,ulDelt,ulEpsi,ulAlph,79);
    /*lint -restore*/

    aulState[0] += ulAlph;
    aulState[1] += ulBeta;
    aulState[2] += ulGamm;
    aulState[3] += ulDelt;
    aulState[4] += ulEpsi;

    return ;
}

/*****************************************************************************
 函 数 名  : PPPC_SHA1_Update
 功能描述  : SHA-1算法函数
 输入参数  : PPPC_HRPD_SHA1_STRU    *pstSha1
             VOS_UINT8              *pData
             VOS_UINT32              ulLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_SHA1_Update
(
    PPPC_HRPD_SHA1_STRU                *pstSha1,
    VOS_UINT8                          *pData,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    j = pstSha1->aulCount[0];
    if ((pstSha1->aulCount[0] += ulLen << 3) < j)
    {
        pstSha1->aulCount[1] += (ulLen>>29) + 1;
    }

    j = (j >> 3) & 63;
    if ((j + ulLen) > 63)
    {
        i = 64 - j;

        PS_MEM_CPY(&pstSha1->aucBuffer[j], pData, i);

        PPPC_SHA1_Transform(pstSha1->aulState, pstSha1->aucBuffer);

        for ( ; (i + 63) < ulLen; i += 64)
        {
            PPPC_SHA1_Transform(pstSha1->aulState, &pData[i]);
        }

        j = 0;
    }
    else
    {
        i = 0;
    }

    PS_MEM_CPY(&pstSha1->aucBuffer[j], &pData[i], ulLen - i);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SHA1_Final
 功能描述  : SHA-1算法函数
 输入参数  : VOS_UINT8               aucDigest[20]
             PPPC_HRPD_SHA1_STRU    *pstSha1
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_SHA1_Final
(
    VOS_UINT8                           aucDigest[20],
    PPPC_HRPD_SHA1_STRU                *pstSha1
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           aucFinalcount[8];

    for (i = 0; i < 8; i++)
    {
        /* Endian independent */
        aucFinalcount[i] =
            (VOS_UINT8)((pstSha1->aulCount[((i >= 4) ? 0 : 1)] >> ((3-(i & 3)) * 8) ) & 255);
    }

    PPPC_SHA1_Update(pstSha1, (VOS_UINT8 *)"\200", 1);

    while ((pstSha1->aulCount[0] & 504) != 448)
    {
        PPPC_SHA1_Update(pstSha1, (VOS_UINT8 *)"\0", 1);

        /*lint !e840*/
    }

    /* Should cause a SHA1Transform() */
    PPPC_SHA1_Update(pstSha1, aucFinalcount, 8);

    if (aucDigest)
    {
        for (i = 0; i < 20; i++)
        {
            aucDigest[i] = (VOS_UINT8)((pstSha1->aulState[i>>2] >> ((3-(i & 3)) * 8) ) & 255);
        }
    }

    return ;
}

/*****************************************************************************
 函 数 名  : PPPC_GetpEsnByMeid
 功能描述  : 通过MEID获取pESN
 输入参数  : PPPC_HRPD_MEID_STRU *pucMeid
             VOS_UINT32 *pulEsn
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_GetpEsnByMeid(PPPC_HRPD_MEID_STRU *pstMeid, VOS_UINT32 *pulEsn)
{
    PPPC_HRPD_SHA1_STRU                 stSha1;
    VOS_UINT8                           aucValue[20];
    VOS_UINT8                           aucMeidTemp[PPPC_HRPD_MEID_LEN];
    VOS_UINT32                          ulTmp;
    VOS_UINT32                          ulpEsn;

    if ((VOS_NULL_PTR == pstMeid) || (VOS_NULL_PTR == pulEsn))
    {
        return VOS_ERR;
    }

    /* 56个bit长的MEID信息 */
    aucMeidTemp[0]  = (VOS_UINT8)((pstMeid->ulMeidHigh & 0x00FF0000) >> (16));
    aucMeidTemp[1]  = (VOS_UINT8)((pstMeid->ulMeidHigh & 0x0000FF00) >> (8));
    aucMeidTemp[2]  = (VOS_UINT8)( pstMeid->ulMeidHigh & 0x000000FF );
    aucMeidTemp[3]  = (VOS_UINT8)((pstMeid->ulMeidLow  & 0xFF000000) >> (24));
    aucMeidTemp[4]  = (VOS_UINT8)((pstMeid->ulMeidLow  & 0x00FF0000) >> (16));
    aucMeidTemp[5]  = (VOS_UINT8)((pstMeid->ulMeidLow  & 0x0000FF00) >> (8));
    aucMeidTemp[6]  = (VOS_UINT8)( pstMeid->ulMeidLow  & 0x000000FF);

    PS_MEM_SET(aucValue, 0, sizeof(aucValue));

    PPPC_SHA1_Init(&stSha1);

    PPPC_SHA1_Update(&stSha1, aucMeidTemp, PPPC_HRPD_MEID_LEN);

    PPPC_SHA1_Final(aucValue, &stSha1);

    /* 1.  The upper 8 bits of pseudo-ESN shall be set to 0x80.

       2.  The lower 24 bits of pseudo-ESN shall be the 24 least significant bits of the
    SHA-1 digest of the MEID. See [10] for the specification of the SHA-1
    algorithm.
    */
    ulTmp   = ((aucValue[17] << 16)
             | (aucValue[18] << 8)
             | aucValue[19]);

    ulpEsn          = ulTmp | 0x80000000;

    *pulEsn         = ulpEsn;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_InitEsnMeidWhenB1B2Eq00
 功能描述  :
            C.S0065卡协议中，当读卡的 6F42 数据即 EF(USGIND)时，若其B1B2的值为'00'时，
            则根据C.S0073协议2.3.1.4章节中的表格描述，使用MEID作为MEID，使用pESN作为ESN

            若有MEID，则使用MEID计算pESN作为ESN，否则，则直接使用ESN。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidWhenB1B2Eq00(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulpEsn;
    VOS_UINT32                          ulRslt;


    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr();
    pstTerminalInfo                     = PPPC_HRPD_GetTerminalInfoAddr();

    /* 判断是否携带MEID，若有，则使用MEID并用其计算pESN */
    if (PPPC_HRPD_ESN_MEID_TYPE_MEID == pstUimInfo->stEsnMeid.enEsnMeidType)
    {
        pstTerminalInfo->stMeid.ulMeidHigh  = pstUimInfo->stEsnMeid.u.stMeid.ulMeidHigh;
        pstTerminalInfo->stMeid.ulMeidLow   = pstUimInfo->stEsnMeid.u.stMeid.ulMeidLow;

        /* 根据MEID，用SHA-1算法算出pEsn, 在需要ESN的场景使用 */
        ulRslt  = PPPC_GetpEsnByMeid(&(pstTerminalInfo->stMeid), &ulpEsn);
        if (VOS_OK == ulRslt)
        {
            /* 将伪ESN赋值给Esn，保证在需要ESN的场景下兼容使用 */
            pstTerminalInfo->ulEsn          = ulpEsn;
        }
    }
    else
    {
        pstTerminalInfo->ulEsn              = pstUimInfo->stEsnMeid.u.ulEsn;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_InitEsnMeidWhenB1B2Eq01
 功能描述  :
            C.S0065卡协议中，当读卡的 6F42 数据即 EF(USGIND)时，若其B1B2的值为'01'时，
            则根据C.S0073协议2.3.1.4章节中的表格描述，使用MEID作为MEID，使用pUIMID作为ESN

            若有EUIMID，则使用EUIMID计算pUIMID作为ESN，否则，则直接使用pUIMID作为ESN。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidWhenB1B2Eq01(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulpEsn;
    VOS_UINT32                          ulRslt;
    PPPC_HRPD_MEID_STRU                 stMeid;


    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr();
    pstTerminalInfo                     = PPPC_HRPD_GetTerminalInfoAddr();

    PS_MEM_SET(&stMeid, 0, sizeof(PPPC_HRPD_MEID_STRU));

    /* 判断是否携带EUIMID，若有，则仅用其计算pUIMID作为ESN使用 */
    if (PPPC_HRPD_MEID_LEN == pstUimInfo->stRuimid.ucNumbytes)
    {
        stMeid.ulMeidHigh  = pstUimInfo->stRuimid.ulRUIMIDHigh;
        stMeid.ulMeidLow   = pstUimInfo->stRuimid.ulRUIMIDLow;

        /* 根据MEID，用SHA-1算法算出pEsn, 在需要ESN的场景使用 */
        ulRslt  = PPPC_GetpEsnByMeid(&stMeid, &ulpEsn);
        if (VOS_OK == ulRslt)
        {
            /* 将伪ESN赋值给Esn，保证在需要ESN的场景下兼容使用 */
            pstTerminalInfo->ulEsn          = ulpEsn;
        }
    }
    else
    {
        pstTerminalInfo->ulEsn              = pstUimInfo->stRuimid.ulRUIMIDLow;
    }

    /* 判断是否携带MEID，若有，则仅使用MEID */
    if (PPPC_HRPD_ESN_MEID_TYPE_MEID == pstUimInfo->stEsnMeid.enEsnMeidType)
    {
        pstTerminalInfo->stMeid.ulMeidHigh  = pstUimInfo->stEsnMeid.u.stMeid.ulMeidHigh;
        pstTerminalInfo->stMeid.ulMeidLow   = pstUimInfo->stEsnMeid.u.stMeid.ulMeidLow;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_InitEsnMeidWhenB1B2Eq10
 功能描述  :
            C.S0065卡协议中，当读卡的 6F42 数据即 EF(USGIND)时，若其B1B2的值为'10'时，
            则根据C.S0073协议2.3.1.4章节中的表格描述，使用EUIMID作为MEID，使用pESN作为ESN

            若有MEID，则使用MEID计算pESN作为ESN，否则，则直接使用ESN。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidWhenB1B2Eq10(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulpEsn;
    VOS_UINT32                          ulRslt;
    PPPC_HRPD_MEID_STRU                 stMeid;


    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr();
    pstTerminalInfo                     = PPPC_HRPD_GetTerminalInfoAddr();

    PS_MEM_SET(&stMeid, 0, sizeof(PPPC_HRPD_MEID_STRU));

    /* 判断是否携带MEID，若有，则仅用其计算pESN作为ESN使用 */
    if (PPPC_HRPD_ESN_MEID_TYPE_MEID == pstUimInfo->stEsnMeid.enEsnMeidType)
    {
        stMeid.ulMeidHigh  = pstUimInfo->stEsnMeid.u.stMeid.ulMeidHigh;
        stMeid.ulMeidLow   = pstUimInfo->stEsnMeid.u.stMeid.ulMeidLow;

        /* 根据MEID，用SHA-1算法算出pEsn, 在需要ESN的场景使用 */
        ulRslt  = PPPC_GetpEsnByMeid(&stMeid, &ulpEsn);
        if (VOS_OK == ulRslt)
        {
            /* 将伪ESN赋值给Esn，保证在需要ESN的场景下兼容使用 */
            pstTerminalInfo->ulEsn          = ulpEsn;
        }
    }
    else
    {
        pstTerminalInfo->ulEsn              = pstUimInfo->stEsnMeid.u.ulEsn;
    }

    /* 判断是否携带EUIMID，若有，则仅使用EUIMID作为MEID */
    if (PPPC_HRPD_MEID_LEN == pstUimInfo->stRuimid.ucNumbytes)
    {
        pstTerminalInfo->stMeid.ulMeidHigh  = pstUimInfo->stRuimid.ulRUIMIDHigh;
        pstTerminalInfo->stMeid.ulMeidLow   = pstUimInfo->stRuimid.ulRUIMIDLow;
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPPC_InitEsnMeidWhenB1B2Eq11
 功能描述  :
            C.S0065卡协议中，当读卡的 6F42 数据即 EF(USGIND)时，若其B1B2的值为'11'时，
            则根据C.S0073协议2.3.1.4章节中的表格描述，使用EUIMID作为MEID，使用pUIMID作为ESN

            若有EUIMID，则使用EUIMID计算pUIMID作为ESN，否则，则直接使用UIMID作为ESN。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidWhenB1B2Eq11(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulpEsn;
    VOS_UINT32                          ulRslt;


    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr();
    pstTerminalInfo                     = PPPC_HRPD_GetTerminalInfoAddr();

    /* 判断是否携带EUIMID，若有，则使用EUIMID作为MEID，并用其计算pUIMID作为ESN使用 */
    if (PPPC_HRPD_MEID_LEN == pstUimInfo->stRuimid.ucNumbytes)
    {
        pstTerminalInfo->stMeid.ulMeidHigh  = pstUimInfo->stRuimid.ulRUIMIDHigh;
        pstTerminalInfo->stMeid.ulMeidLow   = pstUimInfo->stRuimid.ulRUIMIDLow;

        /* 根据MEID，用SHA-1算法算出pEsn, 在需要ESN的场景使用 */
        ulRslt  = PPPC_GetpEsnByMeid(&(pstTerminalInfo->stMeid), &ulpEsn);
        if (VOS_OK == ulRslt)
        {
            /* 将伪ESN赋值给Esn，保证在需要ESN的场景下兼容使用 */
            pstTerminalInfo->ulEsn          = ulpEsn;
        }
    }
    else
    {
        pstTerminalInfo->ulEsn              = pstUimInfo->stRuimid.ulRUIMIDLow;
    }

    return;
}



/*****************************************************************************
 函 数 名  : PPPC_InitEsnMeidByUim
 功能描述  :

 3GPP2 C.S0065-B v2.0
 5.2.33  EFUSGIND (UIM_ID/SF_EUIMID Usage Indicator)

     This EF indicates whether the UIM_ID or ESN_ME is used as the 'ESN' value for
     CAVE authentication and MS identification, as per Section 4.6.1 of [46].
     This EF also indicates whether the SF_EUIMID or MEID_ME shall be used as the
     MEID field over the air when Service n34 is available.

     b1=0:   ESN_ME is used for CAVE Authentication and MS Identification.
     b1=1:    UIM_IDUIMID is used for CAVE Authentication and MS Identification.
     b2=0:    MEID MEID_ME is used for MS Identification.
     b2=1:    SF_EUIMID is used for MS Identification.

 C.S0073-A v1.0
 2.3.1.4  Method of Measurement

     Table 2 MEID and ESN fields in Extended Status Response Message
    -----------------------------------------------------------------------------------------
     No. | Mobile station support |         R-UIM            | Fields of Status Response Message
         |   of R-UIM             |     Configuration        |   MEID     |  ESN
    -----------------------------------------------------------------------------------------
     6.  |  R-UIM supported       | SF_EUIMID with bits b2b1 |   MEID     |  pESN
         |  as per [6] or [7]     | of EFUSGIND set to '00'  |            |
    -----------------------------------------------------------------------------------------
     7.  |  R-UIM supported       | SF_EUIMID with bits b2b1 |   MEID     |  pUIMID
         |  as per [6] or [7]     | of EFUSGIND set to '01'  |            |
    -----------------------------------------------------------------------------------------
     8.  |  R-UIM supported       | SF_EUIMID with bits b2b1 | SF_EUIMID  |  pESN
         |  as per [6] or [7]     | of EFUSGIND set to '10'  |            |
    -----------------------------------------------------------------------------------------
     9.  |  R-UIM supported       | SF_EUIMID with bits b2b1 | SF_EUIMID  |  pUIMID
         |  as per [6] or [7]     | of EFUSGIND set to '11'  |            |
    -----------------------------------------------------------------------------------------

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_InitEsnMeidByUim(VOS_VOID)
{
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;


    pstUimInfo                          = PPPC_HRPD_GetUimDataAddr();

    /* 若B1为'0'，B2为'0'，使用MEID/pESN */
    if (0x00 == pstUimInfo->stUsgind.ucUsgInd)
    {
        PPPC_InitEsnMeidWhenB1B2Eq00();
    }
    /* 若B1为'1'，B2为'0'，使用MEID/pUIMID */
    else if (0x01 == pstUimInfo->stUsgind.ucUsgInd)
    {
        PPPC_InitEsnMeidWhenB1B2Eq01();
    }
    /* 若B1为'0'，B2为'1'，使用SF_EUIMID/pESN */
    else if (0x02 == pstUimInfo->stUsgind.ucUsgInd)
    {
        PPPC_InitEsnMeidWhenB1B2Eq10();
    }
    /* 若B1为'1'，B2为'1'，使用SF_EUIMID/pUIMID */
    else if (0x03 == pstUimInfo->stUsgind.ucUsgInd)
    {
        PPPC_InitEsnMeidWhenB1B2Eq11();
    }
    else
    {
        /* 其他异常场景，参考标杆，用读卡时初始化的默认值0 */
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_InitUimData
 功能描述  : 读UIM中的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月8日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  PPPC_InitUimData(VOS_VOID)
{
    VOS_UINT32                           ulRslt;

    /* 将UIM数据清0 */
    PS_MEM_SET(PPPC_HRPD_GetUimDataAddr(), 0, sizeof(PPPC_HRPD_UIM_INFO_STRU));

    /* 发送读取UIM数据请求 */
    ulRslt  = PPPC_INIT_SndUimReadReq();

    if (VOS_OK != ulRslt)
    {
        PPPC_WARNING_LOG1("PPPC_InitUimData,Read Usim Fail", ulRslt);

        /* 设置UIM卡无效 */
        PPPC_HRPD_SetUimStatus(PPPC_HRPD_UIM_STATUS_ABSENT);

        return ulRslt;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_InitFixedData
 功能描述  : 初始化固定数据,包括从SIM卡中读取的数据以及NVIM中读出的数据等
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月8日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  PPPC_InitFixedData(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    PPPC_HRPD_UIM_STATUS_ENUM_UINT8     enUimStatus;


    /* 如果有卡，则读取卡信息 */
    enUimStatus    = PPPC_HRPD_GetUimStatus();
    if ((PPPC_HRPD_CARD_STATUS_CSIM_PRESENT == enUimStatus)
        || (PPPC_HRPD_CARD_STATUS_UIM_PRESENT == enUimStatus))
    {
        /* 初始化FIX DATA */
        PS_MEM_SET(PPPC_HRPD_GetFixedDataAddr(), 0, sizeof(PPPC_HRPD_FIXED_DATA_STRU));

        /* 初始化FIX DATA后，重置卡状态 */
        PPPC_HRPD_SetUimStatus(enUimStatus);

        /* 发送读UIM消息 */
        ulRslt          = PPPC_InitUimData();

        if (VOS_OK != ulRslt)
        {
            PPPC_WARNING_LOG1("PPPC_InitFixedData,PPPC_InitUimData,ulRslt:", ulRslt);
        }
    }
    else
    {
        /* 初始化FIX DATA */
        PS_MEM_SET(PPPC_HRPD_GetFixedDataAddr(), 0, sizeof(PPPC_HRPD_FIXED_DATA_STRU));

        /* 初始化FIX DATA后，重置卡状态 */
        PPPC_HRPD_SetUimStatus(PPPC_HRPD_UIM_STATUS_ABSENT);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_MD5Active
 功能描述  : MD5算法是否可用
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月8日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_MD5Active(VOS_VOID)
{
    VOS_UINT8                           ucType;
    PPPC_HRPD_UIM_INFO_STRU            *pstUimInfo;


    pstUimInfo      = PPPC_HRPD_GetUimDataAddr();
    ucType          = pstUimInfo->stEfCst.aucCst[1];


    /*  b1为0说明不支持MD5算法，b2为0说明MD5算法未激活 */
    if ((0 == (ucType & 0x01)) || (0 == (ucType & 0x02)))
    {
        return PS_FALSE;
    }

    /* UIM卡6F57文件全为0或F */
    if (0 == pstUimInfo->stHrpdUpp.ucHrpdUppLen)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 函 数 名  : PPPC_UIM_RunCaveAuthReq
 功能描述  : 向UIM发送RUN CAVE命令
 输入参数  : VOS_UINT32 ulRandu
 输出参数  : 无
 返 回 值  : VOS_UINT32   是否发送成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_UIM_RunCaveAuthReq(VOS_UINT32 ulRandu)
{
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg;
    PPPC_HRPD_NVIM_TERMINAL_INFO_STRU  *pstTerminalInfo;
    VOS_UINT32                          ulResult;


    pstTerminalInfo = PPPC_HRPD_GetTerminalInfoAddr();

    /* 分配消息内存并初始化 */
    /* 申请消息内存 */
    pstMsg = (USIMM_AUTHENTICATION_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_AUTHENTICATION_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_WARNING_LOG("PPPC_UIM_RunCaveAuthReq: Allocate Msg Failed.");
        return VOS_ERR;
    }

    /* 填写消息头 */
    pstMsg->stMsgHeader.enMsgName               = USIMM_AUTHENTICATION_REQ;
    pstMsg->stMsgHeader.enAppType               = USIMM_CDMA_APP;
    pstMsg->stMsgHeader.ulSendPara              = 0;

    /* 填写消息体 */
    pstMsg->enAuthType                          = USIMM_RUNCAVE_AUTH;
    pstMsg->uAuth.stRunCaveAuth.ucRandType      = USIMM_RUNCAVE_RAND;
    pstMsg->uAuth.stRunCaveAuth.ucDigLen        = 0;
    pstMsg->uAuth.stRunCaveAuth.ucProcessCtrl   = PPPC_HRPD_AUTH_PROCESSCTRL_SAVE_REGS_ON;

    /* 填充 RANDU 24bit */
    pstMsg->uAuth.stRunCaveAuth.aucRand[3]      = (VOS_UINT8)( ulRandu & 0x000000FF );
    pstMsg->uAuth.stRunCaveAuth.aucRand[2]      = (VOS_UINT8)(( ulRandu & 0x0000FF00 ) >> 8);
    pstMsg->uAuth.stRunCaveAuth.aucRand[1]      = (VOS_UINT8)(( ulRandu & 0x00FF0000 ) >> 16);
    pstMsg->uAuth.stRunCaveAuth.aucRand[0]      = (VOS_UINT8)(( ulRandu & 0xFF000000 ) >> 24);

    /* 根据接入类型填充Digit内容 */
    /* 默认值为0 */
    pstMsg->uAuth.stRunCaveAuth.aucDigits[0]    = 0;
    pstMsg->uAuth.stRunCaveAuth.aucDigits[1]    = 0;
    pstMsg->uAuth.stRunCaveAuth.aucDigits[2]    = 0;

    /* 填充ESN的内容 */
    pstMsg->uAuth.stRunCaveAuth.aucEsn[0]       =
                  (VOS_UINT8)(pstTerminalInfo->ulEsn & 0x000000FF);
    pstMsg->uAuth.stRunCaveAuth.aucEsn[1]       =
                  (VOS_UINT8)((pstTerminalInfo->ulEsn & 0x0000FF00) >> 8);
    pstMsg->uAuth.stRunCaveAuth.aucEsn[2]       =
                  (VOS_UINT8)((pstTerminalInfo->ulEsn & 0x00FF0000) >> 16);
    pstMsg->uAuth.stRunCaveAuth.aucEsn[3]       =
                  (VOS_UINT8)((pstTerminalInfo->ulEsn & 0xFF000000) >> 24);

    ulResult =  PPPC_UIM_SndMsg(MSPS_PID_PPPC, WUEPS_PID_USIM, pstMsg);

    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG1("PPPC_UIM_RunCaveAuthReq: PPPC_UIM_SndMsg ulRslt", ulResult);
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_VOID PPPC_UsimmReadFileCnfProc(USIMM_READFILE_CNF_STRU *pstMsg)
{
    VOS_UINT32                          ulEFID;


    USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &ulEFID);

    /* 读卡成功,才保存USIM卡信息 */
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        PPPC_INIT_SaveUsimInfo(pstMsg);
    }
    else
    {
        /* 要读取的文件失败 */
        PPPC_WARNING_LOG1("PPPC_UsimmGetFileRspMsgProc, ulResult", pstMsg->stCmdResult.ulResult);

        /* 根据需要读取的文件ID,清除对应的读卡标志位 */
        /* 根据卡类型清除标记 */

        switch(ulEFID)
        {
            case USIMM_CSIM_EFRUIMID_ID :
            case USIMM_CDMA_EFRUIMID_ID :
                PPPC_HRPD_RmvUsimFileMask(PPPC_INIT_USIM_ELEMENT_RUIMID_MASK);
                break;

            case USIMM_CSIM_EFCSIMST_ID :
            case USIMM_CDMA_EFCST_ID :
                PPPC_HRPD_RmvUsimFileMask(PPPC_INIT_USIM_ELEMENT_CST_MASK);
                break;

            case USIMM_CSIM_EFESNMEID_ID :
            case USIMM_CDMA_EFESNMEIDME_ID :
                PPPC_HRPD_RmvUsimFileMask(PPPC_INIT_USIM_ELEMENT_ESNMEIDME_MASK);
                break;

            case USIMM_CSIM_EFUSGIND_ID :
            case USIMM_CDMA_EFUSGIND_ID :
                PPPC_HRPD_RmvUsimFileMask(PPPC_INIT_USIM_ELEMENT_USGIND_MASK);
                break;

            case USIMM_CSIM_EFHRPDUPP_ID :
            case USIMM_CDMA_EFHRPDUPP_ID :
                PPPC_HRPD_RmvUsimFileMask(PPPC_INIT_USIM_ELEMENT_HRPDUPP_MASK);
                break;

            default:
                PPPC_WARNING_LOG1("PPPC_UsimmGetFileRspMsgProc, File ID is error. ulEFID:0x%x.\n", ulEFID);
                break;
        }
    }

    /* 如果所有的卡文件都读取完毕 */
    if (0 == PPPC_HRPD_GetUsimFileMask())
    {
        /* 根据卡文件初始化 ESN */
        PPPC_InitEsnMeidByUim();
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_PihUsimStatusIndProc
 功能描述  : 收到PIH模块上报的卡状态指示消息的预处理
 输入参数  : USIMM_CARDSTATUS_IND_STRU  *pstUsimMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_PihUsimStatusIndProc(USIMM_CARDSTATUS_IND_STRU  *pstUsimMsg)
{
    VOS_UINT8                           ucSimType;


    switch (pstUsimMsg->stCsimUimInfo.enCardType)
    {
        case USIMM_CARD_UIM:
            ucSimType = PPPC_HRPD_CARD_STATUS_UIM_PRESENT;
            break;

        case USIMM_CARD_CSIM:
            ucSimType = PPPC_HRPD_CARD_STATUS_CSIM_PRESENT;
            break;

        case USIMM_CARD_NOCARD:
        case USIMM_CARD_ISIM:
        default:

            ucSimType = PPPC_HRPD_UIM_STATUS_ABSENT;
            break;
    }

    PPPC_HRPD_SetUimStatus(ucSimType);

    return VOS_OK;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
