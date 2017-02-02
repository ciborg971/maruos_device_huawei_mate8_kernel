#ifndef NSR_API_DEF_INCLUDED
#define NSR_API_DEF_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

enum  enNSRErrorCode
{
    NSR_OK = 0,                                     /*<0>�����ɹ�*/
    NSR_ERR,                                        /*<1>����ʧ��*/
    NSR_ERR_WRITE_QUEUE_FAIL,                       /*<2>д����ʧ��*/
    NSR_ERR_REINIT,                                 /*<3>�ظ���ʼ��*/
    NSR_ERR_RESOURCE_UAAVAILABLE,                   /*<4>�ڴ�����ʧ��*/
    NSR_ERR_GET_I3_INDEX_ERROR,                     /*<5>NSR��ȡI3 Indexʧ��*/
    NSR_ERR_GET_I3_JOIN_ERROR,                      /*<6>NSR��ȡI3 Joinʧ��*/
    NSR_ERR_PARAMETER_ERROR,                        /*<7>��������*/
    NSR_ERR_SEND_BATCH_ERROR,                       /*<8>�����������ݴ���*/
    NSR_ERR_SEND_REALTIME_ERROR,                    /*<9>����ʵʱ���ݴ���*/
    NSR_ERR_OSPF_NOT_EXIST,                         /*<10>OSPF���̲�����*/
    NSR_ERR_CB_TYPE_NOT_FOUND,                      /*<11>�����������Ͳ�����*/
    NSR_ERR_OSPF_DATA_INIT_ERROR,                   /*<12>OSPF NSR���ݳ�ʼ������*/
    NSR_ERR_OSPF_REPL_INIT_ERROR,                   /*<13>OSPF NSR�������ݳ�ʼ������*/
    NSR_ERR_GET_LSDB_TLV_ERROR,                     /*<14>��ȡ���ݵ�LSDB TLV����*/
    NSR_ERR_INSERT_LSDB_ERROR,                      /*<15>LSDB������*/
    NSR_ERR_REMOVE_LSDB_ERROR,                      /*<16>LSDB������*/
    NSR_ERR_CAN_NOT_FIND_OSPF_ENT,                  /*<17>���ұ��ݵ�OSPF���̴���*/
    NSR_ERR_RESTORE_IF_CB_NOT_FOUND,                /*<18>���ݻָ�ʱ�޷��ҵ�OSPF�ӿڿ��ƿ�*/
    NSR_ERR_RESTORE_REPL_IF_CB_ERROR,               /*<19>�ָ����ݵĽӿ���Ϣʱ����*/
    NSR_ERR_RESTORE_IF_CB_ERROR,                    /*<20>���ݻָ��ӿڿ��ƿ�ʱ����*/
    NSR_ERR_RESTORE_TYPE_NOT_FOUND,                 /*<21>���ݻָ��������Ͳ�����*/
    NSR_ERR_RESTORE_ERROR,                          /*<22>���ݻָ����ݹ��̴���*/
    NSR_ERR_RESTORE_PERMANENT_NBR_CB_NOT_FOUND,     /*<23>���ݻָ�ʱ�޷��ҵ�OSPF�����ھӿ��ƿ�*/
    NSR_ERR_RESTORE_DYNAMIC_NBR_CB_ALREADY_EXIST,   /*<24>���ݻָ�ʱ�޷��ҵ�OSPF��̬���ƿ�*/
    NSR_ERR_RESTORE_REPL_NBR_CB_ERROR,              /*<25>�ָ����ݵ��ھ���Ϣʱ����*/
    NSR_ERR_RESTORE_NBR_CB_ERROR,                   /*<26>���ݻָ��ӿڿ��ƿ�ʱ����*/
    NBR_ERR_RESTORE_LSDB_AREA_NOT_FOUND,            /*<27>���ݻָ�LSAʱ���򲻴���*/
    NBR_ERR_RESTORE_LSDB_CB_ERROR,                  /*<28>���ݻָ�LSAʱ����*/
    NBR_ERR_RESTORE_LSDB_TO_IF_ERROR,               /*<29>���ݻָ�LSA���ھ�ʱ����*/
    NBR_ERR_RESTORE_LSDB_TO_AREA_ERROR,             /*<30>���ݻָ�LSA���ھ�ʱ����*/
    NSR_ERR_QUERY_INPUT_NULL,                       /*<31>��ѯ�ӿ����ΪNULL*/
    NSR_ERR_OSPF_PROCESSID_OVERFLOW,                /*<32>ospfʵ���ų������ֵ*/
    NSR_ERR_OSPF_PROCESS_NOT_FOUND,                 /*<33>�Ҳ�����Ӧ��ospfʵ��*/
    NSR_ERR_OSPF_IF_CB_NOT_FOUND,                   /*<34>�Ҳ����ӿ�*/
    NSR_ERR_NO_OSPF_PROCESS_EXIT,                   /*<35>û���������е�ospfʵ��*/
    NSR_ERR_END_OF_TABLE,                           /*<36>�Ѿ����ҵ�����ĩβ */
    NSR_ERR_AREA_FILTER_FLAG_INVALID,               /*<37>��ѯ�������������־���Ϸ� */
    NSR_ERR_RESTORE_NBR_PARENT_IF_CONSISTENT,       /*<38>���ݻָ��ھӸ��ӿڵ�ַ��ͻ*/
    NSR_ERR_BACKUP_DATA_CHECK_ERROR,                /*<39>���յı������ݼ�����*/
    NSR_ERR_NSR_ALREADY_BEEN_ENABLE,                /*<40>NSR�����Ѿ�ʹ��*/
    NSR_ERR_NSR_ALREADY_BEEN_DISABLE,               /*<41>NSR�����Ѿ�ȥ����*/
    NSR_ERR_OSPF_PROCESSID_NOT_MATCH,               /*<42>�����ospf���̺�����ҵ��Ĳ�ƥ��*/
    NSR_ERR_CREATE_BACKUP_BEGIN_TIMER_FAIL,         /*<43>����nsr���ݿ�ʼ��ʱ��ʧ��*/
    NSR_ERR_DELETE_BACKUP_BEGIN_TIMER_FAIL,         /*<44>����nsr���ݿ�ʼ��ʱ��ʧ��*/
    NSR_ERR_CREATE_BACKUP_TIMER_FAIL,               /*<45>����nsr���ݶ�ʱ��ʧ��*/
    NSR_ERR_DELETE_BACKUP_TIMER_FAIL,               /*<46>����nsr���ݶ�ʱ��ʧ��*/
    NSR_ERR_BACKUP_MSG_TYPE_ERROR,                  /*<47>ospf���͵ı�����Ϣ���ʹ���*/
    NSR_ERR_IF_BACKUP_DATA_ERROR,                   /*<48>slave�յ�if�������������쳣*/
    NSR_ERR_IF_BACKUP_MSG_TYPE_ERROR,               /*<49>slave�յ�if����������Ϣ���ʹ���*/
    NSR_ERR_ALLOC_INIT_IF_CB_FAIL,                  /*<50>slave�յ�if�������ݣ������ʼ��if���ƿ�ʧ��*/
    NSR_ERR_IF_CB_NOT_EXIST,                        /*<51>if���ƿ鲻����*/
    NSR_ERR_IF_BACKUP_DATA_LENGH_IS_ZERO,           /*<52>���ݵĽӿ���Ϣ���ݳ���Ϊ0*/
    NSR_ERR_IF_BACKUP_DATA_LENGH_IS_NOT_ZERO,       /*<53>���ݵĽӿ���Ϣ���ݳ��Ȳ�Ϊ0*/
    NSR_ERR_IF_BACKUP_MSG_REP_OPERATION_ERROR,      /*<54>���ݵĽӿ���Ϣ�������ʹ���*/
    NSR_ERR_BACKUP_MSG_DATA_LENGH_IS_ZERO,          /*<55>���ݵĽӿ���Ϣ�������ʹ���*/
    NSR_ERR_BACKUP_NBR_KEY_ERROR,                   /*<56>���ݵĽӿ���Ϣ�������ʹ���*/
    NSR_ERR_BACKUP_IF_KEY_ERROR,                    /*<57>���ݵĽӿ���Ϣ�������ʹ���*/
    NSR_ERR_RESTORE_IF_ALREADY_UP,                  /*<58>���ݻָ�ʱ�޷��ҵ�OSPF�ӿڿ��ƿ�*/
    NSR_ERR_PARAMETER_IS_NULL,                      /*<59>����Ϊ��*/
    NSR_ERR_SUB_MODULE_ALREADY_REGIST,              /*<60>NSR��ģ���Ѿ�ע��*/
    NSR_ERR_NOT_SUPPORT_NSR,                        /*<61>NSR���ܱ��ü�����ǰ��֧��*/
    NSR_ERR_I3AGENT_NSR_OSPF_MSGSENDHOOK_IS_NULL,   /*<62>I3Agentע���OSPF NSR��Ϣ������ΪNULL*/
    NSR_ERR_NSR_NOT_INIT,                           /*<63>NSRδ��ʼ��*/
    NSR_ERR_NSR_OSPF_NOT_INIT,                      /*<64>NSR OSPFδ��ʼ��*/
    NSR_ERR_NSR_NOT_ENABLE,                         /*<65>NSRδʹ��*/
    NSR_ERR_NSR_CAPABILITY_IS_CONFLICT,             /*<66>NSRʹ��ȥʹ��״̬��ͻ*/
    NSR_ERR_NSR_OSPF_CAPABILITY_IS_CONFLICT,        /*<67>NSR OSPF ʹ��ȥʹ��״̬��ͻ*/
    NSR_ERR_NSR_OSPF_STATUS_NOT_EXPECTED,           /*<68>OSPF NSR���ڷ�Ԥ��״̬(ʹ��NSRʱ����������)*/
    NSR_ERR_GET_BASE_INFO_HOOK_NOT_REGIST,          /*<69>��ȡNSR������Ϣ�Ĺ���δע��(�ù����ɲ�Ʒע��)*/
    NSR_ERR_SEND_BACKUP_MSG_HOOK_NOT_REGIST,        /*<70>NSR���ͱ������ݵĹ���δע��(�ù����ɲ�Ʒע��)*/
    NSR_ERR_SEND_CONTROL_MSG_HOOK_NOT_REGIST        /*<71>NSR���Ϳ�����Ϣ����δע��(�ù����ɲ�Ʒע��)*/
};

