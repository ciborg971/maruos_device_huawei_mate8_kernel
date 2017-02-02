/******************************************************************************
  �� �� ��   : PsQnode.c
  �� �� ��   : ����
  ��    ��   : liukai
  ��������   : 2013��9��16��
  ����޸�   :
  ��������   : �ṩPsQnode����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��9��16��
    ��    ��   : liukai
    �޸�����   : �����ļ�
******************************************************************************/

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "PsQnode.h"
#include "TTFComm.h"


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_PS_QNODE_C /*lint !e767*/




/******************************************************************************
   2 �ⲿ������������
******************************************************************************/


/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
/* ���PsQnode���ݵĿռ�, QNode���֧���ڶ����񻷾���ʹ�� */
PS_QNODE_STRU    g_astQnode[MAX_PS_QNODE_NUM];

/* ������ṹ, ͨ��usNodeIdx��������ṹ�ͽ���ν����� */
PS_QNODE_MGMT_STRU     g_stMgmt;

#if (VOS_OS_VER == VOS_WIN32)
VOS_UINT32             g_ulPsQnodeNum;
#endif


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/*****************************************************************************
 �� �� ��  : PS_Qnode_Init
 ��������  : ��ʼ����ʹ�ܵ��ԵĽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 ˵    ��  : �˺���ֻ�����ʼ��һ��

 �޸���ʷ      :
  1.��    ��   : 2013��9��16��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PS_Qnode_Init(VOS_VOID)
{
    VOS_UINT32                  ulLoop;
    VOS_UINT32                  ulCurrOffset;
    const VOS_UINT32            ul32Bit = 32;
    VOS_UINT32                  ulMaxLoop;


    PS_MEM_SET(&g_stMgmt, 0x0, sizeof(g_stMgmt));
    PS_MEM_SET(&g_astQnode[0], 0x0, sizeof(g_astQnode));

    g_stMgmt.enIsTracePrintOn   =   PS_QNODE_TRACE_PRINT_OFF;
    g_stMgmt.usNodeIdx          =   0;

#if (VOS_OS_VER == VOS_WIN32)
    /* ����PC���� */
    ulCurrOffset   =   /*lint --e(778)*/TTF_MOD_GET(g_ulPsQnodeNum, ul32Bit);
#else
    ulCurrOffset   =   /*lint --e(778)*/TTF_MOD_GET(MAX_PS_QNODE_NUM, ul32Bit);
#endif
    ulMaxLoop      =   TTF_MOD_GET((ul32Bit - ulCurrOffset), ul32Bit);

    /* ���MAX_PS_QNODE_NUM����32��������, ��ô�������bit��1 */
    for (ulLoop = 0; ulLoop < ulMaxLoop; ulLoop++)    /*lint !e681*/
    {
        TTF_SET_A_BIT((g_stMgmt.aulQuickMap[(MAX_PS_QNODE_4BYTE_ALIGN_NUM - 1)]), ulLoop);
    }

    for (ulLoop = 0; ulLoop < MAX_PS_QNODE_NUM; ulLoop++)
    {
        TTF_NodeInit(&(g_astQnode[ulLoop].stNode));
        g_astQnode[ulLoop].enState  =   PS_QNODE_FREE_STATE;
        g_astQnode[ulLoop].usIndex  =   (VOS_UINT16)ulLoop;
        g_astQnode[ulLoop].usMagic  =   PS_QNODE_MAGICNUM;
    }

    return;
} /* PS_Qnode_Init */

