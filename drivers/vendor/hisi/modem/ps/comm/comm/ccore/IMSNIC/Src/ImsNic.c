/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ImsNic.c
  �� �� ��   : ����
  ��    ��   : caikai
  ��������   : 2013��7��22��
  ����޸�   :
  ��������   : VoLTE������IMS���������Ĵ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��22��
    ��    ��   : caikai
    �޸�����   : �����ļ�

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "IpsMntnCCore.h"

#if ( FEATURE_ON == FEATURE_IMS )
#include "mdrv.h"
#include <stdio.h>

#if ((VOS_OS_VER == VOS_WIN32) && (VOS_PC_TEST == VOS_RTOSCK))
#include "VxWorksStub.h"
#include "tcpip/public/tcpip_sock.h"
#elif (VOS_OS_VER == VOS_WIN32)
#include "VxWorksStub.h"
#elif (VOS_OS_VER == VOS_RTOSCK)
#include "v_sock.h"
#else
#include "muxLib.h"
#include "endLib.h"
#include "v_sock.h"
#endif

/*lint -e534*/
/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_IMS_NIC_C

#define         IMS_NIC_OK              (0)
#define         IMS_NIC_ERR             (1)
#define         IMS_NIC_ERROR           (-1)

/* ����ʱʹ�õĴ�ӡ���� */
VOS_UINT8       g_ucImsNicDebugPrint    = 0;

/* ���Դ�ӡ */
#define IMS_NIC_DEBUG_PRINT(...)\
        {\
            if ( 1 ==  g_ucImsNicDebugPrint)\
            {\
                (VOS_VOID)vos_printf(__VA_ARGS__);\
            }\
        }

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
IMS_NIC_ENTITY_STRU                     g_astImsNicEntity[IMS_NIC_MODEM_ID_BUTT] = {{0}};  /* IMS��������ʵ����Ϣ */

const IMS_NIC_MANAGE_TBL_STRU           g_stImsNicManageTbl    =
{
    "ims_nic0",
    {
        {
            {
                {
                    0x58, 0x02, 0x03, 0x04, 0x05, 0x06
                },
                {
                    0x00, 0x11, 0x09, 0x64, 0x01, 0x01
                },
                0x0008
            },
            {
                {
                    0x58, 0x02, 0x03, 0x04, 0x05, 0x06
                },
                {
                    0x00, 0x11, 0x09, 0x64, 0x01, 0x01
                },
                0xDD86
            }
        }
    }
};


IMS_NIC_CTX_STRU    g_stImsNicCtx   =
{
    IMS_NIC_MTU_DEFAULT_VALUE,
    0,
    0,
    {
        VOS_NULL_PTR
    }
};

IMS_NIC_DEV_STRU                        g_astImsNicDev[IMS_NIC_MODEM_ID_BUTT];                  /* ���������豸�ռ� */

