/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasLppEtcMsgProc.c
  �� �� ��   : ����
  ��    ��   : LIFUXIN
  ��������   : 2015��7��30��
  ����޸�   :
  ��������   : LPP ģ����ڲ���Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��1��
    ��    ��   : LIFUXIN
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
//#include  "vos.h"
#include  "NasLppPublic.h"
#include  "NasLppSendMsg.h"
#include  "EtcLppInterface.h"
#include  "NasLppSendMsg.h"
#include  "NasLppEtcMsgProc.h"

#if (FEATURE_LPP == FEATURE_ON)
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#define    THIS_FILE_ID            PS_FILE_ID_NASLPPETCMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPETCMSGPROC_C


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/



VOS_VOID NAS_LPP_RcvLppEtcResetPostitionInfoInd( ETC_LPP_RESET_POSTION_INFO_STRU *pRcvMsg )
{
    NAS_LPP_LOC_TECH_MAP_STRU              *pstLocTechmap = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEtcResetPostitionInfoInd is entered!");

    switch(pRcvMsg->enRestType)
    {
        case ETC_LPP_RESET_TYPE_GNSS:
            /*TODO*/
            break;

        case ETC_LPP_RESET_TYPE_OTDOA:
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEtcResetPostitionInfoInd: Reset OTDOA Information!");

            /*��λOTDOA�ĸ�����Ϣ*/
            /*��ձ��ش����ĸ�����Ϣ*/
            NAS_LPP_MEM_SET(&(NAS_LPP_GetLppEntityCtx()->stMeasResult.stOtdoaMeasRslt),
                            0,
                            sizeof(NAS_LPP_OTDOA_MEAS_RESLT_STRU));

            NAS_LPP_MEM_SET(&(NAS_LPP_GetLppEntityCtx()->stLppConfig.stOtdoaAssisCfg),
                            0,
                            sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU));

            /*����running���õ�transactionIndex��sessionTransactionIndx*/
            pstLocTechmap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
            if (NAS_LPP_NULL_PTR != pstLocTechmap)
            {
                /*��LRRC���Ͳ���ֹͣ*/
                NAS_LPP_SndOtdoaMeasReq(pstLocTechmap->ucSessionIndx,
                                              pstLocTechmap->ucSessionTranIndx,
                                              LPP_LRRC_LCS_MEAS_CMD_REL);
            }
            break;

        default:
            break;
    }

    return;
}
VOS_VOID NAS_LPP_EtcMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_EtcMsgDistr is entered!");

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pEmmMsg->ulMsgName)
    {
        /*�յ�����ID_ETC_LPP_RESET_POSTION_INFO_IND��Ϣ*/
        case ID_ETC_LPP_RESET_POSTION_INFO_IND:
            NAS_LPP_RcvLppEtcResetPostitionInfoInd((ETC_LPP_RESET_POSTION_INFO_STRU *)pRcvMsg);
            break;

        default:
            NAS_LPP_WARN_LOG("NAS_LPP_EtcMsgDistr:NORM: Error SenderPid!");
            break;
    }

    return;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

