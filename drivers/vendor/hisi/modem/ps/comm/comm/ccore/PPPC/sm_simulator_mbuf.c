



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"

#include "PsLib.h"
#include "PsCommonDef.h"
#include "sm_simulator_mbuf.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_MBUF_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

SM_PGPADAPT_PACKET_INFO_S g_astPgpAdaptPktInfo[SM_PGPADAPT_MBUF_CORR_PKTID_MAX_NUM];

SM_VOID sm_debug_printAll
(
    SM_UCHAR* szFormat,
    ...
)
{
    return;
}

SM_ULONG    g_ulCurMbufIndex = 0;  /* �����Mbuf��ǰ���� */

SM_PGPADAPT_MBUF_INFO_S g_stPgpAdaptMbufInfo = {0};

SM_ULONG    g_ulPktIdIndex = 0;    /* �洢Mbuf��packet id�Ķ�Ӧ��ϵ������ */

extern SM_PGPADAPT_PACKET_INFO_S g_astPgpAdaptPktInfo[];

#define PMBUF_RESV_HEAD_SIZE            (256)
#define PMBUF_DATABLOCK_SIZE(len)       (len + PMBUF_RESV_HEAD_SIZE)

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

ULONG PMBUF_Destroy(PMBUF_S * pstMbuf)
{
    MBUF_DATABLOCKDESCRIPTOR_S         *pstNextDataBlock    = VOS_NULL_PTR;
    MBUF_DATABLOCKDESCRIPTOR_S         *pstTempDataBlock    = VOS_NULL_PTR;


    if (VOS_NULL_PTR == pstMbuf)
    {
        return VOS_ERR;
    }

    /* ��ȡ��һ��DataBlockScriptorָ�� */
    pstNextDataBlock    = pstMbuf->stDataBlockDescriptor.pstNextDataBlockDescriptor;

    /* ����Ҫ�ж�pstNextDataBlock�Ƿ�ΪVOS_NULL_PTR */
    PMBUF_DataBlockDestroy(pstNextDataBlock);
    pstNextDataBlock = VOS_NULL_PTR;

    /* �����ǰDataBlock������ָ�뼰MBUF�ڴ� */
    if (VOS_NULL_PTR != pstMbuf->stDataBlockDescriptor.pucDataBlock)
    {
        PPP_Free(pstMbuf->stDataBlockDescriptor.pucDataBlock);
        pstMbuf->stDataBlockDescriptor.pucDataBlock = VOS_NULL_PTR;
        pstMbuf->stDataBlockDescriptor.pucData= VOS_NULL_PTR;
    }
    PPP_Free(pstMbuf);
    pstMbuf = VOS_NULL_PTR;

    return VOS_OK;
}
PMBUF_S *PMBUF_GetPMbuf(ULONG ulSubMod, ULONG ulMBufLen)
{
    MBUF_DATABLOCKDESCRIPTOR_S         *pstNextDataBlock    = VOS_NULL_PTR;
    MBUF_DATABLOCKDESCRIPTOR_S         *pstCurrDataBlock    = VOS_NULL_PTR;
    PMBUF_S                            *pstMbuf             = VOS_NULL_PTR;
    UCHAR                              *pucTempdata         = VOS_NULL_PTR;
    ULONG                               ulActualLen         = 0;


    /* ����Ϊ0,��������MBUF */
    if (0 == ulMBufLen)
    {
        PPPC_WARNING_LOG("MBufLen is 0, No Need to Alloc Memory!\r\n");
        return VOS_NULL_PTR;
    }

    /* ����MBUFͷ */
    pstMbuf = PPP_Malloc(sizeof(PMBUF_S));
    if (VOS_NULL == pstMbuf)
    {
        PPPC_WARNING_LOG("Malloc PMBUF Fail!\r\n");
        return VOS_NULL_PTR;
    }
    PS_MEM_SET(pstMbuf, 0x0, sizeof(PMBUF_S));

    pstCurrDataBlock            = &(pstMbuf->stDataBlockDescriptor);
    while ((ulMBufLen > 0) && (VOS_NULL_PTR != pstCurrDataBlock))
    {
        if (ulMBufLen > PMBUF_MAX_AVAILABLE_MEM_SIZE)
        {
            ulActualLen         = PMBUF_MAX_AVAILABLE_MEM_SIZE;
            ulMBufLen          -= PMBUF_MAX_AVAILABLE_MEM_SIZE;

            /* ���ݳ��ȴ���һ�ο����������,��Ȼ������һ�� */
            pstNextDataBlock    = (MBUF_DATABLOCKDESCRIPTOR_S *)PPP_Malloc(
                                    sizeof(MBUF_DATABLOCKDESCRIPTOR_S));
            if (VOS_NULL_PTR == pstNextDataBlock)
            {
                PPPC_ERROR_LOG("Malloc DATABLOCKSCRIPTOR Fail!\r\n");
                PMBUF_Destroy(pstMbuf);
                return VOS_NULL_PTR;
            }
            PS_MEM_SET(pstNextDataBlock, 0, sizeof(MBUF_DATABLOCKDESCRIPTOR_S));
        }
        else
        {
            ulActualLen = ulMBufLen;
            ulMBufLen   = 0;

            /* ���ݳ���С�ڵ���һ�ο����������,��Ȼû����һ��,��Ϊ�� */
            pstNextDataBlock = VOS_NULL_PTR;
        }
        pstCurrDataBlock->pstNextDataBlockDescriptor   = pstNextDataBlock;
        (pstMbuf->ulDataBlockNumber)++;

        /* �����ű��ĵ��ڴ� */
        pucTempdata = PPP_Malloc(PMBUF_DATABLOCK_SIZE(ulActualLen));
        if (VOS_NULL == pucTempdata)
        {
            PPPC_WARNING_LOG("Malloc Data Block Fail!\r\n");
            PMBUF_Destroy(pstMbuf);
            return VOS_NULL_PTR;
        }

        PS_MEM_SET(pucTempdata, 0x0, PMBUF_DATABLOCK_SIZE(ulActualLen));
        pstCurrDataBlock->pucDataBlock       = pucTempdata;
        pstCurrDataBlock->ulDataBlockLength  = PMBUF_DATABLOCK_SIZE(ulActualLen);
        pstCurrDataBlock->pucData            = pucTempdata + PMBUF_RESV_HEAD_SIZE;
        pstCurrDataBlock->ulDataLength       = 0;
        pstCurrDataBlock                     = pstNextDataBlock;
    }

    return pstMbuf;
}
ULONG PMBUF_DataBlockDestroy(MBUF_DATABLOCKDESCRIPTOR_S *pstHeadDataBlock)
{
    MBUF_DATABLOCKDESCRIPTOR_S         *pstNextDataBlock    = VOS_NULL_PTR;
    MBUF_DATABLOCKDESCRIPTOR_S         *pstCurrDataBlock    = VOS_NULL_PTR;


    pstCurrDataBlock    = pstHeadDataBlock;

    while (VOS_NULL_PTR != pstCurrDataBlock)
    {
        /* �洢��һ��DataBlockָ�� */
        pstNextDataBlock    = pstCurrDataBlock->pstNextDataBlockDescriptor;

        /* �ͷ������ڴ� */
        if (VOS_NULL_PTR != pstCurrDataBlock->pucDataBlock)
        {
            /* �����ǰ���ݿ��Dataָ�� */
            PPP_Free(pstCurrDataBlock->pucDataBlock);
            pstCurrDataBlock->pucDataBlock  = VOS_NULL_PTR;
            pstCurrDataBlock->pucData       = VOS_NULL_PTR;
        }
        pstCurrDataBlock->ulDataBlockLength = 0;
        pstCurrDataBlock->ulDataLength  = 0;
        pstCurrDataBlock->ulType        = 0;

        /* ��󽫵�ǰ���ݿ�Ҳ���, �ͷ�DataBlock */
        PPP_Free(pstCurrDataBlock);

        pstCurrDataBlock    = pstNextDataBlock;
    }

    return VOS_OK;
}