/* DNSϵͳ������ */
VOS_CHAR                               *g_pcDnsSSysVarName[IMS_NIC_MAX_DNS_SERVER_NUM] =
{
        "ipdnsc.primaryns",
        "ipdnsc.secondaryns",
        "ipdnsc.tertiaryns",
        "ipdnsc.quaternaryns",
        "ipdnsc.quinaryns",
        "ipdnsc.senaryns"
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

#ifdef  ST_IMS_NIC
extern VOS_VOID  ST_IMS_NIC_InitQ(VOS_VOID);
extern VOS_UINT32  ST_IMS_NIC_PrintData( VOS_UINT8 *pData, VOS_UINT16 usLen );
#endif
VOS_VOID IMS_NIC_MNTN_InitLogCnt(IMS_NIC_LOG_ENT_STRU *pstLogEnt)
{
    if(VOS_OK != VOS_SmP(g_stImsNicCtx.ulInitLogMutexSem, 0))
    {
        return;
    }

    pstLogEnt->ulCnt = 0;

    (VOS_VOID)VOS_SmV(g_stImsNicCtx.ulInitLogMutexSem);

    return;
}


VOS_VOID IMS_NIC_MNTN_LogOutput(IMS_NIC_LOG_ENT_STRU *pstLogEnt, VOS_UINT32 ulPid)
{
    IMS_NIC_TRACE_LOG_MSG_STRU          stImsTraceLogMsg;


    /*  ����ݹ���ѭ�� */
    if( (pstLogEnt->ulCnt > IMS_NIC_LOG_RECORD_MAX_NUM) || (0 == pstLogEnt->ulCnt) )
    {
        IMS_NIC_MNTN_InitLogCnt(pstLogEnt);

        return;
    }

    stImsTraceLogMsg.ulSenderCpuId     = VOS_LOCAL_CPUID;
    stImsTraceLogMsg.ulSenderPid       = ulPid;
    stImsTraceLogMsg.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    stImsTraceLogMsg.ulReceiverPid     = ulPid;
    stImsTraceLogMsg.ulLength          = (sizeof(IMS_NIC_TRACE_LOG_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    stImsTraceLogMsg.usMsgType         = ID_IMS_NIC_MNTN_TRACE_LOG_MSG;
    stImsTraceLogMsg.usTransId         = 0;

    (VOS_VOID)mdrv_memcpy( &stImsTraceLogMsg.stLogMsgCont, pstLogEnt, sizeof(IMS_NIC_LOG_ENT_STRU) );

    DIAG_TraceReport(&stImsTraceLogMsg);

    IMS_NIC_MNTN_InitLogCnt(pstLogEnt);

    return ;
}
VOS_VOID IMS_NIC_MNTN_LogSave
(
    IMS_NIC_LOG_ENT_STRU           *pstLogEnt,
    VOS_UINT32                      ulPid,
    VOS_UINT32                      enLevel,
    PS_FILE_ID_DEFINE_ENUM_UINT32   enFile,
    VOS_UINT32                      ulLine,
    VOS_INT32                       lpara1,
    VOS_INT32                       lpara2,
    VOS_INT32                       lpara3,
    VOS_INT32                       lpara4
)
{
    VOS_UINT32      ulCnt;
    VOS_UINT32      ulCurrentSlice;

    ulCurrentSlice  = mdrv_timer_get_normal_timestamp();

    if(VOS_OK != VOS_SmP(g_stImsNicCtx.ulSaveLogMutexSem, 0))
    {
        return;
    }

    ulCnt           = pstLogEnt->ulCnt;

    if( ulCnt < IMS_NIC_LOG_RECORD_MAX_NUM )
    {
        pstLogEnt->astData[ulCnt].ulTick        = ulCurrentSlice;
        pstLogEnt->astData[ulCnt].enFile        = enFile;
        pstLogEnt->astData[ulCnt].ulLine        = ulLine;
        pstLogEnt->astData[ulCnt].enLevel       = enLevel;
        pstLogEnt->astData[ulCnt].alPara[0]     = lpara1;
        pstLogEnt->astData[ulCnt].alPara[1]     = lpara2;
        pstLogEnt->astData[ulCnt].alPara[2]     = lpara3;
        pstLogEnt->astData[ulCnt].alPara[3]     = lpara4;
        ulCnt++;
        pstLogEnt->ulCnt                        = ulCnt;
    }

    VOS_SmV(g_stImsNicCtx.ulSaveLogMutexSem);

    /* ��¼���ˣ��Զ����� */
    if( ulCnt >= IMS_NIC_LOG_RECORD_MAX_NUM )
    {
        IMS_NIC_MNTN_LogOutput(pstLogEnt, ulPid);
    }

    return;
}
VOS_VOID IMS_NIC_MntnTrace(VOS_UINT16 usMsgId, VOS_UINT8 *pucData, VOS_UINT32 ulLen, VOS_UINT32 ulPara1, VOS_UINT32 ulPara2)
{
    IMS_NIC_MNTN_TRACE_MSG_STRU *pstMntnTrace;
    VOS_UINT32                   ulMsgLen;


    ulMsgLen = IMS_NIC_MNTN_TRACE_DATA_OFFSET_LEN + ulLen;

    pstMntnTrace = (IMS_NIC_MNTN_TRACE_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_IMSNIC, ulMsgLen);

    if (VOS_NULL_PTR == pstMntnTrace)
    {
        IMS_NIC_WARNING_LOG(UEPS_PID_IMSNIC, "IMS_NIC_MntnTrace, WARNING, Alloc msg fail.");

        return;
    }

    pstMntnTrace->ulReceiverPid        = UEPS_PID_IMSNIC;
    pstMntnTrace->ulSenderPid          = UEPS_PID_IMSNIC;
    pstMntnTrace->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstMntnTrace->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstMntnTrace->ulLength             = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMntnTrace->usMsgId              = usMsgId;
    pstMntnTrace->ulPara1              = ulPara1;
    pstMntnTrace->ulPara2              = ulPara2;

    if (VOS_NULL_PTR != pucData)
    {
        (VOS_VOID)mdrv_memcpy(pstMntnTrace->aucData, pucData, ulLen);
    }

    DIAG_TraceReport(pstMntnTrace);

    PS_MEM_FREE(UEPS_PID_IMSNIC, pstMntnTrace);
}


VOS_UINT32 IMS_NIC_MNTN_LogEntInit(VOS_UINT32 ulPid)
{
    VOS_UINT32      ulResult;


    PS_MEM_SET(&g_stImsNicCtx.stLogEnt, 0, sizeof(IMS_NIC_LOG_ENT_STRU));

    ulResult    = VOS_SmMCreate("INIT", VOS_SEMA4_FIFO,
                    (VOS_SEM *)(&g_stImsNicCtx.ulInitLogMutexSem));

    if ( VOS_OK != ulResult )
    {
        IMS_NIC_INIT_LOG_PRINT1(ulPid, "IMS_NIC_MNTN_CreateMutexSem: Create g_ulInitLogMutexSem fail!", ulResult);

        return VOS_ERR;
    }

    ulResult    = VOS_SmMCreate("SAVE", VOS_SEMA4_FIFO,
                    (VOS_SEM *)(&g_stImsNicCtx.ulSaveLogMutexSem));

    if ( VOS_OK != ulResult )
    {
        IMS_NIC_INIT_LOG_PRINT1(ulPid, "IMS_NIC_MNTN_CreateMutexSem: Create g_ulLogSaveMutexSem fail!", ulResult);

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_I2A
 ��������  : ����ת������(10��16), ������ת��ΪASCII��, �����������ַ���
 �������  : usValue    - ��ת��ΪASCII�������
             pcStr      - ���������ַ���
             usRadix    - ת������
 �������  : ��
 �� �� ֵ  : VOS_CHAR*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_CHAR* IMS_NIC_I2A(VOS_UINT16 usValue, VOS_CHAR *pcStr, VOS_UINT16 usRadix)
{
    if (IMS_NIC_TYPE_HEX == usRadix)
    {
        pcStr += VOS_sprintf(pcStr, "%x", usValue);
    }
    else if(IMS_NIC_TYPE_DEC == usRadix)
    {
        pcStr += VOS_sprintf(pcStr, "%d", usValue);
    }
    else
    {
        IMS_NIC_WARNING_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_I2A, WARNING, usRadix is Invalid", usRadix);
    }

    return pcStr;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_FindIpv6AddrZeroFieldsToBeCompressed
 ��������  : �ҳ���Ҫʹ��"::"��ʾ��IP��ַ�ε���ʼλ��
 �������  : ausAddrValue[]     - IPV6��ַ������
             ucTokensNum        - ��ַ�θ���
 �������  : pucZeroFieldStart  - ��ֵ����Ϊ0��IP��ַ����ʼλ��
             pucZeroFieldCount  - ��ֵ����Ϊ0��IP��ַ�θ���
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMS_NIC_FindIpv6AddrZeroFieldsToBeCompressed(
    VOS_UINT8                          *pucZeroFieldStart,
    VOS_UINT8                          *pucZeroFieldCount,
    VOS_UINT16                         *pusAddrValue,
    VOS_UINT8                           ucTokensNum
)
{
    VOS_UINT32                          ulIndx;
    VOS_UINT8                           ucStart;
    VOS_UINT8                           ucCount;


    ucStart                             = 0xFF;
    ucCount                             = 0;

    for (ulIndx = 0; ulIndx < (VOS_UINT32)(ucTokensNum - 1); ulIndx++)
    {
        if ( (0x0000 == pusAddrValue[ulIndx])
          && (0x0000 == pusAddrValue[ulIndx + 1]) )
        {
            /* ��¼��ֵ����Ϊ0��IP��ַ����ʼλ�� */
            if (0xFF == ucStart)
            {
                ucStart = (VOS_UINT8)ulIndx;
            }

            /* ������ֵ����Ϊ0��IP��ַ�θ��� */
            ucCount++;
        }
        else
        {
            /* ���´�ѹ����IP��ַ��λ��, �Լ�IP��ַ�θ��� */
            if (0xFF != ucStart)
            {
                if (ucCount > *pucZeroFieldCount)
                {
                    *pucZeroFieldStart = ucStart;
                    *pucZeroFieldCount = ucCount;
                }

                ucStart = 0xFF;
                ucCount = 0;
            }
        }
    }

    /* ��ֵ����Ϊ0��IP��ַ���ڽ�βʱ, ��Ҫ����һ�δ�ѹ����IP��ַ��λ��,
       �Լ�IP��ַ�θ��� */
    if (0xFF != ucStart)
    {
        if (ucCount > *pucZeroFieldCount)
        {
            *pucZeroFieldStart = ucStart;
            *pucZeroFieldCount = ucCount;
        }
    }
}


/*****************************************************************************
 �� �� ��  : IMS_NIC_ConvertIpv6AddrToCompressedStr
 ��������  : ��IPV6��ַ��ʽת��Ϊ�ַ���ѹ����ʽ
 �������  : aucIpAddr[]    - IPV6��ַ(Э���ʽ)
             ucTokensNum    - ��ַ�θ���
 �������  : aucAddrStr[]   - IPV6��ַ(�ַ�����ʽ)
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMS_NIC_ConvertIpv6AddrToCompressedStr(
    VOS_UINT8                          *pucAddrStr,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT8                           ucTokensNum
)
{
    VOS_UINT8                          *pucBuffer;
    VOS_UINT32                          ulIndx;
    VOS_UINT16                          ausAddrValue[IMS_NIC_IPV6_STR_RFC2373_TOKENS]; /* IMS_NIC_IPV6_STR_RFC2373_TOKENS]; */
    VOS_UINT16                          usAddrNum;
    VOS_UINT8                           ucDelimiter;
    VOS_UINT8                           ucRadix;
    VOS_UINT8                           ucZeroFieldStart;
    VOS_UINT8                           ucZeroFieldCount;


    PS_MEM_SET(ausAddrValue, 0x00, sizeof(ausAddrValue));

    pucBuffer                           = pucAddrStr;
    ucDelimiter                         = IMS_NIC_IPV6_STR_DELIMITER;
    ucRadix                             = IMS_NIC_TYPE_HEX;
    ucZeroFieldStart                    = 0xFF;
    ucZeroFieldCount                    = 0;

    /* ����IP�ַ�����ʽ�������, ��ȡ�ֶε�IP��ַ��ֵ */
    for (ulIndx = 0; ulIndx < ucTokensNum; ulIndx++)
    {
        usAddrNum = *pucIpAddr++;

        usAddrNum <<= 8;
        usAddrNum  |= *pucIpAddr++;

        ausAddrValue[ulIndx] = usAddrNum;
    }

    /* �ҳ���Ҫʹ��"::"��ʾ��IP��ַ�ε���ʼλ��  */
    IMS_NIC_FindIpv6AddrZeroFieldsToBeCompressed(&ucZeroFieldStart, &ucZeroFieldCount, ausAddrValue, ucTokensNum);

    /* ����IP��ַ�ֶ�, �����зָ�����ǵ�IP��ַ�ַ��� */
    for (ulIndx = 0; ulIndx < ucTokensNum; ulIndx++)
    {
        if (ucZeroFieldStart == ulIndx)
        {
            *pucBuffer++ = ucDelimiter;

            ulIndx += ucZeroFieldCount;

            /* ����ѵ�IP��ַ�ֶε����һ��, ��Ҫ����ָ��� */
            if ((ucTokensNum - 1) == ulIndx)
            {
                *pucBuffer++ = ucDelimiter;
            }
        }
        else
        {
            /* �����IP��ַ�ֶεĵ�һ��, ����Ҫ����ָ��� */
            if (0 != ulIndx)
            {
                *pucBuffer++ = ucDelimiter;
            }

            pucBuffer    = (VOS_UINT8 *)IMS_NIC_I2A(ausAddrValue[ulIndx], (VOS_CHAR*)pucBuffer, ucRadix);
        }
    }

    /* �����ַ��������� */
    if (pucAddrStr != pucBuffer)
    {
        *pucBuffer = '\0';
    }
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_IsSameIpAddr
 ��������  : ����IPv4,IPv6��ַ�Ա�������ַ�Ƿ���ͬ
 �������  : pucIpAddr1            -- ��Ҫ�Ƚϵĵ�ַ1
             pucIpAddr2            -- ��Ҫ�Ƚϵĵ�ַ2
             ucIpAddrLen           -- IP��ַ����
 �������  : ��
 �� �� ֵ  : ��ȷ���1������ȷ���0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_IsSameIpAddr(VOS_UINT8 *pucIpAddr1, VOS_UINT8 *pucIpAddr2, VOS_UINT8 ucIpAddrLen)
{
    VOS_UINT32 *pulIpAddrTmp1 = (VOS_UINT32 *)pucIpAddr1;
    VOS_UINT32 *pulIpAddrTmp2 = (VOS_UINT32 *)pucIpAddr2;


    if ((VOS_NULL_PTR == pucIpAddr1) || (VOS_NULL_PTR == pucIpAddr2))
    {
        IMS_NIC_ERROR_LOG2(UEPS_PID_IMSNIC, "IMS_NIC_IsSameIpAddr, ERROR, Input para is NULL.", pucIpAddr1, pucIpAddr2);

        return 0;
    }

    if (IMS_NIC_IPV4_ADDR_LENGTH == ucIpAddrLen)
    {
        return (*(pulIpAddrTmp1) == *(pulIpAddrTmp2));
    }
    else
    {
        return !((pulIpAddrTmp1[0]^pulIpAddrTmp2[0]) | (pulIpAddrTmp1[1]^pulIpAddrTmp2[1])
        | (pulIpAddrTmp1[2]^pulIpAddrTmp2[2]) | (pulIpAddrTmp1[3]^pulIpAddrTmp2[3]));
    }
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_DnsAddrCheck
 ��������  : �������õ�DNS��������ַ�Ƿ��Ѿ����ù�
 �������  : pucIpAddr              -- �����õ�DNS������IP
             ulIpAddrLen            -- IP��ַ����
             pstImsNicDnsInfo       -- �ڲ��洢��DNS������Ϣ
 �������  : pucDnsIndx             -- ���ù��򷵻�DNS��������������û���ù��򷵻ؿ����õ�DNS������������
 �� �� ֵ  : ���ù�ΪVOS_TRUE��û�����ù�ΪVOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_DnsAddrCheck (VOS_UINT8 *pucIpAddr, VOS_UINT8 ucIpAddrLen, IMS_NIC_DNS_INFO_STRU *pstDnsInfo, VOS_UINT8 *pucDnsIndx)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           aucIdle[IMS_NIC_MAX_DNS_SERVER_NUM] = {0};
    VOS_UINT8                           ucIdleNum;


    ucIdleNum   = 0;

    if ((VOS_NULL_PTR == pucIpAddr) || (VOS_NULL_PTR == pucDnsIndx) || (VOS_NULL_PTR == pstDnsInfo))
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DnsAddrCheck, ERROR, Input para is NULL.");

        return IMS_NIC_DNS_NOT_CFGED;
    }

    /* ����pstDnsInfo�д洢��DNS��Ϣ */
    for (ucIndex = 0; ucIndex < IMS_NIC_MAX_DNS_SERVER_NUM; ucIndex++)
    {
        if ( pstDnsInfo->astImsNicDnsInfo[ucIndex].cDnsRef > 0)
        {
            if (pstDnsInfo->astImsNicDnsInfo[ucIndex].ucIpAddrLen == ucIpAddrLen)
            {
                /*  �Ƚ�pucIpAddr��pstDnsInfo->astImsNicDnsInfo[ucIndex].aucDnsAddr���ڴ�(����ucIpAddrLen) */
                if ( IMS_NIC_IsSameIpAddr(pucIpAddr, pstDnsInfo->astImsNicDnsInfo[ucIndex].aucDnsAddr, ucIpAddrLen) )
                {
                    /* ȡ��ǰ���� */
                    *pucDnsIndx  = ucIndex;

                    return IMS_NIC_DNS_CFGED;
                }
            }
        }
        else
        {
            /* ��¼��ǰ���е�DNS��� */
            aucIdle[ucIdleNum]   = ucIndex;
            ucIdleNum++;
        }
    }

    /* ȡ��һ���������� */
    *pucDnsIndx  = aucIdle[0];

    return IMS_NIC_DNS_NOT_CFGED;

}

/*****************************************************************************
 �� �� ��  : IMS_NIC_DnsConfig
 ��������  : ����DNS������
 �������  : pucIpAddr              -- �����õ�DNS������IP
             ulIpAddrLen            -- IP��ַ����
             pstImsNicDnsInfo       -- �ڲ��洢��DNS������Ϣ
             pstImsNicPdnInfo       -- �ڲ��洢�Ķ�Ӧ����������������������Ϣ
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��Ϊ��Ӧ�Ĵ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_DnsConfig (VOS_UINT8 *pucIpAddr, VOS_UINT8 ucIpAddrLen, IMS_NIC_DNS_INFO_STRU *pstDnsInfo, IMS_NIC_SINGLE_PDN_INFO_STRU *pstSinglePdnInfo)
{
    VOS_UINT8               ucDnsIndx;
    VOS_UINT32              ulResult;


    ucDnsIndx = 0;

    if (VOS_NULL_PTR == pucIpAddr)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DnsConfig, ERROR, pucIpAddr is Null Ptr.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    if (VOS_NULL_PTR == pstDnsInfo)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DnsConfig, ERROR, pstDnsInfo is Null Ptr.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    if (VOS_NULL_PTR == pstSinglePdnInfo)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DnsConfig, ERROR, pstSinglePdnInfo is Null Ptr.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    /* �жϵ�ǰ�����õ�DNS�������Ƿ��Ѿ����ù� */
    ulResult     = IMS_NIC_DnsAddrCheck(pucIpAddr, ucIpAddrLen, pstDnsInfo, &ucDnsIndx);

    /* ��DNS������û�����ù� */
    if ( IMS_NIC_DNS_CFGED != ulResult )
    {
        if ( pstDnsInfo->ucDnsServerCnt < IMS_NIC_MAX_DNS_SERVER_NUM )
        {
            IMS_NIC_DnsConfigtoIpStack(ucIpAddrLen, ucDnsIndx, pucIpAddr);

            (VOS_VOID)mdrv_memcpy(pstDnsInfo->astImsNicDnsInfo[ucDnsIndx].aucDnsAddr, pucIpAddr, ucIpAddrLen);
            pstDnsInfo->astImsNicDnsInfo[ucDnsIndx].ucIpAddrLen  = ucIpAddrLen;
            pstDnsInfo->ucDnsServerCnt++;
        }
        else
        {
            IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_DNS_SERVER_FULL, 1, IMS_NIC_MODEM_ID_0);

            return IMS_NIC_DNS_SERVER_FULL;
        }
    }

    /* ����������Ѿ����ù��������óɹ������ü��� */
    pstSinglePdnInfo->aucDnsFlag[ucDnsIndx]  = VOS_TRUE;

    /* ����DNS��������Ӧ�����ü�����1 */
    pstDnsInfo->astImsNicDnsInfo[ucDnsIndx].cDnsRef++;

    return IMS_NIC_SUCC;
}



VOS_UINT32 IMS_NIC_RecfgUncfgedDnsIpv4(IMS_NIC_SINGLE_PDN_INFO_STRU *pstSinglePdnInfo, IMS_NIC_DNS_INFO_STRU *pstDnsInfo)
{
    VOS_UINT32 ulRst;


    ulRst = IMS_NIC_SUCC;

    if (VOS_NULL_PTR == pstSinglePdnInfo || VOS_NULL_PTR == pstDnsInfo)
    {
        IMS_NIC_WARNING_LOG(UEPS_PID_IMSNIC, "IMS_NIC_RecfgUncfgedDns, ERROR, Input para is NULL.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    if ((VOS_TRUE == pstSinglePdnInfo->stIpv4PdnInfo.bitOpDnsPrim)
        && (VOS_FALSE == pstSinglePdnInfo->bitOpIpv4DnsPrimCfged))
    {
        /* ����DNS��Interpeak�� */
        ulRst = IMS_NIC_IPV4_DNS_CONFIG(pstSinglePdnInfo->stIpv4PdnInfo.aucDnsPrimAddr, pstDnsInfo, pstSinglePdnInfo);

        /* ���óɹ���ʾ��DNS�Ѿ������õ�Interpeak��,������ΪDNS�Ѿ�����������ǰDNSδ���õ�Interpeak */
        pstSinglePdnInfo->bitOpIpv4DnsPrimCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    if ((VOS_TRUE == pstSinglePdnInfo->stIpv4PdnInfo.bitOpDnsSec)
        && (VOS_FALSE == pstSinglePdnInfo->bitOpIpv4DnsSecCfged))
    {
        /* ����DNS��Interpeak�� */
        ulRst = IMS_NIC_IPV4_DNS_CONFIG(pstSinglePdnInfo->stIpv4PdnInfo.aucDnsSecAddr, pstDnsInfo, pstSinglePdnInfo);

        /* ���óɹ���ʾ��DNS�Ѿ������õ�Interpeak��,������ΪDNS�Ѿ�����������ǰDNSδ���õ�Interpeak */
        pstSinglePdnInfo->bitOpIpv4DnsSecCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    return ulRst;
}



VOS_UINT32 IMS_NIC_RecfgUncfgedDnsIpv6(IMS_NIC_SINGLE_PDN_INFO_STRU *pstSinglePdnInfo, IMS_NIC_DNS_INFO_STRU *pstDnsInfo)
{
    VOS_UINT32 ulRst;


    ulRst = IMS_NIC_SUCC;

    if (VOS_NULL_PTR == pstSinglePdnInfo || VOS_NULL_PTR == pstDnsInfo)
    {
        IMS_NIC_WARNING_LOG(UEPS_PID_IMSNIC, "IMS_NIC_RecfgUncfgedDns, ERROR, Input para is NULL.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    if ((VOS_TRUE == pstSinglePdnInfo->stIpv6PdnInfo.bitOpDnsPrim)
        && (VOS_FALSE == pstSinglePdnInfo->bitOpIpv6DnsPrimCfged))
    {
        /* ����DNS��Interpeak�� */
        ulRst = IMS_NIC_IPV6_DNS_CONFIG(pstSinglePdnInfo->stIpv6PdnInfo.aucDnsPrimAddr, pstDnsInfo, pstSinglePdnInfo);

        /* ���óɹ���ʾ��DNS�Ѿ������õ�Interpeak��,������ΪDNS�Ѿ�����������ǰDNSδ���õ�Interpeak */
        pstSinglePdnInfo->bitOpIpv6DnsPrimCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    if ((VOS_TRUE == pstSinglePdnInfo->stIpv6PdnInfo.bitOpDnsSec)
        && (VOS_FALSE == pstSinglePdnInfo->bitOpIpv6DnsSecCfged))
    {
        /* ����DNS��Interpeak�� */
        ulRst = IMS_NIC_IPV6_DNS_CONFIG(pstSinglePdnInfo->stIpv6PdnInfo.aucDnsSecAddr, pstDnsInfo, pstSinglePdnInfo);

        /* ���óɹ���ʾ��DNS�Ѿ������õ�Interpeak��,������ΪDNS�Ѿ�����������ǰDNSδ���õ�Interpeak */
        pstSinglePdnInfo->bitOpIpv6DnsSecCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    return ulRst;
}



VOS_VOID  IMS_NIC_RecfgUncfgedDns(IMS_NIC_PDN_INFO_STRU *pstPdnInfo)
{
    VOS_UINT32                      ulIndx;
    IMS_NIC_SINGLE_PDN_INFO_STRU   *pstSinglePdnInfo;


    if (VOS_NULL_PTR == pstPdnInfo)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_RecfgUncfgedDns, ERROR, Input para is NULL.");

        return;
    }

    for(ulIndx = 0; ulIndx < IMS_NIC_RAB_ID_MAX_NUM; ulIndx++)
    {
        pstSinglePdnInfo = &pstPdnInfo->astImsNicPdnInfo[ulIndx];

        if (VOS_TRUE == pstSinglePdnInfo->bitOpIpv4PdnInfo)
        {
            /* һ�����ɹ��Ͳ���������,�˳�ѭ�� */
            if (IMS_NIC_SUCC != IMS_NIC_RecfgUncfgedDnsIpv4(pstSinglePdnInfo, &pstPdnInfo->stImsNicDnsInfo))
            {
                break;
            }
        }

        if (VOS_TRUE == pstSinglePdnInfo->bitOpIpv6PdnInfo)
        {
            /* һ�����ɹ��Ͳ���������,�˳�ѭ�� */
            if (IMS_NIC_SUCC != IMS_NIC_RecfgUncfgedDnsIpv6(pstSinglePdnInfo, &pstPdnInfo->stImsNicDnsInfo))
            {
                break;
            }
        }
    }
}


VOS_VOID IMS_NIC_DnsInfoDel(IMS_NIC_PDN_INFO_STRU *pstPdnInfo, VOS_UINT8 ucRabId)
{
    VOS_UINT32                           ulIndx;
    IMS_NIC_SINGLE_PDN_INFO_STRU        *pstSinglePdnInfo;
    IMS_NIC_DNS_INFO_STRU               *pstDnsInfo;


    if (VOS_NULL_PTR == pstPdnInfo)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DnsInfoDel, ERROR, Input para is NULL.");

        return;
    }

    pstSinglePdnInfo = &(pstPdnInfo->astImsNicPdnInfo[ucRabId - IMS_NIC_RAB_ID_OFFSET]);
    pstDnsInfo       = &(pstPdnInfo->stImsNicDnsInfo);

    for (ulIndx = 0; ulIndx < IMS_NIC_MAX_DNS_SERVER_NUM; ulIndx++)
    {
        /* �ҵ���Ӧ��dns���� */
        if (VOS_TRUE == pstSinglePdnInfo->aucDnsFlag[ulIndx])
        {
            pstDnsInfo->astImsNicDnsInfo[ulIndx].cDnsRef--;
            pstSinglePdnInfo->aucDnsFlag[ulIndx]    = VOS_FALSE;

            /* �����ǰDNS�Ѿ�û�������ã���Interpeak��ɾ�� */
            if (0 >= pstDnsInfo->astImsNicDnsInfo[ulIndx].cDnsRef)
            {
                IMS_NIC_DnsDeltoIpStack(ulIndx, ucRabId, pstDnsInfo);

                PS_MEM_SET(&pstDnsInfo->astImsNicDnsInfo[ulIndx], 0, sizeof(IMS_NIC_SINGLE_DNS_INFO_STRU));
                pstDnsInfo->ucDnsServerCnt--;
            }
        }
    }

    /* ����д�Interpeak��ɾ��DNS Server������֮ǰ�����ÿ��Ƿ���δ���óɹ���DNS,�����䵽Interpeak�� */
    if (pstDnsInfo->ucDnsServerCnt < IMS_NIC_MAX_DNS_SERVER_NUM)
    {
        IMS_NIC_RecfgUncfgedDns(pstPdnInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_PdnInfoDel
 ��������  : IMS��������PDN������Ϣɾ������IMSAģ����PDNȥ��������
 �������  : ucRabId        ���غ�
             enModemId      ��ǰmodemID
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��Ϊ��Ӧ�Ĵ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_PdnInfoDel(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId)
{
    IMS_NIC_ENTITY_STRU                 *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU        *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU               *pstPdnInfo;


    IMS_NIC_MNTN_TRACE_NO_DATA(ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_DEL, enModemId, ucRabId);

    if ( enModemId >= IMS_NIC_MODEM_ID_BUTT )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_DEL_MODEM_ID_ERR, 1, IMS_NIC_MODEM_ID_0);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoDel, ERROR Input modem id invalid!\n", enModemId);

        return IMS_NIC_MODEM_ID_INVALID;
    }

    /* �����غ��Ƿ���Ч��ȡֵ��Χ[5, 15] */
    if ( !IMS_NIC_IS_RAB_VALID(ucRabId) )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_DEL_RAB_ID_ERR, 1, enModemId);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoDel, ERROR Input Rab id invalid!\n", ucRabId);

        return IMS_NIC_RABID_INVALID;
    }


    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);
    pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ucRabId - IMS_NIC_RAB_ID_OFFSET]);

    if (VOS_FALSE == (pstSinglePdnInfo->bitOpIpv4PdnInfo | pstSinglePdnInfo->bitOpIpv6PdnInfo))
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_DEL_NO_PDN, 1, enModemId);

        IMS_NIC_WARNING_LOG2(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoDel, ERROR No Cfged PDN!\n", enModemId, ucRabId);

        return IMS_NIC_NO_CFG_PDN;
    }

    if (0 >= pstPdnInfo->iPdnCfgCnt)
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_NO_CFGED_PDN, 1, enModemId);

        IMS_NIC_WARNING_LOG2(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoDel, ERROR Input Rab id invalid!\n", enModemId, ucRabId);

        /* �ó��������쳣����һ��״̬ */
        IMS_NIC_ResetAll(enModemId);

        return IMS_NIC_NO_CFG_PDN;
    }


    if ( VOS_TRUE == pstSinglePdnInfo->bitOpIpv4PdnInfo )
    {
       IMS_NIC_PdnInfoDelIpv4(ucRabId, enModemId);
    }

    if ( VOS_TRUE == pstSinglePdnInfo->bitOpIpv6PdnInfo )
    {
        IMS_NIC_PdnInfoDelIpv6(ucRabId, enModemId);
    }

    IMS_NIC_DnsInfoDel(pstPdnInfo, ucRabId);

    pstPdnInfo->iPdnCfgCnt--;

    if (0 >= pstPdnInfo->iPdnCfgCnt)
    {
        IMS_NIC_ResetAll(enModemId);
    }

    IMS_NIC_MNTN_TRACE2(ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_DEL_RSLT, pstPdnInfo, sizeof(IMS_NIC_PDN_INFO_STRU), enModemId, ucRabId);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_PdnInfoConfigIpv4
 ��������  : IMS��������IPv4���ýӿ�
 �������  : pstConfigInfo   IMS��������������Ϣ
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��Ϊ��Ӧ�Ĵ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_PdnInfoConfigIpv4(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo)
{
    VOS_UINT32                          ulRst;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU       *pstSinglePdnInfo;
    IMS_NIC_DNS_INFO_STRU              *pstDnsInfo;


    ulRst = IMS_NIC_SUCC;

    if (VOS_NULL_PTR == pstConfigInfo)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfigIpv4, ERROR, Input Null Ptr.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(pstConfigInfo->enModemId);
    pstSinglePdnInfo    = &(pstImsNicEntity->stImsNicPdnInfo.astImsNicPdnInfo[pstConfigInfo->ucRabId  - IMS_NIC_RAB_ID_OFFSET]);
    pstDnsInfo          = &(pstImsNicEntity->stImsNicPdnInfo.stImsNicDnsInfo);

    pstSinglePdnInfo->bitOpIpv4PdnInfo  = VOS_TRUE;
    (VOS_VOID)mdrv_memcpy(pstSinglePdnInfo->stIpv4PdnInfo.aucIpV4Addr, pstConfigInfo->stIpv4PdnInfo.aucIpV4Addr, IMS_NIC_IPV4_ADDR_LENGTH);

    /* ����ipv4���� */
    IMS_NIC_ConfigIpv4Addr(pstConfigInfo->enModemId, pstConfigInfo->stIpv4PdnInfo.aucIpV4Addr);

    if (VOS_TRUE == pstConfigInfo->stIpv4PdnInfo.bitOpDnsPrim)
    {
        /* ����DNS��ַ��Ϣ */
        (VOS_VOID)mdrv_memcpy(pstSinglePdnInfo->stIpv4PdnInfo.aucDnsPrimAddr, pstConfigInfo->stIpv4PdnInfo.aucDnsPrimAddr, IMS_NIC_IPV4_ADDR_LENGTH);
        pstSinglePdnInfo->stIpv4PdnInfo.bitOpDnsPrim = VOS_TRUE;

        /* ����DNS��Interpeak�� */
        ulRst = IMS_NIC_IPV4_DNS_CONFIG(pstConfigInfo->stIpv4PdnInfo.aucDnsPrimAddr, pstDnsInfo, pstSinglePdnInfo);

        /* ���óɹ���ʾ��DNS�Ѿ������õ�Interpeak��,������ΪDNS�Ѿ�����������ǰDNSδ���õ�Interpeak */
        pstSinglePdnInfo->bitOpIpv4DnsPrimCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    if (VOS_TRUE == pstConfigInfo->stIpv4PdnInfo.bitOpDnsSec)
    {
        /* ����DNS��ַ��Ϣ */
        (VOS_VOID)mdrv_memcpy(pstSinglePdnInfo->stIpv4PdnInfo.aucDnsSecAddr, pstConfigInfo->stIpv4PdnInfo.aucDnsSecAddr, IMS_NIC_IPV4_ADDR_LENGTH);
        pstSinglePdnInfo->stIpv4PdnInfo.bitOpDnsSec = VOS_TRUE;

        /* ����DNS��Interpeak�� */
        ulRst = IMS_NIC_IPV4_DNS_CONFIG(pstConfigInfo->stIpv4PdnInfo.aucDnsSecAddr, pstDnsInfo, pstSinglePdnInfo);

        /* ���óɹ���ʾ��DNS�Ѿ������õ�Interpeak��,������ΪDNS�Ѿ�����������ǰDNSδ���õ�Interpeak */
        pstSinglePdnInfo->bitOpIpv4DnsSecCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_PdnInfoConfigIpv6
 ��������  : IMS��������IPv6���ýӿ�
 �������  : pstConfigInfo   IMS��������������Ϣ
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��Ϊ��Ӧ�Ĵ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_PdnInfoConfigIpv6(IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo)
{
    VOS_UINT8                           aucIpAddrStr[IMS_NIC_IPV6_ADDR_STR_LEN + 1] = {0};
    VOS_UINT32                          ulRst;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU       *pstSinglePdnInfo;
    IMS_NIC_DNS_INFO_STRU              *pstDnsInfo;


    ulRst  = IMS_NIC_SUCC;

    if (VOS_NULL_PTR == pstConfigInfo)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfigIpv6, ERROR, Input Null Ptr.");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    if (pstConfigInfo->stIpv6PdnInfo.ulBitPrefixLen > IMS_NIC_IPV6_ADDR_BIT_LEN)
    {
        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfigIpv6, ERROR, Invalid Prefixlen.", pstConfigInfo->stIpv6PdnInfo.ulBitPrefixLen);

        IMS_NIC_STATS_INC(IMS_NIC_STATS_INVALID_IPV6_PREFIX_LEN, 1, pstConfigInfo->enModemId);

        return IMS_NIC_PREFIXLEN_INVALID;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(pstConfigInfo->enModemId);
    pstSinglePdnInfo    = &(pstImsNicEntity->stImsNicPdnInfo.astImsNicPdnInfo[pstConfigInfo->ucRabId  - IMS_NIC_RAB_ID_OFFSET]);
    pstDnsInfo          = &(pstImsNicEntity->stImsNicPdnInfo.stImsNicDnsInfo);

    pstSinglePdnInfo->bitOpIpv6PdnInfo  = VOS_TRUE;
    pstSinglePdnInfo->stIpv6PdnInfo.ulBitPrefixLen    = pstConfigInfo->stIpv6PdnInfo.ulBitPrefixLen;
    (VOS_VOID)mdrv_memcpy(pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr, pstConfigInfo->stIpv6PdnInfo.aucIpV6Addr, IMS_NIC_IPV6_ADDR_LENGTH);

    IMS_NIC_ConvertIpv6AddrToCompressedStr((VOS_UINT8 *)aucIpAddrStr, pstConfigInfo->stIpv6PdnInfo.aucIpV6Addr, IMS_NIC_IPV6_STR_RFC2373_TOKENS);

    /* ����ipv6���� */
    IMS_NIC_ConfigIpv6Addr(pstConfigInfo->enModemId, aucIpAddrStr, pstConfigInfo->stIpv6PdnInfo.ulBitPrefixLen);

    if (VOS_TRUE == pstConfigInfo->stIpv6PdnInfo.bitOpDnsPrim)
    {
        /* ����DNS��ַ��Ϣ */
        (VOS_VOID)mdrv_memcpy(pstSinglePdnInfo->stIpv6PdnInfo.aucDnsPrimAddr, pstConfigInfo->stIpv6PdnInfo.aucDnsPrimAddr, IMS_NIC_IPV6_ADDR_LENGTH);
        pstSinglePdnInfo->stIpv6PdnInfo.bitOpDnsPrim = VOS_TRUE;

        /* ������DNS��Interpeak�� */
        ulRst = IMS_NIC_IPV6_DNS_CONFIG(pstConfigInfo->stIpv6PdnInfo.aucDnsPrimAddr, pstDnsInfo, pstSinglePdnInfo);

        /* ���óɹ���ʾ��DNS�Ѿ������õ�Interpeak��,������ΪDNS�Ѿ�����������ǰDNSδ���õ�Interpeak */
        pstSinglePdnInfo->bitOpIpv6DnsPrimCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    if (VOS_TRUE == pstConfigInfo->stIpv6PdnInfo.bitOpDnsSec)
    {
        /* ����DNS��ַ��Ϣ */
        (VOS_VOID)mdrv_memcpy(pstSinglePdnInfo->stIpv6PdnInfo.aucDnsSecAddr, pstConfigInfo->stIpv6PdnInfo.aucDnsSecAddr, IMS_NIC_IPV6_ADDR_LENGTH);
        pstSinglePdnInfo->stIpv6PdnInfo.bitOpDnsSec = VOS_TRUE;

        /* ���ø�DNS��Interpeak�� */
        ulRst = IMS_NIC_IPV6_DNS_CONFIG(pstConfigInfo->stIpv6PdnInfo.aucDnsSecAddr, pstDnsInfo, pstSinglePdnInfo);

        /* ���óɹ���ʾ��DNS�Ѿ������õ�Interpeak��,������ΪDNS�Ѿ�����������ǰDNSδ���õ�Interpeak */
        pstSinglePdnInfo->bitOpIpv6DnsSecCfged = ((IMS_NIC_SUCC == ulRst) ? VOS_TRUE : VOS_FALSE);
    }

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_PdnInfoConfig
 ��������  : IMS�����������ýӿ�,��IMSAģ�����
 �������  : pstConfigInfo   IMS��������������Ϣ
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��Ϊ��Ӧ�Ĵ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_PdnInfoConfig (IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo)
{
    IMS_NIC_ENTITY_STRU                 *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU        *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU               *pstPdnInfo;
    VOS_UINT32                           ulResult;
    VOS_UINT32                           ulIsNewConfig;


    ulResult        = IMS_NIC_SUCC;
    ulIsNewConfig   = VOS_FALSE;

    if ( VOS_NULL_PTR == pstConfigInfo )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_INPUT_NULL_PTR, 1, IMS_NIC_MODEM_ID_0);

        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfig, ERROR, Input NULL PTR!");

        return IMS_NIC_CONFIG_PTR_NULL;
    }

    /* ��ά�ɲ� */
    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_INFO, pstConfigInfo, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    if ( pstConfigInfo->enModemId >= IMS_NIC_MODEM_ID_BUTT )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_ADD_RAB_ID_ERR, 1, IMS_NIC_MODEM_ID_0);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfig, ERROR, Input Modem id invalid!", pstConfigInfo->enModemId);

        return IMS_NIC_MODEM_ID_INVALID;
    }

    /* �����غ��Ƿ���Ч��ȡֵ��Χ[5, 15] */
    if ( !IMS_NIC_IS_RAB_VALID(pstConfigInfo->ucRabId) )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_ADD_MODEM_ID_ERR, 1, pstConfigInfo->enModemId);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfig, ERROR Input Rab id invalid!\n", pstConfigInfo->ucRabId);

        return IMS_NIC_RABID_INVALID;
    }

    if (VOS_FALSE == (pstConfigInfo->bitOpIpv4PdnInfo | pstConfigInfo->bitOpIpv6PdnInfo))
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CFG_ADD_NO_PDN, 1, pstConfigInfo->enModemId);

        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_PdnInfoConfig, ERROR No IPv4 and IPv6 info cfged!\n");

        return IMS_NIC_NO_CFG_PDN;
    }


    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(pstConfigInfo->enModemId);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);
    pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[pstConfigInfo->ucRabId - IMS_NIC_RAB_ID_OFFSET]);

    /* ��鵱ǰ�������Ƿ񻹴��ھɵ���Ч���� */
    if ( ((pstConfigInfo->bitOpIpv4PdnInfo) & (pstSinglePdnInfo->bitOpIpv4PdnInfo))
        | ((pstConfigInfo->bitOpIpv6PdnInfo) & (pstSinglePdnInfo->bitOpIpv6PdnInfo)))
    {
        /* ɾ���ó����ϵ����� */
        (VOS_VOID)IMS_NIC_PdnInfoDel(pstConfigInfo->ucRabId, pstConfigInfo->enModemId);
    }

    /* ������һ��PDN��ʱ�����ҪcfgCnt++��������Ҫ��ͨ�����ر����״̬ȷ�ϸ�rab���Ƿ��б����ù� */
    /* �ŵ�ɾ��֮�����жϣ����Ա�֤��rab�ϵ������Ǵ�������״̬ */
    if (VOS_FALSE == (pstSinglePdnInfo->bitOpIpv4PdnInfo | pstSinglePdnInfo->bitOpIpv6PdnInfo))
    {
        ulIsNewConfig = VOS_TRUE;
    }

    /* ����IPV4��� */
    if ( VOS_TRUE == pstConfigInfo->bitOpIpv4PdnInfo )
    {
        ulResult = IMS_NIC_PdnInfoConfigIpv4(pstConfigInfo);
    }

    /* ����IPV6��� */
    if ( VOS_TRUE == pstConfigInfo->bitOpIpv6PdnInfo )
    {
        ulResult |= IMS_NIC_PdnInfoConfigIpv6(pstConfigInfo);
    }

    if (0 == pstImsNicEntity->stImsNicPdnInfo.iPdnCfgCnt)
    {
        /* ����Ĭ��·�� */
        IMS_NIC_SetDefaultRoute(pstConfigInfo->enModemId);

        /* �˿����ƽ���������һ�μ���ʱ����һ�Σ���������ɾ������ */
        if (VOS_TRUE == pstConfigInfo->bitOpSockPortInfo)
        {
            /* ����Socket�˿� */
            ulResult |= IMS_NIC_SetSocketPort(pstConfigInfo->stSockPortInfo.usSockMinPort,
                pstConfigInfo->stSockPortInfo.usSockMaxPort, pstConfigInfo->enModemId);
        }
    }

    if (VOS_TRUE == ulIsNewConfig)
    {
        pstPdnInfo->iPdnCfgCnt++;
    }

    /* ǰ��Ŀ�ά�ɲ���ץ���ⲿ������Ϣ������ץȡ��ģ��ά����״̬��Ϣ */
    IMS_NIC_MNTN_TRACE2(ID_IMS_NIC_MNTN_TRACE_CONFIG_PROC_RSLT, pstPdnInfo, sizeof(IMS_NIC_PDN_INFO_STRU), ulResult, ulIsNewConfig);

    return ulResult;
}


