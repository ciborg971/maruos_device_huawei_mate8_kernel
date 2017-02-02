
#include "usimmdl.h"
#include "usimmt1dl.h"
#include "usimmbase.h"
#include "usimmglobal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_T1_DL_C
/*lint +e767*/

/* T=1 ����������  */
USIMM_T1_CTRL_CTX_STRU          g_stUsimmT1CtrlCtx;

/* T=1 ���ݷ�����Ϣ�ṹ  */
USIMM_T1_SEND_DATA_STRU         g_stT1SendDataInfo;

/* T=1 ���ݽ�����Ϣ�ṹ  */
USIMM_T1_RCV_DATA_STRU          g_stT1RcvDataInfo;

/* T=1 ͳ����Ϣ�ṹ  */
USIMM_T1_STATISTIC_STRU         g_stT1StatisticInfo;

/* T=1 �����������ʱ��ʹ�õĻ��棬Ԥ��һ���ֽ������� */
VOS_UINT8                       g_aucT1SndBuffer[USIMM_T1_BLOCK_MAX_SIZE + 1];

/* CRC-16-CCITT��׼CRC��  */
static const VOS_UINT16 g_stT1Crc16CcittTbl[] =
{
    0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
    0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
    0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
    0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
    0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
    0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
    0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
    0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
    0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
    0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
    0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
    0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
    0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
    0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
    0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
    0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
    0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
    0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
    0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
    0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
    0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
    0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
    0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
    0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
    0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
    0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
    0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
    0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
    0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
    0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
    0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
    0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};


VOS_UINT16 USIMM_T1CalCCITTCrc16(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    VOS_UINT16      usCrc16;
    VOS_UINT16      usLoop;

    /* ��ʼ��SEED */
    usCrc16 = VOS_NULL_WORD;

    /* ������CRC16 */
    for (usLoop = 0; usLoop < ulLen; usLoop++)
    {
        usCrc16 = (usCrc16 >> 8) ^ g_stT1Crc16CcittTbl[(usCrc16 ^ pucData[usLoop]) & VOS_NULL_BYTE];
    }

    usCrc16 ^= VOS_NULL_WORD;

    return usCrc16;
}


VOS_UINT8 USIMM_T1CalLrc(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    VOS_UINT8       ucLrc;
    VOS_UINT16      usLoop;

    ucLrc = 0x00;

    /* ���ֽ���� */
    for (usLoop = 0; usLoop < ulLen; usLoop++)
    {
        ucLrc ^= pucData[usLoop];
    }

    return ucLrc;
}
VOS_VOID USIMM_T1StatisticSendSBlockSucc(
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32   enSBlkType
)
{
    switch (enSBlkType)
    {
        case USIMM_T1_S_BLOCK_RESYNCH_REQ:
            g_stT1StatisticInfo.ulSndSBlkResynchReqSuccCnt++;
            break;
        case USIMM_T1_S_BLOCK_IFS_REQ:
            g_stT1StatisticInfo.ulSndSBlkIFSReqSuccCnt++;
            break;
        case USIMM_T1_S_BLOCK_IFS_RES:
            g_stT1StatisticInfo.ulSndSBlkIFSRspSuccCnt++;
            break;
        case USIMM_T1_S_BLOCK_ABORT_REQ:
            g_stT1StatisticInfo.ulSndSBlkAbortReqSuccCnt++;
            break;
        case USIMM_T1_S_BLOCK_ABORT_RES:
            g_stT1StatisticInfo.ulSndSBlkAbortRspSuccCnt++;
            break;
        case USIMM_T1_S_BLOCK_WTX_RES:
            g_stT1StatisticInfo.ulSndSBlkWTXRspSuccCnt++;
            break;
        default:
            break;
    }

    return;
}


VOS_VOID USIMM_T1StatisticSendSBlockFail(
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32   enSBlkType
)
{
    switch (enSBlkType)
    {
        case USIMM_T1_S_BLOCK_RESYNCH_REQ:
            g_stT1StatisticInfo.ulSndSBlkResynchReqFailCnt++;
            break;
        case USIMM_T1_S_BLOCK_IFS_REQ:
            g_stT1StatisticInfo.ulSndSBlkIFSReqFailCnt++;
            break;
        case USIMM_T1_S_BLOCK_IFS_RES:
            g_stT1StatisticInfo.ulSndSBlkIFSRspFailCnt++;
            break;
        case USIMM_T1_S_BLOCK_ABORT_REQ:
            g_stT1StatisticInfo.ulSndSBlkAbortReqFailCnt++;
            break;
        case USIMM_T1_S_BLOCK_ABORT_RES:
            g_stT1StatisticInfo.ulSndSBlkAbortRspFailCnt++;
            break;
        case USIMM_T1_S_BLOCK_WTX_RES:
            g_stT1StatisticInfo.ulSndSBlkWTXRspFailCnt++;
            break;
        default:
            break;
    }

    return;
}


VOS_VOID USIMM_T1ShowCtrlAndStatisticInfo(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\n********************T1 ������������Ϣ************************\n");
    vos_printf("g_stUsimmT1CtrlCtx.ulIFSC                   %d\n", g_stUsimmT1CtrlCtx.ulIFSC);
    vos_printf("g_stUsimmT1CtrlCtx.ulIFSD                   %d\n", g_stUsimmT1CtrlCtx.ulIFSD);
    vos_printf("g_stUsimmT1CtrlCtx.enErrDetectMode          %d\n", g_stUsimmT1CtrlCtx.enErrDetectMode);
    vos_printf("g_stUsimmT1CtrlCtx.ulBWTTimes               %d\n", g_stUsimmT1CtrlCtx.ulBWTTimes);
    vos_printf("g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType    %d\n", g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType);
    vos_printf("g_stUsimmT1CtrlCtx.stSBlkPara.ucLen         %d\n", g_stUsimmT1CtrlCtx.stSBlkPara.ucLen);
    vos_printf("g_stUsimmT1CtrlCtx.stSBlkPara.ucData        %d\n", g_stUsimmT1CtrlCtx.stSBlkPara.ucData);
    vos_printf("g_stUsimmT1CtrlCtx.enT1HandleState          %d\n", g_stUsimmT1CtrlCtx.enT1HandleState);
    vos_printf("g_stUsimmT1CtrlCtx.enT1ProcState            %d\n", g_stUsimmT1CtrlCtx.enT1ProcState);
    vos_printf("g_stUsimmT1CtrlCtx.ulUESeqNum               %d\n", g_stUsimmT1CtrlCtx.ulUESeqNum);
    vos_printf("g_stUsimmT1CtrlCtx.ulUICCSeqNum             %d\n", g_stUsimmT1CtrlCtx.ulUICCSeqNum);
    vos_printf("g_stUsimmT1CtrlCtx.ulRcvBlkChainFlg         %d\n", g_stUsimmT1CtrlCtx.ulRcvBlkChainFlg);
    vos_printf("g_stUsimmT1CtrlCtx.ulSendBlkChainFlg        %d\n", g_stUsimmT1CtrlCtx.ulSendBlkChainFlg);
    vos_printf("g_stUsimmT1CtrlCtx.ulUnexpectCount          %d\n", g_stUsimmT1CtrlCtx.ulUnexpectCount);

    vos_printf("\n********************T1 ��ά�ɲ���Ϣ************************\n");
    vos_printf("����I-Block�ɹ�����ͳ��                     %d\n", g_stT1StatisticInfo.ulSndIBlkSuccCnt);
    vos_printf("����I-Blockʧ�ܴ���ͳ��                     %d\n", g_stT1StatisticInfo.ulSndIBlkFailCnt);
    vos_printf("����R-Block�ɹ�����ͳ��                     %d\n", g_stT1StatisticInfo.ulSndRBlkSuccCnt);
    vos_printf("����R-Blockʧ�ܴ���ͳ��                     %d\n", g_stT1StatisticInfo.ulSndRBlkFailCnt);
    vos_printf("����S-Block(RESYNCH Request)�ɹ�����ͳ��    %d\n", g_stT1StatisticInfo.ulSndSBlkResynchReqSuccCnt);
    vos_printf("����S-Block(RESYNCH Request)ʧ�ܴ���ͳ��    %d\n", g_stT1StatisticInfo.ulSndSBlkResynchReqFailCnt);
    vos_printf("����S-Block(IFS Request)�ɹ�����ͳ��        %d\n", g_stT1StatisticInfo.ulSndSBlkIFSReqSuccCnt);
    vos_printf("����S-Block(IFS Request)ʧ�ܴ���ͳ��        %d\n", g_stT1StatisticInfo.ulSndSBlkIFSReqFailCnt);
    vos_printf("����S-Block(IFS Response)�ɹ�����ͳ��       %d\n", g_stT1StatisticInfo.ulSndSBlkIFSRspSuccCnt);
    vos_printf("����S-Block(IFS Response)ʧ�ܴ���ͳ��       %d\n", g_stT1StatisticInfo.ulSndSBlkIFSRspFailCnt);
    vos_printf("����S-Block(ABORT Request)�ɹ�����ͳ��      %d\n", g_stT1StatisticInfo.ulSndSBlkAbortReqSuccCnt);
    vos_printf("����S-Block(ABORT Request)ʧ�ܴ���ͳ��      %d\n", g_stT1StatisticInfo.ulSndSBlkAbortReqFailCnt);
    vos_printf("����S-Block(ABORT Response)�ɹ�����ͳ��     %d\n", g_stT1StatisticInfo.ulSndSBlkAbortRspSuccCnt);
    vos_printf("����S-Block(ABORT Response)ʧ�ܴ���ͳ��     %d\n", g_stT1StatisticInfo.ulSndSBlkAbortRspFailCnt);
    vos_printf("����S-Block(WTX Response)�ɹ�����ͳ��       %d\n", g_stT1StatisticInfo.ulSndSBlkWTXRspSuccCnt);
    vos_printf("����S-Block(WTX Response)ʧ�ܴ���ͳ��       %d\n", g_stT1StatisticInfo.ulSndSBlkWTXRspFailCnt);
    vos_printf("���յ�NAD������Block����ͳ��              %d\n", g_stT1StatisticInfo.ulRcvNADErrBlkCnt);
    vos_printf("���յ������쳣(С��������С�鳤�Ȼ�����������鳤��)��Block����ͳ�� %d\n", g_stT1StatisticInfo.ulRcvBlkSizeAbnormalBlkCnt);
    vos_printf("���յ����ȴ���(ͷ+LEN+EDC���Ȳ����ڽ��յ����ܳ���)��Block����ͳ��     %d\n", g_stT1StatisticInfo.ulRcvBlkSizeErrBlkCnt);
    vos_printf("���յ�EDC������Block����ͳ��              %d\n", g_stT1StatisticInfo.ulRcvEDCErrBlkCnt);
    vos_printf("���յ���Ϣ�򳬹�IFSD��Block����ͳ��         %d\n", g_stT1StatisticInfo.ulRcvMoreThanIFSDErrBlkCnt);
    vos_printf("���յ�LEN���Ȳ�Ϊ0��R-Block����ͳ��         %d\n", g_stT1StatisticInfo.ulRcvInvalidLenRBlkCnt);
    vos_printf("���յ�PCB��bit 6��Ϊ0��R-Block����ͳ��      %d\n", g_stT1StatisticInfo.ulRcvInvalidBit6OfPCBRBlkCnt);
    vos_printf("���յ�����UE�ط���R-Block����ͳ��           %d\n", g_stT1StatisticInfo.ulRcvTriggerResendRBlkCnt);
    vos_printf("���յ�������Э�������߼���R-Block����ͳ��   %d\n", g_stT1StatisticInfo.ulRcvAbnormalRBlkCnt);
    vos_printf("���յ�������Э�������߼���I-Block����ͳ��   %d\n", g_stT1StatisticInfo.ulRcvAbnormalIBlkCnt);
    vos_printf("���յ�LEN���Ȳ�����Э���߼�(��WTX REQ��LEN!=1)��S-Block����ͳ��       %d\n", g_stT1StatisticInfo.ulRcvInvalidLenSBlkCnt);
    vos_printf("���յ�Type������Э���߼���S-Block����ͳ��   %d\n", g_stT1StatisticInfo.ulRcvInvalidTypeSBlkCnt);
    vos_printf("���յ�������Э�������߼���S-Block����ͳ��   %d\n", g_stT1StatisticInfo.ulRcvAbnormalSBlkCnt);
    vos_printf("ȥ�������ͳ��                            %d\n", g_stT1StatisticInfo.ulDeactCardCnt);
    vos_printf("���õ���ӿ�����BWTʧ�ܴ���ͳ��             %d\n", g_stT1StatisticInfo.ulSetBWTFailCnt);
    vos_printf("���õ���ӿڽ���T=0��T=1Э�������л�ʧ�ܴ���ͳ��                      %d\n", g_stT1StatisticInfo.ulProtocolSwitchFailCnt);
    /*lint +e534*/

    return;

}


