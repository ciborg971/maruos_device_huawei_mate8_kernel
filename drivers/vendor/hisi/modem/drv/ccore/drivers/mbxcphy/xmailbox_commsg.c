
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "xmailbox_types.h"
#include <mdrv_timer.h>
#include <mdrv_bbp.h>
#include <bsp_version.h>
#include "bsp_hardtimer.h"
#include "xmailbox.h"
#include "mdrv_dsp.h"
#include "bsp_ipc.h"

/*****************************************************************************
 �� �� ��  : xMbx_ForbidDspSleep
 ��������  : ����AXI memory��ֹDSP����˯��
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
static void xMbx_ForbidDspSleep(void)
{
    unsigned long key;

    local_irq_save(key);
    g_stxMbxCtrl.lAxiCnt++;
    writel(1, (unsigned)(g_stxMbxCtrl.pulAxiAddr));
    local_irq_restore(key);
}

/*****************************************************************************
 �� �� ��  : xMbx_ForbidDspSleep
 ��������  : ���AXI memory����DSP����˯��
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
static void xMbx_AllowDspSleep(void)
{
    unsigned long key;

    local_irq_save(key);
    if((--g_stxMbxCtrl.lAxiCnt) <= 0)
    {
        g_stxMbxCtrl.lAxiCnt = 0;
        writel(0, (unsigned)(g_stxMbxCtrl.pulAxiAddr));
    }
    local_irq_restore(key);
}

/*lint -save -e717*/
/*****************************************************************************
 Prototype       : xMbx_ComPsPreProc
IPC_INT_DSP_PS_MAC_MBX Description     : PS�����Ԥ������(��Ҫ�����Ǹ���PS/CTBT��Ϣ������Ϣ)
                   1. ��������PS��Ϣ�������PS��Ϣ����
                   2. ��������CT/BT��Ϣ�������PS��Ϣ����
                   3. �������ж��е��ã����ܴ�ӡ��malloc
                   4. DSP��֤�����е�ԭ��δ����ʱ��˯��
 param           : None
 Return Value    : void
*****************************************************************************/
void xMbx_ComPsPreProc()
{
    unsigned long key;
    xMAILBOX_RINGBUFF_STRU* pstComPsUpMail = (xMAILBOX_RINGBUFF_STRU*)(g_stxMbxShareAddr.ulCphyMbxHpaUpAddr);
    xMAILBOX_MSG_HAED_STRU *pstMsgHead;
    u32 ulUpWrPtr = 0;

    /* �����ǰԭ�ﳤ�Ȳ�Ϊ0����ʾ��δ���ߣ�����Ҫ���� */
    if(0 != g_stxMbxCtrl.ulMsgLen) {
        return ;
    }

    local_irq_save(key);


    ulUpWrPtr = pstComPsUpMail->ulRbufWrPtr;

    /* ���дָ��Ƿ����������� */
    if(ulUpWrPtr > pstComPsUpMail->ulRbufSize)
    {
        local_irq_restore(key);
        system_error(DRV_ERRNO_MBX_UP_WR, ulUpWrPtr, pstComPsUpMail->ulRbufRdPtr, (char*)NULL, 0);
        return;
    }

    if(pstComPsUpMail->ulRbufRdPtr == ulUpWrPtr) {
        g_stxMbxCtrl.ulMsgLen = 0;
    } else {
        pstMsgHead = (xMAILBOX_MSG_HAED_STRU*) \
            (pstComPsUpMail->ulRbufRdPtr + pstComPsUpMail->pucRbufAddr + MAILBOX_ADDR_OFFSET);

        g_stxMbxCtrl.ulMsgLen = (u32)(*(u32*)pstMsgHead);    /* ��16λ��¼mod����16λ��¼���� */  /*lint !e740*/
    }

    local_irq_restore(key);

    return ;
}