/*****************************************************************************
 �� �� ��  : IMS_NIC_RegUlDataSendCb
 ��������  : ע��IMS���������������ݷ��ͻص���������CDSģ�����
 �������  : pFunc        �������ݷ��ͻص��ӿ�
             enModemId    ��ǰmodemID
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��:IMS_NIC_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_RegUlDataSendCb(IMS_NIC_SEND_UL_DATA_FUNC pFunc, MODEM_ID_ENUM_UINT16 enModemId)
{
    IMS_NIC_ENTITY_STRU     *pstImsNicEntity;


    if ( enModemId >= IMS_NIC_MODEM_ID_BUTT )
    {
        /* Ĭ�ϼ�¼��Modem0��ʵ���� */;
        IMS_NIC_STATS_INC(IMS_NIC_STATS_MODEM_ID_ERR_IN_REG_CB, 1, IMS_NIC_MODEM_ID_0);

        return IMS_NIC_MODEM_ID_INVALID;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);

    /* ����������û�г�ʼ�� */
    if ( VOS_TRUE != pstImsNicEntity->ulImsNicInitFlag )
    {
        IMS_NIC_SAVE_UL_DATA_FUNC(enModemId, pFunc);
    }
    else
    {
        pstImsNicEntity->pUlDataSendFunc = pFunc;
    }

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_DlParaCheck
 ��������  : IMS���������������ݽ��ղ������
 �������  : pucData      IP������
             usLen        IP������
             enModemId    ��ǰmodemID
 �������  :
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��:IMS_NIC_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_DlParaCheck(VOS_UINT8 *pucData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId)
{

    if ( enModemId >= IMS_NIC_MODEM_ID_BUTT )
    {
        /* Ĭ�ϼ�¼��Modem0��ʵ���� */;
        IMS_NIC_STATS_INC(IMS_NIC_STATS_MODE_ID_ERR_IN_DL_PROC, 1, IMS_NIC_MODEM_ID_0);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_DlParaCheck, ERROR, Input modem id invalid!\n", enModemId);

        return IMS_NIC_FAIL;
    }

    if ( VOS_NULL_PTR == pucData )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_INPUT_NULL_PTR, 1, enModemId);

        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DlParaCheck, ERROR, input pucData is NULL!\n");

        return IMS_NIC_FAIL;
    }

    /* usLenֵ������Чֵ��Χ�� */
    if ( (usLen < IMS_NIC_MIN_IPPKT_LEN) || (usLen > IMS_NIC_MAX_IPPKT_LEN))
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_RCV_DATA_LEN_ERR, 1, enModemId);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_DlParaCheck, ERROR, usLen is invalid! usLen = %d\n", usLen);

        return IMS_NIC_FAIL;
    }

    return IMS_NIC_SUCC;

}


