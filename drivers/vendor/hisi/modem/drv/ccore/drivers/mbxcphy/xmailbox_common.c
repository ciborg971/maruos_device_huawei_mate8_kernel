
/*lint --e{801}*/ /*PCLINT: goto's warning 801 is inevitable*/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "xmailbox.h"
#include <mdrv_timer.h>
#include "bsp_hardtimer.h"
#include "bsp_ipc.h"
#include "mdrv_dsp.h"

#define MBX_PRINT_TIMES     10

/* ����ģ�������Ϣ */
xMAILBOX_MAINCTRL_STRU   g_stxMbxCtrl;
xMAILBOX_MNTN_STRU       g_stxMbxMntn;
xMAILBOX_ADDR_SHARE_STRU g_stxMbxShareAddr;

xMAILBOX_CHANNEL_TABLE_STRU g_astxMbxChnTbl[EN_MAILBOX_SERVICE_TOTAL_BUTT-EN_MAILBOX_SERVICE_BUTT] =
{
	/* cdma���� */
	{EN_MAILBOX_SERVICE_XSYS_RL,     MBX_ADDRESSER_XSYS_PHY_RL,     0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_PUB_MBX},
	{EN_MAILBOX_SERVICE_XSYS_OM,     MBX_ADDRESSER_XSYS_PHY_OM,     0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_OM_MBX },
	{EN_MAILBOX_SERVICE_XSYS_CT,     MBX_ADDRESSER_XSYS_PHY_CT,     0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_PUB_MBX},
	{EN_MAILBOX_SERVICE_XSYS_BT,     MBX_ADDRESSER_XSYS_PHY_BT,     0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_PUB_MBX},
	{EN_MAILBOX_SERVICE_XSYS_HS_DIAG,MBX_ADDRESSER_XSYS_PHY_HS_DIAG,0,   0, NULL,IPC_XDSP_INT_SRC_CCPU_OM_MBX },

};

