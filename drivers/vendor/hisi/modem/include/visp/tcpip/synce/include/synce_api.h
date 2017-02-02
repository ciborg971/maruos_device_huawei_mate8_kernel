/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              synce_api.h
*
*  Project Code: VISPV100R008C03
*   Module Name: synce
*  Date Created: 2009-12-16
*        Author: luogaowei(61496)
*   Description: SyncEģ��API
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-12-16  luogaowei(61496)     Create the first version.
*
*******************************************************************************/
#ifndef _SYNCE_API_H
#define _SYNCE_API_H

#ifdef  __cplusplus
    extern "C"{
#endif

/*ERRORCODE<SyncE������>*/
typedef enum enumSyncEErrCode
{
    SYNCE_OK = VOS_OK,                 /* 0  OK                                */
    SYNCE_ERR,                         /* 1  ERROR                             */
    SYNCE_ERR_PARA = MID_COMP_SYNCE + 2,                    /* 2 ������Ч�Դ���                    */
    SYNCE_ERR_NO_REGISTER,          /*3 ͬ����̫δע��*/    
    SYNCE_ERR_NULL_POINTER,            /* 4  ָ���������                      */ 
    SYNCE_ERR_IF_NULL,                 /* 5  �ӿڲ�����                        */
    SYNCE_ERR_IF_INVALID,              /* 6  �ӿ����ʹ���                      */
    SYNCE_ERR_MEMORY,                  /* 7  �ڴ�ռ䲻��                      */
    SYNCE_ERR_ENABLED,                 /* 8  SYNCE��ʹ��                         */
    SYNCE_ERR_DISABLED,                /* 9  SYNCEδʹ��                         */
    SYNCE_ERR_MBUF_PREPEND,            /* 10 MBUFָ��ǰ�ƴ��� */
    SYNCE_ERR_CB_NOTEXIST,              /* 11 ���ƿ鲻���� */
    SYNCE_ERR_PORT_IS_VIRTUAL,         /* 12 �ӿڷǱ���ӿ� */
    SYNCE_ERR_QL_INVALID,             /*13 �����QL*/
    SYNCE_ERR_RCV_EXIST_ALREADY,    /*14  ϵͳ�Ѿ����ڽ��սӿ�*/
    SYNCE_ERR_ITU_INVALID,          /*15 ITU�ֶηǷ�*/
    SYNCE_ERR_ITU_SUBTYPE_INVALID,          /*16 ITU SUBTYPE�ֶηǷ�*/
    SYNCE_ERR_VERSION_INVALID,          /*17 �汾�ֶηǷ�*/
    SYNCE_ERR_IF_IS_DOWN,          /*18 �ӿ���DOWN״̬*/
    SYNCE_ERR_RCV_FROM_LOCAL,          /*19�յ��������͵�SSM����*/
    SYNCE_ERR_MACADDR_NOT_MULTI,    /*20�Ƕಥ����*/
    SYNCE_ERR_INVALID_PKT_LEN,    /*21���ĳ��ȷǷ�*/
    SYNCE_ERR_MALLOC_MEN_FAIL,    /*22�����ڴ�ʧ��*/
    SYNCE_ERR_MBUF_COPY_FAIL,    /*23MBUF����ʧ��*/
    SYNCE_ERR_GET_MAC_FAIL,    /*24��ȡphysical��ַʧ��*/
    SYNCE_ERR_UNSUPPORT_TLV_TYPE,  /*25 ��ǰ��֧�ָ�����SSM TLV TYPE*/
    SYNCE_ERR_TLV_LENGTH_INVALID,  /*26 TLV Length��Ƿ�*/
    SYNCE_ERR_TLV_CODE_INVALID,  /*27 TLV CODE��Ƿ�*/
    SYNCE_ERR_MAXCODE                  /* SYNCE���������ֵ,�Ժ���Ӵ������밴˳����ӵ���ǰ */
}SYNCE_ERRCODE_E;


/*STRUCT<�ӿ�SyncE PDU����ͳ��>*/
typedef struct tagSyncEPduStat
{
    ULONG ulSndTotalPdu;                 /* �ӿڷ����ܵ�SSM����        */
    ULONG ulSndDropPdu;                  /* �ӿڷ���ʱ�ܵĶ���SSM����  */
    ULONG ulSndInfoPdu;                 /* �ӿڷ�����ϢSSM����        */
    ULONG ulSndEventPdu;                 /* �ӿڷ����¼�SSM����        */
    
    ULONG ulRcvTotalPdu;                 /* �ӿڽ����ܵ�SSM����        */
    ULONG ulRcvDropPdu;                  /* �ӿڽ����ܵĶ���SSM����    */
    ULONG ulRcvInfoPdu;                  /* �ӿڽ�����ϢSSM����        */
    ULONG ulRcvEventPdu;                 /* �ӿڽ����¼�SSM����        */
}SYNCE_PDUSTAT_S;

typedef struct tagSyncEPduStatList
{
    ULONG ulIfIndex;
    SYNCE_PDUSTAT_S stSynceStat;
}SYNCE_PDUSTAT_LIST_S;

/*MACRO<SYNCE_Define> */
#define SYNCE_SEND_MODE          1  /*�ӿ��շ�ģʽ:����*/
#define SYNCE_RECV_MODE          2  /*�ӿ��շ�ģʽ:����*/

/*SYNCE���Կ��ر�־*/
#define SYNCE_DBG_RCV_ERR_MASK          0X01      /*�򿪽��մ�����Ϣ���Կ���*/
#define SYNCE_DBG_SND_ERR_MASK          0X02      /*�򿪷��ʹ�����Ϣ���Կ���*/
#define SYNCE_DBG_RCV_MASK                  0X04     /*�򿪽��ձ��ĵ��Կ���*/
#define SYNCE_DBG_SND_MASK                  0X08     /*�򿪷��ͱ��ĵ��Կ���*/
#define SYNCE_DBG_ALL                             0x0F     /* ���е��Կ��� */

/*******************************************************************************
*    Func Name: TCPIP_EnableSyncMode
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose: ָ����̫�˿�ʹ��ͬ��ģʽ
*  Description: ָ����̫�˿�ʹ��ͬ��ģʽ����ָ��ͬ���շ���ɫ.
*        Input: ULONG ulIfIndex:��̫�ӿ�����
*               ULONG ulSyncRole:ͬ���շ���ɫ
*                       0:δָ������ѡԴ��������Ŀǰ��֧�֣�
*                       1:���նˣ�2�����Ͷ�
*       Output: 
*       Return: �ɹ�����VOS_OK
*                  ʧ�ܷ��ش�����
*      Caution: ����ͬ����̫ģʽ�µĽӿڲ��ܹ����պͷ���ESMC���ġ�
*      ͬһ��ͬ����̫�豸��������ֻ����һ�����սӿڡ�
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableSyncMode(ULONG ulIfIndex, ULONG ulSyncRole);

/*******************************************************************************
*    Func Name: TCPIP_DisableSyncMode
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose: ָ����̫�˿�ȥʹ��ͬ��ģʽ��
*  Description: ָ����̫�˿�ȥʹ��ͬ��ģʽ��
*        Input: ULONG ulIfIndex:��̫�ӿ�����
*       Output: 
*       Return: �ɹ�����VOS_OK
*                  ʧ�ܷ��ش�����
*      Caution: ����ͬ����̫ģʽ�µĽӿڲ��ܹ����պͷ���ESMC���ġ�
*      ȥʹ��ͬ��ģʽ��ͬ���շ���ɫ����ͬʱ�������
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_DisableSyncMode(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_QuerySyncMode
* Date Created: 2009-12-24
*       Author: raofei62469
*      Purpose: ָ����̫�˿ڲ�ѯͬ��ģʽʹ�����
*  Description: ָ����̫�˿ڲ�ѯͬ��ģʽʹ�������
*        Input: ULONG ulIfIndex:�ӿ�����
*       Output: ULONG *pulSyncMode:ͬ��״̬(���ջ���)
*       Return: �ɹ�����SYNCE_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-24   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_QuerySyncMode(ULONG ulIfIndex, ULONG *pulSyncMode);

/*******************************************************************************
*    Func Name: TCPIP_SetLocalQL
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose: ���ñ���QLֵ��
*  Description: ���ñ���QLֵ�� 
*        Input: USHORT usQLValue:QLֵ
*       Output: 
*       Return: �ɹ�����VOS_OK
*                  ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLocalQL(USHORT usQLValue);

/*******************************************************************************
*    Func Name: TCPIP_GetLocalQL
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose: ��ȡ����QLֵ�� 
*  Description: ��ȡ����QLֵ�� 
*        Input: 
*       Output: USHORT *pusQLValue:QLֵ
*       Return: �ɹ�����VOS_OK
*                  ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_GetLocalQL(USHORT* pusQLValue);


extern ULONG TCPIP_SetSsmTlvLength(ULONG ulSsmTlvLen);


extern ULONG TCPIP_GetSsmTlvLength(ULONG *pulSsmTlvLen);

typedef ULONG (*SYNCE_QL_NOTIFY_FUNC)(ULONG ulFlag, ULONG ulNewQL);
/*******************************************************************************
*    Func Name: TCPIP_Reg_Synce_QL_Notify_Hook
* Date Created: 2010-7-23
*       Author: luogaoweil/tuojinbin
*  Description: ͬ����̫״̬�仯��֪ͨע�ắ��
*        Input: pfHookFunc����Ʒע��ĺ���ָ��
*        typedef ULONG (*SYNCE_QL_NOTIFY_FUNC)(ULONG ulFlag, ULONG ulNewQL);
*        ulFlag: 1��ʾ��Ч��0��ʾ��ʱ��
*        ulNewQL:��ʾ���յ�QLֵ.
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*******************************************************************************/
extern  ULONG TCPIP_Reg_Synce_QL_Notify_Hook(SYNCE_QL_NOTIFY_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_Set_Synce_GlobalMode
* Date Created: 2010-7-23
*       Author: luogaoweil/tuojinbin
*  Description: ָ����ȫ��ͬ����̫ģʽ:ͬ��ģʽ���߷�ͬ��ģʽ
*        Input: ulSyncMode:1��ʾͬ��ģʽ��0 ��ʾ��ͬ��ģʽ.
*       Output: 
*       Return: �ɹ�����VOS_OK
*                 ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*******************************************************************************/
extern ULONG TCPIP_Set_Synce_GlobalMode(USHORT usGlobalMode);

/*******************************************************************************
*    Func Name: TCPIP_Get_Synce_GlobalMode
* Date Created: 2010-7-23
*       Author: luogaoweil/tuojinbin
*  Description: ��ȡ��ǰͬ����̫��ͬ��ģʽ
*        Input:
*       Output: pulSyncMode
*       Return: �ɹ�����VOS_OK
*                 ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*******************************************************************************/
extern ULONG TCPIP_Get_Synce_GlobalMode(USHORT *pusGlobalMode);

/*******************************************************************************
*    Func Name: TCPIP_Get_Synce_GlobalMode
* Date Created: 2010-7-23
*       Author: luogaoweil/tuojinbin
*  Description:��ѯͬ����̫ȫ����Ϣ����ǰͬ��ģʽ
*        Input:
*       Output: 
*       Return: �ɹ�����VOS_OK
*                 ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*******************************************************************************/
extern VOID TCPIP_Show_Synce_GlobalInfo(VOID);
/*Add End*/


/*******************************************************************************
*    Func Name: TCPIP_ShowSyncMode
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose: ָ���ӿ�������ʾͬ��ģʽʹ�������
*  Description: ָ���ӿ�������ʾͬ��ģʽʹ�������
*           ������ulIfIndexΪ0ʱ����ʾ����ʹ��ͬ����̫�Ľӿڡ�
*        Input: ULONG ulIfIndex:��̫�ӿ�����
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern VOID TCPIP_ShowSyncMode(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ShowAllSyncInterface
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose: ��ʾ����ʹ��ͬ����̫�Ľӿڡ�
*  Description: ��ʾ����ʹ��ͬ����̫�Ľӿڡ�
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern VOID TCPIP_ShowAllSyncInterface(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowLocalQL
* Date Created: 2009-12-07
*       Author: raofei62469
*      Purpose:  ��ʾ�û����õı���QLֵ��
*  Description: ��ʾ�û����õı���QLֵ��
*        Input: 
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   raofei62469             Create
*
*******************************************************************************/
extern VOID TCPIP_ShowLocalQL(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SyncE_SetDbgSwitch
* Date Created: 2009-12-24
*       Author: raofei62469
*      Purpose: ����SyncE������Կ���
*  Description: ����SyncE������Կ���
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulDebugSwitch:���ر�־
*                            0x01:��ӡ������Ϣ
*                            0x02:��ӡ�����շ�������Ϣ
*       Output: 
*       Return: �ɹ�����SYNCE_OK��ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-24   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_SyncE_SetDbgSwitch(ULONG ulIfIndex, ULONG ulDebugSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SyncE_GetDbgSwitch
* Date Created: 2009-12-24
*       Author: raofei62469
*      Purpose:��ȡ��ǰSyncE������Կ�����Ϣ
*  Description: ��ȡ��ǰSyncE������Կ�����Ϣ
*        Input: ULONG ulIfIndex:�ӿ�����
*       Output: ULONG *pulDugInfo:��ǰ����״̬
*       Return: �ɹ�����SYNCE_OK��ʧ�ܷ��ش�����
*      Caution: : 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-24   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_SyncE_GetDbgSwitch(ULONG ulIfIndex, ULONG *pulDugInfo);

/*******************************************************************************
*    Func Name: TCPIP_SyncE_GetPacketStat
* Date Created: 2009-12-24
*      Purpose: ��ȡָ���ӿڱ����շ�ͳ����Ϣ
*       Author: raofei62469
*  Description: ��ȡָ���ӿڱ����շ�ͳ����Ϣ
*        Input: ULONG ulIfIndex:�ӿ�����
*       Output: SYNCE_PDUSTAT_S * pstPduStat:����ͳ����Ϣ
*       Return: �ɹ�����SYNCE_OK��ʧ�ܷ��ش�����
*      Caution: : 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-24   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_SyncE_GetPacketStat(ULONG ulIfIndex, SYNCE_PDUSTAT_S * pstPduStat);

/*******************************************************************************
*    Func Name: TCPIP_SyncE_ClearPacketStat
* Date Created: 2009-12-24
*       Author: raofei62469
*      Purpose: ���ָ���ӿڱ����շ�ͳ����Ϣ
*  Description:���ָ���ӿڱ����շ�ͳ����Ϣ
*        Input: ULONG ulIfIndex:�ӿ�����
*       Output: 
*       Return: �ɹ�����SYNCE_OK��ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-24   raofei62469             Create
*
*******************************************************************************/
extern ULONG TCPIP_SyncE_ClearPacketStat(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SyncE_ShowPacketStat
* Date Created: 2009-12-30
*       Author: raofei62469
*      Purpose: ��ʾָ���ӿڱ���ͳ����Ϣ
*  Description: ��ʾָ���ӿڱ���ͳ����Ϣ
*        Input: CHAR *pszIfName:
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-30   raofei62469             Create
*
*******************************************************************************/
extern VOID TCPIP_SyncE_ShowPacketStat(CHAR *pszIfName);

#ifdef  __cplusplus
}
#endif

#endif