MBUF_DATABLOCKDESCRIPTOR_S *PMBUF_GetNextDataBlock
(
    ULONG                               ulSubMod,
    ULONG                               ulDataBlockLen,
    ULONG                              *pulBlockNum
)
{
    MBUF_DATABLOCKDESCRIPTOR_S         *pstNextDataBlock    = VOS_NULL_PTR;
    MBUF_DATABLOCKDESCRIPTOR_S         *pstHeadDataBlock    = VOS_NULL_PTR;
    MBUF_DATABLOCKDESCRIPTOR_S         *pstCurrDataBlock    = VOS_NULL_PTR;
    UCHAR                              *pucTempdata         = VOS_NULL_PTR;
    ULONG                               ulActualLen         = 0;


    /* ������ʼ��Ϊ0 */
    *pulBlockNum    = 0;

    /* ����Ϊ0,��������MBUF */
    if (0 == ulDataBlockLen)
    {
        PPPC_WARNING_LOG("ulDataBlockLen is 0, No Need to Alloc Memory!\r\n");
        return VOS_NULL_PTR;
    }


    /* ���ݳ��ȴ���һ�ο����������,��Ȼ������һ�� */
    pstHeadDataBlock    = (MBUF_DATABLOCKDESCRIPTOR_S *)PPP_Malloc(
                            sizeof(MBUF_DATABLOCKDESCRIPTOR_S));
    if (VOS_NULL_PTR == pstHeadDataBlock)
    {
        PPPC_ERROR_LOG("Malloc DATABLOCKSCRIPTOR Fail!\r\n");
        return VOS_NULL_PTR;
    }
    PS_MEM_SET(pstHeadDataBlock, 0, sizeof(MBUF_DATABLOCKDESCRIPTOR_S));

    pstCurrDataBlock    = pstHeadDataBlock;

    while ((ulDataBlockLen > 0) && (VOS_NULL_PTR != pstCurrDataBlock))
    {
        if (ulDataBlockLen > PMBUF_MAX_AVAILABLE_MEM_SIZE)
        {
            ulActualLen         = PMBUF_MAX_AVAILABLE_MEM_SIZE;
            ulDataBlockLen     -= PMBUF_MAX_AVAILABLE_MEM_SIZE;

            /* ���ݳ��ȴ���һ�ο����������,��Ȼ������һ�� */
            pstNextDataBlock    = (MBUF_DATABLOCKDESCRIPTOR_S *)PPP_Malloc(
                                    sizeof(MBUF_DATABLOCKDESCRIPTOR_S));
            if (VOS_NULL_PTR == pstNextDataBlock)
            {
                PPPC_ERROR_LOG("Malloc DATABLOCKSCRIPTOR Fail!\r\n");

                /* ������ʼ��Ϊ0 */
                *pulBlockNum    = 0;

                PMBUF_DataBlockDestroy(pstHeadDataBlock);
                return VOS_NULL_PTR;
            }
            PS_MEM_SET(pstNextDataBlock, 0, sizeof(MBUF_DATABLOCKDESCRIPTOR_S));
        }
        else
        {
            ulActualLen         = ulDataBlockLen;
            ulDataBlockLen      = 0;

            /* ���ݳ���С�ڵ���һ�ο����������,��Ȼû����һ��,��Ϊ�� */
            pstNextDataBlock    = VOS_NULL_PTR;
        }
        pstCurrDataBlock->pstNextDataBlockDescriptor   = pstNextDataBlock;
        (*pulBlockNum)++;

        /* �����ű��ĵ��ڴ� */
        pucTempdata = PPP_Malloc(PMBUF_DATABLOCK_SIZE(ulActualLen));
        if (VOS_NULL == pucTempdata)
        {
            PPPC_WARNING_LOG("Malloc Data Block Fail!\r\n");

            /* ������ʼ��Ϊ0 */
            *pulBlockNum    = 0;

            PMBUF_DataBlockDestroy(pstHeadDataBlock);
            return VOS_NULL_PTR;
        }

        PS_MEM_SET(pucTempdata, 0x0, PMBUF_DATABLOCK_SIZE(ulActualLen));
        pstCurrDataBlock->pucDataBlock       = pucTempdata;
        pstCurrDataBlock->ulDataBlockLength  = PMBUF_DATABLOCK_SIZE(ulActualLen);
        pstCurrDataBlock->pucData            = pucTempdata + PMBUF_RESV_HEAD_SIZE;
        pstCurrDataBlock->ulDataLength       = 0;
        pstCurrDataBlock                     = pstNextDataBlock;
    }

    return pstHeadDataBlock;
}


PF_VOID MBUF_UPDATE_BY_LEN(PMBUF_S* pstMBuf,PF_LONG lLen)
{
    pstMBuf->stDataBlockDescriptor.pucData -= lLen;
    pstMBuf->stDataBlockDescriptor.ulDataLength += lLen;
    pstMBuf->ulTotalDataLength += lLen;

    return;
}

PF_VOID MBUF_UPDATE_BY_LEN_TAIL(PMBUF_S* pstMBuf,PF_LONG lLen)
{
    pstMBuf->stDataBlockDescriptor.ulDataLength += lLen;
    pstMBuf->ulTotalDataLength += lLen;

    return;
}

PF_VOID MBUF_UPDATE_LENGTH(PMBUF_S* pstMBuf,PF_LONG lLen)
{
    pstMBuf->stDataBlockDescriptor.ulDataLength = lLen;
    pstMBuf->ulTotalDataLength = lLen;

    return;
}


VOID PMBUF_ReleasePMbuf(PMBUF_S *pMbuf)
{
    /* ��֧��Mbuf���ͷ� */
    if ((VOS_NULL_PTR == pMbuf) || (pMbuf->pstNextMBuf != VOS_NULL_PTR))
    {
        return;
    }
    sm_pgpAdapt_releaseMbuf(pMbuf);
    return;
}

SM_MBUF_S* PMBUF_DBDescToMbuf(SM_MBUF_DATABLOCKDESCRIPTOR_S *pstDataBlockDescriptor)
{
    SM_MBUF_S *pMbuf = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S *pstCurDataBlockDescriptor;
    ULONG ulBlockNum = 1;
    ULONG ulLen;

    if (pstDataBlockDescriptor == VOS_NULL_PTR)
    {
        return VOS_NULL_PTR;
    }

    ulLen = pstDataBlockDescriptor->ulDataLength;
    pstCurDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;
    while (pstCurDataBlockDescriptor != VOS_NULL_PTR)
    {
        ulBlockNum++;
        ulLen += pstCurDataBlockDescriptor->ulDataLength;
        pstCurDataBlockDescriptor = pstCurDataBlockDescriptor->pstNextDataBlockDescriptor;
    }

    pMbuf = PMBUF_GET_PMBUF_FROM_DBD(pstDataBlockDescriptor);
    pMbuf->ulDataBlockNumber = ulBlockNum;
    pMbuf->ulTotalDataLength = ulLen;

    /* �Ƿ���Mbuf���??? */

    return pMbuf;
}


/*****************************************************************************
 �� �� ��  : PMBUF_PullUp
 ��������  : ��ָ֤����MBUF��(����MBUF)��ulLength�����ݣ�
             ����ʹ���һ��DATA���������������ͷ�����Ϊ�յ�MBUF���ݿ�
             ע�⣬�˺��������MBUFʹ��DBD������������ulLength���ô���2368�ֽ�
 �������  : UCHAR * pstMBuf       ָ��MBUFָ��
             ULONG ulLength,       Ҫ��֤�����ݳ���
             ULONG ulModuleID      ʹ���ߵ�ģ��ID
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  : PMBUF_TAILING_SPACE()
             PMBUF_MIN()
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��6��14��
    ��    ��   : l60020798
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PMBUF_PullUp(SM_MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID)
{
    SM_MBUF_S *pstDelMBuf = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S* pstCurdbd = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S* pstNextdbd = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S* pstTmpdbd = VOS_NULL_PTR;
    ULONG ulTotalLength = 0;  /* ��Ҫ����ĳ��� */
    ULONG ulPullUpLength = 0; /* ���β���ĳ��� */

    /* ��μ�� */
    if (VOS_NULL_PTR == pstMBuf)
    {
        return PMBUF_FAIL;
    }
    /* ���MBUF�е����ݳ����Ѿ����ڵ���Ҫ��ĳ����򷵻سɹ� */
    if (pstMBuf->stDataBlockDescriptor.ulDataLength >= ulLength)
    {
        return PMBUF_OK;
    }

    /* ����ܵ����ݳ��ȶ�����Ҫ��ĳ��ȵĻ����򷵻ش��� */
    if (pstMBuf->ulTotalDataLength < ulLength)
    {
        PPPC_WARNING_LOG2("The total data len is not enough, ulTotalDataLength:%d, ulLength:%d",
            pstMBuf->ulTotalDataLength, ulLength);
        return PMBUF_FAIL;
    }

    /* �����һ��MBUFβ��û���㹻�Ŀռ�Ļ����򷵻ش��� */
    ulTotalLength = ulLength - pstMBuf->stDataBlockDescriptor.ulDataLength;
    if ( ulTotalLength > PMBUF_TAILING_SPACE(pstMBuf) )
    {
        PPPC_WARNING_LOG2("The space is not enough, ulTotalLength:%d, space:%d",
            ulTotalLength, PMBUF_TAILING_SPACE(pstMBuf));
        return PMBUF_FAIL;
    }

    pstCurdbd = &(pstMBuf->stDataBlockDescriptor);
    pstNextdbd = pstMBuf->stDataBlockDescriptor.pstNextDataBlockDescriptor;
    while (ulTotalLength > 0 && pstNextdbd != VOS_NULL_PTR)
    {
        ulPullUpLength = PMBUF_MIN (pstNextdbd->ulDataLength, ulTotalLength);

        VOS_MemCpy((UCHAR*)(pstCurdbd->pucData + pstCurdbd->ulDataLength),
               (UCHAR*)pstNextdbd->pucData, (ULONG)ulPullUpLength);

        ulTotalLength -= ulPullUpLength;
        pstCurdbd->ulDataLength += ulPullUpLength;

        pstNextdbd->ulDataLength -= ulPullUpLength;
        pstNextdbd->pucData += ulPullUpLength;

        if ( 0 == pstNextdbd->ulDataLength )
        {
            pstTmpdbd = pstNextdbd->pstNextDataBlockDescriptor;
            pstCurdbd->pstNextDataBlockDescriptor = pstTmpdbd;
#ifdef __VXWORKS_PLATFORM__
            pstDelMBuf = (PMBUF_S *)PMBUF_DTOM((UCHAR*) pstNextdbd->pucDataBlock);
#else
            pstNextdbd->pstNextDataBlockDescriptor = VOS_NULL_PTR;
            pstDelMBuf = PMBUF_DBDescToMbuf(pstNextdbd);
#endif
            sm_pgpAdapt_releaseMbuf(pstDelMBuf);
            pstMBuf->ulDataBlockNumber --;
            if ( 0 == ulTotalLength )
            {
                break;
            }
            pstNextdbd = pstTmpdbd;
            continue;
        }
        if ( 0 == ulTotalLength )
        {
            break;
        }
    }
    return PMBUF_OK;
}

SM_MBUF_DATABLOCKDESCRIPTOR_S* sm_plt_pmbuf_getTailDBD(SM_MBUF_S * pstMBuf)
{
    SM_MBUF_DATABLOCKDESCRIPTOR_S* pstDataBlockDescriptor = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S* pstCurDataBlockDescriptor = VOS_NULL_PTR;
    if ( VOS_NULL_PTR == pstMBuf )
    {
        return VOS_NULL_PTR;
    }

    for (pstDataBlockDescriptor = &(pstMBuf->stDataBlockDescriptor);
         pstDataBlockDescriptor != VOS_NULL_PTR;
         pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor)
    {
        pstCurDataBlockDescriptor = pstDataBlockDescriptor;
    }
    return pstCurDataBlockDescriptor;
}

