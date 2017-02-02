
/*lint --e{801}*/ /*PCLINT: goto's warning 801 is inevitable*/

#include "mailbox.h"
#include <mdrv_timer.h>
#include "bsp_hardtimer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define MBX_PRINT_TIMES     10
#define SRAM_DSP_MNTN_INFO_ADDR  ((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DSP_MNTN_INFO


/* ����ģ�������Ϣ */
MAILBOX_MAINCTRL_STRU   g_stMbxCtrl;
MAILBOX_MNTN_STRU       g_stMbxMntn;

MAILBOX_CHANNEL_TABLE_STRU g_astMbxChnTbl[EN_MAILBOX_SERVICE_BUTT] =
{
    {EN_MAILBOX_SERVICE_LTE_PS,      MBX_ADDRESSER_LTE_PHY_RL,     MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_LTE_CT,      MBX_ADDRESSER_LTE_PHY_CT,     MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_LTE_BT,      MBX_ADDRESSER_LTE_PHY_BT,     MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_LTE_OM,      MBX_ADDRESSER_LTE_PHY_OM,     MAILBOX_OM_DOWN_ADDR,    0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
    {EN_MAILBOX_SERVICE_LTE_COEX,    MBX_ADDRESSER_LTE_PHY_COEX,   MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_LTE_HS_DIAG, MBX_ADDRESSER_LTE_PHY_HS_DIAG,MAILBOX_OM_DOWN_ADDR,    0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
    {EN_MAILBOX_SERVICE_LTE_RCM,     MBX_ADDRESSER_LTE_PHY_RCM,    MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_TDS_PS,      MBX_ADDRESSER_TDS_PHY_RL,     MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_TDS_CT,      MBX_ADDRESSER_TDS_PHY_CT,     MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_TDS_BT,      MBX_ADDRESSER_TDS_PHY_BT,     MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_TDS_OM,      MBX_ADDRESSER_TDS_PHY_OM,     MAILBOX_OM_DOWN_ADDR,    0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
    {EN_MAILBOX_SERVICE_TDS_HS_DIAG, MBX_ADDRESSER_TDS_PHY_HS_DIAG,MAILBOX_OM_DOWN_ADDR,    0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
	{EN_MAILBOX_SERVICE_TDS_RCM,     MBX_ADDRESSER_TDS_PHY_RCM,    MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
	/* cdma���� */
	{EN_MAILBOX_SERVICE_XSYS_RL,     MBX_ADDRESSER_XSYS_PHY_RL,     MAILBOX_PS_DOWN_ADDR,   MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
	{EN_MAILBOX_SERVICE_XSYS_OM,     MBX_ADDRESSER_XSYS_PHY_OM,     MAILBOX_OM_DOWN_ADDR,   0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
	{EN_MAILBOX_SERVICE_XSYS_CT,     MBX_ADDRESSER_XSYS_PHY_CT,     MAILBOX_PS_DOWN_ADDR,   MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
	{EN_MAILBOX_SERVICE_XSYS_BT,     MBX_ADDRESSER_XSYS_PHY_BT,     MAILBOX_PS_DOWN_ADDR,   MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
	{EN_MAILBOX_SERVICE_XSYS_HS_DIAG,MBX_ADDRESSER_XSYS_PHY_HS_DIAG,MAILBOX_OM_DOWN_ADDR,   0                 , NULL,IPC_INT_MSP_DSP_OM_MBX},
#endif

    {EN_MAILBOX_SERVICE_RTT_SYS_CTRL,MBX_ADDRESSER_RTT_SYS_CTRL,   MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_RTT_AGENT,   MBX_ADDRESSER_RTT_AGENT,      MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_RTT_CBT,     MBX_ADDRESSER_RTT_CBT,        MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX},
    {EN_MAILBOX_SERVICE_RTT_HIFI_AGENT, MBX_ADDRESSER_RTT_HIFI_AGENT,  MAILBOX_PS_DOWN_ADDR,    MAILBOX_PS_UP_ADDR, NULL,IPC_INT_PS_DSP_PUB_MBX}

};


u32 mbx_IsChnModMatch(u32 ulChn, u32 ulMod)
{
    if(ulChn >= EN_MAILBOX_SERVICE_BUTT)
    {
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    switch(ulChn)
    {
        case EN_MAILBOX_SERVICE_LTE_PS:
        case EN_MAILBOX_SERVICE_TDS_PS:
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        case EN_MAILBOX_SERVICE_XSYS_RL:
        case EN_MAILBOX_SERVICE_XSYS_OM:
#endif
        {
            if((MBX_ADDRESSER_LTE_PHY_RL == ulMod)
            ||(MBX_ADDRESSER_TDS_PHY_RL == ulMod)
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
            ||(MBX_ADDRESSER_XSYS_PHY_RL == ulMod)
            ||(MBX_ADDRESSER_XSYS_PHY_OM == ulMod)
#endif
             )
            {
                return BSP_OK;
            }
            break;
        }
        case EN_MAILBOX_SERVICE_LTE_RCM:
        case EN_MAILBOX_SERVICE_TDS_RCM:
        {
            if((MBX_ADDRESSER_LTE_PHY_RCM == ulMod)
             ||(MBX_ADDRESSER_TDS_PHY_RCM == ulMod))
            {
                return BSP_OK;
            }
            break;
        }

        case EN_MAILBOX_SERVICE_LTE_CT:
        case EN_MAILBOX_SERVICE_LTE_BT:
        case EN_MAILBOX_SERVICE_TDS_CT:
        case EN_MAILBOX_SERVICE_TDS_BT:
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
        case EN_MAILBOX_SERVICE_XSYS_CT:
        case EN_MAILBOX_SERVICE_XSYS_BT:
#endif
        {
            if((MBX_ADDRESSER_LTE_PHY_CT == ulMod)
             ||(MBX_ADDRESSER_LTE_PHY_BT == ulMod)
             ||(MBX_ADDRESSER_TDS_PHY_CT == ulMod)
             ||(MBX_ADDRESSER_TDS_PHY_BT == ulMod)
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
             ||(MBX_ADDRESSER_XSYS_PHY_CT == ulMod)
			 ||(MBX_ADDRESSER_XSYS_PHY_BT == ulMod)
#endif
			 )
            {
                return BSP_OK;
            }
            break;
        }

        default :
        {
            if(g_astMbxChnTbl[ulChn].ulModule == ulMod)
            {
                return BSP_OK;
            }
        }
    }
    return ERR_MAILBOX_PARAM_INCORRECT;
}

u32 mbx_GetChn(u32 ulMod)
{
    u32 i;

    for(i = 0; i < sizeof(g_astMbxChnTbl)/sizeof(MAILBOX_CHANNEL_TABLE_STRU); i++)
    {
        if(ulMod == g_astMbxChnTbl[i].ulModule)
        {
            return g_astMbxChnTbl[i].ulMbxChn;
        }
    }

    return (u32)EN_MAILBOX_SERVICE_BUTT;
}

/*****************************************************************************
 �� �� ��  : mbx_mntnaddr
 ��������  : �����ַ�����Ϣ
*****************************************************************************/
void mbx_mntnaddr(void)
{
    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("��ַ��Ϣ\n");
    Mbx_Printf("PS���������ַ                : %p.\n", (void*)MAILBOX_PS_DOWN_ADDR);
    Mbx_Printf("PS���������ַ                : %p.\n", (void*)MAILBOX_PS_UP_ADDR);
    Mbx_Printf("OM���������ַ                : %p.\n", (void*)MAILBOX_OM_DOWN_ADDR);
    Mbx_Printf("DSP���ֵ�ַ                   : %p.\n", (void*)BSP_DSP_INIT_RESULT_ADDR);
    Mbx_Printf("ģʽ���õ�ַ                  : %p.\n", (void*)LPHY_MAILBOX_LPHY_WORKING_MODE_ADDR);
    Mbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 �� �� ��  : mbx_mntnabnormal
 ��������  : �����쳣��Ϣ
*****************************************************************************/
void mbx_mntnabnormal(void)
{
    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("�쳣��Ϣ\n");
    Mbx_Printf("PS���������ϱ���CT/BT��ϢID   : %d\n", g_stMbxMntn.stAbnormal.ulMulCtBtMsg);
    Mbx_Printf("PS�����ϱ��Ĵ����ģ��ID      : %d\n", g_stMbxMntn.stAbnormal.ucComPsType);
    Mbx_Printf("����������ʱʱ��        : %d\n", g_stMbxMntn.stAbnormal.ulLongestReq);
    Mbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 �� �� ��  : mbx_mntnother
 ��������  : ����������ά�ɲ���Ϣ
*****************************************************************************/
void mbx_mntnother(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("������Ϣ\n");
    Mbx_Printf("PS�����Ƿ���֡�ж�  : %s\n", (g_stMbxCtrl.bIsSubFrameInt)?"yes":"no");
    Mbx_Printf("PS���䵱ǰ��Ϣ����  : %d\n", g_stMbxCtrl.ulMsgLen);

    Mbx_Printf("���ʮ�ε͹��Ļ���ʱ����Ϣ\n");

    ulStart = (g_stMbxMntn.stSleepInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stSleepInfo.astwakeup[j].ulSlice1)
        {
            Mbx_Printf("| slice1(0x%08x) - slice2(0x%08x) | = (0x%08x)   slice3 : 0x%08x\n",
                g_stMbxMntn.stSleepInfo.astwakeup[j].ulSlice1,
                g_stMbxMntn.stSleepInfo.astwakeup[j].ulSlice2,
                (g_stMbxMntn.stSleepInfo.astwakeup[j].ulSlice2 - g_stMbxMntn.stSleepInfo.astwakeup[j].ulSlice1),
                g_stMbxMntn.stSleepInfo.astwakeup[j].ulSlice3);
        }
    }

    Mbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 �� �� ��  : mbx_mntnnum
 ��������  : ���������¼�����Ϣ
*****************************************************************************/
void mbx_mntnnum(void)
{
    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("������Ϣ\n");
    Mbx_Printf("PS�����жϴ���           : %d\n", g_stMbxMntn.stNumber.ulComPsIntNum);
    Mbx_Printf("ר�������жϴ���         : %d\n", g_stMbxMntn.stNumber.ulSpIntNum);

    Mbx_Printf("PS����д�������         : %d\n", g_stMbxMntn.stNumber.ulPsComReqNum);
    Mbx_Printf("PS����PSд�������       : %d\n", g_stMbxMntn.stNumber.ulPsComPsReqNum);
    Mbx_Printf("PS����MSPд�������      : %d\n", g_stMbxMntn.stNumber.ulPsComMspReqNum);
    Mbx_Printf("PS����RttAgentд������� : %d\n", g_stMbxMntn.stNumber.ulPsComRttAgentReqNum);
    Mbx_Printf("OM����д�������         : %d\n", g_stMbxMntn.stNumber.ulOmComReqNum);

    Mbx_Printf("PS����PS��ȡ����         : %d\n", g_stMbxMntn.stNumber.ulPsComPsRdNum);
    Mbx_Printf("PS��ȡ�ɹ�����           : %d\n", g_stMbxMntn.stNumber.ulPsComPsRdOKNum);
    Mbx_Printf("MSP��ȡ����              : %d\n", g_stMbxMntn.stNumber.ulPsComMspRdNum);
    Mbx_Printf("MSP��ȡ�ɹ�����          : %d\n", g_stMbxMntn.stNumber.ulPsComMspRdOKNum);
    Mbx_Printf("RCM��ȡ����              : %d\n", g_stMbxMntn.stNumber.ulPsComRcmRdNum);
    Mbx_Printf("RCM��ȡ�ɹ�����          : %d\n", g_stMbxMntn.stNumber.ulPsComRcmRdOKNum);
    Mbx_Printf("RttAgent��ȡ����         : %d\n", g_stMbxMntn.stNumber.ulPsComRttAgentRdNum);
    Mbx_Printf("RttAgent��ȡ�ɹ�����     : %d\n", g_stMbxMntn.stNumber.ulPsComRttAgentRdOKNum);

    Mbx_Printf("PS����PS�ص�����         : %d\n", g_stMbxMntn.stNumber.ulPsComPsNotifyNum);
    Mbx_Printf("PS����MSP�ص�����        : %d\n", g_stMbxMntn.stNumber.ulPsComMspNotifyNum);
    Mbx_Printf("PS����RCM�ص�����        : %d\n", g_stMbxMntn.stNumber.ulPsComRcmNotifyNum);
    Mbx_Printf("PS����RttAgent�ص�����   : %d\n", g_stMbxMntn.stNumber.ulPsComRttAgentNotifyNum);

    Mbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 �� �� ��  : mbx_mntnmailfull
 ��������  : ������д�붪ʧ��Ϣ
*****************************************************************************/
void mbx_mntnmailfull(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    ulStart = g_stMbxMntn.stMailFull.ulPtr;

    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("��������Ϣ\n");
    Mbx_Printf("����������          : %d\n", g_stMbxMntn.stMailFull.ulFullNum);

    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stMailFull.astFullInfo[j].ulSlice)
        {
            Mbx_Printf("���� : %d   ��ϢID : 0x%08x   ʱ�� : 0x%08x\n",
                g_stMbxMntn.stMailFull.astFullInfo[j].ulModId
                , g_stMbxMntn.stMailFull.astFullInfo[j].ulMsgId
                , g_stMbxMntn.stMailFull.astFullInfo[j].ulSlice);
        }
    }

    Mbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 �� �� ��  : mbx_mntnreqinfo
 ��������  : ����д������Ϣ
*****************************************************************************/
void mbx_mntnreqinfo(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("����д������Ϣ\n");

    ulStart = (g_stMbxMntn.stReqInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stReqInfo.astReq[j].ulSliceEnd)
        {
            Mbx_Printf("���� : %d   ��ϢID : 0x%08x   ����ʱ�� : 0x%08x   д��ʱ�� : 0x%08x\n",
                g_stMbxMntn.stReqInfo.astReq[j].ulModId, g_stMbxMntn.stReqInfo.astReq[j].ulMsgId,
                g_stMbxMntn.stReqInfo.astReq[j].ulSliceStart, g_stMbxMntn.stReqInfo.astReq[j].ulSliceEnd);
        }
    }

    Mbx_Printf("***************************************************************\n");
}


/*****************************************************************************
 �� �� ��  : mbx_mntncnfinfo
 ��������  : �����������Ϣ
*****************************************************************************/
void mbx_mntncnfinfo(void)
{
    u32 i = 0, j = 0;
    u32 ulStart = 0;

    Mbx_Printf("***************************************************************\n");

    Mbx_Printf("���ʮ�θ����жϵ���Ϣ\n");

    ulStart = (g_stMbxMntn.stIntInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stIntInfo.ulSlice[j])
        {
            Mbx_Printf("interrupt slice : 0x%08x\n", g_stMbxMntn.stIntInfo.ulSlice[j]);
        }
    }

    Mbx_Printf("���ʮ��ԭ���ȡ����Ϣ\n");

    ulStart = (g_stMbxMntn.stReadInfo.ulPsPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stReadInfo.astRead[j].ulSlice)
        {
            Mbx_Printf("app read , src 0x%x, slice 0x%08x\n",
                g_stMbxMntn.stReadInfo.astRead[j].ulSrc, g_stMbxMntn.stReadInfo.astRead[j].ulSlice);
        }
    }

    ulStart = (g_stMbxMntn.stCnfInfo.ulPsPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    Mbx_Printf("����PS���10����������Ϣ\n");

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stCnfInfo.astPsCnf[j].ulSlice)
        {
            Mbx_Printf("��ϢID : 0x%08x   ��ȡʱ�� : 0x%08x\n",
                g_stMbxMntn.stCnfInfo.astPsCnf[j].ulMsgId, g_stMbxMntn.stCnfInfo.astPsCnf[j].ulSlice);
        }
    }

    ulStart = (g_stMbxMntn.stCnfInfo.ulRcmPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;
    Mbx_Printf("����RCM���10����������Ϣ\n");
    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;
        if(0 != g_stMbxMntn.stCnfInfo.astRcmCnf[j].ulSlice)
        {
            Mbx_Printf("��ϢID : 0x%08x   ��ȡʱ�� : 0x%08x\n",
                g_stMbxMntn.stCnfInfo.astRcmCnf[j].ulMsgId, g_stMbxMntn.stCnfInfo.astRcmCnf[j].ulSlice);
        }
    }
    ulStart = (g_stMbxMntn.stCnfInfo.ulCbtPtr + MAILBOX_MNTN_NUMBER - MBX_PRINT_TIMES)%MAILBOX_MNTN_NUMBER;

    Mbx_Printf("����CT/BT���10����������Ϣ\n");

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stCnfInfo.astCbtCnf[j].ulSlice)
        {
            Mbx_Printf("��ϢID : 0x%08x   ��ȡʱ�� : 0x%08x\n",
                g_stMbxMntn.stCnfInfo.astCbtCnf[j].ulMsgId, g_stMbxMntn.stCnfInfo.astCbtCnf[j].ulSlice);
        }
    }

    Mbx_Printf("����Rtt Agent���10����������Ϣ\n");

    for(i = 0; i < MBX_PRINT_TIMES; i++)
    {
        j = (ulStart + i)%MAILBOX_MNTN_NUMBER;

        if(0 != g_stMbxMntn.stCnfInfo.astRttAgentCnf[j].ulSlice)
        {
            Mbx_Printf("��ϢID : 0x%08x   ��ȡʱ�� : 0x%08x\n",
                g_stMbxMntn.stCnfInfo.astRttAgentCnf[j].ulMsgId, g_stMbxMntn.stCnfInfo.astRttAgentCnf[j].ulSlice);
        }
    }

    Mbx_Printf("***************************************************************\n");
}

void mbx_mntnSleepCbInfo(void)
{
    u32 i =0,j=0;
    for(i=0; i<MAILBOX_MNTN_NUMBER; i++)
    {
        j = (g_stMbxMntn.stSleepCbInfo.ulPtr+i)%MAILBOX_MNTN_NUMBER;
        if(0 != g_stMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceStart)
        {
            Mbx_Printf("Callback Type : %d, Is Mbx wakeup :%d, end time(0x%08x) - start time(0x%08x) = %d  MS\n",
                g_stMbxMntn.stSleepCbInfo.astCbInfo[j].cbType,g_stMbxMntn.stSleepCbInfo.astCbInfo[j].ulWakeup,\
                g_stMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceEnd,g_stMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceStart,\
                ((g_stMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceEnd-g_stMbxMntn.stSleepCbInfo.astCbInfo[j].ulSliceStart)/32));
        }
    }
}

void mbx_mntnDirectWriteInfo(void)
{
    u32 i = 0 ,k = 0;
    u32 j = g_stMbxMntn.stDirectInfo.ulPtr % MAILBOX_MNTN_NUMBER;
    Mbx_Printf("*************Direct Num 0x%x****************\n",g_stMbxMntn.stDirectInfo.ulPtr);
    Mbx_Printf("*************print lastest *****************\n");
    for(i = 0;i < MAILBOX_MNTN_NUMBER;i++)
    {
        k = (j+1)%MAILBOX_MNTN_NUMBER;
        if(0 != g_stMbxMntn.stDirectInfo.ulSlice[k])
        {
            Mbx_Printf("�� %d �Σ�ʱ���Ϊ :0x%x\n",i,g_stMbxMntn.stDirectInfo.ulSlice[k]);
        }
    }
}
/*****************************************************************************
 �� �� ��  : mbx_mntnerrorcode
 ��������  : ��������������Ϣ
*****************************************************************************/
void mbx_mntnerrorcode(void)
{
    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("��������Ϣ\n");
    Mbx_Printf("1  : ����δ��ʼ��.\n");
    Mbx_Printf("2  : �����������.\n");
    Mbx_Printf("3  : ������.\n");
    Mbx_Printf("4  : ��ʱ.\n");
    Mbx_Printf("5  : ר���������ݸ���.\n");
    Mbx_Printf("6  : дʧ��.\n");
    Mbx_Printf("7  : ��ʧ��.\n");
    Mbx_Printf("8  : ����ϢΪ��.\n");
    Mbx_Printf("9  : DSP˯��.\n");
    Mbx_Printf("10 : ����.\n");
    Mbx_Printf("***************************************************************\n");
}


void mbx_debug(BSP_BOOL bDebug)
{
    g_stMbxMntn.bdbg = bDebug;
}

/*****************************************************************************
 �� �� ��  : mailbox_help
 ��������  : �����ӡ����
*****************************************************************************/
void mailbox_help(void)
{
    Mbx_Printf("***************************************************************\n");
    Mbx_Printf("�����ַ�����Ϣ                mbx_mntnaddr\n");
    Mbx_Printf("���������¼�����Ϣ            mbx_mntnnum\n");
    Mbx_Printf("����д������Ϣ                  mbx_mntnreqinfo\n");
    Mbx_Printf("�����������Ϣ                  mbx_mntncnfinfo\n");
    Mbx_Printf("������д�붪ʧ��Ϣ              mbx_mntnmailfull\n");
    Mbx_Printf("�����쳣��Ϣ                    mbx_mntnabnormal\n");
    Mbx_Printf("����������ά�ɲ���Ϣ            mbx_mntnother\n");
    Mbx_Printf("�������ʧ�ܴ�������Ϣ          mbx_mntnerrorcode\n");
    Mbx_Printf("�����ӡ��Ϣ����                mbx_debug 1/0\n");
    Mbx_Printf("����SLEEP�ص���Ϣ               mbx_mntnSleepCbInfo\n");
    Mbx_Printf("����ֱ��д��Ϣ                  mbx_mntnDirectWriteInfo\n");
    Mbx_Printf("***************************************************************\n");
}


/*lint -save -e545 -e813*/
/*****************************************************************************
 Prototype       : Mbx_BbeIpcProc
 Description     : ������쳣����
                   BBE�����쳣ʱ�������쳣��Ϣ��AXI memory�У�Ȼ��ͨ��IPC�ж�
                   ֪ͨ����ģ�飬������ģ���¼�쳣��Ϣ���������쳣�����ӿ�
 Return Value    : NONE
*****************************************************************************/
void Mbx_BbeIpcProc(void)
{
    u8  ucData[MBX_SYSTEM_ERROR_SIZE] = {0};     /* 4K���棬ǰ32�ֽڴ�DSP��Ϣ */
    u32 *pAddr;
    u16 usMode;

    usMode = *(u16*)SRAM_DSP_MNTN_INFO_ADDR;

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
        Mbx_Memcpy((u8*)pAddr, (u8*)SRAM_DSP_MNTN_INFO_ADDR, SRAM_DSP_MNTN_SIZE); /* [false alarm]:fortify */

        /* �ӵ�512�ֽڿ�ʼ���������������쳣��Ϣ */
        Mbx_DumpSave(ucData+MBX_ERROR_RESERVE_SIZE, (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE));

        system_error(DRV_ERRNO_MBX_DSP_IPC, MBX_ERROR_DSP_IPC, 0, (char*)ucData, MBX_SYSTEM_ERROR_SIZE);
    }
}
/*lint -restore*/


/*****************************************************************************
 �� �� ��  : bsp_mailbox_init
 ��������  : ����ģ���ʼ��
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
void bsp_mailbox_init(void)
{
    s32 ret;

    if(BSP_TRUE == g_stMbxCtrl.bMbxInit)
    {
        Mbx_Printf("enter again.\n");
        return;
    }

    Mbx_Memset(&g_stMbxCtrl, 0, sizeof(MAILBOX_MAINCTRL_STRU));

    Mbx_Memset((void*)(&g_stMbxMntn), 0, sizeof(MAILBOX_MNTN_STRU));

    g_stMbxCtrl.bDspWakeFlag = BSP_FALSE;

    osl_sem_init(0, &g_stMbxCtrl.semDspWakeup);
    osl_sem_init(1, &g_stMbxCtrl.semDspMutex);
    g_stMbxCtrl.pulAxiAddr = (u32*)MBX_LDSP_WAKEUP_ADDR;
    g_stMbxCtrl.lAxiCnt = 0;
    ret = (s32)mdrv_ipc_int_connect(IPC_INT_DSP_PS_PUB_MBX, (VOIDFUNCPTR)Mbx_ComPsIntProc, 0);
	if(BSP_OK != ret)
	{
        Mbx_Printf("mdrv_ipc_int_connect failed.\n");
        return ;
	}

    ret = (s32)mdrv_ipc_int_enable(IPC_INT_DSP_PS_PUB_MBX);
	if(BSP_OK != ret)
	{
        Mbx_Printf("mdrv_ipc_int_enable failed.\n");
        return ;
	}

    ret = (s32)mdrv_ipc_int_connect(IPC_CCPU_INT_SRC_DSP_RCM_PUB_MBX, (VOIDFUNCPTR)Mbx_ComPsIntProc, 0);
    if(BSP_OK != ret)
    {
        Mbx_Printf("mdrv_ipc_int_connect failed.\n");
        return ;
    }

    ret = (s32)mdrv_ipc_int_enable(IPC_CCPU_INT_SRC_DSP_RCM_PUB_MBX);
    if(BSP_OK != ret)
    {
        Mbx_Printf("mdrv_ipc_int_enable failed.\n");
        return ;
    }

    /* DSP��ά�ɲ�IPC�ж� */
    ret = (s32)mdrv_ipc_int_connect(IPC_CCPU_INT_SRC_DSP_MNTN, (VOIDFUNCPTR)Mbx_BbeIpcProc, 0);
    if(BSP_OK != ret)
    {
        Mbx_Printf("mdrv_ipc_int_connect failed.\n");
        return ;
    }

    ret = (s32)mdrv_ipc_int_enable(IPC_CCPU_INT_SRC_DSP_MNTN);
    if(BSP_OK != ret)
    {
        Mbx_Printf("mdrv_ipc_int_enable failed.\n");
        return ;
    }

    g_stMbxCtrl.bIsSubFrameInt = BSP_FALSE;

    Mbx_Printf("success.\n");
    return;
}


/*****************************************************************************
 �� �� ��  : Mbx_ForbidDspSleep
 ��������  : ����AXI memory��ֹDSP����˯��
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
void Mbx_ForbidDspSleep(void)
{
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
#else
    unsigned long key;

    local_irq_save(key);
    g_stMbxCtrl.lAxiCnt++;
    writel(1, (unsigned)(g_stMbxCtrl.pulAxiAddr));
    local_irq_restore(key);
#endif
}


/*****************************************************************************
 �� �� ��  : Mbx_ForbidDspSleep
 ��������  : ���AXI memory����DSP����˯��
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
void Mbx_AllowDspSleep(void)
{
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
#else
    unsigned long key;

    local_irq_save(key);
    if((--g_stMbxCtrl.lAxiCnt) <= 0)
    {
        g_stMbxCtrl.lAxiCnt = 0;
        writel(0, (unsigned)(g_stMbxCtrl.pulAxiAddr));
    }
    local_irq_restore(key);
#endif
}



u32 Mbx_SpaceMalloc(MAILBOX_RINGBUFF_STRU* pMbxHandle,u32 ulSizeReq)
{
    u32 ulFreeBuffSize;
    u32 wr,rd,size;

    wr   = pMbxHandle->ulRbufWrPtr;
    rd   = pMbxHandle->ulRbufRdPtr;
    size = pMbxHandle->ulRbufSize;

    /* ���дָ��Ƿ����������� */
    if(wr > size)
    {
        Mbx_SystemError((u32)MBX_ERROR_UP_WR, wr, rd, ((__LINE__ << 16)|size));
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
        Mbx_Printf("Mbx_SpaceMalloc failed, ulFreeBuffSize(%d), ulSizeReq(%d), wr(%d), rd(%d), size(%d).\n",
            ulFreeBuffSize, ulSizeReq, wr, rd, size);
        return (u32)BSP_ERROR;
    }
}


void Mbx_MntnMailFull(MAILBOX_MSG_HAED_STRU* pstMsg)
{
    g_stMbxMntn.stMailFull.ulFullNum++;

    g_stMbxMntn.stMailFull.astFullInfo[g_stMbxMntn.stMailFull.ulPtr].ulModId = (u32)(pstMsg->usDstMod);
    g_stMbxMntn.stMailFull.astFullInfo[g_stMbxMntn.stMailFull.ulPtr].ulMsgId = *(u32*)(pstMsg->pPayload);
    g_stMbxMntn.stMailFull.astFullInfo[g_stMbxMntn.stMailFull.ulPtr].ulSlice = bsp_get_slice_value();

    g_stMbxMntn.stMailFull.ulPtr = (g_stMbxMntn.stMailFull.ulPtr+1)%MAILBOX_MNTN_NUMBER;
}


/*****************************************************************************
 Prototype       : Mbx_RbuffWrite
 Description     : ѭ��bufferд�ӿ�
 param           : pHead        ѭ��buffer���׵�ַ
                   pstMsg       ��д������ָ��
 Return Value    : BSP_OK : �ɹ�
                   ERR_MAILBOX_MEMORY_NOTENOUGH : ʣ��ռ䲻��
*****************************************************************************/
s32 Mbx_RbuffWrite(MAILBOX_RINGBUFF_STRU* pHead, MAILBOX_MSG_HAED_STRU* pstMsg)
{
    u32 ulMsgSize = pstMsg->usMsgSize + (sizeof(MAILBOX_MSG_HAED_STRU) - 4);
    u32 ulCpySize0;
    u32 ulCpySize1;
    u32 ulTempPPTR;

    /* ����ʣ��ռ��� */
    if(BSP_OK != Mbx_SpaceMalloc(pHead,ulMsgSize))
    {
        Mbx_MntnMailFull(pstMsg);
        return ERR_MAILBOX_MEMORY_NOTENOUGH;
    }

    /* ����Ϣд�� */
    if((ulMsgSize + pHead->ulRbufWrPtr) <= pHead->ulRbufSize)
    {
        Mbx_Memcpy((void*)(pHead->ulRbufWrPtr + pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                        (void*)pstMsg,
                        (sizeof(MAILBOX_MSG_HAED_STRU) - 4));
        Mbx_Memcpy((void*)(pHead->ulRbufWrPtr + pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET + (sizeof(MAILBOX_MSG_HAED_STRU) - 4)),
                        (void*)(pstMsg->pPayload),
                        pstMsg->usMsgSize);     /*lint !e516*/
    }
    else
    {
        ulCpySize0 = pHead->ulRbufSize - pHead->ulRbufWrPtr;
        ulCpySize1 = ulMsgSize - ulCpySize0;

        if(ulCpySize0 < (sizeof(MAILBOX_MSG_HAED_STRU) - 4))
        {
            Mbx_Memcpy((void*)(pHead->pucRbufAddr + pHead->ulRbufWrPtr + MAILBOX_ADDR_OFFSET),
                            (void*)pstMsg,
                            ulCpySize0);

            Mbx_Memcpy((void*)(pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                            (void*)((u32)(pstMsg)+ulCpySize0),
                            ((sizeof(MAILBOX_MSG_HAED_STRU) - 4)-ulCpySize0));

            Mbx_Memcpy((void*)(pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET + ((sizeof(MAILBOX_MSG_HAED_STRU) - 4)-ulCpySize0)),
                            (void*)(pstMsg->pPayload),
                            pstMsg->usMsgSize);     /*lint !e516*/
        }
        else
        {
            Mbx_Memcpy((void*)(pHead->pucRbufAddr + pHead->ulRbufWrPtr + MAILBOX_ADDR_OFFSET),
                            (void*)(pstMsg),
                            (sizeof(MAILBOX_MSG_HAED_STRU) - 4));

            Mbx_Memcpy((void*)(pHead->pucRbufAddr + pHead->ulRbufWrPtr + MAILBOX_ADDR_OFFSET + (sizeof(MAILBOX_MSG_HAED_STRU) - 4)),
                            (void*)(pstMsg->pPayload),
                            (ulCpySize0 - (sizeof(MAILBOX_MSG_HAED_STRU) - 4)));

            Mbx_Memcpy((void*)(pHead->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                            (void*)((u32)(pstMsg->pPayload) + (ulCpySize0 - (sizeof(MAILBOX_MSG_HAED_STRU) - 4))),
                            ulCpySize1);
        }
    }

    /* дָ�����,��֤���ֽڶ��� */
    ulTempPPTR = ((pHead->ulRbufWrPtr + ulMsgSize + 3) & (~3));

    if(ulTempPPTR >= pHead->ulRbufSize)
    {
        ulTempPPTR -= pHead->ulRbufSize;
    }

    Mbx_MntnWriteEnd(pHead, pstMsg, ulTempPPTR);

    pHead->ulRbufWrPtr = ulTempPPTR;

    return BSP_OK;
}
u32 Mbx_GetNewMsgLen (MAILBOX_MSG_HAED_STRU* pMsg)
{
    return(u32)(pMsg->usMsgSize);
}



u32 Mbx_NewMsgReadOut(MAILBOX_MSG_HAED_STRU* pMsg,MAILBOX_RINGBUFF_STRU* pMbxHandle)
{
    u32 ulMsgSize;
    u32 ulCpySize0;
    u32 ulCpySize1;
    u32 ulTempCPTR;
    MAILBOX_MSG_HAED_STRU *pstMsg = NULL;

    pstMsg = (MAILBOX_MSG_HAED_STRU*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET + pMbxHandle->ulRbufRdPtr);
    ulMsgSize = Mbx_GetNewMsgLen(pstMsg) + (sizeof(MAILBOX_MSG_HAED_STRU) - 4);

    /* user space not enough, return failure, avoid overflow */
    if(pstMsg->usMsgSize > pMsg->usMsgSize)
    {
        pMsg->usMsgSize = pstMsg->usMsgSize;
        goto newmsgreadfailed;
    }

    /* ����Ϣ���� */
    if((ulMsgSize + pMbxHandle->ulRbufRdPtr) <= pMbxHandle->ulRbufSize)
    {
        Mbx_Memcpy((void*)pMsg,
                (void*)(pMbxHandle->ulRbufRdPtr + pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                (sizeof(MAILBOX_MSG_HAED_STRU) - 4));

        Mbx_Memcpy((void*)(pMsg->pPayload),
                (void*)(pMbxHandle->ulRbufRdPtr + pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET + (sizeof(MAILBOX_MSG_HAED_STRU) - 4)),
                pstMsg->usMsgSize);     /*lint !e516*/
    }
    else
    {
        ulCpySize0 = pMbxHandle->ulRbufSize - pMbxHandle->ulRbufRdPtr;
        ulCpySize1 = ulMsgSize - ulCpySize0;

        if(ulCpySize0 < (sizeof(MAILBOX_MSG_HAED_STRU) - 4))
        {
            Mbx_Memcpy((void*)(pMsg),
                    (void*)(pMbxHandle->pucRbufAddr + pMbxHandle->ulRbufRdPtr + MAILBOX_ADDR_OFFSET),
                    ulCpySize0);

            Mbx_Memcpy((void*)((u32)pMsg + ulCpySize0),
                    (void*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET),
                    (sizeof(MAILBOX_MSG_HAED_STRU) - 4) - ulCpySize0);

            Mbx_Memcpy((void*)(pMsg->pPayload),
                    (void*)(pMbxHandle->pucRbufAddr + MAILBOX_ADDR_OFFSET + (sizeof(MAILBOX_MSG_HAED_STRU) - 4) - ulCpySize0),
                    pstMsg->usMsgSize);     /*lint !e516*/
        }
        else
        {
            Mbx_Memcpy((void*)(pMsg),
                    (void*)(pMbxHandle->pucRbufAddr + pMbxHandle->ulRbufRdPtr + MAILBOX_ADDR_OFFSET),
                    (sizeof(MAILBOX_MSG_HAED_STRU) - 4));

            Mbx_Memcpy((void*)(pMsg->pPayload),
                    (void*)(pMbxHandle->pucRbufAddr + pMbxHandle->ulRbufRdPtr + MAILBOX_ADDR_OFFSET + (sizeof(MAILBOX_MSG_HAED_STRU) - 4)),
                    ulCpySize0 - (sizeof(MAILBOX_MSG_HAED_STRU) - 4));

            Mbx_Memcpy((void*)((u32)(pMsg->pPayload) + ulCpySize0 - (sizeof(MAILBOX_MSG_HAED_STRU) - 4)),
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

    Mbx_MntnReadEnd(pMsg->pPayload, (enum __MBX_ADDRESSEE_ID_ENUM__)pMsg->usDstMod, ulTempCPTR, pMbxHandle->ulRbufWrPtr);

    pMbxHandle->ulRbufRdPtr = ulTempCPTR;

    return (ulTempCPTR);
}


/*****************************************************************************
 Prototype       : BSP_MailBox_GetDspStatusReg
 Description     : ��ȡDSP˯��״̬�ص�����ע��ӿڣ��͹���ģ�����
 param           : pFun             ��ȡDSP˯��״̬������
 Return Value    : BSP_VOID
*****************************************************************************/
void BSP_MailBox_GetDspStatusReg(BSP_MBX_GET_STATUS_FUNC pFun)
{
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    g_stMbxCtrl.pfnGetDspStatusProc = NULL;
#else
    g_stMbxCtrl.pfnGetDspStatusProc = pFun;
#endif
}


/*****************************************************************************
 Prototype       : BSP_MailBox_DspForceAwakeReg
 Description     : DSPǿ�ƻ��ѻص�����ע��ӿڣ��͹���ģ�����
 param           : pFun             DSPǿ�ƻ��Ѵ�����
 Return Value    : BSP_VOID
*****************************************************************************/
void BSP_MailBox_DspForceAwakeReg(BSP_MBX_DSP_AWAKE_FUNC pFun)
{
    g_stMbxCtrl.pfnDspForceAwakeProc = pFun;
}


/*****************************************************************************
 Prototype       : BSP_MailBox_GetSpMsgStatusReg
 Description     : ��ȡר����������DSP˯��״̬�ص�����ע��ӿڣ�PS����
 param           : pFun             ��ȡDSP˯��״̬������
 Return Value    : BSP_VOID
*****************************************************************************/
void BSP_MailBox_GetSpMsgStatusReg(BSP_MBX_GET_STATUS_FUNC pFun)
{
    g_stMbxCtrl.pfnGetSpMsgProc = pFun;
}


/*****************************************************************************
 Prototype       : BSP_MailBox_DspAwakeProc
 Description     : DSP���Ѻ�����䴦��ӿڣ��͹���ģ�����
 param           : BSP_VOID
 Return Value    : BSP_VOID
*****************************************************************************/
void BSP_MailBox_DspAwakeProc(MAILBOX_CALLBACK_TYPE cbType)
{
    u32 ulPtr = g_stMbxMntn.stSleepCbInfo.ulPtr;
    g_stMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].cbType       = cbType;
    if(cbType >= EN_MAILBOX_CALLBACK_DSP_BUTT)
    {
        Mbx_Printf("err parm ! %d \n",cbType);
        cbType = EN_MAILBOX_CALLBACK_DSP_BUTT;
    }
    if(g_stMbxCtrl.pfnRcmNotifyProc)
    {
        g_stMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].ulWakeup     = g_stMbxCtrl.bDspWakeFlag;

        g_stMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].ulSliceStart = bsp_get_slice_value();
        g_stMbxCtrl.pfnRcmNotifyProc(cbType);

        g_stMbxMntn.stSleepCbInfo.astCbInfo[ulPtr].ulSliceEnd   = bsp_get_slice_value();

        ulPtr = g_stMbxMntn.stSleepCbInfo.ulPtr +1;

        g_stMbxMntn.stSleepCbInfo.ulPtr = ulPtr%MAILBOX_MNTN_NUMBER;
    }
    /* ֻ��������ģ�鷢��Ļ��� */
    if(BSP_TRUE == g_stMbxCtrl.bDspWakeFlag)
    {
        g_stMbxMntn.stSleepInfo.astwakeup[g_stMbxMntn.stSleepInfo.ulPtr].ulSlice2 = bsp_get_slice_value();
        g_stMbxCtrl.bDspWakeFlag = BSP_FALSE;
        osl_sem_up(&g_stMbxCtrl.semDspWakeup);
    }
}


/*****************************************************************************
 Prototype       : BSP_MailBox_IsAllowDspSleep
 Description     : ��ѯ�Ƿ�����DSP˯�ߵĴ���ӿڣ��͹���ģ�����
                    ���ô˽ӿ�ʱ�͹���ģ�鱣֤DSPδ˯��
                    �˽ӿ�ֻ���PS�����ר�����䣬�����OM����(OMԭ����ʱ��Ҫ��)
 param           : BSP_VOID
 Return Value    : BSP_BOOL: TRUE-allow;FALSE-forbid
*****************************************************************************/
int BSP_MailBox_IsAllowDspSleep(void)
{
#if (FEATURE_MAILBOX_CDMA_NOT_USE == FEATURE_ON)
    return BSP_FALSE;
#else
    BSP_BOOL bFlag;
    MAILBOX_RINGBUFF_STRU* pstComPsUpMail = (MAILBOX_RINGBUFF_STRU*)MAILBOX_PS_UP_ADDR;
    MAILBOX_RINGBUFF_STRU* pstComPsDownMail = (MAILBOX_RINGBUFF_STRU*)MAILBOX_PS_DOWN_ADDR;
    MAILBOX_RINGBUFF_STRU* pstOmDownMail = (MAILBOX_RINGBUFF_STRU*)MAILBOX_OM_DOWN_ADDR;

    if(!(g_stMbxCtrl.bMbxInit))
    {
        g_stMbxMntn.stAbnormal.ulNInitSlic = bsp_get_slice_value();
        return BSP_TRUE;
    }

    /* ��һ���ȼ��Ȳ�AXI memory��AXI memory����ʱ������DSP˯�� */
    if(*(g_stMbxCtrl.pulAxiAddr) == 1)
    {
        return BSP_FALSE;
    }

    /* ר��������ԭ��δ���߽�ֹ˯�� */
    if(NULL != g_stMbxCtrl.pfnGetSpMsgProc)
    {
        bFlag = g_stMbxCtrl.pfnGetSpMsgProc();
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
#endif
}


/*****************************************************************************
 Prototype       : BSP_UniMailboxWrite
 Description     : �����ͨ��д�ӿ�(�ɵ����߱�֤����ĵ�ַ�ĺϷ���)
                   ���ӿ�ʵ������memcpy����������
                   �ӿ��ڲ���֤DSP�Ļ��Ѳ������������ʧ�ܣ�����ERR_MAILBOX_TIMEOUT
 Return Value    :
                   BSP_OK
                   ERR_MAILBOX_PARAM_INCORRECT
                   ERR_MAILBOX_TIMEOUT
*****************************************************************************/
unsigned int BSP_UniMailboxWrite(void *pDst, void *pSrc, unsigned int ulLen)
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

    Mbx_Memcpy(pDst, pSrc, ulLen);

    BSP_Mailbox_AllowDspSleep();

    return BSP_OK;
}


/*****************************************************************************
 Prototype       : BSP_MailboxAbnormalProc
 Description     : �����쳣����
                   Э��ջ������Ϣ��ʱ����ô˽ӿڱ������������Ϣ
                   ��Э��ջ�̶���ǰ0.5K����Э��ջ��Ϣ����3.5K����������Ϣ
 Input           : ucData       �����׵�ַ
 Return Value    : NONE
*****************************************************************************/
void BSP_MailboxAbnormalProc(unsigned char *ucData)
{
    if(BSP_NULL == ucData)
    {
        return;
    }

    Mbx_Printf("enter.\n");

    Mbx_DumpSave(ucData, (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE));

    Mbx_Printf("exit.\n");
}


/*****************************************************************************
 Prototype       : Mbx_DumpSave
 Description     : �����쳣������Ϣ����ӿ�
                    ��¼���е�������Ϣ
                    ��¼���еĶ�ȡ���󡢶�ȡ�����Ϣ
                    ��¼���һ��DSP IPC�ж��ϱ���ʱ��
                    ��¼����DSP��ʱ����Ϣ
 Input           :  pData ��������ʼ��ַ
                    ulSize ��������С
 Return Value    : NONE
*****************************************************************************/
void Mbx_DumpSave(u8* pData, u32 ulSize)
{
    u32 i,ptr;
    u32 ultmp = 0;

    /* ����Ŀռ��С��С3.5K */
    if((ulSize < (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE)) || (NULL == pData))
    {
        Mbx_Printf("ulSize %d, pData %p.\n", ulSize, pData);
        return;
    }

    ptr = g_stMbxMntn.stReqInfo.ulPtr;
    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        /* (msg ID/RWpointer/start slice/end slice) */
        Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stReqInfo.astReq[ptr].ulMsgId), 4*sizeof(u32)); /*lint !e420*/ /* [false alarm]:fortify */
        ultmp += 4*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 1600 */
    Mbx_Printf("ultmp = %d.\n", ultmp);

    ptr = g_stMbxMntn.stCnfInfo.ulPsPtr;
    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        /* (msg ID/slice) */
        Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stCnfInfo.astPsCnf[ptr]), 2*sizeof(u32));
        ultmp += 2*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 2400 */
    Mbx_Printf("ultmp = %d.\n", ultmp);

    ptr = g_stMbxMntn.stReadInfo.ulPsPtr;
    for(i = 0; i < MAILBOX_MNTN_NUMBER; i++)
    {
        /* (read src/slice) */
        Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stReadInfo.astRead[ptr]), 2*sizeof(u32));
        ultmp += 2*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 3200 */
    Mbx_Printf("ultmp = %d.\n", ultmp);

    /* �ռ����ޣ�ֻ��¼���ʮ�εĻ�����Ϣ */
    ptr = (g_stMbxMntn.stSleepInfo.ulPtr + MAILBOX_MNTN_NUMBER - MBX_ERROR_MNTN_NUM)%MAILBOX_MNTN_NUMBER;
    for(i = 0; i < MBX_ERROR_MNTN_NUM; i++)
    {
        /* (req slice/callback slice/proc slice) */
        Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stSleepInfo.astwakeup[ptr]), 3*sizeof(u32));
        ultmp += 3*sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 3320 */
    Mbx_Printf("ultmp = %d.\n", ultmp);

    /* �ռ����ޣ�ֻ��¼���ʮ�ε�IPCʱ����Ϣ */
    ptr = (g_stMbxMntn.stCallback.ulPtr + MAILBOX_MNTN_NUMBER - MBX_ERROR_MNTN_NUM)%MAILBOX_MNTN_NUMBER;
    for(i = 0; i < MBX_ERROR_MNTN_NUM; i++)
    {
        /* (callback timer) */
        Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stCallback.ulSlice[ptr]), sizeof(u32));
        ultmp += sizeof(u32);
        ptr = (ptr+1)%MAILBOX_MNTN_NUMBER;
    }

    /* ultmp value is 3360 */
    Mbx_Printf("ultmp = %d.\n", ultmp);

    Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stNumber), sizeof(g_stMbxMntn.stNumber));
    ultmp += sizeof(g_stMbxMntn.stNumber);

    /* ultmp value is 3408 */

    Mbx_Printf("ultmp = %d.\n", ultmp);

    Mbx_Memcpy(&pData[ultmp], (u8*)&(g_stMbxMntn.stAbnormal), sizeof(g_stMbxMntn.stAbnormal));
    ultmp += sizeof(g_stMbxMntn.stAbnormal);

    /* ultmp value is 3424 */
    Mbx_Printf("ultmp = %d.\n", ultmp);

    /* �����32���ֽڱ�������������ͷ��Ϣ */
    if(BSP_OK == BSP_Mailbox_ForbidDspSleep(EN_MAILBOX_SLEEP_WAKEUP))
    {
        Mbx_Memcpy(&pData[ulSize-(2*sizeof(MAILBOX_RINGBUFF_STRU))],
            (BSP_VOID*)MAILBOX_PS_DOWN_ADDR, sizeof(MAILBOX_RINGBUFF_STRU)); /* [false alarm]:fortify */

        Mbx_Memcpy(&pData[ulSize - sizeof(MAILBOX_RINGBUFF_STRU)],
            (BSP_VOID*)MAILBOX_PS_UP_ADDR, sizeof(MAILBOX_RINGBUFF_STRU)); /* [false alarm]:fortify */

        BSP_Mailbox_AllowDspSleep();
    }

}


