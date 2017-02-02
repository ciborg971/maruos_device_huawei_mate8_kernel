



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasLmmTest.h"
#include  "NasEsmPublic.h"
#include  "NasLmmPubMPrint.h"
#include  "NasLmmPubMEntry.h"
#include  "NasLmmPubMOm.h"
#include  "NasLmmPubMOsa.h"
#include  "NasEmmcPublic.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMTEST_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMTEST_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
static VOS_UINT32 NAS_PUBM_HELP_IE_PRESENT = 1;

/*****************************************************************************
  3 Function
*****************************************************************************/


VOS_VOID  NAS_LMM_CmdHelp( VOS_VOID )
{
    (VOS_VOID)vos_printf("\r\n");
    (VOS_VOID)vos_printf("********************** NAS EMM ��������б� *********************\r\n");
    (VOS_VOID)vos_printf("%-30s : NAS MM������Ϣ\r\n","NAS_LMM_ShowCommInfo");
    /*(VOS_VOID)vos_printf("%-30s : UE��PLMN�����Ϣ\r\n","NAS_LMM_ShowPlmnInfo");*/
    (VOS_VOID)vos_printf("%-30s : UE��TMSI�����Ϣ\r\n","NAS_LMM_ShowTmsiInfo");
    (VOS_VOID)vos_printf("%-30s : UE���ƶ���Ϣ(GUTI��TaiList��Last TA)\r\n","NAS_LMM_ShowMobilityInfo");
    (VOS_VOID)vos_printf("%-30s : EMMģ��״̬��Ϣ\r\n","NAS_LMM_ShowEmmFsmInfo");
    (VOS_VOID)vos_printf("%-30s : EMM��Ե״̬���յ�ϵͳ��Ϣ��ͳ��\r\n","NAS_LMM_ShowSysInfoCount");
    (VOS_VOID)vos_printf("*********************************************************************\r\n");
    (VOS_VOID)vos_printf("\r\n");
}

/*****************************************************************************
 Function Name   : NAS_LMM_DebugInit
 Description     : MM�����ʼ��
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-03-10  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_DebugInit(VOS_VOID)
{
    /*��ʼ��DSDS������Ϣ����*/
    /*lint -e960*/
    #if (FEATURE_ON == FEATURE_DSDS)
    NAS_LMM_MEM_SET(g_astDsdsNotifyMsgNum, 0, sizeof(NAS_LMM_DSDS_MSG_COUNT_STRU)* LRRC_LNAS_SESSION_TYPE_BUTT);
    NAS_LMM_MEM_SET(g_astDsdsInputNotifyMsgNum, 0, sizeof(NAS_LMM_DSDS_MSG_COUNT_STRU) * NAS_EMM_INPUT_DSDS_MSG_NUM);
    #endif
    /*lint +e960*/

    return ;
}
VOS_VOID NAS_LMM_ShowImsi(VOS_VOID)
{

}

/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_LMM_ShowImei( VOS_VOID )
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           aucImei[10] = {0};
    VOS_UINT8                           aucImeiStr[16];

    NAS_EMMC_UEID_STRU                   *pstUeId;

    /* ��ȡUEID��ַ */
    pstUeId = NAS_LMM_GetEmmInfoUeidAddr();

    if (NAS_PUBM_HELP_IE_PRESENT != pstUeId->bitOpImei)
    {
        aucImeiStr[0] = '\0';
        (VOS_VOID)vos_printf("%-30s : %s\r\n","IMEI״̬","��Ч");
        return;
    }

    NAS_LMM_MEM_CPY(aucImei, pstUeId->aucImei, 8+1);

    /*NAS_LMM_PubmComputeImeicd(aucImei);*/


    if (aucImei[0] > 8)
    {
        aucImeiStr[0] = '\0';
        (VOS_VOID)vos_printf("%-30s : %s\r\n","IMEI״̬","��Ч");
        return;
    }

    aucImeiStr[0] = ((aucImei[1] & 0xF0) >> 4) + '0';

    for (ucLoop = 2; ucLoop <= 8; ucLoop++)
    {
        aucImeiStr[(ucLoop*2)-3] = ((aucImei[ucLoop] & 0x0F)) + '0';

        aucImeiStr[(ucLoop*2)-2] = ((aucImei[ucLoop] & 0xF0) >> 4) + '0';

    }

    aucImeiStr[15] = '\0';
    (VOS_VOID)vos_printf("%-30s : %s\r\n","IMEI",aucImeiStr);
}