SM_MBUF_S * sm_plt_mbufReferenceCopy(SM_MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, ULONG ulModuleID)
{
    SM_MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S * pstNextDataBlockDescriptor = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S * pstTailDataBlockDescriptor = VOS_NULL_PTR;
    SM_MBUF_S* pstNewMbuf = VOS_NULL_PTR;
    SM_MBUF_S* pstHeadMbuf = VOS_NULL_PTR;
    ULONG ulCopyLength = 0;
    VOS_INT32 iHead = 0;/* ��������MBUF�Ѿ���չ��ͷ���������������п��ܴ��ڹ涨�����������ȣ����ֵΪУ��ֵ */

    /* ��μ�� */
    if ( VOS_NULL_PTR == pstMBuf )
    {
        return VOS_NULL_PTR;
    }
    if(ulOffset > pstMBuf->ulTotalDataLength)
    {
        return VOS_NULL_PTR;
    }
    if(ulLength > pstMBuf->ulTotalDataLength - ulOffset)
    {
        return VOS_NULL_PTR;
    }

    /* ͨ��ƫ�����ҵ����ĸ�MBUF��ʼ���� */
    for(pstDataBlockDescriptor = &(pstMBuf->stDataBlockDescriptor);
        ulOffset >= pstDataBlockDescriptor->ulDataLength;
        pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor)
    {
        ulOffset -= pstDataBlockDescriptor->ulDataLength;
        if (VOS_NULL_PTR == pstDataBlockDescriptor->pstNextDataBlockDescriptor)
        {
            break;
        }
    }
    /* �ȴ����µ�MBUF���ĵ�һ����� */
    pstHeadMbuf = sm_pgpAdapt_getMbuf(ulModuleID);
    if ( VOS_NULL_PTR == pstHeadMbuf)
    {
        return VOS_NULL_PTR;
    }

    /* �����û���Ϣ */
    (VOID)VOS_MemCpy((VOID*)(&pstHeadMbuf->stUserTagData),
                       (VOID*)(&pstMBuf->stUserTagData),
                       sizeof(pstMBuf->stUserTagData));
    ulCopyLength = PMBUF_MIN(ulLength, pstDataBlockDescriptor->ulDataLength - ulOffset);
    iHead = (VOS_INT32)(pstDataBlockDescriptor->pucData - (pstDataBlockDescriptor->pucDataBlock + 512));
    /* �������� */
    (VOID)VOS_MemCpy(pstHeadMbuf->stDataBlockDescriptor.pucData + iHead,
                       pstDataBlockDescriptor->pucData + ulOffset ,
                       ulCopyLength);
    pstHeadMbuf->stDataBlockDescriptor.pucData += iHead;
    pstHeadMbuf->stDataBlockDescriptor.ulDataLength = ulCopyLength;
    pstHeadMbuf->ulTotalDataLength = ulLength;
    ulOffset = 0;
    ulLength = ulLength - ulCopyLength;
    if ( 0 == ulLength )
    {
        return pstHeadMbuf;
    }
    /* ���һ�����ݿ�Ϳ��Ը㶨�Ļ���ֱ�ӷ����µ�MBUF */
    if ( VOS_NULL_PTR == pstDataBlockDescriptor->pstNextDataBlockDescriptor)
    {
        return pstHeadMbuf;
    }
    pstNextDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;
    while ( (pstNextDataBlockDescriptor != VOS_NULL_PTR)&& (ulLength > 0))
    {
        pstNewMbuf = sm_pgpAdapt_getMbuf(ulModuleID);
        if ( VOS_NULL_PTR == pstNewMbuf)
        {
            sm_pgpAdapt_releaseMbuf(pstMBuf);
            return VOS_NULL_PTR;
        }
        pstHeadMbuf->ulDataBlockNumber ++;
        ulCopyLength = PMBUF_MIN(ulLength, pstNextDataBlockDescriptor->ulDataLength);

        iHead = (VOS_INT32)(pstNextDataBlockDescriptor->pucData - (pstNextDataBlockDescriptor->pucDataBlock + 512));
        (VOID)VOS_MemCpy(pstNewMbuf->stDataBlockDescriptor.pucData + iHead,
                           pstNextDataBlockDescriptor->pucData ,
                           ulCopyLength);
        pstNewMbuf->stDataBlockDescriptor.pucData += iHead;
        pstNewMbuf->stDataBlockDescriptor.ulDataLength = ulCopyLength;
        ulLength = ulLength - ulCopyLength;

        /* ���� */
        pstTailDataBlockDescriptor = sm_plt_pmbuf_getTailDBD(pstHeadMbuf);
        if ( VOS_NULL_PTR == pstTailDataBlockDescriptor)
        {
            sm_pgpAdapt_releaseMbuf(pstMBuf);
            sm_pgpAdapt_releaseMbuf(pstNewMbuf);
            return VOS_NULL_PTR;
        }
        pstTailDataBlockDescriptor->pstNextDataBlockDescriptor = &(pstNewMbuf->stDataBlockDescriptor);
        if (0 == ulLength)
        {
            break;
        }
        /* ȡ��һ��MBUF */
        pstNextDataBlockDescriptor = pstNextDataBlockDescriptor->pstNextDataBlockDescriptor;
    }
    return pstHeadMbuf;
}


/*****************************************************************************
 �� �� ��  : PMBUF_CutHeadInMultiDataBlock
 ��������  : ��ͷ����ʼ�ڶ�����ݿ����г�����,�����MBUF���ݿ鳤��Ϊ0�������ͷ�
 �������  : PMBUF_S * pstMBuf
             ULONG ulLength
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��7��19��
    ��    ��   : l60020798
    �޸�����   : �Ϻ�����û���޸ģ����˸�����ͷ����

*****************************************************************************/
VOID PMBUF_CutHeadInMultiDataBlock(PMBUF_S * pstMBuf, ULONG ulLength)
{
    ULONG ulMyLength = 0;
    SM_MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor = VOS_NULL_PTR;

    /*pstMBuf has been checked by caller*/
    /*the following code can process the situation that ulLength > pstMBuf->ulTotalDataLength*/
    if (VOS_NULL_PTR == pstMBuf)
    {
        return;
    }

    ulMyLength = (ulLength);
    pstDataBlockDescriptor = &((pstMBuf)->stDataBlockDescriptor);
    while(pstDataBlockDescriptor != VOS_NULL_PTR)
    {
        if(pstDataBlockDescriptor->ulDataLength <= ulMyLength)
        {
            ulMyLength -= pstDataBlockDescriptor->ulDataLength;
            pstDataBlockDescriptor->pucData += pstDataBlockDescriptor->ulDataLength;
            pstDataBlockDescriptor->ulDataLength = 0;

            /*next*/
            pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;
        }
        else
        {
            pstDataBlockDescriptor->ulDataLength -= ulMyLength;
            pstDataBlockDescriptor->pucData += ulMyLength;
            ulMyLength = 0;
            break;
        }
    }
    /*whether terminate from break or the loop, the following is OK.*/
    pstMBuf->ulTotalDataLength -= ((ulLength) - ulMyLength);
    return ;
}



/*****************************************************************************
 �� �� ��  : PMBUF_CopyDataFromPMBufToBuffer
 ��������  : ��MBUF�е����ݿ�����BUFFER��
 �������  : PMBUF_S * pstMBuf
             ULONG ulOffset
             ULONG ulLength
             UCHAR * pucBuffer
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��7��19��
    ��    ��   : l60020798
    �޸�����   : �Ϻ�����û���޸ģ����˺���ͷ����

*****************************************************************************/
ULONG PMBUF_CopyDataFromPMBufToBuffer(SM_MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, UCHAR * pucBuffer)
{
    SM_MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor;
    ULONG ulCopyLength;

    if(pstMBuf == VOS_NULL_PTR)
    {
        return PMBUF_FAIL;
    }
    if(pucBuffer == VOS_NULL_PTR)
    {
        return PMBUF_FAIL;
    }
    if(ulOffset > pstMBuf->ulTotalDataLength)
    {
        return PMBUF_FAIL;
    }
    if(ulLength > pstMBuf->ulTotalDataLength - ulOffset)
    {
        return PMBUF_FAIL;
    }
    if(ulLength == 0)
    {
        return PMBUF_OK;
    }
    for(pstDataBlockDescriptor = &(pstMBuf->stDataBlockDescriptor);\
        ulOffset >= pstDataBlockDescriptor->ulDataLength;\
        pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor)
    {
        ulOffset -= pstDataBlockDescriptor->ulDataLength;
        if (VOS_NULL_PTR == pstDataBlockDescriptor->pstNextDataBlockDescriptor)
        {
           return PMBUF_FAIL;
        }
    }
    while(ulLength > 0 )
    {
        ulCopyLength = PMBUF_MIN(pstDataBlockDescriptor->ulDataLength - ulOffset, ulLength);
        (VOID)VOS_MemCpy(pucBuffer, pstDataBlockDescriptor->pucData + ulOffset, ulCopyLength);

        ulLength -= ulCopyLength;
        pucBuffer += ulCopyLength;
        ulOffset = 0;
        if ( 0 == ulLength )
        {
            break;
        }
        pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;
        if (VOS_NULL_PTR == pstDataBlockDescriptor)
        {
            return PMBUF_FAIL;
        }
    }
    return PMBUF_OK;
}