/*****************************************************************************
 �� �� ��  : IMS_NIC_UlDataSend
 ��������  : �ú�������MUX����������ݽ���CDS
 �������  : pucData      IP������
             usLen        IP������
             enModemId    ��ǰmodemID
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��ΪIMS_NIC_FAIL
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_UlDataSend(VOS_UINT8 *pucData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId)
{
    IMS_NIC_ENTITY_STRU                     *pstImsNicEntity;
    IMS_NIC_ETH_HEADER_STRU                 *pstEthHdr;
    VOS_UINT8                               *pucIpData;
    VOS_UINT16                               usIpDataLen;
    VOS_UINT32                               ulResult;
    VOS_UINT16                               usEtherType;

    /* ����ָ��Ϊ�� */
    if ( VOS_NULL_PTR == pucData )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_INPUT_NULL_PTR, 1, enModemId);

        IMS_NIC_ERROR_LOG_MSG(UEPS_PID_IMSNIC, "IMS_NIC_UlDataSend, ERROR, Input data is NULL!\n");

        return IMS_NIC_FAIL;
    }

    /* ���ݱ��ĳ��Ȳ�����Чֵ��Χ�ڣ���[MIN + OFFSET, MTU + OFFSET],
        ����MINΪ��СIP����С��OFFSETΪ14���ֽ�(14�ֽ���̫����ͷ����) */
    if ( (usLen < (IMS_NIC_MIN_IPPKT_LEN + IMS_NIC_ETH_HDR_SIZE)) ||
        (usLen > (IMS_NIC_GET_MTU + IMS_NIC_ETH_HDR_SIZE)) )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_DATA_LEN_ERR, 1, enModemId);

        IMS_NIC_ERROR_LOG_MSG2(UEPS_PID_IMSNIC, "IMS_NIC_UlDataSend, ERROR, Input data len =%d mtu = %d is invalid!\n", (VOS_INT32)usLen, (VOS_INT32)IMS_NIC_GET_MTU);

        return IMS_NIC_FAIL;
    }

    pstEthHdr   = (IMS_NIC_ETH_HEADER_STRU *)pucData;

    /* ������ת��Ϊ������ */
    usEtherType   = VOS_NTOHS(pstEthHdr->usEtherType);

    switch (usEtherType)
    {
        case IMS_NIC_ETHERTYPE_IPV4:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_IPV4_PKT, 1, enModemId);
            break;

        case IMS_NIC_ETHERTYPE_IPV6:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_IPV6_PKT, 1, enModemId);
            break;

        /* ��������ΪNOARP, �յ�ARP�������еݽ���ֱ�ӷ��� */
        case IMS_NIC_ETHERTYPE_ARP:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_ARP_PKT, 1, enModemId);
            return IMS_NIC_SUCC;

        default:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_ERR_PKT, 1, enModemId);
            IMS_NIC_ERROR_LOG_MSG1(UEPS_PID_IMSNIC, "IMS_NIC_UlDataSend, ERROR, receive err pkt, the usEthType = 0x%x!\n", (VOS_INT32)usEtherType);
            return IMS_NIC_FAIL;
    }

    /* ����MACͷ��ƫ�Ƶ�ַ */
    pucIpData           = pucData + IMS_NIC_ETH_HDR_SIZE;
    usIpDataLen         = usLen - IMS_NIC_ETH_HDR_SIZE;

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);
    if ( VOS_NULL_PTR   == pstImsNicEntity->pUlDataSendFunc )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_CB_FUN_NOT_REG, 1, enModemId);

        IMS_NIC_ERROR_LOG_MSG(UEPS_PID_IMSNIC, "IMS_NIC_UlDataSend, pUlDataSendFunc is NULL!\n");

        return IMS_NIC_FAIL;
    }

    /* ����CDSע����������ݷ��ͺ��� */
    ulResult    = pstImsNicEntity->pUlDataSendFunc(pucIpData, usIpDataLen, enModemId);
    if( IMS_NIC_SUCC != ulResult )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_CALL_CB_FUN_FAIL, 1, enModemId);

        IMS_NIC_ERROR_LOG_MSG(UEPS_PID_IMSNIC, "IMS_NIC_UlDataSend, ERROR, call pUlDataSendFunc fail!\n");

        return IMS_NIC_FAIL;
    }

    /* ���з�������ͳ�� */
    IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_SEND_PKT, 1, enModemId);

    /* ���������������ݷ����ֽ��� */
    IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_SEND_BYTES, usIpDataLen, enModemId);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_InitAll
 ��������  : ��ʼ�����е�IMS��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��ΪIMS_NIC_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_InitAll(VOS_VOID)
{
    VOS_UINT32      ulResult;
    VOS_UINT16      usIndex;


    if (VOS_OK != IMS_NIC_MNTN_LogEntInit(UEPS_PID_IMSNIC))
    {
        IMS_NIC_INIT_LOG_PRINT(UEPS_PID_IMSNIC, "IMS_NIC_InitAll, ERROR, muxDevStart failed! iResult = %d\n");

        return IMS_NIC_FAIL;
    }

    /* ��ʼ��IMS�������� */
    for (usIndex = 0 ; usIndex < IMS_NIC_MODEM_ID_BUTT ; usIndex++)
    {
        ulResult    = IMS_NIC_Init(usIndex);
        if ( IMS_NIC_SUCC != ulResult )
        {
            /* ��ӡ��ulResult��ֵ */
            IMS_NIC_INIT_LOG_PRINT2(UEPS_PID_IMSNIC, "IMS_NIC_InitAll, ERROR, IMS_NIC_Init Failed, usIndex=%d, ulResult=0x%x\n", usIndex, ulResult);
            return IMS_NIC_FAIL;
        }
    }

#ifdef  ST_IMS_NIC
    ST_IMS_NIC_InitQ();
#endif

    return IMS_NIC_SUCC;
}


VOS_UINT32 IMS_NIC_Addr_Util_GetUnsetBitsInByte(VOS_UINT8 ucAddressByte, VOS_UINT32 *pulLeftUnsetBits)
{
    VOS_UINT32  ulLoopIndex;
    VOS_UINT32  ulCountBits = 0;
    VOS_UINT8   ucAddrByteComplement;
    VOS_UINT8   ucMask = 0x80;

    /* Complement the Byte so that all 0s are converted to 1's and Vice-Versa */
    ucAddrByteComplement = (VOS_UINT8)(~(ucAddressByte));

    for (ulLoopIndex = 0; ulLoopIndex < 8; ulLoopIndex++)
    {
        /* If the result of AND operation between the Mask and the Complemented
           byte is Non-Zero then the count has to be Incremented */
        if (ucMask & ucAddrByteComplement)
        {
            ulCountBits++;
        }
        else
        {
            break;
        }

        /* Right Shift the Mask by 1 */
        ucMask = (VOS_UINT8)(ucMask >> 1);
    }

    *pulLeftUnsetBits = ulCountBits;

    return ADDRADP_OK;
}
VOS_UINT32 IMS_NIC_Addr_Util_GetNumOfMatchingBits(const IN6ADDR_S *pstIP6Addr1,
                                         const IN6ADDR_S *pstIP6Addr2,
                                         VOS_UINT32 *pulMatchBitsNum)
{
    IN6ADDR_S       stXoredPattern;
    VOS_UINT32      ulMatchBitsCount = 0;
    VOS_UINT32      ulLoopIndex;
    VOS_UINT32      ulLoopIndex1;
    VOS_UINT8       ucAddrPos = 0;
    VOS_UINT32      ulLeftUnsetBits = 0;

    IMS_NIC_IP6_ADDR_XOR_ADDRESSES(pstIP6Addr1, pstIP6Addr2, stXoredPattern)

    for (ulLoopIndex = 0; ulLoopIndex < 4; ulLoopIndex++)
    {
        if (0 == stXoredPattern.s6_addr32[ulLoopIndex])
        {
            /* Since the complete VOS_UINT32 value is Zero, so increase the number
               of matching bits by 32 */
            ulMatchBitsCount += 32;
        }
        else
        {
            /* The following part of code finds Leftmost Unset bits in a
               VOS_UINT32 */
            for (ulLoopIndex1 = (ulLoopIndex * 4);
                 (0 == (ucAddrPos = stXoredPattern.s6_addr8[ulLoopIndex1]));
                 ulLoopIndex1++)
            {
                ulMatchBitsCount += 8;
            }

            (VOS_VOID)IMS_NIC_Addr_Util_GetUnsetBitsInByte(ucAddrPos, &ulLeftUnsetBits);
            ulMatchBitsCount += ulLeftUnsetBits;

            /* Since Number of matching bits are computed so break and return
              the number of matching bits to the caller */
            break;
        }
    }

    *pulMatchBitsNum = ulMatchBitsCount;

    return ADDRADP_OK;
}


ULONG IMS_NIC_MatchSrcAddr(TCPIP_ADDR_INFO_S *pstMatchSrcAddr)
{
    VOS_UINT32                          ulCount;
    VOS_UINT32                          ulMatchBitsNum;
    VOS_UINT32                          ulSrcAddrBitsMatch          = 0;
    IN6ADDR_S                           *pstIp6CurIfAddrSel         = VOS_NULL;
    IMS_NIC_ENTITY_STRU                 *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU        *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU               *pstPdnInfo;

    /*Ŀ�ĵ�ַΪ0,linklocal,�ಥ��ַ����ǰ��֧�֣������г�����֧�֣��˴��ſ�*/
    if ( IMS_NIC_IN6_IS_LINKLOCAL(&pstMatchSrcAddr->stDestAddr) ||
         IMS_NIC_IN6_IS_MULTICAST(&pstMatchSrcAddr->stDestAddr) ||
         IMS_NIC_IN6_IS_UNSPECIFIED(&pstMatchSrcAddr->stDestAddr) )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_MATCH_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);
        return ADDRADP_ERR;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(IMS_NIC_MODEM_ID_0);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);

    /*����������Ҫ��������*/
    for (ulCount = 0; ulCount < IMS_NIC_RAB_ID_MAX_NUM; ulCount++)
    {
        pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ulCount]);

        if (VOS_FALSE == pstSinglePdnInfo->bitOpIpv6PdnInfo)
        {
            continue;
        }

        ulMatchBitsNum      = 0;
        (VOS_VOID)IMS_NIC_Addr_Util_GetNumOfMatchingBits(
                                        (const IN6ADDR_S *)pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr,
                                        (const IN6ADDR_S *)&pstMatchSrcAddr->stDestAddr,
                                        &ulMatchBitsNum);

        if (ulMatchBitsNum > ulSrcAddrBitsMatch)
        {
            ulSrcAddrBitsMatch = ulMatchBitsNum;
            pstIp6CurIfAddrSel = (IN6ADDR_S *)pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr;
        }
    }

    if (VOS_NULL != pstIp6CurIfAddrSel)
    {
        PS_MEM_CPY(&pstMatchSrcAddr->stSrcAddr, pstIp6CurIfAddrSel, sizeof(IN6ADDR_S));

        IMS_NIC_STATS_INC(IMS_NIC_STATS_MATCH_IPV6_ADDR_SUCC, 1, IMS_NIC_MODEM_ID_0);

        return ADDRADP_OK;
    }

    IMS_NIC_STATS_INC(IMS_NIC_STATS_MATCH_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);

    return ADDRADP_ERR;
}


ULONG IMS_NIC_IsLocalAddr(TCPIP_ADDR_INFO_S *pstMatchSrcAddr)
{
    VOS_UINT32                          ulCount;
    IMS_NIC_ENTITY_STRU                 *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU        *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU               *pstPdnInfo;

    /*Ŀ�ĵ�ַΪ0,linklocal,�ಥ��ַ����ǰ��֧�֣������г�����֧�֣��˴��ſ�*/
    if ( IMS_NIC_IN6_IS_LINKLOCAL(&pstMatchSrcAddr->stDestAddr) ||
         IMS_NIC_IN6_IS_MULTICAST(&pstMatchSrcAddr->stDestAddr) ||
         IMS_NIC_IN6_IS_UNSPECIFIED(&pstMatchSrcAddr->stDestAddr) )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_MATCH_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);
        return ADDRADP_ERR;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(IMS_NIC_MODEM_ID_0);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);

    if (pstMatchSrcAddr->ulIfIndex)
    {
        if (pstImsNicEntity->ulIfIndex != pstMatchSrcAddr->ulIfIndex)
        {
            IMS_NIC_STATS_INC(IMS_NIC_STATS_LOCAL_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);

            return ADDRADP_ERR;
        }

        for (ulCount = 0; ulCount < IMS_NIC_RAB_ID_MAX_NUM; ulCount++)
        {
            pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ulCount]);

            if (VOS_FALSE == pstSinglePdnInfo->bitOpIpv6PdnInfo)
            {
                continue;
            }

            if (0 == PS_MEM_CMP(&pstMatchSrcAddr->stDestAddr, pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr, sizeof(IN6ADDR_S)))
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_LOCAL_IPV6_ADDR_SUCC, 1, IMS_NIC_MODEM_ID_0);

                return ADDRADP_OK;
            }
        }
    }
    else
    {
        /*����������Ҫ��������*/

        for (ulCount = 0; ulCount < IMS_NIC_RAB_ID_MAX_NUM; ulCount++)
        {
            pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ulCount]);

            if (VOS_FALSE == pstSinglePdnInfo->bitOpIpv6PdnInfo)
            {
                continue;
            }

            if (0 == PS_MEM_CMP(&pstMatchSrcAddr->stDestAddr, pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr, sizeof(IN6ADDR_S)))
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_LOCAL_IPV6_ADDR_SUCC, 1, IMS_NIC_MODEM_ID_0);

                return ADDRADP_OK;
            }
        }
    }

    IMS_NIC_STATS_INC(IMS_NIC_STATS_LOCAL_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);

    return ADDRADP_ERR;
}