/*****************************************************************************
 �� �� ��  : PS_Qnode_GetNode
 ��������  : ����Qnode���
 �������  : usFileId   - �ļ�ID
             usLineId   - �к�
             ulPid      - PID
 �������  : �ɹ�, ���������Qnode���; ʧ��, ����NULL
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��16��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
PS_QNODE_STRU* PS_Qnode_GetNode(VOS_UINT16 usFileId,
                                VOS_UINT16 usLineId,
                                VOS_UINT32 ulPid)
{
    PS_QNODE_STRU              *pstQnode = VOS_NULL_PTR;
    VOS_UINT16                  usCurrQnodeIdx;
    VOS_UINT32                  ulTick;
    VOS_INT32                   lLockKey;
    const VOS_UINT16            us32Bit = 32;
    VOS_UINT16                  usStartPos;
    VOS_UINT32                  ulCurr32Bit;
    VOS_UINT16                  usCurrPos;
    VOS_UINT32                  ulTmp;
    VOS_UINT32                  ulLoop;
    const VOS_UINT32            ulMask = 0x80000000;//0x00000001;

    ulTick          =   VOS_GetTick();
    usCurrQnodeIdx  =   g_stMgmt.usNodeIdx;
    usStartPos      =   usCurrQnodeIdx / us32Bit;    /* ��¼StartPos */
    usCurrPos       =   usStartPos;

    do
    {
        ulCurr32Bit = g_stMgmt.aulQuickMap[usCurrPos];

        if (PS_NULL_UINT32 != ulCurr32Bit)    /* ��ֵΪ0��bit, ˵���п�λ */
        {
            /* �±��ҵ�һ��Ϊ1��bit */
            ulTmp   =   ~ulCurr32Bit;

            for (ulLoop = 0; ulLoop < us32Bit; ulLoop++)
            {
                if (ulTmp & ulMask) //�ҵ�
                {
                    usCurrQnodeIdx = (VOS_UINT16)(PS_MOD_ADD((usCurrPos * us32Bit), ulLoop, MAX_PS_QNODE_NUM));
                    break;
                }

                ulTmp <<= 1;//>>= 1;
            }

            pstQnode    =   &(g_astQnode[usCurrQnodeIdx]);

            lLockKey    =   VOS_SplIMP();

            if (PS_QNODE_FREE_STATE == pstQnode->enState)
            {
                pstQnode->enState               =   PS_QNODE_USED_STATE;

                pstQnode->stDbg.ulAllocTick     =   ulTick;
                pstQnode->stDbg.usAllocFileId   =   usFileId;
                pstQnode->stDbg.usAllocLineNum  =   usLineId;

                /* ˢ�¿�� */
                TTF_SET_A_BIT(ulCurr32Bit, (us32Bit - ulLoop - 1));
                g_stMgmt.aulQuickMap[usCurrPos] = ulCurr32Bit;

                /* ��д���ؽڵ������ֵ */
                g_stMgmt.usNodeIdx = PS_MOD_ADD(usCurrQnodeIdx, 1, MAX_PS_QNODE_NUM);//usCurrQnodeIdx;

                /* ˢ��ͳ�� */
                g_stMgmt.stStat.ulAllocTotalCnt++;

                VOS_Splx(lLockKey);

                return pstQnode;
            }

            VOS_Splx(lLockKey);
        }

        usCurrPos = PS_MOD_ADD(usCurrPos, 1, MAX_PS_QNODE_4BYTE_ALIGN_NUM);
    }
    while (usCurrPos != usStartPos);

    lLockKey    =   VOS_SplIMP();

    g_stMgmt.stStat.ulAllocFailCnt++;
    g_stMgmt.stStat.ulAllocTotalCnt++;

    VOS_Splx(lLockKey);

    TTF_LOG4(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "fileid, line, pid, tick, PS_Qnode_GetNode fail",
        usFileId, usLineId, (VOS_INT32)ulPid, (VOS_INT32)ulTick);

    return VOS_NULL_PTR;
} /* PS_Qnode_GetNode */

/*****************************************************************************
 �� �� ��  : PS_Qnode_SendEvent
 ��������  : �ϱ��¼�
 �������  : ulPid - ����PID
             enEventId - �¼�ID
             pEventData - �¼���Ϣ����
             ulDataLen - �¼���Ϣ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��9��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PS_Qnode_SendEvent(VOS_UINT32  ulPid,
                            VOS_UINT16  usEventId,
                            VOS_VOID   *pEventData,
                            VOS_UINT32  ulDataLen)
{
    DIAG_EVENT_IND_STRU                 stDiagEvent;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stDiagEvent, 0x0, sizeof(DIAG_EVENT_IND_STRU));

    /* ��д�¼����� */
    stDiagEvent.ulModule    = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(ulPid), DIAG_MODE_COMM);
    stDiagEvent.ulPid       = ulPid;
    stDiagEvent.ulEventId   = usEventId;
    stDiagEvent.ulLength    = ulDataLen;
    stDiagEvent.pData       = pEventData;

    ulRet   = DIAG_EventReport(&stDiagEvent);

    /* ����DIAG���¼��ϱ��ӿ� */
    if ( VOS_OK != ulRet)
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_ERROR, "cttf mntn event sent fail");
    }

    return;
}    /* PS_Qnode_SendEvent */