/*****************************************************************************
 �� �� ��  : PMBUF_CopyDataFromBufferToPMBuf
 ��������  : ��BUF���ݿ�����MBUFָ��λ��,�����16K����
             �����µ�MBUF����ʹ��DBD��������MBUF��
 �������  : PMBUF_S * pstMBuf   ָ��MBUFָ��
             ULONG ulOffset     MBUF�е�ƫ��
             ULONG ulLength     ���ݳ���
             UCHAR * pucBuffer  BUF
             ULONG ulModuleID
 �������  : ��
 �� �� ֵ  : �ɹ�����MBUF_OK;ʧ�ܷ���MBUF_FAIL;
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��7��4��
    ��    ��   : l60020798
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG PMBUF_CopyDataFromBufferToPMBuf(SM_MBUF_S * pstMBuf, ULONG ulOffset,
                              ULONG ulLength, UCHAR * pucBuffer, ULONG ulModuleID)
{
    ULONG                               ulCopyLength                = 0;
    ULONG                               ulTotalLength               = 0;
    ULONG                               ulDataLength                = 0;
    ULONG                               ulBlockNum                  = 0;
    ULONG                               ulSurplusDBDNum             = 0;
    SM_MBUF_DATABLOCKDESCRIPTOR_S      *pstDataBlockDescriptor      = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S      *pstTemDataBlockDescriptor   = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S      *pstLastDataBlockDescriptor  = VOS_NULL_PTR;


    /* ��μ�� */
    if( 0 == ulLength )
    {
        return PMBUF_OK;
    }
    if(( VOS_NULL_PTR == pstMBuf )||( VOS_NULL_PTR == pucBuffer ))
    {
        return PMBUF_FAIL;
    }
    if(ulOffset > pstMBuf->ulTotalDataLength)
    {
        return PMBUF_FAIL;
    }

    /* ��֧����MBUFͷָ�������ӵ�MBUF */
    if ( VOS_NULL_PTR != pstMBuf->pstNextMBuf )
    {
        return PMBUF_FAIL;
    }

    /*buff������ֻ����16k�ֽڣ���������ݽ������� */
    if ( ulLength > 16*1024 )
    {
        ulLength = 16*1024;
    }
    ulTotalLength = ulLength + ulOffset;

    /* �õ��׸�MBUF�����ݿ�ָ�� */
    pstDataBlockDescriptor = &(pstMBuf->stDataBlockDescriptor);

    /* ͨ��ƫ�����ҵ���һ��Ҫ������MBUF,Ҳ�������һ���ǿյ�DataBlock */
    while (VOS_NULL_PTR != pstDataBlockDescriptor)
    {
        if (ulOffset > pstDataBlockDescriptor->ulDataLength)
        {
            if ( VOS_NULL_PTR == pstDataBlockDescriptor->pstNextDataBlockDescriptor )
            {
                /* ulOffset��ulDataLength����һ��DataBlockȴ�Ѿ���Ϊ�쳣����,
                   �Ѿ������������������,ֱ�ӷ����쳣�˳� */
                return PMBUF_FAIL;
            }

            ulOffset -= pstMBuf->stDataBlockDescriptor.ulDataLength;
            pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;
        }
        else if (ulOffset == pstDataBlockDescriptor->ulDataLength)
        {
            if (ulOffset == 0)
            {
                pstLastDataBlockDescriptor  = pstDataBlockDescriptor;
                break;
            }

            ulOffset -= pstMBuf->stDataBlockDescriptor.ulDataLength;

            /* ulOffset��ulDataLength��ͬ,����һ��Ϊ��ʱ������DataBlock */
            if (VOS_NULL_PTR == pstDataBlockDescriptor->pstNextDataBlockDescriptor)
            {
                ulDataLength
                    = PS_MIN(ulLength, PMBUF_MAX_AVAILABLE_MEM_SIZE);
                pstLastDataBlockDescriptor
                    = (SM_MBUF_DATABLOCKDESCRIPTOR_S *)PMBUF_GetNextDataBlock(
                        ulModuleID, ulDataLength, &ulBlockNum);
                if (VOS_NULL_PTR == pstLastDataBlockDescriptor)
                {
                    return PMBUF_FAIL;
                }
                pstDataBlockDescriptor->pstNextDataBlockDescriptor = pstLastDataBlockDescriptor;

                pstMBuf->ulDataBlockNumber += ulBlockNum;
            }
            else
            {
                pstLastDataBlockDescriptor  = pstDataBlockDescriptor->pstNextDataBlockDescriptor;
            }

            break;
        }
        else
        {
            /* offset=0��ǰDataBlock���ܴ������ʱ�Ӵ˴��˳� */
            pstLastDataBlockDescriptor  = pstDataBlockDescriptor;
            break;
        }
    }


    /* �����ݿ�����MBUF�� */
    while (ulLength > 0)
    {
        ULONG ulUsableLength = 0;
        ulUsableLength = (ULONG)(pstLastDataBlockDescriptor->pucDataBlock
                        + pstLastDataBlockDescriptor->ulDataBlockLength
                        - pstLastDataBlockDescriptor->pucData
                        - ulOffset);

        ulCopyLength = PMBUF_MIN(ulUsableLength, ulLength);

        (VOID)VOS_MemCpy((UCHAR*)(pstLastDataBlockDescriptor->pucData) + ulOffset,
                          pucBuffer, ulCopyLength);

        ulLength    -= ulCopyLength;
        pucBuffer   += ulCopyLength;

        /* �����������ݳ���,�û���Ϊ�����ݳ���Ӧ���ǿ����ĳ���+ƫ����Ԥ���ĳ��� */
        pstLastDataBlockDescriptor->ulDataLength = ulCopyLength + ulOffset;
        ulOffset = 0;

        /* ������ο����Ѿ������ȫ�������ݿ��������˳�ѭ�� */
        if (0 == ulLength)
        {
            break;
        }
        /* �������û�п����꣬���Һ�����MBUF��Ϊ�յĻ�����������MBUF */
        if (VOS_NULL_PTR == pstLastDataBlockDescriptor->pstNextDataBlockDescriptor)
        {
            ulDataLength
                = PS_MIN(ulLength, PMBUF_MAX_AVAILABLE_MEM_SIZE);
            pstTemDataBlockDescriptor
                = (SM_MBUF_DATABLOCKDESCRIPTOR_S *)PMBUF_GetNextDataBlock(
                    ulModuleID, ulDataLength, &ulBlockNum);
            if (VOS_NULL_PTR == pstTemDataBlockDescriptor)
            {
                return PMBUF_FAIL;
            }
            pstLastDataBlockDescriptor->pstNextDataBlockDescriptor
                = pstTemDataBlockDescriptor;
            pstMBuf->ulDataBlockNumber += ulBlockNum;
        }

        pstLastDataBlockDescriptor
            = pstLastDataBlockDescriptor->pstNextDataBlockDescriptor;
    }

    pstTemDataBlockDescriptor = pstLastDataBlockDescriptor->pstNextDataBlockDescriptor;
    while( VOS_NULL_PTR != pstTemDataBlockDescriptor )
    {
        ulSurplusDBDNum++;
        pstTemDataBlockDescriptor = pstTemDataBlockDescriptor->pstNextDataBlockDescriptor;
    }
    /* ���MBUF ulLength�Ժ���DBD�� ��������ɾ�� */
    if( VOS_NULL_PTR != pstLastDataBlockDescriptor->pstNextDataBlockDescriptor )
    {
        PMBUF_DataBlockDestroy(pstLastDataBlockDescriptor->pstNextDataBlockDescriptor);
    }

    pstMBuf->ulDataBlockNumber = pstMBuf->ulDataBlockNumber - ulSurplusDBDNum;
    pstLastDataBlockDescriptor->pstNextDataBlockDescriptor = VOS_NULL_PTR;

    /* ���������ܳ��� */
    pstMBuf->ulTotalDataLength = ulTotalLength;

    return PMBUF_OK;
}

ULONG PMBUF_CutTail(SM_MBUF_S * pstMBuf, ULONG ulLength)
{
    ULONG ulSurplusLength = 0;
    ULONG ulCutDataBlockNumber = 0;
    SM_MBUF_S* pstRelMbuf = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S * pstNextDataBlockDescriptor = VOS_NULL_PTR;

    if ( VOS_NULL_PTR == pstMBuf )
    {
        return PMBUF_FAIL;
    }

    if (0 == ulLength)
    {
        return PMBUF_OK;
    }

    if (ulLength > pstMBuf->ulTotalDataLength )
    {
        return PMBUF_FAIL;
    }
    /* �޸�MBUF�������ĳ���Ϊʣ�೤�� */
    ulSurplusLength = pstMBuf->ulTotalDataLength - ulLength;
    pstMBuf->ulTotalDataLength = ulSurplusLength;

    /*ulSurplusLength ����Ϊƫ�����������ҵ����ĸ�MBUF��ʼ�Ѻ�������ݽ�ȡ�� */
    pstDataBlockDescriptor = &(pstMBuf->stDataBlockDescriptor);
    while ( ulSurplusLength > pstDataBlockDescriptor->ulDataLength )
    {
        ulSurplusLength -= pstDataBlockDescriptor->ulDataLength;
        if (VOS_NULL_PTR == pstDataBlockDescriptor->pstNextDataBlockDescriptor)
        {
            return PMBUF_FAIL;
        }

        pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;
    }
    pstDataBlockDescriptor->ulDataLength = ulSurplusLength;

    pstNextDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;
    pstDataBlockDescriptor->pstNextDataBlockDescriptor = VOS_NULL_PTR;/* �ƻ�ԭ����DBD�� */
    pstDataBlockDescriptor = pstNextDataBlockDescriptor;
    /* ��ʼ�ͷź����MBUF */
    while ( pstDataBlockDescriptor != VOS_NULL_PTR )
    {
        pstNextDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;

        pstDataBlockDescriptor->pstNextDataBlockDescriptor = VOS_NULL_PTR;
        pstRelMbuf = PMBUF_DBDescToMbuf(pstDataBlockDescriptor);

        sm_pgpAdapt_releaseMbuf(pstRelMbuf);
        ulCutDataBlockNumber ++;
        pstDataBlockDescriptor = pstNextDataBlockDescriptor;
    }
    /* ����MBUF���ݿ�ĸ��� */
    pstMBuf->ulDataBlockNumber -= ulCutDataBlockNumber;
    return PMBUF_OK;

}