u32 xmbx_IsChnModMatch(u32 ulChn, u32 ulMod)
{
    xMAILBOX_CHANNEL_TABLE_STRU* pMbxTbl;

    pMbxTbl = xMbx_get_tbl(ulChn);
    if (xMbx_invalid_type(ulChn)) {
        xMbx_Printf("invalid Channel %d.\n", ulChn);
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    switch(ulChn)
    {
        case EN_MAILBOX_SERVICE_XSYS_RL:
        case EN_MAILBOX_SERVICE_XSYS_OM:
        {
            if((MBX_ADDRESSER_XSYS_PHY_RL == ulMod)||(MBX_ADDRESSER_XSYS_PHY_OM == ulMod))
            {
                return BSP_OK;
            }
            break;
        }

        case EN_MAILBOX_SERVICE_XSYS_CT:
        case EN_MAILBOX_SERVICE_XSYS_BT:
        {
            if((MBX_ADDRESSER_XSYS_PHY_CT == ulMod)||(MBX_ADDRESSER_XSYS_PHY_BT == ulMod))
            {
                return BSP_OK;
            }
            break;
        }

        default :
        {
            pMbxTbl = xMbx_get_tbl(ulChn);
            if (pMbxTbl->ulModule == ulMod)
            {
                return BSP_OK;
            }
        }
    }
    return ERR_MAILBOX_PARAM_INCORRECT;
}

u32 xmbx_GetChn(u32 ulMod)
{
    u32 i;
    xMAILBOX_CHANNEL_TABLE_STRU* pMbxTbl;

    if (xMbx_invalid_module(ulMod)) {
        return (u32)EN_MAILBOX_SERVICE_TOTAL_BUTT;
    }
        
    for(i = 0; i < EN_MAILBOX_SERVICE_TOTAL_BUTT - EN_MAILBOX_SERVICE_BUTT; i++)
    {
        pMbxTbl = xMbx_get_tbl(i + EN_MAILBOX_SERVICE_BUTT);
        if(ulMod == pMbxTbl->ulModule)
        {
            return pMbxTbl->ulMbxChn;
        }
    }

    return (u32)EN_MAILBOX_SERVICE_TOTAL_BUTT;
}

/*****************************************************************************
 �� �� ��  : xmbx_mntnaddr
 ��������  : �����ַ�����Ϣ
*****************************************************************************/
void xmbx_mntnaddr(void)
{
    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("��ַ��Ϣ\n");
    xMbx_Printf("CPHY PS���������ַ                : %p.\n", (void*)g_stxMbxShareAddr.ulCphyMbxHpaDownAddr);
    xMbx_Printf("CPHY PS���������ַ                : %p.\n", (void*)g_stxMbxShareAddr.ulCphyMbxHpaUpAddr);
    xMbx_Printf("CPHY OM���������ַ                : %p.\n", (void*)g_stxMbxShareAddr.ulCphyMbxOmDownAddr);
    xMbx_Printf("CPHY DSP���ֵ�ַ                   : %p.\n", (void*)g_stxMbxShareAddr.ulCphyMbxLoadMemAddr);
    xMbx_Printf("CPHY ģʽ���õ�ַ                  : %p.\n", (void*)g_stxMbxShareAddr.ulCphyMbxWorkModeAddr);
    xMbx_Printf("CPHY pCphyMntnInfoAddr            : %p.\n", (void*)g_stxMbxShareAddr.pCphyMntnInfoAddr);
    xMbx_Printf("CPHY pCphyWakeupAddr               : %p.\n", (void*)g_stxMbxShareAddr.pCphyWakeupAddr);

    xMbx_Printf("***************************************************************\n");
}

/*****************************************************************************
 �� �� ��  : xmbx_mntnabnormal
 ��������  : �����쳣��Ϣ
*****************************************************************************/
void xmbx_mntnabnormal(void)
{
    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("�쳣��Ϣ\n");
    xMbx_Printf("PS���������ϱ���CT/BT��ϢID   : %d\n", g_stxMbxMntn.stAbnormal.ulMulCtBtMsg);
    xMbx_Printf("PS�����ϱ��Ĵ����ģ��ID      : %d\n", g_stxMbxMntn.stAbnormal.ucComPsType);
    xMbx_Printf("����������ʱʱ��        : %d\n", g_stxMbxMntn.stAbnormal.ulLongestReq);
    xMbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 �� �� ��  : xmbx_mntnother
 ��������  : ����������ά�ɲ���Ϣ
*****************************************************************************/
void xmbx_mntnother(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("������Ϣ\n");
    xMbx_Printf("PS�����Ƿ���֡�ж�  : %s\n", (g_stxMbxCtrl.bIsSubFrameInt)?"yes":"no");
    xMbx_Printf("PS���䵱ǰ��Ϣ����  : %d\n", g_stxMbxCtrl.ulMsgLen);

    xMbx_Printf("���ʮ�ε͹��Ļ���ʱ����Ϣ\n");

    ulStart = (g_stxMbxMntn.stSleepInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stSleepInfo.astwakeup[j].ulSlice1)
        {
            xMbx_Printf("| slice1(0x%08x) - slice2(0x%08x) | = (0x%08x)   slice3 : 0x%08x\n",
                g_stxMbxMntn.stSleepInfo.astwakeup[j].ulSlice1,
                g_stxMbxMntn.stSleepInfo.astwakeup[j].ulSlice2,
                (g_stxMbxMntn.stSleepInfo.astwakeup[j].ulSlice2 - g_stxMbxMntn.stSleepInfo.astwakeup[j].ulSlice1),
                g_stxMbxMntn.stSleepInfo.astwakeup[j].ulSlice3);
        }
    }

    xMbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 �� �� ��  : xmbx_mntnnum
 ��������  : ���������¼�����Ϣ
*****************************************************************************/
void xmbx_mntnnum(void)
{
    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("������Ϣ\n");
    xMbx_Printf("PS�����жϴ���           : %d\n", g_stxMbxMntn.stNumber.ulComPsIntNum);
    xMbx_Printf("ר�������жϴ���         : %d\n", g_stxMbxMntn.stNumber.ulSpIntNum);

    xMbx_Printf("PS����д�������         : %d\n", g_stxMbxMntn.stNumber.ulPsComReqNum);
    xMbx_Printf("PS����PSд�������       : %d\n", g_stxMbxMntn.stNumber.ulPsComPsReqNum);
    xMbx_Printf("PS����MSPд�������      : %d\n", g_stxMbxMntn.stNumber.ulPsComMspReqNum);
    xMbx_Printf("PS����RttAgentд������� : %d\n", g_stxMbxMntn.stNumber.ulPsComRttAgentReqNum);
    xMbx_Printf("OM����д�������         : %d\n", g_stxMbxMntn.stNumber.ulOmComReqNum);

    xMbx_Printf("PS����PS��ȡ����         : %d\n", g_stxMbxMntn.stNumber.ulPsComPsRdNum);
    xMbx_Printf("PS��ȡ�ɹ�����           : %d\n", g_stxMbxMntn.stNumber.ulPsComPsRdOKNum);
    xMbx_Printf("MSP��ȡ����              : %d\n", g_stxMbxMntn.stNumber.ulPsComMspRdNum);
    xMbx_Printf("MSP��ȡ�ɹ�����          : %d\n", g_stxMbxMntn.stNumber.ulPsComMspRdOKNum);
    xMbx_Printf("RCM��ȡ����              : %d\n", g_stxMbxMntn.stNumber.ulPsComRcmRdNum);
    xMbx_Printf("RCM��ȡ�ɹ�����          : %d\n", g_stxMbxMntn.stNumber.ulPsComRcmRdOKNum);
    xMbx_Printf("RttAgent��ȡ����         : %d\n", g_stxMbxMntn.stNumber.ulPsComRttAgentRdNum);
    xMbx_Printf("RttAgent��ȡ�ɹ�����     : %d\n", g_stxMbxMntn.stNumber.ulPsComRttAgentRdOKNum);

    xMbx_Printf("PS����PS�ص�����         : %d\n", g_stxMbxMntn.stNumber.ulPsComPsNotifyNum);
    xMbx_Printf("PS����MSP�ص�����        : %d\n", g_stxMbxMntn.stNumber.ulPsComMspNotifyNum);
    xMbx_Printf("PS����RCM�ص�����        : %d\n", g_stxMbxMntn.stNumber.ulPsComRcmNotifyNum);
    xMbx_Printf("PS����RttAgent�ص�����   : %d\n", g_stxMbxMntn.stNumber.ulPsComRttAgentNotifyNum);

    xMbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 �� �� ��  : xmbx_mntnmailfull
 ��������  : ������д�붪ʧ��Ϣ
*****************************************************************************/
void xmbx_mntnmailfull(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    ulStart = g_stxMbxMntn.stMailFull.ulPtr;

    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("��������Ϣ\n");
    xMbx_Printf("����������          : %d\n", g_stxMbxMntn.stMailFull.ulFullNum);

    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stMailFull.astFullInfo[j].ulSlice)
        {
            xMbx_Printf("���� : %d   ��ϢID : 0x%08x   ʱ�� : 0x%08x\n",
                g_stxMbxMntn.stMailFull.astFullInfo[j].ulModId
                , g_stxMbxMntn.stMailFull.astFullInfo[j].ulMsgId
                , g_stxMbxMntn.stMailFull.astFullInfo[j].ulSlice);
        }
    }

    xMbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 �� �� ��  : xmbx_mntnreqinfo
 ��������  : ����д������Ϣ
*****************************************************************************/
void xmbx_mntnreqinfo(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("����д������Ϣ\n");

    ulStart = (g_stxMbxMntn.stReqInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stReqInfo.astReq[j].ulSliceEnd)
        {
            xMbx_Printf("���� : %d   ��ϢID : 0x%08x   ����ʱ�� : 0x%08x   д��ʱ�� : 0x%08x\n",
                g_stxMbxMntn.stReqInfo.astReq[j].ulModId, g_stxMbxMntn.stReqInfo.astReq[j].ulMsgId,
                g_stxMbxMntn.stReqInfo.astReq[j].ulSliceStart, g_stxMbxMntn.stReqInfo.astReq[j].ulSliceEnd);
        }
    }

    xMbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 �� �� ��  : xmbx_mntncnfinfo
 ��������  : �����������Ϣ
*****************************************************************************/
void xmbx_mntncnfinfo(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    xMbx_Printf("***************************************************************\n");

    xMbx_Printf("���ʮ�θ����жϵ���Ϣ\n");

    ulStart = (g_stxMbxMntn.stIntInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stIntInfo.ulSlice[j])
        {
            xMbx_Printf("interrupt slice : 0x%08x\n", g_stxMbxMntn.stIntInfo.ulSlice[j]);
        }
    }

    xMbx_Printf("���ʮ��ԭ���ȡ����Ϣ\n");

    ulStart = (g_stxMbxMntn.stReadInfo.ulPsPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stReadInfo.astRead[j].ulSlice)
        {
            xMbx_Printf("app read , src 0x%x, slice 0x%08x\n",
                g_stxMbxMntn.stReadInfo.astRead[j].ulSrc, g_stxMbxMntn.stReadInfo.astRead[j].ulSlice);
        }
    }

    ulStart = (g_stxMbxMntn.stCnfInfo.ulPsPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    xMbx_Printf("����PS���10����������Ϣ\n");

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stCnfInfo.astPsCnf[j].ulSlice)
        {
            xMbx_Printf("��ϢID : 0x%08x   ��ȡʱ�� : 0x%08x\n",
                g_stxMbxMntn.stCnfInfo.astPsCnf[j].ulMsgId, g_stxMbxMntn.stCnfInfo.astPsCnf[j].ulSlice);
        }
    }

    ulStart = (g_stxMbxMntn.stCnfInfo.ulRcmPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;
    xMbx_Printf("����RCM���10����������Ϣ\n");
    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;
        if(0 != g_stxMbxMntn.stCnfInfo.astRcmCnf[j].ulSlice)
        {
            xMbx_Printf("��ϢID : 0x%08x   ��ȡʱ�� : 0x%08x\n",
                g_stxMbxMntn.stCnfInfo.astRcmCnf[j].ulMsgId, g_stxMbxMntn.stCnfInfo.astRcmCnf[j].ulSlice);
        }
    }
    ulStart = (g_stxMbxMntn.stCnfInfo.ulCbtPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    xMbx_Printf("����CT/BT���10����������Ϣ\n");

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stCnfInfo.astCbtCnf[j].ulSlice)
        {
            xMbx_Printf("��ϢID : 0x%08x   ��ȡʱ�� : 0x%08x\n",
                g_stxMbxMntn.stCnfInfo.astCbtCnf[j].ulMsgId, g_stxMbxMntn.stCnfInfo.astCbtCnf[j].ulSlice);
        }
    }

    xMbx_Printf("����Rtt Agent���10����������Ϣ\n");

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stxMbxMntn.stCnfInfo.astRttAgentCnf[j].ulSlice)
        {
            xMbx_Printf("��ϢID : 0x%08x   ��ȡʱ�� : 0x%08x\n",
                g_stxMbxMntn.stCnfInfo.astRttAgentCnf[j].ulMsgId, g_stxMbxMntn.stCnfInfo.astRttAgentCnf[j].ulSlice);
        }
    }

    xMbx_Printf("***************************************************************\n");
}