/*****************************************************************************
 Prototype       : Mbx_SystemError
 Description     : �����쳣��������ӿ�
                    ��¼���е�������Ϣ
                    ��¼���еĶ�ȡ���󡢶�ȡ�����Ϣ
                    ��¼���һ��DSP IPC�ж��ϱ���ʱ��
                    ��¼����DSP��ʱ����Ϣ
 Input           : errcode  �����ڲ�������
                   ulPara1,ulPara2,ulPara3   ����1,2,3���쳣�����ֻ�������1
 Return Value    : NONE
*****************************************************************************/
void Mbx_SystemError(u32 errcode, u32 ulPara1, u32 ulPara2, u32 ulPara3)
{
    u8 *pData;
    u32 *pAddr;

    errcode = DRV_ERRNO_MBX_WR_FULL + errcode;
    pData = osl_malloc(MBX_SYSTEM_ERROR_SIZE);
    if(NULL == pData)
    {
        /* �����������DRV_ERRNO_MBX_WR_FULL��ʼ */
        system_error(errcode, ulPara1, ulPara2, (char*)NULL, 0); /* [false alarm]:fortify */
        return ;
    }
    Mbx_Memset(pData, 0, MBX_SYSTEM_ERROR_SIZE);

    /* ǰ4���ֱ��洫��Ĳ��� */
    pAddr = (u32*)pData;

    *(pAddr++) = errcode;
    *(pAddr++) = ulPara1;
    *(pAddr++) = ulPara2;
    *(pAddr++) = ulPara3;

    /* �ӵ�512�ֽڴ���ʼ�洢��Ϣ����Э��ջ��DSP�쳣���� */
    Mbx_DumpSave((pData+MBX_ERROR_RESERVE_SIZE), (MBX_SYSTEM_ERROR_SIZE-MBX_ERROR_RESERVE_SIZE));

    system_error(errcode, ulPara1, ulPara2, (char*)pData, MBX_SYSTEM_ERROR_SIZE);

    osl_free(pData);
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