SM_ULONG sm_plt_concatenateMbuf(SM_MBUF_S * pstDestinationMBuf, SM_MBUF_S * pstSourceMBuf, SM_ULONG ulModuleID)
{
    SM_MBUF_DATABLOCKDESCRIPTOR_S *pstDataBlockDescriptor = VOS_NULL_PTR;

    /* ��μ�� */
    if ( (VOS_NULL_PTR == pstDestinationMBuf) || (VOS_NULL_PTR == pstSourceMBuf) )
    {
        return PMBUF_FAIL;
    }

    if (pstDestinationMBuf == pstSourceMBuf)
    {
        return PMBUF_FAIL;
    }

    for ( pstDataBlockDescriptor = &(pstDestinationMBuf->stDataBlockDescriptor);\
        pstDataBlockDescriptor->pstNextDataBlockDescriptor != VOS_NULL_PTR;\
        pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor )
    {
        /* �ҵ����һ��MBUF */
    }
    pstDataBlockDescriptor->pstNextDataBlockDescriptor = &pstSourceMBuf->stDataBlockDescriptor;
    pstDestinationMBuf->ulTotalDataLength += pstSourceMBuf->ulTotalDataLength;
    pstDestinationMBuf->ulDataBlockNumber += pstSourceMBuf->ulDataBlockNumber;
    pstSourceMBuf->ulTotalDataLength = 0;
    pstSourceMBuf->ulDataBlockNumber = 1;
    return PMBUF_OK;
}


SM_MBUF_DATABLOCKDESCRIPTOR_S* sm_plt_getTailDBDMbuf(SM_MBUF_S * pstMBuf)
{
    SM_MBUF_DATABLOCKDESCRIPTOR_S* pstDataBlockDescriptor = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S* pstCurDataBlockDescriptor = VOS_NULL_PTR;
    if ( VOS_NULL_PTR == pstMBuf )
    {
        return VOS_NULL_PTR;
    }

    for (pstDataBlockDescriptor = &(pstMBuf->stDataBlockDescriptor);
         pstDataBlockDescriptor != VOS_NULL_PTR;
         pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor)
    {
        pstCurDataBlockDescriptor = pstDataBlockDescriptor;
    }
    return pstCurDataBlockDescriptor;
}


ULONG sm_plt_neatConcatenateMbuf(SM_MBUF_S * pstDestinationMBuf, SM_MBUF_S * pstSourceMBuf,
                                 SM_MBUF_DATABLOCKDESCRIPTOR_S ** ppstLastDataBlockDescriptor,
                                 SM_ULONG ulModuleID)
{
    SM_MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S * pstNextDataBlockDescriptor = VOS_NULL_PTR;
    SM_MBUF_S * pstRealMBUF = VOS_NULL_PTR;
    SM_ULONG ulRemainingSpace = 0;

    /* ��μ�� */
    if ((VOS_NULL_PTR == pstDestinationMBuf) || (VOS_NULL_PTR == pstSourceMBuf) || (VOS_NULL_PTR == ppstLastDataBlockDescriptor) )
    {
        return PMBUF_FAIL;
    }

    if (pstDestinationMBuf == pstSourceMBuf)
    {
        return PMBUF_FAIL;
    }

    /* Ѱ��Ŀ��MBUF�����һ��DBD */
    for (pstDataBlockDescriptor = &(pstDestinationMBuf->stDataBlockDescriptor);
         pstDataBlockDescriptor->pstNextDataBlockDescriptor != VOS_NULL_PTR;
         pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor)
    {
        /* do noting */
    }


    pstDataBlockDescriptor->pstNextDataBlockDescriptor = &(pstSourceMBuf->stDataBlockDescriptor);
    pstDestinationMBuf->ulTotalDataLength += pstSourceMBuf->ulTotalDataLength;
    pstDestinationMBuf->ulDataBlockNumber += pstSourceMBuf->ulDataBlockNumber;
    pstSourceMBuf->ulTotalDataLength = 0;
    pstSourceMBuf->ulDataBlockNumber = 1;

    while(pstDataBlockDescriptor->pstNextDataBlockDescriptor != VOS_NULL_PTR)
    {
        pstNextDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;
        /* ����β��ʣ��ռ� */
        ulRemainingSpace = (ULONG)(pstDataBlockDescriptor->pucDataBlock + pstDataBlockDescriptor->ulDataBlockLength
                           - (pstDataBlockDescriptor->pucData + pstDataBlockDescriptor->ulDataLength));
        if((pstDataBlockDescriptor->ulType == pstNextDataBlockDescriptor->ulType)
           && (ulRemainingSpace >= pstNextDataBlockDescriptor->ulDataLength)
           && (pstNextDataBlockDescriptor->ulDataLength < MBUF_TOO_SMALL_LENGTH))
        {
            (VOID)VOS_MemCpy(pstDataBlockDescriptor->pucData + pstDataBlockDescriptor->ulDataLength,
                               pstNextDataBlockDescriptor->pucData,
                               pstNextDataBlockDescriptor->ulDataLength);

            pstDataBlockDescriptor->ulDataLength += pstNextDataBlockDescriptor->ulDataLength;

            pstDataBlockDescriptor->pstNextDataBlockDescriptor = pstNextDataBlockDescriptor->pstNextDataBlockDescriptor;

            pstNextDataBlockDescriptor->pstNextDataBlockDescriptor = VOS_NULL_PTR;
            /* �ҵ���������ΪNULL��MBUFͷ */
            pstRealMBUF = PMBUF_DBDescToMbuf(pstNextDataBlockDescriptor);
            /* �ͷŵ�MBUF*/
            sm_pgpAdapt_releaseMbuf(pstRealMBUF);
            pstDestinationMBuf->ulDataBlockNumber --;
        }
        else
        {
            /* ȡ��һ��MBUF������ */
            pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;
        }
    }
    /* for the last one */
    * ppstLastDataBlockDescriptor = sm_plt_getTailDBDMbuf(pstDestinationMBuf);
    return PMBUF_OK;
}

SM_MBUF_S* sm_plt_createForControlPacket(SM_ULONG ulReserveHeadSpace, SM_ULONG ulLength,
                                         SM_ULONG ulType, SM_ULONG ulModuleID)
{
    SM_MBUF_S* pstMBuf = VOS_NULL_PTR;

    /* Ԥ���Ŀռ�+���ݳ��� > MBUF��������󳤶� */
    if( (ulReserveHeadSpace > PMBUF_DATA_MAXLEN)
        || (ulLength > PMBUF_DATA_MAXLEN)
        || (ulReserveHeadSpace + ulLength > PMBUF_DATA_MAXLEN) )
    {
        return VOS_NULL_PTR;
    }

    /* ����һ��MBUF */
    pstMBuf = sm_pgpAdapt_getMbuf(ulModuleID);
    if( VOS_NULL_PTR == pstMBuf )
    {
        return VOS_NULL_PTR;
    }

    /* ����MBUF�����Ϣ */
    pstMBuf->stDataBlockDescriptor.ulType = ulType;
    pstMBuf->stDataBlockDescriptor.pstNextDataBlockDescriptor = VOS_NULL_PTR;
    pstMBuf->stDataBlockDescriptor.pucData = pstMBuf->stDataBlockDescriptor.pucData + ulReserveHeadSpace;
    pstMBuf->stDataBlockDescriptor.ulDataLength = 0;

    pstMBuf->ulTotalDataLength = pstMBuf->stDataBlockDescriptor.ulDataLength;
    pstMBuf->ulDataBlockNumber = 1;

    /* ��֤�����mbuf��һ�������Ľ�� */
    pstMBuf->pstNextMBuf = VOS_NULL_PTR;

    return pstMBuf;
}

SM_MBUF_DATABLOCKDESCRIPTOR_S * sm_plt_CreateDBDescriptorAndDB(SM_ULONG ulDataBlockLength,
                                                               SM_ULONG ulType,
                                                               SM_ULONG ulModuleID)
{
    SM_MBUF_S* pstMbuf = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S* pstMbufDataDescriptor = VOS_NULL_PTR;

    /* ��μ�� */
    if ( ulDataBlockLength > PMBUF_DATA_SIZE)
    {
        return VOS_NULL_PTR;
    }

    /* ������һ��MBUF */
    pstMbuf = sm_pgpAdapt_getMbuf(ulModuleID);
    if ( VOS_NULL_PTR == pstMbuf )
    {
        return VOS_NULL_PTR;
    }

    /* ���������Ϣ */
    pstMbufDataDescriptor = (&pstMbuf->stDataBlockDescriptor);
    pstMbufDataDescriptor->pstNextDataBlockDescriptor = VOS_NULL_PTR;
    pstMbufDataDescriptor->ulType = ulType;

    return pstMbufDataDescriptor;
}

