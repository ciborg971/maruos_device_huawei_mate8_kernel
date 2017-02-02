/******************************************************************************

                  ��Ȩ���� (C), 2014, ��Ϊ�������޹�˾
 ******************************************************************************
  �� �� ��   : BST_DRV_LinkSta.c
  �� �� ��   : ����
  ��    ��   :
  ��������   :
  ����޸�   :
  ��������   :
  �����б�   :

  �޸���ʷ   :
  1.��    ��   :
    ��    ��   :
    �޸�����   : �����ļ�

����    |   Ӣ��          | ����                      | ȡֵ��Χ  |     Ȩֵ
        |                 |                           |--------------------+-------------
        |                 |                           |           |  Idle  | Connected
--------+-----------------+---------------------------+----------------------------------
R       |   Rank          | ��·�ȼ���ǰ�ȼ�״̬      | 0--������ | 0
        |                 |                           | 1--������ | S��(0��40)
        |                 |                           | 2--��     | S��[40��70)
        |                 |                           | 3--��     | S��[70��100]
--------+-----------------+---------------------------+-----------+--------+-------------
S       |   Score         | �ۺϵ÷�                  | 0-100     |        |
--------+-----------------+---------------------------+-----------+--------+-------------
N       |   Net Strength  |����RSCP,ECI0�ۺϼ���ó�  | 0-100     |  100%  | 40%
--------+-----------------+---------------------------+-----------+--------+-------------
Q       |   Queue State   | RRC�����ж������         | 0-100     |  0     | 30%
--------+-----------------+---------------------------+-----------+--------+-------------
T       |   Transimit     | �����ԣ���ǰ����RRC�ش�   | 0-100     |  0     | 30%
--------+---------------------------------------------+-----------+--------+-------------
D       |   DownLinkRx    | �յ��������ݰ�,�̶�����20 | 0         |  0%    |
-----------------------------------------------------------------------------------------

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_DRV_LinkSta.h"
#include "BST_OS_Memory.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_DRV_LINKSTA_C
/*lint +e767*/
/******************************************************************************
   2 �궨��
******************************************************************************/
/*****************************************************************************
  3 ��������
*****************************************************************************/

/* �ṩ��PAL�㣬��������д�벻ͬMODEM����ͬ��ʽ�������ź����� */
BST_UINT32          BST_DRV_LsItf_InWriteNetStrength(
    const BST_UINT32        ulModemId,
    const BST_UINT32        ulRatMode,
    const BST_UINT32        ulCellId,
    const BST_INT16         sRscp,
    const BST_INT16         sEcio );

/* �ṩ��PAL�㣬����ע���ѯ���Խӿ� */
BST_ERR_ENUM_UINT8 BST_DRV_LsItf_InRegInquireFun(
    const BST_UINT32        ulModemId,
    const BST_UINT32        ulRatMode,
    BST_VOID               *pfReadTrsInfo,
    BST_VOID               *pfReadQueInfo );

/* ��׼����IO�ӿ� */
BST_ERR_ENUM_UINT8  BST_DRV_LsItf_IoInit(
    BST_VOID               *pvArg );

BST_ERR_ENUM_UINT8  BST_DRV_LsItf_IoWrite(
    BST_UINT32              ulLength,
    BST_UINT8              *pucData );

BST_UINT32          BST_DRV_LsItf_IoRead(
    BST_UINT32              ulLength,
    BST_UINT8              *pucData );

BST_ERR_ENUM_UINT8  BST_DRV_LsItf_IoCtrl(
    BST_UINT32              ulCmdId,
    BST_VOID               *pucData );

/* ��DRV_AS���ýӿ� */
BST_VOID            BST_DRV_LsItf_AsRatMode(
    BST_UINT32              ulRatMode );

BST_VOID            BST_DRV_LsItf_AsRrcState(
    BST_UINT32              ulRrcState );

BST_VOID            BST_DRV_LsItf_AsBlockedState(
    BST_UINT32              ulIsBlocked );

BST_VOID            BST_DRV_LsItf_AsRxInd( BST_VOID );

/* ��DRV_NET���ýӿ� */
BST_VOID            BST_DRV_LsItf_NetUsingModem(
    BST_UINT32              ulModemId );

/* �ڲ�ʹ�ú��� */
BST_STATIC  BST_DRV_LS_RAT_SN_ENUM_UINT32 BST_DRV_LsMapRatToSn(
    BST_AS_RAT_MODE_UINT32  ulRatMode );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_RValue(
    BST_UINT32              ulSValue );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_SValue(
    BST_UINT32              ulNValue,
    BST_UINT32              ulTValue,
    BST_UINT32              ulQValue );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_TValue(
    BST_DRV_LS_READ_TRS_FUNC   pfTrsFun );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_QValue(
    BST_DRV_LS_READ_QUE_FUNC   pfQueFun );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_NValue(
    BST_INT16                ulRscp,
    BST_INT16                ulEci0 );

BST_STATIC  BST_VOID BST_DRV_LsCal_RscpAvg(
    BST_INT16                    sRscp,
    BST_INT16                    sEci0,
    BST_INT16                    *psRscpAvg,
    BST_INT16                    *psEci0Avg );

BST_STATIC  BST_VOID BST_DRV_LsCal_RscpVrc(
    BST_INT16                    sRscpAvg );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_LW_NCore(
    BST_INT16                    sRscpAvg,
    BST_INT16                    sEci0Avg );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_TG_NCore(
    BST_INT16                    sRscpMin,
    BST_INT16                    sRscpMax,
    BST_INT16                    sRscpAvg );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_QScore(
  BST_UINT32                     ulQueLength,
  BST_UINT32                     ulQueHigh,
  BST_UINT32                     ulQueLow);

BST_STATIC  BST_UINT32 BST_DRV_LsCal_Score(
  BST_UINT32                     ulRate,
  BST_UINT32                     ulNValue,
  BST_UINT32                     ulTValue,
  BST_UINT32                     ulQValue );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_TScore(
  BST_UINT32                     ulReTxRate,
  BST_UINT16                     usReTxMin,
  BST_UINT16                     usReTxMax);

BST_VOID BST_DRV_LsItf_InitThreshold( BST_VOID );