ULONG IMS_NIC_HaveAddrCheck(TCPIP_ADDR_INFO_S *pstMatchSrcAddr)
{
    VOS_UINT32                          ulCount;
    IN6ADDR_S                           stZeroAddr;
    IMS_NIC_ENTITY_STRU                 *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU        *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU               *pstPdnInfo;

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(IMS_NIC_MODEM_ID_0);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);

    PS_MEM_SET(&stZeroAddr, 0, sizeof(IN6ADDR_S));

    if (pstImsNicEntity->ulIfIndex != pstMatchSrcAddr->ulIfIndex)
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_HAVE_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);

        return ADDRADP_ERR;
    }

    /* �ӿ��Ƿ����linklocal��ַcheck */
    if (TCPIP_ADDR_LINKLOCAL_FLAG == pstMatchSrcAddr->ulFlag)
    {
        if (0 != PS_MEM_CMP(pstImsNicEntity->aucIpV6LinkLocalAddr, &stZeroAddr, sizeof(IN6ADDR_S)))
        {
            IMS_NIC_STATS_INC(IMS_NIC_STATS_HAVE_IPV6_ADDR_SUCC, 1, IMS_NIC_MODEM_ID_0);

            return ADDRADP_OK;
        }
    }
    else
    {
        for (ulCount = 0; ulCount < IMS_NIC_RAB_ID_MAX_NUM; ulCount++)
        {
            pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ulCount]);

            if (VOS_FALSE == pstSinglePdnInfo->bitOpIpv6PdnInfo)
            {
                continue;
            }

            if (0 != PS_MEM_CMP(pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr, &stZeroAddr, sizeof(IN6ADDR_S)))
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_HAVE_IPV6_ADDR_SUCC, 1, IMS_NIC_MODEM_ID_0);

                return ADDRADP_OK;
            }
        }
    }

    IMS_NIC_STATS_INC(IMS_NIC_STATS_HAVE_IPV6_ADDR_FAIL, 1, IMS_NIC_MODEM_ID_0);

    return ADDRADP_ERR;
}
VOS_VOID IMS_NIC_SetLinklocalAddr(IN6ADDR_S *pstLinkLocalAddr, VOS_UINT8 *pData)
{
    VOS_UINT8               ucInterfaceID[8];   /* �ӿ�ID */
    IMS_NIC_INTERFACEID_S   stInterfaceId;

    (VOS_VOID)PS_MEM_SET((VOS_UINT8 *)&stInterfaceId, 0, sizeof(IMS_NIC_INTERFACEID_S));
    IMS_NIC_MAP_MAC_INTERFACEID((VOS_UINT8 *)pData, (VOS_UINT8 *)ucInterfaceID);

    (VOS_VOID)PS_MEM_CPY((VOS_UINT8 *)&stInterfaceId, ucInterfaceID, 8);

    pstLinkLocalAddr->s6_addr8[0]   = 0xfe;
    pstLinkLocalAddr->s6_addr8[1]   = 0x80;
    pstLinkLocalAddr->s6_addr16[1]  = 0;
    pstLinkLocalAddr->s6_addr32[1]  = 0;
    pstLinkLocalAddr->s6_addr32[2]  = stInterfaceId.ip6_ifid32[0];
    pstLinkLocalAddr->s6_addr32[3]  = stInterfaceId.ip6_ifid32[1];

    return;
}

/*****************************************************************************
 �ṹ��    : stAddrHook
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���ڵ�ַѡ��
*****************************************************************************/
TCPIP_ADDR_HOOK_S stAddrHook =
{
    IMS_NIC_MatchSrcAddr,
    IMS_NIC_IsLocalAddr,
    IMS_NIC_HaveAddrCheck
};


VOS_VOID   IMS_NIC_ConfigIpv6Addr
(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT32                          ulBitPrefixLen
)
{
    VOS_INT8                            aucIfName[IMS_NIC_TCPIP_INPUT_LEN]   = {0};
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN];
    VOS_UINT32                          ulRet;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;

    /* �ⲿ�Ѽ��ָ��ǿ� */
    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);

    ulRet = TCPIP_GetFullNameByIfIndex(pstImsNicEntity->ulIfIndex, (CHAR *)aucIfName);
    if ( VOS_OK != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_GET_IF_NAME_BY_INDEX_FAIL, 1, enModemId);

        /* ��ά�ɲ� */
        PS_MEM_SET(aucInput, 0, sizeof(aucInput));

        (VOS_VOID)IMS_NIC_TCPIP_INPUT_STR_LOG2(aucInput, TCPIP_GetFullNameByIfIndex,
            pstImsNicEntity->ulIfIndex, aucIfName, ulRet);

        IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

        return;
    }

    ulRet             = TCPIP_ShutDownIf(pstImsNicEntity->ulIfIndex);
    if ( (VRP_IFNET_NOERR != ulRet) && (VRP_IFNET_NO_HAVE_BEEN_DOWN != ulRet))
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_RESUME_IF_FAIL, 1, enModemId);
    }

    ulRet             = TCPIP_ResumeIf(pstImsNicEntity->ulIfIndex);
    if ( (VRP_IFNET_NOERR != ulRet) && (VRP_IFNET_NO_HAVE_BEEN_DOWN != ulRet))
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_RESUME_IF_FAIL, 1, enModemId);
    }

    PS_MEM_SET(aucInput, 0, sizeof(aucInput));

    /* ��ά�ɲ� */
    IMS_NIC_TCPIP_INPUT_STR_LOG4(aucInput, IMS_NIC_ConfigIpv6Addr,
        aucIfName, pucIpAddr, IMS_NIC_DEFAULT_IPV6_MASK_LEN, IMS_NIC_TCPIP_GLOBAL_ADDR_FLAG, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    return;
}
VOS_VOID   IMS_NIC_ConfigIpv4Addr(MODEM_ID_ENUM_UINT16 enModemId, VOS_UINT8 *pucIpAddr)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIpAddr;
    VOS_UINT32                          ulMask;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN];


    /* �ⲿ�Ѽ��ָ��ǿ� */

    ulIpAddr        = vrp_ntohl(*(VOS_UINT32 *)pucIpAddr);
    ulMask          = IMS_NIC_TCPIP_DEFAULT_SUBNET_MASK;
    pstImsNicEntity = IMS_NIC_GET_ENTITY_STRU(enModemId);

    ulRet           = TCPIP_ResumeIf(pstImsNicEntity->ulIfIndex);
    if ( (VRP_IFNET_NOERR != ulRet) && (VRP_IFNET_NO_HAVE_BEEN_DOWN != ulRet))
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_RESUME_IF_FAIL, 1, enModemId);
    }

    /* ��ά�ɲ� */
    PS_MEM_SET(aucInput, 0, sizeof(aucInput));
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG1(aucInput, TCPIP_ResumeIf, pstImsNicEntity->ulIfIndex, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    ulRet           = TCPIP_AddIpAddr(ulIpAddr, ulMask, pstImsNicEntity->ulIfIndex);

    /* ��ά�ɲ� */
    PS_MEM_SET(aucInput, 0, sizeof(aucInput));
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG3(aucInput, TCPIP_AddIpAddr, ulIpAddr,
        ulMask, pstImsNicEntity->ulIfIndex, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    if ( ERR_AM4_OK != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_ADD_IPV4_ADDR_FAIL, 1, enModemId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_PdnInfoDelIpv6
 ��������  : IMS��������PDN IPv6������Ϣɾ��
 �������  : ucRabId        ���غ�
             enModemId      ��ǰmodemID

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID   IMS_NIC_PdnInfoDelIpv6(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_INT8                            acIpAddrStr[IMS_NIC_IPV6_ADDR_STR_LEN + 1] = {0};
    VOS_INT8                            acIfName[IMS_NIC_TCPIP_INPUT_LEN]   = {0};
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN]    = {0};
    VOS_UINT32                          ulIfIndex;
    VOS_UINT32                          ulRet;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU       *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU              *pstPdnInfo;

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);
    pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ucRabId - IMS_NIC_RAB_ID_OFFSET]);

    IMS_NIC_ConvertIpv6AddrToCompressedStr((VOS_UINT8 *)acIpAddrStr, pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr, IMS_NIC_IPV6_STR_RFC2373_TOKENS);

    ulIfIndex       = pstImsNicEntity->ulIfIndex;

    ulRet = TCPIP_GetFullNameByIfIndex(ulIfIndex, (CHAR *)acIfName);
    if ( VOS_OK != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_GET_IF_NAME_BY_INDEX_FAIL, 1, enModemId);
        return;
    }

    PS_MEM_SET(aucInput, 0, sizeof(aucInput));

    /* ��ά�ɲ� */
    IMS_NIC_TCPIP_INPUT_STR_LOG4(aucInput, IMS_NIC_PdnInfoDelIpv6,
        acIfName, acIpAddrStr, IMS_NIC_DEFAULT_IPV6_MASK_LEN, IMS_NIC_TCPIP_GLOBAL_ADDR_FLAG, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    /* ����״̬���������¼��IP��Ϣ */
    pstSinglePdnInfo->bitOpIpv6PdnInfo      = VOS_FALSE;
    pstSinglePdnInfo->bitOpIpv6DnsPrimCfged = VOS_FALSE;
    pstSinglePdnInfo->bitOpIpv6DnsSecCfged  = VOS_FALSE;

    PS_MEM_SET(&(pstSinglePdnInfo->stIpv6PdnInfo), 0, sizeof(IMS_NIC_IPV6_PDN_INFO_STRU));

    return;
}


VOS_VOID   IMS_NIC_PdnInfoDelIpv4(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId)
{
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    IMS_NIC_SINGLE_PDN_INFO_STRU       *pstSinglePdnInfo;
    IMS_NIC_PDN_INFO_STRU              *pstPdnInfo;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIpAddr;
    VOS_UINT32                          ulMask;
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};


    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);
    pstPdnInfo          = &(pstImsNicEntity->stImsNicPdnInfo);
    pstSinglePdnInfo    = &(pstPdnInfo->astImsNicPdnInfo[ucRabId - IMS_NIC_RAB_ID_OFFSET]);
    ulIpAddr            = vrp_ntohl(*(VOS_UINT32 *)pstSinglePdnInfo->stIpv4PdnInfo.aucIpV4Addr);
    ulMask              = IMS_NIC_TCPIP_DEFAULT_SUBNET_MASK;

    ulRet = TCPIP_DelIpAddr(ulIpAddr, ulMask, pstImsNicEntity->ulIfIndex);

    /* ��ά�ɲ� */
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG3(aucInput, TCPIP_DelIpAddr,
        ulIpAddr, ulMask, pstImsNicEntity->ulIfIndex, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    if ( ERR_AM4_OK != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_DEL_IPV4_ADDR_FAIL, 1, enModemId);
        return;
    }

    /* ����״̬���������¼��IP��Ϣ */
    pstSinglePdnInfo->bitOpIpv4PdnInfo      = VOS_FALSE;
    pstSinglePdnInfo->bitOpIpv4DnsPrimCfged = VOS_FALSE;
    pstSinglePdnInfo->bitOpIpv4DnsSecCfged  = VOS_FALSE;

    PS_MEM_SET(&(pstSinglePdnInfo->stIpv4PdnInfo), 0, sizeof(IMS_NIC_IPV4_PDN_INFO_STRU));

    return;
}


