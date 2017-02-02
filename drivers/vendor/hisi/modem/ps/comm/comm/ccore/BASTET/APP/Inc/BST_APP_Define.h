
#ifndef __BST_APP_DEFINE_H__
#define __BST_APP_DEFINE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Typedefine.h"
#include "BST_OS_Timer.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*public state*/
#define BST_EMAIL_UNCONNECT             ( 0x00 )
#define BST_EMAIL_CONNECTED             ( 0x01 )
#define BST_EMAIL_QUITED                ( 0x06 )
#define BST_EMAIL_EXCEPTION             ( 0x08 )
/*pop3 state*/
#define BST_EMAIL_POP3_LOGINED          ( 0x02 )
#define BST_EMAIL_POP3_AUTHED           ( 0x03 )
#define BST_EMAIL_POP3_QUERYNUMED       ( 0x04 )
#define BST_EMAIL_POP3_QUERYUIDED       ( 0x05 )
/*imap state*/
#define BST_EMAIL_IMAP_ID               ( 0x02 )
#define BST_EMAIL_IMAP_LOGINED          ( 0x03 )
#define BST_EMAIL_IMAP_SELECTED         ( 0x04 )
#define BST_EMAIL_IMAP_QUERYED          ( 0x05 )
/*exchange state*/
#define BST_EMAIL_EAS_QUERYED_INBOX     ( 0x02 )
#define BST_EMAIL_EAS_QUERYED_OUTBOX    ( 0x03 )
#define BST_EMAIL_EAS_QUERYED_CON       ( 0x04 )
#define BST_EMAIL_EAS_QUERYED_CAL       ( 0x05 )

#define BST_APP_MAIN_TASK_ID            ( 0x01 )

/*��������ʧ�ܾ��ϱ�*/
#define BST_CON_FAIL_NUM                ( 3 )
/*20s������ʱ*/
#define BST_APP_CONNECT_TIME_OUT        ( 20 * BST_OS_MS_IN_S )
/*���ճ�ʱʱ�����Ҫ����socket����ʱʱ��*/
#define BST_APP_RX_TIME_OUT             ( BST_IP_RX_TIME_OUT + BST_OS_MS_IN_S )


#define BST_APP_IsEncrpValid(Mode)     ( ( ( Mode ) > BST_APP_ENCRP_INVALID_TYPE )\
                                      && ( ( Mode ) < BST_APP_ENCRP_MODE_BUTT ) )
#define BST_APP_IsHbChkTypeValid(Type) ( ( ( Type ) > BST_APP_HB_INVALID_CHK_TYPE )\
                                      && ( ( Type ) < BST_APP_HB_CHK_TYPE_BUTT ) )

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/
enum OBJ_TYPE_ENUM
{
    BST_APP_TYPE_MIN                = 0,
    BST_APP_TYPE_SYSTASK,
    BST_APP_TYPE_MAILBOX,
    BST_APP_TYPE_HEARTBEAT,
    BST_OBJ_TYPE_MAX
};
typedef BST_UINT8                       BST_APP_TYPE_ENUM_UINT8;

enum BST_ENCRP_MODE_ENUM
{
    BST_APP_ENCRP_INVALID_TYPE          = 0,
    BST_APP_ENCRP_NO_TYPE,
    BST_APP_ENCRP_SSL_MODE,
    BST_APP_ENCRP_TLS_MODE,
    BST_APP_ENCRP_MODE_BUTT
};
typedef BST_UINT32                       BST_APP_ENCRP_MODE_ENUM_UINT32;

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/

/*****************************************************************************
 ö����    : BST_HB_RETRY_INFO
 Э����  :
 ASN.1���� :
 ö��˵��  : ����Ӧ�÷����ش��������Ϣ
*****************************************************************************/
typedef struct 
{
    BST_UINT32                          ulMaxReTimes;       /*����ش�����*/
    BST_UINT32                          ulIntervals;        /*��ʱ���ʱ��*/
}BST_HB_RETRY_INFO;

/*****************************************************************************
 ö����    : TX_HB_RETRY_TIMER_STRU
 Э����  :
 ASN.1���� :
 ö��˵��  : Ӧ�÷����ش���ʱ���������Ϣ
*****************************************************************************/
typedef struct
{
    BST_OS_TIMERID_T      ulTimerId;
    BST_UINT32            usRetryNum;                       /*��ǰ�ش�����*/
    BST_HB_RETRY_INFO     stRetryInfo;
} TX_HB_RETRY_TIMER_STRU; 


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif

