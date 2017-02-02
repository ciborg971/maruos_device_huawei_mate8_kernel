
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_APP_ExcgHttp.h"
#include "BST_OS_Memory.h"
#include <stdlib.h>
#if( BST_VER_TYPE == BST_UT_VER )
#include <string>
#endif
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_APP_EMAILEXCGHTTP_CPP
/*lint +e767*/
/******************************************************************************
   2 �궨��
******************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

/******************************************************************************
   4 ˽�ж���
******************************************************************************/

/******************************************************************************
   5 ȫ�ֱ�������
******************************************************************************/

/******************************************************************************
   6 ����ʵ��
******************************************************************************/

BST_APP_CExcgHttp::BST_APP_CExcgHttp()
{
    m_pstrWbxml     = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    m_pstrRequest   = BST_LIB_StrCreat( BST_LIB_LONG_STR_LEN );
    m_pstrHttpBody  = BST_LIB_StrCreat( BST_LIB_LONG_STR_LEN );
    m_pstrReqIn     = BST_LIB_StrCreat( BST_LIB_LONG_STR_LEN );
    m_pstrReqOut    = BST_LIB_StrCreat( BST_LIB_LONG_STR_LEN );
    m_pstrReqCon    = BST_LIB_StrCreat( BST_LIB_LONG_STR_LEN );
    m_pstrReqCal    = BST_LIB_StrCreat( BST_LIB_LONG_STR_LEN );
    m_enCmdType     = INVALID_SYNC_CMD;
}

/*lint -e438*/
BST_BOOL BST_APP_CExcgHttp::ConfigRqst(
    const BST_CHAR                      *strUserName,
    const BST_CHAR                      *strUserNameAndPass,
    const BST_CHAR                      *strDeviceId,
    const BST_EMAIL_HTTP_REQ_HEAD_STRU  *pstHttpReqHead,
    const BST_EMAIL_WBXML_BODY_STRU     *pstWbxmlBody,
    const BST_APP_EXCGREQ_TYPE_ENUM_UINT8 enCmdType )
{
    BST_UINT16          usLen;
    BST_INT8           *pcBuf;

    if ( BST_NULL_PTR == pstHttpReqHead )
    {
        return BST_FALSE;
    }
    if ( BST_NULL_PTR == pstWbxmlBody )
    {
        return BST_FALSE;
    }
    pcBuf               = (BST_INT8 *)BST_OS_MALLOC(EXCG_WEB_XML_LEN);
    if ( BST_NULL_PTR == pcBuf )
    {
        return BST_FALSE;
    }
    /*Clear the content of old request message block*/
    BST_LIB_StrClear( m_pstrRequest);
    m_enCmdType         = enCmdType;
    CreateRqstLine( strUserName, strDeviceId, enCmdType );
    if ( PING_CMD == m_enCmdType )
    {
        usLen           = CreatePingBody( pstWbxmlBody );
        (BST_VOID)snprintf( (BST_CHAR *)pcBuf, EXCG_WEB_XML_LEN, "%d", usLen );
        CreateRqstHeader( strUserNameAndPass, (BST_CHAR *)pcBuf, pstHttpReqHead, enCmdType );
        BST_LIB_StrAddBytes( m_pstrRequest, m_pstrHttpBody->pData, m_pstrHttpBody->usUsed );
        BST_LIB_StrAddBytes( m_pstrRequest, m_pstrWbxml->pData, m_pstrWbxml->usUsed );
        BST_LIB_StrClear( m_pstrWbxml );
    }
    else
    {
        usLen           = CreateSyncBody( pstWbxmlBody, BST_APP_EXCH_IN_EMAIL );
        BST_CREAT_SYNC_REQUEST(m_pstrReqIn);
        
        usLen           = CreateSyncBody( pstWbxmlBody, BST_APP_EXCH_OUT_EMAIL );
        BST_CREAT_SYNC_REQUEST(m_pstrReqOut);
        
        usLen           = CreateSyncBody( pstWbxmlBody, BST_APP_EXCH_CONTACT );
        BST_CREAT_SYNC_REQUEST( m_pstrReqCon );
        
        usLen           = CreateSyncBody( pstWbxmlBody, BST_APP_EXCH_CALENDAR );
        BST_CREAT_SYNC_REQUEST( m_pstrReqCal );
    }
    BST_OS_FREE( pcBuf );
    return BST_TRUE;
}
/*lint +e438*/