VOS_VOID NAS_LMM_ShowImeisv(VOS_VOID)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           aucImsisv[10] = {0};
    VOS_UINT8                           aucImsisvStr[17];

    NAS_EMMC_UEID_STRU                   *pstUeId;

    /* ��ȡUEID��ַ */
    pstUeId = NAS_LMM_GetEmmInfoUeidAddr();

    if (NAS_PUBM_HELP_IE_PRESENT != pstUeId->bitOpImeisv)
    {
        aucImsisvStr[0] = '\0';
        (VOS_VOID)vos_printf("%-30s : %s\r\n","IMEISV״̬","��Ч");
        return;
    }

    NAS_LMM_MEM_CPY(aucImsisv, pstUeId->aucImeisv, 8+2);

    if (aucImsisv[0] > 9)
    {
        aucImsisvStr[0] = '\0';
        (VOS_VOID)vos_printf("%-30s : %s\r\n","IMEISV״̬","��Ч");
        return;
    }

    aucImsisvStr[0] = ((aucImsisv[1] & 0xF0) >> 4) + '0';

    for (ucLoop = 2; ucLoop <= 8; ucLoop++)
    {
        aucImsisvStr[(ucLoop*2)-3] = ((aucImsisv[ucLoop] & 0x0F)) + '0';

        aucImsisvStr[(ucLoop*2)-2] = ((aucImsisv[ucLoop] & 0xF0) >> 4) + '0';
    }

    aucImsisvStr[15] = (aucImsisv[9] & 0x0F) + '0';
    aucImsisvStr[16] = '\0';
    (VOS_VOID)vos_printf("%-30s : %s\r\n","IMEISV",aucImsisvStr);
}
VOS_VOID NAS_LMM_ShowFsmstate
(
    NAS_LMM_PARALLEL_FSM_ENUM_UINT16         enParallelFsmId
)
{

    NAS_LMM_FSM_STATE_STRU               *pstFsmState;
    VOS_INT32                           ilOutPutLen;
    VOS_UINT16                          usTotalLen         = 0;
    VOS_CHAR                            *pBuf              = VOS_NULL_PTR;

    pstFsmState = NAS_LMM_GetCurFsmAddr(enParallelFsmId);

    /* ��ӡ״̬��(��������״̬����״̬����״̬��״̬��ʱ��) */
    ilOutPutLen = NAS_LMM_PUBM_PrintFsmState(
                        NAS_COMM_GET_MM_PRINT_BUF(),
                        usTotalLen,
                        pstFsmState);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PrintFsmState, NAS_LMM_PUBM_PrintFsmState exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ShowFsmstate_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }
    usTotalLen += (VOS_UINT16)(ilOutPutLen);
    pBuf = NAS_COMM_GET_MM_PRINT_BUF();

    pBuf[usTotalLen++] = '\r';
    pBuf[usTotalLen++] = '\n';

    pBuf[usTotalLen] = 0;

    (VOS_VOID)vos_printf("%s",NAS_COMM_GET_MM_PRINT_BUF());
}
VOS_VOID NAS_LMM_ShowAuxFsm(VOS_VOID)
{
    NAS_LMM_AUXILIARY_FSM_STRU            *pstAuxFsm;
    VOS_INT32                            ilOutPutLen;
    VOS_UINT16                           usTotalLen         = 0;
    VOS_CHAR                             *pBuf              = VOS_NULL_PTR;

    pstAuxFsm = NAS_LMM_GetMmAuxFsmAddr();

    /* ��ӡ����״̬��(����EMM����״̬��RRC����״̬��SIM��״̬) */
    ilOutPutLen = NAS_LMM_PUBM_PrintAuxFsm(
                        NAS_COMM_GET_MM_PRINT_BUF(),
                        usTotalLen,
                        pstAuxFsm);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PrintAuxFsm, NAS_LMM_PUBM_PrintAuxFsm exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ShowAuxFsm_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }
    usTotalLen += (VOS_UINT16)(ilOutPutLen);

    pBuf = NAS_COMM_GET_MM_PRINT_BUF();

    pBuf[usTotalLen++] = '\r';
    pBuf[usTotalLen++] = '\n';

    pBuf[usTotalLen] = 0;

    (VOS_VOID)vos_printf("%s",NAS_COMM_GET_MM_PRINT_BUF());

    return;
}
VOS_VOID NAS_LMM_ShowEmmFsmInfo(VOS_VOID)
{
    (VOS_VOID)vos_printf("\r\n");
    NAS_LMM_ShowFsmstate(NAS_LMM_PARALLEL_FSM_EMM);
    /*NAS_LMM_ShowFsmstate(NAS_LMM_PARALLEL_FSM_MMC);*/
    NAS_LMM_ShowAuxFsm();
}
/* ע��/����״̬�ϱ�����MMC��ɾ��NAS_LMM_ShowServStateInfo���� */