VOS_VOID USIMM_T1ResetStatisticInfo(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet(&g_stT1StatisticInfo, 0, sizeof(g_stT1StatisticInfo));
    /*lint +e534*/
    return;
}


VOS_UINT32  USIMM_T1DLSendRBlock(
    USIMM_T1_R_BLOCK_ERRCODE_ENUM_UINT32    enErrcode,
    VOS_UINT32                              ulSeqNum
)
{
    VOS_UINT32      ulRBlkLen;
    VOS_UINT8      *pucRBlk;
    VOS_UINT16      usCrc16;
    VOS_INT32       lSCIResult;

    /* ����R-Block�ĳ��� */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        ulRBlkLen = USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_LRC_SIZE;
    }
    else
    {
        ulRBlkLen = USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_CRC_SIZE;
    }

    /*lint -e534*/
    VOS_MemSet(g_aucT1SndBuffer, 0, sizeof(g_aucT1SndBuffer));
    /*lint +e534*/

    pucRBlk = &g_aucT1SndBuffer[0];

    /* ���Prologue field */
    /* 1.���NADΪ0 */
    pucRBlk[T1_NAD] = 0;

    /* 2.���PCB:
         Bit 8~Bit 6: 100
         Bit 5:��дΪԤ�ڵ�N(R);
         Bit 4~Bit 1:0000-Error free;
                     0001-EDC error;
                     0002-Other error;
                     ����-RFU*/
    pucRBlk[T1_PCB] = 0x80;

    pucRBlk[T1_PCB] |= (VOS_UINT8)(ulSeqNum << (USIMM_R_BLOCK_PCB_NR_BIT - 1));

    pucRBlk[T1_PCB] |= (VOS_UINT8)enErrcode;

    /* 3.���LEN��R-block��INF����Ϊ0 */
    pucRBlk[T1_LEN] = 0;

    /* ���Epilogue field */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        pucRBlk[T1_INFO_START_BYTE] = USIMM_T1CalLrc(pucRBlk, USIMM_T1_PROLOGUE_FIELD_SIZE);
    }
    else
    {
        usCrc16 = USIMM_T1CalCCITTCrc16(pucRBlk, USIMM_T1_PROLOGUE_FIELD_SIZE);

        pucRBlk[T1_INFO_START_BYTE] = (VOS_UINT8)(usCrc16 & VOS_NULL_BYTE);
        pucRBlk[T1_INFO_START_BYTE + 1] = (VOS_UINT8)((usCrc16 >> 8) & VOS_NULL_BYTE);
    }

    /* ���õ���SCI���ͽӿ� */
    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_SND_R_BLOCK);
    lSCIResult = mdrv_sci_send_data(ulRBlkLen, pucRBlk);
    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    /* ��ȡ���͵�R-Block */
    USIMM_SciDataHook(ulRBlkLen, pucRBlk);

    if (USIMM_SCI_SUCCESS == lSCIResult)
    {
        /* ��ά�ɲ���Ϣͳ�� */
        g_stT1StatisticInfo.ulSndRBlkSuccCnt++;

        return VOS_OK;
    }
    else
    {
        /* ��ά�ɲ���Ϣͳ�� */
        g_stT1StatisticInfo.ulSndRBlkFailCnt++;

        return VOS_ERR;
    }
}


