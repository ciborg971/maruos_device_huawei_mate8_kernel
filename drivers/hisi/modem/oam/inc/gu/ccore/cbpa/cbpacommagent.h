

#ifndef __CBPA_COMMAGENT_H__
#define __CBPA_COMMAGENT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CbpaPsInterface.h"
#include "OmHdlcInterface.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CBPCA_HDLC_BUFFER_SIZE          (3 * 1024)          /* CBPCA����HDLC��װ�����װ�Ļ����С */

#define CBPCA_MAX_INDEX                 (0x7FFF)            /* HDLC��Index��ֵ��Ч��ΧΪ:0~0x7FFF */


/* CBPCA�յ��ϲ�Ӧ�÷��͵����ݣ���ҪԤ��6���ֽڣ�������дHDLC֡�ж�Index��Length��MsgId��
   ���Լ���һ���ڴ濽����������ݷ���Ч�� */
#define CBPCA_RCV_UPPER_DATA_RSV_LEN    (6)

/* CBPA ���Դ�ӡ�� */
#if (VOS_WIN32 == VOS_OS_VER)
#define CBPA_DEBUG_TRACE(pucData, ulDataLen)    {;}
#else
#define CBPA_DEBUG_TRACE(pucData, ulDataLen) \
    if(VOS_FALSE != (g_ucCbpcaDbgFlag)) \
    { \
        VOS_UINT32 ulCbpaDbgLoop; \
        (VOS_VOID)vos_printf("\n%s, Rcv UART Data Len: = %d\n", __FUNCTION__, ulDataLen); \
        for (ulCbpaDbgLoop = 0 ; ulCbpaDbgLoop < ulDataLen; ulCbpaDbgLoop++) \
        { \
            (VOS_VOID)vos_printf("%02x ", *((VOS_UINT8*)pucData + ulCbpaDbgLoop)); \
        } \
        (VOS_VOID)vos_printf("\r\n"); \
    } \

#endif

/* CBPA LOG�� */
#define CBPA_INFO_LOG(string)            PS_LOG(WUEPS_PID_CBPCA, 0, PS_PRINT_INFO,   string)
#define CBPA_NORMAL_LOG(string)          PS_LOG(WUEPS_PID_CBPCA, 0, PS_PRINT_NORMAL, string)
#define CBPA_WARNING_LOG(string)         PS_LOG(WUEPS_PID_CBPCA, 0, PS_PRINT_WARNING,string)
#define CBPA_ERROR_LOG(string)           PS_LOG(WUEPS_PID_CBPCA, 0, PS_PRINT_ERROR,  string)

#define CBPA_INFO1_LOG(string, para1)    PS_LOG1(WUEPS_PID_CBPCA, 0, PS_PRINT_INFO,   string, para1)
#define CBPA_NORMAL1_LOG(string, para1)  PS_LOG1(WUEPS_PID_CBPCA, 0, PS_PRINT_NORMAL, string, para1)
#define CBPA_WARNING1_LOG(string, para1) PS_LOG1(WUEPS_PID_CBPCA, 0, PS_PRINT_WARNING,string, para1)
#define CBPA_ERROR1_LOG(string, para1)   PS_LOG1(WUEPS_PID_CBPCA, 0, PS_PRINT_ERROR,  string, para1)

/* CBPCA��ά�ɲ�ͳ�ƺ� */
#define CBPCA_STATISTIC_INC(statistic_type)            ((*(((VOS_UINT32 *)&g_stCbpcaStatic) + statistic_type))++)

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/*****************************************************************************
 ö����    : CBP_MODEM_STATUS_ENUM
 ö��˵��  : CBP Modem�Ƿ����
*****************************************************************************/
enum CBP_MODEM_STATUS_ENUM
{
    CBP_MODEM_STATUS_NOT_READY          = 0x0000,           /* CBP Modemδ���� */
    CBP_MODEM_STATUS_READY              = 0x0001,           /* CBP Modem�Ѿ��� */

    CBP_MODEM_STATUS_BUTT
};
typedef VOS_UINT32 CBP_MODEM_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : CBPCA_STATISTIC_TYPE_ENUM
 ö��˵��  : CBPCA��ά�ɲ�����ö��
*****************************************************************************/
enum CBPCA_STATISTIC_TYPE_ENUM
{
    CBPCA_STATISTIC_HDLC_DECAP_SUCC             = 0x0000,    /* HDLC���װ:���װ�ɹ� */
    CBPCA_STATISTIC_UART_CALLBACK_WRONG_PORTNO  = 0x0001,    /* ������ûص���������uPortNo���� */
    CBPCA_STATISTIC_UART_CALLBACK_NULL_PTR      = 0x0002,    /* ������ûص������������ָ��Ϊ�� */
    CBPCA_STATISTIC_UART_CALLBACK_LEN_IS_ZERO   = 0x0003,    /* ������ûص�����������ڳ���Ϊ0 */
    CBPCA_STATISTIC_UART_CALLBACK_CBP_NOT_READY = 0x0004,    /* ������ûص���������CBP״̬ΪNOT READY */
    CBPCA_STATISTIC_HDLC_DECAP_FCS_ERR          = 0x0005,    /* HDLC���װ:FCS���� */
    CBPCA_STATISTIC_HDLC_DECAP_DISCARD          = 0x0006,    /* HDLC���װ:�쳣֡������ */
    CBPCA_STATISTIC_HDLC_DECAP_BUFF_FULL        = 0x0007,    /* HDLC���װ:������� */
    CBPCA_STATISTIC_HDLC_DECAP_PARA_ERROR       = 0x0008,    /* HDLC���װ:��δ��� */
    CBPCA_STATISTIC_HDLC_DECAP_INVALID_INDEX    = 0x0009,    /* HDLC���װ:�����Index */
    CBPCA_STATISTIC_HDLC_DECAP_NO_DATA_FIELD    = 0x000A,    /* HDLC���װ:���װ������ݳ���<=6��������Data�� */
    CBPCA_STATISTIC_HDLC_DECAP_LENGTH_ABNORMAL  = 0x000B,    /* HDLC���װ:���װ��LENGTH��<=2���쳣 */
    CBPCA_STATISTIC_HDLC_DECAP_LENGTH_IS_LESS   = 0x000C,    /* HDLC���װ:Length��ʵ�����ݳ���ҪС */
    CBPCA_STATISTIC_HDLC_DECAP_LENGTH_IS_MORE   = 0x000D,    /* HDLC���װ:Length��ʵ�����ݳ���Ҫ�� */
    CBPCA_STATISTIC_HDLC_DECAP_INVALID_MSGID    = 0x000E,    /* HDLC���װ:�����MsgId */
    CBPCA_STATISTIC_HDLC_DECAP_INVALID_FRAME    = 0x000F,    /* HDLC���װ:��Ч֡ */

    CBPCA_STATISTIC_HDLC_ENCAP_SEND_SUCC        = 0x0010,    /* ���õ���ӿ�DRV_UART_SEND���ͳɹ� */
    CBPCA_STATISTIC_CBP_NOT_READY_DISCARD_FRAME = 0x0011,    /* CBPδ���������·���CBP��֡������ */
    CBPCA_STATISTIC_CANNOT_FIND_MATCH_MSGID     = 0x0012,    /* ����CBP�����ݣ������Ҳ���MsgId��Ӧ��PID�������� */
    CBPCA_STATISTIC_HDLC_ENCAP_FAIL             = 0x0013,    /* HDLC��װʧ�� */
    CBPCA_STATISTIC_HDLC_ENCAP_SEND_FAIL        = 0x0014,    /* ���õ���ӿ�DRV_UART_SEND����ʧ�� */

    CBPCA_STATISTIC_TYPE_BUTT
};
typedef VOS_UINT32 CBPCA_STATISTIC_TYPE_ENUM_UINT32;

/*******************************************************************************
  4 �ṹ����
*******************************************************************************/
/*****************************************************************************
 �ṹ��    : CBPCA_HDLC_ENCAP_BUFFER_STRU
 �ṹ˵��  : CBPCAģ�������ʹ�������ĵ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          *pucEncapBuff;       /* HDLC��װ���õĻ��� */
    VOS_UINT32                          ulEncapBuffSize;    /* �����ܳ��� */
}CBPCA_HDLC_ENCAP_BUFFER_STRU;

