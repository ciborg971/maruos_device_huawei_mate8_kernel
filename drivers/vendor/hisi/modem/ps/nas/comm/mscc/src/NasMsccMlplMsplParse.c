


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMsccMlplMsplParse.h"
#include "NasMsccComFunc.h"
#include "NasMsccCtx.h"
#include "Crc.h"
#include "PsCommonDef.h"
#include "NasMntn.h"
#include "NasMsccMntn.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_MLPL_MSPL_PARSE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#define NAS_MSCC_BIT_TO_BYTE(pBuf, bOffSet, bLen)                                   \
        NAS_MSCC_ExtractBitStringToOctet(&pBuf[bOffSet/NAS_MSCC_BIT_LEN_8_BIT],     \
                                         (VOS_UINT8)bOffSet%NAS_MSCC_BIT_LEN_8_BIT, \
                                         bLen)

#define NAS_MSCC_BIT_TO_WORD(pBuf, bOffSet, bLen)                                   \
        NAS_MSCC_ExtractBitStringToWord(&pBuf[bOffSet/NAS_MSCC_BIT_LEN_8_BIT],      \
                                        (VOS_UINT8)bOffSet%NAS_MSCC_BIT_LEN_8_BIT,  \
                                        bLen)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
NAS_MSPL_PRI_SRCH_TIME_MAP_MINUTE_STRU
    g_astMsplSrchTimeMillsecMap[NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_COUNT] =
{
    { NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_1_MIN , {0,0,0}, 1 * 60 * 1000 },
    { NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_2_MIN , {0,0,0}, 2 * 60 * 1000 },
    { NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_4_MIN , {0,0,0}, 4 * 60 * 1000 },
    { NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_8_MIN , {0,0,0}, 8 * 60 * 1000 },
    { NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_16_MIN, {0,0,0}, 16 * 60 * 1000 },
    { NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_24_MIN, {0,0,0}, 24 * 60 * 1000 },
    { NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_32_MIN, {0,0,0}, 32 * 60 * 1000 },
    { NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_64_MIN, {0,0,0}, 64 * 60 * 1000 },
};


/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e429*/



/*****************************************************************************
Function Name   :   NAS_MSCC_ExtractBitStringToOctet
Description     :   Extract 8 bit info.
Input parameters:   pucSrcAddr - source buffer
                    ucOffsetPos  - offset position
                    ucBitLen - information len in bits
Outout parameters:  None
Return Value     :  VOS_UINT8
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
/*lint -e701*/
VOS_UINT8  NAS_MSCC_ExtractBitStringToOctet(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucBitLen
)
{
    VOS_UINT8                          *pucBuffOffset = VOS_NULL_PTR;
    VOS_INT16                           iRemainBitLen;
    VOS_UINT8                           ucExtractByte;
    VOS_UINT8                           ucRemainLen;

    pucBuffOffset = pucSrcAddr;

    iRemainBitLen = (VOS_INT16)(NAS_MSCC_BIT_LEN_8_BIT - (ucOffsetPos + ucBitLen));

    /* ���һ���ֽ�����usOffsetPos��ʣ��bit�ĳ��ȴ��ڵ���usOffsetPos����ֱ���ڸ��ֽ��н���ȡֵ */
    /* ���һ���ֽ�����usOffsetPos��ʣ��bit�ĳ���С��usOffsetPos,����Ҫ����һ���ֽ��н���ȡֵ*/
    if ( iRemainBitLen >= 0 )
    {
        ucExtractByte =  (VOS_UINT8)(((VOS_UINT8)((*pucBuffOffset) << ucOffsetPos)) >> (ucOffsetPos + iRemainBitLen));
    }
    else
    {
        /* ����ʣ��λ */
        ucRemainLen = (VOS_UINT8)(ucBitLen - (NAS_MSCC_BIT_LEN_8_BIT - ucOffsetPos));

        ucExtractByte = (VOS_UINT8)(((*pucBuffOffset) & (0xFF >> ucOffsetPos)) << ucRemainLen);

        pucBuffOffset++;

        /* ���ֽ�ʣ��bit���� */
        ucExtractByte |= (VOS_UINT8)(((*pucBuffOffset) & 0xFF) >> (NAS_MSCC_BIT_LEN_8_BIT - ucRemainLen));
    }

    return ucExtractByte;

}
/*lint +e701*/


/*****************************************************************************
Function Name   :   NAS_MSCC_ExtractBitStringToWord
Description     :   Extract 16 bit info.
Input parameters:   pucSrcAddr - source buffer
                    ucOffsetPos  - offset position
                    ucBitLen - information len in bits
Outout parameters:  None
Return Value     :  VOS_UINT16
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
/*lint -e701*/
VOS_UINT16 NAS_MSCC_ExtractBitStringToWord(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucBitLen
)
{
    VOS_UINT8                          *pucTmpSrc = VOS_NULL_PTR;
    VOS_UINT16                          usExtractWord;
    VOS_UINT16                          usRemainBitLen;

    pucTmpSrc = pucSrcAddr;

    if (ucBitLen > NAS_MSCC_BIT_LEN_16_BIT)
    {
        ucBitLen = NAS_MSCC_BIT_LEN_16_BIT;
    }

    if (ucBitLen <= NAS_MSCC_BIT_LEN_8_BIT)
    {
        /* ����bit lengthС�ڵ���8bit�Ĵ��� */
        usExtractWord = (VOS_UINT16)NAS_MSCC_ExtractBitStringToOctet(pucTmpSrc,
                                                                     ucOffsetPos,
                                                                     ucBitLen);

        return usExtractWord;
    }

    /* �����ȥ��ǰ�ֽ���Чbit��ʣ��bit���� */
    usRemainBitLen = (VOS_UINT16)(ucBitLen - (NAS_MSCC_BIT_LEN_8_BIT - ucOffsetPos));

    /* ��ȡ�׸��ֽ����ݲ��֣����Ƶ���Ӧ�ĸ�λ, �ճ�ʣ��bitλ */
    usExtractWord  = (VOS_UINT16)(((*pucTmpSrc) & (0xFF >> ucOffsetPos)) << usRemainBitLen);

    /* ָ����һ���ֽ� */
    pucTmpSrc++;

    /* ���ʣ�೤�� */
    if (usRemainBitLen > NAS_MSCC_BIT_LEN_8_BIT)
    {
        /* ����ʣ��δȡ���bit */
        usRemainBitLen -= NAS_MSCC_BIT_LEN_8_BIT;

        /* ���ƣ��ճ�ʣ��bitλ */
        usExtractWord |= (VOS_UINT16)((VOS_UINT8)(*pucTmpSrc) << usRemainBitLen);
    }
    else
    {
        /* ���ֽ�ʣ��bit���� */
        usExtractWord |= (VOS_UINT16)(((*pucTmpSrc) & 0xFF) >> (NAS_MSCC_BIT_LEN_8_BIT - usRemainBitLen));

        /* bit�Ѿ�ȡ�꣬��0 */
        usRemainBitLen = 0;
    }

    if (usRemainBitLen > 0)
    {
        pucTmpSrc++;

        /* ���ֽ�ʣ��bit���� */
        usExtractWord |= (VOS_UINT16)(((*pucTmpSrc) & 0xFF) >> (NAS_MSCC_BIT_LEN_8_BIT - usRemainBitLen));
    }

    /* ����ת�����ֽڵĴ��� */
    return usExtractWord;
}
/*lint +e701*/


