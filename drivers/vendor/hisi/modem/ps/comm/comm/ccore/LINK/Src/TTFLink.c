/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "TTFLink.h"
#include "TTFComm.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e534*/
/*lint -e(760)*/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_TTF_LINK_C
/*lint +e767*/


/******************************************************************************
   2 �ⲿ������������
******************************************************************************/


/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
VOS_SPINLOCK             g_stTtfLinkSpinLock;


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/*lint -save -e958 */

VOS_VOID TTF_NodeInit(TTF_NODE_ST *pNode)
{
    pNode->pPrev    = VOS_NULL_PTR;
    pNode->pNext    = VOS_NULL_PTR;
} /* TTF_NodeInit */

VOS_VOID TTF_LinkInit(VOS_UINT32 ulPid, TTF_LINK_ST *pLink)
{
    if (VOS_NULL_PTR == pLink)
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pLink is Null!");
        return;
    }

    pLink->stHead.pNext = &pLink->stHead;
    pLink->stHead.pPrev = &pLink->stHead;
    pLink->ulCnt        = 0;

} /* TTF_LinkInit */

#ifdef WTTF_PC_ST_SWITCH
VOS_UINT32 TTF_LinkCheckNodeInLink(VOS_UINT32 ulPid, TTF_LINK_ST *pLink, TTF_NODE_ST *pCurr)
{
    TTF_NODE_ST *pNode;

    pNode = pLink->stHead.pNext;

    while ((&pLink->stHead) != pNode)
    {
        if (pCurr == pNode)
        {
            return PS_TRUE;
        }

        pNode = pNode->pNext;
    }

    /*��������δ���ҵ���Ӧ�Ľ��*/
    return PS_FALSE;
}
#endif



#ifndef _lint
VOS_UINT32 TTF_LinkInsertHead(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pInsert)
{

    if ( (VOS_NULL_PTR == pLink) || (VOS_NULL_PTR == pInsert ))
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pLink Or pInsert is Null!");
        return PS_FAIL;
    }

#ifdef WTTF_PC_ST_SWITCH
    /*���ڵ�pInsert�Ƿ�������pLink��*/
    if ( PS_TRUE == TTF_LinkCheckNodeInLink(ulPid, pLink, pInsert) )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pInsert has Existed in pLink!");
        return PS_FAIL;
    }
#endif

    pInsert->pPrev              = (TTF_NODE_ST *)(&pLink->stHead);
    pLink->stHead.pNext->pPrev  = pInsert;
    pInsert->pNext              = pLink->stHead.pNext;
    pLink->stHead.pNext         = pInsert;

    pLink->ulCnt++;

    return PS_SUCC;
} /*TTF_LinkInsertHead*/
#endif


#ifndef _lint

VOS_UINT32 TTF_LinkInsertNext(VOS_UINT32 ulPid, TTF_LINK_ST * pLink,
                TTF_NODE_ST *pCurr, TTF_NODE_ST *pInsert)
{

    if ( (VOS_NULL_PTR == pLink) || (VOS_NULL_PTR == pCurr) || (VOS_NULL_PTR == pInsert))
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pLink��pCurr Or pInsert is Null!");
        return PS_FAIL;
    }

    /*�����ýڵ��Ƿ��������ڣ����ޣ�����ʧ��*/





#ifdef WTTF_PC_ST_SWITCH
    /*���ڵ�pInsert�Ƿ�������pLink��*/
    if ( PS_TRUE == TTF_LinkCheckNodeInLink(ulPid, pLink, pInsert) )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pInsert has Existed in pLink!");
        return PS_FAIL;
    }
#endif

    pInsert->pPrev              = pCurr;
    pCurr->pNext->pPrev         = pInsert;
    pInsert->pNext              = pCurr->pNext;
    pCurr->pNext                = pInsert;

    pLink->ulCnt++;

    return PS_SUCC;
}
#endif