VOS_VOID NAS_LMM_ShowPlmn(VOS_UINT8 const *pucPlmnId)
{
    VOS_UINT8               ucMcc1;
    VOS_UINT8               ucMcc2;
    VOS_UINT8               ucMcc3;
    VOS_UINT8               ucMnc1;
    VOS_UINT8               ucMnc2;
    VOS_UINT8               ucMnc3;

    ucMcc1 = pucPlmnId[0] & 0x0F;
    ucMcc2 = (pucPlmnId[0] & 0xF0) >> 4;
    ucMcc3 = pucPlmnId[1] & 0x0F;

    ucMnc3 = (pucPlmnId[1] & 0xF0) >> 4;
    ucMnc1 = pucPlmnId[2] & 0x0F;
    ucMnc2 = (pucPlmnId[2] & 0xF0) >> 4;

    if ((0xF == ucMcc1) && (0xF == ucMcc2) && (0xF == ucMcc3)
        && (0xF == ucMnc1) && (0xF == ucMnc2) && (0xF == ucMnc3))
    {
        (VOS_VOID)vos_printf("PLMN ID��Ч!\r\n");
        return;
    }


    if ((0 == ucMcc1) && (0 == ucMcc2) && (0 == ucMcc3)
        && (0 == ucMnc1) && (0 == ucMnc2) && (0 == ucMnc3))
    {
        (VOS_VOID)vos_printf("PLMN ID��Ч!\r\n");
        return;
    }

    if ( 0xF == ucMnc3 )
    {
        (VOS_VOID)vos_printf("%-30s : %d%d%d %d%d\r\n","PLMNID",ucMcc1,ucMcc2,ucMcc3,ucMnc1,ucMnc2);
    }
    else
    {
        (VOS_VOID)vos_printf("%-30s : %d%d%d %d%d%d\r\n","PLMNID",ucMcc1,ucMcc2,ucMcc3,ucMnc1,ucMnc2,ucMnc3);
    }
}



VOS_VOID  NAS_LMM_ShowTmsiInfo( VOS_VOID )
{
    NAS_LMM_UEID_STRU                        *pstUeId   =  (NAS_LMM_UEID_STRU*)NAS_LMM_GetEmmInfoUeidAddr();
    VOS_UINT8                               asTmsi[5];
    VOS_UINT32                              i;

    (VOS_VOID)vos_printf("****************TMSI��Ӧ�������Ϣ����****************\r\n");

    if ( 0 == pstUeId->bitOpGuti)
    {
        (VOS_VOID)vos_printf("S-TMSI������");
    }
    else
    {
        asTmsi[0] = pstUeId->stGuti.stMmeCode.ucMmeCode;
        NAS_LMM_MEM_CPY(&asTmsi[1], &(pstUeId->stGuti.stMTmsi), 4);

        (VOS_VOID)vos_printf("��ǰS-TMSI:  ");
        for (i = 0; i < 5; i++)
        {
            (VOS_VOID)vos_printf("%02x ",asTmsi[i]);
        }
        (VOS_VOID)vos_printf("\n");
    }

    return;
}