BST_VOID BST_APP_CExcgHttp::CreateRqstLine(
    const BST_CHAR *strUserName,
    const BST_CHAR *strDeviceId,
    const BST_APP_EXCGREQ_TYPE_ENUM_UINT8 enCmdType )
{
    switch ( enCmdType )
    {
        case PING_CMD:
            BST_LIB_StrAddStr( m_pstrRequest,
                       "POST /Microsoft-Server-ActiveSync?Cmd=Ping&User=" );
            break;

        case SYNC_CMD:
            BST_LIB_StrAddStr( m_pstrRequest,
                       "POST /Microsoft-Server-ActiveSync?Cmd=Sync&User=" );
            break;
        default:
            BST_RLS_LOG("CreateRqstLine enCmdType is error!");
            break;
    }
    BST_LIB_StrAddStr( m_pstrRequest, strUserName );
    BST_LIB_StrAddStr( m_pstrRequest, "&DeviceId=" );
    BST_LIB_StrAddStr( m_pstrRequest, strDeviceId );
    BST_LIB_StrAddStr( m_pstrRequest, "&DeviceType=" );
    BST_LIB_StrAddStr( m_pstrRequest, BST_EMAIL_EAS_DEVICE_TYPE );
    BST_LIB_StrAddStr( m_pstrRequest, " " );
    BST_LIB_StrAddStr( m_pstrRequest, BST_EMAIL_HTTP_VERSION );
    BST_LIB_StrAddStr( m_pstrRequest, BST_EMAIL_HTTP_CRLF );
}

BST_VOID BST_APP_CExcgHttp::CreateRqstHeader(
    const BST_CHAR * strUserNameAndPass,
    const BST_CHAR * strBodyLen,
    const BST_EMAIL_HTTP_REQ_HEAD_STRU *pstHttpReqHead,
    BST_APP_EXCGREQ_TYPE_ENUM_UINT8 enCmdType )
{
    if ( BST_NULL_PTR == pstHttpReqHead)
    {
        return;
    }
    BST_LIB_StrAddStr( m_pstrHttpBody, "Authorization: Basic " );
    /*���˺ţ����롱 base64����*/
    BST_LIB_StrAddStr( m_pstrHttpBody, strUserNameAndPass  );
    BST_LIB_StrAddStr( m_pstrHttpBody, BST_EMAIL_HTTP_CRLF );
    BST_LIB_StrAddStr( m_pstrHttpBody, "MS-ASProtocolVersion: " );
    BST_LIB_StrAddStr( m_pstrHttpBody, pstHttpReqHead->pstPrtcVer->pData );
    BST_LIB_StrAddStr( m_pstrHttpBody, BST_EMAIL_HTTP_CRLF );
    BST_LIB_StrAddStr( m_pstrHttpBody, "User-Agent: " );
    BST_LIB_StrAddStr( m_pstrHttpBody, pstHttpReqHead->pstUsrAgent->pData );
    BST_LIB_StrAddStr( m_pstrHttpBody, BST_EMAIL_HTTP_CRLF );
    BST_LIB_StrAddStr( m_pstrHttpBody, "Accept-Encoding: " );
    BST_LIB_StrAddStr( m_pstrHttpBody, pstHttpReqHead->pstEncoding->pData );
    BST_LIB_StrAddStr( m_pstrHttpBody, BST_EMAIL_HTTP_CRLF );
    BST_LIB_StrAddStr( m_pstrHttpBody, "Content-Type: application/vnd.ms-sync.wbxml" );
    BST_LIB_StrAddStr( m_pstrHttpBody, BST_EMAIL_HTTP_CRLF );
    if ( SYNC_CMD == enCmdType )
    {
        BST_LIB_StrAddStr( m_pstrHttpBody, "X-MS-PolicyKey: " );
        BST_LIB_StrAddStr( m_pstrHttpBody, pstHttpReqHead->pstPolicyKey->pData );
        BST_LIB_StrAddStr( m_pstrHttpBody, BST_EMAIL_HTTP_CRLF );
    }
    BST_LIB_StrAddStr( m_pstrHttpBody, "Content-Length: " );
    BST_LIB_StrAddStr( m_pstrHttpBody, strBodyLen );
    BST_LIB_StrAddStr( m_pstrHttpBody, BST_EMAIL_HTTP_CRLF );
    BST_LIB_StrAddStr( m_pstrHttpBody, "Host: " );
    BST_LIB_StrAddStr( m_pstrHttpBody, pstHttpReqHead->pstHostName->pData );
    BST_LIB_StrAddStr( m_pstrHttpBody, BST_EMAIL_HTTP_CRLF );
    BST_LIB_StrAddStr( m_pstrHttpBody, "Connection: Keep-Alive" );
    BST_LIB_StrAddStr( m_pstrHttpBody, BST_EMAIL_HTTP_CRLF );
    BST_LIB_StrAddStr( m_pstrHttpBody, BST_EMAIL_HTTP_CRLF );
}
BST_UINT16 BST_APP_CExcgHttp::CreatePingBody(
    const BST_EMAIL_WBXML_BODY_STRU    *pstWbxmlBody )
{
    BST_UINT16          usLen;

    if ( BST_NULL_PTR == pstWbxmlBody )
    {
        return 0;
    }
    usLen               = CreateWbxmlHeader();
    usLen              += CreatePingWbxml( pstWbxmlBody );

    return usLen;
}