/*****************************************************************************
 �� �� ��  : PS_Qnode_FreeNode
 ��������  : �ͷ�Qnode���
 �������  : usFileId   - �ļ�ID
             usLineId   - �к�
             ulPid      - PID
             pstQnode   - Qnode���
 �������  : ��
 �� �� ֵ  : �������, �ɹ� - PS_SUCC, ���� - PS_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��16��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
PS_RSLT_CODE_ENUM_UINT32 PS_Qnode_FreeNode(VOS_UINT16       usFileId,
                                       VOS_UINT16      usLineId,
                                       VOS_UINT32      ulOpPid,
                                       PS_QNODE_STRU  *pstQnode)
{
    VOS_UINT32                      ulTick;
    VOS_INT32                       lLockKey;
    PS_QNODE_TAMPERED_EVENT_STRU    stEvent;
    const VOS_UINT16                us32Bit = 32;
    VOS_UINT16                      usCurrPos;
    VOS_UINT16                      usCurrOffset;
    VOS_UINT32                      ulQnodeAddr;
    VOS_UINT32                      ulFirstQnodeAddr;
    VOS_UINT32                      ulLastQnodeAddr;


    ulTick  =   VOS_GetTick();

    if (VOS_NULL_PTR == pstQnode)
    {
        lLockKey    =   VOS_SplIMP();

        g_stMgmt.stStat.ulFreeNullPtrCnt++;
        g_stMgmt.stStat.ulFreeTotalCnt++;

        VOS_Splx(lLockKey);

        TTF_LOG4(ulOpPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "FileId, LineId, Pid, tick, pstQnode is NULL",
            usFileId, usLineId, (VOS_INT32)ulOpPid, (VOS_INT32)ulTick);
        return PS_FAIL;
    }

    ulQnodeAddr         =   (VOS_UINT32)pstQnode;
    ulFirstQnodeAddr    =   (VOS_UINT32)(&g_astQnode[0]);
    ulLastQnodeAddr     =   (VOS_UINT32)(&g_astQnode[MAX_PS_QNODE_NUM - 1]);

    if ((0 != (ulQnodeAddr - ulFirstQnodeAddr) % sizeof(g_astQnode[0]))
        || ((ulQnodeAddr > ulLastQnodeAddr)
        || (ulQnodeAddr < ulFirstQnodeAddr)))
    {
        lLockKey    =   VOS_SplIMP();

        g_stMgmt.stStat.ulFreeInvalidPrtCnt++;
        g_stMgmt.stStat.ulFreeTotalCnt++;

        VOS_Splx(lLockKey);

        TTF_LOG4(ulOpPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "FileId, LineId, Pid, tick, pstQnode is invalid",
            usFileId, usLineId, (VOS_INT32)ulOpPid, (VOS_INT32)ulTick);
        return PS_FAIL;
    }

    if (PS_QNODE_MAGICNUM == pstQnode->usMagic)    /* δ�۸� */
    {
        if (PS_QNODE_USED_STATE != pstQnode->enState)
        {
            lLockKey    =   VOS_SplIMP();

            g_stMgmt.stStat.ulFreePtrBeforeCnt++;
            g_stMgmt.stStat.ulFreeTotalCnt++;

            VOS_Splx(lLockKey);

            TTF_LOG4(ulOpPid, DIAG_MODE_COMM, PS_PRINT_WARNING,
                "FileId, LineId, Pid, tick, pstQnode has already been freed before",
                usFileId, usLineId, (VOS_INT32)ulOpPid, (VOS_INT32)ulTick);
            return PS_FAIL;
        }
    }
    else    /* ���۸� */
    {
        lLockKey    =   VOS_SplIMP();

        g_stMgmt.stStat.ulMagicTamperedCnt++;

        /* ǿ�ƻָ� */
        pstQnode->usMagic   =   PS_QNODE_MAGICNUM;
        pstQnode->usIndex   =   (VOS_UINT16)((ulQnodeAddr - ulFirstQnodeAddr) / sizeof(g_astQnode[0]));

        VOS_Splx(lLockKey);

        /* ��дevent */
        stEvent.usFileId    =   usFileId;
        stEvent.usLineId    =   usLineId;
        stEvent.ulPid       =   ulOpPid;
        stEvent.ulTick      =   ulTick;

        stEvent.usEventId   =   ID_PS_QNODE_FOUND_TAMPERED;

        mdrv_memcpy(&(stEvent.stQnode), pstQnode, sizeof(stEvent.stQnode));

        /* SDTҪ��event id����ҽ���ĳ���̶���PID��, �ݾ�������WRLC�� */
        PS_Qnode_SendEvent(WUEPS_PID_RLC, ID_PS_QNODE_FOUND_TAMPERED, &stEvent,
            sizeof(stEvent));

        TTF_LOG4(ulOpPid, 0, PS_PRINT_ERROR,
            "FileId, LineId, Pid, Qnode magic number tampered pstQnode",
            usFileId, usLineId, (VOS_INT32)ulOpPid, (VOS_INT32)pstQnode);
        TTF_LOG1(ulOpPid, 0, PS_PRINT_ERROR,
            "found magic number tampered pstQnode at tick",
            (VOS_INT32)ulTick);
    }

    lLockKey    =   VOS_SplIMP();

    PS_MEM_SET(&(pstQnode->stMemSrc), 0x0, sizeof(pstQnode->stMemSrc));
    PS_MEM_SET(&(pstQnode->aucPara[0]), 0x0, sizeof(pstQnode->aucPara));

    pstQnode->stDbg.ulTraceTick     =   ulTick;
    pstQnode->stDbg.usTraceFileId   =   usFileId;
    pstQnode->stDbg.usTraceLineNum  =   usLineId;

    /* ˢ�¿�� */
    usCurrPos      =   (pstQnode->usIndex) / us32Bit;
    usCurrOffset   =   (pstQnode->usIndex) % us32Bit;
    TTF_CLEAR_A_BIT(g_stMgmt.aulQuickMap[usCurrPos], ((us32Bit - 1) - usCurrOffset));

    /* ˢ��ͳ�� */
    g_stMgmt.stStat.ulFreeTotalCnt++;

    /* �Ѹ���״̬�������, ��Ϊ��ǰ��, ���ܳ���getnode��һ������state���������ȡ�߽����,
       ���߳��»����freenodeδ����, ����Ѿ���ȡ��ʹ�� */
    pstQnode->enState   =   PS_QNODE_FREE_STATE;

    VOS_Splx(lLockKey);

    return PS_SUCC;
} /* PS_Qnode_FreeNode */