VOS_UINT32  USIMM_T1DLSendIBlock(VOS_UINT8 *pucData, VOS_UINT32 ulLen, VOS_UINT32 ulSeqNum)
{
    VOS_UINT32                                              ulIBlkLen;
    /* ���ַ�Ƭ/����Ƭ�ĳ�������Ҫ��¼��ǰ���ʵ�ʷ��͵�INF�򳤶� */
    VOS_UINT32                                              ulCurrSndInflen;
    VOS_UINT8                                              *pucIBlk;
    VOS_UINT16                                              usCrc16;
    VOS_INT32                                               lSCIResult;
    USIMM_T1_PROC_STATE_ENUM_UINT32                         enDstState;
    USIMM_T1_I_BLOCK_MORE_DATA_BIT_ENUM_UINT32              enMoreBit;

    if (0 == ulLen)
    {
        USIMM_WARNING_LOG("USIMM_T1DLSendIBlock: ulLen is 0!");

        /* ��ά�ɲ���Ϣͳ�� */
        g_stT1StatisticInfo.ulSndIBlkFailCnt++;

        return VOS_ERR;
    }
    else if (ulLen <= g_stUsimmT1CtrlCtx.ulIFSC)
    {
        ulCurrSndInflen = ulLen;
        enMoreBit = USIMM_T1_I_BLOCK_WITHOUT_MORE_DATA;
        enDstState = USIMM_T1_PROC_STATE_SENT_APDU;
    }
    else
    {
        ulCurrSndInflen = g_stUsimmT1CtrlCtx.ulIFSC;
        enMoreBit = USIMM_T1_I_BLOCK_WITH_MORE_DATA;
        enDstState = USIMM_T1_PROC_STATE_SENT_CHAIN_APDU;

        /* ����������鷢�͹����� */
        g_stUsimmT1CtrlCtx.ulSendBlkChainFlg = VOS_TRUE;
    }

    /* ����I-Block�ĳ��� */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        ulIBlkLen = USIMM_T1_PROLOGUE_FIELD_SIZE + ulCurrSndInflen + USIMM_T1_LRC_SIZE;
    }
    else
    {
        ulIBlkLen = USIMM_T1_PROLOGUE_FIELD_SIZE + ulCurrSndInflen + USIMM_T1_CRC_SIZE;
    }

    /*lint -e534*/
    VOS_MemSet(g_aucT1SndBuffer, 0, sizeof(g_aucT1SndBuffer));
    /*lint +e534*/

    pucIBlk = &g_aucT1SndBuffer[0];

    /* ���Prologue field */
    /* 1.���NADΪ0 */
    pucIBlk[T1_NAD] = 0;

    /* 2.���PCB:
         Bit 8: 0
         Bit 7: ���N(S)
         Bit 6: ��ֵΪM bit��ֵ
         Bit 5~Bit 1:RFU*/
    pucIBlk[T1_PCB] = (VOS_UINT8)(ulSeqNum << (USIMM_I_BLOCK_PCB_NS_BIT - 1));

    pucIBlk[T1_PCB] |= (VOS_UINT8)(enMoreBit << (USIMM_I_BLOCK_PCB_MORE_DATA_BIT - 1));

    /* 3.���LEN��I-block��INF������дΪ���˷��͵ĳ��� */
    pucIBlk[T1_LEN] = (VOS_UINT8)ulCurrSndInflen;

    /* ���Information field */
    /*lint -e534*/
    VOS_MemCpy(pucIBlk + T1_INFO_START_BYTE, pucData, ulCurrSndInflen);
    /*lint +e534*/

    /* ���Epilogue field */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        pucIBlk[T1_INFO_START_BYTE + ulCurrSndInflen] = USIMM_T1CalLrc(pucIBlk, USIMM_T1_PROLOGUE_FIELD_SIZE + ulCurrSndInflen);
    }
    else
    {
        usCrc16 = USIMM_T1CalCCITTCrc16(pucIBlk, USIMM_T1_PROLOGUE_FIELD_SIZE + ulCurrSndInflen);

        pucIBlk[T1_INFO_START_BYTE + ulCurrSndInflen] = (VOS_UINT8)(usCrc16 & VOS_NULL_BYTE);
        pucIBlk[T1_INFO_START_BYTE + ulCurrSndInflen + 1] = (VOS_UINT8)((usCrc16 >> 8) & VOS_NULL_BYTE);
    }

    /* ���õ���SCI���ͽӿ� */
    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_SND_I_BLOCK);
    lSCIResult = mdrv_sci_send_data(ulIBlkLen, pucIBlk);
    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    /* ��ȡ���͵�R-Block */
    USIMM_SciDataHook(ulIBlkLen, pucIBlk);

    if (USIMM_SCI_SUCCESS == lSCIResult)
    {
        /* ��״̬Ǩ����Ŀ��״̬ */
        g_stUsimmT1CtrlCtx.enT1ProcState = enDstState;

        /* ���˴η��͵�INF�򳤶ȼ�¼��ȫ�ֱ����� */
        g_stT1SendDataInfo.ulLastLen = ulCurrSndInflen;

        /* ��ά�ɲ���Ϣͳ�� */
        g_stT1StatisticInfo.ulSndIBlkSuccCnt++;

        return VOS_OK;
    }
    else
    {
        /* ��ά�ɲ���Ϣͳ�� */
        g_stT1StatisticInfo.ulSndIBlkFailCnt++;

        return VOS_ERR;
    }
}
VOS_UINT32  USIMM_T1DLSendSBlock(USIMM_T1_S_BLOCK_STRU *pstSBlk)
{
    VOS_UINT32      ulSBlkLen;
    VOS_UINT8      *pucSBlk;
    VOS_UINT16      usCrc16;
    VOS_INT32       lSCIResult;

    /* ���S-Block��Ϣ��ĳ����Ƿ�Ϸ� */
    if (pstSBlk->ucLen > 1)
    {
        USIMM_WARNING_LOG("USIMM_T1DLSendSBlock: pstSBlk->ucLen is abnormal!");
        return VOS_ERR;
    }

    /* ����S-Block�ĳ��� */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        ulSBlkLen = USIMM_T1_PROLOGUE_FIELD_SIZE + pstSBlk->ucLen + USIMM_T1_LRC_SIZE;
    }
    else
    {
        ulSBlkLen = USIMM_T1_PROLOGUE_FIELD_SIZE + pstSBlk->ucLen + USIMM_T1_CRC_SIZE;
    }

    /*lint -e534*/
    VOS_MemSet(g_aucT1SndBuffer, 0, sizeof(g_aucT1SndBuffer));
    /*lint +e534*/

    pucSBlk = &g_aucT1SndBuffer[0];

    /* ���Prologue field */
    /* 1.���NADΪ0 */
    pucSBlk[T1_NAD] = 0;

    /* 2.���PCB:
         Bit 8~Bit 7: 11
         Bit 6: 0- request;
                1- response;
         Bit 5~Bit 1:00000-RESYNCH;
                     00001-IFS;
                     00002-ABORT;
                     00003-WTX;
                     00004-VPP error(��ʹ��)
                     ����-RFU*/
    pucSBlk[T1_PCB] = (VOS_UINT8)pstSBlk->enSBlkType;

    /* 3.���LEN */
    pucSBlk[T1_LEN] = pstSBlk->ucLen;

    /* ���Information field,S-Block��LEN����Ϊ0��1 */
    if (0 != pstSBlk->ucLen)
    {
        pucSBlk[T1_INFO_START_BYTE] = pstSBlk->ucData;
    }

    /* ���Epilogue field */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        pucSBlk[T1_INFO_START_BYTE + pstSBlk->ucLen] = USIMM_T1CalLrc(pucSBlk, USIMM_T1_PROLOGUE_FIELD_SIZE + pstSBlk->ucLen);
    }
    else
    {
        usCrc16 = USIMM_T1CalCCITTCrc16(pucSBlk, USIMM_T1_PROLOGUE_FIELD_SIZE + pstSBlk->ucLen);

        pucSBlk[T1_INFO_START_BYTE + pstSBlk->ucLen] = (VOS_UINT8)(usCrc16 & VOS_NULL_BYTE);
        pucSBlk[T1_INFO_START_BYTE + pstSBlk->ucLen + 1] = (VOS_UINT8)((usCrc16 >> 8) & VOS_NULL_BYTE);
    }

    /* ���õ���SCI���ͽӿ� */
    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_SND_S_BLOCK);
    lSCIResult = mdrv_sci_send_data(ulSBlkLen, pucSBlk);
    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    /* ��ȡ���͵�R-Block */
    USIMM_SciDataHook(ulSBlkLen, pucSBlk);

    if (USIMM_SCI_SUCCESS == lSCIResult)
    {
        /* ������͵���S-Block��request֡������Ҫ��״̬����USIMM_T1_PROC_STATE_SENT_S_BLOCK_REQ */
        if (0 == (pstSBlk->enSBlkType & USIMM_S_BLOCK_PCB_REQ_RSP_BIT_MASK))
        {
            g_stUsimmT1CtrlCtx.enT1ProcState = USIMM_T1_PROC_STATE_SENT_S_BLOCK_REQ;
        }

        /* ��ά�ɲ���Ϣͳ�� */
        USIMM_T1StatisticSendSBlockSucc(pstSBlk->enSBlkType);
        return VOS_OK;
    }
    else
    {
        /* ��ά�ɲ���Ϣͳ�� */
        USIMM_T1StatisticSendSBlockFail(pstSBlk->enSBlkType);
        return VOS_ERR;
    }
}


VOS_VOID USIMM_T1DLGetBlkType(VOS_UINT8 ucPCB, USIMM_T1_BLOCK_PARA_STRU *pstBlkPara)
{
    if (USIMM_T1_BLOCK_TYPE_R == (ucPCB & USIMM_T1_BLOCK_PCB_TYPE_BIT_MASK))
    {
        /* �յ�R block */
        pstBlkPara->enBlockType = USIMM_T1_BLOCK_TYPE_R;

        /* �õ�R block����� */
        pstBlkPara->uBlockPara.stRBlockPara.ulSeqNum = (ucPCB & USIMM_R_BLOCK_PCB_NR_BIT_MASK) >> (USIMM_R_BLOCK_PCB_NR_BIT - 1);

        /* �õ�R block�Ĵ����� */
        pstBlkPara->uBlockPara.stRBlockPara.enErrcode = ucPCB & USIMM_R_BLOCK_PCB_ERRCODE_BIT_MASK;
    }
    else if (USIMM_T1_BLOCK_TYPE_S == (ucPCB & USIMM_T1_BLOCK_PCB_TYPE_BIT_MASK))
    {
        /* �յ�S block */
        pstBlkPara->enBlockType = USIMM_T1_BLOCK_TYPE_S;

        /* ��ȡS block�������� */
        pstBlkPara->uBlockPara.stSBlockPara.enSBlkType = ucPCB;
    }
    else
    {
        /* �յ�I block */
        pstBlkPara->enBlockType = USIMM_T1_BLOCK_TYPE_I;

        /* ��ȡI block����� */
        pstBlkPara->uBlockPara.stIBlockPara.ulSeqNum  = (ucPCB & USIMM_I_BLOCK_PCB_NS_BIT_MASK) >> (USIMM_I_BLOCK_PCB_NS_BIT - 1);

        /* ��ȡI block��more data bit ָʾλ */
        pstBlkPara->uBlockPara.stIBlockPara.enMoreBit = (ucPCB & USIMM_I_BLOCK_PCB_MORE_DATA_BIT_MASK) >> (USIMM_I_BLOCK_PCB_MORE_DATA_BIT - 1);
    }

    return;
}