TTF_NODE_ST* TTF_LinkRemoveTail(VOS_UINT32 ulPid, TTF_LINK_ST * pLink)
{
    TTF_NODE_ST    *pNode;

    if (VOS_NULL_PTR == pLink)
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pLink is Null!");
        return VOS_NULL_PTR;
    }

    if (0 == pLink->ulCnt)
    {
        return VOS_NULL_PTR;
    }

    /*�쳣:��������������һ��ʱ, �ݴ���*/
    if ( pLink->stHead.pNext == &pLink->stHead )
    {
        TTF_LOG1(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pLink is null, but Cnt is <1>!", (VOS_INT32)pLink->ulCnt);
        pLink->ulCnt = 0;
        return VOS_NULL_PTR;
    }

    pNode               = pLink->stHead.pPrev;
    pLink->stHead.pPrev = pNode->pPrev;
    pNode->pPrev->pNext = &pLink->stHead;
    pNode->pNext        = VOS_NULL_PTR;
    pNode->pPrev        = VOS_NULL_PTR;

    pLink->ulCnt--;
    return  pNode;

} /* TTF_LinkRemoveTail */


VOS_VOID TTF_LinkRemoveNode(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pRemoveNode)
{

    pRemoveNode->pNext->pPrev = pRemoveNode->pPrev;
    pRemoveNode->pPrev->pNext = pRemoveNode->pNext;
    pRemoveNode->pPrev        = VOS_NULL_PTR;
    pRemoveNode->pNext        = VOS_NULL_PTR;

    pLink->ulCnt--;
    return;

}

/*****************************************************************************
 �� �� ��  : TTF_LinkPeekTail
 ��������  : �鿴�����β��������β�ڵ�
 �������  : pLink   -- ����ָ��
 �������  : ��
 �� �� ֵ  : pNode   -- ����ڵ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��8��
    ��    ��   : �����壬����Ƽ
    �޸�����   : �����ɺ���

*****************************************************************************/
TTF_NODE_ST* TTF_LinkPeekTail(VOS_UINT32 ulPid, const TTF_LINK_ST * pLink)
{
    if ( VOS_NULL_PTR == pLink )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pLink is Null!");
        return VOS_NULL_PTR;
    }

    if ( 0 == pLink->ulCnt )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_INFO, "Info: Tail Node is Null!");
        return VOS_NULL_PTR;
    }

    return pLink->stHead.pPrev;
}

/*****************************************************************************
 �� �� ��  : TTF_LinkPeekNext
 ��������  : �鿴������ָ���ڵ��һ���ڵ㣬���ظýڵ�ĵ�ַ��
                ���ýڵ���β�ڵ㣬�򷵻ؿ�
 �������  : pLink   -- ����ָ��
             pCurr   -- ������ָ���Ľڵ�
 �������  : pCurr��һ���ڵ�
 �� �� ֵ  : PS_SUCC, PS_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��8��
    ��    ��   : �����壬����Ƽ
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TTF_LinkPeekNext(VOS_UINT32 ulPid, const TTF_LINK_ST * pLink,
        TTF_NODE_ST *pCurr, TTF_NODE_ST **ppCurrNext)
{
    TTF_NODE_ST*    pNode;

    if (( VOS_NULL_PTR == pLink ) || ( VOS_NULL_PTR == pCurr ) || ( VOS_NULL_PTR == ppCurrNext ))
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pLink��pInsert Or ppCurrNext is Null!");
        return PS_FAIL;
    }

    if ( 0 == pLink->ulCnt )
    {
        return PS_FAIL;
    }

    if ( (TTF_NODE_ST*)pLink == pCurr )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: Node Address == Link Address!");
        return PS_FAIL;
    }

#ifdef WTTF_PC_ST_SWITCH
    pNode = pLink->stHead.pNext;
    while (pCurr != pNode)
    {
        /*��������δ���ҵ���Ӧ�Ľڵ�*/
        if (&(pLink->stHead) == pNode)
        {
            TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: Not Find The Node In the Link!");
            return PS_FAIL;
        }

        pNode = pNode->pNext;
    }
#else
    pNode = pCurr;
#endif

    /*����ǰ�ڵ���β�ڵ㣬�򷵻�VOS_NULL_PTR�����򣬷�����һ����ַ*/
    if ( &(pLink->stHead) == pNode->pNext )
    {
        *ppCurrNext = VOS_NULL_PTR;
    }
    else
    {
        *ppCurrNext = pNode->pNext;
    }

    return PS_SUCC;

}