void xmbx_mntnSleepCbInfo(void)
{
    u32 i =0,j=0;
    for(i=0; i<MAILBOX_MNTN_NUMBER; i++)
    {
        j = (g_stxMbxMntn.stSleepCbInfo.ulPtr+i)%MAILBOX_MNTN_NUMBER;
        if(0 != g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceStart)
        {
            xMbx_Printf("Callback Type : %d, Is Mbx wakeup :%d, end time(0x%08x) - start time(0x%08x) = %d  MS\n",
                g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].cbType,g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].ulWakeup,\
                g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceEnd,g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceStart,\
                ((g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceEnd-g_stxMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceStart)/32));
        }
    }
}

void xmbx_mntnDirectWriteInfo(void)
{
    u32 i = 0 ,k = 0;
    u32 j = g_stxMbxMntn.stDirectInfo.ulPtr % MAILBOX_MNTN_NUMBER;
    xMbx_Printf("*************Direct Num 0x%x****************\n",g_stxMbxMntn.stDirectInfo.ulPtr);
    xMbx_Printf("*************print lastest *****************\n");
    for(i = 0;i < MAILBOX_MNTN_NUMBER;i++)
    {
        k = (j+1)%MAILBOX_MNTN_NUMBER;
        if(0 != g_stxMbxMntn.stDirectInfo.ulSlice[k])
        {
            xMbx_Printf("�� %d �Σ�ʱ���Ϊ :0x%x\n",i,g_stxMbxMntn.stDirectInfo.ulSlice[k]);
        }
    }
}
/*****************************************************************************
 �� �� ��  : xmbx_mntnerrorcode
 ��������  : ��������������Ϣ
*****************************************************************************/
void xmbx_mntnerrorcode(void)
{
    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("��������Ϣ\n");
    xMbx_Printf("1  : ����δ��ʼ��.\n");
    xMbx_Printf("2  : �����������.\n");
    xMbx_Printf("3  : ������.\n");
    xMbx_Printf("4  : ��ʱ.\n");
    xMbx_Printf("5  : ר���������ݸ���.\n");
    xMbx_Printf("6  : дʧ��.\n");
    xMbx_Printf("7  : ��ʧ��.\n");
    xMbx_Printf("8  : ����ϢΪ��.\n");
    xMbx_Printf("9  : DSP˯��.\n");
    xMbx_Printf("10 : ����.\n");
    xMbx_Printf("***************************************************************\n");
}


void xmbx_debug(BSP_BOOL bDebug)
{
    g_stxMbxMntn.bdbg = bDebug;
}

/*****************************************************************************
 �� �� ��  : xmailbox_help
 ��������  : �����ӡ����
*****************************************************************************/
void xmailbox_help(void)
{
    xMbx_Printf("***************************************************************\n");
    xMbx_Printf("�����ַ�����Ϣ                xmbx_mntnaddr\n");
    xMbx_Printf("���������¼�����Ϣ            xmbx_mntnnum\n");
    xMbx_Printf("����д������Ϣ                  xmbx_mntnreqinfo\n");
    xMbx_Printf("�����������Ϣ                  xmbx_mntncnfinfo\n");
    xMbx_Printf("������д�붪ʧ��Ϣ              xmbx_mntnmailfull\n");
    xMbx_Printf("�����쳣��Ϣ                    xmbx_mntnabnormal\n");
    xMbx_Printf("����������ά�ɲ���Ϣ            xmbx_mntnother\n");
    xMbx_Printf("�������ʧ�ܴ�������Ϣ          xmbx_mntnerrorcode\n");
    xMbx_Printf("�����ӡ��Ϣ����                xmbx_debug 1/0\n");
    xMbx_Printf("����SLEEP�ص���Ϣ               xmbx_mntnSleepCbInfo\n");
    xMbx_Printf("����ֱ��д��Ϣ                  xmbx_mntnDirectWriteInfo\n");
    xMbx_Printf("***************************************************************\n");
}


