

#include <msp_errno.h>
#include <osm.h>
#include <gen_msg.h>
#include <ftm.h>
#include "LMspLPhyInterface.h"
#include "ftm_ct.h"
/*lint -save -e537*/
#include <AppRrcInterface.h>
#include "TafAppMma.h"
/*lint -restore*/
#include "Tds_ps_at.h"

#include "TPsTMspInterface.h"
#include "ftm_mntn.h"
/*lint --e{830,539,525}*/

/*lint -e767*/
#define    THIS_FILE_ID        MSP_FILE_ID_FTM_BASE_CMD_C
/*lint -e767*/

#if (VOS_OS_VER == VOS_WIN32)
static VOS_BOOL g_PomDspInitIsOK = TRUE;
#else
static VOS_BOOL g_PomDspInitIsOK = FALSE;
#endif

extern VOS_VOID LPHY_SetBTBandInd(VOS_UINT8 ucBand);
extern VOS_VOID LPHY_GetBandStatus(VOS_UINT8 *pucBand, VOS_UINT8 *pucMode);

/*lint -save -e958 -e713 -e718 -e746 -e734*/
/*****************************************************************************
 ��������: pom_GetDspInitFlg
 ��������: ����DSP��д���

 ����˵��:
  NONE

 �� �� ֵ:
    �ɹ���ERR_MSS_SUCCESS: ��ʾ�����ɹ�
    ʧ�ܣ�ERR_MSS_INVALID_PARAMETER��ERR_MSS_NO_INITILIZATION�� ERR_MSS_UNKNOWN
          ����ʧ��
*****************************************************************************/
/* ��¼UE_ROOT�����ķ��������������ȷ��DSP�Ѿ���ʼ���ɹ���*/
/* DRA����ſ�ʼ����DSP���䣻*/
VOS_BOOL pom_GetDspInitFlg(VOS_VOID)
{
/* ��MSP_SUPPORT_HPA_STUB�궨�嶨��˴�����*/
#if(VOS_OS_VER == VOS_WIN32)
    g_PomDspInitIsOK = TRUE;
#else

    if( LRRC_COMM_LoadDspAlready() == TRUE)
    {
        g_PomDspInitIsOK = TRUE;
    }
    else
    {
        g_PomDspInitIsOK = FALSE;
    }
#endif
    return g_PomDspInitIsOK;
}
/* E*/