/******************************************************************************
   4 �ⲿ��������
******************************************************************************/
extern BST_VOID BST_PAL_LsInit( BST_VOID );
extern BST_VOID BST_PAL_LsRegCb( BST_DRV_LS_INS_STRU *pstLsIns );
extern BST_VOID BST_DRV_AsEventCallBack(
    BST_AS_EVT_ENUM_UINT32          enAsEvent,
    BST_UINT32                      ulLength,
    BST_VOID                       *pvData );

/******************************************************************************
   5 ȫ�ֱ�������
******************************************************************************/
BST_DRV_STRU    g_BstDrvLinkStateHandle =
{
    BST_DRV_LsItf_IoInit,
    BST_DRV_LsItf_IoWrite,
    BST_DRV_LsItf_IoRead,
    BST_DRV_LsItf_IoCtrl,
    BST_FALSE
};
BST_DRV_LS_INS_STRU g_BstDrvLsInstance = { 0 };
/******************************************************************************
   6 ����ʵ��
******************************************************************************/

BST_ERR_ENUM_UINT8 BST_DRV_LsItf_IoInit(
    BST_VOID       *pvArg )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_UINT16                          usCnt0, usCnt1;

    pstLsIns                            = BST_DRV_LsGetInstance();
    pstLsIns->ulCurModemId              = BST_MODEM_MAX;
    pstLsIns->ulCurRrc                  = BST_RRC_STATE_BUTT;
    pstLsIns->ulCurRAT                  = BST_AS_RAT_NONE;
    pstLsIns->ulCellId                  = BST_AS_INVALID_CELLID;
    pstLsIns->ulBlockState              = BST_FALSE;
    pstLsIns->ulRankValue               = BST_AS_NET_RANK_INVALID;
    pstLsIns->ulLastRank                = BST_AS_NET_RANK_INVALID;
    pstLsIns->stNetSta.usCounter        = 0;
    pstLsIns->ulCurDValue               = 0;
    pstLsIns->stNetSta.usIsFull         = BST_FALSE;

    pstLsIns->stRlcStat.ulStatFlag      = BST_FALSE;
    pstLsIns->stRlcStat.ulTotalPkt      = 0;
    pstLsIns->stRlcStat.ulTotalRePkt    = 0;
    pstLsIns->usMovingState             = BST_DRV_LS_STATE_BUTT;
    pstLsIns->usStaticCounter           = 0;
    pstLsIns->ulTransScore              = BST_AS_INVALID_SCORE;

    for( usCnt0 = 0; usCnt0 < BST_DRV_LS_BUF_LENGTH; usCnt0++ )
    {
        pstLsIns->stNetSta.asRscp[usCnt0] = 0;
        pstLsIns->stNetSta.asEcI0[usCnt0] = 0;
    }

    for( usCnt0 = 0; usCnt0 < BST_MODEM_MAX; usCnt0++ )
    {
        for( usCnt1 = 0; usCnt1 < BST_DRV_LS_RAT_NUMBER; usCnt1++ )
        {
            pstLsIns->apfReadQueInfo[usCnt0][usCnt1]
                                        = BST_NULL_PTR;
            pstLsIns->apfReadTrsInfo[usCnt0][usCnt1]
                                        = BST_NULL_PTR;
        }
    }

    BST_DRV_LsItf_InitThreshold();
    BST_PAL_LsRegCb( pstLsIns );

    return BST_NO_ERROR_MSG;
}


BST_ERR_ENUM_UINT8 BST_DRV_LsItf_IoWrite(
    BST_UINT32      ulLength,
    BST_UINT8      *pucData )
{
    return BST_NO_ERROR_MSG;
}



BST_UINT32 BST_DRV_LsItf_IoRead(
    BST_UINT32      ulLength,
    BST_UINT8      *pucData )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( BST_OS_SIZEOF(BST_UINT32) != ulLength )
    {
        BST_DBG_LOG("BST_DRV_LsItf_IoRead len is invalid");
        return 0;
    }

    if( BST_NULL_PTR == pucData )
    {
        BST_DBG_LOG("BST_DRV_LsItf_IoRead len is null ptr");
        return 0;
    }

   *( (BST_UINT32 *)pucData )           = pstLsIns->ulRankValue;
    return BST_OS_SIZEOF(BST_UINT32);
}



BST_ERR_ENUM_UINT8 BST_DRV_LsItf_IoCtrl(
    BST_UINT32      ulCmdId,
    BST_VOID       *pucData )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_UINT32                          ulQScore;
    BST_UINT32                          ulRatSn;
    BST_UINT32                          ulModemId;

    pstLsIns                            = BST_DRV_LsGetInstance();
    ulRatSn                             = BST_DRV_LsMapRatToSn( pstLsIns->ulCurRAT );
    ulModemId                           = pstLsIns->ulCurModemId;

    if( BST_NULL_PTR == pucData )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }

    switch( ulCmdId )
    {
        case BST_DRV_CMD_GET_CONGESTION:
            if( ( BST_DRV_LS_RAT_INVALID_SN == ulRatSn )
             || ( !BST_DRV_LsMdmIdValid( ulModemId ) ) )
            {
                *( (BST_UINT32 *)pucData )     = 0;
                break;
            }

            ulQScore = BST_DRV_LsCal_QValue( pstLsIns->apfReadQueInfo[ulModemId][ulRatSn] );
            if ( ulQScore >= BST_DRV_LS_FULL_SCORE )
            {
                *( (BST_UINT32 *)pucData )     = 0;
            }
            else
            {
                *( (BST_UINT32 *)pucData )     = BST_DRV_LS_FULL_SCORE - ulQScore;
            }
            break;

        default:
            return BST_ERR_ILLEGAL_PARAM;
    }

    return BST_NO_ERROR_MSG;
}