/*lint -restore*/
/*****************************************************************************
 Prototype       : BSP_xMailbox_ForbidDspSleep
 Description     : ��ֹDSP˯�߽ӿ�(��BSP_Mailbox_AllowDspSleep���ʹ��)
 Input           : enProcType     DSP˯��ʱ�Ĵ�������
                    EN_MAILBOX_SLEEP_WAKEUP : ǿ�ƻ���ʱ���еȴ�����
                                              �������жϻص�������˲���
                                              ֻ��������������˲���
                    EN_MAILBOX_SLEEP_LOST   : �жϻص��������ж�������˲���
                   pkey : intLock key

 Return Value    : BSP_OK: �ɹ�,DSP��ǰû˯�ߣ��������ý�ֹDSP����˯��
                   ERR_MAILBOX_DSP_POWERDOWN : ������ΪEN_MAILBOX_SLEEP_LOST,
                                               DSP��ǰ���ڵ͹���״̬,����ʧ��
                   ERR_MAILBOX_TIMEOUT       : ������ΪEN_MAILBOX_SLEEP_WAKEUP,
                                               ����DSP��ʱ(10s)
*****************************************************************************/
unsigned int BSP_xMailbox_ForbidDspSleep(MAILBOX_SLEEP_PROC_E enProcType)
{
    s32 ret;

    if (g_stxMbxCtrl.mem_init == 0) {
        xMbx_Printf("xMailbox is not inited \n");
        return ERR_MAILBOX_NOT_INIT;
    }

    xMbx_ForbidDspSleep();

    if(EN_MAILBOX_SLEEP_DIRECT == enProcType)/*ֱ�ӷ���OK*/
    {
        g_stxMbxMntn.stDirectInfo.ulSlice[g_stxMbxMntn.stDirectInfo.ulPtr%MAILBOX_MNTN_NUMBER] = bsp_get_slice_value();
        g_stxMbxMntn.stDirectInfo.ulPtr++;
        return BSP_OK;
    }

    if((NULL != g_stxMbxCtrl.pfnGetDspStatusProc) && (BSP_TRUE == g_stxMbxCtrl.pfnGetDspStatusProc()))
    {
        if (EN_MAILBOX_SLEEP_WAKEUP == enProcType) {
            ret = osl_sem_downtimeout(&g_stxMbxCtrl.semDspMutex, (MAILBOX_WAKEUP_TIMEOUT*2));
            if(BSP_OK != ret)
            {
                xMbx_Printf("semTake semDspMutex failed.\n");

                ret = ERR_MAILBOX_TIMEOUT;
                goto mbx_forbiddspsleep_fail;/*lint !e801*/
            }

            /* ���õ͹��Ľӿڻ���DSP */
            if(NULL == g_stxMbxCtrl.pfnDspForceAwakeProc)
            {
                ret = ERR_MAILBOX_TIMEOUT;

                osl_sem_up(&g_stxMbxCtrl.semDspMutex);

                goto mbx_forbiddspsleep_fail;/*lint !e801*/
            }

            /* ��¼��־����ʾ������ģ�鷢��Ļ���DSP */
            g_stxMbxCtrl.bDspWakeFlag = BSP_TRUE;

            g_stxMbxMntn.stSleepInfo.astwakeup[g_stxMbxMntn.stSleepInfo.ulPtr].ulSlice1 = bsp_get_slice_value();

            g_stxMbxCtrl.pfnDspForceAwakeProc();

            /* �ȴ�DSP������ */
            /* coverity[lock] */
            ret = osl_sem_downtimeout(&g_stxMbxCtrl.semDspWakeup, MAILBOX_WAKEUP_TIMEOUT);

            g_stxMbxMntn.stSleepInfo.astwakeup[g_stxMbxMntn.stSleepInfo.ulPtr].ulSlice3 = bsp_get_slice_value();
            g_stxMbxMntn.stSleepInfo.ulPtr = (g_stxMbxMntn.stSleepInfo.ulPtr+1)%MAILBOX_MNTN_NUMBER;

            if (BSP_OK != ret) {
                xMbx_Printf("semTake semDspWakeup failed.\n");

                ret = ERR_MAILBOX_TIMEOUT;

                osl_sem_up(&g_stxMbxCtrl.semDspMutex);

                goto mbx_forbiddspsleep_fail;/*lint !e801*/
            }

            osl_sem_up(&g_stxMbxCtrl.semDspMutex);
        }
        else if(EN_MAILBOX_SLEEP_LOST == enProcType)
        {
            ret = ERR_MAILBOX_DSP_POWERDOWN;
            goto mbx_forbiddspsleep_fail;/*lint !e801*/
        }
        else
        {
            ret = ERR_MAILBOX_PARAM_INCORRECT;

            goto mbx_forbiddspsleep_fail;/*lint !e801*/
        }
    }

    return BSP_OK;

mbx_forbiddspsleep_fail:

    xMbx_AllowDspSleep();

    return (u32)ret;
}


/*****************************************************************************
 Prototype       : BSP_xMailbox_AllowDspSleep
 Description     : ����DSP˯�߽ӿ�(��BSP_Mailbox_ForbidDspSleep���ʹ��)
 Input           : key : intLock key
 Return Value    : None
*****************************************************************************/
void BSP_xMailbox_AllowDspSleep(void)
{

    xMbx_AllowDspSleep();

}

/*****************************************************************************
 Prototype      : BSP_xMailBox_ComMsgInit
 Description    : ͨ������ĳ�ʼ��(�ṩ��Э��ջ���ã�
                  �ӿ��ڲ�ʵ������������ĳ�ʼ������DSP������Ϣ�ĳ�ʼ��)
 Input          : None
 Return Value   : None
*****************************************************************************/
void BSP_xMailBox_ComMsgInit(unsigned int ulworkingmode)
{
    unsigned long key;
    u32 ret;

    ret = BSP_xMailbox_ForbidDspSleep(EN_MAILBOX_SLEEP_WAKEUP);
    if((BSP_OK != ret) && (ERR_MAILBOX_DSP_POWERDOWN != ret))
    {
        xMbx_Printf("BSP_Mailbox_ForbidDspSleep failed.\n");
        return ;
    }

    local_irq_save(key);

    /* ��ʼ��������Ϣ */
    *((u32 *)g_stxMbxShareAddr.ulCphyMbxLoadMemAddr) = 0;

    /* PS��DSP���ù���ģʽ(������˫����RTT��ȫϵͳ����Ϣ) */
    *((u32 *)g_stxMbxShareAddr.ulCphyMbxWorkModeAddr) = ulworkingmode;

    local_irq_restore(key);

    BSP_xMailbox_AllowDspSleep();

    xMbx_Printf("init success.\n");
}


/*****************************************************************************
 Prototype      : BSP_xMailBox_IsDspOk
 Description    : ��DSP�����ֺ������ж�DSP�Ƿ��ʼ������
                  (�ṩ��Э��ջ���ã�������ֲ��ɹ���Э��ջ��Ҫѭ����ε���)
 Input          : None
 Return Value   : BSP_TRUE: DSP��ʼ�����������ֳɹ�
                  BSP_FALSE:DSPû�г�ʼ�����������ֲ��ɹ�
*****************************************************************************/
int BSP_xMailBox_IsDspOk(void)
{
    if (g_stxMbxCtrl.mem_init == 0) {
        xMbx_Printf("xMailbox is not inited \n");
        return BSP_FALSE;
    }
    
    if(*((u32 *)g_stxMbxShareAddr.ulCphyMbxLoadMemAddr) != BSP_CPHY_SHAKEHAND_CMP)
    {
        return BSP_FALSE;
    }

    g_stxMbxCtrl.bMbxInit = BSP_TRUE;
    return BSP_TRUE;
}