/*****************************************************************************
 �� �� ��  : at_ftm_tmode_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOID at_ftm_tmode_store(VOS_UINT8 ucStoreType, SYM_SET_TMODE_REQ_STRU* pstReq)
{
    static SYM_SET_TMODE_REQ_STRU stReq = { 0 };
    SYM_TMODE_ENUM* pSymTmode           = ftm_GetTmodeMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL!=pstReq))
    {
        stReq.enTmodeMode = pstReq->enTmodeMode;
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        *pSymTmode = stReq.enTmodeMode;
    }
}
/*lint -save -e550 */
/*****************************************************************************
 �� �� ��  : at_ftm_bandsw_setcnf
 ��������  : ����ȷ��
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_tmode_setcnf(VOS_UINT32 ulErrCode)
{
    SYM_SET_TMODE_CNF_STRU stSetCnf = { 0 };

    stSetCnf.enTmodeMode   = *ftm_GetTmodeMainInfo();
    stSetCnf.enSymTmodeSta = 1; /* switch mode completely */
    stSetCnf.ulErrCode     = ulErrCode;

    return ftm_comm_send(ID_MSG_SYM_SET_TMODE_CNF,
        (VOS_UINT32)&stSetCnf, sizeof(SYM_SET_TMODE_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_bandsw_read
 ��������  : ID_MSG_SYM_RD_TMODE_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_tmode_read(VOS_VOID* pParam)
{
    SYM_RD_TMODE_CNF_STRU stRdCnf = { 0 };
    stRdCnf.ulErrCode     = ERR_MSP_SUCCESS;
    stRdCnf.enTmodeMode   = *ftm_GetTmodeMainInfo();
    stRdCnf.enSymTmodeSta = 1; /* switch mode completely */

    return ftm_comm_send(ID_MSG_SYM_RD_TMODE_CNF,
        (VOS_UINT32)&stRdCnf, sizeof(SYM_RD_TMODE_CNF_STRU));
}
/*lint -restore*/

/*****************************************************************************
 �� �� ��  : at_ftm_tmode_set
 ��������  : ���ù���ģʽ
 �������  :
 �������  :
 �� �� ֵ  :
*****************************************************************************/
extern	VOS_UINT32 TDS_CBT_SetSlaveModeThenMasterMode( VOS_VOID );

extern VOS_UINT32 g_ulTdsDelayLen;
extern 	VOS_VOID TDS_CBT_SetSlaveMode( VOS_VOID );
extern 	VOS_VOID TDS_CBT_SetMasterMode( VOS_VOID );

VOS_UINT32 at_ftm_tmode_set(VOS_VOID* pParam)
{
    SYM_SET_TMODE_REQ_STRU* pstFtmReq = (SYM_SET_TMODE_REQ_STRU*)pParam;
    FTM_SYN_INFO_STRU* pFtmSynINfo    = ftm_GetSynMainInfo();
    SYM_TMODE_ENUM*    pSymTmode      = ftm_GetTmodeMainInfo();
    OM_PHY_CT_TEST_MODE_REQ_STRU stReqDspTmode = {0};
    MSP_PS_AT_MODE_REQ_STRU  stReqPsTm = {0};

    HAL_SDMLOG("\n at_ftm_tmode_set, old tmode: %d, new tmode %d\n", *pSymTmode, pstFtmReq->enTmodeMode);

    switch(pstFtmReq->enTmodeMode)
    {
        case EN_SYM_TMODE_SIGNAL:         //TMODE=0  signaling mode
        {
           *pSymTmode = pstFtmReq->enTmodeMode;
            return at_ftm_tmode_setcnf(ERR_MSP_SUCCESS);
        }

        case EN_SYM_TMODE_NONESIGNAL:     /* TMODE=1  non-signaling mode    */
            /* ���÷������ */
             ftm_SetNoneSig(FTM_NONESIG_RTT_OPEN);
             ftm_SetDefault();
             *pSymTmode = pstFtmReq->enTmodeMode;
             return at_ftm_tmode_setcnf(ERR_MSP_SUCCESS);

        case EN_SYM_TMODE_F_NONESIGNAL:   /* TMODE=13 quick calibration mode */
        case EN_SYM_TMODE_SYN_NONESIGNAL: /* TMODE=14 non-signaling BT mode  */
        {
            /* ���LRTT�ĳ�ʼ��״̬ */
            if (pom_GetDspInitFlg() == FALSE)
            {
                return at_ftm_tmode_setcnf(ERR_MSP_INVALID_OP);
            }

            if (ERR_MSP_SUCCESS != LHPA_InitDspNvForLteTdsCBT())
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] LHPA_InitDspNvForLteTdsCBT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_MSP_INVALID_OP);
            }

            if(ERR_MSP_SUCCESS != LHPA_LoadDspForLteCBT())
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] LHPA_LoadDspForLteCBT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_MSP_INVALID_OP);
            }

			TDS_CBT_SetSlaveMode();
		

            /*  �л�LRTTΪ��ģ */
            LHPA_DbgSetSlaveModeThenMasterMode();
            HAL_SDMLOG("\n call LHPA_DbgSetSlaveModeThenMasterMode! \n");
            //VOS_TaskDelay(300);

            /* ����ԭ�ﵽLRTT����Ϊ������ģʽ */
            stReqDspTmode.ulMsgId = OM_PHY_CT_TEST_MODE_REQ;
            stReqDspTmode.usTMode = pstFtmReq->enTmodeMode;
            if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqDspTmode, sizeof(OM_PHY_CT_TEST_MODE_REQ_STRU)))
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] ftm_mailbox_ltect_write failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_MSP_UNKNOWN);
            }

            if(EN_SYM_TMODE_SYN_NONESIGNAL == pstFtmReq->enTmodeMode)
            {
                pFtmSynINfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_TMODE_7_REQ;
            }

            at_ftm_tmode_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
            return ERR_MSP_WAIT_ASYNC;
        }
            
        case EN_SYM_TMODE_COMM_CT: /* TMODE=19 comm non-signaling CT mode  */
        {
            /* ���LRTT�ĳ�ʼ��״̬ */
            if (pom_GetDspInitFlg() == FALSE)
            {
                return at_ftm_tmode_setcnf(ERR_MSP_INVALID_OP);
            }

            if(ERR_MSP_SUCCESS != LHPA_LoadDspForLteCBT())
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] LHPA_LoadDspForLteCBT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_MSP_INVALID_OP);
            }

			TDS_CBT_SetSlaveMode();


            /*  �л�LRTTΪ��ģ */
            LHPA_DbgSetSlaveModeThenMasterMode();
            HAL_SDMLOG("\n call LHPA_DbgSetSlaveModeThenMasterMode! \n");
            //VOS_TaskDelay(300);

            /* ����ԭ�ﵽLRTT����Ϊ������ģʽ */
            stReqDspTmode.ulMsgId = OM_PHY_CT_TEST_MODE_REQ;
            stReqDspTmode.usTMode = pstFtmReq->enTmodeMode;
            if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqDspTmode, sizeof(OM_PHY_CT_TEST_MODE_REQ_STRU)))
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] ftm_mailbox_ltect_write failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_MSP_UNKNOWN);
            }

            at_ftm_tmode_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
            return ERR_MSP_WAIT_ASYNC;
        }

        case EN_SYM_TMODE_TDS_BT:
        {
            /*at^tmode=18 ��Ҫ֪ͨPS*/
            stReqPsTm.MsgId = ID_T_MSP_PS_AT_MODE_REQ;

            if(ERR_MSP_SUCCESS != atFTMSendVosMsg(TPS_PID_MAC,&stReqPsTm,sizeof(stReqPsTm)))
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] atFTMSendVosMsg failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_MSP_UNKNOWN);
		    }

            if (ERR_MSP_SUCCESS != LHPA_InitDspNvForLteTdsCBT())
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] LHPA_InitDspNvForLteTdsCBT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_MSP_INVALID_OP);
            }

            LHPA_DbgSendSetWorkMode_toSlaveMode();
            (VOS_VOID)VOS_TaskDelay(g_ulTdsDelayLen);

            (VOS_VOID)TDS_CBT_SetSlaveModeThenMasterMode();

            /* ����ԭ�ﵽDSP����Ϊ������ģʽ */
            stReqDspTmode.ulMsgId = OM_PHY_CT_TEST_MODE_REQ;
            stReqDspTmode.usTMode = pstFtmReq->enTmodeMode;

            /*  MODE  �ȷ���TDS BT ��������Ҫ����LTEBT */
            if(ERR_MSP_SUCCESS != ftm_mailbox_bt_write(EN_FCHAN_MODE_TD_SCDMA, &stReqDspTmode, sizeof(OM_PHY_CT_TEST_MODE_REQ_STRU)))
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] ftm_mailbox_bt_write failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_MSP_UNKNOWN);
            }

            /* �ο�TMODE=14�ӵģ�GETNOSIG ʱ���ж�  ��֮����--��ȷ�� */
            if(EN_SYM_TMODE_TDS_BT == pstFtmReq->enTmodeMode)
            {
                pFtmSynINfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_TMODE_7_REQ;//  ---��ȷ��
            }

            at_ftm_tmode_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
            return ERR_MSP_WAIT_ASYNC;
				
	    }
        
        case EN_SYM_TMODE_TDS_FAST_CT:
        {
			//TDS_CBT_SetSlaveModeThenMasterMode();

            if (ERR_MSP_SUCCESS != LHPA_InitDspNvForLteTdsCBT())
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] LHPA_InitDspNvForLteTdsCBT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_MSP_INVALID_OP);
            }

			LHPA_DbgSendSetWorkMode_toSlaveMode();
			
			(VOS_VOID)VOS_TaskDelay(g_ulTdsDelayLen);			

			(VOS_VOID)TDS_CBT_SetSlaveModeThenMasterMode();
			
            /* ����ԭ�ﵽLRTT����Ϊ������ģʽ */
            stReqDspTmode.ulMsgId = OM_PHY_CT_TEST_MODE_REQ;
            stReqDspTmode.usTMode = pstFtmReq->enTmodeMode;
            if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(EN_FCHAN_MODE_TD_SCDMA, &stReqDspTmode, sizeof(OM_PHY_CT_TEST_MODE_REQ_STRU)))
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] ftm_mailbox_ct_write failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_tmode_setcnf(ERR_MSP_UNKNOWN);
            }
            at_ftm_tmode_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
            return ERR_MSP_WAIT_ASYNC;
        }
            
        case EN_SYM_TMODE_SIGNAL_NOCARD:  /* TMODE=11 signaling with no card mode */
        {
            *pSymTmode = pstFtmReq->enTmodeMode;
            return at_ftm_tmode_setcnf(ERR_MSP_SUCCESS);
        }


        case EN_SYM_TMODE_SET_SLAVE:      /* TMODE=15 set LTE DSP to slave mode */
        case EN_SYM_TMODE_GU_BT:
        {
            LHPA_DbgSendSetWorkMode_toSlaveMode();
            HAL_SDMLOG("\n call LHPA_DbgSendSetWorkMode_toSlaveMode\n");

            /* delay for mode switch */
            (VOS_VOID)VOS_TaskDelay(300);

            *pSymTmode = pstFtmReq->enTmodeMode;
            return at_ftm_tmode_setcnf(ERR_MSP_SUCCESS);
        }

        case EN_SYM_TMODE_RESET:          /* TMODE=3 */
        {
            *pSymTmode = pstFtmReq->enTmodeMode;
            (VOS_VOID)VOS_TaskDelay(300);
            //BSP_OM_SoftReboot();
        }
            break;

        case EN_SYM_TMODE_LOAD:           /* TMODE=2 */
        case EN_SYM_TMODE_SHUTDOWN:       /* TMODE=4 */
        case EN_SYM_TMODE_OFFLINE:        /* TMODE=12 */
            (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] Error Mode\n", __FUNCTION__, __LINE__,VOS_GetSlice());
            return ERR_MSP_FAILURE;

        default:
            ;
    }

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_tmode_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_tmode_timeout(VOS_VOID)
{
#ifdef BSP_CONFIG_HI3650
    /* ����Ҫ����Ӵ˹��ܷ��㶨λDSP���⣬������ʧ��һ��ϵͳ������ */
    mdrv_om_system_error(MSP_REBOOT_FTM_ERR, THIS_FILE_ID, __LINE__, 0, 0);
#endif
    
    return at_ftm_tmode_setcnf(ERR_MSP_OPEN_CHAN_ERROR);
}