/*lint -save -e545 -e813*/
/*****************************************************************************
 Prototype       : xMbx_BbeIpcProc
 Description     : ������쳣����
                   BBE�����쳣ʱ�������쳣��Ϣ��AXI memory�У�Ȼ��ͨ��IPC�ж�
                   ֪ͨ����ģ�飬������ģ���¼�쳣��Ϣ���������쳣�����ӿ�
 Return Value    : NONE
*****************************************************************************/
void xMbx_BbeIpcProc(void)
{
    u8  ucData[MBX_SYSTEM_ERROR_SIZE] = {0};     /* 4K���棬ǰ32�ֽڴ�DSP��Ϣ */
    u32 *pAddr;
    u16 usMode;

    usMode = *(u16*)g_stxMbxShareAddr.pCphyMntnInfoAddr ;

    /* 0��ʾPS������ */
    if(0 == usMode)
    {
        /* ǰ4���ֱ��洫��Ĳ��� */
        pAddr = (u32*)ucData;

        *(pAddr++) = MBX_ERROR_DSP_IPC;
        *(pAddr++) = 0;
        *(pAddr++) = 0;
        *(pAddr++) = 0;

        /* ����DSP���쳣��Ϣ */
        xMbx_Memcpy((u8*)pAddr, (u8*)g_stxMbxShareAddr.pCphyMntnInfoAddr, SRAM_CDSP_MNTN_SIZE); /* [false alarm]:fortify */

        /* �ӵ�512�ֽڿ�ʼ���������������쳣��Ϣ */
        xMbx_DumpSave(ucData+MBX_ERROR_RESERVE_SIZE, (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE));

        system_error(DRV_ERRNO_MBX_DSP_IPC, MBX_ERROR_DSP_IPC, 0, (char*)ucData, MBX_SYSTEM_ERROR_SIZE);
    }
}
/*lint -restore*/

/*****************************************************************************
 �� �� ��  : bsp_xmailbox_init
 ��������  : ����ģ���ʼ��
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
void bsp_xmailbox_init(void)
{
    s32 ret;
    SRAM_SMALL_SECTIONS * pSram_Small_section;

    xMbx_Memset(&g_stxMbxCtrl, 0, sizeof(xMAILBOX_MAINCTRL_STRU));

    xMbx_Memset((void*)(&g_stxMbxMntn), 0, sizeof(xMAILBOX_MNTN_STRU));

    g_stxMbxCtrl.bDspWakeFlag = BSP_FALSE;

    osl_sem_init(0, &g_stxMbxCtrl.semDspWakeup);
    osl_sem_init(1, &g_stxMbxCtrl.semDspMutex);

    pSram_Small_section = (SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS);
    g_stxMbxShareAddr.pCphyMntnInfoAddr = pSram_Small_section->SRAM_CDSP_MNTN_INFO;
    g_stxMbxShareAddr.pCphyWakeupAddr = (void *)&pSram_Small_section->SRAM_CDSP_DRV;

    g_stxMbxCtrl.pulAxiAddr = (u32*)g_stxMbxShareAddr.pCphyWakeupAddr;
    g_stxMbxCtrl.lAxiCnt = 0;

    ret = (s32)bsp_ipc_int_connect(IPC_CCPU_INT_SRC_XDSP_PS_MBX, (VOIDFUNCPTR)xMbx_ComPsIntProc, 0);
	if(BSP_OK != ret)
	{
        xMbx_Printf("bsp_ipc_int_connect failed.\n");
        return ;
	}

    ret = (s32)bsp_ipc_int_enable(IPC_CCPU_INT_SRC_XDSP_PS_MBX);
	if(BSP_OK != ret)
	{
        xMbx_Printf("bsp_ipc_int_enable failed.\n");
        return ;
	}

    ret = (s32)bsp_ipc_int_connect(IPC_CCPU_INT_SRC_XDSP_RCM_MBX, (VOIDFUNCPTR)xMbx_ComPsIntProc, 0);
    if(BSP_OK != ret)
    {
        xMbx_Printf("bsp_ipc_int_connect failed.\n");
        return ;
    }

    ret = (s32)bsp_ipc_int_enable(IPC_CCPU_INT_SRC_XDSP_RCM_MBX);
    if(BSP_OK != ret)
    {
        xMbx_Printf("bsp_ipc_int_enable failed.\n");
        return ;
    }

    /* DSP��ά�ɲ�IPC�ж� */
    ret = (s32)bsp_ipc_int_connect(IPC_CCPU_INT_SRC_XDSP_MNTN, (VOIDFUNCPTR)xMbx_BbeIpcProc, 0);
    if(BSP_OK != ret)
    {
        xMbx_Printf("bsp_ipc_int_connect failed.\n");
        return ;
    }

    ret = (s32)bsp_ipc_int_enable(IPC_CCPU_INT_SRC_XDSP_MNTN);
    if(BSP_OK != ret)
    {
        xMbx_Printf("bsp_ipc_int_enable failed.\n");
        return ;
    }

    g_stxMbxCtrl.bIsSubFrameInt = BSP_FALSE;

    xMbx_Printf("success.\n");
    return;
}
u32 xMbx_SpaceMalloc(xMAILBOX_RINGBUFF_STRU* pMbxHandle,u32 ulSizeReq)
{
    u32 ulFreeBuffSize;
    u32 wr,rd,size;

    wr   = pMbxHandle->ulRbufWrPtr;
    rd   = pMbxHandle->ulRbufRdPtr;
    size = pMbxHandle->ulRbufSize;

    /* ���дָ��Ƿ����������� */
    if(wr > size)
    {
        xMbx_SystemError((u32)MBX_ERROR_UP_WR, wr, rd, ((__LINE__ << 16)|size));
    }

    if(wr < rd)
    {
        ulFreeBuffSize = (rd - wr);
    }
    else
    {
        ulFreeBuffSize = (size + rd - wr);
    }

    if(ulFreeBuffSize >= (ulSizeReq+4))
    {
        return BSP_OK;
    }
    else
    {
        xMbx_Printf("Mbx_SpaceMalloc failed, ulFreeBuffSize(%d), ulSizeReq(%d), wr(%d), rd(%d), size(%d).\n",
            ulFreeBuffSize, ulSizeReq, wr, rd, size);
        return (u32)BSP_ERROR;
    }
}