VOS_UINT32  USIMM_T1DLCheckBlockByPCB(USIMM_T1_PROLOGUE_FIELD_STRU  *pstPrologueField)
{
    USIMM_T1_BLOCK_PARA_STRU            stBlkPara;

    /* ��ȡ�����ͼ����� */
    USIMM_T1DLGetBlkType(pstPrologueField->ucPCB, &stBlkPara);

    if (USIMM_T1_BLOCK_TYPE_R == stBlkPara.enBlockType)
    {
        /* R block ��Ϣ��Ӧ��Ϊ0 */
        if (0 != pstPrologueField->ucLen)
        {
            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulRcvInvalidLenRBlkCnt++;
            return VOS_ERR;
        }

        /* R block ��PCB�ֽ��У�bit 6����Ϊ0 */
        if (0 != (pstPrologueField->ucPCB & USIMM_R_BLOCK_PCB_SIXTH_BIT_MASK))
        {
            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulRcvInvalidBit6OfPCBRBlkCnt++;
            return VOS_ERR;
        }
    }

    if (USIMM_T1_BLOCK_TYPE_S == stBlkPara.enBlockType)
    {
        switch (stBlkPara.uBlockPara.stSBlockPara.enSBlkType)
        {
            /* ����S BLOCKӦ������Ϣ�� */
            case USIMM_T1_S_BLOCK_IFS_REQ:
            case USIMM_T1_S_BLOCK_IFS_RES:
            case USIMM_T1_S_BLOCK_WTX_REQ:
                if (1 != pstPrologueField->ucLen)
                {
                    /* ��ά�ɲ���Ϣͳ�� */
                    g_stT1StatisticInfo.ulRcvInvalidLenSBlkCnt++;
                    return VOS_ERR;
                }
                break;

            /* ����S BLOCKӦ��û����Ϣ�� */
            case USIMM_T1_S_BLOCK_RESYNCH_RES:
            case USIMM_T1_S_BLOCK_ABORT_REQ:
            case USIMM_T1_S_BLOCK_ABORT_RES:
                if (0 != pstPrologueField->ucLen)
                {
                    /* ��ά�ɲ���Ϣͳ�� */
                    g_stT1StatisticInfo.ulRcvInvalidLenSBlkCnt++;
                    return VOS_ERR;
                }
                break;

            default:
                /* �Ƿ�S BLOCK */
                /* ��ά�ɲ���Ϣͳ�� */
                g_stT1StatisticInfo.ulRcvInvalidTypeSBlkCnt++;
                return VOS_ERR;
        }
    }

    return VOS_OK;
}
VOS_BOOL USIMM_T1DLIsBlockValid(VOS_UINT32 ulLength, VOS_UINT8 *pucData)
{
    VOS_UINT8                           ucLrc;
    VOS_UINT16                          usCrc;
    USIMM_T1_PROLOGUE_FIELD_STRU        stPrologueField;
    VOS_UINT32                          ulBlkSize;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulMaxBlkSize;
    VOS_UINT32                          ulMinBlkSize;

    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        ulMinBlkSize = USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_LRC_SIZE;
    }
    else
    {
        ulMinBlkSize = USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_CRC_SIZE;
    }

    if (ulLength < ulMinBlkSize)
    {
        /* ��ά�ɲ���Ϣͳ�� */
        g_stT1StatisticInfo.ulRcvBlkSizeAbnormalBlkCnt++;
        return VOS_FALSE;
    }

    /* ����ʼ��ֵ */
    stPrologueField.ucNAD = pucData[T1_NAD];
    stPrologueField.ucPCB = pucData[T1_PCB];
    stPrologueField.ucLen = pucData[T1_LEN];

    /* ������õ���LRCУ�� */
    if (USIMM_T1_BLOCK_EPILOGUE_FIELD_LRC == g_stUsimmT1CtrlCtx.enErrDetectMode)
    {
        /* �������������С,����Ϊ��Ƿ� */
        ulMaxBlkSize = USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_MAX_IFS + USIMM_T1_LRC_SIZE;

        if (ulLength > ulMaxBlkSize)
        {
            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulRcvBlkSizeAbnormalBlkCnt++;
            return VOS_FALSE;
        }

        /* �����У��ʹ���,����Ϊ��Ƿ� */
        ucLrc = USIMM_T1CalLrc(pucData, ulLength - USIMM_T1_LRC_SIZE);

        /* LRCУ��ʹ���,���������һ���ֽ�ΪLRCУ��� */
        if (ucLrc != pucData[ulLength - 1])
        {
            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulRcvEDCErrBlkCnt++;
            return VOS_FALSE;
        }

        /* ������С */
        ulBlkSize = USIMM_T1_PROLOGUE_FIELD_SIZE + stPrologueField.ucLen + USIMM_T1_LRC_SIZE;
    }
    else
    {
        /* �������������С,����Ϊ��Ƿ� */
        ulMaxBlkSize = USIMM_T1_PROLOGUE_FIELD_SIZE + USIMM_T1_MAX_IFS + USIMM_T1_CRC_SIZE;

        if (ulLength > ulMaxBlkSize)
        {
            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulRcvBlkSizeAbnormalBlkCnt++;
            return VOS_FALSE;
        }

        /* �����У��ʹ���,����Ϊ��Ƿ� */
        usCrc = USIMM_T1CalCCITTCrc16(pucData, ulLength - USIMM_T1_CRC_SIZE);

        /* CRCУ��ʹ���,��������������ֽ�ΪCRCУ��� */
        if (usCrc != ((pucData[ulLength - 1] << 8) | pucData[ulLength - 2]))
        {
            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulRcvEDCErrBlkCnt++;
            return VOS_FALSE;
        }

        /* ������С */
        ulBlkSize = USIMM_T1_PROLOGUE_FIELD_SIZE + stPrologueField.ucLen + USIMM_T1_CRC_SIZE;
    }

    /* ���SAD��DAD��������Ϊ��Ƿ� */
    if (0 != stPrologueField.ucNAD)
    {
        /* ��ά�ɲ���Ϣͳ�� */
        g_stT1StatisticInfo.ulRcvNADErrBlkCnt++;

        return VOS_FALSE;
    }

    /* ͨ��PCB�ж��Ƿ�Ƿ� */
    ulResult = USIMM_T1DLCheckBlockByPCB(&stPrologueField);
    if (VOS_OK != ulResult)
    {
        return VOS_FALSE;
    }

    /* �����ֶ����ʵ�ʳ��Ȳ�����Ƿ� */
    if (ulBlkSize != ulLength)
    {
        /* ��ά�ɲ���Ϣͳ�� */
        g_stT1StatisticInfo.ulRcvBlkSizeErrBlkCnt++;
        return VOS_FALSE;
    }

    /* ��Ϣ�򳤶ȴ���IFSD��Ƿ� */
    if (stPrologueField.ucLen > g_stUsimmT1CtrlCtx.ulIFSD)
    {
        /* ��ά�ɲ���Ϣͳ�� */
        g_stT1StatisticInfo.ulRcvMoreThanIFSDErrBlkCnt++;
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 USIMM_T1DLProcInvalidBlock(VOS_VOID)
{
    VOS_UINT32      ulResult;

    if (g_stUsimmT1CtrlCtx.ulUnexpectCount < USIMM_T1_MAX_ATTEMPTS_TIMES)
    {
        /* ����R-BLOCK�����ش� */
        ulResult = USIMM_T1DLSendRBlock(USIMM_T1_R_BLOCK_OTHER_ERR, g_stUsimmT1CtrlCtx.ulUICCSeqNum);

        /* ���������� */
        g_stUsimmT1CtrlCtx.ulUnexpectCount++;
    }
    else
    {
        /* ������ͬ������,����Ϣ�� */
        g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_RESYNCH_REQ;
        g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
        g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

        ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);

        /* ����������,������ͬ�����������յ��Ƿ�������·���Sblock�����յ�Sblock��Ӧ������������� */
        g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;
    }

    return ulResult;
}


VOS_UINT32 USIMM_T1DLProcCardCmdRes(USIMM_APDU_ST *pstAPDUData)
{
    /* ������Ӧ����Ϊ���ֽ� */
    if (g_stT1RcvDataInfo.ulDataLen < T1_CARD_SW_LEN)
    {
        return VOS_ERR;
    }

    /* �����ϲ����ݣ������ֶθ�ֵ */
    pstAPDUData->ucSW1 = g_stT1RcvDataInfo.aucInfoData[g_stT1RcvDataInfo.ulDataLen - 2];
    pstAPDUData->ucSW2 = g_stT1RcvDataInfo.aucInfoData[g_stT1RcvDataInfo.ulDataLen - 1];

    if ((g_stT1RcvDataInfo.ulDataLen - T1_CARD_SW_LEN) <= USIMM_APDU_MAXLEN)
    {
        /*lint -e534*/
        VOS_MemCpy(pstAPDUData->aucRecvBuf, g_stT1RcvDataInfo.aucInfoData, g_stT1RcvDataInfo.ulDataLen - T1_CARD_SW_LEN);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(pstAPDUData->aucRecvBuf, g_stT1RcvDataInfo.aucInfoData, USIMM_APDU_MAXLEN);
        /*lint +e534*/
    }

    pstAPDUData->ulRecDataLen = g_stT1RcvDataInfo.ulDataLen - T1_CARD_SW_LEN;

    pstAPDUData->ucApduSW1 = pstAPDUData->ucSW1;
    pstAPDUData->ucApduSW2 = pstAPDUData->ucSW2;

    /*lint -e534*/
    VOS_MemSet(pstAPDUData->aucGetRepAPDU, 0, USIMM_APDU_HEADLEN);
    /*lint +e534*/

    return VOS_OK;
}