/*****************************************************************************
 �� �� ��  : at_ftm_tmode_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_TEST_MODE_CNF������
 �������  : pParam PHY_OM_CT_TEST_MODE_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_tmode_dspcnf(VOS_VOID* pParam)
{
    at_ftm_tmode_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    /* ���÷������ */
    ftm_SetNoneSig(FTM_NONESIG_RTT_OPEN);
    ftm_SetDefault();

    return at_ftm_tmode_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_bandsw_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOID at_ftm_bandsw_store(VOS_UINT8 ucStoreType, FTM_SET_BANDSW_REQ_STRU* pstReq)
{
    static FTM_SET_BANDSW_REQ_STRU stReq = {0};
    FTM_CT_F_MANAGE_INFO_STRU *pstFCtMainInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_BANDSW_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFCtMainInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_BANDSW;
        pstFCtMainInfo->enCurMode = stReq.enMode;
        pstFCtMainInfo->ucCurBand = stReq.ucBand;/*BandSwith ID*/

        ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode = stReq.enMode;
    }

    return ;
}
/*lint -save -e550 */
/*****************************************************************************
 �� �� ��  : at_ftm_bandsw_setcnf
 ��������  : ����ȷ��
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_bandsw_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_BANDSW_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_BANDSW_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_BANDSW_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_bandsw_read
 ��������  : ID_MSG_FTM_RD_BANDSW_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_bandsw_read(VOS_VOID* pParam)
{
    VOS_UINT8 ucBandPs = 0;
    VOS_UINT8 ucModePs = 0;
    FTM_RD_BANDSW_CNF_STRU stRdCnf = { 0 };
    FCHAN_MODE_ENUM* penCurMode = &ftm_GetFastCTMainInfo()->enCurMode;
    VOS_UINT8*       pucCurBand = &ftm_GetFastCTMainInfo()->ucCurBand;
    stRdCnf.ulErrCode           = ERR_MSP_SUCCESS;

    /* ����ȱ��, LPHY_GetBandStatusֻ����δ����at^bandsw=*,*���״ε���at^bandsw?��Ч */
    /* at^bandsw=*,*���ú��at^bandsw?�Ի�������Ϊ׼                                 */
    if((*penCurMode==EN_FCHAN_MODE_UNKONWN) && (*pucCurBand==255))
    {
        /* ��Э��ջ��õ�ǰƵ����Ϣ */
        #if !defined(CHIP_BB_HI6210)
        LPHY_GetBandStatus((VOS_UINT8 *)&ucBandPs, (VOS_UINT8 *)&ucModePs);
        #endif
        if(ERR_MSP_SUCCESS!=at_ftm_getLteBandswId(ucBandPs, pucCurBand, penCurMode))
        {
            stRdCnf.ulErrCode = ERR_MSP_BNADSW_ERROR;
            *pucCurBand       = 255;
            *penCurMode       = EN_FCHAN_MODE_UNKONWN;
        }
     }

     stRdCnf.ucBand    = *pucCurBand ;
     stRdCnf.enMode    = *penCurMode;

     return ftm_comm_send(ID_MSG_FTM_RD_BANDSW_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_BANDSW_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_bandsw_set
 ��������  : ID_MSG_FTM_SET_BANDSW_REQ ������
             ����LTEƵ���л�
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_bandsw_set(VOS_VOID* pParam)
{
    VOS_UINT8 ucBand = 0;
    FTM_SET_BANDSW_REQ_STRU* pstFtmReq         = (FTM_SET_BANDSW_REQ_STRU*)pParam;
    OM_PHY_CT_F_BANDSW_SET_REQ_STRU stReqToDsp = { 0 };
    SYM_TMODE_ENUM symTmode = *ftm_GetTmodeMainInfo();
    
    /* �ж��Ƿ�Ϊ��Ч��ʽ(FDD_LTE��TDD_LTE TDSCDMA) */
    if((pstFtmReq->enMode!=EN_FCHAN_MODE_FDD_LTE)
        && (pstFtmReq->enMode!=EN_FCHAN_MODE_TDD_LTE)
        && (pstFtmReq->enMode!=EN_FCHAN_MODE_TD_SCDMA))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] nknown mode\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_bandsw_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
    
    /* ͨ��BandSwitch ID���Band ID */
    if(ERR_MSP_SUCCESS != at_ftm_getBandID(pstFtmReq->enMode, pstFtmReq->ucBand, &ucBand))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] get bandid failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_bandsw_setcnf(ERR_MSP_INVALID_PARAMETER);
    }

    if(ftm_GetNoneSig()!= FTM_NONESIG_RTT_OPEN )
    {
        /* �޿�����ģʽ(TMODE=11)Ƶ���л���ֱ�ӵ���PS���� */
        if(symTmode==EN_SYM_TMODE_SIGNAL_NOCARD)
        {
          at_ftm_bandsw_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
          at_ftm_bandsw_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);
          #if !defined(CHIP_BB_HI6210)
          LPHY_SetBTBandInd(ucBand);
          #endif
          return at_ftm_bandsw_setcnf(ERR_MSP_SUCCESS);
        }
    }
    else
    {
        /* ������ģʽ(TMODE=1,13,14)Ƶ���л��������л�ԭ���DSP */
        stReqToDsp.ulMsgId  = OM_PHY_CT_F_BANDSW_SET_REQ;
        stReqToDsp.usMode = pstFtmReq->enMode;
        stReqToDsp.usBand = ucBand;
        stReqToDsp.usDLFreq = at_ftm_get_freq(pstFtmReq->enMode, pstFtmReq->usDlCh);
        stReqToDsp.usUlFreq = at_ftm_get_freq(pstFtmReq->enMode, pstFtmReq->usUlCh);
		/*lint -save -e553 */
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
		stReqToDsp.usDlAbbChanIndex = pstFtmReq->usDlAbbChanIndex;
#endif
		/*lint -restore*/

		if(EN_SYM_TMODE_TDS_BT == symTmode)
		{   /* ��ȷ��-�����Դ����mode ���ж�BT /CT �� */

		     if(ERR_MSP_SUCCESS!=ftm_mailbox_bt_write(pstFtmReq->enMode, &stReqToDsp, sizeof(OM_PHY_CT_F_BANDSW_SET_REQ_STRU)))
		     {
                 (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_bt_write fail\n", __FUNCTION__, __LINE__,VOS_GetSlice());
		         return at_ftm_bandsw_setcnf(ERR_MSP_UNKNOWN);
		     }
		}
        else if (EN_SYM_TMODE_COMM_CT == symTmode)/*TMODE=19ʱ���뷢��LTE����*/
        {
            if (ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_CT_F_BANDSW_SET_REQ_STRU)))
            {
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ltect_write fail\n", __FUNCTION__, __LINE__,VOS_GetSlice());
                return at_ftm_bandsw_setcnf(ERR_MSP_UNKNOWN);
            }
        }
		else
		{
	        if(ERR_MSP_SUCCESS!=ftm_mailbox_ct_write(pstFtmReq->enMode, &stReqToDsp, sizeof(OM_PHY_CT_F_BANDSW_SET_REQ_STRU)))
	        {
                
                (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ct_write fail\n", __FUNCTION__, __LINE__,VOS_GetSlice());
	            return at_ftm_bandsw_setcnf(ERR_MSP_UNKNOWN);
	        }
		}

        at_ftm_bandsw_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
        return ERR_MSP_WAIT_ASYNC;
    }

    return at_ftm_bandsw_setcnf(ERR_MSP_UE_MODE_ERR);
}