BST_UINT16 BST_APP_CExcgHttp::CreateSyncBody(
    const BST_EMAIL_WBXML_BODY_STRU    *pstWbxmlBody,
    BST_UINT16                          usType )
{
    BST_UINT16          usLen;

    if ( BST_NULL_PTR == pstWbxmlBody )
    {
        return 0;
    }
    usLen               = CreateWbxmlHeader();
    usLen              += CreateSyncWbxml( pstWbxmlBody, usType );

    return usLen;
}


BST_UINT16 BST_APP_CExcgHttp::CreateWbxmlHeader( BST_VOID )
{
    BST_LIB_StrAddByte( m_pstrWbxml,  0x03 );
    BST_LIB_StrAddByte( m_pstrWbxml,  0x01 );
    BST_LIB_StrAddByte( m_pstrWbxml,  0x6a );
    BST_LIB_StrAddByte( m_pstrWbxml,  0x00 );
    return BST_WBXML_HEADER;
}

BST_UINT16 BST_APP_CExcgHttp::CreatePingWbxml(
    const BST_EMAIL_WBXML_BODY_STRU *pstWbxmlBody )
{
    BST_UINT16  usLength;

    if ( BST_NULL_PTR == pstWbxmlBody )
    {
        return 0;
    }
    usLength    = m_pstrWbxml->usUsed;
    BST_LIB_StrAddByte( m_pstrWbxml,  BST_EMAIL_SWITCH_PAGE );
    BST_LIB_StrAddByte( m_pstrWbxml,  BST_EMAIL_PING );
    CreateWbxmlTag( BST_EMAIL_PING_PING, BST_FALSE );   /*<ping>*/
    /*�������*/
    CreateWbxmlData( "480", BST_EMAIL_PING_HEARTBEAT_INTERVAL ); 
    CreateWbxmlTag( BST_EMAIL_PING_FOLDERS, BST_FALSE );    /*<Folders>*/

    BST_CREAT_PING_XML(pstWbxmlBody->stEmlInWxmInfo,BST_EMAIL_NAME);
    BST_CREAT_PING_XML(pstWbxmlBody->stEmlOutWxmInfo,BST_EMAIL_NAME);
    BST_CREAT_PING_XML(pstWbxmlBody->stConWxmInfo,BST_CONTACTS_NAME);
    BST_CREAT_PING_XML(pstWbxmlBody->stCalWxmInfo,BST_CALENDAR_NAME);

    BST_LIB_StrAddByte( m_pstrWbxml,  BST_EMAIL_END );      /*</Folders>*/
    BST_LIB_StrAddByte( m_pstrWbxml,  BST_EMAIL_END );  /*</ping>*/
    if ( m_pstrWbxml->usUsed < usLength )
    {
        return 0;
    }
    usLength    = m_pstrWbxml->usUsed - usLength;
    return usLength;
}
BST_UINT16 BST_APP_CExcgHttp::CreateSyncWbxml(
    const BST_EMAIL_WBXML_BODY_STRU *pstWbxmlBody,
    BST_UINT16                       usType )
{
    BST_UINT16  usLength;

    if ( BST_NULL_PTR == pstWbxmlBody )
    {
        return 0;
    }
    usLength        = m_pstrWbxml->usUsed;

    CreateWbxmlTag( BST_EMAIL_SYNC_SYNC, BST_FALSE );               /*<Sync>*/
    CreateWbxmlTag( BST_EMAIL_SYNC_COLLECTIONS, BST_FALSE );            /*Collections*/

    CreateWbxmlTag( BST_EMAIL_SYNC_COLLECTION, BST_FALSE );                 /*Collenction*/
    switch( usType )
    {
    case BST_APP_EXCH_IN_EMAIL:
        BST_CREAT_SYNC_XML( pstWbxmlBody->stEmlInWxmInfo );
        break;
    case BST_APP_EXCH_OUT_EMAIL:
        BST_CREAT_SYNC_XML( pstWbxmlBody->stEmlOutWxmInfo );
        break;
    case BST_APP_EXCH_CONTACT:
        BST_CREAT_SYNC_XML( pstWbxmlBody->stConWxmInfo );
        break;
    case BST_APP_EXCH_CALENDAR:
        BST_CREAT_SYNC_XML( pstWbxmlBody->stCalWxmInfo );
        break;
    default:
        break;
    }
    /*���б�ɾ������Ŀ���ƶ���ɾ���ļ�����*/
    CreateWbxmlData( "1", BST_EMAIL_SYNC_DELETES_AS_MOVES );                        /*<DeleteAsMoves>*//*</DeleteAsMoves>*/
    /*��server���ط����仯*/
    CreateWbxmlTag( BST_EMAIL_SYNC_GET_CHANGES, BST_TRUE );                         /*</GetChanges>*/
    /*server���ر仯��Ŀ�����ֵ*/
    CreateWbxmlData( pstWbxmlBody->psWinSize->pData, BST_EMAIL_SYNC_WINDOW_SIZE );  /*<WindowSize>*//*</WindowSize>*/
    CreateWbxmlTag( BST_EMAIL_SYNC_OPTIONS, BST_FALSE );                            /*<Options>*/
    /*��ǰһ�����ڵı仯*/
    CreateWbxmlData( "4", BST_EMAIL_SYNC_FILTER_TYPE );                                 /*<FilterType>*//*</FilterType>*/
    BST_LIB_StrAddByte( m_pstrWbxml, BST_EMAIL_SWITCH_PAGE );
    BST_LIB_StrAddByte( m_pstrWbxml, BST_EMAIL_BASE );
    CreateWbxmlTag( BST_EMAIL_BASE_BODY_PREFERENCE, BST_FALSE );                        /*<BodyPreference>*/
    CreateWbxmlData( "2", BST_EMAIL_BASE_TYPE );                                            /*<Type>*//*</Type>*/
    /*�ʼ��ضϵĴ�С�����Բ����޸�*/
    CreateWbxmlData( "200000", BST_EMAIL_BASE_TRUNCATION_SIZE );                            /*<TruncationSize>*//*</TruncationSize>*/
    BST_LIB_StrAddByte( m_pstrWbxml, BST_EMAIL_END );                                   /*</BodyPreference>*/
    BST_LIB_StrAddByte( m_pstrWbxml, BST_EMAIL_END );                               /*</Options>*/
    BST_LIB_StrAddByte( m_pstrWbxml, BST_EMAIL_END );                       /*</Collection>*/

    BST_LIB_StrAddByte( m_pstrWbxml, BST_EMAIL_END );                   /*</Collections>*/
    BST_LIB_StrAddByte( m_pstrWbxml, BST_EMAIL_END );               /*</Sync>*/
    if ( m_pstrWbxml->usUsed < usLength )
    {
        return 0;
    }
    usLength        = m_pstrWbxml->usUsed - usLength;
    return usLength;
}
BST_VOID BST_APP_CExcgHttp::CreateWbxmlTag(
    BST_CHAR cTag,
    BST_BOOL bNoContent )
{
    BST_LIB_StrAddByte( m_pstrWbxml, bNoContent ? cTag : cTag | BST_EMAIL_WITH_CONTENT );
}

