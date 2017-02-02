/************************************************************************
*                                                                      *
*                             stac.c                                   *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/06/21                                      *
*  Author:             SHIY YONG                                       *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           STAC��ʵ�ֺͶ���ӿں���                        *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*                       STAC��ʵ�ֺͶ���ӿں���                         *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_VSNCP_STAC_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

#if( VRP_MODULE_STAC == VRP_YES )
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/****************************************************************************
* CREATE DATE    : 2000-6-21
* CREATED BY    : SHI YONG
* FUNCTION        : Initialize stac compression
* MODIFY DATE    :
* MODIFIED BY    :
* INPUT            : STAC_COMPRESSINFO_S *pstInfo
* OUTPUT        :
* RETURN        : STAC_SUCCESS -- 0
*                 STAC_FAIL -- 1;
* CALLED BY     :
****************************************************************************/
LONG STAC_InitStacCompress( STAC_COMPRESSINFO_S *pstInfo )
{

    pstInfo->pucInputStream = VOS_NULL_PTR;
    pstInfo->usInlen = 0;
    pstInfo->pucOutputStream = VOS_NULL_PTR;
    pstInfo->usOutlen = 0;

    pstInfo->usBufferTail = 0;
    pstInfo->pucHoldBuf = VOS_NULL_PTR;
    pstInfo->usHoldLen = 0;

    /*�����λ���*/
    pstInfo->ucBitMask = 0x80;

    pstInfo->ucSequenceNum = 1;
    pstInfo->pucOutput = VOS_NULL_PTR;

    return STAC_SUCCESS;
}


/****************************************************************************
* CREATE DATE    : 2000-6-21
* CREATED BY    : SHI YONG
* FUNCTION        : Exit StacCompress
* MODIFY DATE    :
* MODIFIED BY    :
* INPUT            : STAC_COMPRESSINFO_S *pstInfo
* OUTPUT        :
* RETURN        :
* CALLED BY     :
****************************************************************************/
VOID  STAC_ExitStacCompress( STAC_COMPRESSINFO_S * pstInfo )
{
    /* Deleted start by liutao 38563 at 2004-11-09 V800R002 for PPPC��ֲ */
 #if 0
    if (pstInfo->pstHashTable != VOS_NULL_PTR)
    {
        STAC_HASH_FreeHashTable( pstInfo->pstHashTable );
        pstInfo->pstHashTable = VOS_NULL_PTR;
    }

    if (pstInfo->pucBuffer != VOS_NULL_PTR)
    {
        (VOID)PPP_Free( pstInfo->pucBuffer );
        pstInfo->pucBuffer = VOS_NULL_PTR;
    }
 #endif

    /* Deleted end by liutao 38563 at 2004-11-09 V800R002 for PPPC��ֲ */

    /*�ص���ʼ״̬*/
    pstInfo->pucInputStream = VOS_NULL_PTR;
    pstInfo->usInlen = 0;
    pstInfo->pucOutputStream = VOS_NULL_PTR;
    pstInfo->usOutlen = 0;
    pstInfo->usBufferTail = 0;
    pstInfo->pucHoldBuf = VOS_NULL_PTR;
    pstInfo->usHoldLen = 0;
    pstInfo->ucBitMask = 0x80;
    pstInfo->ucSequenceNum = 0;
    pstInfo->pucOutput = VOS_NULL_PTR;

    return;
}


/****************************************************************************
* CREATE DATE    : 2000-6-21
* CREATED BY    : SHI YONG
* FUNCTION        : Init StacDecompress
* MODIFY DATE    :
* MODIFIED BY    :
* INPUT            : STAC_COMPRESSINFO_S *pstInfo
* OUTPUT        :
* RETURN        : STAC_SUCCESS -- 0
*                 STAC_FAIL -- 1;
* CALLED BY     :
****************************************************************************/
LONG     STAC_InitStacDecompress( STAC_DECOMPRESSINFO_S *pstInfo )
{

    if(VOS_NULL_PTR == pstInfo)
    {
        VOS_DBGASSERT(pstInfo);
        return STAC_FAIL;
    }
    pstInfo->pucInputStream = VOS_NULL_PTR;
    pstInfo->pucInput = VOS_NULL_PTR;
    pstInfo->usInlen = 0;
    pstInfo->pucOutputStream = VOS_NULL_PTR;
    pstInfo->usOutlen   = 0;
    pstInfo->pucHoldBuf = VOS_NULL_PTR;
    pstInfo->usHoldLen  = 0;

    /*�����λ����*/
    pstInfo->ucBitMask = 0x80;

    pstInfo->usBufferTail  = 0;
    pstInfo->ucSequenceNum = 1;

    pstInfo->ucResetReqSend = 0;

    pstInfo->ulTimeoutID   = 0;
    pstInfo->ulTimeOutTime = STAC_SENDRSTREQTIMEOUT;
    return STAC_SUCCESS;
}

/****************************************************************************
* CREATE DATE    : 2000-6-21
* CREATED BY    : SHI YONG
* FUNCTION        : Exit StacDecompress
* MODIFY DATE    :
* MODIFIED BY    :
* INPUT            : STAC_COMPRESSINFO_S *pstInfo
* OUTPUT        :
* RETURN        :
* CALLED BY     :
****************************************************************************/
VOID     STAC_ExitStacDecompress( STAC_DECOMPRESSINFO_S *pstInfo )
{

    if(VOS_NULL_PTR == pstInfo)
    {
        VOS_DBGASSERT(pstInfo);
        return;
    }
    /* Deleted end by liutao 38563 at 2004-11-09 V800R002 for PPPC��ֲ */
    pstInfo->pucBuffer = VOS_NULL_PTR;

    /*�ص���ʼ״̬*/
    pstInfo->pucInputStream = VOS_NULL_PTR;
    pstInfo->pucInput = VOS_NULL_PTR;
    pstInfo->usInlen = 0;
    pstInfo->pucOutputStream = VOS_NULL_PTR;
    pstInfo->usOutlen   = 0;
    pstInfo->pucHoldBuf = VOS_NULL_PTR;
    pstInfo->usHoldLen  = 0;
    pstInfo->ucBitMask  = 0x80;

    pstInfo->usBufferTail  = 0;
    pstInfo->ucSequenceNum = 1;

    pstInfo->ucResetReqSend = 0;

    return;
}


/****************************************************************************
* CREATE DATE    : 2000-6-29
* CREATED BY    : SHI YONG
* FUNCTION        : Clear stac history buffer
* MODIFY DATE    :
* MODIFIED BY    :
* INPUT            : STAC_COMPRESSINFO_S *pstInfo
* OUTPUT        :
* RETURN        :
* CALLED BY     :
****************************************************************************/

VOID STAC_ResetHistorybuffer(STAC_COMPRESSINFO_S *pstInfo)
{

    if(VOS_NULL_PTR ==  pstInfo)
    {
        VOS_DBGASSERT(pstInfo);
        return;
    }

    /*��βָ��*/
    pstInfo->usBufferTail = 0;

    /*����ر�־λ*/
    pstInfo->pstHashTable->ulHashTable_NextNode = 0L;
    pstInfo->pstHashTable->ucHashTable_Recycled = 0L;
    pstInfo->ucBitMask = 0x80;

}



#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