VOS_VOID IMS_NIC_DnsConfigtoIpStack
(
    VOS_UINT8                           ucIpAddrLen,
    VOS_UINT8                           ucDnsIndx,
    VOS_UINT8                          *pucIpAddr
)
{
    VOS_INT8                            acIpAddrStr[IMS_NIC_IPV6_ADDR_STR_LEN + 1] = {0};
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};
    VOS_INT                             iLen;
    VOS_UINT32                          ulRet;


    /* �ⲿ�Ѽ��ָ��ǿ� */

    if (IMS_NIC_IPV6_ADDR_LENGTH == ucIpAddrLen)
    {
        /* IPv6��ַתΪ�ַ��� */
        IMS_NIC_ConvertIpv6AddrToCompressedStr((VOS_UINT8 *)acIpAddrStr, pucIpAddr, IMS_NIC_IPV6_STR_RFC2373_TOKENS);

        /* ����IP��ַ�ַ�������DNS Server��Э��ջ */
        ulRet = TCPIP_SetDnsServer(IMS_NIC_TCPIP_ADD_DNS_OP, (CHAR *)acIpAddrStr, IMS_NIC_TCPIP_DNS_CONFIG_IPV6_FLAG);

        /* ��ά�ɲ� */
        (VOS_VOID)IMS_NIC_TCPIP_INPUT_STR_LOG3(aucInput, TCPIP_SetDnsServer,
            IMS_NIC_TCPIP_ADD_DNS_OP, IMS_NIC_TCPIP_DNS_CONFIG_IPV6_FLAG, acIpAddrStr, ulRet);

        IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

        if ( DNSC_SUCCESS != ulRet )
        {
            IMS_NIC_ERROR_LOG_MSG1(UEPS_PID_IMSNIC, "SetDnsServer IPV6 Failed!\n", (VOS_INT32)ulRet);
        }
    }
    else
    {
        /* IPv4��ַתΪ�ַ��� */
        iLen = IMS_NIC_IP4_TO_STR(acIpAddrStr, pucIpAddr);
        IMS_NIC_SET_CMD_END(acIpAddrStr, iLen);

        /* ����IP��ַ�ַ�������DNS Server��Э��ջ */
        ulRet = TCPIP_SetDnsServer(IMS_NIC_TCPIP_ADD_DNS_OP, (CHAR *)acIpAddrStr, IMS_NIC_TCPIP_DNS_CONFIG_IPV4_FLAG);

        /* ��ά�ɲ� */
        (VOS_VOID)IMS_NIC_TCPIP_INPUT_STR_LOG3(aucInput, TCPIP_SetDnsServer,
            IMS_NIC_TCPIP_ADD_DNS_OP, IMS_NIC_TCPIP_DNS_CONFIG_IPV4_FLAG, acIpAddrStr, ulRet);

        IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

        if ( DNSC_SUCCESS != ulRet )
        {
            IMS_NIC_ERROR_LOG_MSG1(UEPS_PID_IMSNIC, "SetDnsServer IPV4 Failed!\n", (VOS_INT32)ulRet);
        }
    }

    return;
}
VOS_VOID IMS_NIC_DnsDeltoIpStack
(
    VOS_UINT32                          ulIndx,
    VOS_UINT8                           ucRabId,
    IMS_NIC_DNS_INFO_STRU              *pstDnsInfo
)
{
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};
    VOS_INT8                            acIpAddrStr[IMS_NIC_IPV6_ADDR_STR_LEN + 1] = {0};
    VOS_UINT32                          ulRet;
    VOS_INT                             iLen;


    /* ǰ���Ѿ����ucRabId�Ϸ��Ժ�ָ��ǿ� */

    if (IMS_NIC_IPV6_ADDR_LENGTH == pstDnsInfo->astImsNicDnsInfo[ulIndx].ucIpAddrLen)
    {
        /* IPv6��ַתΪ�ַ��� */
        IMS_NIC_ConvertIpv6AddrToCompressedStr((VOS_UINT8 *)acIpAddrStr,
            pstDnsInfo->astImsNicDnsInfo[ulIndx].aucDnsAddr, IMS_NIC_IPV6_STR_RFC2373_TOKENS);

        /* ����IP��ַ�ַ�������DNS Server��Э��ջ */
        ulRet = TCPIP_SetDnsServer(IMS_NIC_TCPIP_DEL_DNS_OP, (CHAR *)acIpAddrStr, IMS_NIC_TCPIP_DNS_CONFIG_IPV6_FLAG);
        if ( DNSC_SUCCESS != ulRet )
        {
            IMS_NIC_ERROR_LOG_MSG1(UEPS_PID_IMSNIC, "SetDnsServer IPV6 Failed!\n", (VOS_INT32)ulRet);
        }

        /* ��ά�ɲ� */
        (VOS_VOID)IMS_NIC_TCPIP_INPUT_STR_LOG3(aucInput, TCPIP_SetDnsServer,
            IMS_NIC_TCPIP_DEL_DNS_OP, IMS_NIC_TCPIP_DNS_CONFIG_IPV6_FLAG, acIpAddrStr, ulRet);

        IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));
    }
    else
    {
        /* IPv4��ַתΪ�ַ��� */
        iLen = IMS_NIC_IP4_TO_STR(acIpAddrStr, pstDnsInfo->astImsNicDnsInfo[ulIndx].aucDnsAddr);
        IMS_NIC_SET_CMD_END(acIpAddrStr, iLen);

        /* ����IP��ַ�ַ�������DNS Server��Э��ջ */
        ulRet = TCPIP_SetDnsServer(IMS_NIC_TCPIP_DEL_DNS_OP, (CHAR *)acIpAddrStr, IMS_NIC_TCPIP_DNS_CONFIG_IPV4_FLAG);
        if ( DNSC_SUCCESS != ulRet )
        {
            IMS_NIC_ERROR_LOG_MSG1(UEPS_PID_IMSNIC, "SetDnsServer IPV4 Failed!\n", (VOS_INT32)ulRet);
        }

        /* ��ά�ɲ� */
        (VOS_VOID)IMS_NIC_TCPIP_INPUT_STR_LOG3(aucInput, TCPIP_SetDnsServer,
            IMS_NIC_TCPIP_DEL_DNS_OP, IMS_NIC_TCPIP_DNS_CONFIG_IPV4_FLAG, acIpAddrStr, ulRet);

        IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));
    }

    return;
}
VOS_VOID IMS_NIC_ResetAll(MODEM_ID_ENUM_UINT16 enModemId)
{
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};
    VOS_UINT32                          ulRet;


    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);

    ulRet = TCPIP_ShutDownIf(pstImsNicEntity->ulIfIndex);
    if ( VRP_IFNET_NOERR != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_NETIF_RESET_FAIL, 1, enModemId);
    }

    /* ��ά�ɲ� */
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG1(aucInput, TCPIP_ShutDownIf, pstImsNicEntity->ulIfIndex, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    PS_MEM_SET(&(pstImsNicEntity->stImsNicPdnInfo), 0, sizeof(IMS_NIC_PDN_INFO_STRU));

    return;
}
VOS_VOID IMS_NIC_SetDefaultRoute(MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN];
    VOS_INT8                            acIfName[IMS_NIC_TCPIP_INPUT_LEN] = {0};
    VOS_UINT32                          ulRet;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);

    /* ����IPV4Ĭ��·�ɵ����������� */
    /* Ĭ��·��IP��ַ�����볤����Ϊ0 */
    ulRet = TCPIP_RouteAdd(0, 0, IMS_NIC_DEFAULT_ROUTE_GATEWAY, pstImsNicEntity->ulIfIndex, IMS_NIC_TCPIP_DEFAULT_ROUTE_PRIORITY);

    /* ��ά�ɲ� */
    PS_MEM_SET(aucInput, 0, sizeof(aucInput));
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG3(aucInput, TCPIP_RouteAdd,
        IMS_NIC_DEFAULT_ROUTE_GATEWAY,
        pstImsNicEntity->ulIfIndex, IMS_NIC_TCPIP_DEFAULT_ROUTE_PRIORITY, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    if ( VOS_OK != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_CONFIG_IPV4_ROUTE_FAIL, 1, enModemId);
        return;
    }

    /* ����IPV6Ĭ��·�ɵ����������� */
    ulRet = TCPIP_GetFullNameByIfIndex(pstImsNicEntity->ulIfIndex, (CHAR *)acIfName);

    /* ��ά�ɲ� */
    PS_MEM_SET(aucInput, 0, sizeof(aucInput));
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_STR_LOG2(aucInput, TCPIP_GetFullNameByIfIndex,
        pstImsNicEntity->ulIfIndex, acIfName, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    if ( VOS_OK != ulRet )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_GET_IF_NAME_BY_INDEX_FAIL, 1, enModemId);
        return;
    }

    return;
}
VOS_UINT32 IMS_NIC_SetSocketPort
(
    VOS_UINT16                          usMinPort,
    VOS_UINT16                          usMaxPort,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};
    VOS_UINT32                          ulRet;
    SOCK_GLOBLE_S                       stSockGlobal;


    stSockGlobal.usAutoPortStart   = usMinPort;
    stSockGlobal.usAutoPortEnd     = usMaxPort;

    if (usMinPort > usMaxPort)
    {
        IMS_NIC_ERROR_LOG2(UEPS_PID_IMSNIC,
            "IMS_NIC_SetSocketPort, ERROR, min, max", usMinPort, usMaxPort);

        IMS_NIC_STATS_INC(IMS_NIC_STATS_PORT_CONFIG_INVALID, 1, enModemId);

        return IMS_NIC_FAIL;
    }

    ulRet = TCPIP_SetSockGlobleConfig(&stSockGlobal);
    if ( VOS_OK != ulRet )
    {
        IMS_NIC_ERROR_LOG3(UEPS_PID_IMSNIC,
            "IMS_NIC_SetSocketPort, ERROR, min, max", usMinPort, usMaxPort, ulRet);
    }

    /* ��ά�ɲ� */
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG2(aucInput, TCPIP_SetSockGlobleConfig,
        stSockGlobal.usAutoPortStart, stSockGlobal.usAutoPortEnd, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_MtuSet
 ��������  : IMS��������MTU����
 �������  : ulMtu        ����͵�Ԫ
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��Ϊ��Ӧ�Ĵ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��14��
    ��    ��   : lvcunpai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_MtuSet(VOS_UINT32 ulMtu)
{
    VOS_UINT16                          usIndex;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};


    /* ulMtu���Ȳ�����Ч��Χ�� */
    if ( (ulMtu < IMS_NIC_MIN_IPPKT_LEN) || (ulMtu > IMS_NIC_MAX_IPPKT_LEN) )
    {
        /* Ĭ�ϼ�¼��Modem0��ʵ���� */;
        IMS_NIC_STATS_INC(IMS_NIC_STATS_MTU_INVALID, 1, IMS_NIC_MODEM_ID_0);

        return IMS_NIC_MTU_INVALID;
    }

    for (usIndex = 0 ; usIndex < IMS_NIC_MODEM_ID_BUTT ; usIndex++)
    {
        pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(usIndex);

        /* ���������Ѿ���ʼ��������ifconfig��������MTU */
        if ( VOS_TRUE == pstImsNicEntity->ulImsNicInitFlag )
        {
            ulRet = TCPIP_SetLinkMtu(pstImsNicEntity->ulIfIndex, ulMtu);

            /* ��ά�ɲ� */
            (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG2(aucInput, TCPIP_SetLinkMtu,
                pstImsNicEntity->ulIfIndex, ulMtu, ulRet);

            IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

            if ( VRP_IFNET_NOERR != ulRet )
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_MTU_CONFIG_FAIL, 1, usIndex);
            }

            ulRet = ADDR_Set_Mtu(pstImsNicEntity->ulIfIndex, ulMtu);

            /* ��ά�ɲ� */
            PS_MEM_SET(aucInput, 0, sizeof(aucInput));
            (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG2(aucInput, ADDR_Set_Mtu,
                pstImsNicEntity->ulIfIndex, ulMtu, ulRet);

            IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

            if ( VOS_OK != ulRet )
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_MTU_CONFIG_FAIL, 1, usIndex);
                continue;
            }
        }

        /* �޸�IMS_NIC_MTU_VALUE��ֵ������������ʼ��ʱ�����ø�ֵΪMTU��С */
        IMS_NIC_SET_MTU(ulMtu);
    }

    return IMS_NIC_SUCC;
}