/*****************************************************************************
 �ṹ��    : CBPCA_CTX_STRU
 �ṹ˵��  : CBPCAģ�������ʹ�������ĵ����ݽṹ
*****************************************************************************/
typedef struct
{
    CBPCA_HDLC_ENCAP_BUFFER_STRU        stEncapCtrlCtx;     /* HDLC��װ���õĻ��� */
    OM_HDLC_STRU                        stDecapCtrlCtx;     /* HDLC���װ��ʹ�õĻ��漰���Ʋ��� */
    VOS_UINT16                          usExpectRcvIndex;   /* CPBCA�������յ���Index���� */
    VOS_UINT16                          usExpectSndIndex;   /* CPBCA�������͵�Index���� */
    CBP_MODEM_STATUS_ENUM_UINT32        enCBPStatus;        /* CPB Modem��ǰ�Ƿ���� */
}CBPCA_CTX_STRU;

/*****************************************************************************
 �ṹ��    : CBPCA_STATISTIC_STRU
 �ṹ˵��  : CBPCAģ���ά�ɲ�ͳ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHdlcDecapSucc;                        /* HDLC���װ:���װ�ɹ� */
    VOS_UINT32                          ulUartCBWrongPortNo;                    /* ������ûص���������uPortNo���� */
    VOS_UINT32                          ulUartCBNullPtr;                        /* ������ûص������������ָ��Ϊ�� */
    VOS_UINT32                          ulUartCBLenIsZero;                      /* ������ûص�����������ڳ���Ϊ0 */
    VOS_UINT32                          ulUartCBCBPNotReady;                    /* ������ûص���������CBP״̬ΪNOT READY */
    VOS_UINT32                          ulHdlcDecapFCSError;                    /* HDLC���װ:FCS���� */
    VOS_UINT32                          ulHdlcDecapDiscard;                     /* HDLC���װ:�쳣֡������ */
    VOS_UINT32                          ulHdlcDecapBuffFull;                    /* HDLC���װ:������� */
    VOS_UINT32                          ulHdlcDecapParaError;                   /* HDLC���װ:��δ��� */
    VOS_UINT32                          ulHdlcDecapInvalidIndex;                /* HDLC���װ:�����Index */
    VOS_UINT32                          ulHdlcDecapNoDataField;                 /* HDLC���װ:���װ������ݳ���<=6��������Data�� */
    VOS_UINT32                          ulHdlcDecapLengthAbnormal;              /* HDLC���װ:���װ��LENGTH��<=2���쳣 */
    VOS_UINT32                          ulHdlcDecapLengthIsLess;                /* HDLC���װ:Length��ʵ�����ݳ���ҪС */
    VOS_UINT32                          ulHdlcDecapLengthIsMore;                /* HDLC���װ:Length��ʵ�����ݳ���Ҫ�� */
    VOS_UINT32                          ulHdlcDecapInvalidMsgId;                /* HDLC���װ:�����MsgId */
    VOS_UINT32                          ulHdlcDecapInvalidFrame;                /* HDLC���װ:��Ч֡ */

    VOS_UINT32                          ulSendToUartSucc;                       /* ���õ���ӿ�DRV_UART_SEND���ͳɹ� */
    VOS_UINT32                          ulCBPNotReadyDiscardFrame;              /* CBPδ���������·���CBP��֡������ */
    VOS_UINT32                          ulHdlcEncapInvalidPID;                  /* ����CBP�����ݣ������Ҳ���MsgId��Ӧ��PID�������� */
    VOS_UINT32                          ulHdlcEncapFail;                        /* HDLC��װʧ�� */
    VOS_UINT32                          ulSendToUartFail;                       /* ���õ���ӿ�DRV_UART_SEND����ʧ�� */
}CBPCA_STATISTIC_STRU;


/*****************************************************************************
 �ṹ��    : CBPCA_PID_MSGID_MAP_TABLE_STRU
 �ṹ˵��  : HDLC֡�е�MsgId��CBPCA��Ҫת������PID֮���ӳ���ϵ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPid;              /* CBPCA��Ҫת������PID */
    VOS_UINT16                          usMsgId;            /* HDLC֡�е�MsgId */
    VOS_UINT16                          usRsv;              /* �����ֽ� */
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType;          /* ���ӦPID���MsgType */
}CBPCA_PID_MSGID_MAP_TABLE_STRU;

/*****************************************************************************
 �ṹ��    : CBPCA_MSG_HDR_STRU
 �ṹ˵��  : CSIMA���յ�����Ϣ��ͷ��������Ϣ����������ж���Ϣ����ʹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CBPCA_MSG_TYPE_ENUM_UINT32          enMsgType;          /* ��ϢID */
}CBPCA_MSG_HDR_STRU;

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 ��������
*****************************************************************************/


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of cbpacommagent.h*/