SM_UCHAR *sm_plt_AppendMemorySpace(SM_MBUF_S * pstMBuf, SM_ULONG ulLength, SM_ULONG ulModuleID)
{
    SM_MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor = VOS_NULL_PTR;
    UCHAR * pucAppending = VOS_NULL_PTR;
    SM_ULONG ulType = 0;

    if (VOS_NULL_PTR == pstMBuf)
    {
        return VOS_NULL_PTR;
    }
    if(ulLength > PMBUF_DATA_MAXLEN)
    {
        return VOS_NULL_PTR;
    }

    ulType = pstMBuf->stDataBlockDescriptor.ulType;

    /* �ҵ����һ��DBD */
    for(pstDataBlockDescriptor = &pstMBuf->stDataBlockDescriptor;\
        pstDataBlockDescriptor->pstNextDataBlockDescriptor != VOS_NULL_PTR;\
        pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor)
    {
    }
    if(ulLength == 0)
    {
        return (pstDataBlockDescriptor->pucData + pstDataBlockDescriptor->ulDataLength);
    }

    /* ���β���ռ䲻��Ļ���������һ����������Ϊ�յ�MBUF���û�ʹ�� */
    if((SM_ULONG)(pstDataBlockDescriptor->pucDataBlock + pstDataBlockDescriptor->ulDataBlockLength \
        - (pstDataBlockDescriptor->pucData + pstDataBlockDescriptor->ulDataLength) ) < ulLength)
    {
        pstDataBlockDescriptor->pstNextDataBlockDescriptor
            = sm_plt_CreateDBDescriptorAndDB(PMBUF_DATA_MAXLEN + PMBUF_TRANSMIT_RESERVED_SIZE,
                                             ulType, ulModuleID);
        if( pstDataBlockDescriptor->pstNextDataBlockDescriptor == VOS_NULL_PTR)
        {
            return VOS_NULL_PTR;
        }
        pstMBuf->ulDataBlockNumber ++;
        /* ʹpstDataBlockDescriptor Ϊ���һ�����ݿ��ָ�� */
        pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;

        pstDataBlockDescriptor->ulDataLength = ulLength;
        pucAppending = pstDataBlockDescriptor->pucData;
        pstMBuf->ulTotalDataLength += ulLength;
        return pucAppending;
    }
    else
    {
        pucAppending = pstDataBlockDescriptor->pucData + pstDataBlockDescriptor->ulDataLength;
        pstDataBlockDescriptor->ulDataLength += ulLength;
        pstMBuf->ulTotalDataLength += ulLength;
    }


    return (pucAppending);
}

SM_ULONG sm_simulatort_releasembufandDatablack(SM_MBUF_S *pPFData )
{
    SM_MBUF_S *pstMBuf = SM_NULL_PTR;
    if ( pPFData == SM_NULL_PTR )
    {
        return SM_RET_ERR;
    }
    if ( pPFData->ulDataBlockNumber > 1 )
    {
        PMBUF_S *pstMBuf = VOS_NULL_PTR;
        PMBUF_DATABLOCKDESCRIPTOR_S *pstDataBlockDescriptor = VOS_NULL_PTR;
        SM_UCHAR *pucData = VOS_NULL_PTR;
        SM_ULONG ulTotalDataLength = 0;
        SM_ULONG ulDataLength = 0;

        pstDataBlockDescriptor = &pPFData->stDataBlockDescriptor;
        while ( SM_NULL_PTR != pstDataBlockDescriptor)
        {
            pstMBuf = (PMBUF_S *)(pstDataBlockDescriptor->pucDataBlock - sizeof(PMBUF_S));
            pstDataBlockDescriptor =  pstDataBlockDescriptor->pstNextDataBlockDescriptor;
            pstMBuf->stDataBlockDescriptor.pstNextDataBlockDescriptor = VOS_NULL_PTR;
            sm_pgpAdapt_releaseMbuf(pstMBuf);
        }
    }
    else
    {
        sm_pgpAdapt_releaseMbuf(pPFData);
    }
    return SM_RET_OK;
}
SM_ULONG sm_simulatort_pmbuf_cutpartforwin32(SM_MBUF_S * pstMBuf, SM_ULONG ulOffset, SM_ULONG ulLength)
{
    SM_MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor = VOS_NULL_PTR;
    SM_MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptorFirstCut = VOS_NULL_PTR;
    SM_ULONG ulCutLength = 0;
    SM_ULONG ulOriginalLength = 0;

    if(pstMBuf == VOS_NULL_PTR)
    {
        return SM_RET_ERR;
    }
    if(ulOffset > pstMBuf->ulTotalDataLength)
    {
        return SM_RET_ERR;
    }
    if(ulLength > pstMBuf->ulTotalDataLength - ulOffset)
    {
        return SM_RET_ERR;
    }

    if(ulLength == 0)/*ulOffset == ulTotalDataLength*/
    {
        return SM_RET_OK;
    }

    ulOriginalLength = ulLength;
    pstDataBlockDescriptor = &(pstMBuf->stDataBlockDescriptor);
    /*find the DB*/
    while( ulOffset >= pstDataBlockDescriptor->ulDataLength)
    {
            ulOffset -= pstDataBlockDescriptor->ulDataLength;
            if (VOS_NULL_PTR == pstDataBlockDescriptor->pstNextDataBlockDescriptor)
            {
                return SM_RET_ERR;
            }
             pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;
    }
    /*ulOffset < pstDataBlockDescriptor->ulDataLength*/
    pstDataBlockDescriptorFirstCut = pstDataBlockDescriptor;
    while(ulLength > 0)
    {
        ulCutLength = PMBUF_MIN(pstDataBlockDescriptor->ulDataLength - ulOffset, ulLength);
        ulLength -= ulCutLength;
        if(ulLength == 0)
        {
            /*cut end*/
            if(pstDataBlockDescriptor == pstDataBlockDescriptorFirstCut && ulOffset != 0)
            {
                /*move*/
                (VOID)VOS_MemCpy(pstDataBlockDescriptor->pucData + ulOffset,
                                     pstDataBlockDescriptor->pucData + ulOffset + ulCutLength,
                                     pstDataBlockDescriptor->ulDataLength - (ulOffset + ulCutLength));

                pstMBuf->ulTotalDataLength -= ulOriginalLength;
                pstDataBlockDescriptor->ulDataLength -= ulCutLength;
                return SM_RET_OK;
            }/*move*/
            else
            {
                /*need not move*/
                pstDataBlockDescriptor->ulDataLength -= ulCutLength;
                pstDataBlockDescriptor->pucData += ulCutLength;
                pstMBuf->ulTotalDataLength -= ulOriginalLength;
                return SM_RET_OK;
            }
        }

        /*cut next*/
        pstDataBlockDescriptor->ulDataLength -= ulCutLength;
        ulOffset = 0;
        pstDataBlockDescriptor = pstDataBlockDescriptor->pstNextDataBlockDescriptor;
        if (VOS_NULL_PTR == pstDataBlockDescriptor)
        {
            return SM_RET_ERR;
        }
    }/*while, never exit from here */
    /*never come here*/
    pstMBuf->ulTotalDataLength -= ulOriginalLength;
    return SM_RET_OK;
}





SM_VOID sm_pgpAdapt_setMbufMsgCode
(
    PMBUF_S* pstMbuf,
    SM_ULONG ulMsgCode
)
{
    SM_ULONG *pulMsgCode = 0;

    pulMsgCode = ((SM_ULONG *)(pstMbuf->stDataBlockDescriptor.pucData)) - 1;

    *pulMsgCode = ulMsgCode;

}


SM_ULONG sm_pgpAdapt_getMbufMsgCode
(
    PMBUF_S* pstMbuf
)
{
    SM_ULONG *pulMsgCode = 0;

    pulMsgCode = (SM_ULONG *)(pstMbuf->stDataBlockDescriptor.pucData) - 1;

    return *pulMsgCode;
}