/*NSR��������Ϣ���Ͷ���*/
#define NSR_CONTROL_MSG_BOARD            1     /*����״̬��Ϣ(��/��)*/
#define NSR_CONTROL_MSG_CHANNEL          2     /*����ͨ����Ϣ(ͨ���Ƿ�OK)*/
#define NSR_CONTROL_MSG_SLAVE_BOARD      3     /*����״̬��Ϣ(�����Ƿ�OK)*/
#define NSR_CONTROL_MSG_BACKUP           4     /*����״̬��Ϣ*/
#define NSR_CONTROL_MSG_RESTORE          5     /*���ݻָ���Ϣ()*/
#define NSR_CONTROL_MSG_SMOOTH           6     /*ƽ����Ϣ*/

/*NSR��ɫ(��/��)*/
#define NSR_ROLE_NULL    0      /*NSR��ɫΪ��ʼ״̬*/
#define NSR_ROLE_MASTER  1      /*NSR��ɫΪ��*/
#define NSR_ROLE_SLAVE   2      /*NSR��ɫΪ��*/

/*NSR����������������*/
#define NSR_CONTROL_OK              0   /*�ɹ�*/
#define NSR_CONTROL_UNSUCCESS       1   /*ʧ��*/

/*ͨ��״̬����*/
#define NSR_CHANNEL_INACTIVE   0        /*ͨ����Ч*/
#define NSR_CHANNEL_ACTIVE     1        /*ͨ����Ч*/