/*****************************************************************************
 �� �� ��  : at_ftm_bandsw_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_bandsw_timeout(VOS_VOID)
{
    return at_ftm_bandsw_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fchan_setcnf
 ��������  : ����ȷ��
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fchan_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FCHAN_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode   = ulErrCode;
    stCnf.enFchanMode = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;

    return ftm_comm_send(ID_MSG_FTM_SET_FCHAN_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FCHAN_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_bandsw_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_BANDSW_SET_CNF������
             �����AT^BANDSW���͵�Ƶ���л��򷵻�BANDSWȷ��
             �����AT^FCAHN���͵�Ƶ���л��򷵻�FCHANȷ��
 �������  : pParam PHY_OM_CT_TSELRF_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_bandsw_dspcnf(VOS_VOID* pParam)
{
    at_ftm_bandsw_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_bandsw_setcnf(ERR_MSP_SUCCESS);
    
}

/*****************************************************************************
 �� �� ��  : at_ftm_fchan_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fchan_store(VOS_UINT8 ucStoreType, FTM_SET_FCHAN_REQ_STRU* pstReq)
{
    static FTM_SET_FCHAN_REQ_STRU stReq = {0};
    FTM_CT_MANAGE_INFO_STRU* pstFCtManageInfo = &ftm_GetMainInfo()->stFtmCtInfo;

    VOS_UINT16 usUlChannel = 65535; /* ����Ƶ��Ĭ��Ϊ��Чֵ */
    VOS_UINT16 usDlChannel = 65535; /* ����Ƶ��Ĭ��Ϊ��Чֵ */

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FCHAN_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFCtManageInfo->stCurFchan.enFchanMode = stReq.enFchanMode;
        pstFCtManageInfo->stCurFchan.ucBand      = stReq.ucBand;
        pstFCtManageInfo->stCurFchan.usUlChannel = usUlChannel;
        pstFCtManageInfo->stCurFchan.usDlChannel = usDlChannel;

        ftm_GetMainInfo()->stFtmFastCtInfo.enCurMode = stReq.enFchanMode;

        if(stReq.enFchanMode == EN_FCHAN_MODE_TD_SCDMA)
        {
            /* TDSCDMA������Ƶ����� */
            pstFCtManageInfo->stCurFchan.usUlChannel = stReq.usChannel;/* [false alarm]:fortify */
            pstFCtManageInfo->stCurFchan.usDlChannel = stReq.usChannel;
        }
        else
        {
            /* ����Ƶ��������Ƶ������򱣴�����Ƶ�㣬��������Ƶ��Ϊ��Чֵ */
            usUlChannel = at_ftm_get_ulchan(EN_FCHAN_MODE_FDD_LTE, stReq.usChannel);
            /* coverity[original] */
            if(stReq.usChannel == usUlChannel)
            {
                pstFCtManageInfo->stCurFchan.usUlChannel = usUlChannel;
            }

            /*����Ƶ��������Ƶ������򱣴�����Ƶ�㣬��������Ƶ��Ϊ��Чֵ */
            usDlChannel = at_ftm_get_dlchan(EN_FCHAN_MODE_FDD_LTE, stReq.usChannel);
            /* coverity[copy_paste_error] */
            if(stReq.usChannel == usUlChannel)
            {
                pstFCtManageInfo->stCurFchan.usDlChannel = usDlChannel;
            }
        }
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fchan_read
 ��������  : ID_MSG_FTM_RD_FCHAN_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fchan_read(VOS_VOID* pParam)
{
    FTM_RD_FCHAN_CNF_STRU stRdCnf = { 0 };
    FTM_RD_FCHAN_CNF_STRU* pstSavedRdCnf = &ftm_GetMainInfo()->stFtmCtInfo.stCurFchan;

    stRdCnf.ulErrCode   = ERR_MSP_SUCCESS;
    stRdCnf.enFchanMode = pstSavedRdCnf->enFchanMode;
    stRdCnf.ucBand      = pstSavedRdCnf->ucBand;
    stRdCnf.usUlChannel = pstSavedRdCnf->usUlChannel;
    stRdCnf.usDlChannel = pstSavedRdCnf->usDlChannel;

     return ftm_comm_send(ID_MSG_FTM_RD_FCHAN_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_FCHAN_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fchan_set
 ��������  : ID_MSG_FTM_SET_FCHAN_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fchan_set(VOS_VOID* pParam)
{
    FTM_SET_FCHAN_REQ_STRU* pstFtmReq       = (FTM_SET_FCHAN_REQ_STRU*)pParam;
    OM_PHY_CT_FREQ_SET_REQ_STRU stReqToDsp  = { 0 };
    VOS_UINT8  ucBand;
    VOS_UINT16 usUlChan = 0;
    VOS_UINT16 usDlChan = 0;    

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if (ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] FTM_NONESIG_RTT_CLOSE\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_fchan_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    if(pstFtmReq->enFchanMode == EN_FCHAN_MODE_TD_SCDMA)
    {
        /* ��LRTT��ģ */
        LHPA_DbgSendSetWorkMode_toSlaveMode();
        (VOS_VOID)VOS_TaskDelay(100);

        /* ��TRTT��ģ */
        TDS_CBT_SetSlaveMode();    

        /* ��TRTTΪ��ģ */
        TDS_CBT_SetMasterMode();
    }
    else
    {
        /* ��LRTT��ģ */
         LHPA_DbgSendSetWorkMode_toSlaveMode();  
         (VOS_VOID)VOS_TaskDelay(100);  

        /* ��TRTT��ģ */
        TDS_CBT_SetSlaveMode();        
        
        /*  �л�LRTTΪ��ģ */
		LHPA_DbgSendSetWorkMode_toMaterMode();
		(VOS_VOID)VOS_TaskDelay(100);
    }

    usUlChan = at_ftm_get_ulchan(pstFtmReq->enFchanMode, pstFtmReq->usChannel);
    usDlChan = at_ftm_get_dlchan(pstFtmReq->enFchanMode, pstFtmReq->usChannel);
    if(ERR_MSP_SUCCESS != at_ftm_getBandID(pstFtmReq->enFchanMode, pstFtmReq->ucBand, &ucBand))
    {
         (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] at_ftm_getBandID failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
         return at_ftm_fchan_setcnf(ERR_MSP_INVALID_PARAMETER);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId   = OM_PHY_CT_FREQ_SET_REQ;
    stReqToDsp.usMode    = pstFtmReq->enFchanMode;  
    stReqToDsp.usBandNum = ucBand;
    stReqToDsp.usUlFreq  = at_ftm_get_freq(pstFtmReq->enFchanMode, usUlChan);
    stReqToDsp.usDlFreq  = at_ftm_get_freq(pstFtmReq->enFchanMode, usDlChan);

    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(pstFtmReq->enFchanMode, &stReqToDsp, sizeof(OM_PHY_CT_FREQ_SET_REQ_STRU)))
    {
        
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] ftm_mailbox_ct_write failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_fchan_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fchan_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fchan_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fchan_timeout(VOS_VOID)
{
    return at_ftm_fchan_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fchan_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_FREQ_SET_CNF������
             ��DSP����ԭ�����Ƶ���л�
 �������  : pParam PHY_OM_CT_FREQ_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fchan_dspcnf(VOS_VOID* pParam)
{
    at_ftm_fchan_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);
    return at_ftm_fchan_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_tselrf_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_tselrf_store(VOS_UINT8 ucStoreType, FTM_SET_TSELRF_REQ_STRU* pstReq)
{
    static FTM_SET_TSELRF_REQ_STRU stReq = {0};

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if ((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_TSELRF_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        (ftm_GetMainInfo()->stFtmCtInfo).ucTselrfPath = stReq.ucPath;
        (ftm_GetMainInfo()->stFtmCtInfo).ucTselrfGroup = stReq.ucGroup;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_tselrf_setcnf
 ��������  : ����ȷ��
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_tselrf_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_TSELRF_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_TSELRF_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_TSELRF_CNF_STRU));
}
/*lint -restore*/

/*****************************************************************************
 �� �� ��  : at_ftm_tselrf_set
 ��������  : ID_MSG_FTM_SET_TSELRF_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_tselrf_set(VOS_VOID* pParam)
{
    FTM_SET_TSELRF_REQ_STRU* pstFtmReq       = (FTM_SET_TSELRF_REQ_STRU*)pParam;
    OM_PHY_CT_TSELRF_SET_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM emFchanMode              = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;
    
    /* �жϲ�����Ч�� */
    if((pstFtmReq->ucPath     != FTM_TSELRF_TD)
        && (pstFtmReq->ucPath != FTM_TSELRF_FDD_LTE_MAIN)
        && (pstFtmReq->ucPath != FTM_TSELRF_TDD_LTE_MAIN)
        && (pstFtmReq->ucPath != FTM_TSELRF_FDD_LTE_SUB)
        && (pstFtmReq->ucPath != FTM_TSELRF_TDD_LTE_SUB))
    {
        return at_ftm_tselrf_setcnf(ERR_MSP_INVALID_OP);
    }

    /* �ж��Ƿ��ڷ�����ģʽ */
    if (ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] FTM_NONESIG_RTT_CLOSE\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_tselrf_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    stReqToDsp.ulMsgId = OM_PHY_CT_TSELRF_SET_REQ;

    if((pstFtmReq->ucPath    == FTM_TSELRF_FDD_LTE_MAIN)
        ||(pstFtmReq->ucPath == FTM_TSELRF_TDD_LTE_MAIN))
    {
        stReqToDsp.ucPath = FTM_RXANT_OPEN_CHAN1;
        stReqToDsp.ucGroup= FTM_RXANT_TYPE_RX;
    }
    else if((pstFtmReq->ucPath == FTM_TSELRF_FDD_LTE_SUB)
        || (pstFtmReq->ucPath == FTM_TSELRF_TDD_LTE_SUB))
    {
        stReqToDsp.ucPath = FTM_RXANT_OPEN_CHAN2;
        stReqToDsp.ucGroup= FTM_RXANT_TYPE_RX;
    }
    else /* FTM_TSELRF_TD */ 
    {
        stReqToDsp.ucGroup = 0xFF;
        stReqToDsp.ucPath  = pstFtmReq->ucPath;
    }
            
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(emFchanMode, &stReqToDsp, sizeof(OM_PHY_CT_TSELRF_SET_REQ_STRU)))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] ftm_mailbox_ct_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_tselrf_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_tselrf_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_tselrf_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_tselrf_timeout(VOS_VOID)
{
    return at_ftm_tselrf_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_tselrf_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_TSELRF_SET_CNF������
 �������  : pParam PHY_OM_CT_TSELRF_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_tselrf_dspcnf(VOS_VOID* pParam)
{
    at_ftm_tselrf_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);
    return at_ftm_tselrf_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_ftxon_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOID at_ftm_ftxon_store(VOS_UINT8 ucStoreType, FTM_SET_TXON_REQ_STRU* pstReq)
{
    static FTM_SET_TXON_REQ_STRU stReq = {0};
    FTM_CT_MANAGE_INFO_STRU* pstFCtManageInfo = &ftm_GetMainInfo()->stFtmCtInfo;

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_TXON_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFCtManageInfo->enCurTxon = stReq.enSwtich;
    }

    return ;
}
/*lint -save -e550 */
/*****************************************************************************
 �� �� ��  : at_ftm_ftxon_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ftxon_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_TXON_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_TXON_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_TXON_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_ftxon_read
 ��������  : ID_MSG_FTM_RD_TXON_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ftxon_read(VOS_VOID* pParam)
{
    FTM_RD_TXON_CNF_STRU stRdCnf = { 0 };
    FTM_TXON_SWT_ENUM enCurTxon  = ftm_GetMainInfo()->stFtmCtInfo.enCurTxon;

    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    stRdCnf.enSwtich  = enCurTxon;

     return ftm_comm_send(ID_MSG_FTM_RD_TXON_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_TXON_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_ftxon_set
 ��������  : ID_MSG_FTM_SET_TXON_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ftxon_set(VOS_VOID* pParam)
{
    FTM_SET_TXON_REQ_STRU* pstFtmReq   = (FTM_SET_TXON_REQ_STRU*)pParam;
    OM_PHY_CT_TXON_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode          = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]FTM_NONESIG_RTT_CLOSE\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_ftxon_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* �жϲ����Ƿ�Ϊ��Ч���� */
    if((pstFtmReq->enSwtich != EN_FTM_TXON_CLOSE)
        && (pstFtmReq->enSwtich !=  EN_FTM_TXON_UL_RFBBP_OPEN)
        && (pstFtmReq->enSwtich !=  EN_FTM_TXON_RF_PA_OPEN))
    {
        
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ERR_MSP_INVALID_PARAMETER\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_ftxon_setcnf(ERR_MSP_INVALID_PARAMETER);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId  = OM_PHY_CT_TXON_REQ;
    stReqToDsp.usTxType = (VOS_UINT16)pstFtmReq->enSwtich;
    
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_TXON_REQ_STRU)))
    {
      (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ct_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_ftxon_setcnf(ERR_MSP_UNKNOWN);
    }    

    at_ftm_ftxon_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_ftxon_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ftxon_timeout(VOS_VOID)
{
    return at_ftm_ftxon_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_ftxon_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_TXON_CNF������
 �������  : pParam PHY_OM_CT_TXON_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ftxon_dspcnf(VOS_VOID* pParam)
{
    at_ftm_ftxon_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_ftxon_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_frxon_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOID at_ftm_frxon_store(VOS_UINT8 ucStoreType, FTM_SET_RXON_REQ_STRU* pstReq)
{
    static FTM_SET_RXON_REQ_STRU stReq = {0};
    FTM_CT_MANAGE_INFO_STRU* pstFCtManageInfo = &ftm_GetMainInfo()->stFtmCtInfo;

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_RXON_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFCtManageInfo->enCurRxon = stReq.ulRxSwt;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_frxon_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_frxon_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_RXON_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_RXON_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_RXON_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_frxon_read
 ��������  : ID_MSG_FTM_RD_TXON_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_frxon_read(VOS_VOID* pParam)
{
    FTM_RD_RXON_CNF_STRU stRdCnf = { 0 };
    FTM_RXON_SWT_ENUM enCurRxon = ftm_GetMainInfo()->stFtmCtInfo.enCurRxon;

    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    stRdCnf.ulRxSwt= enCurRxon;

     return ftm_comm_send(ID_MSG_FTM_RD_RXON_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_RXON_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_frxon_set
 ��������  : ID_MSG_FTM_SET_RXON_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_frxon_set(VOS_VOID* pParam)
{
    FTM_SET_RXON_REQ_STRU* pstFtmReq   = (FTM_SET_RXON_REQ_STRU*)pParam;
    OM_PHY_CT_RXON_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode          = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]FTM_NONESIG_RTT_CLOSE\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_frxon_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* �жϲ����Ƿ�Ϊ��Ч���� */
    if((pstFtmReq->ulRxSwt!= EN_FTM_RXON_CLOSE)
        && (pstFtmReq->ulRxSwt != EN_FTM_RXON_OPEN))
    {
        
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ERR_MSP_INVALID_PARAMETER\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_frxon_setcnf(ERR_MSP_INVALID_PARAMETER);
    }

    /* ע��: ʵ��ʹ���в�Ϊ��DSP���Ϳ��ر�־�� DSP���ջ�һֱ�ǿ��ŵ�  */

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId  = OM_PHY_CT_RXON_REQ;
    stReqToDsp.usRxType = pstFtmReq->ulRxSwt;
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_RXON_REQ_STRU)))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ct_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_frxon_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_frxon_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_frxon_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_frxon_timeout(VOS_VOID)
{
    return at_ftm_frxon_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_frxon_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_RXON_CNF������
 �������  : pParam PHY_OM_CT_RXON_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_frxon_dspcnf(VOS_VOID* pParam)
{

    at_ftm_frxon_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_frxon_setcnf(ERR_MSP_SUCCESS);
}

#if (FEATURE_LTE_4RX == FEATURE_ON)
VOID at_ftm_frssi_store_lte_4rx(VOS_INT16 usRssiVal1, VOS_INT16 usRssiVal2,VOS_INT16 usRssiVal3,VOS_INT16 usRssiVal4);
#endif

#if (FEATURE_LTE_4RX == FEATURE_ON)
VOID at_ftm_frssi_store_lte_4rx(VOS_INT16 usRssiVal1, VOS_INT16 usRssiVal2,VOS_INT16 usRssiVal3,VOS_INT16 usRssiVal4)
{
    ftm_GetMainInfo()->stFtmCtInfo.usRssiVal1 = (VOS_UINT16)usRssiVal1;
    ftm_GetMainInfo()->stFtmCtInfo.usRssiVal2 = (VOS_UINT16)usRssiVal2;
    ftm_GetMainInfo()->stFtmCtInfo.usRssiVal3 = (VOS_UINT16)usRssiVal3;
    ftm_GetMainInfo()->stFtmCtInfo.usRssiVal4 = (VOS_UINT16)usRssiVal4;
    return ;
}
#else
/*****************************************************************************
 �� �� ��  : at_ftm_frssi_store
 ��������  : �������
 �������  : sRssiVal  �����ź�ǿ��(����: 850����-85dbm)
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOID at_ftm_frssi_store(VOS_INT16 sRssiVal)
{
    ftm_GetMainInfo()->stFtmCtInfo.sCurRssiVal = sRssiVal;
    return ;
}
#endif

/*****************************************************************************
 �� �� ��  : at_ftm_frssi_readcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_frssi_readcnf(VOS_UINT32 ulErrCode)
{
    FTM_FRSSI_CNF_STRU stCnf = { 0 };
    stCnf.ulErrCode = ulErrCode;
#if (FEATURE_LTE_4RX == FEATURE_ON)
    stCnf.lValue1 = ftm_GetMainInfo()->stFtmCtInfo.usRssiVal1;
    stCnf.lValue2 = ftm_GetMainInfo()->stFtmCtInfo.usRssiVal2;
    stCnf.lValue3 = ftm_GetMainInfo()->stFtmCtInfo.usRssiVal3;
    stCnf.lValue4 = ftm_GetMainInfo()->stFtmCtInfo.usRssiVal4;
#else
    stCnf.lValue1 = ftm_GetMainInfo()->stFtmCtInfo.sCurRssiVal;
#endif
    return ftm_comm_send(ID_MSG_FTM_FRSSI_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_FRSSI_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_frssi_read
 ��������  : ID_MSG_FTM_FRSSI_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_frssi_read(VOS_VOID* pParam)
{
    OM_PHY_CT_MEAS_RSSI_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode               = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_frssi_readcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId = OM_PHY_CT_MEAS_RSSI_REQ;
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_MEAS_RSSI_REQ_STRU)))
    {
        return at_ftm_frssi_readcnf(ERR_MSP_UNKNOWN);
    }

    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_frssi_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_frssi_timeout(VOS_VOID)
{
    return at_ftm_frssi_readcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_frssi_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_MEAS_RSSI_CNF������
 �������  : pParam PHY_OM_CT_MEAS_RSSI_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_frssi_dspcnf(VOS_VOID* pParam)
{

    /* �˺���ɶҲ����, ������Щ���� */
    /* �رճ�ʱ�ж϶�ʱ������at_ftm_frssi_dspind������*/

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_frssi_dspind
 ��������  : DSPԭ��PHY_OM_CT_RSSI_IND������
 �������  : pParam PHY_OM_CT_RSSI_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_frssi_dspind(VOS_VOID* pParam)
{
    VOS_UINT32 ulErrCode = ERR_MSP_SUCCESS;
    PHY_OM_CT_RSSI_IND_STRU* pDspInd = (PHY_OM_CT_RSSI_IND_STRU*)pParam;

    HAL_SDMLOG("\n usRxANT1ValidFlag:0x%x, sRxANT1RSSI:0x%x, usRxANT2ValidFlag:0x%x, sRxANT2RSSI:0x%x \n",
        pDspInd->usRxANT1ValidFlag, pDspInd->sRxANT1RSSI, pDspInd->usRxANT2ValidFlag, pDspInd->sRxANT2RSSI);
#if (FEATURE_LTE_4RX == FEATURE_ON)
    at_ftm_frssi_store_lte_4rx(pDspInd->sRxANT1RSSI,pDspInd->sRxANT2RSSI,pDspInd->sRxANT3RSSI,pDspInd->sRxANT4RSSI);
    ulErrCode = ERR_MSP_SUCCESS;
#else
    if(pDspInd->usRxANT1ValidFlag == 1)
    {

        at_ftm_frssi_store(pDspInd->sRxANT1RSSI);
        ulErrCode = ERR_MSP_SUCCESS;
    }
    else if(pDspInd->usRxANT2ValidFlag == 1)
    {
        HAL_SDMLOG("\n pDspInd->usRxANT1ValidFlag == 1 \n");
        at_ftm_frssi_store(pDspInd->sRxANT2RSSI);
        ulErrCode = ERR_MSP_SUCCESS;
    }
    else
    {
        at_ftm_frssi_store(-1);
        ulErrCode = ERR_MSP_OPERTION_ERROR;
    }
#endif

    return at_ftm_frssi_readcnf(ulErrCode);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fwave_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOID at_ftm_fwave_store(VOS_UINT8 ucStoreType, FTM_SET_FWAVE_REQ_STRU* pstReq)
{
    static FTM_SET_FWAVE_REQ_STRU stReq = {0};
    FTM_CT_MANAGE_INFO_STRU* pstFCtManageInfo = &ftm_GetMainInfo()->stFtmCtInfo;

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FWAVE_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFCtManageInfo->enCurFwaveType  = (FWAVE_TYPE_ENUM)stReq.usType;
        pstFCtManageInfo->usCurFwavePower = stReq.usPower;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fwave_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fwave_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FWAVE_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FWAVE_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FWAVE_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fwave_read
 ��������  : ID_MSG_FTM_RD_FWAVE_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fwave_read(VOS_VOID* pParam)
{
    FTM_RD_FWAVE_CNF_STRU stRdCnf = { 0 };

    stRdCnf.usType    = ftm_GetMainInfo()->stFtmCtInfo.enCurFwaveType;
    stRdCnf.usPower   = ftm_GetMainInfo()->stFtmCtInfo.usCurFwavePower;

    return ftm_comm_send(ID_MSG_FTM_RD_FWAVE_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_FWAVE_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fwave_set
 ��������  : ID_MSG_FTM_SET_FWAVE_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fwave_set(VOS_VOID* pParam)
{
    FTM_SET_FWAVE_REQ_STRU* pstFtmReq       = (FTM_SET_FWAVE_REQ_STRU*)pParam;
    OM_PHY_CT_FWAVE_SET_REQ_STRU stReqToDsp = { 0 };  
    FCHAN_MODE_ENUM fchanMode               = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fwave_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId = OM_PHY_CT_FWAVE_SET_REQ;
    stReqToDsp.usType  = pstFtmReq->usType;
    stReqToDsp.usPower = pstFtmReq->usPower;
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_FWAVE_SET_REQ_STRU)))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ct_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_fwave_setcnf(ERR_MSP_UNKNOWN);
    }
    at_ftm_fwave_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fwave_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fwave_timeout(VOS_VOID)
{
    return at_ftm_fwave_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fwave_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_FWAVE_CNF������
             �رճ�ʱ��ʱ��
 �������  : pParam PHY_OM_CT_FWAVE_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fwave_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fwave_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fwave_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_flna_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOID at_ftm_flna_store(VOS_UINT8 ucStoreType, FTM_SET_AAGC_REQ_STRU* pstReq)
{
    static FTM_SET_AAGC_REQ_STRU stReq = {0};
    FTM_CT_MANAGE_INFO_STRU* pstFCtManageInfo = &ftm_GetMainInfo()->stFtmCtInfo;

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_AAGC_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFCtManageInfo->ucCurLnaLvl = stReq.ucAggcLvl;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_flna_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_flna_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_AAGC_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_AAGC_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_AAGC_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_flna_read
 ��������  : ID_MSG_FTM_RD_AAGC_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_flna_read(VOS_VOID* pParam)
{
    FTM_RD_AAGC_CNF_STRU stRdCnf = { 0 };

    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    stRdCnf.ucAggcLvl = ftm_GetMainInfo()->stFtmCtInfo.ucCurLnaLvl;

     return ftm_comm_send(ID_MSG_FTM_RD_AAGC_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_AAGC_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_flna_set
 ��������  : ID_MSG_FTM_SET_AAGC_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_flna_set(VOS_VOID* pParam)
{
    FTM_SET_AAGC_REQ_STRU* pstFtmReq       = (FTM_SET_AAGC_REQ_STRU*)pParam;
    OM_PHY_CT_AAGC_SET_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode              = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]FTM_NONESIG_RTT_CLOSE\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_flna_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId     = OM_PHY_CT_AAGC_SET_REQ;
    stReqToDsp.usAAGCValue = pstFtmReq->ucAggcLvl;
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_AAGC_SET_REQ_STRU)))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ct_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_flna_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_flna_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_flna_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_flna_timeout(VOS_VOID)
{
    return at_ftm_flna_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_flna_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_AAGC_CNF������
             �رճ�ʱ��ʱ��
             �������  : pParam PHY_OM_CT_AAGC_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_flna_dspcnf(VOS_VOID* pParam)
{

    at_ftm_flna_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);
    return at_ftm_flna_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fvctcxo_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOID at_ftm_fvctcxo_store(VOS_UINT8 ucStoreType, FTM_SET_FVCTCXO_REQ_STRU* pstReq)
{
    static FTM_SET_FVCTCXO_REQ_STRU stReq = {0};
    FTM_CT_MANAGE_INFO_STRU* pstFCtManageInfo = &ftm_GetMainInfo()->stFtmCtInfo;

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FVCTCXO_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFCtManageInfo->usCurVctcxoVol = stReq.ulVol;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fvctcxo_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fvctcxo_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FVCTCXO_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FVCTCXO_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FVCTCXO_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fvctcxo_read
 ��������  : ID_MSG_FTM_RD_FVCTCXO_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fvctcxo_read(VOS_VOID* pParam)
{
    FTM_RD_FVCTCXO_CNF_STRU stRdCnf = { 0 };

    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    stRdCnf.ulVol     = ftm_GetMainInfo()->stFtmCtInfo.usCurVctcxoVol;

     return ftm_comm_send(ID_MSG_FTM_RD_FVCTCXO_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_FVCTCXO_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fvctcxo_set
 ��������  : ID_MSG_FTM_SET_FVCTCXO_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fvctcxo_set(VOS_VOID* pParam)
{
    FTM_SET_FVCTCXO_REQ_STRU* pstFtmReq      = (FTM_SET_FVCTCXO_REQ_STRU*)pParam;
    OM_PHY_CT_VCTCXO_SET_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode                = ftm_GetMainInfo()->stFtmCtInfo.stCurFchan.enFchanMode;
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
       (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]FTM_NONESIG_RTT_CLOSE\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_fvctcxo_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId = OM_PHY_CT_VCTCXO_SET_REQ;
    stReqToDsp.usVctcxoCtrl = (VOS_UINT16)pstFtmReq->ulVol;
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_VCTCXO_SET_REQ_STRU)))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ct_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_fvctcxo_setcnf(ERR_MSP_UNKNOWN);
    }
    
    at_ftm_fvctcxo_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fvctcxo_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fvctcxo_timeout(VOS_VOID)
{
    return at_ftm_fvctcxo_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fvctcxo_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_VCTCXO_CNF������
             �رճ�ʱ��ʱ��
             �������  : pParam PHY_OM_CT_VCTCXO_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fvctcxo_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fvctcxo_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fvctcxo_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpllstatus_read
 ��������  : ID_MSG_FTM_RD_FPLLSTATUS_REQ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/

VOS_UINT32 at_ftm_fpllstatus_read(VOS_VOID* pParam)
{
    OM_PHY_FPLLSTATUS_RD_REQ_STRU stReqToDsp = {0};
    if (NULL == pParam)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ERR_MSP_INVALID_OP\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_MSP_INVALID_OP;
    }
      
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId   = OM_PHY_FPLLSTATUS_RD_REQ;
     
    if (ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_FPLLSTATUS_RD_REQ_STRU)))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]ftm_mailbox_ltect_write\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return at_ftm_fpllstatus_readcnf(0,0,ERR_MSP_UNKNOWN);            
    }
    return ERR_MSP_WAIT_ASYNC;
}

VOS_UINT32 at_ftm_fpllstatus_readcnf(VOS_UINT16 txStatus, VOS_UINT16 rxStatus, VOS_UINT32 ulErrCode)
{
    FTM_RD_FPLLSTATUS_CNF_STRU stCnf = { 0 };
    stCnf.tx_status = txStatus;
    stCnf.rx_status = rxStatus;
    stCnf.ulErrCode = ulErrCode;
    
    return ftm_comm_send(ID_MSG_FTM_RD_FPLLSTATUS_CNF,
             (VOS_UINT32)&stCnf, sizeof(FTM_RD_FPLLSTATUS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpllstatus_dspcnf
 �������  : pParam PHY_OM_CT_FPLLSTATUS_RD_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpllstatus_dspcnf(VOS_VOID* pParam)
{
    if (NULL == pParam)
    {
        (VOS_VOID)vos_printf("invalid data\n");
        return ERR_MSP_INVALID_OP;
    }

    PHY_OM_FPLLSTATUS_RD_CNF_STRU *pDspCnf = (PHY_OM_FPLLSTATUS_RD_CNF_STRU *)pParam;
    FTM_RD_FPLLSTATUS_CNF_STRU stCnf = {0};
    stCnf.tx_status = pDspCnf->tx_status;
    stCnf.rx_status = pDspCnf->rx_status;
    stCnf.ulErrCode = ERR_MSP_SUCCESS;

    return ftm_comm_send(ID_MSG_FTM_RD_FPLLSTATUS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_RD_FPLLSTATUS_CNF_STRU));
}
/*lint -restore*/

VOS_UINT32 at_ftm_fpllstatus_timeout(VOS_VOID)
{
    return at_ftm_fpllstatus_readcnf(0,0,ERR_MSP_TIME_OUT);
}