BST_UINT32 BST_DRV_LsItf_InWriteNetStrength(
    const BST_UINT32        ulModemId,
    const BST_UINT32        ulRatMode,
    const BST_UINT32        ulCellId,
    const BST_INT16         sRscp,
    const BST_INT16         sEcio )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_AS_NET_RANK_ENUM_UINT32         ulNewRank;
    BST_UINT32                          ulNetScore;
    BST_UINT32                          ulTrsScore;
    BST_UINT32                          ulQueueScore;
    BST_UINT32                          ulScore;
    BST_UINT32                          ulRatSn;

    pstLsIns                            = BST_DRV_LsGetInstance();
    ulRatSn                             = BST_DRV_LsMapRatToSn( ulRatMode );
    ulNewRank                           = BST_AS_NET_RANK_INVALID;
    ulNetScore                          = 0;
    ulTrsScore                          = 0;
    ulQueueScore                        = 0;
    ulScore                             = BST_AS_INVALID_SCORE;

    /*modem id��ͬʱ��ֱ�ӷ���*/
    if( ulModemId != pstLsIns->ulCurModemId )
    {
        return BST_FALSE;
    }

    /*������ʽ��ͬʱ��ֱ�ӷ���*/
    if( ulRatMode != pstLsIns->ulCurRAT )
    {
        return BST_FALSE;
    }

    /*��ǰ����ҵ������RAT��ʽ����GPRS,��δ��ȡ����Ч��RRC״̬ʱ,ֱ�ӷ���*/
    if( ( BST_DRV_AsIsRrcStateInvalid() ) && ( BST_AS_RAT_GPRS != ulRatMode ) )
    {
        return BST_FALSE;
    }

    /*�����ǰ������ʽ��modem idΪ��Чʱ��ֱ�ӷ���*/
    if( ( BST_DRV_LS_RAT_INVALID_SN == ulRatSn )
     || ( !BST_DRV_LsMdmIdValid( ulModemId ) ) )
    {
        return BST_FALSE;
    }

    /*Cell id�����仯������̬RLC���ش��ʵ÷���Ϊ��Ч����*/
    if( ulCellId != pstLsIns->ulCellId )
    {
        BST_DBG_LOG("Cell id is changed!");
        pstLsIns->ulCellId     = ulCellId;
        pstLsIns->ulTransScore = BST_AS_INVALID_SCORE;
    }

    BST_DBG_LOG4("ulRatMode=%d,ulCellId=%d,sRscp=%d,sEcio=%d",
                  ulRatMode, ulCellId, sRscp, sEcio);

    /************************************************************************
    * �������RAT��RRC״̬���ò�ͬ�㷨���� ulNewRank
    * ��λ����� BST_DRV_LsCal_xValue����
    * IDLE̬ÿ�����ڶ����㣬����̬ÿ��һ��ʱ�����һ�Σ��õ�ulNewRank
    **************************************************************************/

    /*IDLE̬��GSM��ʽ�¼�����·�ȼ��������ź�����*/
    if( !BST_DRV_AsIsRrcExisted() || ( BST_AS_RAT_GPRS == ulRatMode ) )
    {
        ulScore = BST_DRV_LsCal_NValue( sRscp, sEcio );
        BST_DBG_LOG1("idle state ulScore=%d", ulScore);
    }
    /*RRC����̬�¼�����·�ȼ��������ź�������RLC�ش��ʡ��������*/
    else
    {
        ulNetScore   = BST_DRV_LsCal_NValue( sRscp, sEcio );
        ulTrsScore   = BST_DRV_LsCal_TValue( pstLsIns->apfReadTrsInfo[ulModemId][ulRatSn] );
        ulQueueScore = BST_DRV_LsCal_QValue( pstLsIns->apfReadQueInfo[ulModemId][ulRatSn] );
        ulScore      = BST_DRV_LsCal_SValue( ulNetScore, ulTrsScore, ulQueueScore );
        BST_DBG_LOG4("connect state ulNetScore=%d,ulTrsScore=%d,ulQueueScore=%d,ulScore=%d",
                     ulNetScore, ulTrsScore, ulQueueScore, ulScore);
    }

    ulNewRank = BST_DRV_LsCal_RValue( ulScore );
    BST_DBG_LOG3("ulCurDValue=%d, ulTransScore=%d, ulNewRank=%d",
                  pstLsIns->ulCurDValue, pstLsIns->ulTransScore, ulNewRank);

    /*������block״̬����unblock״̬��������һ�μ����rank�ȼ�*/
    pstLsIns->ulLastRank = ulNewRank;

    if( BST_TRUE == pstLsIns->ulBlockState )
    {
        BST_RLS_LOG("ulBlockState is true, ulRankValue is BST_AS_NET_RANK_INVALID");
        return BST_TRUE;
    }

    if( ulNewRank != pstLsIns->ulRankValue )
    {
        pstLsIns->ulRankValue           = ulNewRank;
        BST_DRV_AsEventCallBack(
            BST_AS_EVT_L3_NET_RANK, BST_OS_SIZEOF(ulNewRank), &ulNewRank );

        BST_DBG_LOG1("ulRankValue is changed ulNewRank=%d", ulNewRank);
    }

    return BST_TRUE;
}
BST_ERR_ENUM_UINT8  BST_DRV_LsItf_InRegInquireFun(
    const BST_UINT32        ulModemId,
    const BST_UINT32        ulRatMode,
    BST_VOID               *pfReadTrsInfo,
    BST_VOID               *pfReadQueInfo )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( !BST_DRV_LsMdmIdValid(ulModemId) )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    if( !BST_DRV_LsIsRatSnValid(ulRatMode) )
    {
        return BST_ERR_ITEM_NOT_EXISTED;
    }

    pstLsIns->apfReadTrsInfo[ulModemId][ulRatMode]
                                        = (BST_DRV_LS_READ_TRS_FUNC)pfReadTrsInfo;
    pstLsIns->apfReadQueInfo[ulModemId][ulRatMode]
                                        = (BST_DRV_LS_READ_TRS_FUNC)pfReadQueInfo;

    return BST_NO_ERROR_MSG;
}



BST_VOID BST_DRV_LsItf_AsRatMode(
    BST_UINT32              ulRatMode )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( ulRatMode != pstLsIns->ulCurRAT )
    {
        pstLsIns->ulCellId              = BST_AS_INVALID_CELLID;
        pstLsIns->stNetSta.usCounter    = 0;
        pstLsIns->stNetSta.usIsFull     = BST_FALSE;
        pstLsIns->ulCurRrc              = BST_RRC_STATE_BUTT;

        pstLsIns->stRlcStat.ulStatFlag  = BST_FALSE;
        pstLsIns->usMovingState         = BST_DRV_LS_STATE_BUTT;
        pstLsIns->usStaticCounter       = 0;
        pstLsIns->ulTransScore          = BST_AS_INVALID_SCORE;
    }

    pstLsIns->ulCurRAT                  = ulRatMode;
    return;
}



BST_VOID BST_DRV_LsItf_NetSetDeviceState(
    BST_DRV_NET_STATE_ENUM_UINT32           ulNetDeviceStatus )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;

    pstLsIns                            = BST_DRV_LsGetInstance();
    pstLsIns->ulNetDeviceState          = ulNetDeviceStatus;

    return;
}