/*****************************************************************************
 �� �� ��  : TTF_LinkPeekPrev
 ��������  : �鿴������ָ���ڵ�ǰһ���ڵ㣬���ظýڵ�ĵ�ַ
                ���ýڵ���ͷ�ڵ㣬�򷵻ؿ�
 �������  : pLink   -- ����ָ��
             pCurr   -- ������ָ���Ľڵ�
 �������  : ��
 �� �� ֵ  : pCurrǰһ���ڵ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��8��
    ��    ��   : �����壬����Ƽ
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TTF_LinkPeekPrev(VOS_UINT32 ulPid, TTF_LINK_ST * pLink,
    TTF_NODE_ST *pCurr, TTF_NODE_ST **ppCurrPrev)
{
    TTF_NODE_ST*    pNode;

    if (( VOS_NULL_PTR == pLink ) || ( VOS_NULL_PTR == pCurr ) || ( VOS_NULL_PTR == ppCurrPrev ))
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "\n Warning: pLink��pInsert Or ppCurrPrev is Null!\n");
        return PS_FAIL;
    }

    if ( 0 == pLink->ulCnt )
    {
        return PS_FAIL;
    }

    if ( (TTF_NODE_ST*)pLink == pCurr )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "\n Warning: Node Address == Link Address!\n");
        return PS_FAIL;
    }

#ifdef WTTF_PC_ST_SWITCH
    pNode = pLink->stHead.pNext;
    while (pCurr != pNode)
    {
        /*��������δ���ҵ���Ӧ�Ľڵ�*/
        if ( &(pLink->stHead) == pNode )
        {
            TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "\n Warning: Not Find The Node In the Link!\n");
            return PS_FAIL;
        }

        pNode = pNode->pNext;
    }
#else
    pNode = pCurr;
#endif

    /*����ǰ�ڵ���ͷ�ڵ㣬�򷵻�VOS_NULL_PTR�����򣬷���ǰһ����ַ*/
    if ( &(pLink->stHead) == pNode->pPrev )
    {
        *ppCurrPrev = VOS_NULL_PTR;
    }
    else
    {
        *ppCurrPrev = pNode->pPrev;
    }

    return PS_SUCC;

}


VOS_UINT32 TTF_LinkStick(VOS_UINT32 ulPid, TTF_LINK_ST *pLink1,
    TTF_LINK_ST *pLink2)
{
    if (VOS_NULL_PTR == pLink1)
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING,
            "TTFCOMM, TTF_LinkStick, ERROR, pLink1 is null\n");
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == pLink2)
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING,
            "TTFCOMM, TTF_LinkStick, ERROR, pLink2 is null\n");
        return VOS_ERR;
    }

    if (TTF_LINK_IS_EMPTY(pLink2))
    {
        return VOS_OK;
    }

    pLink1->stHead.pPrev->pNext = pLink2->stHead.pNext;
    pLink2->stHead.pNext->pPrev = pLink1->stHead.pPrev;
    pLink1->stHead.pPrev        = pLink2->stHead.pPrev;
    pLink2->stHead.pPrev->pNext = (TTF_NODE_ST *)&(pLink1->stHead);

    /*���³���*/
    pLink1->ulCnt       += pLink2->ulCnt;

    TTF_LINK_INIT(pLink2);

    return VOS_OK;
}
VOS_UINT32 TTF_LinkSafeInsertTail(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pInsert, VOS_UINT32 *pulNonEmptyEvent)
{
    VOS_ULONG       ulLockLevel = 0UL;

    *pulNonEmptyEvent    = PS_FALSE;

    VOS_SpinLockIntLock(&g_stTtfLinkSpinLock, ulLockLevel);

    if ( (VOS_NULL_PTR == pLink) || (VOS_NULL_PTR == pInsert) )
    {
        VOS_SpinUnlockIntUnlock(&g_stTtfLinkSpinLock, ulLockLevel);
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pLink Or pInsert is Null!");
        return PS_FAIL;
    }

#ifdef WTTF_PC_ST_SWITCH
    /*���ڵ�pInsert�Ƿ�������pLink��*/
    if ( PS_TRUE == TTF_LinkCheckNodeInLink(ulPid, pLink, pInsert) )
    {
        VOS_SpinUnlockIntUnlock(&g_stTtfLinkSpinLock, ulLockLevel);
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pInsert has Existed in pLink!");
        return PS_FAIL;
    }
#endif

    if (0 == TTF_LINK_CNT(pLink))
    {
        *pulNonEmptyEvent  = PS_TRUE;
    }

    pInsert->pNext              = (TTF_NODE_ST *)(&pLink->stHead);
    pInsert->pPrev              = pLink->stHead.pPrev;

    pLink->stHead.pPrev->pNext  = pInsert;
    pLink->stHead.pPrev         = pInsert;

    pLink->ulCnt++;

    VOS_SpinUnlockIntUnlock(&g_stTtfLinkSpinLock, ulLockLevel);

    return PS_SUCC;
} /* TTF_LinkSafeInsertTail */