VOS_VOID NAS_LMM_ShowGutiInfo( APP_GUTI_STRU const *pstGutiInfo )
{
    VOS_UINT32                          ulData;

    (VOS_VOID)vos_printf("**********************GUTI��Ϣ����*************************\r\n");

    NAS_LMM_ShowPlmn(pstGutiInfo->stPlmn.aucPlmnId);

    ulData = (pstGutiInfo->stMmeGroupId.ucGroupId << 8)
            | pstGutiInfo->stMmeGroupId.ucGroupIdCnt;

    (VOS_VOID)vos_printf("%-30s : %02x %02x(%d)\r\n","mme group id",
                                           pstGutiInfo->stMmeGroupId.ucGroupId,\
                                           pstGutiInfo->stMmeGroupId.ucGroupIdCnt,\
                                           ulData);

    (VOS_VOID)vos_printf("%-30s : 0x%0x\r\n","mme code",pstGutiInfo->stMmeCode.ucMmeCode);

    /*lint -e701*/

    ulData = (pstGutiInfo->stMTmsi.ucMTmsi << 24)
              | (pstGutiInfo->stMTmsi.ucMTmsiCnt1 << 16)
              | (pstGutiInfo->stMTmsi.ucMTmsiCnt2 << 8)
              | pstGutiInfo->stMTmsi.ucMTmsiCnt3;
    /*lint +e701*/

    (VOS_VOID)vos_printf("%-30s : %02x %02x %02x %02x(%d)\r\n","m-tmsi",\
                                            pstGutiInfo->stMTmsi.ucMTmsi,\
                                            pstGutiInfo->stMTmsi.ucMTmsiCnt1,\
                                            pstGutiInfo->stMTmsi.ucMTmsiCnt2,\
                                            pstGutiInfo->stMTmsi.ucMTmsiCnt3,\
                                            ulData);
}

VOS_VOID NAS_LMM_ShowTailistInfo( APP_TA_LIST_STRU const *pstTaiList )
{
    VOS_UINT32                           ulLoop;
    VOS_UINT32                           ulTalistNum;

    (VOS_VOID)vos_printf("********************TA LIST��Ϣ����************************\r\n");

    ulTalistNum = pstTaiList->ulTaNum;

    if (ulTalistNum > APP_MM_MAX_TA_NUM)
    {
        ulTalistNum = APP_MM_MAX_TA_NUM;
    }

    (VOS_VOID)vos_printf("%-30s : %d\r\n","TA LIST�е�TA����",ulTalistNum);


    for ( ulLoop = 0 ; ulLoop < ulTalistNum; ulLoop++ )
    {
        (VOS_VOID)vos_printf("��%d��TA��Ϣ����\r\n",(ulLoop + 1));

        NAS_LMM_ShowPlmn(pstTaiList->astTa[ulLoop].stPlmnId.aucPlmnId);

        NAS_LMM_ShowTac(pstTaiList->astTa[ulLoop].stTac.ucTac,\
                  pstTaiList->astTa[ulLoop].stTac.ucTacCnt);
    }
}


VOS_VOID NAS_LMM_ShowTac(VOS_UINT8 ucTac,VOS_UINT8 ucTacCnt)
{
    (VOS_VOID)vos_printf( "%-30s : %02x %02x(%d)\r\n","TAC",
                ucTac,
                ucTacCnt,
                ((ucTac<<8) | ucTacCnt) );
}


VOS_VOID NAS_LMM_ShowLastTaInfo( APP_TA_STRU const *pstLastTa )
{
    (VOS_VOID)vos_printf("********************LAST TA��Ϣ����************************\r\n");
    NAS_LMM_ShowPlmn(pstLastTa->stPlmnId.aucPlmnId);
    NAS_LMM_ShowTac(pstLastTa->stTac.ucTac,\
              pstLastTa->stTac.ucTacCnt);
}