BST_VOID BST_DRV_LsItf_AsRrcState(
    BST_UINT32              ulRrcState )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    pstLsIns                            = BST_DRV_LsGetInstance();

    /*����RRC״̬�仯��һ��Ҫ��� ulCurDValue*/
    if( ulRrcState != pstLsIns->ulCurRrc )
    {
        pstLsIns->ulCurDValue = 0;

        if( ( BST_RRC_STATE_IDLE == ulRrcState )
         || ( BST_RRC_STATE_PCH == ulRrcState ) )
        {
            pstLsIns->stRlcStat.ulStatFlag = BST_FALSE;
        }
    }

    pstLsIns->ulCurRrc = ulRrcState;
    return;
}
BST_VOID BST_DRV_LsItf_AsBlockedState(
    BST_UINT32              ulIsBlocked )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    pstLsIns                            = BST_DRV_LsGetInstance();

    pstLsIns->ulBlockState              = ulIsBlocked;
    /*
     * ������ӿ��õ������ã������ϱ�һ��
     */
    BST_RLS_LOG1("Block state is changed new BlockeState=%d", ulIsBlocked);

    if( ( BST_AS_NET_RANK_INVALID != pstLsIns->ulRankValue )
      &&( BST_TRUE == ulIsBlocked ) )
    {
        pstLsIns->ulRankValue           = BST_AS_NET_RANK_INVALID;

        BST_DRV_AsEventCallBack(
            BST_AS_EVT_L3_NET_RANK,
            BST_OS_SIZEOF(pstLsIns->ulRankValue),
            &pstLsIns->ulRankValue );
    }

    /*����block��unblock״̬ʱ���ϱ���һ�μ�¼�����������ȼ�*/
    else if( BST_FALSE == ulIsBlocked )
    {
        pstLsIns->ulRankValue           = pstLsIns->ulLastRank;

        BST_DRV_AsEventCallBack(
            BST_AS_EVT_L3_NET_RANK,
            BST_OS_SIZEOF(pstLsIns->ulRankValue),
            &pstLsIns->ulRankValue );
    }
    else
    {
        /*for pc_lint*/
    }

    return;
}



BST_VOID BST_DRV_LsItf_AsRxInd( BST_VOID )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    pstLsIns                            = BST_DRV_LsGetInstance();
    pstLsIns->ulCurDValue               = BST_DRV_LS_TRX_ADD_SVALUE;
    return;
}



BST_VOID BST_DRV_LsItf_NetUsingModem(
    BST_UINT32              ulModemId )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_DRV_STRU                       *pDrvHandle;

    pDrvHandle                          = BST_DRV_LsGetDvcHandle();
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( ulModemId != pstLsIns->ulCurModemId )
    {
        pstLsIns->ulCurDValue               = 0;
        pstLsIns->stNetSta.usCounter        = 0;
        pstLsIns->stNetSta.usIsFull         = BST_FALSE;
        BST_RLS_LOG1("Modem Id is changed new ulModemId=%d", ulModemId);
    }
    pstLsIns->ulCurModemId = ulModemId;

    /*ap�·�modem idʱ����modem���������ģ�鷢���ź�����ע��ص���Ϣ��ֻ����һ��*/
    if( BST_FALSE == pDrvHandle->ulIsInited )
    {
        pDrvHandle->ulIsInited = BST_TRUE;
        BST_PAL_LsInit();
    }

    return;
}
BST_STATIC  BST_DRV_LS_RAT_SN_ENUM_UINT32 BST_DRV_LsMapRatToSn(
    BST_AS_RAT_MODE_UINT32  ulRatMode )
{
    switch( ulRatMode )
    {
        case BST_AS_RAT_CDMA:
            return BST_DRV_LS_RAT_INVALID_SN;

        case BST_AS_RAT_EVDO:
            return BST_DRV_LS_RAT_INVALID_SN;

        case BST_AS_RAT_GPRS:
            return BST_DRV_LS_RAT_GSM_SN;

        case BST_AS_RAT_WCDMA:
            return BST_DRV_LS_RAT_WCDMA_SN;

        case BST_AS_RAT_TDSCDMA:
            return BST_DRV_LS_RAT_TDSCDMA_SN;

        case BST_AS_RAT_LTE:
            return BST_DRV_LS_RAT_LTE_SN;

        default :
            return BST_DRV_LS_RAT_INVALID_SN;

    }
}



BST_STATIC  BST_UINT32 BST_DRV_LsCal_RValue(
    BST_UINT32              ulSValue )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_UINT32                          ulRank;

    ulRank                              = BST_AS_NET_RANK_GOOD;
    pstLsIns                            = BST_DRV_LsGetInstance();



    /*δ���㵽��Ч��SValueֵ��������һ�ε���·�ȼ�*/
    if( BST_AS_INVALID_SCORE == ulSValue )
    {
        return pstLsIns->ulLastRank;
    }

    /*��ǰ�Ƿ��������շ��ӷ����RRC״̬�仯ʱ����ֵ���㣬
      ����GSM��RRC״̬����GSM��ʽʱ��������ӷ���*/
    if( BST_AS_RAT_GPRS != pstLsIns->ulCurRAT )
    {
        ulSValue += pstLsIns->ulCurDValue;
    }

    if( BST_DRV_LS_ZERO_SCORE == ulSValue )
    {
        ulRank = BST_AS_NET_RANK_POOR;
    }
    else if( ulSValue < BST_DRV_LS_WEAK_SCORE )
    {
        /*********************************************************
        IDLE̬���������ȼ�����ж�������wcdma��lte��tdscdma��ʽ:
        (1)���������÷ֵ���BST_DRV_LS_WEAK_SCORE;
        (2)����̬���ش��ʵ÷ֵ���BST_DRV_LS_POOR_SCORE����Ϊ��Ч�������򲻿��Ǵ�������
           ֻҪ����ulSValue < BST_DRV_LS_WEAK_SCORE������Ϊ��ǰ���������ȼ�Ϊpoor.

        gsm��ʽ����RLC�ش���Ҳ��RRC״̬���ж�����Ϊ:
        (1)���������÷ֵ���BST_DRV_LS_WEAK_SCORE;
        (2)��ǰ��ʽΪGSM��ʽ.

        Connect̬���������ȼ�����ж�����:
        (1)���������÷ֵ���BST_DRV_LS_WEAK_SCORE;
        (2)����RRC����̬.
        *********************************************************/
        if( (pstLsIns->ulTransScore <= BST_DRV_LS_POOR_SCORE)
           || (BST_AS_INVALID_SCORE == pstLsIns->ulTransScore)
           || ( BST_AS_RAT_GPRS == pstLsIns->ulCurRAT )
           || ( BST_DRV_AsIsRrcExisted() ) )
        {
            ulRank = BST_AS_NET_RANK_POOR;
        }
        else
        {
            ulRank = BST_AS_NET_RANK_MIDDLE;
        }
    }
    else if ( ( ulSValue >= ( BST_DRV_LS_WEAK_SCORE + BST_DRV_LS_EXTRA_SCORE ) )
         && ( ulSValue < BST_DRV_LS_MIDD_SCORE ) )
    {
        ulRank = BST_AS_NET_RANK_MIDDLE;
    }
    else if( ulSValue >= ( BST_DRV_LS_MIDD_SCORE + BST_DRV_LS_EXTRA_SCORE ) )
    {
        ulRank = BST_AS_NET_RANK_GOOD;
    }
    else
    {
        ulRank = pstLsIns->ulLastRank;
    }

    return ulRank;
}