/*****************************************************************************
Function Name   :   NAS_MSCC_CheckMlplMsplCrcChecksum
Description     :   perform CRC checck.
Input parameters:   pMsplMlplBuff - MSPL buffer
Outout parameters:  None
Return Value     :  NAS_MSCC_PARSE_CRC_RSLT_ENUM_UINT32
Modify History:
    1)  Date    :   2015-04-08
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
NAS_MSCC_PARSE_CRC_RSLT_ENUM_UINT32 NAS_MSCC_CheckMlplMsplCrcChecksum(
    VOS_UINT8                          *pMsplMlplBuff
)
{
    VOS_UINT16                          usCrcCalLength;
    VOS_UINT16                          usListCrc;
    VOS_UINT16                          usListSize;
    VOS_UINT16                          usCalcCrc;
    VOS_UINT8                          *pBuff = VOS_NULL_PTR;

    pBuff        = pMsplMlplBuff;

    /* MSPL/MLPL list size */
    usListSize = NAS_MSCC_ExtractBitStringToWord(pBuff, 0, NAS_MSCC_BIT_LEN_16_BIT);

    /* See 3.5.5.1 Preferred Roaming List CRC Calculation in C.S0016-D:
       The 16-bit CRC field MLPL_CRC (or MSPL_CRC) iscalculated on all bits of MMSS Location
       Associated Priority List (or MMSS System Priority List) excluding the bits of the
       MLPL_CRC (or MSPL_CRC) field itself. The generator polynomial for this CRC is
       g(x) = x16 + x12 + x5 + x0 */
    usCrcCalLength = usListSize - sizeof(VOS_UINT16);

    /* LIST_SIZE - MSPL/MLPL list size.
       This field is set to the total size, in octets, of the MSPL/MLPL, including
       the MSPL_LIST_SIZE/MLPL_LIST_SIZE and LIST_CRC fields. */
    usListCrc = NAS_MSCC_BIT_TO_WORD(pBuff, (usCrcCalLength * NAS_MSCC_BIT_LEN_8_BIT), NAS_MSCC_BIT_LEN_16_BIT);

    /* ����CRC, length��Ҫת����bit�� */
    usCalcCrc = CRC_CalculateCRC16(pBuff, usCrcCalLength * NAS_MSCC_BIT_LEN_8_BIT);

    if (usListCrc == usCalcCrc)
    {
        return NAS_MSCC_PARSE_CRC_RSLT_SUCCESS;
    }

    return NAS_MSCC_PARSE_CRC_RSLT_FAIL;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMsplBitStream
Description     :   Parse MSPL info.
Input parameters:   pucMsplBuff - MSPL buffer
                    ulBuffSize  - buff size in bytes
Outout parameters:  None
Return Value     :  NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32 NAS_MSCC_ParseMsplBitStream(
    VOS_UINT8                          *pucMsplBuff,
    VOS_UINT16                          usBuffSize
)
{
    NAS_MSCC_MSPL_PARSE_CTX_STRU                            stMsplParseCtx;
    VOS_UINT8                                               ucMsplIdCount;
    VOS_UINT8                                               ucIndex;
    NAS_MSCC_PARSE_MSPL_ID_RSLT_ENUM_UINT32                 enIdParseRslt;
    NAS_MSCC_PARSE_CRC_RSLT_ENUM_UINT32                     enCrcCause;
    VOS_UINT32                                              ulTempLen;
    NAS_MSCC_MSPL_ID_STRU                                  *pstTempMsplId;
    VOS_UINT32                                              ulRemainBitLength;

    PS_MEM_SET(&stMsplParseCtx, 0, sizeof(NAS_MSCC_MSPL_PARSE_CTX_STRU));

    stMsplParseCtx.pucMsplSrcBuff = pucMsplBuff;
    stMsplParseCtx.usBuffSize     = usBuffSize;
    stMsplParseCtx.pstMsplInfo    = NAS_MSCC_GetMsplInfoAddr();

    NAS_MSCC_ResetMsplInfo(stMsplParseCtx.pstMsplInfo, 0);

    /* Parse MSPL header */
    if (NAS_MSCC_PARSE_MSPL_HDR_RSLT_SUCCESS != NAS_MSCC_ParseMsplHeader(&stMsplParseCtx))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ParseMsplBitStream:MSPL Parse header failure.");
        return NAS_MSCC_PARSE_MSPL_RSLT_HDR_PARSE_FAIL;
    }

    stMsplParseCtx.usBuffSize = stMsplParseCtx.pstMsplInfo->stMsplHdr.usMsplSize;

    /* Get total no of MSPL_IDs */
    ucMsplIdCount = stMsplParseCtx.pstMsplInfo->stMsplHdr.ucNumMsplId;

    /* Get Remaining bit len available for parsing */
    ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(stMsplParseCtx.usBuffSize,
                                                    stMsplParseCtx.usBitOffset);
    ucIndex          = 0;
    ulTempLen        = 0;
    while ((ucMsplIdCount > 0)
        && (ulRemainBitLength >= NAS_MSCC_MSPL_ID_MIN_BIT_LEN))
    {
        ulTempLen = ulRemainBitLength;

        pstTempMsplId = (NAS_MSCC_MSPL_ID_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                               sizeof(NAS_MSCC_MSPL_ID_STRU));
        if (VOS_NULL_PTR == pstTempMsplId)
        {
            NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ParseMsplBitStream:Malloc failure.");

            NAS_MSCC_ResetMsplInfo(stMsplParseCtx.pstMsplInfo, ucIndex);
            return NAS_MSCC_PARSE_MSPL_RSLT_MALLOC_FAIL;
        }

        PS_MEM_SET(pstTempMsplId, 0, sizeof(NAS_MSCC_MSPL_ID_STRU));

        /* Parse NUM_MSPL_ID struct */
        enIdParseRslt = NAS_MSCC_ParseMsplId(&stMsplParseCtx, pstTempMsplId);
        if (enIdParseRslt != NAS_MSCC_PARSE_MSPL_ID_RSLT_SUCCESS)
        {
            NAS_ERROR_LOG1(UEPS_PID_MSCC,
                           "NAS_MSCC_ParseMsplBitStream:MSPL ID Parse fail,MSPL ID = ",
                           pstTempMsplId->ucMsplId);

            NAS_MSCC_ResetMsplInfo(stMsplParseCtx.pstMsplInfo, ucIndex);
            return NAS_MSCC_PARSE_MSPL_RSLT_MSPL_ID_PARSE_FAIL;
        }

        /* Get Remaining bit len available for parsing */
        ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(stMsplParseCtx.usBuffSize,
                                        stMsplParseCtx.usBitOffset);

        /* Update parsed bit len for MSPL_IDs, this will be used to calculate
           reserve bits at the end when parsing for all MSPL_IDs is finished
           successfully
        */
        stMsplParseCtx.ulParsedMsplIdBitLen += (ulTempLen - ulRemainBitLength);

        /* MSPL ID parse success, write this ID to global CTX */
        NAS_MSCC_UpdateMsplIdInfo(&stMsplParseCtx, pstTempMsplId, ucIndex);

        ucMsplIdCount--;
        ucIndex++;
    }

    if (ucMsplIdCount != 0)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,
                      "NAS_MSCC_ParseMsplBitStream:MSPL parse failure.RemainBitlen is not enough to continue.");

        NAS_MSCC_ResetMsplInfo(stMsplParseCtx.pstMsplInfo, ucIndex);
        return NAS_MSCC_PARSE_MSPL_RSLT_FAIL;
    }

    if (0 == stMsplParseCtx.ucNumValidMsplId)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,
                      "NAS_MSCC_ParseMsplBitStream:MSPL parse failure,ucNumValidMsplId = 0 in MSPList.");

        NAS_MSCC_ResetMsplInfo(stMsplParseCtx.pstMsplInfo, ucIndex);
        return NAS_MSCC_PARSE_MSPL_RSLT_FAIL;
    }

    /* Here comes, means parsing is sucess for all MSPL IDs */
    /* Calculate and skip reserved bits after parsing of all MSPL_IDs */
    NAS_MSCC_ProcResrvBitsInBuff(stMsplParseCtx.ulParsedMsplIdBitLen,
                                 &stMsplParseCtx.usBitOffset);

    ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(stMsplParseCtx.usBuffSize,
                                                stMsplParseCtx.usBitOffset);

    if (NAS_MSCC_MSPL_CRC_BIT_LEN == ulRemainBitLength)
    {
        stMsplParseCtx.pstMsplInfo->usMsplCrc = NAS_MSCC_BIT_TO_WORD(stMsplParseCtx.pucMsplSrcBuff,
                                                  stMsplParseCtx.usBitOffset,
                                                  NAS_MSCC_MSPL_CRC_BIT_LEN);
        NAS_MSCC_UPDATE_BIT_OFFSET(stMsplParseCtx.usBitOffset, NAS_MSCC_MSPL_CRC_BIT_LEN);

        enCrcCause = NAS_MSCC_CheckMlplMsplCrcChecksum(stMsplParseCtx.pucMsplSrcBuff);
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMsplBitStream:CRC check result = ",
                       enCrcCause);

        NAS_MSCC_MNTN_LogMlplMsplCrcChkRslt(enCrcCause, NAS_MSCC_MLPL_MSPL_PARSE_TYPE_MSPL);

        ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(stMsplParseCtx.usBuffSize,
                                        stMsplParseCtx.usBitOffset);
    }

    if (ulRemainBitLength != 0)
    {
        NAS_INFO_LOG1(UEPS_PID_MSCC,
                      "NAS_MSCC_ParseMsplBitStream:All MSPL IDs parsed, ulRemainBitLen = ",
                      ulRemainBitLength);
    }

    stMsplParseCtx.pstMsplInfo->ucIsMsplValid = VOS_TRUE;

    NAS_INFO_LOG(UEPS_PID_MSCC, "NAS_MSCC_ParseMsplBitStream:MSPL parse Success.");

    return NAS_MSCC_PARSE_MSPL_RSLT_SUCCESS;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMsplHeader
Description     :   Parse MSPL info.
Input parameters:   pstMsplParseCtx - parse Ctx
Outout parameters:  pstMsplHeader - parsed MSPL hdr
Return Value     :  NAS_MSCC_PARSE_MSPL_HDR_RSLT_ENUM_UINT32
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
NAS_MSCC_PARSE_MSPL_HDR_RSLT_ENUM_UINT32 NAS_MSCC_ParseMsplHeader(
    NAS_MSCC_MSPL_PARSE_CTX_STRU       *pstMsplParseCtx
)
{
    NAS_MSCC_MSPL_HEADER_STRU          *pstMsplHeader;

    pstMsplHeader  = &pstMsplParseCtx->pstMsplInfo->stMsplHdr;

    /* Parse MSPL_SIZE */
    pstMsplHeader->usMsplSize = NAS_MSCC_BIT_TO_WORD(pstMsplParseCtx->pucMsplSrcBuff,
                                                     pstMsplParseCtx->usBitOffset,
                                                     NAS_MSCC_MSPL_MSPL_SIZE_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMsplParseCtx->usBitOffset, NAS_MSCC_MSPL_MSPL_SIZE_BIT_LEN);

    if (0 == pstMsplHeader->usMsplSize)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ParseMsplHeader:Parse Fail:MSPL_SIZE is 0.");
            return NAS_MSCC_PARSE_MSPL_HDR_RSLT_FAIL;
    }

    if ((pstMsplParseCtx->usBuffSize < pstMsplHeader->usMsplSize))
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMsplHeader:Parse Fail:Input BuffSize is lesser than MSPL_SIZE, BuffSize = ",
                       pstMsplParseCtx->usBuffSize);
        return NAS_MSCC_PARSE_MSPL_HDR_RSLT_FAIL;
    }

    if (NAS_MSCC_CONVERT_BYTES_TO_BITS(pstMsplHeader->usMsplSize) < NAS_MSCC_MSPL_MIN_BIT_LEN)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,
                      "NAS_MSCC_ParseMsplHeader:Parse Fail:MSPL_SIZE is lesser than NAS_MSCC_MSPL_MIN_BIT_LEN.");
        return NAS_MSCC_PARSE_MSPL_HDR_RSLT_FAIL;
    }

    if ((pstMsplParseCtx->usBuffSize > pstMsplHeader->usMsplSize))
    {
        NAS_INFO_LOG1(UEPS_PID_MSCC,
                      "NAS_MSCC_ParseMsplHeader:INFO:Input BuffSize greater than MSPL_SIZE, BuffSize = ",
                      pstMsplParseCtx->usBuffSize);
    }

    /* Parse CUR_MMSS_P_REV */
    pstMsplHeader->ucCurrProtRev = NAS_MSCC_BIT_TO_BYTE(pstMsplParseCtx->pucMsplSrcBuff,
                                                        pstMsplParseCtx->usBitOffset,
                                                        NAS_MSCC_MSPL_CUR_MMSS_P_REV_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMsplParseCtx->usBitOffset, NAS_MSCC_MSPL_CUR_MMSS_P_REV_BIT_LEN);


    /* Modified by t00323010 for CDMA Iteration 16 2015-8-7 begin */
    /* Parse MSPL_VER_ID */
    pstMsplHeader->usMsplVerId = NAS_MSCC_BIT_TO_WORD(pstMsplParseCtx->pucMsplSrcBuff,
                                                      pstMsplParseCtx->usBitOffset,
                                                      NAS_MSCC_MSPL_MSPL_VER_ID_BIT_LEN);
    /* Modified by t00323010 for CDMA Iteration 16 2015-8-7 end */

    NAS_MSCC_UPDATE_BIT_OFFSET(pstMsplParseCtx->usBitOffset, NAS_MSCC_MSPL_MSPL_VER_ID_BIT_LEN);

    /* Parse NUM_MSPL_ID */
    pstMsplHeader->ucNumMsplId = NAS_MSCC_BIT_TO_BYTE(pstMsplParseCtx->pucMsplSrcBuff,
                                                      pstMsplParseCtx->usBitOffset,
                                                      NAS_MSCC_MSPL_NUM_MSPL_ID_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMsplParseCtx->usBitOffset, NAS_MSCC_MSPL_NUM_MSPL_ID_BIT_LEN);

    if (0 == pstMsplHeader->ucNumMsplId)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,
                      "NAS_MSCC_ParseMsplHeader:Parse Fail:No of MSPL IDs is 0.");
        return NAS_MSCC_PARSE_MSPL_HDR_RSLT_FAIL;
    }

    return NAS_MSCC_PARSE_MSPL_HDR_RSLT_SUCCESS;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMsplId
Description     :   Parse MSPL Id.
Input parameters:   pstMsplParseCtx - parse Ctx
Outout parameters:  pstMsplId - parsed MSPL Id
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
NAS_MSCC_PARSE_MSPL_ID_RSLT_ENUM_UINT32 NAS_MSCC_ParseMsplId(
    NAS_MSCC_MSPL_PARSE_CTX_STRU       *pstMsplParseCtx,
    NAS_MSCC_MSPL_ID_STRU              *pstMsplId
)
{
    VOS_UINT8                           ucMsplRecCount;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRemainBitLength;
    VOS_UINT8                           ucCountValidRec;
    NAS_MSCC_PARSE_MSPL_REC_RSLT_ENUM_UINT32                enRslt;

    pstMsplId->ucIsMsplIdValid = VOS_FALSE;

    /* Parse MSPL_ID, It can be 0 */
    pstMsplId->ucMsplId = NAS_MSCC_BIT_TO_BYTE(pstMsplParseCtx->pucMsplSrcBuff,
                                        pstMsplParseCtx->usBitOffset,
                                        NAS_MSCC_MSPL_MSPL_ID_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMsplParseCtx->usBitOffset, NAS_MSCC_MSPL_MSPL_ID_BIT_LEN);

    /* Parse NUM_MSPL_RECS */
    pstMsplId->ucNumMsplRec = NAS_MSCC_BIT_TO_BYTE(pstMsplParseCtx->pucMsplSrcBuff,
                                        pstMsplParseCtx->usBitOffset,
                                        NAS_MSCC_MSPL_NUM_MSPL_RECS_BIT_LEN);

    NAS_MSCC_UPDATE_BIT_OFFSET(pstMsplParseCtx->usBitOffset, NAS_MSCC_MSPL_NUM_MSPL_RECS_BIT_LEN);

    if (0 == pstMsplId->ucNumMsplRec)
    {
        NAS_INFO_LOG1(UEPS_PID_MSCC,
                      "NAS_MSCC_ParseMsplId:NUM_MSPL_REC is 0 in MSPL_ID = ",
                      pstMsplId->ucMsplId);
        return NAS_MSCC_PARSE_MSPL_ID_RSLT_SUCCESS;
    }

    ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(pstMsplParseCtx->usBuffSize,
                                        pstMsplParseCtx->usBitOffset);

    ucMsplRecCount = pstMsplId->ucNumMsplRec;
    ucIndex = 0;
    ucCountValidRec = 0;
    while ((ucMsplRecCount > 0)
        && (ulRemainBitLength >= NAS_MSCC_MSPL_REC_MIN_BIT_LEN))
    {
        /* Parse MSPL_REC struct */
        enRslt = NAS_MSCC_ParseMsplRecord(pstMsplParseCtx, &pstMsplId->astMsplRec[ucIndex]);
        if (enRslt != NAS_MSCC_PARSE_MSPL_REC_RSLT_SUCCESS)
        {
            /* Possible Scenario: Last record in last MSPL ID contains
               NETWORK_CAP_IND = 0x01 but No remain data len. */
            return NAS_MSCC_PARSE_MSPL_ID_RSLT_INSUFFICIENT_DATA_LEN;
        }

        if (VOS_TRUE == pstMsplId->astMsplRec[ucIndex].ucIsValid)
        {
            ucCountValidRec++;
        }

        ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(pstMsplParseCtx->usBuffSize,
                                        pstMsplParseCtx->usBitOffset);
        ucMsplRecCount--;
        ucIndex++;
    }

    if (ucMsplRecCount != 0)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMsplId:Insufficient to continue parse MSPL record, ulRemainBitLength = ",
                       ulRemainBitLength);
        return NAS_MSCC_PARSE_MSPL_ID_RSLT_INSUFFICIENT_DATA_LEN;
    }

    pstMsplId->ucIsMsplIdValid = ((0 == ucCountValidRec) ? VOS_FALSE : VOS_TRUE);

    return NAS_MSCC_PARSE_MSPL_ID_RSLT_SUCCESS;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMsplRecord
Description     :   Parse MSPL record.
Input parameters:   pstMsplParseCtx - parse Ctx
Outout parameters:  pstMsplRec - parsed MSPL record
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
NAS_MSCC_PARSE_MSPL_REC_RSLT_ENUM_UINT32 NAS_MSCC_ParseMsplRecord(
    NAS_MSCC_MSPL_PARSE_CTX_STRU       *pstMsplParseCtx,
    NAS_MSCC_MSPL_REC_STRU             *pstMsplRec
)
{
    VOS_UINT32                          ulRemainBitLength;

    pstMsplRec->ucIsValid = VOS_FALSE;

    /* Parse SYS_TYPE */
    pstMsplRec->enSysType = NAS_MSCC_BIT_TO_BYTE(pstMsplParseCtx->pucMsplSrcBuff,
                                        pstMsplParseCtx->usBitOffset,
                                        NAS_MSCC_MSPL_REC_SYS_TYPE_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMsplParseCtx->usBitOffset, NAS_MSCC_MSPL_REC_SYS_TYPE_BIT_LEN);

    /* Parse PRI_CLASS */
    pstMsplRec->enPriClass = NAS_MSCC_BIT_TO_BYTE(pstMsplParseCtx->pucMsplSrcBuff,
                                        pstMsplParseCtx->usBitOffset,
                                        NAS_MSCC_MSPL_REC_PRIO_CLASS_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMsplParseCtx->usBitOffset, NAS_MSCC_MSPL_REC_PRIO_CLASS_BIT_LEN);

    /* Parse SYS_PRI */
    pstMsplRec->enSysPri = NAS_MSCC_BIT_TO_BYTE(pstMsplParseCtx->pucMsplSrcBuff,
                                        pstMsplParseCtx->usBitOffset,
                                        NAS_MSCC_MSPL_REC_SYS_PRIO_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMsplParseCtx->usBitOffset, NAS_MSCC_MSPL_REC_SYS_PRIO_BIT_LEN);

    /* Parse HIGHER_PRI_SRCH_TIME */
    pstMsplRec->enHigherPriSrchTime = NAS_MSCC_BIT_TO_BYTE(pstMsplParseCtx->pucMsplSrcBuff,
                                        pstMsplParseCtx->usBitOffset,
                                        NAS_MSCC_MSPL_REC_HIGHER_PRIO_SRCH_TIME_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMsplParseCtx->usBitOffset, NAS_MSCC_MSPL_REC_HIGHER_PRIO_SRCH_TIME_BIT_LEN);

    /* Parse NETWORK_CAP_IND */
    pstMsplRec->ucNetwrkCapInd = NAS_MSCC_BIT_TO_BYTE(pstMsplParseCtx->pucMsplSrcBuff,
                                        pstMsplParseCtx->usBitOffset,
                                        NAS_MSCC_MSPL_REC_NETWRK_CAP_IND_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMsplParseCtx->usBitOffset, NAS_MSCC_MSPL_REC_NETWRK_CAP_IND_BIT_LEN);

    ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(pstMsplParseCtx->usBuffSize,
                                        pstMsplParseCtx->usBitOffset);

    if (NAS_MSCC_MSPL_BIT_NETWORK_CAP_IND & pstMsplRec->ucNetwrkCapInd)
    {
        if (ulRemainBitLength < NAS_MSCC_MSPL_REC_NETWRK_CAP_BIT_LEN)
        {
            NAS_ERROR_LOG(UEPS_PID_MSCC,
                         "NAS_MSCC_ParseMsplRecord:Parse Fail:Insufficient ulRemainBitLen to continue parse NETWORK_CAP");
            return NAS_MSCC_PARSE_MSPL_REC_RSLT_INSUFFICIENT_DATA_LEN;
        }

        /* Parse NETWORK_CAP */
        pstMsplRec->enNetwrkCap = NAS_MSCC_BIT_TO_BYTE(pstMsplParseCtx->pucMsplSrcBuff,
                                        pstMsplParseCtx->usBitOffset,
                                        NAS_MSCC_MSPL_REC_NETWRK_CAP_BIT_LEN);
        NAS_MSCC_UPDATE_BIT_OFFSET(pstMsplParseCtx->usBitOffset, NAS_MSCC_MSPL_REC_NETWRK_CAP_BIT_LEN);
    }

    pstMsplRec->ucIsValid = NAS_MSCC_IsMsplRecValid(pstMsplRec);

    return NAS_MSCC_PARSE_MSPL_REC_RSLT_SUCCESS;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_IsMsplRecValid
Description     :   Check if MSPL record is valid.
Input parameters:   pstTempMsplRec - MSPL record data
Outout parameters:  None
Return Value     :  VOS_BOOL
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
VOS_UINT8 NAS_MSCC_IsMsplRecValid(
    NAS_MSCC_MSPL_REC_STRU              *pstTempMsplRec
)
{
    if (VOS_TRUE != NAS_MSCC_IsSystemTypeValid(pstTempMsplRec->enSysType))
    {
        NAS_INFO_LOG(UEPS_PID_MSCC,
                     "NAS_MSCC_IsMsplRecValid:Invalid system type found MSPL record.");
        return VOS_FALSE;
    }

    if ((pstTempMsplRec->enPriClass != NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME)
     && (pstTempMsplRec->enPriClass != NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME_AND_PREF)
     && (pstTempMsplRec->enPriClass != NAS_MSCC_MSPL_SYS_PRI_CLASS_ANY))
    {
        NAS_INFO_LOG(UEPS_PID_MSCC,
                     "NAS_MSCC_IsMsplRecValid:Invalid priority class in MSPL record.");
        return VOS_FALSE;
    }

    if ((NAS_MSCC_MSPL_BIT_NETWORK_CAP_IND == pstTempMsplRec->ucNetwrkCapInd)
     && (pstTempMsplRec->enNetwrkCap != NAS_MSCC_MSPL_NETWORK_CAP_VOICE_AND_DATA))
    {
        NAS_INFO_LOG(UEPS_PID_MSCC,
                     "NAS_MSCC_IsMsplRecValid:Invalid network capability in MSPL record.");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_UpdateMsplIdInfo
Description     :   update parsed MSPL record info to ParseCtx.
Input parameters:   pstMsplId  - parsed MSPL record info
                    ucIndex - index, the MSPL ID to be written at
Outout parameters:  pstMsplParseCtx - ParseCtx
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-13
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_UpdateMsplIdInfo(
    NAS_MSCC_MSPL_PARSE_CTX_STRU       *pstMsplParseCtx,
    NAS_MSCC_MSPL_ID_STRU              *pstMsplId,
    VOS_UINT8                           ucIndex
)
{
    pstMsplParseCtx->pstMsplInfo->apstMsplId[ucIndex] = pstMsplId;

    if (VOS_TRUE == pstMsplId->ucIsMsplIdValid)
    {
        pstMsplParseCtx->ucNumValidMsplId++;
    }

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMlplBitStream
Description     :   Parse MLPL info.
Input parameters:   pucMlplBuff - MLPL buffer
                    ulBuffSize  - buff size in bytes
Outout parameters:  None
Return Value     :  NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32 NAS_MSCC_ParseMlplBitStream(
    VOS_UINT8                          *pucMlplBuff,
    VOS_UINT16                          usBuffSize
)
{
    NAS_MSCC_MLPL_PARSE_CTX_STRU                            stMlplParseCtx;
    VOS_UINT8                                               ucMlplRecCount;
    NAS_MSCC_PARSE_MLPL_REC_RSLT_ENUM_UINT32                enRecParseRslt;
    NAS_MSCC_PARSE_CRC_RSLT_ENUM_UINT32                     enCrcCause;
    VOS_UINT32                                              ulTempLen;
    NAS_MSCC_MLPL_RECORD_STRU                              *pstTempMlplRec;
    VOS_UINT8                                               ucIsDefaultRec;
    VOS_UINT32                                              ulRemainBitLength;
    VOS_UINT8                                               ucIndex;

    PS_MEM_SET(&stMlplParseCtx, 0, sizeof(NAS_MSCC_MLPL_PARSE_CTX_STRU));

    stMlplParseCtx.pucMlplSrcBuff = pucMlplBuff;
    stMlplParseCtx.usBuffSize     = usBuffSize;
    stMlplParseCtx.pstMlplInfo    = NAS_MSCC_GetMlplInfoAddr();

    NAS_MSCC_ResetMlplInfo(stMlplParseCtx.pstMlplInfo, 0);

    /* Parse MSPL header */
    if (NAS_MSCC_PARSE_MLPL_HDR_RSLT_SUCCESS != NAS_MSCC_ParseMlplHeader(&stMlplParseCtx))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,
                      "NAS_MSCC_ParseMlplBitStream:MLPL header parse failure!");
        return NAS_MSCC_PARSE_MLPL_RSLT_HDR_PARSE_FAIL;
    }

    stMlplParseCtx.usBuffSize = stMlplParseCtx.pstMlplInfo->stMlplHdr.usMlplSize;

    ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(stMlplParseCtx.usBuffSize,
                                                    stMlplParseCtx.usBitOffset);

    /* Get total no of MSPL_RECs */
    ucMlplRecCount = stMlplParseCtx.pstMlplInfo->stMlplHdr.ucNumMlplRec;

    ulTempLen      = 0;
    ucIndex        = 0;
    ucIsDefaultRec = VOS_FALSE;
    while ((ucMlplRecCount > 0)
        && (ulRemainBitLength >= NAS_MSCC_MLPL_DEFAULT_REC_MIN_BIT_LEN))
    {
        ulTempLen      = ulRemainBitLength;

        pstTempMlplRec = (NAS_MSCC_MLPL_RECORD_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                        sizeof(NAS_MSCC_MLPL_RECORD_STRU));
        if (VOS_NULL_PTR == pstTempMlplRec)
        {
            NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ParseMlplBitStream:Malloc failure!");

            NAS_MSCC_ResetMlplInfo(stMlplParseCtx.pstMlplInfo, ucIndex);
            return NAS_MSCC_PARSE_MLPL_RSLT_MALLOC_FAIL;
        }

        PS_MEM_SET(pstTempMlplRec, 0, sizeof(NAS_MSCC_MLPL_RECORD_STRU));

        /* Parse NUM_MSPL_ID struct */
        enRecParseRslt = NAS_MSCC_ParseMlplRec(&stMlplParseCtx,
                                        pstTempMlplRec,
                                        &ucIsDefaultRec);
        if (enRecParseRslt != NAS_MSCC_PARSE_MLPL_REC_RSLT_SUCCESS)
        {
            NAS_ERROR_LOG(UEPS_PID_MSCC,
                          "NAS_MSCC_ParseMlplBitStream:MLPL record parse failure!");

            NAS_MSCC_ResetMlplInfo(stMlplParseCtx.pstMlplInfo, ucIndex);
            return NAS_MSCC_PARSE_MLPL_RSLT_MLPL_REC_PARSE_FAIL;
        }

        ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(stMlplParseCtx.usBuffSize,
                                        stMlplParseCtx.usBitOffset);

        /* MLPL REC parse success, write this REC to global CTX */
        NAS_MSCC_UpdateMlplRecInfo(&stMlplParseCtx, pstTempMlplRec, ucIndex, ucIsDefaultRec);
        ucIsDefaultRec = VOS_FALSE;

        /* Update parsed bit len for MLPL_RECs, this will be used to calculate
           reserve bits at the end when parsing for all MLPL_RECs is finished
           successfully
        */
        stMlplParseCtx.ulParsedMlplRecBitLen += (ulTempLen - ulRemainBitLength);
        ucMlplRecCount--;
        ucIndex++;
    }

    if (ucMlplRecCount != 0)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMlplBitStream:Parse fail:RemainBitlen not enough to continue parse!Left ucMlplRecCount = ",
                       ucMlplRecCount);

        NAS_MSCC_ResetMlplInfo(stMlplParseCtx.pstMlplInfo, ucIndex);
        return NAS_MSCC_PARSE_MLPL_RSLT_FAIL;
    }

    if (0 == stMlplParseCtx.ucNumValidMlplRec)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,
                      "NAS_MSCC_ParseMlplBitStream:Parse fail:ucNumValidRecInMlpl is 0 in MLPL!");

        NAS_MSCC_ResetMlplInfo(stMlplParseCtx.pstMlplInfo, ucIndex);
        return NAS_MSCC_PARSE_MLPL_RSLT_FAIL;
    }

    /* Calculate and skip reserved bits after parsing of all MLPL records */
    NAS_MSCC_ProcResrvBitsInBuff(stMlplParseCtx.ulParsedMlplRecBitLen,
                                        &stMlplParseCtx.usBitOffset);

    ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(stMlplParseCtx.usBuffSize,
                                        stMlplParseCtx.usBitOffset);

    if (NAS_MSCC_MLPL_CRC_BIT_LEN == ulRemainBitLength)
    {
        stMlplParseCtx.pstMlplInfo->usMlplCrc = NAS_MSCC_BIT_TO_WORD(stMlplParseCtx.pucMlplSrcBuff,
                                                  stMlplParseCtx.usBitOffset,
                                                  NAS_MSCC_MLPL_CRC_BIT_LEN);
        NAS_MSCC_UPDATE_BIT_OFFSET(stMlplParseCtx.usBitOffset, NAS_MSCC_MLPL_CRC_BIT_LEN);

        enCrcCause = NAS_MSCC_CheckMlplMsplCrcChecksum(stMlplParseCtx.pucMlplSrcBuff);

        NAS_INFO_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMlplBitStream:CRC check result:",
                       enCrcCause);

        NAS_MSCC_MNTN_LogMlplMsplCrcChkRslt(enCrcCause, NAS_MSCC_MLPL_MSPL_PARSE_TYPE_MLPL);

        ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(stMlplParseCtx.usBuffSize,
                                        stMlplParseCtx.usBitOffset);
    }

    if (ulRemainBitLength != 0)
    {
        NAS_INFO_LOG1(UEPS_PID_MSCC,
                      "NAS_MSCC_ParseMlplBitStream:After MLPL parse, ulRemainBitLen = ",
                      ulRemainBitLength);
    }

    stMlplParseCtx.pstMlplInfo->ucIsMlplValid = VOS_TRUE;

    NAS_INFO_LOG(UEPS_PID_MSCC, "NAS_MSCC_ParseMlplBitStream:MLPL parse Success.");

    return NAS_MSCC_PARSE_MLPL_RSLT_SUCCESS;
}