void xMbx_MntnWritStart(MAILBOX_SERVICE_TYPE_E enMbxType)
{
    g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulSliceStart = bsp_get_slice_value();

    switch(enMbxType)
    {
        case EN_MAILBOX_SERVICE_XSYS_RL:

            g_stxMbxMntn.stNumber.ulPsComPsReqNum++;
            return;


        case EN_MAILBOX_SERVICE_XSYS_CT:
        case EN_MAILBOX_SERVICE_XSYS_BT:

            g_stxMbxMntn.stNumber.ulPsComMspReqNum++;
            return;

        case EN_MAILBOX_SERVICE_XSYS_OM:
            g_stxMbxMntn.stNumber.ulOmComReqNum++;
            return;
        default :
            return ;
    }
}

void xMbx_MntnWriteEnd(xMAILBOX_RINGBUFF_STRU* pHead, xMAILBOX_MSG_HAED_STRU* pstMsg, u32 ulTempPPTR)
{
    u32 ulInterval = 0;

    g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulSliceEnd = bsp_get_slice_value();
    g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulModId = pstMsg->usDstMod;
    g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulMsgId = *(u32*)(pstMsg->pPayload);
    g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulRWPtr = (pHead->ulRbufRdPtr << 16) | ulTempPPTR;

    ulInterval = (g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulSliceEnd
                - g_stxMbxMntn.stReqInfo.astReq[g_stxMbxMntn.stReqInfo.ulPtr].ulSliceStart);
    if(ulInterval > g_stxMbxMntn.stAbnormal.ulLongestReq)
    {
        g_stxMbxMntn.stAbnormal.ulLongestReq = ulInterval;
    }

    g_stxMbxMntn.stReqInfo.ulPtr = (g_stxMbxMntn.stReqInfo.ulPtr+1)%MAILBOX_MNTN_NUMBER;
}

/*lint -save -e958*/
/*****************************************************************************
 Prototype       : xMailbox_ComMsgWrite
 Description     : ����д�ӿڴ����װ�ӿ�
 Input           : ucModule     ģ��ID
                   pstAddr      ����ͷ��ַ
                   pData        ����ָ��
                   ulLen        ���ݳ���(���ֽ�Ϊ��λ)
 Output          : None.
 Return Value    : BSP_OK: �ɹ�
                   ����: ʧ��
*****************************************************************************/
u32 xMailbox_ComMsgWrite(u8 ucModule,
                            xMAILBOX_RINGBUFF_STRU* pstAddr,
                            void* pData,
                            u32 ulLen)
{
    unsigned long key;
    s32 ret = BSP_OK;
    xMAILBOX_MSG_HAED_STRU stBuffer = {0};

    stBuffer.usMsgSize = (u16)((ulLen + 3) & (~3));
    stBuffer.usDstMod = (u16)ucModule;
    stBuffer.pPayload = pData;

    /* coverity[lock_acquire] */
    local_irq_save(key);
    ret = xMbx_RbuffWrite(pstAddr, &stBuffer);
    local_irq_restore(key);

    if(BSP_OK != ret)
    {
        xMbx_Printf("Mbx_RbuffWrite failed %d, ucModule %d.\n", ret, ucModule);
        xMbx_SystemError((u32)MBX_ERROR_WR_FULL, (u32)stBuffer.usMsgSize, pstAddr->ulRbufRdPtr, pstAddr->ulRbufWrPtr);
    }
    else
    {
        if ((MBX_ADDRESSER_XSYS_PHY_CT == ucModule) ||(MBX_ADDRESSER_XSYS_PHY_BT == ucModule))

        {
            xMbx_Printf(" Write CBT 0x%x success.\n",  *((u32*)pData));
        }
    }

    return (u32)ret;
}

