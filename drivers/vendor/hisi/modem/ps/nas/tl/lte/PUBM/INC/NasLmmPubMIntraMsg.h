

#ifndef __NASLMMPUBMINTRAMSG_H__
#define __NASLMMPUBMINTRAMSG_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "vos.h"
#include    "LRrcLNasInterface.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define NAS_EMM_BUF_MSG_MAX_NUM         (8)

/* the size for intra msg queue */
#define NAS_LMM_INTRA_MSG_MAX_NUM        (16)

#define NAS_EMM_INTRA_MSG_MAX_SIZE      (1024)

#define NAS_EMM_STATUS_MSG_SIZE          1

/* FSM MSG buffer*/
#define NAS_EMM_MAIN_MAX_HIGH_MSG_NUM   (16)                /* ����ĸ����ȼ���Ϣ���� */
#define NAS_EMM_MAIN_MAX_MID_MSG_NUM    (16)                /* ����������ȼ���Ϣ���� ��ʱ���� */
#define NAS_EMM_MAIN_MAX_LOW_MSG_NUM    (4)                 /* ����ĵ����ȼ���Ϣ���� ��ʱ���� */

#define NAS_LMM_INTRA_MSG_HEADER         0x00121200

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_LMM_INTRA_MSG_ID_ENUM_UINT32
 ö��˵��  : �ڲ�����Ϣ���Ͷ���

ulMsgID����4����:

-----------------------------------------------------------
  �ֽڸ�λ                                      �ֽڵ�λ
-----------------------------------------------------------
| BYTE1��4λ + 0000 |  BYTE2    |   BYTE3    |    BYTE4   |
-----------------------------------------------------------
0000��Э��ģ�����Ϣ|  Դģ��� |  Ŀ��ģ���| ��Ϣ��0-255
-----------------------------------------------------------
0001��L2 LOG        |           |            |
-----------------------------------------------------------
0010���տ���Ϣ      |           |            |
-----------------------------------------------------------
0011����ͨ����      |           |            |
-----------------------------------------------------------
0100��ʵʱ�������  |           |            |
-----------------------------------------------------------
0101���ؼ��¼�      |           |            | ��������
-----------------------------------------------------------

MM��ģ���Ϊ            : 0x02
MM���ڲ���Ϣ�ı��Ϊ   : 0x000202**,ֻ�����һ���ֽ������ڲ���ϢID
*****************************************************************************/
enum NAS_LMM_INTRA_MSG_ID_ENUM
{
    ID_NAS_LMM_INTRA_MM_MM_BEGIN                             = NAS_LMM_INTRA_MSG_HEADER|0x00,

    /* MM �������ڲ�����Ϣ,��дԴ��Ŀ��ģ������ */


    /* MMC �ļ���Ϣ */
    ID_NAS_LMM_INTRA_EMMC_EMM_START_REQ                       = NAS_LMM_INTRA_MSG_HEADER|0x01,
    ID_NAS_LMM_INTRA_EMMC_EMM_START_CNF                       = NAS_LMM_INTRA_MSG_HEADER|0x02,
    ID_NAS_LMM_INTRA_EMMC_EMM_STOP_REQ                        = NAS_LMM_INTRA_MSG_HEADER|0x03,
    ID_NAS_LMM_INTRA_EMMC_EMM_STOP_CNF                        = NAS_LMM_INTRA_MSG_HEADER|0x04,
    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_REQ                        = NAS_LMM_INTRA_MSG_HEADER|0x05,
    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND                        = NAS_LMM_INTRA_MSG_HEADER|0x06,
    ID_NAS_LMM_INTRA_EMMC_EMM_CELL_SELECTION_CTRL_REQ         = NAS_LMM_INTRA_MSG_HEADER|0x07,
    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND                    = NAS_LMM_INTRA_MSG_HEADER|0x08,
    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND               = NAS_LMM_INTRA_MSG_HEADER|0x09,
    /*ID_NAS_LMM_INTRA_EMMC_EMM_ACTION_RESULT_REQ               = NAS_LMM_INTRA_MSG_HEADER|0x0a,*/


    /* MRRC���ڲ���Ϣ */

     /* NAS_EMM_MRRC_INTRA_DATA_REQ_STRU ����ģ��ͨ������Ϣ����MRRC���Ϳտ���Ϣ*/
    ID_NAS_LMM_INTRA_MRRC_DATA_REQ                           = NAS_LMM_INTRA_MSG_HEADER|0x0b,

    /* NAS_EMM_MRRC_INTRA_REL_REQ_STRU ����ģ��ͨ������Ϣ����MRRC�ͷ�RRC����*/
    ID_NAS_LMM_INTRA_MRRC_REL_REQ                            = NAS_LMM_INTRA_MSG_HEADER|0x0c,

    /* MRRC������ģ�鷢��INTRA_CONNECT_FAIL_IND�����ͷ����*/
    ID_NAS_LMM_INTRA_MRRC_CONNECT_FAIL_IND                   = NAS_LMM_INTRA_MSG_HEADER|0x0d,

    /* REG���ڲ���Ϣ */