BST_STATIC  BST_UINT32 BST_DRV_LsCal_SValue(
    BST_UINT32              ulNValue,
    BST_UINT32              ulTValue,
    BST_UINT32              ulQValue )
{
    BST_UINT32                          ulScore;
    BST_UINT32                          ulRate;

    ulScore                             = BST_AS_INVALID_SCORE;
    ulRate                              = BST_DRV_LS_NONE_USED_BIT;

    /*��ulTValue��ulQValue����һ��ֵ����Ϊ0ʱ������Ϊ��ǰ��·����Ϊ��*/
    if( ( BST_DRV_LS_ZERO_SCORE == ulTValue )
     || ( BST_DRV_LS_ZERO_SCORE == ulQValue ) )
    {
        ulScore = BST_DRV_LS_ZERO_SCORE;
        return ulScore;
    }

    /*��ulNValueֵ��Чʱ�������Ȩ��*/
    if( BST_AS_INVALID_SCORE != ulNValue )
    {
        ulRate = ulRate | BST_DRV_LS_N_USED_BIT;
    }

    /*��ulTValueֵ��Чʱ�������Ȩ��*/
    if( BST_AS_INVALID_SCORE != ulTValue )
    {
        ulRate = ulRate | BST_DRV_LS_T_USED_BIT;
    }

    /*��ulQValueֵ��Чʱ�������Ȩ��*/
    if( BST_AS_INVALID_SCORE != ulQValue )
    {
        ulRate = ulRate | BST_DRV_LS_Q_USED_BIT;
    }

    ulScore = BST_DRV_LsCal_Score( ulRate, ulNValue, ulTValue, ulQValue );

    return ulScore;
}



BST_STATIC  BST_UINT32 BST_DRV_LsCal_Score(
  BST_UINT32                 ulRate,
  BST_UINT32                 ulNValue,
  BST_UINT32                 ulTValue,
  BST_UINT32                 ulQValue )
{
    BST_UINT32                          ulScore;

    ulScore                             = 0;

    switch( ulRate )
    {
        /*N��T��Q����Ч,Nռ50%, Tռ25% Qռ25%*/
        case BST_DRV_LS_ALL_USED_BIT:
            ulScore += ( ulNValue >> BST_DRV_LS_BIT1_FAC );
            ulScore += ( ulTValue >> BST_DRV_LS_BIT2_FAC );
            ulScore += ( ulQValue >> BST_DRV_LS_BIT2_FAC );
            break;

        /*N��Q��Ч,��ռ50%*/
        case BST_DRV_LS_NQ_USED_BIT:
            ulScore = ( ( ulNValue + ulQValue ) >> BST_DRV_LS_BIT1_FAC );
            break;

        /*N��T��Ч,��ռ50%*/
        case BST_DRV_LS_NT_USED_BIT:
            ulScore = ( ( ulNValue + ulTValue ) >> BST_DRV_LS_BIT1_FAC );
            break;

        /*T��Q��Ч,��ռ50%*/
        case BST_DRV_LS_TQ_USED_BIT:
            ulScore = ( ( ulTValue + ulQValue ) >> BST_DRV_LS_BIT1_FAC );
            break;

        /*����N��Ч*/
        case BST_DRV_LS_N_USED_BIT:
            ulScore = ulNValue;
            break;

        /*����Q��Ч*/
        case BST_DRV_LS_Q_USED_BIT:
            ulScore = ulQValue;
            break;

        /*����T��Ч*/
        case BST_DRV_LS_T_USED_BIT:
            ulScore = ulTValue;
            break;

        default:
            return BST_AS_INVALID_SCORE;
    }

    return ulScore;
}
BST_STATIC  BST_UINT32 BST_DRV_LsCal_TValue(
    BST_DRV_LS_READ_TRS_FUNC   pfTrsFun )
{
    BST_UINT32                          ulScore;
    BST_UINT32                          ulTotalPkt;
    BST_UINT32                          ulTotalRePkt;
    BST_UINT32                          ulReTxRate;
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_DRV_LS_THRESHOLD_STRU          *pstThold;

    pstLsIns                            = BST_DRV_LsGetInstance();
    pstThold                            = BST_DRV_LsGetNetThreshold();
    ulTotalPkt                          = 0;
    ulTotalRePkt                        = 0;
    ulReTxRate                          = 0;
    ulScore                             = BST_AS_INVALID_SCORE;

    if( BST_NULL_PTR == pfTrsFun )
    {
        return BST_AS_INVALID_SCORE;
    }

    pfTrsFun( &ulTotalPkt, &ulTotalRePkt );

    if( ( BST_AS_RAT_LTE == pstLsIns->ulCurRAT )
     || ( BST_AS_RAT_TDSCDMA == pstLsIns->ulCurRAT ) )
    {
        /*��һ��������̬����TL��ʽ��RLC���ش��ʣ��ȱ��浱ǰ�ۻ�ֵ*/
        if( BST_FALSE == pstLsIns->stRlcStat.ulStatFlag )
        {
            pstLsIns->stRlcStat.ulStatFlag   = BST_TRUE;
            pstLsIns->stRlcStat.ulTotalPkt   = ulTotalPkt;
            pstLsIns->stRlcStat.ulTotalRePkt = ulTotalRePkt;

            return BST_AS_INVALID_SCORE;
        }

        ulTotalPkt   = BST_DRV_LS_MOD_SUB( ulTotalPkt, pstLsIns->stRlcStat.ulTotalPkt );
        ulTotalRePkt = BST_DRV_LS_MOD_SUB( ulTotalRePkt, pstLsIns->stRlcStat.ulTotalRePkt );
    }

    BST_DBG_LOG2("ulTotalPkt=%d, ulTotalRePkt=%d",ulTotalPkt, ulTotalRePkt );

    /*������PDU��������С��BST_DRV_LS_TX_PKT_NUMʱ��������RLC�ش��ʣ�ֻ�е����ڵ�ʱ��ż���*/
    if( ulTotalPkt < BST_DRV_LS_TX_PKT_NUM )
    {
        return pstLsIns->ulTransScore;
    }

    /*����RLC�ش��ʣ��ȳ���100*/
    ulReTxRate = ( ulTotalRePkt * BST_DRV_LS_ONE_HUNDRED ) / ulTotalPkt;

    switch( pstLsIns->ulCurRAT )
    {
        case BST_AS_RAT_LTE:
            ulScore = BST_DRV_LsCal_TScore( ulReTxRate,
                                            pstThold->lte.usReTxMin,
                                            pstThold->lte.usReTxMax );
            break;

        case BST_AS_RAT_WCDMA:
            ulScore = BST_DRV_LsCal_TScore( ulReTxRate,
                                            pstThold->wcdma.usReTxMin,
                                            pstThold->wcdma.usReTxMax );
            break;

        case BST_AS_RAT_TDSCDMA:
            ulScore = BST_DRV_LsCal_TScore( ulReTxRate,
                                            pstThold->tdscdma.usReTxMin,
                                            pstThold->tdscdma.usReTxMax );
            break;

        default:
            BST_RLS_LOG("BST_DRV_LsCal_TValue invalid rat mode");
            break;
    }

    /*��¼����̬��RLC�ش��ʵ÷֣��Թ�IDLE̬��ʹ��*/
    pstLsIns->ulTransScore = ulScore;

    return ulScore;
}