void xMbx_MntnMailFull(xMAILBOX_MSG_HAED_STRU* pstMsg)
{
    g_stxMbxMntn.stMailFull.ulFullNum++;

    g_stxMbxMntn.stMailFull.astFullInfo[g_stxMbxMntn.stMailFull.ulPtr].ulModId = (u32)(pstMsg->usDstMod);
    g_stxMbxMntn.stMailFull.astFullInfo[g_stxMbxMntn.stMailFull.ulPtr].ulMsgId = *(u32*)(pstMsg->pPayload);
    g_stxMbxMntn.stMailFull.astFullInfo[g_stxMbxMntn.stMailFull.ulPtr].ulSlice = bsp_get_slice_value();

    g_stxMbxMntn.stMailFull.ulPtr = (g_stxMbxMntn.stMailFull.ulPtr+1)%MAILBOX_MNTN_NUMBER;
}


/*****************************************************************************
 Prototype       : xMbx_RbuffWrite
 Description     : ѭ��bufferд�ӿ�
 param           : pHead        ѭ��buffer���׵�ַ
                   pstMsg       ��д������ָ��
 Return Value    : BSP_OK : �ɹ�
                   ERR_MAILBOX_MEMORY_NOTENOUGH : ʣ��ռ䲻��
*****************************************************************************/
s32 xMbx_RbuffWrite(xMAILBOX_RINGBUFF_STRU* pHead, xMAILBOX_MSG_HAED_STRU* pstMsg)
{
    u32 ulMsgSize = pstMsg->usMsgSize + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4);
    u32 ulCpySize0;
    u32 ulCpySize1;
    u32 ulTempPPTR;

    /* ����ʣ��ռ��� */
    if(BSP_OK != xMbx_SpaceMalloc(pHead,ulMsgSize))
    {
        xMbx_MntnMailFull(pstMsg);
        return ERR_MAILBOX_MEMORY_NOTENOUGH;
    }

    /* ����Ϣд�� */
    if((ulMsgSize + pHead->ulRbufWrPtr) <= pHead->ulRbufSize)
    {
        xMbx_Memcpy((void*)(pHead->ulRbufWrPtr + pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                        (void*)pstMsg,
                        (sizeof(xMAILBOX_MSG_HAED_STRU) - 4));
        xMbx_Memcpy((void*)(pHead->ulRbufWrPtr + pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4)),
                        (void*)(pstMsg->pPayload),
                        pstMsg->usMsgSize);     /*lint !e516*/
    }
    else
    {
        ulCpySize0 = pHead->ulRbufSize - pHead->ulRbufWrPtr;
        ulCpySize1 = ulMsgSize - ulCpySize0;

        if(ulCpySize0 < (sizeof(xMAILBOX_MSG_HAED_STRU) - 4))
        {
            xMbx_Memcpy((void*)(pHead->pucRbufAddr + pHead->ulRbufWrPtr + MAILBOX_ADDR_OFFSET),
                            (void*)pstMsg,
                            ulCpySize0);

            xMbx_Memcpy((void*)(pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                            (void*)((u32)(pstMsg)+ulCpySize0),
                            ((sizeof(xMAILBOX_MSG_HAED_STRU) - 4)-ulCpySize0));

            xMbx_Memcpy((void*)(pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET + ((sizeof(xMAILBOX_MSG_HAED_STRU) - 4)-ulCpySize0)),
                            (void*)(pstMsg->pPayload),
                            pstMsg->usMsgSize);     /*lint !e516*/
        }
        else
        {
            xMbx_Memcpy((void*)(pHead->pucRbufAddr + pHead->ulRbufWrPtr + MAILBOX_ADDR_OFFSET),
                            (void*)(pstMsg),
                            (sizeof(xMAILBOX_MSG_HAED_STRU) - 4));

            xMbx_Memcpy((void*)(pHead->pucRbufAddr + pHead->ulRbufWrPtr + MAILBOX_ADDR_OFFSET + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4)),
                            (void*)(pstMsg->pPayload),
                            (ulCpySize0 - (sizeof(xMAILBOX_MSG_HAED_STRU) - 4)));

            xMbx_Memcpy((void*)(pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                            (void*)((u32)(pstMsg->pPayload) + (ulCpySize0 - (sizeof(xMAILBOX_MSG_HAED_STRU) - 4))),
                            ulCpySize1);
        }
    }

    /* дָ�����,��֤���ֽڶ��� */
    ulTempPPTR = ((pHead->ulRbufWrPtr + ulMsgSize + 3) & (~3));

    if(ulTempPPTR >= pHead->ulRbufSize)
    {
        ulTempPPTR -= pHead->ulRbufSize;
    }

    xMbx_MntnWriteEnd(pHead, pstMsg, ulTempPPTR);

    pHead->ulRbufWrPtr = ulTempPPTR;

    return BSP_OK;
}
u32 xMbx_GetNewMsgLen (xMAILBOX_MSG_HAED_STRU* pMsg)
{
    return(u32)(pMsg->usMsgSize);
}