    /* ����ģ�鷢��ATTACH���ڲ���Ϣ */
    ID_NAS_LMM_INTRA_ATTACH_REQ                              = NAS_LMM_INTRA_MSG_HEADER|0x0f,

    /* DEREG���ڲ���Ϣ ����ģ�鷢��DETACH���ڲ���Ϣ*/
    ID_NAS_LMM_INTRA_DETACH_REQ                              = NAS_LMM_INTRA_MSG_HEADER|0x10,

    /* TAU�ڲ���Ϣ */
    ID_NAS_LMM_INTRA_TAU_REQ                                 = NAS_LMM_INTRA_MSG_HEADER|0x11,


    /*��ģ��ͨ������Ϣת������տ���Ϣ*/
    ID_NAS_LMM_INTRA_DATA_IND                                = NAS_LMM_INTRA_MSG_HEADER|0x15,

    /*�յ�RRC_REL_IND����INTRA_REL_IND��Ϣ�����͸���Ϣ����NAS����̬��CONN��ΪIDLE*/
    ID_NAS_LMM_INTRA_CONN2IDLE_REQ                           = NAS_LMM_INTRA_MSG_HEADER|0x16,

    /* EMM�յ�UsimStatusInd��Ϣ��ת����MMC */
    ID_NAS_LMM_INTRA_EMMC_EMM_USIM_STATUS_IND                = NAS_LMM_INTRA_MSG_HEADER|0x17,

    /* LMM��cs/ps1 mode��ҪDISABLE LTEʱ���Լ��������ڲ���Ϣ */
    /* SECUģ����EIA0����ʱ��EMMģ�鷢�������ڲ���Ϣ */
    ID_NAS_LMM_INTRA_EIA0_ACT_NOTIFY                         = NAS_LMM_INTRA_MSG_HEADER|0x19,

    ID_NAS_LMM_INTRA_MSG_TYPE_BUTT                           = NAS_LMM_INTRA_MSG_HEADER|0x1F
};
typedef VOS_UINT32 NAS_LMM_INTRA_MSG_ID_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : NasMmIntraMsgCB
 �ṹ˵��  : NAS_LMM�ڲ���Ϣ�ṹ,ͬVOS����ʱ����Ľṹ MsgCB
*****************************************************************************/
struct NasMmIntraMsgCB
{
    VOS_MSG_HEADER
    VOS_UINT8 aucValue[4];
};

typedef struct NasMmIntraMsgCB          NasMmIntraMsgBlock;

/*****************************************************************************
 �ṹ��    : NAS_LMM_INTRA_MSG_STRU
 �ṹ˵��  : NAS_LMM�ڲ���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    NAS_LMM_INTRA_MSG_ID_ENUM_UINT32     ulMsgId;                /* ��Ϣ ID */
    VOS_UINT8                           aucMsgData[4];          /* ������Ϣ�洢 */
}NAS_LMM_INTRA_MSG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_INTRA_DATA_IND_STRU
 �ṹ˵��  : NAS_LMM�ڲ��տ���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    NAS_LMM_INTRA_MSG_ID_ENUM_UINT32     ulMsgId;                /* ��Ϣ ID */
    LRRC_LNAS_MSG_STRU                    stNasMsg;               /* �տ���Ϣ������*/
}NAS_LMM_INTRA_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LMM_INTER_MSG_QUEUE_STRU
 �ṹ˵��  : NAS_LMM�ڲ���Ϣ���нṹ
             usHeader   : ָ����һ�����ӵ���Ϣ
             usTail     : ָ����һ����ӵ���Ϣ���������λ�ã���λ�õ�ǰΪ��
                          ��aucMsgBuff[usTail]����ǰΪ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usHeader;                                   /* ��ͷ */
    VOS_UINT16                      usTail;                                     /* ��β */
    VOS_UINT8                       aucMsgBuff[NAS_LMM_INTRA_MSG_MAX_NUM][NAS_EMM_INTRA_MSG_MAX_SIZE];    /* ��Ϣ������� */
}NAS_LMM_INTRA_MSG_QUEUE_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern  VOS_UINT32  NAS_LMM_MMSendIntraMsg(  VOS_VOID          **pucIntraMsg );
extern  NasMmIntraMsgBlock * NAS_LMM_GetSendIntraMsgBuffAddr( VOS_UINT32 ulBuffSize );/*lint -e826*/
extern  VOS_VOID    NAS_LMM_MAIN_EnQueue(VOS_VOID);
extern  VOS_UINT8 * NAS_LMM_GetIntraMsgFromQueue( VOS_VOID  );
extern  VOS_VOID    NAS_LMM_DeQueue(VOS_VOID);
extern  MsgBlock *  NAS_LMM_GetLmmMmcMsgBuf( VOS_UINT32 ulBuffSize );
extern  VOS_VOID    NAS_LMM_SendLmmMmcMsg( const VOS_VOID *pstLmmMmcMsg );

#define NAS_LMM_SendIntraMsg(pMsg )     NAS_LMM_MMSendIntraMsg( (VOS_VOID**)(&(pMsg)))/*lint +e826*/

/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmPubMIntraMsg.h*/