/*����״̬����*/
#define NSR_SLAVE_BOARD_INACTIVE   0    /*����δ����*/
#define NSR_SLAVE_BOARD_ACTIVE     1    /*���弤��*/

/*����״̬����*/
#define NSR_BACKUP_NULL                     0   /*���������ֳ�ʼֵ*/
#define NSR_BACKUP_START                    1   /*���ݿ�ʼ*/
#define NSR_BACKUP_ERROR                    2   /*���ݴ���*/
#define NSR_BACKUP_OUT_OF_ORDER             3   /*��������*/
#define NSR_BACKUP_TIMEOUT                  4   /*���ݳ�ʱ*/
#define NSR_BACKUP_FINISH                   5   /*���ݽ���*/
#define NSR_BACKUP_CANCEL                   6   /*ȡ������*/
#define NSR_BACKUP_START_ACK                7   /*����ظ����壬�յ����巢���� backup start ��Ϣ*/
#define NSR_BACKUP_MAX                      8   /*�������������ֵ*/

/*�������ݻָ�֪ͨ����*/
#define NSR_RESTORE_NULL        0   /*�ָ������ֳ�ʼֵ*/
#define NSR_RESTORE_START       1   /*�ָ���ʼ*/
#define NSR_RESTORE_FINISH      2   /*�ָ�����*/
#define NSR_RESTORE_MAX         3   /*�ָ����������ֵ*/