/*****************************************************************************
 �� �� ��  : PS_Qnode_FillMemInfo
 ��������  : ��Qnode�����д�ҽӵ�����Դ, ����д�Զ������
 �������  : usFileId       - �ļ�ID
             usLineId       - �к�
             ulPid          - PID
             pstQnode       - Qnode���
             pstMemSrc      - �����ڴ��йҽӵ��û�����Դ�Ľṹ
             ucParaOctetCnt - �û��Զ����������, ��λ: �ֽ�
             aucPara        - �û��Զ������
 �������  : ��
 �� �� ֵ  : �������, �ɹ� - PS_SUCC, ���� - PS_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��17��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
PS_RSLT_CODE_ENUM_UINT32 PS_Qnode_FillMemInfo(VOS_UINT16   usFileId,
                            VOS_UINT16                     usLineId,
                            VOS_UINT32                     ulPid,
                            PS_QNODE_STRU                 *pstQnode,
                            PS_QNODE_MEM_SOURCE_STRU      *pstMemSrc,
                            VOS_UINT8                      ucParaOctetCnt,
                            VOS_UINT8                      aucPara[])
{
    VOS_UINT32  ulTick;

    ulTick  =   VOS_GetTick();

    if (VOS_NULL_PTR == pstQnode)
    {
        TTF_LOG4(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "fileid, line, pid, tick, pstQnode is NULL",
            usFileId, usLineId, (VOS_INT32)ulPid, (VOS_INT32)ulTick);
        return PS_FAIL;
    }

    if (VOS_NULL_PTR == pstMemSrc)
    {
        TTF_LOG4(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "fileid, line, pid, tick, pstMemSrc is NULL",
            usFileId, usLineId, (VOS_INT32)ulPid, (VOS_INT32)ulTick);
        return PS_FAIL;
    }

    if (PS_QNODE_FREE_STATE == pstQnode->enState)
    {
        TTF_LOG4(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "fileid, line, pid, tick, pstQnode state is free",
            usFileId, usLineId, (VOS_INT32)ulPid, (VOS_INT32)ulTick);
        return PS_FAIL;
    }

    if (ucParaOctetCnt > MAX_PARA_OCTET_NUM)
    {
        TTF_LOG(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "more than allowed para octet num");
        return PS_FAIL;
    }

    PS_MEM_CPY(&(pstQnode->stMemSrc), pstMemSrc, sizeof(pstQnode->stMemSrc));
    if (0 != ucParaOctetCnt)
    {
        PS_MEM_CPY(&(pstQnode->aucPara[0]), aucPara, (ucParaOctetCnt * sizeof(VOS_UINT8)));
    }

    return PS_SUCC;
} /* PS_Qnode_FillMemInfo */