/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMlplHeader
Description     :   Parse MLPL header info.
Input parameters:   pstMlplParseCtx - parse Ctx
Outout parameters:  pstMsplHeader - parsed MSPL hdr
Return Value     :  NAS_MSCC_PARSE_MSPL_HDR_RSLT_ENUM_UINT32
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
NAS_MSCC_PARSE_MLPL_HDR_RSLT_ENUM_UINT32 NAS_MSCC_ParseMlplHeader(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx
)
{
    NAS_MSCC_MLPL_HEADER_STRU          *pstMlplHeader;

    pstMlplHeader = &pstMlplParseCtx->pstMlplInfo->stMlplHdr;

    /* Parse MLPL_SIZE */
    pstMlplHeader->usMlplSize = NAS_MSCC_BIT_TO_WORD(pstMlplParseCtx->pucMlplSrcBuff,
                                                     pstMlplParseCtx->usBitOffset,
                                                     NAS_MSCC_MLPL_MLPL_SIZE_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_MLPL_SIZE_BIT_LEN);

    if (0 == pstMlplHeader->usMlplSize)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMlplHeader:Parse fail:MLPL_SIZE = ",
                       pstMlplHeader->usMlplSize);
        return NAS_MSCC_PARSE_MLPL_HDR_RSLT_FAIL;
    }

    if (pstMlplParseCtx->usBuffSize < pstMlplHeader->usMlplSize)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMlplHeader:Parse fail:Input BuffSize is lesser than MLPL_SIZE, BuffSize = ",
                       pstMlplParseCtx->usBuffSize);
        return NAS_MSCC_PARSE_MLPL_HDR_RSLT_FAIL;
    }

    if (NAS_MSCC_CONVERT_BYTES_TO_BITS(pstMlplHeader->usMlplSize) < NAS_MSCC_MLPL_MIN_BIT_LEN)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ParseMlplHeader:Parse fail:MLPL_SIZE is lesser than NAS_MSCC_MSPL_MIN_BIT_LEN!");
        return NAS_MSCC_PARSE_MLPL_HDR_RSLT_FAIL;
    }

    if (pstMlplParseCtx->usBuffSize > pstMlplHeader->usMlplSize)
    {
        NAS_INFO_LOG1(UEPS_PID_MSCC,
                      "NAS_MSCC_ParseMlplHeader:Input buffer size greater than MLPL_SIZE, BuffSize = ",
                      pstMlplParseCtx->usBuffSize);
    }

    /* Parse CUR_MMSS_P_REV */
    pstMlplHeader->ucCurrProtRev = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                                        pstMlplParseCtx->usBitOffset,
                                                        NAS_MSCC_MLPL_CUR_MMSS_P_REV_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_CUR_MMSS_P_REV_BIT_LEN);


    /* Parse MLPL_VER_ID */
    pstMlplHeader->usMlplVerId = NAS_MSCC_BIT_TO_WORD(pstMlplParseCtx->pucMlplSrcBuff,
                                                      pstMlplParseCtx->usBitOffset,
                                                      NAS_MSCC_MLPL_MLPL_VER_ID_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_MLPL_VER_ID_BIT_LEN);

    /* Parse MLPL_ID */
    pstMlplHeader->ucMlplId = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                                   pstMlplParseCtx->usBitOffset,
                                                   NAS_MSCC_MLPL_MLPL_ID_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_MLPL_ID_BIT_LEN);

    /* Parse NUM_MLPL_REC */
    pstMlplHeader->ucNumMlplRec = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                                      pstMlplParseCtx->usBitOffset,
                                                      NAS_MSCC_MLPL_NUM_MLPL_REC_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_NUM_MLPL_REC_BIT_LEN);

    if (0 == pstMlplHeader->ucNumMlplRec)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ParseMlplHeader:Parse fail:NUM_MLPL_REC is 0!");
        return NAS_MSCC_PARSE_MLPL_HDR_RSLT_FAIL;
    }

    return NAS_MSCC_PARSE_MLPL_HDR_RSLT_SUCCESS;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMlplRec
Description     :   Parse MLPL record.
Input parameters:   pstMlplParseCtx - parse Ctx
Outout parameters:  pstMlplRec - parsed MLPL record
                    pucIsDefaultRec - flag to indicate if record is of default type
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
NAS_MSCC_PARSE_MLPL_REC_RSLT_ENUM_UINT32 NAS_MSCC_ParseMlplRec(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx,
    NAS_MSCC_MLPL_RECORD_STRU          *pstMlplRec,
    VOS_UINT8                          *pucIsDefaultRec
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRemainBitLength;
    VOS_UINT8                           ucSysLocTagNum;
    VOS_UINT8                           ucNumValidSysLocTag;

    pstMlplRec->ucIsRecValid = VOS_TRUE;

    /* Parse LOC_PARAM_TYPE, It can be 0 */
    pstMlplRec->ucLocParamType = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                       pstMlplParseCtx->usBitOffset,
                                       NAS_MSCC_MLPL_REC_LOC_PARAM_TYPE_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_REC_LOC_PARAM_TYPE_BIT_LEN);

    ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(pstMlplParseCtx->usBuffSize,
                                        pstMlplParseCtx->usBitOffset);

    if (NAS_MSCC_IS_DEFAULT_MLPL_REC(pstMlplRec->ucLocParamType))
    {
        *pucIsDefaultRec = VOS_TRUE;

        /* Parse MSPL_INDEX */
        pstMlplRec->ucMsplIndex = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                        pstMlplParseCtx->usBitOffset,
                                        NAS_MSCC_MLPL_REC_MSPL_INDEX_BIT_LEN);
        NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_REC_MSPL_INDEX_BIT_LEN);

        return NAS_MSCC_PARSE_MLPL_REC_RSLT_SUCCESS;
    }

    if (VOS_FALSE == NAS_MSCC_IsEnoughBitLenToParseLocParamVal(pstMlplRec->ucLocParamType,
                                        ulRemainBitLength))
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMlplRec:Parse fail:Insufficient len to continue parse,RemainBitLen = ",
                       ulRemainBitLength);
        return NAS_MSCC_PARSE_MLPL_REC_RSLT_INSUFFICIENT_DATA_LEN;
    }

    if ((pstMlplRec->ucLocParamType) & NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC)
    {
        /* Parse MCC */
        pstMlplRec->stLocParamVal.usMcc = NAS_MSCC_BIT_TO_WORD(pstMlplParseCtx->pucMlplSrcBuff,
                                        pstMlplParseCtx->usBitOffset,
                                        NAS_MSCC_MLPL_LOC_PARAM_MCC_BIT_LEN);
        NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_LOC_PARAM_MCC_BIT_LEN);
    }

    if ((pstMlplRec->ucLocParamType) & NAS_MSCC_MLPL_LOC_PARAM_BIT_MNC)
    {
        /* Parse MNC */
        pstMlplRec->stLocParamVal.usMnc = NAS_MSCC_BIT_TO_WORD(pstMlplParseCtx->pucMlplSrcBuff,
                                        pstMlplParseCtx->usBitOffset,
                                        NAS_MSCC_MLPL_LOC_PARAM_MNC_BIT_LEN);
        NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_LOC_PARAM_MNC_BIT_LEN);
    }

    ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(pstMlplParseCtx->usBuffSize,
                                        pstMlplParseCtx->usBitOffset);

    if ((pstMlplRec->ucLocParamType) & NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG)
    {
        /* Parse NUM_SYS_LOC_TAG */
        pstMlplRec->stLocParamVal.ucNumSysLocTag = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                        pstMlplParseCtx->usBitOffset,
                                        NAS_MSCC_MLPL_LOC_PARAM_NUM_SYS_LOC_TAG_BIT_LEN);
        NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_LOC_PARAM_NUM_SYS_LOC_TAG_BIT_LEN);


        ucSysLocTagNum    = pstMlplRec->stLocParamVal.ucNumSysLocTag;
        ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(pstMlplParseCtx->usBuffSize,
                                        pstMlplParseCtx->usBitOffset);

        ucIndex = 0;
        ucNumValidSysLocTag = 0;
        while ((ucSysLocTagNum > 0)
            && (ulRemainBitLength >= NAS_MSCC_MLPL_SYS_LOC_TAG_MIN_BIT_LEN))
        {
            NAS_MSCC_ParseMlplSysLocTag(pstMlplParseCtx, &pstMlplRec->stLocParamVal.astSysLocTag[ucIndex]);

            if (VOS_TRUE == pstMlplRec->stLocParamVal.astSysLocTag[ucIndex].ucIsLocTagValid)
            {
                ucNumValidSysLocTag++;
            }

            ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(pstMlplParseCtx->usBuffSize,
                                        pstMlplParseCtx->usBitOffset);

            ucSysLocTagNum--;
            ucIndex++;
        }

        if (ucSysLocTagNum != 0)
        {
            pstMlplRec->ucIsRecValid = VOS_FALSE;

            NAS_ERROR_LOG1(UEPS_PID_MSCC,
                           "NAS_MSCC_ParseMlplRec:Parse fail:Insufficient len to continue parse,RemainBitLen = ",
                           ulRemainBitLength);
            return NAS_MSCC_PARSE_MLPL_REC_RSLT_INSUFFICIENT_DATA_LEN;
        }

        if (pstMlplRec->stLocParamVal.ucNumSysLocTag != 0)
        {
            pstMlplRec->ucIsRecValid = ((0 == ucNumValidSysLocTag) ? VOS_FALSE : VOS_TRUE);
        }
    }

    if (ulRemainBitLength < NAS_MSCC_MLPL_REC_MSPL_INDEX_BIT_LEN)
    {
        pstMlplRec->ucIsRecValid = VOS_FALSE;

        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_ParseMlplRec:Parse fail:Insufficient len to parse MSPL_INDEX,RemainBitLen = ",
                       ulRemainBitLength);
        return NAS_MSCC_PARSE_MLPL_REC_RSLT_INSUFFICIENT_DATA_LEN;
    }

    /* Parse MSPL_INDEX */
    pstMlplRec->ucMsplIndex = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                                   pstMlplParseCtx->usBitOffset,
                                                   NAS_MSCC_MLPL_REC_MSPL_INDEX_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_REC_MSPL_INDEX_BIT_LEN);

    return NAS_MSCC_PARSE_MLPL_REC_RSLT_SUCCESS;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMlplSysLocTag
Description     :   Parse System location tag in LOC_PARAM in MLPL record.
Input parameters:   pstMlplParseCtx - parse Ctx
Outout parameters:  pstSysLocTag - parsed system location tag
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_ParseMlplSysLocTag(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx,
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU     *pstSysLocTag
)
{
    VOS_UINT32                          ulRemainBitLength;
    VOS_UINT8                           ucSubntLen;

    pstSysLocTag->ucIsLocTagValid = VOS_FALSE;

    /* Parse SYS_TYPE */
    pstSysLocTag->enSysType = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                        pstMlplParseCtx->usBitOffset,
                                        NAS_MSCC_MLPL_LOC_PARAM_SYS_TYPE_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_LOC_PARAM_SYS_TYPE_BIT_LEN);

    /* Parse SYS_LOC_TAG_SIZE, it contains no of bits. */
    pstSysLocTag->ucSysLocTagSize = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                        pstMlplParseCtx->usBitOffset,
                                        NAS_MSCC_MLPL_LOC_PARAM_SYS_LOC_TAG_SIZE_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_LOC_PARAM_SYS_LOC_TAG_SIZE_BIT_LEN);

    ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(pstMlplParseCtx->usBuffSize,
                                                    pstMlplParseCtx->usBitOffset);

    if (ulRemainBitLength < pstSysLocTag->ucSysLocTagSize)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                      "NAS_MSCC_ParseMlplSysLocTag:Insufficient remainBitlen to continue parse sys loc tag,SysLocTagSize = ",
                      pstSysLocTag->ucSysLocTagSize);

        /* Skip the bits to break loop in caller and to return MLPL_PARSE_FAIL */
        NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, (VOS_UINT16)ulRemainBitLength);

        return;
    }

    if (0 == pstSysLocTag->ucSysLocTagSize)
    {
        NAS_INFO_LOG(UEPS_PID_MSCC,
                     "NAS_MSCC_ParseMlplSysLocTag:System location tag size is either 0!");
        return;
    }

    switch (pstSysLocTag->enSysType)
    {
        case NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI:
        case NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_1X:
        {
            NAS_MSCC_ParseMlplSysLocTagCdma2000(pstMlplParseCtx, pstSysLocTag);

            pstSysLocTag->ucIsLocTagValid = VOS_TRUE;
            break;
        }
        case NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI:
        case NAS_MSCC_MLPL_MSPL_SYS_TYPE_GSM:
        case NAS_MSCC_MLPL_MSPL_SYS_TYPE_UMTS:
        case NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE:
        {
            NAS_MSCC_ParseMlplSysLocTag3Gpp(pstMlplParseCtx, pstSysLocTag);

            pstSysLocTag->ucIsLocTagValid = VOS_TRUE;
            break;
        }
        case NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD:
        {
            /* System location tag parameter and len in bits
            ___________________________________
            |SUBNET_LENGTH ------ 8             |
            |SUBNET_ID ---------- SUBNET_LENGTH |
            |RESERVED ----------- 0 or 7        |
            -----------------------------------
            */
            /* Parse SUBNET_LENGTH */
            ucSubntLen = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                        pstMlplParseCtx->usBitOffset,
                                        NAS_MSCC_MLPL_LOC_TAG_SUBNET_LENGTH_BIT_LEN);

            NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_LOC_TAG_SUBNET_LENGTH_BIT_LEN);

            ucSubntLen = ((ucSubntLen > NAS_MSCC_MLPL_SYS_TAG_CDMA2000_MAX_SUBNET_BIT_LEN)
                            ? NAS_MSCC_MLPL_SYS_TAG_CDMA2000_MAX_SUBNET_BIT_LEN : ucSubntLen);

            /* Assumption and behaviour : if SubnetLen is greater than 128 bits,
               only first 128 bits will be considered and parsed as subnet*/
            pstSysLocTag->unSysLocTag.stSysLocTagCdma2000Hrpd.ucSubnetLen = ucSubntLen;

            /* Update remainBitLen available for parsing */
            ulRemainBitLength = NAS_MSCC_GET_REMAIN_BIT_LEN(pstMlplParseCtx->usBuffSize,
                                        pstMlplParseCtx->usBitOffset);
            if (ucSubntLen > ulRemainBitLength)
            {
                /* Skip the bits to break loop in caller and to fail the parsing */
                NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, (VOS_UINT8)ulRemainBitLength);
                break;
            }

            NAS_MSCC_ParseMlplSysLocTagCdma2000Hrpd(pstMlplParseCtx, pstSysLocTag);

            pstSysLocTag->ucIsLocTagValid = VOS_TRUE;
            break;
        }
        default:
        {
            pstSysLocTag->ucIsLocTagValid = VOS_FALSE;
            NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, pstSysLocTag->ucSysLocTagSize);
            break;
        }
    }

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMlplSysLocTagCdma2000
Description     :   Parse sys location tag for system type (cdma2000_AI) or (cdma2000 1x).
Input parameters:   pstMlplParseCtx - parse Ctx
Outout parameters:  pstSysLocTag - system location tag
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-11
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_ParseMlplSysLocTagCdma2000(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx,
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU     *pstSysLocTag
)
{
    VOS_UINT16                          usSID;
    VOS_UINT16                          usNIDStrt;
    VOS_UINT8                           ucNIDRange;

    /* System location tag parameter and len in bits
        |RESERVED -------- 1 |
        |SID ------------ 15 |
        |NID_START ------ 16 |
        |NID_RANGE ------- 8 |
    */
    /* Parse SID */
    usSID = NAS_MSCC_BIT_TO_WORD(pstMlplParseCtx->pucMlplSrcBuff,
                                 pstMlplParseCtx->usBitOffset,
                                 NAS_MSCC_MLPL_LOC_TAG_SID_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_LOC_TAG_SID_BIT_LEN);

    /* Remove the reserve bit */
    usSID &= 0x7FFF;

    pstSysLocTag->unSysLocTag.stSysLocTagCdma2000.usSid = usSID;

    /* Parse NID_START */
    usNIDStrt = NAS_MSCC_BIT_TO_WORD(pstMlplParseCtx->pucMlplSrcBuff,
                                    pstMlplParseCtx->usBitOffset,
                                    NAS_MSCC_MLPL_LOC_TAG_NID_START_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_LOC_TAG_NID_START_BIT_LEN);

    pstSysLocTag->unSysLocTag.stSysLocTagCdma2000.usNidStart = usNIDStrt;

    /* Parse NID_RANGE */
    ucNIDRange = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                      pstMlplParseCtx->usBitOffset,
                                      NAS_MSCC_MLPL_LOC_TAG_NID_RANGE_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_LOC_TAG_NID_RANGE_BIT_LEN);

    pstSysLocTag->unSysLocTag.stSysLocTagCdma2000.ucNidRange = ucNIDRange;

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMlplSysLocTag3Gpp
Description     :   Parse sys location tag for system type (3GPP_AI),
                    (GERAN (GSM)), (UTRAN (UMTS))  or (EUTRAN (LTE)).