/*****************************************************************************
 Prototype       : BSP_xMailBox_ComMsgWrite
 Description     : ����д�ӿ�(ÿ��ֻ֧��дһ��ԭ��)
 Input           : enMbxType    �����ҵ������
                   pData        ����ָ��
                   ulLen        ���ݳ���(���ֽ�Ϊ��λ)
                   enProcType   DSP˯��ʱ�Ĵ�������
 Output          : None.
 Return Value    : BSP_OK: �ɹ�
                   ����: ʧ��
*****************************************************************************/
unsigned int BSP_xMailBox_ComMsgWrite(MAILBOX_SERVICE_TYPE_E enMbxType,
                               void* pData,
                               unsigned int ulLen,
                               MAILBOX_SLEEP_PROC_E enProcType)
{
    u32 ret = 0;
    xMAILBOX_RINGBUFF_STRU* pstAddr;
    u8 ucModule = 0;
    xMAILBOX_CHANNEL_TABLE_STRU *pMbxTbl;
	u32 xmbx_ipc_coreid;

    g_stxMbxMntn.stNumber.ulPsComReqNum++;

    if((BSP_NULL == pData) || (0 == ulLen) || xMbx_invalid_type(enMbxType))
    {
        xMbx_Printf("pData %p, ulLen %d, enMbxType %d.\n", pData, ulLen, enMbxType);

        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    if((EN_MAILBOX_SERVICE_XSYS_CT == enMbxType)
		||(EN_MAILBOX_SERVICE_XSYS_BT == enMbxType))
    {
        xMbx_Printf("Write CBT 0x%x request.\n", *((u32*)pData));
    }

    if(!(g_stxMbxCtrl.bMbxInit))
    {
        g_stxMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return ERR_MAILBOX_NOT_INIT;
    }
	/*lint -save -e737*/
    xMbx_Trace(pData, ulLen);
	/*lint -restore*/
    pMbxTbl = xMbx_get_tbl(enMbxType);
    pstAddr     = (xMAILBOX_RINGBUFF_STRU*)pMbxTbl->ulDlAddr;
    ucModule    = (u8)pMbxTbl->ulModule;

    xMbx_MntnWritStart(enMbxType);

    ret = BSP_xMailbox_ForbidDspSleep(enProcType);
    if(BSP_OK != ret)
    {
        xMbx_Printf("***[%s]BSP_xMailbox_ForbidDspSleep ret %d\n",__FUNCTION__, ret);
        return ret;
    }

    ret = xMailbox_ComMsgWrite(ucModule, pstAddr, pData, ulLen);
    if(BSP_OK != ret)
    {
        xMbx_Printf("Mailbox_ComMsgWrite failed %d.\n", ret);
    }

    if(BSP_OK == ret)
    {
        
        if(CHIP_K3V5 == bsp_get_version_info()->chip_type) {
			xmbx_ipc_coreid = IPC_CORE_LDSP;
        }
		else {
			xmbx_ipc_coreid = IPC_CORE_BBE;
		}
        if(BSP_OK != bsp_ipc_int_send((IPC_INT_CORE_E)xmbx_ipc_coreid, pMbxTbl->ulIntNum)) {
            xMbx_Printf("failed to send IPC int %d\n",pMbxTbl->ulIntNum);
        }
    }

    BSP_xMailbox_AllowDspSleep();

    return ret;
}

/*****************************************************************************
 Prototype       : BSP_xMailBox_ComNotifyReg
 Description     : �������ݵ���֪ͨע��ӿڣ���֡�жϼ�ʹû����ҲҪ�ص���
 param           : enMbxType        �����ҵ������
                   pFun             �������ݵ��ﴦ����
 Return Value    : BSP_OK: �ɹ�
                   ERR_MAILBOX_NOT_INIT
                   ERR_MAILBOX_PARAM_INCORRECT
*****************************************************************************/
unsigned int BSP_xMailBox_ComNotifyReg(MAILBOX_SERVICE_TYPE_E enMbxType,
                                BSP_xMBX_NOTIFY_FUNC pFun)
{
    xMAILBOX_CHANNEL_TABLE_STRU *pMbxTbl;
    /* Ŀǰ�Ļ�������һ��ҵ��ֻע��һ���ص������������ͨ����Ҫ���⴦�� */
    if(xMbx_invalid_type(enMbxType))
    {
        xMbx_Printf("enMbxType %d.\n", enMbxType);
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    switch(enMbxType)
    {
        case EN_MAILBOX_SERVICE_XSYS_RL:
        {
            pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_XSYS_RL);
            pMbxTbl->pFnCallBack = pFun;
            break;
        }
        case EN_MAILBOX_SERVICE_XSYS_BT:
        case EN_MAILBOX_SERVICE_XSYS_CT:
        {
            pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_XSYS_BT);
            pMbxTbl->pFnCallBack = pFun;
            pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_XSYS_CT);
            pMbxTbl->pFnCallBack = pFun;
            break;
        }

        default :
        {
            pMbxTbl = xMbx_get_tbl(enMbxType);
            pMbxTbl->pFnCallBack = pFun;
        }
    }

    return BSP_OK;
}



/*****************************************************************************
 Prototype       : BSP_xMailBox_ComMsgSize
 Description     : ��ȡͨ�������е�һ��ԭ��ĳ���
                   (�ṩ���ϲ���ã��������ṩ������ԭ�������ӿڣ���Ҫ�ϲ�ѭ��
                   �����Ա����ϲ�©���ж�֪ͨʱ���������ԭ�ﻺ��)
 param           : enMbxType        �����ҵ������
 Return Value    : 0:  û�л�ȡԭ�����Ϊ�գ������������͵�ԭ��δ���ߣ�
                   ����ֵ: �����һ��ԭ��ĳ���
*****************************************************************************/
unsigned int BSP_xMailBox_ComMsgSize(MAILBOX_SERVICE_TYPE_E enMbxType)
{
    u32 ret;
    u32 len;
    unsigned long key;

    if (xMbx_invalid_type(enMbxType)) {
        xMbx_Printf("enMbxType %d.\n", enMbxType);
        return 0;
    }

    if(EN_MAILBOX_SERVICE_XSYS_OM == enMbxType) {
        local_irq_save(key);
        len = (g_stxMbxCtrl.ulOmMsgLen & 0x0000ffff);
        ret = xmbx_IsChnModMatch(enMbxType, (g_stxMbxCtrl.ulOmMsgLen >> 16));
        local_irq_restore(key);
    } else if(EN_MAILBOX_SERVICE_XSYS_RL == enMbxType) {
        local_irq_save(key);
        len = (g_stxMbxCtrl.ulMsgLen & 0x0000ffff);
        ret = xmbx_IsChnModMatch(enMbxType, (g_stxMbxCtrl.ulMsgLen >> 16));
        local_irq_restore(key);
    } else {
        xMbx_Printf("input error mode.\n");
        return 0;
    }

    if(BSP_OK == ret) {
        return len;
    }

    return 0;
}