/*****************************************************************************
 �� �� ��  : PS_Qnode_Trace
 ��������  : ��Qnode�����д������Ϣ(������API)
 �������  : usFileId   - �ļ�ID
             usLineId   - �к�
             ulPid      - PID
             pstQnode   - Qnode���
 �������  : ��
 �� �� ֵ  : �������, �ɹ� - PS_SUCC, ���� - PS_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��17��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
PS_RSLT_CODE_ENUM_UINT32 PS_Qnode_Trace(VOS_UINT16 usFileID, VOS_UINT16 usLineNum,
            VOS_UINT32 ulPid, PS_QNODE_STRU *pstQnode)
{
    VOS_UINT32                      ulTick;
    VOS_UINT32                      ulQnodeAddr;
    VOS_UINT32                      ulFirstQnodeAddr;

    ulTick  =   VOS_GetTick();

    if (VOS_NULL_PTR == pstQnode)
    {
        TTF_LOG4(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "FileId, LineId, Pid, tick, pstQnode is NULL",
            usFileID, usLineNum, (VOS_INT32)ulPid, (VOS_INT32)ulTick);
        return PS_FAIL;
    }

    ulQnodeAddr         =   (VOS_UINT32)pstQnode;
    ulFirstQnodeAddr    =   (VOS_UINT32)(&g_astQnode[0]);

    if (0 != (ulQnodeAddr - ulFirstQnodeAddr) % sizeof(g_astQnode[0]))
    {
        TTF_LOG4(ulPid, DIAG_MODE_COMM, PS_PRINT_WARNING, "FileId, LineId, Pid, tick, pstQnode is invalid",
            usFileID, usLineNum, (VOS_INT32)ulPid, (VOS_INT32)ulTick);
        return PS_FAIL;
    }

    pstQnode->stDbg.ulTraceTick     =   ulTick;
    pstQnode->stDbg.usTraceFileId   =   usFileID;
    pstQnode->stDbg.usTraceLineNum  =   usLineNum;

    return PS_SUCC;
} /* PS_Qnode_Trace */

/*****************************************************************************
 �� �� ��  : PS_Qnode_ShowBinaryInfo
 ��������  : �����ƴ�ӡ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��11��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PS_Qnode_ShowBinaryInfo(VOS_UINT32 ulValue)
{
    VOS_UINT32              ulLoop;
    const VOS_UINT32        ul32Bit = 32;
    VOS_UINT8               ucChar;

    for (ulLoop = 0; ulLoop < ul32Bit; ulLoop++)
    {
        if (TTF_GET_A_BIT(ulValue, (ul32Bit - ulLoop - 1)))
        {
            ucChar = '1';
        }
        else
        {
            ucChar = '0';
        }
        vos_printf("%c", ucChar);
    }

    return;
} /* PS_Qnode_ShowBinaryInfo */

/*****************************************************************************
 �� �� ��  : PS_Qnode_ShowUsedInfo
 ��������  : ��ʾ���õ�Qnode���(������API)
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��11��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PS_Qnode_ShowUsedInfo(VOS_VOID)
{
    VOS_UINT32              ulLoop;
    VOS_UINT32              ulCurr;
    const VOS_UINT32        ul32Bit = 32;

    if (PS_QNODE_TRACE_PRINT_ON == g_stMgmt.enIsTracePrintOn)
    {
        for (ulLoop = 0; ulLoop < MAX_PS_QNODE_4BYTE_ALIGN_NUM; ulLoop++)
        {
            ulCurr = g_stMgmt.aulQuickMap[ulLoop];
            vos_printf("Index from %d to %d: [0b", (ulLoop * ul32Bit),
                (((ulLoop + 1) * ul32Bit) - 1));
            PS_Qnode_ShowBinaryInfo(ulCurr);
            vos_printf("]\n");
        }
    }
    else
    {
        vos_printf("Enable trace print function by PS_Qnode_SetTracePrint(1).\n");
    }
} /* PS_Qnode_ShowUsedInfo */