BST_STATIC  BST_UINT32 BST_DRV_LsCal_TScore(
  BST_UINT32                            ulReTxRate,
  BST_UINT16                            usReTxMin,
  BST_UINT16                            usReTxMax)
{
    BST_UINT32                          ulScore;

    ulScore                             = BST_AS_INVALID_SCORE;

    if(  ulReTxRate <= usReTxMin )
    {
        ulScore = BST_DRV_LS_FULL_SCORE;
    }
    else if( ulReTxRate >= usReTxMax )
    {
        ulScore = 0;
    }
    else
    {
        /*����ֵ�ȳ���100����������������ֵ*/
        ulScore = ( usReTxMax - ulReTxRate ) * BST_DRV_LS_ONE_HUNDRED;
        ulScore = ulScore / ( (BST_UINT16)( usReTxMax - usReTxMin ) );
    }

    return ulScore;
}
BST_STATIC  BST_UINT32 BST_DRV_LsCal_QValue(
    BST_DRV_LS_READ_QUE_FUNC   pfQueFun )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_UINT32                          ulScore;
    BST_UINT32                          ulQueLength;
    BST_UINT32                          ulBandWidth;

    ulQueLength                         = 0;
    ulBandWidth                         = 0;
    ulScore                             = BST_AS_INVALID_SCORE;
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( BST_NULL_PTR == pfQueFun )
    {
        return BST_AS_INVALID_SCORE;
    }

    pfQueFun( &ulQueLength, &ulBandWidth );
    BST_DBG_LOG1("ulQueLength=%d", ulQueLength);

    /*���������С��BST_DRV_LS_QUE_LEN_MIN�������㻺�������ռȨ��*/
    if( ulQueLength < BST_DRV_LS_QUE_LEN_MIN )
    {
        return BST_AS_INVALID_SCORE;
    }

    switch( pstLsIns->ulCurRAT )
    {
        case BST_AS_RAT_LTE:
            /*lte ��������Ĭ��Ϊ512k bit/s������9λ*/
            ulScore = BST_DRV_LsCal_QScore( ulQueLength >> BST_DRV_LS_BIT9_FAC,
                                            BST_DRV_LS_QUE_HIGH,
                                            BST_DRV_LS_QUE_LOW );
            break;

        case BST_AS_RAT_WCDMA:
            /*wcdma ��������Ĭ��Ϊ256k bit/s������8λ*/
            ulScore = BST_DRV_LsCal_QScore( ulQueLength >> BST_DRV_LS_BIT8_FAC,
                                            BST_DRV_LS_QUE_HIGH,
                                            BST_DRV_LS_QUE_LOW );
            break;

        case BST_AS_RAT_TDSCDMA:
            /*tdscdma ��������Ĭ��Ϊ64k bit/s������6λ*/
            ulScore = BST_DRV_LsCal_QScore( ulQueLength >> BST_DRV_LS_BIT6_FAC,
                                            BST_DRV_LS_QUE_HIGH,
                                            BST_DRV_LS_QUE_LOW );
            break;

        case BST_AS_RAT_GPRS:
            /*gsm ��������Ĭ��Ϊ8k bit/s������3λ*/
            ulScore = BST_DRV_LsCal_QScore( ulQueLength >> BST_DRV_LS_BIT3_FAC,
                                            BST_DRV_LS_QUE_HIGH,
                                            BST_DRV_LS_QUE_LOW );
            break;

        default:
            BST_RLS_LOG("BST_DRV_LsCal_QValue invalid rat mode");
            break;
    }

    return ulScore;
}
BST_STATIC  BST_UINT32 BST_DRV_LsCal_QScore(
  BST_UINT32                            ulQueLength,
  BST_UINT32                            ulQueHigh,
  BST_UINT32                            ulQueLow)
{
    BST_UINT32                          ulScore;

    ulScore                             = BST_AS_INVALID_SCORE;

    /*�������ʱ��С��ulQueLow*/
    if( ulQueLength <= ulQueLow )
    {
        ulScore = BST_DRV_LS_FULL_SCORE;
    }
    /*�������ʱ�����ulQueHigh*/
    else if( ulQueLength >= ulQueHigh )
    {
        ulScore = 0;
    }
    else
    {
        /*����ֵ�ȳ���100����������������ֵ*/
        ulScore = ( ulQueHigh - ulQueLength ) * BST_DRV_LS_ONE_HUNDRED;
        ulScore = ulScore >> BST_DRV_LS_BIT13_FAC;
    }

    return ulScore;
}
BST_STATIC  BST_UINT32 BST_DRV_LsCal_NValue(
    BST_INT16                    sRscp,
    BST_INT16                    sEci0 )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_INT16                           sRscpAvg;
    BST_INT16                           sEci0Avg;
    BST_UINT32                          ulScore;
    BST_DRV_LS_THRESHOLD_STRU          *pstThold;

    sRscpAvg                            = 0;
    sEci0Avg                            = 0;
    ulScore                             = BST_AS_INVALID_SCORE;
    pstThold                            = BST_DRV_LsGetNetThreshold();
    pstLsIns                            = BST_DRV_LsGetInstance();

    /*RSCPΪ�쳣ֵ��������Ч����*/
    if( sRscp >= 0 )
    {
        return BST_AS_INVALID_SCORE;
    }

    /*�����źž�ֵ�ͷ���*/
    BST_DRV_LsCal_RscpAvg( sRscp, sEci0, &sRscpAvg, &sEci0Avg );

    switch( pstLsIns->ulCurRAT )
    {
        case BST_AS_RAT_LTE:
        case BST_AS_RAT_WCDMA:
            ulScore = BST_DRV_LsCal_LW_NCore( sRscpAvg,
                                              sEci0Avg );
            break;

        case BST_AS_RAT_TDSCDMA:
            ulScore = BST_DRV_LsCal_TG_NCore( pstThold->tdscdma.sRscpMin,
                                              pstThold->tdscdma.sRscpMax,
                                              sRscpAvg );
            break;

        case BST_AS_RAT_GPRS:
            ulScore = BST_DRV_LsCal_TG_NCore( pstThold->gsm.sRxLevAMin,
                                              pstThold->gsm.sRxLevAMax,
                                              sRscpAvg );
            break;

        default:
            BST_RLS_LOG("BST_DRV_LsCal_NValue invalid rat mode");
            break;
    }

    return ulScore;
}



