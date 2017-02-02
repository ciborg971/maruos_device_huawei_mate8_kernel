

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTA_COMM_C


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafMtaComm.h"
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_UINT32 TAF_MTA_Ac2ul(
    VOS_CHAR                           *pcStr,
    VOS_UINT32                          ulLen,
    VOS_UINT32                         *pulRtn
)
{
    VOS_UINT32                          ulTotal;            /* current Total */
    VOS_UINT32                          ulLength;           /* current Length */
    VOS_CHAR                            cCur;               /* current Char */

    /* ���ָ�벻��Ϊ��ָ�� */
    if ((VOS_NULL_PTR == pcStr) || (VOS_NULL_PTR == pulRtn))
    {
        return VOS_ERR;
    }

    /* ulLen����Ϊ0 */
    if (0 == ulLen)
    {
        return VOS_ERR;
    }

    cCur        = *(pcStr++);
    ulLength    = 0;
    ulTotal     = 0;
    while(ulLength++ < ulLen)
    {
        if ((cCur >= '0') && (cCur <= '9'))
        {
            /* 0xFFFFFFFF = 4294967295 */
            if ( ((ulTotal == MTA_UNSIGNED_LONG_FORMER_NINE_DIGIT) && (cCur > MTA_UNSIGNED_LONG_LAST_DIGIT))
              || (ulTotal > MTA_UNSIGNED_LONG_FORMER_NINE_DIGIT) )
            {
                /* ��������������֧�ֵ����ֵ */
                return VOS_ERR;
            }
            ulTotal = (ulTotal * 10) + (cCur - '0');
            cCur    = *(pcStr++);
        }
        else
        {
            return VOS_ERR;
        }
    }

    *pulRtn = ulTotal;
    return VOS_OK;
}
VOS_UINT32 TAF_MTA_Ac2us(
    VOS_CHAR                           *pcStr,
    VOS_UINT32                          ulLen,
    VOS_UINT16                         *pusRtn
)
{
    VOS_UINT32                          ulLength;           /* current Length */
    VOS_UINT16                          usTotal;            /* current Total */
    VOS_CHAR                            cCur;               /* current Char */

    /* ���ָ�벻��Ϊ��ָ�� */
    if ((VOS_NULL_PTR == pcStr) || (VOS_NULL_PTR == pusRtn))
    {
        return VOS_ERR;
    }

    /* ulLen����Ϊ0 */
    if (0 == ulLen)
    {
        return VOS_ERR;
    }

    cCur        = *(pcStr++);
    ulLength    = 0;
    usTotal     = 0;
    while(ulLength++ < ulLen)
    {
        if ((cCur >= '0') && (cCur <= '9'))
        {
            /* 0xFFFF = 65535 */
            if ( ((usTotal == MTA_UNSIGNED_SHORT_FORMER_FOUR_DIGIT) && (cCur > MTA_UNSIGNED_SHORT_LAST_DIGIT))
              || (usTotal > MTA_UNSIGNED_SHORT_FORMER_FOUR_DIGIT) )
            {
                /* ��������������֧�ֵ����ֵ */
                return VOS_ERR;
            }
            usTotal = (VOS_UINT16)((usTotal * 10) + (cCur - '0'));
            cCur    = *(pcStr++);
        }
        else
        {
            return VOS_ERR;
        }
    }

    *pusRtn = usTotal;
    return VOS_OK;
}
VOS_UINT32 TAF_MTA_Ac2uc(
    VOS_CHAR                           *pcStr,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucRtn
)
{
    VOS_UINT32                          ulLength;           /* current Length */
    VOS_UINT8                           ucTotal;            /* current Total */
    VOS_CHAR                            cCur;               /* current Char */

    /* ���ָ�벻��Ϊ��ָ�� */
    if ((VOS_NULL_PTR == pcStr) || (VOS_NULL_PTR == pucRtn))
    {
        return VOS_ERR;
    }

    /* ulLen����Ϊ0 */
    if (0 == ulLen)
    {
        return VOS_ERR;
    }

    cCur        = *(pcStr++);
    ulLength    = 0;
    ucTotal     = 0;
    while(ulLength++ < ulLen)
    {
        if ((cCur >= '0') && (cCur <= '9'))
        {
            /* 0xFF = 255 */
            if ( ((ucTotal == MTA_UNSIGNED_CHAR_FORMER_TWO_DIGIT) && (cCur > MTA_UNSIGNED_CHAR_LAST_DIGIT))
              || (ucTotal > MTA_UNSIGNED_CHAR_FORMER_TWO_DIGIT) )
            {
                /* ��������������֧�ֵ����ֵ */
                return VOS_ERR;
            }
            ucTotal = (VOS_UINT8)((ucTotal * 10) + (cCur - '0'));
            cCur    = *(pcStr++);
        }
        else
        {
            return VOS_ERR;
        }
    }

    *pucRtn = ucTotal;
    return VOS_OK;
}
VOS_UINT32 TAF_MTA_Ac2sl(
    VOS_CHAR                           *pcStr,
    VOS_UINT32                          ulLen,
    VOS_INT32                          *plRtn
)
{
    VOS_INT32                           lSign;
    VOS_INT32                           lTotal;             /* current Total */
    VOS_UINT32                          ulLength;           /* current Length */
    VOS_CHAR                            cCur;               /* current Char */
    VOS_CHAR                            cTmp;

    /* ���ָ�벻��Ϊ��ָ�� */
    if ((VOS_NULL_PTR == pcStr) || (VOS_NULL_PTR == plRtn))
    {
        return VOS_ERR;
    }

    /* ulLen����Ϊ0 */
    if (0 == ulLen)
    {
        return VOS_ERR;
    }

    cCur        = *(pcStr++);
    ulLength    = 0;
    lTotal      = 0;

    /* �жϷ���λ */
    if ('-' == cCur )
    {
        lSign = MTA_NEGATIVE;
        cCur  = *(pcStr++);
        cTmp  = MTA_SIGNED_LONG_NEGATIVE_LAST_DIGIT;
        ulLength++;
    }
    else if ('+' == cCur )
    {
        lSign = MTA_POSITIVE;
        cCur  = *(pcStr++);
        cTmp  = MTA_SIGNED_LONG_POSITIVE_LAST_DIGIT;
        ulLength++;
    }
    else
    {
        /* ��"+"��"-"���ţ������������� */
        lSign = MTA_POSITIVE;
        cTmp  = MTA_SIGNED_LONG_POSITIVE_LAST_DIGIT;
    }

    while(ulLength++ < ulLen)
    {
        if ((cCur >= '0') && (cCur <= '9'))
        {
            /* 0x7FFFFFFF = 2147483647 */
            if ( ((lTotal == MTA_SIGNED_LONG_FORMER_NINE_DIGIT) && (cCur > cTmp))
              || (lTotal > MTA_SIGNED_LONG_FORMER_NINE_DIGIT) )
            {
                /* ��������������֧�ֵ����ֵ */
                return VOS_ERR;
            }
            lTotal  = (10 * lTotal) + (cCur - '0');
            cCur    = *(pcStr++);
        }
        else
        {
            return VOS_ERR;
        }
    }

    *plRtn = lTotal * lSign;
    return VOS_OK;
}

/*lint +e958*/


VOS_UINT32 TAF_MTA_AcNums2DecNums(
    VOS_UINT8                          *pucAsciiNum,
    VOS_UINT8                          *pucDecNum,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulIndex         = 0;

    /* ����ָ���ɵ����߱�֤��ΪNULL, �ô������ж� */

    for (ulIndex = 0; ulIndex < ulLen; ulIndex++)
    {
        /* �ж��Ƿ������� */
        if ( ('0' <= pucAsciiNum[ulIndex]) && ('9' >= pucAsciiNum[ulIndex]) )
        {
            pucDecNum[ulIndex] = pucAsciiNum[ulIndex] - '0';
        }
        else
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