VOS_VOID NAS_LMM_ShowForbidTalistInfo( APP_TA_LIST_STRU const *pstFtalist )
{
    VOS_UINT32                           ulLoop;
    VOS_UINT32                           ulFTalistNum;

    (VOS_VOID)vos_printf("*******************��ֹTA LIST��Ϣ����*********************\r\n");

    ulFTalistNum = pstFtalist->ulTaNum;


    if (ulFTalistNum > APP_MM_MAX_TA_NUM)
    {
        ulFTalistNum = APP_MM_MAX_TA_NUM;
    }

    (VOS_VOID)vos_printf("%-30s : %d\r\n","��ֹTA LIST����",ulFTalistNum);

    for ( ulLoop = 0 ; ulLoop < ulFTalistNum; ulLoop++ )
    {
        (VOS_VOID)vos_printf("��%d����ֹTA��Ϣ����\r\n",(ulLoop + 1));
        NAS_LMM_ShowPlmn(pstFtalist->astTa[ulLoop].stPlmnId.aucPlmnId);
        NAS_LMM_ShowTac(pstFtalist->astTa[ulLoop].stTac.ucTac,\
                  pstFtalist->astTa[ulLoop].stTac.ucTacCnt);
    }
}


/*lint -e438*/
VOS_VOID NAS_LMM_ShowMobilityInfo(VOS_VOID )
{
    APP_EMM_INFO_STRU                   *pstEmmInfo = VOS_NULL_PTR;

    pstEmmInfo = (APP_EMM_INFO_STRU *) NAS_LMM_MEM_ALLOC(sizeof(APP_EMM_INFO_STRU));

    if (VOS_NULL_PTR == pstEmmInfo)
    {
        return;
    }

    NAS_LMM_PubmGetEmmInfo(pstEmmInfo);

    (VOS_VOID)vos_printf("\r\n");

    /*��ӡGUTI��Ϣ*/
    NAS_LMM_ShowGutiInfo(&pstEmmInfo->stGuti);

    /*��ӡTALIST��Ϣ*/
    NAS_LMM_ShowTailistInfo(&pstEmmInfo->stTaiList);

    /*��ӡLAstTa��Ϣ*/
    NAS_LMM_ShowLastTaInfo(&pstEmmInfo->stLastTa);

    /*��ӡ��ֹTA����Ϣ*/
    NAS_LMM_ShowForbidTalistInfo(&pstEmmInfo->stForbTaList);

    NAS_LMM_MEM_FREE(pstEmmInfo);
    pstEmmInfo = VOS_NULL_PTR;

    (VOS_VOID)vos_printf("\r\n");

}
/*lint +e438*/


VOS_VOID NAS_LMM_ShowConnInfo( VOS_VOID )
{
    NAS_LMM_AUXILIARY_FSM_STRU           *pstAuxFsm = VOS_NULL_PTR;

    pstAuxFsm = NAS_LMM_GetMmAuxFsmAddr();

    if ((NAS_EMM_CONN_IDLE == pstAuxFsm->ucRrcConnState)
        || (NAS_EMM_CONN_RELEASING == pstAuxFsm->ucRrcConnState))
    {
        (VOS_VOID)vos_printf("%-30s : %s\r\n","����״̬","����");
    }
    else
    {
        (VOS_VOID)vos_printf("%-30s : %s\r\n","����״̬","����");
    }
}


/*lint -e438*/
VOS_VOID  NAS_LMM_ShowCommInfo(VOS_VOID)
{
    APP_EMM_INFO_STRU                   *pstEmmInfo = VOS_NULL_PTR;
    NAS_MMC_TA_STRU                      stTa;

    pstEmmInfo = (APP_EMM_INFO_STRU *) NAS_LMM_MEM_ALLOC(sizeof(APP_EMM_INFO_STRU));

    if (VOS_NULL_PTR == pstEmmInfo)
    {
        return;
    }

    NAS_LMM_PubmGetEmmInfo(pstEmmInfo);

    (VOS_VOID)vos_printf("\r\n");

    /*lint -e522*/
    NAS_LMM_ShowImsi();
    NAS_LMM_ShowImei();
    NAS_LMM_ShowImeisv();
    NAS_LMM_ShowTmsiInfo();
    /*lint +e522*/
/* ע��/����״̬�ϱ�����MMC��ɾ������ */

    /*��ӡ����״̬��Ϣ*/
    NAS_LMM_ShowConnInfo();

    /*��ӡλ����Ϣ*/
    NAS_EMMC_GetCurrentTa(&stTa);

    NAS_LMM_ShowPlmn( stTa.stPlmnId.aucPlmnId);
    NAS_LMM_ShowTac(  stTa.stTac.ucTac,\
                     stTa.stTac.ucTacCnt);

    (VOS_VOID)vos_printf("\r\n");

    NAS_LMM_MEM_FREE(pstEmmInfo);
    pstEmmInfo = VOS_NULL_PTR;

    (VOS_VOID)vos_printf("\r\n");
}
/*lint +e438*/
/*lint +e961*/
/*lint +e960*/