VOS_UINT32  USIMM_T1DLReSendSBlock(VOS_VOID)
{
    VOS_UINT32      ulResult;

    /* �ط������ѳ��������� */
    if (g_stUsimmT1CtrlCtx.ulUnexpectCount >= USIMM_T1_MAX_ATTEMPTS_TIMES)
    {
        /* ��ͬ�������ѷ������λ���IFS����������ֱ�Ӹ�λ */
        if ((USIMM_T1_S_BLOCK_RESYNCH_REQ == g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType)
            ||(USIMM_T1_S_BLOCK_IFS_REQ == g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType))
        {
            /* ���õ���APIȥ��� */
            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_RST);
            ulResult = mdrv_sci_deact();

            if (USIMM_SCI_SUCCESS != ulResult)
            {
                USIMM_ERROR_LOG("USIMM_T1DLReSendSBlock: Deactive Card Error");
            }
            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulDeactCardCnt++;

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
            /* �˳�����Ҫ�ϱ��޿���Э��ջ */
            USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);
#else
            /* �˳�����Ҫ�ϱ��޿���Э��ջ */
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enStateChange  = USIMM_CARD_STATE_CHANGED;
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType     = USIMM_CARD_NOCARD;
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService  = USIMM_CARD_SERVIC_ABSENT;
#endif

            g_stUsimmT1CtrlCtx.enT1ProcState = USIMM_T1_PROC_STATE_IDLE;

            return VOS_ERR;
        }
        else
        {
            /* ������ͬ������ */
            g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_RESYNCH_REQ;
            g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;
            g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;

            ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);

            /* �ط��������������� */
            g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;
        }
    }
    else
    {
        /* �ط�S BLOCK */
        ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);

        /* �ط��������������� */
        g_stUsimmT1CtrlCtx.ulUnexpectCount++;
    }

    return ulResult;
}


VOS_UINT32 USIMM_T1DLProcRcvSBlockReq(
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32   enSBlkType,
    VOS_UINT8                           ucData
)
{
    VOS_UINT32      ulResult;

    switch (enSBlkType)
    {
        case USIMM_T1_S_BLOCK_IFS_REQ:

            /* IFSC���ڷ�Χ�ڣ��򲻸���ȫ�ֱ���,����ͬ������ */
            if ((ucData > USIMM_T1_MAX_IFS) || (ucData < USIMM_T1_MIN_IFS))
            {
                g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_RESYNCH_REQ;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

                /* �ط��������������� */
                g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;
            }
            else
            {
                /* ����IFSC */
                g_stUsimmT1CtrlCtx.ulIFSC = ucData;

                /* �ظ���Ӧ */
                g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_IFS_RES;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = sizeof(ucData);
                g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = ucData;
            }

            ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);
            break;

        case USIMM_T1_S_BLOCK_ABORT_REQ:

            /* �ж��Ƿ������鷢���� */
            if (VOS_TRUE == g_stUsimmT1CtrlCtx.ulSendBlkChainFlg)
            {
                /* ����ѷ������� */
                g_stT1SendDataInfo.pucLastInfoData = g_stT1SendDataInfo.aucInfoData;
                g_stT1SendDataInfo.ulLastLen       = 0;
                g_stT1SendDataInfo.ulLastTotalLen  = 0;

                /* �ظ���Ӧ */
                g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_ABORT_RES;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

                ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);
            }
            else if (VOS_TRUE == g_stUsimmT1CtrlCtx.ulRcvBlkChainFlg) /* �ж��Ƿ������������ */
            {
                /* ��ս������� */
                g_stT1RcvDataInfo.ulDataLen = 0;

                /* �ظ���Ӧ */
                g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_ABORT_RES;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

                ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);
            }
            else /* �����֧ */
            {
                /* ������Ӧ, ������ͬ������ */
                g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_RESYNCH_REQ;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

                /* �ط��������������� */
                g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

                ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);
            }
            break;

        case USIMM_T1_S_BLOCK_WTX_REQ:
            /* �ж�BWT�����Ƿ�Ϸ� */
            if (0 == ucData)
            {
                /* BWT�����Ƿ�, ������ͬ������ */
                g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_RESYNCH_REQ;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
                g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

                /* �ط��������������� */
                g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

                ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);
                return ulResult;
            }

            /* ����WTX */
            g_stUsimmT1CtrlCtx.ulBWTTimes = ucData;

            /* �ظ���Ӧ */
            g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_WTX_RES;
            g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = sizeof(ucData);
            g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = ucData;

            ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);

            /* �������ݳ��� */
            if (VOS_OK != ulResult)
            {
                break;
            }

            /* ���õ���API����BWT��ʱ */
            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_SET_BWT_1);
            if (USIMM_SCI_SUCCESS == mdrv_sci_set_bwt(ucData))
            {
                ulResult = VOS_OK;
            }
            else
            {
                ulResult = VOS_ERR;

                /* ��ά�ɲ���Ϣͳ�� */
                g_stT1StatisticInfo.ulSetBWTFailCnt++;
            }
            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

            break;

        default:
            /* ������Ӧ, ����RULE 7.1����Ҫ����R-BLOCK�����ش� */
            ulResult = USIMM_T1DLSendRBlock(USIMM_T1_R_BLOCK_OTHER_ERR, g_stUsimmT1CtrlCtx.ulUICCSeqNum);

            /* ���������� */
            g_stUsimmT1CtrlCtx.ulUnexpectCount++;

            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulRcvAbnormalSBlkCnt++;

            break;
    }

    return ulResult;
}


VOS_UINT32 USIMM_T1DLProcRcvSBlockRes(
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32   enSBlkType,
    VOS_UINT8                           ucData
)
{
    VOS_UINT32                          ulResult = VOS_OK;
    NV_USIMM_T1_CTRL_PARA_STRU          stT1CtrlPara;

    /* �ж��յ�����Ӧ�ͷ��͵�REQ�Ƿ�ƥ�䣬��ƥ�������·���REQ */
    if (enSBlkType != (USIMM_S_BLOCK_PCB_REQ_RSP_BIT_MASK | g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType))
    {
        ulResult = USIMM_T1DLReSendSBlock();

        /* ��ά�ɲ���Ϣͳ�� */
        g_stT1StatisticInfo.ulRcvAbnormalSBlkCnt++;

        return ulResult;
    }

    switch(enSBlkType)
    {
        case USIMM_T1_S_BLOCK_IFS_RES:

            /*lint -e534*/
            VOS_MemSet(&stT1CtrlPara, 0, sizeof(stT1CtrlPara));
            /*lint +e534*/

            if(VOS_OK != NV_Read(en_NV_Item_Usimm_T1_Ctrl_PARA, &stT1CtrlPara, sizeof(stT1CtrlPara)))
            {
                /* ��ӡ���� */
                USIMM_ERROR_LOG("USIMM_DecideTMode:USIM Read T1 PARA NV error");
            }

            if (ucData != stT1CtrlPara.ulDefaultIFSD)
            {
                /* ��IFS REQ�еĲ���ͬ�����·���IFS REQ */
                ulResult = USIMM_T1DLReSendSBlock();
            }
            else
            {
                /* ����IFSD��ֵ */
                g_stUsimmT1CtrlCtx.ulIFSD = ucData;

                /* IFS REQֻ�ڳ�ʼ����һ�η��ͣ�����յ���Ӧ��״̬����ΪIDLE */
                g_stUsimmT1CtrlCtx.enT1ProcState = USIMM_T1_PROC_STATE_IDLE;
            }

            break;

        case USIMM_T1_S_BLOCK_RESYNCH_RES:

            /* ����UE�Ϳ��Ŀ��ʼ��� */
            g_stUsimmT1CtrlCtx.ulUESeqNum = USIMM_T1_I_BLOCK_INIT_SEQ;
            g_stUsimmT1CtrlCtx.ulUICCSeqNum = USIMM_T1_I_BLOCK_INIT_SEQ;

            /* ����ѷ������� */
            g_stT1SendDataInfo.pucLastInfoData = g_stT1SendDataInfo.aucInfoData;
            g_stT1SendDataInfo.ulLastLen       = 0;
            g_stT1SendDataInfo.ulLastTotalLen  = 0;

            /* ���·���I-BLOCK */
            ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.aucInfoData, g_stT1SendDataInfo.ulTotalLen,
                                            g_stUsimmT1CtrlCtx.ulUESeqNum);

            break;

        case USIMM_T1_S_BLOCK_ABORT_RES:

            /* ��ǰ�ڷ������飬�����·������� */
            if (VOS_TRUE == g_stUsimmT1CtrlCtx.ulSendBlkChainFlg)
            {
                /* ���ѷ����������� */
                g_stT1SendDataInfo.pucLastInfoData = g_stT1SendDataInfo.aucInfoData;
                g_stT1SendDataInfo.ulLastLen       = 0;
                g_stT1SendDataInfo.ulLastTotalLen  = 0;

                /* ���·������� */
                ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.aucInfoData, g_stT1SendDataInfo.ulTotalLen,
                                            g_stUsimmT1CtrlCtx.ulUESeqNum);
            }
            else if (VOS_TRUE == g_stUsimmT1CtrlCtx.ulRcvBlkChainFlg)/* ��ǰ�ڽ������飬���·���I-BLOCK����������Ľ��� */
            {
                /* ����ѽ������ݳ��� */
                g_stT1RcvDataInfo.ulDataLen = 0;

                /* ���·������� */
                ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.aucInfoData, g_stT1SendDataInfo.ulTotalLen,
                                            g_stUsimmT1CtrlCtx.ulUESeqNum);
            }
            else
            {
                /* ������Ӧ,���·���S-BLOCK */
                ulResult = USIMM_T1DLReSendSBlock();
            }

            break;

        default:
            /* ������Ӧ,���·���S-BLOCK */
            ulResult = USIMM_T1DLReSendSBlock();

            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulRcvAbnormalSBlkCnt++;

            break;
    }

    return ulResult;
}