BST_VOID BST_APP_CExcgHttp::CreateWbxmlData(
    const BST_CHAR     *strData,
    const BST_CHAR      cTag )
{
    BST_LIB_StrAddByte( m_pstrWbxml,  cTag | BST_EMAIL_WITH_CONTENT );
    BST_LIB_StrAddByte( m_pstrWbxml,  BST_EMAIL_SIR_I );
    BST_LIB_StrAddStr( m_pstrWbxml, strData );
    BST_LIB_StrAddByte( m_pstrWbxml, 0 );
    BST_LIB_StrAddByte( m_pstrWbxml, BST_EMAIL_END );
}

BST_EMAIL_SERVER_STATE_ENUM_UINT8 BST_APP_CExcgHttp::ParseRspns(
    const BST_CHAR *pcResponse,
    BST_UINT16      usLength )
{
    BST_EMAIL_SERVER_STATE_ENUM_UINT8   enRtnVal;
    if ( BST_NULL_PTR == pcResponse )
    {
        return BST_APP_SERVER_UNUSUAL;
    }
    if ( 0 == usLength )
    {
        return BST_APP_SERVER_UNUSUAL;
    }
    /*
     *��Ƭ����ʣ�ಿ�֣�������
     */
    if ( BST_LIB_StrCmp( 0, pcResponse,
                         BST_EMAIL_HTTP_VERSION,
                         BST_LIB_StrLen(BST_EMAIL_HTTP_VERSION) ) )
    {
        BST_RLS_LOG( "BST_APP_CExcgHttp excrescent packet." );
        return BST_APP_SERVER_EXCRESCENT;
    }

   /*
    *http������״̬�ظ���˵���쳣
    */
    if( BST_LIB_StrCmp( BST_LIB_StrLen(BST_EMAIL_HTTP_VERSION) + 1,
                        pcResponse,
                        BST_EMAIL_HTTP_STATUS_LINE,
                        BST_LIB_StrLen(BST_EMAIL_HTTP_STATUS_LINE) ) )
    {
        BST_RLS_LOG( "BST_APP_CExcgHttp server is not normal!" );
        return BST_APP_SERVER_UNUSUAL;
    }

    /*
     * ͨ������������ж��������ping�����лظ���Ϊ�����ʼ�
     */
    if ( PING_CMD == m_enCmdType )
    {
        enRtnVal        = ParsePingRspns( pcResponse, usLength );
        return enRtnVal;
        //BST_RLS_LOG( "BST_APP_CExcgHttp new letter" );
        //return BST_APP_SERVER_NEW_MAIL;
    }
    /*
     * ͨ������������ж��������sync��
     */
    else if ( SYNC_CMD == m_enCmdType )
    {
        enRtnVal        = ParseSyncRspns( pcResponse, usLength );
        return enRtnVal;
    }
    /*
     * ��������Ȳ���pingҲ����sync,һ�㲻�����
     */
    else
    {
        BST_RLS_LOG( "BST_APP_CExcgHttp m_enCmdType is not normal!" );
        return BST_APP_SERVER_UNUSUAL;
    }
}