TTF_NODE_ST* TTF_LinkSafeRemoveHead(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, VOS_UINT32 *pulRemainCnt)
{
    TTF_NODE_ST    *pNode;
    VOS_ULONG       ulLockLevel = 0UL;

    VOS_SpinLockIntLock(&g_stTtfLinkSpinLock, ulLockLevel);

    *pulRemainCnt   = 0;

    if (VOS_NULL_PTR == pLink)
    {
        VOS_SpinUnlockIntUnlock(&g_stTtfLinkSpinLock, ulLockLevel);
        TTF_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is Null!");
        return VOS_NULL_PTR;
    }

    if (0 == pLink->ulCnt)
    {
        VOS_SpinUnlockIntUnlock(&g_stTtfLinkSpinLock, ulLockLevel);
        return VOS_NULL_PTR;
    }

    /*�쳣:��������������һ��ʱ, �ݴ���*/
    if ( pLink->stHead.pNext == &pLink->stHead )
    {
        pLink->ulCnt = 0;
        VOS_SpinUnlockIntUnlock(&g_stTtfLinkSpinLock, ulLockLevel);
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is null, but Cnt is <1>!", (VOS_INT32)pLink->ulCnt);
        return VOS_NULL_PTR;
    }

    pNode               = pLink->stHead.pNext;
    pLink->stHead.pNext = pNode->pNext;
    pNode->pNext->pPrev = &pLink->stHead;
    pNode->pNext        = VOS_NULL_PTR;
    pNode->pPrev        = VOS_NULL_PTR;

    pLink->ulCnt--;

    /* ��ȡ������ʣ��Ԫ�ظ��� */
    *pulRemainCnt   = pLink->ulCnt;

    VOS_SpinUnlockIntUnlock(&g_stTtfLinkSpinLock, ulLockLevel);

    return pNode;
} /* TTF_LinkSafeRemoveHead */

#ifndef _lint
VOS_UINT32 TTF_LinkInsertTail(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pInsert)
{
    if ( (VOS_NULL_PTR == pLink) || (VOS_NULL_PTR == pInsert) )
    {
        /*TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pLink Or pInsert is Null!");
 */
        return PS_FAIL;
    }

    pInsert->pNext              = (TTF_NODE_ST *)(&pLink->stHead);
    pInsert->pPrev              = pLink->stHead.pPrev;

    pLink->stHead.pPrev->pNext  = pInsert;
    pLink->stHead.pPrev         = pInsert;

    pLink->ulCnt++;

    return PS_SUCC;
} /* TTF_LinkInsertTail */

#endif
/*lint -esym( 528, TTF_LinkRemoveHead )*/
TTF_NODE_ST* TTF_LinkRemoveHead(VOS_UINT32 ulPid, TTF_LINK_ST * pLink)
{
    TTF_NODE_ST    *pNode;

    if (VOS_NULL_PTR == pLink)
    {
        return VOS_NULL_PTR;
    }

    if (0 == pLink->ulCnt)
    {
        return VOS_NULL_PTR;
    }

    /*�쳣:��������������һ��ʱ, �ݴ���*/
    if ( pLink->stHead.pNext == &pLink->stHead )
    {
        pLink->ulCnt = 0;
        return VOS_NULL_PTR;
    }

    pNode               = pLink->stHead.pNext;
    pLink->stHead.pNext = pNode->pNext;
    pNode->pNext->pPrev = &pLink->stHead;
    pNode->pNext        = VOS_NULL_PTR;
    pNode->pPrev        = VOS_NULL_PTR;

    pLink->ulCnt--;

    return pNode;

} /* TTF_LinkRemoveHead */