BST_STATIC  BST_VOID BST_DRV_LsCal_RscpAvg(
    BST_INT16                    sRscp,
    BST_INT16                    sEci0,
    BST_INT16                    *psRscpAvg,
    BST_INT16                    *psEci0Avg )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_UINT8                           ucIndex;
    BST_INT16                           sRscpSum;
    BST_INT16                           sEci0Sum;

    BST_UINT16                          usCounter;
    BST_INT16                           sRscpAvg;
    BST_INT16                           sEci0Avg;

    sRscpSum                            = 0;
    sEci0Sum                            = 0;
    sRscpAvg                            = 0;
    sEci0Avg                            = 0;
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( ( BST_NULL_PTR == psRscpAvg ) || ( BST_NULL_PTR == psEci0Avg ) )
    {
        return;
    }

    /*TL��ʽ�²��ü�ʱֵ���޾�ֵ�ͷ���ļ��㣬WG��ʽ�²��û���ƽ��ֵ*/
    if( ( BST_AS_RAT_LTE == pstLsIns->ulCurRAT )
     || ( BST_AS_RAT_TDSCDMA == pstLsIns->ulCurRAT ) )
    {
        sRscpAvg                = sRscp;
        sEci0Avg                = sEci0;
        pstLsIns->usMovingState = BST_DRV_LS_STATE_STATIC;
    }
    else
    {
        pstLsIns->stNetSta.asRscp[pstLsIns->stNetSta.usCounter] = sRscp;
        pstLsIns->stNetSta.asEcI0[pstLsIns->stNetSta.usCounter] = sEci0;
        pstLsIns->stNetSta.usCounter++;

        if( BST_DRV_LS_BUF_LENGTH == pstLsIns->stNetSta.usCounter )
        {
            pstLsIns->stNetSta.usCounter = 0;
            pstLsIns->stNetSta.usIsFull  = BST_TRUE;
        }

        /*���ݻ�����δ��ʱ����ʵ����Ч���������ֵ*/
        if( BST_FALSE == pstLsIns->stNetSta.usIsFull )
        {
            for( ucIndex = 0; ucIndex < pstLsIns->stNetSta.usCounter; ucIndex++ )
            {
                sRscpSum += pstLsIns->stNetSta.asRscp[ucIndex];
                sEci0Sum += pstLsIns->stNetSta.asEcI0[ucIndex];
            }
            usCounter = pstLsIns->stNetSta.usCounter;
        }
        else /*���ݻ���������*/
        {
            for( ucIndex = 0; ucIndex < BST_DRV_LS_BUF_LENGTH; ucIndex++ )
            {
                sRscpSum += pstLsIns->stNetSta.asRscp[ucIndex];
                sEci0Sum += pstLsIns->stNetSta.asEcI0[ucIndex];
            }
            usCounter = BST_DRV_LS_BUF_LENGTH;
        }

        sRscpAvg = ( sRscpSum / usCounter );
        sEci0Avg = ( sEci0Sum / usCounter );

        /*���㷽��, WG��ʽ�¼���*/
        BST_DRV_LsCal_RscpVrc( sRscpAvg );
    }

    *psRscpAvg = sRscpAvg;
    *psEci0Avg = sEci0Avg;

    BST_DBG_LOG2("sRscpAvg=%d, sEci0Avg=%d", sRscpAvg, sEci0Avg );
}


