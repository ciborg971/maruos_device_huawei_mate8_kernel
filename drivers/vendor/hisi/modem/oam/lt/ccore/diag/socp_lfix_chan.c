/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��      : Om.c
  �� �� ��      : ����
  ��    ��      : ����47350
  ��������      : 2008��5��3��
  ����޸�      :
  ��������      : ��C�ļ�������OMģ���ʵ��
  �����б�      :
  �޸���ʷ      :
  1.��    ��    : 2008��5��3��
    ��    ��    : ����47350
    �޸�����    : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"

#if (FEATURE_SAMPLE_LTE_CHAN == FEATURE_ON)
/*lint -e830 -e628*/
#include "SOCPInterface.h"
#include "BSP_SOCP_DRV.h"
#include "socp_lfix_chan.h"
#if((VOS_OS_VER == VOS_VXWORKS) || (VOS_OS_VER == VOS_RTOSCK))
#include "TLPhyInterface.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/
SOCP_ENCSRC_FIXCHAN_S g_stEncSrcFixChan[SOCP_CODER_SRC_BUTT];
VOS_INT32 g_armBaseAddr = 0;


VOS_UINT  DRV_SOCP_INIT_LTE_DSP(VOS_UINT ulChanId,VOS_UINT ulPhyAddr,VOS_UINT ulSize)
{
    SOCP_ENCSRC_FIXCHAN_S *pChan;

    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(ulChanId),(VOS_UINT)ulPhyAddr);
    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(ulChanId),(VOS_UINT)ulPhyAddr);
    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(ulChanId), (VOS_UINT)ulPhyAddr);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(ulChanId), 0, 27, ulSize);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(ulChanId), 27, 5, 0);

    /*����SOCP ����*/
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 1, 2, SOCP_ENCSRC_CHNMODE_CTSPACKET);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 4, 4, SOCP_DSPLOG_DST_BUFID);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 8, 2, SOCP_CHAN_PRIORITY_0);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 10, 1, SOCP_ENCSRC_BYPASS_DISABLE);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 16, 8, SOCP_DATA_TYPE_0);

    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 11, 1, SOCP_DATA_TYPE_EN);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 31, 1, SOCP_ENC_DEBUG_DIS);

    /* ʹ���ж�*/
    SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT1, ulChanId, 1, 1);
    SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, ulChanId, 1, 0);

    /* ���������ȫ�ֱ���*/

    pChan = &g_stEncSrcFixChan[ulChanId];
    pChan->u32ChanID               = ulChanId;
    pChan->u32DestChanID           = SOCP_DSPLOG_DST_BUFID;
    pChan->eChnMode                = SOCP_ENCSRC_CHNMODE_CTSPACKET;
    pChan->eDataType               = SOCP_DATA_TYPE_0;
    pChan->ePriority               = SOCP_CHAN_PRIORITY_0;
    pChan->sEncSrcBuf.u32Start     = (VOS_UINT)ulPhyAddr;
    pChan->sEncSrcBuf.u32Write     = (VOS_UINT)ulPhyAddr;
    pChan->sEncSrcBuf.u32End       = (VOS_UINT)(ulPhyAddr+ulSize);
    pChan->sEncSrcBuf.u32Read      = (VOS_UINT)ulPhyAddr;
    pChan->sEncSrcBuf.u32Length    = (VOS_UINT)ulSize;
    pChan->u32ChanEn               = SOCP_CHN_ENABLE;

    return VOS_OK;
}
/*****************************************************************************
* �� �� ��  :  DRV_SOCP_INIT_LTE_BBP_LOG
*
* ��������  : LTE BBPͨ����ʼ������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : �ͷųɹ����ı�ʶ��
*****************************************************************************/
VOS_UINT  DRV_SOCP_INIT_LTE_BBP_LOG(VOS_UINT ulChanId,VOS_UINT ulPhyAddr,VOS_UINT ulSize)
{
    SOCP_ENCSRC_FIXCHAN_S * pChan;
    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(ulChanId), ulPhyAddr);
    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(ulChanId), ulPhyAddr);
    SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(ulChanId), ulPhyAddr);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(ulChanId), 0, 27, ulSize);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(ulChanId), 27, 5, 0);

    /*����SOCP ����*/
    //SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 0, 1, 1);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 1, 2, SOCP_ENCSRC_CHNMODE_CTSPACKET);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 4, 4, SOCP_BBPLOG_DST_BUFID);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 8, 2, SOCP_CHAN_PRIORITY_0);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 10, 1, SOCP_ENCSRC_BYPASS_DISABLE);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 16, 8, SOCP_DATA_TYPE_0);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 11, 1, SOCP_DATA_TYPE_EN);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 31, 1, SOCP_ENC_DEBUG_DIS);

    /* ʹ���ж�*/
    SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT1, ulChanId, 1, 1);
    SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, ulChanId, 1, 0);

    pChan = &g_stEncSrcFixChan[ulChanId];

    pChan->u32ChanID               = ulChanId;
    pChan->u32DestChanID           = SOCP_BBPLOG_DST_BUFID;
    pChan->eChnMode                = SOCP_ENCSRC_CHNMODE_CTSPACKET;
    pChan->eDataType               = SOCP_DATA_TYPE_0;
    pChan->ePriority               = SOCP_CHAN_PRIORITY_0;
    pChan->sEncSrcBuf.u32Start     = ulPhyAddr;
    pChan->sEncSrcBuf.u32Write     = ulPhyAddr;
    pChan->sEncSrcBuf.u32Read      = ulPhyAddr;
    pChan->sEncSrcBuf.u32End       = ulPhyAddr + ulSize;
    pChan->sEncSrcBuf.u32Length    = (VOS_UINT)ulSize;
    pChan->u32ChanEn               = SOCP_CHN_ENABLE;

    return VOS_OK;
}
/*****************************************************************************
* �� �� ��  :  DRV_SOCP_INIT_LTE_BBP_DS
*
* ��������  : LTE BBPͨ����ʼ������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : �ͷųɹ����ı�ʶ��
*****************************************************************************/
VOS_UINT  DRV_SOCP_INIT_LTE_BBP_DS(VOS_UINT ulChanId,VOS_UINT ulPhyAddr,VOS_UINT ulSize)
{
   SOCP_ENCSRC_FIXCHAN_S * pChan;
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFADDR(ulChanId),ulPhyAddr);
	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFWPTR(ulChanId),ulPhyAddr);
   	SOCP_REG_WRITE(SOCP_REG_ENCSRC_BUFRPTR(ulChanId),ulPhyAddr);
	/*����SOCP ����*/
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(ulChanId), 0, 27, ulSize);
	SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG0(ulChanId), 27, 5, 0);

    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 1, 2, SOCP_ENCSRC_CHNMODE_FIXPACKET);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 4, 4, SOCP_BBPDS_DST_BUFID);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 8, 2, SOCP_CHAN_PRIORITY_0);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 10, 1, SOCP_ENCSRC_BYPASS_DISABLE);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 16, 8, SOCP_DATA_TYPE_0);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 11, 1, SOCP_DATA_TYPE_EN);
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 31, 1, SOCP_ENC_DEBUG_DIS);

    /* ����ͨ��Ĭ�ϲ��򿪣����ϲ�� */
    SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 0, 1, 0);

    /* ������ͨ���� �ж�*/
    SOCP_REG_SETBITS(SOCP_REG_ENC_RAWINT1, ulChanId, 1, 1);
    SOCP_REG_SETBITS(SOCP_REG_APP_MASK1, ulChanId, 1, 0);
    /* ���������ȫ�ֱ���*/
    pChan = &g_stEncSrcFixChan[ulChanId];
    pChan->u32ChanID               = ulChanId;
    pChan->u32DestChanID           = SOCP_BBPDS_DST_BUFID;
    pChan->eChnMode                = SOCP_ENCSRC_CHNMODE_FIXPACKET;
    pChan->eDataType               = SOCP_DATA_TYPE_0;
    pChan->ePriority               = SOCP_CHAN_PRIORITY_0;
    pChan->sEncSrcBuf.u32Start     = (VOS_UINT)ulPhyAddr;
    pChan->sEncSrcBuf.u32Write     = (VOS_UINT)ulPhyAddr;
    pChan->sEncSrcBuf.u32Read      = (VOS_UINT)ulPhyAddr;
    pChan->sEncSrcBuf.u32End       = (VOS_UINT)(ulPhyAddr+ulSize);
    pChan->sEncSrcBuf.u32Length    = (VOS_UINT)ulSize;
    return VOS_OK;

}