VOS_UINT32 USIMM_T1DLProcSBlock(
    USIMM_T1_S_BLOCK_TYPE_ENUM_UINT32   enSBlkType,
    VOS_UINT8                          *pucInfData
)
{
    VOS_UINT32      ulResult;

    /* ��ǰ���͹�S BLOCK REQ,�ȴ�����response */
    if (USIMM_T1_PROC_STATE_SENT_S_BLOCK_REQ == g_stUsimmT1CtrlCtx.enT1ProcState)
    {
        ulResult = USIMM_T1DLProcRcvSBlockRes(enSBlkType, *pucInfData);
    }
    else /* �յ�S BLOCK REQ */
    {
        ulResult = USIMM_T1DLProcRcvSBlockReq(enSBlkType, *pucInfData);
    }

    return ulResult;
}


VOS_UINT32 USIMM_T1DLProcIBlockRes(
    USIMM_T1_I_BLOCK_MORE_DATA_BIT_ENUM_UINT32  enMoreBit,
    USIMM_T1_PROLOGUE_FIELD_STRU               *pstPrologueField,
    VOS_UINT8                                  *pucInformationData
)
{
    VOS_UINT32      ulResult = VOS_OK;

    /* �ж��Ƿ�Ϊ�������� */
    if (USIMM_T1_I_BLOCK_WITH_MORE_DATA == enMoreBit)
    {
        /* ���������Ľ����� */
        g_stUsimmT1CtrlCtx.ulRcvBlkChainFlg = VOS_TRUE;

        /* �ط��������������� */
        g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

        /* ��������У�����������ŷ�ת */
        g_stUsimmT1CtrlCtx.ulUICCSeqNum = (g_stUsimmT1CtrlCtx.ulUICCSeqNum + 1) % 2;

        /* ����buf���Ļ��������� */
        if ((g_stT1RcvDataInfo.ulDataLen + pstPrologueField->ucLen) <= USIMM_T1_RCV_BUF_SIZE)
        {
            /* �洢���� */
            /*lint -e534*/
            VOS_MemCpy(&(g_stT1RcvDataInfo.aucInfoData[g_stT1RcvDataInfo.ulDataLen]), pucInformationData, pstPrologueField->ucLen);
            /*lint +e534*/

            g_stT1RcvDataInfo.ulDataLen += pstPrologueField->ucLen;
        }

        /* ����R BLOCKȷ�Ͽ飬������һ�����ݿ� */
        ulResult = USIMM_T1DLSendRBlock(USIMM_T1_R_BLOCK_ERROR_FREE, g_stUsimmT1CtrlCtx.ulUICCSeqNum);
    }
    else
    {
        /* ������¹�WTX�����յ�������Ӧ�󣬻ָ�WTXֵ */
        if (USIMM_T1_DEFAULT_WTX != g_stUsimmT1CtrlCtx.ulBWTTimes)
        {
            /* ���õ���API����BWT��ʱ */
            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_RST_BWT_2);
            if (USIMM_SCI_SUCCESS != mdrv_sci_set_bwt(USIMM_T1_DEFAULT_WTX))
            {
                /* ������õ���API������ӡ���� */
                USIMM_ERROR_LOG("USIMM_T1DLProcIBlockRes:Set BWT to default value fail");

                /* ��ά�ɲ���Ϣͳ�� */
                g_stT1StatisticInfo.ulSetBWTFailCnt++;
            }
            else
            {
                g_stUsimmT1CtrlCtx.ulBWTTimes = USIMM_T1_DEFAULT_WTX;
            }
            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);
        }

        /* �յ�����apdu����Ӧ������������һ����Ӧ��������ź�����������Ŷ�Ҫ��ת */
        g_stUsimmT1CtrlCtx.ulUESeqNum = (g_stUsimmT1CtrlCtx.ulUESeqNum + 1) % 2;

        g_stUsimmT1CtrlCtx.ulUICCSeqNum = (g_stUsimmT1CtrlCtx.ulUICCSeqNum + 1) % 2;

        if ((g_stT1RcvDataInfo.ulDataLen + pstPrologueField->ucLen) <= USIMM_T1_RCV_BUF_SIZE)
        {
            /* �洢���� */
            /*lint -e534*/
            VOS_MemCpy(&(g_stT1RcvDataInfo.aucInfoData[g_stT1RcvDataInfo.ulDataLen]), pucInformationData, pstPrologueField->ucLen);
            /*lint +e534*/

            g_stT1RcvDataInfo.ulDataLen += pstPrologueField->ucLen;
        }
        else if (g_stT1RcvDataInfo.ulDataLen + T1_CARD_SW_LEN <= USIMM_T1_RCV_BUF_SIZE)
        {
            /* buf�����洢�����������ݣ����ֻ�洢״̬�� */
            /*lint -e534*/
            VOS_MemCpy(&(g_stT1RcvDataInfo.aucInfoData[g_stT1RcvDataInfo.ulDataLen]),
                       (pucInformationData + pstPrologueField->ucLen - T1_CARD_SW_LEN), T1_CARD_SW_LEN);
            /*lint +e534*/

            g_stT1RcvDataInfo.ulDataLen += T1_CARD_SW_LEN;
        }
        else
        {
            /* buf�����洢״̬�֣����״̬�ָ���ԭ�к��������� */
            /*lint -e534*/
            VOS_MemCpy(&(g_stT1RcvDataInfo.aucInfoData[USIMM_T1_RCV_BUF_SIZE-T1_CARD_SW_LEN]),
                       (pucInformationData + pstPrologueField->ucLen - T1_CARD_SW_LEN), T1_CARD_SW_LEN);
            /*lint +e534*/

            g_stT1RcvDataInfo.ulDataLen = USIMM_T1_RCV_BUF_SIZE;
        }

        /* �ط��������������� */
        g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

        /* ��������������ΪVOS_FALSE */
        g_stUsimmT1CtrlCtx.ulRcvBlkChainFlg = VOS_FALSE;

        /* ��������������ΪVOS_FALSE */
        g_stUsimmT1CtrlCtx.ulSendBlkChainFlg = VOS_FALSE;

        /* �յ���������Ӧ���� */
        g_stUsimmT1CtrlCtx.enT1ProcState = USIMM_T1_PROC_STATE_IDLE;
    }

    return ulResult;
}
VOS_UINT32 USIMM_T1DLProcIdleState(VOS_BOOL bValidFlag, VOS_UINT32 ulLength, VOS_UINT8 *pucData)
{
    USIMM_ERROR_LOG("USIMM_T1DLProcIdleState: Usimm T1 DL receive block Run into Error State");

    return VOS_ERR;
}