u32 xMbx_NewMsgReadOut(xMAILBOX_MSG_HAED_STRU* pMsg,xMAILBOX_RINGBUFF_STRU* pMbxHandle)
{
    u32 ulMsgSize;
    u32 ulCpySize0;
    u32 ulCpySize1;
    u32 ulTempCPTR;
    xMAILBOX_MSG_HAED_STRU *pstMsg = NULL;

    pstMsg = (xMAILBOX_MSG_HAED_STRU*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET + pMbxHandle->ulRbufRdPtr);
    ulMsgSize = xMbx_GetNewMsgLen(pstMsg) + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4);

    /* user space not enough, return failure, avoid overflow */
    if(pstMsg->usMsgSize > pMsg->usMsgSize)
    {
        pMsg->usMsgSize = pstMsg->usMsgSize;
        goto newmsgreadfailed;
    }

    /* ����Ϣ���� */
    if((ulMsgSize + pMbxHandle->ulRbufRdPtr) <= pMbxHandle->ulRbufSize)
    {
        xMbx_Memcpy((void*)pMsg,
                (void*)(pMbxHandle->ulRbufRdPtr + pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                (sizeof(xMAILBOX_MSG_HAED_STRU) - 4));

        xMbx_Memcpy((void*)(pMsg->pPayload),
                (void*)(pMbxHandle->ulRbufRdPtr + pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4)),
                pstMsg->usMsgSize);     /*lint !e516*/
    }
    else
    {
        ulCpySize0 = pMbxHandle->ulRbufSize - pMbxHandle->ulRbufRdPtr;
        ulCpySize1 = ulMsgSize - ulCpySize0;

        if(ulCpySize0 < (sizeof(xMAILBOX_MSG_HAED_STRU) - 4))
        {
            xMbx_Memcpy((void*)(pMsg),
                    (void*)(pMbxHandle->pucRbufAddr + pMbxHandle->ulRbufRdPtr + MAILBOX_ADDR_OFFSET),
                    ulCpySize0);

            xMbx_Memcpy((void*)((u32)pMsg + ulCpySize0),
                    (void*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                    (sizeof(xMAILBOX_MSG_HAED_STRU) - 4) - ulCpySize0);

            xMbx_Memcpy((void*)(pMsg->pPayload),
                    (void*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4) - ulCpySize0),
                    pstMsg->usMsgSize);     /*lint !e516*/
        }
        else
        {
            xMbx_Memcpy((void*)(pMsg),
                    (void*)(pMbxHandle->pucRbufAddr + pMbxHandle->ulRbufRdPtr + MAILBOX_ADDR_OFFSET),
                    (sizeof(xMAILBOX_MSG_HAED_STRU) - 4));

            xMbx_Memcpy((void*)(pMsg->pPayload),
                    (void*)(pMbxHandle->pucRbufAddr + pMbxHandle->ulRbufRdPtr + MAILBOX_ADDR_OFFSET + (sizeof(xMAILBOX_MSG_HAED_STRU) - 4)),
                    ulCpySize0 - (sizeof(xMAILBOX_MSG_HAED_STRU) - 4));

            xMbx_Memcpy((void*)((u32)(pMsg->pPayload) + ulCpySize0 - (sizeof(xMAILBOX_MSG_HAED_STRU) - 4)),
                    (void*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                    ulCpySize1);
        }
    }

newmsgreadfailed:

    /* ��ָ�����,��֤���ֽڶ��� */
    ulTempCPTR = ((pMbxHandle->ulRbufRdPtr + ulMsgSize + 3) & (~3));

    if((ulTempCPTR) >= pMbxHandle->ulRbufSize)
    {
        ulTempCPTR -= pMbxHandle->ulRbufSize;
    }

    xMbx_MntnReadEnd(pMsg->pPayload, (enum __MBX_ADDRESSEE_ID_ENUM__)pMsg->usDstMod, ulTempCPTR, pMbxHandle->ulRbufWrPtr);

    pMbxHandle->ulRbufRdPtr = ulTempCPTR;

    return (ulTempCPTR);
}


/*****************************************************************************
 Prototype       : BSP_xMailBox_GetDspStatusReg
 Description     : ��ȡDSP˯��״̬�ص�����ע��ӿڣ��͹���ģ�����
 param           : pFun             ��ȡDSP˯��״̬������
 Return Value    : BSP_VOID
*****************************************************************************/
void BSP_xMailBox_GetDspStatusReg(BSP_MBX_GET_STATUS_FUNC pFun)
{
    g_stxMbxCtrl.pfnGetDspStatusProc = pFun;
}


/*****************************************************************************
 Prototype       : BSP_xMailBox_DspForceAwakeReg
 Description     : DSPǿ�ƻ��ѻص�����ע��ӿڣ��͹���ģ�����
 param           : pFun             DSPǿ�ƻ��Ѵ�����
 Return Value    : BSP_VOID
*****************************************************************************/
void BSP_xMailBox_DspForceAwakeReg(BSP_xMBX_DSP_AWAKE_FUNC pFun)
{
    g_stxMbxCtrl.pfnDspForceAwakeProc = pFun;
}


/*****************************************************************************
 Prototype       : BSP_xMailBox_GetSpMsgStatusReg
 Description     : ��ȡר����������DSP˯��״̬�ص�����ע��ӿڣ�PS����
 param           : pFun             ��ȡDSP˯��״̬������
 Return Value    : BSP_VOID
*****************************************************************************/
void BSP_xMailBox_GetSpMsgStatusReg(BSP_MBX_GET_STATUS_FUNC pFun)
{
    g_stxMbxCtrl.pfnGetSpMsgProc = pFun;
}


/*****************************************************************************
 Prototype       : BSP_xMailBox_DspAwakeProc
 Description     : DSP���Ѻ�����䴦��ӿڣ��͹���ģ�����
 param           : BSP_VOID
 Return Value    : BSP_VOID
*****************************************************************************/
void BSP_xMailBox_DspAwakeProc(MAILBOX_CALLBACK_TYPE cbType)
{
    u32 ulPtr = g_stxMbxMntn.stSleepCbInfo.ulPtr;
    g_stxMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].cbType       = cbType;
    if(cbType >= EN_MAILBOX_CALLBACK_DSP_BUTT)
    {
        xMbx_Printf("err parm ! %d \n",cbType);
        cbType = EN_MAILBOX_CALLBACK_DSP_BUTT;
    }
    if(g_stxMbxCtrl.pfnRcmNotifyProc)
    {
        g_stxMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].ulWakeup     = g_stxMbxCtrl.bDspWakeFlag;

        g_stxMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].ulSliceStart = bsp_get_slice_value();
        g_stxMbxCtrl.pfnRcmNotifyProc(cbType);

        g_stxMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].ulSliceEnd   = bsp_get_slice_value();

        ulPtr = g_stxMbxMntn.stSleepCbInfo.ulPtr +1;

        g_stxMbxMntn.stSleepCbInfo.ulPtr = ulPtr%MAILBOX_MNTN_NUMBER;
    }
    /* ֻ��������ģ�鷢��Ļ��� */
    if(BSP_TRUE == g_stxMbxCtrl.bDspWakeFlag)
    {
        g_stxMbxMntn.stSleepInfo.astwakeup[g_stxMbxMntn.stSleepInfo.ulPtr].ulSlice2 = bsp_get_slice_value();
        g_stxMbxCtrl.bDspWakeFlag = BSP_FALSE;
        osl_sem_up(&g_stxMbxCtrl.semDspWakeup);
    }
}