BST_STATIC  BST_VOID BST_DRV_LsCal_RscpVrc( BST_INT16 sRscpAvg )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_INT16                           sRscpVrc;
    BST_UINT8                           ucIndex;

    sRscpVrc                            = 0;
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( BST_TRUE != pstLsIns->stNetSta.usIsFull )
    {
        return;
    }

    for( ucIndex = 0; ucIndex < BST_DRV_LS_BUF_LENGTH; ucIndex++ )
    {
        sRscpVrc += (BST_INT16)(abs(pstLsIns->stNetSta.asRscp[ucIndex] - sRscpAvg));
    }

    /*���ݷ���ֵ�ж϶���̬*/
    if( sRscpVrc <= BST_DRV_LS_STATIC_VRC )
    {
        pstLsIns->usStaticCounter++;
        /*��̬����������BST_DRV_LS_STATIC_CNT������Ϊ��ǰ���ھ�ֹ״̬*/
        if( pstLsIns->usStaticCounter >= BST_DRV_LS_STATIC_CNT )
        {
            pstLsIns->usStaticCounter = BST_DRV_LS_STATIC_CNT;
            pstLsIns->usMovingState   = BST_DRV_LS_STATE_STATIC;
        }
    }
    else
    {
        if( pstLsIns->usStaticCounter > 0 )
        {
            pstLsIns->usStaticCounter--;
        }
        else
        {
             pstLsIns->usStaticCounter = 0;
        }

        /*��̬������С��BST_DRV_LS_DYNAMIC_CNT������Ϊ��ǰ�����ƶ�״̬*/
        if( pstLsIns->usStaticCounter < BST_DRV_LS_DYNAMIC_CNT )
        {
            pstLsIns->usMovingState = BST_DRV_LS_STATE_DYNAMIC;
        }
    }

    BST_DBG_LOG3("sRscpVrc=%d, usStaticCounter=%d, usMovingState=%d",
                  sRscpVrc, pstLsIns->usStaticCounter, pstLsIns->usMovingState );

    return;
}
BST_STATIC  BST_UINT32 BST_DRV_LsCal_LW_NCore(
    BST_INT16                    sRscpAvg,
    BST_INT16                    sEci0Avg )
{
    BST_UINT32                          ulScore;
    BST_UINT32                          ulRscpScore;
    BST_UINT32                          ulEci0Score;
    BST_INT16                           sRscpMin;
    BST_INT16                           sRscpMax;
    BST_INT16                           sEci0Min;
    BST_INT16                           sEci0Max;
    BST_DRV_LS_THRESHOLD_STRU          *pstThold;
    BST_DRV_LS_INS_STRU                *pstLsIns;

    pstLsIns                            = BST_DRV_LsGetInstance();
    pstThold                            = BST_DRV_LsGetNetThreshold();
    ulScore                             = BST_AS_INVALID_SCORE;

    if( BST_AS_RAT_LTE == pstLsIns->ulCurRAT )
    {
        sRscpMin = pstThold->lte.sRsrpMin;
        sRscpMax = pstThold->lte.sRsrpMax;
        sEci0Min = pstThold->lte.sRsrqMin;
        sEci0Max = pstThold->lte.sRsrqMax;
    }
    else
    {
        sRscpMin = pstThold->wcdma.sRscpMin;
        sRscpMax = pstThold->wcdma.sRscpMax;
        sEci0Min = pstThold->wcdma.sEci0Min;
        sEci0Max = pstThold->wcdma.sEci0Max;
    }

    /*����RSCPֵ�÷�*/
    if( sRscpAvg <= sRscpMin )
    {
        ulRscpScore = 0;
    }
    else if( sRscpAvg >= sRscpMax )
    {
        ulRscpScore = BST_DRV_LS_FULL_SCORE;
    }
    else
    {
        /*����ֵ�ȳ���100����������������ֵ*/
        ulRscpScore = ( sRscpAvg - sRscpMin ) * BST_DRV_LS_ONE_HUNDRED;
        ulRscpScore = ulRscpScore >> BST_DRV_LS_BIT5_FAC;
    }

    /*����ECI0ֵ�÷�*/
    if( sEci0Avg <= sEci0Min )
    {
        ulEci0Score = 0;
    }
    else if( sEci0Avg >= sEci0Max )
    {
        ulEci0Score = BST_DRV_LS_FULL_SCORE;
    }
    else
    {
        /*����ֵ�ȳ���100����������������ֵ*/
        ulEci0Score = ( sEci0Avg - sEci0Min ) * BST_DRV_LS_ONE_HUNDRED;
        ulEci0Score = ulEci0Score >> BST_DRV_LS_BIT4_FAC;
    }

    ulScore = ( ulRscpScore + ulEci0Score ) >> BST_DRV_LS_BIT1_FAC;

    return ulScore;
}


BST_STATIC  BST_UINT32 BST_DRV_LsCal_TG_NCore(
    BST_INT16                    sRscpMin,
    BST_INT16                    sRscpMax,
    BST_INT16                    sRscpAvg )
{
    BST_UINT32                          ulScore;

    ulScore                             = BST_AS_INVALID_SCORE;

    if( sRscpAvg <= sRscpMin )
    {
        ulScore = 0;
    }
    else if( sRscpAvg >= sRscpMax )
    {
        ulScore = BST_DRV_LS_FULL_SCORE;
    }
    else
    {
        /*����ֵ�ȳ���100����������������ֵ*/
        ulScore = ( sRscpAvg - sRscpMin ) * BST_DRV_LS_ONE_HUNDRED;
        ulScore = ulScore >> BST_DRV_LS_BIT5_FAC;
    }

    return ulScore;
}
BST_VOID BST_DRV_LsItf_InitThreshold( BST_VOID )
{
    const BST_INT16                     asNetThreshold[] =
    {
        -110,    /* GSM �ź�ǿ��������Сֵ */
        -78,     /* GSM �ź�ǿ���������ֵ */
        -117,    /* TDSCDMA �ź�ǿ��������Сֵ */
        -85,     /* TDSCDMA �ź�ǿ���������ֵ */
        5,       /* TDSCDMA �ش���������Сֵ */
        65,      /* TDSCDMA �ش����������ֵ */
        -120,    /* WCDMA �źŹ���������Сֵ */
        -88,     /* WCDMA �źŹ����������ֵ */
        -21,     /* WCDMA �ź�����������Сֵ */
        -5,      /* WCDMA �ź������������ֵ */
        1,       /* WCDMA �ش���������Сֵ */
        55,      /* WCDMA �ش����������ֵ */
        -125,    /* LTE �źŹ���������Сֵ */
        -93,     /* LTE �źŹ����������ֵ */
        -21,     /* LTE �ź�����������Сֵ */
        -5,      /* LTE �ź������������ֵ */
        1,       /* LTE �ش���������Сֵ */
        50       /* LTE �ش����������ֵ */
    };

    /* �����������޸�ֵ */
    BST_OS_MEMCPY( BST_DRV_LsGetNetThreshold(),
                   &asNetThreshold[0],
                   BST_OS_SIZEOF( BST_DRV_LS_THRESHOLD_STRU ) );

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