VOS_VOID DRV_SOCP_ENABLE_LTE_BBP_DSP(VOS_UINT ulChanId)
{
	if(0==(SOCP_REG_GETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 0, 1)))
	{
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(ulChanId), 0, 1, 1);
	}
}


/*****************************************************************************
* �� �� ��  : DRV_SOCP_DSPCHN_START
* ��������  : enable DSP channel
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
VOS_VOID  DRV_SOCP_DSPCHN_START(VOS_VOID)
{
	if(0==(SOCP_REG_GETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 0, 1)))
	{
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 0, 1, 1);
	}

}

/*****************************************************************************
* �� �� ��  : DRV_SOCP_DSPCHN_STOP
* ��������  : disable DSP channel
* �������  :
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
VOS_VOID  DRV_SOCP_DSPCHN_STOP(VOS_VOID)
{
	VOS_UINT32 IdleFlag;
       VOS_UINT32 j;

	if(SOCP_REG_GETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 0, 1))
	{
		SOCP_REG_SETBITS(SOCP_REG_ENCSRC_BUFCFG1(SOCP_DSPLOG_CHN), 0, 1, 0);
	}
/*lint -e525 -e746*/
	for (j = 0; j < (SOCP_RESET_TIME*2); j++)
    {
        IdleFlag = SOCP_REG_GETBITS(SOCP_REG_ENCSTAT, SOCP_DSPLOG_CHN, 1);
        if (0 == IdleFlag)
        {
            break;
        }

        if ((SOCP_RESET_TIME - 1) == j)
        {
            vos_printf("bsp_socp_stop_dsp failed!\n");

			return ;
        }
    }
/*lint +e525 +e746*/
}

VOS_VOID  SOCP_EnableLFixChan(VOID)
{
}
VOS_VOID SOCP_LFixChan_Init(VOS_VOID)
{
}
/*lint +e830 +e628*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