/*****************************************************************************
 Prototype       : BSP_xMailBox_IsAllowDspSleep
 Description     : ��ѯ�Ƿ�����DSP˯�ߵĴ���ӿڣ��͹���ģ�����
                    ���ô˽ӿ�ʱ�͹���ģ�鱣֤DSPδ˯��
                    �˽ӿ�ֻ���PS�����ר�����䣬�����OM����(OMԭ����ʱ��Ҫ��)
 param           : BSP_VOID
 Return Value    : BSP_BOOL: TRUE-allow;FALSE-forbid
*****************************************************************************/
int BSP_xMailBox_IsAllowDspSleep(void)
{
    BSP_BOOL bFlag;
    xMAILBOX_RINGBUFF_STRU* pstComPsUpMail   = (xMAILBOX_RINGBUFF_STRU*)g_stxMbxShareAddr.ulCphyMbxHpaUpAddr;
    xMAILBOX_RINGBUFF_STRU* pstComPsDownMail = (xMAILBOX_RINGBUFF_STRU*)g_stxMbxShareAddr.ulCphyMbxHpaDownAddr;
    xMAILBOX_RINGBUFF_STRU* pstOmDownMail    = (xMAILBOX_RINGBUFF_STRU*)g_stxMbxShareAddr.ulCphyMbxOmDownAddr;

    if(!(g_stxMbxCtrl.bMbxInit))
    {
        g_stxMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return BSP_TRUE;
    }

    /* ��һ���ȼ��Ȳ�AXI memory��AXI memory����ʱ������DSP˯�� */
    if(*(g_stxMbxCtrl.pulAxiAddr) == 1)
    {
        return BSP_FALSE;
    }

    /* ר��������ԭ��δ���߽�ֹ˯�� */
    if(NULL != g_stxMbxCtrl.pfnGetSpMsgProc)
    {
        bFlag = g_stxMbxCtrl.pfnGetSpMsgProc();
        if(BSP_TRUE != bFlag)
        {
            return bFlag;
        }
    }

    /* PS������ԭ��δ���߽�ֹ˯�� */
    if((pstComPsUpMail->ulRbufRdPtr != pstComPsUpMail->ulRbufWrPtr)
        || (pstComPsDownMail->ulRbufRdPtr != pstComPsDownMail->ulRbufWrPtr)
        || (pstOmDownMail->ulRbufRdPtr != pstOmDownMail->ulRbufWrPtr))
    {
        return BSP_FALSE;
    }

    return BSP_TRUE;
}


/*****************************************************************************
 Prototype       : BSP_xUniMailboxWrite
 Description     : �����ͨ��д�ӿ�(�ɵ����߱�֤����ĵ�ַ�ĺϷ���)
                   ���ӿ�ʵ������memcpy����������
                   �ӿ��ڲ���֤DSP�Ļ��Ѳ������������ʧ�ܣ�����ERR_MAILBOX_TIMEOUT
 Return Value    :
                   BSP_OK
                   ERR_MAILBOX_PARAM_INCORRECT
                   ERR_MAILBOX_TIMEOUT
*****************************************************************************/
unsigned int BSP_xUniMailboxWrite(void *pDst, void *pSrc, unsigned int ulLen)
{
    u32 ulret;

    if((NULL == pDst) || (NULL == pSrc) || (0 == ulLen))
    {
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    ulret = BSP_Mailbox_ForbidDspSleep(EN_MAILBOX_SLEEP_WAKEUP);
    if(ulret)
    {
        return ulret;
    }

    xMbx_Memcpy(pDst, pSrc, ulLen);

    BSP_Mailbox_AllowDspSleep();

    return BSP_OK;
}


/*****************************************************************************
 Prototype       : BSP_xMailboxAbnormalProc
 Description     : �����쳣����
                   Э��ջ������Ϣ��ʱ����ô˽ӿڱ������������Ϣ
                   ��Э��ջ�̶���ǰ0.5K����Э��ջ��Ϣ����3.5K����������Ϣ
 Input           : ucData       �����׵�ַ
 Return Value    : NONE
*****************************************************************************/
void BSP_xMailboxAbnormalProc(unsigned char *ucData)
{
    if(BSP_NULL == ucData)
    {
        return;
    }

    xMbx_Printf("enter.\n");

    xMbx_DumpSave(ucData, (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE));

    xMbx_Printf("exit.\n");
}


/*****************************************************************************
 Prototype       : xMbx_DumpSave
 Description     : �����쳣������Ϣ����ӿ�
                    ��¼���е�������Ϣ
                    ��¼���еĶ�ȡ���󡢶�ȡ�����Ϣ
                    ��¼���һ��DSP IPC�ж��ϱ���ʱ��
                    ��¼����DSP��ʱ����Ϣ
 Input           :  pData ��������ʼ��ַ
                    ulSize ��������С
 Return Value    : NONE
*****************************************************************************/
void xMbx_DumpSave(u8* pData, u32 ulSize)
{
    u32 i,ptr;
    u32 ultmp = 0;

    /* ����Ŀռ��С��С3.5K */
    if((ulSize < (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE)) || (NULL == pData))
    {
        xMbx_Printf("ulSize %d, pData %p.\n", ulSize, pData);
        return;
    }

    ptr = g_stxMbxMntn.stReqInfo.ulPtr;
    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        /* (msg ID/RWpointer/start slice/end slice) */
        xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stReqInfo.astReq[ptr].ulMsgId), 4*sizeof(u32)); /*lint !e420*/ /* [false alarm]:fortify */
        ultmp += 4*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 1600 */
    xMbx_Printf("ultmp = %d.\n", ultmp);

    ptr = g_stxMbxMntn.stCnfInfo.ulPsPtr;
    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        /* (msg ID/slice) */
        xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stCnfInfo.astPsCnf[ptr]), 2*sizeof(u32));
        ultmp += 2*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 2400 */
    xMbx_Printf("ultmp = %d.\n", ultmp);

    ptr = g_stxMbxMntn.stReadInfo.ulPsPtr;
    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        /* (read src/slice) */
        xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stReadInfo.astRead[ptr]), 2*sizeof(u32));
        ultmp += 2*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 3200 */
    xMbx_Printf("ultmp = %d.\n", ultmp);

    /* �ռ����ޣ�ֻ��¼���ʮ�εĻ�����Ϣ */
    ptr = (g_stxMbxMntn.stSleepInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_ERROR_MNTN_NUM)%MAILBOX_MNTN_NUMBER;
    for(i = 0; i < MBX_ERROR_MNTN_NUM; i++)
    {
        /* (req slice/callback slice/proc slice) */
        xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stSleepInfo.astwakeup[ptr]), 3*sizeof(u32));
        ultmp += 3*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 3320 */
    xMbx_Printf("ultmp = %d.\n", ultmp);

    /* �ռ����ޣ�ֻ��¼���ʮ�ε�IPCʱ����Ϣ */
    ptr = (g_stxMbxMntn.stCallback.ulPtr + MAILBOX_MNTN_NUMBER - MBX_ERROR_MNTN_NUM)%MAILBOX_MNTN_NUMBER;
    for(i = 0; i < MBX_ERROR_MNTN_NUM; i++)
    {
        /* (callback timer) */
        xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stCallback.ulSlice[ptr]), sizeof(u32));
        ultmp += sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 3360 */
    xMbx_Printf("ultmp = %d.\n", ultmp);

    xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stNumber), sizeof(g_stxMbxMntn.stNumber));
    ultmp += sizeof(g_stxMbxMntn.stNumber);

    /* ultmp value is 3408 */

    xMbx_Printf("ultmp = %d.\n", ultmp);

    xMbx_Memcpy(&pData[ultmp], (u8*)&(g_stxMbxMntn.stAbnormal), sizeof(g_stxMbxMntn.stAbnormal));
    ultmp += sizeof(g_stxMbxMntn.stAbnormal);

    /* ultmp value is 3424 */
    xMbx_Printf("ultmp = %d.\n", ultmp);

    /* �����32���ֽڱ�������������ͷ��Ϣ */
    if(BSP_OK == BSP_xMailbox_ForbidDspSleep(EN_MAILBOX_SLEEP_WAKEUP))
    {
        xMbx_Memcpy(&pData[ulSize-(2*sizeof(xMAILBOX_RINGBUFF_STRU))],
            (BSP_VOID*)g_stxMbxShareAddr.ulCphyMbxHpaDownAddr, sizeof(xMAILBOX_RINGBUFF_STRU)); /* [false alarm]:fortify */

        xMbx_Memcpy(&pData[ulSize - sizeof(xMAILBOX_RINGBUFF_STRU)],
            (BSP_VOID*)g_stxMbxShareAddr.ulCphyMbxHpaUpAddr, sizeof(xMAILBOX_RINGBUFF_STRU)); /* [false alarm]:fortify */

        BSP_xMailbox_AllowDspSleep();
    }

}