/*****************************************************************************
 �� �� ��  : PS_Qnode_ShowUsedInfo
 ��������  : ��ʾ���õ�Qnode�����ϸ(������API)
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��20��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PS_Qnode_ShowDetailUsedInfo(VOS_VOID)
{
    VOS_UINT32               ulLoop;
    PS_QNODE_DEBUG_STRU     *pstDbg;
    VOS_UINT32               ulUsedCnt;
    const VOS_UINT32         ulConsectivePrintCnt  = 200; /* һ���Դ�ӡ�������� */

    if (PS_QNODE_TRACE_PRINT_ON == g_stMgmt.enIsTracePrintOn)
    {
        PS_Qnode_ShowUsedInfo();

        ulUsedCnt   = 0;

        for (ulLoop = 0; ulLoop < MAX_PS_QNODE_NUM; ulLoop++)
        {
            if (PS_QNODE_USED_STATE == g_astQnode[ulLoop].enState)
            {
                pstDbg  =   &(g_astQnode[ulLoop].stDbg);
                vos_printf("index = %u, Alloc fileid=%u, line=%u, tick=0x%x, trace fileid=%u, line=%u, tick=0x%x\n",
                    g_astQnode[ulLoop].usIndex, pstDbg->usAllocFileId,
                    pstDbg->usAllocLineNum, pstDbg->ulAllocTick,
                    pstDbg->usTraceFileId, pstDbg->usTraceLineNum,
                    pstDbg->ulTraceTick);

                ulUsedCnt++;
                /* Ϊ�˷�ֹ������ӡ�����ڴ���, ÿ�δ�ӡһ������, ���ӳ�, Ȼ�������ӡ */
                if (ulUsedCnt >= ulConsectivePrintCnt)
                {
                    VOS_TaskDelay(10);
                    ulUsedCnt   =   0;
                }
            }
        }
    }
    else
    {
        vos_printf("Enable trace print function by PS_Qnode_SetTracePrint(1).\n");
    }

    return;
} /* PS_Qnode_ShowDetailUsedInfo */

/*****************************************************************************
 �� �� ��  : PS_Qnode_SetTracePrint
 ��������  : ʹ��Qnode���trace print����(������API)
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��20��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PS_Qnode_SetTracePrint(PS_QNODE_TRACE_PRINT_SWITCH_ENUM_UINT8 enPrint)
{
    if (PS_QNODE_TRACE_PRINT_BUTT <= enPrint)
    {
        vos_printf("para error\n");
        return;
    }

    g_stMgmt.enIsTracePrintOn = enPrint;

    return;
} /* PS_Qnode_SetTracePrint */

/*****************************************************************************
 �� �� ��  : PS_Qnode_Statistics
 ��������  : ��ʾQnode���ͳ��(������API)
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��20��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PS_Qnode_Statistics(VOS_VOID)
{
    vos_printf("total alloc %u times\n",          g_stMgmt.stStat.ulAllocTotalCnt);
    vos_printf("alloc fail %u times\n",           g_stMgmt.stStat.ulAllocFailCnt);
    vos_printf("total free %u times\n",           g_stMgmt.stStat.ulFreeTotalCnt);
    vos_printf("free null ptr %u times\n",        g_stMgmt.stStat.ulFreeNullPtrCnt);
    vos_printf("free unused ptr %u times\n",      g_stMgmt.stStat.ulFreePtrBeforeCnt);
    vos_printf("found tampered qnode %u times\n", g_stMgmt.stStat.ulMagicTamperedCnt);
    vos_printf("free invalid ptr %u times\n",     g_stMgmt.stStat.ulFreeInvalidPrtCnt);

    return;
} /* PS_Qnode_Statistics */

/*****************************************************************************
 �� �� ��  : PS_Qnode_Help
 ��������  : Qnode�����԰�������(������API)
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��20��
    ��    ��   : liukai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PS_Qnode_Help(VOS_VOID)
{
    vos_printf("********************TTF_Qnode DEBUG INFO************************\n");
    vos_printf("PS_Qnode_ShowUsedInfo(VOS_VOID)             Show used PsQnode when trace print is enabled.\n");
    vos_printf("PS_Qnode_ShowDetailUsedInfo(VOS_VOID)       Show detail of used PsQnode when trace print is enabled.\n");
    vos_printf("PS_Qnode_SetTracePrint(enPrint)             Enable/Disable trace print. Setting enPrint = 0, it will be disabled.\n");
    vos_printf("PS_Qnode_Statistics(VOS_VOID)               Show Qnode statistics.\n");

    return;
} /* PS_Qnode_Help */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