/*NSRƽ��֪ͨ����*/
#define NSR_SMOOTH_NULL          0    /*ƽ�������ֳ�ʼֵ*/
#define NSR_SMOOTH_START         1    /*ƽ����ʼ*/
#define NSR_SMOOTH_FINISH        2    /*ƽ������*/
#define NSR_SMOOTH_MAX           3    /*ƽ�����������ֵ*/

/*NSR��������Ϣ����Ŀ�궨��(UCHAR�ĸ���λ�ֱ����Master��Slave)*/
#define NSR_CONTROL_MSG_DEST_MASTER     0x80    /*NSR��������Ϣ����Ŀ���� ��*/
#define NSR_CONTROL_MSG_DEST_SLAVE      0x40    /*NSR��������Ϣ����Ŀ���� ��*/

/*NSR��������Ϣת���ĸ�ģ�鴦��*/
#define NSR_CONTROL_MSG_DIRECT_AGENT   0x01   /*NSR��������Ϣ����Ŀ���� ��Ʒ*/
#define NSR_CONTROL_MSG_DIRECT_NSR     0x02   /*NSR��������Ϣ����Ŀ���� OSPF NSR ģ��*/

#define NSR_CAPABILITY_NULL        0x0    /*NSRʹ��/ȥʹ�ܳ�ʼֵ*/
#define NSR_CAPABILITY_ENABLE      0x1    /*NSRʹ��*/
#define NSR_CAPABILITY_DISENABLE   0x2    /*NSRȥʹ��*/

/*STRUCT<����״̬��Ϣ>*/
typedef struct nsr_backup_info
{
    USHORT usProcessID;      /*OSPF����ID*/
    UCHAR ucBackupType;      /*���ݱ��ݱ�ʶ��Ϣ*/
    UCHAR ucResult;          /*���ݽ��*/
    UCHAR ulReserve[8];      /*Ԥ����չ�ֶ�*/
}NSR_BACKUP_INFO;

/*STRUCT<�ָ���Ϣ>*/
typedef struct nsr_restore_info
{
    UCHAR ucRestoreType;    /*���ݻָ���ʶ��Ϣ*/
    UCHAR ucResult;         /*���ݻָ����*/
    CHAR  pad[2];
    UCHAR ulReserve[8];     /*Ԥ����չ�ֶ�*/
}NSR_RESTORE_INFO;

/*STRUCT<ƽ����Ϣ>*/
typedef struct nsr_smooth_info
{
    UCHAR ucSmoothType;     /*NSRƽ����ʶ��Ϣ*/
    UCHAR ucResult;         /*NSRƽ�����*/
    CHAR  pad[2];
    UCHAR ulReserve[8];     /*Ԥ����չ�ֶ�*/
}NSR_SMOOTH_INFO;