BST_INT32 BST_APP_CExcgHttp::ParsePingStatus(
    const BST_CHAR  *pstRspStr,
    const BST_UINT16 usLength)
{
    BST_UINT16          StatusPos;
    BST_LIB_StrStru    *pstrWbxmlLen;
    BST_INT32           lStatus;
    BST_UINT16          i;
    BST_CHAR            BST_EMAIL_HTTP_ENCODE_STATUS[] = {(BST_EMAIL_PING_STATUS | BST_EMAIL_WITH_CONTENT), BST_EMAIL_SIR_I};
    lStatus             = 0;
    pstrWbxmlLen        = BST_LIB_StrCreat( usLength );
    StatusPos           = BST_LIB_StrFind( pstRspStr,
                                           usLength,
                                           BST_EMAIL_HTTP_ENCODE_STATUS,
                                           sizeof(BST_EMAIL_HTTP_ENCODE_STATUS));
    if ( BST_LIB_STR_NPO != StatusPos )
    {
        i              = StatusPos + BST_LIB_StrLen( BST_EMAIL_HTTP_ENCODE_STATUS );
        /* ��Content-Length:֮��ʼ���� */
        while( ( ( pstRspStr[i] >= '0' ) && ( pstRspStr[i] <= '9' ) ) && ( i < usLength ) )
        {
            BST_LIB_StrAddByte( pstrWbxmlLen, pstRspStr[i] );
            i++;
        }
        /* ������ת��Ϊ���ִ���ֲ����� */
        lStatus          = atoi( pstrWbxmlLen->pData );
    }

    BST_LIB_StrDelete( pstrWbxmlLen );

    return lStatus;
}