/*****************************************************************************
 �� �� ��  : _pgpAdapt_clearLinkInMbufAndPktid
 ��������  : ���Mbuf��pkt Id�Ķ�Ӧ��ϵ
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  : sm_pgpAdapt_releaseMbuf

 �޸���ʷ      :
  1.��    ��   : 2010��12��22��
    ��    ��   : jinhua
    �޸�����   : �����ɺ���
*****************************************************************************/
SM_VOID _pgpAdapt_clearLinkInMbufAndPktid
(
    IN      SM_ULONG    ulPacketId
)
{
    SM_PGPADAPT_PACKET_INFO_S* pstPgpAdaptPktInfo = SM_NULL_PTR;
    SM_ULONG ulPacketIndex = 0;

    /* ��Ϊ�����±��0��ʼ��Packet Id��1��ʼ����Ҫ��1*/
    ulPacketIndex = ulPacketId - 1;

    pstPgpAdaptPktInfo = (SM_PGPADAPT_PACKET_INFO_S*)&(g_astPgpAdaptPktInfo);

    pstPgpAdaptPktInfo[ulPacketIndex].pstMbuf = SM_NULL_PTR;
    pstPgpAdaptPktInfo[ulPacketIndex].ulPacketId = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : sm_pgpAdapt_findFreeMbuf
 ��������  : ��ȫ�ֱ����в��ҷ�ʹ��̬��Mbuf
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  : sm_pgpAdapt_getPktIdByMbuf

 �޸���ʷ      :
  1.��    ��   : 2010��12��18��
    ��    ��   : jinhua
    �޸�����   : �����ɺ���
*****************************************************************************/
SM_ULONG sm_pgpAdapt_findFreeMbuf
(
    OUT     MBUF_S**     ppstMbuf
)
{
    SM_PGPADAPT_MBUF_INFO_S*  pstPgpAdaptMbufInfo = SM_NULL_PTR;
    MBUF_S*  pstMbuf = SM_NULL_PTR;
    SM_ULONG ulPacketId = 0;
    SM_ULONG ulIndex = 0;
    SM_ULONG ulIndexMax = 0;
    SM_ULONG ulFindFlag = SM_FALSE;
    SM_ULONG ulCount = 0;


    pstPgpAdaptMbufInfo = &(g_stPgpAdaptMbufInfo);

    /* ѭ��ʹ�ã���Ϊ���治�ᳬ��500��mbuf*/
    if (g_ulCurMbufIndex >= SM_PGPADAPT_MBUF_MAX_NUM)
    {
        g_ulCurMbufIndex = 0;
    }

    /* ���ڵ�ǰ�����ĺ������ */
    ulIndexMax = SM_PGPADAPT_MBUF_MAX_NUM;
    for (ulIndex = g_ulCurMbufIndex; ulIndex < SM_PGPADAPT_MBUF_MAX_NUM;)
    {
        if(ulCount >= SM_PGPADAPT_MBUF_MAX_NUM)
        {
            break;
        }


        if (SM_FALSE == pstPgpAdaptMbufInfo->astPgpAdaptMbuf[ulIndex].ulUsed)
        {
            ulPacketId = ulIndex;
            ulFindFlag = SM_TRUE;
            break;
        }

        ulIndex++;
        ulCount++;

        /* ��ǰ��������û�ҵ���ʱ���ٴ�ͷ���� */
        if (ulIndex >= SM_PGPADAPT_MBUF_MAX_NUM)
        {
            ulIndex = 0;
            ulIndexMax = g_ulCurMbufIndex;
        }


    }

    if (SM_TRUE == ulFindFlag)
    {
        pstMbuf = &(pstPgpAdaptMbufInfo->astPgpAdaptMbuf[ulPacketId].stMbuf);
        *ppstMbuf = pstMbuf;

        /* ����Mbuf״̬Ϊʹ��̬ */
        pstPgpAdaptMbufInfo->astPgpAdaptMbuf[ulPacketId].ulUsed = SM_TRUE;

        pstPgpAdaptMbufInfo->ulMbufMallocNum++;
        g_ulCurMbufIndex = ulPacketId;

        return SM_RET_OK;
    }

    return SM_RET_ERR;
}

/*****************************************************************************
 �� �� ��  : sm_pgpAdapt_getMbufDataBlock
 ��������  : ΪMbuf����pucDataBlock�������������
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  : sm_pgpAdapt_getMbuf

 �޸���ʷ      :
  1.��    ��   : 2010��12��20��
    ��    ��   : jinhua
    �޸�����   : �����ɺ���
*****************************************************************************/
SM_VOID sm_pgpAdapt_getMbufDataBlock
(
    IN      MBUF_S*                         pstMbuf,
    OUT      PMBUF_DATABLOCKDESCRIPTOR_S*   pstDataBlockDescriptor,
    IN      SM_ULONG                        ulMID
)
{
    SM_PGPADAPT_MBUF_INFO_S*  pstPgpAdaptMbufInfo = SM_NULL_PTR;
    SM_UCHAR*   pucDataBlock = SM_NULL_PTR;

    pstPgpAdaptMbufInfo = &(g_stPgpAdaptMbufInfo);



    pucDataBlock = (SM_UCHAR*)(pstMbuf + 1);

    VOS_MemSet(pucDataBlock, 0, SM_PGPADAPT_DATABLOCK_MAX_LENGTH);

    pstDataBlockDescriptor->pucDataBlock = pucDataBlock;
    pstDataBlockDescriptor->pucData = pucDataBlock + SM_PGP_MBUF_DATABLOCK_OFFSET;
    pstDataBlockDescriptor->ulDataBlockLength = SM_PGP_MBUF_DATABLOCK_MAX_LEN;
    pstDataBlockDescriptor->pstNextDataBlockDescriptor = SM_NULL_PTR;
    pstDataBlockDescriptor->ulDataLength = 0;

    pstPgpAdaptMbufInfo->astPgpAdaptMbuf[g_ulCurMbufIndex].ulDataBlockMallocNum++;
    pstPgpAdaptMbufInfo->astPgpAdaptMbuf[g_ulCurMbufIndex].ulMID = ulMID; /* ��¼ģ��� */

    return;
}
MBUF_S* sm_pgpAdapt_DTOM(UCHAR *pData)
{
    return (MBUF_S*)(pData - sizeof(MBUF_S));
}

/*****************************************************************************
 �� �� ��  : sm_pgpAdapt_getMbuf
 ��������  : ����Mbuf������������ӣ�������Mbuf��pkt Id�Ķ�Ӧ��ϵ
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  : sm_mbuf_getMbuf

 �޸���ʷ      :
  1.��    ��   : 2010��12��20��
    ��    ��   : jinhua
    �޸�����   : �����ɺ���
*****************************************************************************/
MBUF_S* sm_pgpAdapt_getMbuf
(
    IN      SM_ULONG ulMID
)
{
    SM_PGPADAPT_PACKET_INFO_S* pstPgpAdaptPktInfo = SM_NULL_PTR;
    MBUF_S*     pstMbuf = SM_NULL_PTR;
    SM_ULONG ulMbufIndex = 0;
    SM_ULONG ulRet = SM_RET_OK;

    /* ��ȫ�ֱ����в��ҷ�ʹ��̬��Mbuf, �����Ҳ�����ֱ�ӷ��� */
    ulRet = sm_pgpAdapt_findFreeMbuf(&pstMbuf);
    if (SM_RET_OK != ulRet)
    {
        return SM_NULL_PTR;
    }

    PS_MEM_SET(pstMbuf, 0, sizeof(MBUF_S));

    /* ����Mbuf��pkt Id�Ķ�Ӧ��ϵ */
    pstPgpAdaptPktInfo = (SM_PGPADAPT_PACKET_INFO_S*)&(g_astPgpAdaptPktInfo);
    pstPgpAdaptPktInfo[g_ulPktIdIndex].pstMbuf = pstMbuf;
    pstPgpAdaptPktInfo[g_ulPktIdIndex].ulPacketId = g_ulPktIdIndex + 1; /* ��֤�����ݰ��е�packet idһ��,��1��ʼ */
    g_ulPktIdIndex++;

    /* ����DataBlock*/
    sm_pgpAdapt_getMbufDataBlock(pstMbuf, &(pstMbuf->stDataBlockDescriptor), ulMID);
    pstMbuf->ulDataBlockNumber = 1;

    g_ulCurMbufIndex++;

    return pstMbuf;
}

/*****************************************************************************
 �� �� ��  : sm_pgpAdapt_getMbuf
 ��������  : �ͷ�Mbuf���ͷŸ������ӣ���ɾ����Ӧpkt Id��Mbuf�Ķ�Ӧ��ϵ
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  : sm_mbuf_releaseMbuf

 �޸���ʷ      :
  1.��    ��   : 2010��12��20��
    ��    ��   : jinhua
    �޸�����   : �����ɺ���
*****************************************************************************/
SM_ULONG g_ulCurMbufReleaseIndex = 0;
SM_VOID sm_pgpAdapt_releaseMbuf
(
    IN  MBUF_S*     pstMBuf
)
{
    SM_PGPADAPT_MBUF_INFO_S*        pstPgpAdaptMbufInfo    = SM_NULL_PTR;
    SM_PGPADAPT_PACKET_INFO_S*      pstPgpAdaptPktInfo     = SM_NULL_PTR;
    PMBUF_DATABLOCKDESCRIPTOR_S*    pstDataBlockDescriptor = SM_NULL_PTR;
    SM_ULONG ulindex = 0;
    SM_ULONG ulPacketId = 0;

    pstPgpAdaptMbufInfo = &(g_stPgpAdaptMbufInfo);
    pstPgpAdaptPktInfo = (SM_PGPADAPT_PACKET_INFO_S*)&(g_astPgpAdaptPktInfo);

    for (ulindex = 0; ulindex < SM_PGPADAPT_MBUF_MAX_NUM; ulindex++)
    {
        /* ��ȫ�ֱ����в�����pstMBuf��ͬ��Mbuf*/
        if (pstMBuf == &(pstPgpAdaptMbufInfo->astPgpAdaptMbuf[ulindex].stMbuf))
        {
            /* ����Mbuf״̬Ϊ��ʹ��̬ */
            pstPgpAdaptMbufInfo->astPgpAdaptMbuf[ulindex].ulUsed = SM_FALSE;
            pstPgpAdaptMbufInfo->astPgpAdaptMbuf[ulindex].ulDataBlockFreeNum++;

            break;
        }
    }

    for (ulindex = 0; ulindex < g_ulPktIdIndex; ulindex++)
    {
        /* ��ȫ�ֱ����в�����pstMBuf��ͬ��Mbuf*/
        if (pstMBuf == pstPgpAdaptPktInfo[ulindex].pstMbuf)
        {
            ulPacketId =  pstPgpAdaptPktInfo[ulindex].ulPacketId;

            /* ɾ����Ӧpkt Id��Mbuf�Ķ�Ӧ��ϵ */
            _pgpAdapt_clearLinkInMbufAndPktid(ulPacketId);

            break;
        }
    }

    pstPgpAdaptMbufInfo->ulMbufFreeNum++;
    g_ulCurMbufReleaseIndex ++;
    return;
}



SM_VOID sm_pgpAdapt_releaseMbufLink
(
    IN  MBUF_S* pstMBuf
)
{
    MBUF_S* pstTmp = pstMBuf;

    do
    {
        sm_pgpAdapt_releaseMbuf(pstTmp);
        /* ��Ҫ�ͷ���һ�� datablock */
        pstTmp = PMBUF_DBDescToMbuf(pstTmp->stDataBlockDescriptor.pstNextDataBlockDescriptor);
    } while ( SM_NULL_PTR != pstTmp );

    return;
}


SM_ULONG sm_pgpAdapt_copyMbuf()
{
    return SM_RET_OK;
}

/*****************************************************************************
 �� �� ��  : sm_pgpAdapt_getPktIdByMbuf
 ��������  : ����Mnuf���Ҷ�Ӧ��packet ID�������ڱ������ݵļ��
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  : _pfAdapt_sendPktProc��sm_pfAdapt_recvPacketProc

 �޸���ʷ      :
  1.��    ��   : 2010��12��20��
    ��    ��   : jinhua
    �޸�����   : �����ɺ���
*****************************************************************************/
SM_VOID sm_pgpAdapt_getPktIdByMbuf
(
    IN      MBUF_S*     pPFData,
    OUT     SM_ULONG*   pulPktId
)
{
    SM_PGPADAPT_PACKET_INFO_S*  pstPgpAdaptPktInfo = SM_NULL_PTR;
    SM_ULONG ulIndex = 0;
    SM_ULONG ulPacketId = 0;

    pstPgpAdaptPktInfo = (SM_PGPADAPT_PACKET_INFO_S*)&(g_astPgpAdaptPktInfo);

    for (ulIndex = 0; ulIndex < g_ulPktIdIndex; ulIndex++)
    {
        /* ��ȫ�ֱ����в�����pPFData��ͬ��Mbuf*/
        if ( pPFData == pstPgpAdaptPktInfo[ulIndex].pstMbuf)
        {
            ulPacketId =  pstPgpAdaptPktInfo[ulIndex].ulPacketId;

            *pulPktId = ulPacketId;
            return;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : sm_pgpAdapt_getMbufByPktId
 ��������  : ����packet ID���Ҷ�Ӧ��Mbuf
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��20��
    ��    ��   : jinhua
    �޸�����   : �����ɺ���
*****************************************************************************/
SM_VOID sm_pgpAdapt_getMbufByPktId
(
    IN       SM_ULONG     ulPktId,
    OUT      MBUF_S**     ppPFData
)
{
    SM_PGPADAPT_PACKET_INFO_S*  pstPgpAdaptPktInfo = SM_NULL_PTR;
    SM_ULONG ulIndex = 0;

    pstPgpAdaptPktInfo = (SM_PGPADAPT_PACKET_INFO_S*)&(g_astPgpAdaptPktInfo);

    for (ulIndex = 0; ulIndex < g_ulPktIdIndex; ulIndex++)
    {
        /* ��ȫ�ֱ����в�����pPFData��ͬ��Mbuf*/
        if (ulPktId ==  pstPgpAdaptPktInfo[ulIndex].ulPacketId)
        {
            *ppPFData = pstPgpAdaptPktInfo[ulIndex].pstMbuf;

            return;
        }
    }

    return;
}
SM_VOID sm_pgpAdapt_getMbufByPktId_headen
(
    IN       SM_ULONG     ulPktId,
    OUT      MBUF_S**     ppPFData
)
{
    SM_PGPADAPT_PACKET_INFO_S*  pstPgpAdaptPktInfo = SM_NULL_PTR;
    SM_ULONG ulIndex = 0;

    pstPgpAdaptPktInfo = (SM_PGPADAPT_PACKET_INFO_S*)&(g_astPgpAdaptPktInfo);

    for (ulIndex = 0; ulIndex < g_ulPktIdIndex; ulIndex++)
    {
        /* ��ȫ�ֱ����в�����pPFData��ͬ��Mbuf*/
        if(SM_NULL_PTR != pstPgpAdaptPktInfo[ulIndex].pstMbuf)
        {
            if(ulPktId ==  pstPgpAdaptPktInfo[ulIndex].pstMbuf->ulResv[1])
            {
                *ppPFData = pstPgpAdaptPktInfo[ulIndex].pstMbuf;
                return;
            }
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : _pgpAdapt_checkMbufInfo
 ��������  : ���Mbuf����Ϣ
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  : _pgpAdapt_checkResByUser

 �޸���ʷ      :
  1.��    ��   : 2010��12��22��
    ��    ��   : jinhua
    �޸�����   : �����ɺ���
*****************************************************************************/
SM_BOOL _pgpAdapt_checkMbufInfo
(
    OUT  SM_PGPADAPT_MBUF_CHECK_RESULT_S* pstResult
)
{
    SM_PGPADAPT_MBUF_INFO_S*    pstPgpAdaptMbufInfo = SM_NULL_PTR;
    SM_PGPADAPT_PACKET_INFO_S*  pstPgpAdaptPktInfo    = SM_NULL_PTR;
    MBUF_S* pPFData = SM_NULL_PTR;
    SM_ULONG ulIndex = 0;

    pstPgpAdaptMbufInfo = &(g_stPgpAdaptMbufInfo);
    pstPgpAdaptPktInfo = (SM_PGPADAPT_PACKET_INFO_S*)&(g_astPgpAdaptPktInfo);
    pstResult->ulMbufMallocNum =  pstPgpAdaptMbufInfo->ulMbufMallocNum;
    pstResult->ulMbufFreeNum =  pstPgpAdaptMbufInfo->ulMbufFreeNum;
    /* ��������Mbuf�����ͷŵ�Mbuf���Ƿ���ͬ */
    if (pstPgpAdaptMbufInfo->ulMbufMallocNum != pstPgpAdaptMbufInfo->ulMbufFreeNum)
    {
        pstResult->bIfMbufMallocEqualFree = SM_FALSE;
    }

    /* ���ÿ��Mbuf��״̬�Ƿ�Ϊ��ʹ��̬ */
    for (ulIndex = 0; ulIndex < SM_PGPADAPT_MBUF_MAX_NUM; ulIndex++)
    {
        if (SM_TRUE == pstPgpAdaptMbufInfo->astPgpAdaptMbuf[ulIndex].ulUsed)
        {
            pstResult->ulMbufUsedNum++;
        }

        /* ���ÿ��Mbuf��datablock����������ͷŸ����Ƿ���ͬ */
        if (pstPgpAdaptMbufInfo->astPgpAdaptMbuf[ulIndex].ulDataBlockMallocNum
            != pstPgpAdaptMbufInfo->astPgpAdaptMbuf[ulIndex].ulDataBlockFreeNum)
        {
            pstResult->ulMbufErrNum++;
        }

    }

    /* ���ÿ��Mbuf��Packet Id�Ķ�Ӧ��ϵ�Ƿ���� */
    for (ulIndex = 0; ulIndex < g_ulPktIdIndex; ulIndex++)
    {
        if ((SM_NULL_PTR != pstPgpAdaptPktInfo[ulIndex].pstMbuf)
            || (0 != pstPgpAdaptPktInfo[ulIndex].ulPacketId))
        {
            pstResult->ulMbufExistRelationNum++;
        }
    }

    if ((SM_TRUE != pstResult->bIfMbufMallocEqualFree)
        || (0 != pstResult->ulMbufUsedNum)
        || (0 != pstResult->ulMbufErrNum)
        || (0 != pstResult->ulMbufExistRelationNum))
    {
        return SM_FALSE;
    }

    return SM_TRUE;
}

/*****************************************************************************
 �� �� ��  : _pgpAdapt_reportMbufFailureInfo
 ��������  : ��ӡPGP ��resoure�����
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  : _pgpAdapt_checkResByUser

 �޸���ʷ      :
  1.��    ��   : 2010��12��22��
    ��    ��   : jinhua
    �޸�����   : �����ɺ���
*****************************************************************************/
SM_VOID _pgpAdapt_reportMbufFailureInfo
(
    IN      SM_PGPADAPT_MBUF_CHECK_RESULT_S* pstResult,
    IN      SM_VOID* pFile
)
{

    sm_debug_printAll(
                     "\r\n");
    sm_debug_printAll(
                     "\r\n -----------------------------------------------------------------");
    sm_debug_printAll(
                     "\r\n |                         MBUF CHECK ERROR                      |");
    if (SM_FALSE == pstResult->bIfMbufMallocEqualFree)
    {
        sm_debug_printAll(
                     "\r\n |             Mbuf Malloc Num                   = % 4u,         |"
                     "\r\n |             Mbuf Free Num                     = % 4u,         |",
                    pstResult->ulMbufMallocNum,
                    pstResult->ulMbufFreeNum);
    }

    sm_debug_printAll(
                     "\r\n |             Mbuf Used Num                     = % 4u,         |"
                     "\r\n |             Mbuf Err Num                      = % 4u,         |"
                     "\r\n |             Relation Num (Mbuf With PktId)    = % 4u,         |",
                     pstResult->ulMbufUsedNum,
                     pstResult->ulMbufErrNum,
                     pstResult->ulMbufExistRelationNum);

    sm_debug_printAll(
                     "\r\n -----------------------------------------------------------------");

    return;
}

/*****************************************************************************
 �� �� ��  : _pgpAdapt_clearResInfo
 ��������  : ���ʹ��״̬
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  : _pgpAdapt_checkResByUser

 �޸���ʷ      :
  1.��    ��   : 2010��12��22��
    ��    ��   : jinhua
    �޸�����   : �����ɺ���
*****************************************************************************/
SM_VOID _pgpAdapt_clearMbufInfo
(
    IN      SM_PGPADAPT_MBUF_CHECK_RESULT_S*  pstMbufCheckResult
)
{
    SM_PGPADAPT_MBUF_INFO_S*   pstPgpAdaptMbufInfo = SM_NULL_PTR;
    SM_PGPADAPT_MBUF_S*   pstPgpAdaptMbuf = SM_NULL_PTR;
    SM_PGPADAPT_PACKET_INFO_S* pstPktInfo = SM_NULL_PTR;
    SM_ULONG ulIndex = 0;

    pstPgpAdaptMbufInfo = &(g_stPgpAdaptMbufInfo);
    pstPgpAdaptMbuf = (SM_PGPADAPT_MBUF_S*)&(pstPgpAdaptMbufInfo->astPgpAdaptMbuf);

    /* ���Mbuf�洢��Ϣ */
    g_ulPktIdIndex = 0;
    g_ulCurMbufIndex = 0;
    g_ulCurMbufReleaseIndex = 0;
    pstPgpAdaptMbufInfo->ulMbufMallocNum = 0;
    pstPgpAdaptMbufInfo->ulMbufFreeNum   = 0;

    for (ulIndex = 0; ulIndex < SM_PGPADAPT_MBUF_MAX_NUM; ulIndex++)
    {
        pstPgpAdaptMbuf[ulIndex].ulUsed               = SM_FALSE;
        pstPgpAdaptMbuf[ulIndex].ulDataBlockMallocNum = 0;
        pstPgpAdaptMbuf[ulIndex].ulDataBlockFreeNum   = 0;
    }

    /* ���Mbuf�����Ϣ */
    pstMbufCheckResult->bIfMbufMallocEqualFree = SM_TRUE;
    pstMbufCheckResult->ulMbufErrNum = 0;
    pstMbufCheckResult->ulMbufExistRelationNum = 0;
    pstMbufCheckResult->ulMbufUsedNum = 0;

    pstPktInfo = (SM_PGPADAPT_PACKET_INFO_S*)&(g_astPgpAdaptPktInfo);

    for (ulIndex = 0; ulIndex < SM_PGPADAPT_MBUF_MAX_NUM; ulIndex++)
    {
        pstPktInfo[ulIndex].pstMbuf = SM_NULL_PTR;
        pstPktInfo[ulIndex].ulPacketId = 0;
    }


    return;
}



/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