VOS_VOID  NAS_LMM_ShowSysInfoCount( VOS_VOID )
{
    NAS_LMM_SYSINFO_COUNT_STRU           *pstSysInfoCounter;

    pstSysInfoCounter                  = NAS_EMM_GetSysInfCntAddr();

    (VOS_VOID)vos_printf("\n*******************ϵͳ��Ϣͳ����Ϣ����*********************\r\n");
    (VOS_VOID)vos_printf("״̬Ms:RrcConnEstInit Ss:WaitRrcConnCnf\n");
    (VOS_VOID)vos_printf("%-20s : %d\r\n","�յ�ϵͳ��Ϣ����",pstSysInfoCounter->ulEstCnfCount);

    (VOS_VOID)vos_printf("״̬Ms:RrcConnRelInit Ss:WaitRrcRelCnf\n");
    (VOS_VOID)vos_printf("%-20s : %d\r\n","�յ�ϵͳ��Ϣ����",pstSysInfoCounter->ulRelCnfCount);

    (VOS_VOID)vos_printf("״̬Ms:RegInit        Ss:WaitRrcRelInd\n");
    (VOS_VOID)vos_printf("%-20s : %d\r\n","�յ�ϵͳ��Ϣ����",pstSysInfoCounter->ulRegInitRrcRelIndCount);

    (VOS_VOID)vos_printf("״̬Ms:DeregInit      Ss:WaitRrcRelInd\n");
    (VOS_VOID)vos_printf("%-20s : %d\r\n","�յ�ϵͳ��Ϣ����",pstSysInfoCounter->ulDeregInitRrcRelIndCount);

    (VOS_VOID)vos_printf("״̬Ms:TAUInit        Ss:WaitRrcRelInd\n");
    (VOS_VOID)vos_printf("%-20s : %d\r\n","�յ�ϵͳ��Ϣ����",pstSysInfoCounter->ulTauInitRrcRelIndCount);

    (VOS_VOID)vos_printf("״̬Ms:ServInit       Ss:WaitRrcRelInd\n");
    (VOS_VOID)vos_printf("%-20s : %d\r\n","�յ�ϵͳ��Ϣ����",pstSysInfoCounter->ulServInitRrcRelIndCount);

    (VOS_VOID)vos_printf("״̬Ms:Reg       Ss:ImsiDetachWaitRrcRelInd\n");
    (VOS_VOID)vos_printf("%-20s : %d\r\n","�յ�ϵͳ��Ϣ����",pstSysInfoCounter->ulRegImsiDetachRrcRelIndCount);
}

#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID  NAS_LMM_ShowDsdsNotifyNum( VOS_VOID )
{
    VOS_UINT32 ulIndex = 0;
    (VOS_VOID)vos_printf("\n*******************DSDS��Ϣͳ����Ϣ����*********************\r\n");
    for(ulIndex=0;ulIndex<LRRC_LNAS_SESSION_TYPE_BUTT;ulIndex++)
    {
        if((0 != g_astDsdsNotifyMsgNum[ulIndex].ulBeginMsgCnt)
             || (0 != g_astDsdsNotifyMsgNum[ulIndex].ulEndMsgCnt))
        {
            (VOS_VOID)vos_printf("g_astDsdsNotifyMsgNum[%d].ulBeginMsgCnt=%d,g_astDsdsNotifyMsgNum[%d].ulEndMsgCnt=%d\r\n",
            ulIndex,g_astDsdsNotifyMsgNum[ulIndex].ulBeginMsgCnt,
            ulIndex,g_astDsdsNotifyMsgNum[ulIndex].ulEndMsgCnt);
        }
    }

    return;
}
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