/*lint -esym( 528, TTF_LinkCnt )*/
VOS_UINT32 TTF_LinkCnt(VOS_UINT32 ulPid, const TTF_LINK_ST *pLink)
{
    if (VOS_NULL_PTR == pLink)
    {
        /*TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pLink is Null!");
 */
        return 0;
    }
    return (pLink->ulCnt);
} /* TTF_LinkCnt */

/*lint -esym( 528, TTF_LinkIsEmpty )*/
VOS_UINT32 TTF_LinkIsEmpty(VOS_UINT32 ulPid, const TTF_LINK_ST *pLink)
{
    if (VOS_NULL_PTR == pLink)
    {
        /*TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pLink is Null!");
 */
        return PS_TRUE;
    }

    if (0 == pLink->ulCnt)
    {
        return PS_TRUE;
    }

    return PS_FALSE;
} /* TTF_LinkIsEmpty */


/*****************************************************************************
 �� �� ��  : TTF_LinkPeekHead
 ��������  : �鿴�����ͷ��������ͷ�ڵ�
 �������  : pLink   -- ����ָ��
 �������  : ��
 �� �� ֵ  : pNode   -- ����ڵ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��8��
    ��    ��   : �����壬����Ƽ
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -esym( 528, TTF_LinkPeekHead )*/
TTF_NODE_ST* TTF_LinkPeekHead(VOS_UINT32 ulPid, const TTF_LINK_ST * pLink)
{
    if ( VOS_NULL_PTR == pLink )
    {
        /*TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pLink is Null!");
 */
        return VOS_NULL_PTR;
    }

    if ( 0 == pLink->ulCnt )
    {
        return VOS_NULL_PTR;
    }

    return pLink->stHead.pNext;
}


VOS_UINT32  TTF_RING_Q_Init(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ, VOS_UINT32 ulMaxSize )
{
    VOS_VOID **ppNode;


    if (VOS_NULL_PTR == pstRingQ )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pstRingQ is Null !");
        return PS_FAIL;
    }

    if ( 2 > ulMaxSize)
    {
        TTF_LOG1(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: RingQ  ulMaxSize<1> less than 2 !",(VOS_INT32)ulMaxSize);
        return PS_FAIL;
    }

    #if( VOS_OS_VER == VOS_WIN32 )
    ppNode  = (VOS_VOID **)malloc(sizeof(VOS_VOID *) * ulMaxSize);
    #else
    ppNode  = (VOS_VOID **)VOS_MemAlloc(ulPid, (STATIC_MEM_PT), (sizeof(VOS_VOID *) * ulMaxSize));
    #endif

    if(VOS_NULL_PTR == ppNode )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: RingQ Init Malloc Fail!");
        return PS_FAIL;
    }

    pstRingQ->ppNode       = ppNode;
    pstRingQ->ulFront      = 0;
    pstRingQ->ulRear       = 0;
    pstRingQ->ulMaxSize    = ulMaxSize;
    return PS_SUCC;

} /* TTF_RING_Q_Init */