Input parameters:   pstMlplParseCtx - parse Ctx
Outout parameters:  pstSysLocTag - system location tag
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-11
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_ParseMlplSysLocTag3Gpp(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx,
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU     *pstSysLocTag
)
{
    VOS_UINT8                           ucPLMNStrt;
    VOS_UINT8                           ucPLMNRange;
    VOS_UINT8                           ucIndex;

    /* System location tag parameter and len in bits
         _________________________
        |PLMN_START ---------- 24 |
        |PLMN_RANGE ----------  8 |
         -------------------------
    */
    ucIndex = 0;
    while (ucIndex < NAS_MSCC_MLPL_LOC_TAG_PLMN_START_NUM_OCTET)
    {
        /* Parse PLMN_START */
        ucPLMNStrt = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                          pstMlplParseCtx->usBitOffset,
                                          NAS_MSCC_BIT_LEN_8_BIT);

        NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_BIT_LEN_8_BIT);

        pstSysLocTag->unSysLocTag.stSysLocTag3GPP.aucPlmnStart[ucIndex++] = ucPLMNStrt;
    }

    /* Parse PLMN_RANGE */
    ucPLMNRange = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                       pstMlplParseCtx->usBitOffset,
                                       NAS_MSCC_MLPL_LOC_TAG_PLMN_RANGE_BIT_LEN);
    NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, NAS_MSCC_MLPL_LOC_TAG_PLMN_RANGE_BIT_LEN);

    pstSysLocTag->unSysLocTag.stSysLocTag3GPP.ucPlmnRange = ucPLMNRange;

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ParseMlplSysLocTagCdma2000Hrpd
Description     :   Parse sys location tag for system type (cdma2000 HRPD).
Input parameters:   pstMlplParseCtx - parse Ctx
Outout parameters:  pstSysLocTag - system location tag
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-11
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_ParseMlplSysLocTagCdma2000Hrpd(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx,
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU     *pstSysLocTag
)
{
    VOS_UINT8                           ucSubntIdBitLen;
    VOS_UINT8                           ucSubntId;
    VOS_UINT8                           ucParsedSubntIdLen;
    VOS_UINT8                           ucLocTagBitLenParsed;
    VOS_UINT8                           ucIndex;

    /* System location tag parameter and len in bits
         ___________________________________
        |SUBNET_LENGTH ------ 8             |
        |SUBNET_ID ---------- SUBNET_LENGTH |
        |RESERVED ----------- 0 or 7        |
         -----------------------------------
    */

    ucLocTagBitLenParsed = 0;
    ucSubntIdBitLen = pstSysLocTag->unSysLocTag.stSysLocTagCdma2000Hrpd.ucSubnetLen;

    /* Parse SUBNET_ID */

    ucIndex = 0;
    while (ucSubntIdBitLen > 0)
    {
        ucParsedSubntIdLen = ((ucSubntIdBitLen >= NAS_MSCC_BIT_LEN_8_BIT)
                            ? NAS_MSCC_BIT_LEN_8_BIT : ucSubntIdBitLen);

        /* Parse PLMN_START - total 24 bits, first read 16 bits */
        ucSubntId = NAS_MSCC_BIT_TO_BYTE(pstMlplParseCtx->pucMlplSrcBuff,
                                          pstMlplParseCtx->usBitOffset,
                                          ucParsedSubntIdLen);
        NAS_MSCC_UPDATE_BIT_OFFSET(pstMlplParseCtx->usBitOffset, ucParsedSubntIdLen);

        pstSysLocTag->unSysLocTag.stSysLocTagCdma2000Hrpd.aucSubnetId[ucIndex++] = ucSubntId;

        ucLocTagBitLenParsed += ucParsedSubntIdLen;

        ucSubntIdBitLen -= ucParsedSubntIdLen;
    }

    /* Skip RESERVED bits */
    NAS_MSCC_ProcResrvBitsInBuff((VOS_UINT32)ucLocTagBitLenParsed, &pstMlplParseCtx->usBitOffset);

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_IsEnoughBitLenToParseLocParamVal
Description     :   To check if Remain bit len is enough to parse LOC_PARAM_VAL.
Input parameters:   ucLocParamType  - Loc param type
                    ulRemainBitLength - Remain bit len in input buffer
Outout parameters:  None
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-12
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
VOS_UINT8 NAS_MSCC_IsEnoughBitLenToParseLocParamVal(
    VOS_UINT8                           ucLocParamType,
    VOS_UINT32                          ulRemainBitLength
)
{
    VOS_UINT32                          ulBitLenRequired;

    ulBitLenRequired = 0;

    if (ucLocParamType & NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC)
    {
        /* Parse MCC */
        ulBitLenRequired += NAS_MSCC_MLPL_LOC_PARAM_MCC_BIT_LEN;
    }

    if (ucLocParamType & NAS_MSCC_MLPL_LOC_PARAM_BIT_MNC)
    {
        /* Parse MNC */
        ulBitLenRequired += NAS_MSCC_MLPL_LOC_PARAM_MNC_BIT_LEN;
    }

    if (ucLocParamType & NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG)
    {
        ulBitLenRequired += NAS_MSCC_MLPL_LOC_PARAM_NUM_SYS_LOC_TAG_BIT_LEN;
    }

    if (ulRemainBitLength >= ulBitLenRequired)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_UpdateMlplRecInfo
Description     :   update parsed MLPL record info to ParseCtx.
Input parameters:   pstMlplRec  - parsed Mlpl record info
                    ucIndex - index, the MLPL REC to be written at
                    ucIsDefaultRec - if currecnt rec is default type
Outout parameters:  pstMlplParseCtx - ParseCtx
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-13
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_UpdateMlplRecInfo(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx,
    NAS_MSCC_MLPL_RECORD_STRU          *pstMlplRec,
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucIsDefaultRec
)
{
    pstMlplParseCtx->pstMlplInfo->apstMlplRec[ucIndex] = pstMlplRec;

    if (VOS_TRUE == pstMlplRec->ucIsRecValid)
    {
        pstMlplParseCtx->ucNumValidMlplRec++;
    }

    if ((VOS_TRUE == ucIsDefaultRec)
     && (VOS_FALSE == pstMlplParseCtx->pstMlplInfo->ucIsContainDefRec))
    {
        pstMlplParseCtx->pstMlplInfo->ucIsContainDefRec = VOS_TRUE;
        pstMlplParseCtx->pstMlplInfo->ucMsplIdxInFirstDefRec = pstMlplRec->ucMsplIndex;

    }

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_IsSystemTypeValid
Description     :   to check if system type is valid.
Input parameters:   enSysType - input system type
Outout parameters:  None
Return Value     :  VOS_BOOL
Modify History:
    1)  Date    :   2015-04-07
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
VOS_UINT8 NAS_MSCC_IsSystemTypeValid(
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType
)
{

    if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI == enSysType)
     || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == enSysType)
     || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_WIMAX == enSysType)
     || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_1X == enSysType)
     || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == enSysType)
     || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_GSM == enSysType)
     || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_UMTS == enSysType)
     || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE == enSysType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ProcResrvBitsInBuff
Description     :   fun to calculate and process reserve bits in input buffer.
Input parameters:   ulParsedBitLen - Parsed bit len
Outout parameters:  pusBitOffset - bit offset
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-13
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcResrvBitsInBuff(
    VOS_UINT32                          ulParsedBitLen,
    VOS_UINT16                         *pusBitOffset
)
{
    VOS_UINT8                           ucReservedBits;

    ucReservedBits = (ulParsedBitLen) % 8;
    ucReservedBits = NAS_MSCC_BIT_LEN_8_BIT - ucReservedBits;
    ucReservedBits = ((NAS_MSCC_BIT_LEN_8_BIT == ucReservedBits) ? 0 : ucReservedBits);

    NAS_MSCC_UPDATE_BIT_OFFSET(*pusBitOffset, ucReservedBits);
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ResetMsplInfo
Description     :   to reset MSPL struct
Input parameters:   pstMsplInfo - MsPL info struct
                    ucMaxIndex - max index to be used
Outout parameters:  None
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-16
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_ResetMsplInfo(
    NAS_MSCC_MSPL_STRU                 *pstMsplInfo,
    VOS_UINT8                           ucMaxIndex
)
{
    VOS_UINT8                           ucIndex;

    ucIndex = 0;
    while (ucIndex < ucMaxIndex)
    {
        PS_MEM_FREE(UEPS_PID_MSCC, pstMsplInfo->apstMsplId[ucIndex++]);
    }

    PS_MEM_SET(pstMsplInfo, 0, sizeof(NAS_MSCC_MSPL_STRU));

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ResetMlplInfo
Description     :   to reset MLPL struct.
Input parameters:   pstMlplInfo - MLPL info struct
                    ucMaxIndex - max index to be used
Outout parameters:  None
Return Value     :  VOS_VOID
Modify History:
    1)  Date    :   2015-04-16
        Author  :   n00742771
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_ResetMlplInfo(
    NAS_MSCC_MLPL_STRU                 *pstMlplInfo,
    VOS_UINT8                           ucMaxIndex
)
{
    VOS_UINT8                           ucIndex;

    ucIndex = 0;
    while (ucIndex < ucMaxIndex)
    {
        PS_MEM_FREE(UEPS_PID_MSCC, pstMlplInfo->apstMlplRec[ucIndex++]);
    }

    PS_MEM_SET(pstMlplInfo, 0, sizeof(NAS_MSCC_MLPL_STRU));

    return;
}



VOS_UINT8 NAS_MSCC_ConvertMsplBsrTimerLenToMillisec(
    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_ENUM_UINT8           enInPriSrchTime,
    VOS_UINT32                                             *pusOutMillSec
)
{
    VOS_UINT8                                               i;

    for (i = 0; i < NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_COUNT; i++)
    {
        if (enInPriSrchTime == g_astMsplSrchTimeMillsecMap[i].enPriSrchTime)
        {
            *pusOutMillSec = g_astMsplSrchTimeMillsecMap[i].usMilliSec;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

