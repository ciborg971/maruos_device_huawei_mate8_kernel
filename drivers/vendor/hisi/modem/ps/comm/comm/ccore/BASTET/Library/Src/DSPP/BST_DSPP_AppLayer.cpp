

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_DSPP_AppLayer.h"
#include "BST_DSPP_CtrLayer.h"
#include "BST_DSPP_TrsLayer.h"
#include "BST_DBG_MemLeak.h"
#include "BST_SRV_Event.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_DSPP_APPLAYER_CPP
/*lint +e767*/

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
******************************************************************************/


BST_DSPP_CAppDlVa::BST_DSPP_CAppDlVa( BST_VOID )
    : BST_DSPP_CDlLayerBase( BST_DSPP_LAYER_APP, BST_DSPP_VER_A )
{
    m_pcTaskManager = BST_SRV_CTaskMng::GetInstance ();
}


BST_DSPP_CAppDlVa::~BST_DSPP_CAppDlVa( BST_VOID )
{
    m_pcTaskManager                     = BST_NULL_PTR;
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::ParseHeadInfo(
    BST_DSPP_HEAD_STRU   *const pstHead,
    BST_UINT8 const      *pucData,
    BST_UINT16            usLength )
{
    return BST_NO_ERROR_MSG;
}


BST_UINT16 BST_DSPP_CAppDlVa::ReadOut(
    BST_DSPP_OBJTADDR_T     usObjtAddr,
    BST_DSPP_OFSTADDR_T     usOfstAddr,
    BST_UINT8              *pucSrcBuff,
    BST_UINT8              *pucDstBuff,
    BST_UINT16              usSrcLen,
    BST_UINT16              usDstLen )
{

    BST_CORE_PID_LEN_T                  usParamLen;
    BST_CORE_PID_ENUM_UINT16            usParamId;
    BST_UINT16                          usLooper;
    BST_UINT16                          usResBufCnt;

    usResBufCnt                         = 0;
    for ( usLooper = 0;
          usLooper < usSrcLen;
          usLooper += BST_CORE_PID_LEN )
    {

        /*
         * ��ȡPID���
         */
        usParamId                       = BST_DSPP_AP_BYTE2PID
                                         ( pucSrcBuff[ usLooper ], pucSrcBuff[ usLooper + 1 ] );
        /*
         * ��ȡ�������泤��
         * |--PL(2 BYTE)--|--PID(2 BYTE)--|--Content( usParamLen���������)--|
         * ��ˣ����뻺�峤������ΪBST_OS_SIZEOF ( BST_CORE_PID_LEN_T )+BST_CORE_PID_LEN
         */
        usParamLen                      = m_pcTaskManager->Inquire
                                         ( usObjtAddr, usOfstAddr, usParamId,
                                         ( BST_UINT16 )( usDstLen - usResBufCnt
                                                       - BST_OS_SIZEOF ( BST_CORE_PID_LEN_T )
                                                       - BST_CORE_PID_LEN ),
                                                        pucDstBuff + usResBufCnt
                                                        + BST_OS_SIZEOF ( BST_CORE_PID_LEN_T )
                                                        + BST_CORE_PID_LEN );
        BST_DBG_LOG4( "DSPP Inquire: procid=%u, taskid=%u, pid=%u, plen=%u",
                      usObjtAddr, usOfstAddr, usParamId, usParamLen );

        /*
         * �������Ȼ�ȡ�ɹ��󣬸��ƻ���������
         */
        if ( 0 != usParamLen )
        {
            usParamLen                 += ( BST_OS_SIZEOF ( BST_CORE_PID_LEN_T ) + BST_CORE_PID_LEN );
            pucDstBuff[usResBufCnt]    = BST_DSPP_U16_TO_U8L ( usParamLen );
            pucDstBuff[usResBufCnt+1]  = BST_DSPP_U16_TO_U8H ( usParamLen );
            pucDstBuff[usResBufCnt+2]  = BST_DSPP_U16_TO_U8L ( usParamId );
            pucDstBuff[usResBufCnt+3]  = BST_DSPP_U16_TO_U8H ( usParamId );
            usResBufCnt               += usParamLen;
        }

        /*
         * ���������ȡ���ȳ��ޣ���ô���������β�����ȡ����
         */
        if ( usResBufCnt + BST_OS_SIZEOF ( BST_CORE_PID_LEN_T ) + BST_CORE_PID_LEN > usDstLen )
        {
            break;
        }
    }
    return usResBufCnt;
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::Inquire(
    BST_DSPP_OBJTADDR_T    usObjtAddr,
    BST_DSPP_OFSTADDR_T    usOfstAddr,
    BST_DSPP_HEAD_STRU    *const pstRxHeadInfo )
{
    BST_CORE_PID_LEN_T          usParamLen;
    BST_CORE_PID_ENUM_UINT16    usParamId;
    BST_UINT16                  usLooper;
    BST_UINT16                  usResBufCnt;
    BST_UINT8                  *pucData;
    BST_UINT8                  *pcResBuffer;
    BST_UINT16                  usPktTotLen;

    usLooper                    = 0;
    usParamLen                  = 0;
    usPktTotLen                 = 0;
    usResBufCnt                 = 0;
    usParamId                   = BST_PID_INVALID;
    pcResBuffer                 = BST_NULL_PTR;
    pucData                     = pstRxHeadInfo->pucData;

    /*
     * ����������
     */
    if ( ( BST_NULL_PTR == m_pcTaskManager )
     || ( BST_NULL_PTR == pstRxHeadInfo ) )
    {
        return BST_ERR_INVALID_PTR;
    }

    if ( !BST_DSPP_IsObjIdValid (usObjtAddr) )
    {
        BST_RLS_LOG1( "BST_DSPP_CAppDlVa::Inquire usObjtAddr=%u",
                      usObjtAddr );
        return BST_ERR_UNKNOW_OBJ;
    }

    if ( ( BST_NULL_PTR == pucData )
     || ( BST_CORE_PID_LEN > pstRxHeadInfo->usLength ) )
    {
        return BST_ERR_PAR_LEN;
    }

    if ( ( pstRxHeadInfo->usLength % BST_CORE_PID_LEN ) != 0 )
    {
        BST_RLS_LOG1( "BST_DSPP_CAppDlVa::Inquire pstRxHeadInfo->usLength=%u",
                      pstRxHeadInfo->usLength );
        return BST_ERR_PAR_LEN;
    }

    /*
     * ���Ȼ�ȡԤ��ѯ�������ܳ���
     */
    for ( usLooper = 0;
          usLooper < pstRxHeadInfo->usLength;
          usLooper+= BST_CORE_PID_LEN )
    {
        usParamId               = BST_DSPP_AP_BYTE2PID
                                ( pucData[usLooper], pucData[usLooper + 1] );
        usParamLen              = m_pcTaskManager->GetLen
                                ( usObjtAddr, usOfstAddr, usParamId );

        if ( 0 != usParamLen )
        {
            usPktTotLen        += ( BST_OS_SIZEOF ( BST_CORE_PID_LEN_T )
                                  + BST_CORE_PID_LEN
                                  + usParamLen );
        }
    }
    if ( 0 == usPktTotLen )
    {
        return BST_ERR_PAR_UNKNOW;
    }
    /*
     * ����Ŀ�껺����Դ
     */
    pcResBuffer                 = ( BST_UINT8 * )BST_OS_MALLOC ( usPktTotLen );
    if ( BST_NULL_PTR == pcResBuffer )
    {
        return BST_ERR_NO_MEMORY;
    }
    BST_OS_MEMSET( pcResBuffer, 0, usPktTotLen );
    /*
     * ��PID���ݿ����Ӧ�ó����ò�������
     */
    usResBufCnt                 = ReadOut( usObjtAddr, usOfstAddr, pucData, pcResBuffer,
                                           pstRxHeadInfo->usLength, usPktTotLen );
    /*
     * Memory Leak! If we malloc the space but copy none, We shoud release it here;
     */
    if ( 0 == usResBufCnt )
    {
        BST_OS_FREE ( pcResBuffer );
        pcResBuffer             = BST_NULL_PTR;
    }
    /*
     * �������û��������ݣ���Ӧ��ʹ��
     */
    pstRxHeadInfo->pucData      = pcResBuffer;
    pstRxHeadInfo->usLength     = usResBufCnt;
    return BST_NO_ERROR_MSG;
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::Config(
    BST_DSPP_OBJTADDR_T usObjtAddr,
    BST_DSPP_OFSTADDR_T usOfstAddr,
    BST_DSPP_HEAD_STRU *const pstRxHeadInfo )
{
    BST_CORE_PID_LEN_T          usParamLen;
    BST_CORE_PID_ENUM_UINT16    usParamId;
    BST_UINT8                  *pcData;
    BST_UINT16                  usBufCnt;
    BST_ERR_ENUM_UINT8          ucRtnVal;

    if ( BST_NULL_PTR == pstRxHeadInfo )
    {
        return BST_ERR_INVALID_PTR;
    }
    usParamLen                  = 0;
    usBufCnt                    = 0;
    usParamId                   = BST_PID_INVALID;
    ucRtnVal                    = BST_NO_ERROR_MSG;
    pcData                      = pstRxHeadInfo->pucData;

    /*
     * ��ڼ��
     */
    if ( BST_NULL_PTR == m_pcTaskManager )
    {
        return ( BST_ERR_INVALID_PTR );
    }

    if ( !BST_DSPP_IsObjIdValid (usObjtAddr) )
    {
        BST_RLS_LOG1( "BST_DSPP_CAppDlVa::Config usObjtAddr=%u",
                      usObjtAddr );
        return ( BST_ERR_UNKNOW_OBJ );
    }

    if( BST_CORE_PID_LEN > pstRxHeadInfo->usLength )
    {
        return ( BST_ERR_PAR_LEN );
    }

    for (;;)
    {
        /*
         * ���ʣ�����ݳ����޷���ȡ��ЧPID��Ϣ����ôֱ���˳��򷵻�
         */
        if ( pstRxHeadInfo->usLength - usBufCnt <= BST_DSPP_AP_CMD_HEAD_LEN )
        {
            if ( pstRxHeadInfo->usLength == usBufCnt )
            {
                ucRtnVal        = BST_NO_ERROR_MSG;
            }
            else
            {
                ucRtnVal        = BST_ERR_PAR_LEN;
            }
            break;
        }
        /*
         * ��ȡPID���ȣ�PID���Ƶ���Ϣ
         */
        usParamLen              = ( BST_CORE_PID_LEN_T )BST_DSPP_U8_TO_U16
                                  ( pcData[BST_DSPP_AP_CMD_LEN_L],
                                    pcData[BST_DSPP_AP_CMD_LEN_H] )
                                   -BST_DSPP_AP_CMD_HEAD_LEN;
        usParamId               = BST_DSPP_AP_BYTE2PID
                                ( pcData[BST_DSPP_AP_CMD_ID_L],
                                  pcData[BST_DSPP_AP_CMD_ID_H] );
        pcData                 += BST_DSPP_AP_CMD_HEAD_LEN;
        usBufCnt               += BST_DSPP_AP_CMD_HEAD_LEN;

        /*
         * ���ʣ�����ݳ�����������Ľ�������ϣ����ȡʶ���޷���������
         */
        if ( ( pstRxHeadInfo->usLength - usBufCnt ) < usParamLen )
        {
            BST_RLS_LOG3( "BST_DSPP_CAppDlVa::Config usLength=%u,usBufCnt=%u,usParamLen=%u",
                          pstRxHeadInfo->usLength, usBufCnt, usParamLen );
            ucRtnVal            = BST_ERR_PAR_LEN;
            break;
        }
        /*
         * д�����ֵ
         */
        ucRtnVal                = m_pcTaskManager->Config
                                 ( usObjtAddr, usOfstAddr, usParamId,
                                   usParamLen, pcData );
        if ( BST_NO_ERROR_MSG == ucRtnVal )
        {
            pcData             += usParamLen;
            usBufCnt           += usParamLen;
        }
        else
        {
            break;
        }
    }
    return ( ucRtnVal );
}


 BST_ERR_ENUM_UINT8 BST_DSPP_CAppDlVa::Assign(
    BST_DSPP_HEAD_STRU     *const pstRxHeadInfo,
    BST_OS_MBX_T          **ppstMbox )
{
    BST_UINT16              usOfstAddr;
    /*
     * ��ڼ��
     */
    if ( ( BST_NULL_PTR == m_pcTaskManager )
      || ( BST_NULL_PTR == pstRxHeadInfo )
      || ( BST_NULL_PTR == ppstMbox ) )
    {
        return ( BST_ERR_INVALID_PTR );
    }
    /*
     * У��PID�Ƿ���Ч
     */
    if ( !BST_DSPP_IsObjIdValid (pstRxHeadInfo->stCpVerA.usObjtAddr) )
    {
        return ( BST_ERR_UNKNOW_OBJ );
    }

    /*
     * �������������ȡ�������ID���
     */
    usOfstAddr              = m_pcTaskManager->Assign 
                            ( pstRxHeadInfo->stCpVerA.usObjtAddr,
                              pstRxHeadInfo->stCpVerA.usOfstAddr, ppstMbox );
    BST_DBG_LOG2( "DSPP Assign: procid=%u, taskid=%u", pstRxHeadInfo->stCpVerA.usObjtAddr, usOfstAddr );
    if( ( BST_DSPP_INVALID_ADDR == usOfstAddr )
      ||( BST_NULL_PTR == ppstMbox ) )
    {
        return ( BST_ERR_NO_MEMORY );
    }
    /*
     * ���ֲ���ֵ�����
     */
    pstRxHeadInfo->stCpVerA.usOfstAddr  = usOfstAddr;
    pstRxHeadInfo->enApVer              = BST_DSPP_VER_VOID;
    return ( BST_NO_ERROR_MSG );
}

BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::Remove(
    BST_DSPP_OBJTADDR_T usObjtAddr,
    BST_DSPP_OFSTADDR_T usOfstAddr )
{
    if ( BST_NULL_PTR == m_pcTaskManager )
    {
        return BST_ERR_INVALID_PTR;
    }
    if ( BST_DSPP_INVALID_ADDR == usOfstAddr )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    BST_DBG_LOG2( "DSPP Remove: procid=%u, taskid=%u", usObjtAddr, usOfstAddr );
    return ( m_pcTaskManager->Remove ( usObjtAddr, usOfstAddr ) );
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::ProcAction(
    BST_DSPP_HEAD_STRU             *const pstRxHeadInfo,
    BST_DSPP_OFSTADDR_T             usOfstAddr,
    BST_DSPP_OBJTADDR_T             usObjtAddr )
{
    BST_ERR_ENUM_UINT8              enRtnVal;
    BST_DSPP_CAppUlVa              *pcUlProc;

    enRtnVal                        = BST_ERR_UNKNOW_ACT;
    switch ( pstRxHeadInfo->stCpVerA.ucActType )
    {
        /*
         * �������
         */
        case BST_ACTION_ADD:
            enRtnVal                = m_pcTaskManager->Create( usObjtAddr, usOfstAddr );
                /*
                 * �������ɺ���������ݣ���ô�ȼ���ò�����Ҫ����
                 */
            if( ( BST_NO_ERROR_MSG == enRtnVal )
             && ( 0 != pstRxHeadInfo->usLength )
             && ( BST_NULL_PTR != pstRxHeadInfo->pucData ) )
            {
                enRtnVal            = Config( usObjtAddr, usOfstAddr, pstRxHeadInfo );
            }
            /*���������ʧ��ʱ��ֱ��ɾ�������񣬷�ֹ����������ò��������쳣*/
            if ( enRtnVal != BST_NO_ERROR_MSG )
            {
                BST_DBG_LOG2( "procId,taskId add fail,remove", usObjtAddr, usOfstAddr );
                Remove( usObjtAddr, usOfstAddr );
            }
            break;
        /*
         * ɾ������
         */
        case BST_ACTION_REMOVE:
            enRtnVal                = Remove ( usObjtAddr, usOfstAddr ) ;
            break;
        /*
         * ��ʼ��������в�����Ҫ�����ã�����������������
         */
        case BST_ACTION_START:
            if( ( 0 != pstRxHeadInfo->usLength )
             && ( BST_NULL_PTR != pstRxHeadInfo->pucData ) )
            {
                /*
                 * �������ʧ�ܣ���Start������������ϵͳ�쳣����˲�������
                 */
                enRtnVal            = Config( usObjtAddr, usOfstAddr, pstRxHeadInfo );
                if ( BST_NO_ERROR_MSG == enRtnVal )
                {
                    enRtnVal        = m_pcTaskManager->Start ( usObjtAddr, usOfstAddr );
                }
            }
            else
            {
                enRtnVal            = m_pcTaskManager->Start ( usObjtAddr, usOfstAddr );
            }
            break;
        /*
         * ֹͣ��������
         */
        case BST_ACTION_STOP:
            enRtnVal                = m_pcTaskManager->Stop ( usObjtAddr, usOfstAddr );
            break;

        /*
         * ��ѯ����
         */
        case BST_ACTION_INQUIRE:
            if ( BST_NULL_PTR != pstRxHeadInfo->pucData )
            {
                enRtnVal                = Inquire ( usObjtAddr, usOfstAddr, pstRxHeadInfo );
                if(BST_NO_ERROR_MSG != enRtnVal)
                {
                    BST_DBG_LOG1 ( "BST_DSPP_CAppDlVa::inquire error:%d",enRtnVal);
                    pstRxHeadInfo->pucData  = BST_NULL_PTR;
                    pstRxHeadInfo->usLength = 0;
                }
            }
            else
            {
                enRtnVal                = BST_ERR_LAYER_VER;
                pstRxHeadInfo->pucData  = BST_NULL_PTR;
                pstRxHeadInfo->usLength = 0;
            }
            break;
        /*
         * ���ò���
         */
        case BST_ACTION_CONFIG:
            if ( BST_NULL_PTR != pstRxHeadInfo->pucData )
            {
                enRtnVal            = Config ( usObjtAddr, usOfstAddr, pstRxHeadInfo ) ;
            }
            else
            {
                enRtnVal            = BST_ERR_LAYER_VER;
            }
            break;

        default:
            enRtnVal                = BST_ERR_PAR_UNKNOW;
            BST_DBG_LOG ( "BST_DSPP_CAppDlVa::ProcAction Error, Unknow Action" );
            break;
    }

    if ( BST_ACTION_INQUIRE != pstRxHeadInfo->stCpVerA.ucActType )
    {
        pstRxHeadInfo->pucData      = BST_NULL_PTR;
        pstRxHeadInfo->usLength     = 0;
    }
    BST_OS_FREE( pstRxHeadInfo->pucSource );
    /*
     * Ӧ��S��ACTION���
     */
    pcUlProc                        = BST_DSPP_CAppUlVa::GetInstance ();
    enRtnVal                        = pcUlProc->Response( pstRxHeadInfo, enRtnVal );
    return enRtnVal;
}

/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::UnpackInternal(
    BST_DSPP_HEAD_STRU         *const pstRxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const pstNextVer )
{
    BST_DSPP_CAppUlVa          *pcUlProc;
    BST_OS_MBX_T               *pstRcver;
    BST_ERR_ENUM_UINT8          enRtnVal;

    pcUlProc                    = BST_DSPP_CAppUlVa::GetInstance ();
    enRtnVal                    = BST_NO_ERROR_MSG;

    /*
     * ��ڼ��
     */
    BST_ASSERT_NULL_RTN ( pstRxHeadInfo, BST_ERR_INVALID_PTR);
    BST_ASSERT_NULL_RTN ( pcUlProc, BST_ERR_INVALID_PTR);
    if ( BST_NULL_PTR == m_pcTaskManager )
    {
        BST_OS_FREE( pstRxHeadInfo->pucSource );
        return ( pcUlProc->Response ( pstRxHeadInfo, BST_ERR_INVALID_PTR ) );
    }
    if ( BST_DSPP_VER_A != pstRxHeadInfo->enCpVer )
    {
        BST_OS_FREE( pstRxHeadInfo->pucSource );
        return ( pcUlProc->Response ( pstRxHeadInfo, BST_ERR_LAYER_VER ) );
    }
    /*
     * ����������������ô������Ҫ�����߳���Դ��������APP�߳���ɹ���
     */
    if ( BST_ACTION_ADD == pstRxHeadInfo->stCpVerA.ucActType )
    {
        /*
         * Ϊ����������߳���Դ
         */
        enRtnVal                    = Assign ( pstRxHeadInfo, &pstRcver );
    }
    else
    {
        pstRcver                    = BST_SRV_GetTaskMsgHandle(
                                      pstRxHeadInfo->stCpVerA.usObjtAddr,
                                      pstRxHeadInfo->stCpVerA.usOfstAddr );
    }
    /*
     * ������س������û�����������ڣ���ô��Ϊʧ�ܣ�����Ӧ���̲߳��룬ֱ�ӻظ�S
     */
    if( ( BST_NO_ERROR_MSG != enRtnVal )
      ||( BST_NULL_PTR == pstRcver ) )
    {

        BST_OS_FREE( pstRxHeadInfo->pucSource );
        pstRxHeadInfo->usLength     = 0;
        pstRxHeadInfo->pucData      = BST_NULL_PTR;
        /*
         * Ӧ��S��ACTION���ʧ��
         */
        enRtnVal                    = pcUlProc->Response( pstRxHeadInfo, enRtnVal );
    }
    else
    {
        BST_SRV_ApiSendDsppEvent(
            pstRxHeadInfo->stCpVerA.ucActType,
            BST_DSPP_VER_A,
            BST_OS_SIZEOF(BST_DSPP_HEAD_STRU),
            pstRxHeadInfo,
            pstRcver );
    }
    return enRtnVal;
}
/*lint +e438*/

BST_DSPP_CDlLayerBase *BST_DSPP_CAppDlVa::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    return BST_NULL_PTR;
}


BST_DSPP_CAppDlVa *BST_DSPP_CAppDlVa::GetInstance( BST_VOID )
{
    static BST_DSPP_CAppDlVa   *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance             = new BST_DSPP_CAppDlVa ();
    }
    return s_pInstance;
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVa::Response(
    BST_DSPP_HEAD_STRU   *const pstOrigHeadInfo,
    BST_ERR_ENUM_UINT8    enErrMsg )
{
    BST_UINT8          *pucSdu;
    pucSdu             = BST_NULL_PTR;

    /*
     * ��ڼ��
     */
    if ( BST_NULL_PTR == pstOrigHeadInfo )
    {
        return BST_ERR_UNREACHABLE;
    }

    /*
     * У��Э��汾�����Ƿ�Ϸ�
     */
    if ( !BST_DSPP_IsVersionValid ( pstOrigHeadInfo->enCpVer ) )
    {
        return BST_ERR_UNREACHABLE;
    }

    /*
     * ��дDSPP�ṹ�����ݣ�����ΪRESPONSE
     */
    pstOrigHeadInfo->enTpVer        = BST_DSPP_VER_VOID;
    pstOrigHeadInfo->enPrmvType     = BST_DSPP_PRMTV_RESPONSE;

    /*
     * ���ԴӦ�𻺳��������ݣ���ô����ռ�Ҳ����
     */
    if ( ( BST_NULL_PTR != pstOrigHeadInfo->pucData )
      && ( 0 != pstOrigHeadInfo->usLength ) )
    {
        pstOrigHeadInfo->enApVer= BST_DSPP_VER_A;
        pucSdu                  = ( BST_UINT8 * )BST_OS_MALLOC
                                  ( pstOrigHeadInfo->usLength+BST_DSPP_CPA_HEAD_LENGTH );
        if ( BST_NULL_PTR == pucSdu )
        {
            BST_OS_FREE( pstOrigHeadInfo->pucData );
            return BST_ERR_NO_MEMORY;
        }
        BST_OS_MEMCPY( &pucSdu[BST_DSPP_APA_OFFSET_ADDR],
                        pstOrigHeadInfo->pucData,
                        pstOrigHeadInfo->usLength );
        BST_OS_FREE( pstOrigHeadInfo->pucData );
        pstOrigHeadInfo->pucData    = pucSdu;
    }
    /*
     * ���Ӧ��Ϊ�հף�ֱ������DSPPͷ���ȼ���
     */
    else
    {
        pstOrigHeadInfo->enApVer    = BST_DSPP_VER_VOID;
        pstOrigHeadInfo->usLength   = 0;
        pstOrigHeadInfo->pucData    = ( BST_UINT8 * )
                                      BST_OS_MALLOC ( BST_DSPP_CPA_HEAD_LENGTH );
        if ( BST_NULL_PTR == pstOrigHeadInfo->pucData )
        {
            return BST_ERR_NO_MEMORY;
        }
    }

    switch ( pstOrigHeadInfo->enCpVer )
    {
        case BST_DSPP_VER_A:
            pstOrigHeadInfo->stCpVerA.ucActType
                                    = enErrMsg;
            break;

        case BST_DSPP_VER_B:
            pstOrigHeadInfo->stCpVerA.ucActType
                                    = enErrMsg;
            break;

        default:
            break;
    }
    /*
     * ������һ����з��
     */
    return ( Pack ( pstOrigHeadInfo ) );
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVa::Report(
    BST_DSPP_OBJTADDR_T      usObjtAddr,
    BST_DSPP_OFSTADDR_T      usOfstAddr,
    BST_DSPP_CMDLEN_T        usCmdLen,
    BST_CORE_PID_ENUM_UINT16 enCmdId,
    BST_UINT8               *pucCmdData )
{
    BST_DSPP_HEAD_STRU                  stTxHeadInfo;
    BST_UINT8                          *pucSdu;

    pucSdu                             = BST_NULL_PTR;
    /*
     * ��ڼ��
     */
    if ( ( 0 == usCmdLen )
      || ( BST_NULL_PTR == pucCmdData ) )
    {
        return BST_ERR_INVALID_PTR;
    }
    /*
     * У�����͡���ֵַ�Ƿ���Ч
     */
    if ( (!BST_DSPP_IsObjIdValid ( usObjtAddr ) )
      || ( BST_DSPP_INVALID_ADDR == usOfstAddr ) )
    {
        return BST_ERR_UNREACHABLE;
    }

    /*
     * ��ȡ�ϱ�����
     */
    pucSdu                              = ( BST_UINT8 * )BST_OS_MALLOC ( usCmdLen
                                        + BST_DSPP_AP_CMD_HEAD_LEN + BST_DSPP_CPA_HEAD_LENGTH );
    if ( BST_NULL_PTR == pucSdu )
    {
        return BST_ERR_NO_MEMORY;
    }
    /*
     * ��дSDU-AP����Ϣ
     */
    stTxHeadInfo.pucData                = pucSdu;
    pucSdu                             += BST_DSPP_APA_OFFSET_ADDR;
    pucSdu[BST_DSPP_AP_CMD_LEN_L]       = BST_DSPP_U16_TO_U8L
                                        ( usCmdLen + BST_DSPP_AP_CMD_HEAD_LEN );
    pucSdu[BST_DSPP_AP_CMD_LEN_H]       = BST_DSPP_U16_TO_U8H
                                        ( usCmdLen + BST_DSPP_AP_CMD_HEAD_LEN );
    pucSdu[BST_DSPP_AP_CMD_ID_L]        = BST_DSPP_U16_TO_U8L ( enCmdId );
    pucSdu[BST_DSPP_AP_CMD_ID_H]        = BST_DSPP_U16_TO_U8H ( enCmdId );
    BST_OS_MEMCPY ( pucSdu + BST_DSPP_AP_CMD_HEAD_LEN, pucCmdData, usCmdLen );

    /*
     * ��дDSPP�ṹ�壬ѡ��Э��汾�����²�ʹ��
     */
    stTxHeadInfo.enCpVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enApVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enTpVer                = BST_DSPP_VER_VOID;
    stTxHeadInfo.enPrmvType             = BST_DSPP_PRMTV_REPORT;
    stTxHeadInfo.usPktNum               = BST_DSPP_TP_INVALID_PKTNUM;
    stTxHeadInfo.usLength               = ( usCmdLen + BST_DSPP_AP_CMD_HEAD_LEN );
    stTxHeadInfo.stCpVerA.usObjtAddr    = usObjtAddr;
    stTxHeadInfo.stCpVerA.usOfstAddr    = usOfstAddr;
    stTxHeadInfo.stCpVerA.ucActType     = BST_ACTION_REPORT;

    return ( Pack ( &stTxHeadInfo ) );
}

BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVa::Report(
    BST_DSPP_OBJTADDR_T usObjtAddr,
    BST_DSPP_OFSTADDR_T usOfstAddr,
    BST_ERR_ENUM_UINT8  enErr )
{
    BST_DSPP_HEAD_STRU                  stTxHeadInfo;

    /*
     * ��ڼ��
     */
    if ( (!BST_DSPP_IsObjIdValid ( usObjtAddr ) )
      || ( BST_DSPP_INVALID_ADDR == usOfstAddr ) )
    {
        return BST_ERR_UNREACHABLE;
    }
    stTxHeadInfo.pucData                = ( BST_UINT8 * )
                                          BST_OS_MALLOC ( BST_DSPP_CPA_HEAD_LENGTH );
    if ( BST_NULL_PTR == stTxHeadInfo.pucData )
    {
        return BST_ERR_NO_MEMORY;
    }
    /*
     * ��дDSPP�ṹ�壬ѡ��Э��汾�����²�ʹ��
     */
    stTxHeadInfo.pucSource              = stTxHeadInfo.pucData;
    stTxHeadInfo.enCpVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enApVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enTpVer                = BST_DSPP_VER_VOID;
    stTxHeadInfo.enPrmvType             = BST_DSPP_PRMTV_REPORT;
    stTxHeadInfo.usPktNum               = BST_DSPP_TP_INVALID_PKTNUM;
    stTxHeadInfo.usLength               = 0;
    stTxHeadInfo.stCpVerA.usObjtAddr    = usObjtAddr;
    stTxHeadInfo.stCpVerA.usOfstAddr    = usOfstAddr;
    stTxHeadInfo.stCpVerA.ucActType     = enErr;
    return ( Pack ( &stTxHeadInfo ) );
}


BST_DSPP_CAppUlVa *BST_DSPP_CAppUlVa::GetInstance ( BST_VOID )
{
    static BST_DSPP_CAppUlVa           *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance                     = new BST_DSPP_CAppUlVa ();
    }

    return s_pInstance;
}


BST_DSPP_CAppUlVa::BST_DSPP_CAppUlVa ( BST_VOID )
    : BST_DSPP_CUlLayerBase ( BST_DSPP_LAYER_APP, BST_DSPP_VER_A )
{

}

BST_DSPP_CAppUlVa::~BST_DSPP_CAppUlVa ( BST_VOID )
{

}

BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVa::PackInternal(
    BST_DSPP_HEAD_STRU         *const pstTxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const penNextVer )
{
    if ( BST_NULL_PTR == pstTxHeadInfo )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    if ( BST_NULL_PTR != penNextVer )
    {
        *penNextVer                          = pstTxHeadInfo->enCpVer;
    }
    return BST_NO_ERROR_MSG;
}


BST_DSPP_CUlLayerBase *BST_DSPP_CAppUlVa::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    switch ( enNextVer )
    {
        case BST_DSPP_VER_A:
            return ( BST_DSPP_CCtrUlVa::GetInstance() );

        case BST_DSPP_VER_C:
            return ( BST_DSPP_CCtrUlVc::GetInstance() );
        default:
            break;
    }
    return BST_NULL_PTR;
}

BST_VOID BST_PbufStatusCallBack( BST_UINT16 usStatus )
{
    BST_DSPP_CAppUlVc::GetInstance()->ReportBuffer( usStatus );
}


BST_DSPP_CAppDlVc::BST_DSPP_CAppDlVc( BST_VOID )
    : BST_DSPP_CDlLayerBase( BST_DSPP_LAYER_APP, BST_DSPP_VER_C )
{
}


BST_DSPP_CAppDlVc::~BST_DSPP_CAppDlVc( BST_VOID )
{
}


/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVc::UnpackInternal(
    BST_DSPP_HEAD_STRU         *const pstRxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const pstNextVer )
{
    BST_ERR_ENUM_UINT8          enRtnVal;
    BST_SRV_CHNL_HEAD_STRU     *pstPktHead;
    BST_OS_MBX_T               *pstRcver;
    /*
     * ��ڼ��
     */
    pstPktHead                  = BST_NULL_PTR;
    pstRcver                    = BST_NULL_PTR;
    if( BST_NULL_PTR == pstRxHeadInfo )
    {
        enRtnVal                = BST_ERR_INVALID_PTR;
        goto err_out;
    }
    if( BST_NULL_PTR == pstNextVer )
    {
        enRtnVal                = BST_ERR_INVALID_PTR;
        goto err_out;
    }
    enRtnVal                    = BST_NO_ERROR_MSG;

    pstPktHead              = BST_SRV_AlocIpBlock();

    if( BST_NULL_PTR == pstPktHead )
    {
        enRtnVal                = BST_ERR_NO_MEMORY;
        goto err_out;
    }
    pstPktHead->pNext           = BST_NULL_PTR;

    pstRcver                    = ParseHeadInfo( pstRxHeadInfo, pstPktHead );
    if( BST_NULL_PTR == pstRcver )
    {
        enRtnVal                = BST_ERR_LAYER_VER;
        goto err_out;
    }

    pstRxHeadInfo->usLength     = 0;
    pstRxHeadInfo->pucData      = BST_NULL_PTR;
    BST_OS_FREE( pstRxHeadInfo->pucSource );

    BST_SRV_ApiSendDsppEvent(
        pstRxHeadInfo->enPrmvType,
        BST_DSPP_VER_C,
        BST_OS_SIZEOF(BST_SRV_CHNL_HEAD_STRU),
        pstPktHead,
        pstRcver );
    return BST_NO_ERROR_MSG;

err_out:
    if( BST_NULL_PTR != pstPktHead )
    {
        BST_SRV_FreeIpBlock(pstPktHead);
    }
    if( BST_NULL_PTR != pstRxHeadInfo )
    {
        BST_OS_FREE( pstRxHeadInfo->pucSource );
    }
    return enRtnVal;
}
/*lint +e438*/

BST_OS_MBX_T  *BST_DSPP_CAppDlVc::ParseHeadInfo(
    BST_DSPP_HEAD_STRU     *const pstDsppHead,
    BST_SRV_CHNL_HEAD_STRU *pstChnHead )
{
    BST_UINT16                  usLength;
    BST_UINT8                  *pucData;
    BST_OS_MBX_T               *pstRcver;

    /*
     * ��ڼ��
     */
    BST_ASSERT_NULL_RTN( pstDsppHead, BST_NULL_PTR );
    BST_ASSERT_NULL_RTN( pstChnHead, BST_NULL_PTR );
    pucData                     = pstDsppHead->pucData;
    usLength                    = pstDsppHead->usLength;
   /*
    * ��ȡIP Address
    */
    if ( BST_DSPP_FLG_ADDTYPE_INET == pstDsppHead->stCpVerC.ucAddrType )
    {
        if( usLength < BST_OS_SIZEOF( BST_IP_SOCKET_ADD_T ) )
        {
            return BST_NULL_PTR;
        }
        BST_OS_MEMCPY( &pstChnHead->stAddr.stInet, pucData, BST_OS_SIZEOF( BST_IP_SOCKET_ADD_T ) );
        pucData                += BST_OS_SIZEOF( BST_IP_SOCKET_ADD_T );
        usLength               -= BST_OS_SIZEOF( BST_IP_SOCKET_ADD_T );
        pstChnHead->ucAddrType  = BST_DSPP_FLG_ADDTYPE_INET;
        pstRcver                = BST_SRV_GetChnlCtrlHandle( 0 );
    }
    else if( BST_DSPP_FLG_ADDTYPE_TASK == pstDsppHead->stCpVerC.ucAddrType )
    {
        if( usLength < BST_OS_SIZEOF( pstChnHead->stAddr.stTask ) )
        {
            return BST_NULL_PTR;
        }

        pstChnHead->stAddr.stTask.usProcId
                                = BST_DSPP_U8_TO_U16( pucData[BST_DSPP_CP_OBJT_ADD_L],
                                                      pucData[BST_DSPP_CP_OBJT_ADD_H] );
        pstChnHead->stAddr.stTask.usTaskId
                                = BST_DSPP_U8_TO_U16( pucData[BST_DSPP_CP_OFST_ADD_L],
                                                      pucData[BST_DSPP_CP_OFST_ADD_H] );
        pucData                += BST_OS_SIZEOF( pstChnHead->stAddr.stTask );
        usLength               -= BST_OS_SIZEOF( pstChnHead->stAddr.stTask );
        pstChnHead->ucAddrType  = BST_DSPP_FLG_ADDTYPE_TASK;
        pstRcver                = BST_SRV_GetTaskMsgHandle(
                                    pstChnHead->stAddr.stTask.usProcId,
                                    pstChnHead->stAddr.stTask.usTaskId );

    }
    else
    {
        pstChnHead->ucAddrType  = BST_DSPP_FLG_ADDTYPE_VOID;
        pstRcver                = BST_SRV_GetChnlCtrlHandle( 0 );
    }

    BST_ASSERT_NULL_RTN( pstRcver, BST_NULL_PTR );
   /*
    * ��ȡSocket property
    */

    BST_OS_MEMSET( &pstChnHead->stProp, 0, BST_OS_SIZEOF(BST_IP_SKT_PROPTY_STRU) );
    switch( pstDsppHead->stCpVerC.ucPropType )
    {
        case BST_IP_SKT_PROP_NONE:        /*0 û��property*/
        break;

        case BST_IP_SKT_PROP_SEQNO:       /*1 ֻ��seqno*/
            if( usLength < BST_OS_SIZEOF( BST_UINT32 ) )
            {
                return BST_NULL_PTR;
            }
            BST_OS_MEMCPY( &pstChnHead->stProp.ulSeqNum, pucData, BST_OS_SIZEOF(BST_UINT32) );
            pucData            += BST_OS_SIZEOF( BST_UINT32 );
            usLength           -= BST_OS_SIZEOF( BST_UINT32 );
        break;

        case BST_IP_SKT_PROP_SEQNO_TS:    /* 2 ֻ��seqno+timestamp */
            if( usLength < BST_OS_SIZEOF( BST_UINT32 )*2 )
            {
                return BST_NULL_PTR;
            }
            BST_OS_MEMCPY( &pstChnHead->stProp.ulSeqNum, pucData, BST_OS_SIZEOF(BST_UINT32) );
            pucData            += BST_OS_SIZEOF( BST_UINT32 );
            usLength           -= BST_OS_SIZEOF( BST_UINT32 );
            BST_OS_MEMCPY( &pstChnHead->stProp.ulTsCurrent, pucData, BST_OS_SIZEOF(BST_UINT32) );
            pucData            += BST_OS_SIZEOF( BST_UINT32 );
            usLength           -= BST_OS_SIZEOF( BST_UINT32 );
        break;

        case BST_IP_SKT_PROP_TOTAL:       /*3 ����property*/
            if( usLength < BST_OS_SIZEOF( BST_IP_SKT_PROPTY_STRU ) )
            {
                return BST_NULL_PTR;
            }
            BST_OS_MEMCPY( &pstChnHead->stProp, pucData, BST_OS_SIZEOF(BST_IP_SKT_PROPTY_STRU) );
            pucData            += BST_OS_SIZEOF( BST_IP_SKT_PROPTY_STRU );
            usLength           -= BST_OS_SIZEOF( BST_IP_SKT_PROPTY_STRU );
        break;

        default:                            /*4 ��Ч*/
             return BST_NULL_PTR;
        break;
    }
    pstChnHead->ucPropType      = pstDsppHead->stCpVerC.ucPropType;

   /*
    *ʶ��Sendʱ��Bufferʹ�����
    */
    if( BST_DSPP_FLG_CMD_SEND == pstDsppHead->stCpVerC.usCmdId )
    {
        if( ( usLength == 0 ) || ( usLength > BST_SRV_BLOCK_SIZE ) )
        {
            return BST_NULL_PTR;
        }
        pstChnHead->ulUsed      = usLength;
        BST_OS_MEMCPY( &pstChnHead->aucData[0], pucData, usLength );
    }
    else
    {
        pstChnHead->ulUsed      = 0;
    }
    pstChnHead->ulMainLinkId    = pstDsppHead->stCpVerC.ulMainLinkId;
    pstChnHead->ulAuxLinkId     = pstDsppHead->stCpVerC.ulAuxLinkId;
    pstChnHead->usCmdId         = pstDsppHead->stCpVerC.usCmdId;
    pstChnHead->usProcLevel     = pstDsppHead->stCpVerC.usProcLevel;
    pstChnHead->ucIpProtocol    = pstDsppHead->stCpVerC.ucIpProtocol;
    pstChnHead->ucPktAddr       = pstDsppHead->stCpVerC.ucPktAddr;
    return pstRcver;
}


BST_DSPP_CDlLayerBase *BST_DSPP_CAppDlVc::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    return BST_NULL_PTR;
}


BST_DSPP_CAppDlVc *BST_DSPP_CAppDlVc::GetInstance( BST_VOID )
{
    static BST_DSPP_CAppDlVc   *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance             = new BST_DSPP_CAppDlVc ();
    }
    return s_pInstance;
}