VOS_UINT32  TTF_RING_Q_NodeAddrInit(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ, VOS_VOID **ppNodeAddr,VOS_UINT32 ulNodeCnt,VOS_UINT8 ucSize)
{
    VOS_UINT32      ulNodeLoop;

    if ( VOS_NULL_PTR == pstRingQ )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pstRingQ is Null !");
        return PS_FAIL;
    }

    if ( VOS_NULL_PTR == pstRingQ->ppNode )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: ppNode is Null !");
        return PS_FAIL;
    }

    if ( VOS_NULL_PTR == ppNodeAddr )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: ppNodeAddr is Null !");
        return PS_FAIL;
    }

    if ( 2 > ulNodeCnt)
    {
        TTF_LOG1(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: ppNodeAddr  ulNodeCnt<1> less than 2 !",(VOS_INT32)ulNodeCnt);
        return PS_FAIL;
    }


    if ( ulNodeCnt != pstRingQ->ulMaxSize )
    {
        TTF_LOG2(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: RingQ MaxSize<1> is not matched NodeCnt<2>!", (VOS_INT32)pstRingQ->ulMaxSize, (VOS_INT32)ulNodeCnt);
        return PS_FAIL;
    }

    for (ulNodeLoop = 0; ulNodeLoop < pstRingQ->ulMaxSize; ulNodeLoop++)
    {
        /* �˼乲����ĵ�ַ */
/*      ppNodeAddr = ppNodeAddr + ulNodeLoop*ucSize;
 */
        pstRingQ->ppNode[ulNodeLoop] = (VOS_VOID *)ppNodeAddr;
        ppNodeAddr = ppNodeAddr + ucSize;
    }
    return PS_SUCC;
}




VOS_UINT32  TTF_RING_Q_InitAndNodeAddrSet(VOS_UINT32 ulPid,
                                                        TTF_RING_Q_ST *pstRingQ,
                                                        VOS_VOID **ppNode,
                                                        VOS_VOID *pQueueNode,
                                                        VOS_UINT32 ulBlkSize,
                                                        VOS_UINT32 ulBlkCnt )
{
    VOS_UINT32      ulNodeNoLoop        = 0;
    VOS_UINT8      *pucQueueNodeAddr      = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstRingQ )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pstRingQ is Null !");
        return PS_FAIL;
    }

    if ( 2 > ulBlkCnt)
    {
        TTF_LOG1(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: RingQ  ulMaxSize<1> less than 2 !",(VOS_INT32)ulBlkCnt);
        return PS_FAIL;
    }

    if(VOS_NULL_PTR == ppNode )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: RingQ Init Malloc Fail!");
        return PS_FAIL;
    }

    pstRingQ->ppNode       = ppNode;
    pstRingQ->ulFront      = 0;
    pstRingQ->ulRear       = 0;
    pstRingQ->ulMaxSize    = ulBlkCnt;          /* TTF_RING_Q_ST��ulMaxSize����������ݿ��� */
    pucQueueNodeAddr         = (VOS_UINT8 *)pQueueNode;

    for(ulNodeNoLoop = 0; ulNodeNoLoop < pstRingQ->ulMaxSize; ulNodeNoLoop ++)
    {
        pstRingQ->ppNode[ulNodeNoLoop] = (pucQueueNodeAddr + ulBlkSize * ulNodeNoLoop);
    }

    return PS_SUCC;
} /* TTF_RING_Q_InitAndNodeAddrSet */


VOS_UINT32  TTF_RING_Q_NodeAddrSet(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ,
                                    VOS_VOID **ppNodeAddr,VOS_UINT32 ulNodeCnt)
{
    VOS_UINT32      ulNodeNoLoop;


    if (VOS_NULL_PTR == pstRingQ )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pstRingQ is Null !");
        return PS_FAIL;
    }

    if ( VOS_NULL_PTR == pstRingQ->ppNode )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: ppNode is Null !");
        return PS_FAIL;
    }

    if ( VOS_NULL_PTR == ppNodeAddr )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: ppNodeAddr is Null !");
        return PS_FAIL;
    }

    if ( 2 > ulNodeCnt)
    {
        TTF_LOG1(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: ppNodeAddr  ulNodeCnt<1> less than 2 !",(VOS_INT32)ulNodeCnt);
        return PS_FAIL;
    }


    if ( ulNodeCnt != pstRingQ->ulMaxSize )
    {
        TTF_LOG2(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: RingQ MaxSize<1> is not matched NodeCnt<2>!", (VOS_INT32)pstRingQ->ulMaxSize, (VOS_INT32)ulNodeCnt);
        return PS_FAIL;
    }


    for(ulNodeNoLoop = 0; ulNodeNoLoop < pstRingQ->ulMaxSize; ulNodeNoLoop ++)
    {
        pstRingQ->ppNode[ulNodeNoLoop] = ppNodeAddr[ulNodeNoLoop];
    }
    return PS_SUCC;

} /* TTF_RING_Q_NodeAddrSet */

VOS_VOID* TTF_RING_Q_Rear(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{
    VOS_VOID    *pNode;


    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null ! */
    {
        return VOS_NULL_PTR;
    }

    if ( VOS_NULL_PTR == pstRingQ->ppNode) /* pstRingQ is not Initialized ! */
    {
        return VOS_NULL_PTR;
    }

    if ( pstRingQ->ulFront == PS_MOD_ADD(pstRingQ->ulRear, 1, pstRingQ->ulMaxSize) ) /*  RingQ is Full ! */
    {
        return VOS_NULL_PTR;
    }

    pNode = pstRingQ->ppNode[pstRingQ->ulRear];
    return pNode;

} /* TTF_RING_Q_Rear */



VOS_UINT32 TTF_RING_Q_In(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ )
{

    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null ! */
    {
        return PS_FAIL;
    }

    if ( pstRingQ->ulFront == PS_MOD_ADD(pstRingQ->ulRear, 1, pstRingQ->ulMaxSize) ) /* RingQ is Full ! */
    {
        return PS_FAIL;
    }

    pstRingQ->ulRear  = PS_MOD_ADD(pstRingQ->ulRear, 1, pstRingQ->ulMaxSize);
    return PS_SUCC;

} /* TTF_RING_Q_In */

VOS_VOID* TTF_RING_Q_Front(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{
    VOS_VOID    *pNode;

    if (VOS_NULL_PTR == pstRingQ )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pstRingQ is Null !");
        return VOS_NULL_PTR;
    }

    if ( VOS_NULL_PTR == pstRingQ->ppNode) /* pstRingQ is not Initialized ! */
    {
        return VOS_NULL_PTR;
    }

    if ( pstRingQ->ulRear == pstRingQ->ulFront)
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_INFO, "Info: RingQ is Empty !");
        return VOS_NULL_PTR;
    }

    pNode = pstRingQ->ppNode[pstRingQ->ulFront];

    return pNode;

} /* TTF_RING_Q_Rear */