/*****************************************************************************
 �� �� ��  : IMS_NIC_DlDataRcv
 ��������  : IMS���������������ݽ��սӿڣ��ṩ��CDS����
 �������  : pucData      IP������
             usLen        IP������
             enModemId    ��ǰmodemID
 �������  :
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��:IMS_NIC_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��14��
    ��    ��   : lvcunpai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_DlDataRcv(VOS_UINT8 *pucData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId)
{
    MBUF_S                             *pMbuf;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulQueueId;
    VOS_UINT8                           ucIpType;

    /* ��μ�� */
    ulResult        = IMS_NIC_DlParaCheck(pucData, usLen, enModemId);
    if ( IMS_NIC_SUCC != ulResult )
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_DlDataRcv, ERROR, input para invalid!\n");
        IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_RCV_ERR_PKT, 1, enModemId);

        return IMS_NIC_FAIL;
    }

    /* ����IP���İ汾�� */
    ucIpType    = ((pucData[0] >> IMS_NIC_IP_VERSION_POS) & IMS_NIC_IP_VERSION_MASK);

    switch (ucIpType)
    {
        case IMS_NIC_IPV4_VERSION:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_RCV_IPV4_PKT, 1, enModemId);
            ulQueueId = QUE_IP_INPUT;
            break;

        case IMS_NIC_IPV6_VERSION:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_RCV_IPV6_PKT, 1, enModemId);
            ulQueueId = QUE_IPV6_INPUT;
            break;

        default:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_RCV_ERR_PKT, 1, enModemId);

            IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_DlDataRcv, ERROR, ucIpType=%d error!\n", ucIpType);
            return IMS_NIC_FAIL;
    }

    /* ����MBUF�ڴ沢�����ݿ��� */
    pMbuf = MBUF_CreateByCopyBuffer(IMS_NIC_TCPIP_HEADER_RESERVE_LEN, usLen, pucData, MBUF_TYPE_DATA, 0);
    if ( VOS_NULL_PTR == pMbuf )
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "CreateByCopyBuffer Fail!\n");

        return IMS_NIC_FAIL;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);

    /* IP������� */
    ulResult            = TCPIP_EnMBufQueue(pMbuf, ulQueueId, pstImsNicEntity->ulIfIndex);
    if ( VRP_IFNET_NOERR != ulResult)
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "EnMBufQueue Fail!\n");

        return IMS_NIC_FAIL;
    }

    /* ���з�������ͳ�� */
    IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_SEND_PKT, 1, enModemId);

    /* ���������������ݽ����ֽ��� */
    IMS_NIC_STATS_INC(IMS_NIC_STATS_DL_RCV_BYTES, usLen, enModemId);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_Delete
 ��������  : IMS��������ж�غ���
 �������  : enModemId      --��ǰModem��
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��Ϊ��Ӧ�Ĵ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��14��
    ��    ��   : lvcunpai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_Delete (MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT32                          ulIfIndex;
    VOS_UINT32                          ulRet;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT8                           aucInput[IMS_NIC_TCPIP_INPUT_LEN] = {0};


    if ( enModemId >= IMS_NIC_MODEM_ID_BUTT )
    {
        /* Ĭ�ϼ�¼��Modem0��ʵ���� */;
        IMS_NIC_STATS_INC(IMS_NIC_STATS_MODEM_ID_ERR_OTHER, 1, IMS_NIC_MODEM_ID_0);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_Free, ERROR, Input modem id invalid!\n", enModemId);

        return IMS_NIC_MODEM_ID_INVALID;
    }

    /* ����modem id�ҵ�IfIndex */
    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);
    ulIfIndex           = pstImsNicEntity->ulIfIndex;

    /* ����������û�г�ʼ�� */
    if ( VOS_TRUE != pstImsNicEntity->ulImsNicInitFlag )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_NOT_INITED_ERR, 1, enModemId);

        return IMS_NIC_NOT_INITED;
    }

    ulRet = TCPIP_DeleteIF(ulIfIndex);

    /* ��ά�ɲ� */
    (VOS_VOID)IMS_NIC_TCPIP_INPUT_LOG1(aucInput, TCPIP_DeleteIF, pstImsNicEntity->ulIfIndex, ulRet);

    IMS_NIC_MNTN_TRACE(ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG, aucInput, sizeof(aucInput));

    if (VRP_IFNET_NOERR != ulRet)
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_SYS_CALL_FAIL, 1, enModemId);

        IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_Free, ERROR, call DeleteIF fail!\n", enModemId);

        return IMS_NIC_SYSCALLFAIL;
    }

    pstImsNicEntity->ulImsNicInitFlag = VOS_FALSE;

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_UL_IPDataSend
 ��������  : �ú�������MUX����������ݽ���CDS
 �������  : pucData      IP������
             usLen        IP������
             enModemId    ��ǰmodemID
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��ΪIMS_NIC_FAIL
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_UL_IPDataSend(VOS_UINT8 *pucData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId)
{
    IMS_NIC_ENTITY_STRU                     *pstImsNicEntity;
    VOS_UINT32                               ulResult;
    VOS_UINT8                                ucIpType;

    /* ���ݱ��ĳ��Ȳ�����Чֵ��Χ�ڣ���[MIN, MTU], ����MINΪ��СIP����С */
    if ( VOS_NULL_PTR == pucData )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_INPUT_NULL_PTR, 1, enModemId);

        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_UL_IPDataSend, ERROR, Input data  is invalid!\n");

        return IMS_NIC_FAIL;
    }

    /* ���ݱ��ĳ��Ȳ�����Чֵ��Χ�ڣ���[MIN, MTU], ����MINΪ��СIP����С */
    if ( (usLen < IMS_NIC_MIN_IPPKT_LEN) || (usLen > IMS_NIC_GET_MTU) )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_DATA_LEN_ERR, 1, enModemId);

        IMS_NIC_ERROR_LOG2(UEPS_PID_IMSNIC, "IMS_NIC_UL_IPDataSend, ERROR, Input data len =%d mtu = %d is invalid!\n", (VOS_INT32)usLen, (VOS_INT32)IMS_NIC_GET_MTU);

        return IMS_NIC_FAIL;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);
    if ( VOS_NULL_PTR   == pstImsNicEntity->pUlDataSendFunc )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_CB_FUN_NOT_REG, 1, enModemId);

        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_UL_IPDataSend, pUlDataSendFunc is NULL!\n");

        return IMS_NIC_FAIL;
    }

    /* ����IP���İ汾�� */
    ucIpType    = ((pucData[0] >> IMS_NIC_IP_VERSION_POS) & IMS_NIC_IP_VERSION_MASK);
    switch (ucIpType)
    {
        case IMS_NIC_IPV4_VERSION:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_IPV4_PKT, 1, enModemId);
            break;

        case IMS_NIC_IPV6_VERSION:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_IPV6_PKT, 1, enModemId);
            break;

        default:
            IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_RCV_ERR_PKT, 1, enModemId);

            IMS_NIC_ERROR_LOG1(UEPS_PID_IMSNIC, "IMS_NIC_UL_IPDataSend, ERROR, ucIpType=%d error!\n", ucIpType);

            return IMS_NIC_FAIL;
    }

    /* ����CDSע����������ݷ��ͺ��� */
    ulResult    = pstImsNicEntity->pUlDataSendFunc(pucData, usLen, enModemId);
    if( IMS_NIC_SUCC != ulResult )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_CALL_CB_FUN_FAIL, 1, enModemId);

        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_UL_IPDataSend, ERROR, call pUlDataSendFunc fail!\n");

        return IMS_NIC_FAIL;
    }

    /* ���з�������ͳ�� */
    IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_SEND_PKT, 1, enModemId);

    /* ���������������ݷ����ֽ��� */
    IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_SEND_BYTES, usLen, enModemId);

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_Send
 ��������  : �ú�������MUX����������ݽ���CDS
 �������  : VOS_UINT32 ulPhyLink   --  �ײ���ƿ�ָ��
             MBUF_S * pMbuf         --  ��̫����,��ο�MBUF�ṹ��
 �������  : ��
 �� �� ֵ  : 2                      --  ����֪ͨVISP�Ѿ�������ɣ�����VISP�ڲ���Ҫ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��14��
    ��    ��   : lvcunpai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_Send (VOS_UINT32 ulPhyLink, MBUF_S * pMbuf)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulIndex;
    VOS_UINT16                          usDataLen;
    VOS_UINT16                          usRemainlen;
    IMS_NIC_DEV_STRU                   *pstImsNicDev;

    if ( VOS_NULL_PTR == pMbuf )
    {
        IMS_NIC_STATS_INC(IMS_NIC_STATS_UL_INPUT_NULL_PTR, 1, IMS_NIC_MODEM_ID_0);

        return IMS_NIC_ERR;
    }

    pstImsNicDev    = IMS_NIC_GET_DEV_STRU_PTR(IMS_NIC_MODEM_ID_0);
    usRemainlen     = (VOS_UINT16)pMbuf->ulTotalDataLength;
    ulIndex         = 0;

    while ( usRemainlen > 0 )
    {
        if ( usRemainlen > IMS_NIC_MAX_IPPKT_LEN )
        {
            usDataLen       = IMS_NIC_MAX_IPPKT_LEN;
            usRemainlen    -= IMS_NIC_MAX_IPPKT_LEN;
        }
        else
        {
            usDataLen       = usRemainlen;
            usRemainlen     = 0;
        }

        ulResult    = MBUF_CopyDataFromMBufToBuffer(pMbuf, ulIndex * IMS_NIC_MAX_IPPKT_LEN,
                            usDataLen, pstImsNicDev->aucSendBuf);
        ulIndex++;

        if ( VOS_OK != ulResult )
        {
            IMS_NIC_STATS_INC(IMS_NIC_STATS_COPY_DATA_FROM_MBUF_FAIL, 1, IMS_NIC_MODEM_ID_0);
            continue;
        }

        /* �������ݴ��� */
        ulResult    = IMS_NIC_UL_IPDataSend(pstImsNicDev->aucSendBuf, usDataLen, IMS_NIC_MODEM_ID_0);
        if ( IMS_NIC_SUCC != ulResult )
        {
            IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_Send, call IMS_NIC_UlDataSend!\n");
        }
    }

    /* ����ϵͳ�����ͷŸ�MBUF�ڴ� */
    MBUF_Destroy(pMbuf);

    return IMS_NIC_OK;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_Ioctl
 ��������  : �ú�������ִ��IO��������
 �������  : VOS_UINT32 ulPhyLink       --  �ײ���ƿ�ָ��
             VOS_UINT32 ulCmdIndex      --  ����������
             char *pData                --  ���Ʋ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��14��
    ��    ��   : lvcunpai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_Ioctl(VOS_UINT32 ulPhyLink, VOS_UINT32 ulCmdIndex, VOS_CHAR *pData)
{
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT32                          ulRet;
    IMS_NIC_ELEMENT_TAB_STRU           *pstImsNicElementTbl;
    VOS_UINT8                           aucMacAddr[IMS_NIC_ETHER_ADDR_LEN];

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(IMS_NIC_MODEM_ID_0);

    switch ( ulCmdIndex )
    {
        case PHY_SHUTDOWN :
            /*�ײ��¼�ýӿڱ�shutdown���*/
            /*�ñ����ҪӦ���ڣ����ײ�״̬���ͱ仯�������ݱ�������ʱ������ýӿ��Ѿ���shutdown��
              ��Ӧ���ϱ��ײ�״̬�����ݱ���*/
            /*�˴�������ɽӿ�Down�Ĵ���*/
            ulRet   = TCPIP_IF_LinkIoCtl(pstImsNicEntity->ulIfIndex, ISLDOWN, VOS_NULL_PTR);
            if (VRP_IFNET_NOERR != ulRet)
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_ISLUP_FAIL, 1, IMS_NIC_MODEM_ID_0);
            }
            break;

        case PHY_NO_SHUT :
            /*����ײ��¼�ýӿ��ѱ�shutdown�������shutdown���*/
            /*���ײ��Ƿ�UP�����UP�������ϱ�Э��ջ�ײ�UP�¼�*/
            /*�˴�������ɽӿ�noshutdown�Ĵ���*/
            ulRet   = TCPIP_IF_LinkIoCtl(pstImsNicEntity->ulIfIndex, ISLUP, VOS_NULL_PTR);
            if (VRP_IFNET_NOERR != ulRet)
            {
                IMS_NIC_STATS_INC(IMS_NIC_STATS_ISLUP_FAIL, 1, IMS_NIC_MODEM_ID_0);
            }
            break;

        case PHY_POWERUP :
            /* ��ϵͳ����ʱ�Ѿ���ʼ����TSEC���˴����Բ����κδ���*/
            ulRet   = TCPIP_IF_LinkIoCtl(pstImsNicEntity->ulIfIndex, ISLUP, VOS_NULL_PTR);
            if (VRP_IFNET_NOERR != ulRet)
            {
                IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC,
                    "TCPIP_IF_LinkIoCtl, ISLUP Retrun Value Error!\n", ulRet);

                IMS_NIC_STATS_INC(IMS_NIC_STATS_ISLUP_FAIL, 1, IMS_NIC_MODEM_ID_0);
            }

            /* ��DOPRA IP�ϱ�MAC��ַ����Ʒ������Ҫ��ȡ�ӿڵ�MAC��ַ */
            /* ÿ��modem id�̶�һ��MAC��ַ�����������Ŀ�ĵ�ַ */
            pstImsNicElementTbl = (IMS_NIC_ELEMENT_TAB_STRU *)IMS_NIC_GET_ELEMENT_TABLE(IMS_NIC_MODEM_ID_0);
            PS_MEM_CPY(aucMacAddr, pstImsNicElementTbl->stIpv4Ethhead.aucEtherShost, IMS_NIC_ETHER_ADDR_LEN);

            ulRet = TCPIP_IF_LinkIoCtl(pstImsNicEntity->ulIfIndex, ISLSETMAC, (CHAR *)aucMacAddr);
            if (VRP_IFNET_NOERR != ulRet)
            {
                IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC,
                    "TCPIP_IF_LinkIoCtl, ISLSETMAC Retrun Value Error!\n", ulRet);

                return IMS_NIC_FAIL;
            }

            IMS_NIC_STATS_INC(IMS_NIC_STATS_ISLUP_SUCC, 1, IMS_NIC_MODEM_ID_0);

            break;

        case PHY_JOINMULTI :
            /* �˴��������ಥ��ַ��ӵ������Ķಥ�����б��� */
            break;

        case PHY_LEAVEMULTI :
            /* �˴��������ಥ��ַ�������Ķಥ�����б���ɾ�� */
            break;

        case PHY_DELETE :
            /* �ײ�ɾ���ӿڣ��ͷ������Դ*/
            return IMS_NIC_SUCC;

        case PHY_SETMACADDR :
            /*����MAC��ַ��̬����*/
            break;

        default:
            /* ���� */;
            return IMS_NIC_FAIL;/* ����������֧�ָò��� */
    }

    return IMS_NIC_SUCC;
}

/*****************************************************************************
 �� �� ��  : IMS_NIC_Load
 ��������  : �ӿڳ�ʼ������
 �������  : DEVLINK_S *pstDev      --  �����豸ָ��
             VOS_UINT32 *pulIfIndex --  �ӿ�����ָ��
             VOS_UINT32 *pulSlot    --  ��ǰδʹ��
             VOS_UINT32 ulSlotNum   --  ��ǰδʹ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��14��
    ��    ��   : lvcunpai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_Load(DEVLINK_S *pstDev, VOS_UINT32 *pulIfIndex, VOS_UINT32 *pulSlot, VOS_UINT32 ulSlotNum)
{
    VOS_UINT32                          ulRet;

    if ( VOS_NULL_PTR == pulIfIndex )
    {
        IMS_NIC_INIT_LOG_PRINT(UEPS_PID_IMSNIC, "IMS_NIC_Load: Null Input Ptr!");

        return IMS_NIC_ERR;
    }

    ulRet = TCPIP_RegFuncPhyIoCtlHook(*pulIfIndex, (IF_PHYIOCTL_FUNC)IMS_NIC_Ioctl);
    if (VRP_IFNET_NOERR != ulRet)
    {
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC, "TCPIP_RegFuncPhyIoCtlHook: Error!", ulRet);

        return IMS_NIC_ERR;
    }

    ulRet = TCPIP_RegFuncPhyTransmitHook(*pulIfIndex, (IF_TRANSMIT_FUNC)IMS_NIC_Send);
    if (VRP_IFNET_NOERR != ulRet)
    {
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC, "TCPIP_RegFuncPhyTransmitHook: Error!", ulRet);

        return IMS_NIC_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 IMS_NIC_Init (MODEM_ID_ENUM_UINT16 enModemId)
{
    VOS_UINT32                          ulIfIndex;
    VOS_UINT32                          ulRet;
    DEVLINK_S                           strDev;
    VOS_UINT8                           aucMacAddr[IMS_NIC_ETHER_ADDR_LEN] = {0};
    VOS_UINT32                          ulPortNo;
    const IMS_NIC_ELEMENT_TAB_STRU     *pstImsNicElementTbl;
    IMS_NIC_SEND_UL_DATA_FUNC           pFunc;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    IN6ADDR_S                           stAddr;

    if ( enModemId >= IMS_NIC_MODEM_ID_BUTT )
    {
        /* Ĭ�ϼ�¼��Modem0��ʵ���� */;
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC, "IMS_NIC_Init, ERROR, Input modem id invalid!\n", enModemId);

        return IMS_NIC_MODEM_ID_INVALID;
    }

    pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(enModemId);

    /* �����������Ѿ���ʼ�� */
    if ( VOS_TRUE == pstImsNicEntity->ulImsNicInitFlag )
    {
        IMS_NIC_INIT_LOG_PRINT(UEPS_PID_IMSNIC, "IMS_NIC_Init, WARNNING, IMS NIC is already initialed!\n");
        return IMS_NIC_ALREADY_INITED;
    }

    /* ��ʼ����������ʵ��pstImsNicEntity */
    PS_MEM_SET(pstImsNicEntity, 0, sizeof(IMS_NIC_ENTITY_STRU));

    pFunc   = IMS_NIC_GET_SAVED_UL_DATA_FUNC(enModemId);

    /* ��������������ݷ��ͻص�������ֵ��ʵ���� */
    pstImsNicEntity->pUlDataSendFunc    = pFunc;

    /* �����豸�ڵ�*/
    PS_MEM_SET( &strDev, 0, sizeof( DEVLINK_S ));

    /* ÿ��modem id�̶�һ��port no����ֻ���������������� */
    ulPortNo = (VOS_UINT32)enModemId;

    /* ��ʼ���豸�ڵ㣬DEVLINK_S��dev_pDeviceName��dev_pfInitial������Ա�ĳ�ʼ���Ǳ����*/
    (VOS_VOID)VOS_sprintf(strDev.dev_pDeviceName, "UI%d", ulPortNo);
    strDev.dev_pfInitial = (FUNC_PHY_INITIAL)IMS_NIC_Load;

    /* ����DOPRA IP �ӿڴ����豸��IFNET�ṹ */
    ulRet = TCPIP_CreateIFByDev(&strDev, (ULONG *)&ulIfIndex);
    if( VRP_IFNET_NOERR != ulRet )
    {
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC, "CreateIFByDev ERROR!\n", ulRet);

        return IMS_NIC_FAIL;
    }

    /* ���IFNET������ֵ */
    /* ����ֵ���������������������ҵ����������� */
    pstImsNicEntity->ulIfIndex = ulIfIndex;

    /* ��DOPRA IP�ϱ�MAC��ַ����Ʒ������Ҫ��ȡ�ӿڵ�MAC��ַ */
    /* ÿ��modem id�̶�һ��MAC��ַ�����������Ŀ�ĵ�ַ */
    pstImsNicElementTbl = (IMS_NIC_ELEMENT_TAB_STRU *)IMS_NIC_GET_ELEMENT_TABLE(enModemId);
    PS_MEM_CPY(aucMacAddr, pstImsNicElementTbl->stIpv4Ethhead.aucEtherShost, IMS_NIC_ETHER_ADDR_LEN);

    IMS_NIC_SetLinklocalAddr(&stAddr, aucMacAddr);
    PS_MEM_CPY(pstImsNicEntity->aucIpV6LinkLocalAddr, &stAddr, sizeof(IN6ADDR_S));

    /* ���ϳ�ʼ����� */
    pstImsNicEntity->ulImsNicInitFlag = VOS_TRUE;

    /* ����MTU,IPV4��IPV6��Ҫ�ò�ͬ�ӿ� */
    ulRet = TCPIP_SetLinkMtu(ulIfIndex, IMS_NIC_GET_MTU);
    if (VRP_IFNET_NOERR != ulRet)
    {
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC,
            "TCPIP_SetLinkMtu, Set IPV4 Mtu Fail!\n", ulRet);

        return IMS_NIC_FAIL;
    }

    ulRet = ADDR_IPv6EnableOnIntf_Host((CHAR *)strDev.dev_pDeviceName, IMS_NIC_ENABLE_HOST_MODE);
    if ( ADDRADP_OK != ulRet)
    {
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC,
            "ADDR_IPv6EnableOnIntf_Host, Enable Ipv6 Interface Fail!\n", ulRet);
        return IMS_NIC_FAIL;
    }

    ulRet = ADDR_Set_Mtu(ulIfIndex, IMS_NIC_GET_MTU);
    if (VOS_OK != ulRet)
    {
        IMS_NIC_INIT_LOG_PRINT1(UEPS_PID_IMSNIC,
            "ADDR_Set_Mtu, Set IPV6 Mtu Fail!\n", ulRet);

        return IMS_NIC_FAIL;
    }

    /* �رմ��ڵ�VISP��ӡ */
    TCPIP_OutputToCOM(0);

    return IMS_NIC_SUCC;
}