VOS_UINT32 USIMM_T1DLProcSendApduState(
    VOS_BOOL        bValidFlag,
    VOS_UINT32      ulLength,
    VOS_UINT8      *pucData
)
{
    VOS_UINT32                          ulResult;
    USIMM_T1_BLOCK_PARA_STRU            stBlkPara;
    USIMM_T1_PROLOGUE_FIELD_STRU        stPrologueField;
    VOS_UINT8                          *pucInformationData;

    /* ����Ƿ��� */
    if (VOS_FALSE == bValidFlag)
    {
        ulResult = USIMM_T1DLProcInvalidBlock();

        return ulResult;
    }

    /* ����������Ӧ */
    stPrologueField.ucNAD = pucData[T1_NAD];
    stPrologueField.ucPCB = pucData[T1_PCB];
    stPrologueField.ucLen = pucData[T1_LEN];
    pucInformationData    = pucData + T1_INFO_START_BYTE;

    /* ��ȡ�����ͼ����� */
    USIMM_T1DLGetBlkType(stPrologueField.ucPCB, &stBlkPara);

    if (USIMM_T1_BLOCK_TYPE_I == stBlkPara.enBlockType)
    {
        /* �ж��Ƿ�Ϊ���Ƿ�����I BLOCK����Ӧ���� */
        if (stBlkPara.uBlockPara.stIBlockPara.ulSeqNum == g_stUsimmT1CtrlCtx.ulUICCSeqNum)
        {
            ulResult = USIMM_T1DLProcIBlockRes(stBlkPara.uBlockPara.stIBlockPara.enMoreBit, &stPrologueField, pucInformationData);
        }
        else
        {
            /* �����������������ݣ�����R Block�������ط� */
            ulResult = USIMM_T1DLSendRBlock(USIMM_T1_R_BLOCK_OTHER_ERR, g_stUsimmT1CtrlCtx.ulUICCSeqNum);

            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulRcvAbnormalIBlkCnt++;
        }
    }
    else if (USIMM_T1_BLOCK_TYPE_R == stBlkPara.enBlockType)
    {
        /* ��ο��ƴ˴� �����ڴ˴���ѭ�� */
        if (stBlkPara.uBlockPara.stRBlockPara.ulSeqNum == g_stUsimmT1CtrlCtx.ulUESeqNum)
        {
            /* ���·���I BLOCK */
            ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.pucLastInfoData,
                                            g_stT1SendDataInfo.ulTotalLen - g_stT1SendDataInfo.ulLastTotalLen,
                                            g_stUsimmT1CtrlCtx.ulUESeqNum);

            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulRcvTriggerResendRBlkCnt++;
        }
        else
        {
            /* �յ�һ���������Ŀ飬���󷢳���I BLOCK����Ӧ���ݿ� */
            ulResult = USIMM_T1DLSendRBlock(USIMM_T1_R_BLOCK_OTHER_ERR, g_stUsimmT1CtrlCtx.ulUICCSeqNum);

            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulRcvAbnormalRBlkCnt++;
        }
    }
    else
    {
        ulResult = USIMM_T1DLProcSBlock(stBlkPara.uBlockPara.stSBlockPara.enSBlkType, pucInformationData);
    }

    return ulResult;
}
VOS_UINT32 USIMM_T1DLProcSendChainApduState(
    VOS_BOOL        bValidFlag,
    VOS_UINT32      ulLength,
    VOS_UINT8      *pucData
)
{
    VOS_UINT32                          ulResult;
    USIMM_T1_BLOCK_PARA_STRU            stBlkPara;
    USIMM_T1_PROLOGUE_FIELD_STRU        stPrologueField;
    VOS_UINT8                          *pucInformationData;

    /* ����Ƿ��� */
    if (VOS_FALSE == bValidFlag)
    {
        ulResult = USIMM_T1DLProcInvalidBlock();

        return ulResult;
    }

    /* ����������Ӧ */
    stPrologueField.ucNAD = pucData[T1_NAD];
    stPrologueField.ucPCB = pucData[T1_PCB];
    stPrologueField.ucLen = pucData[T1_LEN];
    pucInformationData    = pucData + T1_INFO_START_BYTE;

    /* ��ȡ�����ͼ����� */
    USIMM_T1DLGetBlkType(stPrologueField.ucPCB, &stBlkPara);

    if (USIMM_T1_BLOCK_TYPE_I == stBlkPara.enBlockType)
    {
        /* ����������Ӧ��ֱ�ӷ�����ͬ�����󣬴˴�Э��û����ȷ�涨��δ��� */
        g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_RESYNCH_REQ;
        g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = VOS_NULL;
        g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = VOS_NULL;

        /* �ط��������������� */
        g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

        ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);

        /* ��ά�ɲ���Ϣͳ�� */
        g_stT1StatisticInfo.ulRcvAbnormalIBlkCnt++;
    }
    else if (USIMM_T1_BLOCK_TYPE_R == stBlkPara.enBlockType)
    {
        /* �ж��յ�������Ƿ�ͷ��������ͬ */
        /* ��ο��ƴ˴� �����ڴ˴���ѭ�� */
        if (stBlkPara.uBlockPara.stRBlockPara.ulSeqNum == g_stUsimmT1CtrlCtx.ulUESeqNum)
        {
            /* �ط�I BLOCK��Ƭ */
            ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.pucLastInfoData,
                                            g_stT1SendDataInfo.ulTotalLen - g_stT1SendDataInfo.ulLastTotalLen,
                                            g_stUsimmT1CtrlCtx.ulUESeqNum);

            /* ��ά�ɲ���Ϣͳ�� */
            g_stT1StatisticInfo.ulRcvTriggerResendRBlkCnt++;
        }
        else  /* �յ�������Ӧ */
        {
            /* �ط��������������� */
            g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

            /* ���鷢�͹����У��յ�������Ӧ�󣬷���������� */
            g_stUsimmT1CtrlCtx.ulUESeqNum = (g_stUsimmT1CtrlCtx.ulUESeqNum + 1) % 2;

            /* �����ѷ�������ָ�� */
            g_stT1SendDataInfo.pucLastInfoData += g_stT1SendDataInfo.ulLastLen;
            g_stT1SendDataInfo.ulLastTotalLen  += g_stT1SendDataInfo.ulLastLen;

            /* ������һ����Ƭ */
            ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.pucLastInfoData,
                                            g_stT1SendDataInfo.ulTotalLen - g_stT1SendDataInfo.ulLastTotalLen,
                                            g_stUsimmT1CtrlCtx.ulUESeqNum);
        }
    }
    else
    {
        /* �յ�S BLOCK */
        ulResult = USIMM_T1DLProcSBlock(stBlkPara.uBlockPara.stSBlockPara.enSBlkType, pucInformationData);
    }

    return ulResult;
}


VOS_UINT32 USIMM_T1DLProcSendSBlkReqState(
    VOS_BOOL        bValidFlag,
    VOS_UINT32      ulLength,
    VOS_UINT8      *pucData
)
{
    VOS_UINT32                          ulResult;
    USIMM_T1_BLOCK_PARA_STRU            stBlkPara;
    USIMM_T1_PROLOGUE_FIELD_STRU        stPrologueField;
    VOS_UINT8                          *pucInformationData;

    /* ����Ƿ��� */
    if (VOS_FALSE == bValidFlag)
    {
        /* ���·���S BLOCK */
        ulResult = USIMM_T1DLReSendSBlock();

        return ulResult;
    }

    /* ����������Ӧ */
    stPrologueField.ucNAD = pucData[T1_NAD];
    stPrologueField.ucPCB = pucData[T1_PCB];
    stPrologueField.ucLen = pucData[T1_LEN];
    pucInformationData    = pucData + T1_INFO_START_BYTE;

    /* ��ȡ�����ͼ����� */
    USIMM_T1DLGetBlkType(stPrologueField.ucPCB, &stBlkPara);

    if (USIMM_T1_BLOCK_TYPE_S == stBlkPara.enBlockType)
    {
        /* �����յ���S BLOCK */
        ulResult = USIMM_T1DLProcSBlock(stBlkPara.uBlockPara.stSBlockPara.enSBlkType, pucInformationData);
    }
    else
    {
        /* I BLOCK����R BLOCK���ط�S BLOCK */
        ulResult = USIMM_T1DLReSendSBlock();

        /* ��ά�ɲ���Ϣͳ�� */
        if (USIMM_T1_BLOCK_TYPE_R == stBlkPara.enBlockType)
        {
            g_stT1StatisticInfo.ulRcvAbnormalRBlkCnt++;
        }
        else
        {
            g_stT1StatisticInfo.ulRcvAbnormalIBlkCnt++;
        }

    }

    return ulResult;
}
static USIMMT1DL_RECV_FUNC_STATUS gastUSIMMT1DLRecvBlkProc[] =
{
    {USIMM_T1_PROC_STATE_IDLE,              USIMM_T1DLProcIdleState},
    {USIMM_T1_PROC_STATE_SENT_APDU,         USIMM_T1DLProcSendApduState},
    {USIMM_T1_PROC_STATE_SENT_CHAIN_APDU,   USIMM_T1DLProcSendChainApduState},
    {USIMM_T1_PROC_STATE_SENT_S_BLOCK_REQ,  USIMM_T1DLProcSendSBlkReqState},
};

VOS_UINT32 USIMM_T1DLProcessBlock(VOS_BOOL bValidFlag, VOS_UINT32 ulLength, VOS_UINT8 *pucData)
{
    VOS_UINT32      ulResult = VOS_ERR;
    VOS_UINT32      i;

    for (i = 0; i < ARRAYSIZE(gastUSIMMT1DLRecvBlkProc); i++)
    {
        if (g_stUsimmT1CtrlCtx.enT1ProcState == gastUSIMMT1DLRecvBlkProc[i].enStateId)
        {
            ulResult = gastUSIMMT1DLRecvBlkProc[i].pProcFun(bValidFlag, ulLength, pucData);

            break;
        }
    }

    return ulResult;
}