BST_EMAIL_SERVER_STATE_ENUM_UINT8 BST_APP_CExcgHttp::ParsePingRspns(
    const BST_CHAR  *pstRspStr,
    const BST_UINT16 usLength)
{
    BST_INT32           lWbxmlLen;
    BST_LIB_StrStru    *pstrWbxmlLen;
    BST_UINT16          i;
    BST_UINT16          ContentLenPos;  /*��¼Content-Lengthλ��*/
    BST_UINT16          TrsEncodingPos; /*��¼Transfer-Encodingλ��*/
    BST_UINT16          LFPos;          /*��¼"\r\n\r\n"λ�� */
    BST_UINT16          GzipPos;/*��¼"gzip"λ�� */
    BST_CHAR           *puncompr;
    BST_UINT32          uncomprLen;
    BST_BOOL            bstatus;
    /*��ʼ��*/
    ContentLenPos       = 0;
    TrsEncodingPos      = 0;
    LFPos               = 0;
    lWbxmlLen           = 0;
    bstatus             = BST_FALSE;

    pstrWbxmlLen        = BST_LIB_StrCreat( usLength );
    BST_ASSERT_NULL_RTN( pstrWbxmlLen, BST_APP_SERVER_PARSE_EXCEPT );

    /*�ҵ�Content-Length:��λ��*/
    ContentLenPos       = BST_LIB_StrFind( pstRspStr,
                                           usLength,
                                           BST_EMAIL_HTTP_CODE_CONTENT,
                                           BST_LIB_StrLen(BST_EMAIL_HTTP_CODE_CONTENT));
    TrsEncodingPos      = BST_LIB_StrFind( pstRspStr,
                                           usLength,
                                           BST_EMAIL_HTTP_CODE_CHUNKED,
                                           BST_LIB_StrLen(BST_EMAIL_HTTP_CODE_CHUNKED));
    /* �ҵ�Content-Lengthͷ��Ϣ,RFC1945�������������ŵı�ʶ���ȵ����� */
    if ( BST_LIB_STR_NPO != ContentLenPos ) // ���ȿ�ȷ��
    {
        i               = ContentLenPos + BST_LIB_StrLen( BST_EMAIL_HTTP_CODE_CONTENT );
        /* ��Content-Length:֮��ʼ���� */
        while( ( pstRspStr[i] != '\r' ) && ( i < usLength ) )
        {
            if ( ( pstRspStr[i] >= '0' )
              && ( pstRspStr[i] <= '9' ) )
            {
                BST_LIB_StrAddByte( pstrWbxmlLen, pstRspStr[i] );
            }
            i++;
        }
        /* ������ת��Ϊ���ִ���ֲ����� */
        lWbxmlLen           = atoi( pstrWbxmlLen->pData );
    }
    /* ʹ��Transfer-Encoding: chunked��ͷ��Ϣ,RFC2616 */
    else if ( BST_LIB_STR_NPO != TrsEncodingPos ) // ���Ȳ�ȷ��
    {
        LFPos               = BST_LIB_StrFind( pstRspStr,
                                               usLength,
                                               BST_EMAIL_HTTP_HEAD_END,
                                               BST_LIB_StrLen(BST_EMAIL_HTTP_HEAD_END));
        /* �����쳣���� */
        if ( BST_LIB_STR_NPO == LFPos )
        {
            BST_RLS_LOG( "Transfer-Encoding parse except!" );
            BST_LIB_StrDelete( pstrWbxmlLen );
            return BST_APP_SERVER_PARSE_EXCEPT;
        }
        i                   = LFPos + BST_LIB_StrLen(BST_EMAIL_HTTP_HEAD_END);
        while( ( pstRspStr[i] != '\r' ) && ( i < usLength ) )
        {
            BST_LIB_StrAddByte( pstrWbxmlLen, pstRspStr[i] );
            i++;
        }
        lWbxmlLen           = HexStrToInt( (const BST_UINT8 *)pstrWbxmlLen->pData,
                                            pstrWbxmlLen->usUsed );
        BST_RLS_LOG1( "---BST_APP_CExcgHttp lWbxmlLen: %d", lWbxmlLen );
    }
    else
    /* 2�ֱ��붼���ǣ����������� */
    {
        BST_RLS_LOG( "BST_APP_CExcgHttp parse except!" );
        BST_LIB_StrDelete( pstrWbxmlLen );
        return BST_APP_SERVER_PARSE_EXCEPT;
    }
    /* �����ʼ� */
    if ( ( lWbxmlLen < BST_EMAIL_EAS_NEW_MAIL_LEN ) && ( lWbxmlLen >= 0 ) )
    {
        BST_RLS_LOG( "BST_APP_CExcgHttp not new letter" );
        BST_LIB_StrDelete( pstrWbxmlLen );
        return BST_APP_SERVER_NOT_NEW_MAIL;
    }
    /* �����ʼ� */
    else if ( lWbxmlLen > 0 )
    {
        LFPos               = BST_LIB_StrFind( pstRspStr,
                                               usLength,
                                               BST_EMAIL_HTTP_HEAD_END,
                                               BST_LIB_StrLen(BST_EMAIL_HTTP_HEAD_END));
        if ( BST_LIB_STR_NPO == LFPos )
        {
            BST_RLS_LOG( "encode parse except!" );
            BST_LIB_StrDelete( pstrWbxmlLen );
            return BST_APP_SERVER_PARSE_EXCEPT;
        }

        if ( BST_LIB_STR_NPO != ContentLenPos )
        {
            GzipPos         = BST_LIB_StrFind( pstRspStr,
                                               usLength,
                                               BST_EMAIL_HTTP_CONTENT_ENCODING,
                                               BST_LIB_StrLen(BST_EMAIL_HTTP_CONTENT_ENCODING));
            if ( BST_LIB_STR_NPO != GzipPos ) // gzip
            {
                /* ��ѹgzip */
                i           = LFPos + BST_LIB_StrLen(BST_EMAIL_HTTP_HEAD_END);
                puncompr    = BST_ZLB_Uncompress(&pstRspStr[i], lWbxmlLen, &uncomprLen);
                if ( NULL != puncompr ) {
                    BST_DBG_LOG1( "++++Test_Uncompress length:%d", uncomprLen);
                    for (i = 0; i < uncomprLen; i++) {
                        BST_DBG_LOG1( "++++Test_Uncompress uncopress:%d", puncompr[i]);
                    }
                    bstatus = ParsePingStatus(puncompr, uncomprLen);
                    BST_OS_FREE(puncompr);
                }
                else
                {
                    BST_DBG_LOG( "++++Test_Uncompress error!");
                }
            }
            else
            {
                bstatus = ParsePingStatus(&pstRspStr[LFPos], usLength - LFPos);
            }
        } 
        else if (BST_LIB_STR_NPO != TrsEncodingPos ) // chunked
        {
            bstatus = ParsePingStatus(&pstRspStr[LFPos], lWbxmlLen);
        }

        /* ����Status */
        BST_RLS_LOG("BST_APP_CExcgHttp new letter" );
        BST_LIB_StrDelete( pstrWbxmlLen );
        return ( BST_TRUE == bstatus ) ? BST_APP_SERVER_NEW_MAIL : BST_APP_SERVER_NOT_NEW_MAIL;
    }
    /* ����С��0��˵���������� */
    else
    {
        BST_RLS_LOG( "BST_APP_CExcgHttp parse except!" );
        BST_LIB_StrDelete( pstrWbxmlLen );
        return BST_APP_SERVER_PARSE_EXCEPT;
    }
}
BST_EMAIL_SERVER_STATE_ENUM_UINT8 BST_APP_CExcgHttp::ParseSyncRspns(
    const BST_CHAR  *pstRspStr,
    const BST_UINT16 usLength)
{
    BST_INT32           lWbxmlLen;
    BST_LIB_StrStru    *pstrWbxmlLen;
    BST_UINT16          i;
    BST_UINT16          ContentLenPos;  /*��¼Content-Lengthλ��*/
    BST_UINT16          TrsEncodingPos; /*��¼Transfer-Encodingλ��*/
    BST_UINT16          LFPos;          /*��¼"\r\n\r\n"λ�� */
    /*��ʼ��*/
    ContentLenPos       = 0;
    TrsEncodingPos      = 0;
    LFPos               = 0;
    lWbxmlLen           = 0;

    pstrWbxmlLen        = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    BST_ASSERT_NULL_RTN( pstrWbxmlLen, BST_APP_SERVER_PARSE_EXCEPT );

    /*�ҵ�Content-Length:��λ��*/
    ContentLenPos       = BST_LIB_StrFind( pstRspStr,
                                           usLength,
                                           BST_EMAIL_HTTP_CODE_CONTENT,
                                           BST_LIB_StrLen(BST_EMAIL_HTTP_CODE_CONTENT));
    TrsEncodingPos      = BST_LIB_StrFind( pstRspStr,
                                           usLength,
                                           BST_EMAIL_HTTP_CODE_CHUNKED,
                                           BST_LIB_StrLen(BST_EMAIL_HTTP_CODE_CHUNKED));
    /* �ҵ�Content-Lengthͷ��Ϣ,RFC1945�������������ŵı�ʶ���ȵ����� */
    if ( BST_LIB_STR_NPO != ContentLenPos )
    {
        i               = ContentLenPos + BST_LIB_StrLen( BST_EMAIL_HTTP_CODE_CONTENT );
        /* ��Content-Length:֮��ʼ���� */
        while( ( pstRspStr[i] != '\r' ) && ( i < usLength ) )
        {
            if ( ( pstRspStr[i] >= '0' )
              && ( pstRspStr[i] <= '9' ) )
            {
                BST_LIB_StrAddByte( pstrWbxmlLen, pstRspStr[i] );
            }
            i++;
        }
        /* ������ת��Ϊ���ִ���ֲ����� */
        lWbxmlLen           = atoi( pstrWbxmlLen->pData );
    }
    /* ʹ��Transfer-Encoding: chunked��ͷ��Ϣ,RFC2616 */
    else if ( BST_LIB_STR_NPO != TrsEncodingPos )
    {
        LFPos               = BST_LIB_StrFind( pstRspStr,
                                               usLength,
                                               BST_EMAIL_HTTP_HEAD_END,
                                               BST_LIB_StrLen(BST_EMAIL_HTTP_HEAD_END));
        /* �����쳣���� */
        if ( BST_LIB_STR_NPO == LFPos )
        {
            BST_RLS_LOG( "Transfer-Encoding parse except!" );
            BST_LIB_StrDelete( pstrWbxmlLen );
            return BST_APP_SERVER_PARSE_EXCEPT;
        }
        i                   = LFPos + BST_LIB_StrLen(BST_EMAIL_HTTP_HEAD_END);
        while( ( pstRspStr[i] != '\r' ) && ( i < usLength ) )
        {
            BST_LIB_StrAddByte( pstrWbxmlLen, pstRspStr[i] );
            i++;
        }
        lWbxmlLen           = HexStrToInt( (const BST_UINT8 *)pstrWbxmlLen->pData,
                                            pstrWbxmlLen->usUsed );
    }
    else
    /* 2�ֱ��붼���ǣ����������� */
    {
        BST_RLS_LOG( "BST_APP_CExcgHttp parse except!" );
        BST_LIB_StrDelete( pstrWbxmlLen );
        return BST_APP_SERVER_PARSE_EXCEPT;
    }
    /* �����ʼ� */
    if ( ( lWbxmlLen < BST_EMAIL_EAS_NEW_MAIL_LEN ) && ( lWbxmlLen >= 0 ) )
    {
        BST_RLS_LOG( "BST_APP_CExcgHttp not new letter" );
        BST_LIB_StrDelete( pstrWbxmlLen );
        return BST_APP_SERVER_NOT_NEW_MAIL;
    }
    /* �����ʼ� */
    else if ( lWbxmlLen > BST_EMAIL_EAS_NEW_MAIL_LEN )
    {
        BST_RLS_LOG("BST_APP_CExcgHttp new letter" );
        BST_LIB_StrDelete( pstrWbxmlLen );
        return BST_APP_SERVER_NEW_MAIL;
    }
    /* ����С��0��˵���������� */
    else
    {
        BST_RLS_LOG( "BST_APP_CExcgHttp parse except!" );
        BST_LIB_StrDelete( pstrWbxmlLen );
        return BST_APP_SERVER_PARSE_EXCEPT;
    }
}