/* �����ȡ����ʱ����Ϣ��¼ */
void xMbx_MntnReadStart(MAILBOX_SERVICE_TYPE_E enMbxType)
{
    xMAILBOX_MNTN_READ_STRU *pstCnf = NULL;
    u32 *pluPtr = NULL;

    pstCnf = &(g_stxMbxMntn.stReadInfo.astRead[g_stxMbxMntn.stReadInfo.ulPsPtr]);
    pluPtr = &(g_stxMbxMntn.stReadInfo.ulPsPtr);

    pstCnf->ulSrc = enMbxType;
    pstCnf->ulSlice = bsp_get_slice_value();
    *pluPtr = (*pluPtr+1)%MAILBOX_MNTN_NUMBER;

    if(EN_MAILBOX_SERVICE_XSYS_RL == enMbxType)
    {
        g_stxMbxMntn.stNumber.ulPsComPsRdNum++;
    }
    else
    {
        g_stxMbxMntn.stNumber.ulPsComMspRdNum++;
    }

}


void xMbx_MntnReadEnd(void* pData, enum __MBX_ADDRESSEE_ID_ENUM__ enMbxType, u32 pRd, u32 pWr)
{
    xMAILBOX_MNTN_CNF_STRU *pstCnf = NULL;
    u32 *pluPtr = NULL;

    if(MBX_ADDRESSER_XSYS_PHY_RL == enMbxType)
    {
        g_stxMbxMntn.stNumber.ulPsComPsRdOKNum++;

        pstCnf = &(g_stxMbxMntn.stCnfInfo.astPsCnf[g_stxMbxMntn.stCnfInfo.ulPsPtr]);

        pluPtr = &(g_stxMbxMntn.stCnfInfo.ulPsPtr);
    }
    else if(MBX_ADDRESSER_XSYS_PHY_OM == enMbxType)
    {
        g_stxMbxMntn.stNumber.ulOmComOmRdNum++;

        pstCnf = &(g_stxMbxMntn.stCnfInfo.astOmCnf[g_stxMbxMntn.stCnfInfo.ulOmPtr]);

        pluPtr = &(g_stxMbxMntn.stCnfInfo.ulOmPtr);
    }
    else
    {
        g_stxMbxMntn.stNumber.ulPsComMspRdOKNum++;

        pstCnf = &(g_stxMbxMntn.stCnfInfo.astCbtCnf[g_stxMbxMntn.stCnfInfo.ulCbtPtr]);

        pluPtr = &(g_stxMbxMntn.stCnfInfo.ulCbtPtr);
    }

    pstCnf->ulMsgId = *(u32*)pData;
    pstCnf->ulRWptr = (pRd << 16) | pWr;
    pstCnf->ulSlice = bsp_get_slice_value();

    *pluPtr = (*pluPtr+1)%MAILBOX_MNTN_NUMBER;
}