VOS_UINT32 USIMM_T1DLReceiveData(VOS_VOID)
{
    VOS_INT32       lSCIResult;
    VOS_UINT8       aucRecData[USIMM_T1_BLOCK_MAX_SIZE + 1] = {0};    /* ����һ�ֽڱ��� */
    VOS_UINT32      ulRecBlockLen = 0;
    VOS_BOOL        bBlockValidFlag;
    VOS_UINT32      ulResult;

    /* ���õ���ӿڽ������� */
    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_RCV);
    lSCIResult = mdrv_sci_rcv_blk(aucRecData, (VOS_UINT *)&ulRecBlockLen);
    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    if (USIMM_SCI_SUCCESS == lSCIResult)
    {
        /* ��ȡԭʼ���� */
        USIMM_SciDataHook(ulRecBlockLen, aucRecData);

        /* �ж����Ƿ�Ϸ� */
        bBlockValidFlag = USIMM_T1DLIsBlockValid(ulRecBlockLen, aucRecData);
    }
    else
    {
        /* ��ӡ���󣬵���api���ش��� or ��ʱ */
        bBlockValidFlag = VOS_FALSE;
    }

    ulResult = USIMM_T1DLProcessBlock(bBlockValidFlag, ulRecBlockLen, aucRecData);

    return ulResult;
}
VOS_UINT32 USIMM_T1DLCombineSendData(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32      ulResult = VOS_OK;

    switch (gstUSIMMDLControl.enCMDCase)
    {
        case USIMM_CMD_CASE1: /* case1 ֻ�����ֽ�apduͷ����û�з�������Ҳû����Ӧ���� */

            /* COPY APDU */
            /*lint -e534*/
            VOS_MemCpy(g_stT1SendDataInfo.aucInfoData, pstAPDUData->aucAPDU, T1_CASE1_APDU_LEN);
            /*lint +e534*/
            g_stT1SendDataInfo.ulTotalLen = T1_CASE1_APDU_LEN;

            break;

        case USIMM_CMD_CASE2: /* case2 û�з�����������Ӧ���ݻ��� */

            /* COPY APDU */
            /*lint -e534*/
            VOS_MemCpy(g_stT1SendDataInfo.aucInfoData, pstAPDUData->aucAPDU, USIMM_APDU_HEADLEN);
            /*lint +e534*/
            g_stT1SendDataInfo.ulTotalLen = USIMM_APDU_HEADLEN;
            break;

        case USIMM_CMD_CASE3: /* case3 �з�������û����Ӧ���ݻ��� */

            /* COPY APDU */
            /*lint -e534*/
            VOS_MemCpy(g_stT1SendDataInfo.aucInfoData, pstAPDUData->aucAPDU, USIMM_APDU_HEADLEN);

            /* copy �������� */
            VOS_MemCpy(g_stT1SendDataInfo.aucInfoData + USIMM_APDU_HEADLEN, pstAPDUData->aucSendBuf, pstAPDUData->ulLcValue);
            /*lint +e534*/

            /* ��ֵ���ͳ��� */
            g_stT1SendDataInfo.ulTotalLen = USIMM_APDU_HEADLEN + pstAPDUData->ulLcValue;
            break;

        case USIMM_CMD_CASE4: /* case4 ���з�������Ҳ����Ӧ���ݻ��� */

            /* COPY APDU */
            /*lint -e534*/
            VOS_MemCpy(g_stT1SendDataInfo.aucInfoData, pstAPDUData->aucAPDU, USIMM_APDU_HEADLEN);

            /* copy �������� */
            VOS_MemCpy(g_stT1SendDataInfo.aucInfoData + USIMM_APDU_HEADLEN, pstAPDUData->aucSendBuf, pstAPDUData->ulLcValue);
            /*lint +e534*/

            /* ��ֵLE�ֶ� */
            g_stT1SendDataInfo.aucInfoData[USIMM_APDU_HEADLEN + pstAPDUData->ulLcValue] = (VOS_UINT8)pstAPDUData->ulLeValue;

            /* ��ֵ���ͳ��� */
            g_stT1SendDataInfo.ulTotalLen = USIMM_APDU_HEADLEN + pstAPDUData->ulLcValue + 1;
            break;

        default:
            /* ������� */
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}


VOS_UINT32 USIMM_T1DLHandleIdleState(USIMM_APDU_ST* pstAPDUData)
{
    USIMM_ERROR_LOG("USIMM_T1DLHandleIdleState: Usimm T1 DL handle Run into Error State");

    return VOS_ERR;
}


VOS_UINT32 USIMM_T1DLHandleSendIFSState(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32      ulResult;

    g_stUsimmT1CtrlCtx.stSBlkPara.enSBlkType = USIMM_T1_S_BLOCK_IFS_REQ;
    g_stUsimmT1CtrlCtx.stSBlkPara.ucLen      = sizeof(VOS_UINT8);
    g_stUsimmT1CtrlCtx.stSBlkPara.ucData     = pstAPDUData->aucSendBuf[0];

    ulResult = USIMM_T1DLSendSBlock(&g_stUsimmT1CtrlCtx.stSBlkPara);

    /* ����ok�Ļ�ת�����տ�״̬ */
    if (VOS_OK == ulResult)
    {
        g_stUsimmT1CtrlCtx.enT1HandleState = USIMM_T1DL_HANDLE_STATE_RCV_BLOCK;
    }

    return ulResult;
}
VOS_UINT32 USIMM_T1DLHandleSendInfoState(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32      ulResult;

    ulResult = USIMM_T1DLCombineSendData(pstAPDUData);

    if (VOS_OK != ulResult)
    {
        return ulResult;
    }

    /* ȫ�ֱ�����ʼ�� */
    g_stT1SendDataInfo.pucLastInfoData = g_stT1SendDataInfo.aucInfoData;
    g_stT1SendDataInfo.ulLastLen       = 0;
    g_stT1SendDataInfo.ulLastTotalLen  = 0;

    /* ��ȡ���͵�APDU */
    USIMM_SciDataHook(g_stT1SendDataInfo.ulTotalLen, g_stT1SendDataInfo.aucInfoData);

    /* ����case��װ��Ϣ�������� */
    ulResult = USIMM_T1DLSendIBlock(g_stT1SendDataInfo.aucInfoData, g_stT1SendDataInfo.ulTotalLen, g_stUsimmT1CtrlCtx.ulUESeqNum);

    /* ����ok�Ļ�ת�����տ�״̬ */
    if (VOS_OK == ulResult)
    {
        g_stUsimmT1CtrlCtx.enT1HandleState = USIMM_T1DL_HANDLE_STATE_RCV_BLOCK;
    }

    return ulResult;
}


VOS_UINT32 USIMM_T1DLHandleRcvBlockState(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32      ulResult = VOS_ERR;

    while (USIMM_T1_PROC_STATE_IDLE != g_stUsimmT1CtrlCtx.enT1ProcState)
    {
        ulResult = USIMM_T1DLReceiveData();

        /* ���̳��ִ���,����ѭ�� */
        if (VOS_OK != ulResult)
        {
            break;
        }
    }

    return ulResult;
}
VOS_VOID USIMM_T1DLHandleStateStar(USIMM_APDU_ST* pstAPDUData)
{
    /* IFS REQ */
    if (VOS_TRUE == g_bSendIFSReqFlag)
    {
        /* ״̬Ǩ������IFS */
        g_stUsimmT1CtrlCtx.enT1HandleState = USIMM_T1DL_HANDLE_STATE_SEND_IFS;
    }
    else
    {
        /* ��������ȫ�ֱ������ */
        /*lint -e534*/
        VOS_MemSet(&g_stT1SendDataInfo, 0, sizeof(g_stT1SendDataInfo));

        VOS_MemSet(pstAPDUData->aucGetRepAPDU, 0, USIMM_APDU_HEADLEN);

        VOS_MemSet(&g_stT1RcvDataInfo, 0, sizeof(g_stT1RcvDataInfo));
        /*lint +e534*/

        /* ���·���һ������ʱ������������ */
        g_stUsimmT1CtrlCtx.ulUnexpectCount = 0;

        /* �ж�case */
        USIMM_DLJudgeCmdCase(pstAPDUData);

        /* ״̬Ǩ������ҵ������ */
        g_stUsimmT1CtrlCtx.enT1HandleState = USIMM_T1DL_HANDLE_STATE_SEND_INFO;
    }

    return;
}


static USIMMT1DL_HANDLE_FUNC_STATUS gastUSIMMT1DLHandleProc[] =
{
    {USIMM_T1DL_HANDLE_STATE_IDLE,              USIMM_T1DLHandleIdleState},
    {USIMM_T1DL_HANDLE_STATE_SEND_IFS,          USIMM_T1DLHandleSendIFSState},
    {USIMM_T1DL_HANDLE_STATE_SEND_INFO,         USIMM_T1DLHandleSendInfoState},
    {USIMM_T1DL_HANDLE_STATE_RCV_BLOCK,         USIMM_T1DLHandleRcvBlockState},
};

VOS_UINT32 USIMM_T1DLHandle(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32      ulResult = VOS_ERR;
    VOS_UINT32      i;

    if (USIMMDL_STATE_IDLE != g_stUsimmT1CtrlCtx.enT1HandleState)
    {
        USIMM_WARNING_LOG("USIMM_T0DLHandle: DL State is Wrong");/* ��ӡ���� */
    }

    USIMM_T1DLHandleStateStar(pstAPDUData);

    for (i = 0; i < ARRAYSIZE(gastUSIMMT1DLHandleProc); i++)
    {
        if (g_stUsimmT1CtrlCtx.enT1HandleState == gastUSIMMT1DLHandleProc[i].enStateId)
        {
            ulResult = gastUSIMMT1DLHandleProc[i].pProcFun(pstAPDUData);

            if (VOS_OK != ulResult)
            {
                break;
            }
        }
    }

    /* һ��״̬Ǩ��idle̬���Ա���һ�ι����������� */
    g_stUsimmT1CtrlCtx.enT1HandleState = USIMM_T1DL_HANDLE_STATE_IDLE;

    if (VOS_TRUE == g_bSendIFSReqFlag)
    {
        return ulResult;
    }

    /* �����������ֵ */
    if (VOS_OK == ulResult)
    {
        ulResult = USIMM_T1DLProcCardCmdRes(pstAPDUData);
    }

    return ulResult;
}
VOS_UINT32 USIMM_T1DLUpdateParaByATR(
    USIMM_T1_BLOCK_EPILOGUE_FIELD_ENUM_UINT32   enEDCType,
    VOS_UINT32                                  ulIFSC,
    VOS_UINT32                                  ulIFSD
)
{
    if ((ulIFSC > USIMM_T1_MAX_IFS) || (ulIFSC < USIMM_T1_MIN_IFS))
    {
        return VOS_ERR;
    }

    if ((ulIFSD > USIMM_T1_MAX_IFS) || (ulIFSD < USIMM_T1_MIN_IFS))
    {
        return VOS_ERR;
    }

    if (enEDCType >= USIMM_T1_BLOCK_EPILOGUE_FIELD_BUTT)
    {
        return VOS_ERR;
    }

    g_stUsimmT1CtrlCtx.enErrDetectMode = enEDCType;
    g_stUsimmT1CtrlCtx.ulIFSC = ulIFSC;
    g_stUsimmT1CtrlCtx.ulIFSD = ulIFSD;

    return VOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