BST_LIB_StrStru *BST_APP_CExcgHttp::GetRequest(
    BST_UINT16              usType )
{
    switch( usType )
    {
        case BST_APP_EXCH_IN_EMAIL:
            return m_pstrReqIn;
        case BST_APP_EXCH_OUT_EMAIL:
            return m_pstrReqOut;
        case BST_APP_EXCH_CONTACT:
            return m_pstrReqCon;
        case BST_APP_EXCH_CALENDAR:
            return m_pstrReqCal;
        case BST_APP_EXCH_PING:
            return m_pstrRequest;
        default:
            BST_DBG_LOG1("GetRequest Type err",usType);
            return BST_NULL_PTR;
    }
}

BST_INT32 BST_APP_CExcgHttp::HexStrToInt(
    const BST_UINT8* pHexStr,
    BST_UINT16       usLen)
{
    BST_UINT16  i;
    BST_UINT16  n;
    BST_INT32   lTemp;

    lTemp       = 0;
    if ( BST_NULL_PTR == pHexStr )
    {
        return -1;
    }
    /* 8λ16���Ƶ�����4���ֽڣ�����������ش��� */
    if ( usLen > 8 )
    {
        return -1;
    }
    for ( i = 0; i < usLen; i++ )
    {
        if ( (pHexStr[i] >= 'A') && (pHexStr[i] <= 'F') )/*'A'-'F'*/
        {
            n   = pHexStr[i] - 'A' + 10;
        }
        else if ( (pHexStr[i] >= 'a') && (pHexStr[i] <= 'f') )/*'a'-'f'*/
        {
            n   = pHexStr[i] - 'a' + 10;
        }
        else if ( (pHexStr[i] >= '0') && (pHexStr[i] <= '9') )/*'0'-'9'*/
        {
            n   = pHexStr[i] - '0';
        }
        /*�����ַ������ش���*/
        else
        {
            return -1;
        }
        /*����ת��Ϊ10���Ʋ��ۼ�*/
        lTemp   = lTemp*16 + n;
    }
    return lTemp;
}

BST_APP_CExcgHttp::~BST_APP_CExcgHttp()
{
#if ( BST_OS_VER != BST_QCOM_ROS )
    try
    {
#endif  /*�������������б���״̬��Ϊ��ʼֵ*/
        BST_LIB_StrDelete( m_pstrHttpBody );
        BST_LIB_StrDelete( m_pstrRequest );
        BST_LIB_StrDelete( m_pstrReqIn );
        BST_LIB_StrDelete( m_pstrReqOut );
        BST_LIB_StrDelete( m_pstrReqCon );
        BST_LIB_StrDelete( m_pstrReqCal );
        BST_LIB_StrDelete( m_pstrWbxml );
        m_enCmdType     = INVALID_SYNC_CMD;
#if ( BST_OS_VER != BST_QCOM_ROS )
    }
    catch (...)
    {
        BST_DBG_LOG("BST_APP_CExcgHttp exception!");
    }
#endif
}