VOS_VOID* TTF_RING_Q_Out(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{
    VOS_VOID    *pNode;


    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null */
    {
        return VOS_NULL_PTR;
    }

    if ( VOS_NULL_PTR == pstRingQ->ppNode) /* pstRingQ is not Initialized ! */
    {
        return VOS_NULL_PTR;
    }

    if ( pstRingQ->ulRear == pstRingQ->ulFront) /* RingQ is Empty */
    {
        return VOS_NULL_PTR;
    }

    pNode               = pstRingQ->ppNode[pstRingQ->ulFront];
    pstRingQ->ulFront   = PS_MOD_ADD(pstRingQ->ulFront, 1, pstRingQ->ulMaxSize);
    return pNode;

} /* TTF_RING_Q_Out */



VOS_UINT32 TTF_RING_Q_IsFull(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{

    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null */
    {
        return PS_TRUE;
    }

    if ( pstRingQ->ulFront == PS_MOD_ADD(pstRingQ->ulRear, 1, pstRingQ->ulMaxSize) )
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }

} /* TTF_RING_Q_IsFull */


VOS_UINT32 TTF_RING_Q_IsEmpty(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{

    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null */
    {
        return PS_TRUE;
    }

    if ( pstRingQ->ulRear == pstRingQ->ulFront)
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }

} /* TTF_RING_Q_IsEmpty */


VOS_UINT32 TTF_RING_Q_Flush(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{

    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null ! */
    {
        return PS_FAIL;
    }

    pstRingQ->ulFront = pstRingQ->ulRear;/* ��ͷ׷�϶�β */
    return PS_SUCC;

} /* TTF_RING_Q_GetCnt */

VOS_UINT32 TTF_RING_Q_GetCnt(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{
    VOS_UINT32 ulCnt;

    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null ! */
    {
        return 0;
    }

    ulCnt   = PS_MOD_SUB( pstRingQ->ulRear, pstRingQ->ulFront, pstRingQ->ulMaxSize);
    return ulCnt;

} /* TTF_RING_Q_GetCnt */



VOS_UINT32  TTF_RING_Q_Free(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{

    if (VOS_NULL_PTR == pstRingQ )
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "Warning: pstRingQ is Null !");
        return PS_FAIL;
    }

    if ( VOS_NULL_PTR != pstRingQ->ppNode )
    {
        #if( VOS_OS_VER == VOS_WIN32 )
        free(pstRingQ->ppNode);
        #else
        VOS_MemFree(ulPid, pstRingQ->ppNode);
        #endif

        pstRingQ->ppNode = VOS_NULL_PTR;
    }

    pstRingQ->ulFront   =0;
    pstRingQ->ulRear    =0;
    pstRingQ->ulMaxSize =0;

    return PS_SUCC;

} /* TTF_RING_Q_Free */
/*lint -restore */
/*lint +e534*/


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