/*****************************************************************************
 Prototype       : xMbx_MsgRead
 Description     : ����ԭ����ӿ�
                   (�˽ӿ��ڲ�����)
 param           : pData        ���յ����ݻ�����ָ��(�洢ԭ����Ϣ��������ԭ�ﳤ��)
                   ulLen        pData��������size(���ֽ�Ϊ��λ)
 Return Value    : 0 : �ɹ�
                   ���� : ʧ��
*****************************************************************************/
u32 xMbx_MsgRead(MAILBOX_SERVICE_TYPE_E enMbxType, void* pData, u32 ulLen)
{
    unsigned long key;
    u32 ret;
    u32 mod;
    u32 len;
    xMAILBOX_MSG_HAED_STRU stBuffer = {0};
    xMAILBOX_RINGBUFF_STRU* pstComPsUpMail;

    if(EN_MAILBOX_SERVICE_XSYS_RL == enMbxType) {
        pstComPsUpMail = (xMAILBOX_RINGBUFF_STRU*)g_stxMbxShareAddr.ulCphyMbxHpaUpAddr;
    } else if(EN_MAILBOX_SERVICE_XSYS_OM == enMbxType) {
        pstComPsUpMail = (xMAILBOX_RINGBUFF_STRU*)g_stxMbxShareAddr.ulCphyMbxHpaDownAddr;
    } else {
        xMbx_Printf(" input error enMbxType.\n");
        return ERR_MAILBOX_READ_FAILED;
    }

    if(EN_MAILBOX_SERVICE_XSYS_RL == enMbxType) {
        local_irq_save(key);
        mod = (u16)(g_stxMbxCtrl.ulMsgLen >> 16);
        len = (u16)(g_stxMbxCtrl.ulMsgLen & 0x0000ffff);
        local_irq_restore(key);
    } else if(EN_MAILBOX_SERVICE_XSYS_OM == enMbxType) {
        local_irq_save(key);
        mod = (u16)(g_stxMbxCtrl.ulOmMsgLen >> 16);
        len = (u16)(g_stxMbxCtrl.ulOmMsgLen & 0x0000ffff);
        local_irq_restore(key);
    } else {
        xMbx_Printf("input error enMbxType.\n");
        return ERR_MAILBOX_READ_FAILED;
    }

    ret = xmbx_IsChnModMatch(enMbxType, mod);
    if(BSP_OK != ret) {
        xMbx_Printf("enMbxType(0x%x)  g_stxMbxCtrl.ulMsgLen(0x%x).\n",
            enMbxType, g_stxMbxCtrl.ulMsgLen);
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    if(ulLen != len) {
        xMbx_Printf("ulLen(0x%x) != g_stxMbxCtrl.ulMsgLen(0x%x).\n",
            ulLen, g_stxMbxCtrl.ulMsgLen);
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    stBuffer.usMsgSize = (u16)ulLen;  /* for compare with actually length */
    stBuffer.pPayload = pData;

    local_irq_save(key);
    ret = xMbx_NewMsgReadOut(&stBuffer, pstComPsUpMail); /* [false alarm]:fortify */
    local_irq_restore(key);

    if(stBuffer.usMsgSize != (u16)len) {
        xMbx_Printf("pBuffer->usMsgSize(0x%x) != g_stxMbxCtrl.ulMsgLen(0x%x).\n",
            stBuffer.usMsgSize, g_stxMbxCtrl.ulMsgLen);
        ret = ERR_MAILBOX_READ_FAILED;
    } else {
        ret = BSP_OK;
    }

    /* ��ȡ�ɹ���ѳ������㣬�����´ζ�ȡ */
    if(EN_MAILBOX_SERVICE_XSYS_OM == enMbxType) {
        local_irq_save(key);
        g_stxMbxCtrl.ulOmMsgLen = 0;
        local_irq_restore(key);
    } else if(EN_MAILBOX_SERVICE_XSYS_RL == enMbxType) {
        local_irq_save(key);
        g_stxMbxCtrl.ulMsgLen = 0;
        local_irq_restore(key);
    } else {
        xMbx_Printf(" input error enMbxType.\n");
        return ERR_MAILBOX_READ_FAILED;
    }

    return ret;
}


/*****************************************************************************
 Prototype       : BSP_xMailBox_ComMsgRead
 Description     : ������ӿ�
                   (�˽ӿڻỽ��DSP����ҪBSP_MailBox_ComMsgSize���طǿ�ʱ����)
 param           : enMbxType    �����ҵ������
                   pData        ���յ����ݻ�����ָ��(�洢ԭ����Ϣ��������ԭ�ﳤ��)
                   ulLen        pData��������size(���ֽ�Ϊ��λ)
                   enProcType   DSP˯��ʱ�Ĵ�������
 Return Value    : 0 : �ɹ�
                   ���� : ʧ��
*****************************************************************************/
unsigned int BSP_xMailBox_ComMsgRead(MAILBOX_SERVICE_TYPE_E enMbxType,
                               void* pData,
                               unsigned int ulLen,
                               MAILBOX_SLEEP_PROC_E enProcType)
{
    unsigned long key;
    u32 ret;
    u16 mod;
    u16 len;
    u32 ulChn;
    MAILBOX_INT_TYPE_E enType;
    xMAILBOX_CHANNEL_TABLE_STRU *pMbxTbl;

    if((BSP_NULL == pData) || (0 == ulLen) || (xMbx_invalid_type(enMbxType)))
    {
        xMbx_Printf(" %p,%d,%d.\n", pData, ulLen, enMbxType);
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    /* ��¼���������ʱ����Ϣ */
    xMbx_MntnReadStart(enMbxType);

    if(!(g_stxMbxCtrl.bMbxInit))
    {
        g_stxMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return ERR_MAILBOX_NOT_INIT;
    }

    ret = BSP_xMailbox_ForbidDspSleep(enProcType);
    if(BSP_OK != ret)
    {
        xMbx_Printf("BSP_Mailbox_ForbidDspSleep failed.\n");
        return ret;
    }

    ret = xMbx_MsgRead(enMbxType, pData, ulLen);
	/*lint -save -e737*/
    xMbx_Trace(pData,ulLen);
	/*lint -restore*/
    /* ����g_stxMbxCtrl.ulPsMsgLen */
    xMbx_ComPsPreProc();

    BSP_xMailbox_AllowDspSleep();

    if(EN_MAILBOX_SERVICE_XSYS_RL == enMbxType) {
        local_irq_save(key);
        mod = (u16)(g_stxMbxCtrl.ulMsgLen >> 16);
        len = (u16)(g_stxMbxCtrl.ulMsgLen & 0x0000ffff);
        local_irq_restore(key);
    } else if(EN_MAILBOX_SERVICE_XSYS_OM == enMbxType) {
        local_irq_save(key);
        mod = (u16)(g_stxMbxCtrl.ulOmMsgLen >> 16);
        len = (u16)(g_stxMbxCtrl.ulOmMsgLen & 0x0000ffff);
        local_irq_restore(key);
    } else {
        xMbx_Printf("input error mode.\n");
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    if(0 != len) {
        ulChn = xmbx_GetChn(mod);
        if(EN_MAILBOX_SERVICE_TOTAL_BUTT == ulChn) {
            /* DSPд���˷Ƿ���MOD�������ֳ������� */
            xMbx_SystemError(MBX_ERROR_DL_MOD, g_stxMbxCtrl.ulMsgLen, (u32)mod, (u32)len); /* [false alarm]:fortify */
            return ret;
        }

        if((u16)MBX_ADDRESSER_XSYS_PHY_RL == mod) {
            g_stxMbxMntn.stNumber.ulPsComPsNotifyNum++;
            g_stxMbxMntn.stCallback.ulSlice[g_stxMbxMntn.stCallback.ulPtr] = bsp_get_slice_value();
            g_stxMbxMntn.stCallback.ulPtr = (g_stxMbxMntn.stCallback.ulPtr+1)%MAILBOX_MNTN_NUMBER;
        } else {
            g_stxMbxMntn.stNumber.ulPsComMspNotifyNum++;
        }

        pMbxTbl = xMbx_get_tbl(ulChn);
        if(pMbxTbl->pFnCallBack) {
            enType = g_stxMbxCtrl.bIsSubFrameInt ? EN_MAILBOX_INT_SUBFRAME : EN_MAILBOX_INT_COM_IPC;
            pMbxTbl->pFnCallBack(enType);
        }
    }

    return ret;
}

void xMbx_CallBackProc(void)
{
    MAILBOX_INT_TYPE_E enType;
    u32 ulChn;
    u16 mod;
    u16 len;
    unsigned long key;
    xMAILBOX_CHANNEL_TABLE_STRU *pMbxTbl;

    local_irq_save(key);
    mod = (u16)(g_stxMbxCtrl.ulMsgLen >> 16);
    len = (u16)(g_stxMbxCtrl.ulMsgLen & 0x0000ffff);
    local_irq_restore(key);

    /* ��֡�жϻ���PSԭ����ص�PS */
    if((g_stxMbxCtrl.bIsSubFrameInt) || ((0 != len) && ((u16)MBX_ADDRESSER_XSYS_PHY_RL == mod))) {
        pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_XSYS_RL);
        if(pMbxTbl->pFnCallBack) {
                g_stxMbxMntn.stNumber.ulPsComPsNotifyNum++;
                g_stxMbxMntn.stCallback.ulSlice[g_stxMbxMntn.stCallback.ulPtr] = bsp_get_slice_value();
                g_stxMbxMntn.stCallback.ulPtr = (g_stxMbxMntn.stCallback.ulPtr+1)%MAILBOX_MNTN_NUMBER;

                enType = g_stxMbxCtrl.bIsSubFrameInt ? EN_MAILBOX_INT_SUBFRAME : EN_MAILBOX_INT_COM_IPC;
                pMbxTbl->pFnCallBack(enType);
         }

        /* PSԭ���Ѿ�������ص����˴���Ҫ�ж��Ƿ�������ԭ�� */
        if((0 != len) && ((u16)MBX_ADDRESSER_LTE_PHY_RL != mod) && ((u16)MBX_ADDRESSER_TDS_PHY_RL != mod)) {
            ulChn = xmbx_GetChn(mod);
            if(EN_MAILBOX_SERVICE_TOTAL_BUTT == ulChn) {
                /* DSPд���˷Ƿ���MOD�������ֳ������� */
                xMbx_SystemError(MBX_ERROR_DL_MOD, g_stxMbxCtrl.ulMsgLen, (u32)mod, (u32)len); /* [false alarm]:fortify */
                return ;
            }
         }

    return;
    }
}

/*****************************************************************************
 Prototype       : xMbx_ComPsIntProc
 Description     : PS�����жϴ�����
                   (���DSPд�����ͨ�������ж�֪ͨARM��DSPӦ��֤��ARMδ��������ǰ������)
 param           : None
 Return Value    : None
*****************************************************************************/
void xMbx_ComPsIntProc(void)
{
    g_stxMbxMntn.stNumber.ulComPsIntNum++;

    if(!(g_stxMbxCtrl.bMbxInit))
    {
        g_stxMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return ;
    }

    /* ��¼ʱ�䣬��λ�ж϶�ʧ */
    g_stxMbxMntn.stIntInfo.ulSlice[g_stxMbxMntn.stIntInfo.ulPtr] = bsp_get_slice_value();
    g_stxMbxMntn.stIntInfo.ulPtr = (g_stxMbxMntn.stIntInfo.ulPtr+1)%MAILBOX_MNTN_NUMBER;

    xMbx_ForbidDspSleep();

    /* ���µ�ǰԭ�ﳤ�� */
    xMbx_ComPsPreProc();

    xMbx_AllowDspSleep();

    xMbx_CallBackProc();

    return ;
}

/*****************************************************************************
 Prototype       : BSP_xMailBox_IsDspSleep
 Description     : DSP�Ƿ�˯��
 param           : None
 Return Value    : 0 --- δ˯��; 1 --- ˯��
*****************************************************************************/
u32 BSP_xMailBox_IsDspSleep(void)
{
    /* DSPδ˯�� */
    if((NULL != g_stxMbxCtrl.pfnGetDspStatusProc) && (BSP_FALSE == g_stxMbxCtrl.pfnGetDspStatusProc()))
    {
        return BSP_FALSE;
    }

    return BSP_TRUE;
}
/*****************************************************************************
 Prototype       : BSP_xMailBox_Rcm_CallBackReg
 Description     : Rcm �¼��ص�ע��ӿ�
 param           : None
 Return Value    :
*****************************************************************************/
void BSP_xMailBox_Rcm_CallBackReg(BSP_xMBX_RCM_CALLBACK_FUNC pFunc)
{
    g_stxMbxCtrl.pfnRcmNotifyProc = pFunc;
}

/*****************************************************************************
 Prototype       : xMbx_ComOmPreProc
IPC_INT_DSP_PS_MAC_MBX Description     : PS�����Ԥ������(��Ҫ�����Ǹ���PS/
CTBT��Ϣ������Ϣ)
                   1. ��������PS��Ϣ�������PS��Ϣ����
                   2. ��������CT/BT��Ϣ�������PS��Ϣ����
                   3. �������ж��е��ã����ܴ�ӡ��malloc
                   4. DSP��֤�����е�ԭ��δ����ʱ��˯��
 param           : None
 Return Value    : void
*****************************************************************************/
void xMbx_ComOmPreProc()
{
    unsigned long key;
    xMAILBOX_RINGBUFF_STRU* pstComOmUpMail;
	    xMAILBOX_MSG_HAED_STRU *pstMsgHead;
    u32 ulUpWrPtr = 0;

    pstComOmUpMail = (xMAILBOX_RINGBUFF_STRU*)g_stxMbxShareAddr.ulCphyMbxOmDownAddr ;

    /* �����ǰԭ�ﳤ�Ȳ�Ϊ0����ʾ��δ���ߣ�����Ҫ���� */
    if( 0 != g_stxMbxCtrl.ulOmMsgLen )
    {
        return ;
    }

    local_irq_save(key);


    ulUpWrPtr = pstComOmUpMail->ulRbufWrPtr;

    /* ���дָ��Ƿ����������� */
    if(ulUpWrPtr > pstComOmUpMail->ulRbufSize)
    {
        local_irq_restore(key);
        system_error(BSP_MODU_MBX, (int)ulUpWrPtr, (int)pstComOmUpMail->ulRbufRdPtr, (char*)NULL, 0);
        return;
    }

    if(pstComOmUpMail->ulRbufRdPtr == ulUpWrPtr)
    {
        g_stxMbxCtrl.ulOmMsgLen = 0;
    }
    else
    {
        pstMsgHead = (xMAILBOX_MSG_HAED_STRU*) \
            (pstComOmUpMail->ulRbufRdPtr + pstComOmUpMail->pucRbufAddr + MAILBOX_ADDR_OFFSET);
         g_stxMbxCtrl.ulOmMsgLen = (u32)(*(u32*)pstMsgHead);    /* ��16λ��¼mod����16λ��¼���� */  /*lint !e740*/
    }

    local_irq_restore(key);

    return ;
}

void xMbx_MntnRead(void* pData, MAILBOX_SERVICE_TYPE_E enMbxType)
{
    xMAILBOX_MNTN_CNF_STRU *pstCnf = NULL;
    u32 *pluPtr = NULL;

    if(EN_MAILBOX_SERVICE_XSYS_RL == enMbxType)
    {
        pstCnf = &(g_stxMbxMntn.stCnfInfo.astPsCnf[g_stxMbxMntn.stCnfInfo.ulPsPtr]);

        pluPtr = &(g_stxMbxMntn.stCnfInfo.ulPsPtr);
    }
    else if (EN_MAILBOX_SERVICE_XSYS_OM == enMbxType)
    {
        pstCnf = &(g_stxMbxMntn.stCnfInfo.astOmCnf[g_stxMbxMntn.stCnfInfo.ulOmPtr]);

        pluPtr = &(g_stxMbxMntn.stCnfInfo.ulOmPtr);
    }
    else
    {
        pstCnf = &(g_stxMbxMntn.stCnfInfo.astCbtCnf[g_stxMbxMntn.stCnfInfo.ulCbtPtr]);

        pluPtr = &(g_stxMbxMntn.stCnfInfo.ulCbtPtr);
    }

    pstCnf->ulMsgId = *(u32*)pData;
    pstCnf->ulSlice = bsp_get_slice_value();

    *pluPtr = (*pluPtr+1)%MAILBOX_MNTN_NUMBER;
}

/*****************************************************************************
 Prototype       : xMailbox_OmMsgRead
 Description     : Omԭ����ӿ�
                   (�˽ӿ��ڲ�����)
 param           : pData        ���յ����ݻ�����ָ��(�洢ԭ����Ϣ��������ԭ�ﳤ��)
                   ulLen        pData��������size(���ֽ�Ϊ��λ)
 Return Value    : 0 : �ɹ�
                   ���� : ʧ��
*****************************************************************************/
u32 xMailbox_OmMsgRead(void* pData, u32 ulLen)
{
    unsigned long key;
    u32 ret;

    xMAILBOX_MSG_HAED_STRU stBuffer = {0};
    xMAILBOX_RINGBUFF_STRU* pstComOmDownMail;

    pstComOmDownMail = (xMAILBOX_RINGBUFF_STRU*)g_stxMbxShareAddr.ulCphyMbxOmDownAddr ;

    if(ulLen != g_stxMbxCtrl.ulOmMsgLen)
    {
        xMbx_Printf(" ulLen(%d) != g_stxMbxCtrl.ulOmMsgLen(%d).\n",
            ulLen, g_stxMbxCtrl.ulOmMsgLen);

        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    stBuffer.usMsgSize = (u16)ulLen;  /* for compare with actually length */
    stBuffer.pPayload = pData;

    local_irq_save(key);
    ret = xMbx_NewMsgReadOut(&stBuffer, pstComOmDownMail);
    local_irq_restore(key);

    if(stBuffer.usMsgSize != g_stxMbxCtrl.ulOmMsgLen)
    {
        xMbx_Printf("pBuffer->usMsgSize(%d) != g_stxMbxCtrl.ulOmMsgLen(%d).\n",
            stBuffer.usMsgSize, g_stxMbxCtrl.ulOmMsgLen);

        ret = ERR_MAILBOX_READ_FAILED;
    }
    else if( MBX_ADDRESSER_XSYS_PHY_OM != stBuffer.usDstMod )
    {
        xMbx_Printf("pBuffer->usDstMod %d.\n",
            stBuffer.usDstMod);

        ret = ERR_MAILBOX_READ_FAILED;
    }
    else
    {
        g_stxMbxMntn.stNumber.ulOmComOmRdOKNum++;

        ret = BSP_OK;
    }

    xMbx_MntnRead(pData, EN_MAILBOX_SERVICE_XSYS_OM);

    /* ��ȡ�ɹ���ѳ������㣬�����´ζ�ȡ */
    local_irq_save(key);
    g_stxMbxCtrl.ulOmMsgLen = 0;
    local_irq_restore(key);

    /* ����g_stxMbxCtrl.ulOmMsgLen */
    xMbx_ComOmPreProc();

    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}

#endif
#endif




/* end C file */