/*STRUCT<NSR����������Ϣ����>*/
typedef struct nsr_control_msg
{
    UCHAR ucMsgType;                         /*��Ϣ����*/
    UCHAR ucDirect;                          /*��������Ϣ�ķ���Ŀ��*/
    CHAR  pad[2];
    UCHAR ulReserve[4];                      /*Ԥ����չ�ֶ�*/
    union
      {
          UCHAR ucBoardInfo;                  /*����״̬֪ͨ*/
          UCHAR ucChannelInfo;                /*ͨ��״̬֪ͨ*/
          UCHAR ucSlaveBoardInfo;             /*����״̬֪ͨ*/
          NSR_BACKUP_INFO stBackupInfo;       /*����״̬֪ͨ*/
          NSR_RESTORE_INFO stRestoreInfo;     /*���ݻָ�֪ͨ*/
          NSR_SMOOTH_INFO stSmothInfo;        /*ƽ��֪ͨ*/
      }uControlMsg;

}NSR_CONTROL_MSG;

/*STRUCT<NSR COMMON�ı�������>*/
typedef struct nsr_common_info_show
{
    BOOL_T bNSRInit;              /*NSR�Ƿ��ʼ�� 0-δ��ʼ��  1-�ѳ�ʼ��*/
    UCHAR ucNSRCapability;        /*NSR�Ƿ�ʹ��   1-ʹ��  2-��ʹ��, Ĭ��Ϊ2*/
    UCHAR ucNextNSRCapability;    /*�ӳ���Ч��NSRʹ��״̬��Ĭ��Ϊ0*/
    UCHAR ucNSRRole;              /*NSR��ɫ,Ĭ��Ϊ��*/
    UCHAR ucIFReadyFlag;          /*�ӿ��ϱ�������ʶ*/
    UCHAR ucIFReadyStatus;        /*�ӿ��ϱ�״̬*/
    UCHAR ucNSRStatus;            /*NSR״̬*/
    ULONG ulNSRFlag;              /*NSR��ǣ���λʹ��*/
}NSR_COMMON_INFO_SHOW;

/*STRUCT<NSR������Ϣ>*/
typedef struct nsr_base_info
{
    UCHAR ucBoardInfo;                  /*����״̬*/
    UCHAR ucChannelInfo;                /*ͨ��״̬*/
    UCHAR ucSlaveBoardInfo;             /*����״̬*/
    UCHAR pad[1];
}NSR_BASE_INFO;

/*******************************************************************************
*    Func Name: NSR_SetNSRCapability
* Date Created: 2013-11-07
*       Author: guojianjun178934
*      Purpose: ���ͱ�������
*  Description: 
*        Input: UCHAR  *: ��������
*               ULONG :   ���ݳ���
*               BOOL_T :  �����װ���ʶ
*       Output: 
*       Return: �ɹ���NSR_OK
*               ʧ�ܣ�������
*      Caution: 
*        Since: V300R002C00
*    Reference: NSR_RegFunSendBackupMsgHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-07   guojianjun178934        Create
*
*******************************************************************************/
typedef ULONG (*NSR_SEND_BACKUP_MSG_FUNC)(UCHAR *, ULONG, BOOL_T);

/*******************************************************************************
*    Func Name: NSR_SetNSRCapability
* Date Created: 2013-11-07
*       Author: guojianjun178934
*      Purpose: ���Ϳ�����Ϣ
*  Description: 
*        Input: NSR_CONTROL_MSG  *: ������Ϣ
*       Output: 
*       Return: �ɹ���NSR_OK
*               ʧ�ܣ�������
*      Caution: 
*        Since: V300R002C00
*    Reference: NSR_RegFunSendControlMsgHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-07   guojianjun178934        Create
*
*******************************************************************************/
typedef ULONG (*NSR_SEND_CONTROL_MSG_FUNC)(NSR_CONTROL_MSG *);

/*******************************************************************************
*    Func Name: NSR_SetNSRCapability
* Date Created: 2013-11-07
*       Author: guojianjun178934
*      Purpose: ��NSRģ���ȡ �����ɫ��ͨ��״̬������״̬
*  Description: 
*        Input: 
*       Output: NSR_BASE_INFO *:NSR������Ϣ �����ɫ��ͨ��״̬������״̬
*       Return: �ɹ���NSR_OK
*               ʧ�ܣ�������
*      Caution: 
*        Since: V300R002C00
*    Reference: NSR_RegFunGetNSRBaseInfoHook
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-07   guojianjun178934        Create
*
*******************************************************************************/
typedef ULONG (*NSR_GET_NSR_BASE_INFO_FUNC)(NSR_BASE_INFO *);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