/*****************************************************************************
 Prototype       : xMbx_SystemError
 Description     : �����쳣��������ӿ�
                    ��¼���е�������Ϣ
                    ��¼���еĶ�ȡ���󡢶�ȡ�����Ϣ
                    ��¼���һ��DSP IPC�ж��ϱ���ʱ��
                    ��¼����DSP��ʱ����Ϣ
 Input           : errcode  �����ڲ�������
                   ulPara1,ulPara2,ulPara3   ����1,2,3���쳣�����ֻ�������1
 Return Value    : NONE
*****************************************************************************/
void xMbx_SystemError(u32 errcode, u32 ulPara1, u32 ulPara2, u32 ulPara3)
{
    u8 *pData;
    u32 *pAddr;

    errcode = DRV_ERRNO_XMBX_WR_FULL + errcode;
    pData = osl_malloc(MBX_SYSTEM_ERROR_SIZE);
    if(NULL == pData)
    {
        /* �����������DRV_ERRNO_MBX_WR_FULL��ʼ */
        system_error(errcode, ulPara1, ulPara2, (char*)NULL, 0); /* [false alarm]:fortify */
        return ;
    }
    xMbx_Memset(pData, 0, MBX_SYSTEM_ERROR_SIZE);

    /* ǰ4���ֱ��洫��Ĳ��� */
    pAddr = (u32*)pData;

    *(pAddr++) = errcode;
    *(pAddr++) = ulPara1;
    *(pAddr++) = ulPara2;
    *(pAddr++) = ulPara3;

    /* �ӵ�512�ֽڴ���ʼ�洢��Ϣ����Э��ջ��DSP�쳣���� */
    xMbx_DumpSave((pData+MBX_ERROR_RESERVE_SIZE), (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE));

    system_error(errcode, ulPara1, ulPara2, (char*)pData, MBX_SYSTEM_ERROR_SIZE);

    osl_free(pData);
}

void BSP_xMailbox_SetDtcmAddr(CPHY_CCORE_DYN_ADDR_SHARE_STRU *paddr)
{
    xMAILBOX_CHANNEL_TABLE_STRU *pMbxTbl;

    g_stxMbxShareAddr.ulCphyMbxHpaDownAddr  = paddr->ulCphyMbxHpaDownAddr;
    g_stxMbxShareAddr.ulCphyMbxHpaUpAddr    = paddr->ulCphyMbxHpaUpAddr;
    g_stxMbxShareAddr.ulCphyMbxLoadMemAddr  = paddr->ulCphyMbxLoadMemAddr;
    g_stxMbxShareAddr.ulCphyMbxOmDownAddr   = paddr->ulCphyMbxOmDownAddr;
    g_stxMbxShareAddr.ulCphyMbxWorkModeAddr = paddr->ulCphyMbxWorkModeAddr;

    pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_XSYS_RL);
    pMbxTbl->ulDlAddr = g_stxMbxShareAddr.ulCphyMbxHpaDownAddr;
    pMbxTbl->ulUlAddr = g_stxMbxShareAddr.ulCphyMbxHpaUpAddr;

    pMbxTbl = xMbx_get_tbl(EN_MAILBOX_SERVICE_XSYS_OM);
    pMbxTbl->ulDlAddr = g_stxMbxShareAddr.ulCphyMbxOmDownAddr;

    g_stxMbxCtrl.mem_init = 1;
    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