/*****************************************************************************
 �� �� ��  : IMS_NIC_GetMntnInfo
 ��������  : ��ȡIMS����������ͳ����Ϣ�������������ϱ�
 �������  : usType         -- ��ά�ɲ���Ϣ����
 �������  : pucData        -- �洢���ݵ��ڴ�
             pulLen         -- ���ݳ���
 �� �� ֵ  : �ɹ�:IMS_NIC_OK��ʧ��ΪIMS_NIC_FAIL
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 IMS_NIC_GetMntnInfo
(
    VOS_UINT8                       *pucData,
    VOS_UINT32                      *pulLen,
    VOS_UINT16                       usType
)
{
    VOS_UINT16                      usIndex;
    IMS_NIC_ENTITY_STRU            *pstImsNicEntity;
    VOS_UINT32                      ulModemCnt;


    if ( VOS_NULL_PTR == pucData )
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_GetMntnInfo, ERROR, Input pucData id null!\n");
        return IMS_NIC_FAIL;
    }

    if ( VOS_NULL_PTR == pulLen )
    {
        IMS_NIC_ERROR_LOG(UEPS_PID_IMSNIC, "IMS_NIC_GetMntnInfo, ERROR, Input pulLen id null!\n");
        return IMS_NIC_FAIL;
    }

    *pulLen     = 0;

    /* ��дModem���� */
    ulModemCnt  = (VOS_UINT32)IMS_NIC_MODEM_ID_BUTT;
    (VOS_VOID)mdrv_memcpy(pucData, &ulModemCnt, sizeof(ulModemCnt));
    pucData     += sizeof(ulModemCnt);

    for (usIndex = 0 ; usIndex < IMS_NIC_MODEM_ID_BUTT ; usIndex++)
    {
        pstImsNicEntity     = IMS_NIC_GET_ENTITY_STRU(usIndex);

        /* ��дmodemId */
        (VOS_VOID)mdrv_memcpy(pucData, &usIndex, IMS_NIC_MODEM_ID_LEN);
        pucData     += IMS_NIC_MODEM_ID_OFFSET;
        *pulLen     += IMS_NIC_MODEM_ID_OFFSET;

        /* ����ͳ����Ϣ */
        (VOS_VOID)mdrv_memcpy(pucData, (VOS_UINT8 *)(&(pstImsNicEntity->stImsNicStatsInfo)), sizeof(IMS_NIC_STATS_INFO_STRU));
        pucData     += sizeof(IMS_NIC_STATS_INFO_STRU);
        *pulLen     += sizeof(IMS_NIC_STATS_INFO_STRU);
    }

    return IMS_NIC_SUCC;
}
VOS_VOID IMS_NIC_Help(VOS_VOID)
{
    (VOS_VOID)vos_printf("��ӡ����״̬��Ϣ��IMS_NIC_ShowEntityState \n");
    (VOS_VOID)vos_printf("��ӡ����ͳ����Ϣ��IMS_NIC_ShowStats \n");
    (VOS_VOID)vos_printf("MuxShow��IMS_NIC_MuxShow \n");
}



VOS_VOID IMS_NIC_ShowEntityState(VOS_VOID)
{
    VOS_UINT8                       ucRabId;
    VOS_INT32                       iIndx1;
    VOS_INT32                       iIndx2;
    VOS_INT32                       iIndx3;
    VOS_UINT16                     *pusIpv6;
    VOS_UINT8                      *pucIpv4;
    IMS_NIC_ENTITY_STRU            *pstImsNicEntity;
    IMS_NIC_SINGLE_DNS_INFO_STRU   *pstSingleDnsInfo;
    IMS_NIC_SINGLE_PDN_INFO_STRU   *pstSinglePdnInfo;


    for (iIndx1 = 0; iIndx1 < IMS_NIC_MODEM_ID_BUTT; iIndx1++)
    {
        pstImsNicEntity = IMS_NIC_GET_ENTITY_STRU(iIndx1);
        (VOS_VOID)vos_printf("======================Entity info for Modem %d ======================\n", iIndx1);
        (VOS_VOID)vos_printf("ʵ���ʼ��״̬:             %d \n", pstImsNicEntity->ulImsNicInitFlag);
        (VOS_VOID)vos_printf("���з����ص�����ָ���ַ:   0x%x \n", pstImsNicEntity->pUlDataSendFunc);
        (VOS_VOID)vos_printf("��ǰ����PDN����:            %d \n", pstImsNicEntity->stImsNicPdnInfo.iPdnCfgCnt);
        (VOS_VOID)vos_printf("��ǰ���õ�DNS����:          %d \n", pstImsNicEntity->stImsNicPdnInfo.stImsNicDnsInfo.ucDnsServerCnt);

        for (iIndx2 = 0; iIndx2 < IMS_NIC_MAX_DNS_SERVER_NUM; iIndx2++)
        {
            pstSingleDnsInfo = &pstImsNicEntity->stImsNicPdnInfo.stImsNicDnsInfo.astImsNicDnsInfo[iIndx2];
            if (IMS_NIC_IPV6_ADDR_LENGTH == pstSingleDnsInfo->ucIpAddrLen)
            {
                pusIpv6 = (VOS_UINT16 *)pstSingleDnsInfo->aucDnsAddr;

                (VOS_VOID)vos_printf("%s �����ô���:%d, ��ַ����:%d, ��ַ:%x:%x:%x:%x:%x:%x:%x:%x \n",
                            g_pcDnsSSysVarName[iIndx2], pstSingleDnsInfo->cDnsRef, pstSingleDnsInfo->ucIpAddrLen,
                            VOS_HTONS(pusIpv6[0]), VOS_HTONS(pusIpv6[1]), VOS_HTONS(pusIpv6[2]), VOS_HTONS(pusIpv6[3]), VOS_HTONS(pusIpv6[4]), VOS_HTONS(pusIpv6[5]), VOS_HTONS(pusIpv6[6]), VOS_HTONS(pusIpv6[7]));
            }
            else if (IMS_NIC_IPV4_ADDR_LENGTH == pstSingleDnsInfo->ucIpAddrLen)
            {
                pucIpv4 = pstSingleDnsInfo->aucDnsAddr;

                (VOS_VOID)vos_printf("%s �����ô���:%d, ��ַ����:%d, ��ַ:%d.%d.%d.%d \n",
                            g_pcDnsSSysVarName[iIndx2], pstSingleDnsInfo->cDnsRef, pstSingleDnsInfo->ucIpAddrLen,
                            pucIpv4[0], pucIpv4[1], pucIpv4[2], pucIpv4[3]);
            }
            else
            {
                (VOS_VOID)vos_printf("%s �����ô���:%d, ��ַ����:%d \n", g_pcDnsSSysVarName[iIndx2], pstSingleDnsInfo->cDnsRef, pstSingleDnsInfo->ucIpAddrLen);
            }

        }

        for (iIndx3 = 0; iIndx3 < IMS_NIC_RAB_ID_MAX_NUM; iIndx3++)
        {
            pstSinglePdnInfo = &pstImsNicEntity->stImsNicPdnInfo.astImsNicPdnInfo[iIndx3];

            ucRabId = (VOS_UINT8)iIndx3 + IMS_NIC_RAB_ID_OFFSET;

            (VOS_VOID)vos_printf("PDN %d DNS ��������[primaryns]:%d, [secondaryns]:%d, [tertiaryns]:%d, [quaternaryns]:%d \n", ucRabId, pstSinglePdnInfo->aucDnsFlag[0], pstSinglePdnInfo->aucDnsFlag[1], pstSinglePdnInfo->aucDnsFlag[2], pstSinglePdnInfo->aucDnsFlag[3]);
            (VOS_VOID)vos_printf("PDN %d �Ƿ�����IPv4:%d \n", ucRabId, pstSinglePdnInfo->bitOpIpv4PdnInfo);

            if (VOS_TRUE == pstSinglePdnInfo->bitOpIpv4PdnInfo)
            {
                pucIpv4 = pstSinglePdnInfo->stIpv4PdnInfo.aucIpV4Addr;

                (VOS_VOID)vos_printf("PDN %d IPv4��ַ:%d.%d.%d.%d \n", ucRabId, pucIpv4[0], pucIpv4[1], pucIpv4[2], pucIpv4[3]);
                (VOS_VOID)vos_printf("PDN %d IPv4��DNS��Ϣ, bitOpDnsPrim:%d, bitOpDnsPrimCfged:%d \n", ucRabId, pstSinglePdnInfo->stIpv4PdnInfo.bitOpDnsPrim, pstSinglePdnInfo->bitOpIpv4DnsPrimCfged);

                pucIpv4 = pstSinglePdnInfo->stIpv4PdnInfo.aucDnsPrimAddr;
                (VOS_VOID)vos_printf("PDN %d IPv4��DNS��ַ:%d.%d.%d.%d \n", ucRabId, pucIpv4[0], pucIpv4[1], pucIpv4[2], pucIpv4[3]);

                (VOS_VOID)vos_printf("PDN %d IPv4��DNS��Ϣ, bitOpDnsPrim:%d, bitOpDnsPrimCfged:%d \n", ucRabId, pstSinglePdnInfo->stIpv4PdnInfo.bitOpDnsSec, pstSinglePdnInfo->bitOpIpv4DnsSecCfged);

                pucIpv4 = pstSinglePdnInfo->stIpv4PdnInfo.aucDnsSecAddr;
                (VOS_VOID)vos_printf("PDN %d IPv4��DNS��ַ:%d.%d.%d.%d \n", ucRabId, pucIpv4[0], pucIpv4[1], pucIpv4[2], pucIpv4[3]);
            }

            (VOS_VOID)vos_printf("PDN %d �Ƿ�����IPv6:%d \n", ucRabId, pstSinglePdnInfo->bitOpIpv6PdnInfo);

            if (VOS_TRUE == pstSinglePdnInfo->bitOpIpv6PdnInfo)
            {
                pusIpv6 = (VOS_UINT16 *)pstSinglePdnInfo->stIpv6PdnInfo.aucIpV6Addr;

                (VOS_VOID)vos_printf("PDN %d IPv6��ַ:%x:%x:%x:%x:%x:%x:%x:%x \n", ucRabId, VOS_HTONS(pusIpv6[0]), VOS_HTONS(pusIpv6[1]), VOS_HTONS(pusIpv6[2]), VOS_HTONS(pusIpv6[3]), VOS_HTONS(pusIpv6[4]), VOS_HTONS(pusIpv6[5]), VOS_HTONS(pusIpv6[6]), VOS_HTONS(pusIpv6[7]));
                (VOS_VOID)vos_printf("PDN %d IPv6��DNS��Ϣ, bitOpDnsPrim:%d, bitOpDnsPrimCfged%d \n", ucRabId, pstSinglePdnInfo->stIpv6PdnInfo.bitOpDnsPrim, pstSinglePdnInfo->bitOpIpv6DnsPrimCfged);

                pusIpv6 = (VOS_UINT16 *)pstSinglePdnInfo->stIpv6PdnInfo.aucDnsPrimAddr;
                (VOS_VOID)vos_printf("PDN %d IPv6��DNS��ַ:%x:%x:%x:%x:%x:%x:%x:%x \n", ucRabId, VOS_HTONS(pusIpv6[0]), VOS_HTONS(pusIpv6[1]), VOS_HTONS(pusIpv6[2]), VOS_HTONS(pusIpv6[3]), VOS_HTONS(pusIpv6[4]), VOS_HTONS(pusIpv6[5]), VOS_HTONS(pusIpv6[6]), VOS_HTONS(pusIpv6[7]));

                (VOS_VOID)vos_printf("PDN %d IPv6��DNS��Ϣ, bitOpDnsPrim:%d, bitOpDnsPrimCfged:%d \n", ucRabId, pstSinglePdnInfo->stIpv6PdnInfo.bitOpDnsSec, pstSinglePdnInfo->bitOpIpv6DnsSecCfged);

                pusIpv6 = (VOS_UINT16 *)pstSinglePdnInfo->stIpv6PdnInfo.aucDnsSecAddr;
                (VOS_VOID)vos_printf("PDN %d IPv6��DNS��ַ:%x:%x:%x:%x:%x:%x:%x:%x \n", ucRabId, VOS_HTONS(pusIpv6[0]), VOS_HTONS(pusIpv6[1]), VOS_HTONS(pusIpv6[2]), VOS_HTONS(pusIpv6[3]), VOS_HTONS(pusIpv6[4]), VOS_HTONS(pusIpv6[5]), VOS_HTONS(pusIpv6[6]), VOS_HTONS(pusIpv6[7]));
            }
            (VOS_VOID)vos_printf("\n");
        }
    }
}


VOS_VOID IMS_NIC_ShowStats(VOS_VOID)
{
    VOS_INT32                i;


    for (i = 0; i < IMS_NIC_MODEM_ID_BUTT; i++)
    {
        (VOS_VOID)vos_printf("======================Debug info for Modem %d ======================\n", i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_RCV_IPV4_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_RCV_IPV6_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_SEND_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_RCV_BYTES, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_RCV_ERR_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_INPUT_NULL_PTR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DL_RCV_DATA_LEN_ERR, i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_RCV_IPV4_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_RCV_IPV6_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_SEND_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_SEND_BYTES, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_RCV_ERR_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_RCV_ARP_PKT, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_INPUT_NULL_PTR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_RCV_DATA_LEN_ERR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_CB_FUN_NOT_REG, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_CALL_CB_FUN_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_UL_PKT_MEM_SEG, i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_DNS_SERVER_FULL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_INPUT_NULL_PTR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_ADD_MODEM_ID_ERR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_DEL_MODEM_ID_ERR, i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_ADD_RAB_ID_ERR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_DEL_RAB_ID_ERR, i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_GET_CLUSTER_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_GET_CLBLK_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_GET_MBLK_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MBLK_COPY_ERR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_NOT_INITED_ERR, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_SYS_CALL_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_FIND_DEV_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_NO_CFGED_PDN, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_ADD_NO_PDN, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CFG_DEL_NO_PDN, i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MODEM_ID_ERR_OTHER, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MODEM_ID_ERR_IN_REG_CB, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MODE_ID_ERR_IN_DL_PROC, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MODE_ID_ERR_IN_UL_PROC, i);

        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MTU_INVALID, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_INVALID_IPV6_PREFIX_LEN, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MTU_CONFIG_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_PORT_CONFIG_INVALID, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_NETIF_RESET_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DEL_IPV4_ADDR_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_DEL_IPV6_ADDR_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_GET_IF_NAME_BY_INDEX_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_ADD_IPV4_ADDR_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_ADD_IPV6_ADDR_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CONFIG_IPV4_ROUTE_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_CONFIG_IPV6_ROUTE_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_COPY_DATA_FROM_MBUF_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_RESUME_IF_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_SET_STATIC_ARP_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_SET_STATIC_ND_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_ENABLE_HOST_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_ISLUP_SUCC, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_ISLUP_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MATCH_IPV6_ADDR_SUCC, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_MATCH_IPV6_ADDR_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_LOCAL_IPV6_ADDR_SUCC, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_LOCAL_IPV6_ADDR_FAIL, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_HAVE_IPV6_ADDR_SUCC, i);
        IMS_INC_STATS_SHOW(IMS_NIC_STATS_HAVE_IPV6_ADDR_FAIL, i);

        (VOS_VOID)vos_printf("\n\n");
    }
}

#ifdef IMS_NIC_DEBUG
VOS_VOID IMS_NIC_TestSdt(VOS_VOID)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU    stConfigInfo;
    VOS_UINT8                       aucDstIpAddr1[4]            = {0x2, 0x1, 0x15, 0x27};
    VOS_UINT32                      ulResult;
    VOS_UINT8   ucRabId1    = 5;
    char *cmd_str1           = "ifconfig -a";
    char *cmd_str2           = "route -n show";

    VOS_MemSet(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConfigInfo.bitOpIpv4PdnInfo   = PS_TRUE;
    stConfigInfo.bitOpIpv6PdnInfo   = PS_FALSE;
    stConfigInfo.enModemId          = 0;
    stConfigInfo.ucRabId            = ucRabId1;
    VOS_MemCpy(stConfigInfo.stIpv4PdnInfo.aucIpV4Addr, aucDstIpAddr1, 4);

    stConfigInfo.stIpv4PdnInfo.bitOpDnsPrim         = PS_FALSE;
    stConfigInfo.stIpv4PdnInfo.bitOpDnsSec          = PS_FALSE;

    ulResult    = IMS_NIC_PdnInfoConfig (&stConfigInfo);
    if (IMS_NIC_SUCC != ulResult)
    {
        (VOS_VOID)vos_printf("ST_DL_RCV_001: config pdn fail! ulResult = %d\n", ulResult);
        return;
    }

    ipcom_run_cmd(cmd_str1);
    ipcom_run_cmd(cmd_str2);

    /* ɾ�������������� */
    IMS_NIC_PdnInfoDel(stConfigInfo.ucRabId, 0);

    ipcom_run_cmd(cmd_str1);
    ipcom_run_cmd(cmd_str2);

    return;
}
#endif
#endif  /*FEATURE_ON == FEATURE_IMS*/
/*lint -restore */

/*lint +e534*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