BST_ERR_ENUM_UINT8 BST_DSPP_CAppDlVc::ProcAction(
    BST_SRV_CHNL_HEAD_STRU     *pstChnHead )
{
    BST_CORE_CRegedit          *m_pcRegedit;
    BST_ERR_ENUM_UINT8          enRtnVal = BST_NO_ERROR_MSG;

    BST_ASSERT_NULL_RTN( pstChnHead, BST_ERR_INVALID_PTR );

    BST_DBG_LOG1( "CPC_PACKET_DROP usAddrType", pstChnHead->ucAddrType );
    if ( BST_DSPP_FLG_ADDTYPE_INET == pstChnHead->ucAddrType )
    {
        enRtnVal                        = BST_SRV_CHNL_Itf( pstChnHead );
    }
    else if( BST_DSPP_FLG_ADDTYPE_TASK == pstChnHead->ucAddrType )
    {
        m_pcRegedit                     = BST_CORE_CRegedit::GetInstance();

        BST_ASSERT_NULL_RTN( pstChnHead, BST_ERR_INVALID_PTR );
        enRtnVal                        = m_pcRegedit->ChnlCtrl(
                                          pstChnHead->stAddr.stTask.usProcId,
                                          pstChnHead->stAddr.stTask.usTaskId,
                                          pstChnHead );
    }
    else
    {
        BST_SRV_FreeIpBlock( pstChnHead );
        enRtnVal                        = BST_ERR_UNKNOW_OBJ;
    }

    return enRtnVal;
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVc::Report(
    BST_DSPP_FLG_CMD_ENUM_UINT8 enCmdId,
    BST_DSPP_LINKID1_T          ulLinkId0,
    BST_DSPP_LINKID1_T          ulLinkId1,
    BST_DSPP_OBJTADDR_T         usObjtAddr,
    BST_DSPP_OFSTADDR_T         usOfstAddr )
{
    BST_DSPP_HEAD_STRU                  stTxHeadInfo;
    BST_UINT8                          *pucSdu;
    BST_UINT32                          ulSduLen;
    BST_BOOL                            bUseTaskId;

    pucSdu                              = BST_NULL_PTR;
    bUseTaskId                          = BST_TRUE;
    ulSduLen                            = 0;

    /*
     * У�����͡���ֵַ�Ƿ���Ч
     */
    if ( (!BST_DSPP_IsObjIdValid ( usObjtAddr ) )
      || ( BST_DSPP_INVALID_ADDR == usOfstAddr ) )
    {
        if ( ( BST_DSPP_INVALID_LINK_ID == ulLinkId0 )
          || ( BST_DSPP_INVALID_LINK_ID == ulLinkId1 ) )
        {
            return BST_ERR_UNREACHABLE;
        }
        bUseTaskId                      = BST_FALSE;
        ulSduLen                        = BST_DSPP_CPC_HEAD_LENGTH;
    }
    else
    {
        bUseTaskId                      = BST_TRUE;
        ulSduLen                        = BST_DSPP_CPC_HEAD_LENGTH
                                        + BST_DSPP_APC_ADDRESS_LEN;
    }

    /*
     * ��ȡ�ϱ�����
     */
    pucSdu                              = ( BST_UINT8 * )BST_OS_MALLOC( ulSduLen );
    if ( BST_NULL_PTR == pucSdu )
    {
        return BST_ERR_NO_MEMORY;
    }
    /*
     * ��дSDU-AP����Ϣ
     */
    stTxHeadInfo.pucData                = pucSdu;
    stTxHeadInfo.pucSource              = pucSdu;

    if( BST_TRUE == bUseTaskId )
    {
        pucSdu                             += BST_DSPP_APC_OFFSET_ADDR;
        pucSdu[BST_DSPP_APC_PROCID_ADD_L]   = BST_DSPP_U16_TO_U8L
                                            ( usObjtAddr );
        pucSdu[BST_DSPP_APC_PROCID_ADD_H]   = BST_DSPP_U16_TO_U8H
                                            ( usObjtAddr );
        pucSdu[BST_DSPP_APC_TASKID_ADD_L]   = BST_DSPP_U16_TO_U8L
                                            ( usObjtAddr );
        pucSdu[BST_DSPP_APC_TASKID_ADD_H]   = BST_DSPP_U16_TO_U8H
                                            ( usObjtAddr );
        stTxHeadInfo.usLength               = BST_DSPP_APC_ADDRESS_LEN;
        stTxHeadInfo.stCpVerC.ulMainLinkId  = BST_DSPP_COMMON_LINK_ID;
        stTxHeadInfo.stCpVerC.ulAuxLinkId   = BST_DSPP_COMMON_LINK_ID;
        stTxHeadInfo.stCpVerC.ucAddrType    = BST_DSPP_FLG_ADDTYPE_TASK;
    }
    else
    {
        stTxHeadInfo.usLength               = 0;
        stTxHeadInfo.stCpVerC.ulMainLinkId  = ulLinkId0;
        stTxHeadInfo.stCpVerC.ulAuxLinkId   = ulLinkId1;
        stTxHeadInfo.stCpVerC.ucAddrType    = BST_DSPP_FLG_ADDTYPE_VOID;
    }
    /*
     * ��дDSPP�ṹ�壬ѡ��Э��汾�����²�ʹ��
     */
    stTxHeadInfo.enCpVer                = BST_DSPP_VER_C;
    stTxHeadInfo.enApVer                = BST_DSPP_VER_C;
    stTxHeadInfo.enTpVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enPrmvType             = BST_DSPP_PRMTV_REPORT;
    stTxHeadInfo.usPktNum               = BST_DSPP_TP_INVALID_PKTNUM;
    stTxHeadInfo.stCpVerC.usCmdId       = enCmdId;
    stTxHeadInfo.stCpVerC.ucIpProtocol  = BST_DSPP_FLG_PROTYPE_TCP;
    stTxHeadInfo.stCpVerC.usProcLevel   = BST_DSPP_FLG_LVLTYPE_NORMAL;
    stTxHeadInfo.stCpVerC.ucPropType    = BST_IP_SKT_PROP_NONE;
    stTxHeadInfo.stCpVerC.ucPktAddr     = BST_DSPP_FLG_PKTADDR_SINGLE;
    return ( Pack ( &stTxHeadInfo ) );
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVc::Report(
    BST_DSPP_FLG_CMD_ENUM_UINT8 enCmdId,
    BST_DSPP_OBJTADDR_T         usObjtAddr,
    BST_DSPP_OFSTADDR_T         usOfstAddr )
{
    return Report( enCmdId,
                   BST_DSPP_INVALID_LINK_ID, BST_DSPP_INVALID_LINK_ID,
                   usObjtAddr, usOfstAddr );

}

BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVc::Report(
    BST_DSPP_FLG_CMD_ENUM_UINT8 enCmdId,
    BST_DSPP_LINKID1_T          ulLinkId0,
    BST_DSPP_LINKID1_T          ulLinkId1 )
{
    return Report( enCmdId, ulLinkId0, ulLinkId1,
                   BST_DSPP_INVALID_ADDR,
                   BST_DSPP_INVALID_ADDR );
}

BST_VOID BST_DSPP_CAppUlVc::ReportBuffer( BST_UINT16 ulBufferStatus )
{
    BST_DSPP_HEAD_STRU                  stTxHeadInfo;
    BST_UINT8                          *pucSdu;

    pucSdu                              = BST_NULL_PTR;

    /*
     * ��ȡ�ϱ�����
     */
    pucSdu                              = ( BST_UINT8 * )BST_OS_MALLOC(
                                          BST_DSPP_CPC_HEAD_LENGTH
                                        + BST_DSPP_CPC_BUFFER_NUM_LEN );
    if ( BST_NULL_PTR == pucSdu )
    {
        return;
    }

    /*
     * ��дSDU-AP����Ϣ
     */
    stTxHeadInfo.pucData                = pucSdu;
    stTxHeadInfo.pucSource              = pucSdu;

    pucSdu                             += BST_DSPP_APC_OFFSET_ADDR;
    pucSdu[BST_DSPP_CPC_BUFFER_NUM_0]   = BST_DSPP_U16_TO_U8L
                                        ( ulBufferStatus );
    pucSdu[BST_DSPP_CPC_BUFFER_NUM_1]   = BST_DSPP_U16_TO_U8H
                                        ( ulBufferStatus );
    stTxHeadInfo.usLength               = BST_DSPP_CPC_BUFFER_NUM_LEN;
    stTxHeadInfo.stCpVerC.ulMainLinkId  = BST_DSPP_COMMON_LINK_ID;
    stTxHeadInfo.stCpVerC.ulAuxLinkId   = BST_DSPP_COMMON_LINK_ID;
    stTxHeadInfo.stCpVerC.ucAddrType    = BST_DSPP_FLG_ADDTYPE_VOID;
    stTxHeadInfo.enCpVer                = BST_DSPP_VER_C;
    stTxHeadInfo.enApVer                = BST_DSPP_VER_C;
    stTxHeadInfo.enTpVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enPrmvType             = BST_DSPP_PRMTV_REPORT;
    stTxHeadInfo.usPktNum               = BST_DSPP_TP_INVALID_PKTNUM;
    stTxHeadInfo.stCpVerC.usCmdId       = BST_DSPP_FLG_CMD_BUFFER;
    stTxHeadInfo.stCpVerC.ucIpProtocol  = BST_DSPP_FLG_PROTYPE_TCP;
    stTxHeadInfo.stCpVerC.usProcLevel   = BST_DSPP_FLG_LVLTYPE_NORMAL;
    stTxHeadInfo.stCpVerC.ucPropType    = BST_IP_SKT_PROP_NONE;
    stTxHeadInfo.stCpVerC.ucPktAddr     = BST_DSPP_FLG_PKTADDR_SINGLE;
    Pack( &stTxHeadInfo );
}

BST_VOID BST_DSPP_CAppUlVc::ReportFlow(
    BST_IP_TRAFFIC_FLOW_STRU   *pstFlowInfo,
    BST_DSPP_LINKID1_T          ulLinkId0,
    BST_DSPP_LINKID1_T          ulLinkId1 )
{
    BST_DSPP_HEAD_STRU                  stTxHeadInfo;
    BST_UINT8                          *pucSdu;

    pucSdu                              = BST_NULL_PTR;

    /*
     * ��ȡ�ϱ�����
     */
    pucSdu                              = ( BST_UINT8 * )BST_OS_MALLOC(
                                          BST_DSPP_CPC_HEAD_LENGTH
                                        + BST_DSPP_CPC_FLOW_NUM_LEN );
    if ( BST_NULL_PTR == pucSdu )
    {
        return;
    }

    /*
     * ��дSDU-AP����Ϣ
     */
    stTxHeadInfo.pucData                = pucSdu;
    stTxHeadInfo.pucSource              = pucSdu;

    pucSdu                             += BST_DSPP_APC_OFFSET_ADDR;
    pucSdu[BST_DSPP_CPC_FLOW_NUM_0]   = BST_DSPP_U32_TO_U8_0
                                        ( pstFlowInfo->ulTxByte );
    pucSdu[BST_DSPP_CPC_FLOW_NUM_1]   = BST_DSPP_U32_TO_U8_1
                                        ( pstFlowInfo->ulTxByte );
    pucSdu[BST_DSPP_CPC_FLOW_NUM_2]   = BST_DSPP_U32_TO_U8_2
                                        ( pstFlowInfo->ulTxByte );
    pucSdu[BST_DSPP_CPC_FLOW_NUM_3]   = BST_DSPP_U32_TO_U8_3
                                        ( pstFlowInfo->ulTxByte );

    stTxHeadInfo.usLength               = BST_DSPP_CPC_FLOW_NUM_LEN;
    stTxHeadInfo.stCpVerC.ulMainLinkId  = ulLinkId0;
    stTxHeadInfo.stCpVerC.ulAuxLinkId   = ulLinkId1;
    stTxHeadInfo.stCpVerC.ucAddrType    = BST_DSPP_FLG_ADDTYPE_VOID;
    stTxHeadInfo.enCpVer                = BST_DSPP_VER_C;
    stTxHeadInfo.enApVer                = BST_DSPP_VER_C;
    stTxHeadInfo.enTpVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enPrmvType             = BST_DSPP_PRMTV_REPORT;
    stTxHeadInfo.usPktNum               = BST_DSPP_TP_INVALID_PKTNUM;
    stTxHeadInfo.stCpVerC.usCmdId       = BST_DSPP_FLG_CMD_TRAFFIC; /*����*/
    stTxHeadInfo.stCpVerC.ucIpProtocol  = BST_DSPP_FLG_PROTYPE_TCP;
    stTxHeadInfo.stCpVerC.usProcLevel   = BST_DSPP_FLG_LVLTYPE_NORMAL;
    stTxHeadInfo.stCpVerC.ucPropType    = BST_IP_SKT_PROP_NONE;
    stTxHeadInfo.stCpVerC.ucPktAddr     = BST_DSPP_FLG_PKTADDR_SINGLE;
    Pack( &stTxHeadInfo );
}
BST_DSPP_CAppUlVc *BST_DSPP_CAppUlVc::GetInstance ( BST_VOID )
{
    static BST_DSPP_CAppUlVc           *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance                     = new BST_DSPP_CAppUlVc ();
    }

    return s_pInstance;
}


BST_DSPP_CAppUlVc::BST_DSPP_CAppUlVc ( BST_VOID )
    : BST_DSPP_CUlLayerBase ( BST_DSPP_LAYER_APP, BST_DSPP_VER_A )
{
    /*ע��pbuf�����ڴ�״̬�ص�����*/
    BST_OS_RegisgerMemStatus(BST_MEM_TYPE_PBUF,BST_PbufStatusCallBack);
}
BST_DSPP_CAppUlVc::~BST_DSPP_CAppUlVc ( BST_VOID )
{

}

BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVc::PackInternal(
    BST_DSPP_HEAD_STRU         *const pstTxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const penNextVer )
{
    if ( BST_NULL_PTR == pstTxHeadInfo )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    if ( BST_NULL_PTR != penNextVer )
    {
       *penNextVer                          = pstTxHeadInfo->enCpVer;
    }
    return BST_NO_ERROR_MSG;
}


BST_DSPP_CUlLayerBase *BST_DSPP_CAppUlVc::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    switch ( enNextVer )
    {
        case BST_DSPP_VER_C:
            return BST_DSPP_CCtrUlVc::GetInstance();
        default:
            break;
    }
    return BST_NULL_PTR;
}
